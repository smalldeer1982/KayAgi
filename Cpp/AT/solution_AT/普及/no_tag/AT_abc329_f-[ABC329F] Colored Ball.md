# [ABC329F] Colored Ball

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc329/tasks/abc329_f

$ 1,\ 2,\ \ldots,\ N $ の番号がついた $ N $ 個の箱があり、はじめ箱 $ i $ には色 $ C_i $ のボールが $ 1 $ つ入っています。

$ Q $ 個のクエリが与えられるので、これらを順に処理してください。

各クエリは整数の組 $ (a,b) $ によって与えられ、その内容は以下の通りです。

- 箱 $ a $ のボールをすべて箱 $ b $ に移し、その後箱 $ b $ に何種類の色のボールが入っているかを出力する。
 
ただし、箱 $ a $ や箱 $ b $ が空の場合もあることに注意してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ Q\ \leq\ 200000 $
- $ 1\ \leq\ C_i\ \leq\ N $
- $ 1\ \leq\ a,\ b\ \leq\ N $
- $ a\ \neq\ b $
- 入力される数値はすべて整数
 
### Sample Explanation 1

\- $ 1 $ 番目のクエリでは、箱 $ 1 $ のボールをすべて箱 $ 2 $ に移します。箱 $ 2 $ には色 $ 1 $ のボールが $ 2 $ つ入っている状態となるため、$ 1 $ を出力します。 - $ 2 $ 番目のクエリでは、箱 $ 6 $ のボールをすべて箱 $ 4 $ に移します。箱 $ 4 $ には色 $ 2 $ のボールが $ 1 $ つ、色 $ 3 $ のボールが $ 1 $ つ入っている状態となるため、$ 2 $ を出力します。 - $ 3 $ 番目のクエリでは、箱 $ 5 $ のボールをすべて箱 $ 1 $ に移します。箱 $ 1 $ には色 $ 2 $ のボールが $ 1 $ つ入っている状態となるため、$ 1 $ を出力します。 - $ 4 $ 番目のクエリでは、箱 $ 3 $ のボールをすべて箱 $ 6 $ に移します。箱 $ 6 $ には色 $ 1 $ のボールが $ 1 $ つ入っている状態となるため、$ 1 $ を出力します。 - $ 5 $ 番目のクエリでは、箱 $ 4 $ のボールをすべて箱 $ 6 $ に移します。箱 $ 6 $ には色 $ 1 $ のボールが $ 1 $ つ、色 $ 2 $ のボールが $ 1 $ つ、色 $ 3 $ のボールが $ 1 $ つ入っている状態となるため、$ 3 $ を出力します。

## 样例 #1

### 输入

```
6 5
1 1 1 2 2 3
1 2
6 4
5 1
3 6
4 6```

### 输出

```
1
2
1
1
3```

## 样例 #2

### 输入

```
5 3
2 4 2 4 2
3 1
2 5
3 2```

### 输出

```
1
2
0```

# 题解

## 作者：Mars_Dingdang (赞：6)

打完 NOIP 然而分并不是很高，开一场 ABC 回复心情。

## 题目大意
初始有 $n$ 个箱子，每个箱子装有一个颜色为 $C_i$ 的小球。

有 $q$ 次操作，每次将 $a$ 号箱子里的所有球放入 $b$ 号箱子，问此时 $b$ 箱子中球的颜色种类数。

$1\le n,q\le 2\cdot 10^5 $，$1\le C_i\le n$。保证每次 $a\neq b$，但 $a,b$ 可能为空箱子。

## 大体思路
有三种思路。

#### 第一种：bitset。

使用 bitset 记录每个箱子 $i$ 有哪些球 $f_i$，然后 $a\to b$ 等价于 $f_b\leftarrow f_b\ \text{or}\ f_a$ 并清空 $f_a$。

这样做的时间复杂度是 $O(\dfrac {nq}{\omega})$，空间复杂度是 $O(\dfrac{n^2}{\omega})$，如果是 $10^5$ 估计能过（原题 4s, 1024MB），但 $2\cdot 10^5$ 刚好被卡（悲）。

```cpp
bitset <maxn> f[maxn];
int main () {
	read(n); read(q);
	rep(i, 1, n) {
		int x; read(x);
		f[i][x] = 1;
	}
	rep(i, 1, q) {
		int a, b;
		read(a); read(b);
		f[b] |= f[a];
		f[a].reset();
		writeln(f[b].count());
	}
	
	return 0;
}
```
被卡记录：

https://atcoder.jp/contests/abc329/submissions/47700854 开 $10^5$ RE 了。

