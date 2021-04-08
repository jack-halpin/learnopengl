"""
This script is used to generate a new tutorial project based off of an old one.
It copies and renames the source file and shaders into a new folder from old project
and adds the instructions to the CMakeLists.txt to generate the project.

New project name should be in the form "Project_Title"
"""
import sys
import os
import shutil

if __name__ == "__main__":
    # Check that we have enough arguments
    if len(sys.argv) != 3:
        sys.exit(-1)

    print(sys.argv)
    template_project = sys.argv[1]
    template_project_dir = f"src/{template_project}"

    new_project = sys.argv[2]
    new_project_dir = f"src/{new_project}"
    print(template_project_dir)
    if not os.path.exists(template_project_dir):
        print(f"{sys.argv[0]} is not a valid path.")
        sys.exit(-1)

    # Create new folder for new project name
    if os.path.exists(new_project_dir):
        print(f"{new_project_dir} already exists. Deleting it...")
        shutil.rmtree(new_project_dir, True)
    
    os.mkdir(new_project_dir)

    cpp_file_name = ""

    for src_file in os.listdir(template_project_dir):
        src_path = os.path.join(template_project_dir, src_file)

        new_filename = src_file.replace(template_project.lower(), new_project.lower())
        dst_path = os.path.join(new_project_dir, new_filename)
        shutil.copyfile(src_path, dst_path)
        if dst_path[-4:] == ".cpp":
            cpp_file_name = dst_path

    # # Update the CMake file

    # offset = 0
    # set_offset = 0
    # add_offset = 0
    # with open("CMakeLists.txt", "r+", newline="\n") as c_file:
    #     line = c_file.readline()
    #     while line:
    #         offset += len(line.encode())
    #         find_set_str = (template_project + " ").upper()
    #         if line.find(find_set_str) > 0:
    #             print("Set offset has been found")
    #             set_offset = offset

           
    #         line_add_str = f"target_link_libraries({template_project.lower()} "
    #         if line.find(line_add_str) >= 0:
    #             print("add offset has been found")
    #             add_offset = c_file.tell()

    #         line = c_file.readline()


    #     c_file.seek(add_offset)

    # if set_offset > 0:
    #     set_string = f"set ({new_project.upper()} src/{new_project}/{new_project.lower()}.cpp src/glad.cpp)\n"
    #     with open("CMakeLists.txt", "rb+") as c_file:
    #         c_file.seek(set_offset)
    #         rest_of_file = c_file.read()
    #         c_file.seek(set_offset)

    #         file_as_string = rest_of_file.decode()
    #         line_replace_len = file_as_string.find("\n")

    #         c_file.write(set_string.encode("utf8"))
    #         c_file.seek(set_offset + len(set_string))
    #         c_file.write(rest_of_file)

    #         if add_offset:
    #             add_offset += len(set_string)
    
    # if add_offset > 0:
    #     add_string = f"\nadd_executable({new_project.lower()} \"${{{new_project.upper()}}}\")\ntarget_link_libraries({new_project.lower()} \"${{GLFW_LIB}}\")\n"
    #     with open("CMakeLists.txt", "rb+") as c_file:
    #         c_file.seek(add_offset)
    #         rest_of_file = c_file.read()
    #         c_file.seek(add_offset)

    #         file_as_string = rest_of_file.decode()
    #         line_replace_len = file_as_string.find("\n")

    #         c_file.write(add_string.encode("utf8"))
    #         c_file.seek(add_offset + len(add_string))
    #         c_file.write(rest_of_file)

            
                

