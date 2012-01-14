/*
 * Curve.h
 *
 *  Created on: Apr 2, 2011
 *      Author: buck <sebastian.buck@student.uni-tuebingen.de>
 */

#ifndef CURVE_H_
#define CURVE_H_

#include "CurveSegment.h"
#include "CircleSegment.h"
#include "LineSegment.h"
#include "../common/Point2d.h"

#include <vector>

class circle_pair {
public:
  Point2d center_left;
  Point2d center_right;
};

namespace ReedsShepp {

class Curve {
  friend class CurveGenerator;
  friend class CurveRenderer;

public:
  virtual ~Curve();

  /**
   * returns false, iff no combination  resulted in a feasible path
   */
  bool is_valid();

  /**
   * Get the weight of the curve
   */
  double weight();



  /**
   * Start iterating over the points on this curve
   */
  virtual void reset_iteration();

  /**
   * Check, if another point exists
   *
   * @return true, iff there exists another point
   */
  virtual bool has_next();

  /**
   * Get the next point in this iteration
   */
  virtual Pose2d next();

  Pose2d goal() {return m_goal;}
private:
  /**
   * Private constructor, only the Generator can instatiate this class
   */
  Curve();

  void test_sequence(std::vector< CurveSegment* > &sequence);

  double handle_sequence(CurveSegment *segment1,
                         CurveSegment *segment2,
                         CurveSegment *segment3);

  double handle_sequence(CurveSegment *segment1,
                         CurveSegment *segment2,
                         CurveSegment *segment3,
                         CurveSegment *segment4);

  double handle_sequence(CircleSegment *circle1,
                         LineSegment *line,
                         CircleSegment *circle2);

  double handle_sequence(CircleSegment *circle1,
                         CircleSegment *line,
                         CircleSegment *circle2);

  double handle_sequence(CircleSegment *circle1,
                         CircleSegment *circle2,
                         CircleSegment *circle3,
                         CircleSegment *circle4);

  void init_circle_pairs(Pose2d &next_to, circle_pair &target);

  bool m_init;

  float m_circle_radius;
  float m_max_waypoint_distance;

  float m_cost_forwards;
  float m_cost_backwards;
  float m_cost_curve;
  float m_cost_straight;

  std::vector<CurveSegment*> m_min_combo;
  float m_min_length;

  circle_pair m_circle_start;
  circle_pair m_circle_goal;

  Pose2d m_start;
  Pose2d m_goal;

  MapInfo *m_map;

  bool m_iterating;
  int m_output_number;
};

}

#endif /* CURVE_H_ */
