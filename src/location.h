/*
 * location.h
 *
 *  Created on: Apr 26, 2019
 *      Author: mprabhu
 */


class Location {
public:
	int x, y;
	Location(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Location(Location &l) {
		this->x = l.x;
		this->y = l.y;
	}

	Location() {
		this->x = 0;
		this->y = 0;
	}
};


