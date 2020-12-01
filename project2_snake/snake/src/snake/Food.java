package snake;

import java.util.*;

public class Food {
	private int size = SnakeBody.CELL_SIZE;
	private int x;
	private int y;
 
	public int getX() {
		return x;
	}
 
	public int getY() {
		return y;
	}
 
	public int getSize() {
		return size;
	}
 
	public void generateFood(ArrayList<SnakeCell> snakeList) {
		boolean loop = true;
		while(loop) {
			x = (int)(Math.random() * GameWindow.WINDOW_WIDTH) / SnakeBody.CELL_SIZE * SnakeBody.CELL_SIZE;
			y = (int)(Math.random() * GameWindow.WINDOW_HEIGHT) / SnakeBody.CELL_SIZE * SnakeBody.CELL_SIZE;
			loop = false;
			System.out.println("x = " + x + "y = " + y);
			//checks if generated food appeared inside snake body
			for(SnakeCell cell: snakeList) {
				if (this.equals(cell)) {
					loop = true;
				}
			}
		}
	}
 
	public boolean equals(Object obj) {
		SnakeCell cell = (SnakeCell) obj;
		return x == cell.getX() && y == cell.getY();
	}
 
	public int hashCode() {
		return x + y;
	}
}