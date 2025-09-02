# Chips on a Board

## 题目描述

Alice and Bob have a rectangular board consisting of $ n $ rows and $ m $ columns. Each row contains exactly one chip.

Alice and Bob play the following game. They choose two integers $ l $ and $ r $ such that $ 1 \le l \le r \le m $ and cut the board in such a way that only the part of it between column $ l $ and column $ r $ (inclusive) remains. So, all columns to the left of column $ l $ and all columns to the right of column $ r $ no longer belong to the board.

After cutting the board, they move chips on the remaining part of the board (the part from column $ l $ to column $ r $ ). They make alternating moves, and the player which cannot make a move loses the game. The first move is made by Alice, the second — by Bob, the third — by Alice, and so on. During their move, the player must choose one of the chips from the board and move it any positive number of cells to the left (so, if the chip was in column $ i $ , it can move to any column $ j < i $ , and the chips in the leftmost column cannot be chosen).

Alice and Bob have $ q $ pairs of numbers $ L_i $ and $ R_i $ . For each such pair, they want to determine who will be the winner of the game if $ l = L_i $ and $ r = R_i $ . Note that these games should be considered independently (they don't affect the state of the board for the next games), and both Alice and Bob play optimally.

## 样例 #1

### 输入

```
8 10
1 3 3 7 4 2 6 9
7
2 3
1 3
1 4
1 10
5 10
8 10
9 10```

### 输出

```
BAAAAAB```

# 题解

## 作者：Saliеri (赞：19)

一开始其实也只会莫队套 Trie 的 $O(n\sqrt n\log n)$，看了官方题解不知所云，后来在 CF 讨论区里找到了这个神奇的做法，来补一发。

___

首先非常明显，这两位就是在玩一个 Nim 游戏，所以问题转化为：考虑在范围内的棋子，这些棋子到左边界的距离的**异或**和。

看到位运算，考虑逐位确定答案。发现逐位这种东西用**倍增**维护起来非常方便，（毕竟倍增就是一个逐位的过程），所以来考虑倍增怎么做。

我们定义 $jp_{i,k}$ 表示，只考虑纵坐标位于 $i$ 至 $i+2^k-1$ 的棋子、钦定左边界为 $i$ 的距离异或和。

考虑转移。发现倍增在转移到更高位时，最高位的贡献是**独立**的（即 k 更低的位都不会对这一位产生影响）。所以如果要从 $jp_{i,k-1} $ 转移到 $ jp_{i,k}$，第 k 位的贡献就只是纵坐标位于 $i+2^{k-1}$ 到 $i+2^k-1$ 的棋子数量的奇偶性。

写成更简洁的形式：其中 $\oplus$ 表示异或，$Sum_i$ 表示前 i 列中有多少个棋子。

$$jp_{i,k} = jp_{i,k-1} \oplus jp_{i+2^{k-1},k-1} \oplus [Sum_{i+2^{k}-1}-Sum_{i+2^{k-1}-1} \text{mod} \ 2 = 1] \times 2^{k-1}$$

这整个倍增表可以在 $O(m\log m)$ 的时间内预处理出来。

然后来考虑回答询问。用倍增的套路，从高位到低位依次逼近答案。我们发现，每拼接上一段，整个区间中还未被拼接上的部分的所有棋子的距离都会增加一个**二的幂次**。换句话说，这只对要求的答案的**某一位**产生贡献。

然后跟预处理部分一样，前缀和讨论棋子数量的奇偶性即可。

每回答一次询问需要 $O(\log m)$ 的时间，总复杂度 $O((m+q)\log m)$。

给个代码：

```cpp
#include <cstdio>
const int maxn = 2e5+5;
int n,m,q,a[maxn],sum[maxn];
int Log[maxn],jp[maxn][19];
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),++sum[a[i]];
	for(int i=1;i<=m;++i)sum[i] += sum[i-1];
	for(int i=2;i<=m;++i)Log[i] = Log[i>>1] + 1;
	for(int j=1;j<=Log[m];++j)
		for(int i=1;i+(1<<j)-1<=m;++i)
			jp[i][j] = jp[i][j-1]^jp[i+(1<<j-1)][j-1]^((1<<j-1)*((sum[i+(1<<j)-1]-sum[i+(1<<j-1)-1])&1));
	scanf("%d",&q);
	for(int i=1,l,r,ans;i<=q;++i){
		scanf("%d %d",&l,&r),ans = 0;
		for(int k=Log[m];~k;--k)
			if(l+(1<<k) <= r){
				ans ^= jp[l][k],l += (1<<k);
				if((sum[r]-sum[l-1])&1)ans ^= (1<<k);
			}
		putchar(ans?'A':'B');
	}
	return 0;
}
```

挺好一题。

---

## 作者：dead_X (赞：6)

## 题意
求 $\bigoplus\limits_{i=1}^n[l\leq a_i\leq r](a_i-l)$ 是否为 $0$。

$n,q,a_i\leq 2\times 10^5$。
## 思路
看到离线，根号复杂度，区间查询，我啪的一下就把莫队码上去了，很快啊！

然后考虑移动端点会发生什么。

显然移动端点可能会发生这些情况：在一个集合里加入一个数，删除一个数，所有数 $+1$，所有数 $-1$。

于是我们考虑这样一个题：维护一个集合，支持加入，删除，全体 $\pm 1$，全局异或和。

诶这个题不就是联考 2020 的那个题吗？我们考虑反向建一棵 trie，然后加 $1$ 就只要交换 $0,1$ 的转移边并递归 $0$ 的转移边即可。

于是单次操作的复杂度是 $\log n$ 的，乘上莫队的 $n\log m$ 复杂度为 $n\sqrt m\log n$。

于是你写了，交了，TLE 飞了。
## 一些卡常思路
注意到我们的 insert 和 delete 修改的信息很少，而 plus 和 minus 修改的信息很多，因此我们考虑减少 plus 和 minus 的次数。

首先想到将 plus 和 minus 分开，于是我们不使用普通莫队而使用回滚莫队，这样可以通过调整块长的方式平衡一定的常数。

然后我们发现写 insert 可以通过非递归形式来写，并且 plus 的时候可以在动态开点时保留部分信息。

然后我们将同一个节点的信息塞到二维数组里保证内存尽可能连续。

然后我们可以在动态开点的时候清空内存，回滚时不清空内存。

然后我们加上火车头和快读去优化一点点 IO 常数。

最后就过了，用时 $4929$ 毫秒，比 $O(nq)$ 还慢（悲）
## 参考代码
```cpp
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#include<bits/stdc++.h>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<20],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') s*=10,s+=ch^48,ch=getchar();
	return s;
}
int cnt=1;
int A[5000003][6];
inline int add(int cur,int i)
{
	int t=++cnt;
	A[t][0]=A[cur][3],A[t][1]=A[cur][0],
	A[t][2]=A[cur][1],A[t][3]=A[cur][2],
	A[t][5]=A[cur][5],A[t][4]=A[cur][4]^A[A[cur][3]][4],
	A[t][4]-=(A[t][4]&((i<<2)-1));
	if(A[t][0]) A[t][0]=add(A[t][0],i<<2);
	A[t][4]^=A[A[t][0]][4],
	((A[A[t][1]][5]+A[A[t][3]][5])&1)&&(A[t][4]+=i),
	((A[A[t][2]][5]+A[A[t][3]][5])&1)&&(A[t][4]+=i<<1);
	return t;
}
int ans[200003];
struct query
{
	int l,r,bl,id;
	bool operator<(const query&t)const{return bl<t.bl||(bl==t.bl&&r<t.r);}
}q[200003];
bool f[200003];
signed main()
{
	int T=read(),n=read();
	for(int i=1; i<=T; ++i) f[read()]^=1;
	int m=read();
	int B=sqrt(1ll*n*n/m)/2+5;
	for(int i=1; i<=m; ++i) q[i].l=read(),q[i].r=read(),q[i].bl=q[i].l/B,q[i].id=i; 
	sort(q+1,q+m+1);
	for(int i=1,l=B,r=B-1; i<=m; ++i)
	{
		if(q[i].bl!=q[i-1].bl)
			cnt=1,memset(A[1],0,24),
			l=(q[i].bl+1)*B,r=l-1;
		if(q[i].r<l) for(int j=q[i].l; j<=q[i].r; ++j) (f[j])&&(ans[q[i].id]^=j-q[i].l);  
		else
		{
			while(r<q[i].r) 
			{
				++r;
				if(f[r])
				for(int i=0,cur=1,c,x=r-l; i<=18; i+=2,cur=A[cur][c])
					c=(x>>i)&3,
					(!A[cur][c])&&(A[cur][c]=++cnt,memset(A[cnt],0,24)),
					A[cur][4]^=x-(x&((1<<i)-1)),
					++A[cur][5];
			}
			int C=cnt,R=1;
			for(int j=q[i].l; j<l; ++j) (f[j])&&(ans[q[i].id]^=j-q[i].l);
			for(int j=q[i].l; j<l; ++j) R=add(R,1);
			ans[q[i].id]^=A[R][4],cnt=C;
		}
	}
	for(int i=1; i<=m; ++i) *O++="AB"[(ans[i]==0)];
	fwrite(obuf,O-obuf,1,stdout);
    return 0;
}
```

---

## 作者：zcxxnqwq (赞：3)

很容易发现题目就是在描述一个朴素的 nim 博弈，要求的就是 $\oplus_{a_i\in[l,r]}(a_i-l)$ 是否为 $0$。

场上立刻想到了省选联考某题用 01trie 维护 $+1$ 和 $-1$ 操作，套个莫队，时间复杂度 $O(n\sqrt n\log n)$，没敢写，但居然卡卡常能过。

有一个更简单的做法：考虑倍增，维护 $f[i][j]$ 为纵坐标在 $[i,i+2^j-1]$ 之间的坐标 $k-i$ 的异或和，发现 $[0,j-1]$ 位的贡献与第 $j$ 位的贡献无关，于是只需要知道纵坐标在区间内个数的奇偶性即可转移。维护前缀和 $sum_i$：

$$f[i][j]=f[i][j-1]\oplus f[i+2^{j-1}][j-1]\oplus([sum_{i+2^j-1}-sum_{i+2^{j-1}-1}\equiv 1\pmod 2]\times2^{j-1})$$

查询也同理，从 $l$ 每次跳可以跳的最长区间直到跳到 $r$ 即可，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define rep(i,s,e) for(int i=(s);i<=(e);++i)
#define Rep(i,s,e) for(int i=(e);i>=(s);--i)
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=2e5+5;
int n,m,a[N],q,f[N][20],mi[N];
signed main(){
    n=read(),m=read();
    rep(i,1,n) a[read()]^=1;
    n=m;
    rep(i,1,n) a[i]^=a[i-1];
    rep(j,1,__lg(n)) rep(i,1,n-(1<<j)+1){
        int p=i+(1<<j-1);
        f[i][j]=f[i][j-1]^f[p][j-1]^((a[p+(1<<j-1)-1]^a[p-1])<<j-1);
    }
    q=read();
    while(q--){
        int l=read(),r=read(),ans=0,pre=0;
        while(l<=r){
            int len=__lg(r-l+1);
            ans^=f[l][len]^(a[l+(1<<len)-1]^a[l-1])*pre;
            pre+=1<<len,l+=1<<len;
        }
        putchar(ans?'A':'B');
    }
    putchar('\n');
}
```

---

## 作者：FutaRimeWoawaSete (赞：3)

做过最好的一道运用到“逐位考虑”性质的题目了，不看题解思路完全往莫队上面去了……                   

首先很显然的转化一下题意，我们只需要知道石子堆的异或和就好了，也就是回答所有询问的：           

$\bigoplus_{i = 1} ^ n [l \leq a_i \leq r](a_i - l)$    

即可。              

考虑如何维护这个东西，最经典的操作就是莫队滚区间然后用 trie 树做全局整体 $\pm 1$ 以及全局整体异或和得到 $O(n \sqrt n \log n)$ 的时间复杂度，虽然可以卡常过掉此题但是这种做法显然还不够优秀。                

我们考虑一些很有兴趣的性质。既然是异或和，那么还是逐位考虑咯？而且我们的式子里面只和左端点有关系，还要维护类似“和”的东西。不难想到倍增固定左端点维护以这个端点开始的一个区间异或和。                

记 $sum_{i , j}$ 表示从值域的第 $i$ 个数开始到 $i + 2 ^ {j} - 1$ 这一段的区间异或和，注意这里的区间异或和对于每一个数已经减去了 $l$ 。            

那么我们很自然的开始凑式子，最理想的情况当然是像 st 表那样从 $sum_{i , j - 1}$ 和 $sum_{i + 2 ^ {j - 1} , j - 1}$ 转移。我们不难发现，对于 $i + 2 ^ {j - 1}$ 到 $i + 2 ^ j - 1$ 这一段减去 $i$ 后，值域在 $[2 ^ {j - 1} , 2 ^ j - 1]$ 之间，其最高位是 $2 ^ {j - 1}$ 。而且我们刚才罗列的两个状态里面都是不涉及这一位的。考虑异或的性质，我们现在是不是只要知道这一段值域区间里面棋盘上的棋子数的奇偶性就可以得到这一位对最后的答案是否有贡献了啊？          

令 $Sum_x$ 表示棋盘上有多少个棋子在 $1 \sim x$ 这些列上，于是可以得到转移式：             

$sum_{i,j} = sum_{i , j - 1} \bigoplus sum_{i + 2 ^ {j - 1} , j - 1} \bigoplus [Sum_{i + 2 ^ j - 1} - Sum_{i + 2 ^ {j - 1} - 1} \mod 2 = 1] \times 2 ^ {j - 1}$       

预处理这个东西出来之后，我们对于查询还是运用相同的道路：                   

从高位到低位考虑每一位的贡献。如果当前答案可能涉及到一位 $k$ ，那么我们就先把预处理出来的 $dp_{l , k}$ 往答案里面塞，接着只用考虑 $[l + 2 ^ k , r]$ 这一段内棋子数的奇偶性就可以求得 $2 ^ k$ 这一位是否会对答案贡献，由于从高到低枚举，$k$ 是当前的最高位，所以这一位的造成贡献情况以及 $[l , l + 2 ^ k - 1]$ 这一段区间的异或和已经被全部搞定。     

接下来把 $l$ 置为 $l + 2 ^ k$ 后继续考虑就好了，由于从高到位倍增枚举，所以最后单次查询只会用 $O(\log m)$ 的时间。         

最终的时间复杂度就是 $O((m + q) \log m)$ 。    

对于这种方法，个人认为是不止 2700 的。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
int sum[Len][35],n,m,q,a[Len],Sum[Len];
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&a[i]);
		Sum[a[i]] ++;
		//sum[a[i]][0] ^= a[i];
	}
	for(int i = 1 ; i <= m ; i ++) Sum[i] += Sum[i - 1];
	for(int j = 1 ; j <= 28 ; j ++)
		for(int i = 1 ; i + (1 << j) - 1 <= m ; i ++) 
			sum[i][j] = sum[i][j - 1] ^ sum[i + (1 << (j - 1))][j - 1] ^ (((Sum[i + (1 << j) - 1] - Sum[i + (1 << (j - 1)) - 1]) % 2) * (1 << (j - 1)));		
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i ++)
	{
		int l,r;scanf("%d %d",&l,&r);int ans = 0;
		for(int j = 28 ; j >= 0 ; j --)
		{
			if(l + (1 << j) <= r) 
			{
				ans ^= sum[l][j] , l += (1 << j);
				if((Sum[r] - Sum[l - 1]) & 1) ans ^= (1 << j);
			}
		}
		(ans == 0) ? putchar('B') : putchar('A');
	} 
	return 0;
}
```

---

## 作者：syksykCCC (赞：2)

通过 Nim 定理，很容易发现第 $i$ 个询问的答案是 `B` 当且仅当 $\bigoplus\limits_{L_i \le c_j \le R_i}(c_j - L_i) = 0$。否则询问的答案就是 `A`。

那么我们来对每一个询问计算这个异或和。发现答案 $<2^{18}$，接下来尝试**根号分治**，选择某一个数 $K$，用一种算法去计算最低的 $K$ 位的答案，用另一种算法去计算最高的 $18-K$ 位的答案。

两种算法都有一个共同的思想：我们会把每一个询问拆成两个询问：$(L_i, R_i)$ 会被表示为 $Q(L_i, L_i)$ 和 $Q(R_i + 1, L_i)$，这里 $Q(x, y) = \bigoplus\limits_{c_j \ge x}(c_j - y)$。其实本质就是一个**差分**。

在改造了询问之后，对于每一个 $x \in [1, m]$，把每一个 $Q(x, y)$ 存在一些 vector 中。接着遍历 $x$，处理所有对于当前 $x$ 的询问。

怎么找到每个询问的最低 $K$ 位呢？从 $m \to 1$ 遍历 $x$，用**桶**维护当前所访问过的每一个数字 $c_i$ 的数量。某时间我们想要计算 $Q(x, y)$，就遍历每一个桶，暴力计算它们的异或和。因为我们只关心答案的末 $K$ 位，所以只需要保留 $c_i \bmod 2^K$，所以计算异或和是 $O(2^K)$ 的，这一部分的时间复杂度是 $O(n+m+2^K q)$。

怎么找到每个询问的最高 $18-K$ 位呢？可以发现，对于每一个数字 $c_i$，在我们遍历 $x$ 的过程中，$c_i - x$ 的这些高位的变化**并不频繁**：$c_i - x$ 的这些位的变化只有约 $\frac{m}{2^K}$ 个区间（这很好理解，因为我们不关心 $c_i - x$ 的末 $K$ 位，所以重复了 $2^K$ 次 $+1$ 后高位才会变化一次）。使用一种数据结构，支持两种操作：区间异或、单点查询。比如 **BIT** 就可以做到这件事。我们重新从 $m \to 1$ 遍历 $x$，当我们想要处理一个数 $c_i$ 的时候，我们找到 $c_i - y$ 的高位相同的那些段区间，然后在 BIT 中更新这些区间。当查询 $Q(x, y)$ 的时候，直接查询 BIT 中 $y$ 位置的值即可。这部分的时间复杂度是 $O(n \frac{m}{2^K} \log m + m + q)$。

记 $N = \max(n, m, q)$，在 $K$ 选定适当的情况下，可以在 $O(N \sqrt{N \log N})$ 的时间复杂度内解决这个问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, k = 10, K = 1 << 10;
int n, m, q, c[N], ans[N];
bool cnt[N], tub[K];
vector<pair<int, int>> vec[N]; // q[x] = {id, y}
struct binary_indexed_tree
{
	int o[N];
	void Modify(int p, int v)
	{
		for(; p <= m; p += (p & -p)) o[p] ^= v;
	}
	int Query(int p)
	{
		int res = 0;
		for(; p; p -= (p & -p)) res ^= o[p];
		return res; 
	}
} bit;
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		cin >> c[i];
		cnt[c[i]] ^= 1;
	}
	cin >> q;
	for(int i = 1; i <= q; i++)
	{
		int l, r;
		cin >> l >> r;
		vec[l].push_back(make_pair(i, l));
		vec[r + 1].push_back(make_pair(i, l));
	}
	for(int i = m; i; i--)
	{
		if(cnt[i])
		{
			tub[i % K] ^= 1;
			for(int r = i, l; r >= 1; r = l - 1)
			{
				l = max(1, r - K + 1);
				bit.Modify(l, i - l >> k); 
				bit.Modify(r + 1, i - l >> k);
			}
		}
		for(pair<int, int> qry : vec[i])
		{
			int res = bit.Query(qry.second) << k;
			for(int j = 0; j < K; j++)
				if(tub[j]) res ^= ((j - qry.second) % K + K) % K;
			ans[qry.first] ^= res;
		}
	}
	for(int i = 1; i <= q; i++) cout << "AB"[ans[i] == 0];
	return 0;
}
```

---

## 作者：YLWang (赞：2)

### 题意简述

- 现有 $n$ 个数 $1 \le c_1, c_2, ... , c_n \le m$。

- $Q$ 次询问，每次询问给出 $l, r$，询问 ${\rm xor}_{\ l \le c_i \le r}(c_i - l)$ **是否等于 0**。

- $n, m, Q \le 2 \times 10^5$。

提供了三种不同做法。

### 算法 1
自己 yy 的做法。

先将 $c_i$ 排序。然后值域区间对应一个下标区间，对值域区间莫队。

于是我们只需要支持以下操作：

全局权值 $+1$ 或 $-1$，全局异或和。

这个是某年联合省选原题。 具体地，把 Trie 倒过来就容易维护了。

$O(n \sqrt{n} \log n)$。

不过右侧移动似乎是 $O(1)$ 的，应该有奇怪的排序方法能把 $\log$ 放进去。日后有空想一想写一写会放份代码。

### 算法 2
官方题解的奇妙根号分治。感觉十分奇怪。

先离线下来，然后问题就变成了查询 $F(x, y) = {\rm xor}_{\ y \le c_i}(c_i - l)$。

把每个数拆成 $\le 2^K$ 和 $ > 2^K$ 两部分分别统计答案。

前一部分比较好处理。我们直接存下来所有数对 $2^K$ 取余的结果，查询时是容易的。

后一部分看起来比较困难，但发现每个位置的前 $2^K$ 位在 $l$ 变化时只改变 $ \dfrac{m}{2^K}$ 次，于是拿个 BIT 暴力去维护他就好了。

两个拼起来就好。

$O(n \sqrt{n \log n})$。

挺智慧的，反正我肯定不会去想。想了也不一定能想到基于改变用 BIT 维护。

~~忘记基础思想.jpg~~

### 算法 3

自己 yy 的做法 2。

当时想完算法 1 就想不根号。想着想着还真给想出了点什么。

我们考虑位运算和倍增，就像笔芯和钻石一样，性质不同，却相互衍生，本质相同。

于是我们记一手 $f(x, y) = {\rm xor}_{\ x \le c_i \le2^y}(c_i - x)$。 

然后大力倍增去求 $f$。只在当前位有奇数个的时候才略需讨论。

求答案的时候也是不难操作的。于是就单 log 了。

代码下次一定。

---

## 作者：tribool4_in (赞：1)

降智了。

首先显然是个 Nim 游戏，且可以转化到值域上，具体的考虑一个数字出现偶数次直接删掉，奇数次则保留一个，然后放到值域上。于是要求区间带减异或和。

一、莫队+01trie

直接上莫队，发现需要维护加删数字、全局加减 1，求全局异或。于是上 01trie，其余是容易维护的，全局加减 1 的话考虑加减对结构的影响，发现交换 0/1 子树并选择相应子树递归下去即可。时间复杂度 $O(n\sqrt{n}\log{n})$，$n,m,q$ 同阶。

二、倍增

很智慧的，考虑倍增，设 $f_{i,j}$ 表示 $[i,i+2^j)$ 区间，左端点在 $i$，此时的异或和。倍增转移时，发现右半部分可能会加上 $2^{j-1}$ 的贡献，具体当右半部分有值的位置有奇数个时会产生贡献。于是有转移 $f_{i,j}=f_{i,j-1}\oplus f_{i+2^{j-1},j-1}\oplus 2^{j-1}[cnt_{[i+2^{j-1},i+2^j)}\bmod2=1]$。

求答案的话，考虑类似预处理过程，对于当前段，首先将 $f$ 的贡献加上，然后考虑当前段中的点若为奇数个则需要增加一些贡献，对之前倍增到的位都异或一下即可，喜提 $O(n\log^2{n})$。然后发现向前考虑不如直接向后考虑，考虑后面会有多少个位置会因当前段产生贡献。于是变成了 $O(n\log{n})$。具体见代码。好像两者跑的差不多快。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, K = 18;
int n, m, q, a[N], bs[N], f[N][K];
bool b[N];
int query(int l, int r) {
    int ans = 0, p = l;
    vector<int> vec;
    for (int i = K - 1; i >= 0; i--) {
        if (p + (1 << i) - 1 <= r) {
            ans ^= f[p][i];
            if ((bs[r] - bs[p + (1 << i) - 1]) & 1)
                ans ^= (1 << i);
            // if ((bs[p + (1 << i) - 1] - bs[p - 1]) & 1)
            //     for (auto j : vec) ans ^= (1 << j);
            p += (1 << i), vec.push_back(i);
        }
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], b[a[i]] ^= 1;
    for (int i = 1; i <= m; i++) bs[i] = bs[i - 1] + b[i];
    for (int j = 1; j < K; j++)
        for (int i = 1; i + (1 << j) - 1 <= m; i++)
            f[i][j] = f[i][j - 1] ^ f[i + (1 << j - 1)][j - 1] ^ ((bs[i + (1 << j) - 1] - bs[i + (1 << j - 1) - 1]) & 1) * (1 << j - 1);
    cin >> q;
    for (int i = 1, l, r; i <= q; i++) {
        cin >> l >> r;
        cout << (query(l, r) ? 'A' : 'B');
    }
    return 0;
}
```

