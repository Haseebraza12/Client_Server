# #wo multithreading
# import socket
# import json
# import os
# import re

# from itertools import repeat, compress, groupby
# from itertools import chain, repeat, islice


# BUFFER_SIZE = 10240
# PORT = 8080

# DOWNLOAD_DIR = "downloaded_files"  # Define the download directory


# def rle_encodee(iterable):
#     result = []
#     for k, g in groupby(iterable):
#         count = len(list(g))
#         result.append(f"{count}{k}")
#     return ''.join(result)

# def rle_decodee(encoded):
#     result = []
#     # This will create an iterator over the encoded string
#     it = iter(encoded)

#     # Loop through the encoded string in pairs
#     while True:
#         try:
#             # Get the count (digits)
#             count_str = ''
#             while True:
#                 char = next(it)
#                 if char.isdigit():
#                     count_str += char
#                 else:
#                     # When we find a non-digit, we've reached the end of the count
#                     break
            
#             count = int(count_str)  # Convert count to an integer
            
#             # Append the character repeated 'count' times to the result
#             result.append(char * count)

#         except StopIteration:
#             # Break the loop if we've exhausted the iterator
#             break
  
#     return ''.join(result)


# #wo mt
# def upload_file(sock, filename):
#     try:
#         with open(filename, 'r') as file:
#             file_content = file.read()

#         # Encode file content using RLE
#         encoded_content = ''.join(rle_encodee(file_content))

#         # Prepare the JSON object
#         json_data = json.dumps({
#             "filename": filename,
#             "file_content": encoded_content
#         })

#         # Send the JSON object
#         sock.sendall(json_data.encode())
#         print(f"File '{filename}' uploaded successfully.")

#     except FileNotFoundError:
#         print(f"File '{filename}' not found.")




# #wo multi thread
# def download_file(sock, filename):
#     try:
#         if not os.path.exists(DOWNLOAD_DIR):
#             os.makedirs(DOWNLOAD_DIR)

#         request = json.dumps({"action": "download", "filename": filename})
#         sock.sendall(request.encode())

#         json_data = sock.recv(BUFFER_SIZE).decode()
#         file_data = json.loads(json_data)
#         # Decode the received file content using RLE
#         encoded_content = file_data['file_content'].strip('.txt')
#         #decoded_content = rle_decodee(encoded_content)
#         #encoded_content = re.sub(r'[^a-zA-Z0-9]+$', '', encoded_content)
#         encoded_content = re.split(r'[^a-zA-Z0-9]', file_data['file_content'])[0]

#         print(encoded_content)
#         # Decode the received file content using RLE
#         decoded_content = ''.join(rle_decodee(encoded_content))

#         file_path = os.path.join(DOWNLOAD_DIR, file_data['filename'])

#         with open(file_path, 'w') as file:
#             file.write(decoded_content)

#         print(f"File '{file_data['filename']}' downloaded successfully to '{file_path}'.")

#     except json.JSONDecodeError as e:
#         print(f"Failed to decode JSON: {e}")
#     except FileNotFoundError:
#         print(f"File '{filename}' not found.")
#     except KeyError as e:
#         print(f"Missing key in response data: {e}")
#     except Exception as e:
#         print(f"An error occurred: {e}")




# #wo multi threading

# def view_files(sock):
#     try:
#         # Send view command
#         request = json.dumps({"action": "view"})
#         sock.sendall(request.encode())

#         # Receive the list of files or failure message
#         response = sock.recv(BUFFER_SIZE).decode()

#         # Print the response from the server
#         if response.startswith("$FAILURE$"):
#             print("No client data available.")
#         else:
#             print("Files available for download:")
#             print(response)
    
#     except Exception as e:
#         print(f"An error occurred: {e}")


# def main():
#     # Create a socket
#     sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#     sock.connect(('127.0.0.1', PORT))

#     # Get user input
#     command = input("Enter command: ")
    
#     if command.startswith("$upload$"):
#         _, filename = command.split()
#         upload_file(sock, filename)
#     elif command.startswith("$download$"):
#         _, filename = command.split()
#         download_file(sock, filename)
#     elif command=="$view$":
#         view_files(sock)
#     else:
#         print("Invalid command.")

#     sock.close()

# if __name__ == "__main__":
#     main()







import socket
import json
import os

import re

from itertools import repeat, compress, groupby
from itertools import chain, repeat, islice


BUFFER_SIZE = 10240
PORT = 8080

def rle_encodee(iterable):
    result = []
    for k, g in groupby(iterable):
        count = len(list(g))
        result.append(f"{count}{k}")
    return ''.join(result)

