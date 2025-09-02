# 「DLESS-2」XOR and Tree Construction

## 题目背景

一道题目需要一个题目背景。

## 题目描述

Bob 有一棵 $n$ 个点的无根树 $T$，树上每个点都有权值，第 $i$ 个点的权值为 $a_i$。Alice 记录了一个 $n\times n$ 的矩阵 $b$，其中 $b_{i,j}$ 表示树上 $i\to j$ 最短路径上所有点的点权的异或和。

Alice 观察这个矩阵，惊奇地发现矩阵里所有数都是**正整数**。

不幸的是，某一天，Bob 把他的树搞丢了。于是你得到了 Alice 记录的矩阵，并需要还原出一种可能的树 $T$ 与序列 $a$。值得注意的是，Alice 非常靠谱，因此你总是可以还原出至少一种树。

## 说明/提示

对于所有数据，保证：
- $1\le T\le 10$
- $1\le n\le 500$
- $1\le b_{i,j}<2^{60}$

**本题采用捆绑测试**，各子任务描述如下：
- Subtask 1（5 pts）：$n=2$。
- Subtask 2（10 pts）：$n=3$。
- Subtask 3（10 pts）：$n=4$。
- Subtask 4（15 pts）：$n\le 8$。
- Subtask 5（25 pts）：$b_{i,i}$ 互不相同。
- Subtask 6（35 pts）：无特殊限制。

## 样例 #1

### 输入

```
2
3
1 3 7
3 2 6
7 6 4
5
8 9 10 15 1 
9 1 2 14 9 
10 2 3 13 10 
15 14 13 7 6 
1 9 10 6 8 
```

### 输出

```
1 2 4 
1 2
2 3
8 1 3 7 8 
1 2
1 4
2 3
2 5
```

## 样例 #2

### 输入

```
1
2
10000000000 29999508480
29999508480 20000000000```

### 输出

```
10000000000 20000000000
1 2```

# 题解

## 作者：喵仔牛奶 (赞：9)

## Solution

显然，$i$ 的点权 $a_i=b_{i,i}$。

考虑一对 $(i,j)$：
- 若 $a_i\oplus a_j\neq b_{i,j}$，则必然不存在 $(i,j)$ 这条边。
- 若 $a_i\oplus a_j=b_{i,j}$，则必然存在 $(i,j)$ 这条边。若不存在，$i\to j$ 路径长度 $\ge 3$，则路径去掉 $i,j$ 两个点至少有一个点，而路径上点权的异或和为 $b_{i,j}\oplus a_i\oplus a_j=0$，不符合题意。

由于保证有解，直接输出所有 $a_i\oplus a_j=b_{i,j}$ 的对即可。

复杂度 $\mathcal O(\sum n^2)$。

---

## 作者：tuntunQwQ (赞：4)

$a_i$ 很好求，因为 $b_{i,i}=a_i$。

对于 $b_{i,j}=a_i⊕a_j$ 的两个节点 $i,j$，我们需要用一条边直接连接这两个节点。

为什么 $b_{i,j}=a_i⊕a_j$ 的两个节点 $i,j$ 一定要有一条边连接这两个节点？假设这两个节点的最短路径上存在除了这两个节点以外的点，则该路径上的这些点的异或和为 $0$，而数据范围中说 $b_{i,j}\ge 1$，所以我们找到所有 $b_{i,j}=a_i⊕a_j$ 的两个节点直接连边就行了。

为了防止重复连边，我们只需要让 $i<j$ 就可以了。

