#include "ZedWrapper.h"

#include <sl/Camera.hpp>

using namespace sl;

ZedWrapper::ZedWrapper()
{

}

ZedWrapper::~ZedWrapper()
{
	mZed->close();
	delete mZed;
}


bool ZedWrapper::init(String svo)
{
	mZed = new Camera;

	InitParameters init_params;
	init_params.depth_mode = DEPTH_MODE::QUALITY;
	init_params.coordinate_units = UNIT::MILLIMETER;
	init_params.input.setFromSVOFile(svo);

	ERROR_CODE returned_state = mZed->open(init_params);
	if (returned_state != ERROR_CODE::SUCCESS) {
		std::cout << "Error " << returned_state << ", exit program.\n";
		return false;
	}

	mZedDepth = new Mat(mZed->getCameraInformation().camera_resolution, MAT_TYPE::U8_C4);
	mCLDepth = new cv::Mat(mZedDepth->getHeight(), mZedDepth->getWidth(), CV_8UC4, mZedDepth->getPtr<sl::uchar1>(MEM::CPU), mZedDepth->getStepBytes(MEM::CPU));

	return true;
}

bool ZedWrapper::progressFrame()
{
	if (mZed->grab() == ERROR_CODE::SUCCESS)
	{
		return true;
	}
	else if (mZed->grab() == ERROR_CODE::END_OF_SVOFILE_REACHED)
	{
		std::cout << "SVO end has been reached. Looping back to first frame" << std::endl;
		mZed->setSVOPosition(0);
		return false;
	}
}

Mat ZedWrapper::retrieveDepth()
{
	mZed->retrieveImage(*mZedDepth, VIEW::DEPTH);
	return *mZedDepth;
}

cv::Mat ZedWrapper::retrieveOpenCLDepth()
{
	retrieveDepth();
	return *mCLDepth;
}
