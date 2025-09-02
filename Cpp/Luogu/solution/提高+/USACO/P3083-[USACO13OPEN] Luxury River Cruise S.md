# [USACO13OPEN] Luxury River Cruise S

## 题目描述

Farmer John is taking Bessie and the cows on a cruise! They are sailing on a network of rivers with N ports (1 <= N <= 1,000) labeled 1..N, and Bessie starts at port 1. Each port has exactly two rivers leading out of it which lead directly to other ports, and rivers can only be sailed one way.

At each port, the tour guides choose either the "left" river or the "right" river to sail down next, but they keep repeating the same choices over and over. More specifically, the tour guides have chosen a short sequence of M directions (1 <= M <= 500), each either "left" or "right", and have repeated it K times (1 <= K <= 1,000,000,000). Bessie thinks she is going in circles -- help her figure out where she ends up!


农民约翰带着Bessie和奶牛在邮轮上！他们在网格上的N条河流航行（1≤N≤1000）标记为1到N，一开始他们在开始在河口1。每一个港口都有两条河流直通，直接通往其他港口，河流只能通过一条路航行。


在每一个港口，导游选择左边的河或右边的河向下航行，但他们不断重复相同的选择一遍又一遍。更具体地说，导游选择了一个m方向（1 < =m= 500），每一个向左或向右，并重复它K次（1 < = K = 1000000000）。Bessie认为她是在兜圈子，帮她找出结束的位置！


## 说明/提示

The port numbers are arranged clockwise in a circle, with 'L' being a clockwise rotation and 'R' being a counterclockwise rotation. The sequence taken is LLRLLRLLR.


After the first iteration of the sequence of directions, Bessie is at port 2 (1 -> 2 -> 3 -> 2); after the second, she is at port 3 (2 -> 3 -> 4 -> 3), and at the end she is at port 4 (3 -> 4 -> 1 -> 4).

感谢 @ SilverWolf 提供翻译


## 样例 #1

### 输入

```
4 3 3 
2 4 
3 1 
4 2 
1 3 
L L R 
```

### 输出

```
4 
```

# 题解

## 作者：红黑树 (赞：7)

## 题意
给定 $N$ 个点的图，每个点有两条出边，给定一条长 $M$ 的指令，从 $1$ 出发按照指令移 $K$ 轮，求最终位置。

## 思路
可以对移动的过程进行模拟，但由于 $K$ 很大，这样做比较低效。

由于每一轮移动的指令都是一样的，所以我们可以将一轮移动看作一个整体。由于一共只有 $N$ 个点，所以最多移动 $N$ 轮以后必然会产生环，环中的移动是重复的，可以利用同余来处理。

因此，我们从 $1$ 出发模拟移动直到找到环，再根据 $K$ 在环上还是环外来求解终点即可。

## 复杂度
### 时间
* 模拟找环次数 $\mathcal O(N)$
* 每次移动 $\mathcal O(M)$
* 总共 $\mathcal O(NM)$。

### 空间
* 记录图 $\mathcal O(N)$
* 记录指令 $\mathcal O(M)$
* 总共 $\mathcal O(N + M)$

## Code
```cpp
#include <icecream>
#include <utility>
#include <vector>

using namespace std;
using tp = long long int;

tp m;
vector<char> d;
vector<pair<tp, tp>> go;

struct Item_t {
  tp p, r;

  Item_t() = default;
  Item_t(tp _p, tp _r) : p(_p), r(_r) {}

  Item_t move() {
    p = (d[r] == 'L' ? go[p].first : go[p].second);
    r = (r + 1) % m;
    return *this;
  }

  bool operator==(const Item_t& comp) const {
    return p == comp.p && r == comp.r;
  }

  bool operator!=(const Item_t& comp) const {
    return !(*this == comp);
  }
};

signed main() {
  tp n, k;
  Item_t _1(1, 0), _2(1, 0);
  scanf("%lld%lld%lld", &n, &m, &k);
  k *= m;
  d = vector<char>(m);
  go = vector<pair<tp, tp>>(n + 1);
  for (tp i = 1; i <= n; ++i) {
    scanf("%lld%lld", &go[i].first, &go[i].second);
  }
  for (auto&& i : d) {
    cin >> i;
  }
  while (k--) {
    _2.move();
    if (_1.move() == _2.move()) {
      break;
    }
  }
  k += !~k;
  if (k) {
    tp cnt = 1;
    while (_1.move() != _2) {
      ++cnt;
    }
    for (k %= cnt; k--; _1.move()) {
    }
  }
  cout << _1.p << '\n';
  return 0;
}
```

