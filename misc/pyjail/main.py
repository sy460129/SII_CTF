from socket import *
import os, subprocess

ban = [
    'a', 'e', 'g', 'i', 'l', 'r', 's', 'u', '\'', '\"'
]

def secure_eval(user_input):
    if any(b in user_input for b in ban):
        raise Exception("You are going to jail!")
    
    try:
        result = eval(user_input, {"__builtins__": None})
        return str(result)
    except Exception as e:
        return f"Error: {e}"

def handle_client(conn, addr):
    conn.sendall(b"Welcome to PyJail! Read 'flag' if you can!\n\n")
    while True:
        try:
            conn.sendall(b">>> ")
            data = conn.recv(1024).decode().strip()
            if not data:
                break
            
            response = secure_eval(data)
            os.system(response)
            result = subprocess.check_output(response, shell=True, stderr=subprocess.STDOUT)
            conn.sendall(result + b"\n")
        except Exception as e:
            conn.sendall(f"Hmm.. {e}\n".encode())
            break
    conn.close()
    os._exit(0)  # 자식 프로세스 종료

def start_server(host="0.0.0.0", port=9889):
    server = socket(AF_INET, SOCK_STREAM)
    server.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen(20)
    print(f"[*] Listening on {host}:{port}")
    while True:
        conn, addr = server.accept()
        print(f"[*] Connection from {addr}")
        pid = os.fork()
        if pid == 0:  # 자식 프로세스
            server.close()  # 자식에서는 서버 소켓 닫기
            handle_client(conn, addr)
        else:
            conn.close()  # 부모는 클라이언트 소켓 닫기

if __name__ == "__main__":
    start_server()
