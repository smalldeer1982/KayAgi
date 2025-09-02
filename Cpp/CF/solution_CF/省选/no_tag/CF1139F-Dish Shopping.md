# Dish Shopping

## 题目描述

有 $m$ 个人居住在一座城市中。城市里有 $n$ 道菜品在售。每道菜 $i$ 有一个价格 $p_i$，一个标准 $s_i$ 和一个美观度 $b_i$。每个人 $j$ 有一个收入 $inc_j$ 和一个偏好美观度 $pref_j$。

一个人绝不会购买标准低于其收入的菜品。同时，一个人也买不起价格高于其收入的菜品。换句话说，某个人 $j$ 只有在 $p_i \leq inc_j \leq s_i$ 时才可以买第 $i$ 道菜。

此外，某个人 $j$ 只有在 $|b_i - pref_j| \leq (inc_j - p_i)$ 时才可以买第 $i$ 道菜。也就是说，如果菜品的价格比该人的收入低 $k$，那么该人只允许菜品的美观度与其偏好美观度的绝对差值最多为 $k$。

请输出城市中每个人能买到的菜品数量。

## 说明/提示

在第一个样例中，第一个人可以购买第 $2$ 道菜，第二个人可以购买第 $1$ 和第 $2$ 道菜，第三个人无法购买任何菜品。

在第二个样例中，第一个人无法购买任何菜品，第二个人可以购买第 $1$ 和第 $4$ 道菜，第三个人可以购买第 $1$、第 $2$ 和第 $4$ 道菜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
2 1 3
2 4 4
2 1 1
2 2 3
1 2 4
```

### 输出

```
1 2 0 ```

## 样例 #2

### 输入

```
4 3
1 2 1 1
3 3 1 3
2 1 3 2
1 1 3
1 2 1
```

### 输出

```
0 2 3 ```

# 题解

## 作者：xyz32768 (赞：5)

题意
=

- $n$ 种菜和 $m$ 个人

- 每种菜 $i$ 有三个属性 $p_i,s_i,b_i$

- 每个人 $j$ 有两个属性 $inc_j,pref_j$

- 一个人 $j$ 能品尝菜 $i$ 当且仅当 $p_i\le inc_j\le s_i$ 且 $|b_i-pref_j|\le inc_j-p_i$

- 求每个人能品尝多少种菜

- $1\le n,m\le 10^5$ ，其他数据均为 $10^9$ 级别

算法：扫描线 + 树状数组
=

- 此题有一个非常套路的 $O((n+m)\log^2n)$ 做法（ CDQ 分治）和一个比较妙的官方题解做法，复杂度少一个 $\log$ ，下面只讨论后者

- 首先， $|b_i-pref_j|\le inc_j-p_i$ 就相当于 $b_i-pref_j\le inc_j-p_i$ 且 $pref_j-b_i\le inc_j-p_i$

- 把问题抽象到二维平面上，一个点 $(x,y)$ 表示一个人的 $inc$ 为 $x$ ， $pref$ 为 $y$

- 整理一下得出条件

- （1） $p_i\le inc_j\le s_i$

- （2） $inc_j+pref_j\ge b_i+p_i$

- （3） $pref_j-inc_j\le b_i-p_i$

- 这相当于点 $(inc_j,pref_j)$ 位于如下图所示的三角形内（含边界）

![(p[i],b[i])(s[i],b[i]+p[i]-s[i])(s[i],b[i]+s[i]-p[i])三点构成的三角形](https://img-blog.csdnimg.cn/20190326213144721.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3h5ejMyNzY4,size_16,color_FFFFFF,t_70)

- 考虑扫描线，把所有人离线按照 $inc$ 排序，按照 $x$ 坐标递增的顺序扫描，当扫到 $b_i$ 时加入第 $i$ 个三角形的影响，扫到 $s_i+1$ 时去除第 $i$ 个三角形的影响

- 我们对于每个人 $(inc_j,pref_j)$ 需要询问这个点在多少个三角形内

- 考虑差分，也就是说当 $x=x_0$ 时，如果直线 $x=x_0$ 经过了第 $i$ 个三角形且 $y$ 坐标范围 $[l,r]$ 被第 $i$ 个三角形覆盖，则在 $l$ 处贡献 $1$ ， $r+1$ 处贡献 $-1$ ，则当 $inc_j=x_0$ 时，单点询问 $(inc_j,pref_j)$ 转化成询问前缀和 $pref_j$

- 于是我们考虑第 $i$ 个三角形的影响，可以看成

- （1）在直线 $x+y=b_i+p_i$ 上贡献 $1$

- （2）在直线 $y-x=b_i-p_i+1$ 上贡献 $-1$

- 消除第 $i$ 个三角形的影响则同理

- 询问相当于询问横坐标为 $inc_j$ ，纵坐标不超过 $pref_j$ 的贡献之和

- 用两个数据结构 $A$ 和 $B$ 分别记录 $x+y$ 和 $y-x$ 的贡献

- 直线 $x+y=k$ 能为 $(inc_j,pref_j)$ 贡献当且仅当 $k\le inc_j+pref_j$

- 所以加入第 $i$ 个三角形时，在数据结构 $A$ 的 $b_i+p_i$ 处进行单点加 $1$

- 直线 $y-x=k$ 能为询问贡献当且仅当 $k\le pref_j-inc_j$

- 所以加入第 $i$ 个三角形时，在数据结构 $B$ 的 $b_i-p_i+1$ 处进行单点加 $1$

- 这样第 $j$ 个询问的答案就是当 $x$ 扫描到 $inc_j$ 时，数据结构 $A$ 的前缀和 $inc_j+pref_j$ 减去数据结构 $B$ 的前缀和 $pref_j-inc_j$

- 可以用树状数组等实现

- 复杂度 $O((n+m)\log(n+m))$

代码
=

```cpp
#include <bits/stdc++.h>

