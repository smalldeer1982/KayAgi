# 题目信息

# Try and Catch

## 题目描述

Vasya 正在开发他的编程语言 VPL（Vasya 编程语言），目前他在实现异常处理系统。他认为异常处理的机制应该如下运作：

异常由 try-catch 块来处理。有两个操作符与异常块相关：

1. **try 操作符**：用于开启一个新的 try-catch 块。
2. **catch(<exception_type>, <message>) 操作符**：用于关闭最后一个尚未关闭的 try-catch 块。这个块仅在捕获到类型为 <exception_type> 的异常时被激活。当块被激活时，屏幕将显示 <message>。如果没有打开的 try-catch 块，则无法使用 catch 操作符。

异常仅在使用 throw 操作符时才会抛出。throw(<exception_type>) 操作符会创建指定类型的异常。

假如由于某个 throw 操作符，程序抛出了类型为 $a$ 的异常。那么将激活一个 try-catch 块，该块的 try 操作符在程序中位于该 throw 操作符之前，并且该块的 catch 操作符使用了异常类型 $a$，且它的位置在 throw 之后。如果存在多个这样的 try-catch 块，系统将激活 catch 操作符位置最靠前的块。如果没有满足条件的 try-catch 块被激活，屏幕将显示 "Unhandled Exception"。

为测试该系统，Vasya 编写了一个程序，其中只包含 try、catch 和 throw 操作符，并且每行最多包含一个操作符。程序中恰好有一个 throw 操作符。

你的任务是：根据给定的 VPL 语言程序，确定程序执行后屏幕将显示的消息。

## 说明/提示

在第一个例子中，有两个符合条件的 try-catch 块：try-catch(BE, "BE in line 3") 和 try-catch(AE, "AE somewhere")。异常类型是 AE，因此第二个块将被激活，因为其 catch 操作符的参数与异常类型匹配。

在第二个例子中，try-catch(AE, "AE in line 3") 和 try-catch(AE, "AE somewhere") 都符合条件，但第一个块的 catch 操作符位置较早，因此第一个块将被激活。

在第三个例子中，没有可被类型为 CE 的异常激活的块。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
8
try
    try
        throw ( AE ) 
    catch ( BE, &quot;BE in line 3&quot;)

    try
    catch(AE, &quot;AE in line 5&quot;) 
catch(AE,&quot;AE somewhere&quot;)
```

### 输出

```
AE somewhere
```

## 样例 #2

### 输入

```
8
try
    try
        throw ( AE ) 
    catch ( AE, &quot;AE in line 3&quot;)

    try
    catch(BE, &quot;BE in line 5&quot;) 
catch(AE,&quot;AE somewhere&quot;)
```

### 输出

```
AE in line 3
```

## 样例 #3

### 输入

```
8
try
    try
        throw ( CE ) 
    catch ( BE, &quot;BE in line 3&quot;)

    try
    catch(AE, &quot;AE in line 5&quot;) 
catch(AE,&quot;AE somewhere&quot;)
```

### 输出

```
Unhandled Exception
```

# AI分析结果

### 题目内容
# Try and Catch

## 题目描述
Vasya正在开发他的编程语言VPL（Vasya编程语言），目前他在实现异常处理系统。他认为异常处理的机制应该如下运作：

异常由try - catch块来处理。有两个操作符与异常块相关：
1. **try操作符**：用于开启一个新的try - catch块。
2. **catch(<exception_type>, <message>)操作符**：用于关闭最后一个尚未关闭的try - catch块。这个块仅在捕获到类型为<exception_type>的异常时被激活。当块被激活时，屏幕将显示<message>。如果没有打开的try - catch块，则无法使用catch操作符。

异常仅在使用throw操作符时才会抛出。throw(<exception_type>)操作符会创建指定类型的异常。

假如由于某个throw操作符，程序抛出了类型为$a$的异常。那么将激活一个try - catch块，该块的try操作符在程序中位于该throw操作符之前，并且该块的catch操作符使用了异常类型$a$，且它的位置在throw之后。如果存在多个这样的try - catch块，系统将激活catch操作符位置最靠前的块。如果没有满足条件的try - catch块被激活，屏幕将显示 "Unhandled Exception"。

为测试该系统，Vasya编写了一个程序，其中只包含try、catch和throw操作符，并且每行最多包含一个操作符。程序中恰好有一个throw操作符。

你的任务是：根据给定的VPL语言程序，确定程序执行后屏幕将显示的消息。

## 说明/提示
在第一个例子中，有两个符合条件的try - catch块：try - catch(BE, "BE in line 3")和try - catch(AE, "AE somewhere")。异常类型是AE，因此第二个块将被激活，因为其catch操作符的参数与异常类型匹配。

在第二个例子中，try - catch(AE, "AE in line 3")和try - catch(AE, "AE somewhere")都符合条件，但第一个块的catch操作符位置较早，因此第一个块将被激活。

在第三个例子中，没有可被类型为CE的异常激活的块。

 **本翻译由AI自动生成**

## 样例 #1
### 输入
```
8
try
    try
        throw ( AE ) 
    catch ( BE, "BE in line 3")

    try
    catch(AE, "AE in line 5") 
