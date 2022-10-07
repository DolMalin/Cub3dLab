import os
import subprocess
from re import search
import string

## EXPECTED FUNCTIONS
def	parsing(scene_name: str, scene_path: str) -> str:
	"""A function that takes a scene path and remove useless spaces, useless lines and reshape in correct order the elements.
	The goal of that function is to provide an example of what our c program must do.

	Args:
		scene_name (str): The name of a scene.

	Returns:
		str: A formatted string that is the parsed scene.
	"""
	scene = os.path.abspath(os.getcwd()) + "/" + scene_path + "/" + "valid" + "/" + scene_name
	with open(scene, 'r') as file:
		data = file.read()
	splited_data = data.split('\n')
	
	# Get the config lines and remove withespaces
	filtered_lines = []
	for line in splited_data:
		trim_line = line.translate(str.maketrans("", "", string.whitespace))
		if search("NO|SO|EA|WE|F|C", trim_line):
			filtered_lines.append(line.translate(str.maketrans("", "", string.whitespace)))

	# Remove the ID at the start of the liens
	idless_lines = []
	for line in filtered_lines:
		if search("NO|SO|EA|WE", line[:2]):
			idless_lines.append(line[2:])
		if search("F|C", line[:1]):
			idless_lines.append(line[1:])

	# Join the lines
	joined_lines = "\n".join(idless_lines)
	return joined_lines



def	check_input(scene_name: str, scene_path: str) -> str:
	scene = os.path.abspath(os.getcwd()) + "/" + scene_path + "/" + "unvalid" + "/" + scene_name
	with open(scene, 'r') as file:
		data = file.read()
	splited_data = data.split('\n')

	# Check if the .cub file exists
	if not os.path.exists(os.getcwd() + "/" + scene_path + "/" + "unvalid" + "/" + scene_name):
		return "Can't access scene file"

	# Check if the extension is .cub
	if scene_name[-4 :] != ".cub":
		return "Not a .cub scene file"
	# Get the map lines and remove the empty ones
	map = []
	for line in splited_data:
		trim_line = line.translate(str.maketrans("", "", string.whitespace))
		if not search("NO|SO|EA|WE|F|C", trim_line) and line.strip():
				map.append(line)

	# Check for unvalid characters
	for line in map:
		if search("[^0|1|N|S|E|W| ]", line):
			return "Invalid characters in the map\nMap is incorrect"

	# Get the config lines and remove withespaces
	filtered_lines = []
	for line in splited_data:
		trim_line = line.translate(str.maketrans("", "", string.whitespace))
		if search("NO|SO|EA|WE|F|C", trim_line):
			filtered_lines.append(line.translate(str.maketrans("", "", string.whitespace)))

	# Remove the ID at the start of the textures lines
	idless_textures_lines = []
	for line in filtered_lines:
		if search("NO|SO|EA|WE", line[:2]):
			idless_textures_lines.append(line[2:])


	# Remove the ID at the start of the textures lines
	idless_color_lines = []	
	for line in filtered_lines:
		if search("F|C", line[:1]):
			idless_color_lines.append(line[1:])
	
	# Check if the textures path are valid
	for line in idless_textures_lines:
		if not os.path.exists(os.getcwd() + "/" + line):
			return f"Can't access the {line} texture file"

	# Check if there is the correct number of comas in code
	for line in idless_color_lines:
		if line.count(',') != 2:
			return "Error: check comas in color code"
	
	return "Test OK"

def	exec_command(command: str, scene_name: str, scene_path: str, test_name:str) -> str :
	"""Execute our C command to get the output we want with the given scene

	Args:
		command (str): The name of the test program written in C we want to start
		scene_name (str): The name of the scene

	Returns:
		bool: A formatted string of what our C program outputs
	"""
	folder = "valid" if test_name == "parsing" else "unvalid"
	full_command = os.path.abspath(os.getcwd()) + "/" + command + " " + scene_path + "/" + folder + "/" + scene_name
	output = subprocess.getoutput(full_command)
	
	return output


def difference(string1: str, string2: str) -> set:
	""" Print the differences between two strings as a set of differences.

	Args:
		string1 (str): The first string to compare
		string2 (str): The second string to compare

	Returns:
		set: The differences between the two strings
	"""
	string1 = string1.split()
	string2 = string2.split()

	A = set(string1)
	B = set(string2)
 
	str_diff = A.symmetric_difference(B)
	return str_diff

def	compare_commands(scene_name: str, scene_path: str, test_name: str) -> bool:
	""" Compare the data structure of our code with whats expected

	Args:
		scene_name (str): The name of the scene we wants to test

	Returns:
		bool: True if our code prints whats we expected
	"""
	if test_name == "parsing":
		expected = parsing(scene_name, scene_path)
	else:
		expected = check_input(scene_name, scene_path)
	
	output = exec_command("test", scene_name, scene_path, test_name)
	if output ==  expected:
		return True
	else:
		print("===================================")
		print(f"[Error] data structure: {scene_name}")
		print(f"Diff: {difference(output, expected)}")
		print(f"Expected: {expected}")
		print(f"Output: {output}")
		print("===================================\n")
		return False


def	run_test(scene_path: str, test_name: str):
	"""Run the start of comparing expected outputs with actual outputs for every scenes in the folder

	Args:
		scenes_path (str): The path of where the scenes are stored.
	"""
	folder = "valid" if test_name == "parsing" else "unvalid"
	scenes = os.listdir(os.path.abspath(os.getcwd()) + "/"  + scene_path + "/" + folder + "/")
	for scene in scenes:
		if not compare_commands(scene, scene_path, test_name):
			return
	print("===================================")
	print(f"[Test OK]")
	print("===================================\n")


if __name__ == "__main__":

	scene_path = "unit-tests/scenes"

	# Command to execute
	testclean_command = "make testclean -C " + os.path.abspath(os.getcwd() + " > /dev/null")
	parsing_command = "make test_parsing -C" + os.path.abspath(os.getcwd() + " > /dev/null")
	input_command = "make test_input -C" + os.path.abspath(os.getcwd() + " > /dev/null")

	# run parsing test
	print("\nPARSING")
	os.system(testclean_command)
	os.system(parsing_command)
	run_test(scene_path, "parsing")

	# # run input test
	print("\nINPUT")
	os.system(testclean_command)
	os.system(input_command)
	run_test(scene_path, "input")

	# print("expected : " + check_input("wrong_textures_path.cub", "unit-tests/scenes"))
	# print("our : " + exec_command("test", "wrong_textures_path.cub", "unit-tests/scenes", "input"))