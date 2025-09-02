# 【MX-S4-T2】「yyOI R2」youyou 不喜欢夏天

## 题目背景

原题链接：<https://oier.team/problems/S4B>。

## 题目描述

youyou 有一个大小为 $2 \times n $ 的网格，每个格子可能是黑色或者白色。

现在 youyou 和 yy 要在这个网格上玩一个游戏：

- youyou 先选取出一个可以为空的**连通块**。
- 之后 yy 可以选择网格中最多 $m$ 列，将这些列上下行的格子颜色互换。

定义一个格子集合 $S$ 为一个连通块，当且仅当 $S$ 中任意两个格子可以通过集合 $S$ 内**边相邻**的若干个格子连通（即四连通）。

youyou 希望最大化最终连通块中黑色格子减白色格子的数量，而 yy 希望最小化之。

现在 youyou 希望你求出：在双方都采用最优策略的情况下，最终连通块黑色格子减白色格子的数量是多少？


## 说明/提示

**【样例解释 \#1】**

下文中记 $(x,y)$ 表示第 $x$ 行第 $y$ 列的格子。

对于第一组数据，youyou 选择 $(1,2)$ 和 $(2,2)$ 两个格子，无论 yy 怎么交换，最终黑色格子和白色格子数量的差至少为 $2$。可以证明没有更优的解。

对于第二组数据，youyou 选择 $(1,1),(1,2),(1,3),(1,4),(2,4),(2,5),(2,6),(2,7)$ 八个格子，无论 yy 怎么交换，最终黑色格子和白色格子数量的差至少为 $4$。可以证明没有更优的解。

**【样例 #2】**

见附件中的 ```summer/summer2.in``` 与 ```summer/summer2.ans```。

该组样例满足测试点 $4\sim 7$ 的约束条件。

**【样例 #3】**

见附件中的 ```summer/summer3.in``` 与 ```summer/summer3.ans```。

该组样例满足测试点 $10\sim 11$ 的约束条件。

**【样例 #4】**

见附件中的 ```summer/summer4.in``` 与 ```summer/summer4.ans```。


对于第一组测试数据，其满足特殊性质 A。

对于第二组测试数据，其满足特殊性质 B 和 C。

对于第三组测试数据，其满足特殊性质 B。

对于第四组测试数据，其满足特殊性质 C。

对于第五组测试数据，其满足特殊性质 D。

该组样例满足 $T=5$，$\sum n \le 2\times10^6$。

**【样例 #5】**

见附件中的 ```summer/summer5.in``` 与 ```summer/summer5.ans```。

该组样例满足测试点 $23 \sim 25$ 的约束条件。

**【数据范围】**

本题共 $25$ 个测试点，每个 $4$ 分。

|  测试点编号  |         $\sum n$         | 特殊性质 |
| :----------: | :-----------------: | :------: |
|  $1 \sim 3$  |      $\le 18$       |    无    |
|  $4 \sim 7$  |      $\le 100$      |    无    |
| $8 \sim 9$  | $\le10^3$ |    无    |
| $10 \sim 11$  | $\le2\times10^5$ |    无    |
| $12 \sim 13$ | $\le 2 \times 10^6$ |    A|
| $14 \sim 15$ | $\le 2 \times 10^6$ |    B 和 C|
| $16 \sim 17$ |     $\le 2 \times 10^6$   |  B  |
| $18 \sim 19$ |    $\le 2 \times 10^6$    |  C  |
| $20 \sim 22$ |     $\le 2 \times 10^6$   |  D  |
| $23 \sim 25$  | $\le 2 \times 10^6$ |    无    |

特殊性质 A：保证不存在任何一列，使得上下两格为一黑一白。  
特殊性质 B：保证不存在任何一列，使得上下两格均为黑色。  
特殊性质 C：保证不存在任何一列，使得上下两格均为白色。  
特殊性质 D：保证对于任意位置，其颜色在黑白中等概率随机生成。

对于全部数据，保证：$1\le T \le 5$，$1 \le m \le n \le 2\times 10^6$，$\sum{n}\le 2\times10^6$。

## 样例 #1

### 输入

```
0 2
5 2
11110
01001
7 1
1110000
0001111```

### 输出

```
2
4
```

# 题解

## 作者：MicroSun (赞：14)

CSP 赛前写题解加 rp（

赛时用了半小时左右想出来了，但是去打 CF 了，没调完。

---

下文中的 $\{co_a,co_b\}$ 表示上面一个格子的颜色为 $co_a$，下面一个格子的颜色为 $co_b$ 的一列。

对于这类博弈题，我们可以考虑，如果先手已经做出了决策，后手的决策时什么？对于这道题，即 如果 youyou 已经选好了一个连通块，yy 会怎么操作？分开考虑每一个格子对，对于所有的 $\{1,1\}$ 和 $\{0,0\}$ 对，没有任何操作的必要性，因为操作与否并不会真正改变整个网格。如果一个 $\{0,1\}$ 或一个 $\{1,0\}$ 对被连通块**完全覆盖**，则这一列也没有必要操作，因为操作不会影响黑格子的总数和白格子的总数。那么，对于一个格子对，只有它是一个 $\{0,1\}$ 对或 $\{1,0\}$ 对，且这个格子对中有且仅有一个被选择了，这个格子对才**可能**产生有效的交换操作。

既然 yy 希望最小化黑色格子减白色格子的数量，即最小化黑色格子的数量或最大化白色格子的数量，那么容易发现 yy 一定会把这 $m$ 次操作用在 使一个选择的黑色格子变白 上。即对于所有的 $\{0,1\}$ 或 $\{1,0\}$ 对，如果 youyou 选择且仅选择了黑色格子，那么在次数够用的情况下这一对格子会被交换。

知道了 youyou 的策略，接下来我们可以开始考虑 yy 的策略了。

首先有一个很显然的结论，因为选择的是一个连通块，设连通块中最靠左的格子的横坐标为 $l$，最靠右的格子的横坐标为 $r$，那么 $[l,r]$ 中的每一对格子都会有至少一个被选，否则与这个点集是连通块相矛盾。

于是我们可以考虑确定了选点的区间 $[l,r]$ 后 youyou 的决策。这时，问题被转换为了对于每一列选 $[1,2]$ 个格子。明显地，由于 youyou 希望最大化黑色格子减白色格子的数量，即使最终的黑色格子尽量多且白色格子尽量少，对于 $\{1,1\}$ 和 $\{0,0\}$ 的决策可以确定。即对于 $\{1,1\}$ 两个格子全选；对于 $\{0,0\}$ 选与上一列选的点格子的纵坐标相同的格子，如果上一列选了两个格子则任选一个。

如何处理 $\{0,1\}$ 和 $\{1,0\}$ 对呢？笔者认为这是整道题目中最难的部分。直接贪心，不论是什么策略，都显然是错误的。这时我们需要一个新思想：分类讨论。我们只需使劲地拍脑袋，就会发现策略只有两种，一种是在可能的情况下全部都选黑格子，第二种是全部都选上（这些对内，黑色格子数等于白色格子数，贡献为 $0$）。除了这两种策略之外的任何策略都是不优的，简证如下：

很明显任何对内只选白色格子是劣的。于是我们要么选黑色格子，要么黑白全选。

设尽可能选黑格子，可以选出 $s$ 个黑格子，我们要证明不优的策略选了 $x$ 个黑格子，满足 $0<x<s$。

- 如果 $x\le m$，这种策略的贡献为 $-1\times x<0$，其中 $0$ 为全选的贡献；
- 如果 $x>m$，这种策略的贡献为 $-m+(x-m)< -m+(s-m)$，其中 $-m+(s-m)$ 为尽可能选黑格子的贡献。

证毕。

于是，我们只要算出两种情况的答案并取最大值即可。

现在，我们的问题已经变得很简单了，只需要选出一个区间使得按照上面的方式计算，两种策略的最大值尽量大。

不如把这个问题稍微改变一下，变为找到全选情况下的最大值和尽量选黑色格子情况下的最大值并取 $\max$。容易证明这两个问题等价。

对于全选情况下的最大值，只需将 $\{0,0\}$ 赋权 $-1$，$\{1,1\}$ 赋权 $2$，$\{0,1\}$ 和 $\{1,0\}$ 赋权 $0$ 并跑一下最大子段和即可。

对于尽量选黑格子的情况，也可以用类似的方法赋权跑最大子段和，但是无后效性的证明比较麻烦，这里就不提了。具体的实现是维护一个 $lst$ 表示上次选的黑点的纵坐标，如果当前的黑白点对中黑点的纵坐标与上次选的黑点的纵坐标不同，就得选上当前列中的两个格子，原因显然。每到一个两个元素都被选上了的点就清空标记。记得最后的答案要减去 $2m$。

但是笔者比较蠢，赛时没把无后效性证出来，用了另一种写法：枚举上面提到的区间的右端点并用一个区间加单点修改求 $\max\{\sum_{j=i}^r a_j\}$（$r$ 为当前枚举的右端点）的线段树（如果你不会这个技巧你可以做一做 [P10381](/problem/P10381)）。但是实质其实是一样的。这大概是没调出来的原因吧（

**upd on 10.23** 关于最大子段和做法的正确性。

首先 $\{0,0\}$ 和 $\{1,1\}$ 的正确性显然，然后将 $\{1,0\}$ 和 $\{0,1\}$ 转换时的负贡献向前挪动到上一个 $1$ 位置不同的 $\{1,0\}$ 或 $\{0,1\}$ 格子，可以发现这是等价的。挪动负贡献后，无后效性就显然了。

最大子段和写法：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;++i)
#define dep(i,s,e) for(int i=s;i>=e;--i)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int N=2e6+10;

