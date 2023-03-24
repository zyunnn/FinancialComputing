<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.6">
  <compound kind="file">
    <name>Data.hpp</name>
    <path></path>
    <filename>_data_8hpp.html</filename>
    <includes id="_function_8hpp" name="Function.hpp" local="yes" imported="no">cfl/Function.hpp</includes>
    <class kind="class">cfl::Data::CashFlow</class>
    <class kind="class">cfl::Data::Swap</class>
    <class kind="class">cfl::Data::Option</class>
    <namespace>cfl::Data</namespace>
    <member kind="function">
      <type>Function</type>
      <name>discount</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>a4575eaa8279c938412253e3ff6269413</anchor>
      <arglist>(double dYield, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>discount</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>abbb1e8d9f7d299d60c846e5ae477a9a5</anchor>
      <arglist>(const Function &amp;rYield, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>volatility</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>aa9561ed3f83762f4260324be1b70f45c</anchor>
      <arglist>(double dSigma, double dLambda, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>forward</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>a2d070b6a8d3e7c19886dee13def2978b</anchor>
      <arglist>(double dSpot, double dCostOfCarry, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>forward</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>abe01a2be0546fad89dc429c1c99139e8</anchor>
      <arglist>(double dSpot, const Function &amp;rCostOfCarry, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>forward</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>ae8bb46ec753435fee82de68490d210b6</anchor>
      <arglist>(double dSpot, double dDividendYield, const Function &amp;rDiscount, double dInitialTime)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Error.hpp</name>
    <path></path>
    <filename>_error_8hpp.html</filename>
    <includes id="_macros_8hpp" name="Macros.hpp" local="yes" imported="no">cfl/Macros.hpp</includes>
    <class kind="class">cfl::Error</class>
    <namespace>cfl::NError</namespace>
    <member kind="function">
      <type>Error</type>
      <name>range</name>
      <anchorfile>namespacecfl_1_1_n_error.html</anchorfile>
      <anchor>a894a502c1601ee82feaadffd50b93002</anchor>
      <arglist>(const char *pWhere)</arglist>
    </member>
    <member kind="function">
      <type>Error</type>
      <name>sort</name>
      <anchorfile>namespacecfl_1_1_n_error.html</anchorfile>
      <anchor>a1eded1c862e839e80fb15a8ffbffcd67</anchor>
      <arglist>(const char *pWhere)</arglist>
    </member>
    <member kind="function">
      <type>Error</type>
      <name>size</name>
      <anchorfile>namespacecfl_1_1_n_error.html</anchorfile>
      <anchor>ac6ec8baaccb77da7ec8d57c2290a3a14</anchor>
      <arglist>(const char *pWhere)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Fit.hpp</name>
    <path></path>
    <filename>_fit_8hpp.html</filename>
    <includes id="_function_8hpp" name="Function.hpp" local="yes" imported="no">cfl/Function.hpp</includes>
    <class kind="struct">cfl::FitParam</class>
    <class kind="class">cfl::IFit</class>
    <class kind="class">cfl::Fit</class>
    <namespace>cfl::NFit</namespace>
    <member kind="function">
      <type>cfl::Fit</type>
      <name>linear</name>
      <anchorfile>namespacecfl_1_1_n_fit.html</anchorfile>
      <anchor>afbe6163f49ccaeb028a4972b8c913413</anchor>
      <arglist>(const cfl::Function &amp;rBasisF, const cfl::Function &amp;rFreeF=cfl::Function(0.))</arglist>
    </member>
    <member kind="function">
      <type>cfl::Fit</type>
      <name>linear_regression</name>
      <anchorfile>namespacecfl_1_1_n_fit.html</anchorfile>
      <anchor>aa5d75a9d98548dc4078607ab07477cde</anchor>
      <arglist>(const cfl::Function &amp;rBasisF, const cfl::Function &amp;rFreeF=cfl::Function(0.))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Function.hpp</name>
    <path></path>
    <filename>_function_8hpp.html</filename>
    <includes id="_error_8hpp" name="Error.hpp" local="yes" imported="no">cfl/Error.hpp</includes>
    <class kind="class">cfl::IFunction</class>
    <class kind="class">cfl::Function</class>
    <member kind="function">
      <type>Function</type>
      <name>apply</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaefc6f748aa55ba9af5888fc5939165e3</anchor>
      <arglist>(const Function &amp;rF, const std::function&lt; double(double)&gt; &amp;rOp)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>apply</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga1aad160b1231eab45c51bcbfd4ebb6ed</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG, const std::function&lt; double(double, double)&gt; &amp;rOp)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator-</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga9002e8a5719a0e0f8641c07c2776c65f</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator+</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga791881014381dc9299817a8ee54c01a4</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator+</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaebb9ffd9ebdf865392443b29a8ca3e81</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator+</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaa2901a847a20fd95fce20b72d94608ca</anchor>
      <arglist>(double dV, const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator-</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga780c9857fc017d7e7e0a189f37780853</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator-</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga89ab2b0065cd02be196a8eb8e2100bab</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator-</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga4b95eadaa3cd0c7555aa12ef099cb083</anchor>
      <arglist>(double dV, const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator*</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga23508570c1c867b26314fef7b138ec8f</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator*</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga7724362a5921d2ca77728d86c99a76f7</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator*</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaa56f481d9efec745cc2441743735f56e</anchor>
      <arglist>(double dV, const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator/</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga5a9609f238dcd27d489c120d300e8d2f</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator/</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaafb41bdcea13efa36de86fab86a8c8d7</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>operator/</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gadd70bb3e3d448678e90960b415fb253c</anchor>
      <arglist>(double dV, const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>pow</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga0ad815989b496eb88418f0cfacb86a8b</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>abs</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga57c16d6a064f32801f2e623e316d2c08</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>exp</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga52c70d0f89df857c746bc8cd465b4492</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>log</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga7a3f02432f55b86da5cda89b0ba989ff</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>sqrt</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gad5d6807fd56f4f4d275aef884a1a4db6</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>GaussRollback.hpp</name>
    <path></path>
    <filename>_gauss_rollback_8hpp.html</filename>
    <includes id="_macros_8hpp" name="Macros.hpp" local="yes" imported="no">Macros.hpp</includes>
    <class kind="class">cfl::IGaussRollback</class>
    <class kind="class">cfl::GaussRollback</class>
  </compound>
  <compound kind="file">
    <name>Index.hpp</name>
    <path></path>
    <filename>_index_8hpp.html</filename>
  </compound>
  <compound kind="file">
    <name>Interp.hpp</name>
    <path></path>
    <filename>_interp_8hpp.html</filename>
    <includes id="_function_8hpp" name="Function.hpp" local="yes" imported="no">cfl/Function.hpp</includes>
    <class kind="class">cfl::IInterp</class>
    <class kind="class">cfl::Interp</class>
    <namespace>cfl::NInterp</namespace>
    <member kind="function">
      <type>cfl::Interp</type>
      <name>linear</name>
      <anchorfile>namespacecfl_1_1_n_interp.html</anchorfile>
      <anchor>a67d5187b35fd70ff9dbf47d6e134f13a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Macros.hpp</name>
    <path></path>
    <filename>_macros_8hpp.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>PRECONDITION</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>gad98dcd871dcffebd5a39802226a429b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ASSERT</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>gaf343b20373ba49a92fce523e948f2ab3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>POSTCONDITION</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>ga41c215e9b1a35b82ddacbdbd2dfd707d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const double</type>
      <name>EPS</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>gae4eb6817537ee44fb52f581538da5ee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const unsigned</type>
      <name>IMAX</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>ga9af89fe2818b01bb5fc41f307a9fcee1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const double</type>
      <name>EPS</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>gae4eb6817537ee44fb52f581538da5ee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const unsigned</type>
      <name>IMAX</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>ga9af89fe2818b01bb5fc41f307a9fcee1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MultiFunction.hpp</name>
    <path></path>
    <filename>_multi_function_8hpp.html</filename>
    <includes id="_function_8hpp" name="Function.hpp" local="yes" imported="no">cfl/Function.hpp</includes>
    <class kind="class">cfl::IMultiFunction</class>
    <class kind="class">cfl::MultiFunction</class>
    <member kind="function">
      <type>MultiFunction</type>
      <name>apply</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga5247e31632f9710cbbf9accfe834383e</anchor>
      <arglist>(const MultiFunction &amp;rF, const std::function&lt; double(double)&gt; &amp;rOp)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>apply</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gaf3137b36af4def0bef224625158b1ee2</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG, const std::function&lt; double(double, double)&gt; &amp;rOp)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator-</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga40f53303aea62d73fc853819ed6e5837</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator+</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga37338e31a6a4f8f2905551ab72fb9c8b</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator+</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gacfd17352434d3815e3db45028ecf1a18</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator+</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga17b936b13bc246df5bfd4bc11fba6791</anchor>
      <arglist>(double dV, const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator-</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga34d84ccc5639453caed3df61e7851b90</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator-</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gac2de7180a86332c72defc54d89ccf0ea</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator-</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gadbb2599723603e89c6479675f3b27201</anchor>
      <arglist>(double dV, const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator*</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gaef6a511dd49168f6ba0552d932160954</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator*</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gaf96b53e2581d663f660be10cceb4d939</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator*</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga715f406b62c8850e1afccf93d0f31a03</anchor>
      <arglist>(double dV, const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator/</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga2659b4388ba89c590e871545cc1f9c24</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator/</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gaa277497fea39fc9bf6e5253761a0fd9c</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>operator/</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga12a036f1c869d65a4900f5b2bb2420da</anchor>
      <arglist>(double dV, const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>pow</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga92da3fb0054e172cdde524a7d95f0781</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>abs</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga22c909396db6796296bc88664fe3ca05</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>exp</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga4533cffaa9d943f0d499cd326f9cad7a</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>log</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga7be7274a542c736132f5b2dc6973df04</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>sqrt</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga3d3bb4ca7588f011089ac5930ff5ef9e</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>toMultiFunction</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga14973cccaa304063c3b3203362e6f965</anchor>
      <arglist>(const Function &amp;rF, unsigned iArg, unsigned iDim)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>toMultiFunction</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga6efeec5029b76cd45ad07b114a445d79</anchor>
      <arglist>(const MultiFunction &amp;rF, const std::vector&lt; unsigned &gt; &amp;rArg, const std::valarray&lt; double &gt; &amp;rOtherArg)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>toFunction</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga21229af02dbb2bbfbbf365d0de718073</anchor>
      <arglist>(const MultiFunction &amp;rF, unsigned iArg=0, const std::valarray&lt; double &gt; &amp;rOtherArg=std::valarray&lt; double &gt;())</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Root.hpp</name>
    <path></path>
    <filename>_root_8hpp.html</filename>
    <includes id="_function_8hpp" name="Function.hpp" local="yes" imported="no">cfl/Function.hpp</includes>
    <class kind="class">cfl::IRoot</class>
    <class kind="class">cfl::Root</class>
  </compound>
  <compound kind="file">
    <name>RootD.hpp</name>
    <path></path>
    <filename>_root_d_8hpp.html</filename>
    <includes id="_function_8hpp" name="Function.hpp" local="yes" imported="no">cfl/Function.hpp</includes>
    <class kind="class">cfl::IRootD</class>
    <class kind="class">cfl::RootD</class>
    <namespace>cfl::NRootD</namespace>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>newton</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>aae56d8f9628a19b13bbd7c0bd86f5156</anchor>
      <arglist>(double dAbsErr, double dRelErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>newton</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>a1f08d527c6968b9bbfa317817a278995</anchor>
      <arglist>(double dFuncErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>secant</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>a07d41fd379a498b6f08c5a2b0bde28b0</anchor>
      <arglist>(double dAbsErr, double dRelErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>secant</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>ac29bf6e12d1322fbb6127fc2a380666e</anchor>
      <arglist>(double dFuncErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>steffenson</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>a865f6ec3ebdec67f894ea8791b7241d5</anchor>
      <arglist>(double dAbsErr, double dRelErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>steffenson</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>ad2339171bfb04c0dee341dfd0cb7822f</anchor>
      <arglist>(double dFuncErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::Data::CashFlow</name>
    <filename>classcfl_1_1_data_1_1_cash_flow.html</filename>
    <member kind="variable">
      <type>double</type>
      <name>notional</name>
      <anchorfile>classcfl_1_1_data_1_1_cash_flow.html</anchorfile>
      <anchor>a83e6efbb967ea198fdcf89fd182768d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>rate</name>
      <anchorfile>classcfl_1_1_data_1_1_cash_flow.html</anchorfile>
      <anchor>a1db901b942d09692afaa53ba695e1f2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>period</name>
      <anchorfile>classcfl_1_1_data_1_1_cash_flow.html</anchorfile>
      <anchor>a1908f61bd9961959a6fe84a839302f99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>numberOfPayments</name>
      <anchorfile>classcfl_1_1_data_1_1_cash_flow.html</anchorfile>
      <anchor>ac02486d6500d240bdb0f6f8b615fc19c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::Error</name>
    <filename>classcfl_1_1_error.html</filename>
    <base>std::exception</base>
    <member kind="function">
      <type></type>
      <name>Error</name>
      <anchorfile>classcfl_1_1_error.html</anchorfile>
      <anchor>ac4e18e7c69d7496311499efcee71109d</anchor>
      <arglist>(const char *pWhere)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>what</name>
      <anchorfile>classcfl_1_1_error.html</anchorfile>
      <anchor>a62f331fc93c5d950c80db91c6b923ada</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::Fit</name>
    <filename>classcfl_1_1_fit.html</filename>
    <member kind="function">
      <type></type>
      <name>Fit</name>
      <anchorfile>classcfl_1_1_fit.html</anchorfile>
      <anchor>ac6bf5ff8f24b17664d31529cef6c2b03</anchor>
      <arglist>(IFit *pNewP=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign</name>
      <anchorfile>classcfl_1_1_fit.html</anchorfile>
      <anchor>af0db58671e5abc17ddeebf6ea1ce21a1</anchor>
      <arglist>(InIt1 itArgBegin, InIt1 itArgEnd, InIt2 itValBegin)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign</name>
      <anchorfile>classcfl_1_1_fit.html</anchorfile>
      <anchor>ad5bd1feb4e2c20b8c1917b7a47bb909f</anchor>
      <arglist>(InIt1 itArgBegin, InIt1 itArgEnd, InIt2 itValBegin, InIt3 itWtBegin, bool bChi2=true)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>fit</name>
      <anchorfile>classcfl_1_1_fit.html</anchorfile>
      <anchor>a3f5e9bfc7b8e4bfc934b029bec23397a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>err</name>
      <anchorfile>classcfl_1_1_fit.html</anchorfile>
      <anchor>a9fdfb6dd1cdf9f7ddfbec2e726978d95</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FitParam</type>
      <name>param</name>
      <anchorfile>classcfl_1_1_fit.html</anchorfile>
      <anchor>adfbefe4d1df265effee035e0b60e0280</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cfl::FitParam</name>
    <filename>structcfl_1_1_fit_param.html</filename>
    <member kind="variable">
      <type>std::valarray&lt; double &gt;</type>
      <name>fit</name>
      <anchorfile>structcfl_1_1_fit_param.html</anchorfile>
      <anchor>a5d5e6ddf0c7881a64becda3a247f4a83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::valarray&lt; double &gt;</type>
      <name>cov</name>
      <anchorfile>structcfl_1_1_fit_param.html</anchorfile>
      <anchor>aaf3ef6f509422f3d6f8a5e1722246168</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>chi2</name>
      <anchorfile>structcfl_1_1_fit_param.html</anchorfile>
      <anchor>a91f7e92ad34f8a79ef6d350a52bc7b01</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::Function</name>
    <filename>classcfl_1_1_function.html</filename>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a30214a8eafd7442f2ff5cfc83131b4b3</anchor>
      <arglist>(double dV=0., double dL=-std::numeric_limits&lt; double &gt;::max(), double dR=std::numeric_limits&lt; double &gt;::max())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>aaf7e32ded0390fbe8ccdeed8612a5330</anchor>
      <arglist>(IFunction *pNewP)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a9be1ca7540ee77144201ee40e779b5cb</anchor>
      <arglist>(const std::function&lt; double(double)&gt; &amp;rF, double dL=-std::numeric_limits&lt; double &gt;::max(), double dR=std::numeric_limits&lt; double &gt;::max())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a67f948aaac73c26826f65a987f479a9c</anchor>
      <arglist>(const std::function&lt; double(double)&gt; &amp;rF, const std::function&lt; bool(double)&gt; &amp;rBelongs)</arglist>
    </member>
    <member kind="function">
      <type>Function &amp;</type>
      <name>operator=</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a7df110206721b324175ce8887ec73d5f</anchor>
      <arglist>(double dV)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator()</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a8cc45c57aa5bcf30ec0bf6acce3c7670</anchor>
      <arglist>(double dX) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>belongs</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a85bc8e51a6eb4e33405e6a187b745183</anchor>
      <arglist>(double dX) const</arglist>
    </member>
    <member kind="function">
      <type>Function &amp;</type>
      <name>operator+=</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a8a88696759715a556080acf707672e3e</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function &amp;</type>
      <name>operator*=</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a7cbd41b8b12e8785d22a12acf05f4071</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function &amp;</type>
      <name>operator-=</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a70a3d18fd2dcfcb5e7f8e727838a8516</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function &amp;</type>
      <name>operator/=</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a8f48110269945468be472c1d1b1dee45</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function &amp;</type>
      <name>operator+=</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a890a70632ba20a8df049a048ae421adc</anchor>
      <arglist>(double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function &amp;</type>
      <name>operator-=</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>a8572a0cb5c0f540aec525942c2741110</anchor>
      <arglist>(double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function &amp;</type>
      <name>operator*=</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>aac902b50af64a184b49cc8e212f384c2</anchor>
      <arglist>(double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function &amp;</type>
      <name>operator/=</name>
      <anchorfile>classcfl_1_1_function.html</anchorfile>
      <anchor>af5a2a2f2305f9934cabd4ecf48af0f42</anchor>
      <arglist>(double dV)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::GaussRollback</name>
    <filename>classcfl_1_1_gauss_rollback.html</filename>
    <member kind="function">
      <type></type>
      <name>GaussRollback</name>
      <anchorfile>classcfl_1_1_gauss_rollback.html</anchorfile>
      <anchor>aee8f61ec6514ee2837038f04361704e2</anchor>
      <arglist>(IGaussRollback *pNewP=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign</name>
      <anchorfile>classcfl_1_1_gauss_rollback.html</anchorfile>
      <anchor>a7fb906726094b5b9b61a4de4a5320c41</anchor>
      <arglist>(unsigned iSize, double dH, double dVar)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rollback</name>
      <anchorfile>classcfl_1_1_gauss_rollback.html</anchorfile>
      <anchor>ab6c7d0f33435160c80ea3c57650428d1</anchor>
      <arglist>(std::valarray&lt; double &gt; &amp;rValues) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rollback</name>
      <anchorfile>classcfl_1_1_gauss_rollback.html</anchorfile>
      <anchor>a9294fcc52e425d805248d8a00f99c9c7</anchor>
      <arglist>(std::valarray&lt; double &gt; &amp;rValues, std::valarray&lt; double &gt; &amp;rDelta) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rollback</name>
      <anchorfile>classcfl_1_1_gauss_rollback.html</anchorfile>
      <anchor>a25d07eb8274cea2c6311cfcd495a9771</anchor>
      <arglist>(std::valarray&lt; double &gt; &amp;rValues, std::valarray&lt; double &gt; &amp;rDelta, std::valarray&lt; double &gt; &amp;rGamma) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>vega</name>
      <anchorfile>classcfl_1_1_gauss_rollback.html</anchorfile>
      <anchor>ad74fbe4c9454a49589e7959fb9f3704b</anchor>
      <arglist>(std::valarray&lt; double &gt; &amp;rGammaToVega) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::IFit</name>
    <filename>classcfl_1_1_i_fit.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IFit</name>
      <anchorfile>classcfl_1_1_i_fit.html</anchorfile>
      <anchor>a0f1ad3a4b542cb3c18895efb88f37c7d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual IFit *</type>
      <name>newObject</name>
      <anchorfile>classcfl_1_1_i_fit.html</anchorfile>
      <anchor>ad9d14bda885544eee2452c854992515d</anchor>
      <arglist>(const std::vector&lt; double &gt; &amp;rArg, const std::vector&lt; double &gt; &amp;rVal, const std::vector&lt; double &gt; &amp;rW, bool bChi2) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Function</type>
      <name>fit</name>
      <anchorfile>classcfl_1_1_i_fit.html</anchorfile>
      <anchor>a9aa6875c865b7e7a0c72a6035a6a512c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Function</type>
      <name>err</name>
      <anchorfile>classcfl_1_1_i_fit.html</anchorfile>
      <anchor>ad0f069690916e9503b5194293053a63b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FitParam</type>
      <name>param</name>
      <anchorfile>classcfl_1_1_i_fit.html</anchorfile>
      <anchor>acb2cb24fc27a09eb03f140519f0c8892</anchor>
      <arglist>() const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::IFunction</name>
    <filename>classcfl_1_1_i_function.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IFunction</name>
      <anchorfile>classcfl_1_1_i_function.html</anchorfile>
      <anchor>a9c437e68e806a7f590985935ea1539ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>operator()</name>
      <anchorfile>classcfl_1_1_i_function.html</anchorfile>
      <anchor>a2b92b7827fcd085c30481d66d2b823e8</anchor>
      <arglist>(double dX) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>belongs</name>
      <anchorfile>classcfl_1_1_i_function.html</anchorfile>
      <anchor>a1a91da27455f02e77aa91895261dbc53</anchor>
      <arglist>(double dX) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::IGaussRollback</name>
    <filename>classcfl_1_1_i_gauss_rollback.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IGaussRollback</name>
      <anchorfile>classcfl_1_1_i_gauss_rollback.html</anchorfile>
      <anchor>a9eb352964065abf762690b7cdc9a6c79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual IGaussRollback *</type>
      <name>newObject</name>
      <anchorfile>classcfl_1_1_i_gauss_rollback.html</anchorfile>
      <anchor>ad54d0df0fd31740d2a6f4694ae906a2c</anchor>
      <arglist>(unsigned iSize, double dH, double dVar) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>rollback</name>
      <anchorfile>classcfl_1_1_i_gauss_rollback.html</anchorfile>
      <anchor>a5007e6a9cbaeb8334130e9aa774235ff</anchor>
      <arglist>(std::valarray&lt; double &gt; &amp;rValues) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::IInterp</name>
    <filename>classcfl_1_1_i_interp.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IInterp</name>
      <anchorfile>classcfl_1_1_i_interp.html</anchorfile>
      <anchor>a9d10ce5642dda4db0397c2b0dfe8a7f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Function</type>
      <name>interpolate</name>
      <anchorfile>classcfl_1_1_i_interp.html</anchorfile>
      <anchor>a0ff5a765df9e6bd7145ced97c5894580</anchor>
      <arglist>(const std::vector&lt; double &gt; &amp;rArg, const std::vector&lt; double &gt; &amp;rVal) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::IMultiFunction</name>
    <filename>classcfl_1_1_i_multi_function.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IMultiFunction</name>
      <anchorfile>classcfl_1_1_i_multi_function.html</anchorfile>
      <anchor>ad279e67c0cac702f54666f07d650001e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>operator()</name>
      <anchorfile>classcfl_1_1_i_multi_function.html</anchorfile>
      <anchor>aa9294beb103344785106f1300d38e901</anchor>
      <arglist>(const std::valarray&lt; double &gt; &amp;rX) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>belongs</name>
      <anchorfile>classcfl_1_1_i_multi_function.html</anchorfile>
      <anchor>a72177a54755bf19b51efc9abda58f822</anchor>
      <arglist>(const std::valarray&lt; double &gt; &amp;rX) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned</type>
      <name>dim</name>
      <anchorfile>classcfl_1_1_i_multi_function.html</anchorfile>
      <anchor>a5ffbe04a403010670353bed3748ffff7</anchor>
      <arglist>() const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::Interp</name>
    <filename>classcfl_1_1_interp.html</filename>
    <member kind="function">
      <type></type>
      <name>Interp</name>
      <anchorfile>classcfl_1_1_interp.html</anchorfile>
      <anchor>a0f4bd3f32e580f9f7fbbe829330d839a</anchor>
      <arglist>(IInterp *pNewP=0)</arglist>
    </member>
    <member kind="function">
      <type>cfl::Function</type>
      <name>interpolate</name>
      <anchorfile>classcfl_1_1_interp.html</anchorfile>
      <anchor>a1b8a5ef5841332f96b365528c2d9b124</anchor>
      <arglist>(It1 itArgBegin, It1 itArgEnd, It2 itValBegin) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::IRoot</name>
    <filename>classcfl_1_1_i_root.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IRoot</name>
      <anchorfile>classcfl_1_1_i_root.html</anchorfile>
      <anchor>a18e2eb391e4a1d5bfdcaeb59a15b9c54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>find</name>
      <anchorfile>classcfl_1_1_i_root.html</anchorfile>
      <anchor>ab03067521ba09b66edb5356f500d842c</anchor>
      <arglist>(const cfl::Function &amp;rF, double dL, double dR) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::IRootD</name>
    <filename>classcfl_1_1_i_root_d.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IRootD</name>
      <anchorfile>classcfl_1_1_i_root_d.html</anchorfile>
      <anchor>a1c5ec775ccc58268c81cc5d337ced224</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>find</name>
      <anchorfile>classcfl_1_1_i_root_d.html</anchorfile>
      <anchor>a4746908f4b01f75a728d1cb7fdc51bed</anchor>
      <arglist>(const cfl::Function &amp;rF, const cfl::Function &amp;rDF, double dX0) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::MultiFunction</name>
    <filename>classcfl_1_1_multi_function.html</filename>
    <member kind="function">
      <type></type>
      <name>MultiFunction</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a42d5d589ee32dcd18a19c1adfade030b</anchor>
      <arglist>(double dV=0., unsigned iDim=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiFunction</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>af45d1aec06c75811eb16e350de9db924</anchor>
      <arglist>(IMultiFunction *pNewF)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiFunction</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>ad0a32c89a430cfe7e12094910e630240</anchor>
      <arglist>(const std::function&lt; double(const std::valarray&lt; double &gt; &amp;)&gt; &amp;rF, unsigned iDim)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiFunction</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a2220c9c07545974aadc9cc07cee53744</anchor>
      <arglist>(const std::function&lt; double(const std::valarray&lt; double &gt; &amp;)&gt; &amp;rF, const std::function&lt; bool(const std::valarray&lt; double &gt; &amp;)&gt; &amp;rBelongs, unsigned iDim)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction &amp;</type>
      <name>operator=</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a51d80cd4f265879a2dff822d51096287</anchor>
      <arglist>(double dV)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator()</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a2d46129063d7fe61a7ece8dcf033a2c0</anchor>
      <arglist>(const std::valarray&lt; double &gt; &amp;rX) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>belongs</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a6fd434bbde5ce79146d7edd427a1087c</anchor>
      <arglist>(const std::valarray&lt; double &gt; &amp;rX) const</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>dim</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>aa9aa5321bdebc90b12f248be40368eaa</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction &amp;</type>
      <name>operator+=</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>af02f1dd710ae79ccf2e4c969d18e1d5c</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction &amp;</type>
      <name>operator*=</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>ab8b0cd064dc80f6a7b36aaa2f01c9955</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction &amp;</type>
      <name>operator-=</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>acfd1217b31b20de09123e7319bf125c8</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction &amp;</type>
      <name>operator/=</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a53c73fb1d4e0027e41f4020ee7dbab90</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction &amp;</type>
      <name>operator+=</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a607d84651a2d3deb6e45f7ca0a28606e</anchor>
      <arglist>(double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction &amp;</type>
      <name>operator-=</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a8c9d19a1a15ab9c6f3894014b0883255</anchor>
      <arglist>(double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction &amp;</type>
      <name>operator*=</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a51a8a7a626acb1be0e2344762b8c929a</anchor>
      <arglist>(double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction &amp;</type>
      <name>operator/=</name>
      <anchorfile>classcfl_1_1_multi_function.html</anchorfile>
      <anchor>a28ffea8798d658935d59f7d3f8f9deb9</anchor>
      <arglist>(double dV)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::Data::Option</name>
    <filename>classcfl_1_1_data_1_1_option.html</filename>
    <member kind="variable">
      <type>double</type>
      <name>number</name>
      <anchorfile>classcfl_1_1_data_1_1_option.html</anchorfile>
      <anchor>ab2b6d6c3d61025026e5760f132fc889b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>maturity</name>
      <anchorfile>classcfl_1_1_data_1_1_option.html</anchorfile>
      <anchor>a55d27d9c6ddfe276c4d1f8e3564ac07a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>strike</name>
      <anchorfile>classcfl_1_1_data_1_1_option.html</anchorfile>
      <anchor>aa12b76f99531f018f7e7745496eed916</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::Root</name>
    <filename>classcfl_1_1_root.html</filename>
    <member kind="function">
      <type></type>
      <name>Root</name>
      <anchorfile>classcfl_1_1_root.html</anchorfile>
      <anchor>a66713703ed07069ac3bc14b8617fde05</anchor>
      <arglist>(IRoot *pNewP=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>find</name>
      <anchorfile>classcfl_1_1_root.html</anchorfile>
      <anchor>a42bad8446c51733772e253b33864c979</anchor>
      <arglist>(const cfl::Function &amp;rF, double dL, double dR) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::RootD</name>
    <filename>classcfl_1_1_root_d.html</filename>
    <member kind="function">
      <type></type>
      <name>RootD</name>
      <anchorfile>classcfl_1_1_root_d.html</anchorfile>
      <anchor>a9ef09208a8fb2f2eed4e96c033afb02b</anchor>
      <arglist>(IRootD *pNewP=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>find</name>
      <anchorfile>classcfl_1_1_root_d.html</anchorfile>
      <anchor>ada7cfd9add7bc155570eb5c3c25460eb</anchor>
      <arglist>(const cfl::Function &amp;rF, const cfl::Function &amp;rDF, double dX0) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cfl::Data::Swap</name>
    <filename>classcfl_1_1_data_1_1_swap.html</filename>
    <base>cfl::Data::CashFlow</base>
    <member kind="function">
      <type></type>
      <name>Swap</name>
      <anchorfile>classcfl_1_1_data_1_1_swap.html</anchorfile>
      <anchor>a0f3a707e0a0789c742a74adc380bd617</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Swap</name>
      <anchorfile>classcfl_1_1_data_1_1_swap.html</anchorfile>
      <anchor>a625a0fb180d14af005daa1ffebf45258</anchor>
      <arglist>(const CashFlow &amp;rCashFlow, bool bPayFloat=true)</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>payFloat</name>
      <anchorfile>classcfl_1_1_data_1_1_swap.html</anchorfile>
      <anchor>a288b309704865d5cf5b1679b341c4236</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>cfl::Data</name>
    <filename>namespacecfl_1_1_data.html</filename>
    <class kind="class">cfl::Data::CashFlow</class>
    <class kind="class">cfl::Data::Option</class>
    <class kind="class">cfl::Data::Swap</class>
    <member kind="function">
      <type>Function</type>
      <name>discount</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>a4575eaa8279c938412253e3ff6269413</anchor>
      <arglist>(double dYield, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>discount</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>abbb1e8d9f7d299d60c846e5ae477a9a5</anchor>
      <arglist>(const Function &amp;rYield, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>volatility</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>aa9561ed3f83762f4260324be1b70f45c</anchor>
      <arglist>(double dSigma, double dLambda, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>forward</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>a2d070b6a8d3e7c19886dee13def2978b</anchor>
      <arglist>(double dSpot, double dCostOfCarry, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>forward</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>abe01a2be0546fad89dc429c1c99139e8</anchor>
      <arglist>(double dSpot, const Function &amp;rCostOfCarry, double dInitialTime)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>forward</name>
      <anchorfile>namespacecfl_1_1_data.html</anchorfile>
      <anchor>ae8bb46ec753435fee82de68490d210b6</anchor>
      <arglist>(double dSpot, double dDividendYield, const Function &amp;rDiscount, double dInitialTime)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>cfl::NError</name>
    <filename>namespacecfl_1_1_n_error.html</filename>
    <member kind="function">
      <type>Error</type>
      <name>range</name>
      <anchorfile>namespacecfl_1_1_n_error.html</anchorfile>
      <anchor>a894a502c1601ee82feaadffd50b93002</anchor>
      <arglist>(const char *pWhere)</arglist>
    </member>
    <member kind="function">
      <type>Error</type>
      <name>sort</name>
      <anchorfile>namespacecfl_1_1_n_error.html</anchorfile>
      <anchor>a1eded1c862e839e80fb15a8ffbffcd67</anchor>
      <arglist>(const char *pWhere)</arglist>
    </member>
    <member kind="function">
      <type>Error</type>
      <name>size</name>
      <anchorfile>namespacecfl_1_1_n_error.html</anchorfile>
      <anchor>ac6ec8baaccb77da7ec8d57c2290a3a14</anchor>
      <arglist>(const char *pWhere)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>cfl::NFit</name>
    <filename>namespacecfl_1_1_n_fit.html</filename>
    <member kind="function">
      <type>cfl::Fit</type>
      <name>linear</name>
      <anchorfile>namespacecfl_1_1_n_fit.html</anchorfile>
      <anchor>afbe6163f49ccaeb028a4972b8c913413</anchor>
      <arglist>(const cfl::Function &amp;rBasisF, const cfl::Function &amp;rFreeF=cfl::Function(0.))</arglist>
    </member>
    <member kind="function">
      <type>cfl::Fit</type>
      <name>linear_regression</name>
      <anchorfile>namespacecfl_1_1_n_fit.html</anchorfile>
      <anchor>aa5d75a9d98548dc4078607ab07477cde</anchor>
      <arglist>(const cfl::Function &amp;rBasisF, const cfl::Function &amp;rFreeF=cfl::Function(0.))</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>cfl::NInterp</name>
    <filename>namespacecfl_1_1_n_interp.html</filename>
    <member kind="function">
      <type>cfl::Interp</type>
      <name>linear</name>
      <anchorfile>namespacecfl_1_1_n_interp.html</anchorfile>
      <anchor>a67d5187b35fd70ff9dbf47d6e134f13a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>cfl::NRootD</name>
    <filename>namespacecfl_1_1_n_root_d.html</filename>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>newton</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>aae56d8f9628a19b13bbd7c0bd86f5156</anchor>
      <arglist>(double dAbsErr, double dRelErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>newton</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>a1f08d527c6968b9bbfa317817a278995</anchor>
      <arglist>(double dFuncErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>secant</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>a07d41fd379a498b6f08c5a2b0bde28b0</anchor>
      <arglist>(double dAbsErr, double dRelErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>secant</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>ac29bf6e12d1322fbb6127fc2a380666e</anchor>
      <arglist>(double dFuncErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>steffenson</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>a865f6ec3ebdec67f894ea8791b7241d5</anchor>
      <arglist>(double dAbsErr, double dRelErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
    <member kind="function">
      <type>cfl::RootD</type>
      <name>steffenson</name>
      <anchorfile>namespacecfl_1_1_n_root_d.html</anchorfile>
      <anchor>ad2339171bfb04c0dee341dfd0cb7822f</anchor>
      <arglist>(double dFuncErr, unsigned iMaxSteps=IMAX)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>cflCommonElements</name>
    <title>Common elements of financial models.</title>
    <filename>group__cfl_common_elements.html</filename>
    <subgroup>cflData</subgroup>
  </compound>
  <compound kind="group">
    <name>cflData</name>
    <title>Data structures.</title>
    <filename>group__cfl_data.html</filename>
    <namespace>cfl::Data</namespace>
  </compound>
  <compound kind="group">
    <name>cflMisc</name>
    <title>Auxiliary items.</title>
    <filename>group__cfl_misc.html</filename>
    <subgroup>cflError</subgroup>
    <subgroup>cflMacros</subgroup>
  </compound>
  <compound kind="group">
    <name>cflError</name>
    <title>Exceptions.</title>
    <filename>group__cfl_error.html</filename>
    <namespace>cfl::NError</namespace>
    <class kind="class">cfl::Error</class>
  </compound>
  <compound kind="group">
    <name>cflFit</name>
    <title>Fitting of one-dimensional functions.</title>
    <filename>group__cfl_fit.html</filename>
    <namespace>cfl::NFit</namespace>
    <class kind="struct">cfl::FitParam</class>
    <class kind="class">cfl::IFit</class>
    <class kind="class">cfl::Fit</class>
  </compound>
  <compound kind="group">
    <name>cflFunctionObjects</name>
    <title>Function objects.</title>
    <filename>group__cfl_function_objects.html</filename>
    <subgroup>cflFunction</subgroup>
    <subgroup>cflMultiFunction</subgroup>
  </compound>
  <compound kind="group">
    <name>cflFunction</name>
    <title>One-dimensional function object.</title>
    <filename>group__cfl_function.html</filename>
    <class kind="class">cfl::IFunction</class>
    <class kind="class">cfl::Function</class>
    <member kind="function">
      <type>Function</type>
      <name>cfl::apply</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaefc6f748aa55ba9af5888fc5939165e3</anchor>
      <arglist>(const Function &amp;rF, const std::function&lt; double(double)&gt; &amp;rOp)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::apply</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga1aad160b1231eab45c51bcbfd4ebb6ed</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG, const std::function&lt; double(double, double)&gt; &amp;rOp)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator-</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga9002e8a5719a0e0f8641c07c2776c65f</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator+</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga791881014381dc9299817a8ee54c01a4</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator+</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaebb9ffd9ebdf865392443b29a8ca3e81</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator+</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaa2901a847a20fd95fce20b72d94608ca</anchor>
      <arglist>(double dV, const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator-</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga780c9857fc017d7e7e0a189f37780853</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator-</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga89ab2b0065cd02be196a8eb8e2100bab</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator-</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga4b95eadaa3cd0c7555aa12ef099cb083</anchor>
      <arglist>(double dV, const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator*</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga23508570c1c867b26314fef7b138ec8f</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator*</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga7724362a5921d2ca77728d86c99a76f7</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator*</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaa56f481d9efec745cc2441743735f56e</anchor>
      <arglist>(double dV, const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator/</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga5a9609f238dcd27d489c120d300e8d2f</anchor>
      <arglist>(const Function &amp;rF, const Function &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator/</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gaafb41bdcea13efa36de86fab86a8c8d7</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::operator/</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gadd70bb3e3d448678e90960b415fb253c</anchor>
      <arglist>(double dV, const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::pow</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga0ad815989b496eb88418f0cfacb86a8b</anchor>
      <arglist>(const Function &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::abs</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga57c16d6a064f32801f2e623e316d2c08</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::exp</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga52c70d0f89df857c746bc8cd465b4492</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::log</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>ga7a3f02432f55b86da5cda89b0ba989ff</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::sqrt</name>
      <anchorfile>group__cfl_function.html</anchorfile>
      <anchor>gad5d6807fd56f4f4d275aef884a1a4db6</anchor>
      <arglist>(const Function &amp;rF)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>cflGaussRollback</name>
    <title>Gaussian conditional expectation.</title>
    <filename>group__cfl_gauss_rollback.html</filename>
    <class kind="class">cfl::IGaussRollback</class>
    <class kind="class">cfl::GaussRollback</class>
  </compound>
  <compound kind="group">
    <name>cflNumeric</name>
    <title>Numerical methods.</title>
    <filename>group__cfl_numeric.html</filename>
    <subgroup>cflFit</subgroup>
    <subgroup>cflGaussRollback</subgroup>
    <subgroup>cflInterp</subgroup>
    <subgroup>cflRoot</subgroup>
    <subgroup>cflRootD</subgroup>
  </compound>
  <compound kind="group">
    <name>cflInterp</name>
    <title>Interpolation of one-dimensional functions.</title>
    <filename>group__cfl_interp.html</filename>
    <namespace>cfl::NInterp</namespace>
    <class kind="class">cfl::IInterp</class>
    <class kind="class">cfl::Interp</class>
  </compound>
  <compound kind="group">
    <name>cflMacros</name>
    <title>Macros and constants.</title>
    <filename>group__cfl_macros.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>PRECONDITION</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>gad98dcd871dcffebd5a39802226a429b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ASSERT</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>gaf343b20373ba49a92fce523e948f2ab3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>POSTCONDITION</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>ga41c215e9b1a35b82ddacbdbd2dfd707d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const double</type>
      <name>cfl::EPS</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>gae4eb6817537ee44fb52f581538da5ee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const unsigned</type>
      <name>cfl::IMAX</name>
      <anchorfile>group__cfl_macros.html</anchorfile>
      <anchor>ga9af89fe2818b01bb5fc41f307a9fcee1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>cflMultiFunction</name>
    <title>Multi-dimensional function object.</title>
    <filename>group__cfl_multi_function.html</filename>
    <class kind="class">cfl::IMultiFunction</class>
    <class kind="class">cfl::MultiFunction</class>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::apply</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga5247e31632f9710cbbf9accfe834383e</anchor>
      <arglist>(const MultiFunction &amp;rF, const std::function&lt; double(double)&gt; &amp;rOp)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::apply</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gaf3137b36af4def0bef224625158b1ee2</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG, const std::function&lt; double(double, double)&gt; &amp;rOp)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator-</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga40f53303aea62d73fc853819ed6e5837</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator+</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga37338e31a6a4f8f2905551ab72fb9c8b</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator+</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gacfd17352434d3815e3db45028ecf1a18</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator+</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga17b936b13bc246df5bfd4bc11fba6791</anchor>
      <arglist>(double dV, const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator-</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga34d84ccc5639453caed3df61e7851b90</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator-</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gac2de7180a86332c72defc54d89ccf0ea</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator-</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gadbb2599723603e89c6479675f3b27201</anchor>
      <arglist>(double dV, const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator*</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gaef6a511dd49168f6ba0552d932160954</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator*</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gaf96b53e2581d663f660be10cceb4d939</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator*</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga715f406b62c8850e1afccf93d0f31a03</anchor>
      <arglist>(double dV, const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator/</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga2659b4388ba89c590e871545cc1f9c24</anchor>
      <arglist>(const MultiFunction &amp;rF, const MultiFunction &amp;rG)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator/</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>gaa277497fea39fc9bf6e5253761a0fd9c</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::operator/</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga12a036f1c869d65a4900f5b2bb2420da</anchor>
      <arglist>(double dV, const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::pow</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga92da3fb0054e172cdde524a7d95f0781</anchor>
      <arglist>(const MultiFunction &amp;rF, double dV)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::abs</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga22c909396db6796296bc88664fe3ca05</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::exp</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga4533cffaa9d943f0d499cd326f9cad7a</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::log</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga7be7274a542c736132f5b2dc6973df04</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::sqrt</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga3d3bb4ca7588f011089ac5930ff5ef9e</anchor>
      <arglist>(const MultiFunction &amp;rF)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::toMultiFunction</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga14973cccaa304063c3b3203362e6f965</anchor>
      <arglist>(const Function &amp;rF, unsigned iArg, unsigned iDim)</arglist>
    </member>
    <member kind="function">
      <type>MultiFunction</type>
      <name>cfl::toMultiFunction</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga6efeec5029b76cd45ad07b114a445d79</anchor>
      <arglist>(const MultiFunction &amp;rF, const std::vector&lt; unsigned &gt; &amp;rArg, const std::valarray&lt; double &gt; &amp;rOtherArg)</arglist>
    </member>
    <member kind="function">
      <type>Function</type>
      <name>cfl::toFunction</name>
      <anchorfile>group__cfl_multi_function.html</anchorfile>
      <anchor>ga21229af02dbb2bbfbbf365d0de718073</anchor>
      <arglist>(const MultiFunction &amp;rF, unsigned iArg=0, const std::valarray&lt; double &gt; &amp;rOtherArg=std::valarray&lt; double &gt;())</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>cflRoot</name>
    <title>Root finding with bracketing algorithm.</title>
    <filename>group__cfl_root.html</filename>
    <class kind="class">cfl::IRoot</class>
    <class kind="class">cfl::Root</class>
  </compound>
  <compound kind="group">
    <name>cflRootD</name>
    <title>RootD finding with polishing algorithm.</title>
    <filename>group__cfl_root_d.html</filename>
    <namespace>cfl::NRootD</namespace>
    <class kind="class">cfl::IRootD</class>
    <class kind="class">cfl::RootD</class>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Library for the course &quot;Financial Computing with C++&quot;</title>
    <filename>index.html</filename>
  </compound>
</tagfile>