https://atcoder.jp/contests/abc329/submissions/47700152 开 $2\cdot 10^5 $ CE 了。

#### 第二种：采用启发式合并。

我们发现，如果每次将小的合并到大的箱子，那么总的移动球的次数就是 $O(n\log n)$。这是因为你可以考虑所有箱子从 $1$ 个球变成 $2$ 个球，$2$ 个球变成 $4$ 个球，以此类推，总共有 $\log n$ 层，每层中移动全部的 $\dfrac n 2$ 个，故上界为 $O(n\log n)$。

用 set 维护每个箱子里面的球，单次插入操作是 $O(\log n)$，总复杂度为 $O(n\log ^2 n)$。

然而不一定每次都有 $size_a<size_b$。对于前者大于后者的情况，我们可以给每个 $i$ 记录一个编号 $id_i$ 表示编号为 $id_i$ 的 set 存放 $i$ 箱子的情况，然后交换一下 $id_a,id_b$ 即可。

#### 第三种：采用线段树合并。
不会有人 ABC 要使用线段树合并吧？

但是这样也能做。给每个箱子建立一个动态开点的权值线段树，$a\to b$ 相当于合并 $a,b$ 的权值线段树。

时间复杂度为 $O(n\log n)$，但空间复杂度多一个 $\log $。

## 代码
代码采用的是第二种方法。没有人 ABC 会去写线段树合并的，特别是刚考完 NOIP 然后炸了的那个晚上。进不了省队就寄了。呜呜呜。

```cpp
int n, q, id[maxn];
set<int> st[maxn];
int main () {
	read(n); read(q);
	rep(i, 1, n) {
		id[i] = i;
		int x; read(x);
		st[i].insert(x);
	}
	rep(i, 1, q) {
		int a, b;
		read(a); read(b);	
		if(st[id[a]].size() > st[id[b]].size()) swap(id[a], id[b]);
		a = id[a], b = id[b];
		for(auto it = st[a].begin(); it != st[a].end(); ++ it) st[b].insert(*it);
		st[a].clear();
		writeln(st[b].size());		
	}
	
	return 0;
}
```

---

## 作者：xz001 (赞：5)

- 启发式合并，我们可以用 ```set``` 维护有多少种不同的球，每次我们先看看 ```a``` 框和 ```b``` 框哪个球更少，然后将其合并到球数较多的框上，再按照情况交换一下 ```set``` 即可，交换两个容器是 $O(1)$ 的，总复杂度为 $O(q\log_2^2 n)$。
- 代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, q;

set <int> c[200005];

