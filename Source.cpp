#include "glut.h"
#include <iostream>
#include <random>
#include <conio.h>
#include <vector>

#define SCALE 25
#define W SCALE*SCALE
#define H SCALE*SCALE 
#define LENGHT 4
//Params



short lenght = 4;
bool end = false;
short count = 0;
short speed = 200;
short apples = 0;
//Functions
void display();
void reshape(int w, int h);
void DrawField(void);
void DrawSnake();
void FirstInit();
void MainInit();
void KeyEvent(unsigned char key,int x,int y);
void chek();
void start();

//snake
struct SNAKE {

	int x;
	int y;

};

std::vector<SNAKE>snake(LENGHT);

class fruits {

public: int random()
{
	int rnd;
	rnd = rand() % 1000;
	rnd *= 25;
	while (rnd > 500)
		rnd -= 500;
	if (rnd > 500)return rnd - 500;
	else return rnd;
}
public: void oneInit(int number)
{
	this->fruit[number].x = this->random();
	this->fruit[number].y = this->random();
}
public: void Init()
{
	int value = 0;
	for (int i = 0; i < 5; i++)
	{

		fruit[i].x = this->random();
		fruit[i].y = this->random();
	}
};


public: void DrawFruit()
	{
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
			for (int i = 0; i < 5; i++)
			{
				glVertex2f(fruit[i].x,fruit[i].y);
				glVertex2f(fruit[i].x-25, fruit[i].y);
				glVertex2f(fruit[i].x-25, fruit[i].y-25);
				glVertex2f(fruit[i].x, fruit[i].y-25);
			}

		glEnd();
		return;
	}
public : struct fruit {

int x;
int y;
}fruit[5];

		
};
int dir = 0;
int keydir = 0;



fruits *frut = new fruits();
//timer
void timer(int = 0)
{
	chek();

	display();
	if (end == true)
		return;
	glutTimerFunc(speed,timer, 0);
}

int main(int argc,char *argv[])
{
	
	setlocale(LC_ALL, "RUSSIAN");
	start();
	FirstInit();
	frut->Init();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Loly");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(KeyEvent);
	glutTimerFunc(speed, timer, 0);

	glutMainLoop();
	return 0;
}
//KeyBoard
void KeyEvent(unsigned  char key,int x,int y)
{
	keydir = key;
	if (key == 'w' ||  key == 'W' || key == 'Ц' || key == 'ц')			dir = 0;
	else if (key == 's' ||  key == 'S' || key == 'ы' || key == 'Ы')	dir = 1;
	else if (key == 'd' ||  key == 'D' || key == 'в' || key == 'В')	dir = 2;
	else if (key == 'a' ||  key == 'A' || key == 'ф' || key == 'Ф')	dir = 3;

	std::cout << key <<	std::endl;
	return;
}
//MainInit
void MainInit()
{
	if (dir == 0)
	{

		if (snake[0].y > SCALE*SCALE)snake[0].y = SCALE;
		int size = snake.size();
		for (int i = size-1; i > 0; i--)
		{
			snake[i].x = snake[i-1].x; snake[i].y = snake[i-1].y;
		}
		snake[0].y += SCALE;
	}
	if (dir == 1)
	{

		if (snake[0].y < 0)snake[0].y = SCALE*SCALE;
		int size = snake.size();
		for (int i = size-1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x; snake[i].y = snake[i - 1].y;
		}
		snake[0].y -= SCALE;
	}
	if (dir == 2) 
	{

		if (snake[0].x > SCALE*SCALE)snake[0].x = SCALE;
		int size = snake.size();
		for (int i = size-1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x; snake[i].y = snake[i - 1].y;
		}
		snake[0].x += SCALE;
	}
	if (dir == 3)
	{
		

		if (snake[0].x < 0)snake[0].x = SCALE*SCALE;
		int size = snake.size();
		for (int i = size-1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x; snake[i].y = snake[i - 1].y;
		}
		snake[0].x -= SCALE;
	}
}



