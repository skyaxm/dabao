#!/bin/bash
func()
{
    echo "hello"
    exit 5
}

echo $0
echo $#
echo "start"
func
sleep 5
echo "end"

:<<EOF
echo $#
if [[ $# != 2 && $# != 3 ]]; then
    exit 1
fi
functest()
{
    echo "hiahiahia"
    return 5
}
functest
ls -l
exit 4
EOF
