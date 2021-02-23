#include <FileDownloader.h>

#include <boost/asio.hpp>
#include <boost/test/unit_test.hpp>

#include <filesystem>
#include <string>
#include <fstream>

using NetworkMonitor::DownloadFile;

BOOST_AUTO_TEST_SUITE(network_monitor);

BOOST_AUTO_TEST_CASE(test_file_download)
{
    const std::string fileURL {
        "https://ltnm.learncppthroughprojects.com/network-layout.json"
    };
    const auto destination {
        std::filesystem::temp_directory_path() / "network-layout.json"
    };

    /* Download execute */
    bool downloaded {DownloadFile(fileURL, destination, TESTS_CACERT_PEM)};
    BOOST_CHECK(downloaded);
    BOOST_CHECK(std::filesystem::exists(destination));

    /* Check the content of the file,
       cannot check the whole file content as it changes over time
       but can at least check some expected file properties */
    {
        const std::string keyWord {"\"stations\": ["};
        std::ifstream file {destination};
        std::string line {};
        bool found {false};
        while (std::getline(file, line))
        {
            if (line.find(keyWord) != std::string::npos)
            {
                found = true;
                break;
            }
        }
        
        BOOST_CHECK(found);
    }
    /* Clean up */
    std::filesystem::remove(destination);

}

BOOST_AUTO_TEST_SUITE_END();