# [ABC386D] Diagonal Separation

## 题目描述

有一个 $N \times N$ 的网格，高桥君希望将每个格子涂成黑色或白色，并满足以下条件：

- 对于每一行，存在一个整数 $i$（$0 \leq i \leq N$），该行从左到右的前 $i$ 个格子是黑色，其余的为白色。
- 对于每一列，存在一个整数 $i$（$0 \leq i \leq N$），该列从上到下的前 $i$ 个格子是黑色，其余的为白色。

目前已有 $M$ 个格子被涂上了颜色。具体来说，第 $i$ 个被涂色的格子位于第 $X_i$ 行、第 $Y_i$ 列。如果 $C_i$ 为 `B`，表示该格子已经被涂黑；如果 $C_i` 为 `W`，则表示该格子已经被涂白。

请判断剩下的 $N^2 - M$ 个格子是否可以通过适当选择颜色来满足上述所有条件。

## 说明/提示

- $1 \leq N \leq 10^9$
- $1 \leq M \leq \min(N^2, 2 \times 10^5)$
- $1 \leq X_i, Y_i \leq N$
- 任意两个不同的 $i$，$(X_i, Y_i) \neq (X_j, Y_j)$
- $C_i$ 为 `B` 或 `W`

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 3
4 1 B
3 2 W
1 3 B```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2
1 2 W
2 2 B```

### 输出

```
No```

## 样例 #3

### 输入

```
1 1
1 1 W```

### 输出

```
Yes```

## 样例 #4

### 输入

```
2289 10
1700 1083 W
528 967 B
1789 211 W
518 1708 W
1036 779 B
136 657 B
759 1497 B
902 1309 B
1814 712 B
936 763 B```

### 输出

```
No```

# 题解

## 作者：xiaoke2021 (赞：7)

喜报：

![](https://cdn.luogu.com.cn/upload/image_hosting/j3r05xw8.png)

---

当然啦，你可以用三维偏序来写这题（我们班的一位 dalao 就是这么做的）。但这对蒟蒻来说有点离谱，所以介绍简单方法。

首先证明一个结论：每个白色方块的右下方不能有黑色方块（包括白色方块下面一列和右边一行）。

很容易证明：既然这个位置有一个白色方块，那么它的下面和右边必然都**需要**是白色（由题意得）。那么，对于这个白色方块的下面和右边的每一个白色方块，都适用上述规则，所以右下角都不应有黑色方块。上一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mmcxkhv7.png)

问题是如何判断是否存在上述情况。

考虑排序。以行的从小到大为第一关键字，以白色方块排在黑色方块前为第二关键字（后面会解释为什么要这样）。

将所有方块排序后，从前往后枚举每一个方块。维护一个值，使其存储**最靠左**的白色方块的列的值。接下来，若有黑色方块在这一列右边（包括这一列），那么摆放不合法；反之，若没有这种方块，则摆放合法。

接下来解释为什么要将白色方块摆在前面。如下图，我们多放一个黑色方块。

![](https://cdn.luogu.com.cn/upload/image_hosting/co2610ij.png)

此时，若先枚举第三行的黑色方块，会发现左侧白色方块还没被计算，此时最靠左的白色方块的列的值还没有被统计到，这个值应当为无穷大，所以黑色的摆放会被认为是合法的，这显然违反题意。


```cpp
#include<bits/stdc++.h>
using namespace std;
struct T{
	int x,y;
	char c;
}node[200000+5];
int n,m;
int wy=2147483647; // 维护的值，初始设为无穷大
bool cmp(T a,T b){
	if(a.x==b.x) return a.y<b.y;
	else return a.x<b.x;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		char c;
		cin>>node[i].x>>node[i].y>>node[i].c;
	}
    sort(node+1,node+1+m,cmp); // 结构体排序
	for(int i=1;i<=m;i++){
		if(node[i].c=='W') wy=min(wy,node[i].y); // 是白色就维护最左侧的白色方块的列的值
		else if(node[i].y>=wy){ // 是黑色就判断是否合法
			cout<<"No";
			return 0;
		}
	}
    cout<<"Yes";
	return 0;
}

