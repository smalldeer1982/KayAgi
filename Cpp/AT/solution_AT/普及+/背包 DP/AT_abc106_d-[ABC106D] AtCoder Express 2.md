# [ABC106D] AtCoder Express 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc106/tasks/abc106_d

高橋王国には, 東西にのびる $ 1 $ 本の線路がある. これに沿って $ N $ 個の都市があり, 西から順に都市 $ 1,\ 2,\ 3,\ \cdots,\ N $ と番号づけられている.  
 AtCoder Express という会社は $ M $ 本の列車を保有しており, 列車 $ i $ は都市 $ L_i $ から都市 $ R_i $ の区間 ($ L_i\ =\ R_i $ の場合もある) を走っている.

この王国の国王である高橋君は, $ Q $ 個のことに興味を持った. 具体的には, $ i=1,\ 2,\ 3,\ \dots,\ Q $ のときの以下の質問の答えを求めたくなった.

- 都市 $ p_i $ から都市 $ q_i $ までの区間に, 走る区間が **完全に含まれる** 列車の本数. 言い換えれば, $ p_i\ \leq\ L_j $ と $ R_j\ \leq\ q_i $ が両方成り立つような列車 $ j $ の本数.

高橋君は天才である. しかし流石の彼でも, 膨大なデータを処理することはできない. 高橋君のために, $ Q $ 個の質問それぞれに対して答えを求めよ.

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 500 $ 以下の整数
- $ M $ は $ 1 $ 以上 $ 200\ 000 $ 以下の整数
- $ Q $ は $ 1 $ 以上 $ 100\ 000 $ 以下の整数
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ M) $
- $ 1\ \leq\ p_i\ \leq\ q_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ Q) $

### Sample Explanation 1

全ての列車の走る区間が, 都市 $ 1 $ から都市 $ 2 $ までの区間に含まれているので, この質問の答えは $ 3 $ となる.

### Sample Explanation 2

$ 1 $ 個目の質問は, 都市 $ 1 $ から $ 7 $ までの区間についてである. その区間に走る区間が完全に含まれている列車は, 列車 $ 1 $ のみである. $ 2 $ 個目の質問は, 都市 $ 3 $ から $ 10 $ までの区間についてである. その区間に走る区間が完全に含まれている列車は, 列車 $ 3 $ のみである.

## 样例 #1

### 输入

```
2 3 1
1 1
1 2
2 2
1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
10 3 2
1 5
2 8
7 10
1 7
3 10```

### 输出

```
1
1```

## 样例 #3

### 输入

```
10 10 10
1 6
2 9
4 5
4 7
4 7
5 8
6 6
6 7
7 9
10 10
1 8
1 9
1 10
2 8
2 9
2 10
3 8
3 9
3 10
1 10```

### 输出

```
7
9
10
6
8
9
6
7
8
10```

# 题解

## 作者：qwerty12346 (赞：9)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc106_d)

## 题意

这题就是求有多少个给定的数对 $(i,j)$ 满足 $l \leq i$ 且 $i \leq r$。

## 思路

直接用区间 $dp$，求 $dp_{p,q}$。

## 状态定义

$dp_{i,j}$ 表示城市 $i$ 到 城市 $j$ 的列车数量。

## 状态转移方程

