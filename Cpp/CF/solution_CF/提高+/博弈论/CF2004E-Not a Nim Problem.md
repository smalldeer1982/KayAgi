# Not a Nim Problem

## 题目描述

有 $n$ 堆石子，每堆有 $a_i$ 个。

Alice 和 Bob 轮流取石子。Alice 先手。每个人在当前回合下可以随意选择一堆石子取任意数量个，要求：

- 设选择的这堆石子有 $x$，取走 $y$ 个，则必须使 $x$ 与 $y$ 互质。

第一个不能操作的人输掉这场游戏。在两人都使用最优策略的前提下，求获胜者。

## 样例 #1

### 输入

```
3
3
3 2 9
4
3 3 6 1
5
1 2 3 4 5```

### 输出

```
Bob
Alice
Bob```

# 题解

## 作者：伊地知虹夏 (赞：5)

**笑点解析**：(E + D) < B

发现每堆游戏是相对独立的，通过计算每堆的 Sprague-Grundy (SG) 值，然后将这些值进行异或运算，以判断当前状态是否为必胜（即结果是否为 $0$）。  

接下来，我们需要探讨如何计算 SG 值。  

通过观察前 $30$ 个 SG 值，我们首先注意到偶数的 SG 值均为 $0$。此外，我们发现奇质数的 SG 值是连续的。进一步的观察揭示，合数的 SG 值等于其最小质因子的 SG 值。   

**证明**：设 $ S_n = \{f(x) | (x,n) = 1\} $。

我们使用数学归纳法来推导，假设对于所有 $ n \leq k $ 的情况都成立，接下来看 $ n = k + 1 $。  

- 如果 $ n $ 是质数，由于所有小于或等于 $ k $ 的 $ x $ 都与 $ n $ 互质，因此 $\operatorname{mex} S_n $ 将等于 $\max \{f(x) | x \le k\} + 1$。  
  
- 如果 $ n $ 是合数，设其最小质因子为 $ p $，那么对于所有 $ x < p $，有 $ f(x) \in S_n $。同时，由于 $ p $ 是 $ x $ 的因子，满足 $\gcd(n,x) > 1$，所以 $ f(p) \notin S_n $。因此，$\operatorname{mex} S_n = f(p)$。

证明结论后，我们就可以使用线性筛法求出 SG 值。

接下来是我调校了很久后 GPT 3.5 给出的代码

```cpp
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000000;  // 最大值为 10^7
int min_prime[MAXN + 1];    // 存储每个数的最小质因子
int sg[MAXN + 1];           // SG 值数组
vector<int> primes;         // 存储质数

// 线性筛法计算最小质因子和 SG 值
void calculate_min_prime_and_sg() {
  memset(min_prime, 0, sizeof(min_prime));  // 初始化最小质因子数组
  memset(sg, 0, sizeof(sg));                // 初始化 SG 值数组
  // 线性筛法
  for (int i = 2; i <= MAXN; ++i) {
    if (min_prime[i] == 0) {  // 如果 i 是质数
      min_prime[i] = i;       // 质数的最小质因子是它自己
      primes.push_back(i);    // 记录质数
      sg[i] = primes.size();
    }
    // 更新最小质因子
    for (int p : primes) {
      if (p > min_prime[i] || p * i > MAXN) break;  // 只需查找到 sqrt(i)
      min_prime[p * i] = p;                         // 设置最小质因子
    }
  }
  sg[1] = 1;  // SG(1) = 1
  sg[2] = 0;  // SG(2) = 0
  // 计算 SG 值
  for (int i = 3; i <= MAXN; ++i)
    if (min_prime[i] < i)
      sg[i] = sg[min_prime[i]];  // 合数的 SG 值等于其最小质因子的 SG 值
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // 预处理最小质因子和 SG 值
  calculate_min_prime_and_sg();

  int t;
  cin >> t;  // 测试案例的数量
  vector<string> results;

  while (t--) {
    int n;
    cin >> n;  // 当前测试案例的石头堆数量
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];  // 当前测试案例的石头数量
    }

    // 计算 SG 的异或值
    int xor_sum = 0;
    for (int num : a) {
      xor_sum ^= sg[num];  // 使用预处理的 SG 值
    }

    // 判断赢家
    if (xor_sum == 0) {
      results.push_back("Bob");
    } else {
      results.push_back("Alice");
    }
  }

  // 输出结果
  for (const string& result : results) {
    cout << result << "\n";
  }

  return 0;
}
```

---

## 作者：Mirage_Insane (赞：4)

