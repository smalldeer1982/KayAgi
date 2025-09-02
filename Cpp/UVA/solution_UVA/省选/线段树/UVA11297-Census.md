# Census

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2272

[PDF](https://uva.onlinejudge.org/external/112/p11297.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11297/dcd5caafdceb17224df6ccc10085a992416eab82.png)

## 样例 #1

### 输入

```
5
1 2 3 4 5
0 9 2 1 3
0 2 3 4 1
0 1 2 4 5
8 5 3 1 4
4
q 1 1 2 3
c 2 3 10
q 1 1 5 5
q 1 2 2 2```

### 输出

```
9 0
10 0
9 2```

# 题解

## 作者：JJA_ (赞：10)

~~正解难度 紫 暴力难度 黄 看懂题目难度 黑~~

## 题目大意

在一些城市，人口普查难度很高，鉴于有很多移民或人口增长率非常高。每年，ACM（人口统计协会）在每个地区进行一次人口普查。国家被划分为很多个区域，由 $N \times N$ 的区域网格组成。你的任务是在某些区域内找到最少和最多的人口。ACM 也会根据一些居民的数量来修改人口数量。

输入的第一行是 $N$ $(0\le N\le 500)$，之后的 $N$ 行，每行有 $N$ 个数，代表每块区域的人口。之后有一个数字 $Q$ $(0 \le Q\le 40000$，代表询问的次数。接下来的 $Q$ 行，每行有两种可能的操作，
$q$ $x_1$ $y_1$ $x_2$ $y_2$ 代表输出 $x_1$ $y_1$ $x_2$ $y_2$ 内的最小值和最大值， $c$ $x$ $y$ $v$ 代表将坐标为 $x$ $y$ 的值修改为 $v$。

## 题目思路

1. 树套树 $O(Q \log^2 n)$
2. $n^2$ 暴力

由于时限 $8s$，我们选择对键盘好点的方法——暴力。

单点修改：

```cpp
mapp[x][y]=v;
```

查询最值：

```cpp
#define chkmax(a,b) a=a>b?a:b;
#define chkmin(a,b) a=a<b?a:b;
forr(a,x1,x2){
	forr(b,y1,y2){
		chkmax(maxn,mapp[a][b]);
		chkmin(minn,mapp[a][b]);
	}
}
```

思路清晰。

源代码:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<sstream>
#include<queue>
//#include<map>
#include<vector>
#include<math.h>
using namespace std;
//#define int long long
#define forr(i,a,b) for(int i=a;i<=b;i++)
#define repp(i,a,b) for(int i=a;i>=b;i--)
#define INF 1e9
#define ll long long
#define MAXN 20005
const int _x[]={0,1,0,-1,0},_y[]={0,0,1,0,-1};
#define mem(a,n) memset(a,n,sizeof(a));
#define chkmax(a,b) a=a>b?a:b;
#define chkmin(a,b) a=a<b?a:b;
#include<set>
#include<stack>
#define DE puts("check");
int mapp[MAXN][MAXN];
int n,m;
int main(){
	scanf("%d",&n);
	forr(i,1,n){
		forr(j,1,n){
			scanf("%d",&mapp[i][j]);
		}
	}
	scanf("%d",&m);
	forr(i,1,m){
		char opt;
        int x1,y1,x2,y2,k;
		cin>>opt>>x1>>y1;
//		printf("%c\n",opt);
	    if(opt=='c'){
			scanf("%d",&k);
			mapp[x1][y1]=k;
		}
		if(opt=='q'){
			int minn=MAXN;
			int maxn=-1;
			scanf("%d%d",&x2,&y2);
			forr(a,x1,x2){
				forr(b,y1,y2){
					chkmax(maxn,mapp[a][b]);
					chkmin(minn,mapp[a][b]);
				}
			}
			printf("%d %d\n",maxn,minn);
		}
	}
}
```
求赞求过qwq。

---

## 作者：Cylete (赞：5)

二维RMQ

提供几种做法

1. 暴力 $O(qn^2)$

2. KD-tree $O(n^2log_2^2 n + qn)$

3. 线段树套线段树 $O(n^2log_2^2n + qlog_2^2n)$

4. 500棵线段树（？为什么不直接上暴力呢

5. 树状数组套树状数组

树状数组也是可以求区间最值的

不清楚可以看[这里](https://blog.csdn.net/u010598215/article/details/48206959)

为了保护头发我选择了暴力

```cpp
const int inf = 1234567890;

int n, m, e[505][505];

char opt;
int a, b, c, d, minn, maxx;

signed main()
{
	into();
	cin >> n;
	for(R int i = 1; i <= n; i++)
		for(R int j = 1; j <= n; j++)
			cin >> e[i][j];
	cin >> m;
	while(m--)
	{
		cin >> opt >> a >> b >> c;
		if(opt == 'q')
		{
			cin >> d;
			maxx = -inf; minn = inf;
			for(R int i = a; i <= c; i++)
				for(R int j = b; j <= d; j++)
				{
					maxx = max(maxx, e[i][j]);
					minn = min(minn, e[i][j]);
				}
			writesn(maxx); writeln(minn);
		}
		else
		{
			e[a][b] = c;
		}
	}
	return 0;
}
```

---

## 作者：ezoixx130 (赞：4)

题目大意：

给你一个矩阵，每个格子上都有一个数字。

有一种更改操作：把位置$[x,y]$的数字改成$v$。

一种询问：问第$x1$~$x2$行，$y1$~$y2$列的数字的最大值和最小值分别是多少。

题解：

~~暴力可过~~

很明显是一个二维的动态修改，查询区间最大最小值的问题。（二维RMQ）

那就用线段树做。

当然是线段树套线段树啦，我们对每一行建一棵主线段树，该线段树的每一个节点都保存一棵小线段树。这样对于每一个修改或询问，现在主线段树上求解，然后调用小线段树即可。

在主线段树上求解的时间复杂度为$O(log(n))$，每个区间调用一棵小线段树的时间复杂度为$O(log(n))$，所以每个操作的总时间复杂度为$O(log(n)^2)$。

当然可以用四叉树，时间复杂度相同，这里不再介绍。

代码:

```cpp
#include <bits/stdc++.h>  
using namespace std;  
  
int n,m,a[501][501],maxn,minn;  
  
struct node{  
    int maxv,minv;  
}p[2001][2001];  
  
void build2(int mo,int ml,int mr,int o,int l,int r)  
{  
    if(l!=r)  
    {  
        int m=(l+r)>>1;  
        build2(mo,ml,mr,o<<1,l,m);  
        build2(mo,ml,mr,(o<<1)+1,m+1,r);  
        p[mo][o].maxv=max(p[mo][o<<1].maxv,p[mo][(o<<1)+1].maxv);  
        p[mo][o].minv=min(p[mo][o<<1].minv,p[mo][(o<<1)+1].minv);  
    }  
    else  
    {  
        if(ml==mr)p[mo][o].maxv=p[mo][o].minv=a[ml][l];  
        else  
        {  
            p[mo][o].maxv=max(p[mo<<1][o].maxv,p[(mo<<1)+1][o].maxv);  
            p[mo][o].minv=min(p[mo<<1][o].minv,p[(mo<<1)+1][o].minv);  
        }  
    }  
}  
  
void build1(int o,int l,int r)  
{  
    if(l!=r)  
    {  
        int m=(l+r)>>1;  
        build1(o<<1,l,m);  
        build1((o<<1)+1,m+1,r);  
    }  
    build2(o,l,r,1,1,n);  
}  
  
void query2(int o,int l,int r,int ql,int qr,int mo)  
{  
    if(l>=ql && r<=qr)  
    {  
        maxn=max(maxn,p[mo][o].maxv);  
        minn=min(minn,p[mo][o].minv);  
    }  
    else  
    {  
        int m=(l+r)>>1;  
        if(ql<=m)query2(o<<1,l,m,ql,qr,mo);  
        if(qr>m)query2((o<<1)+1,m+1,r,ql,qr,mo);  
    }  
}  
  
void query1(int o,int l,int r,int ql,int qr,int l2,int r2)  
{  
    if(l>=ql && r<=qr)  
    {  
        query2(1,1,n,l2,r2,o);  
    }  
    else  
    {  
        int m=(l+r)>>1;  
        if(ql<=m)query1(o<<1,l,m,ql,qr,l2,r2);  
        if(qr>m)query1((o<<1)+1,m+1,r,ql,qr,l2,r2);  
    }  
}  
  
void update2(int o,int l,int r,int q,int val,int mo)  
{  
    if(l==r)  
    {  
        if(val==-1)  
        {  
            p[mo][o].maxv=max(p[mo<<1][o].maxv,p[(mo<<1)+1][o].maxv);  
            p[mo][o].minv=min(p[mo<<1][o].minv,p[(mo<<1)+1][o].minv);  
            return;  
        }  
        p[mo][o].maxv=p[mo][o].minv=val;  
        return;  
    }  
    int m=(l+r)>>1;  
    if(q<=m)update2(o<<1,l,m,q,val,mo);else update2((o<<1)+1,m+1,r,q,val,mo);  
    p[mo][o].maxv=max(p[mo][o<<1].maxv,p[mo][(o<<1)+1].maxv);  
    p[mo][o].minv=min(p[mo][o<<1].minv,p[mo][(o<<1)+1].minv);  
}  
  
void update1(int o,int l,int r,int qx,int qy,int val)  
{  
    if(l==r)  
    {  
        update2(1,1,n,qy,val,o);  
    }  
    else  
    {  
        int m=(l+r)>>1;  
        if(qx<=m)update1(o<<1,l,m,qx,qy,val);else update1((o<<1)+1,m+1,r,qx,qy,val);  
        update2(1,1,n,qy,-1,o);  
    }  
}  
  
int main()  
{  
    scanf("%d\n",&n);  
    for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)scanf("%d",&a[i][j]);  
    build1(1,1,n);  
    scanf("%d\n",&m);  
    char s[5];  
    for(int i=1;i<=m;++i)  
    {  
        scanf("%s",s);  
        if(s[0]=='q')  
        {  
            int x,y,xx,yy;  
            scanf("%d%d%d%d",&x,&y,&xx,&yy);  
            minn=2147483647;maxn=0;  
            query1(1,1,n,x,xx,y,yy);  
            printf("%d %d\n",maxn,minn);  
        }  
        else  
        {  
            int x,y,c;  
            scanf("%d%d%d",&x,&y,&c);  
            update1(1,1,n,x,y,c);  
        }  
    }  
}  
```

---

## 作者：云浅知处 (赞：4)

二维RMQ+单点修改。

$n\le 500,Q\le40000$，嗯，刚看到题的时候我的思路是直接树套树 $O(Q\log^2n)$。

然后想了想觉得直接每行一个线段树，每次单点修改就在对应线段树上操作，每次查询就直接扫一遍每个要查询的行，对每一行在线段树上查询一下区间最大最小值。

复杂度是 $O(Qn\log n)$ 的，实际的话由于单点修改时 $O(\log n)$ 可能会更快。

感觉会卡着时限过，打算卡常。

于是，在我正准备去打线段树的时候，发现：

![](https://s3.ax1x.com/2020/11/16/Dk98Ts.png)

哈哈哈哈哈哈哈哈那我还打什么线段树，还想着卡常，哈哈哈哈哈哈

暴力 $O(Qn^2)$ 即可。

（甚至快读啥的都不需要，直接 `cin` 和 `cout` 都可以）

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstdlib>

#define MAXN 600

using namespace std;

int n,q,qwq[MAXN][MAXN];

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);//黑科技加速一下 cin&cout，毕竟咱是打的暴力，还是给人家一点尊重，卡一点常数吧=_=
	
	cin>>n;
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>qwq[i][j];
		}
	}
	
	cin>>q;
	
	while(q--){
		char opt;
		cin>>opt;
	   
		if(opt=='q'){
			int x1,x2,y1,y2;
			cin>>x1>>y1>>x2>>y2;
			
			int ans1=-0x3f3f3f3f;
			int ans2=0x3f3f3f3f;
			for(int i=x1;i<=x2;i++){
				for(int j=y1;j<=y2;j++){
					ans1=max(ans1,qwq[i][j]);
					ans2=min(ans2,qwq[i][j]);
				}
			}
			
			cout<<ans1<<" "<<ans2<<'\n';
		}
		else{
			int x,y,val;
			cin>>x>>y>>val;
			
			qwq[x][y]=val;
		}
	}

	return 0;
}
```

然后只用了 $2.53\text{s}$。。

![](https://s3.ax1x.com/2020/11/16/Dk9d6U.png)

qwq

---

## 作者：zhengrunzhe (赞：3)

显然这题可以KD树

不会kdtree的来[这里](https://www.luogu.org/blog/van/qian-tan-pian-xu-wen-ti-yu-k-d-tree)学，写的非常好

题意：矩形极值，单点修改

建树$O(n^2\log{n^2})$

单点修改直接依照kdt的比较原则往下走，找到了就改，回溯pushup，由于树高log，所以一次修改$O(\log{n^2})$

矩形查询单次是$O(\sqrt{n^2})=O(n)$，极值能够进行小剪枝，当前极值不比查过的极值优的时候，就可以不走整棵子树

所以总复杂度$O(n^2\log{n^2}+qn)$
```cpp
#include<cstdio>
#include<algorithm>
using std::nth_element;
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
template<class type>inline const type min(const type &a,const type &b)
{
	return a<b?a:b;
}
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
const int N=510,K=2,inf=2147483647;
int n,q;
int f;
struct point
{
	int d[K],w;
	inline point(){}
	inline point(const int &x,const int &y,const int &w=0):w(w){d[0]=x;d[1]=y;}
	inline const bool operator==(const point &p)const
	{
		for (int i=0;i<K;i++)
			if (d[i]^p.d[i])
				return 0;
		return 1;
	}
	inline const bool operator<(const point &p)const
	{
		if (d[f]^p.d[f])return d[f]<p.d[f];
		for (int i=0;i<K;i++)
			if (i^f&&d[i]^p.d[i])
				return d[i]<p.d[i];
	}
}a[N*N];
template<int k,int maxn>class KD_Tree
{
	private:
		struct tree
		{
			tree *son[2];
			point range,mn,mx;
			inline const void uprange()
			{
				for (int i=0;i<k;i++)
					mx.d[i]=max(range.d[i],max(son[0]->mx.d[i],son[1]->mx.d[i])),
					mn.d[i]=min(range.d[i],min(son[0]->mn.d[i],son[1]->mn.d[i]));
			}
			inline const void pushup()
			{
				mn.w=min(range.w,min(son[0]->mn.w,son[1]->mn.w));
				mx.w=max(range.w,max(son[0]->mx.w,son[1]->mx.w));
			}
			inline const bool out(const point &lower,const point &upper)
			{
				for (int i=0;i<k;i++)
					if (mn.d[i]>upper.d[i]||mx.d[i]<lower.d[i])
						return 1;
				return 0;
			}
			inline const bool in(const point &lower,const point &upper)
			{
				for (int i=0;i<k;i++)
					if (!(mn.d[i]>=lower.d[i]&&mx.d[i]<=upper.d[i]))
						return 0;
				return 1;
			}
			inline const bool at(const point &lower,const point &upper)
			{
				for (int i=0;i<k;i++)
					if (!(range.d[i]>=lower.d[i]&&range.d[i]<=upper.d[i]))
						return 0;
				return 1;
			}
		}*root,memory_pool[maxn],*tail,*null;
		int mx,mn;
		inline const void init()
		{
			tail=memory_pool;
			null=tail++;
			null->mx.w=-inf;null->mn.w=inf;
			root=null->son[0]=null->son[1]=null;
			for (int i=0;i<k;i++)null->mx.d[i]=-inf,null->mn.d[i]=inf;
		}
		inline tree *spawn(const point &x)
		{
			tree *p=tail++;
			p->range=p->mn=p->mx=x;
			p->son[0]=p->son[1]=null;
			return p;
		}
		inline tree *build(int l,int r,int d)
		{
			if (l>r)return null;
			int mid=l+r>>1;f=d;
			nth_element(a+l,a+mid,a+r+1);
			tree *p=spawn(a[mid]);
			if (l==r)return p;
			p->son[0]=build(l,mid-1,(d+1)%k);
			p->son[1]=build(mid+1,r,(d+1)%k);
			p->pushup();p->uprange();
			return p;
		}
		inline const void modify(tree *p,const point &x,int y,int d)
		{
			if (p->range==x)return p->range.w=y,p->pushup();
			f=d;modify(p->son[p->range<x],x,y,(d+1)%k);
			p->pushup();
		}
		inline const void querymax(tree *p,const point &x,const point &y)
		{
			if (p==null)return;
			if (p->mx.w<=mx)return;
			if (p->out(x,y))return;
			if (p->in(x,y))return mx=p->mx.w,void();
			if (p->at(x,y))mx=max(mx,p->range.w);
			querymax(p->son[0],x,y);querymax(p->son[1],x,y);
		}
		inline const void querymin(tree *p,const point &x,const point &y)
		{
			if (p==null)return;
			if (p->mn.w>=mn)return;
			if (p->out(x,y))return;
			if (p->in(x,y))return mn=p->mn.w,void();
			if (p->at(x,y))mn=min(mn,p->range.w);
			querymin(p->son[0],x,y);querymin(p->son[1],x,y);
		}
	public:
		inline const void build()
		{
			init();root=build(1,n*n,0);
		}
		inline const void modify(int x,int y,int z)
		{
			modify(root,point(x,y),z,0);
		}
		inline const int querymax(int x1,int y1,int x2,int y2)
		{
			mx=-inf;
			querymax(root,point(x1,y1),point(x2,y2));
			return mx;
		}
		inline const int querymin(int x1,int y1,int x2,int y2)
		{
			mn=inf;
			querymin(root,point(x1,y1),point(x2,y2));
			return mn;
		}
};
KD_Tree<K,N*N>kdt;
int main()
{
	read(n);
	for (int i=1;i<=n;i++)
		for (int w,j=1;j<=n;j++)
			read(w),a[(i-1)*n+j]=point(i,j,w);
	kdt.build();//kdt.check();
	read(q);char opt;
	for (int x1,y1,x2,y2;q--;)
		if (scanf(" %c",&opt),read(x1),read(y1),read(x2),opt=='q')
			read(y2),printf("%d %d\n",kdt.querymax(x1,y1,x2,y2),kdt.querymin(x1,y1,x2,y2));
		else kdt.modify(x1,y1,x2);
	return 0;
}
```

---

## 作者：Exber (赞：3)

## 题意
- #### 给你一个 $n\times n$ 的数组，有 $q$ 个操作，每个操作有两种类型，分别用字符 `q` 和 `c` 代表。
- #### `q`：求出数组中左上角坐标为 $(x1_i,y1_i)$，右下角坐标为 $(x2_i,y1_i)$ 的矩阵里所有元素的最小值和最大值。
- #### `c`：把数组中坐标为 $(x_i,y_i)$ 的位置的值改为 $v_i$。

## 做法
暴力……

刚开始想到了二维树状数组，可是一看时间限制，`8.00s`，这不就是让人跑暴力的吗……

题目的空间限制虽然标为 `0B`，但实际上这是误标，空间限制大得很呢！

## AC 代码
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n,q,a[505][505];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		char opt;
		cin>>opt; // 操作类型 
		if(opt=='q')
		{
			int x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			int maxx=-1e9,minn=1e9;
			for(int i=x1;i<=x2;i++)
			{
				for(int j=y1;j<=y2;j++)
				{
					maxx=max(maxx,a[i][j]);
					minn=min(minn,a[i][j]);
				}
			}
			cout<<maxx<<" "<<minn<<endl;
		}
		else
		{
			int x,y,v;
			cin>>x>>y>>v;
			a[x][y]=v;
		}
	}
	return 0;
}
```


---

## 作者：_lfxxx_ (赞：2)

**题目传送门：[UVA11297 Census](https://www.luogu.com.cn/problem/UVA11297)**

### 题目大意：（没翻译）
给定 $n\times n$ 的矩阵，后面跟着 $Q$ 组询问。

询问 $q$ 让你输出子矩阵的最大值和最小值。

询问 $c$ 让你更换某个元素。

**注意**

![时间](https://cdn.luogu.com.cn/upload/image_hosting/ftkjjugz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

**$8s$ ~~岂不白给？~~** 

**~~记住，UVA不会为难我们~~**

这样一来，直接暴力即可。相信不做过多解释大家也看得懂。

## 暴力代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[501][501];
int main(){
	int n,t;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);//读入矩阵
	cin>>t;
	while(t--){
		int s,x1,y1,x2,y2;
		char q;
		cin>>q;
		if(q=='q'){//q询问
			int maxs=0,mins=1e9;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			for(int i=x1;i<=x2;i++)
				for(int j=y1;j<=y2;j++){//暴力找
					maxs=max(maxs,a[i][j]);
					mins=min(mins,a[i][j]);
				}
			printf("%d %d\n",maxs,mins);
		}
		else{//c询问
			scanf("%d %d %d",&x1,&y1,&s);
			a[x1][y1]=s;
		}
	}
	return 0;
}
```
~~**暴力大法好！！！**~~

---

## 作者：ez_lcw (赞：1)

题意：给定一个 $n\times n$ 的网格，要求支持修改和询问某个矩阵的最大值和最小值。

解法多样，可以用二维线段树，我用的是 $kd-tree$。

那么这题就很裸了，我在这里只提几点需要注意的地方。

首先就是建树以及修改时的比较一定要判断当前维度相等的情况，这时就要比较下一维度。

不然你修改时可能永远找不到你要找的那个点，导致 $TLE$。

其次是 $up$ 的时候一定要判断有没有左右儿子，不然最小值会 $WA$。

代码如下：

```cpp
#include<bits/stdc++.h>

#define N 510
#define lc t[u].ch[0]
#define rc t[u].ch[1]
#define INF 0x7fffffff

using namespace std;

bool D;

struct Point
{
	int num[2],val;
	Point(){};
	Point(int x,int y,int vall)
	{
		num[0]=x,num[1]=y,val=vall;
	}
	bool operator == (Point a)
	{
		return num[0]==a.num[0]&&num[1]==a.num[1];
	}
	bool operator < (const Point &b) const
	{
		if(num[D]==b.num[D]) return num[D^1]<b.num[D^1];//需要注意的地方
		return num[D]<b.num[D];
	}
}p[N*N];

struct kdtree
{
	int ch[2],minn[2],maxn[2],maxval,minval;
	Point x;
}t[N*N];

struct data
{
	int maxn,minn;
	data(){};
	data(int a,int b)
	{
		maxn=a,minn=b;
	}
	data operator + (data a)
	{
		return data(max(maxn,a.maxn),min(minn,a.minn));
	}
};

int n,q,tot,root;

void up(int u)
{
	for(int i=0;i<2;i++)
	{
		t[u].maxn[i]=t[u].minn[i]=t[u].x.num[i];
		if(lc)
		{
			t[u].maxn[i]=max(t[u].maxn[i],t[lc].maxn[i]);
			t[u].minn[i]=min(t[u].minn[i],t[lc].minn[i]);
		}
		if(rc)
		{
			t[u].maxn[i]=max(t[u].maxn[i],t[rc].maxn[i]);
			t[u].minn[i]=min(t[u].minn[i],t[rc].minn[i]);
		}
	}
	t[u].minval=t[u].maxval=t[u].x.val;
	if(lc)t[u].minval=min(t[u].minval,t[lc].minval),t[u].maxval=max(t[u].maxval,t[lc].maxval);//需要注意的地方
	if(rc)t[u].minval=min(t[u].minval,t[rc].minval),t[u].maxval=max(t[u].maxval,t[rc].maxval);
}

int build(int l,int r,bool d)
{
	if(l>r) return 0;
	int u=(l+r)>>1;
	D=d,nth_element(p+l,p+u,p+r+1);
	t[u].x=p[u];
	lc=build(l,u-1,d^1);
	rc=build(u+1,r,d^1);
	up(u);
	return u;
}

bool in(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2)
{
	return x1<=X1&&y1<=Y1&&x2>=X2&&y2>=Y2;
}

bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2)
{
	return x1>X2||y1>Y2||x2<X1||y2<Y1;
}

data query(int u,int x1,int y1,int x2,int y2)
{
	if(out(x1,y1,x2,y2,t[u].minn[0],t[u].minn[1],t[u].maxn[0],t[u].maxn[1])) return data(-INF,INF);
	data ans=data(-INF,INF);
	if(in(x1,y1,x2,y2,t[u].minn[0],t[u].minn[1],t[u].maxn[0],t[u].maxn[1])) return data(t[u].maxval,t[u].minval);
	if(in(x1,y1,x2,y2,t[u].x.num[0],t[u].x.num[1],t[u].x.num[0],t[u].x.num[1])) ans=ans+data(t[u].x.val,t[u].x.val);
	ans=ans+query(lc,x1,y1,x2,y2);
	ans=ans+query(rc,x1,y1,x2,y2);
	return ans;
}

void update(int u,Point x,bool d)
{
	if(t[u].x==x)
	{
		t[u].x.val=x.val;
		up(u);
		return;
	}
	D=d;
	if(x<t[u].x) update(lc,x,d^1);
	else update(rc,x,d^1); 
	up(u);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			int x;
			scanf("%d",&x);
			p[++tot]=Point(i,j,x);
		}
	}
	root=build(1,n*n,0);
	scanf("%d",&q);
	while(q--)
	{
		char ch=getchar();
		while(ch!='q'&&ch!='c') ch=getchar();
		if(ch=='q')
		{
			int x1,y1,x2,y2;//左上、右下 
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			data ans=query(root,x1,y1,x2,y2);
			printf("%d %d\n",ans.maxn,ans.minn);
		}
		if(ch=='c')
		{
			int x,y,val;
			scanf("%d%d%d",&x,&y,&val);
			update(root,Point(x,y,val),0);
		}
	}
}
```


---

## 作者：to_be_continued (赞：1)

在UVA水题时看到这题，**时限8s,~~岂不白给~~**

题意：
	给你一个n*n的矩阵，有Q次操作
    
   q:查询从x1,y1开始到x2,y2这个矩阵中的最大值
   
   c:将x,y这个数改为v
   
	n<=500,Q<=40000
	
   ~~500难道不是什么算法都能过吗~~
   
那么我在这里介绍一下线段树的做法。

不会线段树的同学可以去看看——[**线段树**](https://www.luogu.com.cn/problem/P3372)差不多就是一个板子的修改

首先这肯定是一个二维的，那么我们就要用一个类，开500颗线段树

每次暴力枚举x1-x2，因为我们开了500颗线段树，所以每一行y1-y2的最大值我们是可以很快的求出来的。
~~又是8s,岂不白给~~

然后接下来就是怎么改了，怎么改呢，看看时限，不如暴力。
直接暴力修改，但是怎么说也写了线段树不是吗，那就找到哪一行，然后直接把这个值加上v-现在的值，用线段树的修改操作，还不用打lazy标记。

Code

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read(){//一个正常不过的快读
    int AK = 1, IOI  = 0;
    char ch = 0;
    while (ch < '0' || ch > '9'){
        AK = ch =='-'?-1:1;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0'){
        IOI *= 10;
        IOI += ch - 48;
        ch = getchar();
    }
    return AK * IOI;
}
inline int left_son(int x){
    return x << 1;
}
inline int right_son(int x){
    return x << 1 ^ 1;
}
struct nod{
    int a[501];
    int ans_min[501 << 2];
    int ans_max[501 << 2];
    void push_up(int x){
        ans_max[x] = std::max (ans_max[left_son(x)], ans_max[right_son(x)]);
        ans_min[x] = std::min (ans_min[left_son(x)], ans_min[right_son(x)]);
    }    
    void build_tree(int x, int left, int right){//建树
        if (left == right){
            ans_max[x] = a[left];
            ans_min[x] = a[left];
            return ;
        }
        int middle = (left + right) >> 1;
        build_tree(left_son(x), left, middle);
        build_tree(right_son(x), middle + 1, right);
        push_up(x);
    }
    void modify_data(int modify_left, int modify_right, int left, int right, int x, int k){//修改
        if (modify_left <= left && modify_right >= right){
            ans_min[x] += k;
            ans_max[x] += k;
            return ;
        }
        int middle = (left + right) >> 1;
        if (modify_left <= middle){
            modify_data(modify_left, modify_right, left, middle, left_son(x), k);
        }
        if (modify_right > middle){
            modify_data(modify_left, modify_right, middle + 1, right, right_son(x), k);
        }
        push_up(x);
    }
    int find_find1(int x, int y, int left, int right, int k){//查询最大
        if (x <= left && y >= right){
            return ans_max[k];
        }
        int middle = (left + right) >> 1;
        int answer = 0;
        if (x <= middle){
            answer = find_find1(x, y, left ,middle, left_son(k));
        }
        if (y > middle){
            answer = std::max (answer, find_find1(x, y, middle + 1, right, right_son(k)));
        }
        return answer;
    }
    int find_find2(int x, int y, int left, int right, int k ){//查询最小
        if (x <= left && y >= right){
            return ans_min[k];
        }
        int middle = (left + right) >> 1;
        int answer = 0x7f7f7f7f;
        if (x <= middle){
            answer = std::min (answer, find_find2(x, y, left, middle, left_son(k)));
        }
        if (y > middle){
            answer = std::min (answer, find_find2(x, y, middle + 1, right, right_son(k)));
        }
        return answer;
    }
} a[501];//500颗线段树
int main(){
    int n = read();
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j ++){
            a[i] . a[j] = read();
        }
        a[i] . build_tree(1, 1, n);//对该行建一颗线段树
    }
    int Q = read();
    while (Q--){
        char ch = 0;
        cin >> ch;
        if (ch == 'q'){
            int x1 = read(), y1 = read(), x2 = read(), y2 = read();
            int Max = 0;
            int Min = 0x7f7f7f7f;
            for (int i = x1; i <= x2; i ++){//找到每一行的最大最小值，进行比较
                int k = a[i] . find_find1(y1, y2, 1, n, 1);
                Max = std::max (Max, k);
                k = a[i] . find_find2(y1, y2, 1, n, 1);
                Min = std::min (Min, k);
            }
            printf("%d %d\n", Max, Min);
        } else{
            int x = read(), y = read(), z = read();
            a[x] . modify_data(y, y, 1, n, 1, z - a[x] . a[y]);//直接暴力修，修完之后把该值换为z以防之后该值还有修改然后出错
            a[x] . a[y] = z;
        }
    }
}
```



---

## 作者：Super_Cube (赞：1)

# 题目大意：

给你一个 $N \times N$ 的矩阵和 $Q$ 次操作，操作有两种形式：

1. $q$ $x_1$ $y_1$ $x_2$ $y_2$：输出 $(x_1,y_1)$ 到 $(x_2,y_2)$ 之间的最大值和最小值。

2. $c$ $x$ $y$ $v$：将点 $(x_1,y_1)$ 的值修改为 $v$。

---
# 思路：

作为蒟蒻，拿到这道题的思路应该是什么呢？

相信大家都会想到两个字：**暴力**。

那么，暴力该如何做呢？

+ 操作1：

循环扫一遍，直接统计就好啦。
```cpp
Max=1<<31,Min=1<<30;
scanf("%d%d",&x2,&y2);
for(register int i=x1;i<=x2;++i){
	for(register int j=y1;j<=y2;++j){
		if(Max<a[i][j])Max=a[i][j];
		if(Min>a[i][j])Min=a[i][j];
	}
}printf("%d %d\n",Max,Min);
```

+ 操作2：

直接重新输入一遍点 $(x_1,y_1)$ 的值就完了。

`scanf("%d",&a[x1][y1]);`

**是不是非常的简洁明了呢？**

时间复杂度：$O(QN^2)$。

---

# Code：
```cpp
#include<cstdio>
int a[505][505],n,T,i,j,x1,x2,y1,y2,Max,Min;
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			scanf("%d",&a[i][j]);
		}
	}scanf("%d",&T);
	while(T--){
		char x;scanf("\n%c",&x);
		scanf("%d%d",&x1,&y1);
		if(x=='q'){
			Max=1<<31,Min=1<<30;
			scanf("%d%d",&x2,&y2);
			for(register int i=x1;i<=x2;++i){
				for(register int j=y1;j<=y2;++j){
					if(Max<a[i][j])Max=a[i][j];
					if(Min>a[i][j])Min=a[i][j];
				}
			}printf("%d %d\n",Max,Min);
		}else scanf("%d",&a[x1][y1]);
	}
	return 0;
}
```

---

## 作者：int127 (赞：1)

### 思路

二维线段树。

**但是，**
> 时间限制 8.00s。

于是...上暴力吧。

单个测试点时间复杂度 $\Theta(n^2)$。

### 分析

$q$ 操作：查找左上角为 $(x_1,y_1)$，右下角为 $(x_2,y_2)$ 的矩形中的 $\max$ 与 $\min$。

循环查找即可。

```cpp
int v=-inf;//max
int vv=inf;//min
for(int i=x;i<=xx;i++){
	for(int j=y;j<=yy;j++){
		v=max(v,a[i][j]);//求max
		vv=min(vv,a[i][j]);//求min
	}
}
```

$c$ 操作：将 $(x,y)$ 的点改成 $c$。

直接改。

```cpp
a[x][y]=delta;//这里的delta就是上文的c
```

温馨提示：多组数据，过不了检查一下输出格式。

### AC Record

[Record](https://www.luogu.com.cn/record/51422217)

---

## 作者：0nullptr (赞：1)

题目传送门：[UVA11297 Census](https://www.luogu.org/problem/UVA11297)

**题意简述：**

- 给定一个 $n\times n$ 的矩阵，要求其子矩阵的最大、最小值，同时支持单点修改。

这是一道十分经典的二维$\text{RMQ}$问题，可以通过二维数据结构解决。例如四叉树或者是线段树套线段树。但是这些高级数据结构都十分难写难调，我们希望有一些更简单的方法解决此题 ~~拯救头发~~。

注意到 $n\le100,Q\le40000$ ,而且UVA很友好的将时限开到了8s，那么我们只需要一个时间复杂度为 $O(Qn^2)$ 的暴力就可以轻松氵过该题 ~~运行时间不到3s~~。代码如下：

```cpp
#include <iostream>
#define MAXN 1005
#define INF 0x3f3f3f3f
using namespace std;

