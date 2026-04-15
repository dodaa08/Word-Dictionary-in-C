# Word Trie Dictionary C

A terminal-based dictionary app that lets you add, search, delete, update, and display words. Powered by a **Trie** (prefix tree) for fast O(m) lookups and persistent storage to disk.

---

## How It Works

Words are stored in a Trie in memory while the program runs. On exit, the trie is serialized to `dict.txt`. On startup, words are loaded back from `dict.txt` into the trie  so your dictionary persists across sessions.

All operations (insert, search, delete) run in **O(m)** time, where m is the length of the word, completely independent of how many words are in the dictionary.

---

## Features

- Add, search, delete, update, and display words
- **Prefix search**  when an exact word isn't found, matching words with the same prefix are shown automatically
- Trie data structure as an in-memory cache
- Persistent storage via `dict.txt`
- Words displayed in **sorted (ASCII) order**
- Full **ASCII support** (case-sensitive, supports 128 characters)
- Colored CLI output
- Built-in test suite that runs on startup

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
- After each operation, you are shown the result
- Press **Enter** to go back to the menu
- Choose **6** to save and exit  words are written to `dict.txt`

### Search behaviour

When you search for a word:
- If the exact word exists → confirmed with a success message
- If not found → prefix matches are shown automatically (e.g. searching `co` shows `collect`, `comfort`, `command`, etc.)

---

## How the Trie Works

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

- `"cat"` and `"car"` share the prefix `"ca"`  stored only once
- The `isEndOfWord` flag marks where a valid word ends
- Search walks the path  if it falls off the tree, the word doesn't exist
- Each node holds up to 128 children, supporting the full ASCII range

---

## Tests

A built-in test suite runs automatically on startup, completely isolated from your saved dictionary. It verifies:

| Test | Description |
|---|---|
| Insert | 100 words inserted into a test trie |
| Search (existing) | Confirms words like `"ability"` and `"palace"` are found |
| Search (non-existing) | Confirms `"xyz123"` is not found |
| Duplicate insert | Verifies inserting the same word twice is blocked |
| Delete | Confirms `"ability"` is removed and no longer found |
| Delete (non-existing) | Confirms graceful handling of missing words |
| Update | `"balance"` → `"balanced"`  old gone, new present |
| Prefix search | Live output of all words matching prefix `"co"` |
| Word count | Confirms count is 98 after all operations |

The test trie is discarded after the suite  your saved words are never affected.

---
