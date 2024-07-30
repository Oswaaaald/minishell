max=1000
for i in `seq 2 $max`
do
    temp=`./minishell | wc -l`
    if [ "$temp" -gt "4" ]
    then
        echo "bad"
    fi
done