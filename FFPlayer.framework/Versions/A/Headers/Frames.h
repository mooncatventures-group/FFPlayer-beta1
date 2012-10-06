#import <AudioToolbox/AudioQueue.h>
#import <AudioToolbox/AudioToolbox.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#include <FFmpegDecoder/libavformat/avformat.h>
#include <FFmpegDecoder/libswscale/swscale.h>
#import <FFmpegDecoder/libavcodec/avcodec.h>
#import <FFmpegDecoder/libavformat/avio.h>
#import <FFmpegDecoder/libswscale/swscale.h>
#import "FrameData.h"

#import <UIKit/UIKit.h>
#define kPollingInterval 1.0/30
#define OUTPUT_FILE_NAME @"screen.mov"
#define FRAME_WIDTH 320
#define FRAME_HEIGHT 480
#define TIME_SCALE 600 


@protocol CGImageBufferDelegate <NSObject>
@required
-(void)didOutputCGImageBuffer:(NSTimer *)timer;
-(void)didOutputpixels:(FrameData *)pixels;
@optional
-(void)didGetContext:(AVCodecContext*)_pCodecCtx;
@end



@interface Frames : NSObject {
    id<CGImageBufferDelegate> __unsafe_unretained cgimageDelegate;
    int sourceWidth, sourceHeight;
	int outputWidth, outputHeight;
	float lastFrameTime;
	UIImage *currentImage;
	double duration;
    BOOL frameReady;
    AVStream *_audioStream;
    NSLock *audioPacketQueueLock;
    dispatch_queue_t firstSerialQueue;
    int16_t *_audioBuffer;
    int audioPacketQueueSize;
    NSMutableArray *audioPacketQueue;
    AVCodecContext *_audioCodecContext;
    NSUInteger _audioBufferSize;
    AVPacket *_packet, _currentPacket;
    BOOL _inBuffer;
    BOOL primed;
    BOOL movieDone;
    BOOL _usesAudio;

  
}


@property  (unsafe_unretained) id cgimageDelegate;
@property (nonatomic, retain) NSMutableArray *audioPacketQueue;
@property (nonatomic, assign)  AVCodecContext *_audioCodecContext;
@property (nonatomic, assign)  AudioQueueBufferRef emptyAudioBuffer;
@property (nonatomic, assign)  	int audioPacketQueueSize;
@property (nonatomic, assign)  	AVStream *_audioStream;

- (BOOL)decodeFrame:(NSData*)frameData;
- (BOOL)isFrameReady;
- (NSData*)getDecodedFrame;
- (NSUInteger)getDecodedFrameWidth;
- (NSUInteger)getDecodedFrameHeight;


-(void)setupCgimageSession;

-(void)setupPVimageSession;




-(void)setOutputWidth:(int)newValue;

-(void)setOutputHeight:(int)newValue;


-(void)willOutputpixels:(FrameData *)pixels;



/* Last decoded picture as UIImage */
@property (weak, nonatomic, readonly) UIImage *currentImage;

/* Size of video frame */
@property (nonatomic, readonly) int sourceWidth, sourceHeight;

/* Output image size. Set to the source size by default. */
@property (nonatomic) int outputWidth, outputHeight;

/* Length of video in seconds */
@property (nonatomic, readonly) double duration;

/* Initialize with movie at moviePath. Output dimensions are set to source dimensions. */
-(id)initWithVideo:(NSString *)moviePath  usesTcp:(BOOL)usesTcp  usesAudio:(BOOL)usesAudio;


/* Read the next frame from the video stream. Returns false if no frame read (video over). */
-(BOOL)stepFrame;

-(void)setupScaler;

-(void)displayNextImageBuffer;
-(void)shutDownAVcapture;


/* Seek to closest keyframe near specified time */
-(void)seekTime:(double)seconds;



@end
