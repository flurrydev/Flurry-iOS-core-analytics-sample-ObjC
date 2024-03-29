//
//  Flurry.h
//  Flurry iOS Analytics Agent
//
//  Copyright (c) 2021 Yahoo. All rights reserved.
//
//	Methods in this header file are for use with Flurry Analytics

#import <UIKit/UIKit.h>
#if !TARGET_OS_WATCH
@class SKPaymentTransaction;
#endif
#if TARGET_OS_TV
@class JSContext;
#endif

#import "FlurrySessionBuilder.h"

/*!
 *  @brief Enum for payment transaction state
 */
typedef NS_ENUM(NSUInteger, FlurryPaymentTransactionState) {
    FlurryPaymentTransactionStatePurchasing NS_SWIFT_NAME(purchasing) = 0,
    FlurryPaymentTransactionStateSuccess NS_SWIFT_NAME(success),
    FlurryPaymentTransactionStateFailure NS_SWIFT_NAME(failure),
    FlurryPaymentTransactionStateRestored NS_SWIFT_NAME(restored),
    FlurryPaymentTransactionStateDeferred NS_SWIFT_NAME(deffered)
};


typedef NS_ENUM(NSUInteger, FlurryEventRecordStatus) {
    FlurryEventFailed NS_SWIFT_NAME(failed) = 0,
    FlurryEventRecorded NS_SWIFT_NAME(recorded),
    FlurryEventUniqueCountExceeded NS_SWIFT_NAME(uniqueCountExceeded),
    FlurryEventParamsCountExceeded NS_SWIFT_NAME(paramsCountExceeded),
    FlurryEventLogCountExceeded NS_SWIFT_NAME(logCountExceeded),
    FlurryEventLoggingDelayed NS_SWIFT_NAME(loggingDelayed),
    FlurryEventAnalyticsDisabled NS_SWIFT_NAME(analyticsDisabled),
    FlurryEventParametersMismatched NS_SWIFT_NAME(parametersMismatched)
};


/*!
 *  @brief Enum for logging events that occur within a syndicated app
 *  @since 6.7.0
 *
 */

typedef NS_ENUM(NSUInteger, FlurrySyndicationEvent){
    FlurrySyndicationReblog NS_SWIFT_NAME(reblog) = 0,
    FlurrySyndicationFastReblog NS_SWIFT_NAME(fastReblog),
    FlurrySyndicationSourceClick NS_SWIFT_NAME(sourceClick),
    FlurrySyndicationLike NS_SWIFT_NAME(like),
    FlurrySyndicationShareClick NS_SWIFT_NAME(shareClick),
    FlurrySyndicationPostSend NS_SWIFT_NAME(postSend)
};

extern NSString* _Nonnull const kSyndicationiOSDeepLink;
extern NSString* _Nonnull const kSyndicationAndroidDeepLink;
extern NSString* _Nonnull const kSyndicationWebDeepLink;


typedef NS_ENUM(NSUInteger, FlurryTransactionRecordStatus) {
    FlurryTransactionRecordFailed NS_SWIFT_NAME(failed) = 0,
    FlurryTransactionRecorded NS_SWIFT_NAME(recorded),
    FlurryTransactionRecordExceeded NS_SWIFT_NAME(recordExceeded),
    FlurryTransactionRecodingDisabled NS_SWIFT_NAME(recordingDisabled)
};

#if !TARGET_OS_WATCH

/*!
 *  @brief Provides all available delegates for receiving callbacks related to Flurry analytics.
 *
 *  Set of methods that allow developers to manage and take actions within
 *  different phases of App.
 *
 *  @note This class serves as a delegate for Flurry. \n
 *  For additional information on how to use Flurry's Ads SDK to
 *  attract high-quality users and monetize your user base see <a href="http://wiki.flurry.com/index.php?title=Publisher">Support Center - Publisher</a>.
 *  @author 2010 - 2014 Flurry, Inc. All Rights Reserved.
 *  @version 6.3.0
 *
 */
@protocol FlurryDelegate <NSObject>

/*!
 *  @brief Invoked when analytics session is created
 *  @since 6.3.0
 *
 *  This method informs the app that an analytics session is created.
 *
 *  @see Flurry#startSession for details on session.
 *
 *  @param info A dictionary of session information: sessionID, apiKey
 *  @note By default the callback is received on the global_queue with default priority. Optionally users can choose to receive on a specific queue by using
 * + (void)setDelegate:(nonnull id<FlurryDelegate>)delegate withCallbackQueue:(dispatch_queue_t)flurryCallbackQueue;
 */
- (void)flurrySessionDidCreateWithInfo:(nonnull NSDictionary*)info;

@end

#if TARGET_OS_IOS
/*!
 *  @brief Provides delegate method for receiving callbacks related to publisher data is fetched.
 */
@protocol FlurryFetchObserver <NSObject>

@optional

/*!
 *  @brief Invoked when publisher data is fetched
 *  @since 11.3.0
 *
 *  @param publisherData A dictionary of key-value paired configuration for publisher segmentation data, nil if data not fetched or not changed.
 */
- (void)onFetched:(NSDictionary<NSString *, NSString *> *_Nullable)publisherData;

@end
#endif

/*!
 *  @brief Provides all available methods for defining and reporting Analytics from use
 *  of your app.
 * 
 *  Set of methods that allow developers to capture detailed, aggregate information
 *  regarding the use of their app by end users.
 *  
 *  @note This class provides methods necessary for correct function of Flurry.h.
 *  For information on how to use Flurry's Ads SDK to
 *  attract high-quality users and monetize your user base see <a href="https://developer.yahoo.com/flurry/docs/howtos">Support Center - Publishers</a>.
 *
 *  @version 4.3.0
 * 
 */

@interface Flurry : NSObject {
}

#pragma mark - Pre-Session Calls

/** @name Pre-Session Calls
 *  Optional sdk settings that should be called before start session. 
 */
//@{

