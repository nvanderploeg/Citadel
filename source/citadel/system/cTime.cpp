
#include "citadelSystem.h"

namespace citadel {

	// CONSTRUCTORS

	Time::Time()
		: m_microseconds(0)
	{

	}

	Time::Time(int64_t microseconds)
		: m_microseconds(microseconds)
	{

	}

	Time::Time(float seconds)
		: m_microseconds(static_cast<int64_t>(seconds * 1000000))
	{

	}

	// CONVERSION METHODS

	float Time::asSeconds() const
	{
		return m_microseconds / 1000000.0f;
	}

	int32_t Time::asMilliseconds() const
	{
		return static_cast<int32_t>(m_microseconds / 1000);
	}

    int64_t Time::asMicroseconds() const
	{
		return m_microseconds;
	}

	Time Time::getCurrentTime()
	{
		return Time(static_cast<int64_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000));
	}

	// STATIC METHODS

	Time Time::seconds(float seconds)
	{
		return Time(seconds);
	}

	Time Time::milliseconds(int32_t milliseconds)
	{
		return Time(static_cast<int64_t>(milliseconds));
	}

	Time Time::microseconds(int64_t microseconds)
	{
		return Time(microseconds);
	}

	// SERIALIZATION

	void Time::serialize(Json::Value& jValue) const
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

	Time operator *  (Time left, float right)
	{
		return Time::seconds(left.asSeconds() * right);
	}

	Time operator *  (Time left, int64_t right)
	{
		return Time::microseconds(left.asMicroseconds() * right);
	}

	Time operator *  (float left, Time right)
	{
		return right * left;
	}

	Time operator *  (int64_t left, Time right)
	{
		return right * left;
	}

	Time& operator*= (Time &left, float right)
	{
		return left = left * right;
	}

	Time& operator*= (Time &left, int64_t right)
	{
		return left = left * right;
	}

	Time operator /  (Time left, float right)
	{
		return Time::seconds(left.asSeconds() / right);
	}

	Time operator /  (Time left, int64_t right)
	{
		return Time::microseconds(left.asMicroseconds() / right);
	}

	Time& operator/= (Time &left, float right)
	{
		return left = left / right;
	}

	Time& operator/= (Time &left, int64_t right)
	{
		return left = left / right;
	}

	float operator  /  (Time left, Time right)
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
