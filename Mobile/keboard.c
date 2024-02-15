#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    VideoCapture cap(0); // 웹캠으로부터 비디오 스트림을 읽어옵니다.

    if (!cap.isOpened()) {
        return -1; // 웹캠을 열지 못했을 경우 종료합니다.
    }

    Mat frame, gray, prevGray;
    std::vector<Point2f> points[2];

    while (true) {
        cap >> frame; // 웹캠에서 새로운 프레임을 읽어옵니다.
        cvtColor(frame, gray, COLOR_BGR2GRAY); // 프레임을 그레이스케일로 변환합니다.

        if (points[0].empty()) {
            goodFeaturesToTrack(gray, points[1], 200, 0.01, 10); // 초기 키포인트를 검출합니다.
            prevGray = gray.clone();
        } else {
            std::vector<uchar> status;
            std::vector<float> err;
            calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err);

            for (size_t i = 0; i < points[1].size(); i++) {
                if (status[i]) {
                    circle(frame, points[1][i], 3, Scalar(0, 255, 0), -1); // 움직임을 인식한 지점에 점을 찍습니다.
                }
            }

            points[0] = points[1];
            prevGray = gray.clone();
        }

        imshow("Frame", frame); // 결과 프레임을 화면에 출력합니다.

        if (waitKey(30) >= 0) {
            break; // 사용자가 종료 키를 누르면 프로그램을 종료합니다.
        }
    }

    return 0;
}
