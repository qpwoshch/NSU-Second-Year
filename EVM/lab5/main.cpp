#include <opencv2/opencv.hpp>
#include <iostream>
#include <locale>

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    cv::VideoCapture capture(0);
    cv::Mat frame;
    cv::Mat newFrame;
    int frameCount = 0;
    double totalCaptureTime = 0;
    double totalProcessingTime = 0;
    double totalDisplayTime = 0;
    double totalFrameTime = 0;
    while (true) {
        double frameStart = cv::getTickCount();
        double startCapture = cv::getTickCount();
        capture >> frame;
        double endCapture = cv::getTickCount();
        totalCaptureTime += (endCapture - startCapture) / cv::getTickFrequency() * 1000.0;
        double startProcessing = cv::getTickCount();
        cv::flip(frame, newFrame, 0);
        cv::erode(newFrame, newFrame, cv::Mat(), cv::Point(-1, -1), 5);
        double endProcessing = cv::getTickCount();
        totalProcessingTime += (endProcessing - startProcessing) / cv::getTickFrequency() * 1000.0;
        double startDisplay = cv::getTickCount();
        cv::imshow("Original video", frame);
        cv::imshow("Modified video", newFrame);
        double endDisplay = cv::getTickCount();
        totalDisplayTime += (endDisplay - startDisplay) / cv::getTickFrequency() * 1000.0;
        frameCount++;
        double frameEnd = cv::getTickCount();
        totalFrameTime += (frameEnd - frameStart) / cv::getTickFrequency();
        if (cv::waitKey(5) == 27) {
            break;
        }
    }

    capture.release();
    cv::destroyAllWindows();
    double totalTime = totalCaptureTime + totalProcessingTime + totalDisplayTime;
    double averageFPS = frameCount / totalFrameTime;
    std::cout << "Всего кадров обработано: " << frameCount << std::endl;
    std::cout << "Среднее время захвата: " << (totalCaptureTime / frameCount) << " мс" << std::endl;
    std::cout << "Среднее время обработки: " << (totalProcessingTime / frameCount) << " мс" << std::endl;
    std::cout << "Среднее время отображения: " << (totalDisplayTime / frameCount) << " мс" << std::endl;
    std::cout << "Среднее количество FPS: " << averageFPS << std::endl;
    std::cout << "\nПроцентное распределение времени:\n";
    std::cout << "Время захвата камеры: " << (totalCaptureTime / totalTime) * 100 << " %\n";
    std::cout << "Время обработки: " << (totalProcessingTime / totalTime) * 100 << " %\n";
    std::cout << "Время отображения: " << (totalDisplayTime / totalTime) * 100 << " %\n";

    return 0;
}
