/* @brief: Synchronous operations
 *         Under the hood the connect function talks to the io_context object.
 *         The io_context object, in turn, talks to the TCP socket interface to connect to an endpoint
 *         When the connection completes (or fails), the TCP socket replies directly to the I/O context,
 *         which receives the response.
 *         Finally, the I/O context forwards the response back to us through the error_code variable.
 * 
 * @note:  If you run synchronous code, you don't see the execution environment,
 *         you only see the result of the operation you have run,
 *         Because io_context::run function is called under the hood. 
 *         Example: socket.connect tries to connect to an endpoint and places the result of the connection
 *         into the error_code parameter. 
 *         The work of the I/O context happens under the hood and you don't see it.
 */

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>

void Log (boost::system::error_code);

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
   socket.connect(*endpoint, ec);
   
   if (ec)
   {
      Log(ec);
      return -2;
   }
   Log(ec);
   return 0;
}

void Log (boost::system::error_code ec)
{
   std::cerr << (ec ? "Error: " : "OK")
             << (ec ? ec.message() : "")
             << std::endl;
}