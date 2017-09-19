#include <iostream>
#include <cmath>
#include <cassert>
#include <locale>

double seconds_difference(double time_1, double time_2)
{
	// your implementation goes here...

	/*
	Return the number of seconds later that a time in seconds
	time_2 is than a time in seconds time_1.

	>>> seconds_difference(1800.0, 3600.0)
	1800.0

	>>> seconds_difference(3600.0, 1800.0)
	-1800.0

	>>> seconds_difference(1800.0, 2160.0)
	360.0

	>>> seconds_difference(1800.0, 1800.0)
	0.0
	*/
	return time_2 - time_1;
}

double hours_difference(double time_1, double time_2)
{
	/*
	Return the number of hours later that a time in seconds
	time_2 is than a time in seconds time_1.

	>>> hours_difference(1800.0, 3600.0)
	0.5

	>>> hours_difference(3600.0, 1800.0)
	-0.5

	>>> hours_difference(1800.0, 2160.0)
	0.1

	>>> hours_difference(1800.0, 1800.0)
	0.0
	*/
	return (time_2 - time_1) / 3600.0;
}

double to_float_hours(int hours, int minutes, int seconds)
{
	/*
	Return the total number of hours in the specified number
	of hours, minutes, and seconds.

	Precondition: 0 <= minutes < 60  and  0 <= seconds < 60

	>>> to_float_hours(0, 15, 0)
	0.25

	>>> to_float_hours(2, 45, 9)
	2.7525

	>>> to_float_hours(1, 0, 36)
	1.01
	*/
	assert(minutes >= 0 && minutes < 60 && "Minutes mistake in to_float_hours");
	assert(seconds >= 0 && seconds < 60 && "Seconds mistake in to_float_hours");
	return hours + minutes / 60.0 + seconds / 3600.0;
}

double to_24_hour_clock(double hours)
{
	/*
	hours is a number of hours since midnight. Return the
	hour as seen on a 24-hour clock.

	Precondition: hours >= 0

	>>> to_24_hour_clock(24)
	0

	>>> to_24_hour_clock(48)
	0

	>>> to_24_hour_clock(25)
	1

	>>> to_24_hour_clock(4)
	4

	>>> to_24_hour_clock(28.5)
	4.5

	You may wish to inspect various function in <cmath> to work
	with integer and fractional part of a hours separately.

	*/
	assert(hours >= 0 && "Hours mistake in to_24_hour_clock");
	while (hours >= 24)
		hours -= 24;
	return hours;
}

/*
Implement three functions
* get_hours
* get_minutes
* get_seconds
They are used to determine the hours part, minutes part and seconds part
of a time in seconds. E.g.:

>>> get_hours(3800)
1

>>> get_minutes(3800)
3

>>> get_seconds(3800)
20

In other words, if 3800 seconds have elapsed since midnight,
it is currently 01:03:20 (hh:mm:ss).
*/
double get_hours(int seconds)
{
	return seconds / 3600;
}
double get_minutes(int seconds)
{
	return seconds % 3600 / 60;
}
double get_seconds(int seconds)
{
	return seconds % 60;
}

double time_to_utc(int utc_offset, double time)
{
	/*
	Return time at UTC+0, where utc_offset is the number of hours away from
	UTC+0.
	You may be interested in:
	https://en.wikipedia.org/wiki/Coordinated_Universal_Time

	>>> time_to_utc(+0, 12.0)
	12.0

	>>> time_to_utc(+1, 12.0)
	11.0

	>>> time_to_utc(-1, 12.0)
	13.0

	>>> time_to_utc(-11, 18.0)
	5.0

	>>> time_to_utc(-1, 0.0)
	1.0

	>>> time_to_utc(-1, 23.0)
	0.0
	*/
	double d = time - utc_offset;
	if (d >= 24) //Т.к utc_offset находится в диапозоне от -12 до +12, то мы никак не можем получить 48 часов и более 
		d -= 24;
	if (d < 0)
		d = 24.0 + d;
	return d;
}

