# 题目信息

# Box Fitting

## 题目描述

You are given $ n $ rectangles, each of height $ 1 $ . Each rectangle's width is a power of $ 2 $ (i. e. it can be represented as $ 2^x $ for some non-negative integer $ x $ ).

You are also given a two-dimensional box of width $ W $ . Note that $ W $ may or may not be a power of $ 2 $ . Moreover, $ W $ is at least as large as the width of the largest rectangle.

You have to find the smallest height of this box, such that it is able to fit all the given rectangles. It is allowed to have some empty space left in this box after fitting all the rectangles.

You cannot rotate the given rectangles to make them fit into the box. Moreover, any two distinct rectangles must not overlap, i. e., any two distinct rectangles must have zero intersection area.

See notes for visual explanation of sample input.

## 说明/提示

For the first test case in the sample input, the following figure shows one way to fit the given five rectangles into the 2D box with minimum height:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1498B/c4bb98ad37834f3e833cc55e38d3b77b700a7197.png)In the figure above, the number inside each rectangle is its width. The width of the 2D box is $ 16 $ (indicated with arrow below). The minimum height required for the 2D box in this case is $ 2 $ (indicated on the left).

In the second test case, you can have a minimum height of three by keeping two blocks (one each of widths eight and two) on each of the three levels.

## 样例 #1

### 输入

```
2
5 16
1 2 8 4 8
6 10
2 8 8 2 2 8```

### 输出

```
2
3```

# AI分析结果

### 题目内容重写
#### 题目描述
给定 $n$ 个高度为 $1$ 的矩形，每个矩形的宽度是 $2$ 的幂次（即可以表示为 $2^x$，其中 $x$ 是非负整数）。同时给定一个宽度为 $W$ 的二维盒子。注意，$W$ 不一定是 $2$ 的幂次，且 $W$ 至少与最大矩形的宽度一样大。

你需要找到这个盒子的最小高度，使得所有给定的矩形都能放入其中。允许盒子中有一些空余空间。矩形不能旋转，且任何两个不同的矩形不能重叠。

#### 说明/提示
对于第一个样例输入，下图展示了一种将五个矩形放入宽度为 $16$ 的二维盒子的方式，最小高度为 $2$：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1498B/c4bb98ad37834f3e833cc55e38d3b77b700a7197.png)

在图中，每个矩形内的数字表示其宽度。盒子的宽度为 $16$（下方箭头指示），最小高度为 $2$（左侧指示）。

在第二个样例中，最小高度为 $3$，通过在每个层放置两个矩形（一个宽度为 $8$，一个宽度为 $2$）来实现。

#### 样例输入
```
2
5 16
1 2 8 4 8
6 10
2 8 8 2 2 8
```

#### 样例输出
```
2
3
```

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是贪心算法，通过优先放置宽度较大的矩形来最小化盒子的高度。多个题解都采用了类似的贪心策略，但实现方式有所不同，主要区别在于数据结构的选用和具体实现细节。

### 精选题解
#### 1. 作者：SpeedStar (5星)
**关键亮点**：
- 使用优先队列（大顶堆）来维护每一行的剩余空间，确保每次都能选择剩余空间最大的行进行放置。
- 通过排序和优先队列的结合，实现了高效的贪心策略。

**核心代码**：
```cpp
priority_queue<int> q;
q.push(0);
int ans = 0;
rep(i, n) {
    int x = q.top(); q.pop();
    if (x < a[i]) {
        q.push(x);
        q.push(w - a[i]);
        ans++;
    }
    else q.push(x - a[i]);
}
```

#### 2. 作者：cunzai_zsy0531 (4星)
**关键亮点**：
- 使用 `multiset` 来维护每一行的剩余空间，通过二分查找快速找到合适的行进行放置。
- 强调了 `multiset` 的正确使用方法，避免了常见的错误。

**核心代码**：
```cpp
multiset<int> t;
multiset<int>::iterator it;	
for(int i=1;i<=n;++i){
    if(t.empty()){
        ++cnt;
        if(w!=a[i]) t.insert(w-a[i]);
        continue;
    }
    it=t.lower_bound(a[i]);
    if(it==t.end()){
        ++cnt;
        if(w!=a[i]) t.insert(w-a[i]);
    }
    else{
        int p=(*it);
        t.erase(it);
        if(p!=a[i]) t.insert(p-a[i]);
    }
}
```

#### 3. 作者：wawatime1 (4星)
**关键亮点**：
- 采用二分答案的方法，结合优先队列进行模拟，确保每次都能找到最小的高度。
- 通过二分搜索优化了贪心策略的实现。

**核心代码**：
```cpp
int calc (int h){
    priority_queue <int> q;
    for (int i = 1; i <= h; i++)
        q.push (w);
    for (int i = 1; i <= n; i++){
        if (q.top() < a[i] || q.empty()){
            return 0;
        }
        if (q.top() > a[i]){
            q.push (q.top() - a[i]);
            q.pop();
        } 
        else{
            q.pop();
        }
    }
    return 1;
}
```

### 最优关键思路
最优的思路是使用优先队列（大顶堆）来维护每一行的剩余空间，确保每次都能选择剩余空间最大的行进行放置。这种贪心策略能够有效地最小化盒子的高度。

### 可拓展之处
类似的问题可以扩展到三维空间中的装箱问题，或者考虑旋转矩形的情况。此外，可以进一步优化数据结构的选择，例如使用更高效的查找和插入操作。

### 推荐题目
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

### 个人心得摘录
- **cunzai_zsy0531**：强调了 `multiset` 的正确使用方法，避免了常见的错误，提醒了在 `multiset` 中二分查找时应该使用 `t.lower_bound(a[i])` 而不是 `lower_bound(t.begin(),t.end(),a[i])`。
- **SpeedStar**：通过优先队列的实现，展示了如何高效地维护剩余空间，确保每次都能选择最优的行进行放置。

---
处理用时：42.66秒