int n, q, mmp[MAXN][MAXN]/*mmp数组用于存储每个点的权值*/;
int main() {
    cin>>n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin>>mmp[i][j];
    cin>>q;
    while (q--) {
        char op;
        cin>>op;
        if (op == 'q') {
            int x1, x2, y1, y2;
            cin>>x1>>y1>>x2>>y2;
            int maxx = -INF, minn = INF;
            for (int i = x1; i <= x2; i++)
                for (int j = y1; j <= y2; j++) {
                    maxx = max(maxx, mmp[i][j]);
                    minn = min(minn, mmp[i][j]);
                }
//暴力O(n^2)遍历子矩阵，获取最大值和最小值
            cout<<maxx<<" "<<minn<<endl;
        } else {
            int x, y, val;
            cin>>x>>y>>val;
            mmp[x][y] = val;
//简单的O(1)单点修改
        }
    }
    return 0;
}
```

---

## 作者：_CHO (赞：0)

~~据说这题暴力能过~~

~~针不戳~~



------------

我猜这题的正解应该该是一棵线段树套线段树

这样珂以在 $O(qlog^2n)$ 的时间内完成询问

~~但是我太弱了写不来树套树~~

那么我们来500棵线段树

回答询问的复杂度为 $O(qnlogn)$ 题目的$8s$时限戳戳有余

每一行建一棵树，询问时对每一行暴力循环，行内使用线段树查询即可。

题解中已经有了朴素的堆式存储写法

那我就来一个动态开点

Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000;
const int inf = 0x7fffffff;
struct Tree{
	int max,min;
};
int n,m;
int a[maxn][maxn];
int rt[maxn];
int maxv[maxn*maxn],minv[maxn*maxn],cnt;
int ls[maxn*maxn],rs[maxn*maxn];
inline void pushup(int o){
	maxv[o] = max(maxv[ls[o]],maxv[rs[o]]);
	minv[o] = min(minv[ls[o]],minv[rs[o]]);
}
inline void build(int &o,int l,int r,int t[]){
	o = ++cnt;
	if(l==r){
		maxv[o] = minv[o] = t[l];
		return ;
	}
	int mid=l+r>>1;
	build(ls[o],l,mid,t);
	build(rs[o],mid+1,r,t);
	pushup(o);
}
inline void optset(int o,int l,int r,int q,int v){
	if(l==r){
		maxv[o] = minv[o] = v;
		return ;
	}
	int mid=l+r>>1;
	if(q<=mid) optset(ls[o],l,mid,q,v);
	else optset(rs[o],mid+1,r,q,v);
	pushup(o);
	return ;
}
inline Tree query(int o,int l,int r,int ql,int qr){
	Tree ret;
	ret.max=-inf;ret.min=inf;
	if(ql<=l&&r<=qr){
		ret.max=maxv[o];
		ret.min=minv[o];
		return ret;
	}
	int mid=l+r>>1;
	if(ql<=mid){
		Tree s = query(ls[o],l,mid,ql,qr);
		ret.max=s.max;ret.min=s.min;
	}
	if(qr>mid){
		Tree s = query(rs[o],mid+1,r,ql,qr);
		ret.max=max(ret.max,s.max);
		ret.min=min(ret.min,s.min);
	}
	return ret;
}
int main(){
	cin>>n;
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j){
			cin>>a[i][j];
		}
		build(rt[i],1,n,a[i]);
	}
	cin>>m;
	while(m--){
		char s[8];scanf("%s",s);
		if(s[0]=='q'){
			int x,y,_x,_y;
			cin>>x>>y>>_x>>_y;
			int mn=inf,mx=-inf;
			for(register int i=x;i<=_x;++i){
				Tree t = query(rt[i],1,n,y,_y);
				mx=max(mx,t.max);
				mn=min(mn,t.min);
			}
			printf("%d %d\n",mx,mn);
		}
		if(s[0]=='c'){
			int x,y,v;
			cin>>x>>y>>v;
			optset(rt[x],1,n,y,v);
		}
	}
	return 0;
}
```

