# [ABC112A] Programming Education

## 题目描述

2020 年，AtCoder 公司年营业额超过了 10 亿日元，并开始涉足编程教育。
某天举行的测试中，1 岁的孩子需要编写一个输出 `Hello World` 的程序，2 岁的孩子需要编写一个输入整数 $A$、$B$ 并输出 $A+B$ 的程序。
高桥君正在参加这次测试，但他突然忘记了自己几岁。
于是，他决定先输入自己的年龄 $N$（$N$ 为 1 或 2），如果 $N=1$ 就输出 `Hello World`，如果 $N=2$ 就输入 $A$、$B$ 并输出 $A+B$ 的程序。
请你代替高桥君，编写这样一个程序。

## 说明/提示

### 限制

- $N$ 为 1 或 2。
- $A$ 是 1 到 9 之间的整数。
- $B$ 是 1 到 9 之间的整数。

### 样例解释 1

因为 $N=1$，所以高桥君 1 岁。因此输出 `Hello World`。

### 样例解释 2

因为 $N=2$，所以高桥君 2 岁。$A=3,\ B=5$，因此输出 $A+B=8$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1```

### 输出

```
Hello World```

## 样例 #2

### 输入

```
2
3
5```

### 输出

```
8```

# 题解

## 作者：Level_1024 (赞：2)

## **题面和思路都没什么好说的了，两位大佬讲的很好，我在此提供一种新的做法和思路**

   这就是：**三目运算符**
# 用法

举个例子：

```cpp
a>0 ? b=1 : b=0
```
这个的含义是：当a大于0时，b是1，否则是0

所以当问号前的语句为真时，执行冒号前的语句否则执行冒号后的语句

知道了这些，代码也就好些了，如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
   
  int n,a,b;
  cin>>n;
  n!=1 ? cin>>a>>b,cout<<a+b:cout<<"Hello World",exit(0)  ;
  return 0;
  //交了好多篇题解都没过，给次过吧，也许这将成为我的第一篇题解qwq****
}


```



---

## 作者：lzqy_ (赞：1)

### 首先给一下题面：
输入一个正整数 $n$，如果 $n$ = 1，输出$Hello World$，否则再输入两个正整数 $a$ 和 $b$ ，输出 $a+b$。

~~感觉有点水~~

这道题需要运用到的就是判断语句，以及输入输出语句。对于这道题，代码有两种写法：

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
   
  int n,a,b;
  cin>>n;
  if(n==1)//注：只有一行代码，可以不加括号
     cout<<"Hello World\n";
  else
  {
    cin>>a>>b;
    cout<<a+b<<endl;//岛国的题必须加换行
  }
  return 0;
}

```
这是我们一般的做法，当然也可以用以下的做法：

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n,a,b;
    cin>>n;
   if(n==1)
   {
     cout<<"Hello World\n";
     return 0;//直接结束程序
   }
    //注意：此处可以不加else
   cin>>a>>b;
   cout<<a+b<<endl;
    return 0;
}
```
这里在$if$中直接用 $return$ $0$ 结束程序，就不再需要$else$了。

两种做法虽然效率相同，但是都尝试一下，可以锻炼思维~


---

## 作者：Tear_stains (赞：0)

### 题意：
 
输入 $n$，如果 $n$ 等于 $1$ 输出 ```Hello World```，否则输入 $a$，输入 $b$，输出 $a+b$。
 
本题只需要判断 $n$ 是否等于 $1$ 即可，然后就可以愉快的输出答案了。

代码如下：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
int a, b;
signed main() {
	cin >> n;
	if(n == 1) {
		cout << "Hello World" << endl;
	} else {
		cin >> a >> b;
		cout << a + b << endl;
	}
	return 0;
}

```


---

## 作者：NOI_AK_dreeeam (赞：0)

给你一个 $n$ ，如果 $n = 1$ ，就输出 `Hello World` 。否则就再输入两个整数 $a$ 和 $b$ 并算出这两个数之和。

这是一道模拟题，主要运用到 `if` 和输入输出语句。

**_AC code_**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int main(){
    cin>>n;
    if(n==1) cout<<"Hello World\n";
    else{
        cin>>a>>b;
        cout<<a+b<<"\n";
    }
    return 0;
}
```


---

## 作者：wdgm4 (赞：0)

这种题很适用于初学者，~~说白了就是题很水~~。

初学者可以通过此题来练习 ```if``` 语句。

------------

### 题意

输入一个 $n$，如果 $n=1$，输出 ```Hello World```，否则输入 $a$ 与 $b$，输出 $a+b$。

### 做法

一个判断即可。

