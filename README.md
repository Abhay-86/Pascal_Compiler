
PASCAL compiler implemented in C
____________________________________________________________________________________________________________

________________________________Guide to run (if u have created ./executablefile)___________________________

PASCAL files can be compiled using the command `./compiler <file_name.p>`. The command `gcc <file_name.s>` will then convert the generated assembly file to an executable, which can be run with `./a.out`.
 
_________________________ Guide to run (if u have not created ./executablefile)______________________________
run "bison -d compiler.y -Wnone" //Wnone will not show warnig
then run "flex compiler.l"
then "gcc lex.yy.c compiler.tab.c tree.c reg_stack.c hash.c gencode.c -w -lm" // which will generate ./.out
then to execute ./a.out <file_name.p>
which will create <file_name.s> file


____________________________________________Extra information________________________________________________
we have created test_file which contain ./compiler file.So by executing "./compiler <file_name.p>" you can create assembly code for that file.


____________________________________________Generated File___________________________________________________

we have generated assembly code for different .p file by executing above command, u can check

_____________________________________________THE END________________________________________________________


We have created assembly folder
Other then project if u want to run assembly code then run command as follow:

run "gcc -s -o <file_name.s> <file_name.c>"
then "./file_name.c"

ex  run "gcc -s -o hello_world.s hello_world.c"
then "./hello_world.c"


refence -- https://github.com/kdakan/Building-a-Pascal-Compiler 
___________________________________________Thank You___________________________________________
