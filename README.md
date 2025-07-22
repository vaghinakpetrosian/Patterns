# Command Pattern Text Editor

This C++ implementation demonstrates a text editor using the Command design pattern to support undoable operations.

## Key Features

- **Command Pattern Implementation**: Encapsulates operations as objects
- **Undo/Redo Support**: Maintains command history for reversibility
- **Core Editing Operations**:
  - Copy text to clipboard
  - Cut text to clipboard
  - Paste text from clipboard
  - Undo previous operation

## Class Structure

### Core Components

1. **`Editor` Class**:
   - Maintains the current text content
   - Provides basic text manipulation methods:
     - `getSelection()`/`deleteSelection()`/`replaceSelection()`
     - `getText()`/`setText()`

2. **`Command` Abstract Base Class**:
   - Defines the command interface
   - Implements common functionality:
     - Backup/restore mechanism
     - Undo support
   - Requires concrete commands to implement `execute()`

3. **Concrete Commands**:
   - `CopyCommand`: Copies text to clipboard
   - `CutCommand`: Cuts text to clipboard
   - `PasteCommand`: Pastes from clipboard
   - `UndoCommand`: Reverts last operation

4. **`CommandHistory` Class**:
   - Manages undo stack
   - Stores executed commands
   - Provides push/pop operations

5. **`Application` Class**:
   - Coordinates editor components
   - Maintains shared clipboard
   - Executes commands and manages history

## Usage Example

```cpp
int main() {
    Application app;
    app.editor.setText("Hello, World!");
    
    // Execute commands
    app.executeCommand(std::make_unique<CopyCommand>(&app, &app.editor));
    app.executeCommand(std::make_unique<CutCommand>(&app, &app.editor));
    app.executeCommand(std::make_unique<PasteCommand>(&app, &app.editor));
    app.executeCommand(std::make_unique<UndoCommand>(&app, &app.editor));
    
    return 0;
}
