#ifndef __FUSION_P_H__
#define __FUSION_P_H__
#include "monty.h"
#include "mosektask_p.h"
#include "list"
#include "vector"
#include "unordered_map"
#include "fusion.h"
namespace mosek
{
namespace fusion
{
// mosek.fusion.BaseModel from file 'src/fusion/cxx/BaseModel_p.h'
// namespace mosek::fusion
struct p_BaseModel
{
  p_BaseModel(BaseModel * _pubthis);

  void _initialize( monty::rc_ptr<BaseModel> m);
  void _initialize( const std::string & name,
                    const std::string & licpath);

  virtual ~p_BaseModel() { /* std::cout << "~p_BaseModel()" << std::endl;*/  }

  static p_BaseModel * _get_impl(Model * _inst) { return _inst->_impl; }

  //----------------------

  bool synched;
  std::string taskname;

  monty::rc_ptr<SolutionStruct> sol_itr;
  monty::rc_ptr<SolutionStruct> sol_itg;
  monty::rc_ptr<SolutionStruct> sol_bas;

  //---------------------

  std::unique_ptr<Task> task;

  //---------------------
  void task_setLogHandler (const msghandler_t & handler);
  void task_setCallbackHandler (const datacbhandler_t & handler);

  int alloc_rangedvar(const std::string & name, double lb, double ub);
  int alloc_linearvar(const std::string & name, mosek::fusion::RelationKey relkey, double bound);
  int task_append_barvar(int size, int num);

  void task_var_name   (int index, const std::string & name);
  void task_con_name   (int index, const std::string & name);
  void task_cone_name  (int index, const std::string & name);
  void task_barvar_name(int index, const std::string & name);
  void task_objectivename(         const std::string & name);

  void task_break_solve();

  //--------------------------

  int task_numvar();
  int task_numcon();
  int task_numcone();
  int task_numbarvar();

  //--------------------------

  void task_put_param(const std::string & name, const std::string & value);
  void task_put_param(const std::string & name, int    value);
  void task_put_param(const std::string & name, double value);
  
  double    task_get_dinf (const std::string & name);
  int       task_get_iinf (const std::string & name);
  long long task_get_liinf(const std::string & name);
  
  //--------------------------
  void task_con_putboundslice_fr(int first, int last); 
  void task_con_putboundslice_lo(int first, int last, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_con_putboundslice_up(int first, int last, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_con_putboundslice_ra(int first, int last, const std::shared_ptr<monty::ndarray<double,1>> & lb , 
                                                      const std::shared_ptr<monty::ndarray<double,1>> & ub );
  void task_con_putboundslice_fx(int first, int last, const std::shared_ptr<monty::ndarray<double,1>> & rhs);

  void task_con_putboundlist_lo(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_con_putboundlist_up(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_con_putboundlist_fx(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_con_putboundlist_ra(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & lb , 
                                                            const std::shared_ptr<monty::ndarray<double,1>> & ub );
  void task_var_putboundslice_fr(int first, int last);
  void task_var_putboundslice_lo(int first, int last, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_var_putboundslice_up(int first, int last, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_var_putboundslice_ra(int first, int last, const std::shared_ptr<monty::ndarray<double,1>> & lb, 
                                                      const std::shared_ptr<monty::ndarray<double,1>> & ub);
  void task_var_putboundslice_fx(int first, int last, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_var_putintlist(const std::shared_ptr<monty::ndarray<int,1>> & idxs);
  void task_var_putcontlist(const std::shared_ptr<monty::ndarray<int,1>> & idxs); 
 
  //--------------------------

  int  task_append_barmatrix
    ( int dim, 
      const std::shared_ptr<monty::ndarray<int,1>>    & subi, 
      const std::shared_ptr<monty::ndarray<int,1>>    & subj, 
      const std::shared_ptr<monty::ndarray<double,1>> & cof);
  int  task_barvar_dim(int j);
  void task_putbaraij (int i, int j, int k);
  void task_putbaraij (int i, int j, const std::shared_ptr<monty::ndarray<int,1>> & k);
  void task_putbarcj  (int j, int k);
  void task_putbarcj  (int j,        const std::shared_ptr<monty::ndarray<int,1>> & k);
  int  task_barvardim (int index);

  int task_append_var(int num);
  int task_append_con(int num);
  int task_append_quadcone (int conesize, int first, int num, int d0, int  d1);
  int task_append_rquadcone(int conesize, int first, int num, int d0, int  d1);

  void task_putarowslice(
    int first, 
    int last, 
    const std::shared_ptr<monty::ndarray<long long,1>> & ptrb, 
    const std::shared_ptr<monty::ndarray<int,1>>       & subj, 
    const std::shared_ptr<monty::ndarray<double,1>>    & cof);
  void task_putaijlist(
    const std::shared_ptr<monty::ndarray<int,1>>       & subi, 
    const std::shared_ptr<monty::ndarray<int,1>>       & subj, 
    const std::shared_ptr<monty::ndarray<double,1>>    & cof, 
    long long                           num);

  void task_setnumvar(int num);
  void task_cleanup(int oldnum, int oldnumcon, int oldnumcone, int oldnumbarvar);
  void task_solve();

  void task_putobjective( 
    bool                             maximize,
    const std::shared_ptr<monty::ndarray<int,1>>    & subj    ,
    const std::shared_ptr<monty::ndarray<double,1>> & cof     ,
    double                           cfix    );

  void task_putobjectivename(const std::string & name);

  void task_write(const std::string & filename);
  void task_dump (const std::string & filename);

  MSKtask_t task_get();
  void dispose();

  void task_putxx_slice(SolutionType which, int first, int last, std::shared_ptr<monty::ndarray<double,1>> & xx);

  static void env_syeig (int n, std::shared_ptr<monty::ndarray<double,1>> & a, std::shared_ptr<monty::ndarray<double,1>> & w);
  static void env_potrf (int n, std::shared_ptr<monty::ndarray<double,1>> & a);                        
  static void env_syevd (int n, std::shared_ptr<monty::ndarray<double,1>> & a, std::shared_ptr<monty::ndarray<double,1>> & w);

  static void env_putlicensecode(std::shared_ptr<monty::ndarray<int,1>> code);
  static void env_putlicensepath(const std::string &licfile);
  static void env_putlicensewait(int wait);

  void convertSolutionStatus(MSKsoltypee soltype, p_SolutionStruct * sol, MSKsolstae status, MSKprostae prosta);


};

// End of file 'src/fusion/cxx/BaseModel_p.h'
struct p_Model : public ::mosek::fusion::p_BaseModel
{
Model * _pubthis;
static mosek::fusion::p_Model* _get_impl(mosek::fusion::Model * _inst){ return static_cast< mosek::fusion::p_Model* >(mosek::fusion::p_BaseModel::_get_impl(_inst)); }
static mosek::fusion::p_Model * _get_impl(mosek::fusion::Model::t _inst) { return _get_impl(_inst.get()); }
p_Model(Model * _pubthis);
virtual ~p_Model() { /* std::cout << "~p_Model" << std::endl;*/ };
int task_vars_used{};int task_vars_allocated{};monty::rc_ptr< ::mosek::fusion::Utils::StringIntMap > con_map{};int cons_used{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::ModelConstraint >,1 > > cons{};int vars_used{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::ModelVariable >,1 > > vars{};std::shared_ptr< monty::ndarray< bool,1 > > initsol_xx_flag{};std::shared_ptr< monty::ndarray< double,1 > > initsol_xx{};int natbarvarmap_num{};std::shared_ptr< monty::ndarray< int,1 > > natbarvarmap_Var{};monty::rc_ptr< ::mosek::fusion::Utils::StringIntMap > var_map{};int natvarmap_num{};std::shared_ptr< monty::ndarray< long long,1 > > natvarmap_idx{};std::shared_ptr< monty::ndarray< int,1 > > natvarmap_Var{};mosek::fusion::SolutionType solutionptr{};mosek::fusion::AccSolutionStatus acceptable_sol{};std::string model_name{};virtual void destroy();
static Model::t _new_Model(monty::rc_ptr< ::mosek::fusion::Model > _435);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _435);
static Model::t _new_Model();
void _initialize();
static Model::t _new_Model(const std::string &  _442);
void _initialize(const std::string &  _442);
static  void putlicensewait(bool _443);
static  void putlicensepath(const std::string &  _444);
static  void putlicensecode(std::shared_ptr< monty::ndarray< int,1 > > _445);
static  void inst(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _446,int _447,int _448,std::shared_ptr< monty::ndarray< long long,1 > > _449,int _450,std::shared_ptr< monty::ndarray< int,1 > > _451,std::shared_ptr< monty::ndarray< int,1 > > _452,std::shared_ptr< monty::ndarray< int,1 > > _453);
static  void inst(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _463,std::shared_ptr< monty::ndarray< long long,1 > > _464,std::shared_ptr< monty::ndarray< int,1 > > _465,std::shared_ptr< monty::ndarray< int,1 > > _466,std::shared_ptr< monty::ndarray< int,1 > > _467);
virtual void dispose();
virtual void varname(int _470,const std::string &  _471);
virtual void nativeVarToStr(int _472,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _473);
virtual int append_linearvar(monty::rc_ptr< ::mosek::fusion::ModelVariable > _474,long long _475,mosek::fusion::RelationKey _476,double _477);
virtual int append_rangedvar(monty::rc_ptr< ::mosek::fusion::ModelVariable > _479,long long _480,double _481,double _482);
virtual MSKtask_t getTask();
virtual void flushNames();
virtual void writeTask(const std::string &  _486);
virtual long long getSolverLIntInfo(const std::string &  _487);
virtual int getSolverIntInfo(const std::string &  _488);
virtual double getSolverDoubleInfo(const std::string &  _489);
virtual void setCallbackHandler(mosek::datacbhandler_t  _490);
virtual void setLogHandler(mosek::msghandler_t  _491);
virtual void setSolverParam(const std::string &  _492,double _493);
virtual void setSolverParam(const std::string &  _494,int _495);
virtual void setSolverParam(const std::string &  _496,const std::string &  _497);
virtual void breakSolver();
virtual void solve();
virtual void flushSolutions();
virtual void flush_initsol(mosek::fusion::SolutionType _498);
virtual mosek::fusion::SolutionStatus getDualSolutionStatus();
virtual mosek::fusion::SolutionStatus getPrimalSolutionStatus();
virtual double dualObjValue();
virtual double primalObjValue();
virtual monty::rc_ptr< ::mosek::fusion::SolutionStruct > get_sol_cache(mosek::fusion::SolutionType _506,bool _507);
virtual void setSolution_xx(std::shared_ptr< monty::ndarray< int,1 > > _512,std::shared_ptr< monty::ndarray< double,1 > > _513);
virtual void ensure_initsol_xx();
virtual std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > getSolution_bars(mosek::fusion::SolutionType _519);
virtual std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > getSolution_barx(mosek::fusion::SolutionType _520);
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_y(mosek::fusion::SolutionType _521);
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_xc(mosek::fusion::SolutionType _522);
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_snx(mosek::fusion::SolutionType _523);
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_suc(mosek::fusion::SolutionType _524);
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_slc(mosek::fusion::SolutionType _525);
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_sux(mosek::fusion::SolutionType _526);
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_slx(mosek::fusion::SolutionType _527);
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_xx(mosek::fusion::SolutionType _528);
virtual void selectedSolution(mosek::fusion::SolutionType _529);
virtual mosek::fusion::AccSolutionStatus getAcceptedSolutionStatus();
virtual void acceptedSolutionStatus(mosek::fusion::AccSolutionStatus _530);
virtual mosek::fusion::ProblemStatus getProblemStatus(mosek::fusion::SolutionType _531);
virtual mosek::fusion::SolutionStatus getDualSolutionStatus(mosek::fusion::SolutionType _533);
virtual mosek::fusion::SolutionStatus getPrimalSolutionStatus(mosek::fusion::SolutionType _534);
virtual mosek::fusion::SolutionStatus getSolutionStatus(mosek::fusion::SolutionType _535,bool _536);
virtual void objective_(const std::string &  _539,mosek::fusion::ObjectiveSense _540,monty::rc_ptr< ::mosek::fusion::Expression > _541);
virtual void objective(double _578);
virtual void objective(mosek::fusion::ObjectiveSense _579,double _580);
virtual void objective(mosek::fusion::ObjectiveSense _581,monty::rc_ptr< ::mosek::fusion::Variable > _582);
virtual void objective(mosek::fusion::ObjectiveSense _583,monty::rc_ptr< ::mosek::fusion::Expression > _584);
virtual void objective(const std::string &  _585,double _586);
virtual void objective(const std::string &  _587,mosek::fusion::ObjectiveSense _588,double _589);
virtual void objective(const std::string &  _590,mosek::fusion::ObjectiveSense _591,monty::rc_ptr< ::mosek::fusion::Variable > _592);
virtual void objective(const std::string &  _593,mosek::fusion::ObjectiveSense _594,monty::rc_ptr< ::mosek::fusion::Expression > _595);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Variable > _596,monty::rc_ptr< ::mosek::fusion::QConeDomain > _597);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _598,monty::rc_ptr< ::mosek::fusion::Variable > _599,monty::rc_ptr< ::mosek::fusion::QConeDomain > _600);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Set > _601,monty::rc_ptr< ::mosek::fusion::Variable > _602,monty::rc_ptr< ::mosek::fusion::QConeDomain > _603);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _604,monty::rc_ptr< ::mosek::fusion::Set > _605,monty::rc_ptr< ::mosek::fusion::Variable > _606,monty::rc_ptr< ::mosek::fusion::QConeDomain > _607);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Variable > _608,monty::rc_ptr< ::mosek::fusion::RangeDomain > _609);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _610,monty::rc_ptr< ::mosek::fusion::Variable > _611,monty::rc_ptr< ::mosek::fusion::RangeDomain > _612);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Set > _613,monty::rc_ptr< ::mosek::fusion::Variable > _614,monty::rc_ptr< ::mosek::fusion::RangeDomain > _615);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _616,monty::rc_ptr< ::mosek::fusion::Set > _617,monty::rc_ptr< ::mosek::fusion::Variable > _618,monty::rc_ptr< ::mosek::fusion::RangeDomain > _619);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Variable > _620,monty::rc_ptr< ::mosek::fusion::LinearDomain > _621);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _622,monty::rc_ptr< ::mosek::fusion::Variable > _623,monty::rc_ptr< ::mosek::fusion::LinearDomain > _624);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Set > _625,monty::rc_ptr< ::mosek::fusion::Variable > _626,monty::rc_ptr< ::mosek::fusion::LinearDomain > _627);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _628,monty::rc_ptr< ::mosek::fusion::Set > _629,monty::rc_ptr< ::mosek::fusion::Variable > _630,monty::rc_ptr< ::mosek::fusion::LinearDomain > _631);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Variable > _632,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _633);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _634,monty::rc_ptr< ::mosek::fusion::Variable > _635,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _636);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Variable > _637,monty::rc_ptr< ::mosek::fusion::PSDDomain > _638);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _639,monty::rc_ptr< ::mosek::fusion::Variable > _640,monty::rc_ptr< ::mosek::fusion::PSDDomain > _641);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Expression > _642,monty::rc_ptr< ::mosek::fusion::QConeDomain > _643);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _644,monty::rc_ptr< ::mosek::fusion::Expression > _645,monty::rc_ptr< ::mosek::fusion::QConeDomain > _646);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Set > _647,monty::rc_ptr< ::mosek::fusion::Expression > _648,monty::rc_ptr< ::mosek::fusion::QConeDomain > _649);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _650,monty::rc_ptr< ::mosek::fusion::Set > _651,monty::rc_ptr< ::mosek::fusion::Expression > _652,monty::rc_ptr< ::mosek::fusion::QConeDomain > _653);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Expression > _654,monty::rc_ptr< ::mosek::fusion::RangeDomain > _655);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _656,monty::rc_ptr< ::mosek::fusion::Expression > _657,monty::rc_ptr< ::mosek::fusion::RangeDomain > _658);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Set > _659,monty::rc_ptr< ::mosek::fusion::Expression > _660,monty::rc_ptr< ::mosek::fusion::RangeDomain > _661);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _662,monty::rc_ptr< ::mosek::fusion::Set > _663,monty::rc_ptr< ::mosek::fusion::Expression > _664,monty::rc_ptr< ::mosek::fusion::RangeDomain > _665);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Expression > _666,monty::rc_ptr< ::mosek::fusion::LinearDomain > _667);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _668,monty::rc_ptr< ::mosek::fusion::Expression > _669,monty::rc_ptr< ::mosek::fusion::LinearDomain > _670);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Set > _671,monty::rc_ptr< ::mosek::fusion::Expression > _672,monty::rc_ptr< ::mosek::fusion::LinearDomain > _673);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _674,monty::rc_ptr< ::mosek::fusion::Set > _675,monty::rc_ptr< ::mosek::fusion::Expression > _676,monty::rc_ptr< ::mosek::fusion::LinearDomain > _677);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Expression > _678,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _679);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _680,monty::rc_ptr< ::mosek::fusion::Expression > _681,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _682);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(monty::rc_ptr< ::mosek::fusion::Expression > _683,monty::rc_ptr< ::mosek::fusion::PSDDomain > _684);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint(const std::string &  _685,monty::rc_ptr< ::mosek::fusion::Expression > _686,monty::rc_ptr< ::mosek::fusion::PSDDomain > _687);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _688);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(int _689,int _690,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _691);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(int _692,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _693);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _694,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _695);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _696,int _697,int _698,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _699);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _700,int _701,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _702);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _703,monty::rc_ptr< ::mosek::fusion::Set > _704,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _705);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(monty::rc_ptr< ::mosek::fusion::PSDDomain > _706);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(int _707,int _708,monty::rc_ptr< ::mosek::fusion::PSDDomain > _709);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(int _710,monty::rc_ptr< ::mosek::fusion::PSDDomain > _711);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _712,monty::rc_ptr< ::mosek::fusion::PSDDomain > _713);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _714,int _715,int _716,monty::rc_ptr< ::mosek::fusion::PSDDomain > _717);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _718,int _719,monty::rc_ptr< ::mosek::fusion::PSDDomain > _720);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _721,monty::rc_ptr< ::mosek::fusion::Set > _722,monty::rc_ptr< ::mosek::fusion::PSDDomain > _723);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricVariable > variable(int _724,monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > _725);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricVariable > variable(const std::string &  _726,int _727,monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > _728);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(monty::rc_ptr< ::mosek::fusion::QConeDomain > _729);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(monty::rc_ptr< ::mosek::fusion::RangeDomain > _730);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(monty::rc_ptr< ::mosek::fusion::LinearDomain > _731);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(std::shared_ptr< monty::ndarray< int,1 > > _732,monty::rc_ptr< ::mosek::fusion::RangeDomain > _733);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(std::shared_ptr< monty::ndarray< int,1 > > _734,monty::rc_ptr< ::mosek::fusion::LinearDomain > _735);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(monty::rc_ptr< ::mosek::fusion::Set > _736,monty::rc_ptr< ::mosek::fusion::QConeDomain > _737);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(monty::rc_ptr< ::mosek::fusion::Set > _738,monty::rc_ptr< ::mosek::fusion::RangeDomain > _739);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(monty::rc_ptr< ::mosek::fusion::Set > _740,monty::rc_ptr< ::mosek::fusion::LinearDomain > _741);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(int _742,monty::rc_ptr< ::mosek::fusion::QConeDomain > _743);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(int _744,monty::rc_ptr< ::mosek::fusion::RangeDomain > _745);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(int _746,monty::rc_ptr< ::mosek::fusion::LinearDomain > _747);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(std::shared_ptr< monty::ndarray< int,1 > > _748);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(int _749);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable();
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _750,monty::rc_ptr< ::mosek::fusion::QConeDomain > _751);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _752,monty::rc_ptr< ::mosek::fusion::RangeDomain > _753);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _754,monty::rc_ptr< ::mosek::fusion::LinearDomain > _755);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _756,std::shared_ptr< monty::ndarray< int,1 > > _757,monty::rc_ptr< ::mosek::fusion::RangeDomain > _758);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _759,std::shared_ptr< monty::ndarray< int,1 > > _760,monty::rc_ptr< ::mosek::fusion::LinearDomain > _761);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _762,monty::rc_ptr< ::mosek::fusion::Set > _763,monty::rc_ptr< ::mosek::fusion::QConeDomain > _764);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _765,monty::rc_ptr< ::mosek::fusion::Set > _766,monty::rc_ptr< ::mosek::fusion::RangeDomain > _767);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _768,monty::rc_ptr< ::mosek::fusion::Set > _769,monty::rc_ptr< ::mosek::fusion::LinearDomain > _770);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _771,int _772,monty::rc_ptr< ::mosek::fusion::QConeDomain > _773);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _774,int _775,monty::rc_ptr< ::mosek::fusion::RangeDomain > _776);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _777,int _778,monty::rc_ptr< ::mosek::fusion::LinearDomain > _779);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _780,std::shared_ptr< monty::ndarray< int,1 > > _781);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _782,int _783);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable(const std::string &  _784);
virtual monty::rc_ptr< ::mosek::fusion::Variable > ranged_variable(const std::string &  _785,int _786,monty::rc_ptr< ::mosek::fusion::SymmetricRangeDomain > _787);
virtual monty::rc_ptr< ::mosek::fusion::Variable > ranged_variable(const std::string &  _806,monty::rc_ptr< ::mosek::fusion::Set > _807,monty::rc_ptr< ::mosek::fusion::RangeDomain > _808);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable_(const std::string &  _825,monty::rc_ptr< ::mosek::fusion::Set > _826,monty::rc_ptr< ::mosek::fusion::QConeDomain > _827);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricVariable > variable_(const std::string &  _851,int _852,monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > _853);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable_(const std::string &  _871,monty::rc_ptr< ::mosek::fusion::Set > _872,monty::rc_ptr< ::mosek::fusion::LinearDomain > _873);
virtual monty::rc_ptr< ::mosek::fusion::Variable > variable_(const std::string &  _890,monty::rc_ptr< ::mosek::fusion::Set > _891,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _892);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricVariable > variable_(const std::string &  _900,monty::rc_ptr< ::mosek::fusion::Set > _901,monty::rc_ptr< ::mosek::fusion::PSDDomain > _902);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint_(const std::string &  _907,monty::rc_ptr< ::mosek::fusion::Set > _908,monty::rc_ptr< ::mosek::fusion::Expression > _909,monty::rc_ptr< ::mosek::fusion::RangeDomain > _910);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint_(const std::string &  _933,monty::rc_ptr< ::mosek::fusion::Set > _934,monty::rc_ptr< ::mosek::fusion::Expression > _935,monty::rc_ptr< ::mosek::fusion::QConeDomain > _936);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint_(const std::string &  _971,monty::rc_ptr< ::mosek::fusion::Set > _972,monty::rc_ptr< ::mosek::fusion::Expression > _973,monty::rc_ptr< ::mosek::fusion::LinearDomain > _974);
virtual monty::rc_ptr< ::mosek::fusion::ConNZStruct > build_conA(std::shared_ptr< monty::ndarray< long long,1 > > _995,long long _996,std::shared_ptr< monty::ndarray< long long,1 > > _997,std::shared_ptr< monty::ndarray< long long,1 > > _998,std::shared_ptr< monty::ndarray< double,1 > > _999,std::shared_ptr< monty::ndarray< double,1 > > _1000,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _1001);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint_(const std::string &  _1058,monty::rc_ptr< ::mosek::fusion::Expression > _1059,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _1060);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > constraint_(const std::string &  _1095,monty::rc_ptr< ::mosek::fusion::Expression > _1096,monty::rc_ptr< ::mosek::fusion::PSDDomain > _1097);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > nonsym_psdconstraint(const std::string &  _1110,monty::rc_ptr< ::mosek::fusion::Expression > _1111,monty::rc_ptr< ::mosek::fusion::PSDDomain > _1112);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > sdptrilcon(const std::string &  _1174,int _1175,int _1176,std::shared_ptr< monty::ndarray< long long,1 > > _1177,std::shared_ptr< monty::ndarray< long long,1 > > _1178,std::shared_ptr< monty::ndarray< long long,1 > > _1179,std::shared_ptr< monty::ndarray< long long,1 > > _1180,std::shared_ptr< monty::ndarray< double,1 > > _1181,std::shared_ptr< monty::ndarray< double,1 > > _1182,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _1183);
virtual void addConstraint(const std::string &  _1254,monty::rc_ptr< ::mosek::fusion::ModelConstraint > _1255);
virtual void addVariable(const std::string &  _1259,monty::rc_ptr< ::mosek::fusion::ModelVariable > _1260);
virtual long long numConstraints();
virtual long long numVariables();
virtual bool hasConstraint(const std::string &  _1264);
virtual bool hasVariable(const std::string &  _1265);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > getConstraint(int _1266);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > getConstraint(const std::string &  _1267);
virtual monty::rc_ptr< ::mosek::fusion::Variable > getVariable(int _1268);
virtual monty::rc_ptr< ::mosek::fusion::Variable > getVariable(const std::string &  _1269);
virtual std::string getName();
virtual monty::rc_ptr< ::mosek::fusion::Model > clone();
virtual void natbarvarmap_ensure(int _1270);
virtual void natvarmap_ensure(int _1275);
virtual int task_alloc_vars(int _1280);
}; // struct Model;

// mosek.fusion.Debug from file 'src/fusion/cxx/Debug_p.h'
// namespace mosek::fusion
struct p_Debug
{
  Debug * _pubthis;

  p_Debug(Debug * _pubthis) : _pubthis(_pubthis) {}

  static Debug::t o ()                 { return monty::rc_ptr<Debug>(new Debug()); }
  Debug::t p (const std::string & val) { std::cout << val; return Debug::t(_pubthis); }
  Debug::t p (      int val)           { std::cout << val; return Debug::t(_pubthis); }
  Debug::t p (long long val)           { std::cout << val; return Debug::t(_pubthis); }
  Debug::t p (   double val)           { std::cout << val; return Debug::t(_pubthis); }
  Debug::t p (     bool val)           { std::cout << val; return Debug::t(_pubthis); }
  Debug::t lf()                        { std::cout << std::endl; return Debug::t(_pubthis); }

  static p_Debug * _get_impl(Debug * _inst) { return _inst->ptr.get(); }

  template<typename T>
  Debug::t p(const std::shared_ptr<monty::ndarray<T,1>> & val)
  {
    if (val->size() > 0)
    {
      std::cout << (*val)[0];
      for (int i = 1; i < val->size(); ++i)
        std::cout << "," << (*val)[i];
    }
    return Debug::t(_pubthis);
  }
};
// End of file 'src/fusion/cxx/Debug_p.h'
struct p_Sort
{
Sort * _pubthis;
static mosek::fusion::p_Sort* _get_impl(mosek::fusion::Sort * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Sort * _get_impl(mosek::fusion::Sort::t _inst) { return _get_impl(_inst.get()); }
p_Sort(Sort * _pubthis);
virtual ~p_Sort() { /* std::cout << "~p_Sort" << std::endl;*/ };
virtual void destroy();
static  void argTransposeSort(std::shared_ptr< monty::ndarray< long long,1 > > _142,std::shared_ptr< monty::ndarray< long long,1 > > _143,int _144,int _145,int _146,std::shared_ptr< monty::ndarray< long long,1 > > _147);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _155,std::shared_ptr< monty::ndarray< long long,1 > > _156);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _157,std::shared_ptr< monty::ndarray< int,1 > > _158);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _159,std::shared_ptr< monty::ndarray< long long,1 > > _160,std::shared_ptr< monty::ndarray< long long,1 > > _161);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _162,std::shared_ptr< monty::ndarray< int,1 > > _163,std::shared_ptr< monty::ndarray< int,1 > > _164);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _165,std::shared_ptr< monty::ndarray< long long,1 > > _166,long long _167,long long _168);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _169,std::shared_ptr< monty::ndarray< int,1 > > _170,long long _171,long long _172);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _173,std::shared_ptr< monty::ndarray< long long,1 > > _174,std::shared_ptr< monty::ndarray< long long,1 > > _175,long long _176,long long _177);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _178,std::shared_ptr< monty::ndarray< int,1 > > _179,std::shared_ptr< monty::ndarray< int,1 > > _180,long long _181,long long _182);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _183,std::shared_ptr< monty::ndarray< long long,1 > > _184,long long _185,long long _186,bool _187);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _190,std::shared_ptr< monty::ndarray< int,1 > > _191,long long _192,long long _193,bool _194);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _197,std::shared_ptr< monty::ndarray< long long,1 > > _198,std::shared_ptr< monty::ndarray< long long,1 > > _199,long long _200,long long _201,bool _202);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _205,std::shared_ptr< monty::ndarray< int,1 > > _206,std::shared_ptr< monty::ndarray< int,1 > > _207,long long _208,long long _209,bool _210);
static  void argbucketsort(std::shared_ptr< monty::ndarray< long long,1 > > _213,std::shared_ptr< monty::ndarray< long long,1 > > _214,long long _215,long long _216,long long _217,long long _218);
static  void argbucketsort(std::shared_ptr< monty::ndarray< long long,1 > > _219,std::shared_ptr< monty::ndarray< int,1 > > _220,long long _221,long long _222,int _223,int _224);
static  void getminmax(std::shared_ptr< monty::ndarray< long long,1 > > _225,std::shared_ptr< monty::ndarray< long long,1 > > _226,std::shared_ptr< monty::ndarray< long long,1 > > _227,long long _228,long long _229,std::shared_ptr< monty::ndarray< long long,1 > > _230);
static  void getminmax(std::shared_ptr< monty::ndarray< long long,1 > > _233,std::shared_ptr< monty::ndarray< int,1 > > _234,std::shared_ptr< monty::ndarray< int,1 > > _235,long long _236,long long _237,std::shared_ptr< monty::ndarray< int,1 > > _238);
static  bool issorted(std::shared_ptr< monty::ndarray< long long,1 > > _241,std::shared_ptr< monty::ndarray< long long,1 > > _242,long long _243,long long _244,bool _245);
static  bool issorted(std::shared_ptr< monty::ndarray< long long,1 > > _247,std::shared_ptr< monty::ndarray< int,1 > > _248,long long _249,long long _250,bool _251);
static  bool issorted(std::shared_ptr< monty::ndarray< long long,1 > > _253,std::shared_ptr< monty::ndarray< long long,1 > > _254,std::shared_ptr< monty::ndarray< long long,1 > > _255,long long _256,long long _257,bool _258);
static  bool issorted(std::shared_ptr< monty::ndarray< long long,1 > > _260,std::shared_ptr< monty::ndarray< int,1 > > _261,std::shared_ptr< monty::ndarray< int,1 > > _262,long long _263,long long _264,bool _265);
}; // struct Sort;

