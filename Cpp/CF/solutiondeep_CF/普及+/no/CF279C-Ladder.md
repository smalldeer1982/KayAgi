# 题目信息

# Ladder

## 题目描述

You've got an array, consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Also, you've got $ m $ queries, the $ i $ -th query is described by two integers $ l_{i},r_{i} $ . Numbers $ l_{i},r_{i} $ define a subsegment of the original array, that is, the sequence of numbers $ a_{li},a_{li}+1,a_{li}+2,...,a_{ri} $ . For each query you should check whether the corresponding segment is a ladder.

A ladder is a sequence of integers $ b_{1},b_{2},...,b_{k} $ , such that it first doesn't decrease, then doesn't increase. In other words, there is such integer $ x $ $ (1<=x<=k) $ , that the following inequation fulfills: $ b_{1}<=b_{2}<=...<=b_{x}>=b_{x+1}>=b_{x+2}...>=b_{k} $ . Note that the non-decreasing and the non-increasing sequences are also considered ladders.

## 样例 #1

### 输入

```
8 6
1 2 1 3 3 5 2 1
1 3
2 3
2 4
8 8
1 4
5 8
```

### 输出

```
Yes
Yes
No
Yes
No
Yes
```

# AI分析结果

### 题目内容
# 梯子

## 题目描述
你有一个由 $n$ 个整数 $a_{1},a_{2},\cdots,a_{n}$ 组成的数组。同时，你有 $m$ 个查询，第 $i$ 个查询由两个整数 $l_{i},r_{i}$ 描述。数字 $l_{i},r_{i}$ 定义了原始数组的一个子段，即数字序列 $a_{l_{i}},a_{l_{i}+1},a_{l_{i}+2},\cdots,a_{r_{i}}$ 。对于每个查询，你应该检查相应的段是否是一个梯子。

一个梯子是一个整数序列 $b_{1},b_{2},\cdots,b_{k}$ ，使得它首先不递减，然后不递增。换句话说，存在这样一个整数 $x$ （$1\leq x\leq k$），使得以下不等式成立：$b_{1}\leq b_{2}\leq\cdots\leq b_{x}\geq b_{x + 1}\geq b_{x + 2}\cdots\geq b_{k}$ 。注意，非递减和非递增序列也被认为是梯子。

## 样例 #1
### 输入
```
8 6
1 2 1 3 3 5 2 1
1 3
2 3
2 4
8 8
1 4
5 8
```
### 输出
```
Yes
Yes
No
Yes
No
Yes
```

### 算法分类
无算法分类

### 题解综合分析与结论
这些题解主要围绕判断给定区间是否为“梯子”形状展开，思路和方法各有不同。部分题解通过预处理数组信息，如左右连续大于等于自身值的数量，来快速判断区间是否满足条件；部分使用线段树、ST表等数据结构来查询区间最大值位置等信息辅助判断；还有通过莫队算法来处理询问。整体来看，不同题解在时间复杂度、空间复杂度和代码实现难度上有所差异。

### 所选的题解
 - **作者：wxzzzz（5星）**
    - **关键亮点**：思路简洁高效，通过预处理记录每个位置左边和右边连续大于等于自身值的个数，然后根据左右两边的统计值之和与区间长度的关系快速判断区间是否为“梯子”，时间复杂度为 $O(n + q)$，代码实现简单清晰。
    - **重点代码核心实现思想**：先读入数据并初始化左右统计数组，然后两次遍历数组分别计算每个位置的左右连续大于等于自身值的个数，最后根据每次询问的区间左右端点的统计值之和与区间长度比较输出结果。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q, l, r, a[1000005], bl[1000005], br[1000005];
