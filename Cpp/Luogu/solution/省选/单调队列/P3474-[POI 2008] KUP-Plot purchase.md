# [POI 2008] KUP-Plot purchase

## 题目描述

Byteasar is going to buy an industrial plot.

His fortune is estimated at $k$ bythalers and this is exactly the amount    Byteasar would like to spend on the parcel.

Finding a parcel worth exactly $k$ bythalers, however, is not an easy task.

For this reason Byteasar is ready to buy a more expensive plot.

He considers taking out a loan. The Byteotian Credit Bank will grant him    a loan of up to $k$ bythalers. Thus, Byteasar can spend no more than $2k$    bythalers on the parcel and he would like to spend no less than $k$ bythalers.

The area in which Byteasar wants to buy his parcel is a square with side    length of $n$ metres. The current landlords have set up various prices per square metre. Byteasar has spoken to each one of them and has then prepared a price map    of the area. The map depicts the price of every metre by metre square. Clearly, there    are $n^2$ such squares. Now is the time to find the dream parcel. It has to be rectangular and consist of whole unit squares. Byteasar has already started looking for the plot on the map,    but after many hours he was still unable to find a suitable one. Be a chap and help him!

<Task> 

Write a programme that:

reads the numbers $k$ and $n$ from the standard input,  along with the price map of the area, determines a parcel with price in the interval $[k,2k]$ or states that no such parcel exists, writes out the result to the standard output.



## 说明/提示


给定 $k,n$ 和 $n\times n$ 的矩阵，求一个子矩形满足权值和在 $[k,2k]$ 之间。

$n<2000$，$1\le k\le10^9$，每个价格都是不大于$2 \times 10^9$ 的非负整数。

感谢@cn：苏卿念 提供的spj

## 样例 #1

### 输入

```
8 4
1 2 1 3
25 1 2 1
4 20 3 3
3 30 12 2```

### 输出

```
2 1 4 2```

# 题解

## 作者：kczno1 (赞：19)

首先一个格子如果权值$>2*k$是不能选的，如果在$[k,2*k]$是直接找到了答案的。

那么接下来的问题就是只能选$<k$的。


可以发现，存在一个子矩形权值和$>=k$是等价于存在答案的。

因为一个权值和$>2*k$的矩形一定可以找到一个子矩形权值和$>=k$且$<=2*k$。

因为变化是连续的，具体说就是考虑一行一行删，有一行$>2*k$就一格一格删。


那么只要找到权值和最大的子矩形就好了。

它一定是个极大矩形，所以悬线法即可。


```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
const int N=2000+5;
int n,k,a[N][N];
ll s[N][N];
int up[N],st[N],top;

ll S(int li,int lj,int ri,int rj)
{
    return s[ri][rj]-s[li][rj]-s[ri][lj]+s[li][lj];
}

int main()
{
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    k=read();n=read();
    rep(i,1,n)
    rep(j,1,n)a[i][j]=read();
    rep(i,1,n)
    rep(j,1,n)s[i][j]=s[i][j-1]+a[i][j];
    rep(i,1,n)
    rep(j,1,n)s[i][j]=s[i-1][j]+s[i][j];
    
    rep(i,1,n)
    rep(j,1,n+1)
    {
        if(a[i][j]<=2*k&&j<=n)
        {
            ++up[j];
            if(a[i][j]>=k)
            {
                printf("%d %d %d %d\n",j,i,j,i);
                exit(0);
            }
        }
        else up[j]=0;
        while(top&&up[st[top]]>=up[j])
        {
            int lj=st[top-1],rj=j-1;
            int li=i-up[st[top]];
            if(S(li,lj,i,rj)>=k)
            {
                while(S(li,lj,i,rj)>2*k)
                {
                    if(S(li,lj,li+1,rj)>2*k)
                    {
                        while(S(li,lj,li+1,rj)>2*k)++lj;
                        printf("%d %d %d %d\n",lj+1,li+1,rj,li+1);
                        exit(0);
                    }
                    ++li;
                }
                printf("%d %d %d %d\n",lj+1,li+1,rj,i);
                exit(0);
            }
            --top;
        }
        if(j<=n)st[++top]=j;
    }
    puts("NIE");
}
```

---

## 作者：i207M (赞：5)

做这道题真的是把所有可能的错都犯了一遍...

注意：

1. 单调栈求最大子矩形，出栈的条件是>=不是>；
2. 即使是坏点也要入栈充数；
3. 要做好边界条件，例如求左边界前先把0入栈；

好的，我们来看这道题：给定k,n,和n*n的矩阵，求一个子矩形满足权值和在[k,2k]之间；

今天考试T2的灵感就来源于此；

几个显然的结论：

1. 如果有1个数在$[k,2k]$，直接输出；
2. 如果一个数>2k，它一定不能选；

这样我们就得到了一个矩阵，上面有一些坏点不能选，其他点的权值都<k；先别急着证明，来看看做法：

求出这个矩阵的最大子矩形，那么答案一定包含在它里面：

1. 如果最大子矩形的权值本身在$[k,2k]$直接输出；
2. 否则一行一行的切下这个矩形，如果这一行符合条件，直接输出；或者这一行的和>2k，接下来就处理这一行；
3. 剩下的情况只有，这一行的和<k，减去这一行的和，重复步骤1；