catch(AE,"AE somewhere")
```
### 输出
```
AE somewhere
```

## 样例 #2
### 输入
```
8
try
    try
        throw ( AE ) 
    catch ( AE, "AE in line 3")

    try
    catch(BE, "BE in line 5") 
catch(AE,"AE somewhere")
```
### 输出
```
AE in line 3
```

## 样例 #3
### 输入
```
8
try
    try
        throw ( CE ) 
    catch ( BE, "BE in line 3")

    try
    catch(AE, "AE in line 5") 
catch(AE,"AE somewhere")
```
### 输出
```
Unhandled Exception
```

### 算法分类
模拟

### 题解综合分析与结论
这两道题解思路相似，均利用栈来模拟try - catch块的逻辑。它们的核心在于记录try块的位置，在遇到throw时记录异常信息，在catch时判断是否匹配并处理。难点在于对try - catch块匹配规则的准确实现，即判断try在throw之前且catch在throw之后且异常类型匹配。

### 题解1
 - **星级**：4星
 - **关键亮点**：代码结构清晰，通过函数封装不同功能，如识别语句类型、提取参数、打印信息等，增强了代码可读性。
 - **个人心得**：无
```cpp
// 识别语句类型
int func_type(){
    for(int i=0;i<s.length();i++){
        if(s.substr(i,3)=="try")return 1;
        if(s.substr(i,5)=="catch")return 2;
        if(s.substr(i,5)=="throw")return 3;
    }
    return -1;
}
// 提取参数
string func_arg(bool is_last=0){
    string res="";
    int a=s.find("("),b=s.find(is_last?")":",");
    if(a+1&&b+1){
        for(int i=a+1;i<b;i++){
            if(s[i]!=' ')res+=s[i];
        }
    }
    return res;
}
// 打印信息
void func_print(){
    int a=s.find("\""),b=s.rfind("\"");
    if(a+1&&b+1){
        for(int i=a+1;i<b;i++){
            cout<<s[i];
        }
        cout<<endl;
    }
}
void solve(){
    cin>>n;
    getline(cin,s); 
    for(int i=1;i<=n;i++){
        getline(cin,s);
        int p=func_type();

        if(p==1){
            st.push(i);
        } else if(p==2) {
            int pp=st.top();
            st.pop();
            if(tp>pp && func_arg()==ts){
                func_print();
                return;
            }
        } else if(p==3) {
            ts = func_arg(1);
            tp = i;
        }
    }
    cout<<"Unhandled Exception"<<endl;
}
```
核心实现思想：`func_type`函数识别每行语句类型，`func_arg`提取异常类型或消息，`func_print`提取并打印消息。`solve`函数中，根据语句类型进行操作，try入栈，throw记录信息，catch判断匹配并处理。

### 题解2
 - **星级**：4星
 - **关键亮点**：Python代码简洁，通过字符串替换和`split`方法简洁地获取所需信息，逻辑清晰。
 - **个人心得**：无
```python
st = []
pos = -1
type = ''
for i in range(int(input())):
    s = input().replace('(', ' ').replace(')', ' ').replace(',', ' ')
    t = s.split()
    if len(t) == 0:
        continue
    if t[0] == 'try':
        st += i,
    if t[0] == 'throw':
        type = t[1]
        pos = i
    if t[0] == 'catch':
        if pos > st.pop() and type == t[1]:
            exit(print(s[s.find('"')+1:s.rfind('"')]))
print('Unhandled Exception')
```
核心实现思想：通过字符串替换和`split`获取每行信息，try将行号入栈，throw记录异常类型和位置，catch判断栈顶try位置和异常类型匹配后打印消息。

### 最优关键思路或技巧
利用栈来模拟try - catch块的嵌套结构，通过记录行号来确定try、catch和throw的先后顺序，准确实现匹配规则。同时，在处理输入时，通过字符串操作简洁地提取所需信息。

### 可拓展之处
此类题目属于模拟类型，类似的题目还可能涉及其他编程语言的特定语法模拟，如函数调用栈模拟、作用域模拟等。解题套路通常是根据给定规则，利用合适的数据结构（如栈、队列等）来模拟运行过程。

### 推荐洛谷题目
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举和组合实现对数字组合的筛选，与本题类似之处在于对特定条件的判断和处理。
 - [P1046 陶陶摘苹果（升级版）](https://www.luogu.com.cn/problem/P1046)：模拟陶陶摘苹果的过程，需要根据不同条件进行判断和操作，和本题模拟异常处理逻辑类似。
 - [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：通过栈来处理输入数字，和本题利用栈模拟try - catch块结构类似。 

---
处理用时：70.53秒