struct p_IndexCounter
{
IndexCounter * _pubthis;
static mosek::fusion::p_IndexCounter* _get_impl(mosek::fusion::IndexCounter * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_IndexCounter * _get_impl(mosek::fusion::IndexCounter::t _inst) { return _get_impl(_inst.get()); }
p_IndexCounter(IndexCounter * _pubthis);
virtual ~p_IndexCounter() { /* std::cout << "~p_IndexCounter" << std::endl;*/ };
long long start{};std::shared_ptr< monty::ndarray< int,1 > > dims{};std::shared_ptr< monty::ndarray< long long,1 > > strides{};std::shared_ptr< monty::ndarray< long long,1 > > st{};std::shared_ptr< monty::ndarray< int,1 > > ii{};int n{};virtual void destroy();
static IndexCounter::t _new_IndexCounter(monty::rc_ptr< ::mosek::fusion::Set > _267);
void _initialize(monty::rc_ptr< ::mosek::fusion::Set > _267);
static IndexCounter::t _new_IndexCounter(long long _270,std::shared_ptr< monty::ndarray< int,1 > > _271,monty::rc_ptr< ::mosek::fusion::Set > _272);
void _initialize(long long _270,std::shared_ptr< monty::ndarray< int,1 > > _271,monty::rc_ptr< ::mosek::fusion::Set > _272);
static IndexCounter::t _new_IndexCounter(long long _275,std::shared_ptr< monty::ndarray< int,1 > > _276,std::shared_ptr< monty::ndarray< long long,1 > > _277);
void _initialize(long long _275,std::shared_ptr< monty::ndarray< int,1 > > _276,std::shared_ptr< monty::ndarray< long long,1 > > _277);
virtual bool atEnd();
virtual std::shared_ptr< monty::ndarray< int,1 > > getIndex();
virtual long long next();
virtual long long get();
virtual void inc();
virtual void reset();
}; // struct IndexCounter;

struct p_CommonTools
{
CommonTools * _pubthis;
static mosek::fusion::p_CommonTools* _get_impl(mosek::fusion::CommonTools * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_CommonTools * _get_impl(mosek::fusion::CommonTools::t _inst) { return _get_impl(_inst.get()); }
p_CommonTools(CommonTools * _pubthis);
virtual ~p_CommonTools() { /* std::cout << "~p_CommonTools" << std::endl;*/ };
virtual void destroy();
static  void ndIncr(std::shared_ptr< monty::ndarray< int,1 > > _283,std::shared_ptr< monty::ndarray< int,1 > > _284,std::shared_ptr< monty::ndarray< int,1 > > _285);
static  void transposeTriplets(std::shared_ptr< monty::ndarray< int,1 > > _287,std::shared_ptr< monty::ndarray< int,1 > > _288,std::shared_ptr< monty::ndarray< double,1 > > _289,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< long long,1 > >,1 > > _290,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< long long,1 > >,1 > > _291,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > _292,long long _293,int _294,int _295);
static  void transposeTriplets(std::shared_ptr< monty::ndarray< int,1 > > _308,std::shared_ptr< monty::ndarray< int,1 > > _309,std::shared_ptr< monty::ndarray< double,1 > > _310,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _311,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _312,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > _313,long long _314,int _315,int _316);
static  void tripletSort(std::shared_ptr< monty::ndarray< int,1 > > _329,std::shared_ptr< monty::ndarray< int,1 > > _330,std::shared_ptr< monty::ndarray< double,1 > > _331,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _332,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _333,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > _334,long long _335,int _336,int _337);
static  void argMSort(std::shared_ptr< monty::ndarray< int,1 > > _363,std::shared_ptr< monty::ndarray< int,1 > > _364);
static  void mergeInto(std::shared_ptr< monty::ndarray< int,1 > > _369,std::shared_ptr< monty::ndarray< int,1 > > _370,std::shared_ptr< monty::ndarray< int,1 > > _371,int _372,int _373,int _374);
static  void argQsort(std::shared_ptr< monty::ndarray< long long,1 > > _380,std::shared_ptr< monty::ndarray< long long,1 > > _381,std::shared_ptr< monty::ndarray< long long,1 > > _382,long long _383,long long _384);
static  void argQsort(std::shared_ptr< monty::ndarray< long long,1 > > _385,std::shared_ptr< monty::ndarray< int,1 > > _386,std::shared_ptr< monty::ndarray< int,1 > > _387,long long _388,long long _389);
}; // struct CommonTools;

struct p_SolutionStruct
{
SolutionStruct * _pubthis;
static mosek::fusion::p_SolutionStruct* _get_impl(mosek::fusion::SolutionStruct * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_SolutionStruct * _get_impl(mosek::fusion::SolutionStruct::t _inst) { return _get_impl(_inst.get()); }
p_SolutionStruct(SolutionStruct * _pubthis);
virtual ~p_SolutionStruct() { /* std::cout << "~p_SolutionStruct" << std::endl;*/ };
std::shared_ptr< monty::ndarray< double,1 > > snx{};std::shared_ptr< monty::ndarray< double,1 > > sux{};std::shared_ptr< monty::ndarray< double,1 > > slx{};std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > bars{};std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > barx{};std::shared_ptr< monty::ndarray< double,1 > > y{};std::shared_ptr< monty::ndarray< double,1 > > suc{};std::shared_ptr< monty::ndarray< double,1 > > slc{};std::shared_ptr< monty::ndarray< double,1 > > xx{};std::shared_ptr< monty::ndarray< double,1 > > xc{};double dobj{};double pobj{};mosek::fusion::ProblemStatus probstatus{};mosek::fusion::SolutionStatus dstatus{};mosek::fusion::SolutionStatus pstatus{};int sol_numbarvar{};int sol_numcone{};int sol_numvar{};int sol_numcon{};virtual void destroy();
static SolutionStruct::t _new_SolutionStruct(int _390,int _391,int _392,int _393);
void _initialize(int _390,int _391,int _392,int _393);
static SolutionStruct::t _new_SolutionStruct(monty::rc_ptr< ::mosek::fusion::SolutionStruct > _394);
void _initialize(monty::rc_ptr< ::mosek::fusion::SolutionStruct > _394);
virtual monty::rc_ptr< ::mosek::fusion::SolutionStruct > clone();
virtual void resize(int _397,int _398,int _399,int _400);
virtual bool isDualAcceptable(mosek::fusion::AccSolutionStatus _424);
virtual bool isPrimalAcceptable(mosek::fusion::AccSolutionStatus _425);
virtual bool isAcceptable(mosek::fusion::SolutionStatus _426,mosek::fusion::AccSolutionStatus _427);
}; // struct SolutionStruct;

struct p_ConNZStruct
{
ConNZStruct * _pubthis;
static mosek::fusion::p_ConNZStruct* _get_impl(mosek::fusion::ConNZStruct * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_ConNZStruct * _get_impl(mosek::fusion::ConNZStruct::t _inst) { return _get_impl(_inst.get()); }
p_ConNZStruct(ConNZStruct * _pubthis);
virtual ~p_ConNZStruct() { /* std::cout << "~p_ConNZStruct" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > barmidx{};std::shared_ptr< monty::ndarray< int,1 > > barsubj{};std::shared_ptr< monty::ndarray< int,1 > > barsubi{};std::shared_ptr< monty::ndarray< double,1 > > bfix{};std::shared_ptr< monty::ndarray< double,1 > > cof{};std::shared_ptr< monty::ndarray< int,1 > > subj{};std::shared_ptr< monty::ndarray< long long,1 > > ptrb{};virtual void destroy();
static ConNZStruct::t _new_ConNZStruct(std::shared_ptr< monty::ndarray< long long,1 > > _428,std::shared_ptr< monty::ndarray< int,1 > > _429,std::shared_ptr< monty::ndarray< double,1 > > _430,std::shared_ptr< monty::ndarray< double,1 > > _431,std::shared_ptr< monty::ndarray< int,1 > > _432,std::shared_ptr< monty::ndarray< int,1 > > _433,std::shared_ptr< monty::ndarray< int,1 > > _434);
void _initialize(std::shared_ptr< monty::ndarray< long long,1 > > _428,std::shared_ptr< monty::ndarray< int,1 > > _429,std::shared_ptr< monty::ndarray< double,1 > > _430,std::shared_ptr< monty::ndarray< double,1 > > _431,std::shared_ptr< monty::ndarray< int,1 > > _432,std::shared_ptr< monty::ndarray< int,1 > > _433,std::shared_ptr< monty::ndarray< int,1 > > _434);
}; // struct ConNZStruct;

struct p_BaseVariable : public /*implements*/ ::mosek::fusion::Variable
{
BaseVariable * _pubthis;
static mosek::fusion::p_BaseVariable* _get_impl(mosek::fusion::BaseVariable * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_BaseVariable * _get_impl(mosek::fusion::BaseVariable::t _inst) { return _get_impl(_inst.get()); }
p_BaseVariable(BaseVariable * _pubthis);
virtual ~p_BaseVariable() { /* std::cout << "~p_BaseVariable" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Model > model{};monty::rc_ptr< ::mosek::fusion::Set > shape_p{};virtual void destroy();
static BaseVariable::t _new_BaseVariable(monty::rc_ptr< ::mosek::fusion::BaseVariable > _2524,monty::rc_ptr< ::mosek::fusion::Model > _2525);
void _initialize(monty::rc_ptr< ::mosek::fusion::BaseVariable > _2524,monty::rc_ptr< ::mosek::fusion::Model > _2525);
static BaseVariable::t _new_BaseVariable(monty::rc_ptr< ::mosek::fusion::Model > _2526,monty::rc_ptr< ::mosek::fusion::Set > _2527);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2526,monty::rc_ptr< ::mosek::fusion::Set > _2527);
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _2528,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2529);
virtual void elementName(long long _2530,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2531) { throw monty::AbstractClassError("Call to abstract method"); }
virtual std::string toString();
virtual void inst(std::shared_ptr< monty::ndarray< long long,1 > > _2537,int _2538,int _2539,long long _2540,long long _2541,std::shared_ptr< monty::ndarray< int,1 > > _2542,std::shared_ptr< monty::ndarray< int,1 > > _2543,std::shared_ptr< monty::ndarray< int,1 > > _2544);
virtual void inst(long long _2546,long long _2547,std::shared_ptr< monty::ndarray< int,1 > > _2548,std::shared_ptr< monty::ndarray< int,1 > > _2549,std::shared_ptr< monty::ndarray< int,1 > > _2550) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _2551,std::shared_ptr< monty::ndarray< double,1 > > _2552,bool _2553) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void set_values(long long _2554,std::shared_ptr< monty::ndarray< int,1 > > _2555,std::shared_ptr< monty::ndarray< long long,1 > > _2556,int _2557,std::shared_ptr< monty::ndarray< double,1 > > _2558,bool _2559) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void values(int _2560,std::shared_ptr< monty::ndarray< double,1 > > _2561,bool _2562);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _2567,int _2568,std::shared_ptr< monty::ndarray< double,1 > > _2569,bool _2570) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void values(long long _2571,std::shared_ptr< monty::ndarray< int,1 > > _2572,std::shared_ptr< monty::ndarray< long long,1 > > _2573,int _2574,std::shared_ptr< monty::ndarray< double,1 > > _2575,bool _2576) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void setLevel(std::shared_ptr< monty::ndarray< double,1 > > _2577);
virtual monty::rc_ptr< ::mosek::fusion::Model > getModel();
virtual monty::rc_ptr< ::mosek::fusion::Set > shape();
virtual monty::rc_ptr< ::mosek::fusion::Set > getShape();
virtual long long size();
virtual std::shared_ptr< monty::ndarray< double,1 > > dual();
virtual std::shared_ptr< monty::ndarray< double,1 > > level();
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _2582) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _2583) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void makeContinuous();
virtual void makeInteger();
virtual monty::rc_ptr< ::mosek::fusion::Variable > transpose();
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2586,int _2587,int _2588);
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2589,int _2590);
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(std::shared_ptr< monty::ndarray< int,1 > > _2591);
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2592);
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2593,std::shared_ptr< monty::ndarray< int,1 > > _2594,std::shared_ptr< monty::ndarray< int,1 > > _2595);
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2597,std::shared_ptr< monty::ndarray< int,1 > > _2598);
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,2 > > _2600);
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2603);
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag(int _2605);
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag();
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag(int _2606);
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag();
virtual monty::rc_ptr< ::mosek::fusion::Variable > general_diag(std::shared_ptr< monty::ndarray< int,1 > > _2607,std::shared_ptr< monty::ndarray< int,1 > > _2608);
virtual monty::rc_ptr< ::mosek::fusion::Expression > asExpr();
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(std::shared_ptr< monty::ndarray< int,1 > > _2621,std::shared_ptr< monty::ndarray< int,1 > > _2622);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(int _2625,int _2626);
}; // struct BaseVariable;

struct p_CompoundVariable : public ::mosek::fusion::p_BaseVariable
{
CompoundVariable * _pubthis;
static mosek::fusion::p_CompoundVariable* _get_impl(mosek::fusion::CompoundVariable * _inst){ return static_cast< mosek::fusion::p_CompoundVariable* >(mosek::fusion::p_BaseVariable::_get_impl(_inst)); }
static mosek::fusion::p_CompoundVariable * _get_impl(mosek::fusion::CompoundVariable::t _inst) { return _get_impl(_inst.get()); }
p_CompoundVariable(CompoundVariable * _pubthis);
virtual ~p_CompoundVariable() { /* std::cout << "~p_CompoundVariable" << std::endl;*/ };
int stackdim{};std::shared_ptr< monty::ndarray< int,1 > > varsb{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > vars{};virtual void destroy();
static CompoundVariable::t _new_CompoundVariable(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _1283,int _1284);
void _initialize(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _1283,int _1284);
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _1290,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1291);
virtual void elementName(long long _1294,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1295);
virtual void inst(long long _1298,long long _1299,std::shared_ptr< monty::ndarray< int,1 > > _1300,std::shared_ptr< monty::ndarray< int,1 > > _1301,std::shared_ptr< monty::ndarray< int,1 > > _1302);
virtual void set_values(long long _1305,std::shared_ptr< monty::ndarray< int,1 > > _1306,std::shared_ptr< monty::ndarray< long long,1 > > _1307,int _1308,std::shared_ptr< monty::ndarray< double,1 > > _1309,bool _1310);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _1328,std::shared_ptr< monty::ndarray< double,1 > > _1329,bool _1330);
virtual void values(long long _1338,std::shared_ptr< monty::ndarray< int,1 > > _1339,std::shared_ptr< monty::ndarray< long long,1 > > _1340,int _1341,std::shared_ptr< monty::ndarray< double,1 > > _1342,bool _1343);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _1358,int _1359,std::shared_ptr< monty::ndarray< double,1 > > _1360,bool _1361);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _1368);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _1375);
virtual monty::rc_ptr< ::mosek::fusion::Expression > asExpr();
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(std::shared_ptr< monty::ndarray< int,1 > > _1402,std::shared_ptr< monty::ndarray< int,1 > > _1403);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(int _1421,int _1422);
static  monty::rc_ptr< ::mosek::fusion::Set > compute_shape(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _1430,int _1431);
static  monty::rc_ptr< ::mosek::fusion::Model > model_from_var(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _1439);
}; // struct CompoundVariable;

struct p_PickVariable : public ::mosek::fusion::p_BaseVariable
{
PickVariable * _pubthis;
static mosek::fusion::p_PickVariable* _get_impl(mosek::fusion::PickVariable * _inst){ return static_cast< mosek::fusion::p_PickVariable* >(mosek::fusion::p_BaseVariable::_get_impl(_inst)); }
static mosek::fusion::p_PickVariable * _get_impl(mosek::fusion::PickVariable::t _inst) { return _get_impl(_inst.get()); }
p_PickVariable(PickVariable * _pubthis);
virtual ~p_PickVariable() { /* std::cout << "~p_PickVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > indexes{};monty::rc_ptr< ::mosek::fusion::Variable > origin{};virtual void destroy();
static PickVariable::t _new_PickVariable(monty::rc_ptr< ::mosek::fusion::Variable > _1440,std::shared_ptr< monty::ndarray< long long,1 > > _1441);
void _initialize(monty::rc_ptr< ::mosek::fusion::Variable > _1440,std::shared_ptr< monty::ndarray< long long,1 > > _1441);
virtual void inst(long long _1444,long long _1445,std::shared_ptr< monty::ndarray< int,1 > > _1446,std::shared_ptr< monty::ndarray< int,1 > > _1447,std::shared_ptr< monty::ndarray< int,1 > > _1448);
virtual void set_values(long long _1449,std::shared_ptr< monty::ndarray< int,1 > > _1450,std::shared_ptr< monty::ndarray< long long,1 > > _1451,int _1452,std::shared_ptr< monty::ndarray< double,1 > > _1453,bool _1454);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _1457,std::shared_ptr< monty::ndarray< double,1 > > _1458,bool _1459);
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _1461,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1462);
virtual void elementName(long long _1463,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1464);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(int _1465,int _1466);
virtual void values(long long _1468,std::shared_ptr< monty::ndarray< int,1 > > _1469,std::shared_ptr< monty::ndarray< long long,1 > > _1470,int _1471,std::shared_ptr< monty::ndarray< double,1 > > _1472,bool _1473);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _1476,int _1477,std::shared_ptr< monty::ndarray< double,1 > > _1478,bool _1479);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _1482);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _1484);
}; // struct PickVariable;

struct p_SliceVariable : public ::mosek::fusion::p_BaseVariable
{
SliceVariable * _pubthis;
static mosek::fusion::p_SliceVariable* _get_impl(mosek::fusion::SliceVariable * _inst){ return static_cast< mosek::fusion::p_SliceVariable* >(mosek::fusion::p_BaseVariable::_get_impl(_inst)); }
static mosek::fusion::p_SliceVariable * _get_impl(mosek::fusion::SliceVariable::t _inst) { return _get_impl(_inst.get()); }
p_SliceVariable(SliceVariable * _pubthis);
virtual ~p_SliceVariable() { /* std::cout << "~p_SliceVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > strides{};long long first{};monty::rc_ptr< ::mosek::fusion::Variable > origin{};virtual void destroy();
static SliceVariable::t _new_SliceVariable(monty::rc_ptr< ::mosek::fusion::Variable > _1486,monty::rc_ptr< ::mosek::fusion::Set > _1487,long long _1488,std::shared_ptr< monty::ndarray< long long,1 > > _1489);
void _initialize(monty::rc_ptr< ::mosek::fusion::Variable > _1486,monty::rc_ptr< ::mosek::fusion::Set > _1487,long long _1488,std::shared_ptr< monty::ndarray< long long,1 > > _1489);
virtual void inst(long long _1490,long long _1491,std::shared_ptr< monty::ndarray< int,1 > > _1492,std::shared_ptr< monty::ndarray< int,1 > > _1493,std::shared_ptr< monty::ndarray< int,1 > > _1494);
virtual void set_values(long long _1499,std::shared_ptr< monty::ndarray< int,1 > > _1500,std::shared_ptr< monty::ndarray< long long,1 > > _1501,int _1502,std::shared_ptr< monty::ndarray< double,1 > > _1503,bool _1504);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _1523,std::shared_ptr< monty::ndarray< double,1 > > _1524,bool _1525);
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _1531,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1532);
virtual void elementName(long long _1537,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1538);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(std::shared_ptr< monty::ndarray< int,1 > > _1543,std::shared_ptr< monty::ndarray< int,1 > > _1544);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(int _1548,int _1549);
virtual void values(long long _1550,std::shared_ptr< monty::ndarray< int,1 > > _1551,std::shared_ptr< monty::ndarray< long long,1 > > _1552,int _1553,std::shared_ptr< monty::ndarray< double,1 > > _1554,bool _1555);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _1573,int _1574,std::shared_ptr< monty::ndarray< double,1 > > _1575,bool _1576);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _1582);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _1588);
}; // struct SliceVariable;

struct p_BoundInterfaceVariable : public ::mosek::fusion::p_SliceVariable
{
BoundInterfaceVariable * _pubthis;
static mosek::fusion::p_BoundInterfaceVariable* _get_impl(mosek::fusion::BoundInterfaceVariable * _inst){ return static_cast< mosek::fusion::p_BoundInterfaceVariable* >(mosek::fusion::p_SliceVariable::_get_impl(_inst)); }
static mosek::fusion::p_BoundInterfaceVariable * _get_impl(mosek::fusion::BoundInterfaceVariable::t _inst) { return _get_impl(_inst.get()); }
p_BoundInterfaceVariable(BoundInterfaceVariable * _pubthis);
virtual ~p_BoundInterfaceVariable() { /* std::cout << "~p_BoundInterfaceVariable" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::RangedVariable > originvar{};bool islower{};virtual void destroy();
static BoundInterfaceVariable::t _new_BoundInterfaceVariable(monty::rc_ptr< ::mosek::fusion::RangedVariable > _2362,monty::rc_ptr< ::mosek::fusion::Set > _2363,long long _2364,std::shared_ptr< monty::ndarray< long long,1 > > _2365,bool _2366);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangedVariable > _2362,monty::rc_ptr< ::mosek::fusion::Set > _2363,long long _2364,std::shared_ptr< monty::ndarray< long long,1 > > _2365,bool _2366);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice_(monty::rc_ptr< ::mosek::fusion::Set > _2367,long long _2368,std::shared_ptr< monty::ndarray< long long,1 > > _2369);
virtual void dual_values(long long _2370,std::shared_ptr< monty::ndarray< int,1 > > _2371,std::shared_ptr< monty::ndarray< long long,1 > > _2372,int _2373,std::shared_ptr< monty::ndarray< double,1 > > _2374);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _2375,int _2376,std::shared_ptr< monty::ndarray< double,1 > > _2377);
}; // struct BoundInterfaceVariable;

struct p_ModelVariable : public ::mosek::fusion::p_BaseVariable
{
ModelVariable * _pubthis;
static mosek::fusion::p_ModelVariable* _get_impl(mosek::fusion::ModelVariable * _inst){ return static_cast< mosek::fusion::p_ModelVariable* >(mosek::fusion::p_BaseVariable::_get_impl(_inst)); }
static mosek::fusion::p_ModelVariable * _get_impl(mosek::fusion::ModelVariable::t _inst) { return _get_impl(_inst.get()); }
p_ModelVariable(ModelVariable * _pubthis);
virtual ~p_ModelVariable() { /* std::cout << "~p_ModelVariable" << std::endl;*/ };
long long varid{};std::string name{};virtual void destroy();
static ModelVariable::t _new_ModelVariable(monty::rc_ptr< ::mosek::fusion::ModelVariable > _2458,monty::rc_ptr< ::mosek::fusion::Model > _2459);
void _initialize(monty::rc_ptr< ::mosek::fusion::ModelVariable > _2458,monty::rc_ptr< ::mosek::fusion::Model > _2459);
static ModelVariable::t _new_ModelVariable(monty::rc_ptr< ::mosek::fusion::Model > _2460,const std::string &  _2461,monty::rc_ptr< ::mosek::fusion::Set > _2462,long long _2463);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2460,const std::string &  _2461,monty::rc_ptr< ::mosek::fusion::Set > _2462,long long _2463);
virtual void flushNames() { throw monty::AbstractClassError("Call to abstract method"); }
virtual void elementName(long long _2464,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2465);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(std::shared_ptr< monty::ndarray< int,1 > > _2466,std::shared_ptr< monty::ndarray< int,1 > > _2467);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(int _2473,int _2474);
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > clone(monty::rc_ptr< ::mosek::fusion::Model > _2476) { throw monty::AbstractClassError("Call to abstract method"); }
}; // struct ModelVariable;

struct p_SymRangedVariable : public ::mosek::fusion::p_ModelVariable, public /*implements*/ ::mosek::fusion::SymmetricVariable
{
SymRangedVariable * _pubthis;
static mosek::fusion::p_SymRangedVariable* _get_impl(mosek::fusion::SymRangedVariable * _inst){ return static_cast< mosek::fusion::p_SymRangedVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_SymRangedVariable * _get_impl(mosek::fusion::SymRangedVariable::t _inst) { return _get_impl(_inst.get()); }
p_SymRangedVariable(SymRangedVariable * _pubthis);
virtual ~p_SymRangedVariable() { /* std::cout << "~p_SymRangedVariable" << std::endl;*/ };
int dim{};bool names_flushed{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};monty::rc_ptr< ::mosek::fusion::RangeDomain > dom{};monty::rc_ptr< ::mosek::fusion::Utils::IntMap > idxmap{};virtual void destroy();
static SymRangedVariable::t _new_SymRangedVariable(monty::rc_ptr< ::mosek::fusion::SymRangedVariable > _1594,monty::rc_ptr< ::mosek::fusion::Model > _1595);
void _initialize(monty::rc_ptr< ::mosek::fusion::SymRangedVariable > _1594,monty::rc_ptr< ::mosek::fusion::Model > _1595);
static SymRangedVariable::t _new_SymRangedVariable(monty::rc_ptr< ::mosek::fusion::Model > _1597,const std::string &  _1598,monty::rc_ptr< ::mosek::fusion::RangeDomain > _1599,int _1600,std::shared_ptr< monty::ndarray< int,1 > > _1601,long long _1602);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1597,const std::string &  _1598,monty::rc_ptr< ::mosek::fusion::RangeDomain > _1599,int _1600,std::shared_ptr< monty::ndarray< int,1 > > _1601,long long _1602);
virtual std::string toString();
virtual void flushNames();
virtual void inst(std::shared_ptr< monty::ndarray< long long,1 > > _1609,int _1610,int _1611,long long _1612,long long _1613,std::shared_ptr< monty::ndarray< int,1 > > _1614,std::shared_ptr< monty::ndarray< int,1 > > _1615,std::shared_ptr< monty::ndarray< int,1 > > _1616);
virtual void inst(long long _1622,long long _1623,std::shared_ptr< monty::ndarray< int,1 > > _1624,std::shared_ptr< monty::ndarray< int,1 > > _1625,std::shared_ptr< monty::ndarray< int,1 > > _1626);
virtual void dual_u(long long _1631,std::shared_ptr< monty::ndarray< int,1 > > _1632,std::shared_ptr< monty::ndarray< long long,1 > > _1633,int _1634,std::shared_ptr< monty::ndarray< double,1 > > _1635);
virtual void dual_u(std::shared_ptr< monty::ndarray< long long,1 > > _1647,int _1648,std::shared_ptr< monty::ndarray< double,1 > > _1649);
virtual void dual_l(long long _1657,std::shared_ptr< monty::ndarray< int,1 > > _1658,std::shared_ptr< monty::ndarray< long long,1 > > _1659,int _1660,std::shared_ptr< monty::ndarray< double,1 > > _1661);
virtual void dual_l(std::shared_ptr< monty::ndarray< long long,1 > > _1673,int _1674,std::shared_ptr< monty::ndarray< double,1 > > _1675);
virtual void dual_values(long long _1682,std::shared_ptr< monty::ndarray< int,1 > > _1683,std::shared_ptr< monty::ndarray< long long,1 > > _1684,int _1685,std::shared_ptr< monty::ndarray< double,1 > > _1686);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _1698,int _1699,std::shared_ptr< monty::ndarray< double,1 > > _1700);
virtual void set_values(long long _1708,std::shared_ptr< monty::ndarray< int,1 > > _1709,std::shared_ptr< monty::ndarray< long long,1 > > _1710,int _1711,std::shared_ptr< monty::ndarray< double,1 > > _1712,bool _1713);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _1727,std::shared_ptr< monty::ndarray< double,1 > > _1728,bool _1729);
virtual void values(long long _1739,std::shared_ptr< monty::ndarray< int,1 > > _1740,std::shared_ptr< monty::ndarray< long long,1 > > _1741,int _1742,std::shared_ptr< monty::ndarray< double,1 > > _1743,bool _1744);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _1753,int _1754,std::shared_ptr< monty::ndarray< double,1 > > _1755,bool _1756);
virtual long long tril_idx(long long _1763);
virtual long long tril_lin_idx(long long _1766);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _1769);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _1772);
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > clone(monty::rc_ptr< ::mosek::fusion::Model > _1775);
virtual monty::rc_ptr< ::mosek::fusion::Expression > asExpr() /*override*/
{ return mosek::fusion::p_BaseVariable::asExpr(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(int _2473,int _2474) /*override*/
{ return mosek::fusion::p_ModelVariable::slice(_2473,_2474); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,2 > > _2600) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2600); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2603) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2603); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag() /*override*/
{ return mosek::fusion::p_BaseVariable::antidiag(); }
virtual void makeContinuous() /*override*/
{ mosek::fusion::p_BaseVariable::makeContinuous(); }
virtual monty::rc_ptr< ::mosek::fusion::Set > shape() /*override*/
{ return mosek::fusion::p_BaseVariable::shape(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2593,std::shared_ptr< monty::ndarray< int,1 > > _2594,std::shared_ptr< monty::ndarray< int,1 > > _2595) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2593,_2594,_2595); }
virtual void elementName(long long _2464,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2465) /*override*/
{ mosek::fusion::p_ModelVariable::elementName(_2464,_2465); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2592) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2592); }
virtual void makeInteger() /*override*/
{ mosek::fusion::p_BaseVariable::makeInteger(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2586,int _2587,int _2588) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2586,_2587,_2588); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag() /*override*/
{ return mosek::fusion::p_BaseVariable::diag(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2589,int _2590) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2589,_2590); }
virtual monty::rc_ptr< ::mosek::fusion::Set > getShape() /*override*/
{ return mosek::fusion::p_BaseVariable::getShape(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > transpose() /*override*/
{ return mosek::fusion::p_BaseVariable::transpose(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(std::shared_ptr< monty::ndarray< int,1 > > _2591) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2591); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2597,std::shared_ptr< monty::ndarray< int,1 > > _2598) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2597,_2598); }
virtual std::shared_ptr< monty::ndarray< double,1 > > level() /*override*/
{ return mosek::fusion::p_BaseVariable::level(); }
virtual monty::rc_ptr< ::mosek::fusion::Model > getModel() /*override*/
{ return mosek::fusion::p_BaseVariable::getModel(); }
virtual void setLevel(std::shared_ptr< monty::ndarray< double,1 > > _2577) /*override*/
{ mosek::fusion::p_BaseVariable::setLevel(_2577); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag(int _2606) /*override*/
{ return mosek::fusion::p_BaseVariable::diag(_2606); }
virtual std::shared_ptr< monty::ndarray< double,1 > > dual() /*override*/
{ return mosek::fusion::p_BaseVariable::dual(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(std::shared_ptr< monty::ndarray< int,1 > > _2466,std::shared_ptr< monty::ndarray< int,1 > > _2467) /*override*/
{ return mosek::fusion::p_ModelVariable::slice(_2466,_2467); }
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _2528,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2529) /*override*/
{ return mosek::fusion::p_BaseVariable::elementDesc(_2528,_2529); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag(int _2605) /*override*/
{ return mosek::fusion::p_BaseVariable::antidiag(_2605); }
virtual long long size() /*override*/
{ return mosek::fusion::p_BaseVariable::size(); }
virtual void values(int _2560,std::shared_ptr< monty::ndarray< double,1 > > _2561,bool _2562) /*override*/
{ mosek::fusion::p_BaseVariable::values(_2560,_2561,_2562); }
}; // struct SymRangedVariable;

struct p_RangedVariable : public ::mosek::fusion::p_ModelVariable
{
RangedVariable * _pubthis;
static mosek::fusion::p_RangedVariable* _get_impl(mosek::fusion::RangedVariable * _inst){ return static_cast< mosek::fusion::p_RangedVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_RangedVariable * _get_impl(mosek::fusion::RangedVariable::t _inst) { return _get_impl(_inst.get()); }
p_RangedVariable(RangedVariable * _pubthis);
virtual ~p_RangedVariable() { /* std::cout << "~p_RangedVariable" << std::endl;*/ };
bool names_flushed{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};monty::rc_ptr< ::mosek::fusion::RangeDomain > dom{};monty::rc_ptr< ::mosek::fusion::Utils::IntMap > idxmap{};virtual void destroy();
static RangedVariable::t _new_RangedVariable(monty::rc_ptr< ::mosek::fusion::RangedVariable > _1776,monty::rc_ptr< ::mosek::fusion::Model > _1777);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangedVariable > _1776,monty::rc_ptr< ::mosek::fusion::Model > _1777);
static RangedVariable::t _new_RangedVariable(monty::rc_ptr< ::mosek::fusion::Model > _1779,const std::string &  _1780,monty::rc_ptr< ::mosek::fusion::Set > _1781,monty::rc_ptr< ::mosek::fusion::RangeDomain > _1782,std::shared_ptr< monty::ndarray< int,1 > > _1783,long long _1784);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1779,const std::string &  _1780,monty::rc_ptr< ::mosek::fusion::Set > _1781,monty::rc_ptr< ::mosek::fusion::RangeDomain > _1782,std::shared_ptr< monty::ndarray< int,1 > > _1783,long long _1784);
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _1785,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1786);
virtual void flushNames();
virtual void inst(std::shared_ptr< monty::ndarray< long long,1 > > _1791,int _1792,int _1793,long long _1794,long long _1795,std::shared_ptr< monty::ndarray< int,1 > > _1796,std::shared_ptr< monty::ndarray< int,1 > > _1797,std::shared_ptr< monty::ndarray< int,1 > > _1798);
virtual void inst(long long _1802,long long _1803,std::shared_ptr< monty::ndarray< int,1 > > _1804,std::shared_ptr< monty::ndarray< int,1 > > _1805,std::shared_ptr< monty::ndarray< int,1 > > _1806);
virtual monty::rc_ptr< ::mosek::fusion::Variable > upperBoundVar();
virtual monty::rc_ptr< ::mosek::fusion::Variable > lowerBoundVar();
virtual void dual_u(long long _1813,std::shared_ptr< monty::ndarray< int,1 > > _1814,std::shared_ptr< monty::ndarray< long long,1 > > _1815,int _1816,std::shared_ptr< monty::ndarray< double,1 > > _1817);
virtual void dual_u(std::shared_ptr< monty::ndarray< long long,1 > > _1828,int _1829,std::shared_ptr< monty::ndarray< double,1 > > _1830);
virtual void dual_l(long long _1837,std::shared_ptr< monty::ndarray< int,1 > > _1838,std::shared_ptr< monty::ndarray< long long,1 > > _1839,int _1840,std::shared_ptr< monty::ndarray< double,1 > > _1841);
virtual void dual_l(std::shared_ptr< monty::ndarray< long long,1 > > _1852,int _1853,std::shared_ptr< monty::ndarray< double,1 > > _1854);
virtual void dual_values(long long _1861,std::shared_ptr< monty::ndarray< int,1 > > _1862,std::shared_ptr< monty::ndarray< long long,1 > > _1863,int _1864,std::shared_ptr< monty::ndarray< double,1 > > _1865);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _1877,int _1878,std::shared_ptr< monty::ndarray< double,1 > > _1879);
virtual void set_values(long long _1887,std::shared_ptr< monty::ndarray< int,1 > > _1888,std::shared_ptr< monty::ndarray< long long,1 > > _1889,int _1890,std::shared_ptr< monty::ndarray< double,1 > > _1891,bool _1892);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _1906,std::shared_ptr< monty::ndarray< double,1 > > _1907,bool _1908);
virtual void values(long long _1918,std::shared_ptr< monty::ndarray< int,1 > > _1919,std::shared_ptr< monty::ndarray< long long,1 > > _1920,int _1921,std::shared_ptr< monty::ndarray< double,1 > > _1922,bool _1923);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _1932,int _1933,std::shared_ptr< monty::ndarray< double,1 > > _1934,bool _1935);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _1940);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _1943);
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > clone(monty::rc_ptr< ::mosek::fusion::Model > _1946);
}; // struct RangedVariable;

