---
layout: post
title: Akuna全部面经(bar很高)
description: 笔试题, 二面, 最终面, 感觉bar很高
categories:
- 技术
tags:
- C++
---

首先做了笔试题， 我觉得笔试题非常好, 才对公司有兴趣的.

# 二面
全程英文，问了很多问题
1. 算法，判断一个数是否power of two的方法， quicksort过程，平均，最差时间复杂度，例子是怎么样
2. 调用函数的汇编代码； 如果有很多参数，register存不了怎么样；32位的汇编跟64位有什么区别？smart pointer是怎么样的，为什么可以这样
share pointer跟unique pointer有什么区别；  segment，section在程序中是怎么分布；nmap映射的是程序的什么；  IPC的方法， 共享内存的缺点，什么方法是reliable的； TCP，UDP的区别，优缺点； TCP肯定不会有data loss吗？ 为什么TCP稳定；  gdp怎么调试多线程，怎么看程序栈；
多线程怎么保证线程安全，知道spin lock是什么吗？怎么实现；condition_variable有哪些API；dead lock是什么，有哪些方法去解决。
 Linux怎么创建儿子进程； Linux调用system call的过程；为什么进入kernel space; 调用system call优缺点；
tcp中send的block跟unblock方法有什么区别
虚函数是什么，有什么用，为什么需要虚函数destruction； C++11中怎么表示原子变量；汇编中有一个方法用来保证原子性交换变量，是怎么样的？
signal是怎么样的，有什么用；

# 最终面

> template<int size> pow() 实现这个功能


2.
vector<stirng> my_string= {"hello", " ", "world"};
auto &a = my_string[0];
输出a的内容会是什么

3.
read(fd, xx)直接读取文件内容与nmap fd后memcpy的区别是什么.
