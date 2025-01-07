# Project 2: Breakout Strategy
# Instructions
# Each problem consists of a function to implement and instructions 
# on how to implement the function. The parts of the function that need to 
# be implemented are marked with a # TODO comment. After implementing the function, 
# run the cell to test it against the unit tests we've provided. For each problem, we 
# provide one or more unit tests from our project_tests package. These unit tests won't 
# tell you if your answer is correct, but will warn you of any major errors. 
# Your code will be checked for the correct solution when you submit it to Udacity.

# Packages
# When you implement the functions, you'll only need to you use the packages you've 
# used in the classroom, like Pandas and Numpy. These packages will be imported for you. 
# We recommend you don't add any import statements, otherwise the grader might not be able to 
# run your code.

#The other packages that we're importing are helper, project_helper, and project_tests. 
#These are custom packages built to help you solve the problems. 
#The helper and project_helper module contains utility functions and graph functions. 
#The project_tests contains the unit tests for all the problems.
#



#
# The Alpha Research Process
# In this project you will code and evaluate a "breakout" signal. 
# It is important to understand where these steps fit in the alpha research workflow. 
# The signal-to-noise ratio in trading signals is very low and, as such, it is very easy 
# to fall into the trap of overfitting to noise. It is therefore inadvisable to jump right 
# into signal coding. To help mitigate overfitting, it is best to start with a general 
# observation and hypothesis; i.e., you should be able to answer the following question before 
#you touch any data: What feature of markets or investor behaviour would lead to a persistent 
# anomaly that my signal will try to use? Ideally the assumptions behind the hypothesis will 
# be testable before you actually code and evaluate the signal itself. The workflow therefore 
# is as follows: In this project, we assume that the first three steps area done 
# ("observe & research", "form hypothesis", "validate hypothesis"). 
# The hypothesis you'll be using for this project is the following: In the absence of news or 
# significant investor trading interest, stocks oscillate in a range. Traders seek to capitalize 
# on this range-bound behaviour periodically by selling/shorting at the top of the range and 
# buying/covering at the bottom of the range. This behaviour reinforces the existence of the range.
# When stocks break out of the range, due to, e.g., a significant news release or from market 
# pressure from a large investor: the liquidity traders who have been providing liquidity at the 
# bounds of the range seek to cover their positions to mitigate losses, thus magnifying the move 
# out of the range, and the move out of the range attracts other investor interest; these investors, 
#due to the behavioural bias of herding (e.g., Herd Behavior) build positions which favor continuation 
#of the trend. Using this hypothesis, let start coding..








import sys
!{sys.executable} -m pip install -r requirements.txt
!python -m pip install plotly==3.10.0 --no-cache

# Restart the Kernel
import plotly
print(plotly.__version__)
# Should return plotly==3.10.0

import pandas as pd
import numpy as np
import helper
import project_helper
import project_tests


# Market Data
# Load Data:
# While using real data will give you hands on experience, 
# it's doesn't cover all the topics we try to condense in one project. 
# We'll solve this by creating new stocks. We've create a scenario where companies 
# mining Terbium are making huge profits. All the companies in this sector of the 
# market are made up. They represent a sector with large growth that will be used 
# for demonstration latter in this project.


df_original = pd.read_csv('../../data/project_2/eod-quotemedia.csv', parse_dates=['date'], index_col=False)

# Add TB sector to the market
df = df_original
df = pd.concat([df] + project_helper.generate_tb_sector(df[df['ticker'] == 'AAPL']['date']), ignore_index=True)

close = df.reset_index().pivot(index='date', columns='ticker', values='adj_close')
high = df.reset_index().pivot(index='date', columns='ticker', values='adj_high')
low = df.reset_index().pivot(index='date', columns='ticker', values='adj_low')

print('Loaded Data')

# View Data
# To see what one of these 2-d matrices looks like, 
# let's take a look at the closing prices matrix.

close

# Stock Example
# Let's see what a single stock looks like from the closing prices. 
# For this example and future display examples in this project, 
# we'll use Apple's stock (AAPL). If we tried to graph all the stocks, it would be too much information.
apple_ticker = 'AAPL'
project_helper.plot_stock(close[apple_ticker], '{} Stock'.format(apple_ticker))




# 1. Compute the Highs and Lows in a Window
# You'll use the price highs and lows as an indicator for the breakout strategy. 
# In this section, implement get_high_lows_lookback to get the maximum high price and 
# minimum low price over a window of days. The variable lookback_days contains the number of 
# days to look in the past. Make sure this doesn't include the current day.

