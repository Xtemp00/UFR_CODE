public abstract class Piece{
    private Position
    private boolean isWhite;
}


// Path: POA/TD2/Chess.java
// Compare this snippet from POA/TD1/Turing.java:

public class pawn extends Piece{}

public class rook extends Piece{}

public class knight extends Piece{}

public class bishop extends Piece{}

public class queen extends Piece{

}

public class king extends Piece{
}

public class Position {
    private int x;
    private int y;

    Position(int x, int y){
        this.x = x;
        this.y = y;
    }

    public int getX(){
        return this.x;
    }

    public int getY(){
        return this.y;
    }

    public boolean isValid(){
        return (this.x >= 0 && this.x < 8 && this.y >= 0 && this.y < 8);
    }
}

public class Move {
    private Position start;
    private Position end;

    Move(Position start, Position end){
        this.start = start;
        this.end = end;
    }

    public Position getStart(){
        return this.start;
    }

    public Position getEnd(){
        return this.end;
    }

    //on veut verifier si le mouvement est horizontal, vertical ou diagonal
    public boolean isHorizontal(){
        return (this.start.getY() == this.end.getY());
    }

    public boolean isVertical(){
        return (this.start.getX() == this.end.getX());
    }

    public boolean isDiagonal(){
        return (Math.abs(this.start.getX() - this.end.getX()) == Math.abs(this.start.getY() - this.end.getY()));
    }

    public boolean isValid(){
        return (this.start.isValid() && this.end.isValid());
    }

    public String toString(){
        return "Start: " + this.start.getX() + " " + this.start.getY() + " End: " + this.end.getX() + " " + this.end.getY();
    }

}

public class Board {
    private Piece[][] board;

    Board(){
        this.board = new Piece[8][8];
    }

    public void setPiece(Piece piece, Position position){
        this.board[position.getX()][position.getY()] = piece;
    }

    public Piece getPiece(Position position){
        return this.board[position.getX()][position.getY()];
    }

    public void move(Move move){
        if (move.isValid()){
            if (this.getPiece(move.getStart()) != null){
                this.setPiece(this.getPiece(move.getStart()), move.getEnd());
                this.setPiece(null, move.getStart());
            }
        }
    }

    public String toString(){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if (this.board[i][j] != null){
                    System.out.print(this.board[i][j].toString());
                }
                else{
                    System.out.print(" ");
                }
            }
            System.out.println();
        }
        return "";
    }
}

public class Game {

}

public static void main(String[] args) {
    /*Board board = new Board();
    Position position = new Position(0, 0);
    Position position2 = new Position(1, 0);
    Piece piece = new pawn();
    board.setPiece(piece, position);
    Move move = new Move(position, position2);
    board.move(move);
    System.out.println(board.toString());*/
}