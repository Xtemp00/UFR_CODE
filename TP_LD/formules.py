class Symbol:
    def __init__(self,arity,name):
        self.arity=arity
        self.name=name

    @classmethod
    def OR(cls):
        return Symbol(2,"OR")

    @classmethod
    def AND(cls):
        return Symbol(2,"AND")

    @classmethod
    def IMP(cls):
        return Symbol(2,"IMP")

    @classmethod
    def EQU(cls):
        return Symbol(2,"EQU")

    @classmethod
    def T(cls):
        return Symbol(0,"TRUE")

    @classmethod
    def F(cls):
        return Symbol(0,"FALSE")

    @classmethod
    def NOT(cls):
        return Symbol(1,"NOT")

    @classmethod
    def VAR(cls,i):
        return Symbol(0,"X"+str(i)) 

##############################        
class Node:
    def __init__(self,S):
        self.left=None #not used if TRUE/FALSE
        self.right=None #not used if unary
        self.value=S

    def __str__(self):
        if self==None :
            print("formule vide")
        else :
            if type(self.value) != Symbol:
                print("erreur 0")
            if self.value.arity == 0:
                resultat= self.value.name
            if self.value.arity == 1:
                resultat = self.value.name+"("+str(self.left)+")"
            if self.value.arity == 2:
                resultat = self.value.name+"("+str(self.left)+","+ str(self.right)+")"
            return resultat

    @classmethod
    def __racine(cls,m): #retourne la racine de l'arbre d'une formule
                     #ecrite comme une chaine de caracteres
        if m=="":
            return None
        if m=="TRUE":
            return Node(Symbol.T()),""
        if m=="FALSE":
            return Node(Symbol.F()),""
        if m[0]=="X":
            z=1
            numvariable=""
            while z < len(m) and m[z] != ")":
                numvariable+=m[z]
                z+=1
            return Node(Symbol.VAR(int(numvariable))),""
        if m[:2]=="OR" and m[2]=="(" and m[-1]==")":
            return Node(Symbol.OR()),m[3:-1]
        if m[:3]=="AND" and m[3]=="(" and m[-1]==")":
            return Node(Symbol.AND()),m[4:-1]
        if m[:3]=="IMP" and m[3]=="(" and m[-1]==")":
            return Node(Symbol.IMP()),m[4:-1]
        if m[:3]=="EQU" and m[3]=="(" and m[-1]==")":
            return Node(Symbol.EQU()),m[4:-1]
        if m[:3]=="NOT" and m[3]=="(" and m[-1]==")":
            return Node(Symbol.NOT()),m[4:-1]
        raise Exception("La formule n'est pas valide a la racine (symbole ou parentheses)")

    @classmethod
    def __cut(cls,m): # decoupe une formule ecrite sous forme de chaine de
                  # caracteres avec ses sous arbres
        racine,newm=Node.__racine(m)
        if newm == "" : # cas TRUE/FALSE
            return racine
        #print(racine.value.name)
        if racine.value.name=="NOT":
            racine.left=Node.__cut(newm)
            return racine
        
        parenthese=[]
        somme=0
        for i in range(len(newm)):
            if newm[i]=="(" :
                somme+=1
            if newm[i]==")":
                somme-=1
            if newm[i]=="," and somme==0:
                milieu=i
        racine.left=Node.__cut(newm[:milieu])
        racine.right=Node.__cut(newm[milieu+1:])
        return racine

    @classmethod
    def fromString(cls,m):
        return Node.__cut(m)
   
