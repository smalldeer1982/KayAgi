# Half Queen Cover

## 题目描述

You are given a board with $ n $ rows and $ n $ columns, numbered from $ 1 $ to $ n $ . The intersection of the $ a $ -th row and $ b $ -th column is denoted by $ (a, b) $ .

A half-queen attacks cells in the same row, same column, and on one diagonal. More formally, a half-queen on $ (a, b) $ attacks the cell $ (c, d) $ if $ a=c $ or $ b=d $ or $ a-b=c-d $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1667C/7bd42db06039264b9144129e45c89b4a8730a512.png)The blue cells are under attack.  What is the minimum number of half-queens that can be placed on that board so as to ensure that each square is attacked by at least one half-queen?Construct an optimal solution.

## 说明/提示

Example $ 1 $ : one half-queen is enough. Note: a half-queen on $ (1, 1) $ attacks $ (1, 1) $ .

Example $ 2 $ : one half-queen is enough too. $ (1, 2) $ or $ (2, 1) $ would be wrong solutions, because a half-queen on $ (1, 2) $ does not attack the cell $ (2, 1) $ and vice versa. $ (2, 2) $ is also a valid solution.

Example $ 3 $ : it is impossible to cover the board with one half queen. There are multiple solutions for $ 2 $ half-queens; you can print any of them.

## 样例 #1

### 输入

```
1```

### 输出

```
1
1 1```

## 样例 #2

### 输入

```
2```

### 输出

```
1
1 1```

## 样例 #3

### 输入

```
3```

### 输出

```
2
1 1
1 2```

# 题解

## 作者：StarLbright40 (赞：17)

- 鸣谢：@SpadeA261

- ~~挑战最短代码~~

- （由于笔者太菜了不会画图，读者珂以利用方格纸辅助理解）