// 20030830

inline int read()
{
	int res = 0; bool bo = 0; char c;
	while (((c = getchar()) < '0' || c > '9') && c != '-');
	if (c == '-') bo = 1; else res = c - 48;
	while ((c = getchar()) >= '0' && c <= '9')
		res = (res << 3) + (res << 1) + (c - 48);
	return bo ? ~res + 1 : res;
}

const int N = 1e5 + 5, M = N << 2;

int n, m, p[N], s[N], b[N], inc[N], pref[N], tot, a[M], A[M], B[M], cnt, ans[N];

struct node
{
	int tm, x, y, op, id;
} que[M];

inline bool comp(node a, node b)
{
	return a.tm < b.tm || (a.tm == b.tm && a.op < b.op);
}

void changeA(int x, int v)
{
	for (; x <= tot; x += x & -x)
		A[x] += v;
}

int askA(int x)
{
	int res = 0;
	for (; x; x -= x & -x)
		res += A[x];
	return res;
}

void changeB(int x, int v)
{
	for (; x <= tot; x += x & -x)
		B[x] += v;
}

int askB(int x)
{
	int res = 0;
	for (; x; x -= x & -x)
		res += B[x];
	return res;
}

int main()
{
	n = read(); m = read();
	for (int i = 1; i <= n; i++) p[i] = read();
	for (int i = 1; i <= n; i++) s[i] = read();
	for (int i = 1; i <= n; i++) b[i] = read();
	for (int i = 1; i <= m; i++) inc[i] = read();
	for (int i = 1; i <= m; i++) pref[i] = read();
	for (int i = 1; i <= n; i++)
		a[++tot] = p[i] + b[i], a[++tot] = b[i] - p[i] + 1;
	for (int i = 1; i <= m; i++)
		a[++tot] = inc[i] + pref[i], a[++tot] = pref[i] - inc[i];
	std::sort(a + 1, a + tot + 1);
	int tt = std::unique(a + 1, a + tot + 1) - a - 1;
	tot = tt;
	for (int i = 1; i <= n; i++)
		que[++cnt] = (node) {p[i], p[i], b[i], 1, 0},
		que[++cnt] = (node) {s[i] + 1, p[i], b[i], -1, 0};
	for (int i = 1; i <= m; i++)
		que[++cnt] = (node) {inc[i], inc[i], pref[i], 2, i};
	std::sort(que + 1, que + cnt + 1, comp);
	for (int i = 1; i <= cnt; i++)
		if (que[i].op <= 1)
		{
			changeA(std::lower_bound(a + 1, a + tot + 1,
				que[i].x + que[i].y) - a, que[i].op);
			changeB(std::lower_bound(a + 1, a + tot + 1,
				que[i].y - que[i].x + 1) - a, que[i].op);
		}
		else ans[que[i].id] = askA(std::lower_bound(a + 1, a + tot + 1,
			que[i].x + que[i].y) - a) -
			askB(std::lower_bound(a + 1, a + tot + 1,
			que[i].y - que[i].x) - a);
	for (int i = 1; i <= m; i++) printf("%d ", ans[i]);
	return puts(""), 0;
}
```

---

## 作者：wsyhb (赞：4)

## 前言

没人写 CDQ 分治，那就让我来补一发。

## 题解

经典套路——看到绝对值就分类讨论（尤其是在绝对值符号比较少的时候）。

那么，题目所求的第 $j$ 个答案即为下面**两个方程组中 $i$ 的取值个数之和**：

$$\begin{cases}
b_i+p_i \le inc_j+pref_j\\
s_i \ge inc_j\\
b_i \ge pref_j
\end{cases}$$

$$\begin{cases}
p_i-b_i \le inc_j-pref_j\\
s_i \ge inc_j\\
b_i<pref_j
\end{cases}$$

（对题目条件的式子进行绝对值的讨论以及移项即可得到）

容易看出这是**三维偏序**，于是直接上 **bitset，CDQ 分治或 KD-Tree** 即可。

不会的请左转模板区：[洛谷 P3810 【模板】三维偏序（陌上花开）](https://www.luogu.com.cn/problem/P3810)，这里只提一些细节问题。

------------

为了便于处理，可将上述两个方程组中的 $\ge$ 和 $<$ 都变成 $\le$，得到如下方程组：

$$\begin{cases}
b_i+p_i \le inc_j+pref_j\\
-s_i \le -inc_j\\
-b_i \le -pref_j
\end{cases}$$

$$\begin{cases}
p_i-b_i \le inc_j-pref_j\\
-s_i \le -inc_j\\
b_i+1 \le pref_j
\end{cases}$$

------------

实现时需**注意某一维相同的情况**——笔者使用的是 CDQ 分治，具体包括：第一维的比较函数，第二维的归并排序。

你也可以将上述 $\le$ 改成 $<$ 而进行其他处理。

而第三维只需注意：需要提前**离散化**，以使用**树状数组**。

------------

使用 CDQ 分治，总时间复杂度为 $O((n+m)\log^2{(n+m)})$。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt;
const int max_n=1e5+5;
int p[max_n],s[max_n],b[max_n];
const int max_m=1e5+5;
int inc[max_m],pref[max_m],ans[max_m];
const int max_cnt=2e5+5;
struct Triplet
{
	int x,y,z,id;
	inline Triplet(int p=0,int q=0,int r=0,int k=0)
	{
		x=p,y=q,z=r,id=k;
	}
}t[max_cnt],now[max_cnt];
inline bool operator < (const Triplet &a,const Triplet &b)
{
	return a.x!=b.x?a.x<b.x:a.id<b.id;
}
const int max_R=2e5+5;
int Hash[max_R],R;
namespace BIT
{
	int val[max_R];
	inline void modify(int k,int v)
	{
		for(int i=k;i<=R;i+=i&(-i))
			val[i]+=v;
	}
	inline int query(int k)
	{
		int res=0;
		for(int i=k;i>0;i-=i&(-i))
			res+=val[i];
		return res;
	}
}
void CDQ(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	int k=l;
	for(int i=l,j=mid+1;i<=mid||j<=r;)
	{
		if(i<=mid&&(j>r||t[i].y<=t[j].y))
		{
			if(!t[i].id)
				BIT::modify(t[i].z,1);
			now[k++]=t[i++];
		}
		else
		{
			if(t[j].id)
				ans[t[j].id]+=BIT::query(t[j].z);
			now[k++]=t[j++];
		}
	}
	for(int i=l;i<=mid;++i)
	{
		if(!t[i].id)
			BIT::modify(t[i].z,-1);
	}
	for(int i=l;i<=r;++i)
		t[i]=now[i];
}
inline void solve()
{
	sort(t+1,t+cnt+1);
	for(int i=1;i<=cnt;++i)
		Hash[i]=t[i].z;
	sort(Hash+1,Hash+cnt+1);
	R=unique(Hash+1,Hash+cnt+1)-Hash-1;
	for(int i=1;i<=cnt;++i)
		t[i].z=lower_bound(Hash+1,Hash+R+1,t[i].z)-Hash;
	CDQ(1,cnt);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",p+i);
	for(int i=1;i<=n;++i)
		scanf("%d",s+i);
	for(int i=1;i<=n;++i)
		scanf("%d",b+i);
	for(int i=1;i<=m;++i)
		scanf("%d",inc+i);
	for(int i=1;i<=m;++i)
		scanf("%d",pref+i);
	cnt=n+m;
	for(int i=1;i<=n;++i)
		t[i]=Triplet(b[i]+p[i],-s[i],-b[i],0);
	for(int i=1;i<=m;++i)
		t[n+i]=Triplet(inc[i]+pref[i],-inc[i],-pref[i],i);
	solve();
	for(int i=1;i<=n;++i)
		t[i]=Triplet(p[i]-b[i],-s[i],b[i]+1,0);
	for(int i=1;i<=m;++i)
		t[n+i]=Triplet(inc[i]-pref[i],-inc[i],pref[i],i);
	solve();
	for(int i=1;i<=m;++i)
		printf("%d%c",ans[i],i<m?' ':'\n');
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1139F)

## 思路

我的 $\rm cdq$ 分治比较奇怪，码比较长，但是很好理解。

首先这个题目显然是三维偏序，绝对值拆拆就好了。

我们先讨论 $b_i \ge pref_j$ 的情况，相当于满足三个限制：

$$b_i \ge pref_j$$

$$b_i+p_i \le inc_j+pref_j$$

$$inc_j \le s_i$$


这个东西比较难受，考虑取反一些值，然后全部都变成 $\le$ 或 $\ge$。

$$-b_i \le -pref_j$$

$$b_i+p_i \le inc_j+pref_j$$

$$-s_i \le -inc_j$$

直接三维偏序就好了，另一种情况同理。

接下来就是 $\rm cdq$ 的实现问题了。

先按第一维从小到大排序。

然后分治，对左右区间分别按第二维从小到大排序。

然后树状数组维护第三维坐标，直接来就好了。

但是真的吗？

右区间有木有可能对左区间产生贡献呢。

显然有可能，考虑有一段区间 $(s,t)$，这些数的第一维值相等，且 $s \le mid \le mid+1 \le t$。

我的处理方式就是直接把这些数拎出来，然后直接算右边对左边的贡献。

可能处理方式比较傻，但是确实很好理解。

时间复杂度 $\mathcal O((n+m) \log^2 (n+m))$。

据说有单 $\log$ 二维数点，可是我不想用脑子。

## 代码

贴一个 $\rm cdq$ 部分代码吧：

```cpp
inline void cdq(int l,int r){
    if (l==r) return;
    cdq(l,mid);cdq(mid+1,r);
    sort(q+l,q+mid+1,cmp2);
    sort(q+mid+1,q+r+1,cmp2);
    int j=l;
    for (int i=mid+1;i<=r;++i){
        while (q[i].b>=q[j].b && j<=mid)
            if (!q[j].id) T.update(q[j].c,1),++j;
            else ++j;
        if (q[i].id) ans[q[i].id]+=T.query(q[i].c);
    }
    for (int i=l;i<j;++i) if (!q[i].id) T.update(q[i].c,-1);
        
    int cnt1=0,Min=9e18;
    for (int i=mid+1;i<=r;++i) Min=min(Min,q[i].s);
    for (int i=mid+1;i<=r;++i) if (q[i].s==Min) Q[++cnt1]=q[i];
    int cnt2=0,Max=-9e18;
    for (int i=l;i<=mid;++i) Max=max(Max,q[i].s);
    for (int i=l;i<=mid;++i) if (q[i].s==Max) P[++cnt2]=q[i];
    if (Min!=Max) return;

    j=1;
    for (int i=1;i<=cnt2;++i){
        while (P[i].b>=Q[j].b && j<=cnt1)
            if (!Q[j].id) T.update(Q[j].c,1),++j;
            else ++j;
        if (P[i].id) ans[P[i].id]+=T.query(P[i].c);
    }
    for (int i=1;i<j;++i) if (!Q[i].id) T.update(Q[i].c,-1);
}
```

---

## 作者：cike_bilibili (赞：1)

拆掉绝对值符号变成两个四维偏序的子问题，cdq 分治即可。特别地可以使用树状数组减少常数，时间复杂度 $O((n+m)\log^3(n+m))$。

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
struct Dish{
	int p,s,b;
}d[100005];
struct Person{
	int inc,pref;
}p[100005];
struct node{
	int d[4],val,opt,id;
	bool operator<(const node &a)const{if(d[0]==a.d[0])return val>a.val;return d[0]>a.d[0];}
}a[500005],b[4][500005];
int top;
int ans[100005];
struct BIT{
	const int V=200000;
	int tree[200005];
	int lowbit(int i){
		return i&-i;
	}
	void add(int pos,int val){
		for(int i=pos;i<=V;i+=lowbit(i))tree[i]+=val;
	}
	int ask(int l,int r){
		int ans=0;
		for(int i=r;i;i-=lowbit(i))ans+=tree[i];
		for(int i=l-1;i;i-=lowbit(i))ans-=tree[i];
		return ans;
	}
}T;
int stk[500005],tot;
void cdq(int d,int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	cdq(d,l,mid),cdq(d,mid+1,r);
	for(int i=l;i<=r;i++)a[i].d[d]=i>mid;
	for(int i=l,j=l,k=mid+1,sum=0;i<=r;i++){
		if((j<=mid&&(a[j].d[d+1]>a[k].d[d+1]||a[j].d[d+1]==a[k].d[d+1]&&a[j].val>=a[k].val))||k>r){
			if(d==1&&!a[j].d[0]&&!a[j].d[1]&&a[j].val)T.add(a[j].d[3],1),stk[++tot]=a[j].d[3];
//			if(d==2)cout<<a[j].id<<" "<<a[j].d[0]<<' '<<a[j].d[1]<<' '<<a[j].d[2]<<'\n';
			b[d][i]=a[j++];
		}else{
			if(d==1&&a[k].d[0]&&a[k].d[1])ans[a[k].id]+=T.ask(a[k].d[3],200000);
			b[d][i]=a[k++];
		}
	}
	while(tot)T.add(stk[tot--],-1);
	for(int i=l;i<=r;i++)a[i]=b[d][i];
	if(d<1){
		cdq(d+1,l,r);
		for(int i=l;i<=r;i++)a[i]=b[d][i];
	}
}
struct lisan{
	int val,id;
	bool operator<(const lisan &a)const{return val<a.val;}
}li[500005];
int lcnt=0;
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)d[i].p=read();
	for(int i=1;i<=n;i++)d[i].s=read();
	for(int i=1;i<=n;i++)d[i].b=read();
	for(int i=1;i<=m;i++)p[i].inc=read();
	for(int i=1;i<=m;i++)p[i].pref=read();//input 
	//1st 
	for(int i=1;i<=n;i++)a[++top]={d[i].s,-d[i].p,d[i].b,-d[i].b-d[i].p,1,0,0},li[top]={-d[i].b-d[i].p,top};
	for(int i=1;i<=m;i++)a[++top]={p[i].inc,-p[i].inc,p[i].pref,-p[i].pref-p[i].inc,0,1,i},li[top]={-p[i].pref-p[i].inc,top};
	sort(li+1,li+1+top);
	li[0].val=-2e9-5;
	for(int i=1;i<=top;i++){
		if(li[i].val>li[i-1].val)++lcnt;
		a[li[i].id].d[3]=lcnt;
	}	
	sort(a+1,a+1+top);
	cdq(0,1,top);
	top=0;
	lcnt=0;
	for(int i=1;i<=n;i++)a[++top]={d[i].s,-d[i].p,-d[i].b,d[i].b-d[i].p,1,0,0},li[top]={d[i].b-d[i].p,top};
	for(int i=1;i<=m;i++)a[++top]={p[i].inc,-p[i].inc,-p[i].pref+1,p[i].pref-p[i].inc,0,1,i},li[top]={p[i].pref-p[i].inc,top};
	sort(li+1,li+1+top);
	li[0].val=-2e9-5;
	for(int i=1;i<=top;i++){
		if(li[i].val>li[i-1].val)++lcnt;
		a[li[i].id].d[3]=lcnt;
	}	
	sort(a+1,a+1+top);
	cdq(0,1,top);
	for(int i=1;i<=m;i++)cout<<ans[i]<<' ';
	return 0;
}
/*
p s b

2 2 2
1 4 1
3 4 1
2 1
2 2
3 4
*/
```

