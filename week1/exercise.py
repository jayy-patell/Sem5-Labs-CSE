# a= int(input('Enter number:'))
# b= int(input('Enter number:'))
# c= int(input('Enter number:'))
# largest=0
# if a>b:
# 	if a>c: 
# 		largest=a  
# 	else:
# 		largest=c
# else:
# 	if b>c:
# 		largest=b
# 	else:
# 		largest=c
# print("Largest: "+largest)

arr = [1,2,3,0,-1,-2,-2]
pos=0
neg=0
for i in arr:
	if i>0:
		pos+=1
	elif i<0:
		neg+=1
print(pos)
print(neg)