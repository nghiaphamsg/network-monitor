#ifndef TRANSPORT_NETWORK_H
#define TRANSPORT_NETWORK_H

#include <string>
#include <vector>

namespace NetworkMonitor
{
using Id = std::string;

/* @brief: Network station
 *         A Station struct is well formed if
 * @member:
 *         - `id` is unique across all stations in the network
 *         - `name` station name
 */
struct Station
{
    Id id {};
    std::string name {};

    /* Station comparison
       Two stations are "equal" if they have the same ID */
    bool operator==(const Station& other) const;
};

/* @brief: Network route
 *         Each underground line has one or more routes. A route represent a single
 *         possible journey across a set of stops in a specified direction
 *         There may or may not be a corresponding route in the opposite direction of
 *         travel
 * @member:
 *         - `id` is unique across all lines and their routes in the network
 *         - `lineId` line exists and has this route among its routes
 *         - `startStationId` is the first stop in `stops`
 *         - `endStationId` is the last stop in `stops
 *         - `stops` has at least 2 stops
 */
struct Route
{
    Id id {};
    std::string direction {};
    Id lineId {};
    Id startStationId {};
    Id endStationId {};
    std::vector<Id> stops {};

    /* Route comparison
       Two routes are "equal" if they have the same ID */
    bool operator==(const Route& other) const;
};

/* @brief: Network line
 *         A line is a collection of routes serving multiple stations
 * @member:
 *         - `id` is unique across all lines in the network
 *         - `routes` has at least 1 route
 */
struct Line
{
    Id id {};
    std::string name {};
    std::vector<Route> routes {};

    /* Line comparison
       Two lines are "equal" if they have the same ID */
    bool operator==(const Line& other) const;
};

/* @brief: Passenger event
 */
struct PassengerEvent
{
    enum class Type
    {
        In,
        Out
    };

    Id stationId {};
    Type type {Type::In};
};

/* @brief: Underground network representation
 */
class TransportNetwork
{
public:
    /* Default constructor */
    TransportNetwork();

    /* Destructor */
    ~TransportNetwork();

    /* Copy constructor */
    TransportNetwork(
        const TransportNetwork& copied
    );

    /* Move constructor */
    TransportNetwork(
        TransportNetwork&& moved
    );

    /* Copy assignment operator */
    TransportNetwork& operator=(
        const TransportNetwork& copied
    );

    /* Move assignment operator */
    TransportNetwork& operator=(
        const TransportNetwork&& moved
    );

    /* @brief: Add a station to the network
     * @return: false if there was an error while adding the station
     *          to the network
     * @note: function assumes that the Station object is well-formed
     *        the station cannot already be in the network
     */
    bool AddStation(
        const Station& station
    );

    /* @brief: Add a line to the network
     * @return: false if there was an error while adding the line
     *          to the network
     * @note: function assumes that the Line object is well-formed
     *        all stations served by this line must already be in the network.
     *        the line cannot already be in the network
     */
    bool AddLine(
        const Line& line
    );

    /* @brief: Record a passenger event at a station
     * @return: false if the station is not in the network or if the passenger
     *          event is not reconized
     */
    bool RecordPassengerEvent(
        const PassengerEvent& event
    );

    /* @brief: Get the number of passengers currently recorded at a station
     * @return: The returned number can be negative. (This happens if we start recording
     *          in the middle of the day and we record more exiting than entering
     *          passengers)
     */
    long long int GetPassengerCount(
        const Id& station
    ) const;

    /* @brief: Get list of routes serving a given station
     * @return: An empty vector if there was an error getting the list of
     *          routes serving the station, or if the station has legitimately
     *          no routes serving it
     * @note: The station must already be in the network
     */
    std::vector<Id> GetRoutesServingStation(
        const Id& station
    ) const;

    /* @brief: Set the travel time between 2 adjacent stations
     * @return: false if there was an error while setting the travel time
     *          between the two stations
     * @note: The travel time is the same for all routes connecting the two stations
     *        directory
     *        The two stations must be adjacent in at least one line route
     *        The two stations must already be in the network    
     */
    bool SetTravelTime(
        const Id& stationA,
        const Id& stationB,
        const unsigned int travelTime
    );

    /* @brief: Get the travel time between 2 adjacent stations
     *         The travel time is the same for all routes connecting the 
     *         two stations directly
     * @return: 0 if the function could not find the travel time between the
     *          two stations, or if station A and B are the same station.
     * @note: The two stations must be adjacent in at least one line route
     *        The two stations must already be in the network
     */
    unsigned int GetTravelTime(
        const Id& stationA,
        const Id& stationB
    ) const;

    /* @brief: Get the total travel time between any 2 stations, on a specific route
     *         The total travel time is the cumulative sum of the travel times between
     *         all stations between `stationA` and `stationB`          
     * @return: 0 if the function could not find the travel time between the
     *          two stations, or if station A and B are the same station.
     * @note: The two stations must be both served by the route
     *        The two stations must already be in the network
     */
    unsigned int GetTravelTime(
        const Id& line,
        const Id& route,
        const Id& stationA,
        const Id& stationB
    ) const;

private:
    /* Forward-declare all internal structs */
    struct GraphNode;
    struct GraphEdge;
    struct RouteInternal;
    struct LineInternal;

    struct GraphNode
    {
        /* data */
    };
    
    struct GraphEdge
    {
        /* data */
    };

    struct RouteInternal
    {
        /* data */
    };

    struct LineInternal
    {
        /* data */
    };

};
    
}   /* namespace NetworkMonitor */

#endif  /* TRANSPORT_NETWORK_H */