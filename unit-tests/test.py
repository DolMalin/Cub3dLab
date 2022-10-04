import os
import subprocess
from re import search
import string

def	get_scene_config(scene_name: str) -> str:
	"""A function that takes a scene path and remove useless spaces, useless lines and reshape in correct order the elements.
	The goal of that function is to provide an example of what our c program must do.

	Args:
		scene_name (str): The name of a scene.

	Returns:
		str: A formatted string that is the parsed scene.
	"""
	scene_folder_path = "unit-tests/scenes/"
	scene_path = os.path.abspath(os.getcwd()) + "/" + scene_folder_path + scene_name
	with open(scene_path, 'r') as file:
		data = file.read()
	splited_data = data.split('\n')
	
	# Get the config lines and remove withespaces
	filtered_lines = []
	for line in splited_data:
		if search("N|O|S|O|E|A|W|E|F|C", line):
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


def	exec_command(command: str, scene_name: str) -> str :
	"""Execute our C command to get the output we want with the given scene

	Args:
		command (str): The name of the test program written in C we want to start
		scene_name (str): The name of the scene

	Returns:
		bool: A formatted string of what our C program outputs
	"""
	scene_folder_path = "unit-tests/scenes/"
	full_command = os.path.abspath(os.getcwd()) + "/" + command + " " + scene_folder_path + scene_name
	output = subprocess.getoutput(full_command)
	return output

def difference(string1, string2):
	string1 = string1.split()
	string2 = string2.split()

	A = set(string1)
	B = set(string2)
 
	str_diff = A.symmetric_difference(B)
	return str_diff

def	compare_scenes_config(scene_name: str) -> bool:
	""" Compare the data structure of our code with whats expected

	Args:
		scene_name (str): The name of the scene we wants to test

	Returns:
		bool: True if our code prints whats we expected
	"""
	expected = get_scene_config(scene_name)
	output = exec_command("test", scene_name)
	if output ==  expected:
		return True
	else:
		print(f"\n[Error] data structure: {scene_name}")
		print(f"Diff: {difference(output, expected)}")
		print(f"Expected: {expected}")
		print(f"Output: {output}\n")
		return False


def	test_data_structure():
	scenes = os.listdir(os.path.abspath(os.getcwd()) + "/unit-tests/scenes")
	for scene in scenes:
		if not compare_scenes_config(scene):
			return
	print("[Test OK] data structure")

if __name__ == "__main__":

	# Compile the C functions
	compile_command = "make test -C" + os.path.abspath(os.getcwd())
	os.system(compile_command)
	
	# Start the test
	test_data_structure()
