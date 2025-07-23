#include <curl/curl.h>
#include <iostream>

#include "mainwindow.h"


size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;
    std::string* data = (std::string*)userp;  // Store the data in a string
    data->append((char*)contents, totalSize); // Append the received data to the string
    return totalSize;
}


QStringList MainWindow::getReplayFromUrl(const QString &url)
{
    std::string stdurl = url.toStdString() + ".log";
    std::string buffer;
    QStringList lines;
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();


    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, stdurl.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            QString body = QString::fromStdString(buffer);
            lines = body.split('\n', Qt::SkipEmptyParts);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return lines;
}