/*!
 *  @brief Retrieves the Flurry Agent Build Version.
 *  @since 2.7
 *
 *  This is an optional method that retrieves the Flurry Agent Version the app is running under. 
 *  It is most often used if reporting an unexpected behavior of the SDK to <a href="mailto:iphonesupport@flurry.com">
 *  Flurry Support</a>
 *
 *  @see #setLogLevel: for information on how to view debugging information on your console.
 *
 *  @return The agent version of the Flurry SDK.
 *
 */
+ (nonnull NSString *)getFlurryAgentVersion;

/*!
 *  @brief Displays an exception in the debug log if thrown during a Session.
 *  @since 2.7
 *
 *  This is an optional method that augments the debug logs with exceptions that occur during the session.
 *  You must both capture exceptions to Flurry and set debug logging to enabled for this method to
 *  display information to the console. The default setting for this method is @c NO.
 *
 *  @note This method can be called at any point in the execution of your application and
 *  the setting will take effect for SDK activity after this call.
 *
 *  @see #setLogLevel: for information on how to view debugging information on your console. \n
 *  #logError:message:exception: for details on logging exceptions. \n
 *  #logError:message:error: for details on logging errors.
 *
 *  @param value @c YES to show errors in debug logs, @c NO to omit errors in debug logs.
 */
+ (void)setShowErrorInLogEnabled:(BOOL)value
NS_SWIFT_NAME(set(showErrorInLogEnabled:));

/*!
 *  @brief Generates debug logs to console.
 *  @since 4.2.2
 *
 *  This is an optional method that displays debug information related to the Flurry SDK.
 *  display information to the console. The default setting for this method is @c FlurryLogLevelCriticalOnly.
 *
 *  @note The log level can be changed at any point in the execution of your application and
 *  the level that is set will take effect for SDK activity after this call.
 *
 *  @param value Log level
 *
 */
+ (void)setLogLevel:(FlurryLogLevel)value
NS_SWIFT_NAME(set(logLevel:));

/*!
 *  @brief An api to send gpp compliance data to Flurry on the consent string and section Ids
 *  @since 12.2.0
 *
 *  @param gppString  GPP Consent String
 *  @param gppSectionIds An array of integer values
 */

+ (void)setGppConsent:(NSString* _Nonnull)gppString gppSectionIds:(NSArray<NSNumber *>* _Nonnull) gppSectionIds
NS_SWIFT_NAME(set(gppString:gppSectionIds:));

//@}

#pragma mark - Flurry Delegate setters

/*!
 *  @brief Set Flurry delegate for callback on session creation.
 *  @since 6.3.0
 *
 * @code
 *  - (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 {
 // Optional Flurry startup methods
 // If self implements protocol, FlurryDelegate
 [Flurry setDelegate:self];
 // ....
 }
 * @endcode
 *
 
 */
+ (void)setDelegate:(nonnull id<FlurryDelegate>)delegate
NS_SWIFT_NAME(set(delegate:));

/*!
 *  @brief Set Flurry delegate for callback on session creation with a callback queue.
 *  @since 8.4.4
 *
 * @code
 *  - (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 {
 // Optional Flurry startup methods
 // If self implements protocol, FlurryDelegate
 [Flurry setDelegate:self withCallbackQueue:queue];
 // ....
 }
 * @endcode
 *
 */
+ (void)setDelegate:(nonnull id<FlurryDelegate>)delegate withCallbackQueue:(nonnull dispatch_queue_t)flurryCallbackQueue
NS_SWIFT_NAME(set(delegate:callbackQueue:));

#pragma mark - start session APIs'

/** @name startSession APIs'
 *  API to start session by passing API key, optionally passing launchOptions and/or customizing the session settings/options
 *  Only one of the API must be called to start the session
 */
//@{

/*!
 *  @brief Start a Flurry session for the project denoted by @c apiKey.
 *  @since 2.6
 * 
 *  This method serves as the entry point to Flurry Analytics collection.  It must be
 *  called in the scope of @c applicationDidFinishLaunching.  The session will continue 
 *  for the period the app is in the foreground until your app is backgrounded for the 
 *  time specified in #withSessionContinueSeconds:. If the app is resumed in that period
 *  the session will continue, otherwise a new session will begin.
 *
 *  Crash reporting will not be enabled. See #withCrashReporting: in FlurrySessionBuilder for
 *  more information.
 * 
 *  @note If testing on a simulator, please be sure to send App to background via home
 *  button. Flurry depends on the iOS lifecycle to be complete for full reporting.
 * 
 * @see #withSessionContinueSeconds: for details on setting a custom session timeout in FlurrySessionBuilder.
 *
 * @code
 *  - (void)applicationDidFinishLaunching:(UIApplication *)application 
 {
 // Optional Flurry startup methods
 [Flurry startSession:@"YOUR_API_KEY"];
 // ....
 }
 * @endcode
 * 
 * @param apiKey The API key for this project.
 */

+ (void)startSession:(nonnull NSString *)apiKey
NS_SWIFT_NAME(startSession(apiKey:));


/*!
 *  @brief Start a Flurry session for the project denoted by @c apiKey. Gather more information by passing in the launchOptions.
 *  @since 4.0.8
 *
 *  This method overloads on the #startSession: and serves as the entry point to Flurry Analytics collection.  It must be
 *  called in the scope of @c applicationDidFinishLaunching passing in the launchOptions param.
 *  The session will continue
 *  for the period the app is in the foreground until your app is backgrounded for the
 *  time specified in #withSessionContinueSeconds:. If the app is resumed in that period
 *  the session will continue, otherwise a new session will begin.
 *
 *  Crash reporting will not be enabled. See #withCrashReporting: in FlurrySessionBuilder for
 *  more information.
 *
 *  @note If testing on a simulator, please be sure to send App to background via home
 *  button. Flurry depends on the iOS lifecycle to be complete for full reporting.
 *
 * @see #withSessionContinueSeconds: for details on setting a custom session timeout in FlurrySessionBuilder.
 *
 * @code
 *  - (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 {
 // Optional Flurry startup methods
 [Flurry startSession:@"YOUR_API_KEY" withOptions:launchOptions];
 // ....
 }
 * @endcode
 *
 * @param apiKey The API key for this project.
 * @param options passed launchOptions from the applicatin's didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 
 */
