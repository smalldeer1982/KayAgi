# Mister B and PR Shifts

## 题目描述

Some time ago Mister B detected a strange signal from the space, which he started to study.

After some transformation the signal turned out to be a permutation $ p $ of length $ n $ or its cyclic shift. For the further investigation Mister B need some basis, that's why he decided to choose cyclic shift of this permutation which has the minimum possible deviation.

Let's define the deviation of a permutation $ p $ as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF819B/47275887a8ad3386063ea864423569d3d609b7f9.png).

Find a cyclic shift of permutation $ p $ with minimum possible deviation. If there are multiple solutions, print any of them.

Let's denote id $ k $ ( $ 0<=k&lt;n $ ) of a cyclic shift of permutation $ p $ as the number of right shifts needed to reach this shift, for example:

- $ k=0 $ : shift $ p_{1},p_{2},...\ p_{n} $ ,
- $ k=1 $ : shift $ p_{n},p_{1},...\ p_{n-1} $ ,
- ...,
- $ k=n-1 $ : shift $ p_{2},p_{3},...\ p_{n},p_{1} $ .

## 说明/提示

In the first sample test the given permutation $ p $ is the identity permutation, that's why its deviation equals to $ 0 $ , the shift id equals to $ 0 $ as well.

In the second sample test the deviation of $ p $ equals to $ 4 $ , the deviation of the $ 1 $ -st cyclic shift $ (1,2,3) $ equals to $ 0 $ , the deviation of the $ 2 $ -nd cyclic shift $ (3,1,2) $ equals to $ 4 $ , the optimal is the $ 1 $ -st cyclic shift.

