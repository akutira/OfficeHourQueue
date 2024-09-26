// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here


TEST(test_push_pop) {
    List<int> my_list;
    my_list.push_back(4);
    my_list.push_back(25);
    my_list.push_back(23);
    my_list.push_back(567);
    my_list.push_back(45);
    //cout << "begin" << endl;
    ASSERT_EQUAL(my_list.front(), 4);
    ASSERT_EQUAL(my_list.back(), 45);
    //cout << "end" << endl;
    my_list.pop_back();
    my_list.pop_back();
    my_list.pop_back();
    ASSERT_EQUAL(my_list.back(), 25);
    my_list.pop_front();
    ASSERT_EQUAL(my_list.front(), 25);

    ASSERT_EQUAL(my_list.front(), my_list.back());
    ASSERT_FALSE(my_list.empty());
    my_list.pop_front();
    ASSERT_TRUE(my_list.empty());

    my_list.push_front(62);
    my_list.push_front(24);
    my_list.push_back(19);

    ASSERT_EQUAL(my_list.front(), 24);
    ASSERT_EQUAL(my_list.back(), 19);
}

TEST(test_copy) {
    List<char> my_list;
    my_list.push_back('i');
    my_list.push_back('v');
    my_list.push_back('e');
    my_list.push_front('d');
    my_list.push_back('d');
    //dived

    List<char> list(my_list);
    ASSERT_EQUAL(list.front(),'d');
    ASSERT_EQUAL(list.back(),'d');
    list.pop_back();
    list.pop_front();
    //ive
    ASSERT_EQUAL(list.front(),'i');
    ASSERT_EQUAL(list.back(),'e');
    ASSERT_EQUAL(my_list.front(),'d');
    ASSERT_EQUAL(my_list.back(),'d');
    list = my_list;
    //dived
    ASSERT_EQUAL(list.size(), 5);
    ASSERT_EQUAL(list.front(), my_list.front());
    ASSERT_EQUAL(list.back(), my_list.back());
}

TEST(test_empty) {
    List<string> my_list;
    my_list.push_back("a");
    my_list.push_back("test");
    my_list.push_front("is");
    my_list.push_front("this");
    //this is a test

    List<string> list = my_list;
    List<string> newList;
    ASSERT_FALSE(list.empty());
    ASSERT_TRUE(newList.empty());

    list.pop_back();
    list.pop_back();
    list.pop_back();
    list.pop_back();
    ASSERT_TRUE(list.empty());
    list.push_front("favorite");
    list.push_front("my");
    list.push_front("is");
    list.push_front("smash");
    //smash is my favorite
    newList = list;
    list.clear();

    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(newList.front(), "smash");
    ASSERT_EQUAL(newList.back(), "favorite");
    ASSERT_EQUAL(my_list.front(), "this");
    ASSERT_EQUAL(my_list.back(), "test");
    list.push_front("new");
    list.pop_back();
        //cout << "hit" << endl;
    ASSERT_TRUE(list.empty());
    list.push_back("start");
    list.pop_front();
    ASSERT_TRUE(list.empty());
}

TEST(test_iterator) {
    List<int> my_list;
    my_list.push_back(342);
    my_list.push_back(76);
    my_list.push_back(78);
    my_list.push_back(7132);
    my_list.push_back(5);

    //342 76 78 7132 5

    List<int> list;
    for (List<int>::Iterator ls = my_list.begin(); ls != my_list.end(); ++ls){
        list.push_back(*ls);
    }
    ASSERT_EQUAL(list.front(), 342);
    ASSERT_EQUAL(list.back(), 5);
    ASSERT_EQUAL(list.size(), 5);

    List<int>::Iterator ls = my_list.begin();
    ASSERT_EQUAL(*ls, my_list.front());
    ++ls;

    List<int>::Iterator ls2 = my_list.begin();
    ASSERT_TRUE(ls != ls2);
    ++ls2;

    ASSERT_TRUE(ls == ls2);
    List<int>::Iterator ls3 = ls2;
    ++ls3;

    ASSERT_TRUE(ls3 != ls2);
    ++ls2;

    ASSERT_TRUE(ls3 == ls2);
}

TEST(test_erase) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);

    //1 2 3 4
    List<int>::Iterator ls = my_list.begin();
    ++ls;
    ++ls;
    ++ls;
    my_list.erase(ls);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 3);
    ASSERT_EQUAL(my_list.size(), 3);
    ls = my_list.begin();
    ASSERT_EQUAL(*ls, 1);
    ++ls;
    ASSERT_EQUAL(*ls, 2);
    ++ls;
    ASSERT_EQUAL(*ls, 3);
}

TEST(test_erase_2) {
    List<char> my_list;
    my_list.push_back('a');
    my_list.push_back('b');
    my_list.push_back('c');
    my_list.push_back('d');

    //a b c d
    my_list.erase(my_list.begin());
    List<char>::Iterator ls = my_list.begin();
    ASSERT_EQUAL('b', my_list.front());
    ++ls;
    ++ls;
    my_list.erase(ls);
    ASSERT_EQUAL('c',my_list.back());
    ASSERT_EQUAL(my_list.size(), 2);
    my_list.push_back('d');
    my_list.erase(my_list.begin());
    my_list.erase(my_list.begin());
    my_list.erase(my_list.begin());
    ASSERT_TRUE(my_list.empty());
}

TEST(test_insert) {
    List<char> my_list;
    List<char>::Iterator ls = my_list.begin();
    my_list.insert(ls, 'a');
    ASSERT_EQUAL(my_list.front(), 'a');
    ASSERT_EQUAL(my_list.back(), 'a');
    ls = my_list.end();
    my_list.insert(ls, 'c');
    ASSERT_EQUAL(my_list.front(), 'a');
    ASSERT_EQUAL(my_list.back(), 'c');
    ls = my_list.begin();
    ++ls;
    my_list.insert(ls, 'b');
    --ls;
    ASSERT_EQUAL(*ls, 'b');
    //a b c d
    my_list.insert(my_list.end(), 'd');
    ASSERT_EQUAL(my_list.back(),'d');
    my_list.insert(my_list.begin(), 'z');
    ASSERT_EQUAL(my_list.front(), 'z');

}

TEST(test_insert2) {
    List<char> my_list;
    List<char>::Iterator ls = my_list.begin();
    my_list.insert(ls, 'a');
    ASSERT_EQUAL(my_list.front(), 'a');
    ASSERT_EQUAL(my_list.back(), 'a');
    ls = my_list.end();
    my_list.insert(ls, 'b');
    ASSERT_EQUAL(my_list.front(), 'a');
    ASSERT_EQUAL(my_list.back(), 'b');
    ls = my_list.begin();
    ++ls;
    ++ls;
    my_list.insert(ls, 'c');
    ASSERT_EQUAL(my_list.back(), 'c');
    //a b c
    my_list.insert(my_list.end(), 'd');
    ASSERT_EQUAL(my_list.back(),'d');
    my_list.insert(my_list.begin(), 'z');
    ASSERT_EQUAL(my_list.front(), 'z');

}

TEST_MAIN()

