#!/bin/bash


echo "####################################################"
if [ -z $IIOD_REMOTE ]; then
	echo "U will use local context."
else
	echo "U will use network context."
	echo "network device IP: $IIOD_REMOTE"
fi
echo "####################################################"



