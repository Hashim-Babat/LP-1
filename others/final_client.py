import socket

HOST ="127.0.0.1"
PORT = 12345

def start_client():
    client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    client_socket.connect((HOST,PORT))

    while True:
        message = input("> ")
        if not message or message.lower() == "exit":
            break

        client_socket.send(message.encode("utf-8"))

        echoed_msg = client_socket.recv(1024).decode('utf-8')
        print(f"Echoed Message : {echoed_msg}")
    
    client_socket.close()

if __name__ == "__main__":
    start_client()