/* @breaf: Implement a C++ function to download the network
 *         layout JSON file from the remote HTTPS endpoint.
 * @Note: Using a C++ wrapper for libcurl
 */

#ifndef FILE_DOWNLOADER_H
#define FILE_DOWNLOADER_H

#include <nlohmann/json.hpp>

#include <string>
#include <filesystem>

namespace NetworkMonitor
{
    bool DownloadFile (
        const std::string& fileURL,
        const std::filesystem::path& destination,
        const std::filesystem::path& caFile = {}
    );

    nlohmann::json ParseJsonFile (
        const std::filesystem::path& src
    );
}   /* namespace NetworkMonitor */

#endif  /* FILE_DOWNLOADER_H */