------------
[博客园链接](https://www.cnblogs.com/XG0000/p/CF1667C.html)

本题解主要讲解一种构造方式。

本文作如下定义：

- “$n$ 阶棋盘”即为题意中 $n$ 行 $n$ 列的棋盘；

- 对角线（与主对角线平行）的编号为其上格子的行号减列号。

------------
设答案为 $k$，考虑在 $n$ 阶棋盘左上角的 $k$ 阶棋盘中不重行不重列地放置 $k$ 个棋子，于是 $n$ 阶棋盘中的前 $k$ 行均能被同行棋子攻击，前 $k$ 列均能被同列棋子攻击。

于是还剩下右下角的 $n-k$ 阶棋盘，它们只能被同对角线的棋子攻击。

$n-k$ 阶棋盘可被划分为 $2(n-k)-1$ 条对角线，为使它们被覆盖，需要有 $k\ge2(n-k)-1$，

解得 $k=\left\lceil\dfrac{2n-1}{3}\right\rceil=\left\lfloor\dfrac{2n+1}{3}\right\rfloor$，

同时 $n=\left\lfloor\dfrac{3k+1}{2}\right\rfloor$。

接下来考虑放置方案。

由 $k\ge2(n-k)-1$ 变形得 $\left\lfloor\dfrac{k+1}{2}\right\rfloor\ge n-k$，注意到 $n-k$ 即为 $n-k$ 阶棋盘中编号非负的对角线数量。

考虑用 $k$ 阶棋盘中的前 $\left\lfloor\dfrac{k+1}{2}\right\rfloor$ 列上的棋子攻击这些对角线。

首先在 $(1,1)$ 放置一枚棋子~~别问为什么问就是看上去很优~~，则它能攻击 $0$ 号对角线；

接着采用类似“马走日”的方法，下一枚棋子放置在上一枚棋子位置行号 $+2$，列号 $+1$ 的位置，于是它能攻击的对角线编号 $+1$。

也就是像 $(3,2),(5,3)…$ 这样，依次攻击 $n-k$ 阶棋盘中的非负对角线，直到第 $\left\lfloor\dfrac{k+1}{2}\right\rfloor$ 列，此时棋子刚好没有超出 $k$ 阶棋盘，同时编号非负的对角线全部被攻击到。

剩下的任务就是用 $k$ 阶棋盘余下的列上的棋子攻击 $n-k$ 阶棋盘余下的对角线。

在 $k$ 阶棋盘中，考虑再下一列上的棋子，由于奇数行已全被占据，棋子应被放在偶数行，我们将它放在第二行，也就是放在 $(2,\left\lfloor\dfrac{k+1}{2}\right\rfloor+1)$。

它能攻击的对角线，编号为 $2-(\left\lfloor\dfrac{k+1}{2}\right\rfloor+1)=-\left\lfloor\dfrac{k-1}{2}\right\rfloor$。

$n-k$ 阶棋盘中编号最小的对角线，编号为 $1-(n-k)=1-\left\lfloor\dfrac{3k+1}{2}\right\rfloor+k=-\left\lfloor\dfrac{k-1}{2}\right\rfloor$。

于是这枚棋子刚好攻击到编号最小的对角线。

我们依旧采用上面提到的“马走日”的方法放置棋子，于是第 $k$ 列的棋子位置是 $(2\left\lfloor\dfrac{k}{2}\right\rfloor,k)$，显然它攻击的对角线编号不是 $0$ 就是 $-1$，此时编号为负的对角线也全部被攻击到。

至此我们完成了全部分析。

在代码实现中，我们可以枚举列号，按上面的方法模拟行号的变化。

代码很短，在 $0.2kb$ 以内~~传说中思维很巧妙代码很好写的题~~。
```cpp
#include<cstdio>
int n,k;
int main(){
	scanf("%d",&n);
	k=(n*2+1)/3;
	printf("%d",k);
	for(int i=1,x=1;i<=k;++i,x+=2){
		if(x>k) x=2;
		printf("\n%d %d",x,i);
	}
	return 0;
}
```

---

## 作者：enucai (赞：6)

upd: 更新了图片。

## Analysis

棋子数量的**理论下界**：

假设放了 $k$ 颗棋子，仅看横竖，最多覆盖 $k$ 行，$k$ 列。将剩下的格子平移可以拼成 $(n-k)\times (n-k)$ 的正方形，该正方形的 $2\times (n-k)-1$ 条对角线都要由棋子的对角线覆盖。

因此可以列出不等式 $k\ge 2\times(n-k)-1$，化简得 $k\ge \frac{2n-1}{3}$。因此棋子数量 $k$ 的理论下界是 $\left\lceil\frac{2n-1}{3}\right\rceil$。

理论下界的**构造方法**：

假设 $n\equiv 2\pmod 3$，那么 $k=\frac{2n-1}{3}$。去掉这些行列之后还剩一个 $\frac{n+1}{3}\times \frac{n+1}{3}$ 的正方形。我们将这个正方形放于右下角（红色），再在左上角拷贝一份（红色），取出中间的交集（绿色）。

![](https://cdn.luogu.com.cn/upload/image_hosting/zwro3iew.png)

如上图，在左边红色的正方形对角线上摆棋子，中间绿色正方形对角线上摆棋子，即可满足题意。证明较为容易，读者可以自行证明（~~这东西要证吗？~~）。

对于 $n\not\equiv 2\pmod 3$，在右下角加棋子即可。

## Code

[Codeforces Status](https://codeforces.com/contest/1667/submission/154184893)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define int long long
int n,m;
signed main(){
	cin>>n;
	if(n==1){cout<<"1\n1 1\n";return 0;}
	cout<<(2*n-2)/3+1<<endl;
	m=n; while(m%3!=2) m--;
	int k=(2*m-1)/3,p=2*k-m,q=k-p;
	For(i,1,q) cout<<i<<" "<<q-i+1<<endl;
	For(i,q+1,k) cout<<i<<" "<<q+k-i+1<<endl;
	For(i,m+1,n) cout<<i<<" "<<i<<endl;
}
```

---

## 作者：I_am_Accepted (赞：3)

### Preface

这种题对于我来说真的难，猜结论 + 证明 + 构造。

### Analysis

以下 H 表示半皇后的行攻击，L 表示半皇后的列攻击。

设我们在 $n\times n$ 的棋盘上放置了 $k$ 个半皇后，则若只考虑半皇后的 H/L，最多 $k$ 行、$k$ 列被攻击。

找到 从上到下第一个没有被 H 的行 和 从左往右第一个没有被 L 的列。

这一行、一列上总共至少有 $2n-2k-1$ 个没有被 h 且没有被 L 的点，而且这些点所在的对角线各不相同。

所以，我们得到 $2n-2k-1\le k$，即 $k\ge \frac{2n-1}{3}$，我们证明 $k=\lceil\frac{2n-1}{3}\rceil$ 可以取到。

对于 $n \bmod 3=2$，设 $t=\frac{n-2}{3}$，我们在左上角 $(t+1)\times (t+1)$ 的子矩形的反对角线上放半皇后，同理在右下角 $t\times t$ 的子矩形的反对角线上放半皇后。

![](https://cdn.luogu.com.cn/upload/image_hosting/1wjp4a7p.png)

大概就长这样↑，红色为半皇后，绿色为攻击范围。

对于 $n \bmod 3\ne 2$，我们在 $(n,n)$ 放一个半皇后，这样问题变成了 $(n-1)\times (n-1)$ 的棋盘问题了。

### Code

[Link](https://codeforces.com/contest/1667/submission/154284785)

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N -1

int n;
vector<pair<int,int> > ans;
signed main(){IOS;
	cin>>n;
	if(n==1){
		cout<<"1\n1 1"<<endl;
		return 0;
	} 
	while(n%3!=2){
		ans.pb(mkp(n,n));
		n--;
	}
	int tar=(n+1)/3;
	For(i,1,tar) ans.pb(mkp(i,tar+1-i));
	For(i,1,tar-1) ans.pb(mkp(n+1-i,n+1-(tar-i)));
	cout<<ans.size()<<endl;
	for(auto i:ans) cout<<i.fir<<" "<<i.sec<<endl;
return 0;}
```

---

## 作者：lzytag (赞：3)

# 简单构造题
[题目传送门](https://www.luogu.com.cn/problem/CF1667C)
## 前言

本题 $CF$ 评分 $2400$ 我觉得有点虚高，~~毕竟是本菜鸡可以自己推出来的~~ ，但本题的结论，无论是做法还是证法都很有趣，所以简单写一篇题解记录一下。

## 棋子个数

首先，这题一个棋子的**横向攻击**和**纵向攻击**都较好处理。

但对于**斜向攻击**的处理却相当麻烦。

于是，我们不妨先将**横向攻击**和**纵向攻击**先处理完毕，再加入**斜向攻击**。

对于问题 $n \times n$，我们假设需要 $x$ 枚棋子。

很明显，只有当每枚棋子都不在同一行或同一列上时，才可能最优。

于是**横向和纵向**攻击完后，还剩下 $(n-x) \times (n-x)$ 个空格，且他是原图的一个 $(n-x) \times (n-x)$ 的子矩阵。

对于这个子矩阵，取第一行和第一列，共有 $(2 \times (n-x) - 1)$ 枚棋子不在同一斜线上，既得不等式。

$$
2 \times (n-x) - 1\le x
$$
解得
$$
x\ge \frac{(2n-1)}{3}
$$
于是
$$
x = \lceil\frac{(2n-1)}{3}\rceil
$$
即可

剩下的格子只要都与前面这$(2 \times (n-x) - 1)$ 枚棋子在同一斜线上即可。

## 构造方法

了解原理后，构造方法应该很多，这里提供我的一种。

首先，$n=1$ 时特判。

接下来，当 $n \equiv 2\mod 3$ 时，设 $m = (n+1)/3$ 按如下方法放：

$$
(1,m),(2,m-1)……(m,1)
$$

$$
(m+1,2 \times m-1),(m+2,2 \times m-2)……(2 \times m - 1 ,m+1)
$$

当 $n \equiv 2 \mod 3$ 不成立时，先按前面的做法做完，再补棋子补到 $n$。

附上简短代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
int read()
{
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)) f|=ch=='-',ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
ll lread()
{
	ll x=0,f=0;char ch=getchar();
	while(!isdigit(ch)) f|=ch=='-',ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
//file head over
int n; 
int main()
{
	n = read();
	printf("%d\n",(2*n+1)/3);
	if(n == 1)
	{
		puts("1 1");
		return 0;
	}
	for(int i = 1;i <= (n+1)/3;i++) printf("%d %d\n",i,(n+1)/3-i+1);
	for(int i = 1;i < (n+1)/3;i++) printf("%d %d\n",i+(n+1)/3,(n+1)/3*2-i);
	for(int i = (n+1)%3;i > 0;i--) printf("%d %d\n",n-i+1,n-i+1);
   	//纯懒狗写法
	return 0;
}

```


---

## 作者：Purslane (赞：2)

# Solution

非常简单的构造题，但是做了很久，怎么会事呢。

假设我们放了 $k$ 个皇后，则会有 $(n-k) \times (n-k)$ 个格子（他们和这样的正方形同构）没有被行或列覆盖，必须被斜对角线覆盖，也就是至少占据了 $2n-2k-1$ 条对角线。

所以 $k \ge 2n-2k-1$，得 $k \ge \dfrac{2n-1}{3}$，取 $k=\lceil \dfrac{2n-1}{3} \rceil$ 即可。

-------

考虑构造，不妨把 $(n-k) \times (n-k)$ 塞到左下角。

考虑先把对角线干掉。

![](https://s21.ax1x.com/2024/11/14/pAgDGU1.png)

如图，在左上角放长度分别为 $n-k$ 和 $n-k-1$ 的对角线。

这样可能还会有剩余（因为你只放了 $2n-2k-1 \le k$ 个皇后），在蓝色矩形的左上方加进去即可。

![](https://s21.ax1x.com/2024/11/14/pAgDavD.png)

代码好短。

```cpp
int n; 
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	if(n==1) return cout<<1<<'\n'<<1<<' '<<1,0;
	int a=(n+1)/3;
	cout<<n-a<<'\n';
	ffor(i,1,a) cout<<i<<' '<<a+1-i<<'\n';
	ffor(i,a+1,a+a-1) cout<<i<<' '<<a*3-i<<'\n';
	ffor(i,a+a,n-a) cout<<i<<' '<<i<<'\n';
	return 0;
}
```

---

## 作者：lfxxx (赞：2)

假设我们需要 $n-k$ 个棋子，那么只看横竖就只会剩 $k$ 行与 $k$ 列，这些列当然是构成一个 $k \times k$ 的矩形最好。

接下来我们需要在 $(n-k) \times (n-k)$ 的矩形中摆出一些对角线将 $k \times k$ 矩形中的点全部覆盖掉，需要的对角线数有 $2 \times k - 1$ 条，而我们希望 $n-k$ 个棋子在行列互不相同的前提下所处对角线也互不相同，故 $n - k \geq 2 \times k - 1$ 也就是 $n +1 \geq 3 \times k$ 所以最大的 $k$ 为 $\lfloor \frac{n+1}{3} \rfloor$ ，最小次数就是 $n-k$。

考虑构造，考虑从 $(k+1,k+1)$ 出发每次纵坐标增加 $1$ 横坐标增加 $2$ 让两个坐标之差相互错开，横坐标超过 $n$ 时回到 $k+2$，不过在 $n=3$ 会造成出现两个点在同一个对角线上的情况，不过在 $n=3$ 的特例下这种方案仍然合法。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    int k=(n+1)/3;
    cout<<n-k<<'\n';
    int nx=k+1;
    int ny=k+1;
    for(int i=1;i<=n-k;i++){
        cout<<nx<<' '<<ny<<'\n';
        nx++,ny+=2;
        if(ny>n) ny=k+2;
    }
    return 0;
}
```

---

## 作者：3a51_ (赞：2)

### 前言

洛谷翻译有没有树脂，国际象棋里的皇后是两条斜线都能覆盖的，如果像我一样没有特意关注覆盖条件就很容易误解题面。。。

---

### 分析

一眼数据范围发现 $n\le 10^5$，$O(n^2)$ 绝对过不了，所以 dp 啥的都不用想了，考虑找规律。

考虑对于一个 $n\times n$ 的棋盘，设其最小放置棋子数为 $k$，则至少有 $n-k$ 行没被一整行覆盖，$n-k$ 列没被一整列覆盖，这就导致了存在一个 $(n-k)\times (n-k)$ 的正方形，不会被整行、整列的覆盖。所以，这些格子只能被对角线覆盖。

$(n-k)\times (n-k)$ 的棋盘有 $2\times(n-k)-1$ 条对角线，又由于一个棋子只能覆盖一条对角线，所以要想完整用对角线覆盖 $(n-k)\times (n-k)$ 的棋盘，需要满足 $k\ge 2\times(n-k)-1$。移个项，化简一下可得 $k\ge \frac{2n-1}{3}$。因为 $k$ 是整数，所以不妨写成 $k\ge \lceil\frac{2n-1}{3}\rceil$。

接下来考虑怎么构造。不难考虑到，不是所有的 $(n-k)\times (n-k)$ 的棋盘都能够被 $2\times(n-k)-1$ 条对角线覆盖，比如下面的棋盘：

![](https://cdn.luogu.com.cn/upload/image_hosting/wd12xzp2.png)

黑色的是 $(n-k)\times (n-k)$ 的棋盘，显然不能用 $2\times(n-k)-1$ 条对角线覆盖。

考虑什么时候能被 $2\times(n-k)-1$ 条对角线覆盖。不难发现你选择留下来让对角线覆盖的相邻两行和相邻两列都是等距的时候才能被 $2\times(n-k)-1$ 条对角线覆盖。（以下将选择留下来让对角线覆盖的格简称黑格）

不妨设所有黑格都是相邻的，并且放在右下角。为什么这么设呢？因为这样方便思考，便于总结规律。你最后的程序不可能是打表对吧。

为了让所有格都覆盖，你需要让所有放半皇后的格子没有重行、重列、重对角线。不妨设所有覆盖了黑格的格子都在左上角边长 $2\times (n-k) -1$ 的正方形里。(这里不理解可以看下面那张图）

![](https://cdn.luogu.com.cn/upload/image_hosting/9syu8sgr.png)

右下角是之前所说的黑格，紫色、橙色、蓝色、深红色是四个半皇后，黑色框是所有覆盖了黑格的格子所在的正方形（以下简称覆盖正方形）。这是 $n=6$ 的最优解之一。

不难看出，除去覆盖正方形和黑格外的部分只需要沿着主对角线（$x=y$）放置即可。

接下来考虑覆盖正方形内部怎么放置。这里需要满足 $3$ 个要求：

1. 对于覆盖正方形内的每一行，应有且仅有一个半皇后；
2. 对于覆盖正方形内的每一列，应有且仅有一个半皇后；
3. 对于覆盖正方形内的每一斜线，如果其能覆盖到黑格，应有且仅有一个半皇后；如果不能，应没有半皇后。

找一找规律即可发现，对于覆盖正方形内的每一行放置的位置，是上一行放置的位置后移两格（如果出了边界就回到第一格），然后把代码写出来就长这样：

```cpp
#include<bits/stdc++.h>
#define int long long
#define I 1e18
using namespace std;
const int N=0;
int n,k,rd,lu,nx=1,ny=1;
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	if(n<=2) cout<<1<<endl<<"1 1"<<endl;//特判corner case
	else{
		k=ceil((double)(2*n-1)/(double)3);//计算半皇后个数
		cout<<k<<endl;
		rd=n-k,lu=2*rd-1;//rd 是右下角黑格的边长，lu是左上角覆盖正方形的边长
		if(lu) cout<<"1 1"<<endl;//特判第一行
		for(int i=2;i<=lu;i++){//枚举每一行
			if(ny>lu-2) ny=(ny+2)%lu;//出界
			else ny+=2;
			cout<<++nx<<" "<<ny<<endl;
		}
		for(int i=lu+1;i<=k;i++) cout<<++nx<<" "<<nx<<endl;//除去覆盖正方形和黑格之外的部分，直接沿主对角线覆盖
	}
	return 0;
}


```

交上去发现 AC 了，但没有证明怎么行呢？

---

### 证明

再把那三个条件粘一遍：

1. 对于覆盖正方形内的每一行，应有且仅有一个半皇后；
2. 对于覆盖正方形内的每一列，应有且仅有一个半皇后；
3. 对于覆盖正方形内的每一斜线，如果其能覆盖到黑格，应有且仅有一个半皇后；如果不能，应没有半皇后。

首先考虑条件 $1,2$。条件 $1$ 显然满足，因为是一行一行放的。条件 $2$ 也不难证，因为走到头的机会只有一次，第一遍会把所有奇数列覆盖掉，因为左上角的边长是 $2\times(n-k) -1$，一定是奇数，所以第二次就会把所有偶数覆盖掉。

关键在条件 $3$。我们称主对角线编号为 $0$，每往右上走一个，编号 $+1$，每往左下走一个，编号 $-1$。第一遍肯定是把所有编号非负的对角线覆盖了，这不难看出。第二遍开始的时候会跳到第二列，也就是编号最小的那个对角线，然后每次会覆盖编号比上次大 $1$ 的对角线，最后正好覆盖到 $-1$。证毕。（很烂的证明）

---

### 总结

这可能是我写过的最认真的一篇题解了吧，主要是因为这题思维有趣代码好写。

---

## 作者：wangyibo201026 (赞：1)

## solution

做过的同 Rating 题里几乎最难，可能是不怎么会构造。

考虑弱化问题，如果一个半皇后只能攻击行和列，考虑怎么做。

显然，我们放满一条主对角线即可满足条件。

但是如果加上半皇后的主对角线，我们就不可能放一条主对角线上了，因为这样会浪费掉对角线的特殊性质。

不妨从简单的角度去想，我们钦定用行和列覆盖的区域形状，这样就可以确定用对角线覆盖的区域形状。在这里不妨钦定用对角线覆盖的区域形状为一个矩形，为了方便描述于构造，我们又钦定是 $n \times n$ 的矩形中的左上角大小为 $m \times m$ 的矩形。

那么也就是说除了这个 $m \times m$ 的矩形内的 $m$ 行与 $m$ 列，其他的每一行每一列都需要用半皇后的行与列进行覆盖，所以在此我们推断出至少要用 $n - m$ 个皇后。

那我们自然是希望这 $n - m$ 个半皇后不仅能够行列覆盖 $n - m$ 个行和列，其对角线覆盖还能覆盖左上角的 $m \times m$ 的矩形。

不难发现满足这一条件的必要性是 $2 \times m - 1 \le n - m$，因为我的 $m \times m$ 的矩形本来就有 $2 \times m - 1$ 条对角线，至少也需要 $2 \times m - 1$ 个半皇后才能覆盖。我们通过解不等式可得 $m \le \frac{n + 1}{3}$，那么最优情况下 $m = \lfloor \frac{n + 1}{3} \rfloor$，因为我们要放 $n - m$ 个半皇后，$m$ 当然越大越好。

接下来我们通过构造的方式尝试证明其充分性，我们令 $x = m + 1, y = m + 1$，然后每次 $x + 1, y + 2$，如果 $y$ 越位了就重新赋 $y = m + 2$，不难发现这种情况完美的行列覆盖 $n - m$ 个行列，又同时没有一个半皇后在另一个半皇后的主对角线上，那么此时就充分可以覆盖 $m \times m$ 的矩形内的 $2 \times m - 1$ 个对角线了。

至此，我们按照证明的构造，即可构造出点数为 $n - \lfloor \frac{n + 1}{3} \rfloor$ 的方案了，感受一下，应该是最优的了，交一发，过了。

---

## 作者：ethan0328 (赞：1)

## 思路
假如我们放 $k$ 个后，假设放在左上角，使得右下只有 $(n-k)\times(n-k)$ 个格子没被覆盖，我们要用对角线去覆盖它们。

$(n-k)\times(n-k)$ 个格子有 $2\times(n-k)-1$ 条对角线，所以 $k \ge 2\times(n-k)-1$，即 $k \ge \lfloor \frac{2n+1}{3} \rfloor$。

当 $k=\lfloor \frac{2n+1}{3} \rfloor$，我们可以考虑先在 $(1,1)$ 放一个后，然后横坐标 $+1$，纵坐标 $+2$，再放一个后，不停地放，直到出右上角的 $k\times k$ 的矩形为止。然后我们再横坐标 $+1$，纵坐标为 $2$ 的点开始用同样的方式放。

为什么这是对的？我们不妨给对角线标号，令 $(k+1,k+1)$ 所在的对角线为 $0$，它左边的对角线分别为 $-1,-2\dots$，右边的对角线分别为 $1,2\dots$，我们第一个在 $(1,1)$ 的后覆盖了对角线 $0$，后面每次的后覆盖了上一条 $-1$ 的对角线。而在 $(\lfloor \frac{k}{2} \rfloor+1,2)$ 的点覆盖了对角线 $n-k-1$，后面每条覆盖了上一条 $-1$ 的对角线。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
signed main()
{
	cin>>n;
	k=(n*2+1)/3;
	cout<<k<<"\n";
	for(int i=1,j=1;j<=k;j++,i+=2)
	{
		if(i>k)
		{
			i=2;
		}
		cout<<i<<" "<<j<<endl;
	}
}
```

---

## 作者：xxgirlxx (赞：0)

一起来对脑电波，欢乐多又多（可能讲得不好，还请大佬们见谅）。

可以发现最优的情况下每个半皇后之间互相攻击不到（这样才能最大化使用行、列和斜线），然后就可以让每行、每列、每个斜线延伸到下、右边界时互相不重叠（除非三倍答案大于 $2\times n-1$）。因此可以得出答案是 $\lceil\frac{2\times n-1}{3}\rceil$，并且有了一个大致的构造方向：就是让每个半皇后之间互相攻击不到（~~怎么在水字数~~）。

具体怎么构造呢？

我们可以把整个棋盘切一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/3hq3ddnm.png)

其中放棋子的区域是一个正方形，边长为 $\lceil\frac{2\times n-1}{3}\rceil$（~~是的没错就是棋子数量~~），这样的话范围就变小了，更方便构造了。

然后发现假设从 $(1,1)$ 开始放置棋子，下一个棋子就得放在 $(2,3)$，因为 $(2,2)$ 被上一个棋子的斜线攻击了。以此类推，直到放不了下一个（即下一个棋子的行超过了 $\lceil\frac{2\times n-1}{3}\rceil$）。

那剩下的怎么放呢？发现之前每两个棋子之间还空了一行，刚好可以拿来放剩下的，注意即使我们是的行减了，但是为了保证列上的棋子不会相互攻击，新放的棋子的列仍旧得是上一个棋子的列加一，而且接下来的每一个棋子的行也刚好都是在之前每两个棋子的行之间。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,num;
int main(){
	cin>>n,ans=(n*2-1)/3+((n*2-1)%3!=0),num=1;
	cout<<ans<<"\n";
	for(int i=1;i<=ans;i+=2,num++)cout<<i<<" "<<num<<"\n";
	for(int i=2;i<=ans;i+=2,num++)cout<<i<<" "<<num<<"\n";
	return 0;
}
```

---