为什么一定有解呢？因为我们最初的数字$>2k$，我们每次减去$<k$的一个数，那么我们无论如何也无法跳过$[k,2k]$这个长度为k的区间，所以一定有解；

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
#include<climits>
using namespace std;
#define LL long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pairint pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
il char gc()
{
	static const int BS = 1 << 22;
	static unsigned char buf[BS], *st, *ed;
	if (st == ed) ed = buf + fread(st = buf, 1, BS, stdin);
	return st == ed ? EOF : *st++;
}
#define gc getchar
template<class T>void in(T &x)
{
	x = 0;
	bool f = 0;
	char c = gc();
	while (c < '0' || c > '9')
	{
		if (c == '-') f = 1;
		c = gc();
	}
	while ('0' <= c && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = gc();
	}
	if (f) x = -x;
}
#undef gc
#define pb push_back
#define N 2005
int k,n,k2;
LL a[N][N];
LL sum[N][N];
int up[N][N],lef[N],rit[N];
LL ask(int lx,int ly,int ux,int uy)
{
	return sum[ux][uy]-sum[lx-1][uy]-sum[ux][ly-1]+sum[lx-1][ly-1];
}
LL mx;
int alx,aly,aux,auy;
void cutline(int x,int l,int r)
{
	mx=ask(x,l,x,r);
	for(ri i=r; i>=l; --i)
	{
		mx-=a[x][i];
		if(mx>=k&&mx<=k2)
		{
			printf("%d %d %d %d",l,x,i-1,x);
			exit(0);
		}
	}
}
void solve()
{
	for(ri i=aux; i>=alx; --i)
	{
		LL t=ask(i,aly,i,auy);
		if(t>=k&&t<=k2)
		{
			printf("%d %d %d %d",aly,i,auy,i);
			exit(0);
		}
		else if(t>k2)
		{
			cutline(i,aly,auy);
		}
		else
		{
			mx-=t;
			if(mx>=k&&mx<=k2)
			{
				printf("%d %d %d %d",aly,alx,auy,i-1);
				exit(0);
			}
		}
	}
}
void upd(int lx,int ly,int ux,int uy)
{
	LL t=ask(lx,ly,ux,uy);
	if(t>=k&&t<=k2)
	{
		printf("%d %d %d %d",ly,lx,uy,ux);
		exit(0);
	}
	if(t>mx)
	{
		mx=t;
		alx=lx,aly=ly,aux=ux,auy=uy;
	}
}
int st[N],tp;
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
#endif
	in(k),in(n);
	k2=k<<1;
	for(ri i=1; i<=n; ++i)
	{
		for(ri j=1; j<=n; ++j)
		{
			in(a[i][j]);
			sum[i][j]=sum[i][j-1]+a[i][j];
			if(a[i][j]>=k&&a[i][j]<=k2)
			{
				printf("%d %d %d %d",j,i,j,i);
				return 0;
			}
		}
		for(ri j=1; j<=n; ++j)
			sum[i][j]+=sum[i-1][j];
	}
	for(ri i=1; i<=n; ++i)
	{
		for(ri j=1; j<=n; ++j)
			if(a[i][j]<k)
			{
				up[i][j]=up[i-1][j]+1;
			}
		// left
		st[tp=1]=0;
		up[i][0]=-1;
		for(ri j=1; j<=n; ++j)
		{
			while(tp&&up[i][st[tp]]>=up[i][j]) --tp;
			lef[j]=st[tp]+1;
			st[++tp]=j;
		}
		// right
		st[tp=1]=n+1;
		up[i][n+1]=-1;
		for(ri j=n; j>=1; --j)
		{
			while(tp&&up[i][st[tp]]>=up[i][j]) --tp;
			rit[j]=st[tp]-1;
			st[++tp]=j;
			if(up[i][j]) upd(i-up[i][j]+1,lef[j],i,rit[j]);
		}
	}
	if(mx<k)
	{
		puts("NIE");
		return 0;
	}
	solve();
	return 0;
}

