
#ifndef __TIME_H__
#define __TIME_H__

#include "JSONSerializable.h"

namespace citadel
{

	/// \class citadel::Time
	/// \ingroup system
	/// \brief Represents a time value.
	/// \note citadel::Time borrows heavily from sf::Time.
	///
	/// citadel::Time encapsulates a time value in a flexible way.
	/// It allows you to define a time value either as a number of
	/// seconds, milliseconds or microseconds. It also works the
	/// other way round: you can read a time value as either
	/// a number of seconds, milliseconds or microseconds.
	///
	/// Time values support the usual mathematical operations:
	/// you can add or subtract two times, multiply or divide
	/// a time by a number, compare two times, etc.
	///
	/// Since they represent a time span and not an absolute time
	/// value, times can also be negative.
	///
	/// Usage example:
	/// \code
	/// using namespace citadel;
	/// Time t1 = Time::seconds(0.1f);
	/// i32 milli = t1.asMilliseconds(); // 100
	///
	/// Time t2 = Time::milliseconds(30);
	/// i64 micro = t2.asMicroseconds(); // 30000
	///
	/// Time t3 = Time::microseconds(-800000);
	/// f32 sec = t3.asSeconds(); // -0.8
	/// \endcode
	///
	/// \code
	/// void update(citadel::Time elapsed)
	/// {
	///    position += speed * elapsed.asSeconds();
	/// }
	///
	/// update(citadel::milliseconds(100));
	/// \endcode
	///
	/// \see citadel::Clock
    class Time : public IJSONSerializable
	{
	private:
		int64_t m_microseconds; ///< Time value stored as microseconds.

	public:
		/// \brief Default constructor.
		/// Sets the time value to zero.
		Time();
		
		/// \brief Construct the time from a seconds value.
		explicit Time(float seconds);

		/// \brief Construct from a number of microseconds.
		/// \param microseconds Number of microseconds
		explicit Time(int64_t microseconds);

		virtual void serialize(Json::Value& jValue) const override;

		virtual void deserialize(const Json::Value& jValue) override;

		/// \brief Return the time value as a number of seconds.
		/// \return Time in seconds.
		/// \see asMilliseconds, asMicroseconds
		float asSeconds() const;

		/// \brief Return the time value as a number of milliseconds.
		/// \return Time in milliseconds.
		/// \see asSeconds, asMicroseconds
        int32_t asMilliseconds() const;

		/// \brief Return the time value as a number of microseconds.
		/// \return Time in microseconds.
		/// \see asSeconds, asMilliseconds
        int64_t asMicroseconds() const;

		/// \brief Get the current system time.
		/// \note This function uses std::chrono and the std::chrono::high_resolution_clock.
		/// \return A time value represting the system time at which the function was called.
		static Time getCurrentTime();

		/// \brief Construct a time value from a number of seconds.
		/// \param seconds Number of seconds.
		/// \return Time value constructed from the amount of seconds.
		/// \see milliseconds, microseconds
		static Time seconds(float seconds);

		/// \brief Construct a time value from a number of milliseconds.
		/// \param milliseconds Number of milliseconds.
		/// \return Time value constructed from the amount of milliseconds.
		/// \see seconds, microseconds
		static Time milliseconds(int32_t milliseconds);

		/// \brief Construct a time value from a number of microseconds.
		/// \param microseconds Number of microseconds.
		/// \return Time value constructed from the amount of microseconds.
		/// \see seconds, milliseconds
		static Time microseconds(int64_t microseconds);

	}; // class Time

	/// \relates Time
	/// \brief Overload of == operator to compare two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return True if both time values are equal.
	bool operator == (Time left, Time right);

	/// \relates Time
	/// \brief Overload of != operator to compare two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return True if both time values are different.
	bool operator != (Time left, Time right);

	/// \relates Time
	/// \brief Overload of < operator to compare two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return True if \a left is lesser than \a right.
	bool operator <  (Time left, Time right);