要求 $i$ 到 $j$ 的区间，那我们就直接加上 $i$ $+$ $1$ 到 $j$ 的区间再加上 $i$ 到 $j$ $-$ $1$ 的区间，然后我们就能发现重复了一部分，而那部分就是 $i$ $+$ $1$ 到 $j$ $-$ $1$ 的区间。那么状态转移方程就是 $dp_{i,j}+=dp_{i+1,j}+dp_{i,j-1}-dp_{i+1,j-1}$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y,a[1000005],b[1000005],f[1005][1005];//定义dp数组
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
    {
	cin>>a[i]>>b[i];
	f[a[i]][b[i]]++;
    }
    for(int i=n;i>=1;i--)for(int j=1;j<=n;j++)f[i][j]+=f[i+1][j]+f[i][j-1]-f[i+1][j-1];//状态转移方程
    for(int i=1;i<=k;i++)
    {
	cin>>x>>y;
	cout<<f[x][y]<<endl;
    } 
    return 0;
}
```


---

## 作者：Walter_Fang (赞：7)

区间 DP 。

跳脱出平常的思路，我们用 $a_{i,j}$ 记录恰好以第 $x$ 个城市为起点并且以第 $y$ 个城市为终点的高铁数量,并用 $dp_{x,y}$ 表示在第 $x$ 个城市和第 $y$ 个城市间存在的高铁数量。

接下来到保留节目：动态转移方程的推导。

被 $dp_{x+1,y}$ 或 $dp_{x,y-1}$ 包含或者经过城市 $x$ 和城市 $y$ 的地铁一定被 $dp_{x,y}$ 包含。

被 $dp_{x+1,y-1}$ 包含的地铁一定被 $dp_{x+1,y}$ 和 $dp_{x,y-1}$ 包含。


因此动态转移方程如下： `dp[i][j]=dp[i+1][j]+dp[i][j-1]+a[i][j]-dp[i+1][j-1];`

代码（感觉解析里说的蛮清楚了，注释就不写了）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T,i,j,x,y,dp[510][510],a[510][510];
int main(){
    cin>>n>>m>>T;
    for(i=1;i<=m;i++)cin>>x>>y,a[x][y]++;
    for(i=n;i>=1;i--)
    	for(j=i;j<=n;j++)
    		dp[i][j]=dp[i+1][j]+dp[i][j-1]+a[i][j]-dp[i+1][j-1];
    while(T--)cin>>x>>y,cout<<dp[x][y]<<'\n';
}
```

求过审qwq

---

## 作者：fengenrong (赞：5)

这题就是道区间动态规划的题目，根据题目可知它的询问次数很多，所以不能暴力，只能使用动态规划。我们可以定义 $f(i,j)$ 表示在 $i$ 到 $j$ 所含有的列车（初始时都是 $0$），则动态转移方程为：
$$f(i,j)=f(i,j-1)+\sum_{k=i}^{j}a(k,j)$$

