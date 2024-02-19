#!/usr/bin/bash

clear

sentence="I will not mistype ls again."

echo "It looks you mistyped ls or a similar command, before you can go on you have to prove that you are worhty of this machine and its keyboard.\n"

read -p "Please type the following sentence : $phrase : " sentence_1

if [[$sentence_1 -ne I will not mistype ls again.]]

read -ps "You will now type it again, but you will not be able to see what you write : 'I will not mistype ls again.' : " sentence_1
