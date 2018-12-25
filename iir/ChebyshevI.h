/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco and adapted by Bernd Porr

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco
Copyright (c) 2011 by Bernd Porr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#ifndef DSPFILTERS_CHEBYSHEVI_H
#define DSPFILTERS_CHEBYSHEVI_H

#include "Common.h"
#include "Cascade.h"
#include "PoleFilter.h"
#include "State.h"

namespace Iir {

/**
 * Filters with Chebyshev response characteristics. The last parameter
 * defines the passband ripple in decibel.
 **/
namespace ChebyshevI {

// Half-band analog prototypes (s-plane)

class DllExport AnalogLowPass : public LayoutBase
{
public:
  AnalogLowPass ();

  void design (const int numPoles,
               double rippleDb);

private:
  int m_numPoles;
  double m_rippleDb;
};

//------------------------------------------------------------------------------

class DllExport AnalogLowShelf : public LayoutBase
{
public:
  AnalogLowShelf ();

  void design (int numPoles,
               double gainDb,
               double rippleDb);

private:
  int m_numPoles;
  double m_rippleDb;
  double m_gainDb;
};

//------------------------------------------------------------------------------

// Factored implementations to reduce template instantiations

struct DllExport LowPassBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double rippleDb);
};

struct DllExport HighPassBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double rippleDb);
};

struct DllExport BandPassBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency,
              double rippleDb);
};

struct DllExport BandStopBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency,
              double rippleDb);
};

struct DllExport LowShelfBase : PoleFilterBase <AnalogLowShelf>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double gainDb,
              double rippleDb);
};

struct DllExport HighShelfBase : PoleFilterBase <AnalogLowShelf>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double gainDb,
              double rippleDb);
};

struct DllExport BandShelfBase : PoleFilterBase <AnalogLowShelf>
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency,
              double gainDb,
              double rippleDb);
};

//------------------------------------------------------------------------------

//
// Userland filters
//

/**
 * ChebyshevI lowpass filter
 */
template <int MaxOrder, class StateType = DEFAULT_STATE>
	struct DllExport LowPass : PoleFilter <LowPassBase, StateType, MaxOrder>
	{
		/**
		 * Calculates the coefficients of the filter
                 * \param sampleRate Sampling rate
                 * \param cutoffFrequency Cutoff frequency.
                 * \param rippleDb Permitted ripples in dB in the passband
                 **/
		void setup (double sampleRate,
			    double cutoffFrequency,
			    double rippleDb) {
			LowPassBase::setup (MaxOrder,
					    sampleRate,
					    cutoffFrequency,
					    rippleDb);
		}
		
		void setup (int order,
			    double sampleRate,
			    double cutoffFrequency,
			    double rippleDb) {
			LowPassBase::setup (order,
					    sampleRate,
					    cutoffFrequency,
					    rippleDb);
		}
	};

/**
 * ChebyshevI highpass filter
 */
template <int MaxOrder, class StateType = DEFAULT_STATE>
	struct DllExport HighPass : PoleFilter <HighPassBase, StateType, MaxOrder>
	{
		/**
		 * Calculates the coefficients of the filter
                 * \param sampleRate Sampling rate
                 * \param cutoffFrequency Cutoff frequency.
                 * \param rippleDb Permitted ripples in dB in the passband
                 **/
		void setup (double sampleRate,
			    double cutoffFrequency,
			    double rippleDb) {
			HighPassBase::setup (MaxOrder,
					     sampleRate,
					     cutoffFrequency,
					     rippleDb);
		}

		void setup (int order,
			    double sampleRate,
			    double cutoffFrequency,
			    double rippleDb) {
			HighPassBase::setup (order,
					     sampleRate,
					     cutoffFrequency,
					     rippleDb);
		}
	};

/**
 * ChebyshevI bandpass filter
 */
template <int MaxOrder, class StateType = DEFAULT_STATE>
	struct DllExport BandPass : PoleFilter <BandPassBase, StateType, MaxOrder, MaxOrder*2>
	{
		/**
		 * Calculates the coefficients of the filter
                 * \param sampleRate Sampling rate
                 * \param centerFrequency Center frequency of the bandpass
                 * \param widthFrequency Frequency with of the passband
                 * \param rippleDb Permitted ripples in dB in the passband
                 **/
      		void setup (double sampleRate,
			    double centerFrequency,
			    double widthFrequency,
			    double rippleDb) {
			BandPassBase::setup (MaxOrder,
			       sampleRate,
			       centerFrequency,
			       widthFrequency,
			       rippleDb);
		}

		void setup (int order,
			    double sampleRate,
			    double centerFrequency,
			    double widthFrequency,
			    double rippleDb) {
			BandPassBase::setup (order,
			       sampleRate,
			       centerFrequency,
			       widthFrequency,
			       rippleDb);
		}
	};

