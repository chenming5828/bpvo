/*
   This file is part of bpvo.

   bpvo is free software: you can redistribute it and/or modify
   it under the terms of the Lesser GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   bpvo is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   Lesser GNU General Public License for more details.

   You should have received a copy of the Lesser GNU General Public License
   along with bpvo.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * Contributor: halismai@cs.cmu.edu
 */

#ifndef BPVO_VO_H
#define BPVO_VO_H

#include <bpvo/types.h>

namespace bpvo {

class VisualOdometry
{
  typedef typename EigenAlignedContainer<Point>::type PointVector;

 public:
  /**
   * \param ImageSize
   * \param AlgorithmParameters
   */
  VisualOdometry(const Matrix33& K, float baseline, ImageSize,
                 AlgorithmParameters = AlgorithmParameters());

  /**
   */
  ~VisualOdometry();

  /**
   * Estimate the motion of the image wrt. to the previously added frame
   *
   * \param image pointer to the image data
   * \param disparity pionter to disparity map
   *
   * Both the image & disparity must have the same size
   *
   * \retun Result
   */
  Result addFrame(const uint8_t* image, const float* disparity);


  /**
   * \return the number of points at the specified pyramid level
   */
  int numPointsAtLevel(int level = 0) const;

  /**
   * \return the points at the specified level
   */
  const PointVector& pointsAtLevel(int level = 0) const;

 private:
  class Impl;
  Impl* _impl;
}; // VisualOdometry

}; // bpvo

#endif