def get_high_lows_lookback(high, low, lookback_days):
    """
    Get the highs and lows in a lookback window.
    
    Parameters
    ----------
    high : DataFrame
        High price for each ticker and date
    low : DataFrame
        Low price for each ticker and date
    lookback_days : int
        The number of days to look back
    
    Returns
    -------
    lookback_high : DataFrame
        Lookback high price for each ticker and date
    lookback_low : DataFrame
        Lookback low price for each ticker and date
    """
    #TODO: Implement function
    lookback_high = high.shift(1).rolling(window=lookback_days).max()
    lookback_low = low.shift(1).rolling(window=lookback_days).min()

    return lookback_high, lookback_low

project_tests.test_get_high_lows_lookback(get_high_lows_lookback)

# EXPLANATIONS: 
	# 1. 	shift(1): This shifts the data by one day to exclude the current day’s values.
	# 2.	.rolling(window=lookback_days).max() and .rolling(window=lookback_days).min(): 
	# These apply a rolling window to calculate the maximum and minimum values over the lookback period.

# This function returns lookback_high and lookback_low, which contain the maximum high and minimum 
# low prices over the specified lookback period for each ticker and date.



# 2. Compute Long and Short Signals
# Using the generated indicator of highs and lows, create long and short signals using a breakout 
# strategy. Implement get_long_short to generate the following signals: -1 if Low > Close price, 
# 1 if High < Close price, or 0 otherwise. 

def get_long_short(close, lookback_high, lookback_low):
    """
    Generate the signals long, short, and do nothing.
    
    Parameters
    ----------
    close : DataFrame
        Close price for each ticker and date
    lookback_high : DataFrame
        Lookback high price for each ticker and date
    lookback_low : DataFrame
        Lookback low price for each ticker and date
    
    Returns
    -------
    long_short : DataFrame
        The long, short, and do nothing signals for each ticker and date
    """
    long_short = pd.DataFrame(0, index=close.index, columns=close.columns)
    
    # Generate short signal
    long_short[lookback_low > close] = -1
    
    # Generate long signal
    long_short[lookback_high < close] = 1
    
    return long_short


# Explanation

# 1.  We create a DataFrame long_short initialized to 0, representing no action.
# 2.  We apply conditions:
#   •   long_short[lookback_low > close] = -1 for short signals.
#   •   long_short[lookback_high < close] = 1 for long signals.
# This function returns the long_short DataFrame containing the trading 
# signals (1 for long, -1 for short, 0 for neutral).


# 3. Filter Signals
# That was a lot of repeated signals! If we're already shorting a stock, having an additional signal to short a stock isn't helpful for this strategy. This also applies to additional long signals when the last signal was long.
# Implement filter_signals to filter out repeated long or short signals within the lookahead_days. If the previous signal was the same, change the signal to 0 (do nothing signal). For example, say you have a single stock time series that is
# [1, 0, 1, 0, 1, 0, -1, -1]
# Running filter_signals with a lookahead of 3 days should turn those signals into
# [1, 0, 0, 0, 1, 0, -1, 0]
# To help you implement the function, we have provided you with the clear_signals function. This will remove all signals within a window after the last signal. For example, say you're using a windows size of 3 with clear_signals. It would turn the Series of long signals
# [0, 1, 0, 0, 1, 1, 0, 1, 0] into [0, 1, 0, 0, 0, 1, 0, 0, 0]
# clear_signals only takes a Series of the same type of signals, where 1 is the signal and 0 is no signal. It can't take a mix of long and short signals. Using this function, implement filter_signals.
# For implementing filter_signals, we don't reccommend you try to find a vectorized solution. Instead, you should use the iterrows over each column.

def clear_signals(signals, window_size):
    """
    Clear out signals in a Series of just long or short signals.
    
    Remove the number of signals down to 1 within the window size time period.
    
    Parameters
    ----------
    signals : Pandas Series
        The long, short, or do nothing signals
    window_size : int
        The number of days to have a single signal       
    
    Returns
    -------
    signals : Pandas Series
        Signals with the signals removed from the window size
    """
    # Start with buffer of window size
    # This handles the edge case of calculating past_signal in the beginning
    clean_signals = [0]*window_size
    
    for signal_i, current_signal in enumerate(signals):
        # Check if there was a signal in the past window_size of days
        has_past_signal = bool(sum(clean_signals[signal_i:signal_i+window_size]))
        # Use the current signal if there's no past signal, else 0/False
        clean_signals.append(not has_past_signal and current_signal)
        
    # Remove buffer
    clean_signals = clean_signals[window_size:]

    # Return the signals as a Series of Ints
    return pd.Series(np.array(clean_signals).astype(np.int), signals.index)


