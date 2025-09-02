# [ARC190A] Inside or Outside

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc190/tasks/arc190_a

整数列 $ x\ =\ (x_1,\ \ldots,\ x_N) $ があり，$ x_1=\cdots=x_N=0 $ で初期化されています．

あなたはこの整数列について，$ M $ 回の操作を行います．$ i $ 回目の操作では，$ 1\leq\ L_i\leq\ R_i\leq\ N $ を満たす整数の組 $ (L_i,\ R_i) $ が与えられるので，以下の $ 3 $ つのうち**ちょうど** $ 1 $ つを行います．

- 操作 $ 0 $：何もしない．この操作にはコストが $ 0 $ かかる．
- 操作 $ 1 $：$ 1\leq\ j\leq\ N $ を満たす各整数 $ j $ に対して，$ L_i\leq\ j\leq\ R_i $ を**満たす**ならば $ x_j=1 $ と定める．この操作にはコストが $ 1 $ かかる．
- 操作 $ 2 $：$ 1\leq\ j\leq\ N $ を満たす各整数 $ j $ に対して，$ L_i\leq\ j\leq\ R_i $ を**満たさない**ならば $ x_j=1 $ と定める．この操作にはコストが $ 1 $ かかる．

あなたの目標は，最終的に $ x_1=\cdots=x_N=1 $ が成り立つようにすることです．この目標が達成できるか否かを判定してください．目標が達成可能な場合には，そのような方法のうち操作にかかるコストの総和が最小となるものをひとつ答えてください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 1000000 $
- $ 1\leq\ M\leq\ 200000 $
- $ 1\leq\ L_i\leq\ R_i\leq\ N $
- 入力される値はすべて整数

### Sample Explanation 1

出力例では $ x $ は次のように変化します． - はじめ $ x=(0,0,0,0,0) $ である． - $ 1 $ 回目の操作で操作 $ 2 $ を行う．$ x_1,x_5 $ が $ 1 $ になり，$ x=(1,0,0,0,1) $ になる． - $ 2 $ 回目の操作で操作 $ 0 $ を行う．$ x=(1,0,0,0,1) $ になる． - $ 3 $ 回目の操作で操作 $ 1 $ を行う．$ x_1,x_2,x_3,x_4 $ が $ 1 $ になり，$ x=(1,1,1,1,1) $ になる． - $ 4 $ 回目の操作で操作 $ 0 $ を行う．$ x=(1,1,1,1,1) $ になる．

## 样例 #1

### 输入

```
5 4
2 4
3 5
1 4
2 5```

### 输出

```
2
2 0 1 0```

## 样例 #2

### 输入

```
5 4
1 3
1 5
2 4
3 5```

### 输出

```
1
0 1 0 0```

## 样例 #3

### 输入

```
5 2
1 3
2 5```

### 输出

```
2
1 1```

## 样例 #4

### 输入

```
5 2
1 3
2 4```

### 输出

```
-1```

# 题解

## 作者：Noah2022 (赞：5)

### 思路
本题为 ARC 的第一题，一看就不是什么正经题目，采用分类讨论。
* 情况一，有一个区间为 $1 \sim n$ 花费为 1。
* 情况二，有两个区间，一个区间的 $l$ 为 `1`，另一区间的 $r$ 为 $n$，输出 `2` 和那两个 `1` 即可。
* 情况三，一个区间包含于另外一个区间，则里面的那个区间输出 `2`，外面的那个区间输出 `1`，总花费为 `2`。
* 情况四，有两个区间不相交，输出那两个 `2` 即可，总花费也为 `2`。
* 情况五，以上四个都不满足，且 $m \le 2$，输出 `-1` 即可。
* 情况六，以上五个都不满足，易证连续三个都是相交的情况，总花费为 `3`。


