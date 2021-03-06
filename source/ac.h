/*
 * Acid Cam Functions for OpenCV
 * written by Jared Bruni https://github.com/lostjared
 
 This software is dedicated to all the people that experience mental illness.
 
 Website: http://lostsidedead.com
 YouTube: http://youtube.com/LostSideDead
 Instagram: http://instagram.com/lostsidedead
 Twitter: http://twitter.com/jaredbruni
 Facebook: http://facebook.com/LostSideDead0x
 
 You can use this program free of charge and redistrubute it online as long
 as you do not charge anything for this program. This program is meant to be
 100% free.
 
 BSD 2-Clause License
 
 Copyright (c) 2019, Jared Bruni
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __AC_H__
#define __AC_H__
#ifdef __APPLE__
#include<opencv2/videoio.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#else
#include<opencv2/opencv.hpp>
#endif
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<random>
#include<unordered_map>
#include<memory>
#include<cassert>
#include<utility>
#include"ac-filtercat.h"
//#define ASSERT_CHECK
// Macro for assert testing
#ifdef ASSERT_CHECK
#define ASSERT(X) assert(X)
#else
#define ASSERT(X)
#endif
/*
 *
 * Be sure to call fill_filter_map
 * to use set appropriate variables, call the function
 *
 * ac::SelfAlphaBlend(mat);
 *
 * or use CallFilter
 *
 * CallFilter(function_index, mat);
 *
 * then just use function_index to point to whatever filter
 *
 * for text of the filter use the following array of strings
 *
 * ac::draw_strings[function_index];
 *
 */
// exernal variables
extern int current_filterx, bytesPerSample, bytesPerRow, width, height, red, green, blue, offset, randomNumber, reverse;
extern bool negate, blend_set, colorkey_set,colorkey_bg, colorkey_replace, colorkey_filter;
extern cv::Mat blend_image,color_image,color_bg_image, color_replace_image, color_filter;

int AC_GetFX(int oldw,int x, int nw);
int AC_GetFZ(int oldh, int y, int nh);

// acid cam namespace
namespace ac {
    // get version string
    extern std::string getVersion();
    // version string
    extern const std::string version;
    extern double translation_variable, pass2_alpha;
    extern double alpha, tr;
    extern bool isNegative, noRecord,iRev;
    extern int color_order;
    extern double fps;
    extern int draw_offset;
    extern int subfilter;
    extern std::string fileName;
    extern cv::Mat orig_frame;
    extern cv::Mat blendW_frame;
    extern cv::Mat image_files[4];
    extern bool images_Enabled,fps_force;
    extern int snapshot_Type;
    extern bool in_custom;
    extern int swapColor_r, swapColor_g, swapColor_b;
    extern cv::Size resolution;
    extern bool strobe_It;
    extern int set_color_map;
    extern bool color_map_set;
    extern int GetFX(cv::Mat &frame, int x, int nw);
    extern int GetFY(cv::Mat &frame, int y, int nh);
    extern bool reset_alpha;
    void invert(cv::Mat &frame, int x, int y);
    /* filter typedef */
    typedef void (*DrawFunction)(cv::Mat &frame);
    typedef std::pair<std::string,DrawFunction> FilterType;
    extern DrawFunction custom_callback;
    extern DrawFunction plugin_func;
    // ror/rol tempaltes
    template<typename T>
    inline T ror(T x, int m){
        return (x >> m) | (x << (sizeof(T)*8 - m));
    }
    template<typename T>
    inline T rol(T x, int m) {
        return (x << m) | (x >> (sizeof(T)*8 -m));
    }
    enum class KeyValueType { KEY_RANGE, KEY_TOLERANCE };
    class Keys {
    public:
        cv::Vec3b low, high;
        KeyValueType key_type;
        bool spill;
        Keys() : key_type(KeyValueType::KEY_RANGE), spill(false) {}
    };
    
