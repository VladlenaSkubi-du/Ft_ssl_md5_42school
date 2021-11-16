#!/bin/bash

TYPE=$1
ALGO=$2
STRING=$3

if [ -z "$TYPE" ]
then
	printf "Please, define stdin/string/file as first argument\n"
	exit 1
fi

if [ -z "$ALGO" ]
then
	printf "Please, define algorithm as second argument\n"
	exit 1
fi

if [ -z "$STRING" ]
then
	printf "Please, define string as third argument\n"
	exit 1
fi

if [ "$TYPE" == "stdin" ]
then
	printf "Launching:\necho \"%s\" | ./ft_ssl %s -q > 1\n" $STRING $ALGO
	printf "echo \"%s\" | openssl %s > 2\n" $STRING $ALGO
	printf "diff 1 2\n"

	echo $STRING | ./ft_ssl $ALGO -q > 1
	echo $STRING | openssl $ALGO > 2
	diff 1 2
elif [ "$TYPE" == "string" ]
then
	if [ "$ALGO" == "md5" ]
	then
		printf "Launching:\n./ft_ssl %s -q -s %s > 1\n" $ALGO $STRING
		printf "md5 -q -s %s > 2\n" $STRING
		printf "diff 1 2\n"
	
		./ft_ssl $ALGO -q -s $STRING > 1
		md5 -q -s $STRING > 2
		diff 1 2
	else
		printf "Launching:\n./ft_ssl %s -q -s %s > 1\n" $ALGO $STRING
		printf "echo \"%s\" | openssl %s > 2\n" $STRING $ALGO
		printf "diff 1 2\n"

		./ft_ssl $ALGO -q -s $STRING > 1
		echo $STRING | openssl $ALGO > 2
		diff 1 2
	fi
else
	printf "Launching:\n./ft_ssl %s -q %s ... > 1\n" $ALGO $STRING
	printf "openssl %s %s ... | awk \'BEGIN{FS=\"= \"} {print \$2}\' > 2\n" $ALGO $STRING
	printf "diff 1 2\n"

	./ft_ssl $ALGO -q ${@:3} > 1
	openssl $ALGO ${@:3} | awk 'BEGIN{FS="= "} {print $2}' > 2
	diff 1 2
fi
	
