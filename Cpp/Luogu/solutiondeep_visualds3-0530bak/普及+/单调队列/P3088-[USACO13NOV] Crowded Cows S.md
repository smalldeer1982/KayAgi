# 题目信息

# [USACO13NOV] Crowded Cows S

## 题目描述

Farmer John's N cows (1 <= N <= 50,000) are grazing along a one-dimensional fence.  Cow i is standing at location x(i) and has height h(i) (1 <= x(i),h(i) <= 1,000,000,000).

A cow feels "crowded" if there is another cow at least twice her height within distance D on her left, and also another cow at least twice her height within distance D on her right (1 <= D <= 1,000,000,000).  Since crowded cows produce less milk, Farmer John would like to count the number of such cows.  Please help him.

FJ有 $N(1\le N\le50000)$ 头奶牛沿着一维的栅栏吃草，第 $i$ 头奶牛在目标点 $x_i$ ，它的身高是 $h_i (1 \le x_i,h_i\le10^9)$。

当一头奶牛左边 $D(1\le D\le10^9)$ 距离内且右边 $D$ 距离内有身高至少是它的两倍的奶牛，它就会觉得拥挤。

请计算觉得拥挤的奶牛的数量。


## 说明/提示

There are 6 cows, with a distance threshold of 4 for feeling crowded.  Cow #1 lives at position x=10 and has height h=3, and so on.


The cows at positions x=5 and x=6 are both crowded. 



## 样例 #1

### 输入

```
6 4 
10 3 
6 2 
5 3 
9 7 
3 6 
11 2 
```

### 输出

```
2 
```

# AI分析结果



# [USACO13NOV] Crowded Cows S 题解分析

## 一、算法分类
**单调队列**

## 二、核心思路与难点分析
### 核心算法流程
1. **排序预处理**：将奶牛按坐标排序，时间复杂度 O(n log n)
2. **双端单调队列维护**：
   - **从左向右扫描**：维护当前奶牛左侧 D 距离内的最大高度，使用单调递减队列
   - **从右向左扫描**：维护当前奶牛右侧 D 距离内的最大高度，同样使用单调递减队列
3. **条件判断**：若左右两侧的最大高度均 ≥ 当前高度的两倍，则计入答案

### 解决难点
1. **距离判断**：通过队列头部元素的坐标差动态维护合法区间
2. **单调性维护**：新元素入队时弹出尾部所有高度更低的元素，保证队列递减
3. **双向处理**：正反两次扫描分别处理左右条件，避免二维区间查询

## 三、题解评分（≥4★）

| 作者         | 评分 | 亮点分析                                                                 |
|--------------|------|--------------------------------------------------------------------------|
| jzqjzq       | ★★★★★ | O(n) 双端单调队列实现，代码简洁高效                                      |
| EarthGiao    | ★★★★☆ | 结构体封装清晰，队列维护逻辑完整                                        |
| YosemiteHe   | ★★★★☆ | 使用 deque 实现，边界条件处理规范                                        |

## 四、最优代码实现（jzqjzq 题解核心片段）
```cpp
int main() {
    // 排序预处理
    sort(a+1,a+n+1,cmp);
    
    // 左扫描
    for(int i=1;i<=n;i++){
        while(l<=r&&qq[r].y<a[i].y) r--; // 维护单调性
        qq[++r] = a[i];
        while(l<=r&&qq[l].x < a[i].x-d) l++; // 维护距离约束
        if(qq[l].y >= a[i].y*2) q[i]=1; // 左条件标记
    }
    
    // 右扫描（逻辑对称）
    for(int i=n;i;i--){
        while(l<=r&&qq[r].y < a[i].y) r--;
        qq[++r] = a[i];
        while(l<=r&&qq[l].x > a[i].x+d) l++;
        if(qq[l].y >= a[i].y*2) h[i]=1; // 右条件标记
    }
    
    // 统计结果
    for(int i=1;i<=n;i++) ans += q[i]&&h[i];
}
```

## 五、扩展应用与相似题目
### 同类型题目套路
1. 滑动窗口最大值（洛谷 P1886）
2. 区间极值约束计数问题
3. 双向约束验证模型

### 推荐练习题
1. **P1886 滑动窗口** - 单调队列模板题
2. **P1714 切蛋糕** - 单调队列优化区间和
3. **P1440 求m区间内的最小值** - 双向单调队列应用

## 六、可视化方案设计
### 核心动画逻辑
```javascript
// 伪代码示例：单调队列维护动画
function animateQueue(cowArray) {
    let queue = [];
    for(let i=0; i<cowArray.length; i++) {
        // 高亮当前奶牛
        highlight(cowArray[i], 'processing');
        
        // 弹出队尾较小元素（红色闪烁）
        while(queue.length && queue[queue.length-1].h < cowArray[i].h) {
            let removed = queue.pop();
            flash(removed, 'red');
        }
        
        // 入队当前元素（绿色渐入）
        queue.push(cowArray[i]);
        animateAdd(queue, cowArray[i]);
        
        // 维护距离约束（黄色标记）
        while(queue[0].x < cowArray[i].x - D) {
            let removed = queue.shift();
            flash(removed, 'yellow');
        }
        
        // 条件判断（蓝色高亮）
        if(queue[0].h >= 2*cowArray[i].h) {
            markConditionMet(cowArray[i], 'left');
        }
    }
}
```

### 复古像素风格要素
1. **视觉设计**：
   - 奶牛用 16x16 像素块表示，不同高度用颜色梯度（绿→红）
   - 队列显示为横向排列的方块，带坐标刻度线
   - 当前操作元素显示脉冲光效

2. **音效设计**：
   - 元素入队：8-bit "blip" 音效（频率随高度递增）
   - 条件达成：FC 风格的胜利音效（短促上升音阶）
   - 越界弹出：低沉爆炸音

3. **交互功能**：
   - 速度控制滑杆（1x-16x）
   - 单步执行按钮（Space 键控制）
   - 队列状态监视面板（显示当前队列头尾坐标）

## 七、关键调试心得
1. **距离判断方向**：右扫描时条件应为 `a[i].x + d` 而非 `a[i].x - d`
2. **队列初始化**：每次扫描前需重置队列指针
3. **浮点精度**：使用 `>=` 而非 `>` 避免浮点误差

## 八、总结
本题通过双端单调队列的巧妙运用，将二维区间查询转化为线性时间的双向扫描。核心在于理解单调队列维护极值的特性与滑动窗口的距离约束机制。建议通过可视化工具动态观察队列维护过程，加深对"淘汰不可能成为答案的元素"这一核心思想的理解。

---
处理用时：84.66秒