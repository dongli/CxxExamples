/**
 *  This example uses Boost.DateTime library to handle date and time.
 *
 *  History:
 *
 *      2015-06-22
 *
 *          Li Dong     First creation.
 */

#include <boost/date_time.hpp>
#include <iostream>

using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace std;

int main(void) {
    // Construct ptime object from date object.
    ptime t1(date(2000, 1, 1));
    cout << "[Notice]: Construct a boost::ptime object \"";
    cout << t1 << "\"." << endl;
    // Set HMS parts of ptime.
    t1 += hours(5);
    cout << "[Notice]: Add 5 hours \"" << t1 << "\"." << endl;
    t1 += minutes(10);
    cout << "[Notice]: Add 10 minutes \"" << t1 << "\"." << endl;
    t1 += seconds(3);
    cout << "[Notice]: Add 3 seconds \"" << t1 << "\"." << endl;
    t1 += time_duration(0, 0, 0, time_duration::ticks_per_second()*0.5);
    cout << "[Notice]: Add 0.5 seconds \"" << t1 << "\"." << endl;
    t1 += time_duration(0, 0, 0, time_duration::ticks_per_second()*0.5*86400);
    cout << "[Notice]: Add 0.5 days \"" << t1 << "\"." << endl;
    t1 += date_duration(1);
    cout << "[Notice]: Add 1 day \"" << t1 << "\"." << endl;
    t1 += months(2);
    cout << "[Notice]: Add 1 month \"" << t1 << "\"." << endl;
    t1 = ptime(date(2004, 2, 29));
    cout << "[Notice]: Set to \"" << t1 << "\"";
    t1 += months(1);
    cout << ", and add 1 month \"" << t1 << "\"." << endl;
    // Read ptime from string.
    cout << "[Notice]: Read boost::ptime from \"2015-06-22 14:13:32.4\" string \"";
    cout << time_from_string("2015-06-22 14:13:32.4") << endl;
    // Read time_duration from string.
    cout << "[Notice]: Read boost::time_duration from \"0.5\" string \"";
    cout << duration_from_string("0.5") << "\"." << endl;
    cout << "[Notice]: Read boost::time_duration from \"01:20:30.5\" string \"";
    cout << duration_from_string("01:20:30.5") << "\"." << endl;
}