signed main() {
    scanf("%lld%lld", &n, &q);
    for (int i = 1, a; i <= n; ++ i) {
    	scanf("%lld", &a);
    	c[i].insert(a);
	}
	while (q -- ) {
		int a, b;
		scanf("%lld%lld", &a, &b);
		if (c[a].size() < c[b].size()) {
			for (set <int> :: iterator it = c[a].begin(); it != c[a].end(); ++ it) c[b].insert(*it);
			c[a].clear();
			printf("%lld\n", (int)c[b].size());
		} else {
			for (set <int> :: iterator it = c[b].begin(); it != c[b].end(); ++ it) c[a].insert(*it);
			c[b].clear();
			swap(c[a], c[b]);
			printf("%lld\n", (int)c[b].size());
		}
	}
    return 0;
}
```

---

## 作者：2huk (赞：2)

# F - Colored Ball

## Description

有 $n$ 个集合 $S_1, S_2, \dots, S_n$，最开始第 $i$ 个集合内有且仅有一个元素 $c_i$。接下来需要进行 $q$ 次操作，第 $i$ 次操作如下：

- 将集合 $S_{a_i}$ 中的元素全部移动到集合 $S_{b_i}$ 中。

每次操作后，你需要求出集合 $S_{b_i}$ 中的元素种类数量。

$1 \le n, q \le 2 \times 10^5$。

## Solution

合并集合，自然的想到启发式合并。

但这并不是简单的合并集合，而是将某个集合中的所有元素全部搬到另一个集合中，再把这个集合清空。

可以这样实现这件事情：仍然按照启发式合并的思路，将总数较少的集合搬到总数较多的集合中（注意这里没有区分 $a_i, b_i$），再把另一个集合清空。然后看一下，如果刚才是把集合 $b_i$ 中的元素搬到了集合 $a_i$ 里，那么就代表我们移错了。解决措施直接又快捷：将两个集合交换即可。因为交换 STL 容器是 $\Theta (1)$ 的。

总时间复杂度 $\Theta (n \log n)$，这也是启发式合并的复杂度。

## Code

<https://atcoder.jp/contests/abc329/submissions/47731747>

at_abc329_f

---

## 作者：沉石鱼惊旋 (赞：2)

# 闲话

来点不同的大炮打蚊子的非 STL 的做法。

# 题目翻译

你有 $n$ 个盒子，每个盒子一开始装了一个颜色为 $c_i$ 的球。

有 $q$ 次询问（操作），每次询问给出一对 $(a,b)$，要把盒子 $a$ 的**所有球**转到盒子 $b$ 里，问此时 $b$ 里有多少**颜色不同**的球。

$1\leq n,q\leq 2\times 10^5,1\leq a,b,c_i\leq n$。

# 题目思路

考虑使用根号分治。

显然的阈值为 $B=\sqrt n\approx 450$。

对于目前球个数 $\geq B$ 的盒子，我们记录一个桶 $bkt_{i,j}$ 表示**序号（不是编号）为 $i$** 的盒子是否装了 $j$。

因为这样的盒子数只有 $\leq B$ 个，所以我们需要记录一个序号，设编号为 $i$ 的盒子的序号为 $id_i$。

然后对于装球个数 $\lt B$ 的盒子，我们记录 $arr_{i,j}$ 表示**编号为 $i$** 的盒子的第 $j$ 个装的是什么。

大和大在一起，我们可以直接 $O(n)$ 转移。可以证明这样子转移的次数不会超过 $B$ 次。

小并到大的，直接扫一遍小的往大的里塞。

大并到小的，和上面同理。但我们无需新开一个 $id$，直接 $id_b\gets id_a$ 继承一下就可以。

小的和小的在一起，我们需要讨论一下。如果新出来的集合大小是 $\geq B$ 的，我们需要新开一个 $id$。否则直接合并。

代码和上面一样的。

# 完整代码

[AT submission 47747560](https://atcoder.jp/contests/abc329/submissions/47747560)

代码里前半段注释是本题正常的 STL 做法，感兴趣的也可以学习一下。

---

## 作者：haokee (赞：0)

[博客园](https://www.cnblogs.com/haokee/articles/ABC329F.html)

## 暴力算法

首先一看题目，相信大家一眼就看出了并查集。但是做着做着，你就会发现，这根本就不是一个并查集啊！原因如下：

1. 这里的合并是单向的，即 $a$ 合并到 $b$ 不等于 $b$ 合并到 $a$；
2. 输出的是不同颜色的球的数量，但是使用并查集实现非常麻烦。

所以我们可以想出一种十分暴力的解法：开上 $n$ 个 set，然后使用 `merge()` 合并函数进行模拟。但是有一种特殊情况，就是将 $N-1$ 个球的盒子合并到只有 $1$ 个球的盒子里面，那么就需要 $N-1$ 次遍历。这种算法的最高时间复杂度是 $\mathcal O(NQ)$ 的，而 $N,Q\le 2\times 10^5$，因此会超时。有没有一种方法，可以减低合并的时间呢？

## 启发式合并

什么是启发式合并？就是将小的盒子合并到大的盒子里面，这样子每次合并时间复杂度就取决于小的盒子的大小。这种合并方式的平均时间复杂度是 $\mathcal O(\log_2 N)$ 的，非常稳定。

但是我们发现，如果把 $a$ 移动到 $b$ 改为了 $b$ 移动到 $a$，那么最后两个 set 还需要交换，因为方向改变了。而 set 的赋值速度非常慢，最坏一次交换还是会卡到 $\mathcal O(N)$。所以，我们不能直接移动 set，而是交换指向 set 的指针。

所以我们就可以使用 $N$ 个指向 set 的指针，按照题意模拟，但是交换的时候要交换两个指针本身，而不是指针指向的 set。于是，本题就可以使用指针巧妙地解决了！

**注：**`->` 运算符表示访问指针所指对象的成员。

## 代码

```cpp
#include <iostream>
#include <unordered_set>  // 使用无序集合

using namespace std;

const int kMaxN = 2e5 + 5;

int n, q;
unordered_set<int> *s[kMaxN];  // 指向 set 的指针，注意指针的操作

