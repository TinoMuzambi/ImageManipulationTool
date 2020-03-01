# MZMTIN002 Assignment 2

This project consists of four C++ files. "volimage.cpp", "volimage.h", "main.cpp" & "main.h"

The volimage.cpp file has all the definitions of the methods ans well as the constructor and destructor for the VolImage class. The linked volimage.h header file has all the declarations of the methods as well as any necessary includes.

The main.cpp file has the main method that gets invoked at runtime. It has a header file linked to it which just pulls in the methods and attributes of the volimage header.

# RUN INSTRUCTIONS
The program is invoked from the terminal with a few options for arguments.

volimage \<imageBase> [-d i j output_file_name] [-x i output_file_name] [-g i output_file_name]

where commands between <> are mandatory and commands between [] are optional. For this program only one or zero of the optional commands can be utilised at any given invocation.

# RUN EXAMPLES

Here are examples of valid invocations of the program:

volimage MRI  
volimage brain_mri_raws/MRI  
volimage brain_mri_raws/MRI -x 10 output  
volimage brain_mri_raws/MRI -g 10 output  
volimage brain_mri_raws/MRI -d 0 10 output  
