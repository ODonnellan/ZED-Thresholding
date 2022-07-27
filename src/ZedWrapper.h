#ifndef ZED_WRAPPER
#define ZED_WRAPPER

#include <sl/Camera.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ZedWrapper
{
public:
	ZedWrapper();
	~ZedWrapper();

	bool init(sl::String svo);

	bool progressFrame();
	sl::Mat retrieveDepth();
	cv::Mat retrieveOpenCLDepth();

private:
	sl::Camera* mZed = nullptr;

	sl::Mat* mZedDepth = nullptr;
	cv::Mat* mCLDepth = nullptr;
};

#endif