#include <iostream>
#include <OpenNI.h>
#include "Viewer.h"

using namespace std;
using namespace openni;

int main(int argc, char** argv) {
	Status rc = STATUS_OK;

	Device device;
	VideoStream depth;

	rc = OpenNI::initialize();
	if (rc != STATUS_OK) {
		cout << "ERROR1" << endl;
		OpenNI::shutdown();
		return 1;
	}

	Array<DeviceInfo> deviceList;
	OpenNI::enumerateDevices(&deviceList);

	const char *deviceUri = deviceList[0].getUri();

	rc = device.open(deviceUri);
	if (rc != STATUS_OK) {
		cout << "ERROR3" << endl;
		OpenNI::shutdown();
		return 3;
	}

	rc = depth.create(device, SENSOR_DEPTH);
	if (rc != STATUS_OK) {
		cout << "ERROR4" << endl;
		OpenNI::shutdown();
		return 4;
	}

	rc = depth.start();
	if (rc != STATUS_OK) {
		cout << "ERROR5" << endl;
		OpenNI::shutdown();
		return 5;
	}

	if (!depth.isValid()) {
		cout << "ERROR6" << endl;
		OpenNI::shutdown();
		return 6;
	}

	SampleViewer viewer("Depth Test", device, depth);
	rc = viewer.init(argc, argv);
	if (rc != STATUS_OK) {
		cout << "ERROR7" << endl;
		OpenNI::shutdown();
		return 7;
	}
	viewer.run();

	getchar();
	return 0;
}