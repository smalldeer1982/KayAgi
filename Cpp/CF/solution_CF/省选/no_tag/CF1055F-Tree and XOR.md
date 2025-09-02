# Tree and XOR

## 题目描述

给定一棵包含 $n$ 个顶点的无环连通无向图（即一棵树），树的每条边上都写有一个非负整数。

对于所有顶点对 $(v, u)$（一共恰好有 $n^2$ 个），对于每一对，计算从 $v$ 到 $u$ 的简单路径上所有边权的按位异或（xor）值。如果路径只包含一个顶点，则该路径上所有边权的异或值为 $0$。

假设将所有得到的 $n^2$ 个值按非降序排列。你需要找出其中第 $k$ 小的值。

异或的定义如下：

给定两个整数 $x$ 和 $y$，考虑它们的二进制表示（可能有前导零）：$x_k \dots x_2 x_1 x_0$ 和 $y_k \dots y_2 y_1 y_0$（其中 $k$ 足够大以容纳 $x$ 和 $y$ 的所有位）。这里 $x_i$ 表示 $x$ 的第 $i$ 位，$y_i$ 表示 $y$ 的第 $i$ 位。令 $r = x \oplus y$ 表示 $x$ 和 $y$ 的异或操作结果。那么 $r$ 的定义为 $r_k \dots r_2 r_1 r_0$，其中：

$$
r_i = \left\{
\begin{aligned}
1, ~ \text{如果} ~ x_i \ne y_i \\
0, ~ \text{如果} ~ x_i = y_i
\end{aligned}
\right.
$$

## 说明/提示

第二个样例的树结构如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1055F/5bfa2eab3ef44ea89fb9c60d427736329daa0bdd.png)

对于这样的树，一共有 $9$ 条路径：

1. $1 \to 1$，值为 $0$
2. $2 \to 2$，值为 $0$
3. $3 \to 3$，值为 $0$
4. $2 \to 3$（经过 $1$），值为 $1 = 2 \oplus 3$
5. $3 \to 2$（经过 $1$），值为 $1 = 2 \oplus 3$
6. $1 \to 2$，值为 $2$
7. $2 \to 1$，值为 $2$
8. $1 \to 3$，值为 $3$
9. $3 \to 1$，值为 $3$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1
1 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 6
1 2
1 3
```

### 输出

```
2
```

# 题解

## 作者：hs_black (赞：12)

## [CF1055F Tree and XOR](https://www.luogu.com.cn/problem/CF1055F)

首先进行一步转化，求出每个点到根节点路径的异或值作为它的点值，求u -> v路径的异或值就相当于两点值异或一下，因为lca到根节点的路径会被异或两次而抵消

接下来就是如下问题

> 一个序列$a_1~a_2~a_3\cdots a_n$，两两异或，有$n^2$组异或值， 求第k大

说到异或首先要想到01trie

首先想到一个二分的思路：将所有数插入01trie，二分一个第k大的值val，对于每个点在01trie上找出异或其点值后小于val的值有多少个，时间复杂度$O(nlog^2_n)$， ~~极限卡常~~，肯定布星

那么，考虑贪心的从高位到地位来考虑答案，很多题都可以这么做因为只要高位较大，低位就不用考虑了

对于当前位，n个点并行计算出当前异或意义下取零的方案数，如果方案数大于等于k，就走异或意义下的0， 否则k减去方案数，走异或意义下的1(fixed by tommy0103)

这道题可能有点卡空间，滚一下

*talk is cheap, show me the code:* 

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const int N = 1000050;
template <typename T>
void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c=getchar();
    for (;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^48);
}

ll dis[N], n, K;
int ch[2][N<<2][2];
int cnt[2], p[N], p2[N];

int h[N], to[N], ne[N];
ll siz[2][N], w[N], tot;
inline void add(int x, int y, ll z) {
    ne[++tot] = h[x], to[tot] = y;
    h[x] = tot, w[tot] = z;
}

void dfs(int x) {
    for (int i = h[x]; i; i = ne[i]) 
        dis[to[i]] = dis[x] ^ w[i], dfs(to[i]);
}

int main() {
    read(n), read(K);
    for (int i = 2;i <= n; i++) {
        ll a, b; read(a), read(b);
        add(a, i, b);
    } dfs(1);
    ll ans = 0;
    for (int i = 1;i <= n; i++) p[i] = p2[i] = 1;
    for (ll b = 62;b >= 0; b--) {
        int k = b & 1, pk = !k; cnt[k] = 0;
        for (int i = 1;i <= n; i++) {
            ll di = (dis[i] >> b) & 1; siz[pk][p[i]] = 0;
            if (!ch[pk][p[i]][di]) ch[pk][p[i]][di] = ++cnt[k];
            p[i] = ch[pk][p[i]][di]; siz[k][p[i]]++;
            ch[k][p[i]][0] = ch[k][p[i]][1] = 0;
        }
        ll sum = 0;
        for (int i = 1;i <= n; i++) {
            ll di = (dis[i] >> b) & 1;
            sum += siz[k][ch[pk][p2[i]][di]];
        }
        for (int i = 1;i <= n; i++) {
        	ll di = (dis[i] >> b) & 1;
        	if (K > sum) p2[i] = ch[pk][p2[i]][!di];
        	else p2[i] = ch[pk][p2[i]][di];
        }
        if (K > sum) K -= sum, ans |= (1ll << b);
    }
    cout << ans << endl;
}
```



