package POA.TD2;
public abstract class Pieces {
    private Position position;
    private boolean isWhite;

    public Pieces(Position position, boolean isWhite){
        this.position = position;
        this.isWhite = isWhite;
    }

    public Position getPosition(){
        return this.position;
    }

    public boolean isWhite(){
        return this.isWhite;
    }

    public abstract boolean isMoveValid(Move move);

    public abstract String toString();

}