```

---

## 作者：LionBlaze (赞：5)

题目大意：有一个 $N \times N$ 的网格，每个格子可能是黑色或白色，网格有一些 amazing 的性质：

- 网格的每一行都有一个分界线（可能在最左端或最右端），分界线左边都是黑色，右边都是白色。
- 列同理，分界线上面都是黑色，下面都是白色。

现在，网格中有 $M$ 个格子的状态是已知的，请求出有没有符合条件的网格。

---

前情提要：我们用 $M_b$ 代表已知的黑格数量，$M_w$ 代表已知的白格数量。

我们先分析一下在 $(x,y)$ 点处是黑格能够确定什么信息吧。

首先，根据 $(x,y)$ 为黑，得到 $\forall 1 \le i \le y$，都有 $(x,i)$ 为黑。

然后，如果 $(x,i)$ 为黑，则 $\forall 1 \le j \le x$，都有 $(i,j)$ 为黑。

所以，我们得到 $\forall 1 \le i \le x, 1 \le j \le y$，都有 $(i,j)$ 为黑。

这样，左上角为 $(1,1)$，右下角为 $(x,y)$ 的长方形中的所有方格均为黑色。

相似地，我们可以得到如果 $(x,y)$ 为白，那么左上角 $(x,y)$ 右下角 $(N,N)$ 的长方形中均为白色。

于是，如果无解，那么肯定是有某个方格 $(x,y)$ 由于某个 $(x_1,y_1)$ 为黑色（$x_1 \ge x, y_1 \ge y$）所以为黑，但是又因为某个 $(x_2,y_2)$ 为白色（$x \ge x_2, y \ge y_2$），导致矛盾。

我们容易推出，如果有 $(x_1,y_1)$ 是已知的黑色，$(x_2,y_2)$ 是已知的白色，并且 $x_1 \ge x_2$ 并且 $y_1 \ge y_2$，也就是黑格在白格的右下方（正右方，正下方也可以），则无解。

如果暴力枚举每个黑色和白色，则时间复杂度 $\Theta(M_bM_w)=\mathcal O(M^2)$ 无法承受。

我们可以想到，把所有黑格和白格按照 $x$ 坐标排序，然后枚举每一个白格，这样就可以不用判断地得出哪些黑格的 $x$ 坐标不小于这个白格了。但是怎么判断是否有黑格 $y$ 坐标也不小于这个白格？

显然，有黑格的 $y$ 坐标不小于这个白格，意味着这些黑格的 $y$ 坐标最大值不小于这个白格。于是我们可以用一个最小值数组 $m_{i}$ 代表排序后的第 $i \sim M_b$ 个黑格的 $y$ 坐标的最大值。

小细节：怎么样找出第一个 $x$ 坐标值不小于某个给定的 $x$ 的黑格（当然已经排序）？

第一种方法是二分。非常简单，就不说了。单次时间复杂度 $\Theta(\log n)$，事实上可以“优化”为 $\mathcal O(\log n)$，不过最坏都一样。

第二种方法是用一个指针来记录，因为实际需求是给定的 $x$ 坐标增大（因为白格也排过序），所以这个下标也必然一直增大（至少不会减少），所以就可以从上次的下标开始枚举。单次时间复杂度 $\mathcal O(n)$，但是均摊时间复杂度 $\Theta(1)$，所以总时间复杂度还是 $\mathcal O(n)$（为什么 $n \times \Theta(1) = \mathcal O(n)$？因为可能不会延伸到末尾）。

---

代码很简单，逐部分讲一下吧。

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

class black
{
public:
	int x, y;
} blacks[200005];
class white
{
public:
	int x, y;
} whites[200005];
int ymax[200005];
```

这里是类（其实除了默认访问权限不同，和结构体是一样的）的定义，黑格和白格。

另外这里还有一个 `ymax` 数组，其实就是我们讲的最小值 $m$ 数组。

```cpp
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	int bcur = 0, wcur = 0;
	for(int i=1;i<=m;i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		getchar();
		char c = getchar();
		if(c == 'B') blacks[++bcur] = {x, y};
		else whites[++wcur] = {x, y};
	}
	sort(blacks + 1, blacks + bcur + 1, [](const black &x, const black &y) { return x.x < y.x; });
	sort(whites + 1, whites + wcur + 1, [](const white &x, const white &y) { return x.x < y.x; });
```

输入&排序，刚才讲的挺清楚的了。这里用到了一个叫做 lambda 表达式的语法，其实可以理解为简单的函数。（其实还是有挺大区别的，但是重点不在这里）

```cpp
for(int i=bcur;i>=1;i--)
{
	if(blacks[i].y > ymax[i+1]) ymax[i] = blacks[i].y;
	else ymax[i] = ymax[i+1];
}
blacks[bcur+1].x = 2147483647;
```

这里就是预处理 $m$ 数组了。后面还有一句代码，是一个小细节，因为如果 $i > M_b$，则由于 `blacks` 是全局的，所以 `blacks[i].x` 是 $0$，导致后面无限循环然后数组越界。一发罚时。

