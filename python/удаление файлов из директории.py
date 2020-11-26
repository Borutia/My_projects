import os
import shutil

class Counter():
    def __init__(self):
        self.dirs = 0
        self.files = {}

    def print_information(self):
        for key, val in self.files.items():
            print('delete ' + key + ": " + str(val))
        print('delete dirs: ' + self.dirs)


folder = '/Users/macbook/Desktop/тест'

counter = Counter()

for root, dirs, files in os.walk(folder):
       for f in files:
           extension = f[f.rfind(".") + 1:]
           if extension in counter.files:
               counter.files[extension] += 1
           else:
               counter.files[extension] = 1
           os.unlink(os.path.join(root, f))
       for d in dirs:
           shutil.rmtree(os.path.join(root, d))
           counter.dirs += 1

counter.print_information()

