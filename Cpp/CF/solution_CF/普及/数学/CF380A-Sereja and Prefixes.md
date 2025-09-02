# Sereja and Prefixes

## 题目描述

Sereja loves number sequences very much. That's why he decided to make himself a new one following a certain algorithm.

Sereja takes a blank piece of paper. Then he starts writing out the sequence in $ m $ stages. Each time he either adds a new number to the end of the sequence or takes $ l $ first elements of the current sequence and adds them $ c $ times to the end. More formally, if we represent the current sequence as $ a_{1},a_{2},...,a_{n} $ , then after we apply the described operation, the sequence transforms into $ a_{1},a_{2},...,a_{n}[,a_{1},a_{2},...,a_{l}] $ (the block in the square brackets must be repeated $ c $ times).

A day has passed and Sereja has completed the sequence. He wonders what are the values of some of its elements. Help Sereja.

## 样例 #1

### 输入

```
6
1 1
1 2
2 2 1
1 3
2 5 2
1 4
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
```

### 输出

```
1 2 1 2 3 1 2 1 2 3 1 2 1 2 3 4
```

# 题解

## 作者：qjxqjx (赞：2)

## 题目大意：
现维护一个初始全部为空的序列，可支持两种操作，共 m 个：  
1.将一个数插入到数列的尾端（插入的数不大于 $10^5$）  
2.将数列的前 l 位复制 c 次，贴到数列的尾端 （$1\le l\le$ $10 ^ 5$, $1\le$ c $\le$ $10 ^ 4$）

然后进行 n  次查询，每次给出一个数 x ，输出最终数列的第 x 位（所有查询数满足严格递增）。

题目满足数据合法。

## 题目思路：
这道题数据规模很大，直接模拟不仅会超时，而且会爆内存(最多大概可以有 $10^9$ 个数)，所以我们着手去想其他的解题思路。

思路：$\boxed{\color{red}\textbf{二分}}$

处理出每一个操作所生成的数列的位置，然后按照查询给出的位置 x 在操作序列中****二分查找****出生成包含 x 这一段的操作的位置，根据这个操作去计算位置 x 上的值。  
但是这样要考虑到一件事，如果生成 x 的操作是操作 2 ， 那么由于操作 2 是复制当前的数列的前 l 个数，而当前数列仍旧是未知的，也就是说我们还是需要再在前面的操作中二分，知道查到一个由操作一生成的点。这个代码对代码能力有比较大的要求，建议初学者先别看这题。

我们从范围入手，注意到操作二只会用到当前数列的前 $10^5$ 个点，然而数列中的点是不会修改的，所以我们有了这种想法：

模拟出数列的前 $10^5$ 个点，然后再查找生成 x 的对应操作。

模拟之后的查找有两种方案，第一种还是二分，时间复杂度不是太大（能过），但是写起来稍微有点麻烦。第二种方法用到了题目中查询序列的递增顺序，直接线性地从先往后扫就行，这个的时间复杂度就是 $O(n+m)$。


但是，****要注意****：  
1.注意边界条件和循环退出条件。  
2.如果当前查到的点的位置小于 $10^5$ 直接输出模拟出来的数列中的对应位置值就可以了。  
3.如果查到的位置对应操作为操作 1，就直接输出操作一的操作数值，如果为操作二需要计算一下取模，特别注意取模得零的情况。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxm = 100005;
inline int getint(){
    int ans(0); char w = getchar();
    while('0' > w || w > '9')w = getchar();
    while('0' <= w && w <= '9')
    {
        ans = ans * 10 + w - '0';
        w = getchar();
    }
    return ans;
}
int n, m;
struct build{
    int ord, x, l, c;
    long long a, b;
}hell[maxm];
int sq[maxm];
int main(){
    m = getint();
    for(int i = 1; i <= m; ++i){
        hell[i].ord = getint();
        if(hell[i].ord == 1){
            hell[i].x = getint();
            hell[i].a = hell[i].b = hell[i - 1].b + 1LL;
            if(hell[i].a < maxm)sq[hell[i].a] = hell[i].x;
        }
        else{
            hell[i].l = getint(); hell[i].c = getint();
            hell[i].a = hell[i - 1].b + 1LL;
            hell[i].b = hell[i - 1].b + (long long)hell[i].l * (long long)hell[i].c;
            if(hell[i].a < maxm)
            {
                int now = hell[i].a;
                for(int j = 1; j <= hell[i].c && now < maxm; ++j)
                    for(int k = 1; k <= hell[i].l && now < maxm; ++k)
                        sq[now++] = sq[k];
            }
        }
    }

    n = getint();
    int h = 1; long long x;
    for(int i = 1; i <= n; ++i){
        cin >> x;
        while(!(hell[h].a <= x && hell[h].b >= x))++h;
        if(x <= 100000)printf("%d ", sq[x]);
        else{
            if((x - hell[h - 1].b) % (long long)hell[h].l != 0)
                cout << sq[(x - hell[h - 1].b) % (long long)hell[h].l] << ' ';
            else cout << sq[hell[h].l] << ' ';
        }
    }
    return 0;
}
```

---

