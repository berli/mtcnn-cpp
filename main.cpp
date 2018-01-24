#include <iostream>
#include "face_detector.hpp"
#include "helpers.hpp"
#include <sys/time.h>

long getMillSeconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return 1000*tv.tv_sec+tv.tv_usec/1000;
}
int main(int argc, char** argv) {
	Timer timer;
	mtcnn::FaceDetector fd("./model/", 0.6f, 0.7f, 0.7f, true, false, 0);
	cv::Mat img = cv::imread(argv[1]);
	timer.start();
       long s = getMillSeconds();
	std::vector<mtcnn::Face> faces = fd.detect(img, 40.f, 0.709f);
	//std::cout <<"faces:"<<faces.size()<<" Elapsed time (ms): " << timer.stop() << std::endl;
	std::cout <<"faces:"<<faces.size()<<" Elapsed time (ms): " << getMillSeconds()-s << std::endl;
	for (size_t i = 0; i < faces.size(); ++i) 
	{
		std::vector<cv::Point> pts;
		for (int p = 0; p < mtcnn::NUM_PTS; ++p) 
		{
			pts.push_back(cv::Point(faces[i].ptsCoords[2 * p], faces[i].ptsCoords[2 * p + 1]));
		}
		//drawAndShowFace(img, faces[i].bbox.getRect(), pts);
	cv::rectangle(img, faces[i].bbox.getRect(), cv::Scalar(0, 0, 255));
	for (size_t i = 0; i < pts.size(); ++i) 
		cv::circle(img, pts[i], 3, cv::Scalar(0, 0, 255));
	}
	cv::imshow("test", img);
	cv::waitKey(0);
	return 0;
}