In the third sample test the deviation of $ p $ equals to $ 4 $ , the deviation of the $ 1 $ -st cyclic shift $ (1,3,2) $ equals to $ 2 $ , the deviation of the $ 2 $ -nd cyclic shift $ (2,1,3) $ also equals to $ 2 $ , so the optimal are both $ 1 $ -st and $ 2 $ -nd cyclic shifts.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
0 0
```

## 样例 #2

### 输入

```
3
2 3 1
```

### 输出

```
0 1
```

## 样例 #3

### 输入

```
3
3 2 1
```

### 输出

```
2 1
```

# 题解

## 作者：hzoi_liuchang (赞：10)


## 分析

这道题$n\leq10^{6}$，显然$n^{2}$的暴力是无法解决问题的

那么我们可以考虑数列的某一种性质

因为最终的答案是$\sum{n \atop i=1} |p_i - i|$，和绝对值有关，所以我们把数列中的数分为两类

第一类是$p_i-i>0$，第二类是$p_i-i\leq0$

我们可以开四个变量：$Zcnt$ 记录第一类数的个数，$Ztot$ 记录第一类数对结果的贡献，$Fcnt$ 记录第二类数的个数，$Ftot$ 记录第二类数对结果的贡献

这些变量的初始值我们可以预处理出来

每次我们把数列中位置最靠后的元素拿出来，放在最前面，其他的元素向后移动一位

我们先不考虑临界元素和特殊情况

一个很显然的结论是，除了扔到队首的那一个元素，第一类数每次做出的贡献之和都要减去$Zcnt$，第二类数每次做出的贡献之和都要加上$Fcnt$

但是$Zcnt$和$Fcnt$的个数并不是恒定不变的，有两种特殊情况

1、一个数由第一类数变为第二类数，这时的临界条件是$p_i-i=0$

那么我们只需要在读入的时候预处理每一个数发生临界变化的时间就可以了

2、一个数由第二类数变为第一类数，这时只有可能是原来在队尾的数扔到了队首

这时我们只需要特判一下就可以了

## 代码

``` cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
const int maxn=1e7+5;
ll n,Zcnt,Fcnt,Ztot,Ftot;
ll a[maxn],judone[maxn];
int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    for(ll i=1;i<=n;i++){
        if(a[i]<=i){
            Fcnt++;
            Ftot+=(i-a[i]);
        } else {
            judone[a[i]-i]++;
            Zcnt++;
            Ztot+=(a[i]-i);
        }
    }
    ll ans=Ztot+Ftot,jl=0;
    for(ll i=1;i<n;i++){
        Ztot-=Zcnt;
        Zcnt-=judone[i];
        Ftot+=Fcnt;
        Fcnt+=judone[i];
        ll x=a[n-i+1];
        Ftot-=n+1-x,--Fcnt;
        if(x>1)++judone[x-1+i],Ztot+=x-1,++Zcnt;
        else ++Fcnt;
        if(ans>Ftot+Ztot) ans=Ftot+Ztot,jl=i;
    }
    printf("%lld %lld\n",ans,jl);
    return 0;
}
```



---

## 作者：2huk (赞：4)

upd on 2024/05/21：修复了寄掉的 $\LaTeX$。

> - 定义排列 $p$ 的权值为 $\sum_{i=1}^n |p_i - i|$。给你一个 $1 \sim n$ 的排列 $a$，从后面拿 $k \in [0, n - 1]$ 个数放在前面，使得其权值最小。求最小权值和任意一 $k$。
> - $n \le 10^6$。

我们设 $f(k)$ 表示将 $a_k, a_{k+1}, \dots, a_n$ 放在前面后的权值，即排列 $a_k, a_{k+1}, \dots, a_n, a_1, a_2, \dots, a_{k-1}$ 的权值。那么有：
$$
f(k) = \sum_{i=k}^n |a_i - i + k - 1| + \sum_{i = 1}^{k - 1} |a_i - i - k|
$$
设 $b_i = a_i - i$，那么：
$$
f(k) = \sum_{i=k}^n |b_i + k - 1| + \sum_{i = 1}^{k - 1} |b_i - k|
$$


考虑偏移一位后的答案，即：
$$
f(k+1) = \sum_{i=k+1}^n |b_i + k| + \sum_{i = 1}^{k} |b_i - k - 1|
$$
显然求出偏移差后，可以通过 $f(1)$ 推导至所有 $f(i)$，然后 $\min f(i)$ 即为答案。

做差观察偏移量：
$$
\begin{aligned}
 f(k) - f(k + 1) &= \sum_{i=k}^n |b_i + k - 1| + \sum_{i = 1}^{k - 1} |b_i - k| - \sum_{i=k+1}^n |b_i + k| - \sum_{i = 1}^{k} |b_i - k - 1|\\
  &= \sum_{i=k+1}^n (|b_i + k - 1| - |b_i + k|) + \sum_{i=1}^{k-1} (|b_i - k| - |b_i - k - 1|) + |b_k+k-1| - |b_k-k-1|\\
  &= \sum_{i=k+1}^n (|b_i + k - 1| - |b_i + k|) - \sum_{i=1}^{k-1} (|b_i - k - 1| - |b_i - k|) + |b_k+k-1| - |b_k-k-1|
\end{aligned}
$$
然后发现前面两个**形式极其相似**的和式不好做了。发现这两个和式的区别仅在于 $\Sigma$ 中 $i$ 的范围以及 $k$ 的系数 $\pm 1$。

设 $l \in\{k+1, 1\}, r \in\{n, k-1\}, c \in \{k, -k\}$ ，那么我们只需要求解 $g(l, r, c) = \sum_{i=l}^r (|b_i + c| - |b_i + c - 1|)$，那么这两个和式分别为 $g(k+1, n, k)$ 和 $g(1, k-1, -k)$。

发现 $\Sigma$ 中是一个 $|a - 1| - |a|$ 的形式，分类讨论：
$$
|a-1|-|a| = \begin{cases}
 -1 & \text{ if } a \ge 1\\
 1-2a & \text{ if } 0 < a < 1 \\
 1 & \text{ if } a \le 0\\
\end{cases}
$$
所以我们要分别统计这样的数量。即：

- $s_1 = \sum\limits_{i=l}^r[b_i + c \ge 1] = \sum\limits_{i=l}^r[b_i \ge 1 - c]$；
- $s_2 = \sum\limits_{i=l}^r[b_i + c \le 0] = \sum\limits_{i=l}^r[b_i \le - c]$；
- $s_3 = r - l + 1 - s_1 - s_2$。

以及第二个分类中的：

- $s_0 = \sum\limits_{i=l}^r [0 < b_i + c < 1](1-2(b_i + c))$。

显然 $s_0$ 的推导不够：
$$
\begin{aligned}

s_0&=
\sum_{i=l}^r [0 < b_i + c < 1](1-2(b_i + c))\\&=
\sum_{i=l}^r [-c < b_i < 1 - c](1-2(b_i + c))\\&=
s_3 - 2\sum_{i=l}^r [-c < b_i < 1 - c] b_i -2cs_3

\end{aligned}
$$

此时 $s_0, s_1, s_2$ 中的和式都可以直接用**主席树**等数据结构维护了。反推即可。

---

## 作者：vanyou (赞：4)

## 思路

定义 $b_i$ 表示 $a_i-i$，通过手玩样例发现，每一次变化会让 $1 \le i \le n-1$ 的 $b_i$ 减 $1$，而 $b_n$ 会加 $n-1$，而每次的答案就是 $b_1$ 到 $b_n$ 的绝对值和，但是每次都扫一遍 $b$ 数组 $\mathcal{O}(n^2)$ 显然会超时，考虑找到相邻两次变化之间的规律。

由于答案是取的绝对值，所以在进行一次修改之前，所有小于等于 $0$ 的 $b_i$ 都会让答案加 $1$，所有大于 $0$ 的 $b_i$ 都会让答案减 $1$，而 $b_n$ 的情况单独考虑就可以了。

为了快速求出有多少数大于和小于等于 $0$ 并且还要满足全体减 $1$，考虑使用树状数组维护。因为有负数，所以定义一个数 $N$ 表示树状数组中 $0$ 的位置，全体减一就让 $N$ 加 $1$ 就可以了。

综上，只需要处理出原数组的答案，就可以在 $\log$ 的时间里算出下一次修改的答案，最后取个最小的答案并记录操作了多少次就可以了，$\mathcal{O}(n\log n)$。

## Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000010],b[1000010],now,ans,front,N=1000000,c[3000010],id;//N表示树状数组里0的位置

int lowbit(int x){return x&-x;}

void update(int x,int v){
	x+=N;
	for(int i=x;i<=n+N;i+=lowbit(i)) c[i]+=v;
}

int sum(int x){
	x+=N;
	int ans=0;
	for(int i=x;i;i-=lowbit(i)) ans+=c[i];
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		b[i]=a[i]-(i+1);
		now+=abs(b[i]);//算出原排列的答案
		update(b[i],1);
	}
	ans=now,id=0;
	for(int i=1;i<n;i++){
		front=(front-1+n)%n;//b[n]的位置
		b[front]-=i-1;//减掉前i-1次修改的减1
		now-=abs(b[front]);
		update(b[front],-1);//删掉树状数组里原来的b[n]
		b[front]+=n-1;
		now+=abs(b[front]);
		int x=sum(0);
		update(b[front],1);
		N++;//全体减1
		now+=x*2-n+1;//加1是为了去除b[n]，单独考虑b[n]
		if(ans>now) ans=now,id=i;//取最小值
	}
	cout<<ans<<" "<<id;
	return 0;
}
```

