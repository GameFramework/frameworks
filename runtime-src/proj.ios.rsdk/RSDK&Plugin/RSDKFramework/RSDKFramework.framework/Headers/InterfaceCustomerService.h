//
//  InterfaceCustomerService.h
//  RSDKFramework
//
//  Created by 邹明明 on 16/11/21.
//

@protocol InterfaceCustomerService <NSObject>

- (void) showCustomerService:(NSMutableDictionary*) parms;
- (void) showContactus:(NSMutableDictionary*) parms;
- (void) showHelpe:(NSMutableDictionary*) parms;
- (void) showFAQ:(NSMutableDictionary*) parms;
- (void) setDebugMode: (BOOL) debug;
- (NSString*) getSDKVersion;
- (NSString*) getPluginVersion;
- (NSString*) getPluginId;
- (BOOL) isFunctionSupported : (NSString*) functionName;
@end