+ (void) startSession:(nonnull NSString *)apiKey withOptions:(nullable id)options
NS_SWIFT_NAME(startSession(apiKey:options:));


/*!
 *  @brief Start a Flurry session for the project denoted by @c apiKey by specifying the desired session construction options.
 *  Gather more information by passing in the launchOptions.
 *
 *  @since 7.7.0
 *
 *  This method overloads on the #startSession:withOptions: and serves as the entry point to Flurry Analytics collection.  It must be
 *  called in the scope of @c applicationDidFinishLaunching passing in the launchOptions param.
 *  The session will continue
 *  for the period the app is in the foreground until your app is backgrounded for the
 *  time specified in #withSessionContinueSeconds:. If the app is resumed in that period
 *  the session will continue, otherwise a new session will begin.
 *
 *  @note If testing on a simulator, please be sure to send App to background via home
 *  button. Flurry depends on the iOS lifecycle to be complete for full reporting.
 *
 * @see #withSessionContinueSeconds: for details on setting a custom session timeout in FlurrySessionBuilder.
 *
 * @code
 *  - (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
    {
        // Optional Flurry startup methods
        FlurrySessionBuilder* builder = [[[[[FlurrySessionBuilder new] withLogLevel:FlurryLogLevelDebug]
                                                                 withCrashReporting:NO]
                                                         withSessionContinueSeconds:10]
                                                                     withAppVersion:@"0.1.2"];
 
        [Flurry startSession:@"YOUR_API_KEY" withOptions:launchOptions withSessionBuilder:sessionBuilder];
        // ....
    }
 * @endcode
 *
 * @param apiKey The API key for this project.
 * @param options passed launchOptions from the applicatin's didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 * @param sessionBuilder pass in the session builder object to specify that session construction options
 
 */
+ (void) startSession:(nonnull NSString *)apiKey withOptions:(nullable id)options withSessionBuilder:(nullable FlurrySessionBuilder*) sessionBuilder
NS_SWIFT_NAME(startSession(apiKey:options:sessionBuilder:));


/*!
 *  @brief Start a Flurry session for the project denoted by @c apiKey by specifying the desired session construction options.
 *  @since 7.7.0
 *
 *  This method overloads on the #startSession: and serves as the entry point to Flurry Analytics collection. It must be
 *  called in the scope of @c applicationDidFinishLaunching.
 *  The session will continue
 *  for the period the app is in the foreground until your app is backgrounded for the
 *  time specified in #withSessionContinueSeconds:. If the app is resumed in that period
 *  the session will continue, otherwise a new session will begin.
 *
 *  @note If testing on a simulator, please be sure to send App to background via home
 *  button. Flurry depends on the iOS lifecycle to be complete for full reporting.
 *
 * @see #withSessionContinueSeconds: for details on setting a custom session timeout in FlurrySessionBuilder.
 *
 * @code
 *  - (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
    {
        // Optional Flurry startup methods
        FlurrySessionBuilder* builder = [[[[[FlurrySessionBuilder new] withLogLevel:FlurryLogLevelDebug]
                                                                 withCrashReporting:NO]
                                                         withSessionContinueSeconds:10]
                                                                     withAppVersion:@"0.1.2"];
 
        [Flurry startSession:@"YOUR_API_KEY" withSessionBuilder:sessionBuilder];
        // ....
    }
 * @endcode
 *
 * @param apiKey The API key for this project.
 * @param sessionBuilder pass in the session builder object to specify that session construction options
 */
+ (void) startSession:(nonnull NSString *)apiKey withSessionBuilder:(nullable FlurrySessionBuilder *)sessionBuilder
NS_SWIFT_NAME(startSession(apiKey:sessionBuilder:));
//@}

#pragma mark - Session Details

/*!
 *  @brief Returns true if a session currently exists and is active.
 *  @since 6.0.0
 *
 * @code
 *  - (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
    {
        // Optional Flurry startup methods
        [Flurry activeSessionExists];
        // ....
    }
 * @endcode
 *
 */
+ (BOOL)activeSessionExists;

/*!
 *  @brief Returns the session ID of the current active session.
 *  @since 6.3.0
 *
 * @code
 *  - (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
    {
        // Optional Flurry startup methods
        [Flurry getSessionID];
        // ....
    }
 * @endcode
 *
 
 */
+ (nonnull NSString*)getSessionID;

#pragma mark - Manual session pausing

#if !TARGET_OS_TV
/*!
 *  @brief Pauses a Flurry session left running in background.
 *  @since 4.2.2
 *
 *  This method can be called when application finished all background tasks (such as playing music) to pause session.
 *
 *  @code
 *  - (void)allBackgroundTasksFinished
    {
        // ....
        [Flurry pauseBackgroundSession];
        // ....
    }
 *  @endcode
 *
 */
+ (void)pauseBackgroundSession;
#endif

#pragma mark - User Info Setters and Getters

/** @name User Info
 *  Methods to set user information.
 */
//@{

/*!
 *  @brief Assign a unique id for a user in your app.
 *  @since 2.7
 *
 *  @note Please be sure not to use this method to pass any private or confidential information
 *  about the user.
 *
 *  @param userID The app id for a user.
 */
+ (void)setUserID:(nullable NSString *)userID
NS_SWIFT_NAME(set(userId:));

/*!
 *  @brief Set your user's age in years.
 *  @since 2.7
 *
 *  Use this method to capture the age of your user. Only use this method if you collect this
 *  information explictly from your user (i.e. - there is no need to set a default value).
 *
 *  @note The age is aggregated across all users of your app and not available on a per user
 *  basis.
 *
 *  @param age Reported age of user.
 *
 */
+ (void)setAge:(int)age
NS_SWIFT_NAME(set(age:));

/*!
 *  @brief Set your user's gender.
 *  @since 2.7
 *
 *  Use this method to capture the gender of your user. Only use this method if you collect this
 *  information explictly from your user (i.e. - there is no need to set a default value). Allowable
 *  values are @c @"m" or @c @"f"
 *
 *  @note The gender is aggregated across all users of your app and not available on a per user
 *  basis.
 *
 *  @param gender Reported gender of user.
 *
 */
