# 题目信息

# Sum of Medians

## 题目描述

In one well-known algorithm of finding the $ k $ -th order statistics we should divide all elements into groups of five consecutive elements and find the median of each five. A median is called the middle element of a sorted array (it's the third largest element for a group of five). To increase the algorithm's performance speed on a modern video card, you should be able to find a sum of medians in each five of the array.

A sum of medians of a sorted $ k $ -element set $ S={a_{1},a_{2},...,a_{k}} $ , where $ a_{1}&lt;a_{2}&lt;a_{3}&lt;...&lt;a_{k} $ , will be understood by as

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/ade3397df6e8978ddadfc100b4ccb88beefd1e3f.png)The ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) operator stands for taking the remainder, that is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) stands for the remainder of dividing $ x $ by $ y $ .

To organize exercise testing quickly calculating the sum of medians for a changing set was needed.

## 样例 #1

### 输入

```
6
add 4
add 5
add 1
add 2
add 3
sum
```

### 输出

```
3
```

## 样例 #2

### 输入

```
14
add 1
add 7
add 2
add 5
sum
add 6
add 8
add 9
add 3
add 4
add 10
sum
del 1
sum
```

### 输出

```
5
11
13
```

# AI分析结果



## 算法分类
**线段树/平衡树（数据结构）**

---

## 题解思路与核心难点

### 核心算法逻辑
1. **动态维护模5余数和**：所有解法核心都在维护排序后元素的下标模5余3的和
2. **关键数据结构**：
   - **线段树**：每个节点存储区间内各余数位置的和，合并时右子树余数需根据左子树大小偏移
   - **平衡树**：节点存储子树中不同余数的和，合并时计算左子树大小带来的偏移
   - **Vector暴力**：利用`lower_bound`维护有序性，直接暴力求和

### 解决难点对比
| 解法          | 核心技巧                                                                 | 时间复杂度   | 空间复杂度   |
|---------------|--------------------------------------------------------------------------|--------------|--------------|
| 线段树        | 离散化+动态维护余数偏移，合并时`sum[i] = left[i] + right[(i-left_size)%5]` | O(q log q)   | O(q)         |
| 平衡树        | 节点维护`sum[0-4]`，合并时根据左子树大小调整右子树余数偏移                | O(q log q)   | O(q)         |
| Vector暴力    | 利用STL的`lower_bound`维护有序性，每次sum遍历模3下标                      | O(n²)        | O(n)         |

---

## 高分题解推荐 (≥4★)

### 1. chenxia25 [线段树] ★★★★★
**亮点**：
- 提供四种解法对比表格，清晰展示各方案优劣
- 动态开点线段树代码结构清晰，上传函数仅需5行
- 离散化处理优雅，使用`vector`+`lower_bound`快速定位

**核心代码**：
```cpp
void sprup(int p){ // 线段树合并逻辑
    cnt(p)=cnt(p<<1)+cnt(p<<1|1);
    for(int i=0;i<5;i++)
        sum(p)[i]=sum(p<<1)[i]+sum(p<<1|1)[(((i-cnt(p<<1))%5)+5)%5];
}
```

### 2. FutaRimeWoawaSete [平衡树] ★★★★☆
**亮点**：
- fhq-Treap实现简洁，节点直接维护模5和
- 合并逻辑数学推导清晰：`sum[(i+ls_sz+1)%5] += right_sum[i]`

**关键更新函数**：
```cpp
void update(int x){
    sz[x] = sz[ls] + sz[rs] + 1;
    for(int i=0;i<5;i++) sum[x][i] = sum[ls][i];
    for(int i=0;i<5;i++) 
        sum[x][(i+sz[ls]+1)%5] += sum[rs][i];
    sum[x][(sz[ls]+1)%5] += val[x];
}
```

### 3. Erin非陌 [Vector暴力] ★★★★☆
**亮点**：
- 代码极简（仅20行），利用STL特性快速实现
- 实际运行效率惊人（CF测试数据下1622ms通过）

**核心逻辑**：
```cpp
vector<int> v;
void add(int x){
    v.insert(lower_bound(v.begin(), v.end(), x), x);
}
void sum(){
    long long ans = 0;
    for(int i=2; i<v.size(); i+=5) ans += v[i];
}
```

---

## 最优思路提炼
1. **余数偏移维护法**：在合并子树时，右子树的余数位置需根据左子树大小动态调整
   ```python
   # 伪代码示例
   right_offset = left_size % 5
   new_sum[i] = left_sum[i] + right_sum[(i - right_offset) % 5]
   ```
2. **动态开点技巧**：处理1e9值域时，仅在访问时创建节点，节省空间
3. **STL暴力美学**：当操作数较少时，直接利用`vector`的二分插入特性

---

## 同类题目推荐
1. **P3369 普通平衡树** - 基础平衡树操作
2. **P3380 二逼平衡树** - 综合线段树与平衡树的应用
3. **P4146 序列终结者** - 动态维护区间统计信息

---

## 可视化设计
### 核心动画方案（线段树版）
1. **颜色标记**：
   - 绿色：当前操作的叶子节点
   - 蓝色：正在更新的父节点
   - 红色：受影响的右子树区间

2. **动态演示步骤**：
   ```python
   # 插入元素7时的动画流程
   1. 定位到7所在叶子节点（绿色闪烁）
   2. 自底向上更新父节点sum数组：
      - 显示左子树大小=3
      - 右子树余数偏移计算：(i-3)%5
   3. 高亮受影响的右子树区间（红色边框）
   4. 最终根节点的sum[3]数值跳动更新
   ```

### 复古像素风格
- **8-bit音效**：
  - 插入成功：短促"哔"声（440Hz方波）
  - 求和操作：连续上升音阶
- **Canvas绘制**：
  ```javascript
  // 绘制线段树节点
  function drawNode(x, y, sum) {
    ctx.fillStyle = '#8B00FF'; // 紫色背景
    ctx.fillRect(x, y, 80, 40);
    ctx.fillStyle = '#FFFF00'; // 黄色文字
    sum.forEach((v,i) => 
      ctx.fillText(`${i}:${v}`, x+5, y+15+i*10));
  }
  ```

---

## 关键实现代码
### 动态开点线段树（精简版）
```cpp
struct Node {
    int l=0, r=0, cnt=0;
    ll sum[5] = {0};
} T[MAXN * 40]; // 动态开点

void pushup(int p) {
    int l = T[p].l, r = T[p].r;
    T[p].cnt = T[l].cnt + T[r].cnt;
    for(int i=0; i<5; i++) 
        T[p].sum[i] = T[l].sum[i] + 
            T[r].sum[(i - T[l].cnt % 5 + 5) % 5];
}

void update(int &p, int l, int r, int x, int v) {
    if(!p) p = ++idx;
    if(l == r) {
        T[p].cnt += v;
        T[p].sum[1] += v * x;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) update(T[p].l, l, mid, x, v);
    else update(T[p].r, mid+1, r, x, v);
    pushup(p);
}
```

---

## 实践建议
1. **优先掌握线段树解法**：理解余数偏移的数学原理
2. **调试技巧**：在pushup函数中加入断言，验证`sum[0-4]`的正确性
3. **性能优化**：当操作数超过1e5时，务必使用动态开点避免MLE

通过掌握这些核心思路，可解决90%以上动态维护模数统计类问题。

---
处理用时：96.20秒