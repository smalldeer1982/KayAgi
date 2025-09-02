# 「DAOI R1」Ciky

## 题目背景

> 
> She is Mine.
>


## 题目描述

深秋，落叶纷纷，瞳可开心了。

$ \texttt{Augen} $ 带着小朋友们一起在树林里捡了很多金黄的叶子。

他们捡的所有叶子都是正多边形，现在 $ \texttt{Augen} $ 准备把它们制作成标本装订成册送给瞳。

制作一个标本，需要沿一片叶子的边缘画上颜色，每一片叶子边缘的颜色不能相同。同时，每一个标本都有相对应的美丽程度。

将标本装订成册时，需满足以下条件：

- 第 $i$ 片叶子的周长不能大于第 $i+1$ 片叶子；
- 第 $i$ 片叶子的美丽程度不能大于第 $i+1$ 片叶子。

 $ \texttt{Augen} $ 拥有 $n$ 支不同颜色的笔，每支还可以画 $a_i$ 的长度。

$m$ 片叶子，第 $i$ 片叶子为正 $k_i$ 边形，每条边长 $b_i$ ，每片叶子的美丽程度$c_i$ 。

更简单地说，即，只有满足 $k_i*b_i \leq a_j$ 的情况下，可以用第 $j$ 支画笔，画第 $i$ 片叶子。

特别地，在一片叶子被第 $i$ 支画笔画完过后，它的周长会变成 $a_i$。一个画笔最多画一片叶子。

 $ \texttt{Augen} $ 希望能更多的送出标本或者使得制作出来的标本美丽程度总和最大。
 
 **注意：两个小问相互独立。**
 
 

## 说明/提示

#### 样例解释
对于第一个问题，用第 $4$ 个画笔画第 $1$ 个叶子，用第 $5$ 个画笔画第 $2$ 个叶子，用第 $1$ 个画笔画第 $3$ 个叶子，画出的叶子周长为 $5,6,9$，可画 $3$ 片。

对于第二问，可以用同样的方法画，美丽度为 $2+6+8=16$

### 数据规模
**本题采用捆绑测试**

| Subtask | $n$ | $m$  | 分值 |
| :----------: | :----------:  | :----------: | :----------: |
| $0$ | $\le10$ | $\le10$ | $10$ |
| $1$ | $\le10^3$ | $\le10^3$  | $20$ |
| $2$ | $\le10^6$ | $\leq 10^6$  | $70$ |

对于 $100\%$ 的数据，$1 \leq n,m \leq 10^6,3\leq k_i \leq 10^6,1 \leq a_i \leq 10^9,1 \leq b_i,c_i \leq 10^6$

## 样例 #1

### 输入

```
5 3
9 7 2 5 6
1 2 1
2 6 8
3 3 4```

### 输出

```
3
16```

# 题解

## 作者：櫻尘ིོི༹ (赞：2)

### 出题人题解

**Subtask 0**

暴力枚举每片叶子用哪个画笔画，画哪些叶子能使美观值最大。

裸搜。

时间复杂度 $O(n^m)$

**Subtask 1**

考虑 dp 。

将画笔按长度从小到大排序，将叶子按美观程度从小到大排序。

每次选出一片叶子后，看用至少用哪支画笔可以画，则它后面的每一支画笔都可以画。

```cpp
for(int i=1;i<=m;++i){
	int v,s;
	int p=lower_bound(c,c+n,s)-c;
	for(int j=n;j>=p+1;--j)dp[j]=max(dp[j],dp[j-1]+1);
}
```

计算美观值最大同理。
```cpp
for(int i=1;i<=m;++i){
	int v,s;
	int p=lower_bound(c,c+n,s)-c;
	for(int j=n;j>=p+1;--j)dp[j]=max(dp[j],dp[j-1]+v);
}
```

时间复杂度 $O(nm)$ 

**Subtask 2**

正解贪心。

将画笔按长度从大到小排序，将叶子按美观度从小到大排序。

由于与越长的画笔匹配的叶子理应美观度越大，且边长小的叶子也能与长的画笔匹配。所以让长度长的画笔匹配满足条件下最大美观度的叶子一定不亏，反复执行这样不亏的操作，最后得到的即是最优解。

适用于维护最长以及美观度最大，但维护美观度最大需要用优先队列维护。

```cpp
priority_queue<int> q;
int head=1;
for(int i=1;i<=m;++i){
	for(int j=head;j<=n;++j){
		if(a[j].s>c[i]||blog){
			head=j;
			break;
		}
		q.push(a[j].v);
		if(j==n)blog=true;
	}
	if(!q.empty())sum+=q.top(),q.pop();
}
```
时间复杂度 $O(n \log n)$ 

---

## 作者：Wei_Han (赞：0)

这没有蓝吧，难度在读题。

考虑贪心，对于第一问，装册需要周长和美观程度单调上升，而周长可能变化，所以我们按照美观程度大到小排序，这样就需要让大美观程度匹配大长度，所以把长度大到小排序，逐个匹配即可，复杂度 $O(n)$。

对于第二问，不需要装册，我们只需要让每一个长度的画笔尽可能匹配它能画的最大美观的图形即可，把画笔从小到大排，周长从小到大排序，开优先队列每次选择美观程度最大的即可，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#pragma GCC optimize(2)
using namespace std;
//typedef int ll;
typedef long long ll;
//typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=1e6+5,M=2e4+5,mod=1e9+7;
ll n,m,a[N];
struct node{ll b,c,k;}b[N];
inline bool cmp(node x,node y){return x.c==y.c?x.b*x.k>y.b*y.k:x.c>y.c;}
inline bool cmp2(node x,node y){return x.b*x.k<y.b*y.k;}
inline bool cmp1(ll x,ll y){return x>y;}
signed main(){
	read(n),read(m);fo(1,i,n) read(a[i]);
	fo(1,i,m) read(b[i].b);
	fo(1,i,m) read(b[i].c);
	fo(1,i,m) read(b[i].k);
	sort(b+1,b+1+m,cmp);
	sort(a+1,a+1+n,cmp1);
	ll now=1,ans1=0,ans2=0;
	fo(1,i,m) if(now<=n&&b[i].k*b[i].b<=a[now]) now++,ans1++;
	priority_queue<ll> pq;
	sort(b+1,b+1+m,cmp2);sort(a+1,a+1+n);
	now=1;
	fo(1,i,n)
	{
		while(now<=m&&a[i]>=b[now].b*b[now].k) pq.push(b[now].c),now++;
		if(pq.size()) ans2+=pq.top(),pq.pop();
	}
	wr(ans1),pr,wr(ans2),pr;
	return 0;
}

``````

---