在每一次询问时输出 $f(x,y)$ 就行了。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, q, a[1005][1005], dp[1005][1005];
int x, y;
signed main() {
    scanf("%lld%lld%lld", &n, &m, &q);
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        a[x][y]++;//统计
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = dp[i][j - 1];
            for (int k = i; k <= j; k++) {
                dp[i][j] += a[k][j];//利用动态转移方程
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        scanf("%lld%lld", &x, &y);//询问
        printf("%lld\n", dp[x][y]);直接输出
    }
    return 0;
}
```

---

## 作者：Ggsddu_zzy (赞：5)


> upd：2023 05 07：修改了一处代码错误

[题目传送门](https://www.luogu.com.cn/problem/AT_abc106_d)

[更好的阅读体验](https://www.cnblogs.com/zzyblog0619/p/17368247.html)



#### 解题思路

区间 $dp$。

划分阶段：以左右城市之间的列车数量为阶段。

状态表达：设 $f_{i,j}$ 为城市 $i$ 与城市 $j$ 之间的列车数量。

状态转移：

![](https://cdn.luogu.com.cn/upload/image_hosting/q5o8dm4w.png?x-oss-process=image/resize,m_lfit,h_5200,w_520)

由图可知，城市 $l$ 与城市 $r$ 之间的列车数量，就是城市 $l$ 与城市 $r-1$ 之间的列车数量与城市 $l+1$ 与城市 $r$ 之间的列车数量（蓝色括号）加上刚好从城市 $l$ 到城市 $r$ 的列车数量，但是还有一个重合部分，也就是城市 $l+1$ 与城市 $r-1$ 之间的列车数量（橙色方框）。

所以，城市 $l$ 与城市 $r$ 之间的列车数量就等于城市 $l$ 与城市 $r-1$ 之间的列车数量与城市 $l+1$ 与城市 $r$ 之间的列车数量减去城市 $l+1$ 与城市 $r-1$ 之间的列车数量加上刚好从城市 $l$ 到城市 $r$ 的列车数量。

即：
$$
f_{i,j}=f_{i,j}+f_{i,j-1}+f_{i+1,j}-f_{i+1,j-1}
$$
初始状态：预处理出刚好从城市 $i$ 到城市 $j$ 的列车数量；即：`f[l[i]][r[i]]++;`。

求解目标：$f_{p,q}$；

#### 代码

[AC 记录](https://www.luogu.com.cn/record/108214537)

```c++
#include<bits/stdc++.h>
#define ri register int
using namespace std;
int n,m,q; 
int l[200005],r[200005],f[505][505];
int main(){
	cin>>n>>m>>q;
	for(ri i=1;i<=m;i++){
		cin>>l[i]>>r[i];
		f[l[i]][r[i]]++;
	}
	for(ri i=n;i>=1;i--)//因为 f[i][j] 是由 f[i+1][j] 得来，所以要从 n 到 1 枚举 
		for(ri j=1;j<=n;j++)
			f[i][j]+=f[i+1][j]+f[i][j-1]-f[i+1][j-1];
	while(q--){
		int u,v;
		cin>>u>>v;
		cout<<f[u][v]<<'\n';
	} 
	return 0;
}
```



---

## 作者：what_can_I_do (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT_abc106_d)

首先想到先预处理所有 $l$ 和 $r$ 的答案。

刚开始想到的是对于每一个 $l$，$r$，可以求出排除掉左端点在 $1$ 到 $l-1$ 的区间的区间数和排除掉右端点在 $r+1$ 到 $n$ 的区间的区间数，最后用这两个区间数的和减去总数 $m$ 即可得到答案，因为这么算的话相当于左端点在 $1$ 到 $l-1$ 的区间数和右端点在 $r+1$ 到 $n$ 的区间数被算了一次，中间的也就是我要求的区间数被算了两次，减去总数就会把每个部分都消掉一次，最后我们要求的区间的区间数就只被算了一次。

但是这么想其实是错的，因为这样子做遗漏了一种区间，这种是包含了要求的区间 $l$ 到 $r$ 的。在计算的时候这种区间比较特殊，它既是属于左端点在 $1$ 到 $l-1$ 的区间，又是属于右端点在 $r+1$ 到 $n$ 的区间，所以它在做加法的过程中不会被算，却在做减法的过程中被计算，所以现在还需加上这样的一种区间的数量。

于是我就有了一种奇怪的处理方式：使用优先队列，关键字为右端点，从小到大，如果一个区间左端点小于 $l$ 就入队，在后面枚举 $r$ 的时候如果这个区间右端点小于等于 $r$ 的就出队，统计目前还在队内的数量。但是这么做跑的很慢，还得优化。

其实很容易发现，使用优先队列的原因是因为不保证区间右端点有序，所以只需要先对于所有区间按照右端点从小到大排序，后面处理时就可以直接按照顺序取出区间右端点扔进 vector 里，在用一个变量表示目前属于这种特殊区间的在取出的右端点序列中下标最靠前的下标，因为这么做可以很方便地去除右端点已经小于等于 $r$ 的区间的数量。

最后询问时直接输出对应的区间的答案即可。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,q;
int l[200010],r[200010];
int ql[100010],qr[100010];
int vl[510],vr[510];
int ans[510][510];
vector<int> v;
struct aaa
{
	int lll,rr;
}a[200010];
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		vl[l[i]]++,vr[r[i]]++;
		a[i].lll=l[i],a[i].rr=r[i];
	}
	for(int i=1;i<=n;i++) vl[i]+=vl[i-1],vr[i]+=vr[i-1];
	sort(a+1,a+m+1,[](aaa x,aaa y){return x.rr<y.rr;});
	for(int i=1;i<=n;i++)
	{
		int sum=m-vl[i-1],tot=0,ss=0;
		for(int j=1;j<=m;j++)
			if(a[j].lll<i) v.push_back(a[j].rr),tot++;
		for(int j=i;j<=n;j++)
		{
			int s=m-(vr[n]-vr[j]);
			while(1)
			{
				if(ss>=tot) break;
				if(v[ss]>j) break;
				ss++;
			}
			ans[i][j]=s+sum-m+tot-ss;
		}
		v.clear();
	}
	while(q--)
	{
	    int l,r;
	    scanf("%d%d",&l,&r);
	    printf("%d\n",ans[l][r]);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

## 分析

对于求满足 $l \le i \le j \le r$ 的二元组 $(i,j)$ 数量，很容易想到二分。我们先用二分求出对于所有的 $(i,j)$，满足 $l \le i \le r$ 的区间。最终的答案就是在这个区间里面 $l \le j \le r$ 的数量。

很显然，我们是无法二分 $j$ 的，因为同一组 $(i,j)$ 是有依赖性，也就是保序 $i$ 后，$j$ 是无法保序的。考虑使用其它方法维护答案。

对于求区间答案，不难想到莫队。对于指针的每次移动，我们可用一棵树状数组更新数量。而在指针移动完之后，该询问的答案就可以直接用树状数组求得 $j \le r$ 的数量了。在这里，为了减小复杂度，我们可以对 $(i,j)$ 合并一下相同项。这样的话在用树状数组更新数量时就可能不是 $1$，而是更新的 $(i,j)$ 的出现次数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
#define re register 
const int N=1e6+10,M=1e4+10;
int n,m,q;
struct node{
	int l,r,cnt;
}c[N],c1[N];
int cidx;
struct node2{
	int p,q;
}Q[N];
struct node3{
	int l,r,id,k;
}Q2[N];
int ANS[N],idx,len;
int tr[M];//树状数组 
inline bool cmp(node a,node b){
	return ((a.l!=b.l)?(a.l<b.l):(a.r<b.r));
}
inline bool cmp2(node3 a,node3 b){
	if(a.l/len!=b.l/len) return a.l<b.l;
	if((a.l/len)&1) return a.r<b.r;
	return a.r>b.r;
}
inline int find1(int l,int r,int x){
	int ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(c1[mid].l>=x) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
inline int find2(int l,int r,int x){
	int ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(c1[mid].l<=x) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
inline void insert(int x,int y){
	while(x<=n+10) tr[x]+=y,x+=x&(-x);
}
inline int query(int x){
	int ans=0;
	while(x) ans+=tr[x],x-=x&(-x);
	return ans;
}
inline void read(){
	scanf("%lld%lld%lld",&n,&m,&q);
	for(re int i=1;i<=m;++i)
		scanf("%lld%lld",&c[i].l,&c[i].r);
	for(re int i=1;i<=q;++i)
		scanf("%lld%lld",&Q[i].p,&Q[i].q);
	return ;
}
inline void solve(){
	sort(c+1,c+m+1,cmp);
	int last=1;
	for(re int i=2;i<=m+1;++i)//合并相同项 
		if(c[i].l!=c[i-1].l||c[i].r!=c[i-1].r) c1[++cidx]={c[i-1].l,c[i-1].r,last},last=1;
		else ++last;
	for(re int i=1;i<=q;++i){//二分查找i的区间 
		int where=find1(1,cidx,Q[i].p);
		int where2=find2(where,cidx,Q[i].q);
		if(where>where2||where<1||where2<1) ANS[i]=0;
		else Q2[++idx]={where,where2,i,Q[i].q};
	}
	len=sqrt(idx);
	sort(Q2+1,Q2+idx+1,cmp2);
	int l=1,r=0;
	for(re int i=1;i<=idx;++i){//莫队 
		while(l>Q2[i].l) --l,insert(c1[l].r,c1[l].cnt);
		while(r<Q2[i].r) ++r,insert(c1[r].r,c1[r].cnt);
		while(l<Q2[i].l) insert(c1[l].r,-c1[l].cnt),++l;
		while(r>Q2[i].r) insert(c1[r].r,-c1[r].cnt),--r;
		ANS[Q2[i].id]=query(Q2[i].k);
	}
	for(re int i=1;i<=q;++i)
		printf("%lld\n",ANS[i]);
	return ;
}
signed main(){
	read(),solve();return 0;
}
```


