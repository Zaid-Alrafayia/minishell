cat < infile | grep "42" >> outfile

1. Token Chain (t_token)

The Lexer creates this linked list first, identifying the raw "parts" of the input string .  
Node value type Description
1 "cat" CMD The first executable command.
2 "<" REDIRECT_IN 

Instructs the shell to redirect input.
3 "infile" CMD 

The file to be used as input.
4 `" "` PIPE
5 "grep" CMD The second executable command.
6 "42" CMD 

An argument for grep. Your parser will strip the double quotes.
7 ">>" APPEND 

Redirects output in append mode.
8 "outfile" CMD 

The file where output will be appended.
2. Command Pipeline (t_cmd)

The Parser converts those tokens into these execution units. This is the list your Executor (Pipex-style logic) will actually run .  
Node A (The Producer)

    args: {"cat", NULL} (Ready for execve ).  

    infile: open("infile", O_RDONLY) (Opened by the executor or parser ).  

    outfile: -1 (Will be replaced by the write-end of the pipe during execution ).  

    append: false

    limiter: NULL

    next: Points to Node B.

Node B (The Consumer)

    args: {"grep", "42", NULL}

    infile: -1 (Will be replaced by the read-end of the pipe during execution ).  

    outfile: open("outfile", O_WRONLY | O_CREAT | O_APPEND).  

    append: true.  

    limiter: NULL

    next: NULL (End of the pipeline).

3. Environment List (t_env)

This persists throughout your shell session and is modified by export or unset .  

    Node 1: key: "PATH", value: "/usr/bin:/bin" (Used to find where cat and grep live ).  

    Node 2: key: "PWD", value: "/home/user/minishell"

    Node 3: key: "USER", value: "zaid"

4. Shell State (t_shell)

This is the "God Struct" that keeps track of the overall shell status.

    exit_status: 0 (Success of the previous command ).  

    pids: [1024, 1025] (The PIDs of the child processes for cat and grep ).  

    stdin_backup: 3 (Used to restore the shell's keyboard input after a command finishes ).  

    stdout_backup: 4 (Used to restore the screen output ).  

    tokens: Points to Token Node 1.

    current_cmd: Points to Command Node A.
