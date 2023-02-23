[如何启动vue项目 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/95011629)

- [(162条消息) npm install 你很明白吗_Never Yu的博客-CSDN博客_npm install](https://blog.csdn.net/csdn_yudong/article/details/83721870)

   

### 基础



不需要下载下来自己通过在<script>标签中引用具体的CDN地址即可

 <script src=" https://unpkg.com/vue@3/dist/vue.global.js">
[(162条消息) 使用CDN方法的方式进行Vue.js的安装_江夏、的博客-CSDN博客](https://blog.csdn.net/qq_41153943/article/details/97655373)





##### createapp + mount

`createApp`方法接收的是根组件对象作为参数，并返回了一个有`mount`方法的应用实例对象。



创建`app`应用实例: `ensureRenderer().createApp(...args)`

重写了`app.mount`方法。`document.querySelector`方法获取`HTMLElement`对象作为参数传入原`mount`方法。该部分会在`mount`段落详细讲解



- data: 变量的容器?
- computed: 在其中定义计算的函数
- watch: 用来响应数据的变化,然后以其变化前,变化后的值作为参数,完成相应的动作



![image-20221219101437989](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202302230934183.png)

挂载

![image-20221219101524008](note.assets/image-20221219101524008.png)

传入一个对象,

![image-20221219101652035](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202302230934015.png)

将script中vue的内容挂载到html页面中去

响应式, 数据来驱动视图更新

data(){} - 定义数据

属性 - template: 



![image-20221219102551359](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202302230934768.png)

插值表达式

![image-20221219103258914](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202302230934133.png)

​	



![image-20221219105448999](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202302230935076.png)



![image-20221219142331490](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202302230935261.png)

###### demo:cart







##### 内部指令



- v-model: 双向绑定 - 在程序中要获取用户及时输入在文本框中的信息(即使还没有提交),能够对此作出相应的反应
- v-bind: 感觉就是,我从script中拿出一些东西,填入到html中去
- v-on: 监听器,可以监听一些东西,比如鼠标点击button之后,作出一些动作
- 





###### v-model

[内置指令 | Vue.js (vuejs.org)](https://cn.vuejs.org/api/built-in-directives.html#v-model)

双向绑定 - 在程序中要获取用户及时输入的信息(即使还没有提交),还要显示出来



html内部模板

![image-20221219144230403](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202302230935947.png)







显示用户当前输入再文本框中的值

![image-20221219144655783](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202302230935901.png)

![image-20221219151245848](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202302230935257.png)

v-if不会去渲染,而v-if只是针对于css的切换,所以相对来说,在频繁切换flag的情况下v-show开销更小



```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .red {
            width: 100px;
            height: 100px;
            border: 2px solid blue;
            background: red;
        }

        .bg {
            background-color: yellow;
        }
    </style>
</head>

<body>
    <div id="app">
        <!-- v-model -->
        <p>input元素</p>
        <!-- v-model后面接的是data中的变量,而不是字符串,同时,如果对其改变,变量也会实时改变 -->
        <input type="text" v-model="inputMessage">
        <!-- 在标签中,用{{}}括起来的就是变量, 除此之外只能扩数字不能扩字符 -->
        <p>input的内容是:{{12}}{{inputMessage}}</p>
        <p>使用 watch 侦听</p>
        <!-- watch监听的是 inputmsg -->
        <input type="text" v-model="inputMsg">


        <!-- v-on -->
        <p>{{msg}}</p>
        <!-- 绑定到方法名,点击button触发监听事件,触发方法 -->
        <button v-on:click="showMsg">确认信息</button>
        <!-- 简写 v-on 指令 可以没有v-on,但是不可以没有click  -->
        <!-- button v-on= 变为 p@click -->
        <p @click="linkClick">有问题,就找API</p>

        <!-- v-bind 指令 -->
        <!-- 绑定一个属性 这里的title是p标签的title  -->
        <p v-bind:title="title">绑定一个属性</p>
        <!-- 简写 v-bind 指令 不用写 v-bind即可 -->
        <p :title="title">绑定一个属性 简写</p>
        <!-- 像msg那样直接使用是失效的 -->
        <p title={{title}}>绑定一个属性 简写</p>
        <!-- 动态属性绑定 也就是不知道绑定什么属性 这里的key是变量 -->
        <!-- a标签是超链接 -->
        <p><a :[key]="value">动态属性绑定</a></p>

        <!-- 绑定到class, 给这个div的class赋值为red -->
        <!-- 这里是条件判断, red是class名 isRed是变量名 -->
        <div :class="{red: isRed}"></div>
        <div :class="[classA, classB]"></div>
        <div :class="[classA, { classB: isB, classC: isC }]"></div>

        <!-- v-if和v-show的区别在于,v-if连html的dom都不会产生
            ,而show是在html中针对css的切换, 改变display:none来修改可见性
        v-show更适合作为频繁的切换   -->
        <!-- v-if -->
        <p v-if="flag">能不能看见我</p>
        <!-- v-show -->
        <p v-show="flag">能不能看见我</p>

        <!-- v-for -->
        <ul>
            <li v-for="item in items">
                {{item}}
            </li>
        </ul>

        <!-- v-for 遍历对象
            定义三个变量来接收遍历的 user
            键值对+索引
            这里并不是说user有三个属性所以这里有三个变量,三个属性表示遍历三次,每次都有一个键值对加一个index  -->
        <p v-for="(value, key , i) in user">
            {{key }}----{{value}}----{{i}}
        </p>
    </div>
    <!-- cdn方式使用vue -->
    <script src=" https://unpkg.com/vue@3/dist/vue.global.js">
    </script>
    <script>
        const { createApp } = Vue
        // 创建 Vue 对象
        const app = createApp({
            data() {
                return {
                    inputMessage: "使用 v-model",
                    inputMsg: "使用 watch 属性",
                    msg: "使用 v-on 指令",
                    title: "这是标题",
                    key: 'href',
                    value: "https://cn.vuejs.org/api/built-in-directives.html#v-bind",
                    isRed: true,
                    classA: 'red',
                    classB: 'bg',
                    classC: 'red',
                    flag: true,
                    items: [1, 2, 3, 4, 5],
                    user: {
                        id: 1,
                        name: "张三",
                        gender: "男"
                    }
                }
            },
            // 方法属性
            methods: {
                // 方法实现
                showMsg() {
                    this.msg = "确认 v-on 指令" // 在这里修改msg之后,在html中的渲染是实时更新的
                },
                linkClick() {
                    console.log("有问题,查找API")
                }
            },
            watch: {
                inputMsg(val, oldVal) {
                    console.log("新值:" + val, "旧值:" + oldVal)
                }
            }
        }).mount("#app")
    </script>
</body>

</html>
```



###### 事件处理 

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <div id="app">
        <!-- 停止冒泡 v-on .stop-->
        <div>
            <!-- 不会传递到父容器上去 - 没明白什么意思 -->
            <button @click.stop="stopHandler">阻止冒泡</button>
        </div>
        <!-- v-on .prevent -->
        <!-- 阻止默认行为:点击超链接会跳转网页 .prevent  -->
        <a href="https://cn.vuejs.org/api/built-in-directives.html#v-on" @click.prevent="linkClick">查看vue API </a>
        <form @submit.prevent>
            <button type="submit">提交</button>
        </form>

        <!-- 只触发一次事件处理 - 在后面加上once -->
        <a href="https://cn.vuejs.org/api/built-in-directives.html#v-on" @click.prevent.once="linkClick">查看vue API </a>
    </div>
    <script src="https://unpkg.com/vue@3/dist/vue.global.js"></script>
    <script>
        const { createApp } = Vue
        // 创建 Vue 对象
        const app = createApp({
            methods: {
                stopHandler() {
                    console.log("阻止冒泡")
                },
                linkClick() {
                    console.log("触发超链接的操作")
                }
            }

        }).mount("#app")
    </script>
</body>

</html>
```









##### 组件





###### 根组件,局部组件,全局组件

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <div id="app">
        <!-- 三个button-counter之间相互不干扰,独立
            这里的button-counter没有语法填充  -->
        <button-counter></button-counter>
        <button-counter></button-counter>
        <button-counter></button-counter>

        <!-- 组件名称当成标签去使用 -->
        <component-a></component-a>
    </div>

    <!-- 可以不写在script中,而是写在template标签中  -->
    <template id="temp-a">
        <div>
            <h2>局部组件A</h2>
        </div>
    </template>

    <script src="https://unpkg.com/vue@3/dist/vue.global.js"></script>
    <script>
        const { createApp } = Vue
        // 创建 Vue 对象

        // 组件的区别并不在于对象内容,内容之间没有区别
            // 如果直接传入 createapp 则为 root组件
            // 如果传递给component这个函数,那就是一个全局组件
            // 如果放进components这个属性里面,那就是一个局部组件

        // root 组件
        // 定义一个对象 
        // const RootComponent = {
        //     data(){
        //     },
        //     methods:{
        //     }
        // }
        // const app = createApp(RootComponent).mount("#app")



        // 局部组件：定义在 components 属性上
        const ComponentA = {
            // 写在template标签中,用标签id传入 template属性,而不是用字符串写入
            template: '#temp-a'
        }

        // 传入给createApp的内容,被配置为根组件, 根组件是我们渲染的起点
        // 当我们的应用要挂载到dom元素时,需要传递给app对象
        const app = createApp({
            // 根组件下有components属性,在这里装载局部组件
            components: {
                // 组件名称 : 组件对象
                "component-a": ComponentA
            }
        })

        // 全局组件
        // 如何使用全局组件?
            // 将 组件名称 当成 DOM 标签使用
        // 调用component这个函数 (组件名称, 对象内容)
        app.component('button-counter', {

            data() {
                return {    
                    count: 0
                }
            },
            // 模板属性 申明这个组件长什么样子
            // 这里没有用函数,而是直接上代码 count++
            template: `
            <button @click="count++">点击{{count}}</button>
            `
        })

        app.mount("#app")// 将app挂载到具体的应用对象上去
    </script>
</body>

</html>
```



###### 组件通信

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <div id="app"> 
        <!-- 在app标签中,通过对msg属性传值进行 父子间组件通信 -->
        <my-component msg="hello vue"></my-component>
        <!-- <my-component></my-component> -->
    </div>



    <script src="https://unpkg.com/vue@3/dist/vue.global.js"></script>
    <script>
        const { createApp } = Vue
        // 创建 Vue 对象
        // 组件通信 
            // 根组件向子组件发送信息 
                // 1.在父组件的 组件名称的标签中 中直接赋值
                // 2.要在子组件中的props[]中进行接收声明
            // 子组件向根组件传递数据
                // 1.在子组件的 emit method中传递事件
                // 2.要在子组件的emit[]中进行发送声明

        // 根组件
        const app = createApp({
            data() {
                return {
                    val: 1,
                    inputValue: '',
                    list: []
                }
            },
            methods: {
                handlerAddItem() {
                    // 填装 list
                    this.list.push(this.inputValue)
                    this.inputValue = ''
                }
            },
            // 注释掉,才会有全局组件作为子组件的效果
            // 点击按钮,生成数据
            // 模板属性,申明根组件的样子
                // v-model 绑定到input的inputvalue
                // v-on 监听button事件到方法 handler, 点击即触发handler
                // v-for 遍历list v-bind 将遍历到的item和index传递到子组件 my-course 中
            template: `
            <div>
                <input type="text" v-model="inputValue">
                <button v-on:click="handlerAddItem">增加课程</button>
                <ul>
                    <my-course v-for="(item, index) of list" :item="item"  :index="index"></my-course>
                </ul>
            </div>
            `
        })

        // 全局组件 (通过component函数添加的组件为全局组件)
        // app.component('my-component', {
        //     // 使用 props 接收 父组件 传递过来的数据
        //     data() {
        //         return {
        //             val: 2
        //         }
        //     }
        // })

        // 全局组件 (通过component函数添加的组件为全局组件)
        app.component('my-component', {
            // 使用 props 接收 父组件 传递过来的数据
            props: ['msg'], // 申明所需要接收的数据
            template: '<div>{{msg}}</div>', // 将接收到的msg进行输出
            data() {
                return {
                    val: 2
                }
            }
        })

        // 接收到从父组件root中传递过来的 index,item 
        app.component('my-course', {
            props: ['item', 'index'],
            // 在这里打印列表, 每一次传递出来,都是由一个新的子组件接收
            template: '<li>{{index}}----{{item}}</li>'
        })

        app.mount("#app")
    </script>
</body>

</html>
```





##### 组合式api



响应式数据























##### 项目

###### vite

[开始 | Vite 官方中文文档 (vitejs.dev)](https://cn.vitejs.dev/guide/)



创建一个项目

[(162条消息) 使用Vite快速创建vue3项目（超级简单，超级快速）_银子先生的博客-CSDN博客_vite创建vue3](https://blog.csdn.net/z1093541823/article/details/124348035)



导入别人的vite项目

[(162条消息) 如何打开别人的vue项目_idiot_MAN的博客-CSDN博客_如何打开别人的vue项目](https://blog.csdn.net/idiot_MAN/article/details/126962125)



[(162条消息) 解决vite不是内部或外部命令，也不是可运行的程序 或批处理文件。_小花皮猪的博客-CSDN博客_vite' 不是内部或外部命令,也不是可运行的程序](https://blog.csdn.net/weixin_46713508/article/details/128211201)









组件插件

elements plus



状态管理 pinia [Home | Pinia 中文文档 (web3doc.top)](https://pinia.web3doc.top/)