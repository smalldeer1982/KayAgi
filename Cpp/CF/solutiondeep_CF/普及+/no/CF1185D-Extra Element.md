# 题目信息

# Extra Element

## 题目描述

A sequence $ a_1, a_2, \dots, a_k $ is called an arithmetic progression if for each $ i $ from $ 1 $ to $ k $ elements satisfy the condition $ a_i = a_1 + c \cdot (i - 1) $ for some fixed $ c $ .

For example, these five sequences are arithmetic progressions: $ [5, 7, 9, 11] $ , $ [101] $ , $ [101, 100, 99] $ , $ [13, 97] $ and $ [5, 5, 5, 5, 5] $ . And these four sequences aren't arithmetic progressions: $ [3, 1, 2] $ , $ [1, 2, 4, 8] $ , $ [1, -1, 1, -1] $ and $ [1, 2, 3, 3, 3] $ .

You are given a sequence of integers $ b_1, b_2, \dots, b_n $ . Find any index $ j $ ( $ 1 \le j \le n $ ), such that if you delete $ b_j $ from the sequence, you can reorder the remaining $ n-1 $ elements, so that you will get an arithmetic progression. If there is no such index, output the number -1.

## 说明/提示

Note to the first example. If you delete the $ 4 $ -th element, you can get the arithmetic progression $ [2, 4, 6, 8] $ .

Note to the second example. The original sequence is already arithmetic progression, so you can delete $ 1 $ -st or last element and you will get an arithmetical progression again.

## 样例 #1

### 输入

```
5
2 6 8 7 4
```

### 输出

```
4```

## 样例 #2

### 输入

```
8
1 2 3 4 5 6 7 8
```

### 输出

```
1```

## 样例 #3

### 输入

```
4
1 2 4 8
```

### 输出

```
-1```

# AI分析结果

### 题目内容中文重写
#### 额外元素

##### 题目描述
一个序列 $ a_1, a_2, \dots, a_k $ 被称为等差数列，当且仅当对于从 $ 1 $ 到 $ k $ 的每个 $ i $，元素都满足条件 $ a_i = a_1 + c \cdot (i - 1) $（其中 $ c $ 为某个固定的值）。

例如，以下五个序列是等差数列：$ [5, 7, 9, 11] $、$ [101] $、$ [101, 100, 99] $、$ [13, 97] $ 和 $ [5, 5, 5, 5, 5] $。而以下四个序列不是等差数列：$ [3, 1, 2] $、$ [1, 2, 4, 8] $、$ [1, -1, 1, -1] $ 和 $ [1, 2, 3, 3, 3] $。

给定一个整数序列 $ b_1, b_2, \dots, b_n $。找出任意一个索引 $ j $（$ 1 \le j \le n $），使得如果你从序列中删除 $ b_j $，然后对剩下的 $ n - 1 $ 个元素进行重新排序，能够得到一个等差数列。如果不存在这样的索引，则输出 $ -1 $。

##### 说明/提示
第一个样例的注释：如果你删除第 $ 4 $ 个元素，就可以得到等差数列 $ [2, 4, 6, 8] $。

第二个样例的注释：原始序列本身就是等差数列，所以你可以删除第一个或最后一个元素，仍然可以得到一个等差数列。

##### 样例 #1
###### 输入
```
5
2 6 8 7 4
```
###### 输出
```
4
```

##### 样例 #2
###### 输入
```
8
1 2 3 4 5 6 7 8
```
###### 输出
```
1
```

##### 样例 #3
###### 输入
```
4
1 2 4 8
```
###### 输出
```
-1
```

### 算法分类
排序、枚举

### 综合分析与结论
这些题解的核心思路大多是先对序列进行排序，然后通过枚举删除不同位置的元素，判断剩余元素能否构成等差数列。各题解的差异主要在于枚举的方式和判断等差数列的方法。

部分题解利用 `map` 或 `set` 记录相邻元素的差值，通过统计差值的出现次数来辅助判断；部分题解则是直接遍历序列，根据等差数列的性质进行判断。

### 所选题解
- **作者：DaiRuiChen007（4星）**
    - **关键亮点**：思路清晰，将情况分为删除第一个元素、删除第二个元素、同时保留前两个元素再找不满足等差的元素分别枚举删除这几种情况，逻辑简洁明了，代码可读性高。
- **作者：奇米（4星）**
    - **关键亮点**：通过 `map` 记录相邻元素的差值，利用差值的统计信息来判断删除某个元素后是否能构成等差数列，实现较为巧妙。
- **作者：Disjoint_cat（4星）**
    - **关键亮点**：提出了除去排序 $O(n)$ 的算法，通过分类讨论，先考虑保留前两个元素的情况，再考虑删除第一个或第二个元素的情况，复杂度分析清晰。

