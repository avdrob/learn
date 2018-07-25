import os
import tempfile

class File:
    def __init__(self, filename):
        self._filename = filename
    
    @property
    def filename(self):
        return self._filename

    def write(self, content):
        with open(self.filename, 'w') as f:
            f.write(content)
    
    def __iter__(self):
        def file_gen(self):
            with open(self.filename, 'r') as f:
                for line in f:
                    line = line.rstrip()
                    yield line
        return file_gen(self)

    def __add__(self, other):
        tmpdir = tempfile.gettempdir()
        new_file = tempfile.NamedTemporaryFile(mode="w",
                dir=tmpdir, delete=False)
        with open(self.filename, 'r') as f1:
            with open(other.filename, 'r') as f2:
                f1_contents = f1.read()
                f2_contents = f2.read()
                new_file.write(f1_contents + f2_contents)
        new_file.close()
        return File(new_file.name)
        
    def __str__(self):
        return self.filename

"""Reference solution

import os
import uuid


class File:
    def __init__(self, path):
        self.path = path
        self.current_position = 0

        if not os.path.exists(self.path):
            open(self.path, 'w').close()

    def write(self, content):
        with open(self.path, 'w') as f:
            return f.write(content)

    def read(self):
        with open(self.path, 'r') as f:
            return f.read()

    def __add__(self, obj):
        new_path = os.path.join(
            os.path.dirname(self.path),
            str(uuid.uuid4().hex)
        )
        new_file = type(self)(new_path)
        new_file.write(self.read() + obj.read())

        return new_file

    def __str__(self):
        return self.path

    def __iter__(self):
        return self

    def __next__(self):
        with open(self.path, 'r') as f:
            f.seek(self.current_position)

            line = f.readline()
            if not line:
                self.current_position = 0
                raise StopIteration('EOF')

            self.current_position = f.tell()
            return line
"""