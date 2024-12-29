// SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;

// Collateralized Loan Contract
contract CollateralizedLoan {
    
    // Define the structure of a loan
    struct Loan {
        address payable borrower;
        address payable lender;
        uint collateralAmount;
        uint loanAmount;
        uint interestRate;
        uint dueDate;
        bool isFunded;
        bool isRepaid;
    }

    // Create a mapping to manage the loans
    mapping(uint => Loan) public loans;
    uint public nextLoanId;

    // Events for loan lifecycle
    event LoanRequested(uint loanId, address indexed borrower, uint collateralAmount, uint loanAmount);
    event LoanFunded(uint loanId, address indexed lender);
    event LoanRepaid(uint loanId);
    event CollateralClaimed(uint loanId);

    // Modifier to check if a loan exists
    modifier loanExists(uint loanId) {
        require(loans[loanId].borrower != address(0), "Loan does not exist");
        _;
    }

    // Modifier to ensure a loan is not already funded
    modifier notFunded(uint loanId) {
        require(!loans[loanId].isFunded, "Loan is already funded");
        _;
    }

    // Function to deposit collateral and request a loan
    function depositCollateralAndRequestLoan(uint _interestRate, uint _duration) external payable {
        require(msg.value > 0, "Collateral must be greater than 0");

        // Calculate the loan amount based on the collateralized amount (e.g., 50% of collateral)
        uint loanAmount = msg.value / 2;

        // Increment nextLoanId and create a new loan in the loans mapping
        loans[nextLoanId] = Loan({
            borrower: payable(msg.sender),
            lender: payable(address(0)),
            collateralAmount: msg.value,
            loanAmount: loanAmount,
            interestRate: _interestRate,
            dueDate: block.timestamp + _duration,
            isFunded: false,
            isRepaid: false
        });

        emit LoanRequested(nextLoanId, msg.sender, msg.value, loanAmount);
        nextLoanId++;
    }

    // Function to fund a loan
    function fundLoan(uint loanId) external payable loanExists(loanId) notFunded(loanId) {
        Loan storage loan = loans[loanId];
        require(msg.value == loan.loanAmount, "Incorrect loan amount sent");

        loan.lender = payable(msg.sender);
        loan.isFunded = true;

        // Transfer the loan amount to the borrower
        loan.borrower.transfer(msg.value);

        emit LoanFunded(loanId, msg.sender);
    }

    // Function to repay a loan
    function repayLoan(uint loanId) external payable loanExists(loanId) {
        Loan storage loan = loans[loanId];
        require(loan.isFunded, "Loan not funded");
        require(!loan.isRepaid, "Loan already repaid");
        require(msg.sender == loan.borrower, "Only the borrower can repay the loan");

        // Calculate the total repayment amount (loan amount + interest)
        uint repaymentAmount = loan.loanAmount + (loan.loanAmount * loan.interestRate / 100);
        require(msg.value == repaymentAmount, "Incorrect repayment amount");
        require(block.timestamp <= loan.dueDate, "Loan repayment period has expired");

        loan.isRepaid = true;

        // Transfer the repayment amount to the lender
        loan.lender.transfer(msg.value);

        // Return the collateral to the borrower
        loan.borrower.transfer(loan.collateralAmount);

        emit LoanRepaid(loanId);
    }

    // Function to claim collateral on default
    function claimCollateral(uint loanId) external loanExists(loanId) {
        Loan storage loan = loans[loanId];
        require(loan.isFunded, "Loan not funded");
        require(!loan.isRepaid, "Loan already repaid");
        require(block.timestamp > loan.dueDate, "Loan repayment period not yet expired");
        require(msg.sender == loan.lender, "Only the lender can claim the collateral");

        loan.isRepaid = true;

        // Transfer the collateral to the lender
        loan.lender.transfer(loan.collateralAmount);

        emit CollateralClaimed(loanId);
    }
}








// Test in the file X.js

// Importing necessary modules and functions from Hardhat and Chai for testing
const {
  loadFixture,
} = require("@nomicfoundation/hardhat-toolbox/network-helpers");
const { expect } = require("chai");
const { ethers } = require("hardhat");

