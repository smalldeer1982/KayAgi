# [GCJ 2020 #1A] Pascal Walk

## 题目描述

**帕斯卡三角形** 由无限多行整数构成，每行的整数数量逐行递增，排列成三角形。

定义 $(r, k)$ 为第 $r$ 行从左数第 $k$ 个位置，其中 $r$ 和 $k$ 均从 1 开始计数。帕斯卡三角形的构造遵循以下规则：

- 第 $r$ 行包含 $r$ 个位置 $(r, 1), (r, 2), \ldots, (r, r)$。
- 对于所有 $r$，位置 $(r, 1)$ 和 $(r, r)$ 的数字均为 $1$。
- 对于所有满足 $2 \leqslant k \leqslant r-1$ 的 $k$，位置 $(r, k)$ 的数字等于位置 $(r-1, k-1)$ 和 $(r-1, k)$ 的数字之和。

帕斯卡三角形的前 5 行如下所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/6s8m35j7.png)

在本问题中，**帕斯卡游走** 是指帕斯卡三角形中一个长度为 $\mathrm{s}$ 的位置序列 $\left(\mathrm{r}_{1}, \mathrm{k}_{1}\right), \left(\mathrm{r}_{2}, \mathrm{k}_{2}\right), \ldots, \left(\mathrm{r}_{\mathrm{s}}, \mathrm{k}_{\mathrm{s}}\right)$，满足以下条件：

1. $\mathrm{r}_{1}=1$ 且 $\mathrm{k}_{1}=1$。
2. 每个后续位置必须在三角形内，并且与前一个位置相邻（六个可能方向之一）。即对于所有 $\mathrm{i} \geqslant 1$，$\left(\mathrm{r}_{\mathrm{i}+1}, \mathrm{k}_{\mathrm{i}+1}\right)$ 必须是以下之一且位于三角形内：$\left(\mathrm{r}_{\mathrm{i}}-1, \mathrm{k}_{\mathrm{i}}-1\right)$、$\left(\mathrm{r}_{\mathrm{i}}-1, \mathrm{k}_{\mathrm{i}}\right)$、$\left(\mathrm{r}_{\mathrm{i}}, \mathrm{k}_{\mathrm{i}}-1\right)$、$\left(\mathrm{r}_{\mathrm{i}}, \mathrm{k}_{\mathrm{i}}+1\right)$、$\left(\mathrm{r}_{\mathrm{i}}+1, \mathrm{k}_{\mathrm{i}}\right)$、$\left(\mathrm{r}_{\mathrm{i}}+1, \mathrm{k}_{\mathrm{i}}+1\right)$。
3. 序列中不能重复访问同一位置。即对于任意 $\mathrm{i} \neq \mathrm{j}$，必须满足 $\mathrm{r}_{\mathrm{i}} \neq \mathrm{r}_{\mathrm{j}}$ 或 $\mathrm{k}_{\mathrm{i}} \neq \mathrm{k}_{\mathrm{j}}$，或两者均不相等。

请构造一个长度 $\mathrm{S} \leqslant 500$ 的帕斯卡游走，使得所访问位置中所有数字之和恰好等于 $\mathrm{N}$。题目保证对于所有 $\mathrm{N}$，至少存在一个这样的游走。

## 说明/提示


## 说明/提示

**样例解释**

- 样例 #1 仅需起点位置即可满足要求。

![](https://cdn.luogu.com.cn/upload/image_hosting/06jwicgw.png)

- 样例 #2 中，虽然存在更短的路径，但路径长度只需不超过 500 即可，无需最短。

![](https://cdn.luogu.com.cn/upload/image_hosting/scfogipe.png)

- 下图展示了样例 #3 的解决方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/x6b2j5as.png)

**数据范围**

- $1 \leqslant \mathrm{T} \leqslant 100$。

**测试集 1（3 分，可见评测结果）**

- $1 \leqslant \mathrm{N} \leqslant 501$。

**测试集 2（11 分，可见评测结果）**

- $1 \leqslant \mathrm{N} \leqslant 1000$。

**测试集 3（21 分，隐藏评测结果）**

- $1 \leqslant \mathrm{N} \leqslant 10^{9}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
1
4
19```

### 输出

```
Case #1:
1 1
Case #2:
1 1
2 1
2 2
3 3
Case #3:
1 1
2 2
3 2
4 3
5 3
5 2
4 1
3 1```

# 题解

## 作者：tuboshu666 (赞：0)

## 思路：
观察帕斯卡三角形，不难发现：第 $r$ 行数的和为 $2^{r-1}$。于是想到，能不能通过类似二进制拆分的方法，凑出所有整数。由于 $2^{30}$ 就已大于 $10^{9}$，因此只需要考虑到第 $30$ 位。

本题难点在于：要想到达二进制对应行，难免会经过中间行，可能会得到一些多余的 $1$。既然多出的这些 $1$ 无法被消除，考虑一开始就缺少 $30$ 个 $1$，视情况补上少的 $1$。

若 $n$ $\leq$ $30$，直接沿边缘走完即可。否则，将 $n-30$ 进行二进制拆分，踩完其二进制位中 $1$ 位对应行的所有数，其余行只从边缘经过。该策略仍会得到多余的 $1$，记作 $cnt$ 个。此时得到的数为 $n-30+cnt$。最后只需要再补 $30-cnt$ 个 $1$ 就行。

## Code：

```cpp
#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

typedef bitset<50> bt;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    for (int i = 1 ; i <= T ; i++)
    {
        cout << "Case #" << i << ":" << endl;
        int n;
        cin >> n;
        if (n <= 30)
        {
            for (int j = 1 ; j <= n ; j++)
            {
                cout << j << " " << 1 << endl;
            }
        }
        else
        {
            //懒得手动拆分二进制，直接使用bitset
            bt bit = bt(n-30);
            bool flag = false; //0代表左,1代表右
            vector<int> vec;
            for (int j = 0 ; j <= 30 ; j++)
            {
                if (bit[j]) vec.push_back(j); //将n-30每个1的位置存起来
            }

            int pos = 0; //当前在第几行
            int cnt = 0; //多踩的1的个数
            for (int j = 0 ; j < vec.size() ; j++)
            {
                for (int k = pos+1 ; k <= vec[j] ; k++)
                {
                    cnt++;
                    if (!flag) cout << k << " " << 1 << endl;
                    else cout << k << " " << k << endl;
                }

                if (!flag)
                {
                    for (int k = 1 ; k <= vec[j]+1 ; k++)
                    {
                        cout << vec[j]+1 << " " << k << endl;
                    }
                }
                else
                {
                    for (int k = vec[j]+1 ; k >= 1 ; k--)
                    {
                        cout << vec[j]+1 << " " << k << endl;
                    }
                }

                flag = !flag;
                pos = vec[j]+1;
            }

            for (int j = 1 ; j <= 30-cnt ; j++)
            {
                if (!flag) cout << ++pos << " " << 1 << endl;
                else cout << ++pos << " " << pos << endl;
            }
        }
    }

    return 0;
}
```

---

