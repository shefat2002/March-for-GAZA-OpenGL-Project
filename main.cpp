#include <windows.h>
#include <iostream>
#include <bits/stdc++.h>
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <cmath>
#include <string>

//<--------------MACROS START--------------->
//<--------CONSTANTS---------->
#define PI 3.14159265358979323846 // Define PI constant

//<--------CONSTANTS---------->

#define var(x, y) glVertex2f(x, y);
#define triangle glBegin(GL_TRIANGLES);
#define quads glBegin(GL_QUADS);
#define polygon glBegin(GL_POLYGON);
#define line glBegin(GL_LINES);
#define strip glBegin(GL_LINE_STRIP);
#define loop glBegin(GL_LINE_LOOP);
#define fan glBegin(GL_TRIANGLE_FAN);
#define tstrip glBegin(GL_TRIANGLE_STRIP);
#define end glEnd();

//<--------COLORS---------->
#define rgb(r, g, b) glColor3f(r, g, b); // RGB color
#define cRED glColor3f(1.0, 0.0, 0.0); // red color
#define cBLACK glColor3f(0.0, 0.0, 0.0); // black color
#define cGREEN glColor3f(0.0, 1.0, 0.0); // green color
#define cBLUE glColor3f(0.0, 0.0, 1.0); // blue color
#define cYELLOW glColor3f(1.0, 1.0, 0.0); // yellow color
#define cCYAN glColor3f(0.0, 1.0, 1.0); // cyan color
#define cMAGENTA glColor3f(1.0, 0.0, 1.0); // magenta color
#define cWHITE glColor3f(1.0, 1.0, 1.0); // white color
#define cGRAY glColor3f(0.5, 0.5, 0.5); // gray color
#define cDARKGRAY glColor3f(0.06, 0.06, 0.06); // dark gray color
#define cORANGE glColor3f(1.0, 0.5, 0.0); // orange color
#define cPURPLE glColor3f(0.5, 0.0, 1.0); // purple color
#define cPINK glColor3f(1.0, 0.2, 0.5); // pink color
#define cSKY glColor3f(0.88, 0.79, 0.6); // sky color
#define cGround glColor3f(0.82, 0.71, 0.53); // ground color
#define cBUILDING glColor3f(0.37, 0.3, 0.27); // building color
#define cFARBUILDING1 glColor3f(0.4, 0.36, 0.32); // back building1 color (dark)
#define cFARBUILDING2 glColor3f(0.64, 0.54, 0.48); // back building2 color (medium)
#define cFARBUILDING3 glColor3f(0.6, 0.55, 0.51); // back building3 color (light)
#define cGLASSBACK glColor3f(0.69, 0.71, 0.68); // glass back color
#define cGLASSFRONT glColor3f(0.83, 0.84, 0.81); // glass front color
#define cFLAGRED glColor3f(0.93, 0.18, 0.22); // flag red color
#define cFLAGGREEN glColor3f(0, 0.59, 0.23); // flag green color
#define cFLAGBLACK glColor3f(0.2, 0.17, 0.17); // flag black color
#define cSHADOW glColor3f(0.63, 0.49, 0.37); // shadow color
#define cSHADOW2 glColor3f(0.54, 0.4, 0.33); // shadow2 color
#define cGROUND1 glColor3f(0.62, 0.54, 0.47); // ground1 color
#define cGROUND2 glColor3f(0.61, 0.52, 0.42); // ground2 color
#define cGROUND3 glColor3f(0.56, 0.43, 0.33); // ground3 color
#define cGROUND4 glColor3f(0.36, 0.24, 0.14); // ground4 color
#define cFIRE glColor3f(0.93, 0.58, 0.33); // fire color
#define cBLACKUPPER glColor3f(0.15, 0.15, 0.15);
#define cBLACKLOWER glColor3f(0, 0, 0);
#define cMAPRED glColor3f(0.95, 0.02, 0.01);
#define cMAPGAZA glColor3f(0, 0.57, 0.21);

//<--------COLORS---------->
//<--------------MACROS END--------------->



//<-------Variables Start--------->
bool showFirstScreen = true;

//<-------Variables End--------->



//<-------Functions Start--------->

void init(void)
{
    glClearColor(01.0, 01.0, 01.0, 01.0); //GLfloat red,green,blue,alpha initial value 0 alpha values used by glclear to clear the color buffers
    glMatrixMode(GL_PROJECTION);  // To specify which matrix is the current matrix & projection applies subsequent matrix to projecton matrix stack
    glLoadIdentity();
    glOrtho(0, 2000.0, 2000, 0.0, -1.0, 1.0);
    //gluOrtho2D(0.0,300.0,0.0,300.0); // Orthographic representation; multiply the current matrix by an orthographic matrix 2D= left right,bottom,top equivalent near=-1,far=1
}

void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    fan
        var(cx, cy);

    for (int i = 0; i <= 100;i++) {
        float angle = 2 * 3.1416 * i / 100;
        float x = rx * cosf(angle);
        float y = ry * sinf(angle);
        var(x + cx, y + cy);
    }
    end
}

// Function to draw a filled arc for curved letters
void drawArc(float cx, float cy, float outerRadius, float innerRadius, float startAngle, float endAngle, int segments) {
    tstrip
        for (int i = 0; i <= segments; i++) {
            float theta = startAngle + (endAngle - startAngle) * (i / (float)segments);
            float cosTheta = cos(theta);
            float sinTheta = sin(theta);

            // Outer edge
            var(cx + outerRadius * cosTheta, cy + outerRadius * sinTheta);
            // Inner edge
            var(cx + innerRadius * cosTheta, cy + innerRadius * sinTheta);
        }
    end
}

//<-------Drawing Functions Start--------->
//<-------Text Drawing Functions Start--------->


GLuint base;
HFONT currentFont = NULL;

void buildFont(const char* fontName, int fontSize) {
    if (base != 0) {
        glDeleteLists(base, 96);
    }

    HFONT font = CreateFont(
        -fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
        fontName);

    HDC hdc = wglGetCurrentDC();
    SelectObject(hdc, font);

    base = glGenLists(96);
    wglUseFontBitmaps(hdc, 32, 96, base);

    currentFont = font;
}

void renderText(float x, float y, const char* text, const char* fontName, int fontSize) {
    buildFont(fontName, fontSize);  // Rebuild font every time
    glRasterPos2f(x, y);
    glPushAttrib(GL_LIST_BIT);
    glListBase(base - 32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}

//sample
void sampleText() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    renderText(10, 130, "GAZA", "Arial", 24);
    renderText(10, 90, "GAZA", "Impact", 30);
    renderText(10, 50, "GAZA", "Tahoma", 18);

    glFlush();
}

//<-------Text Drawing Functions End--------->
//<-------Drawing First Screen Start--------->

void drawA1()
{
    cBLACK
        polygon
        var(742, 1166); var(807, 1166); var(872, 833); var(845, 700);
    end

        polygon
        var(939, 1166); var(1003, 1166); var(900, 700); var(872, 833);
    end

        triangle
        var(872, 833); var(900, 700); var(845, 700);
    end
        cRED
        quads
        var(826, 1066); var(919, 1066); var(906, 1002); var(838, 1002);
    end
        quads
        var(742, 1166); var(807, 1166); var(840, 1005); var(778, 1000);
    end
        quads
        var(939, 1166); var(1003, 1166); var(980, 1061); var(911, 1045);
    end

}

void drawA2()
{
    cBLACK
        int x = 485;
    polygon
        var(742 + x, 1166); var(807 + x, 1166); var(872 + x, 833); var(845 + x, 700);
    end

        polygon
        var(939 + x, 1166); var(1003 + x, 1166); var(900 + x, 700); var(872 + x, 833);
    end

        triangle
        var(872 + x, 833); var(900 + x, 700); var(845 + x, 700);
    end
        cRED
        quads
        var(826 + x, 1066); var(919 + x, 1066); var(906 + x, 1002); var(838 + x, 1002);
    end
        quads
        var(742 + x, 1166); var(807 + x, 1166); var(840 + x, 1005); var(778 + x, 1000);
    end
        quads
        var(939 + x, 1166); var(1003 + x, 1166); var(980 + x, 1061); var(911 + x, 1045);
    end

}

void drawZ()
{
    cBLACK
        quads
        var(1024, 700); var(1215, 700); var(1215, 790); var(1024, 790);
    end

        quads
        var(1145, 790); var(1215, 790); var(1085, 1076); var(1024, 1076);
    end
        cRED
        quads
        var(1024, 1076); var(1215, 1076); var(1215, 1166); var(1024, 1166);
    end

}

void drawG()
{
    cBLACK
        quads
        var(588, 910); var(710, 910); var(710, 978); var(588, 978);
    end

        quads
        var(710, 910); var(710, 1076); var(650, 1076); var(650, 910);
    end

        int x = 156;
    quads
        var(710 - x, 794); var(710 - x, 1076); var(650 - x, 1076); var(650 - x, 794);
    end

        quads
        var(710, 794); var(710, 834); var(650, 834); var(650, 794);
    end

        drawArc(602, 810, 52, 109, 0, -PI, 50);

    cRED
        drawArc(602, 1050, 52, 109, 0, PI, 50);
}

void drawBloodOnText()
{
    cRED
        //G
        circle(12, 10, 514, 930);
    circle(5, 5, 514, 972);
    circle(4, 4, 542, 938);
    circle(4, 3, 497, 970);
    circle(12, 15, 514, 930);
    circle(11, 10, 522, 996);
    circle(11, 19, 522, 950);
    circle(8, 7, 524, 1010);
    circle(8, 9, 546, 1005);
    circle(4, 3, 536, 1009);
    circle(3, 3, 526, 1011);
    circle(4, 4, 498, 1005);
    circle(8, 9, 504, 1041);
    circle(12, 31, 526, 1037);
    circle(6, 4, 498, 1061);
    circle(6, 16, 544, 1050);

    circle(16, 17, 688, 966);
    circle(8, 7, 700, 972);
    circle(8, 7, 664, 1010);
    circle(8, 9, 676, 1000);
    circle(4, 3, 686, 1009);
    circle(10, 13, 700, 1025);
    circle(3, 3, 676, 998);
    circle(4, 4, 698, 995);
    circle(8, 9, 674, 1030);
    circle(12, 11, 6666, 1037);
    circle(6, 4, 668, 1061);
    circle(6, 10, 684, 1050);
    circle(12, 19, 662, 1060);
    circle(12, 15, 662, 1040);

    //A1
    circle(15, 22, 816, 968);
    circle(5, 5, 826, 970);
    polygon
        var(791, 946); var(804, 962); var(802, 1003); var(777, 1003);
    end
        circle(4, 4, 836, 970);
    circle(14, 14, 934, 1037);
    circle(14, 24, 923, 1043);
    circle(14, 33, 958, 1043);
    circle(14, 15, 820, 990);

    circle(4, 4, 934, 987);
    circle(4, 4, 923, 993);
    circle(4, 5, 958, 983);
    circle(7, 13, 937, 952);
    circle(14, 14, 913, 952);
    circle(12, 14, 921, 970);
    circle(14, 16, 933, 915);
    circle(4, 4, 934, 1003);
    circle(7, 8, 927, 1009);
    circle(4, 5, 958, 1000);

    //Z
    circle(4, 4, 1080, 994);
    polygon
        var(1078, 948); var(1100, 958); var(1124, 940); var(1140, 954);var(1073, 1104);var(1022, 1080);
    end
        circle(15, 17, 1118, 928);
    circle(5, 5, 1093, 930);
    circle(5, 8, 1143, 925);
    circle(5, 8, 1143, 895);
    circle(5, 4, 1158, 851);

    //A2
    circle(15, 22, 1300, 968);
    circle(5, 5, 1310, 970);
    polygon
        var(1275, 946); var(1288, 962); var(1286, 1003); var(1261, 1003);
    end
        circle(4, 4, 1320, 970);
    circle(14, 14, 1418, 1037);
    circle(14, 24, 1407, 1043);
    circle(14, 33, 1442, 1043);
    circle(14, 15, 1420, 990);

}

void drawBackgroundBlood()
{
    rgb(1, 0.85, 0.86);

    circle(70, 70, 313, 1215);
    circle(120, 70, 495, 1177);
    circle(450, 140, 983, 1076);
    circle(70, 70, 1430, 1115);
    circle(90, 90, 1108, 1267);
    circle(90, 90, 655, 1255);
    circle(70, 70, 1525, 989);
    circle(70, 70, 1693, 1215);
    circle(70, 70, 1775, 1268);
    circle(70, 70, 1405, 1262);
    circle(70, 70, 772, 1315);
    circle(70, 70, 793, 1355);
    circle(70, 70, 434, 1265);
    circle(70, 70, 326, 1269);
    circle(70, 70, 242, 1143);
    circle(70, 70, 999, 894);
    circle(70, 70, 755, 957);
    circle(70, 70, 1274, 876);
    circle(70, 70, 1059, 903);
    circle(25, 25, 335, 1013);
    circle(25, 25, 250, 1100);
    circle(25, 25, 366, 981);
    circle(25, 25, 405, 1020);
    circle(25, 25, 662, 1350);
    circle(45, 85, 1262, 1300);
    circle(45, 85, 1340, 1300);
    circle(45, 85, 1410, 1300);
    circle(65, 85, 1480, 1250);
    circle(105, 85, 1550, 1250);
    circle(105, 85, 880, 1350);
    circle(35, 85, 1002, 1350);
    circle(35, 35, 1100, 1350);
    circle(115, 55, 390, 1070);


    //Blood drops
    polygon
        var(295, 1271); var(295, 1412); var(315, 1412); var(315, 1270);
    end
        circle(10, 10, 304, 1418);
    polygon
        var(457, 1271); var(457, 1412); var(482, 1412); var(482, 1270);
    end
        circle(13, 13, 469, 1418);
    polygon
        var(530, 1271); var(530, 1440); var(560, 1440); var(560, 1270);
    end
        circle(15, 15, 545, 1445);
    polygon
        var(650, 1364); var(650, 1520); var(685, 1520); var(685, 1364);
    end
        circle(17, 17, 667, 1525);
    polygon
        var(730, 1271); var(730, 1440); var(760, 1440); var(760, 1270);
    end
        circle(15, 15, 745, 1445);
    polygon
        var(850, 1264); var(850, 1720); var(885, 1720); var(885, 1264);
    end
        circle(17, 17, 867, 1725);


    polygon
        var(995, 1271); var(995, 1462); var(1015, 1462); var(1015, 1270);
    end
        circle(10, 10, 1004, 1468);
    polygon
        var(1057, 1271); var(1057, 1412); var(1082, 1412); var(1082, 1270);
    end
        circle(13, 13, 1069, 1418);
    polygon
        var(1130, 1271); var(1130, 1440); var(1160, 1440); var(1160, 1270);
    end
        circle(15, 15, 1145, 1445);
    polygon
        var(1250, 1364); var(1250, 1520); var(1285, 1520); var(1285, 1364);
    end
        circle(17, 17, 1267, 1525);
    polygon
        var(1330, 1271); var(1330, 1440); var(1360, 1440); var(1360, 1270);
    end
        circle(15, 15, 1345, 1445);
    polygon
        var(1450, 1264); var(1450, 1720); var(1485, 1720); var(1485, 1264);
    end
        circle(17, 17, 1467, 1725);

    polygon
        var(334, 1001); var(345, 970); var(364, 961); var(383, 960);var(402, 970); var(390, 987); var(403, 1015); var(380, 1030);var(371, 1015); var(351, 1009);
    end



        polygon
        var(245, 1245); var(254, 1206); var(266, 1199); var(278, 1180); var(286, 1186); var(295, 1145); var(308, 1139); var(328, 1138);var(352, 1149); var(359, 1162); var(374, 1171); var(385, 1169);var(399, 1131); var(495, 1046); var(558, 1066); var(644, 1024);var(715, 1024); var(793, 928); var(1204, 905); var(1266, 931);var(1349, 900); var(1465, 961); var(1480, 1068); var(1602, 1134);var(1653, 1116); var(1682, 1168); var(1655, 1208); var(1612, 1184);var(1587, 1196); var(1550, 1182); var(1527, 1204); var(1505, 1214);var(1486, 1178); var(1427, 1177); var(1270, 1311); var(1190, 1304);var(1129, 1373); var(990, 1269); var(850, 1236); var(697, 1317);var(587, 1277); var(414, 1289); var(364, 1254); var(288, 1269);
    end

        for (int i = 0; i < 2000; ++i) {
            float x = 150 + (float)rand() / RAND_MAX * 1700;
            float y = 700 + (float)rand() / RAND_MAX * 1000;
            circle(5, 5, x, y);
        }
    for (int i = 0; i < 3500; ++i) {
        float x = 150 + (float)rand() / RAND_MAX * 1700;
        float y = 700 + (float)rand() / RAND_MAX * 1000;
        circle(1, 1, x, y);
    }
    for (int i = 0; i < 3500; ++i) {
        float x = 150 + (float)rand() / RAND_MAX * 1700;
        float y = 700 + (float)rand() / RAND_MAX * 1000;
        circle(2.2, 1.2, x, y);
    }
    for (int i = 0; i < 2500; ++i) {
        float x = 150 + (float)rand() / RAND_MAX * 1700;
        float y = 700 + (float)rand() / RAND_MAX * 1000;
        circle(2.2, 2, x, y);
    }
    for (int i = 0; i < 3500; ++i) {
        float x = 150 + (float)rand() / RAND_MAX * 1700;
        float y = 700 + (float)rand() / RAND_MAX * 1000;
        circle(2.3, 1.2, x, y);
    }
    for (int i = 0; i < 200; ++i) {
        float x = 150 + (float)rand() / RAND_MAX * 1700;
        float y = 700 + (float)rand() / RAND_MAX * 1000;
        circle(10.5, 10.5, x, y);
    }
    for (int i = 0; i < 50; ++i) {
        float x = 150 + (float)rand() / RAND_MAX * 1700;
        float y = 700 + (float)rand() / RAND_MAX * 1000;
        circle(12.5, 20.5, x, y);
    }
    for (int i = 0; i < 15; ++i) {
        float x = 150 + (float)rand() / RAND_MAX * 1700;
        float y = 700 + (float)rand() / RAND_MAX * 1000;
        circle(33.5, 30.5, x, y);
    }

    cWHITE
        polygon
        var(1411, 647);var(1411, 803);var(1549, 870);var(1714, 1118);var(1865, 1142); var(1909, 628);
    end
        polygon
        var(140, 1120);var(280, 1008);var(434, 862);var(455, 610);var(147, 610);
    end
        polygon
        var(434, 859);var(721, 856);var(981, 798);var(1252, 814);var(1610, 800);var(1390, 642);var(336, 660);
    end
        polygon
        var(138, 1231);var(222, 1318);var(271, 1330);var(271, 1500);var(142, 1683);var(136, 1231);
    end
        polygon
        var(150, 1430);var(608, 1518);var(663, 1559);var(940, 1884);var(940, 1800);var(644, 1892);var(150, 1800);
    end
        polygon
        var(1850, 1390);var(1850, 1950);var(1500, 1950);var(1500, 1390);
    end
        circle(80, 50, 1660, 1370);

    circle(200, 190, 1100, 1700);
    circle(140, 130, 1300, 1700);
    circle(80, 130, 750, 1630);

}

void drawText()
{
    drawG();
    drawA1();
    drawA2();
    drawZ();
}

void drawFirstScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackgroundBlood();
    drawText();
    drawBloodOnText();

    glutSwapBuffers();
}

//<-------Drawing First Screen End--------->



//<-------Drawing Second Screen Start--------->


void drawBackground()
{
    //sky
    cSKY
        quads
        var(0, 0); var(2000, 0); var(2000, 2000); var(0, 2000);
    end
        //ground
        cGround
        quads
        var(0, 1278);var(1998, 1091);var(2000, 2000);var(0, 2000);
    end

}
void drawLowerGround()
{
    quads
        cGROUND1
        var(0, 1600);var(2000, 1600);
    cBLACK
        var(2000, 2000);var(0, 2000);
}
void drawFar()
{
    //far building left side
    rgb(.93, .93, .93)
        fan
        var(2, 584);var(8, 575);var(22, 512);var(31, 471);var(52, 378);var(92, 303);var(103, 320);var(121, 375);var(121, 372);var(157, 284);var(205, 233);var(377, 219);var(401, 297);var(412, 345);var(472, 332);var(548, 339);var(574, 366);var(661, 372);var(787, 419);var(823, 458);var(934, 561);var(923, 578);var(809, 582);var(740, 561);var(650, 582);var(640, 629);var(658, 663);var(686, 701);var(677, 755);var(587, 749);var(412, 674);var(296, 656);var(187, 639);var(130, 705);var(91, 707);var(38, 614);var(11, 566);var(205, 419);var(320, 437);
    end
        rgb(.66, .66, .66)
        fan
        var(701, 681);var(440, 672);var(428, 647);var(464, 593);var(547, 545);var(548, 512);var(803, 576);var(836, 545);var(833, 488);var(908, 503);var(911, 414);var(887, 270);var(770, 290);var(643, 294);var(635, 234);var(775, 140);var(1147, 170);var(809, 357);var(826, 368);var(1397, 288);var(1403, 305);var(1255, 419);var(1253, 521);var(1279, 654);var(1153, 789);var(985, 825);var(878, 840);var(710, 867);var(650, 899);var(508, 791);var(430, 929);var(368, 842);var(316, 572);var(218, 291);var(307, 404);var(298, 215);var(407, 144);var(463, 281);var(601, 473);var(601, 662);var(497, 641);var(479, 42);var(608, 122);var(823, 120);var(1135, 342);var(1280, 596);var(1363, 671);var(1315, 845);var(1168, 947);var(944, 972);var(764, 923);var(689, 602);var(269, 27);var(433, 249);
    end
        rgb(0.83, 0.77, 0.58)
        fan
        var(961, 743);var(896, 848);var(784, 827);var(796, 723);var(829, 666);var(913, 654);var(965, 608);var(974, 639);var(1016, 665);var(1052, 651);var(1031, 701);var(1093, 719);var(1127, 746);var(1144, 776);var(1162, 825);
    rgb(0.53, 0.77, 0.58)
        var(1115, 852);var(1019, 872);var(953, 891);var(868, 894);var(815, 876);var(827, 782);var(935, 719);
    end

        rgb(.85, .78, .76)
        fan
        var(935, 719);var(1487, 764);var(1208, 879);var(1202, 713);var(1283, 653);var(1348, 657);var(1465, 677);var(1520, 680);var(1621, 681);var(1711, 681);var(1742, 684);var(1861, 714);var(1886, 725);var(1888, 767);var(1906, 780);var(1930, 807);var(1945, 843);var(1925, 885);var(1867, 921);var(1724, 950);var(1513, 945);var(1286, 926);var(1213, 887);var(1169, 758);var(1189, 672);var(1310, 627);
    end

        rgb(.73, .73, .73)
        fan
        var(1661, 635);var(1747, 576);var(1810, 540);var(1828, 522);var(1810, 483);var(1819, 533);var(1865, 480);var(1903, 464);var(1930, 461);var(1696, 477);var(1519, 567);var(1342, 278);var(1363, 179);var(1559, 96);var(1354, 101);var(1355, 47);var(1156, 81);var(1144, 12);var(1264, 6);var(1367, 6);var(1673, 8);var(1786, 27);var(1855, 9);var(2000, 71);var(2000, 260);var(2000, 549);var(2000, 728);var(2000, 807);var(1685, 819);var(1471, 833);var(1241, 699);var(1120, 612);var(965, 291);var(1090, 152);var(1307, 129);
    end
        rgb(0.37, 0.35, 0.37)
        fan
        var(1639, 824);var(1460, 911);var(1471, 867);var(1478, 834);var(1496, 819);var(1540, 800);var(1570, 791);var(1600, 783);var(1646, 776);var(1652, 764);var(1691, 756);var(1730, 750);var(1760, 749);var(1813, 762);var(1838, 770);var(1841, 773);var(1879, 777);var(1885, 768);var(1904, 749);var(1919, 734);var(1940, 798);var(1951, 827);var(1964, 875);var(1829, 995);var(1445, 984);var(1270, 942);var(1370, 861);var(1474, 839);
    end
}