#### 小插曲
我在判情况 $3\sim4$ 时，用暴力枚举，由于怕时超，所以将第一重循环的边界改成了 $\min(10000,m)$，因为没有枚举完，错了 $8$ 个点。[Submission](https://atcoder.jp/contests/arc190/submissions/61665525)。

#### 方法
用一个变量存最小的 $r$，用来判断情况四。用一个变量存最大的 $r$，用来判断情况三即可。

### AC code And [AC Link](https://atcoder.jp/contests/arc190/submissions/61684796)
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
struct node
{
    int l, r, minr;
} s[200005];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> s[i].l >> s[i].r, s[i].minr = i;
        if (s[i].l == 1 && s[i].r == n)
        {
            cout << "1\n";
            for (int j = 1; j <= m; j++)
            {
                if (j == s[i].minr)
                    cout << "1 ";
                else
                    cout << "0 ";
            }
            return 0;
        }
    }
    sort(s + 1, s + m + 1, [](node a, node b)
         { return a.l == b.l ? a.r < b.r : a.l < b.l; });
    int minr = 1, maxr = 1;
    for (int j = 2; j <= m; j++)
    {
        if (s[minr].r < s[j].l)
        {
            cout << "2\n";
            for (int i = 1; i <= m; i++)
            {
                if (i == s[minr].minr || i == s[j].minr)
                    cout << "2 ";
                else
                    cout << "0 ";
            }
            return 0;
        }
        if (s[maxr].r >= s[j].r)
        {
            cout << "2\n";
            for (int i = 1; i <= m; i++)
            {
                if (i == s[maxr].minr)
                    cout << "1 ";
                else if (i == s[j].minr)
                    cout << "2 ";
                else
                    cout << "0 ";
            }
            return 0;
        }
        if (s[j].l == s[j - 1].l)
        {
            cout << "2\n";
            for (int i = 1; i <= m; i++)
            {
                if (i == s[j - 1].minr)
                    cout << "2 ";
                else if (i == s[j].minr)
                    cout << "1 ";
                else
                    cout << "0 ";
            }
            return 0;
        }
        if (s[minr].r > s[j].r)
            minr = j;
        if (s[maxr].r < s[j].r)
            maxr = j;
    }
    if (s[1].l == 1 && s[m].r == n)
    {
        cout << "2\n";
        for (int i = 1; i <= m; i++)
        {
            if (i == s[1].minr)
                cout << "1 ";
            else if (i == s[m].minr)
                cout << "1 ";
            else
                cout << "0 ";
        }
        return 0;
    }
    if (m <= 2)
    {
        cout << "-1";
        return 0;
    }
    else
    {
        cout << "3\n";
        for (int i = 1; i <= m; i++)
        {
            if (i == s[1].minr)
                cout << "2 ";
            else if (i == s[2].minr)
                cout << "1 ";
            else if (i == s[3].minr)
                cout << "2 ";
            else
                cout << "0 ";
        }
    }
    // for(int i=1;i<=m;i++){
    //     cout<<s[i].l<<" "<<s[i].r<<" "<<"\n";
    // }
}
```

---

## 作者：ARIS2_0 (赞：4)

### 前言

大力分讨，助我切 A。但是赛时判区间完全包含判挂了，吃了三发，糖丸了。

### 思路

考虑对花费的代价 $cost$ 分讨。

当 $cost=1$ 时，当且仅当存在一个区间 $[1,n]$，对它进行操作 $1$。易证这是唯一的方案。

当 $cost=2$ 时，分为三种情况：

1. 两个区间都进行操作 $1$，即有两个区间的并区间为 $[1,n]$。

2. 两个区间都进行操作 $2$，即两个区间无交。

3. 一个区间进行操作 $1$，一个区间进行操作 $2$。因为对一个区间进行操作 $2$ 时，它的内部是没有被覆盖的，所以进行操作 $1$ 的区间一定**完全包含**进行操作 $2$ 的区间。

将以上情况排除后，将 $m$ 个区间按左端点排序后，一定遵守如下条件：

$L_1<L_2<\dots<L_m,R_1<R_2<\dots<R_m,L_m<R_1$，且 $L_1=1$ 和 $R_m=n$ 不同时成立。

在这种情况下，若 $m=2$，显然无解。

接下来证明，当 $m\le 3$ 时，总有一种 $cost$ 为 $3$ 的方案能满足题目条件。

设 $mid=\lceil\frac{n}{2}\rceil$，我们对区间 $mid$ 进行操作 $2$，对区间 $mid-1$ 与 $mid+1$ 执行操作 $1$。因为上述条件，易证区间 $mid-1$ 与区间 $mid+1$ 的并区间一定**完全包含第 $mid$ 个区间**，则题给条件被满足。

### 实现

按上述方案构造即可。

时间复杂度 $O(m\log m)$。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16,maxn=1e6+10;
struct node{int id,l,r;}a[maxn];
bool operator < (node a,node b){
    return a.l==b.l?a.r<b.r:a.l<b.l;
}
int res[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;cin>>n>>m;
    for(int i=1;i<=m;i++){
        a[i].id=i,cin>>a[i].l>>a[i].r;
        if(a[i].l==1 and a[i].r==n){
            cout<<"1\n";
            for(int j=1;j<=m;j++){
                cout<<(i==j?1:0)<<" ";
            }
            return 0;
        }
    }
    sort(a+1,a+m+1);
    int id=1;
    int pid=1;
    for(int i=2;i<=m;i++){
        if(a[id].r<a[i].l){//无交
            cout<<"2\n";
            for(int j=1;j<=m;j++){
                if(a[id].id==j or a[i].id==j)cout<<"2 ";
                else cout<<"0 ";
            }
            return 0;
        }
        if(a[pid].r>=a[i].r){//第一种全交
            cout<<"2\n";
            for(int j=1;j<=m;j++){
                if(a[pid].id==j)cout<<"1 ";
                else if(a[i].id==j)cout<<"2 ";
                else cout<<"0 ";
            }
            return 0;
        }
        if(a[i].l==a[i-1].l){//第二种全交
            cout<<"2\n";
            for(int j=1;j<=m;j++){
                if(a[i-1].id==j)cout<<"2 ";
                else if(a[i].id==j)cout<<"1 ";
                else cout<<"0 ";
            }
            return 0;
        }
        if(a[id].r>a[i].r)id=i;
        if(a[id].r<a[i].r)pid=i;
    }
    if(a[1].l==1 and a[m].r==n){//并集为 [1,n]
        cout<<"2\n";
        for(int i=1;i<=m;i++){
            if(a[1].id==i or a[m].id==i)cout<<"1 ";
            else cout<<"0 ";
        }
        return 0;
    }
    if(m<=2){
        cout<<"-1";return 0;
    }
    int mid=ceil(m*1.0/2);
    cout<<"3\n";
    for(int i=1;i<=m;i++){
        if(a[mid].id==i)cout<<"2 ";
        else if(a[mid-1].id==i or a[mid+1].id==i)cout<<"1 ";
        else cout<<"0 ";
    }
	return 0;
}
/*
1 2
2 2
*/
```

