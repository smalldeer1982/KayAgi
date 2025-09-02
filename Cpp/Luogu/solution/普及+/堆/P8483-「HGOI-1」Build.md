# 「HGOI-1」Build

## 题目背景

一次旅行，$\text{uuku}$ 到了一个奇怪的小镇。

## 题目描述

这个小镇将要和周围的其他小镇一共 $n$ 个小镇，一起修建一个能**连通**这 $n$ 个小镇，有 $m$ 条高速公路的交通网。其中每条高速公路都将会连接**不同的两个小镇**，即不存在一条高速公路的起点和终点相同。

但高速公路的修建费用是很高的，所以镇长们一致决定将共同承担高速公路的费用，所以他们希望修建的**总费用最小**。

而且由于不同小镇的基础设施建设情况不同，所以每个小镇在修建的费用也不同。经过协商，每条高速公路将由其所连接的两个小镇共同施工。每个小镇负责一半路程。为了同时结束整个施工过程，显然将会有小镇同时进行多条道路的施工，而施工的道路数量越多，所需要花费的价钱就越多。

经过计算，每个小镇施工的花费可以用函数表示，及对于小镇 $i$，有三个参数 $a_i$，$b_i$，$c_i$。对于 $i$ 小镇来说在修建其第 $j$ 条高速时，**这条**高速所需要的花费为 $a_ij^2+b_ij+c_i$。

现在，这些镇长想要 $\text{uuku}$ 给他们提供一个满足要求的**建造方案**，使**总价格最小**。

当然，$\text{uuku}$ 将这个问题交给了你。

## 说明/提示

#### 数据范围
本题采用**捆绑测试**，共有 $6$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。
$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \textbf{特殊限制} \cr\hline
1 & 10 & n,m\le 500  \cr\hline
2 & 20 &  n,m\le 5\times 10^3 \cr\hline
3 & 10 & \text{每个小镇的函数相同}\cr\hline
4 & 20 & a_i=0 \cr\hline
5 & 20 & m=n-1 \cr\hline
6 & 20 & \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$2\le n \le 2 \times 10^5$， $n-1 \le m \le 10^6$，$0 \le a_i$，$b_i$，$c_i \le 10^6$。

数据保证最小价格在 $\tt{long \ long}$ 范围内。

#### 说明

本题有 $\text{spj}$，价格正确可以获得 $30\%$ 的分数。每个 $\text{subtask}$ 取其中所有数据点得分的最小值。

如果你不会构造方案，也请你再输出最小价格后输出 $m$ 行，每行两个 $[1,n]$ 范围内的整数，防止 $\text{spj}$ 出现错误。

本题已添加 hack 数据，为 $\text{subtask7}$，该 $\text{subtask}$ 不计分数，但会影响是否 $\text{AC}$。

## 样例 #1

### 输入

```
4 4
1 2 3
2 3 4
3 4 5
4 5 6```

### 输出

```
114
1 2
1 2
1 3
3 4```

# 题解

## 作者：uuku (赞：13)

不难发现，每个小镇花费的价钱只与该小镇建了多少条公路有关，与和哪个小镇建的无关。而每个小镇修建的条数就是最后生成的途中该点的度数，记为 $du_i$。

所以我们不妨从每个小镇的角度进行求解。将每个小镇修建下一条公路的代价排序后取最小值。显然修建 $m$ 条道路，即 $\sum\limits_{i=1}^n du_i=2m$。所以只需取 $2m$ 次最小值即可。

上述过程可以用堆维护。

但是还没结束，还要满足图连通和没有自环两个条件。

图连通的一个显然的必要条件是 $\forall i \in [1,n],du_i>0$。

无自环的一个显然的必要条件是 $\forall i \in [1,n],du_i\le m$。

### 下面给出构造方案以证明充分性：

我们只需不断的将当前度数最小值的点连向度数最大值的点即可。

#### 证明连通性

考虑当当前的度数最小值是 $1$ 时，连了这条边之后它将无法再和其它点连边。但是连了这条边之后，它将和当前的度数最大的点连通。

而之前和它连通的点（可能没有），也会间接的和剩下的点连通。

也就是说每个度数变为 $0$ 的点都会直接或间接的和当前剩下的度数不为 $0$ 的点连通。

所以最终这 $n$ 个点会连通。

#### 证明无自环

考虑用反证法，假设最终会产生自环，即 $\exists i \in [1,n],du_i>0$。而由于总度数是偶数，每次连边也会使总度数减 $2$。所以 $du_i\ge 2$ 且 $ du_i \bmod 2=0$。

$i$ 会有两种情况：

1. $du_i$ 一直是最大值，那么意味着一直是将 $i$ 与其他点连边，即 $du_i>2m-du_i$，这与上面要求的 $du_i\le m$ 矛盾。

2. 存在 $j$，满足在最开始时 $du_j>du_i$。那么当 $du_j$ 减到 $du_i$ 时，根据上述过程不难发现，在此之后会满足 $|du_i-du_j|\le 1$。而根据假设此时 $du_i-du_j\ge 2$。产生矛盾。

所以假设不成立，即最后不会产生自环。

时间复杂度 $O(m\log n)$

示例代码：

```
#define pli pair<ll,int>
const int N = 2e5 + 10;
int n, m, du;
ll ans;
struct P{
	int id, a, b, c, cnt;
	inline void rd(int i){id = i, cin >> a >> b >> c;}
	inline ll get(){cnt++; return (1ll * a * cnt + b) * cnt + c;}
} v[N];
priority_queue<pli, vector<pli>, greater<pli>> q;
pli now;
inline bool cmp(P x, P y){return x.cnt > y.cnt;}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m, du = m << 1;
	for(int i = 1; i <= n; ++i) v[i].rd(i);
	
	for(int i = 1; i <= n; ++i) ans += v[i].get();
	du -= n;
	
	for(int i = 1; i <= n; ++i) q.push(make_pair(v[i].get(), i));
	
	while(du--)
	{
		now = q.top(), q.pop();
		ans += now.first;
		if(v[now.second].cnt == m){v[now.second].cnt++;continue;}
		q.push(make_pair(v[now.second].get(), now.second));		
	}
	for(int i = 1; i <= n; i++) v[i].cnt--; 
	
	cout<<ans<<'\n';
	
	sort(v + 1, v + n  + 1, cmp);
	int l = 1, r = n;
	while(v[r].cnt == 0) r--;
	while(l < r)
	{
		if(v[1].cnt == 1)break;
		cout<<v[r].id<<' '<<v[l].id<<'\n';
		v[r].cnt--, v[l].cnt--;
		l++;
		if(v[l].cnt <= v[1].cnt && v[1].cnt) l = 1;
		if(!v[r].cnt) r--;
		if(l == r && v[l].cnt)swap(v[l], v[1]), l = 1;
	}
	if(v[1].cnt)
	{
		for(int i = 2; i <= n; i++)
			if(v[i].cnt)
			{
				cout<<v[i].id<<' '<<v[i-1].id<<"\n";
				v[i].cnt--, v[i-1].cnt--;
			}
	}
	return 0;
}
```

### 赛时选手提供的爆标思路

同样只考虑每个点的度数，显然会有一个最大值，我们不妨直接二分这个最大值。然后可以用二次函数求根公式快速计算每个点选了多少次。然后判断总度数是否达到 $2m$ 且每个点度数仍符合上述条件即可。复杂度可以做到 $O(n\log V+m)$。

---

