# [ARC074E] RGB Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc074/tasks/arc074_c

$ N $ 個のマスが横一列に並んでいます。 マスには左から順に $ 1 $, $ 2 $, $ ... $, $ N $ と番号が振られています。

すぬけ君は、各マスを 赤 / 緑 / 青 のどれかの色で塗ろうとしています。 すぬけ君の美的感覚によると、次の $ M $ 個の条件がすべて成り立つ必要があるそうです。 $ i $ 番目の条件は次のようなものです。

- マス $ l_i $, $ l_i\ +\ 1 $, $ ... $, $ r_i $ の色の種類数がちょうど $ x_i $ である。

条件がすべて成り立つようなマスの配色は何通りでしょうか？ $ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 300 $
- $ 1\ <\ =\ M\ <\ =\ 300 $
- $ 1\ <\ =\ l_i\ <\ =\ r_i\ <\ =\ N $
- $ 1\ <\ =\ x_i\ <\ =\ 3 $

### Sample Explanation 1

次の $ 6 $ 通りです。 - RGB - RBG - GRB - GBR - BRG - BGR ただし、R / G / B はそれぞれ 赤 / 緑 / 青 のマスを表します。

### Sample Explanation 2

次の $ 6 $ 通りです。 - RRRG - RRRB - GGGR - GGGB - BBBR - BBBG

### Sample Explanation 3

次の $ 0 $ 通りです。

## 样例 #1

### 输入

```
3 1
1 3 3```

### 输出

```
6```

## 样例 #2

### 输入

```
4 2
1 3 1
2 4 2```

### 输出

```
6```

## 样例 #3

### 输入

```
1 3
1 1 1
1 1 2
1 1 3```

### 输出

```
0```

## 样例 #4

### 输入

```
8 10
2 6 2
5 5 1
3 5 2
4 7 3
4 4 1
2 3 1
7 7 1
1 5 2
1 7 3
3 4 2```

### 输出

```
108```

# 题解

## 作者：喵仔牛奶 (赞：22)

tag：DP 优化

# Solution

$\mathcal{O}(n^3)$ 的做法其他题解已经讲得蛮清楚了，我来讲一下如何优化到 $\mathcal{O}(n^2+m)$。

设 $f_{i,j,k}$ 表示从 $a_i$ 往前，第一个与 $a_i$ 颜色不同的是 $a_j$，第一个颜色与 $a_i,a_j$ 都不相同的是 $a_k$ 的方案数。

每次需要做的是将不合法状态置零，转移到 $i+1$。

将 $j,k$ 看着横纵两维，观察每次的操作：
- 将不合法状态置零相当于之保留一个矩阵，将这个矩阵之外的状态置为 $0$。
- 转移到 $i+1$ 时有三种 $(j,k),(i,k),(i,j)$。第一种滚动数组时自动继承，什么也不干；后面两种第一维都是 $i$，相当于加入一行。

我们维护 $s_i=\sum_{j=1}^{n}f_{now,i,j}+f_{now,j,i}$，这样可以 $\mathcal{O}(n)$ 加入一行。因为每次加入一行，所以非 $0$ 的状态总共只有 $\mathcal{O}(n^2)$ 个，如果可以 $\mathcal{O}(1)$ 找到一个要置零的数，就可以 $\mathcal{O}(n^2)$ 完成置零。

维护 $A_i,B_i$ 表示第 $i$ 行 / 第 $i$ 列当前的非零状态的集合。每次删除时枚举不合法的行列，枚举行列中的数删除并打上删除标记，并清空对应的集合。一个数可能在行集合被删除后在列集合中仍然存在，但我们打上了删除标记，遇到不要管就行了。

总复杂度 $\mathcal{O}(n^2+m)$。

# Code

```cpp
namespace Milkcat {
	typedef long long LL;
	typedef pair<int, int> pii;
	const int N = 1e6 + 5, mod = 1e9 + 7;
	typedef Math::Mint<mod> MI;
	int n, m, x, y, z; MI s[N], t[N];
	vector<pii> g[N]; vector<MI> f; vector<int> p, q, A[N], B[N];
	void ins(int x, int y, MI v) {
		if (v == 0) return;
		int b = SZ(f); f.pb(v), p.pb(x), q.pb(y);
		A[x].pb(b), B[y].pb(b), s[x] += v, s[y] += v;
	} // 加入状态 f[x][y]=v
	int main() {
		cin >> n >> m;
		REP(i, 1, m)
			cin >> x >> y >> z, g[y].pb(x, z);
		ins(0, 0, 1);
		REP(i, 0, n) {
			int pl = 0, pr = 1e9, ql = 0, qr = 1e9;
			for (auto [j, x] : g[i]) {
				if (x == 1) pr = min(pr, j - 1);
				if (x == 2) pl = max(pl, j), qr = min(qr, j - 1);
				if (x == 3) ql = max(ql, j);
			} // 求出 j,k 的取值范围
			REP(j, 0, i) {
				if (j >= pl && j <= pr) continue;
				for (int x : A[j])
					s[p[x]] -= f[x], s[q[x]] -= f[x], f[x] = 0;
				A[j].clear();
			}
			REP(j, 0, i) {
				if (j >= ql && j <= qr) continue;
				for (int x : B[j])
					s[p[x]] -= f[x], s[q[x]] -= f[x], f[x] = 0;
				B[j].clear();
			} // 置零
			if (i < n) {
				REP(j, 0, i) t[j] = s[j];
				REP(j, 0, i) ins(i, j, t[j]);
			} // 转移到 i+1
		}
		MI rs = 0;
		REP(i, 0, n) {
			rs += s[i], s[i] = 0;
			A[i].clear(), B[i].clear(), g[i].clear();
		}
		f.clear(), p.clear(), q.clear();
		cout << rs / 2 << '\n'; // f[i][j] 被计算了两次！
		return 0;
	}
}
```

---

## 作者：Krystallos (赞：16)

