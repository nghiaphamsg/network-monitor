/*  @brief: While a multi-threaded I/O context can help with performance and throughput,
 *          it also incurs the typical pitfalls of concurrent programming.
 *          The most common one is the issue of synchronization between multiple threads
 *          accessing the same shared resource.
 * 
 *          You can think of strands as funnels where multiple operations are serialized
 *          to prevent overlap. A callback that goes through the strand is only called if 
 *          the execution of the previous callback completed.
 * 
 *          When passing the ioc instance to the socket constructor, we wrap it into a 
 *          strand object created on the spot. This way, any callback that results from 
 *          the socket I/O object will pass through the strand.
 */

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>
#include <thread>
#include <iomanip>
#include <vector>

void Log(boost::system::error_code);
void OnConnect (boost::system::error_code);

int main()
{
    std::cerr << "["
              << std::setw(14) << std::this_thread::get_id()
              << "] main"
              << std::endl;

    boost::system::error_code ec{};

    /* Create I/O context */
    boost::asio::io_context ioc{};

    /* Create I/O object */
    /* strand mechanism to help with the synchronization of concurrent io_context::run loops */
    boost::asio::ip::tcp::socket socket{boost::asio::make_strand(ioc)};

    boost::asio::ip::tcp::resolver resolver{ioc};
    auto endpoint{resolver.resolve("google.com", "80", ec)};

    if (ec)
    {
        Log(ec);
        return -1;
    }

    size_t nThreads{4};
    for (size_t i = 0; i < nThreads; ++i)
    {
        socket.async_connect(*endpoint, OnConnect);
    }

    /* We must call io_context::run for asynchronous callbacks to run */
    std::vector<std::thread> threads{};
    threads.reserve(nThreads);
    for (size_t i = 0; i < nThreads; ++i)
    {
        threads.emplace_back(
            [&ioc]() {
                ioc.run();
            }
        );
    }

    /* Release thread resource,
       terminate before we can safely terminate the program */
    for (size_t i = 0; i < nThreads; ++i)
    {
        threads[i].join();
    }

    return 0;
}

void OnConnect(boost::system::error_code ec)
{
    Log(ec);
}

void Log(boost::system::error_code ec)
{
    std::cerr << "[" << std::setw(14) << std::this_thread::get_id() << "] "
              << (ec ? "Error: " : "OK")
              << (ec ? ec.message() : "")
              << std::endl;
}