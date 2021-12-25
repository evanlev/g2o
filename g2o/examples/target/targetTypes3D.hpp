#ifndef G2O_TARGET_TYPES_3D_HPP_
#define G2O_TARGET_TYPES_3D_HPP_

#include <g2o/core/base_unary_edge.h>
#include <g2o/core/base_vertex.h>

#include <Eigen/Core>

// This header file specifies a set of types for the different
// tracking examples; note that

class VertexPosition3D : public g2o::BaseVertex<3, Eigen::Vector3d> {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  VertexPosition3D() {}

  virtual void setToOriginImpl() { estimate_.setZero(); }

  virtual void oplusImpl(const double* update) {
    estimate_[0] += update[0];
    estimate_[1] += update[1];
    estimate_[2] += update[2];
  }

  virtual bool read(std::istream& /*is*/) { return false; }

  virtual bool write(std::ostream& /*os*/) const { return false; }
};

// Store velocity separately from position?
class VertexVelocity3D : public g2o::BaseVertex<3, Eigen::Vector3d> {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  VertexVelocity3D() {}

  virtual void setToOriginImpl() { estimate_.setZero(); }

  virtual void oplusImpl(const double* update) {
    estimate_[0] += update[0];
    estimate_[1] += update[1];
    estimate_[2] += update[2];
  }

  virtual bool read(std::istream& /*is*/) { return false; }

  virtual bool write(std::ostream& /*os*/) const { return false; }
};

// The idealised GPS measurement; this is 3D and linear
class GPSObservationPosition3DEdge
    : public g2o::BaseUnaryEdge<3, Eigen::Vector3d, VertexPosition3D> {
 public:
  GPSObservationPosition3DEdge() {}

  void computeError() {
    const VertexPosition3D* v = vertexXnRaw<0>();
    error_ = v->estimate() - measurement_;
  }

  virtual bool read(std::istream& /*is*/) { return false; }

  virtual bool write(std::ostream& /*os*/) const { return false; }
};

#endif  //  __TARGET_TYPES_3D_HPP__
