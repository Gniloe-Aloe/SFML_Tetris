#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <string>
//C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\pic\\block5.png


class Block {
public:
	int x;
	int y;

	sf::Sprite block_sprite;
	

};

class Form {
private:
	const int FIELD_WIDTH = 10;
	const int FIELD_HEIGHT = 20;
	const int BLOCK_SIZE = 45;
public:
	sf::RenderWindow window;
	sf::Event event;
	Block** field = nullptr;

	
	
	void set_field(const sf::Texture& block_texture) {
		//тут специально перепутаны столбцы и строки для того, чтобы к координатам массива можно было обращаться
		//в таком же порядке, как это происходит в библиотеке SFML: сначала обращение к абсциссу, а потом к ординату.
		//в двумерном динамическом массиве происходит наоборот.
		field = new Block* [FIELD_WIDTH];
		for (int w = 0; w < FIELD_WIDTH; ++w) {
			field[w] = new Block[FIELD_HEIGHT];
		}
		//задаём первоначальные параметры для блоков
		for (int w = 0; w < FIELD_WIDTH; ++w) {
			for (int h = 0; h < FIELD_HEIGHT; ++h) {	
				field[w][h].block_sprite.setTexture(block_texture);
				field[w][h].x = w;
				field[w][h].y = h;
				field[w][h].block_sprite.move(float(w * BLOCK_SIZE),float(h * BLOCK_SIZE));
			}
		}
	}

	void draw_field() {
		for (int w = 0; w < FIELD_WIDTH; ++w) {
			for (int h = 0; h < FIELD_HEIGHT; ++h) {
				window.draw((field[w][h].block_sprite));
			}
		}
	}
	
	
	void set_window() {
		window.create(sf::VideoMode(FIELD_WIDTH * BLOCK_SIZE, FIELD_HEIGHT * BLOCK_SIZE), "Tetris", sf::Style::Close);
		window.clear(sf::Color::White);
		window.setVerticalSyncEnabled(true);
	}

	~Form() {
		if (field != nullptr) {
			for (int i = 0; i < FIELD_WIDTH; ++i) {
				delete[] field[i];
			}
			delete[] field;
		}
	}
};







int main() {
	Form game;
	
	
	//
	sf::Texture block_texture;
	block_texture.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\pic\\block5.png");
	//
	game.set_window();
	game.set_field(block_texture);

	


	
	
	while (game.window.isOpen()) {
		


		

		while (game.window.pollEvent(game.event)) {
			switch (game.event.type)
			{
			case sf::Event::Closed:
				game.window.close();
				break;
			}
		}

		
		
	
		game.draw_field();
		
		game.window.display();
	}
	return 1;
}
