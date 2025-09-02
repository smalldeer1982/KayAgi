# 题目信息

# Golden Plate

## 题目描述

You have a plate and you want to add some gilding to it. The plate is a rectangle that we split into $ w\times h $ cells. There should be $ k $ gilded rings, the first one should go along the edge of the plate, the second one — $ 2 $ cells away from the edge and so on. Each ring has a width of $ 1 $ cell. Formally, the $ i $ -th of these rings should consist of all bordering cells on the inner rectangle of size $ (w - 4(i - 1))\times(h - 4(i - 1)) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1031A/347cd2ee781d01fc5a8212010a9a488ef250ad46.png)The picture corresponds to the third example.Your task is to compute the number of cells to be gilded.

## 说明/提示

The first example is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1031A/8ef68100f0e4d74d121ee779a666ca2b2a0d0fdf.png)The second example is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1031A/22b59cf41d139cb0bc1ae7e108eb90b4ef24521f.png)The third example is shown in the problem description.

## 样例 #1

### 输入

```
3 3 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
7 9 1
```

### 输出

```
28
```

## 样例 #3

### 输入

```
7 9 2
```

### 输出

```
40
```

# AI分析结果



【中文重写题目】
# 金盘装饰

## 题目描述

你有一个盘子，想要给它添加金边装饰。盘子被划分为 $w \times h$ 的网格。需要制作 $k$ 层金环，第一层沿着盘子边缘，第二层距离边缘 2 个单元格，依此类推。每个金环宽度为 1 个单元格。形式化地说，第 $i$ 个金环由尺寸为 $(w - 4(i - 1)) \times (h - 4(i - 1))$ 的矩形边界上所有单元格构成。请计算需要镀金的单元格总数。

## 样例说明
- 样例1输入：3 3 1 → 输出8（3x3最外层周长）
- 样例2输入：7 9 1 → 输出28（7x9最外层周长）
- 样例3输入：7 9 2 → 输出40（叠加两层周长）

---

**算法分类**：数学

---

### 题解分析与结论
核心问题转化为数学公式推导，通过等差数列求和将时间复杂度优化至 O(1)。关键点在于：
1. 每层金环的周长公式：2*(w' + h' - 2)，其中 w' = w-4(i-1)，h' = h-4(i-1)
2. 总周长可转化为等差数列求和，最终推导出公式：`2k*(w + h - 4k + 2)`

---

### 精选题解

#### 1. Alex_Wei（⭐⭐⭐⭐⭐）
**亮点**：
- 双解法（模拟+数学公式），思路清晰
- 详细推导等差数列转化过程
- 提供极简版代码（83B）

**核心代码**：
```cpp
int main() {
    int w,h,k; 
    std::cin>>w>>h>>k;
    std::cout<<2*k*(w+h-4*k+2);
}
```

#### 2. REAL_曼巴（⭐⭐⭐⭐）
**亮点**：
- 直接应用数学公式，代码简洁高效
- 公式推导步骤清晰

**核心代码**：
```cpp
printf("%d", (w+h+2-4*k)*2*k);
```

#### 3. zmza（⭐⭐⭐⭐）
**亮点**：
- 代码极度简洁（仅6行）
- 正确实现公式推导结果

**核心代码**：
```cpp
printf("%d", (w + h + 2 - 4 * k) * 2 * k);
```

---

### 最优技巧总结
**关键突破点**：将层数计算转化为等差数列求和，推导出：
```
总单元格数 = 2k*(w + h - 4k + 2)
```
**思维启示**：当循环次数固定且存在线性规律时，应优先尝试数学公式推导而非模拟。

---

### 拓展练习
1. **P5717 三角形面积**（数学公式推导）
2. **P1007 独木桥**（边界问题与对称性思维） 
3. **P1059 明明的随机数**（数学规律与去重技巧）

---
处理用时：74.30秒