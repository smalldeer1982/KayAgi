# 题目信息

# Group Photo 2 (online mirror version)

## 题目描述

Many years have passed, and $ n $ friends met at a party again. Technologies have leaped forward since the last meeting, cameras with timer appeared and now it is not obligatory for one of the friends to stand with a camera, and, thus, being absent on the photo.

Simply speaking, the process of photographing can be described as follows. Each friend occupies a rectangle of pixels on the photo: the $ i $ -th of them in a standing state occupies a $ w_{i} $ pixels wide and a $ h_{i} $ pixels high rectangle. But also, each person can lie down for the photo, and then he will occupy a $ h_{i} $ pixels wide and a $ w_{i} $ pixels high rectangle.

The total photo will have size $ W×H $ , where $ W $ is the total width of all the people rectangles, and $ H $ is the maximum of the heights. The friends want to determine what minimum area the group photo can they obtain if no more than $ n/2 $ of them can lie on the ground (it would be strange if more than $ n/2 $ gentlemen lie on the ground together, isn't it?..)

Help them to achieve this goal.

## 样例 #1

### 输入

```
3
10 1
20 2
30 3
```

### 输出

```
180
```

## 样例 #2

### 输入

```
3
3 1
2 2
4 3
```

### 输出

```
21
```

## 样例 #3

### 输入

```
1
5 10
```

### 输出

```
50
```

# AI分析结果



# Group Photo 2 (online mirror version)

## 题目描述

多年后，$n$ 个朋友在派对上重逢。相机技术有了长足进步，现在拍照时不需要有人操作相机，所有朋友都可以出现在照片中。

每个朋友在站立状态下占据宽 $w_i$ 像素、高 $h_i$ 像素的矩形区域，也可以选择躺下，此时占据宽 $h_i$ 像素、高 $w_i$ 像素的区域。照片的总尺寸为 $W \times H$，其中 $W$ 是所有朋友占据区域的宽度总和，$H$ 是最大高度。要求最多有 $\lfloor n/2 \rfloor$ 个人躺下，求能获得的最小照片面积。

## 题解分析与结论

### 关键思路
1. **枚举最大高度**：固定可能的最大高度 $H$，计算该约束下的最小总宽度 $W$
2. **分类处理状态**：对每个朋友，根据其尺寸与当前 $H$ 的关系分为：
   - 必须躺下（原站立高度超过 $H$）
   - 必须站立（原躺下高度超过 $H$）
   - 可自由调整（两种状态高度均不超过 $H$）
3. **贪心选择**：在满足躺下人数限制的前提下，优先让调整后宽度减少最多的朋友躺下

### 最优技巧
- **枚举剪枝**：枚举所有可能的 $H$（取值范围为所有 $w_i$ 和 $h_i$ 的并集）
- **差值排序**：对可调整的朋友按 $w_i - h_i$ 降序排序，优先选择能减少更多宽度的

---

## 精选题解

### 题解一：communist（★★★★☆）
**亮点**：思路清晰，代码简洁，利用排序实现贪心选择  
**核心代码**：
```cpp
sort(v.begin(),v.end(),cmp); // 按w[i]-h[i]降序排序
for(int i=0;i<v.size()&&cnt+i<n/2;i++)
    rs += h[v[i]]-w[v[i]];   // 选择减少宽度最多的调整
ans = min(ans, rs*maxh);
```
**处理流程**：
1. 预处理每个 $H$ 下必须躺下的人数
2. 将可调整的朋友存入数组并排序
3. 在名额限制内选择最优调整

### 题解二：Bitter_Tea（★★★★☆）
**亮点**：使用优先队列优化选择，结合前缀和预处理  
**核心代码**：
```cpp
priority_queue<int> q; // 大根堆维护差值
for(可调整的朋友)
    q.push(w[i]-h[i]);
while(名额未满 && 堆非空)
    选择堆顶元素调整
```
**优化点**：通过前缀和快速判断可能的躺下人数范围

### 题解三：Happy_mouse（★★★★☆）
**亮点**：详细的状态分类与清晰的代码结构  
**分类逻辑**：
```cpp
if(h[i]>maxh && w[i]>maxh) 无解;
else if(h[i]必须躺下) 计数并累加宽度变化;
else if(可调整) 存入待处理数组;
```

---

## 总结与拓展
**关键思维**：当问题存在两个相互制约的变量时（如本题的 $W$ 和 $H$），可以通过固定一个变量来优化另一个变量，再遍历所有可能的候选值。

**同类题目推荐**：
1. [CF524B - 简化版集体照](https://www.luogu.com.cn/problem/CF524B)
2. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)（贪心选择最优分隔线）
3. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)（贪心排序策略）
4. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)（二维偏序+贪心）

**调试心得**：
- 注意处理边界情况，如 $n=1$ 时躺下名额为 0
- 枚举范围要覆盖所有可能的 $H$ 候选值（包括所有 $w_i$ 和 $h_i$）
- 必须确保至少有一个朋友的高度等于当前枚举的 $H$，否则实际总高度可能更小

---
处理用时：185.75秒