# [AGC018A] Getting Difference

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc018/tasks/agc018_a

箱に $ N $ 個のボールが入っていて、$ i $ 番目のボールには整数 $ A_i $ が書かれています。 すぬけ君は、次の操作を好きな回数だけ行うことができます。

- 箱から二つのボールを取り出し、その二つのボールに書かれている数の差の絶対値を書いた新しいボールと一緒に箱に戻す。

すぬけ君が、整数 $ K $ の書かれたボールが箱の中に入っている状態にできるかどうか判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

まず、$ 9 $ と書かれたボールと $ 4 $ と書かれたボールを取り出し、$ abs(9-4)=5 $ なので、$ 5 $ と書かれた新しいボールと一緒に箱に戻します。 次に、$ 3 $ と書かれたボールと $ 5 $ と書かれたボールを取り出し、$ abs(3-5)=2 $ なので、$ 2 $ と書かれた新しいボールと一緒に箱に戻します。 最後に、$ 9 $ と書かれたボールと $ 2 $ と書かれたボールを取り出し、$ abs(9-2)=7 $ なので、$ 7 $ と書かれた新しいボールと一緒に箱に戻します。 $ 7 $ と書かれたボールを箱に入れることができたので、この例の答えは `POSSIBLE` になります。

### Sample Explanation 2

どれだけ操作を行っても、$ 5 $ の書かれたボールを箱の中に入れることはできません。 よってこの例の答えは、`IMPOSSIBLE` になります。

### Sample Explanation 3

操作を行うまでもなく、箱の中には $ 11 $ の書かれたボールが入っています。 よってこの例の答えは、`POSSIBLE` になります。

## 样例 #1

### 输入

```
3 7
9 3 4```

### 输出

```
POSSIBLE```

## 样例 #2

### 输入

```
3 5
6 9 3```

### 输出

```
IMPOSSIBLE```

## 样例 #3

### 输入

```
4 11
11 3 7 15```

### 输出

```
POSSIBLE```

## 样例 #4

### 输入

```
5 12
10 2 8 6 4```

### 输出

```
IMPOSSIBLE```

# 题解

## 作者：DreamsChaser (赞：6)

$\mathcal{Lemma}$

> 如果 $\gcd(a,b)=d$，那么存在 $x,y\in Z$，使得 $ax+by=d$

这就是裴蜀定理，运用欧几里得辗转相除法可以轻松证明。

由此我们就大致有了一个做法：

设 $d=\gcd (a_1,a_2,\cdots a_n)$.

则由 $\mathcal{Lemma}$ ，若 $K$ 可以出现在集合 $A$ 中，必有：

$$K\equiv 0\pmod d$$

因为 $K$ 是通过不停地作差的绝对值作出来的，我们就有：

$$K\le \max(a_1,a_2\cdots a_n).$$

综上答案为：

$\begin{cases}\text{Possible}&K\equiv 0\pmod d,K\le \max(a_1,a_2\cdots a_n)\\\text{Impossible}&\text{otherwice}\end{cases}$

---

## 作者：CQ_Bab (赞：2)

# 题意
有 $n$ 个数和一个 $k$，问可否用 $k$ 个数相邻数的绝对值得到 $k$。

# 思路
这道题有一个很重要的理论，就是如果这 $n$ 个数的 $\gcd$ 为 $x$,那么他们减出来的数也一定是 $x$ 的倍数，例如样例六他们的公因数是 $3$ 所以它们的差也只有可能为 $3$ 的倍数，若 $n$ 个数的公因数为 $x$，那减出来的数也只有可能是 $x$ 的倍数，所以判断一下 $k$ 是不是 $x$ 的倍数即可切记还需要加一个特判那就是 $k$ 一定不能超过这 $n$ 个数的最大值且题目中保证了 $1\leq a[i]\leq100000$ ，没有负数减出来的数就一定小于原数。
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1001000],maxn,g;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		maxn=max(maxn,a[i]);// 求最大值 
		if(i==1) g=a[1]; // 将公因数初始化为a[1] 
		else g=__gcd(g,a[i]); // 求公因数 
	}
	if(k%g==0&&k<=maxn) puts("POSSIBLE"); // 特判 
	else puts("IMPOSSIBLE");
	return false;
}

