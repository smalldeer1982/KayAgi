# Minimax Problem

## 题目描述

You are given $ n $ arrays $ a_1 $ , $ a_2 $ , ..., $ a_n $ ; each array consists of exactly $ m $ integers. We denote the $ y $ -th element of the $ x $ -th array as $ a_{x, y} $ .

You have to choose two arrays $ a_i $ and $ a_j $ ( $ 1 \le i, j \le n $ , it is possible that $ i = j $ ). After that, you will obtain a new array $ b $ consisting of $ m $ integers, such that for every $ k \in [1, m] $ $ b_k = \max(a_{i, k}, a_{j, k}) $ .

Your goal is to choose $ i $ and $ j $ so that the value of $ \min \limits_{k = 1}^{m} b_k $ is maximum possible.

## 样例 #1

### 输入

```
6 5
5 0 3 1 2
1 8 9 1 3
1 2 3 4 5
9 1 0 3 7
2 3 0 6 3
6 4 1 7 0```

### 输出

```
1 5```

# 题解

## 作者：CXY07 (赞：16)

# 少判了一种情况，被 $Hack$ 掉了，心情复杂

## 题目链接：[CF1288D 【Minimax Problem】](https://www.luogu.com.cn/problem/CF1288D)

题意比较奇怪，要你求一个什么东西的最大值的最小值的最大值来着，建议先把题目仔细看几遍再往下看。

首先观察数据范围，发现 $m$ 特别小，最大只有 $8$ 来者，考虑在 $m$ 上搞点事情。

考虑 **二分答案** ~~套路~~

首先二分一个数字 $ans$ ，表示当前的答案。

然后把原本矩阵中大于等于 $ans$ 的位置设为 $1$ ，小于 $ans$ 的位置设为 $0$。

```
比如样例：

6 5
5 0 3 1 2
1 8 9 1 3
1 2 3 4 5
9 1 0 3 7
2 3 0 6 3
6 4 1 7 0

当 ans = 5 时，可以得到矩阵

1 0 0 0 0
0 1 1 0 0
0 0 0 0 1
1 0 0 0 1
0 0 0 1 0
1 0 0 1 0

```

又根据 $m$ 的范围，不难发现我们可以把每一行都压成二进制的形式。

这样就变成了 $n$ 个数字。

回到二分答案，我们现在的 $ans$ 是二分出来的，要怎么 $check$ 才行？

我们发现，只要当两个数字 **或起来** 正好等于 $2^m - 1$ 也就是二进制下的 $111...$ 就说明可行。

为什么？

在做或运算的时候，只要两个数字对应位置上有一个 $1$，当前位置就是 $1$。
这正好满足我们取 $max$ 的操作，如果两个都是 $1$ 呢？其实我们也不需要在意这两个 $1$ 原来数字的相对关系，因为他们显然都大于等于 $ans$。

那么现在问题就变成了：

给定 $n$ 个数字 $a_i$，判断是否存在 $i$，$j$ （可以相等）满足：$a_i$ $or$ $a_j== 2^m - 1$

发现我们可以把所有数都丢到一个桶里面，每次枚举到一个数，找一下这个数字哪些位置上为 $0$，那么你需要找的数字在这一位上一定是 $1$，其他位置上 $0$，$1$ 随意。

$DFS$ 即可。

注意一个小小的优化，如果一个数字的二进制为 $111...$，那么说明根本不需要找另一个数字，直接选两次自己即可。

**还要注意一种情况**

如果最后你根本没有选出答案，那么说明答案只能为 $0$，则任意选择两个行即可。~~就是这里送掉了我的 D ！！！~~

代码也还比较好写。


```cpp
//Code By CXY
#include<bits/stdc++.h>
using namespace std;
     
#define min _______min
#define max _______max
     
const int MAXN = 3e5 + 10;
const int INF = 1e9;
     
int n,m,ans1,ans2;
int a[MAXN][10],p[MAXN][10],c[MAXN],rev[MAXN]; 
int l = INF,r = -1,mid;
int buk[510];
     
inline int min(int x,int y) {return (x < y) ? x : y;}
inline int max(int x,int y) {return (x > y) ? x : y;}
     
bool find(int x,int p) {
  	bool res = false;
   	if(p < 0) {
   		if(buk[x]) ans2 = buk[x];//保存答案
   		return buk[x];
   	}
   	if(x & (1 << p)) return find(x,p - 1);
   	res |= find(x,p - 1);
   	res |= find(x + (1 << p),p - 1);
   	return res;
} //DFS 判断
     
inline bool chk() {
   	memset(buk,0,sizeof buk);
   	for(register int i = 1;i <= n; ++i) {
   		int now = 0;
   		for(register int j = 1;j <= m; ++j) {
   			now <<= 1;
   			if(a[i][j] >= mid) now++;
   		}//now就是这一行代表的数字
   		buk[now] = i;
   		c[i] = now;
   		if(c[i] == (1 << m) - 1) {ans1 = ans2 = i; return true;}//特殊小优化的情况
   		rev[i] = ((1 << m) - 1) ^ c[i];//必须为1的位置组成的数
   	}
   	for(register int i = 1;i <= n; ++i) 
   		if(find(rev[i],7)) {
   			ans1 = i;//保存答案
   			return true;
   		}
   	return false;
}
     
int main () {
  	scanf("%d%d",&n,&m);
   	for(register int i = 1;i <= n; ++i)
   		for(register int j = 1;j <= m; ++j) {
   			scanf("%d",&a[i][j]);
   			l = min(l,a[i][j]);
   			r = max(r,a[i][j]);
   		}
   	while(l < r) {
   		mid = (l + r + 1) >> 1;
   		if(chk()) l = mid;
   		else r = mid - 1;
   	}//二分
	if(ans1 == 0 && ans2 == 0) printf("1 1 \n");//！！！注意这个小情况
	else printf("%d %d",min(ans1,ans2),max(ans1,ans2));
   	return 0;
}
```

我的 $D$ 啊啊啊本来是上分好场的来着呜呜呜

初三的 $OIer$ ，请多关照

---

## 作者：zac2010 (赞：8)

看到题目中有很多 $\min,\max$，一眼二分答案。

考虑一个常见的套路：假设我们二分的值是 $mid$，那么我们在判断合法性时把数字矩阵变成 $01$ 矩阵：假若 $a_{i,j}\geq mid$，则赋值为 $1$；否则为 $0$。

用了这个套路后，我们可以把一行中最小值是否 $\geq mid$ 这个判断给替换成：$b_i$ 是否每个都为 $1$。所以现在要求解的是：找到两行使得或起来每个位置都为 $1$。由于 $m\leq 8$，直接把一行给压成一个状态。

接下来有一种暴力的思路：直接对于每一行的状态都枚举补集的超集，看看是否存在。但是行数太多，外面还要套个二分答案，太慢了。考虑 $01$ 状态最多只有 $2^m$ 个，而 $2^m$ 最多只有 $256$ 个，也就是说，现在的状态序列中存在大量的重复。所以现在就只要对于合法的状态去枚举它补集的超集就行了。

