# 题目信息

# Coat of Anticubism

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF667B/da431a35861ffb0dfb05294a401b5e75bc0d5240.png)As some of you know, cubism is a trend in art, where the problem of constructing volumetrical shape on a plane with a combination of three-dimensional geometric shapes comes to the fore.

A famous sculptor Cicasso, whose self-portrait you can contemplate, hates cubism. He is more impressed by the idea to transmit two-dimensional objects through three-dimensional objects by using his magnificent sculptures. And his new project is connected with this. Cicasso wants to make a coat for the haters of anticubism. To do this, he wants to create a sculpture depicting a well-known geometric primitive — convex polygon.

Cicasso prepared for this a few blanks, which are rods with integer lengths, and now he wants to bring them together. The $ i $ -th rod is a segment of length $ l_{i} $ .

The sculptor plans to make a convex polygon with a nonzero area, using all rods he has as its sides. Each rod should be used as a side to its full length. It is forbidden to cut, break or bend rods. However, two sides may form a straight angle ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF667B/88c61e080ae2c77e20323807b54f172a39161c4f.png).

Cicasso knows that it is impossible to make a convex polygon with a nonzero area out of the rods with the lengths which he had chosen. Cicasso does not want to leave the unused rods, so the sculptor decides to make another rod-blank with an integer length so that his problem is solvable. Of course, he wants to make it as short as possible, because the materials are expensive, and it is improper deed to spend money for nothing.

Help sculptor!

## 说明/提示

In the first example triangle with sides $ {1+1=2,2,1} $ can be formed from a set of lengths $ {1,1,1,2} $ .

In the second example you can make a triangle with lengths $ {20,11,4+3+2+1=10} $ .

## 样例 #1

### 输入

```
3
1 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
20 4 3 2 1
```

### 输出

```
11
```

# AI分析结果

### 题目内容中文重写
# 反立体主义的外衣

## 题目描述
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF667B/da431a35861ffb0dfb05294a401b5e75bc0d5240.png)你们中有些人可能知道，立体主义是艺术领域的一种潮流，其核心问题是通过组合三维几何形状在平面上构建立体形状。

著名雕塑家西加索（Cicasso）——你可以欣赏到他的自画像——非常讨厌立体主义。他更感兴趣的是通过宏伟的雕塑，用三维物体来表现二维物体，他的新项目就与此相关。西加索想为反反立体主义者制作一件外衣。为此，他想创作一件描绘著名几何图形——凸多边形的雕塑。

西加索为此准备了一些毛坯，它们是具有整数长度的杆，现在他想把它们组合起来。第 $i$ 根杆是长度为 $l_{i}$ 的线段。

雕塑家计划用他所有的杆作为边，制作一个面积非零的凸多边形。每根杆都要完整地作为一条边使用，禁止切割、折断或弯曲杆。不过，两条边可以形成平角。
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF667B/88c61e080ae2c77e20323807b54f172a39161c4f.png)

西加索知道，用他选择的杆的长度无法制作出面积非零的凸多边形。他不想留下未使用的杆，所以决定再制作一根长度为整数的杆毛坯，以使问题有解。当然，他希望这根杆尽可能短，因为材料很昂贵，无端浪费钱财是不可取的行为。

请帮助雕塑家！

## 说明/提示
在第一个样例中，可以用长度集合 $\{1,1,1,2\}$ 组成边长为 $\{1 + 1 = 2, 2, 1\}$ 的三角形。

在第二个样例中，可以组成边长为 $\{20, 11, 4 + 3 + 2 + 1 = 10\}$ 的三角形。

## 样例 #1
### 输入
```
3
1 2 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
5
20 4 3 2 1
```
### 输出
```
11
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于凸多边形的性质：凸多边形任意 $n - 1$ 条边之和大于另外一条边。由于给定的边无法构成凸多边形，所以最长边大于等于其余边之和。要构造一条最短的边使这些边能构成凸多边形，就是让加上这条边后最长边小于其余边之和，即这条边的长度为最长边的长度减去其余边长度之和再加 $1$。

各题解的差异主要体现在找最大值的方法和代码实现细节上，有的使用循环查找，有的使用STL的 `max_element()` 函数，还有的使用排序。

### 所选题解
- **lichenzhen（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接通过循环找出最长边并计算结果。
- **RE_Prince（4星）**
    - **关键亮点**：不仅给出了常规的循环查找最大值的方法，还介绍了使用STL的 `max_element()` 函数和排序找最大值的方法，拓展性强。
- **szh_AK_all（4星）**
    - **关键亮点**：对判断凸多边形的原理进行了详细解释，代码中考虑了结果为负数的情况并进行了处理。

### 重点代码
#### lichenzhen的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,maxn;
int main()
{
    cin>>n;
    while(n--){
       cin>>k;
       maxn=max(k,maxn);//找最长边
       ans+=k;
    }
    ans-=maxn;
    cout<<maxn-ans+1;
}
```
**核心实现思想**：通过循环读入每条边的长度，同时找出最长边并计算所有边的长度之和，最后用最长边的长度减去其余边长度之和再加 $1$ 得到结果。

#### RE_Prince的代码（循环查找）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, i, j, k, l, p;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> k;
        l = max(l, k), p += k;
    }
    cout << 2 * l - p + 1;
}
```
**核心实现思想**：同样是通过循环读入每条边的长度，找出最长边并计算所有边的长度之和，最后根据公式计算结果。

#### szh_AK_all的代码
```c
#include<iostream>
using namespace std;
int main()
{
    long long ans=0,tmp=0;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        long long x;
        cin>>x;
        if(x>ans)//用打擂台的方式记录最大值
            ans=x;
        tmp+=x;
    }
    tmp-=ans;//注意，计算完总和后要减掉最大值
    long long k=ans-tmp+1;
    if(k<0)
    k=0;
    cout<<k;
}
```
**核心实现思想**：通过循环读入每条边的长度，用打擂台的方式找出最长边并计算所有边的长度之和，计算结果时考虑了结果为负数的情况并将其置为 $0$。

### 最优关键思路或技巧
- **数学性质的运用**：利用凸多边形的性质，将问题转化为数学计算，通过简单的加减运算得到结果。
- **找最大值的方法**：可以使用循环查找、STL的 `max_element()` 函数或排序等方法找出最长边。

### 可拓展之处
同类型题目可能会有更多的限制条件，如要求多边形的边必须满足某些特定的关系，或者给定的边可以进行一定的操作（如切割、拼接等）。类似的算法套路就是利用几何图形的性质，将问题转化为数学计算，通过分析和推导得出结果。

### 推荐洛谷题目
- P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)
- P1067 [多项式输出](https://www.luogu.com.cn/problem/P1067)
- P1075 [质因数分解](https://www.luogu.com.cn/problem/P1075)

### 个人心得
题解中未包含个人心得。

---
处理用时：40.51秒