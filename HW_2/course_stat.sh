#!/bin/bash

#if one or more grades were used as input
if [[ $# == 1 ]]; then

file=$1.txt

#if course_num.txt file is present in cwd
	if [[ -f $file ]]; then
	
	#creating course_num_stat new folder and removing old one if needed
	new_dir=$1"_stat"
	
		if [[ -d $new_dir ]]; then
		
			rm -rf $new_dir
			mkdir $new_dir
			
		else
		
			mkdir $new_dir
		fi
		
		num_of_lines=$(cat $file | wc -l)
		
		#scanning file line by line and extracting grades to grades.txt file
		cat $file | head -n 1 | tail -n 1 | grep -P -o "\t[0-9]+" >./$new_dir/grades.txt
		
		for (( i=2; i<=$num_of_lines; ++i )); do
		
			cat $file | head -n $i | tail -n 1 | grep -P -o "\t[0-9]+" >>./$new_dir/grades.txt
		     
		done
		
	
	
	else 
	
	echo "Course not found" 1>&2
	exit
	
	fi


else

echo "Wrong number of arguments" 1>&2 
exit

fi

#compiling calc_statistics c file
gcc -g -Wall calc_statistics.c -o prog.exe

cd ./$new_dir

#running calc_statistics executable file
../prog.exe $new_dir $num_of_lines

cat course_statistics.txt
