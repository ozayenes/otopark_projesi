#include "raylib.h"
#include <stdio.h>
#include <string.h>

/*
  LAYOUT (1400x900 pencere, sol panel 240px, harita 1140px):
  [  W SIRASI - yatay, ust  ]
  [====== ANA KORIDOR ======]
  [ BLOK A ][ BLOK B ]
  [====== ORTA KORIDOR =====]
  [ BLOK C ][ BLOK D ]
  [====== ALT KORIDOR ======]

  Her blok: sol sutun (asagi) + ic koridor + sag sutun (yukari)
  3 park per sutun => 12 park per blok
  W(8) + A(12) + B(12) + C(12) + D(12) = 56
*/

#define PARK_SAYISI 56

typedef struct {
    char isim[6];
    int  dolu;
    Rectangle alan;
    int yukariMi;
} ParkYeri;

// Renk paleti - tamamen dolgun, seffaf yok
#define COL_BG          (Color){14, 16, 28, 255}
#define COL_PANEL_BG    (Color){22, 26, 45, 255}
#define COL_PANEL_HDR   (Color){35, 80, 200, 255}
#define COL_ROAD        (Color){42, 46, 68, 255}
#define COL_ROAD_LINE   (Color){230, 200, 0, 255}
#define COL_SLOT_BOSH   (Color){18, 140, 55, 255}
#define COL_SLOT_DOLU   (Color){160, 22, 22, 255}
#define COL_BORDER_BOS  (Color){40, 255, 90, 255}
#define COL_BORDER_DOLU (Color){255, 60, 60, 255}
#define COL_BLOCK_BG    (Color){24, 28, 50, 255}
#define COL_BLOCK_HDR   (Color){38, 75, 185, 255}
#define COL_CAR_BODY    (Color){30, 65, 200, 255}
#define COL_CAR_SHADOW  (Color){8, 12, 40, 255}
#define COL_CAR_GLASS   (Color){90, 180, 255, 255}
#define COL_HEADLIGHT   (Color){255, 235, 60, 255}
#define COL_TAILLIGHT   (Color){255, 40, 40, 255}
#define COL_WHEEL       (Color){18, 18, 18, 255}
#define COL_TEXT_WHITE  (Color){240, 245, 255, 255}
#define COL_TEXT_GREEN  (Color){50, 255, 100, 255}
#define COL_TEXT_RED    (Color){255, 70, 70, 255}
#define COL_TEXT_YELLOW (Color){255, 200, 50, 255}
#define COL_TEXT_BLUE   (Color){80, 180, 255, 255}
#define COL_GIRIS       (Color){0, 160, 80, 255}
#define COL_CIKIS       (Color){220, 80, 20, 255}
#define COL_HIGHLIGHT   (Color){255, 220, 0, 255}
#define COL_STAT_BOS_BG (Color){18, 100, 40, 255}
#define COL_STAT_DOLU_BG (Color){120, 20, 20, 255}
#define COL_INNER_KOR   (Color){50, 55, 80, 255}

