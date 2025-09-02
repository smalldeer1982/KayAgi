# 题目信息

# Red and Blue

## 题目描述

Monocarp had a sequence $ a $ consisting of $ n + m $ integers $ a_1, a_2, \dots, a_{n + m} $ . He painted the elements into two colors, red and blue; $ n $ elements were painted red, all other $ m $ elements were painted blue.

After painting the elements, he has written two sequences $ r_1, r_2, \dots, r_n $ and $ b_1, b_2, \dots, b_m $ . The sequence $ r $ consisted of all red elements of $ a $ in the order they appeared in $ a $ ; similarly, the sequence $ b $ consisted of all blue elements of $ a $ in the order they appeared in $ a $ as well.

Unfortunately, the original sequence was lost, and Monocarp only has the sequences $ r $ and $ b $ . He wants to restore the original sequence. In case there are multiple ways to restore it, he wants to choose a way to restore that maximizes the value of

 $ $$$f(a) = \max(0, a_1, (a_1 + a_2), (a_1 + a_2 + a_3), \dots, (a_1 + a_2 + a_3 + \dots + a_{n + m})) $ $ </p><p>Help Monocarp to calculate the maximum possible value of  $ f(a)$$$.

## 说明/提示

In the explanations for the sample test cases, red elements are marked as bold.

In the first test case, one of the possible sequences $ a $ is $ [\mathbf{6}, 2, \mathbf{-5}, 3, \mathbf{7}, \mathbf{-3}, -4] $ .

In the second test case, one of the possible sequences $ a $ is $ [10, \mathbf{1}, -3, \mathbf{1}, 2, 2] $ .

In the third test case, one of the possible sequences $ a $ is $ [\mathbf{-1}, -1, -2, -3, \mathbf{-2}, -4, -5, \mathbf{-3}, \mathbf{-4}, \mathbf{-5}] $ .

In the fourth test case, one of the possible sequences $ a $ is $ [0, \mathbf{0}] $ .

## 样例 #1

### 输入

```
4
4
6 -5 7 -3
3
2 3 -4
2
1 1
4
10 -3 2 2
5
-1 -2 -3 -4 -5
5
-1 -2 -3 -4 -5
1
0
1
0```

### 输出

```
13
13
0
0```

# AI分析结果

### 题目内容
# 红色与蓝色

## 题目描述
莫诺卡普有一个由 \(n + m\) 个整数 \(a_1, a_2, \dots, a_{n + m}\) 组成的序列 \(a\) 。他将这些元素涂成两种颜色，红色和蓝色；其中 \(n\) 个元素被涂成红色，其余 \(m\) 个元素被涂成蓝色。

在给元素涂色之后，他写出了两个序列 \(r_1, r_2, \dots, r_n\) 和 \(b_1, b_2, \dots, b_m\) 。序列 \(r\) 由 \(a\) 中所有红色元素按它们在 \(a\) 中出现的顺序组成；类似地，序列 \(b\) 由 \(a\) 中所有蓝色元素按它们在 \(a\) 中出现的顺序组成。

不幸的是，原始序列丢失了，莫诺卡普现在只有序列 \(r\) 和 \(b\) 。他想恢复原始序列。如果有多种恢复方式，他想选择一种恢复方式，使得以下值最大化：

\(f(a) = \max(0, a_1, (a_1 + a_2), (a_1 + a_2 + a_3), \dots, (a_1 + a_2 + a_3 + \dots + a_{n + m}))\)

## 说明/提示
在示例测试用例的解释中，红色元素用粗体标记。

在第一个测试用例中，一种可能的序列 \(a\) 是 \([\mathbf{6}, 2, \mathbf{-5}, 3, \mathbf{7}, \mathbf{-3}, -4]\) 。

在第二个测试用例中，一种可能的序列 \(a\) 是 \([10, \mathbf{1}, -3, \mathbf{1}, 2, 2]\) 。

在第三个测试用例中，一种可能的序列 \(a\) 是 \([\mathbf{-1}, -1, -2, -3, \mathbf{-2}, -4, -5, \mathbf{-3}, \mathbf{-4}, \mathbf{-5}]\) 。

在第四个测试用例中，一种可能的序列 \(a\) 是 \([0, \mathbf{0}]\) 。

## 样例 #1
### 输入
```
4
4
6 -5 7 -3
3
2 3 -4
2
1 1
4
10 -3 2 2
5
-1 -2 -3 -4 -5
5
-1 -2 -3 -4 -5
1
0
1
0
```
### 输出
```
13
13
0
0
```