	/// \relates Time
	/// \brief Overload of <= operator to compare two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return True if \a left is lesser or equal than \a right.
	bool operator <= (Time left, Time right);

	/// \relates Time
	/// \brief Overload of > operator to compare two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return True if \a left is greater than \a right.
	bool operator >  (Time left, Time right);

	/// \relates Time
	/// \brief Overload of >= operator to compare two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return True if \a left is greater or equal than \a right.
	bool operator >= (Time left, Time right);

	/// \relates Time
	/// \brief Overload of unary - operator to negate a time value.
	/// \param right Right operand (a time).
	/// \return Opposite of the time value.
	Time operator -  (Time right);

	/// \relates Time
	/// \brief Overload of binary - operator to subtract two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return Difference of the two times values.
	Time operator -  (Time left, Time right);

	/// \relates Time
	/// \brief Overload of binary -= operator to subtract/assign two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return Difference of the two times values.
	Time& operator-= (Time &left, Time right);

	/// \relates Time
	/// \brief Overload of binary + operator to add two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return Sum of the two times values.
	Time operator +  (Time left, Time right);

	/// \relates Time
	/// \brief Overload of binary += operator to add/assign two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return Sum of the two times values.
	Time& operator+= (Time &left, Time right);

	/// \relates Time
	/// \brief Overload of binary * operator to scale a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a number).
	/// \return \a left multiplied by \a right.
	Time operator *  (Time left, float right);

	/// \relates Time
	/// \brief Overload of binary * operator to scale a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a number).
	/// \return \a left multiplied by \a right.
	Time operator *  (Time left, int64_t right);

	/// \relates Time
	/// \brief Overload of binary * operator to scale a time value.
	/// \param left  Left operand (a number).
	/// \param right Right operand (a time).
	/// \return \a left multiplied by \a right.
	Time operator *  (float left, Time right);

	/// \relates Time
	/// \brief Overload of binary * operator to scale a time value.
	/// \param left  Left operand (a number).
	/// \param right Right operand (a time).
	/// \return \a left multiplied by \a right.
	Time operator *  (int64_t left, Time right);

	/// \relates Time
	/// \brief Overload of binary *= operator to scale/assign a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a number).
	/// \return \a left multiplied by \a right.
	Time& operator*= (Time &left, float right);

	/// \relates Time
	/// \brief Overload of binary *= operator to scale/assign a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a number).
	/// \return \a left multiplied by \a right.
	Time& operator*= (Time &left, int64_t right);

	/// \relates Time
	/// \brief Overload of binary *= operator to scale/assign a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a number).
	/// \return \a left multiplied by \a right.
	Time operator /  (Time left, float right);

	/// \relates Time
	/// \brief Overload of binary / operator to scale a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a number).
	/// \return \a left divided by \a right.
	Time operator /  (Time left, int64_t right);

	/// \relates Time
	/// \brief Overload of binary /= operator to scale/assign a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a number).
	/// \return \a left divided by \a right.
	Time& operator/= (Time &left, float right);

	/// \relates Time
	/// \brief Overload of binary /= operator to scale/assign a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a number).
	/// \return \a left divided by \a right.
	Time& operator/= (Time &left, int64_t right);

	/// \relates Time
	/// \brief Overload of binary / operator to compute the ratio of two time values.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return \a left divided by \a right.
	float operator  /  (Time left, Time right);

	/// \relates Time
	/// \brief Overload of binary % operator to compute remainder of a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return \a left modulo \a right.
	Time operator %  (Time left, Time right);

	/// \relates Time
	/// \brief Overload of binary %= operator to compute/assign remainder of a time value.
	/// \param left  Left operand (a time).
	/// \param right Right operand (a time).
	/// \return \a left modulo \a right.
	Time& operator%= (Time &left, Time right);

} // namespace citadel

#endif // __TIME_H__
