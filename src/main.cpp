#include "Scene.h"

#include "CameraPerspective.h"

#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"

#include "ShaderFlat.h"
#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include "ShaderPhongBumpMapped.h"

#include "LightPoint.h"
#include "LightArea.h"
#include "timer.h"


//int samples;
//SampleGenerator* sampleGenerator = NULL;

//#define OVERSAMPLING

Mat RenderFrame(void)
{
	// Define a scene
	CScene scene;

	// Load scene description 
//	scene.ParseOBJ("../data/cone32.obj");
//	scene.ParseOBJ("barney.obj");
//	scene.ParseOBJ("ground.obj");

#ifdef ENABLE_BSP
	// Build BSPTree
	scene.BuildAccelStructure();
#endif

	// --- Scene description for 4.2 only ---

	auto shd1 = std::make_shared<CShaderPhongBumpMapped>(scene, RGB(1, 0, 0), 0.1f, 0.5f, 0.5f, 40); // red surface
	auto shd2 = std::make_shared<CShaderPhongBumpMapped>(scene, RGB(1, 1, 0), 0.1f, 0.5f, 0.5f, 40); // yellow surface
	
	auto shd3 = std::make_shared<CShaderPhong>(scene, RGB(0, 1, 1), 0.1f, 0.5f, 0.5f, 40); // cyan surface
	auto shd4 = std::make_shared<CShaderPhong>(scene, RGB(0, 0, 1), 0.1f, 0.5f, 0.5f, 40); // blue surface
	
	scene.Add(std::make_shared<CPrimSphere>(Vec3f(-2, 1.7f, 0), 2, shd1));
	scene.Add(std::make_shared<CPrimSphere>(Vec3f(1, -1, 1), 2.2f, shd3));
	scene.Add(std::make_shared<CPrimSphere>(Vec3f(3, 0.8f, -2), 2, shd4));
	scene.Add(std::make_shared<CPrimPlane>(Vec3f(0, -1, 0), Vec3f(0, 1, 0), shd2));
	
	Vec3f pointLightIntensity(7, 7, 7);
	Vec3f lightPosition2(-3, 5, 4);
	Vec3f lightPosition3(0, 1, 4);
	
	scene.Add(std::make_shared<CLightPoint>(pointLightIntensity, lightPosition2));
	scene.Add(std::make_shared<CLightPoint>(pointLightIntensity, lightPosition3));

	// --- End description for 4.2 ---


	Mat img(scene.m_pCamera->getResolution(), CV_32FC3);		// image array
	Ray ray;                                          			// primary ray


#ifdef OVERSAMPLING
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			// --- PUT YOUR CODE HERE ---
		}
	}
#else
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			scene.m_pCamera->InitRay(x, y, ray); // initialize ray
			img.at<Vec3f>(y, x) = scene.RayTrace(ray);
		}
#endif

#ifdef OVERSAMPLING
	delete sampleGenerator;
#endif
	
	img.convertTo(img, CV_8UC3, 255);
	return img;
}

int main(int argc, char* argv[])
{
	//if (argc == 3 && !strcmp(argv[1], "-regular")) {
	//	samples = atoi(argv[2]);
	//	sampleGenerator = new RegularSampleGenerator;
	//}
	//else if (argc == 3 && !strcmp(argv[1], "-random")) {
	//	samples = atoi(argv[2]);
	//	sampleGenerator = new RandomSampleGenerator;
	//}
	//else if (argc == 3 && !strcmp(argv[1], "-stratified")) {
	//	samples = atoi(argv[2]);
	//	sampleGenerator = new StratifiedSampleGenerator;
	//}
	//else if (argc == 1)
	//{
	//	samples = 4;
	//	sampleGenerator = new RandomSampleGenerator;
	//}
	//else {
	//	std::cerr << "Usage: " << argv[0] << " [option(s)]" << std::endl;
	//	std::cerr << std::endl;
	//	std::cerr << "Options are:" << std::endl;
	//	std::cerr << "  -regular <samples>    : Regular sampling." << std::endl;
	//	std::cerr << "  -random <samples>     : Random sampling." << std::endl;
	//	std::cerr << "  -stratified <samples> : Stratified sampling." << std::endl;
	//	exit(1);
	//}

	Mat img = RenderFrame();
	imshow("Image", img);
	waitKey();
	imwrite("image.jpg", img);
	return 0;
}
