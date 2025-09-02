# [ARC119F] AtCoder Express 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc119/tasks/arc119_f

AtCoder 鉄道には $ N+1 $ 個の駅があり、駅には $ 0 $ から $ N $ までの番号が付けられています。ここではかつて、各 $ i $ $ (0\ \leq\ i\ \leq\ N-1) $ に対して駅 $ i $ と駅 $ i+1 $ の間を双方向に $ 1 $ 分で走行する **普通列車** のみが運行されていました。

しかし、ある日鉄道会社は「光速派」と「準急派」の $ 2 $ つのグループに分裂し、駅 $ 0 $ と駅 $ N $ を除く各駅は光速派と準急派のうち片方が管理することになりました。駅 $ j $ $ (1\ \leq\ j\ \leq\ N-1) $ を管理するグループは文字 $ c_j $ で表され、`A` は光速派が、`B` は準急派が管理すること、`?` はまだ決まっていないことを表します。駅 $ 0 $ と駅 $ N $ は重要な駅なので、両方が管理します。

ここで、光速派と準急派は、普通列車に加えて新たに $ 2 $ 種類の鉄道路線を作ることにしました。

> **光速列車**：光速派が管理する駅の番号を昇順に $ a_0,\ a_1,\ \dots,\ a_s $ として、各 $ k $ に対して駅 $ a_k $ と駅 $ a_{k+1} $ の間を双方向に $ 1 $ 分で走行する。
> 
> **準急列車**：準急派が管理する駅の番号を昇順に $ b_0,\ b_1,\ \dots,\ b_t $ として、各 $ k $ に対して駅 $ b_k $ と駅 $ b_{k+1} $ の間を双方向に $ 1 $ 分で走行する。

`?` の個数を $ q $ として、作られる鉄道路線は $ 2^q $ 通り考えられます。その中で、$ K $ 分以内の乗車で駅 $ 0 $ から駅 $ N $ に行けるようになるものは何通りあるでしょうか？これを $ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 4000 $
- $ 1\ \leq\ K\ \leq\ \frac{N+1}{2} $
- $ N,\ K $ は整数
- $ c_1,\ c_2,\ \dots,\ c_{N-1} $ はそれぞれ `A`、`B`、`?` のいずれか

### Sample Explanation 1

ここでは $ 2^3\ =\ 8 $ 通りの鉄道路線がありえますが、そのうち以下の $ 4 $ 通りについて、$ 3 $ 分以内の乗車で駅 $ 0 $ から駅 $ 8 $ に行くことが可能です。 - 駅 $ 2,\ 3,\ 6 $ を光速派が管理する場合：駅 $ 0\ \rightarrow\ 5\ \rightarrow\ 7\ \rightarrow\ 8 $ と移動する（下図の #1 に対応） - 駅 $ 2,\ 3 $ を光速派が、駅 $ 6 $ を準急派が管理する場合：駅 $ 0\ \rightarrow\ 5\ \rightarrow\ 4\ \rightarrow\ 8 $ と移動する（下図の #2 に対応） - 駅 $ 2 $ を光速派が、駅 $ 3,\ 6 $ を準急派が管理する場合：駅 $ 0\ \rightarrow\ 3\ \rightarrow\ 4\ \rightarrow\ 8 $ と移動する（下図の #4 に対応） - 駅 $ 2,\ 3,\ 6 $ を準急派が管理する場合：駅 $ 0\ \rightarrow\ 1\ \rightarrow\ 4\ \rightarrow\ 8 $ と移動する（下図の #8 に対応） したがって、答えは $ 4 $ 通りとなります。これを図で表すと、以下のようになります。下図においては、赤色が光速派のみが管理する駅や光速列車の路線、青色が準急派のみが管理する駅や準急列車の路線を表すものとします。 !\[ \](https://img.atcoder.jp/arc119/db3f88315c456535f7ce57116009c126.png)

### Sample Explanation 2

ここでは、$ 2^8\ =\ 256 $ 通りの組み合わせすべてについて、駅 $ 0 $ から駅 $ 11 $ まで $ 6 $ 分以内の乗車で行くことが可能です。

### Sample Explanation 3

