#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <map>
#include <memory>
#include <vector>
#include <functional>
#include <algorithm>

template<typename T>
class DataRepository {
private:
    std::map<int, std::shared_ptr<T>> items;
    int nextId = 1;

public:
    int add(std::shared_ptr<T> item) { items[nextId] = item; return nextId++; }

    void addWithId(int id, std::shared_ptr<T> item) {
        items[id] = item;
        if (id >= nextId) nextId = id + 1;
    }

    bool remove(int id) { return items.erase(id) > 0; }

    std::shared_ptr<T> get(int id) const {
        auto it = items.find(id);
        return it != items.end() ? it->second : nullptr;
    }

    std::vector<std::shared_ptr<T>> getAll() const {
        std::vector<std::shared_ptr<T>> result;
        for (const auto& [_, item] : items) result.push_back(item);
        return result;
    }

    std::vector<std::shared_ptr<T>> filter(std::function<bool(const std::shared_ptr<T>&)> pred) const {
        std::vector<std::shared_ptr<T>> result;
        for (const auto& [_, item] : items) if (pred(item)) result.push_back(item);
        return result;
    }

    int count() const { return items.size(); }
    bool contains(int id) const { return items.contains(id); }
    void clear() { items.clear(); nextId = 1; }
    int getNextId() const { return nextId; }
};

#endif