```



---

## 作者：奇米 (赞：4)

# $\mathrm{  [POI2008]\ KUP-Plot purchase}$ 题解

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

### 题目意思
* [[POI2008]KUP-Plot purchase](https://www.luogu.com.cn/problem/P3474)
* 你随意选择一个子矩阵使得子矩阵里的权值和$v∈[k,2*k]$
* 一个坑点：**输出横纵坐标要反一下的**。

### $\mathrm{ Sol }$
* 前置知识：**单调栈**
* 因为我们只要随意输出一个子矩阵，那么如果存在$a_{i,j}∈[k,2*k]$直接输出即可。
* 那么肯定没这么简单：我们要找到这个矩阵的最大子矩阵，因为答案一定在这个矩阵当中。如果这个最大子矩阵的权值和$∈[k,2*k]$就结束了。如果不满足，我们只要一行一行地切下去。
* 对于切下来的那一行我们再做类似处理：如果权值和$∈(2*k,∞)$，那么我们一列一列地去切这一行直到$∈[k,2*k]$。否则如果$∈[k,2*k]$直接输出即可。再否则直接舍弃这行。

### $\mathrm{ Code }$

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define int long long 
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=2005;

int n,m,a[N][N],b[N][N],ans;
int up[N][N],stak[N],L[N],R[N],top;
int ax,ay,bx,by;

inline int sum(int sx,int sy,int ex,int ey)
{
	return b[ex][ey]-b[sx-1][ey]-b[ex][sy-1]+b[sx-1][sy-1];
}

signed main()
{
	m=read();
	n=read();
	for ( int i=1;i<=n;i++ ) 
		for ( int j=1;j<=n;j++ ) 
		{
			a[i][j]=read();
			if(a[i][j]>=m&&a[i][j]<=m*2) 
				return printf("%lld %lld %lld %lld\n",j,i,j,i),0;
			//情况1
		}
	for ( int i=1;i<=n;i++ ) 
		for ( int j=1;j<=n;j++ ) 
			b[i][j]=b[i][j-1]+b[i-1][j]-b[i-1][j-1]+a[i][j];
			//二维前缀和
	int mx=0;
	for ( int i=1;i<=n;i++ )
	{
		for ( int j=1;j<=n;j++ ) 
			if(a[i][j]<m)
				up[i][j]=up[i-1][j]+1;
				//∈[m,2*m]已经特判了，此时只有<m才会产生贡献
		stak[top=1]=0;
		up[i][0]=-1;
		for ( int j=1;j<=n;j++ ) 
		{
			while(top&&up[i][stak[top]]>=up[i][j]) top--;
			L[j]=stak[top]+1;
			stak[++top]=j;
		}
		//单调栈
		stak[top=1]=n+1;
		up[i][n+1]=-1;
		for ( int j=n;j>=1;j-- ) 
		{
			while(top&&up[i][stak[top]]>=up[i][j]) top--;
			R[j]=stak[top]-1;
			stak[++top]=j;
			if(up[i][j])  
			{
				int now=sum(i-up[i][j]+1,L[j],i,R[j]);
				if(now>=m&&now<=2*m) 
					return printf("%lld %lld %lld %lld\n",L[j],i-up[i][j]+1,R[j],i),0;
				//如果子矩阵以满足条件，直接输出
				if(now>mx)
				{
					mx=now;
					ax=i-up[i][j]+1,ay=L[j];
					bx=i,by=R[j];
				}//寻找最大子矩阵
			}
		}
	}
	if(mx<m) return printf("NIE\n"),0;
	for ( int i=bx;i>=ax;i-- )//一行一行地切
	{
		int now=sum(i,ay,i,by);
		if(now>=m&&now<=2*m) 
			return printf("%lld %lld %lld %lld\n",ay,i,by,i),0;	//满足条件
		if(now>2*m) 
		{
			mx=now;
			for ( int j=by;j>=ay;j-- ) //一列一列地切
			{
				mx-=a[i][j];
				if(mx>=m&&mx<=2*m) 
					return printf("%lld %lld %lld %lld\n",ay,i,j-1,i),0;
			}
		}
		else 
		{
			mx-=now;//舍弃这小块，总的减掉就可以了，直至满足条件
			if(mx>=m&&mx<=2*m) 
				return printf("%lld %lld %lld %lld\n",ay,ax,by,i-1),0;
		}
	}
	return 0;
}
			
	
```


---

## 作者：hegm (赞：3)

### [[POI2008]KUP-Plot purchase](https://www.luogu.com.cn/problem/P3474)

笛卡尔树~

竟然没有笛卡尔树的题解，真是令人惊讶。

考虑转化题意。

性质：

> 如果存在一个子矩形，满足它的所有元素都小于 $2k$，并且它的总和大于等于 $k$，那么一定有解，否则一定无解。

先来证明它的充分性：

两种情况：

1. 子矩形总和小于等于 $2k$，那么这个子矩形本身就是答案。

2. 总和大于 $2k$，考虑一步步的缩小他，钦定这个矩形是 $(x1,y1),(x2,y2)$（$x$ 为行，$y$ 为列）
	
    现在先缩小行长，取 $mid=\dfrac{x1+x2}{2}$（下取整），形成 $(x1,y1),(mid,y2)$ 和 $(mid+1,y1),(x2,y2)$ 上下两个矩形，记 $s_1$ 表示上方矩形总和，$s_2$ 同理。
    
    分情况讨论：
    
    - $s_1,s_2>2k$，那么直接取任意一个接着二分即可。
    
    - $2k \ge s_1\ge k$，直接输出 $s_1$ 即可，$s_2$ 同理。
    
    - $s_1>2k,s_2<k$，取 $s_1$ 接着二分即可，反之亦然。
    
    - $s_1,s_2<k$，两者和 $s_1+s_2<2k$，与条件总和大于 $2k$ 相悖，不存在此情况。
    
    如果缩成一行后仍然没有答案，那么同理缩小列即可。
    
    由于保证了每个元素都小于 $<k$ 而总和大于 $2k$，所以一定有解。
    
必要性：

如果最大的不存在大于 $2k$ 的元素的子矩形小于 $k$，那么扩展任何一维都会碰到大于 $2k$ 的元素，则总和大于 $2k$。

那么转化为了求二维最大子矩形，并且有些点不能碰。

因为题面给出了所有元素大于 $0$，所以可以贪心的用笛卡尔树来求解。

考虑柱状图最大子矩形的过程，那时，底面已经被确定，所以每一列都有一个限高，但是现在不同，没有底面，所以我们枚举一维底面，对于底面上的点，找到它上方第一个不能取的点，那么这就是他的限高，接下来直接笛卡尔树即可。

复杂度 $O(n^2)$。

