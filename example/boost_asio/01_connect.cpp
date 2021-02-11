/* @brief: Boost.Asio provides APIs to interact with low-level I/O interfaces, called I/O objects.
 *         Every Boost.Asio API uses an intermediary to talk to the I/O objects.
 *         This intermediary is called the I/O context, boost::asio::io_context
 *         The I/O context receives work to do and runs it in its own execution environment.
 */

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>

int main ()
{
   /* Create I/O context */
   boost::asio::io_context ioc {};

   /* Create I/O object */
   boost::asio::ip::tcp::socket socket {ioc};
   boost::system::error_code ec {};

   /* The socket object tries to connect to 1.1.1.1:80 */
   auto address {boost::asio::ip::address::from_string("1.1.1.1")};
   boost::asio::ip::tcp::endpoint endpoint {address, 80};
   socket.connect(endpoint, ec);

   if (ec)
   {
      std::cerr << "Error:" << ec.message() << std::endl;
      return -1;
   }
   else
   {
      std::cout << "OK" << std::endl;
      return 0;
   }
}
