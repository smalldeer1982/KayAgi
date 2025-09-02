# [GDCPC 2023] Path Planning

## 题目描述

有一个 $n$ 行 $m$ 列的网格。网格里的每个格子都写着一个整数，其中第 $i$ 行第 $j$ 列的格子里写着整数 $a_{i, j}$。从 $0$ 到 $(n \times m - 1)$ 的每个整数（含两端）在网格里都恰好出现一次。

令 $(i, j)$ 表示位于第 $i$ 行第 $j$ 列的格子。您现在需要从 $(1, 1)$ 出发并前往 $(n, m)$。当您位于格子 $(i, j)$ 时，您可以选择走到右方的格子 $(i, j + 1)$（若 $j < m$），也可以选择走到下方的格子 $(i + 1, j)$（若 $i < n$）。

令 $\mathbb{S}$ 表示路径上每个格子里的整数形成的集合，包括 $a_{1, 1}$ 和 $a_{n, m}$。令 $\text{mex}(\mathbb{S})$ 表示不属于 $\mathbb{S}$ 的最小非负整数。请找出一条路径以最大化 $\text{mex}(\mathbb{S})$，并求出这个最大的值。

## 样例 #1

### 输入

```
2
2 3
1 2 4
3 0 5
1 5
1 3 0 4 2```

### 输出

```
3
5```

# 题解

## 作者：2011FYCCCTA (赞：9)

[原题](https://www.luogu.com.cn/problem/P9698)

---
### 分析&思路

可以用二分答案解决。关键在于 check 函数，它可以这么写：题目中说每次只能向右或向下走，所以每一步的横坐标肯定都大于等于上一步，可以使用一个变量 `lstx` 记录，因此当某个点小于 check 函数传入的答案并且当前点的横坐标要比前一个小时，就说明这个答案不对，否则当前点的横坐标大于等于前一个时，更新 `lstx`。

**注意：由于 $n$ 和 $m$ 的范围，不能用二维数组存，需要压维。**

---
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t , n , m , a[(int)1e6 + 5] , ans;

bool check(int mina)
{
    int lstx = 1;
    for (int i = 1 ; i <= n ; i++)
        for (int j = 1 ; j <= m ; j++)
            if (a[(i - 1) * m + j] < mina)
            {
                if (lstx <= j) lstx = j;
                else return false;
            }
    return true;
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 1 ; i <= n * m ; i++) cin >> a[i];
        ans = 0;
        int l = 0 , r = n * m , mid;
        while (l <= r)
        {
            mid = (l + r) / 2;
            if (check(mid)) {ans = mid; l = mid + 1;}
            else r = mid - 1;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：zhaohanwen (赞：2)

### 题目分析

考虑二分答案。重点是 check 函数怎么写。先把所有二维的点都存起来，如果发现有逆序的，就说明有问题，check 函数返回 false 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
#define ll long long
int n, m, a[MAXN];
bool check(int mid)
{
	int last = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (a[i*m+j] < mid)
			{
				if (last > j) return false;
				last = j;
			}
		}
	}
	return true;
}
int solve()
{
	cin>>n>>m;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin>>a[i*m+j];
	int L = 0, R = n * m;
	while (L < R)
	{
		int mid = (L +R + 1)/2;
		if (check(mid)) L = mid;
		else R = mid - 1;
	}
	return L;
}
int main()
{
	int T;
	cin>>T;
	while (T--) cout<<solve()<<endl;
	return 0;
}
```


---

## 作者：May_Cry_ (赞：1)

### 思路

由于 $n,m\leq 10^{6}$，所以不能开二维数组，也就不能去写 bfs。我们考虑开两个桶数组记录每个值所在点的横纵坐标，二分答案，因为只能**往下或往右**走，所以我们在 `check` 时把每个值小于等于 `mid` 的数的坐标压入一个 `vector`，再给他排一个序，遍历整个 `vector`，当此时遍历的点的纵坐标小于上一个点的纵坐标，说明需要往左走或往上走，不满足条件。注意可能小于等于 `mid` 的值的点不包括起点和终点，所以需要特判压入这两个点。由于值域为 $0\sim n-1$，所以需要加 $1$，当然也可以从 $0$ 开始。

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 7;
int n ,m ,T;
int L[N] ,R[N] ,a[N];
int l ,r ,ans;
bool check (int mid) {
    bool f1 = 0 ,f2 = 0;vector <pair <int ,int> > E;//用pair可以直接先按横坐标再按纵坐标排序
    for (int i = 1;i <= mid;i ++) {
        E.push_back(make_pair(L[i] ,R[i]));
        if (L[i] == 1 && R[i] == 1) f1 = 1;
        if (L[i] == n && R[i] == m) f2 = 1;
    }
    if (!f1) E.push_back(make_pair(1 ,1));
    if (!f2) E.push_back(make_pair(n ,m));
    sort (E.begin(),E.end());
    // cout << endl;
    // for (int i = 0;i < E.size();i ++) cout << E[i].first << " " << E[i].second << endl;
    // cout << endl;
    int last = E[0].second;
    for (int i = 1;i < E.size();i ++) {
        if (last > E[i].second) return 0;
        last = E[i].second;
    }
    return 1;
}
inline int read();
int main(){
    T = read();
	while (T --) {
        n = read() ,m = read();
        for (int i = 1;i <= n * m;i ++) L[i] = R[i] = 0;
        for (int i = 1;i <= n;i ++) {
            for (int j = 1;j <= m;j ++) {
                a[i] = read();a[i] ++;L[a[i]] = i ,R[a[i]] = j;
            }
        }
        l = 0 ,r = n * m;
        while (l <= r) {
            int mid = l + r >> 1;
            if (check (mid)) l = mid + 1 ,ans = mid;
            else r = mid - 1;
        }
        printf ("%d\n" ,ans);
    }
	return 0;
}
inline int read(){
	int x = 0 ,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){ x = (x << 1) + (x << 3 ) + (ch ^ 48);ch = getchar();}
	return x * f;
}
```