代码~

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 2005
#define lc ls[now]
#define rc rs[now]
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int fr[N][N],n,m,mp[N][N],last[N][N],w[N],x1,x2,y11,y2,tot,dl,ls[N],rs[N],siz[N];
stack<int> t;
int get(int x,int y,int a,int b)
{
	if(x>a||y>b)return 0;x--;y--;
	return fr[a][b]-fr[a][y]-fr[x][b]+fr[x][y];
}
void dfs(int now)
{
	if(lc)dfs(lc),siz[now]+=siz[lc];
	if(rc)dfs(rc),siz[now]+=siz[rc];
	siz[now]++;int a1=now-siz[lc],a2=now+siz[rc],b1=dl,b2=dl+w[now]-1,p=get(a1,b1,a2,b2);
	if(tot<p)tot=p,x1=a1,x2=a2,y11=b1,y2=b2;
}
int out(int x1,int y11,int x2,int y2)
{
	cout<<y11<<" "<<x1<<" "<<y2<<" "<<x2<<"\n";
	exit(0);
}
signed main()
{
	m=read();n=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			mp[i][j]=read();
			fr[i][j]=fr[i-1][j]+fr[i][j-1]-fr[i-1][j-1]+mp[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		last[i][n+1]=n+1;
		for(int j=n;j>=1;j--)
		{
			if(mp[i][j]>2*m)last[i][j]=j;
			else last[i][j]=last[i][j+1];
		}
	}
	for(int j=1,rt=0;j<=n;j++)
	{
		while(t.size())t.pop();dl=j;
		for(int i=1;i<=n;i++)w[i]=last[i][j]-j,ls[i]=rs[i]=0,siz[i]=0;
		for(int i=1,last;i<=n;i++)
		{
			last=0;
			while(t.size()&&w[t.top()]>w[i])last=t.top(),t.pop();
			if(last)ls[i]=last;
			if(t.empty())rt=i;
			else rs[t.top()]=i;
			t.push(i);
		}
		dfs(rt);
	}
	if(tot>=m&&tot<=2*m)out(x1,y11,x2,y2);
	else if(tot<m)
	{
		cout<<"NIE\n";
		return 0;
	}
	int mid=0;
	while(x1<x2)
	{
		mid=(x1+x2)>>1;
		int p1=get(x1,y11,mid,y2),p2=get(mid+1,y11,x2,y2);
		if(p1<=2*m&&p1>=m)out(x1,y11,mid,y2);
		if(p2<=2*m&&p2>=m)out(mid+1,y11,x2,y2);
		if(p1>2*m)x2=mid;
		else x1=mid+1;
	}
	while(y11<y2)
	{
		mid=(y11+y2)>>1;
		int p1=get(x1,y11,x2,mid),p2=get(x1,mid+1,x2,y2);
		if(p1<=2*m&&p1>=m)out(x1,y11,x2,mid);
		if(p2<=2*m&&p2>=m)out(x1,mid+1,x2,y2);
		if(p1>2*m)y2=mid;
		else y11=mid+1;
	}
	return 0;
}

```

---

## 作者：LEWISAK (赞：2)

# 前言

1. 这道题的输出 $x$ 和 $y$ 是反的。

2. dfs 实际思路和别的题解一样，只不过实现方法不同。

3. 前置知识：单调栈求最大子矩阵，二维前缀和。
# 正文

设 $a_{i,j}$ 表示矩阵的第 $i$ 行 $j$ 列。

那么考虑 $a_{i,j}$ 的每种情况,有以下几个结论。

1. 如果 $a_{i,j}>2 \times k$ 这个点**不能**选。

2. 如果 $a_{i,j}\le 2 \times k$ 并且 $a_{i,j} \ge k$ 直接输出，该点为一种方案。

处理矩阵代码：

```cpp
//sum：二维前缀和，以后要用
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			sum[i][j]=sum[i][j-1]+a[i][j];
			if(a[i][j]>=k&&a[i][j]<=2*k){//满足直接输出
				cout<<j<<" "<<i<<" "<<j<<" "<<i;
				return 0;
			}
			if(a[i][j]<k){
				h[i][j]=h[i-1][j]+1;
			}
		}
		for(int j=1;j<=n;j++){
			sum[i][j]+=sum[i-1][j];
		}
	}
