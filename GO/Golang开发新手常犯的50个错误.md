《50 Shades of Go: Traps, Gotchas, and Common Mistakes for New [Golang](https://so.csdn.net/so/search?q=Golang&spm=1001.2101.3001.7020) Devs》

原文地址：[http://devs.cloudimmunity.com/gotchas-and-common-mistakes-in-go-golang/index.html](http://devs.cloudimmunity.com/gotchas-and-common-mistakes-in-go-golang/index.html)

### 一、初级

###### 1、不允许左大括号单独一行(遇到过)

###### 2、不允许出现未使用的变量(遇到过)

###### 3、不允许出现未使用的import(遇到过)

解决方法：使用`_`作为引入包别名

    package main
    
    import (  
        _ "fmt"         // 指定别名为`_`
        "log"
        "time"
    )
    
    var _ = log.Println // 变量名为`_`
    
    func main() {  
        _ = time.Now
    }

###### 4、短的变量声明(Short Variable Declarations)只能在函数内部使用(遇到过)

    package main
    
    // myvar := 1   // error
    var myvar = 1   // ok
    
    func main() {  
    }

###### 5、不能使用短变量声明(Short Variable Declarations)重复声明 (遇到过)

###### 6、不能使用短变量声明(Short Variable Declarations)这种方式来设置字段值 (遇到过)

    package main
    
    func main() {  
        one := 0
        // one := 1                   //error: Redeclaring Variables Using Short Variable Declarations
        // data.result, err := work() //error：Can't Use Short Variable Declarations to Set Field Values
        data.result, err = work()     //ok
    }

###### 7、意外的变量幽灵（Accidental Variable Shadowing）(遇到过)

短变量声明语法，很好用，但是代码块中使用短变更声明与外部相同的变量时，  
没有语法编译错误，但是代码块中同名短变量声明从声明开始到代码块结束，对变量的修改将不会影响到外部变量！

    package main
    
    import "fmt"
    
    func main() {  
        x := 1
        fmt.Println(x)     //prints 1
        {
            fmt.Println(x) //prints 1
            // x = 3
            x := 2         // 不会影响到外部x变量的值
            fmt.Println(x) //prints 2
            //x = 5        // 不会影响到外部x变量值
        }
        fmt.Println(x)     //prints 3
    }

这种现象称之为`幽灵变量`，可以使用`go tool vet -shadow you_file.go`检查幽灵变量。  
使用`go-ynet`命令会执行更多幽灵变量的检测。

###### 8、不能使用`nil`初始化一个未指定类型的变量

    // var x = nil                 //error
    var x interface{} = nil  // OK
    _ = x

###### 9、不能直接使用`nil`值的Slice和Map (遇到过)

###### 10、map使用make分配内存时可指定capicity，但是不能对map使用cap函数 (遇到过)

​	这里的意思是, 可以对hash调用 cap_init, 即初始化时reserve一个size,但是对其是无法调用cap函数的, 原因是hash是可以通过rehash来扩容, 但其扩容并不是向slice那样需要连续内存空间, 所以不需要担心cap,故而也没有对外提供这个

```go
m := make(map[string]int, 10) // 创建一个初始长度为 10 的 map
```



###### 11、字符串不允许使用`nil`值 (遇到过)

在golang中，nil只能赋值给指针、channel、func、interface、map或slice类型的变量。

    var x string = nil  //error
    if x == nil {       //error
        x = "default"
    }
    
    //var x string      //defaults to "" (zero value)
    if x == "" {
        x = "default"
    }

###### 12、数组用于函数传参时是值复制 (已遇到)

但是使用slice时,就是调用的引用传递

_注意：方法或函数调用时，传入参数都是值复制（跟赋值一致），除非是map、slice、channel、指针类型这些特殊类型是引用传递。_

    x := [3]int{1,2,3}
    
    // 数组在函数中传参是值复制
    func(arr [3]int) {
        arr[0] = 7
        fmt.Println(arr) //prints [7 2 3]
    }(x)
    fmt.Println(x)       //prints [1 2 3] (not ok if you need [7 2 3])
    
    // 使用数组指针实现引用传参
    func(arr *[3]int) {
        (*arr)[0] = 7
        fmt.Println(arr) //prints &[7 2 3]
    }(&x)
    fmt.Println(x)       //prints [7 2 3]
    





###### 13、range关键字返回是键值对，而不是值 (注意)

如果只用一个val来接受遍历, 则其为索引

如果用 a,b := range x 来遍历, 则a是索引 b是value

    x := []string{"a","b","c"}
    
    // for v := range x {
    //     fmt.Println(v) //prints 0, 1, 2
    // }
    
    for _, v := range x {
        fmt.Println(v) //prints a, b, c
    }





###### 14、Slice和Array是一维的

Go表面上看起来像多维的，实际上只是一维的。但可以使用原始的一维数组、一维的切片来实现多维。





###### 15、从不存在key的map中取值时，返回的总是”0值” (遇到过)

存在就是   value, ok=true

不存在就是   value是 零值, 这里string的零值是 "" 空字符串,  而如果是int的话,则是0



    x := map[string]string{"one": "1", "two": "2"}
    	if value, ok := x["two"]; !ok { // 判断是否存在，x[key]始终有返回值, 只不过有的ok有的不ok
    		fmt.Println(value, "Not OK")
    	} else {
    		fmt.Println(value, "OK")
    	}

###### 16、字符串是不可变 (遇到过)

如果要改, 就将 string 改为 []byte

    x := "text"
    // x[0] = 'T'       // error
    
    xtytes := []byte(x) 
    xbytes[0] = 'T'     // ok
    
    fmt.Println(string(xbytes)) //prints Text

###### 17、字符串与`[]byte`之间的转换是复制（有内存损耗），可以用map\[string\] \[\]byte建立字符串与\[\]byte之间映射，也可range来避免内存分配来提高性能

range不能变内存分配

    //[]byte: 遍历string 
    for i,v := range []byte(str) {
    }





###### 18、string的索引操作返回的是byte（或uint8），如想获取字符可使用`for range`，也可使用`unicode/utf8`包和`golang.org/x/exp/utf8string`包的`At()`方法。(遇到过)

char, size := utf8.DecodeRuneInString(str[i:])

读取string中从i开始的char, 比如英文的size是1, 中文的size是3



string转成int：
int, err := strconv.Atoi(string)
string转成int64：
int64, err := strconv.ParseInt(string, 10, 64)
int转成string：
string := strconv.Itoa(int)
int64转成string：
string := strconv.FormatInt(int64,10)



###### 19、字符串并不总是UTF8的文本 (遇到过)

还有可能是中文 



###### 20、`len(str)`返回的是字符串的字节数，获取字符串的rune数是使用`unicode/utf8.RuneCountInString()`函数，但注意一些字符也可能是由多个rune组成，如`é`是两个rune组成。  (遇到过)

```
size := utf8.RuneCountInString(str)
	fmt.Println("size is", size)

	count := len(str)
	fmt.Println("len is", count)
```



###### 21、在Slice、Array、Map的多行书写最后的逗号不可省略 (没有问题啊)

    x := []int{
        1,
        // 2    //error
        3,      // ok
    }
    
    y := []int {1, 2, 3,}   // ok
    z := []int {1, 2, 3}    // 单行书写，最后一个元素的逗号可省略





###### 22、内置数据结构的操作并不同步，但可把Go提供了并发的特性使用起来：goroutines和channels。



###### 23、使用for range迭代String，是以rune来迭代的。(遇到过)

一个字符，也可以有多个rune组成。需要处理字符，尽量使用`golang.org/x/text/unicode/norm`包。

for range总是尝试将字符串解析成utf8的文本，对于它无法解析的字节，它会返回`oxfffd`的rune字符。  
因此，任何包含非utf8的文本，一定要先将其转换成字符切片(`[]byte`)。

     data := "A\xfe\x02\xff\x04"
    for _,v := range data {
        fmt.Printf("%#x ",v)
    }
    //prints: 0x41 0xfffd 0x2 0xfffd 0x4 (not ok)
    
    fmt.Println()
    for _,v := range []byte(data) {
        fmt.Printf("%#x ",v)
    }
    //prints: 0x41 0xfe 0x2 0xff 0x4 (good)



###### 24、使用for range迭代map时每次迭代的顺序可能不一样，因为map的迭代是随机的。(遇到过)



###### 25、switch的case默认匹配规则不同于其它语言的是，匹配case条件后默认退出，除非使用fallthrough继续匹配；而其它语言是默认继续匹配，除非使用break退出匹配。(遇到过)



###### 26、只有后置自增、后置自减，不存在前置自增、前置自减 (遇到过)



###### 27、位运算的非操作是`^`（跟异或位运算一样），有别于其它语言的`~`。(遇到过)



###### 28、位运算(与、或、异或、取反)优先级高于四则运算(加、减、乘、除、取余)，有别于C语言。(遇到过)



###### 29、结构体在序列化时非导出字段（以小写字母开头的字段名）不会被encode，因此在decode时这些非导出字段的值为”0值”

dump时 该字段直接没有, 而decode时, 则会将其置为默认零值



###### 30、程序不等所有goroutine结束就会退出。可通过channel实现主协程(main goroutine)等待所有goroutine完成。(类似于线程的join)



###### 31、对于无缓存区的channel，写入channel的goroutine会阻塞直到被读取，读取channel的goroutine会阻塞直到有数据写入。

1. **无缓冲区通道**：

   - **写入操作**：当一个 goroutine 尝试向一个无缓冲区通道写入值时，如果通道已满（即通道没有缓冲区），写入操作会阻塞，直到另一个 goroutine 从通道读取值。
   - **读取操作**：当一个 goroutine 尝试从无缓冲区通道读取值时，如果通道为空（即通道没有数据），读取操作会阻塞，直到另一个 goroutine 向通道写入值。

2. **有缓冲区通道**：

   - **写入操作**：如果缓冲区未满，写入操作会立即成功。如果缓冲区已满，写入操作会阻塞，直到缓冲区有空间。
   - **读取操作**：如果缓冲区非空，读取操作会立即成功。如果缓冲区为空，读取操作会阻塞，直到缓冲区有数据

   

###### 32、从一个closed状态的channel读取数据是安全的，可通过返回状态（第二个返回参数）判断是否关闭；而向一个closed状态的channel写数据会导致panic。(遇到过)

所以在读取时,需要先判断是否关闭 

```go
val, ok := <-ch // 从通道读取数据
	if ok {
		fmt.Println("Received value:", val)
	} else {
		fmt.Println("Channel is closed")
	}
```





###### 33、向一个`nil`值（未用make分配空间）的channel发送或读取数据，会导致永远阻塞。

实践之后是直接报错

    package main
    
    import (  
        "fmt"
        "time"
    )
    
    func main() {  
        var ch chan int
        for i := 0; i < 3; i++ {
            go func(idx int) {
                ch <- (idx + 1) * 2
            }(i)
        }
    
        //get first result
        fmt.Println("result:",<-ch)
        //do other work
        time.Sleep(2 * time.Second)
    }





###### 34、方法接收者是类型（T），接收者只是原对象的值复制，在方法中修改接收者不会修改原始对象的值；如果方法接收者是指针类型（\*T），是对原对象的引用，方法中对其修改当然是原对象修改。(遇到过)

    type data struct {  
        num int
        key *string
        items map[string]bool
    }
    
    func (this *data) pmethod() {  
        this.num = 7
    }
    
    func (this data) vmethod() {  
        this.num = 8
        *this.key = "v.key"
        this.items["vmethod"] = true
    }

###### 35、log包中的`log.Fata`l和`log.Panic`不仅仅记录日志，还会中止程序。它不同于`Logging`库。

在 Go 语言中，`log` 包是一个标准库，用于记录日志信息。它提供了几个日志级别，包括 `Info`、`Warn`、`Error`、`Fatal` 和 `Panic`。这些日志级别与它们的行为有关：

- `Info`、`Warn` 和 `Error`：这些日志级别不会中断程序的执行。它们只是简单地记录日志信息，并且程序会继续执行。

- `Fatal` 和 `Panic`：这些日志级别会中断程序的执行。

  - `Fatal` 会在记录日志信息后调用 `os.Exit(1)`，这会终止程序并返回退出状态码 1。
  - `Panic` 会在记录日志信息后调用 `panic`，这会导致程序立即进入恐慌模式，并开始执行所有未完成的 defer 语句，然后程序会崩溃并打印堆栈跟踪信息。

  

### 二、中级

###### 1、关闭HTTP的Response.Body

使用defer语句关闭资源时要注意nil值，在defer语句之前要进行nill值处理

以下以http包的使用为例

    package main
    
    import (  
        "fmt"
        "net/http"
        "io/ioutil"
    )
    
    func main() {  
        resp, err := http.Get("https://api.ipify.org?format=json")
    
        if resp != nil {
            defer resp.Body.Close()     // ok，即使不读取Body中的数据，即使Body是空的，也要调用close方法
        }
    
        //defer resp.Body.Close()       // （1）Error:在nil值判断之前使用，resp为nil时defer中的语句执行会引发空引用的panic
        if err != nil {
            fmt.Println(err)
            return
        }
    
        //defer resp.Body.Close()       // （2）Error:排除了nil隐患，但是出现重定向错误时，仍然需要调用close
        body, err := ioutil.ReadAll(resp.Body)
        if err != nil {
            fmt.Println(err)
            return
        }
    
        fmt.Println(string(body))
    }

在Go 1.5之前`resp.Body.Close()`会读取并丢失body中的数据，保证在启用keepaliva的http时能够在下一次请求时重用。  
在Go 1.5之后，就需要在关闭前手动处理。

    _, err = io.Copy(ioutil.Discard, resp.Body)   // 手动清空

如果只是读取Body的部分，就很有必要在关闭Body之前做这种手动处理。例如处理json api响应时`json.NewDecoder(resp.Body).Decode(&data)`就需要处理掉剩余的数据。







###### 2、关闭HTTP连接：

(1) 可使用`req.Close=true`，表示在http请求完成时关闭连接

(2) 添加`Connection: close`的连接请求头。http服务端也会发送`Connection: close`的响应头，http库处理响应时会关闭连接。

    package main
    
    import (  
        "fmt"
        "net/http"
        "io/ioutil"
    )
    
    func main() {  
        req, err := http.NewRequest("GET","http://golang.org",nil)
        if err != nil {
            fmt.Println(err)
            return
        }
    
        req.Close = true // 这告诉 HTTP 客户端在完成请求后立即关闭连接 (短连接)
        //or do this:
        //req.Header.Add("Connection", "close") // 与前者相同
    
        resp, err := http.DefaultClient.Do(req) // 发出请求 DefaultClient
        if resp != nil {
            defer resp.Body.Close()
        }
    
        if err != nil {
            fmt.Println(err)
            return
        }
    
        body, err := ioutil.ReadAll(resp.Body)
        if err != nil {
            fmt.Println(err)
            return
        }
    
        fmt.Println(len(string(body)))
    }

（3）全局关闭http连接重用。

对于相同http server发送多个请求时，适合保持网络连接；  
但对于短时间内向多个HTTP服务器发送一个或两个请求时，最好在每次接收到服务端响应后关闭网络链接

    package main
    
    import (  
        "fmt"
        "net/http"
        "io/ioutil"
    )
    
    func main() {  
        tr := &http.Transport{DisableKeepAlives: true} // 关闭长连接
        client := &http.Client{Transport: tr} // 使用tr作为传输层
    
        resp, err := client.Get("http://golang.org")
        if resp != nil {
            defer resp.Body.Close()
        }
    
        if err != nil {
            fmt.Println(err)
            return
        }
    
        fmt.Println(resp.StatusCode)
    
        body, err := ioutil.ReadAll(resp.Body)
        if err != nil {
            fmt.Println(err)
            return
        }
    
        fmt.Println(len(string(body)))
    }





###### 3、Json反序列化数字到interface{}类型的值中，默认解析为float64类型，在使用时要注意。

      var data = []byte(`{"status": 200}`)
    
      var result map[string]interface{}
      if err := json.Unmarshal(data, &result); err != nil {
        fmt.Println("error:", err)
        return
      }
    
      //var status = result["status"].(int) //error: panic: interface conversion: interface is float64, not int 
      var status = uint64(result["status"].(float64)) //ok
      fmt.Println("status value:",status)

(1) 使用`Decoder`类型解析JSON

    var data = []byte(`{"status": 200}`)
    
    var decoder = json.NewDecoder(bytes.NewReader(data))
    decoder.UseNumber()
    
    if err := decoder.Decode(&result); err != nil {
        fmt.Println("error:", err)
        return
    }
    
    var status,_ = result["status"].(json.Number).Int64() //ok
    fmt.Println("status value:",status)
    
    var status2 uint64
    if err := json.Unmarshal([]byte(result["status"].(json.Number).String()), &status2); err != nil {
        fmt.Println("error:", err)
        return
    }


（2）使用struct结构体映射

    var data = []byte(`{"status": 200}`)
    var result struct {
        Status uint64 `json:"status"`
    }
    
    if err := json.NewDecoder(bytes.NewReader(data)).Decode(&result); err != nil {
        fmt.Println("error:", err)
        return
    }
    
    fmt.Printf("result => %+v",result) //prints: result => {Status:200}

(3) 使用struct映射数字为`json.RawMessage`

        records := [][]byte{
            []byte(`{"status": 200, "tag":"one"}`),
            []byte(`{"status":"ok", "tag":"two"}`),
        }
    
        for idx, record := range records {
            var result struct {
                StatusCode uint64
                StatusName string
                Status json.RawMessage `json:"status"`
                Tag string             `json:"tag"`
            }
    
            if err := json.NewDecoder(bytes.NewReader(record)).Decode(&result); err != nil {
                fmt.Println("error:", err)
                return
            }
    
            var sstatus string
            if err := json.Unmarshal(result.Status, &sstatus); err == nil {
                result.StatusName = sstatus
            }
    
            var nstatus uint64
            if err := json.Unmarshal(result.Status, &nstatus); err == nil {
                result.StatusCode = nstatus
            }
    
            fmt.Printf("[%v] result => %+v\n",idx,result)
        }







###### 4、Struct、Array、Slice、Map的比较

如果struct结构体的所有字段都能够使用`==`操作比较，那么结构体变量也能够使用`==`比较。  
但是，如果struct字段不能使用`==`比较，那么结构体变量使用`==`比较会导致编译错误。

同样，array只有在它的每个元素能够使用`==`比较时，array变量才能够比较。

Go提供了一些用于比较不能直接使用`==`比较的函数，其中最常用的是`reflect.DeepEqual()`函数。

`DeepEqual()`函数对于nil值的slice与空元素的slice是不相等的，这点不同于`bytes.Equal()`函数。

    type data struct {  
        num int
        fp float32
        complex complex64
        str string
        char rune
        yes bool
        events <-chan string
        handler interface{}
        ref *byte
        raw [10]byte
    }
    
    v1 := data{}
    v2 := data{}
    fmt.Println("v1 == v2:",v1 == v2)   //prints: v1 == v2: true
    
    type data2 struct {  
        num int                //ok
        checks [10]func() bool //not comparable
        doit func() bool       //not comparable
        m map[string] string   //not comparable
        bytes []byte           //not comparable
    }
    
    v3 := data2{}
    v4 := data2{}
    fmt.Println("v3 == v4:",v3 == v4)   // error
    
    v5 := data2{}
    v6 := data2{}
    fmt.Println("v5 == v6:",reflect.DeepEqual(v5,v6)) //prints: v5 == v6: true
    
    m1 := map[string]string{"one": "a","two": "b"}
    m2 := map[string]string{"two": "b", "one": "a"}
    fmt.Println("m1 == m2:",reflect.DeepEqual(m1, m2)) //prints: m1 == m2: true
    
    s1 := []int{1, 2, 3}
    s2 := []int{1, 2, 3}
    fmt.Println("s1 == s2:",reflect.DeepEqual(s1, s2)) //prints: s1 == s2: true
    
    var b1 []byte = nil
    b2 := []byte{}
    fmt.Println("b1 == b2:",reflect.DeepEqual(b1, b2)) //prints: b1 == b2: false
    
    var b3 []byte = nil
    b4 := []byte{}
    fmt.Println("b3 == b4:",bytes.Equal(b3, b4)) //prints: b3 == b4: true

`DeepEqual()`函数并不总是能够正确处理slice。

    var str string = "one"
    var in interface{} = "one"
    fmt.Println("str == in:",str == in,reflect.DeepEqual(str, in))  //prints: str == in: true true
    
    v1 := []string{"one","two"}
    v2 := []interface{}{"one","two"}
    fmt.Println("v1 == v2:",reflect.DeepEqual(v1, v2))              //prints: v1 == v2: false (not ok)
    
    data := map[string]interface{}{
        "code": 200,
        "value": []string{"one","two"},
    }
    encoded, _ := json.Marshal(data)
    var decoded map[string]interface{}
    json.Unmarshal(encoded, &decoded)
    fmt.Println("data == decoded:",reflect.DeepEqual(data, decoded)) //prints: data == decoded: false (not ok)

如果要忽略大小写来比较包含文字数据的字节切片(byte slice)，  
不建议使用`bytes`包和`strings`包里的`ToUpper()`、`ToLower()`这些函数转换后再用`==`、`byte.Equal()`、`bytes.Compare()`等比较，

`ToUpper()`、`ToLower()`只能处理英文文字，对其它语言无效。因此建议使用`strings.EqualFold()`和`bytes.EqualFold()`

如果要比较用于验证用户数据密钥信息的字节切片时，使用`reflact.DeepEqual()`、`bytes.Equal()`、  
`bytes.Compare()`会使应用程序遭受计时攻击(Timing Attack)，可使用`crypto/subtle.ConstantTimeCompare()`避免泄漏时间信息。

###### 5、从panic中恢复

`recover()`函数能够捕获或拦截panic，但必须在`defer`函数或语句中直接调用，否则无效。

    package main
    
    import "fmt"
    
    func doRecover() {  
        fmt.Println("recovered =>",recover()) //prints: recovered => <nil>
    }
    
    func main() {  
        defer func() {
            fmt.Println("recovered:",recover()) // ok
        }()
    
        defer func() {
            doRecover() //panic is not recovered
        }()
    
        // recover()   //doesn't do anything
        panic("not good")
        // recover()   //won't be executed :)
    
        fmt.Println("ok")
    }

###### 6、在slice、array、map的for range子句中修改和引用数据项

使用range获取的数据项是从集合元素的复制过来的，并非引用原始数据，但使用索引能访问原始数据。

    data := []int{1,2,3}
    for _,v := range data {
        v *= 10          // original item is not changed
    }
    
    data2 := []int{1,2,3}
    for i,v := range data2 {
        data2[i] *= 10       // change original item
    }
    
    // 元素是指针类型就不一样了
    data3 := []*struct{num int} {{1}, {2}, {3}}
    for _,v := range data {
        v.num *= 10
    }
    
    fmt.Println("data:", data)              //prints data: [1 2 3]
    fmt.Println("data:", data2)             //prints data: [10 20 30]
    fmt.Println(data3[0],data3[1],data3[2])    //prints &{10} &{20} &{30}

###### 7、Slice中的隐藏数据

从一个slice上再生成一个切片slice，新的slice将直接引用原始slice的那个数组，两个slice对同一数组的操作，会相互影响。

可通过为新切片slice重新分配空间，从slice中copy部分的数据来避免相互之间的影响。

    raw := make([]byte,10000)
    fmt.Println(len(raw),cap(raw),&raw[0])      //prints: 10000 10000 <byte_addr_x>
    
    data := raw[:3]
    fmt.Println(len(data),cap(data),&data[0])   //prints: 3 10000 <byte_addr_x>
    
    res := make([]byte,3)
    copy(res,raw[:3])
    fmt.Println(len(res),cap(res),&res[0])      //prints: 3 3 <byte_addr_y>

###### 8、Slice超范围数据覆盖

从已存在的切片slice中继续切片时，新切片的capicity等于原capicity减去新切片之前部分的数量，新切片与原切片都指向同一数组空间。

新生成切片之间capicity区域是重叠的，因此在添加数据时易造成数据覆盖问题。

slice使用append添加的内容时超出capicity时，会重新分配空间。  
利用这一点，将要修改的切片指定capicity为切片当前length，可避免切片之间的超范围覆盖影响。

        path := []byte("AAAA/BBBBBBBBB")
        sepIndex := bytes.IndexByte(path,'/')
        dir1 := path[:sepIndex]
        // 解决方法
        // dir1 := path[:sepIndex:sepIndex] //full slice expression
        dir2 := path[sepIndex+1:]
        fmt.Println("dir1 =>",string(dir1)) //prints: dir1 => AAAA
        fmt.Println("dir2 =>",string(dir2)) //prints: dir2 => BBBBBBBBB
    
        dir1 = append(dir1,"suffix"...)
        path = bytes.Join([][]byte{dir1,dir2},[]byte{'/'})
    
        fmt.Println("dir1 =>",string(dir1)) //prints: dir1 => AAAAsuffix
        fmt.Println("dir2 =>",string(dir2)) //prints: dir2 => uffixBBBB (not ok)
    
        fmt.Println("new path =>",string(path))

###### 9、Slice增加元素重新分配内存导致的怪事

slice在添加元素前，与其它切片共享同一数据区域，修改会相互影响；但添加元素导致内存重新分配之后，不再指向原来的数据区域，修改元素，不再影响其它切片。

        s1 := []int{1,2,3}
        fmt.Println(len(s1),cap(s1),s1) //prints 3 3 [1 2 3]
    
        s2 := s1[1:]
        fmt.Println(len(s2),cap(s2),s2) //prints 2 2 [2 3]
    
        for i := range s2 { s2[i] += 20 }
    
        //still referencing the same array
        fmt.Println(s1) //prints [1 22 23]
        fmt.Println(s2) //prints [22 23]
    
        s2 = append(s2,4)
    
        for i := range s2 { s2[i] += 10 }
    
        //s1 is now "stale"
        fmt.Println(s1) //prints [1 22 23]
        fmt.Println(s2) //prints [32 33 14]

###### 10、类型重定义与方法继承

从一个已存在的(non-interface)非接口类型重新定义一个新类型时，不会继承原类型的任何方法。  
可以通过定义一个组合匿名变量的类型，来实现对此匿名变量类型的继承。

但是从一个已存在接口重新定义一个新接口时，新接口会继承原接口所有方法。

###### 11、从”for switch”和”for select”代码块中跳出。

无label的break只会跳出最内层的`switch`/`select`代码块。  
如需要从`switch`/`select`代码块中跳出外层的for循环，可以在for循环外部定义label，供break跳出。

`return`当然也是可以的，如果在这里可以用的话。

###### 12、在for语句的闭包中使用迭代变量会有问题

在for迭代过程中，迭代变量会一直保留，只是每次迭代值不一样。  
因此在for循环中在闭包里直接引用迭代变量，在执行时直接取迭代变量的值，而不是闭包所在迭代的变量值。

如果闭包要取所在迭代变量的值，就需要for中定义一个变量来保存所在迭代的值，或者通过闭包函数传参。

    package main
    
    import (  
        "fmt"
        "time"
    )
    
    func forState1(){
        data := []string{"one","two","three"}
    
        for _,v := range data {
            go func() {
                fmt.Println(v)
            }()
        }
        time.Sleep(3 * time.Second)    //goroutines print: three, three, three
    
        for _,v := range data {
            vcopy := v // 使用临时变量
            go func() {
                fmt.Println(vcopy)
            }()
        }
        time.Sleep(3 * time.Second)    //goroutines print: one, two, three
    
        for _,v := range data {
            go func(in string) {
                fmt.Println(in)
            }(v)
        }
        time.Sleep(3 * time.Second)    //goroutines print: one, two, three
    }
    
    func main() {  
        forState1()
    }

再看一个坑埋得比较深的例子。

    package main
    
    import (  
        "fmt"
        "time"
    )
    
    type field struct {  
        name string
    }
    
    func (p *field) print() {  
        fmt.Println(p.name)
    }
    
    func main() {  
        data := []field{{"one"},{"two"},{"three"}}
        for _,v := range data {
            // 解决办法：添加如下语句
            // v := v
            go v.print()
        }
        time.Sleep(3 * time.Second)     //goroutines print: three, three, three
    
        data2 := []*field{{"one"}, {"two"}, {"three"}}  // 注意data2是指针数组
        for _, v := range data2 {
            go v.print()                // go执行是函数，函数执行之前，函数的接受对象已经传过来
        }
        time.Sleep(3 * time.Second)     //goroutines print: one, two, three
    }

###### 13、`defer`函数调用参数

`defer`后面必须是函数或方法的调用语句。`defer`后面不论是函数还是方法，输入参数的值是在`defer`声明时已计算好，  
而不是调用开始计算。

要特别注意的是，`defer`后面是方法调用语句时，方法的接受者是在defer语句执行时传递的，而不是defer声明时传入的。

    type field struct{
        num int
    }
    func(t *field) print(n int){
        fmt.println(t.num, n)
    }
    func main() {    
        var i int = 1
        defer fmt.Println("result2 =>",func() int { return i * 2 }())
        i++
    
        v := field{1}
        defer v.print(func() int { return i * 2 }())
        v = field{2}
        i++
    
        // prints: 
        // 2 4
        // result => 2 (not ok if you expected 4)
    }

###### 14、`defer`语句调用是在当前函数结束之后调用，而不是变量的作用范围。

    for _,target := range targets {
        f, err := os.Open(target)
        if err != nil {
            fmt.Println("bad target:",target,"error:",err) //prints error: too many open files
            break
        }
        defer f.Close()         //will not be closed at the end of this code block, but closed at end of this function
        // 解决方法1：不用defer
        // f.Close()
        // 解决方法2：将for中的语句添加到匿名函数中执行。
        // func () {
        // }() 
    }

###### 15、失败的类型断言

`var.(T)`类型断言失败时会返回`T`类型的“0值”，而不是变量原始值。

        var data interface{} = "great"
    
        if data, ok := data.(int); ok {
            fmt.Println("[is an int] value =>",data)
        } else {
            fmt.Println("[not an int] value =>",data)         //prints: [not an int] value => 0 (not "great")
        }
    
        if res, ok := data.(int); ok {
            fmt.Println("[is an int] value =>",res)
        } else {
            fmt.Println("[not an int] value =>",data)         //prints: [not an int] value => great (as expected)
        }

###### 16、阻塞的goroutine与资源泄漏

    func First(query string, replicas ...Search) Result {  
        c := make(chan Result)
        // 解决1：使用缓冲的channel： c := make(chan Result,len(replicas))
        searchReplica := func(i int) { c <- replicas[i](query) }
        // 解决2：使用select-default，防止阻塞
        // searchReplica := func(i int) { 
        //     select {
        //     case c <- replicas[i](query):
        //     default:
        //     }
        // }
        // 解决3：使用特殊的channel来中断原有工作
        // done := make(chan struct{})
        // defer close(done)
        // searchReplica := func(i int) { 
        //     select {
        //     case c <- replicas[i](query):
        //     case <- done:
        //     }
        // }
    
        for i := range replicas {
            go searchReplica(i)
        }
        return <-c
    }

### 三、高级

1、用值实例上调用接收者为指针的方法

对于可寻址(addressable)的值变量(而不是指针)，可以直接调用接受对象为指针类型的方法。  
换句话说，就不需要为可寻址值变量定义以接受对象为值类型的方法了。

但是，并不是所有变量都是可寻址的，像Map的元素就是不可寻址的。

    package main
    
    import "fmt"
    
    type data struct {  
        name string
    }
    
    func (p *data) print() {  
        fmt.Println("name:",p.name)
    }
    
    type printer interface {  
        print()
    }
    
    func main() {  
        d1 := data{"one"}
        d1.print() //ok
    
        // var in printer = data{"two"} //error
        var in printer = &data{"two"}
        in.print()
    
        m := map[string]data {"x":data{"three"}}
        //m["x"].print() //error
        d2 = m["x"]
        d2.print()      // ok
    }

2、更新map值的字段

如果map的值类型是结构体类型，那么不能更新从map中取出的结构体的字段值。  
但是对于结构体类型的slice却是可以的。

    package main
    
    type data struct {  
        name string
    }
    
    func main() {  
        m := map[string]data {"x":{"one"}}
        //m["x"].name = "two" //error
        r := m["x"]
        r.name = "two"
        m["x"] = r
        fmt.Println(s)       // prints: map[x:{two}]
    
        mp := map[string]*data {"x": {"one"}}
        mp["x"].name = "two" // ok
    
        s := []data{{"one"}}
        s[0].name = "two"    // ok
        fmt.Println(s)       // prints: [{two}]
    }

3、`nil`值的`interface{}`不等于`nil`

在golang中，nil只能赋值给指针、channel、func、interface、map或slice类型的变量。

`interface{}`表示任意类型，可以接收任意类型的值。`interface{}`变量在底是由类型和值两部分组成，表示为(T,V)，`interface{}`变量比较特殊，判断它是`nil`时，要求它的类型和值都是`nil`，即(nil, nil)。  
其它类型变量，只要值是nil，那么此变量就是`nil`（为什么？变量类型不是`nil`，那当然只能用值来判断了）

声明变量`interface{}`，它默认就是`nil`，底层类型与值表示是(nil, nil)。  
当任何类型T的变量值V给`interface{}`变量赋值时，`interface{}`变量的底层表示是(T, V)。只要T非nil，即使V是nil，`interface{}`变量也不是`nil`。

因此，`var a interface{}`、`var a interface{} = nil`、“

        var data *byte
        var in interface{}
    
        fmt.Println(data,data == nil) //prints: <nil> true
        fmt.Println(in,in == nil)     //prints: <nil> true
    
        in = data
        fmt.Println(in,in == nil)     //prints: <nil> false
        //'data' is 'nil', but 'in' is not 'nil'
    
        doit := func(arg int) interface{} {
            var result *struct{} = nil
            if(arg > 0) {
                result = &struct{}{}
            }
            return result
        }
        if res := doit(-1); res != nil {
            fmt.Println("good result:",res) //prints: good result: <nil>
            //'res' is not 'nil', but its value is 'nil'
        }
    
        doit = func(arg int) interface{} {
            var result *struct{} = nil
            if(arg > 0) {
                result = &struct{}{}
            } else {
                return nil //return an explicit 'nil'
            }
            return result
        }
    
        if res := doit(-1); res != nil {
            fmt.Println("good result:",res)
        } else {
            fmt.Println("bad result (res is nil)") //here as expected
        }

4、变量内存的分配

在C++中使用new操作符总是在heap上分配变量。Go编译器使用`new()`和`make()`分配内存的位置到底是stack还是heap，  
取决于变量的大小(size)和逃逸分析的结果(result of “escape analysis”)。这意味着Go语言中，返回本地变量的引用也不会有问题。

要想知道变量内存分配的位置，可以在`go build`、`go run`命令指定`-gcflags -m`即可：  
`go run -gcflags -m app.go`

5、GOMAXPROCS、Concurrency和Parallelism

Go 1.4及以下版本每个操作系统线程只使用一个执行上下文execution context)。这意味着每个时间片，只有一个goroutine执行。  
从Go 1.5开始可以设置执行上下文的数量为CUP内核数量`runtime.NumCPU()`，也可以通过`GOMAXPROCS`环境变量来设置，  
还可调用`runtime.GOMAXPROCS()`函数来设置。

注意，GOMAXPROCS并不代表Go运行时能够使用的CPU数量，它是一个小256的数值，可以设置比实际的CPU数量更大的数字。

        fmt.Println(runtime.GOMAXPROCS(-1)) //prints: X (1 on play.golang.org)
        fmt.Println(runtime.NumCPU())       //prints: X (1 on play.golang.org)
        runtime.GOMAXPROCS(20)
        fmt.Println(runtime.GOMAXPROCS(-1)) //prints: 20
        runtime.GOMAXPROCS(300)
        fmt.Println(runtime.GOMAXPROCS(-1)) //prints: 256

6、读写操作排序

Go可能会对一些操作排序，但它保证在goroutine的所有行为保持不变。  
但是，它无法保证在跨多个goroutine时的执行顺序。

    package main
    
    import (  
        "runtime"
        "time"
    )
    
    var _ = runtime.GOMAXPROCS(3)
    
    var a, b int
    
    func u1() {  
        a = 1
        b = 2
    }
    
    func u2() {  
        a = 3
        b = 4
    }
    
    func p() {  
        println(a)
        println(b)
    }
    
    func main() {  
        go u1()
        go u2()
        go p()
        time.Sleep(1 * time.Second)
        // 多次执行可显示以下以几种打印结果
        // 1   2
        // 3   4
        // 0   2 (奇怪吗？)
        // 0   0    
        // 1   4 (奇怪吗？)
    }

看到上面显示的02，14这样的值了吗？这没什么奇怪的。以02这样的输出结果，goroutine的执行应该是这样的

    -------------------------------------
       p函数    |   u1函数    |  u2函数  |
    -------------------------------------
    println(a)  |            |          |
                |   a = 1    |          |
                |   b = 2    |          |
    println(b)  |            |          |
                |            |   a = 3  |
                |            |   b = 4  |
    -------------------------------------
    (从上向下为时间执行顺序)

7、优先调度

有一些比较流氓的goroutine会阻止其它goroutine的执行。  
例如for循环可能就不允许调度器(scheduler)执行。

scheduler会在GC、go语句、阻塞channel的操作、阻塞系统调用、lock操作等语句执行之后立即执行。  
也可以显示地执行`runtime.Gosched()`（让出时间片）使scheduler执行调度工作。

    package main
    
    import (  
        "fmt"
        "runtime"
    )
    
    func main() {  
        done := false
        go func(){
            done = true
        }()
    
        for !done {
            // ... 
            //runtime.Gosched() // 让scheduler执行调度，让出执行时间片
        }
        fmt.Println("done!")
    }