void FarBuilding()
{
    //far building middle
    cFARBUILDING3 //light
        fan
        var(693, 1008);var(622, 1072);var(622, 1000);var(641, 991);var(650, 988);var(653, 988);var(660, 987);var(661, 982);var(662, 972);var(662, 964);var(662, 956);var(665, 944);var(678, 944);var(770, 945);var(771, 1052);var(661, 1063);var(606, 1061);var(623, 1000);
    end

        fan
        var(1100, 919);var(1079, 897);var(1128, 893);var(1130, 901);var(1130, 906);var(1137, 914);var(1129, 918);var(1122, 930);var(1118, 939);var(1120, 943);var(1105, 952);var(1091, 949);var(1080, 934);var(1078, 918);var(1079, 904);var(1080, 900);var(1090, 896);
    end
        fan
        var(1128, 984);var(1095, 950);var(1115, 940);var(1120, 949);var(1128, 956);var(1133, 956);var(1160, 966);var(1170, 963);var(1182, 963);var(1193, 961);var(1193, 961);var(1196, 977);var(1209, 1067);var(1224, 1150);var(1200, 1226);var(1090, 1215);var(1051, 1164);var(1055, 1083);var(1065, 1021);var(1080, 970);var(1092, 950);var(1099, 945);var(1103, 945);var(1114, 943);
    end


        //building middle1
        cFARBUILDING1
        fan
        var(771, 995);var(743, 1042);var(741, 966);var(748, 967);var(753, 964);var(757, 959);var(758, 953);var(762, 958);var(765, 957);var(784, 954);var(792, 954);var(796, 1041);var(743, 1043);var(743, 1037);
    end
        fan
        var(783, 924);var(768, 955);var(764, 950);var(758, 942);var(752, 935);var(747, 935);var(740, 932);var(737, 930);var(737, 926);var(738, 907);var(735, 893);var(736, 876);var(738, 876);var(744, 878);var(752, 880);var(754, 880);var(756, 880);var(765, 879);var(769, 877);var(777, 872);var(785, 870);var(790, 871);var(793, 881);var(807, 911);var(805, 937);var(802, 952);var(793, 956);var(787, 954);
    end
        fan
        var(786, 951);var(780, 921);var(764, 954);var(805, 957);var(781, 920);var(770, 933);
    end

        // building middle2
        cFARBUILDING1
        fan
        var(870, 979);var(828, 946);var(853, 920);var(857, 925);var(862, 934);var(870, 937);var(873, 929);var(873, 922);var(905, 1002);var(908, 1021);var(907, 1051);var(840, 1051);var(821, 1033);var(830, 946);var(843, 933);
    end
        fan
        var(906, 955);var(869, 979);var(872, 934);var(878, 922);var(872, 916);var(889, 897);var(889, 897);var(917, 914);var(924, 983);var(932, 1041);var(874, 1039);var(870, 979);var(875, 935);
    end

        //left side building
        cFARBUILDING2
        fan
        var(387, 811);var(343, 844);var(348, 775);var(375, 772);var(377, 744);var(380, 741);var(389, 741);var(390, 741);var(394, 738);var(394, 737);var(403, 736);var(409, 736);var(419, 736);var(421, 736);var(452, 772);var(453, 920);var(346, 845);var(340, 841);
    end
        fan
        var(476, 891);var(419, 848);var(518, 814);var(525, 871);var(501, 876);var(497, 895);var(495, 908);var(506, 923);var(512, 937);var(516, 950);var(521, 966);var(521, 983);var(521, 983);var(516, 993);var(498, 998);var(472, 1000);var(464, 1000);var(448, 999);var(447, 999);var(425, 967);var(426, 937);var(418, 926);var(408, 892);var(414, 875);var(422, 853);var(422, 839);
    end
        fan

        var(487, 966);var(517, 948);var(542, 1257);var(424, 1283);var(409, 991);var(488, 965);var(485, 1073);
    end
        fan
        var(556, 910);var(493, 841);var(494, 783);var(500, 775);var(505, 772);var(519, 769);var(529, 768);var(547, 771);var(569, 784);var(568, 813);var(566, 833);var(562, 851);var(573, 863);var(573, 880);var(576, 942);var(579, 986);var(572, 1026);var(563, 1049);var(565, 1074);var(505, 1082);var(497, 1014);var(500, 942);var(513, 865);var(529, 865);var(530, 865);
    end

        //right side building
        cFARBUILDING2
        fan
        var(1717, 974);var(1698, 1122);var(1701, 952);var(1740, 950);var(1740, 959);var(1736, 970);var(1746, 984);var(1781, 1160);
    end
        fan
        var(1717, 974);var(1698, 1122);var(1701, 952);var(1740, 950);var(1740, 959);var(1736, 970);var(1746, 984);var(1781, 1160);
    end
        fan
        var(1746, 1046);var(1705, 1002);var(1806, 1004);var(1825, 1214);var(1693, 1189);var(1702, 1002);var(1801, 1000);
    end



}
void Building1()
{
    //from the left side
            //#1
    cBLACK
        fan
        var(173, 787);var(152, 757);var(154, 751);var(162, 751);var(168, 757);var(177, 763);var(188, 758);var(202, 758);var(210, 769);var(216, 784);var(222, 798);var(226, 803);var(227, 809);var(223, 811);var(217, 813);var(213, 814);var(200, 814);var(194, 808);var(185, 804);var(178, 809);var(170, 810);var(166, 810);var(160, 801);var(159, 795);var(155, 780);var(152, 767);var(149, 758);var(150, 757);
    end


        cBUILDING
        fan
        var(95, 968);var(1, 579);var(152, 689);var(161, 705);var(150, 713);var(144, 737);var(176, 805);var(195, 802);var(222, 807);var(239, 815);var(239, 1361);var(0, 1361);var(1, 579);
    end
        cBLACK
        strip
        var(1, 579);var(152, 689);var(161, 705);var(150, 713);var(144, 737);var(176, 805);var(195, 802);var(222, 807);var(239, 815);var(239, 1361);var(0, 1361);var(1, 579);

    end

        //windows
        cBLACK
        quads
        var(160, 838);var(196, 850);var(193, 884);var(157, 874);
    end
        strip
        var(159, 828);var(204, 845);var(205, 888);var(158, 876);var(159, 829);
    end

        cBLACK
        quads
        var(68, 805);var(25, 792);var(24, 824);var(67, 841);
    end
        strip
        var(24, 779);var(77, 798);var(76, 845);var(24, 830);var(24, 778);
    end

        cBLACK
        quads
        var(165, 967);var(200, 975);var(197, 1006);var(164, 997);
    end
        strip
        var(165, 967);var(200, 975);var(197, 1006);var(164, 997);var(164, 958);var(206, 970);var(206, 1005);var(166, 998);var(165, 957);
    end
}
void Building2()
{
    //#2
    cBUILDING
        fan;
    var(348, 1020);var(229, 834);var(396, 828);var(424, 848);var(431, 861);var(429, 871);var(424, 884);var(431, 897);var(431, 916);var(442, 917);var(453, 922);var(457, 932); var(464, 1361);var(229, 1361);var(229, 834);
    end
        cBLACK
        strip
        var(229, 834);var(396, 828);var(424, 848);var(431, 861);var(429, 871);var(424, 884);var(431, 897);var(431, 916);var(442, 917);var(453, 922);var(457, 932); var(464, 1361);var(229, 1361);var(229, 834);
    //middle line
    var(396, 828);var(396, 1361);
    end
        //windows
        // window 1
        cBLACK
        quads
        var(251, 882);var(296, 880);var(295, 912);var(253, 914);
    end
        strip
        var(248, 878);var(300, 877);var(299, 917);var(251, 918);
    end

        // window 2
        cBLACK
        quads
        var(339, 880);var(378, 878);var(339, 909);var(378, 907);
    end
        strip
        var(338, 876);var(382, 871);var(381, 912);var(332, 915);
    end

        cBLACK
        quads
        var(402, 1020);var(437, 1028);var(434, 1059);var(401, 1050);
    end
        strip
        var(402, 1020);var(437, 1028);var(434, 1059);var(401, 1050);var(401, 1011);var(443, 1023);var(443, 1058);var(403, 1051);var(402, 1010);
    end
        cBLACK
        fan
        var(325, 944);var(273, 979);var(254, 1010);var(243, 1051);var(259, 1076);var(265, 1110);var(301, 1097);var(336, 1058);var(358, 1062);var(355, 1027);var(365, 1003);var(360, 982);var(341, 969);var(315, 974);var(318, 953);var(323, 949);var(325, 944);var(278, 1022);
    end
        strip
        var(270, 973);var(279, 969);var(307, 955);var(317, 949);var(318, 946);var(323, 940);var(331, 942);var(325, 950);var(322, 961);var(316, 970);var(321, 974);var(330, 967);var(339, 966);var(351, 966);var(361, 975);var(367, 984);var(369, 1002);var(367, 1016);var(358, 1030);var(362, 1060);var(362, 1070);var(355, 1070);var(351, 1070);var(346, 1069);var(345, 1065);var(344, 1058);var(339, 1063);var(306, 1097);var(297, 1103);var(285, 1111);var(274, 1114);var(266, 1113);var(258, 1109);var(259, 1099);var(258, 1078);var(254, 1073);var(241, 1051);var(243, 1050);var(247, 1046);var(275, 1025);var(251, 1012);var(251, 1007);var(255, 1004);var(272, 980);var(275, 976);var(279, 969);var(289, 959);var(299, 955);var(306, 951);
    end

        strip
        var(399, 1036);var(399, 1027);var(402, 1021);var(404, 1016);var(407, 1013);var(416, 1016);var(416, 1013);var(416, 1006);var(423, 999);var(430, 1001);var(432, 1002);var(440, 992);var(447, 990);var(445, 1000);var(443, 1003);var(441, 1009);var(441, 1017);var(445, 1024);var(446, 1027);var(448, 1029);var(450, 1034);var(440, 1035);var(433, 1037);var(429, 1039);var(422, 1040);var(412, 1039);var(405, 1046);var(398, 1048);var(399, 1042);
    end
}
void Building3()
{
    //#3
    cBUILDING
        fan
        var(690, 962);var(673, 885);var(686, 882);var(687, 896);var(693, 903);var(707, 897);var(709, 1026);var(726, 1225);var(683, 1231);var(670, 1019);var(673, 885);
    end
        fan
        var(600, 1120);var(520, 1031);var(670, 1019);var(685, 1234);var(512, 1247);var(520, 1031);
    end
        cBLACK
        fan
        var(541, 1098);var(552, 1088);var(557, 1074);var(571, 1065);var(578, 1070);var(608, 1064);var(613, 1078);var(610, 1094);var(598, 1112);var(587, 1092);var(583, 1114);var(566, 1128);var(548, 1119);var(547, 1099);var(551, 1087);
    end
        strip
        var(708, 939);var(703, 939);var(699, 942);var(695, 945);var(698, 953);var(701, 957);var(694, 964);var(694, 968);var(693, 984);var(693, 984);var(697, 987);var(698, 987);var(703, 983);var(706, 980);var(708, 976);
    end
}
void Building4()
{
    //#4
    cBUILDING
        fan
        var(812, 983);var(794, 1019);var(791, 878);var(797, 879);var(796, 874);var(800, 873);var(801, 878);var(808, 879);var(807, 903); var(820, 897); var(821, 881); var(828, 877);var(830, 1020);var(844, 1214);var(813, 1218);var(794, 1019);
    end
        fan
        var(882, 1130);var(711, 1026);var(829, 1021);var(838, 1025);var(873, 1025);var(880, 1040);var(898, 1039);var(901, 1025);var(912, 1018);var(913, 1011);var(937, 1211);var(723, 1226);var(711, 1026);
    end

        cBLACK
        strip
        var(795, 976);var(797, 972);var(799, 968);var(799, 965);var(799, 962);var(805, 957);var(809, 954);var(814, 958);var(816, 960);var(817, 966);var(816, 971);var(816, 978);var(819, 982);var(822, 984);var(826, 986);var(828, 990);var(828, 994);var(829, 999);
    end
        fan
        var(816, 924);var(813, 931);var(820, 940);var(825, 947);var(826, 941);var(825, 926);var(825, 916);
    end

}
void Building5()
{
    //#5
    cBUILDING
        fan
        var(1056, 902);var(918, 1211);var(914, 1010);var(913, 860);var(942, 828);var(955, 829);var(959, 835);var(971, 828);var(977, 820);var(985, 816);var(977, 785);var(987, 769);var(1004, 753);var(1096, 747);var(1111, 1186);var(918, 1211);
    end
        //line 3, 4, 5
        cBLACK
        strip
        var(512, 1247);var(520, 1031);var(670, 1019);var(673, 885);var(686, 882);var(687, 896);var(693, 903);var(707, 897);var(709, 1026);var(794, 1019);var(791, 878);var(797, 879);var(796, 874);var(800, 873);var(801, 878);var(808, 879);var(807, 903); var(820, 897); var(821, 881);var(828, 877);var(830, 1020);var(829, 1021);var(838, 1025);var(873, 1025);var(880, 1040);var(898, 1039);var(901, 1025);var(912, 1018);var(913, 1011);var(913, 860);var(942, 828);var(955, 829);var(959, 835);var(971, 828);var(977, 820);var(985, 816);var(977, 785);var(987, 769);var(1004, 753);var(1096, 747);var(1111, 1186);var(918, 1211);
    end

        //windows
        cBLACK
        quads
        var(994, 839);var(1030, 836);var(1031, 870);var(992, 871);
    end
        strip
        var(994, 839);var(1030, 836);var(1031, 870);var(992, 871);var(989, 839);var(988, 872);var(1037, 874);var(1036, 834);var(988, 838);
    end

        //destroyed
        cBLACK
        strip
        var(963, 868);var(962, 875);var(920, 915);var(923, 949);var(922, 994);var(969, 1022);var(978, 979);var(967, 942);var(988, 912);var(973, 888);var(969, 875);var(966, 870);var(965, 870);
    end
}
void Building6()
{
    //#6
    cBUILDING
        fan
        var(1272, 983);var(1181, 862);var(1229, 857);var(1236, 866);var(1228, 889);var(1238, 898);var(1259, 892);var(1288, 896);var(1287, 881);var(1287, 855);var(1346, 849);var(1359, 1151);var(1198, 1172);var(1181, 862);
    end
        strip
        cBLACK
        var(1181, 862);var(1229, 857);var(1236, 866);var(1228, 889);var(1238, 898);var(1259, 892);var(1288, 896);var(1287, 881);var(1287, 855);var(1346, 849);var(1359, 1151);var(1198, 1172);var(1181, 862);
    end

        //windows
        cBLACK
        quads
        var(1255, 920);var(1289, 921);var(1308, 964);var(1258, 945);
    end
        strip
        var(1248, 918);var(1255, 950);var(1314, 966);var(1293, 916);var(1246, 918);
    end

        //destroyed
        cBLACK
        fan
        var(1331, 923);var(1303, 952);var(1291, 978);var(1327, 1009);var(1340, 947);var(1333, 922);var(1330, 923);var(1323, 970);
    end
        strip
        var(1322, 915);var(1314, 929);var(1313, 940);var(1308, 950);var(1301, 956);var(1293, 965);var(1274, 978);var(1267, 986);var(1262, 989);var(1262, 990);var(1274, 982);var(1282, 974);var(1290, 970);var(1302, 964);var(1322, 956);var(1328, 950);var(1344, 941);
    end
}
void Building7()
{
    //#7

            //minar
    cGRAY
        triangle
        var(1395, 639); var(1405, 493); var(1428, 638);
    end
        cBLACK
        strip
        var(1395, 639); var(1405, 493); var(1428, 638);
    end
        cBLACK
        circle(72.6, 52, 1413, 670);

    cGRAY
        circle(70, 50, 1413, 670);
    //destroyed
    cBLACK
        fan
        var(1404, 629);var(1402, 636);var(1395, 646);var(1390, 650);var(1377, 656);var(1371, 657);var(1357, 657);var(1351, 657);var(1349, 654);var(1349, 650);var(1349, 650);var(1352, 645);var(1355, 640);var(1359, 638);var(1369, 633);var(1376, 630);var(1382, 625);var(1388, 623);var(1394, 625);var(1404, 628);
    end
        fan
        var(1377, 662);var(1356, 658);var(1356, 665);var(1357, 670);var(1351, 671);var(1354, 672);var(1359, 678);var(1362, 678);var(1368, 670);var(1377, 674);var(1387, 667);var(1385, 660);var(1378, 657);var(1374, 656);var(1367, 654);var(1358, 654);var(1357, 665);
    end
        fan
        var(1377, 662);var(1356, 658);var(1356, 665);var(1357, 670);var(1351, 671);var(1354, 672);var(1359, 678);var(1362, 678);var(1368, 670);var(1377, 674);var(1387, 667);var(1385, 660);var(1378, 657);var(1374, 656);var(1367, 654);var(1358, 654);var(1357, 665);var(1402, 645);var(1382, 660);var(1389, 670);var(1391, 666);var(1396, 662);var(1401, 662);var(1410, 656);var(1411, 651);var(1410, 648);var(1410, 638);var(1410, 633);var(1401, 626);var(1398, 624);var(1390, 634);var(1386, 644);var(1383, 649);var(1381, 666);var(1385, 669);
    end
        //moon
        cDARKGRAY
        fan
        var(1409, 489);var(1431, 473);var(1430, 477);var(1429, 480);var(1427, 483);var(1423, 490);var(1421, 491);var(1416, 494);var(1413, 495);var(1409, 495);var(1405, 495);var(1402, 494);var(1397, 492);var(1394, 491);var(1393, 489);var(1390, 487);var(1386, 485);var(1383, 481);var(1383, 479);var(1382, 477);var(1385, 477);var(1388, 479);var(1391, 481);var(1392, 483);var(1396, 483);var(1399, 483);var(1402, 484);var(1404, 485);var(1407, 485);var(1411, 485);var(1414, 485);var(1417, 483);var(1420, 483);var(1423, 481);var(1427, 478);var(1430, 477);
    end
        cBLACK
        strip
        var(1431, 473);var(1430, 477);var(1429, 480);var(1427, 483);var(1423, 490);var(1421, 491);var(1416, 494);var(1413, 495);var(1409, 495);var(1405, 495);var(1402, 494);var(1397, 492);var(1394, 491);var(1393, 489);var(1390, 487);var(1386, 485);var(1383, 481);var(1383, 479);var(1382, 477);var(1385, 477);var(1388, 479);var(1391, 481);var(1392, 483);var(1396, 483);var(1399, 483);var(1402, 484);var(1404, 485);var(1407, 485);var(1411, 485);var(1414, 485);var(1417, 483);var(1420, 483);var(1423, 481);var(1427, 478);var(1430, 477);
    end


        //building structure
        cBUILDING
        fan
        var(1419, 921);var(1341, 712);var(1480, 707);var(1494, 1158);var(1359, 1151);var(1341, 712);
    end
        strip
        cBLACK
        var(1341, 712);var(1480, 707);var(1494, 1158);var(1359, 1151);var(1341, 712);
    end

        //1st 
        cBUILDING
        polygon
        var(1347, 869);var(1485, 859);var(1486, 855);var(1488, 853);var(1488, 851);var(1487, 849);var(1487, 848);var(1490, 847);var(1493, 845);var(1495, 844);var(1495, 841);var(1495, 839);var(1493, 838);var(1493, 836);var(1495, 835);var(1495, 835);var(1499, 832);var(1501, 828);var(1501, 826);var(1500, 825);var(1497, 825);var(1321, 837);var(1321, 840);var(1322, 841);var(1324, 842);var(1326, 843);var(1328, 844);var(1332, 846);var(1331, 846);var(1331, 849);var(1331, 849);var(1333, 853);var(1335, 853);var(1337, 854);var(1340, 854);var(1342, 855);var(1341, 856);var(1340, 857);var(1341, 862);var(1343, 864);var(1344, 864);var(1346, 864);var(1346, 865);var(1348, 866);var(1348, 866);var(1348, 866);var(1349, 868);var(1416, 847);
    end
        cBLACK
        strip
        var(1318, 834);var(1500, 822);var(1500, 825);var(1500, 828);var(1498, 830);var(1497, 831);var(1497, 832);var(1495, 832);var(1493, 833);var(1492, 834);var(1491, 834);var(1489, 835);var(1487, 835);var(1484, 836);
    end
        strip
        var(1318, 834);var(1500, 822);var(1500, 825);var(1500, 828);var(1498, 830);var(1497, 831);var(1497, 832);var(1495, 832);var(1493, 833);var(1492, 834);var(1491, 834);var(1489, 835);var(1487, 835);var(1484, 836);var(1319, 833);var(1318, 836);var(1319, 837);var(1319, 839);var(1321, 841);var(1323, 843);var(1325, 844);var(1329, 845);var(1332, 845);var(1332, 845);var(1336, 846);var(1484, 832);
    end
        strip
        var(1333, 848);var(1332, 848);var(1332, 849);var(1331, 852);var(1335, 855);var(1335, 855);var(1343, 856);var(1455, 846);
    end


        //2nd
        cBUILDING
        polygon
        var(1342, 712);var(1320, 690);var(1491, 680);var(1481, 707);
    end
        cBLACK
        strip
        var(1342, 712);var(1337, 709);var(1341, 702);var(1482, 693);var(1481, 707);var(1342, 712);
    end
        strip
        var(1341, 712);var(1335, 706);var(1484, 697);var(1480, 709);
    end
        strip
        var(1324, 691);var(1320, 690);var(1491, 680);var(1490, 681);var(1324, 691);
    end

        //doors
        cBLACK
        fan
        var(1378, 789);var(1378, 746);var(1379, 748);var(1382, 752);var(1384, 757);var(1386, 764);var(1387, 768);var(1387, 773);var(1388, 778);var(1388, 783);var(1388, 827);var(1388, 828);var(1370, 830);var(1368, 807);var(1368, 790);var(1368, 777);var(1368, 769);var(1369, 765);var(1370, 761);var(1372, 755);var(1374, 752);var(1376, 750);var(1378, 745);
    end
        strip
        var(1364, 829);var(1363, 767);var(1363, 757);var(1365, 750);var(1367, 745);var(1369, 744);var(1372, 744);var(1375, 744);var(1378, 745);var(1380, 748);
    end

        cBLACK
        fan
        var(1431, 789);var(1422, 825);var(1418, 771);var(1418, 757);var(1419, 753);var(1420, 750);var(1422, 748);var(1424, 745);var(1427, 744);var(1430, 744);var(1430, 745);var(1432, 745);var(1435, 745);var(1435, 746);var(1436, 748);var(1437, 748);var(1438, 751);var(1439, 752);var(1440, 755);var(1441, 759);var(1441, 761);var(1442, 763);var(1442, 765);var(1442, 768);var(1442, 768);var(1442, 768);var(1442, 770);var(1443, 771);var(1443, 775);var(1443, 779);var(1443, 783);var(1442, 786);var(1442, 788);var(1443, 792);var(1443, 798);var(1444, 813);var(1443, 824);var(1440, 825);var(1432, 825);var(1425, 825);var(1422, 825);
    end
        strip
        var(1446, 827);var(1446, 820);var(1446, 815);var(1446, 810);var(1446, 805);var(1446, 800);var(1448, 792);var(1448, 785);var(1448, 777);var(1447, 769);var(1446, 761);var(1444, 753);var(1442, 749);var(1439, 747);var(1437, 744);var(1434, 743);var(1430, 743);
    end


        cBLACK
        fan
        var(1466, 790);var(1460, 823);var(1460, 793);var(1459, 772);var(1460, 765);var(1461, 760);var(1462, 754);var(1464, 751);var(1467, 752);var(1467, 754);var(1468, 757);var(1469, 761);var(1470, 766);var(1472, 775);var(1472, 784);var(1473, 791);var(1473, 808);var(1472, 822);var(1462, 823);
    end
        strip
        var(1466, 790);var(1460, 823);var(1460, 793);var(1459, 772);var(1460, 765);var(1461, 760);var(1462, 754);var(1464, 751);var(1467, 752);var(1467, 754);var(1468, 757);var(1469, 761);var(1470, 766);var(1472, 775);var(1472, 784);var(1473, 791);var(1473, 808);var(1472, 822);var(1462, 823);var(1462, 752);var(1464, 747);var(1466, 744);var(1468, 743);var(1471, 743);var(1471, 744);var(1471, 744);var(1474, 746);var(1474, 749);var(1475, 754);var(1475, 757);var(1476, 763);var(1476, 766);var(1477, 772);var(1478, 788);var(1477, 821);var(1478, 822);
    end



        //destroyed
        cGRAY
        fan
        var(1351, 951);var(1353, 945);var(1361, 936);var(1370, 926);var(1382, 931);var(1392, 925);var(1401, 922);var(1412, 929);var(1422, 936);var(1432, 945);var(1440, 969);var(1440, 973);var(1438, 987);var(1443, 995);var(1440, 1010);var(1431, 1026);var(1422, 1031);var(1414, 1050);var(1415, 1079);var(1410, 1102);var(1408, 1101);var(1394, 1085);var(1386, 1079);var(1380, 1083);var(1376, 1090);var(1367, 1101);var(1363, 1109);var(1360, 1118);var(1356, 1122);var(1351, 951);var(1392, 992);
    end
        cBLACK
        strip
        var(1351, 951);var(1353, 945);var(1361, 936);var(1370, 926);var(1382, 931);var(1392, 925);var(1401, 922);var(1412, 929);var(1422, 936);var(1432, 945);var(1440, 969);var(1440, 973);var(1438, 987);var(1443, 995);var(1440, 1010);var(1431, 1026);var(1422, 1031);var(1414, 1050);var(1415, 1079);var(1410, 1102);var(1408, 1101);var(1394, 1085);var(1386, 1079);var(1380, 1083);var(1376, 1090);var(1367, 1101);var(1363, 1109);var(1360, 1118);var(1356, 1122);var(1351, 951);
    end

        cGRAY
        fan
        var(1457, 921);var(1459, 912);var(1470, 913);var(1475, 915);var(1479, 921);var(1480, 927);var(1480, 935);var(1476, 936);var(1473, 948);var(1466, 949);var(1460, 943);var(1457, 941);var(1458, 933);var(1457, 926);var(1457, 921);var(1468, 927);
    end
        cBLACK
        strip
        var(1457, 921);var(1459, 912);var(1470, 913);var(1475, 915);var(1479, 921);var(1480, 927);var(1480, 935);var(1476, 936);var(1473, 948);var(1466, 949);var(1460, 943);var(1457, 941);var(1458, 933);var(1457, 926);var(1457, 921);
    end

        cGRAY
        fan
        var(1472, 1127);var(1491, 1079);var(1487, 1080);var(1483, 1084);var(1475, 1087);var(1469, 1092);var(1458, 1094);var(1450, 1095);var(1448, 1098);var(1443, 1099);var(1443, 1104);var(1444, 1110);var(1438, 1118);var(1438, 1119);var(1439, 1129);var(1443, 1136);var(1450, 1141);var(1457, 1142);var(1463, 1146);var(1465, 1148);var(1465, 1155);var(1458, 1165);var(1458, 1166);var(1468, 1165);var(1479, 1163);var(1485, 1158);var(1492, 1153);var(1491, 1079);
    end
        cBLACK
        strip
        var(1491, 1079);var(1487, 1080);var(1483, 1084);var(1475, 1087);var(1469, 1092);var(1458, 1094);var(1450, 1095);var(1448, 1098);var(1443, 1099);var(1443, 1104);var(1444, 1110);var(1438, 1118);var(1438, 1119);var(1439, 1129);var(1443, 1136);var(1450, 1141);var(1457, 1142);var(1463, 1146);var(1465, 1148);var(1465, 1155);var(1458, 1165);var(1458, 1166);var(1468, 1165);var(1479, 1163);var(1485, 1158);var(1492, 1153);
    end
}
void Building8()
{
    //#8
    cBUILDING
        polygon
        var(1493, 1170);var(1482, 924);var(1648, 895);var(1702, 924);var(1709, 1161);
    end
        cBLACK
        strip
        var(1493, 1170);var(1482, 924);var(1648, 895);var(1702, 924);var(1709, 1161);
    end
        line
        var(1648, 895);var(1650, 1165);
    end

        //window
        cBLACK
        quads
        var(1543, 963);var(1583, 958);var(1582, 982);var(1544, 985);
    end
        strip
        var(1583, 958);var(1582, 982);var(1534, 987);var(1534, 957);var(1583, 951);var(1584, 958);
    end

        //destroyed
        cBLACK
        strip
        var(1527, 913);var(1531, 917);var(1531, 923);var(1536, 930);var(1536, 935);var(1544, 941);var(1547, 937);var(1555, 937);var(1558, 933);var(1558, 930);var(1554, 923);var(1558, 923);var(1561, 919);var(1560, 915);var(1563, 910);var(1564, 908);
    end
        strip
        var(1580, 1123);var(1578, 1113);var(1577, 1108);var(1572, 1093);var(1566, 1083);var(1562, 1078);var(1561, 1069);var(1564, 1060);var(1566, 1052);var(1568, 1039);var(1571, 1033);var(1575, 1029);var(1579, 1024);var(1582, 1021);var(1587, 1014);var(1594, 1014);var(1592, 1022);var(1596, 1030);var(1600, 1033);var(1608, 1035);var(1614, 1037);var(1616, 1040);var(1620, 1048);var(1621, 1056);var(1620, 1069);var(1616, 1082);var(1614, 1094);var(1606, 1107);var(1599, 1116);var(1589, 1121);var(1583, 1125);
    end
        strip
        var(1703, 938);var(1699, 938);var(1696, 939);var(1692, 939);var(1690, 940);var(1686, 942);var(1682, 946);var(1679, 955);var(1676, 963);var(1680, 967);var(1681, 974);var(1679, 978);var(1674, 981);var(1673, 991);var(1672, 1001);var(1677, 1005);var(1682, 1007);var(1687, 1008);var(1691, 1006);var(1696, 1001);
    end
}
void Building9()
{
    //#9
    cBUILDING
        fan
        var(1955, 880);var(2000, 731);var(1949, 738);var(1937, 787);var(1832, 800);var(1822, 820);var(1810, 833);var(1785, 839);var(1789, 1155);var(2000, 1159);var(2000, 731);
    end
        cBLACK
        strip
        var(2000, 731);var(1949, 738);var(1937, 787);var(1832, 800);var(1822, 820);var(1810, 833);var(1785, 839);var(1789, 1155);var(2000, 1159);var(2000, 731);
    end

        //window
        cBLACK
        quads
        var(1825, 874);var(1886, 867);var(1885, 897);var(1821, 901);
    end
        strip
        var(1886, 867);var(1885, 897);var(1821, 901);var(1813, 900);var(1813, 865);var(1889, 857);var(1886, 866);
    end
        quads
        var(1956, 860);var(1998, 853);var(1998, 884);var(1954, 888);
    end
        strip
        var(1998, 884);var(1954, 888);var(1946, 888);var(1947, 853);var(1999, 847);
    end

        //destroyed
        cBLACK
        strip
        var(1785, 943);var(1811, 924);var(1822, 924);var(1836, 925);var(1839, 928);var(1849, 936);var(1850, 937);var(1848, 950);var(1855, 955);var(1852, 962);var(1860, 968);var(1862, 969);var(1859, 974);var(1859, 981);var(1856, 982);var(1850, 982);var(1854, 988);var(1842, 987);var(1834, 988);var(1826, 994);var(1814, 1001);var(1803, 1004);var(1792, 1005);var(1785, 1002);
    end

        cGRAY
        fan
        var(1885, 996);var(1898, 972);var(1911, 939);var(1919, 925);var(1939, 923);var(1978, 928);var(1986, 933);var(1991, 937);var(1997, 945);var(1997, 954);var(1997, 969);var(1998, 986);var(1998, 994);var(1933, 1001);var(1912, 1001);var(1889, 1000);var(1885, 999);var(1884, 995);var(1949, 966);
    end
        cBLACK
        strip
        var(1885, 996);var(1898, 972);var(1911, 939);var(1919, 925);var(1939, 923);var(1978, 928);var(1986, 933);var(1991, 937);var(1997, 945);var(1997, 954);var(1997, 969);var(1998, 986);var(1998, 994);var(1933, 1001);var(1912, 1001);var(1889, 1000);var(1885, 999);var(1884, 995);
    end

}
void Flag()
{
    //stand
    cBLACK
        quads
        var(1576, 905);var(1578, 789);var(1579, 789);var(1579, 906);
    end





        //black
        cFLAGBLACK
        fan
        var(1608, 818);var(1579, 790);var(1581, 790);var(1584, 790);var(1588, 790);var(1591, 791);var(1593, 791);var(1599, 792);var(1601, 792);var(1603, 793);var(1604, 793);var(1605, 794);var(1607, 794);var(1610, 795);var(1611, 795);var(1614, 795);var(1617, 797);var(1618, 797);var(1619, 797);var(1619, 797);var(1621, 797);var(1623, 797);var(1625, 798);var(1627, 798);var(1629, 797);var(1633, 797);var(1635, 797);var(1635, 797);var(1637, 801);var(1639, 810);var(1642, 822);var(1639, 828);var(1627, 833);var(1608, 832);var(1599, 825);var(1595, 818);var(1589, 808);var(1583, 799);var(1582, 798);var(1579, 793);var(1579, 791);

    end
        fan
        var(1608, 818);var(1579, 790);var(1581, 790);var(1584, 790);var(1588, 790);var(1591, 791);var(1593, 791);var(1599, 792);var(1601, 792);var(1603, 793);var(1604, 793);var(1605, 794);var(1607, 794);var(1610, 795);var(1611, 795);var(1614, 795);var(1617, 797);var(1618, 797);var(1619, 797);var(1619, 797);var(1621, 797);var(1623, 797);var(1625, 798);var(1627, 798);var(1629, 797);var(1633, 797);var(1635, 797);var(1635, 797);var(1637, 801);var(1639, 810);var(1642, 822);var(1639, 828);var(1627, 833);var(1608, 832);var(1599, 825);var(1595, 818);var(1589, 808);var(1583, 799);var(1582, 798);var(1579, 793);var(1579, 791);var(1672, 798);var(1635, 796);var(1637, 796);var(1640, 796);var(1644, 796);var(1646, 794);var(1648, 792);var(1651, 792);var(1654, 790);var(1655, 789);var(1658, 788);var(1661, 786);var(1662, 786);var(1664, 784);var(1667, 782);var(1668, 782);var(1671, 782);var(1671, 782);var(1671, 780);var(1672, 781);var(1674, 781);var(1675, 781);var(1677, 781);var(1678, 781);var(1681, 780);var(1683, 780);var(1683, 780);var(1686, 782);var(1689, 783);var(1689, 783);var(1691, 784);var(1693, 786);var(1694, 786);var(1695, 788);var(1696, 790);var(1696, 793);var(1696, 796);var(1696, 797);var(1696, 799);var(1695, 802);var(1695, 803);var(1691, 805);var(1685, 807);var(1677, 809);var(1670, 810);var(1662, 812);var(1647, 813);var(1643, 814);var(1641, 814);var(1640, 813);var(1639, 810);var(1636, 806);var(1636, 804);var(1638, 801);var(1640, 797);var(1643, 797);var(1634, 800);var(1637, 796);
    end

        //white
        cWHITE
        fan
        var(1620, 826);var(1591, 808);var(1596, 810);var(1601, 810);var(1606, 812);var(1610, 814);var(1614, 814);var(1616, 814);var(1619, 816);var(1622, 816);var(1624, 816);var(1626, 816);var(1628, 817);var(1629, 817);var(1631, 817);var(1633, 817);var(1635, 816);var(1636, 816);var(1637, 816);var(1640, 815);var(1641, 815);var(1642, 815);var(1644, 822);var(1648, 829);var(1649, 833);var(1645, 835);var(1640, 839);var(1634, 841);var(1624, 844);var(1616, 844);var(1609, 843);var(1608, 843);var(1600, 840);var(1596, 833);var(1594, 821);var(1593, 815);var(1593, 812);
    end
        fan
        var(1653, 819);var(1638, 814);var(1640, 814);var(1641, 814);var(1644, 814);var(1648, 812);var(1651, 812);var(1653, 810);var(1655, 809);var(1657, 808);var(1659, 808);var(1663, 806);var(1665, 806);var(1666, 804);var(1668, 804);var(1668, 805);var(1669, 810);var(1670, 814);var(1671, 818);var(1671, 819);var(1672, 824);var(1670, 827);var(1663, 831);var(1660, 833);var(1657, 833);var(1653, 833);var(1647, 833);var(1640, 833);var(1635, 833);var(1634, 831);var(1634, 826);var(1634, 820);var(1637, 818);var(1639, 816);

    end
        fan
        var(1679, 812);var(1654, 808);var(1657, 808);var(1658, 806);var(1662, 805);var(1665, 805);var(1667, 803);var(1670, 802);var(1673, 802);var(1677, 802);var(1680, 801);var(1684, 801);var(1688, 802);var(1690, 802);var(1692, 802);var(1694, 802);var(1695, 804);var(1691, 826);var(1679, 831);var(1658, 832);var(1654, 831);var(1654, 816);var(1654, 809);
    end

        //GREEN
        cFLAGGREEN
        fan
        var(1599, 844);var(1578, 847);var(1587, 834);var(1600, 832);var(1603, 833);var(1606, 834);var(1609, 835);var(1613, 837);var(1617, 838);var(1621, 839);var(1624, 839);var(1627, 839);var(1628, 842);var(1629, 852);var(1630, 858);var(1625, 861);var(1620, 860);var(1617, 859);var(1613, 858);var(1610, 857);var(1606, 854);var(1607, 856);var(1604, 855);var(1599, 853);var(1592, 852);var(1591, 852);var(1586, 850);var(1583, 849);var(1581, 849);var(1579, 848);
    end
        fan
        var(1690, 836);var(1671, 841);var(1664, 843);var(1659, 845);var(1655, 848);var(1651, 850);var(1645, 853);var(1640, 856);var(1635, 859);var(1631, 860);var(1628, 860);var(1626, 852);var(1627, 843);var(1630, 839);
    end
        fan
        var(1682, 834);var(1671, 841);var(1678, 843);var(1682, 844);var(1685, 847);var(1689, 849);var(1690, 843);var(1690, 834);var(1690, 828);var(1690, 828);var(1685, 825);var(1682, 825);var(1679, 825);var(1676, 825);var(1673, 825);var(1669, 825);var(1666, 826);var(1661, 827);var(1660, 831);var(1659, 833);var(1659, 839);var(1664, 842);var(1665, 843);
    end
        fan
        var(1682, 834);var(1671, 841);var(1678, 843);var(1682, 844);var(1685, 847);var(1689, 849);var(1690, 843);var(1690, 834);var(1690, 828);var(1690, 828);var(1685, 825);var(1682, 825);var(1679, 825);var(1676, 825);var(1673, 825);var(1669, 825);var(1666, 826);var(1661, 827);var(1660, 831);var(1659, 833);var(1659, 839);var(1664, 842);var(1665, 843);
    end
        fan
        var(1652, 839);var(1636, 839);var(1642, 837);var(1651, 835);var(1655, 833);var(1658, 830);var(1660, 829);var(1662, 829);var(1669, 828);var(1672, 827);var(1676, 830);var(1677, 837);var(1677, 837);var(1677, 837);var(1673, 839);var(1667, 840);var(1662, 842);var(1653, 846);var(1646, 850);var(1643, 851);var(1639, 854);var(1633, 856);var(1630, 858);var(1624, 858);var(1620, 856);var(1613, 852);var(1607, 848);var(1607, 848);var(1610, 845);var(1617, 843);var(1623, 842);var(1630, 841);var(1640, 839);var(1649, 835);var(1658, 832);var(1662, 832);
    end


        //red
        cFLAGRED
        triangle
        var(1579, 789);var(1608, 825);var(1577, 847);
    end

        //outline
        cBLACK
        strip
        var(1577, 849);var(1579, 789);var(1583, 789);var(1586, 789);var(1589, 789);var(1593, 791);var(1592, 791);var(1595, 791);var(1598, 791);var(1601, 792);var(1603, 793);var(1604, 793);var(1607, 794);var(1608, 794);var(1611, 795);var(1613, 796);var(1615, 796);var(1618, 796);var(1620, 796);var(1623, 796);var(1625, 796);var(1629, 796);var(1630, 797);var(1632, 797);var(1635, 797);var(1637, 797);var(1640, 797);var(1642, 795);var(1645, 795);var(1647, 794);var(1650, 794);var(1652, 792);var(1655, 790);var(1657, 789);var(1659, 788);var(1662, 786);var(1665, 785);var(1668, 783);var(1670, 782);var(1672, 781);var(1674, 781);var(1678, 780);var(1679, 780);var(1684, 781);var(1685, 781);var(1688, 782);var(1691, 784);var(1693, 786);var(1695, 787);var(1697, 787);var(1697, 789);var(1698, 794);var(1697, 797);var(1697, 800);var(1697, 802);var(1697, 804);var(1697, 804);var(1697, 806);var(1697, 806);var(1697, 810);var(1697, 810);var(1697, 812);var(1695, 816);var(1695, 817);var(1695, 819);var(1694, 821);var(1693, 821);var(1693, 823);var(1693, 824);var(1692, 826);var(1692, 827);var(1692, 828);var(1692, 830);var(1692, 831);var(1691, 833);var(1691, 835);var(1691, 836);var(1691, 839);var(1691, 841);var(1690, 844);var(1690, 844);var(1691, 846);var(1691, 848);var(1691, 848);var(1689, 846);var(1689, 846);var(1686, 845);var(1685, 843);var(1684, 843);var(1684, 843);var(1682, 843);var(1680, 842);var(1678, 842);var(1678, 842);var(1676, 841);var(1675, 841);var(1672, 842);var(1670, 843);var(1666, 844);var(1663, 845);var(1660, 846);var(1657, 848);var(1655, 849);var(1652, 851);var(1649, 853);var(1647, 854);var(1645, 855);var(1643, 856);var(1641, 857);var(1638, 858);var(1637, 859);var(1635, 859);var(1634, 859);var(1633, 860);var(1631, 860);var(1629, 860);var(1627, 860);var(1627, 860);var(1625, 861);var(1623, 861);var(1621, 861);var(1620, 861);var(1619, 861);var(1616, 861);var(1614, 860);var(1613, 860);var(1612, 859);var(1610, 859);var(1608, 858);var(1608, 858);var(1607, 858);var(1605, 858);var(1605, 858);var(1603, 856);var(1602, 855);var(1601, 854);var(1600, 854);var(1598, 853);var(1597, 852);var(1597, 852);var(1596, 851);var(1595, 850);var(1593, 850);var(1592, 850);var(1590, 850);var(1587, 848);var(1585, 848);var(1584, 848);var(1582, 848);var(1580, 848);var(1580, 849);var(1578, 849);
    end
}

