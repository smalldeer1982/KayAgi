# [ABC278D] All Assign Point Add

## 题目描述

【题目翻译】

给定长度为 $n$ 的数组 $a$，每次有三种操作：

+ $op_i = 1$，表示将 $a$ 数组全部元素替换成 $k$。
+ $op_i = 2$，表示 $a_i \gets a_i + k$。
+ $op_i = 3$，表示查询 $a_i$ 的值。

对于每个 $op_i = 3$，输出结果。

translated by @[liangbowen](https://www.luogu.com.cn/user/367488).

## 说明/提示

$1 \le n, q \le 2 \times 10^5$

保证 $1 \le i \le n$，$1 \le a_i, k \le 10^9$。

## 样例 #1

### 输入

```
5
3 1 4 1 5
6
3 2
2 3 4
3 3
1 1
2 3 4
3 3```

### 输出

```
1
8
5```

## 样例 #2

### 输入

```
1
1000000000
8
2 1 1000000000
2 1 1000000000
2 1 1000000000
2 1 1000000000
2 1 1000000000
2 1 1000000000
2 1 1000000000
3 1```

### 输出

```
8000000000```

## 样例 #3

### 输入

```
10
1 8 4 15 7 5 7 5 8 0
20
2 7 0
3 7
3 8
1 7
3 3
2 4 4
2 4 9
2 10 5
1 10
2 4 2
1 10
2 3 1
2 8 11
2 3 14
2 1 9
3 8
3 8
3 1
2 6 5
3 7```

### 输出

```
7
5
7
21
21
19
10```

# 题解

## 作者：Neil_Qian (赞：6)

# [ABC278D] All Assign Point Add 题解
给你一个长度为 $n$ 的序列 $a$，有一下三种操作：

- 给定一个数 $x$，把所有 $a$ 中的元素变为 $x$.
- 给定两个数 $i$ 和 $x$,把 $a_i$ 赋值为 $x$。
- 给定一个数 $i$，求出 $a_i$。

由于 $n\times q$ 显然太大，暴力不可能过。

很容易发现，在执行第一个操作的时候，很多数根本没有经过其它的修改就被下一次全部赋值给赋值成了其他的数。

因此，我们要考虑在修改或是访问是进行修改。

如果在访问的时候赋值的话，会发现一个问题，根本不知道是先赋值还是先修改，所以只能在修改的时候赋值。

如何知道每一个数是否被最新的赋值过呢？如果用布尔值的话，每次需要把整个数组赋值为零，又不行了。应该对每一个下标都有一个更新度 $cnt$，然后有一个最新值 $rp$，每一次修改先看一看：更新了吗？是最新吗？即检查 $cnt_i$ 是否等于 $rp$。每次赋值的时候，$rp+1$ 并且将赋值的值变为输入的数。这样就实现了每次常数的询问。

```cpp
#include<bits/stdc++.h>
using namespace std;using ll=long long;
ll n,Q,a[200002],op,x,y,to,cnt[200002],rp;
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)scanf("%lld",&a[i]);
	scanf("%lld",&Q);
	while(Q--){
		scanf("%lld",&op);
		if(op==1)scanf("%lld",&x),to=x,rp++;
		else if(op==2){
			scanf("%lld%lld",&x,&y);
			if(cnt[x]<rp)a[x]=to,cnt[x]=rp;
			a[x]+=y;
		}
		else{
			scanf("%lld",&x);
			if(cnt[x]<rp)a[x]=to,cnt[x]=rp;
			printf("%lld\n",a[x]);
		}
	}
	return 0;
}
```


---

## 作者：liangbowen (赞：1)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc278_d)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16910364.html)

难度加强版：[P1253](https://www.luogu.com.cn/problem/P1253)。

[整合题解](https://www.luogu.com.cn/blog/liangbowen/abc278-ti-jie)。

## 思路

很容易想到线段树。维护 $cov_i$ 表示覆盖的懒标记。

单点加与单点查都非常简单。全局覆盖只需要给每一层都打懒标记即可。

对于 pushdown 操作，看是否有 $cov$ 标记，有就先覆盖，再加。

## 代码

事实上，如果你做过 P1253，你会发现这题只需要改一改操作就行。

~~所以我两分钟过了 D！~~。

由于[代码](https://atcoder.jp/contests/abc278/submissions/36621808)是从 P1253 贴过来的，所以很诡异，就不放出来了。

---

## 作者：Laffey (赞：0)

## Solution

&emsp;&emsp;[更好的阅读体验？](https://laffey.fun/abc278d-all-assign-point-add)

&emsp;&emsp;题目是一个简单的区间覆盖修改 + 单点查询问题。可以直接线段树在 $O(n + q \log n)$ 的复杂度内解决。

&emsp;&emsp;注意到后两种操作可以用普通的数组，而区间覆盖只有全部覆盖一种范围。我们可否利用这些性质优化时间复杂度呢？

&emsp;&emsp;答案是肯定的。类比线段树的懒标记思想，我们可以在执行覆盖时先不进行任何操作，在之后用到这个数字时再进行修改。这可以通过再开一个标记数组实现。

&emsp;&emsp;然而，我们每次覆盖都要清空原有的标记，如果朴素地做复杂度将会达到 $O(nq)$，这是我们不能接受的。为了优化，可以引入「时间戳」的思想。每次清空标记时，将当前时间戳加上 $1$；判断是否进行过修改时，判断这个位置的标记是否和当前时间戳相等即可。这些操作都是 $O(1)$ 的。因此总的复杂度可以做到 $O(n + q)$。

## Code

```cpp
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
ll a[MAXN];
int v[MAXN];
int cov, top;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    // freopen("out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    const char endl = '\n';

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    while (q--) {
        int t, p, x;
        cin >> t;
        switch (t) {
            case 1:
                cin >> cov;
                top++;
                break;
            case 2:
                cin >> p >> x;
                if (v[p] != top) {
                    v[p] = top;
                    a[p] = cov;
                }
                a[p] += x;
                break;
            case 3:
                cin >> p;
                if (v[p] != top) {
                    v[p] = top;
                    a[p] = cov;
                }
                cout << a[p] << endl;
                break;
        }
    }

    return 0;
}
```

---

## 作者：sunzz3183 (赞：0)

# [ABC278D] All Assign Point Add 题解

## 题意

给定一个长度为 $n$ 的序列 $a$，要求执行以下操作 $q$ 次操作：

- 区间推平

- 单点加

- 单点查询

## 分析

如果只有单点加和查询的话，那么其实只要每次对每个点进行一次操作就可以了，时间为 $O(1)$ 。

但现在有一个区间推平，如果我们直接推平的话，时间为 $O(n)$，总共为 $O(nq)$，肯定为超时，怎么办呢？

~~珂朵莉树~~

我们可以用分块的思想，给每个点打上一个懒标记 $c_i$，记录它**上一次被使用的时间**，你会问：“那这样推平的话每次更改时间不还是要 $O(n)$ 吗？”

其实，每次推平会对每个点都进行修改，所以我们对总序列去打一个懒标记 $id$ 与 $x$，记录**上一次被推平的时间**和**推平的数字**。

而处理这两个懒标记就非常简单了

首先，$c_i$ 初始为 $0$，意为没有被使用过。

对于区间推平：直接更改 $id$ 等于当前时间（操作次数），$x$ 等于推平的数字。

对于单点加：检查 $c_i$ 是否大于 $id$，即在推平后操作过，直接加即可，不用更改 $c_i$，因为我们注意的仅是 $c_i>id$；如果小于，那么也就是说 $a_i$ 被推平过了 $a_i=x+num$，其中 $num$ 为加数。

对于单点查询：与单点加同理，检查 $c_i$ 是否大于 $id$，直接输出可；如果小于，那么也就是说 $a_i$ 被推平过了 $a_i=x$，然后输出。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mk make_pair
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=2e5+5;
int n,q,x,id,a[N],c[N];
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	q=read();
	for(int i=1;i<=q;i++){
		int opt=read();
		if(opt==1){
			x=read();id=i;
		}
		if(opt==2){
			int y=read(),num=read();
			if(c[y]<id)a[y]=x+num,c[y]=i;
			else a[y]+=num;
		}
		if(opt==3){
			int y=read();
			if(c[y]<id)a[y]=x,c[y]=i;
			printf("%lld\n",a[y]);
		}
	}
	return 0;
}
```


---

