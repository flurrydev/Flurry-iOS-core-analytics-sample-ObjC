//
//  FlurryAnalyticsConfiguration.m
//  FlurryCoreAnalyticsSampleApp_Obj
//
//  Created by Yilun Xu on 10/4/18.
//  Copyright © 2018 Flurry. All rights reserved.
//

#import "FlurryAnalyticsConfiguration.h"

static FlurryAnalyticsConfiguration* sharedInstance;
static NSString * const fileName = @"/setting.plist";

@interface FlurryAnalyticsConfiguration ()

@property (nonatomic, retain) NSMutableDictionary* info;
@property (nonatomic, retain) NSMutableDictionary* defaultInfo;

@end

@implementation FlurryAnalyticsConfiguration

- (NSString *) docsDir {
    return [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)objectAtIndex:0];
}

- (NSString *) getPath {
    return [[self docsDir]stringByAppendingString:fileName];
}


+ (instancetype)sharedInstance {
    static dispatch_once_t once;
    dispatch_once(&once, ^{
        sharedInstance = [[self.class alloc] init];
        sharedInstance.info = [[NSMutableDictionary alloc] initWithContentsOfFile:[[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)objectAtIndex:0] stringByAppendingString:fileName]];
        NSString *defaultFile = [[NSBundle mainBundle] pathForResource:@"FlurryConfig" ofType:@"plist"];
        sharedInstance.defaultInfo = [NSMutableDictionary dictionaryWithContentsOfFile:defaultFile];
    });
    return sharedInstance;
}

-(NSString *) apiKey {
    return [self.info objectForKey:@"apiKey"];
}


-(NSNumber *) sessionSeconds {
    return [self.info objectForKey:@"sessionSeconds"];
}

-(NSString *) appVersion {
    return [self.info objectForKey:@"appVersion"];
}

-(NSString *) enableCrashReport {
    NSLog(@"read crash report %@", [self.info objectForKey:@"enableCrashReport"]);
    return [self.info objectForKey:@"enableCrashReport"];
}

-(NSNumber *)age {
    return [self.info objectForKey:@"age"];
}

- (NSString *)gender {
    return [self.info objectForKey:@"gender"];
}

- (NSString *)userId {
    return [self.info objectForKey:@"userId"];
}

-(void) setApiKey:(NSString *)apiKey {
    [self.info setObject:apiKey forKey:@"apiKey"];
    [self.info writeToFile:self.getPath atomically:YES];
}

-(void) setSessionSeconds:(NSNumber *)seconds {
    [self.info setObject:seconds forKey:@"sessionSeconds"];
    [self.info writeToFile:self.getPath atomically:YES];
}

-(void) setAppVersion:(NSString *)appVersion {
    [self.info setObject:appVersion forKey:@"appVersion"];
    [self.info writeToFile:self.getPath atomically:YES];
}

-(void) setEnableCrashReport:(BOOL)isCrashReportEnabled {
    [self.info setObject:[NSNumber numberWithBool:isCrashReportEnabled] forKey:@"enableCrashReport"];
    [self.info writeToFile:self.getPath atomically:YES];
}

- (void)setAge:(NSNumber *)age {
    [self.info setObject:age forKey:@"age"];
    [self.info writeToFile:self.getPath atomically:YES];
}

- (void)setGender:(NSString *)gender {
    [self.info setObject:gender forKey:@"gender"];
    [self.info writeToFile:self.getPath atomically:YES];
}

- (void)setUserId:(NSString *)userId {
    [self.info setObject:userId forKey:@"userId"];
    [self.info writeToFile:self.getPath atomically:YES];
}

- (void)removeAge {
    [self.info removeObjectForKey:@"age"];
    [self.info writeToFile:self.getPath atomically:YES];
}

- (void)removeGender {
    [self.info removeObjectForKey:@"gender"];
    [self.info writeToFile:self.getPath atomically:YES];
}

- (void)removeUserId {
    [self.info removeObjectForKey:@"userId"];
    [self.info writeToFile:self.getPath atomically:YES];
}

- (NSString *)defaultApiKey {
    return [self.defaultInfo objectForKey:@"apiKey"];
}

- (NSString *)defaultAppVersion {
    return [self.defaultInfo objectForKey:@"appVersion"];
}

- (NSNumber *)defaultSessionSeconds {
    return [self.defaultInfo objectForKey:@"sessionSeconds"];
}

- (NSString *)defaultEnableCrashReport {
    return [self.info objectForKey:@"enableCrashReport"];
}


@end
