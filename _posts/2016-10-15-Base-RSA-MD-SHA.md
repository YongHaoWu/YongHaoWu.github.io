---
layout: post
title: 加密算法的科普
description: Base32, RSA, MD5, SHA以及SSL等科普
categories:
- 技术
tags:
- go
---

###Base32,Base64

Base32是一种将任意文件编码为只有基础32个字符的数据编码方式, 64则是64个.
主要目的是为了避免出现不符合规则的字符, 方便把含有不可见字符串的信息用可见字符串表示出来.
比如http协议当中的key value字段，必须进行URLEncode 不然出现的等号可能使解析失败 空格也会使http请求解析出现问题，比如 请求行就是以空格来划分的 POST /hi/you HTTP/1.1  推荐一篇[文章](http://blog.xiayf.cn/2016/01/24/base64-encoding/) 
Base32有不合法字符/

网上有误解Base编码方式为加密方式, 实际上标准Base64编码解码无需额外信息即完全可逆.

---

###RSA

RSA是非对称加密算法, 对称算法就是双方用同一个密钥加密.
RSA是基于对两个质数相乘容易，而将其合数分解很难的这个特点进行的加密算法
生成公钥与私钥, 公钥加密而私钥解密, 或者相反都可以.
一般公钥公开到网上, 想发送信息给你的人用公钥加密, 而只有你拥有私钥可以解密, 这样确保了信息的保密.
或者你用私钥加密, 其他所有人都可以用公钥解密你的信息, 这样可以确保信息是由你所发出. 网上发邮件或者个人网站上所用到的签名,就是使用此技术.

###数字证书
数字证书跟普通用私钥加密，别人用你的公钥解密信息相比，只是多了数据完整性(Data Integrity)保护.
数字证书会有一个中间服务器CA（Certificate Agent)存放通讯双方A,B的公钥, 通过用自己的私钥加密B的公钥hahs以及附带B的公钥一起发送给A, A用CA的公钥解密信息, 并且对得到的B的公钥做hash与得到的hash来判断对方的公钥是否在传输途中被修改, 随后再获取B加密的信息,用公钥解密成功后即可认证B.

###Public key infrastructure
以上的中间人就是PKI中的信任锚, PKI还需要解决证书吊销,互操作等等其他的功能, 加密和签名已经是很成熟的设计了

##攻击手段

重放攻击（Replay attack） 和 中间人攻击（Man-in-the-middle attack)
简单来说就是有人从连接一开始就监听着,并且在双方传输密码或公钥途中拦截,改成自己的密码/公钥,伪装成通讯一方通讯.

---

###MD5, SHA

MD5只是哈希算法，算不得严格意义上的加密算法, MD5是生成128bit再每每用4bit转换为16进制表示的字符,所以会生成128/4=32位的字符, 字符集是0-f, 通常可以作文件名保存.
哈希算法简单来说就是生成一个指纹,但是此指纹信息难以反推原来的信息.

---


###HTTP/HTTPS, SSL

HTTPS = HTTP + SSL

其实也是用了非对称加密, 客户端先向服务器端索要公钥，然后用公钥加密信息，服务器收到密文后，用自己的私钥解密。