```

接着注意到对于一个矩阵的情况与其类似，又有以下3个结论 （设该矩阵元素和为 $ans$）：

3. 如果 $ans \le 2\times k$ 并且 $ans \ge k$ 直接输出，该矩阵为一种方案。

4. 如果 $ans<k$ 该矩阵内无解。

这个时候，我们发现，因为结论1，所以最后选出来的矩阵中的数都必定小于 $2\times k$ ，所以当 $ans>2\times k$ 时，我们缩小矩阵就有：

5. 如果该矩阵的第一列的元素和小于 $2\times k$ ：直接减小。

6. 如果该矩阵的第一列的元素和大于等于 $2\times k$ ：将矩阵的第一列作为接下来要缩小的目标。

又注意到，在这种情况下，我们每次缩小矩阵都**不会超过** $k$。

那么本来大于 $2\times k$ 的矩阵，每次缩小 $k$ 就一定逃不掉 $k$ 到 $2\times k$ 的区间，也就是绝对有解！

缩小矩阵部分的代码实现：

```cpp
//ans 表示矩阵大小（不好意思和说好的不一样）
//xx，yy表示左上角的坐标
//x，y表示右下角的坐标
inline void dfs(int ans,int xx,int yy,int x,int y){
	if(ans>=k&&ans<=2*k){//如果ans符合，直接输出即可
		cout<<yy<<" "<<xx<<" "<<y<<" "<<x;
		exit(0);
	}
	if(ans<k){//无解的情况
		return;
	}
	if(ans>2*k){//缩小矩阵
		int t=summ(xx,y,x,y);//等会会讲
		int tt=t;
		for(int i=x;i>=xx;i--){
			t-=a[i][y];//枚举第一列
			if(t>=k&&t<=2*k){
				cout<<y<<" "<<min(xx,i-1)<<" "<<y<<" "<<max(i-1,xx);
				exit(0);
			}
		}
		if(y>yy){
        //缩小
			dfs(ans-tt,xx,yy,x,y-1);
		}
	}
	return;
}
```

问题来了：

> 怎么开始算答案了？要缩小哪个矩阵？

那么为了不让我们误把有解判断成无解，考虑到上面的矩阵只要大于 $k$ 就保证有解，所以矩阵越大越好。

那么就可以干脆使用最大的子矩阵，根据第1条定理:

> 如果 $a_{i,j}>2\times k$ 这个点**不能**选。

那么就是[经典板子](https://www.luogu.com.cn/problem/P4147)了。

这部分的代码处理：

```cpp

	for(int i=1;i<=n;i++){
		int tot=0;
		for(int j=1;j<=n;j++){
			while(tot&&h[i][st[tot]]>=h[i][j]){
				tot--;
			}
			l[j]=st[tot]+1;
			st[++tot]=j;
		}
		tot=0;
		for(int j=n;j>=1;j--){
			while(tot&&h[i][st[tot]]>=h[i][j]){
				tot--;
			}
			if(!tot){
				r[j]=n+1-1;
			}
			else{
				r[j]=st[tot]-1;
			}
			st[++tot]=j;
			int t=summ(i-h[i][j]+1,l[j],i,r[j]);//等会会讲
			if(ans<t){
              //记录左上角和右下角的坐标
				lx=i-h[i][j]+1,ly=l[j];
				rx=i,ry=r[j];
				ans=t;
			}
		}
	}
	if(ans<k){
		cout<<"NIE"<<endl;
		return 0;
	}
```

最后注意到：

> `int t=summ(i-h[i][j]+1,l[j],i,r[j]);//等会会讲`

这个函数其实就是[二维前缀和模板](https://www.luogu.com.cn/problem/P5542)了

代码实现：

```cpp
inline int summ(int xx,int yy,int x,int y){
	return sum[x][y]-sum[x][yy-1]-sum[xx-1][y]+sum[xx-1][yy-1];
}
```

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int lx,ly,rx,ry,ans=0,sum[2015][2015],a[2015][2015],n,k,h[2015][2015],st[2015],l[2015],r[2015];
inline int summ(int xx,int yy,int x,int y){
	return sum[x][y]-sum[x][yy-1]-sum[xx-1][y]+sum[xx-1][yy-1];
}
inline void dfs(int ans,int xx,int yy,int x,int y){
	if(ans>=k&&ans<=2*k){
		cout<<yy<<" "<<xx<<" "<<y<<" "<<x;
		exit(0);
	}
	if(ans<k){
		return;
	}
	if(ans>2*k){
		int t=summ(xx,y,x,y);
		int tt=t;
		for(int i=x;i>=xx;i--){
			t-=a[i][y];
			if(t>=k&&t<=2*k){
				cout<<y<<" "<<min(xx,i-1)<<" "<<y<<" "<<max(i-1,xx);
				exit(0);
			}
		}
		if(y>yy){
			dfs(ans-tt,xx,yy,x,y-1);		
		}
	}
	return;
}
signed main(){
	cin>>k>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			sum[i][j]=sum[i][j-1]+a[i][j];
			if(a[i][j]>=k&&a[i][j]<=2*k){
				cout<<j<<" "<<i<<" "<<j<<" "<<i;
				return 0;
			}
			if(a[i][j]<k){
				h[i][j]=h[i-1][j]+1;
			}
		}
		for(int j=1;j<=n;j++){
			sum[i][j]+=sum[i-1][j];
		}
	}
	for(int i=1;i<=n;i++){
		int tot=0;
		for(int j=1;j<=n;j++){
			while(tot&&h[i][st[tot]]>=h[i][j]){
				tot--;
			}
			l[j]=st[tot]+1;
			st[++tot]=j;
		}
		tot=0;
		for(int j=n;j>=1;j--){
			while(tot&&h[i][st[tot]]>=h[i][j]){
				tot--;
			}
			if(!tot){
				r[j]=n+1-1;
			}
			else{
				r[j]=st[tot]-1;
			}
			st[++tot]=j;
			int t=summ(i-h[i][j]+1,l[j],i,r[j]);
			if(ans<t){
				lx=i-h[i][j]+1,ly=l[j];
				rx=i,ry=r[j];
				ans=t;
			}
		}
	}
	if(ans<k){
		cout<<"NIE"<<endl;
		return 0;
	}
	dfs(ans,lx,ly,rx,ry);
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：2)

### [P3474 [POI2008] KUP-Plot purchase](https://www.luogu.com.cn/problem/P3474 "T2 方格取数（P3474 [POI2008] KUP-Plot purchase）")
先特判不可能合法的点和一定合法的点，然后就只剩下权值在 $[1,k-1]$ 中的点，这时考虑找到一个子矩阵的权值和大于 $k$，则此时一定有解。
- 考虑这个子矩阵的从上到下每一行，如果这一行的权值和大于 $k$，那么答案属于这一行，因为这时的所有点权小于 $k$，所以可以一个一个删使这一行达到合法范围。
- 如果这一行权值小于 $k$，删去这一行后继续往下找。以此类推，直到剩下的矩阵权值和在合法范围中。

