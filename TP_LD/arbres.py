from formules import*

exampleForm = Node ( Symbol . AND ()) # creation de la racine
print ( exampleForm )
exampleForm . left = Node ( Symbol . T ()) # creation du fils gauche
exampleForm . right = Node ( Symbol . NOT ()) # creation du fils droit
print ( exampleForm )
exampleForm . right . left = Node ( Symbol . VAR (0)) # dernier noeud
print ( exampleForm )

print("")
print("")
print("")


arbres = Node (Symbol.OR())
print(arbres)
arbres.left = Node(Symbol.AND())
arbres.right = Node(Symbol.NOT())
print(arbres)
arbres.left.left = Node(Symbol.T())
arbres.left.right = Node(Symbol.F())
print(arbres)
arbres.right.left = Node(Symbol.NOT())
arbres.right.left.left = Node(Symbol.VAR(1))
print(arbres)


def nbNot(formule):
    if (formule.value.arity == 1):
        return 1 + nbNot(formule.left)
    elif (formule.value.arity == 2):
        return nbNot(formule.left) + nbNot(formule.right)
    else :
        return 0

arbres = Node.fromString('OR(AND(TRUE,FALSE),NOT(NOT(X1)))')
print(nbNot(arbres))

def listeVariables(formule,tab):
    if (formule.value.arity == 0 and formule.value.name != "TRUE" and formule.value.name != "FALSE"):
        tab.append(int(formule.value.name[1:]))
        return tab
    if (formule.value.arity == 1):
        listeVariables(formule.left, tab)
        return tab
    elif (formule.value.arity == 2):
        listeVariables(formule.left, tab)
        listeVariables(formule.right, tab)
        return tab

arbres = Node.fromString('OR(AND(TRUE,FALSE),NOT(NOT(X1)))')
print(listeVariables(arbres,[]))

def conjonction(formule1,formule2):
    