一道还不错的动规题，式子也没啥毒瘤的。唯一的遗憾就是我没见过这种动规题，然后今天 nodgd 拿出来考的时候毫无头绪  
统计方案容易想到动规，但是此题对方案有限制，所以设出来的状态必须要能够快速判断出是否满足限制。这里设的是 $f_{i, j, k}$，表示从 $a_i$ 往前，第一个与 $a_i$ 颜色不同的是 $a_j$，第一个颜色与 $a_i, a_j$ 都不相同的是 $a_k$ 这种情况的方案数，当然 $i > j > k$（特别地，当 $j = 0$ 时 $k$ 可以为 $0$）  
如果我们有一个形如 $(l, r, x)$ 的限制，那么这样的三元组 $(i, j, k)$（$r = i$） 它应该是不符合限制的（即 $f_{i, j, k}$ 需要设为 $0$）：  
* $x = 1$ 且 $l \leq j$，因为 $[l, r]$ 这段区间内出现了一个与 $a_i$ 不同的 $a_j$
* $x = 2$ 且 $l \leq k$ 或 $j < l$，前者是因为出现了第三种既不同于 $a_i$ 也不同于 $a_j$ 的颜色，后者是因为距离 $a_i$ 最近的不同于 $a_i$ 的 $a_j$ 并不在 $[l, r]$ 内，即 $[l, r]$ 这段区间内只有一个颜色。
* $x = 3$ 且 $k < l$ 因为距离 $a_i$ 最近的第三种颜色 $a_k$ 在 $[l, r]$ 之外，即 $[l, r]$ 内至多只有两种颜色  

tips：当我们讨论状态到 $i$ 时，我们需要把所有 $r = i$ 的限制拿出来，并根据这些限制剔除不合法的状态

首先我们可以知道 $f_{1, 0, 0} = 3$，因为 $a_1$ 可以在三种颜色中任选  
那么剔除不合法的状态后，可以考虑如何从 $a_i$ 转移到 $a_{i + 1}$：  
* $a_{i + 1} = a_i$，那么 $f_{i + 1, j, k}$ 会继承 $f_{i, j, k}$ 的方案数
* $a_{i + 1} = a_j$，那么 $f_{i + 1, i, k}$ 会继承 $f_{i, j, k}$ 的方案数
* $a_{i + 1} = a_k$，那么 $f_{i + 1, i, j}$ 会继承 $f_{i, j, k}$ 的方案数

当我们把所有 $f$ 都算出来后，答案就出来了：
$$ans = \sum_{j = 0}^{j < n}\ \  \sum_{k = 0}^{k < j\ (\text{如果} j = 0 \text{那么} k < 1)} f_{n, j, k}$$

code:
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
const int mod = 1e9 +7;
const int nn = 305;
int n, m;
struct query {
	int l, r, cnt;
	inline int operator< (const query &p)const {
		return r < p.r;
	}
} a[nn];
int f[nn][nn][nn];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].cnt);
	std::sort(a + 1, a + m + 1); //对所有限制按 r 升序排序
	f[1][0][0] = 3; //初值
	int pt = 1;
	for (int i = 1; i <= n; i++) {
		while (pt <= m && a[pt].r <= i) { //只要当前这个限制 r = i 那么剔除不合法状态
			for (int j = 0; j < i; j++) {
				int limit = j ? j - 1 : 0;
				for (int k = 0; k <= limit; k++) {
					if (a[pt].cnt == 1 && a[pt].l <= j) //上面列出的三种不合法的 (i, j, k)
						f[i][j][k] = 0;
					if (a[pt].cnt == 2 && (a[pt].l <= k || j < a[pt].l))
						f[i][j][k] = 0;
					if (a[pt].cnt == 3 && k < a[pt].l)
						f[i][j][k] = 0;
				}
			}
			++pt;
		}
		if (i == n) break; //如果 i = n 那么下面就不需要继续递推了
		for (int j = 0; j < i; j++) {
			int limit = j ? j - 1 : 0;
			for (int k = 0; k <= limit; k++) {
				if (!f[i][j][k]) continue;
				f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k]) % mod; //上面讲的三种转移方式
				f[i + 1][i][k] = (f[i + 1][i][k] + f[i][j][k]) % mod;
				f[i + 1][i][j] = (f[i + 1][i][j] + f[i][j][k]) % mod;
			}
		}
	}
	int ans = 0;
	for (int j = 0; j < n; j++) { //统计答案
		int limit = j ? j - 1 : 0;
		for (int k = 0; k <= limit; k++)
			ans = (ans + f[n][j][k]) % mod;
	}
	printf("%d", ans);
}

