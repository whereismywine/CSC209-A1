#!/bin/bash

./addecho -d 12000 -v 2 testingsamples/door_original.wav testingsamples/door_12000_2_test.wav;
cmp -l testingsamples/door_12000_2_test.wav testingsamples/door_12000_2.wav >> test_output.txt;
if [ ! -s test_output.txt ]; 
then
    echo "testcase: door [-d = 12000], [-v = 2] >> PASSED"
    rm test_output.txt
fi

./addecho -d 12000 -v 4 testingsamples/door_original.wav testingsamples/door_12000_4_test.wav;
cmp -l testingsamples/door_12000_4_test.wav testingsamples/door_12000_4.wav >> test_output.txt;
if [ ! -s test_output.txt ]; 
then
    echo "testcase: door [-d = 12000], [-v = 4] >> PASSED"
    rm test_output.txt
fi

./addecho -d 20000 -v 4 testingsamples/door_original.wav testingsamples/door_20000_4_test.wav;
cmp -l testingsamples/door_20000_4_test.wav testingsamples/door_20000_4.wav >> test_output.txt;
if [ ! -s test_output.txt ]; 
then
    echo "testcase: door [-d = 20000], [-v = 4] >> PASSED"
    rm test_output.txt
fi

./addecho -d 35000 -v 2 testingsamples/door_original.wav testingsamples/door_35000_2_test.wav;
cmp -l testingsamples/door_35000_2_test.wav testingsamples/door_35000_2.wav >> test_output.txt;
if [ ! -s test_output.txt ]; 
then
    echo "testcase: door [-d = 35000], [-v = 2] >> PASSED"
    rm test_output.txt
fi

./addecho -d 60000 -v 1 testingsamples/door_original.wav testingsamples/door_60000_1_test.wav;
cmp -l testingsamples/door_60000_1_test.wav testingsamples/door_60000_1.wav >> test_output.txt;
if [ ! -s test_output.txt ]; 
then
    echo "testcase: door [-d = 60000], [-v = 1] >> PASSED"
    rm test_output.txt
fi

./addecho -d 3 -v 2 testingsamples/short.wav testingsamples/short_3_2_test.wav;
cmp -l testingsamples/short_3_2.wav testingsamples/short_3_2_test.wav >> test_output.txt;
if [ ! -s test_output.txt ]; 
then
    echo "testcase: short [-d = 3], [-v = 2] >> PASSED"
    rm test_output.txt
fi
