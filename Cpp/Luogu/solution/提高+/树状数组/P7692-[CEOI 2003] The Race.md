# [CEOI 2003] The Race

## 题目描述

在一年一度的调谐宇宙飞船星际竞赛中，$N$ 艘宇宙飞船将参赛。每艘宇宙飞船 $i$ 的调谐方式都是这样的，它可以在零时间内加速到它的最大速度 $V_i$ 并继续以那个速度巡航。由于过去的成就，每艘宇宙飞船都从一个起始位置出发，给定其飞船离起跑线的距离。  
赛程无限长。因为宇宙飞船速度很快，比赛的路线一直都是笔直的。在直线赛道上，飞船可以很容易地相互通过，而没有互相干扰。  
很多观众还没有意识到，比赛的胜负是可以提前预测的。你的任务是向他们展示这一点，告诉他们宇宙飞船将相互经过多少次，并通过按时间顺序预测宇宙飞船经过的前 $10000$ 次。  
您可以假设每艘宇宙飞船都从不同的位置开始。此外，任何时候在赛道的同一位置上永远不会有超过两艘飞船。   
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/437urrvu.png)

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$0 < N \leq 250 000$，$0 \leq X_i \leq 1 000 000$，$0 < V_i < 100$。
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2003 的 [The Race](https://www.ceoi2003.de/www/downloads/therace-en.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
4
0 2
2 1
3 8
6 3```

### 输出

```
2
3 4
1 2```

# 题解

## 作者：comcopy (赞：4)

题意不多赘述。

求超车次数，可以发现能将问题转换为一个逆序对问题。

由于速度的范围只有 $1\sim 99$ 所以我们可以直接开个桶储存 $1\sim i-1$ 的速度，然后直接暴力统计前面的速度大于当前的速度的个数累加就行。

然后就是超车问题。

我们首先将车按位置排序，可以发现所有车都无法越位超车，即第 $i$ 辆车不可能在：

第 $i$ 辆车不超过第 $i+1$ 辆车且第 $i+1$ 辆车不超过第 $i+2$ 辆车的情况下超过第 $i+2$ 辆车。

所以我们可以发现当前时间后的第二次超车一定是相邻两辆车之间发生的。

所以我们直接开个结构体堆维护相邻两辆车之间的超车所用相对时间。

优先比较时间就行。

剩下的似乎就是模拟了。

因为担心出现精度问题，所以这里直接用 `double` 类型储存时间。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 250010;
int n, x[N],v[N];
int f[N],id[N];
//排名，编号
struct fyn1 {
	int x, y;
	double t;
	inline bool operator <(const fyn1 &fyn)const {
		return t!=fyn.t? t > fyn.t: f[x] > f[fyn.x];
	}
};

priority_queue<fyn1> q;
int fyn[110];

signed main() {

	cin>>n;
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		cin>>x[i]>>v[i];
		f[i] = id[i] = i;
		for(int j=v[i]+1; j<=99; ++j) {
			ans+=fyn[j];
			ans%=1000000;
		}
		++fyn[v[i]];
		if(i^1 && v[i - 1] > v[i])
			q.push((fyn1) {
			i-1,i,1.0*(x[i] - x[i - 1]) / (v[i - 1] - v[i])
		});//将相邻超车时间全部记录下来

	}

	cout<<ans<<endl;//超车次数

	int cnt = 1;
	while (cnt <= 10000 && q.size()) {//控制次数
		int nx=q.top().x,ny=q.top().y;
		q.pop();
		if(f[nx]+1!=f[ny])continue;
		else
			++cnt;
		cout<<nx<<' '<<ny<<endl;

		swap(id[f[nx]], id[f[ny]]);
		swap(v[f[nx]], v[f[ny]]);
		swap(x[f[nx]], x[f[ny]]);
		swap(f[nx], f[ny]);//交换位置

		if (f[nx]<n && v[f[nx]]>v[f[nx]+1]&&f[id[f[nx]]] + 1 == f[id[f[nx] + 1]])//若能超车且相邻
			q.push((fyn1) {
			id[f[nx]],id[f[nx]+1],1.0*(x[f[nx] + 1] - x[f[nx]]) / (v[f[nx]] - v[f[nx] + 1])
		});

		if (f[ny] > 1 && v[f[ny] - 1] > v[f[ny]] && f[id[f[ny] - 1]] + 1 == f[id[f[ny]]])//若能超车且相邻
			q.push((fyn1) {
			id[f[ny] - 1], id[f[ny]], 1.0*(x[f[ny]] - x[f[ny] - 1]) / (v[f[ny] - 1] - v[f[ny]])
		});
	}
	return(0-0);
}
```


---

## 作者：Chenyichen0420 (赞：3)

## 思路分析

试着交一下吧，远古题没给 hack。

首先，题目中输入时保证了 $x$ 单调递增，那么在 $i$ 飞船输入进来的时候，只有之前的 $v_j>v_i$ 的飞船 $j$ 才会超过 $i$，于是第一问可以大常数线性做。

第二问呢？考场上我并没有想出来合适的方式处理，于是开始考虑骗分歪解。我们注意到，我们一定可以通过最劣根优先队列来维护所有可能的解。

当我们发现堆中的个数超过了 $10^4$ 的时候，我们就可以将超过 $10^4$ 的那些解丢掉，然后记录下堆顶的相遇时间 $tmax$。

这有什么用呢？我们再想一下我们怎样统计贡献。当 $p_j<p_i$ 且 $v_j>v_i$ 的时候 $i,j$ 会相遇。于是，我们可以对于每一个 $i$，枚举满足 $v_j>v_i$ 的点的贡献。

但是这样显然不优。我们考虑按照 $v$ 分批处理。这时候我们惊奇的发现：$v$ 对应的那些船相对静止。

这看似很废话，但是这告诉我们相同速度的船，越靠前的一定越先相遇。也就是说，如果我们倒序枚举这个速度对应的船，当我们发现某一艘船的相遇时间已经超过 $tmax$ 的时候，其前面的一定不会在 $tmax$ 内。

这样，在随机数据下，统计贡献的次数就会大大降低。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr bool online = 0;
int n, p[250005], v[250005], ans;
inline double get(int l, int r) {
	return double(p[r] - p[l]) / (v[l] - v[r]);
}
struct node {
	int l, r; double t, p;
	node(int li = 0, int ri = 0) :l(li), r(ri) {
		t = get(l, r); p = ::p[l] + t * v[l];
	}
	friend bool operator<(const node& l, const node& r) {
		return l.t != r.t ? l.t < r.t : l.p < r.p;
	}
}tp; priority_queue<node>pq; stack<node>an;
vector<int>ps[100]; double ltt;
signed main() {
	if (online)
		freopen("race.in", "r", stdin),
		freopen("race.out", "w", stdout);
	ios::sync_with_stdio(0); cin >> n; ltt = 1e18;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i] >> v[i];
		ps[v[i]].emplace_back(i);
		for (int j = 99; j > v[i]; --j) {
			ans = (ans + ps[j].size()) % 1000000;
			for (int p = ps[j].size() - 1; p >= 0; p--) {
				tp = node(ps[j][p], i);
				if (tp.t > ltt) break;
				pq.emplace(tp);
			}
			if (pq.size() >= 10000) {
				while (pq.size() > 10000) pq.pop();
				ltt = pq.top().t;
			}
		}
	}
	cout << ans << endl;
	while (pq.size()) an.emplace(pq.top()), pq.pop();
	while (an.size()) cout << an.top().l << " " << an.top().r << endl, an.pop();
	return 0;
}
//私は猫です
```

---

## 作者：Dumby_cat (赞：3)

# 一只蒟蒻的 POJ2274(洛谷 p7692)题解报告
[POJ题目链接](http://poj.org/problem?id=2274)

[洛谷题目链接](https://www.luogu.com.cn/problem/P7692)
## 题目描述
给一堆车超出起点的距离 x 和车速度 v，速度不变，求出飞行过程中的超车总数（$\mod 1000000$）并输出超车与被超车的车的编号（如有同时则编号小的先输出）。
### 输入
一行一个整数  $n (0 < n <= 250000)$  表示车数。

接下来 n 行，每行两个整数  $x (0 <= x <= 1000000)$  和  $v (0 < v < 100)$，表示车超出起点的距离和车速。
### 输出
第一行一个整数，表示超车次数  $ans \mod 1000000$  的值。

后面  $\min(10000,ans)$  行（即如果超车次数不足  $10000$  次，则全输出，否则输出前  $10000$  个）每行两个整数 a 和 b，表示超车的车的编号以及被超车的车的编号（即  a  车超过了  b  车）。如果有多个超车事件同时发生，先输出离起跑线近的那个（即排名小的）。
## 题解
第一个问题一看就是逆序对问题，可以用树状数组求。

第二个问题稍微麻烦些。

我们令离起跑线近的排名小。

我们将所有车按照其  x  值排序，如图：

![请添加图片描述](https://img-blog.csdnimg.cn/3f9dc9693f714c6187b47554ddbb27e2.jpg)

我们发现，只有排名相邻的两辆车才会最先发生超车事件。

超车事件发生的条件比较容易推出来：

设被超车的车的编号是  X  ，排名是  NUMX。

那么只要当 排名为  $\text{NUMX}-1$  的车（上图中靠左的车辆）的速度 大于  X  的速度 就会发生超车。


![请添加图片描述](https://img-blog.csdnimg.cn/3ab57d5b48b145dfa5a0738686fc789e.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0R1bWJ5X2NhdA==,size_16,color_FFFFFF,t_70)

如上图，最先发生超车的一定是  $1$  和  $2$， $2$  和  $3$，或  $3$  和  $4$。

假设此时只有  $2$  和  $3$  发生超车事件，超车交换位置后排名如下：

![请添加图片描述](https://img-blog.csdnimg.cn/ec436cd4fce248b5b3003888e39a12ec.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0R1bWJ5X2NhdA==,size_16,color_FFFFFF,t_70)

交换后又产生两组可能发生超车：  $1$  和  $3$、 $2$  和  $4$。所以接下来需要考虑这两个。

然后我们想：需要找最先超车的（即超车时间最小的），又要在中途加入操作对象，可以想到用堆来实现。

堆（小根堆）中存一个三元组，表示前一辆车（超车的车）的编号，后一辆车（被超车的车）的编号 以及 两车发生超车的时间  $\dfrac{x_{1}-x_{2}}{v_{2}-v_{1}}$。

堆中排序的关键字就是超车时间和排名（注意时间相同时要按排名输出）

每次取出堆顶，输出。

然后判断交换位置后新产生的两组是否能发生超车，能则入堆。

接下来见代码。
## 嗲吗
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#define PII pair<int,int>
#define int long long
using namespace std;
const int N = 1111500, MOD = 1e6, P = 131;
int read(){char c=getchar();int s=0,f=1;for(;!isdigit(c);c=getchar())if(c=='-')f=-1;for(;isdigit(c);c=getchar())s=s*10+c-48;return s*f;}
int n, tr[N], x[N], v[N], num[N], id[N];
//tr数组是树状数组
//x[i]表示排名为 i 的车离超过起点的距离
//v[i]表示排名为 i 的车的速度
//num[i]表示编号为 i 的车的排名
//id[i]表示排名为 i 的车的编号
struct node 
{//堆中的三元组
	int x, y;
	double t;
	bool operator <(const node &b)const {
		return t > b.t || (t == b.t && num[x] > num[b.x]);
	}//重载运算符，让堆变成小根堆（按照时间和排名排序）
};

priority_queue<node> q;

//接下来两个树状数组操作
void add(int x) 
{//添加
	for (; x <= 100; x += x & -x)tr[x]++;
}
int ask(int x) 
{//查询
	int ans = 0;
	for (; x; x -= x & -x)ans = (ans + tr[x]) % MOD;//记得取模
	return ans;
}

signed main() 
{
	
	n = read();
	int ans = 0;
	//ans用来记超车次数
	for (int i = 1; i <= n; i++) 
	{
		x[i] = read(), v[i] = read();
		
		num[i] = id[i] = i;
		//初始化
		ans = (ans + ask(100) - ask(v[i])) % MOD;
		add(v[i]);
		//树状数组操作
		if (i ^ 1 && v[i - 1] > v[i])
		//如果 i!=1 并且排名比他小一的车速度比他快
			q.push((node) { 
				i - 1, //前一辆车
				i, //后一辆车
				(double)(x[i] - x[i - 1]) / (v[i - 1] - v[i]) //超车时间
			});
	}
	
	printf("%lld \n", ans);
	
	int t = 1; //t用来记录个数，保证输出不超过10000个
	while (t <= 10000 && q.size()) 
	{
		int X = q.top().x, Y = q.top().y;
		q.pop();
		//X是前一辆车的编号，Y是后一辆车的编号
		
		if (num[X] + 1 != num[Y])continue;
		//如果两辆车的排名不相邻（不是最先发生超车）则跳过。
		
		printf("%lld %lld\n", X, Y); 
		t++;
		
		swap(id[num[X]], id[num[Y]]);
		swap(v[num[X]], v[num[Y]]);
		swap(x[num[X]], x[num[Y]]);
		swap(num[X], num[Y]);
		//交换 X 车与 Y 车的位置
		//交换后 X 车在前，Y 车在后（原本 Y 前 X 后）
		if (num[X] < n && v[num[X]] > v[num[X] + 1] &&
		        num[id[num[X]]] + 1 == num[id[num[X] + 1]])
		        //如果交换后 X 的排名不是 n （X 前还有车）
		        //并且 X 车速大于 X 前面那辆
		        //并且两辆车的排名相邻
			q.push((node) {
				id[num[X]], //前一辆车编号
				id[num[X] + 1], //后一辆车编号
				(double)(x[num[X] + 1] - x[num[X]]) / (v[num[X]] - v[num[X] + 1])
			});



		if (num[Y] > 1 && v[num[Y] - 1] > v[num[Y]] &&
		        num[id[num[Y] - 1]] + 1 == num[id[num[Y]]])
		        //同上
			q.push((node) {
				id[num[Y] - 1], 
				id[num[Y]], 
				(double)(x[num[Y]] - x[num[Y] - 1]) / (v[num[Y] - 1] - v[num[Y]]) 
			});
	}
	return 0; 
}
```

有错误请 D 我

---

