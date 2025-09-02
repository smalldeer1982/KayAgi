# [PA 2020] Mieszanie kolorów

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 1 [Mieszanie kolorów](https://sio2.mimuw.edu.pl/c/pa-2020-1/p/kol/)**

Byteasar 正准备给栅栏涂漆。他已经准备了 $n$ 罐白色油漆，他把这些油漆排列成一排，从 $1$ 到 $n$ 编号。他想用这些油漆，但他不想把栅栏涂成白色。他委托了调色专家，调色专家有三种颜料：黄色、蓝色和红色。专家进行了 $m$ 次操作，其中第 $i$ 次操作是向编号在 $l_i$ 到 $r_i$ 之间（包括两端）的所有罐子中加入某种颜料。

油漆的最终颜色取决于被添加到其中的颜料。添加的颜料按照下表和图示进行混合。

|        颜料        | 颜色 |
| :----------------: | :--: |
|         无         | 白色 |
|        黄色        | 黄色 |
|        蓝色        | 蓝色 |
|        红色        | 红色 |
|    黄色 + 蓝色     | 绿色 |
|    黄色 + 红色     | 橙色 |
|    蓝色 + 红色     | 紫色 |
| 黄色 + 蓝色 + 红色 | 棕色 |

![](https://cdn.luogu.com.cn/upload/image_hosting/zow92g6w.png)

Byteasar 想要给栅栏涂成一种颜色。思来想去，他选择了绿色，因为绿色代表了你常会在算法竞赛中看到的 Accepted。他想知道现在有多少罐油漆是绿色的，请帮他数数。

## 说明/提示

#### 样例 1 解释

操作结束后，这些油漆分别是蓝色、绿色、黄色、绿色、绿色、棕色、橙色、黄色和白色的。因此，只有三罐油漆是绿色。

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1\le n,m\le 10^6$，$1\le l_i\le r_i\le n$，$1\le k_i\le 3$。

## 样例 #1

### 输入

```
9 5
2 8 1
4 5 2
6 7 3
5 6 2
1 2 2```

### 输出

```
3```

# 题解

## 作者：WaterSky (赞：30)

[题目传送门](https://www.luogu.com.cn/problem/P9094)。

# 开始讲解：
## 思路：
看见这一道题的第一眼，就觉得是一道差分题。因为它求得是一个数列经过某一些操作后，求出某个区间的数量，而差分这一个算法，就是为了解决这一个类型的题目，故而用差分。

既然知道了用差分，那么就需要深入的研究怎么使用这一个算法。首先，题目中说：有三种颜色：红、黄、蓝。在 $M$ 个 操作中，让从 $x$ 到 $y$ 的这一个区间加上这三种颜色的一种。所以，可以开三个数组，分别储存这三种颜色的添加情况，最后再判断处理。
## 我的代码（码丑勿喷）：
```
#include<bits/stdc++.h>
using namespace std;
long long n,m,A[1000005],B[1000005],C[1000005],x,y,z,ans;//定义
int main()
{
	cin>>n>>m;//输入
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>z;//输入
		if(z==1) A[x]++,A[y+1]--;//黄色颜料处理
		if(z==2) B[x]++,B[y+1]--;//蓝色颜料处理
		if(z==3) C[x]++,C[y+1]--;//红色颜料处理
	}
	for(int i=1;i<=n;i++) A[i]+=A[i-1],B[i]+=B[i-1],C[i]+=C[i-1];//前缀差分
	for(int i=1;i<=n;i++) 
	if( A[i] && B[i] && !C[i]) ans++; //判断是否为绿色
	cout<<ans;//输出答案
    return 0;//最好return 0;
} 
```

---

## 作者：lbdontknow (赞：7)

## 算法分析
### 题目解读
由于绿色是由黄色与蓝色组成的，所以如果一个栅栏染上了蓝色与黄色并且没有染上红色，那么它就是一块绿色的栅栏。
### 暴力做法
我们可以用三个一维数组来记录是否被上了对应的颜色，然后从 $1$ 到 $n$ 模拟一遍，对于每一块染上了蓝色与黄色并且没有染上红色的栅栏，将 $ans+1$。


但是这样做的复杂度为 $O(nm)$，对于本题 $n,m \leq 10^6$ 的数据范围无法通过。
### 正解
仔细想想，我们超时的原因是什么?是因为每一次将 $l$ 到 $r$ 这个区间染色的时间复杂度**太高了**。有没有什么可以用较低时间复杂度修改区间的算法呢？对了，是**差分**。
#### 差分介绍
用 $d_i$ 维护 $a_i-a_{i-1}$。


这样，当我们想把 $a_l$ 到 $a_r$ 这个区间所有的数 $+1$ 的时候，我们可以通过更改差分数组来实现 $O(1)$ 修改。


我们可以将 $d_i$ 加上 $1$。


这样， $a_l$ 和 $a_l$ 以后的数都会 $+1$。但是，这样之后，$a_{r+1}$ 和以后的数字也被加上了 $1$，所以我们应该在 $d_{r+1}$ 减去 $1$，这样就不会影响到 $a_{r+1}$ 和以后的数的值。


至于通过 $d$ 数组还原 $a$ 数组的方法，可以通过记录一个 $sum$ 维护当前的值， $sum$ 初始化为 $0$，每一次 $sum+d_i$ 之后，再将 $a_i+sum$，这样就可以通过 $d$ 数组还原回 $a$ 数组。 
#### 回归题目
了解了差分数组之后，我们可以维护三个差分数组 $yellow$，$blue$ 和 $red$。 


每一次修改时，就修改对应差分数组。


然后从 $1$ 枚举到 $n$ ，记录 $sumyellow$，$sumblue$，$sumred$。当 $sumyellow$ 与 $sumblue$ 不为 $0$ 且 $sumred$ 为 $0$ 时，将 $ans+1$。


最后输出 $ans$，就大功告成啦！
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int yellow[1919810],red[1919810],blue[1919810];//差分数组 
int main(){
	ios::sync_with_stdio(false);//读入优化，加快cin的速度 
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int color,l,r;
		cin>>l>>r>>color;
		if(color==1){
			yellow[l]++; 
			yellow[r+1]--;
		}
		else if(color==2){
			blue[l]++;
			blue[r+1]--;
		}
		else{
			red[l]++;
			red[r+1]--;
		}
	}
	int redsum=0,yellowsum=0,bluesum=0;//当前栅栏的涂色情况 
	for(int i=1;i<=n;i++){
		redsum+=red[i];//sum统计 
		yellowsum+=yellow[i];//sum统计 
		bluesum+=blue[i];//sum统计 
		if(redsum==0&&min(bluesum,yellowsum)>0){//min(bluesum,yellowsum)>0等价于bluesum>0&&yellowsum>0 
			ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：happybob (赞：5)

显然可以直接差分。

但是我看题的时候看成了多次查询。

所以我就写了个线段树。

注意到一个油漆桶被多次覆盖一个颜色是没有贡献的，所以考虑线段树的每个节点维护 `c[0/1][0/1][0/1]` 分别表示 $3$ 种原色是否出现的方案数。

接着维护一个 `tag`，可以使用 `unordered_set` 等结构，顺序存储每一个操作。

`pushdown` 的时候维护 `c` 即可。

但是这样是过不去的，会 MLE。考虑如果一个数被涂了第 $3$ 种原色，那么之后不可能变成绿色，因此可以压缩最后 $1$ 维，然后神奇卡常即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>
#include <vector>
#include <unordered_set>
using namespace std;

const int N = 8e5 + 5;

class SegmentTree
{
public:
	struct Node
	{
		int c[2][2][1];
		unordered_set<int> tag;
		//set<int> used;
		friend Node operator+(const Node& a, const Node& b)
		{
			if (a.c[0][0][0] == -1) return b;
			if (b.c[0][0][0] == -1) return a;
			Node c;
			c.tag.clear();
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					for (int k = 0; k < 1; k++) c.c[i][j][k] = b.c[i][j][k] + a.c[i][j][k];
				}
			}
			return c;
		}
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u] = tr[u << 1] + tr[u << 1 | 1];
	}
	void pushdown(int u)
	{
		auto& rt = tr[u], & l = tr[u << 1], & r = tr[u << 1 | 1];
		for (int i : rt.tag)
		{
			if (i == 0)
			{
				if (l.tag.count(i) == 0)
				{
					l.tag.insert(i);
					l.c[1][0][0] += l.c[0][0][0];
					//l.c[1][0][1] += l.c[0][0][1];
					l.c[1][1][0] += l.c[0][1][0];
					//l.c[1][1][1] += l.c[0][1][1];
					for (int j = 0; j < 2; j++)
					{
						for (int k = 0; k < 1; k++) l.c[0][j][k] = 0;
					}
				}
				if (r.tag.count(i) == 0)
				{
					r.tag.insert(i);
					r.c[1][0][0] += r.c[0][0][0];
					//r.c[1][0][1] += r.c[0][0][1];
					r.c[1][1][0] += r.c[0][1][0];
					//r.c[1][1][1] += r.c[0][1][1];
					for (int j = 0; j < 2; j++)
					{
						for (int k = 0; k < 1; k++) r.c[0][j][k] = 0;
					}
				}
			}
			else if (i == 1)
			{
				if (l.tag.count(i) == 0)
				{
					l.tag.insert(i);
					l.c[0][1][0] += l.c[0][0][0];
					//l.c[0][1][1] += l.c[0][0][1];
					l.c[1][1][0] += l.c[1][0][0];
					//l.c[1][1][1] += l.c[1][0][1];
					for (int j = 0; j < 2; j++)
					{
						for (int k = 0; k < 1; k++) l.c[j][0][k] = 0;
					}
				}
				if (r.tag.count(i) == 0)
				{
					r.tag.insert(i);
					r.c[0][1][0] += r.c[0][0][0];
					//r.c[0][1][1] += r.c[0][0][1];
					r.c[1][1][0] += r.c[1][0][0];
					//r.c[1][1][1] += r.c[1][0][1];
					for (int j = 0; j < 2; j++)
					{
						for (int k = 0; k < 1; k++) r.c[j][0][k] = 0;
					}
				}
			}
			else if (i == 2)
			{
				l.tag.insert(2);
				r.tag.insert(2);
				//printf("!\n");
				for (int j = 0; j < 2; j++)
				{
					for (int k = 0; k < 2; k++) l.c[j][k][0] = 0;
				}
				for (int j = 0; j < 2; j++)
				{
					for (int k = 0; k < 2; k++) r.c[j][k][0] = 0;
				}
			}
		}
		rt.tag.clear();
	}
	void build(int u, int l, int r)
	{
		tr[u].tag.clear();
		tr[u].c[0][0][0] = 1;
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void update(int u, int lx, int rx, int x, int l, int r)
	{
		if (tr[u].tag.count(x)) return;
		if (l >= lx and r <= rx)
		{
			tr[u].tag.insert(x);
			auto& l = tr[u];
			if (x == 0)
			{
				l.c[1][0][0] += l.c[0][0][0];
				//l.c[1][0][1] += l.c[0][0][1];
				l.c[1][1][0] += l.c[0][1][0];
				//l.c[1][1][1] += l.c[0][1][1];
				for (int j = 0; j < 2; j++)
				{
					for (int k = 0; k < 1; k++) l.c[0][j][k] = 0;
				}
			}
			else if (x == 1)
			{
				l.c[0][1][0] += l.c[0][0][0];
				//l.c[0][1][1] += l.c[0][0][1];
				l.c[1][1][0] += l.c[1][0][0];
				//l.c[1][1][1] += l.c[1][0][1];
				for (int j = 0; j < 2; j++)
				{
					for (int k = 0; k < 1; k++) l.c[j][0][k] = 0;
				}
			}
			else
			{
				l.tag.insert(2);
				//printf("!\n");
				for (int j = 0; j < 2; j++)
				{
					for (int k = 0; k < 2; k++) l.c[j][k][0] = 0;
				}
			}
			return;
		}
		pushdown(u);
		int mid = l + r >> 1;
		if (lx <= mid) update(u << 1, lx, rx, x, l, mid);
		if (rx > mid) update(u << 1 | 1, lx, rx, x, mid + 1, r);
		pushup(u);
	}
	Node query(int u, int l, int r, int nl, int nr)
	{
		if (nl >= l and nr <= r) return tr[u];
		pushdown(u);
		int mid = nl + nr >> 1;
		Node res;
		res.c[0][0][0] = -1;
		if (l <= mid) res = query(u << 1, l, r, nl, mid);
		if (r > mid) res = res + query(u << 1 | 1, l, r, mid + 1, nr);
		return res;
	}
}tr;

int n, m;

int main()
{
	scanf("%d%d", &n, &m);
	tr.build(1, 1, n);
	while (m--)
	{
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		x--;
		tr.update(1, l, r, x, 1, n);
	}
	printf("%d\n", tr.query(1, 1, n, 1, n).c[1][1][0]);
	//tr.print(1, 1, n);
	return 0;
}
```


---

## 作者：Ginger_he (赞：5)

我们开 $3$ 棵线段树，分别表示每桶油漆是否加入了黄色、蓝色、红色颜料，最后遍历一下整棵树，统计只加入了黄色和蓝色的油漆即可，时间复杂度 $\Theta(n\log n+m)$。

---

## 作者：shaozhehan (赞：3)

[原题链接](https://www.luogu.com.cn/problem/P9094)

题目大意：

给你 $n$ 罐颜料，你执行 $m$ 次操作。每次操作指将编号为 $l\sim r$ 的油漆混合第 $k$ 中颜色，其中 $k=1$ 表示黄色，$k=2$ 表示蓝色，$k=3$ 表示红色。具体颜色混合之后的结果参见原题目。

思路：

这一个题我们可以用[差分](https://oiwiki.org/basic/prefix-sum/#%E5%B7%AE%E5%88%86)，首先开三个差分数组 $d\_red$、$d\_yellow$、$d\_blue$。我们可以边输入边维护三个数组。
```cpp
for (int i = 1; i <= m; i++){
    int l, r, k;
    cin >> l >> r >> k;
    if (k == 1){// 黄色
        d_yellow[l]++;
        d_yellow[r + 1]--;
    } else if (k == 2){// 蓝色
        d_blue[l]++;
        d_blue[r + 1]--;
    } else {// 红色
        d_red[l]++;
        d_red[r + 1]--;
    }
}
```
最后，我们可以把这三个数组前缀和了。题目要求了绿色只能用黄色和蓝色合成，所以最后我们可以判断：没有红色且有黄色和蓝色的可以。
```cpp
int cnt = 0;
for (int i = 1; i <= n; i++){
    // 前缀和
    d_red[i] += d_red[i - 1];
    d_yellow[i] += d_yellow[i - 1];
    d_blue[i] += d_blue[i - 1];
    if (d_red[i] == 0 && d_yellow[i] > 0 && d_blue[i] > 0){// 如果是绿色
        cnt++;
    }
}
```
完整代码贴在[这里](https://www.luogu.com.cn/paste/gb7yofbe)。

---

## 作者：skyskyCCC (赞：2)

## 前言。
差分基础题。
## 分析。
我们将每个地方先涂上色，然后查询颜色就行了。

我们设 $3$ 个数组，分布代表红，蓝和黄三种颜色，然后差分取出每个栏杆涂不同的颜色的次数。

因为只有黄色和蓝色混合才能出绿色，而红色无论如何也合成不了绿色。所以我们只要找到第 $i$ 个栏杆的红色涂的次数为 $0$ 而黄色和蓝色涂的次数不为 $0$ 即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,m,l,r,k,ans,red[1000005],ye[1000005],bule[1000005]; 
int main(){
    cin>>n>>m;
    while(m--){
        cin>>l>>r>>k;
        if(k==1){
            ye[l]++;
            ye[r+1]--;
        }
        else if(k==2){
            bule[l]++;
            bule[r+1]--;
        }
        else{
            red[l]++;
            red[r+1]--;
        }
    }
    for(int i=1;i<=n;i++){
        red[i]+=red[i-1];
        ye[i]+=ye[i-1];
        bule[i]+=bule[i-1];
        if(!red[i]&&ye[i]&&bule[i]){
            ans++;
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：guozhetao (赞：2)

## 思路
很显然这题并不需要用到线段树。我们只需要运用**差分**就行了（显而易见先涂色后查询）。[前缀和的逆](https://www.luogu.com.cn/problem/U69096)。

我们设置 $r,b,y$ 三个数组代表红色，蓝色和黄色，并用差分修改求出每一个栅栏刷三种油漆的次数，最后求出满足 $r_i = 0$ 且 $b_i \not = 0$ 且 $g_i \not = 0$ 的个数即可。
## 代码
```cpp
//定义数组
int n,m,r[1000005],y[1000005],b[1000005],ans = 0; 
int main() {
	n = read(),m = read();
	while(m--) {
		int l = read(),rr = read(),k = read();
        //差分
		if(k == 1) y[l]++,y[rr + 1]--;
		else if(k == 2) b[l]++,b[rr + 1]--;
		else r[l]++,r[rr + 1]--;
	}
	for(int i = 1;i <= n;i++) {
		r[i] += r[i - 1],y[i] += y[i - 1],b[i] += b[i - 1];//还原数组
		if(!r[i] and y[i] and b[i]) ans++;//判断条件
	}
	write(ans);
    return 0;
}
```


---