当 $m$ 较大的时候可以用[高维前缀和](https://www.luogu.com.cn/blog/zac2010/gao-wei-qian-zhui-he)优化枚举超集的过程。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 3e5 + 10, M = 1 << 8;
int n, m, U, a[N][10], s[N], id[M];
pair<int, int> p = make_pair(1, 1);
int check(int x){
	fill(id, id + U + 1, 0);
	FL(i, 1, n){
		s[i] = 0;
		FL(j, 1, m) s[i] |= (a[i][j] >= x) << j - 1;
		id[s[i]] = i;
	}
	FL(i, 0, U) if(id[i]){
		int t = U ^ i;
		FL(j, i, U) if(id[j] && (j & t) == t){
			p = make_pair(id[i], id[j]); return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d%d", &n, &m), U = (1 << m) - 1;
	FL(i, 1, n) FL(j, 1, m) scanf("%d", &a[i][j]);
	int l = 0, r = 1e9, ans;
	while(l <= r){
		int mid = l + r >> 1;
		if(check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	printf("%d %d\n", p.first, p.second);
	return 0;
}
```


---

## 作者：KingPowers (赞：5)

## CF1288D Minimax Problem

[题目链接](https://www.luogu.com.cn/problem/CF1288D)

首先大家应该都看得出来要去二分这个最大的最小值。

观察一下数据中有没有什么不正常的地方：$m\le8$，立马想到状压。于是我们可以将原矩阵中大于等于 $mid$ 的全都变为 $1$，小于 $mid$ 的设为 $0$，然后把每一行全都状压了。那么此时，如果存在两行操作后满足条件，它们的状态按位或起来之后一定为 $2^m-1$。

同样还是因为 $m$ 实在太小了，$2^m$ 最大只有 $256$，因此我们可以开一个桶记录下每个状态在哪一行（随便记一个就行），然后暴力枚举两个状态，如果这两个状态或起来为 $2^m-1$ 并且都出现过那就满足条件。

具体实现见代码。

```cpp
int n,m,a[N][10],t[1<<9];
bool check(int mid){
	memset(t,0,sizeof(t));
	for(int i=1;i<=n;i++){
		int res=0;
		for(int j=1;j<=m;j++) res=res*2+(a[i][j]>=mid);
		t[res]=i;
	}
	if(t[(1<<m)-1]) return 1;
	for(int i=0;i<=(1<<m)-1;i++)
		for(int j=0;j<=(1<<m)-1;j++)
			if(t[i]&&t[j]&&(i|j)==(1<<m)-1) return 1;
	return 0;
}
void get_ans(int ans){
	memset(t,0,sizeof(t));
	for(int i=1;i<=n;i++){
		int res=0;
		for(int j=1;j<=m;j++) res=res*2+(a[i][j]>=ans);
		t[res]=i;
	}
	if(t[(1<<m)-1]) return printf("%lld %lld",t[(1<<m)-1],t[(1<<m)-1]),void();
	for(int i=0;i<=(1<<m)-1;i++)
		for(int j=0;j<=(1<<m)-1;j++)
			if(t[i]&&t[j]&&(i|j)==(1<<m)-1) return printf("%lld %lld",t[i],t[j]),void();
}
void Main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) a[i][j]=read();
	int l=1,r=1e9,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	get_ans(ans);
}
```

---

## 作者：YLWang (赞：5)



众所周知二分的目的是让求解性问题转变为判定性问题使得题目变得更加简单

然而有些时候你转化完成以后你却不知道怎么办

这里给出几条常用方法

第一条就是贪心或者dp检验

第二种就是把所有大于/小于mid的数变成0/1，方便统计和操作

这种题就是一个典型的二分转化01的应用

二分一手答案mid，把所有大于等于mid的数都设成1，反之设成0. 这样只需要求出两个或起来全是1的数。因为$m$小到令人发指，所以直接暴力把所有存在的都跑出来就行了。非常好写。

注意一下二分上界。

```cpp
const int MAXN = 300005, MAXM = 10;
int a[MAXN][MAXM], n, m, b[MAXN], exi[2005];
pair < int, int > check(int mid) {
	mst(b, 0); mst(exi, 0);
	For(i, 1, n)
		For(j, 1, m) 
			b[i] = b[i] * 2 + (a[i][j] >= mid);
	For(i, 1, n) exi[b[i]] = 1;
	vector < int > tmp; tmp.clear();
	For(i, 0, (1 << m)) if(exi[i]) tmp.pb(i);
	for(auto u : tmp) {
		for(auto v : tmp) {
			if((u | v) == ((1 << m) - 1)) {
				pair < int, int > ans;
				For(i, 1, n) {
					if(b[i] == u) ans.first = i;
					if(b[i] == v) ans.second = i;
				}
				return ans;
			}
		}
	}
	return mkp(-1, -1);
}
signed main()
{
	cin >> n >> m;
	For(i, 1, n) For(j, 1, m)
		a[i][j] = read();
	int l = 0, r = 1000000000, ai = 1, aj = 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		pair < int, int > tmp = check(mid);
		if(tmp.first != -1) ai = tmp.first, aj = tmp.second, l = mid+1;
		else r = mid-1;
	}
	cout << ai << ' ' << aj << endl;
    return 0;
}




```

---

## 作者：IceKylin (赞：4)

# CF1288D Minimax Problem 题解
### [原题链接（in luogu）](https://www.luogu.com.cn/problem/CF1288D)
### [原题链接（in CodeForces）](https://codeforces.com/problemset/problem/1288/D)
### [更好的阅读体验？](https://www.luogu.com.cn/blog/std-IK/cf1288d-ti-xie)

这是一道 **二分答案** 题目，关于如何才能 **“一眼”** 看出来，可以参考笔者另一篇文章的开头部分（[link](https://www.luogu.com.cn/blog/std-IK/cf1370d-ti-xie)）。

观察数据范围，惊喜地发现 ${1\le m\le 8}$。这就意味着这道题目大概率可以 **状压**。

考虑 **判定**。有一个很常用的技巧，对于给定的 ${k}$，原矩阵可以转化为一个 ${01}$ 矩阵，具体如下：

设原矩阵为 ${\{a_{ij}\}}$，$01$ 矩阵为 ${\{b_{ij}\}}$，

那么有 ${b_{ij}=\left\{\begin{matrix}1\quad(a_{ij}\ge k)\\0\quad(a_{ij}<k)\end{matrix}\right.}$

然后可以将矩阵 ${b}$ 的第二维状压，那么对于 ${i}$ 行与 ${j}$ 行，当且仅当 **按位或** 后的值为 ${(2^m -1)}$ 时，判定通过。

但直接判定的时间复杂度为 ${O(n^2)}$，会超时，考虑优化。可以发现最多只有 ${2^m\le 256}$ 种不同状态，所以可以通过桶实现 **去重**。

判定的最后，还需要寻找答案在原矩阵中的下标（参见代码）。加上这一步的时间，判定的时间复杂度即为 ${O(2^{2m}+n)}$。

此题总时间复杂度为 ${O((2^{2m}+n)\log R)}$，其中 ${R}$ 表示二分的值域，此题可以取 ${10^9}$，也可以取 ${\max\{a_{ij}\}-\min\{a_{ij}\}}$。

P.S. 按位或的优先级是很低的，参与运算时需要加括号。代码参考了题解区大佬的 pair 写法，可以让代码更加清晰美观。

## AC代码
```cpp
//By IceKylin
#include<bits/stdc++.h>
#define maxn 300050
#define pii pair<int,int>
#define ft first
#define sd second
#define mp make_pair
using namespace std;
int n,m;
int a[maxn][10],b[maxn],c[270],t[270];


pii check(int x){
	for(int i=1;i<=n;++i)b[i]=c[i]=0;
	for(int i=0;i<(1<<m);++i)t[i]=0;
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
		b[i]=b[i]*2+(a[i][j]>=x);
	for(int i=1;i<=n;++i)t[b[i]]=1;
	int cnt=0;
	for(int i=0;i<(1<<m);++i)
		if(t[i])c[++cnt]=i;
	for(int i=1;i<=cnt;++i)
	for(int j=1;j<=i;++j){
		if((c[i]|c[j])==(1<<m)-1){
			pii ans;
			for(int k=1;k<=n;++k){
				if(c[i]==b[k])ans.ft=k;
				if(c[j]==b[k])ans.sd=k;
			}
			return ans;
		}
	}
	return mp(-1,0);
}


pii binary_search(int l,int r){
	pii ans=mp(1,1);
	while(l<=r){
		int mid=(l+r)/2;
		pii tmp=check(mid);
		if(tmp.ft!=-1){
			ans.ft=tmp.ft;
			ans.sd=tmp.sd;
			l=mid+1;
		}
		else r=mid-1;
	}
	return ans;
}


int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
		cin>>a[i][j];
	pii ans=binary_search(0,(int)1e9);
	cout<<ans.ft<<' '<<ans.sd;
	return 0;
}
```


---

## 作者：Nt_Tsumiki (赞：3)

提供一个爆标的做法。

常规的做法是二分答案然后对于每个 $i$ 用 01 串去表示状态，看是否存在并集为全集的状态对。

这样的话复杂度带个 $\log$ 非常不美观，我们考虑给他优化掉。

对于这种问题我们有一个比较经典的做法是把更新答案这一步的复杂度给他摊掉。

我们考虑维护一个 $id_{sta}$ 表示有哪些状态包含这个状态 $sta$，不难发现由于我们只在意 $sta$ 是否被包含，所以我们只用记录任意一个数即可。

那么这样的话每个 $id_{sta}$ 只会最多更新一次，又因为一个状态 $sta$ 被标记了，那么它所有的子集都会被标记，我们从大到小枚举去暴力更新状态，遇到被标记的就跳，就可以把复杂度摊掉了。

因为还有转移和排序的复杂度，所以复杂度是 $O(nm\log nm+m2^m)$ 的。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#define N 300005

inline int R() {
    int x=0; bool f=0; char c=getchar();
    while (!isdigit(c)) f|=(c=='-'),c=getchar();
    while (isdigit(c)) x=x*10+c-'0',c=getchar();
    return f?-x:x;
}

template<typename T>
void W(T x,int op=0) {
    if (x<0) return putchar('-'),W(-x,op);
    if (x>9) W(x/10); putchar(x%10+'0');
    if (op) putchar(op==1?' ':'\n');
}

using namespace std;
int n,m,cnt,a[N][8],vis[1<<8],sta[N];
struct Tmp { int x,y; } p[8*N];

void dfs(int sta,int id) {
    vis[sta]=id;
    for (int i=sta;i&-i;i-=(i&-i))
        if (!vis[sta-(i&-i)]) dfs(sta-(i&-i),id);
}

int main() {
    n=R(),m=R();
    for (int i=1;i<=n;i++)
        for (int j=0;j<m;j++)
            a[i][j]=R(),p[++cnt]={i,j};
    sort(p+1,p+cnt+1,[](Tmp tmp1,Tmp tmp2) {
        return a[tmp1.x][tmp1.y]>a[tmp2.x][tmp2.y];
    });
    vis[0]=1;
    for (int i=1;i<=cnt;i++) {
        auto [x,y]=p[i]; sta[x]|=(1<<y);
        if (vis[((1<<m)-1)^sta[x]]) {
            W(x,1),W(vis[((1<<m)-1)^sta[x]],2);
            return 0;
        }
        if (!vis[sta[x]]) dfs(sta[x],x);
    }
    return 0;
}
```

---

## 作者：been_apart (赞：1)

这题比较明显要二分了。（求最小的最大）

那么如何得知可以满足二分的答案呢？（就是$check$函数）

可以把每个数组每一位能否满足二分答案标记为$1$或$0$（$O(nm)$）,然后只需找出两个数组，能让$n$个位置都至少有一个数组是$1$。能找到说明符合。

那么怎么找那两个数组呢？

针对$m$出奇地小，就可以用二进制来解决。而如上的要求两个数组每个位置至少有一个数组为$1$恰与 $|$ 异曲同工。

所以给每个数组编一个二进制（就是由上面提到的标记转换而成），并用桶记录。先枚举数组，然后再枚举二进制，用 $|$ 来判断是否可以满足要求，用桶判断此二进制是否存在数组。

而之所以直接枚举二进制，不离散化的原因很简单：$n$的范围比$(1<<m)$还大。

时间效率：$O(n(1<<m)logk)$,$k$是最大数减最小数。


代码很简单，就是稍微难想到用二进制。需要自行体会。

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
#include<bitset>
#include<vector>
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int n,m,a[300005][10],mn=1e9,mx=0,ans1,ans2,xx,yy,f[300005];
int d[260];
inline bool ok(int x){
	int p=0;memset(d,0,sizeof(d));
	for(re i=1;i<=m;i++)p+=1<<(i-1);
	for(re i=1;i<=n;i++){f[i]=0;
		for(re j=1;j<=m;j++){
			if(a[i][j]>=x){
				f[i]+=1<<(j-1);
			}
		}
		d[f[i]]=i;
	}
	for(re i=1;i<=n;i++){
		for(re j=0;j<(1<<m);j++){
			if(d[j]&&(f[i]|j)==p){
				xx=i;yy=d[j];return 1;
			}
		}
	}
	return 0;
}
signed main(){
   	n=read();m=read();
   	for(re i=1;i<=n;i++){
   		for(re j=1;j<=m;j++){
   			a[i][j]=read();mn=min(mn,a[i][j]);mx=max(mx,a[i][j]);
   		}
   	}
   	int l=mn,r=mx,mid;
   	while(l<=r){
   		mid=(l+r)>>1;
   		if(ok(mid)){
   			l=mid+1;ans1=xx;ans2=yy;
   		}
   		else {
   			r=mid-1;
   		}
   	}
   	cout<<ans1<<" "<<ans2<<endl;
   	return 0;
}
```

---

## 作者：syksykCCC (赞：1)

看到要求 **最小值的最大值**，显然要想到 **二分**。

观察到 $m \le 8$，是不是可以 **二进制压位** 呢？答案是肯定的。

比如我们在判断答案为 $mid$ 是否可行时，我们对每一行定义一个二进制数 $b_i$，这个其实是一个 `bitset`，但因为位数太少直接 `int` 就能实现，当 $a_{i,j} \ge mid$ 时，$b_i$ 的左数第 $j$ 位就是 $1$，否则为 $0$。例如，$mid = 3$，$a_i = \{ 3, 4, 1, 2 \}$，那么 $b_i = 1100_{(2)}$。这时，我们将 $t_{b_{i}}  \gets i$，表示此状态的来源。

考虑枚举两个状态 $i, j$，如果 $i, j$ 状态都存在（可以通过先将 $t$ 初始化为 $0$，看 $t_i, t_j$ 是不是 $> 0$ 来实现），然后如果 $i \operatorname{or} j = 11\dots 11$，那么这两个状态就可以满足我们的需求了（因为这说明每个位置都能找到至少一个 $\ge mid$ 的数字），将所选的两行数定为 $t_i$ 和 $t_j$ 即可。

代码如下，仅供参考：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5, M = 10;
int n, m, a[N][M], b[N], t[1 << M], x, y;
inline bool check(int mid)
{
	memset(b, 0, sizeof b);
	memset(t, 0, sizeof t);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
			b[i] = (b[i] << 1) | (a[i][j] >= mid);
		t[b[i]] = i;
	}
	for(int i = 1; i < (1 << m); i++)
		for(int j = 1; j < (1 << m); j++)
			if((i | j) == (1 << m) - 1 && t[i] && t[j])
			{
				x = t[i]; y = t[j];
				return true;
			}
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> a[i][j];
	int lb = -1, rb = 1e9;
	while(lb < rb)
	{
		int mid = lb + rb + 1 >> 1;
		if(check(mid)) lb = mid;
		else rb = mid - 1;
	}
	cout << x << ' ' << y << endl;
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

20 篇题解都能写题解属实是开了。

然后我们思考这道题咋做。

考虑到 $n$ 过大，$m$ 过小，所以肯定复杂度内是有一些关于 $m$ 的很大的项的。

首先让最大值最小，想到二分，我们可以将问题转化一下：将 $x \ge mid$ 的位置设为 $1$，$x < mid$ 的位置设为 $0$，把每一行看成一个二进制数，相当于说就是让你找到是否有两个二进制数的或 $m$ 位全为 $1$。

然后这个问题显然是好做的，我们把 $2^8$ 个数丢进桶里依次判断一下就好了。

时间复杂度 $O(2^mn\log V)$，这复杂度属实是开了，但是竟然能过。

## code

code：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 3e5 + 5;

int n, m;
int a[N][10], p[N], tong[N];

bool Check ( int mid ) {
  memset ( tong, 0, sizeof ( tong ) );
  for ( int i = 1; i <= n; i ++ ) {
    p[i] = 0;
    for ( int j = 0; j < m; j ++ ) {
      if ( a[i][j] >= mid ) {
        p[i] |= ( 1 << j );
      }
    }
    tong[p[i]] ++;
  }
  for ( int i = 1; i <= n; i ++ ) {
    for ( int j = 0; j < ( 1 << m ); j ++ ) {
      if ( ( p[i] | j ) == ( 1 << m ) - 1 && tong[j] ) {
        return true;
      }
    }
  }
  return false;
}

pii help ( int mid ) {
  memset ( tong, 0, sizeof ( tong ) );
  for ( int i = 1; i <= n; i ++ ) {
    p[i] = 0;
    for ( int j = 0; j < m; j ++ ) {
      if ( a[i][j] >= mid ) {
        p[i] |= ( 1 << j );
      }
    }
    tong[p[i]] = i;
  }
  for ( int i = 1; i <= n; i ++ ) {
    for ( int j = 0; j < ( 1 << m ); j ++ ) {
      if ( ( p[i] | j ) == ( 1 << m ) - 1 && tong[j] ) {
        return { i, tong[j] };
      }
    }
  }
  return { 114514, 1919810 };
}

void Solve () {
  cin >> n >> m;
  for ( int i = 1; i <= n; i ++ ) {
    for ( int j = 0; j < m; j ++ ) {
      cin >> a[i][j];
    }
  }
  int l = -1, r = 1e9 + 1;
  while ( l + 1 < r ) {
    int mid = l + r >> 1;
    if ( Check ( mid ) ) {
      l = mid;
    }
    else {
      r = mid;
    }
  }
  pii ans = help ( l );
  cout << ans.first << " " << ans.second;
}

signed main () {
#ifdef judge
	freopen ( "Code.in", "r", stdin );
	freopen ( "Code.out", "w", stdout );
	freopen ( "Code.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

二分答案之后，每个数按照大于等于还是小于 $mid$ 赋值为 $0/1$，现在只用解决只有 $0,1$ 的问题。

我们发现，取 $\max$ 运算在只有 $0,1$ 时可以视作或，所以就是要找出两行按位或之后为全 $1$。

枚举一行，另一行的限制为某个位置只能是 $1$ 或者没有限制，这是一个高维后缀和，预处理下即可做到 $O((n + 2^m) \log V)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxv = (1<<8);
const int maxn = 3e5+114;
int a[maxn][8];
int b[maxn][8];
int n,m;
int dp[maxv];
int ansx,ansy;
bool check(int x){
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++) b[i][j]=(a[i][j]>=x);
    for(int i=0;i<(1<<m);i++) dp[i]=0;
    for(int i=1;i<=n;i++){
        int x=0;
        for(int j=0;j<m;j++) x+=(1<<j)*b[i][j];
        dp[x]=max(dp[x],i);
    }
    for(int i=0;i<m;i++){
        for(int j=(1<<m)-1;j>=0;j--){
            if(!((1<<i)&j)) dp[j]=max(dp[j],dp[j+(1<<i)]);
        }
    }
    for(int i=1;i<=n;i++){
        int x=0;
        for(int j=0;j<m;j++) x+=(1<<j)*(b[i][j]^1);
        if(dp[x]!=0){
            ansx=i,ansy=dp[x];
            return true;
        }
    }
    return false;
}   
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++) cin>>a[i][j];
    int l=0,r=1e9+114;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(check(mid)==true) l=mid;
        else r=mid; 
    }
    check(l);
    cout<<ansx<<' '<<ansy<<'\n';
    return 0;
}
```

---

## 作者：incra (赞：0)

### Sol
不是，为啥其他题解写的这么神秘。

要算最大值最小，显然二分，考虑要 `check(x)`，那么把大于等于 $x$ 的数都变为 $1$，否则变为 $0$，那么我们只需要选两行 $i,j$，使得这两行的每一列至少有一个位置是 $1$，考虑到 $m\le 8$，直接暴力做。

时间复杂度 $2^{2m}\log V$。

### Code
```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#include <chrono>
#include <random>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define puts(s) cout << s << endl
#define endl '\n'
const int N = 300010,M = 10;
int n,m;
int a[N][M];
int st[N];
int ans1 = 1,ans2 = 1;
bool check (int x) {
	map <int,int> mp;
//	cout << "state = " << x << ": \n";
	for (int i = 1;i <= n;i++) {
		st[i] = 0;
		for (int j = 1;j <= m;j++) st[i] |= (a[i][j] >= x) << j - 1;
		mp[st[i]] = i;
//		cout << st[i] << ' ';
	}
//	cout << endl;
	int all = (1 << m) - 1;
	for (int i = 0;i < 1 << m;i++) {
		for (int j = 0;j < 1 << m;j++) {
			if ((i | j) == all && mp[i] && mp[j]) return ans1 = mp[i],ans2 = mp[j],true;
		}
	}
	return false;
}
int main () {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) for (int j = 1;j <= m;j++) cin >> a[i][j];
	int l = 0,r = 1e9;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check (mid)) l = mid;
		else r = mid - 1;
	}
	check (l);
	cout << ans1 << ' ' << ans2 << endl;
	return 0;
}
```

---

## 作者：__ikun__horro__ (赞：0)

## Solution

题目要求 $b_j$ 最小值的最大值，像这种求最小值的最大值或最大值的最小值的问题，很显然可以用二分答案。

接下来考虑二分答案怎么写 check，注意到数据范围 $m \le 8$，对于这种很小的数据范围，可以使用状态压缩来解决。

以样例为例：

```
6 5
5 0 3 1 2
1 8 9 1 3
1 2 3 4 5
9 1 0 3 7
2 3 0 6 3
6 4 1 7 0

(mid = 3)
```

我们可以把大于等于 $mid$ 的的值标为 $1$，否则标为 $0$：

```
6 5
1 0 1 0 0
0 1 1 0 1
0 0 1 1 1
1 0 0 1 1
0 1 0 1 1
1 1 0 1 0
```

随后进行状态压缩（为了方便观察，用二进制表示）：

```
6
10100 01101 00111 10011 01011 11010
```

如果 $a_{x,j}$ 和 $a_{y,j}$ 中至少有一个 $\ge mid$，那么 $b_j$ 就 $\ge mid$。不难发现，$b$ 通过以上操作状压后的结果，就是 $a_x$ 状压的结果按位或 $a_y$ 状压后的结果。

我们 check 的是 $b$ 中的最小值是否 $\ge mid$，也就是说 $b$ 中所有元素都要 $\ge mid$，那么 $b$ 状压后的结果每一位必须都是 $1$。

这时，check 函数就变成了求 $a$ 中的两个数，使它们按位或之后的结果每一位都是 $1$。我们可以枚举第一个数，通过 dfs 枚举每一位，根据按位或的性质，如果一位是 $0$，那么第二个数的这一位一定是 $1$，如果一位是 $0$，那么第二个数的这一位可能是 $0$ 或 $1$。

我们纪录每一个数在 $a$ 中的位置，就可以判断了。

## Code

```cpp
#include <iostream>
#include <cstring>
#define int long long

#define ikun 114514

using namespace std;

const int N = 3e5 + 5;

int n, m, a[N][10], b[N], c[300], ans = -1, ans1, ans2;

int dfs(int u, int now, int ex) {
	if (u > m) {
		return c[now];
	}
	if (((ex >> (u - 1)) & 1) == 1) {
		int t1 = dfs(u + 1, now | (1 << (u - 1)), ex);
		int t2 = dfs(u + 1, now, ex);
		if (t1) return t1;
		return t2;
	}
	return dfs(u + 1, now | (1 << (u - 1)), ex);
}

bool check(int d) {
	if (d == 0) {
		if (ans < d) {
			ans = d;
			ans1 = 1, ans2 = 1;
		}
		return 1;
	}
	memset(c, 0, sizeof c);
	for (int i = 1; i <= n; i++) {
		b[i] = 0;
		for (int j = 1; j <= m; j++) {
			if (a[i][j] >= d) b[i] |= (1 << (j - 1));
		}
		c[b[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		int tmp = dfs(1, 0, b[i]);
		if (tmp) {
			if (ans < d) {
				ans = d;
				ans1 = i, ans2 = tmp;
				return 1;
			}
		}
	}
	return 0;
}

void sol() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	int l = 0, r = 1e9, mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	cout << ans << "\n";
	cout << ans1 << " " << ans2 << "\n";
}

signed main() {
#ifdef ikun
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T;
	T = 1;
	while (T--) sol();
	return 0;
}
```

---

## 作者：chenzhaoxu2027 (赞：0)

# 题目大意（搬的）

给出一个 $n$ 行 $m$ 列的数字矩阵 $a$，找出两行 $x,y$，令 $b_j=\max(a_{x,j},a_{y,j})$，试使得 $\min_{1 \le j \le m} b_j$ 最大，输出选择的 $x,y$，可以相同。

# 分析

看了题目，是一类**最小值最大**的题目，考虑**二分**。

问题变成判断是否有 $x,y$ 使得 $\min_{1 \le j \le m} b_j \ge mid$。

由于 $m \le 8$，所以想到**二进制**，定义新矩阵 $c_{i,j}=[a_{i,j} \ge mid]$，此时新矩阵属于零一矩阵，将新矩阵每一行浓缩成一个十进制数字得到数列 $d$，问题就又转化成了：

判断是否有 $x,y$ 使得 $d_x \mid d_y = 2^m$。

这个问题就可以用桶秒掉了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300005][10];
int b[300005];
int n,m;
int t[300];
int tl,tr;
bool check(int x){
//	cout<<"check "<<x<<"\n";
	for(int i=0;i<(1<<m);i++){
		t[i]=0;
	}
	for(int i=1;i<=n;i++){
		int res=0;
		for(int j=1;j<=m;j++){
			res*=2; 
			res+=(a[i][j]>=x);
//			cout<<"b["<<i<<"]["<<j<<"]="<<(a[i][j]>=x)<<" ";
		}
//		cout<<"res="<<res<<"\n";
		t[res]=i;
	}
	for(int i=0;i<(1<<m);i++){
		for(int j=0;j<(1<<m);j++){
			if((i|j)==((1<<m)-1)&&t[i]&&t[j]){
				tl=t[i];
				tr=t[j];
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	int l=0,r=1e9,ansl=-1,ansr=-1;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)){
			ansl=tl;
			ansr=tr;
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	cout<<ansl<<" "<<ansr;
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

最小值最大，考虑二分。在值域维度二分，对于每一个 mid，可以将每个数组大于等于 mid 的数赋值为一，其余为零。考虑两个数组合法当且仅当两个 01 数组按位或起来所有位数均为一。注意到 $m \le 8$，暴力枚举即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,m;
int a[300005][10];
struct node{
	int val;
	int x,y;
	bool operator<(const node &a)const{return val<a.val;}
}li[3000005];
int top;
int t[10000];
int b[15];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			li[++top]={a[i][j],i,j};
		}
	}
	sort(li+1,li+1+top);
	int L=0,R=top;
	int ans=0;
	int l=0,r=0;
	while(L<=R){
		memset(t,0,sizeof t);
		int mid=L+R>>1;
		int V=li[mid].val;
		int bj=0;
		for(int i=1;i<=n;i++){
			int sum=0,cnt=0;
			for(int j=1;j<=m;j++){
				if(a[i][j]>=V)sum|=(1<<(j-1)),b[++cnt]=(1<<(j-1));
			}
			if(sum==(1<<m)-1){
				l=i,r=i;
				bj=1;
				break;
			}
			for(int j=0;j<(1<<cnt);j++){
				int now=((1<<m)-1)^sum;
				for(int k=1;k<=cnt;k++)now+=((j>>(k-1))&1)*b[k];
				if(t[now]){
					bj=1,l=t[now],r=i;
					break;
				}
			}
			if(bj)break;
			t[sum]=i;
		}
		if(bj)ans=mid,L=mid+1;
		else R=mid-1;
	}
	cout<<l<<' '<<r<<'\n';
}
```

---

## 作者：rainygame (赞：0)

在这里给出一个 $O((nm+2^m) \log V)$（$V$ 为值域）的做法。

首先看到最小值最大，二分答案。考虑判断答案是否 $\ge x$。

考虑一个简单的转化：设 $S_i=\{1\le j\le m\wedge a_{i,j} \ge x \mid j\}$，那么命题变为是否存在 $1\le x,y \le n$，使得 $S_x \cup S_y=[1,m]\cap\mathbb{Z}$。对于 $S_i$ 在代码中的表示，可以状压。 

考虑一个简单的做法，我们可以将所有 $S_i$ 的子集放到桶里，等到查询 $j$ 的时候直接查询 $\complement_{[1,m]\cap\mathbb{Z}}S_j$ 即可查询到，但是分析可得时间复杂度为 $O(n2^m)$。

容易想到，对于一个被查询到的子集，如果它是多个 $S_i$ 的子集，那么除第一个 $S_i$ 以外，其它的都是冗余的。所以枚举子集时，如果它出现过了，直接退出即可。时间复杂度降到了 $O(nm+2^m)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 300001

int n, m, tx, ty;
int v[MAXN]; 
int a[MAXN][8];
int b[1<<8];

bool check(int x){
	for (int i(1); i<=n; ++i){
		v[i] = 0;
		for (int j(0); j<m; ++j) if (a[i][j] >= x) v[i] |= 1<<j;
	}
	memset(b, 0, sizeof(b));
	for (int i(1); i<=n; ++i){
		if (v[i] == (1<<m)-1){
			tx = ty = i;
			return true;
		}else if (b[((1<<m)-1)^v[i]]){
			tx = i;
			ty = b[((1<<m)-1)^v[i]];
			return true;
		}
		
		for (int j(v[i]); j; j=(j-1)&v[i]){
			if (b[j]) break;
			b[j] = i;
		}
	}
	return false;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	for (int i(1); i<=n; ++i){
		for (int j(0); j<m; cin >> a[i][j++]);
	}
//	cout << '\n';
//	cout << check(1) << '\n';
	
	int l(0), r(1e9), mid;
	while (l < r){
		mid = (l+r+1) >> 1;
		if (check(mid)) l = mid;
		else r = mid-1;
	}
	if (check(l)) cout << tx << ' ' << ty;
	
	return 0;
}

```

