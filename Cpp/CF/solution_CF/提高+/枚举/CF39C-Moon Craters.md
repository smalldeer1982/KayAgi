# Moon Craters

## 题目描述

There are lots of theories concerning the origin of moon craters. Most scientists stick to the meteorite theory, which says that the craters were formed as a result of celestial bodies colliding with the Moon. The other version is that the craters were parts of volcanoes.

An extraterrestrial intelligence research specialist professor Okulov (the namesake of the Okulov, the author of famous textbooks on programming) put forward an alternate hypothesis. Guess what kind of a hypothesis it was –– sure, the one including extraterrestrial mind involvement. Now the professor is looking for proofs of his hypothesis.

Professor has data from the moon robot that moves linearly in one direction along the Moon surface. The moon craters are circular in form with integer-valued radii. The moon robot records only the craters whose centers lay on his path and sends to the Earth the information on the distance from the centers of the craters to the initial point of its path and on the radii of the craters.

According to the theory of professor Okulov two craters made by an extraterrestrial intelligence for the aims yet unknown either are fully enclosed one in the other or do not intersect at all. Internal or external tangency is acceptable. However the experimental data from the moon robot do not confirm this theory! Nevertheless, professor Okulov is hopeful. He perfectly understands that to create any logical theory one has to ignore some data that are wrong due to faulty measuring (or skillful disguise by the extraterrestrial intelligence that will be sooner or later found by professor Okulov!) That’s why Okulov wants to choose among the available crater descriptions the largest set that would satisfy his theory.

## 样例 #1

### 输入

```
4
1 1
2 2
4 1
5 1
```

### 输出

```
3
1 2 4
```

# 题解

## 作者：封禁用户 (赞：7)

