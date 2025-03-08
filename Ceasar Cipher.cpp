//Ceasar Cipher
#include<iostream>

using namespace std;

int main(){
    cout<<"-------Welcome to Ceasar Cipher Encryption and Decryption Program--------"<<endl;
    cout<<"-----------------------By: Syed Waleed-----------------------------"<<endl;
    char choose;
    int choice;
    do{
    cout<<"1. Encrypt"<<endl;
    cout<<"2. Decrypt"<<endl;
    cin>>choice;
    cin.ignore();

    if(choice == 1){
        string text;
        cout << "Enter the text to be encrypted: ";
        getline(cin, text);
    
        int shift;
        cout << "Enter the shift value: ";
        cin >> shift;
        cin.ignore();
    
        string encryptedText = "";
    
        for (int i = 0; i < text.length(); i++) {
            char c = text[i];
    
            if (isalpha(c)) {
                if (islower(c)) {
                    encryptedText += char(((c - 'a' + shift) % 26) + 'a');
                } else {
                    encryptedText += char(((c - 'A' + shift) % 26) + 'A');
                }
            } else {
                encryptedText += c;
            }
        }
    
        cout << "Encrypted text: " << encryptedText << endl;
            
    }else if(choice == 2){
        string encryptedText;
    cout << "Enter the text to be decrypted: ";
    getline(cin, encryptedText);

    int shift;
    cout << "Enter the shift value: ";
    cin >> shift;
    cin.ignore();

    string decryptedText = "";

    for (int i = 0; i < encryptedText.length(); i++) {
        char c = encryptedText[i];

        if (isalpha(c)) {
            if (islower(c)) {
                decryptedText += char(((c - 'a' - shift + 26) % 26) + 'a');
            } else {
                decryptedText += char(((c - 'A' - shift + 26) % 26) + 'A');
            }
        } else {
            decryptedText += c;
        }
    }

    cout << "Decrypted text: " << decryptedText << endl;
    }else{
        cout << "Invalid choice" << endl;
    }
    cout << "\nDo you want to continue? (Y/N): ";
    cin >> choose;
    cin.ignore();

} while (choose == 'Y' || choose == 'y');

cout << "Program terminated. Goodbye!" << endl;

    return 0;
}