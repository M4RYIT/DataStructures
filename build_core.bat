set PRJ_PATH=%~dp0
set BIN_PATH=%PRJ_PATH%bin\
set APP_PATH=%PRJ_PATH%app\
set CORE_PATH=%PRJ_PATH%core\

clang -I%CORE_PATH%inc -o %BIN_PATH%ds_core.lib %CORE_PATH%src\*.c -fuse-ld=llvm-lib