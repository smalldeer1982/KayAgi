# [ABC282F] Union of Two Sets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc282/tasks/abc282_f

本题为**交互式问题**（你的程序将与评测程序通过标准输入输出进行交互）。

你和评测程序将按照如下步骤进行操作。操作分为第 $1$ 阶段和第 $2$ 阶段，首先进行第 $1$ 阶段，紧接着进行第 $2$ 阶段。

（第 $1$ 阶段）

- 评测程序会给出一个整数 $N$。
- 你需要输出一个 $1$ 到 $50000$ 之间的整数 $M$。
- 此外，你还需要输出 $M$ 个整数对 $(l_1, r_1), (l_2, r_2), \ldots, (l_M, r_M)$，其中对于所有 $i = 1, 2, \ldots, M$，都有 $1 \leq l_i \leq r_i \leq N$。这些整数对可以重复。

（第 $2$ 阶段）

- 评测程序会给出一个整数 $Q$。
- 接下来，你和评测程序将重复以下操作 $Q$ 次：
  - 评测程序会给出两个整数 $L, R$ 作为一次查询。
  - 你需要输出两个 $1$ 到 $M$ 之间的整数 $a, b$（允许 $a = b$）。这两个数必须满足以下条件，否则判为不正确：
      - 集合 $\lbrace l_a, l_a+1, \ldots, r_a\rbrace$ 与集合 $\lbrace l_b, l_b+1, \ldots, r_b\rbrace$ 的并集，恰好等于集合 $\lbrace L, L+1, \ldots, R\rbrace$。

完成上述所有步骤后，程序应立即结束，否则判为不正确。

## 说明/提示

### 约束条件

- $1 \leq N \leq 4000$
- $1 \leq Q \leq 10^5$
- $1 \leq L \leq R \leq N$
- 所有输入均为整数。

### 注意事项

- **每次输出后请务必输出换行并刷新标准输出，否则可能会因超时（TLE）被判为错误。**
- **如果在交互过程中输出不合法，或程序中途退出，评测结果不确定。** 特别是，如果程序运行时发生运行时错误，评测结果可能不是 RE，而是 WA 或 TLE。
- 第 $2$ 阶段结束后请立即终止程序，否则评测结果不确定。
- 第 $2$ 阶段中给出的 $L, R$ 会根据你在第 $1$ 阶段输出的 $(l_1, r_1), (l_2, r_2), \ldots, (l_M, r_M)$ 决定。

### 输入输出样例

以下为 $N = 4, Q = 4$ 时的输入输出示例。

输入输出说明  
`4` 评测程序给出 $N$。  
`6` 你输出 $M$。  
`3 3` 你输出 $(l_1, r_1) = (3, 3)$。  
`4 4` 你输出 $(l_2, r_2) = (4, 4)$。  
`1 1` 你输出 $(l_3, r_3) = (1, 1)$。  
`2 4` 你输出 $(l_4, r_4) = (2, 4)$。  
`1 3` 你输出 $(l_5, r_5) = (1, 3)$。  
`2 2` 你输出 $(l_6, r_6) = (2, 2)$。  
`4` 评测程序给出 $Q$。  
`1 3` 第 $1$ 次查询，$L = 1, R = 3$。  
`1 5` 你输出 $a = 1, b = 5$。  
`3 4` 第 $2$ 次查询，$L = 3, R = 4$。  
`2 1` 你输出 $a = 2, b = 1$。  
`2 4` 第 $3$ 次查询，$L = 2, R = 4$。  
`4 4` 你输出 $a = 4, b = 4$。  
`1 1` 第 $4$ 次查询，$L = 1, R = 1$。  
`3 3` 你输出 $a = 3, b = 3$。

由 ChatGPT 4.1 翻译

# 题解

## 作者：yuyc (赞：5)

## 前言
在这里提供运用 ST 表思想但又略不同于 ST 表的构造方法，能够在 $n=4000$ 时相比 ST 表少构造将近 $4000$ 个区间。
## 解析

构造的思路是这样的：

