import unittest

from progress import count_cpp_functions


class FunctionCountTests(unittest.TestCase):
    def test_multiline_signature(self):
        source = 'void Example(\n    int first,\n    int second)\n{\n}\n'
        self.assertEqual(count_cpp_functions(source), 1)

    def test_prototype_is_not_definition(self):
        source = 'void Declared(int);\nvoid Defined() { }\n'
        self.assertEqual(count_cpp_functions(source), 1)

    def test_comments_and_strings_are_not_definitions(self):
        source = '''/* void Fake() { } */
// void Other() { }
const char *text = "void Fake() { }";
void Real() { }
'''
        self.assertEqual(count_cpp_functions(source), 1)

    def test_data_types_are_not_functions(self):
        source = 'struct Thing { int field; };\nenum Values { ONE };\n'
        self.assertEqual(count_cpp_functions(source), 0)

    def test_function_pointer_parameter(self):
        source = 'void Callback(void (*callback)(int),\n int value)\n{ callback(value); }\n'
        self.assertEqual(count_cpp_functions(source), 1)


if __name__ == '__main__':
    unittest.main()
