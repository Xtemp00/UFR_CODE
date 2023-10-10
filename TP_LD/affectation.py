import copy

l =[1 ,[2 ,3] ,2]
copiedel = copy . deepcopy ( l )
l [0]=0
print ( copiedel )
l [1][0]=0
print ( copiedel )
print ( l )