```cpp
int bptr = 0;
for(int i=1;i<=wcur;i++)
{
	while(blacks[bptr].x < whites[i].x)
	{
		bptr++;
	}
	if(ymax[bptr] >= whites[i].y)
	{
		printf("No\n");
		return 0;
	}
}
printf("Yes\n");
return 0;
}
```

`while(blacks[bptr].x < whites[i].x)` 就是刚刚讲的小细节，如果没有则会导致 `blacks[bptr].x == 0`，然后 `bptr` 就飞了。

其余部分说的挺清楚了，这里不再赘述。

---

## 作者：Drifty (赞：2)

### Solution

会发现题目实际上等价于判断每个白色点右下方有没有黑色点。

会发现直接维护很不好做。我们考虑排序。

如果我们按照 $x$ 为第一关键字，$y$ 为第二关键字排序，那么实际上由于 $x$ 是递增的，对于纵坐标我们贪心地去想，会发现我们如果取当前纵坐标最大的白色点，由于接下来的黑点一定都在这个白色点的右方，那么只要判断黑点的纵坐标是否小于等于那个白色点的纵坐标就可以了。

[My Submission.](https://atcoder.jp/contests/abc386/submissions/61177199)

---

## 作者：Yuexingfei_qwq (赞：2)

赛时没过，谨此以篇纪念一下。
## 思路  
这题显然如果有白色点在黑色点的左上方就可以直接输出`No`了。

首先对输入的所有点排序，用 $p_{i + 1}$ 表示前 $i$ 个点中的白色点的 $y$ 坐标最小值，用 $s_i$ 表示后 $i$ 个点中的黑色点的 $y$ 坐标最大值，接着将 $p$ 数组和 $s$ 数组处理出来。

最后遍历 $p$ 数组和 $s$ 数组（注意此处要遍历到 $m + 1$ 的位置），如果`p[i] <= s[i]`就输出`No`并且终止程序；如果遍历完了还没有终止，输出`Yes`。
## AC CODE
赛时代码。  

```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int n, m;
struct Info {
	int x, y;
	char c;
} a[210000];

inline bool cmp(Info x, Info y) {
	if (x.x != y.x) {
		return x.x < y.x;
	}
	return x.y < y.y;
}

int p[210000], s[210000];

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> n >> m;
	F(i, 1, m, 1) {
		cin >> a[i].x >> a[i].y >> a[i].c;
	}
	std::sort(a + 1, a + m + 1, cmp);
	F(i, 0, m + 1, 1) {
		p[i] = inf;
		s[i] = -inf;
	}
	F(i, 1, m, 1) {
		p[i + 1] = p[i];
		if (a[i].c == 'W') {
			p[i + 1] = std::min(p[i + 1], a[i].y);
		}
	}
	for (int i = m; i; i--) {
		s[i] = s[i + 1];
		if (a[i].c == 'B') {
			s[i] = std::max(s[i], a[i].y);
		}
	}
	F(i, 1, m + 1, 1) {
		if (p[i] <= s[i]) {
			cout << "No" << el;
			r0;
		}
	}
	cout << "Yes" << el;
	r0;
}
```

[AC记录](https://atcoder.jp/contests/abc386/submissions/61221528)

---
完结~~不~~散花。

---

## 作者：_zqh_ (赞：1)

分析题面，发现题目求的是是否存在一个白点被 $(1, 1)$ 和任意一个黑点围成的矩形内。

枚举所有的白点。

找到所有横坐标不比该白点横坐标小的所有黑点的纵坐标的最大值所属点。

- 如果该点的纵坐标小于该白点的纵坐标：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/35wlb8vq.png)

  （蓝点代表题目中的白点，红点反之，右下角的红点为题目已染色的点）
  
  此时当前白点没有被任何一个黑点构成的矩形覆盖，满足题目要求，枚举下一个白点。

- 否则：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/xltozsgy.png)

  当前白点被至少一个黑点构成的矩形覆盖，不满足要求。

  输出 `No` 舍掉。

其余的输出 `Yes`。

---

以上的维护方法有很多，我的方法是二分、后缀最大值，可以参考一下。

先将所有黑点按 $x$、$y$ 坐标排序。

横坐标不比该白点横坐标小的编号最小的点可以通过二分找到。

此时只需要求出该点后的所有点的纵坐标最大值即可。

而这个可以通过后缀最大值来维护。