## 大致题意

给定 $n$ 堆石子，第 $i$ 堆有 $a_i$ 个。对于每次操作，玩家可以选择任意一堆石子，设其还剩 $x$ 个，若玩家可以从中取走 $y$ 个，当且仅当 $\gcd(x, y)$ 为 1。不能取石子的人输，问先手是否必胜。

## 题解

一眼博弈论，进一步发现属于公平组合游戏，于是转换成有向图游戏，使用 SG 定理。[不会的戳这里](https://oi.wiki/math/game-theory/impartial-game/#%E6%9C%89%E5%90%91%E5%9B%BE%E6%B8%B8%E6%88%8F%E4%B8%8E-sg-%E5%87%BD%E6%95%B0)。

考虑求出每个数的 SG 值。假设当前只有一个数，显然 0 先手必败；1 先手必胜；2 先手必败，因为先手只能取 1，然后后手就取完了。于是初始化：

$$SG(0) = 0,\ SG(1) = 1,\ SG(2) = 0$$

再设当前数为 $x$ ($x \geq 3$)，当 $x$ 为质数时，显然 $y$ 可以是 1 到 $x - 1$ 的任意数，有：

$$SG(x) = \operatorname{mex}_{y = 1} ^ {x - 1}\{SG(y)\} $$

进一步发现他的值就是他为第几个质数。

若 $x$ 为合数，根据游戏的定义，有：

$$SG(x) = \operatorname{mex}_{y = 1}^{x - 1}\{SG(x - y)\}$$，其中 $\gcd(x, y) = 1$。

打表发现设 $x$ 最小的质因数为 $p$， 则 $SG(x) = SG(p)$。

用欧拉筛提前预处理出所有数的 SG 值，然后用 SG 定理就结束了。

### Code:

```cpp
#define Vanishment return
#define This 0
#define World ;
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
int sg[10000005], tot, a[10000005];
bool flag[10000005];
void init() {
    sg[0] = 0;
    for(int i = 2; i <= 10000000; i++) {
        if(!flag[i]) a[++tot] = i, sg[i] = tot;
        sg[1] = 1, sg[2] = 0;
        for(int j = 1; j <= tot; j++) {
            if(i * a[j] > 10000000) break;
            flag[i * a[j]] = 1;
            sg[i * a[j]] = sg[a[j]];
            if(i % a[j] == 0) break; 
        }
    }
}  
int main() {
    init();
    int T;
    SF("%d", &T);
    while(T--) {
        int n, x, ans = 0;
        SF("%d", &n);
        for(int i = 1; i <= n; i++) {
            SF("%d", &x);
            ans ^= sg[x];
        }
        PF(ans ? "Alice\n" : "Bob\n");
    }
    Vanishment This World
}
```

---

## 作者：Defy_HeavenS (赞：2)

# 题意
Alice 和 Bob 玩游戏，一开始有 $n$ 堆石子，其中第 $i$ 堆有 $a_i$ 颗石子。两个玩家轮流取石子，在一个玩家的回合里，它可以取走任意一堆的任意正数个石子，并满足取石子的数量不能与当前堆的石子数量为互质。

无法再取石子的人输。假设两人都足够聪明，Alice 先取谁会赢？

# 思路
博弈论，构建 SG 函数。

考虑单堆情况，当个数 $x$ 为偶数时没有先手必胜策略，而 $x$ 为奇数时仅需一步取走 $x-2$ 个石子即可。

暴力转移肯定超时，因为要满足**取石子的数量不能与当前堆的石子数量为互质**，所以考虑质数。我们打一下表发现现象：
1. $SG(0)=0,SG(1)=1$ ~~这不显然吗~~。
2. 对于所有偶数，$SG=0$。
3. 对于所有奇数质数 $x$，满足 $\forall 1\le i<x,\gcd(x,i)=1$，则 $SG(x)=\mathrm{mex}(1,2,\dots,x-1)=SG(x')+1$，其中 $x'$ 为上一个质数（特殊地，$SG(3)=2$），也可以理解为 $x$ 在质数中的排名。
4. 对于所有奇数 $x$，设其最小质因子为 $x'$，那么 $SG(x)=SG(x')$。

仅需通过线性筛，对于每个数求得其最小质因子，即可求得所有 $SG$ 函数，则仅需判断 $SG⁡(a_1)\oplus SG(a_2) \oplus \dots \oplus SG⁡(a_n)\ne0$ 是否成立即可。

## 证明
采用数学归纳法证明。

首先对于 $x\le 2$ 成立，考虑 $x+1$。

- 对于 $x+1$ 是质数，并且其是第 $i$ 个质数，那么 $[1,x]$ 就是其后继状态，然后 $[1,i-1]$ 一定在之前出现过，所以 $SG(x+1)=i$。
- 对于 $x+1$ 是偶数，对于一个数 $y$，若 $\gcd(x,y)=1$ 那么 $y$ 一定是奇数，$x+1-y$ 一定是奇数，$[1,x]$ 中奇数都不为 $0$，所以 $SG(x+1)=0$。
- 对于 $x+1$ 是奇数，其某个质因子 $p$，那么 $p$ 的倍数一定不能减去，并且 $[1,x]$ 中的 $y$ 满足 $SG(y)=SG(p)$ 的一定有 $p\mid y$，所以 $SG(x+1)<SG(p)$，然后 $SG(p)$ 最小的那个就是最小质因子的 $SG$。

Q.E.D.

# 代码
赛时代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double D;
const int N=3e5+5,M=1e7+5;
LL n,a[N],cnt,prim[M],mifac[M],sg[M];    //mifac[i] 表示 i 的最小质因子 
bool vis[M];
void get_prime(int n){
    for(int i=2;i<=n;++i){
        if(!vis[i]) prim[++cnt]=i,mifac[i]=i;
        for(int j=1;j<=cnt;++j){
            if(i*prim[j]>n) break;
            vis[i*prim[j]]=1;
            mifac[i*prim[j]]=prim[j];
            if(i%prim[j]==0){
				break;
			}
        }
    }
}
void solve(){
	cin>>n;
	LL sum=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum^=sg[a[i]];
	}
	if(sum){
		cout<<"Alice";
	}else{
		cout<<"Bob";
	}
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	get_prime(10000005);
	sg[1]=1,sg[2]=0;
	for(int i=3,cnt=1;i<=10000001;i++){
		if(!vis[i]) cnt++;
		sg[i]=sg[mifac[i]];
		if(!vis[i]){
			sg[i]=cnt;
		}
	}
	int t=1;cin>>t;
	while(t--) solve();
	return 0;
}
/*

*/
```

---

## 作者：liruixiong0101 (赞：1)

这篇题解先讲如何思考，在讲证明。

发现这是一个公平组合游戏（ICG），考虑 SG 定理。

首先有 $sg_0=0,sg_1=1$，打一个暴力出来发现前几项是：`0 1 0 2 0 3 0 4 0 2 0`，发现偶数的 sg 函数等于 $0$，这让我们想要知道每一个质数的倍数的 sg 函数有什么规律：$sg_3=2,sg_9=2,sg_{15}=2,\cdots$（这里舍去偶数，因为肯定是 $0$）我们发现这些数的 SG 函数都是 $2$。舍去 $2,3$ 的倍数看 $5$ 的倍数的 SG 函数，发现其都是 $3$。到这里我们就有一个结论：
- 若数为偶数，则 SG 函数是 $0$；
- 若数为 $1$，则 SG 函数是 $1$；
- 否则 SG 函数就是其最小的质因子在质数表中的位置。

运用这个结论，通过线性筛筛出每一个数的 SG 函数，最后每次询问将输入的数的 SG 函数异或起来，看其是否为 $0$ 即可。

代码还是很简单的，不放了。

---

下面是证明，使用数学归纳法。

先证偶数的 SG 函数是 $0$，且非偶数的 SG 函数非 $0$。

> 首先结论对 $x=0,1$ 成立，接下来考虑归纳到了 $x-1$。
> - 若 $x$ 为偶数，则不能选出 $y$ 个石子且 $y$ 为偶数，那么转移到 $sg_x$ 的每一个数的 SG 函数都非零，那么就有 $sg_x=0$。
> - 若 $x$ 为奇数，则肯定能选出 $y$ 个石子且 $y$ 为偶数，同理就有 $sg_x\neq 0$。
> 
> 证毕。

再证非偶数且非 $1$ 的数的 SG 函数为其最小质因子在质数表中的位置。

> 我们对于每一个质因子 $p>2$ 进行归纳。
>
> 对于每一个以 $p$ 为最小质因子的数 $x$，肯定能在其中选出 $1,2$ 个石子，且可以选出 $p_2=3,p_3=5,\cdots,p_{r-1}\le x$ 个石子（其中 $r$ 为 $p$ 在质数表中的排名），那么转移到 $sg_x$ 的数的 SG 函数的值肯定包括 $0,1,\cdots,r-1$，那么就有 $sg_x=r$。
>
> 证毕。

---

## 作者：鲤鱼江 (赞：1)

看到是公平组合游戏，每堆石子独立，马上能够想到 SG 函数。

考虑到大部分 SG 函数是有规律的，进行打表寻找。

当然打表也是有技巧的，先进行分析：这题明显发现质数的 SG 函数使其在质数中的排名，当然 $2$ 除外。其次本题和因数分解大概率有关系。

给出 $O(n^2\log n)$ 的打表程序：

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define cin Fastio :: cin
#define cout Fastio :: cout

const int N=1e5+10;
int f[N],n,vis[N],las;

int main(){
	cin>>n;cout<<0<<' '<<0<<'\n';
	for(int i=1;i<=n;++i){
		for(int j=1;j<=i;++j) if(__gcd(i,j)==1) vis[f[i-j]]=1;
		while(vis[f[i]]) ++f[i];
		for(int i=0;i<=n;++i) vis[i]=0;
		cout<<i<<' '<<f[i]<<'\n';
	}
	return 0;
}
```