int num(pii a){
	if(a.fst==a.scd) return a.fst;
	return a.fst+2;
}
/*
0: 0 0
1: 1 1
2: 0 1
3: 1 0
*/
void solve(){
	int n,m;
	cin>>n>>m;
	string a1,b1;
	cin>>a1>>b1;
	vector<int> ve;
	rep(i,0,n-1)
		ve.pb(num({a1[i]-'0',b1[i]-'0'}));
	int cnt=0,ans1=0;
	for(int typ:ve){
		if(typ==0) --cnt;
		else if(typ==1) cnt+=2;
		ans1=max(ans1,cnt);
		cnt=max(cnt,0);
	}
	int ans2=0,lst=0;
	cnt=0;
	for(int typ:ve){
		if(typ==0) --cnt;
		else if(typ==1){
			cnt+=2;
			lst=0;
		}
		else{
			if(!lst||lst==typ) ++cnt,lst=typ;
			else lst=0;
		}
		ans2=max(ans2,cnt);
		if(cnt<=0) cnt=lst=0;
	}
	ans2-=m*2;
	cout<<max(ans2,ans1)<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int c,t=1;
	cin>>c>>t;
	while(t--) solve();
    return 0;
}
```

线段树写法：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;++i)
#define dep(i,s,e) for(int i=s;i>=e;--i)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int N=2e6+10;

int num(pii a){
	if(a.fst==a.scd) return a.fst;
	return a.fst+2;
}
/*
0: 0 0
1: 1 1
2: 0 1
3: 1 0
*/
#define ls ((u)<<1)
#define rs ((u)<<1|1)
int mx[N<<2],tag[N<<2],n,m;
void upd(int p,int v,int l=1,int r=n,int u=1){
	if(l==r){
		mx[u]=v;
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid) upd(p,v,l,mid,ls);
	else upd(p,v,mid+1,r,rs);
	mx[u]=max(mx[ls],mx[rs]);
}
void pd(int u){
	mx[ls]+=tag[u];
	mx[rs]+=tag[u];
	tag[ls]+=tag[u];
	tag[rs]+=tag[u];
	tag[u]=0;
}
void add2(int s,int t,int v,int l=1,int r=n,int u=1){
	if(t<l||r<s) return;
	if(s<=l&&r<=t){
		mx[u]+=v;
		tag[u]+=v;
		return;
	}
	int mid=(l+r)>>1;
	pd(u);
	if(s<=mid) add2(s,t,v,l,mid,ls);
	if(t>mid) add2(s,t,v,mid+1,r,rs);
	mx[u]=max(mx[ls],mx[rs]);
}
int get(int s,int t,int l=1,int r=n,int u=1){
	if(t<l||r<s) return INT_MIN;
	if(s<=l&&r<=t) return mx[u];
	int mid=(l+r)>>1;
	pd(u);
	return max(get(s,t,l,mid,ls),get(s,t,mid+1,r,rs));
}
void solve(){
	cin>>n>>m;
	rep(i,1,n<<2) mx[i]=tag[i]=0;
	string a1,b1;
	cin>>a1>>b1;
	vector<int> ve;
	rep(i,0,n-1)
		ve.pb(num({a1[i]-'0',b1[i]-'0'}));
	int cnt=0,ans1=0;
	for(int typ:ve){
		if(typ==0) --cnt;
		else if(typ==1) cnt+=2;
		ans1=max(ans1,cnt);
		cnt=max(cnt,0);
	}
	int ans2=0,stp=0,lst=0;
	for(int typ:ve){
		++stp;
		if(typ==0) add2(1,stp,-1);
		else if(typ==1){
			add2(1,stp,2);
			lst=0;
		}
		else{
			if(lst==0||lst==typ) add2(1,stp-1,1),lst=typ;
			else lst=0;
			upd(stp,1);
		}
		ans2=max(ans2,get(1,stp));
	}
	ans2-=m*2;
	cout<<max(ans2,ans1)<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int c,t=1;
	cin>>c>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：2huk (赞：14)

youyou $\to$ Alice，yy $\to$ Bob。

Bob 交换的列一定一黑一白，否则没有意义。

如果这一列都是黑，Alice 都选择一定最优。

如果这一列都是白，Alice 能只选一个就只选一个。这里【能】指可以使得左右连通起来。

所以最难做的是一黑一白的列。

Alice 在一黑一白的列上，要么只选黑，要么都选（选黑白）。

于是对于这些列 Alice 有两种策略：

1. 每一列都选黑白；

2. 只选黑的列数 $\ge m$。（如果只选黑的列数 $< m$，那么 Bob 可以将这些列都操作。）

于是我们需要分别计算 Alice 用这两种策略能得到的最优解。

1. 每个一黑一白列都选黑白。

   这样 Bob 无法操作。

   构造这样一组策略：全黑列两个都选，全白列只选第一行的，一黑一白列都选。这样每一种列的贡献分别是 $2,-1,0$。不难发现这种策略能在保证连通的情况下最优。

2. 每个一黑一白列中，只选黑的列数 $\ge m$。

   Bob 会在这些只选黑的列中选 $m$ 个操作。

   若我们将**所有**这样只选黑的列的贡献视为 $1$，其余列的贡献仍然不变，这样计算后得到的答案**减去 $\mathbf {2m}$** 即为真实答案。因为这 $m$ 列的贡献我们都多算了 $2$（$-1 \to 1$）。

考虑这两种做法的答案具体如何求解。

1. 如上所述，将全黑列，一黑一白列，全白列的贡献分别视作 $2,0,-1$，然后变成了[最大子段和](https://www.luogu.com.cn/problem/P1115)问题。
2. 最后减去 $2m$ 是容易的。求最初答案可以 DP。设 $f(i, 0/1/2)$ 表示考虑连通块的右端点以 $i$ 结尾，且 $i$ 这一列只选上/只选下/上下都选。转移时需要保证连通。第 $i$ 列的具体贡献上面已提。

复杂度线性。代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

int n, m;
bool g[2][N];

int solve1() {
	int res = 0;
	int sum = 0;
	int mn = 0;
	for (int i = 1; i <= n; ++ i ) {
		if (g[0][i] && g[1][i]) sum += 2;
		else if (!g[0][i] && !g[1][i]) sum -- ;
		mn = min(mn, sum);
		res = max(res, sum - mn);
	}
	return res;
}

int f[N][3];

int solve2() {
	memset(f, -0x3f, sizeof f);
	f[0][0] = f[0][1] = f[0][2] = 0;
	
	for (int i = 1; i <= n; ++ i ) {
		if (!g[0][i] && !g[1][i]) {
			f[i][0] = max(f[i - 1][0], f[i - 1][2]) - 1;
			f[i][1] = max(f[i - 1][1], f[i - 1][2]) - 1;
			f[i][2] = max(f[i - 1][0], max(f[i - 1][1], f[i - 1][2])) - 2;
			
			f[i][0] = max(f[i][0], -1);
			f[i][1] = max(f[i][1], -1);
			f[i][2] = max(f[i][2], -2);
		} else if (g[0][i] && g[1][i]) {
			f[i][0] = max(f[i - 1][0], f[i - 1][2]) + 1;
			f[i][1] = max(f[i - 1][1], f[i - 1][2]) + 1;
			f[i][2] = max(f[i - 1][0], max(f[i - 1][1], f[i - 1][2])) + 2;
			
			f[i][0] = max(f[i][0], 1);
			f[i][1] = max(f[i][1], 1);
			f[i][2] = max(f[i][2], 2);
		} else {
			f[i][0] = max(f[i - 1][0], f[i - 1][2]) + (g[0][i] ? 1 : -1);
			f[i][1] = max(f[i - 1][1], f[i - 1][2]) + (g[1][i] ? 1 : -1);
			f[i][2] = max(f[i - 1][0], max(f[i - 1][1], f[i - 1][2]));
			
			f[i][0] = max(f[i][0], (g[0][i] ? 1 : -1));
			f[i][1] = max(f[i][1], (g[1][i] ? 1 : -1));
			f[i][2] = max(f[i][2], 0);
		}
	}
	
	int res = 0;
	for (int i = 1; i <= n; ++ i )
		for (int j : {0, 1, 2}) {
			res = max(res, f[i][j]);
		}
	return res;
}

int solve() {
	cin >> n >> m;
	for (int i = 0; i < 2; ++ i )
		for (int j = 1; j <= n; ++ j ) {
			char c;
			cin >> c;
			g[i][j] = c - '0';
		}
	
	return max(solve1(), solve2() - 2 * m);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int c, T;
	cin >> c >> T;
	while (T -- ) cout << solve() << '\n';
	return 0;
}
```

---

## 作者：hez_EX (赞：12)

小小 DP 加类贪心，场上想到了正确思路，但是以为贪心是假的，不敢写，寄了呜呜呜。

[题面](/problem/P11218)。

### $\mathcal O(nm)$ 做法
这一挡引导考虑 DP。考虑设计 $f_{i,j,c}$：
 - $c=0$ 时，只选上侧方格；
 - $c=1$ 时，只选下侧方格；
 - $c=2$ 时，两格都选。

$i$ 为考虑前 $i$ 列，$j$ 为已经翻转 $j$ 次。转移有点麻烦，和正解关联性也不大，就不赘述了。

### $\mathcal O(n)$ 做法
注意到题目的数据构造始终在围绕 $n$ 做文章，~~利用出题人心理学法~~，不妨大胆猜想：$m$ 对应的一维可以直接干掉！

那么 yy 必然就有确定的最优方案。继续分讨。
 - 当两格同色，翻转与否无影响，故不翻转；
 - 当两格异色。
   - 当同时选两格，翻转与否无影响，故不翻转；
   - 当选黑一格，尽可能多翻转此类，假设共有 $x$ 次这样的选择，贡献 $-2\min\{x,m\}$；
   - 当选白一格，不做处理即最优。

注意到 $-2\min\{x,m\}$ 是单峰的，故最大值取在两侧，即 $x$ 尽可能少一侧和尽可能多一侧，所以贪心地取这两侧进行 DP 就完了。

对于少一侧，注意每遇到一列异色的贡献 $-1$，因为默认 yy 会翻转。而多一侧则恰恰相反贡献 $1$，但注意统计答案要减去 $2m$。

因为转移方程比较冗长，这里就不用公式列出，读者可自行移至代码处查看，故解释代码中一部分细节。

代码先分讨上述第一类情况，再分讨第二类情况。在第一类情况中代码将异色列一起处理了而第二类分开处理，因为第二类中需要明确选择的是黑格还是白格，二者贡献不一致（即先假设了 yy 一个都不翻的自然情况）。这个 DP 类似最大子段和，故每次 $f$ 的值掉下 $0$ 之后就应该重新开始，这里为了方便编写，代码将 `max` 操作中的 $0$ 平衡了贡献，这样可以把贡献直接提出来，读者为方便理解，可将后面加上贡献的改回 `max` 操作中。

### AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;
inline void read(int &x)
{
	char c=getchar();x=0;
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10-48+c,c=getchar();
}
int t,n,m,f[2000005][3],ans;
bool a[2000005][2];
int main()
{
	read(t);read(t);
	while(t--)
	{
	read(n);read(m);ans=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	for(int i=1;i<=n;i++) a[i][0]=c-48,c=getchar();
	while(!isdigit(c)) c=getchar();
	for(int i=1;i<=n;i++) a[i][1]=c-48,c=getchar();
	for(int i=1;i<=n;i++)
	{
		if(a[i][0]^a[i][1])
			f[i][0]=max({1,f[i-1][0],f[i-1][2]})-1,
			f[i][1]=max({1,f[i-1][1],f[i-1][2]})-1,
			f[i][2]=max({0,f[i-1][0],f[i-1][1],f[i-1][2]});
		else
			if(a[i][0])
				f[i][0]=max({-1,f[i-1][0],f[i-1][2]})+1,
				f[i][1]=max({-1,f[i-1][1],f[i-1][2]})+1,
				f[i][2]=max({-2,f[i-1][0],f[i-1][1],f[i-1][2]})+2;
			else
				f[i][0]=max({1,f[i-1][0],f[i-1][2]})-1,
				f[i][1]=max({1,f[i-1][1],f[i-1][2]})-1,
				f[i][2]=max({2,f[i-1][0],f[i-1][1],f[i-1][2]})-2;
		ans=max({ans,f[i][0],f[i][1],f[i][2]});
	}
	memset(f,0,sizeof f);
	for(int i=1;i<=n;i++)
	{
		if(a[i][0]^a[i][1])
			if(a[i][0])
				f[i][0]=max({-1,f[i-1][0],f[i-1][2]})+1,
				f[i][1]=max({1,f[i-1][1],f[i-1][2]})-1,
				f[i][2]=max({0,f[i-1][0],f[i-1][1],f[i-1][2]});
			else
				f[i][0]=max({1,f[i-1][0],f[i-1][2]})-1,
				f[i][1]=max({-1,f[i-1][1],f[i-1][2]})+1,
				f[i][2]=max({0,f[i-1][0],f[i-1][1],f[i-1][2]});
		else
			if(a[i][0])
				f[i][0]=max({-1,f[i-1][0],f[i-1][2]})+1,
				f[i][1]=max({-1,f[i-1][1],f[i-1][2]})+1,
				f[i][2]=max({-2,f[i-1][0],f[i-1][1],f[i-1][2]})+2;
			else
				f[i][0]=max({1,f[i-1][0],f[i-1][2]})-1,
				f[i][1]=max({1,f[i-1][1],f[i-1][2]})-1,
				f[i][2]=max({2,f[i-1][0],f[i-1][1],f[i-1][2]})-2;
		ans=max({ans,f[i][0]-2*m,f[i][1]-2*m,f[i][2]-2*m});
	}
	printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：xixisuper (赞：7)

# P11218 【MX-S4-T2】「yyOI R2」youyou 不喜欢夏天 题解

挺好的 dp，感觉难点在于思路转化。

~~场上 dp 少开了一维，得到了 56pts 的高分，赛后 10min 想出正解，我还是太菜了。~~

upd：2024/10/24 修改了一点小笔误，望管理员重新审核后通过。

## 思路

思考一下对于 youyou 和 yy 来说的最优策略是啥。

假设 youyou 选择了一个连通块，并且其中存在一列，youyou 上下都选了，yy 显然不会去交换那一列，因为那样对最终的答案没有影响；如果 youyou 选了某一列一个 `0`，而另一个没选，yy 也显然不会交换那一列，因为那样对最终答案的影响不优；**当且仅当 youyou 选择了某一列的一个 `1`，而另一个是 `0` 且 youyou 没选，yy 才会去选择交换。**

整理完 yy 的最优策略，对于 youyou 的最优策略也就显然了。对于一列全是 `1` 来说，youyou 显然会全选；对于一列全是 `0` 来说，youyou 只可能选其中一个 `0`，用于延长连通块的长度；对于一列有 `1` 有 `0` 来说，youyou 要么全选，要么只选其中的那个 `1`，显然不可能只选那个 `0`。

经过一些简单的分析，最终 youyou 想要得到最大的结果，只有可能是在如下两种方案中选择最大值：

- 只要这一列有 `1` 我就全选，yy 没法通过交换上下两个格子的方式使答案变小，最终的答案是选择的 `1` 的个数减去选择的 `0` 的个数。
- 尽量选择更多的 `1`，如果上下两个数一 `1` 一 `0`，尽量只选那个 `1`，最终答案是选择的 `1` 的个数减去选择的 `0` 的个数再减去 $2m$。

第一种方案是显然的，我就不细说了，重点讲一下第二种方案。我们发现，yy 仅会交换选 `1` 没选 `0` 的那些列，并且是能换就换，最多交换 `m` 次。对于最终的答案来说，yy 每做一次有效的交换，都会使最终的答案减少 $2$，所以最终要把答案减掉 $2m$。

这时候又会有人说了，如果我第二种方案没有选超过 $m$ 列一 `1` 一 `0` 的情况，那答案不是减去 $2m$，而是减去二倍的有效交换次数。但是你会发现，如果你选择的一 `1` 一 `0` 的列数没有超过 $m$，那么这种方案显然会劣于第一种方案，因为第一种方案会使答案减少的只有上下两个 `0` 只选一个的情况，然而第二种方案不仅这种情况会使答案减少，那些单选一个 `1` 的列也会使答案减少，故这种情况我们直接忽略掉就好了。

怎么维护呢？对于第一种方案，我们直接跑一个板子最大子段和就好了，详细的说就是把 `00` 的列视为 $-1$，把 `10` 和 `01` 的列视为 $0$，把 `11` 的列视为 $2$，然后跑最大子段和。对于第二种操作，显然选择这一列的情况只有三种：“只选上面”，“只选下面”，“上下都选”。然后还是一样的方式去跑最大子段和，只不过注意转移即可。

简单列一下方案二的状态转移方程，设 $f_{i,0}$ 表示第 $i$ 列只选上面，$f_{i,1}$ 表示第 $i$ 列只选下面，$f_{i,2}$ 表示第 $i$ 列上下都选，$a_i$ 表示第 $i$ 列上面的那个数，$b_i$ 表示第 $i$ 列下面那个数，则有：

$$
f_{i,0}=\max\{A,A+f_{i-1,0},A+f_{i-1,2}\}
$$
$$
f_{i,1}=\max\{B,B+f_{i-1,1},B+f_{i-1,2}\}
$$
$$
f_{i,2}=\max\{A+B,A+B+f_{i-1,0},A+B+f_{i-1,1},A+B+f_{i-1,2}\}
$$

其中 $A=[a_i=1]-[a_i=0],B=[b_i=1]-[b_i=0]$。

方案二最终的答案为 $\max\{f_{i,j}-2m\}$。

由于最大子段和的 dp 的时间复杂度为 $O(n)$，则总时间复杂度为 $O(Tn)$，足以通过此题。

## 代码

不错的 dp 题。

```cpp
#include <iostream>
#include <algorithm>
#define ll int
using namespace std;
const ll N=2e6+10;
string a,b;
ll n,m,f[N][5],ya[N],dp[N];
void solve(){
	cin>>n>>m;
	cin>>a>>b;
	a=' '+a;b=' '+b;
	for(ll i=1;i<=n;i++){
		if(a[i]=='0'&&b[i]=='0') ya[i]=-1;
		if(a[i]=='0'&&b[i]=='1') ya[i]=0;
		if(a[i]=='1'&&b[i]=='0') ya[i]=0;
		if(a[i]=='1'&&b[i]=='1') ya[i]=2;
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
		if(dp[i-1]+ya[i]<ya[i]) dp[i]=ya[i];
		else dp[i]=dp[i-1]+ya[i];
		ans=max(ans,dp[i]);
	}
	for(ll i=1;i<=n;i++){
		ll A=(a[i]=='1')-(a[i]=='0'),B=(b[i]=='1')-(b[i]=='0');
		f[i][0]=max(A,max(A+f[i-1][0],A+f[i-1][2]));
		f[i][1]=max(B,max(B+f[i-1][1],B+f[i-1][2]));
		f[i][2]=max(max(A+B,A+B+f[i-1][0]),max(A+B+f[i-1][1],A+B+f[i-1][2]));
		ans=max(ans,f[i][0]-2*m);
		ans=max(ans,f[i][1]-2*m);
		ans=max(ans,f[i][2]-2*m);
	}
	cout<<ans<<"\n";
}
ll c,T;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>c>>T;
	while(T--) solve();
	return 0;
} 
```

---

## 作者：Qing_que (赞：7)

## 分析
考虑在一列上有几种情况。

1. 上下全为黑：全部选择的贡献为 $2$，上下交换后的贡献为 $2$。
2. 上下为一黑一白：全部选择的贡献为 $0$（黑色为 $1$，白色为 $-1$），上下交换后为 $0$；选择黑色格子的贡献为 $1$，上下交换后为 $-1$。
3. 上下全为白：全部选择的贡献为 $-2$，交换后还是 $-2$。

不难发现，情况 1 一定被选择全部，情况 3 若选，一定选择其中的一个。而这两种情况 yy 不会交换，因为交换后结果不变。于是我们有做法 1。
## 做法  1
除情况 3 外，每次都选择一整列。那么情况 3 只选择其中的一个就可以保证联通。于是三种情况的贡献分别为 $2,0,-1$。按照 [最大子段和](https://www.luogu.com.cn/problem/P1115) 的方法选择即可。

## 分析 2
发现做法 A 不能通过样例。手玩发现，对于情况 2，还可以只选黑色格子。但是 yy 交换后，情况 2 的贡献会改变。

yy 可以交换 $k$ 个格子，对答案的改变最多为 $-2m$ （减去原来黑色格子的贡献 $m$，以及加上白色格子的贡献 $-m$）。记选出单个格子的数量为 $x$，则当 $x > 2m$ 时，选择单个格子更优。于是我们有做法 2。
## 做法 2
选出原图上的一个最大连通块，最后统计时减去 $2m$。

## code
具体实现上的细节放在代码里。
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
using pii = pair<int, int>;
#define fi first
#define se second
#define mkp make_pair

const int INF = 0x3f3f3f3f3f3f3f3f;
const int N = 2e6+10;
const int P = 1e9+7;

int n, m;
int a[N][3], f[N], v[N], g[N][4];
signed main() {
    int op, T;
    cin >> op >> T;
    while(T--) {
        cin >> n >> m;
        for(int i = 1;i <= n;i++) {
            char x;
            cin >> x;
            a[i][1] = x-'0';
        }
        for(int i = 1;i <= n;i++) {
            char x;
            cin >> x;
            a[i][2] = x-'0';
            v[i] = (a[i][1] == 1 ? 1 : -1)+(a[i][2] == 1 ? 1 : -1);
            if(v[i] == -2) v[i] = -1;
        }
        //情况 1
        for(int i = 1;i <= n;i++) f[i] = max(f[i-1], f[i])+v[i];
        int maxn = 0; //情况 2，1表示选了上面的，2表示选了下面的，3表示选择全部。
        for(int i = 1;i <= n;i++) {
            g[i][1] = max({g[i-1][1], g[i-1][3], 0ll})+(a[i][1] == 1 ? 1 : -1);
            g[i][2] = max({g[i-1][2], g[i-1][3], 0ll})+(a[i][2] == 1 ? 1 : -1);
            g[i][3] = max({g[i-1][1], g[i-1][2], g[i-1][3], 0ll})+(a[i][1] == 1 ? 1 : -1)+(a[i][2] == 1 ? 1 : -1);
            maxn = max({maxn, g[i][1], g[i][2], g[i][3]});
        }
        //取两种情况的最大值
        cout << max(*max_element(f+1, f+n+1), maxn-2*m) << '\n';
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
    }
	return 0;
}
/*


*/
```

---

## 作者：ForwardStar (赞：6)

考虑 $m=n$      

由于同一列最多只会交换一次，所以该条件的等价于无限交换。因此，当一列分别是黑和白时，如果只选黑，那 yy 一定会交换，会劣，所以我们如果选一定会两个都选上，于是我们就总结出了以下策略。   

- 如果是两个黑，全选上，贡献为 $2$。
- 如果是两个白，选其中一个，贡献为 $-1$。
- 如果一黑一白，全选上，贡献为 $0$。

也容易发现这个策略可以保证选出的网格一定连通，跑最大子段和。

考虑 $m=0$   

由于 yy 不能交换，遇到一黑一白的情况可以只选择黑色，但如果遇到两列黑白交叉的情况，需要额外选一个白色保证连通，于是我们就总结出了以下策略。   

- 如果是两个黑，全选上，贡献为 $2$。
- 如果是两个白，选择与上一列能联通的那个，贡献为 $-1$。
- 如果是一黑一白，且黑色与上一列联通，选择黑色，贡献为 $1$。
- 如果一黑一白，且黑色不与上一列联通，全部选上，贡献为 $0$。

但要注意，在跑最大子段和，进行重新起一段的决策时，不需要考虑与上一列的连通。  

那其实一般情况也很显然了，我们同时尝试两种策略，但第二种策略 yy 会使我们 $m$ 个黑子被交换为白子，分数会减去 $2m$，取最大即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 55;
int c, T, n, m;
char str[2][N];
int f[N]; 
int calc1(int x) {
	if (str[0][x] != str[1][x]) return 0;
	else if (str[0][x] == '1') return 2;
	else return -1;
}

int main() {
	scanf("%d%d", &c, &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		scanf("%s", str[0] + 1);
		scanf("%s", str[1] + 1);
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			f[i] = max(f[i - 1] + calc1(i), calc1(i));
			ans = max(ans, f[i]);
		}
		int t = 2;
		for (int i = 1; i <= n; i++) {
			int d;
			if (t == 2) {
				if (str[0][i] != str[1][i]) {
					d = 1;
					t = (str[1][i] == '1');
				}
				else if (str[0][i] == '1') d = 2;
				else d = -1;
			} 
			else {
				if (str[0][i] == str[1][i]) {
					if (str[0][i] == '1') {
						d = 2;
						t = 2;
					}
					else d = -1;
				}
				else {
					if (str[t][i] == '1') d = 1;
					else {
						d = 0;
						t = 2;
					}
				}
			}
			f[i] = max(f[i - 1] + d, d == 0 ? 1 : d);
			ans = max(ans, f[i] - 2 * m);
		}	
		printf("%d\n", ans);	
	}
	return 0;
}


```

---

## 作者：qzmoot (赞：5)

# 题解：P11218 youyou 不喜欢夏天
## 题目大意
进行两次操作，第一次取出一个连通块，第二次可以将 $m$ 列的颜色上下调换。若两人为了达到自己的目标使用最优策略最后黑减白的数量是多少。
## 分析
观察调换颜色的操作，我们发现，这个操作十分有局限性。

1. 如果一列是全白的，我们肯定只会选择一个，多选了会导致多扣一个贡献，选择一个的话后手也奈何不了我们。
2. 如果一列是全黑的，我们肯定要全选，后手无法消除我们全黑的贡献。
3. 如果是黑白相间的，我们全选的话就是 $0$ 贡献的。若只想选择一个，我们先手肯定是选择黑的，这样的话后手就肯定会操作一次。

知道后手的操作思路后，我们就考虑如何先手能够最大化价值。

很显然的一个思路就是我们选比 $2\times m$ 还要多的黑白格子的一行，因为后手进行操作一次，我们会减少一个黑格子，增加一个白格子。总贡献减 $2$，所以我们若要选择黑白格子的一行，必须数量要超过 $2\times m$ 否则我们选择黑白格子的贡献就是负的。所以我们就不考虑限制地取连通块，然后答案就是连通块中的贡献减去 $2\times m$。

但是如果 $2\times m$ 很大的情况下，我们单选择黑白格子的黑格子就是找死，因为后手可以让你的贡献全部减掉。但是我们只选独立的全黑格子的话贡献就太低了，那不妨将黑白格子全选，贡献虽然为 $0$ 但是可以帮助我们和其他的全黑格子连通上。这个时候问题就转化成了一个最大子段和问题，可以贪心或者像我一样蠢蠢地拿单调栈和前缀和做。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int c,T;
int a[3][N],id[N];
//每一行的格子转化成二进制 
//01:1
//10:2
//00:0
//11:3
int st[N],top,s[N];
int ans;
int main()
{
	scanf("%d%d",&c,&T);
	while(T--)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=2;i++)
			for(int j=1;j<=n;j++)
				scanf("%1d",&a[i][j]);
		for(int i=1;i<=n;i++)
			id[i]=(a[1][i]<<1)+a[2][i];
		top=ans=0;
		st[++top]=0;
		for(int i=1;i<=n;i++)
		{
			s[i]=s[i-1];
			if(id[i]==3)
				s[i]+=2;
			if(id[i]==0)
				s[i]-=1;
			ans=max(ans,s[i]-s[st[1]]);
			while(top && s[st[top]]>s[i])
				top--;
			st[++top]=i;
		}
		int las=3,sum=0;
		//las的二进制就表示上一次操作后第一行和第二行是否和目前的连通 
		for(int i=1;i<=n;i++)
		{
			if(id[i]==3)
				las=3,sum+=2;
			else if(id[i]==0)
				sum--;
			else if(id[i]==2)
			{
				if(las&1)
					las=1,sum++;//必须连通的地方也有才能增加 
				else
					las=3;//否则就只能全选，下面的也是一样的意思。 
			}
			else
			{
				if(las&2)
					las=2,sum++;
				else
					las=3;
			}
			ans=max(ans,sum-2*m);
			if(sum<=0)
				sum=0,las=3;//如果中间有很长一串全白的话我们就重新开始 
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：_Cheems (赞：5)

简单 dp 题。

观察到 yy 交换的列一定满足：youyou 在这列恰选了一个格子，该格子为黑色，且另一个格子为白色。称这种列为合法列。

于是可以直接做 2D 的 dp，设 $f_{i,j,S}$ 表示考虑了前 $i$ 列、总共有 $j$ 个合法列，且第 $i$ 列的选择情况是 $S$ 时的最大价值（黑减白）。答案就是 $\max \{f_{i,j,S}-\min(2m,j)\}$，复杂度 $O(n^2)$。

然后观察到最终答案不可能落在 $0<j<2m$，因为此时合法列产生的总贡献为负，而我们可以将合法列填充为两个都选使得贡献为 $0$。

于是，可以强行让 $j>0$ 的都减去 $2m$，这样做答案肯定不会更优，而且根据上面讨论又一定包含最优答案，所以没错。

这样第二维只需记录 $[j>0]$，复杂度 $O(n)$，带个小常数。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(a, b) a = max(a, b)
const int N = 2e6 + 5;
int T, n, m, f[N][3][2], ans, v[3], pd[3];
char a[N], b[N];

inline int val(char c) {return c == '1' ? 1 : -1;}
inline bool chk(char now, char pre) {return now == '1' && pre == '0';}
signed main(){
	cin >> T >> T;
	while(T--){
		ans = 0;
		scanf("%d%d%s%s", &n, &m, a + 1, b + 1);
		memset(f, -0x3f, sizeof f);
		for(int i = 1; i <= n; ++i){
			v[0] = val(a[i]), v[1] = val(b[i]); v[2] = v[0] + v[1];
			pd[0] = chk(a[i], b[i]), pd[1] = chk(b[i], a[i]);
			f[i][0][pd[0]] = v[0], f[i][1][pd[1]] = v[1], f[i][2][pd[2]] = v[2];
			if(i > 1){
				for(int S = 0; S < 3; ++S)
					for(int p = 0; p < 2; ++p)
						for(int S2 = 0; S2 < 3; ++S2){
							if((S == 0 && S2 == 1) || (S == 1 && S2 == 0)) continue;
							MAX(f[i][S2][p | pd[S2]], f[i - 1][S][p] + v[S2]);
						}
			}
			for(int j = 0; j < 3; ++j) MAX(ans, max(f[i][j][0], f[i][j][1] - 2 * m));
		}
		printf("%d\n", ans);
	}
	return 0;
}

```

---

## 作者：Xy_top (赞：3)

显然可以进行分类讨论：

遇到 $2$ 黑或者 $2$ 白的情况比较简单，在此只讨论遇到 $1$ 黑 $1$ 白的情况。

1. 如果 $m$ 个操作次数全部用完，当本列为 $1$ 黑 $1$ 白时，如果能只扩展到黑那就只扩展到黑，如果不能那就两个都扩展。

2. 如果 $m$ 个操作次数没有用完，那么遇到 $1$ 黑 $1$ 白时全选是最优的。

于是就写完了，不明白为什么是蓝题。

代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int c, T, n, m;
char s[3][2000005];
signed main () {
	scanf ("%lld%lld", &c, &T);
	while (T --) {
		scanf ("%lld%lld", &n, &m);
		scanf ("%s%s", s[1] + 1, s[2] + 1);
		int ans = 0, cnt = 0, cur = 0, sh = 0;
		For (i, 1, n) {//case1：操作次数用尽，能选则选，做最大子段和
			if (cur == 0) {
				if (s[1][i] + s[2][i] == 97) {
					if (s[1][i] == 49) sh = 1;
					else sh = 2;
					cur = 1;
					cnt = 1;
				} else if (s[1][i] + s[2][i] == 98) {
					sh = 3;
					cur = 2;
					cnt = 0;
				}
				continue;
			}
			if (s[1][i] + s[2][i] == 97) {
				if (s[1][i] == 49) {
					if (sh == 1 || sh == 3) {
						++ cur;
						++ cnt;
						sh = 1;
					} else if (sh == 2) sh = 3;
				} else {
					if (sh == 2 || sh == 3) {
						++ cur;
						++ cnt;
						sh = 2;
					} else sh = 3;
				}
			} else if (s[1][i] + s[2][i] == 98) {
				cur += 2;
				sh = 3;
			} else -- cur;
			ans = max (ans, cur - 2 * min (cnt, m) );
		}
		int tmp = 0;
		For (i, 1, n) {//case2：操作次数没用尽
			if (s[1][i] + s[2][i] == 98) tmp += 2;
			if (s[1][i] + s[2][i] == 96) -- tmp;
			ans = max (ans, tmp);
			tmp = max (tmp, 0LL);
		}
		cout << max (0LL, ans) << '\n';
	}
	return 0;
}//进行 2 轮，则承受3 * s，进行 m 轮，则承受 (2^m - 1) * s
//区间加，前缀和
//单点加，维护 a[1] * n + a[2] * n = a[3] * n
```

---

## 作者：zjinze (赞：3)

#### 思路：

设 $dp_{i,{0/1/2}}$ 表示以第 $i$ 列结尾，且第 $i$ 列只选了上面的格子或只选了下面的格子或者上下两个格子都选了时黑色格子减白色格子数量的最大值。

显然，对于某一列，如果上下两个格子颜色相同，此时无论 yy 是否交换，都不会影响最终结果。所以我们只需考虑一黑一白的情况。

假如某一列的格子颜色为一黑一白，若 youyou 上下两个格子都选了的话，那么 yy 无论是否交换这一列也不会影响最终的结果，若 youyou 只选了白色格子的话，那么 yy 是无论如何也不会交换这一列的，因为 yy 交换这一列后，youyou 选择的黑色格子数量只会更多，选择的白色格子数量只会更少。所以接下来我们只需要考虑对于一黑一白的一列，只选了黑色格子的情况。

普遍的，我们给黑色格子的权值设为 $1$，给白色格子的权值设为 $-1$，再给整个列的权值设为黑色格子数量减去白色格子数量，接下来跑一个二维的最大子段和即可。

接下来我们要减去 yy 操作的结果。记选了一黑一白的某一列，且只选了黑色格子的数量为 $cnt$，那么我们最后在求出来的结果里要减去 $2 \cdot \min(cnt,m)$。显然这两个可以分段去求，最后取个最大值即可。

如何分段？

对于第一种，我们将处在某一列为一黑一白中的黑色格子的权值改为 $-1$ 即可，第二种不变，于是我们就过了这道题。

#### code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF=1e15;
const int N=2e6+7;
int idx,t,n,m,a[N],b[N],dp[N][3],c[N],d[N],e[N];
char ch;
signed main(){
//	freopen("T529605.in","r",stdin);
//	freopen("T529605.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>idx>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>ch;
			a[i]=ch-'0'; 
		}
		for(int i=1;i<=n;i++){
			cin>>ch;
			b[i]=ch-'0';
		}
        for(int i=1;i<=n;i++){
            if(a[i]+b[i]==2){
                c[i]=d[i]=1;
                e[i]=2;
            }
            else if(a[i]+b[i]==1){
                c[i]=d[i]=-1;             
                e[i]=0; 
            }
            else{
                c[i]=d[i]=-1;
                e[i]=-2;
            }
        }
        for(int i=1;i<=n;i++)dp[i][0]=dp[i][1]=dp[i][2]=-INF;
        dp[0][0]=dp[0][1]=dp[0][2]=0;
		for(int i=1;i<=n;i++){
            dp[i][0]=max(max(dp[i-1][0],dp[i-1][2])+c[i],c[i]);
            dp[i][1]=max(max(dp[i-1][1],dp[i-1][2])+d[i],d[i]);
            dp[i][2]=max(max(max(dp[i-1][0],dp[i-1][1]),dp[i-1][2])+e[i],e[i]);
		}
		int maxs1=0,maxs2=0;
		for(int i=1;i<=n;i++){
			maxs1=max(maxs1,max(max(dp[i][0],dp[i][1]),dp[i][2]));
		}
        for(int i=1;i<=n;i++)dp[i][0]=dp[i][1]=dp[i][2]=-INF;
        for(int i=1;i<=n;i++){
            if(a[i]+b[i]==2){
                c[i]=d[i]=1;
                e[i]=2;
            }
            else if(a[i]+b[i]==1){
				if(a[i]==1)c[i]=1,d[i]=-1;
				else c[i]=-1,d[i]=1;                              
                e[i]=0;
            }
            else{
                c[i]=d[i]=-1;
                e[i]=-2;
            }
        }
        dp[0][0]=dp[0][1]=dp[0][2]=0;
		for(int i=1;i<=n;i++){
            dp[i][0]=max(max(dp[i-1][0],dp[i-1][2])+c[i],c[i]);
            dp[i][1]=max(max(dp[i-1][1],dp[i-1][2])+d[i],d[i]);
            dp[i][2]=max(max(max(dp[i-1][0],dp[i-1][1]),dp[i-1][2])+e[i],e[i]);
		}
		for(int i=1;i<=n;i++){
			maxs2=max(maxs2,max(max(dp[i][0],dp[i][1]),dp[i][2]));
		}
		int maxs=max(maxs1,maxs2-2*m);
		cout<<maxs<<"\n";
	}	
	return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
场上想到的，因为去打 div1 了所以没写，今天刚补感觉挺 ez 的，顺手补个题解好了。
## 思路分析
考虑交换的意义。

如果上下两个格子都选了或者相同显然交换是没有意义的。

那么可能交换的只可能是 $1,0$ 格子只选了一半。

又因为交换是为了让 $1$ 尽可能少 $0$ 尽可能多，所以如果 $1,0$ 格子里只选了 $0$ 那包是不交换的。

但是先手选择也有避免被交换的方法，那就是对于所有选到了的 $1,0$ 格子都全选。

所以在考虑交换的意义下，$1,1$ 格子的贡献是 $2$，选 $0$ 的贡献就是 $-1$，$1,0$ 格子的贡献是 $0$。

对于每一列，我们的选择有四种：全选，选第一行，选第二行，不选。

不选显然无法满足连通块继续向后拓展，所以直接把初始状态当不选即可。

考虑 dp 来计算这个过程，定义 $f_{i,0/1/2}$ 表示最后选中了第 $i$ 列两行/第一行/第二行的最大答案。

转移也就非常 ez，枚举上一列的状态，如果没有接起来那就转移不了，接起来了判断一下 $i$ 这列若为 $1,0$ 则直接贡献标 $0$，否则算一下选上的数的贡献转移就行了。

接着我们来考虑当 $1,0$ 有贡献的时候。

这个时候我们发现，前面 $m$ 个 $1,0$ 都会被交换为 $-1$ 的贡献，后面剩下多余的都是 $1$ 的贡献。

也就是设我们选了 $x$ 个 $1,0$，贡献就是：
$$x-2\times\min(x,m)$$
发现这里有个 $\min$，所以我们大力给 $x$ 扔到 dp 状态里，随便写下就能得到一个 $O(n^2)$ 的 naive 做法。

接着来考虑优化。

其实很清楚，我们是有方法让 $x$ 个 $1,0$ 的贡献为 $0$ 的，所以 $1,0$ 的实际贡献是：
$$\max(0,x-2\times\min(x,m)))$$

显然的是如果 $x-2\times\min(x,m))>0$，则 $x>2\times m$，此时 $\min(x,m)=m$。

所以这个 $\min(x,m)$ 直接写作 $m$ 就行了，不然对式子没有贡献的。

所以我们只考虑 $1,0$ 有贡献的时候，他的贡献就是 $x-2\times m$。

也就是 $1,0$ 只选一个 $1$，贡献为 $1$。

还是考虑用 dp。

和上面一样的写法，只不过把碰到 $1,0$ 直接令贡献为 $0$ 去掉就行了，最后算答案记得减掉 $2\times m$。

如果还没懂的话看下代码应该就行了。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e6+10,M=3,INF=0x3f3f3f3f3f3f3f3f;
int n,m,ans,f[N][M];char s[N],t[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,ot[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(ot,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();ot[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int get(int i,int j,int op)
{
    if(j==0) return s[i]-'0'+t[i]-'0';
    if(s[i]^t[i]&&!op) return 0;
    if(j==1) return s[i]-'0';return t[i]-'0';
}
inline void solve()
{
    read();m=read();n=0;rd(s,n);n=0;rd(t,n);ans=0;for(int i=1;i<=n;i++) f[i][0]=f[i][1]=f[i][2]=0;
    for(int i=1;i<=n;i++) s[i]-=(s[i]=='0'),t[i]-=(t[i]=='0');
    for(int i=1;i<=n;i++) for(int j=0;j<M;j++) for(int k=0;k<M;k++)
    {
        if(j==1&&k==2||j==2&&k==1) continue;
        f[i][j]=max(f[i][j],f[i-1][k]+get(i,j,0));
        ans=max(ans,f[i][j]);
    }
    for(int i=1;i<=n;i++) f[i][0]=f[i][1]=f[i][2]=0;
    for(int i=1;i<=n;i++) for(int j=0;j<M;j++) for(int k=0;k<M;k++)
    {
        if(j==1&&k==2||j==2&&k==1) continue;
        f[i][j]=max(f[i][j],f[i-1][k]+get(i,j,1));
        ans=max(ans,f[i][j]-2*m);
    }print(ans);put('\n');
}
signed main()
{
    read();int T=1;
    T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Hadtsti (赞：2)

### 题目分析

在 @luanyanjia 大佬提示分讨之后会了。

首先列之间只是就连通性而言对 youyou 有关系，对 yy 是没关系的。yy 只会就具体的连通块选减少得分最多的那至多 $m$ 列进行操作。

所以一个简单的思路就是按列 DP，设 $f_{i,0/1/2}$ 分别为第 $i$ 列只取第一行/只取第二行/两行都取的答案。转移很直接：只要该列的状态和上一列的状态连通就可以转移过来，同时加上该列的贡献即可，细节看代码。又由于 yy 最后可以选择 $m$ 列把它们的贡献都从 $1$ 变成 $-1$（我们姑且假设列数是够的），故最后答案需要减去 $2m$。

列数不够的情况呢？我们发现 yy 当且仅当一列是一黑一白且 youyou 只选黑色时可以将贡献 $-2$，那么我们发现如果 youyou 选了不超过 $2m$ 列这么干，还不如一列也不这么干。而前者的情况与上文的情况已经覆盖了所有情况，故我们再算一下每一列要么不取要么全取的答案，就是一个简单的最大子段和问题。

时间复杂度 $O(n)$。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,a[2000010],b[2000010],sum,ans,f[2][3];
int main()
{
	scanf("%*d%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%1d",&a[i]);
		sum=ans=0;
		memset(f,0,sizeof f);
		for(int i=1,w=1;i<=n;i++,w^=1)
		{
			scanf("%1d",&b[i]);
			sum=max(sum+max(2*(a[i]+b[i]-1),-1),0);
			f[w][0]=max({0,f[w^1][0],f[w^1][2]})+2*a[i]-1;
			f[w][1]=max({0,f[w^1][1],f[w^1][2]})+2*b[i]-1;
			f[w][2]=max({0,f[w^1][0],f[w^1][1],f[w^1][2]})+2*(a[i]+b[i]-1);
			ans=max({ans,max({f[w][0],f[w][1],f[w][2]})-2*m,sum});
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Dtw_ (赞：2)

# 题意
给定一个 $2 \times n$ 的网格，每个网格只有黑白两种颜色，你可以选一个联通块，你的对手可以交换同一列上的两个网格中的颜色 $m$ 次，你希望你选的联通块内黑色数量 $-$ 白色数量最大。
# Solution
考虑一下当什么时候交换同一列上的颜色会使得答案减小？

一定是你在一黑一白的列上选了黑色，那么此时对手交换会使你的答案 $-2$。

所以考虑两种策略：

* 对于所有的一黑一白的列，全部选上，这样你的对手无论怎样操作，答案都不变。

* 选大于 $m$ 个一黑一白的列。你的对手一定会交换 $m$ 列，那剩下的就不会了。

所以考虑 $f_{i, 0/1/2/3}$ 表示当前这一列，不选、选了上面的、选了下面的、上下都选了。

因为我们规定了第一次黑白的全选，那么就不能只选一个，所以特判把他们的贡献改成负无穷就好。

$$f_{i, j} = \max(f_{i-1, k} + val_j)$$

其中 $val_j$ 表示当前列选 $j$ 这个状态的贡献，$k$ 要满足和 $j$ 按位与起来后不为 $0$。这是因为我们用二进制表达了上一位的状态，只要你有交集，那么就是联通块，否则不是。

第二次在 dp 的时候就不用判黑白的了，在统计答案的时候直接 $- 2m$ 就行。

为什么直接 $- 2m$ 可以呢？因为只要你选 $< m$ 列黑白的他一定是不优的，所以劣的情况都不会被统计到。
# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define fi first
#define se second

#define int long long

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int inf = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int f[N][4], a[N][2], b[10];

int n, m;

string s;

void solve()
{
	cin >> n >> m >> s;
	for (int i=1; i<=n; i++) a[i][1] = s[i - 1] - '0';
	cin >> s;
	for (int i=1; i<=n; i++) a[i][2] = s[i - 1] - '0';
	for (int i=1; i<=n; i++)
	{
		for (int j=0; j<=3; j++)
		{
			f[i][j] = -inf;
		}
	}
	int res = -inf; 
	for (int i=1; i<=n; i++)
	{
		b[0] = 0, b[1] = (a[i][1] == 1 ? 1 : -1), b[2] = (a[i][2] == 1 ? 1 : -1), b[3] = b[1] + b[2];
		if (a[i][1] != a[i][2]) b[1] = b[2] = -inf;
		for (int j=0; j<=3; j++) f[i][j] = b[j];
		for (int j=0; j<=3; j++)
		{
			for (int k=0; k<=3; k++)
			{
				if (j & k) f[i][j] = max(f[i][j], f[i - 1][k] + b[j]);
			}
		}
		for (int j=0; j<=3; j++) res = max(res, f[i][j]);
	}
	for (int i=1; i<=n; i++)
	{
		b[0] = 0, b[1] = (a[i][1] == 1 ? 1 : -1), b[2] = (a[i][2] == 1 ? 1 : -1), b[3] = b[1] + b[2];
		for (int j=0; j<=3; j++) f[i][j] = b[j];
		for (int j=0; j<=3; j++)
		{
			for (int k=0; k<=3; k++)
			{
				if (j & k) f[i][j] = max(f[i][j], f[i - 1][k] + b[j]);
			}
		}
		for (int j=0; j<=3; j++) res = max(res, f[i][j] - 2 * m);
	}
	cout << res << endl;
}

signed main()
{
	fst
	int c, t;
	cin >> c >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：zzy0618 (赞：2)

我们规定 ```10``` 为某处上面为 $1$，下面为 $0$，```11```，```00```，```01``` 类似。

可以发现，```10```，```01``` 的情况上下都选贡献是 $0$，可以连接左右的联通块。而如果选其中的 $1$，yy 则可以使用一次操作将其变为 $0$。所以 youyou 有两种选法

- 所有的 ```10```，```01```，```11```上下都选，再考虑 ```00``` 的隔绝。

- 其中的 $1$ 选得够多，将 yy 的操作次数耗尽，之后再回本。

对于前者，我们发现只有 ```00``` 的情况我们有待斟酌，因此可以通过 ```00``` 分成若干不含 ```00``` 的块。一个块如果选那么里面的数一定都选，而合并两个块我们只用选择 ```00``` 中的一个 $0$ 作为代价。最终做一个类似与最大子段和，

对于后者，可以直接 dp。定义 $f_{i,0/1/2}$ 为前 $i$ 列的答案，第 $i$ 列选上面，下面，全部，则有如下方程。$a$ 为原题中的网格。

$$f_{i,0}=\max(f_{i-1,0},f_{i-1,2},0)+g_{0,i}$$

$$f_{i,1}=\max(f_{i-1,1},f_{i-1,2},0)+g_{1,i}$$

$$f_{i,2}=\max(f_{i-1,0},f_{i-1,1},f_{i-1,2},0)+g_{0,i}+g_{1,i}$$

$$g_{i,j}=\begin{cases}
1&\text{ }a_{i,j}=1 \\
-1 &\text{ }a_{i,j}=0 \\
\end{cases}$$

答案在 $f$ 中取最大值，最终减去 yy 造成的 $2m$ 的损失。为什么一定是 $2m$？首先 yy 会 $m$ 次将 $1$ 改为 $0$，共 $2m$ 的损失。如果我们选的 ```01``` 和 ```10``` 不足 $2m$ 个，不够为 yy 的操作回本，那么不如前者的做法。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int max(int a,int b,int c){
	return max(max(a,b),c);
}int max(int a,int b,int c,int d){
    return max(max(a,b,c),d);
}int c,t,n,m,k;string a[2];
int s[N],ans;
int dp[N][3];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>c>>t;
	while(t--){
		cin>>n>>m>>a[0]>>a[1];
		k=ans=0;memset(dp,0,sizeof(dp));
		for(int i=0;i<n;++i){
			if(a[0][i]=='0'&&a[1][i]=='0')++k;
			else if(a[0][i]=='1'&&a[1][i]=='1')s[k]+=2;
		}int sum=0;
		for(int i=0;i<=k;++i)
			sum=max(sum+s[i],s[i]),ans=max(ans,sum),--sum,s[i]=0;
		dp[0][0]=(a[0][0]=='1'?1:-1);
		dp[0][1]=(a[1][0]=='1'?1:-1);
		dp[0][2]=(a[0][0]=='1'?1:-1)+(a[1][0]=='1'?1:-1);
		ans=max(ans,dp[0][0]-m*2,dp[0][1]-m*2,dp[0][2]-m*2);
		for(int i=1;i<n;++i){
			dp[i][0]=max(dp[i-1][0],dp[i-1][2],0)+(a[0][i]=='1'?1:-1),
			dp[i][1]=max(dp[i-1][1],dp[i-1][2],0)+(a[1][i]=='1'?1:-1),
			dp[i][2]=max(dp[i-1][0],dp[i-1][1],dp[i-1][2],0)+(a[0][i]=='1'?1:-1)+(a[1][i]=='1'?1:-1);
			ans=max(ans,dp[i][0]-m*2,dp[i][1]-m*2,dp[i][2]-m*2);
		}cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Corzica (赞：1)

我们先考虑 $m$ 次上下翻转怎么交，你会发现只有上下两个数为 $(0,1)$ 且你只选了 $1$ 的时候用，带来 $-2$ 的贡献。

假设我们现在用了 $k$ 次翻转。如果 $k\leq m$，实际上这 $k$ 次翻转都是可以被化解的，也就是说我们可以把 $0$ 一起选上。这时候这 $k$ 列的贡献从 $-2$ 上升到了 $-1$。并且连通性更优。也就是说，翻转只能用 $0$ 次和 $m$ 次。

这里我们已经能够看出来做法了，分有没有用翻转。如果没有用，说明每一个 $(0,1)$ 的列都是两个都选了，按照连通性递推求出答案即可。另一种是 $(0,1)$ 无限制，但是你要在最后减去这 $m$ 次每一次 $-2$ 的贡献，两种情况去最优即可。

复杂度 $O(\sum n)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int c, t;
char ch;
int a[2000006][3], f[5], ans[5], n, m, aans;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> c >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 0; i <= 1; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> ch;
				a[j][i] = ch - '0';
			}
		}
		memset(ans, 0, sizeof(ans));
		aans = 0;
		for (int i = 1; i <= n; i++) {
			if (a[i][0] + a[i][1] == 0) {
				ans[1] = max(ans[1], ans[3]) - 1;
				ans[2] = max(ans[2], ans[3]) - 1;
				ans[3] = 0;
			} else if (a[i][0] + a[i][1] == 1) {
				ans[3] = max(ans[1], max(ans[2], ans[3]));
				ans[1] = ans[2] = 0;
			} else {
				ans[3] = max(ans[3], max(ans[1], ans[2])) + 2;
				ans[1] = ans[2] = 0;
			}
			for (int j = 1; j <= 3; j++) {
				ans[j] = max(ans[j], 0);
				aans = max(aans, ans[j]);
			}
		}
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= n; i++) {
			if (a[i][0] + a[i][1] == 0) {
				int op = max(ans[3], max(ans[1], ans[2])) ;
				ans[1] = max(ans[1], ans[3]) - 1;
				ans[2] = max(ans[2], ans[3]) - 1;
				ans[3] = op - 2;
			} else if (a[i][0] + a[i][1] == 1) {
				int p = 1, q = 2;
				if (a[i][1] == 1) {
					swap(p, q);
				}
				int op = max(ans[3], max(ans[1], ans[2]));
				ans[p] = max(ans[p], ans[3]) + 1;
				ans[q] = max(ans[q], ans[3]) - 1;
				ans[3] = op;
			} else {
				int op = max(ans[3], max(ans[1], ans[2])) ;
				ans[1] = max(ans[1], ans[3]) + 1;
				ans[1] = max(ans[2], ans[3]) + 1;
				ans[3] = op + 2;
			}
			for (int j = 1; j <= 3; j++) {
				ans[j] = max(ans[j], 0);
				aans = max(aans, ans[j] - 2 * m);
			}
		}
		cout << aans << "\n";
	}
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

考虑一列的状态有：

- 全黑。
- 全白。
- 一黑一白。

设只选了状态为一黑一白中黑色的点的数量为 $x$，那么 `yy` 可以翻转其中 $m$ 列，使得贡献为 $x - 2\min(m,x)$。

故可以分类讨论，当 $x < 2m$ 时，我们显然对于一黑一白的列白和黑都选，这样 `yy` 翻转后贡献是不变的，此时令全黑状态权值为 $2$，全白状态权值为 $-1$，一黑一白权值为 $0$ 找最大子段和即可。

当 $x > 2m$ 时，将全黑权值为 $2$，全白权值为 $-1$，上黑下白权值为 $1$ 当且仅当上一列全选了或者上一列只选了上面的棋子；下黑上白同理，当且仅当上一列全选或者上一列只选了下面的棋子，此时答案为 $sum - 2m$。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e6 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int c, T, n, m, s, ans;
int dp[N];
bool a[N],b[N];
char t[N];
void solve(){
	ans = s = 0;
	n = read(), m = read();
	scanf("%s", t + 1);
	for(int i = 1; i <= n; ++i)
	  a[i] = t[i] - '0';
	scanf("%s", t + 1);
	for(int i = 1; i <= n; ++i)
	  b[i] = t[i] - '0';	
	for(int i = 1; i <= n; ++i){
		if(a[i] & b[i])
		  s = max(s + 2, 2);
		else if(!a[i] && !b[i])
		  s = max(s - 1, -1);
		ans = max(ans, s);
	}
	s = 0;
	int F = 3;
	for(int i = 1; i <= n; ++i){
		if(a[i] & b[i]){
			s += 2;
			F = 3;
		}
		if(!a[i] && !b[i])
		  --s;
		if(a[i] && !b[i]){
			if(F & 1){
				++s;
				F = 1;
			}
			else
			  F = 3;
		}
		if(!a[i] && b[i]){
			if(F & 2){
				++s;
				F = 2;
			}
			else
			  F = 3;
		}
		ans = max(ans, s - 2*m);
		if(s <= 0){
			s = 0;
			F = 3;
		}
	}
	write(ans);
	putchar('\n');
}
bool End;
int main(){
	c = read(), T = read();
	while(T--)
	  solve();
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

顺手贴一下赛时打的 $O(nm)$ 的 dp 代码，如果你需要的话：

```cpp
namespace Sub{
	int dp[1010][1010][3];
	void work(){
		memset(dp, 0, sizeof(dp));
		n = read(), m = read();
		for(int i = 0; i < 2; ++i)
		  for(int j = 1; j <= n; ++j)
		    a[i][j] = get() - '0';
		ans = 0;
	    for (int i = 1; i <= n; i ++){
	        for (int j = 0; j <= m; j ++){
	            if(a[0][i] != a[1][i])
				  dp[i][j][2] = max({dp[i - 1][j][0], dp[i - 1][j][1], dp[i - 1][j][2], 0});
	            else if (a[0][i])
				  dp[i][j][2] = max({dp[i - 1][j][0] + 2, dp[i - 1][j][1] + 2, dp[i - 1][j][2] + 2, 2});
	            else
				  dp[i][j][2] = max({dp[i - 1][j][0] - 2, dp[i - 1][j][1] - 2, dp[i - 1][j][2] - 2, 0});
	            if(a[0][i] ^ 1 && a[1][i]&& j)
	              dp[i][j][1] = max({dp[i - 1][j - 1][1] - 1, dp[i - 1][j - 1][2] - 1, 0});
	            if(a[0][i] ^ 1 && a[1][i]&& !j)
	              dp[i][j][1] = max({dp[i - 1][j][1] + 1, dp[i - 1][j][2] + 1, 1});
	            if(a[0][1]&& a[1][i] ^ 1)
	              dp[i][j][1] = max({dp[i - 1][j][1] - 1, dp[i - 1][j][2] - 1, 0});
	            if(a[0][i] == a[1][i] && a[0][i])
	              dp[i][j][1] = max({dp[i - 1][j][1] + 1, dp[i - 1][j][2] + 1, 1});
	            if(a[0][i] == a[1][i] && a[0][i] ^ 1)
	              dp[i][j][1] = max({dp[i - 1][j][1] - 1, dp[i - 1][j][2] - 1, 0});
	            if(a[0][i]&& a[1][i] ^ 1 && j) 
	              dp[i][j][0] = max({dp[i - 1][j - 1][0] - 1, dp[i - 1][j - 1][2] - 1, 0});
	            if(a[0][i]&& a[1][i] ^ 1 && !j)
	              dp[i][j][0] = max({dp[i - 1][j][0] + 1, dp[i - 1][j][2] + 1, 1});
	            if(a[0][i] ^ 1 && a[1][i])
	              dp[i][j][0] = max({dp[i - 1][j][0] - 1, dp[i - 1][j][2] - 1, 0});
	            if(a[0][i] == a[1][i] && a[0][i])
	        	  dp[i][j][0] = max({dp[i - 1][j][0] + 1, dp[i - 1][j][2] + 1, 1});
	            if(a[0][i] == a[1][i] && a[0][i] ^ 1)
	              dp[i][j][0] = max({dp[i - 1][j][0] - 1, dp[i - 1][j][2] - 1, 0});
	        }
	        ans=max({ans, dp[i][m][0], dp[i][m][1], dp[i][m][2]});
	    }
	    write(ans);
	    putchar('\n');
	}
};
```

---

## 作者：刘梓轩2010 (赞：1)

# MX-S4-T2 youyou 不喜欢夏天 题解

## 题意

给你一个 $2 \times n$ 的网格，每个格子是黑色的或是白色的，先手选出一个四联通的连通块，后手可以将 $m$ 个列上下调换，先手要使得黑色块的数量减去白色块的数量尽量大，后手要使它尽量小，问你最终在选出的连通块里黑色块的数量减白色块的数量最大是多少。

$T$ 组数据。

$m \le n$，$\sum n \le 2\times 10^6$，$1 \le T \le 5$。

## 思路

首先，对于上下是全黑，一黑一白，全白，有不同的策略。

- 对于全黑，肯定是都选更优，这样无论怎么换，都不会减少贡献。
- 对于全白，我们肯定最多选一个，因为选两个一定不优，选一个就能维护连通性，或者直接不选。
- 对于一黑一白，我们又有两种选法。我们可以都选上，这样的贡献是 $0$，无论他怎么换都不会影响贡献；我们也可以只选那一个黑的，但是可能被调换，造成 $-2$ 的贡献，由于他最多换 $m$ 个，所以要减去 $2 \times m$ 的贡献。

需要注意的是，对于一黑一白只选一个黑的的位置的情况，如果选的不足 $2 \times m$ 个，设选了 $k$ 个，那么在造成 $-2 \times k$ 的贡献后，一定不如把这些位置的黑白块都选上更优，所以即使算出来的贡献不是这种选法真正的贡献，但是不会影响答案。

对于每种情况，我们可以通过 dp 解决。

设 $f_{i,j},j \in \{0,1,2,3\}$ 表示到了第 $i$ 个位置，最后一个不选/选了上面那个/选了下面那个/都选了的最大贡献（其实就是状压）。那么转移的时候，一个状态能转移到另一个状态，当且仅当两个状态选的列有交集，或者直接只选这一列。

设 $add_{i,j}$ 表示第 $i$ 列不选/选了上面那个/选了下面那个/都选了的贡献。

$f_{i,j}$ 的初值即为 $add_{i,j}$。

令 $\operatorname{and}$ 表示按位与。

转移方程即为：

$$f_{i,j}=\max_{k \in \{0,1,2,3\},j \operatorname{and} k \neq 0} f_{i-1,k}+add_k,f_{i,j}$$

复杂度 $O(n)$。

不理解结合代码。

## Code

```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define fi first
#define se second
using namespace std;
const int N=2e6+10;
const int inf=0x3f3f3f3f3f3f3f3f;
int n,m;
string s[2];
int f[N][4];
int c;
int t;
int ans=-inf; 
/*
对于上下全黑,肯定都选
对于全白,肯定最多选一个
对于一黑一白,有两种情况
1.一部分只选黑的,但有可能被调换
2.都选成上下都选,贡献为0
对于连通性,可以用状压维护 
*/
signed main()
{
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>c>>t;
	while(t--)
	{
	    ans=-inf;
	    cin>>n>>m;
        cin>>s[0]>>s[1];
        for(int i=0;i<=3;i++) f[0][i]=-inf;
	    for(int i=1;i<=n;i++)  //第一种选法,所有的黑白都选,有0的贡献 
	    {
	        int add[4]; //分别4种选法的贡献
	        add[0]=0;
	        if(s[0][i-1]=='1') add[1]=1;
	        else add[1]=-1;
	        if(s[1][i-1]=='1') add[2]=1;
	        else add[2]=-1;
	        add[3]=add[1]+add[2];
	        if(add[1]!=add[2]||(add[1]==add[2]&&add[1]==1)) add[1]=add[2]=-inf;
	        for(int j=0;j<4;j++) f[i][j]=add[j];
	        for(int j=0;j<4;j++)
	        {
	            for(int k=0;k<4;k++)
	            {
	                if(j&k) f[i][k]=max(f[i][k],f[i-1][j]+add[k]);
                }
            }
            for(int j=0;j<4;j++) ans=max(f[i][j],ans);
        }
        for(int i=1;i<=n;i++) //第二种,有部分的黑白选的是黑的,对于这种选法,最多减去2*m的贡献
        //需要注意的是,如果选的不足m个,那么一定没有上面的选法优,所以虽然说选出的答案不是正确的贡献,但一定不如上面的优 
        {
            int add[4]; //分别4种选法的贡献
	        add[0]=0;
	        if(s[0][i-1]=='1') add[1]=1;
	        else add[1]=-1;
	        if(s[1][i-1]=='1') add[2]=1;
	        else add[2]=-1;
	        add[3]=add[1]+add[2];
	        for(int j=0;j<4;j++) f[i][j]=add[j];
	        if(add[1]==add[2]&&add[1]==1) add[1]=add[2]=-inf;
	        for(int j=0;j<4;j++)
	        {
	            for(int k=0;k<4;k++)
	            {
	                if(j&k) f[i][k]=max(f[i][k],f[i-1][j]+add[k]);
                }
            }
            for(int j=0;j<4;j++) ans=max(f[i][j]-2*m,ans);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：xz001 (赞：1)

首先发现只有其中一列一黑一白时且这一列仅选择了黑时修改才有意义，而修改的次数小于等于 $m$，为了摆脱 $m$ 的限制，我们进行两种 dp，第一种为求每个一黑一白且这一列选择了黑时都修改的最大数量，第二种为求每个一黑一白的位置都不修改的最大数量，第二种就默认修改的数量大于了 $m$，直接减去 $2m$，然后求个最大值即可。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e6 + 5;

int c, T, n, m, f[N][2][2], g[N][2][2];

char s[3][N];

int gx (char x, char y, int p) {
	if (x == y) {
		int c = (x == '1') ? 1 : -1;
		if (p == 1 || p == 2) return c;
		return 2 * c;
	}
	if (p == 3) return 0;
	return -1;
}

int dfs1 (int i, int j, int k) { 
	if (i > n) return 0;
	if (f[i][j][k] != -1) return f[i][j][k];
	int ans = 0;
	if (j && k) {
		ans = max(ans, dfs1 (i + 1, 1, 0) + gx(s[1][i], s[2][i], 1));
		ans = max(ans, dfs1 (i + 1, 0, 1) + gx(s[1][i], s[2][i], 2));
		ans = max(ans, dfs1 (i + 1, 1, 1) + gx(s[1][i], s[2][i], 3));
		return f[i][j][k] = ans;
	}
	if (j) {
		ans = max(ans, dfs1 (i + 1, 1, 0) + gx(s[1][i], s[2][i], 1));
		ans = max(ans, dfs1 (i + 1, 1, 1) + gx(s[1][i], s[2][i], 3));
		return f[i][j][k] = ans;
	}
	ans = max(ans, dfs1 (i + 1, 0, 1) + gx(s[1][i], s[2][i], 2));
	ans = max(ans, dfs1 (i + 1, 1, 1) + gx(s[1][i], s[2][i], 3));
	return f[i][j][k] = ans;
}

int gx2 (int x, int y, int p) {
	if (p == 1) return x == '1' ? 1 : -1;
    if (p == 2) return y == '1' ? 1 : -1;
    return (int)(x == '1') + (y == '1') - (x == '0') - (y == '0');
}

int dfs2 (int i, int j, int k) {
	if (i > n) return 0;
	if (g[i][j][k] != -1) return g[i][j][k];
	int ans = 0;
	if (j && k) {
		ans = max(ans, dfs2 (i + 1, 1, 0) + gx2(s[1][i], s[2][i], 1));
		ans = max(ans, dfs2 (i + 1, 0, 1) + gx2(s[1][i], s[2][i], 2));
		ans = max(ans, dfs2 (i + 1, 1, 1) + gx2(s[1][i], s[2][i], 3));
		return g[i][j][k] = ans;
	}
	if (j) {
		ans = max(ans, dfs2 (i + 1, 1, 0) + gx2(s[1][i], s[2][i], 1));
		ans = max(ans, dfs2 (i + 1, 1, 1) + gx2(s[1][i], s[2][i], 3));
		return g[i][j][k] = ans;
	}
	ans = max(ans, dfs2 (i + 1, 0, 1) + gx2(s[1][i], s[2][i], 2));
	ans = max(ans, dfs2 (i + 1, 1, 1) + gx2(s[1][i], s[2][i], 3));
	return g[i][j][k] = ans;
}

signed main() {
	scanf("%lld%lld", &c, &T);
	while (T -- ) {
		scanf("%lld%lld%s%s", &n, &m, s[1] + 1, s[2] + 1);
		memset(f, -1, sizeof(f));
		memset(g, -1, sizeof(f));
		int ans = 0;
	    for (int i = 1; i <= n; ++ i ) ans = max(ans, dfs1 (i, 1, 1));
	    for (int i = 1; i <= n; ++ i ) ans = max(ans, dfs2 (i, 1, 1) - 2 * m);
	    printf("%lld\n", ans);
	}
	return 0;
} 
```

最后说一句：此题思维难度最多绿，代码难度黄，不应评蓝

---

## 作者：ran_qwq (赞：1)

互换的 $m$ 列肯定是选择取了黑色没取白色的互换。

而按最优方案互换，互换一列对答案产生 $-2$ 的贡献。

所以若有 $k$ 列互换后答案减小 $2$，互换对答案的影响是 $-2\min(m,k)$。

看到 $\min$ 直接拆开分讨，分成 $k\ge m$ 和 $k<m$ 两类。

若 $k\ge m$，相当于不互换，最后把答案减去 $2m$。

若 $k<m$，相当于都互换，把取了黑色没取白色看成取了白色没取黑色。

我们发现 $k$ 与 $m$ 的大小关系没有用：若情况 $1$ 的 $k<m$，一定不优，情况 $2$ 同理。

到这里就可以愉快地 dp 了，类似最大子段和，设 $dp_{i,s=0/1/2}$ 为前 $i$ 列，只取第 $1$ 行/只取第二行/两行都取的答案。转移枚举的上一列状态 $t$ 只用保证 $s\cap t\ne\empty$ 即可，根据分讨的结果统计 $i$ 列的贡献。

代码比较短。

```cpp
int n,m,a[N],b[N],dp[N][3]; string s,t;
void QwQ() {
	n=rd(),m=rd(),cin>>s>>t,s=" "+s,t=" "+t;
	auto gt=[&](int x) {return x?1:-1;};
	for(int i=1;i<=n;i++) a[i]=s[i]-'0',b[i]=t[i]-'0';
	auto sol=[&](int x) {
		int rs=0,y=gt(x),c[4]={-1,-1,y,1},d[4]={-1,y,-1,1};
		for(int i=1;i<=n;i++)
			dp[i][0]=max({dp[i-1][0],dp[i-1][2],0})+c[a[i]<<1|b[i]],
			dp[i][1]=max({dp[i-1][1],dp[i-1][2],0})+d[a[i]<<1|b[i]],
			dp[i][2]=max({dp[i-1][0],dp[i-1][1],dp[i-1][2],0})+gt(a[i])+gt(b[i]),
			cmax(rs,max({dp[i][0],dp[i][1],dp[i][2]}));
		return rs-(x?m*2:0);
	};
	wr(max(sol(0),sol(1)),"\n");
}
```

---

## 作者：gcx12012 (赞：0)

### 前言
一道有点套路但不多的题。
### Solution
特殊性质 A 和 $n^2$ 已经把正解喂给你了，需要一些些脑子即可。

首先我们考虑 yy 的最优策略是什么，我们发现：当 youyou 在某一列上下两格一黑一白，**仅**选择黑的那一格的时候，yy 一定会选择翻转，这样原本这一列对答案的贡献从 +1 变成了 -1。

然后设 youyou 进行了 $k$ 次选择，那么当 $0 \le k \le m$ 时，对答案的贡献是 $-k$，而当 $k>m$ 时，对答案的贡献是 $k-2m$。

显然 youyou 进行上述的选择次数要么尽量少，要么尽量多，由此我们可以得出进行两次 dp 的做法，第一次将一黑一白的格子设为全白，第二次将**仅**选择一列一黑一白的黑格子对答案的贡献设为 +1，然后第二次 dp 的时候将求得的值减去 $2m$。

然后我们设 $f_{i,S}$ 为当前选到第 $i$ 列时所选的状态为 $S$，答案的最大值，对每一个点初始化，然后从左到右转移，这样的时间复杂度是 $O(n^2)$ 的。

接着观察特殊性质 A，我们发现只需要做个最大子段和即可，然后我们回忆一下最大子段和的递推转移方程。
$$
f_{i,0}=\max(f_{i-1,0},f_{i-1,1})
$$
$$
f_{i,1}=\max(0,f_{i-1,1})+a_i
$$
其中 $f_{i,0}$ 表示历史最大子段和，$f_{i,1}$ 表示以 $i$ 为右端点的最大子段和。

我们考虑结合上述式子，重新写出状态转移方程，状态设计还是不变，就可以通过此题，时间复杂度是 $O(n)$。

详细转移见代码。
### Code

```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define N 2000010
#define For(i,a,b) for(int i=a;i<=b;++i)
#define Rof(i,a,b) for(int i=a;i>=b;--i)

using namespace std;
char s[2][N];
int f[N][4];
int T,n,m,ans=0;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

void sol(){
	n=read(),m=read();
	ans=0;
	For(i,0,3) fill(f[i],f[i]+n+1,0);
	For(i,0,1){
		For(j,1,n){
			cin>>s[i][j];
		}
	}
	For(i,1,n){
		f[i][0]=max(max(f[i-1][0],f[i-1][1]),max(f[i-1][2],f[i-1][3]));
		if(s[0][i]=='0' && s[1][i]=='0'){
			f[i][1]=max(max(0,f[i-1][1]),f[i-1][3])-1;
			f[i][2]=max(max(0,f[i-1][2]),f[i-1][3])-1;
			f[i][3]=max(max(0,f[i-1][1]),max(f[i-1][2],f[i-1][3]))-2;
		}
		if(s[0][i]=='0' && s[1][i]=='1'){
			f[i][1]=max(max(0,f[i-1][1]),f[i-1][3])-1;
			f[i][2]=max(max(0,f[i-1][2]),f[i-1][3])+1;
			f[i][3]=max(max(0,f[i-1][1]),max(f[i-1][2],f[i-1][3]));
		}
		if(s[0][i]=='1' && s[1][i]=='0'){
			f[i][1]=max(max(0,f[i-1][1]),f[i-1][3])+1;
			f[i][2]=max(max(0,f[i-1][2]),f[i-1][3])-1;
			f[i][3]=max(max(0,f[i-1][1]),max(f[i-1][2],f[i-1][3]));
		}
		if(s[0][i]=='1' && s[1][i]=='1'){
			f[i][1]=max(max(0,f[i-1][1]),f[i-1][3])+1;
			f[i][2]=max(max(0,f[i-1][2]),f[i-1][3])+1;
			f[i][3]=max(max(0,f[i-1][1]),max(f[i-1][2],f[i-1][3]))+2;
		}
	}
	ans=max(ans,max(max(f[n][0],f[n][1]),max(f[n][2],f[n][3]))-2*m);
	For(i,0,3) fill(f[i],f[i]+n+1,0);
	For(i,1,n){
		f[i][0]=max(max(f[i-1][0],f[i-1][1]),max(f[i-1][2],f[i-1][3]));
		if(s[0][i]=='0' && s[1][i]=='0'){
			f[i][1]=max(max(0,f[i-1][1]),f[i-1][3])-1;
			f[i][2]=max(max(0,f[i-1][2]),f[i-1][3])-1;
			f[i][3]=max(max(0,f[i-1][1]),max(f[i-1][2],f[i-1][3]))-2;
		}
		if(s[0][i]=='0' && s[1][i]=='1'){
			f[i][1]=max(max(0,f[i-1][1]),f[i-1][3])-1;
			f[i][2]=max(max(0,f[i-1][2]),f[i-1][3])-1;
			f[i][3]=max(max(0,f[i-1][1]),max(f[i-1][2],f[i-1][3]));
		}
		if(s[0][i]=='1' && s[1][i]=='0'){
			f[i][1]=max(max(0,f[i-1][1]),f[i-1][3])-1;
			f[i][2]=max(max(0,f[i-1][2]),f[i-1][3])-1;
			f[i][3]=max(max(0,f[i-1][1]),max(f[i-1][2],f[i-1][3]));
		}
		if(s[0][i]=='1' && s[1][i]=='1'){
			f[i][1]=max(max(0,f[i-1][1]),f[i-1][3])+1;
			f[i][2]=max(max(0,f[i-1][2]),f[i-1][3])+1;
			f[i][3]=max(max(0,f[i-1][1]),max(f[i-1][2],f[i-1][3]))+2;
		}
	}
	ans=max(ans,max(max(f[n][0],f[n][1]),max(f[n][2],f[n][3])));
	printf("%d\n",ans);
}

int main()
{
	//fprintf(stderr,"%.2lf",(&ed-&st)/1024.0/1024.0);
	//freopen("beyond.in","r",stdin);
	//freopen("beyond.out","w",stdout);
	read();
	T=read();
	while(T--) sol();
 	return 0;
}
/*

*/
```

---

## 作者：KinNa_Sky (赞：0)

首先一黑一白的列选一列不亏，黑的一列选了赚，白的一列显然只会选一行用以保持连通性。

然后到现在还没有博弈，因为 yy 的操作不会改变答案。

所以我们发现 **yy 会操作当且仅当 youyou 选了黑白列中的黑行，并且一次操作会使答案 $-2$**。

所以我们有一个策略：先把所有黑白列和黑列选上，白列不选。然后白列划分开了若干联通块。

此时分情况：

- 如果黑白列都选一列那么每个联通块的权值就是黑列个数 $\times 2$，然后跑最大子段和。

- 如果黑白列要选黑行，如果选了就要尽可能多选。为了保持连通性，可以 dp 出每个连通块 左上/左下进-右上/右下出 的能选的最多黑行。而最后的答案应减去 $\min(\text{选的黑行数},m) \times 2$。

  考虑到选的黑行少了肯定亏而不会成为答案，所以可以直接减去 $2m$。

  所以同样跑最大子段和，连通块的权值就是黑列个数 $\times 2$ 加上选的黑行数。统计答案时用最大子段和减去 $2m$ 与 $ans$ 取 $\max$。

[Code](https://www.luogu.com/paste/3ohwd72i)

---

