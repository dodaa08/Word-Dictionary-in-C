# Word Dictionary CLI

A terminal-based dictionary app that lets you add, search, delete, update, and display words powered by a Trie data structure for fast lookups and persistent storage to disk.

---

## How it works

Words are stored in a **Trie** (prefix tree) in memory while the program runs. On exit, the trie is serialized to `dict.txt`. On startup, words are loaded back from `dict.txt` into the trie — so your dictionary persists across sessions.

This means all operations (insert, search, delete) run in **O(m)** time where `m` is the length of the word — completely independent of how many words are in the dictionary.

---

## Features

- Add, search, delete, update, and display words
- Trie data structure as in-memory cache
- Persistent storage via `dict.txt`
- Words displayed in sorted order
- Case sensitive
- Colored CLI output
- Built-in test suite

---

## Getting Started

**Requirements**
- GCC

**Compile**
```bash
gcc -o dict main.c
```

**Run**
```bash
./dict
```

---

## Usage

```
╔══════════════════════════╗
║      Word Dictionary      ║
╚══════════════════════════╝
  1. Add a word
  2. Search a word
  3. Delete a word
  4. Display all words
  5. Update a word
  6. Exit
```

- Choose an option by entering the number
- After each operation you are shown the result
- Press **Enter** to continue or **b** to go back to the menu
- Choose **6** to save and exit — words are written to `dict.txt`

---

## How the Trie works

Each character of a word is stored as a node. Words that share a prefix share the same path in the tree.

```
Inserting: "cat", "car", "dog"

root
├── 'c'
│    └── 'a'
│         ├── 't'  ← isEndOfWord = 1  ("cat")
│         └── 'r'  ← isEndOfWord = 1  ("car")
└── 'd'
     └── 'o'
          └── 'g'  ← isEndOfWord = 1  ("dog")
```

- "cat" and "car" share the prefix "ca" — stored only once
- `isEndOfWord` flag marks where a valid word ends
- Search just walks the path — if it falls off the tree, word doesn't exist

---

## Tests

A built-in test suite runs automatically on startup. It:

- Inserts 100 words into an isolated test trie
- Verifies search on existing and non-existing words
- Verifies duplicate insert is blocked
- Verifies delete removes the word
- Verifies update replaces old word with new
- Verifies word count is correct after all operations

The test trie is completely separate from your dictionary — tests don't affect your saved words.

---

## Future Improvements

- Prefix search — find all words starting with a given prefix
- Case insensitive mode
- Word count command
- Import words from a custom file
