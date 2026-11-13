Commands that can be currently used to check things out:
- just clean
- just build release
- just run release
- just build debug
- just run debug
- gdb ./build/{{preset}}/kestrel where preset = release/debug (to start the debugger)

Add breakpoint:
Suppose you want to add a breakpoint at: line of  cpp/itch_stat/src/itch_stat_json.cpp file
use command  - break cpp/itch_stat/src/itch_stat_json.cpp:101

Load breakpoint from file bp.txt:
Enter the debugger shell and use the command - source bp.txt to load the breakpoints

How the ITCH stat results are shown in JSON format (with each message type frequency displayed as values)
!(screenshots/itch_stat_json.png)[Itch Stat Json display]
