JuMP
====

JuMP is a domain-specific modeling language for **[mathematical optimization]**
embedded in **[Julia]**. It currently supports a number of open-source and
commercial solvers ([Bonmin], [Cbc], [Clp], [Couenne], [CPLEX], [ECOS], [GLPK],
[Gurobi], [Ipopt], [KNITRO], [MOSEK], [NLopt], [SCS]) for a variety of problem classes, including
**[linear programming]**, **[(mixed) integer programming]**,
**[second-order conic programming]**, **[semidefinite programming]**, and **[nonlinear programming]**.

[mathematical optimization]: http://en.wikipedia.org/wiki/Mathematical_optimization
[Julia]: http://julialang.org/
[Bonmin]: https://projects.coin-or.org/Bonmin
[Couenne]: https://projects.coin-or.org/Couenne
[Clp]: https://projects.coin-or.org/Clp
[Cbc]: https://projects.coin-or.org/Cbc
[ECOS]: https://github.com/ifa-ethz/ecos
[GLPK]: http://www.gnu.org/software/glpk/
[Gurobi]: http://www.gurobi.com/
[MOSEK]: http://mosek.com/
[CPLEX]: http://www-01.ibm.com/software/commerce/optimization/cplex-optimizer/
[Ipopt]: https://projects.coin-or.org/Ipopt
[KNITRO]: http://www.ziena.com/knitro.htm
[NLopt]: http://ab-initio.mit.edu/wiki/index.php/NLopt
[SCS]: https://github.com/cvxgrp/scs
[linear programming]: http://en.wikipedia.org/wiki/Linear_programming
[(mixed) integer programming]: http://en.wikipedia.org/wiki/Integer_programming
[second-order conic programming]: http://en.wikipedia.org/wiki/Second-order_cone_programming
[semidefinite programming]: https://en.wikipedia.org/wiki/Semidefinite_programming
[nonlinear programming]: http://en.wikipedia.org/wiki/Nonlinear_programming

JuMP makes it easy to specify and **solve optimization problems without expert knowledge**, yet at the same time allows experts to implement advanced algorithmic techniques such as exploiting efficient hot-starts in linear programming or using callbacks to interact with branch-and-bound solvers. JuMP is also **fast** - benchmarking has shown that it can create problems at similar speeds to special-purpose commercial tools such as AMPL while maintaining the expressiveness of a generic high-level programming language. JuMP can be easily embedded in complex work flows including simulations and web servers.

Our documentation includes an installation guide, quick-start guide, and reference manual. The **[juliaopt-notebooks]** repository contains a small but growing collection of contributed examples. Submissions are welcome!

[juliaopt-notebooks]: https://github.com/JuliaOpt/juliaopt-notebooks

**Latest Release**: 0.14.2 (via ``Pkg.add``)
  * [Documentation](http://www.juliaopt.org/JuMP.jl/0.14/)
  * [Examples](https://github.com/JuliaOpt/JuMP.jl/tree/release-0.14/examples)
  * Testing status:
    * TravisCI: [![Build Status](https://travis-ci.org/JuliaOpt/JuMP.jl.svg?branch=release-0.14)](https://travis-ci.org/JuliaOpt/JuMP.jl)
    * PackageEvaluator:
      [![JuMP](http://pkg.julialang.org/badges/JuMP_0.4.svg)](http://pkg.julialang.org/?pkg=JuMP&ver=0.4)
      [![JuMP](http://pkg.julialang.org/badges/JuMP_0.5.svg)](http://pkg.julialang.org/?pkg=JuMP&ver=0.5)


**Development version**:
  * [Documentation](https://jump.readthedocs.io/en/latest)
  * [Examples](https://github.com/JuliaOpt/JuMP.jl/tree/master/examples)
  * Testing status:
    * TravisCI: [![Build Status](https://travis-ci.org/JuliaOpt/JuMP.jl.svg?branch=master)](https://travis-ci.org/JuliaOpt/JuMP.jl)
    * Test coverage:
      [![Coverage Status](https://coveralls.io/repos/JuliaOpt/JuMP.jl/badge.svg?branch=master)](https://coveralls.io/r/JuliaOpt/JuMP.jl?branch=master)
      [![codecov](https://codecov.io/gh/JuliaOpt/JuMP.jl/branch/master/graph/badge.svg)](https://codecov.io/gh/JuliaOpt/JuMP.jl)
  * Changes: see [NEWS](https://github.com/JuliaOpt/JuMP.jl/tree/master/NEWS.md)


## Installation

JuMP can be installed through the Julia package manager:

```julia
julia> Pkg.add("JuMP")
```

For full installation instructions, including how to install solvers, see the documentation linked above.


## Supported problem classes

Mathematical optimization encompasses a large variety of problem classes.
We list below what is currently supported. See the documentation for more information.

**Objective types**

* Linear
* Convex Quadratic
* Nonlinear (convex and nonconvex)

**Constraint types**

* Linear
* Convex Quadratic
* Second-order Conic
* Semidefinite
* Nonlinear (convex and nonconvex)

**Variable types**

* Continuous
* Integer-valued
* Semicontinuous
* Semi-integer


## Bug reports and support

Please report any issues via the Github **[issue tracker]**. All types of issues are welcome and encouraged; this includes bug reports, documentation typos, feature requests, etc. The **[julia-opt]** mailing list is appropriate for general discussion, including "how do I do this?" questions.

[issue tracker]: https://github.com/JuliaOpt/JuMP.jl/issues
[julia-opt]: https://groups.google.com/forum/#!forum/julia-opt


## Citing JuMP

If you find JuMP useful in your work, we kindly request that you cite the following [paper](http://arxiv.org/abs/1508.01982):

    @article{DunningHuchetteLubin2015,
    title = {{JuMP}: {A} modeling language for mathematical optimization},
    author = {Iain Dunning and Joey Huchette and Miles Lubin},
    journal = {arXiv:1508.01982 [math.OC]},
    year = {2015},
    url = {http://arxiv.org/abs/1508.01982}
    }

For an earlier work where we presented a prototype implementation of JuMP, see [here](http://dx.doi.org/10.1287/ijoc.2014.0623):

    @article{LubinDunningIJOC,
    author = {Miles Lubin and Iain Dunning},
    title = {Computing in Operations Research Using Julia},
    journal = {INFORMS Journal on Computing},
    volume = {27},
    number = {2},
    pages = {238-248},
    year = {2015},
    doi = {10.1287/ijoc.2014.0623},
    URL = {http://dx.doi.org/10.1287/ijoc.2014.0623}
    }

A preprint of this paper is freely available on [arXiv](http://arxiv.org/abs/1312.1431).
