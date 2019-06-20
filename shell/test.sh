#!/bin/bash
func()
{
    echo "hello"
    exit 5
}
echo "hello world"

:<<EOF
echo $0
echo $#
echo "start"
func
sleep 5
echo "end"
EOF

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
