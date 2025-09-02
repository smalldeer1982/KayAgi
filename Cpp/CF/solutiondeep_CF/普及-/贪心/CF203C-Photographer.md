# 题目信息

# Photographer

## 题目描述

Valera's lifelong ambition was to be a photographer, so he bought a new camera. Every day he got more and more clients asking for photos, and one day Valera needed a program that would determine the maximum number of people he can serve.

The camera's memory is $ d $ megabytes. Valera's camera can take photos of high and low quality. One low quality photo takes $ a $ megabytes of memory, one high quality photo take $ b $ megabytes of memory. For unknown reasons, each client asks him to make several low quality photos and several high quality photos. More formally, the $ i $ -th client asks to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos.

Valera wants to serve as many clients per day as possible, provided that they will be pleased with his work. To please the $ i $ -th client, Valera needs to give him everything he wants, that is, to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos. To make one low quality photo, the camera must have at least $ a $ megabytes of free memory space. Similarly, to make one high quality photo, the camera must have at least $ b $ megabytes of free memory space. Initially the camera's memory is empty. Valera also does not delete photos from the camera so that the camera's memory gradually fills up.

Calculate the maximum number of clients Valera can successfully serve and print the numbers of these clients.

## 样例 #1

### 输入

```
3 10
2 3
1 4
2 1
1 0
```

### 输出

```
2
3 2 ```

## 样例 #2

### 输入

```
3 6
6 6
1 1
1 0
1 0
```

### 输出

```
1
2 ```

# AI分析结果



# Photographer

## 题目描述

瓦列拉的毕生志向是成为一名摄影师，因此他购买了一台新相机。每天都有越来越多的客户要求拍照，有一天瓦列拉需要一个程序来确定他最多可以服务多少客户。

相机的内存为 $d$ 兆字节。瓦列拉的相机可以拍摄高质量和低质量的照片。一张低质量照片占用 $a$ 兆字节内存，一张高质量照片占用 $b$ 兆字节内存。出于未知原因，每个客户都要求他拍摄若干张低质量照片和若干张高质量照片。更正式地说，第 $i$ 个客户要求拍摄 $x_{i}$ 张低质量照片和 $y_{i}$ 张高质量照片。

瓦列拉希望每天尽可能多地服务客户，前提是他们对他的工作满意。为了让第 $i$ 个客户满意，瓦列拉必须完全满足其要求，即拍摄 $x_{i}$ 张低质量照片和 $y_{i}$ 张高质量照片。每拍摄一张低质量照片时，相机必须有至少 $a$ 兆字节的可用内存空间。类似地，每拍摄一张高质量照片时，相机必须有至少 $b$ 兆字节的可用内存空间。初始时相机的内存是空的。瓦列拉也不会删除相机中的照片，因此相机的内存会逐渐被填满。

计算瓦列拉最多能成功服务的客户数量，并输出这些客户的编号。

---

## 题解分析与结论

### 核心思路
所有题解均采用**贪心算法**，通过以下步骤实现：
1. **计算每个客户的总内存需求**：`总内存 = x_i*a + y_i*b`
2. **按总内存升序排序**：优先处理需求小的客户
3. **顺序处理客户直到内存不足**：累加处理客户数量并记录编号

### 关键实现技巧
1. **结构体存储客户信息**：包含原始需求、总内存、客户编号
2. **排序函数优化**：使用自定义比较函数或lambda表达式
3. **内存递减判断**：在遍历时实时扣除内存并判断剩余容量

---

## 高星题解推荐

### 1. Szr__QAQ（4星）
**亮点**：
- 结构体定义清晰，包含完整客户信息
- 代码注释明确，逻辑直观
- 输出处理规范，空格控制合理

**核心代码**：
```cpp
struct szr{ int x,y,id,sum; };
bool cmp(szr a,szr b){ return a.sum < b.sum; }

sort(photo+1,photo+n+1,cmp);
for(int i=1;i<=n;i++){
    if(photo[i].sum <= d){
        d -= photo[i].sum;
        cnt++;
    } else break;
}
```

### 2. yzm0325（4星）
**亮点**：
- 变量命名简洁（yh = 用户）
- 内存递减逻辑紧凑（`d -= yh[i].s`）
- 输出部分处理高效

**代码亮点**：
```cpp
struct client { int s, id; };
sort(yh + 1, yh + n + 1, cmp);
for(int i=1;i<=n;i++){
    d -= yh[i].s;
    if(d < 0) break;
    ans++;
}
```

### 3. CleverRaccoon（4星）
**亮点**：
- 使用C++11特性初始化结构体
- lambda表达式实现排序
- vector动态存储答案

**创新实现**：
```cpp
sort(a + 1, a + n + 1, [](node a, node b) {
    return a.use < b.use;
});
for(int i=1;i<=n;i++){
    if((d -= a[i].use) <= 0) break;
    ans.push_back(a[i].id);
}
```

---

## 关键优化总结
1. **预处理计算**：在输入阶段直接计算总内存，避免重复计算
2. **编号绑定**：排序时保留原始编号信息
3. **提前终止**：发现无法满足立即break，减少无效遍历

---

## 调试经验摘录
- **yzm0325**：因测试平台问题导致初始代码错误，强调验证边界条件的重要性
- **liupan2010**：使用快速读写函数时注意负数处理，体现输入输出细节的重要性
- **Dr_Glitch**：结构体设计经验：同时存储原始数据和计算结果便于后续处理

---

## 相似题目推荐
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 经典贪心排序
2. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803) - 区间调度类贪心
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 优先队列实现贪心

---
处理用时：47.61秒