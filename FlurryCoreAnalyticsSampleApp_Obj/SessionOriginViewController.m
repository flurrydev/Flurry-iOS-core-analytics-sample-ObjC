//
//  SessionOriginViewController.m
//  FlurryCoreAnalyticsSampleApp_Obj
//
//  Created by Yilun Xu on 10/4/18.
//  Copyright © 2018 Flurry. All rights reserved.
//

#import "SessionOriginViewController.h"
#import "Flurry.h"

@interface SessionOriginViewController ()


@end

@implementation SessionOriginViewController

static NSString *sSessionOriginName = @"facebuk";
static NSString *sSessionOriginWithDeeplinkName = @"facebuk with a link";
static NSString *sOriginName = @"Interesting Wrapper";
static NSString *sDeeplink = @"Flurry://app/analytics";
static NSString *sOriginVersion = @"1.0.0";
static double sAlertDismissTime = 0.35;

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    switch(indexPath.section) {
        case 0:
            if (indexPath.row == 0) {
                // add session origin
                [Flurry addSessionOrigin:sSessionOriginName];
                [self displayAlertWithTitle:@"session origin added" message:nil dismissAfter:sAlertDismissTime];
            } else if (indexPath.row == 1) {
                // add session origin with deeplink
                [Flurry addSessionOrigin:sSessionOriginName withDeepLink:sDeeplink];
                [self displayAlertWithTitle:@"session origin with deeplink added" message:nil dismissAfter:sAlertDismissTime];
            } else {
                // set session property
                NSDictionary *properties = @{@"location" : @"sunnyvale"};
                [Flurry sessionProperties:properties];
                [self displayAlertWithTitle:@"session properties set" message:nil dismissAfter:sAlertDismissTime];
            }
            break;
        case 1:
            if (indexPath.row == 0) {
                // add origin with version
                [Flurry addOrigin:sOriginName withVersion:sOriginVersion];
                [self displayAlertWithTitle:@"origin with version added" message:nil dismissAfter:sAlertDismissTime];
            } else {
                // add origin with params and version
                NSDictionary *params = @{@"origin info key" : @"origin info value"};
                [Flurry addOrigin:sOriginName withVersion:sOriginVersion withParameters:params];
                [self displayAlertWithTitle:@"origin with version and params added" message:nil dismissAfter:sAlertDismissTime];
            }
            break;
        default:
            break;
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
