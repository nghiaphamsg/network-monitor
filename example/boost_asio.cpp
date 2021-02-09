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
   auto address { boost::asio::ip::address::from_string("1.1.1.1") };
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
