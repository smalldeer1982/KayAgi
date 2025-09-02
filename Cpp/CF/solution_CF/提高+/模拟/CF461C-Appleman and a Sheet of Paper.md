# Appleman and a Sheet of Paper

## 题目描述

Appleman has a very big sheet of paper. This sheet has a form of rectangle with dimensions $ 1×n $ . Your task is help Appleman with folding of such a sheet. Actually, you need to perform $ q $ queries. Each query will have one of the following types:

1. Fold the sheet of paper at position $ p_{i} $ . After this query the leftmost part of the paper with dimensions $ 1×p_{i} $ must be above the rightmost part of the paper with dimensions $ 1×([current width of sheet]-p_{i}) $ .
2. Count what is the total width of the paper pieces, if we will make two described later cuts and consider only the pieces between the cuts. We will make one cut at distance $ l_{i} $ from the left border of the current sheet of paper and the other at distance $ r_{i} $ from the left border of the current sheet of paper.

Please look at the explanation of the first test example for better understanding of the problem.

## 说明/提示

The pictures below show the shapes of the paper during the queries of the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF461C/0d6f18a0c20d16406159d704035cbac205902978.png)After the first fold operation the sheet has width equal to $ 4 $ , after the second one the width of the sheet equals to $ 2 $ .

## 样例 #1

### 输入

```
7 4
1 3
1 2
2 0 1
2 1 2
```

### 输出

```
4
3
```

## 样例 #2

### 输入

```
10 9
2 2 9
1 1
2 0 1
1 8
2 0 8
1 2
2 1 3
1 4
2 2 4
```

### 输出

```
7
2
10
4
5
```

# 题解

## 作者：Rushroom (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF461C)
## 题目意思
一个长度为 $n$ 的纸条，包括两端一共有 $n+1$ 个点，编号为 $0$ $\sim$ $n$ ，有 $q$ 个操作，分两种：

 $1$ $p$  ：从第 $p$ 个点处向右折（折后重新把点编号）

$2$ $l$ $r$ ：求第 $l$ 个点到第 $r$ 个点中间共有多少个长度为 $1$ 的纸（可能会有多层）
## 思路
很容易想到用树状数组维护区间和

那么问题就在第一个操作了

很容易想到每次暴力单点修改，但是如果 $p$ 在纸条长度的一半以上，向右折的时候就会越界。所以我们在 $p$ 在纸条长度一半以上时把右半边向左折过来，并且把所有下标反过来，同时用 $fst$ 变量记录现在 $0$ 号点的下标（因为折的时候会变），$f$ 记录下标是正的还是反的。

所以用这个函数算出点对应的下标

```cpp
int index(int i)
{
    i--;
    return fst + f * i;
}
```

再把树状数组板子套上去，就能 A 了

注意下标正反

## 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define ld long double
#define forr(i, a, n) for (int i = a; i < n; i++)
#define rep(i, n) forr(i, 0, n)
#define repp(i, n) forr(i, 1, n + 1)
#define foreach(it, t) for (__typeof(t.begin()) it = t.begin(); it != t.end(); it++)
#define pb push_back
#define mp make_pair
#define all(a) a.begin(), a.end()
#define init(a, i) memset(a, i, sizeof(a))
#define pii pair<int, int>
#define vvi vector<vector<int> >
#define MAXN 0x3f3f3f3f
int n, m, q, op, l, r, x, tree[100005], fst = 1, f = 1;
int lowbit(int i)
{
    return i & (-i);
}
void update(int x, int k)//单点修改
{
    while (x <= n)
    {
        tree[x] += k;
        x += lowbit(x);
    }
}
int sum(int x)//1~x区间和
{
    if (!x)
        return 0;
    int cnt = 0;
    while (x > 0)
    {
        cnt += tree[x];
        x -= lowbit(x);
    }
    return cnt;
}
int index(int i)//求下标
{
    i--;
    return fst + f * i;
}
int query(int x)//单点查询
{
    if (f == 1)
        return sum(index(x)) - sum(index(x - 1));
    else
        return sum(index(x)) - sum(index(x + 1));
}
void solve()
{
    cin >> n >> q;
    m = n;
    repp(i, n) update(i, 1);
    while (q--)
    {
        cin >> op;
        if (op == 1)//1操作
        {
            cin >> x;
            if (x <= m - x)//小于等于一半
            {
                for (int i = 1; i <= x; i++)//暴力修改
                    update(index(x + i), query(x-i+1));
                m -= x;
                fst = index(x+1);
            }
            else//大于一半
            {
                for (int i = 1; i <= m - x; i++)//暴力修改
                    update(index(x - i + 1), query(x + i));
                m = x;
                fst = index(x);
                f *= -1;//下标反转
            }
        }
        else//2操作
        {
            cin >> l >> r;
            l++;
            if (f == 1)
                cout << sum(index(r)) - sum(index(l-1)) << endl;
            else
                cout << sum(index(l)) - sum(index(r+1)) << endl;
        }
    }
}
int main()
{
    int T;
    T = 1;
    //cin>>T;
    while (T--)
        solve();
    return 0;
}
```


---

## 作者：Ynoi (赞：5)

每次折叠，如果左边的长度大于右边，则直接暴力折叠

如果左边长度小于右边，则右边向左边折叠，然后打上翻转标记

至于一个区间求纸条长度，用树状数组维护一下了

时间复杂度：

设每次折叠长度为x，则总长度减小x

故最多有n次修改

则时间复杂度为 $O(nlogn)$（这个log是树状数组）

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define lowbit(x) (x&(-x))

int n,m,l,r,sl,q;
int a[MAXN];
int c[MAXN];//树状数组

void jia(int x,int y) {
	while(x <= n) 
	{
		c[x] += y;
		x += lowbit(x);
	}
}

int he(int x) {
	int ans = 0;
	while(x > 0) {
		ans += c[x];
		x -= lowbit(x);
	} return ans; 
} 

int qiu(int l,int r) {
	return he(r) - he(l-1); 
}

void orz(int x,int y) {
	a[x] += y;
	jia(x,y);
}

void zzq(int x) {//从左边折叠
	for(int i = l; i < x; i ++) {
		orz(x*2-i-1,a[i]);
	} l = x;
} 

void wxh(int x) { //从右边折叠
	for(int i = r; i >= x; i --) {
		orz(x*2-i-1,a[i]);
	} r = x-1;
}

int o = 0;//0没有翻转，1翻转

inline int QAQ(int x)//将一个点位置转换为翻转后的位置
{
	if(o == 1) return l+r-x;
	return x;
}

int main()
{
	cin >> n >> q;
	l = 1; r = n;
	sl = 1;
	for(int i = 1; i <= n; i ++) 
		orz(i,1);
	for(int i = 1; i <= q; i ++)
	{
		int opt;
		cin >> opt;
		sl = l;
		if(opt == 1) {
			int x;
			cin >> x;
			x += sl;
			sl = l; 
			if(o == 0) {
				if(x*2 > (l+r)) {
					wxh(x); 
					o ^= 1; 
				} else {
					zzq(x);
				}
			} else {
				x = (r+l-x);
				x ++;
				if(x*2 > (l+r)) {
					wxh(x); 
				} else {
					zzq(x);
					o ^= 1; 
				}				
			}
		} else {
			int ll,rr;
			cin >> ll >> rr;
			ll += sl;
			rr += sl;
			rr --;
			ll = QAQ(ll);
			rr = QAQ(rr);
			if(rr < ll) swap(ll,rr);
			cout<<qiu(ll,rr)<<"\n"; 
		} 
		
	} 
	return 0; 
 } 
```

