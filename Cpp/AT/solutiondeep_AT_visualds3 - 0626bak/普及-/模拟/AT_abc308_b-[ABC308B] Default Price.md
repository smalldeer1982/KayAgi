# 题目信息

# [ABC308B] Default Price

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc308/tasks/abc308_b

高橋くんは回転寿司で $ N $ 皿の料理を食べました。 $ i $ 皿目の色は文字列 $ C_i $ で表されます。

また、料理の価格は皿の色と対応し、 $ i=1,\ldots,M $ のそれぞれについて、色が文字列 $ D_i $ の皿の料理は一皿 $ P_i $ 円です。また、$ D_1,\ldots,D_M $ のいずれとも異なる色の皿の料理は一皿 $ P_0 $ 円です。

高橋くんが食べた料理の価格の合計を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N,M\leq\ 100 $
- $ C_i,D_i $ は英小文字からなる長さ $ 1 $ 以上 $ 20 $ 以下の文字列
- $ D_1,\ldots,D_M $ はすべて異なる
- $ 1\leq\ P_i\leq\ 10000 $
- $ N,M,P_i $ は整数
 
### Sample Explanation 1

`blue` の皿は $ P_1\ =\ 1600 $ 円、`red` の皿は $ P_2\ =\ 2800 $ 円、`green` の皿は $ P_0\ =\ 800 $ 円です。 高橋くんが食べた料理の価格の合計は、$ 2800+800+1600=5200 $ 円です。

## 样例 #1

### 输入

```
3 2

red green blue

blue red

800 1600 2800```

### 输出

```
5200```

## 样例 #2

### 输入

```
3 2

code queen atcoder

king queen

10 1 1```

### 输出

```
21```

# AI分析结果



## 唯一算法分类
无算法分类

## 综合分析与结论
该题属于简单模拟题，核心在于正确建立颜色与价格的映射关系，并通过遍历求和计算总价。关键点包括：

1. **输入处理与映射构建**  
   - 第四行输入的 P 数组中，P[0] 是默认价格，后续元素对应 D 数组中的颜色价格。需注意 D[i] 对应 P[i+1]。
   - 使用哈希表（如 `unordered_map`）快速将 D 中的颜色映射到对应价格。

2. **核心流程**  
   - 遍历每个盘子的颜色，若存在于哈希表中，累加对应价格；否则累加默认价格 P0。

3. **可视化设计**  
   - **动画演示**：在 Canvas 上展示颜色匹配过程。每处理一个颜色时，高亮当前颜色，若匹配成功则显示对应价格，否则显示 P0。
   - **音效提示**：匹配成功时播放短促音效，未匹配则播放较低音调。
   - **像素风格**：用 8 位风格渲染颜色块和价格，增强趣味性。

## 最优思路提炼
1. **哈希表映射**  
   使用哈希表将颜色到价格的映射预计算，查询时间复杂度为 O(1)，极大优化效率。
2. **输入处理技巧**  
   注意 P 数组的索引与 D 数组的对应关系（P[i+1] 对应 D[i]），避免逻辑错误。

## 核心代码实现
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> C(N);
    for (int i = 0; i < N; ++i) cin >> C[i];
    
    vector<string> D(M);
    for (int i = 0; i < M; ++i) cin >> D[i];
    
    vector<int> P(M + 1);
    for (int i = 0; i <= M; ++i) cin >> P[i];
    
    unordered_map<string, int> color_price;
    for (int i = 0; i < M; ++i) color_price[D[i]] = P[i + 1];
    
    int total = 0;
    for (const string& color : C) {
        if (color_price.count(color)) total += color_price[color];
        else total += P[0];
    }
    
    cout << total << endl;
    return 0;
}
```

## 可视化设计要点
1. **像素动画**  
   - 颜色块以 16x16 像素方块显示，匹配成功时方块变为绿色，未匹配为红色。
   - 价格数值以 8 位字体叠加在颜色块下方。
2. **音效触发**  
   - 匹配成功：播放“叮”声（高频）。
   - 默认价格：播放“咚”声（低频）。
3. **自动演示模式**  
   - 按固定时间间隔逐步处理每个颜色，支持暂停/继续。

---
处理用时：89.00秒