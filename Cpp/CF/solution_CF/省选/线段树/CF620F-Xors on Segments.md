# Xors on Segments

## 题目描述

You are given an array with $ n $ integers $ a_{i} $ and $ m $ queries. Each query is described by two integers $ (l_{j},r_{j}) $ .

Let's define the function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF620F/f18ed64d02d5b1c443dfe0810af3982715620dfd.png). The function is defined for only $ u<=v $ .

For each query print the maximal value of the function $ f(a_{x},a_{y}) $ over all $ l_{j}<=x,y<=r_{j},\ a_{x}<=a_{y} $ .

## 样例 #1

### 输入

```
6 3
1 2 3 4 5 6
1 6
2 5
3 4
```

### 输出

```
7
7
7
```

## 样例 #2

### 输入

```
1 1
1
1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6 20
10 21312 2314 214 1 322
1 1
1 2
1 3
1 4
1 5
1 6
2 2
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 4
4 5
4 6
5 5
5 6
6 6
```

### 输出

```
10
21313
21313
21313
21313
21313
21312
21313
21313
21313
21313
2314
2315
2315
214
215
323
1
323
322
```

# 题解

## 作者：楚泫 (赞：6)

## 题意：

给定$N(1≤N≤5⋅104)$个整数$a_i(1≤a_i≤10^6)$

以及$M(1≤M≤5·10^3)$个查询。

定义$f(i,j)$=(i^i+1^i+2^...^j)。

对于每个查询(l,r)，求出每个查询中最大的$f(a_x,a_y)\quad (l≤x,y≤r\;;a_x≤a_y)$	

---

预处理异或前缀和。

定义$f[j]$表示从i开始，到j位置的最大答案。

每次利用得到的值每次更新所有可更新的区间。

---

### code:

```cpp
#include <bits/stdc++.h>
#define endl putchar('\n')
using namespace std;
inline void read(int &a) {a=0;int c=getchar(),b=1; while(c>'9'||c<'0') {if(c=='-')b=-1;c=getchar();} while(c>='0'&&c<='9') a=(a<<3)+(a<<1)+c-48,c=getchar();a*=b; }
inline void write(int x) {if(x>9)write(x/10);putchar('0'+x%10);}
inline void W(int x) {if(x<0){putchar('-'),x=-x;}write(x);}
/**/
const int N=5e4+5,M=5e3+5,A=1e6+5;
int n,m,a[N],l[M],r[M],sum[A],f[N],ans[M];
/**/
int main()
{
	for(int i=1;i<=A-5;i++) sum[i]=i^sum[i-1];
	read(n);read(m);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=m;i++) read(l[i]),read(r[i]);
	for(int i=1;i<=n;i++)
	{
		f[i]=a[i];
		for(int j=i+1;j<=n;j++)
		{
			f[j]=max(f[j-1],sum[min(a[i],a[j])-1]^sum[max(a[i],a[j])]);
		}
		for(int j=1;j<=m;j++)
		{
			if(i>=l[j]&&i<=r[j])	
			{
				ans[j]=max(ans[j],f[r[j]]);
			}
		}
	}
	for(int i=1;i<=m;i++) W(ans[i]),endl;
}
```


---

## 作者：FutaRimeWoawaSete (赞：1)

什么啊怎么就 2800 了……

提供一个稍微简单点的直接 dp 不依赖查询个数的做法，好像也很裸……

（所以这道题从 ds 到 dp 都没什么太大的亮点为什么是 2800 呢）

首先就是有一个特别简单的回滚莫队的做法，就是你直接用一个函数 $g(i) = \bigoplus_{i = 1} ^ x$，$f(a,b)$ 就是 $g(b) \bigoplus g(a - 1)$ 了。然后问题变成了一个区间每个数有两个属性值（$g(a_i)$ 和 $g(a_i - 1)$）然后选择不同属性的数使得异或和最大，但是这里注意到选择的数有一个偏序关系，就是说如果 $a_i > a_j$ 就只能算 $(g(a_i),g(a_j - 1))$ 而不能算 $(g(a_i - 1),g(a_j))$，我们考虑一下该怎么体现这个性质。

