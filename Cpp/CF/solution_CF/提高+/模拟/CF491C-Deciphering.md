# Deciphering

## 题目描述

One day Maria Ivanovna found a Sasha's piece of paper with a message dedicated to Olya. Maria Ivanovna wants to know what is there in a message, but unfortunately the message is ciphered. Maria Ivanovna knows that her students usually cipher their messages by replacing each letter of an original message by some another letter. Replacement works in such way that same letters are always replaced with some fixed letter, and different letters are always replaced by different letters.

Maria Ivanovna supposed that the message contains answers to the final exam (since its length is equal to the number of final exam questions). On the other hand she knows that Sasha's answer are not necessary correct. There are $ K $ possible answers for each questions. Of course, Maria Ivanovna knows correct answers.

Maria Ivanovna decided to decipher message in such way that the number of Sasha's correct answers is maximum possible. She is very busy now, so your task is to help her.

## 样例 #1

### 输入

```
10 2
aaabbbaaab
bbbbabbbbb
```

### 输出

```
7
ba
```

## 样例 #2

### 输入

```
10 2
aaaaaaabbb
bbbbaaabbb
```

### 输出

```
6
ab
```

## 样例 #3

### 输入

```
9 4
dacbdacbd
acbdacbda
```

### 输出

```
9
cdba
```

# 题解

## 作者：睿智的憨憨 (赞：1)

## 解法分析

如果将映射看成二分图左部到右部的一条边，而一条边 $(u,v)$ 的权值为满足 $s_i=u,t_i=v$ 的 $i$ 的个数，那么答案就是二分图的最大权完美匹配。将所有边的流量设为 $1$，费用设为边权值的相反数，跑最小费用最大流，过程中记录匹配情况。答案就是最小费用的绝对值。

## 参考代码

```
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pushf push_front
#define pushb push_back
#define popf pop_front
#define popb pop_back
#define lowbit(x) (x-(x&(x-1)))
using namespace std;
const int N = 110, inf = 2e9;
 
struct Edge{
	int to, id;
} ;

int n, k, m, S, T, id[N][N];
vector<Edge> e[N];
string s, t;

int dis[N], cur[N], p[N], f[1000010], val[1000010], ans;
bool vis[N];
bool spfa(){
	for (int i = S; i <= T; i++)
		dis[i] = inf, vis[i] = false, cur[i] = 0;
	queue<int> q;
	q.push(S), dis[S] = 0;
	while (!q.empty()){
		int u = q.front();
		q.pop(), vis[u] = false;
		for (Edge i : e[u])
			if (f[i.id] && dis[i.to] > dis[u] + val[i.id]){
				dis[i.to] = dis[u] + val[i.id];
				if (!vis[i.to]){
					vis[i.to] = true;
					q.push(i.to);
				}
			}
	}
	return dis[T] != inf;
}
int dfs(int u, int flow){
	vis[u] = true;
	if (u == T)
		return flow;
	int used = 0, rlow = 0;
	for (int i = cur[u]; i < e[u].size(); i++){
		cur[u] = i + 1;
		int v = e[u][i].to, id = e[u][i].id;
		if ((v == T || !vis[v]) && dis[v] == dis[u] + val[id] && f[id])
			if (rlow = dfs(v, min(f[id], flow - used))){
				if (1 <= u && u <= k && k + 1 <= v && v <= 2 * k)
					p[u] = v;
				used += rlow;
				ans += val[id] * rlow;
				f[id] -= rlow, f[id ^ 1] += rlow;
				if (used == flow)
					return flow;
			}
	}
	return used;
}
int Dinic(){
	ans = 0;
	while (spfa()){
		dfs(S, inf);
		while (vis[T]){
			memset(vis, false, sizeof(vis));
			dfs(S, inf);
		}
	}
	return abs(ans);
}
char ch(int i){
	if (i <= 26)
		return 'a' + (i - 1);
	return 'A' + (i - 27);
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> k >> s >> t;
	S = 0, T = 2 * k + 1;
	for (int i = 1; i <= k; i++){
		m++;
		e[S].push_back({i, id[S][i] = 2 * m - 2}), f[2 * m - 2] = 1; 
		e[i].push_back({S, id[i][S] = 2 * m - 1});
		m++;
		e[k + i].push_back({T, id[k + i][T] = 2 * m - 2}), f[2 * m - 2] = 1;
		e[T].push_back({k + i, id[T][k + i] = 2 * m - 1});
		for (int j = k + 1; j <= 2 * k; j++){
			m++;
			e[i].push_back({j, id[i][j] = 2 * m - 2}), f[2 * m - 2] = 1;
			e[j].push_back({i, id[j][i] = 2 * m - 1});
		}
	}
	for (int i = 0; i < n; i++){
		int a = (s[i] >= 'a' ? s[i] - 'a' + 1 : 26 + s[i] - 'A' + 1);
		int b = (t[i] >= 'a' ? t[i] - 'a' + 1 : 26 + t[i] - 'A' + 1);
		val[id[a][k + b]]--;
		val[id[a][k + b] ^ 1]++;
	}
	cout << Dinic() << "\n";
	for (int i = 1; i <= k; i++)
		cout << ch(p[i] - k);
	cout << "\n";
	return 0;
}
```Deciphering

---

