def mainstrlen(str):
	return len(str)

def mainsubstr(str, sub):
	if (sub in str):
		i = str.find(sub)
		i = str[i:]
		return i
	else:
		return ""