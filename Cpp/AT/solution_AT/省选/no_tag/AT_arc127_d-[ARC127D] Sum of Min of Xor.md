# [ARC127D] Sum of Min of Xor

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc127/tasks/arc127_d

長さ $ N $ の整数列 $ (A_1,A_2,\cdots,A_N) $ および $ (B_1,B_2,\cdots,B_N) $ が与えられます．

$ \sum_{1\ \leq\ i\ <\ j\ \leq\ N}\ \min(A_i\ \oplus\ A_j,\ B_i\ \oplus\ B_j) $ の値を求めてください． ただしここで，$ \oplus $ はビットごとの排他的論理和を表します．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 250000 $
- $ 0\ \leq\ A_i,B_i\ <\ 2^{18} $
- 入力される値はすべて整数である

### Sample Explanation 1

\- $ \min(1\ \oplus\ 2,\ 4\ \oplus\ 5)=\min(3,1)=1 $ - $ \min(1\ \oplus\ 3,\ 4\ \oplus\ 6)=\min(2,2)=2 $ - $ \min(2\ \oplus\ 3,\ 5\ \oplus\ 6)=\min(1,3)=1 $ よって，答えは $ 1+2+1=4 $ になります．

## 样例 #1

### 输入

```
3
1 2 3
4 5 6```

### 输出

```
4```

## 样例 #2

### 输入

```
4
1 2 3 4
1 2 3 4```

### 输出

```
24```

## 样例 #3

### 输入

```
10
195247 210567 149398 9678 23694 46151 187762 17915 176476 249828
68649 128425 249346 62366 194119 117620 26327 161384 207 57656```

### 输出

```
4019496```

# 题解

## 作者：Phartial (赞：3)

没有 $\min$ 的情况是 trival 的，发现瓶颈在于如何比较两个数之间的大小。

可以发现，对两个二进制数，我们本质上是想要找到它们第一个不同的位置。于是考虑从最高位开始，将 $(a_i,b_i)$ 按最高位分组为 $(0,0),(0,1),(1,0),(1,1)$ 四组。每组内部需要继续枚举低位，因此只考虑两组之间的贡献。

可以发现，有贡献的组对如下：

- $(0,0),(0,1)$：此时贡献为 $a_i\oplus a_j$。
- $(0,0),(1,0)$：此时贡献为 $b_i\oplus b_j$。
- $(1,1),(0,1)$：此时贡献为 $b_i\oplus b_j$。
- $(1,1),(1,0)$：此时贡献为 $a_i\oplus a_j$。
- $(0,0),(1,1)$：贡献不确定，需要继续枚举，因此我们需要将这两组并在一起向下处理。
- $(0,1),(1,0)$：贡献不确定，需要继续枚举，因此我们需要将这两组并在一起向下处理。

直接爆算即可。

```cpp
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 2.5e5 + 1;
const int kL = 18;

int n, a[kN], b[kN];
LL ans;
vector<int> sd;

void C(vector<int> &d1, vector<int> &d2, bool w) {
  for (int i = 0; i < kL; ++i) {
    int c11 = 0, c12 = 0;
    for (int j : d1) {
      c11 += (w ? b[j] : a[j]) >> i & 1;
    }
    for (int j : d2) {
      c12 += (w ? b[j] : a[j]) >> i & 1;
    }
    ans += (1LL * c11 * (d2.size() - c12) + 1LL * (d1.size() - c11) * c12) << i;
  }
}
void S(int p, vector<int> &d) {
  if (d.empty()) {
    return;
  }
  if (p == -1) {
    for (int i = 0; i < kL; ++i) {
      int c1 = 0;
      for (int j : d) {
        c1 += a[j] >> i & 1;
      }
      ans += 1LL * c1 * (d.size() - c1) << i;
    }
    return;
  }
  vector<int> l[2][2];
  for (int i : d) {
    l[a[i] >> p & 1][b[i] >> p & 1].push_back(i);
  }
  C(l[0][0], l[0][1], 0);
  C(l[0][0], l[1][0], 1);
  C(l[1][1], l[0][1], 1);
  C(l[1][1], l[1][0], 0);
  for (int i : l[1][1]) {
    l[0][0].push_back(i);
  }
  for (int i : l[1][0]) {
    l[0][1].push_back(i);
  }
  S(p - 1, l[0][0]), S(p - 1, l[0][1]);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sd.push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }
  S(kL - 1, sd);
  cout << ans;
  return 0;
}
```


