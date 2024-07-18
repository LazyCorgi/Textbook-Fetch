#include "downloader.h"

#include <iostream>

int main() {
  std::string i_text, o_text;
  i_text = "https://basic.smartedu.cn/tchMaterial/"
           "detail?contentType=assets_document&contentId=c71014f5-3bf1-47e2-"
           "b9db-d70b79f2b33d&catalogType=tchMaterial&subCatalog=tchMaterial";
  // https
  //     : //
  //     r3-ndr-private.ykt.cbern.com.cn/edu_product/esp/assets/c71014f5-3bf1-47e2-b9db-d70b79f2b33d.pkg/pdf.pdf
  // https
  //     : //
  //     r3-ndr-private.ykt.cbern.com.cn/edu_product/esp/assets/7786158e-01d7-4544-a358-5759664c78ea.pkg/pdf.pdf
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

  Downloader downloader;
  downloader.download(
      url, "../download/abc.pdf", [](double total, double downloaded) {
        if (total > 0) {
          std::cout << "Total: " << total << " bytes\t";
          std::cout << "Progress: " << (downloaded / total) * 100 << "%\r";
          std::cout.flush();
        }
      });

  return 0;
}