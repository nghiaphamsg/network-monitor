#include "TransportNetwork.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>

using NetworkMonitor::Id;
using NetworkMonitor::Station;
using NetworkMonitor::Route;
using NetworkMonitor::Line;
using NetworkMonitor::PassengerEvent;
using NetworkMonitor::TransportNetwork;

bool Station::operator==(const Station& other) const
{
    return id == other.id;
}

bool Route::operator==(const Route& other) const
{
    return id == other.id;
}

bool Line::operator==(const Line& other) const
{
    return id == other.id;
}

/* Default constructor */
TransportNetwork::TransportNetwork() = default;

/* Destructor */
TransportNetwork::~TransportNetwork() = default;

/* Copy constructor */
TransportNetwork::TransportNetwork(
    const TransportNetwork& copied
) = default;

/* Move constructor */
TransportNetwork::TransportNetwork(
    TransportNetwork&& moved
) = default;

/* Copy assignment operator */
TransportNetwork& TransportNetwork::operator=(
    const TransportNetwork& copied
) = default;

/* Move assignment operator */
TransportNetwork& TransportNetwork::operator=(
    TransportNetwork&& moved
) = default;

bool TransportNetwork::AddStation (
    const Station& station
)
{
    /* Cannot add a station that is already in the network */
    if (GetStation(station.id) != nullptr)
        return false;
    
    /* Create a new station node and add it to the map
       and start with no passengers, no edges */
    auto node {std::make_shared<GraphNode>(GraphNode {
        station.id,
        station.name,
        0,
        {}
    })};
    stations_.emplace(station.id, std::move(node));

    return true;
}
