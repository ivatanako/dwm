/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 6;
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 0;        /* 1 = master at right*/
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 27;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int tag_padding        = 0;        
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const char *fonts[]          = {"Ubuntu:Regular:size=10", "Material Design Icons:Regular:pixelsize=16:antialias=true"};
static const char dmenufont[]       = "monospace:size=10";

static const char fore[]   = "#f8f8f2";
static const char back[]   = "#282a36"; 
static const char border[] = "#f8f8f2";
static const char col0[]   = "#000000";
static const char col1[]   = "#FF5555";
static const char col2[]   = "#50FA7B";
static const char col3[]   = "#F1FA8C";
static const char col4[]   = "#BD93F9";
static const char col5[]   = "#FF79C6";
static const char col6[]   = "#8BE9FD";
static const char col7[]   = "#BFBFBF";
static const char col8[]   = "#4D4D4D";
static const char col9[]   = "#FF6E67";
static const char col10[]  = "#5AF78E";
static const char col11[]  = "#F4F99D";
static const char col12[]  = "#CAA9FA";
static const char col13[]  = "#FF92D0";
static const char col14[]  = "#9AEDFE";
static const char col15[]  = "#E6E6E6";

static const char spotify[]= "#1FC167";
 

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]     = { fore,      back,      back   }, // \x0b
	[SchemeSel]      = { fore,      back,      border }, // \x0c
	[SchemeStatus]   = { fore,      back,      border }, // \x0d  Statusbar right 
	[SchemeTagsSel]  = { col4,      back,      border }, // \x0e  Tagbar left selected 
        [SchemeTagsNorm] = { fore,      back,      border }, // \x0f  Tagbar left unselected 
        [SchemeInfoSel]  = { fore,      back,      border }, // \x10  infobar middle  selected 
        [SchemeInfoNorm] = { fore,      back,      border }, // \x11  infobar middle  unselected 
	[SchemeCol1]     = { fore,      back,      col0   }, // \x12 
	[SchemeCol2]     = { fore,      back,      col0   }, // \x13
	[SchemeCol3]     = { fore,      back,      col0   }, // \x14 
	[SchemeCol4]     = { fore,      back,      col0   }, // \x15
	[SchemeCol5]     = { fore,      back,      col0   }, // \x16 
	[SchemeCol6]     = { fore,      back,      col0   }, // \x17
	[SchemeCol7]     = { fore,      back,      col0   }, // \x18
	[SchemeCol8]     = { fore,      back,      col0   }, // \x19
	[SchemeCol9]     = { fore,      back,      col0   }, // \x1a
	[SchemeCol10]    = { back,      col10,      col0   }, // \x1b
	[SchemeCol11]    = { back,      col11,      col0   }, // \x1c 
	[SchemeCol12]    = { fore,      back,   col0   }, // \x1d Spotify
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4"};
//static const char *alttags[] = { "󰄯", "󰄯", "󰄯", "󰄯"};

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
	{ "Spotify",       NULL,       NULL,       5,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "󰙀",      tile },    /* first entry is default */
 	{ "󰕴",      dwindle },
	{ "󰋁",      grid },
	{ "󱒅",      centeredmaster },
	{ "󰕬",      centeredfloatingmaster },
	{ "[M]",      monocle },
	{ "[D]",      deck },
	{ NULL, NULL },
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
		     { MODKEY,                       XK_0,      setlayout,      {.v = &layouts[2]} }, /*Grid*/
		     { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, /*ventana enfocada en todos los tags*/
		     { MODKEY|ShiftMask,             XK_o,      winview,        {0} }, // Ir al tag de la ventana enfocada
		     { MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[0]} }, /*tiled*/
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
		     { MODKEY|Mod1Mask,              XK_f,      setlayout,      {.v = &layouts[1]} }, /*Spiral*/
		     { MODKEY|Mod1Mask,              XK_g,      setlayout,      {.v = &layouts[2]} }, /*Grid*/
		     { MODKEY|Mod1Mask,              XK_c,      setlayout,      {.v = &layouts[3]} }, /*center*/
		     { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[5]} }, /*monocle*/
		     { MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[6]} }, /*Deck*/
		     { MODKEY,                       XK_s,      togglefloating, {0} }, /*float*/
		     { MODKEY,			     XK_F11,    togglefullscr,  {0} }, /*Fullscreen*/
		     { MODKEY|Mod1Mask,              XK_comma,  cyclelayout,    {.i = -1 } }, /*Ciclar layouts*/
		     { MODKEY|Mod1Mask,              XK_period, cyclelayout,    {.i = +1 } }, /*Ciclar layouts*/

		     /*Monitores*/
		     { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, /*Enfocar siguiente monitor*/
		     { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, /*Enfocar siguiente monitor*/
		     { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, /*Mandar ventana a monitor anterior*/
		     { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, /*Mandar ventana a monitor siguiente*/

		     /* dwm especifico*/
		     { MODKEY,                       XK_b,      togglebar,      {0} }, /*Activar o desactivar panel*/
                     { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
                     { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
                     { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,      {.i = +1 } },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[5]} },
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


