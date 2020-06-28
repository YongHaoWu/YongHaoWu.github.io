---
layout: post
title: 设计分布式系统—简明粗暴的名字发现服务
description: 在设计实现分布式系统时，必定离不开名字发现服务： 一个新节点加进来系统里了，怎么样被其他节点感知到，并且能与此节点通信呢？ 在此， 我向大家简明扼要的介绍一下 erlang 这个设计了十多年稳定性达到 99.99999999% 的电话系统的语言是怎么样做的。
categories:
- 技术
tags:
- go
---

在设计实现分布式系统时，必定离不开名字发现服务： 一个新节点加进来系统里了，怎么样被其他节点感知到，并且能与此节点通信呢？

在此， 我向大家简明扼要的介绍一下 erlang 这个设计了十多年稳定性达到99.99999999%的电话系统的语言是怎么样做的。

erlang 的这个名字发现服务叫`epmd(Erlang Port Mapper Daemon)`，中文是`Erlang 端口映射守护进程`，默认是开启在4369端口。

一个 node 上（可以暂时理解为一台物理机上），所有其他 erlang 的程序启动启动时，必须指定自己的名称（例如:`my_name@ubuntu，`，这个是 erlang 节点名称，@的前面是名字，后面是本机 hostname），并把ip到4369端口上（当然这些erlang 都帮你处理好了）。值得注意的是，每个程序启动时，都会试图去创建 empd进程，失败就算了。（这很粗暴， 但可以保证empd必定会启动

注册完成后，empd 会广播此节点的信息到各个节点上，让各个节点保存起来。这样子就算 empd 挂掉了，其他节点依然有着其他节点的信息，能够通信。

而empd 服务正常时，节点则会向 empd 查询其他节点的信息。

empd挂掉了，由于节点存有其他全部节点的信息，所以旧节点依然能够通信。empd 重新启动了，新节点依然通过 empd 注册信息，但因为旧节点不会重连 empd（不清楚 erlang 为何这样设计，照理重连应该挺方便的），所以新节点无法与旧的节点通信了。要想恢复，除了重启，唯一的办法就是通过`erl_epmd:register_node`重新注册该节点。

![](https://diycode.b0.upaiyun.com/photo/2018/6cd4a3822968dc6be2fcb927fddf00ec.png)

分布式服务，自然是把服务器都放在同一个内网中，相互通信。不暴露在外面，不做成内网简直是愚蠢。

而当本地节点尝试通过 empd与远程节点联系时，empd 会发请求其他内网机器的 empd 服务，这两个 empd 服务就作为桥梁，把本地节点与远程节点联系起来。

你也许会有一个疑问， 本地节点怎么样得知远程节点的内网 ip？



还记得`my_name@ubuntu，`这个 节点名称吗？

@的前面是名字，后面是本机 hostname。



与其他节点通信时，便是靠@后面的这个 hostname 来通信，这意味着，你需要在 `/etc/hosts`里配置好所有 hostname 对应的内网 ip。自然这个可以通过很多办法便捷的完成。



至此，empd 的名字发现服务便介绍完成。你也可以依据此来自己实现一个简单的服务。