---

## 作者：SengRiy (赞：0)

## 简要题意

初始有一个长度为 $n$，厚度为 $1$ 的纸条，有 $q$ 次操作，操作 $1$ 为给出一个 $p$，以 $p$ 将纸条折叠；操作 $2$ 为询问一个区间的所有纸条的长度之和。

## 思路

首先，每次折叠纸条时，便于操作，可以将短的一段折向长的一段，当需将右端折向左端时，相当于将整个区间翻转即可。

由于操作 $1$ 无法直接区间修改，直接暴力单点修改，复杂度易证。

区间和查询 $+$ 单点修改，考虑树状数组。

在代码中注意每次折叠下标均会改变。

## Code


```cpp
#include <iostream>

using namespace std;

const int N = 1e5 + 5;

int n, m, hst = 1, f = 0, sum[N];
// hst 为起点，f 代表区间是否翻转

int ID(int x) {
// 查询 x 此时的下标
  x = x - 1;
  if (f == 0) { 
    return hst + x;
  }
  return hst - x;
}

int lowbit(int x) {
  return x & -x;
}

void add(int x, int k) {
  while (x <= n) {
    sum[x] += k;
    x += lowbit(x);
  }
}

int query(int x) {
  int res = 0;
  while (x > 0) {
    res += sum[x];
    x -= lowbit(x);
  }
  return res;
}

void read(int &a) {
// 快读
  a = 0;
  int f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    a = (a << 1) + (a << 3) + (ch ^ 48);
    ch = getchar();
  }
}

void write(int x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x >= 10) {
    write(x / 10);
  }
  putchar(x % 10 + '0');
}

int main() {
  read(n), read(m);
  int mm = n;
  // 纸条此时的长度 
  for (int i = 1; i <= n; ++ i) {
    add(i, 1);
  }
  for (int i = 1; i <= m; ++ i) {
    int op, l, r;
    read(op), read(l);
    if (op == 1) {
      if (l <= mm / 2) {
        for (int i = 1; i <= l; ++ i) {
          add(ID(l + i), (f == 0 ? query(ID(l - i + 1)) - query(ID(l - i + 1 - 1)) : query(ID(l - i + 1)) - query(ID(l - i + 1 + 1))));
          // 暴力将原纸条的贡献转移至折叠后的纸条下标
        }
        hst = ID(l + 1), mm = mm - l;
      } else {
        for (int i = 1; i <= mm - l; ++ i) {
          add(ID(l - i + 1), (f == 0 ? query(ID(l + i)) - query(ID(l + i - 1)) : query(ID(l + i)) - query(ID(l + i + 1))));
        }
        hst = ID(l), mm = l;
        f = !f;
        // 将整个区间翻转
      }
    } else if (op == 2) {
      read(r);
      ++ l;
      // 询问不包括 l
      write(f == 0 ? query(ID(r)) - query(ID(l - 1)) : query(ID(l)) - query(ID(r + 1)));
      // 询问区间
      puts("");
    }
  }
  return 0;
}
```

这道题将树状数组套成线段树的话也行，但也许会比树状数组慢一点。

---