---

## 作者：7KByte (赞：1)

出题人并没有想到单 $\log$ 做法 （

题意是求$\bigoplus\limits_{l\le a_i\le r} (a_i-l)$ 。

然后 rk1 老哥 $\rm O(N^2)$ 艹过去了 $2\times 10^5$ 并抗住了 $100$ 发 Hack，不得不说 CF 机子跑的是真的快。

（写什么正解快点写暴力

实际上单 $\log$ 做法比题解的 $\rm O(N\sqrt{N\log N})$ 做法好想好写。

处理异或和的套路，按位讨论。

对于最高位取值为 $1$ 的数，一定是连续的一段。

所以我们直接倍增，定义 $f[i][j]$ 表示 $\bigoplus \limits_{i\le a_k<i+2^j}(a_k-i)$ 。不难发现 $(a_k-i)$ 都是 $<2^j$ 的数，异或和一定 $<2^j$ 。

同时定义 $g[i][j]$ 表示在 $i\le a_k<i+2^j$ 的 $k$ 的个数。

边界 $f[i][0]=0$，$g[i][0]=c_i$，其中 $c$ 是桶。

考虑转移，$g[i][j]=g[i][j-1]+g[i+2^{j-1}][j-1]$，这很好理解。

$$f[i][j]=f[i][j-1] \bigoplus f[i+2^{j-1}][j-1]\bigoplus (g[i+2^{j-1}][j-1]\&1)\times2^{j-1} $$

