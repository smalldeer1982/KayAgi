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



# 题目重写

## 题目描述

若干年后，$ n $ 个朋友在聚会上重逢。相比上次见面，科技已有了长足进步，带定时器的相机出现后，不再需要有人操作相机而缺席合影。

简而言之，拍照流程如下：每个朋友在照片中占据一个像素矩形，第 $ i $ 个朋友站立时占据宽 $ w_i $ 像素、高 $ h_i $ 像素的矩形；也可以躺下，此时占据宽 $ h_i $ 像素、高 $ w_i $ 像素的矩形。

照片总尺寸为 $ W×H $，其中 $ W $ 为所有人矩形宽度之和，$ H $ 为所有矩形高度的最大值。朋友们想知道在最多允许 $ \lfloor n/2 \rfloor $ 人躺下的情况下，能获得的最小合影面积是多少。

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

---

# 题解分析与结论

## 综合思路
各题解均采用**枚举最大高度+贪心优化**的核心框架：
1. **枚举所有可能的最终高度**（范围由输入数据确定）
2. **分类处理每个朋友的状态**：
   - 必须站立/必须躺下的强制情况
   - 可优化选择的灵活情况
3. **贪心选择最优躺下组合**，通过排序或优先队列选取对宽度优化最有利的选项

## 最优题解推荐

### 1. 题解 by communist（4星）
**关键亮点**：
- 简洁高效的分类逻辑
- 直接通过差值排序实现贪心
- 代码结构清晰易懂

**核心思路**：
```cpp
for(int maxh=1; maxh<=hh; maxh++) {
    int cnt=0, rs=sw;
    vector<int> v;
    // 分类处理四种情况
    sort(v.begin(), v.end(), cmp); // 按w[i]-h[i]排序
    // 贪心选择最优躺下组合
    ans = min(ans, rs * maxh);
}
```

### 2. 题解 by Happy_mouse（4星）
**关键亮点**：
- 将情况细分为五类，逻辑严密
- 明确注释提升可读性
- 变量命名清晰（如hfn表示半数限制）

**调试心得**：
> 注意乘的是枚举的high而非实际高度，因为最终高度由枚举值决定

### 3. 题解 by tZEROちゃん（4星）
**关键亮点**：
- 使用优先队列动态维护最优解
- Lambda表达式封装判断逻辑
- 包含简单版本题目链接便于对比学习

**核心片段**：
```cpp
auto calc = [&](i64 lim) -> i64 {
    priority_queue<int> q; // 维护可优化的差值
    // ...处理必须躺下的情况...
    while (f-- && q.size()) { // 贪心选取最优解
        b -= q.top();
        q.pop();
    }
    return b * lim;
};
```

---

## 关键技巧总结
1. **枚举极值参数**：当问题中存在极值参数（如本题的最大高度）时，枚举该参数并验证可行性是常见套路
2. **状态分类处理**：将元素分为强制选择和可选优化两类，分别处理
3. **贪心差值优化**：通过维护(w[i]-h[i])的差值，优先选择能最大减少宽度的元素进行状态转换

---

## 类似题目推荐
1. P1080 国王游戏（贪心+排序策略）
2. P1230 智力大冲浪（时间窗口+贪心选择）
3. P2123 皇后游戏（多条件排序策略）

---
处理用时：52.95秒