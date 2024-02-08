package POA.TD2;
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