设 $len$ 为询问的区间的长度，从小到大考虑。

当 $len=1$ 时，询问区间必定只能是相同的长度为一的区间的并，故对于所有 $1 \le i\le n$，必定需要构造一个 $[i,i]$ 的区间。

当 $len=2$ 时，询问区间可以通过先前构造的长度为 $1$ 的相邻两个区间取并得到。

当 $len=3$ 时，无法通过现有的区间得到询问区间，故对于所有 $1 \le i \le n-2$，构造一个 $[i,i+2]$ 的区间。

当 $4 \le len \le 6$ 时，可以发现询问区间可以通过两个长度为 $3$ 的区间取并得到。

事实上，如果我们构造了一连串的一个长度为 $i$ 的区间，那么对于所有 $i \le len \le i \times2$，询问区间都可以由两个长度为 $i$ 的区间取并得到。

具体地，对于满足 $i \le len \le i \times2$ 的一次询问 $L,R$，可以先选取一个以 $L$ 为左端点，长度为 $i$ 的区间，再选取一个以 $R$ 为右端点（即以 $L+len-i$ 为左端点），长度为 $i$ 的区间，取并得到询问区间。

这样，我们就只需要从长度为 $1$ 的区间开始构造，每次将长度乘 $2$ 再加 $1$。

通过这种方法构造出来的区间，第 $k$ 短的区间长度为 $2^k-1$，ST 表则是 $2^{k-1}$，并且，如果 $n$ 不等于 $2$ 的幂减 $1$，这种方法构造出来的不同区间长度的数量比 ST 表少 $1$，其余情况相等。

由此可见，当 $n \not = 1$ 时，此方法构造出来的区间的数量总是比 ST 表少。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4e3 + 5;
vector<int> v[N];//v[i][j]表示是否构造出长度第 i 短，左端点位于 j 的区间，
int s[N],lth[N];//s[i]表示构造出来的第 1 至第 i 短的区间个数
			//lth[i]表示第 i 短的区间的长度
int main(){
	int n,cnt = 0;
	cin>>n;
	for(int len = 1;len <= n;len = len * 2 + 1){
		cnt++;
		lth[cnt] = len;
		for(int l = 1;l + len - 1 <= n;l++){
			v[cnt].push_back(l);//存的东西不重要，能判断有没有构造出这个区间即可
		}
		s[cnt] = s[cnt - 1] + v[cnt].size();
	}
	cout<<s[cnt]<<endl;
	for(int i=1;i<=cnt;i++){
		for(int j : v[i]){
			cout<<j<<' '<<j + lth[i] - 1<<endl;
		}
	}
	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		int len = r - l + 1;
		int t = upper_bound(lth,lth + cnt + 1,len) - lth - 1;
		cout<<s[t - 1] + l<<" "<<s[t - 1] + l + len - lth[t]<<endl;
	}
	return 0;
}