以下の図に示される $ 10 $ 通りの組み合わせについて、駅 $ 0 $ から駅 $ 16 $ まで $ 5 $ 分以内の乗車で行くことが可能です。 !\[ \](https://img.atcoder.jp/arc119/4b879e19b8c1cd7eac9d52eb0ea58e5c.png)

### Sample Explanation 4

条件を満たすものは $ 1623310324709451 $ 通りありますが、これを $ 10^9\ +\ 7 $ で割った余りである $ 313346281 $ を出力してください。

## 样例 #1

### 输入

```
8 3
A??AB?B```

### 输出

```
4```

## 样例 #2

### 输入

```
11 6
???B??A???```

### 输出

```
256```

## 样例 #3

### 输入

```
16 5
?A?B?A?B?A?B?A?```

### 输出

```
10```

## 样例 #4

### 输入

```
119 15
????????A?????????????????????????BA????????????????????????AB???????A???????????B?????????????????????????????A??????```

### 输出

```
313346281```

# 题解

## 作者：namelessgugugu (赞：20)

很搞不懂为什么另一篇题解要感谢我，但总之写一下自己的做法。

#### 题意

有 $n + 1$ 个点，编号 $0 \sim n$，每个点是 A 型点或 B 型点中的一个（特别地，点 $0$ 和点 $n$ 同时是 AB 型点），点 $i$ 与点 $i + 1$ 之间有一条双向边，每个点与编号比它大的第一个同类型点之间也有一条双向边（例如 A 型点是 $0, 2, 7, n$，则会有边 $(0 ,2), (2, 7), (7, n)$）。

这 $n + 1$ 个点中，有一些点的类型已经确定，有一些还没有确定，求有多少种确定点的类型的方案使得从 $0$ 到 $n$ 的最短路长度不超过 $m$，答案对 $10^9 + 7$ 取模。

$1 \leq n \leq 4000, 1 \leq m \leq \frac{n + 1}{2}$。

#### 题解

先考虑如果所有点的类型都确定了要怎么判定。

把走一条 $(i, i + 1)$ 的边称作走，走同类型之间的边称作跳。

思考最短路可能长什么样，首先每次使用跳跃一定是跳过一整段另一种类型的连续段，而唯一可能往回走的情况是刚刚跳完一次，然后往回走一步走到另一种类型的点，方便继续跳出去。不然的话，可以发现往回走多了总会走到自己曾经到过的点，因此是不优的。

于是发现只需要记录几个信息就能做到判定：只考虑前 $i$ 个点时，第 $i$ 个点是什么类型，从起点到当前最后一个 A 型点的最短路距离，和到最后一个 B 型点的最短路距离。

这个信息也是容易做到转移的，不妨设第 $i$ 个点是 A 类型，两个距离分别是 $d_A, d_B$，则如果 $i + 1$ 是 A 类型，则新的距离 $d_A' = d_A + 1, d_B' = d_B$，否则 $d_A' = \min\{d_A, d_B + 2\}, d_B' = \min\{d_A + 1, d_B + 1\}$。

如果 $i = n - 1$ 时 $\min\{d_A, d_B\} < m$，说明这是一个合法的方案。

于是我们会简单的判定了，而且这个东西是容易套上 DP 的，直接令 $f_{i ,j, k, ty}$ 表示考虑到前 $i$ 个点，两个距离分别是 $j, k$，第 $i$ 个点的类型是 $ty$ 时的方案数即可做到 $O(n^3)$ 的复杂度。

尝试化简状态，还是不妨设 $ty = A$，则会有 $j \geq k - 1$，因为这个 $j$ 其实是从最后一个 B 后面的 A 一步一步走过来的，而设起点到在这个 B 后面的这个 A 的最短路是 $x$，则有 $j \geq x$ 而 $x + 1 \geq k$，所以有 $j \geq k - 1$。同时发现如果 $j$ 比 $k$ 大太多的话，在下一次遇到 B 型点的时候这个 $j$ 就没有用了，而如果一直不遇见 B 型点，最后统计答案时查 $\min\{j, k\}$ 肯定也和 $j$ 没啥关系。具体来说，如果 $j > k + 2$，那么和 $j = k + 2$ 是一样的，可以压进一个状态里。$ty = B$ 同理。

所以，实际上有效的状态被压到了 $O(n ^ 2)$，而转移还是 $O(1)$ 的，故复杂度降到了 $O(n ^ 2)$，可以通过。

#### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N = 2015, mod = 1000000007;
int n, m;
char s[N << 1];
int f[2][N][7][2];
inline int &getf(int o, int x, int y, int ty)
{
	x = std::min(x, y + 2), y = std::min(y, x + 2);
	return f[o][x][y - x + 2][ty];
}
inline void update(int &x, int v)
{
	x = (x + v) % mod;
	return;
}
int main(void)
{
	scanf("%d%d%s", &n, &m, s + 1), --n;
	f[0][0][2][0] = 1;
	for(int i = 0, o = 0;i < n;++i, o ^= 1)
	{
		memset(f[o ^ 1], 0, sizeof(f[o ^ 1]));
		for(int j = 0;j <= m + 2;++j)
			for(int k = j - 2;k <= j + 2;++k)
			{
				if(s[i + 1] != 'B')
				{
					update(getf(o ^ 1, j + 1, k, 0), getf(o, j, k, 0));
					update(getf(o ^ 1, std::min(j + 1, k + 1), std::min(j + 2, k), 0), getf(o, j, k, 1));
				}
				if(s[i + 1] != 'A')
				{
					update(getf(o ^ 1, j, k + 1, 1), getf(o, j, k, 1));
					update(getf(o ^ 1, std::min(k + 2, j), std::min(k + 1, j + 1), 1), getf(o, j, k, 0));
				}
			}
	}
	int ans = 0;
	for(int i = 0;i <= m + 2;++i)
		for(int j = i - 2;j <= i + 2;++j)
			if(std::min(i, j) + 1 <= m)
				ans = (1ll * ans + getf(n & 1, i, j, 0) + getf(n & 1, i, j, 1)) % mod;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：软糖RT (赞：12)

### 前置——

首先我们要先确认如何保证在我们的一次构造中求出其最小的路径长度。

通过一个最简单的策略，我们可以直接设计一个朴素的 dp，令 $f_{x,y,z}$ 表示我们走到第 $x$ 位，离我们最近的 A 点是 $y$，B 点是 $z$。随后一步步的往前走，在出现“?”的时候保存一个 A 点的答案，再保存一个 B 点的答案。由于“?”的存在要求我们填充大量的 $y$ 和 $z$ 的位置，所以这个 dp 是 $O(n^3)$ 级别的，并不能满足我们的要求。

此时我们考虑为什么需要一个这样的转移，其原因在于“?”的存在让我们并不知道我们进入了什么样的一个区段，不知道要怎么跳跃转移，而是选择寻找所有之前的可行点。

如果我们可以约束转移的过程，等于我们明确这个图具备什么样的性质时可以是最优的，那么我们就能快速的进行转移。官方题解是直接优化转移式子。

### 但是——

**自动机**很明显是可以满足我们的需求的另一种选择。

在自动机内的转移状态被固定的时候，自动机的复杂度就只和状态数量，输入的串的长度相关。而我们需要考虑一些步数问题，那么也和我们需要转移的答案规模相关。每一次位置的移动都相当于在自动机上走一步，而“?”则代表两步都会走一次。

自动机内部的边就相当于一个很好的 dp 约束，告诉我们自动机的这个节点的答案只能转移到一个固定的位置。只要我们保证自动机的设计是能跑出最短路的，就能保证我们的答案是正确的。

接下来的问题就是自动机了。让我们来考虑一下最短路的策略。

### 分析

下文的“跳”代指走到一个和自己同类型的点，“走”代指走到一个节点。

很显然的，对于一个长序列“ABBBB...BBBA”，站在第一个 A 时最优的选择是从第一个 A 跳到下一个 A，否则我们就要走完中间的所有 B。

那么我们设计一个节点 AB...BA，表示我们在遇到一串 B 且开头为 A 的情况，对称的我们也需要 B 的节点。

此时的情况大概是这样的，感觉很好理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/u6sl4tky.png)

（原谅我不会用它画自环）

在我们跳完这一步后，我们的位置到达了 A。如果这个序列在我们位置后面还有 A，如“ABBBB...BBBAAAA...AAB”我们应该选择往回走一步到 B 然后跳到下一个 B。

那么我们就要设计一些中继节点来弥补我们“不知道 A 的数量”这一件事，对于 B 我们对称的设计即可。先看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jo1ri6ed.png)