void blackStone()
{
    cGRAY
        fan
        var(186, 1188);var(202, 1185);var(220, 1179);var(235, 1179);var(250, 1179);var(262, 1179);var(280, 1178);var(294, 1178);var(303, 1170);var(321, 1161);var(339, 1161);var(349, 1161);var(358, 1161);var(273, 1191);var(136, 1257);var(147, 1236);var(153, 1226);var(165, 1202);var(175, 1191);var(189, 1184);var(213, 1166);var(222, 1157);var(244, 1146);var(249, 1142);var(273, 1131);var(274, 1127);var(280, 1124);var(298, 1130);var(315, 1137);var(330, 1142);var(352, 1149);var(361, 1152);var(369, 1155);var(376, 1160);var(382, 1167);var(394, 1191);var(403, 1206);var(415, 1217);var(432, 1247);var(432, 1250);var(438, 1260);var(441, 1283);var(448, 1298);var(448, 1314);var(433, 1322);var(396, 1331);var(312, 1331);var(280, 1331);var(165, 1322);var(144, 1308);var(133, 1284);var(136, 1263);var(144, 1244);var(150, 1227);
    end
        cBLACK
        strip
        var(202, 1185);var(220, 1179);var(235, 1179);var(250, 1179);var(262, 1179);var(280, 1178);var(294, 1178);var(303, 1170);var(321, 1161);var(339, 1161);var(349, 1161);var(358, 1161);var(273, 1191);var(136, 1257);var(147, 1236);var(153, 1226);var(165, 1202);var(175, 1191);var(189, 1184);var(213, 1166);var(222, 1157);var(244, 1146);var(249, 1142);var(273, 1131);var(274, 1127);var(280, 1124);var(298, 1130);var(315, 1137);var(330, 1142);var(352, 1149);var(361, 1152);var(369, 1155);var(376, 1160);var(382, 1167);var(394, 1191);var(403, 1206);var(415, 1217);var(432, 1247);var(432, 1250);var(438, 1260);var(441, 1283);var(448, 1298);var(448, 1314);var(433, 1322);var(396, 1331);var(312, 1331);var(280, 1331);var(165, 1322);var(144, 1308);var(133, 1284);var(136, 1263);var(144, 1244);var(150, 1227);
    end

        cDARKGRAY
        fan
        var(767, 1266);var(764, 1253);var(764, 1236);var(775, 1227);var(785, 1218);var(796, 1214);var(803, 1206);var(823, 1218);var(838, 1227);var(850, 1232);var(856, 1235);var(859, 1238);var(850, 1254);var(818, 1262);var(808, 1263);var(793, 1265);var(779, 1262);var(770, 1256);var(772, 1238);
    end
        cGRAY
        fan
        var(904, 1287);var(883, 1260);var(869, 1248);var(884, 1238);var(893, 1238);var(898, 1238);var(910, 1238);var(940, 1236);var(956, 1236);var(973, 1230);var(994, 1217);var(1006, 1233);var(1018, 1263);var(1021, 1272);var(1021, 1281);var(1000, 1289);var(968, 1299);var(941, 1299);var(937, 1302);var(922, 1296);var(913, 1293);var(905, 1286);var(896, 1272);var(883, 1254);var(944, 1260);
    end
        cBLACK
        strip
        var(904, 1287);var(883, 1260);var(869, 1248);var(884, 1238);var(893, 1238);var(898, 1238);var(910, 1238);var(940, 1236);var(956, 1236);var(973, 1230);var(994, 1217);var(1006, 1233);var(1018, 1263);var(1021, 1272);var(1021, 1281);var(1000, 1289);var(968, 1299);var(941, 1299);var(937, 1302);var(922, 1296);var(913, 1293);var(905, 1286);var(896, 1272);var(883, 1254);
    end

        //outline
        cDARKGRAY
        fan
        var(472, 1301);var(482, 1283);var(494, 1286);var(499, 1290);var(499, 1266);var(499, 1217);var(505, 1217);var(541, 1236);var(548, 1253);var(556, 1277);var(557, 1286);var(562, 1292);var(574, 1280);var(590, 1262);var(595, 1263);var(602, 1287);var(605, 1293);var(608, 1305);var(580, 1311);var(574, 1313);
    end
        fan
        var(1288, 1623);var(1289, 1623);var(1273, 1622);var(1276, 1605);var(1297, 1595);var(1313, 1601);var(1319, 1617);var(1319, 1635);var(1289, 1637);var(1267, 1637);var(1261, 1629);var(1298, 1601);var(1300, 1601);
    end

}
void destroyedBuilding()
{
    blackStone();
    rgb(0.25, 0.31, 0.31);
    fan
        var(64, 933);var(1, 717);var(82, 902);var(111, 951);var(129, 986);var(150, 1017);var(160, 1032);var(109, 1073);var(102, 1070);var(97, 1067);var(88, 1065);var(84, 1065);var(82, 1065);var(78, 1068);var(75, 1070);var(70, 1070);var(70, 1070);var(3, 911);var(1, 905);var(1, 716);
    end
        fan
        var(151, 1080);var(111, 1077);var(112, 1083);var(112, 1091);var(112, 1097);var(111, 1106);var(111, 1115);var(124, 1127);var(126, 1127);var(207, 1100);var(201, 1094);var(199, 1091);var(195, 1083);var(195, 1076);var(192, 1064);var(192, 1059);var(187, 1052);var(183, 1041);var(178, 1038);var(168, 1034);var(162, 1032);var(150, 1029);var(130, 1035);var(106, 1056);var(99, 1067);
    end
        fan
        var(202, 1166);var(123, 1125);var(223, 1298);var(289, 1247);var(208, 1101);var(126, 1127);
    end

        cBLACK
        fan
        var(1, 786);var(12, 795);var(15, 800);var(21, 815);var(24, 824);var(31, 837);var(34, 846);var(39, 851);var(42, 861);var(45, 867);var(48, 881);var(48, 887);var(46, 894);var(34, 987);var(4, 912);var(0, 878);var(0, 788);var(16, 873);
    end
        fan
        var(201, 1218);var(168, 1092);var(204, 1164);var(235, 1226);var(259, 1268);var(213, 1278);var(180, 1221);var(154, 1176);var(184, 1190);var(169, 1095);
    end


        cBLACK
        strip
        var(1, 714);var(84, 902);var(114, 951);var(132, 986);var(153, 1019);var(156, 1026);var(159, 1028);var(165, 1029);var(169, 1029);var(172, 1034);var(177, 1037);var(178, 1037);var(183, 1040);var(183, 1049);var(184, 1053);var(189, 1059);var(193, 1070);var(195, 1079);var(202, 1086);var(208, 1095);var(213, 1100);var(225, 1134);var(291, 1247);var(223, 1302);var(124, 1130);var(120, 1125);var(114, 1122);var(114, 1122);var(112, 1119);var(111, 1110);var(112, 1101);var(112, 1095);var(112, 1091);var(112, 1089);var(112, 1086);var(109, 1083);var(109, 1080);var(106, 1079);var(100, 1074);var(99, 1073);var(97, 1073);var(91, 1073);var(87, 1073);var(81, 1073);var(76, 1073);var(73, 1074);var(73, 1073);var(1, 911);
    end
        strip
        var(48, 890);var(94, 965);var(94, 965);var(94, 971);var(94, 972);var(94, 972);var(93, 974);var(93, 983);var(97, 987);var(100, 993);var(106, 993);var(112, 993);var(114, 993);var(115, 992);var(171, 1095);var(235, 1227);
    end

        //destructions
        cBLACK
        fan
        var(709, 1100);var(679, 1092);var(674, 1092);var(698, 1086);var(715, 1079);var(715, 1079);var(719, 1067);var(746, 1071);var(749, 1059);var(764, 1047);var(818, 1050);var(821, 1056);var(832, 1071);var(863, 1059);var(865, 1080);var(865, 1098);var(878, 1122);var(850, 1131);var(859, 1200);var(847, 1218);var(811, 1230);var(740, 1226);var(724, 1235);var(709, 1227);var(697, 1209);var(694, 1164);var(682, 1161);var(688, 1148);
    end

}

void drawBuildings()
{
    FarBuilding();
    Building2();
    Building1();
    Building3();
    Building4();
    Building5();
    Building6();
    Building8();
    Building7();
    Building9();
    Flag();
    destroyedBuilding();
}

void drawStones()
{
    //back
    cBLACK
        fan
        var(1743, 1600);var(1742, 1654);var(1732, 1634);var(1728, 1600);var(1725, 1578);var(1720, 1552);var(1714, 1548);var(1713, 1542);var(1730, 1539);var(1750, 1539);var(1779, 1543);var(1782, 1555);var(1785, 1576);var(1790, 1595);var(1792, 1610);var(1791, 1628);var(1789, 1644);var(1792, 1658);var(1799, 1663);var(1815, 1666);var(1828, 1672);var(1830, 1674);var(1831, 1681);var(1831, 1681);var(1831, 1681);var(1821, 1684);var(1813, 1684);var(1800, 1683);var(1787, 1679);var(1776, 1678);var(1772, 1679);var(1756, 1684);var(1749, 1685);var(1731, 1690);var(1724, 1694);var(1756, 1686);var(1743, 1695);var(1735, 1701);var(1729, 1704);var(1719, 1704);var(1709, 1705);var(1703, 1705);var(1701, 1697);var(1705, 1678);var(1711, 1660);var(1719, 1629);var(1721, 1610);var(1721, 1579);var(1721, 1553);var(1709, 1542);var(1728, 1544);var(1750, 1570);var(1763, 1603);
    end
        // car 1 shadow
        cBLACK
        fan
        var(1911, 1316);var(1782, 1327);var(1795, 1319);var(1837, 1305);var(1856, 1292);var(1881, 1284);var(1926, 1279);var(1933, 1279);var(1960, 1277);var(1992, 1282);var(2001, 1286);var(2001, 1307);var(1997, 1334);var(1958, 1357);var(1893, 1364);var(1858, 1367);var(1841, 1367);var(1810, 1359);var(1795, 1352);var(1786, 1344);var(1781, 1337);var(1785, 1325);var(1798, 1316);
    end


        //from the left side

        cGRAY
        polygon
        var(1, 1771);var(141, 1711);var(389, 1651);var(480, 1812);var(1, 1822);
    end
        cBLACK
        strip
        var(1, 1770);var(141, 1711);var(389, 1651);var(480, 1812);var(1, 1822);
    end
        cGRAY
        fan
        var(309, 1729);var(171, 1788);var(171, 1781);var(171, 1778);var(167, 1774);var(163, 1769);var(163, 1764);var(163, 1761);var(164, 1759);var(167, 1756);var(168, 1756);var(173, 1751);var(174, 1750);var(182, 1745);var(188, 1741);var(196, 1736);var(207, 1731);var(221, 1726);var(232, 1719);var(239, 1714);var(254, 1706);var(267, 1699);var(277, 1689);var(286, 1683);var(297, 1676);var(308, 1669);var(314, 1669);var(318, 1666);var(343, 1661);var(353, 1656);var(361, 1653);var(371, 1648);var(379, 1641);var(387, 1640);var(398, 1636);var(406, 1634);var(411, 1633);var(413, 1638);var(413, 1646);var(413, 1651);var(413, 1658);var(413, 1663);var(417, 1665);var(418, 1668);var(423, 1671);var(427, 1674);var(434, 1678);var(438, 1678);var(446, 1683);var(448, 1694);var(442, 1700);var(433, 1715);var(421, 1728);var(411, 1736);var(398, 1746);var(393, 1749);var(386, 1758);var(386, 1761);var(377, 1770);var(374, 1775);var(367, 1783);var(359, 1790);var(338, 1795);var(329, 1795);var(317, 1791);var(302, 1785);var(286, 1784);var(271, 1789);var(249, 1794);var(229, 1798);var(219, 1798);var(203, 1796);var(188, 1794);var(177, 1793);var(174, 1791);
    end
        cBLACK
        strip
        var(171, 1788);var(171, 1781);var(171, 1778);var(167, 1774);var(163, 1769);var(163, 1764);var(163, 1761);var(164, 1759);var(167, 1756);var(168, 1756);var(173, 1751);var(174, 1750);var(182, 1745);var(188, 1741);var(196, 1736);var(207, 1731);var(221, 1726);var(232, 1719);var(239, 1714);var(254, 1706);var(267, 1699);var(277, 1689);var(286, 1683);var(297, 1676);var(308, 1669);var(314, 1669);var(318, 1666);var(343, 1661);var(353, 1656);var(361, 1653);var(371, 1648);var(379, 1641);var(387, 1640);var(398, 1636);var(406, 1634);var(411, 1633);var(413, 1638);var(413, 1646);var(413, 1651);var(413, 1658);var(413, 1663);var(417, 1665);var(418, 1668);var(423, 1671);var(427, 1674);var(434, 1678);var(438, 1678);var(446, 1683);var(448, 1694);var(442, 1700);var(433, 1715);var(421, 1728);var(411, 1736);var(398, 1746);var(393, 1749);var(386, 1758);var(386, 1761);var(377, 1770);var(374, 1775);var(367, 1783);var(359, 1790);var(338, 1795);var(329, 1795);var(317, 1791);var(302, 1785);var(286, 1784);var(271, 1789);var(249, 1794);var(229, 1798);var(219, 1798);var(203, 1796);var(188, 1794);var(177, 1793);var(174, 1791);
    end

        cGRAY
        fan
        var(507, 1758);var(463, 1802);var(448, 1793);var(430, 1788);var(424, 1787);var(414, 1779);var(408, 1775);var(415, 1767);var(421, 1754);var(435, 1743);var(445, 1736);var(456, 1725);var(460, 1727);var(463, 1728);var(468, 1730);var(472, 1725);var(474, 1716);var(478, 1710);var(487, 1700);var(493, 1691);var(501, 1685);var(504, 1680);var(516, 1656);var(519, 1647);var(543, 1638);var(561, 1649);var(573, 1655);var(603, 1658);var(618, 1664);var(636, 1679);var(646, 1685);var(672, 1695);var(675, 1695);var(681, 1706);var(681, 1710);var(676, 1724);var(676, 1745);var(685, 1763);var(688, 1770);var(684, 1781);var(673, 1781);var(646, 1788);var(631, 1796);var(603, 1803);var(528, 1805);var(489, 1805);var(459, 1808);var(462, 1794);
    end
        cBLACK
        strip
        var(463, 1802);var(448, 1793);var(430, 1788);var(424, 1787);var(414, 1779);var(408, 1775);var(415, 1767);var(421, 1754);var(435, 1743);var(445, 1736);var(456, 1725);var(460, 1727);var(463, 1728);var(468, 1730);var(472, 1725);var(474, 1716);var(478, 1710);var(487, 1700);var(493, 1691);var(501, 1685);var(504, 1680);var(516, 1656);var(519, 1647);var(543, 1638);var(561, 1649);var(573, 1655);var(603, 1658);var(618, 1664);var(636, 1679);var(646, 1685);var(672, 1695);var(675, 1695);var(681, 1706);var(681, 1710);var(676, 1724);var(676, 1745);var(685, 1763);var(688, 1770);var(684, 1781);var(673, 1781);var(646, 1788);var(631, 1796);var(603, 1803);var(528, 1805);var(489, 1805);var(459, 1808);var(462, 1794);
    end
        strip
        var(673, 1700);var(660, 1712);var(646, 1716);var(634, 1721);var(621, 1731);var(613, 1737);var(594, 1754);var(592, 1758);var(582, 1761);var(577, 1766);var(567, 1778);var(567, 1778);var(564, 1778);var(555, 1785);var(547, 1790);var(544, 1794);var(537, 1797);var(529, 1800);
    end

        cGRAY
        fan
        var(934, 1761);var(856, 1752);var(868, 1748);var(879, 1736);var(891, 1727);var(906, 1718);var(918, 1715);var(927, 1718);var(942, 1716);var(969, 1713);var(976, 1712);var(984, 1706);var(997, 1703);var(1008, 1701);var(1020, 1698);var(1014, 1713);var(1011, 1719);var(1014, 1725);var(1023, 1742);var(1020, 1763);var(1018, 1779);var(1018, 1791);var(1003, 1793);var(973, 1796);var(945, 1796);var(919, 1796);var(900, 1797);var(873, 1797);var(870, 1797);var(856, 1793);var(849, 1788);var(847, 1785);var(846, 1775);var(852, 1767);var(856, 1761);var(856, 1754);var(856, 1748);
    end
        cBLACK
        strip
        var(856, 1752);var(868, 1748);var(879, 1736);var(891, 1727);var(906, 1718);var(918, 1715);var(927, 1718);var(942, 1716);var(969, 1713);var(976, 1712);var(984, 1706);var(997, 1703);var(1008, 1701);var(1020, 1698);var(1014, 1713);var(1011, 1719);var(1014, 1725);var(1023, 1742);var(1020, 1763);var(1018, 1779);var(1018, 1791);var(1003, 1793);var(973, 1796);var(945, 1796);var(919, 1796);var(900, 1797);var(873, 1797);var(870, 1797);var(856, 1793);var(849, 1788);var(847, 1785);var(846, 1775);var(852, 1767);var(856, 1761);var(856, 1754);var(856, 1748);
    end
        strip
        var(1011, 1730);var(1000, 1730);var(994, 1730);var(987, 1733);var(981, 1733);var(969, 1736);var(961, 1740);var(946, 1740);var(945, 1740);var(928, 1745);var(922, 1745);var(916, 1745);var(906, 1745);var(900, 1745);var(898, 1745);var(888, 1740);var(880, 1739);
    end

        cGRAY
        fan
        var(1030, 1763);var(975, 1757);var(985, 1748);var(991, 1737);var(1005, 1730);var(1017, 1727);var(1024, 1730);var(1042, 1746);var(1042, 1746);var(1057, 1758);var(1071, 1769);var(1078, 1770);var(1087, 1773);var(1104, 1773);var(1107, 1775);var(1110, 1775);var(1110, 1787);var(1110, 1794);var(1107, 1794);var(1084, 1794);var(1066, 1794);var(1044, 1794);var(1035, 1794);var(1006, 1794);var(991, 1791);var(982, 1791);var(976, 1791);var(972, 1788);var(975, 1772);var(981, 1754);
    end
        cBLACK
        strip
        var(975, 1757);var(985, 1748);var(991, 1737);var(1005, 1730);var(1017, 1727);var(1024, 1730);var(1042, 1746);var(1042, 1746);var(1057, 1758);var(1071, 1769);var(1078, 1770);var(1087, 1773);var(1104, 1773);var(1107, 1775);var(1110, 1775);var(1110, 1787);var(1110, 1794);var(1107, 1794);var(1084, 1794);var(1066, 1794);var(1044, 1794);var(1035, 1794);var(1006, 1794);var(991, 1791);var(982, 1791);var(976, 1791);var(972, 1788);var(975, 1772);var(981, 1754);
    end
        fan
        var(990, 1773);var(988, 1737);var(979, 1742);var(976, 1749);var(978, 1754);var(975, 1773);var(975, 1788);var(978, 1794);var(990, 1793);var(994, 1793);var(1002, 1793);var(1006, 1793);var(1002, 1790);var(990, 1773);var(988, 1764);var(993, 1755);var(994, 1752);var(996, 1746);
    end
        strip
        var(1041, 1748);var(1059, 1767);var(1066, 1772);var(1080, 1775);var(1092, 1776);
    end

        cGRAY
        fan
        var(1144, 1776);var(1113, 1796);var(1111, 1781);var(1111, 1770);var(1111, 1757);var(1116, 1748);var(1117, 1736);var(1120, 1716);var(1120, 1716);var(1129, 1730);var(1132, 1730);var(1140, 1725);var(1141, 1724);var(1147, 1721);var(1147, 1721);var(1152, 1743);var(1156, 1746);var(1162, 1755);var(1173, 1760);var(1182, 1757);var(1188, 1746);var(1192, 1746);var(1201, 1769);var(1207, 1778);var(1215, 1794);var(1218, 1799);var(1216, 1805);var(1197, 1806);var(1171, 1802);var(1149, 1796);var(1129, 1796);var(1116, 1796);var(1104, 1796);
    end
        cBLACK
        strip
        var(1113, 1796);var(1111, 1781);var(1111, 1770);var(1111, 1757);var(1116, 1748);var(1117, 1736);var(1120, 1716);var(1120, 1716);var(1129, 1730);var(1132, 1730);var(1140, 1725);var(1141, 1724);var(1147, 1721);var(1147, 1721);var(1152, 1743);var(1156, 1746);var(1162, 1755);var(1173, 1760);var(1182, 1757);var(1188, 1746);var(1192, 1746);var(1201, 1769);var(1207, 1778);var(1215, 1794);var(1218, 1799);var(1216, 1805);var(1197, 1806);var(1171, 1802);var(1149, 1796);var(1129, 1796);var(1116, 1796);var(1104, 1796);
    end


        cGRAY
        fan
        var(1408, 1514);var(1371, 1500);var(1381, 1487);var(1393, 1487);var(1402, 1479);var(1411, 1478);var(1417, 1478);var(1425, 1478);var(1440, 1482);var(1450, 1484);var(1456, 1485);var(1470, 1490);var(1482, 1490);var(1488, 1491);var(1504, 1497);var(1509, 1497);var(1497, 1503);var(1480, 1508);var(1468, 1511);var(1456, 1514);var(1446, 1520);var(1437, 1526);var(1420, 1536);var(1411, 1539);var(1404, 1541);var(1387, 1548);var(1386, 1550);var(1377, 1553);var(1374, 1553);var(1363, 1556);var(1353, 1559);var(1348, 1559);var(1341, 1559);var(1339, 1559);var(1321, 1566);var(1318, 1566);var(1315, 1566);var(1312, 1560);var(1308, 1551);var(1308, 1548);var(1314, 1539);var(1320, 1532);var(1326, 1526);var(1333, 1518);var(1342, 1512);var(1350, 1508);var(1360, 1503);var(1369, 1497);var(1375, 1497);
    end
        cBLACK
        strip
        var(1371, 1500);var(1381, 1487);var(1393, 1487);var(1402, 1479);var(1411, 1478);var(1417, 1478);var(1425, 1478);var(1440, 1482);var(1450, 1484);var(1456, 1485);var(1470, 1490);var(1482, 1490);var(1488, 1491);var(1504, 1497);var(1509, 1497);var(1497, 1503);var(1480, 1508);var(1468, 1511);var(1456, 1514);var(1446, 1520);var(1437, 1526);var(1420, 1536);var(1411, 1539);var(1404, 1541);var(1387, 1548);var(1386, 1550);var(1377, 1553);var(1374, 1553);var(1363, 1556);var(1353, 1559);var(1348, 1559);var(1341, 1559);var(1339, 1559);var(1321, 1566);var(1318, 1566);var(1315, 1566);var(1312, 1560);var(1308, 1551);var(1308, 1548);var(1314, 1539);var(1320, 1532);var(1326, 1526);var(1333, 1518);var(1342, 1512);var(1350, 1508);var(1360, 1503);var(1369, 1497);var(1375, 1497);
    end


        cGRAY
        fan
        var(1716, 1476);var(1494, 1494);var(1504, 1484);var(1516, 1473);var(1531, 1460);var(1537, 1445);var(1546, 1434);var(1552, 1427);var(1560, 1425);var(1566, 1424);var(1569, 1419);var(1573, 1407);var(1575, 1394);var(1579, 1388);var(1587, 1373);var(1597, 1365);var(1602, 1364);var(1620, 1355);var(1621, 1353);var(1630, 1338);var(1635, 1334);var(1654, 1329);var(1671, 1329);var(1683, 1328);var(1704, 1328);var(1713, 1328);var(1720, 1326);var(1723, 1323);var(1741, 1322);var(1744, 1322);var(1753, 1322);var(1783, 1320);var(1789, 1320);var(1806, 1322);var(1827, 1326);var(1848, 1326);var(1869, 1326);var(1878, 1323);var(1894, 1322);var(1900, 1322);var(1902, 1332);var(1902, 1338);var(1899, 1361);var(1899, 1376);var(1899, 1394);var(1897, 1407);var(1893, 1424);var(1888, 1436);var(1882, 1446);var(1881, 1454);var(1875, 1466);var(1866, 1473);var(1866, 1485);var(1860, 1499);var(1854, 1515);var(1848, 1524);var(1839, 1550);var(1839, 1550);var(1837, 1563);var(1837, 1563);var(1837, 1563);var(1833, 1569);var(1825, 1578);var(1810, 1578);var(1785, 1583);var(1768, 1583);var(1743, 1583);var(1686, 1583);var(1651, 1583);var(1605, 1583);var(1600, 1583);var(1560, 1583);var(1552, 1596);var(1540, 1605);var(1540, 1607);var(1521, 1619);var(1491, 1625);var(1489, 1625);var(1480, 1617);var(1464, 1605);var(1455, 1593);var(1449, 1584);var(1452, 1577);var(1464, 1565);var(1470, 1559);var(1479, 1544);var(1488, 1532);var(1494, 1514);var(1494, 1509);var(1503, 1496);
    end

        cBLACK
        strip
        var(1494, 1494);var(1504, 1484);var(1516, 1473);var(1531, 1460);var(1537, 1445);var(1546, 1434);var(1552, 1427);var(1560, 1425);var(1566, 1424);var(1569, 1419);var(1573, 1407);var(1575, 1394);var(1579, 1388);var(1587, 1373);var(1597, 1365);var(1602, 1364);var(1620, 1355);var(1621, 1353);var(1630, 1338);var(1635, 1334);var(1654, 1329);var(1671, 1329);var(1683, 1328);var(1704, 1328);var(1713, 1328);var(1720, 1326);var(1723, 1323);var(1741, 1322);var(1744, 1322);var(1753, 1322);var(1783, 1320);var(1789, 1320);var(1806, 1322);var(1827, 1326);var(1848, 1326);var(1869, 1326);var(1878, 1323);var(1894, 1322);var(1900, 1322);var(1902, 1332);var(1902, 1338);var(1899, 1361);var(1899, 1376);var(1899, 1394);var(1897, 1407);var(1893, 1424);var(1888, 1436);var(1882, 1446);var(1881, 1454);var(1875, 1466);var(1866, 1473);var(1866, 1485);var(1860, 1499);var(1854, 1515);var(1848, 1524);var(1839, 1550);var(1839, 1550);var(1837, 1563);var(1837, 1563);var(1837, 1563);var(1833, 1569);var(1825, 1578);var(1810, 1578);var(1785, 1583);var(1768, 1583);var(1743, 1583);var(1686, 1583);var(1651, 1583);var(1605, 1583);var(1600, 1583);var(1560, 1583);var(1552, 1596);var(1540, 1605);var(1540, 1607);var(1521, 1619);var(1491, 1625);var(1489, 1625);var(1480, 1617);var(1464, 1605);var(1455, 1593);var(1449, 1584);var(1452, 1577);var(1464, 1565);var(1470, 1559);var(1479, 1544);var(1488, 1532);var(1494, 1514);var(1494, 1509);var(1503, 1496);
    end
        fan
        var(1560, 1584);var(1506, 1622);var(1515, 1608);var(1518, 1602);var(1525, 1593);var(1527, 1583);var(1527, 1569);var(1527, 1553);var(1531, 1532);var(1542, 1512);var(1542, 1523);var(1534, 1536);var(1542, 1548);var(1546, 1562);var(1558, 1562);var(1566, 1562);var(1576, 1554);var(1591, 1545);var(1608, 1536);var(1615, 1535);var(1624, 1538);var(1636, 1545);var(1636, 1554);var(1642, 1563);var(1639, 1572);var(1621, 1583);var(1609, 1586);var(1588, 1595);var(1570, 1599);var(1549, 1610);var(1539, 1620);var(1518, 1631);var(1512, 1631);var(1506, 1626);var(1506, 1620);var(1510, 1616);var(1522, 1610);
    end
        fan
        var(1726, 1544);var(1581, 1553);var(1594, 1541);var(1608, 1527);var(1618, 1514);var(1630, 1511);var(1644, 1496);var(1653, 1485);var(1653, 1485);var(1669, 1496);var(1671, 1496);var(1687, 1502);var(1696, 1503);var(1713, 1505);var(1722, 1503);var(1728, 1503);var(1735, 1511);var(1735, 1520);var(1740, 1520);var(1752, 1514);var(1759, 1503);var(1773, 1518);var(1776, 1524);var(1777, 1524);var(1798, 1520);var(1807, 1511);var(1813, 1506);var(1828, 1488);var(1843, 1482);var(1863, 1482);var(1860, 1505);var(1848, 1541);var(1839, 1557);var(1831, 1580);var(1815, 1580);var(1783, 1584);var(1762, 1604);var(1735, 1608);var(1710, 1607);var(1686, 1596);var(1657, 1596);var(1644, 1598);var(1633, 1592);var(1626, 1589);var(1608, 1575);var(1602, 1566);var(1600, 1551);var(1600, 1536);var(1603, 1523);var(1615, 1515);var(1627, 1503);
    end


        cGRAY
        fan
        var(1681, 1619);var(1597, 1566);var(1609, 1565);var(1617, 1562);var(1623, 1560);var(1638, 1553);var(1645, 1548);var(1651, 1544);var(1660, 1539);var(1666, 1544);var(1671, 1548);var(1675, 1551);var(1684, 1557);var(1690, 1557);var(1699, 1551);var(1716, 1545);var(1720, 1541);var(1729, 1560);var(1737, 1593);var(1740, 1623);var(1747, 1640);var(1756, 1655);var(1761, 1668);var(1758, 1683);var(1746, 1697);var(1732, 1706);var(1719, 1713);var(1699, 1719);var(1681, 1719);var(1671, 1713);var(1663, 1707);var(1660, 1700);var(1653, 1689);var(1650, 1682);var(1645, 1676);var(1639, 1664);var(1639, 1664);var(1627, 1670);var(1626, 1670);var(1618, 1673);var(1605, 1665);var(1599, 1659);var(1591, 1650);var(1590, 1647);var(1587, 1637);var(1588, 1631);var(1593, 1619);var(1591, 1601);var(1594, 1590);var(1603, 1575);var(1602, 1562);
    end
        cBLACK
        strip
        var(1597, 1566);var(1609, 1565);var(1617, 1562);var(1623, 1560);var(1638, 1553);var(1645, 1548);var(1651, 1544);var(1660, 1539);var(1666, 1544);var(1671, 1548);var(1675, 1551);var(1684, 1557);var(1690, 1557);var(1699, 1551);var(1716, 1545);var(1720, 1541);var(1729, 1560);var(1737, 1593);var(1740, 1623);var(1747, 1640);var(1756, 1655);var(1761, 1668);var(1758, 1683);var(1746, 1697);var(1732, 1706);var(1719, 1713);var(1699, 1719);var(1681, 1719);var(1671, 1713);var(1663, 1707);var(1660, 1700);var(1653, 1689);var(1650, 1682);var(1645, 1676);var(1639, 1664);var(1639, 1664);var(1627, 1670);var(1626, 1670);var(1618, 1673);var(1605, 1665);var(1599, 1659);var(1591, 1650);var(1590, 1647);var(1587, 1637);var(1588, 1631);var(1593, 1619);var(1591, 1601);var(1594, 1590);var(1603, 1575);var(1602, 1562);
    end
        strip
        var(1603, 1580);var(1620, 1598);var(1626, 1608);var(1638, 1622);var(1645, 1622);var(1659, 1638);var(1671, 1643);var(1672, 1646);var(1681, 1647);var(1684, 1649);var(1689, 1649);var(1690, 1650);var(1704, 1653);var(1711, 1653);var(1716, 1653);var(1723, 1652);var(1728, 1652);var(1741, 1652);var(1747, 1650);var(1749, 1646);
    end

        cGRAY
        fan
        var(1807, 1632);var(1759, 1631);var(1756, 1614);var(1755, 1596);var(1750, 1590);var(1755, 1587);var(1765, 1581);var(1785, 1577);var(1791, 1577);var(1801, 1577);var(1809, 1571);var(1815, 1565);var(1816, 1565);var(1822, 1565);var(1836, 1584);var(1848, 1587);var(1857, 1598);var(1860, 1614);var(1870, 1641);var(1870, 1673);var(1839, 1679);var(1822, 1685);var(1800, 1685);var(1785, 1680);var(1771, 1673);var(1768, 1667);var(1762, 1653);var(1758, 1637);var(1755, 1631);
    end
        cBLACK
        strip
        var(1759, 1631);var(1756, 1614);var(1755, 1596);var(1750, 1590);var(1755, 1587);var(1765, 1581);var(1785, 1577);var(1791, 1577);var(1801, 1577);var(1809, 1571);var(1815, 1565);var(1816, 1565);var(1822, 1565);var(1836, 1584);var(1848, 1587);var(1857, 1598);var(1860, 1614);var(1870, 1641);var(1870, 1673);var(1839, 1679);var(1822, 1685);var(1800, 1685);var(1785, 1680);var(1771, 1673);var(1768, 1667);var(1762, 1653);var(1758, 1637);var(1755, 1631);
    end
        strip
        var(1761, 1634);var(1822, 1605);
    end

        //right stones

}

