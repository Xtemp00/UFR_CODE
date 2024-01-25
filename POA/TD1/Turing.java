// Machine de turing

class Tape {
    private int taille;
    private boolean [] tab;
    private int head;
    Tape() {
        taille = 1000;
        tab = new boolean[taille];
        head = 0;
    }

    Tape(int taille) {
        this.taille = taille;
        tab = new boolean[taille];
        head = 0;
    }
    public void goRight(){
        if (this.head+1 < 1000){
            this.head++;
        }
    }

    public void goLeft(){
        if (this.head-1 >= 0){
            this.head--;
        }
    }

    public void write(){
        this.tab[this.head] = true;

    }

    public boolean read(){
        return this.tab[this.head];
    }

    public void erase(){
        this.tab[this.head] = false;
    }

    public String toString(){
        for (int i = 0; i < this.taille; i++){
            if(i == this.head){
                System.out.print("[");
                System.out.print("1");
                System.out.print("]");
            }
            else if (this.tab[i] == true){
                System.out.print("1");
            }
            else{
                System.out.print("_");
            }
        }
        return "";
    }


}

class TuringMachine {
    public Tape tape;
    private int state = 1;

    TuringMachine(Tape tape) {
        this.tape = tape;
    }

    public int getState() {
        return state;
    }

    public void setState(int state) {
        this.state = state;
    }

    //retourne la chaine decrivant sont ruban
    public String toString(){
        return this.tape.toString();
    }
}

class Instruction {
    private int state;
    private boolean r;
    private boolean w;
    private int e;
    private int l;

    Instruction(int state, boolean r, boolean w, int e, int l){
        this.state = state;
        this.r = r;
        this.w = w;
        this.e = e;
        this.l = l;
    }

    public int getState(){
        return this.state;
    }

    public boolean getR(){
        return this.r;
    }

    public boolean getW(){
        return this.w;
    }

    public int getE(){
        return this.e;
    }

    public int getL(){
        return this.l;
    }

    public String toString(){
        return "state : " + this.state + " r : " + this.r + " w : " + this.w + " e : " + this.e + " l : " + this.l;
    }
}

class Program {
    private Instruction[] instructions;
    private int size;

    Program(){
        this.instructions = new Instruction[100];
        this.size = 0;
    }

    public void addInstruction(Instruction instruction){
        this.instructions[this.size] = instruction;
        this.size++;
    }

    public Instruction getInstruction(int state){
        for (int i = 0; i < this.size; i++){
            if (this.instructions[i].getState() == state){
                return this.instructions[i];
            }
        }
        return null;
    }

    public String toString(){
        String str = "";
        for (int i = 0; i < this.size; i++){
            str += this.instructions[i].toString() + "\n";
        }
        return str;
    }
}


//main
class Turing {
    public static void main(String[] args) {
        //on instancie une machine de turing de 14 cases

        Tape tape = new Tape(14);
        TuringMachine machine = new TuringMachine(tape);
        // 0 0 1 1 1 0 1 1 1 1 1 0 0 0
        machine.tape.goRight();
        machine.tape.goRight();
        for (int i = 0; i < 3; i++){
            machine.tape.write();
            machine.tape.goRight();
        }
        for (int i = 0; i < 5; i++){
            machine.tape.goRight();
            machine.tape.write();
        }
        for (int i = 0; i < 3; i++){
            machine.tape.goLeft();
        }
        machine.toString();

        //on instancie un programme
        Program program = new Program();
        program.addInstruction(new Instruction(1, true, true, 2, 0));
        program.addInstruction(new Instruction(2, true, true, 3, 0));
        program.addInstruction(new Instruction(3, true, true, 4, 0));
        program.addInstruction(new Instruction(4, true, true, 5, 0));
        program.addInstruction(new Instruction(5, true, true, 6, 0));
        program.addInstruction(new Instruction(6, true, true, 7, 0));
        program.addInstruction(new Instruction(7, true, true, 8, 0));

        //on lance la machine de turing
        while (machine.getState() != 0){
            Instruction instruction = program.getInstruction(machine.getState());
            if (instruction.getR() == true){
                machine.tape.goRight();
            }
            if (instruction.getW() == true){
                machine.tape.write();
            }
            if (instruction.getE() == 0){
                machine.tape.erase();
            }
            if (instruction.getL() == 0){
                machine.tape.goLeft();
            }
            machine.setState(instruction.getState());
            System.out.println(machine.toString());
        }


    }
}