---

## 作者：Vitamin_B (赞：0)

# 思路
遇到最小值的最大，首先想到二分答案。check 怎么写呢？因为 $m\le8$，所以我们可以状态压缩，在这里 $t_{i,j}$ 表示 $t_i$ 二进制的第 $j$ 位。如果 $a_{i,j}\ge mid$ 则 $t_{i,j}=1$，否则 $t_{i,j}=0$。然后只要判断是否有 $t_i$ 按位或上 $t_j$ 是否等于 $2^m-1$ 就行，如果有就把答案更新成 $i,j$。但是 $n^2$ 枚举 $i,j$ 肯定不行，这是因为 $t$ 中有巨量重复元素。于是，我们可以把 $vis_i$ 表示第一个 $t_j=i$ 的下标 $j$，然后两重循环枚举 $0\sim2^m-1$，这下时间复杂度只有 $(2^m)^2$ 了，不会超时。总时间复杂度 $\log(\max a_{i,j},\min a_{i,j})\max(nm,2^{2m})$，时间够了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, m, a[300005][10], t, x, l = 1e9, r, mid, best1 = 1, best2 = 1, vis[270];
bool check () {
	for (int i = 0; i <= t; ++ i)
		vis[i] = 0;
	for (int i = 1; i <= n; ++ i) {
		x = 0;
		for (int j = 0; j < m; ++ j)
			if (a[i][j] >= mid)
				x |= 1 << j;
		if (! vis[x])
			vis[x] = i;
	}
	for (int i = t; ~i; -- i)
		if (vis[i])
			for (int j = t; ~j; -- j)
				if (vis[j] && (i | j) == t) {
					best1 = vis[i], best2 = vis[j];
					return 1;
				}
	return 0;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	t = (1 << m) - 1;
	for (int i = 1; i <= n; ++ i)
		for (int j = 0; j < m; ++ j)
			cin >> a[i][j], r = max (a[i][j], r), l = min (a[i][j], l);
	while (l <= r) {
		mid = l + r >> 1;
		if (check ())
			l = mid + 1;
		else
			r = mid - 1;
	}
	cout << best1 << ' ' << best2;
	return 0;
}
```

---

## 作者：Light_Pursuer (赞：0)

# [Minimax Problem - 洛谷](https://www.luogu.com.cn/problem/CF1288D) 1900

## Solution

二分答案。

看到 $n$ 属于比较大的，$m$ 算是较小的，思考如何从 $m$ 入手。

不难发现，是可以将 $m$ 位二进制化成至多 `256` 个十进制数的，即：`00000000`，`00000001` …… `11111111`。

有了这点，就好想二分答案了。

二分出来一个 $mid$，思考将每一行化成一个 $m$ 位的二进制编码，那就当 $mid\leq a_{i,j}$ 时，将二进制数组 $h_{i,j}$ 标记为 `1`，否则标记为 `0`。

例如：

当原来数组为：

`5 0 3 1 2`

`1 8 9 1 3`

`1 2 3 4 5`

`9 1 0 3 7`

`2 3 0 6 3`

`6 4 1 7 0`

$mid$ 为 `3` 时，$h$ 数组为：

`1 0 1 0 0`

`0 1 1 0 1`

`0 0 1 1 1`

`1 0 0 1 1`

`1 1 0 1 0`

`1 1 0 1 0`

这时候将这 $n$ 个二进制编码化成十进制为 $p$ 数组，分别为：`20 13 7 19 11 26`。

只需要找到两个数或起来等于 $(11111)_2$ 即可。枚举其中一个数 $p_i$，再暴力枚举 `1` 到 `31`，代表二进制的所有可能，接着一一查找是否存在一个数，使得 $vis_{j}=true$ 并且 $(j|p_{i})=2^{m+1}-1$。如果能找到，说明方案可行，标记答案，继续二分。否则方案不可行，这时 $mid$ 需要变小。

code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10,P=1<<8+5;
int read()
{
	int ret=0,f=1;char c=getchar();
	while(!(c>='0'&&c<='9'))
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*f;
}
int n,m,a[N][10],ans,h[N][10],p[N],r1,r2; 
int vis[P],ans1,ans2;
bool check(int mid)
{
	int maxx=0;
	for(int i=1;i<=m;i++)
	{
		maxx=(maxx<<1)+1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=1<<m;j++)
		{
			if(vis[j]&&(j|p[i])==maxx)
			{
//				cout<<mid<<' '<<maxx<<' '<<i<<' '<<p[i]<<' '<<j<<endl;
				ans1=p[i],ans2=j;
				return true;
			}
		}
	}
	return false;
}
void solve()
{
	n=read(),m=read();
	int l=0,r=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
			r=max(r,a[i][j]);
		}
	}
	while(l<=r)
	{
		int mid=(l+r)>>1;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++) h[i][j]=0;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]>=mid) h[i][j]=1;
				else h[i][j]=0; 
			}
		}
		for(int i=1;i<=n;i++)
		{
			p[i]=0; 
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				p[i]=p[i]*2+h[i][j];
			}
//			cout<<p[i]<<endl;
		}
		for(int i=1;i<=n;i++)
		{
			vis[p[i]]=true;
		}
		if(check(mid))
		{
//			cout<<mid<<endl;
			for(int i=1;i<=n;i++)
			{
				if(p[i]==ans1)
				{
					r1=i;
				}
				if(p[i]==ans2)
				{
					r2=i;
				}
			}
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	if(ans==0)
	{
		cout<<1<<' '<<1;
		return;
	}
	cout<<r1<<' '<<r2<<endl;
}
signed main()
{
	solve();
	return 0;
}
```

