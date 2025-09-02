# オークション

## 题目描述

[problemUrl]: https://atcoder.jp/contests/yahoo-procon2018-qual/tasks/yahoo_procon2018_qual_b

矢風くんはオークションに参加しています。矢風くんの欲しい品物には、現在 $ X $ 円の値が付いています。

矢風くんはこの品物に、以下の条件を満たすような $ Y $ に対して、$ Y $ 円の値段をつけることができます。

- オークションでつける値段として適切である。すなわち、$ X+1\leq\ Y $ である。
- つける金額は細かすぎない。すなわち、$ Y $ の $ 10 $ 進表記の下 $ K $ 桁は全て $ 0 $ である。

矢風くんがつけることのできる最小の金額を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ X\ \leq\ 10^9 $
- $ 0\ \leq\ K\ \leq\ 9 $
- 入力はすべて整数である

### Sample Explanation 1

$ 2018 $ 円より大きく、下 $ 2 $ 桁が $ 0 $ であるような最小の金額は、$ 2100 $ 円です。

### Sample Explanation 2

$ X $ 円より大きい値段をつけなければならないことに注意してください。

## 样例 #1

### 输入

```
2018 2```

### 输出

```
2100```

## 样例 #2

### 输入

```
888 0```

### 输出

```
889```

## 样例 #3

### 输入

```
100 7```

### 输出

```
10000000```

# 题解

## 作者：cq_loves_Capoo (赞：7)

这蒟蒻刚开始的时候想着暴力AC这道题，结果= =，不出意外，没看数据范围的人都是吃亏的，可是看了数据范围之后，这个蒟蒻开始思考怎么样用 $O(1)$ 的方法做（终于会用脑子了），于是，遍搞出了这样的思路：   
   
首先，定义一个变量 $x$ ，它的值为 $10^{k}$ ，这样子可以方便计算qwq。    
   
接着，如果 $x$ 大于 $n$ ，则直接输出 $x$ 。   
   
否则，就输出 $(n/x+1)*x$ 。   
   
贴代码（注意AT的题目要换行）：    
   
```
#include<bits/stdc++.h>//懒人专用（考场建议别用）
using namespace std;
int n,k,ans;
signed main()
{
	cin>>n>>k; 
	x=pow(10,k);//rt，10的k次方
	if(x>n) cout<<x<<endl;//输出x
	else cout<<(n/x+1)*x<<endl;//输出(n/x+1)*x
}

```  
我发现这题好像不用换行qwq

---

## 作者：lsyx0918 (赞：3)

翻译：输入X和K

输出一个数Y，要求：

1.Y>X

2.Y的末尾K位必须都是0

3.同时Y尽量小

看着这些要求后，突然发现，**普及的提好简单！！**

现在正在发射题解光波：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
//定义全局变量
double a,b;
long long ans;
int main()//主函数
{
    cin>>a>>b;
    a++;//Y>X，所以a++
    ans=ceil(a/pow(10,b))*pow(10,b);//用公式就OK了
    cout<<ans<<endl;//输出
    return 0;//拜拜了您嘞
}
```
最后，提醒一句：

**AT不换行，暴零两行泪！

---

## 作者：yyy爱编程 (赞：2)

最近在刷$AT$的题，看到~~这么好~~的题目，~~只能来水一发~~了。

$emmm,$读题。

读完题后我们发现，这可以用穷举直接做嘛!但是穷举很难并且这个数据范围......果断决定推个公式好吧。

末尾$k$位都是0的话呢，那么先乘上一个$10^k$。

再去看，$y>x$,从$x+1$开始处理呗。

但是肯定没有那么简单。

$x+1$用到哪里呢，用它来乘肯定错,所以，我想到了先除后乘的好办法。先除，好的，除数是什么？肯定是$10^k$。
好的，公式基本上出来了，$\frac{(x+1)}{pow(10,k)}*pow(10,k)$。正当我雄赳赳气昂昂地打开$ide$输入介条公式然后运行打上第一个样例时，竟然显示2019,没搞错吧?还是公式推错了？经过了一番思索后，我想到了：在$\frac{(x+1)}{pow(10,k)}$中除到不是整数怎么办?应该加$ceil()$还是$floor()$?然后就尝试呗。

$ceil()$是2100，对了。

再看看floor(),变成了2000。那么就是ceil了，

数学化是这样的:$\boxed{\lceil \frac{(x+1)}{(10^k)} \rceil \times 10^k}$。

$C++$化是这样的:$\boxed{ceil((x+1)/pow(10,k))*pow(10,k)}$。

然后就是快乐的代码时间:

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x,k;
	cin>>x>>k;
	cout<<ceil((x+1)/pow(10,k))*pow(10,k);
}
```

写完一看，我不就是写了个@$RioBlu $的本题第一篇题解的加长版吗。

