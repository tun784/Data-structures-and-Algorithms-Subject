import os
import re
import simple_colors as SP

SPACE = 5
# Một cái Object mang tên là Node.
class Node:
	def __init__(this, data):
		this.data = data
		this.left = None # NULL trong C/C++ là None trong Python.
		this.right = None


# Các thao tác.
# Left - Node - Right.
def LNR(node, space):
	if node is None:
		return
	
	space += SPACE
	LNR(node.left, space)
	for i in range(0, space, 1):
		print(" ",end= "")
	print("%d[id=%d]"%(node.data, id(node))) # Sử dụng print như printf.
	LNR(node.right, space) 

# Right - Node - Left.
def RNL(node, space):
	if node is None:
		return
	
	space += SPACE
	RNL(node.right, space)
	for i in range(0, space, 1):
		print(" ",end= "")
	print("%d[id=%d]"%(node.data, id(node))) # Sử dụng print như printf.
	RNL(node.left, space) 

# Node - Left - Right.
def NLR(node, space):
	if node is None:
		return
	
	space += SPACE
	for i in range(0, space, 1):
		print(" ",end= "")
	print("%d[id=%d]"%(node.data, id(node))) # Sử dụng print như printf.
	NLR(node.left, space)
	NLR(node.right, space) 

# Node - Right - Left.
def NRL(node, space):
	if node is None:
		return
	
	space += SPACE
	for i in range(0, space, 1):
		print(" ",end= "")
	print("%d[id=%d]"%(node.data, id(node))) # Sử dụng print như printf.
	NRL(node.right, space)
	NRL(node.left, space) 

# Left - Right - Node.
def LRN(node, space):
	if node is None:
		return
	
	space += SPACE
	LRN(node.left, space)
	LRN(node.right, space)
	for i in range(0, space, 1):
		print(" ",end= "")
	print("%d[id=%d]"%(node.data, id(node))) # Sử dụng print như printf.

# Right - Left - Node.
def RLN(node, space):
	if node is None:
		return
	
	space += SPACE
	RLN(node.left, space)
	RLN(node.right, space)
	for i in range(0, space, 1):
		print(" ",end= "")
	print("%d[id=%d]"%(node.data, id(node))) # Sử dụng print như printf.

# Hàm tạo và thêm node.
def insert(node, data):
	if node is None:
		return Node(data)
	elif node.data > data:
		node.left = insert(node.left, data)
	elif node.data < data:
		node.right = insert(node.right, data)
	else:
		print(SP.red("---> Trùng phần tử, không thêm vào được."))
	
	return node

# Hàm tìm node nhỏ nhất.
def min_node(root):
	current = root
	while(current.left is not None):
		current = current.left  # Tương tự như current = current->left trong C.
	return current

# Hàm xoá node.
def deleteNode(root, data):
	# Base case.
	if root is None:
		return

	if root.data > data:
		root.left = deleteNode(root.left, data)
	elif root.data < data:
		root.right = deleteNode(root.right, data)
	else:
		# Trường hợp node có một con hoặc 0 con.
		if root.left is None:
			temp = root.right
			root = None
			return temp
		elif root.right is None:
			temp = root.left
			root = None
			return temp

		"""
		Trường hợp cuối cùng là node cần xoá có 2 con:
			+ Tìm node thế mạng.
			+ Gán node thế mạng vào node cần xoá.
			+ Xoá node thế mạng.
		"""
		temp = min_node(root.right)
		root.data = temp.data
		
		root.right = deleteNode(root.right, temp.data)
	
	return root

def search_x(root, data):
	current = root
	while current is not None and current.data != data:
		if current.data > data:
			current = current.left
		elif current.data < data:
			current = current.right

	return current


# Các hàm hỗ trợ thực hiện các chức năng.
def menu():
	print(SP.cyan("\t\t\t===Các thao tác trên Binary Search Tree===", 'bold'))
	print(SP.magenta("\t0. Thoát chương trình."))
	print(SP.magenta("\t1. Cung cấp dữ liệu cho cây."))
	print(SP.magenta("\t2. Duyệt cây."))
	print(SP.magenta("\t3. Tìm phần tử x trên cây."))
	print(SP.magenta("\t4. Xoá phần tử x trên cây."))
	print(SP.cyan("\t\t\t==========================================", 'bold'))

