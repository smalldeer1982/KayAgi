# [ABC377E] Permute K times 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc377/tasks/abc377_e

$ (1,2,\ldots,N) $ の並べ替え $ P=(P\ _\ 1,P\ _\ 2,\ldots,P\ _\ N) $ が与えられます。

次の操作を $ K $ 回行います。

- $ i=1,2,\ldots,N $ に対して**同時に** $ P\ _\ i $ を $ P\ _\ {P\ _\ i} $ で更新する
 
すべての操作を終えたあとの $ P $ を出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10^5 $
- $ 1\leq\ K\leq10^{18} $
- $ 1\leq\ P\ _\ i\leq\ N\ (1\leq\ i\leq\ N) $
- $ P\ _\ i\neq\ P\ _\ j\ (1\leq\ i\lt\ j\leq\ N) $
- 入力はすべて整数
 
### Sample Explanation 1

それぞれの操作によって、$ P $ は次のように変化します。 - $ 1 $ 回目の操作の結果、$ P=(2,4,3,5,6,1) $ となります。 - $ 2 $ 回目の操作の結果、$ P=(4,5,3,6,1,2) $ となります。 - $ 3 $ 回目の操作の結果、$ P=(6,1,3,2,4,5) $ となります。 よって、`6 1 3 2 4 5` を出力してください。

### Sample Explanation 2

$ P\ _\ i=i $ なので、何度操作を行っても $ P $ は変化しません。

## 样例 #1

### 输入

```
6 3
5 6 3 1 2 4```

### 输出

```
6 1 3 2 4 5```

## 样例 #2

### 输入

```
5 1000000000000000000
1 2 3 4 5```

### 输出

```
1 2 3 4 5```

## 样例 #3

### 输入

```
29 51912426
7 24 8 23 6 1 4 19 11 18 20 9 17 28 22 27 15 2 12 26 10 13 14 25 5 29 3 21 16```

### 输出

```
18 23 16 24 21 10 2 27 19 7 12 8 13 5 15 26 17 4 3 9 1 22 25 14 28 11 29 6 20```

# 题解

## 作者：Sih_qwq (赞：8)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc377_e) && [AT 链接](https://atcoder.jp/contests/abc377/tasks/abc377_e)。

手摸了一个晚上，一天后才敲的代码，~~最后肚子痛，一只手捂着肚子另一只手把题过了~~。

## 思路

令序列为 $\{a_i\}(1 \le i \le n)$。

首先，我们要对样例进行手摸。

例如第一个样例：

原序列为：

$$5 \, 6 \, 3 \, 1 \, 2 \, 4$$

置换依次为：


$$2 \, 4 \, 3 \, 5 \, 6 \, 1 \\ 4 \, 5 \, 3 \, 6 \, 1 \, 2 \\ 6 \, 1 \, 3 \, 2 \, 4 \, 5 \\ 5 \, 6 \, 3 \, 1 \, 2 \, 4$$

我们又回到了原序列。

发现这个序列中，除了 $3$ 以外的元素都会轮番置换。

由小学数学老师教的方法，用笔在当前第 $i$ 数 $a_i$ 与他要到达的第 $a_i$ 个数之间画一个箭头。

由于我们有注意力，我们发现这些箭头形成了一个环。因为序列 $\{a_i\}$ 为排列，不重复，有一个数和另一个数换，最后总有一个数需要顶替这个数的位置，所以成环。

所以这个序列我们就可以看成有 $tot$ 个环，若 $a_i=i$，则这个数看做自环。

于是我们猜想与循环节有关。但是 $n$ 范围较大，会超时。

考虑 $k$ 要怎么处理。继续手摸样例。

我们令第一次置换后序列为 $b_i$，则 $b_i = a_{a_i}$。

令第二次置换后序列为 $c_i$，则 $c_i = b_{b_i} = a_{a_{a_{a_i}}}$。

第三次自行手摸。

