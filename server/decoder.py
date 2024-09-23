
import socket
import json
import os
from itertools import repeat, compress, groupby
from itertools import chain, repeat, islice

def rle_decodee(encoded):
    result = []
    # This will create an iterator over the encoded string
    it = iter(encoded)

    # Loop through the encoded string in pairs
    while True:
        try:
            # Get the count (digits)
            count_str = ''
            while True:
                char = next(it)
                if char.isdigit():
                    count_str += char
                else:
                    # When we find a non-digit, we've reached the end of the count
                    break
            
            count = int(count_str)  # Convert count to an integer
            
            # Append the character repeated 'count' times to the result
            result.append(char * count)

        except StopIteration:
            # Break the loop if we've exhausted the iterator
            break

    return ''.join(result)


decoded_content = rle_decodee("12W1B12W3B24W1B14W")
print(decoded_content)  # This should show the expanded version of the string