+ (void)setGender:(nonnull NSString *)gender
NS_SWIFT_NAME(set(gender:)); // user's gender m or f

//@}

/** @name Location Reporting
 *  Opt-out Methods for setting location information.
 */
//@{
/*!
 *  @brief Turn on/off location information of the session (default is on).
 *  @since 8.4.0
 *
 *  Use CLLocationManager to start the location tracking of the session. Flurry does not
 *  prompt users for location permission, we fetch the available location in device daemon.
 *
 *  @note Only the last location in cache is captured per session. \n
 *  Regardless of accuracy specified, the Flurry SDK will only report location at city level or higher. \n
 *  Location is aggregated across all users of your app and not available on a per user basis. \n
 *  This information should only be captured if it is germaine to the use of your app.
 *
 *  @code
 CLLocationManager *locationManager = [[CLLocationManager alloc] init];
 [locationManager startUpdatingLocation];
 *  @endcode
 *
 *  It is on by default. After starting the location manager, you can turn off
 *  opt-out location tracking by calling this method.
 *
 *  @code
 [Flurry  trackPreciseLocation:NO];
 *  @endcode
 *  @param state The boolean to switch on/off for location tracking
 *  @return a boolean, if the state is YES, it tests device/app permission. If permission
 *   is granted, it returns NO. If permission is valid, it returns YES. If the
 *   state is NO, it always returns NO.
 */
+ (BOOL)trackPreciseLocation:(BOOL)state;

/*!
 *  @brief Enables implicit recording of Apple Store transactions.
 *  @since 7.9.0
 *
 *  This method needs to be called before any transaction is finialized.
 *  @note: Needs a 'required' dependency on StoreKit for this API to function correctly.
 *
 *  @param value YES to enable transaction logging, NO to stop transaction logging.
 *
 */
+ (void) setIAPReportingEnabled:(BOOL)value
NS_SWIFT_NAME(set(iapReportingEnabled:));


#pragma mark - Add sessionOrigin, originAttributes and sessionProperties

/*!
 *  @brief Adds an session origin attached to each session specified by @c sessionOriginName.
 *  @since 6.5.0
 *
 *  This method allows you to specify session origin for each session. This is different than #addOrigin:withVersion: (originAttributes) which is used for third party
 *  wrappers after every session start.
 *
 *  @code
 *  - (void)interestingMethod
 {
 // ... after calling startSession
 [Flurry addSessionOrigin:@"facebuk"];
 // more code ...
 }
 *  @endcode
 *
 *  @param sessionOriginName    Name of the origin.
 */
+ (void)addSessionOrigin:(nonnull NSString *)sessionOriginName
NS_SWIFT_NAME(add(sessionOriginName:));

/*!
 *  @brief Adds an session origin and deep link attached to each session specified by @c sessionOriginName and  @c deepLink.
 *  @since 6.5.0
 *
 *  This method allows you to specify session origin and deep link for each session. This is different than addOrigin:withVersion: (originAttributes) which is used for third party
 *  wrappers after every session start.
 *
 *
 *  @code
 *  - (void)interestingMethod
    {
        // ... after calling startSession
        [Flurry addSessionOrigin:@"facebuk" withDeepLink:@"https://www.facebuk.com/xyz/"];
        // more code ...
    }
 *  @endcode
 *
 *  @param sessionOriginName    Name of the origin.
 *  @param deepLink             Url of the deep Link.
 */
+ (void)addSessionOrigin:(nonnull NSString *)sessionOriginName
            withDeepLink:(nonnull NSString *)deepLink
NS_SWIFT_NAME(add(sessionOriginName:deepLink:));

/*!
 *  @brief Adds a custom parameterized session parameters @c parameters.
 *  @since 6.5.0
 *
 *  This method allows you to associate parameters with a session. Parameters
 *  are valuable as they allow you to store characteristics of a session.
 *
 *  @note You should not pass private or confidential information about your origin info in a
 *  custom origin. \n
 *  A maximum of 10 parameter names may be associated with any origin. Sending
 *  over 10 parameter names with a single origin will result in no parameters being logged
 *  for that origin.
 *
 *
 *  @code
 * - (void)interestingMethod
    {
        // ... after calling startSession
         NSDictionary *params =
         [NSDictionary dictionaryWithObjectsAndKeys:@"Session Info Item", // Parameter Value
         @"Session Info Item Key", // Parameter Name
         nil];
         [Flurry sessionProperties:params];
         // more code ...
    }
 *  @endcode
 *
 *  @param parameters An immutable copy of map containing Name-Value pairs of parameters.
 */
+ (void)sessionProperties:(nonnull NSDictionary *)parameters;

/*!
 *  @brief Adds an SDK origin specified by @c originName and @c originVersion.
 *  @since 5.0.0
 *
 *  This method allows you to specify origin within your Flurry SDK wrapper. As a general rule
 *  you should capture all the origin info related to your wrapper for Flurry SDK after every session start.
 *
 *  @see #addOrigin:withVersion:withParameters: for details on reporting origin info with parameters. \n
 *
 *  @code
 *  - (void)interestingSDKWrapperLibraryfunction
 {
     // ... after calling startSession
     [Flurry addOrigin:@"Interesting_Wrapper" withVersion:@"1.0.0"];
     // more code ...
 }
 *  @endcode
 *
 *  @param originName    Name of the origin.
 *  @param originVersion Version string of the origin wrapper
 */
+ (void)addOrigin:(nonnull NSString *)originName
      withVersion:(nonnull NSString *)originVersion
NS_SWIFT_NAME(add(originName:originVersion:));