void upperStones()
{
    cBLACK
        fan
        var(1975, 1665);var(1952, 1640);var(1963, 1622);var(1963, 1616);var(1963, 1602);var(1963, 1586);var(1963, 1580);var(1972, 1547);var(1963, 1518);var(1978, 1503);var(1979, 1496);var(1987, 1487);var(1997, 1482);var(2000, 1493);var(2002, 1745);var(2000, 1803);var(1916, 1787);var(1916, 1749);var(1942, 1700);var(1945, 1676);var(1945, 1652);var(1960, 1635);
    end

        cGRAY
        fan
        var(606, 1271);var(436, 1266);var(471, 1247);var(493, 1229);var(514, 1221);var(546, 1215);var(571, 1202);var(603, 1187);var(642, 1176);var(657, 1176);var(699, 1200);var(714, 1212);var(730, 1226);var(730, 1227);var(741, 1256);var(754, 1280);var(754, 1290);var(754, 1298);var(771, 1319);var(789, 1340);var(802, 1353);var(801, 1353);var(823, 1374);var(832, 1382);var(840, 1398);var(780, 1406);var(751, 1407);var(696, 1421);var(603, 1430);var(549, 1434);var(519, 1436);var(514, 1436);var(510, 1427);var(496, 1377);var(481, 1359);var(459, 1337);var(445, 1295);var(436, 1266);var(405, 1217);var(415, 1203);var(442, 1206);var(468, 1217);var(493, 1218);var(516, 1220);var(523, 1223);var(538, 1215);var(540, 1215);var(556, 1211);
    end
        cBLACK
        strip
        var(436, 1266);var(471, 1247);var(493, 1229);var(514, 1221);var(546, 1215);var(571, 1202);var(603, 1187);var(642, 1176);var(657, 1176);var(699, 1200);var(714, 1212);var(730, 1226);var(730, 1227);var(741, 1256);var(754, 1280);var(754, 1290);var(754, 1298);var(771, 1319);var(789, 1340);var(802, 1353);var(801, 1353);var(823, 1374);var(832, 1382);var(840, 1398);var(780, 1406);var(751, 1407);var(696, 1421);var(603, 1430);var(549, 1434);var(519, 1436);var(514, 1436);var(510, 1427);var(496, 1377);var(481, 1359);var(459, 1337);var(445, 1295);var(436, 1266);var(405, 1217);var(415, 1203);var(442, 1206);var(468, 1217);var(493, 1218);var(516, 1220);var(523, 1223);var(538, 1215);var(540, 1215);var(556, 1211);
    end

        cBLACK
        strip
        var(714, 1350);var(723, 1346);var(726, 1340);var(738, 1332);var(739, 1332);var(751, 1334);var(751, 1334);var(757, 1346);var(760, 1346);var(765, 1346);var(781, 1346);
    end




        cGRAY
        fan
        var(256, 1286);var(159, 1260);var(162, 1247);var(172, 1238);var(183, 1223);var(196, 1218);var(207, 1217);var(226, 1221);var(244, 1224);var(250, 1230);var(258, 1235);var(265, 1238);var(273, 1244);var(276, 1245);var(294, 1245);var(304, 1241);var(310, 1233);var(319, 1227);var(336, 1224);var(355, 1224);var(364, 1224);var(394, 1233);var(402, 1239);var(417, 1256);var(424, 1272);var(438, 1287);var(444, 1302);var(444, 1314);var(444, 1326);var(444, 1344);var(432, 1370);var(415, 1385);var(379, 1392);var(333, 1400);var(304, 1400);var(253, 1391);var(204, 1362);var(186, 1337);var(165, 1310);var(154, 1296);var(151, 1272);var(151, 1257);var(166, 1236);
    end
        cBLACK
        strip
        var(159, 1260);var(162, 1247);var(172, 1238);var(183, 1223);var(196, 1218);var(207, 1217);var(226, 1221);var(244, 1224);var(250, 1230);var(258, 1235);var(265, 1238);var(273, 1244);var(276, 1245);var(294, 1245);var(304, 1241);var(310, 1233);var(319, 1227);var(336, 1224);var(355, 1224);var(364, 1224);var(394, 1233);var(402, 1239);var(417, 1256);var(424, 1272);var(438, 1287);var(444, 1302);var(444, 1314);var(444, 1326);var(444, 1344);var(432, 1370);var(415, 1385);var(379, 1392);var(333, 1400);var(304, 1400);var(253, 1391);var(204, 1362);var(186, 1337);var(165, 1310);var(154, 1296);var(151, 1272);var(151, 1257);var(166, 1236);
    end

        cGRAY
        fan
        var(450, 1365);var(340, 1407);var(354, 1385);var(373, 1364);var(394, 1344);var(408, 1325);var(430, 1304);var(463, 1286);var(478, 1296);var(489, 1311);var(501, 1319);var(511, 1322);var(538, 1335);var(553, 1362);var(568, 1386);var(546, 1412);var(480, 1424);var(453, 1430);var(369, 1430);var(352, 1424);var(336, 1406);var(354, 1389);
    end
        cBLACK
        strip
        var(340, 1407);var(354, 1385);var(373, 1364);var(394, 1344);var(408, 1325);var(430, 1304);var(463, 1286);var(478, 1296);var(489, 1311);var(501, 1319);var(511, 1322);var(538, 1335);var(553, 1362);var(568, 1386);var(546, 1412);var(480, 1424);var(453, 1430);var(369, 1430);var(352, 1424);var(336, 1406);var(354, 1389);
    end

        cGRAY
        fan
        var(552, 1398);var(498, 1410);var(499, 1385);var(504, 1371);var(513, 1350);var(523, 1332);var(541, 1338);var(553, 1350);var(573, 1371);var(594, 1385);var(609, 1401);var(630, 1422);var(613, 1424);var(588, 1422);var(571, 1422);var(553, 1422);var(535, 1422);var(510, 1422);var(499, 1418);var(493, 1412);var(501, 1409);
    end
        cBLACK
        strip
        var(552, 1398);var(498, 1410);var(499, 1385);var(504, 1371);var(513, 1350);var(523, 1332);var(541, 1338);var(553, 1350);var(573, 1371);var(594, 1385);var(609, 1401);var(630, 1422);var(613, 1424);var(588, 1422);var(571, 1422);var(553, 1422);var(535, 1422);var(510, 1422);var(499, 1418);var(493, 1412);var(501, 1409);
    end

        cBLACK
        fan
        var(513, 1364);var(537, 1338);var(525, 1356);var(519, 1374);var(523, 1416);var(505, 1413);var(499, 1410);var(495, 1407);var(499, 1392);var(501, 1379);var(505, 1368);var(514, 1358);var(523, 1346);var(535, 1341);
    end





        fan
        var(157, 1289);var(106, 1292);var(117, 1284);var(126, 1271);var(129, 1250);var(139, 1236);var(153, 1229);var(186, 1250);var(199, 1257);var(208, 1263);var(217, 1277);var(213, 1287);var(208, 1310);var(226, 1332);var(204, 1353);var(159, 1353);var(118, 1349);var(106, 1344);var(111, 1322);var(106, 1295);
    end

        cGRAY
        fan
        var(153, 1349);var(64, 1322);var(156, 1259);var(171, 1268);var(181, 1280);var(190, 1292);var(202, 1293);var(205, 1296);var(208, 1298);var(208, 1301);var(219, 1320);var(226, 1331);var(240, 1346);var(250, 1359);var(261, 1385);var(265, 1406);var(265, 1415);var(247, 1424);var(225, 1430);var(175, 1442);var(165, 1446);var(108, 1448);var(106, 1449);var(66, 1431);var(60, 1397);var(58, 1361);var(58, 1325);var(60, 1323);
    end
        cBLACK
        strip
        var(64, 1322);var(156, 1259);var(171, 1268);var(181, 1280);var(190, 1292);var(202, 1293);var(205, 1296);var(208, 1298);var(208, 1301);var(219, 1320);var(226, 1331);var(240, 1346);var(250, 1359);var(261, 1385);var(265, 1406);var(265, 1415);var(247, 1424);var(225, 1430);var(175, 1442);var(165, 1446);var(108, 1448);var(106, 1449);var(66, 1431);var(60, 1397);var(58, 1361);var(58, 1325);var(60, 1323);
    end

        cBLACK
        fan
        var(87, 1377);var(57, 1328);var(61, 1323);var(63, 1323);var(75, 1323);var(76, 1325);var(78, 1335);var(93, 1341);var(102, 1341);var(102, 1341);var(120, 1341);var(126, 1344);var(135, 1344);var(135, 1346);var(132, 1371);var(132, 1379);var(132, 1392);var(130, 1412);var(130, 1421);var(129, 1424);var(114, 1434);var(102, 1436);var(90, 1436);var(76, 1436);var(69, 1433);var(64, 1427);var(52, 1406);var(46, 1386);var(46, 1371);var(48, 1356);var(51, 1343);var(54, 1328);var(54, 1325);
    end
        strip
        var(208, 1299);var(202, 1299);var(195, 1302);var(190, 1307);var(189, 1307);var(181, 1313);var(177, 1316);var(169, 1322);var(166, 1323);var(160, 1331);var(160, 1332);var(153, 1355);var(153, 1367);var(153, 1374);var(153, 1382);var(139, 1401);var(136, 1407);var(132, 1410);var(132, 1410);
    end
        strip
        var(67, 1320);var(70, 1320);var(75, 1323);var(78, 1326);var(81, 1331);var(85, 1338);var(93, 1340);var(99, 1343);var(105, 1343);var(111, 1343);var(118, 1344);var(124, 1344);var(135, 1344);var(136, 1344);var(150, 1346);var(151, 1346);var(162, 1341);var(162, 1341);
    end

        cGRAY
        fan
        var(256, 1380);var(192, 1424);var(193, 1415);var(223, 1338);var(229, 1335);var(234, 1325);var(238, 1326);var(259, 1326);var(267, 1326);var(270, 1326);var(279, 1326);var(288, 1329);var(303, 1344);var(307, 1356);var(315, 1365);var(316, 1377);var(324, 1392);var(333, 1404);var(333, 1412);var(333, 1413);var(321, 1424);var(313, 1424);var(301, 1424);var(283, 1424);var(261, 1419);var(249, 1421);var(228, 1422);var(207, 1431);var(207, 1431);var(201, 1431);var(192, 1428);var(192, 1428);var(193, 1415);
    end
        cBLACK
        strip
        var(256, 1380);var(192, 1424);var(193, 1415);var(223, 1338);var(229, 1335);var(234, 1325);var(238, 1326);var(259, 1326);var(267, 1326);var(270, 1326);var(279, 1326);var(288, 1329);var(303, 1344);var(307, 1356);var(315, 1365);var(316, 1377);var(324, 1392);var(333, 1404);var(333, 1412);var(333, 1413);var(321, 1424);var(313, 1424);var(301, 1424);var(283, 1424);var(261, 1419);var(249, 1421);var(228, 1422);var(207, 1431);var(207, 1431);var(201, 1431);var(192, 1428);var(192, 1428);var(193, 1415);
    end
        fan
        var(244, 1380);var(225, 1340);var(237, 1343);var(246, 1343);var(258, 1350);var(259, 1350);var(267, 1356);var(267, 1358);var(268, 1362);var(267, 1374);var(280, 1389);var(288, 1403);var(294, 1415);var(294, 1415);var(289, 1421);var(283, 1424);var(276, 1428);var(265, 1431);var(258, 1431);var(238, 1428);var(231, 1425);var(222, 1424);var(214, 1424);var(210, 1424);var(204, 1424);var(199, 1422);var(195, 1422);var(195, 1422);var(190, 1418);var(222, 1340);
    end

        cBLACK
        strip
        var(292, 1341);var(292, 1349);var(294, 1362);var(295, 1371);var(301, 1382);var(301, 1383);var(298, 1389);var(298, 1392);var(301, 1397);var(301, 1401);var(301, 1401);var(307, 1406);var(313, 1412);var(318, 1415);var(324, 1418);
    end

        cGRAY
        fan
        var(253, 1433);var(219, 1448);var(225, 1440);var(255, 1410);var(291, 1436);var(288, 1440);var(255, 1448);var(243, 1448);var(222, 1454);var(222, 1445);
    end
        cBLACK
        strip
        var(219, 1448);var(225, 1440);var(255, 1410);var(291, 1436);var(288, 1440);var(255, 1448);var(243, 1448);var(222, 1454);var(222, 1445);
    end





        cGRAY
        fan
        var(43, 1413);var(0, 1400);var(37, 1343);var(39, 1340);var(42, 1337);var(42, 1337);var(45, 1335);var(48, 1335);var(48, 1338);var(49, 1343);var(51, 1346);var(58, 1353);var(66, 1356);var(73, 1361);var(84, 1367);var(87, 1367);var(87, 1367);var(88, 1374);var(90, 1379);var(90, 1380);var(96, 1394);var(99, 1406);var(102, 1421);var(114, 1452);var(39, 1482);var(30, 1493);var(25, 1493);var(22, 1493);var(16, 1488);var(9, 1478);var(7, 1476);var(6, 1475);var(4, 1472);var(0, 1470);var(3, 1398);var(4, 1394);
    end

        cBLACK
        fan
        var(16, 1430);var(39, 1338);var(40, 1412);var(43, 1413);var(45, 1415);var(48, 1416);var(48, 1418);var(48, 1422);var(45, 1422);var(42, 1424);var(43, 1425);var(40, 1436);var(40, 1443);var(40, 1449);var(42, 1457);var(46, 1458);var(43, 1464);var(43, 1472);var(42, 1485);var(40, 1485);var(37, 1485);var(33, 1487);var(24, 1491);var(18, 1491);var(15, 1490);var(3, 1476);var(-2, 1472);var(0, 1470);var(0, 1397);var(37, 1338);
    end

        cBLACK
        strip
        var(0, 1400);var(37, 1343);var(39, 1340);var(42, 1337);var(42, 1337);var(45, 1335);var(48, 1335);var(48, 1338);var(49, 1343);var(51, 1346);var(58, 1353);var(66, 1356);var(73, 1361);var(84, 1367);var(87, 1367);var(87, 1367);var(88, 1374);var(90, 1379);var(90, 1380);var(96, 1394);var(99, 1406);var(102, 1421);var(114, 1452);var(39, 1482);var(30, 1493);var(25, 1493);var(22, 1493);var(16, 1488);var(9, 1478);var(7, 1476);var(6, 1475);var(4, 1472);var(0, 1470);var(3, 1398);var(4, 1394);
    end
        strip
        var(45, 1415);var(84, 1433);var(106, 1446);var(114, 1454);
    end


        cGRAY
        fan
        var(135, 1430);var(76, 1439);var(105, 1415);var(130, 1394);var(141, 1389);var(147, 1392);var(153, 1398);var(154, 1398);var(159, 1403);var(159, 1409);var(171, 1419);var(178, 1428);var(193, 1439);var(187, 1446);var(145, 1461);var(127, 1467);var(82, 1458);var(75, 1446);var(75, 1437);
    end
        cBLACK
        strip
        var(76, 1439);var(105, 1415);var(130, 1394);var(141, 1389);var(147, 1392);var(153, 1398);var(154, 1398);var(159, 1403);var(159, 1409);var(171, 1419);var(178, 1428);var(193, 1439);var(187, 1446);var(145, 1461);var(127, 1467);var(82, 1458);var(75, 1446);var(75, 1437);
    end
        strip
        var(159, 1407);var(160, 1409);var(160, 1409);var(157, 1416);var(157, 1425);var(153, 1431);var(151, 1434);var(151, 1434);var(147, 1442);var(147, 1442);var(144, 1449);var(141, 1451);var(136, 1455);var(130, 1464);
    end
}