```

---

## 作者：RicardoShips (赞：12)

先说几句题外话，这题是国家集训队作业

不过个人认为$AtCoder$上面的题质量真心不错

这题我硬是调了大半天，坑点还是有几个

而且这题竟然没有题解？？？赶紧过来水一发

这题正常人一眼过去就应该是$DP$，别告诉我你不是正常人

至于为什么显然是$DP$。。。方案数不是$DP$是什么？

因为颜色的数量很少，只有三种

所以可以直接上三维$DP$，话说这好像还是我第一道三维$DP$

所以我们可以用$f$ $[$ $i$ $]$ $[$ $j$ $]$ $[$ $k$ $]$来记录状态，统计方案数

$i$是当前枚举到的位置，$j$和$k$则分别是另外两种颜色最后出现的位置

建议将$j$设置为另外两种颜色靠后的那一种，枚举起来比较方便

然后思考状态转移方程，这里要分三种情况情况讨论

- $i+1$位置上的颜色与$i$位置上的颜色一致

  那么显然$j$和$k$的位置不变，$f$ $[$ $i+1$ $]$ $[$ $j$ $]$ $[$ $k$ $]$ $=$ $f$ $[$ $i$ $]$ $[$ $j$ $]$ $[$ $k$ $]$
  
- $i+1$位置上的颜色与$j$位置上的颜色一致

  那么$i$位置上的颜色就要后移一位，$f$ $[$ $i+1$ $]$ $[$ $i$ $]$ $[$ $k$ $]$ $=$ $f$ $[$ $i$ $]$ $[$ $j$ $]$ $[$ $k$ $]$
  
- $i+1$位置上的颜色与$k$位置上的颜色一致

  那么$i$和$j$位置上的颜色都要后移一位，$f$ $[$ $i+1$ $]$ $[$ $i$ $]$ $[$ $j$ $]$ $=$ $f$ $[$ $i$ $]$ $[$ $j$ $]$ $[$ $k$ $]$
  
接下来我们以右端点为限制考虑贡献，这里脑补一下

根据$j$和$k$的大小关系判断区间内的颜色数量

不满足区间限制的直接赋值为0，不参与贡献

最后统计答案即可，这里要注意开$long$ $long$

因为之前只是统计了区间内颜色数量而不是统计颜色方案数

就是之前没有计算区间内具体有什么颜色

所以统计答案之后一定要将$ans$乘以$3$

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int f[333][333][333];
int m,n,l,r,x,ans,size;
vector < pair < int , int > > rer[333];
inline void update(int &x,int y){ x=((long long)1*x+y+mod)%mod; }
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&l,&r,&x);
        rer[r].push_back(make_pair(l,x));
    }
    f[1][0][0]=1;
    for(register int i=1;i<=n;++i)
    {
        size=rer[i].size();
        for(register int j=0;j<size;++j)
        {
            l=rer[i][j].first;x=rer[i][j].second;
            for(register int k=0;k<i;++k)
                for(register int p=0;p<=max(0,k-1);++p)
                {
                    if(x==1) { if(l<=k) f[i][k][p]=0; }
                    else if(x==2) { if(k<l||l<=p) f[i][k][p]=0; }
                    else { if(p<l) f[i][k][p]=0; }
                }
        }
        if(i==n) break ;
        for(register int j=0;j<i;++j)
            for(register int k=0;k<=max(0,j-1);++k)
                if(!f[i][j][k]) continue ;
                else
                {
                    update(f[i+1][j][k],f[i][j][k]);
                    update(f[i+1][i][k],f[i][j][k]);
                    update(f[i+1][i][j],f[i][j][k]);
                }
    }
    for(register int j=0;j<n;++j)
        for(register int k=0;k<=max(0,j-1);++k)
            update(ans,f[n][j][k]);
    ans=((long long)3*ans)%mod;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：人间温柔 (赞：6)

题目要求方案数，很显然就是 $dp$。

都说动态规划最难的是设计状态和列方程，我建议大家还是先自己思考一下再来看解答。

红绿蓝三种颜色，我们先不管它们叫什么，姑且将它们命名为“一种颜色”“第二种颜色”“另外一种颜色”。

假设 $f[i][j][k]$ 表示的含义是：目前已经给 $i$ 号点涂色（涂了“一种颜色”），且“第二种颜色”“另外一种颜色”最后一次出现的格子编号分别为 $j,k$ 时的方案数量。

![截图20220805160133.png](https://yacs-public.oss-cn-hangzhou.aliyuncs.com/image/1659686520520.png)

为了方便表述，记 $col[i]$ 表示 $i$ 号格子的颜色。现在为了列出转移方程，想象自己站在当前的局面往后决策（可以借助上图帮助理解）：

+ 如果 $col[i+1]=col[i]$，也就是 $i+1$ 号格子与 $i$ 号格子颜色相同，那么这个时候，“第二种颜色”最后一次出现的位置就是 $j$，“另外一种颜色”最后一次出现的位置就是 $k$，所以此时的方程：$f[i+1][j][k]+=f[i][j][k]$。

+ 如果 $col[i+1]=col[j]$，那么此时“第二种颜色”最后一次出现的位置就是 $i$，“另外一种颜色”最后一次出现的位置就是 $k$，所以此时的方程：$f[i+1][i][k]+=f[i][j][k]$。

+ 如果 $col[i+1]=col[k]$，按照上面的思路，可以列出方程：$f[i+1][i][j]+=f[i][j][k]$。

推出了状态转移方程，不要忘记考虑题目里的限制 $(l,r,x)$。

当我们在决策 $i$ 号格子的时候，我们把所有右端点等于 $i$ 的区间找出来，去判断 $l,i,j,k$ 之间的大小关系，便可以知道那些状态时不合法的了，对于不合法的状态，我们就令这个状态对应的 $f$ 数组的值为 $0$，这样它对答案的贡献就为 $0$。

+ 当 $x=1$ 时，区间内只有一个颜色，$r=i$ 作为它的右端点，那么这个区间内其他所有格子的颜色都必须与 $i$ 相同，那么区间左端点 $l$ 的取值范围就是 $j<l\leq i$。

+ 当 $x=2$ 时，$r=i$ 作为它的右端点，那么这个区间内其他所有格子的颜色要么与 $i$ 相同，要么与 $j$ 相同，区间左端点 $l$ 的取值范围就是 $k<l\leq j$。

+ 当 $x=3$ 时，按照同样的逻辑，$l\leq k$。

反不满足以上条件的状态，我们就赋值为 $0$。

最后就是答案和边界。

【边界】 $f[1][0][0]=1$

【答案】
$$
3\times \sum_{j=0}^{n-1}\ \  \sum_{k=0}^{max(0,j-1)} f[n][j][k]
$$

这里容易发现两个问题：
1. 为什么最前面需要乘以 $3$？因为我们在最开始说了，不考虑颜色种类，我们只考虑了颜色的相对关系。因此，如果一个格子可以填“一种颜色”，那么它也一定可以填“第二种颜色”与“另外一种颜色”，只需要把其他的颜色修改掉就好了。所以总共有 $3$ 种可能，需要乘以 $3$。

2. 为什么 $k$ 的上界是 $max(0,j-1)$？$j-1$ 很好理解，就是因为 $k$ 必须在 $j$ 的左边。至于为什么还要和 $0$ 比较大小，是因为 $j$ 的下界是 $0$，$k$ 在它的左边，那 $k$ 只能是负数，就不对了。

至此，我们就完成了此题，下面是 AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=305;
const int mod=1000000007;

int n,m;
long long ans=0;
int f[maxn][maxn][maxn];
struct node{
	int l,x;
};
vector<node>a[maxn];

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int l,r,x;
		cin>>l>>r>>x;
		a[r].push_back((node){l,x}); //以 r 作为一个关键字存储区间限制。 
	}
	f[1][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			for(int k=0;k<=max(0,j-1);k++){
				for(int t=0;t<a[i].size();t++){
					int l=a[i][t].l; //取出以 r 为右端点的所有区间 
					int x=a[i][t].x;
					if(x==1 && l<=j) f[i][j][k]=0;          //这里三行，就是把所有不合法的情况赋值为 0 
					if(x==2 && (l>j || l<=k)) f[i][j][k]=0;
					if(x==3 && l>k) f[i][j][k]=0;
				}
			}
		}
		for(int j=0;j<i;j++){ //计数 
			for(int k=0;k<=max(0,j-1);k++){
				f[i+1][j][k]=(f[i+1][j][k]+f[i][j][k])%mod; //col[i+1]==col[i]
				f[i+1][i][k]=(f[i+1][i][k]+f[i][j][k])%mod; //col[i+1]==col[j]
				f[i+1][i][j]=(f[i+1][i][j]+f[i][j][k])%mod; //col[i+1]==col[k]
			}
		}
	}
	for(int j=0;j<n;j++){
		for(int k=0;k<=max(0,j-1);k++){
			ans=(ans+f[n][j][k])%mod;  //累计答案。记得 ans 要开 long long。 
		}
	}
	cout<<(ans*3ll)%mod<<endl;
	return 0;
}
```


