//
//  SettingViewController.h
//  FlurryCoreAnalyticsSampleApp_Obj
//
//  Created by Yilun Xu on 10/4/18.
//  Copyright © 2018 Flurry. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SettingViewController : UIViewController <UIPickerViewDataSource, UIPickerViewDelegate, UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UISwitch *enableCrashReportSwitch;
@property (weak, nonatomic) IBOutlet UITextField *apiKeyTextField;
@property (weak, nonatomic) IBOutlet UITextField *sessionSecondsTextField;
@property (weak, nonatomic) IBOutlet UITextField *appVersionTextField;
@property (weak, nonatomic) IBOutlet UITextField *ageTextField;
@property (weak, nonatomic) IBOutlet UITextField *genderTextField;
@property (weak, nonatomic) IBOutlet UITextField *userIdTextField;

- (IBAction)start:(id)sender;

@end

