# [DMOI-R2] 梦境

## 题目背景

小 A 做噩梦了。

## 题目描述

小 A 的梦境可以看做有 $n$ 个点，$m$ 条边的无向图。小 A 在图上的点 $S$，有一个怪物在点 $B$，安全屋在点 $F$。

怪物正在追杀小 A，现在小 A 需要逃到安全屋。小 A 意识到这是在自己的梦境里，所以他在一定程度上操控了梦境。他把怪物的移动速度设置成了 $3$，但代价是自己的移动速度被设置成 $2$。

小 A 始终会沿着到 $F$ 的最短路走，如果有多条最短路，则小 A 会选择使得**经过点的编号所顺次构成序列的字典序最小**的那条最短路，因为他觉得这样走最不容易被怪物抓到。

而怪物在梦境中游荡，会随机向自身周围的点移动，且怪物已经访问过的点不会重复访问。

现在小 A 需要知道**在最坏情况下**他能否安全到达安全屋，或者何时被怪物抓住。

## 说明/提示

**关于最坏情况的解释**：怪物的走法可能有多种。也就是说，你需要同时考虑怪物的每种走法，只要怪物的某种最短路走法可以抓到小 A 时答案即为 `NO`。而最坏情况是指怪物的走法在所有走法中能够最快抓到（或接近）小 A 的情况。

另外本题没有 special judge，也就是说如果答案是整数，你需要严格输出整数答案，不带小数点。同时数据保证不存在小数位数超过两位的答案。

### 数据范围

本题采用捆绑测试。

$$
\def{\arraystretch}{1.5}
\begin{array}{c|c|c|c|c}\hline 
\textbf{~~Subtask~~}&\bm{~~n \le ~~}&\bm{~~~~m \le~~~~}& ~\textbf{~~特殊性质~~}~&\textbf{~~分值~~}\cr\hline 
0	&10			&20			&		&10\cr\hline 
1	&500		&1000		&		&10\cr\hline 
2	&800 		&2000		&		&10\cr\hline 
3	&2\times10^5&  			&\text{A+B}&15	\cr\hline 
4	&2\times10^5& 			&\text{A}&15	\cr\hline
5	&10^5		&2\times10^5&		&20\cr\hline
6	&2\times10^5&2\times10^5&		&20
\end{array}
$$

特殊性质 $\text{A}$：$m=n-1$。

特殊性质 $\text{B}$：对于给定的每个 $v_i$，满足 $v_i=u_i+1$。

对于 $100\%$ 的数据，保证 $S \ne B \ne F$ 且 $1 \le S,B,F \le n$，$1 \le w_i \le 10^3$，图连通且不存在重边。

### 特殊评分方式
本题开启子任务依赖，具体如下：
- 对于子任务 $i\in\{0,3\}$，您只需答对子任务 $i$ 即可获得子任务 $i$ 的分数。
- 对于子任务 $4$，您需要答对子任务 $3$ 才能获得子任务 $4$ 的分数。
- 对于子任务 $i\in\{1,2,5,6\}$，您需要答对子任务 $0$ 才能获得子任务 $i$ 的分数。

### 附件说明
对于赛时许多选手卡在了 sub3，此处提供一组 sub3 内的数据用于检查并改正代码。

## 样例 #1

### 输入

```
4 3 1 2 3
1 3 1
2 4 2
4 3 1```

### 输出

```
YES
1.5```

## 样例 #2

### 输入

```
4 3 1 2 3
1 3 2
2 4 2
4 3 1```

### 输出

```
NO
1```

# 题解

## 作者：ande (赞：5)

## 一.简述题意
### 1.简化题意
给定一个图，无向边，小 A 从 S 点出发，以 2 的速度运动在目标为 F 点的最小字典序最短路上运动，现有一怪物从点 Ｂ 出发，以 3 的速度随机游荡，但怪物无法经过重复的点。小 A 想要在不被抓到的情况下到达 F 点，请问在最坏情况下，小 A 能否逃脱，若能逃脱给出怪兽距离小 A 最近的距离，若不能则最早什么时候能抓到小 A。
### 2.一些需要注意的点
1.怪兽可以在 F 点抓住小 A。

**2.怪兽可以在边上抓到小 A。**

（赛时卡了半天瞄了一眼赛时答疑才看到/kk）

**3.正搜和倒搜的区别，文中做了详细解释。**


## 二.分析
### 1.Dijk最短路（记录路径）
题中提到小 A 会按照从 S 到 F 的最短路运动，那么显而易见怪兽只会在这条最短路径上抓住小 A，想要知道能否抓住小 A，只需要对比两者到达同一位置的时间即可，所以我们的第一步就是求出小 A 的路径及怪兽到达路径上每个点的最短时间。注意，此时要求出字典序最小的最短路径，要从 F 点起搜，到达 S 点结束。