### 算法分类
前缀和

### 综合分析与结论
所有题解的核心思路一致，均基于“组合得到的数列 \(a\) 的最大前缀和等于 \(r\) 和 \(b\) 各自的最大前缀和之和”这一结论。该结论的依据是原序列中同组内元素相对顺序不变，使得原序列的前缀和性质在合并后依然保持。各题解的主要差异在于代码实现细节，如变量命名、输入输出方式、初始化方式以及是否使用函数封装等。

### 所选的题解
- **作者：zjjws（5星）**
    - **关键亮点**：通过反证法严谨证明了组合后数列最大前缀和与两个子序列最大前缀和的关系，逻辑清晰。代码简洁明了，使用`inline`函数定义核心操作，变量命名规范。
    - **重点代码**：
```cpp
inline void work()
{
    int n=rin();
    LL sum=0;
    LL s=0;
    LL maxs=0;
    for(int i=1;i<=n;i++)
    {
        s+=rin();
        if(s>maxs)maxs=s;
    }
    sum+=maxs;
    n=rin();
    s=maxs=0;
    for(int i=1;i<=n;i++)
    {
        s+=rin();
        if(s>maxs)maxs=s;
    }
    sum+=maxs;
    printf("%lld\n",sum);
    return;
}
```
    - **核心实现思想**：先对第一个序列求最大前缀和并累加到`sum`，再对第二个序列做同样操作，最后输出`sum`。
- **作者：lianchanghua（4星）**
    - **关键亮点**：在分析部分清晰阐述了结论的由来，代码简洁易懂，使用`#define int long long`避免了整型溢出问题，同时利用`std::ios::sync_with_stdio(false)`加速输入输出。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n;
        int sa=0,sb=0;
        int maxa=0,maxb=0;
        for(int i=1;i<=n;i++){
            int a;
            cin>>a;
            sa+=a;
            maxa=max(maxa,sa);
        }
        cin>>m;
        for(int i=1;i<=m;i++){
            int b;
            cin>>b;
            sb+=b;
            maxb=max(maxb,sb);
        }
        cout<<maxa+maxb<<"\n";
    }
    return 0;
}
```
    - **核心实现思想**：通过循环分别计算两个序列的前缀和，并不断更新最大前缀和，最后输出两个最大前缀和的和。
- **作者：I_like_magic（4星）**
    - **关键亮点**：在题解中特别提醒了`maxa`和`maxb`初始要赋值为0，以处理可以不取任何数的情况，对细节把握较好。代码结构清晰，变量命名直观。
    - **重点代码**：
```cpp
#include<iostream>
using namespace std;
int t;
int n,m;
int sa,sb;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        sa=0,sb=0;
        int maxa=0,maxb=0;
        for(int i=1;i<=n;i++){
            int a;
            cin>>a;
            sa+=a;
            maxa=max(maxa,sa);
        }
        cin>>m;
        for(int i=1;i<=m;i++){
            int b;
            cin>>b;
            sb+=b;
            maxb=max(maxb,sb);
        }
        cout<<maxa+maxb<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：与其他题解类似，通过两轮循环分别计算两个序列的最大前缀和并相加输出。

### 最优关键思路或技巧
利用前缀和的性质，通过分别计算两个子序列的最大前缀和并相加来得到合并后序列的最大前缀和。在代码实现中，注意变量的初始化，尤其是在可能存在不取任何元素的情况下，用于记录最大前缀和的变量应初始化为0。

### 拓展
同类型题目通常围绕序列的前缀和性质展开，可能会增加一些限制条件或改变目标值的计算方式。例如，要求在满足某些特定条件下的最大前缀和，或者在多个序列间进行更复杂的合并操作后求前缀和等。类似算法套路是在处理序列问题时，善于挖掘序列内部元素顺序不变等条件与前缀和之间的关系，通过分析子序列的特征来简化对整个序列的处理。

### 洛谷推荐题目
- **P1115 最大子段和**：该题同样是关于序列前缀和相关问题，求序列的最大子段和，与本题思路有相似之处。
- **P3957 [NOIP2017 普及组] 跳房子**：涉及到对序列的处理和前缀和优化，通过合理利用前缀和来解决问题。
- **P1414 又是毕业季II**：需要通过前缀和来统计满足一定条件的子序列数量，与本题在利用前缀和解决序列问题上有共通点。 

---
处理用时：67.46秒