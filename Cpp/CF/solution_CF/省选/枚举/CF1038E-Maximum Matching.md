# Maximum Matching

## 题目描述

给定 $n$ 个方块，每个方块的格式为 $color_1\mid value \mid color_2$，方块也可以翻转得到 $color_2 \mid value \mid color_1$。

如果一个方块序列中相邻方块的接触端颜色相同，则称该序列为有效序列。例如，由三个方块 A、B 和 C 组成的序列是有效的，当且仅当 B 的左侧颜色与 A 的右侧颜色相同，且 B 的右侧颜色与 C 的左侧颜色相同。

序列的值定义为该序列中所有方块的值之和。

请从给定的方块子集中构造一个有效序列，并找到该序列的最大可能值。子集中的方块可以重新排序和翻转。每个方块在序列中最多只能使用一次。


## 说明/提示

第一个样例中，可以使用所有方块构造有效序列。

一种有效序列如下：

$4|2|1$，$1|32|2$，$2|8|3$，$3|16|3$，$3|4|4$，$4|1|2$

输入的第一个方块（$2|1|4$ $\to$ $4|1|2$）和第二个方块（$1|2|4$ $\to$ $4|2|1$）被翻转。

第二个样例中，最优解可由前三个方块构造（输入的第二个或第三个方块被翻转）：

$2|100000|1$，$1|100000|1$，$1|100000|2$

第三个样例中，无法构造包含两个或更多方块的有效序列，因此答案是仅包含第一个方块的序列（因为它是数值最大的方块）。

翻译由 DeepSeek V3+R1 完成

## 样例 #1

### 输入

```
6
2 1 4
1 2 4
3 4 4
2 8 3
3 16 3
1 32 2
```

### 输出

```
63```

## 样例 #2

### 输入

```
7
1 100000 1
1 100000 2
1 100000 2
4 50000 3
3 50000 4
4 50000 4
3 50000 3
```

### 输出

```
300000```

## 样例 #3

### 输入

```
4
1 1000 1
2 500 2
3 250 3
4 125 4
```

### 输出

```
1000```

# 题解

## 作者：BqtMtsZDnlpsT (赞：9)

