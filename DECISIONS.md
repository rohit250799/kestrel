Itch stat:

In the class (Itch_Stat_JSON):
- using unsigned int for total_messages since value can be pretty high and min 4 bytes is required
- using std::array with capacity = 6 and each index storing a uint8_t element for timestamps since in NASDAQ ITCH, they require 6 bytes and timestamp value = nanoseconds since midnight
- first opening the binary file and getting the file descriptor and using that descriptor to mmap the binary file
- since every message is preceded by a 2-byte big-endian length, extracting the first 2 bytes of every message and converting / decoding it to little endian format. If the 
little endian format length matches with that of any message type (stored in the unordered_set), then the message is valid. Else, its an anomaly and anomaly count is incremented by 1
- for storing the frequency of each acceptable message type, using a fixed_size array (26) and mapping each index to the character number in English (like A = 0, B = 1 and so on.. )
The following character codes represent unacceptable message_types:'G', 'M', 'T' and 'Z' - so, in the array, initializing their value with a sentinel = -1 and the remaining indexes are initialized to 0 
 
- if the length of the message is valid, we would have to check whether this particular message type exists in the array (condition: the message's first byte character mapped index in the array should be >= 0). 
If it does, increment the value of that particular index. Else, increment the anomaly count, total message count, total bytes etc. and move to the next message's length.

- fixed the timestamps issue in ITCH Stat JSON - in all message types, the fourth element in message body is timestamp. Timstamp is encoded in Big-endian format and each timestamp consumes 6 bytes. The bytes are stored in a fixed size array inside the class by member variables as uint8_t types. Once the bytes are selected, they are sent to the decode_big_endian_message_timestamp function which reconstructs a 48-bit timstamp as a uint64_t value and returns it. There is no need to mask the upper bits exclusively since the function constructs the correct numerical value from big-endian bytes. The compiler and platform handle its in-memory representation. Using the biggest and smallest possible sentinel values for the first and last timestamps respectively to help with the comparison and at the end of the loop, passing the uint64_t values of first and last timestamps to the JSON conversion function before its printed to the screen

- Total messages number is significantly higher than what the individual message types sum up to since there are multiple unacceptable messages 
with varying lengths which have not been considered into the calculation