容易发现这玩意像套娃一样，每次套的 $a$ 都翻倍，于是得出操作 $k$ 次后会套 $2^k$ 个 $a$。

而对于每个数的套娃，都只会在他所在环上，每套 $1$  个 $a$ 都表示在换上走一步。不理解的可以手摸。

综上，我们可以得出，对于每个数，置换 $k$ 次后得到的数是这个数在环上走 $2^k$ 步后的数。

于是就可以写代码了，dfs 求环，记录环上每一个数和每个环长度，快速幂计算 $2^k$ 对环长度取模的答案，直接计算每个位置的答案。

## AC Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200010
#define ll long long
vector < int > g[N];
int n, bel[N], pos[N], len[N], ans[N], a[N], tot;
ll k;
map < int, int > hu[N];
bool vis[N];
// _id 是第 _id 个环，dep 没用，本来想用这个记录环长度的
void dfs(int x, int fa, int dep, int _id) {
//	cout << x << " " << fa << endl;
	bel[x] = _id;              // 每个数属于第 _id 个环
	hu[_id][++len[_id]] = x;   // 记录第 _id 个环上每个点，len 是每个环的长度
	pos[x] = len[_id];         // 记录当前第 x 个点在环上的位置
	if (vis[x]) return ;
	vis[x] = 1;   // 标记以访问
	for (int y : g[x])
		if (!vis[y]) dfs(y, x, dep + 1, _id);
}
ll fast_pow(ll base, ll power, ll _p) {
	ll res = 1;
	for (; power; power >>= 1, base = base * base % _p)
		if (power & 1) res = res * base % _p;
	return res % _p;
}
// 快速幂
int main() {
	scanf("%d %lld", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) {
		g[i].push_back(a[i]);
		g[a[i]].push_back(i); // 建图（画箭头）
	} 
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) dfs(i, i, 0, ++tot); // tot 表示环的数量
	for (int i = 1; i <= n; ++i) {
		int _p = len[bel[i]];                 // 以长度为模数
		ll bu = fast_pow(2, (ll)k, (ll)_p);   // 在环上走的步数
		int id = (pos[i] + bu) % len[bel[i]]; // 走到第 id 个数
		ans[i] = hu[bel[i]][id ? id : len[bel[i]]];   // 特判取模后变成 0 的情况
	//	cout << _p << " " << bu << endl;
	} 
	for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：ZhaoV1 (赞：4)

看见 Permutation（排列）字样，意味着很可能要从多个环入手做题，对于这题而言正中靶心。老样子，将 $a_{i}$ 指向 $a_{a_{i}}$，由于这是一组排序，所以经过不断地指向，箭头一定会绕为一个环，例如：

