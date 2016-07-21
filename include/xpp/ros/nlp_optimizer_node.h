/**
 @file    nlp_optimizer_node.cc
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Jul 21, 2016
 @brief   Declares the interface to the ROS node that initializes/calls the NLP optimizer.
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ROS_NLP_OPTIMIZER_NODE_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ROS_NLP_OPTIMIZER_NODE_H_

#include <xpp/ros/optimizer_node_base.h>
#include <xpp/zmp/nlp_facade.h>
#include <xpp/ros/optimization_visualizer.h>

#include <xpp_opt/RequiredInfoNlp.h>        // receive
#include <xpp_opt/OptimizedParametersNlp.h> // send

namespace xpp {
namespace ros {

class NlpOptimizerNode : public OptimizerNodeBase {
public:
  typedef xpp::zmp::NlpFacade NlpFacade;
  typedef xpp::hyq::LegID LegID;
  typedef xpp_opt::RequiredInfoNlp ReqInfoMsg;
  typedef xpp_opt::OptimizedParametersNlp OptParamMsg;

public:
  NlpOptimizerNode ();
  virtual ~NlpOptimizerNode () {};

private:
  NlpFacade nlp_facade_;
  void UpdateCurrentState(const ReqInfoMsg& msg);
  void OptimizeTrajectory();
  void PublishOptimizedValues() const;

  int curr_swingleg_;
  xpp::hyq::MarginValues supp_polygon_margins_;

  ::ros::Subscriber current_info_sub_;
  ::ros::Publisher opt_params_pub_;
  void CurrentInfoCallback(const ReqInfoMsg& msg);

  OptimizationVisualizer optimization_visualizer_;
};

} /* namespace ros */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ROS_OPTIMIZER_NODE_H_ */
