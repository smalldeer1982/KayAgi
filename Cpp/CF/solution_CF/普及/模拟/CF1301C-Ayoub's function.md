# Ayoub's function

## 题目描述

Ayoub thinks that he is a very smart person, so he created a function $ f(s) $ , where $ s $ is a binary string (a string which contains only symbols "0" and "1"). The function $ f(s) $ is equal to the number of substrings in the string $ s $ that contains at least one symbol, that is equal to "1".

More formally, $ f(s) $ is equal to the number of pairs of integers $ (l, r) $ , such that $ 1 \leq l \leq r \leq |s| $ (where $ |s| $ is equal to the length of string $ s $ ), such that at least one of the symbols $ s_l, s_{l+1}, \ldots, s_r $ is equal to "1".

For example, if $ s =  $ "01010" then $ f(s) = 12 $ , because there are $ 12 $ such pairs $ (l, r) $ : $ (1, 2), (1, 3), (1, 4), (1, 5), (2, 2), (2, 3), (2, 4), (2, 5), (3, 4), (3, 5), (4, 4), (4, 5) $ .

Ayoub also thinks that he is smarter than Mahmoud so he gave him two integers $ n $ and $ m $ and asked him this problem. For all binary strings $ s $ of length $ n $ which contains exactly $ m $ symbols equal to "1", find the maximum value of $ f(s) $ .

Mahmoud couldn't solve the problem so he asked you for help. Can you help him?

## 说明/提示

In the first test case, there exists only $ 3 $ strings of length $ 3 $ , which has exactly $ 1 $ symbol, equal to "1". These strings are: $ s_1 =  $ "100", $ s_2 =  $ "010", $ s_3 =  $ "001". The values of $ f $ for them are: $ f(s_1) = 3, f(s_2) = 4, f(s_3) = 3 $ , so the maximum value is $ 4 $ and the answer is $ 4 $ .

In the second test case, the string $ s $ with the maximum value is "101".

In the third test case, the string $ s $ with the maximum value is "111".

In the fourth test case, the only string $ s $ of length $ 4 $ , which has exactly $ 0 $ symbols, equal to "1" is "0000" and the value of $ f $ for that string is $ 0 $ , so the answer is $ 0 $ .

In the fifth test case, the string $ s $ with the maximum value is "01010" and it is described as an example in the problem statement.

## 样例 #1

### 输入

```
5
3 1
3 2
3 3
4 0
5 2```

### 输出

```
4
5
6
0
12```

# 题解

## 作者：CSP_Sept (赞：3)

远古时期曾经给这题提交过翻译而且过了，今天随机跳题跳到这题，那就来做一下吧。

由于其他题解要么没有贪心证明，要么证明过于深奥，那我来补一篇有证明的题解吧 /kx

### Solution

首先注意到由于容斥原理，$f(s)=\text{tot}-g(s)$（$g(s)$ 是 $s$ 中 $(l,r)$ 的对数，满足 $s_l=s_{l+1}=\cdots=s_{r-1}=s_r=\tt0$）。

$\text{tot}$ 是总共 $(l,r)$ 的对数，显然值为 $\dfrac{n(n+1)}2$。

要最大化 $f(s)$，最小化 $g(s)$ 即可。

注意到把 $\tt0$ 分成 $m+1$ 段**均匀**分布在 $\tt1$ 的两边能最小化 $g(s)$，下面给出简要证明。

