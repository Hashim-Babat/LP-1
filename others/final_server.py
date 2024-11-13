import socket
import threading

HOST = "127.0.0.1"
PORT = 12345


def handle_client(client_socket,client_address):
    print(f"[NEW server CONNECTION] {client_address} CONNECTED")

    while True :
        try : 
            message = client_socket.recv(1024).decode('utf-8')
            if not message or message.lower == "exit":
                break
                
            print(f"[{client_address}] : {message}")

            client_socket.send(message.encode('utf-8'))

        except ConnectionResetError:
            break

    client_socket.close()
    print(f"[{client_address}] Connection Closed")


def start_server() :
    server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server_socket.bind((HOST,PORT))
    server_socket.listen()
    print(f"[Listening] server is listening on {HOST}:{PORT}")

    while True : 
        client_socket,client_address = server_socket.accept()
        client_thread = threading.Thread(target=handle_client,args = (client_socket,client_address))
        client_thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 1}")


if __name__ == "__main__" :
    print("[STARTING] Server is starting...")
    start_server()