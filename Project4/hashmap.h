//
//  HashMap.h
//  Project4
//
//  Created by venkat on 3/7/24.
//

#include <vector>
#include <string>
#include <list>
#ifndef HashMap_h
#define HashMap_h

template <typename T>
class HashMap
{
public:
    // Constructor
    HashMap(double max_load = 0.75){
        numBucks = 10; // Initialize number of buckets
        // Initialize buckets with empty lists
        for(int i = 0; i < numBucks; i++){
            std::list<Pair> l1;
            buckets.push_back(l1);
        }
        m_mxload = max_load; // Set maximum load factor
        numObjs = 0; // Initialize number of objects
    }
    // Destructor
    ~HashMap(){
        buckets.clear(); // Clear the buckets
    }
    // Return the number of associations in the hashmap
    int size() const{
        return numObjs;
    }
    // Insert a key-value pair into the hashmap
    void insert(const std::string& key, const T& value);
    // Find the value associated with the given key
    const T* find(const std::string& key) const{
        unsigned int hashVal = getHashVal(key);
        // Search for the key in the appropriate bucket
        for(typename std::list<Pair>::const_iterator p = buckets.at(hashVal % numBucks).begin(); p != buckets.at(hashVal % numBucks).end(); p++){
            if(hashVal == getHashVal((*p).m_key)){
                return &((*p).m_val);
            }
        }
        return nullptr; // Key not found
    }
    // Non-const version of find method
    T* find(const std::string& key) {
        const auto& hm = *this;
        return const_cast<T*>(hm.find(key));
    }
    // Bracket operator for HashMap
    T& operator[](const std::string& key){
        T* obj = find(key);
        if(obj != nullptr){
            return *obj;
        }
        T val = T();
        insert(key, val);
        T* obj2 = find(key);
        return *obj2;
    }
    
private:
    // Struct representing key-value pairs
    struct Pair{
        Pair(std::string key, T val){
            m_key = key;
            m_val = val;
        }
        std::string m_key; // Key
        T m_val; // Value
    };
    std::vector<std::list<Pair>> buckets; // Vector of buckets
    bool findNUpdateList(const std::string key, const T value, std::list<Pair> l){
        T* val = find(key);
        if(val != nullptr){
            *val = value; // Update value if key exists
            return true;
        }
        return false; // Key not found
    }
    
    // Hash function to compute hash value of a key
    unsigned int getHashVal(std::string key) const{
        std::hash<std::string> str_hash;
        unsigned int hashValue = str_hash(key);
        return hashValue;
    }
    // Rehash the hashmap when load factor exceeds the threshold
    void rehash(){
        std::vector<std::list<Pair>> buckets2;
        int numBucks2 = 2 * numBucks;
        // Initialize new buckets
        for(int i = 0; i < numBucks2; i++){
            std::list<Pair> l1;
            buckets2.push_back(l1);
        }
        // Rehash each key-value pair
        for(int i = 0; i < numBucks; i++){
            for(typename std::list<Pair>::iterator p = buckets.at(i).begin(); p != buckets.at(i).end(); p++){
                unsigned int hashValue = getHashVal((*p).m_key);
                buckets2.at(hashValue % numBucks2).push_back(Pair((*p).m_key, (*p).m_val));
            }
        }
        buckets.swap(buckets2); // Swap old and new buckets
        numBucks = numBucks2; // Update number of buckets
    }
    int numBucks; // Number of buckets
    int numObjs; // Number of objects
    double m_mxload; // Maximum load factor
    
};

// Definition of insert method
template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value){
    unsigned int hashValue = getHashVal(key);
    // If bucket is empty or key does not exist, insert the key-value pair
    if(buckets.at(hashValue % numBucks).empty() || !findNUpdateList(key, value, buckets.at(hashValue % numBucks))){
        // Check if rehashing is needed
        if((double)numObjs / numBucks >= m_mxload){
            rehash();
        }
        // Insert the key-value pair into the appropriate bucket
        buckets.at(hashValue % numBucks).push_back(Pair(key, value));
        numObjs++; // Increment number of objects
    }
}

#endif /* HashMap_h */
