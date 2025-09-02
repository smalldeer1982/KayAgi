# [ABC179F] Simplified Reversi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc179/tasks/abc179_f

縦 $ N $ マス、横 $ N $ マスのグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマスをマス$ (i,j) $ と表します。

グリッドの中央 $ (N-2)\times\ (N-2) $ マスには黒い石が $ 1 $ 個ずつ置いてあり、下辺と右辺の計 $ 2N-1 $ マスには白い石が $ 1 $ 個ずつ置いてあります。

$ Q $ 個のクエリが与えられるので、順番に処理してください。 クエリには $ 2 $ 種類あり、入力形式とクエリの内容は以下のとおりです。

- `1 x`： $ (1,x) $ に白い石を置く。そこから下方向に最も近い白い石との間にある黒い石を全て白い石に置き換える
- `2 x`： $ (x,1) $ に白い石を置く。そこから右方向に最も近い白い石との間にある黒い石を全て白い石に置き換える

$ Q $ 個のクエリを全て処理したあとグリッド上に黒い石はいくつありますか。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ Q\ \leq\ \min(2N-4,2\times\ 10^5) $
- $ 2\ \leq\ x\ \leq\ N-1 $
- 同じクエリが複数回与えられることはない

### Sample Explanation 1

各クエリにより、グリッドは次のように変化します。 !\[図\](https://img.atcoder.jp/ghi/31ba2cd6b3155b137f0e007299225028.png)

## 样例 #1

### 输入

```
5 5
1 3
2 3
1 4
2 2
1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
200000 0```

### 输出

```
39999200004```

## 样例 #3

### 输入

```
176527 15
1 81279
2 22308
2 133061
1 80744
2 44603
1 170938
2 139754
2 15220
1 172794
1 159290
2 156968
1 56426
2 77429
1 97459
2 71282```

### 输出

```
31159505795```

# 题解

## 作者：syxmz (赞：5)

### 1 题目链接
[传送门](https://atcoder.jp/contests/abc179/tasks/abc179_f?lang=en)
### 2 题目大意
有一个边长为 $N$ 正方形的网格，$(i,j)$ 为第 $i$ 行第 $j$ 列的正方形。

网格中央 $(N-2)\times(N-2)$ 的每个方格上都有一个黑色的石头。底部和右侧的方格中，每个方格上都有一块白色的石头。

给出了 $Q$ 个查询，有两种查询。它们的输入格式和描述如下:

- 在 $(1,x)$ 上放一个白色石头。之后，对于 $(1,x)$ 和 $(1,x)$ 之间的每一个黑色石头，如果你从 $(1,x)$ 开始，用白色石头替换它。
- 在 $(x,1)$ 上放一个白色石头。之后，对于 $(x,1)$ 和 $(x,1)$ 之间的每一个黑色石头，如果你从 $(x,1)$ 开始，你击中的第一个白色石头，用白色石头替换它。

在处理完所有 $Q$ 次查询后，网格上有多少黑色石头?
### 3 解法分析
提供一种不用数据结构的思路。

先把格局打开，把它想成一道思维题。

假设某一黑色区域宽为 $x$，长为 $y$，我们考虑一种修改，比如 $1\ \ k$。

不难发现修改后对 $[k+1,y]$ 的 $1$ 操作，都是固定的减去 $x$。

而 $2$ 操作与 $1$ 同理。

每操作一次都将黑色区域的长宽进行缩小，并用数组记录减少的黑色方块数即可。
### 4 AC Code
```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); ++(i))
#define fep(i, a, b) for (int (i) = (a); (i) < (b); ++(i))
#define int long long
#define N 200007
using namespace std;

int ans;
int n, q;
int x, y;
int opt, k;
int r[N],c[N];

signed main() {
	scanf("%lld%lld", &n, &q);
	x = y = n;
	ans = (n - 2) * (n - 2);
	while (q--) {
		scanf("%lld%lld", &opt, &k);
		if (opt == 1) {
			if (k < y) {
				ans -= x - 2;
				while (y > k)
					c[y--] = x - 2;
			}
			else
				ans -= c[k];
		}
		else {
			if (k < x) {
				ans -= y - 2;
				while (x > k)
					r[x--] = y - 2;
            }
			else
				ans -= r[k];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：zhr2021 (赞：2)

# [ABC179F] Simplified Reversi 题解
[题面链接](https://www.luogu.com.cn/problem/AT_abc179_f)  
~~这是本蒟蒻的第一篇题解，大佬勿喷。~~  
~~线段树模板题，但题解区没有一篇是线段树。~~

分享一种题解区还没有的线段树做法。
## step 1 大体思路
一个非常粗暴的思路，考虑记录当前在上面或左侧放一个白棋，会把多少个黑棋变成白棋。
## step 2 分析样例
![](https://cdn.luogu.com.cn/upload/image_hosting/vjteqkmw.png)

这是初始的状态，在所有位置放白棋的贡献都是 3。

![](https://cdn.luogu.com.cn/upload/image_hosting/toetwaap.png)

第一次操作后，更新在左侧放棋子的贡献（由于不会重复放置，最中间一列不必更新）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ugyq25xz.png)

第二次操作后，更新在上方放棋子的贡献。

发现在上方放棋子，就要更新左边；在左边放棋子，就要更新上方。每次的贡献，是当前这个地方的所有更新的最小值。

我们会发现，这其实就是两棵支持区间取最小值和单点查询的线段树！！！

**时间复杂度 $O(n+q\log n)$**

~~然而发现时间复杂度并不优秀。~~
## step 3 代码
思路已经出来了，就是线段树模板，操作还贼少。

最后，放上本蒟蒻~~极其丑陋的~~线段树代码。
```cpp
#include<bits/stdc++.h>
#define L long long
using namespace std;
const L N=2e5+10,inf=1e12;
L n,q,ans,opt,x;
struct sgtree{
	L tree[N<<2],tag[N<<2];
	#define ls p<<1
	#define rs p<<1|1
	void pushdown(L p){
		tag[ls]=min(tag[ls],tag[p]);
		tag[rs]=min(tag[rs],tag[p]);
		tag[p]=inf;
	}
	void build(L s,L t,L p,L val){
		tag[p]=inf;
		if(s==t){tree[p]=val;return;}
		L m=s+t>>1;
		build(s,m,ls,val);
		build(m+1,t,rs,val);
		return;
	}
	void mdf(L s,L t,L p,L l,L r,L val){
		if(s==t){tree[p]=min(min(tag[p],tree[p]),val);return;}
		if(l<=s&&t<=r){tag[p]=min(tag[p],val);return;}
		pushdown(p);
		L m=s+t>>1;
		if(l<=m) mdf(s,m,ls,l,r,val);
		if(m<r) mdf(m+1,t,rs,l,r,val);
	}
	L qry(L s,L t,L p,L k){
		if(s==t){
			tree[p]=min(tree[p],tag[p]);
			return tree[p];
		}
		pushdown(p);
		L m=s+t>>1;
		if(s<=k&&k<=m) return qry(s,m,ls,k);
		else return qry(m+1,t,rs,k);
	}
}tr[2];
int main(){
	scanf("%lld%lld",&n,&q);
	ans=(n-2)*(n-2);
	tr[0].build(2,n-1,1,n-2);
	tr[1].build(2,n-1,1,n-2);
	while(q--){
		scanf("%lld%lld",&opt,&x);
		if(opt==1){
			L s=tr[0].qry(2,n-1,1,x);
			ans-=s;
			tr[1].mdf(2,n-1,1,2,s+1,x-2);
		}
		else{
			L s=tr[1].qry(2,n-1,1,x);
			ans-=s;
			tr[0].mdf(2,n-1,1,2,s+1,x-2);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

## step 4 总结
在此题，线段树并不是一个时间复杂度十分优秀的算法。但线段树的写法十分模板，背熟了就可以节约时间，在赛时可以节省出时间去看后面的题。

---

## 作者：liruixiong0101 (赞：1)

# at_abc179_f - Simplified Reversi
## 题意：
luogu 有点难懂，这里给一个易懂的翻译。

有一个 $n\times n$ 的网格图，中央的 $(n-2)\times(n-2)$ 的区域有黑色石头，第 $n$ 行和第 $n$ 列全部有白色石头，你需要进行下列 $2$ 中操作 $T$ 次，求最后黑色石头的数量。操作如下：

- 将第 $x$ 列从上往下数的第一个白色石头的上面所有的黑色石头换成白色石头。
- 将第 $x$ 列从左往右数的第一个白色石头的左边所有的黑色石头换成白色石头。

## 思路：
先考虑第一种操作，我们需要找到第 $x$ 列的第一个白色石头，其实就是第 $x$ 列的白色石头的横坐标的最小值，考虑到我们还要添加白色石头，我们可以用线段树维护行和列的最上或最左的白色石头的位置（就是查单点最小值），然后再在 $1$ 到这个白色石头的位置添加白色石头（就是区间查最小值），这可以用线段树维护。

## 代码：
<https://atcoder.jp/contests/abc179/submissions/57823074>

---

## 作者：hellolin (赞：1)


# ABC179F Simplified Reversi 题解

建议前往 [note.hellolin.cf](https://note.hellolin.cf/solutions/abc179f/) 获得更好的阅读体验！

一个边长为 $n$ 的正方形，中间 $(n-2)\times (n-2)$ 每个方格都有一颗黑子，底部和右边每个方格都有一颗白子。

有以下两种询问：

- `1 x`：在 $(1,x)$ 处放一颗白子，将其与向下最近的白子之间的所有黑子替换为白子。

- `2 x`：在 $(x,1)$ 处放一颗白子，将其与右边最近的白子之间的所有黑子替换为白子。

处理完所有的 $q$ 次查询后，问剩下多少黑子？

---

考虑如下的初始局面：

![](https://cdn.luogu.com.cn/upload/image_hosting/s8vzo3p3.png)

此时，假设有询问 `1 x`：

![](https://cdn.luogu.com.cn/upload/image_hosting/ufprvv3z.png)

替换完成后，我们发现右边这些方格不再受 2 操作的影响，于是可以缩小长宽：

![](https://cdn.luogu.com.cn/upload/image_hosting/xgywzqbo.png)

反过来同理。

之后，使用两个数组存储每行每列剩的黑子即可。两个数组只会在缩小长宽时更新，故时间复杂度为 $O(n+q)$。

``` cpp
constexpr int N = 2e5 + 5;
int a[N], b[N];

void main() {
    int n, c, r;
    read(n);
    std::fill(&a[1], &a[n + 1], n);
    std::fill(&b[1], &b[n + 1], n);
    ll ans = (1ll * n - 2ll) * (1ll * n - 2ll);
    c = r = n;
    for (int q = read(); q--;) {
        int op, x;
        read(op, x);
        if (op == 1) {
            if (x < c) {
                std::fill(&b[x], &b[c], r);
                c = x;
            }
            ans -= b[x] - 2;
        } else {
            if (x < r) {
                std::fill(&a[x], &a[r], c);
                r = x;
            }
            ans -= a[x] - 2;
        }
    }
    writeln(ans);
}
```

也可用线段树解决问题，区间 chmin + 单点查询即可。这里就不贴代码了。


---

## 作者：Claire0918 (赞：0)

先给出样例的操作示意图。

![](https://cdn.luogu.com.cn/upload/image_hosting/dashdbq0.png)

观察操作过程，考量第 $x$ 列上的操作可以消去几个黑子。记 $y$ 表示最小的行使得该行在 $x$ 列上有操作，那么第 $x$ 列上的操作显然只能消去 $y - 2$ 个黑子。

具体的，我们记第 $x$ 行消去到的最大的列为 $a_x$，第 $y$ 列消去到的最大的行为 $b_y$。那么在操作第 $x$ 列时，我们要找到最小的 $y$，使得 $b_y \geq x$，答案即为 $y - 2$。这等价于找到最大的 $y$，使得 $(\forall i \in [1, y])(b_y < x)$，答案为 $y - 1$。

不难想到二分。一个 $y$ 合法的条件是 $\max_{i = 1}^{y} b_i < x$。我们需要维护动态的前缀最大值，可以运用线段树维护。

对第 $y$ 行的操作是类似的，这里不再详细描述。

时间复杂度 $\mathcal{O}(n \log^2 n)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2e5 + 10;

struct{
    struct{
        int l, r, value;
    } tree[maxn << 2];

    inline void pushup(int index){
        tree[index].value = max(tree[index << 1].value, tree[index << 1 | 1].value);
    }

    inline void build(int index, int l, int r){
        tree[index].l = l, tree[index].r = r;
        if (l == r){
            return;
        }
        const int mid = l + r >> 1;
        build(index << 1, l, mid);
        build(index << 1 | 1, mid + 1, r);
    }

    inline void modify(int index, int x, int k){
        if (tree[index].l == tree[index].r){
            tree[index].value = k;
            return;
        }
        const int mid = tree[index].l + tree[index].r >> 1;
        if (x <= mid){
            modify(index << 1, x, k);
        }else{
            modify(index << 1 | 1, x, k);
        }
        pushup(index);
    }

    inline int query(int index, int l, int r){
        if (l <= tree[index].l && r >= tree[index].r){
            return tree[index].value;
        }
        const int mid = tree[index].l + tree[index].r >> 1;
        int res = -1e9;
        if (l <= mid){
            res = max(res, query(index << 1, l, r));
        }
        if (r > mid){
            res = max(res, query(index << 1 | 1, l, r));
        }
        return res;
    }
} a, b;

int n, q;
long long res;

int main(){
    scanf("%d %d", &n, &q);
    res = (long long)(n - 2) * (n - 2);
    a.build(1, 1, n - 1), b.build(1, 1, n - 1);
    while (q--){
        int op, x;
        scanf("%d %d", &op, &x);
        if(op == 1){
            int l = 1, r = n - 1;
            while (l < r){
                const int mid = l + r + 1 >> 1;
                if (b.query(1, 1, mid) < x){
                    l = mid;
                }else{
                    r = mid - 1;
                }
            }
            res -= (l - 1);
            a.modify(1, x, l);
        }else{
            int l = 1, r = n - 1;
            while (l < r){
                const int mid = l + r + 1 >> 1;
                if (a.query(1, 1, mid) < x){
                    l = mid;
                }else{
                    r = mid - 1;
                }
            }
            res -= (l - 1);
            b.modify(1, x, l);
        }
    }
    printf("%lld", res);
}
```

---