struct p_LinearPSDVariable : public ::mosek::fusion::p_ModelVariable
{
LinearPSDVariable * _pubthis;
static mosek::fusion::p_LinearPSDVariable* _get_impl(mosek::fusion::LinearPSDVariable * _inst){ return static_cast< mosek::fusion::p_LinearPSDVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_LinearPSDVariable * _get_impl(mosek::fusion::LinearPSDVariable::t _inst) { return _get_impl(_inst.get()); }
p_LinearPSDVariable(LinearPSDVariable * _pubthis);
virtual ~p_LinearPSDVariable() { /* std::cout << "~p_LinearPSDVariable" << std::endl;*/ };
int numcones{};int coneidx{};int conesize{};int sdpvardim{};int blocksize{};virtual void destroy();
static LinearPSDVariable::t _new_LinearPSDVariable(monty::rc_ptr< ::mosek::fusion::LinearPSDVariable > _1947,monty::rc_ptr< ::mosek::fusion::Model > _1948);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearPSDVariable > _1947,monty::rc_ptr< ::mosek::fusion::Model > _1948);
static LinearPSDVariable::t _new_LinearPSDVariable(monty::rc_ptr< ::mosek::fusion::Model > _1949,const std::string &  _1950,int _1951,monty::rc_ptr< ::mosek::fusion::Set > _1952,int _1953,long long _1954);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1949,const std::string &  _1950,int _1951,monty::rc_ptr< ::mosek::fusion::Set > _1952,int _1953,long long _1954);
virtual void flushNames();
virtual std::string toString();
virtual void inst(std::shared_ptr< monty::ndarray< long long,1 > > _1958,int _1959,int _1960,long long _1961,long long _1962,std::shared_ptr< monty::ndarray< int,1 > > _1963,std::shared_ptr< monty::ndarray< int,1 > > _1964,std::shared_ptr< monty::ndarray< int,1 > > _1965);
virtual void inst(long long _1975,long long _1976,std::shared_ptr< monty::ndarray< int,1 > > _1977,std::shared_ptr< monty::ndarray< int,1 > > _1978,std::shared_ptr< monty::ndarray< int,1 > > _1979);
virtual void set_values(long long _1985,std::shared_ptr< monty::ndarray< int,1 > > _1986,std::shared_ptr< monty::ndarray< long long,1 > > _1987,int _1988,std::shared_ptr< monty::ndarray< double,1 > > _1989,bool _1990);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _1991,std::shared_ptr< monty::ndarray< double,1 > > _1992,bool _1993);
virtual void values(long long _1994,std::shared_ptr< monty::ndarray< int,1 > > _1995,std::shared_ptr< monty::ndarray< long long,1 > > _1996,int _1997,std::shared_ptr< monty::ndarray< double,1 > > _1998,bool _1999);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _2008,int _2009,std::shared_ptr< monty::ndarray< double,1 > > _2010,bool _2011);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _2017);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _2018);
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > clone(monty::rc_ptr< ::mosek::fusion::Model > _2019);
}; // struct LinearPSDVariable;

struct p_PSDVariable : public ::mosek::fusion::p_ModelVariable, public /*implements*/ ::mosek::fusion::SymmetricVariable
{
PSDVariable * _pubthis;
static mosek::fusion::p_PSDVariable* _get_impl(mosek::fusion::PSDVariable * _inst){ return static_cast< mosek::fusion::p_PSDVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_PSDVariable * _get_impl(mosek::fusion::PSDVariable::t _inst) { return _get_impl(_inst.get()); }
p_PSDVariable(PSDVariable * _pubthis);
virtual ~p_PSDVariable() { /* std::cout << "~p_PSDVariable" << std::endl;*/ };
int numcones{};int coneidx{};int conesize{};virtual void destroy();
static PSDVariable::t _new_PSDVariable(monty::rc_ptr< ::mosek::fusion::PSDVariable > _2020,monty::rc_ptr< ::mosek::fusion::Model > _2021);
void _initialize(monty::rc_ptr< ::mosek::fusion::PSDVariable > _2020,monty::rc_ptr< ::mosek::fusion::Model > _2021);
static PSDVariable::t _new_PSDVariable(monty::rc_ptr< ::mosek::fusion::Model > _2022,const std::string &  _2023,int _2024,int _2025,int _2026,long long _2027);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2022,const std::string &  _2023,int _2024,int _2025,int _2026,long long _2027);
virtual void flushNames();
virtual std::string toString();
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _2030,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2031);
virtual void elementName(long long _2037,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2038);
virtual void inst(std::shared_ptr< monty::ndarray< long long,1 > > _2044,int _2045,int _2046,long long _2047,long long _2048,std::shared_ptr< monty::ndarray< int,1 > > _2049,std::shared_ptr< monty::ndarray< int,1 > > _2050,std::shared_ptr< monty::ndarray< int,1 > > _2051);
virtual void inst(long long _2060,long long _2061,std::shared_ptr< monty::ndarray< int,1 > > _2062,std::shared_ptr< monty::ndarray< int,1 > > _2063,std::shared_ptr< monty::ndarray< int,1 > > _2064);
virtual void set_values(long long _2069,std::shared_ptr< monty::ndarray< int,1 > > _2070,std::shared_ptr< monty::ndarray< long long,1 > > _2071,int _2072,std::shared_ptr< monty::ndarray< double,1 > > _2073,bool _2074);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _2075,std::shared_ptr< monty::ndarray< double,1 > > _2076,bool _2077);
virtual void values(long long _2078,std::shared_ptr< monty::ndarray< int,1 > > _2079,std::shared_ptr< monty::ndarray< long long,1 > > _2080,int _2081,std::shared_ptr< monty::ndarray< double,1 > > _2082,bool _2083);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _2095,int _2096,std::shared_ptr< monty::ndarray< double,1 > > _2097,bool _2098);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _2106);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _2107);
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > clone(monty::rc_ptr< ::mosek::fusion::Model > _2108);
virtual monty::rc_ptr< ::mosek::fusion::Expression > asExpr() /*override*/
{ return mosek::fusion::p_BaseVariable::asExpr(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(int _2473,int _2474) /*override*/
{ return mosek::fusion::p_ModelVariable::slice(_2473,_2474); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,2 > > _2600) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2600); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2603) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2603); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag() /*override*/
{ return mosek::fusion::p_BaseVariable::antidiag(); }
virtual void makeContinuous() /*override*/
{ mosek::fusion::p_BaseVariable::makeContinuous(); }
virtual monty::rc_ptr< ::mosek::fusion::Set > shape() /*override*/
{ return mosek::fusion::p_BaseVariable::shape(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2593,std::shared_ptr< monty::ndarray< int,1 > > _2594,std::shared_ptr< monty::ndarray< int,1 > > _2595) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2593,_2594,_2595); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2592) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2592); }
virtual void makeInteger() /*override*/
{ mosek::fusion::p_BaseVariable::makeInteger(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2586,int _2587,int _2588) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2586,_2587,_2588); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag() /*override*/
{ return mosek::fusion::p_BaseVariable::diag(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2589,int _2590) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2589,_2590); }
virtual monty::rc_ptr< ::mosek::fusion::Set > getShape() /*override*/
{ return mosek::fusion::p_BaseVariable::getShape(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > transpose() /*override*/
{ return mosek::fusion::p_BaseVariable::transpose(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(std::shared_ptr< monty::ndarray< int,1 > > _2591) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2591); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2597,std::shared_ptr< monty::ndarray< int,1 > > _2598) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2597,_2598); }
virtual std::shared_ptr< monty::ndarray< double,1 > > level() /*override*/
{ return mosek::fusion::p_BaseVariable::level(); }
virtual monty::rc_ptr< ::mosek::fusion::Model > getModel() /*override*/
{ return mosek::fusion::p_BaseVariable::getModel(); }
virtual void setLevel(std::shared_ptr< monty::ndarray< double,1 > > _2577) /*override*/
{ mosek::fusion::p_BaseVariable::setLevel(_2577); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag(int _2606) /*override*/
{ return mosek::fusion::p_BaseVariable::diag(_2606); }
virtual std::shared_ptr< monty::ndarray< double,1 > > dual() /*override*/
{ return mosek::fusion::p_BaseVariable::dual(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(std::shared_ptr< monty::ndarray< int,1 > > _2466,std::shared_ptr< monty::ndarray< int,1 > > _2467) /*override*/
{ return mosek::fusion::p_ModelVariable::slice(_2466,_2467); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag(int _2605) /*override*/
{ return mosek::fusion::p_BaseVariable::antidiag(_2605); }
virtual long long size() /*override*/
{ return mosek::fusion::p_BaseVariable::size(); }
virtual void values(int _2560,std::shared_ptr< monty::ndarray< double,1 > > _2561,bool _2562) /*override*/
{ mosek::fusion::p_BaseVariable::values(_2560,_2561,_2562); }
}; // struct PSDVariable;

struct p_SymLinearVariable : public ::mosek::fusion::p_ModelVariable, public /*implements*/ ::mosek::fusion::SymmetricVariable
{
SymLinearVariable * _pubthis;
static mosek::fusion::p_SymLinearVariable* _get_impl(mosek::fusion::SymLinearVariable * _inst){ return static_cast< mosek::fusion::p_SymLinearVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_SymLinearVariable * _get_impl(mosek::fusion::SymLinearVariable::t _inst) { return _get_impl(_inst.get()); }
p_SymLinearVariable(SymLinearVariable * _pubthis);
virtual ~p_SymLinearVariable() { /* std::cout << "~p_SymLinearVariable" << std::endl;*/ };
int dim{};bool names_flushed{};monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > dom{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};monty::rc_ptr< ::mosek::fusion::Utils::IntMap > idxmap{};virtual void destroy();
static SymLinearVariable::t _new_SymLinearVariable(monty::rc_ptr< ::mosek::fusion::SymLinearVariable > _2109,monty::rc_ptr< ::mosek::fusion::Model > _2110);
void _initialize(monty::rc_ptr< ::mosek::fusion::SymLinearVariable > _2109,monty::rc_ptr< ::mosek::fusion::Model > _2110);
static SymLinearVariable::t _new_SymLinearVariable(monty::rc_ptr< ::mosek::fusion::Model > _2112,const std::string &  _2113,monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > _2114,int _2115,std::shared_ptr< monty::ndarray< int,1 > > _2116,long long _2117);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2112,const std::string &  _2113,monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > _2114,int _2115,std::shared_ptr< monty::ndarray< int,1 > > _2116,long long _2117);
virtual std::string toString();
virtual void flushNames();
virtual void inst(std::shared_ptr< monty::ndarray< long long,1 > > _2127,int _2128,int _2129,long long _2130,long long _2131,std::shared_ptr< monty::ndarray< int,1 > > _2132,std::shared_ptr< monty::ndarray< int,1 > > _2133,std::shared_ptr< monty::ndarray< int,1 > > _2134);
virtual void inst(long long _2140,long long _2141,std::shared_ptr< monty::ndarray< int,1 > > _2142,std::shared_ptr< monty::ndarray< int,1 > > _2143,std::shared_ptr< monty::ndarray< int,1 > > _2144);
virtual void dual_values(long long _2148,std::shared_ptr< monty::ndarray< int,1 > > _2149,std::shared_ptr< monty::ndarray< long long,1 > > _2150,int _2151,std::shared_ptr< monty::ndarray< double,1 > > _2152);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _2164,int _2165,std::shared_ptr< monty::ndarray< double,1 > > _2166);
virtual void set_values(long long _2174,std::shared_ptr< monty::ndarray< int,1 > > _2175,std::shared_ptr< monty::ndarray< long long,1 > > _2176,int _2177,std::shared_ptr< monty::ndarray< double,1 > > _2178,bool _2179);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _2193,std::shared_ptr< monty::ndarray< double,1 > > _2194,bool _2195);
virtual void values(long long _2203,std::shared_ptr< monty::ndarray< int,1 > > _2204,std::shared_ptr< monty::ndarray< long long,1 > > _2205,int _2206,std::shared_ptr< monty::ndarray< double,1 > > _2207,bool _2208);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _2218,int _2219,std::shared_ptr< monty::ndarray< double,1 > > _2220,bool _2221);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _2229);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _2232);
virtual long long tril_idx(long long _2235);
virtual long long tril_lin_idx(long long _2238);
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > clone(monty::rc_ptr< ::mosek::fusion::Model > _2241);
virtual monty::rc_ptr< ::mosek::fusion::Expression > asExpr() /*override*/
{ return mosek::fusion::p_BaseVariable::asExpr(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(int _2473,int _2474) /*override*/
{ return mosek::fusion::p_ModelVariable::slice(_2473,_2474); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,2 > > _2600) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2600); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2603) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2603); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag() /*override*/
{ return mosek::fusion::p_BaseVariable::antidiag(); }
virtual void makeContinuous() /*override*/
{ mosek::fusion::p_BaseVariable::makeContinuous(); }
virtual monty::rc_ptr< ::mosek::fusion::Set > shape() /*override*/
{ return mosek::fusion::p_BaseVariable::shape(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2593,std::shared_ptr< monty::ndarray< int,1 > > _2594,std::shared_ptr< monty::ndarray< int,1 > > _2595) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2593,_2594,_2595); }
virtual void elementName(long long _2464,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2465) /*override*/
{ mosek::fusion::p_ModelVariable::elementName(_2464,_2465); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2592) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2592); }
virtual void makeInteger() /*override*/
{ mosek::fusion::p_BaseVariable::makeInteger(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2586,int _2587,int _2588) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2586,_2587,_2588); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag() /*override*/
{ return mosek::fusion::p_BaseVariable::diag(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2589,int _2590) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2589,_2590); }
virtual monty::rc_ptr< ::mosek::fusion::Set > getShape() /*override*/
{ return mosek::fusion::p_BaseVariable::getShape(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > transpose() /*override*/
{ return mosek::fusion::p_BaseVariable::transpose(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(std::shared_ptr< monty::ndarray< int,1 > > _2591) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2591); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2597,std::shared_ptr< monty::ndarray< int,1 > > _2598) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2597,_2598); }
virtual std::shared_ptr< monty::ndarray< double,1 > > level() /*override*/
{ return mosek::fusion::p_BaseVariable::level(); }
virtual monty::rc_ptr< ::mosek::fusion::Model > getModel() /*override*/
{ return mosek::fusion::p_BaseVariable::getModel(); }
virtual void setLevel(std::shared_ptr< monty::ndarray< double,1 > > _2577) /*override*/
{ mosek::fusion::p_BaseVariable::setLevel(_2577); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag(int _2606) /*override*/
{ return mosek::fusion::p_BaseVariable::diag(_2606); }
virtual std::shared_ptr< monty::ndarray< double,1 > > dual() /*override*/
{ return mosek::fusion::p_BaseVariable::dual(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(std::shared_ptr< monty::ndarray< int,1 > > _2466,std::shared_ptr< monty::ndarray< int,1 > > _2467) /*override*/
{ return mosek::fusion::p_ModelVariable::slice(_2466,_2467); }
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _2528,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2529) /*override*/
{ return mosek::fusion::p_BaseVariable::elementDesc(_2528,_2529); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag(int _2605) /*override*/
{ return mosek::fusion::p_BaseVariable::antidiag(_2605); }
virtual long long size() /*override*/
{ return mosek::fusion::p_BaseVariable::size(); }
virtual void values(int _2560,std::shared_ptr< monty::ndarray< double,1 > > _2561,bool _2562) /*override*/
{ mosek::fusion::p_BaseVariable::values(_2560,_2561,_2562); }
}; // struct SymLinearVariable;

struct p_LinearVariable : public ::mosek::fusion::p_ModelVariable
{
LinearVariable * _pubthis;
static mosek::fusion::p_LinearVariable* _get_impl(mosek::fusion::LinearVariable * _inst){ return static_cast< mosek::fusion::p_LinearVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_LinearVariable * _get_impl(mosek::fusion::LinearVariable::t _inst) { return _get_impl(_inst.get()); }
p_LinearVariable(LinearVariable * _pubthis);
virtual ~p_LinearVariable() { /* std::cout << "~p_LinearVariable" << std::endl;*/ };
bool names_flushed{};monty::rc_ptr< ::mosek::fusion::LinearDomain > dom{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};monty::rc_ptr< ::mosek::fusion::Utils::IntMap > idxmap{};virtual void destroy();
static LinearVariable::t _new_LinearVariable(monty::rc_ptr< ::mosek::fusion::LinearVariable > _2242,monty::rc_ptr< ::mosek::fusion::Model > _2243);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearVariable > _2242,monty::rc_ptr< ::mosek::fusion::Model > _2243);
static LinearVariable::t _new_LinearVariable(monty::rc_ptr< ::mosek::fusion::Model > _2245,const std::string &  _2246,monty::rc_ptr< ::mosek::fusion::LinearDomain > _2247,monty::rc_ptr< ::mosek::fusion::Set > _2248,std::shared_ptr< monty::ndarray< int,1 > > _2249,long long _2250);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2245,const std::string &  _2246,monty::rc_ptr< ::mosek::fusion::LinearDomain > _2247,monty::rc_ptr< ::mosek::fusion::Set > _2248,std::shared_ptr< monty::ndarray< int,1 > > _2249,long long _2250);
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _2251,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2252);
virtual void elementName(long long _2253,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2254);
virtual void flushNames();
virtual void inst(std::shared_ptr< monty::ndarray< long long,1 > > _2259,int _2260,int _2261,long long _2262,long long _2263,std::shared_ptr< monty::ndarray< int,1 > > _2264,std::shared_ptr< monty::ndarray< int,1 > > _2265,std::shared_ptr< monty::ndarray< int,1 > > _2266);
virtual void inst(long long _2270,long long _2271,std::shared_ptr< monty::ndarray< int,1 > > _2272,std::shared_ptr< monty::ndarray< int,1 > > _2273,std::shared_ptr< monty::ndarray< int,1 > > _2274);
virtual void dual_values(long long _2276,std::shared_ptr< monty::ndarray< int,1 > > _2277,std::shared_ptr< monty::ndarray< long long,1 > > _2278,int _2279,std::shared_ptr< monty::ndarray< double,1 > > _2280);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _2292,int _2293,std::shared_ptr< monty::ndarray< double,1 > > _2294);
virtual void set_values(long long _2302,std::shared_ptr< monty::ndarray< int,1 > > _2303,std::shared_ptr< monty::ndarray< long long,1 > > _2304,int _2305,std::shared_ptr< monty::ndarray< double,1 > > _2306,bool _2307);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _2321,std::shared_ptr< monty::ndarray< double,1 > > _2322,bool _2323);
virtual void values(long long _2333,std::shared_ptr< monty::ndarray< int,1 > > _2334,std::shared_ptr< monty::ndarray< long long,1 > > _2335,int _2336,std::shared_ptr< monty::ndarray< double,1 > > _2337,bool _2338);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _2347);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _2350);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _2353,int _2354,std::shared_ptr< monty::ndarray< double,1 > > _2355,bool _2356);
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > clone(monty::rc_ptr< ::mosek::fusion::Model > _2361);
}; // struct LinearVariable;