---

## 作者：yuzhechuan (赞：12)

### 题解：

先是对题意的一些简单转换：由于对于每一条xor链都可以看成是两个数（xor前缀）的结果，所以题目变成了对于长度为$n$的数列$val_i$（也就是xor前缀），求两两异或结果的第$k$小值

下面开始正文：

我们考虑以贪心的思路从高到低逐位推出ans每一位的值

构建trie树的同时，对于每一个$val_i$，我们计算出在当前答案进度下，与它配对所能得到0的方案数$cnt$，假如比当前剩余的$k$值小，就在$k$中减掉$cnt$，且当前位答案应为1，否则0

(上面的话可能很玄乎，毕竟是洛谷黑题CF2800pt呢，我争取再讲清楚点)

在某一层上，遍历时对于trie树上的两条链，我们发现会有三种情况，一种是小于答案的，我们会在减cnt时减掉并换一条链继续便利（因为另一条一定是更大的）；一种是大于答案的，我们不会去管（遍历）它；还有一种是（可能）等于答案的，也就是我们所要从上到下遍历的，注意到因为是两条链，因此对于每个$val_i$自己的链（代码中是$a[i]$），还要额外记一条能与它异或出答案的链（代码中是$b[i]$）

这样就是一个时空$O(62*N)$的算法

思路貌似有了呢，但代码难度还是十分高的

因为还有很重要的一点，由于朴素的trie内存会炸，所以我们要考虑滚存trie树（然后会使代码可读性极度下降，导致蒟蒻我一开始难以理解）

trie树滚存的大致思路是由于一层最多只有$n$个点，所以我们只保存改层$n$个点的两个子节点，并对于每个$val_i$记两个指针$a[i]$和$b[i]$（上面有提到），一个是自己的，一个是要与自己匹配的链的，每次开始处理新的一层，处理指针数组都要清空，在根据上一层的指针数组构建出这一层的trie树，为啥这不会导致节点混乱呢？大概是因为如果上一层两个$val_i$指向同一个节点的话，他们在新建的节点中的“指向”也不会发生改变

这样，空间复杂度就降到了$O(n)$

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=1e6+5;
int n,a[N],b[N],ch[N][2],sz[N];
/*a[]b[]上文有讲，ch[i][0/1]表示val[i]的左右节点编号，sz[]表示有多少val[i]经过这个节点*/
long long sum,ans,k,val[N];

