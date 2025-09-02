# Rock, Paper, Scissors

## 题目描述

Alice and Bob have decided to play the game "Rock, Paper, Scissors".

The game consists of several rounds, each round is independent of each other. In each round, both players show one of the following things at the same time: rock, paper or scissors. If both players showed the same things then the round outcome is a draw. Otherwise, the following rules applied:

- if one player showed rock and the other one showed scissors, then the player who showed rock is considered the winner and the other one is considered the loser;
- if one player showed scissors and the other one showed paper, then the player who showed scissors is considered the winner and the other one is considered the loser;
- if one player showed paper and the other one showed rock, then the player who showed paper is considered the winner and the other one is considered the loser.

Alice and Bob decided to play exactly $ n $ rounds of the game described above. Alice decided to show rock $ a_1 $ times, show scissors $ a_2 $ times and show paper $ a_3 $ times. Bob decided to show rock $ b_1 $ times, show scissors $ b_2 $ times and show paper $ b_3 $ times. Though, both Alice and Bob did not choose the sequence in which they show things. It is guaranteed that $ a_1 + a_2 + a_3 = n $ and $ b_1 + b_2 + b_3 = n $ .

Your task is to find two numbers:

1. the minimum number of round Alice can win;
2. the maximum number of rounds Alice can win.

## 说明/提示

In the first example, Alice will not win any rounds if she shows scissors and then paper and Bob shows rock and then scissors. In the best outcome, Alice will win one round if she shows paper and then scissors, and Bob shows rock and then scissors.

In the second example, Alice will not win any rounds if Bob shows the same things as Alice each round.

In the third example, Alice always shows paper and Bob always shows rock so Alice will win all three rounds anyway.

## 样例 #1

### 输入

```
2
0 1 1
1 1 0```

### 输出

```
0 1```

## 样例 #2

### 输入

```
15
5 5 5
5 5 5```

### 输出

```
0 15```

## 样例 #3

### 输入

```
3
0 0 3
3 0 0```

### 输出

```
3 3```

## 样例 #4

### 输入

```
686
479 178 29
11 145 530```

### 输出

```
22 334```

## 样例 #5

### 输入

```
319
10 53 256
182 103 34```

### 输出

```
119 226```

# 题解

## 作者：AsunderSquall (赞：18)

update：远古题解一大堆格式错误，试图一个个修复。  

~~你们巨佬的代码怎么都这么长啊，让我来水一发短的代码~~


**题意**  
两个人玩石头剪刀布。A 出了 $a_1$ 个石头，$a_2$ 个剪刀，$a_3$ 个布。B 出了 $b_1$ 个石头，$b_2$ 个剪刀，$b_3$ 个布。  
求 A 最少赢的次数和最多赢的次数。
（题目中还给了一个无用信息 $n=a_1+a_2+a_3=b_1+b_2+b_3$，不过可以使代码更简洁）  

**题解**  
考场上随便乱搞就整出来的题目为什么被你们搞的这么复杂？（逃

显然是两个独立的~~水~~问题。其中第二个更水。   

先考虑第 $2$ 个问题。  
A 出石头 $(a_1)$ 只有对应 B 出剪刀 $(b_2)$ 才能赢。   
那么赢的次数最多是 $\min(a_1,b_2)$。  
显然出石头、剪刀、布赢的次数相互独立，那么答案即为  $\min(a_1,b_2)+\min(a_2,b_3)+\min(a_3,b_1)$。  

再考虑第 $1$ 个问题。  
$a_1$ 对应不是 $b_2$ 的要尽量多。那么不赢的次数最多是 $\min(a1,n-b2)$。   
注意这一问和上一问不一样，出石头、剪刀、布不赢的次数并不相互独立。  
如果没有 $a_1+a_2+a_3=b_1+b_2+b_3 $ 这个条件就会错。     
那么在题目这个条件下，我们可以~~根据样例猜到~~证明答案就是 $n-\min(a_1,n-b_2)-\min(a_2,n-b_3)-\min(a3,n-b_1)$。

**~~口胡~~证明**

