# Create a Maze

## 题目描述

ZS the Coder 喜欢迷宫。你的任务是创建一个迷宫，让他玩。一个迷宫由 $n \times m$ 个房间组成，房间排列成 $n$ 行（从上到下编号为 $1$ 到 $n$）和 $m$ 列（从左到右编号为 $1$ 到 $m$）。位于第 $i$ 行第 $j$ 列的房间记为 $(i, j)$。玩家从房间 $(1, 1)$ 出发，希望抵达房间 $(n, m)$。

每个房间（除位于迷宫边界的房间外）都有四扇门，分别位于四个墙壁上，两个相邻房间共用一扇门。一些门是锁住的，玩家不能通过被锁住的门。例如，如果连接房间 $(i, j)$ 和 $(i, j+1)$ 的门被锁住，那么玩家就无法从房间 $(i, j)$ 进入房间 $(i, j+1)$。此外，玩家只能向下或向右移动，即从房间 $(i, j)$ 到 $(i+1, j)$ 或从房间 $(i, j)$ 到 $(i, j+1)$，前提是对应的门未被锁住。

![](https://espresso.codeforces.com/da825c734f91a205fb60ed4701c20b1370986107.png)

上图表示了一个部分门被锁住的迷宫。彩色箭头表示所有可能的路径，红色叉表示被锁住的门。

ZS the Coder 定义一个迷宫的**难度**为 $x$，表示从房间 $(1,1)$ 到房间 $(n,m)$ 恰好有 $x$ 种不同的路径。两条路径不同是指行进过程中经过的房间序列不同。

你的任务是设计一个迷宫，使其难度正好为给定的整数 $T$。此外，ZS the Coder 不喜欢太大的迷宫，因此迷宫的大小和锁住门的数量都有上限限制。看起来很简单，是吧？

## 说明/提示

以下图片展示了上述样例输入和输出的情况，彩色箭头表示所有可能路径，红色叉表示被锁住的门。

**第一个样例：**

![](https://espresso.codeforces.com/f6e1f6bc4019999d53cd11eb5f578fc8ae14c3c9.png)

**第二个样例：**

![](https://espresso.codeforces.com/da825c734f91a205fb60ed4701c20b1370986107.png)

## 样例 #1

### 输入

```
3
```

### 输出

```
3 2
0
```

## 样例 #2

### 输入

```
4
```

### 输出

```
4 3
3
1 2 2 2
3 2 3 3
1 3 2 3```

# 题解

## 作者：tybbs (赞：7)

[题目链接](https://codeforces.com/problemset/problem/715/D)

随机化题解。

我们注意到可能的构造方案应该有很多，所以考虑随机化。

有一个简单的贪心：每次删边删使得新的答案 $\ge T$ 但最尽可能小的边（即删边的贡献尽量大），删边的贡献可以用简单的前后缀 dp 维护。这样可以使答案快速向 $T$ 逼近。写出来发现这样的正确率大约有 $\frac{1}{2}$ 左右，问题在于这个贪心在很多情况下会快速把路径堵死，导致调整空间不足。

尝试加入一些随机的成分。对于每条贡献合法且大于当前最大贡献的边，我们不再一定接受，而是以一定的概率接受。概率随便取的 $\frac{1}{2}$，事实上非常优秀，正确性很高，对于每一个 $n,m$ 跑一次都完全足以通过，并且实际只需要删 $\le 50$ 条边。

---

## 作者：AsunderSquall (赞：5)

[**题目链接**](https://www.luogu.com.cn/problem/CF715D)  

**题意**  
构造一个大小为 $n \times m(n,m \le 50)$ 的网格，并且钦定 $k(k \le 300)$ 条边不能走，使从左上角走到右下角的总方案数为 $T(T \le 10^{18})$。其中 $T$ 是输入的，$n,m,k$ 是自己构造的。  

**题解**  
[官方题解](https://codeforces.com/blog/entry/47169)  
想到了进制拆分，但最开始的时候想偏了……  

首先，由于一个点走到右下方的那个格子，在没有限制的情况下，方案数会变为原来的 $2$ 倍，于是我们可以进行二进制拆分，不停地进行 $\times2$ 和 $+1$ 操作。比如说，我们可以用一个类似于管道的一个东西，在这个管道里面的方案数永远是 $1$，然后开一些缺口出去，就相当于是 $+1$ 操作了。
类似于这样一个东西：  
![](https://cdn.luogu.com.cn/upload/image_hosting/2q1yu2kz.png)  
其中红色是必须建的障碍物或者边界，蓝色是根据二进制拆分选择的可以有或者没有的障碍物。  
可以发现，绿色的这一条表示我所说的“通道”，到任意一个绿色的格子的方案数均为 $1$。  
而走到黄色格子的方案数，可以是走到上一个黄色格子的方案数的 $2$ 倍或者 $2$ 倍 $+1$。  

但是这个方法并不足以过这道题，因为 $10^{18}$ 二进制拆分后有 $60$ 位左右，超过了 $50$。  

那怎么办？二进制不行的话，我们发现，$3 \times 3$ 的网格从左上走到右下的方案数为 $6$，那么我们用 $6$ 进制。  

因为 $6^{24} >10^{18}$，所以大概是可以的。接下来就是尝试构造了。  

尝试一下可以构造出类似这样的东西：  
![](https://cdn.luogu.com.cn/upload/image_hosting/daspe911.png)    
图稍微有点错误，就是黄色的 $1$ 上方也应该是红色的。  
注意浅蓝色对当前的贡献为 $1$，而深蓝色为 $3$。  
这样就可以对 $6$ 进制拆分进行构造了。  
实际上我们并不需要每一个障碍物都放，可以将一些不必要的边不连，来压缩障碍物的数量。  

主要是构造“通道”那边的障碍物数量可以大幅压缩。  
最后如果用 [CF 题解中的这张图](https://codeforces.com/predownloaded/39/65/396500eab5871bd133e7458731b59b246875daef.png)的压缩通道的方法，可以将障碍物总数压在 $300$ 以内。  

实际上不超过 $24 \cdot 12+2=290$ 条边。


**代码**   

代码参考了题解，因此和我上述画的图可能不太一样。  
```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#define rd(x) x=read()
#define wt(x) write(x)
#define pos(x) (((x)-1)/SZ+1)
#define y1 _
#define pii pair<int,int> 
#define mp make_pair
using namespace std;
const int N=2e6+5;
const int M=70;
const int SZ=450;
const int mod=998244353;
const int inf=0x3f3f3f3f3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if (ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x<0){putchar('-');x=-x;}if(x>=10)write(x/10);putchar(x%10+'0');}
int ksm(int x,int y=mod-2,int z=mod){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}

set<pair< pii,pii > > S;
void add(int x1,int y1,int x2,int y2) {if (x1<1 || y1<1 || x2<1 || y2<1) return;if (x1+y1>x2+y2) swap(x1,x2),swap(y1,y2);S.insert(mp(mp(x1,y1),mp(x2,y2)));}
int X,Y;
void change(int k)
{
    add(X-2,X+3,X-1,X+3);
    add(X-1,X+1,X,X+1);
    add(X,X+2,X,X+3);
    add(X,X+4,X+1,X+4);
    add(X+1,X+2,X+1,X+3);
    add(X+2,X,X+3,X);
    add(X+2,X+1,X+3,X+1);
    add(X+3,X-2,X+3,X-1);
    add(X+4,X,X+4,X+1);
    if(k%3==0) add(X-1,X+2,X,X+2);
    if(k%3!=2) add(X+2,X-1,X+2,X);
    if(k<3) add(X+1,X-1,X+1,X);
    X+=2;Y+=2;
}
int T;
int a[N],t,sz;
signed main()
{
    rd(T);
    add(1,2,2,2);add(2,1,2,2);
    X=Y=2;
    while (T) a[++t]=T%6,T/=6;
    for (int i=t;i>=1;i--) change(a[i]);
    cout<<X<<" "<<Y<<endl;
    for (pair< pii,pii > p:S) if (p.first.first>X || p.second.second>X || p.first.second>X || p.second.first>X) sz++;
    cout<<S.size()-sz<<endl;
    for (pair< pii,pii > p:S)
    {
        if (p.first.first>X || p.second.second>X || p.first.second>X || p.second.first>X) continue;
        cout<<p.first.first<<" "<<p.first.second<<" "<<p.second.first<<" "<<p.second.second<<"\n";
    }

}
/*
*/
```

**~~彩蛋~~**  
![](https://cdn.luogu.com.cn/upload/image_hosting/cxyub78o.png)

---

## 作者：I_am_Accepted (赞：3)

提供地图长宽 $n=39$，栅栏数 $<3n$ 的解法。

假设读者会了官方给出的 $n=2\log_6V+2$ 的做法。

考虑优化这个做法，我们可以将 $3\times 3$ 的网络换成 $k\times k$ 中选一些格子，要求：
* $(1,1),(k,k)$ 必选。
* 每一行选中的格子必须是连续段。
* 从上到下每一行选中格子连续段的左右端点分别不降。

设这样从 $(1,1)$ 走到 $(k,k)$ 的路径条数为 $p$，则还有一个条件：
* 将所有下方或右方未选择的格子（$(k,k)$ 除外）的权值定义为 $(1,1)$ 走到它的路径条数。所有权值作 $01$ 背包可以得到 $0,1,\dots,p-1$ 所有数。

换句话说，就是 $p$ 进制下这一位 $0,1,\dots,p-1$ 都能取到。

地图大小 $n=(k-1)\log_{p}V+2=\frac{k-1}{\ln p}\ln V+2$。

我们考虑最优化这个 $\lambda=\frac{k-1}{\ln p}$，通过朴素的爆搜得到：



| $k$ | $\max p$ | $\min\lambda$|
|:-:|:-:|:-:|
| $2$ | $2$ | $1.443$ |
| $3$ | $6$ | $1.116$ |
| $4$ | $19$ | $1.019$ |
| $5$ | $62$ | $0.969$ |
| $6$ | $228$ | $0.921$ |
| $7$ | $803$ | $0.897$ |
| $8$ | $2832$ | $0.881$ |
| $9$ | $9994$ | $0.869$ |

举例，下图为 $k=4$ 的最优解：

![](https://cdn.luogu.com.cn/upload/image_hosting/zxb4wkky.png)

对于本题 $V=10^{18}$，可用线性 DP 求解出最优的 $\{k\}=\{9,9,9,9,6\}$，$n=(9-1)\times 4+6-1+2=39$。

爆搜代码

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define rep(Ii,Jj,Kk) for(int Ii=(Jj),Ii##_=(Kk);Ii<=Ii##_;Ii++)
#define per(Ii,Jj,Kk) for(int Ii=(Jj),Ii##_=(Kk);Ii>=Ii##_;Ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned uint;
typedef long double db;
#define fir first
#define sec second
#define siz(Aa) ((int)(Aa).size())
#define all(Aa) (Aa).begin(),(Aa).end()
#define ckmx(Aa,Bb) (Aa=max(Aa,Bb))
#define ckmn(Aa,Bb) (Aa=min(Aa,Bb))

const int N=100;
int n,a[N][N],f[N][N];
int ans=0;
vector<int> v;
template<int cnt=64>
bool get(int x){
	if(x>cnt) return get<min(cnt<<1,1<<29)>(x);
	bitset<cnt> b;
	b.set(0);
	for(int i:v) b|=b<<i;
	b.flip();
	return b._Find_first()>=x;
}
void slv(){
	rep(i,1,n) rep(j,1,n){
		f[i][j]=(i==1 && j==1);
		if(a[i][j]){
			f[i][j]+=f[i-1][j];
			f[i][j]+=f[i][j-1];
		}
	}
	v.clear();
	rep(i,1,n) rep(j,1,n) if(i!=n || j!=n){
		if(a[i][j] && (!a[i+1][j] || !a[i][j+1])){
			v.emplace_back(f[i][j]);
		}
	}
	// cout<<f[n][n]<<":";
	// for(int i:v) cout<<i<<" ";
	// cout<<"\n";
	if(ans<f[n][n] && get(f[n][n])) ckmx(ans,f[n][n]);
}
void dfs(int lay,int x,int y){
	if(lay==n+1){
		if(y==n){
			slv();
		}
		return ;
	}
	rep(l,x,y){
		rep(r,y,n){
			fill(a[lay]+l,a[lay]+r+1,1);
			dfs(lay+1,l,r);
			fill(a[lay]+l,a[lay]+r+1,0);
		}
	}
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	cout<<fixed<<setprecision(3);
	rep(i,2,9){
		n=i;
		dfs(1,1,1);
		cout<<"| $"<<i<<"$ | $"<<ans<<"$ | $"<<(n-1)/log(ans)<<"$ |"<<endl;
		// cout<<ans<<",";
	}
return 0;}
/*
*/
```

DP 代码

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define rep(Ii,Jj,Kk) for(int Ii=(Jj),Ii##_=(Kk);Ii<=Ii##_;Ii++)
#define per(Ii,Jj,Kk) for(int Ii=(Jj),Ii##_=(Kk);Ii>=Ii##_;Ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned uint;
typedef long double db;
#define fir first
#define sec second
#define siz(Aa) ((int)(Aa).size())
#define all(Aa) (Aa).begin(),(Aa).end()
#define ckmx(Aa,Bb) (Aa=max(Aa,Bb))
#define ckmn(Aa,Bb) (Aa=min(Aa,Bb))

const ll inf=1e18;
const int d[]={0,0,2,6,19,62,228,803,2832,9994};
ll f[100];
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	f[1]=inf;
	rep(i,2,99){
		f[i]=inf;
		rep(j,2,min(9,i)){
			ckmn(f[i],f[i-j+1]/d[j]);
		}
		if(f[i]==0){
			cout<<i<<"+1\n";
			return 0;
		}
	}
return 0;}
/*
*/
```

---

## 作者：small_john (赞：1)

## 前言

UPD：修改了一处笔误。

## 思路

先考虑一种较劣的方式：二进制拆分，将迷宫构造成下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7gd8xltb.png)

图中黑色的边是必须堵住的，而红色的边是可能堵住的。

这种构造方式可以看做一种有很多个 $2\times 2$ 的块组成的，我们对于一个其中一个块的相邻部分进行分析：

![](https://cdn.luogu.com.cn/upload/image_hosting/42sw4dfl.png)

可以发现，当红色的边没有被堵住时，$y=1$，否则 $y=0$。这样我们就可以对方案数不断进行乘二或者乘二加一的操作（最多操作 $48$ 次），就实现了二进制拆分。然而这种方法不足以通过。

考虑把块扩大到 $3\times 3$，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ovm1ar34.png)

当打开一号边时，$y$ 会加三，当打开二号边或三号边时，$y$ 会加一。通过组合可以得到满足 $0\le y<6$ 的所有整数 $y$，相当于 $6$ 进制拆分。这样最多操作 $24$ 次，足够了。

最终时间复杂度为 $O(\log_6t)$，有比较大的常数。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second 
#define y1 ____
#define y2 _____
using namespace std;
int t,n;
vector<int> vec;
vector<pair<pair<int,int>,pair<int,int>>> s;
#define add(x1,y1,x2,y2) (s.push_back({{x1,y1},{x2,y2}}))
inline void work(int val)
{
	add(n-1,n+1,n,n+1);
	add(n-2,n+3,n-1,n+3);
	add(n+1,n+2,n+1,n+3);
	add(n,n+4,n+1,n+4);
	add(n+2,n,n+3,n);
	add(n+2,n+1,n+3,n+1);
	add(n,n+2,n,n+3);
	add(n+3,n-2,n+3,n-1);
	add(n+4,n,n+4,n+1);
	if(val<3) add(n+1,n-1,n+1,n);
	else val-=3;
	if(val==0) add(n-1,n+2,n,n+2);
	if(val<=1) add(n+2,n-1,n+2,n);
	n+=2; 
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t) vec.push_back(t%6),t/=6;
	n = 2;
	add(1,2,2,2),add(2,1,2,2);
	for(int i = vec.size()-1;~i;i--) work(vec[i]);
	cout<<n<<' '<<n<<'\n';
	int k = s.size();
	for(auto i:s) if(i.x.x<1||i.x.x>n||i.x.y<1||i.x.y>n||i.y.x<1||i.y.x>n||i.y.y<1||i.y.y>n) k--;
	cout<<k<<'\n';
	for(auto i:s)
	{
		if(i.x.x<1||i.x.x>n||i.x.y<1||i.x.y>n||i.y.x<1||i.y.x>n||i.y.y<1||i.y.y>n) continue;
		cout<<i.x.x<<' '<<i.x.y<<' '<<i.y.x<<' '<<i.y.y<<'\n';
	}
	return 0;
}
```

---

## 作者：RainySoul (赞：1)

绝妙构造题。

### 思路

一眼看上去没什么思路，先画个简单的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/w0nwk7mm.png)

发现一个 $2 \times 2$ 的矩形从，左上角走到右下角的方案数会乘一个 $2$。

然后你只需要把这些个 $2 \times 2$ 的矩形首尾相接就能轻松构造出 $2^{k}$ 了。

![](https://cdn.luogu.com.cn/upload/image_hosting/0pc78ojl.png)

这启发我们可能可以对 $T$ 进行二进制拆分构造。

再把上面那个 $2 \times 2$ 的矩形拎出来看。

![](https://cdn.luogu.com.cn/upload/image_hosting/4pm24wwz.png)

现在我们还只会构造 $y=2 \times x$，要实现二进制构造你还需要能构造出 $y=2 \times x+1$。

如果你可以在这个矩形左下角或者是右上角开个口子，并且从这里加一个 $1$ 进去不就实现了 $y=2 \times x+1$ 了吗？

![](https://cdn.luogu.com.cn/upload/image_hosting/rb1t6lem.png)

所以你想要随时随地可以加入一个 $1$，这可以通过保护一条一直为 $1$ 的路径办到，形如这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/4y0ieibd.png)

其中红色和白色的区域就是我们围起来的区域。

---

解决了吗？好像并没有。虽然说我们可以对着 $T$ 的二进制进行构造了，但是因为有 $n \le 50$ 且 $m \le 50$ 的限制，你最多只能构造出 $2^{50}$ 的样子，而 $T \le 10^{18}$，你至少需要构造出 $2^{60}$。怎么办呢？

把那个 $2 \times 2$ 的矩形换成 $3 \times 3$ 的矩形试试。

![](https://cdn.luogu.com.cn/upload/image_hosting/985oz0gs.png)

每次从左上角走到右下角，方案数会乘 $6$。相当于把上面的二进制构造变成了六进制构造，其实变化不大。而 $6^{24} > 10^{18}$，所以 $3 \times 3$ 的已经够用了。

![](https://cdn.luogu.com.cn/upload/image_hosting/shuez2vp.png)

按照上面的思路你需要完成 $y=6 \times x$，$y=6 \times x+1$，$y=6 \times x+2$，$y=6 \times x+3$，$y=6 \times x+4$，$y=6 \times x+5$ 这六种情况的构造才能完成六进制构造。

还是考虑开口。

这两个位置加入一个 $1$ 对 $y$ 的贡献都是 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/l22w5a7z.png)

这两个位置加入一个 $1$ 对 $y$ 的贡献都是 $3$：

![](https://cdn.luogu.com.cn/upload/image_hosting/tu4rzixl.png)

使用一个 $3$ 和两个 $1$ 组合一下就可以拼成 $0$ 到 $5$ 的任意整数了。

所以你在一个矩形左下方和右上方都要保护一条 $1$ 的路径。

但是你发现直接把需要的全都围起来似乎障碍物 $k \le 300$ 又有点不够用了，不过细想一下两条 $1$ 的路径并不需要全都围起来。

![](https://cdn.luogu.com.cn/upload/image_hosting/10tecnfj.png)

具体来说，从一个 $y$ 跳到 $x$ 时，只有上图中的黑边是必须加的，这样足以保护出两条 $1$ 的路径了（读者可以手玩一下看看为啥）。而蓝边是根据 $y \bmod 6$ 的结果选择加的。那么满打满算最多只要 $(8+4) \times 24+2=290$ 个障碍就够了。实际上有触碰到边界的是不需要放的，最终达不到这个数，可以通过此题。

上面计算障碍最末的那个加 $2$ 是因为最后一次跳完后你需要给整个封顶。就是说最后一步的 $x$ 一定是为 $0$ 或者 $1$ 的，为 $0$ 的时候你需要把 $0$ 这个格子左边和上边都封死，为 $1$ 的时候你需要把这个格子左边或者上边封死。

对 $T$ 进行六进制拆分，从 $(n,n)$ 开始往左上方跳，一个一个地构造 $3 \times 3$ 的矩形。

然后你就解决了这道好玩的构造题。

AC code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct zyx{int a,b,c,d;};
queue<zyx> q;
int t,cnt,n;
void add(int a,int b,int c,int d){
    if(a<=0||a>n||b<=0||b>n||c<=0||c>n||d<=0||d>n)return;
    if(a>c||b>d){
        swap(a,c);
        swap(b,d);
    }
    q.push((zyx){a,b,c,d});
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>t;
    int T=t;
    while(T>1){T/=6;cnt++;}
    n=(cnt+1)*2;
    cout<<n<<" "<<n<<'\n';
    T=t;
    int x=n,y=n;
    while(T>1){
        int now=T%6;
        add(x-1,y,x-1,y+1);
        add(x-2,y,x-2,y+1);
        add(x,y-1,x+1,y-1);
        add(x,y-2,x+1,y-2);
        add(x-3,y,x-4,y);
        add(x-5,y-1,x-6,y-1);
        add(x,y-3,x,y-4);
        add(x-1,y-5,x-1,y-6);
        if(now==0){
            add(x-2,y-1,x-3,y-1);
            add(x-2,y,x-3,y);
            add(x,y-2,x,y-3);
            add(x-1,y-2,x-1,y-3);
        }
        else if(now==1){
            add(x-2,y-1,x-3,y-1);
            add(x,y-2,x,y-3);
            add(x-1,y-2,x-1,y-3);
        }
        else if(now==2){
            add(x-2,y-1,x-3,y-1);
            add(x-1,y-2,x-1,y-3);
        }
        else if(now==3){
            add(x-2,y,x-3,y);
            add(x,y-2,x,y-3);
            add(x-1,y-2,x-1,y-3);
        }
        else if(now==4){
            add(x,y-2,x,y-3);
            add(x-1,y-2,x-1,y-3);
        }
        else if(now==5){
            add(x-1,y-2,x-1,y-3);
        }
        x-=2,y-=2;
        T/=6;
    }
    if(T!=1)add(x,y,x-1,y);
    add(x,y,x,y-1);
    cout<<q.size()<<'\n';
    while(!q.empty()){
        zyx tt=q.front();
        cout<<tt.a<<" "<<tt.b<<" "<<tt.c<<" "<<tt.d<<'\n';
        q.pop();
    }
    return 0;
}
```

话说题目名怎么是 `Create a Maze` ~~创造一个妹子~~啊（喜）。

另：在使用六进制构造的过程中，应该还有更少障碍物的方案，读者可以自己尝试。

---

## 作者：UKE_Automation (赞：0)

### CF715D Create a Maze

[$\text{Link}$](https://codeforces.com/problemset/problem/715/D)

首先我们需要考虑一个基本结构：

```
1 1
1 2
```

这也就是说，我们可以通过这个结构将当前的方案数 $\times 2$。这启发我们进行二进制分解。

不过要利用二进制进行构造，我们除了要完成 $\times 2$ 这个操作以外，还需要完成 $\times 2+1$ 这个操作。实际上这个并不难实现，我们给上面的基本结构中开一个口，把外面的一个 $1$ 引进来即可，即：

```
x x x
x 1 1
1 2 3
```

这样的话我们除了维护中间的主体部分以外，还需要额外维护外面的一圈 $1$ 来辅助分解，那么我们最终的构造应该形如下图：

```
1 - - x x 
1 - - - x
1 1 - - -
x 1 1 - -
```

`-` 的地方就是我们构造的主体部分，`1` 就是辅助部分。这样的话我们最多能够造出的数字大概是 $2^{50}$，很遗憾的是这个值没有达到 $10^{18}$，所以我们需要改进做法。

实际上把基本结构当成 $2\times 2$ 是有点浪费的，我们将它扩大到 $3\times 3$：

```
1 1 1
1 2 3
1 3 6
```

这样的话我们可以做到单次 $\times 6$，所以我们可以进行六进制拆分。此时我们需要实现在 $\times6$ 的基础上加 $1\sim 5$，依然考虑从基本结构中开口解决。我们有两种本质不同的开口方式，分别可以使答案 $+3$ 和 $+1$，拼一起即可完成这个要求。

不过此时我们不能只维护一边的 $1$ 了，我们要在左边和上边都维护一圈 $1$ 来辅助，也就是说我们的构造应该形如下：

```
1 1 1 1 1 x x x
1 - - - 1 x x x
1 - - - 1 1 1 x
1 - - - - - 1 x
1 1 1 - - - 1 1
x x 1 - - - - -
x x 1 1 1 - - -
x x x x 1 - - -
```

此时我们可以构造出的最大数字大概为 $6^{24}>10^{18}$，已经可以满足要求了。然后我们现在需要满足障碍物的限制。对于主体部分和辅助部分之间的墙，每个部分最多需要 $8$ 个障碍物；对于辅助部分和无用部分之间的墙，看似我们也需要 $8$ 个障碍物，但是实际上在每个转折处，我们只需要保留水平方向或竖直方向上的两个障碍物即可，所以这一部分只需要 $4$ 个障碍物。加上开头我们封住起点的两个障碍物，总数是 $(8+4)\times 24+2=290$ 个障碍物，可以满足要求。

```cpp
#include <bits/stdc++.h>
#define il inline
#define int long long

using namespace std;

const int Maxn = 2e5 + 5;
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int w, n;
int num[Maxn], cnt;
struct node {
	int x1, y1, x2, y2;
};
vector <node> res;

il void add(int x1, int y1, int x2, int y2) {
	if(x1 < 1 || x1 > n || y1 < 1 || y1 > n || x2 < 1 || x2 > n || y2 < 1 || y2 > n) return ;
	res.push_back({x1, y1, x2, y2});
}

int c[] = {3, 3, 1, 1};
node d[] = {{-1, 1, 0, 1}, {1, -1, 1, 0}, {-1, 2, 0, 2}, {2, -1, 2, 0}};

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
signed main() {
	cin >> w;
	while(w) num[++cnt] = w % 6, w /= 6;
	n = (cnt + 1) << 1;
	cout << n << " " << n << '\n';
	for(int i = 1; i <= cnt; i++) {
		int p = (i << 1);
		add(p, p + 2, p, p + 3);
		add(p + 1, p + 2, p + 1, p + 3);
		add(p + 2, p, p + 3, p);
		add(p + 2, p + 1, p + 3, p + 1);
		add(p - 3, p + 1, p - 3, p + 2);
		add(p - 2, p + 1, p - 2, p + 2);
		add(p + 1, p - 3, p + 2, p - 3);
		add(p + 1, p - 2, p + 2, p - 2);
		int t = num[cnt - i + 1];
		for(int i = 0; i < 4; i++) {
			if(t >= c[i]) t -= c[i];
			else add(p + d[i].x1, p + d[i].y1, p + d[i].x2, p + d[i].y2);
		}
	}
	add(1, 2, 2, 2); add(2, 1, 2, 2);
	cout << res.size() << '\n';
	for(auto p : res) cout << p.x1 << " " << p.y1 << " " << p.x2 << " " << p.y2 << '\n';
    Usd();
	return 0;
}

```

---