/*!
 *  @brief Adds a custom parameterized origin specified by @c originName with @c originVersion and @c parameters.
 *  @since 5.0.0
 *
 *  This method overloads #addOrigin to allow you to associate parameters with an origin attribute. Parameters
 *  are valuable as they allow you to store characteristics of an origin.
 *
 *  @note You should not pass private or confidential information about your origin info in a
 *  custom origin. \n
 *  A maximum of 9 parameter names may be associated with any origin. Sending
 *  over 10 parameter names with a single origin will result in no parameters being logged
 *  for that origin.
 *
 *
 *  @code
 *  - (void)userPurchasedSomethingCool
    {
        NSDictionary *params =
        [NSDictionary dictionaryWithObjectsAndKeys:@"Origin Info Item", // Parameter Value
            @"Origin Info Item Key", // Parameter Name
            nil];
        // ... after calling startSession
         [Flurry addOrigin:@"Interesting_Wrapper" withVersion:@"1.0.0" withParameters:params];
        // more code ...
    }
 *  @endcode
 *
 *  @param originName    Name of the origin.
 *  @param originVersion Version string of the origin wrapper
 *  @param parameters An immutable copy of map containing Name-Value pairs of parameters.
 */
+ (void)addOrigin:(nonnull NSString *)originName
      withVersion:(nonnull NSString*)originVersion
   withParameters:(nullable NSDictionary *)parameters
NS_SWIFT_NAME(add(originName:originVersion:parameters:));

#pragma mark - Event Logging

/** @name Event and Error Logging
 *  Methods for reporting custom events and errors during the session. 
 */
//@{

/*!
 *  @brief Records a custom event specified by @c eventName.
 *  @since 2.8.4
 * 
 *  This method allows you to specify custom events within your app.  As a general rule
 *  you should capture events related to user navigation within your app, any action 
 *  around monetization, and other events as they are applicable to tracking progress
 *  towards your business goals. 
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event. \n
 *  Where applicable, you should make a concerted effort to use timed events with
 *  parameters (#logEvent:withParameters:timed:) or events with parameters 
 *  (#logEvent:withParameters:). This provides valuable information around the time the user
 *  spends within an action (e.g. - time spent on a level or viewing a page) or characteristics
 *  of an action (e.g. - Buy Event that has a Parameter of Widget with Value Golden Sword).
 * 
 *  @see #logEvent:withParameters: for details on storing events with parameters. \n
 *  #logEvent:timed: for details on storing timed events. \n
 *  #logEvent:withParameters:timed: for details on storing timed events with parameters. \n
 *  #endTimedEvent:withParameters: for details on stopping a timed event and (optionally) updating 
 *  parameters.
 *
 *  @code
 *  - (void)interestingAppAction 
    {
        [Flurry logEvent:@"Interesting_Action"];
        // Perform interesting action
    }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 *
 *  @return enum FlurryEventRecordStatus for the recording status of the logged event.
 */
+ (FlurryEventRecordStatus)logEvent:(nonnull NSString *)eventName
NS_SWIFT_NAME(log(eventName:));

/*!
 *  @brief Records a custom parameterized event specified by @c eventName with @c parameters.
 *  @since 2.8.4
 * 
 *  This method overloads #logEvent to allow you to associate parameters with an event. Parameters
 *  are extremely valuable as they allow you to store characteristics of an action. For example,
 *  if a user purchased an item it may be helpful to know what level that user was on.
 *  By setting this parameter you will be able to view a distribution of levels for the purcahsed
 *  event on the <a href="http://dev.flurry.com">Flurrly Dev Portal</a>.
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event. \n
 *  A maximum of 10 parameter names may be associated with any event. Sending
 *  over 10 parameter names with a single event will result in no parameters being logged
 *  for that event. You may specify an infinite number of Parameter values. For example,
 *  a Search Box would have 1 parameter name (e.g. - Search Box) and many values, which would
 *  allow you to see what values users look for the most in your app. \n
 *  Where applicable, you should make a concerted effort to use timed events with
 *  parameters (#logEvent:withParameters:timed:). This provides valuable information 
 *  around the time the user spends within an action (e.g. - time spent on a level or 
 *  viewing a page).
 * 
 *  @see #logEvent:withParameters:timed: for details on storing timed events with parameters. \n
 *  #endTimedEvent:withParameters: for details on stopping a timed event and (optionally) updating 
 *  parameters.
 *
 *  @code
 *  - (void)userPurchasedSomethingCool 
    {
        NSDictionary *params =
        [NSDictionary dictionaryWithObjectsAndKeys:@"Cool Item", // Parameter Value
            @"Item Purchased", // Parameter Name
            nil];
        [Flurry logEvent:@"Something Cool Purchased" withParameters:params];
        // Give user cool item
    }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 *  @param parameters An immutable copy of map containing Name-Value pairs of parameters.
 *
 *  @return enum FlurryEventRecordStatus for the recording status of the logged event.
 */
+ (FlurryEventRecordStatus)logEvent:(nonnull NSString *)eventName
                     withParameters:(nullable NSDictionary *)parameters
NS_SWIFT_NAME(log(eventName:parameters:));

/*!
 *  @brief Records a syndicated event specified by @c syndicationEvent.
 *  @since 6.7.0
 *
 *  This method is excusively for use by the Tumblr App, calls from others app will be ignored.
 *
 *  @code
 - (void) reblogButtonHandler
 {
 [Flurry logEvent:Reblog syndicationID:@"123", parameters:nil];
 // Perform
 }
 *  @endcode
 *
 *  @param syndicationEvent syndication event.
 *  @param syndicationID syndication ID that is associated with the event
 *  @param parameters use this to pass in syndication parameters such as
 *         kSyndicationiOSDeepLink, kSyndicationAndroidDeepLink, kSyndicationWebLinkDeepLink
 *
 *  @return enum FlurryEventRecordStatus for the recording status of the logged event.
 */
+ (FlurryEventRecordStatus) logEvent:(FlurrySyndicationEvent) syndicationEvent
                       syndicationID:(nonnull NSString *) syndicationID
                          parameters:(nullable NSDictionary *) parameters
NS_SWIFT_NAME(log(syndicationEvent:syndicationID:parameters:));

/*!
 *  @brief Records an Apple Store transaction.
 *  @since 7.8.0
 *
 *  This method needs to be called before a transaction is finished and finalized.
 *  @note: Needs a 'required' dependency on StoreKit for this API to function correctly.
 *
 *  @param transaction an SKPaymentTransaction.
 *  @param statusCallback a callback gettign called when the status of  ID that is associated with the event
 *
 */