---

## 作者：DiDi123 (赞：3)

# 一、分析

本蒟蒻太菜了，只会拿树状数组做qwq

首先可以把 $a$ 数组拷贝一份到后面，每次取连续的 $n$ 个数就是一种变换能得到的序列。区间 $[i,i+n-1]$ 的数组成的序列就是把前 $n-i+1$ 个数放到后面组成的序列。

那么可以把这道题看做一个类似滑动窗口的东西，每次窗口往后滑一格。设窗口第一个数为 $a_i$，那么窗口中要新加入的数就是 $a_{i+n}$，很显然 $a_i=a_{i+n}$。我们先来考虑序列中区间 $[i+1,i+n-1]$ 的数，我们发现这个区间中的住需要减掉的坐标都减小 $1$，此时绝对值有可能变大也有可能变小。如果这个数是减掉原本坐标已经是非负数，那么绝对值会变大，反之绝对值会减小。

那么我们就可以考虑分类讨论，设 $p_i$ 表示滑到 $i$ 时与上一个滑动窗口的差别。设 $b_i=a_i-i$，如果 $b_i\geq0$，那么只要 $i$ 不滑出窗口贡献一定是正的，所以我们就给 $p_{2\sim i}$ 加上 $1$；如果 $b_i<0$，那么我们就需要分两段区间，第一段是 $a_i$ 减去现在坐标小于 $0$ 的区间，第二段是大于 $0$ 的区间。对于第一段区间，应该给 $p_i$ 减 $1$，对于第二段区间应该加 $1$。