---

## 作者：幻影星坚强 (赞：1)

补一发无脑二维数点做法。

对于每个人就相当于要满足两个条件：

- $ \left| b - pref\right| + p \leq inc$

- $inc \leq s$

于是我们考虑对绝对值分情况讨论，即 $b - pref + p \leq inc$ 与 $pref - b + p \leq inc$。

统计答案时，对于 $b \leq pref$ 的菜，我们要询问满足 $- b + p \leq inc - pref$ 与 $inc \leq s$的答案总和，也就是将每个菜当成 $(p - b, s)$ 的点，询问 $(1, inc)$ 到 $(inc - pref, s_{max})$ 这一矩形的点数和。对于其他的菜，要询问满足 $b + p \leq inc + pref$ 与 $inc \leq s$ 的答案总和。，也就是将每个菜当成 $(p + b, s)$ 的点，询问 $(1, inc)$ 到 $(inc + pref, s_{max})$ 这一矩形的点数和。

所以我们直接开两个树套树，在一开始把所有菜放到一颗树套树上，并把点当成 $(p + b, s)$ ，之后将菜和人分别按 $b$ 与 $pref$ 排序，按 $pref$ 顺序从小到大询问每个人的答案，并且将所有 $b \leq pref$ 的菜扔到另一颗树套树上，每个菜变成 $(p - b, s)$。之后将两颗树套树上的答案相加即可。