---

## 作者：xibaohe (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc106_d)

# 题目大意
有一条东西走向的铁路和 $N$ 个城市，有 $M$ 列火车，每列火车从 $\mathit{L}_{i}$ 运行到 $\mathit{R}_{i}$，问在在城市 $\mathit{p}_{i}$ 和城市 $\mathit{q}_{i}$ 之间运行的列车数量。

# 题目思路
由于每列火车的运行路段和所给出的城市 $\mathit{p}_{i}$ 和城市 $\mathit{q}_{i}$ 恰似区间，因此我们可以尝试用区间 $dp$ 来解决这道题。

#### $\mathit{a}_{i,j}$ 表示恰好以第 $i$ 个城市为起点并且以第 $j$ 个城市为终点的高铁数量。
#### $\mathit{dp}_{i,j}$ 表示在第 $i$ 个城市和第 $j$ 个城市间存在的高铁数量。

# 状态转移
接下来进入状态转移方程的推导：
 - 如果一条高铁被 $\mathit{dp}_{x+1,y}$ 所包含，那么它**一定**被 $\mathit{dp}_{x,y}$ 所包含。
 - 如果一条高铁被 $\mathit{dp}_{x,y-1}$ 所包含，那么它**一定**被 $\mathit{dp}_{x,y}$ 所包含。
 - 如果一条高铁被 $\mathit{dp}_{x+1,y-1}$ 所包含，那么它**一定**被 $\mathit{dp}_{x,y-1}$ **和** $\mathit{dp}_{x+1,y}$ 所包含。
 - 如果一条高铁恰好经过城市 $x$ 和城市 $y$，那么它**也**被 $\mathit{dp}_{x,y}$ 所包含。
 
