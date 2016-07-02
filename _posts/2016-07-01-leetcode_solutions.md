---
layout: post
title: leetcode解题笔记
description: 记录思路, 难点. 以及教是最好的学
categories:
- 技术
tags:
- C++
---

##344. [Reverse String](https://leetcode.com/problems/reverse-string/)

> Write a function that takes a string as input and returns the string reversed.
> Example:
> Given s = "hello", return "olleh".

###Solution1(two pointers)

```
class Solution {
public:
    string reverseString(string s) {
        for(int i=0,j=s.length()-1; i<j; ++i,--j)
            swap(s[i], s[j]);
        return s;
    }
};
```

###Solution2(recursion)

```
class Solution {
public:
    string reverseString(string s) {
        const int len = s.length();
        if(len <= 1) return s;
        string left_str = s.substr(0, len/2);
        string right_str = s.substr(len/2, len-len/2);
        return reverseString(right_str) + reverseString(left_str) ;
    }
};
```

## 345. [Reverse Vowels of a String](https://leetcode.com/problems/reverse-vowels-of-a-string/)

> Write a function that takes a string as input and reverse only the vowels of a string.
> Example 1:
> Given s = "hello", return "holle".
> Example 2:
> Given s = "leetcode", return "leotcede".

The same as [Reverse String](https://leetcode.com/problems/reverse-string/), while we just need to switch the vowels. It is easy to come up with two pointers solution.
Besides, we can use find_first_of and find_last_of method of string. 

###Solution1(two pointers)

```
class Solution {
    public:
        string reverseVowels(string s) {
            string vowerls = "aeiouAEIOU";
            for(int i=0,j=s.length()-1; i<j; ) {
                if(vowerls.find(s[i]) == string::npos) {
                    ++i;
                }
                if(vowerls.find(s[j]) == string::npos) {
                    --j;
                }
                if(vowerls.find(s[i])!=string::npos && vowerls.find(s[j])!=string::npos) {
                    if(s[i] != s[j]) {
                        swap(s[i], s[j]);
                    }
                    ++i; --j;
                }
            }
            return s;
        }
};

class Solution {
public:
    string reverseVowels(string s) {
        auto p1 = s.begin(), p2 = s.end() - 1;
        string vowels = "aeiouAEIOU";
        while(p1 < p2) {
            while((vowels.find(*p1) == string::npos) && (p1 < p2)) p1++;
            while((vowels.find(*p2) == string::npos) && (p1 < p2)) p2--;
            if(p1 < p2) swap(*p1, *p2);
            p1++;
            p2--;
        }
        return s;
    }
};
```

```
class Solution {
public:
    string reverseVowels(string s) {
        int i=0, j=s.length()-1;
        while(i < j) {
            i = s.find_first_of("aeiouAEIOU", i);
            j = s.find_last_of("aeiouAEIOU", j);
            /* pos	-	position at which to begin searching */

            /* need plus, as it just swap vowerls' place */
            if(i < j)
                swap(s[i++], s[j--]);
        }
        return s;
    }
};
```

## 371. [Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/)

> Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.
> Example:
> Given a = 1 and b = 2, return 3.

If you have learn how machine do the add operation through bits or read the book Code, it is easy to know that using xor(^) operation can simulate add without carry. Then and(&) operation can simulate carry after shift(<<).
For example, 

    ```
101 + 101 = 1010 
101 ^ 101 = 000 //(without carry)
(101 & 101) << 1 =  1010 //carry
//After that, we add withoutarry add carry untill carry is 0

1010 ^ 000 = 1010
(1010 & 000) = 0000
    ```

    ```
class Solution {
public:
    int getSum(int a, int b) {
        int sum = a;
        while(b) {
            sum = a^b;
            b = (a&b)<<1;
            a = sum;
        }
        return sum;
    }
};
    ```