时间复杂度 $O((n+m)\log^2n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int n, m;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read()
{
	register int x = 0;
	register char a = getchar();
	while (a < '0' || a > '9')  a = getchar();
	while (a >= '0'&& a <= '9') x = x * 10 + (a ^ 48), a = getchar();
	return x;
}
struct tree_in_tree
{
	int bit[N];
	struct t
	{
		int ch[2];
		int val;
	}tree[10500000];
	int root[N * 3], num;
	void opt1(int &o, int l, int r, int i, int w)
	{
		if(o == 0)
		o = ++ num;
		tree[o].val += w;
		if(l == r)return;
		int mid = (l + r) >> 1;
		if(mid >= i) opt1(tree[o].ch[0], l, mid, i, w);
		else opt1(tree[o].ch[1], mid + 1, r, i, w);
	}
	
	void add(int pos, int y, int val)
	{
		if(pos == 0)return;
		for (; pos <= 3 * n + 1; pos += pos & -pos)opt1(root[pos], 1, 3 * n + 1, y, val);
	}
	
	int to2[30][30], num2;
	int opt2(int now, int l, int r, int L, int R)
	{
		if(R < L)return 0;
		if(l >= L && r <= R)
    		{
			int re = 0;
			for (int i = 1; i <= num2; ++ i)
			re += tree[to2[now][i]].val;
			return re;
		}
		int mid = (l + r) >> 1;
		int ans = 0;
		if(mid >= L)
		{
			for (int i = 1; i <= num2; ++ i)
			to2[now + 1][i] = tree[to2[now][i]].ch[0];
			ans += opt2(now + 1, l, mid, L, R);
		}
		if(mid < R)
		{
			for (int i = 1; i <= num2; ++ i)
			to2[now + 1][i] = tree[to2[now][i]].ch[1];
			ans += opt2(now + 1, mid + 1, r, L, R);
		}
		return ans;
	}
	
	int que(int l, int r, int L, int R)
	{
		if(r < l)return 0;
		num2 = 0;
		if(r >= 0)
		for (int i = r; i; i -= i & -i)to2[0][++ num2] = root[i];
		return opt2(0, 1, 3 * n + 1, L, R);
	}
}t1, t2;
struct dish
{
	int p, s, b;
}d[N];
struct person
{
	int ids, inc, pref;
}p[N];
int nums[N];
bool pd1(person i, person j)
{
	return i.pref < j.pref;
}
bool pd2(dish i, dish j)
{
	return i.s < j.s;
}
bool pd3(int i, int j)
{
	return d[i].b < d[j].b;
}
int val[N * 3];
int ans[N];
int main()
{
	n = read();
	m = read();
	for (int i = 1; i <= n; ++ i)
	{
		nums[i] = i;
		d[i].p = read();
	}
	for (int i = 1; i <= n; ++ i)
	{
		d[i].s = read();
	}
	for (int i = 1; i <= n; ++ i)
	{
		d[i].b = read();
		val[i * 3 - 2] = d[i].s;
		val[i * 3 - 1] = d[i].p + d[i].b;
		val[i * 3] = d[i].p - d[i].b;
	}
	sort(val + 1, val + 1 + 3 * n);
	for (int i = 1; i <= m; ++ i)
	{
		p[i].ids = i;
		p[i].inc = read();
	}
	for (int i = 1; i <= m; ++ i)
	{
		p[i].pref = read();
	}
	sort(p + 1, p + 1 + m, pd1);
	sort(d + 1, d + 1 + n, pd2);
	sort(nums + 1, nums + 1 + n, pd3);
	for (int i = 1; i <= n; ++ i)
	{
		int xx = lower_bound(val + 1, val + 1 + 3 * n, d[i].b + d[i].p) - val;
		int yy = lower_bound(val + 1, val + 1 + 3 * n, d[i].s) - val;
		t1.add(xx, yy, 1);
	}
	int now = 1;
	for (int i = 1; i <= m; ++ i)
	{
		while(now <= n && d[nums[now]].b < p[i].pref)
		{
			int xx = lower_bound(val + 1, val + 1 + 3 * n, d[nums[now]].p + d[nums[now]].b) - val;
			int yy = lower_bound(val + 1, val + 1 + 3 * n, d[nums[now]].s) - val;
			t1.add(xx, yy, -1);
			xx = lower_bound(val + 1, val + 1 + 3 * n, - d[nums[now]].b + d[nums[now]].p) - val;
			t2.add(xx, yy, 1);
			++ now;
		}
		int xx = lower_bound(val + 1, val + 1 + 3 * n, p[i].inc + p[i].pref + 1) - val;
		-- xx;
		int yy = lower_bound(val + 1, val + 1 + 3 * n, p[i].inc) - val;
		ans[p[i].ids] += t1.que(1, xx, yy, 3 * n + 1);
		xx = lower_bound(val + 1, val + 1 + 3 * n, p[i].inc - p[i].pref + 1) - val;
		-- xx;
		ans[p[i].ids] += t2.que(1, xx, yy, 3 * n + 1);
	}
	for (int i = 1; i <= m; ++ i)
	printf("%d ", ans[i]);
}
```


---

## 作者：xfrvq (赞：0)

记 $inc$ 为 $x$，$pref$ 为 $y$。直接拆绝对值，$|b_i-y_j|\le x_j-p_i$ 转化为 $b_i+p_i\le x_j+y_j,b_i-p_i\ge y_j-x_j$。

直接做三维数点是 $O(n\log^2n)$ 的。考虑优化。

+ $b_i+p_i\le x_j+y_j$ 即点 $(x_j,y_j)$ 在直线 $y=-x+b_i+p_i$ 上方（下图红色线段）。
+ $b_i-p_i\ge y_j-x_j$ 即点 $(x_j,y_j)$ 在直线 $y=x+b_i-p_i$ 下方（下图蓝色线段）。

![](https://cdn.luogu.com.cn/upload/image_hosting/w6i54ubu.png)

现在即有若干如图直角三角形，询问每个点在几个三角形内。

+ 数一个点上面蓝色线段数（包括穿过它的），就是它在黄色与灰色部分总出现次数。
+ 数一个点上面红色线段数（不包括穿过它的），就是它在灰色部分出现次数。

二者的差即是答案。现在是普通二维数点，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n,m,p[N],s[N],b[N],X[N],Y[N],ans[N];
vector<int> V;
vector<tuple<int,int,int>> P;

struct BIT{
	int T[N * 4];
	
	void upd(int p,int x){ for(;p < N * 4;p += p & -p) T[p] += x; }
	
	int qry(int p,int s = 0){ for(;p;p &= p - 1) s += T[p]; return s; }
} T[2];

#define val(x) lower_bound(begin(V),end(V),x) - begin(V) + 1

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i) scanf("%d",p + i),P.emplace_back(p[i],-1,i);
	for(int i = 1;i <= n;++i) scanf("%d",s + i),P.emplace_back(s[i],1,i);
	for(int i = 1;i <= n;++i) scanf("%d",b + i),V.push_back(b[i] + p[i]),V.push_back(b[i] - p[i] + 1);
	for(int i = 1;i <= m;++i) scanf("%d",X + i),P.emplace_back(X[i],0,i);
	for(int i = 1;i <= m;++i) scanf("%d",Y + i),V.push_back(X[i] + Y[i]),V.push_back(Y[i] - X[i]);
	ranges::sort(P),ranges::sort(V);
	for(auto[x,o,i] : P){
		if(o) T[0].upd(val(b[i] + p[i]),-o),T[1].upd(val(b[i] - p[i] + 1),-o);
		else ans[i] = T[0].qry(val(X[i] + Y[i])) - T[1].qry(val(Y[i] - X[i]));
	}
	for(int i = 1;i <= m;++i) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Inzaghi_Luo (赞：0)

### 分析
题目中如此多的不等号，直接想偏序相关算法。把式子展开，得到四个式子。但是可以发现，其中 $p_i \leq inc_j$ 其实是可以省略的，因为 $|b_i-pref_j|+p_i \leq inc_j$ 成立，那么上面的式子一定成立。因此剩下三维偏序，用 CDQ 分治做就好。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
int p[MAXN], s[MAXN], b[MAXN], inc[MAXN], pref[MAXN];
int lsh[MAXN << 1], _;
struct D{
	int x, y, z, id;
}d[MAXN << 1], e[MAXN << 1];
bool cmp(D a, D b){
	if(a.x == b.x) return a.id < b.id;
	return a.x < b.x;
}
int ft[MAXN];
int lowbit(int x){
	return x & (-x);
}
void change(int x, int y){
	for(int i = x;i <= _;i += lowbit(i)) ft[i] += y;
}
int query(int x){
	int ans = 0;
	for(int i = x;i;i -= lowbit(i)) ans += ft[i];
	return ans;
}
int ans[MAXN];
void cdq(int l, int r){
	if(l == r) return ;
	int mid = l + r >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	for(int i = l, j = mid + 1, k = l;k <= r;k++){
		if(j > r || (i <= mid && (d[i].y < d[j].y || d[i].y == d[j].y && d[i].id < d[j].id))){
			if(!d[i].id) change(d[i].z, 1);
			e[k] = d[i++];
		}
		else{
			if(d[j].id) ans[d[j].id] += query(d[j].z);
			e[k] = d[j++];
		}
	}
	for(int i = l;i <= mid;i++) if(!d[i].id) change(d[i].z, -1);
	for(int i = l;i <= r;i++) d[i] = e[i]; 
}
int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++) scanf("%d", &p[i]);
	for(int i = 1;i <= n;i++) scanf("%d", &s[i]);
	for(int i = 1;i <= n;i++) scanf("%d", &b[i]);
	for(int i = 1;i <= m;i++) scanf("%d", &inc[i]);
	for(int i = 1;i <= m;i++) scanf("%d", &pref[i]);
	for(int i = 1;i <= n;i++) lsh[++_] = -s[i];
	for(int i = 1;i <= m;i++) lsh[++_] = -inc[i];
	sort(lsh + 1, lsh + _ + 1);
	_ = unique(lsh + 1, lsh + _ + 1) - lsh - 1;
	int num = 0;
	for(int i = 1;i <= n;i++){
		d[++num] = (D){b[i] + p[i], p[i] - b[i], lower_bound(lsh + 1, lsh + _ + 1, -s[i]) - lsh, 0};
	}
	for(int i = 1;i <= m;i++){
		d[++num] = (D){inc[i] + pref[i], inc[i] - pref[i], lower_bound(lsh + 1, lsh + _ + 1, -inc[i]) - lsh, i};
	}
	sort(d + 1, d + num + 1, cmp);
	cdq(1, num);
	for(int i = 1;i <= m;i++) printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)


观察到这个形式，首先想到了偏序。但是第二个偏序带绝对值，而且两边都有人和菜，不好处理。

所以考虑分类讨论拆开绝对值，再把人的属性放在一边、菜的属性放在一边。但是由于有分讨的限制，会从二位偏序变成三维偏序。

分类讨论之后，整理一下可得以下两种限制：

- $\begin{cases}b_i+p_i \leq pref_j+inc_j\\p_i \leq	inc_j \leq s_i\\b_i \geq pref_j\end{cases}$

- $\begin{cases}p_i \leq inc_j \leq s_i\\p_i-b_i\geq inc_j-pref_j\\b_i<pref_j\end{cases}$

这就是一个经典的三维偏序问题啦。CDQ 分治维护一下即可，复杂度 $O(n \log^2 n)$。

如果为了代码实现简单，可以把式子都转化成 $<$ 和 $\leq$ 连接的，然后封装 CDQ 之后跑两遍。

---

## 作者：zztqwq (赞：0)

注意到 $|b_i-pref_j|\ge 0$，所以只要满足 $inc_j-p_i\ge |b_i-pref_j|$ 就一定满足 $inc_j\ge p_i$。

绝对值不好处理，把他拆成两个：

$$
\begin{cases}
inc_j\le s_i\\
inc_j-p_i\ge b_i-pref_j\\
inc_j-p_i\ge pref_j-b_i
\end{cases}
$$

整理一下：

$$
\begin{cases}
-inc_j\ge -s_i\\
inc_j+pref_j\ge b_i+p_i\\
inc_j-pref_j\ge p_i-b_i
\end{cases}
$$

直接 cdq 分治跑三维偏序即可，时间复杂度 $\mathcal O(n\log^2 n)$。

```cpp
const int N=2e5+10;
int p[N],s[N],b[N];
int inc[N],pref[N];
struct node{
	int x,y,z,tp;
}a[N];
bool cmp(node x,node y)
{
	if(x.x!=y.x)return x.x<y.x;
	return x.tp<y.tp;
}
bool cmp1(node x,node y)
{
	if(x.y!=y.y)return x.y<y.y;
	return x.tp<y.tp;
}
int t[N],cc=0;
struct bit{
	int c[N];
	bit(){memset(c,0,sizeof(c));}
	int query(int x){int ans=0;for(;x;x-=x&-x)ans+=c[x];return ans;}
	void modify(int x,int d){for(;x<=cc;x+=x&-x)c[x]+=d;}
}T;
int Ans[N];
void cdq(int L,int R)
{
	if(L>=R)return;int mid=(L+R)>>1;
	cdq(L,mid),cdq(mid+1,R);
	sort(a+L,a+mid+1,cmp1),sort(a+mid+1,a+R+1,cmp1);
	int j=L;
	for(int i=mid+1;i<=R;i++)
	{
		while(j<=mid&&a[j].y<=a[i].y)
		{
			if(!a[j].tp)T.modify(a[j].z,1);
			j++;
		}
		if(a[i].tp)Ans[a[i].tp]+=T.query(a[i].z);
	}
	for(int i=L;i<j;i++)if(!a[i].tp)T.modify(a[i].z,-1);
}
int main()
{
	int n=read(),m=read();
	for(int i=1;i<=n;i++)p[i]=read();
	for(int i=1;i<=n;i++)s[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=m;i++)inc[i]=read();
	for(int i=1;i<=m;i++)pref[i]=read();
	for(int i=1;i<=n;i++)t[++cc]=-s[i];
	for(int i=1;i<=m;i++)t[++cc]=-inc[i];
	sort(t+1,t+cc+1),cc=unique(t+1,t+cc+1)-t-1;
	int c=0;
	for(int i=1;i<=n;i++)c++,a[c].tp=0,a[c].x=b[i]+p[i],a[c].y=p[i]-b[i],a[c].z=-s[i];
	for(int i=1;i<=m;i++)c++,a[c].tp=i,a[c].x=inc[i]+pref[i],a[c].y=inc[i]-pref[i],a[c].z=-inc[i];
	for(int i=1;i<=c;i++)a[i].z=lower_bound(t+1,t+cc+1,a[i].z)-t;
	sort(a+1,a+c+1,cmp);
	
//	for(int i=1;i<=c;i++)printf("tp=%d, x=%d, y=%d, z=%d\n",a[i].tp,a[i].x,a[i].y,a[i].z);
	cdq(1,c);
	for(int i=1;i<=m;i++)printf("%d ",Ans[i]);
	return 0;
}
//zzt qwq
```

---

## 作者：meyi (赞：0)

一眼 CDQ 分治，然后发现是个裸扫描线+二维数点，就当成了树套树板子来写。

下文的所有值都是离散化后的，~~不然 $10^9$ 的数据范围显然过不了~~，相信能找到这题的人都知道离散化怎么写。

$p_i\le inc_j\le s_i$ 的条件直接使用扫描线就能满足，具体来说，在 $p_i$ 位置插入 $i$ 这个点，在 $inc_j$ 位置查询 $j$ 的答案，在 $s_i+1$ 位置删除 $i$ 这个点。

另一个条件 $|b_i-pref_j|\le inc_j-p_i$ 带个绝对值就有点棘手了，这个绝对值显然是要拆的，分类讨论一下。

- $b_i\ge pref_j$ 时，原式可化为 $b_i+p_i\le inc_j+pref_j$。

- $b_i< pref_j$ 时，原式可化为 $p_i-b_i\le inc_j-pref_j$。

显然统计答案是二维数点的形式，开两颗树套树，分别统计满足上面式子的点的数量即可。

时间复杂度 $O((n+m)\log^2n)$，最慢的点跑了 1949 ms，基本上是卡着过的，快读是肯定要加的，还得注意卡卡常。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=1e5+10;
static char pbuf[1000000],*p1=pbuf,*p2=pbuf,obuf[1000000],*o=obuf;
#define getchar() p1==p2&&(p2=(p1=pbuf)+fread(pbuf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (o-obuf<1000000)?(*o++=(x)):(fwrite(obuf,o-obuf,1,stdout),o=obuf,*o++=(x))
inline int qr(){
	ri in=0;register char ch;
	while(!isdigit(ch=getchar()));
	do in=(in<<1)+(in<<3)+(ch^48);while(isdigit(ch=getchar()));
	return in;
}
template<class T>
void qw(T out){
	if(out>9)qw(out/10);
	putchar(out%10|48);
}
struct flusher{~flusher(){fwrite(obuf,o-obuf,1,stdout);}}autoflush;
struct discretize{
	int b[maxn*3],bl;
	inline void insert(int k){
		b[++bl]=k;
	}
	inline void init(){
		sort(b+1,b+bl+1);
		bl=unique(b+1,b+bl+1)-b-1;
	}
	inline int query(int k){
		return lower_bound(b+1,b+bl+1,k)-b;
	}
}b1,b2,b3;
// b1: bi prefj
// b2: bi+pi incj+prefj
// b3: pi-bi incj-prefj
struct BIT_SGT{
	struct SGT{
		int ls,rs,sum;
	}t[maxn*100];
	int cnt;
	inline void push_up(int p){
		t[p].sum=t[t[p].ls].sum+t[t[p].rs].sum;
	}
	void insert(int &p,int l,int r,int k,int v){
		if(!p)p=++cnt;
		if(l==r){
			t[p].sum+=v;
			return;
		}
		ri mid=l+r>>1;
		if(k<=mid)insert(t[p].ls,l,mid,k,v);
		else insert(t[p].rs,mid+1,r,k,v);
		push_up(p);
	}
	typedef vector<int> vi;
	int query(vi &pt,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr){
			ri ret=0;
			for(auto p:pt)ret+=t[p].sum;
			return ret;
		}
		ri mid=l+r>>1,ret=0;
		if(ql<=mid){
			vi tmp=pt;
			for(auto &p:tmp)p=t[p].ls;
			ret+=query(tmp,l,mid,ql,qr);
		}
		if(qr>mid){
			vi tmp=pt;
			for(auto &p:tmp)p=t[p].rs;
			ret+=query(tmp,mid+1,r,ql,qr);
		}
		return ret;
	}
	#define lowbit(k) ((k)&(-k))
	int len1,len2,rt[maxn*3];
	inline void modify(int k1,int k2,int v){
		for(ri i=k1;i<=len1;i+=lowbit(i))insert(rt[i],1,len2,k2,v);
	}
	inline int query(int k1,int k2){
		vi tmp;
		for(ri i=k1;i;i^=lowbit(i))tmp.push_back(rt[i]);
		return query(tmp,1,len2,1,k2);
	}
}t1,t2;
struct node{
	int id,op,pos;
	inline bool operator<(const node &k)const{
		return pos!=k.pos?pos<k.pos:op<k.op;
	}
}q[maxn*3];
int ans[maxn],b[maxn],bp[maxn],cnt,inc[maxn],ip[maxn],m,n,p[maxn],pb[maxn],pi[maxn],pref[maxn],s[maxn];
int main(){
	n=qr(),m=qr();
	for(ri i=1;i<=n;++i)p[i]=qr();
	for(ri i=1;i<=n;++i)s[i]=qr();
	for(ri i=1;i<=n;++i){
		b[i]=qr();
		b1.insert(b[i]);
		b2.insert(b[i]+p[i]);
		b3.insert(p[i]-b[i]);
		q[++cnt]={i,1,p[i]};
		q[++cnt]={i,2,s[i]+1};
	}
	for(ri i=1;i<=m;++i)inc[i]=qr();
	for(ri i=1;i<=m;++i){
		pref[i]=qr();
		b1.insert(pref[i]);
		b2.insert(inc[i]+pref[i]);
		b3.insert(inc[i]-pref[i]);
		q[++cnt]={i,3,inc[i]};
	}
	b1.init();
	t1.len1=t2.len1=b1.bl;
	b2.init();
	t1.len2=b2.bl;
	b3.init();
	t2.len2=b3.bl;
	for(ri i=1;i<=n;++i){
		bp[i]=b2.query(b[i]+p[i]);
		pb[i]=b3.query(p[i]-b[i]);
		b[i]=b1.query(b[i]);
	}
	for(ri i=1;i<=m;++i){
		ip[i]=b2.query(inc[i]+pref[i]);
		pi[i]=b3.query(inc[i]-pref[i]);
		pref[i]=b1.query(pref[i]);
	}
	sort(q+1,q+cnt+1);
	for(ri i=1;i<=cnt;++i)
		if(q[i].op==1){
			t1.modify(b1.bl-b[q[i].id]+1,bp[q[i].id],1);
			t2.modify(b[q[i].id],pb[q[i].id],1);
		}
		else if(q[i].op==2){
			t1.modify(b1.bl-b[q[i].id]+1,bp[q[i].id],-1);
			t2.modify(b[q[i].id],pb[q[i].id],-1);
		}
		else{
			ri sum=0;
			sum+=t1.query(b1.bl-pref[q[i].id]+1,ip[q[i].id]);
			sum+=t2.query(pref[q[i].id]-1,pi[q[i].id]);
			ans[q[i].id]=sum;
		}
	for(ri i=1;i<=m;++i)qw(ans[i]),putchar(32);
	return 0;
}
```


---

