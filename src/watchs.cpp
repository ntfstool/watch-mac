/**
 * @author   service@ntfstool.com
 * Copyright (c) 2020 ntfstool.com
 * Copyright (c) 2020 alfw.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the MIT General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * MIT General Public License for more details.
 *
 * You should have received a copy of the MIT General Public License
 * along with this program (in the main directory of the NTFS Tool
 * distribution in the file COPYING); if not, write to the service@ntfstool.com
 */

#include <iostream>
#include <CoreServices/CoreServices.h>
#include <unistd.h>
void NtfsToolCallback(
    ConstFSEventStreamRef streamRef,
    void *clientCallBackInfo,
    size_t numEvents,
    void *eventpathArr,
    const FSEventStreamEventFlags eventFlags[],
    const FSEventStreamEventId eventIds[]) {
	int i;
	char const **pathArr = (char const**)eventpathArr;
	FSEventStreamEventId lastRenameEventID = 0;
	const char*  lastPath = nil;
	for (i=0; i<numEvents; i++) {
		FSEventStreamEventFlags flag = eventFlags[i];
		if(kFSEventStreamEventFlagItemCreated & flag) {
			printf("CreteFileEvent\t%s\n",pathArr[i]);
		}
		if(kFSEventStreamEventFlagItemRenamed & flag) {
			FSEventStreamEventId currentEventID = eventIds[i];
			const char*  currentPath = pathArr[i];
			if (currentEventID == lastRenameEventID + 1) {
				printf("MoveFileEvent\t%s\t%s\n",lastPath,currentPath);
			} else {
				// access 0 -> ok  access -1 ->fail
				if (access(currentPath, R_OK) == 0) {
					//move file in this folder
					printf("MoveFileInEvent\t%s\n",currentPath);
				} else {
					//move file out this folder
					printf("MoveFileOutEvent\t%s\n",currentPath);
				}
			}
			lastRenameEventID = currentEventID;
			lastPath = currentPath;
		}
		if(kFSEventStreamEventFlagItemRemoved & flag) {
			printf("DeleteFileEvent\t%s\n",pathArr[i]);
		}
		if(kFSEventStreamEventFlagItemModified & flag) {
			printf("ModifyFileEvent\t%s\n",pathArr[i]);
		}
	}
}
int main(int argc,char **argv) {
    if(!argv[1] || strcmp(argv[1],"help") == 0){
       printf("Usage:\twatchs path\nResult:\tCreteFileEvent\tpath\n\tMoveFileEvent\tpath\n\tMoveFileEvent\tfromPath\ttoPath\n\tMoveFileInEvent\tpath\n\tMoveFileOutEvent\tpath\n\tDeleteFileEvent\tpath\n\tModifyFileEvent\tpath\n");
       printf("Watch for file (folder) changes [For MAC]\nCopyright ©2020 ntfstool.com\n");
       return 0;
    }

    char * firstName_c = argv[1];
    CFStringRef watchPath =CFStringCreateWithCString(NULL, firstName_c, kCFStringEncodingUTF8);



	CFArrayRef  pathArrToWatch = CFArrayCreate(NULL, (const void **)&watchPath, 1, NULL);
	FSEventStreamRef stream;
	CFAbsoluteTime latency = 1.0;
	/* Latency in seconds */
	/* Create the stream, passing in a callback */
	stream = FSEventStreamCreate(NULL,
	      &NtfsToolCallback,
	      NULL,
	      pathArrToWatch,
	      kFSEventStreamEventIdSinceNow,
	        /* Or a previous event ID */
	        latency,
            kFSEventStreamCreateFlagFileEvents
            // kFSEventStreamEventFlagItemCreated
            // kFSEventStreamCreateFlagNone /* Flags explained in reference */
	);
	FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
	FSEventStreamStart(stream);
	printf("Watch Files Tools for Mac\nCopyright ©2020 ntfstool.com\n");
	CFRunLoopRun();
	FSEventStreamInvalidate(stream);
	FSEventStreamRelease(stream);
	return 0;
}
