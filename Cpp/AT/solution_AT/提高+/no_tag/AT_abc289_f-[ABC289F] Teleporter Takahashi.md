# [ABC289F] Teleporter Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc289/tasks/abc289_f

$ xy $ 平面上に高橋くんがいます。 はじめ、高橋くんは点 $ (s\ _\ x,s\ _\ y) $ にいます。 高橋くんは、点 $ (t\ _\ x,t\ _\ y) $ に移動したいです。

$ xy $ 平面上に、長方形 $ R\coloneqq\lbrace(x,y)\mid\ a-0.5\leq\ x\leq\ b+0.5,c-0.5\leq\ y\leq\ d+0.5\rbrace $ があります。 次の操作を考えます。

- 長方形 $ R $ に含まれる格子点 $ (x,y) $ をひとつ選ぶ。 点 $ (x,y) $ を中心に高橋くんはいまいる位置と対称な位置に瞬間移動する。
 
上の操作を $ 0 $ 回以上 $ 10^6 $ 回以下繰り返して、高橋くんが点 $ (t\ _\ x,t\ _\ y) $ にいるようにできるか判定してください。 できる場合、高橋くんが点 $ (t\ _\ x,t\ _\ y) $ に移動することができるような操作の列を $ 1 $ つ構成してください。

## 说明/提示

### 制約

- $ 0\leq\ s\ _\ x,s\ _\ y,t\ _\ x,t\ _\ y\leq2\times10^5 $
- $ 0\leq\ a\leq\ b\leq2\times10^5 $
- $ 0\leq\ c\leq\ d\leq2\times10^5 $
- 入力はすべて整数
 
### Sample Explanation 1

