### Project Description: Bank Management System for ABC Bank

#### Overview

This project aims to develop a banking management system for ABC Bank to efficiently manage customer data. The system will cater to three primary stakeholders: User Clients, Company Clients, and Banking Employees. The system will handle account creation, transactions, account management, and more. The key features and requirements are detailed below.

#### Stakeholders and Account Types

1. **User Client**: An individual user account.
2. **Company Client**: A shared account opened by a company's CEO, accessible by multiple employees.
3. **Banking Employee**: A bank employee responsible for managing user and company accounts.

#### Account Types and Restrictions

1. **Bronze Account**: 
   - Daily Withdrawal Limit: 100,000 PKR
   - Available for User and Company Clients
2. **Gold Account**: 
   - Daily Withdrawal Limit: 500,000 PKR
   - Available for User and Company Clients
3. **Business Account**: 
   - Daily Withdrawal Limit: 20,000,000 PKR
   - Available for Company Clients only

#### Transactions

The banking system will support the following types of transactions:
- **Deposit**
- **Withdraw**
- **Transfer to another User Client**

#### Functional Requirements

1. **User Client**

   - **Account Creation**: A user can open a new bank account by providing the following information:
     - Full Name
     - Address
     - Phone
     - CNIC
     - Login ID
     - Password
     - Estimated Daily Withdrawal Limit
   - **Verification and Approval**: A banking employee will verify and approve the account. Upon approval, the user is assigned a 16-digit card number and prompted to set a PIN.
   - **Account Type Assignment**: The system assigns an account type based on the estimated daily withdrawal limit.
   - **File Storage**: User information is stored in `users.txt` in the format: `userid, username, user address, user cnic, user id, user password, account balance`
   - **Account Operations**:
     - Deposit and withdraw funds.
     - View account balance and transaction history.
     - Transfer funds to other accounts within the bank.
     - Proper checks to prevent overdrawing or exceeding daily limits.
     - New accounts start with a balance of 0.

2. **Company Client**

   - **Account Creation**: A company's CEO can open a shared account by providing:
     - Company’s Name
     - Company’s Address
     - Company’s Tax Number
     - Estimated Daily Withdrawal Limit
     - Account ID
     - Account Password
   - **File Storage**: Company information is stored in `companies.txt` in the format: `companyid, companyname, company address, company tax number, company user id, company password, account balance`
   - **Employee Access**: The system maintains a `companies_employees.txt` file to link user clients to company accounts.
   - **Account Operations**:
     - Deposit and withdraw funds.
     - View account balance and transaction history.
     - Transfer funds to user clients within the bank.
     - Request loans from the bank.
     - Multiple users can access the company account using their Bank User ID.

3. **Banking Employee**

   - **Login**: Employees can log in using credentials stored in `admin.txt`.
   - **Account Management**:
     - View all client accounts.
     - Approve or reject new account applications.
     - Approve or reject company loan requests.
     - View transaction history for specific accounts.
     - Freeze or close accounts if necessary.

4. **Other Requirements**

   - **Transaction Records**: Maintain a `transactions.txt` file for all client transactions in the format: `transaction date, Client User ID, Amount, Type of Transaction`. In case of a transfer, include the receiving User ID.
   - **Credit Cards**: Maintain a `cards.txt` file for client credit cards in the format: `Client User ID, Card Number, Card PIN`.
     - Transactions require the card PIN.
     - Users can have multiple cards and select which card to use for transactions.
     - After three incorrect PIN attempts, mark the account as fraudulent and report to a banking employee.
     - Banking employees can mark cards as fraudulent and freeze accounts. 

This project will involve implementing the above features using appropriate data structures and file handling techniques to ensure data integrity and security.
