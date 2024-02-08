// Version: 1.0
package POA.TD2;
public static void main(String[] args) {
    //on crée un exemple de jeu d'echec
    Board board = new Board();
    King king = new King(new Position(4, 4), true);
    board.setPiece(king, new Position(4, 4));
    System.out.println(board.toString());
    Move move = new Move(new Position(4, 4), new Position(4, 5));
    board.move(move);
    System.out.println(board.toString());
    Move move2 = new Move(new Position(4, 5), new Position(4, 6));
    board.move(move2);
    System.out.println(board.toString());
}