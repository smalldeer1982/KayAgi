# 「WWOI R1」WsW 的笔

## 题目背景

WsW 准备送几支笔给 bln。

## 题目描述

WsW 有 $b-a+1$ 支笔，每支笔的编号为 $a\sim b$ 的正整数，且笔的编号互不相同。他决定送若干支笔给 bln，并将剩余的笔留给自己。   

当所有的笔都满足以下条件时，WsW 认为这种送笔方案是**优秀送笔方案**：  
* 如果将编号为 $x$ 的笔送给 bln，那么必须将编号为 $x/k$ 的笔留给自己。  
* 如果将编号为 $x$ 的笔留给自己，那么必须将编号为 $x/k$ 的笔送给 bln。  

	当然，这些条件的前提是 WsW 有编号为 $x/k$ 的笔。

WsW 认为，如果某个编号的笔在一种方案中被送出，在另一种方案中被留下，则这两种送笔方案是不同的。

现在所有的笔都已经被 WsW 编完号了，WsW 想知道一共有多少种**不同的优秀送笔方案**。  

由于最后的结果可能很大，你只需要告诉 WsW 总方案数对 $10^9+7$ 取模后的值。

## 说明/提示

### 【样例 $1$ 解释】

|方案|送出编号|留下编号|
|:-:|:-:|:-:|
|$1$|$2$|无|
|$2$|无|$2$|

共 $2$ 种不同的优秀送笔方案。

### 【样例 $2$ 解释】

|方案|送出编号|留下编号|
|:-:|:-:|:-:|
|$1$|$1$|$2,3,4$|
|$2$|$1,2$|$3,4$|
|$3$|$1,4$|$2,3$|
|$4$|$1,2,4$|$3$|
|$5$|$3$|$1,2,4$|
|$6$|$2,3$|$1,4$|
|$7$|$3,4$|$1,2$|
|$8$|$2,3,4$|$1$|

共 $8$ 种不同的优秀送笔方案。

### 【数据范围】
**本题采用捆绑测试**。

对于所有测试数据，保证 $1\le T\le 5$，$1\le a\le b\le 10^{18}$，$2\le k\le10^{5}$。

| 子任务编号 | $a,b\leq$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: |
| $1$ | $20$ | 无 | $10$ |
| $2$ | $10^3$ | 无 | $10$ |
| $3$ | $10^5$ | B | $5$ |
| $4$ | ^ | 无 | $10$ |
| $5$ | $7\times10^6$ | A | $5$ |
| $6$ | ^ | B | $5$ |
| $7$ | ^ | 无 | $15$ |
| $8$ | $10^{18}$ | A | $5$ |
| $9$ | ^ | B | $10$ |
| $10$ | ^ | 无 | $25$ |

* 特殊性质 A：$a\times k>b$。  

* 特殊性质 B：$k=2$。  


## 样例 #1

### 输入

```
1
2
2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
1
3
1 4```

### 输出

```
8```

## 样例 #3

### 输入

```
1
114
514 1919810```

### 输出

```
532406817```

# 题解

## 作者：WsW_ (赞：3)

这里是出题人题解。  

---
### 思路
为了方便表达，令 $n=b-a+1$。  
如果编号为 $i$ 的笔送给谁已经确定，那么编号为 $i\times k^t,t\in \mathbb{N}$ 的笔送给谁就都确定了。我们把这些互相依赖的笔分为一组，如果一组中某一支笔送给谁确定了，一组中所有的笔送给谁就都确定了。  
组和组之间互不影响，假设分出了 $m$ 组，答案就是 $2^m$。  
如何求出有多少组呢？可以用每一组中最小的编号来指代这一组。可以发现，满足 $i\bmod k\ne0$ 或 $i<a\times k$ 的编号 $i$ 一定是某一组中最小的编号；这两个条件都不满足的编号 $i$，一定不是某一组中最小的编号。  

所以只需要求出满足这两个条件的 $i$ 的数量，再容斥去掉重复的即可。  

