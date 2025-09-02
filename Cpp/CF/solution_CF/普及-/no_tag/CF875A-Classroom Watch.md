# Classroom Watch

## 题目描述

Eighth-grader Vova is on duty today in the class. After classes, he went into the office to wash the board, and found on it the number $ n $ . He asked what is this number and the teacher of mathematics Inna Petrovna answered Vova that $ n $ is the answer to the arithmetic task for first-graders. In the textbook, a certain positive integer $ x $ was given. The task was to add $ x $ to the sum of the digits of the number $ x $ written in decimal numeral system.

Since the number $ n $ on the board was small, Vova quickly guessed which $ x $ could be in the textbook. Now he wants to get a program which will search for arbitrary values of the number $ n $ for all suitable values of $ x $ or determine that such $ x $ does not exist. Write such a program for Vova.

## 说明/提示

In the first test case $ x=15 $ there is only one variant: $ 15+1+5=21 $ .

In the second test case there are no such $ x $ .

## 样例 #1

### 输入

```
21
```

### 输出

```
1
15
```

## 样例 #2

### 输入

```
20
```

### 输出

```
0
```

# 题解

## 作者：Frank_R_Z (赞：3)

###
啊哈，~~枚举都能过~~，这道题真的是简单代数问题，只不过循环开始要做一点手段，从n-90开始循环
```cpp
#include<bits/stdc++.h>
using namespace std;
bool ans(int x,int n)//自定义函数判断是否相同
{
	int k=x;
	while(x>0)
	{
		k+=x%10;
		x/=10;
	}
	if(k==n)return true;
	else return false;
}
int main()
{
	int n,k=0,a[1002],sum=0;
	cin>>n;
	for(int i=n-90;i<=n;i++)
	{
		if(ans(i,n))sum++,a[++k]=i;//引入自定义函数
	}
	cout<<sum<<endl;
	for(int i=1;i<=k;i++)
	{
		cout<<a[i]<<endl;//输出快乐
	}
	return 0;
}

```


---

## 作者：Arghariza (赞：2)

$n_{max}=10^9$

小学数学告诉我们如果一个数 $k$ 的第 $q$ 位为 $f_q(k)$ ，则 $k$ 的所有数字之和为：

$$f(k)=\sum\limits_{i=1}^{\mid k\mid}f_i(k)$$

显然让 $k+f(k)$ 最大的方案为 $\forall i \in  \{x\mid 1≤x≤|k|, x\in \mathbb{Z}\}, \ f_i(k)=9$ 

~~即个位数字都为$9$。~~

此时会发现 $|k|_{max}=9$ 

所以我们直接从 $n-|k|_{max}\cdot 9=n-81$ 开始枚举到 $n$ 即可。

```
#include <iostream>
#include <cstdio>
namespace mystd {
    #define maxl 1000100
    inline int read() {// 快读
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {// 快输
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

int n, cnt, ans[maxl];

int calc(int x) {// 数位和
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

int main() {
    n = read();
    for (int i = n - 81; i <= n; i++) {// 枚举
        if (i > 0 && calc(i) + i == n) {// 注意i到大于0
            ans[++cnt] = i;// 统计答案
        }
    }
    write(cnt);
    puts("");
    for (int i = 1; i <= cnt; i++) {
        write(ans[i]);
        puts("");
    }
    return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
这道题乍一看还挺简单的，只需要枚举 $1\sim n$ 即可，但是一看范围 $1 \leq n \leq 10^9$ 便放弃了，但是再想一想就会发现其实当小于 $n$ 时的最大值为 $9$ 个 $9$ 那么总和也最大只能为 $9 \times 9=81$，那这思路不就出来了吗？只需要从 $n-81\sim n$枚举即可。然后在循环中判断是否满足条件即可。
# AC代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
int n;
int cnt,res[100]; // 存答案
int main() {
	cin>>n;
	for(int i=max(n-81,1);i<=n;i++) { // 从n-81枚举到n 
		int sum=0,x=i; // 记录各位之和
		while(x) {
			sum+=x%10;
			x/=10;
		} 
		if(sum+i==n) res[++cnt]=i; // 判断是否满足条件，满足则加入答案 
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++) cout<<res[i]<<endl;
	return false ;
} 
```


---

## 作者：test_check (赞：1)

