def bin(n):
	if (n == 0):
		return "0"
	elif (n == 1):
		return "1"
	else:
		return bin(n // 2) + str(n % 2);

def check(s):
	if (len(s) >= 3):
		return s[:3] != '101'
	return True


with open('test.txt', 'w') as f:
	file = open("test.txt")
	lst = []
	for i in range(100000):
		s = bin(i) + "1100"
		if (check(s)):
			lst.append(s)

	print("\n".join(lst), file = f)