struct p_ConicVariable : public ::mosek::fusion::p_ModelVariable
{
ConicVariable * _pubthis;
static mosek::fusion::p_ConicVariable* _get_impl(mosek::fusion::ConicVariable * _inst){ return static_cast< mosek::fusion::p_ConicVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_ConicVariable * _get_impl(mosek::fusion::ConicVariable::t _inst) { return _get_impl(_inst.get()); }
p_ConicVariable(ConicVariable * _pubthis);
virtual ~p_ConicVariable() { /* std::cout << "~p_ConicVariable" << std::endl;*/ };
bool names_flushed{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};monty::rc_ptr< ::mosek::fusion::QConeDomain > dom{};int numcone{};int conesize{};int coneidx{};virtual void destroy();
static ConicVariable::t _new_ConicVariable(monty::rc_ptr< ::mosek::fusion::ConicVariable > _2378,monty::rc_ptr< ::mosek::fusion::Model > _2379);
void _initialize(monty::rc_ptr< ::mosek::fusion::ConicVariable > _2378,monty::rc_ptr< ::mosek::fusion::Model > _2379);
static ConicVariable::t _new_ConicVariable(monty::rc_ptr< ::mosek::fusion::Model > _2381,const std::string &  _2382,monty::rc_ptr< ::mosek::fusion::QConeDomain > _2383,monty::rc_ptr< ::mosek::fusion::Set > _2384,std::shared_ptr< monty::ndarray< int,1 > > _2385,int _2386,int _2387,int _2388,long long _2389);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2381,const std::string &  _2382,monty::rc_ptr< ::mosek::fusion::QConeDomain > _2383,monty::rc_ptr< ::mosek::fusion::Set > _2384,std::shared_ptr< monty::ndarray< int,1 > > _2385,int _2386,int _2387,int _2388,long long _2389);
virtual std::string toString();
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _2392,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2393);
virtual void elementName(long long _2394,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2395);
virtual void flushNames();
virtual void inst(std::shared_ptr< monty::ndarray< long long,1 > > _2397,int _2398,int _2399,long long _2400,long long _2401,std::shared_ptr< monty::ndarray< int,1 > > _2402,std::shared_ptr< monty::ndarray< int,1 > > _2403,std::shared_ptr< monty::ndarray< int,1 > > _2404);
virtual void inst(long long _2406,long long _2407,std::shared_ptr< monty::ndarray< int,1 > > _2408,std::shared_ptr< monty::ndarray< int,1 > > _2409,std::shared_ptr< monty::ndarray< int,1 > > _2410);
virtual void set_values(long long _2411,std::shared_ptr< monty::ndarray< int,1 > > _2412,std::shared_ptr< monty::ndarray< long long,1 > > _2413,int _2414,std::shared_ptr< monty::ndarray< double,1 > > _2415,bool _2416);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _2426,std::shared_ptr< monty::ndarray< double,1 > > _2427,bool _2428);
virtual void values(long long _2434,std::shared_ptr< monty::ndarray< int,1 > > _2435,std::shared_ptr< monty::ndarray< long long,1 > > _2436,int _2437,std::shared_ptr< monty::ndarray< double,1 > > _2438,bool _2439);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _2446,int _2447,std::shared_ptr< monty::ndarray< double,1 > > _2448,bool _2449);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _2452);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _2454);
virtual int get_variable_index(int _2456);
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > clone(monty::rc_ptr< ::mosek::fusion::Model > _2457);
}; // struct ConicVariable;

struct p_NilVariable : public ::mosek::fusion::p_BaseVariable, public /*implements*/ ::mosek::fusion::SymmetricVariable
{
NilVariable * _pubthis;
static mosek::fusion::p_NilVariable* _get_impl(mosek::fusion::NilVariable * _inst){ return static_cast< mosek::fusion::p_NilVariable* >(mosek::fusion::p_BaseVariable::_get_impl(_inst)); }
static mosek::fusion::p_NilVariable * _get_impl(mosek::fusion::NilVariable::t _inst) { return _get_impl(_inst.get()); }
p_NilVariable(NilVariable * _pubthis);
virtual ~p_NilVariable() { /* std::cout << "~p_NilVariable" << std::endl;*/ };
virtual void destroy();
static NilVariable::t _new_NilVariable();
void _initialize();
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > elementDesc(long long _2477,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2478);
virtual void elementName(long long _2479,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2480);
virtual void inst(std::shared_ptr< monty::ndarray< long long,1 > > _2481,int _2482,int _2483,long long _2484,long long _2485,std::shared_ptr< monty::ndarray< int,1 > > _2486,std::shared_ptr< monty::ndarray< int,1 > > _2487,std::shared_ptr< monty::ndarray< int,1 > > _2488);
virtual void inst(long long _2489,long long _2490,std::shared_ptr< monty::ndarray< int,1 > > _2491,std::shared_ptr< monty::ndarray< int,1 > > _2492,std::shared_ptr< monty::ndarray< int,1 > > _2493);
virtual void set_values(std::shared_ptr< monty::ndarray< long long,1 > > _2494,std::shared_ptr< monty::ndarray< double,1 > > _2495,bool _2496);
virtual void set_values(long long _2497,std::shared_ptr< monty::ndarray< int,1 > > _2498,std::shared_ptr< monty::ndarray< long long,1 > > _2499,int _2500,std::shared_ptr< monty::ndarray< double,1 > > _2501,bool _2502);
virtual void values(std::shared_ptr< monty::ndarray< long long,1 > > _2503,int _2504,std::shared_ptr< monty::ndarray< double,1 > > _2505,bool _2506);
virtual void values(long long _2507,std::shared_ptr< monty::ndarray< int,1 > > _2508,std::shared_ptr< monty::ndarray< long long,1 > > _2509,int _2510,std::shared_ptr< monty::ndarray< double,1 > > _2511,bool _2512);
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _2513);
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _2514);
virtual void makeContinuous();
virtual void makeInteger();
virtual std::string toString();
virtual long long size();
virtual std::shared_ptr< monty::ndarray< double,1 > > dual();
virtual std::shared_ptr< monty::ndarray< double,1 > > level();
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(std::shared_ptr< monty::ndarray< int,1 > > _2517);
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2518);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(std::shared_ptr< monty::ndarray< int,1 > > _2519,std::shared_ptr< monty::ndarray< int,1 > > _2520);
virtual monty::rc_ptr< ::mosek::fusion::Variable > slice(int _2522,int _2523);
virtual monty::rc_ptr< ::mosek::fusion::Expression > asExpr() /*override*/
{ return mosek::fusion::p_BaseVariable::asExpr(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,2 > > _2600) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2600); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2603) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2603); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag() /*override*/
{ return mosek::fusion::p_BaseVariable::antidiag(); }
virtual monty::rc_ptr< ::mosek::fusion::Set > shape() /*override*/
{ return mosek::fusion::p_BaseVariable::shape(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2593,std::shared_ptr< monty::ndarray< int,1 > > _2594,std::shared_ptr< monty::ndarray< int,1 > > _2595) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2593,_2594,_2595); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2586,int _2587,int _2588) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2586,_2587,_2588); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag() /*override*/
{ return mosek::fusion::p_BaseVariable::diag(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > index(int _2589,int _2590) /*override*/
{ return mosek::fusion::p_BaseVariable::index(_2589,_2590); }
virtual monty::rc_ptr< ::mosek::fusion::Set > getShape() /*override*/
{ return mosek::fusion::p_BaseVariable::getShape(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > transpose() /*override*/
{ return mosek::fusion::p_BaseVariable::transpose(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > pick(std::shared_ptr< monty::ndarray< int,1 > > _2597,std::shared_ptr< monty::ndarray< int,1 > > _2598) /*override*/
{ return mosek::fusion::p_BaseVariable::pick(_2597,_2598); }
virtual monty::rc_ptr< ::mosek::fusion::Model > getModel() /*override*/
{ return mosek::fusion::p_BaseVariable::getModel(); }
virtual void setLevel(std::shared_ptr< monty::ndarray< double,1 > > _2577) /*override*/
{ mosek::fusion::p_BaseVariable::setLevel(_2577); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > diag(int _2606) /*override*/
{ return mosek::fusion::p_BaseVariable::diag(_2606); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > antidiag(int _2605) /*override*/
{ return mosek::fusion::p_BaseVariable::antidiag(_2605); }
virtual void values(int _2560,std::shared_ptr< monty::ndarray< double,1 > > _2561,bool _2562) /*override*/
{ mosek::fusion::p_BaseVariable::values(_2560,_2561,_2562); }
}; // struct NilVariable;

struct p_Var
{
Var * _pubthis;
static mosek::fusion::p_Var* _get_impl(mosek::fusion::Var * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Var * _get_impl(mosek::fusion::Var::t _inst) { return _get_impl(_inst.get()); }
p_Var(Var * _pubthis);
virtual ~p_Var() { /* std::cout << "~p_Var" << std::endl;*/ };
virtual void destroy();
static  monty::rc_ptr< ::mosek::fusion::Variable > compress(monty::rc_ptr< ::mosek::fusion::Variable > _2689);
static  monty::rc_ptr< ::mosek::fusion::Variable > reshape(monty::rc_ptr< ::mosek::fusion::Variable > _2694,int _2695);
static  monty::rc_ptr< ::mosek::fusion::Variable > reshape(monty::rc_ptr< ::mosek::fusion::Variable > _2696,int _2697,int _2698);
static  monty::rc_ptr< ::mosek::fusion::Variable > flatten(monty::rc_ptr< ::mosek::fusion::Variable > _2699);
static  monty::rc_ptr< ::mosek::fusion::Variable > reshape(monty::rc_ptr< ::mosek::fusion::Variable > _2700,std::shared_ptr< monty::ndarray< int,1 > > _2701);
static  monty::rc_ptr< ::mosek::fusion::Variable > reshape(monty::rc_ptr< ::mosek::fusion::Variable > _2703,monty::rc_ptr< ::mosek::fusion::Set > _2704);
static  monty::rc_ptr< ::mosek::fusion::Variable > reshape_(monty::rc_ptr< ::mosek::fusion::Variable > _2706,monty::rc_ptr< ::mosek::fusion::Set > _2707);
static  monty::rc_ptr< ::mosek::fusion::Variable > index_flip_(monty::rc_ptr< ::mosek::fusion::Variable > _2710,std::shared_ptr< monty::ndarray< int,1 > > _2711);
static  monty::rc_ptr< ::mosek::fusion::Variable > index_permute_(monty::rc_ptr< ::mosek::fusion::Variable > _2718,std::shared_ptr< monty::ndarray< int,1 > > _2719);
static  monty::rc_ptr< ::mosek::fusion::Variable > hrepeat(monty::rc_ptr< ::mosek::fusion::Variable > _2724,int _2725);
static  monty::rc_ptr< ::mosek::fusion::Variable > vrepeat(monty::rc_ptr< ::mosek::fusion::Variable > _2726,int _2727);
static  monty::rc_ptr< ::mosek::fusion::Variable > repeat(monty::rc_ptr< ::mosek::fusion::Variable > _2728,int _2729);
static  monty::rc_ptr< ::mosek::fusion::Variable > repeat(monty::rc_ptr< ::mosek::fusion::Variable > _2730,int _2731,int _2732);
static  monty::rc_ptr< ::mosek::fusion::Variable > drepeat(monty::rc_ptr< ::mosek::fusion::Variable > _2733,int _2734,int _2735);
static  monty::rc_ptr< ::mosek::fusion::Variable > stack(std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > >,1 > > _2740);
static  monty::rc_ptr< ::mosek::fusion::Variable > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _2756,monty::rc_ptr< ::mosek::fusion::Variable > _2757,monty::rc_ptr< ::mosek::fusion::Variable > _2758);
static  monty::rc_ptr< ::mosek::fusion::Variable > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _2759,monty::rc_ptr< ::mosek::fusion::Variable > _2760);
static  monty::rc_ptr< ::mosek::fusion::Variable > vstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _2761);
static  monty::rc_ptr< ::mosek::fusion::Variable > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _2762,monty::rc_ptr< ::mosek::fusion::Variable > _2763,monty::rc_ptr< ::mosek::fusion::Variable > _2764);
static  monty::rc_ptr< ::mosek::fusion::Variable > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _2765,monty::rc_ptr< ::mosek::fusion::Variable > _2766);
static  monty::rc_ptr< ::mosek::fusion::Variable > hstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _2767);
static  monty::rc_ptr< ::mosek::fusion::Variable > stack(monty::rc_ptr< ::mosek::fusion::Variable > _2768,monty::rc_ptr< ::mosek::fusion::Variable > _2769,monty::rc_ptr< ::mosek::fusion::Variable > _2770,int _2771);
static  monty::rc_ptr< ::mosek::fusion::Variable > stack(monty::rc_ptr< ::mosek::fusion::Variable > _2772,monty::rc_ptr< ::mosek::fusion::Variable > _2773,int _2774);
static  monty::rc_ptr< ::mosek::fusion::Variable > stack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _2775,int _2776);
static  monty::rc_ptr< ::mosek::fusion::Variable > dstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _2777,int _2778);
}; // struct Var;

struct p_ConstraintCache
{
ConstraintCache * _pubthis;
static mosek::fusion::p_ConstraintCache* _get_impl(mosek::fusion::ConstraintCache * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_ConstraintCache * _get_impl(mosek::fusion::ConstraintCache::t _inst) { return _get_impl(_inst.get()); }
p_ConstraintCache(ConstraintCache * _pubthis);
virtual ~p_ConstraintCache() { /* std::cout << "~p_ConstraintCache" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > barmatidx{};std::shared_ptr< monty::ndarray< int,1 > > barsubj{};std::shared_ptr< monty::ndarray< int,1 > > barsubi{};long long nbarnz{};long long nunordered{};std::shared_ptr< monty::ndarray< int,1 > > buffer_subi{};std::shared_ptr< monty::ndarray< int,1 > > buffer_subj{};std::shared_ptr< monty::ndarray< double,1 > > buffer_cof{};std::shared_ptr< monty::ndarray< double,1 > > bfix{};std::shared_ptr< monty::ndarray< double,1 > > cof{};std::shared_ptr< monty::ndarray< int,1 > > subi{};std::shared_ptr< monty::ndarray< int,1 > > subj{};long long nnz{};int nrows{};virtual void destroy();
static ConstraintCache::t _new_ConstraintCache(monty::rc_ptr< ::mosek::fusion::ConstraintCache > _3043);
void _initialize(monty::rc_ptr< ::mosek::fusion::ConstraintCache > _3043);
static ConstraintCache::t _new_ConstraintCache(std::shared_ptr< monty::ndarray< long long,1 > > _3044,std::shared_ptr< monty::ndarray< double,1 > > _3045,std::shared_ptr< monty::ndarray< int,1 > > _3046,std::shared_ptr< monty::ndarray< double,1 > > _3047,std::shared_ptr< monty::ndarray< int,1 > > _3048,std::shared_ptr< monty::ndarray< int,1 > > _3049,std::shared_ptr< monty::ndarray< int,1 > > _3050);
void _initialize(std::shared_ptr< monty::ndarray< long long,1 > > _3044,std::shared_ptr< monty::ndarray< double,1 > > _3045,std::shared_ptr< monty::ndarray< int,1 > > _3046,std::shared_ptr< monty::ndarray< double,1 > > _3047,std::shared_ptr< monty::ndarray< int,1 > > _3048,std::shared_ptr< monty::ndarray< int,1 > > _3049,std::shared_ptr< monty::ndarray< int,1 > > _3050);
virtual void unchecked_add_fx(std::shared_ptr< monty::ndarray< double,1 > > _3053);
virtual long long order_barentries();
virtual void add_bar(std::shared_ptr< monty::ndarray< int,1 > > _3063,std::shared_ptr< monty::ndarray< int,1 > > _3064,std::shared_ptr< monty::ndarray< int,1 > > _3065);
virtual void unchecked_add_l(std::shared_ptr< monty::ndarray< long long,1 > > _3071,std::shared_ptr< monty::ndarray< int,1 > > _3072,std::shared_ptr< monty::ndarray< double,1 > > _3073,std::shared_ptr< monty::ndarray< double,1 > > _3074);
virtual void add(std::shared_ptr< monty::ndarray< long long,1 > > _3083,std::shared_ptr< monty::ndarray< int,1 > > _3084,std::shared_ptr< monty::ndarray< double,1 > > _3085,std::shared_ptr< monty::ndarray< double,1 > > _3086);
virtual long long flush(std::shared_ptr< monty::ndarray< int,1 > > _3087,std::shared_ptr< monty::ndarray< int,1 > > _3088,std::shared_ptr< monty::ndarray< double,1 > > _3089,std::shared_ptr< monty::ndarray< double,1 > > _3090);
virtual long long numUnsorted();
virtual monty::rc_ptr< ::mosek::fusion::ConstraintCache > clone();
}; // struct ConstraintCache;

struct p_Constraint
{
Constraint * _pubthis;
static mosek::fusion::p_Constraint* _get_impl(mosek::fusion::Constraint * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Constraint * _get_impl(mosek::fusion::Constraint::t _inst) { return _get_impl(_inst.get()); }
p_Constraint(Constraint * _pubthis);
virtual ~p_Constraint() { /* std::cout << "~p_Constraint" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Set > shape_p{};monty::rc_ptr< ::mosek::fusion::Model > model{};virtual void destroy();
static Constraint::t _new_Constraint(monty::rc_ptr< ::mosek::fusion::Constraint > _3763,monty::rc_ptr< ::mosek::fusion::Model > _3764);
void _initialize(monty::rc_ptr< ::mosek::fusion::Constraint > _3763,monty::rc_ptr< ::mosek::fusion::Model > _3764);
static Constraint::t _new_Constraint(monty::rc_ptr< ::mosek::fusion::Model > _3765,monty::rc_ptr< ::mosek::fusion::Set > _3766);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _3765,monty::rc_ptr< ::mosek::fusion::Set > _3766);
virtual std::string toString();
virtual void toStringArray(std::shared_ptr< monty::ndarray< long long,1 > > _3772,long long _3773,std::shared_ptr< monty::ndarray< std::string,1 > > _3774) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Constraint > add(double _3775);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > add(std::shared_ptr< monty::ndarray< double,1 > > _3780);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > add(monty::rc_ptr< ::mosek::fusion::Variable > _3784);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > add(monty::rc_ptr< ::mosek::fusion::Expression > _3793);
static  void inst(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _3800,std::shared_ptr< monty::ndarray< long long,1 > > _3801,std::shared_ptr< monty::ndarray< int,1 > > _3802,std::shared_ptr< monty::ndarray< int,1 > > _3803,std::shared_ptr< monty::ndarray< int,1 > > _3804);
virtual void add_l(std::shared_ptr< monty::ndarray< long long,1 > > _3812,std::shared_ptr< monty::ndarray< long long,1 > > _3813,std::shared_ptr< monty::ndarray< int,1 > > _3814,std::shared_ptr< monty::ndarray< int,1 > > _3815,std::shared_ptr< monty::ndarray< int,1 > > _3816,std::shared_ptr< monty::ndarray< double,1 > > _3817,std::shared_ptr< monty::ndarray< double,1 > > _3818,long long _3819,int _3820,int _3821) { throw monty::AbstractClassError("Call to abstract method"); }
virtual std::shared_ptr< monty::ndarray< double,1 > > dual(std::shared_ptr< monty::ndarray< int,1 > > _3822,std::shared_ptr< monty::ndarray< int,1 > > _3823);
virtual std::shared_ptr< monty::ndarray< double,1 > > dual(int _3831,int _3832);
virtual std::shared_ptr< monty::ndarray< double,1 > > dual();
virtual void dual_values(int _3836,std::shared_ptr< monty::ndarray< double,1 > > _3837);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _3842,int _3843,std::shared_ptr< monty::ndarray< double,1 > > _3844) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void dual_values(long long _3845,std::shared_ptr< monty::ndarray< int,1 > > _3846,std::shared_ptr< monty::ndarray< long long,1 > > _3847,int _3848,std::shared_ptr< monty::ndarray< double,1 > > _3849) { throw monty::AbstractClassError("Call to abstract method"); }
virtual std::shared_ptr< monty::ndarray< double,1 > > level();
virtual double level(int _3851);
virtual std::shared_ptr< monty::ndarray< double,1 > > level(std::shared_ptr< monty::ndarray< int,1 > > _3854,std::shared_ptr< monty::ndarray< int,1 > > _3855);
virtual std::shared_ptr< monty::ndarray< double,1 > > level(int _3865,int _3866);
virtual void level_values(int _3871,std::shared_ptr< monty::ndarray< double,1 > > _3872);
virtual void level_values(std::shared_ptr< monty::ndarray< long long,1 > > _3877,int _3878,std::shared_ptr< monty::ndarray< double,1 > > _3879) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void level_values(long long _3880,std::shared_ptr< monty::ndarray< int,1 > > _3881,std::shared_ptr< monty::ndarray< long long,1 > > _3882,int _3883,std::shared_ptr< monty::ndarray< double,1 > > _3884) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Model > get_model();
virtual int get_nd();
virtual long long size();
static  monty::rc_ptr< ::mosek::fusion::Constraint > stack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _3885);
static  monty::rc_ptr< ::mosek::fusion::Constraint > stack(monty::rc_ptr< ::mosek::fusion::Constraint > _3886,monty::rc_ptr< ::mosek::fusion::Constraint > _3887,monty::rc_ptr< ::mosek::fusion::Constraint > _3888);
static  monty::rc_ptr< ::mosek::fusion::Constraint > stack(monty::rc_ptr< ::mosek::fusion::Constraint > _3890,monty::rc_ptr< ::mosek::fusion::Constraint > _3891);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > index(std::shared_ptr< monty::ndarray< int,1 > > _3893);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > index(int _3895);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice(std::shared_ptr< monty::ndarray< int,1 > > _3896,std::shared_ptr< monty::ndarray< int,1 > > _3897) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice(int _3898,int _3899) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Constraint > reduceDims();
virtual monty::rc_ptr< ::mosek::fusion::Set > shape();
}; // struct Constraint;

struct p_CompoundConstraint : public ::mosek::fusion::p_Constraint
{
CompoundConstraint * _pubthis;
static mosek::fusion::p_CompoundConstraint* _get_impl(mosek::fusion::CompoundConstraint * _inst){ return static_cast< mosek::fusion::p_CompoundConstraint* >(mosek::fusion::p_Constraint::_get_impl(_inst)); }
static mosek::fusion::p_CompoundConstraint * _get_impl(mosek::fusion::CompoundConstraint::t _inst) { return _get_impl(_inst.get()); }
p_CompoundConstraint(CompoundConstraint * _pubthis);
virtual ~p_CompoundConstraint() { /* std::cout << "~p_CompoundConstraint" << std::endl;*/ };
int stackdim{};std::shared_ptr< monty::ndarray< int,1 > > consb{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > cons{};virtual void destroy();
static CompoundConstraint::t _new_CompoundConstraint(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _3113);
void _initialize(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _3113);
virtual void toStringArray(std::shared_ptr< monty::ndarray< long long,1 > > _3120,long long _3121,std::shared_ptr< monty::ndarray< std::string,1 > > _3122);
virtual void add_l(std::shared_ptr< monty::ndarray< long long,1 > > _3123,std::shared_ptr< monty::ndarray< long long,1 > > _3124,std::shared_ptr< monty::ndarray< int,1 > > _3125,std::shared_ptr< monty::ndarray< int,1 > > _3126,std::shared_ptr< monty::ndarray< int,1 > > _3127,std::shared_ptr< monty::ndarray< double,1 > > _3128,std::shared_ptr< monty::ndarray< double,1 > > _3129,long long _3130,int _3131,int _3132);
virtual void dual_values(long long _3157,std::shared_ptr< monty::ndarray< int,1 > > _3158,std::shared_ptr< monty::ndarray< long long,1 > > _3159,int _3160,std::shared_ptr< monty::ndarray< double,1 > > _3161);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _3178,int _3179,std::shared_ptr< monty::ndarray< double,1 > > _3180);
virtual void level_values(long long _3187,std::shared_ptr< monty::ndarray< int,1 > > _3188,std::shared_ptr< monty::ndarray< long long,1 > > _3189,int _3190,std::shared_ptr< monty::ndarray< double,1 > > _3191);
virtual void level_values(std::shared_ptr< monty::ndarray< long long,1 > > _3208,int _3209,std::shared_ptr< monty::ndarray< double,1 > > _3210);
virtual void add(std::shared_ptr< monty::ndarray< long long,1 > > _3217,std::shared_ptr< monty::ndarray< int,1 > > _3218,std::shared_ptr< monty::ndarray< double,1 > > _3219,std::shared_ptr< monty::ndarray< double,1 > > _3220,int _3221,std::shared_ptr< monty::ndarray< int,1 > > _3222,int _3223);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice(std::shared_ptr< monty::ndarray< int,1 > > _3224,std::shared_ptr< monty::ndarray< int,1 > > _3225);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice(int _3226,int _3227);
static  monty::rc_ptr< ::mosek::fusion::Set > compute_shape(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _3228,int _3229);
static  int count_numcon(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _3236);
static  monty::rc_ptr< ::mosek::fusion::Model > model_from_con(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _3242);
}; // struct CompoundConstraint;

struct p_SliceConstraint : public ::mosek::fusion::p_Constraint
{
SliceConstraint * _pubthis;
static mosek::fusion::p_SliceConstraint* _get_impl(mosek::fusion::SliceConstraint * _inst){ return static_cast< mosek::fusion::p_SliceConstraint* >(mosek::fusion::p_Constraint::_get_impl(_inst)); }
static mosek::fusion::p_SliceConstraint * _get_impl(mosek::fusion::SliceConstraint::t _inst) { return _get_impl(_inst.get()); }
p_SliceConstraint(SliceConstraint * _pubthis);
virtual ~p_SliceConstraint() { /* std::cout << "~p_SliceConstraint" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > strides{};long long first{};monty::rc_ptr< ::mosek::fusion::ModelConstraint > origin{};virtual void destroy();
static SliceConstraint::t _new_SliceConstraint(monty::rc_ptr< ::mosek::fusion::ModelConstraint > _3259,monty::rc_ptr< ::mosek::fusion::Set > _3260,long long _3261,std::shared_ptr< monty::ndarray< long long,1 > > _3262);
void _initialize(monty::rc_ptr< ::mosek::fusion::ModelConstraint > _3259,monty::rc_ptr< ::mosek::fusion::Set > _3260,long long _3261,std::shared_ptr< monty::ndarray< long long,1 > > _3262);
virtual void add_l(std::shared_ptr< monty::ndarray< long long,1 > > _3263,std::shared_ptr< monty::ndarray< long long,1 > > _3264,std::shared_ptr< monty::ndarray< int,1 > > _3265,std::shared_ptr< monty::ndarray< int,1 > > _3266,std::shared_ptr< monty::ndarray< int,1 > > _3267,std::shared_ptr< monty::ndarray< double,1 > > _3268,std::shared_ptr< monty::ndarray< double,1 > > _3269,long long _3270,int _3271,int _3272);
virtual void add_fx(std::shared_ptr< monty::ndarray< long long,1 > > _3283,std::shared_ptr< monty::ndarray< double,1 > > _3284,long long _3285,int _3286,int _3287);
virtual void dual_values(long long _3294,std::shared_ptr< monty::ndarray< int,1 > > _3295,std::shared_ptr< monty::ndarray< long long,1 > > _3296,int _3297,std::shared_ptr< monty::ndarray< double,1 > > _3298);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _3321,int _3322,std::shared_ptr< monty::ndarray< double,1 > > _3323);
virtual void level_values(long long _3329,std::shared_ptr< monty::ndarray< int,1 > > _3330,std::shared_ptr< monty::ndarray< long long,1 > > _3331,int _3332,std::shared_ptr< monty::ndarray< double,1 > > _3333);
virtual void level_values(std::shared_ptr< monty::ndarray< long long,1 > > _3355,int _3356,std::shared_ptr< monty::ndarray< double,1 > > _3357);
virtual void toStringArray(std::shared_ptr< monty::ndarray< long long,1 > > _3363,long long _3364,std::shared_ptr< monty::ndarray< std::string,1 > > _3365);
virtual long long size();
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice(std::shared_ptr< monty::ndarray< int,1 > > _3371,std::shared_ptr< monty::ndarray< int,1 > > _3372);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice(int _3376,int _3377);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice_(monty::rc_ptr< ::mosek::fusion::Set > _3379,long long _3380,std::shared_ptr< monty::ndarray< long long,1 > > _3381);
}; // struct SliceConstraint;

struct p_BoundInterfaceConstraint : public ::mosek::fusion::p_SliceConstraint
{
BoundInterfaceConstraint * _pubthis;
static mosek::fusion::p_BoundInterfaceConstraint* _get_impl(mosek::fusion::BoundInterfaceConstraint * _inst){ return static_cast< mosek::fusion::p_BoundInterfaceConstraint* >(mosek::fusion::p_SliceConstraint::_get_impl(_inst)); }
static mosek::fusion::p_BoundInterfaceConstraint * _get_impl(mosek::fusion::BoundInterfaceConstraint::t _inst) { return _get_impl(_inst.get()); }
p_BoundInterfaceConstraint(BoundInterfaceConstraint * _pubthis);
virtual ~p_BoundInterfaceConstraint() { /* std::cout << "~p_BoundInterfaceConstraint" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::RangedConstraint > origincon{};bool islower{};virtual void destroy();
static BoundInterfaceConstraint::t _new_BoundInterfaceConstraint(monty::rc_ptr< ::mosek::fusion::RangedConstraint > _3243,monty::rc_ptr< ::mosek::fusion::Set > _3244,long long _3245,std::shared_ptr< monty::ndarray< long long,1 > > _3246,bool _3247);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangedConstraint > _3243,monty::rc_ptr< ::mosek::fusion::Set > _3244,long long _3245,std::shared_ptr< monty::ndarray< long long,1 > > _3246,bool _3247);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice_(monty::rc_ptr< ::mosek::fusion::Set > _3248,long long _3249,std::shared_ptr< monty::ndarray< long long,1 > > _3250);
virtual void dual_values(long long _3251,std::shared_ptr< monty::ndarray< int,1 > > _3252,std::shared_ptr< monty::ndarray< long long,1 > > _3253,int _3254,std::shared_ptr< monty::ndarray< double,1 > > _3255);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _3256,int _3257,std::shared_ptr< monty::ndarray< double,1 > > _3258);
}; // struct BoundInterfaceConstraint;

struct p_ModelConstraint : public ::mosek::fusion::p_Constraint
{
ModelConstraint * _pubthis;
static mosek::fusion::p_ModelConstraint* _get_impl(mosek::fusion::ModelConstraint * _inst){ return static_cast< mosek::fusion::p_ModelConstraint* >(mosek::fusion::p_Constraint::_get_impl(_inst)); }
static mosek::fusion::p_ModelConstraint * _get_impl(mosek::fusion::ModelConstraint::t _inst) { return _get_impl(_inst.get()); }
p_ModelConstraint(ModelConstraint * _pubthis);
virtual ~p_ModelConstraint() { /* std::cout << "~p_ModelConstraint" << std::endl;*/ };
bool names_flushed{};std::shared_ptr< monty::ndarray< int,1 > > nativeindexes{};std::string name{};std::shared_ptr< monty::ndarray< double,1 > > cache_bfix{};monty::rc_ptr< ::mosek::fusion::ConstraintCache > cache{};virtual void destroy();
static ModelConstraint::t _new_ModelConstraint(monty::rc_ptr< ::mosek::fusion::ModelConstraint > _3649,monty::rc_ptr< ::mosek::fusion::Model > _3650);
void _initialize(monty::rc_ptr< ::mosek::fusion::ModelConstraint > _3649,monty::rc_ptr< ::mosek::fusion::Model > _3650);
static ModelConstraint::t _new_ModelConstraint(monty::rc_ptr< ::mosek::fusion::Model > _3653,const std::string &  _3654,monty::rc_ptr< ::mosek::fusion::Set > _3655,std::shared_ptr< monty::ndarray< int,1 > > _3656,std::shared_ptr< monty::ndarray< long long,1 > > _3657,std::shared_ptr< monty::ndarray< int,1 > > _3658,std::shared_ptr< monty::ndarray< double,1 > > _3659,std::shared_ptr< monty::ndarray< double,1 > > _3660,std::shared_ptr< monty::ndarray< int,1 > > _3661,std::shared_ptr< monty::ndarray< int,1 > > _3662,std::shared_ptr< monty::ndarray< int,1 > > _3663);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _3653,const std::string &  _3654,monty::rc_ptr< ::mosek::fusion::Set > _3655,std::shared_ptr< monty::ndarray< int,1 > > _3656,std::shared_ptr< monty::ndarray< long long,1 > > _3657,std::shared_ptr< monty::ndarray< int,1 > > _3658,std::shared_ptr< monty::ndarray< double,1 > > _3659,std::shared_ptr< monty::ndarray< double,1 > > _3660,std::shared_ptr< monty::ndarray< int,1 > > _3661,std::shared_ptr< monty::ndarray< int,1 > > _3662,std::shared_ptr< monty::ndarray< int,1 > > _3663);
virtual void flushNames();
virtual std::string toString();
virtual void toStringArray(std::shared_ptr< monty::ndarray< long long,1 > > _3670,long long _3671,std::shared_ptr< monty::ndarray< std::string,1 > > _3672);
virtual void domainToString(long long _3688,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _3689) { throw monty::AbstractClassError("Call to abstract method"); }
virtual void add_l(std::shared_ptr< monty::ndarray< long long,1 > > _3690,std::shared_ptr< monty::ndarray< long long,1 > > _3691,std::shared_ptr< monty::ndarray< int,1 > > _3692,std::shared_ptr< monty::ndarray< int,1 > > _3693,std::shared_ptr< monty::ndarray< int,1 > > _3694,std::shared_ptr< monty::ndarray< double,1 > > _3695,std::shared_ptr< monty::ndarray< double,1 > > _3696,long long _3697,int _3698,int _3699);
virtual void add_fx(std::shared_ptr< monty::ndarray< long long,1 > > _3747,std::shared_ptr< monty::ndarray< double,1 > > _3748,long long _3749,int _3750,int _3751) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice(std::shared_ptr< monty::ndarray< int,1 > > _3752,std::shared_ptr< monty::ndarray< int,1 > > _3753);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > slice(int _3759,int _3760);
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > clone(monty::rc_ptr< ::mosek::fusion::Model > _3762) { throw monty::AbstractClassError("Call to abstract method"); }
}; // struct ModelConstraint;

