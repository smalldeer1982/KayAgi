# Alice and the Doll

## 题目描述

#### 题目大意

最近，爱丽丝得到了一个新玩偶。它甚至可以走路！

爱丽丝为玩偶建造了一个迷宫，并想对其进行测试。迷宫具有$n$行和$m$列。有$k$个障碍物，第$i$个障碍物位于单元格（$x_i,y_i$）上，这意味着第$x_i$个行与第$y_i$列相交的单元格上存在一个禁止通过的障碍物。

然而，玩偶有着缺陷。在**同一**单元格（包括起始单元格）中，它最多只能笔直走或右转**一次**。它无法进入有障碍物的单元格或走出迷宫的界限之外。

现在，爱丽丝正在控制娃娃的动作。她将玩偶放入单元格（$1,1$）（即迷宫的左上角）中。最初，玩偶的朝向从$(1,1)$向着$(1,m)$。她想让玩偶**恰好穿过一次所有**单元格而没有障碍，玩偶的行动可以在**任何**地方结束。爱丽丝的想法可以实现吗？

## 样例 #1

### 输入

```
3 3 2
2 2
2 1
```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 3 2
3 1
2 2
```

### 输出

```
No```

## 样例 #3

### 输入

```
3 3 8
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
```

### 输出

```
Yes```

# 题解

## 作者：Izayoi__Sakuya (赞：8)

### 昨天死于此题


模拟水平太烂 以至于一开始根本就没开出来他是个模拟题....Orz

观察一下题目性质 发现走的方向一定是一个向内螺旋的亚子

于是我们需要维护四个边界 即接下来走的地方不能超过这里

发现n和m都比较大 爆搜肯定不行

于是考虑必须要直接跳点  跳到障碍边界上

可以用一个vector来存每行每列 然后直接取最大最小

这时候我们去想一想当被一块障碍阻隔会发生什么

如果单有一块的话肯定就直接gg了

但如果有连续的一片 反而不会产生没有经过的点

直接判断不太好维护

于是换一种思路  统计走的点是否和需要走的点相等 

记得开long long 不然1e10会爆int

希望对来补这道题的人能一点帮助吧QwQ

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
long long n,m,k,sum,x,y,tmp,a,b,c,d;
//a,b,c,d四个边界
//sum 总共经过的点
vector<long long> p[100050],q[100050];
int main()
{
  cin>>n>>m>>k;
  for(int i=1;i<=k;i++)
  {
  	scanf("%d%d",&x,&y);
  	p[x].push_back(y);
  	q[y].push_back(x);
  }
  sum=1,x=y=1;tmp=m;
  for(int i=0;i<p[x].size();i++)
  if(p[x][i]>y)
  tmp=min(tmp,p[x][i]-1);
  sum+=tmp-x,a=x,y=tmp;//单独列出来是因为这里即便正前面就有岩石也是
  while(1)            //可以直接转向的
  {                  //而整个循环里放的则是转向的情况 如果直接被阻碍
  	tmp=n-c;    //就可以直接退出了
  	for(int i=0;i<q[y].size();i++)
  	if(q[y][i]>x)
  	tmp=min(tmp,q[y][i]-1);
	if(tmp==x) break;
	sum+=tmp-x,b=m-y+1,x=tmp;
	
	tmp=d+1;
	for(int i=0;i<p[x].size();i++)
	if(p[x][i]<y)
	tmp=max(tmp,p[x][i]+1);
	if(tmp==y) break;
	sum+=y-tmp,c=n-x+1,y=tmp;
	
	tmp=a+1;
	for(int i=0;i<q[y].size();i++)
	if(q[y][i]<x)
    tmp=max(tmp,q[y][i]+1);
	if(tmp==x) break;
	sum+=x-tmp,d=y,x=tmp;
	
	tmp=m-b;
	for(int i=0;i<p[x].size();i++)
	if(p[x][i]>y)
	tmp=min(tmp,p[x][i]-1);
	if(tmp==y)break;
	sum+=tmp-y,a=x,y=tmp;
  }
  if(sum==n*m-k) cout<<"YES";
  else cout<<"NO";
  return 0;
}

```


---

## 作者：学委 (赞：6)

每个点只能经过一次，所以路径围成的矩形是走不出去的，所以每次要尽量走得远，所以模拟：走到方向上最近的障碍物，然后右转再次尝试走，如果没有走动说明无法继续，统计走过的格子个数，检查是否走过格子数+障碍数=总格子数。