---

## 作者：RAYMOND_7 (赞：3)

感谢 [@沉石鱼惊旋](https://www.luogu.com.cn/user/516346) 指出开始判断区间包含出现的问题。

简要题意：选择最少的区间，每个区间自由选择覆盖  $[l,r]$ 或 $[1,l-1] \cup [r+1,n]$ ，要求覆盖全集 $[1,n]$。

容易发现有解则答案不超过 $3$ 。

- 考虑答案为 $1$，这个只要判断 $[1,n]$ 是否存在。

- 考虑答案为 $2$，只需要考虑 $11, 12, 22$ 三种情况能否全覆盖，分别对应两个区间并集为全集，包含关系，完全不交，直接判断即可。

- 接下来若只有两个区间无解，否则所有区间有公共部分，可以选择右端点最小和左端点最大的向外覆盖，随便再选一个区间向内覆盖，容易发现一定可行。

```cpp
// LUOGU_RID: 198258183
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <ctime>

using namespace std;

#define PII pair<int,int>
#define x first
#define y second
#define For(i, l, r) for(int i = l; i <= r; i ++)
#define Rep(i, l, r) for(int i = l; i >= r; i --)

bool START;

void in(int &x)
{
	char c = getchar(); int op = 1;
	while(c > '9' || c < '0') op *= (c == '-' ? -1 : 1), c = getchar();
	for(x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0'; x *= op;
}

const int N = 1e6 + 50;

int n, m, a[N], L[N], R[N], cf[N], f[N], id[N];
PII p[N];

void Out(){For(i,1,m)printf("%d ", f[i]);}

bool ENDPOS = 0;
int main()
{
	double chu = clock();
	in(n); in(m);
	For(i, 1, m) in(L[i]), in(R[i]), cf[L[i]] ++, cf[R[i]+1]--;
	For(i,1,n)cf[i]+=cf[i-1];
	int ok=0;
	For(i,1,m)if(L[i]==1&&R[i]==n)ok=i;
	if(ok){puts("1"); f[ok]=1;Out(); return 0;}
	For(i,1,m)p[i]={L[i],R[i]};
	int mr=R[1],ml=L[1];
	For(i,1,m)mr=min(mr,R[i]),ml=max(ml,L[i]);
	if(ml>mr)
	{
		puts("2");
		int x=0,y=0;For(i,1,m)if(R[i]==mr)x=i;else if(L[i]==ml)y=i;
		f[x]=f[y]=2;
		Out();
		return 0;}
	For(i,1,m)id[i]=i;
	sort(id+1,id+m+1,[](int x,int y){return p[x].x!=p[y].x?p[x].x<p[y].x:p[x].y>p[y].y;});//左端点相同右端点降序
	For(i,1,m-1)
	{
		int u=id[i],v=id[i+1];
		if(p[u].y>=p[v].y)
		{
			puts("2");f[u]=1;f[v]=2;
			Out();return 0;
		}
	}
	For(i,2,n)
	{
		if(R[i]==n)
		{
			puts("2");f[id[1]]=f[i]=1;Out();return 0;
		}
	}
	if(m<3){puts("-1");return 0;}
	puts("3");
	int x=0,y=0;For(i,1,m)if(R[i]==mr)x=i;else if(L[i]==ml)y=i;
	int z=1;while(z==x||z==y)z++;
	f[x]=f[y]=2;f[z]=1;
	Out();
	cerr << "Time = " << (clock() - chu) / CLOCKS_PER_SEC << endl;
	cerr << (&ENDPOS - &START) * 1.0 / 1024 / 1024 << endl; return 0;
}


```

---

## 作者：huhaoming2011 (赞：2)

### 题目大意

给出一个大小为 $n$，初始值为 $0$ 的数组，然后给出 $m$ 个区间，每个区间选择题目中三种操作中一种，问：当数组最后都为 $1$ 时，最小代价是多少同时给出方案（可能无解）。

### 正解

分类讨论。

情况一：有一个区间 $l=1$ 同时 $r=n$。该区间进行操作一，代价为 $1$。

情况二：有两个区间不相交。两个区间都选择操作二，代价为 $2$。

情况三：有两个区间出现（完全）包含。被包含区间选操作二，另一个选操作一，代价为 $2$。

情况四：两个区间可以拼成整个数组。都选操作一，代价为 $2$。

情况五：不满足以上且 $m >2$。选中间的区间进行操作一，左右进行操作二，代价为 $3$。

情况六：以上都不满足。无解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+100;
int n,m;
struct Q {
	int l,r,id;
} q[MAXN];
bool cmp(Q x,Q y)
{
	return x.l<y.l or (x.l==y.l and x.r<y.r);
}
signed main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		q[i].id=i;
		scanf("%d %d",&q[i].l,&q[i].r);
		if(q[i].l==1 and q[i].r==n)
		{
			puts("1");
			for(int j=1;j<=m;j++)
			{
				if(i==j)
					putchar('1');
				else
					putchar('0');
				putchar(' ');
			}
			return 0;
		}
	}
	sort(q+1,q+m+1,cmp);
	int lst=1,lstt=1;
	for(int i=2;i<=m;i++)
	{
		if(q[lst].r<q[i].l)
		{
			puts("2");
			for(int j=1;j<=m;j++)
			{
				if(q[i].id==j or q[lst].id==j)
					putchar('2');
				else
					putchar('0');
				putchar(' ');
			}
			return 0;
		}
		if(q[i].l==q[i-1].l)
		{
			puts("2");
			for(int j=1;j<=m;j++)
			{
				if(q[i].id==j)
					putchar('1');
				else if(q[i-1].id==j)
					putchar('2');
				else
					putchar('0');
				putchar(' ');
			}
			return 0;
		}
		if(q[lstt].r>=q[i].r)
		{
			puts("2");
			for(int j=1;j<=m;j++)
			{
				if(q[lstt].id==j)
					putchar('1');
				else if(q[i].id==j)
					putchar('2');
				else
					putchar('0');
				putchar(' ');
			}
			return 0;
		}
		if(q[lst].r>q[i].r)
			lst=i;
		if(q[lstt].r<q[i].r)
			lstt=i;
	}
	if(q[1].l==1 and q[m].r==n)
	{
		puts("2");
		for(int i=1;i<=m;i++)
		{
			if(i==q[1].id or i==q[m].id)
				putchar('1');
			else
				putchar('0');
			putchar(' ');
		}
		return 0;
	}
	if(m<=2)
	{
		puts("-1");
		return 0;
	}
	int md=ceil(1.0*m/2);
	puts("3");
	for(int i=1;i<=m;i++)
	{
		if(i==q[md].id)
			putchar('2');
		else if(i==q[md-1].id or i==q[md+1].id)
			putchar('1');
		else 
			putchar('0');
		putchar(' ');
	}
	return 0;
}
```

---

## 作者：lhz2022 (赞：2)

我们发现进行操作的顺序没什么影响，所以可以把操作离线下来以便进行分类讨论。

首先如果有一个操作是 $[1,n]$，那么直接对它进行一次操作 $1$ 即可。

第一种情况：存在两个不相交的区间。很容易想到，从它们出发，都执行操作 $2$。

第二种情况：存在区间包含关系：很容易想到，对于范围更大的区间进行操作 $1$，对于范围小的区间进行操作 $2$。

第三种情况：存在两个形如 $[1,r_1]$ 和 $[l_1,n]$ 的区间，且满足 $r_1\geq l_1$。 对于这两个区间分别进行操作 $1$ 即可。

第四种情况：存在 $3$ 个形如这样的区间：

![](https://cdn.luogu.com.cn/upload/image_hosting/c8tklq7i.png)我们可以对于其中红色的区间进行操作 $2$，棕色的进行操作 $1$。

我们记把所有区间的右端点从小到大排序后，左端点第一个大于第 $i$ 个区间的区间编号为 $l_i$。

容易发现，可以使用单调栈求出所有的 $l$。

只需查找 $l_{l_i}$ 的区间的左端点是否在第 $i$ 个区间的右端点之前了。

[代码](https://atcoder.jp/contests/arc190/submissions/61649286)

---

## 作者：Drifty (赞：2)

### Solution

神秘的分讨，应该算一道诈骗吧。

通过一些观察容易发现这个东西的答案一定在 $1, 2, 3$ 之间。

考虑以下情况：

- 存在 $L_i = 1,R_i = n$，显然我们只要选这个区间就可以了。
- 存在 $i\neq j, L_i = 1,R_j = n$ 且 $L_j \le R_i$，此时我们选择这两个区间即可。
- 存在 $[L_i, R_i] \cap [L_j, R_j] = \varnothing$，此时我们选这两个区间的补即可。
- 存在 $[L_i, R_i] \in [L_j, R_j],i\neq j$，此时我们一个取补一个取原即可。
- 否则选出最前面的三个区间，其中一个取补一定可以覆盖 $[1, n]$。

按照上述分类模拟即可。[Submission.](https://atcoder.jp/contests/arc190/submissions/61655040)

---

## 作者：Jerrywang09 (赞：1)

思路清奇的题目。

操作 2 非常优秀，它能保证操作过后序列只会有中间的一段空着是 $0$。手玩发现答案不会超过 $3$，以下分类讨论将给出构造方案：

1. 有区间 $[1,n]$，只需要 $1$ 次操作即可。
2. 有两个区间存在包含关系。设这两个区间是 $a_i,a_j$ 且 $a_i\subseteq a_j$。将 $a_i$ 的外面填满，再把 $a_j$ 里面填满。找到两个存在包含关系的区间是一个经典贪心，考虑按区间左端点从大到小排序，维护右端点最小值即可。
3. 有两个区间无交。按照区间左端点从小到大排序，由于情况 2 已经判过了，因此可以保证右端点也从小到大。所以只需要考虑排序后的区间 $1$ 和区间 $m$ 是否无交。如果无交，则两个区间都把外面填满即可。
4. 所有区间有交。先判掉一种特殊情况，就是两个区间拼在一起可覆盖 $[1,n]$，同理也只需要考虑排序后的区间 $1$ 和区间 $m$。否则，随便选三个区间 $a_
i,a_j,a_k|i<j<k$，填满 $a_j$ 外面，由于 $a_i,a_k$ 有交，因此再把 $a_i,a_k$ 里面填满。如果现在只有 $\le 2$ 个区间则无解。

```cpp
// [ARC190A] Inside or Outside
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=200010;
using namespace std;
char buf[1<<21], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}