static void AracCiz(Rectangle r, int yukariMi)
{
    float x  = r.x + 4;
    float y  = r.y + 5;
    float cw = r.width  - 8;
    float ch = r.height - 10;

    // Golge
    DrawRectangleRounded((Rectangle){x+2, y+2, cw, ch}, 0.38f, 8, COL_CAR_SHADOW);
    // Govde
    DrawRectangleRounded((Rectangle){x, y, cw, ch}, 0.38f, 8, COL_CAR_BODY);
    // Parlama
    DrawRectangleRounded((Rectangle){x+2, y+2, cw/2-3, ch/4}, 0.3f, 5,
        (Color){100, 150, 255, 120});

    if(!yukariMi) {
        // Asagi bakan: on cam ustte
        DrawRectangleRounded((Rectangle){x+3, y+6,  cw-6, 10}, 0.4f, 5, COL_CAR_GLASS);
        DrawRectangleRounded((Rectangle){x+3, y+ch-16, cw-6, 10}, 0.4f, 5,
            (Color){70, 140, 200, 255});
        DrawCircle((int)(x+4),    (int)(y+3), 3, COL_HEADLIGHT);
        DrawCircle((int)(x+cw-4), (int)(y+3), 3, COL_HEADLIGHT);
        DrawCircle((int)(x+4),    (int)(y+ch+2), 3, COL_TAILLIGHT);
        DrawCircle((int)(x+cw-4), (int)(y+ch+2), 3, COL_TAILLIGHT);
    } else {
        DrawRectangleRounded((Rectangle){x+3, y+6,  cw-6, 10}, 0.4f, 5,
            (Color){70, 140, 200, 255});
        DrawRectangleRounded((Rectangle){x+3, y+ch-16, cw-6, 10}, 0.4f, 5, COL_CAR_GLASS);
        DrawCircle((int)(x+4),    (int)(y+3), 3, COL_TAILLIGHT);
        DrawCircle((int)(x+cw-4), (int)(y+3), 3, COL_TAILLIGHT);
        DrawCircle((int)(x+4),    (int)(y+ch+2), 3, COL_HEADLIGHT);
        DrawCircle((int)(x+cw-4), (int)(y+ch+2), 3, COL_HEADLIGHT);
    }
    // Tekerler
    DrawRectangleRounded((Rectangle){x-4, y+9, 5, 12}, 0.3f, 3, COL_WHEEL);
    DrawRectangleRounded((Rectangle){x-4, y+ch-21, 5, 12}, 0.3f, 3, COL_WHEEL);
    DrawRectangleRounded((Rectangle){x+cw-1, y+9, 5, 12}, 0.3f, 3, COL_WHEEL);
    DrawRectangleRounded((Rectangle){x+cw-1, y+ch-21, 5, 12}, 0.3f, 3, COL_WHEEL);
    // Jant
    DrawCircle((int)(x-1),    (int)(y+15),    3, (Color){90, 90, 90, 255});
    DrawCircle((int)(x-1),    (int)(y+ch-15), 3, (Color){90, 90, 90, 255});
    DrawCircle((int)(x+cw+2), (int)(y+15),    3, (Color){90, 90, 90, 255});
    DrawCircle((int)(x+cw+2), (int)(y+ch-15), 3, (Color){90, 90, 90, 255});
}

