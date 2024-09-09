# 7 days golang programs from scratch

重点在这个博客里面

[7天用Go从零实现分布式缓存GeeCache | 极客兔兔 (geektutu.com)](https://geektutu.com/post/geecache.html)

[![CodeSize](https://img.shields.io/github/languages/code-size/geektutu/7days-golang)](https://github.com/geektutu/7days-golang)
[![LICENSE](https://img.shields.io/badge/license-MIT-green)](https://mit-license.org/)

<details>
<summary><strong>README 中文版本</strong></summary>
<div>

## 7天用Go从零实现系列

7天能写什么呢？类似 gin 的 web 框架？类似 groupcache 的分布式缓存？或者一个简单的 Python 解释器？希望这个仓库能给你答案。

推荐先阅读 **[Go 语言简明教程](https://geektutu.com/post/quick-golang.html)**，一篇文章了解Go的基本语法、并发编程，依赖管理等内容。

推荐 **[Go 语言笔试面试题](https://geektutu.com/post/qa-golang.html)**，加深对 Go 语言的理解。

推荐 **[Go 语言高性能编程](https://geektutu.com/post/high-performance-go.html)**([项目地址](https://github.com/geektutu/high-performance-go))，写出高性能的 Go 代码。

期待关注我的「[知乎专栏](https://zhuanlan.zhihu.com/geekgo)」和「[微博](http://weibo.com/geektutu)」，查看最近的文章和动态。

### 7天用Go从零实现Web框架 - Gee

[Gee](https://geektutu.com/post/gee.html) 是一个模仿 [gin](https://github.com/gin-gonic/gin) 实现的 Web 框架，[Go Gin简明教程](https://geektutu.com/post/quick-go-gin.html)可以快速入门。

- 第一天：[前置知识(http.Handler接口)](https://geektutu.com/post/gee-day1.html) | [Code](gee-web/day1-http-base)
- 第二天：[上下文设计(Context)](https://geektutu.com/post/gee-day2.html) | [Code](gee-web/day2-context)
- 第三天：[Trie树路由(Router)](https://geektutu.com/post/gee-day3.html) | [Code](gee-web/day3-router)
- 第四天：[分组控制(Group)](https://geektutu.com/post/gee-day4.html) | [Code](gee-web/day4-group)
- 第五天：[中间件(Middleware)](https://geektutu.com/post/gee-day5.html) | [Code](gee-web/day5-middleware)
- 第六天：[HTML模板(Template)](https://geektutu.com/post/gee-day6.html) | [Code](gee-web/day6-template)
- 第七天：[错误恢复(Panic Recover)](https://geektutu.com/post/gee-day7.html) | [Code](gee-web/day7-panic-recover)

### 7天用Go从零实现分布式缓存 GeeCache

[GeeCache](https://geektutu.com/post/geecache.html) 是一个模仿 [groupcache](https://github.com/golang/groupcache) 实现的分布式缓存系统

- 第一天：[LRU 缓存淘汰策略](https://geektutu.com/post/geecache-day1.html) | [Code](gee-cache/day1-lru)
- 第二天：[单机并发缓存](https://geektutu.com/post/geecache-day2.html) | [Code](gee-cache/day2-single-node)
- 第三天：[HTTP 服务端](https://geektutu.com/post/geecache-day3.html) | [Code](gee-cache/day3-http-server)
- 第四天：[一致性哈希(Hash)](https://geektutu.com/post/geecache-day4.html) | [Code](gee-cache/day4-consistent-hash)
- 第五天：[分布式节点](https://geektutu.com/post/geecache-day5.html) | [Code](gee-cache/day5-multi-nodes)
- 第六天：[防止缓存击穿](https://geektutu.com/post/geecache-day6.html) | [Code](gee-cache/day6-single-flight)
- 第七天：[使用 Protobuf 通信](https://geektutu.com/post/geecache-day7.html) | [Code](gee-cache/day7-proto-buf)

### 7天用Go从零实现ORM框架 GeeORM

[GeeORM](https://geektutu.com/post/geeorm.html) 是一个模仿 [gorm](https://github.com/jinzhu/gorm) 和 [xorm](https://github.com/go-xorm/xorm) 的 ORM 框架

gorm 准备推出完全重写的 v2 版本(目前还在开发中)，相对 gorm-v1 来说，xorm 的设计更容易理解，所以 geeorm 接口设计上主要参考了 xorm，一些细节实现上参考了 gorm。

- 第一天：[database/sql 基础](https://geektutu.com/post/geeorm-day1.html) | [Code](gee-orm/day1-database-sql)
- 第二天：[对象表结构映射](https://geektutu.com/post/geeorm-day2.html) | [Code](gee-orm/day2-reflect-schema)
- 第三天：[记录新增和查询](https://geektutu.com/post/geeorm-day3.html) | [Code](gee-orm/day3-save-query)
- 第四天：[链式操作与更新删除](https://geektutu.com/post/geeorm-day4.html) | [Code](gee-orm/day4-chain-operation)
- 第五天：[实现钩子(Hooks)](https://geektutu.com/post/geeorm-day5.html) | [Code](gee-orm/day5-hooks)
- 第六天：[支持事务(Transaction)](https://geektutu.com/post/geeorm-day6.html) | [Code](gee-orm/day6-transaction)
- 第七天：[数据库迁移(Migrate)](https://geektutu.com/post/geeorm-day7.html) | [Code](gee-orm/day7-migrate)


### 7天用Go从零实现RPC框架 GeeRPC

[GeeRPC](https://geektutu.com/post/geerpc.html) 是一个基于 [net/rpc](https://github.com/golang/go/tree/master/src/net/rpc) 开发的 RPC 框架
GeeRPC 是基于 Go 语言标准库 `net/rpc` 实现的，添加了协议交换、服务注册与发现、负载均衡等功能，代码约 1k。

- 第一天 - [服务端与消息编码](https://geektutu.com/post/geerpc-day1.html) | [Code](gee-rpc/day1-codec)
- 第二天 - [支持并发与异步的客户端](https://geektutu.com/post/geerpc-day2.html) | [Code](gee-rpc/day2-client)
- 第三天 - [服务注册(service register)](https://geektutu.com/post/geerpc-day3.html) | [Code](gee-rpc/day3-service )
- 第四天 - [超时处理(timeout)](https://geektutu.com/post/geerpc-day4.html) | [Code](gee-rpc/day4-timeout )
- 第五天 - [支持HTTP协议](https://geektutu.com/post/geerpc-day5.html) | [Code](gee-rpc/day5-http-debug)
- 第六天 - [负载均衡(load balance)](https://geektutu.com/post/geerpc-day6.html) | [Code](gee-rpc/day6-load-balance)
- 第七天 - [服务发现与注册中心(registry)](https://geektutu.com/post/geerpc-day7.html) | [Code](gee-rpc/day7-registry)

### WebAssembly 使用示例

具体的实践过程记录在 [Go WebAssembly 简明教程](https://geektutu.com/post/quick-go-wasm.html)。

- 示例一：Hello World | [Code](demo-wasm/hello-world)
- 示例二：注册函数 | [Code](demo-wasm/register-functions)
- 示例三：操作 DOM | [Code](demo-wasm/manipulate-dom)
- 示例四：回调函数 | [Code](demo-wasm/callback)

</div>
</details>

What can be accomplished in 7 days? A gin-like web framework? A distributed cache like groupcache? Or a simple Python interpreter? Hope this repo can give you the answer.

## Web Framework - Gee

[Gee](https://geektutu.com/post/gee.html) is a [gin](https://github.com/gin-gonic/gin)-like framework

- Day 1 - http.Handler Interface Basic [Code](gee-web/day1-http-base)
- Day 2 - Design a Flexiable Context [Code](gee-web/day2-context)
- Day 3 - Router with Trie-Tree Algorithm [Code](gee-web/day3-router)
- Day 4 - Group Control [Code](gee-web/day4-group)
- Day 5 - Middleware Mechanism [Code](gee-web/day5-middleware)
- Day 6 - Embeded Template Support [Code](gee-web/day6-template)
- Day 7 - Panic Recover & Make it Robust [Code](gee-web/day7-panic-recover)

## Distributed Cache - GeeCache

[GeeCache](https://geektutu.com/post/geecache.html) is a [groupcache](https://github.com/golang/groupcache)-like distributed cache

- Day 1 - LRU (Least Recently Used) Caching Strategy [Code](gee-cache/day1-lru)
- Day 2 - Single Machine Concurrent Cache [Code](gee-cache/day2-single-node)
- Day 3 - Launch a HTTP Server [Code](gee-cache/day3-http-server)
- Day 4 - Consistent Hash Algorithm [Code](gee-cache/day4-consistent-hash)
- Day 5 - Communication between Distributed Nodes [Code](gee-cache/day5-multi-nodes)
- Day 6 - Cache Breakdown & Single Flight  | [Code](gee-cache/day6-single-flight)
- Day 7 - Use Protobuf as RPC Data Exchange Type | [Code](gee-cache/day7-proto-buf)

## Object Relational Mapping - GeeORM

[GeeORM](https://geektutu.com/post/geeorm.html) is a [gorm](https://github.com/jinzhu/gorm)-like and [xorm](https://github.com/go-xorm/xorm)-like object relational mapping library

Xorm's desgin is easier to understand than gorm-v1, so the main designs references xorm and some detailed implementions references gorm-v1.

- Day 1 - database/sql Basic | [Code](gee-orm/day1-database-sql)
- Day 2 - Object Schame Mapping | [Code](gee-orm/day2-reflect-schema)
- Day 3 - Insert and Query | [Code](gee-orm/day3-save-query)
- Day 4 - Chain, Delete and Update | [Code](gee-orm/day4-chain-operation)
- Day 5 - Support Hooks | [Code](gee-orm/day5-hooks)
- Day 6 - Support Transaction | [Code](gee-orm/day6-transaction)
- Day 7 - Migrate Database | [Code](gee-orm/day7-migrate)

## RPC Framework - GeeRPC

[GeeRPC](https://geektutu.com/post/geerpc.html) is a [net/rpc](https://github.com/golang/go/tree/master/src/net/rpc)-like RPC framework

Based on golang standard library `net/rpc`, GeeRPC implements more features. eg, protocol exchange, service registration and discovery, load balance, etc.

- Day 1 - Server Message Codec | [Code](gee-rpc/day1-codec)
- Day 2 - Concurrent Client | [Code](gee-rpc/day2-client)
- Day 3 - Service Register | [Code](gee-rpc/day3-service )
- Day 4 - Timeout Processing | [Code](gee-rpc/day4-timeout )
- Day 5 - Support HTTP Protocol | [Code](gee-rpc/day5-http-debug)
- Day 6 - Load Balance | [Code](gee-rpc/day6-load-balance)
- Day 7 - Discovery and Registry | [Code](gee-rpc/day7-registry)

## Golang WebAssembly Demo

- Demo 1 - Hello World [Code](demo-wasm/hello-world)
- Demo 2 - Register Functions [Code](demo-wasm/register-functions)
- Demo 3 - Manipulate DOM [Code](demo-wasm/manipulate-dom)
- Demo 4 - Callback [Code](demo-wasm/callback)





















































































#### web框架









##### 中间件

Gee 的中间件的定义与路由映射的 Handler 一致，处理的输入是`Context`对象。

插入点是框架接收到请求初始化`Context`对象后，允许用户使用自己定义的中间件做一些额外的处理，例如记录日志等，以及对`Context`进行二次加工。

另外通过调用`(*Context).Next()`函数，中间件可等待用户自己定义的 `Handler`处理结束后，再做一些额外的操作，例如计算本次处理所用时间等。即 Gee 的中间件支持用户在请求被处理的前后，做一些额外的操作。举个例子，我们希望最终能够支持如下定义的中间件，`c.Next()`表示等待执行其他的中间件或用户的`Handler`：







###### 中间件执行顺序

`index`是记录当前执行到第几个中间件，当在中间件中调用`Next`方法时，控制权交给了下一个中间件，直到调用到最后一个中间件，然后再从后往前，调用每个中间件在`Next`方法之后定义的部分。如果我们将用户在映射路由时定义的`Handler`添加到`c.handlers`列表中，结果会怎么样呢？想必你已经猜到了。

```
func A(c *Context) {
    part1
    c.Next()
    part2
}
func B(c *Context) {
    part3
    c.Next()
    part4
}
```

假设我们应用了中间件 A 和 B，和路由映射的 Handler。`c.handlers`是这样的[A, B, Handler]，`c.index`初始化为-1。调用`c.Next()`，接下来的流程是这样的：

- c.index++，c.index 变为 0
- 0 < 3，调用 c.handlers[0]，即 A
- 执行 part1，调用 c.Next()
- c.index++，c.index 变为 1
- 1 < 3，调用 c.handlers[1]，即 B
- 执行 part3，调用 c.Next()
- c.index++，c.index 变为 2
- 2 < 3，调用 c.handlers[2]，即Handler
- Handler 调用完毕，返回到 B 中的 part4，执行 part4
- part4 执行完毕，返回到 A 中的 part2，执行 part2
- part2 执行完毕，结束。

c.Next: 从当前中间件的执行逻辑跳转到下一个中间件,函数栈底结束之后,向上返回弹栈







##### 6-模板



###### 服务端渲染

在服务端完成对于网页的渲染工作,将完整的html页面发送给客户端

SSR的主要优势包括：

1. **更快的加载速度**：由于浏览器直接接收到的是服务器生成的完整HTML页面，因此可以显著减少首次加载的时间，提高用户体验。(在服务端进行渲染,这个渲染的时间可能在最开始部署在服务端时就已经完成,而如果将这个加载放在客户端执行,则会将其加载时间推延到客户端运行时间中)
2. **改善搜索引擎优化（SEO）**：搜索引擎爬虫可以直接抓取到服务器渲染好的页面内容，这有助于提高网页在搜索引擎中的排名。(因为爬虫相当于一种客户端, 其拿到JavaScript之后是无法进行渲染的)
3. **更广泛的设备支持**：因为页面是在服务器端渲染的，所以不需要客户端浏览器支持JavaScript，这意味着SSR可以在更多设备上运行。

总的来说，服务器端渲染是一种有效的技术，可以提升Web应用的性能和用户体验，同时也有利于搜索引擎优化





服务端渲染要做的工作: 将自身的数据结构嵌入到html界面之中







##### 7-错误恢复

###### defer

panic在退出之前,会先完成协程上用defer声明的任务,然后再报错



###### recover

避免因为panic导致整个程序终止

recover只能在defer中生效

在这里需要当服务端有错误发生时,能够返回server error, 而不是直接宕机服务器

错误处理可以作为一种中间件



打印堆栈信息 - trace

```go
defer func() {
	if err := recover(); err != nil {
		message := fmt.Sprintf("%s", err)
		log.Printf("%s\n\n", trace(message))
		c.Fail(http.StatusInternalServerError, "Internal Server Error")
	}
}

func trace(message string) string {
	var pcs [32]uintptr
	n := runtime.Callers(3, pcs[:]) // skip first 3 caller

	var str strings.Builder
	str.WriteString(message + "\nTraceback:")
	for _, pc := range pcs[:n] {
		fn := runtime.FuncForPC(pc)
		file, line := fn.FileLine(pc)
		str.WriteString(fmt.Sprintf("\n\t%s:%d", file, line))
	}
	return str.String()
}
```





























#### 分布式缓存



##### 2-单机并发缓存

单机并发应该就是不同线程之间的并发



##### 4-一致性hash



###### 1.1hash路由

当执行分布式负载均衡时,通过一致性hash来计算这个请求最终应该属于哪个节点



###### 1.2节点数量变化



当我们采用取余的方法时,如果此时节点数量发生变化, 那么之前存储的数据很多都作废了, 比如key为7的KV数据在4个节点时取余, 应存储在节点3上,而如果只有3个节点,则应该存储在节点1上, 所以可能会产生新的数据迁移的开销, 这样大部分缓存失效了, 所以访问时会触发DB读取, 从而增加数据get的开销, 容易引起缓存雪崩



- 取余hash:  
  - 无法适应节点数量变化
- 一致性hash:
  - 节点ID通过hash放置在环上, 节点之间的间隙就是该节点的管辖区域,  插入的kv通过hash计算插入环中,  
  - 适应节点数量变化, 但节点的退出会引发数据倾斜, 前一个节点管辖的区域相当于全部交接给了下一个节点
- 一致性hash+虚拟节点
  - 即节点在环上管辖的区域是碎片化的而不是一整个, 所以当该节点失效之后, 其区域是被多个节点瓜分



一致性hash最重要的使用场景就是 "节点数量发生变化"



##### 6-防止缓存击穿

- 缓存雪崩: 不同key的太多的请求落到了db

- 缓存击穿: 一个key的太多请求落到了db
- 缓存穿透: 不存在的key的太多请求落到了db



防止缓存击穿,即意味着对于同一key进行保护

客户端 -> 节点1 -> 节点2

当客户端触发缓存击穿时,如果只在数据库这里做保护, 即节点二处知晓同一key的请求,但是节点1->节点2的http请求是无法避免的,

```go
package singleflight

import "sync"

type call struct {
	wg  sync.WaitGroup // 等待一组goroutine的完成,计数器实现
	val interface{}
	err error
}

type Group struct {
	mu sync.Mutex       // protects m
	m  map[string]*call
}
```







```go
func (g *Group) Do(key string, fn func() (interface{}, error)) (interface{}, error) {
	g.mu.Lock()
	if g.m == nil {
		g.m = make(map[string]*call)
	}
	if c, ok := g.m[key]; ok { // 如果请求重复, 则在上次执行完毕时一起返回这个结果
		g.mu.Unlock()
		c.wg.Wait()
		return c.val, c.err
	}
    
    // 第一次执行请求
	c := new(call)
	c.wg.Add(1) // 请求计数+1
	g.m[key] = c // kv 标记该call
	g.mu.Unlock()

    // 执行操作
	c.val, c.err = fn()
	c.wg.Done() // 请求结束

    // 删除该请求的相关信息
	g.mu.Lock()
	delete(g.m, key)
	g.mu.Unlock()

	return c.val, c.err
}
```



这里的请求去重,指的是在第一个请求到达之后, 在其返回结果之前的这段时间内, 所有重入的请求都会被去重, 当第一个请求结果拿到之后, 统一返回结果

这里实际上就是一个读者写者的多线程同步问题,  第一个执行操作相当于是写者, 而后的请求都是读者, 读取第一个写者的结果









##### 7-protocolbuf

- 传输前使用 protobuf 编码，接收方再进行解码，可以显著地降低二进制传输的大小

- protobuf 可非常适合传输结构化数据，便于通信字段的扩展。

使用protobuf的优点: 提升性能, 传递结构化数据







#### ORM

##### 1-ORM对象关系映射

将数据库中的表/条目/属性与类与对象中的类/实例/变量所联系起来,当在程序中操作实例时,即完成了对于DB中的数据的管理



这里有一个点在于, 并不是说你为一个具体的类去写一套 载入/导出 的逻辑, 而是说, 对于任意的类都可以, 即是一个类似于模板的操作, 即只用一套代码来去应对多种结构



所以我们接受的是一个任意类型的结构体的指针, 我们要能够对该指针拿到其所有变量, 

**反射**: 反射可以通过指针拿到对应结构体的名称/变量名/方法等信息

```go
// 拿到类型名称
typ := reflect.Indirect(reflect.ValueOf(&Account{})).Type()
fmt.Println(typ.Name()) // Account

// 对于每个变量, 拿到其名称
for i := 0; i < typ.NumField(); i++ {
    field := typ.Field(i)
    fmt.Println(field.Name) // Username Password
}
```



- 如何在开发者没有感知的情况下适配各种数据库呢?
- 当对象字段发生变化时,数据库表结构如何自动更新?





##### 2-链式调用

将多个设置写成一句更符合逻辑, 这里类似于C++的输入输出运算符的重载

所需做的就是将函数返回设置为该对象





##### 3-钩子函数

Hook，翻译为钩子，其主要思想是提前在可能增加功能的地方埋好(预设)一个钩子，当我们需要重新修改或者增加这个地方的逻辑的时候，把扩展的类或者方法挂载到这个点即可。

钩子的应用非常广泛，例如 Github 支持的 travis 持续集成服务，当有 `git push` 事件发生时，会触发 travis 拉取新的代码进行构建。

IDE 中钩子也非常常见，比如，当按下 `Ctrl + s` 后，自动格式化代码。再比如前端常用的 `hot reload` 机制，前端代码发生变更时，自动编译打包，通知浏览器自动刷新页面，实现所写即所得。

钩子机制设计的好坏，取决于扩展点选择的是否合适。例如对于持续集成来说，代码如果不发生变更，反复构建是没有意义的，因此钩子应设计在代码可能发生变更的地方，比如 MR、PR 合并前后。

那对于 ORM 框架来说，合适的扩展点在哪里呢？很显然，记录的增删查改前后都是非常合适的。









##### 6-实现事务

想要在自己的ORM框架中实现事务, 即多个读写任务通过ORM框架请求到DB时,能够保证执行结果和DB的事务处理逻辑一致

ACID性质:

A: 原子性 atomic

C: 一致性 constant

I: 隔离性 island

D: 持久性 提交即持久化





Sqlite中通过 BEGIN, COMMIT来作为事务的开始和结束

GO语言中对于事务的支持

1. tx = db.Begin: 事务开始,拿到事务的实例
2. tx.Exec: 执行命令
3. tx.rollBack: 回滚
4. tx.commit: 提交

如果不需要事务: 命令由sql.DB执行

如果需要事务: 命令由tx执行