def rle_decodee(encoded):
    result = []
    it = iter(encoded)

    while True:
        try:
            count_str = ''
            while True:
                char = next(it)
                if char.isdigit():
                    count_str += char
                else:
                    break

            count = int(count_str)
            result.append(char * count)

        except StopIteration:
            break

    return ''.join(result)

def upload_file(sock, client_name, filename):
    try:
        with open(filename, 'r') as file:
            file_content = file.read()

        # Encode the file content using RLE
        encoded_content = ''.join(rle_encodee(file_content))

        # Prepare the JSON object, now with the client name
        json_data = json.dumps({
            "client_name": client_name,
            "filename": filename,
            "file_content": encoded_content
        })

        # Send the JSON object
        sock.sendall(json_data.encode())
        print(f"File '{filename}' uploaded successfully.")

    except FileNotFoundError:
        print(f"File '{filename}' not found.")
# def download_file(sock, filename):
#     try:
#         if not os.path.exists(DOWNLOAD_DIR):
#             os.makedirs(DOWNLOAD_DIR)

#         request = json.dumps({"action": "download", "filename": filename})
#         sock.sendall(request.encode())

#         json_data = sock.recv(BUFFER_SIZE).decode()
#         file_data = json.loads(json_data)
#         # Decode the received file content using RLE
#         encoded_content = file_data['file_content'].strip('.txt')
#         #decoded_content = rle_decodee(encoded_content)
#         #encoded_content = re.sub(r'[^a-zA-Z0-9]+$', '', encoded_content)
#         encoded_content = re.split(r'[^a-zA-Z0-9]', file_data['file_content'])[0]

#         print(encoded_content)
#         # Decode the received file content using RLE
#         decoded_content = ''.join(rle_decodee(encoded_content))

#         file_path = os.path.join(DOWNLOAD_DIR, file_data['filename'])

#         with open(file_path, 'w') as file:
#             file.write(decoded_content)

#         print(f"File '{file_data['filename']}' downloaded successfully to '{file_path}'.")

#     except json.JSONDecodeError as e:
#         print(f"Failed to decode JSON: {e}")
#     except FileNotFoundError:
#         print(f"File '{filename}' not found.")
#     except KeyError as e:
#         print(f"Missing key in response data: {e}")
#     except Exception as e:
#         print(f"An error occurred: {e}")

def download_file(sock, client_name, filename):
    try:
        request = json.dumps({
            "action": "download",
            "client_name": client_name,  # Send the client name with the download request
            "filename": filename
        })
        sock.sendall(request.encode())
        json_data = sock.recv(BUFFER_SIZE).decode()
        file_data = json.loads(json_data)
#         # Decode the received file content using RLE
        # encoded_content = file_data['file_content'].strip('.txt')
        # encoded_content = re.split(r'[^a-zA-Z0-9]', file_data['file_content'])[0]


                # This ensures no characters are stripped, including spaces
        encoded_content = file_data['file_content']

        # Decode the received file content using RLE (spaces and all other characters are preserved)
        decoded_content = rle_decodee(encoded_content)

        print(encoded_content)
#         # Decode the received file content using RLE
        decoded_content = ''.join(rle_decodee(encoded_content))


        # Save the file in the download directory
        if not os.path.exists('downloaded_files'):
            os.makedirs('downloaded_files')

        file_path = os.path.join('downloaded_files', file_data['filename'])

        with open(file_path, 'w') as file:
            file.write(decoded_content)

        print(f"File '{file_data['filename']}' downloaded successfully to '{file_path}'.")

    except json.JSONDecodeError as e:
        print(f"Failed to decode JSON: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

def view_files(sock, client_name):
    try:
        # Send view request with client name
        request = json.dumps({"action": "view", "client_name": client_name})
        sock.sendall(request.encode())

        response = sock.recv(BUFFER_SIZE).decode()
        print("Files available for download:")
        print(response)

    except Exception as e:
        print(f"An error occurred: {e}")

def main():
    # Get the client's name
    client_name = input("Enter your name: ")

    # Create a socket and connect to the server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('127.0.0.1', PORT))

    # Get user input
    command = input("Enter command ($upload$ filename, $download$ filename, $view$): ")
        
    if command.startswith("$upload$"):
        _, filename = command.split()
        upload_file(sock, client_name, filename)
    elif command.startswith("$download$"):
        _, filename = command.split()
        download_file(sock, client_name, filename)
    elif command == "$view$":
        view_files(sock, client_name)
    else:
        print("Invalid command.")
                  
    sock.close()


if __name__ == "__main__":
    main()
