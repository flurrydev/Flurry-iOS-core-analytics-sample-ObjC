//
//  InfoViewController.h
//  FlurryCoreAnalyticsSampleApp_Obj
//
//  Created by Yilun Xu on 10/4/18.
//  Copyright © 2018 Flurry. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface InfoViewController : UITableViewController <UITextFieldDelegate, UIPickerViewDelegate, UIPickerViewDataSource>
@property (weak, nonatomic) IBOutlet UITextField *ageTextField;
@property (weak, nonatomic) IBOutlet UITextField *genderTextField;
@property (weak, nonatomic) IBOutlet UITextField *userIdTextField;
- (IBAction)save:(id)sender;
@end