~~肯定过不了的~~


---

## 作者：mwhxiaopy (赞：2)

本题很简单。

下面我将介绍一种比较暴力的做法。

由于这道题要求输出后面有$k$个$0$，所以使用模的做法。~~（门外汉的粉丝：又是模）~~

首先，构造一个$10$的$k$次方$k1$；

其次，用$k1$去模$x$，得到$y$;（x的尾数）

然后，用$x$-$y$然后加$k1$，就是最后的值了。（去尾再加上$1后k个0$。）

源代码：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
int y,k,x,k1;
cin>>x>>k;
k1=1;
for(int i=1;i<=k;i++)k1=10*k1;
y=x%k1;
y=x-y;
y+=k1;
cout<<y;}
```

---

## 作者：RioBlu (赞：2)

翻译：输入X和K

输出一个数Y，要求：

* Y>X 
* Y的末尾K位必须都是0
* 同时Y尽量小
___
```
#include<bits/stdc++.h>
using namespace std;
double a,b;
long long ans;
int main()
{
    cin>>a>>b;
    a++;//Y>X，所以a++
	ans=ceil(a/pow(10,b))*pow(10,b);//用公式就OK了
	cout<<ans<<endl;//输出
}
```

---

## 作者：Zhouyc2009 (赞：2)

输入两个数 $n$ 和 $k$ ,题目要求输出一个 $ans$ ，使其符合以下三个条件：

- $ans>n$ 。
- $ans$ 的末尾 $k$ 位都是 $0$ 。
- $ans$ 最小。

由题意可知：

我们先求出 $ans$ 末尾 $k$ 位为 $0$ 是多少，如果比 $n$ 打了就直接输出，不然就用公式 $ (n/ans+1) \times ans$ 求出最小符合题意的 $ans$ 。

CODE：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int main()
{
	cin>>n>>m; 
	k=pow(10,m);//求出ans k位为0的最小数。
	if(k>n) cout<<k;//若大于了n直接输出即可。
	    else cout<<(n/k+1)*k;//否则公式输出。
}
```


---

## 作者：Gmt丶FFF (赞：1)

## 此题理解了题意以后就非常的简单了。

总共分三种情况，1.k>x-1的位数。  2.k=x-1的位数。   3.k<x-1的位数，再分别分析即可。

第一种情况，直接1后面补k个0。

第二种情况，最高位加1，后面补0。

第三种情况，除0位最高位加1，后面补0。

然后就是代码了。


```
#include<iostream>
#define ll long long
using namespace std;
ll pow(ll,ll);
ll wei(ll);
ll qu(ll,ll);
int main()
{
	ll x,k;
	cin>>x>>k;
	if(wei(x)<=k)cout<<(ll)pow(10,k);
	if(wei(x)-1==k)cout<<(ll)(qu(x,wei(x))+1)*pow(10,k);
	if(wei(x)-1>k)cout<<(ll)((x+pow(10,k))/pow(10,k))*pow(10,k);
	cout<<endl;
	return 0;
}
ll pow(ll a,ll b)
{
	if(b==0)return 1;
	b--;
	ll x=a;
	while(b--)a*=x;
	return a;
}
ll wei(ll a)
{
	ll k=1;
	while(a/=10)k++;
	return k;
}
ll qu(ll a,ll b)
{
	b--;
	while(b--)a/=10;
	return a%10;
}

```
当然要开long long，否则就只能见祖宗了。

做完代码，我们可以发现，第二种情况其实跟第三种情况相似，最后发现他们是一样的，所以我们可以合并这两种情况。

```
#include<iostream>
#define ll long long
using namespace std;
ll pow(ll,ll);
ll wei(ll);
ll qu(ll,ll);
int main()
{
	ll x,k;
	cin>>x>>k;
	if(wei(x)<=k)cout<<(ll)pow(10,k);
	else cout<<(ll)((x+pow(10,k))/pow(10,k))*pow(10,k);
	cout<<endl;
	return 0;
}
ll pow(ll a,ll b)
{
	if(b==0)return 1;
	b--;
	ll x=a;
	while(b--)a*=x;
	return a;
}
ll wei(ll a)
{
	ll k=1;
	while(a/=10)k++;
	return k;
}
ll qu(ll a,ll b)
{
	b--;
	while(b--)a/=10;
	return a%10;
}
```
最后再思考一下，在最高位加1，然后补0，发现第一种情况也可以进行合并。最后只剩下第三种情况的代码。