```

---

## 作者：StudyingFather (赞：4)

（看了官方题解，出题人确实是根据 ST 表的原理出了这样一道题）

回顾下 ST 表的原理：我们利用倍增预处理出以 $i$ 位置为左端点，包含 $2^j$ 个元素的区间的最值。对于 $[l, r]$ 区间最值的询问，我们适当选取 $k$，把其拆分为 $[l, l + 2^k - 1]$，$[r - 2^k + 1, r]$ 两个区间的最值，使得两个区间的并为原询问区间，直接合并两个区间的答案。

整个过程恰好与本题的任务相对应！只不过，在这个问题中，我们不需要查询最值，只需要在构建 ST 表的过程中给相应区间标号，并在询问时输出拆分后的两个查询区间编号即可。

```cpp
// Problem: F - Union of Two Sets
// Contest: AtCoder - HHKB Programming Contest 2022 Winter
// (AtCoder Beginner Contest 282)
// URL: https://atcoder.jp/contests/abc282/tasks/abc282_f
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cmath>
#include <iostream>
using namespace std;
int f[4005][15];
int main() {
  ios::sync_with_stdio(false);
  int n, cnt = 0;
  cin >> n;
  // 按道理这里循环应该是先 j 后 i
  // 不过这里不进行任何实际求值，就完全无所谓了
  for (int i = 1; i <= n; i++)
    for (int j = 0; i + (1 << j) - 1 <= n; j++) f[i][j] = ++cnt;
  cout << cnt << endl;
  for (int i = 1; i <= n; i++)
    for (int j = 0; i + (1 << j) - 1 <= n; j++)
      cout << i << ' ' << i + (1 << j) - 1 << endl;
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    int k = log2(r - l + 1);
    cout << f[l][k] << ' ' << f[r - (1 << k) + 1][k] << endl;
  }
  return 0;
}
```

---

## 作者：Hoks (赞：3)

## 前言
[题目链接](https://www.luogu.com.cn/problem/AT_abc282_f)，[传送门](https://www.luogu.com.cn/blog/Hok/solution-at-abc282-f)。
## 思路分析
难点主要不在于给出 $m$ 个序列，而是下一步的并集限定。

观察题目发现 $4000\times\log{4000}\le50000$，那我们便可以使用 ST 表的思想，把每个大区间分割成两个小部分表示。对于每个询问我们只要用两个区间给他覆盖即可。

**注意**：不知为什么我用快读和 scanf 会挂，只能用关流 cin 了（第一次写交互题）。
```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define int long long
#define lowbit(u) (u&-u)
#define ls (p<<1)
#define rs (p<<1|1)
#define len(p) (t[p].e-t[p].s+1)
using namespace std;
const int mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,q,cnt;
int f[4005][15];
//以下为板子
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int u(0),t(1);char fc(getchar());
    while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
    while(isdigit(fc)) u=(u<<1)+(u<<3)+(fc^48),fc=getchar();
    return u*t;
}
inline void print(int u)
{
	if(u<0) putchar('-'),u=-u;
	if(u>9) print(u/10);
	putchar(u%10+'0');
}
inline int ksm(int a,int b,int mod)
{
	int u=a%mod,res=1;
	while(b)
	{
		if(b&1) res=res*u%mod;
		b>>=1;u=u*u%mod;
	}
	return res;
}//以上是板子（之前写树剖和线段树的时候留下的懒得删了）
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
	    for(int j=0;i+(1<<j)-1<=n;j++)
			f[i][j]=++cnt;
	cout<<cnt<<'\n';
	for(int i=1;i<=n;i++)
	    for(int j=0;i+(1<<j)-1<=n;j++)
			cout<<i<<" "<<i+(1<<j)-1<<'\n';
	cin>>q;
	while(q--)
	{
	    int l,r;cin>>l>>r;
    	int k=log2(r-l+1);
    	cout<<f[l][k]<<" "<<f[r-(1<<k)+1][k]<<'\n';	
	}
	return 0;
}
```


---

## 作者：Pethly_Cat (赞：2)

看完这题的题面，应该不难想到 ST 表。

那么它和 ST 表有什么相似之处呢？原因有以下几点：

- ST 表的空间复杂度带一个 $\log$ 。而这题中 $N≤4000$ ，$N \log N≈47000≤50000$ 。

- 题目中给出的并集的条件，恰好与 ST 表询问时的拼凑思想相同。

于是我们就知道了构造区间的方法：对于每个 $1$ 到 $n$ 之间的数 $x$ ，构造出最多 $\log N$ 个区间，每个区间的形式为 $[x,x+2^i]$ 。

而在询问时，类似 ST 表的思想，查询出相应的区间，这道题就解决了。

**Code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int N=4e3+5;
vector<pair<int,int> > g[N];
//find 函数的含义为查询区间 [p,q] 的编号
int find(int p,int q){
	int l=0,r=g[p].size()-1,mid=0,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(g[p][mid].x>=q) r=mid-1,ans=mid;
		else l=mid+1;
	}
	return g[p][ans].y;
}
int main(){
	int n,len=0; scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;i+j-1<=n;j<<=1)
			g[i].push_back({i+j-1,++len});
	printf("%d\n",len);
	cout.flush();
	for(int i=1;i<=n;i++)
		for(auto x:g[i]){
			printf("%d %d\n",i,x.x);
			cout.flush();
		}
	int Q; scanf("%d",&Q);
	while(Q--){
		int l,r; scanf("%d%d",&l,&r);
		int x=log2(r-l+1);
		int l1=l,r1=l+(1<<x)-1,l2=r-(1<<x)+1,r2=r;
		int c1=find(l1,r1),c2=find(l2,r2);
		printf("%d %d\n",c1,c2);
		cout.flush();
	}
	return 0;
} 
```