---

## 作者：CYJian (赞：5)

## ARC074E

简单 dp 题。

考虑设置状态为 $f_{i, j, k}$ 表示考虑到第 $i$ 个位置，与当前位置颜色不同的球最后出现的位置为 $j$，与这两种颜色都不同的球最后出现的位置为 $k$ 的方案数。

转移不难想到有一下几种：

1. 第 $i + 1$ 个位置的颜色与第 $i$ 个位置的颜色相同：$f_{i,j,k} \rightarrow f_{i + 1,j,k}$
2. 第 $i + 1$ 个位置的颜色与第 $j$ 个位置的颜色相同：$f_{i,j,k} \rightarrow f_{i + 1,i,k}$
3. 第 $i + 1$ 个位置的颜色与第 $k$ 个位置的颜色相同：$f_{i,j,k} \rightarrow f_{i + 1,i,j}$

然后再考虑限制：

每个限制可以看做限制了右端点位置 $r$ 上的 $f$ 的后两维。

$x=3$ 的时候会让后两维都 $\ge l$；
$x=2$ 的时候会让后两维中大的那个 $\ge l$，小的那个 $< l$；
$x=1$ 的时候会让后两维都 $< l$；

然后大概就限制一下转移就完事了。

${\rm Code}$

```cpp
/********************************************************************************
	
	Code by a weak man who named CYJian, and he hopes the code can get more points.

	Algorithm: dp

 ********************************************************************************/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int __SIZE = 1 << 18;
char ibuf[__SIZE], *iS, *iT;

#define ge (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
#define ri read_int()
#define rl read_ll()
#define FILE(s) freopen(s"in", "r", stdin), freopen(s"out", "w", stdout)

template<typename T>
inline void read(T &x) {
	char ch, t = 0; x = 0;
	while(!isdigit(ch = ge)) t |= ch == '-';
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = ge;
	x = t ? -x : x;
}
inline int read_int() { int x; return read(x), x; }
inline ll read_ll() { ll x; return read(x), x; }

template<typename T> inline void chkmin(T&a, T b) { a = a < b ? a : b; }
template<typename T> inline void chkmax(T&a, T b) { a = a > b ? a : b; }

const int mod = 1e9 + 7;

inline void Add(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }

int f[310][310][310];
vector<pair<int, int> >limit[310];

inline bool chk(int l, int x, int r) { return l <= x && x < r; }

int main() {
#ifdef LOCAL
	FILE("");
#endif
	int n = ri, m = ri;
	for(int i = 1; i <= m; i++) {
		int L = ri, R = ri, X = ri;
		limit[R].push_back(make_pair(L, X));
	} f[0][0][0] = 1;
	for(int i = 1; i <= n; ++i) {
		int la = 0, ra = i;
		int lb = 0, rb = i;
		for(auto pr : limit[i]) {
			int p = pr.first;
			if(pr.second == 3) chkmax(la, p), chkmax(lb, p);
			if(pr.second == 2) chkmin(rb, p), chkmax(la, p);
			if(pr.second == 1) chkmin(ra, p), chkmin(rb, p);
		}
		for(int a = 0; a < i; ++a) {
			for(int b = 0; !b || b < a; ++b) {
				int F = f[i - 1][a][b], c = i - 1;
				if(chk(la, a, ra) && chk(lb, b, rb)) Add(f[i][a][b], F);
				if(chk(la, c, ra) && chk(lb, a, rb)) Add(f[i][c][a], F);
				if(chk(la, c, ra) && chk(lb, b, rb)) Add(f[i][c][b], F);
			}
		}
	} int res = 0;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			Add(res, f[n][i][j]);
	printf("%d\n", res);
	return 0;
}
```

---

## 作者：天梦 (赞：3)

### [RGB Sequence](https://www.luogu.com.cn/problem/AT2567)

考虑只要知道每种颜色最后一次出现的下标就可以知道每一段区间满足不满足标准。

我们也不需要每次都处理不合法的情况，只是需要在它更新别人时判断出来它是不合法的，或是让已经判断出的不合法的来更新它。根据归纳法容易得出，不存在其他情况。

### 状态设计

状态中需要记录每种颜色最后结尾位置 $i,j,k$ ，而总长度 $len=\max(i,j,k)$ ，所以状态为 $f_{i,j,k}$ ，因为3种颜色并无差别，所以我们不妨设 $i$ 是最靠右的颜色下标，$k$是最靠左的颜色下标。

由此，考虑第 $i+1$ 个是什么颜色，有：
$$
f_{i+1,j,k}=f_{i+1,j,k}+f_{i,j,k}\\
f_{i+1,i,j}=f_{i+1,i,j}+f_{i,j,k}\\
f_{i+1,i,k}=f_{i+1,i,k}+f_{i,j,k}
$$
上面三种情况分别对应填 $i,k,j$ 所代表的颜色。注意，状态 $i,j,k$ 所代表的颜色是不固定的。

因为不知道最开始 $i$ 所代表的颜色是哪一种颜色，所以答案要乘 $3$ ，注意不是乘 $6$ ，因为最开始 $i$ 所代表的颜色已经不重不漏的划分完了该样本空间。

代码：

~~~c++
#define dd double
#define ld long double
#define ll long long
#define int long long
#define ull unsigned long long
#define N 400
#define M number
using namespace std;

const int INF=0x3f3f3f3f;
const int mod=1e9+7;

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

inline int Max(int a,int b){
    return a>b?a:b;
}

struct rode{
    int l,x;
    rode() {}
    rode(int l,int x) : l(l),x(x) {}
};
vector<rode> a[N];

int n,t,f[N][N][N],ans;

inline bool check(int q,int w,int c){
    int r=q;
    int num;
    for(int i=0;i<a[r].size();i++){
        num=1;int l=a[r][i].l,x=a[r][i].x;
        if(l<=w) num++;
        if(l<=c) num++;
        if(num<x||num>x) return 0;
    }
    return 1;
}

signed main(){
    n=read();t=read();
    for(int i=1;i<=t;i++){
        int l=read(),r=read(),x=read();
        a[r].push_back(rode(l,x));
    }
    f[1][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i-1;j++){
            for(int k=0;k<=Max(0,j-1);k++){
                if(!check(i,j,k)) continue;
                (f[i+1][j][k]+=f[i][j][k])%=mod;
                (f[i+1][i][j]+=f[i][j][k])%=mod;
                (f[i+1][i][k]+=f[i][j][k])%=mod;
                if(i==n) (ans+=f[i][j][k])%=mod;
            }
        }
    }
    cout<<ans*3%mod;
    return 0;
}
~~~