    enum SearchType { SEARCH_NOTFOUND=0, SEARCH_PIXEL, SEARCH_GRAY };
    // be sure to call this when the application starts
    void fill_filter_map();
    // draw functions
    DrawFunction getRandomFilter(int &index);
    void DrawFilter(const std::string &name, const cv::Mat &frame, cv::Mat &outframe);
    void DrawFilter(int index, const cv::Mat &frame, cv::Mat &outframe);
    void DrawFilter(int index, cv::Mat &frame);
    void DrawFilter(const std::string &name, cv::Mat &frame);
    void DrawFilterUnordered(const std::string &name, cv::Mat &frame);
    DrawFunction getFilter(std::string name);
    FilterType filterByIndex(const int &num);
    FilterType filterByString(const std::string &num);
    bool CallFilter(int index, cv::Mat &frame);
    bool CallFilter(const std::string &name, cv::Mat &frame);
    // Acid Cam Filter Function prototypes
    void SelfAlphaBlend(cv::Mat &frame);
    void SelfScale(cv::Mat &frame);
    void StrobeEffect(cv::Mat &frame);
    void Blend3(cv::Mat &frame);
    void NegParadox(cv::Mat &frame);
    void ThoughtMode(cv::Mat &frame);
    void Pass2Blend(cv::Mat &frame);
    void RandTriBlend(cv::Mat &frame);
    void Blank(cv::Mat &frame);
    void Tri(cv::Mat &frame);
    void Distort(cv::Mat &frame);
    void CDraw(cv::Mat &frame);
    void Type(cv::Mat &frame);
    void NewOne(cv::Mat &frame);
    void blendWithImage(cv::Mat &frame);
    void triBlendWithImage(cv::Mat &frame);
    void imageStrobe(cv::Mat &frame);
    void imageDistraction(cv::Mat &frame);
    void blendFractal(cv::Mat &frame);
    void blendFractalMood(cv::Mat &frame);
    void cossinMultiply(cv::Mat &frame);
    void colorAccumulate1(cv::Mat &frame);
    void colorAccumulate2(cv::Mat &frame);
    void colorAccumulate3(cv::Mat &frame);
    void filter8(cv::Mat &frame);
    void filter3(cv::Mat &frame);
    void rainbowBlend(cv::Mat &frame);
    void randBlend(cv::Mat &frame);
    void newBlend(cv::Mat &frame);
    void alphaFlame(cv::Mat &frame);
    void custom(cv::Mat &frame);
    void pixelScale(cv::Mat &frame);
    void glitchSort(cv::Mat &frame);
    void pixelSort(cv::Mat &frame);
    void randomFilter(cv::Mat &frame);
    void randomFlash(cv::Mat &frame);
    void imageBlend(cv::Mat &frame);
    void imageBlendTwo(cv::Mat &frame);
    void imageBlendThree(cv::Mat &frame);
    void imageBlendFour(cv::Mat &frame);
    void GaussianBlur(cv::Mat &frame);
    void MedianBlur(cv::Mat &frame);
    void BlurDistortion(cv::Mat &frame);
    void DiamondPattern(cv::Mat &frame);
    void MirrorBlend(cv::Mat &frame);
    void Pulse(cv::Mat &frame);
    void SidewaysMirror(cv:: Mat &frame);
    void MirrorNoBlend(cv::Mat &frame);
    void SortFuzz(cv::Mat &frame);
    void Fuzz(cv::Mat &frame);
    void DoubleVision(cv::Mat &frame);
    void RGBShift(cv::Mat &frame);
    void RGBSep(cv::Mat &frame);
    void GradientRainbow(cv::Mat &frame);
    void GradientRainbowFlash(cv::Mat &frame);
    void Reverse(cv::Mat &frame);
    void Scanlines(cv::Mat &frame);
    void TVStatic(cv::Mat &frame);
    void MirrorAverage(cv::Mat &frame);
    void MirrorAverageMix(cv::Mat &frame);
    void Mean(cv::Mat &frame);
    void Laplacian(cv::Mat &frame);
    void Bitwise_XOR(cv::Mat &frame);
    void Bitwise_AND(cv::Mat &frame);
    void Bitwise_OR(cv::Mat &frame);
    void Equalize(cv::Mat &frame);
    void ChannelSort(cv::Mat &frame);
    void Reverse_XOR(cv::Mat &frame);
    void CombinePixels(cv::Mat &frame);
    void FlipTrip(cv::Mat &frame);
    void Canny(cv::Mat &frame);
    void Boxes(cv::Mat &frame);
    void BoxesFade(cv::Mat &frame);
    void FlashBlack(cv::Mat &frame);
    void SlideRGB(cv::Mat &frame);
    void Side2Side(cv::Mat &frame);
    void Top2Bottom(cv::Mat &frame);
    void StrobeRedGreenBlue(cv::Mat &frame);
    void Outward(cv::Mat &frame);
    void OutwardSquare(cv::Mat &frame);
    void Blend_Angle(cv::Mat &frame);
    void ShiftPixels(cv::Mat &frame);
    void ShiftPixelsDown(cv::Mat &frame);
    void XorMultiBlend(cv::Mat &frame);
    void BitwiseRotate(cv::Mat &frame);
    void BitwiseRotateDiff(cv::Mat &frame);
    void HPPD(cv::Mat &frame);
    void FuzzyLines(cv::Mat &frame);
    void GradientLines(cv::Mat &frame);
    void GradientSelf(cv::Mat &frame);
    void GradientDown(cv::Mat &frame);
    void GraidentHorizontal(cv::Mat &frame);
    void GradientSelfVertical(cv::Mat &frame);
    void GradientRGB(cv::Mat &frame);
    void Inter(cv::Mat &frame);
    void UpDown(cv::Mat &frame);
    void LeftRight(cv::Mat &frame);
    void StrobeScan(cv::Mat &frame);
    void BlendedScanLines(cv::Mat &frame);
    void GradientStripes(cv::Mat &frame);
    void XorSine(cv::Mat &frame);
    void SquareSwap(cv::Mat &frame);
    void SquareSwap4x2(cv::Mat &frame);
    void SquareSwap8x4(cv::Mat &frame);
    void SquareSwap16x8(cv::Mat &frame);
    void SquareSwap64x32(cv::Mat &frame);
    void SquareBars(cv::Mat &frame);
    void SquareBars8(cv::Mat &frame);
    void SquareVertical8(cv::Mat &frame);
    void SquareVertical16(cv::Mat &frame);
    void SquareVertical_Roll(cv::Mat &frame);
    void SquareSwapRand16x8(cv::Mat &frame);
    void SquareSwapSort_Roll(cv::Mat &frame);
    void SquareVertical_RollReverse(cv::Mat &frame);
    void SquareSwapSort_RollReverse(cv::Mat &frame);
    void Circular(cv::Mat &frame);
    void WhitePixel(cv::Mat &frame);
    void FrameBlend(cv::Mat &frame);
    void FrameBlendRGB(cv::Mat &frame);
    void TrailsFilter(cv::Mat &frame);
    void TrailsFilterIntense(cv::Mat &frame);
    void TrailsFilterSelfAlpha(cv::Mat &frame);
    void TrailsFilterXor(cv::Mat &frame);
    void ColorTrails(cv::Mat &frame);
    void MoveRed(cv::Mat &frame);
    void MoveRGB(cv::Mat &frame);
    void MoveRedGreenBlue(cv::Mat &frame);
    void BlurSim(cv::Mat &frame);
    void Block(cv::Mat &frame);
    void BlockXor(cv::Mat &frame);
    void BlockScale(cv::Mat &frame);
    void BlockStrobe(cv::Mat &frame);
    void PrevFrameBlend(cv::Mat &frame);
    void Wave(cv::Mat &frame);
    void HighWave(cv::Mat &frame);
    void VerticalSort(cv::Mat &frame);
    void VerticalChannelSort(cv::Mat &frame);
    void HorizontalBlend(cv::Mat &frame);
    void VerticalBlend(cv::Mat &frame);
    void OppositeBlend(cv::Mat &frame);
    void DiagonalLines(cv::Mat &frame);
    void HorizontalLines(cv::Mat &frame);
    void InvertedScanlines(cv::Mat &frame);
    void Soft_Mirror(cv::Mat &frame);
    void KanapaTrip(cv::Mat &frame);
    void ColorMorphing(cv::Mat &frame);
    void ScanSwitch(cv::Mat &frame);
    void ScanAlphaSwitch(cv::Mat &frame);
    void NegativeStrobe(cv::Mat &frame);
    void XorAddMul(cv::Mat &frame);
    void ParticleRelease(cv::Mat &frame);
    void BlendSwitch(cv::Mat &frame);
    void AllRed(cv::Mat &frame);
    void AllGreen(cv::Mat &frame);
    void AllBlue(cv::Mat &frame);
    void LineRGB(cv::Mat &frame);
    void PixelRGB(cv::Mat &frame);
    void BoxedRGB(cv::Mat &frame);
    void KruegerSweater(cv::Mat &frame);
    void RGBFlash(cv::Mat &frame);
    void IncreaseBlendHorizontal(cv::Mat &frame);
    void BlendIncrease(cv::Mat &frame);
    void GradientReverse(cv::Mat &frame);
    void GradientReverseVertical(cv::Mat &frame);
    void GradientReverseBox(cv::Mat &frame);
    void GradientNewFilter(cv::Mat &frame);
    void ReinterpretDouble(cv::Mat &frame);
    void ReinterpSelfScale(cv::Mat &frame);
    void AverageLines(cv::Mat &frame);
    void ImageFile(cv::Mat &frame);
    void ImageXor(cv::Mat &frame);
    void ImageAlphaBlend(cv::Mat &frame);
    void ColorRange(cv::Mat &frame);
    void ImageInter(cv::Mat &frame);
    void TrailsInter(cv::Mat &frame);
    void TrailsBlend(cv::Mat &frame);
    void TrailsNegate(cv::Mat &frame);
    void InterReverse(cv::Mat &frame);
    void InterMirror(cv::Mat &frame);
    void InterFullMirror(cv::Mat &frame);
    void MirrorRGB(cv::Mat &frame);
    void RGBStatic1(cv::Mat &frame);
    void RGBStatic2(cv::Mat &frame);
    void VectorIncrease(cv::Mat &frame);
    void LineByLineReverse(cv::Mat &frame);
    void RandomIntertwine(cv::Mat &frame);
    void RandomFour(cv::Mat &frame);
    void BlendThree(cv::Mat &frame);
    void AcidTrails(cv::Mat &frame);
    void RandomTwo(cv::Mat &frame);
    void HorizontalTrailsInter(cv::Mat &frame);
    void Trails(cv::Mat &frame);
    void BlendTrails(cv::Mat &frame);
    void RandomFilteredSquare(cv::Mat &frame);
    void ImageX(cv::Mat &frame);
    void RandomQuads(cv::Mat &frame);
    void QuadCosSinMultiply(cv::Mat &frame);
    void QuadRandomFilter(cv::Mat &frame);
    void RollRandom(cv::Mat &frame);
    void AverageRandom(cv::Mat &frame);
    void HorizontalStripes(cv::Mat &frame);
    void DiamondStrobe(cv::Mat &frame);
    void SmoothTrails(cv::Mat &frame);
    void GridFilter8x(cv::Mat &frame);
    void GridFilter16x(cv::Mat &frame);
    void GridFilter8xBlend(cv::Mat &frame);
    void GridRandom(cv::Mat &frame);
    void GridRandomPixel(cv::Mat &frame);
    void Dual_SelfAlphaRainbow(cv::Mat &frame);
    void Dual_SelfAlphaBlur(cv::Mat &frame);
    void SurroundPixelXor(cv::Mat &frame);
    void Darken(cv::Mat &frame);
    void WeakBlend(cv::Mat &frame);
    void AverageVertical(cv::Mat &frame);
    void RandomCollectionAverage(cv::Mat &frame);
    void RandomCollectionAverageMax(cv::Mat &frame);
    void SmoothTrailsSelfAlphaBlend(cv::Mat &frame);
    void SmoothTrailsRainbowBlend(cv::Mat &frame);
    void MedianBlend(cv::Mat &frame);
    void SmoothRandomImageBlend(cv::Mat &frame);
    void SmoothImageAlphaBlend(cv::Mat &frame);
    void RandomAlphaBlend(cv::Mat &frame);
    void RandomTwoFilterAlphaBlend(cv::Mat &frame);
    void PixelatedSquare(cv::Mat &frame);
    void AlphaBlendPosition(cv::Mat &frame);
    void BlendRowAlpha(cv::Mat &frame);
    void BlendRow(cv::Mat &frame);
    void BlendRowByVar(cv::Mat &frame);
    void BlendRowByDirection(cv::Mat &frame);
    void BlendAlphaXor(cv::Mat &frame);
    void SelfXorScale(cv::Mat &frame);
    void BitwiseXorScale(cv::Mat &frame);
    void XorTrails(cv::Mat &frame);
    void RainbowTrails(cv::Mat &frame);
    void NegativeTrails(cv::Mat &frame);
    void IntenseTrails(cv::Mat &frame);
    void SelfAlphaRGB(cv::Mat &frame);
    void BlendImageOnOff(cv::Mat &frame);
    void XorSelfAlphaImage(cv::Mat &frame);
    void BitwiseXorStrobe(cv::Mat &frame);
    void AlphaBlendRandom(cv::Mat &frame);
    void ChannelSortAlphaBlend(cv::Mat &frame);
    void XorChannelSort(cv::Mat &frame);
    void GradientColors(cv::Mat &frame);
    void GradientColorsVertical(cv::Mat &frame);
    void Bitwise_XOR_Average(cv::Mat &frame);
    void NotEqual(cv::Mat &frame);
    void ImageShiftUpLeft(cv::Mat &frame);
    void GradientXorSelfScale(cv::Mat &frame);
    void SmoothSourcePixel(cv::Mat &frame);
    void StrobeBlend(cv::Mat &frame);
    void FrameBars(cv::Mat &frame);
    void Sort_Vertical_Horizontal(cv::Mat &frame);
    void Sort_Vertical_Horizontal_Bitwise_XOR(cv::Mat &frame);
    void Scalar_Average_Multiply(cv::Mat &frame);
    void Scalar_Average(cv::Mat &frame);
    void Total_Average(cv::Mat &frame);
    void AlphaBlendImageXor(cv::Mat &frame);
    void FlashWhite(cv::Mat &frame);
    void FlashBlackAndWhite(cv::Mat &frame);
    void GaussianBlend(cv::Mat &frame);
    void RandomXor(cv::Mat &frame);
    void RandomXorFlash(cv::Mat &frame);
    void RandomAmountMedianBlur(cv::Mat &frame);
    void SoftXor(cv::Mat &frame);
    void SelfXorBlend(cv::Mat &frame);
    void SelfXorDoubleFlash(cv::Mat &frame);
    void SelfOrDoubleFlash(cv::Mat &frame);
    void BlendRowCurvedSqrt(cv::Mat &frame);
    void CycleShiftRGB(cv::Mat &frame);
    void CycleShiftRandomRGB(cv::Mat &frame);
    void CycleShiftRandomRGB_XorBlend(cv::Mat &frame);
    void CycleShiftRandomAlphaBlend(cv::Mat &frame);
    void VerticalColorBars(cv::Mat &frame);
    void GradientLeftRight(cv::Mat &frame);
    void GraidentUpDown(cv::Mat &frame);
    void GradientLeftRightInOut(cv::Mat &frame);
    void GradientUpDownInOut(cv::Mat &frame);
    void Lines(cv::Mat &frame);
    void ColorLines(cv::Mat &frame);
    void WhiteLines(cv::Mat &frame);
    void ThickWhiteLines(cv::Mat &frame);
    void UseLineObject(cv::Mat &frame);
    void TanAlphaGrid(cv::Mat &frame);
    void MedianBlendAnimation(cv::Mat &frame);
    void FibFlash(cv::Mat &frame);
    void ScaleFlash(cv::Mat &frame);
    void LeftLines(cv::Mat &frame);
    void Curtain(cv::Mat &frame);
    void RandomCurtain(cv::Mat &frame);
    void CurtainVertical(cv::Mat &frame);
    void RandomCurtainVertical(cv::Mat &frame);
    void inOrder(cv::Mat &frame);
    void inOrderBySecond(cv::Mat &frame);
    void DarkenFilter(cv::Mat &frame);
    void RandomFilterBySecond(cv::Mat &frame);
    void ThreeRandom(cv::Mat &frame);
    void inOrderAlpha(cv::Mat &frame);
    void inOrderAlphaXor(cv::Mat &frame);
    void SlideFilterXor(cv::Mat &frame);
    void SlideFilter(cv::Mat &frame);
    void RandomSlideFilter(cv::Mat &frame);
    void SlideUpDown(cv::Mat &frame);
    void SlideUpDownXor(cv::Mat &frame);
    void SlideUpDownRandom(cv::Mat &frame);
    void SlideSubFilter(cv::Mat &frame);
    void SlideSubUpDownFilter(cv::Mat &frame);
    void ParticleBlend(cv::Mat &frame);
    void ParticleFlash(cv::Mat &frame);
    void ExactImage(cv::Mat &frame);
    void ParticleAlpha(cv::Mat &frame);
    void BlendInAndOut(cv::Mat &frame);
    void BlendScaleInAndOut(cv::Mat &frame);
    void AcidGlitch(cv::Mat &frame);
    void XorBackwards(cv::Mat &frame);
    void LiquidFilter(cv::Mat &frame);
    void MatrixXorAnd(cv::Mat &frame);
    void XorAlpha(cv::Mat &frame);
    void AlphaAcidTrails(cv::Mat &frame);
    void SelfXorAverage(cv::Mat &frame);
    void RandomXorBlend(cv::Mat &frame);
    void RGBVerticalXor(cv::Mat &frame);
    void RGBVerticalXorScale(cv::Mat &frame);
    void RGBHorizontalXor(cv::Mat &frame);
    void RGBHorizontalXorScale(cv::Mat &frame);
    void FadeStrobe(cv::Mat &frame);
    void RGBMirror(cv::Mat &frame);
    void MirrorStrobe(cv::Mat &frame);
    void AndStrobe(cv::Mat &frame);
    void AndStrobeScale(cv::Mat &frame);
    void AndPixelStrobe(cv::Mat &frame);
    void AndOrXorStrobe(cv::Mat &frame);
    void AndOrXorStrobeScale(cv::Mat &frame);
    void FadeInAndOut(cv::Mat &frame);
    void BrightStrobe(cv::Mat &frame);
    void DarkStrobe(cv::Mat &frame);
    void ParticleFast(cv::Mat &frame);
    void RandomXorOpposite(cv::Mat &frame);
    void StrobeTransform(cv::Mat &frame);
    void InitBlend(cv::Mat &frame);
    void MoveUpLeft(cv::Mat &frame);
    void RandomStrobe(cv::Mat &frame);
    void RandomBlur(cv::Mat &frame);
    void Stuck(cv::Mat &frame);
    void StuckStrobe(cv::Mat &frame);
    void OrStrobe(cv::Mat &frame);
    void LagBlend(cv::Mat &frame);
    void SubFilter(cv::Mat &frame);
    void AddFilter(cv::Mat &frame);
    void BlendImageXor(cv::Mat &frame);
    void BlendImageAround_Median(cv::Mat &frame);
    void ImageBlendTransform(cv::Mat &frame);
    void RGBTrails(cv::Mat &frame);
    void RGBTrailsDark(cv::Mat &frame);
    void RGBTrailsAlpha(cv::Mat &frame);
    void RGBTrailsNegativeAlpha(cv::Mat &frame);
    void MovementRGBTrails(cv::Mat &frame);
    void RGBTrailsXor(cv::Mat &frame);
    void DifferenceStrobe(cv::Mat &frame);
    void BlackAndWhiteDifferenceStrobe(cv::Mat &frame);
    void DifferenceXor(cv::Mat &frame);
    void DifferenceRand(cv::Mat &frame);
    void DifferenceBrightStrobe(cv::Mat &frame);
    void PsycheTrails(cv::Mat &frame);
    void FourSquare(cv::Mat &frame);
    void EightSquare(cv::Mat &frame);
    void DiagonalSquare(cv::Mat &frame);
    void DiagonalSquareRandom(cv::Mat &frame);
    void SquareStretchDown(cv::Mat &frame);
    void SquareStretchRight(cv::Mat &frame);
    void SquareStretchUp(cv::Mat &frame);
    void SquareStretchLeft(cv::Mat &frame);
    void DarkTrails(cv::Mat &frame);
    void SoftFeedback(cv::Mat &frame);
    void SoftFeedbackFrames(cv::Mat &frame);
    void ResizeSoftFeedback(cv::Mat &frame);
    void SoftFeedback8(cv::Mat &frame);
    void SoftFeedbackFrames8(cv::Mat &frame);
    void ResizeSoftFeedback8(cv::Mat &frame);
    void ResizeSoftFeedbackSubFilter(cv::Mat &frame);
    void SoftFeedbackRandFilter(cv::Mat &frame);
    void SoftFeedback32(cv::Mat &frame);
    void SoftFeedbackFrames32(cv::Mat &frame);
    void ResizeSoftFeedback32(cv::Mat &frame);
    void SoftFeedbackRandFilter32(cv::Mat &frame);
    void SoftFeedbackSubFilter(cv::Mat &frame);
    void SoftFeedbackResize64(cv::Mat &frame);
    void SoftFeedbackResizeSubFilter(cv::Mat &frame);
    void SoftFeedbackResizeSubFilter64(cv::Mat &frame);
    void SoftFeedbackReszieSubFilter64_Negate(cv::Mat &frame);
    void SoftFeedbackReszieSubFilter64_Mirror(cv::Mat &frame);
    void HalfNegateStrobe(cv::Mat &frame);
    void MedianBlurXor(cv::Mat &frame);
    void NegateTrails(cv::Mat &frame);
    void RandomGradient(cv::Mat &frame);
    void RandomStrobeFlash(cv::Mat &frame);
    void RandomMirror(cv::Mat &frame);
    void RandomOther(cv::Mat &frame);
    void RandomXorFilter(cv::Mat &frame);
    void RandomMirrorBlend(cv::Mat &frame);
    void RandomMirrorAlphaBlend(cv::Mat &frame);
    void Bitwise_XOR_AlphaSubFilter(cv::Mat &frame);
    void AlphaBlendSubFilter(cv::Mat &frame);
    void GradientSubFilterXor(cv::Mat &frame);
    void XorBlend_SubFilter(cv::Mat &frame);
    void SmoothSubFilterAlphaBlend(cv::Mat &frame);
    void SmoothSubFilterXorBlend(cv::Mat &frame);
    void IntertwineSubFilter(cv::Mat &frame);
    void RandBlend(cv::Mat &frame);
    void EveryOther(cv::Mat &frame);
    void EveryOtherSubFilter(cv::Mat &frame);
    void SmoothRandomFilter(cv::Mat &frame);
    void RandomFilterRandomTimes(cv::Mat &frame);
    void RandomSubFilterRandomTimes(cv::Mat &frame);
    void AddToFrameSubFilter(cv::Mat &frame);
    void MirrorXor(cv::Mat &frame);
    void MirrorXorAll(cv::Mat &frame);
    void MirrorXorScale(cv::Mat &frame);
    void EnergyMirror(cv::Mat &frame);
    void SmoothSubFilter(cv::Mat &frame);
    void SmoothSubFilter16(cv::Mat &frame);
    void EnergizeSubFilter(cv::Mat &frame);
    void EnergizeSubFilter16(cv::Mat &frame);
    void EnergizeSubFilter32(cv::Mat &frame);
    void SmoothSubFilter32(cv::Mat &frame);
    void HalfAddSubFilter(cv::Mat &frame);
    void HalfXorSubFilter(cv::Mat &frame);
    void StaticXorBlend(cv::Mat &frame);
    void PsycheSort(cv::Mat &frame);
    void XorScale(cv::Mat &frame);
    void ChannelMedianSubFilter(cv::Mat &frame);
    void GaussianStrobe(cv::Mat &frame);
    void StrobeSort(cv::Mat &frame);
    void GlitchSortStrobe(cv::Mat &frame);
    void Bitwise_XOR_Blend(cv::Mat &frame);
    void Bitwise_XOR_Sort(cv::Mat &frame);
    void Bitwise_OR_Blend(cv::Mat &frame);
    void Bitwise_AND_Blend(cv::Mat &frame);
    void BitwiseColorMatrix(cv::Mat &frame);
    void PixelReverseXor(cv::Mat &frame);
    void PixelatedSubFilterSort(cv::Mat &frame);
    void SilverBlend(cv::Mat &frame);
    void RandomPixelOrderSort(cv::Mat &frame);
    void ImageXorAlpha(cv::Mat &frame);
    void ImageAverageXor(cv::Mat &frame);
    void PixelXorBlend(cv::Mat &frame);
    void SelfAlphaScale(cv::Mat &frame);
    void SelfScaleAlpha(cv::Mat &frame);
    void RainbowXorBlend(cv::Mat &frame);
    void FrameDifference(cv::Mat &frame);
    void SmallDiffference(cv::Mat &frame);
    void FadeBlend(cv::Mat &frame);
    void FilteredDifferenceSubFilter(cv::Mat &frame);
    void ExpandSquareSubFilter(cv::Mat &frame);
    void ExpandSquareBlendSubFilter(cv::Mat &frame);
    void ExpandSquareVerticalSubFilter(cv::Mat &frame);
    void DarkImageMedianBlend(cv::Mat &frame);
    void GammaDarken5(cv::Mat &frame);
    void GammaDarken10(cv::Mat &frame);
    void SelfAlphaScaleBlend(cv::Mat &frame);
    void FadeBars(cv::Mat &frame);
    void MirrorXorAlpha(cv::Mat &frame);
    void MirrorEnergizeSubFilter(cv::Mat &frame);
    void StrobeXor(cv::Mat &frame);
    void IntertwinedMirror(cv::Mat &frame);
    void BlurredMirror(cv::Mat &frame);
    void ShadeRGB(cv::Mat &frame);
    void InterRGB_SubFilter(cv::Mat &frame);
    void InterSmoothSubFilter(cv::Mat &frame);
    void InterRGB_Bars_XY(cv::Mat &frame);
    void InterRGB_Bars_X(cv::Mat &frame);
    void InterRGB_Bars_Y(cv::Mat &frame);
    void StoredFramesAlphaBlend_SubFilter(cv::Mat &frame);
    void BlendSubFilter(cv::Mat &frame);
    void BlendAlphaSubFilter(cv::Mat &frame);
    void ReverseFrameBlend(cv::Mat &frame);
    void ReverseFrameBlendSwitch(cv::Mat &frame);
    void DoubleRandomMirror(cv::Mat &frame);
    void Blend_AlphaSubFilter(cv::Mat &frame);
    void RandomBlendFilter(cv::Mat &frame);
    void DoubleRandomBlendFilter(cv::Mat &frame);
    void FlipBlendWH(cv::Mat &frame);
    void FlipBlendW(cv::Mat &frame);
    void FlipBlendH(cv::Mat &frame);
    void FlipBlendAll(cv::Mat &frame);
    void FrameMedianBlendSubFilter(cv::Mat &frame);
    void FrameBlurSubFilter(cv::Mat &frame);
    void ImageBlendSubFilter(cv::Mat &frame);
    void ImageBlendXorSubFilter(cv::Mat &frame);
    void ImageCollectionSubFilter(cv::Mat &frame);
    void SelfScaleXorIncrease(cv::Mat &frame);
    void Blend_RedGreenBlue(cv::Mat &frame);
    void XorBlend_RedGreenBlue(cv::Mat &frame);
    void BlendIncrease_RedGreenBlue(cv::Mat &frame);
    void Blend_RedReenBlue_Dark(cv::Mat &frame);
    void DarkModBlend(cv::Mat &frame);
    void PictureBuzz(cv::Mat &frame);
    void IncDifference(cv::Mat &frame);
    void IncDifferenceAlpha(cv::Mat &frame);
    void MirrorMedianBlend(cv::Mat &frame);
    void SubFilterMedianBlend(cv::Mat &frame);
    void DarkenBlend(cv::Mat &frame);
    void DarkCollectionSubFilter(cv::Mat &frame);
    void ChannelSort_NoBlend_Descending(cv::Mat &frame);
    void ChannelSort_NoBlend_Ascending(cv::Mat &frame);
    void Headrush(cv::Mat &frame);
    void DarkSmooth_Filter(cv::Mat &frame);
    void DarkSelfAlpha(cv::Mat &frame);
    void FlipMedian(cv::Mat &frame);
    void FlipMedianSubFilter(cv::Mat &frame);
    void FlipMirror(cv::Mat &frame);
    void FlipMirrorAverage(cv::Mat &frame);
    void FlipMirrorSubFilter(cv::Mat &frame);
    void ShuffleMedian(cv::Mat &frame);
    void ShuffleRGB(cv::Mat &frame);
    void ParticleSnow(cv::Mat &frame);
    void RandomPixels(cv::Mat &frame);
    void DarkRandomPixels(cv::Mat &frame);
    void MedianBlurSubFilter(cv::Mat &frame);
    void Bars(cv::Mat &frame);
    void ShuffleAlpha(cv::Mat &frame);
    void AlphaMorph(cv::Mat &frame);
    void ShuffleSelf(cv::Mat &frame);
    void PixelatedHorizontalLines(cv::Mat &frame);
    void PixelatedVerticalLines(cv::Mat &frame);
    void StrobeShuffle(cv::Mat &frame);
    void BlendBurred(cv::Mat &frame);
    void BlendCombinedValues(cv::Mat &frame);
    void RGBColorTrails(cv::Mat &frame);
    void BlendCombinedValueSubFilter(cv::Mat &frame);
    void BlendSubFilterAlpha(cv::Mat &frame);
    void GradientXorPixels(cv::Mat &frame);
    void PurpleRain(cv::Mat &frame);
    void PixelByPixelXor(cv::Mat &frame);
    void CopyXorAlpha(cv::Mat &frame);
    void AveragePixelsXor(cv::Mat &frame);
    void AveragePixelAlpha(cv::Mat &frame);
    void NegativeByRow(cv::Mat &frame);
    void AveragePixelCollection(cv::Mat &frame);
    void IncorrectLine(cv::Mat &frame);
    void XorShift(cv::Mat &frame);
    void StrobeXorAndOr(cv::Mat &frame);
    void XorWithSource(cv::Mat &frame);
    void AlphaBlendWithSource(cv::Mat &frame);
    void RGBSep1x(cv::Mat &frame);
    void RGBMedianBlend(cv::Mat &frame);
    void RGBMirror1(cv::Mat &frame);
    void RGBMirror1Median(cv::Mat &frame);
    void FlashMirror(cv::Mat &frame);
    void CollectionXorSourceSubFilter(cv::Mat &frame);
    void ReverseMirrorX(cv::Mat &frame);
    void MirrorXorAll_Reverse(cv::Mat &frame);
    void MirrorRGBReverse(cv::Mat &frame);
    void MirrorRGBReverseBlend(cv::Mat &frame);
    void BlendReverseSubFilter(cv::Mat &frame);
    void MirrorBitwiseXor(cv::Mat &frame);
    void SmoothBlendReverseSubFilter(cv::Mat &frame);
    void RandomIncrease(cv::Mat &frame);
    void MedianBlend16(cv::Mat &frame);
    void MedianBlendBufferSubFilter(cv::Mat &frame);
    void BGRBlend(cv::Mat &frame);
    void RGBBlend(cv::Mat &frame);
    void RGBBlendSubFilter(cv::Mat &frame);
    void DivideAndIncH(cv::Mat &frame);
    void DivideAndIncW(cv::Mat &frame);
    void XorOppositeSubFilter(cv::Mat &frame);
    void BlendSmoothSubFilter(cv::Mat &frame);
    void BlurSmooth(cv::Mat &frame);
    void BlurSmoothMedian(cv::Mat &frame);
    void BlurSmoothSubFilter(cv::Mat &frame);
    void BlurFlip(cv::Mat &frame);
    void BlurFlipSubFilter(cv::Mat &frame);
    void BlurMirrorGamma(cv::Mat &frame);
    void MedianBlendDark(cv::Mat &frame);
    void MedianBlendSubFilterEx(cv::Mat &frame);
    void EnergyMirrorDark(cv::Mat &frame);
    void AlphaBlendMirror(cv::Mat &frame);
    void MirrorAlphaBlendedImage(cv::Mat &frame);
    void AlphaBlendXorImage(cv::Mat &frame);
    void ShiftFrameSmoothSubFilter(cv::Mat &frame);
    void ShiftFrameStaticXorSubFilter(cv::Mat &frame);
    void IncreaseDecreaseGamma(cv::Mat &frame);
    void GammaIncDecIncrease(cv::Mat &frame);
    void RandomSubFilter(cv::Mat &frame);
    void TwistedVision(cv::Mat &frame);
    void TwistedMirror(cv::Mat &frame);
    void SelfScaleSortBlend(cv::Mat &frame);
    void FlashMedianBlend(cv::Mat &frame);
    void BlendWithFrameSubFilter(cv::Mat &frame);
    void AlphaBlendWithFrameSubFilter(cv::Mat &frame);
    void AlphaXorBlendWithFrameSubFilter(cv::Mat &frame);
    void XorBlendSubFilter(cv::Mat &frame);
    void FlipAlphaBlend(cv::Mat &frame);
    void RandomFlipFilter(cv::Mat &frame);
    void MirrorMedian(cv::Mat &frame);
    void FlipMatrixCollection(cv::Mat &frame);
    void MirrorMatrixCollection(cv::Mat &frame);
    void MirrorMatrixSource(cv::Mat &frame);
    void SelfScaleByFrame(cv::Mat &frame);
    void SmoothMedianRotateSubFilter(cv::Mat &frame);
    void SmoothCollectionAlphaBlend(cv::Mat &frame);
    void XorSubFilter(cv::Mat &frame);
    void XorAlphaSubFilter(cv::Mat &frame);
    void BlurXorAlphaSubFilter(cv::Mat &frame);
    void ImageXorFrame(cv::Mat &frame);
    void ImageXorFunction(cv::Mat &frame);
    void ImageXorAlphaBlend(cv::Mat &frame);
    void ImageAlphaXorMedianSubFilter(cv::Mat &frame);
    void ImageSmoothAlphaXorSubFilter(cv::Mat &frame);
    void ImageXorMirrorFilter(cv::Mat &frame);
    void ImageXorSubFilter(cv::Mat &frame);
    void ImageAlphaXorSubFilter(cv::Mat &frame);
    void SmoothTrailsBlend(cv::Mat &frame);
    void MatrixCollectionRGBXor(cv::Mat &frame);
    void RainbowGlitch(cv::Mat &frame);
    void RainbowGlichStrobe(cv::Mat &frame);
    void NegateSwitchStrobe(cv::Mat &frame);
    void StrobeAlphaShuffle(cv::Mat &frame);
    void ShuffleAlphaWithRGB(cv::Mat &frame);
    void ShuffleAlphaSubFilter(cv::Mat &frame);
    void ShuffleColorMap(cv::Mat &frame);
    void BlendWithRainbowSubFilter(cv::Mat &frame);
    void BlendWithJetSubFilter(cv::Mat &frame);
    void ColormapBlendSubFilter(cv::Mat &frame);
    void RandomColorMap(cv::Mat &frame);
    void SmoothMirrorBlurFlip(cv::Mat &frame);
    void RandomColorMapAlphaBlendSubFilter(cv::Mat &frame);
    void RandomOrder(cv::Mat &frame);
    void RandomOrderMedianBlendSubFilter(cv::Mat &frame);
    void MirrorOrder(cv::Mat &frame);
    void MirrorOrderSubFilter(cv::Mat &frame);
    void BlurMirrorOrder(cv::Mat &frame);
    void AveragePixelMirror(cv::Mat &frames);
    void ShuffleAlphaMedianBlend(cv::Mat &frame);
    void MirrorOrderAlpha(cv::Mat &frame);
    void FilterStrobeSubFilter(cv::Mat &frame);
    void ImageSubtractMedianBlend(cv::Mat &frame);
    void ImageDarkBlend(cv::Mat &frame);
    void ImageAverageDark(cv::Mat &frame);
    void ImageRemainderPixel(cv::Mat &frame);
    void AverageLinesBlend(cv::Mat &frame);
    void SoftFeedbackMirror(cv::Mat &frame);
    void AverageVerticalLinesBlend(cv::Mat &frame);
    void LinesMedianBlend(cv::Mat &frame);
    void XorSquare(cv::Mat &frame);
    void PixelValuesPlusOne(cv::Mat &frame);
    void AverageHorizontalFilter(cv::Mat &frame);
    void AverageVerticalFilter(cv::Mat &frame);
    void GradientAlphaXorHorizontal(cv::Mat &frame);
    void GradientAlphaXorVertical(cv::Mat &frame);
    void BlendImageWithSubFilter(cv::Mat &frame);
    void BlendImageWithSubFilterAlpha(cv::Mat &frame);
    void MedianBlendSoft(cv::Mat &frame);
    void AndImageSubFilterXor(cv::Mat &frame);
    void AlphaBlendImageSubFilterXor(cv::Mat &frame);
    void AlphaBlendImageSubFilterXorRev(cv::Mat &frame);
    void ParticleReleaseXor(cv::Mat &frame);
    void ParticleReleaseXorVec(cv::Mat &frame);
    void ParticleReleaseAlphaBlend(cv::Mat &frame);
    void ParticleReleaseWithImage(cv::Mat &frame);
    void ParticleReleaseSubFilter(cv::Mat &frame);
    void ParticleReleaseImageSubFilter(cv::Mat &frame);
    void ImageEnergy(cv::Mat &frame);
    void ImageEnergySubFilter(cv::Mat &frame);
    void ImageDistortion(cv::Mat &frame);
    void ImageDistortionSubFilter(cv::Mat &frame);
    void SmoothExactImageXorAlpha(cv::Mat &frame);
    void FeedbackColormap(cv::Mat &frame);
    void SmoothImageAlphaBlendMedian(cv::Mat &frame);
    void ImageDarkenSmoothMedian(cv::Mat &frame);
    void XorReverseImageSmooth(cv::Mat &frame);
    void ReverseSubFilterBlend(cv::Mat &frame);
    void ReverseSubFilterXor(cv::Mat &frame);
    void ImageReverseSubFilter(cv::Mat &frame);
    void SmoothRainbowMedian(cv::Mat &frame);
    void MirrorAlphaBlend(cv::Mat &frame);
    void ImageSmoothMedianBlend(cv::Mat &frame);
    void ImageSmoothMedianSubFilter(cv::Mat &frame);
    void ImageAlphaXorMedianBlend(cv::Mat &frame);
    void MatrixCollectionBlend(cv::Mat &frame);
    void MatrixCollectionSubFilter(cv::Mat &frame);
    void MatrixCollectionImageSubFilter(cv::Mat &frame);
    void MatrixCollectionBlurAlpha(cv::Mat &frame);
    void MatrixCollectionXor(cv::Mat &frame);
    void MatrixCollectionXor32(cv::Mat &frame);
    void MatrixCollectionRandomColorMap(cv::Mat &frame);
    void MatrixCollectionDarkXor(cv::Mat &frame);
    void MatrixCollectionRGB(cv::Mat &frame);
    void TrailsSubFilter(cv::Mat &frame);
    void TrailsSubFilter32(cv::Mat &frame);
    void CompareWithSubFilter(cv::Mat &frame);
    void MedianTrails(cv::Mat &frame);
    void SmoothMedianBlend(cv::Mat &frame);
    void ColorTransition(cv::Mat &frame);
    void ColorTransitionMedian(cv::Mat &frame);
    void ColorTransitionRandom(cv::Mat &frame);
    void ColorTransitionRandomMedian(cv::Mat &frame);
    void ColorTransitionSubFilter(cv::Mat &frame);
    void ColorTransitionImageSubFilter(cv::Mat &frame);
    void CurtainSubFilter(cv::Mat &frame);
    void RandomTrails(cv::Mat &frame);
    void RandomTrailsSubFilter(cv::Mat &frame);
    void CosSinMedianBlend(cv::Mat &frame);
    void TrailsRGB(cv::Mat &frame);
    void MatrixTrailsXorRandom(cv::Mat &frame);
    void CosSinMultiplyCollectionXor(cv::Mat &frame);
    void Filter8_Blend(cv::Mat &frame);
    void Filter8_SubFilter(cv::Mat &frame);
    void RandomSmoothAlphaMedian(cv::Mat &frame);
    void RandomAlphaBlendFilter(cv::Mat &frame);
    void RandomMirrorBitwiseXor(cv::Mat &frame);
    void SquareDivideSubFilter(cv::Mat &frame);
    void SquareSubFilter(cv::Mat &frame);
    void SquareSubFilter8(cv::Mat &frame);
    void SquareRandomFilter(cv::Mat &frame);
    void SquareRandomSubFilter(cv::Mat &frame);
    void ColorExpand(cv::Mat &frame);
    void ColorExpandSubFilter(cv::Mat &frame);
    void RotateImage(cv::Mat &frame);
    void RotateBlendImage(cv::Mat &frame);
    void RotateImageSubFilter(cv::Mat &frame);
    void RotateAlphaBlendImage(cv::Mat &frame);
    void FlipShuffle(cv::Mat &frame);
    void FlipRandom(cv::Mat &frame);
    void FlipOrder(cv::Mat &frame);
    void FlipStrobeSubFilter(cv::Mat &frame);
    void MirrorBlendFrame(cv::Mat &frame);
    void MirrorBlendVertical(cv::Mat &frame);
    void MirrorVerticalAndHorizontal(cv::Mat &frame);
    void BlendFor360(cv::Mat &frame);
    void MirrorSidesMedian(cv::Mat &frame);
    void MirrorSidesSubFilter(cv::Mat &frame);
    void MedianFrameAlphaBlendSubFilter(cv::Mat &frame);
    void MedianSubFilter(cv::Mat &frame);
    void ColorXorScale(cv::Mat &frame);
    void ColorXorScaleSubFilter(cv::Mat &frame);
    void ImageXorScale(cv::Mat &frame);
    void MatrixCollectionShiftSubFilter(cv::Mat &frame);
    void MatrixCollectionImageShiftSubFilter(cv::Mat &frame);
    void MatrixCollectionXorBlendAlphaBlend(cv::Mat &frame);
    void MatrixCollectionBlurImageXorAlpha(cv::Mat &frame);
    void MatrixCollectionBlurImageSubFilter(cv::Mat &frame);
    void MatrixCollectionBlurImageSubFilter16(cv::Mat &frame);
    void ImageAlphaBlendSubFilter(cv::Mat &frame);
    void MultipleMatrixCollectionSubFilter(cv::Mat &frame);
    void BlurAlphaSubFilter(cv::Mat &frame);
    void BlurImageSubFilter(cv::Mat &frame);
    void MedianBlendSubFilter(cv::Mat &frame);
    void MedianBlendImageSubFilter(cv::Mat &frame);
    void MedianBlendSelfBlend(cv::Mat &frame);
    void BlendHalfSubFilter(cv::Mat &frame);
    void BlurImageAlphaBlend(cv::Mat &frame);
    void BlurImageAlphaBlendSubFilter(cv::Mat &frame);
    void BlurImageAlphaBlendScaleSubFilter(cv::Mat &frame);
    void RandomAmountOfMedianBlur(cv::Mat &frame);
    void Bitwise_XOR_BlendFrame(cv::Mat &frame);
    void AlphaBlendWithSubFilter(cv::Mat &frame);
    void AlphaBlendScaleWithSubFilter(cv::Mat &frame);
    void GaussianBlendEx(cv::Mat &frame);
    void SimpleMatrixBlend(cv::Mat &frame);
    void MatrixBlendSubFilter(cv::Mat &frame);
    void SmoothMatrixBlendSubFilter(cv::Mat &frame);
    void BlurSmoothSubFilterAlphaBlend(cv::Mat &frame);
    void BlurSmoothAlphaXorBlendSubFilter(cv::Mat &frame);
    void BlurTwiceSubFilter(cv::Mat &frame);
    void BlurFrameBlendSubFilter(cv::Mat &frame);
    void BlurFrameSubFilter(cv::Mat &frame);
    void BlurSmoothMatrix(cv::Mat &frame);
    void MedianBlurInc(cv::Mat &frame);
    void GaussianBlurInc(cv::Mat &frame);
    void BlurSmoothMedianInc(cv::Mat &frame);
    void BlurSmoothGaussianInc(cv::Mat &frame);
    void BlurMatrixCollectionXor(cv::Mat &frame);
    void MatrixCollection8XorSubFilter(cv::Mat &frame);
    void BlurSmoothRevFilter(cv::Mat &frame);
    void SurroundingPixels(cv::Mat &frame);
    void SurroundingPixelsAlpha(cv::Mat &frame);
    void MatrixCollectionSurroundingPixels(cv::Mat &frame);
    void MatrixCollectionSurroundingPixelsSubFilter(cv::Mat &frame);
    void MatrixCollectionSurroundingPixelsImage(cv::Mat &frame);
    void MatrixCollectionSurroundingPixelsImageSubFilter(cv::Mat &frame);
    void ImageTransparent(cv::Mat &frame);
    void MatrixImageAlphaBlendSubFilter(cv::Mat &frame);
    void ImageAlphaCollectionSmoothBlend(cv::Mat &frame);
    void ImageRandomColormap(cv::Mat &frame);
    void ImageRandomColormapAlphaBlend(cv::Mat &frame);
    void ImageRandomColormapAlphaScale(cv::Mat &frame);
    void ImageRandomColormapSubFilter(cv::Mat &frame);
    void ImageShuffle(cv::Mat &frame);
    void ImageSubFilter(cv::Mat &frame);
    void ImageAlphaBlendWithFrameSubFilter(cv::Mat &frame);
    void ImageFadeInOut(cv::Mat &frame);
    void ImageFadeBlackInOut(cv::Mat &frame);
    void ImageFadeBlackInOutSubFilter(cv::Mat &frame);
    void ImageFadeFrameInOut(cv::Mat &frame);
    void ImageFadeFrameInOutSubFilter(cv::Mat &frame);
    void ImageFadeDouble(cv::Mat &frame);
    void BlendSubFilterAndImage(cv::Mat &frame);
    void FadeSubFilter(cv::Mat &frame);
    void FadeSubFilterRev(cv::Mat &frame);
    void ImageBlendSubFilterMedianBlend(cv::Mat &frame);
    void FadeSubFilterXor(cv::Mat &frame);
    void BlurXorSubFilter(cv::Mat &frame);
    void ColorFlashIncrease(cv::Mat &frame);
    void ScaleFilter(cv::Mat &frame);
    void NegativeDarkenXor(cv::Mat &frame);
    void ImageXor_SubFilter(cv::Mat &frame);
    void NegateBlendSubFilter(cv::Mat &frame);
    void StrobeNegatePixel(cv::Mat &frame);
    void StrobeNegateInOut(cv::Mat &frame);
    void ImageStrobeOnOff(cv::Mat &frame);
    void AlphaStrobeBlend(cv::Mat &frame);
    void CannyRandomPixels(cv::Mat &frame);
    void FrameImageFadeInOut(cv::Mat &frame);
    void FrameImageFadeInOutDouble(cv::Mat &frame);
    void ChangeEachSecond(cv::Mat &frame);
    void ShuffleImage(cv::Mat &frame);
    void ChangeImageEachSecond(cv::Mat &frame);
    void ChangeImageFilterOnOff(cv::Mat &frame);
    void ChangeXorEachSecond(cv::Mat &frame);
    void MorphXor(cv::Mat &frame);
    void MorphXorWithSubFilter(cv::Mat &frame);
    void MirrorEachSecond(cv::Mat &frame);
    void MirrorReverseSubFilter(cv::Mat &frame);
    void MirrorReverseSubFilterAlphaBlend(cv::Mat &frame);
    void Mirror_Xor_Combined(cv::Mat &frame);
    void MirrorFrameShuffle(cv::Mat &frame);
    void MirrorShuffleSmooth(cv::Mat &frame);
    void Mirror_Xor_Smooth(cv::Mat &frame);
    void XorFrameShuffle(cv::Mat &frame);
    void XorMirrorBlendFrame(cv::Mat &frame);
    void ImageXorSmooth(cv::Mat &frame);
    void SmoothSubFilter64(cv::Mat &frame);
    void SmoothMedian64(cv::Mat &frame);
    void SmoothMedian32_SubFilter(cv::Mat &frame);
    void SmoothAlphaMedian_SubFilter(cv::Mat &frame);
    void SmoothImage_SubFilter(cv::Mat &frame);
    void SmoothImageMedian_SubFilter(cv::Mat &frame);
    void SmoothImageAndSubFilter(cv::Mat &frame);
    void SmoothSubFilter90(cv::Mat &frame);
    void SmoothMedianImageSubFilter16(cv::Mat &frame);
    void ImageNegate(cv::Mat &frame);
    void ImageNegateAlphaBlend(cv::Mat &frame);
    void ImageNegateAlphaBlendSubFilter(cv::Mat &frame);
    void FrameNegateAlphaBlendImage(cv::Mat &frame);
    void DarkTrailsEffect(cv::Mat &frame);
    void DarkNegate(cv::Mat &frame);
    void ChannelSortMedianBlend(cv::Mat &frame);
    void MatrixCollectionMirrorDirection(cv::Mat &frame);
    void StrobeRandomChannel(cv::Mat &frame);
    void SplitFramesSort(cv::Mat &frame);
    void SplitFrameSortSubFilter(cv::Mat &frame);
    void MedianBlend64(cv::Mat &frame);
    void SplitFrameFilter(cv::Mat &frame);
    void SplitFrameBlend(cv::Mat &frame);
    void SplitFrameBlendSubFilter(cv::Mat &frame);
    void SplitFrameCollection(cv::Mat &frame);
    void SplitFrameMirror(cv::Mat &frame);
    void RandomChannels(cv::Mat &frame);
    void SmoothRandomChannels(cv::Mat &frame);
    void SmoothChannelSubFilter(cv::Mat &frame);
    void IncreaseRGB(cv::Mat &frame);
    void IncreaseColor(cv::Mat &frame);
    void SaturateBlend(cv::Mat &frame);
    void SaturateBlendSubFilter(cv::Mat &frame);
    void MaxRGB(cv::Mat &frame);
    void XorDifferenceFilter(cv::Mat &frame);
    void AlphaBlendChannelSort(cv::Mat &frame);
    void ColorTrailsFilter(cv::Mat &frame);
    void ColorTrailsSubFilter(cv::Mat &frame);
    void DarkNegateRainbowMedian(cv::Mat &frame);
    void IncreaseQuick(cv::Mat &frame);
    void IncreaseRandomIndex(cv::Mat &frame);
    void ImageChannelSubFilter(cv::Mat &frame);
    void ImageChannelChangeSubFilter(cv::Mat &frame);
    void ImageChannelRandom(cv::Mat &frame);
    void ImageChannelRandomSubFilter(cv::Mat &frame);
    void PixelateBlur(cv::Mat &frame);
    void PixelateBlock(cv::Mat &frame);
    void PixelateNoResize12(cv::Mat &frame);
    void PixelateNoResize8(cv::Mat &frame);
    void PixelateNoResize32(cv::Mat &frame);
    void PixelateNoResize16(cv::Mat &frame);
    void PixelateNoResize24(cv::Mat &frame);
    void PixelateBlurFilter(cv::Mat &frame);
    void PixelateBlurSubFilter(cv::Mat &frame);
    void MirrorXorImage(cv::Mat &frame);
    void MirrorXorSubFilter(cv::Mat &frame);
    void PixelXorImageSubFilter(cv::Mat &frame);
    void PixelAlphaImageSubFilter(cv::Mat &frame);
    void PixelScaleImageSubFilter(cv::Mat &frame);
    void PixelImageSubFilter(cv::Mat &frame);
    void PixelImageTex(cv::Mat &frame);
    void PixelImageXorSubFilter(cv::Mat &frame);
    void PixelRowMedianBlend(cv::Mat &frame);
    void IntertwineRows32(cv::Mat &frame);
    void IntertwineRows16(cv::Mat &frame);
    void IntertwineRows8(cv::Mat &frame);
    void IntertwineAlpha(cv::Mat &frame);
    void IntertwineRowsSubFilter(cv::Mat &frame);
    void IntertwineRows4(cv::Mat &frame);
    void Intertwine64x4(cv::Mat &frame);
    void Intertwine64X(cv::Mat &frame);
    void Intertwine64XSubFilter(cv::Mat &frame);
    void Intertwine64XPixel(cv::Mat &frame);
    void IntertwinePixels(cv::Mat &frame);
    void IntertwineColsX(cv::Mat &frame);
    void IntertwineCols16(cv::Mat &frame);
    void IntertwineCols8(cv::Mat &frame);
    void IntertwineCols32(cv::Mat &frame);
    void MirrorIntertwine(cv::Mat &frame);
    void MirrorIntertwineImage(cv::Mat &frame);
    void MirrorIntertwineImageSubFilter(cv::Mat &frame);
    void IntertwineImageSubFilter(cv::Mat &frame);
    void BlendWithImage(cv::Mat &frame);
    void IntertwineRowsReverse32(cv::Mat &frame);
    void IntertwineRowsReverse16(cv::Mat &frame);
    void IntertwineRowsReverse8(cv::Mat &frame);
    void IntertwineRowsReverse64X(cv::Mat &frame);
    void IntertwineRowsSwitch32(cv::Mat &frame);
    void IntertwineRowsSwitch16(cv::Mat &frame);
    void IntertwineRowsSwitch8(cv::Mat &frame);
    void IntertwineRows64(cv::Mat &frame);
    void IntertwineRowsReverse64(cv::Mat &frame);
    void IntertwineRowsSwitch64(cv::Mat &frame);
    void IntertwineShuffle(cv::Mat &frame);
    void InterwtineAlphaSubFilter(cv::Mat &frame);
    void IntertwineImageAndSubFilter(cv::Mat &frame);
    void IntertwineRowsAndCols(cv::Mat &frame);
    void IntertwineRowsAndColsSubFilter(cv::Mat &frame);
    void MatrixCollectionVariable(cv::Mat &frame);
    void MatrixCollectionVariableSubFilter(cv::Mat &frame);
    void MatrixCollectionVariableImage(cv::Mat &frame);
    void MatrixCollectionVariableImageSubFilter(cv::Mat &frame);
    void SmoothImageAverageSubFilter(cv::Mat &frame);
    void CallSubFilterBlend50(cv::Mat &frame);
    void CallSubFilterBlend25(cv::Mat &frame);
    void CallSubFilterBlend75(cv::Mat &frame);
    void IntertwineColsX2(cv::Mat &frame);
    void SmoothFrame64(cv::Mat &frame);
    void SmoothFrame32(cv::Mat &frame);
    void MatrixCollectionMedianBlendFilter(cv::Mat &frame);
    void MedianBlendIncreaseFilter(cv::Mat &frame);
    void MedianBlendNegate(cv::Mat &frame);
    void BlendWithFrameAndImageSubFilter(cv::Mat &frame);
    void ImageIntertwine32(cv::Mat &frame);
    void ImageIntertwine16(cv::Mat &Frame);
    void ImageIntertwine8(cv::Mat &frame);
    void ImageIntertwine64X(cv::Mat &frame);
    void IntertwineDoubleSubFilter(cv::Mat &frame);
    void IntertwineDoubleImageSubFilter(cv::Mat &frame);
    void IntertwineEachRowXSubFilter(cv::Mat &frame);
    void IntertwineGhost(cv::Mat &frame);
    void IntertwineGhost32(cv::Mat &frame);
    void IntertwineGhostSubFilter(cv::Mat &frame);
    void BlendWithOldFrame(cv::Mat &frame);
    void BlendWith16thFrame(cv::Mat &frame);
    void BlendTrailsFilter(cv::Mat &frame);
    void LineMoveInOut(cv::Mat &frame);
    void MatrixCollectionTrails(cv::Mat &frame);
    void MatrixCollectionRandom(cv::Mat &frame);
    void MatrixCollectionRandom(cv::Mat &frame);
    void MatrixCollectionRandomSmooth(cv::Mat &frame);
    void MatrixCollectionRandomDouble(cv::Mat &frame);
    void MatrixCollectionAddImage(cv::Mat &frame);
    void MatrixCollectionAlphaBlendSubFilter(cv::Mat &frame);
    void MatrixCollectionImageBlendSubFilter(cv::Mat &frame);
    void TwitchinGlitchin(cv::Mat &frame);
    void IntertwineRowsImageAlphaBlend(cv::Mat &frame);
    void ChannelSortSubFilter(cv::Mat &frame);
    void IntertwineRow2(cv::Mat &frame);
    void IntertwineRow720p(cv::Mat &frame);
    void IntertwineRow1080p(cv::Mat &frame);
    void IntertwineRow720pX2(cv::Mat &frame);
    void IntertwineRow1080pX2(cv::Mat &frame);
    void IntertwineCols1280(cv::Mat &frame);
    void IntertwineRowCols1280x720(cv::Mat &frame);
    void IntertwineRowsImage(cv::Mat &frame);
    void MedianBlendSquare(cv::Mat &frame);
    void SmoothIntertwineMedianBlend(cv::Mat &frame);
    void SmoothBlendMedian(cv::Mat &frame);
    void SmoothDoubleSubFilter(cv::Mat &frame);
    void AlphaBlendMedianSubFilter(cv::Mat &frame);
    void ReverseOnOff(cv::Mat &frame);
    void SmoothReverseSubFilter(cv::Mat &frame);
    void IntertwineWithSubFilter(cv::Mat &frame);
    void IntertwineWithImageAndSubFilter(cv::Mat &frame);
    void IntertwineFrameWithImage(cv::Mat &frame);
    void InterlaceVerticalFilter(cv::Mat &frame);
    void InterlaceHorizontalFilter(cv::Mat &frame);
    void IntertwineImageFlip(cv::Mat &frame);
    void IntertwineImageFlipSubFilter(cv::Mat &frame);
    void IntertwineFlipImageAndSubFilter(cv::Mat &frame);
    void IntertwineImageOnOff(cv::Mat &frame);
    void IntertwineVideoShuffle(cv::Mat &frame);
    void ImageFlipFilter(cv::Mat &frame);
    void FlipFrameFilter(cv::Mat &frame);
    // No filter (do nothing)
    void NoFilter(cv::Mat &frame);
    // Alpha blend with original image
    void BlendWithSource(cv::Mat &frame);
    // plugin must be implemented in project
    void plugin(cv::Mat &frame);
    // set Custom Filter callback function
    void setCustom(DrawFunction f);
    void setPlugin(DrawFunction f);
    void setProcMode(int value);
    void setSubFilter(int value);
    void clearSubFilter();
    // color maps
    void Negate(cv::Mat &frame);
    void ApplyColorMap(cv::Mat &frame);
    void AddInvert(cv::Mat &frame);
    // color correction
    void setBlendPercentage(const double &value);
    void setBrightness(cv::Mat &frame, double alpha, int beta);
    void setGamma(cv::Mat &frame, cv::Mat &outframe, double gamma);
    void setSaturation(cv::Mat &frame, int saturation);
    void AlphaBlend(const cv::Mat &one, const cv::Mat &two, cv::Mat &output, double alpha);
    void RealAlphaBlend(const cv::Mat &one, const cv::Mat &two, cv::Mat &output, double alpha);
    void AlphaBlendDouble(const cv::Mat &one, const cv::Mat &two, cv::Mat &output, double alpha1, double alpha2);
    void AlphaXorBlend(const cv::Mat &one, const cv::Mat &two, cv::Mat &output, double alpha);
    void AlphaXorBlendDouble(const cv::Mat &one, const cv::Mat &two, cv::Mat &output, double alpha1, double alpha2);
    void AlphaMovement(double *alpha, int *dir, double inc);
    void AlphaMovementMaxMin(double &alpha, int &dir, double speed, double max, double min);
    void PixelScaleAlpha(cv::Mat &frame, double amt);
    void DarkenImage(cv::Mat &frame, unsigned int size);
    void Pixelate(cv::Mat &frame, unsigned int size);
    void Add(cv::Mat &src, cv::Mat &add, bool sat = false);
    void Sub(cv::Mat &src, cv::Mat &sub, bool sat = false);
    void Xor(cv::Mat &dst, const cv::Mat &add);
    void Xor(const cv::Mat &input, const cv::Mat &add, cv::Mat &out);
    void ScalarAverage(const cv::Mat &frame, cv::Scalar &s);
    void TotalAverageOffset(cv::Mat &frame, unsigned long &value);
    void swapColors(cv::Mat &frame, int x, int y);
    void swapColors_(cv::Mat &frame, int x, int y);
    void procPos(int &direction, double &pos, double &pos_max, const double max_size = 15, double iter = 0.05);
    void setColorKeyRange(cv::Vec3b low, cv::Vec3b high);
    void setBlockedColorKeys(std::vector<Keys> &blocked);
    bool colorBounds(const cv::Vec3b &color, const cv::Vec3b &pixel, const cv::Vec3b &range_low, const cv::Vec3b &range_high);
    SearchType searchColors(const cv::Vec3b &color);
    bool compareColor(const cv::Vec3b &color, const cv::Vec3b &low, const cv::Vec3b &high);
    void setGrayColor(const cv::Vec3b &color);
    unsigned char size_cast(long val);
    unsigned char size_reset(long val);
    // Alpha Blend two filters and set to frame by alpha variable
    void filterFade(cv::Mat &frame, int filter1, int filter2, double alpha);
    void filterColorKeyed(const cv::Vec3b &color, const cv::Mat &orig, const cv::Mat &filtered, cv::Mat &output);
    void resetAlpha(int &dir, double &alpha);
    void resetAlpha(double &alpha);
    void SwapColors(cv::Vec3b &v);
    void FillRow(cv::Mat &frame, unsigned int row, unsigned char value);
    void Shuffle(int &index, cv::Mat &frame, std::vector<std::string> &filter_array);
    void AddMatVector(cv::Mat &frame, std::vector<cv::Mat> &v);
    void setColorMap(int map, cv::Mat &frame);
    void blendFilterWithColorMap(int filter, int map, cv::Mat &frame);
    void SwitchOrder(cv::Vec3b &frame, int order);
    void InterlaceFrames(cv::Mat &frame, const cv::Mat &copy1);
    void InterlaceFrames(cv::Mat &frame, cv::Mat *items, const int num_items);
    void pushSubFilter(int newsub);
    void popSubFilter();
    // draw functions / strings
    extern std::string *draw_strings;
    extern DrawFunction plugin_func;
    extern DrawFunction *draw_func;
    extern FilterType *filter_array;
    extern int draw_max;
    extern bool snapShot;
    extern bool reset_filter;
    extern double alpha_increase;
    extern std::unordered_map<std::string, int> filter_map;
    extern std::unordered_map<std::string, FilterType> filter_map_str;

