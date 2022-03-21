#include <iostream>
#include <fstream>

inline int hash(std::string to_hash, uint32_t size) { return to_hash.size() % size; } 

template<typename K, typename V>
struct Entry
{
    K key{};
    V value{};
    bool taken{false};

    Entry() = default;
    Entry(K k, V v) : key{k}, value{v} {}

    friend std::ostream& operator<<(std::ostream& out, const Entry& entry) {
        out << entry.key << ": " << entry.value;
        return out;
    }
};

template <uint32_t S, typename V>
class HashMap {
    private:
        Entry<std::string, V> entries[S] = {};
        int mSize{0};
        inline int H(std::string key, int k) { return (hash(key, S) + k) % S; }

    public:

        inline int size() { return mSize; }
        inline bool is_empty() { return mSize == 0; }
        inline bool is_full() { return mSize == S; }

        V& operator[](const std::string& key)
        {
            int k = 0;
            if(is_empty())
                throw std::out_of_range("Map is empty\n");

            int curr;
            while(k != S) {
                curr = H(key, k);
                if(entries[curr].taken) {
                    if(entries[curr].key == key)
                        return entries[curr].value;
                }
                k++;
            }
            throw std::out_of_range("Key not found\n");
        }

        void insert(const Entry<std::string, V>& entry)
        {
            int k = 0, hash;
            if(is_full())
                return;

            while(true) {
                hash = H(entry.key, k);
                if(!entries[hash].taken) {
                    entries[hash].key = entry.key;
                    entries[hash].value = entry.value;
                    entries[hash].taken = true;
                    mSize++;
                    break;
                } else {
                    if(entries[hash].key == entry.key) {
                        entries[hash].value = entry.value;
                        break;
                    }
                }
                k++;
            }
        }

        void remove(const std::string& key)
        {
            int k = 0;
            if(is_empty())
                return;

            while(k != S) {
                int curr = H(key, k);
                if(entries[curr].taken) {
                    if(entries[curr].key == key) {
                        Entry<std::string, V> temp;
                        entries[curr] = temp;
                        mSize--;
                    }
                }
                k++;
            }
        }

        bool find(const std::string& key)
        {
            int k = 0;
            if(is_empty())
                return false;

            while(k != S) {
                int curr = H(key, k);
                if(entries[curr].taken) {
                    if(entries[curr].key == key)
                        return true;
                }
                k++;
            }
            return false;
        }

        void display(bool full = false) {
            for(int i = 0; i < S; i++) {
                if(full)
                    std::cout << entries[i] << std::endl;
                else {
                    if(entries[i].taken)
                        std::cout << entries[i] << std::endl;
                }

            }
        }
};