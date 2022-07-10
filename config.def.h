/* See LICENSE file for copyright and license details. */

/* def */
#define WEBBROWSER		"google-chrome-stable"
#define TERMINAL		"alacritty"
#define SCREENSHOT		"spectacle"
#define GUI_FILEMANAGER	        "dolphin"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps size between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11", "Noto Color Emoji:size=11", "Nerd Font Mono:weight=bold:size=15:antialias=true:hinting=true" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_1[]       = "#282c34"; // Background color of bar
static const char col_2[]       = "#282c34"; // Background color of unfocused windows border 
static const char col_3[]       = "#d7d7d7";
static const char col_4[]       = "#018858"; // Background color of focused windows border and tags (main color acent)
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_3, col_1, col_2 },
	[SchemeSel]  = { col_3, col_4,  col_4  },
};
// Autostart programs
static const char *const autostart[] = {
    // Start my build of slstatus
    "slstatus", NULL,
    // Keyboard layouts switch (requires setxkbmap)
    "setxkbmap", "-model", "pc101", "-layout", "us,ar", "-variant", ",,", "-option", "grp:win_space_toggle", NULL,
    "picom", NULL, // Start compositor , for transparency
    "nitrogen", "--restore", NULL, // Restores the wallpaper
     NULL /* terminate */
 };

/* tagging */
// static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ WEBBROWSER, NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Plasma",   NULL,       "Plasma",       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask // win/super key

#define TAGKEYS(KEY,TAG) \
	{1, {{MODKEY,                        KEY}},      view,           {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask,            KEY}},      toggleview,     {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask,              KEY}},      tag,            {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask,  KEY}},      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_1, "-nf", col_3, "-sb", col_4, "-sf", col_1, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include "movestack.c"
