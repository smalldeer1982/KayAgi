# [COTS 2020] 餐厅 Restoran

## 题目背景

译自 [Izborne Pripreme 2020 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2020/) D2T2。$\texttt{2s,0.5G}$。



## 题目描述


苏联餐厅前有 $N$ 个人在排队，按顺序标号 $1\sim N$。

餐厅内只有一种菜，同时也是招牌菜——煎蛋。餐厅内没有厨师，所以食物由客人自己烹饪。

由于设备有限，**同一时刻最多有一个人可以烹饪，同一时刻最多有一个人可以用餐。** 

定义：「用餐总时间」为从第一个人开始准备食物，到最后一个人用完餐，需要的时间。

烹饪和用餐不一定按顺序，先烹饪的客人可以后用餐。

第 $i$ 个人的烹饪时间为 $a_i$，用餐时间为 $b_i$。你需要求出最优情况下，用餐总时间的最小值。



此外，还有 $M$ 个事件：

- $\texttt{DOLAZI a b}$：新来了一位新客人，他的烹饪时间为 $a$，用餐时间为 $b$。设这是第 $i$ 位新来的客人，则标号为 $(N+i)$。
- $\texttt{ODLAZI x}$：第 $x$ 位客人离开队伍。
- $\texttt{POREDAK}$：客人很不耐烦，想要知道最优的策略，使得用餐总时间最短。

对于前两个类型的事件，你需要求出这个事件结束后，用餐总时间的最小值；

对于第三个类型的事件，你需要求出此时最佳的烹饪、用餐顺序。

## 说明/提示



#### 数据范围


对于 $100\%$ 的数据，保证：

- $1\le N,M\le 2\times 10^5$；
- $1\le a_i,b_i,a,b\le 10^9$；
- 事件合法，且每一时刻至少存在一名客人；
- **$\texttt{POREDAK}$ 事件最多只有 $\bf 10$ 个。**


| 子任务编号 | $N\le $ | $M\le $ |  特殊性质   | 得分 |  
| :--: | :--: | :--: | :--: | :--: |  
| $ 1 $    | $9$ | $ 1 $    |  A  | $ 5 $   |  
| $ 2 $    | $20$ | $1$   |  A | $ 13 $   |  
| $ 3 $    | $2\times 10^5$ | $1$ | A  | $ 21 $   |  
| $ 4 $    | $2\times 10^5$ | $2\times 10^5$  |  B | $ 29 $   |  
| $ 5 $    | $2\times 10^5$ | $2\times 10^5$  |   | $ 32 $   |  

- 特殊性质 A：只有 $\texttt{POREDAK}$ 事件。
- 特殊性质 B：没有 $\texttt{POREDAK}$ 事件。


## 样例 #1

### 输入

```
2 1
1 3
2 3
POREDAK```

### 输出

```
7
1 2 1 2```

## 样例 #2

### 输入

```
1 4
4 3
DOLAZI 3 8
DOLAZI 5 2
ODLAZI 1
ODLAZI 3```

### 输出

```
7
14
16
13
11```

# 题解

## 作者：伊地知虹夏 (赞：2)

缝合怪。

首先考虑性质 A 怎么做。这就是 [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)，结论是最优解满足 $\forall 1 \le i < j \le n, \min(a_i,b_j) \le \min(a_j,b_i)$。但是这个条件不满足传递性，所以分 $a_i < b_i$，$a_i = b_i$，$a_i > b_i$ 讨论一下，得到排序方式。然后依次考虑每个人，记 $p_i$ 为 $a_i$ 的前缀和，$q_i$ 为 $[1,i]$ 的答案，则有 $q_i = \max(q_{i-1}, p_i) + b_i$。

然后考虑正解。先把所有人离线下来按照上述规则排序，记 ${\rm rnk}_i$ 为 $i$ 在新序列中的位置，那么方案就是将客人按照 $\rm rnk$ 排序。

接下来我们要加速求答案的过程，考虑把 $p_i$，$q_i$ 的转移写成 $(\max,+)$ 卷积的形式：

$$
[q_i, p_i] = [q_{i-1}, p_{i-1}] \times 
\begin{bmatrix}
b_i & -\infin \\
a_i+b_i & a_i \\
\end{bmatrix}
$$

我们使用线段树维护矩阵乘法即可。

---

## 作者：chenxumin1017 (赞：0)