---

## 作者：Hell0_W0rld (赞：2)

# abc282f 题解
在以往 f 里蒜简单的。

希望管理大大看到后把这题评绿 qwq……
## Part 1 题目大意
给定正整数 $N$，构造 $1\leq M\leq 50000$ 个区间，满足 $\forall i \in[1,M],[l_i,r_i]\in[1,N]$。输出 $M$ 和这 $M$ 个区间。之后给定 $Q$ 个询问 `L R`，求两个编号 $a,b$，使得 $[l_a,r_a]\cup[l_b,r_b]=[L,R]$。
## Part 2 前铺 - $\texttt{ST}$ 表
$\texttt{ST}$ 表是一种基于倍增实现的数据结构。可以在 $O(n\log n)$ 的时间内预处理，$O(1)$ 的时间查询。

$\texttt{ST}$ 表是这样的：

构造长度为 $\forall k \in [0,\lfloor \log n\rfloor]2^k$ 的区间。查询 $\texttt{RMQ}$ 的时候，利用区间拼凑的想法，把两段预处理好了的区间，拼接起来。

虽然有可能有重叠部分，但是计算 $\texttt{RMQ}$ 的时候有重叠也不要紧。

具体代码实现：（[P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)）：
```cpp
void build_ST(){
	int p=log(n)/log(2);
	for(int k=1;k<=p;k++)
		for(int i=1;i<=n-(1<<k)+1;i++)
			st[k][i]=max(st[k-1][i],st[k-1][i+(1<<(k-1))]);
}
int rmq(int l,int r){
	int p=log(r-l+1)/log(2);
	return max(st[p][l],st[p][r-(1<<p)+1]);
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>st[0][i];
	while(m--){
		int l,r;
		cin>>l>>r;
		cout<<rmq(l,r)<<endl;
	}
}
```
## Part 3 solution
我莫名联想到了 $\texttt{ST}$ 表。$\texttt{ST}$ 表不正是用 $O(n)$ 个区间拼凑成 $[1,N]$ 中所有区间吗？$4000\log 4000\approx 48000<50000$，满足条件。只不过这里不需要用到区间最大值。具体我们不能使用上述代码的思维，不能直接读入 ${st}_{0,i}$。