---

## 作者：KazamaRuri (赞：2)

## 题意

给定两个长度为 $n$ 的数组 $a,b$，求

$$\sum_{i=1}^n\sum_{j=i+1}^n\min\{a_i\oplus a_j,b_i\oplus b_j\}$$

其中 $\oplus$ 表示按位异或。

## 分析

简单二进制分治题（看代码可能更好理解）。

先将有序对转成无序对，最后答案为结果的一半。

考虑去除 $\min$，于是拆位计算贡献。

一个经典的思路是考虑 $a_i\oplus a_j,b_i\oplus b_j$，在第 $k$ 位不同，凭此判断大小。设计函数 $f(a,b,k)$ 表示 $a_i\oplus a_j,b_i\oplus b_j$ 的第 $k$ 位之后全部相等，计算 $1 \rightarrow k$ 位的贡献。把每个元素视作 01 二元组 $(x,y)$，代表 $a_i,b_i$ 的第 $k$ 位上的值。答案的贡献分如下几种考虑：

1. $(x,y) \leftarrow (\neg x,y)$，这就说明 $a_i \oplus a_j$ 这一位是 $1$，而 $b_i \oplus b_j$ 这一位是 $0$，$\min = b_i \oplus b_j$，这部分记录位的就能 $O(\log n)$ 算一个数的答案了。

2. $(x,y) \leftarrow (x,\neg y)$，同 1 处理。

3. $(x,y) \leftarrow (\neg x,\neg y) $，两位相等，无法判断大小，但恒有 $2^k$ 的贡献，向下递归处理。

4. $(x,y) \leftarrow (x,y) $，同 3，无贡献，直接向下递归处理。