我们考虑出石头和出剪刀互相影响的情况应该是说，如果  $a_1>b_3 $ 且 $ a_2>b_2$ 此时剩余的石头和剩余的剪刀都要放在 B 出石头这个情况下，可能会溢出。  
但是由于 $a_1+a_2 \leq b_1+b_2+b_3$ 所以这样的情况并不会发生。  
证明有不严谨的地方请评论告诉我然后我会更新。


**代码**
```
#include<bits/stdc++.h>
using namespace std;
int n,a1,a2,a3,b1,b2,b3;
signed main()
{
	cin>>n>>a1>>a2>>a3>>b1>>b2>>b3;
	cout<<n-min(a1,n-b2)-min(a2,n-b3)-min(a3,n-b1)<<" "<<min(a1,b2)+min(a2,b3)+min(a3,b1);
}
```

---

## 作者：一扶苏一 (赞：8)

### Analysis

作为退役很久的选手已经不会分析那些妙妙妙的结论和性质了，但是智商不够可以用高级算法来凑。

对于第二问，贪心得尽可能让 Alice 赢即可。

对于第一问，考虑在”打满 $n$ 局“得情况下求”最小胜场“，是一个典型的最小费用最大流问题，建图如下：

对 Alice 和 Bob 分别建 $3$ 个点表示其石头、剪刀、布，建立超级源汇，源分别向 Alice 的三个点连流量为出该手势的对应次数，费用为 $0$ 的边；Bob 的三个点向源点连流量为该手势对应次数，费用为 $0$ 的边；Alice 向 Bob 的点连流量无穷的边，若该边表示 Alice 胜则费用为 $1$，否则费用为 $0$。

这张图的最小费用即为在跑满最大流 $n$ 时的最小胜场。

因为点数边数是常数级的，所以效率显然没有问题。

### Code

 ```cpp
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>

const int maxn = 100;

int n, a, b, c, x, y, z, s, t, id, ans;

struct Edge {
  int u, v, f, w;
  Edge *nxt, *bk;
  
  Edge(const int U, const int V, const int F, const int W, Edge *const h) : u(U), v(V), f(F), w(W), nxt(h), bk(NULL) {}
};
Edge *hd[maxn], *pre[maxn];
inline void cont(const int u, const int v, const int f, const int w) {
  auto x = new Edge(u, v, f, w, hd[u]), y = new Edge(v, u, 0, -w, hd[v]);
  hd[u] = y->bk = x;
  hd[v] = x->bk = y;
}

bool SPFA();
void work();

int main() {
  std::cin >> n >> a >> b >> c >> x >> y >> z;
  s = ++id; t = ++id;
  cont(s, ++id, a, 0);
  cont(s, ++id, b, 0);
  cont(s, ++id, c, 0);
  cont(++id, t, x, 0);
  cont(++id, t, y, 0);
  cont(++id, t, z, 0);
  cont(3, 7, n, 1);
  cont(4, 8, n, 1);
  cont(5, 6, n, 1);
  cont(3, 6, n, 0);
  cont(3, 8, n, 0);
  cont(4, 6, n, 0);
  cont(4, 7, n, 0);
  cont(5, 7, n, 0);
  cont(5, 8, n, 0);
  while (SPFA()) work();
  std::cout << ans << ' ';
  ans = 0;
  ans += std::min(a, y);
  ans += std::min(b, z);
  ans += std::min(c, x);
  std::cout << ans << std::endl;
  return 0;
}

std::queue<int> Q;
int dist[maxn], qg[maxn];
bool inq[maxn];

bool SPFA() {
  memset(dist, 0x3f, sizeof dist);
  dist[s] = 0; qg[s] = n + 1; Q.push(s);
  for (int u, v, w; !Q.empty(); Q.pop()) {
    inq[u = Q.front()] = false;
    for (auto e = hd[u]; e; e = e->nxt) if ((e->f > 0) && (dist[v = e->v] > (w = dist[u] + e->w))) {
      dist[v] = w;
      qg[v] = std::min(qg[u], e->f);
      pre[v] = e;
      if (!inq[v]) {
        Q.push(v);
        inq[v] = true;
      }
    }
  }
  return dist[t] != 0x3f3f3f3f;
}

void work() {
  for (Edge *e = pre[t]; e; e = pre[e->u]) {
    ans += qg[t] * e->w;
    e->f -= qg[t];
    e->bk->f += qg[t];
  }
}
 ```



