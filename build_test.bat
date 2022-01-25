set PRJ_PATH=%~dp0
set BIN_PATH=%PRJ_PATH%bin\
set CORE_PATH=%PRJ_PATH%core\
set TEST_PATH=%PRJ_PATH%test\

clang -I%TEST_PATH%inc -I%CORE_PATH%inc -o %BIN_PATH%test.exe %TEST_PATH%src\*.c -L %BIN_PATH% -l ds_core