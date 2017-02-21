 using JuPOT

n = 10 # No. Of Assets
returns = rand(n) # Returns a matrix of size(n) with entries between 0-1s
covariance = let # This part generates a covariance matrix for the returns
        S = randn(n, n)
        S'S + eye(n)
end

tickers = [randstring(3) for i in 1:n] # List of asset names

# Assets data structure containing, names, expected returns, covarariance
assets = AssetsCollection(tickers, returns, covariance)

target_return = 0.2
mvo = SimpleMVO(assets, target_return; short_sale=false)

optimize(mvo)