---

## 作者：Limit (赞：0)

# 题目大意

给出一个 $n\times m$ 的矩阵，其中第 $i$ 行第 $j$ 列的元素的值为 $a_{i,j}$，现在需要求出选出两行 $i,j$ 后 $\min\limits_{k=1}^m\max\{a_{i,k},a_{j,k}\}$ 的最大值。

# 分析

~~看到这种最小值最大一眼二分~~

看了一圈题解都是二分，这里给出一种不是二分的做法~~供学不会二分的同学借鉴~~。

设 $c_k$ 为 $a_{i,k},a_{j,k}$ 中的任意一值，可以知道序列 $c$ 至多存在 $2^m$ 种情况。

可以观察到 $\min\limits_{k=1}^m\max\{a_{i,k},a_{j,k}\}\geq \min\limits_{k=1}^m c_k$，那么问题转化为选出两行，对于每个位置可以在两行中任选一个，使得选出的数的最小值最大。如果 $i$ 是最后被选中的两行中的一行，那么可以知道 $a_i$ 这行中有若干元素被选中，于是可以考虑将每一种取数的情况统计下来，用一个桶表示某一种取数情况对于每一行选出的数的最小值的最大值，最后只需要枚举每一种选数情况和这种选数集合的补集对应情况取较小值的最大值即可。

