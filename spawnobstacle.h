#ifndef spawnobstacle_H
#define spawnobstacle_H
#include<vector>

using namespace std;

struct Obstacle {
    int x, y;
    bool passed = false;
    bool active;
    int type;
};

vector<Obstacle> obstacles;

bool canSpawnInLane(int lane, int minGap) {
    for (const auto& obs : obstacles) {
        if (obs.active && (obs.x == lane * LANE_WIDTH + 50)) {
            if (obs.y < minGap) {
                return false;
            }
        }
    }
    return true;
}

void spawnObstacle(int num) {
    std::set<int> usedLanes;
    int currentY = 0;

    for (int i = 0; i < num; i++) {
        int tries = 0;
        bool spawned = false;
        while (tries < 10 && !spawned) {
            int lane = rand() % 3;
            if (usedLanes.count(lane) == 0 && canSpawnInLane(lane, 300)) {
                usedLanes.insert(lane);

                int verticalGap = 300;

                Obstacle obs;
                obs.x = lane * LANE_WIDTH + (LANE_WIDTH - OBSTACLE_SIZE) / 2;
                obs.y = currentY - verticalGap;
                obs.active = true;
                obs.type = rand() % 3;
                obstacles.push_back(obs);
                currentY = obs.y;
                spawned = true;
            }
            tries++;
        }
    }
}

#endif // spawnobstacle_H
