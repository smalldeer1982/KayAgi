# SAC E#1 - 一道简单题 Sequence2

## 题目背景

小强和阿米巴是好朋友。


## 题目描述

小强喜欢数列。有一天，他心血来潮，写下了三个长度均为n的数列。

阿米巴也很喜欢数列。但是他只喜欢其中一种，波动数列。


阿米巴把他的喜好告诉了小强。小强便打算找出这三个数列内的最长波动数列。

也就是说，如果我们将三个数列记做a[n][3]，他必须要构造一个二元组序列：<p[i], q[i]>，使得对于任何 i>1 有：

p[i] > p[i-1]

若q[i] = 0，a[p[i]][q[i]] >= a[p[i-1]][q[i-1]]

若q[i] = 1，a[p[i]][q[i]] <= a[p[i-1]][q[i-1]]

若q[i] = 2，只要保持段内同向即可（就是对于连续的一段q[i]=2，要么都有a[p[i]][q[i]] >= a[p[i-1]][q[i-1]]，要么都有a[p[i]][q[i]] <= a[p[i-1]][q[i-1]]）。

小强希望这个二元组序列尽可能长。


提示：当q[i] != q[i-1]时，数列的增减性由q[i]而非q[i-1]决定。


**清晰版题目描述**


小强拿到一个3×n的数组，要在每一列选一个数（或者不选），满足以下条件：


1.如果在第一行选，那它必须大于等于上一个数

2.如果在第二行选，那么必须小于等于上一个数

3.如果在第三行选，对于连续的一段在第三行选的数，必须满足方向相同（都小于等于上一个数或者都大于等于上一个数）


## 说明/提示

对于20%的数据，n <= 10， m <= 1000

对于60%的数据，n <= 1000,  m <= 1000

对于100%的数据， n <= 100000， m <= 1000000000

其中m = max|a[i]|

样例解释：

取第三行1 2 3（增），然后取第1行6（增），然后取第三行5 4（减），长度为6。


## 样例 #1

### 输入

```
6
1 2 3 6 5 4
5 4 3 7 8 9
1 2 3 6 5 4
```

### 输出

```
6```

# 题解

## 作者：玫葵之蝶 (赞：6)