时间复杂度 $\mathcal{O}(n m 2^m)$，看似比较大，但是可以过。

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,f,l) for(int i(f);i<=l;++i)
#define DOW(i,f,l) for(int i(f);i>=l;--i)
using namespace std;
const int INF=2e9;
int n,m;
int v[1000];
int f[1000];//用一个二进制数表示选择数的集合
int id[1000];
int a,b;
int answer=0;
int main()
{
    scanf("%d%d",&n,&m);
    int t=(1<<m)-1;
    REP(i,1,n)
    {
        REP(j,1,m)
        {
            scanf("%d",&v[j]);
        }
        REP(j,0,t)//枚举选择哪些数
        {
            int mi=INF;
            REP(k,0,m-1)
            {
                if(j&(1<<k))
                {
                    mi=min(v[k+1],mi);//计算选择的数中的最小值
                }
            }
            if(f[j]<=mi)//如果比原来这种选数情况要大则更新
            {
                id[j]=i;
                f[j]=mi;
            }
        }
    }
    REP(i,0,t)
    {
        if(min(f[i],f[t^i])>=answer)//枚举每一种选数情况和它的补集合并与答案比较
        {
            a=id[i];
            b=id[t^i];
            answer=min(f[i],f[t^i]);
        }
    }
    printf("%d %d\n",a,b);
    return 0;
}
```

---

## 作者：Ginger_he (赞：0)

最小值最大，显然是二分答案。

将 $a$ 中 $\ge mid$ 的数设为 $1$，$<mid$ 的数设为 $0$。观察到列数很少，因此我们可以将每行压成一个二进制数 $b_i$，接下来只要找到 $1\le i,j\le n$ 使得 $b_i\operatorname{or} b_j=2^m-1$，对于每个数都枚举 $0\sim2^m-1$ 看看是否符合即可，时间复杂度 $O(n2^m\log V)$。

有点卡，但能过。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 300005
int n,m,l,r,x,y,a[N][8],b[N],p[N];
bool check(int t)
{
	for(int i=0;i<(1<<m);i++)
		p[i]=0;
	for(int i=1;i<=n;i++)
	{
		b[i]=0;
		for(int j=0;j<m;j++)
			b[i]+=(a[i][j]>=t)<<j;
		p[b[i]]=i;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(1<<m);j++)
		{
			if(p[j]&&(b[i]|j)==(1<<m)-1)
			{
				x=i,y=p[j];
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)
			scanf("%d",&a[i][j]);
	}
	l=0,r=1e9,x=y=1;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d %d\n",x,y);
	return 0;
}
```

