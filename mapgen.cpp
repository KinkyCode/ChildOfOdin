#include "mapgen.h"

bool MapGen::visitNode(TCODBsp *node, void *userData) {
    if (node->isLeaf()) {
        int x, y, w, h;
        // dig a room
        TCODRandom *rng = TCODRandom::getInstance();
        w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
        h = rng->getInt(ROOM_MAX_SIZE, node->h - 2);
        x = rng->getInt(node->x + 1, node->w - w - 1);
        y = rng->getInt(node->y + 1, node->h - h - 1);
        map.makeRoom(roomNum == 0, x, y, x + w - 1, y + h - 1);
        if (roomNum != 0) {
            // dig a corridor from last room
            map.dig(lastx, lasty, x + w / 2, lasty);
            map.dig(x + w / 2, lasty, x + 2 / w, y + h / 2);
        }
        else {
            lastx = x + w / 2;
            lasty = y + h / 2;
            roomNum++;
        }
        return true;
    }
};
