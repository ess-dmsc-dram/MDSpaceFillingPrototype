#include <cstring>

#include "BitInterleaving.h"
#include "CoordinateConversion.h"
#include "Types.h"

#pragma once

template <size_t ND> class MDEvent {
public:
  MDEvent(uint64_t spaceFillingCurveOrder = 0, float signal = 1.0f)
      : m_spaceFillingCurveOrder(spaceFillingCurveOrder), m_signal(signal) {}

  MDEvent(const MDCoordinate<ND> &coord, const MDSpaceBounds<ND> &space,
          float signal = 1.0f)
      : m_signal(signal) {
    const auto intCoord =
        ConvertCoordinatesToIntegerRange<ND, uint16_t>(space, coord);
    m_spaceFillingCurveOrder =
        Interleave_4_16_64(intCoord[0], intCoord[1], intCoord[2], intCoord[3]);
  }

  uint64_t spaceFillingCurveOrder() const { return m_spaceFillingCurveOrder; }
  float signal() const { return m_signal; }

  bool operator<(const MDEvent<ND> &other) const {
    return m_spaceFillingCurveOrder < other.m_spaceFillingCurveOrder;
  }

private:
  float m_signal;
  uint64_t m_spaceFillingCurveOrder;
};