用vector存某行或某列上的障碍物，另用四个数字存路径边界，每次二分出最近的障碍物或边界。注意该方法没有考虑开始可以右转，所以要特判。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
template<typename T1, typename T2> void maxup(T1& h, T2 g) { if (h < g) h = g; }
template<typename T1, typename T2> void minup(T1& h, T2 g) { if (h > g) h = g; }
int getint() {
  int res = 0, neg = 0, ch = getchar();
  while (not(isdigit(ch) or ch == '-') and ch != EOF) ch = getchar();
  if (ch == '-') neg = 1, ch = getchar();
  while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
  return neg ? -res : res;
}
const int N = 2e5 + 10, E = 5e5 + 10;
const LL INF = 1e9;
vector<int> nnode[N], mnode[N];
int n, m, k;
struct P {
  int x, y;
} p[N];
bool cmpx(const P& h, const P& g) {
  return h.x < g.x;
}
bool cmpy(const P& h, const P& g) {
  return h.y < g.y;
}
int main() {
  scanf("%d %d %d", &n, &m, &k);
  int al = 0, ar = m + 1, au = 0, ad = n + 1;
  for (int i = 1; i <= n; ++i) nnode[i].push_back(0);
  for (int i = 1; i <= m; ++i) mnode[i].push_back(0);
  LL taken = 1;
  for (int i = 1; i <= k; ++i) scanf("%d %d", &p[i].x, &p[i].y);
  sort(p + 1, p + k + 1, cmpy);
  for (int i = 1; i <= k; ++i) nnode[p[i].x].push_back(p[i].y);
  sort(p + 1, p + k + 1, cmpx);
  for (int i = 1; i <= k; ++i) mnode[p[i].y].push_back(p[i].x);
  for (int i = 1; i <= n; ++i) nnode[i].push_back(m + 1);
  for (int i = 1; i <= m; ++i) mnode[i].push_back(n + 1);
  int x = 1, y = 1, d = 1;
  int lx = x, ly = y;
  while (true) {
    int l, r;
    if (d == 1 or d == 3) {
      l = 0, r = nnode[x].size() - 2;
      while (l < r) {
        int mid = (l + r + 1) / 2;
        if (y > nnode[x][mid]) l = mid;
        else r = mid - 1;
      }
    }
    else {
      l = 0, r = mnode[y].size() - 2;
      while (l < r) {
        int mid = (l + r + 1) / 2;
        if (x > mnode[y][mid]) l = mid;
        else r = mid - 1;
      }
    }
    // 在 l 和 l + 1 之间
    if (d == 1) {
      int ty = min(ar - 1, nnode[x][l + 1] - 1);
      taken += ty - y, au = x, y = ty; d = 2;
    } else if (d == 2) {
      int tx = min(ad - 1, mnode[y][l + 1] - 1);
      taken += tx - x, ar = y, x = tx, d = 3;
    } else if (d == 3) {
      int ty = max(al + 1, nnode[x][l] + 1);
      taken += y - ty, ad = x, y = ty, d = 4;
    } else {
      int tx = max(au + 1, mnode[y][l] + 1);
      taken += x - tx, al = y, x = tx, d = 1;
    }
    if (lx == x and ly == y and not(x == 1 and y == 1 and d == 2)) break;
    lx = x, ly = y;
  }
  if (taken + k == (LL)n * m) puts("Yes");
  else puts("No");
  return 0;
}


