/* @brief: Implement a C++ function to download the network
 *         layout JSON file from the remote HTTPS endpoint.    
 */

#include <FileDownloader.h>

#include <nlohmann/json.hpp>
#include <curl/curl.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <filesystem>
#include <fstream>

bool NetworkMonitor::DownloadFile (
    const std::string& fileURL,
    const std::filesystem::path& destination,
    const std::filesystem::path& caFile
)
{
    /* Provide a buffer to store errors */
    char errBuff[CURL_ERROR_SIZE];
    errBuff[0] = 0;

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
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errBuff);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_CAINFO, caFile.string().c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    /* Perform the request & check error code */
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        size_t len = strlen(errBuff);
        std::cerr << "libcurl: " << res << std::endl;
        if (len)
        {
            std::cerr << errBuff
                      << ((errBuff[len - 1] != '\n') ? "\n" : "")
                      << std::endl;
        }
        else
            std::cerr <<  curl_easy_strerror(res) << std::endl;
        
        /* Clean up */
        curl_easy_cleanup(curl);
        fclose(fp);
        return false;
    }

    /* Clean up */
    curl_easy_cleanup(curl);
    fclose(fp);

    return res == CURLE_OK;
}

nlohmann::json NetworkMonitor::ParseJsonFile (
    const std::filesystem::path& src
)
{
    nlohmann::json parsed {};
    if (!std::filesystem::exists(src))
    {
        return parsed;
    }
    try
    {
        std::ifstream file {src};
        file >> parsed;
    }
    catch(...)
    {
        /* Return an empty object */
    }
    
    return parsed;
}