为什么可以这么计算，因为在区间 $[i+2^{j-1},i+2^j)$ 这段区间中，所有的数都要 $+2^{j-1}$，但是这并不影响前 $j-1$ 位异或和的取值，唯一有影响的是第 $j$ 位的取值。

对于每个询问，在 $\log N$ 的时间内合并答案即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int f[N][20],g[N][20],n,m,q,x,t;
int main(){
	scanf("%d%d",&n,&m);t=log2(m);
	rep(i,1,n)scanf("%d",&x),g[x][0]++;
	rep(j,1,t)rep(i,1,m-(1<<j)+1)
		f[i][j]=(f[i][j-1]^f[i+(1<<(j-1))][j-1])^((g[i+(1<<(j-1))][j-1]&1)<<(j-1)),
		g[i][j]=g[i][j-1]+g[i+(1<<(j-1))][j-1];
	scanf("%d",&q);
	while(q--){
		int l,r,cur=0,sum=0;scanf("%d%d",&l,&r);r=r-l+1;
		pre(i,t,0)if((r>>i)&1)cur=cur^f[l][i]^((g[l][i]&1)*sum),sum+=1<<i,l+=1<<i;
		if(cur)putchar('A');else putchar('B');
	}
	return 0;
}
```

---

## 作者：AzusaCat (赞：1)

这里给一个 $O(n\log^2m)$ 的做法。

不难发现，这个游戏就是一个 nim 游戏，所以我们只需要查询值在 $[l,r]$ 内的所有数减去 $l$ 的异或和是否为 $0$。对其进行差分，为了防止后面对负数的讨论（其实也不需要），我们拆成 $[l,m]$ 和 $[r+1,m]$ 两个询问，那么现在询问的形式就是后缀每个数减去某个数的异或和。

离线询问。我们考虑计算每一位是 0 还是 1，设当前我们在考虑 $2^d$ 这一位。由于保证了减后的数都是正数，我们可以把每个数对 $2^{d+1}$ 取模。当加入某个数时，只需要在该数对 $2^{d+1}$ 取模后的位置加上 1。现在考虑如果减数是 $x$（也对 $2^{d+1}$ 取模），使得差的该位是 $1$ 的被减数的范围：

- 如果 $x$ 的这一位是 1，那么范围是 $[x-2^d,x-1]$。

- 如果 $x$ 的这一位是 0，那么范围是 $[0,x-1]\cup [x+2^d,2^{d+1}-1]$。

以上的正确性可以在边界处分类讨论得到。于是我们只需要一个树状数组维护区间奇偶性。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct query{int x,id;};
vector<query>v[200005];
int n,m,c[200005],lim,ans[200005];
struct BIT
{
    int tree[1<<18|5];
    void modify(int x){x++;for(int i=x;i<=lim;i+=(i&(-i)))tree[i]^=1;}
    int ask(int x){x++;int res=0;for(int i=x;i;i-=(i&(-i)))res^=tree[i];return res;}
    void clear(){memset(tree,0,sizeof(tree));}
}T;
void work(int d)
{
    T.clear();lim=2<<d;
    for(int i=m;i>=1;i--)
    {
        if(c[i])T.modify(i&(lim-1));
        for(auto j:v[i])
        {
            int x=j.x&(lim-1);
            if(x&(1<<d))ans[j.id]^=(T.ask((x-(1<<d))-1)^T.ask(x-1))<<d;
            else ans[j.id]^=(T.ask(lim-1)^T.ask(x+(1<<d)-1)^T.ask(x-1))<<d;
        }
    }
}
int main()
{
    int x,y,q;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&x),c[x]^=1;
    scanf("%d",&q);
    for(int i=1;i<=q;i++)scanf("%d%d",&x,&y),v[x].push_back({x,i}),v[y+1].push_back({x,i});
    for(int i=0;i<18;i++)work(i);
    for(int i=1;i<=q;i++)putchar(ans[i]?'A':'B');
    return 0;
}
```