还要特殊考虑一下上文提到的 $a_i$ 和 $a_{i+n}$，同时要注意新加入的 $a_{i+n}$ 也要计算给 $p$ 的贡献。

区间加以及单点查询，用树状数组。

# 二、代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 4000001
long long n,org,a[MAXN],b[MAXN],c[MAXN],op,ans=0x7f7f7f7f7f;
void add(long long x,long long y)
{
	for(;x<=n;x+=x&-x) c[x]+=y;
}
long long ask(long long x)
{
	long long tp=0;
	for(;x;x-=x&-x) tp+=c[x];
	return tp;
}
int main()
{
	cin>>n;
	for(long long i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=a[i]-i;
		org+=abs(b[i]);
		a[i+n]=a[i];
	}
	for	(long long i=1;i<=n;i++)
	{
		if(b[i]>0)
		{
			add(2,1);
			add(i+1,-1);
		}
		else
		{
			long long bk=-b[i];
			if(bk+1>i) bk=i-1;
			add(2,-1); //2~bk
			add(bk+2,1);
			if(bk+1<i) //bk+1~i
			{
				add(bk+2,1);
				add(i+1,-1);
			}
		}
	}
	for(long long i=1;i<=n;i++)
	{
		long long tt=ask(i)+org;
	//	cout<<tt<<endl;
		if(tt<ans)
		{
			ans=tt;
			op=n-i+1;
		}
		long long px=a[i]-n;
		long long bk=-px;
		if(bk+1>n) bk=n-1;
		add(i+2,-1); //2~bk
		add(bk+i+2,1);
		if(bk+1<n) //bk+1~i
			add(bk+i+2,1);
		org=tt;
		org-=abs(a[i]-1);
		org+=abs(px);
	}
	if(op==n) op=0;
	cout<<ans<<' '<<op;
}
```


---

## 作者：yzxoi (赞：2)

## [My Blog](https://yzxoi.top/archives/1768)

## Description

>题目链接：[CF819B](http://codeforces.com/problemset/problem/819/B)

给定一个长度为 $n$ 的全排列 $\{p_i\}$，定义其偏移值为 $\sum_{i=1}^{n}|p_i-i|$，你可以将 $k\in[0,n-1]$ 个数从后面移到前面，使全排列的偏移值最小，输出最小偏移值和此时的 $k$，如果有多个符合输出任意一个。

$1\leq n \leq 10^6$

## Solution

~~CF评分1900的黑题？？？肯定要来水一下呀（（（~~

先观察下移动一次后偏移值的改变：中间一段的 $i$ 全部加一，最后一个数移到最前面。

移动两次后偏移值的改变：在移动一次后的序列中，中间一段的 $i$ 全部加一，最后一个数移到第二个数。

那么由此可以推理出移动 $j$ 次后偏移值的改变：在移动 $j-1$ 次后的序列中，所有 $i\in[1,n-1]$ 的数字的 $i$ 全部加一，最后一个数移动到 $j$。

考虑区间内数字所有 $i$ 加一的操作如何实现。

可以直接大力分类讨论：

1. $p_i >i $，此时只需要记下此种类的个数以及 $p_i-i$ 的和，每次修改的时候只需要把和减去个数即可。
2. $p_i\leq i$，此时也只需要记下此种类的个数以及 $i-p_i$ 的和，每次修改的时候只需要把和减去个数即可。

由于第一个种的数减多次后可能会变成第二种，所以需要为第一种的所有 $p_i-i$ 开个桶计数，注意维护下即可。

最后一个数移动到 $j$ 可以先考虑不管，那么所有数字都进行一次修改操作，然后把第 $(n+1)$ 个数移到第 $j$ 个即可，注意维护下上文种分类讨论中维护的所有东西。

思路写起来有点麻烦，但代码还是很简洁的。

## Code

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define CI Cn int&
#define gc getchar
#define D isdigit(c=gc())
#define pc(c) putchar((c))
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
namespace Debug{
	Tp I void _debug(Cn char* f,Ty t){cerr<<f<<'='<<t<<endl;}
	Ts I void _debug(Cn char* f,Ty x,Ar... y){W(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	Tp ostream& operator<<(ostream& os,Cn vector<Ty>& V){os<<"[";for(Cn auto& vv:V) os<<vv<<",";os<<"]";return os;}
	#define gdb(...) _debug(#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
namespace FastIO{
	Tp I void read(Ty& x){char c;int f=1;x=0;W(!D) f=c^'-'?1:-1;W(x=(x<<3)+(x<<1)+(c&15),D);x*=f;}
	Ts I void read(Ty& x,Ar&... y){read(x),read(y...);}
	Tp I void write(Ty x){x<0&&(pc('-'),x=-x,0),x<10?(pc(x+'0'),0):(write(x/10),pc(x%10+'0'),0);}
	Tp I void writeln(Cn Ty& x){write(x),pc('\n');}
}using namespace FastIO;
Cn int N=1e6+10;
int n,k,a[N],cnt[N<<1],c0,c1;//由于存在移动操作，所以桶标记可能会超过 n
LL s0,s1,Ans;
int main(){
	RI i;for(read(n),i=1;i<=n;i++) read(a[i]),a[i]>i?++cnt[a[i]-i],++c0,s0+=a[i]-i:(++c1,s1+=i-a[i]);
	Ans=s0+s1;for(i=1;i<=n;i++) s0-=c0,s1+=c1,c0-=cnt[i],c1+=cnt[i],(--c1,s1-=(n+1)-a[n-i+1]),//分类讨论
	a[n-i+1]>1?++cnt[a[n-i+1]-1+i],++c0,s0+=a[n-i+1]-1:++c1,s0+s1<Ans&&(Ans=s0+s1,k=i);//特殊处理最末尾的数
	return write(Ans),pc(' '),writeln(k),0;
}
```



