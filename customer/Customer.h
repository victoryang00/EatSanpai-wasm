// All #include lines that may be used in homework 6.
#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <string>
#include <time.h>
#include <type_traits>
#include <utility>
#include <vector>

// Predefined constants for problem 2.
#define LOTTO6 6
#define LOTTO7 7

using namespace std;
int randInt(int min, int max) {
  if (max < min)
    swap(max, min);
  return rand() % (max - min + 1) + min;
};

/*****************************************************************\
|                            Problem 1                            |
\*****************************************************************/
template <typename T> class CustomSet {
public:
  // Constructors and destructor:
  CustomSet() { set_ = new vector<T>(); };
  // Default constructor

  CustomSet(const CustomSet &other) { set_ = other.set_; };
  // Copy constructor. Should construct a copy of "other".

  CustomSet(T arr[], int size) {
    set_ = new vector<T>();
    for (int i = 0; i < size; i++) {
      set_->push_back(arr[i]);
    }
    assert(set_->size() == size);
  };
  // Constructor using an array.
  // Note that if there are duplicates in the array, you should ignore them.
  // And then the size of your "CustomSet" will be different from the "size"
  // given!

  ~CustomSet() = default;
  ;
  // Destructor. Pay attention to memory leaks!

  // Other member functions:
  int size() const { return set_->size(); };
  // Returns the size of the set.

  bool add(const T &item) { this->set_->push_back(item); };
  // If "item" is already in the set, return false.
  // Otherwise, add it to the set and return true.

  T *find(const T &item) {
    for (auto &&set : *set_) {
      if (set == item) {
        return &set;
      }
    }
    return nullptr;
  };

  // If an object in the set equals "item", return a pointer to it.
  // If "item" is not found, return nullptr(NULL).
  bool erase(const T &item) {
    for (auto it = set_->begin(); it != set_->end(); it++) {
      if (*it == item) {
        set_->erase(it);
        return true;
      }
    }
    return false;
  };
  // If "item" is not in the set, return false.
  // Otherwise, erase it from the set and return true.

  CustomSet intersection(const CustomSet &other) {
    for (auto &&item : *other.set_) {
      if (this->find(item) == nullptr) {
        this->add(item);
      }
    }
    return *this;
  };
  // This function returns the intersection of two sets (*this and other).
  // In other words, the set of all objects that is in both *this and other.
  // If there is no intersection, just return an empty set.

  void sortSet() { std::sort(set_->begin(), set_->end()); };
  // This function sorts the objects in the set in ascending order.
  // Directly using (std::)sort is enough, if you are using an STL container.

  void printSet() {
    cout << "{";
    for (auto &&item : *set_) {

      cout << item;
      if (item != set_->back()) {
        cout << ", ";
      }
    }
    cout << "};" << endl;
  };

  void printPairSet() {
    cout << "{";
    for (auto &&item : *set_) {
      cout << "[" << std::get<0>(item) << ", " << std::get<1>(item) << "]";
      if (item != set_->back()) {
        cout << ", ";
      }
    }
    cout << "};" << endl;
  };

  void printGeChatUser();
  // This function prints the set, seperating elements by { , , , }.
  // It's safe to assume that it supports operator<< of ostream (cout).
  // For example, Assume you've added 2, 4, -2, and 800 to the set, in this
  // order. This function will print: "{2, 4, -2, 800}\n" Note that there are
  // spaces between a comma(,) and the next object. Print a newline at the end.
  // (indicated by the '\n' above)

  // Operators:
  CustomSet operator+(const T &item) {
    this->add(item);
    return *this;
  };

  CustomSet operator+(const CustomSet &that) {
    this->intersection(that);
    return *this;
  };

  CustomSet &operator+=(const T &item) {
    this->add(item);
    return *this;
  };

  CustomSet &operator+=(const CustomSet &that) {
    this->intersection(that);
    return *this;
  };
  // The operator+ and operator += are overloaded.
  // They can be understood intuitively, or consider this:
  // A set "plus" an item means adding in the item.
  // A set "plus" a set means taking the union of two sets.
  // However, the difference between + and += is not written here.
  // Try to figure out on your own!

  CustomSet operator-(const T &item) {
    this->erase(item);
    return *this;
  };

  CustomSet operator-(const CustomSet &that) {
    for (auto &&item : *that.set_) {
      if (this->find(item) != nullptr) {
        this->erase(item);
      }
    }
    return *this;
  };

  CustomSet &operator-=(const T &item) {
    this->erase(item);
    return *this;
  };

  CustomSet &operator-=(const CustomSet &that) {
    for (auto &&item : *that.set_) {
      if (this->find(item) != nullptr) {
        this->erase(item);
      }
    }
    return *this;
  };
  // The operator- and operator -= are overloaded.
  // They can be understood intuitively, or consider this:
  // A set "minus" an item means erasing the item.
  // A set A "minus" a set B means subtracting B from A, or namely, A\B.
  // However, the difference between - and -= is not written here.
  // Try to figure out on your own!

  CustomSet<std::pair<T, T>> operator*(const CustomSet &that) {
    std::pair<T, T> *pair_set = (std::pair<T, T> *)malloc(
        sizeof(std::pair<T, T>) * this->size() * that.size());
    int i = 0;
    for (auto &&item : *this->set_) {
      for (auto &&item2 : *that.set_) {
        pair_set[i] = std::make_pair(item, item2);
        i++;
      }
    }
    return CustomSet<std::pair<T, T>>(pair_set, i);
  };
  // This function returns the Cartesian product of two sets (*this and that).
  // The Cartesian product of two sets is the set of all ordered pairs that
  // satisfy:
  //		The first element of the ordered pair belongs to first set
  //(*this); 		The second element of the ordered pair belongs the
  // second set (that).
  // The (std::)pair (in header <utility>) helps representing the object in it.
  // If you have any question with Cartesian products or std::pair, just look up
  // on Internet!

  std::vector<T> *set_;
};

