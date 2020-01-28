
#ifndef __CLOCK_H__
#define __CLOCK_H__

namespace citadel {

	/// \class citadel::Clock
	/// \ingroup system
	/// \brief Utility class that measures the elapsed time.
	/// \note citadel::Time borrows heavily from sf::Clock.
	///
	/// citadel::Clock is a lightweight class for measuring time.
	///
	/// Usage example:
	/// \code
	/// using namespace citadel;
	/// Clock clock;
	/// ...
	/// Time time1 = clock.getElapsedTime();
	/// ...
	/// Time time2 = clock.restart();
	/// \endcode
	///
	/// The citadel::Time value returned by the clock can then be
	/// converted to a number of seconds, milliseconds or even
	/// microseconds.
	///
	/// \see citadel::Time
	class Clock
	{
	protected:
		Time m_startTime; ///< Time of last restart, in microseconds

	public:
		/// \brief Default constructor.
		/// The clock starts automatically after being constructed.
		Clock();

		/// \brief Get the elapsed time.
		/// This function returns the time elapsed since the last call
		/// to restart() (or the construction of the instance if restart()
		/// has not been called).
		/// \return Time elapsed
		Time getElapsedTime() const;

		/// \brief Restart the clock.
		/// This function puts the time counter back to zero.
		/// It also returns the time elapsed since the clock was started.
		/// \return Time elapsed
		Time restart();

	}; // Clock

} // namespace citadel

#endif // __CLOCK_H__