具体来说，处理出每一个点能向上扩展的最大高度，然后单调栈找最大矩阵即可，因为权值是正整数，所以这样一定可以扫描到权值和最大的矩阵，找到之后就执行上述操作即可。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e3+10;
int n,k,a[N][N],s[N][N],l[N][N],q[N],head,tail,wi[N],sum[N][N];
inline int ask(int i,int j,int x,int y){
    return sum[x][y]-sum[i-1][y]-sum[x][j-1]+sum[i-1][j-1];
}
signed main(){
    // freopen("matrix.in","r",stdin);freopen("matrix.out","w",stdout);
    std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
    k=read(),n=read();
    for(int i=1;i<=n;++i)for(int j=1;j<=n;++j){
        a[i][j]=read();
        if(a[i][j]>=k&&a[i][j]<=2*k){std::cout<<j<<' '<<i<<' '<<j<<' '<<i<<'\n';exit(0);}
        if(a[i][j]<k){
            l[i][j]=l[i-1][j]+1;
            s[i][j]=1;
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)
            sum[i][j]=a[i][j]+sum[i][j-1];
        for(int j=1;j<=n;++j)
            sum[i][j]+=sum[i-1][j];
    }
    int res=0;
    int x=0,y=0,w=0,c=0,pd=0;
    for(int i=1;i<=n;++i){
        for(int i=1;i<=n+1;++i)wi[i]=0;
        head=0,tail=0;
        for(int j=1;j<=n+1;++j){
            int p=l[i][j],zc=0;
            while(p<q[tail]){
                zc+=wi[tail];
                x=i,y=j-1;w=i-q[tail--]+1,c=j-zc;
                if(ask(w,c,x,y)>=k){
                    pd=1;
                    res=ask(w,c,x,y);break;
                }
            }
            if(pd)break;
            q[++tail]=p;wi[tail]=zc+1;
        }
        if(pd)break;
    }
    if(res<k){std::cout<<"NIE\n";exit(0);}
    if(res>=k&&res<=k*2){std::cout<<c<<' '<<w<<' '<<y<<' '<<x<<'\n';exit(0);}
    for(int i=w;i<=x;++i){
        if(res>=k&&res<=k*2){std::cout<<c<<' '<<i<<' '<<y<<' '<<x<<'\n';exit(0);}
        int zc=ask(i,c,i,y);
        if(zc>=k){
            for(int j=c;j<=y;++j){
                zc=ask(i,j,i,y);
                if(zc>=k&&zc<=2*k){std::cout<<j<<' '<<i<<' '<<y<<' '<<i<<'\n';exit(0);}
            }
        }
        res-=zc;
    }   

}
```

---

## 作者：lndjy (赞：2)

看大家都用的单调栈，我发一个悬线法题解。

首先，一个格子在 $k$ 到 $2k$ 是直接选的，大于 $2k$ 是一定不能选的。

这样，就只有小于 $k$ 的可选和大于 $2k$ 的不可选。由于是求一个矩形，所以可以用悬线法求出最大的由小于 $k$ 的数组成的矩形。

这个矩形的和可能大于 $2k$ ，所以要不断切割这个矩形直到在 $k$ 到 $2k$ 之间即可。

由于这个算法的过程中需要不断计算矩形的和，直接暴力计算时间会爆炸，所以可以通过二维前缀和来实现 $O(1)$ 计算。

时间复杂度是 $O(n^2)$ 的。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=2005;
int inline read()
{
	int ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*f;
}
int a[N][N],f[N][N],up[N][N],l[N][N],r[N][N];
int n,k;
int cal(int x1,int y1,int x2,int y2)
{
	return f[x2][y2]+f[x1-1][y1-1]-f[x2][y1-1]-f[x1-1][y2];
}
int main()
{
	k=read();n=read();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		a[i][j]=read();
		if(a[i][j]>=k&&a[i][j]<=2*k)
		{
			cout<<j<<" "<<i<<" "<<j<<" "<<i;
			return 0;
		}
		if(a[i][j]>2*k) continue;
		r[i][j]=l[i][j]=j;
		up[i][j]=1;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+a[i][j];
	for(int i=1;i<=n;i++)
	for(int j=2;j<=n;j++)
	if(a[i][j]<k&&a[i][j-1]<k)
	l[i][j]=l[i][j-1];
	for(int i=1;i<=n;i++)
	for(int j=n-1;j>=1;j--)
	if(a[i][j]<k&&a[i][j+1]<k)
	r[i][j]=r[i][j+1];
	int x1=0,y1=0,x2=0,y2=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i>1&&a[i][j]<k&&a[i-1][j]<k)
			{
				l[i][j]=max(l[i][j],l[i-1][j]);
				r[i][j]=min(r[i][j],r[i-1][j]);
				up[i][j]=up[i-1][j]+1;
			}
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		if(a[i][j]<k&&cal(i-up[i][j]+1,l[i][j],i,r[i][j])>=k)
		{
			y1=l[i][j];
			x1=i-up[i][j]+1;
			y2=r[i][j];
			x2=i;
			break;
		}
	}
	if(x1==0)
	{
		cout<<"NIE";
		return 0;
	}
	while(cal(x1,y1,x2,y2)>2*k)
	{
		if(x1<x2)
		{
			if(cal(x1,y1,x2-1,y2)<k)
			x1=x2;
			else x2--;
		}
		else y2--;
	}
	cout<<y1<<" "<<x1<<" "<<y2<<" "<<x2;
	return 0;
}
```


