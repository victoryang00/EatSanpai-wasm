#include "Customer.h"
#include <iostream>

template <typename T> void CustomSet<T>::printGeChatUser() {
  cout << "{";
  for (auto &&item : *set_) {
    cout << ((GechatUser)item).user_name;
    cout<<" ( friends: "<<((GechatUser)item).friends.size()<<" )" ;
    if (item != set_->back()) {
      cout << ", ";
    }
  }
  cout << "}";
}
int main() {
  cout << "Test1" << endl;
  int a[5] = {4, 6, 32, -4, 0};
  CustomSet<int> sample1(a, 5);
  int b[5] = {4, 2, 10, -2, 0};
  CustomSet<int> sample2(b, 5);
  auto sb = sample1;
  auto sd = CustomSet<int>();
  int c[3] = {3, 4, 5};
  CustomSet<int> sample3(c, 3);
  auto cartesian = sample1 * sample3;
  cartesian.printPairSet(); // prints "{-4, 6, 32}\n"
  cout << "Test2" << endl;
  int another[6] = {1, 2, 3, 4, 5, 6};
  CustomSet<int> foo(another, 6);
  LotteryStation sample;
  sample.setPrizeNumbers(foo, LOTTO6); // LOTTO6 is predefined
  sample.newRound();
  LotteryTicket *jackpot = sample.buy(foo, LOTTO6);
  // prints "Bought another Lotto 6 ticket for 2 Yuan at round 1.\n"
  sample.claimPrize(jackpot);
  // prints "This ticket wins 2000000 Yuan.\n"
  cout << "Test3" << endl;
  shared_ptr<GechatUser> gzw(new GechatUser("GeziWang"));
  shared_ptr<GechatUser> gf(new GechatUser("Girlfriend"));
  gzw->addFriend(gf);
  gf->addFriend(gzw);
  gf->doubleDelete(gzw);
  CustomSet<GechatUser> sad_story;
  sad_story.add(*gzw);
  sad_story.add(*gf);
  sad_story.printGeChatUser();
  // prints "{GeziWang (friends: 0), Girlfriend (friends: 0)}\n"
  return 0;
}