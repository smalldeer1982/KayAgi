# Leaving the Bar

## 题目描述

For a vector $ \vec{v} = (x, y) $ , define $ |v| = \sqrt{x^2 + y^2} $ .

Allen had a bit too much to drink at the bar, which is at the origin. There are $ n $ vectors $ \vec{v_1}, \vec{v_2}, \cdots, \vec{v_n} $ . Allen will make $ n $ moves. As Allen's sense of direction is impaired, during the $ i $ -th move he will either move in the direction $ \vec{v_i} $ or $ -\vec{v_i} $ . In other words, if his position is currently $ p = (x, y) $ , he will either move to $ p + \vec{v_i} $ or $ p - \vec{v_i} $ .

Allen doesn't want to wander too far from home (which happens to also be the bar). You need to help him figure out a sequence of moves (a sequence of signs for the vectors) such that his final position $ p $ satisfies $ |p| \le 1.5 \cdot 10^6 $ so that he can stay safe.

## 样例 #1

### 输入

```
3
999999 0
0 999999
999999 0
```

### 输出

```
1 1 -1 
```

## 样例 #2

### 输入

```
1
-824590 246031
```

### 输出

```
1 
```

## 样例 #3

### 输入

```
8
-67761 603277
640586 -396671
46147 -122580
569609 -2112
400 914208
131792 309779
-850150 -486293
5272 721899
```

### 输出

```
1 1 1 1 1 1 1 -1 
```

# 题解

## 作者：chenxia25 (赞：6)