---

## 作者：Karry5307 (赞：0)

[安利一下我的博客](https://karry5307.github.io/)
### 题意
给定一个$n\times n$的矩阵，支持单点修改，查询子矩阵最大值和子矩阵最小值。
### 题解
经典的二维带修RMQ问题。

一个暴力的思想是建$500$棵线段树，对于修改就在对应的线段树上修改，对于查询的时候就一行一行的查询，每一次把答案与之前的答案合并一下就好了qwq。

这样子做的时间复杂度是$O(qn\log n)$，不会TLE，但是跑的极慢，在测的时候跑了$1070$ms，没有树套树跑的快……
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=551;
struct SegmentTree{
    ll l,r,minn,maxn;  
};
SegmentTree tree[MAXN][MAXN<<2];
ll size,qcnt,lx,ly,rx,ry,x,y,val,minn,maxn;
char ch;
ll num[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void update(ll dim,ll node)
{
    tree[dim][node].maxn=max(tree[dim][node<<1].maxn,tree[dim][(node<<1)|1].maxn);
    tree[dim][node].minn=min(tree[dim][node<<1].minn,tree[dim][(node<<1)|1].minn);
}
inline void create(ll dim,ll l,ll r,ll node)
{
    tree[dim][node].l=l,tree[dim][node].r=r;
    if(l==r)
    {
        tree[dim][node].minn=tree[dim][node].maxn=num[l];
        return;
    }
    ll mid=(l+r)>>1;
    create(dim,l,mid,node<<1);
    create(dim,mid+1,r,(node<<1)|1);
    update(dim,node);
}
inline void changePoint(ll dim,ll pos,ll val,ll node)
{
    if(tree[dim][node].l==tree[dim][node].r)
    {
        tree[dim][node].minn=tree[dim][node].maxn=val;
        return;
    }
    ll mid=(tree[dim][node].l+tree[dim][node].r)>>1;
    if(pos<=mid)
    {
        changePoint(dim,pos,val,node<<1);
    }
    else
    {
        changePoint(dim,pos,val,(node<<1)|1);
    }
    update(dim,node);
}
inline ll queryMax(ll dim,ll l,ll r,ll node)
{
    if(l<=tree[dim][node].l&&r>=tree[dim][node].r)
    {
        return tree[dim][node].maxn;
    }
    ll mid=(tree[dim][node].l+tree[dim][node].r)>>1,res=0;
    if(l<=mid)
    {
        res=max(res,queryMax(dim,l,r,node<<1));
    }
    if(r>mid)
    {
        res=max(res,queryMax(dim,l,r,(node<<1)|1));
    }
    return res;
}
inline ll queryMin(ll dim,ll l,ll r,ll node)
{
    if(l<=tree[dim][node].l&&r>=tree[dim][node].r)
    {
        return tree[dim][node].minn;
    }
    ll mid=(tree[dim][node].l+tree[dim][node].r)>>1,res=0x7fffffff;
    if(l<=mid)
    {
        res=min(res,queryMin(dim,l,r,node<<1));
    }
    if(r>mid)
    {
        res=min(res,queryMin(dim,l,r,(node<<1)|1));
    }
    return res;
}
int main()
{
    size=read();
    for(register int i=1;i<=size;i++)
    {
        for(register int j=1;j<=size;j++)
        {
            num[j]=read();
        }
        create(i,1,size,1);
    }
    qcnt=read();
    for(register int i=0;i<qcnt;i++)
    {
        cin>>ch;
        if(ch=='q')
        {
            lx=read(),ly=read(),rx=read(),ry=read();
            maxn=0,minn=0x7fffffff;
            for(register int j=lx;j<=rx;j++)
            {
                maxn=max(maxn,queryMax(j,ly,ry,1));
                minn=min(minn,queryMin(j,ly,ry,1));
            }
            printf("%d %d\n",maxn,minn);
        }
        else
        {
            x=read(),y=read(),val=read();
            changePoint(x,y,val,1);
        }
    }
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、题意简述

给出一个 $N\times N$（$0\le N\le500$）的方阵，每个方阵中有一个数。

接下来是 $Q$（$Q\le40000$）次操作。有两种可能：

- 以 `q` 开头。此时再输入 $4$ 个数 $x_1$、$y_1$、$x_2$、$y_2$，求出所圈出的长方形中最大和最小的数。

- 以 `c` 开头。此时再输入 $3$ 个数 $x$、$y$、$v$，表示将第 $x$ 行第 $y$ 列的数修改为 $v$。

### 二、思路

一看数据范围和时间限制，直接暴力算法吧。

最坏的情况下，$N=500$，$Q=40000$，每次操作都是以 `q` 开头，每次 $x_1=y_1=1$，$x_2=y_2=500$，此时：

- 初始化时间复杂度 $O(500\times500)=O(250000)$。

- 查询时间复杂度 $O(500\times500\times40000)=O(10^{10})$。

此时的时间复杂度看起来虽高，但考虑一下 $8s$ 的时间限制，暴力足够了。

### 三、完整代码

```cpp
#include<cstdio>
using namespace std;
int n,m;
int graph[501][501];
int main()
{
	scanf("%d",&n);//初始化。
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&graph[i][j]);
		}
	}
	scanf("%d",&m);
	while(m--)
	{
		char op[2];
		scanf("%s",&op);
		if(op[0]=='c')
		{
			int x,y,v;
			scanf("%d%d%d",&x,&y,&v);
			graph[x][y]=v;
		}
		else
		{
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			int minn=40005,maxn=0;
			for(int i=x1;i<=x2;i++)//求最值。
			{
				for(int j=y1;j<=y2;j++)
				{
					if(graph[i][j]<minn)
					{
						minn=graph[i][j];
					}
					if(graph[i][j]>maxn)
					{
						maxn=graph[i][j];
					}
				}
			}
			printf("%d %d\n",maxn,minn);//输出。
		}
	}
	return 0;//完结撒花！
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：PosVII (赞：0)

**前言**

------------

机房巨佬说这是水题。笑死，谁信啊。

看到时间限制 $8s$，笑死，数据绝对很大，看到数据，笑死，先看题面。

此题应该改一下时限，否则这道题难度虚高了。

**思路**

------------

非常简单，不需要任何算法，仅需暴力即可。

- "C" 即插入，直接赋值。
- "Q" 即询问，询问当前子矩阵中的最大值和最小值。

但是为了表达对这种题的尊敬，我们可以进行一些小小的优化。

最终在暴力中时间复杂度第 $4$。

**code**

------------

```
#include<cstdio>
#define max(x,y) x>y?x:y
#define min(x,y) x<y?x:y
int n,arr[506][506],maxn,minn,q,x,y,xx,yy; 
char ask;
int main() {
	scanf("%d",&n);
	for(register int i=1;i<=n;++i) {
		for(register int j=1;j<=n;++j) {
			scanf("%d",&arr[i][j]);
		}
	}
	scanf("%d",&q);
	while(q--) {
		scanf("\n%c",&ask);
		if(ask=='c') {
			scanf("%d %d",&x,&y);
			scanf("%d",&arr[x][y]);
			continue;
		}
		scanf("%d %d %d %d",&x,&y,&xx,&yy);
		maxn=-0x3f3f3f3f;
		minn=0x3f3f3f3f;
		for(register int i=x;i<=xx;++i) {
			for(register int j=y;j<=yy;++j) {
				maxn=max(maxn,arr[i][j]);
				minn=min(minn,arr[i][j]);
			}
		} 
		printf("%d %d\n",maxn,minn);
	}
	return 0;
} 
```

**总结**

------------

非常简单的紫题，完全可以暴力解决，但如果时间限制在 $2$ 秒以内的话暴力是肯定过不了的。

---

## 作者：HYdroKomide (赞：0)

# **正文：**
### 思路：
一道维护矩阵的紫题，乍看上去用线段树，差点当场关闭了页面。结果仔细一看，时限 $8$ 秒，暴力复杂度 $O(qn^2)$，无论如何都可以过，所以我们直接暴力维护代码量最少。

相信不需要过多解释，代码部分的详解放在注释中。
### 程序如下：
```cpp
#include<cstdio>
#define max(x,y) x>y?x:y//手打max和min
#define min(x,y) x<y?x:y
using namespace std;
int q,n,x,y,z,x1,x2,y1,y2,a[601][601];
char flag;
int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	scanf("%d",&q);
	while(q--){
		scanf("\n%c",&flag);//因为scanf中的%c是直接读取下一个字符，也就是会直接读取到回车符，所以我们这里先加了一个换行再进行读入
		if(flag=='q'){//如果是q就查找区间中最大值和最小值
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			int maxn=-0x3f3f3f3f,minn=0x3f3f3f3f;
			for(register int i=x1;i<=x2;i++)
				for(register int j=y1;j<=y2;j++)
					maxn=max(maxn,a[i][j]),minn=min(minn,a[i][j]);
			printf("%d %d\n",maxn,minn);
		}
		else{//否则更改矩阵元素
			scanf("%d%d%d",&x,&y,&z);
			a[x][y]=z;
		}
	}
	return 0;
}
```
[最后跑了2.51s](https://www.luogu.com.cn/record/49073654)
### **THE END**

---

## 作者：hswfwkj_ (赞：0)

### 记住，永远不要相信洛谷上 UVA 的题目难度
题目链接：[UVA11297](https://www.luogu.com.cn/problem/UVA11297)
### 题意简述：
输入一个 $n*n$ 的地图，处理 $m$ 次询问，$q$ 询问输入四个数据 $x1,y1,x2,y2$，代表一个矩形左上角坐标 $(x1,y1)$ 和右下角坐标 $(x2,y2)$
，输出这个矩形中的最大值和最小值。$c$ 询问输入三个数据,$x,y,t$，代表将坐标为 $(x1,y1)$ 的点的数值改为 $t$。

打开题目，先看时限：

![](https://cdn.luogu.com.cn/upload/image_hosting/jmnk3eus.png)

整整 $8$ 秒，这不摆明了让我们暴力吗？

对每次询问进行处理，直接一个一个扫找最大值就行了。

贴上暴力代码，想必不用做过多解释：
```cpp
#include<iostream>
using namespace std;
int a[600][600];
int main(){
	int n,m,i,j; 
	cin>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cin>>a[i][j];
	cin>>m;
	while(m--){
		char c;
		cin>>c;
		if(c=='c'){//处理 c 询问
			int x,y,tot;
			cin>>x>>y>>tot;
			a[x][y]=tot;
		}
		if(c=='q'){//处理 q 询问
			int maxn=-2147483467,mins=2147483647;
			int x1,x2,y1,y2;
			//cout<<maxn<<mins<<endl;调试代码
			cin>>x1>>y1>>x2>>y2;
			for(i=x1;i<=x2;i++){
				for(j=y1;j<=y2;j++){
					maxn=max(maxn,a[i][j]);//找最大值
					mins=min(mins,a[i][j]);//找最小值		
				}
			}
			printf("%d %d\n",maxn,mins);
		}
	}
	return 0;
}
```

---