+ (void) logPaymentTransaction:(nonnull SKPaymentTransaction *)transaction
                statusCallback:(nullable void(^)(FlurryTransactionRecordStatus))statusCallback
NS_SWIFT_NAME(log(transaction:statusCallback:));


/*!
 *  @brief Records Apple store IAP transaction params and user defined transaction params manually.
 *  @since 12.0.0
 *
 *  @param transactionId a string Id for this IAP transaction
 *  @param productId a string Id for this IAP transaction product
 *  @param quantity an integer representation of quantity of items purchased
 *  @param price a float representation of price of the item
 *  @param currency a string representation of currency of the transaction
 *  @param productName a string representation of product name
 *  @param transactionState an enum to convert transaction state to integer: 0:Purchasing, 1:Success, 2:Failure, 3:Restored, 4:Deferred
 *  @param transactionParams a dictionary of user defined transaction params to record
 *  @param statusCallback a callback gettign called when the status of ID that is associated with the event
 *
 */

+ (void) logPaymentTransactionWithTransactionId:(nonnull NSString *)transactionId
                                                  productId:(nonnull NSString *)productId
                                                   quantity:(NSUInteger)quantity
                                                      price:(double)price
                                                   currency:(nonnull NSString *)currency
                                                productName:(nonnull NSString *)productName
                                           transactionState:(FlurryPaymentTransactionState)transactionState
                                          userDefinedParams:(nullable NSDictionary *)transactionParams
                                             statusCallback:(nullable void(^)(FlurryTransactionRecordStatus))statusCallback
NS_SWIFT_NAME(log(transactionId:productId:quantity:price:currency:productName:transactionState:transactionParams:statusCallback:));

#pragma mark - Timed Event Logging

/*!
 *  @brief Records a timed event specified by @c eventName.
 *  @since 2.8.4
 * 
 *  This method overloads #logEvent to allow you to capture the length of an event. This can
 *  be extremely valuable to understand the level of engagement with a particular action. For
 *  example, you can capture how long a user spends on a level or reading an article.
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event. \n
 *  Where applicable, you should make a concerted effort to use parameters with your timed 
 *  events (#logEvent:withParameters:timed:). This provides valuable information 
 *  around the characteristics of an action (e.g. - Buy Event that has a Parameter of Widget with 
 *  Value Golden Sword).
 * 
 *  @see #logEvent:withParameters:timed: for details on storing timed events with parameters. \n
 *  #endTimedEvent:withParameters: for details on stopping a timed event and (optionally) updating 
 *  parameters.
 *
 *  @code
 *  - (void)startLevel 
    {
        [Flurry logEvent:@"Level Played" timed:YES];
        // Start user on level
    }
 
    - (void)endLevel
    {
        [Flurry endTimedEvent:@"Level Played" withParameters:nil];
        // User done with level
    }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 *  @param timed Specifies the event will be timed..
 *
 *  @return enum FlurryEventRecordStatus for the recording status of the logged event.
 */
+ (FlurryEventRecordStatus)logEvent:(nonnull NSString *)eventName timed:(BOOL)timed
NS_SWIFT_NAME(log(eventName:timed:));

/*!
 *  @brief Records a custom parameterized timed event specified by @c eventName with @c parameters.
 *  @since 2.8.4
 * 
 *  This method overloads #logEvent to allow you to capture the length of an event with parameters.
 *  This can be extremely valuable to understand the level of engagement with a particular action 
 *  and the characteristics associated with that action. For example, you can capture how long a user 
 *  spends on a level or reading an article. Parameters can be used to capture, for example, the
 *  author of an article or if something was purchased while on the level.
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event.
 *
 *  @see #endTimedEvent:withParameters: for details on stopping a timed event and (optionally) updating 
 *  parameters.
 *
 *  @code
 *  - (void)startLevel 
    {
        NSDictionary *params =
        [NSDictionary dictionaryWithObjectsAndKeys:@"100", // Parameter Value
            @"Current Points", // Parameter Name
            nil];
 
        [Flurry logEvent:@"Level Played" withParameters:params timed:YES];
        // Start user on level
    }
 
    - (void)endLevel
    {
        // User gained additional 100 points in Level
        NSDictionary *params =
            [NSDictionary dictionaryWithObjectsAndKeys:@"200", // Parameter Value
                @"Current Points", // Parameter Name
                nil];
        [Flurry endTimedEvent:@"Level Played" withParameters:params];
        // User done with level
    }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 *  @param parameters An immutable copy of map containing Name-Value pairs of parameters.
 *  @param timed Specifies the event will be timed..
 *
 *  @return enum FlurryEventRecordStatus for the recording status of the logged event.
 */
+ (FlurryEventRecordStatus)logEvent:(nonnull NSString *)eventName withParameters:(nullable NSDictionary *)parameters timed:(BOOL)timed
NS_SWIFT_NAME(log(eventName:parameters:timed:));

/*!
 *  @brief Ends a timed event specified by @c eventName and optionally updates parameters with @c parameters.
 *  @since 2.8.4
 * 
 *  This method ends an existing timed event.  If parameters are provided, this will overwrite existing
 *  parameters with the same name or create new parameters if the name does not exist in the parameter
 *  map set by #logEvent:withParameters:timed:.
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event. \n
 *  If the app is backgrounded prior to ending a timed event, the Flurry SDK will automatically
 *  end the timer on the event. \n 
 *  #endTimedEvent:withParameters: is ignored if called on a previously
 *  terminated event.
 *
 *  @see #logEvent:withParameters:timed: for details on starting a timed event with parameters.
 *
 *  @code
 *  - (void)startLevel 
    {
        NSDictionary *params =
            [NSDictionary dictionaryWithObjectsAndKeys:@"100", // Parameter Value
            @"Current Points", // Parameter Name
        nil];
 
    [Flurry logEvent:@"Level Played" withParameters:params timed:YES];
    // Start user on level
    }
 
    - (void)endLevel
    {
        // User gained additional 100 points in Level
        NSDictionary *params =
            [NSDictionary dictionaryWithObjectsAndKeys:@"200", // Parameter Value
                @"Current Points", // Parameter Name
                nil];
        [Flurry endTimedEvent:@"Level Played" withParameters:params];
        // User done with level
    }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 *  @param parameters An immutable copy of map containing Name-Value pairs of parameters.
 */
