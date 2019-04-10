#!/bin/bash
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

