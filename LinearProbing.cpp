#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>  
// #include "HashTable.cpp"
using namespace std;

int hashValue(string, int);
int findTarget(string , vector<string>, int );

int main(){
    int setChoice;
    int size = 0;
    cout << "Program 1b - Hash table with linear probing " << endl;
    cout << "1. Set A (100 email addresses) \n2. Set B (100,000 email addresses) \n3. Set C (500,000 email addresses) "  << endl;
    cout << "Enter number of data set you want to test: ";
    cin >> setChoice; 

    cout << "\n\nLinear probing hash table, size of the table = " << (1.5 * ((setChoice == 1) ? 100 : ((setChoice == 2) ? 100000 : 500000))) << endl;
    size = (1.5 * ((setChoice == 1) ? 100 : ((setChoice == 2) ? 100000 : 500000)));   

    string  chosenFile = (setChoice == 1 ? "A" : (setChoice == 2 ? "B" : "C"));
    string fileName = "Set" + chosenFile +  ".txt";
    ifstream fileInput(fileName);
    string email;
    string target;
    string foundTargets[10];
    string notFoundTargets[10] = {"00gt5.oetw2.Aytep@com", "00gt5.oetw2.Aytep@ewfe", "00gt5.oetw2.Aytep@225", "00gt5.1452.Aytep@123", "00gt5.1452.Aytep@sfd", "00gt5.1452.Aytep@uyf",
    "00gt5.1452.Aytep@32f", "00gt5.1452.saddw@344", "53d63.1452.Aytep@uyf","00gt5.1452.Aytep@uyf" };
    int numberOfCollusion = 0;
    vector<string> linearHashTable(size); // array to store emails in linear probing
    auto startInsert = chrono::system_clock::now();
    while(fileInput >> email){ // retrieve emails from the file 
		int hashValueOfEmail = hashValue(email,size);
        if(linearHashTable[hashValueOfEmail] ==  "") // if the array position with index = hash value of the email is empty, insert the email there 
                linearHashTable[hashValueOfEmail] = email;
        else{ // if the array position with index = hash value is filled by other email, start looking for an empty position
            for(int i = 0; i < size; ++i){
                if(hashValueOfEmail + i < size){ // make sure that the index doesn't exceed the size of the array
                    if(linearHashTable[hashValueOfEmail + i] ==  ""){
                        linearHashTable[hashValueOfEmail + i ] = email;
                        numberOfCollusion++;
                        break;
                    }
                }
                else{ // if there is no free slot until the end of the array (size - 1), start looking from the beginning of the array
                    for(int x = 0; x < hashValueOfEmail; ++x){
                        if(linearHashTable[x] == ""){ // free slot found
                            linearHashTable[x] = email;
                            numberOfCollusion++;
                            break; 
                        }
                    }
                    break;
                }
            }
        }
    }
    auto endInsert = chrono::system_clock::now();
    chrono::duration<double> Insertduration = endInsert - startInsert;
    cout << "Inserting duration: " << Insertduration.count() << "s\n";
    fileInput.close();



    srand((unsigned) time(0));

    for(int i = 0; i < 10; ++i){
        int randIndex = (rand() % size);
        if(linearHashTable[randIndex] != "")
            foundTargets[i] = linearHashTable[randIndex]; // get 10 random emails from the hash table and assign them to the could be found targets.
        else
            --i;
    }


    auto startSearchFound = chrono::system_clock::now();
    int foundAt[10];
    for(int j = 0; j < 10; ++j){
        // findTarget(foundTargets[j], linearHashTable ,size);
		string target = foundTargets[j];
		int hashValueOfTarget = hashValue(target,size);
		
		for(int i = 0; i < size; ++i){ //iterate over the array
			if(hashValueOfTarget + i < size){ // as long as hashVale of the target + current iterating location doesn't exceed the size of the array (last index)
				if(linearHashTable[hashValueOfTarget + i] == target ){ // if the item is found on its hashValue index, the loop will break
					foundAt[j] = hashValueOfTarget + i;
					break;
				}
				else if(linearHashTable[hashValueOfTarget + i] == ""){ // if the haveValueOfTarget index is empty, that means it doesn't exist
					foundAt[j] = -1;
					break;
				}
			}
			else{ // if hash value + current location exceeded the array size, move to the beginning of the array.
				for(int x = 0; x < hashValueOfTarget; ++x){
					if(linearHashTable[x] == target){
						foundAt[j] =  x;
						break;
					}
					else if(linearHashTable[x] == ""){
						foundAt[j]= -1;
						break;
					}
				}
				break;
			}
		}
    }
    auto endSearchFound = chrono::system_clock::now();
    chrono::duration<double> searchFoundDuration = endSearchFound - startSearchFound;
    cout << "Search duration(found): " << searchFoundDuration.count() << "s\n";

    auto startSearchNotFound = chrono::system_clock::now();
    for(int j = 0; j < 10; ++j){
        // findTarget(notFoundTargets[j], linearHashTable ,size);
        string target = notFoundTargets[j];
		int hashValueOfTarget = hashValue(target,size);
		int foundAt;
		for(int i = 0; i < size; ++i){
			if(hashValueOfTarget + i < size){// as long as hashVale of the target + current iterating location doesn't exceed the size of the array (last index)
				if(linearHashTable[hashValueOfTarget + i] == target ){
					// cout << "Target found at :"  << hashValue(target,size) << endl;
					foundAt = hashValueOfTarget + i;
					break;
				}
				else if(linearHashTable[hashValueOfTarget + i] == ""){
					foundAt = -1;
					break;
				}
			}
			else{
				for(int x = 0; x < hashValueOfTarget; ++x){// if hash value + current location exceeded the array size, move to the beginning of the array.
					if(linearHashTable[x] == target){
						// cout << "Target found at :"  << hashValue(target,size) << endl;
						foundAt =  x;
						break;
					}
					else if(linearHashTable[x] == ""){
						foundAt = -1;
						break;
					}
				}
				break;
			}
		}
    }
    auto endSearchNotFound = chrono::system_clock::now();
    chrono::duration<double> searchNotFoundDuration = endSearchNotFound - startSearchNotFound;
    cout << "Search duration(not found): " << searchNotFoundDuration.count() << "s\n";
    cout << "Number of collusion: "<< numberOfCollusion << endl;

    for(int i = 0; i < 10; ++i){
        cout << "Target #" << i << ": " <<  foundTargets[i] << " found at: " << foundAt[i] << endl;
    }


    return 0;
}

