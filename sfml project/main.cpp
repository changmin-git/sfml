#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
using namespace sf;
using namespace std;


int main(void)
{
	RenderWindow window(VideoMode(1320, 810), "1 vs 1 soccer game");
	window.setFramerateLimit(60);
	printf("게임 시작!");

	Texture t1, t2, t3, t4, t5, t6, t7, t8;
	t1.loadFromFile("images/soccerball.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/player1.png");
	t4.loadFromFile("images/player2.png");
	t5.loadFromFile("images/wall.png"); //골포스트
	t6.loadFromFile("images/wall.png");
	t7.loadFromFile("images/wall.png");
	t8.loadFromFile("images/wall.png");

	Texture s1, s2, s3;
	Sprite background(t2), ball(t1), player1(t3), player2(t4);
	Sprite wall1(t5), wall2(t6), wall3(t7), wall4(t8);
	Sprite board(s1), score1(s2), score2(s3);

	ball.setPosition(630, 425);
	player1.setPosition(1020, 425);
	player2.setPosition(220, 425);
	board.setPosition(100, 30);
	wall1.setPosition(1230, 290);
	wall2.setPosition(1230, 580);
	wall3.setPosition(0, 290);
	wall4.setPosition(0, 580);

	float dx = 5.0f, dy = 10.0f; //공 움직임
	int sc1 = 0, sc2 = 0;//점수 계산에 필요
	string scoreboard; //점수판

	Texture w1, w2;
	w1.loadFromFile("images/p1win.png");
	w2.loadFromFile("images/p2win.png");
	Sprite win1(w1), win2(w2);
	win1.setPosition(300, 300);
	win2.setPosition(300, 300);

	float power1 = 0, power2 = 0;

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}

		auto ball_pos = ball.getPosition(); //공의 현재 위치를 받아서 충돌 여부를 확인함
		ball_pos.x += dx;
		if (ball_pos.x < 0 || ball_pos.x > 1260) //벽에 닿으면 공 튕기기
			dx = -dx;
		ball_pos.y += dy;
		if (ball_pos.y < 90 || ball_pos.y > 750)
			dy = -dy;
		ball.move(dx, dy);

		//사용자의 움직임
		if (Keyboard::isKeyPressed(Keyboard::Right)) //플레이어 조작
			player1.move(5, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left))
			player1.move(-5, 0);
		if (Keyboard::isKeyPressed(Keyboard::Up))
			player1.move(0, -3);
		if (Keyboard::isKeyPressed(Keyboard::Down))
			player1.move(0, 3);
		if (Keyboard::isKeyPressed(Keyboard::D)) 
			player2.move(5, 0);
		if (Keyboard::isKeyPressed(Keyboard::A))
			player2.move(-5, 0);
		if (Keyboard::isKeyPressed(Keyboard::W))
			player2.move(0, -3);
		if (Keyboard::isKeyPressed(Keyboard::S))
			player2.move(0, 3);

	
		if (player1.getPosition().x < 0)
			player1.setPosition(0, player1.getPosition().y);
		if (player1.getPosition().x > 1260)
			player1.setPosition(1260, player1.getPosition().y);
		if (player1.getPosition().y < 0)
			player1.setPosition(player1.getPosition().x, 0); 
		if (player1.getPosition().y > 710)
			player1.setPosition(player1.getPosition().x, 710);
		
		
		//물리
		if (FloatRect(ball_pos.x - 1, ball_pos.y - 1, 55, 55).intersects(player2.getGlobalBounds()))
		{
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				power2 = 3.0f;
				dx = -dx - power2;
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				power2 = 3.0f;
				dx = -dx + power2;
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				power2 = 3.0f;
				dy = -dy - power2;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				power2 = 3.0f;
				dy = -dy + power2;
			}
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				dx = 0; dy = 0;
				ball.move(dx, dy);
			}
			if (Keyboard::isKeyPressed(Keyboard::E)) {
				dx = 7.0f; dy = 1.0f;
				ball.move(dx, dy);
			}
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				dx = 7.0f; dy = -1.0f;
				ball.move(dx, dy);
			}
		}

		if (FloatRect(ball_pos.x - 1, ball_pos.y - 1, 55, 55).intersects(player1.getGlobalBounds()))
		{
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				power1 = 3.0f;
				dx = -dx - power1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				power1 = 3.0f;
				dx = -dx + power1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				power1 = 3.0f;
				dy = -dy - power1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				power1 = 3.0f;
				dy = -dy + power1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				dx = 0; dy = 0;
				ball.move(dx, dy);
			}
			if (Keyboard::isKeyPressed(Keyboard::N)) {
				dx = -7.0f; dy = 1.0f;
				ball.move(dx, dy);
			}
			if (Keyboard::isKeyPressed(Keyboard::M)) {
				dx = -7.0f; dy = -1.0f;
				ball.move(dx, dy);
			}
		}

		if (FloatRect(1230, 290, 87, 10).intersects(ball.getGlobalBounds())) //골포스트 부분
		{
			dx = -dx;
			dy = -dy;
		}
		if (FloatRect(1230, 580, 87, 10).intersects(ball.getGlobalBounds()))
		{
			dx = -dx;
			dy = -dy;
		}
		if (FloatRect(0, 290, 87, 10).intersects(ball.getGlobalBounds()))
		{
			dx = -dx;
			dy = -dy;
		}
		if (FloatRect(0, 580, 87, 10).intersects(ball.getGlobalBounds()))
		{
			dx = -dx;
			dy = -dy;
		}
		
		
		if (ball_pos.x > 1260)//player1의 골대에 공이 들어간 경우
		{
			if ((300 < ball_pos.y) && (ball_pos.y < 540))
			{
				if (sc2 != 5) {
					sc2++;
					Sleep(2000);
					ball.setPosition(630, 425);
					player1.setPosition(1020, 425);
					player2.setPosition(220, 425);
					float dx = 0.0f, dy = 0.0f;
					ball.move(+1.0, 0.0);
				}
			}
			//else if (sc2 == 5)
				//break;
		}
			

		if (ball_pos.x < 0)//player2의 골대에 공이 들어간 경우
		{
			if ((300 < ball_pos.y) && (ball_pos.y < 540))
			{
				if (sc2 != 5) {
					sc1++;
					Sleep(2000);
					ball.setPosition(630, 425);
					player1.setPosition(1020, 425);
					player2.setPosition(220, 425);
					float dx = 0.0f, dy = 0.0f;
					ball.move(-1.0, 0.0);
				}
			}
			else if (sc1 == 5)
				break;
		}
	

		scoreboard = "[SCORE]                " + to_string(sc2) + "  :  " + to_string(sc1);

		sf::Font font;
		if (!font.loadFromFile("OpenSans-Bold.ttf")) {}
		sf::Text text;
		text.setFont(font);
		text.setString(scoreboard);
		text.setPosition(40, 10);
		text.setCharacterSize(70);
		text.setFillColor(sf::Color::Red);

		string keye;

		keye = "(player1) Q:ball control \n                   E,R:curve kick\n(player2) space:ball control \n                   N,M:curve kick\n";

		sf::Text key;
		key.setFont(font);
		key.setString(keye);
		key.setPosition(1000, 5);
		key.setCharacterSize(20);
		key.setFillColor(sf::Color::White);

		if (sc1 == 5)
		{
			window.clear();
			window.draw(background);
			window.draw(ball);
			window.draw(player1);
			window.draw(player2); 
			window.draw(win1);
			window.setFramerateLimit(1);
			window.draw(win1);
			window.display();
		}
		if (sc2 == 5)
		{
			window.clear();
			window.draw(background);
			window.draw(ball);
			window.draw(player1);
			window.draw(player2); 
			window.draw(win2);
			window.setFramerateLimit(1);
			window.draw(win2);
			window.display();
		}

		window.clear();
		window.draw(background);
		window.draw(ball);
		window.draw(player1); 
		window.draw(player2);
		window.draw(wall1);
		window.draw(wall2);
		window.draw(wall3);
		window.draw(wall4);
		window.draw(text);
		window.draw(key);
		window.display();
	}

	printf("\n게임이 종료되었습니다.");
	return 0;
}
