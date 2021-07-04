# Hash-Table-Using-Linear-Probing
This program uses a hash function to decide where to place each element (emails in this case) in the
array. Whenever collision occurs between different elements, searches for the next available empty spot in the array and stores how far it is from
the original key value. The program also shows the number of collusions occured, inserting and search durations.

In this program, the following hash function is used:

![image](https://user-images.githubusercontent.com/68453742/124392999-00058680-dd01-11eb-97bf-2a5aad11ccb4.png)

where s is an array of characters in an email, P is the prime number 67, m is the
length of the email, and M is the table size.

The number 67 was chosen as our prime number to reduce collisions. Although it is
closer to a power of 2 compared to other prime numbers, experimentally, it produced
far fewer collisions and better distribution with our dataset.

3 sets of randomized emails were used, A, B, and C,with sizes 100,
100000, and 500000, respectively
The format is as follows.
[A-Za-z0-9]{5}\.[A-Za-z0-9]{5}@[A-Za-z]{5}\.(com|net|org)

Set A: 

![image](https://user-images.githubusercontent.com/68453742/124393469-58d61e80-dd03-11eb-9093-cc17319a71d2.png)

Set B: 

![image](https://user-images.githubusercontent.com/68453742/124393483-6a1f2b00-dd03-11eb-9e99-0b6a6d6d4d7d.png)

Set C:

![image](https://user-images.githubusercontent.com/68453742/124393490-786d4700-dd03-11eb-93fb-0664613c36c0.png)