[$ \huge CF875A  \ Classroom \  Watch$](https://www.luogu.org/problem/CF875A)     
本题乍一看仿佛是一道数学题，（因为数据$1\leq n \leq 10^9$吗）但事实上，本题是一道**枚举**题，只是枚举的**范围**值得我们去思考。我们一步一步来解决这道问题

------------
$$First:\text{如何判断}x\text{是否为符合题意的数}$$
首先，我们需要开一个子函数$f()$,函数的类型应该为$bool$，因为要判断是否符合题意吗。那参数又有几个呢，当然是一个参数$x$，因为$x$为要判断的数吗。
所以，我们可以写出以下代码$:$   
```cpp
inline bool f(int x) 
{ 
    int ans = x ;  
    while(x)
	{
        ans += (x % 10) ;
        x /= 10 ;
    }     //将x分解，计算ans的值
    if(ans==n)  
    return 1;//如果符合题意，返回1
    return 0;  //不符合题意，返回0
}
```
以上代码中```inline```只是用来加快程序运行的，没有什么实际意义，不会用的$OIer$把```inline```去掉同样也能$AC$,只不过用时多了一点$(QAQ)$。

------------
$$Second:\text{枚举范围}$$
还是比较难想和难讲的（~~冒汗~~），   
$∵n$的取值范围为$1\leq n \leq 10^9$，所以，我们可以将$n$取$10^9-1$,(因为这样各位数的和就最大的吗），此时各位数的和为$81$,所以，枚举的范围就是$1\leq i \leq n-81$,那有些人就要有疑问了，如果$n$不到$81$怎么办呢？没事，当$i \leq 0$时是不可能符合条件的，所以多枚举$81$个数问题也不大。
代码如下：
```cpp
for(int i=n-81;i<=n;i++)
{
    //具体内容
}
```
------------
$$Last:\text{如何保存符合条件的}x$$
这个简单，用$queue,vector,set$,数组$……$都可以，我在这里就用$vector$($STL$大法好)了，十分简单，直接上代码：
```cpp
//int main之外
vector < int > s;  //定义

//int main之内
if(f(i)) s.push_back(i); //加入x
cout << s.size() << endl ; //输出个数
for(int i=0;i<s.size();i++)
cout << s[i] << endl ;   //输出vector中的元素
```
如果读者不会使用$vector$，那使用数组也可以$AC$

------------
$My \ complete \ code:$
```cpp
#include<bits/stdc++.h>
using namespace std ;
int n ;
vector < int > s;
inline int f(int x) 
{ 
    int ans = x ;
    while(x)
	{ 
        ans += (x % 10) ;
        x /= 10 ;
    }
    if(ans==n)
    return 1;
    return 0;
}
int main() {
    cin >> n ;
    for(int i=n-81;i<=n;i++)
	{
        if(f(i)) s.push_back(i);
    }
    cout << s.size() << endl ;
    for(int i=0;i<s.size();i++)
    cout << s[i] << endl ;
    return 0 ;
}
```

---

## 作者：AlicX (赞：1)

### 题意
对于一个数 $n$，求一个数 $x$，让 $x$ 加上它的各位数字之和等于 $n$，对于有多组解的情况，输出解的数量，再升序输出没一个满足条件的 $x$，没有就输出 $0$。

## 具体思路
本题乍一看很简单，有些同学就会想到从 $1 \sim n$ 暴力枚举，但显然是不行的，来看数据范围：$n \leq 10^9$，这样肯定会超时。现在我们开始想优化方法。既然是 $x$ 加上它的各位数字之和等于 $n$，是不是就意味着 $x \leq n \leq 10^9$，而就算是 $n$ 达到了极限（$10^9$），数字之和最多也只有：$81$，因为最多 $9$ 位数字，而每一位数字最多是 $9$，两者相乘即得 $81$，所以我们只用枚举 $n-81 \sim n$ 之间的数字，再判断这个数字符不符合条件即可。用一个数组记录答案，方便最后输出。

具体细节看代码

### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
int ans[10],cnt=0;
int work(int x){//计算这个数字的各个数位之和 
	int res=0;
	while(x) res+=x%10,x/=10;//累加 
	return res; 
}
signed main(){
	int n;
	cin>>n;
	for(int i=n-81;i<=n;i++) if(i+work(i)==n) ans[++cnt]=i;
	//从n-81开始枚举，只要这个数字加上它各个数位之和等于n，就加入数组 
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++) cout<<ans[i]<<endl;//升序输出 
	return 0;//Bye~
}
```

$$Thanks$$

---

## 作者：TheMatrix (赞：0)


# 题解 CF875A 【Classroom Watch】

## 思路：

首先能想到的是对于1e9的数据量， 
暴力解决问题必定会超时， 
那么我们就想到对于x， 
x的大小一定不会小于n减去n的每位之和， 
因为如果x比当前这个数还要小的话根本不可能构成这个数字， 这样就不用每次都从1跑到n地去找符合的数字个数了。  
### ans最多9位,每位最多为9,最大情况只需要从n-81到n遍历即可.

————————————————————————————————————
```cpp
#include<bits/stdc++.h>

using namespace std;

template <typename T>
  
inline void read(T &x)

{
    
    int t=0,f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) t=t*10+c-'0';
	x=t*f;
}