/*****************************************************************\
|                            Problem 2                            |
\*****************************************************************/
class LotteryTicket {
public:
  LotteryTicket() : m_round(1), m_cost(0), m_numbers(){};

  LotteryTicket(const CustomSet<int> &numbers, int round)
      : m_round(round), m_cost(0), m_numbers(numbers){};

  virtual ~LotteryTicket() = default;
  ;

  int getRound() const { return m_round; };

  int getCost() const { return m_cost; };

  virtual int getTicketType() = 0;

  void setCost(const int &cost) { m_cost = cost; };

  virtual int claimPrize(const CustomSet<int> &prizeNumbers, int round) = 0;

private:
  int m_round; // The valid round of a ticket. An outdated ticket is invalid.
  int m_cost;  // The amount of money spent on this ticket.
protected:
  CustomSet<int> m_numbers;
};

class Lotto6Ticket : public LotteryTicket {
public:
  Lotto6Ticket(const CustomSet<int> &numbers, int round)
      : LotteryTicket(numbers, round) {}

  int getTicketType() override { return LOTTO6; };

  int claimPrize(const CustomSet<int> &prizeNumbers, int round) override {
    int count = 0;
    for (auto &&item : *prizeNumbers.set_) {
      if (m_numbers.find(item) == nullptr) {
        count++;
      }
    }
    switch (count) {
    case 7:
      return 2000000;
    case 6:
      return 4500;
    case 5:
      return 75;
    case 4:
      return 5;
    }
    return 0;
  };
};

class Lotto7Ticket : public LotteryTicket {
public:
  Lotto7Ticket(const CustomSet<int> &numbers, int round)
      : LotteryTicket(numbers, round) {}

  int getTicketType() override { return LOTTO7; };

  int claimPrize(const CustomSet<int> &prizeNumbers, int round) override {
    int count = 0;
    for (auto &&item : *prizeNumbers.set_) {
      if (m_numbers.find(item) == nullptr) {
        count++;
      }
    }
    switch (count) {
    case 6:
      return 2000000;
    case 5:
      return 4500;
    case 4:
      return 75;
    case 3:
      return 5;
    }
    return 0;
  };
};

class LotteryStation {
public:
  LotteryStation() { m_round = 0; };

  ~LotteryStation(){};

  LotteryTicket *buy(CustomSet<int> numbers, int tickettype) {
    cout << "Bought a " << tickettype << " ticket for "
         << " Yuan at round " << m_round << "." << endl;
    m_round++;
    if (tickettype == LOTTO6)
      return new Lotto6Ticket(numbers, m_round);
    else
      return new Lotto7Ticket(numbers, m_round);
  };
  // Represents buying a ticket of "tickettype" with "numbers" at round
  // "m_round". "tickettype" is either LOTTO6 or LOTTO7 (predefined). If
  // succeeds, output a message: "Bought a (??) ticket for (??) Yuan at round
  // (??).\n", then return a pointer to it. See examples for more details. If
  // the numbers are not enough, or some numbers are out of bound for the
  // ticket,
  //   output "Failed.\n" and return nullptr(NULL).