---

## 作者：zhoukangyang (赞：5)

[来蒟蒻无人问津的博客园看/kel](https://www.cnblogs.com/zkyJuruo/p/13747865.html)

一眼题。

第一问很简单吧，就是每个 $\tt Alice$ 能赢的都尽量让他赢。

第二问很简单吧，就是让 $\tt Alice$ 输的或平局的尽量多，于是跑个网络最大流。$1 - 3$ 的点表示 $\tt Alice$ 选石头剪刀或布，$4-6$ 表示$\tt Bob$ 选石头剪刀或布。显然源点连 $1-3$, $4-6$ 连汇点。然后把 $\tt Alice$ 输或 $\tt Alice$ 平的连一下就好了呀。

```cpp
#include<bits/stdc++.h>
#define N 100010
#define inf 0x7ffffff
#define L(i, j, k) for(int i = j; i <= k; i++)
#define R(i, j, k) for(int i = j; i >= k; i--)
using namespace std;
int n,m,s,t,sum,cc[N],use[N];
int head[N],last[N];
struct node{
	int to,next,val;
} e[N << 1];
int edge_id = 1;
void add_edge(int x, int y, int val) {
	int id = ++edge_id;
	if(head[x]==0) head[x] = id;
	else e[last[x]].next=id;
	last[x]=id,e[id].val=val,e[id].to=y;
}
void add(int x, int y, int val) {
	add_edge(x, y, val);
	add_edge(y, x, 0);
}
void bfs() {
	for(int i = 1; i <= n; i++) use[i]=cc[i]=0;
	cc[s]=1,use[1]=s;
	int u=0,v=1;
	while(u<v) {
		++u;
		int fst=use[u];
		for(int i = head[fst]; i != 0; i = e[i].next) {
			if(cc[e[i].to]!=0) continue;
			if(e[i].val==0) continue;
			++v,cc[e[i].to]=cc[fst]+1,use[v]=e[i].to;
		}
	}
}
int dfs(int x,int val) {
	if(x==t) return val;
	if(cc[x]==cc[t]) {
		cc[x]=0;
		return 0;
	}
	int yuliu=val;
	for(int i = head[x]; i != 0; i = e[i].next) {
		if(cc[e[i].to]!=cc[x]+1) continue;
		int addd=dfs(e[i].to,min(e[i].val,yuliu));
		yuliu -= addd , e[i].val -= addd , e[i^1].val += addd;
	}
	return val-yuliu;
}
void Dinic(int &ans) {
	bfs();
	int addd=dfs(s,inf);
	ans += addd;
	if(addd==0) return;
	Dinic(ans);
}
int pn, A[4], B[4];
int main() {
	n = 8, m = 12, s = 7, t = 8;
    scanf("%d", &pn);
    L(i, 1, 3) scanf("%d", &A[i]), add(s, i, A[i]);
	L(i, 1, 3) scanf("%d", &B[i]), add(i + 3, t, B[i]);
    L(i, 1, 3) add(i, i + 3, 1e9);
    L(i, 1, 3) add(i, (i + 1) % 3 + 4, 1e9);
    Dinic(sum);
	printf("%d ", pn - sum);
    printf("%d\n", min(A[1], B[2]) + min(A[2], B[3]) + min(A[3], B[1]));
	return 0;
}
```

---

## 作者：KSToki (赞：2)

这道题第二问很简单，尽量要赢，显然答案为：$min(a1,b2)+min(a2,b3)+min(a3,b1)$。

主要是第一问，首先应该是尽量要输，然后是平，最后才让他赢。但是可能先用完石头不是最优解。不用想那么复杂，我们暴力枚举用完的顺序：

- 石头、剪刀、布
- 石头、布、剪刀
- 剪刀、石头、布
- 剪刀、布、石头
- 布、石头、剪刀
- 布、剪刀、石头

取最小值即可，可以保证正确性。

由于代码太长，~~又丑~~，所以放在了云剪贴板里。

[代码](https://www.luogu.com.cn/paste/mhsbtlex)

---

## 作者：胖头鱼学员 (赞：2)

# [Cf传送门](https://codeforces.com/contest/1426)
# [洛谷传送门](https://www.luogu.com.cn/problem/CF1426E)
## 题意
$Alice$和$Bob$进行石头剪刀布的游戏，总共进行$n$局。

$Alice$出石头$a_1$次，出剪刀$a_2$次，出布$a_3$次。

$Bob$出石头$b_1$次，出剪刀$b_2$次，出布$b_3$次。

问$Alice$最多能赢多少次，最少能赢多少次。
## 做法
首先我们得知道：

1. 石头可以赢剪刀；
2. 剪刀可以赢布；
3. 布可以赢石头。

对于每种出法，都是大同小异的，那么我们先考虑其中一种。
假设现在$Alice$分别出了$a_1$、$a_2$、$a_3$次石头、剪刀和布；$Bob$分别出了$b_2$、$b_1$次剪刀和布。
那么现在的问题变为了：
对于以上这种情况，$Alice$最多/最少能赢多少次呢？
### 1.求最多: 
我们可以尽可能让$Alice$的石头对上$Bob$的剪刀或是让$Alice$的剪刀对上$Bob$的布。

则最多可赢$min(a_1, b_2) + min(a_2, b_3)$次，

### 2.求最少:
我们可以尽可能让$Alice$的石头对上$Bob$的石头和布，让$Alice$的剪刀对上$Bob$的剪刀，这只求出了$Alice$最多可以输或平几次，所以还要用$n$减去。

则最少可以赢$n - min(a_1, b_1 + b_3) - min(a_2, b_2)$次。

那么我们现在把这几个公式拓展一下：
1. 求最多：$min(a_1,b_2) + min(a_2,b_3) + min(a_3,b_1)$；
2. 求最少：$n - min(a_1,b_1 + b_2) - min(a_2,b_2 + b_3) - min(a_3, b_3 + b_1)$。

## 代码如下
```cpp
#include <iostream>

using namespace std;

int n;
int a[4], b[4];

int main() {
  cin >> n;
  cin >> a[1] >> a[2] >> a[3];
  cin >> b[1] >> b[2] >> b[3];
  cout << n - min(a[2], b[1] + b[2]) - min(a[3], b[2] + b[3]) - min(a[1], b[3] + b[1]) << " " << min(a[1], b[2]) + min(a[2], b[3]) + min(a[3], b[1]);
  return 0;
}
```

---

## 作者：鹤箩芠 (赞：0)

感觉有趣的思维题用高大尚的算法解决掉会很无趣qwq ， 给出一个不一样的贪心思路。

题目中给了一个最重要的条件$\rightarrow a_1 +  a_2 + a_ 3 = b_1 + b_2 + b_3$
对于最大胜场很好考虑 
$ans = min (a_1 , b_2) + min (a_2 , b_3) + min (a_3 , b_1)$

对于最少胜场 ， 有一个很重要的结论 ， 那就是答案只含有（石头剪子布）中的最大的一个贡献 ， 也就是说不会出现石头有胜场 ， 剪刀也有胜场的情况。
为什么呢 ？ 对于石头的贡献是 $a_1  -b_1-b_3$ ， 若✂也有贡献那贡献之和就是 $a_1 + a_2 - b_1 - b_3 - b_2$ 若有贡献 ， 也就是大于0 ， 便不满足题目给出的条件。

那最少胜场答案也就是石头剪子布中贡献最大的那一个。
代码：

```cpp
	int a1 , a2 , a3 , b1 , b2 , b3 , n ;
	scanf ("%d%d%d%d%d%d%d" , &n , &a1 , &a2 , &a3 , &b1 , &b2 , &b3) ;
	printf ("%d %d" , max (0 , max (a1 - b1 - b3 , max (a2 - b2 - b1 , a3 - b3 - b2))) , min (a1 , b2) + min (a2 , b3) + min (a3 , b1)) ;
```


---

## 作者：STDquantum (赞：0)

可以非常简单地求出 Alice 赢的最多次数，只要能赢就赢，也就是 $maxAns=\min(a_1,b_2)+\min(a_2,b_3)+\min(a_3,b_1)$。

但是要是求最少次数，如何平衡打平和输掉的次数呢？

我们可以考虑枚举每一种顺序（即三种打平和三种输掉的不同组合顺序），用到了一个 STL 好东西叫 `next_permutation`。

时间复杂度 $\mathcal{O}(6!)$。

```cpp
struct E { // alice 和 bob
    int ch[5];
} a, b;
struct OP {
    int x, y;
    OP(int X = 0, int Y = 0) { x = X, y = Y; }
    inline friend bool operator<(const OP &a, const OP &b) { // next_permutation要用到小于号
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }
};

int n;
inline void workMin() { // 计算最少能赢多少次
    /* 初始化操作：输入操作序列 */
    vector<OP> op;
    vector<OP>::iterator it;
    op.push_back(OP(1, 1));
    op.push_back(OP(2, 2));
    op.push_back(OP(3, 3));
    op.push_back(OP(1, 3));
    op.push_back(OP(2, 1));
    op.push_back(OP(3, 2));

    int tmp, ans = 0x3f3f3f3f;
    do {
        E tmpA = a, tmpB = b; // 
        for (it = op.begin(); it != op.end(); ++it) {
            /* it->x就是循环到当前的结构体的x，it->y同理 */
            tmp = min(tmpA.ch[it->x], tmpB.ch[it->y]);
            tmpA.ch[it->x] -= tmp;
            tmpB.ch[it->y] -= tmp;
        }
        tmp = min(tmpA.ch[1], tmpB.ch[2]) + min(tmpA.ch[2], tmpB.ch[3]) +
              min(tmpA.ch[3], tmpB.ch[1]);
        ans = min(ans, tmp); // 计算最少赢的次数
    } while (next_permutation(op.begin(), op.end()));
    write(ans), putchar(' ');
}
inline void workMax() { // 计算最多能赢多少次
    int tmp = 0;
    tmp += min(a.ch[1], b.ch[2]) + min(a.ch[2], b.ch[3]) +
           min(a.ch[3], b.ch[1]);
    write(tmp);
}

inline void main() {
    read(n);
    read(a.ch[1]), read(a.ch[2]), read(a.ch[3]);
    read(b.ch[1]), read(b.ch[2]), read(b.ch[3]);
    workMin(), workMax();
}
```



---

## 作者：星空舞涵 (赞：0)

#### 这道题很显然是一个大模拟

对于最大值我们很好处理

```cpp
maxx=min(a[1],b[2])+min(a[2],b[3])+min(a[3],b[1]);
```
就是只要能赢就赢，不能赢就不用管。

对于最小值，不是很好处理

我们考虑贪心，能平就平，不能平就输，并且记录平局的次数


```cpp
	l[1]=min(a[1],b[1]);
	a[1]=a[1]-l[1];
	b[1]=b[1]-l[1];
	
	l[2]=min(a[2],b[2]);
	a[2]=a[2]-l[2];
	b[2]=b[2]-l[2];
	
	l[3]=min(a[3],b[3]);
	a[3]=a[3]-l[3];
	b[3]=b[3]-l[3];
	
	if(a[1]!=0)
	{
		ll=min(a[1],b[3]);
		a[1]=a[1]-ll;
		b[3]=b[3]-ll;
	}
	if(a[2]!=0)
	{
		ll=min(a[2],b[1]);
		a[2]=a[2]-ll;
		b[1]=b[1]-ll;
	}
	if(a[3]!=0)
	{
		ll=min(a[3],b[2]);
		a[3]=a[3]-ll;
		b[2]=b[2]-ll;
	}	
```
这样处理完后

可以把数据转换成四种情况

1.

	0 0 x

	x 0 0

2.

	0 x 0

	0 0 x
3.
	
    x 0 0

	0 x 0
    
 4.
	
   	0 0 0

	0 0 0

对于第四种情况，很显然最小值$minn=0$

对于前三种情况处理方法是一样的，我们以第一种情况为例

我们考虑一个替换操作

减少一次剪刀与剪刀平的操作

将这次操作改为剪刀与石头的对抗

现在就成了

	0  0  x
	
	x-1 1 0

然后变成

	0  0  x-1

	x-1 0 0
    
 我们最多替换的次数是$min(剪刀平的次数，x)$
 
 所以$minn=x-min(剪刀平的次数，x)$
 
 ```cpp
	if(a[1]!=0)
	{
		minn=a[1]-min(a[1],l[3]);
		cout<<minn<<" "<<maxx;
		return 0;
	}
	if(a[2]!=0)
	{
		minn=a[2]-min(l[1],a[2]);
		cout<<minn<<" "<<maxx;
		return 0;
	}
	if(a[3]!=0)
	{
		minn=a[3]-min(l[2],a[3]);
		cout<<minn<<" "<<maxx;
		return 0;
	}
```
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,maxx,minn,ll;
	long long a[4],b[4],c[4],l[4];
	cin>>n;
	cin>>a[1]>>a[2]>>a[3];
	cin>>b[1]>>b[2]>>b[3];
	maxx=min(a[1],b[2])+min(a[2],b[3])+min(a[3],b[1]);
	l[1]=min(a[1],b[1]);
	a[1]=a[1]-l[1];
	b[1]=b[1]-l[1];
	
	l[2]=min(a[2],b[2]);
	a[2]=a[2]-l[2];
	b[2]=b[2]-l[2];
	
	l[3]=min(a[3],b[3]);
	a[3]=a[3]-l[3];
	b[3]=b[3]-l[3];
	
	if(a[1]!=0)
	{
		ll=min(a[1],b[3]);
		a[1]=a[1]-ll;
		b[3]=b[3]-ll;
	}
	if(a[2]!=0)
	{
		ll=min(a[2],b[1]);
		a[2]=a[2]-ll;
		b[1]=b[1]-ll;
	}
	if(a[3]!=0)
	{
		ll=min(a[3],b[2]);
		a[3]=a[3]-ll;
		b[2]=b[2]-ll;
	}	
	
	if(a[1]!=0)
	{
		minn=a[1]-min(a[1],l[3]);
		cout<<minn<<" "<<maxx;
		return 0;
	}
	if(a[2]!=0)
	{
		minn=a[2]-min(l[1],a[2]);
		cout<<minn<<" "<<maxx;
		return 0;
	}
	if(a[3]!=0)
	{
		minn=a[3]-min(l[2],a[3]);
		cout<<minn<<" "<<maxx;
		return 0;
	}
	cout<<minn<<" "<<maxx;
} 
```


---

## 作者：Wuzhuoming (赞：0)

题目传送门：
Luogu:[CF1426E Rock, Paper, Scissors](https://www.luogu.com.cn/problem/CF1426F)  
Codeforces:[1426E](https://codeforces.ml/problemset/problem/1426/E)

[更好的阅读体验？](https://www.cnblogs.com/Wuzhuoming-sirenboke/p/13752145.html)

---
(打表找规律）  
相信大家都会玩石头剪刀布，规则都已经知道了，那就不再赘述（话说Codforces题面打了一长串，看完结果发现是在跟我们解释怎么玩石头剪刀布）~~浪费光阴~~

---
蒟蒻瞟了一眼其他的题解，不是dfs就是跑网络流，慢的跟个乌龟一样  
$O(1)$没商量   

---
最大值简单，就是让Alice能赢的尽量赢，于是有了$O(1)$的柿子：$ans2 = min(a1,b2) + min(a2,b3) + min(a3,b1)$

--- 
再说最小值：  
我们先来手模一下样例：  
样例1、2、3都太逊了  
直接看样例4、5：  
先看样例4：  
$ans1 = 22$  
$a1 = 479, a2 = 178, a3 = 29 $  
$b1 = 11 , b2 = 145, b3 = 530$  
经过观察发现$ans1 = a2 - b1 - b2$  
再看看样例5：  
$ans1 = 119$  
$a1 = 10$ , $a2 = 53$ , $a3 = 256$  
$b1 = 182$, $b2 = 103$, $b3 = 34$  
经过观察发现$ans1 = a3 - b2 - b3$    
当时就猜想：ans1是不是一个有规律可循的数呢？  
猜想完后立刻将第三种情况也推了出来：  
$ans1 = a1 - b3 - b1$  
于是我们就有了成功的$O(1)$算法  
最小值代码片段：
```text	
if(min(a1, b2) > min(a2, b3) && min(a1, b2) > min(a3, b1))
  ans1 = a1 - b1 - b3;
else
  if(min(a2, b3) > min(a1, b2) && min(a2, b3) > min(a3, b1))
    ans1 = a2 - b2 - b1;
  else
    if(min(a3, b1) > min(a1, b2) && min(a3, b1) > min(a2, b3))
      ans1 = a3 - b3 - b2;
    else
      ans1 = 0;
```

---
最后放出完整的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a1, a2, a3, b1, b2, b3, ans1, ans2;
int main() {
	scanf("%d", &n);
	scanf("%d%d%d", &a1, &a2, &a3);
	scanf("%d%d%d", &b1, &b2, &b3);
	if(min(a1, b2) > min(a2, b3) && min(a1, b2) > min(a3, b1))
		ans1 = a1 - b1 - b3;
	else
		if(min(a2, b3) > min(a1, b2) && min(a2, b3) > min(a3, b1))
			ans1 = a2 - b2 - b1;
		else
			if(min(a3, b1) > min(a1, b2) && min(a3, b1) > min(a2, b3))
				ans1 = a3 - b3 - b2;
			else
				ans1 = 0;
	ans2 = min(a1, b2) + min(a2, b3) + min(a3, b1);
	printf("%d %d", max(ans1, 0), ans2);
	return 0;
}
```
最后zc一下自己的blog：  
[博客园](https://www.cnblogs.com/Wuzhuoming-sirenboke/)  
[洛谷](https://www.luogu.com.cn/blog/Jouwu/)

---

## 作者：Chinese_zjc_ (赞：0)

求最大胜场,直接尽可能让其胜即可.

因此答案是 $\min(a_1,b_2)+\min(a_2,b_3)+\min(a_3,b_1)$ .

求最小胜场,我们用贪心的思想 $DFS$ 即可.

即先考虑输和平局,最后再迫不得已时使其胜场.

~~虽然直接 DFS 也可以.~~

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
//头文件已省略
#define int long long
#define double long double
using namespace std;
const double PI = acos(-1);
const double eps = 0.0000000001;
const int INF = 0x3fffffffffffffff;
int n, a[2][3], b[2][3], Min, Max, tmp;
bool allzero()
{
    for (int i = 0; i < 3; ++i)
    {
        if (b[0][i])
        {
            return false;
        }
    }
    return true;
}
void dfs(int now)
{
    if (allzero())
    {
        Min = min(now, Min);
    }
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 2; j <= 3; ++j)
        {
            if (b[0][i] && b[1][(i + j) % 3])
            {
                int tmp = min(b[0][i], b[1][(i + j) % 3]);
                b[0][i] -= tmp;
                b[1][(i + j) % 3] -= tmp;
                dfs(now);
                b[0][i] += tmp;
                b[1][(i + j) % 3] += tmp;
            }
        }
        if (b[0][i] && b[1][(i + 1) % 3])
        {
            int tmp = min(b[0][i], b[1][(i + 1) % 3]);
            b[0][i] -= tmp;
            b[1][(i + 1) % 3] -= tmp;
            dfs(now + tmp);
            b[0][i] += tmp;
            b[1][(i + 1) % 3] += tmp;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> a[i][j];
        }
    }
    memcpy(b, a, sizeof b);
    Min = n;
    dfs(0);
    memcpy(b, a, sizeof b);
    for (int i = 0; i < 3; ++i)
    {
        tmp = min(b[0][i], b[1][(i + 1) % 3]);
        Max += tmp;
        b[0][i] -= tmp;
        b[1][(i + 1) % 3] -= tmp;
    }
    cout << Min << ' ' << Max << endl;
    return 0;
}
```



---

## 作者：king_xbz (赞：0)

# 题意简述
给定场次和A，B的石头剪刀布次数，求A最多胜场和最少胜场。

# 思路分析
最大胜场就是尽可能地石头碰剪刀，剪刀碰布，布碰石头。

最小胜场就是尽可能输或者平局，避免石头碰剪刀，剪刀碰布，布碰石头

所以最大胜场数其实就是$min(a,y)+min(b,z)+min(c,x)$。最少胜场就是把输或者平的条件都减去就是了，但是处理不当会导致有些部分不是最优解。

# 代码实现
```cpp
int main()
{
	int n;
	cin>>n;
	int a,b,c;
	cin>>a>>b>>c;
	int x,y,z;
	cin>>x>>y>>z;
	int X=min(a,y),Y=min(b,z),Z=min(c,x);//尽量赢 
	int A=0,B=0,C=0,los=0; 
    if(x>a+b)//输或者平 
    A=x-a-b;
    if(y>b+c)
    B=y-b-c;
    if(z>=c+a) 
    C=z-c-a;
	los=A+B+C;
	cout<<los<<" "<<X+Y+Z;
	return 0;
}

---

## 作者：ZigZagKmp (赞：0)

本文同步于我的[cnblog](https://www.cnblogs.com/ZigZagKmp/p/13758252.html)

本场所有题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1426-solution)
## CF1426E
### 题意简述
`Alice`和`Bob`进行剪刀石头布的游戏，总共进行 $n$ 局。

`Alice`出石头 $a_1$ ​次，出剪刀 $a_2$ 次，出布 $a_3$ 次。

`Bob`出石头 $b_1$ 次，出剪刀 $b_2$ ​次，出布 $b_3$ ​次。

问`Alice`最少赢多少次，最多赢多少次。

$1\le n\le 10^9$。
### 算法标签
贪心 模拟
### 算法分析
最多赢多少次是比较简单的，尽可能让 $a_1$ 与 $b_2$ 搭配， $a_2$ 与 $b_3$ 搭配， $a_3$ 与 $b_1$ 搭配，答案为

$$\min\{a_1,b_2\}+\min\{a_2,b_3\}+\min\{a_3,b_1\}$$

最少赢得次数稍微麻烦一点，因为 $a_1$ 可能与 $b_1,b_3$ 搭配， $a_2$ 可能与 $b_1,b_2$ 搭配， $a_3$ 可能与 $b_2,b_3$ 搭配，答案并不确定。

因此我们考虑按照一定的顺序尽可能进行操作，最后取最小的答案。

时间复杂度 $O(6!)$ 。

~~当然本题也可以转化为线性规划问题用单纯形/网络流求解~~
### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
int a[4],b[4],c[4],d[4];
int ans1,ans2;
pair<int,int>tmp[10];
signed main(){
	read(n);
	read(a[1]),read(a[2]),read(a[3]);
	read(b[1]),read(b[2]),read(b[3]);
	ans2=min(a[1],b[2])+min(a[2],b[3])+min(a[3],b[1]);
	ans1=inf;
	tmp[1]=make_pair(1,1);
	tmp[2]=make_pair(1,3);
	tmp[3]=make_pair(2,1);
	tmp[4]=make_pair(2,2);
	tmp[5]=make_pair(3,2);
	tmp[6]=make_pair(3,3);
	do{
		int sm=0;
		c[1]=a[1];c[2]=a[2];c[3]=a[3];
		d[1]=b[1];d[2]=b[2];d[3]=b[3];
		for(int i=1;i<=6;++i){
			int tt=min(c[tmp[i].first],d[tmp[i].second]);
			c[tmp[i].first]-=tt;d[tmp[i].second]-=tt;
		}
		sm=min(c[1],d[2])+min(c[2],d[3])+min(c[3],d[1]);
		ans1=min(ans1,sm);
	}while(next_permutation(tmp+1,tmp+7));
	printf("%d %d\n",ans1,ans2);
	return 0;
}
```

---

