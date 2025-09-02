# 题目信息

# Restore the Permutation

## 题目描述

A sequence of $ n $ numbers is called permutation if it contains all numbers from $ 1 $ to $ n $ exactly once. For example, the sequences \[ $ 3, 1, 4, 2 $ \], \[ $ 1 $ \] and \[ $ 2,1 $ \] are permutations, but \[ $ 1,2,1 $ \], \[ $ 0,1 $ \] and \[ $ 1,3,4 $ \] — are not.

For a permutation $ p $ of even length $ n $ you can make an array $ b $ of length $ \frac{n}{2} $ such that:

- $ b_i = \max(p_{2i - 1}, p_{2i}) $ for $ 1 \le i \le \frac{n}{2} $

For example, if $ p $ = \[ $ 2, 4, 3, 1, 5, 6 $ \], then:

- $ b_1 = \max(p_1, p_2) = \max(2, 4) = 4 $
- $ b_2 = \max(p_3, p_4) = \max(3,1)=3 $
- $ b_3 = \max(p_5, p_6) = \max(5,6) = 6 $

 As a result, we made $ b $ = $ [4, 3, 6] $ .For a given array $ b $ , find the lexicographically minimal permutation $ p $ such that you can make the given array $ b $ from it.

If $ b $ = \[ $ 4,3,6 $ \], then the lexicographically minimal permutation from which it can be made is $ p $ = \[ $ 1,4,2,3,5,6 $ \], since:

- $ b_1 = \max(p_1, p_2) = \max(1, 4) = 4 $
- $ b_2 = \max(p_3, p_4) = \max(2, 3) = 3 $
- $ b_3 = \max(p_5, p_6) = \max(5, 6) = 6 $

A permutation $ x_1, x_2, \dots, x_n $ is lexicographically smaller than a permutation $ y_1, y_2 \dots, y_n $ if and only if there exists such $ i $ ( $ 1 \le i \le n $ ) that $ x_1=y_1, x_2=y_2, \dots, x_{i-1}=y_{i-1} $ and $ x_i<y_i $ .

## 说明/提示

The first test case is parsed in the problem statement.

## 样例 #1

### 输入

```
6
6
4 3 6
4
2 4
8
8 7 2 3
6
6 4 2
4
4 4
8
8 7 4 5```

### 输出

```
1 4 2 3 5 6 
1 2 3 4 
-1
5 6 3 4 1 2 
-1
1 8 6 7 2 4 3 5```

# AI分析结果

### 题目翻译
#### 恢复排列

### 题目描述
一个包含 $n$ 个数字的序列，如果它恰好包含从 $1$ 到 $n$ 的所有数字各一次，那么这个序列就被称为排列。例如，序列 \[ $ 3, 1, 4, 2 $ \]、\[ $ 1 $ \] 和 \[ $ 2,1 $ \] 是排列，但 \[ $ 1,2,1 $ \]、\[ $ 0,1 $ \] 和 \[ $ 1,3,4 $ \] 不是。

对于一个长度为偶数 $n$ 的排列 $p$，你可以构造一个长度为 $\frac{n}{2}$ 的数组 $b$，使得：
- 当 $1 \le i \le \frac{n}{2}$ 时，$b_i = \max(p_{2i - 1}, p_{2i})$ 

例如，如果 $p$ = \[ $ 2, 4, 3, 1, 5, 6 $ \]，那么：
- $b_1 = \max(p_1, p_2) = \max(2, 4) = 4$
- $b_2 = \max(p_3, p_4) = \max(3,1)=3$
- $b_3 = \max(p_5, p_6) = \max(5,6) = 6$

结果，我们得到 $b$ = $ [4, 3, 6] $ 。给定一个数组 $b$，请找出字典序最小的排列 $p$，使得可以从 $p$ 构造出给定的数组 $b$。

