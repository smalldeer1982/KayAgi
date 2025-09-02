# 题目信息

# Beautiful Sequence

## 题目描述

An integer sequence is called beautiful if the difference between any two consecutive numbers is equal to $ 1 $ . More formally, a sequence $ s_1, s_2, \ldots, s_{n} $ is beautiful if $ |s_i - s_{i+1}| = 1 $ for all $ 1 \leq i \leq n - 1 $ .

Trans has $ a $ numbers $ 0 $ , $ b $ numbers $ 1 $ , $ c $ numbers $ 2 $ and $ d $ numbers $ 3 $ . He wants to construct a beautiful sequence using all of these $ a + b + c + d $ numbers.

However, it turns out to be a non-trivial task, and Trans was not able to do it. Could you please help Trans?

## 说明/提示

In the first test, it is easy to see, that the sequence is beautiful because the difference between any two consecutive numbers is equal to $ 1 $ . Also, there are exactly two numbers, equal to $ 0 $ , $ 1 $ , $ 2 $ and exactly one number, equal to $ 3 $ .

It can be proved, that it is impossible to construct beautiful sequences in the second and third tests.

## 样例 #1

### 输入

```
2 2 2 1
```

### 输出

```
YES
0 1 0 1 2 3 2
```

## 样例 #2

### 输入

```
1 2 3 4
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2 2 2 3
```

### 输出

```
NO
```

# AI分析结果

### 题目内容中文重写
# 美丽序列

## 题目描述
如果一个整数序列中任意两个相邻数字的差都等于 1，那么这个整数序列就被称为美丽序列。更正式地说，如果对于所有的 $1 \leq i \leq n - 1$，都有 $ |s_i - s_{i+1}| = 1 $，那么序列 $ s_1, s_2, \ldots, s_{n} $ 就是美丽序列。

Trans 有 $ a $ 个 0，$ b $ 个 1，$ c $ 个 2 和 $ d $ 个 3。他想使用所有这 $ a + b + c + d $ 个数字来构造一个美丽序列。

然而，事实证明这是一项不简单的任务，Trans 没能完成。你能帮帮 Trans 吗？

## 说明/提示
在第一个测试用例中，很容易看出这个序列是美丽的，因为任意两个相邻数字的差都等于 1。此外，恰好有两个 0、两个 1、两个 2 和一个 3。

可以证明，在第二个和第三个测试用例中不可能构造出美丽序列。

## 样例 #1
### 输入
```
2 2 2 1
```
### 输出
```
YES
0 1 0 1 2 3 2
```

## 样例 #2
### 输入
```
1 2 3 4
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
2 2 2 3
```
### 输出
```
NO
```

### 算法分类
构造

### 综合分析与结论
这三道题解均围绕如何利用给定数量的 0、1、2、3 构造出美丽序列展开。
- **思路对比**：
    - _edge_ 和 yangmuguang 的思路类似，都是枚举序列的起始数字，然后根据相邻数字差为 1 的规则依次放置后续数字，直到无法放置或成功构造出完整序列。
    - Guess00 的思路是先考虑一些特殊情况，然后对剩余的一般情况进行分类讨论，通过计算不同数字的数量关系来判断是否能构造出美丽序列，并确定输出顺序。
- **算法要点对比**：
    - _edge_ 和 yangmuguang 主要是通过模拟构造过程，不断尝试放置数字。
    - Guess00 则是通过数学分析，根据不同数字的数量关系进行特判和分类讨论。
- **解决难点对比**：
    - _edge_ 和 yangmuguang 要解决的难点在于如何保证在枚举起始数字的情况下，能正确地放置后续数字，避免出现无法继续构造的情况。
    - Guess00 要解决的难点在于准确找出所有特殊情况，并合理分类讨论一般情况，确保不遗漏和错误判断。

### 题解评分
- _edge_：4 星。思路清晰，代码简洁，通过枚举起始数字和模拟构造过程解决问题，时间复杂度较低。
- Guess00：3 星。思路较复杂，通过大量特判和分类讨论解决问题，代码可读性相对较差。
- yangmuguang：3 星。思路和 _edge_ 类似，但代码中数组下标使用不太规范，影响了代码的可读性。

### 所选题解
- _edge_（4 星）
    - 关键亮点：思路简洁明了，通过枚举起始数字，模拟构造过程，利用数组记录数字数量，时间复杂度为 $O(n)$。

### 重点代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=1e5+5;
int aa[INF],bb[INF],ans[INF],sum,fl;
void solve(int xx) {
    for (int i=0;i<4;i++) bb[i]=aa[i];
    if (!bb[xx]) return ;
    bb[xx]--;ans[1]=xx;
    for (int i=2;i<=sum;i++) {
        if (xx<3 && bb[xx+1]) xx++;
        else if (xx && bb[xx-1]) xx--;
        else return ;
        ans[i]=xx;bb[xx]--;
    }
    cout<<"YES\n";fl=1;
    for (int i=1;i<=sum;i++) cout<<ans[i]<<" ";
    cout<<"\n";
    exit(0);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>aa[0]>>aa[1]>>aa[2]>>aa[3];
    sum+=aa[0]+aa[1]+aa[2]+aa[3];
    solve(0);solve(1);
    solve(2);solve(3);
    if (!fl) cout<<"NO\n";
    return 0;
}
```
**核心实现思想**：`solve` 函数用于尝试以 `xx` 为起始数字构造美丽序列。首先复制数字数量数组 `aa` 到 `bb`，若起始数字数量为 0 则返回。然后依次放置后续数字，优先选择相邻且数量不为 0 的数字，若无法继续放置则返回。若成功构造出完整序列，则输出 `YES` 和序列，否则在所有起始数字都尝试完后输出 `NO`。

### 可拓展之处
同类型题可能会给出更多种类的数字，或者改变美丽序列的定义，如相邻数字差为某个固定值或在某个范围内。类似算法套路可以先分析特殊情况，再通过枚举、模拟或数学分析等方法进行构造。

### 推荐洛谷题目
1. P1036 选数：考察组合数学和枚举的思想。
2. P1149 火柴棒等式：需要通过枚举和模拟来构造满足条件的等式。
3. P1217 [USACO1.5]回文质数 Prime Palindromes：结合质数和回文数的判断，需要枚举和筛选。

### 个人心得
_edge_：提到楼上 dalao 的特判惊到自己，这里采用枚举起始数字构造的简单想法，不过不太会严格证明正确性，只是感性理解端点要和其他端点对拼消耗掉。总结就是在解题时可以尝试从简单的思路入手，先通过感性理解来解决问题，再考虑严格证明。 

---
处理用时：47.39秒