# ProgrammingToday

A collection of C programming examples, including a feature-rich GTK calculator application.

## Enhanced Calculator

A graphical calculator application built with GTK4, featuring:

- **Multiple Operations**: Add, Subtract, Multiply, Divide
- **Interactive Input**: Enter your own numbers
- **Operation Counter**: Tracks how many calculations you've performed
- **Calculation History**: Scrollable history of all operations
- **Count Feature**: Display numbers 1-10
- **Clear Function**: Reset all inputs and history

## Requirements

- **GTK4** (for the GUI calculator)
- **GCC** compiler
- **pkg-config**

### Installing GTK4

**macOS (using Homebrew):**
```bash
brew install gtk4
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install libgtk-4-dev pkg-config
```

**Linux (Fedora):**
```bash
sudo dnf install gtk4-devel pkg-config
```

## Building

### Simple Hello World (Terminal)
```bash
gcc hello.c -o hello
./hello
```

### Enhanced Calculator (GTK GUI)
```bash
gcc $(pkg-config --cflags gtk4) -o hello_gtk hello_gtk.c $(pkg-config --libs gtk4)
./hello_gtk
```

## Usage

1. Enter numbers in the "Number A" and "Number B" input fields
2. Click any operation button (Add, Subtract, Multiply, Divide)
3. View results in the "Result" section
4. Check the "History" section to see past calculations
5. Use "Clear All" to reset everything

## Files

- `hello.c` - Simple terminal-based C program
- `hello_gtk.c` - Enhanced GTK calculator application
- `README.md` - This file

## License

This project is open source and available for educational purposes.