如果 $b$ = \[ $ 4,3,6 $ \]，那么能构造出它的字典序最小的排列是 $p$ = \[ $ 1,4,2,3,5,6 $ \]，因为：
- $b_1 = \max(p_1, p_2) = \max(1, 4) = 4$
- $b_2 = \max(p_3, p_4) = \max(2, 3) = 3$
- $b_3 = \max(p_5, p_6) = \max(5, 6) = 6$

如果且仅当存在一个 $i$（$ 1 \le i \le n $），使得 $x_1=y_1, x_2=y_2, \dots, x_{i-1}=y_{i-1}$ 且 $x_i<y_i$，那么排列 $x_1, x_2, \dots, x_n$ 的字典序小于排列 $y_1, y_2 \dots, y_n$。

### 说明/提示
第一个测试用例在题目描述中已经解析过。

### 样例 #1
#### 输入
```
6
6
4 3 6
4
2 4
8
8 7 2 3
6
6 4 2
4
4 4
8
8 7 4 5
```
#### 输出
```
1 4 2 3 5 6 
1 2 3 4 
-1
5 6 3 4 1 2 
-1
1 8 6 7 2 4 3 5
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，通过合理的贪心策略来构造满足条件的最小字典序排列。各题解的主要区别在于实现细节和数据结构的选择，如使用 `set`、`vector`、堆、线段树等。难点在于如何证明贪心策略的正确性以及处理无解的情况。

### 所选题解
- **作者：honglan0301 (赞：4)，4星**
    - **关键亮点**：思路清晰，对贪心策略的正确性进行了详细证明，代码实现使用 `set` 数据结构，简单易懂。
    - **个人心得**：无

### 重点代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int t,n,b[100005],c[100005];
set <int> s;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        s.clear();
        bool flag=0;
        for(int i=1;i<=n;i++)
        {
            s.insert(i);
        }
        for(int i=1;i<=n/2;i++)
        {
            cin>>b[i];
            if(s.find(b[i])==s.end())//特判无解 
            {
                flag=1;
            }
            s.erase(b[i]);
        }
        if(flag)
        {
            cout<<"-1"<<endl;
            continue;
        }
        for(int i=n/2;i>=1;i--)
        {
            auto it=s.upper_bound(b[i]);
            if(it==s.begin())//特判无解 
            {
                flag=1;
                break;
            }
            it--;
            c[i]=*it;
            s.erase(c[i]);
        }
        if(flag)
        {
            cout<<"-1"<<endl;
            continue;
        }
        for(int i=1;i<=n/2;i++)
        {
            cout<<c[i]<<" "<<b[i]<<" ";
        }
        cout<<endl;
    }
}
```
**核心实现思想**：
1. 首先将 $1$ 到 $n$ 的所有数字插入 `set` 中。
2. 读取 $b$ 数组，检查 $b$ 数组中的元素是否在 `set` 中，如果不在则无解。
3. 从后往前遍历 $b$ 数组，对于每个 $b_i$，在 `set` 中找到小于 $b_i$ 的最大元素作为 $p_{2i - 1}$，并从 `set` 中删除该元素。
4. 如果找不到小于 $b_i$ 的元素，则无解。
5. 最后输出构造的排列 $p$。

### 关键思路或技巧
- **贪心策略**：从后往前，贪心地选取能用的最大元素，保证字典序最小。
- **数据结构**：使用 `set` 可以方便地进行元素的查找和删除操作，并且可以利用 `upper_bound` 函数快速找到小于某个值的最大元素。

### 拓展思路
同类型题或类似算法套路：
- 其他涉及字典序最小的构造问题，通常可以考虑贪心算法，从后往前或从前往后进行构造。
- 涉及排列和组合的问题，需要注意元素的唯一性和顺序。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：贪心算法的经典题目，通过每次合并最小的两堆果子来使总代价最小。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心算法，按照接水时间从小到大排序，使所有人的等待时间总和最小。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：贪心算法，通过合理的排序策略来使最终结果最优。

---
处理用时：46.98秒