```cpp
#include <bits/stdc++.h>
// #define int long long
#define pii pair<int, int>
#define FRE(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define ALL(x) x.begin(), x.end()
using namespace std;

int _test_ = 1;

const int N = 2e5 + 5;

int n, m, tb, tw, mx[N];
pii B[N], W[N]; // 黑白点

void init() {}

void clear() {}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int l, r;
		char c;
		cin >> l >> r >> c;
		if (c == 'B') B[++tb] = {l, r};
		else W[++tw] = {l, r};
	}
	sort(B + 1, B + tb + 1); // 排序
	for (int i = tb; i >= 1; i--) {
		mx[i] = max(mx[i + 1], B[i].second); // 后缀最大纵坐标
	}
	for (int i = 1; i <= tw; i++) { // 枚举白点
		int t = lower_bound(B + 1, B + tb + 1, W[i]) - B; // 二分第一个不比该点横坐标小的点
		if (mx[t] >= W[i].second) return cout << "No", void(); // 不合法就舍掉
	}
	cout << "Yes";
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
//	cin >> _test_;
	init();
	while (_test_--) {
		clear();
		solve();
	}
	return 0;
}
```

---

## 作者：Emplace (赞：1)

## 思路
如果一个黑点的左上角有白点，那么一定不合法，来证明一下。

先给一张图（黄点为白，黑点为黑）。

