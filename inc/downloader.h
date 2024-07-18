#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <functional>
#include <string>

class Downloader {
public:
  void download(const std::string url, const std::string outputPath,
                std::function<void(double, double)> progressCallback);
};

#endif // DOWNLOADER_H
