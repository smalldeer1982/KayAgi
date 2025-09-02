# Dirty Deeds Done Dirt Cheap

## 题目描述

有 $n$ 个整数对 $(a_1, b_1), (a_2, b_2), \cdots, (a_n, b_n)$. 保证 $a_1, b_1, a_2, b_2, \cdots, a_n, b_n$ 两两不相等, 并且均在区间 $[1, 2 \cdot n]$ 内.

好序列的定义:  
对于一个序列 $x_1, x_2, \cdots, x_{2k}$, 满足
- $x_1 < x_2 > x_3 < \cdots < x_{2k - 2} > x_{2k - 1} < x_{2k}$ 或
- $x_1 > x_2 < x_3 > \cdots > x_{2k - 2} < x_{2k - 1} > x_{2k}$.

求一个序列 $i_1, i_2, \cdots, i_t$ 满足 $a_{i_1}, b_{i_1}, a_{i_2}, b_{i_2}, \cdots, a_{i_t}, b_{i_t}$ 是好序列.

输出 $t$ 的最大值以及对应的序列 $i_1, i_2, \cdots, i_t$.

## 说明/提示

$2 \leq n \leq 3 \cdot 10^5$  
$1 \leq a_i, b_i \leq 2 \cdot n$  
并且所有 $a_i, b_i$ 两两不相等.

### 样例解释
样例 1: $1 < 7 > 3 < 5 > 2 < 10$.

样例 2: $6 > 1 < 3 > 2 < 5 > 4$.

## 样例 #1

### 输入

```
5
1 7
6 4
2 10
9 8
3 5
```

### 输出

```
3
1 5 3
```

## 样例 #2

### 输入

```
3
5 4
3 2
6 1
```

### 输出

```
3
3 2 1
```

# 题解

## 作者：mraymes (赞：4)

也许是我做过的最水的 D 题之一吧.

## 题意
有 $n$ 个整数对 $(a_1, b_1), (a_2, b_2), \cdots, (a_n, b_n)$. 保证 $a_1, b_1, a_2, b_2, \cdots, a_n, b_n$ 两两不相等, 并且均在区间 $[1, 2 \cdot n]$ 中.

好序列的定义:  
对于一个序列 $x_1, x_2, \cdots, x_{2k}$, 满足
- $x_1 < x_2 > x_3 < \cdots < x_{2k - 2} > x_{2k - 1} < x_{2k}$ 或
- $x_1 > x_2 < x_3 > \cdots > x_{2k - 2} < x_{2k - 1} > x_{2k}$.

求一个序列 $i_1, i_2, \cdots, i_t$ 满足 $a_{i_1}, b_{i_1}, a_{i_2}, b_{i_2}, \cdots, a_{i_t}, b_{i_t}$ 是好序列.

输出 $t$ 的最大值以及对应的序列 $i_1, i_2, \cdots, i_t$.

## 解法
首先可以发现, 对于在 $[1, n]$ 区间内的每一个整数 $j$, 都满足 $a_{i_{2j - 1}} < b_{i_{2j}}$ 或者 $a_{i_{2j - 1}} > b_{i_{2j}}$. 因此被选出的下标对应的数对**都满足**第一个数比第二个数小或者大.

因此, 我们就将题目给出的数对分成两类, 第一类满足第一个数比第二个数小, 第二类满足第一个数比第二个数大.

### 对于第一类

当 $b_{i_1} > b_{i_2} > \cdots > b_{i_t}$ 时  
满足 $b_{i_j} > a_{i_{j + 1}} < b_{i_{j + 1}}$  
所以必然满足 $a_{i_1} < b_{i_1} > a_{i_2} < b_{i_2} > \cdots > a_{i_t} < b_{i_t}$.

因此当我们将第一类中的所有数对按第二个数从大到小排序, 顺次连接得到的必然是个好序列.

### 对于第二类

当 $b_{i_1} < b_{i_2} < \cdots < b_{i_t}$ 时  
满足 $b_{i_j} < a_{i_{j + 1}} > b_{i_{j + 1}}$  
所以必然满足 $a_{i_1} > b_{i_1} < a_{i_2} > b_{i_2} < \cdots < a_{i_t} > b_{i_t}$.

因此当我们将第二类中的所有数对按第二个数从小到大排序, 顺次连接得到的必然是个好序列.

所以我们挑选两类中数对更多的一类, 进行上述处理之后即可.

因为最后输出的是原下标, 所以排序的时候要带上原下标一起排序.

具体见代码:
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> ppi;

int n;

// 存放在 pair<pair<int, int>, int> 中更方便排序 (不用手写 comp)
ppi a[300001], b[300001]; // 两类数对

int n1 = 0, n2 = 0;

template <typename T>
inline T read() {
    T x = 0;
    T multiplier = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            multiplier = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * multiplier;
}

int main() {
    n = read<int>();
    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
        if (x < y) {        // 第一个数更小, 归为第一类
            // 按第二个数排序, 因此反着存放, 下同
            a[++n1] = ppi(pii(y, x), i);
        } else if (x > y) { // 否则归为第二类
            b[++n2] = ppi(pii(y, x), i);
        }
    }

    if (n1 >= n2) { // 选第一类
        sort(a + 1, a + n1 + 1, greater<ppi>()); // 从大到小排序
        printf("%d\n", n1);
        for (int i = 1; i <= n1; i++) {
            cout << a[i].second << ' ';
        }
    } else { // 选第二类
        sort(b + 1, b + n2 + 1); // 从小到大排序 (默认排序)
        printf("%d\n", n2);
        for (int i = 1; i <= n2; i++) {
            cout << b[i].second << ' ';
        }
    }
    puts("");

    return 0;
}

```


---

## 作者：LYY_yyyy (赞：0)

首先，$a<b$ 和 $a>b$ 的二元组显然不能同时选，于是我们分开考虑。对于 $a<b$ 的情况，我们考虑按照 $b$ 从大到小排序顺次相接，显然有 $a_{i+1}<b_{i+1}<b_i$，即可将所有 $a<b$ 的二元组全部放入构造中。$a>b$ 类似，按照 $a$ 从小到大排序即可。之后将二元组个数更多的情况输出即可。

代码：
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define pb emplace_back
using namespace std;
int n;
struct node
{
	int a,b,id;
};
vector<node> s1,s2;
inline bool cmp1(node a,node b)
{
	return a.b>b.b;
}
inline bool cmp2(node a,node b)
{
	return a.a<b.a;
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a,b;cin>>a>>b;
		if(a<b) s1.pb((node){a,b,i});
		else s2.pb((node){a,b,i});
	}
	sort(s1.begin(),s1.end(),cmp1);
	sort(s2.begin(),s2.end(),cmp2);
	if(s1.size()<s2.size()) swap(s1,s2);
	cout<<s1.size()<<"\n";
	for(auto o:s1) cout<<o.id<<" ";
	return 0;
}
```

---

