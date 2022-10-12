import os
import subprocess
from re import search
import string

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

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
		return "Error: in arguments."

	# Check if the extension is .cub
	if scene_name[-4 :] != ".cub":
		return "Error: in arguments."

	# Check if there is all identifiers for textures path
	for key in ["NO", "SO", "EA", "WE"]:
		find_key = False
		for line in splited_data:
			trim_line = line.translate(str.maketrans("", "", string.whitespace))
			if search(key, trim_line):
				find_key = True
		if not find_key:
			return "Error: in configuration lines or structure of scene."

	# Check if there is all identifiers for colors
	for key in ["C", "F"]:
		find_key = False
		for line in splited_data:
			trim_line = line.translate(str.maketrans("", "", string.whitespace))
			if search(key, trim_line):
				find_key = True
		if not find_key:
			return "Error: in configuration lines or structure of scene."

	# Get the map lines and remove the empty ones
	map = []
	for line in splited_data:
		trim_line = line.translate(str.maketrans("", "", string.whitespace))
		if not search("NO|SO|EA|WE|F|C", trim_line) and line.strip():
				map.append(line)

	# Check for unvalid characters
	for line in map:
		if search("[^0|1|N|S|E|W| ]", line):
			return "Error: in map."

	#Check for starting position
	player_pos_nb = 0
	for line in map:
		if search("N|S|E|W", line):
			player_pos_nb += 1
	if player_pos_nb != 1:
		return "Error: in map."

	#Check player is in map
	for i, line in enumerate(map):
		if search("N|S|E|W", line):
			player_pos = search("N|S|E|W", line).span()[0]

			# Check if player position is not on border of map
			if player_pos + 1 >= len(line) or player_pos == 0:
				return "Error: in map."
			if i == 0 or i == len(map) - 1:
				return "Error: in map."

			# Check if there is void around player pos
			if int(len(map[i - 1])) < player_pos or int(len(map[i + 1]) < player_pos):
				return "Error: in map."

			# Check if there is space around player pos
			if map[i][player_pos - 1] == ' ' or map[i][player_pos + 1] == ' ':
				return "Error: in map."
			
			if map[i - 1][player_pos] == ' ' or map[i + 1][player_pos] == ' ':
				return "Error: in map."

	for i, line in enumerate(map):
		if search("0", line):
			player_pos = search("0", line).span()[0]

			# Check if player position is not on border of map
			if player_pos + 1 >= len(line) or player_pos == 0:
				return "Error: in map."
			if i == 0 or i == len(map) - 1:
				return "Error: in map."

			# Check if there is void around player pos
			if int(len(map[i - 1])) < player_pos or int(len(map[i + 1]) < player_pos):
				return "Error: in map."

			# Check if there is space around player pos
			if map[i][player_pos - 1] == ' ' or map[i][player_pos + 1] == ' ':
				return "Error: in map."
			
			if map[i - 1][player_pos] == ' ' or map[i + 1][player_pos] == ' ':
				return "Error: in map."
	

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
			return f"Error: in textures paths."

	# Check if there is the correct number of comas in code
	for line in idless_color_lines:
		if line.count(',') != 2:
			return "Error: in RGB color codes."

	for line in idless_color_lines:
		color_split = list(filter(None, line.split(',')))
		if len(color_split) != 3:
			return "Error: in RGB color codes."
		for color in color_split:
			if color.isdigit():
				if int(color) < 0 or int(color) > 255:
					return "Error: in RGB color codes."
			else:
				return "Error: in RGB color codes."
	
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
		print(bcolors.BOLD + bcolors.FAIL + "[Error] data structure: " + bcolors.ENDC + scene_name)
		print(bcolors.BOLD + "Diff: " + bcolors.ENDC + f"{difference(output, expected)}")
		print(bcolors.BOLD + "Expected: " + bcolors.ENDC + expected)
		print(bcolors.BOLD + "Output: " + bcolors.ENDC + output)
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
		if scene == ".DS_Store":
			continue
		if not compare_commands(scene, scene_path, test_name):
			return
	print("===================================")
	print(bcolors.BOLD + bcolors.OKGREEN + "[Test OK]" + bcolors.ENDC)
	print("===================================\n")


if __name__ == "__main__":

	scene_path = "unit-tests/scenes"

	# Command to execute
	testclean_command = "make testclean -C " + os.path.abspath(os.getcwd() + " > /dev/null")
	parsing_command = "make test_parsing -C" + os.path.abspath(os.getcwd() + " > /dev/null")
	input_command = "make test_input -C" + os.path.abspath(os.getcwd() + " > /dev/null")

	# run parsing test
	print(bcolors.BOLD + "\nPARSING" + bcolors.ENDC)
	os.system(testclean_command)
	os.system(parsing_command)
	run_test(scene_path, "parsing")

	# # run input test
	print(bcolors.BOLD + "\nINPUT" + bcolors.ENDC)
	os.system(testclean_command)
	os.system(input_command)
	run_test(scene_path, "input")

	# print("expected : " + check_input("missing_texture3.cub", "unit-tests/scenes"))
	# print("our : " + exec_command("test", "startpos_outside6.cub", "unit-tests/scenes", "input"))
