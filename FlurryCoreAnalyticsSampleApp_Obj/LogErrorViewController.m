//
//  LogErrorViewController.m
//  FlurryCoreAnalyticsSampleApp_Obj
//
//  Created by Yilun Xu on 10/4/18.
//  Copyright © 2018 Flurry. All rights reserved.
//

#import "LogErrorViewController.h"
#import "Flurry.h"

@interface LogErrorViewController ()

@end

@implementation LogErrorViewController

static NSString *sLogException = @"sample log exception";
static NSString *sLogExceptionName = @"sample log exception name";
static NSString *sLogError = @"sample log error";
static NSString *sLogExceptionWithTags = @"sample log exception with tags";
static NSString *sLogExceptionWithTagsName = @"sample log exception with tags name";
static NSString *sLogErrorWithTags = @"sample log error with tags";
static NSString *sFlurryAppDomain = @"sample flurry app domain";
static NSString *sEventsExcetpionName = @"sample events excetpion name";
static NSString *sBreadcrumbsInfo = @"sample breadcrumbs info";

static double sAlertDismissTime = 0.35;

- (void)viewDidLoad {
    [super viewDidLoad];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) dereferencePage0x0 {
    *(uint32_t *)0x4 = 0xDEADBEEF;
}

#pragma mark - Table view data source

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (indexPath.row == 0) {
        // log exception
        
        NSException *exception = [NSException exceptionWithName:sLogExceptionName reason:@"sample reason" userInfo:nil];
        [Flurry logError:sLogException message:@"log with exception message" exception:exception];
        [self displayAlertWithTitle:@"Log Exception" message:nil dismissAfter:sAlertDismissTime];
    } else if (indexPath.row == 1) {
        // log error
        
        NSError *error = [NSError errorWithDomain:sFlurryAppDomain code:42 userInfo:nil];
        [Flurry logError:sLogError message:@"log with error message" error:error];
        [self displayAlertWithTitle:@"Log Error" message:nil dismissAfter:sAlertDismissTime];
    } else if (indexPath.row == 2) {
        // log error with tags
        
        NSError *error = [NSError errorWithDomain:sFlurryAppDomain code:42 userInfo:nil];
        NSDictionary *errorTags = @{@"location":@"not valid"};
        [Flurry logError:sLogErrorWithTags message:@"log with error and tags" error:error withParameters:errorTags];
        [self displayAlertWithTitle:@"Log Error with Tags" message:nil dismissAfter:sAlertDismissTime];
    } else if (indexPath.row == 3) {
        // log exception with tags
        
        NSException *exception = [NSException exceptionWithName:sLogExceptionWithTagsName reason:@"sample reason" userInfo:nil];
        NSDictionary *exceptionTags = @{@"appVersion":@"3.2"};
        [Flurry logError:sLogExceptionWithTags message:@"log with exception and tags" exception:exception withParameters:exceptionTags];
        [self displayAlertWithTitle:@"Log Exception with Tags" message:nil dismissAfter:sAlertDismissTime];
    } else if (indexPath.row == 4){
        // leave breadcrumbs
        
        [Flurry leaveBreadcrumb:sBreadcrumbsInfo];
        [self displayAlertWithTitle:@"example: webview not loading" message:nil dismissAfter:sAlertDismissTime];
    } else {
        //crash
        
        [self dereferencePage0x0];
    }
    
}

-(void)displayAlertWithTitle:(NSString *)title message:(NSString *)message dismissAfter:(double)seconds {
    // decide UI alert style
    UIAlertControllerStyle style = self.traitCollection.userInterfaceIdiom == UIUserInterfaceIdiomPad ? UIAlertControllerStyleAlert : UIAlertControllerStyleActionSheet;
    
    // set alert controller
    UIAlertController *controller = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:style];
    
    if (seconds <= 0) {
        [controller addAction:[UIAlertAction actionWithTitle:@"dismiss" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action){
            // add dismiss option in the alert if seconds less than 0
            [controller dismissViewControllerAnimated:YES completion:nil];
        }]];
    }
    
    // present the alert
    [self presentViewController:controller animated:YES completion:^{
        if (seconds > 0) {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(seconds * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                [controller dismissViewControllerAnimated:YES completion:nil];
            });
        }
    }];
    
    
}





@end

