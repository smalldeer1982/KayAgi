# 题目信息

# A Prosperous Lot

## 题目描述

Apart from Nian, there is a daemon named Sui, which terrifies children and causes them to become sick. Parents give their children money wrapped in red packets and put them under the pillow, so that when Sui tries to approach them, it will be driven away by the fairies inside.

Big Banban is hesitating over the amount of money to give out. He considers loops to be lucky since it symbolizes unity and harmony.

He would like to find a positive integer $ n $ not greater than $ 10^{18} $ , such that there are exactly $ k $ loops in the decimal representation of $ n $ , or determine that such $ n $ does not exist.

A loop is a planar area enclosed by lines in the digits' decimal representation written in Arabic numerals. For example, there is one loop in digit $ 4 $ , two loops in $ 8 $ and no loops in $ 5 $ . Refer to the figure below for all exact forms.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF934B/ef09358ad2ff9bd7af31e67d589f7cc1105bcc74.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
462```

## 样例 #2

### 输入

```
6
```

### 输出

```
8080```

# AI分析结果



# A Prosperous Lot

## 题目描述

除了年兽，还有一个叫“祟”的恶魔，它会惊吓孩子使他们生病。父母会将钱装在红包里放在孩子的枕头下，当祟靠近时，里面的精灵会驱赶它。

大班班在犹豫该给多少钱。他认为循环是幸运的，象征着团结与和谐。

他需要找到一个不大于 $10^{18}$ 的正整数 $n$，使得其十进制表示中恰好包含 $k$ 个环，或判断这样的数不存在。

环是指阿拉伯数字中用线条围成的封闭区域。例如：
- 数字 $4$ 有 1 个环
- 数字 $8$ 有 2 个环
- 数字 $5$ 没有环

各数字环数如下表：
| 数字 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|------|---|---|---|---|---|---|---|---|---|---|
| 环数 | 1 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 2 | 1 |

---

## 题解综合分析

### 核心思路
1. **贪心策略**：优先使用环数最多的数字8（每个8贡献2环）
2. **边界判断**：最大可能环数为36（18个8），故当k>36时无解
3. **奇偶处理**：
   - 偶数k：直接输出k/2个8
   - 奇数k：输出(k-1)/2个8 + 1个单环数字（4/6/9）
4. **正整数限制**：不能使用0来补环（如k=1时输出4而非0）

### 最优题解精选

#### 题解1：Anguei（★★★★★）
**关键亮点**：
- 代码最简洁，逻辑清晰
- 直接处理奇偶情况，用4补足奇数余量
- 时间复杂度O(k/2)

```cpp
#include <iostream>
int main() {
    int k;
    std::cin >> k;
    if (k > 36) std::cout << -1;
    else {
        for (int i = 1; i <= k / 2; ++i) std::cout << 8;
        if (k % 2) std::cout << 4;
    }
}
```

#### 题解2：Creroity（★★★★☆）
**亮点**：
- 明确说明奇数的补数选择6
- 代码包含注释，适合教学

```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
int main(){
    cin>>k;
    if(k>36) cout<<-1;
    else {
        for(int i=1;i<=k/2;i++) cout<<8;
        if(k%2==1) cout<<6;
    }
}
```

#### 题解3：李至擎（★★★★☆）
**个人心得**：
- 强调不能使用0的陷阱
- 代码结构工整，适合阅读

```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
int main() {
    cin>>k;
    if(k>36) { cout<<-1; return 0; }
    if(k%2==1) cout<<6;
    for(int i=1;i<=k/2;i++) cout<<8;
}
```

---

## 关键技巧总结
1. **贪心构造**：在允许范围内使用最大收益元素（8）
2. **边界意识**：通过数学推导确定最大可行值（36）
3. **特例处理**：单独处理奇数情况，避免无效解（如0）
4. **代码精简**：利用循环次数直接控制输出格式

---

## 拓展练习
1. [CF939E - Maximize!](https://www.luogu.com.cn/problem/CF939E)（贪心构造极值）
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（贪心策略与数位处理）
3. [P1323 删数问题](https://www.luogu.com.cn/problem/P1323)（数字构造与优化）

---
处理用时：48.86秒