# [NWRRC 2015] Insider's Information

## 题目描述

伊恩在一家评级机构工作，该机构发布最佳大学的评级。艾琳是一名记者，计划撰写一篇关于即将发布的评级的轰动性文章。

通过各种社会工程技术（我们不深入细节），艾琳从伊恩那里获得了一些内部信息。

具体来说，艾琳收到了几个三元组 $(a_{i}, b_{i}, c_{i})$，这意味着在即将发布的评级中，大学 $b_{i}$ 位于大学 $a_{i}$ 和 $c_{i}$ 之间。也就是说，要么 $a_{i}$ 在 $b_{i}$ 之前，$b_{i}$ 在 $c_{i}$ 之前，要么相反。伊恩提供的所有三元组都是一致的——假设实际评级满足它们。

为了开始撰写未来文章的初稿，艾琳需要看到至少某种对实际评级的近似。她要求你找到一个评级提案，其中至少有一半的艾琳已知的三元组得到满足。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 3
1 2 3
1 2 3
1 4 3
```

### 输出

```
4 3 2 1
```

# 题解

## 作者：Le0Chan (赞：6)

UPD：2023.12.13，被 @realskc hack。修了锅。现在可以通过 hack 数据。

好题无人。

从限制入手，每个限制要求 $b_i$ 出现在 $a_i$ 与 $c_i$ 之间。联想到如果对一个 DAG 拓扑排序，对于每条有向边 $u\to v$，$u$ 的拓扑序一定小于 $v$ 的拓扑序。

所以我们对每个限制连两条边。$a_i\to b_i$ 和 $c_i\to b_i$，但是 $b_i$ 的入度只赋为 $1$，这样使得只要有一条边在拓扑排序中被删掉后，$b_i$ 能立刻入队。

但是如果按照所有的限制连边，是有可能出现环的。我们考虑对一个有向**有**环图拓扑排序，实际上成环部分的点集**不可能**加进队列，也就不会更新拓扑序（可以自行造数据模拟）。由于题目保证有解，所以我们忽略环，强行跑拓扑排序。

跑拓扑排序的过程中，我们考虑如何求解。

如果只是将点从左到右加入答案排列，由于每条限制都有两个点向 $b_i$ 连边，所以选择 $a_i$ 在前还是 $c_i$ 在前成了大问题。所以，我们选择**从两边向中间**填满答案序列，对于队列中的一个点 $u$，计算其填在左边还是右边的贡献更大，将其贪心地填进贡献大的一边。

如何计算贡献？这需要分类讨论。

首先枚举 $u$ 充当 $b$ 的所有限制。

- 该限制 $a,c$ 都未确定位置，实际上不存在这种情况，因为不满足在开始所说的拓扑排序的性质。

- 该限制中 $a$ 或 $c$ 确定了位置。先假设是 $a$ 确定了位置，那么 $a,b$ 必须**相同**一边。如果 $a$ 在左，那么 $b$ 必然要放在左，否则后面 $c$ 无论如何放都会成为 $a,c,b$ 的非法情况。$c$ 位置确定的情况类似。

- 该限制中 $a$ 与 $c$ 都确定位置，按上一条分别讨论即可。

其次枚举 $u$ 充当 $a$ 或 $c$ 的所有限制。

- 如果该限制中 $a,c$ 均未确定位置，则给 $b$ 入队。

- 如果该限制中 $a$ 或 $c$ 确定了位置（显然不会是 $u$ ），则 $u$ 要和其在**不同**一边。证明与上述情况类似，注意如果 $b$ 已经确定位置，则该限制能不能满足已经计算过，不能计算贡献。

```cpp

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define N 100005

int n,m;

vector<int> mid[N],sid[N],g[N];
//mid存以i为b的限制编号 
//sid存以i为a或c的限制编号
//g是正常的连边 

int ind[N];//入度 
int a[N],b[N],c[N],pos[N],ans[N];

queue<int> q;//拓扑排序用的队列 

int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i]>>c[i];
        mid[b[i]].pb(i);
        sid[a[i]].pb(i);
        sid[c[i]].pb(i);
        ind[b[i]]++; 
    }
    for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
    int l=1,r=n;//用两个指针从两边向中间填数 
    while(!q.empty()){
        int x=q.front();q.pop();
        int val1=0,val2=0;//分别存将x放左或右的贡献 
        for(int i:mid[x]){//枚举x为b的情况 
        	if(pos[a[i]]&&pos[c[i]]) continue;	
            if(pos[a[i]]){
                if(pos[a[i]]<=l) val1++;//判断已填好的在左边还是右边 
                if(pos[a[i]]>=r) val2++;
            }
            if(pos[c[i]]){
                if(pos[c[i]]<=l) val1++;
                if(pos[c[i]]>=r) val2++;
            }
        }
        for(int i:sid[x]){//枚举x为a或c的情况 
            if(pos[a[i]]&&!pos[b[i]]){
                if(pos[a[i]]<=l) val2++;
                if(pos[a[i]]>=r) val1++; 
            }
            if(pos[c[i]]&&!pos[b[i]]){
                if(pos[c[i]]<=l) val2++;
                if(pos[c[i]]>=r) val1++;
            }
            //如果ac都没填过，那就强行给b入读减一 
            if(!pos[a[i]]&&!pos[c[i]]) if(!--ind[b[i]]) q.push(b[i]);
        }
        if(val1<val2) pos[x]=r--;
        else pos[x]=l++;//贪心地填进左边或右 
        if(l>r) break;
    }
    for(int i=1;i<=n;i++) ans[pos[i]]=i;
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    return 0;
}

