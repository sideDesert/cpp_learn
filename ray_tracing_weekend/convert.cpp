#include <opencv2/opencv.hpp>
#include <iostream>

namespace Conversion {
int convert(std::string inputFilePath, std::string outputFile){
  cv::Mat image = cv::imread(inputFilePath, cv::IMREAD_COLOR);
  if(image.empty()){
    std::cerr << "Error: Could not open or find the image: " << inputFilePath << std::endl;
    return -1;
  }

  if(!cv::imwrite(outputFile, image)){
    std::cerr << "Error: Could not write image " << outputFile << std::endl;
  }

  std::cout << "Successfully converted " << inputFilePath << " to " << outputFile << std::endl;

  return 0;

}
}
