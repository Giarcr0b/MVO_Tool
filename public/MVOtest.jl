 using JuPOT

             # Collect data from ARGS array
             data = float(split(ARGS[1], ","))
             returns = round(float(split(ARGS[2], ",")),3)
             tickers = split(ARGS[3], ",")
             target_return = float(ARGS[4])

             # Calculate number of stocks and days from data
             stocks = length(tickers)
             days = Int(length(data)/stocks)

             # Form data into matrix
             matrix = reshape(data,days,stocks)

             # Produce covariance matrix
             covariance = cov(matrix)

             # Assets data structure containing, tickers, expected returns and covarariance
             assets = AssetsCollection(tickers, returns, covariance)

             # Create simple MVO object using assets and target_return
             mvo = SimpleMVO(assets, target_return; short_sale=false)

             # Optimise MVO object and print result to file
             outfile = "output.txt"
                          f = open(outfile, "w")
                          println(f, optimize(mvo))
                          close(f)


             # No. Of Assets
             # n = 3
             # No. of days data
             # m = 6
             # d = [0.5,0.7,0.3,0.2,0.56,0.26,0.2,0.4,0.6,0.2,0.15,0.58,0.8,0.3,0.9,0.2,0.51,0.15]
             # Returns a matrix of size(n) with entries between 0-1s
             # returns =  [0.5,0.4,0.6]
             # matrix = reshape(d,m,n)
             #covariance matrix of returns
             # covariance = cov(matrix)
             # List of asset names
             # tickers = [randstring(3) for i in 1:n]

             # Assets data structure containing, names, expected returns, covarariance
             # assets = AssetsCollection(tickers, returns, covariance)

             # target_return = 0.2
             # mvo = SimpleMVO(assets, target_return; short_sale=false)

             # println(optimize(mvo))

