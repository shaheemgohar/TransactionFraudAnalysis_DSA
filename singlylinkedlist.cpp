#include  <stdio.h>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <chrono> 
#include <iomanip>
#include <cmath>

#include "json.hpp"

using namespace std;
using namespace std::chrono;

struct Transaction{
    ///--------------------------
    string transaction_id;
    string timestamp;
    string sender_account;
    string receiver_account;
    double amount;
    string transaction_type;
    string merchant_category;
    string location;
    string device_used;
    string is_fraud;
    string fraud_type;
    double time_since_last_transaction; 
    float spending_deviation_score; 
    float velocity_score;
    float geo_anomaly_score;
    string payment_channel;
    string ip_address; //change to string
    string device_hash;
    ///---------------------------------------------------
    };
struct node{
  struct Transaction data;
  struct node * next;   //it'll point to the next struct {}
};

void add_at_pos(struct node * head, int data, int pos);
struct node * add_in_beginning(struct node*head, struct Transaction data);
struct node * del_first(struct node * head);
void del_last(struct node * head);
void print_list(struct node * head);
void print_performance_metrics(const string& algo_name, double execution_time_ms, size_t memory_used_bytes);
nlohmann::json transactionToJson(const Transaction& t);
std::string generateJsonFromLinkedList(struct node* head);

struct node* deep_copy_list(struct node* original_head);
void free_list(struct node* head);

double safe_stod(const string& s, double defaultValue = 0.0);
float safe_stof(const string& s, float defaultValue = 0.0f);
int size_of_linked_list(struct node * head);

struct node * get_middle(struct node * head);
struct node * mergesort(struct node * head);
struct node * merge(struct node * a, struct node * b);

struct node * selection_sort(struct node * head);

//searches
void linked_list_linear_search(struct node * head,const string &trans_id, const string &trans_location, const string &transaction_type_to_find);
void linked_list_block_search(struct node * head, const string &trans_id, const string& trans_location, const string& transaction_type_to_find);
void linked_list_binary_search(struct node * head, const string & trans_id, const string& translocation, const string &transaction_type_to_find);

