/* @brief: Implement a C++ function to download the network
 *         layout JSON file from the remote HTTPS endpoint.    
 */

#include <FileDownloader.h>
#include <curl/curl.h>

#include <stdio.h>
#include <string>
#include <filesystem>

bool NetworkMonitor::DownloadFile (
    const std::string& fileURL,
    const std::filesystem::path& destination,
    const std::filesystem::path& caFile
)
{
    CURL* curl {curl_easy_init()};
    if (curl == nullptr)
    {
        return false;
    }

    std::FILE* fp {fopen(destination.string().c_str(), "wb")};
    if (fp == nullptr)
    {
        curl_easy_cleanup(curl);
        return false;
    }

    /* Configuration curl */
    curl_easy_setopt(curl, CURLOPT_URL, fileURL.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_CAINFO, caFile.string().c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    /* Perform the request */
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    fclose(fp);

    return res == CURLE_OK;
}
