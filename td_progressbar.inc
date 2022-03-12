#include <YSI_Coding\y_hooks>

#if defined progress_included
	#endinput
#endif
#define progress_included

forward public OnPlayerCompleteProgressBar(playerid);

static Text:TD_ProgressBar_Global,
		PlayerText:TD_ProgressBar_Player[MAX_PLAYERS][2];

hook OnGameModeInit()
{
	TD_ProgressBar_Global = TextDrawCreate(226.199966, 338.679992, "LD_SPAC:white");
	TextDrawLetterSize(TD_ProgressBar_Global, 0.000000, 0.000000);
	TextDrawTextSize(TD_ProgressBar_Global, 207.000000, 34.000000);
	TextDrawAlignment(TD_ProgressBar_Global, 1);
	TextDrawColor(TD_ProgressBar_Global, 255);
	TextDrawSetShadow(TD_ProgressBar_Global, 0);
	TextDrawSetOutline(TD_ProgressBar_Global, 0);
	TextDrawBackgroundColor(TD_ProgressBar_Global, 255);
	TextDrawFont(TD_ProgressBar_Global, 4);
	TextDrawSetProportional(TD_ProgressBar_Global, 0);
	TextDrawSetShadow(TD_ProgressBar_Global, 0);
}

hook OnPlayerDeath(playerid, killerid, reason) return ResetVariable_ProgressBar(playerid);
hook OnPlayerDisconnect(playerid, reason) return ResetVariable_ProgressBar(playerid);

stock ProgressBar_Create(playerid, steps, const text[])
{
	for(new i = 0; i < 2; i++)
    {
        if(TD_ProgressBar_Player[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawHide(playerid, TD_ProgressBar_Player[playerid][i]);
            PlayerTextDrawDestroy(playerid, TD_ProgressBar_Player[playerid][i]);
            TD_ProgressBar_Player[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        } 
    }

	TD_ProgressBar_Player[playerid][0] = CreatePlayerTextDraw(playerid, 227.399978, 340.173309, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, TD_ProgressBar_Player[playerid][0], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, TD_ProgressBar_Player[playerid][0], 0.000000, 30.580013); // X = 204.479187
    PlayerTextDrawAlignment(playerid, TD_ProgressBar_Player[playerid][0], 1);
    PlayerTextDrawColor(playerid, TD_ProgressBar_Player[playerid][0], 8388863);
    PlayerTextDrawSetShadow(playerid, TD_ProgressBar_Player[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, TD_ProgressBar_Player[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, TD_ProgressBar_Player[playerid][0], 255);
    PlayerTextDrawFont(playerid, TD_ProgressBar_Player[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, TD_ProgressBar_Player[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, TD_ProgressBar_Player[playerid][0], 0);

    TD_ProgressBar_Player[playerid][1] = CreatePlayerTextDraw(playerid, 331.200012, 343.813354, "_");
    PlayerTextDrawLetterSize(playerid, TD_ProgressBar_Player[playerid][1], 0.261599, 1.256533);
    PlayerTextDrawAlignment(playerid, TD_ProgressBar_Player[playerid][1], 2);
    PlayerTextDrawColor(playerid, TD_ProgressBar_Player[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, TD_ProgressBar_Player[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, TD_ProgressBar_Player[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, TD_ProgressBar_Player[playerid][1], 255);
    PlayerTextDrawFont(playerid, TD_ProgressBar_Player[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, TD_ProgressBar_Player[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, TD_ProgressBar_Player[playerid][1], 0);

	SetPVarString(playerid, "ProgressBar_Text", text);
	TextDrawShowForPlayer(playerid, TD_ProgressBar_Global);
	SetPVarInt(playerid, "ProgressBar_Timer", SetTimerEx("ProgressBar_Loading", 100, false, "iii", playerid, 0, steps));
	DeletePVar(playerid, "ProgressBar_X");
	return 1;
}

stock IsPlayerProgressBar(playerid)
{
	if(GetPVarInt(playerid, "ProgressBar_Timer")) return true;
	return false;
}

stock ResetVariable_ProgressBar(playerid)
{
	for(new i = 0; i < 2; i++)
	{
		if(TD_ProgressBar_Player[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, TD_ProgressBar_Player[playerid][i]);
			PlayerTextDrawDestroy(playerid, TD_ProgressBar_Player[playerid][i]);
			TD_ProgressBar_Player[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	KillTimer(GetPVarInt(playerid, "ProgressBar_Timer"));
	DeletePVar(playerid, "ProgressBar_Timer");
	DeletePVar(playerid, "ProgressBar_X");
	DeletePVar(playerid, "ProgressBar_Text");
	return 1;
}

forward ProgressBar_Loading(playerid, stockid, steps);
public ProgressBar_Loading(playerid, stockid, steps)
{
	new Float:Chart_X = GetPVarFloat(playerid, "ProgressBar_X");
	if(Chart_X == 204.479187)
	{
		ResetVariable_ProgressBar(playerid);
		TextDrawHideForPlayer(playerid, TD_ProgressBar_Global);
		return CallLocalFunction("OnPlayerCompleteProgressBar", "i", playerid);
	}
	else
	{
		Chart_X = (204.479187/steps)*stockid;
		stockid++;
		SetPVarFloat(playerid, "ProgressBar_X", Chart_X);
		PlayerTextDrawTextSize(playerid, TD_ProgressBar_Player[playerid][0], Chart_X, 30.580013);
	}

	new text[128];
	GetPVarString(playerid, "ProgressBar_Text", text, sizeof(text));
	PlayerTextDrawSetString(playerid, TD_ProgressBar_Player[playerid][1], text);

	PlayerTextDrawShow(playerid, TD_ProgressBar_Player[playerid][0]);
	PlayerTextDrawShow(playerid, TD_ProgressBar_Player[playerid][1]);
	KillTimer(GetPVarInt(playerid, "ProgressBar_Timer"));
	SetPVarInt(playerid, "ProgressBar_Timer", SetTimerEx("ProgressBar_Loading", 100, false, "iii", playerid, stockid, steps));
	return 1;
}