    extern bool frames_released;
    extern std::vector<void *> all_objects;
    // Matrix Collection template
    template<int Size>
    class MatrixCollection {
    public:
        static constexpr int ArraySize = Size;
        MatrixCollection() : w(0), h(0) {
            for(int i = 0; i < Size; ++i)
                all_objects.push_back(&frames[i]);
        }
        cv::Mat frames[Size+4];
        int w, h;
        void shiftFrames(cv::Mat &frame) {
            if(resetFrame(frame)) {
    	        for(int i = Size-1; i > 0; --i) {
	                frames[i] = frames[i-1];
            	}
            	frames[0] = frame.clone();
            }
        }
        
        bool resetFrame(cv::Mat &frame) {
            int wx = frame.cols;
            int wh = frame.rows;
            // check if any frames were released.
            bool check_released = false;
            for(int i = 0; i < Size; ++i) {
                if(frames[i].empty()) {
                    check_released = true;
                    break;
                }
            }
            if(check_released == true || (w != wx || h != wh) || reset_filter == true || frames_released == true) {
                for(int i = 0; i < Size; ++i)
                    frames[i] = frame.clone();
                w = wx;
                h = wh;
                reset_filter = false;
                return false;
            }
            return true;
        }
        
        int size() const { return ArraySize; }
    };
    extern void release_all_objects();
    extern bool testSize(cv::Mat &frame);
    // Trails function
    template<int Size>
    void Smooth(cv::Mat &frame, MatrixCollection<Size> *collection, bool addframe = true) {
        if(addframe == true)
            collection->shiftFrames(frame);
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Scalar test;
                for(int q = 0; q < collection->size()-1; ++q) {
                    cv::Mat &framev = collection->frames[q];
                    cv::Vec3b pix = framev.at<cv::Vec3b>(z, i);
                    for(int j = 0; j < 3; ++j) {
                        test[j] += pix[j];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    test[j] /= (collection->size()-1);
                    pixel[j] = cv::saturate_cast<unsigned char>(test[j]);
                }
                swapColors(frame, z, i);// swap colors
                if(isNegative) invert(frame, z, i);// if isNegative invert pixel
            }
        }
    }
    
    template<int Size>
    void DarkSmooth(cv::Mat &frame, MatrixCollection<Size> *collection, int dark) {
        collection->shiftFrames(frame);
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Scalar test;
                for(int q = 1; q < collection->size(); ++q) {
                    cv::Mat &framev = collection->frames[q];
                    cv::Vec3b pix = framev.at<cv::Vec3b>(z, i);
                    for(int j = 0; j < 3; ++j) {
                        test[j] += pix[j];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    test[j] /= (collection->size());
                    test[j] /= dark;
                    pixel[j] /= dark;
                    pixel[j] = pixel[j]^static_cast<unsigned char>(test[j]);
                }
                swapColors(frame, z, i);// swap colors
                if(isNegative) invert(frame, z, i);// if isNegative invert pixel
            }
        }
    }
    // Trails function
    template<int Size>
    void StaticXor(cv::Mat &frame, MatrixCollection<Size> *collection, cv::Vec3b r) {
        collection->shiftFrames(frame);
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Scalar test;
                for(int q = 0; q < collection->size()-1; ++q) {
                    cv::Mat &framev = collection->frames[q];
                    cv::Vec3b pix = framev.at<cv::Vec3b>(z, i);
                    for(int j = 0; j < 3; ++j) {
                        test[j] += pix[j];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    test[j] /= (collection->size());
                    pixel[j] = static_cast<unsigned char>(test[j])^r[j];
                }
                swapColors(frame, z, i);// swap colors
                if(isNegative) invert(frame, z, i);// if isNegative invert pixel
            }
        }
    }
    // Trails function
    template<int Size>
    void SmoothRGB(cv::Mat &frame, MatrixCollection<Size> *collection) {
        collection->shiftFrames(frame);
        static int index = 0;
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Scalar test;
                for(int q = 0; q < collection->size()-1; ++q) {
                    cv::Mat &framev = collection->frames[q];
                    cv::Vec3b pix = framev.at<cv::Vec3b>(z, i);
                    for(int j = 0; j < 3; ++j) {
                        test[j] += pix[j];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                test[index] /= (collection->size()-1);
                pixel[index] = cv::saturate_cast<unsigned char>(test[index]);
                swapColors(frame, z, i);// swap colors
                if(isNegative) invert(frame, z, i);// if isNegative invert pixel
            }
        }
        ++index;
        if(index > 2)
            index = 0;
    }
    
    template<int Size, typename Func>
    void ImageDifference(cv::Mat &frame, MatrixCollection<Size> *collection, Func func_call, int range = 30) {
        collection->shiftFrames(frame);
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Scalar values;
                for(int q = 0; q < collection->size(); ++q) {
                    cv::Mat &pix_val = collection->frames[q];
                    cv::Vec3b pix = pix_val.at<cv::Vec3b>(z, i);
                    for(int j = 0; j < 3; ++j) {
                        values[j] += pix[j];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                bool found = false;
                for(int j = 0; j < 3; ++j) {
                    values[j] /= collection->size();
                    unsigned char val = static_cast<unsigned char>(values[j]);
                    if(pixel[j] > val+range || pixel[j] < val-range) {
                        found = true;
                        break;
                    }
                }
                if(found == true) {
                    func_call(pixel);
                }
            }
        }
    }
    template<int Size>
    void ImageCopyDifference(cv::Mat &frame,cv::Mat &filtered, MatrixCollection<Size> *collection, int range = 5) {
        if(frame.size() != filtered.size())
            return;
        collection->shiftFrames(frame);
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Scalar values;
                for(int q = 0; q < collection->size(); ++q) {
                    cv::Mat &pix_val = collection->frames[q];
                    cv::Vec3b pix = pix_val.at<cv::Vec3b>(z, i);
                    for(int j = 0; j < 3; ++j) {
                        values[j] += pix[j];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b copypix = filtered.at<cv::Vec3b>(z, i);
                bool found = false;
                for(int j = 0; j < 3; ++j) {
                    values[j] /= collection->size();
                    unsigned char val = static_cast<unsigned char>(values[j]);
                    if(pixel[j] > val+range || pixel[j] < val-range) {
                        found = true;
                        break;
                    }
                }
                if(found == true) {
                    pixel = copypix;
                }
            }
        }
    }
    
    template<int Size>
    void MatrixBlend(cv::Mat &frame, MatrixCollection<Size> *collection) {
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Scalar value;
                for(int j = 0; j < collection->size(); ++j) {
                    cv::Mat &frame1 = collection->frames[j];
                    cv::Vec3b pixel = frame1.at<cv::Vec3b>(z, i);
                    for(int q = 0; q < 3; ++q) {
                        value[q] += pixel[q];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    int val = 1+static_cast<int>(value[j]);
                    pixel[j] = static_cast<unsigned char>(pixel[j] ^ val);
                }
            }
        }
    }
    
    template<int row_size>
    void IntertwineRows(cv::Mat &frame, MatrixCollection<row_size> *collection, const int height) {
        collection->shiftFrames(frame);
        int index = 0;
        int pos = 0;
        for(int z = 0; z < frame.rows; ++z) {
            cv::Mat &current = collection->frames[index];
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b value = current.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    pixel[j] = value[j];
                }
            }
            ++pos;
            if(pos > height-1) {
                pos = 0;
                ++index;
                if(index > row_size-1)
                    index = 0;
            }
        }
    }
    
    template<int row_size>
    void IntertwineRows(cv::Mat &frame, MatrixCollection<row_size> *collection) {
        IntertwineRows(frame, collection, row_size);
    }
    
    template<int row_size>
    void IntertwineRowsReverse(cv::Mat &frame, MatrixCollection<row_size> *collection, const int height) {
        collection->shiftFrames(frame);
        int index = 0;
        int pos = 0;
        for(int z = 0; z < frame.rows; ++z) {
            cv::Mat &current = collection->frames[row_size-index-1];
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b value = current.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    pixel[j] = value[j];
                }
            }
            ++pos;
            if(pos > height-1) {
                pos = 0;
                ++index;
                if(index > row_size-1)
                    index = 0;
            }
        }
    }
    
    template<int row_size>
    void IntertwineRowsReverse(cv::Mat &frame, MatrixCollection<row_size> *collection) {
        IntertwineRowsReverse(frame, collection, row_size);
    }
    
    
    template<int row_size, typename F>
    void IntertwineRowsOperation(cv::Mat &frame, MatrixCollection<row_size> *collection, F func) {
        collection->shiftFrames(frame);
        int index = 0;
        int pos = 0;
        for(int z = 0; z < frame.rows; ++z) {
            cv::Mat &current = collection->frames[index];
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b value = current.at<cv::Vec3b>(z, i);
                func(pixel, value);
            }
            ++pos;
            if(pos > row_size-1) {
                pos = 0;
                ++index;
                if(index > row_size-1)
                    index = 0;
            }
        }
    }

    template<int col_size>
    void IntertwineCols(cv::Mat &frame, MatrixCollection<col_size> *collection, int width) {
        collection->shiftFrames(frame);
        int index = 0;
        int pos = 0;
        for(int i = 0; i < frame.cols; ++i) {
            cv::Mat &current = collection->frames[index];
            for(int z = 0; z < frame.rows; ++z) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b value = current.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    pixel[j] = value[j];
                }
            }
            ++pos;
            if(pos > width-1) {
                pos = 0;
                ++index;
                if(index > col_size-1)
                    index = 0;
            }
        }
    }
    
    template<int col_size>
    void IntertwineCols(cv::Mat &frame, MatrixCollection<col_size> *collection) {
        IntertwineCols(frame, collection, col_size);
    }
    
    template<int row_size>
    void IntertwineDoubleRows(cv::Mat &frame, MatrixCollection<row_size> *collection1, MatrixCollection<row_size> *collection2, int height) {
        int index_col = 0, index = 0;
        int pos = 0;
        for(int z = 0; z < frame.rows; ++z) {
            cv::Mat &copy1 = collection1->frames[index];
            cv::Mat &copy2 = collection2->frames[index];
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b pix_val[2];
                pix_val[0] = copy1.at<cv::Vec3b>(z, i);
                pix_val[1] = copy2.at<cv::Vec3b>(z, i);
                pixel = pix_val[index_col];
            }
            index_col = (index_col == 0) ? 1 : 0;
            ++pos;
            if(pos > height-1) {
                pos = 0;
                ++index;
                if(index > row_size-1) {
                    index = 0;
                }
            }
        }
    }
    
    template<int r_size>
    void MatrixVariable(cv::Mat &frame, MatrixCollection<r_size> *collection, int &depth, int &dir) {
        static constexpr int v_size = r_size;
        collection->shiftFrames(frame);
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Scalar values;
                for(int q = 0; q < depth; ++q) {
                    cv::Mat &frame = collection->frames[q];
                    cv::Vec3b pixel = frame.at<cv::Vec3b>(z, i);
                    for(int j = 0; j < 3; ++j) {
                        values[j] += pixel[j];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    int val = static_cast<int>(values[j]);
                    pixel[j] = pixel[j]^val;
                }
            }
        }
        if(dir == 1) {
            ++depth;
            if(depth > v_size-1)
                dir = 0;
        } else {
            --depth;
            if(depth <= 2)
                dir = 1;
    	}
    }
    // bound long values to size of a byte
    template<typename T>
    T size_type_cast(const long &val) {
        if(val >= 255) return 255;
        if(val <= 0) return 0;
        return static_cast<T>(val);
    }
    // point class
    class Point {
    public:
        Point();
        Point(const Point &p);
        Point(int xx, int yy);
        int x, y;
        void setPoint(int xx, int yy);
        Point &operator=(const Point &p);
    };
    // Rectangle class
    class Rect {
    public:
        Rect();
        Rect(const Rect &r);
        Rect(int xx, int yy, int ww, int hh);
        Rect(int xx, int yy);
        Rect(int xx, int yy, cv::Size s);
        Rect(Point pt, int ww, int hh);
        Rect(Point pt, cv::Size s);
        void setRect(int xx, int yy, int ww, int hh);
        Rect &operator=(const Rect &r);
        int x,y,w,h;
    };
    // classes to be used by the filter
    // Square class to hold broken up cv::Mat
    class Square {
    public:
        // constructor init's vars
        Square() : pos(0), width(0), height(0), x(0), y(0) {}
        // change the size of a square
        void setSize(const int &xx, const int &yy, const int &w, const int &h);
        // set position
        void setPos(const int &p);
        // copy image from cv::Mat
        void copyImage(const cv::Mat &f);
        // copy Image to Target Matrix
        void copyImageToTarget(int xx, int yy, cv::Mat &f);
        // get position
        int getPos() const { return pos; }
        // get square width
        int getWidth() const { return width; }
        // get square height
        int getHeight() const { return height; }
    protected:
        // protected vars
        int pos,width,height,x,y;
        cv::Mat image;
    };
    // Particle movement directions
    enum { DIR_UP=0, DIR_UP_LEFT, DIR_UP_RIGHT, DIR_DOWN, DIR_DOWN_LEFT, DIR_DOWN_RIGHT, DIR_LEFT, DIR_RIGHT };
    // contains info for each pixel
    class Particle {
    public:
        Particle() : x(0), y(0), dir(0), m_count(0) {}
        cv::Vec3b pixel;// color
        int x, y, dir; // position/direction
        int m_count; // counter
    };
    // class to process the pixel
    class ParticleEmiter {
    public:
        // initalize to null
        ParticleEmiter();
        // clean up after done
        ~ParticleEmiter();
        // set frame pixel values
        void set(cv::Mat &frame);
        // draw pixel values to frame
        void draw(cv::Mat &frame);
        void draw_blend(cv::Mat &frame);
        void draw_flash(cv::Mat &frame);
        void draw_alpha(cv::Mat &frame);
        void draw_move(cv::Mat &frame);
        void draw_op(cv::Mat &frame);
        
        // move pixel coordinates around
        void movePixels();
        // reset
        void reset();
    private:
        Particle **part; // array of pointers for Particles
        int w, h; // frame width/height
        int speed;
    };
    extern int colors[3];
    // class to use for random growing filtered rects.
    class Box {
    public:
        Box() : x(0), y(0), w(0), h(0), steps(0), index(0), frame_index(0) {}
        void initBox(int w, int h);
        void drawBox(cv::Mat &frame);
        void sizeBox();
        int x,y,w,h,steps,index,frame_index;
        static int frame_width, frame_height; // current resolution
    };
    
    class GridBox {
    public:
        GridBox();
        GridBox(const GridBox &gb);
        GridBox(const Rect &r, const cv::Vec3b &col);
        GridBox(const cv::Vec3b &col);
        Rect location;
        cv::Vec3b color;
        bool on;
        GridBox &operator=(const GridBox &gb);
    };
    
    class Grid {
    public:
        GridBox **boxes;
        Grid();
        ~Grid();
        void createGrid(cv::Mat &frame, int w, int h, int size);
        void updateGrid(int max);
        void Release();
        void cleanBoxes();
        void fillGrid(cv::Mat &frame);
        int g_w, g_h, g_s;
        std::vector<Point> points;
        std::default_random_engine rng;
        int current_offset;
        bool g_random;
    };
    
    class LineObject {
    public:
        ac::Rect line_size;
        cv::Vec3b color;
        bool on;
        int dir;
    };
    
    class HLine {
    public:
        HLine();
        void drawLines(cv::Mat &frame);
        void createLines(int size, int width, int height);
        void clearLines();
        bool empty() const { return lines.empty(); }
    protected:
        int w, h;
        std::vector<LineObject> lines;
    };
    
    bool operator<(const Point &p1, const Point &p2);
    
    // slow copy functions
    void copyMat(const cv::Mat &src,int src_x, int src_y, cv::Mat &target, const Rect &rc);
    void copyMat(const cv::Mat &src, const Point &p, cv::Mat &target, const Rect &rc);
    void copyMat(const cv::Mat &src, int x, int y, cv::Mat &target, int rx, int ry, int rw, int rh);
    void copyMat(const cv::Mat &src, const Rect &srcrc, cv::Mat &target, const Rect &dst);
    void fillRect(cv::Mat &m, const Rect &r, cv::Vec3b pixel);
    
    // Transform Template
    template<typename Func>
    void Transform(const cv::Mat &source, cv::Mat &output, Func func) {
        if(output.empty() || output.size() != source.size())
            output.create(source.size(), CV_8UC3);
        
        for(int z = 0; z < source.rows; ++z) {
            for(int i = 0; i < source.cols; ++i) {
                cv::Vec3b &pixel = output.at<cv::Vec3b>(z, i);
                cv::Vec3b value = source.at<cv::Vec3b>(z, i);
                func(value, i, z);
                pixel = value;
                swapColors(output, z, i);
                if(isNegative) invert(output, z, i);
            }
        }
    }
    
    template<typename F>
    void transformMat(cv::Mat &src, const Rect &rc,F func) {
        for(int z = rc.y; z < rc.y+rc.h && z < src.rows; ++z) {
            for(int i = rc.x; i < rc.x+rc.w && i < src.cols; ++i) {
                cv::Vec3b &pixel = src.at<cv::Vec3b>(z, i);
                func(pixel, i, z);
            }
        }
    }
    
}

extern ac::ParticleEmiter emiter;
void changePixel(cv::Mat &full_buffer, int i, int z, cv::Vec3b &buffer, double pos, double *count);

#endif
