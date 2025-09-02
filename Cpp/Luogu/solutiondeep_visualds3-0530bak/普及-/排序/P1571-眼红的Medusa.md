# 题目信息

# 眼红的Medusa

## 题目描述

虽然 Miss Medusa 到了北京，领了科技创新奖，但是她还是觉得不满意。原因是：他发现很多人都和她一样获了科技创新奖，特别是其中的某些人，还获得了另一个奖项——特殊贡献奖。而越多的人获得了两个奖项，Miss Medusa就会越眼红。于是她决定统计有哪些人获得了两个奖项，来知道自己有多眼红。

## 说明/提示

对于 $60\%$ 的数据，$0 \leq n, m \leq 1000$，获得奖项的人的编号 $\lt 2 \times 10^9$；

对于 $100\%$ 的数据，$0 \leq n, m \leq 10^5$，获得奖项的人的编号 $\lt 2 \times 10^9$。

输入数据保证第二行任意两个数不同，第三行任意两个数不同。

## 样例 #1

### 输入

```
4 3
2 15 6 8
8 9 2
```

### 输出

```
2 8```

# AI分析结果



## 唯一算法分类
**二分查找**

## 综合分析与结论
### 核心思路
题目要求找出同时获得两个奖项的编号，并按科技创新奖的顺序输出。由于数据规模为1e5级别，需采用高效查找方法。核心思路是：将特殊贡献奖数组排序后，对每个科技创新奖元素进行二分查找判断是否存在。

### 算法流程
1. **排序**：将特殊贡献奖数组排序，时间复杂度O(m log m)
2. **二分查找**：遍历科技创新奖数组，对每个元素在排序后的特殊贡献奖数组中进行二分查找，时间复杂度O(n log m)
3. **输出结果**：按原顺序输出所有满足条件的元素

### 解决难点
- **顺序保持**：科技创新奖数组不能排序，需记录原始顺序
- **高效查找**：针对1e5规模数据，必须采用O(n log m)级别算法
- **去重处理**：题目已保证输入数据内部无重复，无需额外处理

### 可视化设计
1. **像素化排序动画**：用8-bit风格展示特殊贡献奖数组排序过程，每个元素以不同颜色方块表示
2. **二分查找演示**：以绿色光标标记查找区间左右边界，红色光标指示中间元素，黄色高亮匹配成功元素
3. **音效反馈**：匹配成功时播放8-bit音效，查找区间变化时伴随不同频率提示音
4. **自动演示模式**：按科技创新奖顺序自动执行查找，每步间隔可调

## 题解清单 (≥4星)
1. **Christopher_Yan (5星)**  
   使用map实现简洁易懂，适合快速解题。核心亮点：  
   - 利用map自动排序特性简化逻辑
   - 代码极简（仅15行）
   - 时间复杂度O(n log m)完全达标

2. **Starlight237 (5星)**  
   使用STL的binary_search实现最优解法。核心亮点：  
   - 利用标准库函数减少代码量
   - 指针优化提升运行效率（208ms）
   - 附带二分查找模板代码方便学习

3. **引领天下 (4星)**  
   双指针法实现高效查找。核心亮点：  
   - 通过结构体保留原始顺序
   - 时间复杂度O(n log n + m log m)稳定高效
   - 独创性思维值得借鉴

## 最优代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
int a[MAXN], b[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i=0; i<n; ++i) scanf("%d", a+i);
    for(int i=0; i<m; ++i) scanf("%d", b+i);
    
    sort(b, b+m); // 关键排序步骤
    
    for(int i=0; i<n; ++i) {
        if(binary_search(b, b+m, a[i])) // STL二分查找
            printf("%d ", a[i]);
    }
    return 0;
}
```

## 相似题目推荐
1. **P1918 保龄球** - 数字查找问题
2. **P1177 【模板】快速排序** - 排序算法基础
3. **P3369 【模板】普通平衡树** - 高效查找数据结构

## 可视化代码片段
```javascript
// 8-bit风格二分查找动画
function binarySearchVisualize(target, arr) {
    let low = 0, high = arr.length-1;
    let steps = [];
    
    while(low <= high) {
        const mid = Math.floor((low + high)/2);
        steps.push({low, high, mid}); // 记录查找轨迹
        
        if(arr[mid] === target) {
            return {found: true, steps};
        } else if(arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return {found: false, steps};
}

// 生成8-bit音效
function playSFX(type) {
    const ctx = new AudioContext();
    const osc = ctx.createOscillator();
    osc.type = 'square';
    osc.frequency.value = type === 'hit' ? 880 : 440;
    osc.connect(ctx.destination);
    osc.start();
    osc.stop(ctx.currentTime + 0.1);
}
```

## 个人心得摘录
> "被输出顺序坑了两次20分，结构体保存原始位置是关键" —— 引领天下  
> "用指针优化后比普通实现快一倍，细节决定效率" —— Starlight237  
> "本以为map会超时，没想到轻松AC，STL大法好" —— Christopher_Yan

## 复古动画设计
1. **颜色方案**：  
   - 未查找区域：#8B8B8B  
   - 当前区间：#FFD700  
   - 匹配元素：#00FF00  
   - 背景音乐：FC游戏《超级马里奥》地下城BGM改编

2. **动画流程**：  
   - 初始化时展示乱序的特殊贡献奖数组  
   - 快速排序过程用冒泡动画示意  
   - 二分查找时左右指针以像素箭头表示  
   - 成功匹配时触发金币音效+闪光特效

3. **交互功能**：  
   - 空格键暂停/继续  
   - 方向键控制演示速度  
   - F键切换自动/手动模式  
   - ESC键显示算法复杂度分析

---
处理用时：90.22秒