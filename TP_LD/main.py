

def SupDoubles(l):
    resultat = []
    for element in l :
        if element not in resultat :
          resultat.append(element)
    return resultat

print(SupDoubles([0,0,0,1,2,3,5,6,7,2,85,7,8,9]))
print(SupDoubles([1,1,1,1,1,1,1,1,1,11,1,1,11,1]))
