# Best Subsequence

## 题目描述

Given an integer array $ a $ of size $ n $ .

Let's define the value of the array as its size minus the number of set bits in the bitwise OR of all elements of the array.

For example, for the array $ [1, 0, 1, 2] $ , the bitwise OR is $ 3 $ (which contains $ 2 $ set bits), and the value of the array is $ 4-2=2 $ .

Your task is to calculate the maximum possible value of some subsequence of the given array.

## 样例 #1

### 输入

```
4
3
0 0 0
4
1 0 1 2
1
5
8
7 1 48 14 13 8 7 6```

### 输出

```
3
2
0
3```

# 题解

## 作者：BMnya (赞：9)

设 $\operatorname{zerocnt}(x)$ 表示 $x$ 的二进制表示低 $60$ 位中 $0$ 的个数，那么一个集合的价值也可以表示为 $n+\operatorname{zerocnt}(a_1\operatorname{or} a_2\operatorname{or} \dots\operatorname{or} a_n)-60$，这样答案就可以表示为所选数的个数的贡献加上数位中 $0$ 的贡献。

考虑建一张二分图，左部点为 $n$ 个数，右部点为 $60$ 个数位。

如果选择了 $a_i$ 并且 $a_i$ 二进制下第 $j$ 位为 $1$，那么数 $i$ 和数位 $j$ 无法同时产生贡献，那么就连一条 $i\rightarrow j$ 的边；如果这位为 $0$ 那么可以同时产生贡献。

所求最大值为这张图的最大独立集 $-60$，二分图的最大独立集等于点数减去最大匹配数，假设最大匹配为 $mx$，答案即为 $(n+60-mx)-60=n-mx$。

求解二分图最大匹配可以用网络流或者其他做法解决。

---

## 作者：Zeoykkk (赞：4)

# CF2026 E. Best Subsequence

>给定一个大小为 $n$ 的数组 $a$，对于一个长度为 $k$ 的子序列的价值为 $k - bitcount(a_{p_1 } \mid a_{p_2} \mid \dots \mid a_{p_k})$。请你输出 $a$ 的所有子序列中的最大价值。 $n \leq 100, a_i < 2^{60}$。

## Sol：最小割，最大权闭合子图

最大权闭合子图模型，因为一旦选了 $a[i]$，就必须选择 $a[i]$ 二进制位上为 $1$ 的位。考虑最小割求出最小损失，损失分为未被选择的 $a[i]$ 和 被选择的二进制位。

* 源点 $s$ 向每个 $a[i]$ 建流量为 $1$ 的边，如果割了该边代表不选 $a[i]$，所以会损失 $1$ 的价值。
* $a[i]$ 向其二进制位上 $1$ 的位建流量为 $\inf$ 的边，代表该边不可割。
* $0 \sim 59$ 二进制位向汇点 $t$ 建流量为 $1$ 的边，如果割了该边代表存在一个 $a[i]$ 在该位上为 $1$，且被选中，所以该位会产生 $1$ 的损失。

答案即为 $n - \text{MaxFlow}$。

时间复杂度：$O((n + V)^2 nV)$，其中 $V$ 代表二进制位数。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define pb push_back
#define endl '\n'
using ll = long long;
const ll mod = 1000000007;
const ll INF = 1ll << 60;
const int inf = 1 << 30;
const int N = 200010;

int n, bit[70];
ll a[N];

