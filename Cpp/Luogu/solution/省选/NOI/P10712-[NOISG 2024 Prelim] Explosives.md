# [NOISG 2024 Prelim] Explosives

## 题目背景

翻译自 [NOI SG 2024 Prelim E.Explosives](https://github.com/noisg/noi-2024-prelim)。

## 题目描述

你是一名运送炸弹的卡车司机。

有 $n$ 座工厂（生产炸弹）和 $n$ 座矿井（需要炸弹）排列在一条直线上。第 $i$ 座工厂的坐标为 $a_i$，第 $j$ 座矿井的坐标为 $b_j$。并且，所有 $a_i$ 和 $b_j$ 都均不相等。

你今天需要在每一座工厂各领取一个炸弹，并将每一个炸弹送到某一个矿井中。初始时，你的坐标为 $0$。为了完成此任务，你可以进行以下两种操作：

- `pickup(x)`：从你当前的位置驾驶卡车到坐落在 $x$ 的工厂。执行这次操作需要同时满足以下两个条件：

	- 有一个 $i$，满足 $x=a_i$。
    
   - 你的卡车最多装了 $c-1$ 个炸弹。
   
- `offload(x)`：从你当前的位置驾驶卡车到坐落在 $x$ 的矿井。执行这次操作需要同时满足以下两个条件：

	- 有一个 $j$，满足 $x=b_j$。
    
   - 你的卡车最少装了 $1$ 个炸弹。
   
由于炸弹十分危险，所以在你的卡车上需要一名安全员。如果你从点 $x$ 到点 $y$，且车上装有炸弹，那么你需要付给安全员 $|x-y|$ 元。如果车上没有炸药，则你不需要支付任何费用。

请求出在花费最小的情况下的操作序列。

## 说明/提示

### 【样例 #1 解释】

按照顺序访问工厂 $3$，矿井 $2$，工厂 $2$，工厂 $1$，矿井 $1$，矿井 $3$，即可得到最小值 $7$。

以此样例为例，如果你只输出正确的最小代价 $7$，你将可以得到该测试点 $50\%$ 的分数。

### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$16$|$c=1$|
|$2$|$22$|$a_i\le 5000,b_i>5000$|
|$3$|$62$|无|

对于 $100\%$ 的数据，$1 \le n,c \le 1000,1 \le a_i,b_i \le 10000$。

## 样例 #1

### 输入

```
3 2
12 14 4
9 5 8
```

### 输出

```
7
4 5 14 12 9 8```

# 题解

## 作者：船酱魔王 (赞：12)

## 题意回顾

$ n $ 球 $ n $ 洞，你的铲车能装最多 $ c $ 个小球且禁止在洞外放置小球，一个洞只能容纳最多一个小球请问让每个球进洞的代价最小是多少并构造运输方案。

运输的代价为你装载至少一个球的总里程。

$ 1 \le n,c \le 1000 $。

## 分析

### 初步想法

本题是我校一次校内 CSP-S 备赛练习的第四题，分析题面后我初步判断这道题可能是动态规划，还需要一定贪心优化思想，故从简单情况考虑贪心方法再行设计。

### Task 1：$ c=1 $（16 分）

这个问题可以转化为，一条线上有一些红点和蓝点，一一配对连线的最小总连线长度是多少。

考虑两个相邻的点之间，如果这条线段左面（含边界）蓝点和红点差值为 $ x $，则必然会有至少 $ x $ 个点配对需要跨过这条线段。

考虑如何达到这个最优解？红点蓝点排序后一一对应。此时对于每个这样的线段，左侧红点蓝点可以尽量互相“抵消”，此时只会有差值个点越过这条线段连线。

故排序 $ a,b $ 数组后一一输出即可。

### Task2：$ a_i \le 5000,b_i > 5000 $（22 分）

下文中，记 $ a,b $ 为从小到大排序后的数组。

沿用 Task1 的思路，$ |b_1-a_n| $ 会被跨越过 $ \lceil \frac{n}{c} \rceil $ 次。

考虑在这 $ \lceil \frac{n}{c} \rceil $ 次运输中，第 $ i $ 次最左侧的球号为 $ t_i $，最右侧的洞号为 $ s_i $。

故答案为 $ \sum |-a_{t_i}+b_{s_i}| = \sum b_{s_i} - \sum a_{t_i} $。

因此，我们要尽量让每个 $ b_{s_i} $ 和 $ -a_{t_i} $ 最小，即尽量最小化 $ s_i $ 最大化 $ t_i $，考虑从小到大排序 $ t $ 数组，从大到小排序 $ s $ 数组，此时 $ s_1=n,t_1=1 $，考虑 $ t_i $ 的最大值为 $ t_i=1+(i-1)c $，$ s_i $ 的最小值为 $ s_i=n-(i-1)c $，因为必须取完 $ a_2 \sim a_{t_2-1} $ 才能使得 $ t_2 $ 为之后最靠左的球点号，$ s $ 数组同理。取到最优方案的方法是每次取最靠左最靠右的最多 $ c $ 个点匹配。

### Task3A：求出最小花费（31 分）

考虑沿用 Task1 的思路，两个相邻点之间的线段被覆盖的次数最小值为左侧红蓝点差值 $ x $ 计算出 $ \lceil \frac{x}{c} \rceil $ 的值。

故答案为 $ \sum x_i(d_{i+1}-d_i) $，$ d_i $ 为线段 $ i $ 左侧点的坐标。

### Task3B：求出最优方案（31 分）

考虑设计最优的方案，取到这个下界，对于一次运输，设方向为左到右（$ x_i $ 为负的话反过来就行了），则需要尽量保证对于所有非负的 $ x_i $，能运完就运完，否则跨过这条线段运 $ c $ 个球。求出运输量 $ \Delta x_i $ 判断两个相邻的线段之间是否运输量相等即可推出中间的点要不要运输（载货或卸货）。

如果 $ x_i \le c $，那么之前可以运输的必然在范围内都运输完了；否则之前必然有至少 $ c $ 个球被运过去，也能使得答案取到最小值。且 $ x_i $ 相邻差一，必然载货和卸货是互相匹配的。

暴力处理并输出即可，时间复杂度为 $ O(n^2) $。

自此，本算法期望得到本题的所有分数。

### Task4：可以加强吗？

考虑本题需要维护的操作：
* 全局操作 $ x_i \leftarrow \max\{0,x_i-c\} $。
* 寻找 $ 0 < x_i \le c $ 的位置，并输出。

可以线段树维护区间还有效的 $ x_i $ 的最小值，均摊复杂度为 $ O(n \log n) $。

复杂度证明：对于一个区间，若全局超过 $ c $ 则可以打标记，对于所有需要往下检查的结点都是由小于等于 $ c $ 变为 $ 0 $ 的，故每个结点最多被检查一次，时间复杂度上限为 $ O(n \log n) $。

数据范围可以支持到 $ n,c \le 10^6 $。

### 总结

本题是一道一维空间上的类哈密顿问题，处理这种问题可能需要找到一些最小化的放缩方法，再考虑能否取到下界。

对于（类）哈密顿问题，除了通用问题下的状压 DP，如果问题求解在树或数轴这种复杂度小于二维平面的结构可以考虑贪心并放缩证明下界，如果求解在标准二维结构复杂度及以上的结构上的话考虑依据结构特点设计动态规划。

对于一维结构（或准一维结构），我们经常使用区间动态规划完成，实例是 2023 年 NOI 春季测试的任务三。

从本题的思考流程上，先是由最简单的方法想到计算每个间隔段对答案的次数贡献，再由跨过中线的任务想到最小化贡献的思路，通过实现来输出最小化答案的方案。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
const int N = 1005;
int n, c;
int a[N], b[N];
pair<int, int> pr[N * 2];
int p[N * 2];
int e[N * 2];
int ans = 0;
vector<int> vec;
int main() {
	scanf("%d%d", &n, &c);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pr[i] = (pair<int, int>){a[i], 1};
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]), pr[n + i] = (pair<int, int>){b[i], -1};
	sort(pr + 1, pr + 2 * n + 1);
	int pre = 0;
	for(int i = 1; i <= 2 * n; i++) {
		pre += pr[i].second;
		p[i] = pre;
	}
	for(int si = 1; si <= n; si++) {
		int ok = 0;
		for(int i = 1; i <= 2 * n; i++) {
			ok += (p[i] <= 0);
			if(p[i] <= 0) e[i] = 0;
			else e[i] = min(p[i], c), p[i] = max(p[i] - c, 0);
		}
		if(ok == 2 * n) break;
		for(int i = 1; i <= 2 * n; i++) {
			ans += (int)(e[i] > 0) * (pr[i + 1].first - pr[i].first);
			if(e[i] != e[i - 1]) vec.push_back(pr[i].first);
		}
	}
	for(int si = 1; si <= n; si++) {
		int ok = 0;
		for(int i = 1; i <= 2 * n; i++) {
			ok += (p[i] == 0);
			if(p[i] == 0) e[i] = 0;
			else e[i] = min(-p[i], c), p[i] = min(p[i] + c, 0);
		}
		if(ok == 2 * n) break;
		for(int i = 2 * n; i >= 1; i--) {
			ans += (int)(e[i] > 0) * (pr[i + 1].first - pr[i].first);
			if(e[i] != e[i - 1]) vec.push_back(pr[i].first);
		}
	}
	printf("%d\n", ans);
	for(int i = 0; i < vec.size(); i++) printf("%d ", vec[i]);
	puts("");
	return 0;
}
```

---

## 作者：phigy (赞：4)

## 前言

感觉 @船酱魔王 的题解写的有些刻晴了。

也有可能我的做法是假的。

## 正文

不妨将炸弹运输理解为工厂和矿洞进行了匹配，然后每一对之间的路径每个单位长度要运输的炸弹数量就 $+1$，此时很明显有答案下界就是对每个单位长度的炸弹数量除 $c$ 向上取整求和，后面我将构造证明可以取到此下界。

我们先考虑如何匹配是最优的，结论是括号匹配是最优的，因为对于一个单位长度它的炸弹数量也有下界，就是左侧工厂和矿洞的差，而括号匹配能取此下界，至此我们就能算出最优解了。

考虑构造，有些炸弹是向右运的，而有些是向左的，注意到两种运输路径肯定是不交的，因此我们可以完全分开考虑，这样构造就是简单的了，由于括号对呈树形结构，直接按 $dep$ 每 $c$ 层分一组顺着运即可，复杂度是 $O(n\log n)$。

懒，所以写的 $O(n^2)$。


```cpp
#include <bits/stdc++.h>