describe("CollateralizedLoan", function () {
  // A fixture to deploy the contract before each test. This helps in reducing code repetition.
  
  async function deployCollateralizedLoanFixture() {
    // Get the ContractFactory and Signers here.
    const CollateralizedLoan = await ethers.getContractFactory("CollateralizedLoan");
    const [owner, borrower, lender] = await ethers.getSigners();


    // Deploy the contract
    const collateralizedLoan = await CollateralizedLoan.deploy();
    await collateralizedLoan.deployed();

    // Return the deployed contract and signers
    return { collateralizedLoan, owner, borrower, lender };
  }

  // Test suite for the loan request functionality
  describe("Loan Request", function () {
    it("Should let a borrower deposit collateral and request a loan", async function () {
      const { collateralizedLoan, borrower } = await loadFixture(deployCollateralizedLoanFixture);

      // Borrower deposits 2 ETH as collateral and requests a loan
      const collateralAmount = ethers.utils.parseEther("2");
      const interestRate = 10; // 10% interest
      const duration = 60 * 60 * 24 * 7; // 1 week duration

      await expect(collateralizedLoan.connect(borrower).depositCollateralAndRequestLoan(interestRate, duration, { value: collateralAmount }))
        .to.emit(collateralizedLoan, "LoanRequested")
        .withArgs(0, borrower.address, collateralAmount, collateralAmount.div(2));

      const loan = await collateralizedLoan.loans(0);
      expect(loan.borrower).to.equal(borrower.address);
      expect(loan.collateralAmount).to.equal(collateralAmount);
      expect(loan.loanAmount).to.equal(collateralAmount.div(2));
      expect(loan.interestRate).to.equal(interestRate);
    });
  });

  // Test suite for funding a loan
  describe("Funding a Loan", function () {
    it("Allows a lender to fund a requested loan", async function () {
      const { collateralizedLoan, borrower, lender } = await loadFixture(deployCollateralizedLoanFixture);

      // Borrower deposits collateral and requests a loan
      const collateralAmount = ethers.utils.parseEther("2");
      const loanAmount = collateralAmount.div(2);
      const interestRate = 10;
      const duration = 60 * 60 * 24 * 7;

      await collateralizedLoan.connect(borrower).depositCollateralAndRequestLoan(interestRate, duration, { value: collateralAmount });

      // Lender funds the loan
      await expect(collateralizedLoan.connect(lender).fundLoan(0, { value: loanAmount }))
        .to.emit(collateralizedLoan, "LoanFunded")
        .withArgs(0, lender.address);

      const loan = await collateralizedLoan.loans(0);
      expect(loan.lender).to.equal(lender.address);
      expect(loan.isFunded).to.be.true;
    });
  });

  // Test suite for repaying a loan
  describe("Repaying a Loan", function () {
    it("Enables the borrower to repay the loan fully", async function () {
      const { collateralizedLoan, borrower, lender } = await loadFixture(deployCollateralizedLoanFixture);

      // Borrower requests and lender funds the loan
      const collateralAmount = ethers.utils.parseEther("2");
      const loanAmount = collateralAmount.div(2);
      const interestRate = 10;
      const duration = 60 * 60 * 24 * 7;

      await collateralizedLoan.connect(borrower).depositCollateralAndRequestLoan(interestRate, duration, { value: collateralAmount });
      await collateralizedLoan.connect(lender).fundLoan(0, { value: loanAmount });

      // Borrower repays the loan
      const repaymentAmount = loanAmount.add(loanAmount.mul(interestRate).div(100)); // Loan amount + 10% interest
      await expect(collateralizedLoan.connect(borrower).repayLoan(0, { value: repaymentAmount }))
        .to.emit(collateralizedLoan, "LoanRepaid")
        .withArgs(0);

      const loan = await collateralizedLoan.loans(0);
      expect(loan.isRepaid).to.be.true;
    });
  });

  // Test suite for claiming collateral
  describe("Claiming Collateral", function () {
    it("Permits the lender to claim collateral if the loan isn't repaid on time", async function () {
      const { collateralizedLoan, borrower, lender } = await loadFixture(deployCollateralizedLoanFixture);

      // Borrower requests and lender funds the loan
      const collateralAmount = ethers.utils.parseEther("2");
      const loanAmount = collateralAmount.div(2);
      const interestRate = 10;
      const duration = 60 * 60 * 24 * 7; // 1 week

      await collateralizedLoan.connect(borrower).depositCollateralAndRequestLoan(interestRate, duration, { value: collateralAmount });
      await collateralizedLoan.connect(lender).fundLoan(0, { value: loanAmount });

      // Simulate time passing (e.g., 8 days)
      await ethers.provider.send("evm_increaseTime", [60 * 60 * 24 * 8]);
      await ethers.provider.send("evm_mine");

      // Lender claims collateral
      await expect(collateralizedLoan.connect(lender).claimCollateral(0))
        .to.emit(collateralizedLoan, "CollateralClaimed")
        .withArgs(0);

      const loan = await collateralizedLoan.loans(0);
      expect(loan.isRepaid).to.be.true;
    });
  });

  // Test suite for error handling
  describe("Error Handling", function () {
    it("Should revert when trying to fund a nonexistent loan", async function () {
      const { collateralizedLoan, lender } = await loadFixture(deployCollateralizedLoanFixture);

      // Attempting to fund a nonexistent loan (loanId 0 does not exist)
      await expect(collateralizedLoan.connect(lender).fundLoan(0, { value: ethers.utils.parseEther("1") }))
        .to.be.revertedWith("Loan does not exist");
    });

    it("Should revert when trying to repay a loan with an incorrect amount", async function () {
      const { collateralizedLoan, borrower, lender } = await loadFixture(deployCollateralizedLoanFixture);

      // Borrower requests and lender funds the loan
      const collateralAmount = ethers.utils.parseEther("2");
      const loanAmount = collateralAmount.div(2);
      const interestRate = 10;
      const duration = 60 * 60 * 24 * 7;

      await collateralizedLoan.connect(borrower).depositCollateralAndRequestLoan(interestRate, duration, { value: collateralAmount });
      await collateralizedLoan.connect(lender).fundLoan(0, { value: loanAmount });

      // Borrower tries to repay with an incorrect amount
      const incorrectRepaymentAmount = loanAmount; // Should include interest
      await expect(collateralizedLoan.connect(borrower).repayLoan(0, { value: incorrectRepaymentAmount }))
        .to.be.revertedWith("Incorrect repayment amount");
    });

    it("Should revert when trying to claim collateral prematurely", async function () {
      const { collateralizedLoan, borrower, lender } = await loadFixture(deployCollateralizedLoanFixture);

      // Borrower requests and lender funds the loan
      const collateralAmount = ethers.utils.parseEther("2");
      const loanAmount = collateralAmount.div(2);
      const interestRate = 10;
      const duration = 60 * 60 * 24 * 7;

      await collateralizedLoan.connect(borrower).depositCollateralAndRequestLoan(interestRate, duration, { value: collateralAmount });
      await collateralizedLoan.connect(lender).fundLoan(0, { value: loanAmount });

      // Attempt to claim collateral before due date
      await expect(collateralizedLoan.connect(lender).claimCollateral(0))
        .to.be.revertedWith("Loan repayment period not yet expired");
    });
  });
});
