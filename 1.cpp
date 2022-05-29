#include <iostream>
#include <vector>
#include <cassert>

struct StringHasher {
    unsigned int str_hash1(const std::string &data) const {
        unsigned int hash = 0;
        for (auto i: data) {
            hash = hash * 13 + i;
        }
        return hash;
    }

    unsigned int str_hash2(const std::string &data) const {
        unsigned int hash = 0;
        for (auto i: data) {
            hash = hash * 7 + i;
        }
        hash = hash * 2 + 1;
        return hash;
    }

    unsigned int operator()(const std::string &data, int i) const {
        unsigned int hash = str_hash1(data) + (i * str_hash2(data));
        return hash;
    }
};

template<class Kay>
struct DefaultEqual {
    bool operator()(const Kay &l, const Kay &r) const {
        return l == r;
    }
};


template<class Key, class Hash = StringHasher, class Equal = DefaultEqual<Key>>
class HashSet {
public:
    HashSet(Hash hash = Hash(), Equal equal = Equal()) :
            buckets(8),
            hash(hash),
            equal(equal),
            items_count(0) {
    }

    HashSet(const HashSet &) = delete;

    HashSet &operator=(const HashSet &) = delete;

    ~HashSet() = default;


    struct Elem {
        enum data_empty_del {
            empty = 0,
            data,
            rm
        };
        Elem() :
                key(Key()),
                status(empty) {}
        Key key;
        data_empty_del status;
    };

    bool add(const Key &key) {
        bool flag = true;
        size_t pos = 0;
        unsigned int idx;
        for (int i = 0; i < buckets.size(); i++) {
            idx = hash(key, i) % buckets.size();
            if (buckets[idx].status == Elem::data_empty_del::rm) {
                if (flag) {
                    pos = idx;
                    flag = false;
                }
                continue;
            } else if (buckets[idx].status == Elem::data_empty_del::data) {
                if (equal(buckets[idx].key, key))
                    return false;
                continue;
            } else if (buckets[idx].status == Elem::data_empty_del::empty) {
                if (!flag) {
                    buckets[pos].key = key;
                    buckets[pos].status = Elem::data_empty_del::data;
                } else {
                    buckets[idx].key = key;
                    buckets[idx].status = Elem::data_empty_del::data;
                }
                items_count++;
                if (items_count >= (buckets.size() / 4 * 3))
                    grow();
                return true;
            }
        }
        buckets[pos].key = key;
        buckets[pos].status = Elem::data_empty_del::data;
        items_count++;
        if (items_count >= (buckets.size() / 4 * 3))
            grow();
        return true;
    }

    bool has(const Key &key) const {
        unsigned int idx;
        for (int i = 0; i < buckets.size(); i++) {
            idx = hash(key, i) % buckets.size();
            if (buckets[idx].status == Elem::data_empty_del::rm)
                continue;
            else if (buckets[idx].status == Elem::data_empty_del::data) {
                if (equal(buckets[idx].key, key))
                    return true;
                else
                    continue;
            } else if (buckets[idx].status == Elem::data_empty_del::empty)
                return false;
        }
        return false;
    }

    bool del(const Key &key) {
        unsigned int idx;
        for (int i = 0; i < buckets.size(); i++) {
            idx = hash(key, i) % buckets.size();
            if (buckets[idx].status == Elem::data_empty_del::rm)
                continue;
            else if (buckets[idx].status == Elem::data_empty_del::data) {
                if (equal(buckets[idx].key, key)) {
                    items_count--;
                    buckets[idx].status = Elem::data_empty_del::rm;
                    return true;
                } else
                    continue;
            }
            else if (buckets[idx].status == Elem::data_empty_del::empty)
                return false;
        }
        return false;
    }

private:
    void grow() {
        std::vector<Elem> new_buckets(buckets.size() * 2);
        std::vector<Elem> temp(buckets);
        this->buckets = std::move(new_buckets);
        this->items_count = 0;
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i].status == Elem::data_empty_del::data)
                add(temp[i].key);
        }
    }

    std::vector<Elem> buckets;
    Hash hash;
    Equal equal;
    size_t items_count;
};


int main() {
    HashSet<std::string> table;
    char operation = 0;
    std::string data;
    while (std::cin >> operation >> data) {
        switch (operation) {
            case '+':
                std::cout << (table.add(data) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.del(data) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                std::cout << (table.has(data) ? "OK" : "FAIL") << std::endl;
                break;
            default:
                assert(false);
        }
    }
    return 0;
}