---

## 作者：Priori_Incantatem (赞：4)

[题目](https://www.luogu.com.cn/problem/P3083)

这题其实是一道倍增题，跟[这题](https://www.luogu.com.cn/problem/P6148)很
像

$f[i][j]$ 表示以第 $i$ 个点为起点，将操作序列进行 $2^j$ 次后 Bessie 所停留在的点

学过 LCA 的人都知道，倍增通常的转移是这样的 $f[i][j]=f[f[i][j-1]][j-1]$

最后寻找答案时，将 $k$ 二进制拆分，并累加 $f$ 数组

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int Maxn=1010,Maxm=35,inf=0x3f3f3f3f;
int d[Maxn][2],f[Maxn][Maxm];
int n,m,k;
bool flag[Maxn];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)
	scanf("%d%d",&d[i][0],&d[i][1]);
	for(int i=1;i<=m;++i)
	{
		char opt;
		scanf("%s",&opt);
		if(opt=='R')flag[i]=1;
	}
	for(int i=1;i<=n;++i)
	{
		int x=i;
		for(int j=1;j<=m;++j)
		x=d[x][flag[j]];
		f[i][0]=x;
	}
	for(int j=1;j<=30;++j)
	for(int i=1;i<=n;++i)
	f[i][j]=f[f[i][j-1]][j-1];
	int x=1;
	for(int i=30;i>=0;--i)
	if(k>=(1<<i))
	{
		k-=(1<<i);
		x=f[x][i];
	}
	printf("%d\n",x);
	return 0;
}
```

---

## 作者：巨型方块 (赞：3)

经过仔细的读题目之后就会发现这就是一道模拟题

题目看不懂的同学可以看看样例解释

那么显然我们用一个m次操作为单位，每单位循环得到一个新的点，最多1000次就可以出现重复（指新点以前出现过），那么当出现重复的时候就出现循环节，那么接下来就是利用循环节取避免k次循环；

类似于除法的余数

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const int N=1e3+5;
int a[N],v[N][2],vi[N];
int n,m,k,now,top;
char c;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)scanf("%d%d",&v[i][0],&v[i][1]);
    for(int i=1;i<=m;i++){
        cin>>c;
        if(c=='R')a[i]=1;
    }
    now=1;
    while(!vi[now]){
        vi[now]=++top;
        for(int i=1;i<=m;i++)now=v[now][a[i]];
    }
    int x=top-vi[now]+1;
    int y=vi[now]-1;
    k-=y;
    k%=x;
    while(k--)
        for(int i=1;i<=m;i++)now=v[now][a[i]];
    printf("%d",now);
}
```

---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候对题目已经有了深入的了解

经过观察，我们可以发现枚举之后必然会形成一个循环

然而，直接暴力枚举循环节的时间十分的正确

我们考虑直接暴力，通过暴力枚举循环节，枚举到循环节的时候，就直接暴力退出

把要枚举的长度对枚举的循环节长度取余，最后剩下来的部分直接暴力枚举剩下来的
部分，就可以直接求出答案

