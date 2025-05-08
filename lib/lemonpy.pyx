cdef class LemonPy:
    def __init__(self):
        self.variables = {}
        self.namespaces = {}

    def declare(self, type_name, var_name, value=None, namespace=None):
        # Advanced variable declaration with type checking and namespace support
        if type_name not in ['int', 'float', 'str', 'bool']:
            raise ValueError(f"Unsupported type: {type_name}")
        
        if namespace:
            if namespace not in self.namespaces:
                self.namespaces[namespace] = {}
            self.namespaces[namespace][var_name] = self._type_check(type_name, value)
        else:
            self.variables[var_name] = self._type_check(type_name, value)

    def _type_check(self, type_name, value):
        # Type checking to ensure value matches the declared type
        if type_name == 'int' and not isinstance(value, int):
            raise TypeError(f"Expected int, got {type(value).__name__}")
        elif type_name == 'float' and not isinstance(value, (float, int)):
            raise TypeError(f"Expected float, got {type(value).__name__}")
        elif type_name == 'str' and not isinstance(value, str):
            raise TypeError(f"Expected str, got {type(value).__name__}")
        elif type_name == 'bool' and not isinstance(value, bool):
            raise TypeError(f"Expected bool, got {type(value).__name__}")
        return value

    def print(self, message):
        # Advanced print function with formatting support
        if isinstance(message, str):
            print(message)
        else:
            print(str(message))

    def if_statement(self, condition, true_block, false_block=None):
        # Advanced if-else statement with error handling
        if not callable(true_block) or (false_block and not callable(false_block)):
            raise ValueError("Blocks must be callable functions")
        
        if condition:
            true_block()
        elif false_block:
            false_block()

    def for_loop(self, start, end, block):
        # Advanced for loop with error handling
        if not callable(block):
            raise ValueError("Block must be a callable function")
        
        for i in range(start, end):
            block(i)

    def while_loop(self, condition_func, block):
        # Advanced while loop with error handling
        if not callable(condition_func) or not callable(block):
            raise ValueError("Condition and block must be callable functions")
        
        while condition_func():
            block()

    def use_namespace(self, namespace):
        # Advanced use of a namespace with error handling
        if namespace in self.namespaces:
            return self.namespaces[namespace]
        else:
            raise ValueError(f"Namespace {namespace} does not exist.")
