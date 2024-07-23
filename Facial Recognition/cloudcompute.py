import socket
import threading
import requests
from deepface import DeepFace

HOST = '10.0.0.221'  # Standard loopback interface address (localhost)
PORT = 8000        # Port to listen on (non-privileged ports are > 1023)

def handle_client(conn, addr  ):
  print('Connected by', addr)
  while True:
    data = conn.recv(1024)
    if not data:
      break
    message = data.decode()
    print('Received from', addr, message)

    # Example conditional response
    if message == "face":
              # Replace 'https://www.yourwebsite.com' with the actual URL of your website
        website_url = "http://10.0.0.133:8000"

        # Send a GET request to the website
        web_response = requests.get(website_url, stream=True)

        filename = "captured_image.jpg"

        # Open a file for writing the image data in binary mode
        with open(filename, 'wb') as f:
            for chunk in web_response.iter_content(8192):
            # Write the image data chunk by chunk
                f.write(chunk)
        print(f"Image downloaded successfully: {filename}")

        verification = DeepFace.verify(img1_path = "reference_image.jpg", img2_path = "captured_image.jpg", enforce_detection=False)
        if verification["verified"] == True:
            print("its Pranav")
            response = "Pranav"
        else: 
            response= "Not Pranav"

    conn.sendall(response.encode())  # Send custom response based on message
  conn.close()
  print('Client disconnected', addr)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
  s.bind((HOST, PORT))
  s.listen()
  print('Server listening on', (HOST, PORT))
  while True:
    conn, addr = s.accept()
    client_thread = threading.Thread(target=handle_client, args=(conn, addr))
    client_thread.start()