---

## 作者：白简 (赞：1)

#### 简明题意
对于给出的矩阵，在其中找到一个子矩阵使得子矩阵的和大于等于 $k$ 且小于等于 $2k$。
#### 思路
首先我们知道，如果一个数在 $\left[ k,2k \right]$，这个数就是答案；如果一个数大于 $2k$，那这个数不能出现在子矩阵中。

把这两种点排除出去，我们剩下的矩阵就只剩下了一些值小于 $k$ 的点。

假设我们找到了一个极大子矩阵，矩阵和 $sum \geq k$。要是不存在这样一个极大子矩阵，就是无解的情况了。

如果 $sum \leq 2k$ 就可以直接输出答案了，否则我们可以挑出该矩阵的第一行的元素和 $sum_1$。

如果 $sum_1 \geq k$，那么答案就在第一行里，一个个元素删就可以了。因为每个元素的值都是小于 $k$ 的，所以不可能有某个元素被删去后能够使得矩阵和从大于 $2k$ 跳到小于 $k$，就意味着我们只要一个个删去第一行中的元素，就一定可以找到答案。

如果 $sum_1 < k$，我们知道 $sum$ 是大于 $k$ 的，我们就可以舍弃掉第一行，对剩下的矩阵重复上面的操作。

利用悬线法找到极大子矩阵。

#### Code
```cpp
#include <algorithm>
#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

const int N = 2050;

int n,k;
long long val[N][N];
long long sum[N][N];

int l[N][N],r[N][N],h[N][N];

long long Get(int a,int b,int c,int d) {
    return sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1];
}

bool flag = 0;

void Work(int a,int b,int c,int d) {
    while(Get(a,b,c,d) > 2 * k) {
        if(a == c) 
            d --;
        else if(Get(a,b,c,d) >= k)
            c = a;
        else
            a ++;
    }
    cout << b << " " << a << " " << d << " " << c;
    exit(0);
}

signed main() {
	// freopen("matrix.in","r",stdin);
    // freopen("matrix.out","w",stdout);
	scanf("%d%d",&k,&n);
    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= n; j++) {
            cin >> val[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + val[i][j] - sum[i - 1][j - 1];

            if(val[i][j] < k || val[i][j] > 2 * k) 
                continue;
            
            cout << j << " " << i << " " << j << " " << i << "\n";
            return 0;
        }
    }
            
    for(int i = 1;i <= n; i++)
        r[0][i] = n + 1;
    
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <= n; j++)
            if(val[i][j] > 2 * k)
                h[i][j] = 0;
            else
                h[i][j] = h[i - 1][j] + 1;
        
    for(int i = 1;i <= n; i++) {
        int tmp = 0;
        for(int j = 1;j <= n; j++) {
            if(h[i][j]) 
                l[i][j] = max(l[i - 1][j],tmp);
            else {
                tmp = j;
                l[i][j] = 0;
            }
        }
        
        tmp = n + 1;
        for(int j = n;j; j--) {
            if(h[i][j])
                r[i][j] = min(r[i - 1][j],tmp);
            else {
                tmp = j;
                r[i][j] = n + 1;
            }
        }
    }

    int a,b,d;
    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= n; j++) {
            if(h[i][j] == 0)
                continue;
            
            a = i - h[i][j] + 1;
            b = l[i][j] + 1;
            d = r[i][j] - 1;

            
            if(Get(a,b,i,d) < k)
                continue;
            
            Work(a,b,i,d);
        }
    }
    cout << "NIE";
    return 0;
}
```

---

## 作者：cold_cold (赞：1)

此题我们拿来考试了，我写了随机数，可惜没有得到多少分。考试完后学习了一波，才会写。
首先对于每一个点，
- 如果有一个点**大于等于k**且**小于等于2k**，那么我们直接输出这个点即可
- 如果有一个点**大于2k**，那么我们一定不可以选这个点，和包括它的矩形，将其视为障碍物
- 对于一个权值和 **大于2k**的矩形一定可以找到一个子矩形权值和**大于等于k**且**小于等于2k**。
	所以现在我们只需找到一个权值和**大于等于k**且**小于等于2k**的极大子矩形

找极大子矩形我们采用单调栈的方法，我们为每一个点找到其向上最多能伸展多少的点，将其存入up数组