但这篇题解主要想讲的是快读，~~不然没有新意，审核可能都过不了~~。快读，顾名思义，就是比较快的读入，它用到了一个函数 ```getchar()```，```getchar()``` 函数会比 ```cin``` 和 ```scanf``` 快，但每次只能读入一个字符。所以我们在用快读时要循环读入。

#### 快读伪代码

```cpp
int read(){//这是一个函数
	char ch=getchar();
	int num=0,k=1;//num表示数,k表示正负
	while(!(ch<='9' and ch>='0')){ if(ch=='-') k=-1; ch=getchar(); }
	while(ch<='9' and ch>='0') { num*=10,num+=ch-'0',ch=getchar(); }
	return num*k;
}
```

还有一个更快的快读，要用到位运算，仅作扩展

```cpp
int read() {//更快的快读 
    int num=0; bool flag=1; char ch=getchar();
    while( !(ch>='0' and ch<='9') ) {if(ch=='-') flag=0; ch=getchar();}
    while( ch>='0' and ch<='9' ) {num=(num<<1)+(num<<3)+ch-'0'; ch=getchar();}
    if(flag) return num;
    return ~(num-1);
}
```

最后献上完整代码


```cpp
#include<bits/stdc++.h>
#define XD 114514

using namespace std;
int n,a,b;
int read(){//这是一个函数
	char ch=getchar();
	int num=0,k=1;//num表示数,k表示正负
	while(!(ch<='9' and ch>='0')){ if(ch=='-') k=-1; ch=getchar(); }
	while(ch<='9' and ch>='0') { num*=10,num+=ch-'0',ch=getchar(); }
	return num*k;
}
/*int read() {//更快的快读 
    int num=0; bool flag=1; char ch=getchar();
    while( !(ch>='0' and ch<='9') ) {if(ch=='-') flag=0; ch=getchar();}
    while( ch>='0' and ch<='9' ) {num=(num<<1)+(num<<3)+ch-'0'; ch=getchar();}
    if(flag) return num;
    return ~(num-1);
}*/
int main(){
	n=read();
	if(n==1) cout<<"Hello World\n";
	else{
		a=read(),b=read();
		cout<<a+b<<endl;
	}
	return 0;
}

```

#### 无快读代码

```cpp
#include<bits/stdc++.h>
#define XD 114514

using namespace std;
int n,a,b;
int main(){
	cin>>n;
	if(n==1) cout<<"Hello World";
	else{
		cin>>a>>b;
		cout<<a+b;
	}
	return 0;
}
```


---

## 作者：tbdsh (赞：0)

# 题意
[题目传送门](https://www.luogu.com.cn/problem/AT_abc112_a)

输入一个数 $n$，如果 $n = 1$，输出 `Hello World`，否则再输入两个正整数 $a$ 和 $b$（$0 \le a,b \le 9$）,然后输出这两个数的和。

# 分析
~~此题特别水~~，按题意敲代码即可。

# Code A
这是会 `CE` 的代码（原因：~~`AT` 编译器太厉害了~~）：
```cpp
#include<bits/stdc++.h>//CE原因A：C++ (Clang 10.0.0) 语言无法识别万能头文件。

using namespace std;
int n, a, b;
int main(){
  cin >> n;
  n == 1 ? cout << "Hello World" : cin >> a >> b;
  n == 2 ? cout << a + b : cout << "\n";//CE原因B：AT的两个编译器都无法识别单独存在的三目运算符。
  return 0;
}
```

# Code B
这是能 `AC` 的代码：
```cpp
#include<iostream>//被迫使用

using namespace std;
int n, a, b;
int main(){
  cin >> n;//输入 n。
  cout << (n == 1 ? "Hello World" : "\n");如果 n = 1，输出"Hello World"，否则输出一个换行符。
  if (n == 2){//如果 n = 2,
    cin >> a >> b;再输入两个数。
    cout << a + b;输出 a + b。
  }
  return 0;
}
```
# 总结
这道题就是把[B2001](https://www.luogu.com.cn/problem/B2001)、[B2002](https://www.luogu.com.cn/problem/B2002)和[P1001](https://www.luogu.com.cn/problem/P1001)结合了一下，只是AT的编译器是真的让人头疼。

---

## 作者：Yukinoshita_Yukino (赞：0)

水到没法再水的题。。

按题意模拟即可（如果$a$不为1继续输入$b$，$c$，并输出$b+c$。如果$a$为1输出“$Hello World$”），唯一坑点就是岛国题输出要换行！

代码：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
int a,b,c;
cin>>a;
if(a==1)/*判断语句，注意表示“等于”时要用两个等号*/{cout<<"Hello world"<<endl;return 0;}
else {cin>>b>>c;cout<<b+c<<endl;return 0;}
}
```


---

