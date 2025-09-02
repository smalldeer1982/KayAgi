# [NordicOI 2023] Ice Cream Machines

## 题目背景

翻译自 [NordicOI 2023 B 题](https://noi23.kattis.com/contests/noi23/problems/icecreammachines) Ice Cream Machines。

## 题目描述

在你的冰淇淋店里有 $n$ 个顾客在排队，店里一共有 $m$ 种口味，每个人都有想买的口味，但是很不幸，店内只有 $k$ 台机子，无法完全供应所有的口味，所以，如果下一个人要的和这台机子内原有的口味不同时，他需要清洗这台机子并更换成他喜欢的口味。

现在这 $n$ 个人按照从 $1 \sim n$ 的顺序买冰淇淋，你作为一个聪明绝顶的店主需要合理安排他们使用哪台机子，使得清洗机子的次数最少，输出这个最少次数。

注意一台机子如果之前没人用的时候默认需要被清洗（自始至终没人用则不需要）。

## 说明/提示

**本题采用捆绑测试**。

- Subtask 1（7 points）：$n \le 1000$，$m \leq 10$，$k = 1$。
- Subtask 2（12 points）：$n \le 1000$，$m \leq 10$，$k \leq 2$。
- Subtask 3（22 points）：$n \leq 1000$，$m \leq 10$，$k \leq 5$。
- Subtask 4（11 points）：$n \leq 1000$，$m \leq 200$，$k \leq 100$。
- Subtask 5（14 points）：$n \leq 2 \times 10^5$，$m \leq 500$，$k \leq 100$。
- Subtask 6（13 points）：$n \leq 2 \times 10^5$，$m \leq 2 \times 10^5$，$k \leq 100$。
- Subtask 7（21 points）：无特殊限制。

对于所有测试数据，$1 \le n \le 2\times 10^5$，$1 \leq m \leq 2 \times 10^5$，$1 \leq k \leq 2 \times 10^5$，$1 \leq c_i \leq m$。

## 样例 #1

### 输入

```
8 3 1
2
3
3
1
2
1
1
3```

### 输出

```
6```

## 样例 #2

### 输入

```
8 3 2
2
3
3
1
2
1
1
3```

### 输出

```
4```

# 题解

## 作者：ChampionCyan (赞：5)

# P10647 题解

## 前言

这道题和[果汁店的难题](https://www.luogu.com.cn/problem/P2088)很像，但数据大小差异巨大。同时果汁店的难题的机器如果以前没有使用过无需清洗直接可以使用，这道题则不行。

## 朴素做法

贪心即可

**注意到客人的请求是有序的，即不能直接 sort。**

很明显，若制作时已经有相同口味的机器，一定使用这台机器。

若没有相同口味的，看有无新机器，有则一定使用。若清洗已经用过的机器，可能这个机器将来还会用到，即使不会，用新机器也一定是最优解之一，因为后来没有新机器之后也能再清洗以后用不着的那个机器。

若没有新机器，看有无后来不用了的机器，有则一定清洗那个机器，因为后来不用因为这次清洗产生额外清洗量。

若以上条件均不满足，就进入到了整个题目最重要的一步。

**一定清洗最晚有需求的那个。**

### 证明：

定义**少清洗量**为无需清洗就能制作的冰淇淋数量。

根据条件（即前面的假设都不符合），若清洗最晚有需求的那个，则**少清洗量**至少为 $k-1$，因为既然清洗的是清洗最晚有需求的那个，那么其他机器在它有需求之前至少有一次需求。

若不选择它，则**少清洗量**一定小于清洗最晚有需求的那个的**少清洗量**，因为最晚有需求的那个再次之前，根据定义，不可能有需求，因此**少清洗量**就少了最晚有需求的那个在下次使用之前对新选择的另一个的需求量。

根据题目要求，**少清洗量越大越好**，因此我们的选择一定最优。

### 朴素代码

贴上朴素代码（79pts）：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
int m, k, n, ans = 0;
queue<int> pos[MAXN];
bool has[MAXN];
int mac[MAXN], use = 0;
int ice[MAXN], where;

void an_pai(int x) {
	pos[x].pop();
	if (!has[x]) {
		ans++;
		if (use < k) {
			mac[++use] = x;
			has[x] = true;
			return;
		}
		int far = 0, bes;
		for (int i = 1; i <= use; i++)
			if (pos[mac[i]].empty()) {
				has[mac[i]] = false;
				has[x] = true;
				mac[i] = x;
				return ;
			} else if (far < pos[mac[i]].front())
				far = pos[mac[i]].front(), bes = i;
		has[mac[bes]] = false;
		mac[bes] = x;
		has[x] = true;
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		pos[x].push(i);
		ice[i] = x;
	}
	for (where = 1; where <= n; where++)
		an_pai(ice[where]);
	printf("%d", ans);
	return 0;
} 
```

## 优化

不难看出朴素解法的时间复杂度是 $O(n)\sim O(nk)$ 的，T 了最后一个点。

我们对下一次需求的时间进行**大顶堆**维护即可。为方便，若没有下一次需求，将其设为极大值即可。

### 码

code（与朴素版本差别巨大）：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
priority_queue<pair<int, int> > h;
int a[MAXN], nex[MAXN], mac[MAXN], cnt, ans, n, m, k;
bool has[MAXN];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		nex[i] = n + 1;
		scanf("%d", a + i);
		nex[mac[a[i]]] = i;
		mac[a[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		if (has[a[i]]) {
			h.push(make_pair(nex[i], a[i]));
			continue;
		}
		if (cnt == k) {
			int bes = h.top().second;
			has[bes] = false;
			h.pop();
			cnt--;
		}
		h.push(make_pair(nex[i], a[i]));
		has[a[i]] = true;
		cnt++;
		ans++;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：ycy1124 (赞：2)

[双倍经验。](https://www.luogu.com.cn/problem/P3419)[三倍经验。](https://www.luogu.com.cn/problem/CF802B)
### 题意
有 $n$ 个人按顺序来吃冰淇淋，店里一共有 $m$ 种口味的冰淇淋和 $k$ 台机子。每台机子切换一次口味就要清洗一次，试问最小的清洗次数。
### 思路
根据贪心，是不可能同时有一样口味的机子的。考虑每次加入一个没有机子能立马生产的口味的情况。此时如果有机子没用，那么清洗这台还没用的机子是最优的。

证明：此时如果更换一台机子的口味，那么之后遇到这种口味时一定要清洗一次，而此时新开一台机子不用，所以这样做一定是最优的。

接下来考虑没有新机子的情况。此时我们发现当前所有口味的机子他们下一次使用的时间是互不相同的，我们为了使其带来的影响最小，所以考虑清洗下一次使用最晚的机子。

证明：假如此次清洗了一台不是最晚的机子，那么在这台最晚的机子使用下一次的时间里，肯定还要为了刚清洗的机子的口味再清洗一次，所以每次清洗下一次最晚使用的机子一定是不劣的。

对于如何维护最晚使用下一次的机子，我们可以使用堆。需要注意的是，当没有机子清洗的情况下，还是有机子下一次的使用时间会变，所以我们需要记录每台机子在堆中的位置来更改。（本人使用的手写堆，优先队列另当别论）
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
    int color;
}b[200005];
int n,k,tot,p,ans,qwq[200005],a[200005],nex[200005],color[200005];//qwq记录下一次每种口味使用的时间，color先处理每个位置下一次的使用再记录每种口味在堆中的位置
bool bj[200005];//记录是否有这种口味的机子
inline bool pd(int x,int y){
    return qwq[b[x].color]<qwq[b[y].color];//判断哪一个下一次的使用时间在后
}
inline void work1(int x){
    if(x*2+1<=tot&&pd(x,x*2+1)&&pd(x*2,x*2+1)){
        swap(b[x],b[x*2+1]);
        swap(color[b[x].color],color[b[x*2+1].color]);
        work1(x*2+1);
    }
    else if(x*2<=tot&&pd(x,x*2)){
        swap(b[x],b[x*2]);
        swap(color[b[x].color],color[b[x*2].color]);
        work1(x*2);
    }
}
inline void work(int x){
    if(x!=1&&pd(x/2,x)){
        swap(b[x],b[x/2]);
        swap(color[b[x].color],color[b[x/2].color]);//交换口味在堆中的位置
        work(x/2);
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>p>>n>>k;
    for(int i=1;i<=p;i++){
        cin>>a[i];
        if(color[a[i]]){
            nex[color[a[i]]]=i;
        }
        color[a[i]]=i;
    }
    for(int i=1;i<=p;i++){
        if(nex[i]==0){//当没有下一次使用时默认下一次使用时间为无限大
            nex[i]=1e9;
        }
        if(bj[a[i]]){//当没有机子需要清洗时这种口味的机子下一次使用的时间还是会变
            qwq[a[i]]=nex[i];
            work(color[a[i]]);//下一次使用时间只可能增大，所以往堆顶走
        }
        else{
            ans++;
            qwq[a[i]]=nex[i];
            if(tot<k){//有空机子
                b[++tot]={a[i]};
                color[a[i]]=tot;//记录位置
                work(tot);
                bj[a[i]]=1;
            }
            else{
                bj[b[1].color]=0;//这种口味的机子被清洗了
                bj[a[i]]=1;
                swap(color[b[1].color],color[b[tot].color]);
                swap(b[1],b[tot]);
                --tot;//丢出堆顶
                work1(1);
                b[++tot]={a[i]};
                color[a[i]]=tot;
                work(tot);
            }
        }
    }
    cout<<ans;
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/198465386)

---

## 作者：Yan719 (赞：1)

# [洛谷 P10647](https://www.luogu.com.cn/problem/P10647)

对于每一个客人，我们将其分为两种情况考虑：

- 如果存在某台机子的口味和当前的需求相同，就直接使用。
- 否则，我们肯定希望所造成的影响最小，那么就直接选择下一个出现位置最靠后的机子清洗。

用一个优先队列维护即可。

```cpp
#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int N = 2e5 + 10;

struct Node {
    int cnt, col, nxt;
    bool operator < (const Node &i) const {
        return nxt == i.nxt ? cnt > i.cnt : nxt < i.nxt;
    }
};

int n, m, k, a[N], cnt[N], ans;
bool f[N];
priority_queue<Node> pq;
vector<int> pos[N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++;
    for (int i = 1; i <= m; i++) pos[i].push_back(n + 1);
    for (int i = n; i >= 1; i--) pos[a[i]].push_back(i);
    for (int i = 1; i <= k; i++) pq.push({0, 0, n + 1});
    for (int i = 1; i <= n; i++) {
        cnt[a[i]]--, pos[a[i]].pop_back();
        if (f[a[i]]) {
            pq.push({cnt[a[i]], a[i], pos[a[i]].back()});
            continue;
        }
        while (!pq.empty()) {
            auto [ct, col, nxt] = pq.top(); pq.pop();
            if (ct != cnt[col]) continue;
            f[col] = 0, f[a[i]] = 1, ans++;
            pq.push({cnt[a[i]], a[i], pos[a[i]].back()});
            break;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：yx666 (赞：1)

# P10647 Ice Cream Machines 题解
## Part 1：题意
店里一共有 $m$ 种口味，有 $n$ 个顾客按照从 $1 \sim n$ 的顺序买冰激凌，每个人的口味是 $c_i$。

但是店内只有 $k$ 台机子，无法完全供应所有的口味。所以，如果下一个人要的和这台机子内原有的口味不同时，需要清洗这台机子并更换成他喜欢的口味。

你作为店主，需要合理安排使用机子顺序，使得清洗机子的次数最少，输出这个最少次数。

对于所有测试数据，$1 \le n \le 2\times 10^5$，$1 \leq m \leq 2 \times 10^5$，$1 \leq k \leq 2 \times 10^5$，$1 \leq c_i \leq m$。

## Part 2：算法
贪心（来得有点陡，不要介意）。

### Part 2.1：贪心策略
先考虑最简单的：如果有一台机子和当前的口味相符，那么就使用这台机子。

再考虑：如果没有一台机子和当前的口味相符呢？

可以证明，如果可以新增机子，那么就新增；反之，就去找一个影响最小的机子（该机子对应的口味的下一个需求距当前最远或没有）清洗。

证明在文末。

### Part 2.2：代码
策略看起来干巴巴的，这里展示一下核心代码（快读省略，主函数声明省略）。

``` cpp

#define N 200005
#define M 200005
#define K 200005

int n,m,k,ans=0;

int a[N];				// a[i] 表示第 i 个需求
int cnt=0,mac[M];		// cnt 表示使用了 cnt 台机器；mac[i] 表示第 i 台机器制作口味
queue<int>q[K];			// q[i] 表示第 i 种口味位置
bitset<K>made;			// made[i] 表示是否有机子制作第 i 种口味

for(int i=1;i<=n;++i){
	a[i]=read();
	q[a[i]].push(i);
}
for(int i=1;i<=n;++i){
	int x=a[i];
	q[x].pop();
	
	if(made[x])			// 有相符的机子
		continue;
	made[x]=1;
	++ans;
	
	if(cnt<k){			// 还能增加就增加
		mac[++cnt]=x;
		continue;
	}
	
	int p=0,far=0;
	bool fg=1;
	for(int j=1;j<=cnt;++j){
		int t=mac[j];		// 当前的机子对应的种类
		if(q[t].size()){	// 这个种类还有需求
			if(far<q[t].front()){	//（目标是找到需求最远的种类及位置）
				far=q[t].front();
				p=j;
			}
		}else{		// 这个种类没有需求，选这台机子是最优的
			mac[j]=x;
			fg=0;
			break;
		}
	}
	if(fg){
		made[mac[p]]=0;
		mac[p]=x;
	}		
}
```

### Part 2.3：优化
交上去，发现 TLE 最后一个点。

实际上，上面的代码复杂度是 $O(nk)$ 的，过不了 $1 \le n \le 2\times 10^5$，$1 \leq k \leq 2 \times 10^5$。

分析一下，瓶颈在找最大值，一次是 $O(k)$ 的，考虑大根堆优化。

### Part 2.4：优化策略
定义 $pos_i$ 表示第 $i$ 种口味的最后一次出现位置（类似于链表尾指针），$nxt_i$表示第 $i$ 个位置上的口味下一次出现位置（链表）。

仿照链表，得到输入：

``` cpp
fill(nxt,nxt+n+1,n+1);

for(int i=1;i<=n;++i){
	c[i]=read();
	nxt[pos[c[i]]]=i;
	pos[c[i]]=i;
}
```

对应的，贪心写成这样（自认为注释详细，不再赘述）

``` cpp
#define pii pair<int,int>

#define N 200005
#define M 200005
#define K 200005

int n,m,k,ans=0;

int c[N];				// c[i] 表示第 i 个需求口味
int cnt=0;				// cnt 表示使用了 cnt 台机器
int pos[M];				// pos[i] 表示第 i 种口味的最后一次出现位置（链表尾指针）
int nxt[M];				// nxt[i] 表示第 i 个位置上的口味下一次出现位置（链表）
bitset<K>made;			// made[i] 表示是否有点位制作第 i 种口味
priority_queue<pii>q;

for(int i=1;i<=n;++i){
	int t=c[i];
	if(made[t]){				// 如果有相符的
		q.push({nxt[i],t});		// 存入下一个出现位置（可以不 pop，因为当前的 nxt[i] 一定大于之前的出现位置 i）
		continue;
	}
	if(cnt==k){					// 增加不了机子，那么找距现在最远的点，空出一台机子
		int p=q.top().second;q.pop();
		made[p]=0;
		--cnt;
		// 注意没有 continue，因为这一步是空出机子，并没有制作
	}
	// 增加一个机子
	++cnt,++ans;
	q.push({nxt[i],t});
	made[t]=1;
}write(ans);
```

### Part 2.5：最终代码
把上面的代码稍加改动，塞进主函数即可。

[AC 记录 rnk 1](https://www.luogu.com.cn/record/163756479)，里面 $a,pre$ 对应 $c,nxt$。

## Part 3：贪心证明
> 1. 当没有一台机子和当前的口味相符，如果可以新增机子，那么就新增。

显然，新增和清洗一台都耗费 $1$ 次，新增一台可以增加下一次有相符的可能性，所以选择增加一台。


> 2. 当没有一台机子和当前的口味相符，也不可以新增机子，就去找一个影响最小的机子（该机子对应的口味的下一个需求距当前最远或没有）清洗。

这样想：现在只能选择清洗了，就去找一个**影响最小**的机子清洗。

什么叫**影响最小**呢？

1. 当这个机子对应的口味的下一个需求没有（只会一直空着）。

2. 当这个机子对应的口味的下一个需求是所有机子中对应的距离现在最远的（这台机子闲的时间最久）。

## Part 4：结语
一道不错的贪心题。

如果有叙述不清，还请私信赐教。

---

## 作者：junee (赞：1)

# P10647 题解

## 前置知识

贪心，堆

## 题目分析

对于每一种味道，求出下一次出现的位置。当目前使用的个数小于总个数，则直接使用；否则，将最远的踢出，即先解决近处的，再解决远处的。

当遇到之前出现过的，将之前的距离更新为现在此点相同味道下次出现的距离。

## Code

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
const int N=2e5+10;
typedef pair<int,int>PII;
int n,m,k;
int a[N],nex[N],pre[N],b[N];
priority_queue<PII>q;
int ans=0,sz=0;
int main(){
    cin>>k>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        nex[pre[a[i]]]=i;
        pre[a[i]]=i;
    }
    for(int i=1;i<=n;i++)if(!nex[i])nex[i]=0x3f3f3f3f;
    for(int i=1;i<=n;i++){
        if(b[a[i]]){
        	q.push({nex[i],a[i]});
        	continue;
		}
        if(sz==k)b[q.top().second]=0,q.pop(),sz--;
        b[a[i]]=1;
        q.push({nex[i],a[i]});
        ans++,sz++;
    }
    cout<<ans-k;
    return 0;
}
```

---

