---
layout: post
title: Docker解析DNS错误
description: Temporary failure resolving archive ubuntu com Some index files failed to download
- 技术
tags:
- DNS
---

尽管你在宿主机能够解析到`archive.ubuntu.com`, 

```
% nslookup archive.ubuntu.com
Server:		8.8.8.8
Address:	8.8.8.8#53

Non-authoritative answer:
Name:	archive.ubuntu.com
Address: 10.18.75.45
```

在 `/etc/docker/daemon.json`里配置了 docker 的 dns 使用本机,以及`8.8.8.8`, 还是无法解析.

这时候就只能去改`/etc/hosts` 了, 把 nslookup 得到的 ip 地址直接写到里面:

```
archive.ubuntu.com 10.18.75.45
```
