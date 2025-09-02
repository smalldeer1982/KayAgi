# 题目信息

# Saving the City

## 题目描述

Bertown is a city with $ n $ buildings in a straight line.

The city's security service discovered that some buildings were mined. A map was compiled, which is a string of length $ n $ , where the $ i $ -th character is "1" if there is a mine under the building number $ i $ and "0" otherwise.

Bertown's best sapper knows how to activate mines so that the buildings above them are not damaged. When a mine under the building numbered $ x $ is activated, it explodes and activates two adjacent mines under the buildings numbered $ x-1 $ and $ x+1 $ (if there were no mines under the building, then nothing happens). Thus, it is enough to activate any one mine on a continuous segment of mines to activate all the mines of this segment. For manual activation of one mine, the sapper takes $ a $ coins. He can repeat this operation as many times as you want.

Also, a sapper can place a mine under a building if it wasn't there. For such an operation, he takes $ b $ coins. He can also repeat this operation as many times as you want.

The sapper can carry out operations in any order.

You want to blow up all the mines in the city to make it safe. Find the minimum number of coins that the sapper will have to pay so that after his actions there are no mines left in the city.

## 说明/提示

In the second test case, if we place a mine under the fourth building and then activate it, then all mines on the field are activated. The cost of such operations is six, $ b=1 $ coin for placing a mine and $ a=5 $ coins for activating.

## 样例 #1

### 输入

```
2
1 1
01000010
5 1
01101110```

### 输出

```
2
6```

# AI分析结果

### 题目内容重写
#### 题目描述
Bertown 是一个由 $n$ 座建筑排成一条直线的城市。

城市的安全部门发现一些建筑下埋有地雷。他们绘制了一张地图，地图是一个长度为 $n$ 的字符串，其中第 $i$ 个字符为 "1" 表示第 $i$ 座建筑下有地雷，为 "0" 则表示没有。

Bertown 最好的工兵知道如何引爆地雷，使得地雷上方的建筑不受损坏。当引爆第 $x$ 座建筑下的地雷时，它会爆炸并激活相邻的两座建筑下的地雷，即第 $x-1$ 和第 $x+1$ 座建筑下的地雷（如果这些建筑下没有地雷，则不会发生任何事情）。因此，只要引爆一个连续地雷段中的任意一个地雷，就可以激活该段中的所有地雷。手动引爆一个地雷需要花费 $a$ 枚硬币，工兵可以重复进行此操作。

此外，工兵可以在没有地雷的建筑下放置地雷，每次操作需要花费 $b$ 枚硬币。他也可以重复进行此操作。

工兵可以以任意顺序执行这些操作。

你的目标是引爆城市中的所有地雷，使城市变得安全。求工兵需要支付的最少硬币数，以确保操作后城市中没有地雷。

#### 说明/提示
在第二个测试用例中，如果我们在第四座建筑下放置一个地雷并引爆它，那么地图上的所有地雷都会被激活。这样的操作花费为 6，其中 $b=1$ 枚硬币用于放置地雷，$a=5$ 枚硬币用于引爆。

#### 样例 #1
##### 输入
```
2
1 1
01000010
5 1
01101110
```
##### 输出
```
2
6
```

### 算法分类
动态规划

### 题解分析与结论
本题的核心是通过动态规划来求解最小花费。大多数题解都采用了线性 DP 的思路，状态转移方程的设计是关键。题解中常见的思路是：
1. 定义 $dp_i$ 表示将前 $i$ 个字符全部变为 0 的最小代价。
2. 当 $s_i = 0$ 时，$dp_i = dp_{i-1}$。
3. 当 $s_i = 1$ 时，有两种选择：直接引爆当前地雷，或者将前面的 0 变为 1 后再引爆。

难点在于如何高效地处理连续的 0 和 1，以及如何优化状态转移方程。部分题解通过前缀和或单调队列来优化时间复杂度。

### 评分较高的题解
#### 题解作者：Suuon_Kanderu (赞：4)
- **星级**：4.5
- **关键亮点**：状态转移方程清晰，代码简洁，处理了连续的 0 和 1 的情况。
- **核心代码**：
```cpp
for(i++; i < s.size(); i++) {
    if(s[i] == '0') dp[i] = dp[i - 1];
    else {
        dp[i] = dp[last] + min(a , (i - last - 1) * b);
        last = i;    
    }
}
```
- **个人心得**：作者提到第一个 `1` 只能用一个 A 操作，这一点在状态转移中得到了很好的体现。

#### 题解作者：MYCui (赞：3)
- **星级**：4
- **关键亮点**：详细的状态转移方程解释，处理了前导和后缀的 0，代码结构清晰。
- **核心代码**：
```cpp
if(s[i] == '1') {
    if(s[i - 1] == '1') dp[i][1] = dp[i - 1][1];
    else dp[i][1] = min(dp[i - 1][1] , dp[i - 1][0] + A);
}
```
- **个人心得**：作者通过 HACK 数据验证了算法的正确性，增加了题解的可靠性。

#### 题解作者：ACtheQ (赞：2)
- **星级**：4
- **关键亮点**：简单易懂的 DP 思路，代码实现简洁，适合初学者理解。
- **核心代码**：
```cpp
if(cnt!=-1) f[i]=min(f[i-1]+x,f[cnt]+(i-cnt-1)*y);
else f[i]=f[i-1]+x;
```
- **个人心得**：作者通过简单的例子解释了状态转移的思路，便于理解。

### 最优关键思路
1. **状态转移方程**：$dp_i = \min(dp_{i-1} + a, dp_{last} + (i - last - 1) \times b)$，其中 $last$ 是前一个 1 的位置。
2. **优化技巧**：通过记录前一个 1 的位置，减少不必要的计算，时间复杂度为 $O(n)$。

### 拓展思路
类似的问题可以出现在其他需要分段处理的场景中，如字符串分割、区间覆盖等。可以通过类似的 DP 思路进行优化。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 动态规划经典问题
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060) - 动态规划与背包问题
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091) - 动态规划与序列处理

---
处理用时：42.56秒