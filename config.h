/* See LICENSE file for copyright and license details. */

#define OPAQUE 0xffU

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const int swallowfloating    = 0;	    /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* fonts */
static const char *fonts[]    = { "terminus:size=14" };
static const char dmenufont[] = "terminus:size=14";

/* static const char *fonts[]          = { "monospace:size=10", */
/*                                         "Noto Sans CJK JP:size=10" }; */
/* static const char dmenufont[]       = "monospace:size=10"; */

/* colors */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";	/* highlight color inside */
static const char col_cyan[]        = "#8dbf7c";	/* highlight color outside  */

/* teal: #707780 */
/* brown: #8dbf7c */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* transparency values for bar and borders */
static const unsigned int alphas[][3]      = {
	/*               fg      bg      border     */
	[SchemeNorm] = { OPAQUE, OPAQUE, OPAQUE },
	[SchemeSel]  = { OPAQUE, OPAQUE, OPAQUE },
};

/* volume control */
static const char *upvol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *downvol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutevol[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

/* tagging */
/* static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" }; */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       tags mask     isfloating   isterminal	noswallow	monitor */
	{ "Gimp",     		NULL,       NULL,       0,            1,           0,	    	    0,		    -1 },
	{ "Firefox",  		NULL,       NULL,       1 << 8,       0,           0,          -1,		    -1 },
	{ "st-256color",	NULL,       NULL,       0,	          0,           1,           0,		    -1 },	
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *flamecmd[] = { "flameshot", "gui", NULL };

/* scripts */
static const char *pdfmenu[] = { "/home/karl/git/scripts/pdfmenu.sh", NULL };
static const char *sysmenu[] = { "/home/karl/git/scripts/sysmenu.sh", NULL };
static const char *project[] = { "/home/karl/git/scripts/project.sh", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY,                       XK_s,      spawn,          {.v = flamecmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                      XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY, 	                    XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,			                  XK_minus,  zoom,  	       {0} },
	{ MODKEY,			                  XK_plus,   zoom,  	       {0} },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_plus,   setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
  { MODKEY|ShiftMask,             XK_Return, setmfact,       {.f = 0.55} },
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
  { MODKEY|ControlMask,           XK_plus,   spawn,          {.v = upvol   } },
  { MODKEY|ControlMask,           XK_minus,  spawn,          {.v = downvol } },
  { MODKEY|ControlMask,           XK_m,      spawn,          {.v = mutevol } },
  { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = pdfmenu } },
  { MODKEY|ControlMask,           XK_k,      spawn,          {.v = sysmenu } },
  { MODKEY|ControlMask,           XK_p,      spawn,          {.v = project } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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
