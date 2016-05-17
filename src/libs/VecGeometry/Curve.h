// Copyright (C) 2012-2016 The VPaint Developers.
// See the COPYRIGHT file at the top-level directory of this distribution
// and at https://github.com/dalboris/vpaint/blob/master/COPYRIGHT
//
// This file is part of VPaint, a vector graphics editor. It is subject to the
// license terms and conditions in the LICENSE.MIT file found in the top-level
// directory of this distribution and at http://opensource.org/licenses/MIT

#ifndef CURVE_H
#define CURVE_H

#include "CurveSample.h"

#include <vector>

/// \class Curve
/// \brief A class to represent a piecewise linear curve.
///
/// There are two ways to use this class:
///
///    1. You let it compute tangents, normals, arclengths, and angles for you.
///       In this case, only use the following methods to construct the curve:
///
///         - Curve()
///         - void clear()
///         - void addSample(const glm::vec2 & position, double width)
///
///       And the following methods to access the curve:
///
///         - int numSamples() const
///         - CurveSample sample(int i) const
///         - CurveSample sample(double s) const
///         - double length() const
///
///    2. You know what you are doing and want to modify the data directly,
///       in which case you can also use:
///
///         - size_t size() const
///         - void push_back(const CurveSample & sample)
///         - void push_back(CurveSample && sample)
///         - CurveSample & operator[](int i)
///         - std::vector<CurveSample> & samples()
///
class Curve
{
public:
    /// Constructs an empty curve.
    ///
    Curve();

    /// Clears the curve.
    ///
    void clear();

    /// Adds a sample to the curve, automatically computing tangents, normals,
    /// arclengths, and angles. This typically also modifies the previous
    /// sample, since its tangent is affected by the new sample.
    ///
    void addSample(const glm::vec2 & position, float width);

    /// Returns the number of samples in this curve.
    ///
    int numSamples() const;

    /// Returns the i-th sample.
    ///
    const CurveSample & sample(int i) const;

    /// Returns the sample at the given arclength \p s, interpolating
    /// neighbouring samples.
    ///
    CurveSample sample(double s) const;

    /// Returns the length of the curve.
    ///
    double length() const;

    /// Return the number of samples in this curve. This is the same as
    /// numSamples(), provided for convenience for familiarity with the STL.
    ///
    size_t size() const;

    /// Appends a sample to the vector of samples. Passed by const reference.
    ///
    void push_back(const CurveSample & sample);

    /// Appends a sample to the vector of samples. Passed by rvalue.
    ///
    void push_back(CurveSample && sample);

    /// Returns the i-th sample as a modifiable reference.
    ///
    CurveSample & operator[](int i);

    /// Returns the vector of samples as a modifiable reference.
    ///
    std::vector<CurveSample> & samples();

private:
    std::vector<CurveSample> samples_;
};

#endif // CURVE_H