那些存在自环的节点的出边意味着他们发现了这个循环的结束。设计“AB”与“BA”节点是让我们拥有反悔的机会，“BAAAAABABBBBBBB”的最优显然不是让我们在第二个 B 的位置让我们进入循环。

如上，如果中间这一段 A 的数量过少，比起一下子跳过去我们不如一个一个跳，例如“ABBBB...BBBAAB”，在我们跳完第一次 A 后，最优的选择是走一步到下一个 A，这样我们能决定之后是跳 A 还是走 B 跳 B。此时往后走一步再跳到 B 的花费和现在是等价的。

这就必须让我们设计一个新的节点，我们让其表达“这个位置等效于既可以从 A 开始也可以从 B 开始”。有点类似于题目开头的第一个车站。

那么我们再新增一些节点——

![](https://cdn.luogu.com.cn/upload/image_hosting/ovj90ulp.png)

因为 csacademy 画二元环很丑，两个边的边权会重合在一起，所以我多加了一个“0”点，实际上它和“A/B”是一个点。

我们从“A/B”出发的时候，如果连续的遇到了一个“AB”或者“BA”，无论我们起始点是 A 还是 B，我们都能通过跳一步/走一步到到达这个状态。而一旦遇到连续的两个 A 或者 B，进入循环便是有意义的。

然而这个自动机还有一些节点在一些情况下没有出边，我们需要补充它的情况。

“AB”在下一个值是 A 的情况下代表着我们已经进入“A/B”。因为进入“AB”时，我们已经走了一步到 B，而这一步同样可以拿来跳 A。

“AA”在遇到 A 的时候应当还要走一步到“AAA”，因为“BAAABBBBBBBBBA”在我们落点到第一个 A 的时候，只需要走两步就可以到达第三个 A 从而跳到最后一个 A，而向后走一步、再跳一步、再走回来一步需要三步。这个节点的设计也一样是“后悔”，A 的数量大于三时显然可以进入循环，否则我们可以进入“A/B”的状态，因为从第一个 A 到第三个 A 和第二个 B 都是两步。

此时我们的自动机已经每一个点都拥有出边了（csacademy 已经会把这些边堆在一起了，所以手绘）：

![](https://cdn.luogu.com.cn/upload/image_hosting/0s3hm0d2.png)

“BA”和“AB”还需要往“A/B”分别连“B”和“A”边，不好改了/qd。

虽然有点复杂，但是手推一下还是很爽的。

实现的过程就非常简单了，如我们之前所说，遇到一个 A 就让每个节点的值都往 A 走一步，遇到一个 B 就让每个节点的值都往 B 走一步，“?”则各走一步。移动的时候记录一下步数，通过一步一步读入序列跑自动机，最后统计总开销小于 $k$ 的情况。起点显然是“A/B”点。最后的时间复杂度是 $O(13nk)$。其中 $13$ 是我们的节点个数。相比原本的式子，我们不再需要去枚举一个之前的点，少了维护一维的花费。

当然，实际上这张图边的边权各有差异，最后终点统计的时候也不能一下全收（在终点前不一定能到终点），这些具体数值的设定就在代码解释了。

### 码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4004,mod=1000000007;
int tr[14][3],f[N][14][2],pos,n,k,ans;
string s;
inline void init(){
	//边点转化为数值可以自己画画看看对应原图~这种东西大概率是没必要模仿的~
	//原始边，就是最基本的那些移动
	tr[1][1]=2;
	tr[2][1]=3;
	tr[3][2]=4;
	tr[4][2]=5;
	tr[5][2]=6;
	tr[4][1]=7;
	tr[1][2]=8;
	tr[8][2]=9;
	tr[9][1]=10;
	tr[10][1]=11;
	tr[11][1]=12;
	tr[10][2]=13;
	//循环边，两个循环节点的边
	tr[3][1]=3;
	tr[9][2]=9;
	//补偿边，多增加的那些补充部分
	tr[2][2]=1;
	tr[7][1]=3;
	tr[7][2]=1;
	tr[5][1]=7;
	tr[6][1]=1;
	tr[6][2]=9;
	tr[8][1]=1;
	tr[11][2]=13;
	tr[13][1]=1;
	tr[13][2]=9;
	tr[12][1]=3;
	tr[12][2]=1;
} 
inline void dp(int p){
	for(int i=0;i<=k+1;i++){
		for(int j=1;j<=13;j++){
			int to=tr[j][p],val=1;
			if(to==3||to==1||to==9||j==9||j==3){
				val=0;//我定义进出循环节点和进入A/B节点是不需要花费的，这样子很好理解。
			}else if(0){
				val=-1;//原本觉得会有边是这个样子的……
			}else{
				val=1;//正常边都要这么跑
			}
			if(i+val>=0){
				f[i+val][to][pos^1]+=f[i][j][pos];
				f[i+val][to][pos^1]%=mod;
			}
		}
	}
}
signed main(){
	cin>>n>>k;
	init();
	cin>>s;
	f[0][1][0]=1;//第i位的第j个节点走了k步的情况
	for(int i=0;i<s.size();i++,pos^=1){
		if(s[i]=='A'){
			dp(1);
		}else if(s[i]=='B'){
			dp(2);
		}else{
			dp(1);
			dp(2);
		}
		for(int j=0;j<=k+1;j++){
			for(int l=1;l<=13;l++){
				f[j][l][pos]=0;
			}
		}
	}
	for(int i=1;i<=k+1;i++){
		for(int j=1;j<=13;j++){
			if(j==3||j==9||j==12||j==6||j==13||j==7||j==8||j==2){
				if(i<=k){
					ans+=f[i][j][pos];//这些节点多存了一点贡献，他们不需要花费新的。
				}
			}else{
				if(i<k){
					ans+=f[i][j][pos];//其他的节点就需要多走一步进入终点
				}
			}
		}
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

然后我们就解决了！

特在此感谢 [p_b_p_b](https://www.luogu.com.cn/user/76481) 和 [namelessgugugu](https://www.luogu.com.cn/user/244204) 对我的指导，没有二位就没有这篇题解。

---

## 作者：gdf_yhm (赞：6)

[arc119f](https://www.luogu.com.cn/problem/AT_arc119_f)

[AtCoder Express 3](https://atcoder.jp/contests/arc119/tasks/arc119_f)

自动机写法。开始在做的时候题解没讲每个节点代表什么状态，自己推了一遍，记录一下。

### 思路

计数，求有多少种替换方式使得 $0$ 到 $n$ 存在一条长度小于等于 $K$ 的路径。

可以做 $O(n^3)$ 的 dp。设 $dp_{i,a,b}$ 表示前 $i$ 个位置，最近的 $A$ 和 $B$ 分别在 $a$ 和 $b$。官方题解是优化 $a$ 和 $b$，发现有意义状态下 $a$ 和 $b$ 的差不超过一定数值。

观察发现，在 $\text{BAA...AAB}$ 处，肯定选择从 $B$ 直接跳过去。具体的，当有连续的 $4$ 个 $A$ 后，会选择直接从两端的 $B$ 越过。所以有效的状态并不多。

考虑建一个自动机来求出任意状态对应的下一个状态。由于 $A$ 和 $B$ 可以取反得到，先只考虑当前在 $A$，在 $B$ 同理。以下几种有用状态。

- 状态 $0$。当前在 $A$，上一个位置为 $B$，记为 $\text{A}$。

- 状态 $1$ 即状态 $0$ 反过来，记为 $\text{B}$。

- 状态 $2$。当前在 $A$，上一个位置为 $B$，下一个位置为 $A$，记为 $\text{AA}$。

- 状态 $4$。当前在 $A$，上一个位置为 $B$，下两个位置为 $AA$，记为 $\text{AAA}$。

- 状态 $6$。当前在 $A$，上一个位置为 $B$，下三个位置为 $AAA$，记为 $\text{AAAA}$。此时如果往后有 $B$，直接先后退越过；否则走向自己，不会有 $5$ 个 $A$ 的状态。注意到此时无论如何都会后退，所以稍微调整一下。定义状态 $6$ 为当前在 $B$，接下来有连续 $A$ 且一定会选择跳过。

- 状态 $8$。当前在 $A$，上一个位置不重要，下一个位置为 $B$，记为 $\text{AB}$。此时可以跳到下一个 $A$，也可以爬到 $B$，但不知道走一步后要去 $A$ 还是 $B$。

- 状态 $10$ 至 $12$。当前既可以当作在 $A$，也可以当作在 $B$，记为 $\text{O}$，称为状态 $12$。状态 $10$ 表示当前在 $O$，下一个为 $A$，记为 $\text{OA}$。

综上，有 $13$ 种有用状态。

- $\text{A}$，$\text{AA}$，$\text{AAA}$，$\text{AAAA}$，$\text{AB}$。

- 上面 $5$ 种状态取反得到当前在 $B$ 的另外 $5$ 种。

- $\text{OA}$,$\text{OB}$,$\text{O}$。

考虑转移。记 $tree_{i,0/1}$ 表示当前状态为 $i$，加入 $A$ 或 $B$，走向哪一个状态，$val_{i,0/1}$ 为转移的代价。

- 状态 $\text{A}$。如果加入 $A$，走向状态 $\text{AA}$，点没有移动，代价为 $0$。如果加入 $B$，走向状态 $\text{AB}$，点没有移动，代价为 $0$。

- 状态 $\text{AA}$。如果加入 $A$，走向状态 $\text{AAA}$，点没有移动，代价为 $0$。如果加入 $B$，走向状态 $\text{AB}$，点向后移动一格，代价为 $1$。

- 状态 $\text{AAA}$。如果加入 $A$，走向状态 $\text{AAAA}$，点后退一步到上一个 $B$，代价为 $1$。如果加入 $B$，可以先向后再向前越过 $AAA$ 到下一个 $B$，也可以爬两步 $A$，即走向状态 $\text{O}$，代价为 $2$。

- 状态 $\text{AAAA}$。注意这里状态不同于以前，当前点为 $B$。如果加入 $A$，走向状态自己 $\text{AAAA}$，点不动，代价为 $0$。如果加入 $B$，向前越过 $AAAA$ 到下一个 $B$，即走向状态 $\text{B}$，代价为 $1$。

- 状态 $\text{AB}$。如果加入 $A$，可以向后走到 $B$，也可以跳到下一个 $A$，即走向状态 $O$，代价为 $1$。如果加入 $B$，虽然没有连续 $4$ 个 $B$，但一定会从 $A$ 跳过这段 $B$，即状态 $\text{BBBB}$，代价为 $0$。

- 状态 $\text{OA}$。如果加入 $A$，虽然没有连续 $4$ 个 $A$，但一定会把 $O$ 当作 $B$ 跳过这段 $A$，即状态 $\text{AAAA}$，代价为 $0$。如果加入 $B$，可以向后走到 $A$，也可以把 $O$ 当作 $B$ 跳到下一个 $B$，即走向状态 $\text{O}$，代价为 $1$。

- 状态 $\text{O}$。如果加入 $A$，走向状态 $\text{OA}$，代价为 $0$。如果加入 $B$，走向状态 $\text{OB}$，代价为 $0$。

分析完自动机状态的转移，dp 即可。设 $dp_{i,j,k}$ 表示加入前 $i$ 位，走了 $j$ 步，当前状态为 $k$。

$$dp_{0,0,12}=1$$

$$dp_{i+1,j+val_{k,0},tree_{k,0}}+=dp_{i,j,k}$$

$$dp_{i+1,j+val_{k,1},tree_{k,1}}+=dp_{i,j,k}$$

注意到加入一位并不是走到一位。状态设定的当前走到的点不是状态的最后一位。记录 $dis$ 表示状态的最后一位是 $n-1$，状态设定的当前走到的点离终点的距离，稍微处理即可。

复杂度 $O(13nk)$。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=4010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans;
char c[maxn];
int tree[15][2],val[15][2];
int dis[7];
int dp[maxn][maxn][15];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	scanf("%s",c+1);
	tree[0][0]=2;val[0][0]=0;tree[0][1]=8;val[0][1]=0;
	tree[2][0]=4;val[2][0]=0;tree[2][1]=8;val[2][1]=1;
	tree[4][0]=6;val[4][0]=1;tree[4][1]=12;val[4][1]=2;
	tree[6][0]=6;val[6][0]=0;tree[6][1]=1;val[6][1]=1;
	tree[8][0]=12;val[8][0]=1;tree[8][1]=7;val[8][1]=0;
	tree[10][0]=6;val[10][0]=0;tree[10][1]=12;val[10][1]=1;
	tree[12][0]=10;val[12][0]=0;tree[12][1]=11;val[12][1]=0;
	for(int i=0;i<=5;i++){//状态取反。
		for(int k=0;k<=1;k++){
			if(tree[i*2][k^1]==12)tree[i*2+1][k]=tree[i*2][k^1];
			else tree[i*2+1][k]=tree[i*2][k^1]^1;
			val[i*2+1][k]=val[i*2][k^1];
		}
	}
//	for(int i=0;i<=12;i++)cout<<tree[i][0]<<" "<<val[i][0]<<" "<<tree[i][1]<<" "<<val[i][1]<<"\n";
	dis[0]=dis[3]=dis[4]=dis[5]=dis[6]=1;
	dis[1]=dis[2]=2;
	dp[0][0][12]=1;
	for(int i=0;i<=n-2;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<=12;k++){
				if(dp[i][j][k]){
					if(c[i+1]=='A'){
						dp[i+1][j+val[k][0]][tree[k][0]]+=dp[i][j][k];
						dp[i+1][j+val[k][0]][tree[k][0]]%=mod;
					}
					else if(c[i+1]=='B'){
						dp[i+1][j+val[k][1]][tree[k][1]]+=dp[i][j][k];
						dp[i+1][j+val[k][1]][tree[k][1]]%=mod;
					}
					else{
						dp[i+1][j+val[k][0]][tree[k][0]]+=dp[i][j][k];
						dp[i+1][j+val[k][0]][tree[k][0]]%=mod;
						dp[i+1][j+val[k][1]][tree[k][1]]+=dp[i][j][k];
						dp[i+1][j+val[k][1]][tree[k][1]]%=mod;
					}
				}
			}
		}
	}
	for(int j=0;j<=m;j++){
		for(int k=0;k<=12;k++)if(j+dis[k>>1]<=m){
			ans+=dp[n-1][j][k];
			ans%=mod;
		}
	}
	printf("%lld\n",ans);
}
```

---

## 作者：Celtic (赞：4)

一个好想但不好写的做法，不需要用自动机。

容易发现，如果相邻两个位置一个是 A，一个是 B，那么从 $0$ 到 $n$ 的路径一定会经过这两个位置中的一个。并且 $0$ 到这两个位置的最短路差 $\le 1$（因为可以互相走）。

那就可以根据这个来 dp。设 $f_{i,j,0/1,-1/0-1}$ 表示第 $i-1$ 和第 $i$ 个位置一个为 A，一个为 B。第三维表示 AB 还是 BA，第四维表示 $d_i=d_{i-1}+(-1/0/1)$。转移假如说当前是 BA，那就找前面一个 B 的连续段直到一个 A，从这里转移。暴力枚举复杂度是 $O(n^3)$ 的，因为还要枚举一个最短路长度。

考虑优化。如果上一个位置是 $j$，那么当 $i-j$ 比较大的时候一定不会走中间的 B 连续段，而是从两个 A 之间跳。这样的话转移就可以前缀和优化了，只需要枚举前置状态的后三维就行。 $i-j$ 比较小的时候直接暴力枚举。我的代码为了保守一点写的是 $i-j\le 4$ 的时候全都暴力，事实上可能可以更小。

实现上有一些细节，比如说 $0$ 和 $n$ 两种颜色都可以，同时也是必经点。我的处理方法是在开头和结尾加入了两个 `?`。还有一些其他 corner case 读者自行思考。

代码

https://atcoder.jp/contests/arc119/submissions/40448473

---

## 作者：liangbowen (赞：2)

upd：应管理员要求，将「厕所」与「大便」等词去掉了。

[blog](https://www.cnblogs.com/liangbowen/p/18225395)。看完 yhd 的题解看懂了 /bx！

被自动机做法恶心到了，现在也来恶心一下大家。

**以下内容强烈建议自己推一遍，几乎一半是重复的，推完会很爽，并且理解会很深。**

## 设计 DP

暴力 $dp_{i,a,b}$ 表示当前在 $i$，最近的 A/B 在 $a/b$，方案数。这个是三次方的。

考虑优化状态：比如说 $\texttt{BAAAAA...AAB}$ 当前在 B，显然傻逼都知道跳过去最优，那么中间无论有几个 A，state 都是相同的，可以尝试记为同一个 state。

于是直接暴力枚举转移，可以实现一个自动机。

## 列举状态

开始吃【数据删除】！下面标绿的是状态，标红的是当前所在处。

+ $\color{green}\texttt{A}$ 指 $\texttt{B}\color{red}\texttt{A}$，意为当前在 A，前一个是 B，后面的不重要。
+ $\color{green}\texttt{B}$ 指 $\texttt{A}\color{red}\texttt{B}$。
+ $\color{green}\texttt{AA}$ 指 $\texttt{B}\color{red}\texttt{A}\color{black}\texttt{A}$。
+ $\color{green}\texttt{BB}$ 指 $\texttt{A}\color{red}\texttt{B}\color{black}\texttt{B}$。
+ $\color{green}\texttt{AAA}$ 指 $\texttt{B}\color{red}\texttt{A}\color{black}\texttt{AA}$。
+ $\color{green}\texttt{BBB}$ 指 $\texttt{A}\color{red}\texttt{B}\color{black}\texttt{BB}$。
+ $\color{green}\texttt{AAAA}$ 指 $\color{red}\texttt{B}\color{black}\texttt{AAA..AA}$。注意即使 $cnt_A<4$ 但是从 $\texttt{B}$ 直接跳最优的话，也归属于这个 state。
+ $\color{green}\texttt{BBBB}$ 指 $\color{red}\texttt{A}\color{black}\texttt{BBB..BB}$。同上。
+ $\color{green}\texttt{AB}$ 指 $\texttt{?}\color{red}\texttt{A}\color{black}\texttt{B}$。
+ $\color{green}\texttt{BA}$ 指 $\texttt{?}\color{red}\texttt{B}\color{black}\texttt{A}$。
+ $\color{green}\texttt{@}$ 指 $\color{red}\texttt{?}$。注意这里问号的意义是「既可以当作 A 也可以当作 B」。
+ $\color{green}\texttt{@A}$ 指 $\color{red}\texttt{?}\color{black}\texttt{A}$。
+ $\color{green}\texttt{@B}$ 指 $\color{red}\texttt{?}\color{black}\texttt{B}$。

## 转移状态

总计 $13$ 个状态。转移考虑添加 $\texttt{A/B}$，然后尝试用最小代价跑到定义过的状态去。

对于状态 $\color{green}\texttt{A}$ 与 $\color{green}\texttt{B}$，我们有：

+ $\texttt{B}\color{red}\texttt{A}\color{black}\to\texttt{B}\color{red}\texttt{A}\color{black}\texttt{A}$：不用走即有状态 $\texttt{B}\color{red}\texttt{A}\color{black}\texttt{A}$，$\color{green}\texttt{A}\color{black}\xrightarrow{0}\color{green}\texttt{AA}\color{black}\ (\text{add A})$。
+ $\texttt{B}\color{red}\texttt{A}\color{black}\to\texttt{B}\color{red}\texttt{A}\color{black}\texttt{B}$：不用走即有状态 $\color{darkgrey}\texttt{B}\color{red}\texttt{A}\color{black}\texttt{B}$，$\color{green}\texttt{A}\color{black}\xrightarrow{0}\color{green}\texttt{AB}\color{black}\ (\text{add B})$。
+ $\texttt{A}\color{red}\texttt{B}\color{black}\to\texttt{A}\color{red}\texttt{B}\color{black}\texttt{A}$：不用走即有状态 $\color{darkgrey}\texttt{A}\color{red}\texttt{B}\color{black}\texttt{A}$，$\color{green}\texttt{B}\color{black}\xrightarrow{0}\color{green}\texttt{BA}\color{black}\ (\text{add A})$。
+ $\texttt{A}\color{red}\texttt{B}\color{black}\to\texttt{A}\color{red}\texttt{B}\color{black}\texttt{B}$：不用走即有状态 $\texttt{A}\color{red}\texttt{B}\color{black}\texttt{B}$，$\color{green}\texttt{B}\color{black}\xrightarrow{0}\color{green}\texttt{BB}\color{black}\ (\text{add B})$。

对于状态 $\color{green}\texttt{AA}$ 与 $\color{green}\texttt{BB}$，我们有：

+ $\texttt{B}\color{red}\texttt{A}\color{black}\texttt{A}\to\texttt{B}\color{red}\texttt{A}\color{black}\texttt{AA}$：不用走即有状态 $\texttt{B}\color{red}\texttt{A}\color{black}\texttt{AA}$，$\color{green}\texttt{AA}\color{black}\xrightarrow{0}\color{green}\texttt{AAA}\color{black}\ (\text{add A})$。
+ $\texttt{B}\color{red}\texttt{A}\color{black}\texttt{A}\to\texttt{B}\color{red}\texttt{A}\color{black}\texttt{AB}$：往后走一步即有状态 $\color{grey}\texttt{BA}\color{red}\texttt{A}\color{black}\texttt{B}$，$\color{green}\texttt{AA}\color{black}\xrightarrow{1}\color{green}\texttt{AB}\color{black}\ (\text{add B})$。
+ $\texttt{A}\color{red}\texttt{B}\color{black}\texttt{B}\to\texttt{A}\color{red}\texttt{B}\color{black}\texttt{BA}$：往后走一步即有状态 $\color{grey}\texttt{AB}\color{red}\texttt{B}\color{black}\texttt{A}$，$\color{green}\texttt{BB}\color{black}\xrightarrow{1}\color{green}\texttt{BA}\color{black}\ (\text{add A})$。
+ $\texttt{A}\color{red}\texttt{B}\color{black}\texttt{B}\to\texttt{A}\color{red}\texttt{B}\color{black}\texttt{BB}$：不用走即有状态 $\texttt{A}\color{red}\texttt{B}\color{black}\texttt{BB}$，$\color{green}\texttt{BB}\color{black}\xrightarrow{0}\color{green}\texttt{BBB}\color{black}\ (\text{add B})$。

对于状态 $\color{green}\texttt{AAA}$ 与 $\color{green}\texttt{BBB}$，我们有：

+ $\texttt{B}\color{red}\texttt{A}\color{black}\texttt{AA}\to\texttt{B}\color{red}\texttt{A}\color{black}\texttt{AAA}$，往前走一步即有状态 $\color{red}\texttt{B}\color{black}\texttt{AAAA}$，$\color{green}\texttt{AAA}\color{black}\xrightarrow{1}\color{green}\texttt{AAAA}\color{black}\ (\text{add A})$。
+ $\texttt{B}\color{red}\texttt{A}\color{black}\texttt{AA}\to\texttt{B}\color{red}\texttt{A}\color{black}\texttt{AAB}$，发现走一步啥都到不了，而走两步可以到 $\color{grey}\texttt{BAA}\color{red}\texttt{A}\color{grey}\texttt{B}$（往后两步）或 $\color{grey}\texttt{BAAA}\color{red}\texttt{B}$（往前一步然后跳过去），此时同时可得两个状态 $\color{green}\texttt{A}$ 与 $\color{green}\texttt{B}$，故 $\color{green}\texttt{AAA}\color{black}\xrightarrow{2}\color{green}\texttt{@}\color{black}\ (\text{add B})$。
+ $\texttt{A}\color{red}\texttt{B}\color{black}\texttt{BB}\to\texttt{A}\color{red}\texttt{B}\color{black}\texttt{BBA}$，同上，$\color{green}\texttt{BBB}\color{black}\xrightarrow{2}\color{green}\texttt{@}\color{black}\ (\text{add A})$。
+ $\texttt{A}\color{red}\texttt{B}\color{black}\texttt{BB}\to\texttt{A}\color{red}\texttt{B}\color{black}\texttt{BBB}$，往前走一步即有状态 $\color{red}\texttt{A}\color{black}\texttt{BBBB}$，$\color{green}\texttt{BBB}\color{black}\xrightarrow{1}\color{green}\texttt{BBBB}\color{black}\ (\text{add B})$。

对于状态 $\color{green}\texttt{AAAA}$ 与 $\color{green}\texttt{BBBB}$，我们有：

+ $\color{red}\texttt{B}\color{black}\texttt{AAA..AA}\to\color{red}\texttt{B}\color{black}\texttt{AAA..AAA}$，不用动即为原状态，$\color{green}\texttt{AAAA}\color{black}\xrightarrow{0}\color{green}\texttt{AAAA}\color{black}\ (\text{add A})$。
+ $\color{red}\texttt{B}\color{black}\texttt{AAA..AA}\to\color{red}\texttt{B}\color{black}\texttt{AAA..AAB}$，跳过大段 $\texttt{A}$ 即有状态 $\color{grey}\texttt{BAAA..AA}\color{red}\texttt{B}$，$\color{green}\texttt{AAAA}\color{black}\xrightarrow{1}\color{green}\texttt{B}\color{black}\ (\text{add B})$。
+ $\color{red}\texttt{A}\color{black}\texttt{BBB..BB}\to\color{red}\texttt{A}\color{black}\texttt{BBB..BBA}$，跳过大段 $\texttt{B}$ 即有状态 $\color{grey}\texttt{ABBB..BB}\color{red}\texttt{A}$，$\color{green}\texttt{BBBB}\color{black}\xrightarrow{1}\color{green}\texttt{A}\color{black}\ (\text{add A})$。
+ $\color{red}\texttt{A}\color{black}\texttt{BBB..BB}\to\color{red}\texttt{A}\color{black}\texttt{BBB..BBB}$，不用动即为原状态，$\color{green}\texttt{BBBB}\color{black}\xrightarrow{0}\color{green}\texttt{BBBB}\color{black}\ (\text{add B})$。

对于状态 $\color{green}\texttt{AB}$ 与 $\color{green}\texttt{BA}$，我们有：

+ $\texttt{?}\color{red}\texttt{A}\color{black}\texttt{B}\to\texttt{?}\color{red}\texttt{A}\color{black}\texttt{BA}$，发现不能不走，而走一步可以到 $\color{grey}\texttt{?A}\color{red}\texttt{B}\color{grey}\texttt{A}$（往后一步）或 $\color{grey}\texttt{?AB}\color{red}\texttt{A}$（跳过 $\texttt{B}$），此时同时可得两个状态 $\color{green}\texttt{A}$ 与 $\color{green}\texttt{B}$，故 $\color{green}\texttt{AB}\color{black}\xrightarrow{1}\color{green}\texttt{@}\color{black}\ (\text{add A})$。
+ $\texttt{?}\color{red}\texttt{A}\color{black}\texttt{B}\to\texttt{?}\color{red}\texttt{A}\color{black}\texttt{BB}$，很明显，无论后续再加 $\texttt{A/B}$ 都会跳过中间的 $\texttt{B}$，故 $\color{green}\texttt{AB}\color{black}\xrightarrow{0}\color{green}\texttt{BBBB}\color{black}\ (\text{add B})$。
+ $\texttt{?}\color{red}\texttt{B}\color{black}\texttt{A}\to\texttt{?}\color{red}\texttt{B}\color{black}\texttt{AA}$，同上，$\color{green}\texttt{BA}\color{black}\xrightarrow{0}\color{green}\texttt{AAAA}\color{black}\ (\text{add A})$。
+ $\texttt{?}\color{red}\texttt{B}\color{black}\texttt{A}\to\texttt{?}\color{red}\texttt{B}\color{black}\texttt{AB}$，同上上上，$\color{green}\texttt{BA}\color{black}\xrightarrow{1}\color{green}\texttt{@}\color{black}\ (\text{add B})$。

对于状态 $\color{green}\texttt{@}$，我们有：

+ $\color{red}\texttt{?}\color{black}\to\color{red}\texttt{?}\color{black}\texttt{A}$，不用走即有状态 $\color{red}\texttt{?}\color{black}\texttt{A}$，$\color{green}\texttt{@}\color{black}\xrightarrow{0}\color{green}\texttt{@A}\color{black}\ (\text{add A})$。
+ $\color{red}\texttt{?}\color{black}\to\color{red}\texttt{?}\color{black}\texttt{B}$，不用走即有状态 $\color{red}\texttt{?}\color{black}\texttt{B}$，$\color{green}\texttt{@}\color{black}\xrightarrow{0}\color{green}\texttt{@A}\color{black}\ (\text{add B})$。

对于状态 $\color{green}\texttt{@A}$ 与 $\color{green}\texttt{@B}$，我们有：

+ $\color{red}\texttt{?}\color{black}\texttt{A}\color{black}\to\color{red}\texttt{?}\color{black}\texttt{AA}$，最优显然是将 $\texttt{?}\to\texttt{B}$ 然后跳过大段 $\texttt{A}$，所以 $\color{green}\texttt{@A}\color{black}\xrightarrow{0}\color{green}\texttt{AAAA}\color{black}\ (\text{add A})$。
+ $\color{red}\texttt{?}\color{black}\texttt{A}\color{black}\to\color{red}\texttt{?}\color{black}\texttt{AB}$，走一步可以到 $\color{grey}\texttt{A}\color{red}\texttt{A}\color{grey}\texttt{B}$（将 $\texttt{?}\to\texttt{A}$ 然后向后走一步）或 $\color{grey}\texttt{BA}\color{red}\texttt{B}$（将 $\texttt{?}\to\texttt{B}$ 然后向后走跳一步），此时同时可得两个状态 $\color{green}\texttt{A}$ 与 $\color{green}\texttt{B}$，所以 $\color{green}\texttt{@A}\color{black}\xrightarrow{1}\color{green}\texttt{@}\color{black}\ (\text{add B})$。
+ $\color{red}\texttt{?}\color{black}\texttt{B}\color{black}\to\color{red}\texttt{?}\color{black}\texttt{BA}$，同上，$\color{green}\texttt{@B}\color{black}\xrightarrow{1}\color{green}\texttt{@}\color{black}\ (\text{add A})$。
+ $\color{red}\texttt{?}\color{black}\texttt{B}\color{black}\to\color{red}\texttt{?}\color{black}\texttt{BB}$，同上上上，$\color{green}\texttt{@B}\color{black}\xrightarrow{1}\color{green}\texttt{@}\color{black}\ (\text{add B})$。

## 重写 DP

最后定义 $dp_{i,j,s}$ 表示前 $i$ 个点走了 $j$ 步，当前所在状态为 $s$，方案数。

初始化 $dp_{0,0,\color{green}\texttt{?}\color{black}}=1$，跑上述自动机刷表转移即可。

小细节：状态所在的位置不是最终 $n+1$ 点所在位置，所以还需要记一下 $dis_s$ 表示状态 $s$ 还要走多少步到达终点。

具体地，$dis_{\color{green}\texttt{AA}}=dis_{\color{green}\texttt{BB}}=dis_{\color{green}\texttt{AAA}}=dis_{\color{green}\texttt{BBB}}=2$，其余均为 $1$。判一下统计答案即可。

## 代码实现

可以用 map 记录每个状态的 id，这样写转移会清晰很多。

[code](https://atcoder.jp/contests/arc119/submissions/54014177)，时间复杂度 $O(nk|S|)$，其中 $|S|=13$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc119_f)

**题目大意**

> 给定节点 $0\sim n$，用一条 $i,i+1$ 的链连接。
>
> $1\sim n-1$ 有黑白两种颜色，每个点会向其同色前驱后继连双向边（不存在设为 $0/n$）。
>
> 已知一些点的颜色，求有多少种染色方法使得 $0,n$ 之间最短路长度 $\le m$。
>
> 数据范围：$n,m\le 4000$。

**思路分析**

设 $f_{i,j,k,0/1}$ 表示前 $i$ 个点，到最后一个白色，黑色点的最短距离为 $j,k$，第 $i$ 个点的颜色为白或黑的方案数。

设当前颜色为白，那么再加入一个白点会令 $j\gets j+1$，加入一个黑点会令 $j\gets \min(k+2,j),k\gets \min(j+1,k+1)$。

暴力转移复杂度 $\mathcal O(nm^2)$，考虑优化状态数。

依然设当前颜色为白，那么我们发现 $j$ 应该会 $\ge k$，取出最后一个黑点的下一个白点，设其最短距离为 $x$，那么此时 $k\le x+1$ 因为可以从该点往回走一步，并且由于要面对连续的一段白点，那么 $j\ge x$。

因此 $j\ge k-1$。

我们又发现如果 $j$ 比 $k$ 大很多的时候，计算答案时不太可能用 $j$ 更新最短距离。

如果 $j>k+2$，那么填一个黑色格子后 $j$ 就会被 $k+2$ 覆盖，如果不填黑色格子那么 $j$ 始终 $>k$。

因此我们只要维护 $j'=\min(k+2,j)$。

那么我们此时维护的状态 $j',k'$ 就有 $|j'-k'|\le 2$，状态数 $\mathcal O(m)$。

时间复杂度 $\mathcal O(nm)$。

**代码呈现**

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN=4005,MOD=1e9+7;
inline void add(int &x,const int &y) { x=(x+y>=MOD)?x+y-MOD:x+y;}
int f[MAXN][5][2],g[MAXN][5][2];
char s[MAXN];
signed main() {
	int n,m;
	scanf("%d%d%s",&n,&m,s+1);
	f[0][2][0]=1;
	for(int i=1;i<n;++i) {
		memset(g,0,sizeof(g));
		auto upd=[&](int j,int k,int o,const int &w) {
			j=min(j,k+2),k=min(k,j+2),add(g[j][k-j+2][o],w);
		};
		for(int j=0;j<=m+2;++j) for(int k=j-2;k<=j+2;++k) {
			const int &w0=f[j][k-j+2][0],&w1=f[j][k-j+2][1];
			if(s[i]!='B') {
				upd(j+1,k,0,w0);
				upd(min(j+1,k+1),min(j+2,k),0,w1);
			}
			if(s[i]!='A') {
				upd(min(j,k+2),min(j+1,k+1),1,w0);
				upd(j,k+1,1,w1);
			}
		}
		memcpy(f,g,sizeof(f));
	}
	int ans=0;
	for(int j=0;j<=m+2;++j) for(int k=j-2;k<=j+2;++k) if(min(j,k)+1<=m) {
		add(ans,f[j][k-j+2][0]),add(ans,f[j][k-j+2][1]);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

