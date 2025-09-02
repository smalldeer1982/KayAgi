# 题目信息

# Restore Cube 

## 题目描述

Peter had a cube with non-zero length of a side. He put the cube into three-dimensional space in such a way that its vertices lay at integer points (it is possible that the cube's sides are not parallel to the coordinate axes). Then he took a piece of paper and wrote down eight lines, each containing three integers — coordinates of cube's vertex (a single line contains coordinates of a single vertex, each vertex is written exactly once), put the paper on the table and left. While Peter was away, his little brother Nick decided to play with the numbers on the paper. In one operation Nick could swap some numbers inside a single line (Nick didn't swap numbers from distinct lines). Nick could have performed any number of such operations.

When Peter returned and found out about Nick's mischief, he started recollecting the original coordinates. Help Peter restore the original position of the points or else state that this is impossible and the numbers were initially recorded incorrectly.

## 样例 #1

### 输入

```
0 0 0
0 0 1
0 0 1
0 0 1
0 1 1
0 1 1
0 1 1
1 1 1
```

### 输出

```
YES
0 0 0
0 0 1
0 1 0
1 0 0
0 1 1
1 0 1
1 1 0
1 1 1
```

## 样例 #2

### 输入

```
0 0 0
0 0 0
0 0 0
0 0 0
1 1 1
1 1 1
1 1 1
1 1 1
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 还原立方体

## 题目描述
彼得有一个边长非零的立方体。他将这个立方体放置在三维空间中，使得其顶点位于整点上（有可能立方体的边不与坐标轴平行）。然后，他拿了一张纸，写下八行内容，每行包含三个整数——立方体顶点的坐标（一行包含一个顶点的坐标，每个顶点恰好写一次），写完后把纸放在桌上就离开了。彼得不在的时候，他的弟弟尼克决定摆弄纸上的数字。在一次操作中，尼克可以交换某一行内的一些数字（尼克不会交换不同行的数字）。尼克可以进行任意次数这样的操作。

当彼得回来发现尼克的恶作剧后，他开始回忆原来的坐标。请帮助彼得恢复点的原始位置，否则说明这是不可能的，即最初记录的数字有误。

## 样例 #1
### 输入
```
0 0 0
0 0 1
0 0 1
0 0 1
0 1 1
0 1 1
0 1 1
1 1 1
```
### 输出
```
YES
0 0 0
0 0 1
0 1 0
1 0 0
0 1 1
1 0 1
1 1 0
1 1 1
```
## 样例 #2
### 输入
```
0 0 0
0 0 0
0 0 0
0 0 0
1 1 1
1 1 1
1 1 1
1 1 1
```
### 输出
```
NO
```
### 算法分类
搜索（枚举 + 剪枝）
### 综合分析与结论
该题解通过固定一个点，对其余7个点的坐标进行全排列（每个点有6种排列方式），并利用立方体顶点间距离的特性（顶点距离恰好有三种，且每种个数不超过12）进行判断和剪枝。整体思路清晰，利用特性剪枝有效减少了计算量。但代码使用Golang编写，对于熟悉C++的用户不太友好。
### 所选的题解
- **星级**：4星
  - **关键亮点**：利用立方体顶点距离特性进行剪枝，减少计算量。通过递归函数实现对所有可能排列的搜索。
### 重点代码及核心实现思想
```go
func dis(p, q [3]int64) int64 {
    return (p[0]-q[0])*(p[0]-q[0]) + (p[1]-q[1])*(p[1]-q[1]) + (p[2]-q[2])*(p[2]-q[2])
}

func main() {
    points := make([][3]int64, 8)
    for i := range points {
        Scan(&points[i][0], &points[i][1], &points[i][2])
    }
    var f func(int, map[int64]int8) bool
    f = func(i int, cntD map[int64]int8) bool {
        if i == 8 {
            return len(cntD) == 3
        }
        p := points[i]
    outer:
        for _, perm := range [][3]int{{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}} {
            cd := map[int64]int8{}
            for d, c := range cntD {
                cd[d] = c
            }
            points[i] = [3]int64{p[perm[0]], p[perm[1]], p[perm[2]]}
            for j := 0; j < i; j++ {
                d := dis(points[i], points[j])
                if cd[d]++; len(cd) > 3 || cd[d] > 12 {
                    continue outer
                }
            }
            if f(i+1, cd) {
                return true
            }
        }
        return false
    }
    if f(1, map[int64]int8{}) {
        Println("YES")
        for _, p := range points {
            Println(p[0], p[1], p[2])
        }
    } else {
        Print("NO")
    }
}
```
核心实现思想：`dis`函数计算两点间距离的平方。`main`函数中，`f`递归函数用于对每个点的坐标排列进行搜索，通过`cntD`记录不同距离出现的次数，利用距离种类不超过3种且每种不超过12次的特性进行剪枝，找到符合立方体顶点坐标的排列则返回`true`。
### 最优关键思路或技巧
利用立方体顶点距离的特性进行剪枝，在暴力枚举的基础上大大减少了不必要的计算，提高算法效率。
### 拓展与类似算法套路
此类题目属于空间几何与搜索结合的问题，类似套路有利用几何图形的特性（边长、角度、对称等）对搜索空间进行剪枝。同类型题可考虑一些在空间中判断图形位置关系或恢复图形原始状态的问题。
### 洛谷推荐题目
1. P1118 数字三角形：涉及递归与动态规划思想，类似本题对不同排列情况进行探索。（https://www.luogu.com.cn/problem/P1118）
2. P1433 吃奶酪：通过枚举不同路径解决问题，和本题枚举点的排列思路类似。（https://www.luogu.com.cn/problem/P1433）
3. P1731 营救：广度优先搜索问题，和本题一样需要对状态空间进行搜索。（https://www.luogu.com.cn/problem/P1731）
### 个人心得
无

---
处理用时：52.45秒