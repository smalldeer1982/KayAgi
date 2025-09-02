# 题目信息

# Counterexample

## 题目描述

Your friend has recently learned about coprime numbers. A pair of numbers $ {a,b} $ is called coprime if the maximum number that divides both $ a $ and $ b $ is equal to one.

Your friend often comes up with different statements. He has recently supposed that if the pair $ (a,b) $ is coprime and the pair $ (b,c) $ is coprime, then the pair $ (a,c) $ is coprime.

You want to find a counterexample for your friend's statement. Therefore, your task is to find three distinct numbers $ (a,b,c) $ , for which the statement is false, and the numbers meet the condition $ l<=a<b<c<=r $ .

More specifically, you need to find three numbers $ (a,b,c) $ , such that $ l<=a<b<c<=r $ , pairs $ (a,b) $ and $ (b,c) $ are coprime, and pair $ (a,c) $ is not coprime.

## 说明/提示

In the first sample pair $ (2,4) $ is not coprime and pairs $ (2,3) $ and $ (3,4) $ are.

In the second sample you cannot form a group of three distinct integers, so the answer is -1.

In the third sample it is easy to see that numbers $ 900000000000000009 $ and $ 900000000000000021 $ are divisible by three.

## 样例 #1

### 输入

```
2 4
```

### 输出

```
2 3 4
```

## 样例 #2

### 输入

```
10 11
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
900000000000000009 900000000000000029
```

### 输出

```
900000000000000009 900000000000000010 900000000000000021
```

# AI分析结果

### 题目翻译
## 反例

### 题目描述
你的朋友最近学习了互质数的知识。如果一对数 $ {a,b} $ 的最大公约数等于 1，则称这对数为互质数。

你的朋友经常提出不同的命题。他最近猜想，如果数对 $ (a,b) $ 是互质的，且数对 $ (b,c) $ 也是互质的，那么数对 $ (a,c) $ 也是互质的。

你想为你朋友的命题找到一个反例。因此，你的任务是找到三个不同的数 $ (a,b,c) $，使得该命题不成立，并且这些数满足条件 $ l\leq a < b < c\leq r $。

更具体地说，你需要找到三个数 $ (a,b,c) $，使得 $ l\leq a < b < c\leq r $，数对 $ (a,b) $ 和 $ (b,c) $ 是互质的，而数对 $ (a,c) $ 不是互质的。

### 说明/提示
在第一个样例中，数对 $ (2,4) $ 不是互质的，而数对 $ (2,3) $ 和 $ (3,4) $ 是互质的。

在第二个样例中，你无法组成一组三个不同的整数，因此答案是 -1。

在第三个样例中，很容易看出数字 $ 900000000000000009 $ 和 $ 900000000000000021 $ 能被 3 整除。

### 样例 #1
#### 输入
```
2 4
```
#### 输出
```
2 3 4
```

### 样例 #2
#### 输入
```
10 11
```
#### 输出
```
-1
```