int main(){
    
    struct node * head_UPI = NULL; 
    struct node * head_wireTransfer= NULL;
    struct node * head_ach= NULL;
    struct node * head_card= NULL;
    // struct node * head = NULL;

    //to open the csv
    ifstream iFile;
    iFile.open("C:\\Users\\DreamDreams\\Documents\\University\\C++\\Assignment\\Assignment_pt1\\financial_fraud_detection_dataset.csv");
    if (!iFile.is_open()) {
    cerr << "Error: Could not open the CSV file. Please check the path and permissions." << endl;
    return 1; // Exit main with an error code
    }
    string headerline;
    getline(iFile, headerline);
    string line = "";
    int pr_r = 0;
//to form the linked list
    while(getline(iFile, line) && pr_r < 50000){
        Transaction currentTransaction;
        string tempString;
        stringstream ss(line);

        getline(ss, tempString, ',');
        currentTransaction.transaction_id = tempString;
        // cout << tempString << endl;

        getline(ss, tempString, ',');
        currentTransaction.timestamp = tempString;
        // cout << tempString << endl;

        getline(ss, tempString, ',');
        currentTransaction.sender_account = tempString;
        // cout << tempString << endl;

        getline(ss, tempString, ',');
        currentTransaction.receiver_account = tempString;
        // cout << tempString << endl;
      

        getline(ss, tempString, ',');
        currentTransaction.amount = safe_stod(tempString);
        // cout << tempString << endl;
        
        getline(ss, tempString, ',');
        currentTransaction.transaction_type = tempString;
        // cout << tempString << endl;

       
        getline(ss, tempString, ',');
        currentTransaction.merchant_category = tempString;
        // cout << tempString << endl;

        getline(ss, tempString, ',');
        currentTransaction.location = tempString;
        // cout << tempString << endl;

        getline(ss, tempString, ',');
        currentTransaction.device_used = tempString;
        // cout << tempString << endl;


        getline(ss, tempString, ',');
        currentTransaction.is_fraud = tempString;
        // cout << tempString << endl;

       
       
        getline(ss, tempString, ',');
        currentTransaction.fraud_type = tempString;
        // cout << tempString << endl;

        
        getline(ss, tempString, ',');
        currentTransaction.time_since_last_transaction = safe_stod(tempString);
        // cout << tempString << endl;


        
        getline(ss, tempString, ',');
        currentTransaction.spending_deviation_score = safe_stof(tempString);
        // cout << tempString << endl;

        
        getline(ss, tempString, ',');
        currentTransaction.velocity_score = safe_stof(tempString);
        // cout << tempString << endl;

        
        getline(ss, tempString, ',');
        currentTransaction.geo_anomaly_score = safe_stof(tempString);
        // cout << tempString << endl;


        getline(ss, tempString, ',');
        currentTransaction.payment_channel = tempString;
        // cout << tempString << endl;


        getline(ss, tempString, ',');
        currentTransaction.ip_address = tempString;
        // cout << tempString << endl;


        getline(ss, tempString, ',');
        currentTransaction.device_hash = tempString; 
        // cout << tempString << endl;

//to store according the transaction according to the payment channel
        if (currentTransaction.payment_channel == "UPI") {
            // cout << "hello we here 1" << endl;
        head_UPI= add_in_beginning(head_UPI, currentTransaction);
    } else if (currentTransaction.payment_channel == "wire_transfer") {
        // cout << "hello we here 2" << endl;
        head_wireTransfer= add_in_beginning(head_wireTransfer, currentTransaction);
    } else if (currentTransaction.payment_channel == "ACH") {
        // cout << "hello we here 3 " << endl;
        head_ach= add_in_beginning(head_ach, currentTransaction);
    } else if (currentTransaction.payment_channel == "card"){
        // cout << "hello we here 4" << endl;
        head_card = add_in_beginning(head_card, currentTransaction);
    } else {
        // cout << "hello we here 5 " << endl;
        cout << "Warning: Unrecognized payment channel: " << currentTransaction.payment_channel << endl;
    }
    pr_r += 1;
    // cout << "pr: " << pr_r << endl;
}

cout << "Transactions Loaded." << endl;
//to search
string trans_id = "T108863";
string trans_type_to_search = "payment";
string trans_location = "Berlin";

char option_head = ' ';
struct node * current_channel_head = NULL;
while(true){
    while(true){
        cout << "Which payment channel do you want to analyse?\n1. Card\n2. UPI\n3. ACH\n4. Wire Transfer\nEnter (1-4): ";
        cin >> option_head;
        if(option_head == '1'){
         current_channel_head = deep_copy_list(head_card);
            break;
        }
        else if(option_head == '2'){
            current_channel_head = deep_copy_list(head_UPI);
            break;
        }
        else if(option_head == '3'){
            current_channel_head = deep_copy_list(head_ach);
            break;
        }
        else if(option_head == '4'){
            current_channel_head = deep_copy_list(head_wireTransfer);
            break;
        }
        else{

            cout << "Please enter valid input (1-4): ";
        }
    }
    char option_metrics = ' ';
    cout << "Choose the operation you would like see the metrics of\n1. Merge Sort and Linear Search\n2. Merge Sort and Block Search\n3. Selection Sort and Linear Search\n4. Selection Sort and Block Search\n5. Generate JSON Output file\n6. Exit\nEnter number (1-5): ";
    cin >> option_metrics;

    if(option_metrics == '1'){
        //start timer
        auto start_time = high_resolution_clock::now();
        //sorting

            current_channel_head = mergesort(current_channel_head);
        //searching
            linked_list_linear_search(current_channel_head, trans_id, trans_location, trans_type_to_search);

        //stop timer    
            auto end_time = high_resolution_clock::now();

        //calculating metrics
        // The duration_cast converts the time difference to milliseconds
            auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
            double execution_time_ms = duration_ms.count();

        // 2. Calculate the memory usage
        // This requires a function to count the nodes in your list
            size_t list_size = size_of_linked_list(current_channel_head);
        // We multiply the number of nodes by the size of one node struct
            size_t memory_used_bytes = list_size * sizeof(struct node); // This is an approximate value
            print_performance_metrics("Merge Sort and Linear Search", execution_time_ms, memory_used_bytes);
            
    }else if(option_metrics == '2'){
        
        //start timer
        auto start_time = high_resolution_clock::now();
        //sorting
            current_channel_head = mergesort(current_channel_head);
        //searching
            linked_list_block_search(current_channel_head, trans_id, trans_location, trans_type_to_search);

        //stop timer    
            auto end_time = high_resolution_clock::now();

        //calculating metrics
        // The duration_cast converts the time difference to milliseconds
            auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
            double execution_time_ms = duration_ms.count();

        // 2. Calculate the memory usage
        // This requires a function to count the nodes in your list
            size_t list_size = size_of_linked_list(current_channel_head);
        // We multiply the number of nodes by the size of one node struct
            size_t memory_used_bytes = list_size * sizeof(struct node); // This is an approximate value
        // print_list(current_channel_head);

            print_performance_metrics("Merge Sort and Block Search", execution_time_ms, memory_used_bytes);
            
    }else if (option_metrics == '3'){

        //start timer
        auto start_time = high_resolution_clock::now();
        //sorting
            current_channel_head = selection_sort(current_channel_head);
        //searching
            linked_list_linear_search(current_channel_head, trans_id, trans_location, trans_type_to_search);

            //stop timer    
            auto end_time = high_resolution_clock::now();

        //calculating metrics
        // The duration_cast converts the time difference to milliseconds
            auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
            double execution_time_ms = duration_ms.count();

        // 2. Calculate the memory usage
        // This requires a function to count the nodes in your list
            size_t list_size = size_of_linked_list(current_channel_head);
        // We multiply the number of nodes by the size of one node struct
            size_t memory_used_bytes = list_size * sizeof(struct node); // This is an approximate value

            print_performance_metrics("Selection Sort and Linear Search", execution_time_ms, memory_used_bytes);
            
            
    }else if (option_metrics == '4'){

        //start timer
        auto start_time = high_resolution_clock::now();
        //sorting
            current_channel_head = selection_sort(current_channel_head);
        //searching
            linked_list_block_search(current_channel_head, trans_id, trans_location, trans_type_to_search);

        //stop timer    
            auto end_time = high_resolution_clock::now();

        //calculating metrics
        // The duration_cast converts the time difference to milliseconds
            auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
            double execution_time_ms = duration_ms.count();

        // 2. Calculate the memory usage
        // This requires a function to count the nodes in your list
            size_t list_size = size_of_linked_list(current_channel_head);
        // We multiply the number of nodes by the size of one node struct
            size_t memory_used_bytes = list_size * sizeof(struct node); // This is an approximate value
            print_performance_metrics("Selection Sort and Jump Search", execution_time_ms, memory_used_bytes);
    }else if(option_metrics == '5'){
     if (current_channel_head == nullptr) { // Check if data is loaded
            cout << "Please load data first (Option 1).\n";
            break;
        }
        string json_output = generateJsonFromLinkedList(current_channel_head);
        cout << "\n--- Generated JSON Output ---\n";
        

        ofstream outFile("transactions.json");
        if (outFile.is_open()) {
            outFile << json_output;
            outFile.close();
            cout << "JSON data successfully saved to transactions.json\n";
        } else {
            cerr << "Error: Unable to open file for JSON export.\n";
    }   
        
    }else if(option_metrics == '6'){
        cout << "Thank you." << endl;
        break;
        
    }else{
        cout << "wrong input please enter digit" << endl;
    }
    free_list(current_channel_head); 

}
    
    cout << "\nRows inspected: " << pr_r << endl;
    // int size_of_ll = size_of_linked_list(current_channel_head);
    // cout << "Size of head: "  << size_of_ll;
    return 0;
}
// ------------------------------------------------------