def file_input():
	global root # Để thay đổi dữ liệu của biến toàn cục.
	with open("D:\Visual_Studio\Data_structure_and_Algorithms\DoAnCuoiKy\Data.txt", "rt") as f:
		while True:
			line = f.readline()
			if not line:
				break
			line = line.strip() # Xoá tất cả khoảng trắng dư thừa trước khi gặp dữ liệu trong line và \n cuối line.
			line = re.split(' ', line) # Tách line ra.

			for i in line:
				root = insert(root, int(i))
		f.close()
	
	if root is not None:
		return True
	return False

def execution():
	menu()
	global root
	i = input("Hãy chọn một thao tác mà bạn muốn: ").strip()

	os.system("cls")
	match i:
		case '0':
			return False
		case '1':
			print("Bạn muốn cung cấp dữ liệu theo hình thức nào: ")
			print(SP.magenta("\tE- Quay lại."))
			print(SP.magenta("\tH- Nhập tay."))
			print(SP.magenta("\tF- Nhập vào từ file data.txt."))
			k = str(input("-> ")).strip().upper()

			match k:
				case 'E':
					return True
				case 'H':
					data = int(input("Dữ liệu bạn muốn thêm vào là: "))
					root = insert(root, data)
				case 'F':
					check = file_input()
					if check is not None:
						print(SP.green("---> Nhập thành công."))
					else:
						print(SP.red("---> Nhập thất bại, vui lòng kiểm tra lại file."))
				case _:
					print("Yêu cầu không hợp lệ, mặc định nhập vào bằng file")
					check = file_input()
					if check is not False:
						print(SP.green("---> Nhập thành công."))
					else:
						print(SP.red("---> Nhập thất bại, vui lòng kiểm tra lại file."))
		case '2':
			print("Bạn muốn duyệt cây theo hình thức nào: ")
			print(SP.magenta("\t+1. Left - Node - Right."))
			print(SP.magenta("\t+2. Right - Node - Left."))
			print(SP.magenta("\t+3. Node - Left - Right."))
			print(SP.magenta("\t+4. Node - Right - Left."))
			print(SP.magenta("\t+5. Left - Right - Node."))
			print(SP.magenta("\t+6. Right - Left - Node."))

			k = str(input("-> "))
			if root is None:
				print(SP.red("---> Cây hiện không có dữ liệu."))
			match k:
				case '1':
					LNR(root, 0)
				case '2':
					RNL(root, 0)
				case '3':
					NLR(root, 0)
				case '4':
					NRL(root, 0)
				case '5':
					LRN(root, 0)
				case '6':
					RLN(root, 0)
				case _:
					print(SP.red("---> Hinh thuc nhap nay khong ton tai."))
		case '3':
			if root is None:
				print(SP.red("---> Cây hiện không có dữ liệu để tìm."))
			else:
				data = int(input("Phần tử bạn muốn tìm là: "))

				check = search_x(root, data)
				if check is not None:
					print(SP.green("---> Tìm được phần tử %d trên cây."%(check.data)))
				else:
					print(SP.red("---> Không tìm thấy phần tử %d trên cây."%data))
		case '4':
			if root is None:
				print(SP.red("---> Cây hiện không có dữ liệu để xoá."))
			else:
				"""
				Khi xác nhận được là cây có dữ liệu thì:
				Bước 1: Ta kiểm tra coi phần tử cần xoá có tồn tại không, nếu không thì không thực hiện hàm xoá.
				Bước 2: Nếu có thì ta sang bước 2, thực hiện hàm xoá.
				"""
				data = int(input("Phần tử bạn muốn xoá là: "))
				check = search_x(root, data)
				if check is None:
					print(SP.red("---> Phần tử %d không tồn tại."%data))
				else:
					root = deleteNode(root, data)
					
					check = search_x(root, data)
					if check is not None:
						print(SP.red("---> Xoá không thành công phần tử %d vẫn còn tồn tại trên cây."%check.data))
					else:
						print(SP.green("---> Xoá thành công phần tử %d ra khỏi cây."%data))
		case _:
			print(SP.red("Chức năng " + str(i) + " không tồn tại"))

	return True


# Main
root = None
process = True
while process:
	process = execution()

print(SP.yellow("--> Thoát chương trình thành công.", 'bold'))
os.system("pause")
os.system("cls")