我们使用 $id_{i,k}$ 也就是 $st_{i,k}$ 是几号区间，$l_i,r_i$ 如题所述。输出 `id[p][l] id[p][r-(1<<p)+1]`。也就是把上述 `st` 换成 `id`。
## Part 4 Code
$O(Q+N\log N)$，比最优解代码慢了 $35\text{ms}$。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
using namespace std;
void upd_s(ll&x,ll v){x=min(x,v);}
void upd_b(ll&x,ll v){x=max(x,v);}
const ll N=4009;
const ll LOG=20;
const ll K=50009;
ll n;
ll id[N][LOG];
ll L[K],R[K];
void segment(){
	ll p=log(n)/log(2);
	ll cnt=0;
	rep(k,0,p)
		for(ll i=1;i<=n-(1<<k)+1;i++){
			id[i][k]=++cnt;
			L[cnt]=i;
			R[cnt]=i+(1<<k)-1;
		}
	cout<<cnt<<endl;
	rep(i,1,cnt)cout<<L[i]<<" "<<R[i]<<"\n";
}
int main(){
	cin>>n;
	segment();
	ll q,l,r;cin>>q;
	while(q--){
		cin>>l>>r;
		ll p=log(r-l+1)/log(2);
		cout<<id[l][p]<<" "<<id[r-(1<<p)+1][p]<<endl; 
	}
	return 0;
}//位置换了哦
```

---

## 作者：minVan (赞：1)

**解题思路**

这题主要运用了 ST 表的思想，他让对任意 $[l,r]$ 都能被两个你输出的区间表示，不难想到把所有 $[l,l+2^k-1]$ 输出。令 $[p,f(k)]$ 表示区间 $[p,p+2^k-1]$，对于任意区间 $[l,r]$，必然能分解成 $\left[l,f\left(\left\lfloor\log_2(r-l+1)\right\rfloor\right)\right]$ 和 $\left[r-2^{\left\lfloor\log_2(r-l+1)\right\rfloor},f(\left\lfloor\log_2(r-l+1)\right\rfloor)\right]$。

由于 $\log$ 函数带一点常数，建议提前预处理 $\log_2x$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4005;
int n, f[N][15], h[N];
int main() {
  cin >> n;
  for(int i = 2; i <= n; i++) {
    h[i] = h[i >> 1] + 1;
  }
  int cnt = 0;
  for(int i = 1; i <= n; i++) {
    for(int j = 0; i + (1 << j) - 1 <= n; j++) {
      f[i][j] = ++cnt;
    }
  }
  cout << cnt << '\n';
  for(int i = 1; i <= n; i++) {
    for(int j = 0; i + (1 << j) - 1 <= n; j++) {
      cout << i << ' ' << i + (1 << j) - 1 << '\n';
    }
  }
  int q;
  cin >> q;
  while(q--) {
    int l, r;
    cin >> l >> r;
    cout << f[l][h[r - l + 1]] << ' ' << f[r - (1 << h[r - l + 1]) + 1][h[r - l + 1]] << '\n';
  }
  return 0;
}

```

---

## 作者：xu222ux (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc282_f)

本题是一道模板 **ST 表**。

