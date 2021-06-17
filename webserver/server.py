import json
import mimetypes
from http.server import BaseHTTPRequestHandler, HTTPServer
from uuid import uuid4
from os import listdir
from os.path import isfile, join
host_port = 8000
from random import seed
from random import random
import json
seed(1)

def save_token(token):
    path = "tokens.json"
    file = open(path, mode="r+")
    tokens = json.loads(file.read())
    tokens.append(token)
    file.seek(0)
    file.truncate()
    json.dump(tokens, file)
    file.close()


class Server(BaseHTTPRequestHandler):
    status = False
    actual_pipe = ""
    def do_HEAD(self):
        self.send_response(200)
        mimetype, _ = mimetypes.guess_type(self.path)
        self.send_header('Content-type', mimetype)
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, OPTIONS')
        self.send_header("Access-Control-Allow-Headers", "X-Requested-With")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()

    def do_GET(self):
        path = self.path.split("?")[0]
        last_word = self.path.split("/")
        last_word = last_word[len(last_word) - 1]
        if last_word in self.get_file_list():
            self.send_file(last_word)
        elif self.path == "/":
            self.send_file("website/common/login.html")
        elif self.path == "/api/images":
            self.send_list_documents()
        else:
            self.send_file("website" + self.path)

    def do_POST(self):
        # Get the size of data
        content_length = int(self.headers['Content-Length'])
        # Get the data
        post_data = self.rfile.read(content_length)

        if self.path == "/status":
            self.set_status(post_data)
        elif self.path == "/pipe":
            self.set_pipe(post_data)
        else:
            self.resource_not_found()

    def do_PUT(self):
        # Get the size of data
        content_length = int(self.headers['Content-Length'])
        # Get the data
        put_data = self.rfile.read(content_length)
        if self.path == "/api/picture":
            filepath = "picture" + str(random()) +".jpg"
            while filepath in self.get_file_list():
                filepath =  "picture" + str(random()) +".jpg"
            print(filepath)
            self.receive_file(filepath, put_data)
        else:
            self.resource_not_found()

    def do_OPTIONS(self):
        self.do_HEAD()

    def set_status(self,status):
        if status == "True":
            self.status = True
        else:
            self.status = False
        self.do_HEAD()

    def set_pipe(self,data):
        self.actual_pipe = data
        self.do_HEAD()

    def send_list_documents(self):
        try:
            data = self.get_file_list()
            self.do_HEAD()
            self.wfile.write(str.encode(json.dumps(data)))
        except IOError:
            self.resource_not_found()

    def send_status(self):
        try:
            data = ""
            if self.status:
                data = "{ \"status\":true}"
            else:
                data = "{ \"status\":false}"
            self.do_HEAD()
            self.wfile.write(str.encode(data))
        except IOError:
            self.resource_not_found()

    def send_pipe(self):
        try:
            data = "{\"pipe\": \" " + self.actual_pipe + " \"}"
            self.do_HEAD()
            self.wfile.write(str.encode(data))
        except IOError:
            self.resource_not_found()

    def send_file(self, path):
        try:
            file = open(path, mode='rb')
            data = file.read()
            file.close()
            self.do_HEAD()
            self.wfile.write(data)
        except IOError:
            self.resource_not_found()

    def receive_file(self, path, data):
        file = open(path, mode="wb")
        file.write(data)
        file.close()
        self.do_HEAD()


    def authenticate(self, path, data):
        file = open(path, mode='r+')
        users = json.loads(file.read())
        data = json.loads(data)
        for user in users:
            if user["username"] == data["username"] and user["password"] == data["password"]:
                token = str(uuid4())
                save_token(token)
                self.send_token(token)
                return
        token = str(0)
        self.send_token(token)

    def sign_up(self, path, data):
        file = open(path, mode='r+')
        users = json.loads(file.read())
        data = json.loads(data)
        users.append(data)
        file.seek(0)
        file.truncate()
        json.dump(users, file)
        file.close()

    def validate_session(self, path, data):
        file = open(path, mode='r+')
        tokens = json.loads(file.read())
        data = json.loads(data)
        value = "invalid"
        for token in tokens:
            if token == data["token"]:
                value = "valid"
                break
        self.wfile.write(json.dumps({"token": value}).encode())
        file.close()

    def send_token(self, token):
        self.send_response(200)
        self.send_header("Authorization", token)
        self.end_headers()

    def resource_not_found(self):
        self.send_response(404)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def get_file_list(self):
        return [f for f in listdir("./") if isfile(join("./", f))]

if __name__ == '__main__':
    http_server = HTTPServer(('', host_port), Server)
    print("Server started on port: %s" % host_port)
    # print("test %s" % [f for f in listdir("./") if isfile(join("./", f))])

    try:
        http_server.serve_forever()
    except KeyboardInterrupt:
        http_server.server_close()