---

## 作者：Gold14526 (赞：1)

发现做法跟别人不一样，赶紧来交一发。

$\rm Problem:$[Chips on a Baord](https://www.luogu.com.cn/problem/CF1511G)

$\rm Difficulty:2700$

### 题意

Alice 和 Bob 有一个 $n\times m$ 的棋盘。每行恰好有一个棋子。

他们以如下的方式进行一个游戏：

- 选择一对整数 $l,r(1\leq l\leq r\leq m)$，将除第 $l\sim r$ 列之外的部分从棋盘上移除。

- 轮流进行操作，Alice 先手。每一次操作，玩家需要选择一个棋子，并将其向左走任意正整数步（不能移出棋盘）。第一个不能移动的玩家判负。

给定 $q$ 次独立的询问如 $L_i,R_i$ 所示，试求如果第一步中选择的整数是 $(L_i,R_i)$，谁会赢得游戏。

$1\leq n,m,q\leq 2\times 10^5$。

### 做法

首先，这是一个 $\rm Nim$ 游戏，原题显然可以等价于询问 $\bigoplus\limits_{l\le a_i\le r}(a_i-l)$。

设 $cnt_i$ 表示 $a$ 中等于 $i$ 的数的个数除以二的余数。

询问变为 $\bigoplus\limits_{l\le i\le r,cnt_i=1}i-l$。

观察自然数的二进制：

```
2^3  0  0  0  0  0  0  0  0  1  1  1  1  1  1  1  1
2^2  0  0  0  0  1  1  1  1  0  0  0  0  1  1  1  1
2^1  0  0  1  1  0  0  1  1  0  0  1  1  0  0  1  1
2^0  0  1  0  1  0  1  0  1  0  1  0  1  0  1  0  1
     0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 ...
```

按位观察，发现第 $i$ 位为 $2^i$ 个 $0$ 与 $2^i$ 个 $1$ 交替。

我们定义序列中长度为 $x$ 的前缀中，下标 $i$ 满足 $i \equiv x\pmod {2^k}$ 的 $cnt_i$ 的异或和为 $x$ 的 $k$ 级前缀异或和，记作 $sum_{x,k}$，不难通过递推求出。

现在，一段区间第 $k$ 位的答案可以通过 $sum_{x,k}$ 求出。

举个例子，求 $[4,8]$ 第 $1$ 位的答案：

```
2^2              0  0  0  0  1
2^1              0  0  1  1  0
2^0              0  1  0  1  0
i-l              0  1  2  3  4
i    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 ...
```
只需求出 $sum_{6,1}\bigoplus sum_{7,1}\bigoplus sum_{1,1}\bigoplus sum_{2,1}$ 即可。

但是这样效率还是不够，考虑求出 $s_{x,k}=\bigoplus\limits_{1\le i\le x}sum_{i,k}$。

于是，不难求出某一位的答案。

具体的：

设 $len=r-l,x=2^i\times\lfloor\frac{len}{2^i}\rfloor+l,S_{l,r,k}=s_{r,k}\bigoplus s_{l-1,k}$。

对于第 $i$ 位，如果这一位最后 $2^{i+1}$ 个数形如这样：

```
0 ... 0 0 1 1 ... 1 1 0 0 ... 0
```

此时，$x-l\equiv 2^i\pmod{2^{i+1}}$，当前位的答案为 $S_{x-2^i+1,x,i}\bigoplus S_{l-2^i,l-1,i}$。

如果形如这样：

```
1 ... 1 1 0 0 ... 0 0 1 1 ... 1
```

此时，$x-l\equiv 0\pmod{2^{i+1}}$，当前位的答案还要在异或一个 $S_{r-2^{i+1}+1,r,i}$，即 $S_{x-2^i+1,x,i}\bigoplus S_{l-2^i,l-1,i}\bigoplus S_{r-2^{i+1}+1,r,i}$。

即：

$$ans_{l,r,i}=\begin{cases}S_{x-2^i+1,x,i}\bigoplus S_{l-2^i,l-1,i}&x-l\equiv 2^i\pmod{2^{i+1}}\\S_{x-2^i+1,x,i}\bigoplus S_{l-2^i,l-1,i}\bigoplus S_{r-2^{i+1}+1,r,i}&x-l\equiv 0\pmod{2^{i+1}}\end{cases}$$

常数会小一些，因为绝大部分变量都可以以布尔类型存储。

### 代码

```cpp
#include<bits/stdc++.h>
#define cint const int
#define iint inline int
#define ll long long
#define cll const long long
#define ill inline long long
using namespace std;
iint read()
{
	int num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return num;
}
int n,q;
bool a[200001],s[200001][19];
void init()
{
	for(int k=1;k<=18;++k)
	{
		for(int i=1;i<=n;++i)
		{
			s[i][k]=a[i];
			if(i>(1<<k))s[i][k]^=s[i-(1<<k)][k];
		}
		for(int i=1;i<=n;++i)
		{
			s[i][k]^=s[i-1][k];
		}
	}
}
bool sum(cint l,cint r,cint k)
{
	return (s[r][k]^s[max(0,l-1)][k]);
}
bool ask(cint l,cint r)
{
	int len=r-l,x;
	for(int i=1;1<<i-1<=len;++i)
	{
		x=(len>>i-1<<i-1)+l;
		if(sum(l-(1<<i-1),l-1,i)^sum(x-(1<<i-1),x-1,i)^((len>>i-1)&sum(r-(1<<i)+1,r,i)))return 1;
	}
	return 0;
}
int main()
{
	q=read();
	n=read();
	while(q--)a[read()]^=1;
	init();
	q=read();
	while(q--)
	{
		cint l=read();
		cint r=read();
		if(ask(l,r))putchar('A');
		else putchar('B');
	}
	return 0;
}
```

---

## 作者：Dovish (赞：0)

## 分析
这个问题其实就是求区间内的 $\text{nim}$ 游戏。

我们都知道 $\text{nim}$ 游戏，当所有石子堆的异或和为 $0$ 时先手输，反之亦然。

那这道题就是求：
$$
\mathop\text{xor}_{l\le a_i\le r}a_i-l
$$

我们不搞什么诡异倍增 $\text{dp}$，不如直接来暴力算一下这个式子吧！

首先我们把询问拆成两部分，以便于离线下来做：
$$
\mathop\text{xor}_{l\le a_i}a_i-l⊕\mathop\text{xor}_{ a_i>r}a_i-l
$$

这个式子还是不够美观，我们不妨再对每一个询问拆成每一位考虑。

那么对于一个询问，第 $n$ 位上的数就是（其实就是统计每一位上的 $1$ 的个数来确定异或下来的值）：
$$
\sum\lfloor\frac{a_i-l}{2^n}\rfloor \mod 2
$$
这个式子就非常美观了，我们再将其化简：
$$
\sum\lfloor\frac{a_i}{2^n}\rfloor-\sum\lfloor\frac{l}{2^n}\rfloor-\sum[\frac{a_i}{2^n}-\frac{l}{2^n}<\lfloor\frac{a_i}{2^n}\rfloor] \mod 2
$$

对于式子的前两个部分都是好求的。

而最后一步的实际意义就是减去 $\frac{l}{2^n}$ 产生的退位的贡献。

那我们就可以对于每一位对 $\frac{a_i}{2^n}$ 按照**小数部分**离散化后开一棵主席树。我们从大到小依次加入 $a_i$，每次对于每一位查询小于 $\frac{l}{2^n}$ 的**小数部分**的数的个数就可以求出答案了。

注意到我们除的都是二的幂次，所以不用担心精度问题。

空间复杂度 $O(n\log n)$，时间复杂度 $O(n\log^2 n)$。

注意本做法的常数较大。

## code
```cpp
#include<bits/stdc++.h>
#define int unsigned int
using namespace std;
const int N=2e5+10;
int Q,n,m;
int a[N];
struct pro
{
	int from,val;
};
vector<pro>q[N];
double pow2[20];
struct SGT
{
	double lsh[N];
	unordered_map<double,int>ys;
	set<double>get_used;
	int res_lsh,res;
	struct sx
	{
		int ls,rs,val;
	}t[N*2];
	int root;
	void ycl(int w)
	{
		for(int i=1;i<=m;++i)
		if(a[i])
		{
			int g=i/pow2[w];
			lsh[++res_lsh]=i/pow2[w]-g;
		}
		sort(lsh+1,lsh+res_lsh+1);
		res_lsh=unique(lsh+1,lsh+res_lsh+1)-(lsh+1);
		for(int i=1;i<=res_lsh;++i)ys[lsh[i]]=i,
		get_used.insert(lsh[i]);
	}
	void pushup(int u)
	{
		t[u].val=t[t[u].ls].val+t[t[u].rs].val;
	}
	void add(int &u,int l,int r,int x,int k)
	{
		if(!u)u=++res;
		if(l==r)
		{
			t[u].val++;
			return;
		}
		int mid=(l+r)/2;
		if(x<=mid)add(t[u].ls,l,mid,x,k);
		else add(t[u].rs,mid+1,r,x,k);
		pushup(u);
	}
	int get_size(int u,int l,int r,int x,int y)
	{
		if(x>y)return 0;
		if(!u)return 0;
		if(x<=l&&r<=y)
		{
			return t[u].val;
		}
		int mid=(l+r)/2,as=0;
		if(x<=mid)as+=get_size(t[u].ls,l,mid,x,y);
		if(y>mid)as+=get_size(t[u].rs,mid+1,r,x,y);
		return as;
	}
	void insert(double k)
	{
		int g=k;
		k=k-g;
		add(root,1,res_lsh,ys[k],1);
	}
	int smaller_than_k(double k)
	{
		if(ys[k])return get_size(root,1,res_lsh,1,ys[k]-1);
		else 
		{
			auto g=get_used.lower_bound(k);
			if(g==get_used.begin())return 0;
			g--;
			return get_size(root,1,res_lsh,1,ys[*g]);
		}
	}//实现的时候注意lsh中可能不存在k
	int used;
}tre[20];
int ans[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int i=0;i<20;i++)pow2[i]=pow(2,i);
	cin>>n>>m;
	for(int i=1,u;i<=n;++i)
	{
		cin>>u;
		a[u]^=1;
	}
	cin>>Q;
	for(int i=1,l,r;i<=Q;++i)
	{
		cin>>l>>r;
		q[l].push_back(pro{i,l});
		q[r+1].push_back(pro{i,l});
	}
	for(int w=0;w<20;++w)tre[w].ycl(w);
	for(int i=m;i>=1;i--)
	{
		if(a[i])
		{
			for(int w=0;w<20;++w)
			{
				tre[w].insert(i/pow2[w]);
				tre[w].used+=(i>>w);
			}
		}
		for(auto u:q[i])
		{
			for(int w=0;w<20;++w)
			{
				double base=(u.val)/pow2[w];
				int g=base;
				base=base-g;
				int val=tre[w].used-tre[w].t[tre[w].root].val*(u.val>>w)-tre[w].smaller_than_k(base);
				ans[u.from]^=(val%2)<<w;
			}
		}
	}
	for(int i=1;i<=Q;++i)if(ans[i])cout<<"A";else cout<<"B";
}
```

---