#define i64 long long

const int REN=1000,MAXN=REN+5;

using namespace std;

int n,m;
struct node {int x,y,z;} a[MAXN*2];
int vis[MAXN*2];
signed main()
{
    int i,j,k;
    cin>>n>>m;
    for(i=1;i<=n;i++) {cin>>a[i].x;}
    for(i=1;i<=n;i++) {cin>>a[i+n].x;a[i+n].y=1;}
    sort(a+1,a+n*2+1,[&](node A,node B){return A.x<B.x;});
    int now=0,ans=0;
    stack<int>st;
    for(i=1;i<=2*n;i++)
    {
        if(i>1&&now) {ans+=((abs(now)-1)/m+1)*(a[i].x-a[i-1].x);}
        if(!a[i].y) {now--;} else {now++;}
        if(st.empty())            {st.push(i);continue;}
        if(a[st.top()].y!=a[i].y) {a[i].z=st.top();st.pop();}
        else                      {st.push(i);}
    }
    vector<int>vec;
    int fl=1;
    while(fl)
    {
        fl=0;
        vector<int>tmp;
        now=0;
        for(i=1;i<=2*n;i++)
        {
            if(vis[i]) {continue;}
            fl=1;
            if(!now)                       {now++;tmp.push_back(i);vis[i]=1;continue;}
            if(a[i].y==a[tmp[0]].y&&now<m) {now++;tmp.push_back(i);vis[i]=1;}
            else if(vis[a[i].z])           {now--;tmp.push_back(i);vis[i]=1;if(!now) {break;}}
        }
        if(tmp.size())
        {
            if(a[tmp[0]].y==1) {reverse(tmp.begin(),tmp.end());}
            for(int x:tmp) {vec.push_back(x);} 
        }
    }
    cout<<ans<<'\n';
    for(int x:vec) {cout<<a[x].x<<' ';}
    return 0;
}
```

---

## 作者：OsanaiYuki (赞：2)

#### P10712 [NOISG 2024 Prelim] Explosives

> 有 $n$ 个 A 类点和 $n$ 个 B 类点，点的位置各不相同。每个 A 类点有一个炸弹，你要运输炸弹使得最终每个 B 类点有一个炸弹。出于安全原因，车上同一时刻最多有 $c$ 个炸弹。当你的车上有炸弹时，每运输 $1$ 单位距离就要付费 $1$ 元。求最小代价。$1 \leq c \leq n \leq 10^3$，$1 \leq a_i, b_i \leq 10^4$。

$c = 1$ 是经典的贪心：考虑 $a_1 < a_2$，$b_1 < b_2$，则让 $(a_1, b_1) (a_2, b_2)$ 分别匹配一定不劣。另一个部分分形如 $a_i \leq 5000$，$b_i > 5000$，则每次相当于取走最小的 $c$ 个 A 类点坐标，和最大的 $c$ 个 B 类点坐标匹配，证明是容易的。**于是我们能够发现相交关系是不如包含关系的**。

尝试推广整个问题，首先我们每次解决一个极短但非空的首尾 $cnt(a) - cnt(b)$ 前缀和等于 $0$ 的区间，这个区间内所有炸弹的移动方向都必须相同，这是因为所有区间总是独立。于是「最多同时有 $c$ 个炸弹」可以被描述为 **建出括号树后**，取所有层数恰好是 $c$ 的倍数的区间长度并统计答案。时间复杂度 $\mathcal O(n)$。

---

## 作者：Otomachi_Una_ (赞：2)

考虑怎么算最小代价。假设 $s_i$ 表示 $i$ 前面的炸弹个数减去矿洞个数。然后你可以猜最小代价是 $f(s)=\sum \lceil\frac {s_i}{c}\rceil$。然后获得了 50 分。

考虑怎么构造。我们先对 $a_i,b_i$ 排序。我们对 $a_i<b_i$、$a_i>b_i$ 的部分分开处理（两个部分的区间不会相交）。

我们考虑对 $a_i<b_i$ 构造。我们希望我们走 $1$ 的代价，$f(s)$ 就减少 $1$。

考虑枚举 $i=n,n-1,\dots,1$。每次我们对 $\lceil\frac {s_j}{c}\rceil=i$ 的所有 $j$ 进行推平到 $i-1$。即我们想让 $s_j$ 最少减少至 $(i-1)c$。

完成这个任务其实很简单。从小到大走满足条件的 $j$。走到炸弹就装上，走到矿洞就丢进去。当我们走出这个 $j$ 的合法区间时，我们这个时候车上也必然时没有炸弹的。

由于 $s_j\in[ic,(i+1)c)$，所以我们卡车容量是不会爆的。其次我们确实把 $s_{j}$ 给铲平了，我们除掉了里面的所有元素。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=1005;
int n,m,c,a[MAXN],b[MAXN];
int d[MAXN*10],ans;vector<int> vec;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	// freopen("Otomachi_Una.in","r",stdin);
	// freopen("Otomachi_Una.out","w",stdout);
	cin>>n>>c;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	sort(a+1,a+n+1);sort(b+1,b+n+1);m=max(a[n],b[n]);
	for(int i=1;i<=n;i++) if(a[i]<b[i]) d[a[i]]++,d[b[i]]--;
	for(int i=n;i>=0;i--){
		int k=0,s=0;
		for(int j=1;j<=m;j++){
			if(k) ans++;s+=d[j];if(s<=i*c&&!k) continue;
			if(d[j]>0&&k<c) vec.push_back(j),d[j]=0,k++;
			if(d[j]<0&&k) vec.push_back(j),d[j]=0,k--;
		}
	}
	for(int i=1;i<=n;i++) if(a[i]>b[i]) d[a[i]]++,d[b[i]]--;
	for(int i=n;i>=0;i--){
		int k=0,s=0;
		for(int j=m;j>=1;j--){
			if(k) ans++;s+=d[j];if(s<=i*c&&!k) continue;
			if(d[j]>0&&k<c) vec.push_back(j),d[j]=0,k++;
			if(d[j]<0&&k) vec.push_back(j),d[j]=0,k--;
		}
	}
	cout<<ans<<'\n';
	for(int i=0;i<2*n;i++) cout<<vec[i]<<" \n"[i==2*n-1];
	return 0;
}
```

---

