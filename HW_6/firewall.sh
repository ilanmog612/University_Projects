#!/bin/bash


#packets var's
rules="$1"
packets=""
output=""

#going line by line through the packets file
#converting uppercase to lower case and deleting redundent commas, tabs and comments 
while read -r parsed_packet_line;
do
	parsed_packet_line=`echo "$parsed_packet_line" |sed 's/#.*//g'|sed '/^$/d'|sed 's/ //g'|tr -d '\t'|tr -s ','`
	if [[ -n $parsed_packet_line ]]
	then
		if [[ $parsed_packet_line = ,* ]]
		then
			parsed_packet_line=`echo "$parsed_packet_line"|sed 's/.//'`
		fi
		if [[ $parsed_packet_line = *, ]]
		then
			parsed_packet_line=`echo "$parsed_packet_line"|sed 's/.$//'`
		fi
		packets+=`echo "$parsed_packet_line"`
		packets+=$'\n'
	fi
	
done < /dev/stdin


#going line by line through the rules file
#converting uppercase to lower case and deleting redundent commas, tabs and comments
while read -r parsed_rule_line;
do
	parsed_rule_line_line=`echo "$parsed_rule_line" |sed 's/#.*//g'|sed '/^$/d'|sed 's/ //g'|tr -d '\t'|tr -s ','`
	if [[ -n $parsed_rule_line_line ]]
	then
		if [[ $parsed_rule_line = ,* ]]
		then
			parsed_rule_line_line=`echo "$parsed_rule_line"|sed 's/.//'`
		fi
		if [[ $parsed_rule_line_line = *, ]]
		then
			parsed_rule_line_line=`echo "$parsed_rule_line_line"|sed 's/.$//'`
		fi
		
		#filling an array with filters from the rules file & and filtering the packets accordingly
		readarray -d , -t filters <<< "$parsed_rule_line_line"
		
		good_packets=`echo "$packets"|./firewall.exe "${filters[0]}"`
		good_packets=`echo "$good_packets"|./firewall.exe "${filters[1]}"`
		good_packets=`echo "$good_packets"|./firewall.exe "${filters[2]}"`
		good_packets=`echo "$good_packets"|./firewall.exe "${filters[3]}"`
		for i in $good_packets
		do
			packets=$(echo -en "$packets" | grep -v $i)
 		done
		output+=`echo "$good_packets"`
		output+=$'\n'
	fi
	
done < "$rules"
echo -e "$output" |sed '/^$/d'|sed 's/ //g'|sort



