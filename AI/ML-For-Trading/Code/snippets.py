# This file contains all code tasks I did so far:




# Read CSV:

import pandas as pd


def test_run():
    """Function called by Test Run."""
    df = pd.read_csv("data/AAPL.csv")
    
    # TODO: Print last 5 rows of the data frame
    # The head() method retrieves the first 5 rows by default, while 
    # the tail() method retrieves the last 5 rows.
    print(df.tail())
    
    

############################################

"""Compute mean volume"""

import pandas as pd

def get_mean_volume(symbol):
    """Return the mean volume for stock indicated by symbol.
    
    Note: Data for a stock is stored in file: data/<symbol>.csv
    """
    df = pd.read_csv("data/{}.csv".format(symbol))  # read in data
    # TODO: Compute and return the mean volume for this stock
    return df['Volume'].mean()

def test_run():
    """Function called by Test Run."""
    for symbol in ['AAPL', 'IBM']:
        print "Mean Volume"
        print symbol, get_mean_volume(symbol)

############################################

"""Plot High prices for IBM"""

import pandas as pd
import matplotlib.pyplot as plt

def test_run():
    df = pd.read_csv("data/IBM.csv")
    # TODO: Your code here
    plt.plot(df['High'], label='High Prices', color='blue')  # Plot the High prices
    
    # Adding title and labels
    plt.title('High Prices for IBM')
    plt.xlabel('Days')  # You can change this to a more meaningful label if you have a date column
    plt.ylabel('Price (USD)')
    plt.legend()  # Show legend
    
    plt.show()  # must be called to show plots

############################################

import pandas as pd

def test_run():
	start_date = '2010-01-22'
	end_date = '2010-01-26'
	dates = pd.date_range(start_date, end_date)

	df1 = pd.DataFrame(index=dates)

	dfSPY = pd.read_csv("data/SPY.csv", index_col = "Date", parse_dates = True, usecols = ['Date', 'Adj Close'], na_values = ['nan'])

	dfSPY = dfSPY.rename(columns={'Adj Close' : 'SPY'})

	df1 = df1.join(dfSPY, how = 'inner')
	#df1 = df1.dropna()
	print 


	symbols = ['GOOG', 'IBM', 'GLD']
	for symbol in symbols:
		df_temp = pd.read_csv("data/{}.csv".format(symbol), index_col = "Date", parse_dates = True, usecols = ['Date', 'Adj Close'], na_values = ['nan'])
		df_temp = df_temp.rename(columns = {'Adj Close' : symbol})
		df = df1.join(df_temp)


############################################

"""Utility functions"""

import os
import pandas as pd

def symbol_to_path(symbol, base_dir="data"):
    """Return CSV file path given ticker symbol."""
    return os.path.join(base_dir, "{}.csv".format(str(symbol)))


def get_data(symbols, dates):
    """Read stock data (adjusted close) for given symbols from CSV files."""
    df = pd.DataFrame(index=dates)
    if 'SPY' not in symbols:  # add SPY for reference, if absent
        symbols.insert(0, 'SPY')

    for symbol in symbols:
        # TODO: Read and join data for each symbol
        df_temp = pd.read_csv("data/{}.csv".format(symbol), index_col = "Date", parse_dates = True, usecols = ['Date', 'Adj Close'], na_values = ['nan'])
        df_temp = df_temp.rename(columns = {'Adj Close' : symbol})
        df = df.join(df_temp)
        df = df.dropna()
        print(df)


    return df


def test_run():
    # Define a date range
    dates = pd.date_range('2010-01-22', '2010-01-26')

    # Choose stock symbols to read
    symbols = ['GOOG', 'IBM', 'GLD']
    
    # Get stock data
    df = get_data(symbols, dates)
    print df

##########################################
# Compute slicing:

    dates = pd.date_range('2010-01-01', '2010-12-31')
    symbols = ['GOOG', 'IBM', 'GLD']

    # Get stock data
    df = get_data(symbols, dates)

    #1. row slicing using DataFrame.ix 
    print df.ix['2010-01-01' : '2010-01-31']

    #2. column slicing using 
    print df['GOOG']
    print df['GOOG', 'IBM']

    #3. rows and columns:
    print df.ix['2010-01-01' : '2010-01-31', ['GOOG', 'IBM']]

##########################################

# Plot data function
def plot_data(df, title = "Stock Prices")

    ax = df.plot(title = title, fontsize=2)
    ax.set_xlable("Date")
    ax.set_ylable("Price")
    plt.show()


def plot_selected(df, columns, start_index, end_index):
    """Plot the desired columns over index values in the given range."""
    # TODO: Your code here
    # Note: DO NOT modify anything else!
    # Select the specified columns and the desired index range
    df_selected = df.loc[start_index:end_index, columns]
    
    # Plot the selected data
    df_selected.plot()
    
    # Show the plot
    plt.show()

##########################################

# Normalize data:

def normalize_data(df)

    
    return df/df.ix[0, :]


if __name__ == "__main__":
    test_run()














