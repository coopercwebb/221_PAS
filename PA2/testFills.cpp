#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <limits.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "filler.h"
#include "solidColorPicker.h"
#include "stripeColorPicker.h"
#include "quarterColorPicker.h"
#include "borderColorPicker.h"
#include "colorPicker.h"

using namespace std;
using namespace cs221util;

#define IMAGEDIR "images-original/"
#define SOLNIMGDIR "images-soln/"

#define FUNCTORTESTHEIGHT 300
#define FUNCTORTESTWIDTH 300
#define FUNCTORTESTFREQ 10
#define FUNCTORTESTX 40
#define FUNCTORTESTY 10
#define FUNCTORTESTRADIUS 45
#define FUNCTORTESTIMAGEW "images-original/white-300x300.png"
#define FUNCTORTESTIMAGEP "images-original/mr-300x300.png"

#define SOLIDX 60
#define SOLIDY 44
#define SOLIDTOLERANCE 0.25
#define SOLIDTESTIMAGE "images-original/krlkm-124x118.png"
#define SOLIDFRAMEFREQ 70

#define STRIPEX 54 
#define STRIPEY 50
#define STRIPETOLERANCE 0.25
#define STRIPETESTIMAGE "images-original/ibr-d-150x250.png"
#define STRIPEWIDTH 15
#define STRIPEFRAMEFREQ 720

#define QUARTERX 54
#define QUARTERY 50
#define QUARTERTOLERANCE 0.25
#define QUARTERTESTIMAGE "images-original/ibr-d-150x250.png"
#define QUARTERBRIGHT 96
#define QUARTERFRAMEFREQ 720

#define BORDERX 203
#define BORDERY 159
#define BORDERTOLERANCE 0.25
#define BORDERWIDTH 6
#define BORDERTESTIMAGE "images-original/mr-300x300.png"
#define BORDERFRAMEFREQ 320


PNG testColorPicker(ColorPicker& picker)
{
    PNG img;
    img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);
    RGBAPixel px;

    for (int x = 0; x < FUNCTORTESTWIDTH; x++){
        for (int y = 0; y < FUNCTORTESTHEIGHT; y++){
            RGBAPixel* p = img.getPixel(x,y);
            PixelPoint pp(x, y, *p);
            *p = picker(pp);
        }
    }

    return img;
}

TEST_CASE("colorPicker::basic solid","[weight=0][part=colorPicker]"){

    cout << "Entered colorPicker::basic solid..." << endl;

    RGBAPixel px(0, 255, 0); // green
    SolidColorPicker solidPicker(px);

    PNG result = testColorPicker(solidPicker);// result.convert();
    result.writeToFile("images-output/solidColorPickerTest.png");
    PNG expected; expected.readFromFile("images-soln/ex-solidColorPickerTest.png");
    REQUIRE(result == expected);
    
    cout << "Leaving colorPicker::basic solid..." << endl;
}

TEST_CASE("colorPicker::basic stripe","[weight=1][part=colorPicker]"){

    cout << "Entered colorPicker::basic stripe..." << endl;

    PNG imgtest, imgother;
    imgtest.readFromFile(STRIPETESTIMAGE);

    StripeColorPicker stripePicker(STRIPEWIDTH, RGBAPixel(255, 96, 96), RGBAPixel(255, 196, 196));

    PNG result = testColorPicker(stripePicker);// result.convert();
    result.writeToFile("images-output/stripeColorPickerTest.png");
    PNG expected; expected.readFromFile("images-soln/ex-stripeColorPickerTest.png");
    REQUIRE(result == expected);

    cout << "Leaving colorPicker::basic stripe..." << endl;
}

TEST_CASE("colorPicker::basic quarter","[weight=1][part=colorPicker]"){
    
    cout << "Entered colorPicker::basic quarter..." << endl;

    PNG imgtest;
    imgtest.readFromFile(FUNCTORTESTIMAGEP);

    QuarterColorPicker quarterPicker(imgtest, QUARTERBRIGHT);

    PNG result = testColorPicker(quarterPicker);// result.convert();
    result.writeToFile("images-output/quarterColorPickerTest.png");
    PNG expected; expected.readFromFile("images-soln/ex-quarterColorPickerTest.png");// expected.convert();
    REQUIRE(result == expected);

    cout << "Leaving colorPicker::basic quarter..." << endl;
}

TEST_CASE("colorPicker::basic border", "[weight=1][part=colorPicker]") {
  
    cout << "Entered colorPicker::basic border..." << endl;

    PNG imgtest;
    imgtest.readFromFile(FUNCTORTESTIMAGEW);
    PixelPoint p(BORDERX, BORDERY, *(imgtest.getPixel(BORDERX, BORDERY)));
    BorderColorPicker borderPicker(BORDERWIDTH, imgtest, *(imgtest.getPixel(BORDERX, BORDERY)), RGBAPixel(0, 255, 0), BORDERTOLERANCE);

    PNG result = testColorPicker(borderPicker);// result.convert();
    result.writeToFile("images-output/borderColorPickerTest.png");
    PNG expected; expected.readFromFile("images-soln/ex-borderColorPickerTest.png");
    REQUIRE(result == expected);

    cout << "Leaving colorPicker::basic border..." << endl;
}

