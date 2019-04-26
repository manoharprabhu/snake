/*
 * snake.h
 *
 *  Created on: Apr 26, 2019
 *      Author: mprabhu
 */
#include "location.h"
#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_


class Snake {
public:
	Snake();
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};
	bool isStepValid() const;
	bool isGameOver() const;
	void step();
	const Location* getSnakeDef() const;
	int getBoardWidth() const;
	int getBoardHeight() const;
	int getSnakeLength() const;
	void setDirection(Snake::Direction direction);
	const Location& getPowerupLocation() const;


private:
	int boardWidth;
	int boardHeight;
	int snakeLength;
	Direction direction;
	bool gameOver;
	Location *snakeDef;
	Location powerCell;

	bool isOutOfBounds(int x, int y) const;
	bool isSnakePresentOnCell(int x, int y) const;
	void regeneratePowerCell();
};


#endif /* SRC_SNAKE_H_ */
