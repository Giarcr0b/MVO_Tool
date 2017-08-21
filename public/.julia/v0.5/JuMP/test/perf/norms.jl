using JuMP

function norm_stress1(N)
    m = Model()
    @variable(m, x[1:N])
    for i in 1:N
        @constraint(m, norm2{x[j],j=1:i} <= i)
    end
    for i in 1:N
        @constraint(m, norm2{(i/j)*x[j],j=1:i} <= i)
    end
    for i in 1:N
        @constraint(m, norm2{(i/j)*x[j],j=1:i} + sum{x[j],j=1:N} <= i)
    end
end

# Warmup
norm_stress1(10)

@time for iter in 1:10
    norm_stress1(100)
end
