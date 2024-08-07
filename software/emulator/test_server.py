# https://github.com/nickjj/webserver/blob/master/webserver

import env
from http.server import HTTPServer, BaseHTTPRequestHandler

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.write_response(b"")

    def do_POST(self):
        content_length = int(self.headers.get("content-length", 0))
        body = self.rfile.read(content_length)

        self.write_response(body)

    def write_response(self, content):
        self.send_response(200)
        self.end_headers()
        self.wfile.write(content)

        print(self.headers)
        print(content.decode("utf-8"))

print(f"Listening on http://{env.IP}:{env.PORT}\n")

httpd = HTTPServer((env.IP, env.PORT), SimpleHTTPRequestHandler)
httpd.serve_forever()