---

## 作者：DarthVictor (赞：1)

# 题目
[原题链接](http://codeforces.com/problemset/problem/819/B)
# 解说
第一思路暴力，时间效率$O(n^2)$，肯定$T$这次试都没试，想办法优化吧。

$O(n^2)$的效率是因为我们有两层循环：枚举哪一位移动到队首了，以及计算现在的偏移值。枚举估计是省不了，那么我们就要想办法把计算偏移值优化到常数级，这样时间效率为$O(n)$，应该问题不大了。

我们可以注意到，每次移动时，如果原来$a[i]<=i$，由于$a[i]$对应的$i$，变大了，所以$a[i]-i$负的更多了，绝对值变大了，且每移动一位每个数的绝对值增大$1$；相对的，对于$a[i]>i$，由于$i$增大了，绝对值每个数减小$1$，因此每次操作我们只需让$sumpositive$减去$cntpositive$，让$sumnegative$加上$cntnegative$，之后要更新$cntpositive$和$cntnegative$的值。位于队末的元素比较特殊，它的$i$从$n$变成了$1$，需要特殊处理一下。这样的话我们就把时间效率降到$O(n)$了。

有一个小方法需要说一下，就是我们怎么判断一个差为正的数何时转为差为负的数（指小于等于零）。枚举是不可能的，这样时间效率就又回$n^2$了。想一下，如果一个数正出来$x$，那么就一定会在$x$轮之后转负（当然是指没有被扔到队首的情况，这时候我们特殊处理即可），因此我们在开始输入时就统计出来一个$count$数组统计每个正出来的数的$x$值即可。

一些我踩的坑和部分注解在代码里给出。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2000000+3;
typedef long long ll;
ll n,a[1000000+3],sump,sumn,pos,ans,cntp,cntn,Count[maxn];
//注意maxn不是n的范围，Count的下标是差的值，因此应开到差的最大值
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]<=i){
			cntn++;
			sumn+=i-a[i];
		}
		else{
			cntp++;
			sump+=a[i]-i;
			Count[a[i]-i]++;
		}
	}
	ans=sump+sumn;
	pos=0;//注意这里的初始化，一定记得把pos初始化为0，代表不用操作的情况
	for(ll i=1;i<=n-1;i++){
		sump-=cntp;
        cntp-=Count[i];
        sumn+=cntn;
        cntn+=Count[i];
        sumn-=n+1-a[n-i+1];
		cntn--;
        if(a[n-i+1]>1){
			Count[a[n-i+1]-1+i]++;
			sump+=a[n-i+1]-1;
			cntp++;
		}
        else cntn++;
		if(sumn+sump<ans){
			ans=sumn+sump;
			pos=i;
		}
	}
	printf("%lld %lld",ans,pos);
	return 0;
}
```
幸甚至哉，歌以咏志。

---

## 作者：万弘 (赞：1)

~~瞎写的居然A了~~

考虑暴力,第$i$次把$p_{n-i+1}$放到最前面,然后重新计算.

然而另外的$n-1$个元素,要么$+1$要么$-1$,这样算太不明智了.

注意到对于$p_x-x\le 0$,shift一次后,$|p_x-x|$会+1;对于$p_x-x>0,|p_x-x|$会-1.总结一下就是,shift一次后正数的贡献会减去正数数量,正数数量会减去1的数量;非正数数量的贡献会加上非正数数量,非正数数量会加上1的数量.  
然后$p_{n-i+1}$会变成第一个,贡献由$|p_{n-i+1}-(n+1)|$变成$|p_{n-i+1}-1|$.这个直接暴力搞就好了.
  
时间复杂度$\mathcal O(n)$.  
本人过菜,这都讲不清楚,还是看代码吧
```cpp
/**********/
bool umin(ll &a,ll b)
{
	if(b<a)return a=b,1;
	return 0;
}
#define MAXN 2000011
ll c[MAXN],p[MAXN];//c[i]表示p_x-x=i的数量
int main()
{
    ll n=read(),cnt_positive=0,sum_positive=0,cnt_negative=0,sum_negative=0;
    for(ll i=1;i<=n;++i)p[i]=read();
    for(ll i=1;i<=n;++i)
        if(p[i]-i<=0)++cnt_negative,sum_negative+=i-p[i];
        else ++c[p[i]-i],++cnt_positive,sum_positive+=p[i]-i;
    ll ans=sum_positive+sum_negative,pos=0;
    for(ll i=1;i<n;++i)
    {
        sum_positive-=cnt_positive;
        cnt_positive-=c[i];//第i次shift时1的数量就是c[i]
        sum_negative+=cnt_negative;
        cnt_negative+=c[i];
        ll x=p[n-i+1];//处理p[n-i+1]
        sum_negative-=n+1-x,--cnt_negative;
        if(x>1)++c[x-1+i],sum_positive+=x-1,++cnt_positive;
        else ++cnt_negative;
        if(umin(ans,sum_positive+sum_negative))pos=i;
    }
    printf("%lld %lld",ans,pos);
    return 0;
}
```

---

## 作者：hh弟中弟 (赞：0)

### [CF819B Mister B and PR Shifts](https://www.luogu.com.cn/problem/CF819B)
很容易的想到 $n^2$ 做法，发现有很多东西都是重复记录了。考虑继承这些东西。\
定义一个位置的价值为 $a_i-i$，然后记一下这个价值出现的次数，发现每右移一位，这些价值的数量都会左移一位，即原来价值为 $x$ 的现在价值为 $x-1$。\
同时，答案可以借助这些价值从上一次的答案转移过来，即价值为非正整数的会对答案做出 $1$ 的贡献，价值为正整数的做出 $-1$ 的贡献。\
此时只需要支持单点修改区间查询即可，树状数组是个不错的选择（其实再记一下其他东西可以 $\mathcal{O}(n)$，不过 ds 不要脑子）。\
对于每次的右移，开个变量记录一下就行，对于末尾的点单独算。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=4e6+10;
int t[N],len,n,a[N],last,ans=0,mink,minans;
inline void add(int pos,int x){int zc=pos+1;for(;pos<=len;pos+=pos&-pos)t[pos]+=x;}
inline int query(int l,int r){
	int res=0;
	l--;
	for(;l;l-=l&-l)res-=t[l];
    for(;r;r-=r&-r)res+=t[r];
	return res;
}
inline int real(int x){return x+n+last;}
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	n=read();len=n*4+1;
	for(int i=1;i<=n;++i){
		a[i]=read();
		add(real(a[i]-i),1);ans+=std::abs(a[i]-i);
	}
	mink=0,minans=ans;
	for(int i=1;i<=n-1;++i){
		int en=a[n-i+1];
		add(real(en-n),-1);
		ans+=-(std::abs(en-n))+en-1+query(1,real(0))-query(real(1),real(n-1));
		if(minans>ans){minans=ans,mink=i;}
		last++;
		add(real(en-1),1);
	}
	std::cout<<minans<<' '<<mink<<'\n';
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF819B)

# 前置知识

[权值树状数组及应用](https://oi-wiki.org/ds/fenwick/#%E6%9D%83%E5%80%BC%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84%E5%8F%8A%E5%BA%94%E7%94%A8)

# 解法

由 [[ABC351F] Double Sum](https://www.luogu.com.cn/problem/AT_abc351_f) 的套路，尝试展开绝对值及 $\min,\max$。


将式子拆开有 $\begin{aligned} & \min\limits_{k=0}^{n-1}\{ \sum\limits_{i=1}^{n-k}|a_{i}-(i+k)|+ \sum\limits_{i=n-k+1}^{n}|a_{i}-(i-(n-k))| \} \\ &=\min\limits_{k=0}^{n-1}\{ \sum\limits_{i=1}^{n-k}( \max(a_{i},i+k)- \min(a_{i},i+k))+ \sum\limits_{i=n-k+1}^{n}( \max(a_{i},i+k-n)- \min(a_{i},i+k-n)) \} \\ &=\min\limits_{k=0}^{n-1}\{ \sum\limits_{i=1}^{n-k}(a_{i}+i+k-2 \min(a_{i},i+k))+ \sum\limits_{i=n-k+1}^{n}(a_{i}+i+k-n-2 \min(a_{i},i+k-n)) \} \\ &=\sum\limits_{i=1}^{n}(a_{i}+i)+\min\limits_{k=0}^{n-1}\{- \sum\limits_{i=1}^{n-k}2 \min(a_{i},i+k)- \sum\limits_{i=n-k+1}^{n}2 \min(a_{i},i+k-n) \} \\ &=\sum\limits_{i=1}^{n}(a_{i}+i)-2 \max\limits_{k=0}^{n-1}\{\sum\limits_{i=1}^{n-k} \min(a_{i},i+k)+\sum\limits_{i=n-k+1}^{n} \min(a_{i},i+k-n) \} \end{aligned}$。
  - 好像式子推多了，懒得改了，只是常数大点。

现在问题来到了怎么求 $\max\limits_{k=0}^{n-1}\{\sum\limits_{i=1}^{n-k} \min(a_{i},i+k)+\sum\limits_{i=n-k+1}^{n} \min(a_{i},i+k-n) \}$。

令 $\begin{cases} x_{i}=a_{i}-i \\ y_{i}=a_{i}+n-i \end{cases}$，由于是排列所以 $\{ x \},\{ y \}$ 均满足内部两两不同，则转化为求 $\max\limits_{k=0}^{n-1}\{\sum\limits_{i=1}^{n-k}([k \ge x_{i}] \times a_{i}+[k<x_{i}] \times (i+k))+\sum\limits_{i=n-k+1}^{n}([k \ge y_{i}] \times a_{i}+ [k<y_{i}] \times (i+k-n)) \}$，前半部分将其拆成 $\begin{cases} [k \ge x_{i}] \times a_{i} \\ [k<x_{i}] \times i \\ [k<x_{i}] \times k \end{cases}$ 三部分，后半部分同理。

将 $\{ x \},\{ y \}$ 分别插入到权值树状数组里，分别维护 $\begin{cases} [k \ge x_{i}] \times a_{i}/[k \ge y_{i}] \times a_{i} \\ [k<x_{i}] \times i/[k<y_{i}] \times (i-n) \\ [k<x_{i}]/[k<y_{i}] \end{cases}$ 即可，注意及时消除影响。

对于负数整体向右移来处理。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll a[3000010],x[3000010],y[3000010],c[6][3000010];
ll lowbit(ll x)
{
    return (x&(-x));
}
void add(ll n,ll x,ll val,ll c[])
{
    x+=1000001;
    n+=1000001;
    for(ll i=x;i<=n;i+=lowbit(i))
    {
        c[i]+=val;
    }
}
ll ask(ll x,ll c[])
{
    ll ans=0;
    x+=1000001;
    for(ll i=x;i>=1;i-=lowbit(i))
    {
        ans+=c[i];
    }
    return ans;
}
int main()
{
    ll n,ans=0,pos=0,sum=0,i,k;
    scanf("%lld",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        x[i]=a[i]-i;
        y[i]=a[i]+n-i;
        add(2*n,x[i],a[i],c[0]);
        add(2*n,x[i],i,c[2]);
        add(2*n,x[i],1,c[4]);  
    }
    for(k=0;k<=n-1;k++)
    {
        sum=0;
        sum+=ask(k,c[0]);
        sum+=ask(2*n,c[2])-ask(k,c[2]);
        sum+=(ask(2*n,c[4])-ask(k,c[4]))*k;
        sum+=ask(k,c[1]);
        sum+=ask(2*n,c[3])-ask(k,c[3]);
        sum+=(ask(2*n,c[5])-ask(k,c[5]))*k;
        if(sum>ans)
        {
            ans=sum;
            pos=k;
        }
        add(2*n,x[n-k],-a[n-k],c[0]);
        add(2*n,x[n-k],-(n-k),c[2]);
        add(2*n,x[n-k],-1,c[4]);
        add(2*n,y[n-k],a[n-k],c[1]);
        add(2*n,y[n-k],n-k-n,c[3]);
        add(2*n,y[n-k],1,c[5]);
    }
    ans*=-2;
    for(i=1;i<=n;i++)
    {
        ans+=a[i]+i;
    }
    printf("%lld %lld\n",ans,pos);
    return 0;
}
```

