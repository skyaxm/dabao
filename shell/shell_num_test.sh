#!/bin/bash
a=$1
echo "$a"|[ -n "`sed -n '/^[0-9][0-9]*$/p'`" ] && echo string a is number