struct node* deep_copy_list(struct node* original_head) {
    if (original_head == NULL) {
        return NULL;
    }

    struct node* new_head = NULL;
    struct node* current_original = original_head;
    struct node* current_new = NULL;

    while (current_original != NULL) {
        // Allocate a new node
        struct node* new_node = new struct node; // 'new' if you're using 'delete' for freeing memory
                                                

        // Copy the entire Transaction data structure
        new_node->data = current_original->data; 
        new_node->next = NULL; // Initialize next to NULL

        if (new_head == NULL) {
            new_head = new_node;
            current_new = new_node;
        } else {
            current_new->next = new_node;
            current_new = new_node;
        }
        current_original = current_original->next;
    }
    return new_head;
}

void free_list(struct node* head) {
    struct node* current = head;
    while (current != NULL) {
        struct node* next = current->next;
        delete current; // 'delete' if you allocated with 'new'
        current = next;
    }
}

std::string generateJsonFromLinkedList(struct node* head) {
    nlohmann::json root_obj; // This will be the root JSON object
    nlohmann::json transactions_array = nlohmann::json::array(); // This will hold all your transaction objects

    struct node* ptr = head;
    while (ptr != nullptr) {
        // Convert the current node's Transaction data to a JSON object
        nlohmann::json transaction_json = transactionToJson(ptr->data);
        // Add this JSON object to our array
        transactions_array.push_back(transaction_json);
        ptr = ptr->next;
    }

    // Put the array of transactions into the root object under a key, e.g., "all_transactions"
    root_obj["all_transactions"] = transactions_array;

    // Return the JSON as a pretty-printed string (4 spaces indent)
    return root_obj.dump(4);
}