### 重点代码
#### DaiRuiChen007 的代码
```cpp
inline bool judge(int k) {
    //检查删除k后能不能构成等差数列 
    vector <int> seq;
    for(int i=1;i<=n;++i) if(i!=k) seq.push_back(a[i].val);
    int d=seq[1]-seq[0];
    for(int i=1;i<seq.size();++i) {
        if(seq[i]-seq[i-1]!=d) return false;
    }
    return true;
}
signed main() {
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i].val),a[i].id=i;
    if(n<=3) {
        puts("1");
        return 0;
    }
    sort(a+1,a+n+1);
    if(judge(1)) {
        //删除第一项 
        printf("%lld\n",a[1].id);
        return 0;
    }
    if(judge(2)) {
        //删除第二项 
        printf("%lld\n",a[2].id);
        return 0;
    }
    bool flg=true;
    int d=a[2].val-a[1].val,k=0;
    for(int i=3;i<=n;++i) {
        if(a[i].val-a[i-1].val!=d) {
            //找到不满足的两项删除 
            if(judge(i)) {
                printf("%lld\n",a[i].id);
                return 0;
            }
            if(judge(i-1)) {
                printf("%lld\n",a[i-1].id);
                return 0;
            }
            puts("-1");
            return 0;
        }
    }
    return 0;
}
```
**核心实现思想**：定义 `judge` 函数用于判断删除某个元素后剩余元素是否构成等差数列。在 `main` 函数中，先处理 $n\leq3$ 的特殊情况，然后对序列排序，依次判断删除第一个元素、第二个元素以及找到不满足等差的元素分别删除的情况。

#### 奇米的代码
```cpp
For(i,1,n-1) 
{
    b[i]=a[i+1].x-a[i].x;
    lyx[b[i]]++;
}
if(a[1].x==a[n].x||lyx[b[1]]==n-1) return printf("%d\n",a[1].id),0;
lyx[b[1]]--;
if(lyx[b[2]]==n-2) return printf("%d\n",a[1].id),0;
lyx[b[1]]++;

lyx[b[n-1]]--;
if(lyx[b[n-2]]==n-2) return printf("%d\n",a[n].id),0;
lyx[b[n-1]]++;

For(i,2,n-1) 
{
    int x=b[i];
    int nxt=a[i+1].x-a[i-1].x;
    int pre=b[i-1];
    lyx[x]--,lyx[pre]--,lyx[nxt]++;
    if(lyx[nxt]==n-2) 
        return printf("%d\n",a[i].id),0;
    lyx[x]++,lyx[pre]++,lyx[nxt]--;
}
GG;
```
**核心实现思想**：先记录相邻元素的差值并统计其出现次数。然后处理一些特殊情况，如序列元素都相同或所有差值都相同的情况。接着枚举删除中间元素，通过调整差值的统计信息，判断删除该元素后是否能构成等差数列。

#### Disjoint_cat 的代码
```cpp
int sol()
{
    sort(a+1,a+n+1);
    int d=a[2]-a[1];//keep a[1] & a[2]
    a[n+1]=a[n-1]+d;
    for(int i=2;i<n;i++)
        if(a[i+1]-a[i]!=d)
            if(a[i+2]-a[i]==d&&!pos)pos=++i;
            else
            {
                int ok=1;
                d=a[3]-a[2];//delete a[1]
                for(int i=4;i<=n;i++)
                    if(a[i]-a[i-1]!=d)
                    {
                        ok=0;
                        break;
                    }
                if(ok)return 1;
                ok=1;
                d=a[3]-a[1];//delete a[2]
                for(int i=4;i<=n;i++)
                    if(a[i]-a[i-1]!=d)
                    {
                        ok=0;
                        break;
                    }
                if(ok)return 2;
                return 1919810;//no solution
            }
    if(pos)return pos;
    else return n;
}
```
**核心实现思想**：先对序列排序，然后考虑保留前两个元素的情况，若出现不满足等差的情况，尝试删除相应元素。若此情况无解，则分别考虑删除第一个元素和第二个元素的情况，最后根据结果返回相应的索引或表示无解的值。

### 最优关键思路或技巧
- 先对序列进行排序，将问题转化为有序序列下的判断问题，简化了后续操作。
- 利用 `map` 或 `set` 记录相邻元素的差值及其出现次数，通过统计信息辅助判断是否能构成等差数列。
- 分类讨论不同的删除情况，减少不必要的枚举，提高效率。

### 拓展思路
同类型题目可能会在等差数列的基础上进行拓展，如判断等比数列、斐波那契数列等，或者增加更多的约束条件，如限制删除元素的次数、要求序列满足多种性质等。解题思路仍然可以先排序，再通过枚举和判断来解决。

### 推荐洛谷题目
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
- [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)
- [P1634 禽兽的传染病](https://www.luogu.com.cn/problem/P1634)

### 个人心得摘录与总结
- **lyzqs**：注意公差出现次数可能因为重复元素、首项或末项被删除等情况而发生变化，需要进行特判和额外的检查。总结来说，在处理这类问题时，要充分考虑各种边界情况和特殊情况，避免遗漏。
- **Disjoint_cat**：对于输入为 `1 2 3 4 6` 这种情况，要注意在判断时对边界的处理，如让 $a_{n + 1}$ 等于 $a_{n - 1} + d$ 来简化判断。总结为在处理序列问题时，要注意边界条件的处理，确保算法的正确性。 

---
处理用时：66.39秒