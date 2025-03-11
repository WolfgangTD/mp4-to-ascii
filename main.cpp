#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

using std::cout, std::string;

string frame_to_ascii(int pixelIntensity){
    //const string ASCII_CHARS = "@%#&!*+=-_.   ";
    const string ASCII_CHARS = "  ._-=+*!&#%@";

    string s = string(1, ASCII_CHARS[pixelIntensity * ASCII_CHARS.length() / 256]);
    //size_t index = std::clamp(static_cast<size_t>(pixelIntensity * ASCII_CHARS.length() / 256), size_t(0), ASCII_CHARS.length() - 1);
    //return string(1, ASCII_CHARS[index]);
    return s;
}

void video_to_ascii(string video_path, int width, int height){
    using namespace cv;
    VideoCapture cap(video_path);
    cout << "Backend used: " << cap.get(cv::CAP_PROP_BACKEND) << std::endl;
    double fps = cap.get(CAP_PROP_FPS);

    cout << fps << std::endl;

    int frame_duration_ms = 1000/fps;

    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    height = static_cast<int>(width * (static_cast<double>(frame_height) / frame_width) * 0.4194);

    Mat frame, grey_frame, resized_frame;

    // Hide the cursor to reduce flickering
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // Hide cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    while (true){
        cap >> frame;
        if (frame.empty()){
            break;
        }

        cvtColor(frame, grey_frame, COLOR_BGR2GRAY);
        resize(grey_frame, resized_frame, Size(width, height), 0, 0, INTER_LINEAR);
        string ascii_frame;
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                ascii_frame += frame_to_ascii(resized_frame.at<uchar>(i, j));
            }
            ascii_frame += "\n";
        }

        cout << ascii_frame;
        std::this_thread::sleep_for(std::chrono::milliseconds(frame_duration_ms));
    }
}

int main(){
    
    video_to_ascii("cat.mp4", 80, 40);
}