代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,m;
int k;
int l[1010];
int r[1010];
int a[1010];
int v[1010];
int now;
int pop;
int sum1,sum2;
signed main(){
	n=read();
	m=read();
	k=read();
	for(register int i=1;i<=n;++i)
		{
			l[i]=read();
			r[i]=read();
		}
	for(register int i=1;i<=m;++i)
		{
			char c;
			cin>>c;
			if(c=='R')
				a[i]=1;
		}
	now=1;
	while(!v[now])
		{
			++pop;
			v[now]=pop;
			for(register int i=1;i<=m;++i)
				{
					if(a[i]==0)
						now=l[now];
					else
						now=r[now];
				}
		}
	sum1=pop-v[now]+1;
	sum2=v[now]-1;
	k-=sum2;
	k%=sum1;
	while(k--)
		{
			for(register int i=1;i<=m;++i)
				{
					if(a[i]==0)
						now=l[now];
					else
						now=r[now];	
				}
		}
	write(now);
	return 0;
}

```


---

## 作者：Chavapa (赞：1)

### 刚开始看到题目真的被吓到了QAQ
## 第一眼看是图论，本蒟蒻觉得好难
## 第二眼一看数据范围，~~脑袋一片空白~~
## 第三次再读题目，发现根本不是图论，而是道玄学的模拟题

#### 本蒟蒻：哇哇哇~~此题真的好良心~~！……
 _画外音：什么？~~提高+/省选-~~？？你在跟我开玩笑？_ 

### 咳咳，进入正题：
[最简单方法：暴力模拟] 60pts（~~什么，暴力能拿60？？~~）

只需用a数组存储每个结点后继的左右两点，然后写一个k*m的循环模拟即可。

代码：

```
program cruise;
var n,m,k,i,j,x,s:longint;
    a:array[1..1000,1..2] of longint;
    ch:array[1..500] of char;
    t:char;
begin
  readln(n,m,k);
  for i:=1 to n do readln(a[i,1],a[i,2]);
  for i:=1 to m do
  begin
    read(ch[i]); if not(eof) then read(t);
  end;
  x:=1;
  for i:=1 to k do
    for j:=1 to m do
      if ch[j]='L' then x:=a[x,1] else x:=a[x,2];
  writeln(x);
end.

```

[满分方法] 期望得分：100pts

观察到k的范围非常大，而且我们知道直接模拟是行不通的，所以这个图中必有回环。

所以我们要尝试找出这条重复走的路径。

然而如何判断一条路径重复走了多次？可以新建一个数组f用于存储该点是否走到过，如果当前找到的点标记为走过，则接下来要遍历的路径必然与之前重复。

我们定义ans[i]表示从i号结点出发走了M次（按照方向序列）后所到达的点编号，则可以通过预处理算出ans[1]-ans[n]的值。

那么我们在遍历时直接调用ans[i]即可。

举例：从结点x走M次到达的结点：x:=ans[x];

与先前的O(M)复杂度比较，速度提升到O(1)。

这样一来，我们只需先找到一条回环，然后将k值对回环的长度取模，再做一遍模拟即可。

代码：
```
program cruise;
var n,m,k,i,j,x,s:longint;
    a:array[1..1000,1..2] of longint;
    ch:array[1..500] of char;
    ans:array[1..1000] of longint;
    f:array[1..1000] of longint;
    t:char;
begin
  readln(n,m,k);
  for i:=1 to n do readln(a[i,1],a[i,2]);  //读入邻边关系
  for i:=1 to m do
  begin
    read(ch[i]); if not(eof) then read(t);  //读入长度序列
  end;
  for i:=1 to n do  //对每个结点进行预处理，将走M次后到达的结点编号存储
  begin
    x:=i;
    for j:=1 to m do
      if ch[j]='L' then x:=a[x,1] else x:=a[x,2];
    ans[i]:=x;
  end;
  f[1]:=0; x:=1;  //初始化，从1号节点开始走
  while 0=0 do
  begin
    x:=ans[x]; inc(s);  //取后继结点编号，计数器加1
    if f[x]>0 then begin k:=k-f[x]; s:=s-f[x]; break; end;  //如果该结点走过，则跳出循环
                                                            //注意必须将k值减去回环之前的步数；然后s也要作同样处理，用于保存回环长度
    f[x]:=s;  //标记为走过
  end;
  k:=k mod s;  //对结果取模
  for i:=1 to k do x:=ans[x];  //最后从该回环起点开始，模拟一遍即可
  writeln(x);
end.
```

---