int n, m, res[N];
struct node {int l, r, i;} a[N];

void Exit()
{
    rep(i, 1, m) printf("%d ", res[i]);
    exit(0);
}

void solve1() // 一个区间直接铺满
{
    bool ok=0;
    rep(i, 1, m) if(a[i].l==1 && a[i].r==n)
    {
        ok=1, res[i]=1; break;
    }
    if(ok) puts("1"), Exit();
}

bool cmp1(node a, node b)
{
    return a.l!=b.l?a.l>b.l:a.r<b.r;
}
void solve2() // 两个区间有包含关系
{
    sort(a+1, a+m+1, cmp1);
    int mn=n+1, mni=0; bool ok=0;
    rep(i, 1, m)
    {
        if(a[i].r>=mn)
        {
            ok=1; res[a[mni].i]=2, res[a[i].i]=1; break;
        }
        mn=a[i].r, mni=i;
    }
    if(ok) puts("2"), Exit();
}

bool cmp2(node a, node b)
{
    return a.l<b.l;
}
void solve3() // 两个区间无交
{
    sort(a+1, a+m+1, cmp2);
    if(a[1].r<a[m].l)
    {
        res[a[1].i]=2, res[a[m].i]=2;
        puts("2"); Exit();
    }
}

void solve4() // 所有区间有交
{
    if(a[1].l==1 && a[m].r==n)
    {
        res[a[1].i]=1, res[a[m].i]=1;
        puts("2"); Exit();
    }
    if(m<=2) puts("-1"), exit(0);
    res[a[1].i]=1, res[a[2].i]=2, res[a[3].i]=1;
    puts("3"); Exit();
}