个人想了一下，最简单的做法可能就是直接以 g 数组对应的值为键值，在 trie 上每个节点维护当前在这个节点里面最小/最大的 $a_x$，由于只插入不删除，所以这个东西直接记录一下就好了，然后就是正常的直接做就好了。

时间复杂度 $O((n \sqrt m + m\sqrt n) \log V)$，空间复杂度 $O(n \log V)$。

考虑直接用 $dp_{l,r}$ 表示区间的答案，转移式如下：

$dp_{l,r} = \max(dp_{l + 1,r},dp_{l,r-1},f(\min(a_l,a_r),\max(a_l,a_r)))$。

滚动数组，询问存到左端点算完直接问，就是 $O(n ^ 2 + m)$ 以及线性空间了。

```cpp
/*
f(i,j) = f(1,i-1) ^ f(1,j)
现在相当于区间中每个数有两个属性值，选择两个数使得 ^ 值最大。
直接写个 trie+回滚就做完了（bushi 
但是，我们要找到最短的做法！！！
容易发现 m 很小，每次我们可以暴力扫一遍数，如果能 O1 加入一个数就好了。
压位 Trie，哈哈。
......
可以直接写 dp 啊，我是 sb。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 5e4 + 5;
int dp[Len][2],g[1000005];//dp_{i,j}
int n,m,a[Len];int Print[Len];
struct Node
{
	int l,pos;
	Node(){l = pos = 0;}
	Node(int L,int POS){l = L , pos = POS;}
};
vector<Node> vec[Len]; 
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= 1000000 ; i ++) g[i] = (g[i - 1] ^ i);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	for(int i = 1 ; i <= m ; i ++) 	
	{
		int l,r;scanf("%d %d",&l,&r);
		vec[r].push_back(Node(l , i));
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		int ms = 0;
		for(int j = i ; j >= 1 ; j --)//dp_{j,i}
		{
			dp[j][(i & 1)] = max(dp[j + 1][(i & 1)] , dp[j][((i & 1) ^ 1)]);
			//if(j == 3 && i == 5) printf("!!!%d\n",dp[j][(i & 1)]);
			if(a[i] > a[j]) ms = (g[a[j] - 1] ^ g[a[i]]);
			else ms = (g[a[i] - 1] ^ g[a[j]]); 
			dp[j][(i & 1)] = max(dp[j][(i & 1)] , ms); 
			//printf("%d %d %d\n",j,i,dp[j][(i & 1)]);
		}
		for(int j = 0 ; j < vec[i].size() ; j ++) Print[vec[i][j].pos] = dp[vec[i][j].l][(i & 1)];
	}
	for(int i = 1 ; i <= m ; i ++) printf("%d\n",Print[i]);
	return 0;
}
```

---

## 作者：yizhiming (赞：0)

提供一个在线分块 $O(n\sqrt{n}\log n)$ 的做法，但是常数较大跑不过暴力和回滚莫队，但是扩展性强。

