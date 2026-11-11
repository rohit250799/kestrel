Itch stat:

In the class (Itch_Stat_JSON):
- using unsigned long for total_messages since value can be pretty high and min 4 bytes is guaranteed
- using long long for timestamps since in NASDAQ ITCH, they require 6 bytes
- for count per message type, using an unordered_map since the dataset is large, max speed needed (O(1)) and only having simple dictionary lookups with key type = char
- first opening the binary file and getting the file descriptor and using that descriptor to mmap the binary file
- since every message is preceded by a 2-byte big-endian length, extracting the first 2 bytes of every message and converting / decoding it to little endian format. If the 
little endian format length matches with that of any message type (stored in the unordered_set), then the message is valid. Else, its an anomaly and anomaly count is incremented by 1 
