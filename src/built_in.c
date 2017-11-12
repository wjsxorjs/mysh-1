#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/limits.h>

#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "tpf_unix_sock.server"
#define DATA "Hello from client\n"



#include "built_in.h"



int do_cd(int argc, char** argv) {

int val = validate_cd_argv(argc, argv);

 if(val == 2){
return 0;
}


  if (val == 0)
    return -1;

  if (chdir(argv[1]) == -1)
    return -1;

  return 0;
}

int do_pwd(int argc, char** argv) {

int val = validate_pwd_argv(argc, argv);

 if(val == 2){
return 0;
}
  if (val == 0)
    return -1;
  

  char curdir[PATH_MAX];

  if (getcwd(curdir, PATH_MAX) == NULL)
    return -1;

  printf("%s\n", curdir);

  return 0;
}

int do_fg(int argc, char** argv) {

  if (!validate_fg_argv(argc, argv))
    return -1;
  int pid = getpid();
  printf("[%d]: %s. Done\n",pid, argv[0]);

  return 0;
}

int do_bin(int argc, char** argv){

int val = validate_bin_argv(argc, argv);

 if(val == 0){
   return -1;
}
if (val == 2)
return 0;


int pid = fork();
if(pid  < 0){exit(1);}

else if (pid  == 0){
execv(argv[0],argv);
}


wait(NULL);



return 0;
}


int validate_cd_argv(int argc, char** argv) {
if(argc>1){
if(strcmp(argv[argc-1],"&")==0){
bg(argc-1,argv);
return 2;
}
}

  if (argc != 2) return 0;
  if (strcmp(argv[0], "cd") != 0) return 0;

  struct stat buf;
  stat(argv[1], &buf);

  if (!S_ISDIR(buf.st_mode)) return 0;



  return 1;
}

int validate_pwd_argv(int argc, char** argv) {
 if(argc>1){
if(strcmp(argv[argc-1],"&")==0){
bg(argc-1,argv);
return 2;
}
}

 if (argc != 1) return 0;
  if (strcmp(argv[0], "pwd") != 0) return 0;

  return 1;
}

int validate_fg_argv(int argc, char** argv) {
  if (argc != 1) return 0;
  if (strcmp(argv[0], "fg") != 0) return 0;
  


  return 1;
}


int validate_bin_argv(int argc, char** argv){
if(argc>1){
if(strcmp(argv[argc-1],"&")==0){
bg(argc-1, argv);
return 2;
}
}


if (argc < 1) return 0;
if (argv[0][0] == '/'){
if(argv[0][1] == 'b'){
if(argv[0][2] == 'i'){
if(argv[0][3] == 'n'){
if(argv[0][4] == '/') return 1;
}
}
}
else if(argv[0][1] == 'u'){
if(argv[0][2] == 's'){
if(argv[0][3] == 'r'){
if(argv[0][4] == '/') return 1;
}
}
}
}

return 0;

}

void bg(int argc, char **argv){
if(strcmp(argv[0],"cd")==0){do_cd(argc,argv);}
if(strcmp(argv[0],"pwd")==0){do_pwd(argc,argv);}
else {do_bin(argc,argv);}


}
