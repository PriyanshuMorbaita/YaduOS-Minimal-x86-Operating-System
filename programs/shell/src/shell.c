#include "shell.h"
#include "stdio.h"
#include "stdlib.h"
#include "peachos.h"

int main(int argc, char** argv){
    print("PeachOs v1.0.0\n");
    print("\n");
    while(1){
        print("$ ");
        char buffer[1024];
        peachos_terminal_readline(buffer,sizeof(buffer),true);
        print("\n");
        peachos_system_run(buffer);
    }
    return 0;
}