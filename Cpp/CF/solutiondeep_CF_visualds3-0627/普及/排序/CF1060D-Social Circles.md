# 题目信息

# Social Circles

## 题目描述

You invited $ n $ guests to dinner! You plan to arrange one or more circles of chairs. Each chair is going to be either occupied by one guest, or be empty. You can make any number of circles.

Your guests happen to be a little bit shy, so the $ i $ -th guest wants to have a least $ l_i $ free chairs to the left of his chair, and at least $ r_i $ free chairs to the right. The "left" and "right" directions are chosen assuming all guests are going to be seated towards the center of the circle. Note that when a guest is the only one in his circle, the $ l_i $ chairs to his left and $ r_i $ chairs to his right may overlap.

What is smallest total number of chairs you have to use?

## 说明/提示

In the second sample the only optimal answer is to use two circles: a circle with $ 5 $ chairs accomodating guests $ 1 $ and $ 2 $ , and another one with $ 10 $ chairs accomodationg guests $ 3 $ and $ 4 $ .

In the third sample, you have only one circle with one person. The guest should have at least five free chairs to his left, and at least six free chairs to his right to the next person, which is in this case the guest herself. So, overall number of chairs should be at least 6+1=7.

## 样例 #1

### 输入

```
3
1 1
1 1
1 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
1 2
2 1
3 5
5 3
```

### 输出

```
15
```

## 样例 #3

### 输入

```
1
5 6
```

### 输出

```
7
```

# AI分析结果



## 唯一算法分类
贪心

## 综合分析与结论
题目要求最小化总椅子数，关键在于通过贪心策略最大化相邻客人的椅子复用。核心思路是将所有客人的左右需求分别排序后对应位置配对，取每组最大值之和。此策略的正确性可由调整法证明：排序后配对能保证每对的 max 值总和最小。最终答案为总和加客人数量（每个客人自带的椅子）。

### 可视化设计要点
- **像素动画**：将排序后的 l 和 r 数组元素显示为不同颜色的像素块，配对时高亮当前比较的 max 值
- **音效触发**：每次配对成功时播放 8-bit 音效，总答案更新时播放上扬音效
- **进度展示**：用进度条显示当前已配对元素比例，总椅子数实时更新
- **自动演示**：自动排序配对，步进间隔可调节

---

## 题解清单（≥4星）

### 1. 作者：彭骐飞（5星）
- **核心亮点**：通过调整法证明贪心正确性，完整推导公式转化过程
- **代码亮点**：变量命名清晰，直接体现算法逻辑
- **个人心得**：提到被 Hack 经历，强调 long long 的重要性

### 2. 作者：Itst（4星）
- **核心亮点**：代码极度简洁，无冗余操作
- **实现亮点**：使用 STL 排序，初始化 ans 为 n 的写法更直观

### 3. 作者：king_xbz（4星）
- **核心亮点**：将问题分解为二元组最小化问题，明确数学模型
- **推导亮点**：通过单圈案例引出通用公式，降低理解难度

---

## 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int l[MAXN],r[MAXN];

int main(){
    int n; 
    cin>>n;
    for(int i=1;i<=n;i++) cin>>l[i]>>r[i];
    sort(l+1,l+n+1);
    sort(r+1,r+n+1);
    long long ans=n; // 初始化为客人数量
    for(int i=1;i<=n;i++)
        ans += max(l[i],r[i]);
    cout<<ans;
    return 0;
}
```

**关键实现思想**：
1. 双数组排序后对应位置求 max
2. 初始 ans 设为 n 直接累加，避免最后单独加 n
3. 使用 long long 防止溢出

---

## 同类型题推荐
1. **P1090 合并果子**：贪心+优先队列
2. **P1223 排队接水**：时间序列贪心排序 
3. **P1012 拼数**：字符串拼接的贪心策略

---

## 个人心得摘录
- **彭骐飞**：第一次提交未用 long long 导致 WA，强调数据范围意识
- **chufuzhe**：通过样例三的特殊情况发现单独成圈的处理方式
- **mzyc_pzx**：将问题抽象为"最大化公用椅子"的思维突破点

---

## 可视化算法过程（伪代码）
```javascript
// 初始化
let l = [5,1,3], r = [6,2,4]; 
let sortedL = l.sort((a,b)=>a-b); // [1,3,5]
let sortedR = r.sort((a,b)=>a-b); // [2,4,6]

// 动画步骤
function animateStep(i) {
    highlight(sortedL[i], 'blue'); // 高亮当前 l[i]
    highlight(sortedR[i], 'green');// 高亮当前 r[i]
    let currentMax = Math.max(sortedL[i], sortedR[i]);
    playSound('blip'); // 配对音效
    sum += currentMax; 
    updateSumDisplay(sum + n); // 实时显示总和
}

// 自动播放控制
autoPlay(steps, 1000); // 每秒执行一步
```

---

## 复古游戏化效果
- **像素风格**：椅子用 8x8 像素块表示，绿色表示已用，红色表示空闲
- **背景音乐**：8-bit 风格循环 BGM
- **得分系统**：每正确配对得 100 分，连续正确配对触发连击奖励
- **失败特效**：溢出 int 范围时屏幕抖动+红色警告

---
处理用时：197.27秒