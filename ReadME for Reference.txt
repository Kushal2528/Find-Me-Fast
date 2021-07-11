Hey there!!

/*This is an implementation of TCP based Concurrent server 
to which multiple TCP clients can connect and play a random 
integer array based game.*/

Here multiple clients are handled through fork() system call,
where in for every new client request server spawns a child
process to handle it.

The game is based on random numbers.
Server generates a random integer array in range of -20 to 20
and displays it to client in an ordered form.
Looking that array Client needs to answer
four questions i.e 
{Count of negative no's, Max no., Minimum No.,Count of positive no's} 
WITHIN time limit of 7 SECONDS per question!

I used poll() system call to give timeouts.
For more info on poll system call 
Please Visit: 
https://man7.org/linux/man-pages/man2/poll.2.html


