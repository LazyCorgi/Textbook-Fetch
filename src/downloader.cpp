#include "downloader.h"
#include <curl/curl.h>
#include <fstream>
#include <iostream>

// 写入回调函数
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

// 进度回调函数
int progressCallback(void *clientp, curl_off_t dltotal, curl_off_t dlnow,
                     curl_off_t ultotal, curl_off_t ulnow) {
  auto callback = static_cast<std::function<void(double, double)> *>(clientp);
  (*callback)(static_cast<double>(dltotal), static_cast<double>(dlnow));
  return 0;
}

void Downloader::download(
    const std::string url, const std::string outputPath,
    std::function<void(double, double)> progressCallback) {
  curl_global_init(CURL_GLOBAL_DEFAULT);
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl) {
    // 设置URL和写入函数
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    // 设置进度回调函数
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, ::progressCallback);
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &progressCallback);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    // 执行下载
    res = curl_easy_perform(curl);
    // 清理资源
    curl_easy_cleanup(curl);

    if (res == CURLE_OK) {
      // 将下载的数据写入文件
      std::ofstream outFile(outputPath);
      outFile << readBuffer;
      outFile.close();
    } else {
      std::cerr << "Download failed: " << curl_easy_strerror(res) << std::endl;
    }
  }
  curl_global_cleanup();
}