```


---

## 作者：比利♂海灵顿 (赞：6)

# NWRRC2015 Insider’s Information

## 题意

对于 $[1, n]$ 的排列，给 $m$ 个限制，第 $i$ 个限制描述 $b_i$ 出现在 $a_i$，$c_i$ 之间。保证存在一个排列满足所有限制。

构造一个 $n$ 的排列至少满足 $\lceil \frac m2 \rceil$ 个限制。

## 分析

每个限制连接两条有向边 $(a_i，b_i)$，$(c_i，b_i)$，因为所有限制都可以被满足，所以在原序列中的端点一定入度为 $0$。

这个图虽然存在环，但是我们对这个图进行拓扑排序，一次删除一个约束的两条边，仍然是可以将所有点入队出队的，但是排序后仅能保证其中每个约束中，$b$ 点不会同时排在 $a$，$c$ 前面。但是这已经足够做此题了。

证明很简单，如果一个 $b$ 的度变成 $0$，一定是它的所有入边都被删除了，所以不存在 $b$ 被删除，$a$，$c$ 都仍未删除的情况。

我们按拓扑序考虑将点加入最左边还是最右边，从两边往中间堆元素，直到填满排列为止。

对于一个约束，第一个放入的如果是 $b$，则无论 $a$，$b$ 怎么放，都不可能满足约束，而我们的拓扑排序不存在 $b$ 第一个放的情况。

如果第一个放的是 $a$ 或 $c$，第二个放的点的位置就决定了该约束是否能满足。

如果第二个放的是 $b$，那么它放在第一个放的元素同侧，则最后一个元素无论怎么放，约束都满足。如果放在异侧，则无论最后一个元素怎么放，约束都不满足。

如果第二个放的是 $a$ 或 $c$ 那么第三个放的一定是 $b$，所以第一个和第二个放的 $a$，$c$ 只要在异侧，约束一定满足，在同侧则一定不满足。

我们对于每个枚举的元素，统计它属于的约束中，有多少次是第二个放的元素，然后统计这些情况中，是放在左端满足的约束多还是放在右端满足的约束多，放到满足约束多的一侧，这样就保证了一定满足 $\lceil \frac m2 \rceil$ 个限制。

## 代码实现

因为每个约束会给 $b_i$ 带来两个入度，而拓扑排序时我们需要给 $b_i$ 减去两个入度，所以为了方便，不如直接用一个入度表示一个约束。

过程中我们一遍拓扑排序一边处理，因为每个点的位置只和已经放入排列中的点有关，所以这样处理也是正确的。

实现还是很短的，指针轻喷。

```cpp
unsigned m, n, M;
unsigned Top(0), Tl(0), Hd(0);
unsigned A, B, C, D, t;
unsigned Cnt(0), Ans[100005], Tmp(0), BdL(0), BdR;
struct Que;
struct Node {
  vector<Que*> Bel; 
  unsigned Deg;
  char Vis, Le;
}N[100005], * Queue[100005];
struct Que {
  Node* Le, * Ri, * Mid;
  Que* Nxt;
}Q[100005];
signed main() {
  BdR = (n = RD()) + 1, m = RD();
  for (unsigned i(1); i <= m; ++i) {
    A = RD(), B = RD(), C = RD(), ++N[B].Deg;
    Q[i].Le = N + A, N[A].Bel.emplace_back(Q + i);
    Q[i].Mid = N + B, N[B].Bel.emplace_back(Q + i);
    Q[i].Ri = N + C, N[C].Bel.emplace_back(Q + i);
  }
  for (unsigned i(1); i <= n; ++i) if(!N[i].Deg) Queue[++Tl] = N + i;
  while (Tl ^ Hd) {//Topo and Solve 
    Node* Cur(Queue[++Hd]);
    unsigned PutLeft(100000);
    Cur->Vis = 1;
    for (auto Prs:Cur->Bel) {
      if(Cur == Prs->Le) {//Cur is A
        if(Prs->Ri->Vis) {//2nd or 3rd
          if(!(Prs->Mid->Vis)) {if(Prs->Ri->Le) --PutLeft; else ++PutLeft;}//2nd Add
        } else if(!(--(Prs->Mid->Deg))) Queue[++Tl] = Prs->Mid;//1st Add
      } else {//Cur is C or B
        if(Cur == Prs->Ri) {//Cur is C
          if(Prs->Le->Vis) {//2nd or 3rd
            if(!(Prs->Mid->Vis)) {if(Prs->Le->Le) --PutLeft; else ++PutLeft;}//2nd Add
          } else if(!(--(Prs->Mid->Deg)))Queue[++Tl] = Prs->Mid; //1st Add
        } else {//Cur is B
          if(!((Prs->Ri->Vis) & (Prs->Le->Vis))) {//2nd Add
            if(Prs->Ri->Vis) {if(Prs->Ri->Le) ++PutLeft;else --PutLeft;}//1st is C
            else {if(Prs->Le->Le) ++PutLeft;else --PutLeft;}//1st is A
          }
        }
      }
    }
    Cur->Le = (PutLeft >= 100000);
    Ans[(PutLeft < 100000) ? (--BdR) : (++BdL)] = Cur - N; 
  }
  for (unsigned i(1); i <= n; ++i) printf("%u ", Ans[i]);
  return Wild_Donkey;
}
```

---

## 作者：steambird (赞：5)

## 思路

题解区的神奇拓扑排序看不懂，怎么办？

目光转向[讨论区](https://www.luogu.com.cn/discuss/745087)，发现前人（感谢 @[N_z_](https://www.luogu.com.cn/user/320087)）留给我们的智慧。然而，我不太会很严谨的证明，部分内容可能只能“粗略估计”一下。如果下面的说明有错误，还望大家批评指正。

我们的思路是：先构造排列 $1,2,\dots,n$，然后随机两个不相等的数 $x,y$，如果交换后能满足更多限制，则进行交换，否则不交换。

我们考虑一次这样的交换平均能多满足多少个限制。这里假设所有限制的两个端点等概率均匀独立随机，先考虑原先一个限制都不满足的情况，则每次的期望贡献为：

$$ \sum_{i=1}^{n-1} {{2i(n-i)} \over {n^2(n-1)}} = {{n+1} \over {3n}} \approx {1 \over 3} $$

也就是说，操作次数的期望大约为 $3m$。考虑原先随机满足了 $k$ 个限制，使得这一期望减少。在最坏情况下，对于单个位置 $i$，期望贡献也只减少大约 ${k \over {n^2}} \le 10^{-5}$，且不可能对每个位置都满足了 $k$ 个限制，故这一减少可以忽略。

接下来考虑如何计算交换产生的贡献。如果每次交换后都判断每个限制是否仍然满足，时间复杂度 $O(m^2)$，不可接受。考虑把这些限制按涉及到的数分类，每次只计算相关限制的贡献。这时，每个数平均分到大约 ${2m} \over n$ 次计算。认为 $n,m$ 同阶，时间复杂度可以降到 $O(n)$，可以通过本题。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

inline void train() {
	   ios::sync_with_stdio(false);
	   cin.tie(0);
	   cout.tie(0);
}

inline int maxi(int a, int b) {
	return a > b ? a : b;
}

inline int mini(int a, int b) {
	return a < b ? a : b;
}

constexpr int N = 100006;
mt19937 ms;
int n,m,pos[N],a[N],sp[N];
vector<int> accu[N];

int as[N], bs[N], cs[N];
bool vis[N], vis2[N];

bool check(int i) {
	return (pos[bs[i]] >= pos[as[i]] && pos[bs[i]] <= pos[cs[i]])
		|| (pos[bs[i]] >= pos[cs[i]] && pos[bs[i]] <= pos[as[i]]);
}

int main() {

	train();
	ms.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
	
	cin>>n>>m;
	uniform_int_distribution<int> cod(1, n);
	for (int i = 0; i < m; i++) {
		cin>>as[i]>>bs[i]>>cs[i];
		accu[as[i]].push_back(i);
		accu[bs[i]].push_back(i);
		accu[cs[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) sp[i] = pos[i] = i;
	int ok = 0;
	for (int i = 0; i < m; i++) if (check(i)) ok++;
	while (ok <= ((m>>1))) {
		int sp1 = cod(ms), sp2 = cod(ms);
		if (sp1 == sp2) continue;
		int p1 = sp[sp1], p2 = sp[sp2];
		int res = 0;
		
		for (auto &i : accu[p1]) {
			if (!vis[i]) {
				if (check(i)) {
					res--;
					vis[i] = true;
				}
			}
		}
		for (auto &i : accu[p2]) {
			if (!vis[i]) {
				if (check(i)) {
					res--;
					vis[i] = true;
				}
			}
		}
		swap(pos[p1], pos[p2]);
		for (auto &i : accu[p1]) {
			if (!vis2[i]) {
				if (check(i)) {
					res++;
					vis2[i] = true;
				}
			}
		}
		for (auto &i : accu[p2]) {
			if (!vis2[i]) {
				if (check(i)) {
					res++;
					vis2[i] = true;
				}
			}
		}
		
		if (res > 0) {
			ok += res;
			swap(sp[sp1], sp[sp2]);
		} else {
			swap(pos[p1], pos[p2]);	
		}
		for (auto &i : accu[p1]) vis[i] = vis2[i] = false;
		for (auto &i : accu[p2]) vis[i] = vis2[i] = false;
	}
	for (int i = 1; i <= n; i++) a[pos[i]] = i;
	for (int i = 1; i <= n; i++) cout<<a[i]<<' ';
	cout<<endl;
	
	//cout<<flush;

	return 0;
}

```

---

