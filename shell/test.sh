#!/bin/bash
func()
{
    echo "hello"
    return 5
}

echo $0
echo $#
echo "start"
func
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