校模拟赛，由于一些原因，造数据的 std 是逊的，我的同学也发了[帖](https://www.luogu.com.cn/discuss/416411)。

$\large\text{Solution}$

考虑直接建图，$color_1$ 向 $color_2$ 加边，边权为 $val$，这样会有 $4$ 个点，会有大量重边，自环。

首先，自环边可以直接当做点权，不要白不要。

然后，我们考虑在这张图上找到最长路径。

- 如果图不连通

那么图中的任意一个连通块大小一定小于 $4$，可以发现，如果一个连通块大小为 $1,2,3$ 那么度数为奇数的点的个数一定小于等于 $2$ 个（~~想一想为什么~~），那这个连通块一定是欧拉图，有一条欧拉路可以经过所有边，所得的最大值就是连通块内边权和。

- 联通

由于一条边增加的度数为 $2$，那么总度数一定是偶数，因此，$4$ 个点的度数只有可能是全偶，全奇，两偶两奇，其中全偶，两偶两奇构成的图是欧拉图，最大值也是边权和。

重点考虑全奇数。

考虑只要删去一条非自环边，使得图中两个点度数减 $1$，变为偶数，贪心的考虑是对的。这时候就要删除最短边。

但是会有一种情况，删掉边之后原先连通块一分为二。不难发现，一分为二后的连通块大小一定为 $1,3$（否则，你会获得两个包含一个奇点和一个偶点的连通块，显然不对）。而且，大小为 $1$ 的连通块只有一条非自环出边，即你准备删掉的那条边（不然他会直接连回大连通块）。

于是你可以暴力枚举删哪条边，然后判断是否会一分为二，再统计答案。

在一分为二时，减去的不只是边权，还要减去分离出去的连通块的边权（注意我们可能只选大小为 $1$ 的那个连通块（去掉大小为 $3$ 的连通块就是剩下那个点连出的所有自环边边权和））。

复杂度 $O(4n)=O(n)$

代码：

```cpp
inline bool search(vector<int>v,int x){//查找 v 中是否有 x 这个元素
	for(auto I:v)
		if(I==x)return 1;
	return 0;
}
int n,hd[5],cnt,d[5],s[5],ans,X[105],Y[105],SS[105];
struct E{
	int nxt,to;
}e[5005];
inline void add(int u,int v){
	e[++cnt]={hd[u],v};
	hd[u]=cnt;
}
int fa[5];
vector<int>V[5];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}//用并查集判连通块
signed main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	n=read();
	fa[1]=1;fa[2]=2;fa[3]=3;fa[4]=4;
	for(int i=1;i<=n;i++){
		int x=read(),S=read(),y=read();
		if(x==y)s[x]+=S;//自环
		else ++d[x],++d[y];
		int fx=find(x),fy=find(y);
		if(fx!=fy)fa[fx]=fy;
		X[i]=x,Y[i]=y;SS[i]=S;
	}
	for(int i=1;i<=4;i++)V[find(i)].push_back(i);
	for(int i=1;i<=4;i++){
		if(V[i].size()<4){//不是一个连通块
			int res=0;
			for(int j=1;j<=n;j++)
				if(search(V[i],X[j])&&search(V[i],Y[j]))res+=SS[j];
			ans=max(ans,res);
		}
		else{//是一个连通块
			int res=0;
			for(int j=1;j<=n;j++)
				if(search(V[i],X[j])&&search(V[i],Y[j]))res+=SS[j];
			int gg=INF;//gg是要删掉的边权和
			if(d[1]&d[2]&d[3]&d[4]&1){//四个奇点的特殊情况
				for(int j=1;j<=n;j++){//枚举删哪条边
					if(X[j]==Y[j])continue;
					if(d[X[j]]==1)gg=min({gg,SS[j]+s[X[j]],res-s[X[j]]});
					else if(d[Y[j]]==1)gg=min({gg,SS[j]+s[Y[j]],res-s[X[j]]});
					else gg=min(gg,SS[j]);
				}
				res-=gg;//删去
			}
			ans=max(ans,res);//统计答案
		}
	}
	write(ans);
}

```

---

## 作者：龙神哈迪斯 (赞：7)

### [题面](http://codeforces.com/contest/1038/problem/E)
题目大意:
给你$n$个色块，每个色块两端分别有一种颜色，并且每个色块都有一个权值。

你可以将一个色块翻转。如果两个色块接触的两端颜色相同，就可以称这两个色块为一个序列，一个序列可能由多个色块构成，序列的值为所构成的色块值的和，求所有情况下所有序列的最大值

### 放在前面的话
这题应该是有两种做法

第一种是将块看成两个点和一条边，跑欧拉路径，使其路径上边的值最大。这种方法比较明显，但是实现起来可能有点困难，需要分类讨论比较多的细节，还需要判桥之类的。博主一开始写的是这种方法，结果调的一发不可收拾，于是扔了，换第二种做法。

第二种是暴力$dp$，数据范围这么小，不是摆明让你用暴力去水的吗？虽然第二种方法复杂度明显劣于第一种，但是它好打呀！更何况在$Div2$这种手速场，其实更加推荐本做法，也是博主最终写的做法

### Sol
考虑最暴力的方式
$f[i][j][x][y]$表示用第$i$个到第$j$个之间的部分方块构成一个序列，序列左端颜色为$x$，右端颜色为$y$

然后就可以考虑$Floyed$式的转移

1.首先是使用中间的某些块
$$f[i][j][x][y]=max{f[i][k][x][p]+f[k+1][j][p][y]}$$
2.然后因为允许将块左右短点颜色反转
$$f[i][j][x][y]=max{f[i][k][p][y]+f[k+1][j][x][p]}$$
3.然后是不用中间的某些块
$$f[i][j][x][y]=max{f[i][k][x][y],f[k+1][j][x][y]}$$

复杂度是$O(n*n*4*4*n*4)$

然后我们就可以愉快的$AC$此题了~~虽然不是最优解~~

### Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int _=105;
inline int read()
{
	char ch='!';int z=1,num=0;
	while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
	if(ch=='-')z=-1,ch=getchar();
	while(ch<='9'&&ch>='0')num=(num<<3)+(num<<1)+ch-'0',ch=getchar();
	return z*num;
}
int n,f[_][_][5][5];
int main()
{
	n=read();
	memset(f,-63,sizeof(f));
	for(int i=1;i<=n;++i)
	{
		int a=read(),c=read(),b=read();
		f[i][i][a][b]=f[i][i][b][a]=c;
	}
	int ans=0;
	for(int i=n;i;--i)
		for(int j=i;j<=n;++j)
			for(int x=1;x<=4;++x)
				for(int y=1;y<=4;++y)
				{
					for(int k=i;k<=j+1;++k)
					{
						f[i][j][x][y]=max(f[i][j][x][y],max(f[i][k][x][y],f[k+1][j][x][y]));
						for(int p=1;p<=4;++p)
							f[i][j][x][y]=max(f[i][j][x][y],max(f[i][k][p][y]+f[k+1][j][x][p],f[i][k][x][p]+f[k+1][j][p][y]));
					}
					ans=max(ans,f[i][j][x][y]);
				}
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：nynkqh_yzp (赞：3)

首先如果我们把每种颜色当成点，每种色块当成边，那么一个序列相当于图上的一条简单路径。

如果一个部分的边可以全部在一条简单路径上，那么相当于度数为奇数的点数为 $0$ 或 $2$。由于每条边会使总度数加 $2$ 所以奇数点的数量一定为偶数。

所以不满足条件的情况一定是四个点都是奇点。

那么删掉一条边一定可以使得奇点个数最多为 $2$。

如果这个时候，我们考虑删掉其中权值最小的边。这个做法看起来是对的，但是删掉这条边可能会把原图分成两半，这样就求不出正确答案。

简单而正确的做法是枚举删掉某一条边或者不删边，求剩下的图中每个联通块是否满足要求，并取最大的满足条件的联通块的边权之和。

跑的很快，写的也短。
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,a[101],c[2][101],f[5],s[5],ss[5],so[5],ans;
int zbb(int x){//并查集
	if(f[x]==x)
		return f[x];
	f[x]=zbb(f[x]);
	return f[x];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&c[0][i],&a[i],&c[1][i]);
	c[0][0]=c[1][0]=1;
	a[0]=0;
	for(int j=0;j<=n;j++){
		for(int i=1;i<=4;i++)
			f[i]=i,s[i]=0,ss[i]=0,so[i]=0;
		for(int i=1;i<=n;i++)
			if(i!=j){
				if(zbb(c[0][i])!=zbb(c[1][i])){
					s[zbb(c[1][i])]+=s[zbb(c[0][i])];
					f[zbb(c[0][i])]=zbb(c[1][i]);
				}
				s[zbb(c[0][i])]+=a[i];
				ss[c[0][i]]^=1;
				ss[c[1][i]]^=1;
			}
		for(int i=1;i<=4;i++)
			so[zbb(i)]+=ss[i];
		for(int i=1;i<=4;i++)
			if(zbb(i)==i)
				if(so[i]!=4)
					ans=max(ans,s[i]);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

同时可在[我的 $\tt CSDN$ 博客](https://blog.csdn.net/qq_42101694/article/details/104171087)见到该题解。

# 题目
[传送门 to CF](http://codeforces.com/problemset/problem/1038/E)

[传送门 to luogu](https://www.luogu.com.cn/problem/CF1038E)

[传送门 to VJ](https://vjudge.net/contest/354931#problem/F)

# 思路
#### 图论模型
一个合法序列的最后一个方块，只由倒数第二个方块所限制。

这样的限制，往往可以建立图论模型。

注意到一个方块的本质是让结尾颜色变化一次。将一个方块两边的颜色 $\langle a,b\rangle$ 视作一条连接 $a,b$ 的双向边。则答案为原图中边不相交的最长路径。

#### 挑战 $\tt{NP-Hard}$
边不相交？这似乎是 __欧拉路径__ 的必要条件呢！

如果我把走过的边抽象出来，这一定是一条欧拉路径（小知识：其充要条件是奇点数量不超过二）。

于是，我们力求找到原图的边集的子集 $E'(E'\subseteq E)$ ，满足 $G'=(V,E')$ 存在欧拉路径。

这难吗？不难。如果 $\langle a,b\rangle$ 之间有两条边不属于 $E'$ ，则将这两条边加入，仍然存在欧拉路径（因为 $a,b$ 的度数的奇偶性都没有变化）。

那么，我们知道了这一点： $\langle a,b\rangle$ 之间最多只有一条边没有被经过（或者是全部都没有被经过）。

所以大力枚举吧！用 $2^{6}$ 来枚举，哪几种边是没有被全部经过的。之所以指数是六，是因为 ~~这是我算出来的~~ 删掉的边不会是自环，于是只有六种不同的边。

然后检测，并计算答案。战斗就结束了。有意思的是， $\mathcal O(n)$ 只来自于读入！

——言外之意：我允许 $n$ 达到 $10^6$ 级别。

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0' or c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c and c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
inline void writeint(int x){
	if(x > 9) writeint(x/10);
	putchar((x%10)^48);
}
# define MB template < class T >
MB void getMax(T &a,const T &b){ if(a < b) a = b; }
MB void getMin(T &a,const T &b){ if(b < a) a = b; }

const int MaxN = 105, infty = (1<<28)-1;
int sum[4][4], minV[4][4], cnt[4][4];

# define FOR(o) for(int o=0; o<4; ++o)

void input(){
	int n = readint();
	FOR(i) FOR(j) minV[i][j] = infty;
	for(int i=1,l,v,r; i<=n; ++i){
		l = readint()-1;
		v = readint(); // 颜色设置为[0,4)
		r = readint()-1;
		if(l > r) swap(l,r); // 小->大
		sum[l][r] += v, ++ cnt[l][r];
		getMin(minV[l][r],v);
	}
	FOR(i) for(int j=0; j<i; ++j){
		sum[i][j] = sum[j][i];
		minV[i][j] = minV[j][i];
		cnt[i][j] = cnt[j][i];
	} // 大->小
}

bool vis[4], deg[4]; int odd;
int dfs(int x){ // 返回答案的两倍（一条边会被加两次）
	if(vis[x] == true) return 0;
	vis[x] = true; int res = sum[x][x];
	FOR(i) if(x != i and cnt[x][i] > 0){
		res += sum[x][i]+dfs(i);
		if(cnt[x][i]%2 == 1)
			deg[x] = not deg[x];
	}
	if(deg[x]) ++ odd; return res+sum[x][x];
}

int HASH(int l,int r){
	return r+l-(l==0);
} // 请自行验证，顺序为(0,1)(0,2)(0,3)(1,2)(1,3)(2,3)
void solve(){
	int ans = 0;
	for(int S=(1<<6)-1; ~S; --S){
		bool ok = true;
		FOR(i) for(int j=i+1; j<4; ++j)
			if(cnt[i][j] == 0 and (S>>HASH(i,j)&1)){
				ok = false; break;
			} // 删掉了不存在的边 
		if(not ok) continue;
		FOR(i) vis[i] = deg[i] = false;

		FOR(i) for(int j=i+1; j<4; ++j)
			if((S>>HASH(i,j)&1) != 0){
				-- cnt[i][j], -- cnt[j][i];
				sum[i][j] -= minV[i][j];
				sum[j][i] -= minV[j][i];
			} // 对图进行删边操作

		FOR(i) if(not vis[i]){
			odd = 0; int d = dfs(i)>>1;
			if(odd < 3) getMax(ans,d);
		}
		
		FOR(i) for(int j=i+1; j<4; ++j)
			if((S>>HASH(i,j)&1) != 0){
				++ cnt[i][j], ++ cnt[j][i];
				sum[i][j] += minV[i][j];
				sum[j][i] += minV[j][i];
			}/* 将图还原 */
	}
	printf("%d\n",ans);
}

int main(){
	input(), solve();
	return 0;
}
```


---

## 作者：柳易辰 (赞：1)

## 暴力搜索！

容易想到建图，色块 $(c_1,w,c_2)$ 相当于连一条 $c_1\xrightarrow wc_2$ 的无向边，问题转化为：求一条**边权和最大的无向路径**。

观察到 $c_1,c_2$ 的范围是 $C\leqslant 4$，这说明原图上边（除去自环）只有 6 种（把连接同一组点的边是叫做一种）。贪心地，如果我们要走 $u\to v$，我们一定会选边权最大的 $u-v$。再考虑自环的贡献，设对于颜色 $c_i$，自环的贡献和是 $a_{c_i}$，路径点集为 $S$，则自环的总贡献是对于路径点集 $\sum_{p\in S}a_p$。

于是我们想到直接进行爆搜，要记录的信息是：当前所在点、每种边经过的数量、路径点集，根据柯西不等式，状态数量最大约是 $T=2^C(\frac {2n}{C(C-1)})^{\frac{C(C-1)}2}C$，代入 $n=100,C=4$，状态数量约为 $1368408064$ 个，还需要考虑 $T$ 转移的时间，我们可以用 **Dijkstra** 进行转移，时间复杂度 $O(CT\log T)$，显然无法通过。

考虑**剪枝**，对于一种边 $u-v$，它可能有很多条，对于一条路径，我们假设它经过了这种边 $k$ 次。如果 $k>2$，显然路径存在一部分是端点为 $u$ 或 $v$ 的回路，于是我们容易找到一条等价的路径，使得路径上 $u-v$  只有至多两条不在 $u-v$ 的二元环中。也就是说，如果某种边 $u-v$ 出现次数大于三，我们到达点 $u$ 后，连续走二元环 $u-v-u$，直至 $u-v$ 的边只剩两条。

于是我们容易把每种边的状态压缩到了 $3$，状态数量就变成了 $T=2^C3^{\frac{C(C-1)}{2}}C$，这是与 $n$ 无关的，当 $C=4$ 时，状态数量为 46656 个，可以轻松通过。

当然，这题完全可以开到 $n=10^5,C=5$，[Codeforces AC 记录](https://codeforces.com/contest/1038/submission/272693031)。

---