代码如下，可供参考：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
int t,n,b[N][N],a[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>b[i][j];
				if(i==j)a[i]=b[i][j];
			}
		}
		for(int i=1;i<=n;i++)cout<<a[i]<<' ';
		cout<<'\n';
		for(int i=1;i<n;i++){
			for(int j=i+1;j<=n;j++){
				if((a[i]^a[j])==b[i][j]){
					cout<<i<<' '<<j<<'\n';
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：Charged_Charge (赞：1)

# 洛谷 P12826
## 前言：
~~第一眼发现是找规律，然后开始找，然后找出来了。~~
## 题意说明：
$t$ 组测试样例，每组一个 $n$ 作为矩阵的边长，然后是一个边长为 $n$ 的矩阵，第一行输出 $n$ 个数，第 $i$ 个数表示编号为 $i$ 的节点的值，往后 $n-1$ 行，每行两个数 $u$ 和 $v$，表示有一条连接 $u$ 和 $v$ 两个节点的边。
## 解题思路：
题目分为两个小问。定义原数组为 $b$ 数组。先说第一问，不难发现，输出的答案就是矩阵的右斜对角线的所有数，很简单。再说第二问，我们可以新建一个数组，记录上一问的答案，然后根据上一次的答案，遍历每一个不同的节点组合，因为 $n$ 很小，所以双重循环不会超时，然后，我们根据原矩阵的作用，也就是第 $i$ 个节点到第 $j$ 个节点的异或和判断，如果 $a_i \oplus a_j = b_{i,j}$ 那么 $i$ 与 $j$ 有直接相连的边（因为有边直接相连的节点就是两个相邻的节点，如果不相邻，则没有相连的边，异或和就为零，而注意到 $1 \le b_{i,j}$ 则说明如果两节点相邻，则 $a_i \oplus a_j = b_{i,j}$ ），输出 $i$ 与 $j$。
## AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 520;
int t;
int b[N][N];
signed main() {
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> b[i][j];
			}
		}

		int nn = n;
		int l = 1, r = 1;
		int a[N], idx = 0;

		while (nn--) {
			a[++idx] = b[l][r];
			cout << b[l][r] << " ";
			l++;
			r++;
		}

		cout << endl;

		for (int i = 1; i < idx; i++) {
			for (int j = i + 1; j <= idx; j++) {
				int num = a[i];
				num ^= a[j];
				if (num == b[i][j]) {
					cout << i << " " << j << endl;
				}
			}
		}
	}

	return 0;
}
```

---

## 作者：Chenxuhang_play (赞：1)

## 前言

为了防止管理员说我废话讲太多，我使用了云剪切版来存放[前言](https://www.luogu.com.cn/paste/kd34u4wk)。

## 题目传送门

<https://www.luogu.com.cn/problem/P12826>

题目有点长懒得写题目大意了。

## 5 pts 做法

拿到一道题，题目看不懂、没有学过异或，没关系，先想着骗分。

骗分的关键在于数据范围。注意到数据范围中有这么两句话。

>Subtask 1（5 pts）：$n=2$。
>
>Subtask 5（25 pts）：$b_{i,i}$ 互不相同。

当然这里给出第五个测试点不是让我们把第五个测试点过了，而是因为在这里强调了 $b_{i,i}$。这说明 $b_{i,i}$ 很可能是一个很重要的值。回归题目看下 $b_{i,j}$ 是什么意思。

> 其中 $b_{i,j}$ 表示树上 $i\to j$ 最短路径上所有点的点权的异或和。

至于异或和是什么在下面的满分做法中会说，但在这里我们并不需要知道。一个事实是，$b_{i,i}$ 一定是这个树的节点的点权。因为这个点到自己的最短路径上只会有这个点本身，那么异或和就是这个点的点权本身。

知道了这个，我们就可以直接输出所有的 $b_{i,i}$，就把第一个问题，输出点权给搞定了。

至于边这个事，显然两个点之间只有一个边，所以直接输出 $1$ 和 $2$ 即可。

按照惯例，不管范围，全开 `long long`。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long t,n;
    cin>>t;
    while(t--)
    {
    	cin>>n;
    	long long b[n][n],c[n];
    	for(long long i=0;i<n;i++)
    	{
    		for(long long j=0;j<n;j++)
    		{
    			cin>>b[i][j];
    			if(i==j) c[i]=b[i][j];
			}
		}
		for(long long i=0;i<n;i++) cout<<c[i]<<" ";
		cout<<endl<<"1 2"<<endl;
	}
    return 0;
}
```

## 100 pts 做法

这里需要首先搞懂异或和是什么意思。

<https://www.luogu.com.cn/discuss/1092782?page=10>

甚至我都是在赛时问了才知道的，上面是我赛时问的问题和回答。

> 定义 $\oplus$ 为异或运算。
>
> ……
>
> 本题中，设点权分别为 $a_{p_1},a_{p_2}\dots a_k$，“所有点的点权的异或和”即为 $a_{p_1}\oplus a_{p_2}\oplus \dots\oplus a_k$。

明确了这个其实就相当简单了。注意到一个特点，对于点 $i$ 和 $j$，如果 $a_i \oplus a_j =b_{i,j}$，则说明 $i$ 和 $j$ 中一定有边，因为除了对 $0$ 异或，异或的结果一定会改变，且题目中强调了一定是正整数，所以才有以上推论。

代码中注意一个细节，异或在代码中用 `^` 表示，异或的优先级很低，使用时一定要搭配括号一起用。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long t,n;
    cin>>t;
    while(t--)
    {
    	cin>>n;
    	long long b[n][n],c[n];
    	for(long long i=0;i<n;i++)
    	{
    		for(long long j=0;j<n;j++)
    		{
    			cin>>b[i][j];
    			if(i==j) c[i]=b[i][j];
			}
		}
		for(long long i=0;i<n;i++) cout<<c[i]<<" ";
		cout<<endl;
		for(int i=0;i<n;i++)
		{
			for(int j=i;j<n;j++)
			{
				if((c[i]^c[j])==b[i][j]) cout<<i+1<<" "<<j+1<<endl;
			}
		}
	}
    return 0;
}
```

---

## 作者：ZHR100102 (赞：1)

[Blog](https://www.cnblogs.com/zhr0102/p/18928977)

~~险些被诈骗了。~~

注意到题目给出了自己到自己的路径点权异或和，所以我们可以**直接得出每个节点的值**，即 $b_{i,i}$ 的值。

继续考虑如何构造出这棵树，因为我们只需要知道哪些节点之间是直接连边的就可以了，所以只需要得出**两个点相邻的条件**即可。又注意到有 $b>0$ 的性质，所以**没有任何一个路径异或和为 $0$**，两点间加了任何一段路径都会使路径异或和不等于两点异或和，因此如果 $b_{i,i}\oplus b_{j,j}=b_{i,j}$，那么两点就是相邻的。将这些相邻点输出即可。

时间复杂度 $O(tn^2)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=505;
int n;
ll b[N][N];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>b[i][j];
            if(i==j)cout<<b[i][j]<<" ";
        }
    }
    cout<<'\n';
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            if((b[i][i]^b[j][j])==b[i][j])
                cout<<i<<" "<<j<<'\n';
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

