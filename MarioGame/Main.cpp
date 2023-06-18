#include <SFML/Graphics.hpp>
#include "Mario.h"
#include "Game.h"
#include "Turtle.h"
#include "ScoreBoard.h"

int main()
{	
	//window
	sf::RenderWindow window(sf::VideoMode(1024, 1024) , "Mario Game");
	window.setFramerateLimit(90);// limit fps to 90
    //define mario
	Mario mario(&window);
	//define turtles pointer array
	Turtle** turtles = (Turtle**) malloc(5 * sizeof(Turtle*));;
	
	Turtle turtle1 = Turtle(&window, 1);
	Turtle turtle2 = Turtle(&window, 4);
	Turtle turtle3 = Turtle(&window, 7);
	Turtle turtle4 = Turtle(&window, 10);
	Turtle turtle5 = Turtle(&window, 13);
	turtles[0] = &turtle1;
	turtles[1] = &turtle2;
	turtles[2] = &turtle3;
	turtles[3] = &turtle4;
	turtles[4] = &turtle5;
	
	//define scoreboard
	ScoreBoard scoreBoard;
	//define game
	Game game(&mario, turtles, &scoreBoard);
    while (window.isOpen()) {//game loop
        window.clear(); //clear screen in every loop
        sf::Event event;
        while(window.pollEvent(event)){//check to close game
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

		if (game.state !=1) {//if game hasnt started
			game.drawBackground(&window);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {//if press enter, start game
				game.scoreBoard->setLives(3);//set live and score
				game.scoreBoard->setScore(0);
				game.state = 1; //state = 1 game running
				for (int i = 0; i < 5; i++){//Create turtles again (for restarts)
					*turtles[i] = Turtle(&window, (float)(1+3*i));
					turtles[i]->setPosition(sf::Vector2f(1124, (float)((i+1)*100)));
				}
				mario.setPosition(sf::Vector2f(512, 700));//set mario position
				mario.state = 0;//set mario state. state = 0 mario standing
			}
		}
		else if (game.state == 1) {//if game started
			mario.move();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				if (mario.state != 6 and game.onFloor(&mario)) {//if mario is not dead and touching floor
					mario.jump(false);
				}
			}
			//vy direction
			mario.vy += game.gravity;//add gravity to mario y velocity
			if (mario.state != 6) {//if mario is not dead
				mario.sprite.move(0, mario.vy);//move mario sprite to check collision
				if (game.checkAllCollision(&mario)) {//if mario collide
					mario.sprite.move(0, -mario.vy); //undo movement
					mario.vy = 0;
				}
				else {//if not collide
					mario.sprite.move(0, -mario.vy); //take back movement
					mario.setPosition(mario.getPosition() + sf::Vector2f(0, mario.vy)); //set position to the destination
				}
			}
			else {//mario is dead
				mario.setPosition(mario.getPosition() + sf::Vector2f(0, mario.vy));//dont check any collision. just fall
			}
			//vx direction
			mario.sprite.move(mario.vx, 0);//move mario sprite to check collision
			if (game.checkAllCollision(&mario)) {//if collide any object
				mario.sprite.move(-mario.vx, 0);//undo movement
			}
			else {//if not collide
				mario.sprite.move(-mario.vx, 0);//undo movement
				mario.setPosition(mario.getPosition() + sf::Vector2f(mario.vx, 0));//move the target
			}
			//check Mario is dead and respawn
			if (mario.state == 6 and mario.getPosition().y > 2000) {//if mario dead and fall enough
				mario.vy = 0;
				mario.vx = 0;
				mario.setPosition(sf::Vector2f(512, 700));
				mario.state = 1;
			}
			
			for (int i = 0; i < 5; i++) {//check for turtles
				turtles[i]->vy += game.gravity;//add gravity to turtle y velocity 
				turtles[i]->sprite.move(0, turtles[i]->vy);//move mario to check collision
				if (turtles[i]->state != 6){//if the turtle is not dead 
					if (game.checkAllCollision(turtles[i])) {//if collide
						turtles[i]->sprite.move(0, -turtles[i]->vy);//undo movement
						turtles[i]->vy = 0;
					}
					else {
						turtles[i]->sprite.move(0, -turtles[i]->vy);//undo movement
						turtles[i]->setPosition(turtles[i]->getPosition() + sf::Vector2f(0, turtles[i]->vy));//move to target
					}
					bool changeTurtleDirection = false;

					turtles[i]->sprite.move(turtles[i]->vx, 0);
					if (game.checkWallCollision(turtles[i])) {//if there any wall collision
						changeTurtleDirection = true;
					}

					if (game.checkAllCollision(turtles[i])) {//if collide
						turtles[i]->sprite.move(-turtles[i]->vx, 0);//undo movement
					}
					else {
						turtles[i]->sprite.move(-turtles[i]->vx, 0);//undo movement
						turtles[i]->setPosition(turtles[i]->getPosition() + sf::Vector2f(turtles[i]->vx, 0));//set position to target
					}

					if (changeTurtleDirection) {// if change direction = true
						turtles[i]->vx *= -1; //change direction of velocity
						turtles[i]->state = 3; // state = 3 rotating state
					}
					else {
						turtles[i]->state = 0; //runnning state
					}
				}
				else {//if turtle is dead
					turtles[i]->setPosition(turtles[i]->getPosition() + sf::Vector2f(0, turtles[i]->vy));// fall without any collision detection
				}
				//ckeck if turtle arrive the pipes
				if (turtles[i]->spawned) {//if spawned
					if (turtles[i]->getPosition().y > 785 and (turtles[i]->getPosition().x > 950 or turtles[i]->getPosition().x < 74)) { //if turtle is in pipe area
						turtles[i]->spawned = false;//set unspawn
						turtles[i]->spawnTimeClock.restart();//restart spawn clock
						turtles[i]->spawnTime = 1;//turtle will spawn 1 second later in starting position
						turtles[i]->setPosition(sf::Vector2f(1124, (float)((i + 1) * 100))); //turtle waiting in outside of the game
						if (turtles[i]->heading != -1){//restart turtle headings
							turtles[i]->heading = -1;
							turtles[i]->sprite.scale(-1.f, 1.f);
						}
					}
				}
				//if spawn time is up, check the collisions. If there is no collision, spawn else wait 1 second to spawn
				if (turtles[i]->spawned == false and turtles[i]->spawnTimeClock.getElapsedTime().asSeconds() > turtles[i]->spawnTime) {
					float startingPositions[2][3] = { {100, 168, 1}, {924, 168, -1} };
					int r = rand() % 2;//choose starting s pipe randomly 
					sf::Vector2f rightNowPosition = turtles[i]->getPosition(); // right now position
					sf::Vector2f startingPoint = sf::Vector2f(startingPositions[r][0], startingPositions[r][1]); //turtle spawn position
					turtles[i]->sprite.setPosition(startingPoint);// spawn turtle sprite to starting to check collisons
					if (!game.checkAllCollision(turtles[i])){//if there is no collision
						turtles[i]->sprite.setPosition(rightNowPosition);//undo movement
						turtles[i]->setPosition(startingPoint);//set positon to spawn point
						turtles[i]->spawned = true;
						turtles[i]->vx = startingPositions[r][2] * turtles[i]->speed; //set velocity
						if (turtles[i]->heading == 1) {//set heading
							turtles[i]->sprite.scale(-1.f, 1.f);
						}
					}
					else {// if there is collision, turtle will wait 1 second more to spawn
						turtles[i]->sprite.setPosition(rightNowPosition);//undo movement
						turtles[i]->spawnTimeClock.restart();//restart clock
					}
				}
				turtles[i]->move();
				//check mario and turtle touching
				int side = 0;
				if (mario.state !=6 and game.checkCollusion(turtles[i], &mario, side)) {//if mario is not dead and there is a mario turtle collision
					if (side == 1) {//if mario touchs the head of turtle
						turtles[i]->fall();
						turtles[i]->dead = true;
						game.scoreBoard->setScore(game.scoreBoard->getScore() + 100); //add 100 point to score
						//increase score
						bool allTurtlesDead = true;
						for (int i = 0; i < 5; i++) {
							if (!turtles[i]->dead) {
								allTurtlesDead = false; //if any turtle did not dead, set allTurtlesDead to false
								break;
							}
						}
						if (allTurtlesDead) {
							game.state = 3;//game win screen
						}
					}
					else if (side == 2) {
						mario.fall(); //if mario touchs body of turtle
						game.scoreBoard->setLives(game.scoreBoard->getLives() - 1);//reduce live
						if (game.scoreBoard->getLives() == 0) {//if run out lives
							game.state = 2; // game over screen
						}
					}
				}
				turtles[i]->draw(window);//draw turtle
			}
			game.drawBackground(&window);
			mario.draw(window);
		}
        window.display();
    }
    return 0;
}