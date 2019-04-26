#include "snake.h"
#include "stdlib.h"
#define BOARDWIDTH 16
#define BOARDHEIGHT 32

Snake::Snake() {
	this->boardWidth = BOARDWIDTH;
	this->boardHeight = BOARDHEIGHT;
	this->snakeLength = 4;
	this->direction = Direction::UP;
	this->gameOver = false;
	this->snakeDef = new Location[100];
	this->snakeDef[0] = Location(8, 8);
	this->snakeDef[1] = Location(8, 9);
	this->snakeDef[2] = Location(8, 10);
	this->snakeDef[3] = Location(8, 11);
	this->regeneratePowerCell();
}

int Snake::getBoardWidth() const {
	return this->boardWidth;
}

int Snake::getBoardHeight() const {
	return this->boardHeight;
}

int Snake::getSnakeLength() const {
	return this->snakeLength;
}

bool Snake::isGameOver() const {
	return this->gameOver;
}

void Snake::regeneratePowerCell() {
	while (true) {
		const int x = rand() % this->boardWidth;
		const int y = rand() % this->boardHeight;
		if (!isOutOfBounds(x, y) && !isSnakePresentOnCell(x, y)) {
			this->powerCell = Location(x, y);
			return;
		}
	}
}

void Snake::setDirection(Snake::Direction direction) {
	if (this->direction == direction) {
		return;
	}
	switch (direction) {
	case Direction::UP:
	case Direction::DOWN:
		if (this->direction == Direction::LEFT
				|| this->direction == Direction::RIGHT) {
			this->direction = direction;
		}
		break;
	case Direction::RIGHT:
	case Direction::LEFT:
		if (this->direction == Direction::UP
				|| this->direction == Direction::DOWN) {
			this->direction = direction;
		}
		break;
	default:
		break;
	}
}

bool Snake::isOutOfBounds(int x, int y) const {
	if(x >= 0 && x < this->boardWidth && y >= 0 && y < this->boardHeight) {
		return false;
	}

	return true;
}

bool Snake::isSnakePresentOnCell(int x, int y) const {
	for (int index = 0; index < this->snakeLength; index++) {
		if (this->snakeDef[index].x == x && this->snakeDef[index].y == y) {
			return true;
		}
	}
	return false;
}

const Location* Snake::getSnakeDef() const {
	return this->snakeDef;
}

const Location& Snake::getPowerupLocation() const {
	return this->powerCell;
}

void Snake::step() {
	if (!isStepValid()) {
		this->gameOver = true;
		return;
	}
	Location newLocation;
	const Location &head = this->snakeDef[0];
	switch (direction) {
	case Direction::UP:
		newLocation = Location(head.x, head.y - 1);
		break;
	case Direction::RIGHT:
		newLocation = Location(head.x + 1, head.y);
		break;
	case Direction::DOWN:
		newLocation = Location(head.x, head.y + 1);
		break;
	case Direction::LEFT:
		newLocation = Location(head.x - 1, head.y);
		break;
	}
	for (int k = 0; k < this->snakeLength; k++) {
		const Location temp = this->snakeDef[k];
		this->snakeDef[k] = newLocation;
		newLocation = temp;
	}

	for (int k = 0; k < this->snakeLength; k++) {
		if (this->snakeDef[k].x == this->powerCell.x
				&& this->snakeDef[k].y == this->powerCell.y) {
			this->snakeLength++;
			this->snakeDef[this->snakeLength - 1] =
					this->snakeDef[this->snakeLength - 2];
			this->regeneratePowerCell();
			break;
		}
	}
}

bool Snake::isStepValid() const {
	const Location &head = this->snakeDef[0];
	switch (this->direction) {
	case Direction::UP:
		if (isOutOfBounds(head.x, head.y - 1)) {
			return false;
		}
		if (isSnakePresentOnCell(head.x, head.y - 1)) {
			return false;
		}
		break;
	case Direction::RIGHT:
		if (isOutOfBounds(head.x + 1, head.y)) {
			return false;
		}
		if (isSnakePresentOnCell(head.x + 1, head.y)) {
			return false;
		}
		break;
	case Direction::DOWN:
		if (isOutOfBounds(head.x, head.y + 1)) {
			return false;
		}
		if (isSnakePresentOnCell(head.x, head.y + 1)) {
			return false;
		}
		break;
	case Direction::LEFT:
		if (isOutOfBounds(head.x - 1, head.y)) {
			return false;
		}
		if (isSnakePresentOnCell(head.x - 1, head.y)) {
			return false;
		}
		break;
	default:
		return true;
		break;
	}
	return true;
}