```

---

## 作者：邮差将军 (赞：3)

~~STL操作大赏题~~

首先用vector存每行每列的障碍物点，注意加入头和尾方便二分。然后贪心地每次走到头，即：走到更靠前的障碍物/上次走到的点。最后判断走过的点数和空的点数是否相同即可。注意特判最开始直接向下走的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 50;
int n, m, k;
long long num;

vector<int> row[MAXN], col[MAXN];

struct Node
{
    int x, y;
}nd[MAXN];

bool cmpx(const Node &a, const Node &b)
{
    return a.x < b.x;
}
bool cmpy(const Node &a, const Node &b)
{
    return a.y < b.y;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    num = 1LL * n * m - k;
    
    for(int i = 1; i <= n; i++) row[i].push_back(0);
    for(int i = 1; i <= m; i++) col[i].push_back(0);
    for(int i = 1; i <= k; i++) scanf("%d%d", &nd[i].x, &nd[i].y);
    sort(nd+1, nd+1+k, cmpy);
    for(int i = 1; i <= k; i++) row[nd[i].x].push_back(nd[i].y);
    sort(nd+1, nd+1+k, cmpx);
    for(int i = 1; i <= k; i++) col[nd[i].y].push_back(nd[i].x);
    for(int i = 1; i <= n; i++) row[i].push_back(m+1);
    for(int i = 1; i <= m; i++) col[i].push_back(n+1);
    
    
    if((col[1].size() == 0 && num == n) || (col[1].size() != 0 && num == col[1][1] - 1))
    {
        puts("Yes");
        return 0;
    }
    
    int x = 1, y = 1, d = 1;
    int lx = 1, ly = 1;
    long long sum = 1;
    int au = 2, ar = m, ad = n, al = 1;
    while(233)
    {
        if(d == 1)
        {
            auto it = lower_bound(row[x].begin(), row[x].end(), y);
            int ty = min(*it - 1, ar);
            ar = ty - 1;
            sum += ty - y;
            lx = x; ly = y; x = x; y = ty; d = 2;
        }
        else if(d == 2)
        {
            auto it = lower_bound(col[y].begin(), col[y].end(), x);
            int tx = min(*it - 1, ad);
            ad = tx - 1;
            sum += tx - x;
            lx = x; ly = y; x = tx; y = y; d = 3;
        }
        else if(d == 3)
        {
            auto it = lower_bound(row[x].begin(), row[x].end(), y); it--;
            int ty = max(*it + 1, al);
            al = ty + 1;
            sum += y - ty;
            lx = x; ly = y; x = x; y = ty; d = 4;
        }
        else if(d == 4)
        {
            auto it = lower_bound(col[y].begin(), col[y].end(), x); it--;
            int tx = max(*it + 1, au);
            au = tx + 1;
            sum += x - tx;
            lx = x; ly = y; x = tx; y = y; d = 1;
        }
        
        if(lx == x && ly == y) break;
    }
    if(sum == num) puts("Yes");
    else puts("No");
    
    return 0;
}
```

---

## 作者：ACAね (赞：3)

写一篇题解吧QwQ

我们考虑暴力模拟，

具体的，我们考虑每次跳到底，然后回退到第一个白点

然后检查之前是否没有黑点，并删掉之后的黑点并检查是否全是黑点。

维护一下边界

如果边界重合就说明可以了QwQ

为什么暴力检查黑点可以呢？因为黑点只有1e5个，而碰到白点就可以退出了，所以复杂度正确。

具体见代码

```cpp
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define IL inline
#define RG register
#define gi geti<int>()
#define gl geti<ll>()
#define gc getchar()
#define File(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
template<typename T>IL bool chkmax(T &x,const T &y){return x<y?x=y,1:0;}
template<typename T>IL bool chkmin(T &x,const T &y){return x>y?x=y,1:0;}
template<typename T>
IL T geti()
{
	RG T xi=0;
	RG char ch=gc;
	bool f=0;
	while(!isdigit(ch))ch=='-'?f=1:f,ch=gc;
	while(isdigit(ch))xi=xi*10+ch-48,ch=gc;
	return f?-xi:xi;
}
template<typename T>
IL void pi(T k,char ch=0)
{
	if(k<0)k=-k,putchar('-');
	if(k>=10)pi(k/10);
	putchar(k%10+'0');
	if(ch)putchar(ch);
}
const int N=1e5+7;
int n,m,k;
__gnu_pbds::cc_hash_table<int,bool>a[N];
int vis[N*2];
const int LEFT=1,RIGHT=2,UP=3,DOWN=4;
int up=1,down,lef,righ;
inline void check(int x,int y,int DIRECT)
{
	if(DIRECT==RIGHT)
	{
		for(int i=x;i<down;++i)
			for(int j=y;j<=righ;++j)
				if(a[i].find(j)==a[i].end())
					puts("No"),exit(0);
				else --vis[i],--vis[j+n];
	}	
	if(DIRECT==LEFT)
	{
		for(int i=x;i>up;--i)
			for(int j=y;j>=lef;--j)
				if(a[i].find(j)==a[i].end())
					puts("No"),exit(0);
				else --vis[i],--vis[j+n];
	}	
	if(DIRECT==UP)
	{
		for(int i=x;i>=up;--i)
			for(int j=y;j<righ;++j)
				if(a[i].find(j)==a[i].end())
					puts("No"),exit(0);
				else --vis[i],--vis[j+n];
	}	
	if(DIRECT==DOWN)
	{
//		cout<<"YKW"<<x<<" "<<lef<<endl<<y<<" "<<down<<endl;
		for(int i=x;i<=down;++i)
			for(int j=y;j>lef;--j)
				if(a[i].find(j)==a[i].end())
					puts("No"),exit(0);
				else --vis[i],--vis[j+n];
	}
}
inline void jump(int x,int y,int DIRECT=RIGHT)
{
//	cout<<x<<" "<<y<<endl;
//	cout<<up<<" "<<down<<" "<<lef<<" "<<righ<<endl;
//	cout<<x<<" "<<y<<endl;
//	cout<<DIRECT<<endl;
	if(up==down||lef==righ)puts("Yes"),exit(0);
	if(DIRECT==RIGHT)
	{
		y=--righ;
		if(vis[x])
		{
//			cout<<x<<" "<<y<<endl;
			while(a[x][y])--y;
//			cout<<x<<" "<<y<<endl;
			check(x,y+1,DIRECT);
			if(vis[x])puts("No"),exit(0);
		}
		chkmin(righ,y);
		jump(x,y,DOWN);
	}
	if(DIRECT==LEFT)
	{
		y=++lef;
//		cout<<x<<" "<<y<<endl;
		if(vis[x])
		{
			while(a[x][y])++y;//,cout<<x<<" "<<y<<endl;
			check(x,y-1,DIRECT);
			if(vis[x])puts("No"),exit(0);
		}
		chkmax(lef,y);
		jump(x,y,UP);
	}
	if(DIRECT==UP)
	{
		x=++up;
		if(vis[y+n])
		{
			while(a[x][y])++x;
//			cout<<"Add:y"<<y<<endl;
//			cout<<"VIS:"<<vis[y+n]<<endl;
			check(x-1,y,UP);
			if(vis[y+n])puts("No"),exit(0);
		}
		chkmax(up,x);
		jump(x,y,RIGHT);
	}
	if(DIRECT==DOWN)
	{
		x=--down;
//		cout<<x<<" "<<y<<endl;
//		cout<<"Vis:"<<vis[y+n]<<endl;
		if(vis[y+n])
		{
//			cout<<"Down:"<<down<<endl;
			while(a[x][y])--x;//,cout<<x<<" "<<y<<endl;
			check(x+1,y,DOWN);
//			cout<<"Vis:"<<vis[y+n]<<endl;
			if(vis[y+n])puts("No"),exit(0);
		}
		chkmin(down,x);
		jump(x,y,LEFT);
	}
}
int main(void)
{
	#ifndef ONLINE_JUDGE
//	File("");
	#endif
	n=gi,m=gi,k=gi;
	down=n+1,righ=m+1;
	for(int i=1;i<=k;++i)
	{
		int x=gi,y=gi;
		a[x][y]=1;
		++vis[x];++vis[y+n];
	}
/*	for(int i=1;i<=n;++i,putchar('\n'))
		for(int j=1;j<=m;++j)
		{
			if(a[i][j])putchar('*');
			else putchar('-');
		}*/
	jump(1,1);
	puts("YES");
	return 0;
}

```