const int V = 2e5 + 10, E = 2e5 + 10; // V 点数， E 边数
template<typename T> // T 代表流量的类型: int / long long 
struct FlowGraph {
    int s, t, vtot;     // s：源点，t：汇点，vtot：图中点的数量
    int head[V], etot;  // 链式前向星
    int dis[V], cur[V]; // dis[u]: u和源点的距离，cur[]：用来当前弧优化保证复杂度
    struct edge {
        int v, nxt; // v：当前边的终点，nxt：下一条边的编号
        T f;        // f：当前边的流量上限，代表当前能从该边流的流量上限
    } e[E << 1];    // 因为存在反向边，所以边数需要开两倍空间
    void addEdge(int u, int v, T f, T f2 = 0) {
        e[etot] = {v, head[u], f}; head[u] = etot++;
        e[etot] = {u, head[v], f2}; head[v] = etot++;
        // e[id ^ 1] 是 e[id] 的反向边
    }
    // 检查有无增广路，并更新 dis, 重置 cur
    bool bfs() {
        for (int i = 1; i <= vtot; ++i) {
            dis[i] = 0;
            cur[i] = head[i];
        }
        queue<int> q;
        q.push(s); dis[s] = 1;
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; ~i; i = e[i].nxt) {
                // 如果一条正向边流量为 0，则我们将该边视为已断开，即 e[i].f = 0
                if (e[i].f && !dis[e[i].v]) { // 如果该正向边还没到流量上限并且没有被遍历过，就代表可以走
                    int v = e[i].v;
                    dis[v] = dis[u] + 1;
                    if (v == t) return true;
                    q.push(v);
                }
            }
        }
        return false; // 代表不存在增广路
    }
    // dfs 多路增广，m 代表剩余流量，初始为正无穷，即从源点流出的流量是无穷大的
    T dfs(int u, T m) {
        if (u == t) return m;
        T flow = 0;
        for (int i = cur[u]; ~i; cur[u] = i = e[i].nxt) { // 当前弧优化，形象的来说就是删除某条无用的边，优化复杂度
            if (e[i].f && dis[e[i].v] == dis[u] + 1) {
                T f = dfs(e[i].v, min(m, e[i].f)); // f：能够从该点流出的流量
                e[i].f -= f; // 正向边流量上限减少
                e[i ^ 1].f += f; // 反向边流量上限增加
                m -= f; // 剩余流量减少
                flow += f;
                if (!m) break; 
                /*
                    流量没有剩余了，直接退出，不能使用当前弧优化
                    因为如果流完这条边之后流量还有剩余(m > 0)，说明通过这条边到汇点的路径已经被堵住了，
                    以后想再通过这条边流点东西过去已经不可能了，所以不需要再经过这条边了，所以可以使用当前弧优化
                */
            }
        }
        if (!flow) dis[u] = -1; // 如果没有收益，代表从经过这个点不会再产生增广路径了，直接删除该点即可，优化复杂度
        return flow;
    }
    T dinic() {
        T flow = 0;
        while (bfs()) flow += dfs(s, numeric_limits<T>::max()); // 如果还有增广路径
        return flow;
    }
    void init(int s_, int t_, int vtot_) {
        s = s_;
        t = t_;
        vtot = vtot_;
        etot = 0;
        for (int i = 1; i <= vtot; ++i) head[i] = -1;
    }
};
FlowGraph<long long> G;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int tot = n;
    for (int i = 0; i < 60; ++i) {
        bit[i] = ++tot;
    }
    int s = tot + 1, t = tot + 2;
    G.init(s, t, t);
    for (int i = 1; i <= n; ++i) {
        G.addEdge(s, i, 1);
        for (int j = 0; j < 60; ++j) {
            if (a[i] >> j & 1) {
                G.addEdge(i, bit[j], inf);
            }
        }
    }
    for (int i = 0; i < 60; ++i) {
        G.addEdge(bit[i], t, 1);
    }
    int ans = n;
    cout << ans - G.dinic() << endl;
}
signed main(void) {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int Test = 1;
    cin >> Test;
    while (Test--) solve();
    return 0;
}
```

---

## 作者：_Ink (赞：2)

最大权闭合子图。

选择一个数字，就必须选择相应的 bit 位。

显然选一个数字会对答案产生 +1 的贡献，选择一个 bit 位会对答案产生 -1 的贡献。即数字的价值为 1，bit 为的价值为 -1。

把数字和 bit 位看成点，建最大权闭合子图模型就做完了。

---

## 作者：ny_jerry2 (赞：0)

## 前言
什么最小割、最大权闭合子图之类的，我不知道啊。就是二分图的最大独立集呀。

## 思路
先考虑每一个数。  
数与数之间互不干扰，数位与数位之间也互不影响。只有数与数位会互相影响。二分图？

建一张二分图，左侧为 $n$ 个数，右侧为 $60$ 个二进制位。考虑连边。如果一个数 $a_i$ 二进制下的第 $j$ 位数为 $1$，会产生负贡献，那就连边。

显然，这是一个最大独立集问题，跑一遍匹配即可。因为每一个点仅会与另外一个点匹配。根据按位或的性质，如果两个数相同二进制位上的数都是 $1$，它还是 $1$，和二分图匹配的特点正好相同。因此没有问题。

## 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int t,n;
const int N=1e5+10;
long long a[N];
int h[N],e[N],ne[N],idx;
void add(int a,int b){
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
int match[N];
bool st[110];
bool find(int x){
    for(int i=h[x];i!=-1;i=ne[i]){
        int j=e[i];
        if(!st[j]){
            st[j]=true;
            if(match[j]==0||find(match[j])){
                match[j]=x;
                return true;
            }
        }
    }
    return false;
}
int main(){
	cin>>t;
	while(t--){
		scanf("%d",&n);
		idx=0;
		for(int i=1;i<=100;i++){
			h[i]=-1,match[i]=0;
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			for(int j=0;j<=60;j++){
				if(a[i]>>j&1){
					add(i,j+1);
				}
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			memset(st,0,sizeof st);
			ans+=find(i);
		}
		cout<<n-ans<<endl;
	}
}
```

---