def filter_signals(signal, lookahead_days):
    """
    Filter out signals in a DataFrame.
    
    Parameters
    ----------
    signal : DataFrame
        The long, short, and do nothing signals for each ticker and date
    lookahead_days : int
        The number of days to look ahead
    
    Returns
    -------
    filtered_signal : DataFrame
        The filtered long, short, and do nothing signals for each ticker and date
    """
    # Initialize the filtered signal DataFrame with zeros (neutral signals)
    filtered_signal = pd.DataFrame(0, index=signal.index, columns=signal.columns)

    for ticker in signal.columns:
        # Extract the signals for the current ticker
        ticker_signals = signal[ticker]

        # Separate the long and short signals
        long_signals = ticker_signals.where(ticker_signals == 1, 0)
        short_signals = ticker_signals.where(ticker_signals == -1, 0)

        # Clear repeated signals within the lookahead window
        cleared_long_signals = clear_signals(long_signals, lookahead_days)
        cleared_short_signals = clear_signals(short_signals, lookahead_days)

        # Combine the cleared long and short signals back into one series
        filtered_signal[ticker] = cleared_long_signals + cleared_short_signals

    return filtered_signal



# Explanation
#   1.  Initialize filtered_signal: Create a DataFrame of zeros with the same shape as signal, which will hold the filtered signals.
#   2.  Loop over each ticker (column): For each column in signal, we:
#       •   Separate long and short signals using .where(), assigning 0 to any non-matching values.
#       •   Use clear_signals on both long and short signals to filter out repeated signals within the lookahead_days window.
#   3.  Combine and store: Add the cleared long and short signals back into filtered_signal for each ticker.
# This implementation will ensure that only the first occurrence of a long or short signal within each lookahead window is retained.


# 4. Lookahead Close Prices
# With the trading signal done, we can start working on evaluating how many days to short or long the stocks. In this problem, implement get_lookahead_prices to get the close price days ahead in time. You can get the number of days from the variable lookahead_days. We'll use the lookahead prices to calculate future returns in another problem.

def get_lookahead_prices(close, lookahead_days):
    """
    Get the lookahead prices for `lookahead_days` number of days.
    
    Parameters
    ----------
    close : DataFrame
        Close price for each ticker and date
    lookahead_days : int
        The number of days to look ahead
    
    Returns
    -------
    lookahead_prices : DataFrame
        The lookahead prices for each ticker and date
    """
    lookahead_prices = close.shift(-lookahead_days)
    
    return lookahead_prices

# Explanation
#   •   Shift the Close Prices: By shifting the close DataFrame forward by lookahead_days using .shift(-lookahead_days), each date’s close price is replaced with the price lookahead_days days into the future.
#   •   Return lookahead_prices: The resulting DataFrame will have NaN values for the last lookahead_days rows, as they don’t have enough data to look that far ahead.

# This function provides the lookahead prices, which can then be used to calculate returns for the trading signals.



# 5. Lookahead Price Returns
# Implement get_return_lookahead to generate the log price return between the closing price and the lookahead price.

def get_return_lookahead(close, lookahead_prices):
    """
    Calculate the log returns from the lookahead days to the signal day.
    
    Parameters
    ----------
    close : DataFrame
        Close price for each ticker and date
    lookahead_prices : DataFrame
        The lookahead prices for each ticker and date
    
    Returns
    -------
    lookahead_returns : DataFrame
        The lookahead log returns for each ticker and date
    """
    lookahead_returns = np.log(lookahead_prices / close)
    
    return lookahead_returns

# Explanation
#   1.  Calculate Log Returns: Using np.log(lookahead_prices / close), we compute the log returns for each ticker and date.
#   2.  Return the Results: The resulting lookahead_returns DataFrame contains the log returns between each day’s close price and the corresponding lookahead price.

# This function will provide the log returns, which can be used to evaluate the effectiveness of the trading signals over the specified lookahead period.


# 6. Compute the Signal Return: Using the price returns generate the signal returns.

def get_signal_return(signal, lookahead_returns):
    """
    Compute the signal returns.
    
    Parameters
    ----------
    signal : DataFrame
        The long, short, and do nothing signals for each ticker and date
    lookahead_returns : DataFrame
        The lookahead log returns for each ticker and date
    
    Returns
    -------
    signal_return : DataFrame
        Signal returns for each ticker and date
    """
    signal_return = signal * lookahead_returns
    
    return signal_return


# Explanation
#   1.  Element-wise Multiplication: signal * lookahead_returns multiplies each element in the signal DataFrame with the corresponding element in the lookahead_returns DataFrame. This approach:
#       •   Retains the return for long signals (1).
#       •   Inverts the return for short signals (-1).
#       •   Nullifies the return for do-nothing signals (0).
#   2.  Return signal_return: The result is a DataFrame of signal returns, indicating the profit or loss associated with each trading signal.



