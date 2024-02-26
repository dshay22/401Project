To build project use the following command in this order.

cmake build ./..

make

./Project401

----------------------------------------------------------------
----------------------------------------------------------------

If you make an edit to the code and need to RE-build do this order 

make --build <PATH TO YOU PROJECT>/Project_401/build/ --target clean

cmake build ./..

make

./Project401