double time_from_utc(int utc_offset, double time)
{
	/*
	Return UTC time in time zone utc_offset.

	>>> time_from_utc(+0, 12.0)
	12.0

	>>> time_from_utc(+1, 12.0)
	13.0

	>>> time_from_utc(-1, 12.0)
	11.0

	>>> time_from_utc(+6, 6.0)
	12.0

	>>> time_from_utc(-7, 6.0)
	23.0

	>>> time_from_utc(-1, 0.0)
	23.0

	>>> time_from_utc(-1, 23.0)
	22.0

	>>> time_from_utc(+1, 23.0)
	0.0
	*/
	double d = time + utc_offset;
	if (d >= 24) //Т.к utc_offset находится в диапозоне от -12 до +12, то мы никак не можем получить 48 часов и более 
		d -= 24;
	if (d < 0)
		d = 24.0 + d;
	return d;
}
int main()
{
	assert(abs(seconds_difference(1800.0, 3600.0) - 1800.0) < DBL_EPSILON  && "test 1");
	assert(abs(seconds_difference(3600.0, 1800.0) - -1800.0) < DBL_EPSILON  && "test 2");
	assert(abs(seconds_difference(1800.0, 2160.0) - 360.0) < DBL_EPSILON  && "test3");
	assert(abs(seconds_difference(1800.0, 1800.0) - 0.0) < DBL_EPSILON  && "test4");
	assert(abs(hours_difference(1800.0, 3600.0) - 0.5) < DBL_EPSILON  && "test5");
	assert(abs(hours_difference(3600.0, 1800.0) - - 0.5) < DBL_EPSILON  && "test6");
	assert(abs(hours_difference(1800.0, 2160.0) - 0.1) < DBL_EPSILON  && "test7");
	assert(abs(hours_difference(1800.0, 1800.0) - 0.0) < DBL_EPSILON  && "test8");
	assert(abs(to_float_hours(0, 15, 0) - 0.25) < DBL_EPSILON  && "test9");
	assert(abs(to_float_hours(2, 45, 9) - 2.7525) < DBL_EPSILON  && "test10");
	assert(abs(to_float_hours(1, 0, 36) - 1.01) < DBL_EPSILON  && "test11");
	assert(to_24_hour_clock(24) == 0 && "test12");
	assert(to_24_hour_clock(48) == 0 && "test13");
	assert(to_24_hour_clock(25) == 1 && "test14");
	assert(to_24_hour_clock(4) == 4 && "test15");
	assert(to_24_hour_clock(28.5) == 4.5 && "test16");
	assert(abs(time_to_utc(+0, 12.0) - 12.0) < DBL_EPSILON  && "test17");
	assert(abs(time_to_utc(+1, 12.0) - 11.0) < DBL_EPSILON  && "test18");
	assert(abs(time_to_utc(-1, 12.0) - 13.0) < DBL_EPSILON  && "test19");
	assert(abs(time_to_utc(-11, 18.0) - 5.0) < DBL_EPSILON  && "test20");
	assert(abs(time_to_utc(-1, 0.0) - 1.0) < DBL_EPSILON  && "test21");
	assert(abs(time_to_utc(-1, 23.0) - 0.0) < DBL_EPSILON  && "test22");
	assert(abs(time_from_utc(+0, 12.0) - 12.0) < DBL_EPSILON  && "test23");
	assert(abs(time_from_utc(+1, 12.0) - 13.0) < DBL_EPSILON  && "test24");
	assert(abs(time_from_utc(-1, 12.0) - 11.0) < DBL_EPSILON  && "test25");
	assert(abs(time_from_utc(+6, 6.0) - 12.0) < DBL_EPSILON  && "test26");
	assert(abs(time_from_utc(-7, 6.0) - 23.0) < DBL_EPSILON  && "test27");
	assert(abs(time_from_utc(-1, 0.0) - 23.0) < DBL_EPSILON  && "test28");
	assert(abs(time_from_utc(-1, 23.0) - 22.0) < DBL_EPSILON  && "test29");
	assert(abs(time_from_utc(+1, 23.0) - 0.0) < DBL_EPSILON  && "test30");
	assert(get_hours(3800) == 1 &&  "test31");
	assert(get_minutes(3800) ==3 &&  "test32");
	assert(get_seconds(3800) ==20 &&  "test33");
}

