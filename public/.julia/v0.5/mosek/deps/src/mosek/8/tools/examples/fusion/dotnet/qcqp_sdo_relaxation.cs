using System;

using mosek.fusion;
using mosek;

namespace mosek
{
  namespace fusion
  {
    namespace example
    {
      public class qcqp_sdo_relaxation
      {      
        public static void Main(string[] args)
        {       
          //TAG:begin-input-data
          // problem dimensions
          int n = 50;
          int m= 2*n;

          Random rnd = new Random();

          // problem data
          double []A  = new double[m*n];
          double []xs = new double[n];

          for(int j=0;j<n;j++)
          {
            for(int i=0;i<m;i++)
            {
              double u1 = rnd.NextDouble(); //these are uniform(0,1) random doubles
              double u2 = rnd.NextDouble();
              A[i*n+j]= Math.Sqrt(-2.0 * Math.Log(u1)) * Math.Sin(2.0 * Math.PI * u2);
     
            }
            xs[j]= rnd.NextDouble();
          }
      
          double [] P = new double[n*n];
          double [] q = new double[n];

          //P = A^T A
          LinAlg.syrk(
            mosek.uplo.lo,
            mosek.transpose.no,
            n,m,1.0, A, 0.0, P);

          //must fill P upper triangular
          for(int j=0;j<n;j++)
            for(int i=j+1;i<n;i++)
              P[j*n+i] = P[i*n+j];
      
          // q = -P xs
          LinAlg.gemv(  
            mosek.transpose.no,  
            n, n,  
            -1.0,  
            P,  
            xs,  
            0.0,  
            q);
          solve(n,P,q);
        }


      static void solve(int n, double[] P, double[] q)
      {
        using (Model M = new Model())           
        {
          Variable Z = M.Variable(n+1, Domain.InPSDCone());
      
          Variable X= Z.Slice(new int[]{0,0},new int[]{n,n});
          Variable x= Z.Slice(new int[]{0,n},new int[]{n,n+1});
          M.Constraint( Expr.Sub(X.Diag(),x), Domain.GreaterThan(0.0) );
      
          M.Constraint( Z.Index(n,n), Domain.EqualsTo(1.0));
          Expression two_xq = Expr.Mul(2.0, Expr.Dot( x, q) );
          Expression trPX = Expr.Sum(Expr.MulElm( Matrix.Dense(n,n,P), X ));
          M.Objective( ObjectiveSense.Minimize, Expr.Add( trPX , two_xq ) );
          Console.Write("solution status= %s\n",M.GetPrimalSolutionStatus());
          
          M.Solve();
        }
      }
    }

  }
}
}