### 样例 #3
#### 输入
```
900000000000000009 900000000000000029
```
#### 输出
```
900000000000000009 900000000000000010 900000000000000021
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕寻找满足特定条件的三个数 $(a, b, c)$ 展开，思路大致可分为两类：
1. **暴力枚举**：通过三层循环遍历 $l$ 到 $r$ 之间的所有可能组合，使用欧几里得算法或 `__gcd` 函数判断数对是否互质，找到满足条件的组合后输出并结束程序。
2. **数学推导**：利用连续自然数和连续奇数互质的性质，分情况讨论 $r - l$ 的值，直接构造出满足条件的三个数或判断无解。

暴力枚举的优点是思路简单直接，但时间复杂度较高，为 $O((r - l)^3)$；数学推导的优点是时间复杂度低，为 $O(1)$，但需要一定的数学思维和推理能力。

### 所选题解
- **作者：清清老大 (赞：1)，4星**
    - **关键亮点**：思路清晰，通过对 $r - l$ 的不同情况进行分类讨论，直接构造出满足条件的三个数或判断无解，代码简洁明了，时间复杂度为 $O(1)$。
- **作者：HuZHUNZHUN (赞：0)，4星**
    - **关键亮点**：利用连续自然数互质的性质，通过数学推导得出只需判断是否存在满足条件的偶数 $n$ 即可，代码简洁高效，时间复杂度为 $O(1)$。
- **作者：Waaifu_D (赞：0)，4星**
    - **关键亮点**：同样是对 $r - l$ 的不同情况进行分类讨论，逻辑清晰，代码实现简单，时间复杂度为 $O(1)$。

### 重点代码
#### 作者：清清老大
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long l,r;
    cin >> l >> r;
    if(r - l < 2)
    {
        cout << -1;
        return 0;
    }
    else if(r - l == 2)
    {
        if(l % 2 == 0)
        {
            cout << l << " " << l + 1 << " " << l + 2;
            return 0;
        }
        else
        {
            cout << -1;
            return 0;
        }
    }
    if(l % 2 == 0)
    {
        cout << l << " " << l + 1 << " " << l + 2;
        return 0;
    }
    else
    {
        cout << l + 1 << " " << l + 2 << " " << l + 3;
        return 0;
    }
}
```
**核心实现思想**：根据 $r - l$ 的值分情况讨论，当 $r - l < 2$ 时无解；当 $r - l = 2$ 时，若 $l$ 为偶数则输出 $l, l + 1, l + 2$，否则无解；当 $r - l > 2$ 时，若 $l$ 为偶数则输出 $l, l + 1, l + 2$，否则输出 $l + 1, l + 2, l + 3$。

#### 作者：HuZHUNZHUN
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;
int main()
{
    ios::sync_with_stdio(false);
    cin>>l>>r;
    l=l+(l%2);
    if(l+2>r) cout<<"-1";
    else cout<<l<<" "<<l+1<<" "<<l+2<<endl;
    return 0;
}
```
**核心实现思想**：先将 $l$ 调整为偶数，然后判断 $l + 2$ 是否大于 $r$，若大于则无解，否则输出 $l, l + 1, l + 2$。

#### 作者：Waaifu_D
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r,sum;
int main()
{
    cin>>l>>r;
    if(r-l<=1)
    {
        cout<<-1;
        return 0;
    }
    if(r-l==2)
    {
        if(l%2==0)
        {
            cout<<l<<" "<<l+1<<" "<<l+2;
        }
        else
        {
            cout<<-1;
        }
    }
    if(r-l>2)
    {
        if(l%2==0)
        {
            cout<<l<<" "<<l+1<<" "<<l+2;
        }
        else
        {
            cout<<l+1<<" "<<l+2<<" "<<l+3;
        }
    }
    return 0;
}
```
**核心实现思想**：同样是根据 $r - l$ 的值分情况讨论，当 $r - l <= 1$ 时无解；当 $r - l = 2$ 时，若 $l$ 为偶数则输出 $l, l + 1, l + 2$，否则无解；当 $r - l > 2$ 时，若 $l$ 为偶数则输出 $l, l + 1, l + 2$，否则输出 $l + 1, l + 2, l + 3$。

### 关键思路或技巧
- 利用连续自然数和连续奇数互质的性质，简化问题的求解过程。
- 分情况讨论 $r - l$ 的值，避免不必要的计算，提高算法效率。

### 拓展思路
同类型题目可能会涉及更多的数学性质和逻辑推理，例如在不同的数论条件下寻找满足特定关系的数。类似的算法套路包括对给定范围进行分类讨论，利用数学定理和性质直接构造解或判断无解。

### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)
3. [P2568 GCD](https://www.luogu.com.cn/problem/P2568)

### 个人心得摘录与总结
- **LucasXu80**：读题时不要被数据范围吓到，要静下心来分析样例，从中寻找灵感。
- **Remake_**：注意数据范围，要开 `long long` 或 `unsigned long long`；`gcd` 可以使用欧几里得算法或 C++ 自带的 `__gcd` 函数；找到答案后要及时结束程序，节省空间。

---
处理用时：46.68秒