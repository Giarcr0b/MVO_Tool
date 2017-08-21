using JuPOT

name = ARGS[1]
age = ARGS[2]
cats = ARGS[3]

message = "Hello after still working " * name * " you are " * age * " and own " * cats * " cats!!"

outfile = "output.txt"
f = open(outfile, "w")
println(f, message)
close(f)
