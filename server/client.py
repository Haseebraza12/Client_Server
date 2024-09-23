import socket
import json
import os
from itertools import repeat, compress, groupby
from itertools import chain, repeat, islice


BUFFER_SIZE = 10240
PORT = 8080

DOWNLOAD_DIR = "downloaded_files"  # Define the download directory


def rle_encodee(iterable):
    result = []
    for k, g in groupby(iterable):
        count = len(list(g))
        result.append(f"{count}{k}")
    return ''.join(result)

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



def upload_file(sock, filename):
    try:
        with open(filename, 'r') as file:
            file_content = file.read()

        # Encode file content using RLE
        encoded_content = ''.join(rle_encodee(file_content))

        # Prepare the JSON object
        json_data = json.dumps({
            "filename": filename,
            "file_content": encoded_content
        })

        # Send the JSON object
        sock.sendall(json_data.encode())
        print(f"File '{filename}' uploaded successfully.")

    except FileNotFoundError:
        print(f"File '{filename}' not found.")



def download_file(sock, filename):
    try:
        if not os.path.exists(DOWNLOAD_DIR):
            os.makedirs(DOWNLOAD_DIR)

        request = json.dumps({"action": "download", "filename": filename})
        sock.sendall(request.encode())

        json_data = sock.recv(BUFFER_SIZE).decode()
        file_data = json.loads(json_data)
        # Decode the received file content using RLE
        encoded_content = file_data['file_content'].strip('.txt')
        #decoded_content = rle_decodee(encoded_content)

        
        # Decode the received file content using RLE
        decoded_content = ''.join(rle_decodee(encoded_content))

        file_path = os.path.join(DOWNLOAD_DIR, file_data['filename'])

        with open(file_path, 'w') as file:
            file.write(decoded_content)

        print(f"File '{file_data['filename']}' downloaded successfully to '{file_path}'.")

    except json.JSONDecodeError as e:
        print(f"Failed to decode JSON: {e}")
    except FileNotFoundError:
        print(f"File '{filename}' not found.")
    except KeyError as e:
        print(f"Missing key in response data: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

def view_files(sock):
    try:
        # Send view command
        request = json.dumps({"action": "view"})
        sock.sendall(request.encode())

        # Receive the list of files or failure message
        response = sock.recv(BUFFER_SIZE).decode()

        # Print the response from the server
        if response.startswith("$FAILURE$"):
            print("No client data available.")
        else:
            print("Files available for download:")
            print(response)
    
    except Exception as e:
        print(f"An error occurred: {e}")


def main():
    # Create a socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('127.0.0.1', PORT))

    # Get user input
    command = input("Enter command: ")
    
    if command.startswith("$upload$"):
        _, filename = command.split()
        upload_file(sock, filename)
    elif command.startswith("$download$"):
        _, filename = command.split()
        download_file(sock, filename)
    elif command=="$view$":
        view_files(sock)
    else:
        print("Invalid command.")

    sock.close()

if __name__ == "__main__":
    main()



# def download_filee(sock, filename):
#     try:
#         # Send download request
#         request = json.dumps({"action": "download", "filename": filename})
#         sock.sendall(request.encode())

#         # Receive and decode JSON response
#         json_data = sock.recv(BUFFER_SIZE).decode()
#         file_data = json.loads(json_data)

#         # Save the file
#         with open(file_data['filename'], 'w') as file:
#             file.write(file_data['file_content'])
#         print(f"File '{file_data['filename']}' downloaded successfully.")
        
#     except json.JSONDecodeError as e:
#         print(f"Failed to decode JSON: {e}")
#     except FileNotFoundError:

# def ilen(iterable):
#     """
#     Return the number of items in iterable.

#     >>> ilen(x for x in range(1000000) if x % 3 == 0)
#     333334
#     """
#     # using zip() to wrap the input with 1-tuples which compress() reads as true values.
#     return sum(compress(repeat(1), zip(iterable)))

# def batched(iterable, n):
#     """Yield successive n-sized chunks from iterable."""
#     it = iter(iterable)
#     while chunk := list(islice(it, n)):
#         yield chunk

# def rle_encode(iterable, *, length_first=True):
#     """
#     >>> "".join(rle_encode("AAAABBBCCDAA"))
#     '4A3B2C1D2A'
#     >>> "".join(rle_encode("AAAABBBCCDAA", length_first=False))
#     'A4B3C2D1A2'
#     """
#     return (
#         f"{ilen(g)}{k}" if length_first else f"{k}{ilen(g)}" # ilen(g): length of iterable g
#         for k, g in groupby(iterable)
#     )
#         print(f"File '{filename}' not found.")
    
# def rle_decode(iterable, *, length_first=True):
#     """
#     >>> "".join(rle_decode("4A3B2C1D2A"))
#     'AAAABBBCCDAA'
#     >>> "".join(rle_decode("A4B3C2D1A2", length_first=False))
#     'AAAABBBCCDAA'
#     """
#     return chain.from_iterable(
#         repeat(b, int(a)) if length_first else repeat(a, int(b))
#         for a, b in batched(iterable, 2)
#     )

# def upload_file_wo_encoding(sock, filename):
#     try:
#         # Read the file content
#         with open(filename, 'r') as file:
#             file_content = file.read()
        
#         # Prepare the JSON object
#         json_data = json.dumps({
#             "filename": filename,
#             "file_content": file_content
#         })
        
#         # Send the JSON object
#         sock.sendall(json_data.encode())
#         print(f"File '{filename}' uploaded successfully.")
        
#     except FileNotFoundError:
#         print(f"File '{filename}' not found.")
# def download_file_wo_decoding(sock, filename):
#     try:
#         # Ensure the download directory exists
#         if not os.path.exists(DOWNLOAD_DIR):
#             os.makedirs(DOWNLOAD_DIR)
        
#         # Send download request
#         request = json.dumps({"action": "download", "filename": filename})
#         sock.sendall(request.encode())

#         # Receive and decode JSON response
#         json_data = sock.recv(BUFFER_SIZE).decode()
#         file_data = json.loads(json_data)

#         # Create the full path for the file in the download directory
#         file_path = os.path.join(DOWNLOAD_DIR, file_data['filename'])

#         print(file_data['file_content'])
#         # Save the file in the download directory
#         with open(file_path, 'w') as file:
#             file.write(file_data['file_content'])

#         print(f"File '{file_data['filename']}' downloaded successfully to '{file_path}'.")

#     except json.JSONDecodeError as e:
#         print(f"Failed to decode JSON: {e}")
#     except FileNotFoundError:
#         print(f"File '{filename}' not found.")
#     except KeyError as e:
#         print(f"Missing key in response data: {e}")
#     except Exception as e:
#         print(f"An error occurrrrred: {e}")
