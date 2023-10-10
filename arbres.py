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


print(listeVariables(arbres,[]))

def conjonction(formule1, formule2):
    and_node = Node(Symbol.AND())
    and_node.left = formule1
    and_node.right = formule2
    return and_node


print(conjonction(arbres,arbres))

def evalFormuleClose(formule):
    if formule is None:
        return True
    if formule.value.name == "TRUE":
        return True
    if formule.value.name == "FALSE":
        return False
    if formule.value.name == "NOT":
        return not evalFormuleClose(formule.left)
    if formule.value.name == "AND":
        return evalFormuleClose(formule.left) and evalFormuleClose(formule.right)
    if formule.value.name == "OR":
        return evalFormuleClose(formule.left) or evalFormuleClose(formule.right)
    if formule.value.name == "VAR":
        return False




print(evalFormuleClose(arbres))




def evalFormule(formule, instanciation):
    if formule is None:
        return True
    if formule.value.name == "TRUE":
        return True
    if formule.value.name == "FALSE":
        return False
    if formule.value.name == "NOT":
        return not evalFormule(formule.left, instanciation)
    if formule.value.name == "AND":
        return evalFormule(formule.left, instanciation) and evalFormule(formule.right, instanciation)
    if formule.value.name == "OR":
        return evalFormule(formule.left, instanciation) or evalFormule(formule.right, instanciation)
    if formule.value.name == "VAR":
        return instanciation[int(formule.value.name[1:]) - 1]


"""
def tableDeVerite(formule):
    variables = listeVariables(formule, [])
    num_variables = len(variables)

    headers = [f"Var{i}" for i in range(1, num_variables + 1)]
    headers.append("Résultat")

    print(" | ".join(headers))

    for i in range(2 ** num_variables):
        instanciation = {}
        for j, var in enumerate(variables):
            instanciation[var] = bool(i & (1 << j))

        result = evalFormule(formule, instanciation)
        row = [str(int(instanciation[var])) for var in variables] + [str(int(result))]
        print(" | ".join(row))


arbres2 = Node.fromString('AND(X0,X1)')
tableDeVerite(arbres2)

arbres2 = Node.fromString('OR(NOT(X0),X1)')
tableDeVerite(arbres2)"""


arbres = Node.fromString('IMP(AND(TRUE,FALSE),OR(X0,NOT(X1)))')

def supprimeIMPracine(formule):
    if formule.value.name == "IMP":
        or_node = Node(Symbol.OR())
        or_node.left = Node(Symbol.NOT())
        or_node.left.left = formule.left
        or_node.right = formule.right
        return or_node
    return formule


print(supprimeIMPracine(arbres))
arbres = Node.fromString('AND(IMP(TRUE,FALSE),OR(X0,NOT(X1)))')

def supprimeIMP(formule):
    if formule.value.name == "IMP":
        or_node = Node(Symbol.OR())
        or_node.left = Node(Symbol.NOT())
        or_node.left.left = formule.left
        or_node.right = formule.right
        return or_node
    elif formule.value.arity == 1:
        formule.left = supprimeIMP(formule.left)
    elif formule.value.arity == 2:
        formule.left = supprimeIMP(formule.left)
        formule.right = supprimeIMP(formule.right)
    return formule


print(supprimeIMP(arbres))

arbres = Node.fromString('EQU(AND(TRUE,FALSE),OR(X0,NOT(X1)))')

def supprimeEQUracine(formule):
    if formule.value == Symbol.EQU():
        left_not = Node(Symbol.NOT(), formule.left)
        right_not = Node(Symbol.NOT(), formule.right)
        or1 = Node(Symbol.OR(), left_not, formule.right)
        or2 = Node(Symbol.OR(), right_not, formule.left)
        and_node = Node(Symbol.AND(), or1, or2)
        return and_node
    return formule





print(supprimeEQUracine(arbres))


def supprimeEQU(formule):
    if formule.value == Symbol.EQU():
        left_not = Node(Symbol.NOT(), formule.left)
        right_not = Node(Symbol.NOT(), formule.right)
        or1 = Node(Symbol.OR(), left_not, formule.right)
        or2 = Node(Symbol.OR(), right_not, formule.left)
        and_node = Node(Symbol.AND(), or1, or2)
        return and_node
    elif formule.value.arity == 1:
        formule.left = supprimeEQU(formule.left)
    elif formule.value.arity == 2:
        formule.left = supprimeEQU(formule.left)
        formule.right = supprimeEQU(formule.right)
    return formule

print(supprimeEQU(arbres))


def negationNormale(formule):
    if formule.value == Symbol.NOT():
        if formule.left.value == Symbol.NOT():
            return negationNormale(formule.left.left)
        elif formule.left.value.arity == 0:
            return formule
        elif formule.left.value.arity == 1:
            return negationNormale(formule.left.left)
        elif formule.left.value.arity == 2:
            if formule.left.value == Symbol.AND():
                not_left = Node(Symbol.NOT(), formule.left.left)
                not_right = Node(Symbol.NOT(), formule.left.right)
                or_node = Node(Symbol.OR(), not_left, not_right)
                return negationNormale(or_node)
            elif formule.left.value == Symbol.OR():
                not_left = Node(Symbol.NOT(), formule.left.left)
                not_right = Node(Symbol.NOT(), formule.left.right)
                and_node = Node(Symbol.AND(), not_left, not_right)
                return negationNormale(and_node)
    elif formule.value.arity == 1:
        formule.left = negationNormale(formule.left)
    elif formule.value.arity == 2:
        formule.left = negationNormale(formule.left)
        formule.right = negationNormale(formule.right)
    return formule

print(negationNormale(arbres))

