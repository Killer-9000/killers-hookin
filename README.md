
# Killer-Hookin

Killer-Hookin is a library that has the goal of improving the World Of Warcraft;
Wrath Of The Lich King 3.3.5 client. This includes improvements added by newer versions
such as; streaming, hotfixes, map phasing, etc.

## Features

> Hotfixes
>> Hotfixes allow for DBC data to be loaded from the server; this intern allows for data to
   be updated mid-game.

> MapLiveView
>> Map live view (don't know what to call it) allows for live updating, designed for usage
   with a map editor such as noggit.

> Map Phases
>> Map phasing allowes for Cataclysm style phasing, where physical map chunks can be
   replaced allowing for visual change to the terrain. e.g. Gilneas flooding when
   the worgen start leveling.

> Streaming
>> Streaming allows for Cataclysm style archive loading, where files can be streamed from
   a storage server, this allows for data in multiple clients to be synchronized.

## Files structure

> src
>> [Other]
>>- Any third party code used by the library.
>>>
>> KillerHooking
>>- Contains all the library code.
>>> Common
>>>- Common codes used by most of the library.
>>>
>>> Features
>>>
>>>- Different Features code.
>>>
>>> Hooking
>>>- Client Hooking code.

## Code style

> Any way you want, as long as it follows my very specific and extensive list of rules.