nlohmann::json transactionToJson(const Transaction& t) {
    nlohmann::json j;
    j["transaction_id"] = t.transaction_id;
    j["timestamp"] = t.timestamp;
    j["sender_account"] = t.sender_account;
    j["receiver_account"] = t.receiver_account;
    j["amount"] = t.amount;
    j["transaction_type"] = t.transaction_type;
    j["merchant_category"] = t.merchant_category;
    j["location"] = t.location;
    j["device_used"] = t.device_used;
    j["is_fraud"] = t.is_fraud; // This will now correctly convert your bool to true/false
    j["fraud_type"] = t.fraud_type;
    j["time_since_last_transaction"] = t.time_since_last_transaction;
    j["spending_deviation_score"] = t.spending_deviation_score;
    j["velocity_score"] = t.velocity_score;
    j["geo_anomaly_score"] = t.geo_anomaly_score;
    j["payment_channel"] = t.payment_channel;
    j["ip_address"] = t.ip_address;
    j["device_hash"] = t.device_hash;
    return j;
}

struct node* selection_sort(struct node* head) {
    // The main traversal pointer for the outer loop
    struct node* current = head;

    while (current != NULL) {
        struct node* min_node = current;
        
        struct node* runner = current->next;
        
        while (runner != NULL) {
            if (runner->data.location < min_node->data.location) {
                min_node = runner;
            }
            runner = runner->next;
        }

        // --- Swap the data of the current node and the minimum node ---
        if (min_node != current) {
            Transaction temp_data = current->data;
            current->data = min_node->data;
            min_node->data = temp_data;
        }

        current = current->next;
    }

    // Return the head of the sorted list (it's the same head)
    return head;
}

struct node * merge(struct node * a, struct node * b){
    struct node * result = NULL;

    if ( a == NULL){
        return b;
    }
    if( b == NULL){
        return a;
    }

    if (a ->data.location <= b -> data.location){
        result =  a;
        result -> next = merge(a->next, b);
    }else{
        result = b;
        result -> next = merge(a, b -> next);
    }
    return result;
}

struct node * mergesort(struct node * head){
    //base case
    if( head == NULL || head -> next == NULL){
        return head; 
    }

    struct node * mid = get_middle(head);
    struct node * next_to_mid = mid -> next; //head to the 2nd L.L

    mid -> next = NULL;

    struct node * left = mergesort(head);
    struct node * right = mergesort(next_to_mid);

    return merge(left, right);
}

struct node * get_middle(struct node * head){
    if(head == NULL || head -> next == NULL){
        return head; // the size is 0 or 1 which is already the middle
    } 
    //we traverse the list we 2x and 1x speed, which will give us the mid point
    struct node * slow = head;
    struct node * fast = head -> next;

