

import pandas as pd
import numpy as np
import scipy.stats as stats



def analyze_returns(net_returns):
    """
    Perform a t-test, with the null hypothesis being that the mean return is zero.
    
    Parameters
    ----------
    net_returns : Pandas Series
        A Pandas Series for each date
    
    Returns
    -------
    t_value
        t-statistic from t-test
    p_value
        Corresponding p-value
    """
    # TODO: Perform one-tailed t-test on net_returns
    # Hint: You can use stats.ttest_1samp() to perform the test.
    #       However, this performs a two-tailed t-test.
    #       You'll need to divde the p-value by 2 to get the results of a one-tailed p-value.
    
    print(type(net_returns))
    mean = net_returns.mean(numeric_only = True)

    std_dev = net_returns['return'].std()

    n = len(net_returns)
    standard_error = std_dev / (n ** 0.5)


    # Perform the t-test
    t_statistic, p_value = stats.ttest_1samp(net_returns['return'], 0)
    p_value = p_value/2
    
    return t_statistic, p_value



def test_run(filename='net_returns.csv'):
    """Test run analyze_returns() with net strategy returns from a file."""
    net_returns = pd.read_csv(filename, header=0)

    t, p = analyze_returns(net_returns)
    
    print("t-statistic: {:.3f}\np-value: {:.6f}".format(t, p))


if __name__ == '__main__':
    test_run()




