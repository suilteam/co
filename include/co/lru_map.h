#pragma once

#include <list>
#include <unordered_map>

template <typename K, typename V>
class LruMap {
  public:
    typedef typename std::unordered_map<K, V>::iterator iterator;

    explicit LruMap(size_t capacity = 1024) {
        _capacity = capacity > 0 ? capacity : 1024;
    }

    ~LruMap() {}

    bool empty() const {
        return _kv.size() == 0;
    }

    size_t size() const {
        return _kv.size();
    }

    iterator begin() {
        return _kv.begin();
    }

    iterator end() {
        return _kv.end();
    }

    iterator find(const K& key) {
        iterator it = _kv.find(key);
        if (it != _kv.end() && _kl.front() != key) {
            auto ki = _ki.find(key);
            _kl.splice(_kl.begin(), _kl, ki->second); // move key to the front
            ki->second = _kl.begin();
        }
        return it;
    }

    // The key is not inserted if it already exists.
    void insert(K&& key, V&& value) {
        auto r = _kv.emplace(std::forward<K>(key), std::forward<V>(value));
        if (!r.second) return;

        _kl.push_front(key);
        _ki[key] = _kl.begin();

        if (_kv.size() > _capacity) {
            K k = _kl.back();
            _kl.pop_back();
            _kv.erase(k);
            _ki.erase(k);
        }
    }

    void erase(iterator it) {
        if (it != _kv.end()) {
            auto ki = _ki.find(it->first);
            _kl.erase(ki->second);
            _ki.erase(ki);
            _kv.erase(it);
        }
    }

    void erase(const K& key) {
        this->erase(_kv.find(key));
    }

    void clear() {
        _kv.clear();
        _ki.clear();
        _kl.clear();
    }

    void swap(LruMap& x) {
        _kv.swap(x._kv);
        _ki.swap(x._ki);
        _kl.swap(x._kl);
        std::swap(_capacity, x._capacity);
    }

  private:
    std::unordered_map<K, V> _kv;
    std::unordered_map<K, typename std::list<K>::iterator> _ki;
    std::list<K> _kl; // key list
    size_t _capacity; // max capacity
};