[Link](https://www.luogu.com.cn/problem/CF620F)

### 题目大意

给定一个长为 $n$ 的序列 $a$，定义 $f(i,j)$ 表示 $i\oplus i+1\oplus i+2\oplus\dots \oplus j$，其中 $\oplus$ 表示异或，$m$ 次询问 $l,r$，求 $f(a_x,a_y)$ 满足 $x,y\in[l,r],a_x\leq a_y$ 的最大值。

$1\leq n\leq 10^5,1\leq m \leq 5\times 10^3,1\leq a_i\leq 10^6$。

### 题目分析

设 $s_i$ 表示 $1\oplus 2 \oplus 3\oplus \dots \oplus i$，则 $f(i,j) = s_{i-1}\oplus s_j$，这启发我们将所有的点对用这种形式表示出来，但是这样的问题也是明显的。

假设我们将所有的 $s_{a_i-1}$ 都扔到 trie 上贪心，那么就会出现 $s_{i-1}$ 在树上，统计 $j$ 的时候求出了 $s_{i-1}\oplus s_j$，但假设这个时候 $i>j$，那么实际表示出来的异或值，就变成了 $f(j+1,i-1)$，而非我们想要的贡献。

所以考虑将其有序化，若我们能够保证插入数据结构的顺序是有序的，那么就不会出现上述的问题。

我们将其分块，然后块内排序后两个块之间的贡献可以归并起来计算，像这一类问题，有一个比较常见的解法，我们设 $s_{i,j}$ 表示这个点对的左右端点在 $i$ 块到 $j$ 块之间时的最大值，$f_{i,j}$ 表示左端点在 $i$ 到 $i$ 所在块右端点，右端点在 $j$ 块的最大值，设 $g_{i,j}$ 与 $f$ 相反，$val_{i,j}$ 表示左端点在 $i$ 块，右端点在 $j$ 块的最大值。

考虑如何维护这些东西，容易发现若能推出来 $f$，以及 $s_{i,i}$，我们就可以类似区间 dp 的方法，推出 $s$，所以先考虑 $s_{i,i}$，这种就对于每个块，排序后依次将 $s_{a_i-1}$ 插入到 tire 树上，贪心求 $s_{a_i}$ 的异或最大值即可。

求 $f$，可以通过枚举当前左端点所在块是哪一个，右端点是哪一个，每次固定左边，向右扩展，将扩展的新块与左端点所在块归并起来求贡献即可，求完之后在对应位置记一下最大值，块内求一遍前缀最大值即可求出 $f$，对于 $g$ 同理。

那么当前答案就可以由中间部分的整块，散块对整块处理。

当然发现还缺少散块对散块，这种情况直接归并两个散块，对于在对应区间内的点拎出来求最大异或值即可。

### Code

实际实现上，容易发现 $f,g$ 不重叠，所以可以合到一起。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 5e4+5;
const int B = 250;
int s[B][B];//整块的答案
int f[N][B];//当i<j块左端点时左端点在散块区间，右端点在整块，否则反之 
int bel[N],L[N],R[N],n,m; 
int a[N],V[1000005],rt;
struct trie{
	struct aa{
		int ch[2];
		int siz;
		void clear(){
			ch[0] = ch[1] = 0;
			siz = 0;
		}
	}node[N*30];
	int tot;
	int newnode(){
		int u = ++tot;
		node[u].clear();
		return u;
	}
	void ins(int &u,int cs,int x){
		if(!u){
			u = newnode();
		}
		node[u].siz++;
		if(cs==-1){
			return;
		}
		bool y = (x>>cs)&1;
		ins(node[u].ch[y],cs-1,x);
	}
	void clear(){
		rt = tot = 0;
	}
	int ask(int u,int cs,int x){
		if(cs==-1||!u){
			return 0;
		}
		bool y = (x>>cs)&1;
		if(node[node[u].ch[!y]].siz){
			return ask(node[u].ch[!y],cs-1,x)+(1<<cs);
		}else{
			return ask(node[u].ch[y],cs-1,x);
		}
	}
}T;
struct bb{
	int id,x;
	bool operator<(const bb&a)const{
		return x<a.x;
	}
}in[N];
int val(int l1,int r1,int l2,int r2){
	int x = bel[l1],y = bel[l2];
	int res = 0;
	T.clear();
	int l = L[x];
	for(int i=L[y];i<=R[y];i++){
		if(in[i].id>r2||in[i].id<l2){
			continue;
		}
		while(l<=R[x]){
			if(in[l].x<=in[i].x){
				if(l1<=in[l].id&&in[l].id<=r1){
					T.ins(rt,22,V[in[l].x-1]);
					res = max(res,T.ask(rt,22,V[in[l].x]));
				}
				l++;
			}else{
				break;
			}
		}
		T.ins(rt,22,V[in[i].x-1]); 
		res = max(res,T.ask(rt,22,V[in[i].x]));
	}
	for(int i=l;i<=R[x];i++){
		if(in[i].id<l1||in[i].id>r1){
			continue;
		}
		T.ins(rt,22,V[in[i].x-1]);
		res = max(res,T.ask(rt,22,V[in[i].x]));
	}
	return res;
}
int main(){
//	freopen("cs.txt","r",stdin);
	n = read();m = read();
	for(int i=1;i<=n;i++){
		int x = read();
		in[i] = (bb){i,x};
	}
	int sz = sqrt(n);
	for(int i=1;i<=n;i++){
		bel[i] = (i-1)/sz+1;
		if(!L[bel[i]]){
			L[bel[i]] = i;
		}
		R[bel[i]] = i;
	}
	for(int i=1;i<=1e6;i++){
		V[i] = V[i-1]^i;
	}
	for(int i=1;i<=bel[n];i++){
		sort(in+L[i],in+R[i]+1);
	}
	for(int i=1;i<=bel[n];i++){
		for(int j=i+1;j<=bel[n];j++){//求钦定左端点在哪个块时的f 
			T.clear();
			int l = L[i]; 
			for(int k=L[j];k<=R[j];k++){
				while(l<=R[i]){
					if(in[l].x<=in[k].x){
						T.ins(rt,22,V[in[l].x-1]);
						l++;
					}else{
						break;
					}
				}
				f[in[k].id][i] = T.ask(rt,22,V[in[k].x]);
			}
			T.clear();
			int r = R[i];
			for(int k=R[j];k>=L[j];k--){
				while(r>=L[i]){
					if(in[r].x>in[k].x){
						T.ins(rt,22,V[in[r].x]);
						r--;
					}else{
						break;
					}
				}
				f[in[k].id][i] = max(f[in[k].id][i],T.ask(rt,22,V[in[k].x-1]));
			}
			for(int k=L[j]+1;k<=R[j];k++){
				f[k][i] = max(f[k][i],f[k-1][i]);
			}
		}
	}
	for(int i=1;i<=bel[n];i++){
		for(int j=1;j<=i-1;j++){
			T.clear();
			int l = L[i];
			for(int k=L[j];k<=R[j];k++){
				while(l<=R[i]){
					if(in[l].x<=in[k].x){
						T.ins(rt,22,V[in[l].x-1]);
						l++;
					}else{
						break;
					}
				}
				f[in[k].id][i] = T.ask(rt,22,V[in[k].x]);
			}
			T.clear();
			int r = R[i];
			for(int k=R[j];k>=L[j];k--){
				while(r>=L[i]){
					if(in[r].x>in[k].x){
						T.ins(rt,22,V[in[r].x]);
						r--;
					}else{
						break;
					}
				}
				f[in[k].id][i] = max(f[in[k].id][i],T.ask(rt,22,V[in[k].x-1]));
			}
			for(int k=R[j]-1;k>=L[j];k--){
				f[k][i] = max(f[k][i],f[k+1][i]);
			}
		}
	}
	for(int i=1;i<=bel[n];i++){
		T.clear();
		for(int j=L[i];j<=R[i];j++){
			T.ins(rt,22,V[in[j].x-1]);
			s[i][i] = max(s[i][i],T.ask(rt,22,V[in[j].x]));
			
		}
	}
	for(int i=2;i<=bel[n];i++){
		for(int j=1;j+i-1<=bel[n];j++){
			int l = j,r = j+i-1;
			s[l][r] = max({s[l][r-1],s[l+1][r],f[L[l]][r]});
		}
	}
	int z = 0;
	while(m--){
		int l,r;
		l = read();r = read();
		z++;
		int ans = 0;
		if(bel[l]==bel[r]){
			T.clear();
			for(int i=L[bel[l]];i<=R[bel[l]];i++){
				if(in[i].id<l||in[i].id>r){
					continue;
				}
				T.ins(rt,22,V[in[i].x-1]);
				ans = max(ans,T.ask(rt,22,V[in[i].x]));
				
			}
		}else{
			ans = s[bel[l]+1][bel[r]-1];
			for(int i=bel[l]+1;i<bel[r];i++){
				ans = max(ans,f[l][i]);
				ans = max(ans,f[r][i]);
			}
			ans = max(ans,val(l,R[bel[l]],L[bel[r]],r));
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF620F](https://www.luogu.com.cn/problem/CF620F)

* **【解题思路】**

首先我们看到显眼但不那么神奇的 $n=5\times 10^4,m=5\times10^3$，然后我们看到不那么显眼但非常神奇的时限 $10\rm s$。

于是考虑乱搞，我们发现问题很显然的可以转化为给 $2$ 个数组，每个数组选一个数的最大异或和。然后我们就能想到 $\mathrm O(nm\log v)$ 的 Trie。

然后可以发现过不去，乱搞一下，首先我们看到很多答案都是一样的，大部分询问的答案都等于区间 $[1,n]$ 的答案 $c$。于是我们 $\mathrm O(n^2)$ 的处理出离每个数 $x$ 最近的 $y$，使得 $f(a_x,a_y)=c$。对于某次询问，如果 $x,y$ 都在这个区间里直接输出 $c$ 并退出即可。

然后就喜提 slowest solution。

* **【代码实现】**

```cpp
#include <algorithm>
#include <iostream>
#include <array>

using namespace std;

struct trie_node
{
	int edtag;
	array<int,2> sons;
};

array<trie_node,1000001> trie;
array<int,50001> nums,srted,tmparr,maxvans;

int prexor(int target)
{
	switch(target&3)
	{
		case 0:
			return target;
		case 1:
			return 1;
		case 2:
			return target+1;
		default:
			return 0;
	}
}
int get_mxxor(int curnd,int depth,const int target)
{
	if(depth<0)
		return trie[curnd].edtag^target;
	int tmp=trie[curnd].sons[(target>>depth&1)^1];
	if(tmp)
		return get_mxxor(tmp,depth-1,target);
	return get_mxxor(trie[curnd].sons[target>>depth&1],depth-1,target);
}
inline int abs(int x)
{
	return x<0?-x:x;
}

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt,cntq,maxv=0,cntnode=0,answer;
	cin>>cnt>>cntq;
	maxvans.fill(-1e9);
	for(int i=1;i<=cnt;i++)
		cin>>nums[i];
	for(int i=0;i<cnt;i++)
		srted[i]=nums[i+1];
	sort(srted.begin(),srted.begin()+cnt);
	for(int i=0;i<cnt;i++)
	{
		int curnode=0,tmp=prexor(srted[i]-1);
		for(int j=19;~j;j--)
		{
			if(!trie[curnode].sons[tmp>>j&1])
				trie[curnode].sons[tmp>>j&1]=++cntnode;
			curnode=trie[curnode].sons[tmp>>j&1];
		}
		trie[curnode].edtag=tmp;
		maxv=max(maxv,get_mxxor(0,19,prexor(srted[i])));
	}
	for(int i=0;i<=cntnode;i++)
		trie[i].sons.fill(0);
	for(int i=1;i<=cnt;i++)
		srted[i-1]=prexor(nums[i]),tmparr[i-1]=prexor(nums[i]-1);
	for(int i=0;i<cnt;i++)
		for(int j=0;j<cnt;j++)
			if(nums[i+1]>=nums[j+1]&&(srted[i]^tmparr[j])==maxv&&abs(i-j)<abs(maxvans[i]-i))
				maxvans[i+1]=j+1;
	while(cntq--)
	{
		int rgl,rgr;
		cntnode=0,answer=0;
		cin>>rgl>>rgr;
		for(int i=rgl;i<=rgr;i++)
		{
			srted[i-rgl]=nums[i];
			if(maxvans[i]>=rgl&&maxvans[i]<=rgr)
			{
				cout<<maxv<<'\n';
				goto nextcase;
			}
		}
		sort(srted.begin(),srted.begin()+rgr-rgl+1);
		for(int i=0;i<=rgr-rgl;i++)
		{
			int curnode=0,tmp=prexor(srted[i]-1);
			for(int j=19;~j;j--)
			{
				if(!trie[curnode].sons[tmp>>j&1])
					trie[curnode].sons[tmp>>j&1]=++cntnode;
				curnode=trie[curnode].sons[tmp>>j&1];
			}
			trie[curnode].edtag=tmp;
			answer=max(answer,get_mxxor(0,19,prexor(srted[i])));
			if(answer==maxv)
				break;
		}
		for(int i=0;i<=cntnode;i++)
			trie[i].sons.fill(0);
		cout<<answer<<'\n';
		nextcase:;
	}
	return 0;
}

```

---

## 作者：hxhhxh (赞：0)

## 大意

给定一个有 $ n $ 个元素的数组 $ a $ 和 $ m $ 次询问，每一次询问给你一个区间 $ l,r $ ，求

$$ \max_{i=l}^r \max_{j=l}^r f(a_i,a_j) $$

其中

$$ f(i,j) = \oplus_{k=\min(i,j)}^{\max(i,j)} k $$

## 思路

注意这道题时间复杂度可以到 $ O(n^2) $ ，但空间复杂度不可以！

------

首先，设 $ g(x) = \oplus_{i=1}^x i $ 

易知 $ f(i,j) = g(\max(i,j)) \oplus g(\min(i,j)-1) $ 

所以可以简单地预处理出所有 $ g(a_i) $ 和 $ g(a_i - 1) $ ，然后就可以**小常数地**算出所有 $ f(a_i,a_j) $ 了。

正常套路应该是用一个二维数组 $ s $ ， $ s_{i,j} = \max(s_{i+1,j},\max_{k=i}^j f(a_k,a_i)) $ ，然后对于询问 $ i $ ，答案就是 $ s_{l_i,r_i} $ 。

但是，空间炸了！大家还记得`dp`时空间炸了怎么办吗？滚动数组或者降维。我选择了降维。

时间复杂度 $ O(n^2 + n \times m + maxa) $ ，空间复杂度 $ O(n + m + maxa) $ 

---
### 毒瘤拓展

$ a_i \leq 10^9, m \leq 2\times 10^5 $

对于每一个 $ i $ ，将询问 $ l_i,r_i $ 存到一个 $ l_i $ 对应的`vector`里，当访问到 $ i $ 时更新答案即可。 $ O(n \times m) \rightarrow O(m) $ 。

可以 $ O(1) $ 算出 $ g(i) $ ，详情参照[abc121d](https://atcoder.jp/contests/abc121/tasks/abc121_d) 。 $ O(maxa) \rightarrow O(n) $ 。

最终时间复杂度 $ O(n^2 + m) $ ，空间复杂度 $ O(n + m) $ 

## 代码

注意不要无必要地增加常数。

```cpp
#include<bits/stdc++.h>
#define min(a,b) a<b?a:b
#define max(a,b) a<b?b:a
using namespace std;
int n,m,a[50004],s[50004],ans[5003],t[50004],tt[50004];
vector<pair<int,int> >e[50004];
inline int g(const int&x){
	return (x%4==1)?1:(x%4==2)?x+1:(x%4==0)?x:0;
}
inline int f(const int&i,const int&j){
	if(a[i]>a[j]) return t[i]^tt[j];
	return tt[i]^t[j];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),t[i]=g(a[i]),tt[i]=g(a[i]-1);
	for(int i=1,j,k;i<=m;i++){
		scanf("%d %d",&j,&k);
		e[j].push_back((pair<int,int>){i,k});
	}
	for(int i=n;i>=1;i--){
		for(int j=i;j<=n;j++) s[j]=max(s[j],f(i,j));
		for(int j=i;j<=n;j++) s[j]=max(s[j],s[j-1]);
		for(int j=0;j<e[i].size();j++) ans[e[i][j].first]=s[e[i][j].second];
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

