 using JuPOT

             n = 3 # No. Of Assets
             m = 6 # No. of days data
             d = [0.5,0.7,0.3,0.2,0.56,0.26,0.2,0.4,0.6,0.2,0.15,0.58,0.8,0.3,0.9,0.2,0.51,0.15]
             returns =  [0.5,0.4,0.6] # Returns a matrix of size(n) with entries between 0-1s
             matrix = reshape(d,m,n)
             covariance = cov(matrix) #covariance matrix of returns

             tickers = [randstring(3) for i in 1:n] # List of asset names

             # Assets data structure containing, names, expected returns, covarariance
             assets = AssetsCollection(tickers, returns, covariance)

             target_return = 0.2
             mvo = SimpleMVO(assets, target_return; short_sale=false)

             optimize(mvo)