由如上三条我们可以推出 $\mathit{dp}_{x,y}$ 可以由 $\mathit{dp}_{x,y-1}$ 和 $\mathit{dp}_{x+1,y}$ 相加得来。但由于 $\mathit{dp}_{x+1,y-1}$ 被 $\mathit{dp}_{x,y-1}$ 和 $\mathit{dp}_{x+1,y}$ 共同包含，因此我们要减去 $\mathit{dp}_{x+1,y-1}$。

可以推出如下状态转移方程：
```cpp
dp[i][j]=dp[i+1][j]+dp[i][j-1]+a[i][j]-dp[i+1][j-1]
```
# 满分代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<map>
#include<string>
#include<vector>
#include<cfloat>
using namespace std;
int n,m,q,dp[2505][2505],a[2505][2505];
int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++)
    {
    	int l,r;
    	cin>>l>>r;
    	a[l][r]++;
    }//输入部分结束 
    for(int i=n;i>=1;i--)//由于dp[i][j]由dp[i+1][j]推来，因此i要倒序枚举 
    {
    	for(int j=i;j<=n;j++)//由于dp[i][j]由dp[i][j-1]推来且j大于等于i，因此j要正序从i开始枚举 
    	{
    		dp[i][j]=dp[i+1][j]+dp[i][j-1]+a[i][j]-dp[i+1][j-1];//状态转移方程 
    	}
    }
    while(q--)//处理询问部分 
    {
    	int x,y;
    	cin>>x>>y;
    	cout<<s[x][y]<<endl;
    }//输出部分结束，程序结束 
    return 0;
}
```



---

## 作者：FelFa_1414666 (赞：2)

可以考虑**区间 dp**

- $dp_{l,r}$ 表示闭区间 $[l,r]$ 内的区间数。

根据容斥得出递推式

$$dp_{l,r}=dp_{l+1,r}+dp_{l,r-1}-dp_{l+1,r-1}$$

初始时记录在 dp 数组上记录以下所有区间，然后按 $r-l$ 从小到大逐层转移。

每次询问直接输出 $dp_{l,r}$ 即可。

- 时间复杂度：$\operatorname O(n^2+m+q)$
- 空间复杂度：$\operatorname O(n^2)$

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
int n,m,q,l,r,dp[505][505];
int main()
{
	cin>>n>>m>>q;
	for(int i=0;i<m;i++)
	{
		cin>>l>>r;
		dp[l-1][r-1]++;
	}
	for(l=1;l<n;l++)
		for(int i=0;i+l<n;i++)
		{
			int j=i+l;
			dp[i][j]+=dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
		}
	while(q--)
	{
		cin>>l>>r;
		cout<<dp[l-1][r-1]<<endl;
	}
	return 0;
}
```



---