int main() {
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        cin >> a[i], bl[i] = 1, br[i] = 1;

    for (int i = 1; i <= n; i++)
        if (a[i] <= a[i - 1])
            bl[i] = bl[i - 1] + 1;

    for (int i = n; i >= 1; i--)
        if (a[i] <= a[i + 1])
            br[i] = br[i + 1] + 1;

    while (q--) {
        cin >> l >> r;

        if (br[l] + bl[r] >= r - l + 1)
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}
```
 - **作者：梧桐灯（4星）**
    - **关键亮点**：利用线段树或ST表查询区间最大值位置，同时通过双指针预处理以每个位置为起点的最长单调不降（升）区间终点，最后结合这两个预处理信息快速判断区间是否为“梯子”，方法较为巧妙。
    - **重点代码核心实现思想**：先读入数据，通过双指针预处理单调区间终点数组，再用ST表预处理区间最大值位置，然后根据每次询问的区间计算最大值位置，结合单调区间信息判断并输出结果。
```cpp
#include <cstdio>
#define Max(p,q) a[p] > a[q]? p : q;
using namespace std;

template <typename T>
inline void read (T& s) {
    s = 0;
    static char c = getchar ();
    while (c < '0' || c > '9') c = getchar ();
    while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar ();
    return ;
}

const int N = 100003;
int n, Q, a[N], mu [N], md[N];
int mx[17][N], lg[N];

int main () {
    read (n), read (Q);
    int i, j; for (i = 1; i <= n; ++i) read (a[i]), mx[0][i] = i;
    j = 1;
    for (i = 1; i <= n; ++i) {
        if (j < i) j = i;
        while (j < n && a[j] <= a[j + 1]) ++j;
        mu[i] = j;
    } //双指针预处理单调不降
    j = 1;
    for (i = 1; i <= n; ++i) {
        if (j < i) j = i;
        while (j < n && a[j] >= a[j + 1]) ++j;
        md[i] = j;
    }
    for (j = 1; j < 17; ++j) {
        const int p = (1 << j) - 1;
        for (i = 1; i + p <= n; ++i) mx[j][i] = Max (mx[j - 1][i], mx[j - 1][i + (1 << j - 1)]);
    } //st表预处理
    for (i = 1, j = 0; i <= n; ++i) {
        if (1 << j + 1 == i) ++j;
        lg[i] = j;
    } //预处理对数
    int x, y; while (Q--) {
        read (x), read (y);
        const int k = lg[y - x + 1], p = Max (mx[k][x], mx[k][y - (1 << k) + 1]);
        puts (mu[x] >= p && md[p] >= y? "Yes" : "No");
    } //O1输出答案
    return 0;
}
```
 - **作者：fish_love_cat（4星）**
    - **关键亮点**：与wxzzzz思路类似，同样是通过预处理每个位置左右连续大于等于自身值的数量，根据两者之和与区间长度的关系判断区间是否为“梯子”，代码简洁明了。
    - **重点代码核心实现思想**：读入数据并初始化数组，通过两次遍历数组计算每个位置左右连续大于等于自身值的个数，根据每次询问的区间信息比较并输出结果。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],l[100005],r[100005];
int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i],l[i]=1,r[i]=1;
        if(a[i]<=a[i-1])r[i]=r[i-1]+1;
    }
    for(int i=n;i>=1;i--)
    if(a[i]<=a[i+1])l[i]=l[i+1]+1;
    while(q--){int L,R;cin>>L>>R;
        puts((l[L]+r[R]>=R-L+1?"Yes":"No"));
    }
    return 0;
}
```

### 最优关键思路或技巧
预处理每个位置左右连续大于等于自身值的数量这种方法较为高效，通过简单的两次遍历数组即可完成预处理，然后每次询问时只需 $O(1)$ 的时间复杂度判断，整体时间复杂度为 $O(n + q)$，相比使用线段树、莫队算法等方法，代码实现简单且效率较高。

### 可拓展思路
此类题目属于区间性质判断问题，类似的套路可以应用在判断区间单调性、区间最值分布等问题上。例如可以拓展到判断区间是否为严格单峰、是否存在多个峰值等问题，解决方法可能依然是通过预处理数组信息，结合合适的数据结构来快速查询和判断。

### 推荐题目
 - [P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)：通过ST表解决区间最值查询问题，与本题中梧桐灯题解里使用ST表查询区间最大值位置类似。
 - [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)：同样涉及区间最值问题，可以练习使用不同方法（如线段树、单调队列等）来解决。
 - [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)：利用单调队列解决滑动窗口内的最值问题，对于理解区间性质判断和数据结构优化有帮助。

### 个人心得摘录与总结
无。 

---
处理用时：82.55秒