默认您已会 ST 表，不会请移步[此题](https://www.luogu.com.cn/problem/P3865)。

ST 表是解决给定一个区间 $[l,r]$,问关于这个区间的问题。

咋解决呢？他会把区间 $[l,r]$ 拆成 $[l,l+2^k-1]$ 和 $[r-2^k+1,r]$。

因为 $[l,l+2^k-1]$ 和 $[r-2^k+1,r]$ 这两个区间的**并集**是区间 $[l,r]$。

## 思路

构建一个 ST 表，题目问区间 $[l,r]$ 的时候，就找 ST 表中的 $[l,l+2^k-1]$ 和 $[r-2^k+1,r]$ 这两个区间的编号。

## code

```cpp
//马蜂丑
#include<bits/stdc++.h>
using namespace std;
int n;
int f[4003][20];
map<pair<int,int>,int>mp;
void it_st(){
	int t=log2(n),cnt=0;
	for(int i=1;i<=n;i++)f[i][0]=i;
	for(int j=1;j<=t;j++){
		for(int i=1;i<=n-(1<<j)+1;i++){
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
			cnt++;
		}
	}
	cout<<cnt+n<<endl;
	cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=t;j++){
			if(f[i][j]==0)break;
			cout<<i<<' '<<pow(2,j)+i-1<<endl;
			mp[{i,pow(2,j)+i-1}]=++cnt;
		}
	}
}
void ans(int l,int r){
	int k=log2(r-l+1);
	cout<<mp[{l,l+pow(2,k)-1}]<<' '<<mp[{r-(1<<k)+1,r}]<<endl;
}
int main(){
	cin>>n;
	it_st();
        cin>>n;
	while(n--){
		int l,r;cin>>l>>r;
		ans(l,r);
	}
	return 0;
}
```

---

## 作者：ABookCD (赞：0)

我的 ABC282 全场题解：[link](https://www.cnblogs.com/arizonayyds/articles/abc282.html)

## ABC282F [Union of Two Sets](https://atcoder.jp/contests/abc282/tasks/abc282_f) (Diff. 1,604)

### Solution:

显然每个端点都得有开始的线段。

很容易想到回答询问的时候大概是左边一个区间，右边一个区间拼起来。

想到 ST 表的结构，我们倍增构造，每一个 $st[i][j]$ 表示以 $i$ 为开始，$2^j$ 为长度，安排一个线段。

查询也是类似于 ST 表。

还需要考虑线段条数的限制。

当 $n=4,000$ 时，打表可得线段条数为 $43,917$，满足条件。

###  Code:

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int st[4010][13];
int lg[4010],cnt;
void query(int x,int y){
	int lga=lg[y-x+1];
	cout<<st[x][lga]<<" "<<st[y-(1<<lga)+1][lga]<<endl;
	cout.flush();
}
int n;
int ql[50010],qr[50010];
signed main(){
	cin>>n;
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int j=0;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=++cnt;
			ql[cnt]=i,qr[cnt]=i+(1<<j)-1;
		}
	}
	cout<<cnt<<endl;
	cout.flush();
	for(int i=1;i<=cnt;i++){
		cout<<ql[i]<<" "<<qr[i]<<endl;
		cout.flush();
	}
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r;
		query(l,r);
	}
	return 0;
}
```




---

## 作者：luogu_gza (赞：0)

本道题目的原理就是 ST 表。

可以发现，我们需要两个区间来“合成”一个给定区间。

这不就是 ST 表的基本操作吗？

$[l,r]$ 这个区间可以用 $[l,l+2^k-1]$ 和 $[r-2^k+1,r]$ 两个区间得到，其中 $k$ 是 $\lfloor log_{2}(r-l+1) \rfloor$ 。

可以轻松写出代码：

抱歉，我的代码中有些许我的缺省源，比如说 ```fo``` 就是正向循环。

代码风格不喜勿喷。

```cpp
const int N=4010,K=20;
int n,q,cnt;
int ma[N][N];
signed main(){
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    cin>>n;
    fo(i,1,n) for(int j=0;i+(1<<j)-1<=n;j++) ma[i][j]=++cnt; 
    cout<<cnt<<'\n';
    fo(i,1,n) for(int j=0;i+(1<<j)-1<=n;j++) cout<<i<<' '<<(i+(1<<j)-1)<<'\n';
    cin>>q;
    wh(q)
    {
        int l,r;
        cin>>l>>r;
        int k=log2(r-l+1);
        cout<<ma[l][k]<<' '<<ma[r-(1<<k)+1][k]<<'\n';
        fflush(stdout);//交互题记得冲马桶
    }
    return 0;
}
```



---

## 作者：shinzanmono (赞：0)

# 题意：
让你你给出交互库一些数对 $(l_i,r_i)(1\leq l_i\leq r_i\leq n)$，不得大于 $50000$ 个，每次询问给出两个正整数 $L,R$，请选出两个数对 $(l_i,r_i), (l_j,r_j)$ 使得 $[l_i,r_i]\cup[l_j,r_j]=[L,R]$。

# Solution:
考虑数据范围：$1\leq n\leq4000$，如果考虑枚举所有满足条件的数对，那么一共有 $\frac{n(n+1)}2>50000$，显然不满足题意。

稍加计算，发现 $n\log_2n$ 的最大值和 $50000$ 比较相近，所以我们考虑倍增算法。

我们来想一下 ST 表，ST 表的原理是：$f_{i,j}$ 维护了区间  $[j,j+2^i-1]$ 的 $\operatorname{op}$ 值（$\operatorname{op}$ 指一种操作） 当查询区间 $[l,r]$ 的时候，只需要查询 $\operatorname{op}(f_{\lfloor \log_2(r-l+1)\rfloor,l},f_{\lfloor\log_2(r-l+1)\rfloor,r-2^{\lfloor\log_2(r-l+1)\rfloor}+1})$。

这题时需要你求出两个区间是的两个区间的并是第三个区间，我们可以像 ST 表一样，对于每一个 $i$ 满足 $1\leq i\leq n$ 求出所有的 $[j,j+2^k-1](k\in\mathbb{N^+})$，然后对于每个查询操作，令 $k=\lfloor \log_2(R-L+1)\rfloor$，找出区间 $[L,L+2^k-1]$ 与 $[R-2^k+1,R]$，输出编号即可。

# CODE：
```cpp
#include<iostream>
#include<map>
std::map<std::pair<int, int>, int> dict;
int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    int id = 0;
    for (int j = 0; j <= std::__lg(n); j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            dict[std::make_pair(i, i + (1 << j) - 1)] = ++id; // 记录每个区间的编号
    std::cout << id << std::endl; // 输出区间的个数
    for (int j = 0; j <= std::__lg(n); j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            std::cout << i << " " << i + (1 << j) - 1 << std::endl; // 输出区间
    int q;
    std::cin >> q;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        int lg = std::__lg(r - l + 1); 
        std::cout << dict[std::make_pair(l, l + (1 << lg) - 1)] << " "
                  << dict[std::make_pair(r - (1 << lg) + 1, r)] << std::endl; // 查找区间
    }
    return 0; // 完结撒花
}