  void claimPrize(LotteryTicket *ticket) {
    auto ticket_price = 0;
    for (auto &&lot : lottery_numbers) {
      ticket_price += ticket->claimPrize(lot, m_round);
    }
    cout << "This ticket wins " << ticket_price << " Yuan.\n";
  };
  // Claims prize for a given ticket.
  // You should use the claimPrize() function of the ticket.
  // However, you should check the type of the ticket first,
  //   as you need to pass the right prize numbers as parameter.
  // Output a message in the end:
  // "This ticket wins (??) Yuan.\n"
  // You should not claim a ticket that's already claimed or with wrong rounds.
  // In either case above, simply print: "This ticket wins 0 Yuan.\n"

  void newRound() {
    m_round++;
    for (int i = 0; i < this->tickets->getTicketType(); i++) {
      auto price_num = new CustomSet<int>();
      for (int i = 0; i < this->tickets->getTicketType(); i++) {
        price_num->add(randInt(1, 50));
      }
      lottery_numbers.push_back(*price_num);
    }
  };
  // Begins a new round, generating new prize numbers for Lotto7 and Lotto6.
  // You may use the randInt() function given.

  bool setPrizeNumbers(const CustomSet<int> &numbers, int tickettype) {
    if (tickettype == LOTTO6) {
      tickets = new Lotto6Ticket(numbers, m_round);
    } else {
      tickets = new Lotto7Ticket(numbers, m_round);
    }
  };
  // This function simply serves for the purpose of:
  // Making it easier for you to debug, and also easier for us to check your
  // results. It sets the prize numbers of the type given as the "numbers".
  // "tickettype" is either LOTTO6 or LOTTO7 (predefined).
  // If "numbers" are invalid (not enough/out of bounds), do nothing and return
  // false. If succeeded, return true.

private:
  int m_round; // Should be initialized to 0.
  LotteryTicket *tickets = nullptr;
  vector<CustomSet<int>> lottery_numbers;
};

/*****************************************************************\
|                            Problem 3                            |
\*****************************************************************/
class GechatUser {
public:
  // Assume using namespace std;
  GechatUser(){};

  GechatUser(string username) : user_name(username){};

  GechatUser(const GechatUser &other) : user_name(other.user_name){};

  ~GechatUser() = default;

  int numFriends() { return friends.size(); };

  void setUsername(string username) { this->user_name = std::move(username); };

  bool haveFriend(shared_ptr<GechatUser> user) {
    for (auto &&item : *friends.set_) {
      if (item.user_name == user->user_name) {
        return true;
      }
    }
    return false;
  }; // return true if user is a friend to *this.

  bool addFriend(shared_ptr<GechatUser> user) {
    if (user == nullptr) {
      return false;
    }
    if (user->user_name == this->user_name) {
      return false;
    }
    if (haveFriend(user)) {
      return false;
    }
    user->friends.add(*this);
    friends.add(*user);
    return true;
  }; // return false only if user is
  // invalid or already a friend.
  bool singleDelete(shared_ptr<GechatUser> user) {
    if (user == nullptr) {
      return false;
    }
    if (user->user_name == this->user_name) {
      return false;
    }
    if (!haveFriend(user)) {
      return false;
    }
    friends.erase(*user);
    return true;
  }; // return false only if user
  // is invalid or not a friend.
  bool singleDelete(string username) {
    auto ge = GechatUser(std::move(username));
    auto use = make_shared<GechatUser>(ge);
    if (username == this->user_name) {
      return false;
    }
    if (!haveFriend(use)) {
      return false;
    }
    friends.erase(*use);
    return true;
  }; // return false only if username not found in friends.
  bool doubleDelete(shared_ptr<GechatUser> user) {
    if (user == nullptr) {
      return false;
    }
    if (user->user_name == this->user_name) {
      return false;
    }
    if (!haveFriend(user)) {
      return false;
    }
    friends.erase(*user);
    user->friends.erase(*this);
    return true;
  }; // return false only if user
  // is invalid or not a friend.
  bool doubleDelete(string username) {
    auto ge = GechatUser(std::move(username));
    auto use = make_shared<GechatUser>(ge);
    if (username == this->user_name) {
      return false;
    }
    if (!haveFriend(use)) {
      return false;
    }
    friends.erase(*use);
    use->friends.erase(*this);
    return true;
  }; // return false only if username not found in friends.
  bool operator==(const GechatUser &other) {
    if (this->user_name == other.user_name) {
      return true;
    }
    return false;
  };
  bool operator!=(const GechatUser &other) {
    if (this->user_name != other.user_name) {
      return true;
    }
    return false;
  };
  // Not complete...
public:
  string user_name;
  CustomSet<GechatUser> friends;
};