void middleStones()
{
    cGRAY
        fan
        var(907, 1418);var(814, 1431);var(847, 1386);var(862, 1371);var(880, 1359);var(894, 1349);var(925, 1361);var(958, 1368);var(972, 1364);var(984, 1377);var(1005, 1389);var(1006, 1404);var(1006, 1424);var(1009, 1467);var(1009, 1494);var(940, 1506);var(874, 1514);var(816, 1445);var(816, 1430);
    end
        cBLACK
        strip
        var(814, 1431);var(847, 1386);var(862, 1371);var(880, 1359);var(894, 1349);var(925, 1361);var(958, 1368);var(972, 1364);var(984, 1377);var(1005, 1389);var(1006, 1404);var(1006, 1424);var(1009, 1467);var(1009, 1494);var(940, 1506);var(874, 1514);var(816, 1445);var(816, 1430);
    end

        cBLACK
        strip
        var(864, 1383);var(897, 1446);var(904, 1466);var(918, 1467);var(930, 1469);var(940, 1469);var(955, 1466);var(966, 1461);var(976, 1461);var(991, 1457);
    end
        cBLACK
        fan
        var(981, 1479);var(957, 1469);var(970, 1457);var(984, 1452);var(999, 1443);var(1002, 1455);var(1002, 1476);var(1000, 1488);var(996, 1490);var(973, 1497);var(949, 1502);var(945, 1502);var(958, 1469);
    end
        rgb(0.25, 0.24, 0.23);
    fan
        var(876, 1470);var(828, 1448);var(843, 1448);var(852, 1436);var(856, 1419);var(862, 1403);var(867, 1386);var(894, 1445);var(903, 1460);var(912, 1466);var(924, 1467);var(939, 1472);var(955, 1473);var(954, 1479);var(954, 1490);var(954, 1491);var(951, 1497);var(937, 1502);var(927, 1503);var(912, 1509);var(897, 1514);var(885, 1515);var(874, 1517);var(873, 1517);var(825, 1452);var(831, 1448);
    end

        cSHADOW
        fan
        var(877, 1556);var(849, 1490);var(874, 1518);var(885, 1515);var(898, 1514);var(907, 1511);var(916, 1509);var(924, 1505);var(931, 1511);var(937, 1503);var(939, 1503);var(940, 1503);var(958, 1502);var(964, 1497);var(970, 1493);var(981, 1493);var(990, 1493);var(1000, 1485);var(1003, 1487);var(1017, 1542);var(1011, 1544);var(1009, 1547);var(1005, 1550);var(1002, 1553);var(997, 1556);var(949, 1571);var(849, 1589);var(820, 1595);var(816, 1583);var(817, 1574);var(820, 1557);var(829, 1547);var(835, 1541);var(855, 1494);
    end
        //right stones
        rgb(.2, .2, .2);
    fan
        var(1575, 1527);var(1541, 1559);var(1541, 1515);var(1561, 1513);var(1617, 1408);var(1675, 1419);var(1655, 1489);var(1619, 1509);var(1607, 1521);var(1593, 1531);var(1590, 1538);var(1580, 1544);var(1572, 1550);var(1559, 1555);var(1547, 1559);var(1544, 1558);var(1540, 1557);
    end
        fan
        var(1729, 1471);var(1669, 1421);var(1682, 1423);var(1698, 1423);var(1701, 1423);var(1713, 1423);var(1719, 1423);var(1730, 1421);var(1732, 1421);var(1735, 1422);var(1742, 1422);var(1744, 1422);var(1752, 1421);var(1753, 1421);var(1789, 1427);var(1807, 1423);var(1825, 1421);var(1853, 1420);var(1875, 1413);var(1881, 1407);var(1889, 1403);var(1893, 1402);var(1891, 1406);var(1887, 1425);var(1882, 1434);var(1881, 1440);var(1879, 1448);var(1875, 1457);var(1871, 1464);var(1868, 1469);var(1861, 1476);var(1855, 1482);var(1847, 1485);var(1835, 1492);var(1833, 1497);var(1829, 1499);var(1821, 1500);var(1812, 1501);var(1806, 1511);var(1803, 1516);var(1801, 1519);var(1792, 1521);var(1779, 1523);var(1777, 1523);var(1771, 1520);var(1767, 1513);var(1765, 1511);var(1761, 1508);var(1747, 1505);var(1736, 1505);var(1725, 1507);var(1707, 1508);var(1689, 1501);var(1680, 1504);var(1671, 1506);var(1662, 1502);var(1657, 1494);var(1656, 1488);var(1663, 1484);var(1675, 1470);var(1680, 1459);var(1687, 1444);var(1697, 1435);var(1705, 1427);var(1718, 1423);var(1729, 1422);var(1735, 1421);
    end
        fan
        var(1661, 1452);var(1641, 1442);var(1643, 1471);var(1643, 1487);var(1651, 1488);var(1665, 1483);var(1667, 1481);var(1675, 1473);var(1681, 1463);var(1693, 1449);var(1694, 1441);var(1692, 1437);var(1683, 1433);var(1657, 1431);var(1645, 1430);var(1634, 1457);
    end
        fan
        var(1515, 1532);var(1505, 1526);var(1509, 1514);var(1510, 1507);var(1510, 1500);var(1511, 1491);var(1512, 1483);var(1519, 1479);var(1522, 1472);var(1525, 1469);var(1531, 1462);var(1531, 1462);var(1537, 1459);var(1538, 1457);var(1540, 1471);var(1540, 1472);var(1540, 1480);var(1540, 1487);var(1540, 1491);var(1540, 1499);var(1540, 1505);var(1537, 1505);var(1533, 1513);var(1532, 1517);var(1531, 1533);var(1531, 1533);var(1530, 1539);var(1525, 1546);var(1523, 1547);var(1522, 1554);var(1521, 1557);var(1519, 1557);var(1507, 1565);var(1499, 1567);var(1485, 1568);var(1481, 1568);var(1475, 1568);var(1462, 1570);var(1458, 1573);var(1455, 1573);var(1460, 1567);var(1464, 1563);var(1469, 1559);var(1481, 1554);var(1495, 1545);var(1497, 1541);var(1507, 1521);var(1508, 1521);
    end
        fan
        var(1827, 1443);var(1760, 1422);var(1753, 1419);var(1753, 1413);var(1757, 1405);var(1761, 1402);var(1771, 1398);var(1775, 1398);var(1778, 1398);var(1787, 1398);var(1793, 1397);var(1796, 1397);var(1804, 1397);var(1807, 1397);var(1812, 1397);var(1821, 1397);var(1821, 1397);var(1821, 1397);var(1827, 1404);var(1821, 1409);var(1819, 1411);var(1818, 1419);var(1818, 1431);var(1816, 1445);var(1815, 1457);var(1817, 1463);var(1795, 1456);var(1781, 1442);var(1771, 1422);var(1757, 1414);
    end
        fan
        var(1831, 1396);var(1835, 1391);var(1843, 1384);var(1849, 1380);var(1882, 1366);var(1859, 1380);var(1851, 1387);var(1845, 1391);var(1832, 1397);var(1827, 1399);var(1824, 1400);var(1827, 1397);var(1833, 1389);
    end
        fan
        var(1729, 1388);var(1649, 1397);var(1701, 1387);var(1707, 1385);var(1717, 1382);var(1725, 1383);var(1728, 1383);var(1731, 1382);var(1732, 1382);var(1734, 1384);var(1736, 1385);var(1737, 1387);var(1739, 1389);var(1741, 1391);var(1741, 1392);var(1736, 1393);var(1730, 1393);var(1726, 1393);var(1723, 1393);var(1719, 1392);var(1717, 1391);var(1714, 1391);var(1650, 1397);
    end


        rgb(0.25, 0.24, 0.23);
    fan
        var(1591, 1427);var(1570, 1437);var(1573, 1425);var(1576, 1416);var(1579, 1407);var(1583, 1402);var(1591, 1394);var(1595, 1390);var(1598, 1383);var(1602, 1380);var(1605, 1377);var(1606, 1376);var(1613, 1371);var(1614, 1368);var(1615, 1366);var(1619, 1363);var(1616, 1373);var(1616, 1381);var(1615, 1383);var(1613, 1393);var(1613, 1399);var(1612, 1404);var(1611, 1409);var(1607, 1414);var(1603, 1419);var(1601, 1419);var(1597, 1426);var(1594, 1430);var(1587, 1441);var(1586, 1447);var(1584, 1454);var(1579, 1460);var(1576, 1465);var(1575, 1467);var(1575, 1467);var(1572, 1469);var(1569, 1466);var(1569, 1459);var(1571, 1454);var(1571, 1443);var(1571, 1427);var(1575, 1422);
    end

        cBLACK
        fan
        var(1556, 1466);var(1543, 1514);var(1538, 1496);var(1541, 1477);var(1534, 1452);var(1533, 1447);var(1545, 1437);var(1551, 1433);var(1557, 1426);var(1567, 1425);var(1565, 1430);var(1567, 1441);var(1567, 1456);var(1567, 1463);var(1571, 1469);var(1573, 1480);var(1572, 1487);var(1569, 1502);var(1567, 1508);var(1563, 1509);var(1553, 1511);var(1547, 1512);var(1544, 1511);var(1541, 1496);
    end


        //outline
        cBLACK
        strip
        var(1565, 1422);var(1567, 1415);var(1569, 1408);var(1570, 1402);var(1571, 1396);var(1573, 1392);var(1576, 1388);var(1579, 1385);var(1582, 1381);var(1585, 1376);var(1590, 1372);var(1596, 1368);var(1603, 1361);var(1605, 1359);var(1610, 1356);var(1615, 1352);var(1618, 1349);var(1622, 1343);var(1626, 1337);var(1627, 1333);var(1629, 1330);var(1631, 1329);var(1639, 1327);var(1647, 1327);var(1652, 1327);var(1654, 1327);var(1665, 1325);var(1669, 1325);var(1676, 1325);var(1691, 1325);var(1700, 1325);var(1711, 1325);var(1716, 1324);var(1721, 1326);var(1727, 1326);var(1735, 1327);var(1750, 1327);var(1757, 1327);var(1763, 1326);var(1773, 1325);var(1781, 1325);var(1791, 1326);var(1805, 1329);var(1816, 1331);var(1821, 1334);var(1827, 1337);var(1841, 1339);var(1841, 1340);var(1845, 1341);
    end
        strip
        var(1623, 1346);var(1623, 1354);var(1623, 1360);var(1621, 1365);var(1620, 1369);var(1619, 1375);var(1619, 1381);var(1618, 1388);var(1617, 1391);var(1617, 1394);var(1615, 1399);var(1615, 1399);var(1613, 1405);var(1612, 1409);var(1611, 1411);var(1609, 1417);var(1605, 1423);var(1603, 1423);var(1601, 1424);var(1596, 1433);var(1594, 1437);var(1591, 1440);var(1589, 1444);var(1586, 1450);var(1583, 1456);var(1583, 1459);var(1580, 1464);var(1579, 1471);var(1577, 1473);var(1575, 1479);var(1571, 1484);var(1568, 1487);var(1567, 1489);var(1566, 1490);
    end
        strip
        var(1605, 1421);var(1610, 1413);var(1611, 1409);var(1613, 1406);var(1618, 1402);var(1625, 1407);var(1632, 1411);var(1635, 1411);var(1642, 1412);var(1649, 1414);var(1651, 1415);var(1667, 1418);var(1678, 1419);var(1684, 1421);var(1694, 1421);var(1703, 1422);var(1711, 1423);var(1717, 1421);var(1723, 1417);var(1726, 1415);
    end
        strip
        var(1618, 1411);var(1625, 1417);var(1634, 1419);var(1644, 1423);var(1647, 1423);var(1677, 1429);var(1678, 1429);var(1686, 1429);var(1690, 1429);var(1708, 1429);var(1712, 1430);
    end
        strip
        var(1743, 1421);var(1749, 1421);var(1758, 1409);var(1759, 1399);var(1764, 1400);var(1770, 1403);var(1779, 1407);var(1785, 1407);var(1814, 1411);var(1817, 1410);var(1829, 1408);var(1838, 1407);var(1852, 1407);
    end

        cGLASSBACK
        fan
        var(1604, 1609);var(1586, 1640);var(1585, 1634);var(1588, 1631);var(1589, 1626);var(1591, 1620);var(1592, 1610);var(1593, 1604);var(1593, 1590);var(1593, 1584);var(1595, 1578);var(1595, 1574);var(1596, 1569);var(1606, 1576);var(1616, 1590);var(1628, 1604);var(1630, 1612);var(1631, 1615);var(1614, 1612);var(1611, 1616);var(1603, 1619);var(1596, 1624);var(1596, 1624);var(1595, 1628);var(1591, 1629);var(1586, 1630);
    end

        //outline
        cBLACK
        strip
        var(1584, 1641);var(1584, 1641);var(1584, 1634);var(1587, 1630);var(1587, 1627);var(1589, 1624);var(1588, 1621);var(1589, 1615);var(1589, 1613);var(1589, 1610);var(1591, 1602);var(1591, 1596);var(1591, 1592);var(1593, 1588);var(1594, 1583);var(1594, 1580);var(1596, 1574);var(1598, 1571);var(1598, 1568);var(1599, 1568);var(1601, 1568);var(1604, 1570);var(1605, 1572);var(1611, 1578);var(1613, 1580);var(1617, 1587);var(1621, 1592);var(1628, 1598);var(1631, 1602);var(1632, 1610);var(1635, 1617);var(1639, 1620);var(1641, 1620);var(1651, 1624);var(1659, 1624);var(1663, 1629);var(1669, 1635);var(1672, 1637);var(1675, 1639);var(1680, 1645);var(1689, 1652);var(1693, 1652);var(1700, 1652);var(1707, 1650);var(1714, 1652);var(1726, 1648);var(1729, 1646);var(1729, 1645);var(1732, 1643);var(1735, 1642);var(1736, 1642);var(1739, 1640);var(1741, 1640);var(1746, 1640);var(1752, 1638);var(1752, 1640);var(1755, 1651);var(1755, 1657);var(1754, 1665);var(1753, 1674);var(1752, 1676);var(1751, 1679);var(1749, 1683);var(1738, 1690);var(1727, 1697);var(1716, 1703);var(1700, 1709);var(1693, 1712);var(1681, 1714);var(1672, 1714);var(1667, 1714);var(1662, 1710);var(1657, 1700);var(1651, 1692);var(1647, 1687);var(1645, 1680);var(1645, 1674);var(1643, 1672);var(1641, 1668);var(1635, 1664);var(1633, 1665);var(1625, 1669);var(1622, 1672);var(1618, 1672);var(1609, 1668);var(1599, 1659);var(1591, 1652);var(1582, 1641);var(1581, 1637);
    end

        //outlines
        cBLACK
        fan
        var(472, 1307);var(451, 1302);var(424, 1302);var(422, 1307);var(415, 1308);var(407, 1302);var(409, 1289);var(418, 1278);var(451, 1265);var(481, 1253);var(499, 1245);var(551, 1236);var(568, 1241);var(578, 1242);var(592, 1248);var(607, 1275);var(607, 1277);var(587, 1280);var(565, 1280);var(554, 1280);var(539, 1292);var(514, 1293);var(508, 1289);var(499, 1280);var(493, 1272);var(506, 1265);var(452, 1290);var(542, 1263);
    end
        strip
        var(545, 1292);var(557, 1274);var(566, 1260);var(574, 1245);var(589, 1229);var(604, 1235);var(610, 1239);var(616, 1244);var(625, 1250);var(631, 1245);var(640, 1230);var(653, 1236);var(664, 1247);var(671, 1253);var(680, 1253);var(689, 1253);var(692, 1251);var(697, 1251);var(713, 1268);var(718, 1269);var(724, 1265);var(724, 1265);
    end
}
void scatteredStones()
{
    //stone
    cGRAY
        fan
        var(887, 1294);var(892, 1280);var(878, 1286);var(876, 1292);var(867, 1300);var(848, 1310);var(867, 1312);var(880, 1312);var(900, 1311);var(915, 1310);var(917, 1304);var(906, 1297);var(892, 1282);var(880, 1285);
    end
        cBLACK
        strip
        var(892, 1280);var(878, 1286);var(876, 1292);var(867, 1300);var(848, 1310);var(867, 1312);var(880, 1312);var(900, 1311);var(915, 1310);var(917, 1304);var(906, 1297);var(892, 1282);var(880, 1285);
    end
        fan
        var(883, 1304);var(858, 1300);var(876, 1304);var(898, 1302);var(911, 1302);var(902, 1311);var(885, 1311);var(868, 1311);var(857, 1314);var(850, 1314);var(855, 1300);var(857, 1299);var(868, 1300);var(877, 1300);var(885, 1301);
    end
        //shadow
        cSHADOW
        fan
        var(852, 1317);var(835, 1312);var(828, 1316);var(826, 1325);var(833, 1334);var(843, 1334);var(857, 1332);var(871, 1325);var(880, 1324);var(892, 1321);var(907, 1314);var(916, 1309);var(915, 1306);var(911, 1302);
    end

        //stone
        cGRAY
        fan
        var(965, 1308);var(968, 1300);var(960, 1303);var(957, 1305);var(954, 1306);var(954, 1309);var(956, 1311);var(959, 1311);var(963, 1311);var(969, 1311);var(973, 1311);var(975, 1311);var(977, 1310);var(974, 1305);var(970, 1303);var(963, 1299);
    end
        strip
        var(965, 1308);var(968, 1300);var(960, 1303);var(957, 1305);var(954, 1306);var(954, 1309);var(956, 1311);var(959, 1311);var(963, 1311);var(969, 1311);var(973, 1311);var(975, 1311);var(977, 1310);var(974, 1305);var(970, 1303);var(963, 1299);
    end
        //shadow
        cSHADOW
        fan
        var(955, 1315);var(955, 1311);var(950, 1309);var(948, 1312);var(947, 1315);var(948, 1320);var(951, 1320);var(955, 1320);var(964, 1320);var(966, 1320);var(968, 1320);var(972, 1316);var(976, 1315);var(977, 1313);var(973, 1313);var(965, 1313);var(957, 1314);var(954, 1314);
    end


}
void car1()
{
    //-----------------car1-----------------------


        //cae shape
    rgb(0.57, 0.67, 0.62); //car color
    polygon
        var(2000, 988); var(1629, 1019); var(1578, 1122); var(1727, 1194);var(2000, 1182);
    end
        polygon
        var(1528, 1130);var(1565, 1113);var(2000, 1160);var(2000, 1302);var(1777, 1329);var(1675, 1235);
    end
        polygon
        var(1608, 1265);var(1611, 1215);var(1674, 1230);var(1665, 1282);var(1654, 1291);
    end
        fan
        var(1607, 1183);var(1534, 1130);var(1516, 1216);var(1534, 1243);var(1562, 1243);var(1612, 1228);var(1681, 1232);var(1727, 1232);var(1581, 1126);var(1534, 1130);
    end

        //car front glass
        cGLASSBACK //glass back
        fan
        var(1839, 1063);var(1690, 1030);var(1992, 1004);var(1998, 1010);var(2000, 1013);var(2000, 1087);var(1875, 1104);var(1846, 1100);var(1700, 1126);var(1691, 1119);var(1684, 1113);var(1690, 1030);
    end
        cGLASSFRONT //glass front
        circle(70, 30, 1839, 1063);
    fan
        var(1839, 1063);var(1844, 1099);var(1790, 1100);var(1780, 1069);var(1820, 1028);var(1877, 1018);var(1977, 1026);var(1951, 1089);var(1844, 1099);
    end

        //car window
        cBLACK
        fan
        var(1627, 1084);var(1627, 1041);var(1634, 1039);var(1649, 1048);var(1649, 1055);var(1644, 1103);var(1643, 1107);var(1641, 1112);var(1603, 1116);var(1602, 1111);var(1601, 1105);var(1623, 1042);var(1627, 1041);
    end
        cGLASSFRONT //glass front
        fan
        var(1657, 1076);var(1659, 1042);var(1661, 1076);var(1659, 1089);var(1653, 1107);var(1648, 1104);var(1654, 1073);var(1656, 1045);var(1659, 1042);
    end
        triangle
        var(1659, 1043);var(1654, 1045);var(1645, 1034);
    end


        //others shapes
        cBLACK
        strip
        var(1636, 1029);var(1660, 1033);var(1664, 1035);var(1666, 1041);var(1662, 1114);
    end


        //side mirror
        cBLACK
        polygon
        var(1547, 1112);var(1584, 1100);var(1615, 1139);var(1540, 1150);
    end
        polygon
        var(1602, 1126);var(1657, 1121);var(1654, 1131);var(1621, 1138);var(1611, 1142);
    end
        cGLASSBACK //glass back
        polygon
        var(1550, 1116);var(1583, 1104);var(1593, 1127);var(1550, 1135);

    end
        cGLASSFRONT //glass front
        polygon
        var(1550, 1116);var(1583, 1104);var(1588, 1115);var(1551, 1124);
    end


        ///front panel
        cBLACK
        polygon
        var(1720, 1197);var(1926, 1174);var(1936, 1183);var(1956, 1228);var(1727, 1233);
    end
        circle(18, 16, 1732, 1209);


    //rear wheel
    cBLACK
        circle(14, 25, 1592, 1223);
    fan
        var(1592, 1223);var(1584, 1208);var(1567, 1225);var(1559, 1248);var(1592, 1244);var(1598, 1248);var(1603, 1246);var(1605, 1241);var(1606, 1234);var(1606, 1227);var(1605, 1213);var(1594, 1204);var(1587, 1204);var(1583, 1207);
    end
        fan
        var(1966, 1207);var(1938, 1182);var(1945, 1186);var(1952, 1188);var(1959, 1187);var(1962, 1185);var(1965, 1182);var(1968, 1178);var(1974, 1175);var(1983, 1174);var(1990, 1171);var(2000, 1169);var(2000, 1223);var(1993, 1226);var(1986, 1226);var(1978, 1226);var(1972, 1226);var(1963, 1226);var(1955, 1230);var(1945, 1230);var(1937, 1230);var(1930, 1230);var(1925, 1231);var(1919, 1231);var(1938, 1182);
    end

        //head light
        cGLASSBACK //glass back

        fan
        var(1772, 1209);var(1774, 1190);var(1785, 1188);var(1798, 1187);var(1811, 1185);var(1823, 1182);var(1826, 1184);var(1826, 1185);var(1829, 1188);var(1830, 1192);var(1833, 1197);var(1834, 1200);var(1834, 1206);var(1834, 1211);var(1835, 1216);var(1833, 1218);var(1832, 1221);var(1829, 1224);var(1826, 1225);var(1820, 1226);var(1813, 1228);var(1805, 1229);var(1771, 1231);var(1762, 1231);var(1750, 1232);var(1743, 1232);var(1735, 1232);var(1732, 1232);var(1728, 1230);var(1725, 1225);var(1722, 1219);var(1719, 1213);var(1719, 1208);var(1720, 1204);var(1722, 1201);var(1724, 1200);var(1725, 1199);var(1728, 1198);var(1729, 1198);var(1733, 1198);var(1737, 1197);var(1742, 1196);var(1747, 1195);var(1757, 1194);var(1765, 1193);var(1774, 1191);
    end
        cGLASSFRONT //glass front
        fan
        var(1801, 1205);var(1775, 1194);var(1780, 1192);var(1786, 1192);var(1791, 1190);var(1797, 1190);var(1805, 1189);var(1811, 1189);var(1817, 1188);var(1822, 1188);var(1825, 1190);var(1829, 1196);var(1831, 1202);var(1832, 1207);var(1833, 1210);var(1833, 1212);var(1832, 1215);var(1831, 1217);var(1830, 1220);var(1829, 1221);var(1825, 1222);var(1822, 1224);var(1816, 1225);var(1812, 1225);var(1807, 1225);var(1803, 1225);var(1798, 1225);var(1792, 1225);var(1788, 1224);var(1782, 1224);var(1778, 1224);var(1771, 1221);var(1767, 1220);var(1764, 1216);var(1761, 1212);var(1761, 1208);var(1762, 1201);var(1767, 1197);var(1769, 1196);
    end
        cBLACK
        strip
        var(1681, 1038);var(1686, 1034);var(1694, 1031);var(1701, 1030);var(1714, 1030);var(1737, 1030);var(1749, 1027);var(1755, 1026);var(1769, 1023);var(1776, 1022);var(1792, 1021);var(1805, 1020);var(1822, 1020);var(1831, 1016);var(1846, 1014);var(1861, 1014);var(1883, 1015);var(1913, 1010);var(1962, 1007);var(1992, 1004);var(2000, 1011);var(2001, 1018);var(1999, 1088);var(1990, 1093);var(1982, 1095);var(1959, 1095);var(1946, 1091);var(1938, 1090);var(1931, 1090);var(1922, 1088);var(1913, 1089);var(1910, 1091);var(1898, 1099);var(1888, 1102);var(1867, 1105);var(1858, 1105);var(1850, 1106);var(1841, 1106);var(1834, 1107);var(1813, 1111);var(1813, 1111);var(1770, 1117);var(1743, 1121);var(1720, 1122);var(1706, 1122);var(1702, 1122);var(1697, 1119);var(1694, 1117);var(1692, 1114);var(1688, 1110);var(1688, 1108);var(1684, 1105);var(1682, 1095);var(1682, 1088);var(1682, 1079);var(1682, 1072);var(1682, 1061);var(1682, 1052);var(1681, 1047);var(1682, 1039);
    end

        //front line
        cBLACK
        strip
        var(1837, 1235);var(1832, 1235);var(1826, 1235);var(1821, 1235);var(1813, 1236);var(1806, 1237);var(1800, 1238);var(1794, 1239);var(1789, 1240);var(1784, 1240);var(1780, 1240);var(1777, 1239);var(1768, 1238);var(1762, 1238);var(1755, 1238);var(1749, 1238);var(1742, 1238);var(1737, 1237);var(1731, 1236);var(1729, 1234);var(1726, 1229);var(1723, 1224);var(1720, 1220);var(1718, 1218);var(1716, 1213);var(1716, 1209);var(1717, 1206);var(1718, 1202);var(1720, 1199);var(1723, 1197);var(1728, 1197);var(1732, 1195);var(1738, 1195);var(1741, 1194);var(1745, 1194);var(1750, 1192);var(1755, 1191);var(1760, 1191);var(1765, 1189);var(1770, 1189);var(1776, 1188);var(1785, 1187);var(1797, 1185);var(1806, 1183);var(1817, 1181);var(1832, 1180);var(1844, 1178);var(1854, 1178);var(1862, 1177);var(1872, 1176);var(1884, 1176);var(1898, 1176);var(1914, 1175);var(1923, 1179);var(1921, 1189);var(1920, 1204);var(1914, 1220);var(1908, 1225);var(1904, 1229);var(1894, 1231);var(1883, 1231);var(1872, 1233);var(1862, 1233);var(1851, 1234);var(1841, 1235);
    end

        //front wheel
        cBLACK
        fan
        var(1704, 1285);var(1693, 1238);var(1697, 1239);var(1702, 1239);var(1706, 1238);var(1713, 1237);var(1719, 1235);var(1728, 1234);var(1734, 1234);var(1741, 1234);var(1749, 1234);var(1760, 1234);var(1770, 1235);var(1777, 1239);var(1784, 1244);var(1784, 1248);var(1785, 1254);var(1787, 1260);var(1788, 1264);var(1788, 1270);var(1788, 1275);var(1787, 1283);var(1787, 1290);var(1786, 1298);var(1785, 1306);var(1783, 1317);var(1780, 1325);var(1774, 1328);var(1766, 1328);var(1755, 1327);var(1746, 1325);var(1739, 1326);var(1730, 1326);var(1721, 1326);var(1714, 1326);var(1704, 1326);var(1691, 1327);var(1681, 1327);var(1673, 1326);var(1668, 1325);var(1664, 1316);var(1664, 1306);var(1663, 1294);var(1663, 1289);var(1665, 1281);var(1667, 1266);var(1669, 1260);var(1669, 1254);var(1670, 1250);var(1670, 1244);var(1672, 1238);var(1677, 1234);var(1685, 1234);var(1688, 1236);var(1688, 1236);var(1693, 1238);
    end

        rgb(0.27, 0.27, 0.25);
    fan
        var(1692, 1321);var(1675, 1278);var(1676, 1282);var(1676, 1286);var(1677, 1292);var(1680, 1298);var(1684, 1302);var(1689, 1304);var(1691, 1304);var(1693, 1303);var(1698, 1301);var(1703, 1300);var(1705, 1296);var(1706, 1290);var(1707, 1284);var(1709, 1282);var(1713, 1282);var(1713, 1284);var(1716, 1289);var(1718, 1293);var(1718, 1297);var(1718, 1304);var(1717, 1310);var(1714, 1319);var(1709, 1323);var(1703, 1325);var(1703, 1325);var(1694, 1325);var(1685, 1325);var(1677, 1324);var(1677, 1324);var(1672, 1318);var(1671, 1313);var(1670, 1308);var(1670, 1303);var(1670, 1297);var(1670, 1291);var(1671, 1286);var(1673, 1279);var(1675, 1278);
    end

        rgb(0.49, 0.45, 0.42);
    fan
        var(1693, 1316);var(1694, 1310);var(1697, 1308);var(1701, 1306);var(1705, 1302);var(1709, 1300);var(1710, 1296);var(1710, 1293);var(1711, 1289);var(1712, 1290);var(1712, 1294);var(1713, 1297);var(1713, 1300);var(1713, 1304);var(1713, 1308);var(1713, 1313);var(1711, 1320);var(1709, 1322);var(1704, 1324);var(1697, 1324);var(1678, 1324);var(1674, 1320);var(1672, 1315);var(1671, 1312);var(1671, 1307);var(1671, 1305);var(1673, 1302);var(1675, 1304);var(1679, 1307);var(1682, 1309);var(1687, 1310);var(1691, 1310);var(1693, 1309);
    end
        rgb(0.25, 0.24, 0.22);
    fan
        var(1751, 1308);var(1744, 1279);var(1748, 1279);var(1754, 1279);var(1759, 1279);var(1762, 1280);var(1766, 1283);var(1770, 1288);var(1772, 1293);var(1773, 1301);var(1773, 1306);var(1773, 1314);var(1773, 1320);var(1773, 1326);var(1766, 1327);var(1748, 1327);var(1736, 1327);var(1719, 1326);var(1721, 1321);var(1725, 1315);var(1728, 1309);var(1729, 1304);var(1730, 1298);var(1732, 1294);var(1736, 1287);var(1739, 1281);var(1744, 1279);
    end
        cBLACK
        strip
        var(1754, 1289);var(1754, 1294);var(1754, 1298);var(1753, 1305);var(1752, 1311);var(1751, 1315);var(1750, 1318);
    end
        strip
        var(1760, 1307);var(1761, 1303);var(1761, 1299);var(1761, 1295);var(1762, 1291);var(1761, 1287);
    end

        strip
        var(1767, 1279);var(1767, 1284);var(1767, 1291);var(1767, 1301);
    end

        //destroyed
        cBLACK
        fan
        var(1906, 1026);var(1888, 1013);var(1884, 1020);var(1878, 1027);var(1874, 1034);var(1866, 1041);var(1864, 1045);var(1867, 1052);var(1874, 1049);var(1880, 1049);var(1886, 1050);var(1892, 1053);var(1898, 1055);var(1903, 1052);var(1907, 1049);var(1999, 1043);var(2000, 1010);var(1994, 1005);var(1966, 1007);var(1902, 1014);var(1889, 1011);
    end
        fan
        var(1925, 1050);var(1915, 1039);var(1909, 1043);var(1909, 1047);var(1910, 1050);var(1910, 1053);var(1910, 1061);var(1910, 1069);var(1914, 1071);var(1916, 1071);var(1921, 1070);var(1924, 1066);var(1927, 1066);var(1934, 1066);var(1934, 1066);var(1939, 1068);var(1944, 1068);var(1946, 1066);var(1946, 1062);var(1946, 1048);var(1942, 1040);var(1930, 1033);var(1923, 1033);var(1921, 1033);var(1916, 1034);var(1915, 1041);
    end
        fan
        var(1937, 1067);var(1938, 1075);var(1941, 1083);var(1947, 1086);var(1953, 1092);var(1956, 1093);var(1965, 1093);var(1973, 1090);var(1981, 1090);var(1994, 1087);var(2000, 1087);var(2000, 1045);var(2000, 1009);var(2000, 1004);var(1991, 1004);var(1985, 1004);var(1979, 1006);var(1977, 1006);var(1969, 1009);var(1964, 1010);var(1952, 1010);var(1933, 1019);var(1917, 1032);var(1923, 1051);var(1937, 1062);var(1941, 1070);var(1940, 1076);var(1977, 1047);
    end


        //
    //-----------------car1-----------------------
}
void car2()
{

    //shadow
    cBLACK
        fan
        var(1399, 1317);var(1355, 1309);var(1357, 1304);var(1366, 1297);var(1392, 1293);var(1402, 1292);var(1428, 1289);var(1436, 1289);var(1436, 1289);var(1436, 1294);var(1438, 1304);var(1438, 1309);var(1438, 1313);var(1434, 1318);var(1434, 1319);var(1425, 1324);var(1416, 1324);var(1414, 1324);var(1411, 1325);var(1403, 1326);var(1400, 1325);var(1392, 1323);var(1381, 1321);var(1376, 1320);var(1373, 1319);var(1358, 1318);var(1358, 1318);var(1355, 1303);var(1358, 1300);
    end
        //body
        cCYAN
        fan
        var(1272, 1218);var(1140, 1172);var(1250, 1144);var(1289, 1136);var(1311, 1132);var(1323, 1131);var(1332, 1132);var(1343, 1132);var(1349, 1130);var(1356, 1130);var(1368, 1128);var(1373, 1127);var(1376, 1127);var(1378, 1127);var(1380, 1128);var(1381, 1129);var(1384, 1132);var(1385, 1134);var(1389, 1140);var(1404, 1164);var(1410, 1174);var(1415, 1180);var(1420, 1181);var(1430, 1190);var(1436, 1200);var(1437, 1200);var(1442, 1212);var(1448, 1220);var(1453, 1228);var(1457, 1233);var(1462, 1240);var(1464, 1249);var(1464, 1258);var(1464, 1268);var(1464, 1270);var(1460, 1273);var(1447, 1273);var(1432, 1273);var(1419, 1277);var(1403, 1277);var(1387, 1282);var(1374, 1286);var(1365, 1286);var(1354, 1286);var(1326, 1288);var(1270, 1300);var(1169, 1324);var(1101, 1338);var(1095, 1311);var(1100, 1270);var(1102, 1268);var(1104, 1264);var(1105, 1261);var(1108, 1258);var(1110, 1254);var(1112, 1252);var(1113, 1248);var(1116, 1245);var(1117, 1242);var(1118, 1240);var(1120, 1238);var(1122, 1235);var(1123, 1234);var(1124, 1230);var(1127, 1221);var(1126, 1217);var(1126, 1214);var(1127, 1210);var(1128, 1205);var(1130, 1196);var(1132, 1190);var(1133, 1185);var(1134, 1180);var(1135, 1178);var(1135, 1177);var(1135, 1176);var(1136, 1176);var(1137, 1175);var(1138, 1173);var(1139, 1173);
    end

        //front glass
        cGLASSBACK
        fan
        var(1143, 1183);var(1147, 1181);var(1150, 1179);var(1156, 1176);var(1259, 1152);var(1301, 1144);var(1317, 1142);var(1327, 1141);var(1376, 1136);var(1405, 1177);var(1405, 1177);var(1371, 1186);var(1347, 1193);var(1314, 1198);var(1288, 1204);var(1273, 1206);var(1257, 1206);var(1240, 1209);var(1220, 1215);var(1206, 1214);var(1185, 1221);var(1165, 1225);var(1150, 1229);var(1140, 1230);var(1137, 1230);var(1135, 1228);var(1133, 1225);var(1143, 1184);var(1264, 1177);
    end
        cGLASSFRONT
        fan
        var(1267, 1178);var(1258, 1154);var(1252, 1155);var(1247, 1156);var(1239, 1158);var(1233, 1160);var(1227, 1162);var(1218, 1166);var(1211, 1170);var(1208, 1172);var(1200, 1176);var(1200, 1176);var(1194, 1178);var(1187, 1182);var(1179, 1186);var(1175, 1190);var(1171, 1194);var(1166, 1200);var(1167, 1200);var(1165, 1205);var(1169, 1207);var(1171, 1209);var(1172, 1209);var(1178, 1213);var(1182, 1213);var(1186, 1213);var(1192, 1212);var(1195, 1212);var(1200, 1213);var(1208, 1214);var(1213, 1213);var(1218, 1212);var(1224, 1211);var(1228, 1210);var(1241, 1207);var(1251, 1207);var(1264, 1204);var(1271, 1205);var(1280, 1203);var(1291, 1201);var(1298, 1201);var(1305, 1199);var(1313, 1197);var(1318, 1196);var(1323, 1195);var(1320, 1188);var(1312, 1177);var(1301, 1167);var(1295, 1163);var(1277, 1156);var(1263, 1151);var(1261, 1154);
    end
        //headlight - right
        cBLACK
        fan
        var(1407, 1210);var(1375, 1216);var(1371, 1220);var(1370, 1225);var(1371, 1227);var(1373, 1233);var(1375, 1233);var(1382, 1235);var(1387, 1235);var(1395, 1235);var(1403, 1235);var(1417, 1232);var(1432, 1225);var(1435, 1224);var(1438, 1222);var(1444, 1220);var(1444, 1220);var(1450, 1219);var(1451, 1217);var(1451, 1215);var(1451, 1211);var(1447, 1204);var(1447, 1203);var(1443, 1199);var(1442, 1199);var(1442, 1199);var(1440, 1198);var(1439, 1195);var(1437, 1191);var(1436, 1187);var(1433, 1187);var(1428, 1183);var(1428, 1183);var(1422, 1183);var(1420, 1184);var(1418, 1184);var(1414, 1190);var(1406, 1194);var(1398, 1199);var(1398, 1202);var(1377, 1207);var(1378, 1216);var(1374, 1222);var(1382, 1231);
    end
        cGLASSBACK
        fan
        var(1412, 1209);var(1374, 1222);var(1377, 1219);var(1379, 1214);var(1381, 1212);var(1383, 1209);var(1385, 1208);var(1388, 1206);var(1391, 1203);var(1394, 1201);var(1396, 1199);var(1399, 1197);var(1403, 1195);var(1407, 1192);var(1410, 1189);var(1415, 1187);var(1417, 1185);var(1420, 1185);var(1424, 1184);var(1429, 1186);var(1432, 1187);var(1434, 1190);var(1435, 1193);var(1436, 1196);var(1437, 1197);var(1438, 1199);var(1438, 1201);var(1438, 1204);var(1438, 1205);var(1437, 1208);var(1437, 1208);var(1437, 1210);var(1437, 1214);var(1435, 1217);var(1433, 1218);var(1430, 1220);var(1425, 1221);var(1421, 1222);var(1383, 1229);var(1376, 1229);var(1374, 1228);var(1374, 1225);var(1374, 1223);
    end
        cGLASSFRONT
        fan
        var(1419, 1202);var(1404, 1201);var(1404, 1198);var(1405, 1196);var(1406, 1195);var(1410, 1194);var(1412, 1192);var(1414, 1190);var(1416, 1190);var(1420, 1189);var(1424, 1189);var(1426, 1188);var(1430, 1189);var(1432, 1191);var(1434, 1195);var(1436, 1197);var(1436, 1200);var(1436, 1205);var(1436, 1207);var(1436, 1209);var(1434, 1211);var(1432, 1213);var(1428, 1215);var(1425, 1215);var(1422, 1215);var(1418, 1215);var(1416, 1215);var(1411, 1217);var(1409, 1218);var(1408, 1218);var(1407, 1217);var(1405, 1215);var(1404, 1211);var(1403, 1208);var(1405, 1204);var(1404, 1200);
    end

        //headlight - left
        cBLACK
        fan
        var(1120, 1287);var(1094, 1282);var(1094, 1282);var(1094, 1288);var(1094, 1290);var(1091, 1294);var(1091, 1294);var(1091, 1299);var(1093, 1303);var(1094, 1306);var(1094, 1307);var(1097, 1310);var(1099, 1311);var(1100, 1313);var(1101, 1313);var(1103, 1314);var(1107, 1315);var(1113, 1315);var(1119, 1315);var(1121, 1313);var(1126, 1311);var(1131, 1308);var(1134, 1308);var(1141, 1306);var(1143, 1304);var(1144, 1304);var(1149, 1302);var(1150, 1301);var(1156, 1297);var(1156, 1297);var(1161, 1295);var(1162, 1291);var(1164, 1288);var(1164, 1287);var(1163, 1284);var(1156, 1283);var(1150, 1281);var(1141, 1279);var(1127, 1279);var(1126, 1279);var(1117, 1279);var(1109, 1279);var(1104, 1279);var(1100, 1279);var(1095, 1279);var(1095, 1281);var(1095, 1283);var(1095, 1285);var(1098, 1288);
    end

        cGLASSBACK
        fan
        var(1112, 1290);var(1104, 1272);var(1109, 1272);var(1114, 1274);var(1118, 1274);var(1124, 1274);var(1129, 1274);var(1132, 1276);var(1136, 1276);var(1141, 1276);var(1143, 1275);var(1145, 1275);var(1150, 1276);var(1154, 1276);var(1157, 1278);var(1160, 1279);var(1161, 1281);var(1163, 1282);var(1163, 1283);var(1160, 1286);var(1159, 1288);var(1155, 1291);var(1150, 1292);var(1147, 1295);var(1144, 1296);var(1138, 1296);var(1130, 1298);var(1122, 1300);var(1112, 1304);var(1103, 1304);var(1102, 1304);var(1100, 1304);var(1099, 1302);var(1099, 1302);var(1098, 1299);var(1097, 1295);var(1096, 1293);var(1096, 1291);var(1096, 1289);var(1096, 1284);var(1098, 1282);var(1099, 1278);var(1101, 1276);var(1103, 1272);var(1106, 1271);
    end
        cGLASSFRONT
        fan
        var(1111, 1289);var(1105, 1276);var(1108, 1276);var(1112, 1276);var(1115, 1276);var(1119, 1277);var(1126, 1278);var(1129, 1280);var(1133, 1284);var(1132, 1286);var(1131, 1288);var(1130, 1289);var(1127, 1293);var(1126, 1295);var(1122, 1299);var(1120, 1299);var(1113, 1300);var(1107, 1302);var(1105, 1302);var(1102, 1300);var(1101, 1299);var(1101, 1290);var(1101, 1285);var(1101, 1280);var(1105, 1276);
    end

        //frontpanel
        cGRAY
        fan
        var(1268, 1298);var(1227, 1300);var(1236, 1296);var(1246, 1293);var(1256, 1292);var(1262, 1288);var(1274, 1285);var(1282, 1285);var(1298, 1283);var(1315, 1280);var(1327, 1277);var(1334, 1277);var(1344, 1276);var(1349, 1275);var(1352, 1309);var(1350, 1311);var(1345, 1316);var(1343, 1317);var(1334, 1320);var(1327, 1323);var(1319, 1323);var(1310, 1321);var(1305, 1320);var(1302, 1318);var(1288, 1317);var(1274, 1313);var(1270, 1313);var(1266, 1313);var(1262, 1318);var(1259, 1320);var(1251, 1324);var(1244, 1329);var(1236, 1331);var(1236, 1331);var(1235, 1331);var(1229, 1330);var(1229, 1323);var(1226, 1318);var(1226, 1312);var(1223, 1303);var(1226, 1301);
    end
        fan
        var(1148, 1335);var(1106, 1341);var(1112, 1340);var(1118, 1339);var(1125, 1336);var(1128, 1335);var(1133, 1333);var(1145, 1331);var(1153, 1328);var(1159, 1327);var(1164, 1325);var(1171, 1323);var(1186, 1321);var(1199, 1316);var(1209, 1314);var(1218, 1312);var(1221, 1310);var(1222, 1321);var(1222, 1321);var(1212, 1323);var(1207, 1326);var(1200, 1329);var(1181, 1334);var(1176, 1335);var(1160, 1337);var(1153, 1340);var(1151, 1341);var(1139, 1347);var(1137, 1347);var(1131, 1350);var(1122, 1356);var(1114, 1360);var(1108, 1364);var(1107, 1364);var(1101, 1365);var(1100, 1366);var(1100, 1353);var(1100, 1345);var(1100, 1341);
    end
        fan
        var(1095, 1350);var(1085, 1344);var(1089, 1341);var(1092, 1338);var(1095, 1335);var(1098, 1333);var(1101, 1338);var(1103, 1347);var(1108, 1356);var(1110, 1361);var(1112, 1365);var(1107, 1366);var(1103, 1367);var(1100, 1367);var(1098, 1367);var(1095, 1364);var(1092, 1359);var(1089, 1355);var(1087, 1350);var(1085, 1343);
    end
        fan
        var(1422, 1286);var(1351, 1287);var(1359, 1286);var(1367, 1287);var(1376, 1285);var(1382, 1282);var(1393, 1282);var(1400, 1279);var(1406, 1277);var(1416, 1277);var(1422, 1276);var(1429, 1275);var(1438, 1275);var(1443, 1273);var(1448, 1272);var(1462, 1272);var(1466, 1271);var(1471, 1271);var(1476, 1271);var(1477, 1274);var(1475, 1278);var(1471, 1283);var(1467, 1286);var(1460, 1288);var(1453, 1290);var(1444, 1293);var(1440, 1293);var(1431, 1295);var(1426, 1295);var(1413, 1295);var(1402, 1296);var(1393, 1296);var(1385, 1300);var(1382, 1300);var(1369, 1300);var(1365, 1300);var(1356, 1304);var(1354, 1306);var(1351, 1306);var(1350, 1301);var(1352, 1294);var(1349, 1289);
    end





        //wheel - right
        cDARKGRAY
        fan
        var(1450, 1302);var(1425, 1292);var(1428, 1300);var(1429, 1304);var(1429, 1311);var(1429, 1312);var(1424, 1322);var(1425, 1322);var(1431, 1322);var(1435, 1320);var(1438, 1320);var(1452, 1319);var(1454, 1319);var(1462, 1317);var(1468, 1315);var(1472, 1312);var(1474, 1310);var(1476, 1304);var(1477, 1301);var(1478, 1298);var(1478, 1293);var(1479, 1288);var(1479, 1280);var(1476, 1275);var(1473, 1272);
    end
        cGRAY
        fan
        var(1448, 1302);var(1435, 1297);var(1438, 1295);var(1450, 1294);var(1456, 1294);var(1462, 1294);var(1466, 1296);var(1467, 1305);var(1469, 1310);var(1464, 1311);var(1456, 1313);var(1450, 1314);var(1446, 1316);var(1443, 1316);var(1439, 1316);var(1439, 1316);var(1438, 1308);var(1436, 1302);var(1435, 1296);
    end



        //destroyed
        cBLACK
        fan
        var(1278, 1159);var(1267, 1151);var(1263, 1153);var(1259, 1157);var(1257, 1160);var(1253, 1165);var(1251, 1166);var(1249, 1169);var(1249, 1172);var(1248, 1173);var(1250, 1177);var(1252, 1178);var(1255, 1178);var(1259, 1178);var(1262, 1176);var(1267, 1176);var(1270, 1177);var(1276, 1174);var(1280, 1172);var(1284, 1170);var(1289, 1167);var(1292, 1165);var(1298, 1164);var(1302, 1160);var(1305, 1158);var(1303, 1156);var(1297, 1152);var(1292, 1151);var(1284, 1149);var(1276, 1148);var(1269, 1150);
    end
        fan
        var(1348, 1160);var(1276, 1147);var(1285, 1145);var(1296, 1145);var(1306, 1144);var(1315, 1142);var(1327, 1141);var(1336, 1140);var(1351, 1139);var(1361, 1137);var(1369, 1136);var(1377, 1136);var(1383, 1138);var(1388, 1142);var(1406, 1173);var(1406, 1176);var(1406, 1176);var(1403, 1178);var(1400, 1178);var(1392, 1180);var(1367, 1187);var(1360, 1187);var(1352, 1190);var(1343, 1191);var(1338, 1193);var(1331, 1193);var(1323, 1195);var(1317, 1196);var(1315, 1193);var(1310, 1191);var(1306, 1191);var(1302, 1191);var(1300, 1191);var(1296, 1191);var(1294, 1191);var(1293, 1189);var(1293, 1189);var(1292, 1186);var(1289, 1182);var(1289, 1181);var(1284, 1175);var(1286, 1175);var(1292, 1171);var(1291, 1170);var(1290, 1169);var(1287, 1169);var(1287, 1165);var(1283, 1158);var(1282, 1151);var(1286, 1144);
    end


        //outlines
        cBLACK
        strip
        var(1142, 1182);var(1146, 1180);var(1152, 1178);var(1160, 1176);var(1166, 1174);var(1176, 1172);var(1184, 1169);var(1192, 1169);var(1201, 1165);var(1214, 1163);var(1225, 1160);var(1235, 1157);var(1245, 1156);var(1252, 1153);var(1257, 1151);var(1263, 1150);var(1276, 1148);var(1285, 1146);var(1293, 1145);var(1306, 1143);var(1321, 1140);var(1352, 1137);var(1380, 1134);var(1405, 1171);var(1405, 1175);var(1403, 1177);var(1400, 1179);var(1398, 1181);var(1391, 1181);var(1380, 1185);var(1371, 1188);var(1365, 1190);var(1357, 1192);var(1348, 1194);var(1337, 1196);var(1331, 1197);var(1324, 1196);var(1319, 1197);var(1315, 1198);var(1305, 1200);var(1302, 1202);var(1296, 1202);var(1289, 1204);var(1281, 1206);var(1270, 1208);var(1260, 1208);var(1246, 1209);var(1228, 1212);var(1214, 1213);var(1201, 1216);var(1194, 1218);var(1185, 1220);var(1176, 1221);var(1167, 1223);var(1164, 1223);var(1161, 1225);var(1153, 1227);var(1150, 1227);var(1146, 1228);var(1143, 1228);var(1140, 1228);var(1138, 1228);var(1138, 1228);var(1136, 1227);var(1134, 1226);var(1134, 1222);var(1131, 1218);var(1132, 1215);var(1133, 1209);var(1136, 1204);var(1139, 1197);var(1140, 1193);var(1142, 1188);var(1143, 1185);var(1143, 1180);
    end
        strip
        var(1197, 1277);var(1211, 1274);var(1225, 1270);var(1241, 1265);var(1264, 1260);var(1284, 1253);var(1305, 1251);var(1358, 1242);
    end
        strip
        var(1160, 1253);var(1165, 1249);var(1169, 1245);var(1174, 1242);var(1181, 1239);var(1186, 1235);var(1194, 1231);var(1195, 1231);var(1193, 1234);var(1187, 1237);var(1180, 1243);var(1175, 1246);var(1171, 1248);var(1162, 1252);var(1162, 1255);var(1167, 1252);var(1170, 1249);var(1173, 1246);var(1177, 1244);var(1179, 1241);var(1185, 1237);var(1189, 1234);var(1191, 1231);
    end
        strip
        var(1193, 1249);var(1175, 1269);
    end
        strip
        var(1193, 1249);var(1175, 1269);
    end
        strip
        var(1177, 1274);var(1273, 1247);var(1285, 1245);var(1295, 1242);var(1320, 1234);
    end
        fan
        var(1338, 1229);var(1294, 1243);var(1303, 1239);var(1307, 1238);var(1311, 1235);var(1311, 1233);var(1314, 1231);var(1316, 1227);var(1316, 1226);var(1316, 1225);var(1315, 1222);var(1313, 1220);var(1344, 1212);var(1348, 1217);var(1351, 1220);var(1353, 1225);var(1354, 1227);var(1354, 1230);var(1354, 1231);var(1351, 1233);var(1350, 1233);var(1307, 1243);var(1298, 1242);var(1303, 1238);var(1308, 1235);
    end
        fan
        var(1320, 1207);var(1314, 1221);var(1312, 1219);var(1310, 1218);var(1308, 1217);var(1305, 1215);var(1302, 1213);var(1300, 1211);var(1296, 1209);var(1290, 1205);var(1288, 1204);var(1301, 1201);var(1307, 1200);var(1312, 1200);var(1319, 1198);var(1321, 1196);var(1327, 1194);var(1331, 1196);var(1336, 1202);var(1340, 1207);var(1342, 1211);var(1343, 1212);var(1344, 1215);var(1337, 1220);var(1330, 1222);var(1322, 1223);var(1320, 1223);var(1313, 1220);
    end
        fan
        var(1444, 1262);var(1406, 1274);var(1404, 1274);var(1404, 1273);var(1403, 1271);var(1405, 1268);var(1408, 1265);var(1408, 1261);var(1410, 1255);var(1412, 1251);var(1413, 1250);var(1414, 1249);var(1418, 1245);var(1419, 1245);var(1419, 1245);var(1422, 1245);var(1422, 1243);var(1422, 1238);var(1426, 1237);var(1428, 1236);var(1429, 1236);var(1433, 1236);var(1435, 1234);var(1441, 1227);var(1444, 1225);var(1446, 1224);var(1454, 1229);var(1461, 1235);var(1466, 1250);var(1467, 1259);var(1469, 1270);var(1464, 1275);var(1454, 1276);var(1435, 1276);var(1424, 1277);var(1414, 1278);var(1412, 1280);var(1408, 1279);var(1405, 1277);
    end
        fan
        var(1194, 1314);var(1159, 1319);var(1166, 1317);var(1178, 1315);var(1191, 1312);var(1201, 1309);var(1204, 1305);var(1208, 1303);var(1210, 1302);var(1211, 1302);var(1215, 1302);var(1220, 1305);var(1220, 1305);var(1220, 1307);var(1220, 1307);var(1218, 1308);var(1217, 1309);var(1214, 1309);var(1213, 1309);var(1208, 1311);var(1204, 1313);var(1184, 1321);var(1166, 1323);var(1157, 1324);var(1160, 1320);var(1165, 1318);var(1202, 1338);var(1183, 1335);var(1191, 1332);var(1208, 1328);var(1223, 1322);var(1229, 1329);var(1231, 1335);var(1226, 1340);var(1195, 1349);var(1185, 1349);var(1177, 1356);var(1170, 1359);var(1166, 1354);var(1170, 1348);var(1172, 1340);var(1172, 1338);var(1185, 1335);var(1202, 1328);
    end


        fan
        var(1163, 1340);var(1130, 1352);var(1140, 1347);var(1153, 1342);var(1159, 1340);var(1165, 1340);var(1171, 1337);var(1185, 1334);var(1183, 1340);var(1174, 1341);var(1160, 1345);var(1148, 1348);var(1139, 1349);var(1131, 1351);
    end



        fan
        var(1126, 1332);var(1102, 1335);var(1109, 1334);var(1115, 1331);var(1122, 1327);var(1126, 1324);var(1130, 1321);var(1137, 1320);var(1144, 1319);var(1149, 1320);var(1149, 1320);var(1157, 1320);var(1157, 1324);var(1153, 1327);var(1147, 1326);var(1142, 1329);var(1136, 1334);var(1119, 1343);var(1110, 1345);var(1102, 1347);var(1101, 1342);var(1100, 1339);var(1102, 1336);
    end
        fan
        var(1194, 1314);var(1159, 1319);var(1166, 1317);var(1178, 1315);var(1191, 1312);var(1201, 1309);var(1204, 1305);var(1208, 1303);var(1210, 1302);var(1211, 1302);var(1215, 1302);var(1220, 1305);var(1220, 1305);var(1220, 1307);var(1220, 1307);var(1218, 1308);var(1217, 1309);var(1214, 1309);var(1213, 1309);var(1208, 1311);var(1204, 1313);var(1184, 1321);var(1166, 1323);var(1157, 1324);var(1160, 1320);var(1165, 1318);
    end

        fan
        var(1136, 1361);var(1099, 1371);var(1110, 1368);var(1117, 1363);var(1125, 1360);var(1136, 1358);var(1150, 1357);var(1159, 1354);var(1164, 1352);var(1166, 1357);var(1167, 1360);var(1163, 1362);var(1154, 1365);var(1147, 1367);var(1134, 1370);var(1129, 1372);var(1121, 1377);var(1121, 1377);var(1115, 1380);var(1108, 1382);var(1102, 1383);var(1100, 1383);var(1100, 1375);
    end
        fan
        var(1095, 1370);var(1083, 1344);var(1097, 1389);var(1105, 1381);var(1102, 1366);var(1099, 1369);var(1098, 1369);var(1094, 1367);var(1093, 1360);var(1090, 1352);var(1088, 1346);var(1086, 1343);
    end

        strip
        var(1382, 1219);var(1382, 1219);var(1388, 1215);var(1390, 1213);var(1391, 1211);var(1397, 1206);var(1399, 1204);var(1402, 1202);var(1406, 1200);var(1410, 1199);var(1411, 1197);var(1422, 1191);var(1422, 1191);
    end
        strip
        var(1309, 1262);var(1310, 1262);var(1312, 1260);var(1318, 1253);var(1319, 1253);var(1323, 1255);var(1326, 1255);var(1338, 1255);
    end



        //glow
        cGLASSFRONT
        fan
        var(1130, 1254);var(1128, 1237);var(1129, 1263);var(1111, 1265);var(1116, 1256);var(1127, 1242);var(1130, 1240);
    end
        fan
        var(1225, 1234);var(1198, 1240);var(1205, 1231);var(1207, 1227);var(1210, 1224);var(1214, 1223);var(1230, 1215);var(1232, 1215);var(1238, 1217);var(1243, 1227);var(1242, 1235);var(1235, 1246);var(1227, 1253);var(1223, 1259);var(1218, 1260);var(1207, 1265);var(1204, 1261);var(1200, 1255);var(1198, 1248);var(1196, 1242);var(1200, 1235);
    end
}
void drawCars()
{
    car1();
    car2();
}

