# 题目信息

# Playing with Paper

## 题目描述

One day Vasya was sitting on a not so interesting Maths lesson and making an origami from a rectangular $ a $ mm $ × $ $ b $ mm sheet of paper ( $ a>b $ ). Usually the first step in making an origami is making a square piece of paper from the rectangular sheet by folding the sheet along the bisector of the right angle, and cutting the excess part.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527A/919759a22ff5597b60d204c65faf22c2233113ef.png)After making a paper ship from the square piece, Vasya looked on the remaining $ (a-b) $ mm $ × $ $ b $ mm strip of paper. He got the idea to use this strip of paper in the same way to make an origami, and then use the remainder (if it exists) and so on. At the moment when he is left with a square piece of paper, he will make the last ship from it and stop.

Can you determine how many ships Vasya will make during the lesson?

## 说明/提示

Pictures to the first and second sample test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527A/8a10deb3e516fda81e76aae552290cb4cf3649c8.png)

## 样例 #1

### 输入

```
2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 7
```

### 输出

```
6
```

## 样例 #3

### 输入

```
1000000000000 1
```

### 输出

```
1000000000000
```

# AI分析结果

### 题目中文重写
# 玩转纸张

## 题目描述
有一天，瓦西亚正在上一节不那么有趣的数学课，他用一张 $ a $ 毫米 $ × $ $ b $ 毫米的长方形纸（$ a > b $）折纸。通常，折纸的第一步是沿着直角的平分线折叠纸张，将长方形纸变成正方形纸，然后剪掉多余的部分。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527A/919759a22ff5597b60d204c65faf22c2233113ef.png)

用正方形纸折好纸船后，瓦西亚看着剩下的 $ (a - b) $ 毫米 $ × $ $ b $ 毫米的纸条。他想到了一个主意，用同样的方法对这张纸条折纸，然后（如果有剩余的话）继续对剩余部分进行同样的操作，依此类推。当他最后得到一张正方形纸时，他将用它折最后一艘纸船，然后停止。

你能确定瓦西亚在这节课上能折多少艘纸船吗？

## 说明/提示
第一个和第二个示例测试的图片。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527A/8a10deb3e516fda81e76aae552290cb4cf3649c8.png)

## 样例 #1
### 输入
```
2 1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
10 7
```
### 输出
```
6
```

## 样例 #3
### 输入
```
1000000000000 1
```
### 输出
```
1000000000000
```

### 算法分类
模拟

### 综合分析与结论
- **思路对比**：这些题解的核心思路都是模拟将长方形纸不断裁剪成正方形的过程。不同的是，部分题解直接模拟每次裁剪一个正方形，而优化后的题解会一次性减去倍数，避免了大量重复的减法操作，提高效率。
- **算法要点**：都需要在每次操作前确保 `a` 大于 `b`，若不满足则交换两者。通过不断更新 `a` 和 `b` 的值，直到其中一个为 0 停止，同时记录操作次数。
- **解决难点**：主要难点在于处理大数值输入时的效率问题，直接模拟每次减去一个 `b` 会导致超时，因此需要一次性减去 `a` 中包含 `b` 的倍数。

### 题解评分
- **LW_h_FP**：4星。思路清晰，代码简洁，直接指出了原始模拟方法的问题并给出优化方案。
- **GusyNight**：3星。引入自定义函数，但代码结构稍显复杂，且部分注释和代码风格不够规范。
- **Tiago**：3星。详细记录了调试过程，但使用的是 Pascal 语言，且代码可读性一般。
- **江山_远方**：4星。使用递归实现，思路独特，通过判断是否为整倍数进行优化。

### 所选题解
- **LW_h_FP**：4星。关键亮点在于直接指出原始模拟方法的不足，并给出了一次性减去倍数的优化方案，代码简洁易懂。
- **江山_远方**：4星。使用递归实现模拟过程，通过判断是否为整倍数直接返回结果，避免了不必要的递归调用。

### 重点代码
#### LW_h_FP
```cpp
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    long long a,b,ans=0; cin>>a>>b;
    while(a!=0&&b!=0){
        if(a<b) swap(a,b);
        ans+=a/b,a-=b*(a/b);
    }
    cout<<ans<<endl;
    return 0;
}
```
**核心实现思想**：在 `while` 循环中，每次确保 `a` 大于 `b`，然后一次性减去 `a` 中包含 `b` 的倍数，同时将操作次数累加到 `ans` 中，直到 `a` 或 `b` 为 0。

#### 江山_远方
```cpp
#include<bits/stdc++.h>
using namespace std;
long long MIN;
long long n,m;
void bigsort(long long &x,long long &y)//将x,y变为大数在前，小数在后
{
    long long a=max(x,y),b=min(x,y);
    x=a;
    y=b;
}
void dfs(long long x,long long y,long long s)//递归，一次减去他们的倍数差，以防止超时，若是整倍数，则可直接返回
{
    bigsort(x,y);
    if(x%y==0)
    {
        cout<<s+x/y<<endl;
        return ;
    }
    else dfs(y,x%y,s+x/y);
} 
int main()
{
    cin>>n>>m;//读入
    dfs(n,m,0);//调用递归
    return 0;
} 
```
**核心实现思想**：使用递归函数 `dfs` 模拟裁剪过程，在每次递归中确保 `x` 大于 `y`，若 `x` 是 `y` 的整倍数，则直接输出结果，否则继续递归处理 `y` 和 `x % y`。

### 最优关键思路或技巧
- 一次性减去 `a` 中包含 `b` 的倍数，避免大量重复的减法操作，提高效率。
- 使用递归实现模拟过程，通过判断是否为整倍数直接返回结果，减少不必要的递归调用。

### 可拓展之处
同类型题目可能会有不同的裁剪规则或条件，例如裁剪时需要满足一定的面积限制或形状要求。类似算法套路可以应用于模拟其他的迭代操作，如模拟游戏过程、数据处理过程等。

### 推荐洛谷题目
- P1003 铺地毯
- P1047 校门外的树
- P1098 字符串的展开

### 个人心得摘录与总结
- **Tiago**：一开始直接模拟每次减去一个 `b` 导致运行时错误（RE），后来发现需要使用 `int64` 类型处理大数值，但仍然错误。最后通过一次性减去倍数优化程序，成功 AC。总结：对于大数值输入，要注意数据类型的选择，同时优化算法以提高效率。
- **江山_远方**：强调了在处理大数值时要使用 `long long` 类型，否则可能会导致错误。总结：在做题时要注意数据范围，避免因数据类型问题导致错误。

---
处理用时：38.31秒