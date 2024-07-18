#include "downloader.h"

#include <iomanip>
#include <iostream>
#include <sstream>

void showProgressBar(double percentage) {
  const int barWidth = 50;
  std::cout << "\033[32m[";
  int pos = barWidth * percentage;
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos)
      std::cout << "+"; // green block
    else
      std::cout << " ";
  }
  std::cout << "] \033[0m" << std::fixed << std::setprecision(2)
            << (percentage * 100.0) << "% ";
  std::cout.flush();
}

int main() {
  std::string i_text, o_text;
  i_text = "https://basic.smartedu.cn/tchMaterial/"
           "detail?contentType=assets_document&contentId=c71014f5-3bf1-47e2-"
           "b9db-d70b79f2b33d&catalogType=tchMaterial&subCatalog=tchMaterial";
  std::string::size_type pos1 = i_text.find("contentId="),
                         pos2 = i_text.find("&catalogType=");
  if (pos1 != std::string::npos) {
    o_text = i_text.substr(pos1 + 10, pos2 - pos1 - 10);
    // std::cout << o_text << std::endl;
  } else {
    std::cout << "error" << std::endl;
  }
  std::string url = "https://r3-ndr.ykt.cbern.com.cn/edu_product/esp/assets/" +
                    o_text + ".pkg/pdf.pdf";
  std::cout << url << std::endl;

  std::string downloadPath = "output.pdf";

  Downloader downloader;
  downloader.download(url, downloadPath, [](double total, double downloaded) {
    if (total > 0) {
      static double predownloaded = 0;
      showProgressBar(downloaded / total);
      printf("\033[0m(总计%.2f MB, %.2f KB/s)   \r", total / 1024.0 / 1024.0,
             (downloaded - predownloaded) / 1024.0);
      predownloaded = downloaded;
    }
  });

  std::cout << std::endl << "下载成功" << std::endl;

  return 0;
}