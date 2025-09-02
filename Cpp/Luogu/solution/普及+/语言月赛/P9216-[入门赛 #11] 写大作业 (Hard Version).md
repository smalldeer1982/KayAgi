# [入门赛 #11] 写大作业 (Hard Version)

## 题目背景

**本题与 Easy Version 的区别在于：输入的是数列而不是字符串，输入输出格式不同，数据规模不同**。


## 题目描述

扶苏为了写计算理论大作业已经 $36$ 小时没有合眼了。

为了能快点睡觉，扶苏找到了 $n$ 份文献，第 $i$ 份文献是一数列 $a_i$，她打算把这些文献组合起来。

具体来说，一共有两种操作：

- `1 x y`：把文献 $a_x$ 整体拼接到 $a_y$ 的后面，然后删除 $a_x$。
- `2 x y`：查询 $a_x$ 和 $a_y$ 是否**相似**。

我们保证在 `1 x y` 操作出现后，数列 $a_x$ **不会**出现在接下来的任何操作中。这就是说，操作 $1$ 至多有 $n-1$ 次。

**相似**的定义是：对两个数列 $a_x$ 和 $a_y$，如果存在一种重新排列 $a_x$ 的方法，使得重排后的 $a_x$ 和 $a_y$ 相等，则称 $a_x$ 和 $a_y$ **相似**。

例如，假设 $a_1 = 1,2$, $a_2 = 3,4$，$a_3 = 1,2,3,4$，则执行 `1 1 2` 后，$a_1$ 被删除，$a_2 = 3,4,1,2$，$s_3 = 1,2,3,4$；继续执行 `2 2 3` 后，因为可以把 $a_2$ 重排为 $1,2,3,4$，所以 $a_2$ 和 $a_3$ 相似。

注意，操作 $2$ 不会对数列做出实际修改。

## 说明/提示

### 样例解释

共有五次操作，它们的编号和回答情况如下：
| 编号 | 操作 | 回答 |
| :-: | :-: | :-: |
| $1$ | `1 1 2` | 不是查询操作|
| $2$ | `2 2 3` | 相似 |
| $3$ | `2 3 4` | 不相似 |
| $4$ | `2 2 4` | 不相似 |
| $5$ | `2 2 3` | 相似 |

可以看到，回答为**两数列相似**的询问的操作编号为 $2$ 和 $5$。它们的按位异或和是 $7$。故输出为 $7$。

### 数据规模与约定

对全部的测试点，保证 $1 \leq n \leq 10^5$，$1 \leq q \leq 5 \times 10^6$，$1 \leq m_i \leq 10^5$，$\sum_{i = 1}^n m_i \leq 5 \times 10^5$。数列里的元素都是不超过 $10^9$ 的非负整数。

数据保证数列元素的生成方式是：对一个数列，限定一个该数列元素大小的上界 $k$，然后在 $[0, k]$ 内均匀随机地生成 $m_i$ 个整数作为数列 $a_i$。注意，$k$ 不一定是 $10^9$。

## 样例 #1

### 输入

```
4 5
2 1 2
2 3 4
4 1 2 3 4
4 1 2 3 3
1 1 2
2 2 3
2 3 4
2 2 4
2 3 2```

### 输出

```
7```

# 题解

## 作者：一扶苏一 (赞：4)

# 【HASH】【P9216】写大作业

> 磕头：  
> 出题时不知道新科技，被随机 hash 老哥直接 $O(q)$ 爆标了，成了典题。这篇题解是 std 的启发式合并做法。

## Analysis

以下设 $m = \sum_{i = 1}^n m_i$。

首先思考『相似』的定义，容易发现数列 $a$ 和 $b$ 相似等价于任意整数在 $a$ 和 $b$ 中的出现次数相同。

于是考虑维护每个数字在每个数列里的出现次数，对每个数列开一个 map 存一下即可。如果两个数列对应的 map 相同，那么它们相似。

考虑合并两个数列，就是合并两个 map。注意到题意是合并完一个数列以后被合并的数列就被扔掉了，自然考虑启发式合并。合并两个 map 时，枚举较小的 map 里的元素，然后暴力做单点插入到另一个 map 中。注意到一个数字每被枚举到一次，它所属的集合大小至少翻倍，所以至多被枚举 $\log m$ 次。把所有数列都合并起来的复杂度就是 $O(m \log m)$。

接下来处理判定两个 map 相同，考虑 hash。为了迎合启发式合并的单点插入，我们的 hash 函数必须能直接计算单个数字的贡献。std 的做法是：对一个 map 定义 hash 函数 $f$，如果数字 $x$ 在数列里出现了 $y$ 次（即 map 里键值 $x$ 对应的权值是 $y$），那么对 $f$ 产生 $x^{ky}$ 的贡献。其中 $k$ 是规定的常量。std 里取了 $k = 1,2,3,4,5$。

在合并两个集合时，假设把 map $a$ 里的元素插入到 $b$ 中，$x$ 在 $a$ 里的权值是 $y_1$，在 $b$ 的权值是 $y_2$，那么对 $b$ 的 hash 函数的影响是：$- 2^{y_1} + 2^{y_1 + y_2}$。

数据保证了随机，没有卡自然溢出，直接用 unsigned long long 自然溢出 hash 值即可。

这样，我们可以在做启发式合并的同时 $O(\log m)$ 地维护 hash 值的变化，所以启发式合并的总时间复杂度就是 $O(m \log^2 m)$。同时可以 $O(1)$ 回答每次询问。所以算法的总时间复杂度为 $O(m \log ^2 m + q)$。

## Code
```cpp
#include "assert.h"
#include <map>
#include <iostream>

const int maxn = 100005;
const int maxJ = 5;

typedef unsigned long long int ull;

ull mpow(ull x, int y) {
  ull ret = 1;
  while (y) {
    if (y & 1) ret *= x;
    x *= x;
    y >>= 1;
  }
  return ret;
}

ull hash[maxJ][maxn];
std::map<int, int> rec[maxn];
bool oc[maxn];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  for (int i = 1, m, x; i <= n; ++i) {
    for (std::cin >> m; m; --m) {
      std::cin >> x;
      ++rec[i][x];
    }
    for (int j = 0; j < maxJ; ++j) {
      for (auto &[x, y] : rec[i]) {
        hash[j][i] += mpow(x, j * y);
      }
    }
  }
  int ans = 0;
  for (int i = 1, o, x, y; i <= q; ++i) {
    std::cin >> o >> x >> y;
    if (o == 2) {
      bool ret = true;
      for (int j = 0; j < maxJ; ++j) if (hash[j][x] != hash[j][y]) {
        ret = false; break;
      }
      if (ret) ans ^= i;
    } else {
      assert(oc[x] == false);
      oc[x] = true;
      if (rec[x].size() > rec[y].size()) {
        rec[x].swap(rec[y]);
        for (int j = 0; j < maxJ; ++j) std::swap(hash[j][x], hash[j][y]);
      }
      for (auto &[u, v] : rec[x]) {
        if (rec[y][u]) for (int j = 0; j < maxJ; ++j) hash[j][y] -= mpow(u, j * rec[y][u]);
        for (int j = 0; j < maxJ; ++j) hash[j][y] += mpow(u, v * j);
      }
    }
  }
  std::cout << ans << '\n';
}
```

---

## 作者：离散小波变换° (赞：4)

## 题解

如何判定两个序列可通过重新排列使得两数列相等？不妨想想有什么东西是和序列有关而又可以重新排列的。我们可以想到这样的一个多项式：

$$F_a(x)=(x+a_1)(x+a_2)\cdots(x+a_{n-1})(x+a_n)$$

那么如果 $F_a(x)=F_b(x)$，就说明 $a,b$ 可以通过重排变得相同。

但本题中我们显然不可能跑个分治 FFT 啥的（况且复杂度估计要炸）。因为我们只是要判定两个多项式是否相同，一种简便可靠的做法是，选取 $k$ 个不同的 $x$ 的值 $x_1,x_2,\cdots x_k$，分别带入两个多项式进行计算。那么两个多项式相同的一个必要条件显然是：

$$\begin{cases}F_a(x_1)=F_b(x_1)\cr F_a(x_2)=F_b(x_2)\cr\cdots \cr F_a(x_k)=F_b(x_k)\cr\end{cases}$$

然后考虑到写高精度复杂度还是会爆炸的，所以将等式两边同时对一个模数 $M$ 取模（不同的模数也行，反正也卡不掉，这里只是为了实现方便）。因此一个必要条件是：

$$\begin{cases}F_a(x_1)\equiv F_b(x_1) & \pmod M\cr F_a(x_2)\equiv F_b(x_2) & \pmod M\cr\cdots \cr F_a(x_k)\equiv F_b(x_k) & \pmod M\end{cases}$$

具体实现上，我们对于序列 $a$ 计算出一个序列 $H_a=\{F_a(x_1)\bmod M,F_a(x_2)\bmod M,\cdots,F_a(x_k)\bmod M\}$ 作为它的特征值（相当于哈希值）。判定两个序列 $a,b$ 是否可通过重新排列变得相等，只要判断 $H_a$ 和 $H_b$ 是否相等就行，正确率应该很高（~~我猜的~~）。复杂度是 $\mathcal O(k)$。

然后对于序列拼接操作，显然 $H_{a+b}=H_a\cdot H_b$，这是因为 $F_{a+b}(x)=F_a(x)F_b(x)$，把 $F$ 的定义式展开就能得到。所以复杂度仍然是 $\mathcal O(k)$。

总时间复杂度为 $\mathcal O(nk+qk)$。下面代码中取了 $k=30$。

经过实测即使 $k=1$ 也能通过所有数据……

## 代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = 5e5 + 3;
const int MAXM = 5e5 + 3;
const int MAXK = 30 + 3;
const int MOD  = 1e9 + 7;
int S[MAXN][MAXK], T[MAXK], k = 30, n, q;
mt19937 MT;
int main(){
    n = qread(), q = qread();
    uniform_int_distribution <int> U(0, MOD - 1);
    up(1, k, i) T[i] = U(MT);
    up(1, n, i){
        int m = qread();
        up(1, k, j) S[i][j] = 1;
        up(1, m, j){
            int a = qread();
            up(1, k, t)
                S[i][t] = 1ll * S[i][t] * (a + T[t]) % MOD;
        }
    }
    int ans = 0;
    up(1, q, i){
        int o = qread();
        if(o == 1){
            int x = qread(), y = qread();
            up(1, k, j)
                S[y][j] = 1ll * S[y][j] * S[x][j] % MOD;
        } else {
            int x = qread(), y = qread();
            bool flag = true;
            up(1, k, j)
                if(S[x][j] != S[y][j])
                    flag = false;
            if(flag) ans ^= i;
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Disjoint_cat (赞：2)

[传送门！](https://www.luogu.com.cn/problem/P9216)

## 写大作业

### Easy version

**声明：Easy version 与 Hard version 的解法完全不同，不感兴趣者可略过。**

#### 题意

- 有 $n$ 个字符串，总长度不超过 $10^6$，有 $q$ 次询问，有以下两种：

	- 把一个串接到另一个串后面。
    
    - 判断两个串是否相似。
    
    > 此处「相似」的定义为：
    
    > 一个串可以经重排得到另一个串。
    
- $n,q\le10^5$

#### 解法

两串相似等价于字母个数分别相等。

直接记录字母个数。$O(Rn)$，其中 $R$ 为字符集大小。

```cpp
const int N=100005;
int n,q,op,x,y;
string s;
int cnt[N][26];
void Solve()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		for(char ch:s)cnt[i][ch-'a']++;
	}
	while(q--)
	{
		cin>>op>>x>>y;
		if(op==1)
		{
			for(int i=0;i<26;i++)cnt[y][i]+=cnt[x][i];
		}
		else
		{
			bool ok=1;
			for(int i=0;i<26;i++)
				if(cnt[y][i]!=cnt[x][i]){ok=0;break;}
			puts(ok?"Yes":"No");
		}
	}
}
```

### Hard version

题意与 Easy version 相同，但是数据范围、输出格式不同。

$n\le10^5,q\le5\times10^6$，字符串变成数列，值域为 $[0,10^9]$，总长度 $M\le5\times10^5$。

#### 解法

此 version 中 $R$ 高达 $10^9$，即使离散化也只能将 $R$ 降到 $M$ 的量级，所以刚才的做法寄了。

考虑 hash，先将数列离散化至最多 $M$ 个数字。

我们可以把 $x$ 替换成第 $x$ 个质数，然后将一个数列的 hash 值定义成其中所有数的乘积。

> 例如：$114\ 514\ 1919\ 114\ 810\ 1919\rightarrow1\ 2\ 3\ 1\ 4\ 3\rightarrow2\ 3\ 5\ 2\ 7\ 5$

> $hash=2\times3\times5\times2\times7\times5=2100$

为什么这样做呢？因为除非冲突，否则不相似的数列 hash 值一定不同。

而且，第 $5\times10^5$ 个质数小于 $10^7$，完全可以接受。

连接数列的时候，直接令 $hash_y\leftarrow hash_y\times hash_x$ 就可以了。

**不能用 `unsigned long long`，要自己模一个大质数。**

```cpp
//struct ModInt{};
bool p[10000005];
int PRIME_CNT,pri[500005];
void Init()
{
	memset(p,1,sizeof(p));
	for(int i=2;PRIME_CNT<500000;i++)
		if(p[i])
		{
			pri[++PRIME_CNT]=i;
			for(ll j=1ll*i*i;j<=10000000;j+=i)p[j]=0;
		}
}
const int N=100005;
int n,m;
map<int,ModInt>lsh;int cnt;
ModInt Lsh(int x)
{
	if(!lsh.count(x))lsh[x]=pri[++cnt];
	return lsh[x];
}
int ANS;
ModInt hsh[N];
void Solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int k;cin>>k;hsh[i]=1;
		while(k--)
		{
			int x;
			cin>>x;
			hsh[i]*=Lsh(x);
		}
	}
	for(int i=1;i<=m;i++)
	{
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1)hsh[y]*=hsh[x];
		else if(hsh[x]==hsh[y])ANS^=i;
	}
	cout<<ANS;
}
```

---

## 作者：heaksicn (赞：2)

## 1 description

初始给定 $n$ 个序列，第 $i$ 个序列长度为 $m_i$。

有 $q$ 次询问，要求支持两个操作：

- 将序列 $x$ 合并到 序列 $y$ 上

- 询问是否可以通过将 $x$ 重排得到 $y$

## 2 solution
注意到 $q\leq 5\times 10^6$，所以我们的单次操作需要做到 $O(1)$。

考虑哈希。

对于每一个初始序列，我们维护它的每个数的平方和，立方和，异或和，并以多种模数同时取模。

对于操作 1，将 $x$ 的哈希值加到 $y$ 即可。

对于操作 2，看在每个模数的意义下哈希值是否相等即可。

时间复杂度 $O(\sum m+q)$。

注意每个值可能为 $0$，为了避免被不同长度的全 $0$ 序列卡掉，可以将每个数的初始权加 $1$。

## 3 code

```
//Man always remember love because of romance only!
#include<bits/stdc++.h>
using namespace std;
#define int long long
int mod[4]={469762049,1004535809,1000000000+7,998244353}; //4个大模数
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int hs[100001][3][4];
signed main(){
	int n=read(),q=read();
	for(int i=1;i<=n;i++){
		int k=read();
		for(int j=1;j<=k;j++){
			int x=read()+1;//如果不加1可能会被不同长度的全0序列卡掉
			for(int l=0;l<4;l++){
				hs[i][0][l]=(hs[i][0][l]+x*x%mod[l])%mod[l];//平方和
				hs[i][1][l]=(hs[i][1][l]+x%mod[l]*x%mod[l]*x%mod[l])%mod[l];//立方和
				hs[i][2][l]=(hs[i][2][l]^x)%mod[l];//异或和
			}
		}
	}
	int ans=0;
	for(int i=1;i<=q;i++){
		int opt=read();
		if(opt==1){
			int x=read(),y=read();
			for(int j=0;j<2;j++){
				for(int k=0;k<4;k++) hs[y][j][k]=(hs[y][j][k]+hs[x][j][k])%mod[k];
			}
			for(int k=0;k<4;k++) hs[y][2][k]=(hs[y][2][k]^hs[x][2][k]);
		}else{
			int x=read(),y=read();
			bool flag=1;
			for(int j=0;j<3;j++){
				for(int k=0;k<4;k++){
					if(hs[x][j][k]!=hs[y][j][k]) flag=0;
				}
			}
			if(flag) ans^=i;
		}
	}
	write(ans);
	return 0;
}

```


---

## 作者：lfxxx (赞：1)

注意到一个序列被合并之后不会再次出现。

所以，实际上，把两个序列合并后的新序列看成这两个序列的父亲，所以这些序列就构成一个 **树性结构** 。

那么就很显然了，采取 **启发式合并** 。

也就是把小的序列暴力插入到大序列中。

注意到对于每个元素，如果被暴力插入，那么它所在的序列长度至少翻倍，所以最多被暴力插入 $\log n$ 次，总复杂度也就是 $O(n \log n)$ 的。

再考虑查询。

查询本质上是问每个数出现次数是否相等。

类似于星战的做法，对于每个数附上一个随机权值 $v_i$。

定义一个序列的哈希值为 $\sum v_i^{tot_i}(tot_i \not = 1)$。

判断哈希值是否相等即可。

但是直接做会带一个 $\log V$。

所以考虑记录每个数的贡献，每次修改拿出来乘上一个 $v_i$ 再加回去。

这样复杂度 $O(n \log n + q)$。

由于直接用 `unordered_map` 常数比 `map` 还差。所以使用了 `pbds`。

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int unsigned int
using namespace std;
const int maxn = 1e5+114;
__gnu_pbds::gp_hash_table<int,int> val;
int anser;
int fa[maxn];
class Node{
    public:
    vector<int> v;
    __gnu_pbds::gp_hash_table<int,int> tot;
    __gnu_pbds::gp_hash_table<int,int> V;
    inline void init();
    inline void insert(int x);
    int Hash;
}chifan[maxn];
inline int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
inline void Node::init(){
    Hash=0;
}
inline void Node::insert(int x){
    if(val[x]==0){
        val[x]=(rand()+1)*(rand()+1);
    }
    v.push_back(x);
    tot[x]++;
    Hash-=V[x];
    if(V[x]==0) V[x]=val[x];
    else V[x]*=val[x];
    Hash+=V[x];
}
inline void merge(int a,int b){
    a=found(a),b=found(b);
    if(chifan[a].v.size()>chifan[b].v.size()) swap(a,b);
    for(int u:chifan[a].v){
        chifan[b].insert(u);
    }
    fa[a]=b;
}
inline void query(int pos,int a,int b){
    a=found(a),b=found(b);
    if(chifan[a].Hash==chifan[b].Hash){
        anser^=pos;
    }
}
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

int n,q;
signed main(){
    n=read(),q=read();
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=n;i++){
        chifan[i].init();
        int m;
        m=read();
        for(int j=1;j<=m;j++){
            int v;
            v=read();
            chifan[i].insert(v);
        }
    }
    for(int i=1;i<=q;i++){
        int op,a,b;
        op=read(),a=read(),b=read();
        if(op==1) merge(a,b);
        else query(i,a,b);
    }
    cout<<anser;
}
```

求助：谁知道如何计算我这个哈希的出错概率？

---

## 作者：caohan (赞：0)

# 思想

虽然正解是什么启发式合并

~~但是我不会~~

这个题目能用 hash 来解。这东西支持合并，查询，很方便，还能压缩空间。

但是 hash 有重复的概率，所以可以用多组 hash 来降低重复概率。

策略便是用某个常数的次方来做。

比如说对于这个文献：

 $a_i={1,2,3,4,5}$ 
 
有三条信息要记录：

第一个是 $b_i=7^1+7^2+7^3+7^4+7^5$ 为 $7^{a_{i_j}}$。

第二个是 $c_i=13^1+13^2+13^3+13^4+13^5$ 为 $13^{a_{i_j}}$。

第三个是序列长度。

合并时相加就行了。

# 代码
```
#include<iostream>
#include<bits/stdc++.h>
#define mod 9223372036854765808//模数
#define ll long long 
using namespace std;
ll ksm(ll a,ll b)
{
	ll ans=1;
	while(b)
	{
		if(b&1)
		{
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;//快速幂
}
ll n,q;
ll m[1000005];
ll a[1000005];
ll b[1000005];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	ll ttttttt1111;
	for(ll i=1;i<=n;i++)
	{
		cin>>m[i];
		for(ll j=1;j<=m[i];j++)
		{
			cin>>ttttttt1111;
			ttttttt1111%=mod;
			a[i]+=ksm(7,ttttttt1111);
			a[i]%=mod;
			b[i]+=ksm(13,ttttttt1111);
			b[i]%=mod;//哈希
		}
	}
	ll ans=0;
	for(ll i=1;i<=q;i++)
	{
		ll opt;
		cin>>opt;
		if(opt==1)
		{
			ll x,y;
			cin>>x>>y;
			a[y]+=a[x];
			b[y]+=b[x];
			m[y]+=m[x];
			a[x]=0;
			b[x]=0;
			m[x]=0;
			a[y]%=mod;
			b[y]%=mod;//合并
		}
		else
		{
			ll x,y;
			cin>>x>>y;
			if(m[x]==m[y]&&a[x]==a[y]&&b[x]==b[y])
			{
				ans^=i;
			}//相似
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：0)

建议评绿（下位蓝亦可）。

### 思路

观察到每次无非维护两个集合是否相同，以及集合的合并。

我们可以对每个集合的值域开一个桶，然后哈希地判断是否相同。

但是这样复杂度代价太高了，所以我们考虑使用 set + 启发式合并。

哈希的方法比较多样，只要保证不太可能重复即可。为了保险可以使用双哈希之类的。

复杂度 $O(n \log n)$。

但是亲测直接暴力合并似乎也能过，所以就没有写启发式合并了。（

### 代码

```cpp
#include <bits/stdc++.h>

// 缺省源

using namespace std;

#define pii pair<int,int>

#define int long long

const int MAXN=100005,mod=1e18+7,MOD=1e18+9; 
int val1[MAXN],val2[MAXN],fa[MAXN];

unordered_map<int,int> vis; 

inline int find(int k){return fa[k]==k?k:fa[k]=find(fa[k]);}

set<pii> s[MAXN];
void merge(int x,int y){
	for(set<pii>::iterator it=s[x].begin();it!=s[x].end();it++){
		set<pii>::iterator jt=s[y].lower_bound(make_pair(it->first,0));
		int cnt;
		if(jt==s[y].end() || jt->first!=it->first) cnt=0;
		else cnt=jt->second,s[y].erase(jt);
		s[y].insert(make_pair(it->first,cnt+(it->second)));
	}
	val1[y]=val2[y]=0;
	for(set<pii>::iterator it=s[y].begin();it!=s[y].end();it++){
		val1[y]=(1ll*val1[y]*114514%mod+1ll*vis[it->first]*(it->second)%mod)%mod;
		val2[y]=(1ll*val2[y]*1919810%mod+1ll*vis[it->first]*(it->second)%MOD)%MOD;
	}
	s[x].clear();
}

signed main(){
	int n,m,q; read(n,q);
	int FUCK=1000000;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=n;i++){
		read(m);
		for(int x,j=1;j<=m;j++){
			read(x);
			if(!vis[x]) vis[x]=FUCK--;
			set<pii>::iterator it=s[i].lower_bound(make_pair(x,0));
			int cnt;
			if(it==s[i].end() || (it->first)!=x) cnt=0;
			else cnt=it->second,s[i].erase(it);
			s[i].insert(make_pair(x,cnt+1));
		}
		for(set<pii>::iterator it=s[i].begin();it!=s[i].end();it++){
			val1[i]=(1ll*val1[i]*114514%mod+1ll*vis[it->first]*(it->second)%mod)%mod;
			val2[i]=(1ll*val2[i]*1919810%MOD+1ll*vis[it->first]*(it->second)%MOD)%MOD;
		}
	}
	
	int ans=0;
	for(int t=1;t<=q;t++){
		int op,l,r; read(op,l,r);
		if(op==1) merge(l,r);
		else if(val1[l]==val1[r] && val2[l]==val2[r]) ans^=t;
	}
	wrt(ans);
	return flush(),0;
}
```

---

## 作者：L0vely_NaiL0ng (赞：0)

不需要启发式合并，直接给每个数值随机一个权值，一份文献的权值就是数列中每个数值的权值之和。

对于操作一，直接将 $x$ 的权值加到 $y$ 的权值上。

对于操作二，如果 $x$ 的权值和 $y$ 的权值一样我们就认为他们相似，否则不相似。

这种思想以及错误概率分析可以见 [P8819 [CSP-S 2022] 星战](https://www.luogu.com.cn/problem/P8819)。

代码：

```
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
mt19937 rnd(time(0));
const int N = 5e5 + 6;
int n, q, ans;
ull v[N];
map<int, ull> id;
signed main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n ; i++) {
		int m; scanf("%d", &m);
		for (int j = 1; j <= m; j++) {
			int x; scanf("%d", &x);
			if (!id[x]) id[x] = rnd() + 1;
			v[i] += id[x];
		}
	}
	for (int i = 1; i <= q; i++) {
		int op, x, y; scanf("%d%d%d", &op, &x, &y);
		if (op == 1) {
			v[y] += v[x];
		} else {
			if (v[x] == v[y]) ans ^= i;
		}
	}
	printf("%d", ans);
}
```

---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9216)

哈希。

读入时给每个数分配一个随机权值，相同的数权值不变。

每个数列统计一个权值和。拼接操作就是权值和相加，权值和相等时我们有极大的把握称这两个数列相似。如果 WA 了只能说你 rp 低到没边。

然而随机权值我只会用 `rand`，但是这个数据范围直接用 `rand()` 函数是很难跑过去的（因为该函数取值区间右边界为 $32767$），建议使用 `rand()*rand()`，正好在 `int` 范围内。

Code:

```cpp
#include<bits/stdc++.h>
#define inf 2000000000
using namespace std;
const int N=1e5+10;
int a[N],n,q,res;
map<int,int>val;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		int m;scanf("%d",&m);
		for(int j=1,x;j<=m;j++){
			scanf("%d",&x);
			if(!val[x])val[x]=rand()*rand();
			a[i]+=val[x];
		}
	}
	for(int i=1,op,x,y;i<=q;i++){
		scanf("%d%d%d",&op,&x,&y);
		if(op==1)a[y]+=a[x];
		else if(op==2&&a[x]==a[y])res^=i;
	}
	printf("%d\n",res);
    return 0;
}
```

[record](https://www.luogu.com.cn/record/108170899)

---

## 作者：DengDuck (赞：0)

# 简要题意

这道题我们根据题意，得出：

定义一个叫做文献的东西，里面存储了一些可以重复的数字。

只要两个文献包含的数字一样，那么就认为两个文献是相似的。

我们需要考虑实现一个数据结构，来维护两种操作：

- 合并两个文献。
- 判断两个文献是否相似。

# 思路解析

我们可以使用哈希，这是一个可以用一个或几个数字来描述很多信息的东西。

我们通常使用哈希来判断两个包含许多信息的事物是否相等。

对于这道题目，我们考虑这样描述一个文献：

- 文献有一个数字 $x$，那么在表示文献的权值中加上一个 $2^x$。
- 文献有一个数字 $x$，那么在表示文献的另外一个权值中加上一个 $3^x$。
- 保存文献中数字的数量。

为什么要多看几个信息呢？对于单个信息，可能两个不同的东西的权值相等，但是有多个权值判断的话，出现权值相等的概率就会变小。

我们把文献转换成这些数据，接下来维护合并和判断是否相等也就十分简单了。

对于合并，数据直接相加即可。

# 代码实现

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e6;
const LL mod=1e9+7;
LL n,q,a[N],b[N],sz[N],m,op,x,y,ans;
LL ksm(LL x,LL y)//用来计算x的y次方，我的实现叫做快速幂
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=(ans*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return ans; 
}
int main()
{
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&m);
		sz[i]=m;//sz表示包含的数字的数量
		for(int j=1;j<=m;j++)
		{
			scanf("%lld",&x);
			a[i]=(a[i]+ksm(2,x))%mod;//第一个哈希权值
			b[i]=(b[i]+ksm(3,x))%mod;//第二个哈希权值
		}
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%lld%lld%lld",&op,&x,&y);
		if(op==1)
		{
			a[y]+=a[x],b[y]+=b[x],sz[y]+=sz[x];//合并操作，相加即可
			a[x]=0,b[x]=0,sz[x]=0;//删除文献
		}
		else
		{
			if(sz[x]==sz[y]&&a[x]==a[y]&&b[x]==b[y])ans^=i;//判断，相等算上贡献
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：苏联小渣 (赞：0)

感觉这个题思路还是挺显然的（？

考虑转化“相似”的条件：设 $S_{i,j}$ 表示第 $i$ 个数列中 $j$ 这个数的出现次数，则 $x,y$ 相似当且仅当：$\forall i \in [0,+\infty),S_{x,i}=S_{y,i}$。

这个东西看起来就很难维护，而这个问题又是判断是否同一，或者说是否“同构”，不难想到用哈希维护。

那么我们考虑选什么哈希：对于这个问题而言，由于顺序不重要，所以可以使用异或哈希或者和哈希。因为异或两次变成 $0$，所以我们使用和哈希。具体而言，给每个出现的数随机赋一个权值，设 $T_x$ 表示数列 $x$ 中所有数所对应的权值的和，则我们可以用 $T_x=T_y$ 来判定 $x$ 和 $y$ 相似。对于操作一，只需将 $T_y \gets T_y + T_x$ 就行了。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, q, op, x, y, ans, len, b[100010];
map <int, int> mp;
const int mo = 1e12;
signed main(){
	mt19937 rand(time(0));
	scanf ("%lld%lld", &n, &q);
	for (int i=1; i<=n; i++){
		scanf ("%lld", &len);
		for (int j=1; j<=len; j++){
			scanf ("%lld", &x);
			if (mp.find(x) == mp.end()) mp[x] = rand() % mo + 1;
			b[i] += mp[x];
 		}
	}
	for (int i=1; i<=q; i++){
		scanf ("%lld%lld%lld", &op, &x, &y);
		if (op == 1) b[y] += b[x];
		else if (b[x] == b[y]) ans ^= i;
	}
	printf ("%lld\n", ans);
	return 0;
}
```

---

