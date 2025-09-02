# [NERC 2020] Button Lock

## 题目描述

你站在一个藏有巨大宝藏的房间门前。唯一的阻碍是一个带有按钮组合锁的门。这把锁有 $d$ 个按钮，分别标有数字 $0$ 到 $d - 1$。每次按下按钮时，它会保持按下状态。你不能单独弹起一个按钮，但有一个 "RESET" 按钮——按下它会弹起所有其他按钮。初始状态下，所有按钮均未按下。

当某些特定的数字组合被按下时，门会立即打开。遗憾的是，你并不知道密码。通过阅读该锁的文档，你发现这把锁有 $n$ 种可能的密码。  

请找出最短的按钮操作序列，使得在执行过程中所有可能的密码至少出现一次。任何最短的正确操作序列都将被接受。

## 说明/提示

在第二个示例中，序列 $\tt{1 2 R 2 0 1}$ 也是可行的。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2 2
10
11```

### 输出

```
2
0 1```

## 样例 #2

### 输入

```
3 4
001
111
101
011```

### 输出

```
6
2 0 R 1 2 0```

# 题解

## 作者：ArisakaMashiro (赞：3)

下文，我们将一个密码通过按下新的按钮形成另一个密码的过程称之为**操作**。

那么原题的过程就相当于从初始状态开始，通过进行操作不断的尝试每一种密码，并在恰当的时间进行重置回到初始状态。

不妨将密码看作一个二进制数（注意题目的输入是从第 $0$ 位开始）。

如果我们将密码抽象成点，操作抽象为边，那么本题所做的事情本质上就是在图上寻找数条以初始状态为起点的路径，使得所有点都被覆盖至少一次的前提下满足

$$$\sum_{i \in T}(\operatorname{bitcount}(i) + 1) - 1$$$

最小，其中 $T$ 是所有路径的终点所构成的集合。

我们猜想上式有最小值时必定有路径数最小，考虑使用反证法：如果路径数不是最小，要么本来就是结尾的点依旧是结尾，要么 $1$ 更多的密码成为了终点，一定不优。

那么这就是一个最小路径覆盖问题，解决方法有网络流和匈牙利算法，不会做的右转 [P2764 最小路径覆盖问题](https://www.luogu.com.cn/problem/P2764)，此处不多加赘述，下文采用网络流实现。

但若只是照搬最小路径覆盖问题，那么你会 WA#14，原因在于两条路径都唯一指向同一个点的时候，显然应该将这个点划分给当前终点 $1$ 更多的那条路径，但最小路径覆盖问题的网络流实现不了这点。

如何解决？我们只需要让 $1$ 更多的点在找后继节点时有更高的优先级即可。

所以，我们在网络流进行的过程中不一次性将所有点加入，而是将所有点按照 $1$ 的个数分组，再从大到小依次加入并连边，每加完一组点就跑一次最小路径覆盖问题。

正确性不难证明：由于网络流的性质，只要当前的流法能够满足最小路径的前提就不会被修改。那么只要 $1$ 的数量较多的点在较少的点之前先被加入图中，就能够保证其优先与 $1$ 的数量更多的点进行匹配。

总时间复杂度 $O(m ^ {\frac{5}{2}})$，可以通过此题。

:::info[代码如下]
```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int l, r, val;
};
vector<edge> alle;
vector<int> nodes[2400];
queue<int> bfs_q;
int cost[2400], depth[2400], vis[2400], cur[2400], nxt[2400];
int n, m, s, t, ecn, inf = 2045141919, l, r, k;
int bfs(){
    for(int i = 1; i <= t; i++){
        depth[i] = 0;
        cur[i] = 0;
    }
	bfs_q.push(s);
	depth[s] = 1;
	while(bfs_q.size()){
		int now_node = bfs_q.front();
		bfs_q.pop();
		for(int i = 0; i < nodes[now_node].size(); i++){
			edge e = alle[nodes[now_node][i]];
			if(e.val > 0 && !depth[e.r]){
				bfs_q.push(e.r);
				depth[e.r] = depth[e.l] + 1;
			}
		}
	}
	return depth[t];
}
int dinic(int now_node, int flow){
	if(now_node == t){
		return flow;
	}
	int used = 0, maxn = 0;
	for(int i = cur[now_node]; i < nodes[now_node].size(); i++){
		cur[now_node] = i;
		edge e = alle[nodes[now_node][i]];
		if(e.val != 0 && depth[e.r] - depth[e.l] == 1){	
			int next_flow = dinic(e.r, min(e.val, flow - used));
			if(next_flow){
				alle[nodes[now_node][i]].val -= next_flow;
				alle[nodes[now_node][i] ^ 1].val += next_flow;
				used += next_flow;
                nxt[now_node] = e.r;
			}
			if(used == flow){
				return flow;
			}
		}
	}
	return used;
}
void add_edge(int ll, int rr, int k){
	alle.push_back((edge){ll, rr, k});
	nodes[ll].push_back(ecn);
	ecn++;
	alle.push_back((edge){rr, ll, 0});
	nodes[rr].push_back(ecn);
	ecn++;
}
int status[1200], cnt[1200];
vector<int> ech[12], ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
    s = 2 * m + 1, t = s + 1;
    char op; int v;
	for(int i = 1; i <= m; i++){
        for(int j = 0; j < n; j++){
            cin >> op; v = op - '0';
            status[i] |= (v << j);
        }
        cnt[i] = __builtin_popcount(status[i]);
        ech[cnt[i]].push_back(i);
	}
    for(int i = 1; i <= m; i++){
        add_edge(s, i, 1);
        add_edge(i + m, t, 1);
    }
    for(int i = n; i >= 1; i--){
        for(int j = i + 1; j <= n; j++){
            for(int i_a : ech[i]) for(int i_b : ech[j]){
                if((status[i_a] & status[i_b]) == status[i_a]){
                    add_edge(i_a, i_b + m, 1);
                }
            }
        }
    	while(bfs()) dinic(s, inf);
    }
    nxt[0] = 0;
    for(int i = 1; i <= n; i++){
        for(int j : ech[i]){
            if(nxt[j] == -1) continue;
			int tmp = j;
            ans.push_back(-1);
            for(int k = 0; k < n; k++) if((status[j] >> k) & 1) ans.push_back(k);
            while(nxt[tmp]){
                int k = nxt[tmp] - m;
                int sta = status[k] ^ status[tmp];
                for(int l = 0; l < n; l++) if((sta >> l) & 1) ans.push_back(l);
                nxt[tmp] = -1;
                tmp = k;
            }
            nxt[tmp] = -1;
        }
    }
    cout << ans.size() - 1 << '\n';
    for(int i = 1; i < ans.size(); i++){
        if(ans[i] == -1) cout << "R ";
        else cout << ans[i] << " ";
    }
	return 0;
}
``````
:::

---