struct p_LinearPSDConstraint : public ::mosek::fusion::p_ModelConstraint
{
LinearPSDConstraint * _pubthis;
static mosek::fusion::p_LinearPSDConstraint* _get_impl(mosek::fusion::LinearPSDConstraint * _inst){ return static_cast< mosek::fusion::p_LinearPSDConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_LinearPSDConstraint * _get_impl(mosek::fusion::LinearPSDConstraint::t _inst) { return _get_impl(_inst.get()); }
p_LinearPSDConstraint(LinearPSDConstraint * _pubthis);
virtual ~p_LinearPSDConstraint() { /* std::cout << "~p_LinearPSDConstraint" << std::endl;*/ };
int psdvardim{};bool names_flushed{};int numcones{};int conesize{};int coneidx{};virtual void destroy();
static LinearPSDConstraint::t _new_LinearPSDConstraint(monty::rc_ptr< ::mosek::fusion::LinearPSDConstraint > _2792,monty::rc_ptr< ::mosek::fusion::Model > _2793);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearPSDConstraint > _2792,monty::rc_ptr< ::mosek::fusion::Model > _2793);
static LinearPSDConstraint::t _new_LinearPSDConstraint(monty::rc_ptr< ::mosek::fusion::Model > _2794,const std::string &  _2795,monty::rc_ptr< ::mosek::fusion::Set > _2796,std::shared_ptr< monty::ndarray< int,1 > > _2797,int _2798,int _2799,int _2800,std::shared_ptr< monty::ndarray< long long,1 > > _2801,std::shared_ptr< monty::ndarray< int,1 > > _2802,std::shared_ptr< monty::ndarray< double,1 > > _2803,std::shared_ptr< monty::ndarray< double,1 > > _2804,std::shared_ptr< monty::ndarray< int,1 > > _2805,std::shared_ptr< monty::ndarray< int,1 > > _2806,std::shared_ptr< monty::ndarray< int,1 > > _2807);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2794,const std::string &  _2795,monty::rc_ptr< ::mosek::fusion::Set > _2796,std::shared_ptr< monty::ndarray< int,1 > > _2797,int _2798,int _2799,int _2800,std::shared_ptr< monty::ndarray< long long,1 > > _2801,std::shared_ptr< monty::ndarray< int,1 > > _2802,std::shared_ptr< monty::ndarray< double,1 > > _2803,std::shared_ptr< monty::ndarray< double,1 > > _2804,std::shared_ptr< monty::ndarray< int,1 > > _2805,std::shared_ptr< monty::ndarray< int,1 > > _2806,std::shared_ptr< monty::ndarray< int,1 > > _2807);
virtual void domainToString(long long _2810,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2811);
virtual std::string toString();
virtual void toStringArray(std::shared_ptr< monty::ndarray< long long,1 > > _2821,long long _2822,std::shared_ptr< monty::ndarray< std::string,1 > > _2823);
virtual void toStringArray(std::shared_ptr< monty::ndarray< long long,1 > > _2824,long long _2825,std::shared_ptr< monty::ndarray< std::string,1 > > _2826,bool _2827);
virtual void flushNames();
virtual void add_fx(std::shared_ptr< monty::ndarray< long long,1 > > _2855,std::shared_ptr< monty::ndarray< double,1 > > _2856,long long _2857,int _2858,int _2859);
virtual void dual_values(long long _2864,std::shared_ptr< monty::ndarray< int,1 > > _2865,std::shared_ptr< monty::ndarray< long long,1 > > _2866,int _2867,std::shared_ptr< monty::ndarray< double,1 > > _2868);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _2877,int _2878,std::shared_ptr< monty::ndarray< double,1 > > _2879);
virtual void level_values(long long _2885,std::shared_ptr< monty::ndarray< int,1 > > _2886,std::shared_ptr< monty::ndarray< long long,1 > > _2887,int _2888,std::shared_ptr< monty::ndarray< double,1 > > _2889);
virtual void level_values(std::shared_ptr< monty::ndarray< long long,1 > > _2898,int _2899,std::shared_ptr< monty::ndarray< double,1 > > _2900);
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > clone(monty::rc_ptr< ::mosek::fusion::Model > _2906);
}; // struct LinearPSDConstraint;

struct p_PSDConstraint : public ::mosek::fusion::p_ModelConstraint
{
PSDConstraint * _pubthis;
static mosek::fusion::p_PSDConstraint* _get_impl(mosek::fusion::PSDConstraint * _inst){ return static_cast< mosek::fusion::p_PSDConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_PSDConstraint * _get_impl(mosek::fusion::PSDConstraint::t _inst) { return _get_impl(_inst.get()); }
p_PSDConstraint(PSDConstraint * _pubthis);
virtual ~p_PSDConstraint() { /* std::cout << "~p_PSDConstraint" << std::endl;*/ };
bool names_flushed{};int numcones{};int conesize{};int coneidx{};virtual void destroy();
static PSDConstraint::t _new_PSDConstraint(monty::rc_ptr< ::mosek::fusion::PSDConstraint > _2907,monty::rc_ptr< ::mosek::fusion::Model > _2908);
void _initialize(monty::rc_ptr< ::mosek::fusion::PSDConstraint > _2907,monty::rc_ptr< ::mosek::fusion::Model > _2908);
static PSDConstraint::t _new_PSDConstraint(monty::rc_ptr< ::mosek::fusion::Model > _2909,const std::string &  _2910,monty::rc_ptr< ::mosek::fusion::Set > _2911,std::shared_ptr< monty::ndarray< int,1 > > _2912,int _2913,int _2914,int _2915,std::shared_ptr< monty::ndarray< long long,1 > > _2916,std::shared_ptr< monty::ndarray< int,1 > > _2917,std::shared_ptr< monty::ndarray< double,1 > > _2918,std::shared_ptr< monty::ndarray< double,1 > > _2919,std::shared_ptr< monty::ndarray< int,1 > > _2920,std::shared_ptr< monty::ndarray< int,1 > > _2921,std::shared_ptr< monty::ndarray< int,1 > > _2922);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2909,const std::string &  _2910,monty::rc_ptr< ::mosek::fusion::Set > _2911,std::shared_ptr< monty::ndarray< int,1 > > _2912,int _2913,int _2914,int _2915,std::shared_ptr< monty::ndarray< long long,1 > > _2916,std::shared_ptr< monty::ndarray< int,1 > > _2917,std::shared_ptr< monty::ndarray< double,1 > > _2918,std::shared_ptr< monty::ndarray< double,1 > > _2919,std::shared_ptr< monty::ndarray< int,1 > > _2920,std::shared_ptr< monty::ndarray< int,1 > > _2921,std::shared_ptr< monty::ndarray< int,1 > > _2922);
virtual void domainToString(long long _2923,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2924);
virtual std::string toString();
virtual void toStringArray(std::shared_ptr< monty::ndarray< long long,1 > > _2934,long long _2935,std::shared_ptr< monty::ndarray< std::string,1 > > _2936);
virtual void toStringArray(std::shared_ptr< monty::ndarray< long long,1 > > _2937,long long _2938,std::shared_ptr< monty::ndarray< std::string,1 > > _2939,bool _2940);
virtual void flushNames();
virtual void add_fx(std::shared_ptr< monty::ndarray< long long,1 > > _2973,std::shared_ptr< monty::ndarray< double,1 > > _2974,long long _2975,int _2976,int _2977);
virtual void dual_values(long long _2982,std::shared_ptr< monty::ndarray< int,1 > > _2983,std::shared_ptr< monty::ndarray< long long,1 > > _2984,int _2985,std::shared_ptr< monty::ndarray< double,1 > > _2986);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _3002,int _3003,std::shared_ptr< monty::ndarray< double,1 > > _3004);
virtual void level_values(long long _3012,std::shared_ptr< monty::ndarray< int,1 > > _3013,std::shared_ptr< monty::ndarray< long long,1 > > _3014,int _3015,std::shared_ptr< monty::ndarray< double,1 > > _3016);
virtual void level_values(std::shared_ptr< monty::ndarray< long long,1 > > _3032,int _3033,std::shared_ptr< monty::ndarray< double,1 > > _3034);
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > clone(monty::rc_ptr< ::mosek::fusion::Model > _3042);
}; // struct PSDConstraint;

struct p_RangedConstraint : public ::mosek::fusion::p_ModelConstraint
{
RangedConstraint * _pubthis;
static mosek::fusion::p_RangedConstraint* _get_impl(mosek::fusion::RangedConstraint * _inst){ return static_cast< mosek::fusion::p_RangedConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_RangedConstraint * _get_impl(mosek::fusion::RangedConstraint::t _inst) { return _get_impl(_inst.get()); }
p_RangedConstraint(RangedConstraint * _pubthis);
virtual ~p_RangedConstraint() { /* std::cout << "~p_RangedConstraint" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Utils::IntMap > idxmap{};monty::rc_ptr< ::mosek::fusion::RangeDomain > dom{};virtual void destroy();
static RangedConstraint::t _new_RangedConstraint(monty::rc_ptr< ::mosek::fusion::RangedConstraint > _3382,monty::rc_ptr< ::mosek::fusion::Model > _3383);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangedConstraint > _3382,monty::rc_ptr< ::mosek::fusion::Model > _3383);
static RangedConstraint::t _new_RangedConstraint(monty::rc_ptr< ::mosek::fusion::Model > _3384,const std::string &  _3385,monty::rc_ptr< ::mosek::fusion::Set > _3386,monty::rc_ptr< ::mosek::fusion::RangeDomain > _3387,std::shared_ptr< monty::ndarray< int,1 > > _3388,std::shared_ptr< monty::ndarray< long long,1 > > _3389,std::shared_ptr< monty::ndarray< int,1 > > _3390,std::shared_ptr< monty::ndarray< double,1 > > _3391,std::shared_ptr< monty::ndarray< double,1 > > _3392,std::shared_ptr< monty::ndarray< int,1 > > _3393,std::shared_ptr< monty::ndarray< int,1 > > _3394,std::shared_ptr< monty::ndarray< int,1 > > _3395);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _3384,const std::string &  _3385,monty::rc_ptr< ::mosek::fusion::Set > _3386,monty::rc_ptr< ::mosek::fusion::RangeDomain > _3387,std::shared_ptr< monty::ndarray< int,1 > > _3388,std::shared_ptr< monty::ndarray< long long,1 > > _3389,std::shared_ptr< monty::ndarray< int,1 > > _3390,std::shared_ptr< monty::ndarray< double,1 > > _3391,std::shared_ptr< monty::ndarray< double,1 > > _3392,std::shared_ptr< monty::ndarray< int,1 > > _3393,std::shared_ptr< monty::ndarray< int,1 > > _3394,std::shared_ptr< monty::ndarray< int,1 > > _3395);
virtual void add_fx(std::shared_ptr< monty::ndarray< long long,1 > > _3396,std::shared_ptr< monty::ndarray< double,1 > > _3397,long long _3398,int _3399,int _3400);
virtual void dual_u(long long _3406,std::shared_ptr< monty::ndarray< int,1 > > _3407,std::shared_ptr< monty::ndarray< long long,1 > > _3408,int _3409,std::shared_ptr< monty::ndarray< double,1 > > _3410);
virtual void dual_u(std::shared_ptr< monty::ndarray< long long,1 > > _3418,int _3419,std::shared_ptr< monty::ndarray< double,1 > > _3420);
virtual void dual_l(long long _3424,std::shared_ptr< monty::ndarray< int,1 > > _3425,std::shared_ptr< monty::ndarray< long long,1 > > _3426,int _3427,std::shared_ptr< monty::ndarray< double,1 > > _3428);
virtual void dual_l(std::shared_ptr< monty::ndarray< long long,1 > > _3436,int _3437,std::shared_ptr< monty::ndarray< double,1 > > _3438);
virtual void dual_values(long long _3442,std::shared_ptr< monty::ndarray< int,1 > > _3443,std::shared_ptr< monty::ndarray< long long,1 > > _3444,int _3445,std::shared_ptr< monty::ndarray< double,1 > > _3446);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _3454,int _3455,std::shared_ptr< monty::ndarray< double,1 > > _3456);
virtual void level_values(long long _3460,std::shared_ptr< monty::ndarray< int,1 > > _3461,std::shared_ptr< monty::ndarray< long long,1 > > _3462,int _3463,std::shared_ptr< monty::ndarray< double,1 > > _3464);
virtual void level_values(std::shared_ptr< monty::ndarray< long long,1 > > _3472,int _3473,std::shared_ptr< monty::ndarray< double,1 > > _3474);
virtual void add_l(std::shared_ptr< monty::ndarray< long long,1 > > _3478,std::shared_ptr< monty::ndarray< long long,1 > > _3479,std::shared_ptr< monty::ndarray< int,1 > > _3480,std::shared_ptr< monty::ndarray< int,1 > > _3481,std::shared_ptr< monty::ndarray< int,1 > > _3482,std::shared_ptr< monty::ndarray< double,1 > > _3483,std::shared_ptr< monty::ndarray< double,1 > > _3484,int _3485,int _3486,int _3487);
virtual void domainToString(long long _3493,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _3494);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > upperBoundCon();
virtual monty::rc_ptr< ::mosek::fusion::Constraint > lowerBoundCon();
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > clone(monty::rc_ptr< ::mosek::fusion::Model > _3499);
}; // struct RangedConstraint;

struct p_ConicConstraint : public ::mosek::fusion::p_ModelConstraint
{
ConicConstraint * _pubthis;
static mosek::fusion::p_ConicConstraint* _get_impl(mosek::fusion::ConicConstraint * _inst){ return static_cast< mosek::fusion::p_ConicConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_ConicConstraint * _get_impl(mosek::fusion::ConicConstraint::t _inst) { return _get_impl(_inst.get()); }
p_ConicConstraint(ConicConstraint * _pubthis);
virtual ~p_ConicConstraint() { /* std::cout << "~p_ConicConstraint" << std::endl;*/ };
bool names_flushed{};monty::rc_ptr< ::mosek::fusion::QConeDomain > dom{};int conesize{};int last{};int first{};int last_slack{};int first_slack{};int coneidx{};virtual void destroy();
static ConicConstraint::t _new_ConicConstraint(monty::rc_ptr< ::mosek::fusion::ConicConstraint > _3500,monty::rc_ptr< ::mosek::fusion::Model > _3501);
void _initialize(monty::rc_ptr< ::mosek::fusion::ConicConstraint > _3500,monty::rc_ptr< ::mosek::fusion::Model > _3501);
static ConicConstraint::t _new_ConicConstraint(monty::rc_ptr< ::mosek::fusion::Model > _3502,const std::string &  _3503,monty::rc_ptr< ::mosek::fusion::QConeDomain > _3504,monty::rc_ptr< ::mosek::fusion::Set > _3505,std::shared_ptr< monty::ndarray< int,1 > > _3506,int _3507,int _3508,int _3509,int _3510,int _3511,std::shared_ptr< monty::ndarray< long long,1 > > _3512,std::shared_ptr< monty::ndarray< int,1 > > _3513,std::shared_ptr< monty::ndarray< double,1 > > _3514,std::shared_ptr< monty::ndarray< double,1 > > _3515,std::shared_ptr< monty::ndarray< int,1 > > _3516,std::shared_ptr< monty::ndarray< int,1 > > _3517,std::shared_ptr< monty::ndarray< int,1 > > _3518);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _3502,const std::string &  _3503,monty::rc_ptr< ::mosek::fusion::QConeDomain > _3504,monty::rc_ptr< ::mosek::fusion::Set > _3505,std::shared_ptr< monty::ndarray< int,1 > > _3506,int _3507,int _3508,int _3509,int _3510,int _3511,std::shared_ptr< monty::ndarray< long long,1 > > _3512,std::shared_ptr< monty::ndarray< int,1 > > _3513,std::shared_ptr< monty::ndarray< double,1 > > _3514,std::shared_ptr< monty::ndarray< double,1 > > _3515,std::shared_ptr< monty::ndarray< int,1 > > _3516,std::shared_ptr< monty::ndarray< int,1 > > _3517,std::shared_ptr< monty::ndarray< int,1 > > _3518);
virtual void flushNames();
virtual std::string toString();
virtual void dual_values(long long _3526,std::shared_ptr< monty::ndarray< int,1 > > _3527,std::shared_ptr< monty::ndarray< long long,1 > > _3528,int _3529,std::shared_ptr< monty::ndarray< double,1 > > _3530);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _3537,int _3538,std::shared_ptr< monty::ndarray< double,1 > > _3539);
virtual void level_values(long long _3542,std::shared_ptr< monty::ndarray< int,1 > > _3543,std::shared_ptr< monty::ndarray< long long,1 > > _3544,int _3545,std::shared_ptr< monty::ndarray< double,1 > > _3546);
virtual void level_values(std::shared_ptr< monty::ndarray< long long,1 > > _3554,int _3555,std::shared_ptr< monty::ndarray< double,1 > > _3556);
virtual void add_fx(std::shared_ptr< monty::ndarray< long long,1 > > _3560,std::shared_ptr< monty::ndarray< double,1 > > _3561,long long _3562,int _3563,int _3564);
virtual void dual(std::shared_ptr< monty::ndarray< int,1 > > _3569,int _3570,int _3571,int _3572,std::shared_ptr< monty::ndarray< double,1 > > _3573);
virtual void dual_values(std::shared_ptr< monty::ndarray< int,1 > > _3576,std::shared_ptr< monty::ndarray< int,1 > > _3577,int _3578,std::shared_ptr< monty::ndarray< double,1 > > _3579);
virtual void domainToString(long long _3584,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _3585);
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > clone(monty::rc_ptr< ::mosek::fusion::Model > _3586);
}; // struct ConicConstraint;