int main()
{
#ifdef Jerrywang
    freopen("in.txt", "r", stdin);
#endif
    n=read(), m=read();
    rep(i, 1, m) a[i].l=read(), a[i].r=read(), a[i].i=i;
    solve1();
    solve2();
    solve3();
    solve4();

    return 0;
}
```

最后推荐一道类似的[题目](/problem/CF1685C)以及[题解](/article/lgrkrdwo)。

---

## 作者：gyyyyx (赞：0)

太唐了，这题我交了不下五次。

我们按照最终代价从小到大思考。

-  若最终代价为 $1$，那么有且仅有一种方式：存在区间 $[1,n]$，然后对当前区间进行操作 $1$。

- 若最终代价为 $2$。

  显然至少需要两个区间，则 $m=1$ 时不存在方案。

  - 考虑如果是对两个区间分别进行操作 $1,2$，那么只可能是存在两个区间满足从属关系，即 $\exist 1\leq i\neq j\leq m,[L_i,R_i]\in[L_j,R_j]$。

    若存在则对 $i$ 区间进行操作 $2$，$j$ 区间进行操作 $1$。

    若不存在，说明按左端点或右端点排序后所有区间满足 $L_1<L_2<\cdots<L_m$ 且 $R_1<R_2<\cdots<R_m$（下面的分讨均以排好序的区间为前提）。

  - 考虑对两个区间都进行操作 $2$，那么只可能是存在两个区间不相交，即 $\exist 1\leq i<j\leq m,[L_i,R_i]\cap[L_j,R_j]=\varnothing$，即 $R_i<L_j$。

    而其充要条件为 $R_1<L_m$。

    若不存在，说明任意两个区间都相交。

  - 此时考虑对两个区间都进行操作 $1$，那么只可能是存在两个区间满足 $L_i=1,R_j=n$（注意这里是在任意两个区间都相交的前提下）。

    而其充要条件为 $L_1=1,R_m=n$。

- 若上述情况都不存在则说明最终代价不可能为 $2$，下面考虑最终代价为 $3$。

  显然至少需要三个区间，则 $m\leq 2$ 时不存在方案。

  而我们发现那么任意选取三个数 $1\leq i<j<k\leq m$，对区间 $i$ 和 $k$ 进行操作 $2$，对区间 $j$ 进行操作 $1$，一定可以达成目的。

  因为我们对区间 $i$ 和 $k$ 进行操作 $2$ 后，只剩下 $[L_i,R_i]\cap [L_k,R_k]$ 的范围没有染色，而 $[L_j,R_j]$ 必然包含这个范围。

  所以 $m\geq 3$ 时我们必然可以使得最终代价为 $3$。

代码：

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,m;
array <int,3> r[N];
int k,ans[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i(1);i<=m;++i)
		scanf("%d%d",&r[i][0],&r[i][1]),r[i][2]=i;
	sort(r+1,r+1+m,[](const array <int,3> &a,const array <int,3> &b){
		return a[0]^b[0]?a[0]<b[0]:a[1]>b[1];
	});
	if(r[1][0]==1&&r[1][1]==n){
		k=1;ans[r[1][2]]=1;
		goto OUTPUT;
	}
	if(m==1) goto NOPE;
	for(int i(1);i<m;++i)
		if(r[i+1][1]<=r[i][1]){
			k=2;ans[r[i][2]]=1;ans[r[i+1][2]]=2;
			goto OUTPUT;
		}
	if(r[1][1]<r[m][0]){
		k=2;ans[r[1][2]]=ans[r[m][2]]=2;
		goto OUTPUT;
	}
	if(r[1][0]==1&&r[m][1]==n){
		k=2;ans[r[1][2]]=ans[r[m][2]]=1;
		goto OUTPUT;
	}
	if(m>2){
		k=3;ans[r[1][2]]=ans[r[3][2]]=2;ans[r[2][2]]=1;
		goto OUTPUT;
	}
	NOPE:return puts("-1"),0;
	OUTPUT:
	printf("%d\n",k);
	for(int i(1);i<=m;++i) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

## Part 1 - 算法思路

这是一道很好的思维题。

下面描述中的排序均指以 $L$ 从小到大为第一关键字，$R$ 从大到小为第二关键字。

首先，可以发现答案只可能为 $-1,1,2,3$，有以下六种情况：

情况一：当存在区间 $[1,N]$ 时，选这个区间内，答案为 $1$。

情况二：当存在两区间相离时，分别选两区间之外，答案为 $2$。

情况三：当存在两区间存在包含关系时，选包含区间之内，被包含区间之外，答案为 $2$。

情况四：当存在两区间相交，其中之一左端点等于 $1$，另一右端点等于 $N$ 时，分别选两区间之内，答案为 $2$。

情况五：除上述 $4$ 种情况外，当 $m \ge 3$ 时，可以任选 $3$ 个区间，排序后按顺序分别选区间之内、之外和之内，答案为 $3$。

情况六：否则答案为 $-1$。

上述中的存在区间相离、包含和相交均可用排序进行判别。

## Part2 - 代码实现

下面代码中的 $type\in [1,6]$ 分别对应解析中的六种情况。

```cpp
// Problem: A - Inside or Outside
// Contest: AtCoder - AtCoder Regular Contest 190 (Div. 1)
// URL: https://atcoder.jp/contests/arc190/tasks/arc190_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define AC return 0