对于 A 性质，没有修改操作，我们只要找到一种将人排序的策略，如果不会的请左转[加工生产调度](https://www.luogu.com.cn/problem/P1248)。

我们知道按怎样的顺序排列人，$\tt POREDAK$ 操作就只需要用一棵平衡树维护，查询时输出中序遍历即可。

这样，我们就只需要对于每次操作之后快速求答案。
回忆一下[加工生产调度](https://www.luogu.com.cn/problem/P1248)的求答案的方法，同样的，我们维护两个变量 $suma, sumb$ 表示上一个人烹饪的结束时间和上一个人用餐的结束时间。

转移就为 $sumb\leftarrow \max(sumb + b_i,suma + a_i + b_i), suma \leftarrow suma + a_i$。

写成 $(\max,+)$ 矩乘的形式：
$$
\begin{bmatrix}
suma & sumb
\end{bmatrix}
\cdot
\begin{bmatrix}
a_i & a_i + b_i\\
-\infty & b_i\\
\end{bmatrix}
= 
\begin{bmatrix}
suma' & sumb'
\end{bmatrix}
$$

直接平衡树维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5, INFF = 1e18;
int n, m, dcnt, RT;
struct matrix{
	int a[2][2];
}INF, INF2;
matrix operator*(const matrix x, const matrix y){
	matrix z = INF2;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			for(int k = 0; k < 2; k++)
				z.a[i][j] = max(z.a[i][j], x.a[i][k] + y.a[k][j]);
	return z;
}//矩乘
struct Node{
	int x, y, id, op, rank, ls, rs;
	matrix a, sum;
}tr[N * 2];
mt19937 rnd(time(0));
bool operator<(const Node x, const Node y){
	return (x.op == y.op ? (!x.op ? (x.x == y.x ? x.id < y.id : x.x < y.x) : (x.y == y.y ? x.id < y.id : x.y > y.y)) : x.op < y.op);
}//排序策略

void split(int now, Node k, int &x, int &y){
	if(now == 0){
		x = y = 0;
		return;
	}
	if(tr[now] < k){
		x = now;
		split(tr[now].rs, k, tr[now].rs, y);
	}else{
		y = now;
		split(tr[now].ls, k, x, tr[now].ls);
	}
	tr[now].sum = tr[tr[now].ls].sum * tr[now].a * tr[tr[now].rs].sum;
}
int merge(int x, int y){
	
	if(!(x && y))return x | y;
	if(tr[x].rank < tr[y].rank){
		tr[x].rs = merge(tr[x].rs, y);
		tr[x].sum = tr[tr[x].ls].sum * tr[x].a * tr[tr[x].rs].sum;
		return x;
	}
	tr[y].ls = merge(x, tr[y].ls);
	tr[y].sum = tr[tr[y].ls].sum * tr[y].a * tr[tr[y].rs].sum;
	return y;
}
void solve(int x){
	if(!x)return;
	solve(tr[x].ls);
	cout << x << ' ';
	solve(tr[x].rs);
}
signed main(){
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	INF2.a[0][0] = INF2.a[0][1] = INF2.a[0][2] = INF2.a[0][3] = -INFF;
	tr[0].a.a[0][0] = 0, tr[0].a.a[0][1] = -INFF;
	tr[0].a.a[1][0] = -INFF, tr[0].a.a[1][1] = 0;
	tr[0].sum = tr[0].a;
	for(int i = 1; i <= n; i++){
		cin >> tr[i].x >> tr[i].y;
		tr[i].id = i;
		tr[i].op = (tr[i].x >= tr[i].y);
		tr[i].a.a[0][0] = tr[i].x, tr[i].a.a[0][1] = tr[i].x + tr[i].y;
		tr[i].a.a[1][0] = -INFF, tr[i].a.a[1][1] = tr[i].y;
		tr[i].sum = tr[i].a;
		tr[i].rank = rnd();
		int RT1, RT2;
		split(RT, tr[i], RT1, RT2);
		RT = merge(RT1, merge(i, RT2));
	}
	matrix ans = INF * tr[RT].sum;
	cout << ans.a[0][1] << '\n';
	dcnt = n;
	string op;
	for(int i = 1, x, y; i <= m; i++){
		cin >> op;
		if(op[0] == 'D'){
			cin >> tr[++dcnt].x >> tr[dcnt].y;
			tr[dcnt].id = dcnt;
			tr[dcnt].op = (tr[dcnt].x >= tr[dcnt].y);
			tr[dcnt].a.a[0][0] = tr[dcnt].x, tr[dcnt].a.a[0][1] = tr[dcnt].x + tr[dcnt].y;
			tr[dcnt].a.a[1][0] = -INFF, tr[dcnt].a.a[1][1] = tr[dcnt].y;
			tr[dcnt].sum = tr[dcnt].a;
			tr[dcnt].rank = rnd();
			int RT1, RT2;
			split(RT, tr[dcnt], RT1, RT2);
			RT = merge(RT1, merge(dcnt, RT2));
			matrix ans = INF * tr[RT].sum;
			cout << ans.a[0][1] << '\n';
		}else if(op[0] == 'O'){
			cin >> x;
			int RT1, RT2, RT3;
			split(RT, tr[x], RT1, RT2);
			Node xx = tr[x];
			xx.id++;
			split(RT2, xx, RT2, RT3);
			RT = merge(RT1, RT3);
			matrix ans = INF * tr[RT].sum;
			cout << ans.a[0][1] << '\n';
		}else{
			solve(RT);
			solve(RT);
			cout << '\n';
		}
		matrix xx = (tr[2].a * tr[1].sum);
	}
	return 0;
}
``````

---

