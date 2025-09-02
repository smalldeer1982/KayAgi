# 题目信息

# Friends and Presents

## 题目描述

You have two friends. You want to present each of them several positive integers. You want to present $ cnt_{1} $ numbers to the first friend and $ cnt_{2} $ numbers to the second friend. Moreover, you want all presented numbers to be distinct, that also means that no number should be presented to both friends.

In addition, the first friend does not like the numbers that are divisible without remainder by prime number $ x $ . The second one does not like the numbers that are divisible without remainder by prime number $ y $ . Of course, you're not going to present your friends numbers they don't like.

Your task is to find such minimum number $ v $ , that you can form presents using numbers from a set $ 1,2,...,v $ . Of course you may choose not to present some numbers at all.

A positive integer number greater than 1 is called prime if it has no positive divisors other than 1 and itself.

## 说明/提示

In the first sample you give the set of numbers $ {1,3,5} $ to the first friend and the set of numbers $ {2} $ to the second friend. Note that if you give set $ {1,3,5} $ to the first friend, then we cannot give any of the numbers $ 1 $ , $ 3 $ , $ 5 $ to the second friend.

In the second sample you give the set of numbers $ {3} $ to the first friend, and the set of numbers $ {1,2,4} $ to the second friend. Thus, the answer to the problem is $ 4 $ .

## 样例 #1

### 输入

```
3 1 2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 3 2 3
```

### 输出

```
4
```

# AI分析结果

### 题目内容
# 朋友与礼物

## 题目描述
你有两个朋友。你想给他们每人送几个正整数。你想给第一个朋友送 $cnt_{1}$ 个数，给第二个朋友送 $cnt_{2}$ 个数。此外，你希望所有送出的数字都不同，这也意味着没有数字会同时送给两个朋友。

另外，第一个朋友不喜欢能被质数 $x$ 整除的数字。第二个朋友不喜欢能被质数 $y$ 整除的数字。当然，你不会送朋友们他们不喜欢的数字。

你的任务是找到最小的数字 $v$，使得你可以用集合 $1,2,\cdots,v$ 中的数字来准备礼物。当然，你也可以选择不送某些数字。

大于1的正整数如果除了1和它自身外没有其他正因数，则称为质数。

## 说明/提示
在第一个样例中，你给第一个朋友数字集合 $\{1,3,5\}$，给第二个朋友数字集合 $\{2\}$。注意，如果你给第一个朋友集合 $\{1,3,5\}$，那么我们不能把数字 $1$、$3$、$5$ 中的任何一个给第二个朋友。

在第二个样例中，你给第一个朋友数字集合 $\{3\}$，给第二个朋友数字集合 $\{1,2,4\}$。因此，问题的答案是 $4$。

## 样例 #1
### 输入
```
3 1 2 3
```
### 输出
```
5
```
## 样例 #2
### 输入
```
1 3 2 3
```
### 输出
```
4
```

### 算法分类
二分

### 综合分析与结论
这些题解主要围绕如何找到最小的 $v$ 展开，思路可分为两类：
1. **二分查找**：通过二分查找确定 $v$ 的最小值，关键在于设计合理的判断条件，检查当前二分的中间值 $mid$ 是否满足给两个朋友分配数字的要求。
2. **公式推导**：利用数论相关知识，如容斥原理和下取整性质，直接推导出 $v$ 需满足的不等式，进而得出 $v$ 的取值。

解决难点在于准确分析出满足条件的数字数量关系，无论是通过二分的判断条件，还是直接公式推导。

### 所选的题解
- **作者：enyyyyyyy (5星)**
  - **关键亮点**：思路清晰，代码简洁，直接使用二分查找，check函数准确概括判断条件。
  - **核心代码**：
```cpp
lint n, m, x, y,mid,l=1,r=2e9,ans;
bool check() {
    return mid - mid / x >= n && mid - mid / y >= m && mid - mid / (x * y) >= n + m;
}
int main() {
    n=read(),m=read(),x=read(),y=read();
    while (l<=r) {
        mid = (l + r) >> 1;
        if (check()) r = mid-1,ans=mid;
        else l = mid+1;
    }
    print(ans);
    return 0;
}
```
  - **核心思想**：通过二分查找，每次用check函数判断中间值mid是否满足条件，更新左右边界，最终得到最小的满足条件的ans。

- **作者：囧仙 (4星)**
  - **关键亮点**：不仅给出二分思路，还详细证明了满足三个条件的 $V$ 必定可以分成符合要求的两堆，并通过公式推导得出 $V$ 的取值。
  - **核心代码**：
```cpp
int a,b,x,y,v;
int main(){
    scanf("%d%d%d%d",&a,&b,&x,&y);
    v=max(v,(int)floor((double)(a+b-1)*x*y/(x*y-1)));
    v=max(v,(int)floor((double)(a-1)*x/(x-1)));
    v=max(v,(int)floor((double)(b-1)*y/(y-1)));
    printf("%d\n",v+1);
    return 0;
}
```
  - **核心思想**：通过整理式子和下取整性质推导出 $v$ 需满足的不等式，取最大值并加1得到结果。

- **作者：离散小波变换° (4星)**
  - **关键亮点**：挑战用公式直接推导，利用容斥原理和下取整结论，详细推导 $v$ 满足的条件。
  - **核心代码**：无（推导过程复杂，未给出直接可运行核心代码）
  - **核心思想**：设不含因子 $x$、$y$ 的集合，利用容斥原理得出集合元素个数关系，结合下取整结论推导出 $v$ 满足的不等式，取最大值的上取整。

### 最优关键思路或技巧
二分查找思路简洁明了，通过合理设计check函数判断条件，高效找到最小的 $v$ 值。公式推导则更深入理解数字间的数学关系，利用数论知识直接得出结果。两者都体现了对数字规律的把握和巧妙运用。

### 可拓展之处
同类型题通常围绕数论与集合分配问题，类似算法套路包括利用数论性质（如整除、容斥原理）分析条件，通过二分查找或公式推导求解。

### 洛谷相似题目推荐
1. P2678 [NOIP2015 普及组] 跳石头，二分查找应用，判断条件与距离相关。
2. P1182 数列分段 Section II，二分查找合适的分段最大值，判断条件与分段和有关。
3. P2249 查找，通过二分查找满足条件的数值。 

---
处理用时：64.88秒