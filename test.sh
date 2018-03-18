#!/bin/bash

if [ $# == 2 ]; then
	PROG=$1
	DIR=$2
	DEBUG=0
elif [ $# == 3 ]; then
	FLAG=$1
	if [ $FLAG != "-v" ]; then
		echo "WRONG FLAG"
		exit 1
	fi
	PROG=$2
	DIR=$3
	DEBUG=1
else
	echo "INCORRECT INPUT"
	exit 1
fi

if [ ! -f $PROG ]; then
	echo "THERE IS NO PROGRAM"
	exit 1
fi

if [ ! -d $DIR ]; then
	echo "THERE ARE NO TESTS"
	exit 1
fi

for file in $DIR/test*.in; do
	FILENAME=${file/$DIR/""}
	./$PROG $FLAG < $file  > out 2> err
	if !(diff out "${file%.in}.out" >/dev/null 2>&1); then
		echo "$FILENAME NOT PASSED"
			
	fi
	if [ $DEBUG == 1 ]; then
		if !(diff err "${file%.in}.err" >/dev/null 2>&1); then
			echo "$FILENAME NOT PASSED DIAGNOSTIC"
		fi
	fi
done

rm -f out
rm -f err
