//
//  InfoViewController.m
//  FlurryCoreAnalyticsSampleApp_Obj
//
//  Created by Yilun Xu on 10/4/18.
//  Copyright © 2018 Flurry. All rights reserved.
//

#import "InfoViewController.h"
#import "FlurryAnalyticsConfiguration.h"

@interface InfoViewController () {
    NSArray *genders;
    FlurryAnalyticsConfiguration *config;
}

@end

@implementation InfoViewController

@synthesize ageTextField;
@synthesize genderTextField;
@synthesize userIdTextField;

- (void)viewDidLoad {
    [super viewDidLoad];
    config = [FlurryAnalyticsConfiguration sharedInstance];
    ageTextField.delegate = self;
    [ageTextField setReturnKeyType:UIReturnKeyDone];
    userIdTextField.delegate = self;
    [userIdTextField setReturnKeyType:UIReturnKeyDone];
    
    // show settings
    if ([config userId] != nil) {
        userIdTextField.text = [config userId];
    }
    if ([config gender] != nil) {
        genderTextField.text = [config gender];
    }
    if ([config age] != nil) {
        ageTextField.text = [[config age] description];
    }
    
    // set picker
    genders = @[@"", @"Female", @"Male"];
    UIPickerView *picker = [[UIPickerView alloc] init];
    picker.delegate = self;
    picker.dataSource = self;
    picker.showsSelectionIndicator = YES;
    [genderTextField setInputView:picker];
    
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)textFieldDidEndEditing:(UITextField *)textField {
    [textField resignFirstResponder];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
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


- (IBAction)save:(id)sender {
    if (ageTextField.text && ageTextField.text.length > 0) {
        NSNumberFormatter *formatter = [[NSNumberFormatter alloc] init];
        formatter.numberStyle = NSNumberFormatterDecimalStyle;
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
}

-(BOOL)isAgeEmpty {
    return !(ageTextField.text && ageTextField.text.length > 0);
}

-(BOOL)isGenderEmpty {
    return !(genderTextField.text && genderTextField.text.length > 0);
}

-(BOOL)isUserIdEmpty {
    return !(userIdTextField.text && userIdTextField.text.length > 0);
}
@end
