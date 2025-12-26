import os
import json
from mako.template import Template
from mako.lookup import TemplateLookup
import getopt
import sys
import json

def compile_info_collect(json_file, cwd,tool_path):
    with open(json_file, 'r') as f:
        build_cfg = json.load(f)

    data_dict = {}

    header_path_info = {}
    for header_name, header_path in  build_cfg["include_paths_list"].items():
         header_path_str = ""
         for path in header_path:
            if path[0] == ".":
                relative_header_path = os.path.relpath(os.path.join(cwd,path), start=tool_path)
            else:
                relative_header_path = os.path.relpath(path, start=tool_path)
              
            header_path_str += "-I " + relative_header_path + " " 
         header_path_info[header_name] = header_path_str

    objects_str = ""     
    source_info_list = []
    header_info_list = []
    for src_info in build_cfg["src_paths_list"]: 
        source_info_dict = {}
        source_info_dict["name"] = src_info["name"]
        source_info_dict["source_list"] = []
        for src_path in src_info["path_list"]:
            for root, dirs, files in os.walk(src_path):
                for file in files:
                    if file.endswith(".c") and file not in src_info["exclude_files"]:
                        relative_src_path = os.path.relpath(os.path.join(root, file), start=tool_path).replace("\\","/")
                        source_file_info = {"source_path":relative_src_path,"object_path":os.path.join("./build", file.replace(".c", ".o")).replace("\\","/")}
                        source_info_dict["source_list"].append(source_file_info)
                        objects_str += source_file_info["object_path"] + " "
                break
        header_info = src_info["header_list"]
        if header_info in header_info_list:
             pass
        else:
             header_info_list.append(header_info)
        source_info_dict["header_index"] = header_info_list.index(header_info)
        source_info_list.append(source_info_dict)

    header_info_str_list = []
    for header_info in header_info_list:
        header_info_str = ""
        for header_name in header_info:
              header_info_str += header_path_info[header_name] + " "
        header_info_str_list.append(header_info_str)

    data_dict["header_info_str_list"] = header_info_str_list
    data_dict["source_info_list"] = source_info_list
    data_dict["object_path_list"] = objects_str

    return data_dict

def ninja_build_gen(tool_path,data_dict):
    with open(os.path.join(tool_path,"build.ninja"), "wb") as f:
        mylookup = TemplateLookup(directories=[tool_path], output_encoding='utf-8', encoding_errors='replace')
        template = mylookup.get_template("build.ninja_demo.tmpl")
        f.write(template.render(data_dict))

if __name__ == '__main__':
    try:
	     opts, args = getopt.getopt(sys.argv[1:], "l:p:", ["json_file_path=",'tool_path='])
    except getopt.GetoptError:
	     sys.exit(1)
    json_file = ''
    tool_path = ''
    for opt, value in opts:
        if opt in ('-l', '--json_file_path'):
            json_file = value
        elif opt in ('-p', '--tool_path'):
            canif_path = value
        else:
            pass
    json_file = "./build_cfg.json"
    tool_path = "../ninja/"

    cwd = os.getcwd()
    data_dict = compile_info_collect(json_file, cwd, tool_path)
    ninja_build_gen(tool_path,data_dict)
    cmd = f'{os.path.join(tool_path, "ninja.exe")} -C "{tool_path}"'
    cmd = "..\\ninja\\ninja.exe -C ..\\ninja\\"
    os.system(cmd)
    