**[Portal](https://www.luogu.com.cn/problem/CF995C)**

考虑归纳，试图合并两个向量使得 $n$ 减少 $1$。

考虑如果直接合并随意的两个向量。那么最差的情况就是两个向量是垂直的，这时候斜边大于直角边。如果两个边相等都等于 $a$ 的话，那么合并出来的长度就是 $\sqrt2a$。很显然，把 $10^6$ 乘两遍 $\sqrt2$ 你就没掉了。总之这种 naive 的方法是不行的。况且归纳本来就要求除了规模缩小之外，其他条件都不变，而这里显然可能将值域扩大。

注意到两个向量的长度固定了之后，影响他们的和的长度的只有它们的夹角。先不严谨地设它们长度相等，都等于 $x$。那么考虑到等边三角形，显然有它们的和的长度 $\leq x$ 当且仅当夹角 $\alpha\leq 60^\circ$。但是有可能它们的长度不相等，这时候我们需要证明一下 $x\leq$ 较长边。

其实并不难证明。如图，$\boldsymbol a=\overrightarrow{OP}$ 为第一个向量（较大），分别以 $O,P$ 为圆心，$OP$ 为半径作圆。那么第二个向量 $\boldsymbol b$ 显然为 $O$ 与 $OQ,OQ',OQ''$ 上任意一点的连线，其中 $OQ,OQ',OQ''$ 分别为夹角 $<,=,> 60^\circ$ 的三种情况。那么 $|\boldsymbol a+\boldsymbol b|\leq |\boldsymbol a|$ 显然当且仅当该夹角 $\alpha$ 下的 $OQ$ 完全在圆 $O$ 内，肉眼可见 $\alpha\leq 60^\circ$。

![](https://s1.ax1x.com/2020/10/17/0Ly7NR.png)

有了这个结论就不难想到做法了。我们找任意三条向量，它们中夹角最小的一对的夹角显然要 $\leq\dfrac{360^\circ}6=60^\circ$，那么每次可以选择这组向量合并来归纳。到最后还剩 $n=2$ 的时候，不能保证能找到这组向量了，不过这是无所谓了，乘个 $\sqrt2$ 恰好增长不到 $1.5$ 倍。

接下来考虑实现细节：

- 我不会算向量夹角，不过无伤大雅。只需要每次找到所有可能合成的向量中最短的那个即可。
- 如何合并？需要做的操作是将当前一个向量取反，而任意时刻一个向量可能是多个原向量的化合物，暴力取反大概会炸。考虑到每次恰好合并两个，那就建一棵二叉树，合并用虚拟节点连接两个根，打标记（就是树上差分），最后 DFS 一遍即可。一开始觉得很奇怪，但后来发现和 official solution 重合？然后发现其实还可以无脑启发式。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define ppb pop_back
const double inf=1e14;
const int N=100000;
int n;
pair<int,int> a[2*N+1];
int son[2*N+1][2],prod[2*N+1][2];
vector<int> v;
pair<int,int> operator+(pair<int,int> x,pair<int,int> y){return mp(x.X+y.X,x.Y+y.Y);}
pair<int,int> operator*(int x,pair<int,int> y){return mp(x*y.X,x*y.Y);}
pair<int,int> operator-(pair<int,int> x,pair<int,int> y){return x+(-1)*y;}
double len(pair<int,int> x){return sqrt(1ll*x.X*x.X+1ll*x.Y*x.Y);}
int ans[N+1];
void dfs(int x=2*n-1,int now=1){
	if(x>n){
		dfs(son[x][0],now*prod[x][0]);
		dfs(son[x][1],now*prod[x][1]);
	}
	else ans[x]=now;
}
int main(){
	cin>>n;
	if(n==1)return puts("1"),0;
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].X,&a[i].Y),v.pb(i);
	for(int i=1;i<=n-2;i++){
		int x=v.back();v.ppb();
		int y=v.back();v.ppb();
		int z=v.back();v.ppb();
		pair<double,pair<pair<int,int>,pair<int,int> > > mn;
		mn.X=inf;
		mn=min(mn,mp(len(a[x]+a[y]),mp(mp(x,1),mp(y,1))));
		mn=min(mn,mp(len(a[x]-a[y]),mp(mp(x,1),mp(y,-1))));
		mn=min(mn,mp(len(a[x]+a[z]),mp(mp(x,1),mp(z,1))));
		mn=min(mn,mp(len(a[x]-a[z]),mp(mp(x,1),mp(z,-1))));
		mn=min(mn,mp(len(a[y]+a[z]),mp(mp(y,1),mp(z,1))));
		mn=min(mn,mp(len(a[y]-a[z]),mp(mp(y,1),mp(z,-1))));
		a[i+n]=mn.Y.X.Y*a[mn.Y.X.X]+mn.Y.Y.Y*a[mn.Y.Y.X];
		son[i+n][0]=mn.Y.X.X,prod[i+n][0]=mn.Y.X.Y;
		son[i+n][1]=mn.Y.Y.X,prod[i+n][1]=mn.Y.Y.Y;
		v.pb(i+n);
		if(son[i+n][0]==x&&son[i+n][1]==y)v.pb(z);
		if(son[i+n][0]==x&&son[i+n][1]==z)v.pb(y);
		if(son[i+n][0]==y&&son[i+n][1]==z)v.pb(x);
	}
	int x=v.back();v.ppb();
	int y=v.back();v.ppb();
	pair<double,pair<pair<int,int>,pair<int,int> > > mn;
	mn.X=inf;
	mn=min(mn,mp(len(a[x]+a[y]),mp(mp(x,1),mp(y,1))));
	mn=min(mn,mp(len(a[x]-a[y]),mp(mp(x,1),mp(y,-1))));
	a[2*n-1]=mn.Y.X.Y*a[mn.Y.X.X]+mn.Y.Y.Y*a[mn.Y.Y.X];
	son[2*n-1][0]=mn.Y.X.X,prod[2*n-1][0]=mn.Y.X.Y;
	son[2*n-1][1]=mn.Y.Y.X,prod[2*n-1][1]=mn.Y.Y.Y;
	dfs();
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：dead_X (赞：6)

## 假的做法
先随机这些向量，然后贪心地选择是否变反（即选择操作后距离更小的方法）。

具体做法如下：

设前 $(k-1)$ 个向量通过这个算法得到的向量为 $(x_0,y_0)$ ，第 $k$ 个向量为 $(x',y')$ 。我们就贪心地取前 $k$ 个向量通过这个算法得到的向量为 $(x_0+x',y_0+y')$ 和 $(x_0-x',y_0-y')$ 中模长较小的那个。

* 会被奇奇怪怪的数据 hack 。

hack 的数据如下：

```
3
1000000 0
0 999999
600000 -600000
```

意思就是让你到 $(1000000,999999)$ 的地方然后进入死局。很可惜，似乎并没有什么比较好的处理方法。

但是 hack 数据是死的，人是活的！

## 假但是能过的做法
每次 ``random_shuffle`` 数列，按照原来的方法贪心，合法就输出。

* 很难被奇怪的数据 hack 。

## 代码
```
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
double dis(long long x,long long y)
{
    return sqrt((double)x*x+(double)y*y);
}
struct node
{
    int x,y,id;
}a[1000003];
int ans[1000003];
int main()
{
    srand(time(0));
    int n=read();
    int x=0,y=0;
    for(int i=1; i<=n; i++) a[i].x=read(),a[i].y=read(),a[i].id=i;
    while(1)
    {
        x=0,y=0;
        for(int i=1; i<=n; i++)
        {
            int p=a[i].x,q=a[i].y;
            if(dis(x+p,y+q)<dis(x-p,y-q)) x+=p,y+=q,ans[a[i].id]=1; else x-=p,y-=q,ans[a[i].id]=-1;
        }      
        if(dis(x,y)<=1.5e6) 
        {
            for(int i=1; i<=n; i++) printf("%d ",ans[i]);
            return 0;
        }
        random_shuffle(a+1,a+n+1);
    }
    return 0;
}
```

---

## 作者：45dino (赞：2)

介绍一个奇奇怪怪的做法。

（前置知识）向量相加：

设 $\vec{v_1}=(x1,y1),\vec{v_2}=(x2,y2)$ ，

则 $|\vec{v_1}+\vec{v_2}|=(x_1+x_2)^2+(y_1+y_2)^2$ 。

对于
>It can be shown that a solution always exists under the given constraints.

很多大佬都通过一些方法对向量进行合并，其实只用保证最终答案尽可能小就行了。

于是贪心地选择每一条向量是否要取反。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[100001];
double x[100001],y[100001],X,Y;
double rua(double x,double y)
{
	return x*x+y*y;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf %lf",&x[i],&y[i]);
	for(int i=n;i>=1;i--)
		if(rua(X-x[i],Y-y[i])>=rua(X+x[i],Y+y[i]))
		{
			X+=x[i];
			Y+=y[i]; 
			f[i]=1;
		}
		else
		{
			X-=x[i];
			Y-=y[i];
			f[i]=-1;
		}
	for(int i=1;i<=n;i++)
		cout<<f[i]<<" ";
	return 0;
}
```


---

## 作者：Hanx16Kira (赞：1)

# CF995C Leaving the Bar

[Luogu CF995C](https://www.luogu.com.cn/problem/CF995C)

[Codeforces 995C](https://codeforces.com/problemset/problem/995/C)

## Solution

刷随机化的题刷到这道，发现是前几天 % 你赛才考过的题，所以就来写一下题解，加深一下印象。

先是一种非常不动脑子的想法：将每个向量按顺序合并，如果合并完了向量的模大于了给定的最大值，那就将这个向量的方向取反然后合并。这种做法非常不动脑子以至于非常的好卡。发现出的问题在于顺序到底是什么顺序，不同的合并顺序会导致不同的结果。看到题目保证了一定有解，并且自己模拟下发现貌似有解的时候解的数量还不少。也就是说可以用随机化的方式确定顺序然后按照这种思路进行合并。如果合并完成过后答案符合条件就直接输出，否则就再随机一次顺序重新开始。

根据这种思路可以写出代码，然后交上去发现 TLE on 89。仔细再想了一下，发现可以用一种贪心的策略来优化这个合并的过程。每个向量的系数都有 $1,-1$ 两种选择，尝试将 $1,-1$ 两种情况都合并一下试试，取模长更小的那个作为最终答案。会发现这样试出答案的概率非常之高。再改了一下代码，最慢的点仅仅只用了 46ms，效率大大提升。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

namespace Hanx16qwq {
constexpr int _SIZE = 1e5, _MAXN = 1.5e6 * 1.5e6;
int n;

struct Vector { // 向量，重载了 + 和 -
    int x, y, id;

    Vector operator + (const Vector &a) const {
        return {x + a.x, y + a.y, 0};
    }

    Vector operator - (const Vector &a) const {
        return {x - a.x, y - a.y, 0};
    }
}a[_SIZE + 5];

int ans[_SIZE + 5];
mt19937 rnd(time(0)); // 用于随机化打乱

inline int sq(int x) {return x * x;}

int Check(Vector v) {
    return sq(v.x) + sq(v.y); // 计算向量模长，可能爆 int，所以记得开 long long
}

void main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++) 
        cin >> a[i].x >> a[i].y, a[i].id = i;
    
    while (true) {
        shuffle(a + 1, a + n + 1, rnd); // 随机打乱
        Vector res = {0, 0, 0}; // 初始状态

        for (int i = 1; i <= n; i++) { // 顺序合并向量
            if (Check(res + a[i]) < Check(res - a[i])) // 如果 + 比 - 更优
                res = res + a[i], ans[a[i].id] = 1;
            else // 否则 - 更优
                res = res - a[i], ans[a[i].id] = -1;
        }

        if (Check(res) <= _MAXN) { // 如果可行输出方案
            for (int i = 1; i <= n; i++)
                cout << ans[i] << ' ';
            
            return cout << '\n', void();
        }
    }
}
}

signed main() {
    Hanx16qwq::main();
    return 0;
}
```

---

## 作者：Karry5307 (赞：1)

### 题意

给定 $n$ 个向量 $\vec{v}$，你需要构造一个长度为 $n$ 的序列 $c$ 满足 $c_i\in\{-1,1\}$ 同时 $\left|\sum\limits_{i=1}^{n}c_i\vec{v_i}\right|\leq 1.5\times 10^6$。

$\texttt{Data Range:}1\leq n\leq 10^5$

### 题解

首先说一句，本做法不是正解。

拿到这个题目之后发现根本不会于是写了一个随机化，然后交上去发现 WA 了，结果改了一下随机策略然后就过了？？？？

一开始的策略是直接随机 $600$ 个序列然后依次去 check 结果 WA 6 了，接下来想了想可以这么做：在随机序列的同时利用贪心的思想，如果这一次随机到的 $c_i$ 会不合法那么直接用另一个即可。由于随机了 $600$ 次每一次都这么调整所以很难被卡掉。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
mt19937 mt(20050103);
ll n;
li rx,ry,lx,ly;
ll x[MAXN],y[MAXN],c[MAXN];
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
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		x[i]=read(),y[i]=read();
	}
	for(register int i=1;i<=600;i++)
	{
		rx=ry=lx=ly=0;
		for(register int j=1;j<=n;j++)
		{
			c[j]=mt()%2?1:-1,c[j]==1?rx+=x[j],ry+=y[j]:(rx-=x[j],ry-=y[j]);
			if(sqrt(rx*rx+ry*ry)>=1500000)
			{
				c[j]=-c[j],rx=lx,ry=ly;
				c[j]==1?rx+=x[j],ry+=y[j]:(rx-=x[j],ry-=y[j]);
			}
			lx=rx,ly=ry;
		}
		if(sqrt(rx*rx+ry*ry)<1500000)
		{
			for(register int j=1;j<=n;j++)
			{
				printf("%d ",c[j]);
			}
			return 0;
		}
	}
}
```

---

## 作者：tzc_wk (赞：1)

楼下用的都是什么~~沙雕~~神仙方法，爱了爱了。

这里介绍正解

考虑任意三个向量 $\vec{v_1},\vec{v_2},\vec{v_3}$，它们取反之后得到六个向量 $-\vec{v_1},-\vec{v_2},-\vec{v_3}$，根据抽屉原理，它们之间必有两个向量夹角 $\leq 60\degree$。

根据余弦定理 $a^2=b^2+c^2-2bc\cos\theta$，当 $\theta \leq 60 \degree$ 时，$2bc\cos\theta \geq bc$，记 $M=\max(b,c)$，则 $a^2 \leq b^2+c^2-bc \leq 2M^2-M^2=M^2$，也就是合并完这两个向量后得到的向量的模长一定不超过两个向量模长的较大值。

最后合并到只剩两个向量，根据上面的推论，这两个向量的模长一定不超过 $10^6$。此时枚举这两个向量分别选择什么方向，其中必有一种组合得到的向量 $\leq \sqrt{2}|\vec{v}|<1.5 \times 10^6$。

思想非常容易，可你真正写起来就会发现不那么好写，这里提供一些实现思路。

首先根据 $\vec{v_1}·\vec{v_2}=|\vec{v_1}|·|\vec{v_2}|·\cos{\theta}$ 计算向量的夹角。

其次递归实现比较困难。我是建了一个结构体叫做 $\texttt{data}$，维护 $8·10^5$ 个向量 $d_1,d_2,\dots,d_{800000}$。每个向量维护六个值 $x,y,fx,fy,cx,cy$，表示 $\vec{d_x}=cx\vec{d_{fx}}+cy\vec{d_{fy}}$。

```cpp
/*
Contest: -
Problem: Codeforces 995C
Author: tzc_wk
Time: 2020.10.16
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define pb			push_back
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define y1			y1010101010101
#define y0			y0101010101010
typedef pair<int,int> pii;
typedef long long ll;
const double pi=acos(-1);
inline double cross(double x1,double y1,double x2,double y2){
	return x1*x2+y1*y2;
}
inline double len(double x,double y){
	return sqrt(x*x+y*y);
}
inline double angle(double x1,double y1,double x2,double y2){
	if(x1==0&&y1==0) return pi;
	if(x2==0&&y2==0) return pi;
	return acos(cross(x1,y1,x2,y2)/len(x1,y1)/len(x2,y2));
}
int n,x[100005],y[100005],cur=0;
struct data{
	double tx,ty;
	int fx,fy;
	int cx,cy;
	data operator ~(){
		data ans=*this;
		ans.tx=-ans.tx;ans.ty=-ans.ty;
		ans.cx=-ans.cx;ans.cy=-ans.cy;
		return ans;
	}
} d[100005<<5];
inline data add(int x,int y,int cx,int cy){
	data ans;
	ans.tx=d[x].tx*cx+d[y].tx*cy;
	ans.ty=d[x].ty*cx+d[y].ty*cy;
	ans.cx=cx;ans.cy=cy;
	ans.fx=x;ans.fy=y;
	return ans;
}
int neg[100005<<5];
inline void dump(int x){
	if(x<=n) return;
//	printf("%d %d %d\n",x,d[x].fx,d[x].fy);
	neg[d[x].fx]=neg[x]*d[x].cx;
	neg[d[x].fy]=neg[x]*d[x].cy;
	dump(d[x].fx);dump(d[x].fy);
}
inline void dfs(int x,int y,int z,int w){
	if(z==n+1){
		d[++cur]=~d[x];d[++cur]=~d[y];
		vector<int> t;t.pb(x);t.pb(y);t.pb(cur-1);t.pb(cur);
		for(int i=0;i<4;i+=2) for(int j=1;j<4;j+=2){
			int u=t[i],v=t[j];
			if(len(d[u].tx+d[v].tx,d[u].ty+d[v].ty)<=1500000.0){
				if(i==2) neg[x]=-1;else neg[x]=1;
				if(j==3) neg[y]=-1;else neg[y]=1;
				dump(x);dump(y);return;
			}
		}
	}
	d[++cur]=~d[x];d[++cur]=~d[y];d[++cur]=~d[z];
	vector<int> t;t.pb(x);t.pb(y);t.pb(z);
	t.pb(cur-2);t.pb(cur-1);t.pb(cur);
	for(int i=0;i<6;i++) for(int j=0;j<i;j++){
		if((i%3)==(j%3)) continue;
		int a=t[i],b=t[j];
		if(angle(d[a].tx,d[a].ty,d[b].tx,d[b].ty)>=2.0*pi/3){
			d[++cur]=add(a,b,1,1);int nxt=3-(i%3)-(j%3);
//			printf("%d %d\n",a,b);
			if(nxt==0) dfs(cur,x,w,w+1);
			if(nxt==1) dfs(cur,y,w,w+1);
			if(nxt==2) dfs(cur,z,w,w+1);
			return;
		}
	}
}
int main(){
	scanf("%d",&n);if(n==1) return puts("1"),0;
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++){
		d[i].tx=x[i];d[i].ty=y[i];
		d[i].fx=i;d[i].fy=0;
		d[i].cx=1;d[i].cy=0;
	}
	cur=n;dfs(1,2,3,4);
	for(int i=1;i<=n;i++) printf("%d ",neg[i]);
	return 0;
}
```

---

## 作者：wwldx (赞：1)

题意：有一堆向量，你可以将一些取反，使后所有向量之和的长度小于1.5 × 10 ^ 6，保证有解。

思路：最后的总和向量，x ^ 2  +  y ^ 2，肯定是小于2.25 * 10 ^ 12，而每条边的向量模最大是1 * 10 ^ 6，所以极限情况是2条边都是1 * 10 ^ 6，并且成90°，这时模长最大是√2 * 10 ^6,所以任意两条边的向量和长度小于1.414 * 10 ^6 < 1.5 * 10 ^6。使用贪心，每次 保证向量和离原点更近，不断合并边即可。

但是有个隐患，因为每次贪心都是针对当前两条边，而并不是在所有边里找最适合那条，所以有可能出现最后模大于1.5 * 10 ^ 6,

比如，第一条边是（1，0），第二条边是（0，1），那么你合成的时候，最后肯定是（1，1），模长刚好是√2（或者是(-1,-1),(1,-1),(-1,1)，但他们模长都一样，没啥区别），而第三条边是（√2/2，-√2/2），模长刚好是1，且与(1,1)垂直，无论他们俩取反，都是垂直的，这时合成的模长就是√3了，大于了1.5，所以每次我们贪心完后，判断模长是否小于等于1.5，假如大于了，就交换第二位，依次交换，因为卡模长的边一般只要提前处理就不会出事，所以找到那个卡模长的边，优先处理他即可，比如上面的例子，假如第一条边是（1，0），第二条边是（√2/2，-√2/2），那么处理后模长小于1，再与（0，1）合成的时候一定小于1.5

所以假如本次贪心结果不成立，就将第二位与最后一位交换，再不成立，再交换第二位与倒数第二位，循环此次操作，直到成立
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll q=1500000;
#define maxn 100050
typedef pair<int,int> P;
P a[maxn];
int num[maxn],n;
int fact[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1; i<=n; ++i) {
		cin>>a[i].first>>a[i].second;
		num[i]=i;//因为有可能要交换，先预先保存位置 
	}
	ll ans=q*q;
	int qwe=n;
	while(1) {
		ll x=0,y=0;
		for(int i=1; i<=n; ++i) {//判断本次是否需要取反 
			if((x+a[i].first)*(x+a[i].first)+(y+a[i].second)*(y+a[i].second)>(x-a[i].first)*(x-a[i].first)+(y-a[i].second)*(y-a[i].second))
				x-=a[i].first,y-=a[i].second,fact[num[i]]=-1;
			else
				x+=a[i].first,y+=a[i].second,fact[num[i]]=1;
		}
		if(x*x+y*y<=ans)//判断是否成立 
		{//成立了，直接输出 
			for(int i=1;i<=n;i++)
			{
				cout<<fact[i]<<" ";
			}
			cout<<"\n";
			return 0;
		}
		swap(a[2].second,a[qwe].second);
		swap(a[2].first,a[qwe].first);
		swap(num[2],num[qwe--]);//交换 
	}
	return 0;
}
```


---

## 作者：lupengheyyds (赞：0)

# CF995C  Leaving the Bar

> 归纳、贪心。

有一个贪心的思路：

每次随便选取两个向量 $\vec a,\vec b$ 进行操作，取 $\vec a+\vec b$ 与 $\vec a-\vec b$ 中的模长较小值，知道最后只剩下一个向量。

但这样很明显是假的，Hack 如下。这也是第 $26$ 个测试点。

```cpp
3
1000000 0
0 999999
600000 -600000
```

他的原理是一开始放两个无论如何处理后模长度都很大的向量，让你最后只能爆掉。

---

## 乱搞

为了避免使得两个很大的向量放在一起，可以不断`random_shuffle`，直到得到正确的结果。然后就过了。

---

## 正解

根据**归纳的思路**，在**减小规模的同时不能改变其他的限制**，而上述方法却改变的值域的上限。

其实改成一次取三个向量就行了，因为对于任意三个向量，一定会存在两个向量所在直线的夹角小于 $\frac\pi3$ 此时相加或相减的新向量的模长一定小于等于原来的向量的模长中的较大值，于是可以重复执行这种操作，直到只剩下两个向量，那这两个向量合并后的模长一定 $\le\sqrt2\times 10^6$ 于是得到答案。

---

