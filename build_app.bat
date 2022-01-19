set PRJ_PATH=%~dp0
set BIN_PATH=%PRJ_PATH%bin\
set APP_PATH=%PRJ_PATH%app\
set CORE_PATH=%PRJ_PATH%core\

clang -I%APP_PATH%inc -I%CORE_PATH%inc -o %BIN_PATH%app.exe %APP_PATH%src\*.c -L %BIN_PATH% -l ds_core