struct p_LinearConstraint : public ::mosek::fusion::p_ModelConstraint
{
LinearConstraint * _pubthis;
static mosek::fusion::p_LinearConstraint* _get_impl(mosek::fusion::LinearConstraint * _inst){ return static_cast< mosek::fusion::p_LinearConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_LinearConstraint * _get_impl(mosek::fusion::LinearConstraint::t _inst) { return _get_impl(_inst.get()); }
p_LinearConstraint(LinearConstraint * _pubthis);
virtual ~p_LinearConstraint() { /* std::cout << "~p_LinearConstraint" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::LinearDomain > dom{};monty::rc_ptr< ::mosek::fusion::Utils::IntMap > idxmap{};virtual void destroy();
static LinearConstraint::t _new_LinearConstraint(monty::rc_ptr< ::mosek::fusion::LinearConstraint > _3587,monty::rc_ptr< ::mosek::fusion::Model > _3588);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearConstraint > _3587,monty::rc_ptr< ::mosek::fusion::Model > _3588);
static LinearConstraint::t _new_LinearConstraint(monty::rc_ptr< ::mosek::fusion::Model > _3589,const std::string &  _3590,monty::rc_ptr< ::mosek::fusion::LinearDomain > _3591,monty::rc_ptr< ::mosek::fusion::Set > _3592,std::shared_ptr< monty::ndarray< int,1 > > _3593,std::shared_ptr< monty::ndarray< long long,1 > > _3594,std::shared_ptr< monty::ndarray< int,1 > > _3595,std::shared_ptr< monty::ndarray< double,1 > > _3596,std::shared_ptr< monty::ndarray< double,1 > > _3597,std::shared_ptr< monty::ndarray< int,1 > > _3598,std::shared_ptr< monty::ndarray< int,1 > > _3599,std::shared_ptr< monty::ndarray< int,1 > > _3600);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _3589,const std::string &  _3590,monty::rc_ptr< ::mosek::fusion::LinearDomain > _3591,monty::rc_ptr< ::mosek::fusion::Set > _3592,std::shared_ptr< monty::ndarray< int,1 > > _3593,std::shared_ptr< monty::ndarray< long long,1 > > _3594,std::shared_ptr< monty::ndarray< int,1 > > _3595,std::shared_ptr< monty::ndarray< double,1 > > _3596,std::shared_ptr< monty::ndarray< double,1 > > _3597,std::shared_ptr< monty::ndarray< int,1 > > _3598,std::shared_ptr< monty::ndarray< int,1 > > _3599,std::shared_ptr< monty::ndarray< int,1 > > _3600);
virtual void add_fx(std::shared_ptr< monty::ndarray< long long,1 > > _3601,std::shared_ptr< monty::ndarray< double,1 > > _3602,long long _3603,int _3604,int _3605);
virtual void dual_values(long long _3610,std::shared_ptr< monty::ndarray< int,1 > > _3611,std::shared_ptr< monty::ndarray< long long,1 > > _3612,int _3613,std::shared_ptr< monty::ndarray< double,1 > > _3614);
virtual void dual_values(std::shared_ptr< monty::ndarray< long long,1 > > _3622,int _3623,std::shared_ptr< monty::ndarray< double,1 > > _3624);
virtual void level_values(long long _3628,std::shared_ptr< monty::ndarray< int,1 > > _3629,std::shared_ptr< monty::ndarray< long long,1 > > _3630,int _3631,std::shared_ptr< monty::ndarray< double,1 > > _3632);
virtual void level_values(std::shared_ptr< monty::ndarray< long long,1 > > _3640,int _3641,std::shared_ptr< monty::ndarray< double,1 > > _3642);
virtual void domainToString(long long _3646,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _3647);
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > clone(monty::rc_ptr< ::mosek::fusion::Model > _3648);
}; // struct LinearConstraint;

struct p_Set
{
Set * _pubthis;
static mosek::fusion::p_Set* _get_impl(mosek::fusion::Set * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Set * _get_impl(mosek::fusion::Set::t _inst) { return _get_impl(_inst.get()); }
p_Set(Set * _pubthis);
virtual ~p_Set() { /* std::cout << "~p_Set" << std::endl;*/ };
long long size{};int nd_p{};int nd{};virtual void destroy();
static Set::t _new_Set(int _3991,long long _3992);
void _initialize(int _3991,long long _3992);
virtual std::string toString();
virtual std::string indexToString(long long _3995) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Set > slice(std::shared_ptr< monty::ndarray< int,1 > > _3996,std::shared_ptr< monty::ndarray< int,1 > > _3997) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Set > slice(int _3998,int _3999) { throw monty::AbstractClassError("Call to abstract method"); }
virtual long long linearidx(int _4000,int _4001,int _4002);
virtual long long linearidx(int _4003,int _4004);
virtual long long linearidx(std::shared_ptr< monty::ndarray< int,1 > > _4005);
virtual std::shared_ptr< monty::ndarray< int,1 > > idxtokey(long long _4008);
virtual std::string getname(std::shared_ptr< monty::ndarray< int,1 > > _4012) { throw monty::AbstractClassError("Call to abstract method"); }
virtual std::string getname(long long _4013) { throw monty::AbstractClassError("Call to abstract method"); }
virtual long long stride(int _4014) { throw monty::AbstractClassError("Call to abstract method"); }
virtual int dim(int _4015) { throw monty::AbstractClassError("Call to abstract method"); }
static  monty::rc_ptr< ::mosek::fusion::Set > make(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Set >,1 > > _4016);
static  monty::rc_ptr< ::mosek::fusion::Set > make(monty::rc_ptr< ::mosek::fusion::Set > _4017,monty::rc_ptr< ::mosek::fusion::Set > _4018);
static  monty::rc_ptr< ::mosek::fusion::Set > make(std::shared_ptr< monty::ndarray< int,1 > > _4019);
static  monty::rc_ptr< ::mosek::fusion::Set > make(int _4020,int _4021,int _4022);
static  monty::rc_ptr< ::mosek::fusion::Set > make(int _4023,int _4024);
static  monty::rc_ptr< ::mosek::fusion::Set > make(int _4025);
static  monty::rc_ptr< ::mosek::fusion::Set > scalar();
static  monty::rc_ptr< ::mosek::fusion::Set > make(std::shared_ptr< monty::ndarray< std::string,1 > > _4026);
virtual int realnd();
virtual long long getSize();
virtual bool compare(monty::rc_ptr< ::mosek::fusion::Set > _4029);
}; // struct Set;

struct p_BaseSet : public ::mosek::fusion::p_Set
{
BaseSet * _pubthis;
static mosek::fusion::p_BaseSet* _get_impl(mosek::fusion::BaseSet * _inst){ return static_cast< mosek::fusion::p_BaseSet* >(mosek::fusion::p_Set::_get_impl(_inst)); }
static mosek::fusion::p_BaseSet * _get_impl(mosek::fusion::BaseSet::t _inst) { return _get_impl(_inst.get()); }
p_BaseSet(BaseSet * _pubthis);
virtual ~p_BaseSet() { /* std::cout << "~p_BaseSet" << std::endl;*/ };
virtual void destroy();
static BaseSet::t _new_BaseSet(long long _3950);
void _initialize(long long _3950);
virtual int dim(int _3951);
}; // struct BaseSet;

struct p_IntSet : public ::mosek::fusion::p_BaseSet
{
IntSet * _pubthis;
static mosek::fusion::p_IntSet* _get_impl(mosek::fusion::IntSet * _inst){ return static_cast< mosek::fusion::p_IntSet* >(mosek::fusion::p_BaseSet::_get_impl(_inst)); }
static mosek::fusion::p_IntSet * _get_impl(mosek::fusion::IntSet::t _inst) { return _get_impl(_inst.get()); }
p_IntSet(IntSet * _pubthis);
virtual ~p_IntSet() { /* std::cout << "~p_IntSet" << std::endl;*/ };
int last{};int first{};virtual void destroy();
static IntSet::t _new_IntSet(int _3922);
void _initialize(int _3922);
static IntSet::t _new_IntSet(int _3923,int _3924);
void _initialize(int _3923,int _3924);
virtual std::string indexToString(long long _3925);
virtual std::string getname(std::shared_ptr< monty::ndarray< int,1 > > _3926);
virtual std::string getname(long long _3927);
virtual monty::rc_ptr< ::mosek::fusion::Set > slice(std::shared_ptr< monty::ndarray< int,1 > > _3928,std::shared_ptr< monty::ndarray< int,1 > > _3929);
virtual monty::rc_ptr< ::mosek::fusion::Set > slice(int _3930,int _3931);
virtual int getidx(int _3932);
virtual long long stride(int _3933);
}; // struct IntSet;

struct p_StringSet : public ::mosek::fusion::p_BaseSet
{
StringSet * _pubthis;
static mosek::fusion::p_StringSet* _get_impl(mosek::fusion::StringSet * _inst){ return static_cast< mosek::fusion::p_StringSet* >(mosek::fusion::p_BaseSet::_get_impl(_inst)); }
static mosek::fusion::p_StringSet * _get_impl(mosek::fusion::StringSet::t _inst) { return _get_impl(_inst.get()); }
p_StringSet(StringSet * _pubthis);
virtual ~p_StringSet() { /* std::cout << "~p_StringSet" << std::endl;*/ };
std::shared_ptr< monty::ndarray< std::string,1 > > keys{};virtual void destroy();
static StringSet::t _new_StringSet(std::shared_ptr< monty::ndarray< std::string,1 > > _3934);
void _initialize(std::shared_ptr< monty::ndarray< std::string,1 > > _3934);
virtual std::string indexToString(long long _3935);
virtual std::string getname(std::shared_ptr< monty::ndarray< int,1 > > _3936);
virtual std::string getname(long long _3937);
virtual monty::rc_ptr< ::mosek::fusion::BaseSet > slice_(std::shared_ptr< monty::ndarray< int,1 > > _3938,std::shared_ptr< monty::ndarray< int,1 > > _3939);
virtual monty::rc_ptr< ::mosek::fusion::BaseSet > slice_(int _3940,int _3941);
virtual monty::rc_ptr< ::mosek::fusion::Set > slice(std::shared_ptr< monty::ndarray< int,1 > > _3943,std::shared_ptr< monty::ndarray< int,1 > > _3944);
virtual monty::rc_ptr< ::mosek::fusion::Set > slice(int _3945,int _3946);
virtual std::string toString();
virtual long long stride(int _3949);
}; // struct StringSet;

struct p_NDSet : public ::mosek::fusion::p_Set
{
NDSet * _pubthis;
static mosek::fusion::p_NDSet* _get_impl(mosek::fusion::NDSet * _inst){ return static_cast< mosek::fusion::p_NDSet* >(mosek::fusion::p_Set::_get_impl(_inst)); }
static mosek::fusion::p_NDSet * _get_impl(mosek::fusion::NDSet::t _inst) { return _get_impl(_inst.get()); }
p_NDSet(NDSet * _pubthis);
virtual ~p_NDSet() { /* std::cout << "~p_NDSet" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > strides{};std::shared_ptr< monty::ndarray< int,1 > > dimdef{};virtual void destroy();
static NDSet::t _new_NDSet(int _3952,int _3953,int _3954);
void _initialize(int _3952,int _3953,int _3954);
static NDSet::t _new_NDSet(int _3955,int _3956);
void _initialize(int _3955,int _3956);
static NDSet::t _new_NDSet(std::shared_ptr< monty::ndarray< int,1 > > _3957);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _3957);
virtual std::string indexToString(long long _3961);
virtual std::string getname(std::shared_ptr< monty::ndarray< int,1 > > _3965);
virtual std::string getname(long long _3969);
virtual int dim(int _3974);
virtual monty::rc_ptr< ::mosek::fusion::Set > slice(std::shared_ptr< monty::ndarray< int,1 > > _3975,std::shared_ptr< monty::ndarray< int,1 > > _3976);
virtual monty::rc_ptr< ::mosek::fusion::Set > slice(int _3980,int _3981);
virtual std::shared_ptr< monty::ndarray< int,1 > > selectidxs(std::shared_ptr< monty::ndarray< std::string,1 > > _3982);
virtual int linear_index_in_dim(int _3983,std::shared_ptr< monty::ndarray< int,1 > > _3984);
virtual int linear_index_in_dim(int _3985,int _3986);
static  long long sumdims(std::shared_ptr< monty::ndarray< int,1 > > _3987);
virtual long long stride(int _3990);
}; // struct NDSet;

struct p_ProductSet : public ::mosek::fusion::p_NDSet
{
ProductSet * _pubthis;
static mosek::fusion::p_ProductSet* _get_impl(mosek::fusion::ProductSet * _inst){ return static_cast< mosek::fusion::p_ProductSet* >(mosek::fusion::p_NDSet::_get_impl(_inst)); }
static mosek::fusion::p_ProductSet * _get_impl(mosek::fusion::ProductSet::t _inst) { return _get_impl(_inst.get()); }
p_ProductSet(ProductSet * _pubthis);
virtual ~p_ProductSet() { /* std::cout << "~p_ProductSet" << std::endl;*/ };
std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Set >,1 > > sets{};virtual void destroy();
static ProductSet::t _new_ProductSet(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Set >,1 > > _3904);
void _initialize(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Set >,1 > > _3904);
virtual std::string indexToString(long long _3906);
static  std::shared_ptr< monty::ndarray< int,1 > > computedims(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Set >,1 > > _3916);
}; // struct ProductSet;

struct p_QConeDomain
{
QConeDomain * _pubthis;
static mosek::fusion::p_QConeDomain* _get_impl(mosek::fusion::QConeDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_QConeDomain * _get_impl(mosek::fusion::QConeDomain::t _inst) { return _get_impl(_inst.get()); }
p_QConeDomain(QConeDomain * _pubthis);
virtual ~p_QConeDomain() { /* std::cout << "~p_QConeDomain" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Set > shape{};bool int_flag{};int axisidx{};mosek::fusion::QConeKey key{};virtual void destroy();
static QConeDomain::t _new_QConeDomain(mosek::fusion::QConeKey _4032,std::shared_ptr< monty::ndarray< int,1 > > _4033,int _4034);
void _initialize(mosek::fusion::QConeKey _4032,std::shared_ptr< monty::ndarray< int,1 > > _4033,int _4034);
virtual std::string domainToString(long long _4035,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _4036);
virtual bool match_shape(monty::rc_ptr< ::mosek::fusion::Set > _4043);
virtual monty::rc_ptr< ::mosek::fusion::QConeDomain > integral();
virtual int getAxis();
virtual monty::rc_ptr< ::mosek::fusion::QConeDomain > axis(int _4044);
}; // struct QConeDomain;

struct p_LinPSDDomain
{
LinPSDDomain * _pubthis;
static mosek::fusion::p_LinPSDDomain* _get_impl(mosek::fusion::LinPSDDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_LinPSDDomain * _get_impl(mosek::fusion::LinPSDDomain::t _inst) { return _get_impl(_inst.get()); }
p_LinPSDDomain(LinPSDDomain * _pubthis);
virtual ~p_LinPSDDomain() { /* std::cout << "~p_LinPSDDomain" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Set > shape{};virtual void destroy();
static LinPSDDomain::t _new_LinPSDDomain(monty::rc_ptr< ::mosek::fusion::Set > _4045);
void _initialize(monty::rc_ptr< ::mosek::fusion::Set > _4045);
}; // struct LinPSDDomain;

struct p_PSDDomain
{
PSDDomain * _pubthis;
static mosek::fusion::p_PSDDomain* _get_impl(mosek::fusion::PSDDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_PSDDomain * _get_impl(mosek::fusion::PSDDomain::t _inst) { return _get_impl(_inst.get()); }
p_PSDDomain(PSDDomain * _pubthis);
virtual ~p_PSDDomain() { /* std::cout << "~p_PSDDomain" << std::endl;*/ };
mosek::fusion::PSDKey key{};monty::rc_ptr< ::mosek::fusion::Set > shape{};virtual void destroy();
static PSDDomain::t _new_PSDDomain(mosek::fusion::PSDKey _4046,monty::rc_ptr< ::mosek::fusion::Set > _4047);
void _initialize(mosek::fusion::PSDKey _4046,monty::rc_ptr< ::mosek::fusion::Set > _4047);
virtual std::string domainToString(long long _4048,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _4049);
}; // struct PSDDomain;

struct p_RangeDomain
{
RangeDomain * _pubthis;
static mosek::fusion::p_RangeDomain* _get_impl(mosek::fusion::RangeDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_RangeDomain * _get_impl(mosek::fusion::RangeDomain::t _inst) { return _get_impl(_inst.get()); }
p_RangeDomain(RangeDomain * _pubthis);
virtual ~p_RangeDomain() { /* std::cout << "~p_RangeDomain" << std::endl;*/ };
bool sparse_flag{};bool cardinal_flag{};std::shared_ptr< monty::ndarray< double,1 > > ub{};std::shared_ptr< monty::ndarray< double,1 > > lb{};monty::rc_ptr< ::mosek::fusion::Utils::IntMap > idxmap{};monty::rc_ptr< ::mosek::fusion::Set > shape{};virtual void destroy();
static RangeDomain::t _new_RangeDomain(std::shared_ptr< monty::ndarray< double,1 > > _4054,std::shared_ptr< monty::ndarray< double,1 > > _4055,std::shared_ptr< monty::ndarray< int,1 > > _4056,std::shared_ptr< monty::ndarray< long long,1 > > _4057);
void _initialize(std::shared_ptr< monty::ndarray< double,1 > > _4054,std::shared_ptr< monty::ndarray< double,1 > > _4055,std::shared_ptr< monty::ndarray< int,1 > > _4056,std::shared_ptr< monty::ndarray< long long,1 > > _4057);
static RangeDomain::t _new_RangeDomain(monty::rc_ptr< ::mosek::fusion::RangeDomain > _4059);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangeDomain > _4059);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricRangeDomain > symmetric();
virtual monty::rc_ptr< ::mosek::fusion::RangeDomain > sparse();
virtual monty::rc_ptr< ::mosek::fusion::RangeDomain > integral();
virtual std::string domainToString(long long _4060,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _4061);
virtual bool match_shape(monty::rc_ptr< ::mosek::fusion::Set > _4062);
virtual double get_ub_item(long long _4063);
virtual double get_lb_item(long long _4064);
}; // struct RangeDomain;

struct p_SymmetricRangeDomain : public ::mosek::fusion::p_RangeDomain
{
SymmetricRangeDomain * _pubthis;
static mosek::fusion::p_SymmetricRangeDomain* _get_impl(mosek::fusion::SymmetricRangeDomain * _inst){ return static_cast< mosek::fusion::p_SymmetricRangeDomain* >(mosek::fusion::p_RangeDomain::_get_impl(_inst)); }
static mosek::fusion::p_SymmetricRangeDomain * _get_impl(mosek::fusion::SymmetricRangeDomain::t _inst) { return _get_impl(_inst.get()); }
p_SymmetricRangeDomain(SymmetricRangeDomain * _pubthis);
virtual ~p_SymmetricRangeDomain() { /* std::cout << "~p_SymmetricRangeDomain" << std::endl;*/ };
int dim{};virtual void destroy();
static SymmetricRangeDomain::t _new_SymmetricRangeDomain(monty::rc_ptr< ::mosek::fusion::RangeDomain > _4053);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangeDomain > _4053);
}; // struct SymmetricRangeDomain;

struct p_SymmetricLinearDomain
{
SymmetricLinearDomain * _pubthis;
static mosek::fusion::p_SymmetricLinearDomain* _get_impl(mosek::fusion::SymmetricLinearDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_SymmetricLinearDomain * _get_impl(mosek::fusion::SymmetricLinearDomain::t _inst) { return _get_impl(_inst.get()); }
p_SymmetricLinearDomain(SymmetricLinearDomain * _pubthis);
virtual ~p_SymmetricLinearDomain() { /* std::cout << "~p_SymmetricLinearDomain" << std::endl;*/ };
bool sparse_flag{};bool cardinal_flag{};mosek::fusion::RelationKey key{};monty::rc_ptr< ::mosek::fusion::Set > shape{};monty::rc_ptr< ::mosek::fusion::LinearDomain > dom{};int dim{};virtual void destroy();
static SymmetricLinearDomain::t _new_SymmetricLinearDomain(monty::rc_ptr< ::mosek::fusion::LinearDomain > _4065);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearDomain > _4065);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > sparse();
virtual monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > integral();
virtual std::string domainToString(long long _4066,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _4067);
virtual bool match_shape(monty::rc_ptr< ::mosek::fusion::Set > _4068);
virtual double get_rhs_item(long long _4069);
}; // struct SymmetricLinearDomain;

struct p_LinearDomain
{
LinearDomain * _pubthis;
static mosek::fusion::p_LinearDomain* _get_impl(mosek::fusion::LinearDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_LinearDomain * _get_impl(mosek::fusion::LinearDomain::t _inst) { return _get_impl(_inst.get()); }
p_LinearDomain(LinearDomain * _pubthis);
virtual ~p_LinearDomain() { /* std::cout << "~p_LinearDomain" << std::endl;*/ };
bool sparse_flag{};bool cardinal_flag{};mosek::fusion::RelationKey key{};std::shared_ptr< monty::ndarray< double,1 > > bnd{};monty::rc_ptr< ::mosek::fusion::Utils::IntMap > inst{};monty::rc_ptr< ::mosek::fusion::Set > shape{};virtual void destroy();
static LinearDomain::t _new_LinearDomain(mosek::fusion::RelationKey _4070,std::shared_ptr< monty::ndarray< double,1 > > _4071,std::shared_ptr< monty::ndarray< long long,1 > > _4072,std::shared_ptr< monty::ndarray< int,1 > > _4073);
void _initialize(mosek::fusion::RelationKey _4070,std::shared_ptr< monty::ndarray< double,1 > > _4071,std::shared_ptr< monty::ndarray< long long,1 > > _4072,std::shared_ptr< monty::ndarray< int,1 > > _4073);
static LinearDomain::t _new_LinearDomain(monty::rc_ptr< ::mosek::fusion::LinearDomain > _4075);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearDomain > _4075);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > symmetric();
virtual monty::rc_ptr< ::mosek::fusion::LinearDomain > sparse();
virtual monty::rc_ptr< ::mosek::fusion::LinearDomain > integral();
virtual std::string domainToString(long long _4076,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _4077);
virtual bool match_shape(monty::rc_ptr< ::mosek::fusion::Set > _4078);
virtual double get_rhs_item(long long _4079);
virtual bool scalable();
}; // struct LinearDomain;

struct p_Domain
{
Domain * _pubthis;
static mosek::fusion::p_Domain* _get_impl(mosek::fusion::Domain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Domain * _get_impl(mosek::fusion::Domain::t _inst) { return _get_impl(_inst.get()); }
p_Domain(Domain * _pubthis);
virtual ~p_Domain() { /* std::cout << "~p_Domain" << std::endl;*/ };
virtual void destroy();
static  long long dimsize(std::shared_ptr< monty::ndarray< int,1 > > _4080);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > mkLinearDomain(mosek::fusion::RelationKey _4083,monty::rc_ptr< ::mosek::fusion::Matrix > _4084);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > mkLinearDomain(mosek::fusion::RelationKey _4090,std::shared_ptr< monty::ndarray< double,2 > > _4091);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > mkLinearDomain(mosek::fusion::RelationKey _4094,std::shared_ptr< monty::ndarray< double,1 > > _4095,std::shared_ptr< monty::ndarray< int,1 > > _4096);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > mkLinearDomain(mosek::fusion::RelationKey _4099,std::shared_ptr< monty::ndarray< double,1 > > _4100);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > mkLinearDomain(mosek::fusion::RelationKey _4102,double _4103,std::shared_ptr< monty::ndarray< int,1 > > _4104);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > mkLinearDomain(mosek::fusion::RelationKey _4107,double _4108);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(std::shared_ptr< monty::ndarray< double,1 > > _4109,std::shared_ptr< monty::ndarray< double,1 > > _4110,std::shared_ptr< monty::ndarray< int,1 > > _4111);
static  monty::rc_ptr< ::mosek::fusion::SymmetricRangeDomain > symmetric(monty::rc_ptr< ::mosek::fusion::RangeDomain > _4113);
static  monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > symmetric(monty::rc_ptr< ::mosek::fusion::LinearDomain > _4114);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > sparse(monty::rc_ptr< ::mosek::fusion::RangeDomain > _4115);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > sparse(monty::rc_ptr< ::mosek::fusion::LinearDomain > _4116);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > integral(monty::rc_ptr< ::mosek::fusion::RangeDomain > _4117);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > integral(monty::rc_ptr< ::mosek::fusion::LinearDomain > _4118);
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > integral(monty::rc_ptr< ::mosek::fusion::QConeDomain > _4119);
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > axis(monty::rc_ptr< ::mosek::fusion::QConeDomain > _4120,int _4121);
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > inRotatedQCone(std::shared_ptr< monty::ndarray< int,1 > > _4122);
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > inRotatedQCone(int _4124,int _4125);
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > inRotatedQCone(int _4126);
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > inRotatedQCone();
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > inQCone(std::shared_ptr< monty::ndarray< int,1 > > _4127);
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > inQCone(int _4129,int _4130);
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > inQCone(int _4131);
static  monty::rc_ptr< ::mosek::fusion::QConeDomain > inQCone();
static  monty::rc_ptr< ::mosek::fusion::LinPSDDomain > isLinPSD(int _4132,int _4133);
static  monty::rc_ptr< ::mosek::fusion::LinPSDDomain > isLinPSD(int _4134);
static  monty::rc_ptr< ::mosek::fusion::LinPSDDomain > isLinPSD();
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > isTrilPSD(int _4135,int _4136);
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > isTrilPSD(int _4137);
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > isTrilPSD();
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > inPSDCone(int _4138,int _4139);
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > inPSDCone(int _4140);
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > inPSDCone();
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > binary();
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > binary(std::shared_ptr< monty::ndarray< int,1 > > _4141);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > binary(int _4144,int _4145);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > binary(int _4148);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(monty::rc_ptr< ::mosek::fusion::Matrix > _4151,monty::rc_ptr< ::mosek::fusion::Matrix > _4152);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(monty::rc_ptr< ::mosek::fusion::Matrix > _4153,double _4154);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(double _4156,monty::rc_ptr< ::mosek::fusion::Matrix > _4157);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(std::shared_ptr< monty::ndarray< double,1 > > _4159,std::shared_ptr< monty::ndarray< double,1 > > _4160);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(std::shared_ptr< monty::ndarray< double,1 > > _4161,double _4162);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(double _4164,std::shared_ptr< monty::ndarray< double,1 > > _4165);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(double _4167,double _4168);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(monty::rc_ptr< ::mosek::fusion::Matrix > _4169);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(std::shared_ptr< monty::ndarray< double,1 > > _4170,std::shared_ptr< monty::ndarray< int,1 > > _4171);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(std::shared_ptr< monty::ndarray< double,2 > > _4172);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(std::shared_ptr< monty::ndarray< double,1 > > _4173);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(double _4174,std::shared_ptr< monty::ndarray< int,1 > > _4175);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(double _4176,int _4177,int _4178);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(double _4179,int _4180);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(double _4181);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(monty::rc_ptr< ::mosek::fusion::Matrix > _4182);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(std::shared_ptr< monty::ndarray< double,1 > > _4183,std::shared_ptr< monty::ndarray< int,1 > > _4184);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(std::shared_ptr< monty::ndarray< double,2 > > _4185);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(std::shared_ptr< monty::ndarray< double,1 > > _4186);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(double _4187,std::shared_ptr< monty::ndarray< int,1 > > _4188);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(double _4189,int _4190,int _4191);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(double _4192,int _4193);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(double _4194);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(monty::rc_ptr< ::mosek::fusion::Matrix > _4195);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(std::shared_ptr< monty::ndarray< double,1 > > _4196,std::shared_ptr< monty::ndarray< int,1 > > _4197);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(std::shared_ptr< monty::ndarray< double,2 > > _4198);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(std::shared_ptr< monty::ndarray< double,1 > > _4199);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(double _4200,std::shared_ptr< monty::ndarray< int,1 > > _4201);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(double _4202,int _4203,int _4204);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(double _4205,int _4206);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(double _4207);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > unbounded(std::shared_ptr< monty::ndarray< int,1 > > _4208);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > unbounded(int _4210,int _4211);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > unbounded(int _4212);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > unbounded();
}; // struct Domain;

struct p_SymmetricExpr
{
SymmetricExpr * _pubthis;
static mosek::fusion::p_SymmetricExpr* _get_impl(mosek::fusion::SymmetricExpr * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_SymmetricExpr * _get_impl(mosek::fusion::SymmetricExpr::t _inst) { return _get_impl(_inst.get()); }
p_SymmetricExpr(SymmetricExpr * _pubthis);
virtual ~p_SymmetricExpr() { /* std::cout << "~p_SymmetricExpr" << std::endl;*/ };
std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > xs{};monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > b{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::SymmetricMatrix >,1 > > Ms{};int n{};virtual void destroy();
static SymmetricExpr::t _new_SymmetricExpr(int _4221,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::SymmetricMatrix >,1 > > _4222,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4223,monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _4224);
void _initialize(int _4221,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::SymmetricMatrix >,1 > > _4222,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4223,monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _4224);
static  monty::rc_ptr< ::mosek::fusion::SymmetricExpr > add(monty::rc_ptr< ::mosek::fusion::SymmetricExpr > _4225,monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _4226);
static  monty::rc_ptr< ::mosek::fusion::SymmetricExpr > mul(monty::rc_ptr< ::mosek::fusion::SymmetricExpr > _4227,double _4228);
static  monty::rc_ptr< ::mosek::fusion::SymmetricExpr > add(monty::rc_ptr< ::mosek::fusion::SymmetricExpr > _4230,monty::rc_ptr< ::mosek::fusion::SymmetricExpr > _4231);
virtual std::string toString();
}; // struct SymmetricExpr;

struct p_Expr : public /*implements*/ ::mosek::fusion::Expression
{
Expr * _pubthis;
static mosek::fusion::p_Expr* _get_impl(mosek::fusion::Expr * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Expr * _get_impl(mosek::fusion::Expr::t _inst) { return _get_impl(_inst.get()); }
p_Expr(Expr * _pubthis);
virtual ~p_Expr() { /* std::cout << "~p_Expr" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > varsb{};std::shared_ptr< monty::ndarray< long long,1 > > inst{};std::shared_ptr< monty::ndarray< double,1 > > cof_v{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > x{};std::shared_ptr< monty::ndarray< long long,1 > > subj{};std::shared_ptr< monty::ndarray< long long,1 > > ptrb{};std::shared_ptr< monty::ndarray< double,1 > > bfix{};monty::rc_ptr< ::mosek::fusion::Set > shape_p{};monty::rc_ptr< ::mosek::fusion::Model > model{};virtual void destroy();
static Expr::t _new_Expr(std::shared_ptr< monty::ndarray< long long,1 > > _4242,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4243,std::shared_ptr< monty::ndarray< long long,1 > > _4244,std::shared_ptr< monty::ndarray< double,1 > > _4245,std::shared_ptr< monty::ndarray< double,1 > > _4246,monty::rc_ptr< ::mosek::fusion::Set > _4247,std::shared_ptr< monty::ndarray< long long,1 > > _4248);
void _initialize(std::shared_ptr< monty::ndarray< long long,1 > > _4242,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4243,std::shared_ptr< monty::ndarray< long long,1 > > _4244,std::shared_ptr< monty::ndarray< double,1 > > _4245,std::shared_ptr< monty::ndarray< double,1 > > _4246,monty::rc_ptr< ::mosek::fusion::Set > _4247,std::shared_ptr< monty::ndarray< long long,1 > > _4248);
static Expr::t _new_Expr(std::shared_ptr< monty::ndarray< long long,1 > > _4252,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4253,std::shared_ptr< monty::ndarray< long long,1 > > _4254,std::shared_ptr< monty::ndarray< double,1 > > _4255,std::shared_ptr< monty::ndarray< double,1 > > _4256,monty::rc_ptr< ::mosek::fusion::Set > _4257,std::shared_ptr< monty::ndarray< long long,1 > > _4258,int _4259);
void _initialize(std::shared_ptr< monty::ndarray< long long,1 > > _4252,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4253,std::shared_ptr< monty::ndarray< long long,1 > > _4254,std::shared_ptr< monty::ndarray< double,1 > > _4255,std::shared_ptr< monty::ndarray< double,1 > > _4256,monty::rc_ptr< ::mosek::fusion::Set > _4257,std::shared_ptr< monty::ndarray< long long,1 > > _4258,int _4259);
static Expr::t _new_Expr(monty::rc_ptr< ::mosek::fusion::Expression > _4261);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _4261);
virtual std::string toString();
virtual void tostr(monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _4270,int _4271);
static  std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > varstack(std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > >,1 > > _4277);
static  std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > varstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4280,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4281);
static  monty::rc_ptr< ::mosek::fusion::Expression > flatten(monty::rc_ptr< ::mosek::fusion::Expression > _4285);
static  monty::rc_ptr< ::mosek::fusion::Expression > reshape(monty::rc_ptr< ::mosek::fusion::Expression > _4286,int _4287,int _4288);
static  monty::rc_ptr< ::mosek::fusion::Expression > reshape(monty::rc_ptr< ::mosek::fusion::Expression > _4289,int _4290);
static  monty::rc_ptr< ::mosek::fusion::Expression > reshape(monty::rc_ptr< ::mosek::fusion::Expression > _4291,monty::rc_ptr< ::mosek::fusion::Set > _4292);
virtual long long size();
virtual monty::rc_ptr< ::mosek::fusion::FlatExpr > eval();
static  monty::rc_ptr< ::mosek::fusion::Expression > zeros(int _4298);
static  monty::rc_ptr< ::mosek::fusion::Expression > ones(int _4304);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _4309);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(monty::rc_ptr< ::mosek::fusion::Matrix > _4317);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(double _4329);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(monty::rc_ptr< ::mosek::fusion::Set > _4335,double _4336);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(int _4342,double _4343);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(std::shared_ptr< monty::ndarray< double,2 > > _4349);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(std::shared_ptr< monty::ndarray< double,1 > > _4359);
virtual long long numNonzeros();
static  monty::rc_ptr< ::mosek::fusion::Expression > sum_expr(monty::rc_ptr< ::mosek::fusion::Expression > _4365,int _4366,int _4367);
static  monty::rc_ptr< ::mosek::fusion::Expression > sum_var(monty::rc_ptr< ::mosek::fusion::Variable > _4413,int _4414,int _4415);
static  monty::rc_ptr< ::mosek::fusion::Expression > sum(monty::rc_ptr< ::mosek::fusion::Expression > _4445,int _4446,int _4447);
static  monty::rc_ptr< ::mosek::fusion::Expression > sum(monty::rc_ptr< ::mosek::fusion::Expression > _4448,int _4449);
static  monty::rc_ptr< ::mosek::fusion::Expression > sum(monty::rc_ptr< ::mosek::fusion::Variable > _4450,int _4451,int _4452);
static  monty::rc_ptr< ::mosek::fusion::Expression > sum(monty::rc_ptr< ::mosek::fusion::Variable > _4453,int _4454);
static  monty::rc_ptr< ::mosek::fusion::Expression > sum(monty::rc_ptr< ::mosek::fusion::Variable > _4455);
static  monty::rc_ptr< ::mosek::fusion::Expression > sum(monty::rc_ptr< ::mosek::fusion::Expression > _4456);
static  monty::rc_ptr< ::mosek::fusion::Expression > neg(monty::rc_ptr< ::mosek::fusion::Variable > _4464);
static  monty::rc_ptr< ::mosek::fusion::Expression > neg(monty::rc_ptr< ::mosek::fusion::Expression > _4469);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul__(monty::rc_ptr< ::mosek::fusion::Matrix > _4475,monty::rc_ptr< ::mosek::fusion::Expression > _4476);
static  void sparseMatrixVector(std::shared_ptr< monty::ndarray< long long,1 > > _4588,std::shared_ptr< monty::ndarray< int,1 > > _4589,std::shared_ptr< monty::ndarray< double,1 > > _4590,std::shared_ptr< monty::ndarray< double,1 > > _4591,std::shared_ptr< monty::ndarray< double,1 > > _4592,int _4593);
static  void sparseMatmul(std::shared_ptr< monty::ndarray< long long,1 > > _4598,std::shared_ptr< monty::ndarray< int,1 > > _4599,std::shared_ptr< monty::ndarray< double,1 > > _4600,std::shared_ptr< monty::ndarray< long long,1 > > _4601,std::shared_ptr< monty::ndarray< int,1 > > _4602,std::shared_ptr< monty::ndarray< double,1 > > _4603,std::shared_ptr< monty::ndarray< long long,1 > > _4604,std::shared_ptr< monty::ndarray< int,1 > > _4605,std::shared_ptr< monty::ndarray< double,1 > > _4606,int _4607,int _4608,std::shared_ptr< monty::ndarray< int,1 > > _4609);
static  long long computeNz(std::shared_ptr< monty::ndarray< long long,1 > > _4621,std::shared_ptr< monty::ndarray< int,1 > > _4622,std::shared_ptr< monty::ndarray< long long,1 > > _4623,std::shared_ptr< monty::ndarray< int,1 > > _4624,int _4625,int _4626,std::shared_ptr< monty::ndarray< int,1 > > _4627,std::shared_ptr< monty::ndarray< long long,1 > > _4628);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Variable > _4637,monty::rc_ptr< ::mosek::fusion::Matrix > _4638);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Matrix > _4663,monty::rc_ptr< ::mosek::fusion::Variable > _4664);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Expression > _4683,monty::rc_ptr< ::mosek::fusion::Matrix > _4684);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Matrix > _4767,monty::rc_ptr< ::mosek::fusion::Expression > _4768);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Variable > _4833,std::shared_ptr< monty::ndarray< double,2 > > _4834);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(std::shared_ptr< monty::ndarray< double,2 > > _4835,monty::rc_ptr< ::mosek::fusion::Variable > _4836);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Expression > _4837,std::shared_ptr< monty::ndarray< double,2 > > _4838);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(std::shared_ptr< monty::ndarray< double,2 > > _4839,monty::rc_ptr< ::mosek::fusion::Expression > _4840);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm_(monty::rc_ptr< ::mosek::fusion::Matrix > _4841,monty::rc_ptr< ::mosek::fusion::Expression > _4842);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm_(monty::rc_ptr< ::mosek::fusion::Matrix > _4850,monty::rc_ptr< ::mosek::fusion::Variable > _4851);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm_(std::shared_ptr< monty::ndarray< double,1 > > _4858,monty::rc_ptr< ::mosek::fusion::Variable > _4859);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm_(std::shared_ptr< monty::ndarray< double,1 > > _4860,monty::rc_ptr< ::mosek::fusion::Expression > _4861);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm_(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _4863,monty::rc_ptr< ::mosek::fusion::Expression > _4864);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm_(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _4869,monty::rc_ptr< ::mosek::fusion::Variable > _4870);
static  monty::rc_ptr< ::mosek::fusion::Expression > dotmul_(std::shared_ptr< monty::ndarray< long long,1 > > _4872,std::shared_ptr< monty::ndarray< double,1 > > _4873,monty::rc_ptr< ::mosek::fusion::Variable > _4874,monty::rc_ptr< ::mosek::fusion::Set > _4875);
static  monty::rc_ptr< ::mosek::fusion::Expression > dotmul_(std::shared_ptr< monty::ndarray< long long,1 > > _4881,std::shared_ptr< monty::ndarray< double,1 > > _4882,std::shared_ptr< monty::ndarray< long long,1 > > _4883,std::shared_ptr< monty::ndarray< long long,1 > > _4884,std::shared_ptr< monty::ndarray< double,1 > > _4885,std::shared_ptr< monty::ndarray< double,1 > > _4886,std::shared_ptr< monty::ndarray< long long,1 > > _4887,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4888,monty::rc_ptr< ::mosek::fusion::Set > _4889);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Matrix > _4910,monty::rc_ptr< ::mosek::fusion::Expression > _4911);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Expression > _4924,monty::rc_ptr< ::mosek::fusion::Matrix > _4925);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Expression > _4938,std::shared_ptr< monty::ndarray< double,1 > > _4939);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(std::shared_ptr< monty::ndarray< double,1 > > _4947,monty::rc_ptr< ::mosek::fusion::Expression > _4948);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(double _4956,monty::rc_ptr< ::mosek::fusion::Expression > _4957);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Expression > _4961,double _4962);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul_SMatrix_2DSExpr(std::shared_ptr< monty::ndarray< long long,1 > > _4963,std::shared_ptr< monty::ndarray< long long,1 > > _4964,std::shared_ptr< monty::ndarray< double,1 > > _4965,std::shared_ptr< monty::ndarray< double,1 > > _4966,std::shared_ptr< monty::ndarray< long long,1 > > _4967,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4968,monty::rc_ptr< ::mosek::fusion::Set > _4969,int _4970,int _4971,std::shared_ptr< monty::ndarray< int,1 > > _4972,std::shared_ptr< monty::ndarray< int,1 > > _4973,std::shared_ptr< monty::ndarray< double,1 > > _4974,int _4975,int _4976);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul_2DSExpr_SMatrix(std::shared_ptr< monty::ndarray< long long,1 > > _5028,std::shared_ptr< monty::ndarray< long long,1 > > _5029,std::shared_ptr< monty::ndarray< double,1 > > _5030,std::shared_ptr< monty::ndarray< double,1 > > _5031,std::shared_ptr< monty::ndarray< long long,1 > > _5032,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5033,monty::rc_ptr< ::mosek::fusion::Set > _5034,int _5035,int _5036,std::shared_ptr< monty::ndarray< int,1 > > _5037,std::shared_ptr< monty::ndarray< int,1 > > _5038,std::shared_ptr< monty::ndarray< double,1 > > _5039,int _5040,int _5041);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul_DMatrix_2DDExpr(std::shared_ptr< monty::ndarray< long long,1 > > _5089,std::shared_ptr< monty::ndarray< long long,1 > > _5090,std::shared_ptr< monty::ndarray< double,1 > > _5091,std::shared_ptr< monty::ndarray< double,1 > > _5092,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5093,monty::rc_ptr< ::mosek::fusion::Set > _5094,int _5095,int _5096,std::shared_ptr< monty::ndarray< double,1 > > _5097,int _5098,int _5099);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul_2DDExpr_DMatrix(std::shared_ptr< monty::ndarray< long long,1 > > _5119,std::shared_ptr< monty::ndarray< long long,1 > > _5120,std::shared_ptr< monty::ndarray< double,1 > > _5121,std::shared_ptr< monty::ndarray< double,1 > > _5122,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5123,monty::rc_ptr< ::mosek::fusion::Set > _5124,int _5125,int _5126,std::shared_ptr< monty::ndarray< double,1 > > _5127,int _5128,int _5129);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul_0DExpr_Matrix(std::shared_ptr< monty::ndarray< long long,1 > > _5151,std::shared_ptr< monty::ndarray< double,1 > > _5152,std::shared_ptr< monty::ndarray< double,1 > > _5153,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5154,monty::rc_ptr< ::mosek::fusion::Matrix > _5155);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Variable > _5173,std::shared_ptr< monty::ndarray< double,2 > > _5174);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(std::shared_ptr< monty::ndarray< double,2 > > _5178,monty::rc_ptr< ::mosek::fusion::Variable > _5179);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Variable > _5180,double _5181);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(double _5182,monty::rc_ptr< ::mosek::fusion::Variable > _5183);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(std::shared_ptr< monty::ndarray< double,1 > > _5190,monty::rc_ptr< ::mosek::fusion::Variable > _5191);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Variable > _5203,std::shared_ptr< monty::ndarray< double,1 > > _5204);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Variable > _5222,monty::rc_ptr< ::mosek::fusion::Matrix > _5223);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Matrix > _5266,monty::rc_ptr< ::mosek::fusion::Variable > _5267);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot_(monty::rc_ptr< ::mosek::fusion::Matrix > _5313,monty::rc_ptr< ::mosek::fusion::Expression > _5314);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot_(monty::rc_ptr< ::mosek::fusion::Matrix > _5322,monty::rc_ptr< ::mosek::fusion::Variable > _5323);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot_(std::shared_ptr< monty::ndarray< double,1 > > _5330,monty::rc_ptr< ::mosek::fusion::Variable > _5331);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot_(std::shared_ptr< monty::ndarray< double,1 > > _5332,monty::rc_ptr< ::mosek::fusion::Expression > _5333);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot_(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5335,monty::rc_ptr< ::mosek::fusion::Expression > _5336);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot_(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5341,monty::rc_ptr< ::mosek::fusion::Variable > _5342);
static  monty::rc_ptr< ::mosek::fusion::Expression > inner_(std::shared_ptr< monty::ndarray< long long,1 > > _5344,std::shared_ptr< monty::ndarray< double,1 > > _5345,monty::rc_ptr< ::mosek::fusion::Variable > _5346);
static  monty::rc_ptr< ::mosek::fusion::Expression > inner_(std::shared_ptr< monty::ndarray< long long,1 > > _5352,std::shared_ptr< monty::ndarray< double,1 > > _5353,std::shared_ptr< monty::ndarray< long long,1 > > _5354,std::shared_ptr< monty::ndarray< long long,1 > > _5355,std::shared_ptr< monty::ndarray< double,1 > > _5356,std::shared_ptr< monty::ndarray< double,1 > > _5357,std::shared_ptr< monty::ndarray< long long,1 > > _5358,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5359);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(std::shared_ptr< monty::ndarray< double,1 > > _5376,monty::rc_ptr< ::mosek::fusion::Expression > _5377);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(monty::rc_ptr< ::mosek::fusion::Expression > _5401,std::shared_ptr< monty::ndarray< double,1 > > _5402);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(std::shared_ptr< monty::ndarray< double,1 > > _5426,monty::rc_ptr< ::mosek::fusion::Variable > _5427);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(monty::rc_ptr< ::mosek::fusion::Variable > _5437,std::shared_ptr< monty::ndarray< double,1 > > _5438);
virtual monty::rc_ptr< ::mosek::fusion::Expression > pick(std::shared_ptr< monty::ndarray< int,2 > > _5448);
virtual monty::rc_ptr< ::mosek::fusion::Expression > pick(std::shared_ptr< monty::ndarray< int,1 > > _5454);
virtual monty::rc_ptr< ::mosek::fusion::Expression > pick_(std::shared_ptr< monty::ndarray< long long,1 > > _5457);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > >,1 > > _5495);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5501,double _5502,double _5503);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5504,double _5505,monty::rc_ptr< ::mosek::fusion::Variable > _5506);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5507,double _5508,monty::rc_ptr< ::mosek::fusion::Expression > _5509);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5510,monty::rc_ptr< ::mosek::fusion::Variable > _5511,double _5512);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5513,monty::rc_ptr< ::mosek::fusion::Variable > _5514,monty::rc_ptr< ::mosek::fusion::Variable > _5515);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5516,monty::rc_ptr< ::mosek::fusion::Variable > _5517,monty::rc_ptr< ::mosek::fusion::Expression > _5518);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5519,monty::rc_ptr< ::mosek::fusion::Expression > _5520,double _5521);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5522,monty::rc_ptr< ::mosek::fusion::Expression > _5523,monty::rc_ptr< ::mosek::fusion::Variable > _5524);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5525,monty::rc_ptr< ::mosek::fusion::Expression > _5526,monty::rc_ptr< ::mosek::fusion::Expression > _5527);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5528,double _5529,double _5530);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5531,double _5532,monty::rc_ptr< ::mosek::fusion::Variable > _5533);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5534,double _5535,monty::rc_ptr< ::mosek::fusion::Expression > _5536);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5537,monty::rc_ptr< ::mosek::fusion::Variable > _5538,double _5539);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5540,monty::rc_ptr< ::mosek::fusion::Variable > _5541,monty::rc_ptr< ::mosek::fusion::Variable > _5542);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5543,monty::rc_ptr< ::mosek::fusion::Variable > _5544,monty::rc_ptr< ::mosek::fusion::Expression > _5545);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5546,monty::rc_ptr< ::mosek::fusion::Expression > _5547,double _5548);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5549,monty::rc_ptr< ::mosek::fusion::Expression > _5550,monty::rc_ptr< ::mosek::fusion::Variable > _5551);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5552,monty::rc_ptr< ::mosek::fusion::Expression > _5553,monty::rc_ptr< ::mosek::fusion::Expression > _5554);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5555,double _5556,double _5557);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5558,double _5559,monty::rc_ptr< ::mosek::fusion::Variable > _5560);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5561,double _5562,monty::rc_ptr< ::mosek::fusion::Expression > _5563);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5564,monty::rc_ptr< ::mosek::fusion::Variable > _5565,double _5566);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5567,monty::rc_ptr< ::mosek::fusion::Variable > _5568,monty::rc_ptr< ::mosek::fusion::Variable > _5569);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5570,monty::rc_ptr< ::mosek::fusion::Variable > _5571,monty::rc_ptr< ::mosek::fusion::Expression > _5572);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5573,monty::rc_ptr< ::mosek::fusion::Expression > _5574,double _5575);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5576,monty::rc_ptr< ::mosek::fusion::Expression > _5577,monty::rc_ptr< ::mosek::fusion::Variable > _5578);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5579,monty::rc_ptr< ::mosek::fusion::Expression > _5580,monty::rc_ptr< ::mosek::fusion::Expression > _5581);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5582,monty::rc_ptr< ::mosek::fusion::Variable > _5583);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5584,monty::rc_ptr< ::mosek::fusion::Expression > _5585);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5586,double _5587);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5588,monty::rc_ptr< ::mosek::fusion::Variable > _5589);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _5590,monty::rc_ptr< ::mosek::fusion::Expression > _5591);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5592,double _5593);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5594,monty::rc_ptr< ::mosek::fusion::Variable > _5595);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5596,monty::rc_ptr< ::mosek::fusion::Expression > _5597);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5598);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5600,monty::rc_ptr< ::mosek::fusion::Expression > _5601,monty::rc_ptr< ::mosek::fusion::Expression > _5602);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5603,monty::rc_ptr< ::mosek::fusion::Expression > _5604,monty::rc_ptr< ::mosek::fusion::Variable > _5605);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5606,monty::rc_ptr< ::mosek::fusion::Expression > _5607,double _5608);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5609,monty::rc_ptr< ::mosek::fusion::Variable > _5610,monty::rc_ptr< ::mosek::fusion::Expression > _5611);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5612,monty::rc_ptr< ::mosek::fusion::Variable > _5613,monty::rc_ptr< ::mosek::fusion::Variable > _5614);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5615,monty::rc_ptr< ::mosek::fusion::Variable > _5616,double _5617);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5618,double _5619,monty::rc_ptr< ::mosek::fusion::Expression > _5620);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5621,double _5622,monty::rc_ptr< ::mosek::fusion::Variable > _5623);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5624,double _5625,double _5626);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5627,monty::rc_ptr< ::mosek::fusion::Expression > _5628,monty::rc_ptr< ::mosek::fusion::Expression > _5629);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5630,monty::rc_ptr< ::mosek::fusion::Expression > _5631,monty::rc_ptr< ::mosek::fusion::Variable > _5632);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5633,monty::rc_ptr< ::mosek::fusion::Expression > _5634,double _5635);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5636,monty::rc_ptr< ::mosek::fusion::Variable > _5637,monty::rc_ptr< ::mosek::fusion::Expression > _5638);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5639,monty::rc_ptr< ::mosek::fusion::Variable > _5640,monty::rc_ptr< ::mosek::fusion::Variable > _5641);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5642,monty::rc_ptr< ::mosek::fusion::Variable > _5643,double _5644);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5645,double _5646,monty::rc_ptr< ::mosek::fusion::Expression > _5647);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5648,double _5649,monty::rc_ptr< ::mosek::fusion::Variable > _5650);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5651,double _5652,double _5653);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5654,monty::rc_ptr< ::mosek::fusion::Expression > _5655,monty::rc_ptr< ::mosek::fusion::Expression > _5656);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5657,monty::rc_ptr< ::mosek::fusion::Expression > _5658,monty::rc_ptr< ::mosek::fusion::Variable > _5659);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5660,monty::rc_ptr< ::mosek::fusion::Expression > _5661,double _5662);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5663,monty::rc_ptr< ::mosek::fusion::Variable > _5664,monty::rc_ptr< ::mosek::fusion::Expression > _5665);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5666,monty::rc_ptr< ::mosek::fusion::Variable > _5667,monty::rc_ptr< ::mosek::fusion::Variable > _5668);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5669,monty::rc_ptr< ::mosek::fusion::Variable > _5670,double _5671);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5672,double _5673,monty::rc_ptr< ::mosek::fusion::Expression > _5674);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5675,double _5676,monty::rc_ptr< ::mosek::fusion::Variable > _5677);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5678,monty::rc_ptr< ::mosek::fusion::Expression > _5679);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5680,monty::rc_ptr< ::mosek::fusion::Variable > _5681);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _5682,double _5683);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5684,monty::rc_ptr< ::mosek::fusion::Expression > _5685);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5686,monty::rc_ptr< ::mosek::fusion::Variable > _5687);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5688,monty::rc_ptr< ::mosek::fusion::Variable > _5689);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5690,double _5691);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5692,monty::rc_ptr< ::mosek::fusion::Expression > _5693);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5694);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5696,monty::rc_ptr< ::mosek::fusion::Expression > _5697,monty::rc_ptr< ::mosek::fusion::Expression > _5698,monty::rc_ptr< ::mosek::fusion::Expression > _5699);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5700,monty::rc_ptr< ::mosek::fusion::Expression > _5701,monty::rc_ptr< ::mosek::fusion::Expression > _5702,monty::rc_ptr< ::mosek::fusion::Variable > _5703);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5704,monty::rc_ptr< ::mosek::fusion::Expression > _5705,monty::rc_ptr< ::mosek::fusion::Expression > _5706,double _5707);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5708,monty::rc_ptr< ::mosek::fusion::Expression > _5709,monty::rc_ptr< ::mosek::fusion::Variable > _5710,monty::rc_ptr< ::mosek::fusion::Expression > _5711);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5712,monty::rc_ptr< ::mosek::fusion::Expression > _5713,monty::rc_ptr< ::mosek::fusion::Variable > _5714,monty::rc_ptr< ::mosek::fusion::Variable > _5715);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5716,monty::rc_ptr< ::mosek::fusion::Expression > _5717,monty::rc_ptr< ::mosek::fusion::Variable > _5718,double _5719);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5720,monty::rc_ptr< ::mosek::fusion::Expression > _5721,double _5722,monty::rc_ptr< ::mosek::fusion::Expression > _5723);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5724,monty::rc_ptr< ::mosek::fusion::Expression > _5725,double _5726,monty::rc_ptr< ::mosek::fusion::Variable > _5727);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5728,monty::rc_ptr< ::mosek::fusion::Expression > _5729,double _5730,double _5731);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5732,monty::rc_ptr< ::mosek::fusion::Variable > _5733,monty::rc_ptr< ::mosek::fusion::Expression > _5734,monty::rc_ptr< ::mosek::fusion::Expression > _5735);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5736,monty::rc_ptr< ::mosek::fusion::Variable > _5737,monty::rc_ptr< ::mosek::fusion::Expression > _5738,monty::rc_ptr< ::mosek::fusion::Variable > _5739);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5740,monty::rc_ptr< ::mosek::fusion::Variable > _5741,monty::rc_ptr< ::mosek::fusion::Expression > _5742,double _5743);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5744,monty::rc_ptr< ::mosek::fusion::Variable > _5745,monty::rc_ptr< ::mosek::fusion::Variable > _5746,monty::rc_ptr< ::mosek::fusion::Expression > _5747);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5748,monty::rc_ptr< ::mosek::fusion::Variable > _5749,monty::rc_ptr< ::mosek::fusion::Variable > _5750,monty::rc_ptr< ::mosek::fusion::Variable > _5751);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5752,monty::rc_ptr< ::mosek::fusion::Variable > _5753,monty::rc_ptr< ::mosek::fusion::Variable > _5754,double _5755);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5756,monty::rc_ptr< ::mosek::fusion::Variable > _5757,double _5758,monty::rc_ptr< ::mosek::fusion::Expression > _5759);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5760,monty::rc_ptr< ::mosek::fusion::Variable > _5761,double _5762,monty::rc_ptr< ::mosek::fusion::Variable > _5763);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5764,monty::rc_ptr< ::mosek::fusion::Variable > _5765,double _5766,double _5767);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5768,double _5769,monty::rc_ptr< ::mosek::fusion::Expression > _5770,monty::rc_ptr< ::mosek::fusion::Expression > _5771);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5772,double _5773,monty::rc_ptr< ::mosek::fusion::Expression > _5774,monty::rc_ptr< ::mosek::fusion::Variable > _5775);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5776,double _5777,monty::rc_ptr< ::mosek::fusion::Expression > _5778,double _5779);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5780,double _5781,monty::rc_ptr< ::mosek::fusion::Variable > _5782,monty::rc_ptr< ::mosek::fusion::Expression > _5783);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5784,double _5785,monty::rc_ptr< ::mosek::fusion::Variable > _5786,monty::rc_ptr< ::mosek::fusion::Variable > _5787);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5788,double _5789,monty::rc_ptr< ::mosek::fusion::Variable > _5790,double _5791);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5792,double _5793,double _5794,monty::rc_ptr< ::mosek::fusion::Expression > _5795);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5796,double _5797,double _5798,monty::rc_ptr< ::mosek::fusion::Variable > _5799);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5800,monty::rc_ptr< ::mosek::fusion::Variable > _5801,monty::rc_ptr< ::mosek::fusion::Expression > _5802);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5803,monty::rc_ptr< ::mosek::fusion::Variable > _5804,monty::rc_ptr< ::mosek::fusion::Variable > _5805);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5806,monty::rc_ptr< ::mosek::fusion::Variable > _5807,double _5808);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5809,double _5810,monty::rc_ptr< ::mosek::fusion::Expression > _5811);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5812,double _5813,monty::rc_ptr< ::mosek::fusion::Variable > _5814);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5815,monty::rc_ptr< ::mosek::fusion::Expression > _5816,monty::rc_ptr< ::mosek::fusion::Variable > _5817);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5818,monty::rc_ptr< ::mosek::fusion::Expression > _5819,double _5820);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5821,monty::rc_ptr< ::mosek::fusion::Expression > _5822,monty::rc_ptr< ::mosek::fusion::Expression > _5823);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5824,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5825);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack_(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5826,int _5827);
static  monty::rc_ptr< ::mosek::fusion::Expression > repeat(monty::rc_ptr< ::mosek::fusion::Expression > _5901,int _5902,int _5903);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5905);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5975);
static  monty::rc_ptr< ::mosek::fusion::Expression > add_(monty::rc_ptr< ::mosek::fusion::Expression > _5988,double _5989,monty::rc_ptr< ::mosek::fusion::Expression > _5990,double _5991);
virtual monty::rc_ptr< ::mosek::fusion::Expression > transpose();
virtual monty::rc_ptr< ::mosek::fusion::Expression > slice(std::shared_ptr< monty::ndarray< int,1 > > _6091,std::shared_ptr< monty::ndarray< int,1 > > _6092);
virtual monty::rc_ptr< ::mosek::fusion::Expression > index(std::shared_ptr< monty::ndarray< int,1 > > _6133);
virtual monty::rc_ptr< ::mosek::fusion::Expression > index(int _6136);
virtual monty::rc_ptr< ::mosek::fusion::Expression > slice(int _6137,int _6138);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Matrix > _6139,monty::rc_ptr< ::mosek::fusion::Expression > _6140);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Matrix > _6141,monty::rc_ptr< ::mosek::fusion::Variable > _6142);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6143,monty::rc_ptr< ::mosek::fusion::Variable > _6144);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6145,monty::rc_ptr< ::mosek::fusion::Expression > _6146);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(std::shared_ptr< monty::ndarray< double,2 > > _6147,monty::rc_ptr< ::mosek::fusion::Variable > _6148);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(std::shared_ptr< monty::ndarray< double,2 > > _6149,monty::rc_ptr< ::mosek::fusion::Expression > _6150);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(std::shared_ptr< monty::ndarray< double,1 > > _6151,monty::rc_ptr< ::mosek::fusion::Variable > _6152);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(std::shared_ptr< monty::ndarray< double,1 > > _6153,monty::rc_ptr< ::mosek::fusion::Expression > _6154);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Expression > _6155,monty::rc_ptr< ::mosek::fusion::Matrix > _6156);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Expression > _6157,std::shared_ptr< monty::ndarray< double,2 > > _6158);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Expression > _6159,std::shared_ptr< monty::ndarray< double,1 > > _6160);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Expression > _6161,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6162);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Variable > _6163,monty::rc_ptr< ::mosek::fusion::Matrix > _6164);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Variable > _6165,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6166);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Variable > _6167,std::shared_ptr< monty::ndarray< double,2 > > _6168);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Variable > _6169,std::shared_ptr< monty::ndarray< double,1 > > _6170);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Matrix > _6171,monty::rc_ptr< ::mosek::fusion::Expression > _6172);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Matrix > _6173,monty::rc_ptr< ::mosek::fusion::Variable > _6174);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6175,monty::rc_ptr< ::mosek::fusion::Variable > _6176);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6177,monty::rc_ptr< ::mosek::fusion::Expression > _6178);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(std::shared_ptr< monty::ndarray< double,2 > > _6179,monty::rc_ptr< ::mosek::fusion::Variable > _6180);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(std::shared_ptr< monty::ndarray< double,2 > > _6181,monty::rc_ptr< ::mosek::fusion::Expression > _6182);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(std::shared_ptr< monty::ndarray< double,1 > > _6183,monty::rc_ptr< ::mosek::fusion::Variable > _6184);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(std::shared_ptr< monty::ndarray< double,1 > > _6185,monty::rc_ptr< ::mosek::fusion::Expression > _6186);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Expression > _6187,monty::rc_ptr< ::mosek::fusion::Matrix > _6188);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Expression > _6189,std::shared_ptr< monty::ndarray< double,2 > > _6190);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Expression > _6191,std::shared_ptr< monty::ndarray< double,1 > > _6192);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Expression > _6193,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6194);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Variable > _6195,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6196);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Variable > _6197,monty::rc_ptr< ::mosek::fusion::Matrix > _6198);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Variable > _6199,std::shared_ptr< monty::ndarray< double,2 > > _6200);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Variable > _6201,std::shared_ptr< monty::ndarray< double,1 > > _6202);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6203,monty::rc_ptr< ::mosek::fusion::Variable > _6204);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Variable > _6205,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6206);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Matrix > _6207,monty::rc_ptr< ::mosek::fusion::Variable > _6208);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Variable > _6209,monty::rc_ptr< ::mosek::fusion::Matrix > _6210);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(double _6211,monty::rc_ptr< ::mosek::fusion::Variable > _6212);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Variable > _6213,double _6214);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(std::shared_ptr< monty::ndarray< double,2 > > _6215,monty::rc_ptr< ::mosek::fusion::Variable > _6216);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(std::shared_ptr< monty::ndarray< double,1 > > _6217,monty::rc_ptr< ::mosek::fusion::Variable > _6218);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Variable > _6219,std::shared_ptr< monty::ndarray< double,2 > > _6220);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Variable > _6221,std::shared_ptr< monty::ndarray< double,1 > > _6222);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Variable > _6223,monty::rc_ptr< ::mosek::fusion::Variable > _6224);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6225,monty::rc_ptr< ::mosek::fusion::Expression > _6226);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _6227,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6228);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Matrix > _6229,monty::rc_ptr< ::mosek::fusion::Expression > _6230);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _6231,monty::rc_ptr< ::mosek::fusion::Matrix > _6232);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(double _6233,monty::rc_ptr< ::mosek::fusion::Expression > _6234);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _6235,double _6236);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(std::shared_ptr< monty::ndarray< double,2 > > _6237,monty::rc_ptr< ::mosek::fusion::Expression > _6238);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(std::shared_ptr< monty::ndarray< double,1 > > _6239,monty::rc_ptr< ::mosek::fusion::Expression > _6240);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _6241,std::shared_ptr< monty::ndarray< double,2 > > _6242);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _6243,std::shared_ptr< monty::ndarray< double,1 > > _6244);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Variable > _6245,monty::rc_ptr< ::mosek::fusion::Expression > _6246);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _6247,monty::rc_ptr< ::mosek::fusion::Variable > _6248);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _6249,monty::rc_ptr< ::mosek::fusion::Expression > _6250);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6251,monty::rc_ptr< ::mosek::fusion::Variable > _6252);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Variable > _6253,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6254);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Matrix > _6255,monty::rc_ptr< ::mosek::fusion::Variable > _6256);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Variable > _6257,monty::rc_ptr< ::mosek::fusion::Matrix > _6258);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(double _6259,monty::rc_ptr< ::mosek::fusion::Variable > _6260);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Variable > _6261,double _6262);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< double,2 > > _6263,monty::rc_ptr< ::mosek::fusion::Variable > _6264);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< double,1 > > _6265,monty::rc_ptr< ::mosek::fusion::Variable > _6266);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Variable > _6267,std::shared_ptr< monty::ndarray< double,2 > > _6268);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Variable > _6269,std::shared_ptr< monty::ndarray< double,1 > > _6270);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Variable > _6271,monty::rc_ptr< ::mosek::fusion::Variable > _6272);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6273,monty::rc_ptr< ::mosek::fusion::Expression > _6274);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _6275,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _6276);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Matrix > _6277,monty::rc_ptr< ::mosek::fusion::Expression > _6278);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _6279,monty::rc_ptr< ::mosek::fusion::Matrix > _6280);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(double _6281,monty::rc_ptr< ::mosek::fusion::Expression > _6282);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _6283,double _6284);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< double,2 > > _6285,monty::rc_ptr< ::mosek::fusion::Expression > _6286);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< double,1 > > _6287,monty::rc_ptr< ::mosek::fusion::Expression > _6288);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _6289,std::shared_ptr< monty::ndarray< double,2 > > _6290);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _6291,std::shared_ptr< monty::ndarray< double,1 > > _6292);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Variable > _6293,monty::rc_ptr< ::mosek::fusion::Expression > _6294);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _6295,monty::rc_ptr< ::mosek::fusion::Variable > _6296);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _6297,monty::rc_ptr< ::mosek::fusion::Expression > _6298);
virtual monty::rc_ptr< ::mosek::fusion::Set > shape();
virtual monty::rc_ptr< ::mosek::fusion::Set > getShape();
virtual monty::rc_ptr< ::mosek::fusion::Model > getModel();
static  void validateData(std::shared_ptr< monty::ndarray< long long,1 > > _6299,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _6300,std::shared_ptr< monty::ndarray< long long,1 > > _6301,std::shared_ptr< monty::ndarray< double,1 > > _6302,std::shared_ptr< monty::ndarray< double,1 > > _6303,monty::rc_ptr< ::mosek::fusion::Set > _6304,std::shared_ptr< monty::ndarray< long long,1 > > _6305);
static  monty::rc_ptr< ::mosek::fusion::Model > extractModel(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _6320);
}; // struct Expr;

struct p_FlatExpr
{
FlatExpr * _pubthis;
static mosek::fusion::p_FlatExpr* _get_impl(mosek::fusion::FlatExpr * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_FlatExpr * _get_impl(mosek::fusion::FlatExpr::t _inst) { return _get_impl(_inst.get()); }
p_FlatExpr(FlatExpr * _pubthis);
virtual ~p_FlatExpr() { /* std::cout << "~p_FlatExpr" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > inst{};monty::rc_ptr< ::mosek::fusion::Set > shape{};long long nnz{};std::shared_ptr< monty::ndarray< double,1 > > cof{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > x{};std::shared_ptr< monty::ndarray< long long,1 > > subj{};std::shared_ptr< monty::ndarray< long long,1 > > ptrb{};std::shared_ptr< monty::ndarray< double,1 > > bfix{};virtual void destroy();
static FlatExpr::t _new_FlatExpr(monty::rc_ptr< ::mosek::fusion::FlatExpr > _6321);
void _initialize(monty::rc_ptr< ::mosek::fusion::FlatExpr > _6321);
static FlatExpr::t _new_FlatExpr(std::shared_ptr< monty::ndarray< double,1 > > _6322,std::shared_ptr< monty::ndarray< long long,1 > > _6323,std::shared_ptr< monty::ndarray< long long,1 > > _6324,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _6325,std::shared_ptr< monty::ndarray< double,1 > > _6326,monty::rc_ptr< ::mosek::fusion::Set > _6327,std::shared_ptr< monty::ndarray< long long,1 > > _6328);
void _initialize(std::shared_ptr< monty::ndarray< double,1 > > _6322,std::shared_ptr< monty::ndarray< long long,1 > > _6323,std::shared_ptr< monty::ndarray< long long,1 > > _6324,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _6325,std::shared_ptr< monty::ndarray< double,1 > > _6326,monty::rc_ptr< ::mosek::fusion::Set > _6327,std::shared_ptr< monty::ndarray< long long,1 > > _6328);
virtual std::string toString();
virtual int size();
}; // struct FlatExpr;

struct p_SymmetricMatrix
{
SymmetricMatrix * _pubthis;
static mosek::fusion::p_SymmetricMatrix* _get_impl(mosek::fusion::SymmetricMatrix * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_SymmetricMatrix * _get_impl(mosek::fusion::SymmetricMatrix::t _inst) { return _get_impl(_inst.get()); }
p_SymmetricMatrix(SymmetricMatrix * _pubthis);
virtual ~p_SymmetricMatrix() { /* std::cout << "~p_SymmetricMatrix" << std::endl;*/ };
int nnz{};double scale{};std::shared_ptr< monty::ndarray< double,1 > > vval{};std::shared_ptr< monty::ndarray< int,1 > > vsubj{};std::shared_ptr< monty::ndarray< int,1 > > vsubi{};std::shared_ptr< monty::ndarray< double,1 > > uval{};std::shared_ptr< monty::ndarray< int,1 > > usubj{};std::shared_ptr< monty::ndarray< int,1 > > usubi{};int d1{};int d0{};virtual void destroy();
static SymmetricMatrix::t _new_SymmetricMatrix(int _6330,int _6331,std::shared_ptr< monty::ndarray< int,1 > > _6332,std::shared_ptr< monty::ndarray< int,1 > > _6333,std::shared_ptr< monty::ndarray< double,1 > > _6334,std::shared_ptr< monty::ndarray< int,1 > > _6335,std::shared_ptr< monty::ndarray< int,1 > > _6336,std::shared_ptr< monty::ndarray< double,1 > > _6337,double _6338);
void _initialize(int _6330,int _6331,std::shared_ptr< monty::ndarray< int,1 > > _6332,std::shared_ptr< monty::ndarray< int,1 > > _6333,std::shared_ptr< monty::ndarray< double,1 > > _6334,std::shared_ptr< monty::ndarray< int,1 > > _6335,std::shared_ptr< monty::ndarray< int,1 > > _6336,std::shared_ptr< monty::ndarray< double,1 > > _6337,double _6338);
static  monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > rankOne(int _6339,std::shared_ptr< monty::ndarray< int,1 > > _6340,std::shared_ptr< monty::ndarray< double,1 > > _6341);
static  monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > rankOne(std::shared_ptr< monty::ndarray< double,1 > > _6349);
static  monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > antiDiag(std::shared_ptr< monty::ndarray< double,1 > > _6357);
static  monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > diag(std::shared_ptr< monty::ndarray< double,1 > > _6364);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > add(monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _6370);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > sub(monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _6390);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > mul(double _6391);
virtual int getdim();
}; // struct SymmetricMatrix;

struct p_NDSparseArray
{
NDSparseArray * _pubthis;
static mosek::fusion::p_NDSparseArray* _get_impl(mosek::fusion::NDSparseArray * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_NDSparseArray * _get_impl(mosek::fusion::NDSparseArray::t _inst) { return _get_impl(_inst.get()); }
p_NDSparseArray(NDSparseArray * _pubthis);
virtual ~p_NDSparseArray() { /* std::cout << "~p_NDSparseArray" << std::endl;*/ };
std::shared_ptr< monty::ndarray< double,1 > > cof{};std::shared_ptr< monty::ndarray< long long,1 > > inst{};std::shared_ptr< monty::ndarray< int,1 > > dims{};long long size{};virtual void destroy();
static NDSparseArray::t _new_NDSparseArray(std::shared_ptr< monty::ndarray< int,1 > > _6392,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _6393,std::shared_ptr< monty::ndarray< double,1 > > _6394);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _6392,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _6393,std::shared_ptr< monty::ndarray< double,1 > > _6394);
static NDSparseArray::t _new_NDSparseArray(std::shared_ptr< monty::ndarray< int,1 > > _6414,std::shared_ptr< monty::ndarray< long long,1 > > _6415,std::shared_ptr< monty::ndarray< double,1 > > _6416);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _6414,std::shared_ptr< monty::ndarray< long long,1 > > _6415,std::shared_ptr< monty::ndarray< double,1 > > _6416);
static NDSparseArray::t _new_NDSparseArray(monty::rc_ptr< ::mosek::fusion::Matrix > _6430);
void _initialize(monty::rc_ptr< ::mosek::fusion::Matrix > _6430);
static  monty::rc_ptr< ::mosek::fusion::NDSparseArray > make(monty::rc_ptr< ::mosek::fusion::Matrix > _6438);
static  monty::rc_ptr< ::mosek::fusion::NDSparseArray > make(std::shared_ptr< monty::ndarray< int,1 > > _6439,std::shared_ptr< monty::ndarray< long long,1 > > _6440,std::shared_ptr< monty::ndarray< double,1 > > _6441);
static  monty::rc_ptr< ::mosek::fusion::NDSparseArray > make(std::shared_ptr< monty::ndarray< int,1 > > _6442,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _6443,std::shared_ptr< monty::ndarray< double,1 > > _6444);
}; // struct NDSparseArray;

struct p_Matrix
{
Matrix * _pubthis;
static mosek::fusion::p_Matrix* _get_impl(mosek::fusion::Matrix * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Matrix * _get_impl(mosek::fusion::Matrix::t _inst) { return _get_impl(_inst.get()); }
p_Matrix(Matrix * _pubthis);
virtual ~p_Matrix() { /* std::cout << "~p_Matrix" << std::endl;*/ };
int dimj{};int dimi{};virtual void destroy();
static Matrix::t _new_Matrix(int _6513,int _6514);
void _initialize(int _6513,int _6514);
virtual std::string toString();
virtual void switchDims();
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(int _6516,monty::rc_ptr< ::mosek::fusion::Matrix > _6517);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Matrix >,1 > > _6519);
static  monty::rc_ptr< ::mosek::fusion::Matrix > antidiag(int _6537,double _6538,int _6539);
static  monty::rc_ptr< ::mosek::fusion::Matrix > antidiag(int _6540,double _6541);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(int _6542,double _6543,int _6544);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(int _6545,double _6546);
static  monty::rc_ptr< ::mosek::fusion::Matrix > antidiag(std::shared_ptr< monty::ndarray< double,1 > > _6547,int _6548);
static  monty::rc_ptr< ::mosek::fusion::Matrix > antidiag(std::shared_ptr< monty::ndarray< double,1 > > _6558);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(std::shared_ptr< monty::ndarray< double,1 > > _6559,int _6560);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(std::shared_ptr< monty::ndarray< double,1 > > _6568);
static  monty::rc_ptr< ::mosek::fusion::Matrix > ones(int _6569,int _6570);
static  monty::rc_ptr< ::mosek::fusion::Matrix > eye(int _6571);
static  monty::rc_ptr< ::mosek::fusion::Matrix > dense(monty::rc_ptr< ::mosek::fusion::Matrix > _6573);
static  monty::rc_ptr< ::mosek::fusion::Matrix > dense(int _6574,int _6575,double _6576);
static  monty::rc_ptr< ::mosek::fusion::Matrix > dense(int _6577,int _6578,std::shared_ptr< monty::ndarray< double,1 > > _6579);
static  monty::rc_ptr< ::mosek::fusion::Matrix > dense(std::shared_ptr< monty::ndarray< double,2 > > _6580);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(monty::rc_ptr< ::mosek::fusion::Matrix > _6581);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Matrix >,1 > >,1 > > _6585);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(std::shared_ptr< monty::ndarray< double,2 > > _6616);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(int _6629,int _6630);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(int _6631,int _6632,std::shared_ptr< monty::ndarray< int,1 > > _6633,std::shared_ptr< monty::ndarray< int,1 > > _6634,double _6635);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(std::shared_ptr< monty::ndarray< int,1 > > _6637,std::shared_ptr< monty::ndarray< int,1 > > _6638,double _6639);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(std::shared_ptr< monty::ndarray< int,1 > > _6644,std::shared_ptr< monty::ndarray< int,1 > > _6645,std::shared_ptr< monty::ndarray< double,1 > > _6646);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(int _6651,int _6652,std::shared_ptr< monty::ndarray< int,1 > > _6653,std::shared_ptr< monty::ndarray< int,1 > > _6654,std::shared_ptr< monty::ndarray< double,1 > > _6655);
virtual double get(int _6660,int _6661) { throw monty::AbstractClassError("Call to abstract method"); }
virtual bool isSparse() { throw monty::AbstractClassError("Call to abstract method"); }
virtual std::shared_ptr< monty::ndarray< double,1 > > getDataAsArray() { throw monty::AbstractClassError("Call to abstract method"); }
virtual void getDataAsTriplets(std::shared_ptr< monty::ndarray< int,1 > > _6662,std::shared_ptr< monty::ndarray< int,1 > > _6663,std::shared_ptr< monty::ndarray< double,1 > > _6664) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Matrix > transpose() { throw monty::AbstractClassError("Call to abstract method"); }
virtual long long numNonzeros() { throw monty::AbstractClassError("Call to abstract method"); }
virtual int numColumns();
virtual int numRows();
}; // struct Matrix;

struct p_DenseMatrix : public ::mosek::fusion::p_Matrix
{
DenseMatrix * _pubthis;
static mosek::fusion::p_DenseMatrix* _get_impl(mosek::fusion::DenseMatrix * _inst){ return static_cast< mosek::fusion::p_DenseMatrix* >(mosek::fusion::p_Matrix::_get_impl(_inst)); }
static mosek::fusion::p_DenseMatrix * _get_impl(mosek::fusion::DenseMatrix::t _inst) { return _get_impl(_inst.get()); }
p_DenseMatrix(DenseMatrix * _pubthis);
virtual ~p_DenseMatrix() { /* std::cout << "~p_DenseMatrix" << std::endl;*/ };
long long nnz{};std::shared_ptr< monty::ndarray< double,1 > > data{};virtual void destroy();
static DenseMatrix::t _new_DenseMatrix(int _6445,int _6446,std::shared_ptr< monty::ndarray< double,1 > > _6447);
void _initialize(int _6445,int _6446,std::shared_ptr< monty::ndarray< double,1 > > _6447);
static DenseMatrix::t _new_DenseMatrix(monty::rc_ptr< ::mosek::fusion::Matrix > _6448);
void _initialize(monty::rc_ptr< ::mosek::fusion::Matrix > _6448);
static DenseMatrix::t _new_DenseMatrix(std::shared_ptr< monty::ndarray< double,2 > > _6453);
void _initialize(std::shared_ptr< monty::ndarray< double,2 > > _6453);
static DenseMatrix::t _new_DenseMatrix(int _6456,int _6457,double _6458);
void _initialize(int _6456,int _6457,double _6458);
virtual std::string toString();
virtual monty::rc_ptr< ::mosek::fusion::Matrix > transpose();
virtual bool isSparse();
virtual std::shared_ptr< monty::ndarray< double,1 > > getDataAsArray();
virtual void getDataAsTriplets(std::shared_ptr< monty::ndarray< int,1 > > _6471,std::shared_ptr< monty::ndarray< int,1 > > _6472,std::shared_ptr< monty::ndarray< double,1 > > _6473);
virtual double get(int _6477,int _6478);
virtual long long numNonzeros();
}; // struct DenseMatrix;

struct p_SparseMatrix : public ::mosek::fusion::p_Matrix
{
SparseMatrix * _pubthis;
static mosek::fusion::p_SparseMatrix* _get_impl(mosek::fusion::SparseMatrix * _inst){ return static_cast< mosek::fusion::p_SparseMatrix* >(mosek::fusion::p_Matrix::_get_impl(_inst)); }
static mosek::fusion::p_SparseMatrix * _get_impl(mosek::fusion::SparseMatrix::t _inst) { return _get_impl(_inst.get()); }
p_SparseMatrix(SparseMatrix * _pubthis);
virtual ~p_SparseMatrix() { /* std::cout << "~p_SparseMatrix" << std::endl;*/ };
long long nnz{};std::shared_ptr< monty::ndarray< double,1 > > val{};std::shared_ptr< monty::ndarray< int,1 > > subj{};std::shared_ptr< monty::ndarray< int,1 > > subi{};virtual void destroy();
static SparseMatrix::t _new_SparseMatrix(int _6479,int _6480,std::shared_ptr< monty::ndarray< int,1 > > _6481,std::shared_ptr< monty::ndarray< int,1 > > _6482,std::shared_ptr< monty::ndarray< double,1 > > _6483,long long _6484);
void _initialize(int _6479,int _6480,std::shared_ptr< monty::ndarray< int,1 > > _6481,std::shared_ptr< monty::ndarray< int,1 > > _6482,std::shared_ptr< monty::ndarray< double,1 > > _6483,long long _6484);
static SparseMatrix::t _new_SparseMatrix(int _6489,int _6490,std::shared_ptr< monty::ndarray< int,1 > > _6491,std::shared_ptr< monty::ndarray< int,1 > > _6492,std::shared_ptr< monty::ndarray< double,1 > > _6493);
void _initialize(int _6489,int _6490,std::shared_ptr< monty::ndarray< int,1 > > _6491,std::shared_ptr< monty::ndarray< int,1 > > _6492,std::shared_ptr< monty::ndarray< double,1 > > _6493);
virtual std::shared_ptr< monty::ndarray< long long,1 > > formPtrb();
virtual std::string toString();
virtual long long numNonzeros();
virtual monty::rc_ptr< ::mosek::fusion::Matrix > transpose();
virtual bool isSparse();
virtual std::shared_ptr< monty::ndarray< double,1 > > getDataAsArray();
virtual void getDataAsTriplets(std::shared_ptr< monty::ndarray< int,1 > > _6505,std::shared_ptr< monty::ndarray< int,1 > > _6506,std::shared_ptr< monty::ndarray< double,1 > > _6507);
virtual double get(int _6508,int _6509);
}; // struct SparseMatrix;

struct p_Parameters
{
Parameters * _pubthis;
static mosek::fusion::p_Parameters* _get_impl(mosek::fusion::Parameters * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Parameters * _get_impl(mosek::fusion::Parameters::t _inst) { return _get_impl(_inst.get()); }
p_Parameters(Parameters * _pubthis);
virtual ~p_Parameters() { /* std::cout << "~p_Parameters" << std::endl;*/ };
virtual void destroy();
static  void setParameter(monty::rc_ptr< ::mosek::fusion::Model > _6688,const std::string &  _6689,double _6690);
static  void setParameter(monty::rc_ptr< ::mosek::fusion::Model > _6800,const std::string &  _6801,int _6802);
static  void setParameter(monty::rc_ptr< ::mosek::fusion::Model > _6912,const std::string &  _6913,const std::string &  _6914);
static  int string_to_miocontsoltype_value(const std::string &  _7183);
static  int string_to_internal_dinf_value(const std::string &  _7184);
static  int string_to_presolvemode_value(const std::string &  _7185);
static  int string_to_optimizertype_value(const std::string &  _7186);
static  int string_to_xmlwriteroutputtype_value(const std::string &  _7187);
static  int string_to_iinfitem_value(const std::string &  _7188);
static  int string_to_simreform_value(const std::string &  _7189);
static  int string_to_stakey_value(const std::string &  _7190);
static  int string_to_value_value(const std::string &  _7191);
static  int string_to_scalingmethod_value(const std::string &  _7192);
static  int string_to_soltype_value(const std::string &  _7193);
static  int string_to_startpointtype_value(const std::string &  _7194);
static  int string_to_language_value(const std::string &  _7195);
static  int string_to_checkconvexitytype_value(const std::string &  _7196);
static  int string_to_variabletype_value(const std::string &  _7197);
static  int string_to_mpsformat_value(const std::string &  _7198);
static  int string_to_nametype_value(const std::string &  _7199);
static  int string_to_compresstype_value(const std::string &  _7200);
static  int string_to_simdupvec_value(const std::string &  _7201);
static  int string_to_dparam_value(const std::string &  _7202);
static  int string_to_inftype_value(const std::string &  _7203);
static  int string_to_problemtype_value(const std::string &  _7204);
static  int string_to_orderingtype_value(const std::string &  _7205);
static  int string_to_dataformat_value(const std::string &  _7206);
static  int string_to_simdegen_value(const std::string &  _7207);
static  int string_to_onoffkey_value(const std::string &  _7208);
static  int string_to_transpose_value(const std::string &  _7209);
static  int string_to_mionodeseltype_value(const std::string &  _7210);
static  int string_to_rescode_value(const std::string &  _7211);
static  int string_to_scalingtype_value(const std::string &  _7212);
static  int string_to_prosta_value(const std::string &  _7213);
static  int string_to_rescodetype_value(const std::string &  _7214);
static  int string_to_parametertype_value(const std::string &  _7215);
static  int string_to_dinfitem_value(const std::string &  _7216);
static  int string_to_miomode_value(const std::string &  _7217);
static  int string_to_msgkey_value(const std::string &  _7218);
static  int string_to_simseltype_value(const std::string &  _7219);
static  int string_to_internal_liinf_value(const std::string &  _7220);
static  int string_to_iomode_value(const std::string &  _7221);
static  int string_to_streamtype_value(const std::string &  _7222);
static  int string_to_conetype_value(const std::string &  _7223);
static  int string_to_mark_value(const std::string &  _7224);
static  int string_to_feature_value(const std::string &  _7225);
static  int string_to_symmattype_value(const std::string &  _7226);
static  int string_to_callbackcode_value(const std::string &  _7227);
static  int string_to_simhotstart_value(const std::string &  _7228);
static  int string_to_liinfitem_value(const std::string &  _7229);
static  int string_to_branchdir_value(const std::string &  _7230);
static  int string_to_basindtype_value(const std::string &  _7231);
static  int string_to_internal_iinf_value(const std::string &  _7232);
static  int string_to_boundkey_value(const std::string &  _7233);
static  int string_to_solitem_value(const std::string &  _7234);
static  int string_to_objsense_value(const std::string &  _7235);
static  int string_to_solsta_value(const std::string &  _7236);
static  int string_to_iparam_value(const std::string &  _7237);
static  int string_to_sparam_value(const std::string &  _7238);
static  int string_to_intpnthotstart_value(const std::string &  _7239);
static  int string_to_uplo_value(const std::string &  _7240);
static  int string_to_sensitivitytype_value(const std::string &  _7241);
static  int string_to_accmode_value(const std::string &  _7242);
static  int string_to_problemitem_value(const std::string &  _7243);
static  int string_to_solveform_value(const std::string &  _7244);
}; // struct Parameters;

}
}
namespace mosek
{
namespace fusion
{
namespace Utils
{
// mosek.fusion.Utils.IntMap from file 'src/fusion/cxx/IntMap_p.h'
struct p_IntMap 
{
  IntMap * _pubself;

