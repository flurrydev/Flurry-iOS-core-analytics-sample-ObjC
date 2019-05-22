//
//  LogEventViewController.m
//  FlurryCoreAnalyticsSampleApp_Obj
//
//  Created by Yilun Xu on 10/4/18.
//  Copyright © 2018 Flurry. All rights reserved.
//

#import "LogEventViewController.h"
#import "Flurry.h"

@interface LogEventViewController ()

@property (nonatomic, assign) BOOL isLoggingTimedEvent;
@property (nonatomic, assign) BOOL isLoggingTimedEventWithParams;
@property (nonatomic, strong) NSDictionary *defaultParams;

@end

@implementation LogEventViewController

static NSString *sLogEventName = @"sample log event name";
static NSString *sTimedLogEventName = @"sample timed log event name";
static NSString *sLogEventNameWithParams = @"sample log event name with params";
static NSString *sTimedLogEventNameWithParams = @"sample timed log event name with params";
static double sAlertDismissTime = 0.35;


- (void)viewDidLoad {
    [super viewDidLoad];
    self.isLoggingTimedEvent = NO;
    self.isLoggingTimedEventWithParams = NO;
    self.defaultParams = @{
                           @"item purchased" : @"cool item"
                           };
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(NSString *)stringForEventRercordStatus:(FlurryEventRecordStatus)status {
    switch(status) {
        case FlurryEventFailed:
            return @"Log Event Failed";
        case FlurryEventRecorded:
            return @"Log Event Recorded";
        case FlurryEventUniqueCountExceeded:
            return @"Log Event Unique Count Exceeded";
        case FlurryEventParamsCountExceeded:
            return @"Log Event Params Count Exceeded";
        case FlurryEventLogCountExceeded:
            return @"Log Event Count Exceeded";
        case FlurryEventLoggingDelayed:
            return @"Log Event Delayed";
        case FlurryEventAnalyticsDisabled:
            return @"Log Event Analytics Disabled";
    }
}

-(void)setEnabled:(BOOL)enabled params:(BOOL)hasParams forRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];
    if (enabled) {
        if (hasParams) {
            [cell.textLabel setText:@"Begin timed event with params"];
        } else {
            [cell.textLabel setText:@"Begin timed event"];
        }
        [cell.textLabel setTextColor:[UIColor greenColor]];
        [cell.textLabel setTextAlignment:NSTextAlignmentCenter];
    } else {
        if (hasParams) {
            [cell.textLabel setText:@"End timed event with params"];
        } else {
            [cell.textLabel setText:@"End timed event"];
        }
        [cell.textLabel setTextColor:[UIColor redColor]];
        [cell.textLabel setTextAlignment:NSTextAlignmentCenter];
        
    }
}

#pragma mark - Table view data source

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    switch(indexPath.section) {
        case 0:
            // log event
            if (indexPath.row == 0) {
                // normal event
                FlurryEventRecordStatus status = [Flurry logEvent:sLogEventName];
                [self displayAlertWithTitle:@"Log Event" message:[self stringForEventRercordStatus:status] dismissAfter:sAlertDismissTime];
            } else {
                // timed event
                if (!self.isLoggingTimedEvent) {
                    FlurryEventRecordStatus status = [Flurry logEvent:sTimedLogEventName timed:YES];
                    [self displayAlertWithTitle:@"Begin timed event" message:[self stringForEventRercordStatus:status] dismissAfter:sAlertDismissTime];
                } else {
                    [Flurry endTimedEvent:sTimedLogEventName withParameters:nil];
                    [self displayAlertWithTitle:@"End Timed Event" message:nil dismissAfter:sAlertDismissTime];
                }
                self.isLoggingTimedEvent = !self.isLoggingTimedEvent;
                [self setEnabled:!self.isLoggingTimedEvent params:NO forRowAtIndexPath:indexPath];
            }
            break;
        case 1:
            // log event with params
            if (indexPath.row == 0) {
                // normal event with params
                FlurryEventRecordStatus status = [Flurry logEvent:sTimedLogEventNameWithParams withParameters:self.defaultParams];
                [self displayAlertWithTitle:@"Log Event with Params" message:[self stringForEventRercordStatus:status] dismissAfter:sAlertDismissTime];
            } else {
                // timed event with params
                if (!self.isLoggingTimedEventWithParams) {
                    FlurryEventRecordStatus status = [Flurry logEvent:sTimedLogEventNameWithParams withParameters:self.defaultParams timed:YES];
                    [self displayAlertWithTitle:@"Begin timed event with params" message:[self stringForEventRercordStatus:status] dismissAfter:sAlertDismissTime];
                } else {
                    [Flurry endTimedEvent:sTimedLogEventNameWithParams withParameters:self.defaultParams];
                    [self displayAlertWithTitle:@"End Timed Event" message:nil dismissAfter:sAlertDismissTime];
                }
                self.isLoggingTimedEventWithParams = !self.isLoggingTimedEventWithParams;
                [self setEnabled:!self.isLoggingTimedEventWithParams params:YES forRowAtIndexPath:indexPath];
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