此处为什么要倒搜，首先 Dijk 使用根堆优化排序，而堆的第二排序关键字是点的序号，故每次处理出的路径是**从终点到出发点的字典序最小最短路径，不是从起点到终点的字典序最小路径**，这里解释一下：

根堆处理时，是在有多种合法选择时，会选择最优的，而在选无可选的情况下直接采用，那么就会出现如下情况，即部分最优而非整体最优，下图中从 1 点跑最短路和在 5 点跑最短路路径不同：

![](https://cdn.luogu.com.cn/upload/image_hosting/upgqb4wb.png)

转移时， Dijk 每次找影响相同合法转移点中编号最小的，路径反过来之后相当于找能去的点中编号最小的，显然也是符合字典序最小的，所以这里要采取倒搜的方法。

然后处理出 B 点即怪兽出发点到 F 的单源最短路径，如何记录最短路径？这里联想一下链式前向星的存图方式，使用链表存图，当前点存储连接的下一个点的编号，那么以此类推：

定义一个 $P_i = j$，来表示到达 $ i $ 点的最短路径的上一个节点是 $ j $ 点
。具体实现在 Dijk 判断中加一行代码即可。具体如下：


```cpp
 	while ( !pq.empty() ) {
 	    P p = pq.top();
 	    pq.pop();
 	    int now = p.second;
 	    if ( mp[now] == 1 ) continue;
 	    mp[now] = 1;
 	    for ( int i = head[now]; i; i = edge[i].next ) {
 	       int to_ = edge[i].to, val = edge[i].val;
 	       if ( dis1[now] + val == dis1[to_] )
 	          pa[to_] = min( pa[to_], now );//字典序最小
 	       else if ( dis1[to_] > dis1[now] + val ) {
 	          dis1[to_] = dis1[now] + val;
 	          pa[to_] = now;//优先最短路径
 	          pq.push( { dis1[to_], to_ } );
      }
    }
  }
      }
```
调用的时候注意是需要顺序，所以我们采用队列的方式进行调用，如下：

```
 	int sign = s;
  	int x = dis1[s];
 	while ( N ) {
    	    dis1[sign] = x - dis1[sign];//倒搜要处理一下距离
    	    q.push( sign );
    	    sign = pa[sign];
     	    if ( sign == 0 ) break;
  }

```

此时怪兽到达路径的部分我们已经求完了，接下来在挨个遍历的过程中，对于每个点就要判断是下列三种相遇方式中的哪一种，然后按照情况来讨论：

#### 1.两者在同一时间到达同一点：

这种显而易见不再过多赘述。

#### 2.怪兽到达后，需要追上小 A，即追击问题：

这种也很好想，用两者相距距离除以相对速度 1 即可。

#### 3.怪兽到达后，需要与小 A ~~双向奔赴~~，即相遇问题：

两者相距距离除以相对速度 5，本质上和第二种情况相同。

然后对每个答案取 $\min$ 值，判断是否能被抓到将 $\min$ 值设为最劣情况即小 A 在安全屋被抓到的时间，最后进行特判即可。

## 三.坑点
到这里本文应该结束了的，可是毒瘤出题人卡了一下精度，要求有几位输出几位，不得有多余的 $0$ 或 $.$。
我的解决方式是使用双精度浮点型，并使用用 $\operatorname{cout}$ 函数输出，虽然慢但是具有很好的完美符合出题人要求的性质，即输出精确位数。~~然后被卡到 70 ptsTAT。~~

测了一下大样例发现问题在于 $\operatorname{cout}$ 默认**保留 6 位有效数字**，多余的位数用科学记数法表示，所以用一下黑科技:

```cpp
	cout.precision(15);
```

修改到 $15$ 位就好啦，溜！

```cpp

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define P pair< int, int >
const int N = 3e5 + 7;
int n, m, s, B, F;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while ( ch < '0' || ch > '9' ) {
    if ( ch == '-' ) f = -1;
    ch = getchar();
  }
  while ( ch >= '0' && ch <= '9' ) {
    x = ( x << 1 ) + ( x << 3 ) + ( ch - 48 );
    ch = getchar();
  }
  return x * f;
}
double min( double x, double y ) {
  if ( x < y ) return x;
  return y;
}
struct aa {
  int to, next, val;
} edge[N * 2];
int head[N * 2], t = 1;
void add( int now, int to, int val ) {
  edge[t].to = to;
  edge[t].val = val;
  edge[t].next = head[now];
  head[now] = t++;
}
int dis1[N], dis2[N];
int pa[N];
priority_queue< P, vector< P >, greater< P > > pq;
int mp[N];
void dijk( int s1, int s2 ) {
  memset( dis1, 0x3f, sizeof( dis1 ) );
  memset( dis2, 0x3f, sizeof( dis2 ) );
  dis1[s1] = 0;
  pa[s1] = 0;
  pq.push( { dis1[s1], s1 } );
  while ( !pq.empty() ) {
    P p = pq.top();
    pq.pop();
    int now = p.second;
    if ( mp[now] == 1 ) continue;
    mp[now] = 1;
    for ( int i = head[now]; i; i = edge[i].next ) {
      int to_ = edge[i].to, val = edge[i].val;
      if ( dis1[now] + val == dis1[to_] )
        pa[to_] = min( pa[to_], now );
      else if ( dis1[to_] > dis1[now] + val ) {
        dis1[to_] = dis1[now] + val;
        pa[to_] = now;
        pq.push( { dis1[to_], to_ } );
      }
    }
  }
  while ( !pq.empty() )
    pq.pop();
  pq.push( { 0, s2 } );
  for ( int i = 1; i <= n; i++ )
    mp[i] = 0;
  dis2[s2] = 0;
  while ( !pq.empty() ) {
    P p = pq.top();
    pq.pop();
    int now = p.second;
    if ( mp[now] == 1 ) continue;
    mp[now] = 1;
    for ( int i = head[now]; i; i = edge[i].next ) {
      int to_ = edge[i].to, val = edge[i].val;
      if ( dis2[to_] > dis2[now] + val ) {
        dis2[to_] = dis2[now] + val;
        pq.push( { dis2[to_], to_ } );
      }
    }
  }
}
queue< int > q;
signed main() {
  cout.precision( 15 );
  // freopen("data.in","r",stdin);
  // freopen("data.out","w",stdout);
  n = read(), m = read(), s = read(), B = read(), F = read();
  for ( int i = 1; i <= m; i++ ) {
    int x = read(), y = read(), z = read();
    add( x, y, z );
    add( y, x, z );
  }

  dijk( F, B );

  int sign = s;
  double time = dis1[s] / 2.0;
  int x = dis1[s];
  while ( N ) {
    dis1[sign] = x - dis1[sign];
    q.push( sign );
    // cout << dis1[sign] << " ";
    sign = pa[sign];
    if ( sign == 0 ) break;
  }
  while ( !q.empty() ) {
    int now = q.front();
    // cout << now << " ";
    q.pop();
    if ( dis1[now] / 2.0 - dis2[now] / 3.0 >= 0 ) {
      double x = dis1[now] - ( dis2[now] * 2.0 / 3.0 );
      x /= 5.0;
      time = min( time, dis2[now] / 3.0 + x );
    }
    else {
      double x = ( dis2[now] / 3.0 * 2.0 - dis1[now] );
      time = min( time, dis2[now] / 3.0 + x );
    }
  }
  if ( time == dis1[F] / 2.0 && dis1[F] / 2.0 != dis2[F] / 3.0 ) {
    double ans = dis2[F] - ( dis1[F] * 3.0 / 2.0 );
    cout << "YES";
    puts( "" );
    cout << ans;
  }
  else {
    printf( "NO\n" );
    cout << time;
  }

  return 0;
}

```


---

## 作者：Bulyly (赞：5)

### 赛后感言
小数处理应该是这个题最难的一个点了，在  sub3 里体现的非常明显。其次就是子任务也令人苦不堪言，不过还好最后过了。下面为赛时思路，如有疑问欢迎提出。

### 解析

这道题本身并不难，我们可以分情况来考虑。

- 由题可知，首先我们需要跑两次最短路，分别求出小 A 和怪兽到每个点的最短路径，同时记录小 A 应该走的点。

- 考虑抓不到的情况，显然怪兽不能在任一点先于小 A，则需满足小 A 到最短路径上任意的点的时间都严格小于怪兽到达的时间。最后用怪兽离终点的最短距离减去小 A 到达时的已经走了的路程可得出怪物到安全屋的距离。

- 接下来是能抓到的情况，若能抓到小 A，相比较于上，怪兽显然会在一个点不慢于小 A 到达，我们设这个点为 $x$。接下来考虑被抓住的时间，首先怪物一定会在 $x$ 时或之前抓住，那就一定是在通往 $x$ 的路途中。接下分为两种情况，怪兽可以在 $x$ 点之前的点开始追小 A，也可以在到达 $x$ 然后与小 A 相遇。即转化为相遇和追及问题。

- 关于 double 的精度控制可以用 ```cout.precision()``` 来处理，注意 double 的精度为 $15$ 到 $16$ 位，精度不要取得过高。[代码](https://www.luogu.com.cn/paste/t65lnsyl)。

Update on 1.12：纠正了求字典序最小的错误做法。这里简述一下问题，顺推最短路保证的是倒数第二个点，倒数第三个点最小的路径，与要求相反，故需要倒推最短路，注意倒推最短路后的距离处理。这是改正后的[代码](https://www.luogu.com.cn/paste/cq6fqjg9)。



 

---

## 作者：Register_flicker (赞：2)

### 题外话
比赛时本蒟蒻使用`cout`输出因精度问题痛失 30 分，~~114514~~。
## 思路
这题小 A 是在最坏情况下，所以可以看成怪物从 $F$ 点到每个点的路径都是最短路，最短路距离存在 $z2$，小 A 也需要找到最短路，路径可以在每个点用一个数组 $syg$ 存那个点的上一个点，**因为要字典序最小，所以从 $F$ 点开始搜**，如果距离相等取字典序最小的那个，值存在 $z1$。最后正着从 $S$ 点搜一遍，存在 $z3$。先用 dijkstra 算出小 A 和怪物的最短路。

算出最短路后用 $syg$ 推出小 A 走的路径，用数组 $l$ 存。然后**从起点到终点**每个点计算小 A 会不会被怪物抓到。

当小 A 会被怪物抓到时，需要计算时间，这时需要分两种情况，时间取最小值。

* 如果在路径的第 $i$ 个点前抓到时，怪物可能从 $l_i$ 点往 $l_{i-1}$ 点抓，这种~~偷袭~~情况可以看成相遇问题，所以时间是 $(z3_{l_{i}}+z2_{l_{i}}) \div 5$ 。
* 另一种情况是怪物从 $l_{i-1}$ 点往 $l_i$ 追，看成追及，时间是 $(z3_{l_{i-1}}+z2_{l_{i-1}}) \div 1$。

总的结果就是 $\min((z3_{l_{i}}+z2_{l_{i}}) \div 5 , (z3_{l_{i-1}}+z2_{l_{i-1}}) \div 1)$ 。

如果不会抓到，用小 A 到的时间怪物走的路程减去怪物到 $F$ 点的路程即可。

最后输出还有一个问题，如果用`cout`只会输出 6 位，然鹅subtask3 的数据输出大于 6 位，可以在前面加上一行`cout.precision(15);`。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,m,s,b,f,z1[444444],z2[444444],z3[444444],jl1[444444],jl2[444444],jl3[444444],syg1[444444],now,o,ks[444444],lj[444444],ljcd,x;
const int inf=0x3f3f3f3f;
struct node
{
	int u,v,w;
};
struct d
{
	int bh,zz;
	bool operator<(const d &a)const
	{
		return zz>a.zz;
	}
};
node bian[444444];
priority_queue<d> pq1,pq2,pq3;
d noww,abc;
bool cmp(node x,node y)
{
	return x.u<y.u;
}
int main()
{
	cout.precision(15);
	cin>>n>>m>>s>>b>>f;
	for(int i=1;i<=m;i++)
	{
		cin>>bian[i*2-1].u>>bian[i*2-1].v>>bian[i*2-1].w;//无向图，存两个方向
		bian[i*2].u=bian[i*2-1].v;
		bian[i*2].v=bian[i*2-1].u;
		bian[i*2].w=bian[i*2-1].w;
	}
	sort(bian+1,bian+1+m*2,cmp);
	o=0;
	for(int i=1;i<=m*2;i++)
	{
		if(bian[i].u>o)
		{
			o++;
			ks[o]=i;
		}
	}
	ks[n+1]=m*2+1;
	for(int i=1;i<=n;i++)
	{
		z1[i]=inf;
		z2[i]=inf;
		z3[i]=inf;
	}
	z1[f]=0;
	z2[b]=0;
	z3[s]=0;
	abc.bh=f;//从F开始搜
	abc.zz=0;
	pq1.push(abc);
	while(!pq1.empty())//dijkstra
	{
		noww=pq1.top();
		now=noww.bh;
		pq1.pop();
		if(jl1[now]==1)
		{
			continue;
		}
		jl1[now]=1;
		for(int j=ks[now];j<ks[now+1];j++)
		{
			if(jl1[bian[j].v]==1)
			{
				if(bian[j].w+z1[now]==z1[bian[j].v]&&now<syg1[bian[j].v])
				{
					syg1[bian[j].v]=now;
				}
			}
			else
			{
				if(bian[j].w+z1[now]<z1[bian[j].v])
				{
					z1[bian[j].v]=bian[j].w+z1[now];
					syg1[bian[j].v]=now;
					abc.bh=bian[j].v;
					abc.zz=z1[bian[j].v];
					pq1.push(abc);
				}
				else if(bian[j].w+z1[now]==z1[bian[j].v])
				{
					if(now<syg1[bian[j].v])
					{
						syg1[bian[j].v]=now;
					}
				}
			}
		}
	}
	ljcd=1;
	lj[1]=s;
	x=s;
	while(x!=f)//存路径
	{
		ljcd++;
		x=syg1[x];
		lj[ljcd]=x;
	}
	abc.bh=b;
	abc.zz=0;
	pq2.push(abc);
	while(!pq2.empty())
	{
		noww=pq2.top();
		now=noww.bh;
		pq2.pop();
		if(jl2[now]==1)
		{
			continue;
		}
		jl2[now]=1;
		for(int j=ks[now];j<ks[now+1];j++)
		{
			if(jl2[bian[j].v]==0&&bian[j].w+z2[now]<z2[bian[j].v])
			{
				z2[bian[j].v]=bian[j].w+z2[now];
				abc.bh=bian[j].v;
				abc.zz=z2[bian[j].v];
				pq2.push(abc);
			}
		}
	}
	abc.bh=s;
	abc.zz=0;
	pq3.push(abc);
	while(!pq3.empty())
	{
		noww=pq3.top();
		now=noww.bh;
		pq3.pop();
		if(jl3[now]==1)
		{
			continue;
		}
		jl3[now]=1;
		for(int j=ks[now];j<ks[now+1];j++)
		{
			if(jl3[bian[j].v]==0&&bian[j].w+z3[now]<z3[bian[j].v])
			{
				z3[bian[j].v]=bian[j].w+z3[now];
				abc.bh=bian[j].v;
				abc.zz=z3[bian[j].v];
				pq3.push(abc);
			}
		}
	}
	for(int i=2;i<=ljcd;i++)//S点不用搜，因为S不等于B
	{
		if(z3[lj[i]]*3>=z2[lj[i]]*2)
		{
			cout<<"NO"<<endl<<min((z3[lj[i]]+z2[lj[i]])/5.0,(z2[lj[i-1]]-z3[lj[i-1]])/1.0);
			return 0;
		}
	}
	cout<<"YES"<<endl<<z2[f]-z3[f]/2.0*3.0;
    //cjldAKIOI
}
```

---

## 作者：olegekei (赞：2)

### Solution 1
爆搜，因为每个点怪物最多只会访问一次，所以暴力枚举怪物的游荡路线，期望通过 $\text{subtask}1$。
### Solution 2
对于特殊性质 $\text{B}$，给定图为一条链，两种情况：
- 在终点的异侧：
	
	此时怪物只有朝小 A 的方向走才有机会抓到小 A，相遇问题，判一下谁先到 $F$，之后转换成在终点同侧处理。

- 在终点的同侧：

	仍需怪物朝小 A 的方向游荡，然后再细分为两种情况：

	如果怪物距离点 $F$ 更近则是相遇问题，答案为点 $B$ 到点 $S$ 的距离除以 $5$。

	而如果小 A 距离点 $F$ 更近则是追击问题，$\text{小 A 到怪物的距离} \times 2 \le \text{小 A 到终点的距离}$ 则为 `NO`，否则为 `YES`。

第二行答案也不难计算，期望通过$\text{substask}3$。
### Solution 3
对于特殊性质 $\text{A}$，给定图为一棵树，不难想象这棵树的有贡献节点只有小 A 到 $F$ 最短路上的每个点与怪物到「怪物与小 A 的最近公共祖先」最短路上的每一个点，其他点是没有贡献的（如果怪物走了其他点就不可能再捉到小 A 了），所以我们可以直接忽略其他点。

首先排除怪物是小 A 的一个祖先，因为这样可以直接当作链来处理。

除去上面的情况，考虑怪物抓小 A 时会先到达「怪物与小 A 的最近公共祖先」，之后小 A 有两种位置可能：在 $S$ 与公共祖先之间，在公共祖先与 $F$ 之间，此时可以当作链处理，前者相遇问题，后者追击问题，容易解决，期望通过 $\text{subtask}3 \sim 4$。
### Solution 4 
再去细想一下，怪物想要尽快抓到小 A 的话，就需要按照当前怪物的位置到小 A 的最短路路径去走（也就是实时最短路），直到怪物走到小 A 之前走过的路径后，就可以看成怪物严格按照小 A 走过的路径去追赶，（因为小 A 走过的路径是最短路，怪物要沿着到小 A 的最短路去走）。

所以可以通过 Floyd 跑出全源最短路，同时在小 A 到 $F$ 的路上暴力枚举路径上的每一个中间点，直到怪物走到小 A 走过的路上（或可能直接抓到小 A），然后就可以按照链来处理了，期望通过数据点 $\text{subtask}1 \sim 3$。不过如果细节处理过于麻烦的话可能会退化到 $\text{subtask}1 \sim 2$。
### Solution 5
考虑小 A 的移动路线是固定的，在 Solution 4 的基础上进一步思考，发现怪物在前半段的移动路线可以看成是某一时刻小 A 所处的位置为终点的最短路（相当于怪物学会了预判）。

那么也就是说我们并不需要让怪物走实时最短路，只需要暴力枚举小 A 移动路线上的每个点作为怪物的目标点，当怪物走到目标点之后变成链的情况处理即可，最后对所有情况得到的答案取最小值即可，期望通过所有测试点。
### 后记
因为感觉这题太简单所以留了个小数处理的部分。对于这部分我们可以在读入的时候将边权乘二，因为追击问题的速度是 $1$，相遇问题的速度是 $5$，所以乘 $2$ 之后只会出现 $0.2$、$0.4$、$0.6$、$0.8$ 的小数情况，可以直接对 $5$ 取模分类讨论。

而得到答案之后可能需要把 $2$ 除回来，只会出现 $0.5$ 的小数情况，同样可以取模讨论。

直接转换成 double 用 printf 保留小数位输出可能会出现 $x.0$ 的情况（不过可以直接判一下有没有小数位），cout 不加其他限制输出 double 时是自动保留 6 位有效数字的（可能出现精度损失）。

---
除此之外对于小 A 移动路径问题需要找字典序最小的最短路，注意不要从点 $S$ 跑最短路找小 A 最短路上每个点的字典序最小的前驱（正确性错误），而是要从点 $F$ 跑最短路找每个点字典序最小的后继（找的时候注意要确定是最短路上的点）。

前者可以举例子轻易卡掉：

从点 $1$ 到点 $4$ 分别有两条最短路径 $1 \rightarrow 2 \rightarrow 3 \rightarrow 4$ 和 $1 \rightarrow 3 \rightarrow 4$，若按照前者方法去跑的话对于点 $3$ 的前驱为 $1$，会导致小 A 的移动路径变为错误的 $1,3,4$，而真正的字典序最小应该为 $1,2,3,4$。

---

## 作者：_shy (赞：2)

## 难点
1. 如何得到字典序最小的最短路径。

2. 如何找到最坏情况。

3. 如何正确输出答案。

## 解决
### 第一个难点
我们可以以 $F$ 为起点，以 $S$ 为终点跑堆优化的 dijkstra，用 $path[v]$ 表示 $v$ 的最小前驱（前驱即 $v$ 从哪一个点转移过来），并在 dijkstra 的过程中更新，更新方式如下：
```cpp
// tp == 0 表示的是在进行找路径的dijkstra，不用在意。
if (dis[tp][v] > dis[tp][u] + w) 
{
	dis[tp][v] = dis[tp][u] + w;
   q.push ((node) {v, dis[tp][v]});
   if (tp == 0) path[v] = u; // 最短路得到更新，path[v]也要更新。
 }           
else if (tp == 0 && dis[tp][v] == dis[tp][u] + w) 
   path[v] = min (path[v], u); // 如果u更小，则更新。
```

正确性：因为是“倒着跑”dijkstra，故 $S$ 的最小前驱，实际上就是，小 A 从 $S$ 出发踏上的使最短路径字典序最小的第一个点，依次类推得到的便是最小字典序的最短路径。

下面通过举反例的方式证明“正着跑”是错误的，看下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/zbp3vpja.png)

设 $S$ 为 $1$，$F$ 为 $5$，如果“正着跑”按同样的方法记录前驱数组，得到的逃离路线是：$1\rightarrow4\rightarrow2\rightarrow5$；而正确答案是：$1\rightarrow3\rightarrow5$。故“正着跑”错误。
### 第二个难点
解决办法：

我们先从最简单的情况入手，即怪兽在小 A 的逃离路线上，若小 A 比怪兽离终点远，则是相遇问题；若小 A 比怪兽离终点近，则是追击问题。

然后我们复杂化情况，即怪兽不在小 A 的逃离路线上，则怪兽肯定需要走到小 A 的逃离路线上的某一个点，那么为了更可能地追上小 A，怪兽肯定走最短路径过去（dijkstra 又来啦！），走到小 A 的逃离路线某一个点后，就转化成较简单的情况了。但这里有两个问题：一个是**怪兽到不了某个点**，另一个是**怪兽还没到逃离路线上小 A 就逃离了**，需要特判一下。
### 第三个难点
输出问题，因为题目说了小数位不会超过两位，所以我们可以暴力判断，如下：
```cpp
long long x = ans * 100;
if (x % 100 == 0) printf("%lld", x / 100);
else if (x % 10 == 0) printf("%.1lf", 0.01 * x);
else printf("%.2lf", 0.01 * x);
```
于是我们就美美地交上去了，但发现每个 subtask 都有错的，怎么回事呢？

因为**精度损失了**！比如说，虽然我们要的是 $6.0$，但在 double 类型的变量中存储的是 $5.99999$，这就使得输出的由 $6$ 变成了 $5$。于是我们需要**补足精度并在此基础上不改变最后的答案**。最简单的方法就是加上一个数补足精度，显然 $0.001$ 符合要求，具体操作如以下代码：
```cpp
const double eps = 1e-3
long long x = (ans + eps) * 100;
if (x % 100 == 0) printf("%lld", x / 100);
else if (x % 10 == 0) printf("%.1lf", 0.01 * x);
else printf("%.2lf", 0.01 * x);
```
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
int n, m, s, b, f;
int head[maxn], cnt;
double ians = 2147483647, ans = 2147483647;
const double eps = 1e-3;
struct edge 
{
	int v, w, next;
} e[maxn << 1];
void add (int u, int v, int w) 
{
	e[++ cnt] = (edge) {v, w, head[u]};
	head[u] = cnt;
} 
struct node 
{
	int pos, dist;
	bool operator < (node a) const 
	{
		return a.dist < dist;
	}
};
priority_queue <node> q, emptyi;
int dis[2][maxn], vis[maxn], path[maxn];
void dijkstra (int si, int tp) 
{
	memset (vis, 0, sizeof (vis));
	memset (dis[tp], 0x7f7f7f7f, sizeof (dis[tp]));
	q = emptyi;
	dis[tp][si] = 0;
	q.push ((node) {si, 0}); 
	while (!q.empty ()) 
	{
		int u = q.top ().pos;
		q.pop ();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].next) 
		{
			int v = e[i].v, w = e[i].w;
			if (vis[v]) continue;
			if (dis[tp][v] > dis[tp][u] + w) 
			{
				dis[tp][v] = dis[tp][u] + w;
				q.push ((node) {v, dis[tp][v]});
				if (tp == 0)
					path[v] = u;
			}
			else if (tp == 0 && dis[tp][v] == dis[tp][u] + w) 
				path[v] = min (path[v], u);
		} 
	}
}
int main ()
{
	scanf ("%d %d %d %d %d", &n, &m, &s, &b, &f);
	for (int i = 1; i <= m; i++) 
	{
		int u, v, w;
		scanf ("%d %d %d", &u, &v, &w);
		add (u, v, w), add (v, u, w);
	}
	dijkstra (f, 0);
	dijkstra (b, 1);
	int v = s, flag = 0;
	while (v != 0) 
	{
		if (dis[1][v] == 0x7f7f7f7f) continue; 
		double ansi = dis[1][v] / 3.0;
		if (ansi == (dis[0][s] - dis[0][v]) / 2.0) 
			flag = 1, ans = min (ansi, ans);
		else if (ansi * 2.0 < dis[0][s] - dis[0][v]) 
		{
			double ansii = (dis[0][s] - dis[0][v] - ansi * 2.0) / 5.0;
			flag = 1, ans = min (ans, ansi + ansii);
		}
		else 
		{
			if (ansi > dis[0][s] / 2.0 && flag == 0) 
				ians = min (ians, dis[0][v] + 3.0 * (ansi - dis[0][s] / 2.0));
			else 
			{
				double ansii = (2.0 * ansi + dis[0][v] - dis[0][s]);
				if (ansii <= (dis[0][s] - 2 * ansi) / 2.0) 
					flag = 1, ans = min (ans, ansii + ansi);
				else if (ansii > (dis[0][s] - 2 * ansi) / 2.0 && flag == 0)
					ians = min (ians, dis[0][v] - 3.0 * (dis[0][s] - 2 * ansi) / 2.0);
			} 
		}
		v = path[v];
	}
	if (!flag) printf ("YES\n"), ans = ians;
	else printf ("NO\n");
	long long x = (ans + eps) * 100;
   	if (x % 100 == 0) printf("%lld", x / 100);
   	else if (x % 10 == 0) printf("%.1lf", 0.01 * x);
   	else printf("%.2lf", 0.01 * x);
	return 0;
}

```

呼，这个题就做完了!

---

## 作者：OneStar (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8914)。

大体思路: 用 Dijkstra 找到小 A 选择的最短路径，然后遍历该链寻找怪物能抓住小 A 的最小时间。该遍历过程可以用二分优化。

首先，要找到最小字典序的最短路径，想到开一个链表，存这个点从被谁松弛 ( 代码中 last 数组 )。
```cpp
void dijkstra(){
	//...
	while(!q.empty()){
		int u=q.top().u;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=h[u];i;i=e[i].next){
			int v=e[i].to;
			if(dis[u]+e[i].w==dis[v]) last[v]=min(last[v],u);//字典序最小
			else if(dis[u]+e[i].w<dis[v]){
				dis[v]=dis[u]+e[i].w;
				last[v]=u;//v被u松弛
				q.push(Node{v,dis[v]});
			}
		}
	}
}
```
但是当我们对 $S$ 点求单源最短路时会发现，这样的算法对下面这张图是错误的。

![图1](https://cdn.luogu.com.cn/upload/image_hosting/1kl7rc32.png)

对于这张图，$last_7=5$ ，而 $1-3-5-7$ 显然不是字典序最小的最短路径，因为我们所求的其实是反过来的最小字典序的最短路径。

解决办法很简单，我们对 $F$ 而不是 $S$ 求单源最短路。

得到小 A 走的路径后我们就可以在这条链上寻找怪物抓到小 A 的最小时间。具体做法是对 $B$ 求单源最短路后比对怪物到达每点的时间与小 A 到达每点的时间，找到**最早的怪物到达时间小于等于小 A 到达时间的点 $x$**，如果小 A 与怪物到达 $x$ 点的时间相同，那么他们将在 $x$ 相遇。如果不相同，他们就从 $x$ 两侧的边上相遇，此题也就做完了。

但我今天想要重点分析的，是这个过程如何用二分优化 ~~( 然鹅由于瓶颈在 Dijkstra, 时间复杂度并没有太大的影响~~，只是呈现一种思路供大家交流 )。

众所周知，当数列单调时我们才能用二分。**我们想要通过二分找到链上最早的怪物到达时间小于等于小 A 到达时间的点，其实就是要证明怪物与小 A 到达这条链上各点的时间差单调**。

我们设小 A 走的链为 $S-...-i-...-j-...-F$。

若怪物**经过**路径 $i-j$ **最快**到达 $j$ 点，由于怪物的速度比小 A 快，所以此时怪物与小 A 到达 $j$ 的时间差一定大于怪物与小 A 到达 $i$ 点的时间差；若怪物**最快**到达 $j$ 点的路径**不经过**路径 $i-j$，则怪物最快到达 $j$ 点所需的时间一定小于怪物经过路径 $i-j$ 到达 $j$ 点所需的时间。此时怪物与小 A 到达 $j$ 的时间差还是大于怪物与小 A 到达 $j$ 点的时间差。

设小 A 走到点 $i$ 的时间为 $T_{A,i}$，怪物走到点 $i$ 的时间为 $T_{B,i}$，$i$ 点到 $j$ 点的距离为 $dis_{i,j}$，形式化的：

$$T_{A,j}=T_{A,i}+\frac{dis_{i,j}}{2}$$
$$T_{B,j}\leq T_{B,i}+\frac{dis_{i,j}}{3}$$
整理有：
$$T_{A,j}-T_{B,j}\geq T_{A,i}-T_{B,i}+\frac{dis_{i,j}}{6}$$
由于 $dis_{i,j}>0$，所以：
$$T_{A,j}-T_{B,j}> T_{A,i}-T_{B,i}$$
至此，我们证明了怪物与小 A 到达这条链上各点的时间差单调递增。

通过二分找到最早的怪物到达时间小于等于小 A 到达时间的前一个点 $x$ 后，我们发现当两者同时到达 $x$ 时，答案就是到达 $x$ 的时间；而当怪物到达 $x$ 的时间大于小 $A$ 到达 $x$ 的时间时，他俩会在 $x$ 后的边上相遇，我们设这条边为 $x-y$。

显然，怪物要么从 $x$ 追上小 A 要么从 $y$ 与小 A 相遇，只需要分类讨论这两种情况就可以了。

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define db double
#define N 200010
using namespace std;
struct graph{int to,next,w;}e[N<<1];
struct Node{int u,w;};
struct Node1{db t;int u;}path[N];
bool operator <(Node x,Node y){return x.w>y.w;}
int n,m,s,b,f,tot,cnt,h[N],vis[N],last[N],dis[N];
priority_queue<Node> q;
void Add(int u,int v,int w){
	e[++tot].to=v;
	e[tot].w=w;
	e[tot].next=h[u];
	h[u]=tot;
}
void dijA(){
	memset(dis,0x3f,sizeof(dis));
	memset(last,0x3f,sizeof(last));
	last[f]=0;
	dis[f]=0;
	q.push(Node{f,0});
	while(!q.empty()){
		int u=q.top().u;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=h[u];i;i=e[i].next){
			int v=e[i].to;
			if(dis[u]+e[i].w==dis[v]) last[v]=min(last[v],u);
			else if(dis[u]+e[i].w<dis[v]){
				dis[v]=dis[u]+e[i].w;
				last[v]=u;
				q.push(Node{v,dis[v]});
			}
		}
	}
}
void dijB(){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[b]=0;
	q.push(Node{b,0});
	while(!q.empty()){
		int u=q.top().u;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=h[u];i;i=e[i].next){
			int v=e[i].to;
			if(dis[u]+e[i].w<dis[v]){
				dis[v]=dis[u]+e[i].w;
				q.push(Node{v,dis[v]});
			}
		}
	}
}
db Find(int l,int r){ 
	while(l<r){
		int mid=(l+r+1)>>1;
		if(path[mid].t*3>dis[path[mid].u]) r=mid-1;
		else l=mid;
	}
	int x=l; 
	if(path[x].t*3==dis[path[x].u]) return path[x].t;//怪物与小A在点x相遇
	if(path[cnt].t*3<dis[f]) return 0; //怪物不会遇到小A
	return min(/*怪物从x追上小A*/dis[path[x].u]-path[x].t*2,/*怪物从y与小A相遇*/(path[x+1].t*2+dis[path[x+1].u])/5);
}
int main(){
	cout.precision(15);//输出精度 
	scanf("%d%d%d%d%d",&n,&m,&s,&b,&f);
	for(int x,y,z,i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		Add(x,y,z);
		Add(y,x,z);
	}
	dijA();
	for(int i=s;i;i=last[i]) path[++cnt]=Node1{(dis[s]-dis[i])/2.0,i};//由于求的是F的单源最短路，所以要把距离反过来 
	dijB();
	db ans=Find(1,cnt);
	if(!ans){
		printf("YES\n");
		ans=dis[f]-path[cnt].t*3;//怪物没有追上小A，输出怪物距小A的距离 
	}else printf("NO\n");
	cout<<ans;
	return 0;
}
```
语言较为抽象，请大家谅解Orz。

---