就是这样：![](https://s1.ax1x.com/2018/10/21/iBWsPK.png)
然后我们逐行进行操作，每次我们从栈顶取出一个数，若该数比up[j]小，那么我们就将up[j]压入栈
否则我们将栈顶取出操作，直到栈顶比up[j]小为止，这是为什么呢
		![](https://s1.ax1x.com/2018/10/21/iBf1Ld.png)
因为栈顶比up[j]高，那么栈就会不单调，于是我们依次取出操作
	![](https://s1.ax1x.com/2018/10/21/iBhkp8.png)
    ![](https://s1.ax1x.com/2018/10/21/iBhGX4.png)
    ![](https://s1.ax1x.com/2018/10/21/iBhN7R.png)
    ![](https://s1.ax1x.com/2018/10/21/iBhx3T.png)
	
如此反复，逐行完成，找到一个权值和**大于等于k**且**小于等于2k**的极大子矩形

- 如果最大子矩形的权值本身在[k,2k]，则直接输出；
- 否则逐行的切下这个矩形，如果这一行符合条件则直接输出；
- 若这一行的和大于2k，接下来就处理这一行；
- 剩下的情况只有，这一行的和小于k，减去这一行的和，重复；

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <ctime>
using namespace std;
typedef long long ll;
ll read()
{
    ll a=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') a=(a<<3)+(a<<1)+ch-48,ch=getchar();
    return a;
}
const int N=2010;
ll z,n,a[N][N],l[N][N],s[N][N],up[N],top,sta[N],k;
int x1,x2,high;
ll suan(int x1,int y1,int x2,int y2)
{

    return s[x2][y2]-s[x1-1][y2]+s[x1-1][y1-1]-s[x2][y1-1];
}
int main()
{
//  freopen("kup.in","r",stdin);
//  freopen("kup.out","w",stdout);
    k=read();n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            a[i][j]=read();
    for(int j=1;j<=n;j++)
        for(int i=1;i<=n;i++)
            l[i][j]=l[i-1][j]+a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            s[i][j]=s[i][j-1]+l[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n+1;j++)
        {
            if(a[i][j]<=(k<<1)&&j<=n)
            {
                up[j]++;
                if(a[i][j]>=k)
                {
                    printf("%d %d %d %d\n",j,i,j,i);
                    return 0;
                }
            }
            else up[j]=0;
            while(top&&up[sta[top]]>=up[j])
            {
                x1=sta[top-1]+1,x2=j-1;
                high=i-up[sta[top]]+1;
                if(suan(high,x1,i,x2)>=k)
                {
                    while(suan(high,x1,i,x2)>(k<<1))
                    {
                        if(suan(high,x1,high+1,x2)>(k<<1))
                        {
                            while((high,x1,high+1,x2)>(k<<1)) x1++;
                            printf("%d %d %d %d",x1,high,x2,high+1);
                            return 0;
                        }
                        high++;
                    }
                    printf("%d %d %d %d\n",x1,high,x2,i);
                    return 0;
                }
                top--;
            }
            if(j<=n) sta[++top]=j;
        }
    printf("NIE\n");
    return 0;
}
/*
8 4
1 2 1 3
25 1 2 1
4 20 3 3
3 30 12 2
*/

```

---

## 作者：_fairytale_ (赞：0)

草。

扔掉所有 $>2k$ 的格子之后，如果能在剩下的格子中找到一个权值和 $\ge k$ 的矩形就有解。

证明：

如果存在一个格子权值在 $[k,2k]$ 之间直接选取它即可。为了方便，我们认为剩下的所有格子权值在 $[0,k)$ 之间。

- 如果找到了这样的矩形，考察它的每一列：

  - 如果它的权值在 $[k,2k]$ 之间，直接选取即可。
  - 如果它的权值 $>2k$，从上往下依次删掉这一列的格子，因为格子的权值 $<k$，所以必然存在一个时刻它的权值位于 $[k,2k]$ 之间（因为不会从 $>2k$ 突变到 $<k$）。
  - 所以我们只需考虑每一列权值 $<k$ 的情况，直接把每一列当成一个格子，套用上一种情况的构造即可。

- 如果不存在这样的矩形，显然无解。

因为每个格子的权值是非负整数，所以直接找极大的子矩形即可。

单调栈 `while` 打成 `if` 调了一年。

```cpp
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>k>>n;
	auto ans=[&](int i1,int i2,int j1,int j2)->void{
		cout<<j1<<" "<<i1<<" "<<j2<<" "<<i2<<'\n';
		exit(0);
	};
	rep(i,1,n) {
		rep(j,1,n) {
			cin>>a[i][j];
			if(a[i][j]>k+k)a[i][j]=-inf;
			else if(a[i][j]>=k)ans(i,i,j,j);
		}
	}
	rep(i,1,n)rep(j,1,n)pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+a[i][j];
	auto s=[&](int i1,int i2,int j1,int j2)->ll {
		return pre[i2][j2]-pre[i1-1][j2]-pre[i2][j1-1]+pre[i1-1][j1-1];
	};
	rep(i,1,n) {
		rep(j,1,n) {
			if(a[i][j]==-inf)h[j]=0;
			else ++h[j];
		}
		stac[top=0]=0;
		rep(j,1,n) {
			while(top&&h[j]<=h[stac[top]])--top;
			L[j]=stac[top]+1;
			stac[++top]=j;
		}
		stac[top=0]=n+1;
		per(j,n,1) {
			while(top&&h[j]<=h[stac[top]])--top;
			R[j]=stac[top]-1;
			stac[++top]=j;
		}
		rep(j,1,n) {
			if(s(i-h[j]+1,i,L[j],R[j])>=k) {
				for(int i1=i-h[j]+1,i2=i,j1=L[j],j2=R[j]; j1<=j2; --j2) {
					if(s(i1,i2,j1,j2)<=k+k)ans(i1,i2,j1,j2);
					if(s(i1,i2,j2,j2)>k+k){
						for(;i1<=i2;++i1)if(s(i1,i2,j2,j2)<=k+k)ans(i1,i2,j2,j2);
					}
					if(s(i1,i2,j2,j2)>=k)ans(i1,i2,j2,j2);
				}
				assert(0);
			}
		}
	}
	cout<<"NIE\n";
	return 0;
}
```

---

