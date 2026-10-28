#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Account {
private:
    std::string id_;
    double balance_;
    mutable std::mutex mutex_;
    friend class TransactionManager;
public:
    Account(std::string id, double balance) : id_(std::move(id)), balance_(balance) {}
    double getBalance() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return balance_;
    }
    const std::string& getId() const { return id_; }
};

class Transaction {
public:
    enum class Type { Deposit, Withdraw };
private:
    Type type_;
    std::string accountId_;
    double amount_;
public:
    Transaction(Type type, std::string accountId, double amount)
        : type_(type), accountId_(std::move(accountId)), amount_(amount) {}
    void print() const {
        std::cout << (type_ == Type::Deposit ? "Deposito" : "Retiro")
                  << " de " << amount_ << " en cuenta " << accountId_ << '\n';
    }
};

class TransactionManager {
private:
    std::mutex managerMutex_;
    TransactionManager() = default;
    TransactionManager(const TransactionManager&) = delete;
    TransactionManager& operator=(const TransactionManager&) = delete;
public:
    static TransactionManager& getInstance() {
        static TransactionManager instance; // Inicialización thread-safe desde C++11
        return instance;
    }
    bool deposit(Account* account, double amount) {
        if (!account || amount <= 0) return false;
        std::lock_guard<std::mutex> managerLock(managerMutex_);
        {
            std::lock_guard<std::mutex> accountLock(account->mutex_);
            account->balance_ += amount;
        }
        Transaction(Transaction::Type::Deposit, account->getId(), amount).print();
        return true;
    }
    bool withdraw(Account* account, double amount) {
        if (!account || amount <= 0) return false;
        std::lock_guard<std::mutex> managerLock(managerMutex_);
        {
            std::lock_guard<std::mutex> accountLock(account->mutex_);
            if (account->balance_ < amount) return false;
            account->balance_ -= amount;
        }
        Transaction(Transaction::Type::Withdraw, account->getId(), amount).print();
        return true;
    }
};

int main() {
    auto& manager = TransactionManager::getInstance();
    Account account("A1", 1000);
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&]() {
            manager.deposit(&account, 100);
            manager.withdraw(&account, 50);
        });
    }
    for (auto& t : threads) t.join();
    std::cout << "Balance final: "
              << account.getBalance()
              << std::endl;
    std::cout << "Direccion manager: "
              << &TransactionManager::getInstance()
              << std::endl;
}