    while(fast != NULL && fast -> next != NULL){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
}

int size_of_linked_list(struct node * head){
    int count = 0;
    struct node * ptr = head;
    while ( ptr != NULL){
        count++;
        ptr = ptr -> next;
    }
    return count;
}

double safe_stod(const string& s, double defaultValue) {
    try {
        return s.empty() ? defaultValue : stod(s);
    } catch (...) {
        return defaultValue;
    }
}

float safe_stof(const string& s, float defaultValue) {
    try {
        return s.empty() ? defaultValue : stof(s);
    } catch (...) {
        return defaultValue;
    }
}

void print_list(struct node * head){
    struct node * ptr = head;  //ptr has the same value address as head
    int i = 0;
    while(ptr != NULL){
    
        cout << "Transaction " << i + 1 << ":\n";
        cout << "  ID: " << ptr ->data.transaction_id << "\n";
        cout << "  Timestamp: " << ptr -> data.timestamp << "\n";
        cout << "  Sender: " << ptr -> data.sender_account << "\n";
        cout << "  Receiver: " << ptr -> data.receiver_account << "\n";
        cout << "  Amount: " << ptr -> data.amount << "\n";
        cout << "  Type: " << ptr -> data.transaction_type << "\n";
        cout << "  Merchant Category: " << ptr -> data.merchant_category << "\n";
        cout << "  Location: " << ptr -> data.location << "\n";
        cout << "  Device Used: " << ptr -> data.device_used << "\n";
        cout << "  Is Fraud: " << ptr -> data.is_fraud << "\n";
        cout << "  Fraud Type: " << ptr -> data.fraud_type << "\n";
        cout << "  Time Since Last Transaction: " << ptr->data.time_since_last_transaction << "\n";
        cout << "  Spending Deviation Score: " << ptr -> data.spending_deviation_score << "\n";
        cout << "  Velocity Score: " << ptr -> data.velocity_score << "\n";
        cout << "  Geo Anomaly Score: " << ptr -> data.geo_anomaly_score << "\n";
        cout << "  Payment Channel: " << ptr -> data.payment_channel << "\n";
        cout << "  IP Address: " << ptr -> data.ip_address << "\n";
        cout << "  Device Hash: " << ptr -> data.device_hash << "\n\n";

        i ++;
        ptr = ptr -> next;
    }
}

void print_node(struct node * ptr){
       
        cout << "  ID: " << ptr ->data.transaction_id << "\n";
        cout << "  Timestamp: " << ptr -> data.timestamp << "\n";
        cout << "  Sender: " << ptr -> data.sender_account << "\n";
        cout << "  Receiver: " << ptr -> data.receiver_account << "\n";
        cout << "  Amount: " << ptr -> data.amount << "\n";
        cout << "  Type: " << ptr -> data.transaction_type << "\n";
        cout << "  Merchant Category: " << ptr -> data.merchant_category << "\n";
        cout << "  Location: " << ptr -> data.location << "\n";
        cout << "  Device Used: " << ptr -> data.device_used << "\n";
        cout << "  Is Fraud: " << ptr -> data.is_fraud << "\n";
        cout << "  Fraud Type: " << ptr -> data.fraud_type << "\n";
        cout << "  Time Since Last Transaction: " << ptr->data.time_since_last_transaction << "\n";
        cout << "  Spending Deviation Score: " << ptr -> data.spending_deviation_score << "\n";
        cout << "  Velocity Score: " << ptr -> data.velocity_score << "\n";
        cout << "  Geo Anomaly Score: " << ptr -> data.geo_anomaly_score << "\n";
        cout << "  Payment Channel: " << ptr -> data.payment_channel << "\n";
        cout << "  IP Address: " << ptr -> data.ip_address << "\n";
        cout << "  Device Hash: " << ptr -> data.device_hash << "\n\n";

}

struct node * del_first(struct node * head){
    //we create a temp pointer to point to the node to del
    struct node * temp = head;
    head = head -> next;
    free(temp);
    temp = NULL;
    return head;
}

void del_last(struct node *head){
    struct node * ptr = new struct node;
    struct node * ptr2 = new struct node;

    ptr = head; // to del
    ptr2 = head; // new last

    while(ptr -> next != NULL){
        ptr2 = ptr;
        ptr = ptr -> next;
    }
    free(ptr);
    ptr2 -> next = NULL;
    ptr = NULL;

}

void add_at_pos(struct node * head, struct Transaction data, int pos) {
    //create the new node
    struct node * ptr = new struct node;
    ptr -> data = data;
    ptr -> next = NULL;
    struct node * ptr2 = head;
    //traversing to one pos behind the loc
    //we do pos -1 to match the index = 0
    pos--;
    //now we traverse
while (pos != 1){ //as head is 1 
    ptr2 = ptr2 -> next;
    pos--;    
    }
    //first we point the new nodes link to the ptr2's link
    ptr -> next = ptr2 -> next;
    ptr2 -> next = ptr;

}

struct node * add_in_beginning(struct node*head, struct Transaction data){
    struct node * ptr = new struct node;
    if (ptr == NULL) { // <<< ADD THIS CHECK!
        cerr << "Error: Memory allocation failed for a new node!" << endl;
        return head;
    }

