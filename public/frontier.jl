using JuPOT


             m = 6 # No. of days data
             data = ARGS[1]
             returns = split(data, ",")

             meanReturns =  ARGS[2] # Returns a matrix of size(n) with entries between 0-1s
             d = split(meanReturns, ",")

             stocks = ARGS[3]
             tickers = split(stocks, ",")

             n = length(tickers)

             matrix = reshape(d,m,n)
             covariance = cov(matrix) #covariance matrix of returns



             # Assets data structure containing, names, expected returns, covarariance
             assets = AssetsCollection(tickers, returns, covariance)

             target_ret_test = [0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80]

             function efficientFrontierMVO(assets, target_ret_test)

                 # Create the Arrays to be returned, and set them to be the length of the
                 # target_ret_test from the input.
                 n = length(target_ret_test)
                 risk = Array(Float64,n)
                 index = Array(Float64,n)

                 for i in 1:n
                     # Get the target return we want to test.
                     target_ret = target_ret_test[i]

                     # Setup and Optimize the SimpleMVO with the new Target Return.
                     mvo = SimpleMVO(assets, target_ret; short_sale=false)
                     result = optimize(mvo)

                     # Risk is the Objective Value. Index the Target Return.
                     risk[i] = result[1]
                     index[i] = target_ret
                 end

                 # Return as a Tuple of the Arrays
                 return risk, index
             end

             efd = efficientFrontierMVO(assets, target_ret_test)