// X11 keysym definitions
#include <X11/XF86keysym.h> // req (libxinerama1 and libxinerama-dev)
static Keychord keychords[] = {
	/* modifier                     key        function        argument */
	/* ---------------------------------- Apps Keys ---------------------------------- */
	// Dmenu (launcher)
	{1, {{MODKEY|ShiftMask,             XK_d}},      spawn,                  {.v = dmenucmd } },
	// Rofi launcher (small)
	{1, {{MODKEY|ShiftMask|ControlMask, XK_d}},      spawn,                  SHCMD("rofi -show drun") }, 
	// Start the terminal
	{1, {{MODKEY,                       XK_Return}}, spawn,                  {.v = termcmd } },
	// Start the terminal with tmux
	{2, {{MODKEY, XK_t},                {0, XK_1}},      spawn,           SHCMD(TERMINAL " -e tmux")  },
	// File browsers
	{2, {{MODKEY|ShiftMask, XK_f},      {0, XK_g}},     spawn,           SHCMD(GUI_FILEMANAGER) },
	// Rofi file browser (small)
        {2, {{MODKEY|ShiftMask, XK_f},      {0, XK_r}},     spawn,           SHCMD("rofi -show filebrowser") },
	/************************************* Start the web browers *************************************/
        // Google chrome stable
	{2, {{MODKEY, XK_w},                {0, XK_g}},     spawn,           SHCMD(WEBBROWSER) },
        // Tor brower
	{2, {{MODKEY, XK_w},                {0, XK_t}},     spawn,           SHCMD("tor-browser") },
	/************************************* Start the caht/email apps *************************************/
	// Discord
	{2, {{MODKEY, XK_c},                {0, XK_d}},      spawn,           SHCMD("discord") },
	/************************************* Start the dev apps *************************************/
	// Jetbrains toolbox
	{2, {{MODKEY, XK_a},                {0, XK_j}},     spawn,         SHCMD("jetbrains-toolbox") },
        // NeoVim
	{2, {{MODKEY, XK_a},                {0, XK_n}},     spawn,         SHCMD(TERMINAL "-e nvim") },
        // Vim
	{2, {{MODKEY, XK_a},                {0, XK_v}},     spawn,         SHCMD(TERMINAL "-e vim") },
	/************************************* Start the emoji piker apps *************************************/
	// Emoji selector (rofi)
	{1, {{Mod4Mask,                    XK_e}},    spawn,          SHCMD("rofi -show emoji") },
	/************************************* dwm keys *************************************/
	// Full screen mode
	{1, {{MODKEY,			XK_f}},      fullscreen,     {0} },
	// Toggle the slstatus bar (hide/show)
	{1, {{MODKEY,                   XK_b}},      togglebar,      {0} },
        // Change the focus
	{1, {{MODKEY,                   XK_j}},      focusstack,     {.i = +1 } },
	{1, {{MODKEY,                   XK_k}},      focusstack,     {.i = -1 } },
        // Change the stack layout (horizontal/virtecal)
	{1, {{MODKEY,                   XK_i}},      incnmaster,     {.i = +1 } },
	{1, {{MODKEY,                   XK_d}},      incnmaster,     {.i = -1 } },
        // Change the focus window size (in the tile mode)
	{1, {{MODKEY,                   XK_h}},      setmfact,       {.f = -0.05} },
	{1, {{MODKEY,                   XK_l}},      setmfact,       {.f = +0.05} },
//	{ MODKEY,                       XK_Return, zoom,           {0} },
	{1, {{MODKEY,                   XK_Tab}},    view,           {0} },

	{1, {{MODKEY|ShiftMask,         XK_j}},      movestack,      {.i = +1 } }, 
	{1, {{MODKEY|ShiftMask,          XK_k}},      movestack,      {.i = -1 } }, 
    
	// Quit from the foucsed window (kill)
	{2, {{MODKEY, XK_q},            {0, XK_q}},      killclient,     {0} },
        /************************* Switch between layouts *************************/
	// Tiled layout
	{2, {{MODKEY, XK_s},           {0, XK_t}},      setlayout,      {.v = &layouts[0]} },
	// Floating layout
	{2, {{MODKEY, XK_s},           {0, XK_f}},      setlayout,      {.v = &layouts[1]} },
	// Monocle layout
	{2, {{MODKEY, XK_s},           {0, XK_m}},      setlayout,      {.v = &layouts[2]} },
        // Grid layout
	{2, {{MODKEY, XK_s},           {0, XK_g}},      setlayout,      {.v = &layouts[3]} },

        // Toggle between current layout and tile layout  
	{2, {{MODKEY, XK_s},             {0, XK_space}},  setlayout,      {0} },
        // Toggle floating window
	{1, {{MODKEY|Mod1Mask,           XK_f}},        togglefloating,     {0} },
        // View all tags
	{1, {{MODKEY,                    XK_0}},        view,           {.ui = ~0 } },
        // Mirror the current tagg in all tags
	{1, {{MODKEY|ShiftMask,          XK_0}},        tag,            {.ui = ~0 } },
        // I don't know
	{1, {{MODKEY,                    XK_comma}},    focusmon,       {.i = -1 } },
	{1, {{MODKEY,                    XK_period}},   focusmon,       {.i = +1 } },
	{1, {{MODKEY|ShiftMask,          XK_comma}},    tagmon,         {.i = -1 } },
	{1, {{MODKEY|ShiftMask,          XK_period}},   tagmon,         {.i = +1 } },
        /************************* Tag keys *************************/
	TAGKEYS(                         XK_1,                      0)
	TAGKEYS(                         XK_2,                      1)
	TAGKEYS(                         XK_3,                      2)
	TAGKEYS(                         XK_4,                      3)
	TAGKEYS(                         XK_5,                      4)
	TAGKEYS(                         XK_6,                      5)
	TAGKEYS(                         XK_7,                      6)
	TAGKEYS(                         XK_8,                      7)
	TAGKEYS(                         XK_9,                      8)
	// Kill dwm (super + shift + alt + q)
	{1, {{MODKEY|ShiftMask|Mod1Mask,       XK_q}},      quit,           {0} },
	/* ---------------------------------- Control Keys ---------------------------------- */
	// Brightness controllers (requires xbacklight)
	{1, {{0,                               XF86XK_MonBrightnessUp}},   spawn, SHCMD("xbacklight -inc 5") },
	{1, {{0,                               XF86XK_MonBrightnessDown}}, spawn, SHCMD("xbacklight -dec 5") },
	// Sound controllers (requires pamixer)
	{1, {{0,                               XF86XK_AudioRaiseVolume}}, spawn, SHCMD("pamixer --allow-boost -i 4") },
	{1, {{0,                               XF86XK_AudioLowerVolume}}, spawn, SHCMD("pamixer --allow-boost -d 4") },
	{1, {{0,                               XF86XK_AudioMute}},        spawn, SHCMD("pamixer -t") },
	// Media controls (requires playerctl)
	{1, {{0,                               XF86XK_AudioPlay}},	 spawn,	SHCMD("playerctl play-pause") },
	{1, {{0,                               XF86XK_AudioStop}},       spawn, SHCMD("playerctl stop") },
	{1, {{0,                               XF86XK_AudioNext}},	 spawn,	SHCMD("playerctl next") },
	{1, {{0,                               XF86XK_AudioPrev}},	 spawn,	SHCMD("playerctl previous")  },
        // Mute and unmute mic
	{1, {{0,			       XF86XK_AudioMicMute}},	spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	// Take a screenshot
	{1, {{0,			       XK_Print}},		spawn, SHCMD(SCREENSHOT) },
	/* ---------------------------------- lock Keys ---------------------------------- */
	// Lock the screen
	{1, {{MODKEY|ShiftMask,    	       XK_x}},     spawn,          SHCMD("betterlockscreen -l dim") },
	// Plasma screen lock (super + ctrl + shift + x)
	{1, {{MODKEY|ShiftMask|ControlMask,    XK_x}},     spawn,          SHCMD("qdbus-qt5 org.kde.ksmserver /KSMServer org.kde.KSMServerInterface.logout -1 -1 -1") }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