## 作者：Notch810 (赞：2)

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1001][1001],b[1001][1001];
int main()
{
	int n,m,q,l,r,i,j;
	cin>>n>>m>>q;
	for(i=1;i<=m;i++)
	{
		cin>>l>>r;
		b[l][r]++;
	}
    for(i=n;i>=1;i--)
    {
    	for(j=1;j<=n;j++)
    	{
    		a[i][j]=a[i+1][j]+a[i][j-1]-a[i+1][j-1]+b[i][j];
		}
	}
	for(i=1;i<=q;i++)
	{
		cin>>l>>r;
		cout<<a[l][r]<<endl;
	}
	return 0;
}
```
主要用了动态规划，左边加右边减重复就等于长度。

---

## 作者：Nazale_ (赞：1)

大致题意：给定 $Q$ 个询问点对 $(x,y)$ ，求给定的 $m$ 个点对 $(l_i,r_i)$ 中有多少个满足 $l_i \geq x $ 且 $r_i \leq y$ 。

很显然的一个二维偏序问题，考虑二维数点。值得注意的是这里找的应是以 $(x,y)$ 为左上角端点，一直向右扩展的矩形，所以从右向左做扫描线，树状数组维护竖着的一维就好了。

复杂度是 $O((n+m) \log n)$ 的，本题不算特别优秀，但思路是值得借鉴和推广的。

参考代码如下：


```
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define INF 1e10
#define eb emplace_back
#define pb push_back
#define ls (u<<1)
#define rs ((u<<1)|1)
#define lowbit(x) (x&(-x))
#define pii pair<int,int> 
#define fi first
#define se second
using namespace std;
const int maxn=505;
const int maxm=2e5+5;
const int mod=1e9+7;
int n,m,Q,ans[maxm];
struct node{
	int l,r;
	friend bool operator<(node x,node y){
		return x.l<y.l;
	}
}a[maxm];
struct ques{
	int y,id,op;
};
vector<ques> q[maxn];
struct BIT{
	int c[maxn];
	void add(int x,int k){
		while(x<=501){
			c[x]+=k;
			x+=lowbit(x);
		}
	}
	int qry(int x){
		int ans=0;
		while(x){
			ans+=c[x];
			x-=lowbit(x);
		}
		return ans;
	}
}bit;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>Q;
	for (int i=1;i<=m;i++){
		cin>>a[i].l>>a[i].r;
	}
	sort(a+1,a+1+m);
	for (int x,y,i=1;i<=Q;i++){
		cin>>x>>y;
		q[501].eb((ques){y,i,-1});
		q[x].eb((ques){y,i,1});
	}
	int lst=m;
	for (int i=501;i;i--){
		while(a[lst].l>=i){
			bit.add(a[lst].r,1);
			lst--;
		}
		for (int j=0;j<q[i].size();j++){
			int y=q[i][j].y,op=q[i][j].op,id=q[i][j].id;
			ans[id]+=bit.qry(y)*op;
		}
	}
	for (int i=1;i<=Q;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：Orange_qwq (赞：1)

[洛谷题目](https://www.luogu.com.cn/problem/AT_abc106_d) && [AT 链接](https://atcoder.jp/contests/abc106/tasks/abc106_d)

去年 11 月写的，感觉挺好想的。（当然有可能是因为去年 11 月的时候刚 CSP 完，脑子特别乱然后想到了很多东西，想到了学长说他考场上写的暴力 Floyd）

思路很简单，关键在于会不会表示。

## 思路

首先一看题目。$N$ 挺小，$M$ 很大。

然后理解一下题意。题目大意为：有 $M$ 条线段，要求某一区间内的线段总数。

接着就开始想了。~~这个屑想到了按点排序，想到了前缀和，然后发现前缀和假了，又想到了 CSP 考场上树状数组写炸了，又奇奇怪怪地结合前缀和假了否定了树状数组，~~ 想起了学长说他写了个 Floyd，想起了 Floyd 用矩阵存图，下标表示起点和终点。题目中的 $N$ 还很小……这道题不也可以用一个二维数组，用下标表示起点和终点吗？

为什么要这么想呢？以下是这个屑的思路，应该是没错的：

+ 如果按线段的端点排序，还得一个一个遍历另一个端点，看是否符合要求。
+ 左端点和右端点分别前缀和假了。
+ 分别前缀和都假了，没有想到树状数组要往哪里使。
+ 找线段看起来会超时。（但是后来看到题解区有大佬好像是找线段的，这个屑不太理解）

于是我们发现这一条线段要缩成一个点。我们把他转移到平面。

问题变成了：有 $M$ 个点，要求某一块区域内点的个数。

这样解法就很显然了，二维差分！

我们把每一条线段缩成点存到二维数组里去，每次查询时就能做到 $O(1)$ 得到答案，总时间复杂度 $O(N^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define M 200010
int n, m, q, l, r, sum[510][510];
int main() {
	scanf("%d %d %d", &n, &m, &q);
	for (int i = 1; i <= m; ++i) scanf("%d %d", &l, &r), sum[l][r] ++;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) 
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	while (q--) {
		int pi, qi;
		scanf("%d %d", &pi, &qi);
		printf("%d\n", sum[qi][qi] - sum[pi - 1][qi] - sum[qi][pi - 1] + sum[pi - 1][pi - 1]);
	}
	return 0;
}
```


---

## 作者：Nightingale_OI (赞：1)

### 大意

有 $ m $ 条线段，每条为 $ [ l_i , r_i ] $ 。

给你 $ q $ 次讯问，每次问被 $ [ p_i , q_i ] $ 包含的线段有多少个。

### 思路

考虑从大向小枚举线段左端点  $ l_i $ ，并在数组上增加右端点 $ r_i $ 出现次数 $ appear_{r_i} $ 。

同时从大向小枚举讯问左端点 $ p_i $ ，当目前的 $ l_i < p_i $ ，记录答案为：

$$ \sum_{i=1}^{q_i} appear_i $$

前缀和用树状数组维护即可。

注意先记录答案再在数组上增加出现次数。

时间复杂度 $ O(m \log_2 n + q \log_2 n) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
const int mo=1e9+7;
struct lrc{
    int l,r,c;
}a[202020],b[101010];
int c[505],d[101010];
void add(int x,int v){
    for(register int i=x;i<=n;i+=(-i&i))c[i]+=v;
}
int sum(int x){
    int re=0;
    for(register int i=x;i;i-=(-i&i))re+=c[i];
    return re;
}
bool cmp(lrc a,lrc b){
    return a.l>b.l;
}
int main(){
    cin>>n>>m>>s;
    f(i,1,m)scanf("%d %d",&a[i].l,&a[i].r);
    f(i,1,s)scanf("%d %d",&b[i].l,&b[i].r);
    f(i,1,s)b[i].c=i;
    sort(a+1,a+m+1,cmp);
    sort(b+1,b+s+1,cmp);
    f(i,1,s){
        while(l<m && a[l+1].l>=b[i].l)add(a[++l].r,1);
        d[b[i].c]=sum(b[i].r);
    }
    f(i,1,s)printf("%d\n",d[i]);
    return 0;
}
```

---

## 作者：μηδσ (赞：1)

## Definition

一个$n$表示所有区间的$l$和$r$都在这个区间$1-n$

一个$m$表示一共有$m$个区间

一个$q$表示一共有$q$组询问，每次输入一个$l$和$r$表示这个区间的起点和终点

## Solution

这道题的询问并没有问这几个区间分别是什么（即无后效性），而且这道题的$n$的范围只有500，所以可以考虑用二维dp

dp[l][r]表示区间[l, r]之间包括几个区间

于是不难得到动态规划方程
~~~cpp
dp[l][r]=dp[l][r - 1] + dp[l + 1][r] - dp[l + 1][r - 1] + a[l][r];
~~~
即为左端点2重合+右端点重合-这两部分交集+这个段本身

因为这里要用到$r - 1$和$l + 1$所以$l$降序,$r$升序

## Code

~~~cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

#define il inline
#define rep(i, j, k) for(long long i = j;i <= k;i++)
#define per(i, j, k) for(long long i = j;i >= k;i--)

using namespace std;
typedef long long ll;

const int MAXN = 505;

template <typename T>				//快读 
il void read(T &x){
	x = 0;
	char c = 0;
	T w = 0;
	while(!isdigit(c))
		w |= c == '-', c = getchar();
	while(isdigit(c)) x = x * 10 + (c ^ 48), c = getchar();
	if(w)
		x = -x;
}

int dp[MAXN][MAXN];					//动态规划数组 
int a[MAXN][MAXN];					//区间统计数组 
int n;								//n表示区间范围
int m;								//m表示区间范围
int q;								//q表示询问次数 

int main(){
	read(n); read(m); read(q);
	rep(i, 1, m){
		int l, r;
		read(l); read(r);
		a[l][r]++;
	}
	per(l, n, 1)					//双重循环状态转移，前面已将详细说明过了 
		rep(r, 1, n)
			dp[l][r] = dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1] + a[l][r]; 
	while(q--){						//循环询问 
		int l ,r;
		read(l); read(r);
		printf("%d\n", dp[l][r]);
	}
    return 0;
}

~~~

---

## 作者：Prolystic (赞：0)

## Part I Preface

- [原题目(Luogu)](https://www.luogu.com.cn/problem/AT_abc106_c)
- [原题目(AtCoder)](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc106_c)

## Part II Sketch

- 给定正整数 $n, m, q$。
- 接下来给定 $m$ 组 $x_i, y_i$，表示一列列车的起始站和终点站。
- 在接下来给定 $q$ 组 $l_i, r_i$。
- 对于每组询问，回答有多少 $x_i \geq l_i \operatorname{and} y_i \leq r_i$，即有多少列列车的全程都包含在 $l_i, r_i$ 间。
- $1 \leq n \leq 500$。
- $1 \leq m \leq 200000$。
- $1 \leq q \leq 100000$。
- $1 \leq x_i \leq y_i \leq n$。
- $1 \leq l_i \leq r_i \leq n$。

## Part III Analysis

简单思考不难发现， $l_i\sim r_i$ 中的列车数量即为 $l_i\sim r_i - 1$ 中的列车数量加上 $l_i + 1\sim r_i$ 中的列车数量。但是 $l_i + 1\sim r_i - 1$ 中的列车被算了两次，重复了，我们要去掉一个。

所以 $l_i\sim r_i$ 中列车的数量就等于 $l_i\sim r_i - 1$ 中的列车数量加上 $l_i + 1\sim r_i$ 中列车的数量减去 $l_i + 1\sim r_i - 1$ 中列车的数量。若用 $dp(i, j)$ 表示 $i\sim j$ 中列车的数量，状态转移方程即为：

$$dp(i, j) = dp(i, j - 1) + dp(i + 1, j) - dp(i + 1, j - 1)$$

输入时，每次输入一列列车的起始站和终点站 $x_i, y_i$ 时，我们直接给 $dp(x_i, y_i)$ 自增即可，这就是初始状态。最终输出每个 $dp(l_i, r_i)$ 即可。

注意因为我们每次计算时都用到了 $i + 1$ 这一层的信息，所以我们枚举 $i$ 时需要从 $n\sim 1$ 进行遍历。

## Part IV Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 505;
inline int read(){
    int s = 0, w = 1;
    char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-') w = -1;
        ch = getchar();        
    }
    while(isdigit(ch)){
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * w;
}
inline void write(int x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int n, m, q;
int dp[N][N];
int main(){
    n = read(), m = read(), q = read();
    while(m--) dp[read()][read()]++;
    for(int i = n; i >= 1; i--)
        for(int j = i; j <= n; j++)
            dp[i][j] += dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];
    while(q--) write(dp[read()][read()]), putchar('\n');
    return 0;
}
```

---

## 作者：yangyang1000 (赞：0)

发现各位大佬都是用前缀和做的，这里本蒟蒻来讲一下自己的思路，二维差分前缀和。

### 题目分析

用 $cnt_{ij}$ 表示从 $i$ 到 $j$ 的列车数量。

那么对于询问 $p$，$q$，答案就是去求从 $(p,p)$ 这个点到 $(q,q)$ 这个点之间二维数组 $cnt$ 的矩形和。

很自然的想到使用二维前缀和来计算这个矩形和。

那么设 $sum$ 数组是 $cnt$ 数组的二维前缀和。

其中 $sum_{ij}$ 由二维前缀和公式转来，也就是：

`sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1]`

而求矩形和的查找公式是：

`sum[q][q] - sum[p-1][q] - sum[q][p-1] + sum[p-1][p-1]`

于是使用这两个前缀和公式即可 AC。

### code：

```cpp
#include<cstdio>
using namespace std;

int n,m,q,cnt[505][505],sum[505][505];

int main()
{
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d %d",&l,&r);
		cnt[l][r]++;
	}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + cnt[i][j];
	
	for(int i=1;i<=q;i++)
	{
		int p,q;
		scanf("%d %d",&p,&q);
		printf("%d\n",sum[q][q]-sum[p-1][q]-sum[q][p-1]+sum[p-1][p-1]);
	}
	return 0;
}
```


---

