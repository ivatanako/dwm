/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 6;
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 0;        /* 1 = master at right*/
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"JetBrains Mono:Regular:size=9", "Material Design Icons:Regular:pixelsize=16:antialias:true"};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#282a36";
static const char col_gray2[]       = "#ff5555";
static const char col_gray3[]       = "#f8f8f2";
static const char col_gray4[]       = "#689d6a";
static const char col_cyan[]        = "#4d4d4d";
static const char col1[]            = "#ffffff";
static const char col2[]            = "#ffffff";
static const char col3[]            = "#ffffff";
static const char col4[]            = "#ffffff";
static const char col5[]            = "#ffffff";
static const char col6[]            = "#ffffff";
static const char col7[]            = "#ffffff";
static const char col8[]            = "#ffffff";
static const char col9[]            = "#ffffff";
static const char col10[]           = "#ffffff";
static const char col11[]           = "#ffffff";
static const char col12[]           = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]   = { col_gray4, col_gray1,  col_cyan  },
	[SchemeCol1]  = { col1,      col_gray1, col_gray2 },
	[SchemeCol2]  = { col2,      col_gray1, col_gray2 },
	[SchemeCol3]  = { col3,      col_gray1, col_gray2 },
	[SchemeCol4]  = { col4,      col_gray1, col_gray2 },
	[SchemeCol5]  = { col5,      col_gray1, col_gray2 },
	[SchemeCol6]  = { col6,      col_gray1, col_gray2 },
	[SchemeCol7]  = { col7,      col_gray1, col_gray2 },
	[SchemeCol8]  = { col8,      col_gray1, col_gray2 },
	[SchemeCol9]  = { col8,      col_gray1, col_gray2 },
	[SchemeCol10] = { col10,     col_gray1, col_gray2 },
	[SchemeCol11] = { col11,     col_gray1, col_gray2 },
	[SchemeCol12] = { col12,     col_gray1, col_gray2 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance    title       tags mask     isfloating   monitor */
	{ "Gimp",          NULL,       NULL,       0,            1,           -1 },
	{ "mpv",           NULL,       NULL,       0,            1,           -1 },
	{ "Lxappareance",  NULL,       NULL,       0,            1,           -1 },
	{ "Pavucontrol",   NULL,       NULL,       0,            1,           -1 },
	{ "qt5ct",         NULL,       NULL,       0,            1,           -1 },
	{ "Gucharmap",     NULL,       NULL,       0,            1,           -1 },
	{ "Sxiv",          NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "󰕲",      tile },    /* first entry is default */
 	{ "󰕴",      dwindle },
	{ "󰹪",      grid },
	{ "󱒅",      centeredmaster },
	{ "󰕬",      centeredfloatingmaster },
	{ "[M]",      monocle },
	{ "[D]",      deck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,		KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggletag,      {.ui = 1 << TAG} },

/* COSAS QUE TENGO QUE AVERIGUAR COMO QUITAR */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

#include "movestack.c"
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
		     /* Movimiento de ventanas */
		     { MODKEY|ShiftMask,             XK_q,      killclient,     {0} }, /*Matar ventana*/
		     { MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, /*Enfocar siguiente ventana*/
		     { MODKEY,                       XK_k,      focusstack,     {.i = -1 } }, /*Enfocar anterior ventana*/
		     { MODKEY|ControlMask,           XK_j,      inplacerotate,  {.i = +1} }, /*Enfocar siguiente ventana sin cambiar con master (usar con deck)*/
		     { MODKEY|ControlMask,           XK_k,      inplacerotate,  {.i = -1} }, /*Enfocar anterior ventana sin cambiar con master (usar con deck)*/
		     { MODKEY,                       XK_bar,    togglermaster,  {0} }, /*Cambiar master al lado derecho y viceversa */
		     { MODKEY|ShiftMask,             XK_g,      zoom,           {0} }, /*mandar ventana a master*/
		     { MODKEY,                       XK_g,      switchcol,    {0} }, /*Cambiar foco entre stack y master*/
		     { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} }, /*Hacer más pequeño master*/
		     { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} }, /*Hacer más grande master*/
		     { MODKEY|ControlMask,           XK_comma,  incnmaster,     {.i = +1 } }, /*Incrementar master*/
		     { MODKEY|ControlMask,           XK_period, incnmaster,     {.i = -1 } }, /*Disminuir master*/
		     { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } }, /*Mover ventana hacia abajo*/
		     { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } }, /*Mover ventana hacia arriba*/

		     /* Tags*/
		     { MODKEY,                       XK_Tab,    view,           {0} }, /*tag anterior*/
		     { MODKEY,                       XK_0,      view,           {.ui = ~0 } }, /*ver todos los tags a la vez*/
		     { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, /*ventana enfocada en todos los tags*/
		     { MODKEY|ControlMask,           XK_l,      shiftview,  { .i = +1 } }, /*Ver siguiente tag*/
		     { MODKEY|ControlMask,           XK_h,      shiftview,  { .i = -1 } }, /*Ver tag anterior*/
		     TAGKEYS(                        XK_1,                      0) /*Enfocar tag 1*/ 
		     TAGKEYS(                        XK_2,                      1) /*Enfocar tag 2*/
		     TAGKEYS(                        XK_3,                      2) /*Enfocar tag 3*/
		     TAGKEYS(                        XK_4,                      3) /*Enfocar tag 4*/
		     TAGKEYS(                        XK_5,                      4) /*Enfocar tag 5*/
		     TAGKEYS(                        XK_6,                      5) /*Enfocar tag 6*/
		     TAGKEYS(                        XK_7,                      6) /*Enfocar tag 7*/
		     TAGKEYS(                        XK_8,                      7) /*Enfocar tag 8*/
		     TAGKEYS(                        XK_9,                      8) /*Enfocar tag 9*/

		     /*Layouts*/
		     { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /*tiled*/
		     { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[5]} }, /*monocle*/
		     { MODKEY,                       XK_s,      togglefloating, {0} }, /*float*/
		     { MODKEY,			     XK_F11,    togglefullscr,  {0} }, /*Fullscreen*/
		     { MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[6]} }, /*Deck*/
		     { MODKEY|Mod1Mask,              XK_space,  cyclelayout,    {.i = +1 } }, /*Ciclar layouts*/

		     /*Monitores*/
		     { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, /*Enfocar siguiente monitor*/
		     { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, /*Enfocar siguiente monitor*/
		     { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, /*Mandar ventana a monitor anterior*/
		     { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, /*Mandar ventana a monitor siguiente*/

		     /* dwm especifico*/
		     { MODKEY,                       XK_b,      togglebar,      {0} }, /*Activar o desactivar panel*/
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


