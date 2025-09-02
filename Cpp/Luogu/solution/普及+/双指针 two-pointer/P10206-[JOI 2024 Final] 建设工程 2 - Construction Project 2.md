# [JOI 2024 Final] 建设工程 2 / Construction Project 2

## 题目描述

JOI 国有 $N$ 个火车站，编号从 $1$ 到 $N$。另外，JOI 国有 $M$ 条双向铁路线，编号从 $1$ 到 $M$。铁路线 $i\ (1 \leq i \leq M)$ 连接了火车站 $A_{i}$ 和火车站 $B_{i}$，从一个站到另一个站需要花费 $C_i$ 分钟。

你是 JOI 国的部长，决定按照以下方式新建一条铁路线：

选择两个整数 $u, v\ (1 \leq u<v \leq N)$，在火车站 $u$ 和火车站 $v$ 之间建设一条双向铁路线，从一个站到另一个站需要花费 $L$ 分钟。注意，即使已经有一条连接火车站 $u$ 和火车站 $v$ 的铁路线也可以建设。

如果你建设这条铁路线后，可以花费不超过 $K$ 分钟从火车站 $S$ 到火车站 $T$，国王就会高兴。我们不考虑换乘时间和等待时间。

你有 $\frac{N(N-1)}{2}$ 种选择两个整数 $u, v$ 的方法，你想知道其中有多少种方法会让国王高兴。

给定火车站和铁路线以及国王的要求的信息，编写一个程序，求出其中有多少种选择整数的方法会让国王高兴。

## 说明/提示

对于所有输入数据，满足：

- $2 \leq N \leq 2\times 10^5$
- $1 \leq M \leq 2\times 10^5$
- $1 \leq S<T \leq N$
- $1 \leq L \leq 10^{9}$
- $1 \leq K \leq 10^{15}$
- $1 \leq A_{i}<B_{i} \leq N\ (1 \leq i \leq M)$
- $(A_{i}, B_{i}) \neq (A_{j}, B_{j})\ (1 \leq i<j \leq M)$
- $1 \leq C_{i} \leq 10^{9}\ (1 \leq i \leq M)$

详细子任务附加限制及分值如下表所示。

|子任务|	附加限制|	分值|
|:-:|:-:|:-:|
|1|	$L=1, K=2, C_{i}=1\ (1 \leq i \leq M)$|	8
|2|	$N \leq 50, M \leq 50$|	16
|3|	$N \leq 3000, M \leq 3000$|	29
|4|	无附加限制|	47

## 样例 #1

### 输入

```
7 8
6 7 1 2
1 2 1
1 6 1
2 3 1
2 4 1
3 5 1
3 7 1
4 5 1
5 6 1```

### 输出

```
4```

## 样例 #2

### 输入

```
3 2
1 3 1 2
1 2 1
2 3 1```

### 输出

```
3```

## 样例 #3

### 输入

```
6 4
2 5 1000000000 1
1 2 1000000000
2 3 1000000000
2 4 1000000000
5 6 1000000000```

### 输出

```
0```

## 样例 #4

### 输入

```
18 21
4 8 678730772 3000000062
5 13 805281073
8 17 80983648
3 8 996533440
10 16 514277428
2 5 57914340
6 11 966149890
8 12 532734310
2 9 188599710
2 3 966306014
12 16 656457780
16 18 662633078
1 15 698078877
2 8 665665772
2 6 652261981
14 15 712798281
7 13 571169114
13 14 860543313
6 7 454251187
9 14 293590683
6 14 959532841
3 11 591245645```

### 输出

```
16```

# 题解

## 作者：Perta (赞：21)

在不新建铁路线的图上跑最短路，定义此时 $x,y$ 间的最短路长为 $dis(x,y)$。

特判掉 $dis(S,T)\leq K$ 的情况（所有方案均合法），此时我们要求的就是满足 $dis(S,u)+L+dis(T,v)\leq K$ 的无序二元组 $(u,v)$ 数量。

令 $a_i=dis(T,i)$，将 $a$ 数组从小到大排序。枚举 $u$，则满足条件的 $v$ 数量有 $p$ 个，其中 $p$ 为最大的满足 $dis(S,u)\leq K-L-a_p$ 的数（不存在则为 $0$），直接 $\rm upper\_bound$ 即可。

答案为 $\sum p$，时间复杂度 $O(m\log m+n\log n)$。