```

## 注意：这是一道交互题，别忘了输出后清空缓冲区。

---

## 作者：CarroT1212 (赞：0)

### 题目大意

这是一道交互题。

首先输入数据会给定一个整数 $N$，你需要选定一个整数 $M(1 \le M \le 50000)$，并构造两个长度为 $M$ 的数列 $l,r$，并将 $M$ 和这两个数列输出。输出完成后，数据会给定一个整数 $Q$ 和 $Q$ 次询问，每次询问给定两个整数 $L,R$。对于每次询问，你要输出两个数 $a,b$，使得集合 $\{l_a,l_a+1,\cdots,r_a\}$ 和 $\{l_b,l_b+1,\cdots,r_b\}$ 的并集恰好是 $\{L,L+1,\cdots,R\}$。

数据范围：$1 \le N \le 4000$，$1 \le Q \le 10^5$，$1 \le L \le R \le N$。

------------

### 解法分析

显然的是我们不能把 $[1,1],[2,2],\cdots,[N,N],[1,2],\cdots,[N-1,N],[1,3],\cdots,[N-2,N],\cdots,[1,N]$ 全部输出一遍，$M$ 会达到 $N^2$ 级别，不满足条件。

首先思考一下 $4000$ 和 $50000$（$N,M$ 最大值）有什么关系。

不难发现 $4000\times \log_2 4000 \approx 50000$。那我们就可以尝试往一些带 $\log$ 的做法去想。

然后再看看题面，两个连续整数区间放在一起，重叠一部分，得到一个给定的新区间，带 $\log$……

这想不到 ST 表就有点不太合理了。

于是我们可以把前面输出 $l,r$ 数列的过程看作是初始化一个长度为 $N$ 的数组的 ST 表数组的过程，只是每次遍历到一个区间就要输出区间的左右端点，另外输出的时候还要记录每个区间是在第几个输出的。此时 $M$ 约等于 $N \log N$，炸不了。后面询问的时候就可以按 ST 表查询的方法输出两个区间对应的编号。

具体看代码。

------------

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pll pair<ll,ll>
using namespace std;
const ll N=5e4+7;
ll n,l[N],r[N],cnt,q,mp[4007][21];
int main() {
	scanf("%lld",&n);
	for (ll i=0;1<<i<=n;i++) for (ll j=1;j+(1<<i)-1<=n;j++) // 输出的区间就是我们平常写 ST 表初始化到的区间
		l[++cnt]=j,r[cnt]=j+(1<<i)-1,mp[j][i]=cnt;
	printf("%lld\n",cnt),fflush(stdout);
	for (ll i=1;i<=cnt;i++) printf("%lld %lld\n",l[i],r[i]),fflush(stdout);
	scanf("%lld",&q);
	for (ll x,y,s;q--;)
		scanf("%lld%lld",&x,&y),s=log2(y-x+1),
		printf("%lld %lld\n",mp[x][s],mp[y-(1<<s)+1][s]),fflush(stdout); // 就按着 ST 表查询的方法输出
	return 0;
}
```

---