//FirstInit
void  FirstInit()
{
	
	snake[0].x = SCALE*4;
	snake[0].y = SCALE*4;
	int size = snake.size();
	for (int i = 1; i < size; i++)
	{
		snake[i].x = snake[i - 1].x - SCALE;
		snake[i].y = snake[i - 1].y;
	}
	return ;
}
//Snake
void DrawSnake()
{
	glBegin(GL_QUADS);
	int size = snake.size();
		for (int i = 0; i < size ; i++)
		{
			glColor3f(0, 0, 1);
			if(i==0)glColor3f(1, 1, 1);
			
			glVertex2f(snake[i].x-SCALE,snake[i].y);
			glVertex2f(snake[i].x, snake[i].y);
			glVertex2f(snake[i].x, snake[i].y- SCALE);
			glVertex2f(snake[i].x - SCALE, snake[i].y - SCALE);
		}
	
	glEnd();
	return;
}

//Field
void DrawField(void)
{
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);

		for (int i = 0; i < W; i += SCALE)
		{
			glVertex2f(i,0);
			glVertex2f(i,H);
		}

		for (int i = 0; i < W; i += SCALE)
		{
			glVertex2f(0, i);
			glVertex2f(W, i);
		}
		MainInit();
	glEnd();
	return;
}
//START
void start()
{
	char choice = 0;
	std::cout << "Добро пожаловать!Познаконесь со своей новой подругой!Это змейка Loly!" << std::endl;
	std::cout << "Во время игры поменяйте раскладку на ENG!Иначе змейка Loly не будет поворачивать!" << std::endl;
	std::cout << "Выберите уровень сложности(1-легкий,2-средний,3-тяжелый)";
	std::cin >> choice;
	switch (choice)
	{
		case '1': std::cout << "Вы выбрали легкий уровень сложности!" << std::endl;
			speed = 1000;
			break;
		case '2': std::cout << "Вы выбрали средний уровень сложности!" << std::endl;
			speed = 200;
			break;
		case '3': std::cout << "Вы выбрали тяжелый уровень сложности!" << std::endl;
			speed = 100;
			break;
		default: std::cout << "Вы не выбрали уровень сложности!!По дефолту вы будете играть на супер харде!" << std::endl;
			speed = 10;
			break;
	}
	std:: cout << "Нажмите enter, чтобы поиграть!" << std::endl;
	_getch();
	end = false;
	FirstInit();
	return;
}
//chek apple
bool  chekApple(fruits *fruit)
{
	int size = snake.size();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j <size; j++)
		{
			if (fruit->fruit[i].x == snake[j].x && fruit->fruit[i].y == snake[j].y)
			{
				fruit->oneInit(i);
				SNAKE snk;
				snk.x = snake[size - 1].x - SCALE;
				snk.y = snake[size - 1].y - SCALE;
				snake.push_back(snk);
				apples++;
				return true;
			}
		}
	}
	return false;
}

//chek 
void chek()
{
	int truedir = 0;
	int size = snake.size();
	for (int i = 1; i < size; i++)
	{
		if (snake[0].x == snake[i].x)truedir++;
	}
	if (truedir == lenght) return;

	for (int i = 1; i < size; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			end = true;
			system("cls");
			std::cout << "Ваши очки = " << apples << std::endl;
			return;
		}
	}
	return;
}

//display
void display()
{
	chekApple(frut);
	if(count == 0)frut->Init();
	glClear(GL_COLOR_BUFFER_BIT);
		
		if (end == true)
		{
			std::cout << "GAME OVER" << std::endl;
			start();
			return;
			//glRasterPos2f(200,50);
			//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'G');
		}

		frut->DrawFruit();
		DrawSnake();
		DrawField();

		count++;
	
	glutSwapBuffers();
	return;
}
//Reshape
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,0,h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return;
}