拿出前二十五项输出：

```cpp
0 0
1 1
2 0
3 2
4 0
5 3
6 0
7 4
8 0
9 2
10 0
11 5
12 0
13 6
14 0
15 2
16 0
17 7
18 0
19 8
20 0
21 2
22 0
23 9
24 0
25 3
```

发现：

1. 质数符合最开始的猜想。
2. 偶数都是 $0$。

考虑常规地进行质因数分解，发现非质数时，其 SG 函数等于其最小质因子的 SG 函数，容易证明是对的，理由可以采取归纳。

然后 SG 函数可以线筛，给出最终代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

const int N=1e7+10;const int Max=5e5+10;
int f[N],flag[N],prime[N>>3],cnt,n,res,T;

inline void init(const int len){
	f[1]=flag[1]=1;
	for(int i=2;i<=len;++i){
		if(!flag[i]){prime[++cnt]=i;f[i]=(i==2)?0:cnt;}
		for(int j=1;j<=cnt&&i*prime[j]<=len;++j){
			flag[i*prime[j]]=1;
			f[i*prime[j]]=f[prime[j]];
			if(i%prime[j]==0) break;
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;init(10000000);
	while(T--){
		cin>>n;res=0;
		for(int i=1,x;i<=n;++i){cin>>x;res^=f[x];}
		cout<<(res?"Alice":"Bob")<<endl;
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

考虑 $sg_i$ 表示只有一堆 $i$ 个石子的 sg 函数，考虑如下结论：$sg_1=1,sg_2=0$，对于 $i>3$ 的质数 sg 函数等于它是第几个质数，合数的 sg 函数等于它的最小质因子的 sg 函数。证明如下：

- 对于质数 $k>3$，我们假设 $1\sim k-1$ 上述结论都是正确的，则因为 $k$ 与 $1\sim k-1$ 都互质，所以 sg 为它们的 sg 的最大值加一，而最大的 sg 显然是一个质数的 sg，所以是上一个质数的 sg 加一。而 $k=3$ 时 $sg_k=2$，所以成立。
- 对于合数 $x>4$，设它的最小质因数为 $p$，则必然有 $sg_i$ 能为 $sg_x$ 做贡献（$i<p$），而所有 $x$ 的后继中必不存在一个能整除它的数，故 $p$ 不能对 $x$ 有贡献，所以 $sg_x=sg_p$。而 $x=4$ 时 $sg_4=sg_2=0$，所以成立。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int sg[10000010];
bool np[10000010];
vector<int> pri;
void init()
{
	sg[1]=1;sg[2]=0;
	for(int i=2;i<=1e7;i++)
	{
		if(!np[i])
		{
			pri.push_back(i);
			if(i>2)
			sg[i]=pri.size();
		}
		int flag=0;
		for(auto p:pri)
		{
			if(1ll*p*i>1e7||flag) break;
			if(i%p==0) flag=1;
			sg[p*i]=sg[p];
			np[p*i]=1;
		}
	}
}
int main()
{
	init();
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			ans^=sg[x];
		}
		cout<<(ans?"Alice":"Bob")<<'\n';
	}
}

---

## 作者：yeyou26 (赞：0)

# CF2004
- 博弈论。  
- 注意到 ICG，直接上 SG 函数。  
- 观察或注意或打表发现：  
	- $SG(P)=rank(P)$；  
	- $SG(x)=SG(spf(x))$；  
	- $spf(x)\to$ $x$ 的最小质因子；  
- 考虑归纳证明：  
	- 显然 $P$ 的后继为 $1,2,3,4,\dots ,P-1$；  
	- 这些数的 SG 函数中，$rank(P)-1$ 肯定都出现过，且 $rank(P)$ 肯定没出现过（根据归纳的第二条结论）；  
	- 对于合数 $x$，显然 $x$ 的后继有 $1\dots spf(x)-1$ 且 $k\times spf(x)$ 一定不是 $x$ 的后继，根据归纳的第一条结论，不可能存在一个 SG 函数值为 $spf(x)$ 的后继；  
- 实现上，线筛筛出 $spf$ 然后把所有 $a_{i}$ 异或起来判零即可，也就是 SG 的板子。

---

## 作者：GY程袁浩 (赞：0)

这是一道好题！

### 前置知识

[博弈论与 SG 函数](https://www.cnblogs.com/PMpro/articles/18367892)

### 思路

有一种天真的做法是求出所有的 SG 值，但是这样的时间复杂度是 $O(V^2 \log V)$ 的。

但是，实际上，这可以启发我们，借用 CF 题解里的一个过程总结。

>1.编写一个能简单计算 SG 值的解决方案；

>2.运行它并生成 SG 函数的几个初值；

>3.尝试观察一些模式，并利用这些模式制定更快的计算 SG 函数的方法；

>4.在较大数字的 SG 值上验证您的模式，并/或尝试证明它们。

> 第三步可能是最困难的，生成的 SG 值太少可能会导致错误的结论。例如，SG 的前八个值是 $[1,0,2,0,3,0,4,0]$，考虑 $x$ 是偶数，则可能导致假设 $sg(x)=0$ 是偶数，考虑 $x$ 是奇数，则可能导致假设 $sg(x)=\frac{x+1}{2}$ 是奇数。然而，一旦计算出 $sg(9)$，这种方法就被打破了，因为 $sg(9)$ 不是 $5$ ，而是 $2$。

现在，你已经会如何求解 SG 值了，你可以先关掉这个文章，自己试试看！

现在将讲解如何求解 SG 值。

首先进行打表，找规律，表具体是这样的：

[表](https://www.luogu.com.cn/paste/7lgzj2np)

你同样可以自己对着这个表看看。

发现所有偶数的 SG 值都为 $0$。

考虑奇数，首先，是存在一个子序列从 $1$ 开始一直升序的对吧，但是不是全部都是，所以思考，到底哪些才不属于递增子序列。发现 $9、15、21$ 都不是，相信你已经知道了，就是合数奇数是不属于子序列的，但它们的值有什么规律呢？经过仔细思考后发现**它们的值都是自己最小的质因数的 SG 值**，若 $x=p_{1}^{c_{1}} \cdot ... \cdot p_{k}^{c{k}}$，它的 SG 值即为：

$$
\begin{aligned}
\min_{i \le k}\{sg(p_{i})\}
\end{aligned}
$$

现在问题来了，不可能对于每个 $a_{i}$ 都分解质因数啊。此时我们突然想到，它的质因数 SG 值是随质因数大小递增的，我们只需要找出那个数的最小质因数即可。此时我们知道线性筛实际上是用一个合数最小的质因数来筛掉它的，于是在线性筛的过程中记录即可。真是完美又热血的组合技啊！

对于奇数非合数，它的值就是自己是第几个奇数非合数，同样是在线性筛记录即可。

时间复杂度 $O(V + \sum_{i=1}^{q} n_{i})$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e7+5,M=3e5+5;
int sg[N],pre[N],ni[N];
vector<int> primes;
bool st[N];
void init(int n) {
	ni[1]=1;
	for(int i=2;i<=n;i++) {
		if(!st[i]) primes.push_back(i),ni[i]=(int)primes.size();
		for(int j=0;primes[j]<=n/i;j++) {
			st[i*primes[j]]=1;
			pre[i*primes[j]]=primes[j];
			if(i%primes[j]==0) break;
		}
	}
}
signed main() {
	init((int)1e7);
	int tt;
	cin>>tt;
	while(tt--) {
		int n,sum=0;cin>>n;
		for(int i=1;i<=n;i++) {
			int x;cin>>x;
			if(x%2) {
				if(!st[x]) sum^=ni[x];
				else sum^=ni[pre[x]];
			}
		}
		if(!sum) cout<<"Bob"<<endl;
		else cout<<"Alice"<<endl;
	}
	return 0;
}
```

---

