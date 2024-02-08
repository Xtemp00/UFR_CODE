//on importe les autre fichiers
package POA.TD2;


public class King extends Pieces{
    //on veut crée la piece roi pour un jeu d'echec
    public King(Position position, boolean isWhite){
        super(position, isWhite);
    }

    public boolean isMoveValid(Move move){
        return (move.getStart().getX() == move.getEnd().getX() && Math.abs(move.getStart().getY() - move.getEnd().getY()) == 1) || (move.getStart().getY() == move.getEnd().getY() && Math.abs(move.getStart().getX() - move.getEnd().getX()) == 1) || (Math.abs(move.getStart().getX() - move.getEnd().getX()) == 1 && Math.abs(move.getStart().getY() - move.getEnd().getY()) == 1);
    }

    public String toString(){
        return "K";
    }


}