

extern void c2wasm_set_int_prop(int index,const char [], int value);

int c2wasm_get_string_size(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
char c2wasm_get_char_from_string(const char *str, int index) {
    return str[index];
}