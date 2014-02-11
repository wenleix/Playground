for f in `ls *.txt`; do
    number=$RANDOM
    let "number %= 2"
    if [ "$number" -eq 0 ]; then
        mv $f train
    fi
done