int main() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    s[i] = new unordered_set<int>;  // 为每一个 set 申请空间
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x;  // 输入每个球
    s[i]->insert(x);  // 塞入初始的一个球
  }
  for (int i = 1, a, b; i <= q; i++) {
    cin >> a >> b;
    if (s[a]->size() > s[b]->size()) {  // 如果 A 的大小大于 B
      swap(s[a], s[b]);  // 交换所指的位置，不是交换 set！
    }
    s[b]->merge(*s[a]), s[a]->clear();  // 将 A 移动到 B，并把 A 给清空
    cout << s[b]->size() << '\n';  // set 自动去重，size 就是不同的球的数量
  }
  return 0;
}
```

由于使用了 `unordered_set`，因此时间复杂度为 $\mathcal O(Q\log_2 N)$，实测 $819$ 毫秒。

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc329_f)
### 题解
考虑用 set 维护每一个盒子包含的颜色。

由于按照题目的顺序合并铁定超时，故运用学过的**按秩合并**来解决这题。

你可能会说，反过来合并，不也要交换回来吗？是的。但是我们要先了解一点，那就是大部分 STL（不包括 array）交换都是 $O(1)$ 的，于是乎，这题就解决了。

考试的时候忘了 STL 交换是 $O(1)$，然后爆炸。
### 代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#define x first
#define y second
#define pb push_back
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 200010;
int n,q;
set <int> s[N];
int main () {
	cin >> n >> q;
	for (int i = 1;i <= n;i++) {
		int x;
		cin >> x;
		s[i].insert (x);
	}
	while (q--) {
		int a,b;
		cin >> a >> b;
		if (s[a].size () > s[b].size ()) swap (s[a],s[b]);
		for (int x : s[a]) s[b].insert (x);
		s[a].clear ();
		cout << s[b].size () << endl;
	}
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

## 题意

给定 $n$ 个格子，每个格子里一开始有一个颜色为 $c_i$ 的球。还有 $q$ 次操作，每次操作会把格子 $x$ 里的球都放到格子 $y$ 里去。操作后要输出格子 $y$ 里有多少种颜色的球。

## 题解

### 思路

这里提供一个启发式合并的做法。本题可以作为模板题。

我们考虑对每个盒子都开一个 set。初始时对每一个依次插入 $c_i$。

合并的时候只需要把 $x$ 的 set 暴力合并到 $y$ 里面就行了，之后清空 $x$ 的 set。

答案就是 $y$ 的 set 的大小。

但是这样会被卡成 $n^2$ 的。只要每一次都把大小最大的 set 合并到另一个很小的 set 里就会爆掉。

所以我们考虑合并的时候把大小较小的 set 合并到大小较大的 set 里面。这种合并方式称为启发式合并。

还有一点：由于合并是有方向的，所以需要额外记录点 $i$ 现在对应的 set 是第几个 set 以及第 $i$ 个 set 对应哪个点。

### 复杂度证明

我们考虑从每个元素出发。

设元素 $x$ 所在的集合为 $a$，将要合并到 $b$ 里面去，合并后的集合为 $c$。显然有 $\text{size(c)}\ge 2\times \text{size(a)}$。那么 $x$ 所在的集合最多合并 $\log n$ 次就达到了最大大小，即最多合并 $\log n$ 次。那么总复杂度就是 $O(n\log n)$。在本题中，set 带个 $\log$ 所以复杂度 $O(n\log^2 n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> st[200005];
int idx[200005],pos[200005];
//idx是点i所对应的set，pos是st[i]对应的点
signed main(){
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		st[i].insert(x);
		idx[i]=pos[i]=i;
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		x=pos[x],y=pos[y];
		if(st[x].size()<st[y].size()){
			for(auto nx:st[x]) st[y].insert(nx);
			st[x].clear();
			cout<<st[y].size()<<'\n';
		}
		else{
			swap(x,y);
			for(auto nx:st[x]) st[y].insert(nx);
			st[x].clear();
			cout<<st[y].size()<<'\n';
			swap(idx[x],idx[y]);
			pos[idx[x]]=x,pos[idx[y]]=y;
		}
	}
}
```

---

## 作者：BugGod (赞：0)

首先因为颜色种类与数量没有关系，我们可以直接用 `set` 维护。

然后我们有了暴力做法：每次直接复制，清除。但是这样会炸，考虑启发式合并，即每一次将元素少的复制到元素多的当中，复杂度为 $O(n\log n)$。

证明：考虑每个元素的贡献，由于合并复杂度只与较小者有关，极限情况下，合并的集合元素数量应该一样，也就是每次元素数量最多乘 $2$，那么这个元素最多参与 $\log n$ 次的合并就结束了，得证。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,c,a,b;
set<int>s[200010];
int main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>c;
        s[i].insert(c);
    }
    while(q--)
    {
        cin>>a>>b;
        if(s[b].size()<s[a].size())swap(s[b],s[a]);
        s[b].insert(s[a].begin(),s[a].end());
        cout<<s[b].size()<<'\n';
        s[a].clear();
    }
    return 0;
}
```

---

