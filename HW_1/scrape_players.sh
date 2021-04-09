
#!/bin/bash
wget https://www.premierleague.com/players

cat players | grep -P "/players/[0-9]+/[a-z A-z -]+/overview" > out.text

sed -i 's/\/players/https:\/\/www\.premierleague\.com\/players/' out.text

players_num=$(cat out.text | wc -l)
echo "total players: $players_num" > results.csv

for (( i=1; i<=$players_num; ++i )); do

link=$(cat out.text | head -n $i | tail -n 1 | grep -P -o "https://www.premierleague.com/players/[0-9]+/[a-z A-z -]+/overview"  )
wget "$link" 
num_of_times=$(cat overview | grep -P -o "[Mm]idfielder" | wc -w )

if [[ $num_of_times -gt 0 ]]; then 

echo "$link, Midfielder, $num_of_times" >> results.csv

fi

rm overview

done 


