package POA.TD2;
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