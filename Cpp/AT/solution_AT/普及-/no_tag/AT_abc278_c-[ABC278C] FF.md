# [ABC278C] FF

## 题目描述

【题目翻译】

洛谷是一个大平台，从前，这里有 $n$ 个用户。刚开始，他们没有任何关系。

有 $q$ 次操作，每组操作包含 $op_i$，$a_i$，$b_i$：

+ $op_i = 1$，表示 $a_i$ 关注了 $b_i$。
+ $op_i = 2$，表示 $a_i$ 取关了 $b_i$。
+ $op_i = 3$，表示查询 $a_i$ 与 $b_i$ 是否互关。

对于每个 $op_i = 3$，输出结果。

translated by @[liangbowen](https://www.luogu.com.cn/user/367488).

## 说明/提示

$1 \le n \le 10^9$

$1 \le q \le 2 \times 10^5$

保证 $1 \le a_i, b_i \le n$，且 $a_i \ne b_i$。

保证 $op_i \in \{1, 2, 3\}$。

## 样例 #1

### 输入

```
3 9
1 1 2
3 1 2
1 2 1
3 1 2
1 2 3
1 3 2
3 1 3
2 1 2
3 1 2```

### 输出

```
No
Yes
No
No```

## 样例 #2

### 输入

```
2 8
1 1 2
1 2 1
3 1 2
1 1 2
1 1 2
1 1 2
2 1 2
3 1 2```

### 输出

```
Yes
No```

## 样例 #3

### 输入

```
10 30
3 1 6
3 5 4
1 6 1
3 1 7
3 8 4
1 1 6
2 4 3
1 6 5
1 5 6
1 1 8
1 8 1
2 3 10
1 7 6
3 5 6
1 6 7
3 6 7
1 9 5
3 8 6
3 3 8
2 6 9
1 7 1
3 10 8
2 9 2
1 10 9
2 6 10
2 6 8
3 1 6
3 1 8
2 8 5
1 9 10```

### 输出

```
No
No
No
No
Yes
Yes
No
No
No
Yes
Yes```

# 题解

## 作者：youyew2007 (赞：3)

# [ABC278C] FF

题目链接:[AT](https://atcoder.jp/contests/abc278/tasks/abc278_c)；[Luogu](https://www.luogu.com.cn/problem/AT_abc278_c)

## Translation

有 $n$ 个人，他们从 $1$ 到 $n$ 编号，你需要进行 $Q$ 次操作，对于每次操作，给定 $T_i,a_i,b_i$ 三个数，对于它们有如下定义：
- 若 $T_i = 1$，表示 $a_i$ 关注了 $b_i$，若 $a_i$ 在此之前已经关注了 $b_i$，则无事发生；
- 若 $T_i = 2$，表示 $a_i$ 取消关注了 $b_i$，若 $a_i$ 在此之前没有关注 $b_i$，则无事发生；
- 若 $T_i = 3$，你需要输出 $a_i$ 和 $b_i$ 是否互关，对于互关的定义是： $a_i$ 关注了 $b_i$ 且 $b_i$ 关注了 $a_i$。若他们互关，输出 ```Yes```，否则输出 ```No```。

## Solution
~~这道题其实还是挺水的~~ 首先读题，$2 \leq n \leq 10^9$，那么如果直接开数组存是否互关绝对炸空间，那我们怎么办呢？

STL 大法好，我们可以用 map 来存，具体地，关注可以看成 $a$ 和 $b$ 之间建立了一条从 $a$ 通向 $b$ 的单向边，从 $a$ 出发的有可能有多条边，所以普通的 ```map<int,int>``` 肯定无法满足我们的要求，所以，我们可以再借助一个好东西：```pair<int,int>```，我们可以用 pair 来储存边的起点和终点，所以我们的 map 可以开成这样：```map< pair<int,int> ,int>``` ，这样我们就可以解决存图的问题了。

直接上代码
## Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<map>
#include<vector>
#include<stack>

using namespace std;
typedef long long ll;

namespace io{
	char buf[1 << 22],*p1 = buf,*p2 = buf;
	#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1++)
	inline int read() 
	{
		register int s = 0;
		char ch = getchar(),last = ' ';
		while(ch < '0' || ch > '9')
			last = ch,ch = getchar();
		while(ch >= '0' && ch <= '9')
			s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
		return last == '-' ? -s : s;
	}
	int num[100];
	inline void write(int x)
	{
		if(x < 0) putchar('-'),x = -x;
		register int len = 0;
		do num[len++] = x % 10;while(x /= 10);
		while(len--) putchar(num[len] + '0');
		putchar('\n');
	}
}

#define read io::read
#define write io::write

//快读快写模板

#define pii pair<int,int>
#define mpp make_pair

int n,q;
map<pii,int> mp;

int main()
{
	// ios::sync_with_stdio(false);
	// cin.tie(0);
	// cout.tie(0);
	n = read(),q = read();
	while(q--)
	{
		int t = read(),a = read(),b = read();
		if(t == 1)//a 关注 b设1
			mp[mpp(a,b)] = 1;
		if(t == 2)//a 取关 b直接设0
			mp[mpp(a,b)] = 0;
		if(t == 3)
			if(mp[mpp(a,b)] == 1 && mp[mpp(b,a)] == 1)
				printf("Yes\n");
			else
				printf("No\n");
	}
	return 0;
}

```


---

## 作者：RainSpark (赞：2)

# 题意

在某个社交平台有 $N$ 个用户和 $Q$ 次操作，每次操作给出三个参数 $T_i,A_i,B_i$，定义如下：
- 当 $T_i=1$ 时，用户 $A_i$ 关注了用户 $B_i$
- 当 $T_i=2$ 时，用户 $A_i$ 取消关注了用户 $B_i$
- 当 $T_i=3$ 时，查询 $A_i$ 和 $B_i$ 是否互相关注了对方，如果是则输出 `Yes`，反之则输出 `No`。

初始时没有人被关注，对于每一次 $T_i=3$ 的操作输出其结果。

# 思路

由于 $N$ 比较大，但是 $Q$ 比较小，考虑直接映射一个 `pair` 类型的 `map` 表示邻接矩阵，查询时直接 `make_pair` 即可。

# 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<map>
#define PII pair<int,int>
using namespace std;
map<PII,bool> g;
int n,q;
int main(){
	scanf("%d %d",&n,&q);
	while(q--){
		int opt,x,y;
		scanf("%d %d %d",&opt,&x,&y);
		switch(opt){
			case 1:
				g[make_pair(x,y)]=1;
				break;
			case 2:
				g[make_pair(x,y)]=0;
				break;
			case 3:
				if(g[make_pair(x,y)] && g[make_pair(y,x)]) puts("Yes");
				else puts("No");
				break;
		}
	}
    return 0;
}
```

---

## 作者：Strelitzia_ (赞：2)

## 题目大意

有 $n$ 个人，$q$ 次询问。每一次询问：

+ $\texttt{1 a b}$ 表示 $a$ 这个人关注了 $b$；
+ $\texttt{2 a b}$ 表示 $a$ 这个人取消了对 $b$ 的关注；
+ $\texttt{3 a b}$ 询问 $a$ 与 $b$ 两人是否**互相**关注。

------------
## 思路

我们考虑用 `pair<int, int>` 记录第一个人是否关注了第二个人。由于每一个 `pair<>` 内部的两个元素是有序存储的，我们这样记录不会有问题。

我们考虑用 `map<pair<int, int>, bool>` 记录这样的关系是否存在。对于每一次修改我们用 `make_pair()` 来操作，查询同理。于是我们就做完了，复杂度 $O(Q\log Q)$（`map` 自带 $O(\log n)$），可以接受。

代码：

```cpp
map<pair<int, int>, bool> mp;
int n, q;
signed main() {
	n = read(), q = read();
	for (int i = 1; i <= q; i++) {
		int type = read();
		if (type == 1) {
			int a = read(), b = read();
			mp[make_pair(a, b)] = 1;
		} else if (type == 2) {
			int a = read(), b = read();
			mp[make_pair(a, b)] = 0;
		} else {
			int a = read(), b = read();
			puts(mp[make_pair(a, b)] && mp[make_pair(b, a)] ? "Yes" : "No");
		}
	}
	return Strelitzia_H;
}
```

---

## 作者：HuangBarry (赞：0)

思路：map 套 set（其实 stack 等 STL 容器都行），用 set 来记录哪些人关注了下标为 $i$ 的人。
* 关注：$a$ 关注 $b$，将 $b$ 放到 $a$ 的 set 里。
* 取关：$a$ 取关 $b$，将 $b$ 从 $a$ 的 set 里删除。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
unordered_map<int,unordered_set<int>>a; 
int main(){
	cin>>n>>q;
	while(q--){
		int op,x,y;
		cin>>op>>x>>y;
		switch(op){
			case 1://关注
				a[x].insert(y);
				break;
			case 2://取关
				a[x].erase(y);
				break;
			case 3:
				cout<<(a[x].count(y)&&a[y].count(x)?"Yes\n":"No\n");
		}
	}
	return 0;
}
```

---