const ll mod = 1; // Be careful, 998244353 or 998244853.
const ll dx[] = {0, 1, 0, -1};
const ll dy[] = {1, 0, -1, 0};
mt19937 rnd(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
	
void ts() {
	cerr << "The code is running!\n";
}

ll read() {
    char c;
    bool isf = 0;
    while (!isdigit(c = getchar())) isf = (c == '-');
    ll res = (c ^ 48);
    while (isdigit(c = getchar())) res = (res << 3) + (res << 1) + (c ^ 48);
    return isf ? -res : res;
}

void write(ll x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x >= 10)
        write(x / 10);
    putchar('0' + x % 10);
}

void updmin(ll& x, ll y) {
	x = min(x, y);
}

void updmax(ll& x, ll y) {
	x = max(x, y);
}

ll qpow(ll x, ll y) {
	if (y == 0) {
		return 1;
	}
	ll res = qpow(x, y / 2);
	res *= res;
	res %= mod;
	if (y % 2) {
		res *= x;
		res %= mod;
	}
	return res;
}

ll randint(ll l, ll r) {
	return rnd() % (r - l + 1) +  l;
}

void openf(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

ll tc = 1, n, m, mn = 1e18, mnid, mx = -1e18, mxid, type;
ll mx1 = -1e18, mnn = 1e18, mxid1, mnidn;
ll ans[1000005];

struct node {
	ll l, r, id;
} a[1000005];

bool cmp(node qw, node er) {
	if (qw.l != er.l) {
		return qw.l < er.l;
	}
	if (qw.r != er.r) {
		return qw.r > er.r;
	}
	return qw.id < er.id;
}

void init() {
	;
}

void solve() {
	init();
	n = read(), m = read();
	for (ll i = 1; i <= m; i++) {
		a[i].id = i;
		a[i].l = read(), a[i].r = read();
	}
	sort(a + 1, a + m + 1, cmp);
	for (ll i = 1; i <= m; i++) {
		if (a[i].l == 1) {
			if (a[i].r > mx1) {
				mx1 = a[i].r;
				mxid1 = a[i].id;
			}
		}
		if (a[i].r == n) {
			if (a[i].l < mnn) {
				mnn = a[i].l;
				mnidn = a[i].id;
			}
		}
		if (a[i].l == 1 && a[i].r == n) {
			ans[a[i].id] = 1;
			type = 1;
			break;
		}
		if (mn < a[i].l) {
			ans[a[i].id] = 2;
			ans[mnid] = 2;
			type = 2;
			break;
		}
		if (mx >= a[i].r) {
			ans[a[i].id] = 2;
			ans[mxid] = 1;
			type = 3;
			break;
		}
		if (a[i].r < mn) {
			mn = a[i].r;
			mnid = a[i].id;
		}
		if (a[i].r > mx) {
			mx = a[i].r;
			mxid = a[i].id;
		}
	}
	if (!type) {
		if (mx1 >= mnn) {
			ans[mxid1] = ans[mnidn] = 1;
			type = 4;
		}
	}
	if (!type) {
		if (m >= 3) {
			ans[a[1].id] = 1, ans[a[2].id] = 2, ans[a[3].id] = 1;
			type = 5;
		} else {
			write(-1);
			type = 6;
			return;
		}
	}
	ll ans2 = 0;
	for (ll i = 1; i <= m; i++) {
		ans2 += (ans[i] != 0);
	}
	write(ans2);
	putchar('\n');
	for (ll i = 1; i <= m; i++) {
		write(ans[i]);
		putchar(' ');
	}
}

int main() {
	
    // openf("data");
    
    // ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    // tc = read();
    
    while (tc--) {
    	solve();
    	putchar("\n "[(!tc)]);
    }
    
    // printf("Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);

    AC;
}

/*
Things to check:

1. When testing multiple sets of data, remember to clear the array.

2. When clearing, pay attention to clearing the area, starting from 0 or 1. If time permits, use memset.

3. Delete the debugged code.

4. Do you need to enable file input/output.

5. Use faster input and output methods.

6. INT or long long.

7. Pay attention to time complexity and space complexity, and control constants.

8. Think twice before acting.

9. Talk is cheap, show me the code.

10. The most important one, zxq's brain.
*/

/*
                                                                                              
_|_|_|_|_|  _|      _|    _|_|          _|      _|        _|_|      _|      _|_|    _|  _|    
      _|      _|  _|    _|    _|          _|  _|        _|    _|  _|  _|  _|    _|  _|  _|    
    _|          _|      _|  _|_|            _|              _|    _|  _|      _|    _|_|_|_|  
  _|          _|  _|    _|    _|          _|  _|          _|      _|  _|    _|          _|    
_|_|_|_|_|  _|      _|    _|_|  _|      _|      _|      _|_|_|_|    _|    _|_|_|_|      _|    
          
.................................................................................................................
.................................................................................................................
.................................................................................................................
.................................................................................................................
.................................................................................................................
.......RRRRRRRRRRRRRRRRRRRR...................PPPPPPPPPPPPPPPPPPPP...............................................
.......RRRRRRRRRRRRRRRRRRRRRR.................PPPPPPPPPPPPPPPPPPPPPP.............................................
.......RRRRRRRRRRRRRRRRRRRRRRR................PPPPPPPPPPPPPPPPPPPPPPPP...........................................
.......RRRR.................RRRRR.............PPPP...............PPPPP...........................................
.......RRRR.................RRRRR.............PPPP................PPPPP..........................................
.......RRRR.................RRRRR.............PPPP................PPPPP..........................................
.......RRRR...............RRRRR...............PPPP...............PPPPP...........................................
.......RRRR............RRRRRR.................PPPP.............PPPPPP............................................
.......RRRR............RRRRRR.................PPPP............PPPPPP.............................................
.......RRRR........RRRRRR.....................PPPP........PPPPPPP................................................
.......RRRRRRRRRRRRRRRRRR.....................PPPPPPPPPPPPPPPPPP.................................................
.......RRRRRRRRRRRRRRRRRR.....................PPPPPPPPPPPPPPPP...................................................
.......RRRR..........RRRR.....................PPPPP.................................+++................+++.......
.......RRRR...........RRRR....................PPPPP.................................+++................+++.......
.......RRRR.............RRRR..................PPPPP.................................+++................+++.......
.......RRRR..............RRRR.................PPPPP...........................+++++++++++++++....+++++++++++++++.
.......RRRR...............RRRR................PPPPP...........................+++++++++++++++....+++++++++++++++.
.......RRRR................RRRR...............PPPPP.................................+++................+++.......
.......RRRR.................RRRR..............PPPPP.................................+++................+++.......
.......RRRR...................RRRR............PPPPP.................................+++................+++.......
.................................................................................................................
.................................................................................................................
.................................................................................................................
.................................................................................................................
.................................................................................................................
                                                                                    
                                                                 
*/
```

## Part 3 - 公开处刑

怎么能有人如此猖狂。

[![item.filename](https://pic1.imgdb.cn/item/67846e1ed0e0a243d4f3c422.png)](https://pic1.imgdb.cn/item/67846e1ed0e0a243d4f3c422.png)

---

