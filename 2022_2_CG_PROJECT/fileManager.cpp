
#include "fileManager.h"

void loadCube(std::vector<Cube> &vec) {
	std::ifstream ifs("Vertex.txt");
	if (!ifs.fail()) {
		while (!ifs.eof()) {
			glm::vec3 scale, trans, rotate;
			char c;
			ifs >> scale[0] >> c >> scale[1] >> c >> scale[2];
			ifs >> trans[0] >> c >> trans[1] >> c >> trans[2];
			ifs >> rotate[0] >> c >> rotate[1] >> c >> rotate[2];
			Cube temp = Cube(scale, trans, rotate);
			vec.push_back(temp);
		}
		ifs.close();
	}
}

void loadGroundStage1(std::vector<Ground> &vec) {
	std::ifstream ifs("resource/Map/stage1.txt");
	if (!ifs.fail()) {
		while (!ifs.eof()) {
			glm::vec3 scale, trans, rotate;
			char c;
			ifs >> scale[0] >> c >> scale[1] >> c >> scale[2];
			ifs >> trans[0] >> c >> trans[1] >> c >> trans[2];
			ifs >> rotate[0] >> c >> rotate[1] >> c >> rotate[2];
			Ground temp = Ground(scale, trans, rotate);
			vec.push_back(temp);
		}
		ifs.close();
		vec.pop_back();
	}
}

void loadBlock() {
	std::ifstream ifs("Vertex.txt");
	if (!ifs.fail()) {
		while (!ifs.eof()) {
			glm::vec3 scale, trans, rotate;
			char c;
			ifs >> scale[0] >> c >> scale[1] >> c >> scale[2];
			ifs >> trans[0] >> c >> trans[1] >> c >> trans[2];
			ifs >> rotate[0] >> c >> rotate[1] >> c >> rotate[2];
			Cube* temp = new Cube(scale, trans, rotate);
		}
	}
}