---

## 作者：万弘 (赞：0)

考虑$n*m\le 10^{10}$无法接受,但$k\le 10^5$,所以应该创造与$k$相关的算法.

假设现在点为$(x,y)$,横坐标范围需要在$[minrow,maxrow]$之间,纵坐标需要在$[mincol,maxcol]$之间.  
考虑四个方向,以向右为例:  
找到最大的$y'$满足$y'> y,(x,y')$被禁止,且不存在$y< y''<y'$.(也就是$y'是$比$y$大的纵坐标最小的被禁止点,若没有,则$y'=maxcol$)对每行开一个`vector`存禁止点即可维护.找的过程可以二分,也可以直接扫一遍求.

能走完所有白色点,当且仅当走过的点$sum=n*m-k$,顺便维护$sum$就好了.时间复杂度$\mathcal O(n+m+k)$
```cpp
/**********/
#define MAXN 100011
std::vector<ll>row[MAXN],col[MAXN];
int main()
{
    ll n=read(),m=read(),k=read();
    for(ll i=1;i<=k;++i)
    {
        ll x=read(),y=read();
        row[x].push_back(y),col[y].push_back(x);
    }
    ll sum=1,x=1,y=1,end=m;
    for(auto pos:row[x])
        if(pos>y)umin(end,pos-1);
    sum+=end-x,y=end;
    ll maxrow=n,minrow=2,maxcol=end-1,mincol=1;
    while("red")
    {
        end=maxrow;
        for(auto pos:col[y])
            if(pos>x)umin(end,pos-1);
        if(end==x)break;
        sum+=end-x,x=end;maxrow=end-1;
        end=mincol;
        for(auto pos:row[x])
            if(pos<y)umax(end,pos+1);
        if(end==y)break;
        sum+=y-end,y=end;mincol=end+1;
        end=minrow;
        for(auto pos:col[y])
            if(pos<x)umax(end,pos+1);
        if(end==x)break;
        sum+=x-end,x=end;minrow=end+1;
        end=maxcol;
        for(auto pos:row[x])
            if(pos>y)umin(end,pos-1);
        if(end==y)break;
        sum+=end-y,y=end;maxcol=end-1;
    }
    puts(sum==n*m-k?"Yes":"No");
    return 0;
}
```

---

