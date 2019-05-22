//
//  FlurryAnalyticsConfiguration.h
//  FlurryCoreAnalyticsSampleApp_Obj
//
//  Created by Yilun Xu on 10/4/18.
//  Copyright © 2018 Flurry. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FlurryAnalyticsConfiguration : NSObject

+ (id) sharedInstance;

- (NSString *) apiKey;
- (NSNumber *) sessionSeconds;
- (NSString *) appVersion;
- (NSString *) enableCrashReport;

- (NSString *) defaultApiKey;
- (NSNumber *) defaultSessionSeconds;
- (NSString *) defaultAppVersion;
- (NSString *) defaultEnableCrashReport;


- (NSString *) getPath;
- (NSNumber *) age;
- (NSString *) gender;
- (NSString *) userId;

-(void) setApiKey: (NSString *) apiKey;
-(void) setSessionSeconds: (NSNumber *) seconds;
-(void) setAppVersion: (NSString *) appVersion;
-(void) setEnableCrashReport: (BOOL) isCrashReportEnabled;
-(void) setAge: (NSNumber *) age;
-(void) setGender: (NSString *) gender;
-(void) setUserId: (NSString *) userId;

-(void) removeAge;
-(void) removeGender;
-(void) removeUserId;


@end