    ptr -> data = data;
    ptr->next = head;
    head = ptr;
    return head; //should return the address to the head of the newly created node
}

void linked_list_linear_search(struct node * head,const string &trans_id, const string &trans_location, const string &transaction_type_to_find){
    cout << "\n--- Searching for the following transaction details \nTransaction ID: " << trans_id << "\nLocation: " << trans_location << "\nTransaction Type: " << transaction_type_to_find << "\n ---\n" << endl;
    struct node * ptr = head;
    int found_count = 0; // a dedicated counter for found transactions

    while(ptr != NULL ){
        if(ptr -> data.transaction_type == transaction_type_to_find && ptr ->data.transaction_id == trans_id && ptr -> data.location == trans_location){
            found_count++;
            cout << "Transaction " << found_count << endl; 
            cout << "  ID: " << ptr ->data.transaction_id << endl;
            cout << "  Timestamp: " << ptr -> data.timestamp << endl;
            cout << "  Sender: " << ptr -> data.sender_account << endl;
            cout << "  Receiver: " << ptr -> data.receiver_account << endl;
            cout << "  Amount: " << ptr -> data.amount << endl;
            cout << "  Type: " << ptr -> data.transaction_type << endl;
            cout << "  Merchant Category: " << ptr -> data.merchant_category << endl;
            cout << "  Location: " << ptr -> data.location << endl;
            cout << "  Device Used: " << ptr -> data.device_used << endl;
            cout << "  Is Fraud: " << ptr -> data.is_fraud << endl;
            cout << "  Fraud Type: " << ptr -> data.fraud_type << endl;
            cout << "  Time Since Last Transaction: " << ptr->data.time_since_last_transaction << endl;
            cout << "  Spending Deviation Score: " << ptr -> data.spending_deviation_score << endl;
            cout << "  Velocity Score: " << ptr -> data.velocity_score << endl;
            cout << "  Geo Anomaly Score: " << ptr -> data.geo_anomaly_score << endl;
            cout << "  Payment Channel: " << ptr -> data.payment_channel << endl;
            cout << "  IP Address: " << ptr -> data.ip_address << endl;
            cout << "  Device Hash: " << ptr -> data.device_hash << "\n\n"; 
        }
        ptr = ptr -> next; // Move to the next node regardless of whether a match was found
    }
    
    
    if (found_count == 0) {
        cout << "No transactions of type '" << transaction_type_to_find << "' were found." << endl;
    }
    cout << "--- Search complete. Found " << found_count << " transaction(s). ---" << endl;
}

void linked_list_block_search(struct node * head, const string &trans_id, const string& trans_location, const string& transaction_type_to_find){
    cout << "\n--- Searching for the following transaction details \nTransaction ID: " << trans_id << "\nLocation: " << trans_location << "\nTransaction Type: " << transaction_type_to_find << "\n ---\n" << endl;

    if (head == NULL) {
        cout << "No transactions of type '" << transaction_type_to_find << "' were found." << endl;
        cout << "--- Search complete. Found 0 transaction(s). ---" << endl;
        return;
    }

    int n = size_of_linked_list(head);
    
    if (n == 0) {
        cout << "No transactions of type '" << transaction_type_to_find << "' were found." << endl;
        cout << "--- Search complete. Found 0 transaction(s). ---" << endl;
        return;
    }

    int jump_distance = sqrt(n);

    struct node * prev = head;
    struct node * current = head;

    while (current != NULL && current->data.location < trans_location) {
        prev = current;

        for (int i = 0; current != NULL && i < jump_distance; ++i) {
            current = current->next;
        }
    }

    current = prev;

    int found_count = 0;
    int transaction_display_index = 1;

    while (current != NULL && current->data.location <= trans_location) {
        if (current->data.location == trans_location) {
            if (current->data.transaction_type == transaction_type_to_find && current->data.transaction_id == trans_id) {
                found_count++;
                cout << "Transaction " << transaction_display_index++ << endl;
                // Call your print_node function here
                print_node(current);
            }
        } else {
            break;
        }
        current = current->next;
    }

    if (found_count == 0) {
        cout << "No transactions of type '" << transaction_type_to_find << "' were found." << endl;
    }
    cout << "--- Search complete. Found " << found_count << " transaction(s). ---" << endl;
}

void print_performance_metrics(const string& algo_name, double execution_time_ms, size_t memory_used_bytes) {
    cout << "\n---------------------------------------------------" << endl;
    cout << "           PERFORMANCE METRICS - " << algo_name << endl;
    cout << "---------------------------------------------------" << endl;
    cout << left << setw(30) << "Execution Time (ms):" << right << setw(15) << fixed << setprecision(3) << execution_time_ms << endl;
    cout << left << setw(30) << "Memory Usage (bytes):" << right << setw(15) << memory_used_bytes << endl;
    cout << left << setw(30) << "Memory Usage (KB):" << right << setw(15) << fixed << setprecision(2) << (double)memory_used_bytes / 1024.0 << endl;
    cout << "---------------------------------------------------\n" << endl;
}