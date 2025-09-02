# 题目信息

# [USACO13OPEN] Photo G

## 题目描述

Farmer John has decided to assemble a panoramic photo of a lineup of his N cows (1 <= N <= 200,000), which, as always, are conveniently numbered from 1..N.  Accordingly, he snapped M (1 <= M <= 100,000) photos, each covering a contiguous range of cows: photo i contains cows a\_i through b\_i inclusive.  The photos collectively may not necessarily cover every single cow.

After taking his photos, FJ notices a very interesting phenomenon: each photo he took contains exactly one cow with spots!  FJ was aware that he had some number of spotted cows in his herd, but he had never actually counted them.  Based on his photos, please determine the maximum possible number of spotted cows that could exist in his herd.  Output -1 if there is no possible assignment of spots to cows consistent with FJ's photographic results.

农夫约翰决定给站在一条线上的N(1 <= N <= 200,000)头奶牛制作一张全家福照片，N头奶牛编号1到N。


于是约翰拍摄了M(1 <= M <= 100,000)张照片，每张照片都覆盖了连续一段奶牛：第i张照片中包含了编号a\_i 到 b\_i的奶牛。但是这些照片不一定把每一只奶牛都拍了进去。


在拍完照片后，约翰发现了一个有趣的事情：每张照片中都**有且仅有**一只身上带有斑点的奶牛。约翰意识到他的牛群中有一些斑点奶牛，但他从来没有统计过它们的数量。 根据照片，请你帮约翰估算在他的牛群中最多可能有多少只斑点奶牛。如果无解，输出“-1”。


Input

## 说明/提示

There are 5 cows and 3 photos.  The first photo contains cows 1 through 4, etc.


From the last photo, we know that either cow 3 or cow 4 must be spotted. By choosing either of these, we satisfy the first two photos as well.


## 样例 #1

### 输入

```
5 3 
1 4 
2 5 
3 4 
```

### 输出

```
1 
```

# AI分析结果



## 算法分类
动态规划（单调队列优化）

---

## 核心思路与解决难点

### 核心算法流程
1. **状态定义**  
   `f[i]` 表示在位置 `i` 必须放置斑点牛时，前 `i` 个位置的最大斑点牛数量

2. **转移范围预处理**  
   - `minl[i]`：覆盖 `i` 的所有区间中最小的左端点（转移右边界）
   - `maxl[i]`：右端点 `<i` 的区间中最大的左端点（转移左边界）

3. **单调队列优化**  
   维护一个单调递减队列，保证队首元素是当前转移窗口内的最大值

### 关键实现步骤
```cpp
// 预处理 minl 和 maxl
for(int i=N;i>=1;i--) 
    minl[i] = min(minl[i], minl[i+1]);
for(int i=1;i<=N+1;i++) 
    maxl[i] = max(maxl[i], maxl[i-1]);

// 单调队列维护
int j=1, h=1, t=0;
for(int i=1;i<=N+1;i++){
    while(j < minl[i]) { // 扩展右边界
        if(f[j] != -1){
            while(h<=t && f[j]>f[q[t]]) t--;
            q[++t] = j;
        }
        j++;
    }
    while(h<=t && q[h]<maxl[i]) h++; // 收缩左边界
    f[i] = (h<=t) ? f[q[h]] + (i<=N) : -1;
}
```

### 可视化设计要点
- **动画效果**：在 Canvas 上绘制数轴和区间覆盖关系，用不同颜色标注：
  - 红色线段：当前处理的 `minl[i]` 和 `maxl[i]` 区间
  - 蓝色方块：单调队列中的有效转移点
  - 绿色高亮：当前更新的 `f[i]` 值
- **音效触发**：
  - 清脆的"叮"声：成功转移时（`f[i]` 更新）
  - 低沉"嘟"声：转移失败（`f[i] = -1`）
- **像素风格**：用 8-bit 风格绘制奶牛图标，斑点牛用黄色像素块表示

---

## 高分题解推荐（≥4★）

### 1. x义x（5★）  
**亮点**：  
- 清晰推导 `minl/maxl` 的预处理逻辑  
- 虚拟节点 `N+1` 处理边界条件  
- 代码中 `j` 指针的移动与队列维护高度耦合

### 2. bztMinamoto（5★）  
**亮点**：  
- 变量命名简洁（`l[i]/r[i]` 代替 `maxl/minl`）  
- 双指针维护转移窗口更直观  
- 代码结构紧凑，运行效率极高（洛谷 rank1）

### 3. XuYueming（4★）  
**亮点**：  
- 发现 `f` 数组的单调性，改用双指针优化  
- 极致代码压缩（循环与预处理合并）  
- 手写快读优化 IO 效率

---

## 最优技巧提炼

### 核心思维
- **区间约束转换**：将"恰好一个"拆解为"至少一个"和"至多一个"的复合约束  
- **窗口单调性**：`minl` 和 `maxl` 的单调性保证了转移窗口的滑动特性

### 实现优化
```cpp
// 双指针维护转移窗口（替代单调队列）
int j=0, k=0;
for(int i=1; i<=n+1; i++){
    while(j < mx[i]) {
        if(f[++j] != -1) k = j; 
    }
    f[i] = (k >= mi[i]) ? f[k]+1 : -1;
}
```

---

## 相似题目推荐
1. **P1725 琪露诺**  
   区间跳跃 + 单调队列优化 DP

2. **P3957 跳房子**  
   动态规划 + 二分答案验证

3. **P2569 股票交易**  
   带时间窗口限制的 DP 优化

---

## 调试心得摘录
> "UPD9/27：修正了第二张图片。对大家造成的不便请谅解。" —— x义x  
> **总结**：图示错误会导致对转移区间的误解，几何直观验证是调试关键

> "差分约束还是能过的（其实被卡了）" —— x义x  
> **教训**：SPFA 在稠密图下效率极低，需优先考虑问题特殊性质

---

## 复古像素动画实现方案

### 关键帧设计
1. **初始化阶段**  
   - 数轴从左侧逐格绘制，伴随 8-bit 音效  
   - 区间覆盖显示为半透明红色矩形块

2. **预处理动画**  
   - `minl` 从右向左扫描，绿色箭头标记当前处理位置  
   - `maxl` 从左向右扫描，蓝色箭头同步移动

3. **DP 转移过程**  
   - 当前处理位置 `i` 闪烁黄色边框  
   - 单调队列用浮动方阵表示，元素值用像素数字显示

### 音效配置
```javascript
// Web Audio API 音效示例
function playSound(freq) {
    let osc = audioCtx.createOscillator();
    osc.type = 'square';
    osc.frequency.setValueAtTime(freq, audioCtx.currentTime);
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(audioCtx.currentTime + 0.1);
}

// 成功转移音效（C大调）
playSound(523); // C5
playSound(659); // E5
```

---

## 代码实现（核心片段）
```cpp
// 动态规划主循环（带注释）
int j=1, h=1, t=0, q[N+2];
for(int i=1; i<=n+1; ++i){
    // 扩展右边界并维护队列单调性
    for(; j<minl[i]; ++j) if(f[j]!=-1) {
        while(h<=t && f[j]>=f[q[t]]) --t;
        q[++t] = j;
    }
    // 收缩左边界
    while(h<=t && q[h]<maxl[i]) ++h;
    // 状态转移
    f[i] = (h<=t) ? f[q[h]] + (i<=n) : -1;
}
```

---
处理用时：89.80秒