signed main(){
	read(n);read(k);
	a[1]=b[1]=1; //1表示trie树的根节点
	for(int i=2;i<=n;i++){
		int x;long long y;
		read(x);read(y);
		val[i]=y^val[x]; //父节点编号保证小于自己，所以可以直接O(1)维护xor前缀
		a[i]=b[i]=1;
	}
	for(int i=61;i>=0;i--){
		int cnt=0;sum=0;
		for(int j=1;j<=n;j++) ch[j][0]=ch[j][1]=sz[j]=0; //清空上一层的
		for(int j=1;j<=n;j++){
			int &p=ch[a[j]][val[j]>>i&1]; //根据指针建新点
			if(!p) p=++cnt;
			sz[a[j]=p]++;
		}
		for(int j=1;j<=n;j++)
			sum+=sz[ch[b[j]][val[j]>>i&1]]; //统计在“可能相等”中会产生几对0
		int op=0; //op是当前位的答案
		if(sum<k) k-=sum,op=1,ans|=1ll<<i;
		for(int j=1;j<=n;j++)
			b[j]=ch[b[j]][val[j]>>i&1^op]; //看看b指针是否要换一条链
	}
	write(ans);
}
```

---

## 作者：lg_zhou (赞：3)

**trie 树上二分与按位贪心**

前置芝士 [Trie 1](https://www.luogu.com.cn/blog/lgzhou/ke-chi-jiu-hua-trie)。

**CF1055F Tree and XOR**

树上路径的异或和显然可以套路转化。记 $S
[i]$ 为第 $i$ 个节点到根的路径异或和。则点 $A$ 到点 $B$ 路径的异或和就等于 $S[A] \oplus S[B]$。（因为 $lca$ 上面的都消掉了）。那么原题就转化为给出 $n$ 个数，求两两异或和的第 $k$ 大。

这题根本不用建树，由于第一个编号比第二个小。直接如下：

```cpp
for (int i = 2; i <= n; i++){
	int fa,w;
	cin >> fa >> w;
	a[i] = a[fa]^w; 
}
```


我们很轻松能想到一个做法，先将所有数放进 $trie$ 里，预处理出每个节点有多少个数经过。二分最终答案，再扫一遍 $trie$ 累加有多少数小于它，即为 $cnt$，比较 $cnt$ 和 $k$，即可判断二分区间。

这样的复杂度是 $nlog^2n$ 的，多出来一个 $log$ 无法通过本题，考虑直接贪心枚举从高到低的每一位，查看当前这一位选 $1$ 还是选 $0$ 各有多少种对，记选 $0$ 的有 $cnt$ 对，将 $cnt$ 和 $k$ 比较决定选 $0$ 还是选 $1$，如果选 $1$ 的话 $k=k-cnt$，因为它是这一位选 $1$ 条件下的第 $k-cnt$ 小。

具体实现的话可以每个数都维护一个指针，即目前跳到了 $trie$ 的哪个节点。累加 $cnt$ 的时候就暴力扫一遍所有的数，看看接下来能不能走使这个数这一位异或和为零的儿子就可以了。
```cpp
int ans = 0;
for (int i = 1; i <= n; i++) p[i] = 1;
for (int i = 62; i >= 0; i--){
	int cnt = 0;
	//此位取零的方案数 
	for (int j = 1; j <= n; j++){//暴力扫一遍每一个数
		int c = a[j]>>i&1; // 当前这位是什么 
		cnt += sz[trie[p[j]][c]];//sz 在建 trie 的时候维护即可
	}
	int pan = (K > cnt);//取零还是取一
	if (pan){//取一
		K -= cnt;
		ans += (1ll<<i);
	} 
	for (int j = 1; j <= n; j++){
		int c = a[j]>>i&1;
		p[j] = trie[p[j]][c^pan]; //每个数匹配到哪了
	}
}
```

比较坑的是，这题竟然卡内存。只能滚存一下字典树，比较容易绕晕。滚存其实只要在上面的代码上每层清空重来就行，维护 $sz$ 再开一个数组记录原始每个数的当前层就行。

```cpp
for (int i = 61; i >= 0; i--){
//此位取零的方案数 
for (int j = 1; j <= tot; j++){
	sz[j] = trie[j][0] = trie[j][1] = 0;
}
tot = cnt = 0;
for (int j = 1; j <= n; j++){
	int c = (a[j]>>i&1); // 当前这位是什么 
	if (!trie[old[j]][c]){
		tot++;
		old[j] = trie[old[j]][c] = tot;
	}
	else old[j] = trie[old[j]][c];
	sz[old[j]]++;
}
for (int j = 1; j <= n; j++){
	int c = (a[j]>>i&1);
	cnt += sz[trie[p[j]][c]];
} 
int pan = (K > cnt); // 取零还是取一
if (pan){
	K -= cnt;
	ans += (1ll<<i);
} 
for (int j = 1; j <= n; j++){
	int c = (a[j]>>i&1);
	p[j] = trie[p[j]][c^pan];
}

```

这道题还是 [Trie 3](https://www.luogu.com.cn/blog/lgzhou/solution-cf241b) 这里面问题的前置。




---

## 作者：1saunoya (赞：3)

首先考虑一个树上问题。

异或可以抵消掉，所以令 $dis_u = dis_{fa} \oplus w$。

$dis_u \oplus dis_v$ 就是这一条路径上的 $xor$ 了。

然后变成了一个序列上的问题。

发现这个其实就是任意选两个点，$dis_u \oplus dis_v$ 的 kth。

这个玩意是可以枚举 $2^k$ 看合不合法的。

然后往另外一边一直走下去。

搞个 $trie$ 树对每一层进行操作即可。

---

## 作者：popossible (赞：0)

# Tree and XOR

### 题意

给一棵 $n$ 个点的树，有边权，你要求出 $n^2$ 个点对中第 $k$ 小的路径异或和（也就是说，$(a,b)$ 和 $(b,a)$ 算不同的点对），如果点对形如 $(a,a)$ 的话异或和为 0。

### 转化

令 $dis_i$ 为每个点到根结点路径的异或值，则 $(u,v)$ 两点间的路径值为 $dis_u  \ \operatorname{xor} \ dis_v$。

即题意转化为求 $dis$ 序列中数两两异或第 $k$ 小。

即可引出一贪心做法：按二进制下从高位到低位逐位推出每一位为 1 还是为 0，即对于每一位，计算出当前位为 0 时的个数 $cnt$，若 $k \le cnt$，则当前位为 0，否则为 1，并 $k \gets k-cnt$。

具体地，枚举二进制下第 $i$ 位，记 $mp_x$ 表示 $x$ 在这个序列中出现了多少次。

1. 对于 $j \in [1,n],mp[dis_j>>i] \gets mp[dis_j>>i]+1$。

2. 对于 $j \in [1,n],cnt \gets cnt+mp[(ans<<1) \operatorname{xor} (dis_j>>i)]$。

由 $a \operatorname{xor} b=c \rightarrow b=a \operatorname{xor} c$ 即可推出上述柿子。

采用 hash 表作为 $mp$ 即可得到时间复杂度为 $O(n \log n \log V)$ 的算法，~~但是肯定过不去~~。

### 另一种思路

我们使用 $mp$ 仅是为了查找一序列中某个数的个数，因此我们完全可以不使用 $mp$ ，而是处理出上述数的有序序列，而后采用双指针法计算出满足条件的数对的数量，即可完成此题。

若采用基数排序，即可得到时间复杂度为 $O(n \log V)$ 的算法，~~但是也过不去至少我过不去~~。

### 序列的性质

记上述过程 1 得到的序列为 $A$，过程 2 得到的序列为 $B$。

容易发现，在 $dis$ 有序的情况下，$A$ 是有序的，读者自证不难。

但是我们并不知道 $B$ 是否有序，下面我们就来证明它是**部分**有序的 。

+ 首先，在算法开始前，$B$ 中数全为 0。
+ 其次，我们假设在我处理 $B$ 前，他上一次的值已被更新。
+ 因为我们考虑的数末位为 0，设当前位为 $j$，新的 $B_j \gets (ans<<1)\operatorname{xor}(dis_j>>i)$，最末位只与 $dis_j$ 的末位有关，前面的位数在上次已更新为有序，所以整个 $B$ 呈现出只存在末位无序的现状，所以 $B$ 是部分有序的。

所以我们只需对 $B$ 中数进行交换即可，因此去掉排序部分，该算法的时间复杂度为 $O(n \log V)$。

### 代码

声明：作者码的不是很好，所以只拿来对拍吧。

```cpp
#include<bits/stdc++.h>
using namespace std;

//#define int ll
typedef long long ll;

namespace fastio{
	#define FILE_SIZE 1<<21
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}using namespace fastio;

const int M=1e6+1;

struct Pair{
	ll fi,se;
	
	Pair(ll _fi=0,ll _se=0):
		fi(_fi),se(_se){;}
	bool operator == (const Pair &a) const {
		return fi==a.fi; 
	}
	bool operator < (const Pair &a) const {
		return fi<a.fi;
	}
}aim[M]; 

int n;
ll dis[M],k;
ll tmp[M],a[M];

signed main(){
	
	read(n),read(k);
	for(int i=2;i<=n;i++){
		int f;
		ll w;
		read(f),read(w);
		dis[i]=dis[f]^w;
		aim[i]=Pair(0,dis[i]);
	}
	sort(dis+1,dis+n+1);
	
	ll ans=0;
	for(ll i=61;i+1;i--){
		ll siz=0;
        // 处理A序列
		for(int j=1;j<=n;j++) a[j]=(dis[j]>>i);
        // 处理B序列
		for(int j=1,k=0;j<=n;j=k+1) {
			while(aim[k+1].fi==aim[j].fi&&k+1<=n) k++;
			int p_j=j,p_k=k;
			while(p_j<p_k){
				while(!(aim[p_j].se&(1ll<<i))&&p_j<p_k) aim[p_j].fi<<=1,p_j++;
				while((aim[p_k].se&(1ll<<i))&&p_j<p_k) (aim[p_k].fi<<=1)|=1,p_k--;
				swap(aim[p_j],aim[p_k]);
				if(p_j==p_k) aim[p_j].fi=(ans<<1)^(aim[p_j].se>>i); 
			}
			if(j==k) aim[j].fi=(ans<<1)^(aim[j].se>>i);
		}
		int p_a=0,p_aim=0;
		while(p_a<=n){
			p_a++;
			while(aim[p_aim+1].fi<a[p_a]&&p_aim+1<=n) p_aim++;
			ll len1=0,len2=1;
			while(aim[p_aim+1].fi==a[p_a]&&p_aim+1<=n) len1++,p_aim++;
			while(a[p_a+1]==a[p_a]&&p_a+1<=n) len2++,p_a++;
			siz+=len1*len2;
		}
		if(k<=siz) ans<<=1;
		else {
			k-=siz;
			(ans<<=1)|=1;	
            //处理ans末位更改为0后的答案，其实只是对B的某些部分的区间反转
			for(int j=1,k=0;j<=n;j=k+1) {
				while((aim[k+1].fi>>1)==(aim[j].fi>>1)&&k+1<=n) k++;
				int p_j=j,p_k=k;
				while(p_j<p_k){
					while((aim[p_j].se&(1ll<<i))&&p_j<p_k) p_j++;
					while(!(aim[p_k].se&(1ll<<i))&&p_j<p_k) p_k--;
					swap(aim[p_j],aim[p_k]);
				}
				for(int t=j;t<=k;t++) aim[t].fi=ans^(aim[t].se>>i);
			}
		}
	}
	
	cout<<ans;
	
	return 0;
} 
```

后记：~~快读是贺的~~。

---

