// UCLA CS 111 Lab 1 command reading

#include "command.h"
#include "command-internals.h"
#include "alloc.h"

#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* FIXME: You may need to add #include directives, macro definitions,
   static function definitions, etc.  */

/* FIXME: Define the type 'struct command_stream' here.  This should
   complete the incomplete type declaration in command.h.  */

struct individual_command {
  char* command;
  int index;
  int size;
};

/*struct command_stream {
  struct individual_command* curr_command;
  int index;
  int num_commands;
}; */

struct command_stream {
  struct char_node *charRoot;
  struct command_node *next;
  struct command_node *previous;	
};

struct char_node {
	char x;
	struct char_node *next;
	struct char_node *previous;
};


/* char* make_char_buffer (int (*get_next_byte) (void *), void *get_next_byte_argument) {
  size_t buffer_size = 1024;
  char* char_buffer = (char *) checked_malloc(buffer_size);   //initialize buffer, with size of 1024
  char curr_byte;

  size_t file_index = 0;
  while ((curr_byte = get_next_byte(get_next_byte_argument)) != EOF) {
    char_buffer[file_index] = curr_byte;
    file_index++;
    if(file_index == buffer_size) {       //buffer has been filled, need to make it grow
      char_buffer = (char *) checked_realloc(char_buffer, &buffer_size);
    }
  }
  return char_buffer;
} */

command_stream_t
make_command_stream (int (*get_next_byte) (void *),
		     void *get_next_byte_argument)
{
	char curr_byte;
//  command_stream_t m_command_stream;
//  int stream_index = 0;
//  m_command_stream.index = stream_index;
//  int command_index = 0;
//  struct individual_command* curr_command;

	struct command_stream *root;
 	root = checked_malloc(sizeof(struct command_stream));
	root->next = 0;
	root->previous = 0; 
	struct command_stream *curNode = root;
	int parenCount = 0;
	char oneByte = get_next_byte(get_next_byte_argument);
	if (oneByte == '(')
	{
		parenCount++;
	}
	curNode->charRoot = checked_malloc(sizeof(struct char_node));
	struct char_node *curChar = curNode->charRoot;
	curChar->previous = 0;
	curChar->next = 0;
	struct char_node *nextChar = 0;
	struct command_stream *nextNode = 0;
	curChar->x = oneByte;
	int newCommand = 0;

  	while ((curr_byte = get_next_byte(get_next_byte_argument)) != EOF) 
  	{
  		if (curr_byte == '\n')
  		{
			if (newCommand == 1)
			{
				continue;
			}
			if (parenCount > 0)
			{
                        	curChar->next = checked_malloc(sizeof(struct char_node));
                        	nextChar = curChar->next;
                        	nextChar->previous = curChar;
                        	nextChar->next = 0;
				nextChar->x = curr_byte;
                        	curChar = nextChar;
                        	nextChar = 0;
			}
			else
			{
				curNode->next = checked_malloc(sizeof(struct command_stream));
				nextNode = curNode->next;
				nextNode->previous = curNode;
				nextNode->next = 0;
				curNode = nextNode;
				nextNode = 0;
				curNode->charRoot = checked_malloc(sizeof(struct char_node));
				curChar = curNode->charRoot;
				curChar->previous = 0;
				curChar->next = 0;
				nextChar = 0;
				newCommand = 1;
			}
		}
		//else if (curr_byte == '(')
		//{
		//	
		//}
		else if (curr_byte == ')')
		{
                        curChar->next = checked_malloc(sizeof(struct char_node));
                        nextChar = curChar->next;
                        nextChar->previous = curChar;
                        nextChar->next = 0;
                        nextChar->x = curr_byte;
                        curChar = nextChar;
                        nextChar = 0;
                        
			curNode->next = checked_malloc(sizeof(struct command_stream));
			nextNode = curNode->next;
			nextNode->previous = curNode;
			nextNode->next = 0;
			curNode = nextNode;
			nextNode = 0;
			curNode->charRoot = checked_malloc(sizeof(struct char_node));
			curChar = curNode->charRoot;
			curChar->previous = 0;
			curChar->next = 0;
			nextChar = 0;
			newCommand = 1;
	
		}
		else
		{
			if (newCommand == 1)
			{
				curChar->x = curr_byte;
				newCommand = 0;
				continue;
			}
			curChar->next = checked_malloc(sizeof(struct char_node));
			nextChar = curChar->next;
			nextChar->previous = curChar;
			nextChar->next = 0;
			nextChar->x = curr_byte;
			curChar = nextChar;
			nextChar = 0;
		}
  	}


  //error (1, 0, "command reading not yet implemented");
  return root;
}

command_t
read_command_stream (command_stream_t s)
{
  char* curr_char = s -> charRoot -> x;
  
  error (1, 0, "command reading not yet implemented");
  return 0;
}
