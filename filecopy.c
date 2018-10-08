//CREATED BY MATTHEW D'ANGELO & GURBIR MATHARU

#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
	char buffer[100];
	int fp[2], f1, size, target; 
	pipe(fp);

	//error handling below for arguments 
	if(argc != 3){
		fprintf("stderr", "%s" "Too few arguments\n");
		exit(1);
	}

	// Pipe magic 

	 
	if(fork()){//parent

		//Lock the pipe 
		if((close(fp[0]))!= 0)
			perror("Error: ");

		//open the file
		if((f1 = open(argv[1], O_RDONLY)) <0)
			perror("Error: ");

		//reading the input file. Getting the size of it
		if((size = read(f1, buffer, sizeof(buffer)))< 0 )
			perror("Error: ");

		//writing to the critial section 
		if( (write(fp[1], buffer, size)) <0)
			perror("Error: ");

	}else{ // child 
		//Lock the pipe that has the data 
		if( (close(fp[1])) != 0) 
			perror("Error: "); 

		//read the data passed from parent into fp
		if( (read(fp[0], buffer, sizeof(buffer))) <0 )
			perror("Error: "); 

		//fp can't be written to 
		if( (close(fp[0])) != 0)
			perror("Error: ");

		//create a new file with the name of the second argument
		//set it as read and write
		if( (target = open(argv[2], O_CREAT | O_WRONLY, 00777)) <0)
			perror("Error: "); 
		

		//write all the data from the first file into the second file
		if( (write(target, buffer, (strlen(buffer)-1))) <0)
			perror("Error: ");

	}
	return 0;

}