>**引理** 对于字符串 $s$，若只含有 2 段连续的 $\tt0$，长度分别为 $a,b$，则 $g(s)$ 最小当且仅当 $|a-b|$ 最小。
>
>**证明** 首先考虑 $(a+b)\mid2$ 的情况。
>
>- 当 $a=b$ 时，
$$
g(s_1)=\dfrac{a^2+b^2+a+b}2=b^2+b\text{ }\color{#03A89E}{(1)}
$$
>- 当 $a=b+2r(r>0)$ 时（$\tt0$ 的数量不变），
$$
g(s_2)=\dfrac{a^2+b^2+a+b}2=b^2+b+2br+2r^2+r\text{ }\color{#03A89E}{(2)}
$$
>
$$
{\color{#03A89E}{(2)}}-{\color{#03A89E}{(1)}}=2r^2+2br+r=r(2r+2b+1)\text{ }\color{#03A89E}{(3)}
$$
>
>注意到因为 $b,r>0$，所以 ${\color{#03A89E}{(3)}}>0$，即 $g(s_1)<g(s_2)$，$s_1$ 一定优于 $s_2$。
>
>$(a+b)\nmid2$ 的证明类似。
>
>运用数学归纳法，我们可以把结论扩展至 $m+1$ 段连续的 $\tt0$，这里不给出详细过程。

处理好余数即可，注意开 long long。

### Code

```cpp
#include <cstdio>

#define ll long long
using namespace std;
ll n, m;
void sol(){
	scanf("%lld%lld", &n, &m);
	ll tot, p, r;
	tot = n * (n + 1) / 2;
	p = (n - m) / (m + 1);
	r = (n - m) % (m + 1);
	printf("%lld\n", tot - p * (m + 1) * (p + 1) / 2 - (p + 1) * r);
}
int main(){
	int T;
	scanf("%d", &T);
	while(T--)
	    sol();
	return 0;
}
```

---

## 作者：Limit (赞：2)

本题结论题,所以就不放前置芝士了.

# 具体做法

先将最终的答案分为两部分,区间(开始于结束为止不同)和点,点的个数非常显然就是M,于是要计算区间的个数,可以发现如果直接计算有多少合法区间很麻烦,所以用总共的区间数$\frac{N*(N-1)}{2}$,减去没有的部分,可以发现这M个1可以将这个区间分成M+1段0(长度可以为0),两段之间有1的0之间不会相互影响,所以没有的部分就是每一段0中的区间个数之和,对于每一段0中的区间个数,设一个函数$f(x)=\frac{x*(x-1)}{2}$,可以发现这是一个二次函数,然后经过感谢理解,当每一段长度尽可能相等时最终的没有0的区间个数才是最少,所以可以计算出两个数$num1$和$num2$,$num1$为长度为$\lfloor \frac{N-M}{M+1} \rfloor+1$的连续0的段数,$num2$为长度为$\lfloor \frac{N-M}{M+1} \rfloor$的连续0的段数,然后将长度带入函数,再乘上相应的区间数,在总区间数中减去,就可以知道至少含有一个1的区间个数了,最终答案只要再加上一个M就好了.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
long long N,M;
int T;
void work()
{
	scanf("%lld%lld",&N,&M);
	long long len=(N-M)/(M+1);//计算出长度
	long long num1=(N-M-len*(M+1));//因为这个长度是向下取整的随意可能有剩余,而长度为len+1的个数自然就是剩余的0的个数了
	long long num2=M+1-num1;//因为总共有M+1段
	long long answer=N*(N-1)-len*(len+1)*num1-len*(len-1)*num2;//计算
	answer/=2;//前面没有除二
	printf("%lld\n",answer+M);//最后答案加上M之后输出
}
int main()
{
	scanf("%d",&T);
	REP(i,1,T)
	work();
	return 0;
}
```

---

## 作者：_Lazy_zhr_ (赞：0)

这题可以反向思考，只要连续的字符 `0` 在越短的基础上越少即可。

我们可以构造成 `0` 和 `1` 相间的形式，其中若整体 `0` 的个数大于 `1` 的个数，那么每段 `0` 可以由多个 `0` 组成；若整体 `1` 的个数大于 `0` 的个数，那么每段 `1` 可以由多个 `1` 组成。每段 `0` 的个数应该平均。

答案就是总区间数减去全是 `0` 的区间数。

代码如下：

```cpp
#define int long long
int n,m;
void solve(){
	int ans;
	cin>>n>>m;
	if(m==0){
		cout<<"0\n";
		return ;
	}
	ans=(n+1)*n/2;
	int a=n-m,b=m+1;
	int s=a/b,f=a%b;
	ans-=((s+1)*s/2*(b-f));
	ans-=((s+2)*(s+1)/2*f);
	cout<<ans<<"\n";
}
```

---

## 作者：wmrqwq (赞：0)

怎么没有二分的题解啊，写一篇。

# 题目链接

[CF1301C Ayoub's function](https://www.luogu.com.cn/problem/CF1301C)

# 解题思路

发现我们可以将问题转化成将 $n - m$ 个 $1$ 分成 $m$ 份，设第 $i$ 份的数字之和为 $sum_i$，则这样的分配方案的贡献为 $\frac{n \times (n+1)}{2} - \sum_{i=1}^{n} sum_i^2$。

容易发现要使得这样的贡献最小，你选择的不同的每份数字和的个数一定不超过 $2$。

因此你可以通过简单的数学来计算出这两种数字的取值，至于两种数字的数量可以直接二分。

单组测试时间复杂度 $O(\log m)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
ll _t_;
void _clear(){}
ll n,m;
ll ans;
void solve()
{
	ans=0;
	_clear();
	cin>>n>>m;
	if(m==0)
	{
		cout<<0<<endl;
		return ;
	}
	if(n==m)
	{
		cout<<(n+1)*n/2<<endl;
		return ;
	}
	ll last=n-m;
	ll num=last/(m+1);
//	cout<<"number:"<<num<<endl;
	ll L=0,R=m+1;
	while(L<R)
	{
		ll Mid=(L+R+1)/2;
		if(Mid*num<=last)
			L=Mid;
		else
			R=Mid-1;
	}
	ll _0=L,_1=last-L*num;
	_0-=_1;
//	cout<<L<<":"<<_0<<' '<<_1<<endl;
	cout<<(n+1)*n/2 - (_0*(num+1)*num/2 + _1*(num+2)*(num+1)/2)<<endl;
}
int main()
{
	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：Anita_Hailey (赞：0)

## T3 Ayoub's function

我们反向思维，他让我统计包含1的子段最多，我们考虑全是0的字段最少。

证明引理

下面数竞党的福利

$\forall a,b,n \in N^+$且 $a+b=n$，则必有 $a(a+1)+b(b+1) \ge \lceil \frac {n}{2} \rceil*\lceil \frac {n+1}{2} \rceil+\lfloor \frac {n}{2} \rfloor*\lfloor \frac {n+1}{2} \rfloor$


我们对n的奇偶性做讨论

再n为偶数时 ，原式变为
$$
a(a+1)+(n-a)(n-a+1) \ge \frac {n^2} {2}
$$
运用琴生不等式并同时构造辅助函数$f(x)=x(x+1)$,显然此函数是下凸的，于是原不等式变为
$$
\frac {f(a)+f(n-a)}{2} \ge f(\frac{n}{2})
$$
由琴生不等式，这几乎是显然的

再把合理的推广到多元

于是可以证毕。故而能贪心。于是这题就能为转化为 给你一些令 分成较平均几段，算总子段的个数，最后一减就行了

ps:因为和谐了

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <stack>
#include <map>
#include <queue>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
#define fake int
using namespace std;
int read(){
	int x=0;bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=1;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0'){
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return f?-x:x;
}
char Get(){
	char ch=getchar();
	while(ch==' '||ch=='\r'||ch=='\n') ch=getchar();
	return ch;
}
const ll Maxn=1e9+11;
ll t,n,m,ans;
int main(){
//	freopen("ret.in","r",stdin);
	t=read();
	while(t--){
		n=read();m=read();
		if(m==0){
			printf("0\n");
			continue;
		}
		ans=n*(n+1)/2;
		ll m1=n-m;//0 
		ll x=(m1)/(m+1);//һ�μ��� 
		ll q=x*(m+1);//���ڼ���
		ll sum=m1-q;
		ans-=x*(x+1)/2*(m+1-sum);
		ans-=(x+1)*(x+2)/2*(sum);
		printf("%lld\n",ans);
	}
	return 0;
}
```

## 

---

## 作者：123456zmy (赞：0)

题意：  
你需要构造一个长度为 $n$ 的含有 $m$ 个 $1$ 的01串，使得其中含有至少一个 $1$ 的子串的数量最多。输出最多的数量。
___
每个长度一定的串的子串数量是很好求的，于是可以统计有多少子串是不符合要求的，~~显然~~把连续的 $0$ 的数量尽可能平均时答案最优。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,ans,ans1,ansn1,ansn2;
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		ans=(n*(n+1)>>1);
		ans1=(n-m)/(m+1);
		ansn1=n-m-ans1*(m+1);
		ansn2=m+1-ansn1;
		swap(ansn1,ansn2);
		++ans1;
		if(ans1)ans-=ansn1*(ans1*(ans1-1)>>1);
		ans-=ansn2*(ans1*(ans1+1)>>1);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