---

## 作者：Engulf (赞：0)

题目要求最小值最大，所以我们可以二分 $b_j$。

又注意到题目中的 $m \le 8$，所以我们不妨往状压上想想。

对于每一行，我们把 $ \ge b_j$ 的值的那一位置为 $1$，$ < b_j$ 的值的那一位置为 $0$，那么对于每一行 $i$ 都被我们表示成了一个 $8$ 位二进制数 $\mathrm{st}_i$。

如果我们能找到两行 $x$ 和 $y$，且 $\mathrm{st}_x \operatorname{or} \mathrm{st}_y = 2^m - 1$（即每位都是 $1$），证明这个 $b_j$ 可行。

显然不能暴力枚举 $x$ 和 $y$，注意到不同的状态数其实只有 $2^m$ 个，最多也才 $256$ 个状态，所以我们可以去个重，枚举所有出现的状态，更新答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;

const int N = 3e5 + 5, M = 10;
int n, m, a[N][M];

int st[N];

int ansl, ansr;

bool check(int bj)
{
	memset(st, 0, sizeof st);
	bitset<256> vis;
	unordered_map<int, int> mp;
	for (int i = 1; i <= n; i ++ )
	{
		for (int j = 1; j <= m; j ++ )
			if (a[i][j] >= bj) st[i] += (1 << j - 1);
		mp[st[i]] = i;
		vis[st[i]] = 1;
	}
	vector<int> states;
	for (int i = 0; i < 1 << m; i ++ ) if (vis[i]) states.push_back(i);
	for (int i = 0; i < states.size(); i ++ )
		for (int j = 0; j < states.size(); j ++ )
			if ((states[i] | states[j]) == (1 << m) - 1)
			{
				ansl = mp[states[i]], ansr = mp[states[j]];
				return true;
			}
	return false;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ )
			scanf("%d", &a[i][j]);
	int l = 0, r = 1e9, res;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid - 1;
	}
	printf("%d %d\n", ansl, ansr);
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1288D)
## 思路
看到 $m \le 8$，一眼状压。

