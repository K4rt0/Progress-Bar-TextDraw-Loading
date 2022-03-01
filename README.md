# Installation
Write include in your code:
```
#include <td_progressbar>
```
# Usage
```
ProgressBar_Create(playerid, steps, const text);

public OnPlayerCompleteProgressBar(playerid)
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
```
# Note
```
steps = speed
```
