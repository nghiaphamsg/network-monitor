#include "TransportNetwork.h"

#include <boost/test/unit_test.hpp>

using NetworkMonitor::Id;
using NetworkMonitor::Station;
using NetworkMonitor::Route;
using NetworkMonitor::Line;
using NetworkMonitor::PassengerEvent;
using NetworkMonitor::TransportNetwork;

BOOST_AUTO_TEST_SUITE(network_monitor);
BOOST_AUTO_TEST_SUITE(class_TransportNetwork);

BOOST_AUTO_TEST_SUITE(AddStation);

BOOST_AUTO_TEST_CASE(basic)
{
    TransportNetwork nw {};
    bool ok {false};

    Station station {
        "station_000",
        "Station Name"
    };

    ok = nw.AddStation(station);
    BOOST_CHECK(ok);
}

BOOST_AUTO_TEST_CASE(duplicate_id)
{
    TransportNetwork nw {};
    bool ok {false};

    Station station {
        "station_000",
        "Station Name"
    };

    ok = nw.AddStation(station);
    BOOST_REQUIRE(ok);
    ok = nw.AddStation(station);
    BOOST_CHECK(!ok);
}

BOOST_AUTO_TEST_CASE(duplicate_name)
{
    /* It's ok to add a station with the same name, but different ID */
    TransportNetwork nw {};
    bool ok {false};

    Station stationA {
        "station_000",
        "Same Name"
    };
    ok = nw.AddStation(stationA);
    BOOST_REQUIRE(ok);

    Station stationB {
        "station_001",
        "Same Name"
    };
    ok = nw.AddStation(stationB);
    BOOST_CHECK(ok);
}

BOOST_AUTO_TEST_SUITE_END();    /* AddStation */

BOOST_AUTO_TEST_SUITE(AddLine);

BOOST_AUTO_TEST_CASE(basic)
{
    TransportNetwork nw {};
    bool ok {true};

    /* Add stations */
    Station station0 {
        "station_000",
        "Staion Name 0"
    };
    Station station1 {
        "station_001",
        "Station Name 1"
    };
    ok &= nw.AddStation(station0);
    ok &= nw.AddStation(station1);
    BOOST_REQUIRE(ok);

    /* Add line with the one route
       route: 0 ---> 1 */
    Route route {
        "route_000",
        "inbound",
        "line_000",
        "station_000",
        "station_001",
        {"station_000", "station_001"}
    };

    Line line {
        "line_000",
        "Line Name",
        {route},
    };
    ok = nw.AddLine(line);
    BOOST_CHECK(ok);
}

BOOST_AUTO_TEST_CASE(shared_stations)
{
    TransportNetwork nw {};
    bool ok {true};

    /* Add stations */
    Station station0 {
        "station_000",
        "Staion Name 0"
    };
    Station station1 {
        "station_001",
        "Station Name 1"
    };
    Station station2 {
        "station_002",
        "Station Name 2"
    };
    Station station3 {
        "station_003",
        "Station Name 3"
    };
    ok &= nw.AddStation(station0);
    ok &= nw.AddStation(station1);
    ok &= nw.AddStation(station2);
    ok &= nw.AddStation(station3);
    BOOST_REQUIRE(ok);

    /* Add line with the two routes
       route0: 0 ---> 1 ---> 2
       route1: 3 ---> 1 ---> 2*/
    Route route0 {
        "route_000",
        "inbound",
        "line_000",
        "station_000",
        "station_002",
        {"station_000", "station_001", "station_002"}
    };
    Route route1 {
        "route_001",
        "inbound",
        "line_000",
        "station_003",
        "station_002",
        {"station_003", "station_001", "station_002"}
    };

    Line line {
        "line_000",
        "Line Name",
        {route0, route1},
    };
    ok = nw.AddLine(line);
    BOOST_CHECK(ok);
}

BOOST_AUTO_TEST_CASE(duplicate)
{
    /* Can't add the same line twice */
    TransportNetwork nw {};
    bool ok {true};

    /* Add stations */
    Station station0 {
        "station_000",
        "Staion Name 0"
    };
    Station station1 {
        "station_001",
        "Station Name 1"
    };
    ok &= nw.AddStation(station0);
    ok &= nw.AddStation(station1);
    BOOST_REQUIRE(ok);

    /* Add line with the one route
       route: 0 ---> 1 */
    Route route {
        "route_000",
        "inbound",
        "line_000",
        "station_000",
        "station_001",
        {"station_000", "station_001"}
    };

    Line line {
        "line_000",
        "Line Name",
        {route},
    };
    ok = nw.AddLine(line);
    BOOST_REQUIRE(ok);
    ok = nw.AddLine(line);
    BOOST_CHECK(!ok);
}

BOOST_AUTO_TEST_CASE(missing_station)
{
    TransportNetwork nw {};
    bool ok {false};

    /* Add stations */
    Station station0 {
        "station_000",
        "Staion Name 0"
    };
    Station station1 {
        "station_001",
        "Station Name 1"
    };
    Station station2 {
        "station_002",
        "Station Name 2"
    };

    /* Add line with the one route
       route: 0 ---> 1 ---> 2*/
    Route route {
        "route_000",
        "inbound",
        "line_000",
        "station_000",
        "station_002",
        {"station_000", "station_001", "station_002"}
    };

    Line line {
        "line_000",
        "Line Name",
        {route},
    };
    /* Fail: No stations in the network */
    ok = nw.AddLine(line);
    BOOST_CHECK(!ok);

    /* Fail: Add all stations except one */
    ok = true;
    ok &= nw.AddStation(station0);
    ok &= nw.AddStation(station1);
    BOOST_REQUIRE(ok);
    ok = nw.AddLine(line);
    BOOST_CHECK(!ok);

    /* Success: Add final station and try again */
    ok = nw.AddStation(station2);
    BOOST_REQUIRE(ok);
    ok = nw.AddLine(line);
    BOOST_CHECK(ok);
}

BOOST_AUTO_TEST_SUITE_END();    /* AddLine */

BOOST_AUTO_TEST_SUITE_END();    /* class_TransportNetwork */
BOOST_AUTO_TEST_SUITE_END();    /* network_monitor */
