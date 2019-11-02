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
		if (listPtr->curr == listPtr->tail && listPtr->curr->next == NULL)
		{
			newTrack->prev = listPtr->curr;
			listPtr->curr->next = newTrack;
			listPtr->tail = newTrack;
		}
		if (listPtr->curr->next != NULL)
		{
			newTrack->prev = listPtr->curr;
			newTrack->next = listPtr->curr->next;
			listPtr->curr->next->prev = newTrack;
			listPtr->curr->next = newTrack;

		}
	}

	return SUCCESS;	
}

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
	}
	//if the current track is the tail of the playlist
	else if (listPtr->tail == listPtr->curr)
	{
		listPtr->curr = listPtr->tail->prev;
		listPtr->tail = listPtr->curr;
	}
	//if the track is not the head or the tail
	else
	{
		if (moveForward == 1)
		{
			listPtr->curr = listPtr->curr->next;
		}
		else
		{
			listPtr->curr = listPtr->curr->prev;
		}
	}

	pToRemove->next = NULL;
	pToRemove->prev = NULL;
	pToRemove->trackLength = 0;
	strcpy(pToRemove->trackName, "");
	free(pToRemove);

	return SUCCESS;
}