对于特殊性质 A，上面的容斥会出错，需要特判。  

特判时如果直接 $a\times k>b$ 会爆 `unsigned long long`，要把式子转化成 $a>b/k$。

最后用快速幂计算方案数。  

时间复杂度为 $O(T\log n)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull mod=1e9+7;
ull p(ull x){
    ull ans=1,t=2;
    while(x){
        if(x&1)(ans*=t)%=mod;
        (t*=t)%=mod;
        x>>=1;
    }
    return ans;
}
ull g(ull l,ull r,ull k){
	return (r-r/k)-(l-l/k);
}
void work(){
	ull k,a,b; cin>>k>>a>>b;
	if(b/k<a)cout<<p(b-a+1)<<'\n';
	else cout<<p(g(a,b,k)-g(a,a*k-1,k)+a*(k-1))<<'\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1; cin>>T;
	while(T--)work();
	return 0;
}
```

---

## 作者：xiaozhao_ (赞：2)

### 前言
非常好的数学题，使我的大脑飞速旋转。

---
### 分析
由题可知，对于编号为 $x$ 的笔来说，编号为 $x / k$ 的笔的状态一定和它相反，编号为 $x / k^2$ 的笔的状态一定和它相同。因此，一个在 $a \sim b$ 中以编号 $x$ 为开头的子链只有两种状态，每个 $a \sim b$ 中的子链都只有两种状态。综上所述，**只要求出 $a \sim b$ 中的子链数 $n$ 就可以通过 $2^n$ 求出方案数**。

但难点就在于如何求出 $a\sim b$ 中的子链数 $n$？

我们可以将 $a\sim b$ 中的子链数 $n$ 分为两种情况：

+ 第一种：$x \bmod k \ne 0$。**这种 $x$ 由于 $x / k$ 不为正整数导致该子链中仅仅只有 $x$ 本身**。这种情况比较好想，简单地上限减去下限即可，写成算式就是：
$$Case 1 = (b - a + 1) - [b / k - (a - 1)/ k]$$
::::info[算式详解]
$b - a + 1$ 即 $a \sim b$ 编号数，$b / k$ 即 $b$ 中可以整除 $k$ 编号数，但因为包含了 $a - 1$ 中可以整除 $k$ 编号数，因此要减去 $(a - 1)/ k$。
::::
+ 第二种：$x \bmod k = 0$，这种 $x$ 所在的子链有多少个数都有可能。但容易发现，对于每一个这种子链都有一个根元素 $m$（$x$ 不断除以 $k$ 直到小于 $a$ 或除不了），**统计 $m$ 的数量相当于统计了该情况子链数**。同第一种情况在上限减去下限的角度去思考，只要求出上限和下限就能求出 $m$ 的数量。算式如下：
  $$Case2 = \min( a - 1,\lfloor b / k \rfloor) - \lceil a / k \rceil + 1$$
::::info[算式详解]{open}
该情况中的 $m$ **必须**满足以下两个条件：
1. $m$ 在 $1 \sim (a-1)$ 范围内（即 $m \le a-1$）。
2. $m$ 对应的 $x = m \times k$ 必须在 $a \sim b$ 范围内（即 $x = m \times k \ge a$ 且 $x = m \times k \le b$）。

上限：由 $x = m \times k \le b$ 可得 $m \le \lfloor b / k \rfloor$（向下取整保证 $m$ 是不大于 $b / k$ 的最大整数），由条件一可得 $m \le a-1$，联立以上两个式子可得 $m \le \min( a - 1,\lfloor b / k \rfloor)$。

下限：由 $x = m \times k \ge a$ 可得 $m \ge \lceil a / k \rceil$（向上取整确保了 $m$ 是满足 $m \times k \ge a$ 的最小整数）。

综上所述：$\lceil a / k \rceil \le m \le \min( a - 1,\lfloor b / k \rfloor)$。
::::

最后就是计算 $2^n$，直接使用快速幂就行了。

---
### 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int p=1e9+7;
ll fpow(ll a,ll b) {
    ll res=1;
    a%=p;
    while(b>0) {
        if(b&1) res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
} //快速幂。
int t;
ll k,a,b;
int main() {
    cin>>t;
    while(t--){
    	scanf("%lld%lld%lld",&k,&a,&b);
    	ll c1=(b-a+1)-(b/k-(a-1)/k); //第一部分。
    	ll c2=min(a-1,b/k)-(a+k-1)/k+1; //第二部分，(a+k-1)/k+1等价于ceil(a/k)。
    	printf("%lld\n",fpow(2,c1+c2));
	}
    return 0;
}

```

