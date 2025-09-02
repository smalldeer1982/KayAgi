# 题目信息

# Imbalanced Array

## 题目描述

You are given an array $ a $ consisting of $ n $ elements. The imbalance value of some subsegment of this array is the difference between the maximum and minimum element from this segment. The imbalance value of the array is the sum of imbalance values of all subsegments of this array.

For example, the imbalance value of array $ [1,4,1] $ is $ 9 $ , because there are $ 6 $ different subsegments of this array:

- $ [1] $ (from index $ 1 $ to index $ 1 $ ), imbalance value is $ 0 $ ;
- $ [1,4] $ (from index $ 1 $ to index $ 2 $ ), imbalance value is $ 3 $ ;
- $ [1,4,1] $ (from index $ 1 $ to index $ 3 $ ), imbalance value is $ 3 $ ;
- $ [4] $ (from index $ 2 $ to index $ 2 $ ), imbalance value is $ 0 $ ;
- $ [4,1] $ (from index $ 2 $ to index $ 3 $ ), imbalance value is $ 3 $ ;
- $ [1] $ (from index $ 3 $ to index $ 3 $ ), imbalance value is $ 0 $ ;

You have to determine the imbalance value of the array $ a $ .

## 样例 #1

### 输入

```
3
1 4 1
```

### 输出

```
9
```

# AI分析结果

### 题目内容
# 不平衡数组

## 题目描述
给定一个由 $n$ 个元素组成的数组 $a$ 。该数组中某个子段的不平衡值是该子段中最大元素与最小元素的差值。数组的不平衡值是该数组所有子段的不平衡值之和。

例如，数组 $[1, 4, 1]$ 的不平衡值为 $9$ ，因为该数组有 $6$ 个不同的子段：
- $[1]$ （从索引 $1$ 到索引 $1$ ），不平衡值为 $0$ ；
- $[1, 4]$ （从索引 $1$ 到索引 $2$ ），不平衡值为 $3$ ；
- $[1, 4, 1]$ （从索引 $1$ 到索引 $3$ ），不平衡值为 $3$ ；
- $[4]$ （从索引 $2$ 到索引 $2$ ），不平衡值为 $0$ ；
- $[4, 1]$ （从索引 $2$ 到索引 $3$ ），不平衡值为 $3$ ；
- $[1]$ （从索引 $3$ 到索引 $3$ ），不平衡值为 $0$ 。

你需要确定数组 $a$ 的不平衡值。

## 样例 #1
### 输入
```
3
1 4 1
```
### 输出
```
9
```

### 算法分类
数学

### 题解综合分析与结论
这些题解主要围绕如何优化计算数组不平衡值展开。大部分题解思路是将直接枚举区间求不平衡值的高复杂度方法，转化为考虑每个元素对不平衡值的贡献。关键在于确定每个元素作为最大值或最小值时，所在区间的左右边界，进而利用乘法原理计算贡献。不同题解在实现确定边界的方法上有所不同，主要有单调栈、并查集、分治以及树状数组等方式。

### 所选的题解
- **作者：Velix (赞：17)  星级：5星  关键亮点**：思路清晰，详细阐述从暴力解法到优化思路的过程，利用单调栈分别求出每个元素作为最大值和最小值时左右边界的位置，乘法原理计算贡献，代码实现简洁明了。
  ```cpp
  // 核心代码片段
  for(int i=1;i<=n;i++)
  {
      if(a[i]>a[sta[h]])sta[++h]=i,mil[i]=i-1;
      else
      {
          while(a[i]<a[sta[h]])h--;
          mil[i]=sta[h];
          sta[++h]=i;
      }
  }
  // 后续类似代码计算其他边界情况
  for(int i=1;i<=n;i++)
      ans+=1ll*a[i]*(1ll*(i-mxl[i])*(mxr[i]-i)-1ll*(i-mil[i])*(mir[i]-i));
  ```
  **核心实现思想**：通过单调栈确定每个元素作为最值时的左右边界，进而计算每个元素对答案的贡献并累加。

- **作者：Provicy (赞：9)  星级：5星  关键亮点**：简洁清晰地阐述思路，从朴素枚举区间转换到考虑每个位置数的贡献，利用单调栈求出每个数作为最大值和最小值时所在区间的边界，乘法原理统计答案，代码简洁且注释详细。
  ```cpp
  // 核心代码片段
  for(ri int i=1;i<=n;i++)
  {
      while(tp&&a[i]>=a[sta[tp]]) qr[sta[tp--]]=i-1;
      ql[i]=sta[tp]+1; sta[++tp]=i;
  }
  while(tp) qr[sta[tp--]]=n;
  for(ri int i=1;i<=n;i++) ans+=(i-ql[i]+1)*(qr[i]-i+1)*a[i];
  // 后续类似代码计算最小值情况
  ```
  **核心实现思想**：借助单调栈获取每个数作为最值的区间边界，根据乘法原理计算贡献得出答案。

- **作者：zhengrunzhe (赞：6)  星级：4星  关键亮点**：采用增量法，通过维护两个单调栈（分别用于最大值和最小值）实时更新每个位置到末尾的最大最小值，在插入新元素时，根据单调栈的弹出情况更新答案，时空复杂度最优。
  ```cpp
  // 核心代码片段
  inline const void insert(const int k)
  {
      for (;top1&&a[k]>=a[s1[top1]];top1--)sum-=1ll*(s1[top1]-s1[top1-1])*a[s1[top1]];
      for (;top2&&a[k]<=a[s2[top2]];top2--)sum+=1ll*(s2[top2]-s2[top2-1])*a[s2[top2]];
      if (k>1)
          sum+=1ll*(k-1-s1[top1])*a[k],
          sum-=1ll*(k-1-s2[top2])*a[k];
      s1[++top1]=k;s2[++top2]=k;
      ans+=sum;
  }
  ```
  **核心实现思想**：利用单调栈的性质，在插入新元素时，通过调整栈内元素更新区间最值及答案。

### 最优关键思路或技巧
将计算所有子段不平衡值之和转化为计算每个元素作为最大值或最小值时对答案的贡献，利用单调栈高效确定每个元素作为最值时所在区间的左右边界，这种思路有效降低了时间复杂度。

### 可拓展之处
此类题目属于统计区间最值相关问题，类似套路是将对区间的操作转化为对单个元素的贡献计算。常见变形有改变统计的目标值（如求子区间和与最值的关系等），或者改变约束条件（如限定子区间长度等）。

### 相似知识点洛谷题目
- [P1950 长方形](https://www.luogu.com.cn/problem/P1950)：通过枚举点对，利用单调栈优化计算满足条件的长方形数量。
- [P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)：基础的单调栈模板题，用于熟悉单调栈的应用。
- [P4185 [USACO18JAN]MooTube G](https://www.luogu.com.cn/problem/P4185)：结合图论与单调栈，处理路径上的最值问题。 

---
处理用时：62.95秒