首先宣传blog：[blog](http://blog.csdn.net/stone41123/article/details/78172774)

###题解

这个题明显是dp，我们来考虑如何dp。

我们把四种状态：（本列）选1，选2，选3（大于等于上一个），选3（小于等于上一个）

分别称为：状态1，状态2，状态3，状态4

那么，我们可以发现，状态1可以由前面的状态1，2，3，4推过来，只要满足那一位所选的数小于等于当前的数。

类似的，状态2也可以由前面的状态1，2，3，4推过来，只要满足条件。

然而，状态3却不可以由状态4递推过来，因为必须保证方向相同。

同样的，状态4也不可以由状态3递推过来。

我们可以设计这样一个状态：

$dp(k,i)表示以第i位在第k种状态结尾的最大序列长度$

$转移如下：$

$dp(1,i)=max(dp(k,j))(1<=k<=4,1<=j<i,val_{1,j}<=val_{1,i})+1$

$dp(2,i)=max(dp(k,j))(1<=k<=4,1<=j<i,val_{1,j}>=val_{1,i})+1$

$dp(3,i)=max(dp(k,j))(1<=k<=4,k\not =4 ,1<=j<i,val_{1,j}<=val_{1,i})+1$

$dp(4,i)=max(dp(k,j))(1<=k<=4,k\not =3,1<=j<i,val_{1,j}>=val_{1,i})+1$

暴力转移就是$O(n^2)$

然而我们可以用数据结构来优化查询，比如线段树。

我们可以对于每一种状态建一棵线段树，然后每次转移时多查询几次，这样不容易错，然后每次计算完答案之后将值插入到线段树中。

跑得还挺快，最慢的点400ms

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;
inline int read(){
    int x=0;char ch=' ';int f=1;
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int n,size;
int a[100001],b[100001],c[100001],num[300001];
int dp[5][100001],t[5][1200001];
inline void insert(int id,int rt,int l,int r,int pos,int v){
    if(l==r){t[id][rt]=max(t[id][rt],v);return;}
    int mid=(l+r)>>1;
    if(pos<=mid)insert(id,rt<<1,l,mid,pos,v);
    else insert(id,rt<<1|1,mid+1,r,pos,v);
    t[id][rt]=max(t[id][rt<<1],t[id][rt<<1|1]);
}
inline int query(int id,int rt,int l,int r,int L,int R){
    if(L<=l&&r<=R)return t[id][rt];
    int mid=(l+r)>>1;
    int ans=0;
    if(L<=mid)ans=max(ans,query(id,rt<<1,l,mid,L,R));
    if(mid+1<=R)ans=max(ans,query(id,rt<<1|1,mid+1,r,L,R));
    return ans;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read(),num[++size]=a[i];
    for(int i=1;i<=n;i++)b[i]=read(),num[++size]=b[i];
    for(int i=1;i<=n;i++)c[i]=read(),num[++size]=c[i];
    sort(num+1,num+size+1);
    size=unique(num+1,num+size+1)-num-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(num+1,num+size+1,a[i])-num;
    for(int i=1;i<=n;i++)b[i]=lower_bound(num+1,num+size+1,b[i])-num;
    for(int i=1;i<=n;i++)c[i]=lower_bound(num+1,num+size+1,c[i])-num;
    for(int i=1;i<=n;i++){
        dp[1][i]=max(dp[1][i],query(1,1,1,size,1,a[i]));
        dp[1][i]=max(dp[1][i],query(2,1,1,size,1,a[i]));
        dp[1][i]=max(dp[1][i],query(3,1,1,size,1,a[i]));
        dp[1][i]=max(dp[1][i],query(4,1,1,size,1,a[i]));
        dp[1][i]++;
        dp[2][i]=max(dp[2][i],query(1,1,1,size,b[i],size));
        dp[2][i]=max(dp[2][i],query(2,1,1,size,b[i],size));
        dp[2][i]=max(dp[2][i],query(3,1,1,size,b[i],size));
        dp[2][i]=max(dp[2][i],query(4,1,1,size,b[i],size));
        dp[2][i]++;
        dp[3][i]=max(dp[3][i],query(1,1,1,size,1,c[i]));
        dp[3][i]=max(dp[3][i],query(2,1,1,size,1,c[i]));
        dp[3][i]=max(dp[3][i],query(3,1,1,size,1,c[i]));
        dp[3][i]++;
        dp[4][i]=max(dp[4][i],query(1,1,1,size,c[i],size));
        dp[4][i]=max(dp[4][i],query(2,1,1,size,c[i],size));
        dp[4][i]=max(dp[4][i],query(4,1,1,size,c[i],size));
        dp[4][i]++;
        insert(1,1,1,size,a[i],dp[1][i]);
        insert(2,1,1,size,b[i],dp[2][i]);
        insert(3,1,1,size,c[i],dp[3][i]);
        insert(4,1,1,size,c[i],dp[4][i]);
    }
    int ans=0;
    for(int k=1;k<=4;k++){
        for(int i=1;i<=n;i++){
            ans=max(ans,dp[k][i]);
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：灼眼的夏娜 (赞：2)

一道$dp$题（当然考试时候我并没有想出来）

由于数据太水，你只需要
```cpp
printf("%d\n", read());
```
就有20分。。。。。。

## 正解：
设$f[i][j]$，表示第$i$列，状态是$j$可获得的最大长度设第一行为A， 第二行为B， 第三行为C

那就有从A过来的，从B过来的，从C升序过来的，从C降序过来的四种情况，考虑转移

如果是A，$f[i][A]$就需要在A时候判断能不能加，否则就和其他的取个MAX，B同理，C的话，看看是从升或降哪一个

升的和降的取MAX就行，$m$比较大，所以先离散化，之后用线段树维护一下就好了，这是转移方程，其中$j$是你枚举的状态

```cpp
f[i][0] = max(f[i][0], query(1, j, 1, cnt, 1, a[i][0]) + 1);
f[i][1] = max(f[i][1], query(1, j, 1, cnt, a[i][1], cnt) + 1);
if(j != 3) f[i][2] = max(f[i][2], query(1, j, 1, cnt, 1, a[i][2]) + 1);
if(j != 2) f[i][3] = max(f[i][3], query(1, j, 1, cnt, a[i][2], cnt) + 1);
```
之后再分别$Change$一遍就完了，应该好理解吧
```cpp
Change(1, 0, 1, cnt, a[i][0], f[i][0]);
Change(1, 1, 1, cnt, a[i][1], f[i][1]);
Change(1, 2, 1, cnt, a[i][2], f[i][2]);
Change(1, 3, 1, cnt, a[i][2], f[i][3]);
```
完结撒花？

---

## 作者：Union_Find (赞：1)

首先看到题目，考虑 dp。

一开始我设 $f_{i,0/1/2}$ 表示第 $i$ 位选了第 $j+1$ 行的答案，但发现无法处理选第 $3$ 行的情况，所以改成 $f_{i,0/1/2/3}$ 分别表示第 $i$ 位选了第 $1$ 行，第 $2$ 行以及选了第 $3$ 行，是单调增和降的情况。

考虑转移。$f_{i,0} = \max_{j<i \wedge a_{1,j} \leq a_{1,i},1 \leq k \leq 4}(f_{j,k}+1)$ 和 $f_{i,1} = \max_{j<i \wedge a_{2,j} \geq a_{2,i},1 \leq k \leq 4}(f_{j,k}+1)$ 应该是最简单的了。

最后两种情况，$f_{i,2} = \max_{j<i \wedge a_{3,j} \leq a_{3,i},k = 0,1,2}(f_{j,k}+1)$ 和 $f_{i,3} = \max_{j<i \wedge a_{3,j} \geq a_{3,i},k=0,1,3}(f_{j,k}+1)$。

暴力转移是 $O(n^2)$ 的，用线段树维护一下可以优化成 $O(n\log n)$ 的，注意离散化，而且 $a_i$ 会小于 $0$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 100005
#define M 300000
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), a[4][N], f[N][4], tr[N << 4], ls[N << 4], rs[N << 4], rt[4], ans, ep, nls[N << 2], cnt;
void add(ll &p, ll l, ll r, ll x, ll k){
	if (!p) p = ++ep;
	if (l == r) return tr[p] = max(tr[p], k), void(0);
	ll mid = (l + r) >> 1;
	if (x <= mid) add(ls[p], l, mid, x, k);
	else add(rs[p], mid + 1, r, x, k);
	tr[p] = max(tr[ls[p]], tr[rs[p]]);
}ll ask(ll p, ll l, ll r, ll nl, ll nr){
	if (!p) return 0;
	if (nl <= l && r <= nr) return tr[p];
	ll mid = (l + r) >> 1, ans = 0;
	if (nl <= mid) ans = max(ans, ask(ls[p], l, mid, nl, nr));
	if (nr > mid) ans = max(ans, ask(rs[p], mid + 1, r, nl, nr));
	return ans;
}
int main(){
	for (int i = 1; i <= 3; i++) for (int j = 1; j <= n; j++) a[i][j] = rd(), nls[++cnt] = a[i][j];
	sort (nls + 1, nls + cnt + 1);
	cnt = unique(nls + 1, nls + cnt + 1) - nls - 1;
	for (int i = 1; i <= 3; i++) for (int j = 1; j <= n; j++) a[i][j] = lower_bound(nls + 1, nls + cnt + 1, a[i][j]) - nls - 1; 
	for (int i = 1; i <= n; i++){
		for (int k = 0; k < 4; k++) f[i][0] = max(f[i][0], ask(rt[k], 1, M, 1, a[1][i]) + 1);
		for (int k = 0; k < 4; k++) f[i][1] = max(f[i][1], ask(rt[k], 1, M, a[2][i], M) + 1);
		for (int k = 0; k < 4; k++) if (k != 3) f[i][2] = max(f[i][2], ask(rt[k], 1, M, 1, a[3][i]) + 1);
		for (int k = 0; k < 4; k++) if (k != 2) f[i][3] = max(f[i][3], ask(rt[k], 1, M, a[3][i], M) + 1);
		for (int k = 0; k < 4; k++) add(rt[k], 1, M, a[min(k + 1, 3)][i], f[i][k]), ans = max(ans, f[i][k]);//, cout << f[i][k] << " ";puts("");
	}printf ("%lld\n", ans);
	return 0;
}

```

---

## 作者：Sad_Rex (赞：1)

**一、题意解释**：

小强有 $3$ 个数组，共有 $3$ 种**操作**：

+ 若在 $a$ 数组选数的话，则要满足 $a_i \geq $ 上一个数。
+ 若在 $b$ 数组选数的话，则要满足 $b_i \leq $ 上一个数。
+ 若在 $c$ 数组选数的话，若上一个数也是 **$c$ 数组** 中的，则要于其同号，反之 $\leq$ ,$\geq$ 都行。

**二、 DP 状态**：

设 $dp_{k,i}$ 表示在 $1 \ldots i$ 中，且选 $i$ 个数，转移方式是 $k$ 的最长波动数列。

**三、 DP 的转移**：

不难发现有 $4$ 种转移方式。
+ 在 $a$ 数组中，$dp_{1,i}=\max(dp[k,j])+1$，其中 $1 \leq k \leq 4,1  \leq j < i$ 且要满足 $val_{k,j} \leq val_{1,i}$。
+ 在 $b$ 数组中，$dp_{2,i}=\max(dp[k,j])+1$，其中 $1 \leq k \leq 4,1  \leq j < i$ 且要满足 $val_{k,j} \geq val_{1,i}$。
+ 在 $c$ 数组中，$dp_{3,i}=\max(dp[k,j])+1$，其中 $1 \leq k \leq 3,1  \leq j < i$ 且要满足 $val_{k,j} \leq val_{1,i}$。
+ 在 $c$ 数组中，$dp_{4,i}=\max(dp[k,j])+1$，其中 $1 \leq k \leq 4,k \ne 3,1 \leq j < i$ 且要满足 $val_{k,j} \geq val_{1,i}$。

**四、优化**：

按以上方法，因为时间复杂度为 $O(n^2)$，且本题 $n \leq 10^5$，所以只能收获 $60$ 分。

考虑到我们其实每一次操作都是在 $j < i, val$ 等中的条件中求最大值，所以我们理所应当的想到了线段树。

应为从左到右的顺序使得我们无须特判 $j < i$，所以我们将 $val$ 作为边界。

因为 $val \leq 10^9$ 所以我们要对其进行离散化处理。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int  long long
#define kg putchar(' ')
#define endl puts("")
inline int read(){
	int vis=1,ans=0;
	char x=getchar();
	while(x<'0'||x>'9'){
		if(x=='-')vis=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9'){
		ans=ans*10+x-'0';
		x=getchar();
	}
	return vis*ans;
}
inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
const int N=1e5+9;
int a[N],b[N],c[N];
int dp[5][N];
int n=read();
int ans=0; 
int num[3*N],size;
struct nod{
	int l,r,maxn;
}e[5][12*N];
void pushup(int k,int i){
	e[k][i].maxn=max(e[k][i<<1].maxn,e[k][i<<1|1].maxn);
}
void build(int p,int l,int r){
	for(int i=1;i<=4;i++)e[i][p].l=l,e[i][p].r=r;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	for(int i=1;i<=4;i++)pushup(i,p);
	return;
}
int qrevy(int p,int k,int l,int r){
	if(e[k][p].l>r||l>e[k][p].r)return 0;
	if(l<=e[k][p].l&&e[k][p].r<=r)return e[k][p].maxn;
	return max(qrevy(p<<1,k,l,r),qrevy(p<<1|1,k,l,r));
}
void modify(int p,int k,int x,int v){
	if(x<e[k][p].l||e[k][p].r<x)return;
	if(e[k][p].l==e[k][p].r&&e[k][p].l==x){
		e[k][p].maxn=max(e[k][p].maxn,v);
		return;
	}
	modify(p<<1,k,x,v);
	modify(p<<1|1,k,x,v);
	pushup(k,p);
}
signed main(){
	for(int i=1;i<=n;i++)num[i]=a[i]=read();
	for(int i=1;i<=n;i++)num[n+i]=b[i]=read();
	for(int i=1;i<=n;i++)num[n+n+i]=c[i]=read();
	sort(num+1,num+3*n+1);
	size=unique(num+1,num+3*n+1)-num-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(num+1,num+size+1,a[i])-num;
		b[i]=lower_bound(num+1,num+size+1,b[i])-num;
		c[i]=lower_bound(num+1,num+size+1,c[i])-num;
	}
	build(1,1,size);
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(int k=1;k<=4;k++){
			cnt=max(cnt,qrevy(1,k,1,a[i]));
		}
		dp[1][i]=cnt+1,cnt=0;
		for(int k=1;k<=4;k++){
			cnt=max(cnt,qrevy(1,k,b[i],size));
		}
		dp[2][i]=cnt+1,cnt=0;
		for(int k=1;k<=3;k++){
			cnt=max(cnt,qrevy(1,k,1,c[i]));
		}
		dp[3][i]=cnt+1,cnt=0;
		for(int k=1;k<=4;k*=2){
			cnt=max(cnt,qrevy(1,k,c[i],size));
		}
		dp[4][i]=cnt+1,cnt=0;
		modify(1,1,a[i],dp[1][i]);
		modify(1,2,b[i],dp[2][i]);
		modify(1,3,c[i],dp[3][i]);
		modify(1,4,c[i],dp[4][i]);
	}
	for(int k=1;k<=4;k++){
		ans=max(ans,dp[k][n]);
	}
	print(ans);
	return 0;
}
```

---

## 作者：半仙胡小桃 (赞：1)

传送门！

最简单的暴力：输出N（20）！

正解DP：

60DP：

dp[i][j]为选第i行到第j位置最长的符合要求的序列长度。

我们把第三个序列选上升的定义为dp[3][j]

下降的定义为dp[4][j]。

状态转移：

很明显

dp[1][j]=max(dp[1][1->(j-1)],dp[2][1->(j-1)],dp[3][1->(j-1)],dp[4][1->(j-1)])+1(前提是要大于等于转移序列的最后一个)

dp[2][j]的转移同理。

对于dp[3][j]，很明显不能由dp[4][1->(j-1)]转移而来，因为题目要求要整单调的。

对于dp[4][j]同理。

最后输出max(dp[i][j])（i=1->4,j=1->n）.

复杂度O(n^2)。

线段树优化（100）：

对于转移，由于我们取max，那么可以维护四棵线段树来快速求解最大值。

用数组中具体的值作为线段树的端点

查询比当前小的（1->值）

查询比当前大的（值->n）

对于每一个dp[i][j]，转移完以后插入线段树即可。

但是值<=1000000000。太大咋办。

离散化一下，把大小关系整好就行！

复杂度O(nlogn)












```cpp
#include <cstdio> 
#include <iostream>
#include <algorithm>
using namespace std;
const int maxm=1100000;
int a[maxm],b[maxm],c[maxm];
int num[3*maxm],cnt;
int tree[5][4*maxm];
int dp[5][maxm];
void updata(int id,int o,int l,int r,int ind,int ans)
{
    if(l==r)
    {
        tree[id][o]=max(tree[id][o],ans);
        return;
    }
    int mid=(l+r)>>1;
    if(ind<=mid)
     updata(id,(o<<1),l,mid,ind,ans);
    else
     updata(id,(o<<1)|1,mid+1,r,ind,ans);
    tree[id][o]=max(tree[id][(o<<1)],tree[id][(o<<1)|1]);
}
int ask(int id,int o,int l,int r,int ql,int qr)
{
    if(ql>r||qr<l) return -1;
    if(ql<=l&&qr>=r) return tree[id][o];
    int mid=l+((r-l)>>1);
    int p1=ask(id,(o<<1),l,mid,ql,qr);
    int p2=ask(id,(o<<1)+1,mid+1,r,ql,qr);
    return max(p1,p2);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
     scanf("%d",&a[i]),num[++cnt]=a[i];
    for(int i=1;i<=n;i++)
     scanf("%d",&b[i]),num[++cnt]=b[i];
    for(int i=1;i<=n;i++)
     scanf("%d",&c[i]),num[++cnt]=c[i];
    sort(num+1,num+cnt+1);
    int t=unique(num+1,num+cnt+1)-num-1;//离散化
    for(int i=1;i<=n;i++)
     a[i]=lower_bound(num+1,num+t+1,a[i])-num;
    for(int i=1;i<=n;i++)
     b[i]=lower_bound(num+1,num+t+1,b[i])-num;
    for(int i=1;i<=n;i++)
     c[i]=lower_bound(num+1,num+t+1,c[i])-num;//还原大小关系
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=4;j++)
         dp[1][i]=max(dp[1][i],ask(j,1,1,t,1,a[i]));
        for(int j=1;j<=4;j++)
         dp[2][i]=max(dp[2][i],ask(j,1,1,t,b[i],t));
        dp[3][i]=max(dp[3][i],ask(1,1,1,t,1,c[i]));
        dp[3][i]=max(dp[3][i],ask(2,1,1,t,1,c[i]));
        dp[3][i]=max(dp[3][i],ask(3,1,1,t,1,c[i]));
        dp[4][i]=max(dp[4][i],ask(1,1,1,t,c[i],t));
        dp[4][i]=max(dp[4][i],ask(2,1,1,t,c[i],t));
        dp[4][i]=max(dp[4][i],ask(4,1,1,t,c[i],t));
        dp[1][i]++,dp[2][i]++,dp[3][i]++,dp[4][i]++;
        updata(1,1,1,t,a[i],dp[1][i]);
        updata(2,1,1,t,b[i],dp[2][i]);
        updata(3,1,1,t,c[i],dp[3][i]);
        updata(4,1,1,t,c[i],dp[4][i]);//更新线段树的值。
    }
    int ans=0;
    for(int j=1;j<=n;j++)
     for(int i=1;i<=4;i++)
     ans=max(ans,dp[i][j]);//找最大的
    printf("%d",ans);
}
```

---

## 作者：深海鱼的眼泪 (赞：1)

介绍一下用树状数组的做法。

这道题首先是DP。

搬运一下官方题解中的内容：设$dp_{i,j}$表示：第 $i$ 个位置选择第 $j$ 个序列的数，前 $i$ 个位置所能构成的最长子序列的长度。特别的，$dp_{i,2}$表示第 $i$ 个位置选择第三个序列的数，且大于等于前一个数；$dp_{i,3}$表示第 $i$ 个位置选择第三个序列的数，且小于等于前一个数。

$$dp_{i,0}=max(dp_{j,k})+1,0\leq{j}<i,0\leq{k}<4,a_{j,k}\leq{a_{i,0}};$$


$$dp_{i,1}=max(dp_{j,k})+1,0\leq{j}<i,0\leq{k}<4,a_{j,k}\geq{a_{i,1}};$$


$$dp_{i,2}=max(dp_{j,k})+1,0\leq{j}<i,0\leq{k}<3,a_{j,k}\leq{a_{i,2}};$$


$$dp_{i,3}=max(dp_{j,k})+1,0\leq{j}<i,0\leq{k}<4,k\neq{2},a_{j,k}\geq{a_{i,2}};$$


边界条件：$dp_{0,j}=0$。

状态数 $O(n)$，转移复杂度 $O(n)$，总复杂度 $O(n^2)$。

(60分做法）

要取得100分需要进行一些优化。官方题解中是这样说的：该转移和 LIS 的转移类似，可以使用数据结构进行优化。

以 LIS 为例，建立一个线段树，初始时所有位置都为 0。

每次求 $dp$ 值时，查询值介于 $[−∞,a_i]$ 中的 $dp$ 值的最大值。

再将 $i$ 位置的 $dp$ 值插入到线段树 $a_i$ 处。

转移的复杂度优化为 $O(log n)$，故总复杂度 $O(n log n)$。

(100分做法）

然而题解中讲线段树标程里却是树状数组2333

60分做法应该很好写，那我讲一下如何用树状数组优化。

首先我们需要将三个数列的元素进行离散化。

然后根据 $i$ 从 1 到 $n$ 循环。对于第 $k$ 个数列的第 $i$ 个元素，需要找出在它前面的符合条件的最大值。我们可以用树状数组来做。

令 $f[j][0]$ 表示到目前为止 $dp_{i,0}$ 和 $dp_{i,1}$ 中以 $j-(j\&-j)+1$ 到 $j$ 结尾的最大值, $f[j][2]$ 表示到目前为止 $dp_{i,2}$ 中以 $j-(j\&-j)+1$ 到 $j$ 结尾的最大值, $f[j][4]$ 表示到目前为止 $dp_{i,3}$ 中以 $j-(j\&-j)+1$ 到 $j$ 结尾的最大值。由于还要求大于 $a_{j,k}$ 的值，因此再设置 $f[j][1],f[j][3],f[j][5]$，用的时候把 $a_{j,k}$ 反一下就可以了。

计算的时候，

$dp_{i,0}$ 的值用 $f[a_{i,k}][0],f[a_{i,k}][2],f[a_{i,k}][4]$ 更新，再将值更新到 $f[a_{i,k}][0],f[a_{i,k}][1]$ 中;

$dp_{i,1}$ 的值用 $f[a_{i,k}][1],f[a_{i,k}][3],f[a_{i,k}][5]$ 更新，再将值更新到 $f[a_{i,k}][0],f[a_{i,k}][1]$ 中;

$dp_{i,2}$ 的值用 $f[a_{i,k}][0],f[a_{i,k}][2]$ 更新，再将值更新到 $f[a_{i,k}][2],f[a_{i,k}][3]$ 中;

$dp_{i,3}$ 的值用 $f[a_{i,k}][0],f[a_{i,k}][4]$ 更新，再将值更新到 $f[a_{i,k}][4],f[a_{i,k}][5]$ 中。

最后根据 $f[max][0],f[max][2],f[max][4](max为元素离散化后最大值)$ 就可以求出答案了。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n,a[100001][4],f[7][300001],ans,data[300001],up,tot;
void add(int x,int p,int* f){
    for (;p<=up;p+=p&-p){
        if (x<=f[p]) break;
        f[p]=x;
    }
}
int slv(int p,int* f){
    int ans=0;
    for (;p;p-=p&-p) ans=ans<f[p]?f[p]:ans;
    return ans;
}
void dcp(){
    sort(data+1,data+tot+1);
    up=unique(data+1,data+1+tot)-data-1;
    for (int i=0;i<=2;++i)
        for (int j=1;j<=n;++j) a[j][i]=lower_bound(data+1,data+1+up,a[j][i])-data;
}
void read(int& x){
    x=0;
    int y=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') y=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    x=x*y;
}
int main(){
    int i,j,k,t,m,x1,x2,x3;
    read(n);
    for (i=0;i<=2;++i)
        for (j=1;j<=n;++j){
            read(a[j][i]);
            data[++tot]=a[j][i];
        }
    dcp();
    for (i=1;i<=n;++i){
        t=0;
        m=slv(a[i][0],f[0]);
        t=m>t?m:t;
        m=slv(a[i][0],f[2]);
        t=m>t?m:t;
        m=slv(a[i][0],f[4]);
        t=m>t?m:t;
        x1=t+1;
        t=0;
        m=slv(up-a[i][1]+1,f[1]);
        t=m>t?m:t;
        m=slv(up-a[i][1]+1,f[3]);
        t=m>t?m:t;
        m=slv(up-a[i][1]+1,f[5]);
        t=m>t?m:t;
        x2=t+1;
        t=0;
        m=slv(a[i][2],f[0]);
        t=m>t?m:t;
        m=slv(a[i][2],f[2]);
        t=m>t?m:t;
        x3=t+1;
        t=0;
        m=slv(up-a[i][2]+1,f[1]);
        t=m>t?m:t;
        m=slv(up-a[i][2]+1,f[5]);
        t=m>t?m:t;
        add(t+1,a[i][2],f[4]);
        add(t+1,up-a[i][2]+1,f[5]);
        add(x1,a[i][0],f[0]);
        add(x1,up-a[i][0]+1,f[1]);
        add(x2,a[i][1],f[0]);
        add(x2,up-a[i][1]+1,f[1]);
        add(x3,a[i][2],f[2]);
        add(x3,up-a[i][2]+1,f[3]);
    }
    ans=slv(up,f[0]);
    ans=max(ans,slv(up,f[2]));
    ans=max(ans,slv(up,f[4]));
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：s_a_b_e_r (赞：1)

#线段树+dp

设 dp\_(i,k) 表示：第 i 个位置选择第k个序列的数，前 i 个位置 所能构成的最长子序列的长度。

于是我们有一下4个状态,对于每一个位置i

```cpp
k=0选择第一行
k=1选第二行。
k=2选第三行,且大于等于前一个数
k=3选第三行,且小于等于前一个数
```
那么根据题意,对于2,3,两个状态,他们不能相互转移.所以我们有

```cpp
dp[i][0]=dp[0~i-1][0~3]+1   (a[j][k]<=a[i][0]);
dp[i][1]=dp[0~i-1][0~3]+1   (a[j][k]>=a[i][1]);
dp[i][2]=dp[0~i-1][0,1,2]+1   (a[j][k]<=a[i][2]);
dp[i][3]=dp[0~i-1][0,1,3]+1   (a[j][k]>=a[i][3]);
```
那么我们还是发现会T TAT

于是就考虑优化第二维j的循环。

现在对于每一个转移a[i][?]我们都要找到一个dp值最大的a[j][k]其中

a[j][k]满足转移;

于是n很小,就可以把数据离散后放进线段树中.对于dp的每一维建立一个线段树,储存当前以为最后一个选择为(选择数)最大所能到达的dp值。

bel当前属于第几维的dp(查询&&修改)

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=100000+233;
inline int read(){
    int an=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){an=an*10+ch-'0';ch=getchar();}
    return an*f;
}
int dp[maxn][5],n,ans;
int a[maxn][5],tot,cnt,id[maxn<<2];
struct saber{
int ma[6];
int l,r;
}tr[maxn<<4];
void prepare(){
    n=read();
    for(int j=0;j<=2;j++)
        for(int i=1;i<=n;i++){
        a[i][j]=read();tot++;id[tot]=a[i][j];}
    sort(id+1,id+1+tot);
    cnt=unique(id+1,id+1+tot)-id;
    for(int i=1;i<=n;i++)
    for(int j=0;j<=2;j++)
    a[i][j]=lower_bound(id+1,id+cnt,a[i][j])-id+1;
    for(int i=1;i<=n;i++)a[i][3]=a[i][2];
}
void build(int k,int l,int r){
    tr[k].l=l;tr[k].r=r;
    if(l==r)return ;
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
}
int ask(int bel,int k,int x,int y){
    int l=tr[k].l,r=tr[k].r;
    if(l==x&&r==y)return tr[k].ma[bel];
    int mid=(l+r)>>1;
    if(y<=mid)ask(bel,k<<1,x,y);
    else if(x>mid)ask(bel,k<<1|1,x,y);
    else return max( ask(bel,k<<1,x,mid),ask(bel,k<<1|1,mid+1,y) );
}
void add(int bel,int k,int poi,int wi){
    int l=tr[k].l,r=tr[k].r;;
    if(poi==l&&poi==r){
    tr[k].ma[bel]=max(wi,tr[k].ma[bel]);
    return ;}
    int mid=(l+r)>>1;
    if(poi<=mid)add(bel,k<<1,poi,wi);
    else add(bel,k<<1|1,poi,wi);
    tr[k].ma[bel]=max(tr[k<<1].ma[bel],tr[k<<1|1].ma[bel]);
}
void DP(){
    build(1,1,cnt);
    for(int i=1;i<=n;i++){
            for(int k=0;k<4;k++){
            dp[i][0]=max(ask(k,1,1,a[i][0])+1,dp[i][0]);//查询小于等于
            dp[i][1]=max(ask(k,1,a[i][1],cnt)+1,dp[i][1]);//后面大于等于
            if(k!=3)
            dp[i][2]=max(ask(k,1,1,a[i][2])+1,dp[i][2]);
            if(k!=2)
            dp[i][3]=max(ask(k,1,a[i][3],cnt)+1,dp[i][3]);
            }
            add(0,1,a[i][0],dp[i][0]);
            add(1,1,a[i][1],dp[i][1]);
            add(2,1,a[i][2],dp[i][2]);
            add(3,1,a[i][3],dp[i][3]);
        }
    for(int i=0;i<4;i++)
    ans=max(ans,dp[n][i]);
}
int main(){
    prepare();
    DP();
    cout<<ans;
}
```

---

## 作者：2021hych (赞：0)

## 前置芝士
LIS，线段树。
## 思路
明显的线性 DP，与 LIS 模型大致相同。状态设计如下：$dp_{j,i}$ 为当前处理到第 $i$ 个数，若 $j=1/2$，则表示上一个所选的数在第 $j$ 行的最大长度。若 $j=3/4$，则表示上一个所选的数在第 3 行的最大长度（递增/递减）。状态转移方程如下：
$$dp_{1,i}=\max_{1 \le j < i}{dp_{k,j}}(k = 1,2,3,4,a[p_k][j] \le a[1][i])$$
$$dp_{2,i}=\max_{1 \le j < i}{dp_{k,j}}(k = 1,2,3,4,a[p_k][j] \ge a[1][i])$$
$$dp_{3,i}=\max_{1 \le j < i}{dp_{k,j}}(k = 1,2,3,a[p_k][j] \le a[1][i])$$
$$dp_{4,i}=\max_{1 \le j < i}{dp_{k,j}}(k = 1,2,4,a[p_k][j] \ge a[1][i])$$
注意，上述 $p_k$ 仅仅表示第一维所对应的转移行，无特别意义。

此时，是平方级别的算法，过不了此题。我们可以建立 4 棵线段树来维护这四个转移的最大值，就不用线性的扫描了。时间复杂度为 $O(n \log n)$。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5;
int n,len,ans1,ans2,ans3,ans4,ans; 
int a[3][N],b[N];
struct Sgt {
	int val;
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
}t[4][N<<2];
void sre() {
	sort(b+1,b+3*n+1);
	len=unique(b+1,b+3*n+1)-b-1;
	for(int i=0;i<3;i++)
		for(int j=1;j<=n;j++) a[i][j]=lower_bound(b+1,b+len+1,a[i][j])-b;
}
void pushup(int p,int pos) {
	t[pos][p].val=max(t[pos][ls(p)].val,t[pos][rs(p)].val);
}
void change(int p,int l,int r,int x,int d,int pos) {
	if(r<x||l>x) return;
	if(l==r&&l==x) {
		t[pos][p].val=max(t[pos][p].val,d);
		return;
	}
	int mid=l+r>>1;
	change(ls(p),l,mid,x,d,pos);
	change(rs(p),mid+1,r,x,d,pos);
	pushup(p,pos); 
}
int query(int p,int l,int r,int L,int R,int pos) {
	if(L<=l&&r<=R) return t[pos][p].val;
	int mid=l+r>>1;
	int res=0;
	if(L<=mid) res=max(res,query(ls(p),l,mid,L,R,pos));
	if(R>mid) res=max(res,query(rs(p),mid+1,r,L,R,pos)); 
	return res;
}
int max4(int A,int B,int C,int D) {
	return max(A,max(B,max(C,D)));
}
int max3(int A,int B,int C) {
	return max(A,max(B,C));
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=0;i<3;i++)
		for(int j=1;j<=n;j++) {
			cin>>a[i][j];
			b[j+i*n]=a[i][j];
		}
	sre();
	for(int i=1;i<=n;i++) {
		ans1=max4(query(1,1,len,1,a[0][i],0),query(1,1,len,1,a[0][i],1),query(1,1,len,1,a[0][i],2),query(1,1,len,1,a[0][i],3))+1;
        ans2=max4(query(1,1,len,a[1][i],len,0),query(1,1,len,a[1][i],len,1),query(1,1,len,a[1][i],len,2),query(1,1,len,a[1][i],len,3))+1;
        ans3=max3(query(1,1,len,1,a[2][i],0),query(1,1,len,1,a[2][i],1),query(1,1,len,1,a[2][i],2))+1;
        ans4=max3(query(1,1,len,a[2][i],len,0),query(1,1,len,a[2][i],len,1),query(1,1,len,a[2][i],len,3))+1;
        ans=max(ans,max4(ans1,ans2,ans3,ans4));
        change(1,1,len,a[0][i],ans1,0);
        change(1,1,len,a[1][i],ans2,1);
        change(1,1,len,a[2][i],ans3,2);
		change(1,1,len,a[2][i],ans4,3);
	}
	cout<<ans;
	return 0;
}
```


---