这篇文章也发布于[蒟蒻作者的 $\tt CSDN$ 博客](https://blog.csdn.net/qq_42101694/article/details/107639028)。~~尽管没有人去看。~~

~~话说这篇题解也没什么人看呀。~~

# 题目
[传送门 to luogu](https://www.luogu.com.cn/problem/CF39C)

# 思路
在很多年以前，有一道叫做[守卫](https://blog.csdn.net/qq_42101694/article/details/102761127)，是一道区间 $\tt dp$ 的题，而我惨痛爆零。它教给了我很重要的一课，$\tt dp$ 是需要发现相互独立的子问题的。

现在，我们回到这道题。假设我们选择了一个圆，将剩余的圆分成两组，使得其互不干扰，能做到吗？

答案是可以，因为一个圆的边界会自然地切开空间。也就是说，我们选择了一个圆，然后只有两种圆还可以选，一种在圆内（包含或者内切），一种在圆外（相离或外切），而这两种是 __互不干扰__ 的。

话说，我们可以先将圆转化为其直径，问题就变成了选择很多线段。~~但是后文我可能仍然称呼其为圆。~~

为了让圆内、圆外这两组的分布不那么离谱，我们将所有的圆按照左端点排序。我们每次只决策最靠左的一个圆，就会让剩余的圆的分布自然而美好。对于左端点相同的，我们自然是应该先决策右端点大的。然后剩下的圆就可以分成两部分，依据左端点是否小于当前圆的右端点。

但是，我们很悲伤的发现，我们没有完全摆脱选择的这个圆对别人的约束。我们得把它塞到状态里。我们可以写出一个 $f(i,j,x)$ 表示，第 $i$ 到第 $j$ 个圆可选，右端点不可以超过 $x$ 。这是 $\mathcal O(n^3)$ 的。怎么办？

突然发觉，$j$ 和 $x$ 有必然的联系。因为我们的 $j$ 是左端点小于 $x$ 的圆中，最右的一个。如果二者有必然联系，我们可不可以试着将二者用一个值来表示？

用 $f(i,j)$ 表示，从第 $i$ 个圆开始，考虑所有左端点不超过 $j$ 的圆，且不能选择包含 $j$ 的圆。这里的 $j$ 明显只有 $n$ 个取值了，就是每个圆的右端点。这样就完全可做了！

用 $R_i$ 表示，$\forall$ 圆，左端点不超过第 $i$ 个圆的右端点，最靠右的一个。若圆 $i$ 右端点为 $m_i$ ，那么

$$f(i,j)=\max[f(i+1,j),f(i+1,m_i)+f(R_i+1,j)+1]$$

左边表示不选，右边表示选。注意，这个圆本身也要满足不能包含 $j$ ，所以 $m_i\le j$ 。

$R_i$ 可以用 $\mathcal O(n\log n)$ 预处理，$j$ 和 $m_i$ 可以 $\mathcal O(n\log n)$ 压缩至 $[1,n]$ ，所以总复杂度是 $\mathcal O(n^2)$ 。

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0'||c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c&&c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
template < class T >
void getMax(T&a,T b){ if(a < b) a = b; }

const int MaxN = 2001;
// dp[i][j]:从第i个开始，直到左端点不小于R[j]
// R[j]:将所有右端点取出来排序
int dp[MaxN][MaxN], R[MaxN];

struct Range{
	int l, r, id;
	bool operator < (const Range &that) const {
		if(l != that.l)
			return l < that.l;
		return r > that.r;
	}
} node[MaxN];

// Rid:该区间右端点对应哪个R
int Rid[MaxN], nxt[MaxN], n;
void output(int i,int j){
	if(i == n) return ;
	if(dp[i][j] == dp[i+1][j])
		return output(i+1,j);
	printf("%d ",node[i].id+1);
	output(i+1,Rid[i]), output(nxt[i],j);
}

int main(){
	n = readint();
	for(int i=0; i<n; ++i){
		int o = readint(), x = readint();
		node[i].l = o-x, node[i].r = o+x;
		node[i].id = i, R[i] = node[i].r;
	}
	sort(node,node+n), sort(R,R+n);
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			if(node[i].r == R[j])
				Rid[i] = j;
	for(int i=0; i<n; ++i){
		nxt[i] = n;
		for(int j=0; j<n; ++j)
			if(node[i].r <= node[j].l){
				nxt[i] = j; break;
			}
	}
	for(int i=n-1; ~i; --i)
		for(int j=0; j<n; ++j){
			dp[i][j] = dp[i+1][j]; // 不选
			if(node[i].r <= R[j]) // 选
				getMax(dp[i][j],dp[i+1][Rid[i]]
					+dp[nxt[i]][j]+1);
		}
	printf("%d\n",dp[0][n-1]), output(0,n-1);
	return 0;
}
```


---

## 作者：Duramente (赞：4)

区间 $dp$ 的解法已经有很多了，提供一个不同的思路。   
计 $w_i$ 为第 $i$ 个圆内部（含自己）所能选的最多的个数。  
对于每个 $i$ ，用 $dp$ 来计算 $w_i$ 。  
设第 $i$ 个圆的左端点右端点分别为 $l_i$ ，$r_i$ 。  
计 $dp_r$ 为 $[l_i,r]$ 中能选最多的个数。  
转移时 $dp_r=max\{dp_{r-1},max\{dp_{l_j}+w_j\} \}$  
其中要满足 $r_j=r$。  
所以求 $w_i$ 时需要提前知道所有被包含在其中的 $j$ 的 $w_j$ 值。   
具体做法是把所有圆按照右端点为第一关键字升序，左端点为第二关键字降序排序，就能保证被包含在一个圆中的圆在它之前先被计算过了。   
会求 $w$ 之后就可以做了。多开一个包含整个坐标轴的圆，求它的 $w$ 值即可。

复杂度 $O(n^2)$ 。  


### Code
```cpp
#include<bits/stdc++.h>
#define forn(i,a,b)for(int i=(a),_b=(b);i<=_b;i++)
#define fore(i,b,a)for(int i=(b),_a=(a);i>=_a;i--)
#define rep(i,n)for(int i=0,_n=n;i<n;i++)
#define ll long long
#define pii pair<int,int>
#define m_p make_pair
#define pb push_back
#define fi first
#define se second
#define int ll
#define foreach(i,c) for(__typeof(c.begin())i=(c.begin());i!=(c).end();i++)
using namespace std;
const int N=4010;
int dp[N],w[N]; 
int pt[N][N];
int n;
struct seg{
	int l,r;
	int id;
}a[N];
bool cmp(seg x,seg y){
	if(x.r!=y.r)return x.r<y.r;
	return x.l>y.l;
}
vector<int>v;
int getid(int x){
	return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
} 
vector<int>v1[N];
vector<int>ans;
void findans(int id,int r){
	if(!id)return;
	if(r<a[id].l)return;
	if(id!=n+1&&a[id].r==r)ans.pb(a[id].id);
	if(pt[id][r]==-1){
		findans(id,r-1);return;
	}
	int pos=pt[id][r];
	findans(id,a[pos].l);findans(pos,r);
}
signed main(){
	cin>>n;
	forn(i,1,n){
		int x,y;cin>>x>>y;
		a[i].l=x-y;a[i].r=x+y;
		a[i].id=i;
		v.pb(a[i].l);v.pb(a[i].r);
	}
	sort(v.begin(),v.end());v.erase(unique(v.begin(),v.end()),v.end());
	sort(a+1,a+n+1,cmp);
	forn(i,1,n){
		a[i].l=getid(a[i].l);a[i].r=getid(a[i].r);
		v1[a[i].r].pb(i);
	}
	a[n+1].l=1;a[n+1].r=v.size(); 
	forn(i,1,n+1){
		memset(dp,0,sizeof(dp));
		dp[a[i].l]=0;
		forn(j,a[i].l+1,a[i].r){
			dp[j]=max(dp[j],dp[j-1]);
			pt[i][j]=-1;
			rep(k,v1[j].size()){
				int id=v1[j][k];
				if(a[id].l>=a[i].l){
					if(dp[a[id].l]+w[id]>dp[j]){
						dp[j]=dp[a[id].l]+w[id];
						pt[i][j]=id;
					}
				}
			}
		}
		w[i]=dp[a[i].r]+1;
	}
	cout<<w[n+1]-1<<"\n";
	findans(n+1,a[n+1].r);
	rep(i,ans.size())cout<<ans[i]<<" ";cout<<"\n";
	return 0;
}

---

## 作者：信息向阳花木 (赞：2)

讲一个不同的思路。

可以将每个圆转化为数轴上的开区间，这很容易想到。

接下来我们可以把所有端点离散化，然后 dp。（离散化应该不用说了，毕竟在座大佬都比我强 QwQ）

设 $f_{i,j}$ 表示在区间 $(i,j)$ 内能选的区间个数。很显然，如果本身存在 $(i,j)$ 区间，那一定能选。

$f_{i,j}$ 可以从 $f_{i + 1,j}$ 和 $f_{i, j -1}$ 直接转移。如果在 $(i,j)$ 内还有区间 $(i,t)$，$f_{i,j}$ 还可以从 $f_{i,t} + f_{t,j}$ 转移。

注意：在 dp 时，为了保证在算 $f_{i,j}$ 时 $f_{i+1,j}$ 和 $f_{i,j-1}$ 已经算过，我们要将 $i$ 倒着枚举，$j$ 则正着枚举。

答案的输出可以用递归来实现。

虽然 dp 很简单，但是离散化和输出答案还是有很多细节需要注意。具体看代码。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define PII pair<int, int> 

inline void in(int &x)
{
	x = 0; bool f = 0; char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	x = f ? -x : x;
}

inline void out(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x / 10) out(x / 10);
	putchar((x % 10) | 48);
}

int n, cnt;
PII a[4010];
vector<PII> b[4010];
vector<int> ans; 
int alls[4010], f[4010][4010];

void g(int i, int j) //递归答案
{
	int s = 0;
	if(f[i][j] == 0) return;
	for (int k = 0; k < b[i].size(); k ++ )
	{
		int t = b[i][k].second;
		if(t == j)
		{
			ans.push_back(b[i][k].first);
			s = 1; 
		}
	}
	for (int k = 0; k < b[i].size(); k ++ )
	{
		int t = b[i][k].second;
		if(t < j && f[i][t] + f[t][j] + s == f[i][j])
		{
			g(i, t);
			g(t, j);
			return;
		}
	}
	if(f[i + 1][j] + s == f[i][j]) { g(i + 1, j); return; }
	if(f[i][j - 1] + s == f[i][j]) { g(i, j - 1); return; }
}

int main()
{
	in(n);
	for (int i = 1; i <= n; i ++ )
	{
		int x, c;
		in(x); in(c);
		a[i] = {x - c, x + c};
		alls[++ cnt] = x - c;
		alls[++ cnt] = x + c;
	}
	
	sort(alls + 1, alls + cnt + 1);
	int tot = unique(alls + 1, alls + cnt + 1) - alls - 1; 
	cnt = tot;
	
	for (int i = 1; i <= n; i ++ )
	{
		int x = lower_bound(alls + 1, alls + cnt + 1, a[i].first) - alls;
		int y = lower_bound(alls + 1, alls + cnt + 1, a[i].second) - alls;
		b[x].push_back({i, y});
	} //以上是输入和离散化
	
	for (int i = cnt; i >= 1; i -- )
		for (int j = i + 1; j <= cnt; j ++ )
		{
			int s = 0;
			f[i][j] = max(f[i + 1][j], f[i][j - 1]);
			for (int k = 0; k < b[i].size(); k ++ )
			{
				int t = b[i][k].second;
				if(t == j) s = 1;
				if(t < j) f[i][j] = max(f[i][j], f[i][t] + f[t][j]); 
			}
			f[i][j] += s;
		}
	
	g(1, cnt);
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i ++ ) printf("%d ", ans[i]);
	
	return 0;
}
```

---

## 作者：Mihari (赞：1)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF39C)

# 题解

~~研究了俩小时，终于是看懂了题解~~

首先简化题目：可以将这些在同一直线上的圆看做是在直线上的一些区间，现在我们要求最多能选多少区间使得这些区间不相交，并输出任意一种最多的选择情况。

然后，我们可以构想一下最后的状态是什么样子：选了一些很大的不相交的区间，在这些区间中又分别选一些不相交的次大的区间，一直迭代直到小的区间中没有更小的区间可选

那么，对于某一区间 $[l,r]$ 我们可以**假定**有某一 $[l,i]$ 和 $[i,r]$ 的区间（不一定存在）将其分成两个部分，在这俩部分中我们进行递归在 $[l,i]$ 和 $[i,r]$ 中寻找，显然这个 $i\in [l,r]$，如果我们直接枚举，那么这个算法的复杂度显然为 $\mathcal O(n^3)$

考虑对其进行优化，注意到算法瓶颈在于区间 $[l,i]$ 和 $[i,r]$ 都是我们假定存在的，所以我们需要寻找 $[l,r]$ 中的所有 $i$ 以避免不漏掉小区间，但是我们是否可以直接钦定某一边是存在，另一边是虚构的呢？显然可行，储存以 $l$ 为左边界的所有区间中, 他们的右边界有哪些，只需要在这些右边界中对区间 $[l,r]$ 进行划分即可，这样优化之后，算法整体的复杂度**均摊来算**，是 $\mathcal O(n^2)$ 的

在区间处理完之后，我们需要考虑是否存在 $[l,r]$ 这样的区间，将整个区间框起来（这是合法的），如果存在加上即可

因为题目还要求我们输出方案，所以我们可以用另一个数组记录一下某一个区间的分界线，在输出方案时亦可递归寻找

对于算法的一个优化，因为区间 $[l,r]$ 的最优性是独立的，所以我们可以用 $f$ 记录一下某一区间的最优解，再次访问时可直接返回

为了方便处理，其实我们可以将这些区间的左右端点进行离散化，这里不作过多说明

对于方法，我也不知道该说是 $DP$ 还是记忆化搜索了...

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13389763.html
```

---

## 作者：荣一鸣 (赞：1)

![OI WARNING](https://cdn.luogu.com.cn/upload/pic/23143.png)

~~题目也很好理解~~，可以化简一下，就是在这样的一条轴上，求最多有多少个圆能两两互不相交。

提供一个想法，就是贪心（虽然我错了，但如果你能打对记得@我，找到错误（小数据或者数学论证）），每次贪掉交点数最多的圆，使剩下的圆最多。（好像没毛病？？？）

[错误代码链接(这样省文章空间)](https://www.luogu.org/blog/xrr/cf39c-cuo-wu-dai-ma)

正确的思路如下：我们先将每个圆用左边界与右边界来表示，然后将这些点离散化，这样就可以dp了。

### 1.离散化

离散化过程如下

```
for(int i=0;i<n;i++){ 			
	scanf("%d%d",&c,&r);
    x[i]=c-r;
    y[i]=c+r;
    d[i]=x[i];
    d[n+i]=y[i];//把每一个数值放进来
}
sort(d,d+n+n);//从小到大排序
t=unique(d,d+n+n)-d;//去重,unique咋用如下
for(int i=0;i<n;i++){
	x[i]=upper_bound(d,d+t,x[i])-d;//找到相应的位置，用下标来表示离散化后的数值
    y[i]=upper_bound(d,d+t,y[i])-d;
	b[x[i]].push_back(i);//在下面dp时有用
    g[x[i]][y[i]]=i+1;//存以x[i]为左边界,y[i]为由辩解的圆的编号（因为有特判，所以存最后一个就行了）
}
```

[unique用法](http://www.cplusplus.com/reference/algorithm/unique/)

简单说一下，unique将相邻的重复的元素放到最后，后面的提上来（不一定要有序），返回去重后的尾地址。

### 2.区间dp

然后我们用区间dp加递归记忆化。首先f[i][j]表示以i为左边界，j为右边界的时候最多选多少圆。

很显然，f [ i ][ j ]=max( f [ i ][ j ], f [ i ][ k ] + f [ k ][ j ] + ( g [ i ][ j ] > 0 ? 1:0))

但其实，k不需要从i一直枚举到j，我们只需要枚举以i为左边界的圆的右边界（不超过j）作为k就行了。

```
int dp(int l,int r){
	if(l>r)return 0;
	if(f[l][r]) return f[l][r];
	f[l][r]=dp(l+1,r);
	for(int i=0;i<b[l].size();i++){//枚举边界
		int k=b[l][i];
		if(y[k]<r&&dp(l,y[k])+dp(y[k],r)>f[l][r]){
			f[l][r]=f[l][y[k]]+f[y[k]][r];
			s[l][r]=y[k];//存分割的圆用的右边界，说出编号时要用
		}
	}
	f[l][r]+=!!g[l][r];//可以改成f[l][r]+=(g[l][r]>0 ? 1:0)
	return f[l][r];
}
```
### 3.深搜找圆

既然有了怎么分成小区间，就可以通过s [ i ][ j ]来dfs

代码如下

```
void dfs(int l,int r){
	if(l>r) return;
	if(s[l][r]) dfs(l,s[l][r]),dfs(s[l][r],r);
	else dfs(l+1,r);
	if(g[l][r]) printf("%d ",g[l][r]);
}
```
不需解释吧！！！

总代码找这里[正确代码](https://www.luogu.org/blog/xrr/cf39c-zheng-que-dai-ma)

---

