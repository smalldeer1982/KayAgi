# 题目信息

# Two Seals

## 题目描述

One very important person has a piece of paper in the form of a rectangle $ a×b $ .

Also, he has $ n $ seals. Each seal leaves an impression on the paper in the form of a rectangle of the size $ x_{i}×y_{i} $ . Each impression must be parallel to the sides of the piece of paper (but seal can be rotated by 90 degrees).

A very important person wants to choose two different seals and put them two impressions. Each of the selected seals puts exactly one impression. Impressions should not overlap (but they can touch sides), and the total area occupied by them should be the largest possible. What is the largest area that can be occupied by two seals?

## 说明/提示

In the first example you can rotate the second seal by 90 degrees. Then put impression of it right under the impression of the first seal. This will occupy all the piece of paper.

In the second example you can't choose the last seal because it doesn't fit. By choosing the first and the third seals you occupy the largest area.

In the third example there is no such pair of seals that they both can fit on a piece of paper.

## 样例 #1

### 输入

```
2 2 2
1 2
2 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 10 9
2 3
1 1
5 10
9 11
```

### 输出

```
56
```

## 样例 #3

### 输入

```
3 10 10
6 6
7 7
20 5
```

### 输出

```
0
```

# AI分析结果



# Two Seals

## 题目描述

一位重要人物有一张 $a×b$ 的矩形纸张。

他有 $n$ 个印章，每个印章能留下尺寸为 $x_i×y_i$ 的矩形印记（可旋转90度使用）。印记必须与纸张边缘平行。

需要选择两个不同的印章，使得它们不重叠地占据最大面积。求这个最大面积值。

## 说明/提示

样例1中旋转第二个印章后可以铺满整张纸，样例2中无法使用最后一个印章，样例3则没有符合条件的组合。

## 样例 #1

### 输入
```
2 2 2
1 2
2 1
```

### 输出
```
4
```

---

**算法分类**: 枚举

---

### 题解综合分析

各题解核心思路均为枚举所有印章对，考虑旋转后的四种排列组合，通过以下两种方式验证可行性：
1. 横向排列：两印章长之和 ≤ 纸长，且最大宽 ≤ 纸宽
2. 纵向排列：两印章宽之和 ≤ 纸宽，且最大长 ≤ 纸长

#### 关键优化点
1. 旋转处理技巧：通过交换x/y或循环处理旋转（避免手动枚举所有旋转情况）
2. 剪枝优化：部分题解使用j=i+1避免重复枚举
3. 条件合并：将纸的a/b互换判断合并到同一条件式

---

### 高星题解推荐

#### 1. 作者：yuheng_wang080904（⭐⭐⭐⭐⭐）
**核心亮点**：
- 通过双重循环处理旋转，代码简洁高效
- 将纸张的a/b互换判断合并到同一条件式
- 时间复杂度严格保持O(n²)
```cpp
for(int c1=0;c1<2;c1++,swap(x[i],y[i])) { // 处理第一个印章旋转
    for(int c2=0;c2<2;c2++,swap(x[j],y[j])) { // 处理第二个印章旋转
        if(x[i]+x[j]<=a&&max(y[i],y[j])<=b || // 横向排列条件
           x[i]+x[j]<=b&&max(y[i],y[j])<=a)  // 考虑纸张旋转情况
            ans = max(...);
    }
}
```

#### 2. 作者：Cute__yhb（⭐⭐⭐⭐）
**核心亮点**：
- 显式分离横竖排列条件判断
- 使用3-xi技巧简化旋转维度访问
- 变量命名清晰易读
```cpp
for(int xi=1;xi<=2;xi++){ // 第一个印章的旋转维度
    int x1=x[i][xi], y1=x[i][3-xi];
    for(int yi=1;yi<=2;yi++){ // 第二个印章的旋转维度
        int x2=x[j][yi], y2=x[j][3-yi];
        if(横向排列 || 纵向排列)
            maxx = max(...);
    }
}
```

#### 3. 作者：___cjy__（⭐⭐⭐⭐）
**核心亮点**：
- 显式列出四种组合情况
- 封装check函数提升可读性
- 包含详细的排列示意图说明
```cpp
bool check(int x, int y) { // 合并纸张方向判断
    return (x<=a&&y<=b) || (x<=b&&y<=a);
}
```

---

### 同类题目推荐
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 二维空间枚举覆盖
2. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059) - 数据枚举与去重
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219) - 二维空间排列组合验证

---

### 关键技巧总结
1. **旋转处理**：通过交换x/y值或循环处理旋转，比手动枚举更简洁
2. **条件合并**：将纸张的a/b互换情况合并判断，减少代码量
3. **剪枝优化**：使用j=i+1避免重复枚举(i,j)和(j,i)
4. **维度分离**：将长宽判断拆分为独立条件式，便于逻辑组合

---

### 题解心得摘录
> "通过双重循环处理旋转，将4种旋转情况简化为2层循环，极大减少代码量" —— yuheng_wang080904  
> "意识到印章紧挨摆放最优，将问题简化为两种排列方式的条件判断" —— ___cjy__  
> "最初忘记处理纸张本身的旋转情况（a/b互换），导致部分测试点失败" —— TainityAnle

---
处理用时：51.96秒