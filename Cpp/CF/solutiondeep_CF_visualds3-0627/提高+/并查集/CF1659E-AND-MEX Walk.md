# 题目信息

# AND-MEX Walk

## 题目描述

There is an undirected, connected graph with $ n $ vertices and $ m $ weighted edges. A walk from vertex $ u $ to vertex $ v $ is defined as a sequence of vertices $ p_1,p_2,\ldots,p_k $ (which are not necessarily distinct) starting with $ u $ and ending with $ v $ , such that $ p_i $ and $ p_{i+1} $ are connected by an edge for $ 1 \leq i < k $ .

We define the length of a walk as follows: take the ordered sequence of edges and write down the weights on each of them in an array. Now, write down the bitwise AND of every nonempty prefix of this array. The length of the walk is the MEX of all these values.

More formally, let us have $ [w_1,w_2,\ldots,w_{k-1}] $ where $ w_i $ is the weight of the edge between $ p_i $ and $ p_{i+1} $ . Then the length of the walk is given by $ \mathrm{MEX}(\{w_1,\,w_1\& w_2,\,\ldots,\,w_1\& w_2\& \ldots\& w_{k-1}\}) $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Now you must process $ q $ queries of the form u v. For each query, find the minimum possible length of a walk from $ u $ to $ v $ .

The MEX (minimum excluded) of a set is the smallest non-negative integer that does not belong to the set. For instance:

- The MEX of $ \{2,1\} $ is $ 0 $ , because $ 0 $ does not belong to the set.
- The MEX of $ \{3,1,0\} $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the set, but $ 2 $ does not.
- The MEX of $ \{0,3,1,2\} $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the set, but $ 4 $ does not.

## 说明/提示

The following is an explanation of the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1659E/e80c1510937e2e4c165cad1b2b45b357811161d4.png)The graph in the first example.Here is one possible walk for the first query:

 $ $$$1 \overset{5}{\rightarrow} 3 \overset{3}{\rightarrow} 2 \overset{1}{\rightarrow} 1 \overset{5}{\rightarrow} 3 \overset{1}{\rightarrow} 4 \overset{2}{\rightarrow} 5. $ $ </p><p>The array of weights is  $ w=\[5,3,1,5,1,2\] $ . Now if we take the bitwise AND of every prefix of this array, we get the set  $ \\{5,1,0\\} $ . The MEX of this set is  $ 2$$$. We cannot get a walk with a smaller length (as defined in the statement).

## 样例 #1

### 输入

```
6 7
1 2 1
2 3 3
3 1 5
4 5 2
5 6 4
6 4 6
3 4 1
3
1 5
1 2
5 3```

### 输出

```
2
0
1```

## 样例 #2

### 输入

```
9 8
1 2 5
2 3 11
3 4 10
3 5 10
5 6 2
5 7 1
7 8 5
7 9 5
10
5 7
2 5
7 1
6 4
5 2
7 6
4 1
6 2
4 7
2 8```

### 输出

```
0
0
2
0
0
2
1
0
1
1```

# AI分析结果



## 唯一算法分类  
**并查集（位运算应用）**

---

## 综合分析与结论  
**核心思路：**  
1. 答案只能是0、1、2  
2. 答案为0：存在某一位二进制所有边权为1的路径  
3. 答案为1：存在前半段边权按位与>1、后半段有偶数边权的路径  
4. 答案为2：前两种情况均不满足  

**关键实现：**  
- 按位建立30个并查集（对应二进制位）  
- 预处理各二进制位的连通性（判断答案0）  
- 引入虚点连接所有偶数边权的节点（判断答案1）  
- 通过标记数组快速判定是否存在满足条件的路径  

**可视化设计要点：**  
1. **像素化并查集合并动画**  
   - 用不同颜色方块表示不同二进制位的并查集  
   - 动态展示边权按位分类后连通块的合并过程  
2. **虚点连接高亮**  
   - 红色闪烁特效显示偶数边权连接的虚点  
   - 自动步进展示如何通过虚点判断答案1  
3. **8位音效反馈**  
   - 合并成功时播放"滴"声  
   - 找到答案时播放"通关"音效  

---

## 题解清单（≥4星）  
### 1. Binary_Lee（5星）  
**亮点：**  
- 分步骤推导证明答案范围  
- 结构体封装多并查集，代码清晰  
- 虚点合并实现巧妙  

### 2. jiangtaizhe001（4星）  
**亮点：**  
- 简洁高效的预处理方案  
- 使用位运算优化标记数组  

### 3. _Spectator_（4星）  
**亮点：**  
- 完整注释和变量命名规范  
- 通过控制面板实现多条件判断  

---

## 核心代码实现  
**并查集结构体 + 虚点处理**  
```cpp
struct DSU {
    int fa[100005];
    DSU() { for(int i=0;i<=1e5;i++) fa[i]=i; }
    int find(int x) { return x==fa[x]?x:fa[x]=find(fa[x]); }
    void merge(int x,int y) { fa[find(x)]= find(y); }
    bool query(int x,int y) { return find(x)==find(y); }
}x[35],y[35]; // x处理答案0，y处理答案1

// 预处理偶数边权虚点连接
for(int i=1;i<30;i++) {
    y[i] = x[i];
    for(int j=1;j<=n;j++) 
        if(标记为偶数的节点) y[i].merge(j,0);
}
```

---

## 相似题目推荐  
1. CF915F（并查集位运算应用）  
2. P4185（连通性分类讨论）  
3. CF963B（位运算路径特性）  

---

## 可视化算法演示  
**步骤分解：**  
1. 初始化30个并查集网格  
2. 逐条读入边权：  
   - 蓝色方块：当前处理的二进制位  
   - 绿色连线：边权该位为1时建立连接  
3. 虚点连接阶段：  
   - 红色脉冲特效显示偶数边权节点  
   - 黄色连线连接虚点与普通节点  
4. 查询阶段：  
   - 紫色路径显示连通性检查  
   - 失败时显示灰色阻断特效  

**交互功能：**  
- WASD控制视角平移  
- 空格键单步执行  
- F键加速动画  

---

## 总结与扩展  
**关键技巧：**  
- 位运算特性与并查集结合处理路径约束  
- 虚点技巧简化复杂条件判断  
- 预处理标记数组优化查询效率  

**应用场景：**  
- 涉及二进制位约束的连通性问题  
- 需要快速判断多条件路径存在性的场景  
- 带特殊边权限制的最优化路径问题

---
处理用时：59.79秒