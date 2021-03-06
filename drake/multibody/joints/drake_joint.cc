#include "drake/multibody/joints/drake_joint.h"

#include <limits>

#include "drake/common/drake_assert.h"
#include "drake/common/text_logging.h"

using Eigen::Isometry3d;
using Eigen::VectorXd;

DrakeJoint::DrakeJoint(const std::string& _name,
                       const Isometry3d& _transform_to_parent_body,
                       int _num_positions, int _num_velocities)
    : name(_name),
      joint_limit_min(VectorXd::Constant(
          _num_positions, -std::numeric_limits<double>::infinity())),
      joint_limit_max(VectorXd::Constant(
          _num_positions, std::numeric_limits<double>::infinity())),
      joint_limit_stiffness_(VectorXd::Constant(
          _num_positions, 150. /* Historic default from RigidBodyPlant. */)),
      joint_limit_dissipation_(VectorXd::Constant(
          _num_positions, 1. /* Arbitrary, reasonable default. */)),
      transform_to_parent_body(_transform_to_parent_body),
      num_positions(_num_positions),
      num_velocities(_num_velocities) {
  DRAKE_ASSERT(num_positions <= MAX_NUM_POSITIONS);
  DRAKE_ASSERT(num_velocities <= MAX_NUM_VELOCITIES);
}

DrakeJoint::~DrakeJoint() {
  // empty
}

const Isometry3d& DrakeJoint::get_transform_to_parent_body() const {
  return transform_to_parent_body;
}

int DrakeJoint::get_num_positions() const { return num_positions; }

int DrakeJoint::get_num_velocities() const { return num_velocities; }

const std::string& DrakeJoint::get_name() const { return name; }

std::string DrakeJoint::get_velocity_name(int index) const {
  return get_position_name(index) + "dot";
}

// TODO(liang.fok) Remove this deprecated method prior to release 1.0.
int DrakeJoint::getNumPositions() const {
  return get_num_positions();
}

// TODO(liang.fok) Remove this deprecated method prior to release 1.0.
int DrakeJoint::getNumVelocities() const {
  return get_num_velocities();
}

// TODO(liang.fok) Remove this deprecated method prior to release 1.0.
const Eigen::Isometry3d& DrakeJoint::getTransformToParentBody() const {
  return get_transform_to_parent_body();
}

// TODO(liang.fok) Remove this deprecated method prior to release 1.0.
const std::string& DrakeJoint::getName() const {
  return get_name();
}

// TODO(liang.fok) Remove this deprecated method prior to release 1.0.
std::string DrakeJoint::getVelocityName(int index) const {
  return get_velocity_name(index);
}

const Eigen::VectorXd& DrakeJoint::getJointLimitMin() const {
  return joint_limit_min;
}

const Eigen::VectorXd& DrakeJoint::getJointLimitMax() const {
  return joint_limit_max;
}

const Eigen::VectorXd& DrakeJoint::get_joint_limit_stiffness() const {
  return joint_limit_stiffness_;
}

const Eigen::VectorXd& DrakeJoint::get_joint_limit_dissipation() const {
  return joint_limit_dissipation_;
}

bool DrakeJoint::CompareToClone(const DrakeJoint &other) const {
  if (get_transform_to_parent_body().matrix() !=
      other.get_transform_to_parent_body().matrix()) {
    drake::log()->debug(
        "DrakeJoint::CompareToClone(): "
        "transform_to_parent_body mismatch:\n"
        "  - this: {}\n"
        "  - other: {}",
        get_transform_to_parent_body().matrix(),
        other.get_transform_to_parent_body().matrix());
    return false;
  }
  if (get_num_positions() != other.get_num_positions()) {
    drake::log()->debug(
        "DrakeJoint::CompareToClone(): get_num_positions mismatch:\n"
        "  - this: {}\n"
        "  - other: {}",
        get_num_positions(),
        other.get_num_positions());
    return false;
  }
  if (get_num_velocities() != other.get_num_velocities()) {
    drake::log()->debug(
        "DrakeJoint::CompareToClone(): get_num_velocities mismatch:\n"
        "  - this: {}\n"
        "  - other: {}",
        get_num_velocities(),
        other.get_num_velocities());
    return false;
  }
  if (get_name() != other.get_name()) {
    drake::log()->debug(
        "DrakeJoint::CompareToClone(): get_name mismatch:\n"
        "  - this: {}\n"
        "  - other: {}",
        get_name(),
        other.get_name());
    return false;
  }
  if (getJointLimitMin() != other.getJointLimitMin()) {
    drake::log()->debug(
        "DrakeJoint::CompareToClone(): getJointLimitMin mismatch:\n"
        "  - this: {}\n"
        "  - other: {}",
        getJointLimitMin(),
        other.getJointLimitMin());
    return false;
  }
  if (getJointLimitMax() != other.getJointLimitMax()) {
    drake::log()->debug(
        "DrakeJoint::CompareToClone(): getJointLimitMax mismatch:\n"
        "  - this: {}\n"
        "  - other: {}",
        getJointLimitMax(),
        other.getJointLimitMax());
    return false;
  }
  if (get_joint_limit_stiffness() != other.get_joint_limit_stiffness()) {
    drake::log()->debug(
        "DrakeJoint::CompareToClone(): "
        "get_joint_limit_stiffness mismatch:\n"
        "  - this: {}\n"
        "  - other: {}",
        get_joint_limit_stiffness(),
        other.get_joint_limit_stiffness());
    return false;
  }
  if (get_joint_limit_dissipation() != other.get_joint_limit_dissipation()) {
    drake::log()->debug(
        "DrakeJoint::CompareToClone(): "
        "get_joint_limit_dissipation mismatch:\n"
        "  - this: {}\n"
        "  - other: {}",
        get_joint_limit_dissipation(),
        other.get_joint_limit_dissipation());
    return false;
  }
  return true;
}
