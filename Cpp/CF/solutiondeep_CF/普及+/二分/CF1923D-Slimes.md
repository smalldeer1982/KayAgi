# 题目信息

# Slimes

## 题目描述

There are $ n $ slimes placed in a line. The slimes are numbered from $ 1 $ to $ n $ in order from left to right. The size of the $ i $ -th slime is $ a_i $ .

Every second, the following happens: exactly one slime eats one of its neighbors and increases its size by the eaten neighbor's size. A slime can eat its neighbor only if it is strictly bigger than this neighbor. If there is no slime which is strictly bigger than one of its neighbors, the process ends.

For example, suppose $ n = 5 $ , $ a = [2, 2, 3, 1, 4] $ . The process can go as follows:

- first, the $ 3 $ -rd slime eats the $ 2 $ -nd slime. The size of the $ 3 $ -rd slime becomes $ 5 $ , the $ 2 $ -nd slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 1 $ -st slime (they are neighbors since the $ 2 $ -nd slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 7 $ , the $ 1 $ -st slime is eaten.
- then, the $ 5 $ -th slime eats the $ 4 $ -th slime. The size of the $ 5 $ -th slime becomes $ 5 $ , the $ 4 $ -th slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 5 $ -th slime (they are neighbors since the $ 4 $ -th slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 12 $ , the $ 5 $ -th slime is eaten.

For each slime, calculate the minimum number of seconds it takes for this slime to be eaten by another slime (among all possible ways the process can go), or report that it is impossible.

## 样例 #1

### 输入

```
4
4
3 2 4 2
3
1 2 3
5
2 2 3 1 1
7
4 2 3 6 1 1 8```

### 输出

```
2 1 2 1 
1 1 -1 
2 1 -1 1 2 
2 1 1 3 1 1 4```

# AI分析结果



# Slimes

## 题目描述

有 $n$ 个史莱姆排成一列。史莱姆从左到右编号为 $1$ 到 $n$。第 $i$ 个史莱姆的大小为 $a_i$。

每秒会发生以下事件：恰好一个史莱姆吃掉它的邻居之一，并将其大小增加被吃邻居的大小。只有当史莱姆严格大于其邻居时才能吃掉它。若不存在严格大于任一邻居的史莱姆，过程结束。

对于每个史莱姆，计算它被吃掉所需的最短时间（秒数），若不可能被吃掉则输出 `-1`。

## 样例 #1

### 输入

```
4
4
3 2 4 2
3
1 2 3
5
2 2 3 1 1
7
4 2 3 6 1 1 8```

### 输出

```
2 1 2 1 
1 1 -1 
2 1 -1 1 2 
2 1 1 3 1 1 4```

---

## 题解综合分析

### 关键思路总结
1. **二分查找+前缀和**：对每个史莱姆，分别向左右两侧寻找能合并成足够大的连续区间
2. **处理全等区间**：通过预处理极长相同值区间，确保合并可行性
3. **特判相邻情况**：若直接存在更大邻居，时间即为1

### 高星题解推荐

#### 题解作者：Luzhuoyuan（★★★★★）
**核心亮点**：  
- 预处理前缀和`pr`/后缀和`su`加速区间和计算
- 预处理`l[i]`/`r[i]`记录连续相同值的长度
- 使用逆向二分技巧处理单调递减区间
- 代码简洁高效（时间复杂度O(n logn)）

**关键代码解析**：
```cpp
// 预处理连续相同值长度
for(int i=1;i<=n;i++) 
    l[i] = (a[i]==a[i-1] ? l[i-1]+1 : 1);
for(int i=n;i>=1;i--)
    r[i] = (a[i]==a[i+1] ? r[i+1]+1 : 1);

// 左边界二分（反向单调）
lower_bound(su+1, su+1+n, su[i]+a[i], greater<int>())
// 右边界二分（正向单调）
upper_bound(pr+1, pr+1+n, pr[i]+a[i])
```

#### 题解作者：kczw（★★★★☆）
**核心亮点**：
- 维护相邻差绝对值前缀和`c`数组
- 通过判断`c`的区间和是否为0检测全等区间
- 双重二分框架清晰易理解

**关键代码片段**：
```cpp
// 判断左区间是否合法
if(pre[i-1]-pre[mid-1]<=a[i] || (c[i-1]-c[mid]==0 && i-1!=mid))
```

#### 题解作者：AtomAlpaca（★★★★☆）
**核心亮点**：
- 使用ST表维护区间全等性判断
- 合并时动态维护区间相等性
- 代码结构模块化，便于维护

**关键ST表实现**：
```cpp
void build(){
    for(int i=1;i<=n;i++) st[0][i]=true;
    for(int j=1;(1<<j)<=n;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[j][i] = st[j-1][i] && st[j-1][i+(1<<(j-1))] 
                      && (a[i] == a[i+(1<<j)-1]);
}
```

---

## 最优思路提炼
1. **预处理结构**：同时维护前缀和与极长相同值区间信息
2. **二分方向控制**：左侧用反向二分（greater比较器），右侧用标准二分
3. **合法性校验**：在总和足够大的前提下，必须存在可合并的异值区间

## 拓展建议
1. 相似题目练习：
   - 洛谷P1886（滑动窗口极值，二分思想）
   - 洛谷P1712（区间覆盖问题，前缀和+双指针）
   - 洛谷P1496（离散化+区间合并，处理连续区间）

2. 调试技巧：
   - 构造全等序列的测试用例（如`2 2 2 1`）
   - 验证边界条件（如第一个/最后一个元素）

## 心得摘录
> "被hack数据`2 2 2 2 1`卡住后意识到，必须严格判断区间是否存在异值元素。即使总和足够大，若全等也无法合并。" —— 2huk  
> "二分时不仅要考虑总和条件，还要保证区间内存在合并可能性，这需要预处理极长相同值区间。" —— AtomAlpaca

---
处理用时：56.71秒