---

## 作者：洁咪 (赞：2)

考虑到，如果将这位具体填哪种颜色放入状态会带来很多麻烦，于是先不考虑是哪一种。  
设 $f[i][a][b]$ 表示当前填到第 $i$ 位，另外两种颜色上一次出现在 $a$ 处和 $b$ 处。 
于是对于该位填三种颜色直接三种转移，最后统计答案时乘以 $3$ 即可。


------------
Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX=305,mod=1e9+7;
ll read() {
	char ch=getchar();ll x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();}
	return x*f;
}

ll n,m,ans;
ll f[MAX][MAX][MAX];
vector<pair<ll,ll> >vis[MAX];

bool pd(ll u,ll a,ll b) {
	for(auto v:vis[u]) {// 遍历以 u 点为终点的区间 
		ll l=v.first,x=v.second;
		if(((a>=l?1:0)+(b>=l?1:0)+1)!=x)
			return 0;
	}
	return 1;
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read(); m=read();
	for(ll i=1,l,r,x; i<=m; i++) {
		l=read(); r=read(); x=read();
		vis[r].push_back({l,x});
	}
	
	f[1][0][0]=1;
	for(ll i=1; i<=n; i++) {
		for(ll a=0; a<i; a++) {
			for(ll b=0; b<i; b++) {
				if(!pd(i,a,b)) continue;
				(f[i+1][a][b]+=f[i][a][b])%=mod;// 这位填和上一位一样的 
				(f[i+1][i][a]+=f[i][a][b])%=mod;// 填第二维代表的颜色 
				(f[i+1][i][b]+=f[i][a][b])%=mod;// 填第三维代表的颜色 
				if(i==n) (ans+=f[i][a][b])%=mod;
			}
		}
	}
	
	printf("%lld\n",ans*3ll%mod);
	
	return 0;
}

```


---

## 作者：jockbutt (赞：2)

不会吧不会吧，我不会真的做起国家集训队作业了吧。

说句题外话，国家集训队也没有想象的那么奆，他们也是人，通过努力也是有希望AKIOI的~~（这么说来我连人都不如了）~~


------------
# 开始！
### 一.题意

这是我们学校的一次考试题，题意由一位~~很不要脸的~~巨佬nodgd提供。

nodgd出了一道坑爹题但还没造数据，这道题的数据是一个长度为$n$的颜色序列，每个颜色都是红绿蓝三种颜色之一，且满足$m$个约束条件，每个条件都形如：第$  l_i$到第$r_i$个颜色共有$x_i$种。

请你计算共有多少种符合条件的颜色序列，答案$mod 10^9+7$。

### 二.基础思想和算法
当然是一道dp，地球人都想得到，~~可是考试时我却写了dfs嘤嘤嘤~~。

### 三.解法

先设dp代表什么，观察数据范围$n=300$，多半是个$O(n^3)$的时间复杂度，然后，刚好，就是有3种颜色。

于是就~~轻而易举~~地得出了一个三维的$dp[i][j][k]$表示在染第$i$个颜色中，其他的两个颜色最后出现的位置为$j$和$k$，这里为了避免重复，设$k>j$。

然后呢，分三种情况讨论：

#### 1.第$i$个颜色和$i-1$的颜色一样时
$dp[i+1][j][k]+=dp[i][j][k]$
#### 1.第$i$个颜色和$j$的那个颜色一样时
$dp[i+1][i][k]+=dp[i][j][k]$
#### 1.第$i$个颜色和$k$的那个颜色一样时
$dp[i+1][i][j]+=dp[i][j][k]$

然后，然后就完了。。。诶，好像那些限制条件还没有讲呢

### 四.限制条件

这个让我想了半天，~~最后看题解才知道~~以$r_i$为基准，将$dp[r_i]$的那些不符合条件的$dp$值全部改成$0$。

最后，你按照这个写，你会发现你的输出总是会是标准答案的三分之一。Why?
因为有三种颜色，答案最后要乘$3$

### 五.Code

```
#include <bits/stdc++.h>//代码经过暴力压行，阅读起来可能会引起极度舒适
using namespace std;
#define R register
inline int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;}
const int maxn=340,modd=1e9+7;//快读，我们学校老师流行卡常，不加有可能会TLE
int n,m,dp[maxn][maxn][maxn];
vector <pair <int,int> > G[maxn];
int tot=1;
int main(){
//	freopen("colorful.in","r",stdin);
//	freopen("colorful.out","w",stdout);
	memset(dp,0,sizeof(dp));
	n=read(),m=read();
	for(R int i=1,l,r,x;i<=m;i++)	{l=read(),r=read(),x=read();G[r].push_back(make_pair(l,x));}//输入
	dp[1][0][0]=1;
	for(R int i=0;i<=n;i++)
	{
		int size=G[i].size();
		for(R int j=0;j<size;j++)
		{
			int l=G[i][j].first,x=G[i][j].second;
			for(R int k=0;k<i;k++)
				for(R int p=0;p<=max(0,k-1);p++)
				{
					if(x==1)	if(l<=k) dp[i][k][p]=0;
                    if(x==2)	if(k<l||l<=p) dp[i][k][p]=0;
                    if(x==3)	if(p<l) dp[i][k][p]=0;//限制条件
				}
		}
		if(i==n)	break;
		for(R int j=0;j<i;j++)
			for(R int k=0;k<=max(0,j-1);k++)
			{
				if(!dp[i][j][k])	continue;
				dp[i+1][j][k]=(dp[i+1][j][k]+dp[i][j][k])%modd;
				dp[i+1][i][j]=(dp[i+1][i][j]+dp[i][j][k])%modd;
				dp[i+1][i][k]=(dp[i+1][i][k]+dp[i][j][k])%modd;//转移
			}
	}
	long long ans=0;
	for(R int j=0;j<n;j++)
		for(R int k=0;k<=max(0,j-1);k++)	ans=(ans+(long long)dp[n][j][k])%(long long)modd;
	printf("%lld",(3ll*ans)%modd);
	return 0;
   cout<<"I AK IOI"<<endl;//加油你能行
}
```


---

## 作者：EuphoricStar (赞：2)

## 思路

考虑 dp。

显然我们不需要知道每个元素具体的颜色，只需要知道他们之间相对的异同关系就可以判断是否合法。

于是设计状态：$f_{i,j,k}$ 表示当前处理到第 $i$ 个位置，第一个与 $a_i$ 不同的元素下标为 $j$，第一个与 $a_i$ 和 $a_j$ 都不同的元素下标为 $k$，为 $0$ 则表示不存在。

显然需要满足 $j < i$，$k < \max(1,j)$。

状态转移方程：

$f_{i+1,j,k} = f_{i+1,j,k}+f_{i,j,k}$，表示 $a_{i+1}$ 与 $a_{i}$ 颜色相同的情况。

$f_{i+1,i,k} = f_{i+1,i,k}+f_{i,j,k}$，表示 $a_{i+1}$ 与 $a_{j}$ 颜色相同的情况。

$f_{i+1,i,j} = f_{i+1,i,j}+f_{i,j,k}$，表示 $a_{i+1}$ 与 $a_{k}$ 颜色相同的情况。

在转移中判断状态是否合法即可。

最后还要注意，由于一开始不知道 $a_i$ 是什么颜色，于是计算答案时要乘 $3$。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 310;
const ll mod = 1000000007;

struct node {
	ll x, v;
	node(ll a, ll b) {
		x = a;
		v = b;
	}
};

vector<node> a[maxn];

ll n, m, f[maxn][maxn][maxn];

bool check(ll x, ll y, ll z) {
	for (int i = 0; i < (int)a[x].size(); ++i) {
		ll l = a[x][i].x;
		ll cnt = (y >= l) + (z >= l) + 1;
		if (cnt != a[x][i].v) {
			return 0;
		}
	}
	return 1;
}

void solve() {
	scanf("%lld%lld", &n, &m);
	while (m--) {
		ll l, r, x;
		scanf("%lld%lld%lld", &l, &r, &x);
		a[r].pb(node(l, x));
	}
	f[1][0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			for (int k = 0; k < max(1, j); ++k) {
				if (!check(i, j, k)) {
					continue;
				}
				f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k]) % mod;
				f[i + 1][i][j] = (f[i + 1][i][j] + f[i][j][k]) % mod;
				f[i + 1][i][k] = (f[i + 1][i][k] + f[i][j][k]) % mod; 
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < max(1, i); ++j) {
			if (check(n, i, j)) {
				ans = (ans + f[n][i][j]) % mod;
			}
		}
	}
	printf("%lld\n", ans * 3 % mod);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```