+ (void)endTimedEvent:(nonnull NSString *)eventName withParameters:(nullable NSDictionary *)parameters
NS_SWIFT_NAME(endTimedEvent(eventName:parameters:));    // non-nil parameters will update the parameters

#pragma mark - Exceptions Logging

/*!
 *  @brief Records an app exception. Commonly used to catch unhandled exceptions.
 *  @since 2.7
 *
 *  This method captures an exception for reporting to Flurry. We recommend adding an uncaught
 *  exception listener to capture any exceptions that occur during usage that is not
 *  anticipated by your app.
 *
 *  @see #logError:message:error: for details on capturing errors.
 *
 *  @code
 *  - (void) uncaughtExceptionHandler(NSException *exception)
 {
 [Flurry logError:@"Uncaught" message:@"Crash!" exception:exception];
 }
 
 - (void)applicationDidFinishLaunching:(UIApplication *)application
 {
 NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
 [Flurry startSession:@"YOUR_API_KEY"];
 // ....
 }
 *  @endcode
 *
 *  @param errorID Name of the error.
 *  @param message The message to associate with the error.
 *  @param exception The exception object to report.
 */
+ (void)logError:(nonnull NSString *)errorID
         message:(nullable NSString *)message
       exception:(nullable NSException *)exception
NS_SWIFT_NAME(log(errorId:message:exception:));

/*!
 *  @brief Records an app exception. Commonly used to catch unhandled exceptions.
 *  @since 8.4.0
 *
 *  This method overloads on logError:message:exception: to capture an exception with parameters for reporting to Flurry. We recommend adding an uncaught
 *  exception listener to capture any exceptions that occur during usage that is not
 *  anticipated by your app.
 *
 *  @see #logError:message:error:withParameters: for details on capturing errors.
 *
 *  @code
 *  - (void) uncaughtExceptionHandler(NSException *exception)
 {
 NSDictionary* crashParameters =  [NSDictionary dictionaryWithObjectsAndKeys:@"AppVersion", @"3.2", nil];
 [Flurry logError:@"Uncaught" message:@"Crash!" exception:exception withParameters:crashParameters];
 }
 
 - (void)applicationDidFinishLaunching:(UIApplication *)application
 {
 NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
 [Flurry startSession:@"YOUR_API_KEY"];
 // ....
 }
 *  @endcode
 *
 *  @param errorID Name of the error.
 *  @param message The message to associate with the error.
 *  @param exception The exception object to report.
 *  @param parameters Custom parameters associated with the exception
 */
+ (void)logError:(nonnull NSString *)errorID
         message:(nullable NSString *)message
       exception:(nullable NSException *)exception
  withParameters:(nullable NSDictionary*)parameters
NS_SWIFT_NAME(log(errorId:message:exception:parameters:));

#pragma mark - Error Logging

/*!
 *  @brief Records an app error for reporting to Flurry.
 *  @since 2.7
 *
 *  @see #logError:message:exception: for details on capturing exceptions.
 *
 *  @code
 *  - (void)webView:(WKWebView *)webView didFailNavigation:(WKNavigation *)navigation withError:(NSError *)error;
 * {
    [Flurry logError:@"WebView No Load" message:[error localizedDescription] error:error];
    }
 *  @endcode
 *
 *  @param errorID Name of the error.
 *  @param message The message to associate with the error.
 *  @param error The error object to report.
 */
+ (void)logError:(nonnull NSString *)errorID
         message:(nullable NSString *)message
           error:(nullable NSError *)error
NS_SWIFT_NAME(log(errorId:message:error:));

/*!
 *  @brief Records an app error.
 *  @since 8.4.0
 *  This method overloads on logError:message:error: to capture an error for reporting to Flurry.
 *
 *  @see #logError:message:exception:withParameters: for details on capturing exceptions.
 *
 *  @code
 *  - (void)webView:(WKWebView *)webView didFailNavigation:(WKNavigation *)navigation withError:(NSError *)error;
 {
 [Flurry logError:@"WebView No Load" message:[error localizedDescription] error:error];
 }
 *  @endcode
 *
 *  @param errorID Name of the error.
 *  @param message The message to associate with the error.
 *  @param error The error object to report.
 *  @param parameters Custom parameters associated with the error
 */
+ (void)logError:(nonnull NSString *)errorID
         message:(nullable NSString *)message
           error:(nullable NSError *)error
  withParameters:(nullable NSDictionary*)parameters
NS_SWIFT_NAME(log(errorId:message:error:parameters:));

/*!
 *  @brief Leave a breadcrumb.
 *  @since 8.4.0
 *  This method captures breadcrumbs of 250 characters. The last 207 recorded
 *  breadcrumbs are included in crash and error logs.
 *  Breadcrumbs are reset at every application launch.
 *
 *  @code
 *  - (void)webView:(WKWebView *)webView didFailNavigation:(WKNavigation *)navigation withError:(NSError *)error;
 {
 [Flurry leaveBreadcrumb:@"WebView not loading"];
 }
 *  @endcode
 *
 *  @param breadcrumb string.
 *
 */
+ (void)leaveBreadcrumb:(nonnull NSString*)breadcrumb;
//@}

#pragma mark - TVML JSContext

