# 题目信息

# Traps

## 题目描述

There are $ n $ traps numbered from $ 1 $ to $ n $ . You will go through them one by one in order. The $ i $ -th trap deals $ a_i $ base damage to you.

Instead of going through a trap, you can jump it over. You can jump over no more than $ k $ traps. If you jump over a trap, it does not deal any damage to you. But there is an additional rule: if you jump over a trap, all next traps damages increase by $ 1 $ (this is a bonus damage).

Note that if you jump over a trap, you don't get any damage (neither base damage nor bonus damage). Also, the bonus damage stacks so, for example, if you go through a trap $ i $ with base damage $ a_i $ , and you have already jumped over $ 3 $ traps, you get $ (a_i + 3) $ damage.

You have to find the minimal damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 说明/提示

In the first test case it is allowed to jump over all traps and take $ 0 $ damage.

In the second test case there are $ 5 $ ways to jump over some traps:

1. Do not jump over any trap.Total damage: $ 5 + 10 + 11 + 5 = 31 $ .
2. Jump over the $ 1 $ -st trap.Total damage: $ \underline{0} + (10 + 1) + (11 + 1) + (5 + 1) = 29 $ .
3. Jump over the $ 2 $ -nd trap.Total damage: $ 5 + \underline{0} + (11 + 1) + (5 + 1) = 23 $ .
4. Jump over the $ 3 $ -rd trap.Total damage: $ 5 + 10 + \underline{0} + (5 + 1) = 21 $ .
5. Jump over the $ 4 $ -th trap.Total damage: $ 5 + 10 + 11 + \underline{0} = 26 $ .

To get minimal damage it is needed to jump over the $ 3 $ -rd trap, so the answer is $ 21 $ .

In the third test case it is optimal to jump over the traps $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 7 $ :

Total damage: $ 0 + (2 + 1) + 0 + 0 + 0 + (2 + 4) + 0 = 9 $ .

## 样例 #1

### 输入

```
5
4 4
8 7 1 4
4 1
5 10 11 5
7 5
8 2 5 15 11 2 8
6 3
1 2 3 4 5 6
1 1
7```

### 输出

```
0
21
9
6
0```

# AI分析结果



### 唯一算法分类
贪心算法

### 综合分析与结论
题目要求通过跳至多k个陷阱，使得总伤害最小。核心思路是计算每个陷阱跳过的净收益，选择最大的k个，并调整总收益以处理跳过陷阱之间的相互影响。

**关键步骤：**
1. **净收益计算**：每个陷阱i的净收益为`a_i - (n - i - 1)`（0-based索引），表示跳过该陷阱能减少的伤害。
2. **选择k个最大收益**：排序后选取前k个最大的净收益。
3. **调整总收益**：因跳过顺序导致的重复计算，需减去`k*(k-1)/2`。

**可视化设计思路：**
- **动画方案**：用网格展示陷阱，选中跳过的陷阱高亮为红色。每次跳过时，后续陷阱颜色渐变表示伤害增加。
- **颜色标记**：当前选中陷阱用闪烁效果，后续陷阱颜色加深。
- **交互控制**：允许调整k值，实时显示总伤害变化，并高亮当前调整项。

### 题解清单 (≥4星)
1. **Eric998（5星）**  
   - 思路清晰，推导严谨，代码简洁高效。通过数学验证调整项`k*(k-1)/2`，正确解决陷阱间的影响。
2. **happy_dengziyue（5星）**  
   - 详细推导总收益公式，代码实现直观。通过维护跳过次数动态计算伤害，逻辑明确。
3. **suyunqiaoKID（4星）**  
   - 代码可读性高，模拟过程清晰。直接标记跳过的陷阱，遍历时累加伤害，易于理解。

### 最优思路或技巧提炼
- **贪心策略**：选择净收益最大的k个陷阱。
- **调整项处理**：跳过陷阱间的相互影响导致总收益需减去`k*(k-1)/2`。
- **实现技巧**：将陷阱收益转换为`a_i + i`排序，避免直接处理索引偏移。

### 同类型题或类似算法套路
- **相似题目**：选择k个元素最大化/最小化总和，并处理元素间的依赖或影响。
- **通用解法**：将元素贡献转化为独立计算的指标，排序后贪心选择。

### 推荐类似题目
1. [CF1526C2 - Potions (Hard Version)](https://www.luogu.com.cn/problem/CF1526C2)  
2. [P1094 - 纪念品分组](https://www.luogu.com.cn/problem/P1094)  
3. [P1230 - 智力大冲浪](https://www.luogu.com.cn/problem/P1230)  

### 个人心得摘录
- **调试教训**：初始计算忽略陷阱间的相互影响，需通过数学推导发现调整项。
- **顿悟点**：将复杂相互影响转化为独立指标排序，简化问题。

### 代码片段（Eric998）
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define int long long

void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int sum = 0;
    for(int i=0; i<n; i++){
        cin >> a[i];
        sum += a[i];
        a[i] -= n - i - 1; // 计算净收益
    }
    sort(a.rbegin(), a.rend());
    for(int i=0; i<k; i++) sum -= a[i]; // 选最大k个
    cout << sum - k*(k-1)/2 << "\n"; // 调整项
}

signed main(){
    int t; cin >> t;
    while(t--) solve();
    return 0;
}
```

### 可视化与算法演示
- **复古像素风格**：陷阱用8位像素块表示，选中时播放跳跃音效。
- **Canvas动画**：实时显示总伤害计算，调整项出现时闪动提示。
- **交互功能**：滑动条调节k值，自动更新选中陷阱及总伤害。

---
处理用时：223.90秒