  static p_IntMap * _get_impl(IntMap * _inst) { return _inst->_impl.get(); }

  p_IntMap(IntMap * _pubself) : _pubself(_pubself) {}

  static IntMap::t _new_IntMap() { return new IntMap(); }

  ::std::unordered_map<long long,int> m;

  bool hasItem (long long key) { return m.find(key) != m.end(); }
  int  getItem (long long key) { return m.find(key)->second; } // will probably throw something or crash of no such key
  void setItem (long long key, int val) { m[key] = val; }

  std::shared_ptr<monty::ndarray<long long,1>> keys()
  { 
    size_t size = m.size();
    auto res = std::shared_ptr<monty::ndarray<long long,1>>(new monty::ndarray<long long,1>(monty::shape((int)size)));

    ptrdiff_t i = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
      (*res)[i++] = it->first;

    return res;    
  }

  std::shared_ptr<monty::ndarray<int,1>> values()
  {
    size_t size = m.size();
    auto res = std::shared_ptr<monty::ndarray<int,1>>(new monty::ndarray<int,1>(monty::shape((int)size)));

    ptrdiff_t i = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
      (*res)[i++] = it->second;

    return res;
  }

  IntMap::t clone();
};



struct p_StringIntMap
{
  StringIntMap * _pubself;