```
#include<iostream>
#define ll long long
using namespace std;
ll pow(ll,ll);
ll wei(ll);
ll qu(ll,ll);
int main()
{
	ll x,k;
	cin>>x>>k;
	cout<<(ll)((x+pow(10,k))/pow(10,k))*pow(10,k)<<endl;
	return 0;
}
ll pow(ll a,ll b)
{
	if(b==0)return 1;
	b--;
	ll x=a;
	while(b--)a*=x;
	return a;
}
ll wei(ll a)
{
	ll k=1;
	while(a/=10)k++;
	return k;
}
ll qu(ll a,ll b)
{
	b--;
	while(b--)a/=10;
	return a%10;
}
```
记住，pow这个函数是int的，不支持long long，有可能会丢失数据。所有尽量自己写一个函数。

 然后此题就结束了，此题坑只有一点，必须加
 
#  ENDL ！！！！！

---

## 作者：wssdl (赞：0)

## 前言

想暴力者，可以看看数据君： $1\le X \le 10^9,0\le K\le 9$ ，所以请靠边站，否则直接 T 飞。

## 思路

我们知道不能暴力枚举每个数，但是我们换个角度思考一下，不暴力枚举每个数，可以枚举数位啊，再看一看数据，我们发现，如果枚举每个数位，最多只到 $9$ 位，时间肯定是允许的，所以我们先把 $X$ 拆分，但是得到的是从个位开始，一直到最高位的数字，换句话说，它是原输入的倒序，所以我们拆分时用一个数组把答案记好，然后在倒序排列，这样就是正序了，我们知道，题目要求我们后 $K$ 位都要是 $0$ 那我们就把这些位都预留出来，直接枚举总位数减去后 $K$ 位所得到的位数，但是我们是倒序循环的，所以我们在循环时再加一个变脸限制，在循环时，我们把不用变为 $0$ 的位数上的数存到 $sum$ 变量中，实现就是：

```cpp
sum = sum * 10 + a[i];
```

由于我们得到的答案必须要比 $X$ 大，所以我们输出时需要加个一，然后我们再把 $K$ 位 $0$ 补上。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 15;  //由于是在搞数位，所以开到10以上就好了
int x, k;
int cnt;
int sum;
int a[N];
int main() {
  cin >> x >> k;
  while (x > 0) {
    a[++cnt] = x % 10;  //取出每位数
    x /= 10;
  }
  int tmp = cnt - k;
  for (int i = cnt, s = 1; i >= 1 && s <= tmp; i--, s++) {  //把除了后k位的数都存入sum变量中
    sum = sum * 10 + a[i];
  }
  cout << sum + 1;                //必须要大写，所以+1
  for (int i = 1; i <= k; i++) {  //补上后k位
    cout << "0";
  }
  return 0;
}
```


---

## 作者：Franka (赞：0)

### **题目**
输入$X$和$K$

输出一个数$Y$(当然这个数没有前导$0$)，要求：

* $Y>X$
* $Y$的末尾K位必须都是$0$
* 同时$Y$尽量小

### **思路**
看样例
#### 输入
`2018 2`
#### 输出
`2100`

我们模拟一下这个转换的过程：

1. 将$1$~$2$位的数字拷出来，加一，将这个数存到变量$x$里
2. 在$x$的末尾补$0$
3. 输出$x$

### **代码**
```pascal
var x,k,i:longint;q,w:string;//定义
begin
 readln(x,k);//读入x和k
 str(x,q);w:=copy(q,1,length(q)-k);//拷贝出1~位数-k的数
 val(w,x);inc(x);str(x,w);//加1
 for i:=1 to k do w:=w+'0';//补0
 writeln(w);//输出
end.
```


---

## 作者：Achiles (赞：0)

# 题解 AT3699

[原题地址](https://www.luogu.org/problemnew/show/AT3699)

由于此题主要操作与难点在于：“Y的末尾K位必须都是0”，我就想到了用字符串处理

字符串还有个好处，不太需要在意题目的数据范围，反正读入进来都被分解成一位一位的了

我主要是这么想的：把后面的k位从原数（字符串）中剥离开，然后将前面的字符串转化成数字，加上1后输出，再输出k个0即可

代码如下，有些注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,a=1;//由于Y>X，故a要先赋初始值1
string x,y;
int power(int m)//此函数的作用相当于10^m
{
    long long ans=1;
    for(int i=0;i<m;i++) ans*=10;
    return ans;
}
int main()
{
    cin>>x>>k;//输入
    for(int i=x.length()-k-1;i>=0;i--) a+=(x[i]-'0')*power(x.length()-k-1-i);//末尾以上全部换成0，注意是字符0，并将转换后的结果放入a中
    cout<<a;//输出a
    for(int i=x.length()-1;i>x.length()-k-1;i--) cout<<"0";//输出末k位的0
    cout<<endl;//岛国的题一定要空行！！！
    return 0;
}


```
（应该看得懂吧qwq）

中间有一些关于数组下标边界是否要-1及判断是用>还是>=的问题，这些要靠手算，只是些小细节但至关重要！

其实做到最后发现我的解法和字符串关联也不是很大啊qwwq

（勿抄）

---

