/*
 Name: James Robb
 Matric number: 180010640
 Module code: AC21008
*/
#include "playlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int createPlaylist(Playlist **listPtr)
{
	if (listPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//check to see whether pointer is already pointing at something
	if (*listPtr != NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//allocating memory for new playlist
	(*listPtr) = (Playlist*)myMalloc(sizeof(Playlist)); 

	//checking for memory failure
	if ((*listPtr)==NULL)
	{
		return MEMORY_ALLOCATION_ERROR;
	}

	//setting values for playlist
	(*listPtr)->head = NULL;
	(*listPtr)->tail = NULL;
	(*listPtr)->curr = NULL;

	return SUCCESS;
}

int insertBeforeCurr(Playlist* listPtr, char trackName[], int trackLength)
{
	//check to see if pointer is pointing to a valid list
	if (listPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//creates a mp3 track to add to the playlist
	MP3Track *newTrack = (MP3Track*)myMalloc(sizeof(MP3Track));

	//memory allocation check
	if (newTrack == NULL)
	{
		return MEMORY_ALLOCATION_ERROR;
	}

	//input validation check
	if (trackName == NULL || trackLength < 1)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//initialise fields
	strcpy(newTrack->trackName, trackName);
	newTrack->trackLength = trackLength;
	newTrack->prev = NULL;
	newTrack->next = NULL;

	//check to see if playlist is empty.
	if (listPtr->head == NULL && listPtr->curr == NULL && listPtr->tail == NULL)
	{
		listPtr->head = newTrack;
		listPtr->curr = newTrack;
		listPtr->tail = newTrack;
	}else
	{
		//case 1 check (current is at the head of the list)
		if (listPtr->curr == listPtr->head && listPtr->curr->prev == NULL)
		{
			newTrack->next = listPtr->curr;
			listPtr->curr->prev = newTrack;
			listPtr->head = newTrack;
		}
		if(listPtr->curr != listPtr->head && listPtr->curr->prev != NULL)
		{
			newTrack->next = listPtr->curr;
			newTrack->prev = listPtr->curr->prev;
			listPtr->curr->prev->next = newTrack;
			listPtr->curr->prev = newTrack;
		}
	}

	return SUCCESS;
}
















//OWN TESTING PURPOSES DELETE LATER
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

int main(int argc, char const *argv[])
{
	int result;

	// a variable to store an MP3 track popped from the list
	MP3Track track;

	// a pointer to our doubly-linked list
	Playlist *listPtr = NULL;

	// initialise the list - passing the address of our
	// list pointer as an input so it can be modified 
	// to point to the memory allocated for the list
	result = createPlaylist(&listPtr);
	if (result != SUCCESS)
	{
		printf("An error occurred when attempting to initialise the list\n");
	}
	else
	{
		printf("List initialised successfully\n");
	}
	printf("\n");

	result = insertBeforeCurr(listPtr, "Katie is cute", 120);
	if (result != SUCCESS)
	{
		printf("An error occurred when attempting to add before current\n");
	}
	else
	{
		printf("added to list successfully\n");
	}
	printf("\n");

	result = insertBeforeCurr(listPtr, "Bound 2", 120);
	if (result != SUCCESS)
	{
		printf("An error occurred when attempting to add before current\n");
	}
	else
	{
		printf("added to list successfully\n");
	}
	printf("\n");

	return 0;
}