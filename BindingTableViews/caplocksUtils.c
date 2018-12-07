//
//  caplocksUtils.c
//  BindingTableViews
//
//  Created by Dzu Nguyen on 12/7/18.
//  Copyright © 2018 Simon. All rights reserved.
//

#include "caplocksUtils.h"
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/hidsystem/IOHIDLib.h>
#include <IOKit/hidsystem/IOHIDParameter.h>
#include <libgen.h> // basename


static io_connect_t ioc = IO_OBJECT_NULL;

int initConnection()
{
	kern_return_t kr = KERN_FAILURE;
	
	if (ioc != IO_OBJECT_NULL)
		return KERN_SUCCESS;
	
	
	io_service_t ios;
//	io_connect_t ioc;
	CFMutableDictionaryRef mdict;
	int op;
	bool state;

	mdict = IOServiceMatching(kIOHIDSystemClass);
	ios = IOServiceGetMatchingService(kIOMasterPortDefault, (CFDictionaryRef)mdict);
	if (!ios) {
		if (mdict)
			CFRelease(mdict);
		fprintf(stderr, "IOServiceGetMatchingService() failed: %x\n", kr);
		return (int)kr;
	}
	kr = IOServiceOpen(ios, mach_task_self(), kIOHIDParamConnectType, &ioc);
	IOObjectRelease(ios);
	if (kr != KERN_SUCCESS) {
		fprintf(stderr, "IOServiceOpen() failed: %x\n", kr);
		return (int)kr;
	}
	
	return kr;
}

void closeConnection()
{
	if (ioc != IO_OBJECT_NULL)
	{
		IOServiceClose(ioc);
	}
}

int getCaplocksState(bool *value)
{
	if (value == NULL)
		return KERN_INVALID_ARGUMENT;
	
	
	kern_return_t kr = initConnection();
	
	if (kr == KERN_SUCCESS)
	{
		kr = IOHIDGetModifierLockState(ioc, kIOHIDCapsLockState, value);
		if (kr != KERN_SUCCESS) {
			IOServiceClose(ioc);
			fprintf(stderr, "IOHIDGetModifierLockState() failed: %x\n", kr);
			return (int)kr;
		}
	}
	
	
	return kr;
}

int setCapslockState(bool state)
{
	kern_return_t kr = initConnection();
	
	kr = IOHIDSetModifierLockState(ioc, kIOHIDCapsLockState, state);
	if (kr != KERN_SUCCESS) {
		IOServiceClose(ioc);
		fprintf(stderr, "IOHIDSetModifierLockState() failed: %x\n", kr);
		return (int)kr;
	}
	
	return (int)kr;
}






