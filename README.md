# Installation
Write include in your code:
```
#include <td_progressbar>
```
# Usage
```
ProgressBar_Create(playerid, steps, const text);

public OnPlayerCompleteProgressBar(playerid)

IsValidProgressBar(playerid)
```
# Example
```
public OnPlayerConnect(playerid)
{
	ProgressBar_Create(playerid, 100, "Loading...");
	return 1;
}
public OnPlayerCompleteProgressBar(playerid)
{
	SendClientMessage(playerid, 0xFFFFFFFF, "ProgressBar Status: Finish.");
	return 1;
}

CMD:checkprogressbar(playerid)
{
	if(IsValidProgressBar(playerid)) SendClientMessage(playerid, 0xFFFFFFFF, "ProgressBar: Valid");
	else SendClientMessage(playerid, 0xFFFFFFFF, "ProgressBar: Unvalid");
	return 1;
}
```
# Note
```
steps = speed
During you use IsValidProgressBar(playerid) if it returns 1 then progress bar valid and return 0 then progress bar not valid.
```