递归 $O(\log V)$ 层，每层均摊 $O(n\log V)$，时间复杂度为超小常数 $O(n\log^2V)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define lb(x) (x&-x)
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
using namespace std;
using ll=long long;
using LL=__int128;
using pii=pair<ll,int>;
const int N=25e4+5; ll ans;
struct PairSet{
	int c[20][2]; vector<int>v;
	PairSet(){ memset(c,0,sizeof(c)); }
	void ins(int x){
		v.push_back(x);
		for(int j=0;j<20;j++)
			c[j][x>>j&1]++;
	}
	ll ask(int x){
		ll res=0;
		for(int j=0;j<20;j++)
			res+=(1ll<<j)*c[j][!(x>>j&1)];
		return res;
	}
};
void solve(vector<int>&a,vector<int>&b,int k){
	int n=a.size(); if(!n||!~k) return ;
	PairSet w[2][2][2];
	for(int i=0;i<n;i++){
		int x=a[i]>>k&1,y=b[i]>>k&1;
		w[x][y][0].ins(a[i]&=(1<<k+1)-1);
		w[x][y][1].ins(b[i]&=(1<<k+1)-1);
	}
	for(int i=0;i<n;i++){
		int x=a[i]>>k&1,y=b[i]>>k&1;
		ans+=w[x][y^1][0].ask(a[i]);
		ans+=w[x^1][y][1].ask(b[i]);
		ans+=(ll)w[x^1][y^1][0].v.size()*(1<<k);
	}
	for(int i=0;i^2;i++){
		for(int x:w[1][i^1][0].v) w[0][i][0].v.push_back(x);
		for(int x:w[1][i^1][1].v) w[0][i][1].v.push_back(x);
		solve(w[0][i][0].v,w[0][i][1].v,k-1);
	}
}
int main(){
	int n; scanf("%d",&n);
	vector<int>a(n),b(n);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=0;i<n;i++) scanf("%d",&b[i]);
	return solve(a,b,20),printf("%lld",ans>>1)&0;
}
```

---

## 作者：Inui_Sana (赞：2)

题解区是不是有若干一篇抄另一篇的现象。这里提供一种不太一样的做法。

首先考虑计算 $(i,j)$ 为有序对时的答案，原问题答案只需要 $\times \frac 12$。先钦定 $\min(a_i\oplus a_j,b_i\oplus b_j)=a_i\oplus a_j$，$\sum a_i\oplus a_j$ 是容易拆位算的，于是考虑如何求 $\sum[a_i\oplus a_j>b_i\oplus b_j](b_i\oplus b_j-a_i\oplus a_j)$。

$>$ 并不好做，对于 $\oplus$ 常见的套路是枚举最高的不一样的位 $p$，设 $a_{i,j}$ 为 $a_i$ 的前 $j$ 位组成的数。则有 $a_{i,p-1}\oplus a_{j,p-1}=b_{i,p-1}\oplus b_{j,p-1}$。

因为 $=$ 在 $\oplus$ 中有很好的性质，所以直接转化成 $a_{i,p-1}\oplus b_{i,p-1}=a_{j,p-1}\oplus b_{j,p-1}$，也就是 $a_i\oplus b_i$ 的一段前缀相等。把 $a_i\oplus b_i$ 全部丢到 trie 树上，则就是找到这段前缀对应的点，对于经过这个点后和 $a_i\oplus b_i$ 分开的 $a_j\oplus b_j$ 然后算贡献。这一部分是简单的，只用钦定 $a_i\oplus a_j=1$，预处理一些东西然后拆位算贡献即可。

时间复杂度 $O(n\log^2 n)$。

code：

```cpp
int n,m,a[N],b[N],c[18][2];
struct Trie{
	int cur=1,son[N<<1][2],f[N<<1][2][18][2],g[N<<1][2][18][2];
	il void ins(int x,int y){
		int u=1;
		drep(i,17,0){
			int v=(x^y)>>i&1;
			if(!son[u][v]){
				son[u][v]=++cur;
			}
			u=son[u][v];
			rep(j,0,17){
				f[u][x>>i&1][j][x>>j&1]++;
				g[u][x>>i&1][j][y>>j&1]++;
			}
		}
	}
	il ll qry(int x,int y){
		ll ret=0;
		int u=1;
		drep(i,17,0){
			int v=(x^y)>>i&1;
			rep(j,0,17){
				ret+=(g[son[u][v^1]][(x>>i&1)^1][j][(y>>j&1)^1]-f[son[u][v^1]][(x>>i&1)^1][j][(x>>j&1)^1])*(1ll<<j);
			}
			u=son[u][v];
		}
		return ret;
	}
}T;
void Yorushika(){
	read(n);
	ll ans=0;
	rep(i,1,n){
		read(a[i]);
		rep(j,0,17){
			ans+=(1ll<<j)*c[j][(a[i]>>j&1)^1];
			c[j][a[i]>>j&1]++;
		}
	}
	ans*=2;
	rep(i,1,n){
		read(b[i]);
		T.ins(a[i],b[i]);
	}
	rep(i,1,n){
		ans+=T.qry(a[i],b[i]);
	}
	assert((ans+1)&1);
	printf("%lld\n",ans/2);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：DeepSeaSpray (赞：1)

# [ARC127D] Sum of Min of Xor

先说说没有 $\min$ 怎么操作。按位统计 $0$，$1$ 的个数，它们的积就是这一位为 $1$ 的次数，乘上位权即可。

接下来考虑 $\min$ 的问题，想通过怎么样的方式可以比较出 $a_i \oplus a_j$ 与 $b_i \oplus b_j$ 的大小。

我们考虑二元组 $(a_i,b_i)$ 将其按照第一位 $0$ 或 $1$ 分类成如下几类：

- $(0,0)$
- $(0,1)$
- $(1,0)$
- $(1,1)$

然后考虑不同类的二元组之间的贡献。

- $(0,0)$ 与 $(0,1)$ 贡献 $a_i \oplus a_j$（$a_i \oplus a_j \leq b_i \oplus b_j$）。
- $(1,1)$ 与 $(1,0)$ 贡献 $a_i \oplus a_j$
- $(0,0)$ 与 $(1,0)$ 贡献 $b_i \oplus b_j$
- $(1,1)$ 与 $(0,1)$ 贡献 $b_i \oplus b_j$

以下两组无法比较：

- $(0,0)$ 与 $(1,1)$
- $(0,1)$ 与 $(1,0)$

对于无法比较的两组，我们把两组合并起来，然后就变成了子问题，递归处理下一位。

如果到了最后一位都无法比较，那么取 $a$，$b$ 都无所谓了，直接计算组内互相贡献即可。

贡献有没有算漏呢，没有的，两组之间的贡献都进行了计算，仔细观察会发现递归的过程中问题的规模**总体**没有减小，所以贡献并没有算漏。

实现上，我们用 vector 存下标然后分治即可。

[完整代码](https://atcoder.jp/contests/arc127/submissions/49652885)

---

## 作者：Endt (赞：1)

# Sum of Min of Xor-题解

##### STO [$\texttt{\color{white}{Bird}}$](https://www.luogu.com.cn/user/452730) OTZ

### 题意

给定两个长度为 $n$ 的数组 $a$，$b$，求 $\sum_{i=1}^n\sum_{j=i+1}^n\min\{a_i\oplus a_j,b_i\oplus b_j\}$

### 解法

记一个数二进制最低位为第 $0$ 位。

先考虑只有一个数组的情况（不求最小值），是一个很经典的问题。对于每一二进制位 $x$，记录第 $x$ 位为 $0/1$ 的后缀个数和 $s$，若 $a_i$ 的第 $x$ 位是 $1/0$，贡献即为 $2^x s_{0/1}$。时间复杂度 $\Omicron(n\log a)$。

加入数组 $b$，依然枚举二进制位。记二元组 $c_i=\{a_i\ \texttt{的第}\ x\ \texttt{位},b_i\ \texttt{的第}\ x\ \texttt{位}\}$，显然有 $\{1,1\}\{1,0\}\{0,1\}\{0,0\}$ 四种情况，按照这些情况分组。计算 $i\in\{1,1\}\ \texttt{组}$，$j\in\{1,0\}\ \texttt{组}$ 的贡献，显然这种情况下，$a_i\oplus a_j<b_i\oplus b_j$，这样就可以用上面的方法计算贡献了。其他情况同理，如果无法判断大小，继续进入下一位。

时间复杂度 $\Omicron(n\log^2a)$

---

## 作者：shiruoyu114514 (赞：0)

首先枚举 $i$ 计算 $i$ 与前面所有数的贡献之和的方法是行不通的。因为在从高到低枚举位的过程中，$(a_j,b_j)$ 的第 $b$ 位不管与 $(a_i,b_i)$ 的第 $t$ 位全部相同还是全部不同，都无法直接处理贡献，得递归。于是复杂度就会退化到 $O(n^2)$。

但是按位处理贡献这个思路绝对是可行的，但是我们必须从整个序列的角度来计算。我们不妨先看看最高位的贡献，感觉一下。

考虑将所有 $(a,b)$ 对按照最高位分成 $4$ 类：$(0,0)(0,1)(1,0),(1,1)$。我们先看看当枚举第一个数 $i$ 出自 $(0,0)$ 组，讨论第二个数 $j$ 出现的集合。下文叙述令 $A = a_i \oplus a_j,B=b_i \oplus b_j$。

$(0,0)$：无法判断 $A,B$ 的最高位大小，贡献递归计算。

$(0,1)$：可以发现 $B$ 的最高位为 $1$，而 $A$ 的为 $0$。因此只会取 $a_i \oplus a_j$。我们只需要把所有的 $a_i$ 与 $a_j$ 抽出来，算所有数对的异或和之和即可。拆位即可解决。

$(1,0)$：与 $(0,1)$ 相似，但是取的是 $b_i \oplus b_j$。只需要把 $b_i$ 与 $b_j$ 抽出来即可。

$(1,1)$：与 $(0,0)$ 类似，唯一的区别是取一对 $(i,j)$ 的基础贡献为 $2^{\text{highbit}}$，而不是 $0$。提前计算并递归即可。

其它分析类似。

这看起来依然不好处理，但是可以发现这么一件事：需要递归的集合对本质上是 $((0,0)/(1,1),(0,0)/(1,1))$ 或者 $((0,1)/(1,0),(0,1)/(1,0))$。这意味着，我们只需要把 $(0,0)(1,1)$ 合并，$(0,1)(1,0)$ 合并，最高位位数 $-1$ 就能完美规约到子问题了。

每个数至多会被包含在 $\log V$ 个子问题中，每个子问题的时间复杂度至多为计算 $(0,0)(0,1)$ 型贡献时的拆位 $O(\log V)$。所以总时间复杂度为 $O(n \log^2 V)$。

---

## 作者：rizynvu (赞：0)

[我的博客](https://www.cnblogs.com/rizynvu/p/18297148)。

对于 $\oplus$ 这种位运算，直接从二进制位考虑即可。

考虑如何确定 $\min(a_i\oplus a_j, b_i\oplus b_j)$ 是哪一边取到。  
能知道是从高位到低位考虑，会有一段前缀满足异或出来是相等的，然后到了一位时一边是 $0$ 另一边是 $1$，就确定出来了。

于是可以考虑枚举前缀去统计贡献。  
令 $a_{i, w}$ 为取 $a_i$ 中 $\ge w$ 的位组成的数，类似定义 $b_{i, w}$。  
那么在 $w$ 这一位，需要统计的贡献就有两种：

1. 前缀到了这一位都相等，那么要把这一位的贡献算上。
2. 前缀到了下一位就不等了（即找到 $\min$ 了），就把 $\min$ 对应的贡献算上。

考虑到前缀到了这一位相等，就有 $a_{i, w}\oplus a_{j, w} = b_{i, w}\oplus b_{j, w}$。  
那么就有 $a_{i, w}\oplus b_{i, w} = a_{j, w}\oplus b_{j, w}$。  
于是相当于以 $a_{i, w}\oplus b_{i, w}$ 来划分等价类，对于每个等价类统计贡献即可。  

对于第一种贡献，因为取 $a, b$ 都行，例如取个 $a$，记录一下等价类里的数对应 $w$ 位的值为 $0 / 1$ 的个数即可。  
对于第二种贡献也类似，只不过记录的是在 $w - 1$ 位 $a$ 为 $x$ 且 $b$ 为 $y$ 时在 $w'$ 位 $a / b$ 分别 $0 / 1$ 的个数。

时间复杂度 $\mathcal{O}(n\log^2 V)$。

```cpp
#include<bits/stdc++.h>
const int maxn = 2.5e5 + 10, limw = 19;
int a[maxn], b[maxn], A[maxn], B[maxn];
int cnt1[maxn][2], cnt2[maxn][limw][2][2][2][2];
int main() {
   int n; scanf("%d", &n);
   for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
   for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
   long long ans = 0;
   for (int w = limw - 1; ~ w; w--) {
      memset(cnt1, 0, sizeof(cnt1));
      memset(cnt2, 0, sizeof(cnt2));
      for (int i = 1; i <= n; i++) A[i] |= a[i] & (1 << w);
      for (int i = 1; i <= n; i++) B[i] |= b[i] & (1 << w);
      std::unordered_map<int, int> ID; int N = 0;
      for (int i = 1; i <= n; i++) {
         if (! ID[A[i] ^ B[i]]) ID[A[i] ^ B[i]] = ++N;
         int id = ID[A[i] ^ B[i]];
         cnt1[id][a[i] >> w & 1]++;
         if (w) {
            int x = a[i] >> (w - 1) & 1, y = b[i] >> (w - 1) & 1;
            for (int w1 = 0; w1 < w; w1++)
               cnt2[id][w1][x][y][0][a[i] >> w1 & 1]++,
               cnt2[id][w1][x][y][1][b[i] >> w1 & 1]++;
         }
      }
      for (int i = 1; i <= n; i++) {
         int id = ID[A[i] ^ B[i]];
         ans += (1ll << w) * cnt1[id][1 ^ (a[i] >> w & 1)];
         if (w) {
            int xi = a[i] >> (w - 1) & 1, yi = b[i] >> (w - 1) & 1;
            for (int x : {0, 1}) for (int y : {0, 1}) {
               if ((xi ^ x) < (yi ^ y)) {
                  for (int w1 = 0; w1 < w; w1++)
                     ans += (1ll << w1) * cnt2[id][w1][x][y][0][1 ^ (a[i] >> w1 & 1)];
               } else if ((yi ^ y) < (xi ^ x)) {
                  for (int w1 = 0; w1 < w; w1++)
                     ans += (1ll << w1) * cnt2[id][w1][x][y][1][1 ^ (b[i] >> w1 & 1)];
               }
            }   
         }
      }
   }
   printf("%lld\n", ans / 2);
   return 0;
}
```

---

## 作者：Xy_top (赞：0)

一道简单题，因为异或的套路并没有多少，然而还是要说一下：口胡五分钟，代码两小时！

异或的套路很少，这题则使用按位从高到低讨论的方法。

先考虑怎么统计答案，显然若一个数在二进制下某一位前和另一个数都一样但是这一位比它小那么这个数就比另一个二进制数小。

有了这个结论就很简单了，横着看 $a$ 数组，竖着看 $a_i$ $b_i$ 组成的二元组，这两种都试一遍，发现后者更好统计答案。

对 $a_i$ $b_i$ 当前这个二进制位上的数字进行分类讨论，分成 $(0,0)$ $(0,1)$ $(1,0)$ $(1,1)$ 四种，先把能统计的统计了。

第一种是 $(0,0)$ 和 $(0,1)$，此时从 $(0,0)$ 中选一个，再从 $(0,1)$ 中选一个，一定有 $a_i\oplus a_j<b_i \oplus b_j$，除了得到这个，还发现这个小情况的计算就是 P3917 这一道题。

剩下的就不多说了，还有 $(1,1)$ $(1,0)$ 这种情况是 $a_i\oplus a_j<b_i \oplus b_j$ 的，$(1,1)$ $(0, 1)$ 以及 $(0,0)$ $(1,0)$ 这两种情况是 $a_i\oplus a_j > b_i\oplus b_j$ 的，分别进行统计后，还剩下自己和自己中选一个异或，在我们讨论到的二进制位上无法判断大小，只能弄到下一个二进制位上。

以及 $(0,0)$ $(1,1)$ 和 $(0,1)$ $(1,0)$ 也无法判断，这些都将留到下一位统计。

而我们发现如果将当前这一位 $(0,0)$ 和 $(1,1)$ 并到一起再像之前那样进行分类讨论正好能把里面涵盖的三种情况全部算出来且不会多算。

于是做法很显然了，这里采用递归的做法，存两个参数，位数和集合中的元素，每次先统计当前的答案，然后将 $(0,0)$ $(1,1)$ 并起来进行下一位的讨论，再将 $(0,1)$ 和 $(1,0)$ 并起来进行下一位的讨论。

代码十分丑陋，其实可以优化很多：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, ans;
int a[250005], b[250005];
int c[250005], d[250005];
vector <int> v;
void calc1 (vector <int> d1, vector <int> d2) {
	if (d1.empty () || d2.empty () ) return;
	int cnt = 0;
	for (int i : d1) c[++ cnt] = a[i];
	cnt = 0;
	for (int i : d2) d[++ cnt] = a[i];
	For (j, 0, 17) {
		int cnt0 = 0, cnt1 = 0;
		int pre = 1 << j;
		For (i, 0, d2.size () - 1) {
			if ( (d[i + 1] >> j) & 1) ++ cnt1;
			else ++ cnt0;
		}
		For (i, 0, d1.size () - 1) {
			if ( (c[i + 1] >> j) & 1) ans += pre * cnt0;
			else ans += pre * cnt1;
		}
	}
}
void calc2 (vector <int> d1, vector <int> d2) {
	if (d1.empty () || d2.empty () ) return;
	int cnt = 0;
	for (int i : d1) c[++ cnt] = b[i];
	cnt = 0;
	for (int i : d2) d[++ cnt] = b[i];
	For (j, 0, 17) {
		int cnt0 = 0, cnt1 = 0;
		int pre = 1 << j;
		For (i, 0, d2.size () - 1) {
			if ( (d[i + 1] >> j) & 1) ++ cnt1;
			else ++ cnt0;
		}
		For (i, 0, d1.size () - 1) {
			if ( (c[i + 1] >> j) & 1) ans += pre * cnt0;
			else ans += pre * cnt1;
		}
	}
}
void calc (vector <int> d) {
	int cnt = 0;
	For (i, 0, d.size () - 1) c[++ cnt] = a[d[i] ];
	For (j, 0, 17) {
		int cnt0 = 0, cnt1 = 0;
		int pre = 1 << j;
		foR (i, cnt, 1) {
			if ( (c[i] >> j) & 1) ans += pre * cnt0;
			else ans += pre * cnt1;
			if ( (c[i] >> j) & 1) ++ cnt1;
			else ++ cnt0; 
		}
	}
}
void work (int dep, vector <int> &d) {
	if (!d.size () ) return;
	if (dep == -1) {
		calc (d);
		return;
	}
	vector <int> l[2][2];
	for (int i : d) l[(a[i] >> dep) & 1][(b[i] >> dep) & 1].push_back (i);
	calc1 (l[0][0], l[0][1]);//
	calc1 (l[1][1], l[1][0]);//
	//从上面两个中每一个中挑选一个，一定满足 a_i ^ a_j < b_i ^ b_j，统计答案
	calc2 (l[0][0], l[1][0]);//
	calc2 (l[1][1], l[0][1]);//
	//从......一定满足 b_i ^ b_j < a_i ^ a_j，统计答案
	/*
	00 01
	11 10
	00 10
	11 01
	
	11 00
	11 11
	
	00 00
	00 11
	
	10 01
	*/
	for (int i : l[1][1]) l[0][0].push_back (i);
	for (int i : l[0][1]) l[1][0].push_back (i);
	work (dep - 1, l[0][0]);
	work (dep - 1, l[1][0]);
}
void solve () {
	cin >> n;
	For (i, 1, n) v.push_back (i);
	For (i, 1, n) cin >> a[i];
	For (i, 1, n) cin >> b[i];
	work (17, v);
	cout << ans;
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：binbin_200811 (赞：0)

# [ARC127D Sum of Min of Xor](https://www.luogu.com.cn/problem/AT_arc127_d)

性质分析加通用套路。

### 思路

首先我们把这题的 $\min$ 给去掉，那么我们按位算贡献，可以求出和。这是这种式子的通用套路。

考虑加上 $\min$，那么我们先按照 $(a_i,b_i)$ 的最高位分为：$(1,0)$，$(0,1)$，$(1,1)$，$(0,0)$ 四种情况。

可以发现用贡献的组如下：

* $(0,0)$，$(0,1)$ 贡献为 $a_i\oplus a_j$。
* $(0,0)$，$(1,0)$ 贡献为 $b_i\oplus b_j$。
* $(1,1)$，$(1,0)$ 贡献为 $a_i\oplus a_j$。
* $(1,1)$，$(0,1)$ 贡献为 $b_i\oplus b_j$。
* $(1,1)$，$(1,1)$ 贡献需要向下枚举一位计算。
* $(0,0)$，$(0,0)$ 贡献需要向下枚举一位计算。

那么已知贡献的我们可以用通用套路算，不知道的向下枚举即可。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define K 18

const int maxn=3e5+5;

int n;
int a[maxn],b[maxn];

ll ans;

vector<int>sd;

void C(vector<int> &d1,vector<int> &d2,bool w)
{
    for(int i=0;i<K;i++)
    {
        int c1,c2;
        c1=c2=0;
        for(int j:d1) c1+=(w?b[j]:a[j])>>i&1;
        for(int j:d2) c2+=(w?b[j]:a[j])>>i&1;
        ans+=(1ll*c1*(d2.size()-c2)+1ll*c2*(d1.size()-c1))<<i;
    }
}
void S(int p,vector<int> &d)
{
    if(d.empty()) return ;
    if(p==-1)
    {
        for(int i=0;i<K;i++)
        {
            int c1=0;
            for(int j:d)
                c1+=a[j]>>i&1;
            ans+=1ll*c1*(d.size()-c1)<<i;
        }
        return ;
    }
    vector<int> l[2][2];
    for(int i:d) l[a[i]>>p&1][b[i]>>p&1].push_back(i);
    C(l[0][0],l[0][1],0);
    C(l[0][0],l[1][0],1);
    C(l[1][1],l[0][1],1);
    C(l[1][1],l[1][0],0);
    for(int i:l[0][0]) l[1][1].push_back(i);
    for(int i:l[0][1]) l[1][0].push_back(i);
    S(p-1,l[1][1]),S(p-1,l[1][0]);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),sd.push_back(i);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    S(K-1,sd);
    printf("%lld",ans);
}
```



---