```


---

## 作者：Ca1JH (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/AT2670)



------------

### 题目大意：
**有个$a[n]$的数组，可以将数组$a$中任意两个数的绝对值加入数组$a$,能否凑出$k$来**


------------

### 主要思路
**两个互质的数通过多次加减能够得到任意一个数，所以多个公约数为$x$的数只能拼成$x$为约数的数（跟楼下有些类似）**


------------
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[100005],maxn;
int main()
{
    
    cin>>n>>k>>a[0];
    maxn=a[0];//a[0]表示x 
    for(int i=1;i<n;i++)
    {
        cin>>a[i];
        a[0]=__gcd(a[0],a[i]);
        //求最大公因数 
        maxn=max(a[i],maxn);
    }
    if(k%a[0]==0&&k<=maxn) /*判断是否以a[0]为约数*/cout<<"POSSIBLE"<<endl;
    else cout<<"IMPOSSIBLE"<<endl;
    return 0;
}
```


---

## 作者：gi_A (赞：1)

### 题目大意：

初始集合中有 $n$ 个数，任取两个数 $a,b$ 将 $|a-b|$ 加入集合。问能否在集合中找到 $k$。

### 一、 简化题目

绝对值使得结果不好表示，考虑如何去掉它：

——把题目要求改为“将任意两个数相加减，去掉 $<0$ 的 和 $>\max(a_i)$ 的”。

如何保证正确性？

- 减法:很显然满足。
- 加法：想要得到 $a_1+a_2$ ( 一定有一个 $a_3>a_1+a_2$ ) 。那么有(括号代替绝对值)：

	- $(a_3-(a_1-(a_3-a_2)))=(a_3-(a_1+a_2-a_3))=a_1+a_2$


### 二、 寻找规律

由 **扩展欧几里得定理** 可知：当且仅当 $a*x+b*y=c*\gcd(a,b)$ 时 $x,y$ 有整数解。

因此我们只需选出一些数，使得他们的 $\gcd$ 最小（$\gcd$ 越小就越可能是 $k$ 的因子）。显然全部 $n$ 个数都选得到的 $\gcd$ 最小。

核心代码：

```cpp
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
int main()
{
	n=read();
	k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)d=gcd(a[i],d);
	if(k%d==0&&k<=a[n])cout<<"POSSIBLE";
	else cout<<"IMPOSSIBLE"; 
	return 0;
}
```


---

## 作者：赤霞QvQ (赞：1)

# 暴力出不来的，别想了……
乍一看到这道题，个人也以为是暴力把所有能拼出来的数放入一个数组，最后查找一遍。
## 但每个球有无数个，枚举真的很难呀！！！
于是，我就上网搜了一下，找到了一个神奇的定理：

## 两个互质的数通过多次加减能够得到任意一个数

那么这道题就好做多了。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,k,a,ak,h;
	cin>>n>>k>>a;
	h=a;
	for(int i=2;i<=n;i++)
	{
	    cin>>ak;
		a=__gcd(a,ak);       //它们的公约数
		h=max(ak,h);
	}
	if(k%a==0&&k<=h)        //因为多个公约数为n的数必定只能拼成有n这个约数的数
	{
	    cout<<"POSSIBLE"<<endl;
	}
	else
	{
	    cout<<"IMPOSSIBLE"<<endl;
	}
}
```

还算比较好理解……吧

---

## 作者：猜一猜我是谁 (赞：0)

# 题意简述
一个长度为 $n$ 的数组，问能否通过将数组里的数加减凑出 $k$。
# 思路
以样例 $6$ 为例。这几个数都是 $3$ 的倍数，可以发现，它们通过加减得出的数也都是 $3$ 的倍数。

那么思路就出来了。先计算所有数的最大公约数，再看 k 是不是这个最大公约数的倍数。需要注意的是，因为是通过减法，所以不可能凑出比 $\max(a[i])$ 更大的数。
# 代码
```cpp
#include<iostream>
using namespace std;
const int maxn=100005;
long long n,k,maxx,gcdd;
long long a[maxn];
long long gcd(long long n,long long m){//求最大公约数
    return m==0?n:gcd(m,n%m);
}
int main(){
    cin>>n>>k;
    maxx=-0x7f;
    for(long long i=1;i<=n;i++){//边输入边计算
        cin>>a[i];
        if(i==1) gcdd=a[1];
        else gcdd=gcd(gcdd,a[i]);
        maxx=max(maxx,a[i]);
    }
    if(k%gcdd==0&&k<=maxx) cout<<"POSSIBLE";
    else cout<<"IMPOSSIBLE";
}
```

---

