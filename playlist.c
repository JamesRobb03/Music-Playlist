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

//TO-DO add input validation for trackname and tracklength.
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
	if (strlen(trackName)<1 || strlen(trackName)>50)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//initialise fields
	strcpy(newTrack->trackName, trackName);
	newTrack->trackLength = trackLength;
	newTrack->prev = NULL;
	newTrack->next = NULL;

	//check to see if playlist is empty.
	if (listPtr->curr == NULL)
	{
		listPtr->head = newTrack;
		listPtr->curr = newTrack;
		listPtr->tail = newTrack;
	}
	else if (listPtr->curr == listPtr->head)
	{
		newTrack->next = listPtr->curr;
		listPtr->curr->prev = newTrack;
		listPtr->head = newTrack;
	}
	else
	{
		newTrack->next = listPtr->curr;
		newTrack->prev = listPtr->curr->prev;
		listPtr->curr->prev->next = newTrack;
		listPtr->curr->prev = newTrack;
	}

	return SUCCESS;
}
//function which inserts a MP3Track into the playlist after the current position.
int insertAfterCurr(Playlist* listPtr, char trackName[], int trackLength)
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
	if (strlen(trackName)<1 || strlen(trackName)>50)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//initialise fields
	strcpy(newTrack->trackName, trackName);
	newTrack->trackLength = trackLength;
	newTrack->prev = NULL;
	newTrack->next = NULL;

	//check to see if playlist is empty.
	if (listPtr->curr == NULL)
	{
		listPtr->head = newTrack;
		listPtr->curr = newTrack;
		listPtr->tail = newTrack;
	}else
	{
		if (listPtr->curr == listPtr->tail)
		{
			newTrack->prev = listPtr->curr;
			listPtr->curr->next = newTrack;
			listPtr->tail = newTrack;
		}
		else
		{
			newTrack->prev = listPtr->curr;
			newTrack->next = listPtr->curr->next;
			listPtr->curr->next->prev = newTrack;
			listPtr->curr->next = newTrack;

		}
	}

	return SUCCESS;	
}
//moves current forward one track
int skipNext(Playlist* listPtr)
{
	if (listPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}
	if (listPtr->head == NULL || listPtr->curr == NULL || listPtr->curr->next == NULL)
	{
		return INVALID_LIST_OPERATION;
	}

	listPtr->curr = listPtr->curr->next;
	return SUCCESS;
}
//moves current back one track
int skipPrev(Playlist* listPtr)
{
	//check if queue is valid
	if (listPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//checking to see if list is empty
	if (listPtr->head == NULL || listPtr->curr == NULL || listPtr->curr->prev == NULL)
	{
		return INVALID_LIST_OPERATION;
	}

	listPtr->curr = listPtr->curr->prev;
	return SUCCESS;

}

/* Get the data for the current track in the playlist */
int getCurrentTrack(Playlist* listPtr, MP3Track *pTrack)
{
	if (listPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}
	if (pTrack == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}
	if (listPtr->curr == NULL)
	{
		return INVALID_LIST_OPERATION;
	}

	strcpy(pTrack->trackName, listPtr->curr->trackName);
	pTrack->trackLength = listPtr->curr->trackLength;
	pTrack->prev = listPtr->curr->prev;
	pTrack->next = listPtr->curr->next;

	return SUCCESS;
}

//function which removes the MP3Track at the current position in the playlist
int removeAtCurr(Playlist* listPtr, MP3Track *pTrack, int moveForward)
{
	if (listPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}
	if (pTrack == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}
	if (listPtr->curr == NULL)
	{
		return INVALID_LIST_OPERATION;
	}

	//store track at current position in playlist
	strcpy(pTrack->trackName, listPtr->curr->trackName);
	pTrack->trackLength = listPtr->curr->trackLength;
	pTrack->prev = listPtr->curr->prev;
	pTrack->next = listPtr->curr->next;

	//create a temp pointer to track at current position in playlist
	MP3Track *pToRemove = listPtr->curr;

	//if there is only one track within the playlist
	if (listPtr->head == listPtr->tail)
	{
		listPtr->head = NULL;
		listPtr->tail = NULL;
		listPtr->curr = NULL;
	}
	//if the current track is the head of the playlist
	else if (listPtr->head == listPtr->curr)
	{
		//change current to next track in playlist
		//change head to current track
		listPtr->curr = listPtr->head->next;
		listPtr->head = listPtr->curr;
		listPtr->head->prev = NULL;
	}
	//if the current track is the tail of the playlist
	else if (listPtr->tail == listPtr->curr)
	{
		listPtr->curr = listPtr->tail->prev;
		listPtr->tail = listPtr->curr;
		listPtr->tail->next = NULL;
	}
	//if the track is not the head or the tail
	else
	{
		if (moveForward == 1)
		{
			pToRemove->prev->next = pToRemove->next;
			pToRemove->next->prev = pToRemove->prev;
			listPtr->curr = pToRemove->next;
		}
		else
		{
			pToRemove->prev->next = pToRemove->next;
			pToRemove->next->prev = pToRemove->prev;
			listPtr->curr = pToRemove->prev;
		}
	}

	pToRemove->next = NULL;
	pToRemove->prev = NULL;
	pToRemove->trackLength = 0;
	strcpy(pToRemove->trackName, "");
	free(pToRemove);

	return SUCCESS;
}

//function which clears the playlist
int clearPlaylist(Playlist* listPtr)
{
	if (listPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	while(listPtr->head != NULL)
	{
		MP3Track *currentHead = listPtr->head;

		listPtr->head = listPtr->head->next;

		currentHead->next = NULL;
		currentHead->prev = NULL;
		currentHead->trackLength = 0;
		strcpy(currentHead->trackName, "");
		free(currentHead);
	}

	free(listPtr);

	return SUCCESS;
}

//Function which writes out a playlist to a file.
int savePlaylist(Playlist *listPtr, char filename[])
{
	if (listPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}
	if (listPtr->head == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}
	if (filename == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}
	if (strlen(filename)<1)
	{
		return INVALID_INPUT_PARAMETER;
	}

	FILE *fp;
	fp = fopen(filename, "w");
	char delimiter = '#';
	char newLine = '\n';

	//if the file opens then
	if (fp != NULL) 
	{
		MP3Track *nextTrack = listPtr->head;
		//while there are mp3 tracks in the playlist
		while (nextTrack != NULL)
		{
			//writes and MP3Track to a file
			fputs(nextTrack->trackName, fp);
			fputc(delimiter, fp);
			fprintf(fp, "%d" ,nextTrack->trackLength);
			fputc(delimiter, fp);
			fputc(newLine, fp);

			nextTrack = nextTrack->next;
		}
		fclose(fp);
	}
	else
	{
		return FILE_IO_ERROR;
	}
	return SUCCESS;
}

//function which creates a playlist from a file.
int loadPlaylist(Playlist **listPtr, char filename[])
{
	//create the playlist
	createPlaylist(listPtr);

	FILE *fp;
	fp = fopen(filename,"r");
	//if the file opens
	if (fp!=NULL)
	{
		char line[256];
		char name[50];
		char length[4];

		//while there are lines in the text file do
		while(fgets(line, 256, fp) !=NULL)
		{
			char delim[] = "#";

			char *ptr = strtok(line, delim);
			strcpy(name, ptr);
			ptr = strtok(NULL, delim);
			strcpy(length, ptr);
			//converts from string into integer
			int numLength = atoi(length);
			//adds to playlist
			insertAfterCurr((*listPtr),name, numLength);
			skipNext((*listPtr));
		}
		//sets the current position back to the head of the playlist
		(*listPtr)->curr = (*listPtr)->head;
	}
	else
	{
		return FILE_IO_ERROR;
	}

	return SUCCESS;
}

