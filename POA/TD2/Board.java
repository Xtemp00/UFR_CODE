package POA.TD2;
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
