import time
import socket
import select
import io
import bisect

class ClientError(Exception):
    pass

class Client:

    serv_success_response = 'ok'

    def __init__(self, host, port, timeout=None):
        self.socket=socket.create_connection((host, port), timeout=timeout)
        self._timeout = timeout
    

    @property
    def timeout(self):
        return self._timeout


    def sendreq(self, request):
        # _, fds, _ = select.select([], [self.socket.fileno()], [], self.timeout)
        # if not fds:
        #     raise ClientError
        self.socket.send(request.encode())
    

    @staticmethod
    def recv_all(sock):
        text = ''
        chunk = b''

        try:
            while True:
                chunk = sock.recv(4096)
                if not chunk:
                    break
                else:
                    text += chunk.decode()
        except:
            pass
        
        if not text:
            raise ClientError
        
        return text

    def recvresp(self):
        # fds, _, _ = select.select([self.socket.fileno()], [], [], self.timeout)
        # if not fds:
        #     raise ClientError
        return self.recv_all(self.socket)
    
    @staticmethod
    def resp2lines(response):
        lines = response.split('\n')
        lines = [line for line in lines if line]
        return lines

    def put(self, key, value, timestamp=None):
        if not timestamp:
            timestamp = str(int(time.time()))

        request = ' '.join(('put', key, str(value), str(timestamp))) + '\n'
        self.sendreq(request)

        resp_lines = self.resp2lines(self.recvresp())
        if next(iter(resp_lines)) != self.serv_success_response:
            raise ClientError

    def get(self, key='*'):
        request = ' '.join(('get', key)) + '\n'
        self.sendreq(request)

        result = dict()
        resp_lines = self.resp2lines(self.recvresp())
        it = iter(resp_lines)

        if next(it) != self.serv_success_response:
            raise ClientError
        for line in it:
            words = line.split(' ')
            key, val, ts = words
            val, ts = float(val), int(ts)
            if key in result:
                bisect.insort(result[key], (ts, val))
            else:
                result[key] = []
                result[key].append((ts, val))
        
        return result

"""Reference solution
import socket
import time


class ClientError(Exception):
    \"""Общий класс исключений клиента\"""
    pass


class ClientSocketError(ClientError):
    \"""Исключение, выбрасываемое клиентом при сетевой ошибке\"""
    pass


class ClientProtocolError(ClientError):
    \"""Исключение, выбрасываемое клиентом при ошибке протокола\"""
    pass


class Client:
    def __init__(self, host, port, timeout=None):
        # класс инкапсулирует создание сокета
        # создаем клиентский сокет, запоминаем объект socke.socket в self 
        self.host = host
        self.port = port
        try:
            self.connection = socket.create_connection((host, port), timeout)
        except socket.error as err:
            raise ClientSocketError("error create connection", err)

    def _read(self):
        \"""Метод для чтения ответа сервера\"""
        data = b""
        # накапливаем буфер, пока не встретим "\n\n" в конце команды
        while not data.endswith(b"\n\n"):
            try:
                data += self.connection.recv(1024)
            except socket.error as err:
                raise ClientSocketError("error recv data", err)

        # не забываем преобразовывать байты в объекты str для дальнейшей работы
        decoded_data = data.decode()

        status, payload = decoded_data.split("\n", 1)
        payload = payload.strip()

        # если получили ошибку - бросаем исключение ClientError
        if status == "error":
            raise ClientProtocolError(payload)

        return payload

    def put(self, key, value, timestamp=None):
        timestamp = timestamp or int(time.time())

        # отправляем запрос команды put
        try:
            self.connection.sendall(
                f"put {key} {value} {timestamp}\n".encode()
            )
        except socket.error as err:
            raise ClientSocketError("error send data", err)

        # разбираем ответ
        self._read()

    def get(self, key):
        # формируем и отправляем запрос команды get
        try:
            self.connection.sendall(
                f"get {key}\n".encode()
            )
        except socket.error as err:
            raise ClientSocketError("error send data", err)

        # читаем ответ
        payload = self._read()

        data = {}
        if payload == "":
            return data

        # разбираем ответ для команды get
        for row in payload.split("\n"):
            key, value, timestamp = row.split()
            if key not in data:
                data[key] = []
            data[key].append((int(timestamp), float(value)))

        return data

    def close(self):
        try:
            self.connection.close()
        except socket.error as err:
            raise ClientSocketError("error close connection", err)


def _main():
    # проверка работы клиента
    client = Client("127.0.0.1", 8888, timeout=5)
    client.put("test", 0.5, timestamp=1)
    client.put("test", 2.0, timestamp=2)
    client.put("test", 0.5, timestamp=3)
    client.put("load", 3, timestamp=4)
    client.put("load", 4, timestamp=5)
    print(client.get("*"))
    
    client.close()


if __name__ == "__main__":
    _main()
"""