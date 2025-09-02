# [NERC 2020] Digits

## 题目描述

Diana 喜欢玩数字游戏。她有 $n$ 张卡片，每张卡片上写着一个正整数 $a_i$。她闲暇时会挑选一些卡片，将这些卡片上的数字相乘。

当这些数字的乘积以她最喜欢的数字 $d$ 结尾时，Diana 就会很开心。现在她想知道，应该如何选择卡片才能使得这些数字的乘积尽可能大，并且乘积的十进制表示最后一位是 $d$。请你帮帮她。


## 说明/提示

在第一个样例中，$1 \times 2 \times 4 \times 11 \times 13 = 1144$，这是以数字 4 结尾的最大乘积。不包含数字 1 的相同卡片组合也是有效答案，包含 8、11 和 13 的组合（无论是否包含 1）同样可以得到乘积 1144。

在第二个样例中，所有卡片上的数字都是偶数，它们的乘积不可能以奇数 1 结尾。

在第三个样例中，所有可能的乘积为 1、3、5、9、15 和 45，它们均不以数字 7 结尾。

在第四个样例中，$9 \times 11 \times 17 = 1683$，其最后一位是 3。

在第五个样例中，$2 \times 2 \times 2 \times 2 = 16$，其最后一位是 6。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6 4
4 11 8 2 1 13```

### 输出

```
5
1 2 4 11 13```

## 样例 #2

### 输入

```
3 1
2 4 6```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 7
1 3 1 5 3```

### 输出

```
-1```

## 样例 #4

### 输入

```
6 3
8 9 4 17 11 5```

### 输出

```
3
9 11 17```

## 样例 #5

### 输入

```
5 6
2 2 2 2 2```

### 输出

```
4
2 2 2 2```

# 题解

## 作者：liuchuliang666 (赞：0)

看到这题的时候，一下子想起了之前听到过的一句话：

> 遇到大数字比较，取模会丢失大小信息，这时可以存储数的对数辅助比较。

这题不是为这个技巧量身定制的吗？

我们记 $f_{i, d}$ 为 $1 \sim i - 1$ 中选若干个数相乘，末位为 $d$ 的最大数的对数（我这里以 $2$ 为底），考虑使用刷表法（从当前状态向后转移到下一状态）进行递推，那么有：

$$f_{i + 1, d \times a_i \text{mod} 10} \leftarrow f_{i, d} + \log_2a_i$$

本题恶心的一点是要输出具体方案，细节有点多，具体看代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int ll
typedef long long ll;
typedef const int cint;
typedef vector<int> vi;
constexpr int MAXN = 1e5 + 10;
// pos, posd：f[i][d] 的决策点
int n, D, a[MAXN], pos[MAXN][10], posd[MAXN][10];
double lga[MAXN], f[MAXN][10];
void printans()
{
    vi ans;
    int p = pos[n + 1][D], d = posd[n + 1][D];
    while(p)
    {
        ans.emplace_back(a[p]);
        cint np = pos[p][d], nd = posd[p][d];
        p = np, d = nd;
    }
    if (ans.empty()) cout << -1, exit(0);
    cout << ans.size() << endl;
    for (cint x : ans) cout << x << " ";
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> D;
    for (int i = 1; i <= n; i++) cin >> a[i], lga[i] = log2(a[i]);
    for (int i = 1; i <= n; i++)
    {
        cint ad = a[i] % 10;
        copy(f[i], f[i] + 10, f[i + 1]);
        copy(pos[i], pos[i] + 10, pos[i + 1]);
        copy(posd[i], posd[i] + 10, posd[i + 1]);
        for (int d = 0; d < 10; d++)
        {
            // 如果上一状态为空，那么认为只有这个数本身
            cint nd = f[i][d] ? d * ad % 10 : ad;
            if (f[i + 1][nd] <= f[i][d] + lga[i])
            {
                if (f[i][d])
                    f[i + 1][nd] = f[i][d] + lga[i], pos[i + 1][nd] = i, posd[i + 1][nd] = d;
                else
                    f[i + 1][nd] = lga[i], pos[i + 1][nd] = i, posd[i + 1][nd] = 1;
            }
        }
    }
    printans();
    return 0;
}
```

实现参考了 [这里](https://blog.csdn.net/qq_45812711/article/details/115458266) 的题解，属于比较简单的写法。

---