---

## 作者：王珩030115 (赞：0)

一道不错的~~瞎搞~~思维题  
枚举移动距离是O(N)的，如果每次再花O(N)计算一遍显然是不行的。
**tip：**移动均指向右移动

感性思考后，感觉每次移动后每个ai-i对于原来不是+1就是-1(末尾元素特判）

事实就是这样，我们可以通过记录一些东西，使得计算是O(1)的。

对于ai，i称为当前位置，ai称为目标位置，那么，用left表示当前位置在目标位置左边的元素个数，对于这些元素，每次移动后会使当前值-1，同理，用right表示当前位置在目标位置右端（包括重合）的元素个数，这些元素移动会使当前值+1，再单独考虑末尾元素。

所以 now=last-l+r-(n-末尾元素)+(末尾元素-1)；

对于left和right，开一个桶t[i]，表示有t[i]个元素右移i可到达目标位置，
 每次r+=t[i],l-=t[i];即可。具体细节看代码（注意自己多思考思考）
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(i=a;i<=b;i++)
#define LL long long
LL ans,now;
int i,j,k,n,m,l,r,last,id,a[4000005],t[4000005];
char s[10];
inline void read(int& x){
	char s=getchar();x=0; int f=1;
	while(!isdigit(s)){if(s=='-') f=-1; s=getchar();}
	while(isdigit(s)){ x=x*10+s-'0'; s=getchar();}
	x*=f;
}
int main()
{
	read(n);
	ans=1e18;
    for(i=1;i<=n;i++){
    	read(a[i]);
        now+=abs(a[i]-i);
        if(i==n) continue;
		if(i<a[i]) t[a[i]-i]++,l++;
		  else r++; 	
	}  
    ans=now;
    last=n;
    for(i=1;i<n;i++){
    	now=now-l+r-(n-a[last])+a[last]-1;
    	if(now<ans){
    		ans=now;
    		id=i;
		}
		r+=t[i],l-=t[i];
		if(a[last]==1) ;
		  else r--,l++;
		t[i+a[last]-1]++;
    	last--;
	}
	cout<<ans<<" "<<id;
	return 0;
}
```

---

