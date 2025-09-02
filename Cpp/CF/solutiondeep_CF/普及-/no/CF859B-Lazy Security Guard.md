# 题目信息

# Lazy Security Guard

## 题目描述

Your security guard friend recently got a new job at a new security company. The company requires him to patrol an area of the city encompassing exactly $ N $ city blocks, but they let him choose which blocks. That is, your friend must walk the perimeter of a region whose area is exactly $ N $ blocks. Your friend is quite lazy and would like your help to find the shortest possible route that meets the requirements. The city is laid out in a square grid pattern, and is large enough that for the sake of the problem it can be considered infinite.

## 说明/提示

Here are some possible shapes for the examples:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF859B/5e7ebb69b8e66ba58196d654a3513a2ca92c6a2a.png)

## 样例 #1

### 输入

```
4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
11
```

### 输出

```
14
```

## 样例 #3

### 输入

```
22
```

### 输出

```
20
```

# AI分析结果

### 题目中文重写
# 懒惰的保安

## 题目描述
你的保安朋友最近在一家新的保安公司找到了一份新工作。公司要求他巡逻城市中恰好包含 $N$ 个街区的区域，但允许他选择具体是哪些街区。也就是说，你的朋友必须沿着一个面积恰好为 $N$ 个街区的区域的周边行走。你的朋友非常懒惰，希望你能帮他找到满足要求的最短路线。城市呈正方形网格布局，并且足够大，为了解决这个问题，可以将其视为无限大。

## 说明/提示
以下是一些示例的可能形状：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF859B/5e7ebb69b8e66ba58196d654a3513a2ca92c6a2a.png)

## 样例 #1
### 输入
```
4
```
### 输出
```
8
```

## 样例 #2
### 输入
```
11
```
### 输出
```
14
```

## 样例 #3
### 输入
```
22
```
### 输出
```
20
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于数学原理：在面积一定的情况下，正方形的周长小于长方形的周长，所以要尽可能地将 $n$ 个正方形拼成接近正方形的形状。各题解主要通过计算 $\sqrt{n}$ 并向下取整得到短边长度，再根据 $n$ 是否能被短边整除来分类讨论长边长度，进而计算周长。

### 所选题解
- **cff_0102（4星）**：关键亮点在于思路清晰，通过分类讨论不同情况得出通用公式，代码实现简洁明了。
- **TLEWA（4星）**：关键亮点是通过贪心思想，直接计算短边和长边，利用向上取整处理不能整除的情况，思路直观。
- **翼德天尊（4星）**：关键亮点是对长边不能整除的情况进行分类讨论，逻辑清晰，代码简洁。

### 重点代码
#### cff_0102
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int n;cin>>n;
    int s=sqrt(n);
    if(s*s==n) s=s*4;
    else if(s*(s+1)<n) s=s*4+4;
    else s=s*4+2;
    cout<<s;
    return 0;
}
```
核心实现思想：先计算 $\sqrt{n}$ 并向下取整得到 $s$，然后根据 $n$ 与 $s^2$ 和 $s\times(s + 1)$ 的大小关系分类讨论，得出不同情况下的周长。

#### TLEWA
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    int sn=sqrt(n);
    int cn=n/sn+(bool)(n%sn); 
    cout << (sn+cn)*2;
    return 0;
}
```
核心实现思想：计算 $\sqrt{n}$ 并向下取整得到短边 $sn$，通过 $n/sn+(bool)(n\%sn)$ 向上取整得到长边 $cn$，最后计算周长。

#### 翼德天尊
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int main(){
    scanf("%d",&n);
    a=sqrt(n),b=n/a;
    if (n%a) printf("%d\n",(a+b+1)*2);
    else printf("%d\n",(a+b)*2);
    return 0;
}
```
核心实现思想：计算 $\sqrt{n}$ 并向下取整得到短边 $a$，$n/a$ 得到长边 $b$，根据 $n$ 是否能被 $a$ 整除分类讨论计算周长。

### 关键思路或技巧
- 利用数学结论：面积一定时，正方形周长最小，尽量将图形拼成接近正方形的形状。
- 通过计算 $\sqrt{n}$ 并向下取整得到短边长度，再根据整除情况确定长边长度。

### 拓展思路
同类型题目通常会围绕几何图形的面积和周长关系展开，可能会改变图形的形状或增加一些限制条件。解题的关键在于抓住面积和周长的关系，通过数学推导和分类讨论来解决问题。

### 推荐题目
- [P1421 小玉买文具](https://www.luogu.com.cn/problem/P1421)
- [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
- [P1000 超级玛丽游戏](https://www.luogu.com.cn/problem/P1000)

### 个人心得
mcDinic提到“看到题解区的大佬千篇一律，都简单分析做了一下，核心代码仅三行，蒟蒻打算给题解增加些新鲜的血液（虽说运行效率低点，但足以通过本题）”，总结为希望提供不同思路的题解，即使效率可能不高，但也能为解题提供新的方向。 

---
处理用时：33.95秒