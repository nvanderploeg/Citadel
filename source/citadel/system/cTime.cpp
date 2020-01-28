
#include "citadelSystem.h"

namespace citadel {

	// CONSTRUCTORS

	Time::Time()
		: m_microseconds(0)
	{

	}

	Time::Time(s64 microseconds)
		: m_microseconds(microseconds)
	{

	}

	Time::Time(f32 seconds)
		: m_microseconds(static_cast<s64>(seconds * 1000000))
	{

	}

	// CONVERSION METHODS

	f32 Time::asSeconds() const
	{
		return m_microseconds / 1000000.0f;
	}

	s32 Time::asMilliseconds() const
	{
		return static_cast<s32>(m_microseconds / 1000);
	}

	s64 Time::asMicroseconds() const
	{
		return m_microseconds;
	}

	Time Time::getCurrentTime()
	{
		return Time(static_cast<s64>(std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000));
	}

	// STATIC METHODS

	Time Time::seconds(f32 seconds)
	{
		return Time(seconds);
	}

	Time Time::milliseconds(s32 milliseconds)
	{
		return Time(static_cast<s64>(milliseconds));
	}

	Time Time::microseconds(s64 microseconds)
	{
		return Time(microseconds);
	}

	// SERIALIZATION

	void Time::serialize(Json::Value& jValue)
	{
		jValue["microseconds"] = (Json::UInt64) m_microseconds;
	}

	void Time::deserialize(const Json::Value& jValue)
	{
		m_microseconds = jValue.get("microseconds", 0).asInt64();
	}

	// OPERATORS

	bool operator == (Time left, Time right)
	{
		return left.asMicroseconds() == right.asMicroseconds();
	}
	bool operator != (Time left, Time right)
	{
		return left.asMicroseconds() != right.asMicroseconds();
	}

	bool operator <  (Time left, Time right)
	{
		return left.asMicroseconds() < right.asMicroseconds();
	}

	bool operator <= (Time left, Time right)
	{
		return left.asMicroseconds() <= right.asMicroseconds();
	}

	bool operator >  (Time left, Time right)
	{
		return left.asMicroseconds() > right.asMicroseconds();
	}

	bool operator >= (Time left, Time right)
	{
		return left.asMicroseconds() >= right.asMicroseconds();
	}

	Time operator -  (Time right)
	{
		return Time::microseconds(-right.asMicroseconds());
	}

	Time operator -  (Time left, Time right)
	{
		return Time::microseconds(left.asMicroseconds() - right.asMicroseconds());
	}

	Time& operator-= (Time &left, Time right)
	{
		return left = left - right;
	}

	Time operator +  (Time left, Time right)
	{
		return Time::microseconds(left.asMicroseconds() + right.asMicroseconds());
	}

	Time& operator+= (Time &left, Time right)
	{
		return left = left + right;
	}

	Time operator *  (Time left, f32 right)
	{
		return Time::seconds(left.asSeconds() * right);
	}

	Time operator *  (Time left, s64 right)
	{
		return Time::microseconds(left.asMicroseconds() * right);
	}

	Time operator *  (f32 left, Time right)
	{
		return right * left;
	}

	Time operator *  (s64 left, Time right)
	{
		return right * left;
	}

	Time& operator*= (Time &left, f32 right)
	{
		return left = left * right;
	}

	Time& operator*= (Time &left, s64 right)
	{
		return left = left * right;
	}

	Time operator /  (Time left, f32 right)
	{
		return Time::seconds(left.asSeconds() / right);
	}

	Time operator /  (Time left, s64 right)
	{
		return Time::microseconds(left.asMicroseconds() / right);
	}

	Time& operator/= (Time &left, f32 right)
	{
		return left = left / right;
	}

	Time& operator/= (Time &left, s64 right)
	{
		return left = left / right;
	}

	f32 operator  /  (Time left, Time right)
	{
		return left.asSeconds() / right.asSeconds();
	}

	Time operator %  (Time left, Time right)
	{
		return Time::microseconds(left.asMicroseconds() % right.asMicroseconds());
	}

	Time& operator%= (Time &left, Time right)
	{
		return left = left % right;
	}

} // namespace citadel
