import sys
from sys import *
class Hello(object):
    def __init__(self):
        object.__init__(self)
    def hello(self):
        print >> sys.stderr, "Hi there!"
    None, True, False
Hello().hello()
