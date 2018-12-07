//
//  AppDelegate.m
//  BindingTableViews
//
//  Created by Simon on 6/4/12.
//  Copyright (c) 2012 Simon. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

- (id) init {
    self = [super init];
    
    // create a mutable array to hold several Book objects
    self.allKeyboards = [[NSMutableArray alloc] init];
    
    Book *firstBook = [[Book alloc] init];
    // Objective-C setters
    [firstBook setAuthor:@"Fred Smith"];
    [firstBook setTitle:@"On a Dark and Stormy Night"];
    [firstBook setPageCount:315];
    
    [self.allKeyboards insertObject:firstBook atIndex:[self.allKeyboards count]];
    
    Book *secondBook = [[Book alloc] init];
    // dot-syntax
    secondBook.author = @"Jane Jones";
    secondBook.title = @"Under the Moonlight";
    secondBook.pageCount = 280;
    
    [self.allKeyboards insertObject:secondBook atIndex:[self.allKeyboards count]];
    
    return self;
}

- (IBAction)listBooks:(id)sender {
    for (Book *currentBook in self.allKeyboards) {
        NSLog(@"The book %@ by %@ has %i pages",
              currentBook.title,
              currentBook.author,
              currentBook.pageCount);
    }
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    
    
}
@end