#if TARGET_OS_TV
/*!
 *  @brief Registers the TVML's JSContext with the Flurry SDK.
 *  @since 1.0.0
 *  
 *
 *  appController The TVApplicationController object
 *  jsContext The JavaScript context object passed in
 *
 *  This method is exclusively for use by the Client-Server TV apps. This method will internally register
 *  JavaScript APIs exposed on the TVJS domain with the Flurry SDK. The JavaScript methods available are:
 *
 *  Flurry.logEvent(eventId: string);
 *  Flurry.logEvent(eventId: string, timed: boolean);
 *  Flurry.logEvent(eventId: string, parameters: object);
 *  Flurry.logEvent(eventId: string, parameters: object, timed: boolean);
 *
 *  Flurry.endTimedEvent(eventId: string);
 *  Flurry.endTimedEvent(eventId: string, parameters: object);
 *
 *  Flurry.onError(errorId: string, message: string, errorClass: string);
 *  Flurry.onError(errorId: string, message: string, errorClass: string, errorParams: object);
 *
 *  Flurry.setAge(age: number);
 *  Flurry.setGender(gender: string);
 *  Flurry.setUserId(userId: string);
 *
 *  Flurry.setSessionOrigin(originName: string, deepLink: string);
 *  Flurry.addOrigin(originName: string, originVersion: string);
 *  Flurry.addOrigin(originName: string, originVersion: string, originParameters: object);
 *  Flurry.addSessionProperty(name: string, value: string);
 *
 *  Flurry.setIAPReportingEnabled(enableIAP: boolean);
 *  Flurry.getVersions(): object;
 *
 *  Deprecated TVML JavaScript APIs:
 *
 *  flurryLogEvent({String} eventName)
 *  flurryLogEvent({String} eventName, {object} params)
 *  flurryLogTimedEvent({String} eventName)
 *  flurryLogTimedEvent({String} eventName, {object} params)
 *  flurryEndTimedEvent({String} eventName, {object} params)
 *  flurryLogError({String} eventName, {String} message, {object} error)
 *  -> error : {
 *              errorDomain: {String},
                errorID: {Number},
                userInfo: {object}
 *              }
 *  flurrySetUserID({String} userID)
 *  flurrySetGender({String} gender)
 *  flurrySetAge({Number} age)
 *
 *  @code
 - (void)appController:(TVApplicationController *)appController evaluateAppJavaScriptInContext:(JSContext *)jsContext {
    [Flurry registerJSContextWithContext:jsContext];
 }
 *  @endcode
 * 
 *  @param  jscontext JavaScript context passed in by the -appController:evaluateAppJavaScriptInContext method
 */
 
+ (void)registerJSContextWithContext:(JSContext * _Nonnull)jscontext;
#endif

#pragma mark - Privacy dashboard

/*!
 *  @brief Open privacy dashboard in Safari Browser async with a completion handler callback
 *  @since 8.5.0
 *
 *  This method is used to open a web page of privacy dashboard in external browser for user to access and edit their data under the scope of GDPR, in the callback, you are able to check whether privacy dashboard is successfully opened, and apply fallback logics.
 *  @note: Call this method after invoking #startSession:
 *
 *  @param completionHandler a callback getting called when SDK finishes the attempt to openURL the privacy dashboard, the success boolean provided for checks and fallbacks.
 *
 */
+ (void)openPrivacyDashboard:(nullable void(^)(BOOL success))completionHandler;

#if TARGET_OS_IOS
#pragma mark - Publisher Segmentation

/*!
 *  @brief indicate whether the publisher data is fetched and ready to use
 *  @since 11.3.0
 *  @return YES if the publisher segmentation data is fetched and ready to use
 */
+ (BOOL)isFetchFinished;

/*!
 *  @brief register as an observer with given execution queue
 *  @since 11.3.0
 *  @param observer an observing object
 *  @param queue the execution queue on which the observer callbacks will be executed
 */
+ (void)registerFetchObserver:(id<FlurryFetchObserver> _Nonnull)observer withExecutionQueue:(dispatch_queue_t _Nonnull)queue
NS_SWIFT_NAME(registerFetchObserver(_:executionQueue:));

/*!
 *  @brief unregister as an observer
 *  @Since 11.3.0
 *  @param observer an observing object
 */
+ (void)unregisterFetchObserver:(id<FlurryFetchObserver> _Nonnull)observer;

/*!
 *  @brief Retrive the fetched publisher data
 *  @Since 11.3.0
 *  @return the key-value paired configuration for publisher segmentation data. If not yet fetched,
 *  will return the cached segments data.
 */
+ (nullable NSDictionary<NSString *, NSString *> *)getPublisherData;

/*!
 *  @brief Fetch the publisher data
 *  @Since 11.3.0
 *  Fetch will trigger an async call to the server.  Server has a throttle
 *  where when the user calls fetch Config many times in a row, it will
 *  basically do a no-op.
 */
+ (void)fetch;

#endif

/*!
 *  @brief Explicitly specifies the App Version that Flurry will use to group Analytics data.
 *  @since 12.0.0
 *
 *  This is a method that overrides the App Version Flurry uses for reporting. Flurry will
 *  use the CFBundleVersion in your info.plist file when this method is not invoked.
 *
 *  @note There is a maximum of 605 versions allowed for a single app.
 *
 *  @param version The custom version name.
 */
+ (void)setAppVersion:(nonnull NSString *)version
NS_SWIFT_NAME(set(appVersion:));

/*!
 *  @brief Set the timeout for expiring a Flurry session.
 *  @since 12.0.0
 *
 *  This is a method that sets the time the app may be in the background before
 *  starting a new session upon resume.  The default value for the session timeout is 10
 *  seconds in the background.
 *
 *  @param seconds The time in seconds to set the session timeout to.
 */

+ (void)setSessionContinueSeconds:(int)seconds
NS_SWIFT_NAME(set(sessionContinueSeconds:));

/*!
 *  @brief Enables opting out of background sessions being counted towards total sessions.
 *  @since 12.0.0
 *
 *  @param value @c NO to opt out of counting background sessions towards total sessions.
 *  The default value for the session is @c YES
 */


+ (void)setCountBackgroundSessions:(BOOL)value
NS_SWIFT_NAME(set(countBackgroundSessions:));


/*!
 *  @brief indicates whether a Flurry session has been initialized
 *  @since 12.0.0
 *
 *  @return YES if a Flurry session has been initialized and is actively running
 */
+ (BOOL)isInitialized;


@end

#endif
