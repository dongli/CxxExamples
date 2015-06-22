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
    // Construct time object from date object.
    ptime t1(date(2000, 1, 1));
    cout << "[Notice]: Construct a boost::ptime object \"" << t1 << "\"." << endl;
    // Set HMS parts of time.
    t1 += hours(5);
    cout << "[Notice]: Add 5 hours \"" << t1 << "\"." << endl;
    t1 += minutes(10);
    cout << "[Notice]: Add 10 minutes \"" << t1 << "\"." << endl;
    t1 += seconds(3);
    cout << "[Notice]: Add 3 seconds \"" << t1 << "\"." << endl;
    t1 += time_duration(0, 0, 0, time_duration::ticks_per_second()*0.5);
    cout << "[Notice]: Add 0.5 seconds \"" << t1 << "\"." << endl;
}