![](https://cdn.luogu.com.cn/upload/image_hosting/o8l6hcw4.png)

如图，如果一个点为白点，那他的右边与下边必定为白。那其中必定有一个白点使得它右下角的黑点在它的右边或下边。

## 具体实现
先按 $x$ 从小到大排序。那么就能保证后面的点绝对在前面的点下面。

然后再枚举一遍，因为要求黑色左上角是否有白色。上已经保证了，那来看左。我们直接求出上面最左边的即可，这个可以在枚举时直接取当前白点 $y$ 的最小值，让我对于每一个黑点看它的 $y$ 值是否大于那个最小值，如果大于那么肯定不合格（因为已经保证了上面）。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f;
struct node{
	int x,y;
	char op;
}t[300000];
bool cmp(node s1,node s2){
	if(s1.x==s2.x){
		return s1.y<s2.y;
	}
	else{
		return s1.x<s2.x;
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>t[i].x>>t[i].y>>t[i].op;
	}
	int miy=n+1;
	sort(t+1,t+1+m,cmp);
	for(int i=1;i<=m;i++){
		if(t[i].op=='W'){
			miy=min(miy,t[i].y);
		}
		else if(miy<=t[i].y){
			cout<<"No";
			return 0;
		}
	}	
	cout<<"Yes";
}
```

---

## 作者：K_yuxiang_rose (赞：0)

这道题可以简化为判断黑格子的左、上方是否存在白格子。

考虑开两个结构体，分别记录黑格子和白格子，输入完后将黑格子按横坐标为第一关键字，纵坐标为第二关键字排序，并统计一下后缀纵坐标最大值。然后对于每个白格子进行二分，寻找**横坐标不小于这个白格子的横坐标的横坐标最小的黑格子**，如果这个黑格子的后缀最大值比这个白格子的纵坐标大，说明存在一个黑格子，使得这个黑格子的横坐标、纵坐标都比这个白格子大，此时直接输出无解即可。

如果所有白格子都满足条件，说明有解，输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node1
{
	int xb,yb,end;
}ab[200005];
struct node2
{
	int xw,yw;
}aw[200005];
int cnt1,cnt2;
bool cmp(node1 a,node1 b)
{
	if(a.xb!=b.xb)
	return a.xb<b.xb;
	return a.yb<b.yb;
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		char c;
		cin>>x>>y>>c;
		if(c=='B')
		{
			cnt1++;
			ab[cnt1].xb=x;
			ab[cnt1].yb=y;
		}
		else
		{
			cnt2++;
			aw[cnt2].xw=x;
			aw[cnt2].yw=y;
		}
	}
	sort(ab+1,ab+cnt1+1,cmp);
	for(int i=cnt1;i>=1;i--) ab[i].end=max(ab[i+1].end,ab[i].yb);
	for(int i=1;i<=cnt2;i++)
	{
		int x=aw[i].xw,y=aw[i].yw;
		int l=1,r=cnt1,cnt=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(ab[mid].xb>=x) r=mid-1,cnt=mid;
			else l=mid+1;
		}
		if(y<=ab[cnt].end)
		{
			cout<<"No";
			return 0;
		}
	} 
	cout<<"Yes";
	return 0;
}
```

---

## 作者：lyas145 (赞：0)

题目在[这里](https://www.luogu.com.cn/problem/AT_abc386_d)。

## 解题思路

一眼 **CDQ 分治**板子题。

题目其实可以简化成：坐标 $(x,y)$ 表示从上边开始第 $x$ 行，从左边开始第 $y$ 列，判断黑格子左上方有没有白格子，如果有，输出 `No`；否则输出 `Yes`。

为了方便，下面将把涂过色的格子简称为格子。

我们可以**以纵坐标为第一关键字、横坐标为第二关键字**把所有的格子**排个序**，这样就能保证我们在处理第 $i$（$1 \le i \le M$）个格子时，第 $j$（$1 \le j < i$）个格子**一定在第 $i$ 个格子的左面或正上面**。

既然我们已经知道哪些格子在当前格子的左面或正上面了，那么怎么判断这些格子中是否有格子在当前格子的上面呢？非常简单，可以把横坐标**离散化**一下，以离散化后的横坐标为下标，用**树状数组**维护即可。

之后是每个格子的处理，从 $1$ 到 $M$ 把每个格子挨个扫一遍，假设我们扫到了第 $i$ 个格子，那么有以下两种情况：  
- 如果第 $i$ 个格子是**黑色**的，找找它左上方有没有白格子即可。
- 如果第 $i$ 个格子是**白色**的，把它的横坐标离散化后加入树状数组即可。

## 码儿

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int,int> PII;
const int N=2e5+5;
int n,m,o;
int c[N],b[N];
struct Node {
	int x,y;
	char c;
	bool operator< (const Node &A)const {
		if (y==A.y) {return x<A.x;}
		return y<A.y;
	}
}a[N];
int lowbit(int x) {return x&-x;}
void add(int x,int p) {
	for (int i=x;i<=m;i+=lowbit(i)) {c[i]+=p;}
}
int query(int x) {
	int res=0;
	for (int i=x;i;i-=lowbit(i)) {res+=c[i];}
	return res;
}
int get(int x) {return lower_bound(b+1,b+1+o,x)-b;}
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) {
		int x,y;
		char c[2];
		scanf("%d%d%s",&x,&y,c);
		a[i]={x,y,c[0]};
		b[i]=x;
	}
	sort(a+1,a+1+m);
	sort(b+1,b+1+m);
	o=unique(b+1,b+1+m)-b-1;
	for (int i=1;i<=m;i++) {
		if (a[i].c=='B') {
			if (query(get(a[i].x))) {puts("No");return 0;}
		}
		else {add(get(a[i].x),1);}
	}
	puts("Yes");
	return 0;
}
```

Thanks for reading！

---

## 作者：_anll_ (赞：0)

感觉比 E 难写。
## 思路
一开始没理解题错了好几发。大概意思就是对于颜色为黑的 $(x,y)$，以其为右下角，$(1,1)$ 为左上角，染黑整个矩形。如果给出的白色点均不在这些被染色矩形中即合法，反之。

先处理黑色点。一个显然的结论是，若 $x_1<x_2$，$y_1 \ge y_2$，不懂的可以手玩一下这里不赘述了。于是就变成了一个后缀 max 问题，稍微离散一下就可以结束了。

对于白色点，可以按照 $x$ 的大小进行排序，之后直接遍历判断即可。具体一点就是，对于当前点 $x_i,y_i$，找到第一个大于等于它 $x$ 坐标的染色右下角 $(x_j,y_j)$，如果 $y_i\le y_j$ 则该方案不合法。

## 代码
赛时代码，写得一坨。
```cpp
#include<vector>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,m,inf=1e11;
int xmin,xmax,ymin,ymax,mlen,mp[200005],num[200005];
vector<pair<int,int> > wo,bo;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;int x,y;char a;
	for(int i=1;i<=m;i++){
		cin>>x>>y>>a;
		if(a=='W'){
			wo.push_back({x,y});
			continue;
		}
		bo.push_back({x,y});
	}
	sort(bo.begin(),bo.end());
	int pl=0;
	for(auto m:bo){
		int x=m.first,y=m.second;
		mp[++mlen]=y;num[mlen]=x;pl=x;
	}
	for(int i=mlen;i;i--) mp[i]=max(mp[i],mp[i+1]);
	sort(wo.begin(),wo.end());
	int tot=0;
	for(auto m:wo){
		int x=m.first,y=m.second;
		while(num[tot]<x&&tot<=mlen) tot++;
		if(mp[tot]>=y) return cout<<"No\n",0;
	}
	cout<<"Yes\n";
	return 0;
}
```

---