  static p_StringIntMap * _get_impl(StringIntMap * _inst) { return _inst->_impl.get(); }

  p_StringIntMap(StringIntMap * _pubself) : _pubself(_pubself) {}

  static StringIntMap::t _new_StringIntMap() { return new StringIntMap(); }

  ::std::unordered_map<std::string,int> m;

  bool hasItem (const std::string & key) { return m.find(key) != m.end(); }
  int  getItem (const std::string & key) { return m.find(key)->second; } // will probably throw something or crash of no such key
  void setItem (const std::string & key, int val) { m[key] = val; }

  std::shared_ptr<monty::ndarray<std::string,1>> keys()
  {
    size_t size = m.size();
    auto res = std::shared_ptr<monty::ndarray<std::string,1>>(new monty::ndarray<std::string,1>(monty::shape((int)size)));

    ptrdiff_t i = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
      (*res)[i++] = it->first;

    return res;
  }

  std::shared_ptr<monty::ndarray<int,1>> values()
  {
    size_t size = m.size();
    auto res = std::shared_ptr<monty::ndarray<int,1>>(new monty::ndarray<int,1>(monty::shape((int)size)));

    ptrdiff_t i = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
      (*res)[i++] = it->second;

    return res;
  }

  StringIntMap::t clone();
};
// End of file 'src/fusion/cxx/IntMap_p.h'
// mosek.fusion.Utils.StringBuffer from file 'src/fusion/cxx/StringBuffer_p.h'
// namespace mosek::fusion::Utils
struct p_StringBuffer
{
  StringBuffer * _pubthis; 
  std::stringstream ss;

  p_StringBuffer(StringBuffer * _pubthis) : _pubthis(_pubthis) {}

  static p_StringBuffer * _get_impl(StringBuffer::t ptr) { return ptr->_impl.get(); }
  static p_StringBuffer * _get_impl(StringBuffer * ptr) { return ptr->_impl.get(); }

  static StringBuffer::t _new_StringBuffer() { return new StringBuffer(); }

  StringBuffer::t clear ();

  template<typename T> StringBuffer::t a (const monty::ndarray<T,1> & val);

  template<typename T> StringBuffer::t a (const T & val);

  StringBuffer::t lf ();
  std::string toString () const;
};

template<typename T> 
StringBuffer::t p_StringBuffer::a(const monty::ndarray<T,1> & val)
{
  if (val.size() > 0)
  {
    ss << val[0];
    for (int i = 1; i < val.size(); ++i)
      ss << "," << val[i];
  }
  return StringBuffer::t(_pubthis);
}
  
template<typename T>
StringBuffer::t p_StringBuffer::a (const T & val)
{
  ss << val;
  return _pubthis;
}


// End of file 'src/fusion/cxx/StringBuffer_p.h'
}
}
}
#endif