---

## 作者：Error_Eric (赞：0)

### 题意

[LINK](https://www.luogu.com.cn/problem/P9698)

### Sol

比赛时候没想到二分，这里提供另外一个愚蠢做法。

记 $x_{a_{i,j}}=i$ , $y_{a_{i,j}}=j$ 。这种做法不会有冲突因为 $a_{i,j}$ 是两两不同的。

假设最后的路径经过的整数分别是 $p_1,p_2\dots p_{n+m-1}$。

不难发现 $x_{p_i}$ 和 $y_{p_i}$ 都是单调不降的。

考虑将 $[1, n+m-1]$ （显然答案最大就是 $n+m-1$）依次加入一个平衡树，其中这个平衡树以 $x$ 为第一关键字， $y$ 为第二关键字排序。检查插入后是否满足 $y$ 单调不降。如果满足，继续操作。如果不满足，输出答案即为当前操作的数。

时间复杂度是 $O((n+m)\log(n+m))$,可以通过。

### Code

```cpp#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
#include<set>
using namespace std;
const int _=1e6+5;
int t,n,m,aij,x[_],y[_];
struct node{ int val;node(int nx=0){val=nx;}};
bool operator<(node n1,node n2){
    if(x[n1.val]==x[n2.val]) return y[n1.val]<y[n2.val];
    else return x[n1.val]<x[n2.val];
}
set<node> q;
void mian(){
    cin>>n>>m,q.clear();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>aij,x[aij]=i,y[aij]=j;
    for(int i=0;i< n*m;i++){
        if(q.empty()){q.insert(i); continue;}
        auto it=q.lower_bound(i);
        if(it!=q.begin()){  // 如果有前缀
            auto it2=it; --it2;
            if(y[(*it2).val]>y[i])  // 检验 y 是否不降
                {cout<<i<<endl; return;}
        }
        if(it!=q.end()){   // 如果有后缀
            if(y[i]>y[(*it).val])    // 检验 y 是否不降
                {cout<<i<<endl; return;}
        }
        q.insert(i);
    }
    cout<<n+m-1<<endl;
}
int main(){
    ios::sync_with_stdio(0),cin>>t;
    while(t--) mian();
}
```

---

## 作者：Κarrу5307 (赞：0)

显然答案可以二分。判定答案能否是 $x + 1$，等价于判定是否存在一条路径，使得这条路径经过 $0\sim x$ 的格子。

也就是说，现在钦定某些格子必须走，判断存不存在这样的路径。称这些被钦定的格子为关键格子。

对于每一列，若存在关键格子，找出关键格子存在的最小行和最大行。形式化地，设第 $i$ 个格子的坐标为 $(x_i,y_i)$，对于每一列，找出 $a_i=\min\limits_{x_j=i}\{y_j\},b_i=\max\limits_{x_j=i}\{y_j\}$。若不存在这样的 $j$，人为定义 $a_i\gets b_{i-1},b_i\gets b_{i-1}$。

可以发现，存在合法路径的充分必要条件为：对于任意 $i$，满足 $a_i\geq b_{i-1}$。原因是只能向右或向下走，那么向右的过程中，行数是单调不降的。

---

