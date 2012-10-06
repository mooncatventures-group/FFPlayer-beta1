
#import <Foundation/Foundation.h>
#import <FFmpegDecoder/libavcodec/avcodec.h>


@interface FrameData : NSObject {
	NSMutableData *data;
	int64_t pts;
    NSInteger width;
    NSInteger height;
    AVFrame *avFrame;;
}


@property  NSMutableData *data;
@property (assign) int64_t pts;
@property (assign) NSInteger width;
@property (assign) NSInteger height;
- (void)addAVFrame:(AVFrame* )frame;
- (AVFrame*)getAVFrame;


@end
