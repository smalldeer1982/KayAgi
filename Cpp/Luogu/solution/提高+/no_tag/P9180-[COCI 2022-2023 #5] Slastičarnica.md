# [COCI 2022/2023 #5] Slastičarnica

## 题目描述

有一列数 $a_1,\ldots,a_n$ 和 $q$ 次操作，每次操作形如「删掉长为 $d_i$ 的前缀或后缀，且需要保证这个前缀和后缀中所有元素都大于等于 $s_i$。」每次操作前，你可以选择长度任意的前缀或后缀（可以为空，且两端可同时选择），并删除它。如果某次操作无法进行，则停止这次和之后的所有操作。问最多可以进行多少次操作。

## 说明/提示

样例 $3$ 解释：

首先删除前缀 $(1)$，之后进行第一次操作，删除前缀 $(3,2,5)$。此时序列变为 $(1,4,6,2,1)$。

然后删除前缀 $(1)$，之后进行第二次操作，删除前缀 $(4,6)$，此时序列变为 $(2,1)$。

然后不删除任何前缀或后缀，之后进行第三次操作，删除后缀 $(1)$，此时序列变为 $(2)$。

然后不删除任何前缀或后缀，之后进行第四次操作，删除唯一剩余的 $(2)$，此时序列变为空序列。

最后一次操作由于序列为空无法完成，操作停止。

因此一共进行了四次操作。

|子任务编号|	附加限制|	分值|
|:-:|:-:|:-:|
|$0$|	是样例|	$0$|
|$1$|	$n,q\le 100$|	$19$|
|$2$|	$d_1=d_2=\ldots=d_q=1$|	$28$|
|$3$|	无附加限制|	$53$|

## 样例 #1

### 输入

```
5 6
1 2 3 4 5
1 1
1 2
1 3
1 4
1 6
1 5
```

### 输出

```
4```

## 样例 #2

### 输入

```
5 3
1 3 2 2 1
3 1
1 3
2 2
```

### 输出

```
2```

## 样例 #3

### 输入

```
9 5
1 3 2 5 1 4 6 2 1
3 2
2 3
1 1
1 2
1 1
```

### 输出

```
4```

# 题解

## 作者：Demeanor_Roy (赞：12)

- 一道有意思的 dp。

------------

显然 $q$ 的范围是诈骗的，因为最多 $n$ 次操作序列就没了。

显然无法贪心，于是考虑 dp。不难发现当进行到第 $T$ 次操作时，前 $T-1$ 次操作留下来的后效性就是前缀用到了哪和后缀用到了哪。显然不可能全部记录在状态里，否则状态数就是 $n^3$ 的。

于是考虑常见转化：将一维记录在值里。具体来说，令 $f(i,j)$ 表示考虑到第 $i$ 个操作，前缀该用 $j$，后缀该用位置的最大值。

转移的话分两类：

- 当前用前缀：$f(i,j)=f(i-1,\max_{k=1}^{j-d_i}f(i-1,k))[j \geq d+1 \ \wedge \ \min_{p=j-d}^{j-1}v_p \geq s_i]$。

- 当前用后缀：$f(i,j)=\max_{k=1}^{f(i-1,j)}k[\min_{p=k}^{k+d_i-1}v_p \geq s_i]$。

暴力转移 $n^3$，显然第一项可以前缀和优化，第二项枚举的时候用变量记录个最大值即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5010,INF=1e9;
int n,m,v[N],pre[N],f[N][2],mi[N][N];
int main()
{
	memset(f,-1,sizeof f);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=1;i<=n;i++) 
	{
		mi[i][i-1]=INF;
		for(int j=i;j<=n;j++) mi[i][j]=min(mi[i][j-1],v[j]);
	}
	pre[0]=-1;f[1][0]=n;
	for(int t=1;t<=min(n,m);t++)
	{
		int d,s,mx=-1,fr=1;
		scanf("%d%d",&d,&s);
		for(int i=1;i<=n;i++) f[i][t&1]=-1;
		for(int i=1;i<=n;i++) pre[i]=max(pre[i-1],f[i][(t&1)^1]);
		for(int i=d+1;i<=n;i++) if(mi[i-d][i-1]>=s) f[i][t&1]=pre[i-d];
		for(int i=1;i<=n;i++) 
			if(f[i][(t&1)^1]-i+1>=d) 
			{
				while(fr+d-1<=f[i][(t&1)^1]) mx=max(mx,mi[fr][fr+d-1]>=s?fr:-1),fr++;
				f[i][t&1]=max(f[i][t&1],mx-1);
			}
		bool ex=false;
		for(int i=1;i<=n;i++) if(i-f[i][t&1]<=1) ex=true;
		if(!ex) return printf("%d\n",t-1),0;
	}
	printf("%d\n",min(n,m));
	return 0;
}
```


---

## 作者：_anll_ (赞：9)

## 思路
### 暴力

首先 $q$ 的范围不重要，因为你最多只能进行 $n$ 次操作。尝试一番后发现不太可以贪心，考虑 dp。

数据范围启示着三维，那就可以用类似于区间 dp 的方式去进行，想到这点就很容易地给出 $f_{i,l,r}$，表示第 $i$ 次询问，**处理完后**剩区间 $[l,r]$ 是否可行。

具体地，可以从左转移的条件：
$$
\min\limits_{l-d\le j\le l-1}{A_j
}\ge s \ \text{且}\ \exists k\in [1,1-d],f_{i,k,l}=1
$$
同理，可以从右转移的条件：
$$\min\limits_{r+1\le j\le r+d}{A_j}\ge s\ \text{且} \ \exists k\in [r+1,n],f_{i,l,k}=1
$$

### 正解
其实暴力打出来了的话这个就很显然了吧？

发现 $f_{i,l,r}$ 的可行性 dp 很冗余，考虑能不能观察出一些性质让它减掉一维。容易发现，当 $i,l$ 确定时，$r$ 的可行是有单调性的，即我们可以找到一个临界 $x$，使其满足以下条件：

$$
\forall j \in[1,x],f_{i,l,j}=1 \ \text{且} \ 
\forall k \in[x+1,n],f_{i,l,k}=0
$$

重新定义 $f_{i,l}$ 表示第 $i$ 次询问，处理完后可行且以 $l$ 为左端点的区间的最远右端点。下面我们分别考虑从左转移和从右转移的情况。

从左转移的条件很显然，为 $\min\limits_{l-d\le j\le l-1}{A_j
}\ge s$ 这个拿 st 表随便维护一下就好了。转移公式为 $f_{i,l}=\max(f_{i,l},\max\limits_{1\le j\le l-d}f_{i-1,j})$，可以拿前缀和维护。

从右转移稍微复杂一点。当且仅当 $r$ 满足$\min\limits_{r+1\le j\le r+d}{A_j}\ge s$ 时可以进行转移。定义数组 $R_x$ 表示 $x$ 及之前能满足该要求的最大值为多少，这样我们就可以先预处理，再在进行转移时快速得到可以从右转移的最大 $r$ 了。

这个题细节比较多，注意边界维护。

## 代码
注意到本文中的 $f$ 数组在代码中实际用的是 $dp$。
```cpp
#include<cmath>
#include<iostream>
#define int long long
using namespace std;
const int N=5005;
int n,q,ans,num[N],st[N][25],dp[N][N],R[N];
void init(){
	for(int i=0;i<=n;i++) for(int j=0;j<=20;j++) st[i][j]=1e10;
	for(int i=1;i<=n;i++) st[i][0]=num[i],dp[0][i]=n;
	for(int j=1;j<=20;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
int Find(int l,int r){
	int k=log2(r-l+1);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;if(q>n) q=n;
	for(int i=1;i<=n;i++) cin>>num[i];
	init();
	for(int i=1;i<=q;i++){
		int d,s,maxn=0,maxR=0;cin>>d>>s;
		for(int j=1;j<=n-d;j++){
			if(Find(j+1,j+d)>=s) R[j]=j;
			else R[j]=R[j-1];
		}
		for(int j=n-d+1;j<=n;j++) R[j]=R[j-1];
		for(int l=1;l<=n;l++){
			maxR=max(maxR,dp[i-1][l]);
			if(l-d>0) maxn=max(maxn,dp[i-1][l-d]);
			if(l-d>0&&Find(l-d,l-1)>=s&&maxn>=l)
				dp[i][l]=maxn;
			if(maxR-d>0) dp[i][l]=max(dp[i][l],R[maxR-d]);
			if(dp[i][l]<l) dp[i][l]=0;
		}
		for(int l=1;l<=n;l++) if(dp[i][l]) ans=i;
		if(ans!=i){
			for(int j=1;j<=n;j++){
				if(j+d-1>n) break;
				if(dp[i-1][j]-j+1<d) continue;
				bool st=1;
				for(int k=j;st&&k<=j+d-1;k++)
					if(num[k]<s) st=0;
				if(st){ans=i;break;}
			}
			break;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：florrygg (赞：8)

# P9180 [COCI2022-2023#5] Slastičarnica 题解

[题面](https://www.luogu.com.cn/problem/P9180)

## 题意

我觉得出题人说的已经很像人话了，我就不再赘述了（其实我读了两遍）。

## 思路

1. 但凡你有点脑子（我没脑子）就能看出来 $1\le q\le2\times 10^5$ 这个数据范围就是个[诈骗](https://www.bilibili.com/video/BV1V94y1K7GK?t=0.6)，因为你最多删除 $n$ 个数，所以你最多执行 $\min(n,q)$ 次操作，所以直接让 $q=\min(n,q)$。

2. 然后……肯定直接区间 DP 上（简单粗暴），然后直接拿下全场[最劣解](https://www.luogu.com.cn/record/158235574)。

### dp方程

先预处理，对于第 $i$ 个操作，用一个 vector 存下满足要求的所有区间

懒得写 latex 了，直接对着代码讲，对于 $dp_{i,j}$ 

```cpp
int l=*lower_bound(v[dp[i][j]+1][0].begin(),v[dp[i][j]+1][0].end(),i);//从左边取能拿到的最近的满足下一个要求的位置
int r=*--upper_bound(v[dp[i][j]+1][1].begin(),v[dp[i][j]+1][1].end(),j);//从右边取能拿到的最近的满足下一个要求的位置
if(l+d[dp[i][j]+1]-1<=j)//判断满足要求的区间是否超出 i~j 这个范围
{
	dp[l+d[dp[i][j]+1]][j]=max(dp[l+d[dp[i][j]+1]][j],dp[i][j]+1);
	maxx=max(maxx,dp[l+d[dp[i][j]+1]][j]);//统计答案
}
if(r-d[dp[i][j]+1]+1>=i)//判断满足要求的区间是否超出 i~j 这个范围
{
	dp[i][r-d[dp[i][j]+1]]=max(dp[i][r-d[dp[i][j]+1]],dp[i][j]+1);
	maxx=max(maxx,dp[r-d[dp[i][j]+1]][j]);//统计答案
}
```

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define endl '\n'

const int maxn=5010;
int n,q;
int a[maxn];
int d[maxn],s[maxn];
vector<int>v[maxn][2];
int dp[maxn][maxn];

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(q>n)
	{
		q=n;
	}
	for(int i=1;i<=q;i++)
	{
		cin>>d[i]>>s[i];
	}
	for(int i=1;i<=q;i++)
	{
		int p=1;
		v[i][0].push_back(0);
		for(int j=1;j<=n;j++)
		{
			if(a[j]<s[i])
			{
				p=j+1;
			}
			else if(j-p+1>=d[i])
			{
				v[i][0].push_back(p);
				p++;
			}
		}
		v[i][0].push_back(n+1);
		p=n;
		v[i][1].push_back(n+1);
		for(int j=n;j>=1;j--)
		{
			if(a[j]<s[i])
			{
				p=j-1;
			}
			else if(p-j+1>=d[i])
			{
				v[i][1].push_back(p);
				p--;
			}
		}
		v[i][1].push_back(0);
		reverse(v[i][1].begin(),v[i][1].end());
	}


//	for(int i=1;i<=q;i++)
//	{
//		cout<<"i="<<i<<endl;
//		cout<<"1:\n";
//		for(int j:v[i][0])
//		{
//			cout<<j<<' ';
//		}
//		cout<<endl;
//		cout<<"2:\n";
//		for(int j:v[i][1])
//		{
//			cout<<j<<' ';
//		}
//		cout<<endl;
//	}


	int maxx=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=n;j>=i;j--)
		{
			int l=*lower_bound(v[dp[i][j]+1][0].begin(),v[dp[i][j]+1][0].end(),i);
			int r=*--upper_bound(v[dp[i][j]+1][1].begin(),v[dp[i][j]+1][1].end(),j);
			if(l+d[dp[i][j]+1]-1<=j)
			{
				dp[l+d[dp[i][j]+1]][j]=max(dp[l+d[dp[i][j]+1]][j],dp[i][j]+1);
				maxx=max(maxx,dp[l+d[dp[i][j]+1]][j]);
			}
			if(r-d[dp[i][j]+1]+1>=i)
			{
				dp[i][r-d[dp[i][j]+1]]=max(dp[i][r-d[dp[i][j]+1]],dp[i][j]+1);
				maxx=max(maxx,dp[r-d[dp[i][j]+1]][j]);
			}
		}
	}
	cout<<maxx<<endl;
	return 0;
}
```

---

## 作者：ZHR100102 (赞：3)

# 暴力



不难设计出暴力状态：$dp_{q,i,j}$ 表示进行到第 $q$ 次操作，剩下区间 $[i,j]$ 是否可行。

直到全部状态都为 $0$ 的时候输出即可。

期望得分 $19pts$。


# 优化（假）

观察到每个 $dp$ 状态都只有两个值 $0,1$，那么我们可以考虑将状态中的某一维放进 $dp$ 值里。

首先尝试把 $q$ 换进去，状态设计为 $dp_{i,j}$ 为剩余区间 $[i,j]$ 时进行的最大操作数为 $q$。

那么我们怎么转移？从大往小枚举区间，然后根据当前进行的操作，每次查询满足要求的前缀后缀，转移一下即可。

此时我们不难发现，$q$ 的最大值只能是 $n$，根本无法取到更大。这就是这题的诈骗点。

时间复杂度是 $O(n^3)$ 的，而我们可以发现无法继续优化下去（四边形不等式等都用不了），就要换一种思路。

# 贪心

显然，对于一段区间而言，长度越长，自然是对答案更优。为什么？因为每次操作都可以留出更多的空间来操作。

于是我们考虑固定左端点，把右端点换出来。

# 正解

设计状态 $dp_{q,i}$ 表示进行到了第 $q$ 次操作，左端点为 $i$ 时的最大右端点在哪。

每次操作可以选前缀、后缀，于是我们分两种转移。

## 前缀

$dp_{q,i}$ 能转移当且仅当 $[i-d,i-1]$ 能被消掉，然后转移左端点在 $i$ 前面的 $j$ 的所有 $dp_{q-1,j}$ 的值。

这个可以做一个很显然的前缀和优化，不再细说。

## 后缀

感觉这个比较难搞。

$dp_{q,i}$ 能转移的条件是在 $[j,dp_{q-1,j}]$ 中有能消除的后缀，同时在这些后缀中取最大的左端点转移。

观察到 $dp_{q-1,j}$ 也在 $[1,n]$ 之间，于是我们可以预处理出对于每一个点，在他左边的最大可消除后缀的左端点在哪，这个可以 $O(n)$ 处理出。

然后每次转移一下即可。

总体时间复杂度 $O(\min(n,q)n)$。

# 细节

特判整个序列被删完的情况。只需要在删后缀里面加特判即可。因为要删完肯定是一次删全部，那么此时就没有前缀后缀之分了，算哪个都可以。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;
int n,q,a[5005],mn[5005][5005],dp[5005][5005],rmx[5005];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    memset(mn,0x3f,sizeof(mn));
    for(int i=1;i<=n;i++)
    {
        mn[i][i]=a[i];
        for(int j=i+1;j<=n;j++)mn[i][j]=min(mn[i][j-1],a[j]);
    }
    memset(dp,-1,sizeof(dp));
    dp[0][1]=n;
    for(int i=1;i<=min(n,q);i++)
    {
        bool ed=1;
        int d,s,pre=-1,p=-1;
        cin>>d>>s;
        for(int j=1;j<=n;j++)
        {
            if(j-d>=1)pre=max(pre,dp[i-1][j-d]);
            if(j-d>=1&&mn[j-d][j-1]>=s)dp[i][j]=max(dp[i][j],pre);
        }
        for(int j=1;j<=n;j++)
        {
            if(j-d+1>=1&&mn[j-d+1][j]>=s)p=max(p,j-d+1);
            rmx[j]=p;
        }
        for(int j=1;j<=n;j++)
        {
            if(rmx[dp[i-1][j]]-1>=j)dp[i][j]=max(dp[i][j],rmx[dp[i-1][j]]-1);
            if(dp[i][j]<j)dp[i][j]=-1;
            if(rmx[dp[i-1][j]]==j)ed=0;
        }
        for(int j=1;j<=n;j++)if(dp[i][j]!=-1)ed=0;
        if(ed)
        {
            cout<<i-1;
            return 0;
        }
    }
    cout<<q;
    return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：3)

首先，显然的 $q \gets \min(q,n)$。

考虑设计状态 $dp_{l,r,i}$ 表示区间 $[l,r]$ 在第 $i$ 次操作时能否存在。那么从 $dp_{l',r,i-1}$ 或者 $dp_{l,r',i-1}$ 转移到 $dp_{l,r,i}$ 时只要把区间变化的端点一侧多余的前后缀删除掉，再在 $l$ 或者 $r$ 处保留一段长度为 $d_i$ 所有数都大于等于 $s_i$ 的段即可。

考虑在 $O(n^2)$ 的时间内处理区间 $\min$ 后即可 $O(n^3)$ 转移。

由于状态只有 $1,0$ 而且对于一个 $i,l$ 来说非 $0$ 的 $r$ 一定是单调的，所以不妨把 $r$ 的分界点压入状态，也就是 $g_{i,l} = \max_{dp_{l,r,i} \not = 0}(r)$。那么接下来在左端点处的转移是一个前缀 $\max$，在右端点处的转移可以对所有长度为 $d_i$ 的段处理出区间 $\min$ 后再预处理出前缀中最靠后的满足条件的段转移即可做到 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 5114;
int n,q;
int a[maxn];
int d[maxn],s[maxn];
int dp[maxn][maxn];
int vis[maxn];
int Mx[maxn];
int Mi[maxn][maxn]; 
int premx[maxn];
int main(){
	//freopen("F.in","r",stdin);
	//freopen("F.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	q=min(q,n);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		Mi[i][i]=a[i];
	}
	for(int i=1;i<=q;i++) cin>>d[i]>>s[i];
	for(int l=1;l<=n;l++){
		for(int r=l+1;r<=n;r++) Mi[l][r]=min(Mi[l][r-1],a[r]);
	}
	memset(dp,-1,sizeof(dp)); 
	for(int i=1;i<=n;i++)
		dp[0][i]=n;
	for(int i=1;i<=q;i++){
		for(int j=1;j<=n;j++) premx[j]=max(premx[j-1],dp[i-1][j]);
		for(int j=d[i]+1;j<=n;j++) 
			if(Mi[j-d[i]][j-1]>=s[i]&&premx[j-d[i]]>=j) dp[i][j]=premx[j-d[i]];
		//左端点转移
		for(int j=1;j<d[i];j++) vis[j]=0;
		for(int j=d[i];j<=n;j++) vis[j]=(Mi[j-d[i]+1][j]>=s[i]?1:0);
		for(int j=1;j<=n;j++) Mx[j]=(vis[j]==1?j:Mx[j-1]);
		for(int j=1;j<=n;j++){
			if(dp[i-1][j]==-1) continue;
			if(Mx[dp[i-1][j]]-d[i]>=j){
				dp[i][j]=max(dp[i][j],Mx[dp[i-1][j]]-d[i]);
			}
		} 
	}
	int res=0;
	for(int i=1;i<=q;i++){
		for(int j=1;j<=n;j++)
			if(dp[i][j]!=-1) res=max(res,i);
		for(int j=1;j<=n;j++){
			if(i!=n){
				if(dp[i][j]-j+1==d[i+1]&&Mi[j][dp[i][j]]>=s[i+1]) res=max(res,i+1);
			}
		}
	}
	cout<<res<<'\n';
	return 0;
}

```

---

## 作者：dayz_break404 (赞：3)

显然贪心没有正确性，考虑 dp。

首先 $q$ 的范围是假的，即 $n$ 与 $q$ 同阶，启示我们二维的 dp。比较容易想到的是一个三维 dp：$dp_{i,l,r}$ 表示当前是第 $i$ 个操作，剩下 $[l,r]$ 是否可行，做可行性 dp 即可，时间空间都不可接受。

先考虑优化空间，我们发现当前两位固定的时候，右端点越大，对答案一定不劣。所以我们可以记 $dp_{i,j}$ 表示当前是第 $i$ 个操作，左端点为 $j$ 时右端点的最大值，当 $j>dp_{i,j}$ 时不合法。

考虑转移，每次删除可以删除前缀或者后缀，分类讨论即可。

当前用前缀时，那么一定要保证 $\min_{k=j-d}^{j-1}a_k\ge s_i$，在此前提下 $dp_{i,j}$ 可以被上一次操作 $[1,j-d]$ 的区间最大值转移而来。暴力转移是 $O(n^3)$ 的，记录前缀最大值即可做到 $O(n^2)$。

当前用后缀时，记上一次操作后可以使用的区间右端点是 $k$，那么由于使右端点最大的想法，我们找到 $k$ 左侧第一个 $w$ 满足 $\min_{k=w+1}^{w+d}a_k\ge s_i \wedge w+d\le k$，暴力转移还是 $O(n^3)$ 的。记 $mx_i$ 表示上一次操作可用的区间右端点在 $i$ 的时候，当前可用的右端点的最大值。单次转移时 $O(1)$ 的，可以做到 $O(n^2)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
bool mbs;
const int maxn=5e3+20;
int n,a[maxn],q,st[maxn][20],dp[maxn][maxn],pre[maxn],mx[maxn];
inline int ask(int l,int r){
	int k=log2(r-l+1);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}
bool mbt;
int main(){
//	cout<<(&mbs-&mbt)/1024.0/1024.0<<endl;
	n=read(),q=min(n,read());
	pre[0]=n;
	for(int i=1;i<=n;i++) a[i]=read(),st[i][0]=a[i],pre[i]=n,dp[0][i]=n;
	for(int i=1;i<=15;i++) for(int j=1;j<=n-(1<<i)+1;j++) st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
	for(int i=1;i<=q;i++) for(int j=1;j<=n;j++) dp[i][j]=-114514;
	int d,s,flag;
	for(int i=1;i<=q;i++){
		d=read(),s=read(),flag=0;
		for(int j=1;j<=n;j++) flag|=(j<=dp[i-1][j]+1);
		if(!flag) return printf("%d\n",i-2),0;
		for(int j=d+1;j<=n;j++) if(ask(j-d,j-1)>=s) dp[i][j]=pre[j-d-1];
		for(int j=0;j<=n;j++) mx[j]=-114514;
		for(int j=d;j<=n;j++){
			mx[j]=mx[j-1];
			if(ask(j-d+1,j)>=s) mx[j]=j-d;
		}
		for(int j=1;j<=n;j++) if(dp[i-1][j]!=-114514) dp[i][j]=max(dp[i][j],mx[dp[i-1][j]]);
		pre[0]=dp[i][1];
		for(int j=1;j<n;j++) pre[j]=max(pre[j-1],dp[i][j+1]);
	}
	flag=0;
	for(int j=1;j<=n;j++) flag|=(j<=dp[q][j]+1);
	if(!flag) printf("%d\n",q-1);
	else printf("%d\n",q);
	return 0;
}
```

---

## 作者：Grace2022 (赞：2)

设 $dp_{i, j}$ 表示：第 $i$ 个查询，左端点为 $j$ 的最大右端点。
## 思路
### 对于数据范围
对于 $1 \le n \le 5000$，我们应想到 $\mathcal{O}(n ^ 2)$ 的算法，但是 $1 \le q \le 2 \cdot 10 ^ 5$ 的数据范围似乎阻挠了这一点。其实不然，仔细读题便会发现，每一次操作至少会删 $(d_i)_{\min} = 1$ 的长度，最多 $n$ 次序列就会被删完，所以实际上 $1 \le q \le n \le 5000$。
### 贪心 or 二分答案 or 动态规划？
最值问题的一般解决方法应是如题的三个算法。  

对于贪心，我们能直接想到的策略是：在满足要求的情况下，使序列长度尽量长。然而，若遇见同时满足策略的几种情况，或本次操作多删为下次操作服务，等等类似的情况，子结构最优就无法得到全局最优了，所以贪心不行。  

对于二分答案，我们无法证明答案的单调性，即删掉的长短、位置和最多操作次数并无增减性上的关联，所以二分答案不行。  

最后只剩下动态规划了。可是后效性的问题怎么解释？每次选择的改动都会影响后面的结果，且第 $i$ 次操作是依托前 $i - 1$ 次操作的……其实，我们只需要把每一个可能设计为状态，转移时考虑了所有的“可能”，这个问题就不存在了。  

### 设计 dp 状态
由于数据范围的提示，这里的 $dp$ 应该至少两维。题目中的变量有：操作次数 $q$、序列长度 $n$ 和所求最大操作次数 $ans$，因为我们还要考虑前缀后缀的问题，所以序列长度 $n$ 应该分为左端点 $l$ 和右端点 $r$。如何把所有可能的情况覆盖完呢？我们需要以某种方式记录每次操作可能的 $l$ 和 $r$。  

一共四个变量 $q$、$l$、$r$、$ans$，而二维 dp 最多能记录三个变量，该怎么办呢？注意到，这里的 $ans$ 等于满足条件的 $q$ 的最大值，也就是说我们只需要线性地遍历每一次操作，判断当前操作是否满足条件，是则继续，否则输出答案、结束程序。  

统计答案的方式已经想好了，最值问题转化为了判定性问题，四个变量变成了三个：$q$、$l$、$r$，其实随便抓两个当 $i$、$j$，剩下的一个对应 $dp$ 数组的值即可。这里，我们判断是否满足条件的方式是看有没有符合条件的前缀或后缀。设第 $i$ 次操作的序列左右端点为 $l_i$、$r_i$，那么应当判断是否有区间 $[l_{i - 1}, l_i - 1]$ 或 $[r_i + 1, r_{i - 1}]$ 的元素全部大于等于 $s_i$ 且区间长度大于等于 $d_i$。因此，我们应记录当前操作的最大 $r$ 或最小 $l$，为下一次操作判断做准备。  

正解已呼之欲出。  

### 状态与转移方程
设 $dp_{i, j}$ 表示：第 $i$ 个查询，左端点为 $j$ 的最大右端点。  

设 $mn_{i, j}$ 为区间 $[i, j]$ 的最小值。  

我们将操作分为两类：  

1. **删前缀**。暂时仅考虑操作中的删前缀，遍历删完前缀后的左端点 $j (d_i + 1 \le j \le n)$，此时删前缀前的左端点应是 $j - d_i$，那么 $j$ 当且仅当满足 $mn_{j - d_i, j - 1} \ge s_i$ 时符合题意，此时可以沿用上一次操作的 dp 值，即：$dp_{i, j} \gets dp_{i - 1, j}$。现在考虑操作前的前缀删除操作，这一步的删前缀应是从任意左端点 $l (l \le j)$ 删到 $j$ 的操作，所以我们应当取 $\max_{k = 1}^{j}dp_{i - 1, k}$。这里会超时，所以我们通过求前缀最大值的方式，提前统计好第 $i - 1$ 次操作，左端点小于等于 $j$ 的最大右端点。最后复杂度仍是 $\mathcal{O}(n ^ 2)$。

2. **删后缀**。这个比较好想，因为显然地，$dp_{i, j} \gets k$，其中 $k$ 为删完后缀的右端点，$k$ 应满足 $mn_{k + 1, k + d_i} \ge s_i$，且删前右端点 $k + d_i$ 应小于等于上次操作右端点最大值 $dp_{i - 1, j}$。同样很显然，$k$ 的枚举需要优化。因为是一个类似滑动窗口的问题，我们选择用 while 循环加指针来做，具体请看代码，这里不多阐述。

状态转移完毕，现在统计答案：如果有至少一组端点满足条件，即 $l \le r$ 或 $l = r + 1(l, r \gt 0)$（操作后的序列可以为空）时满足条件。如果嫌两步判断麻烦就把 $dp$ 数组初始化成 $-1$ 再判断 $l \le r + 1$ 即可，因为端点 $0$ 是无效的。  

对于初始化，根据定义，应有 $dp_{0, 1} \gets n$。  

至此，题目已经做完，只剩下一堆细节和代码了……  
## 代码
对于求区间最小值 $mn$ 数组的部分，既可以选择 $\mathcal{O}(n ^ 2)$ 的暴力，也可以选择 $\mathcal{O}(n \log n)$ 的 st 表。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	char c = getchar();
	int s = 0, st = 1;
	while(c < '0' || c > '9'){
		(c == '-') && (st = -1);
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = getchar();
	}
	return st * s;
}
inline void write(int x){
	if(x < 0){
		x = -x;
	}
	if(x > 9){
		write(x / 10);
	}
	putchar(x % 10 + 48);
}
inline void Endl(){
	putchar('\n');
}
inline void Swap(int &a, int &b){
	a ^= b;
	b ^= a;
	a ^= b;
}
/*
f[i][j]: 第 i 个查询，左端点为 j 的最大右端点
if(mn[k][k + d[i] - 1] >= s[i]){ // 删前缀 
	f[i][j] = f[i - 1][k];
}
if(mn[j][k - d[i] + 1] >= s[i] && k <= f[i - 1][j]){ // 删后缀 
	f[i][j] = max(f[i][j], k);
}
*/
const int N = 5e3;
int a[N + 5], f[N + 5][N + 5], d[N + 5], s[N + 5], mn[N + 5][25], mx[N + 5], lg[N + 5];
inline int querymn(int l, int r){
	return min(mn[l][lg[r - l + 1]], mn[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]);
}
signed main(){
	int n, q, ans = 0;
	n = read(), q = read();
	for(int i = 2; i <= N; ++i){
		lg[i] = lg[i >> 1] + 1;
	}
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		mn[i][0] = a[i];
	}
	for(int j = 1; j <= 18; ++j){
		for(int i = 1; i + (1 << j) - 1 <= n; ++i){
			mn[i][j] = min(mn[i][j - 1], mn[i + (1 << j - 1)][j - 1]);
		}
	}
	/*
	for(int i = 1; i <= n; ++i){
		for(int j = i + 1; j <= n; ++j){
			mn[i][j] = min(mn[i][j - 1], a[j]); // 任意区间的最小值，可用 st 表 
		}
	}
	*/ 
	q = min(q, n);
	f[0][1] = n;
	for(int i = 1; i <= q; ++i){
		d[i] = read(), s[i] = read();
		for(int j = 1; j <= n; ++j){
			mx[j] = max(mx[j - 1], f[i - 1][j]); // 上一次操作，左端点小于等于 j 的最大右端点 
		}
		for(int j = d[i] + 1; j <= n; ++j){ // j: 删完前缀后的左端点
			if(querymn(j - d[i], j - 1) >= s[i]){
				f[i][j] = max(f[i][j], mx[j - d[i]]);
			}
		}
		int k = 1; // 删完后缀后的右端点
		for(int j = 1; j <= n; ++j){
			while(j + d[i] - 1 <= f[i - 1][j] && k + d[i] <= f[i - 1][j]){
				if(querymn(k + 1, k + d[i]) >= s[i]){
					f[i][j] = max(f[i][j], k);
				}
				++k;
			}
		}
		bool pd = 0;
		for(int j = 1; j <= n; ++j){
			if(j == 1 && j <= f[i][j] || j > 1 && j <= f[i][j] + 1){ // 序列可以为空 
				pd = 1;
				break;
			}
		}
		if(!pd){
			ans = i - 1;
			break;
		}
		ans = max(ans, i);
	}
	write(ans);
	Endl();
	return 0;
}
/*
5 6 1 2 3 4 5 1 1 1 2 1 3 1 4 1 6 1 5
5 3 1 3 2 2 1 3 1 1 3 2 2
9 5 1 3 2 5 1 4 6 2 1 3 2 2 3 1 1 1 2 1 1
*/
```

---

## 作者：ivyjiao (赞：2)

你说得对，但是我 $O(n^3)$ 过了。

首先 $q$ 是假的，因为每次操作都会删元素，最多删 $m$ 次序列就没了，所以 $q=\min\{q,n\}$。

这就给了这题开二维数组的可能性，定义 $dp_{i,j}$ 为进行第 $i$ 次操作后，前缀用到 $j$ 的后缀最大值。

本次操作删前缀：

$$dp_{i,j}=\max_{k=1}^{k\leq dp_{i-1,j}-d_i}dp_{i-1,k}(\min_{l=j-d}^{l\leq j-1}a_l\geq s_i)$$

本次操作删后缀：

$$dp_{i,j}=\max_{k=1}^{k\leq dp_{i-1,j}}k(\min_{l=j+1}^{l\leq j+d}a_l\geq s_i)$$

发现第一个式子可以看到有效值就退（单调的），第二个式子写的时候可以记录最大值。

然而这样做是 $O(n^3)$ 的，在本题最高赞题解中说道：

> 显然第一项可以前缀和优化，第二项枚举的时候用变量记录个最大值即可。

然而我太菜了，没有写前缀和优化，但是也过了，可见数据还是很善的，~~$O(n^3)$ 过 $5000$ 不是基本操作吗~~。

这题原来是紫来着，怎么降蓝了，~~哦是我降的啊，那没事了~~。

啊我这份代码就是 $O(n^2)$ 的？？？

代码，加了一些小的优化：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5001;
int n,q,a[N],b[N][N],dp[N][N],d,s,c[N];
int main(){
	cin>>n>>q;
	q=min(n,q);
	for(int i=1;i<=n;i++) cin>>a[i];
	dp[0][1]=n;
	for(int i=1;i<=n;i++){
		b[i][i]=a[i];
		c[i]=n;
		for(int j=i+1;j<=n;j++) b[i][j]=min(b[i][j-1],a[j]);
	}
	for(int i=1;i<=q;i++){
		cin>>d>>s;
		memset(dp[i],-1,sizeof dp[i]);
		for(int j=d+1;j<=n;j++) if(b[j-d][j-1]>=s) dp[i][j]=c[j-d];
		for(int j=1;j<=n;j++){
			for(int k=max(0,dp[i-1][j]-d);k;k--){
				if(b[k+1][k+d]>=s){
					dp[i][j]=max(dp[i][j],k);
					break;//here
				}
			}
		}
		for(int j=1;j<=n;j++) c[j]=max(c[j-1],dp[i][j]);//here
		for(int j=1;j<=n;j++) if(dp[i][j]>=j-1) goto T3;
		cout<<i-1;
		return 0;
		T3:;
	}
	cout<<q;
}
```

---

## 作者：TonviaSzt (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P9180)

题目够清晰，没什么大意。

**思路分析**

$N\le 5000$，一眼区间dp。设 $f_{l,r}$ 表示区间 $[l,r]$ 最多进行几次操作。

```可以选择一个长度任意的前缀或后缀（可以为空），并删除它``` 指明区间 $[l,r]$ 的 $f$ 必然不超过任意一个子区间的 $f$（**性质1**）。所以基本地，有 $f_{l,r}\rarr f_{l+1,r},f_{l,r}\rarr f_{l,r-1}$。

考虑一次操作如何转移，由于 $f_{l,r}=\max(f_{l-1,r},f_{l,r+1})$，$f_{l,r}$ 最多加一。此时的操作编号 $p$ 为 $f_{l,r}+1$。

转移 $[l',r']\rarr[l,r]$ 必须满足 $(\min_{k={l-d_p}}^{l-1}a_k)\ge s_p$ 的限制，可以用 st 表维护。

在满足限制的情况下 $f_{l,r}=\max^{l-d_p}_{l'=1}f_{l',r}$，根据**性质1**，可以把 $\max$ 丢掉，$f_{l,r}=f_{l-d_p,r}+1$。

细节：注意一定要在前 $i$ 个操作都进行完才能进行下一个操作，所以初始时令 $f_{l,r}=-1,f_{1,n}=0$，只有合法的位置才能进行转移。

**Code**

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dec(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=5e3+5,Q=2e5+5;
int n,q,ans,a[N],d[Q],s[Q],st[N][15],f[N][N];
int find(int l,int r){
    int k=log2(r-l+1);
    return min(st[l][k],st[r-(1<<k)+1][k]);
}
int main(){
    // freopen("presuf.in","r",stdin);
    // freopen("presuf.out","w",stdout);
    scanf("%d%d",&n,&q);
    rep(i,1,n) scanf("%d",a+i),st[i][0]=a[i];
    rep(i,1,q) scanf("%d%d",d+i,s+i);
    rep(j,1,14) for(int i=1;i+(1<<j)-1<=n;i++) st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
    memset(f,-1,sizeof(f));f[1][n]=0;
    dec(len,n,1){
        rep(l,1,n+1-len){
            int r=l+len-1;
            if(f[l][r]==-1) continue;
            f[l+1][r]=max(f[l+1][r],f[l][r]);
            f[l][r-1]=max(f[l][r-1],f[l][r]);
            int nw=f[l][r]+1;
            if(nw>q) continue;
            if(find(l,l+d[nw]-1)>=s[nw]) f[l+d[nw]][r]=max(f[l+d[nw]][r],f[l][r]+1);
            if(find(r-d[nw]+1,r)>=s[nw]) f[l][r-d[nw]]=max(f[l][r-d[nw]],f[l][r]+1);
        }
    }
    rep(i,1,n) ans=max(ans,f[i][i-1]);
    printf("%d",ans);
}
```

---

## 作者：Lu_xZ (赞：2)

怎么都要优化的，来个白痴做法。

在钦定当前左端点位置，满足了几个要求下，显然右端点越远越好。

设 $f(i, p)$ 表示满足了 $i$ 个要求，左端点在 $p$ 时，最大的右端点。

设 $a(i, p)$ 大于等于 $p$ 的第一个位置 $j$ 满足 $[j, j + d_i)$ 全部 $\ge s_i$。

同理 $b(i, p)$ 表示小于等于 $p$ 的第一个位置满足 $(j - d_i, j]$ 全部 $\ge s_i$。

以上信息容易 $O(nq)$ 预处理，其中 $q \gets \min(q, n)$。

考虑第 $i$ 个要求是用前缀还是后缀满足的（转移方程省略第一维）：
$$
f(a(i, p) + d_i) \gets f(p),\ f(p) \gets b(i, f(p)) - d_i
$$

```cpp
#include<bits/stdc++.h>

using namespace std;

constexpr int N = 5005;

int n, q, x[N], a[N], b[N];
int f[2][N], o;

int main() {
	scanf("%d%d", &n, &q);
	q = min(q, n);
	for(int i = 1; i <= n; ++ i) {
		scanf("%d", x + i);
		f[0][i] = n;
	}
	for(int T = 1, d, s; T <= q; ++ T) {
		cin >> d >> s;
		for(int i = n, lst = n + 1, cnt = 0; i >= 1; -- i) {
			if(x[i] >= s) ++ cnt;
			else cnt = 0;
			if(cnt >= d) lst = i;
			a[i] = lst;
		}
		for(int i = 1, lst = 0, cnt = 0; i <= n; ++ i) {
			if(x[i] >= s) ++ cnt;
			else cnt = 0;
			if(cnt >= d) lst = i;
			b[i] = lst;
		}
		o ^= 1;
		memset(f[o], -1, sizeof f[o]);
		for(int i = 1; i <= n; ++ i) {
			if(a[i] + d <= n) f[o][a[i] + d] = max(f[o][a[i] + d], f[o ^ 1][i]);
			if(f[o ^ 1][i] >= i) {
				f[o][i] = max(f[o][i], b[f[o ^ 1][i]] - d);
			}
		}
		int t = 0;
		for(int i = 1; i <= n; ++ i) {
			if(f[o][i] >= i - 1) {
				t = 1;
				break;
			}
		}
		if(!t) return cout << T - 1, 0;
	}
	cout << q;
	return 0;
}
```

---

## 作者：Phobia (赞：2)

首先，这个 $q$ 的数据范围是胡扯的，显然至多 $n$ 次后原序列就被删空了，所以先将 $q$ 和 $n$ 取 $\min$。

其次，操作前删除前缀或后缀一定要对当前操作有帮助，不然你删他干嘛？

考虑 dp 求解，定义 $f[i][j][k]$ 表示第 $i$ 次操作前，能否保留区间 $[j,k]$，转移时贪心的选择最左端满足条件和最右段满足条件的。

直接求解是 $O(n^3)$ 的，但注意到对于两个状态 $f[i][j][k_1]$ 和 $f[i][j][k_2](k_1\leq k_2)$，贪心的想显然是第二个更优，所以改变状态为 $f[i][j]$ 表示第 $i$ 次操作前左端点保留 $j$，右端点的最大值是多少。

时间复杂度 $O(n^2)$，空间滚一下后做到 $O(n)$。

~~~cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 5005;

int a[maxn], n, q;

int pre[maxn], suf[maxn], f[2][maxn]; // pre 存前缀 i 最后一个满足条件的右端点，suf 存后缀 i 最后一个满足条件的右端点。 

int read()
{
	int res = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		;
	for (; isdigit(ch); ch = getchar())
		res = (res << 3) + (res << 1) + (ch & 15);
	return res;
}

int main()
{
	n = read(), q = min(n, read());
	for (int i = 1; i <= n; ++i)
		a[i] = read();

	f[1][1] = n;
	for (int i = 1; i <= q; ++i)
	{
		int d = read(), s = read();
		
		pre[0] = 0;
		for (int j = 1, k = 0; j <= n; ++j)
		{
			k = (a[j] >= s ? k + 1 : 0);
			pre[j] = (k >= d ? j : pre[j - 1]);
		}
		suf[n + 1] = n + 1;
		for (int j = n, k = 0; j >= 1; --j)
		{
			k = (a[j] >= s ? k + 1 : 0);
			suf[j] = (k >= d ? j : suf[j + 1]);
		}
		
		bool ok = 0; // ok 存能否转移成功 
		memset(f[i + 1 & 1], 0, sizeof(f[i + 1 & 1]));
		for (int j = 1; j <= n; ++j)
		{
			if (suf[j] + d - 1 <= f[i & 1][j])
			{
				ok = 1;
				f[i + 1 & 1][suf[j] + d] = max(f[i + 1 & 1][suf[j] + d], f[i & 1][j]);
			}
			if (pre[f[i & 1][j]] - d + 1 >= j)
			{
				ok = 1;
				f[i + 1 & 1][j] = max(f[i + 1 & 1][j], pre[f[i & 1][j]] - d);
			}
		}
		if (!ok) // 不能转移，那就赶紧结束，别浪费时间 
		{
			printf("%d\n", i - 1);
			return 0;
		}
	}
	printf("%d\n", q); 
	return 0;
}
~~~

---

## 作者：hnczy (赞：1)

这题很好的 dp 题。

首先我们知道这个 $q$ 数据范围明显是诈骗的，最多就跟 $n$ 同阶。

那我们的复杂度就大概是 $O(n^2)$ 。

很明显使用 dp 来实现这个过程的，设一个 $dp_{i,l,r}$ 表示在第 $i$ 次中这个区间为 $l\sim r$ 是否可能，这个大概是一个 $O(n^4)$ 的时间复杂度。

考虑优化，我们发现这个 dp 数组只存布尔值，这就很浪费了（当然这里很明显不能用 bitset )，很容易想到在第 $i$ 次操作中 $r$ 越大越优，那我们只需存一个 $dp_{i,l}$ 表示最大的右端点即可。

那我们分别考虑左边的转移和右边的转移。

对于左边的转移很简单，$$dp_{i,j} = \max_{l\in [1,j-d], \min_{j-d-1\sim j-1}\ge s}(dp_{i-1,l}) $$，这里可以用一个前缀最值来实现。可以优化到 $O(n)$。

而右边的转移 $dp_{i,j} = \max_{r\in [j,dp_{i-1,j}-d] , min_{r+1\sim r+d+1}\ge s}(r) $，这个优化其实也不难，观察到它取的是一个 $\min_{r+1\sim r+d+1}$，我们可以再搞一个数组 $h_r$，表示原来以 $r$ 为右端点，最大的值 $h_r$ 能让 $l \sim r$ 转移到 $l\sim h_r$。这个是一个很简单的 dp，不赘述了。

总体的时间复杂度 $O(n^2)$。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int f[N][N],n,q,a[N],mi[N][N];
int pre[N],h[N];
//表示第i次操作,左端点为 l 的最大的 
signed main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++){
		mi[i][i]=a[i];
		for(int j=i+1;j<=n;j++)
			mi[i][j]=min(mi[i][j-1],a[j]);
	}
	f[0][1]=n;
	int i=1;
	for(int d,s,sum=0;i<=n;i++){
		scanf("%d%d",&d,&s);//长度和最小值 
		sum+=d;
		if(sum>n)break;
		for(int l=1,c=0;l<=n;l++){
			pre[l]=max(f[i-1][l],pre[l-1]);
			a[l]>=s?c++:c=0;
			h[l]=c>=d?l-d:h[l-1];
		}
		for(int l=1;l<=n;l++){
			f[i][l]=-0x3f3f3f3f;
			if(l-d>=1 && mi[l-d][l-1]>=s)	
				f[i][l]=max(f[i][l],pre[l-d]);
			//左边的删掉 
			if(pre[l]>=l && h[pre[l]]>=l)
				f[i][l]=max(f[i][l],h[pre[l]]);
		}
		bool op = false;
        for (int l = 1; l <= n && !op; ++l)
            op |= f[i][l] >= l-1 ;
        if (!op) break;
	}
	//f_{i,j} = max(f_{i-1,l}) l\in [1,j-d]^mi[j-d-1,j-1]>=s
	//f_{i,j} = max(r) r\in [j,f_{i-1,j}-d]^mi[r+1,r+d+1]>=s
	cout<<i-1;
	return 0;
	
}

```

---

## 作者：XuYueming (赞：1)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P9180)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18536522)。

## 题意简述

一个长为 $n$ 的序列 $\{a_n\}$ 和 $q$ 次操作，第 $i$ 次操作中，你可以删除序列长为 $d_i$ 的前缀或后缀，并需要保证删除的所有数 $\geq s_i$。每次操作前，你可以选择任意长度的前缀或后缀，并将其删除，也可以不操作。请问，在你不能进行下一次操作前，你最多能执行多少次操作？

$n \leq 5 \times 10^3$，$q \leq 2 \times 10^5$。

## 题目分析

$n$ 的范围提示我们考虑 $\mathcal{O}(n^2)$，进而发现 $q$ 的范围在诈骗——至多进行 $q$ 次操作后序列会被删空。所以，在算法开始前 $q \gets \min \{n, q\}$，让 $n, q$ 同阶。

$n, q$ 范围这么小，应该不是贪心，那就应该是 DP 了。我们很容易想到，$f_{i, l, r}$ 表示在前 $i$ 次操作后，能不能使序列只剩下 $[l, r]$。边界显然是 $f_{0, 1, n} = \text{true}$，统计答案考虑第 $i$ 次操作后，倘若 $f_{i, l, r}$ 均为 $\text{false}$，则说明最多进行 $i - 1$ 次操作。然后考虑转移。

转移其实就是进行某一次操作。找到一对使 $f_{i-1,l,r}=\text{true}$ 的 $[l, r]$，在这个区间上，我们尝试删去一段前缀或一段后缀。考虑前缀，后缀同理。我们枚举一个 $k$，表示删除 $[l, k-1]$ 后，满足 $k+d-q\leq r$ 并且 $\min\limits_{i=k}^{k+d-1}a_i \geq s$，剩下区间为 $[k+d, r]$。如果 $k+d\gt r$，则说明这次操作后会将序列删空，但是依然可以进行第 $i$ 次操作。注意到，对于一对 $[l, r]$，我们只需要转移最小的合法的 $k$，同样能进行一次操作的前提下，删的数越少明显不劣，这是一个常数优化。

其中，区间最小值可以在转移的时候用单调队列维护，但是没必要，$\mathcal{O}(n^2)$ 预处理即可。上述算法的时间复杂度为 $\Theta(qn^3)$，需要优化。

遇到记录的是布尔值的 DP，往往有两种思考方向：使用 `bitset` 压位转移；考虑贪心后记录状态的最值。前者显然不适用本题，解释一下后者。对于具有相同左端点的区间 $[l, r_1]$ 和 $[l, r_2]$，倘若均有 $f_{i,l,r_1}=f_{i,l,r_2}=\text{true}$，那么较大的那个 $r$ 显然是不劣的，因为有更多的数保留下来，以后可能会用到。因此考虑舍弃原先的布尔值，使用 DP 记录最大的 $r$，即 $f_{i,l}=r$ 表示在前 $i$ 次操作后，能够使序列只剩下 $[l, r]$ 的最大的 $r$。

优化后，状态数由 $\mathcal{O}(qn^2)$ 优化至 $\mathcal{O}(qn)$。考虑转移，记 $\operatorname{mi}(l, r) := \min\limits _ {i=l}^r \{a_i\}$。

1. 当前使用前缀。
    $$
    f_{i,l} = \max \Big\{f_{i-1,k} \mid k\in[1,l-d] \land \operatorname{mi}(l-d+1,l-1) \geq s\Big\}
    $$
1. 当前使用后缀。
    $$
    f_{i,l}=\max \Big\{r\mid\displaystyle r\in[l,f_{i-1,l}-d] \land \operatorname{mi}(r+1, r+d) \geq s\Big\}
    $$

朴素转移的话，时间是 $\mathcal{O}(qn^2)$。但是这个转移很有优化空间。第一种转移使用前缀最值优化即可；第二种转移翻译成人话，就是找到 $\leq f_{i-1,l}$ 的最后一个位置，使得以其为结尾的长度为 $d$ 的序列均 $\geq s$，于是可以预处理扫一遍，具体见代码。

于是时间可以优化至 $\mathcal{O}(nq)$，以及一些时空的常数优化，卡常后[最优解](https://www.luogu.com.cn/record/187699198)。

## 代码

包括部分分在内完整代码见[我的博客](https://www.cnblogs.com/XuYueming/p/18536522)。

```cpp
memcpy(g, f, sizeof(f));
for (int i = 1, c = 0; i <= n; ++i) {
    p[i] = max(p[i - 1], g[i]);
    a[i] >= s ? ++c : c = 0;
    h[i] = c >= d ? i - d : h[i - 1];
}
for (int l = 1; l <= n; ++l) {
    f[l] = -0x3f3f3f3f;
    if (g[l] >= l && h[g[l]] >= l)
        f[l] = max(f[l], h[g[l]]);
    if (l - d >= 1 && mi[l - d][l - 1] >= s)
        f[l] = max(f[l], p[l - d]);
}
```

---

## 作者：huangrenheluogu (赞：0)

容易想到 $f_{d,i,j}$ 表示第 $d$ 次，区间 $[i,j]$ 是否可以达到。发现对于 $\forall k\gt j$，$[i,k]$ 可以达到的条件可以推出 $[i,j]$ 可以达到。因此，不妨维护 $f_{d,i}$ 表示最大的 $p$，满足 $d$ 次操作之后，$[i,d]$ 可以被答案。

转移从后面转移和前面转移分类讨论即可。具体的，$pre_i$ 表示 $i$ 为开始右端点删掉之后会到那里，可以处理删除后缀的情况；维护前面函数的前缀最大值处理删除前缀的情况。

注意判断刚好删空区间的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5005;
int n, f[N], g[N], minn[N][N], q, d, s, tmp, a[N], pr[N];
int main(){
    // freopen("presuf.in", "r", stdin);
    // freopen("presuf.out", "w", stdout);
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++){
        scanf("%d", &minn[i][i]);
    }
    // for(int i = 1; i <= n; i++){
    //     minn[i][i] = a[i];
    // }
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            minn[i][j] = min(minn[i][j - 1], minn[j][j]);
        }
    }
    for(int i = 1; i <= n; i++){
        g[i] = n;
    }
    for(int dep = 1; dep <= q; dep++){
        scanf("%d%d", &d, &s);
        for(int i = 0; i <= n; i++) pr[i] = f[i] = -1;
        for(int i = d; i <= n; i++){
            if(minn[i - d + 1][i] >= s){
                pr[i] = i - d;
            }
            else pr[i] = pr[i - 1];
        }
        tmp = -1;
        for(int i = 1; i <= n; i++){
            if(g[i] > i - 1) f[i] = pr[g[i]];
            if(i > d && minn[i - d][i - 1] >= s){
                tmp = max(tmp, g[i - d]);
                f[i] = max(f[i], tmp);
            }
        }
        tmp = 0;
        for(int i = 1; i <= n; i++){
            f[i] = max(f[i], f[i - 1]);
        }
        for(int i = 1; i <= n; i++){
            // printf("f[%d][%d] = %d\n", dep, i, f[i]);
            g[i] = f[i], f[i] = -1;
            if(g[i] < i - 1) g[i] = -1;
            if(g[i] != -1) tmp = 1;
        }
        if(!tmp){
            printf("%d\n", dep - 1);
            return 0;
        }
    }
    printf("%d\n", q);
    return 0;
}
```

---

## 作者：DerrickLo (赞：0)

显然操作次数的上界是 $\min(q,n)$。

我们预处理出 $l_{i,j}$ 表示最小的 $k$ 使得 $[j,k)$ 中有连续 $d_i$ 个数 $\ge s_i$，$r_{i,j}$ 表示最大的 $k$ 使得 $(k,j]$ 中有连续 $d_i$ 个数 $\ge s_i$，这个可以 $\mathcal O(n^2)$ 求。

然后你发现题目转化为现在有两个数 $a$ 和 $b$，初始时 $a=1$，$b=n$。然后每次操作 $i$ 你可以将 $a\leftarrow l_{i,a}$ 或者 $b\leftarrow r_{i,b}$，并且你需要时刻保证 $a\le b+1$，问最多能操作多少次。

考虑 dp。记 $f_{i,j}$ 表示 $a$ 目前在 $i$，已经进行了 $j$ 次操作后，$b$ 的最大值。那么考虑主动转移：

$$f_{i,j+1}\leftarrow\max\{f_{i,j+1},r_{j+1,f_{i,j}}\}$$

$$f_{l_{j+1,i},j+1}\leftarrow\max\{f_{l_{j+1,i},j+1},f_{i,j}\}$$

答案就是最大的 $j$ 使得 $f_{i,j}\ge i-1$。时间复杂度 $\mathcal O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[5005],f[5005][5005],d[200005],s[200005],l[5005][5005],r[5005][5005],ans;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=q;i++)cin>>d[i]>>s[i];
	q=min(n,q);
	for(int i=1;i<=q;i++){
		int cnt=0;l[i][n+1]=n+2;
		for(int j=n;j;j--){
			if(a[j]<s[i])cnt=0;
			else cnt++;
			if(cnt>=d[i])l[i][j]=j+d[i];
			else l[i][j]=l[i][j+1];
		}cnt=0,r[i][0]=-1;
		for(int j=1;j<=n;j++){
			if(a[j]<s[i])cnt=0;
			else cnt++;
			if(cnt>=d[i])r[i][j]=j-d[i];
			else r[i][j]=r[i][j-1];
		}
	}
	memset(f,-1,sizeof f);
	f[1][0]=n;
	for(int i=1;i<=n;i++)for(int j=0;j<=q;j++){
		if(f[i][j]==-1)continue;
		f[i][j+1]=max(f[i][j+1],r[j+1][f[i][j]]);
		f[l[j+1][i]][j+1]=max(f[l[j+1][i]][j+1],f[i][j]);
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=q;j++)if(f[i][j]>=i-1)ans=max(ans,j);
	cout<<ans;
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

昨天模拟赛的题，开晚了没打，挂大分 qwq。

有一个显然的 $n^2q$ dp：设 $f_{i,j,k}$ 代表第 $i$ 个问题结束，现在能否剩下区间 $[j,k]$。

发现这个是存在性问题，有一个常见的优化是把一维放到状态里。一开始想的是把问题这一维放到状态里，发现没有办法快速转移。

所以考虑把左右端点中的一维压进去。令 $f_{i,j}$ 表示第 $i$ 个问题结束，左端点为 $j$ 时右端点最大值。如果此时不合法则 $f_{i,j}=-1$。判断答案就是看如果某一层 $i$，其中所有的 $f_{i,j}=-1$，那么 $i-1$ 就是最终答案。

考虑转移。第 $i$ 个问题肯定从第 $i-1$ 个问题转过来，转过来的方式肯定是删掉左边一段或者右边一段。

删掉左边一段很简单，先判断左边能否满足删除的条件，即 $[j-d_i,j-1]$ 这一段能否被删去，如果可以的话，转移有 $f_{i,j}=\max_{k=1}^{j-d_i}f_{i-1,k}$。这个可以用前缀最大值转移。

我们定义 $g_{i,j}$ 代表第 $i$ 个问题时选择取右边的一段，若右端点为 $j$ 则取完后最大的右端点。如果无法满足则有 $g_{i,j}=-1$。这个显然是可以 $O(nq)$ 预处理的。对于删掉右边一段，我们的答案显然是 $g_{i,f_{i-1,j}}$。

复杂度是 $O(nq)$ 的，都看得出来 $q$ 的范围顶多到 $n$，所以复杂度是 $O(n^2)$ 的。

会有问题，过不了第三个样例。原因是没有考虑刚好删完序列为空的情况，直接特判可以刚好删完的情况就好。

注意转移时的细节。

```cpp
#include <bits/stdc++.h>
//#define int long long
#define Rg register
#define Ri Rg int
#define Il inline
#define vec vector
#define pb push_back
#define fi first
#define se second
#define IT ::iterator

using namespace std;

typedef double db;
//typedef long long ll;
typedef pair<int,int> pii;
const int N=5000,Inf=1e9;
const db eps=1e-9;

int n,Q,a[N+5],d[N+5],s[N+5],f[N+5][N+5],g[N+5][N+5],mn[N+5][N+5];

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>Q;Q=min(n,Q);
	for(Ri i=1;i<=n;i++)cin>>a[i],mn[i][i]=a[i];
	for(Ri i=1;i<=n;i++)for(Ri j=i+1;j<=n;j++)mn[i][j]=min(mn[i][j-1],a[j]);
	for(Ri i=1;i<=Q;i++)cin>>d[i]>>s[i];
	memset(f,-1,sizeof(f));
	for(Ri i=1;i<=n;i++)f[0][i]=n;//初始化
	for(Ri i=1;i<=Q;i++){
		int cnt=0;g[i][0]=-1;
		for(Ri j=1;j<=n;j++){
			if(a[j]>=s[i])cnt++;
			else cnt=0;
			if(cnt>=d[i])g[i][j]=j-d[i];
			else g[i][j]=g[i][j-1];//预处理 g 数组
		}
	}
	for(Ri i=1;i<=Q;i++){
		int mx=-1;bool ok=0;//这一层能否转移到
		for(Ri j=1;j<=n;j++){
			if(~f[i-1][j]){//如果上一个状态合法
				if(g[i][f[i-1][j]]>=j)f[i][j]=g[i][f[i-1][j]];
				if(f[i-1][j]-j+1==d[i]&&mn[j][f[i-1][j]]>=s[i])f[i][j]=j-1;//特判
			}
			if(j>d[i]){//可以通过删左边转移
				mx=max(mx,f[i-1][j-d[i]]);//过程中处理前缀最大值
				if(mn[j-d[i]][j-1]>=s[i]&&mx>=j)f[i][j]=max(f[i][j],mx);//通过删左边转移
			}
			if(~f[i][j])ok=1;
		}
		if(!ok){cout<<i-1;return 0;}
	}
	cout<<Q;
	return 0;
}
```

---

