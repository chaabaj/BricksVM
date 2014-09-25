from string import Template
import os, sys
import argparse

device_src_template_file = 'tools/device_generator/templates/device_source.tpl'
device_header_template_file = 'tools/device_generator/templates/device_header.tpl'
device_cmakelist_template_file = 'tools/device_generator/templates/CMakeLists.tpl'
device_dir = 'device'

def create_project_directories(name):

    os.mkdir(os.path.join("device", name), 755 )
    os.mkdir(os.path.join("device", name, 'src'), 755)
    os.mkdir(os.path.join("device", name, 'include'), 755)
    os.mkdir(os.path.join("device", name, 'src', name), 755)
    os.mkdir(os.path.join("device", name, 'include', name), 755)

def write_template_file(tpl_file, dest, name):
    tpl_content = ''
    generated_content = ''
    
    with open(tpl_file, 'r') as file:
        tpl_content += file.read()
    generated_content = Template(tpl_content).substitute(name = name, upper_name = name.upper())
    with open(dest, 'w') as file:
        file.write(generated_content)

def generate_project(project_name):

    device_src_dest = os.path.join(device_dir, project_name, 'src', project_name,
                                                project_name + '.cpp')
    device_header_dest = os.path.join(device_dir, project_name, 'include',
                                                  project_name, project_name + '.hpp')
    device_cmakelist_dest = os.path.join(device_dir, project_name, 'CMakeLists.txt')

    create_project_directories(project_name)
    write_template_file(device_src_template_file, device_src_dest, project_name)
    write_template_file(device_header_template_file, device_header_dest, project_name)
    write_template_file(device_cmakelist_template_file, device_cmakelist_dest, project_name)

parser = argparse.ArgumentParser(description='Generate device project')

parser.add_argument('project_name', metavar='PROJECT_NAME', help='The project name to generate')

args = parser.parse_args()

generate_project(args.project_name)