int hashValue(string str, int tableSize){
    int p = 67; // close prime number to the number of possible different characters in the string
    int m = tableSize;
    long long power_of_p = 1;
    long long hash = 0;
    for (int i = 0; i < str.length(); i++) {
        hash = ((hash + (str[i] - '.' + 1)) * power_of_p) % m;
        
        power_of_p = (power_of_p * p) % m;        
    }
    return hash;
}


// using a function to find the emails is slower
// int findTarget(string target, vector<string> linearHashTable, int size){
//     int hashValueOfTarget = hashValue(target,size);
//     int foundAt;
//     for(int i = 0; i < size; ++i){
//         if(hashValueOfTarget + i < size){
//             if(linearHashTable[hashValueOfTarget + i] == target ){
//                 // cout << "Target found at :"  << hashValue(target,size) << endl;
//                 foundAt = hashValueOfTarget + i;
//                 break;
//             }
//             else if(linearHashTable[hashValueOfTarget + i] == ""){
//                 foundAt = -1;
//                 break;
//             }
//         }
//         else{
//             for(int x = 0; x < size; ++x){
//                 if(linearHashTable[x] == target){
//                     // cout << "Target found at :"  << hashValue(target,size) << endl;
//                     foundAt =  x;
//                     break;
//                 }
//                 else if(linearHashTable[x] == ""){
//                     foundAt = -1;
//                     break;
//                 }
//             }
//             break;
//         }
//     }
//     return foundAt; 
// }