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

#ifndef BPVO_CHANNELS_H
#define BPVO_CHANNELS_H

#include <opencv2/core/core.hpp>
#include <vector>

namespace bpvo {

class RawIntensity
{
 public:
  static constexpr int NumChannels = 1;
  typedef std::vector<float> PixelVector;
  typedef float ChannelDataType;

 public:
  RawIntensity(float = 0.0f, float = 0.0f);
  explicit RawIntensity(const cv::Mat& I);

  inline int size() const { return NumChannels; }

  inline const cv::Mat_<ChannelDataType>& operator[](int) const {
    return _I;
  }

  inline const ChannelDataType* channelData(int) const {
    return _I.ptr<const ChannelDataType>();
  }

  void compute(const cv::Mat&);

  cv::Mat_<float> computeSaliencyMap() const;

 protected:
  cv::Mat_<ChannelDataType> _I;
}; // RawIntensity


class BitPlanes
{
 public:
  static constexpr int NumChannels = 8;
  typedef std::vector<float> PixelVector;
  typedef float ChannelDataType;

 public:
  /**
   */
  inline BitPlanes(float s1 = 0.5f, float s2 = 0.5f)
      : _sigma_ct(s1), _sigma_bp(s2) {}

  inline BitPlanes(const cv::Mat& I, float s1 = 0.5f, float s2 = 0.5f)
      : BitPlanes(s1, s2) { compute(I); }

  inline int size() const { return NumChannels; }

  inline const cv::Mat_<ChannelDataType>& operator[](int i) const {
    return _channels[i];
  }

  inline const ChannelDataType* channelData(int c) const {
    return _channels[c].ptr<const ChannelDataType>();
  }

  inline void setSigmaCensus(float s) { _sigma_ct = s; }
  inline void setSigmaBitPlanes(float s) { _sigma_bp = s; }

  inline const float& sigmaCensus() const { return _sigma_ct; }
  inline const float& sigmaBitPlanes() const {  return _sigma_bp; }

  cv::Mat_<float> computeSaliencyMap() const;

  void compute(const cv::Mat&);

 protected:
  float _sigma_ct = 0.0f;
  float _sigma_bp = 0.0f;
  std::array<cv::Mat_<ChannelDataType>,NumChannels> _channels;
}; // BitPlanes


}; // bpvo


#endif // BPVO_CHANNELS_H

