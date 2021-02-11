/* @brief: We have taken all the separate sections of the synchronous
 *         example — resolve, connect, handshake, send, receive
 *         and have turned them into asynchronous calls.
 * 
 * @step: 1. Resolve echo.websocket.org:80 with a resolver class.
 *        2. Pass the resolved endpoint to a TCP stream object,
 *           which uses it to start a connection.
 *        3. When the socket connection succeeds,
 *           construct a boost::beast::websocket::stream object,
 *           to which you pass the TCP socket.
 *        4. Use the websocket::stream object to send a WebSocket handshake.
 *        5. When the handshake succeeds,
 *           use the Beast websocket::stream object to send a message
 * 
 * @note: When calling asynchronous APIs, you need to run the
 *        Boost I/O context with the run function. Make sure the run function
 *        has work to do before calling it, or it will return immediately.
 */

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>
#include <iomanip>
#include <string>

void Log (const std::string& where, boost::system::error_code ec)
{  
   std::cerr << "[" << std::setw(20) << where << "] "
             << (ec ? "Error: " : "OK")
             << (ec ? ec.message() : "")
             << std::endl;
}

void onReceive (
   boost::beast::flat_buffer& rbuffer,                               \
   boost::system::error_code& ec                                     \
)
{
   if (ec)
   {
      Log("onReceive", ec);
      return;
   }

   std::cout << boost::beast::make_printable(rbuffer.data())
             << std::endl;
}

void onSend (
   boost::beast::websocket::stream<boost::beast::tcp_stream>& wc,    \
   boost::beast::flat_buffer& rbuffer,                               \
   boost::system::error_code& ec                                     \
)
{
   if (ec)
   {
      Log("onSend", ec);
      return;
   }

   /* Read the echoed message back */
   wc.async_read(rbuffer,
      [&rbuffer](auto ec, auto nBytesRead) {
         onReceive(rbuffer, ec);
      }
   );
}

void onHandshake (
   boost::beast::websocket::stream<boost::beast::tcp_stream>& wc,    \
   const boost::asio::const_buffer& wbuffer,                         \
   boost::beast::flat_buffer& rbuffer,                               \
   const boost::system::error_code& ec                               \
)
{
   if (ec)
   {
      Log("onHandshake", ec);
      return;
   }

   /* Set the text message write option. */
   wc.text(true);

   /* Send a message to the connected WebSocket server */
   wc.async_write(wbuffer,
      [&wc, &rbuffer](auto ec, auto nBytesWritten) {
         onSend(wc, rbuffer, ec);
      }
   );
}

void onConnect (
   boost::beast::websocket::stream<boost::beast::tcp_stream>& wc,    \
   const std::string& url,                                           \
   const boost::asio::const_buffer& wbuffer,                         \
   boost::beast::flat_buffer& rbuffer,                               \
   const boost::system::error_code& ec                               \
)
{
   if (ec)
   {
      Log("onConnect", ec);
      return;
   }

   wc.async_handshake(url, "/",
      [&wc, &wbuffer, &rbuffer](auto ec) {
         onHandshake(wc, wbuffer, rbuffer, ec);
      }
   );
}

void onResolve (
   boost::beast::websocket::stream<boost::beast::tcp_stream>& wc,    \
   const std::string& url,                                           \
   const boost::asio::const_buffer& wbuffer,                         \
   boost::beast::flat_buffer& rbuffer,                               \
   const boost::system::error_code& ec,                              \
   boost::asio::ip::tcp::resolver::iterator endpoint                 \
)
{
   if (ec)
   {
      Log("onResolve", ec);
      return;
   }

   /* Connect to the TCP socket.
      Instead of constructing the socket and the ws objects separately, the
      socket is now embedded in ws, and we access it through next_layer() */
   wc.next_layer().async_connect(*endpoint,
      [&wc, &url, &wbuffer, &rbuffer](auto ec) {
         onConnect(wc, url, wbuffer, rbuffer, ec);
      }
   );
}

int main ()
{
   /* Host target */
   const std::string url {"echo.websocket.org"};
   const std::string port {"80"};
   const std::string message {"Ping..."};

   /* Init I/O context & object */
   boost::asio::io_context ioc {};
   boost::beast::websocket::stream<boost::beast::tcp_stream> wc {ioc};
   boost::asio::const_buffer wbuffer {message.c_str(), message.size()};
   boost::beast::flat_buffer rbuffer {};

   /* Resolve endpoint */
   boost::asio::ip::tcp::resolver resolver {ioc};
   resolver.async_resolve(url, port,
      [&wc, &url, &wbuffer, &rbuffer](auto ec, auto endpoint) {
         onResolve(wc, url, wbuffer, rbuffer, ec, endpoint);
      }
   );

   ioc.run();

   return 0;
}