```
样例
第0次 5 6 3 1 2 4
第1次 2 4 3 5 6 1
第2次 4 5 3 6 1 2
第3次 6 1 3 2 4 5
第4次 5 6 3 1 2 4
...
```
环的图像为：![](https://cdn.luogu.com.cn/upload/image_hosting/lnswgoyg.png)
第一列：  
$5$  
$2$  
$4$  
$6$  
$5$  
发现由 $5$ 变为 $2$，从该值位置向箭头方向走了 $1$ 步；$2$ 变为 $4$，从上一个位置走 $2$ 步；$4$ 变为 $6$ 走 $4$ 步；$6$ 变为 $5$ 走 $8$ 步。

总结规律，若要一个数按题目要求变换 $k$ 次，那么它的值将变为它向箭头方向走 $2^k-1$ 步的值。而由于这是一个环，我们所走的步数只需对该环的总步数进行取模即可。

---

## 作者：FFTotoro (赞：3)

考虑 $K=1$ 时，同时进行 $P_i\leftarrow P_{P_i}$ 相当于进行一次排列复合 $P\leftarrow P\circ P$；如果 $K=2$，就是 $P\leftarrow (P\circ P)\circ(P\circ P)$，由于 $\circ$ 具有结合律，定义 $P^k$ 为 $k$ 个 $P$ 依次复合形成的结果 $\begin{matrix}\underbrace{P\circ P\circ\cdots\circ P}\\k\end{matrix}$，则上面的结果等价于 $P^4$……以此类推，走 $K$ 步的结果就是 $P^{2^K}$。

考虑建图，连边 $i\to P_i(1\le i\le N)$，可以见得最终的图是一些环。于是把每个环找出来，答案就相当于从 $i$ 开始走 $2^K$ 步走到的位置。由于 $2^K$ 很大，我们将其对环长取模之后进行处理：这一部分可以使用快速幂解决。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int qpow(int a,int b,int m){
  int r=1;
  while(b){
    if(b&1)(r*=a)%=m;
    (a*=a)%=m,b>>=1;
  }
  return r;
}
main(){
  ios::sync_with_stdio(false);
  int n,k; cin>>n>>k;
  vector<int> p(n),r(n);
  for(auto &i:p)cin>>i,i--;
  vector<bool> b(n);
  for(int i=0;i<n;i++)
    if(!b[i]){
      vector<int> v;
      for(int x=i;!b[x];x=p[x])
        b[x]=true,v.emplace_back(x);
      int d=qpow(2,k,v.size());
      for(int i=0;i<v.size();i++)
        r[v[i]]=v[(i+d)%v.size()];
    }
  for(int i:r)cout<<i+1<<' ';
  cout<<endl;
  return 0;
}
```

---

## 作者：panxz2009 (赞：2)

观察 $P_i\rightarrow P_{P_i}$ 容易联想到环，考虑建图，对于每一个 $i$，向 $P_i$ 连边。

由 $P_i\ne P_j$ 可以得到建出的图一定是一个个独立的环。在环上向前走一步，相当于做一次 $i\rightarrow P_i$ 的操作。而做一次 $P_i\rightarrow P_{P_i}$ 的操作，相当于做两次 $i\rightarrow P_i$ 操作；做两次，相当于做四次 $i\rightarrow P_i$ 操作。不难发现，做 $K$ 次 $P_i \rightarrow P_{P_i}$ 操作，相当于做 $2^K$ 次 $i\rightarrow P_i$ 操作。那么对于每一个点记录下移动后的答案即可。
```cpp
// Problem: E - Permute K times 2
// Contest: AtCoder - TOYOTA SYSTEMS Programming Contest 2024（AtCoder Beginner Contest 377)
// URL: https://atcoder.jp/contests/abc377/tasks/abc377_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn = 2e5 + 10;
int n, ans[maxn], cnt, x;
LL k;
bool vis[maxn];
vector <int> G[maxn], cir[maxn];
void dfs(int x) {
	vis[x] = 1;
	cir[cnt].push_back(x);
	for(int y : G[x]) {
		if(vis[y]) continue;
		dfs(y);
	}
}
int qpow(int a, LL b, int mod) {
	int ans = 1;
	while(b) {
		if(b & 1) ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return ans;
}
int main(){
	scanf("%d%lld", &n, &k);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &x);
		G[i].push_back(x);
	}
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) ++cnt, dfs(i);
	}
	for(int i = 1; i <= cnt; i++) {
		int stp = qpow(2, k, cir[i].size());
		for(int j = 0; j < (int)cir[i].size(); j++) {
			ans[cir[i][j]] = cir[i][(j + stp) % cir[i].size()];
		}
	}
	for(int i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	return 0;
} 
```

---

## 作者：BYR_KKK (赞：1)

非常厉害的题。

数学归纳法不难证明答案的第 $i$ 个数是原来的第 $i$ 个数做 $2^K-1$ 次 $p_i=p_{p_i}$ 后 $p_i$ 的值。

套路地，$i\rightarrow p_i$ 建图，由于保证不存在 $p_i$ 相同，因此图就是由很多个环组成的。对于每一个环分别考虑，设环上有 $m$ 个点，那么对于环上点做 $2^K-1$ 次 $p_i=p_{p_i}$ 后的结果显然等价于将 $2^K-1$ 对 $m$ 取模后做操作。而操作实际上就是把环转一下，直接求即可。

时间复杂度 $O(n)$。

---

## 作者：CJ_Fu (赞：1)

## [ABC377E Permute K times 2](https://atcoder.jp/contests/abc377/tasks/abc377_e)

给你一个排列 $p_i$，每次操作**同时** $p_i=p_{p_i}$，求 $k$ 次操作后的 $p$ 数列。

$n\le 2\times 10^5,k\le 10^{18}$

考虑建图，连边 $i\to p_i$（本质上就是 $p_i\to p_{p_i}$），可以形成若干置换环，而每次操作将会 $p_i\to p_{p_i}\to p_{p_{p_{p_{i}}}}\to p_{p_{p_{p_{p_{p_{p_{p_{i}}}}}}}}\to \cdots$（$2^k$ 个 $p$），相当于在环上走了 $2^k$ 步到达的位置，直接上快速幂，对环长取模即可。时间复杂度 $O(n\log k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+7;
int n,k,p[maxn],rp[maxn];
vector<int>v[maxn];
int vis[maxn],colcnt;
int ans[maxn];
int qpow(int a,int b,int mod){
    int res=1;
    for(;b;b>>=1,a=a*a%mod) if(b&1) res=res*a%mod;
    return res;
}
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            colcnt++;
            for(int j=i;!vis[j];j=p[j]){
                v[colcnt].emplace_back(j);
                vis[j]=colcnt;
            } 
        }
    }
    for(int i=1;i<=colcnt;i++){
        int siz=v[i].size(),now=qpow(2,k,siz);
        for(int j=0;j<siz;j++){
            ans[v[i][j]]=v[i][(j+now)%siz];
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}
```

