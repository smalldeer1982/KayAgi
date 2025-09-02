# 题目信息

# Berland Fair

## 题目描述

XXI Berland Annual Fair is coming really soon! Traditionally fair consists of $ n $ booths, arranged in a circle. The booths are numbered $ 1 $ through $ n $ clockwise with $ n $ being adjacent to $ 1 $ . The $ i $ -th booths sells some candies for the price of $ a_i $ burles per item. Each booth has an unlimited supply of candies.

Polycarp has decided to spend at most $ T $ burles at the fair. However, he has some plan in mind for his path across the booths:

- at first, he visits booth number $ 1 $ ;
- if he has enough burles to buy exactly one candy from the current booth, then he buys it immediately;
- then he proceeds to the next booth in the clockwise order (regardless of if he bought a candy or not).

Polycarp's money is finite, thus the process will end once he can no longer buy candy at any booth.

Calculate the number of candies Polycarp will buy.

## 说明/提示

Let's consider the first example. Here are Polycarp's moves until he runs out of money:

1. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 33 $ ;
2. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 31 $ ;
3. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 26 $ ;
4. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 21 $ ;
5. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 19 $ ;
6. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 14 $ ;
7. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 9 $ ;
8. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 7 $ ;
9. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 2 $ ;
10. Booth $ 1 $ , buys no candy, not enough money;
11. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 0 $ .

No candy can be bought later. The total number of candies bought is $ 10 $ .

In the second example he has $ 1 $ burle left at the end of his path, no candy can be bought with this amount.

## 样例 #1

### 输入

```
3 38
5 2 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 21
2 4 100 2 6
```

### 输出

```
6
```

# AI分析结果



## 唯一算法分类
贪心优化（模运算加速）

## 综合分析与结论

### 核心思路
1. **转圈优化**：通过计算单圈总花费，用模运算快速跳过完整圈数，将时间复杂度从O(T)优化至O(n log T)
2. 动态维护可用摊位：每次处理余数时排除无法购买的摊位，确保后续计算的sum只包含有效摊位

### 解决难点
- **大数处理**：当T极大时直接模拟会超时，通过取模运算将规模指数级缩减
- **动态更新**：使用循环维护当前有效摊位集合，避免无效遍历

### 可视化设计
1. **环形摊位展示**：像素风格摊位环形排列，灰色表示已排除
2. **关键数值展示**：
   - 当前剩余资金T
   - 单圈总花费sum及可购买次数
   - 累计糖果数ans
3. **动画效果**：
   - 转圈时高速旋转+音效
   - 排除摊位时触发"爆炸"像素动画
4. **音效系统**：
   - 购买成功：8-bit "coin"音效
   - 排除摊位：短促警示音
   - 完成转圈：上升音阶

## 题解清单（≥4星）

### 1. Ynoi（5星）
- **亮点**：代码简洁高效，完美体现核心思路
- 关键代码：
```cpp
while(s > 0) {
    s = 0; rs = 0;
    for(int i = 1; i <= n; i++)
        if(s+a[i] <= m) s += a[i], rs++;
    ans += m/s * rs;
    m %= s;
}
```

### 2. 信息向阳花木（4星）
- **亮点**：变量命名清晰，注释明确
- 优化点：独立维护sum与cnt变量

### 3. JMercury（4星）
- **创新点**：优先队列维护高价摊位，提前排除无效元素

## 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, T, sum, ans = 0;
    cin >> n >> T;
    vector<ll> a(n);
    for(auto& x : a) cin >> x;
    
    while(true) {
        sum = 0;
        ll cnt = 0;
        for(ll x : a) 
            if(x <= T - sum) sum += x, cnt++;
        
        if(!cnt) break;
        
        ans += T / sum * cnt;
        T %= sum;
    }
    cout << ans;
}
```

## 同类型题目
1. **约瑟夫问题优化版**（循环淘汰）
2. **大数取模分块计算**（如矩阵快速幂）
3. **资源调度中的周期优化**

## 洛谷推荐
1. P1082 同余方程（数论基础）
2. P1965 转圈游戏（模运算应用）
3. P1516 青蛙的约会（扩展欧几里得）

## 可视化算法演示
**关键步骤动画：**
1. **初始状态**：彩色摊位环形排列，显示价格
2. **单圈计算**：
   - 绿色高亮可购买摊位
   - 底部显示sum和cnt的累加过程
3. **快速转圈**：
   - 显示"×k"动画，k为完整圈数
   - T数值快速减少
4. **余数处理**：
   - 红色标记超价摊位
   - 触发排除动画（摊位变灰）
5. **循环检测**：当无可用摊位时播放完成音效

**交互控制：**
- 速度滑块：调整计算速度
- 单步执行：观察每步细节
- 重置按钮：随机生成测试案例

## 个人心得
- **溢出陷阱**：多位作者强调使用long long
- **终止条件**：sum=0必须立即break，否则死循环
- **优化本质**：模运算与数论结合，将指数问题转化为对数级

---

通过将贪心策略与模运算结合，该算法在保持线性时间的基础上，巧妙利用数值性质实现对数级优化。可视化设计通过动态摊位状态和音效反馈，直观展现算法核心流程。

---
处理用时：88.54秒