TEST_CASE("fill::basic solid dfs","[weight=1][part=fill]"){
    
    cout << "Entered fill::basic solid dfs..." << endl;

    RGBAPixel px(188, 212, 174);
    SolidColorPicker solidPicker(px);

    filler::FillerConfig solidconfig;
    solidconfig.img.readFromFile(SOLIDTESTIMAGE);
    solidconfig.frameFreq = SOLIDFRAMEFREQ;
    solidconfig.tolerance = SOLIDTOLERANCE;
    solidconfig.seedpoint = PixelPoint(SOLIDX, SOLIDY, *solidconfig.img.getPixel(SOLIDX,SOLIDY));
    solidconfig.picker = &solidPicker;

    animation anim;
    anim = filler::FillDFS(solidconfig);
    PNG result = anim.write("images-output/dfssolid.gif");//  result.convert();
    result.writeToFile("images-output/dfssolid.png");

    PNG expected; expected.readFromFile("images-soln/ex-dfssolid.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic solid dfs..." << endl;
}


TEST_CASE("fill::basic solid bfs","[weight=1][part=fill]"){
    
    cout << "Entered fill::basic solid bfs..." << endl;

    RGBAPixel px(188, 212, 174);
    SolidColorPicker solidPicker(px);

    filler::FillerConfig solidconfig;
    solidconfig.img.readFromFile(SOLIDTESTIMAGE);
    solidconfig.frameFreq = SOLIDFRAMEFREQ;
    solidconfig.tolerance = SOLIDTOLERANCE;
    solidconfig.seedpoint = PixelPoint(SOLIDX, SOLIDY, *solidconfig.img.getPixel(SOLIDX, SOLIDY));
    solidconfig.picker = &solidPicker;

    animation anim;
    anim = filler::FillBFS(solidconfig);
    PNG result = anim.write("images-output/bfssolid.gif");// result.convert();
    result.writeToFile("images-output/bfssolid.png");

    PNG expected; expected.readFromFile("images-soln/ex-bfssolid.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic solid bfs..." << endl;
}

TEST_CASE("fill::basic stripe dfs", "[weight=1][part=fill]") {
    
    cout << "Entered fill::basic stripe dfs..." << endl;

    PNG stripetest;
    stripetest.readFromFile(STRIPETESTIMAGE);
    StripeColorPicker stripePicker(STRIPEWIDTH, RGBAPixel(255, 96, 96), RGBAPixel(255, 196, 196));

    filler::FillerConfig stripeconfig;
    stripeconfig.img = stripetest;
    stripeconfig.frameFreq = STRIPEFRAMEFREQ;
    stripeconfig.tolerance = STRIPETOLERANCE;
    stripeconfig.seedpoint = PixelPoint(STRIPEX, STRIPEY, *stripeconfig.img.getPixel(STRIPEX, STRIPEY));
    stripeconfig.picker = &stripePicker;

    animation anim;
    anim = filler::FillDFS(stripeconfig);
    PNG result = anim.write("images-output/dfsstripe.gif");// result.convert();
    result.writeToFile("images-output/dfsstripe.png");

    PNG expected; expected.readFromFile("images-soln/ex-dfsstripe.png");
    REQUIRE(result == expected);

    cout << "Leaving fill::basic stripe dfs..." << endl;
}

TEST_CASE("fill::basic stripe bfs", "[weight=1][part=fill]") {
  
    cout << "Entered fill::basic stripe bfs..." << endl;

    PNG stripetest;
    stripetest.readFromFile(STRIPETESTIMAGE);
    StripeColorPicker stripePicker(STRIPEWIDTH, RGBAPixel(255, 96, 96), RGBAPixel(255, 196, 196));

    filler::FillerConfig stripeconfig;
    stripeconfig.img = stripetest;
    stripeconfig.frameFreq = STRIPEFRAMEFREQ;
    stripeconfig.tolerance = STRIPETOLERANCE;
    stripeconfig.seedpoint = PixelPoint(STRIPEX, STRIPEY, *stripeconfig.img.getPixel(STRIPEX, STRIPEY));
    stripeconfig.picker = &stripePicker;

    animation anim;
    anim = filler::FillBFS(stripeconfig);
    PNG result = anim.write("images-output/bfsstripe.gif");// result.convert();
    result.writeToFile("images-output/bfsstripe.png");

    PNG expected; expected.readFromFile("images-soln/ex-bfsstripe.png");
    REQUIRE(result == expected);

    cout << "Leaving fill::basic stripe bfs..." << endl;
}

TEST_CASE("fill::basic quarter dfs","[weight=1][part=fill]"){
    
    cout << "Entered fill::basic quarter dfs..." << endl;

    PNG quartertest;
    quartertest.readFromFile(QUARTERTESTIMAGE);
    QuarterColorPicker quarterPicker(quartertest, QUARTERBRIGHT);

    filler::FillerConfig quarterconfig;
    quarterconfig.img = quartertest;
    quarterconfig.frameFreq = QUARTERFRAMEFREQ;
    quarterconfig.tolerance = QUARTERTOLERANCE;
    quarterconfig.seedpoint = PixelPoint(QUARTERX, QUARTERY, *quarterconfig.img.getPixel(QUARTERX, QUARTERY));
    quarterconfig.picker = &quarterPicker;

    animation anim;
    anim = filler::FillDFS(quarterconfig);
    PNG result = anim.write("images-output/dfsquarter.gif");// result.convert();
    result.writeToFile("images-output/dfsquarter.png");

    PNG expected; expected.readFromFile("images-soln/ex-dfsquarter.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic quarter dfs..." << endl;
}

TEST_CASE("fill::basic quarter bfs","[weight=1][part=fill]"){
    
    cout << "Entered fill::basic quarter bfs..." << endl;

    PNG quartertest;
    quartertest.readFromFile(QUARTERTESTIMAGE);
    QuarterColorPicker quarterPicker(quartertest, QUARTERBRIGHT);

    filler::FillerConfig quarterconfig;
    quarterconfig.img = quartertest;
    quarterconfig.frameFreq = QUARTERFRAMEFREQ;
    quarterconfig.tolerance = QUARTERTOLERANCE;
    quarterconfig.seedpoint = PixelPoint(QUARTERX, QUARTERY, *quarterconfig.img.getPixel(QUARTERX, QUARTERY));
    quarterconfig.picker = &quarterPicker;

    animation anim;
    anim = filler::FillBFS(quarterconfig);
    PNG result = anim.write("images-output/bfsquarter.gif");// result.convert();
    result.writeToFile("images-output/bfsquarter.png");

    PNG expected; expected.readFromFile("images-soln/ex-bfsquarter.png");
    REQUIRE(result == expected);

    cout << "Leaving fill::basic quarter bfs..." << endl;
}

TEST_CASE("fill::basic border dfs","[weight=1][part=fill]"){
  
    cout << "Entered fill::basic border dfs..." << endl;
  
    PNG imgtest;
    imgtest.readFromFile(BORDERTESTIMAGE);
    PixelPoint p(BORDERX, BORDERY, *(imgtest.getPixel(BORDERX, BORDERY)));
    BorderColorPicker borderPicker(BORDERWIDTH, imgtest, *(imgtest.getPixel(BORDERX, BORDERY)), RGBAPixel(0, 255, 0), BORDERTOLERANCE);

    filler::FillerConfig negborderconfig;
    negborderconfig.img = imgtest;
    negborderconfig.frameFreq = BORDERFRAMEFREQ;
    negborderconfig.tolerance = BORDERTOLERANCE;
    negborderconfig.seedpoint = p;
    negborderconfig.picker = &borderPicker;

    animation anim;
    anim = filler::FillDFS(negborderconfig);
    PNG result = anim.write("images-output/dfsborder.gif");// result.convert();
    result.writeToFile("images-output/dfsborder.png");

    PNG expected; expected.readFromFile("images-soln/ex-dfsborder.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic border dfs..." << endl;
}

TEST_CASE("fill::basic border bfs","[weight=1][part=fill]"){
  
    cout << "Entered fill::basic border bfs..." << endl;

    PNG imgtest;
    imgtest.readFromFile(BORDERTESTIMAGE);
    PixelPoint p(BORDERX, BORDERY, *(imgtest.getPixel(BORDERX, BORDERY)));
    BorderColorPicker borderPicker(BORDERWIDTH, imgtest, *(imgtest.getPixel(BORDERX, BORDERY)), RGBAPixel(0, 255, 0), BORDERTOLERANCE);

    filler::FillerConfig negborderconfig;
    negborderconfig.img = imgtest;
    negborderconfig.frameFreq = BORDERFRAMEFREQ;
    negborderconfig.tolerance = BORDERTOLERANCE;
    negborderconfig.seedpoint = p;
    negborderconfig.picker = &borderPicker;

    animation anim;
    anim = filler::FillBFS(negborderconfig);
    PNG result = anim.write("images-output/bfsborder.gif");// result.convert();
    result.writeToFile("images-output/bfsborder.png");

    PNG expected; expected.readFromFile("images-soln/ex-bfsborder.png");
    REQUIRE(result == expected);

    cout << "Leaving fill::basic border bfs..." << endl;
}
