#ifndef _STRING_OPERATION_H
#define _STRING_OPERATION_H

#include<iostream>
#include<string>
#include<algorithm>

using namespace std;



// string add
string str_add(string a, string b);
// string minus ( a>b )
string str_minus(string a, string b);
// string exp
string str_pow(string a, int exp);
// character multiply string
string char_str_multiply(char ch, string a);
// string multiply
string str_multiply(string a, string b);



// string add
string str_add(string a, string b) {
    if(a == "0")
        return b;
    if(b == "0")
        return a;
    
    string ans = "";
    bool carry = false;
    int num, index_a = a.length()-1, index_b = b.length()-1;
    for(; index_a >= 0 && index_b >= 0; index_a--, index_b--) {
        num = a[index_a]-'0'+b[index_b]-'0';
        if(carry) {
            carry = false;
            num++;
        }
        if(num >= 10) {
            carry = true;
            num -= 10;
        }
        ans.append(to_string(num));
    }
    for(; index_a >= 0; index_a--) {
        num = a[index_a]-'0';
        if(carry) {
            carry = false;
            num++;
        }
        if(num > 10) {
            carry = true;
            num -= 10;
        }
        ans.append(to_string(num));
    }
    for(; index_b >= 0; index_b--) {
        num = b[index_b]-'0';
        if(carry) {
            carry = false;
            num++;
        }
        if(num > 10) {
            carry = true;
            num -= 10;
        }
        ans.append(to_string(num));
    }
    if(carry)
        ans.append("1");

    reverse(ans.begin(), ans.end());
    return ans;
}


// string minus ( a>b )
string str_minus(string a, string b) {
    if(a == b)
        return "0";

    string ans = "";
    bool borrow = false;
    int num, index_a = a.length()-1, index_b = b.length()-1;
    for(; index_a >= 0 && index_b >= 0; index_a--, index_b--) {
        num = a[index_a]-b[index_b];
        if(borrow) {
            borrow = false;
            num--;
        }
        if(num < 0) {
            borrow = true;
            num += 10;
        }
        ans.append(to_string(num));
    }
    for(; index_a >= 0; index_a--) {
        num = a[index_a]-'0';
        if(borrow) {
            borrow = false;
            num--;
        }
        if(num < 0) {
            borrow = true;
            num += 10;
        }
        ans.append(to_string(num));
    }
    while(ans.size() > 1 && ans[ans.size()-1] == '0')
        ans.pop_back();

    reverse(ans.begin(), ans.end());
    return ans;
}


// string exp
string str_pow(string a, int exp) {
    if(a == "0")
        return "0";
    
    string ans = a;
    for(int i=0; i < exp; i++)
        ans.append("0");
    return ans;
}


// character multiply string
string char_str_multiply(char ch, string a) {
    if(ch == '0' || a == "0")
        return "0";

    string ans = "";
    int ch_num=ch-'0', carry=0;
    for(int i=a.length()-1; i >= 0; i--) {
        int number = ch_num*(a[i]-'0');
        if(carry > 0) {
            number += carry;
            carry = 0;
        }
        carry = number/10;
        ans.append(to_string(number%10));
    }
    if(carry > 0)
        ans.append(to_string(carry));
        
    reverse(ans.begin(), ans.end());
    return ans;
}


// string multiply
string str_multiply(string a, string b) {
    string ans = "";
    for(int i=a.length()-1; i >= 0; i--)
        ans = str_add(ans, str_pow(char_str_multiply(a[i], b), a.length()-1-i));
    
    return ans;
}


#endif