void drawGround()
{




    cGROUND2
        fan
        var(293, 1537);var(68, 1530);var(97, 1524);var(110, 1521);var(134, 1521);var(157, 1519);var(181, 1512);var(190, 1513);var(214, 1522);var(266, 1533);var(290, 1527);var(293, 1527);var(343, 1527);var(412, 1527);var(493, 1522);var(493, 1554);var(455, 1570);var(361, 1564);var(293, 1567);var(211, 1570);var(167, 1563);var(134, 1545);var(116, 1540);var(91, 1528);var(83, 1519);var(83, 1519);
    end
        fan
        var(445, 1566);var(407, 1558);var(383, 1558);var(386, 1557);var(415, 1552);var(443, 1552);var(484, 1554);var(521, 1554);var(524, 1563);var(490, 1585);var(440, 1588);var(392, 1584);var(383, 1570);var(395, 1557);var(404, 1555);
    end
        fan
        var(148, 1690);var(1, 1634);var(84, 1650);var(145, 1653);var(269, 1642);var(300, 1641);var(344, 1645);var(369, 1641);var(375, 1641);var(357, 1662);var(351, 1672);var(291, 1706);var(228, 1718);var(189, 1729);var(149, 1744);var(80, 1766);var(61, 1772);var(15, 1772);var(0, 1774);var(4, 1648);var(5, 1640);var(17, 1645);
    end
        fan
        var(468, 1641);var(435, 1606);var(465, 1610);var(491, 1614);var(512, 1616);var(533, 1617);var(572, 1617);var(581, 1616);var(543, 1654);var(501, 1670);var(456, 1680);var(421, 1680);var(397, 1648);var(407, 1621);var(420, 1625);var(432, 1625);var(439, 1621);var(428, 1606);var(439, 1606);
    end
        fan
        var(801, 1513);var(552, 1509);var(579, 1501);var(629, 1500);var(693, 1500);var(719, 1494);var(767, 1493);var(792, 1493);var(824, 1492);var(876, 1492);var(907, 1493);var(925, 1494);var(971, 1500);var(1015, 1509);var(1032, 1524);var(1069, 1534);var(1092, 1538);var(1064, 1548);var(1013, 1545);var(968, 1541);var(920, 1533);var(900, 1533);var(841, 1532);var(799, 1532);var(775, 1533);var(717, 1534);var(680, 1530);var(633, 1529);var(597, 1529);var(580, 1528);var(563, 1512);var(556, 1501);
    end

        cGROUND1
        fan
        var(932, 1680);var(764, 1657);var(748, 1632);var(907, 1640);var(1048, 1648);var(1148, 1650);var(1299, 1661);var(1308, 1661);var(1091, 1682);var(1077, 1692);var(993, 1714);var(888, 1724);var(815, 1737);var(789, 1746);var(759, 1741);var(720, 1688);var(664, 1653);var(632, 1608);var(692, 1606);var(716, 1614);var(793, 1650);var(877, 1654);var(903, 1650);
    end
        cGROUND3
        fan
        var(736, 1421);var(736, 1421);var(667, 1429);var(695, 1414);var(725, 1413);var(747, 1405);var(749, 1402);var(789, 1400);var(805, 1400);var(856, 1398);var(859, 1396);var(849, 1410);var(828, 1420);var(789, 1425);var(765, 1430);var(749, 1437);var(703, 1446);var(677, 1450);var(659, 1450);var(656, 1449);var(656, 1440);var(672, 1422);
    end
        cGROUND4
        fan
        var(961, 1361);var(852, 1396);var(831, 1361);var(784, 1341);var(821, 1337);var(847, 1336);var(869, 1333);var(881, 1329);var(896, 1329);var(899, 1329);var(916, 1333);var(928, 1336);var(959, 1336);var(959, 1336);var(981, 1336);var(985, 1336);var(1013, 1342);var(1036, 1344);var(1055, 1345);var(1081, 1336);var(1085, 1336);var(1095, 1337);var(1099, 1346);var(1104, 1364);var(1113, 1384);var(1107, 1392);var(1097, 1401);var(1088, 1405);var(1073, 1409);var(1056, 1409);var(1001, 1406);var(988, 1406);var(935, 1406);var(923, 1408);var(913, 1408);var(884, 1406);var(857, 1404);var(853, 1402);var(839, 1384);var(832, 1373);var(832, 1365);
    end
        cGROUND4
        fan
        var(1299, 1361);var(1109, 1373);var(1151, 1368);var(1165, 1358);var(1181, 1354);var(1193, 1349);var(1215, 1342);var(1231, 1334);var(1243, 1330);var(1252, 1324);var(1257, 1317);var(1264, 1313);var(1281, 1313);var(1288, 1314);var(1300, 1324);var(1311, 1325);var(1319, 1328);var(1331, 1328);var(1348, 1325);var(1352, 1318);var(1368, 1309);var(1383, 1316);var(1389, 1320);var(1396, 1324);var(1416, 1329);var(1421, 1329);var(1425, 1330);var(1437, 1333);var(1452, 1324);var(1457, 1317);var(1467, 1318);var(1487, 1330);var(1493, 1332);var(1499, 1329);var(1527, 1322);var(1564, 1310);var(1595, 1304);var(1637, 1304);var(1649, 1302);var(1679, 1309);var(1675, 1321);var(1660, 1329);var(1636, 1341);var(1619, 1349);var(1603, 1358);var(1589, 1366);var(1576, 1373);var(1540, 1381);var(1508, 1382);var(1476, 1382);var(1461, 1384);var(1421, 1384);var(1380, 1386);var(1308, 1394);var(1269, 1396);var(1251, 1400);var(1215, 1401);var(1172, 1402);var(1164, 1402);var(1123, 1400);var(1123, 1394);var(1133, 1374);var(1141, 1369);var(1159, 1362);
    end


        cGROUND2
        fan
        var(1032, 1772);var(968, 1797);var(969, 1785);var(975, 1770);var(981, 1756);var(1003, 1740);var(1012, 1725);var(1020, 1725);var(1043, 1745);var(1051, 1749);var(1068, 1760);var(1076, 1764);var(1095, 1765);var(1099, 1765);var(1109, 1761);var(1111, 1761);var(1116, 1769);var(1119, 1780);var(1125, 1800);var(1121, 1809);var(1103, 1821);var(1068, 1828);var(971, 1828);var(969, 1821);var(972, 1794);
    end
        cGROUND4
        fan
        var(1594, 1317);var(1390, 1341);var(1478, 1332);var(1516, 1332);var(1543, 1323);var(1613, 1304);var(1679, 1289);
    end
        cGROUND3
        fan
        var(1513, 1277);var(1234, 1325);var(1299, 1259);var(1318, 1251);var(1354, 1239);var(1371, 1235);var(1398, 1232);var(1420, 1223);var(1436, 1211);var(1449, 1200);var(1463, 1184);var(1471, 1175);var(1478, 1169);var(1478, 1164);var(1490, 1154);var(1505, 1143);var(1510, 1139);var(1520, 1135);var(1524, 1138);var(1530, 1143);var(1552, 1154);var(1576, 1158);var(1645, 1162);var(1715, 1165);var(1745, 1209);var(1754, 1228);var(1747, 1247);var(1717, 1257);var(1698, 1275);var(1674, 1284);var(1658, 1291);var(1613, 1299);var(1585, 1305);var(1562, 1307);var(1529, 1319);var(1490, 1325);var(1440, 1326);var(1415, 1328);var(1360, 1331);var(1330, 1333);var(1302, 1343);var(1295, 1349);var(1293, 1349);var(1262, 1339);var(1277, 1321);var(1332, 1287);var(1362, 1272);var(1395, 1248);var(1418, 1230);var(1434, 1212);var(1445, 1193);var(1455, 1185);var(1465, 1176);var(1471, 1172);
    end
        cGROUND4
        fan
        var(1947, 1505);var(1822, 1492);var(1847, 1456);var(1871, 1420);var(1890, 1387);var(1891, 1382);var(1898, 1354);var(1898, 1352);var(1901, 1329);var(1921, 1311);var(1953, 1299);var(1980, 1295);var(1988, 1295);var(1997, 1301);var(2000, 1302);var(2001, 1309);var(2000, 1602);var(1945, 1587);var(1776, 1586);var(1778, 1566);var(1791, 1540);var(1820, 1496);var(1825, 1491);var(1828, 1486);
    end

        cGROUND2
        fan
        var(1222, 1449);var(1194, 1451);var(1209, 1445);var(1220, 1443);var(1243, 1449);var(1250, 1451);var(1249, 1451);var(1225, 1453);var(1209, 1456);var(1201, 1455);var(1197, 1448);
    end
        fan
        var(1134, 1482);var(996, 1481);var(1006, 1481);var(1018, 1480);var(1021, 1480);var(1031, 1480);var(1033, 1480);var(1057, 1478);var(1072, 1475);var(1089, 1474);var(1104, 1474);var(1132, 1474);var(1144, 1474);var(1155, 1474);var(1164, 1471);var(1187, 1470);var(1213, 1470);var(1243, 1475);var(1265, 1477);var(1269, 1477);var(1279, 1481);var(1279, 1481);var(1285, 1483);var(1294, 1487);var(1300, 1489);var(1273, 1491);var(1253, 1491);var(1227, 1489);var(1203, 1489);var(1165, 1489);var(1137, 1489);var(1115, 1488);var(1065, 1488);var(1029, 1488);var(975, 1487);var(981, 1484);var(1005, 1484);
    end
        fan
        var(1355, 1459);var(1443, 1439);var(1471, 1432);var(1531, 1417);var(1539, 1417);var(1535, 1428);var(1517, 1437);var(1508, 1437);var(1503, 1445);var(1491, 1446);var(1493, 1450);var(1501, 1455);var(1511, 1456);var(1509, 1462);var(1495, 1465);var(1459, 1468);var(1441, 1465);var(1491, 1461);var(1467, 1463);var(1441, 1464);var(1401, 1460);var(1381, 1460);var(1353, 1464);var(1383, 1459);var(1441, 1446);
    end

        //outline

        cBLACK
        strip
        var(1438, 1207);var(1441, 1199);var(1444, 1195);var(1449, 1191);var(1454, 1187);var(1456, 1183);var(1463, 1186);var(1464, 1175);var(1469, 1173);var(1471, 1174);var(1473, 1174);var(1476, 1170);var(1479, 1167);var(1479, 1165);var(1479, 1165);var(1487, 1161);var(1489, 1159);var(1490, 1158);var(1491, 1155);var(1495, 1155);var(1500, 1151);var(1501, 1150);var(1503, 1148);var(1505, 1145);var(1509, 1142);var(1512, 1139);var(1513, 1139);var(1517, 1137);var(1523, 1138);var(1526, 1139);var(1529, 1141);var(1533, 1145);var(1544, 1151);var(1545, 1153);var(1558, 1157);
    end
        fan
        var(1504, 1177);var(1477, 1187);var(1485, 1179);var(1485, 1177);var(1487, 1176);var(1497, 1175);var(1502, 1167);var(1506, 1161);var(1509, 1159);var(1517, 1159);var(1521, 1156);var(1527, 1166);var(1523, 1170);var(1515, 1178);var(1509, 1181);var(1500, 1187);var(1490, 1189);var(1481, 1189);var(1473, 1192);var(1477, 1191);
    end
        strip
        var(1465, 1214);var(1467, 1213);var(1470, 1207);var(1473, 1206);var(1475, 1204);var(1477, 1204);var(1478, 1204);var(1479, 1206);var(1479, 1207);var(1479, 1209);var(1479, 1209);var(1481, 1209);var(1482, 1208);var(1485, 1205);var(1487, 1203);var(1489, 1201);var(1490, 1199);var(1492, 1197);var(1493, 1195);var(1496, 1194);var(1497, 1195);var(1499, 1196);var(1501, 1197);var(1505, 1199);var(1508, 1199);var(1508, 1199);var(1507, 1197);var(1505, 1195);var(1502, 1193);var(1498, 1190);var(1497, 1190);var(1493, 1191);var(1492, 1191);var(1489, 1196);var(1489, 1195);var(1491, 1194);var(1496, 1194);var(1500, 1195);var(1503, 1197);var(1505, 1199);var(1505, 1199);var(1503, 1194);var(1501, 1193);var(1496, 1191);var(1491, 1196);var(1487, 1199);var(1483, 1201);var(1481, 1207);var(1480, 1208);var(1479, 1208);var(1484, 1203);var(1487, 1202);var(1488, 1199);
    end
        strip
        var(1469, 1235);var(1474, 1237);var(1477, 1237);var(1481, 1237);var(1486, 1237);var(1487, 1237);var(1489, 1237);var(1492, 1238);var(1499, 1239);var(1501, 1241);var(1507, 1246);var(1507, 1246);var(1505, 1249);var(1501, 1251);var(1496, 1251);var(1493, 1250);var(1492, 1250);var(1487, 1251);var(1481, 1253);var(1479, 1254);var(1475, 1255);var(1472, 1255);
    end
        strip
        var(1511, 1279);var(1513, 1280);var(1514, 1280);var(1522, 1275);var(1523, 1275);var(1527, 1275);var(1529, 1273);var(1531, 1271);var(1533, 1269);var(1535, 1267);var(1536, 1266);var(1536, 1265);var(1536, 1262);var(1536, 1261);var(1537, 1257);var(1537, 1253);var(1539, 1253);var(1541, 1253);var(1543, 1253);var(1544, 1253);
    end
        strip
        var(1555, 1271);var(1560, 1271);var(1563, 1267);var(1565, 1263);var(1571, 1257);var(1573, 1255);var(1575, 1255);var(1583, 1255);
    end
        strip
        var(1549, 1283);var(1540, 1291);var(1527, 1300);var(1523, 1304);var(1517, 1313);var(1529, 1309);var(1533, 1309);var(1538, 1307);var(1540, 1306);var(1547, 1304);var(1539, 1316);var(1551, 1311);var(1559, 1308);var(1593, 1305);
    end
        strip
        var(1578, 1294);var(1587, 1290);var(1590, 1286);var(1593, 1285);var(1596, 1283);var(1598, 1276);var(1599, 1271);var(1601, 1270);var(1608, 1270);var(1612, 1270);
    end
        strip
        var(1619, 1291);var(1619, 1292);var(1617, 1293);var(1613, 1294);var(1614, 1296);var(1617, 1297);var(1622, 1297);var(1623, 1297);var(1624, 1296);var(1624, 1295);var(1621, 1294);var(1618, 1293);
    end
        strip
        var(1463, 1305);var(1467, 1312);var(1471, 1315);var(1474, 1319);var(1478, 1321);var(1486, 1322);var(1498, 1331);var(1503, 1335);
    end
        strip
        var(1925, 1365);var(1930, 1361);var(1930, 1360);var(1931, 1358);var(1936, 1353);var(1939, 1350);var(1950, 1350);var(1959, 1351);var(1968, 1354);
    end
        strip
        var(1921, 1418);var(1931, 1422);var(1935, 1421);var(1937, 1421);var(1939, 1421);var(1940, 1420);var(1944, 1415);var(1945, 1412);var(1945, 1412);var(1957, 1414);var(1957, 1414);var(1951, 1410);var(1949, 1411);var(1957, 1408);var(1958, 1408);var(1968, 1402);var(1965, 1400);
    end
        fan
        var(1102, 1426);var(1045, 1449);var(1051, 1446);var(1053, 1444);var(1057, 1441);var(1059, 1437);var(1061, 1436);var(1065, 1433);var(1069, 1432);var(1075, 1431);var(1077, 1429);var(1081, 1427);var(1086, 1427);var(1089, 1425);var(1091, 1424);var(1093, 1424);var(1093, 1424);var(1095, 1419);var(1099, 1415);var(1103, 1412);var(1108, 1409);var(1115, 1407);var(1121, 1404);var(1123, 1401);var(1127, 1400);var(1133, 1398);var(1143, 1393);var(1146, 1393);var(1153, 1403);var(1153, 1403);var(1148, 1414);var(1140, 1419);var(1134, 1423);var(1132, 1424);var(1129, 1426);var(1125, 1429);var(1122, 1430);var(1119, 1432);var(1119, 1432);var(1117, 1434);var(1117, 1435);var(1117, 1436);var(1119, 1437);var(1119, 1441);var(1117, 1444);var(1114, 1444);var(1111, 1443);var(1105, 1443);var(1101, 1443);var(1096, 1443);var(1091, 1445);var(1089, 1447);var(1087, 1447);var(1081, 1446);var(1077, 1445);var(1071, 1445);var(1067, 1450);var(1063, 1453);var(1058, 1453);var(1057, 1453);var(1051, 1453);var(1047, 1453);var(1043, 1450);var(1047, 1450);
    end
        fan
        var(1162, 1419);var(1143, 1417);var(1141, 1411);var(1146, 1407);var(1149, 1403);var(1153, 1405);var(1157, 1407);var(1159, 1409);var(1166, 1413);var(1174, 1418);var(1176, 1419);var(1176, 1420);var(1175, 1423);var(1175, 1424);var(1172, 1425);var(1168, 1425);var(1167, 1424);var(1163, 1423);var(1160, 1422);var(1157, 1421);var(1153, 1419);var(1148, 1417);var(1145, 1414);
    end
        fan
        var(1185, 1430);var(1176, 1421);var(1181, 1424);var(1191, 1429);var(1196, 1430);var(1201, 1433);var(1196, 1433);var(1193, 1433);var(1190, 1433);var(1188, 1433);var(1185, 1433);var(1181, 1433);var(1178, 1433);var(1175, 1431);var(1175, 1429);var(1174, 1428);var(1172, 1424);var(1172, 1424);
    end
        strip
        var(1199, 1434);var(1199, 1432);var(1205, 1433);var(1205, 1433);var(1215, 1427);var(1215, 1427);var(1223, 1427);var(1228, 1426);var(1237, 1425);var(1239, 1427);var(1242, 1429);var(1247, 1433);var(1253, 1435);
    end
        strip
        var(1295, 1395);var(1307, 1399);var(1315, 1399);var(1325, 1399);var(1334, 1399);var(1339, 1397);var(1347, 1395);var(1354, 1394);var(1355, 1392);var(1357, 1390);var(1366, 1389);var(1375, 1387);var(1383, 1384);var(1389, 1383);var(1392, 1381);var(1399, 1381);var(1407, 1381);var(1411, 1379);var(1419, 1377);var(1429, 1379);var(1440, 1379);var(1458, 1381);var(1469, 1381);var(1484, 1382);var(1493, 1382);var(1507, 1384);var(1516, 1384);var(1535, 1388);var(1551, 1384);var(1558, 1383);var(1565, 1381);var(1569, 1378);var(1575, 1377);var(1581, 1374);var(1587, 1369);
    end
        fan
        var(1213, 1381);var(1195, 1388);var(1191, 1386);var(1188, 1383);var(1184, 1380);var(1185, 1376);var(1188, 1377);var(1193, 1375);var(1201, 1372);var(1211, 1371);var(1217, 1371);var(1223, 1371);var(1230, 1370);var(1241, 1368);var(1245, 1367);var(1248, 1365);var(1253, 1364);var(1258, 1361);var(1261, 1361);var(1264, 1357);var(1268, 1357);var(1269, 1355);var(1269, 1359);var(1267, 1364);var(1266, 1367);var(1259, 1374);var(1252, 1378);var(1243, 1379);var(1234, 1383);var(1229, 1385);var(1227, 1385);var(1223, 1389);var(1220, 1389);var(1211, 1389);var(1201, 1389);var(1198, 1389);var(1196, 1389);
    end
        fan
        var(1279, 1351);var(1271, 1353);var(1273, 1349);var(1275, 1347);var(1277, 1346);var(1281, 1346);var(1283, 1348);var(1285, 1352);var(1285, 1353);var(1281, 1353);var(1277, 1355);var(1275, 1357);var(1271, 1361);var(1267, 1365);
    end
        fan
        var(1293, 1365);var(1291, 1367);var(1290, 1365);var(1285, 1362);var(1279, 1357);var(1277, 1354);var(1283, 1348);var(1287, 1350);var(1292, 1355);var(1296, 1358);var(1300, 1361);var(1300, 1359);var(1302, 1359);var(1306, 1365);var(1315, 1372);var(1310, 1370);var(1304, 1370);var(1301, 1369);var(1294, 1363);var(1289, 1359);var(1296, 1361);
    end
        fan
        var(1318, 1372);var(1307, 1368);var(1307, 1365);var(1313, 1365);var(1319, 1365);var(1325, 1367);var(1329, 1371);var(1339, 1377);var(1341, 1379);var(1329, 1376);var(1325, 1375);var(1321, 1375);var(1313, 1373);var(1307, 1369);var(1323, 1373);var(1326, 1376);
    end
        fan
        var(1347, 1360);var(1337, 1356);var(1337, 1355);var(1341, 1351);var(1344, 1348);var(1345, 1346);var(1348, 1345);var(1349, 1346);var(1350, 1352);var(1357, 1352);var(1362, 1352);var(1367, 1351);var(1377, 1348);var(1381, 1348);var(1387, 1348);var(1392, 1350);var(1397, 1350);var(1397, 1351);var(1391, 1356);var(1386, 1359);var(1381, 1361);var(1371, 1363);var(1364, 1365);var(1352, 1369);var(1341, 1369);var(1335, 1369);var(1321, 1371);var(1325, 1371);var(1334, 1364);var(1335, 1361);var(1342, 1357);var(1351, 1354);
    end
        fan
        var(1254, 1394);var(1231, 1395);var(1235, 1389);var(1243, 1386);var(1253, 1384);var(1267, 1379);var(1273, 1379);var(1273, 1379);var(1270, 1382);var(1268, 1387);var(1269, 1388);var(1269, 1393);var(1273, 1393);var(1278, 1393);var(1270, 1393);var(1265, 1395);var(1251, 1397);var(1249, 1397);var(1238, 1397);var(1232, 1397);var(1233, 1397);
    end
        fan
        var(1308, 1385);var(1297, 1391);var(1291, 1389);var(1285, 1384);var(1266, 1379);var(1269, 1379);var(1279, 1377);var(1297, 1372);var(1301, 1372);var(1311, 1374);var(1322, 1377);var(1329, 1381);var(1337, 1383);var(1340, 1383);var(1357, 1387);var(1359, 1388);var(1377, 1391);var(1376, 1391);var(1370, 1392);var(1365, 1393);var(1351, 1397);var(1336, 1398);var(1326, 1399);var(1314, 1399);var(1305, 1399);var(1297, 1396);var(1292, 1393);var(1289, 1388);
    end
        fan
        var(1308, 1385);var(1297, 1391);var(1291, 1389);var(1285, 1384);var(1266, 1379);var(1269, 1379);var(1279, 1377);var(1297, 1372);var(1301, 1372);var(1311, 1374);var(1322, 1377);var(1329, 1381);var(1337, 1383);var(1340, 1383);var(1357, 1387);var(1359, 1388);var(1377, 1391);var(1376, 1391);var(1370, 1392);var(1365, 1393);var(1351, 1397);var(1336, 1398);var(1326, 1399);var(1314, 1399);var(1305, 1399);var(1297, 1396);var(1292, 1393);var(1289, 1388);
    end
        fan
        var(1183, 1399);var(1158, 1407);var(1161, 1406);var(1166, 1402);var(1169, 1397);var(1173, 1393);var(1175, 1390);var(1175, 1389);var(1185, 1394);var(1193, 1399);var(1197, 1402);var(1207, 1404);var(1212, 1407);var(1207, 1409);var(1200, 1411);var(1191, 1412);var(1185, 1411);var(1179, 1407);var(1174, 1407);var(1164, 1413);var(1159, 1416);var(1163, 1409);var(1165, 1403);var(1171, 1399);
    end
        strip
        var(1382, 1317);var(1398, 1323);var(1402, 1324);var(1411, 1328);var(1413, 1329);var(1416, 1330);var(1427, 1332);var(1435, 1332);var(1445, 1332);var(1455, 1333);var(1457, 1333);var(1461, 1333);var(1463, 1333);var(1471, 1337);var(1473, 1336);var(1475, 1333);var(1477, 1331);var(1483, 1333);var(1489, 1336);var(1493, 1335);var(1499, 1330);var(1513, 1333);var(1516, 1333);var(1519, 1333);var(1529, 1329);var(1542, 1329);var(1546, 1324);var(1551, 1320);var(1568, 1319);var(1575, 1316);var(1580, 1313);var(1585, 1309);var(1598, 1309);var(1605, 1308);var(1613, 1309);var(1617, 1311);var(1618, 1308);var(1621, 1304);var(1632, 1300);var(1637, 1300);var(1643, 1297);var(1646, 1292);var(1651, 1289);var(1660, 1293);var(1665, 1296);
    end

        //rightbelow
        cGROUND4
        fan
        var(1869, 1491);var(1869, 1494);var(1869, 1495);var(1866, 1500);var(1861, 1506);var(1853, 1518);var(1846, 1526);var(1841, 1534);var(1838, 1550);var(1832, 1562);var(1834, 1580);var(1835, 1592);var(1844, 1604);var(1851, 1619);var(1857, 1626);var(1865, 1633);var(1874, 1641);var(1887, 1652);var(1905, 1654);var(1925, 1655);var(1929, 1655);var(1945, 1656);var(1951, 1656);var(1958, 1650);var(1968, 1642);var(1967, 1497);var(1949, 1505);var(1941, 1509);var(1927, 1513);var(1895, 1506);var(1887, 1507);var(1873, 1507);var(1877, 1487);var(1871, 1486);var(1869, 1492);
    end
        cGROUND1
        fan
        var(1717, 1743);var(1481, 1791);var(1502, 1784);var(1517, 1776);var(1537, 1765);var(1549, 1756);var(1561, 1746);var(1569, 1737);var(1591, 1721);var(1596, 1714);var(1620, 1702);var(1632, 1692);var(1648, 1679);var(1667, 1675);var(1703, 1674);var(1764, 1674);var(1802, 1664);var(1845, 1659);var(1859, 1658);var(1887, 1658);var(1885, 1649);var(1887, 1644);var(1891, 1640);var(1895, 1640);var(1899, 1642);var(1873, 1658);var(1866, 1660);var(1875, 1650);var(1886, 1640);var(1905, 1646);var(1917, 1652);var(1927, 1662);var(1930, 1663);var(1941, 1672);var(1944, 1682);var(1948, 1692);var(1951, 1702);var(1955, 1712);var(1960, 1740);var(1950, 1732);var(1939, 1726);var(1908, 1740);var(1903, 1752);var(1891, 1767);var(1864, 1779);var(1842, 1787);var(1786, 1792);var(1687, 1800);var(1639, 1802);var(1612, 1802);var(1576, 1802);var(1551, 1799);var(1536, 1788);var(1566, 1769);var(1616, 1754);var(1688, 1724);var(1713, 1718);var(1557, 1753);var(1569, 1738);var(1590, 1721);var(1623, 1714);var(1683, 1712);var(1715, 1705);var(1591, 1726);var(1607, 1700);var(1613, 1693);var(1643, 1686);var(1664, 1684);
    end

        cGROUND2
        fan
        var(1911, 1532);var(1831, 1578);var(1829, 1562);var(1843, 1547);var(1849, 1534);var(1860, 1515);var(1868, 1492);var(1876, 1470);var(1893, 1458);var(1913, 1446);var(1939, 1440);var(1967, 1438);var(1960, 1647);var(1948, 1654);var(1928, 1658);var(1899, 1658);var(1864, 1651);var(1850, 1626);var(1839, 1601);var(1837, 1588);var(1833, 1570);
    end

        //outline
        cBLACK
        strip
        var(1845, 1544);var(1849, 1534);var(1857, 1518);var(1865, 1505);var(1875, 1492);var(1881, 1481);var(1887, 1469);var(1878, 1466);var(1883, 1465);var(1891, 1458);var(1901, 1454);var(1906, 1448);var(1914, 1445);var(1923, 1442);var(1926, 1438);var(1937, 1435);var(1949, 1434);var(1955, 1434);var(1960, 1434);var(1963, 1434);var(1967, 1434);
    end

        //below



        cGROUND3
        fan
        var(1505, 1738);var(1513, 1742);var(1521, 1747);var(1526, 1750);var(1528, 1752);var(1538, 1760);var(1538, 1760);var(1546, 1768);var(1551, 1773);var(1392, 1714);var(1381, 1711);var(1377, 1710);var(1366, 1710);var(1360, 1708);var(1353, 1708);var(1342, 1706);var(1334, 1703);var(1328, 1702);var(1323, 1702);var(1320, 1700);var(1317, 1693);var(1315, 1683);var(1313, 1678);var(1321, 1672);var(1326, 1668);var(1333, 1668);var(1339, 1666);var(1343, 1666);var(1350, 1666);var(1373, 1666);var(1380, 1666);var(1393, 1666);var(1404, 1665);var(1413, 1664);var(1422, 1664);var(1426, 1660);var(1435, 1656);var(1442, 1654);var(1447, 1654);var(1463, 1654);var(1463, 1653);var(1478, 1637);var(1475, 1634);var(1465, 1634);var(1463, 1634);var(1458, 1631);var(1456, 1629);var(1450, 1628);var(1443, 1624);var(1441, 1621);var(1435, 1614);var(1428, 1606);var(1426, 1604);var(1418, 1603);var(1409, 1605);var(1405, 1609);var(1399, 1613);var(1399, 1616);var(1397, 1624);var(1396, 1626);var(1397, 1636);var(1397, 1638);var(1403, 1644);var(1403, 1646);var(1404, 1653);var(1405, 1654);var(1408, 1658);var(1411, 1660);var(1412, 1661);var(1418, 1663);var(1420, 1663);
    end
        cGROUND1
        fan
        var(1647, 1747);var(1226, 1795);var(1239, 1788);var(1249, 1786);var(1257, 1785);var(1271, 1782);var(1281, 1778);var(1294, 1775);var(1301, 1770);var(1304, 1768);var(1310, 1766);var(1317, 1764);var(1323, 1760);var(1328, 1756);var(1331, 1754);var(1337, 1751);var(1340, 1750);var(1345, 1745);var(1349, 1744);var(1351, 1742);var(1353, 1740);var(1357, 1737);var(1363, 1735);var(1366, 1732);var(1375, 1727);var(1376, 1724);var(1381, 1720);var(1385, 1717);var(1392, 1714);var(1395, 1710);var(1398, 1706);var(1404, 1702);var(1408, 1698);var(1413, 1694);var(1417, 1692);var(1421, 1688);var(1428, 1685);var(1428, 1684);var(1429, 1684);var(1441, 1680);var(1445, 1675);var(1453, 1666);var(1455, 1660);var(1461, 1655);var(1468, 1650);var(1473, 1646);var(1483, 1640);var(1489, 1636);var(1493, 1633);var(1496, 1630);var(1503, 1624);var(1512, 1620);var(1529, 1618);var(1545, 1614);var(1549, 1612);var(1558, 1609);var(1574, 1603);var(1569, 1602);var(1579, 1599);var(1589, 1596);var(1513, 1620);var(1516, 1617);var(1522, 1614);var(1530, 1610);var(1538, 1608);var(1542, 1605);var(1547, 1603);var(1552, 1602);var(1553, 1601);var(1557, 1599);var(1564, 1596);var(1568, 1594);var(1575, 1594);var(1585, 1594);var(1605, 1594);var(1637, 1595);var(1701, 1605);var(1765, 1613);var(1843, 1624);var(1859, 1625);var(1860, 1635);var(1878, 1639);var(1883, 1639);var(1903, 1644);var(1913, 1648);var(1921, 1655);var(1931, 1660);var(1938, 1669);var(1941, 1678);var(1948, 1690);var(1951, 1698);var(1957, 1709);var(1960, 1716);var(1963, 1722);var(1967, 1731);var(1964, 1776);var(1965, 1779);var(1962, 1780);var(1961, 1780);var(1957, 1774);var(1955, 1772);var(1953, 1764);var(1948, 1754);var(1944, 1749);var(1941, 1745);var(1937, 1738);var(1932, 1754);var(1935, 1768);var(1935, 1780);var(1935, 1789);var(1933, 1797);var(1933, 1797);var(1928, 1801);var(1918, 1804);var(1904, 1804);var(1874, 1802);var(1870, 1801);var(1865, 1804);var(1807, 1811);var(1764, 1812);var(1739, 1810);var(1707, 1807);var(1657, 1810);var(1626, 1807);var(1607, 1804);var(1593, 1800);var(1574, 1798);var(1538, 1806);var(1522, 1808);var(1504, 1806);var(1461, 1808);var(1461, 1809);var(1413, 1809);var(1386, 1809);var(1338, 1804);var(1301, 1812);var(1297, 1814);var(1273, 1812);var(1257, 1812);var(1231, 1811);var(1220, 1808);var(1219, 1804);var(1220, 1798);var(1225, 1794);var(1219, 1812);var(1211, 1810);var(1204, 1807);var(1195, 1804);var(1195, 1804);var(1212, 1795);var(1239, 1792);var(1580, 1721);
    end
        cGROUND2
        fan
        var(1591, 1730);var(1331, 1784);var(1343, 1780);var(1356, 1771);var(1369, 1767);var(1384, 1757);var(1394, 1748);var(1401, 1742);var(1409, 1734);var(1415, 1727);var(1421, 1722);var(1415, 1717);var(1417, 1715);var(1431, 1709);var(1441, 1701);var(1464, 1687);var(1483, 1677);var(1500, 1664);var(1521, 1648);var(1531, 1642);var(1542, 1636);var(1554, 1624);var(1565, 1616);var(1573, 1614);var(1591, 1610);var(1607, 1612);var(1650, 1647);var(1677, 1662);var(1798, 1693);var(1823, 1700);var(1849, 1707);var(1867, 1732);var(1905, 1765);var(1896, 1771);var(1875, 1780);var(1838, 1781);var(1826, 1800);var(1818, 1808);var(1752, 1801);var(1711, 1801);var(1637, 1803);var(1586, 1804);var(1526, 1806);var(1478, 1809);var(1445, 1812);var(1417, 1814);var(1349, 1812);var(1349, 1812);var(1314, 1808);var(1329, 1796);var(1333, 1788);var(1337, 1787);
    end
        cGROUND3
        fan
        var(1433, 1786);var(1447, 1783);var(1463, 1770);var(1470, 1762);var(1475, 1756);var(1479, 1741);var(1489, 1722);var(1495, 1710);var(1502, 1694);var(1505, 1684);var(1513, 1672);var(1521, 1662);var(1527, 1656);var(1533, 1648);var(1542, 1635);var(1547, 1622);var(1553, 1615);var(1562, 1613);var(1575, 1613);var(1595, 1620);var(1625, 1629);var(1636, 1636);var(1651, 1651);var(1669, 1664);var(1690, 1678);var(1706, 1698);var(1713, 1710);var(1710, 1732);var(1699, 1763);var(1620, 1768);var(1581, 1782);var(1531, 1787);var(1479, 1788);var(1448, 1790);var(1419, 1790);
    end
        cGROUND4
        fan
        var(1717, 1743);var(1481, 1791);var(1502, 1784);var(1517, 1776);var(1537, 1765);var(1549, 1756);var(1561, 1746);var(1569, 1737);var(1591, 1721);var(1596, 1714);var(1620, 1702);var(1632, 1692);var(1648, 1679);var(1667, 1675);var(1703, 1674);var(1764, 1674);var(1802, 1664);var(1845, 1659);var(1859, 1658);var(1887, 1658);var(1885, 1649);var(1887, 1644);var(1891, 1640);var(1895, 1640);var(1899, 1642);var(1873, 1658);var(1866, 1660);var(1875, 1650);var(1886, 1640);var(1905, 1646);var(1917, 1652);var(1927, 1662);var(1930, 1663);var(1941, 1672);var(1944, 1682);var(1948, 1692);var(1951, 1702);var(1955, 1712);var(1960, 1740);var(1950, 1732);var(1939, 1726);var(1908, 1740);var(1903, 1752);var(1891, 1767);var(1864, 1779);var(1842, 1787);var(1786, 1792);var(1687, 1800);var(1639, 1802);var(1612, 1802);var(1576, 1802);var(1551, 1799);var(1536, 1788);var(1566, 1769);var(1616, 1754);var(1688, 1724);var(1713, 1718);var(1557, 1753);var(1569, 1738);var(1590, 1721);var(1623, 1714);var(1683, 1712);var(1715, 1705);var(1591, 1726);var(1607, 1700);var(1613, 1693);var(1643, 1686);var(1664, 1684);
    end

        cBLACK
        strip
        var(973, 1808);var(971, 1791);var(970, 1780);var(972, 1773);var(978, 1761);var(985, 1752);var(989, 1744);var(997, 1740);var(1011, 1734);var(1024, 1734);var(1031, 1734);var(1034, 1734);var(1035, 1735);var(1043, 1742);var(1045, 1745);var(1051, 1756);var(1061, 1766);var(1069, 1774);var(1084, 1783);var(1093, 1786);
    end

        fan
        var(973, 1808);var(971, 1791);var(970, 1780);var(972, 1773);var(978, 1761);var(985, 1752);var(989, 1744);var(997, 1740);var(1011, 1734);var(1024, 1734);var(1031, 1734);var(1034, 1734);var(1035, 1735);var(1043, 1742);var(1045, 1745);var(1051, 1756);var(1061, 1766);var(1069, 1774);var(1084, 1783);var(1093, 1786);var(985, 1782);var(981, 1755);var(987, 1744);var(994, 1737);var(1003, 1742);var(1000, 1754);var(999, 1763);var(1002, 1776);var(1011, 1787);var(1021, 1798);var(1025, 1806);var(1025, 1806);var(1014, 1806);var(1000, 1804);var(983, 1798);var(977, 1798);var(974, 1798);var(971, 1783);var(972, 1756);var(981, 1746);var(985, 1751);var(986, 1744);var(988, 1742);var(995, 1741);
    end
        strip
        var(1047, 1750);var(1065, 1758);var(1073, 1762);var(1082, 1766);var(1093, 1768);var(1102, 1769);var(1105, 1770);var(1109, 1773);var(1108, 1782);var(1112, 1790);var(1113, 1792);var(1113, 1792);var(1112, 1792);var(1110, 1792);var(1109, 1791);var(1110, 1788);var(1111, 1782);var(1111, 1778);var(1111, 1772);var(1111, 1784);var(1111, 1793);var(1112, 1798);var(1112, 1799);var(1112, 1799);var(1109, 1796);var(1109, 1790);var(1109, 1787);var(1111, 1777);var(1111, 1772);var(1111, 1766);var(1111, 1756);var(1110, 1750);var(1110, 1741);var(1110, 1739);var(1110, 1729);var(1110, 1723);var(1110, 1722);var(1110, 1714);var(1117, 1717);var(1120, 1719);var(1121, 1720);var(1123, 1721);var(1124, 1723);var(1127, 1725);var(1127, 1726);var(1128, 1726);var(1131, 1726);var(1131, 1724);var(1136, 1719);var(1139, 1717);var(1141, 1717);var(1147, 1723);var(1149, 1726);var(1151, 1729);var(1150, 1739);var(1149, 1749);var(1149, 1750);var(1150, 1753);var(1157, 1758);var(1159, 1758);var(1164, 1757);var(1165, 1756);var(1169, 1754);var(1171, 1755);var(1175, 1754);var(1177, 1750);var(1181, 1745);var(1186, 1742);var(1188, 1742);var(1192, 1750);var(1197, 1760);var(1201, 1770);var(1208, 1782);var(1211, 1788);var(1212, 1790);var(1213, 1792);var(1213, 1792);var(1208, 1792);var(1213, 1794);var(1215, 1800);var(1221, 1797);var(1228, 1791);var(1251, 1785);var(1255, 1784);var(1261, 1780);var(1277, 1774);var(1297, 1771);var(1306, 1768);var(1316, 1760);var(1330, 1752);var(1342, 1746);var(1349, 1742);var(1356, 1736);var(1362, 1732);var(1369, 1728);var(1377, 1723);var(1381, 1720);var(1385, 1716);var(1390, 1713);var(1393, 1710);var(1400, 1706);var(1405, 1701);var(1406, 1699);var(1413, 1694);var(1424, 1688);var(1429, 1683);var(1435, 1677);var(1442, 1672);var(1447, 1666);var(1455, 1660);var(1457, 1656);var(1461, 1654);var(1465, 1650);var(1467, 1648);var(1475, 1640);var(1476, 1638);var(1482, 1634);var(1483, 1632);var(1491, 1628);var(1499, 1624);var(1505, 1622);var(1515, 1618);var(1527, 1614);var(1545, 1605);var(1555, 1602);var(1560, 1600);var(1567, 1601);var(1576, 1600);var(1579, 1598);var(1585, 1594);var(1593, 1593);var(1593, 1590);var(1619, 1589);var(1671, 1590);var(1707, 1594);var(1730, 1600);var(1775, 1609);var(1801, 1609);var(1821, 1610);var(1833, 1616);var(1853, 1620);var(1860, 1626);var(1871, 1630);var(1891, 1637);var(1909, 1642);var(1919, 1654);var(1935, 1678);var(1941, 1688);var(1947, 1696);var(1950, 1702);var(1951, 1705);var(1955, 1714);var(1957, 1719);var(1959, 1721);var(1965, 1729);var(1966, 1732);
    end
        strip
        var(1413, 1727);var(1421, 1726);var(1423, 1726);var(1427, 1726);var(1429, 1726);var(1433, 1725);var(1437, 1725);var(1441, 1728);var(1447, 1728);var(1449, 1728);var(1462, 1732);var(1465, 1734);var(1483, 1739);var(1487, 1742);var(1503, 1748);var(1505, 1750);var(1516, 1759);var(1523, 1764);
    end
        strip
        var(1505, 1738);var(1513, 1742);var(1521, 1747);var(1526, 1750);var(1528, 1752);var(1538, 1760);var(1538, 1760);var(1546, 1768);var(1551, 1773);
    end
        strip
        var(1505, 1738);var(1513, 1742);var(1521, 1747);var(1526, 1750);var(1528, 1752);var(1538, 1760);var(1538, 1760);var(1546, 1768);var(1551, 1773);var(1392, 1714);var(1381, 1711);var(1377, 1710);var(1366, 1710);var(1360, 1708);var(1353, 1708);var(1342, 1706);var(1334, 1703);var(1328, 1702);var(1323, 1702);var(1320, 1700);var(1317, 1693);var(1315, 1683);var(1313, 1678);var(1321, 1672);var(1326, 1668);var(1333, 1668);var(1339, 1666);var(1343, 1666);var(1350, 1666);var(1373, 1666);var(1380, 1666);var(1393, 1666);var(1404, 1665);var(1413, 1664);var(1422, 1664);var(1426, 1660);var(1435, 1656);var(1442, 1654);var(1447, 1654);var(1463, 1654);var(1463, 1653);var(1478, 1637);var(1475, 1634);var(1465, 1634);var(1463, 1634);var(1458, 1631);var(1456, 1629);var(1450, 1628);var(1443, 1624);var(1441, 1621);var(1435, 1614);var(1428, 1606);var(1426, 1604);var(1418, 1603);var(1409, 1605);var(1405, 1609);var(1399, 1613);var(1399, 1616);var(1397, 1624);var(1396, 1626);var(1397, 1636);var(1397, 1638);var(1403, 1644);var(1403, 1646);var(1404, 1653);var(1405, 1654);var(1408, 1658);var(1411, 1660);var(1412, 1661);var(1418, 1663);var(1420, 1663);
    end


}