例えば、次のようにして $ (1,2) $ から $ (7,8) $ へ移動することができます。 - 点 $ (7,0) $ を選ぶ。高橋くんは $ (13,-2) $ に移動する。 - 点 $ (9,3) $ を選ぶ。高橋くんは $ (5,8) $ に移動する。 - 点 $ (7,1) $ を選ぶ。高橋くんは $ (9,-6) $ に移動する。 - 点 $ (8,1) $ を選ぶ。高橋くんは $ (7,8) $ に移動する。 !\[\](https://img.atcoder.jp/abc289/d6d2cc458bbc92e975ba267856f673cf.png) 条件を満たす操作の列であれば何を出力しても正答となるので、例えば ``` Yes 7 3 9 0 7 2 9 1 8 1 ``` と出力しても正答となります。 !\[\](https://img.atcoder.jp/abc289/3faa56b1d245b87bd4cc36083495383c.png)

### Sample Explanation 2

どのように操作しても点 $ (8,4) $ に移動することはできません。 !\[\](https://img.atcoder.jp/abc289/eb363d09e74f89c5474a4fc7529308bc.png)

### Sample Explanation 3

高橋くんがはじめから目的地にいる場合もあります。

## 样例 #1

### 输入

```
1 2
7 8
7 9 0 3```

### 输出

```
Yes
7 0
9 3
7 1
8 1```

## 样例 #2

### 输入

```
0 0
8 4
5 5 0 0```

### 输出

```
No```

## 样例 #3

### 输入

```
1 4
1 4
100 200 300 400```

### 输出

```
Yes```

## 样例 #4

### 输入

```
22 2
16 7
14 30 11 14```

### 输出

```
No```

# 题解

## 作者：康立扬 (赞：4)

~~数学题，但可以贪心过~~

### 题意：

在平面直角坐标系中，给定起点 $S(sx,sy)$ 与终点 $T(tx,ty)$，和一个长方形 $R := \{(x,y)|a-0.5\le x \le b+0.5, c-0.5\le y \le d+0.5\}$，$S$ 上有一颗棋子。每次操作可以在长方形中选定一个点，让棋子跳到指定点的对称点，也就是在长方形内选定点 $(kx,ky)$，使棋子从 $(x,y)$ 跳到 $(2kx-x,2ky-y)$ 问能不能在 $10^6$ 次操作内使得棋子到达 $T$，如果能到达，输出每次操作选定的点。  
注意，**输出不要求操作数最少。**

### 做法:

#### 分开考虑纵坐标与横坐标。

对于横坐标，考虑到当 $b-a\ge1$ 时，连续选择 $(a,c)$ 点与 $(a+1,c)$ 可使得棋子从 $(x,y)$ 跳到 $(x\pm2,y)$ 的位置，因此可以重复至多 $2\times 10^5$ 次使得棋子的横坐标与T相同。  
对于 $a=b$ 的情况，特判处理。  
纵坐标同理。  
总操作次数上限为 $4\times10^5$，没问题。

##### 注意：

每次操作后，$x$ 坐标和 $y$ 坐标的奇偶性不变。因此要特判处理。
### 代码:

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

inline int read()
{
    int s=0;
    scanf("%lld",&s);
    return s;
}
int sx,sy,tx,ty,a,b,c,d,cnt;
struct ans{
    int x,y;
}ans[1000010];
void move(int x,int y){
    sx=2*x-sx;
    sy=2*y-sy;
    ans[cnt++]={x,y};
}
signed main()
{
    //ios::sync_with_stdio(false);
    sx=read(),sy=read(),tx=read(),ty=read();
    a=read(),b=read(),c=read(),d=read();
    if(sx==tx&&sy==ty) puts("Yes"),exit(0);
    int lenx=b-a,leny=d-c;
    if(sx%2!=tx%2) puts("No"),exit(0);
    if(sy%2!=ty%2) puts("No"),exit(0);
    if(lenx==0&&sx!=tx) move(a,c);
    if(leny==0&&sy!=ty) move(a,c);
    if(lenx==0){
        if(sx!=tx) puts("No"),exit(0);
    }
    else{
        while(sx<tx){
            move(a,c);
            move(a+1,c);
        }
        while(sx>tx){
            move(a+1,c);
            move(a,c);
        }
    }
    if(leny==0){
        if(sy!=ty) puts("No"),exit(0);
    }
    else{
        while(sy<ty){
            move(a,c);
            move(a,c+1);
        }
        while(sy>ty){
            move(a,c+1);
            move(a,c);
        }
    }
    puts("Yes");
    for(int i=0;i<cnt;i++){
        cout<<ans[i].x<<" "<<ans[i].y<<"\n";
    }
    return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：4)

## 思路

首先判掉奇偶性不对的无解。

你有一个点。对给定矩形进行对称。你会得到一个大矩形（实现时只需考虑四个角）。表示大矩形中奇偶性合法的点你都能达到。大矩形的边长应该是给定的矩形的两倍。

你有一个矩形。对给定矩形进行对称。你会得到一个更大矩形（实现时也只需考虑四个角）。含义同上。

某一步后目标点在矩形内，就有解。

$10^6$ 步后还没有，就无解。

然后构造方案。

从后往前，用与第一步相同的做法，得到一个两倍大小矩形。由于我们的更大矩形实在是太大了，所以能够保证两倍大小矩形的四角中至少有一个在更大矩形中。走过去即可。

当然，最后一步要正好走回起点，所以不一定有上一条性质。但是可以直接取中点。

## code

```cpp
#include<stdio.h>
#include<vector>
using namespace std;
int sx,sy,tx,ty,a,b,c,d,ans[1111111],bns[1111111];
vector<int>w,x,y,z;
inline int qwq(const int&x,const int&y){return y+(y-x);}
main()
{
	scanf("%d%d%d%d%d%d%d%d",&sx,&sy,&tx,&ty,&a,&b,&c,&d);
	if((sx&1^tx&1)||(sy&1^ty&1)){printf("No");return 0;}
	w.emplace_back(sx);x.emplace_back(sx);
	y.emplace_back(sy);z.emplace_back(sy);
	for(int i=0;i<1000000;++i)
	{
		if(w[i]<=tx&&tx<=x[i])if(y[i]<=ty&&ty<=z[i])break;
		w.emplace_back(qwq(x[i],a));
		x.emplace_back(qwq(w[i],b));
		y.emplace_back(qwq(z[i],c));
		z.emplace_back(qwq(y[i],d));
	}
	if(w.back()<=tx&&tx<=x.back()&&y.back()<=ty&&ty<=z.back())
	{
		printf("Yes\n");
		if(x.size()==1)return 0;
		for(int i=x.size()-1;i>1;--i)
		{
			if(w[i-1]<=qwq(tx,a)&&qwq(tx,a)<=x[i-1])
				tx=qwq(tx,a),ans[i]=a;
			else tx=qwq(tx,b),ans[i]=b;
			if(y[i-1]<=qwq(ty,c)&&qwq(ty,c)<=z[i-1])
				ty=qwq(ty,c),bns[i]=c;
			else ty=qwq(ty,d),bns[i]=d;
		}
		printf("%d %d\n",sx+tx>>1,sy+ty>>1);
		for(int i=2;i<x.size();printf("%d %d\n",ans[i],bns[i]),++i);
	}
	else printf("No");
}
```

---

## 作者：shinkuu (赞：2)

好题！

题目给了 $10^6$ 次操作机会，基本上每次靠近一格都行。

考虑做一次对称的本质，$(x_1,y_1)$ 关于 $(x_2,y_2)$ 对称点即为 $(x_1+2\times(x_2-x_1),y_1+2\times(y_2-y_1))$。这是 $x_1<x_2,y_1<y_2$ 时的情况，其他同理。

容易发现移动距离一定为 $2$ 的倍数，于是得出结论 $1$：**起点终点横纵坐标相对应，奇偶性不同时无解**。

接下来考虑如何构造操作序列。容易发现，将 $(x_1,y_1)$ 关于 $(x_2,y_2)$ 做一次对称，再关于 $(x_2+1,y_2)$ 做对称，会变成 $(x_1+2,y_2)$。其他方向同理。最多操作 $4\times 10^5$ 次。于是有结论 $2$：**当 $a\not=b$ 且 $c\not=d$ 时，一定有解**。

如果 $a=b$ 或 $c=d$ 呢？**可能起点终点横或纵坐标相等**，那在这一维上不用移动。特判一下。

如果不等就一定无解吗？**有可能 $s_x$ 和 $t_x$ 关于 $x=a$ 对称**，特判一下，$y$ 同理。

还是有错误？**可能 $a=b\land c=d$，而对称了两次**。再特判一下。

于是首次场切 F。

[Submission](https://atcoder.jp/contests/abc289/submissions/41261404)（好吉利的数字）

---

## 作者：_Imaginary_ (赞：1)

提供一种和大部分人不同的做法。

## Problem

平面上有两个点 $S,T$。给定一个矩形内的整点构成的集合 $\mathcal{F}$，问能否用不超过 $10^6$ 步，从 $S$ 开始，每次选择 $\mathcal{F}$ 中的一个点 $A$，从 $S$ 移动到它关于 $A$ 的对称点。如果可以的话，输出方案。

## Solution 1

这个是大部分人的做法，基本上一句话就能说清楚。

$(x,y)$ 经过 $(a,b)$ 再经过 $(a,b+1)$ 可跳到 $(x,y+2)$。

所以，可以转化成用两步，使 $x$ 或 $y$ 变化 $2$ 格位置。

这种我不细讲，看下一个。

## Solution 2

个人感觉比较直观，但有点烦。

考虑 $k$ 步能跳到的点的集合。

![](https://cdn.luogu.com.cn/upload/image_hosting/ud6xlirf.png)

通过感性理解，可以发现：（两条分别对应上面和下面的图，红的表示起点的可能位置，绿表示终点的可能位置）

- 一个点经过给定的矩形可以走到的点也构成一个矩形，不过这些点的横纵坐标奇偶性相同。具体的，相当于可以走到的点相当于一个 $2\times 2$ 方格网的格点的一部分。

- 一个 $2\times 2$ 方格网的格点的一部分也可以变成一个 $2\times 2$ 方格网的格点的一部分。（这是因为，原来相隔 $2$ 的点可以通过两个相隔 $1$ 的点变成两个相隔 $0$ 的点，即同一个点）

我们可以暴力处理下一步的可能位置。具体的，枚举原来矩形 $4$ 个顶点的可能转移位置（也就是 4 个对应的矩形）的并。

这样，我们可以用 $O(10^6)$ 的时间判断 $T$ 是否可达。

问题来了，如果 $T$ 可达，怎么构造呢？

首先，$T$ 可达，$T$ 一定是由某一个点转移过来的，而那一个点也是由前一个点转移过来的，……，最终是由 $S$ 转移过来的。

由于我们在每一步都保存了一个矩形，表示用 $k$ 步可能到达的所有位置，假设 $T$ 是第 $t+1$ 步，我们只需要找到第 $t$ 步对应的矩形中哪一个点能通过反射到达 $T$，然后重复此过程直到 $S$。

怎么找呢？首先，我们设第 $t$ 部对应矩形的左下角是 $(x1,y1)$。假如我们从 $T$ 开始再走一步，能到达的区域（类似从 $S$ 开始走一步能到达的点）也是一个矩形，设它的左下角是 $(x2,y2)$。那么，$(\max\{x1,x2\},\max\{y1,y2\})$ 可行，读者自证不难。

比较复杂，具体看代码，其中 `tele(x,y)`，表示求出这个点反射后可能到达的点。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define y1 hkfsdhgsjdaggrhkerjhbialerbjorhggerukhakjhg
const ll inf=0x3f3f3f3f3f3f3f3f;
ll sx,sy;
ll tx,ty;
ll x1,y1,x2,y2;
int t=1000000;
struct node{
	ll x1,y1,x2,y2;
}a[1000005];
struct pt{
	ll x,y;
}ans[1000005];
node in;
void tele(ll x,ll y)
{
	in.x1=min(in.x1,2*x1-x);
	in.x2=max(in.x2,2*x2-x);
	in.y1=min(in.y1,2*y1-y);
	in.y2=max(in.y2,2*y2-y);
}
void get_ans(int id,ll x,ll y,ll gx,ll gy)
{
	ans[id].x=(x+gx)/2;
	ans[id].y=(y+gy)/2;
}
int main()
{
	scanf("%lld%lld%lld%lld",&sx,&sy,&tx,&ty);
	scanf("%lld%lld%lld%lld",&x1,&x2,&y1,&y2);
	if(sx==tx&&sy==ty)
	{
		printf("Yes");
		return 0;
	}
	if((tx-sx)%2!=0||(ty-sy)%2!=0)
	{
		printf("No");
		return 0;
	}
	a[0]=node{sx,sy,sx,sy};
	bool ok=0;
	for(int i=1;i<=t;i++)
	{
		in={inf,inf,-inf,-inf};
		tele(a[i-1].x1,a[i-1].y1);
		tele(a[i-1].x1,a[i-1].y2);
		tele(a[i-1].x2,a[i-1].y1);
		tele(a[i-1].x2,a[i-1].y2);
		a[i]=in;
		if(in.x1<=tx&&tx<=in.x2&&in.y1<=ty&&ty<=in.y2)
		{
			ok=1;
			t=i;
			break;
		}
	}
	if(!ok)
	{
		printf("No");
		return 0;
	}
	printf("Yes\n");
	for(int i=t;i>=1;i--)
	{
		in={inf,inf,-inf,-inf};
		tele(tx,ty);
		ll xx=max(in.x1,a[i-1].x1);
		ll yy=max(in.y1,a[i-1].y1);
		get_ans(i,tx,ty,xx,yy);
		tx=xx;
		ty=yy;
	}
	for(int i=1;i<=t;i++)
	{
		printf("%lld %lld\n",ans[i].x,ans[i].y);
	}
	return 0;
}

```

---

## 作者：Missa (赞：0)

某人 vp 时 10min 口胡了这道题，然后调了两天，第一天卡在 WA 4，第二天 WA 7 WA 10 交相辉映，心态快崩了，因此写了这篇题解。

$a=b$ 处理有借鉴 [这篇题解](https://www.cnblogs.com/Lanly/p/17113815.html)。

------------

first observation：两维独立。

显然。一次操作可以看成两维分别选点操作。后面的操作均在一维上。

second observation：两次分别选择 $s$ 与 $t$ 的操作可以看成 $x \gets x + 2(t - s)$。

显然。手动模拟都行。

然后你发现一次操作不影响奇偶性，然后可以把两点奇偶性不同的情况判掉。然后你发现你可以移动任意偶数步，就做完了……吗？

判掉 $s=t$，那时有可能只会翻转一次。

回到组合两维的地方。我的做法是翻 $x$ 时永远选择 $y=c$。这样子在 $a \neq b$ 即第一维操作偶数次一定可行。那么 $a \neq b$ 且 $c \neq d$ 做完了。接着来看 $a = b$ 或 $c = d$。

现在考虑有至少一者相等。先判掉两维均相等。

如果 $a = b$ 且 $sx \neq tx$ 可以先对 $(a, c)$ 操作，$c = d$ 同理。这样显然不会影响另一维上的操作，因为由构造 $a \neq b$ 时一定有解。然后做完了。

感觉在空心黄中算是很简单。要不是它难调我觉得空心蓝都行。


```cpp
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
vector<int> work(int x, int a, int b, int y) {
  vector<int> w;
  if(a == b) {
    if(x != y) w.push_back(a);
    return w;
  }
  while (x < y) {
    w.push_back(a); w.push_back(a + 1);
    x += 2;
  }
  while(x > y) {
    w.push_back(a+1); w.push_back(a);
    x -= 2;
  }
  return w;
}

vector<pair<int, int> > ans;
int x1, y1, x2, y2, a, b, c, d; 
int solve() {
  ans.clear();
  if(abs(x1 % 2) != abs(x2 % 2)) return 0;
  if(abs(y1 % 2) != abs(y2 % 2)) return 0;
  if(a == b && x1 != x2 && (2 * a - x1) != x2) return 0;
  if(c == d && y1 != y2 && (2 * c - y1) != y2) return 0;
  if(a == b && c == d) {
    if(x1 == x2 && y1 == y2) return 1;
    int x3 = 2 * a - x1, y3 = 2 * c - y1;
    if(x3 == x2 && y3 == y2) return ans.push_back({a, c}), 1;
    else return 0;
  }
  if(a == b && x1 != x2) {
    ans.push_back({a, c}); x1 = 2 * a - x1; y1 = 2 * c - y1;
  }
  if(c == d && y1 != y2) {
    ans.push_back({a, c}); x1 = 2 * a - x1; y1 = 2 * c - y1;
  }
  vector<int> x = work(x1, a, b, x2), y = work(y1, c, d, y2);
  for(auto u : x) ans.push_back({u, c});
  for(auto v : y) ans.push_back({a, v});
  return 1;
}

int main () {
  scanf("%d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &a, &b, &c, &d);
  if(solve()) {
    printf("Yes\n");
    for(auto i : ans) {
      int x = i.first, y = i.second;
      printf("%d %d\n", x, y);
    }
  } else printf("No\n");
}
```

---

