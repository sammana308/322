# Comp 322
#Lab2
##Name: Sammana Kabir

This project contains two part: 1)Launch
								2)Tube
In Launch, we use fork() to create child process which uses execve() to execute the supplied command, and the parents returns the PID of the child process on stderr.

In Tube, we allocate one pipe using pipe(), create two children processes using fork(), and set up an inter-process communication between the two child processes using dup2(). The first child process execute the first command(/bin/cat), and the second one executes the second command(/usr/bin/head).