# 7. Kolmogorov-Smirnov Test: While you can see the outliers in the histogram, we need to find the stocks that are causing these outlying returns. We'll use the Kolmogorov-Smirnov Test or KS-Test. This test will be applied to teach ticker's signal returns where a long or short signal exits.
# Filter out returns that don't have a long or short signal.
long_short_signal_returns_5 = signal_return_5[signal_5 != 0].stack()
long_short_signal_returns_10 = signal_return_10[signal_10 != 0].stack()
long_short_signal_returns_20 = signal_return_20[signal_20 != 0].stack()

# Get just ticker and signal return
long_short_signal_returns_5 = long_short_signal_returns_5.reset_index().iloc[:, [1,2]]
long_short_signal_returns_5.columns = ['ticker', 'signal_return']
long_short_signal_returns_10 = long_short_signal_returns_10.reset_index().iloc[:, [1,2]]
long_short_signal_returns_10.columns = ['ticker', 'signal_return']
long_short_signal_returns_20 = long_short_signal_returns_20.reset_index().iloc[:, [1,2]]
long_short_signal_returns_20.columns = ['ticker', 'signal_return']

# View some of the data
long_short_signal_returns_5.head(10)


# This gives you the data to use in the KS-Test.
# Now it's time to implement the function calculate_kstest to use Kolmogorov-Smirnov test (KS test) between a distribution of stock returns (the input dataframe in this case) and each stock's signal returns. Run KS test on a normal distribution against each stock's signal returns. Use scipy.stats.kstest perform the KS test. When calculating the standard deviation of the signal returns, make sure to set the delta degrees of freedom to 0.
# For this function, we don't reccommend you try to find a vectorized solution. Instead, you should iterate over the groupby function.

from scipy.stats import kstest


def calculate_kstest(long_short_signal_returns):
    """
    Calculate the KS-Test against the signal returns with a long or short signal.
    
    Parameters
    ----------
    long_short_signal_returns : DataFrame
        The signal returns which have a signal.
        This DataFrame contains two columns, "ticker" and "signal_return"
    
    Returns
    -------
    ks_values : Pandas Series
        KS static for all the tickers
    p_values : Pandas Series
        P value for all the tickers
    """
    # Calculate the overall mean and standard deviation of the signal returns
    overall_mean = long_short_signal_returns['signal_return'].mean()
    overall_std = long_short_signal_returns['signal_return'].std(ddof=0)

    # Initialize dictionaries to store the results
    ks_values = {}
    p_values = {}

    # Iterate over each ticker group
    for ticker, group in long_short_signal_returns.groupby('ticker'):
        # Run the KS test for this ticker's signal returns against the normal distribution
        ks_stat, p_value = kstest(group['signal_return'], 'norm', args=(overall_mean, overall_std))
        
        # Store the results
        ks_values[ticker] = ks_stat
        p_values[ticker] = p_value

    # Convert the results to Pandas Series
    ks_values = pd.Series(ks_values)
    p_values = pd.Series(p_values)

    return ks_values, p_values


# Explanation
#   1.  Compute Overall Parameters: overall_mean and overall_std represent the parameters of the normal distribution we’re testing against.
#   2.  Group by Ticker: We use groupby('ticker') to iterate over each stock’s signal returns.
#   3.  KS Test with kstest: For each stock’s returns, kstest compares the distribution to a normal distribution with the mean and standard deviation we calculated.
#   4.  Store Results: We store the KS statistic and p-value in dictionaries, which are then converted to Pandas Series and returned.
#   This function provides the KS statistic and p-value for each stock, allowing us to assess how closely each stock’s signal returns follow a normal distribution.


# 8. Find Outliers
# With the ks and p values calculate, let's find which symbols are the outliers. Implement the find_outliers function to find the following outliers:
# Symbols that pass the null hypothesis with a p-value less than pvalue_threshold AND with a KS value above ks_threshold.
# Note: your function should return symbols that meet both requirements above.

def find_outliers(ks_values, p_values, ks_threshold, pvalue_threshold=0.05):
    """
    Find outlying symbols using KS values and P-values
    
    Parameters
    ----------
    ks_values : Pandas Series
        KS static for all the tickers
    p_values : Pandas Series
        P value for all the tickers
    ks_threshold : float
        The threshold for the KS statistic
    pvalue_threshold : float
        The threshold for the p-value
    
    Returns
    -------
    outliers : set of str
        Symbols that are outliers
    """
    outliers = set(
        ks_values[(ks_values > ks_threshold) & (p_values < pvalue_threshold)].index
    )
    
    return outliers