int main(void)
{
    ParkYeri parklar[PARK_SAYISI];
    memset(parklar, 0, sizeof(parklar));

    // ── BOYUTLAR ──
    const int PW      = 44;   // park eni
    const int PH      = 82;   // park boyu
    const int xPitch  = 48;   // yatay adim
    const int icKor   = 28;   // blok ici koridor
    const int nPark   = 3;
    const int sutunW  = nPark * xPitch;        // 144
    const int blokW   = sutunW + icKor + sutunW; // 316

    // Pencere
    const int SW = 1400;
    const int SH = 900;

    // Sol panel
    const int panelW = 240;

    // Harita alani
    const int HX = panelW + 12;
    const int HY = 82;
    const int HW = SW - HX - 8;   // ~1140
    const int HH = SH - HY - 45;  // ~773

    // Iki blok yan yana ortala
    const int araKor  = 40;
    const int topBlok = 2 * blokW + araKor;   // 672
    const int kenarBos= (HW - topBlok) / 2;   // ~234
    const int blok0X  = HX + kenarBos;
    const int blok1X  = blok0X + blokW + araKor;

    // Y
    const int WPH      = 44;
    const int WPW      = 70;
    const int yEtiket  = HY + 26;   // "YIKAMA & BEKLEME" serit y
    const int etiketH  = 20;
    const int yW       = yEtiket + etiketH + 6; // W kutulari etiketten sonra baslar
    const int yKor1    = yW + WPH + 8;
    const int kor1H    = 44;
    const int yUstBlok = yKor1 + kor1H;
    const int yOrtaKor = yUstBlok + PH + 8;
    const int ortaKorH = 36;
    const int yUstAlt  = yOrtaKor + ortaKorH;
    const int yKor2    = yUstAlt + PH + 10;
    const int kor2H    = 50;
    const int yAltBlok = yKor2 + kor2H;
    const int yAltOKor = yAltBlok + PH + 8;
    const int altOKorH = 36;
    const int yAltAlt  = yAltOKor + altOKorH;
    const int yKor3    = yAltAlt + PH + 8;

    int idx = 0;

    // W SIRASI
    int wToplam = 8;
    int wPitch  = HW / wToplam;
    for(int i = 0; i < wToplam; i++) {
        sprintf(parklar[idx].isim, "W%d", i+1);
        parklar[idx].dolu     = (i % 3 == 1);
        parklar[idx].yukariMi = 0;
        parklar[idx].alan     = (Rectangle){
            HX + i*wPitch + (wPitch - WPW)/2,
            yW, WPW, WPH
        };
        idx++;
    }

    // 4 BLOK
    int blokBaseX[4] = { blok0X, blok1X, blok0X, blok1X };
    int blokBaseY[4] = { yUstBlok, yUstBlok, yAltBlok, yAltBlok };
    int blokAltY[4]  = { yUstAlt,  yUstAlt,  yAltAlt,  yAltAlt  };
    char blokIsim[4] = {'A','B','C','D'};

    for(int b = 0; b < 4; b++) {
        int bx  = blokBaseX[b];
        int byU = blokBaseY[b];
        int byA = blokAltY[b];
        int sx  = bx + sutunW + icKor;
        char bl = blokIsim[b];

        for(int i = 0; i < nPark; i++) {
            sprintf(parklar[idx].isim, "%c%d", bl, i+1);
            parklar[idx].dolu     = (idx % 2);
            parklar[idx].yukariMi = 0;
            parklar[idx].alan     = (Rectangle){ bx + i*xPitch + 3, byU + 3, PW, PH };
            idx++;
        }
        for(int i = 0; i < nPark; i++) {
            sprintf(parklar[idx].isim, "%c%d", bl, i+1+nPark);
            parklar[idx].dolu     = ((idx+1) % 2);
            parklar[idx].yukariMi = 1;
            parklar[idx].alan     = (Rectangle){ bx + i*xPitch + 3, byA + 3, PW, PH };
            idx++;
        }
        for(int i = 0; i < nPark; i++) {
            sprintf(parklar[idx].isim, "%c%d", bl, i+1+2*nPark);
            parklar[idx].dolu     = (idx % 2);
            parklar[idx].yukariMi = 0;
            parklar[idx].alan     = (Rectangle){ sx + i*xPitch + 3, byU + 3, PW, PH };
            idx++;
        }
        for(int i = 0; i < nPark; i++) {
            sprintf(parklar[idx].isim, "%c%d", bl, i+1+3*nPark);
            parklar[idx].dolu     = ((idx+1) % 2);
            parklar[idx].yukariMi = 1;
            parklar[idx].alan     = (Rectangle){ sx + i*xPitch + 3, byA + 3, PW, PH };
            idx++;
        }
    }

    InitWindow(SW, SH, "AKILLI OTOPARK SISTEMI v3");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Tiklama
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mp = GetMousePosition();
            for(int i = 0; i < PARK_SAYISI; i++)
                if(CheckCollisionPointRec(mp, parklar[i].alan))
                    parklar[i].dolu = !parklar[i].dolu;
        }

        int doluSayisi = 0;
        for(int i = 0; i < PARK_SAYISI; i++) if(parklar[i].dolu) doluSayisi++;
        int bosSayisi = PARK_SAYISI - doluSayisi;
        int doluluk   = (doluSayisi * 100) / PARK_SAYISI;

        char enYakinBos[6] = "YOK";
        int  enYakinIndex  = -1;
        for(int i = 0; i < PARK_SAYISI; i++) {
            if(!parklar[i].dolu) {
                sprintf(enYakinBos, "%s", parklar[i].isim);
                enYakinIndex = i;
                break;
            }
        }

        int tahminiDoluluk = doluluk;
        if(doluluk < 40)       tahminiDoluluk += 15;
        else if(doluluk < 70)  tahminiDoluluk += 8;
        else                   tahminiDoluluk += 3;
        if(tahminiDoluluk > 100) tahminiDoluluk = 100;
        int tahminiDoluPark = (tahminiDoluluk * PARK_SAYISI) / 100;

        // ══ CIZIM ══
        BeginDrawing();
        ClearBackground(COL_BG);

        // ── UST BASLIK ──
        DrawRectangle(0, 0, SW, 76, (Color){20, 42, 100, 255});
        DrawRectangleLinesEx((Rectangle){0, 0, SW, 76}, 2, (Color){50, 100, 220, 255});
        DrawText("AKILLI OTOPARK SISTEMI", 36, 20, 36, COL_TEXT_WHITE);
        DrawText("v3.0", SW-90, 26, 20, COL_TEXT_BLUE);

        // ── SOL PANEL ──
        DrawRectangle(8, 82, panelW-4, SH-82-45, COL_PANEL_BG);
        DrawRectangleLinesEx((Rectangle){8, 82, panelW-4, SH-82-45}, 2,
            (Color){50, 100, 220, 255});

        // Panel baslik
        DrawRectangle(8, 82, panelW-4, 32, COL_PANEL_HDR);
        DrawText("ISTATISTIKLER", 30, 90, 18, COL_TEXT_WHITE);

        int py = 124; // panel y baslangic

        // Toplam
        DrawRectangle(18, py, panelW-24, 44, (Color){30, 70, 150, 255});
        DrawRectangleLinesEx((Rectangle){18, py, panelW-24, 44}, 2, (Color){60, 130, 255, 255});
        DrawText("TOPLAM PARK", 26, py+6, 13, COL_TEXT_BLUE);
        DrawText(TextFormat("%d", PARK_SAYISI), 140, py+8, 26, COL_TEXT_WHITE);
        py += 52;

        // Bos / Dolu
        DrawRectangle(18, py, 104, 44, COL_STAT_BOS_BG);
        DrawRectangleLinesEx((Rectangle){18, py, 104, 44}, 2, (Color){40, 220, 80, 255});
        DrawText("BOS", 32, py+6, 13, COL_TEXT_GREEN);
        DrawText(TextFormat("%d", bosSayisi), 50, py+20, 22, COL_TEXT_GREEN);

        DrawRectangle(128, py, 104, 44, COL_STAT_DOLU_BG);
        DrawRectangleLinesEx((Rectangle){128, py, 104, 44}, 2, (Color){220, 50, 50, 255});
        DrawText("DOLU", 140, py+6, 13, COL_TEXT_RED);
        DrawText(TextFormat("%d", doluSayisi), 158, py+20, 22, COL_TEXT_RED);
        py += 52;

        // Doluluk bar
        DrawRectangle(18, py, panelW-24, 12, (Color){35, 38, 60, 255});
        DrawRectangleLinesEx((Rectangle){18, py, panelW-24, 12}, 1, (Color){70, 80, 130, 255});
        int barW = (int)((panelW-24) * doluluk / 100.0f);
        Color barC = doluluk < 50 ? (Color){30, 220, 80, 255}
                   : doluluk < 80 ? (Color){255, 180, 0, 255}
                   :                (Color){255, 50, 50, 255};
        if(barW > 0) DrawRectangle(18, py, barW, 12, barC);
        py += 16;
        DrawText(TextFormat("DOLULUK: %%%d", doluluk), 24, py, 14, barC);
        py += 22;

        // YZ Tahmini
        DrawRectangle(18, py, panelW-24, 64, (Color){20, 50, 110, 255});
        DrawRectangleLinesEx((Rectangle){18, py, panelW-24, 64}, 2, (Color){50, 130, 255, 255});
        DrawText("YZ TAHMINI (1 SAAT)", 22, py+6, 12, COL_TEXT_BLUE);
        DrawText(TextFormat("Doluluk: %%%d", tahminiDoluluk), 22, py+24, 14, COL_TEXT_WHITE);
        DrawText(TextFormat("T.Dolu: %d park", tahminiDoluPark), 22, py+42, 14, COL_TEXT_YELLOW);
        py += 72;

        // En yakin bos
        DrawRectangle(18, py, panelW-24, 60, (Color){18, 90, 38, 255});
        DrawRectangleLinesEx((Rectangle){18, py, panelW-24, 60}, 2, (Color){40, 220, 80, 255});
        DrawText("EN YAKIN BOS", 26, py+6, 13, COL_TEXT_GREEN);
        DrawText(enYakinBos, 60, py+22, 32, COL_TEXT_GREEN);
        py += 68;

        // Blok durumu
        DrawRectangle(18, py, panelW-24, 22, (Color){30, 60, 140, 255});
        DrawText("BLOK DURUMU", 26, py+5, 13, (Color){180, 200, 255, 255});
        py += 26;

        for(int b = 0; b < 4; b++) {
            int bD = 0;
            for(int i = 8+b*12; i < 8+(b+1)*12; i++) if(parklar[i].dolu) bD++;
            Color bc = bD == 12 ? (Color){255, 50, 50, 255}
                     : bD > 6   ? (Color){255, 180, 0, 255}
                     :             (Color){40, 220, 80, 255};
            DrawRectangle(18, py, panelW-24, 26, COL_BLOCK_BG);
            DrawRectangleLinesEx((Rectangle){18, py, panelW-24, 26}, 1, (Color){70, 80, 130, 255});
            DrawText(TextFormat("BLOK %c", blokIsim[b]), 24, py+7, 14, (Color){200, 210, 255, 255});
            // Mini bar
            DrawRectangle(108, py+7, 100, 12, (Color){30, 30, 50, 255});
            int bBarW = (int)(100.0f * bD / 12.0f);
            if(bBarW > 0) DrawRectangle(108, py+7, bBarW, 12, bc);
            DrawText(TextFormat("%d/12", bD), 186, py+7, 12, bc);
            py += 30;
        }

        // W sirasi
        {
            int wD = 0;
            for(int i = 0; i < 8; i++) if(parklar[i].dolu) wD++;
            DrawRectangle(18, py, panelW-24, 26, COL_BLOCK_BG);
            DrawRectangleLinesEx((Rectangle){18, py, panelW-24, 26}, 1, (Color){70, 80, 130, 255});
            DrawText(TextFormat("YIKAMA %d/8", wD), 24, py+7, 14, COL_TEXT_BLUE);
            py += 30;
        }

        // ── HARITA ALANI ──
        DrawRectangle(HX, HY, HW, HH, (Color){30, 34, 52, 255});
        DrawRectangleLinesEx((Rectangle){HX, HY, HW, HH}, 2, (Color){50, 90, 200, 255});

        // Harita baslik
        DrawRectangle(HX, HY, HW, 26, (Color){32, 65, 160, 255});
        DrawText("OTOPARK HARITASI", HX + HW/2 - 90, HY + 5, 18, COL_TEXT_WHITE);

        // YIKAMA etiketi -- harita basligindan hemen sonra, W kutularinin ustunde
        DrawRectangle(HX, yEtiket, HW, etiketH, (Color){14, 44, 95, 255});
        DrawRectangleLinesEx((Rectangle){HX, yEtiket, HW, etiketH}, 1, (Color){40, 90, 200, 255});
        DrawText("[ YIKAMA & BEKLEME BOLUMU ]", HX + HW/2 - 130, yEtiket+3, 13,
            COL_TEXT_BLUE);

        // ── ANA KORIDOR ──
        DrawRectangle(HX, yKor1, HW, kor1H, COL_ROAD);
        for(int i = 0; i < 18; i++)
            DrawRectangle(HX+30 + i*60, yKor1 + kor1H/2 - 3, 38, 6, COL_ROAD_LINE);
        DrawText(">>", HX+50, yKor1+10, 20, (Color){255, 255, 200, 255});
        DrawText(">>", HX+HW/2-20, yKor1+10, 20, (Color){255, 255, 200, 255});
        DrawText(">>", HX+HW-100, yKor1+10, 20, (Color){255, 255, 200, 255});
        DrawRectangle(HX+HW-16, yKor1, 16, kor1H, COL_GIRIS);
        DrawText("GIR", HX+HW-15, yKor1+16, 10, WHITE);
        DrawRectangle(HX, yKor1, 16, kor1H, COL_CIKIS);
        DrawText("CIK", HX+1, yKor1+16, 10, WHITE);

        // ── ORTA KORIDOR (ust bloklar) ──
        DrawRectangle(HX, yOrtaKor, HW, ortaKorH, COL_ROAD);
        for(int i = 0; i < 20; i++)
            DrawRectangle(HX+20 + i*55, yOrtaKor + ortaKorH/2 - 2, 28, 5,
                (Color){180, 155, 0, 255});

        // ── UST-ALT BOLGE BUYUK KORIDOR ──
        DrawRectangle(HX, yKor2, HW, kor2H, COL_ROAD);
        for(int i = 0; i < 18; i++)
            DrawRectangle(HX+30 + i*60, yKor2 + kor2H/2 - 3, 38, 6, COL_ROAD_LINE);
        DrawText(">>", HX+50, yKor2+14, 20, (Color){255, 255, 200, 255});
        DrawText(">>", HX+HW/2-20, yKor2+14, 20, (Color){255, 255, 200, 255});
        DrawText(">>", HX+HW-100, yKor2+14, 20, (Color){255, 255, 200, 255});
        DrawRectangle(HX+HW-16, yKor2, 16, kor2H, COL_GIRIS);
        DrawText("GIR", HX+HW-15, yKor2+18, 10, WHITE);
        DrawRectangle(HX, yKor2, 16, kor2H, COL_CIKIS);
        DrawText("CIK", HX+1, yKor2+18, 10, WHITE);

        // ── ALT BLOKLAR IC KORIDOR ──
        DrawRectangle(HX, yAltOKor, HW, altOKorH, COL_ROAD);
        for(int i = 0; i < 20; i++)
            DrawRectangle(HX+20 + i*55, yAltOKor + altOKorH/2 - 2, 28, 5,
                (Color){180, 155, 0, 255});

        // ── ALT KORIDOR ──
        DrawRectangle(HX, yKor3, HW, HY+HH-yKor3, COL_ROAD);

        // ── 4 BLOK ALANLARI ──
        for(int b = 0; b < 4; b++) {
            int bx  = blokBaseX[b];
            int byU = blokBaseY[b];
            int byA = blokAltY[b];
            int sx  = bx + sutunW + icKor;
            char bl = blokIsim[b];

            // Blok arka plan ust
            DrawRectangle(bx-2, byU-16, blokW+4, PH+20, COL_BLOCK_BG);
            DrawRectangleLinesEx((Rectangle){bx-2, byU-16, blokW+4, PH+20}, 2,
                (Color){55, 90, 200, 255});
            // Blok arka plan alt
            DrawRectangle(bx-2, byA-2, blokW+4, PH+8, COL_BLOCK_BG);
            DrawRectangleLinesEx((Rectangle){bx-2, byA-2, blokW+4, PH+8}, 2,
                (Color){55, 90, 200, 255});

            // Ic koridor -- baslik altindan baslar
            DrawRectangle(bx + sutunW, byU, icKor, PH*2 + ortaKorH + 20, COL_INNER_KOR);
            DrawText("v", bx+sutunW+8, byU+6,  14, COL_TEXT_YELLOW);
            DrawText("v", bx+sutunW+8, byU+22, 14, COL_TEXT_YELLOW);
            DrawText("^", bx+sutunW+8, byA+6,  14, COL_TEXT_YELLOW);
            DrawText("^", bx+sutunW+8, byA+22, 14, COL_TEXT_YELLOW);

            // Bloklar arasi koridor
            if(b == 0 || b == 2) {
                int kx = bx + blokW + 2;
                DrawRectangle(kx, byU, araKor-4, PH*2 + ortaKorH + 20, COL_INNER_KOR);
                DrawText("v", kx+8, byU+12, 16, (Color){160, 160, 60, 255});
                DrawText("^", kx+8, byA+35, 16, (Color){160, 160, 60, 255});
            }

            // Blok etiketi -- EN SON cizilir, uzerine hicbir sey gelmez
            DrawRectangle(bx-2, byU-16, blokW+4, 16, COL_BLOCK_HDR);
            DrawRectangleLinesEx((Rectangle){bx-2, byU-16, blokW+4, 16}, 1,
                (Color){80, 120, 255, 255});
            char lbl[12];
            sprintf(lbl, "BLOK %c", bl);
            DrawText(lbl, bx + blokW/2 - 24, byU-13, 12, COL_TEXT_WHITE);
        }

        // ── PARK YERLERİ ──
        for(int i = 0; i < PARK_SAYISI; i++) {
            Color zemin = parklar[i].dolu ? COL_SLOT_DOLU : COL_SLOT_BOSH;
            DrawRectangleRounded(parklar[i].alan, 0.15f, 6, zemin);
            Color sinir = parklar[i].dolu ? COL_BORDER_DOLU : COL_BORDER_BOS;
            DrawRectangleLinesEx(parklar[i].alan, 2, sinir);

            // En yakin bos yanip sonme
            if(i == enYakinIndex && ((int)(GetTime()*2))%2 == 0) {
                DrawRectangleLinesEx(
                    (Rectangle){parklar[i].alan.x-4, parklar[i].alan.y-4,
                                 parklar[i].alan.width+8, parklar[i].alan.height+8},
                    3, COL_HIGHLIGHT);
            }

            // Arac
            if(parklar[i].dolu) {
                if(i < 8) {
                    // Yatay W sirasi
                    float x  = parklar[i].alan.x + 4;
                    float y  = parklar[i].alan.y + 4;
                    float cw = parklar[i].alan.width  - 8;
                    float ch = parklar[i].alan.height - 8;
                    DrawRectangleRounded((Rectangle){x+1,y+1,cw,ch}, 0.35f,6, COL_CAR_SHADOW);
                    DrawRectangleRounded((Rectangle){x,y,cw,ch}, 0.35f,6, COL_CAR_BODY);
                    DrawRectangleRounded((Rectangle){x+3,y+4,9,ch-8},0.3f,4, COL_CAR_GLASS);
                    DrawRectangleRounded((Rectangle){x+cw-12,y+4,9,ch-8},0.3f,4, COL_CAR_GLASS);
                    DrawCircle((int)(x+3),    (int)(y+3),    2, COL_HEADLIGHT);
                    DrawCircle((int)(x+cw-3), (int)(y+3),    2, COL_HEADLIGHT);
                    DrawCircle((int)(x+3),    (int)(y+ch+1), 2, COL_TAILLIGHT);
                    DrawCircle((int)(x+cw-3), (int)(y+ch+1), 2, COL_TAILLIGHT);
                    DrawRectangleRounded((Rectangle){x-3,y+5,4,9},0.3f,3, COL_WHEEL);
                    DrawRectangleRounded((Rectangle){x-3,y+ch-14,4,9},0.3f,3, COL_WHEEL);
                    DrawRectangleRounded((Rectangle){x+cw-1,y+5,4,9},0.3f,3, COL_WHEEL);
                    DrawRectangleRounded((Rectangle){x+cw-1,y+ch-14,4,9},0.3f,3, COL_WHEEL);
                } else {
                    AracCiz(parklar[i].alan, parklar[i].yukariMi);
                }
            }

            // Park numarasi
            int fs = (i < 8) ? 11 : 10;
            int tx = (i < 8)
                   ? (int)(parklar[i].alan.x + parklar[i].alan.width/2 - 9)
                   : (int)(parklar[i].alan.x + 3);
            int ty = (i < 8)
                   ? (int)(parklar[i].alan.y + parklar[i].alan.height/2 - 7)
                   : (int)(parklar[i].alan.y + 34);
            DrawText(parklar[i].isim, tx, ty, fs, (Color){255, 255, 255, 220});
        }

        // ── ALT CUBUK ──
        DrawRectangle(0, SH-42, SW, 42, (Color){20, 42, 100, 255});
        DrawRectangleLinesEx((Rectangle){0, SH-42, SW, 42}, 2, (Color){50, 100, 220, 255});
        DrawText(
            "Durum: Sistem Aktif  |  Tikla: Park durumu degistir  |  GIR >> Sag  |  CIK << Sol",
            22, SH-30, 15, (Color){190, 210, 255, 255});

        EndDrawing();
    }

    CloseWindow();
    return 0;
}