看到最大值，一眼二分答案。

我们考虑先二分一个答案 $x$，然后由于 $m$ 非常小，所以我们可以把它的状态压进一个数组里面，若 $a_{i,j} \ge x$，则 $pos_i$ 的这一位为 $1$，否则为 $0$，答案就是找到两个 $i,j$，使得 $pos_i\ \operatorname{or} \ pos_j$ 等于 $2^m-1$，直接暴力 $\verb!DFS!$ 即可，但是我的 $\verb!DFS!$ 超时了，最后改成循环卡着时限过掉了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=3e5+10;
int const M=8+1;
int a[N][M],pos[N],statu[1<<M],n,m,ans1=1,ans2=1,chkx,chky;
inline bool check(int x){
	memset(statu,0,sizeof(statu));
	for (int i=1;i<=n;++i){
		pos[i]=0;
		for (int j=1;j<=m;++j)
			pos[i]|=((1<<(j-1))*(a[i][j]>=x));
		statu[pos[i]]=i;
	}
	for (int i=1;i<=n;++i)
		for (int j=0;j<(1<<m);++j)
			if (statu[j] && (pos[i]|j)==(1<<m)-1)
				return chkx=i,chky=statu[j],1;
	return 0;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i)
    	for (int j=1;j<=m;++j)
    		cin>>a[i][j];
    int l=0,r=1e9;
    while (l<r){
    	if (l+1==r){
    		if (check(r)) l=r,ans1=chkx,ans2=chky;
    		break;
    	}
    	int mid=(l+r)>>1;
    	if (check(mid)) l=mid,ans1=chkx,ans2=chky;
    	else r=mid-1;
    }
    cout<<ans1<<' '<<ans2<<'\n';
    return 0;
}
```


---

## 作者：xlqs23 (赞：0)

**题目大意：**

给出一个$n*m$的矩阵，我们用$maze[n][m]$来表示每一个元素，现在我们需要选出其中 $i $和 $j $两行,$i $和 $j $可以相同，用这两行的元素构成一个新的数组a，构造规则为$a[k]=max(maze[i][k],maze[j][k])$，现在我们要使数组a中的最小值最大，请问该如何选择 $i $和 $j $才能满足条件

**题目分析：**

读完题目后感觉乱糟糟的，但静下心来分析一下，要求最小值的最大值，显然的二分，所以我们很直接的确定下来要对于数组a的最小值进行二分了，但$check$函数该怎么写是我们接下来需要考虑的问题了，其实当我们确定下来了最小值之后，就相当于对原矩阵构成了一种约束条件，换句话说，原矩阵中值小于当前限制的元素，我们是无法选择的了，不然最后构成的数组a中的最小值就无法保证为当前二分的答案了，有了这样一个转换后，我们就可以将原矩阵中大于当前二分的答案的位置都置为1，其余位置为0，这样就很自然的进行了状态压缩，因为每一行的元素都是绑定的，也就是对于某一行来说，我们只能选择或者不选，这样又是一种标准的枚举子集，我们再看一眼数据范围，发现m最大只有7，我们如果以枚举子集的形式来确定$i$和$j$的话，时间复杂度最大也只有2^14，所以我们可以直接两层$for$循环枚举子集状态，找到一种 $i$和 $j$ 的情况，满足其能覆盖整个子集就好了，具体实现看代码吧，代码写的比较清楚了

**代码：**
```cpp
#include<iostream>
#include<cstdio> 
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
 