vector < int > a;

int main()
{
	
    int n, ans = 0;
	read(n);
	for(int i = max(1, n - 81); i <= n; i++)
	{
		int t = i;
		
		ans = i;
		while(t)
		{
			ans = ans + t % 10;
			t /= 10;
		}
		if(ans == n) a.push_back(i);
	}
	cout << a.size() << endl;
	for(int i = 0; i < a.size(); i++) cout << a[i] << endl;
	return 0;
}
```

第一次写题解， 还有许多不足之处， 我会继续努力的。


---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF875A)

## 蒟蒻语

有一个数 $n$，请找出若干个 $x$ 使 $x$ 加上 $x$ 各位上的数字和等于 $n$，输出个数和对应的 $x$。

## 蒟蒻思

明显是一道枚举题。

但我们不能~~傻傻的~~从 $1$ 枚举到 $n$，$n$ 最大 $10^9$，显然会爆。

所以我们要减少枚举范围。

我们不妨用 $sum$ 表示 $x$ 各位上的数字和，则有 $x=n-sum $。

而当 $n$ 为极限的 $10^9-1$ 时，数字和 $sum$ 也只有  $81$。

于是我们发现了一个~~惊天地泣鬼神的~~结论：$x$ 与 $n$ 最多差 $81$，比 $n-81$ 小的全部毙掉。

只要从 $n-81$ 枚举到 $n$ 就可以找到对应 $x$ 啦！

一些细节看代码吧。

## 蒟蒻解

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,cnt=0,b[1010];
	cin>>n;
	for(int i=n-81;i<=n;i++)
	{
		int t=i,sum=i;
		while(t)
		{
			sum+=t%10;
			t/=10;
		}
		if(sum==n)
		{
			b[cnt]=i;
			cnt++;
		}
	}
	cout<<cnt<<endl;
	for(int i=0;i<cnt;i++)
		cout<<b[i]<<endl;
	return 0;
} 
```




---

## 作者：As_Snow (赞：0)

### 思路

看到 $n$ 的范围 $1\le n \le 10^9$，感觉是一道数学题，但仔细一思考，我们会发现一个结论。

设一个答案 $x$ 的第 $i$ 为数字为 $sum_i(x)$，那么 $x$ 各位数之和为：
$$
sum(x) = \sum^{|x|}_{i=1}sum_i(x)
$$
因为必然有 $1\le sum(x)$ 且 $x + sum(x) = n \le 10^9$，所以 $1\le x \le 10^9-1$, 那么 $sum(x)_{\max} = 72 $ 即 $x=99999999$。
因此 $x$ 不会小于 $n-72$ 我们只用枚举 $n\!-\!72\sim n$ 的范围就可以了

### Code

```
#include<bits/stdc++.h>
using namespace std;
int n,ans[100],k;
int sum(int i){
	int res=0;
	while(i)res+=i%10,i/=10;
	return res;
}
signed main(){
	scanf("%d",&n);
	for(int i=max(0,n-81);i<=n;i++)
		if(i+sum(i)==n)ans[++k]=i;
	printf("%d\n",k);
	for(int i=1;i<=k;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Symbolize (赞：0)

# 思路
## 推导
虽说 $1 \leq n\leq 10^9$，但我们不用害怕，因为 $n$ 各个位数之和最大时也不过只有有 $9$ 个 $9$，和只有 $81$。所以我们只需要枚举从 $n-81$ 枚举到 $n$ 就行了。
## 第一步
输入。
## 第二步
从 $n - 81$ 循环遍历到 $n$。再判断对于 $n - 81$ 到 $n$ 中的每一个 $i$ 是否符合题意。若符合则将其存入数组。

条件：$i$ 的各个位数之和加上 $i$ 为 $n$。
## 第三步
输出数组长度以及满足条件的每一个数。
## Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e2+10;
using namespace std;
int n,l,ans[N];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}
bool check(int x)//判断函数
{ 
    int ans=x;
    while(x)//拆分每一位
	{
        ans+=(x%10);//加和
        x/=10;
    }
    if(ans==n) return 1;//满足条件
    return 0;//不满足条件
}
signed main()
{
	//第一步
	n=read();
    //第二步
	rep1(i,n-81,n) if(check(i)) ans[++l]=i;//循环遍历
    //第三步
	cout<<l<<endl;//输出个数
	rep1(i,1,l) cout<<ans[i]<<endl;//输出满足条件的每一个数
	return 0;
}
```

---