---

## 作者：cjh_trailblazer (赞：0)

[原题面](https://atcoder.jp/contests/abc377/tasks/abc377_e)
## 题目分析：
经典套路，对于 $p_i\rightarrow p_{p_i}$ 这个变化方式，不难发现 $p_i$ 序列中的一些数一定能够组成一个环，所以最后建出的图一定是若干个环。  
判断出这个，剩下的就好办了，直接判环快速幂跳 $2^k$ 就行了。
## [Code](https://atcoder.jp/contests/abc377/submissions/59220667)

---

## 作者：kczw (赞：0)

# 题意
你有一个长为 $N\le2\times10^5$ 的序列 $P$，现在对其操作 $K\le10^{18}$ 次，每次操作对于所有 $i\in[1,N]$ 将 $P_i$ 修改为 $P_{P_i}$，求最终序列。
# 思路
肯定有人一眼觉得 $P$ 的可以看做图，然后操作就是图上点一步一步地跑~~我就是~~。看成图上问题是没有问题的，如果 $P$ 不变就是对的，但是这里的 $P$ 不断变化，也就意味着每次操作跑的图是不一样的。

我们分析一下样例中的一个 $P$：
```
5 6 3 1 2 4
```
会发现第一次操作可以看成以下图：
```
5->1 6->2 3->3
1->4 2->5 4->6
```
这里的 `5->1` 意思是第 $5$ 个数转移到第 $1$ 个位置。

那么当操作一次以后，$P$ 和图分别为：
```
2 4 3 5 6 1

2->1 4->2 3->3
5->4 6->5 1->6
```
这里只所以有 `2->1` 是由上一轮的 `2->5` 和 `5->1` 组合得来的，其他边同理。到这里，你应该会很容易联想到倍增，然后你会发现，其实每次图的变动就可以看作是在维护倍增。

怎么证明这是倍增呢，我们第一次操作时，$P_i$ 被修改为 $P_{P_i}$，其实也可以看成是第 $P_i$ 个值转移到了第 $i$ 位上。而第一次操作过后 $P_i(1\le i\le N)$ 变成 $P_{P_i}(1\le i\le N)$，带入第二次操作即将 $P_{P_i}$ 修改为 $P_{P_{P_{P_i}}}$，等同于把 $P_{P_{P_i}}$ 转移到 $P_i$ 上，把此处 $P_i$ 看作 $i$，也就是把 $P_{P_i}$ 转移到 $i$ 上。依次类推。

所以如果我们建图，第 $i$ 次操作时，点 $j$ 将要在最初 $P$ 的基础上经过 $2^{i-1}$ 条边，到达转移到的位置。对于前 $i$ 次操作的总经过边数就是 $2^0+2^1+…+2^{i-1}$，等比数列求和得 $2^i-1$。

所以操作 $k$ 次等同于求按照最初 $P$ 转移 $2^k-1$ 次后的 $P$ 序列。然后对于转移图不难知道其是由一堆环组成的，而在环上跑一圈等于没跑，所以环的大小可以作为模数，然后这里 $2^k-1$ 就可以快速幂处理。然后用倍增维护一个点转移 $2$ 的次幂后的位置即可。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=2e5+5;
int n,m,a[M],p[M][20],u,vis[M],stk[M],top,ans[M];
long long k,g;
inline int qkpow(int base,long long x,int mod,int res=1){
	while(x){
		if(x&1)res=1ll*res*base%mod;
		base=1ll*base*base%mod;
		x>>=1;
	}
	return res;
}
inline void solve(){
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		p[a[i]][0]=i;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=1;
			stk[top=1]=i;
			while(!vis[p[stk[top]][0]])
				stk[++top]=p[stk[top]][0];
			for(int l=1;l<=top;l++)vis[stk[l]]=1;//,printf("%d ",p[stk[l]][0]);puts("");
			for(int j=1;j<=18;j++)
				for(int l=1;l<=top;l++)
					p[stk[l]][j]=p[p[stk[l]][j-1]][j-1];
			m=(qkpow(2,k,top)+top-1)%top;
			for(int l=1;l<=top;l++){				
				u=stk[l];
				for(int j=18;j>=0;j--)
					if(m>>j&1)
						u=p[u][j];
				ans[u]=a[stk[l]];
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
}
int main(){
	int t=1;//scanf("%d",&t);
	while(t--)solve();
	return 0;
}
```

---

## 作者：bryce (赞：0)

## [[ABC377E] Permute K times 2](https://www.luogu.com.cn/problem/AT_abc377_e)
### 思路
对于当前 $i$ 位置上一个数变换一次变为 $p_{p_i}$，$p_{p_i}$ 上的数变为 $p_{p_{p_i}}$，变换两次，$i$ 上的数就变为了 $p_{p_{p_{p_i}}}$，$p_{p_{p_i}}$ 上的数变为 $p_{p_{p_{p_i}}}$，以此类推，发现一个数会在自己的循环中变换 $2^k - 1$ 次，于是，找出这个循环，找到从当前这个数开始往后第 $2^k - 1$ 个数。
### 代码
```cpp
#include<iostream>
#include<vector>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 2e5 + 10;
int n, k;
int a[N], vis[N], pos[N];
vector<int> g[N];
void dfs(int u, int top){
    if (vis[u]) return;
    vis[u] = top;
    g[top].emplace_back(u);
    pos[u] = g[top].size();
    dfs(a[u], top);
}
int qpow(int a, int b, int mod){
    int ans = 1;
    while (b){
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

signed main(){
    n = read(), k = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++)
        if (!vis[a[i]]) dfs(a[i], a[i]);
    for (int i = 1; i <= n; i++){
        int mod = g[vis[a[i]]].size(), p = ((pos[a[i]] + qpow(2, k, mod)) % mod - 1 + mod) % mod;
        p = (p == 0 ? mod : p);
        cout << g[vis[a[i]]][p - 1] << ' ';
    }
    return 0;
}
```

---

