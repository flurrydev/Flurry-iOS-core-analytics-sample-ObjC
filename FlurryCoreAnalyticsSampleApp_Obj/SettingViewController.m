//
//  SettingViewController.m
//  FlurryCoreAnalyticsSampleApp_Obj
//
//  Created by Yilun Xu on 10/4/18.
//  Copyright © 2018 Flurry. All rights reserved.
//

#import "SettingViewController.h"
#import "FlurryAnalyticsConfiguration.h"
#import "Flurry.h"

static NSString * const fileName = @"/setting.plist";

@interface SettingViewController () {
    NSMutableDictionary *settingDictionary;
    NSArray *genders;
    FlurryAnalyticsConfiguration *config;
    UIAlertController *controller;
}

@end

@implementation SettingViewController

@synthesize apiKeyTextField;
@synthesize sessionSecondsTextField;
@synthesize appVersionTextField;
@synthesize enableCrashReportSwitch;
@synthesize ageTextField;
@synthesize genderTextField;
@synthesize userIdTextField;

- (void)viewDidLoad {
    [super viewDidLoad];
    [self showDetail];
    
}

- (void)viewDidAppear:(BOOL)animated {
    [self showDetail];
}

- (void)showDetail{
    NSString *path = [self getPath];
    
    settingDictionary = [NSMutableDictionary dictionaryWithContentsOfFile:path];
    config = [FlurryAnalyticsConfiguration sharedInstance];
    
    
    // showing setting in view controller
    apiKeyTextField.text = [config apiKey];
    sessionSecondsTextField.text = [[config sessionSeconds] description];
    appVersionTextField.text = [config appVersion];
    enableCrashReportSwitch.on = [[NSString stringWithFormat:@"%@", [config enableCrashReport]] isEqualToString:@"0"] ? NO : YES;
    
    if (config.gender != nil) {
        genderTextField.text = [config gender];
    }
    if (config.userId != nil) {
        userIdTextField.text = [config userId];
    }
    if (config.age != nil) {
        ageTextField.text = [[config age] description];
    }
    
    
    
    // set picker
    genders = @[@"", @"Female", @"Male"];
    UIPickerView *picker = [[UIPickerView alloc] init];
    picker.delegate = self;
    picker.dataSource = self;
    picker.showsSelectionIndicator = YES;
    [genderTextField setInputView:picker];
    
    
    
    apiKeyTextField.delegate = self;
    [apiKeyTextField setReturnKeyType:UIReturnKeyDone];
    sessionSecondsTextField.delegate = self;
    [sessionSecondsTextField setReturnKeyType:UIReturnKeyDone];
    appVersionTextField.delegate = self;
    [appVersionTextField setReturnKeyType:UIReturnKeyDone];
    ageTextField.delegate = self;
    [ageTextField setReturnKeyType:UIReturnKeyDone];
    userIdTextField.delegate = self;
    [userIdTextField setReturnKeyType:UIReturnKeyDone];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSString *) docsDir {
    return [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)objectAtIndex:0];
}

- (NSString *) getPath {
    return [[self docsDir]stringByAppendingString:fileName];
}


- (IBAction)start:(id)sender {
    // using default value if some fields are empty
    if (![self isApiKeyEmpty]) {
        [config setApiKey:apiKeyTextField.text];
    } else {
        [config setApiKey:config.defaultApiKey];
    }
    if (![self isAppVersionEmpty]) {
        [config setAppVersion:appVersionTextField.text];
    } else {
        [config setApiKey:config.defaultAppVersion];
    }
    [config setEnableCrashReport:enableCrashReportSwitch.on];
    NSNumberFormatter *formatter = [[NSNumberFormatter alloc] init];
    formatter.numberStyle = NSNumberFormatterDecimalStyle;
    if (![self isSessionSecondsEmpty]) {
        [config setSessionSeconds: [formatter numberFromString:sessionSecondsTextField.text]];
    } else {
        [config setSessionSeconds:[formatter numberFromString:[config.defaultSessionSeconds description]]];
    }
    
    if (ageTextField.text && ageTextField.text.length > 0) {
        [config setAge:[formatter numberFromString:ageTextField.text]];
    } else {
        [config removeAge];
    }
    if (userIdTextField.text && userIdTextField.text.length > 0) {
        [config setUserId:userIdTextField.text];
    } else {
        [config removeUserId];
    }
    if (genderTextField.text && genderTextField.text.length > 0) {
        [config setGender:genderTextField.text];
    } else {
        [config removeGender];
    }
    
    // alert controller
    if ([self isApiKeyEmpty] || [self isSessionSecondsEmpty] || [self isAppVersionEmpty]) {
        controller = [UIAlertController alertControllerWithTitle:@"Caution!" message:@"Some non-optional text field is still empty. We will use the default value if you want to start session anyway. " preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil];
        UIAlertAction *start = [UIAlertAction actionWithTitle:@"Start" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            if ([self isApiKeyEmpty]) {
                self->apiKeyTextField.text = self->config.defaultApiKey;
            }
            if ([self isSessionSecondsEmpty]) {
                self->sessionSecondsTextField.text = [self->config.defaultSessionSeconds description];
            }
            if ([self isAppVersionEmpty]) {
                self->appVersionTextField.text = self->config.defaultAppVersion;
            }
            [self performSegueWithIdentifier:@"start" sender:self];
            [self startFlurrySession];
        }];
        [controller addAction:cancel];
        [controller addAction:start];
        [self presentViewController:controller animated:YES completion:nil];
    } else {
        UIStoryboard *storyBoard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        UITabBarController *tabBarController = [storyBoard instantiateViewControllerWithIdentifier:@"tab"];
        tabBarController.selectedIndex = 0;
        [self startFlurrySession];
        [self performSegueWithIdentifier:@"start" sender:self];
    }
    
}

-(BOOL)isApiKeyEmpty {
    return !(apiKeyTextField.text && apiKeyTextField.text.length > 0);
}

-(BOOL)isSessionSecondsEmpty {
    return !(sessionSecondsTextField.text && sessionSecondsTextField.text.length > 0);
}

-(BOOL)isAppVersionEmpty {
    return !(appVersionTextField.text && appVersionTextField.text.length > 0);
}

-(void)startFlurrySession {
    if ([config age] != nil) {
        [Flurry setAge:[[config age] intValue]];
    }
    if ([config gender] != nil) {
        [Flurry setGender:[config gender]];
    }
    if ([config userId] != nil) {
        [Flurry setUserID:[config userId]];
    }
    BOOL crashReport = [[NSString stringWithFormat:@"%@", [config enableCrashReport]] isEqualToString:@"0"] ? NO : YES;
    FlurrySessionBuilder* builder = [[[[[FlurrySessionBuilder new] withLogLevel:FlurryLogLevelDebug]
                                       withCrashReporting:crashReport]
                                      withSessionContinueSeconds:[sessionSecondsTextField.text integerValue]]
                                     withAppVersion:appVersionTextField.text];
    [Flurry startSession:apiKeyTextField.text withSessionBuilder:builder];
    
}

# pragma picker view data source and delegate

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    return genders.count;
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    return genders[row];
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    [genderTextField setText:[genders objectAtIndex:row]];
    [[self view] endEditing:YES];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [[self view] endEditing:YES];
}

#pragma text field delegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

@end