---

## 作者：Sata_moto (赞：1)


[$ \large{}\color {#6495ED} \mathcal{MyBlog} $](https://xjx885.coding-pages.com/)

---

$
$

## 前言：


$\quad \quad$ 本题似乎是：乍看上去好难好难，做起来还好还好的那种题呢。



---

$
$

## 题目大意：

$\quad \quad$ 有一个序列 $\left\{a_{N}\right\}$，要给序列中的每个元素一种颜色：红/绿/蓝。有 M 条限制 $(l,r,x)$，表示格子 $l-r$ 中颜色的种数要恰好为 $x$，问可行的方案数。

$\quad \quad$ 数据范围：$1 \leq N \leq 300 , 1 \leq\ M\leq 300
,1\leq\ l_{i} \leq r_i\ \leq\ N ,1 \leq x \leq 3$


---


$
$
## 思路分析:

$\quad \quad$ 拿到题目感觉无从下手，制约+方案数的组合似乎是个DP。

$\quad \quad$ 注意到：颜色仅仅只有三种，而且制约并非针对颜色段数，而是针对区间**颜色种数**。

$\quad \quad$ 颜色段数和颜色种数区别相当大了，前者是数据结构的考点之一，后者才是DP状态可以维护出来的东东。

$\quad \quad$ 我们考虑把三种颜色分别表示到DP状态中。

$\quad \quad$ 注意本题数据范围比较小，我们可以直接开三维的状态进行处理。

$\quad \quad$ 不妨令 $f(k,i,j)$ 表示当前处理完了数列的第 $k$ 位，除去第 $k$ 位的颜色，另外两种颜色中，有一种颜色最后出现在了第 $i$ 位，另一种颜色最后出现在了第 $j$ 位时的方案数。

$\quad \quad$ 这样就把三种颜色最后出现的位置都表示出来了，我们不妨令 $i>j$，这样转移更为方便。

$\quad \quad$ 为何表示三种颜色最后出现的位置？当我们处理完了某一个点后，我们可以利用三种颜色最后出现的位置，判断当前的状态是否符合约束条件。

$\quad \quad$ 比如说：有一状态 $f(5,4,2)$，有一约束要求 $[3,5]$区间中仅存在两种颜色。

$\quad \quad$ 因为 $5>3$，所以区间中有 $5$ 号位的颜色，同理，区间中也有 $4$ 号位的颜色，但没有 $2$ 号位的颜色，因为它最后一次出现是在 $2$ 号位置，而区间左端点为 $3 $ 号。

$\quad \quad$ 因此，区间 $[3,5]$ 中有两种颜色，满足约束条件，当前状态可以继续转移。

$\quad \quad$ 如果不满足约束条件，我们可以将当前状态清空，不让它参加转移。

$\quad \quad$ 状态转移是在下一位置分别填入三种颜色的过程，依次列举在下面：

- $\quad \quad$ `f[k + 1][i][j] += f[k][i][j]`  ，填入 $k$ 位置的颜色。

- $\quad \quad$ `f[k + 1][k][j] += f[k][i][j]`  ，填入 $i$ 位置的颜色。

- $\quad \quad$ `f[k + 1][k][i] += f[k][i][j]`  ，填入 $j$ 位置的颜色。

$\quad \quad$ 如果某一种颜色不存在怎么办？我们可以用 $0$ 表示。

$\quad \quad$ 比如我们的初始状态 $f(1,0,0)=3$ ，因为只有一种颜色，所以 $i,j$ 均用 $0$ 表示。

$\quad \quad$ 注意：因为第一个位置有三种颜色可以填，所以初态的值为 $3$。

$\quad \quad$ 我们注意到：如果 $i=j=0$ （因为我们规定了 $i>j$ ，所以 $i=j$ 的情况仅会在 $i=0\ \  and\ \ j=0$ 的条件下出现），那么我们转移方程的第二条与第三条就会完全等价。

$\quad \quad$ 但这并不意味这我们算重了，因为这里确实有两种颜色可以填。

$\quad \quad$ 比如说，假设我们第一个位置选了红色，那么第二个位置可以选蓝色或者绿色，虽然它们对应同一个状态，但它们显然是两种方案。

$\quad \quad$ 然后就没有了什么难点，但代码还是要注意不少细节。

---

$
$

## 代码实现：


```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 310;
const int MOD = 1e9 + 7;

struct node
{
	int l, x;

	node (int a, int b)
	{
		l = a, x = b;
	}
	node () { }
};
vector <node > com[N];

int n, m;
ll f[N][N][N];

inline int read()
{
	int x = 0, ch = '~';

	while(!(ch >= '0' && ch <= '9')) ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1), x += ch - '0', ch = getchar();

	return x;
}

bool check(int k, int i, int j)
{
	bool flag = true;

	for(int c = 0; c < (int )com[k].size(); c++)
	{
		int l = com[k][c].l, x = com[k][c].x, cnt = 0;

		if(k >= l) cnt++;
		if(i >= l) cnt++;
		if(j >= l) cnt++;

		if(cnt != x)
		{
			flag = false;
			break;
		}
	}

	if(!flag)
		f[k][i][j] = 0;

	return flag;
}

int main()
{
	n = read(), m = read();
	for(register int k = 1; k <= m; k++)
	{
		int l = read(), r = read(), x = read();
		com[r].push_back(node(l, x));
	}

	f[1][0][0] = 3;

	for(register int k = 1; k < n; k++)
		for(int i = 0; i < k; i++)
			for(int j = 0; !j || j < i; j++)
			{
				if(!check(k, i, j)) continue;

				f[k + 1][i][j] += f[k][i][j], f[k + 1][i][j] %= MOD;
				f[k + 1][k][i] += f[k][i][j], f[k + 1][k][i] %= MOD;
				f[k + 1][k][j] += f[k][i][j], f[k + 1][k][j] %= MOD;
			}

	ll answ = 0;
	for(register int k = 0; k < n; k++)
		for(int i = 0;!i || i < k; i++)
			if(check(n, k, i))
				answ += f[n][k][i], answ %= MOD;

	printf("%lld", answ);

	return 0;
}
```


---

$
$

## 结语：

$\quad \quad$ 如果本题解有BUG，还请评论或私信作者。

---

$$ \large{END}$$

---

## 作者：Kinandra (赞：1)

标签: DP.

设计状态 $f[i][a][b]$ 表示已经涂完了前 $i$ 个格子, 与第 $i$ 个格子外的两种颜色最靠后的位置一个在 $a$, 另一个在 $b(a>b)$ 的合法方案数.

转移很简单, 考虑 $f[i][a][b]$ 的转移, 考虑枚举 $i+1$ 个格子填的颜色:

* 与 $i$ 颜色相同, 转移到 $f[i+1][a][b]$ .
* 与 $a$ 颜色相同, 转移到 $f[i+1][i][b]$ .
* 与 $b$ 颜色相同, 转移到 $f[i+1][i][a]$ .

注意这样跑出来的答案是不带标号的, 最后要乘上相应的系数.

```cpp
#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int read();
void Add(int &x, int y) { (x += y) >= mod ? x -= mod : x; }
int f[302][302][302];
struct P {
    int l, x;
};
vector<P> p[302];

bool check(int a, int b, int c) {
    for (int i = 0; i < p[a].size(); ++i)
        if (1 + (b >= p[a][i].l) + (c >= p[a][i].l) != p[a][i].x) return 0;
    return 1;
}

int main() {
    int n = read(), m = read();
    for (int i = 1, l, r, x; i <= m; ++i) {
        l = read(), r = read(), x = read();
        if (r - l + 1 < x) return puts("0"), 0;
        p[r].push_back((P){l, x});
    }

    f[1][0][0] = 1;
    for (int i = 1; i < n; ++i) {
        if (check(i, 0, 0))
            Add(f[i + 1][0][0], f[i][0][0]), Add(f[i + 1][i][0], f[i][0][0]);
        for (int j = 1; j < i; ++j) {
            for (int k = 0, x; k < j; ++k) {
                if (!check(i, j, k)) continue;
                Add(f[i + 1][j][k], f[i][j][k]);
                Add(f[i + 1][i][k], f[i][j][k]);
                Add(f[i + 1][i][j], f[i][j][k]);
            }
        }
    }
    long long c[4];
    c[0] = 6, c[1] = 6;
    int res = 0;
    if (check(n, 0, 0)) res = 3ll * f[n][0][0] % mod;
    for (int j = 1; j < n; ++j)
        for (int k = 0; k < j; ++k)
            if (check(n, j, k)) Add(res, c[(!j) + (!k)] * f[n][j][k] % mod);
    printf("%d\n", res);
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```


---

## 作者：小木虫 (赞：0)

### Preface  
一道 dp 好题。
### Problem  
有一个序列 $\left\{a_{N}\right\}$，要给序列中的每个元素一种颜色：红/绿/蓝。有 $M$ 条限制 $(l,r,x)$，表示格子 $l\sim r$ 中颜色的种数要恰好为 $x$，问可行的方案数。
### Solution  
发现这是一个存在性的决策问题，也就是我们不关心颜色出现了几次，我们可以立刻设计出一个 dp 状态：  
$dp_{i,st}$ 其中 $i$ 表示决策到哪里，$st$ 状压三种颜色有没有出现过。  
发现这个状态不能满足我们的要求，因为我们需要知道一段之内三种颜色有没有出现过。这个状态是 $O(n)$ 的，可改造的空间很大，我们需要让状态复杂化来解决我们的问题。  

于是我们考虑将三种颜色分别设计维度来表示其最后出现的位置，这样就能对于每个 $i$ 剔除非法状态。但是这个状态就达到了 $O(n^4)$，明显是过大了。  
我们注意到肯定会有一个颜色最后出现的位置就在当前位置，于是我们可以将：  
$dp_{i,j,k,n},dp_{i,j,n,k},dp_{i,n,j,k},dp_{i,k,j,n},dp_{i,k,n,j},dp_{i,n,k,j}$ 这六种状态一并压进 $dp_{i,j,k}$。  
状态转移方程为：  
$$dp_{i,j,k}=dp_{i-1,j,k}$$  
$$dp_{i,j,i-1}=\sum_{k=0}^{k\leq j}dp_{i-1,k,j}+\sum_{k=j}^{k\leq i-2}dp_{i-1,j,k}$$  
最后我们将不符合要求的状态全部变为 0 即可。  
时间复杂度 $O(n^3)$。  
code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=301;
const int mod=1e9+7;
int n,m;int dp[N][N][N];
struct RULE{int l,x;};int ans;
vector <RULE> ru[N];int l,r,x;
void del(int i){
	for(int s=0;s<ru[i].size();s++){
		int l=ru[i][s].l;int x=ru[i][s].x;
		for(int j=0;j<=i;j++){
			for(int k=j;k<=i;k++){
				if(x==1){
					if(j>=l||k>=l)dp[i][j][k]=0;
				}else if(x==2){
					if((j>=l)+(k>=l)!=1)dp[i][j][k]=0;
				}else if(x==3){
					if((j>=l)+(k>=l)!=2)dp[i][j][k]=0;
				}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>l>>r>>x;
		ru[r].push_back((RULE){l,x});
	}
	dp[1][0][0]=3;del(1);
	for(int i=2;i<=n;i++){
		for(int j=0;j<=i;j++)
			for(int k=j;k<=i;k++)
				dp[i][j][k]=dp[i-1][j][k];
		for(int j=i-2;j>=0;j--){
			for(int k=0;k<=j;k++){
				dp[i][j][i-1]+=dp[i-1][k][j];
				dp[i][j][i-1]%=mod;
			}
			for(int k=j;k<=i-2;k++){
				dp[i][j][i-1]+=dp[i-1][j][k];
				dp[i][j][i-1]%=mod;
			}
		}
		del(i);
	}
	for(int i=0;i<=n;i++){
		for(int j=i;j<=n;j++){
			ans+=dp[n][i][j];
			ans%=mod;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：fade_away (赞：0)

# [ARC074C] RGB Sequence
[安利博客](https://blog.csdn.net/xmr_pursue_dreams/article/details/111825726)
## Solution
显然是一道$dp$，我们发现直接维护当前状态有多少种颜色不好维护，因为颜色只有$3$种，所以可以直接记录每一种颜色最晚在哪里出现，令$f_{i,j,k,l}$表示前$i$个里$R$最晚在$j$，$B$最晚在$k$，$G$最晚在$l$。

我们发现状态是$O(n^4)$的，但是显然有很多冗余状态，因为必然有一种颜色在$i$，所以其中一维不用记录，直接用$f_{i,j,k}$表示前$i$个中一种颜色在$i$，一种在$j$，一种在$k$，看情况转移即可。

对于限制$(l,r,x)$，只需要把不满足条件的$f_{r,j,k}$的值变为$0$即可。

时间复杂度$O(n^3+n^2m)$。
## Code

```cpp
vector<PR> V[MAXN];
int f[305][305][305];
int upd(int x,int y) { return x+y>=mods?x+y-mods:x+y; }
signed main()
{
	int n=read(),m=read();
	for (int i=1;i<=m;i++)
	{
		int l=read(),r=read(),x=read();
		V[r].PB(MP(l,x));
	}
	f[1][0][0]=3;
	for (int i=1;i<=n;i++)
		for (int j=0;j<i;j++)
			for (int k=0;k<i;k++) 
			{
				for (auto v:V[i]) 
					if ((i>=v.fi)+(j>=v.fi)+(k>=v.fi)!=v.se) f[i][j][k]=0;
				if (!f[i][j][k]) continue;
				f[i+1][j][k]=upd(f[i+1][j][k],f[i][j][k]);
				f[i+1][i][k]=upd(f[i+1][i][k],f[i][j][k]);
				f[i+1][j][i]=upd(f[i+1][j][i],f[i][j][k]);
			}
	int ans=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) ans=upd(ans,f[n][i][j]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：XenonKnight (赞：0)

> 题意：
> - 你要将 $n$ 个方格各染成红绿蓝三种颜色中的一种
> - 有 $m$ 条形如 $(l,r,x)$ 的限制，表示格子 $l$ ~ $r$ 之间恰好有 $x$ 种不同的颜色
> - 问有多少种不同的染色方法 $\bmod 10^9+7$。
> - $1 \leq n,m \leq 300$

~~震惊！某蒟蒻竟然独立切掉了一道国家集训队作业题！~~

设 $dp_{i,j,k}$ 为将当前红色最后出现的位置为 $i$，绿色最后出现的位置为 $j$，蓝色最后出现的位置为 $k$ 的方案数。

考虑到三种颜色是等价的，所以不妨假设 $i>j>k$，最后答案 $\times 6$。

转移：
- $j=i-1$，那么枚举红色上一次出现的位置 $l$，由 $dp_{j,l,k}$ 或 $dp_{j,k,l}$（对 $l$ 与 $k$ 的大小关系进行分类讨论） 更新 $dp_{i,j,k}$
- $j \neq i-1$，那么红色上一次出现的位置只能为 $i-1$，由 $dp_{i-1,j,k}$ 更新 $dp_{i,j,k}$

再考虑这 $m$ 条限制，对于每一条**右端点**为 $i$ 的限制 $(l,i,x)$：

- 若 $x=3$，那么 $j,k$ 都 $\geq l$
- 若 $x=2$，那么 $j,k$ 中恰有一个 $\geq l$
- 若 $x=1$，那么 $j,k$ 都 $<l$。

最后，还需要特判三种颜色全部相同的情况。

然后就是一大堆细节了。

```cpp
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
const int MOD=1e9+7;
int n=read(),m=read();
int l[305],r[305],x[305];
vector<int> tr[305];
int dp[305][305][305];
inline bool check(int i,int j,int k){
	bool flg=1;
	foreach(it,tr[i]){
		int ind=*it;
		int cnt=1;
		if(j>=l[ind])	cnt++;
		if(k>=l[ind])	cnt++;
		if(cnt!=x[ind])	flg=0;
	}
	return flg;
}
signed main(){
	fz(i,1,m)	l[i]=read(),r[i]=read(),x[i]=read(),tr[r[i]].push_back(i);
	if(check(1,0,0))	dp[1][0][0]=1;
	fz(i,2,n){
		fz(j,0,i-1){
			fz(k,0,j){
				if(j==k&&j)	continue;
				if(!check(i,j,k))	continue;
				dp[i][j][k]=dp[i-1][j][k];
				if(j==i-1||k==i-1){
					for(int l=0;l<i-1;l++){
						if(l<k)	dp[i][j][k]=(dp[i][j][k]+dp[j][k][l])%MOD;
						else	dp[i][j][k]=(dp[i][j][k]+dp[j][l][k])%MOD;
					}
				}
//				cout<<i<<" "<<j<<" "<<k<<" "<<dp[i][j][k]<<endl;
			}
		}
	}
	int ans=0;
	for(int i=0;i<n;i++)	for(int j=0;j<i;j++){
		ans=(ans+dp[n][i][j])%MOD;
	}
	ans=ans*6ll%MOD;
	ans=(ans+dp[n][0][0]*3)%MOD;
	cout<<ans<<endl;
	return 0;
}
```

---

