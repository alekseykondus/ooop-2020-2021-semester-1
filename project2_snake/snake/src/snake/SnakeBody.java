package snake;

import javax.swing.*;
import java.awt.*;
import java.util.*;

public class SnakeBody {
	public static final int NUMBER_OF_CELLS = 4;
	public static final int CELL_SIZE = 10;
	private ArrayList<SnakeCell> snakeCells = new ArrayList<SnakeCell>();
	private boolean allowToChangeDirection = true;
	private int snakeDirection = 39;
	private int headCoordX;
	private int headCoordY;

	public SnakeBody() {
		for(int i = 0; i < NUMBER_OF_CELLS; i++) {
			snakeCells.add(new SnakeCell(CELL_SIZE, 10 + i*CELL_SIZE, CELL_SIZE));
			headCoordX = NUMBER_OF_CELLS*CELL_SIZE;
			headCoordY = CELL_SIZE;
		}
	}

	public ArrayList<SnakeCell> getCellList() {
		return snakeCells;
	}

	//if game restarts, set default values
	public void reloadSnake() {
		snakeCells.clear();
		for(int i = 0; i < NUMBER_OF_CELLS; i++) {
			snakeCells.add(new SnakeCell(CELL_SIZE, 10 + i*CELL_SIZE, CELL_SIZE));
			headCoordX = NUMBER_OF_CELLS*CELL_SIZE;
			headCoordY = CELL_SIZE;
		}
	}

	//(39 right) (37 left) (38 up) (40 down)
	public void setSnakeDirection(int direction) {
		if ((37 <= direction && direction <=40) && (Math.abs(snakeDirection - direction) != 2) && allowToChangeDirection)  {
			snakeDirection = direction;
			allowToChangeDirection = false;
		} 
	}

	public void move() {
		SnakeCell cell;
		cell = snakeCells.get(0);
		//if last cell of snake bigger than default size(has food in it)
		//then don't delete it(make snake bigger)
		if(cell.getSize() == CELL_SIZE) {
			snakeCells.remove(0);
		} else {
			cell.setSize(CELL_SIZE);
			cell.setX(cell.getX() + 1);
			cell.setY(cell.getY() + 1);
		}
		switch(snakeDirection){
			case 40:	headCoordY += CELL_SIZE;
						if (headCoordY > GameWindow.WINDOW_HEIGHT - CELL_SIZE) { headCoordY = 0; }
						snakeCells.add(new SnakeCell(CELL_SIZE, headCoordX, headCoordY));
						break;
			case 38:	headCoordY -= CELL_SIZE;
						if (headCoordY < 0) { headCoordY = GameWindow.WINDOW_HEIGHT - CELL_SIZE; }
						snakeCells.add(new SnakeCell(CELL_SIZE, headCoordX, headCoordY));
						break;
			case 37:	headCoordX -= CELL_SIZE;
						if (headCoordX < 0) { headCoordX = GameWindow.WINDOW_WIDTH - CELL_SIZE; }
						snakeCells.add(new SnakeCell(CELL_SIZE, headCoordX, headCoordY));
						break;
			case 39:	headCoordX += CELL_SIZE;
						if (headCoordX > GameWindow.WINDOW_WIDTH - CELL_SIZE) { headCoordX = 0; }
						snakeCells.add(new SnakeCell(CELL_SIZE, headCoordX, headCoordY));
						break;
			default:	System.out.println("key code error");
						break;
		}
		allowToChangeDirection = true;
	}
}