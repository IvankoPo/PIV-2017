from lib import mainstrlen, mainsubstr
def func(funca, funcy):
	
	funcb = funca*(funca+funcy)-1
	return funcb


mainy = 3

mainx = func(mainy, 4)
print(mainx)
mainx = mainstrlen("hello")
print(mainx)
mainx = mainx*mainstrlen("main")
print(mainx)
mains = mainsubstr("main program", 887)
print(mains)
mainstr = "in"
mains = mainsubstr("in main", mainstr)
print(mains)

