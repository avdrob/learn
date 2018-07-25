import asyncio
import re
import bisect


class ServerError(Exception):
    pass


class ServerWrongCommand(ServerError):
    """'No such request' exception"""
    pass


class ServerWrongArguments(ServerError):
    """'Wrong request arguments' exception"""


class ClientServerProtocol(asyncio.Protocol):

    metrics = dict()
    req_process_map = {
        'get': None,
        'put': None
    }
    wrong_cmd = 'error\nwrong command\n\n'
    ok_status = 'ok\n'

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.req_process_map['get'] = self.process_get
        self.req_process_map['put'] = self.process_put

    def connection_made(self, transport):
        self.transport = transport

    def data_received(self, data):
        words = re.split('[ \n\r]', data.decode())
        words = [w for w in words if w]

        try:
            self._check_cmd(words)
            resp = self.req_process_map[words[0]](words)
        except ServerError:
            resp = self.wrong_cmd
        except Exception:
            raise
        finally:
            self.send_resp(resp)
            return

    def process_get(self, cmd):
        _, key = cmd
        res = self.ok_status

        if key == '*':
            for metric, values in self.metrics.items():
                for value in values:
                    res += f'{metric} {value[1]} {value[0]}'
                    res += '\n'
        elif key in self.metrics:
            for value in self.metrics[key]:
                res += f'{key} {value[1]} {value[0]}'
                res += '\n'
        else:
            pass

        res += '\n'
        return res

    def process_put(self, cmd):
        _, key, val, ts = cmd

        try:
            val, ts = float(val), int(ts)
        except (ValueError, TypeError):
            raise ServerWrongArguments('Wrong request arguments')

        if key not in self.metrics:
            self.metrics[key] = []
        if (ts, val) not in self.metrics[key]:
            bisect.insort(self.metrics[key], (ts, val))

        return self.ok_status + '\n'

    def send_resp(self, resp):
        if isinstance(resp, str):
            resp = resp.encode()
        self.transport.write(resp)

    def _check_cmd(self, words):
        if (not words or
            not (words[0] == 'get' and len(words) == 2 or
                 words[0] == 'put' and len(words) == 4)):
            raise ServerWrongCommand('No such request')


def run_server(host, port):
    loop = asyncio.get_event_loop()
    coro = loop.create_server(ClientServerProtocol, host, port)

    server = loop.run_until_complete(coro)

    try:
        loop.run_forever()
    except KeyboardInterrupt:
        pass

    server.close()
    loop.run_until_complete(server.wait_closed())
    loop.close()


if __name__ == '__main__':
    run_server('127.0.0.1', 8888)

# Reference solution (actualy I like mine more)

# import asyncio
#
#
# class Storage:
#     """Класс для хранения метрик в памяти процесса"""
#
#     def __init__(self):
#         # используем словарь для хранения метрик
#         self._data = {}
#
#     def put(self, key, value, timestamp):
#         if key not in self._data:
#             self._data[key] = {}
#
#         self._data[key][timestamp] = value
#
#     def get(self, key):
#         data = self._data
#
#         # вовзращаем нужную метрику если это не *
#         if key != "*":
#             data = {
#                 key: data.get(key, {})
#             }
#
#         # для простоты мы храним метрики в обычном словаре и сортируем значения
#         # при каждом запросе, в реальном приложении следует выбрать другую
#         # структуру данных
#         result = {}
#         for key, timestamp_data in data.items():
#             result[key] = sorted(timestamp_data.items())
#
#         return result
#
#
# class ParseError(ValueError):
#     pass
#
#
# class Parser:
#     """Класс для реализации протокола"""
#
#     def encode(self, responses):
#         \"""Преобразование ответа сервера в строку для передачи в сокет\"""
#         rows = []
#         for response in responses:
#             if not response:
#                 continue
#             for key, values in response.items():
#                 for timestamp, value in values:
#                     rows.append(f"{key} {value} {timestamp}")
#
#         result = "ok\n"
#
#         if rows:
#             result += "\n".join(rows) + "\n"
#
#         return result + "\n"
#
#     def decode(self, data):
#         """Разбор команды для дальнейшего выполнения. Возвращает список команд для выполнения"""
#         parts = data.split("\n")
#         commands = []
#         for part in parts:
#             if not part:
#                 continue
#
#             try:
#                 method, params = part.strip().split(" ", 1)
#                 if method == "put":
#                     key, value, timestamp = params.split()
#                     commands.append(
#                         (method, key, float(value), int(timestamp))
#                     )
#                 elif method == "get":
#                     key = params
#                     commands.append(
#                         (method, key)
#                     )
#                 else:
#                     raise ValueError("unknown method")
#             except ValueError:
#                 raise ParseError("wrong command")
#
#         return commands
#
#
# class ExecutorError(Exception):
#     pass
#
#
# class Executor:
#     """Класс Executor реализует метод run, который знает как выполнять команды сервера"""
#
#     def __init__(self, storage):
#         self.storage = storage
#
#     def run(self, method, *params):
#         if method == "put":
#             return self.storage.put(*params)
#         elif method == "get":
#             return self.storage.get(*params)
#         else:
#             raise ExecutorError("Unsupported method")
#
#
# class EchoServerClientProtocol(asyncio.Protocol):
#     \"""Класс для реализции сервера при помощи asyncio\"""
#
#     # Обратите внимание на то, что storage является атрибутом класса
#     # Объект self.storage для всех экземмпляров класса EchoServerClientProtocol
#     # будет являться одним и тем же объектом для хранения метрик.
#     storage = Storage()
#
#     def __init__(self):
#         super().__init__()
#
#         self.parser = Parser()
#         self.executor = Executor(self.storage)
#         self._buffer = b''
#
#     def process_data(self, data):
#         \"""Обработка входной команды сервера\"""
#
#         # разбираем сообщения при помощи self.parser
#         commands = self.parser.decode(data)
#
#         # выполняем команды и запоминаем результаты выполнения
#         responses = []
#         for command in commands:
#             resp = self.executor.run(*command)
#             responses.append(resp)
#
#         # преобразовываем команды в строку
#         return self.parser.encode(responses)
#
#     def connection_made(self, transport):
#         self.transport = transport
#
#     def data_received(self, data):
#         \"""Метод data_received вызывается при получении данных в сокете\"""
#         self._buffer += data
#         try:
#             decoded_data = self._buffer.decode()
#         except UnicodeDecodeError:
#             return
#
#         # ждем данных, если команда не завершена символом \n
#         if not decoded_data.endswith('\n'):
#             return
#
#         self._buffer = b''
#
#         try:
#             # обрабатываем поступивший запрос
#             resp = self.process_data(decoded_data)
#         except (ParseError, ExecutorError) as err:
#             # формируем ошибку, в случае ожидаемых исключений
#             self.transport.write(f"error\n{err}\n\n".encode())
#             return
#
#         # формируем успешный ответ
#         self.transport.write(resp.encode())
#
#
# def run_server(host, port)
#     loop = asyncio.get_event_loop()
#     coro = loop.create_server(
#         EchoServerClientProtocol,
#         host, port
#     )
#     server = loop.run_until_complete(coro)
#     try:
#         loop.run_forever()
#     except KeyboardInterrupt:
#         pass
#
#     server.close()
#     loop.run_until_complete(server.wait_closed())
#     loop.close()
#
#
# if __name__ == "__main__":
#     # запуск сервера для тестирования
#     run_server('127.0.0.1', 8888)