---

## 作者：zyzxzhangyi (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/P13561)

# 思路

我们很容易发现，对于一个数 $x$，若 $\frac{x}{k}$ 在 $a$ 到 $b$ 之间，那么它的位置已经被固定了，反之，它既可以送出，也可以留给自己，方案数就要乘 $2$。 

然后就可以得出以下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long md = 1e9 + 7;
long long t, k, a, b, sum, num;

long long ksm(long long x, long long y){
	num = 1;
    while(y)
    	if(y % 2) num *= x, num %= md, y >>= 1, x *= x, x %= md;
    	else x *= x, x %= md, y >>= 1;
    return num;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> t;
	while(t--){
		sum = 0;
		cin >> k >> a >> b;
		for(int i = a; i <= b; i++)
		    if(i / k < a || i % k) sum++;
	    cout << ksm(2, sum) << endl;
	}
	return 0;
}
```

~~结果发现自己 TLE 了。~~

这时候我们可以用数学知识将复杂度转成 $O(1)$ 的：


```cpp
#include <bits/stdc++.h>
using namespace std;
const long long md = 1e9 + 7;
long long t, k, a, b, sum, num;

long long ksm(long long x, long long y){
	num = 1;
    while(y)
    	if(y % 2) num *= x, num %= md, y >>= 1, x *= x, x %= md;
    	else x *= x, x %= md, y >>= 1;
    return num;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> t;
	while(t--){
		cin >> k >> a >> b;
		sum = (a <= (b + 1) / k ? b + 1 : a * k) - a + b - (a <= (b + 1) / k ? b + 1 : a * k) + 1 - (b / k - min(a - 1, b / k)); //记得判断 a * k 是否超出 b 
	    cout << ksm(2, sum) << endl;
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/228661631)

时间复杂度：$O(T \log {b})$。

空间复杂度：$O(1)$。

---

## 作者：nbhs23a28 (赞：1)

简单题。

分析题面，记留下为 $1$，送出为 $0$，我们发现，对于每一组 $id,id\times k,id\times k^2,\dots$，只要最后一个确定为 $0$ 或 $1$，整一组就确定下来了，有 $2$ 种可能，这样，只要算出组数 $cnt$，答案就是 $2^{cnt}$，用快速幂即可。

考虑如何计算组数，我们发现，只要筛掉 $[a\times k,b]$ 内的所有 $k$ 的倍数，剩余数个数即为组数。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long k,a,b,cnt;
long long qp(long long x,long long y)
{if(y==0) return 1;
 if(y==1) return x;
 long long sum=qp(x,y>>1);
 if(y&1) return sum*sum%mod*x%mod;
 return sum*sum%mod;
}
int main()
{int t;cin>>t;
 while(t--)
 {cin>>k>>a>>b;
  cnt=max(0ll,b/k-a+1);//筛k倍数 
  cout<<qp(2,b-a+1-cnt)<<'\n';
 }
}

---

## 作者：jsisonx (赞：1)

[ 题目传送门](https://www.luogu.com.cn/problem/P13561)

# 题目分析

首先如果没有优秀方案的限制，那么每根笔都有送或留两种选择，因此方案总数为 $2^{b-a+1}$。下面考虑优秀方案的限制。

注意到，第 $x$ 根笔的选择只会影响第 $kx$ 根笔的选择，具体地，第 $kx$ 根笔的选择英语第 $x$ 根笔相反，这意味着一旦确定了第 $x$ 根笔的选择，第 $kx$ 根笔的选择也就确定了。这样，第 $x$ 根笔确实还有两种选择，而第 $kx$ 根笔却只有一种选择了。因此，第一根笔有两种选择，第 $k$ 根笔只有一种选择，第 $2$ 根笔有两种选择，而第 $2k$ 根笔只有一种选择。直到第 $f$ 根笔，第 $f$ 根笔有 两种选择，第 $kf$ 根笔只有一种选择，第 $f+1$ 根笔有两种选择，而不存在第 $k(f+1)$ 根笔，换句话说，$k(f+1)>b$。解得 $f=\lfloor \frac{b}{k} \rfloor$。算下来。有 $\max(0,f-a+1)$ 根笔只有一种选择，其它笔都有两种选择，因此答案为 $2^{b-a+1-\max(0,f-a+1)}$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long fp(long long a,long long b,long long p){
    long long a1=a,b1=b,ans=1;
    while(b1){
        if(b1&1){
            ans=ans*a1%p;
        }
        a1=a1*a1%p;
        b1>>=1;
    }
    return ans%p;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        long long k,a,b;
        cin>>k>>a>>b;
        long long f=b/k;
        long long r=max((long long)0,f-a+1);
        cout<<fp(2,b-a+1-r,1000000007)<<endl;
    }
    return 0;
}
```

---

## 作者：UKE_Piu (赞：1)

## Solution

容易看出，能凑成“一对”的数是很有限的，其中最大的一对是 $(b,\frac{b}{k})$ 所以我们容易知道，$a$ 到 $\frac{b}{k}$ 这段区间中的数字都可以作为优秀方案留或者送，我们有 $\frac{b}{k}-a+1$ 组这样的数对可以满足优秀方案，这些数对我们可以任选每组中的一个留下，另一个送出去，每组两种可能，一共 $2^{\frac{b}{k}-a+1}$ 种可能，剩下的没有配对的数也可以选择留下或者送出，所以剩下的数有 $2^{len-(\frac{b}{k}-a+1)\times 2}$ 种可能，其中 $len$ 是区间长度，乘二因为每对中有两个数，所以是对数乘二。因为我们要全部在一次分配种计算可能，所以这个需要用乘法原理，把上面两个相乘即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k,a,b;
const int P=1e9+7;
int qpow(int base,int exp){
	int ret=1;
	while(exp){
		if(exp&1) ret=ret*base%P;
		base=base*base%P;
		exp>>=1;
	}
	return ret%P;
}
signed main(){
	int T; cin>>T;
	srand(time(0));
	while(T--){
		cin>>k;
		cin>>a>>b;
		// x x/k
		// 0 1
		// 1 0
		// so a pair of (x,x/k) has two possiblity
		// the max number which can be matched is b
		// b can be matched with b/k
		// so we have a range [a, b/k] that can be matched
		int t=max(0ll,b/k-a+1);
		int r=b-a+1-2*t;
		int ans=qpow(2,t)%P*qpow(2,r)%P;
		cout<<ans<<'\n';
	}
} 
```

---

## 作者：zzy_zzy (赞：1)

### 前言
这题真有黄？？？
### 解法
对于一个数 $j\in[a,b]$ 来考虑，若不存在一个 $i\in[a,b]$ 使得 $ik=j$，我们令集合 $S_j=\{jk^x|x\in\mathbb{N},jk^x\in[a,b]\}$，那么由题可得，每个集合 $S_i$ 中的数的总选择方案数只有 2 种，又因为对于每个 $c\in[a,b]$，$c$ 存在且仅存在于一个 $S_i$ 中，于是我们只需要统计满足条件的 $j$ 的数量即可。

如何统计 $j$ 的数量？考虑分两种情况讨论：
1. $j\in[a,b]$ 且 $k\nmid j$
2. $j\in[a,b]$ 且 $k\mid j$ 且 $\frac{j}{k}\in[1,a)$

第一种情况是好做的，直接用整体的减去整除的。考虑第二种情况，此时只需统计 $k\cdot\frac{j}{k}\in[a,b]$ 的个数即可，即 $\frac{j}{k}\in[\lceil\frac{a}{k}\rceil,\lfloor\frac{b}{k}\rfloor]$，和前面的范围取个交集即可。
### 通过代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Mod=1e9+7;
int quick_pow(int x,int y){
    int res=1;
    while(y){
        if(y&1)res=res*x%Mod;
        x=x*x%Mod;
        y>>=1;
    }
    return res;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int k,a,b,cnt=0;
        cin>>k>>a>>b;
        cnt=(b-a+1)-((b/k)-((a-1)/k));
        cnt+=min(b/k,a-1)-a/k+1;
        if(a%k)cnt--;
        cout<<quick_pow(2,cnt)<<"\n";
    }
    return 0;
}
```

---

## 作者：wwwidk1234 (赞：0)

[在博客园食用效果~~更佳~~](https://www.cnblogs.com/wwwidk1234/p/19036622)

拿到题目之后，思考如何直接一步到位算出方案数有点困难，所以考虑将一件事拆开来做。

首先对于两支编号分别为 $x,y$ 的笔，若 $(x,y)$ 满足 $\dfrac{x}{y}=k$ 那么这两支笔就只有一种方案（$x$ 送出 $y$ 留下或 $x$ 留下 $y$ 送出）。下文把这种 $(x,y)$ 叫做“有限制的数对”。

在 $a \sim b$ 范围内，有限制的数对有这些：$(a,ak),(a+1,(a+1)k),(a+2,(a+2)k),\cdots,\left(\dfrac{b}{k},b\right)$。**有限制的数对的个数** $s$ 就是 $a \sim \dfrac b k$ 中数的个数，即 $s=\lfloor \dfrac b k \rfloor -a+1$。**每一个有限制的数对都有两种方案**，所以这些数对的方案一共有 $2^s$ 种。

剩下还有 $b-a+1-2s$ 支**笔**（不是数对），每一支笔都有送出与不送两种选择方案，所以剩下这些笔的方案数就是 $2^{b-a+1-2s}$。

注意到：选择笔的过程分成了两步走：先选有限制的数对再选剩下的笔，满足**乘法原理**，故最终答案为上面两步方案数的乘积，即 $2^s \times 2^{b-a+1-2s}$。

提醒：如果你 TLE 了那就检查一下是不是算出了 $s<0$ 的情况导致快速幂爆炸了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=-1;
constexpr int mod=1e9+7;
inline ll ksm(ll a,ll b)
{
	ll s=1;
	while(b)
	{
		if(b&1) s=s*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return s;
}
int main()
{
//	freopen("neuvillette.in","r",stdin);
//	freopen("neuvillette.out","w",stdout);
	int T;
	cin>>T;
	ll a,b,k,s;
	while(T--)
	{
		cin>>k>>a>>b;
		s=ll(b/k)-a+1;  //有限制的数对有多少个 
		if(s<0) s=0;
		cout<<ksm(2,b-a+1-2*s)*ksm(2,s)%mod<<'\n';
	}
	return 0;
}
/*
思路： 
总方案数:2^(b-a+1) 
若(x,y)满足x/y=k那么只有一种方案(x送出,y留下)或(x留下,y送出) 
有限制的数对:(a,ak),(a+1,(a+1)k),(a+2,(a+2)k),...,(b/k,b)“每一个数对”都只有2种方案
设这些数对的个数为s那么这些有限制的数对合法方案数就是2^s
s为满足(a+i-1)<=b/k的最大的i
s=int(b/k)-a+1

没限制的“数”（不是数对）有b-a+1-2s个,每一个数有2种方案(送或者不送),方案数2^(b-a+1-2s) 
*/
```

---

