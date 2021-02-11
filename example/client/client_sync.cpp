/* @brief: Implement a simple WebSocket client that connects to 
 *         a test endpoint, echo.websocket.org. 
 *         This WebSocket server is served on port 80 and 
 *         it simply echoes every message we send to it.
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
 */

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>
#include <iomanip>
#include <string>

void Log (const std::string &where, boost::system::error_code ec)
{
    std::cerr << "[" << std::setw(20) << where << "] "
              << (ec ? "Error: " : "OK")
              << (ec ? ec.message() : "")
              << std::endl;
}

int main()
{
    /* Host target */
    const std::string url {"echo.websocket.org"};
    const std::string port {"80"};
    const std::string message {"Ping..."};

    /* Init I/O context & object */
    boost::system::error_code ec {};
    boost::asio::io_context ioc {};
    boost::asio::ip::tcp::socket socket {ioc};
    boost::asio::ip::tcp::resolver resolver {ioc};

    /* Resolve endpoint */
    auto endpoint {resolver.resolve(url, port, ec)};
    if (ec)
    {
        Log("resolver.resolve", ec);
        return -1;
    }

    socket.connect(*endpoint, ec);
    if (ec)
    {
        Log("socket.connect", ec);
        return -2;
    }

    boost::beast::websocket::stream<boost::beast::tcp_stream> wc {std::move(socket)};
    wc.handshake(url, "/", ec);
    if (ec)
    {
        Log("wc.handshake", ec);
        return -3;
    }

    /* Set the text message write option. */
    wc.text(true);

    /* Send a message to the connected WebSocket server */
    boost::asio::const_buffer wbuffer {message.c_str(), message.size()};
    wc.write(wbuffer, ec);
    if (ec)
    {
        Log("wc.write", ec);
        return -4;
    }

    /* Read the echoed message back */
    boost::beast::flat_buffer rbuffer {};
    wc.read(rbuffer, ec);
    if (ec)
    {
        Log("wc.read", ec);
        return -5;
    }

    /* Print the message */
    std::cout << boost::beast::make_printable(rbuffer.data())
              << std::endl;

    Log("returning", ec);
}