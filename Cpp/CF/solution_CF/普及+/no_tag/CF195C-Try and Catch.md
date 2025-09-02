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

# 题解

## 作者：hellolin (赞：0)

## Codeforces Round 123 (Div. 2) - C - Try and Catch

[洛谷题面](https://www.luogu.com.cn/problem/CF195C) | [Codeforces 题面](https://codeforc.es/contest/195/problem/C) | [前往 blog.hellolin.cf 获取更好的阅读体验](https://blog.hellolin.cf/articles/cf4af696.html)

因为洛谷爬虫太逊了，**你需要注意到样例输入输出里面异常显示了 `&quot;`，请在测样例的时候把它们换成 `"`。**

这道题很有意思，题目让我们实现一个 `try-catch` 处理程序。给定的这个程序里面只会执行一次 `throw` 抛出异常，我们需要确定哪一个 `catch` 语句捕获到了这个异常（若没有输出 `Unhandled Exception`）。

首先，我们开一个栈存储每一个 `try` 语句的位置（以便在遇到 `catch` 时找到对应的 `try`），之后定义一个字符串和一个整数代表抛出异常的名称和位置。

``` cpp
stack<int> st;
string ts;
int tp;
```

读入每一行时，我们判断当前读入的语句是哪种类型：

- `try`：将当前行号压入栈。
- `throw`：更新一下抛出异常的名称和位置。
- `catch`：读取栈顶元素（对应的 `try` 语句的位置），若：
  - `try` 语句在抛出异常位置之前，且当前 `catch` 的名称与抛出的异常名称匹配：输出 `catch` 定义的输出内容，程序结束。
  - 否则，程序继续。

``` cpp
// 珍爱账号，请勿贺题
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,tp;
string s,ts;
stack<int>st;
// 1-try 2-catch 3-throw //
int func_type(){
    for(int i=0;i<s.length();i++){
        if(s.substr(i,3)=="try")return 1;
        if(s.substr(i,5)=="catch")return 2;
        if(s.substr(i,5)=="throw")return 3;
    }
    return -1;
}
string func_arg(bool is_last=0){
    string res="";
    // find 找元素，没找到返回 -1，找到返回位置，故判断是否找到时将返回值 +1 再转换为 bool 即可。
    int a=s.find("("),b=s.find(is_last?")":",");
    if(a+1&&b+1){
        for(int i=a+1;i<b;i++){
            if(s[i]!=' ')res+=s[i];
        }
    }
    return res;
}
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
    getline(cin,s); // 吃个换行先
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

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
```

---

## 作者：andyli (赞：0)

用一个栈存储 try-catch-block。对于 throw 语句记录位置和类型，在 catch 时判断类型是否相同以及 throw 语句在块中。  

对于每一行输入，将括号和逗号变为空白字符后 `split` 即可得到需要的信息。

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

---

