using JuPOT


            # data = ARGS[1]
             d = float(split(ARGS[1], ","))

             meanReturns =  ARGS[2] # Returns a matrix of size(n) with entries between 0-1s
             returns = round(float(split(meanReturns, ",")),3)

             stocks = ARGS[3]
             tickers = split(stocks, ",")

             m = 10
             n = length(tickers)

             matrix = reshape(d,m,n)
             covariance = cov(matrix) #covariance matrix of returns



             # Assets data structure containing, names, expected returns, covarariance
             assets = AssetsCollection(tickers, returns, covariance)
             if minimum(returns) < 0
             min = 0
             else
             min = minimum(returns)
             end
             max = maximum(returns)

             target_ret_test = collect(min:(max-min)/10:max)

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
                     index[i] = round(target_ret,3)
                 end

                 # Convert arrays to strings
               risk_string = ""
              index_string = ""

              for j in 1:length(risk)
                if j < length(risk)
                    risk_string = risk_string * string(risk[j]) * ","
                    else
                    risk_string = risk_string * string(risk[j])
                end
              end

              for k in 1:length(index)
                if k < length(index)
                    index_string = index_string * string(index[k]) * ","
                    else
                    index_string = index_string * string(index[k])
                end
              end

                 # Return as a Tuple of the Arrays
                 text = risk_string * "\n" * index_string
                  return text
             end

             efd = efficientFrontierMVO(assets, target_ret_test)

             outfile = "output.txt"
             f = open(outfile, "w")
             println(f, efd)
             close(f)