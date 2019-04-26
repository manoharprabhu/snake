/*
 * main.cpp
 *
 *  Created on: Apr 24, 2019
 *      Author: mprabhu
 */

#include "SFML/Graphics.hpp"
#include <iostream>
#include "snake.h"
#include "algorithm"
const int gameWidth = 800;
const int gameHeight = 1600;

void drawSnake(sf::RenderWindow &window, Snake &snake) {
	const Location* snakeBlocks = snake.getSnakeDef();
	const float blockSize = gameWidth / snake.getBoardWidth();
	const int snakeLength = snake.getSnakeLength();
	const float padding = blockSize / 10;
	for (int k = 0; k < snakeLength; k++) {
		const float xPos = snakeBlocks[k].x * blockSize;
		const float yPos = snakeBlocks[k].y * blockSize;
		const float modBlockSize =  std::max(blockSize - padding * (k / 1.5f), blockSize / 3.0f);
		sf::RectangleShape block(
				sf::Vector2f(modBlockSize, modBlockSize));
		block.setFillColor(sf::Color(11, 232, 129));
		block.setPosition(xPos + blockSize / 2 - modBlockSize / 2, yPos + blockSize / 2 - modBlockSize / 2);
		window.draw(block);
	}
}

void drawPowerUp(sf::RenderWindow &window, Snake &snake) {
	const float blockSize = gameWidth / snake.getBoardWidth();
	const Location &powerUpLocation = snake.getPowerupLocation();
	sf::CircleShape circle;
	circle.setFillColor(sf::Color(255, 63, 52, 100));
	circle.setRadius(blockSize / 2);
	circle.setPosition(powerUpLocation.x * blockSize, powerUpLocation.y * blockSize);

	sf::CircleShape innerCircle = circle;
	innerCircle.setRadius(blockSize / 3);
	innerCircle.setFillColor(sf::Color(255, 63, 52, 255));
	innerCircle.setPosition(powerUpLocation.x * blockSize + (blockSize / 6), powerUpLocation.y * blockSize + (blockSize / 6));
	window.draw(circle);
	window.draw(innerCircle);
}

void drawScore(sf::RenderWindow &window, Snake &snake, sf::Font &font) {
	window.pushGLStates();
	const float blockSize = gameWidth / snake.getBoardWidth();
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(gameWidth / 5.0f);
	score.setFillColor(sf::Color(245, 59, 87, 50));
	score.setStyle(sf::Text::Bold);
	score.setString(std::to_string(snake.getSnakeLength()));
	score.setPosition(
			sf::Vector2f(gameWidth - score.getLocalBounds().width - blockSize,
					0.0f));
	window.draw(score);
	window.popGLStates();
}

void performDirectionTurn(Snake &snake, Snake::Direction direction) {
	snake.setDirection(direction);
}

void drawUI(sf::RenderWindow &window, Snake &snake, sf::Font &font) {
	window.clear(sf::Color(255, 255, 255));
	drawSnake(window, snake);
	drawPowerUp(window, snake);
	drawScore(window, snake, font);
	window.display();
}

int main(int arc, char **argv) {
	sf::ContextSettings context;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Could not load the font file" << std::endl;
		return 1;
	}
	context.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Snake",
			sf::Style::Titlebar | sf::Style::Close, context);
	sf::Clock clock;
	Snake snake;
	bool isDirectionTurnRequired = false;
	Snake::Direction newDirection;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (snake.isGameOver()) {
				if (event.key.code == sf::Keyboard::Space
						|| event.key.code == sf::Keyboard::Enter) {
					snake = Snake();
				}
			}
			if (!snake.isGameOver()) {
				if (event.key.code == sf::Keyboard::Up) {
					isDirectionTurnRequired = true;
					newDirection = Snake::Direction::UP;
				}

				if (event.key.code == sf::Keyboard::Down) {
					isDirectionTurnRequired = true;
					newDirection = Snake::Direction::DOWN;
				}

				if (event.key.code == sf::Keyboard::Left) {
					isDirectionTurnRequired = true;
					newDirection = Snake::Direction::LEFT;
				}

				if (event.key.code == sf::Keyboard::Right) {
					isDirectionTurnRequired = true;
					newDirection = Snake::Direction::RIGHT;
				}
			}
		}
		if (clock.getElapsedTime().asMicroseconds() > 100000
				&& !snake.isGameOver()) {
			if (isDirectionTurnRequired) {
				performDirectionTurn(snake, newDirection);
				isDirectionTurnRequired = false;
			}
			snake.step();
			clock.restart();
		}
		drawUI(window, snake, font);
	}
	return 0;
}
