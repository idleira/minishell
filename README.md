# minishell - @42Wolfsburg
project about creating your own simple (mini)shell, taking bash as reference.

our very first group project, that i got to work on with [marianna](https://github.com/fraumarzhuk) (ง •̀_•́)ง (ง •̀_•́)ง

## description
minishell is a re-creation of a basic unix shell, which is a tool that lets users interact with the computer by typing commands. 

it replicates key features of a full-fledged shell, such as command parsing, execution, and basic file manipulation.

## 

these are some **resources** we used:

• [shell command language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)

• [lexical analysis](https://en.wikipedia.org/wiki/Lexical_analysis)

• [playlist with videos about all things minishell](https://www.youtube.com/playlist?list=PLGU1kcPKHMKj5yA0RPb5AK4QAhexmQwrW)

• [writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

• [let's build a linux shell - a tutorial](https://blog.devgenius.io/lets-build-a-linux-shell-part-i-954c95911501)

• [minishell map spreadsheet (744 test cases)](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit?gid=0#gid=0)

• [reallyshell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf): extensive minishell tester by [btvildia](https://github.com/BEQSONA-cmd)

##

![small minishell showcase](showcase.gif)

## how to use minishell
1. clone this repository: `git clone git@github.com:idleira/minishell.git minishell && cd minishell`;

2. use `make` to compile the project;
   
3. run the program with `./minishell`
   
4. have fun ⸂⸂⸜(രᴗര๑)⸝⸃⸃

5. to exit the program simply press `ctrl + d` or type `exit`;
   
6. to clean up:

   • use `make clean` to remove .o files;
   
   • use `make fclean` to clean up the project directory by removing **all** generated files.


## features
  → **command-line interface**: minishell greets you with a prompt, ready to execute your commands swiftly;
  
  → **command parsing and execution**: it efficiently parses and executes commands, from listing files to running scripts;
  
  → **built-in shell commands**: minishell supports built-in commands for easy directory navigation and status checks:
| command | description |
|---------|-------------|
| `pwd`   | print name of current/working directory |
| `cd`    | change the shell working directory (with a relative or absolute path) |
| `env`   | print the environment |
| `echo`  | echo the string(s) to standard output. -n flag: do not output the trailing newline |
| `export`| set export attribute for shell variables |
| `unset` | unset values of shell variables |
| `exit`  | exit minishell with the exit status specified |

  → **environment variable management**: you can easily set, get, and manage environment variables in Minishell;
  
  → **input/output redirection and piping**: it simplifies input/output redirection and command piping;
  
  → **signal handling and process management**: minishell effectively manages processes and handles signals.

  
### limitations
  → our minishell doesn’t support command chaining with ;, &&, or ||, but excels in other features.

##

completing this project was both challenging and demanding, pushing us to the limits of our coding abilities. ᕦ(ò_óˇ)ᕤ

however, it also provided invaluable learning experiences that have given us the confidence to tackle almost any programming challenge.

## a huge thank you

 to [marianna](https://github.com/fraumarzhuk) for collaboration — it was a great experience working together. (´｡• ᵕ •｡`)♡


## our final grade:

![minishell_grade](https://github.com/idleira/pipex/assets/127216218/ee27e75a-7737-449c-a430-e206a50ceb22)
