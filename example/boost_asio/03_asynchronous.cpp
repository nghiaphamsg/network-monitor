/* @brief: Asynchronous operations
 *         socket.async_connect API receives a callback handler as a second parameter
 * 
 * @note:  If you run asynchronous code, you have to manage the I/O context execution environment,
 *         and you do it through the io_context::run function
 *         The run function is a loop that looks for work to do. It returns when there is no work left.
 *         In this context, work to do means an asynchronous callback to call when an operation has completed.
 */

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>

void Log (boost::system::error_code);
void OnConnect (boost::system::error_code);

int main ()
{
    boost::system::error_code ec {};

    /* Create I/O context */
    boost::asio::io_context ioc {};

    /* Create I/O object */
    boost::asio::ip::tcp::socket socket {ioc};

    /* The TCP socket needs to resolve the URL wwww.google.com to an IP address */
    boost::asio::ip::tcp::resolver resolver {ioc};
    auto endpoint {resolver.resolve("google.com", "80", ec)};

    if (ec)
    {
        Log(ec);
        return -1;
    }

    /* Asynchronous function call */
    socket.async_connect(*endpoint, OnConnect);

    /* We must call io_context::run for asynchronous callbacks to run */
    ioc.run();

    return 0;
}

void OnConnect (boost::system::error_code ec)
{
    Log(ec);
}

void Log (boost::system::error_code ec)
{
    std::cerr << (ec ? "Error: " : "OK")
              << (ec ? ec.message() : "")
              << std::endl;
}