typedef long long LL;
const int inf=0x3f3f3f3f;
const int N=3e5+100;
int a[N][8],vis[N],ans1,ans2,n,m;
 
bool check(int x)
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
	{
		int val=0;
		for(int j=1;j<=m;j++)
			if(a[i][j]>=x)
				val|=1<<(j-1);//状态压缩
		vis[val]=i;//标记状态
	}
	for(int i=0;i<(1<<m);i++)//枚举i的状态
		if(vis[i])
			for(int j=0;j<(1<<m);j++)//枚举j的状态
				if(vis[j])
					if((i|j)==(1<<m)-1)
					{
						ans1=vis[i];
						ans2=vis[j];
						return true;
					}
	return false;
}
 
int main()
{
//	freopen("input.txt","r",stdin);
//	ios::sync_with_stdio(false);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	int l=0,r=inf;
	while(l<=r)//二分最小值
	{
		int mid=l+r>>1;
		if(check(mid))
			l=mid+1;
		else
			r=mid-1;
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}

---

## 作者：Sai0511 (赞：0)

上分好场。   
题目大意：  
给出$\text{n}$个长度为$\text{m}$的数组$a_i(i \in[1,n])$，选$\text{2}$个数组
$a_i,a_j$形成一个的数组$b$,其中$b_k=\max(a_{i,k},a_{j,k})(k \in[1,m])$。  
让你求出选哪$\text{2}$个数组使得$\min_{k=1}^{m}b_k$最大。  

外层可以很套路的套一个二分。  
问题就可以转化为传进来的$\text{mid}$答案是否合法。再观察$\text{m=8}$极小，提示了我们可以状压。   
对于一个数组$a$，如果$a_i \ge \text{mid}$，我们就把状态$\text{s}$的这一位设成$\text{1}$，否则设成$0$，然后把$\text{s}$丢进一个桶$\text{buc}$里，其中$\text{buc}_s$表示$\text{s}$这个状态是从哪一个数组过来的。  
最后枚举状态$\text{s0,s1}$，如果$\text{s0|s1=(1<<m)-1}$（只要这一位有一个数大于$\text{mid}$则这一位就是合法的）且$\text{buc}_{s0}$与$\text{buc}_{s1}$有数，那么这个状态就是合法的。  
时间复杂度$O(log(\max{a_{i,j}})\times \max(nm,2^m))$

---