/**
 * ChebyshevI bandstop filter
 */
template <int MaxOrder, class StateType = DEFAULT_STATE>
	struct DllExport BandStop : PoleFilter <BandStopBase, StateType, MaxOrder, MaxOrder*2>
	{
		/**
		 * Calculates the coefficients of the filter
                 * \param sampleRate Sampling rate
                 * \param centerFrequency Center frequency of the notch
                 * \param widthFrequency Frequency with of the notch
                 * \param rippleDb Permitted ripples in dB in the passband
                 **/
		void setup (double sampleRate,
			    double centerFrequency,
			    double widthFrequency,
			    double rippleDb) {
			BandStopBase::setup (MaxOrder,
					     sampleRate,
					     centerFrequency,
					     widthFrequency,
					     rippleDb);
		}

		void setup (int order,
			    double sampleRate,
			    double centerFrequency,
			    double widthFrequency,
			    double rippleDb) {
			BandStopBase::setup (order,
					     sampleRate,
					     centerFrequency,
					     widthFrequency,
					     rippleDb);
		}

	};

/**
 * ChebyshevI low shelf filter. Specified gain in the passband. Otherwise 0 dB.
 **/
template <int MaxOrder, class StateType = DEFAULT_STATE>
	struct DllExport LowShelf : PoleFilter <LowShelfBase, StateType, MaxOrder>
	{
		/**
		 * Calculates the coefficients of the filter
                 * \param sampleRate Sampling rate
                 * \param cutoffFrequency Cutoff frequency.
                 * \param gainDb Gain in the passband
                 * \param rippleDb Permitted ripples in dB in the passband
                 **/
		void setup (double sampleRate,
			    double cutoffFrequency,
			    double gainDb,
			    double rippleDb) {
			LowShelfBase::setup (MaxOrder,
					     sampleRate,
					     cutoffFrequency,
					     gainDb,
					     rippleDb);
		}
	
		void setup (int order,
			    double sampleRate,
			    double cutoffFrequency,
			    double gainDb,
			    double rippleDb) {
			LowShelfBase::setup (order,
					     sampleRate,
					     cutoffFrequency,
					     gainDb,
					     rippleDb);
		}
	};

/**
 * ChebyshevI high shelf filter. Specified gain in the passband. Otherwise 0 dB.
 **/
template <int MaxOrder, class StateType = DEFAULT_STATE>
	struct DllExport HighShelf : PoleFilter <HighShelfBase, StateType, MaxOrder>
	{
		/**
		 * Calculates the coefficients of the filter
                 * \param sampleRate Sampling rate
                 * \param cutoffFrequency Cutoff frequency.
                 * \param gainDb Gain in the passband
                 * \param rippleDb Permitted ripples in dB in the passband
                 **/
		void setup (double sampleRate,
			    double cutoffFrequency,
			    double gainDb,
			    double rippleDb) {
			HighShelfBase::setup (MaxOrder,
			       sampleRate,
			       cutoffFrequency,
			       gainDb,
			       rippleDb);
		}

		void setup (int order,
			    double sampleRate,
			    double cutoffFrequency,
			    double gainDb,
			    double rippleDb) {
			HighShelfBase::setup (order,
			       sampleRate,
			       cutoffFrequency,
			       gainDb,
			       rippleDb);
		}
		
	};

/**
 * ChebyshevI bandshelf filter. Specified gain in the passband. Otherwise 0 dB.
 **/
template <int MaxOrder, class StateType = DEFAULT_STATE>
	struct DllExport BandShelf : PoleFilter <BandShelfBase, StateType, MaxOrder, MaxOrder*2>
	{
		/**
		 * Calculates the coefficients of the filter
                 * \param sampleRate Sampling rate
                 * \param centerFrequency Center frequency of the passband
                 * \param widthFrequency Width of the passband.
                 * \param gainDb Gain in the passband. The stopband has 0 dB.
                 * \param rippleDb Permitted ripples in dB in the passband.
                 **/
		void setup (double sampleRate,
			    double centerFrequency,
			    double widthFrequency,
			    double gainDb,
			    double rippleDb) {
			BandShelfBase::setup (MaxOrder,
					      sampleRate,
					      centerFrequency,
					      widthFrequency,
					      gainDb,
					      rippleDb);
			
		}
		
		void setup (int order,
			    double sampleRate,
			    double centerFrequency,
			    double widthFrequency,
			    double gainDb,
			    double rippleDb) {
			BandShelfBase::setup (order,
					      sampleRate,
					      centerFrequency,
					      widthFrequency,
					      gainDb,
					      rippleDb);

		}

	};

}

}

#endif
