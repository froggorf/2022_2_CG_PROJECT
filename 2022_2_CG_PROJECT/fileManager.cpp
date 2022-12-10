
#include "fileManager.h"

//TODO: 미스터리 박스에서 코인 나오는거면 마리오 코인 값 올려주거나 올려주라는 함수 넣어줘야할듯함

void loadStage1(std::vector<Cube*>& vec) {
    std::ifstream ifs("resource/Map/stage1.txt");
    if (!ifs.fail()) {
        int i = 0;
        while (!ifs.eof()) {
            glm::vec3 scale, trans, rotate;
            char c;
            Cube* temp;
            ifs >> scale[0] >> c >> scale[1] >> c >> scale[2];
            ifs >> trans[0] >> c >> trans[1] >> c >> trans[2];
            ifs >> rotate[0] >> c >> rotate[1] >> c >> rotate[2];
            if (i < 4) {
                temp = new Ground(scale, trans, rotate);
                vec.push_back(temp);
            }
            else if (i >= 4 and i < 6) {
                if (i == 4) {
                    temp = new Door(scale, trans, rotate);
                    vec.push_back(temp);
                }
            }
            else if (i >= 6 and i < 10) {
                temp = new Pipe(scale, trans, rotate);
                vec.push_back(temp);
            }
            else if (i >= 19 and i < 37) {
                temp = new Block(scale, trans, rotate);
                vec.push_back(temp);
            }
            else if (i == 40 or i == 43) {
                temp = new Wall(scale, trans, rotate);
                vec.push_back(temp);
            }
            else if (i >= 41 and i < 43) {
                temp = new Wall(scale, trans, rotate, true);
                vec.push_back(temp);
            }
            else {
                switch (i)
                {
                case 10:
                    temp = new MysteryBlock(scale, trans, rotate, 100);
                    break;
                case 37:
                    temp = new MysteryBlock(scale, trans, rotate, 5);
                    break;
                case 12: case 14:
                    temp = new MysteryBlock(scale, trans, rotate, 1);
                    break;
                default:
                    temp = new Brick(scale, trans, rotate);
                    break;
                }
                vec.push_back(temp);
            }
            i++;
        }
        ifs.close();
        vec.pop_back();
        vec.erase(vec.begin() + 38);
    }
}

void loadStage2(std::vector<Cube*>& vec) {
    std::ifstream ifs("resource/Map/stage2.txt");
    if (!ifs.fail()) {
        int i = 0;
        while (!ifs.eof()) {
            int k;
            glm::vec3 scale, trans, rotate;
            char c;
            Cube* temp;
            ifs >> k;
            ifs >> scale[0] >> c >> scale[1] >> c >> scale[2];
            ifs >> trans[0] >> c >> trans[1] >> c >> trans[2];
            ifs >> rotate[0] >> c >> rotate[1] >> c >> rotate[2];

            switch (k)
            {
            case BLOCK:
                temp = new Block(scale, trans, rotate);
                break;
            case BRICK:
                temp = new Brick(scale, trans, rotate);
                break;
            case DOOR:
                temp = new Door(scale, trans, rotate);
                break;
            case GROUND:
                temp = new Ground(scale, trans, rotate);
                break;
            case MYSTERYBLOCK:
                temp = new MysteryBlock(scale, trans, rotate, 1);
                break;
            case PIPE:
                temp = new Pipe(scale, trans, rotate);
                break;
            case WALL:
                temp = new Wall(scale, trans, rotate);
                break;
            case PICTUREWALL:
                temp = new PictureWall(scale, trans, rotate);
                break;
            default:
                break;
            }

            vec.push_back(temp);
            i++;
        }
        vec.pop_back();
    }
    ifs.close();
}
