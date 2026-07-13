# Address Book

A simple command-line Address Book application written in C. It lets you create, search, edit, delete, and list contacts, with data persisted to a CSV file between runs.

## Features

- **Create contact** — add a new contact with name, phone number, and email, with input validation and duplicate checks
- **Search contact** — look up a contact by name, phone number, or email
- **Edit contact** — update a contact's name, phone number, or email
- **Delete contact** — remove a contact after confirmation
- **List all contacts** — view all saved contacts in a table, sorted alphabetically by name
- **Save contacts** — persist all contacts to a CSV file
- Contacts are automatically loaded from file on startup

## Project Structure

```
ADDRESS BOOK/
├── Data/
│   └── contacts.csv        # Saved contact data (name, phone, email)
├── Include/
│   ├── contact.h            # Contact/AddressBook structs and function declarations
│   └── file.h                # File I/O function declarations
└── source file/
    ├── main.c                 # Program entry point and menu loop
    ├── contact.c             # Contact management logic (create/search/edit/delete/list)
    └── file.c                   # Load/save contacts to CSV
Makefile.txt              # Build instructions
```

## Data Model

Each contact has:
- **Name** — letters, spaces, and dots only (no leading space/dot, no repeated spaces/dots)
- **Phone** — exactly 10 digits, must be unique
- **Email** — must contain a single `@` and end in `.com`, `.in`, or `.edu`

The address book supports up to 100 contacts (`MAX_CONTACTS`).

## Building

The project includes a Makefile. From the project root:

```bash
make
```

If you don't have a configured Makefile target yet, you can compile manually:

```bash
gcc -I"ADDRESS BOOK/Include" "ADDRESS BOOK/source file/main.c" "ADDRESS BOOK/source file/contact.c" "ADDRESS BOOK/source file/file.c" -o addressbook
```

## Running

```bash
./addressbook
```

You'll see a menu:

```
=========Address Book=========
 Address Book Menu:
==============================
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit
===============================
```

Enter the number corresponding to the action you want to perform.

**Note:** Contacts are loaded from and saved to `contacts.csv` in the current working directory, so run the program from the directory containing `contacts.csv` (or copy it there) to preserve existing data.

## Data File Format

`contacts.csv` stores:
1. The first line: total number of contacts
2. One line per contact: `name,phone,email`

Example:
```
1
Ganesh,0987654321,lkjuytr@mail.com
```

## Author

P. Prashanth