void drawFire()
{
    cFIRE
        fan
        var(1145, 1084);var(1080, 1091);var(1078, 1069);var(1078, 1059);var(1078, 1045);var(1083, 1031);var(1086, 1023);var(1088, 1013);var(1090, 1006);var(1095, 1001);var(1104, 996);var(1111, 993);var(1119, 988);var(1124, 987);var(1127, 983);var(1133, 976);var(1139, 968);var(1145, 958);var(1146, 951);var(1150, 942);var(1154, 931);var(1157, 923);var(1158, 915);var(1158, 908);var(1165, 906);var(1188, 928);var(1190, 944);var(1190, 968);var(1188, 984);var(1188, 990);var(1184, 1021);var(1198, 1103);var(1214, 1151);var(1221, 1178);var(1202, 1191);var(1136, 1183);var(1125, 1171);var(1111, 1158);var(1090, 1146);var(1081, 1117);var(1077, 1103);var(1078, 1094);var(1080, 1085);var(1080, 1073);var(1079, 1060);

    end
        cBLACK
        strip
        var(1145, 1084);var(1080, 1091);var(1078, 1069);var(1078, 1059);var(1078, 1045);var(1083, 1031);var(1086, 1023);var(1088, 1013);var(1090, 1006);var(1095, 1001);var(1104, 996);var(1111, 993);var(1119, 988);var(1124, 987);var(1127, 983);var(1133, 976);var(1139, 968);var(1145, 958);var(1146, 951);var(1150, 942);var(1154, 931);var(1157, 923);var(1158, 915);var(1158, 908);

    end


        cFIRE
        fan
        var(1197, 939);var(1190, 984);var(1194, 979);var(1201, 977);var(1207, 977);var(1213, 977);var(1218, 977);var(1221, 972);var(1221, 964);var(1221, 955);var(1221, 951);var(1218, 943);var(1217, 935);var(1215, 929);var(1214, 922);var(1214, 915);var(1209, 909);var(1205, 903);var(1200, 901);var(1194, 898);var(1192, 897);var(1190, 894);var(1185, 891);var(1183, 888);var(1181, 886);var(1178, 883);var(1175, 881);var(1172, 878);var(1169, 873);var(1166, 869);var(1166, 869);var(1164, 866);var(1156, 862);var(1164, 869);var(1158, 864);var(1156, 863);var(1156, 859);var(1154, 852);var(1152, 849);var(1166, 907);var(1177, 898);var(1191, 898);
    end
        cBLACK
        strip
        var(1197, 939);var(1190, 984);var(1194, 979);var(1201, 977);var(1207, 977);var(1213, 977);var(1218, 977);var(1221, 972);var(1221, 964);var(1221, 955);var(1221, 951);var(1218, 943);var(1217, 935);var(1215, 929);var(1214, 922);var(1214, 915);var(1209, 909);var(1205, 903);var(1200, 901);var(1194, 898);var(1192, 897);var(1190, 894);var(1185, 891);var(1183, 888);var(1181, 886);var(1178, 883);var(1175, 881);var(1172, 878);var(1169, 873);var(1166, 869);var(1166, 869);var(1164, 866);var(1156, 862);var(1164, 869);var(1158, 864);var(1156, 863);var(1156, 859);var(1154, 852);var(1152, 849);
    end

        cFIRE
        fan
        var(1034, 1201);var(1040, 1193);var(1041, 1189);var(1045, 1174);var(1049, 1162);var(1052, 1151);var(1054, 1143);var(1055, 1127);var(1055, 1122);var(1057, 1119);var(1061, 1108);var(1062, 1100);var(1064, 1095);var(1065, 1091);var(1065, 1083);var(1065, 1082);var(1065, 1076);var(1063, 1075);var(1059, 1071);var(1057, 1068);var(1056, 1065);var(1062, 1065);var(1065, 1065);var(1066, 1067);var(1066, 1067);var(1068, 1071);var(1070, 1073);var(1072, 1081);var(1073, 1083);var(1074, 1086);var(1077, 1089);var(1080, 1098);var(1082, 1100);var(1082, 1104);var(1086, 1111);var(1089, 1115);var(1091, 1119);var(1091, 1124);var(1092, 1129);var(1096, 1137);var(1100, 1146);var(1104, 1152);var(1109, 1155);var(1114, 1159);var(1119, 1163);var(1122, 1166);var(1129, 1173);var(1138, 1185);var(1143, 1197);var(1147, 1201);var(1142, 1209);var(1128, 1206);var(1040, 1191);var(1070, 1145);var(1095, 1204);var(1058, 1203);var(1050, 1203);var(1040, 1199);var(1055, 1179);var(1070, 1149);
    end
        fan
        var(1068, 1077);var(1064, 1086);var(1063, 1080);var(1062, 1073);var(1056, 1063);var(1054, 1057);var(1067, 1064);var(1067, 1064);var(1073, 1075);var(1074, 1083);
    end
        cBLACK
        strip
        var(1040, 1193);var(1041, 1189);var(1045, 1174);var(1049, 1162);var(1052, 1151);var(1054, 1143);var(1055, 1127);var(1055, 1122);var(1057, 1119);var(1061, 1108);var(1062, 1100);var(1064, 1095);var(1065, 1091);var(1065, 1083);var(1065, 1082);var(1065, 1076);var(1063, 1075);var(1059, 1071);var(1057, 1068);var(1056, 1065);var(1062, 1065);var(1065, 1065);var(1066, 1067);var(1066, 1067);var(1068, 1071);var(1070, 1073);var(1072, 1081);var(1073, 1083);var(1074, 1086);var(1077, 1089);var(1080, 1098);var(1082, 1100);var(1082, 1104);var(1086, 1111);var(1089, 1115);var(1091, 1119);var(1091, 1124);var(1092, 1129);var(1096, 1137);var(1100, 1146);var(1104, 1152);var(1109, 1155);var(1114, 1159);var(1119, 1163);var(1122, 1166);
    end

        cFIRE
        fan
        var(1241, 1071);var(1194, 1070);var(1193, 1049);var(1191, 1039);var(1194, 1031);var(1198, 1023);var(1205, 1019);var(1208, 1017);var(1216, 1014);var(1222, 1012);var(1231, 1006);var(1235, 999);var(1237, 993);var(1238, 991);var(1241, 980);var(1246, 977);var(1254, 977);var(1263, 985);var(1268, 990);var(1271, 995);var(1271, 1003);var(1268, 1008);var(1271, 1019);var(1272, 1029);var(1275, 1031);var(1282, 1036);var(1286, 1039);var(1298, 1057);var(1302, 1075);var(1310, 1084);var(1321, 1093);var(1324, 1099);var(1323, 1111);var(1323, 1118);var(1306, 1130);var(1302, 1143);var(1278, 1162);var(1253, 1170);
    end

        cBLACK
        strip
        var(1241, 1071);var(1194, 1070);var(1193, 1049);var(1191, 1039);var(1194, 1031);var(1198, 1023);var(1205, 1019);var(1208, 1017);var(1216, 1014);var(1222, 1012);var(1231, 1006);var(1235, 999);var(1237, 993);var(1238, 991);var(1241, 980);
    end

        fan
        var(1279, 1078);var(1331, 1144);var(1333, 1126);var(1332, 1114);var(1329, 1101);var(1326, 1097);var(1321, 1087);var(1321, 1080);var(1314, 1059);var(1312, 1055);var(1312, 1043);var(1311, 1032);var(1306, 1015);var(1298, 1007);var(1297, 1007);var(1297, 1013);var(1297, 1018);var(1297, 1024);var(1296, 1027);var(1290, 1032);var(1287, 1032);var(1276, 1033);var(1275, 1033);
    cBLACK
        strip
        var(1279, 1078);var(1331, 1144);var(1333, 1126);var(1332, 1114);var(1329, 1101);var(1326, 1097);var(1321, 1087);var(1321, 1080);var(1314, 1059);var(1312, 1055);var(1312, 1043);var(1311, 1032);var(1306, 1015);var(1298, 1007);var(1297, 1007);var(1297, 1013);var(1297, 1018);var(1297, 1024);var(1296, 1027);var(1290, 1032);var(1287, 1032);var(1276, 1033);var(1275, 1033);
    end
}

void drawSecondScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    drawLowerGround();
    drawFar();
    drawGround();
    drawBuildings();
    drawStones();
    upperStones();
    middleStones();
    scatteredStones();
    drawFire();
    drawCars();


    glutSwapBuffers();
}

//<-------Drawing Second Screen End--------->

//<-------Drawing Third Screen Start--------->



void drawGradientBackground()
{
    quads
        cBLACKUPPER
        var(0, 0);var(2000, 0);
    cBLACKLOWER
        var(2000, 2000);var(0, 2000);
    end
}

void drawMap()

{
    cMAPRED
        fan
        var(937, 138);var(910, 100);var(930, 126);var(944, 119);var(954, 129);var(946, 146);var(948, 151);var(950, 156);var(952, 160);var(952, 163);var(952, 166);var(952, 168);var(950, 172);var(950, 174);var(949, 177);var(946, 177);var(945, 180);var(945, 184);var(896, 177);var(894, 170);var(893, 170);var(890, 170);var(889, 170);var(886, 168);var(886, 164);var(887, 160);var(890, 157);var(891, 156);var(892, 152);var(893, 148);var(894, 145);var(894, 145);var(894, 141);var(895, 140);var(895, 134);var(895, 132);var(895, 127);var(896, 120);var(910, 100);var(911, 100);
    end
        fan
        var(905, 208);var(895, 172);var(945, 182);var(945, 184);var(945, 185);var(946, 188);var(946, 189);var(946, 190);var(945, 192);var(945, 193);var(944, 193);var(943, 195);var(941, 196);var(940, 198);var(940, 200);var(939, 204);var(940, 206);var(940, 208);var(940, 211);var(940, 213);var(939, 215);var(938, 215);var(937, 216);var(937, 216);var(932, 218);var(932, 219);var(929, 221);var(928, 222);var(925, 226);var(922, 227);var(921, 228);var(919, 230);var(918, 231);var(848, 214);var(851, 209);var(854, 207);var(859, 195);var(861, 194);var(863, 194);var(865, 194);var(881, 193);var(882, 193);var(882, 193);var(883, 190);var(883, 190);var(882, 190);var(883, 184);var(883, 182);var(884, 182);var(887, 180);var(889, 181);var(891, 182);var(893, 182);var(893, 182);var(894, 181);var(896, 179);var(899, 174);var(903, 171);var(912, 167);var(918, 167);var(926, 168);var(937, 176);var(939, 180);var(942, 186);var(943, 190);var(943, 192);
    end
        fan
        var(791, 282);var(848, 214);var(825, 216);var(815, 204);var(804, 191);var(778, 194);var(763, 186);var(761, 188);var(761, 192);var(761, 195);var(761, 200);var(758, 198);var(755, 196);var(752, 196);var(749, 195);var(722, 194);var(705, 276);var(706, 276);var(708, 277);var(709, 278);var(712, 279);var(714, 281);var(714, 283);var(715, 285);var(714, 288);var(713, 290);var(713, 293);var(709, 296);var(709, 298);var(709, 301);var(708, 304);var(705, 309);var(705, 310);var(703, 312);var(700, 314);var(698, 316);var(696, 317);var(695, 319);var(691, 321);var(691, 321);var(691, 322);var(688, 323);var(688, 324);var(688, 324);var(687, 324);var(685, 326);var(895, 339);var(926, 240);var(919, 232);var(914, 226);var(900, 220);var(863, 220);var(849, 213);var(825, 215);
    end
        fan
        var(873, 228);var(874, 212);var(860, 210);var(853, 217);var(838, 240);var(881, 255);var(914, 239);var(905, 219);var(888, 203);var(865, 203);
    end
        fan
        var(683, 363);var(687, 328);var(674, 314);var(655, 321);var(654, 370);var(666, 438);var(917, 454);var(917, 451);var(917, 448);var(917, 441);var(917, 434);var(917, 427);var(917, 419);var(917, 412);var(917, 401);var(916, 392);var(916, 385);var(914, 373);var(913, 366);var(912, 359);var(908, 351);var(907, 350);var(903, 346);var(899, 343);var(898, 341);var(895, 337);var(895, 339);var(895, 330);var(887, 315);var(887, 299);var(865, 284);var(856, 282);var(800, 270);var(774, 270);var(716, 282);var(691, 332);var(676, 360);
    end
        fan
        var(747, 528);var(656, 370);var(647, 373);var(646, 375);var(646, 376);var(646, 381);var(647, 386);var(647, 394);var(646, 401);var(646, 408);var(644, 414);var(643, 424);var(642, 433);var(640, 443);var(639, 451);var(635, 465);var(632, 477);var(630, 486);var(628, 492);var(627, 496);var(625, 501);var(623, 508);var(621, 513);var(619, 518);var(617, 522);var(615, 527);var(614, 530);var(613, 531);var(612, 536);var(612, 541);var(612, 565);var(913, 609);var(910, 600);var(910, 593);var(908, 582);var(907, 576);var(907, 568);var(908, 564);var(908, 559);var(911, 553);var(911, 545);var(911, 542);var(909, 537);var(906, 533);var(904, 527);var(906, 522);var(909, 518);var(912, 512);var(914, 504);var(916, 495);var(918, 483);var(919, 472);var(919, 466);var(919, 458);var(919, 452);var(916, 441);var(907, 432);var(854, 420);var(801, 410);var(721, 400);var(704, 407);var(651, 437);var(635, 462);var(624, 502);
    end
        fan
        var(730, 705);var(612, 557);var(911, 604);var(912, 623);var(906, 630);var(906, 655);var(896, 671);var(894, 697);var(899, 702);var(901, 705);var(895, 712);var(896, 716);var(899, 718);var(901, 721);var(903, 724);var(903, 739);var(895, 747);var(893, 750);var(555, 731);var(559, 721);var(559, 716);var(561, 708);var(563, 703);var(565, 696);var(570, 690);var(573, 681);var(575, 676);var(580, 671);var(584, 661);var(588, 654);var(591, 640);var(593, 631);var(595, 622);var(596, 614);var(598, 605);var(600, 600);var(600, 595);var(602, 590);var(602, 585);var(602, 580);var(603, 576);var(605, 572);var(607, 569);var(610, 564);var(611, 561);var(614, 557);var(663, 528);var(774, 557);var(907, 628);
    end

        fan
        var(730, 705);var(612, 557);var(911, 604);var(912, 623);var(906, 630);var(906, 655);var(896, 671);var(894, 697);var(899, 702);var(901, 705);var(895, 712);var(896, 716);var(899, 718);var(901, 721);var(903, 724);var(903, 739);var(895, 747);var(893, 750);var(555, 731);var(559, 721);var(559, 716);var(561, 708);var(563, 703);var(565, 696);var(570, 690);var(573, 681);var(575, 676);var(580, 671);var(584, 661);var(588, 654);var(591, 640);var(593, 631);var(595, 622);var(596, 614);var(598, 605);var(600, 600);var(600, 595);var(602, 590);var(602, 585);var(602, 580);var(603, 576);var(605, 572);var(607, 569);var(610, 564);var(611, 561);var(614, 557);var(663, 528);var(774, 557);var(907, 628);var(705, 794);var(557, 728);var(894, 748);var(893, 752);var(893, 759);var(893, 760);var(896, 765);var(899, 767);var(901, 769);var(903, 773);var(904, 774);var(904, 774);var(903, 776);var(901, 777);var(897, 781);var(897, 781);var(897, 786);var(900, 788);var(901, 789);var(903, 791);var(903, 791);var(904, 792);var(905, 818);var(893, 818);var(890, 818);var(888, 819);var(887, 819);var(867, 840);var(865, 845);var(867, 853);var(865, 867);var(846, 888);var(634, 1060);var(351, 1035);var(353, 1032);var(358, 1027);var(363, 1023);var(368, 1016);var(375, 1010);var(382, 1001);var(389, 993);var(395, 984);var(402, 980);var(410, 970);var(420, 960);var(427, 949);var(438, 937);var(448, 924);var(457, 913);var(466, 902);var(474, 889);var(482, 878);var(493, 862);var(501, 850);var(508, 842);var(514, 823);var(521, 813);var(526, 798);var(530, 790);var(536, 781);var(541, 769);var(547, 759);var(553, 741);var(555, 729);var(557, 721);var(902, 737);
    end
        fan
        var(634, 1061);var(350, 1033);var(406, 1194);var(408, 1197);var(410, 1204);var(410, 1205);var(415, 1207);var(414, 1212);var(418, 1226);var(470, 1332);var(606, 1606);var(822, 1150);var(807, 1006);var(450, 922);
    end
        fan
        var(723, 1078);var(630, 937);var(528, 1106);var(584, 1240);var(816, 1246);var(827, 1108);var(825, 1072);var(830, 984);var(645, 960);var(527, 1104);
    end
        fan
        var(747, 915);var(864, 843);var(865, 868);var(845, 887);var(846, 913);var(838, 926);var(836, 952);var(844, 968);var(833, 984);var(686, 984);var(658, 871);var(700, 777);var(866, 838);
    end
        fan
        var(778, 1004);var(830, 981);var(838, 995);var(843, 1005);var(846, 1012);var(850, 1021);var(852, 1027);var(852, 1031);var(852, 1036);var(842, 1054);var(841, 1063);var(841, 1067);var(841, 1069);var(841, 1069);var(825, 1074);var(634, 1057);var(666, 951);var(748, 913);
    end
        fan
        var(744, 1158);var(724, 1078);var(826, 1108);var(837, 1108);var(837, 1136);var(840, 1141);var(842, 1145);var(844, 1150);var(845, 1155);var(831, 1167);var(831, 1173);var(830, 1178);var(830, 1183);var(830, 1187);var(831, 1191);var(829, 1196);var(828, 1201);var(827, 1203);var(825, 1231);var(815, 1244);var(707, 1463);var(502, 1287);var(633, 1075);var(778, 1002);
    end
        fan
        var(758, 1268);var(702, 1206);var(824, 1205);var(845, 1204);var(844, 1210);var(839, 1216);var(834, 1220);var(829, 1225);var(824, 1232);var(818, 1239);var(814, 1247);var(814, 1246);var(814, 1254);var(817, 1268);var(816, 1273);var(801, 1283);var(798, 1286);var(797, 1291);var(796, 1294);var(795, 1298);var(794, 1300);var(794, 1304);var(794, 1305);var(794, 1309);var(795, 1313);var(795, 1316);var(794, 1319);var(792, 1324);var(791, 1326);var(790, 1327);var(788, 1329);var(786, 1331);var(786, 1333);var(785, 1336);var(785, 1337);var(783, 1338);var(782, 1339);var(782, 1339);var(782, 1342);var(782, 1350);var(782, 1352);var(782, 1352);var(782, 1355);var(661, 1316);var(703, 1202);
    end
        fan
        var(647, 1362);var(678, 1318);var(782, 1357);var(780, 1358);var(777, 1361);var(774, 1362);var(770, 1366);var(769, 1367);var(767, 1369);var(765, 1373);var(763, 1375);var(761, 1378);var(761, 1380);var(759, 1383);var(757, 1386);var(757, 1390);var(757, 1393);var(757, 1396);var(757, 1398);var(756, 1401);var(755, 1402);var(755, 1405);var(755, 1409);var(755, 1412);var(755, 1417);var(755, 1420);var(756, 1422);var(758, 1426);var(758, 1426);var(757, 1430);var(754, 1434);var(752, 1438);var(751, 1441);var(749, 1443);var(747, 1446);var(746, 1448);var(744, 1449);var(742, 1451);var(742, 1453);var(740, 1454);var(739, 1455);var(737, 1456);var(730, 1628);var(710, 1660);var(639, 1896);var(632, 1822);var(618, 1768);var(566, 1619);var(652, 1498);var(737, 1561);
    end
        fan
        var(585, 1357);var(471, 1331);var(471, 1331);var(470, 1368);var(479, 1376);var(478, 1404);var(480, 1406);var(481, 1408);var(484, 1413);var(484, 1413);var(489, 1417);var(492, 1422);var(493, 1424);var(737, 1455);var(758, 1384);var(782, 1338);var(611, 1284);var(471, 1332);
    end
        fan
        var(580, 1443);var(493, 1422);var(491, 1426);var(491, 1426);var(491, 1430);var(490, 1432);var(489, 1437);var(488, 1440);var(487, 1443);var(489, 1451);var(489, 1452);var(489, 1458);var(487, 1459);var(488, 1464);var(491, 1468);var(494, 1471);var(504, 1476);var(518, 1486);var(527, 1508);var(633, 1465);var(578, 1406);var(504, 1419);var(493, 1424);
    end
        fan
        var(651, 1550);var(519, 1490);var(532, 1526);var(539, 1548);var(560, 1604);var(566, 1621);var(566, 1625);var(615, 1768);var(691, 1784);var(691, 1537);var(527, 1507);
    end
        fan
        var(579, 1565);var(567, 1504);var(538, 1520);var(542, 1552);var(561, 1610);var(662, 1579);var(627, 1464);var(539, 1474);var(533, 1523);
    end
        fan
        var(661, 1796);var(617, 1768);var(616, 1774);var(617, 1782);var(617, 1787);var(615, 1796);var(615, 1803);var(619, 1809);var(621, 1813);var(625, 1817);var(627, 1818);var(629, 1824);var(689, 1832);var(689, 1816);var(689, 1792);var(690, 1784);var(698, 1768);var(699, 1764);var(699, 1760);var(696, 1741);var(653, 1706);var(612, 1747);var(616, 1769);
    end
        fan
        var(691, 1722);var(709, 1660);var(709, 1709);var(715, 1720);var(699, 1738);var(664, 1770);var(653, 1698);var(664, 1654);var(710, 1658);var(709, 1661);
    end
        fan
        var(653, 1839);var(629, 1822);var(628, 1825);var(626, 1829);var(625, 1834);var(625, 1836);var(625, 1838);var(625, 1839);var(625, 1842);var(625, 1843);var(625, 1846);var(625, 1848);var(625, 1850);var(624, 1853);var(625, 1854);var(625, 1858);var(627, 1862);var(627, 1868);var(627, 1872);var(629, 1876);var(630, 1879);var(631, 1884);var(640, 1898);var(655, 1870);var(667, 1872);var(667, 1855);var(690, 1831);var(689, 1815);var(630, 1822);
    end
}

void drawMarchForGaza()
{
    //white background
    cWHITE
        quads
        var(1053, 1029);var(1606, 1029);var(1606, 1175);var(1053, 1175);
    end
        //March For
        cBLACK
        renderText(1073, 1126, "MARCH FOR", "Cambria", 48);

    //GAZA
    cWHITE
        renderText(1055, 1360, "GAZA", "Cambria", 115);

}
void drawLocationIcon()
{
    cORANGE
        circle(50, 50, 1100, 1500);
    triangle
        var(1048, 1500);var(1152, 1500);var(1100, 1600);
    end
        cBLACK
        circle(24, 24, 1100, 1500);
}
void drawSuhrawardy()
{

    //Suhrawardy Udyan
    cWHITE
        renderText(1054, 1650, "TOWARDS", "Arial Black", 13);
    renderText(1054, 1700, "SUHRAWARDY UDYAN", "Arial Black", 13);
}

void drawDateTime()
{
    //icon
    cORANGE
        quads
        var(1450, 1500);var(1550, 1500);var(1550, 1600);var(1450, 1600);
    end
        cBLACK
        quads
        var(1460, 1510);var(1540, 1510);var(1540, 1590);var(1460, 1590);
    end
        //Date and Time
        cWHITE
        renderText(1450, 1650, "12 APRIL 2025", "Arial Black", 13);
    renderText(1450, 1700, "03:00 PM", "Arial Black", 13);
}

void drawGazaMap()
{
    cMAPGAZA
        fan
        var(478, 913);var(508, 833);var(549, 869);var(550, 879);var(541, 888);var(539, 891);var(539, 894);var(533, 896);var(527, 901);var(525, 904);var(521, 905);var(515, 910);var(511, 914);var(508, 918);var(505, 923);var(501, 926);var(499, 928);var(496, 932);var(491, 937);var(487, 943);var(481, 948);var(472, 955);var(464, 966);var(455, 975);var(448, 984);var(434, 1007);var(405, 972);var(415, 963);var(423, 953);var(428, 945);var(435, 938);var(441, 930);var(445, 923);var(449, 917);var(457, 911);var(464, 901);var(471, 888);var(481, 877);var(487, 867);var(494, 860);var(499, 851);var(505, 841);var(509, 834);var(512, 837);
    end
        fan
        var(374, 1022);var(385, 1047);var(416, 961);var(434, 1003);var(434, 1007);var(434, 1017);var(436, 1026);var(437, 1034);var(438, 1038);var(438, 1045);var(437, 1051);var(436, 1057);var(434, 1060);var(433, 1061);var(430, 1061);var(428, 1061);var(424, 1063);var(424, 1063);var(423, 1064);var(422, 1066);var(421, 1069);var(421, 1072);var(420, 1073);var(419, 1073);var(418, 1076);var(418, 1078);var(417, 1078);var(415, 1081);var(412, 1085);var(394, 1095);var(390, 1099);var(388, 1099);var(387, 1101);var(387, 1104);var(377, 1113);var(365, 1071);var(360, 1057);var(346, 1039);var(356, 1026);var(370, 1010);var(378, 1003);var(388, 994);var(394, 983);var(406, 974);var(417, 959);var(424, 961);var(374, 1112);var(360, 1062);var(345, 1039);var(395, 986);var(404, 1018);
    end
}


void drawFlagPalestine()
{
    //flag
    cFLAGGREEN
        quads
        var(1032, 370);var(1629, 370);var(1632, 670);var(1032, 670);
    end
        cWHITE
        quads
        var(1632, 570);var(1632, 470);var(1032, 470);var(1032, 570);
    end
        cBLACK
        quads
        var(1632, 470);var(1632, 370);var(1032, 370);var(1032, 470);
    end
        cRED
        triangle
        var(1032, 370);var(1032, 670);var(1232, 520);
    end

}

void drawSlogan()
{
    cWHITE
        renderText(1050, 800, "From the River, to the Sea", "Gabriola", 35);
    cRED
        renderText(1050, 900, "Palestine will be free!", "Gabriola", 44);

}

void drawThirdScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawGradientBackground();
    drawMap();
    drawGazaMap();
    drawMarchForGaza();
    drawLocationIcon();
    drawSuhrawardy();
    drawDateTime();
    drawFlagPalestine();
    drawSlogan();

    glutSwapBuffers();
}

//<-------Drawing Third Screen End--------->

//<-------Drawing Functions End--------->



int currentScreen = 0;

void switchScreen(int value) {
    showFirstScreen = false;
    glutPostRedisplay(); // Request screen redraw
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (currentScreen) {
    case 0: drawFirstScreen(); break;
    case 1: drawSecondScreen(); break;
    case 2: drawThirdScreen(); break;
    }

    glFlush();
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) {
        currentScreen = (currentScreen + 1) % 3;
    }
    else if (key == GLUT_KEY_LEFT) {
        currentScreen = (currentScreen - 1 + 3) % 3; // Ensure it wraps around
    }

    glutPostRedisplay();
}

//<-------Functions End--------->

int main(int argc, char** argv) {


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("March for Gaza");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    // glutTimerFunc(5000, switchScreen, 0); // After 5 seconds, switch
    glutMainLoop();
    return 0;
}
