#import <Foundation/Foundation.h>
#include <string>
#include "DoNotBackup.h"

namespace platform
{

void DoNotBackup::set(const std::string& path)
{
    NSError *err = nil;
    
    NSString *element = [NSString stringWithCString:path.c_str() encoding:NSUTF8StringEncoding];
    NSURL *url = [NSURL fileURLWithPath:element];
    if( [url setResourceValue:[NSNumber numberWithBool:YES] forKey:NSURLIsExcludedFromBackupKey error:&err] == NO)
    {
        NSLog(@"Error: Unable to exclude directory from backup: %@", err);
    }
}

}
