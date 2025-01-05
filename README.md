# **HotelTrack : A Hotel Management System**

Welcome to **HotelTrack** , a simple yet efficient console-based application for managing hotel customer data. This system offers an easy-to-use interface with color-coded features for better readability and interaction. Built with C, it is designed for users looking for an accessible solution to manage reservations, search customer records, and update or delete entries.

---

## **Features**
1. **Login System**
   - Secure login with pre-defined credentials.
   - Hidden password input with asterisks for privacy.
2. **Add Customer**
   - Add new customer details, including room number, name, contact, nationality, and stay period.
3. **View Customer List**
   - Display all customer records in a structured and aligned format.
4. **Search Customer**
   - Quickly find customer details using their room number.
5. **Edit Customer Details**
   - Modify existing customer records with updated information.
6. **Delete Customer**
   - Remove a specific customer record based on their room number.
7. **Color-coded Interface**
   - Green for menus, yellow for actions, cyan for lists, and red for alerts or errors.

---

## **Code Overview**

### **Core Functions**
- **`setcolor(int Forgc)`**: Changes the console text color dynamically.
- **`login()`**: Secure login system with limited retry attempts.
- **`add()`**: Adds customer data to a file (`add.txt`).
- **`list()`**: Reads and displays all customer data from the file.
- **`search()`**: Searches for a specific customer by room number.
- **`edit()`**: Updates details of an existing customer.
- **`delete()`**: Deletes a customer record permanently.

### **Data Structure**
```c
struct CustomerDetails {
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[15];
    char nationality[15];
    char email[20];
    char period[10];
    char arrivaldate[10];
} s;
```
All customer data is stored in binary format in the file `add.txt`.

---

## **How to Run**
1. **Compile the Code:**
   - Use a C compiler like GCC:
     ```bash
     gcc hotel_management.c -o hotel_management
     ```
2. **Run the Executable:**
   - Execute the compiled program:
     ```bash
     ./hotel_management
     ```
3. **Login:**
   - Enter the pre-defined credentials:
     - Username: `user`
     - Password: `pass`

4. **Navigate the Menu:**
   - Follow the on-screen instructions to access different functionalities.
