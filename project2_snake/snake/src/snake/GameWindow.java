package snake;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
 
public class GameWindow {
	public static final int WINDOW_WIDTH = 250;
	public static final int WINDOW_HEIGHT = 350;
	private JFrame mainFrame = new JFrame();
	private JLabel endGameLabel = new JLabel();
	private SnakeBody snake = new SnakeBody();
	private GameField snakeField; 
	private ScorePanel scorePanel = new ScorePanel();
	private Food food = new Food();
	private boolean allowToRestartTheGame = false;
	private boolean allowToMoveSnake = true;
 
	public void setUpGame() {
		int timeBetweenMoves = 180;					//snake speed
		int scoreToChangeSpeedLevel = 100;
 
		setUpGui();
		food.generateFood(snake.getCellList());		//place food on the game field
		while(true) {
			if (!allowToMoveSnake) {				//if snake dead, wait for new game
				continue;
			}
			snakeField.repaint();
			try {
				Thread.sleep(timeBetweenMoves);
			} catch(Exception ex) {
				ex.printStackTrace();
			}
			snake.move();
			checkIfSnakeGotFood();
			if((scorePanel.getScore()) == scoreToChangeSpeedLevel) {
				timeBetweenMoves -= 20;
				scorePanel.incLevel(1);
				scoreToChangeSpeedLevel += 100;
			}
			if(snakeCollapsed()) { 
				endGameLabel.setText("You have lost");
				allowToRestartTheGame = true;
				allowToMoveSnake = false; 
			}
		}
	}
 
	public void checkIfSnakeGotFood() {
		ArrayList<SnakeCell> cellList = snake.getCellList();
		SnakeCell cell = cellList.get(cellList.size() - 1);
		if (food.equals(cell)) {
			food.generateFood(snake.getCellList());
			cell.setSize(cell.getSize() + 2);
			cell.setX(cell.getX() - 1);
			cell.setY(cell.getY() - 1);
			scorePanel.incScore(10);
		}
	}
 
	public boolean snakeCollapsed() {
		ArrayList<SnakeCell> cellList = snake.getCellList();
		SnakeCell cell = cellList.get(cellList.size() - 1);
		Iterator itr = cellList.iterator();
		while(itr.hasNext()){
			if(itr.next().equals(cell) && itr.hasNext()) {
				return true;
			}
		}
		return false;
	}
 
	public void setUpGui() {
		snakeField = new GameField(snake.getCellList(), food, snake);
		snakeField.addKeyListener(new SnakeKeyListener());
		snakeField.add(endGameLabel);
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.setResizable(false);
		mainFrame.getContentPane().add(BorderLayout.CENTER, snakeField);
		mainFrame.getContentPane().add(BorderLayout.EAST, scorePanel);
		mainFrame.pack();
		mainFrame.setVisible(true);
	}
 
	public void restartGame() {
		snake.reloadSnake();
		scorePanel.reloadPanel();
		scorePanel.repaint();
		endGameLabel.setText("");
		allowToMoveSnake = true;
	}
 
	public class SnakeKeyListener implements KeyListener {
		public void keyPressed(KeyEvent e) {
			snake.setSnakeDirection(e.getKeyCode());
			if (e.getKeyCode() == 89 && allowToRestartTheGame) {
				allowToRestartTheGame = false;
				restartGame();
			}
			System.out.println(e.getKeyCode());
		}
		public void keyReleased(KeyEvent e) { }
		public void keyTyped(KeyEvent e) { }
	}
}