[Code](https://www.luogu.com.cn/paste/lbu4o5gp)

***

关于上述解法你或许会有个小小的疑惑：若一个二元组 $(u,v)$ 同时满足 $dis(S,u)+L+dis(T,v)\leq K$ 和 $dis(S,v)+L+dis(T,u)\leq K$，这样算不会算重吗？

答案是这种情况不存在。[证明](https://www.luogu.com.cn/paste/xih4onqp)比较简单，这里不再展开。

---

## 作者：kkxacj (赞：1)

#### 思路

显然，如果不建边，$s$ 到 $t$ 最短路已经小与等于 $k$，显然所有情况都满足，输出 $\frac{n\times \left ( n-1 \right ) }{2} $ 即可，因为连任何边都可以。

如果不满足，设 $dis_{i,j}$ 为 $i$ 到 $j$ 最短路，显然需要找到所有满足 $dis_{s,i} + L + dis_{j,t} \le k$ 的，发现可以枚举 $i$，那么就是看有多少个 $j$ 满足 $dis_{j,t} \le k-L-dis_{s,i}$ 的，树状数组维护即可。

注意到这里是洛谷，不被喜欢的题解会被直接撤下，我们需要来证明为什么不会算重。

首先 $s$ 到 $t$ 距离 $\le k$ 都合法，已经判完了。

那么 $dis_{s,t} > k$，一个显然的 $dis_{s,i}+dis_{i,t} \ge dis_{s,t}$。

如果算重，那么就是 $dis_{s,a}+dis_{b,t}+L\le k,dis_{s,b}+dis_{a,t}+L\le k$ 两个同时成立。

合并一下就是 $dis_{s,a}+dis_{a,t} + dis_{s,b}+dis_{b,t} \le 2\times \left(k-L\right)$。

而左边的式子应当是大于 $2\times k$，所以显然矛盾，所以不存在。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
const int ma = 3e5+10;
int n,m,s,t,L,k,head[ma],cnt,x,y,z,dis[ma][2],v[ma],c[ma],tot,cnt1,d[ma*2],sum[ma],ans,l,r,mid,o1;//0/1 表示s/t 到j的最短路 
struct w
{
	int to,nxt,z;
}b[ma*2];
inline void add(int x,int y,int z)
{
	b[++cnt].nxt = head[x];
	b[cnt].to = y,b[cnt].z = z;
	head[x] = cnt;
}
priority_queue<pair<int,int> >p;
inline void bfs(int id)
{
	while(!p.empty())
	{
		x = p.top().second; p.pop();
		v[x] = 0;
		for(int i = head[x];i;i = b[i].nxt)
		{
			if(dis[b[i].to][id] > b[i].z+dis[x][id])
			{
				dis[b[i].to][id] = b[i].z+dis[x][id];
				if(!v[b[i].to]) p.push(make_pair(-dis[b[i].to][id],b[i].to)),v[b[i].to] = 1;
			} 
		}
	}
}
unordered_map<int,int>mp; 
signed main()
{
	read(n),read(m),read(s),read(t),read(L),read(k);
	for(int i = 1;i <= m;i++) read(x),read(y),read(z),add(x,y,z),add(y,x,z); 
	for(int i = 1;i <= n;i++) dis[i][0] = dis[i][1] = 1e18; 
	dis[s][0] = dis[t][1] = 0;
	p.push(make_pair(0,s)); bfs(0);
	if(dis[t][0] <= k)
	{
		print(n*(n-1)/2);flush();
		return 0;
	}
	p.push(make_pair(0,t)); bfs(1);
	tot = 1;
	for(int i = 1;i <= n;i++) d[++cnt1] = dis[i][1];
	sort(d+1,d+1+cnt1);
	for(int i = 1;i <= cnt1;i++) if(!mp[d[i]]) mp[d[i]] = ++tot;
	for(int i = 1;i <= n;i++) sum[mp[dis[i][1]]]++;
	for(int i = 1;i <= tot;i++) sum[i] += sum[i-1];
	for(int i = 1;i <= n;i++)
	{
		if(L + dis[i][0] > k) continue;
		l = 1,r = cnt1,o1 = -100;
		while(l <= r)
		{
			mid = (l + r) / 2;
			if(d[mid] > k-L-dis[i][0]) r = mid - 1;
			else l = mid + 1,o1 = mp[d[mid]];
		}
		if(o1 != -100) ans += sum[o1];
	}
	print(ans); flush();
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：1)

首先求出最短路，$dis_{s,u}$ 表示 $s\to u$ 最短路，$dis_{t,u}$ 表示 $u\to t$ 最短路。这里可以使用 Dijkstra 算法。

如果 $dis_{s,t}\leq k$，那么不管怎么加都满足条件，特判掉，输出 $\frac{n(n-1)}{2}$。

否则，我们可以枚举 $(u,v)$，判断 $dis_{s,u}+l+dis_{v,t}\leq k$。

但是这样子是 $\mathcal O(n^2)$ 的，考虑优化。

移项得到 $dis_{v,t}\leq k-dis_{s,u}-l$，我们便可以对 $dis_{v,t}$ 排序，枚举 $u$，二分出多少个 $v$ 符合条件。

时间复杂度 $\mathcal O(n\log n)$。

等等，为什么这样是对的呢？为什么 $(u,u)$ 不会被算，$(u,v)$ 不会和 $(v,u)$ 被多计算一次？我们来证明一下。

洛谷所有没证明的题解都被我请求撤下了。

<https://www.luogu.com.cn/discuss/1138765>

首先，特判 $dis_{s,t}\leq k$ 之后 $dis_{s,u}+dis_{u,t}\geq dis_{s,t}\gt k$，所以 $(u,u)$ 肯定不会被统计。

那么就是：

$$
\begin{cases}

dis_{s,u}+l+dis_{t,v} \leq k < dis_{s,u}+dis_{t,u}\\
dis_{s,v}+l+dis_{t,u} \leq k < dis_{s,v}+dis_{t,v}

\end{cases}
$$
我们上下相加得到：
$$
dis_{s,u}+l+dis_{t,v} + dis_{s,v}+l+dis_{t,u} \leq 2k
$$
移项得到：
$$
(dis_{s,u}+dis_{t,u})+(dis_{s,v}+dis_{t,v})\leq 2(k-l)
$$
而我们有：
$$
k < dis_{s,u}+dis_{t,u}\\
k < dis_{s,v}+dis_{t,v}
$$
所以：
$$
(dis_{s,u}+dis_{t,u})+(dis_{s,v}+dis_{t,v}) \gt 2k
$$
由于 $l>0$，所以与 $(dis_{s,u}+dis_{t,u})+(dis_{s,v}+dis_{t,v})\leq 2(k-l)$ 矛盾。故不等式组无解，即 $(u,v)$ 和 $(v,u)$ 不会被计算两次。

---

