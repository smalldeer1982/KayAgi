# 题目信息

# [USACO06DEC] River Hopscotch S

## 题目描述

Every year the cows hold an event featuring a peculiar version of hopscotch that involves carefully jumping from rock to rock in a river. The excitement takes place on a long, straight river with a rock at the start and another rock at the end, L units away from the start (1 ≤ L ≤ 1,000,000,000). Along the river between the starting and ending rocks, N (0 ≤ N ≤ 50,000) more rocks appear, each at an integral distance Di from the start (0 < Di < L).

To play the game, each cow in turn starts at the starting rock and tries to reach the finish at the ending rock, jumping only from rock to rock. Of course, less agile cows never make it to the final rock, ending up instead in the river.

Farmer John is proud of his cows and watches this event each year. But as time goes by, he tires of watching the timid cows of the other farmers limp across the short distances between rocks placed too closely together. He plans to remove several rocks in order to increase the shortest distance a cow will have to jump to reach the end. He knows he cannot remove the starting and ending rocks, but he calculates that he has enough resources to remove up to M rocks (0 ≤ M ≤ N).

FJ wants to know exactly how much he can increase the shortest distance \*before\* he starts removing the rocks. Help Farmer John determine the greatest possible shortest distance a cow has to jump after removing the optimal set of M rocks.

奶牛跳房子：从N块石头中移除M块，使得间距最小值最大。


## 说明/提示

Before removing any rocks, the shortest jump was a jump of 2 from 0 (the start) to 2. After removing the rocks at 2 and 14, the shortest required jump is a jump of 4 (from 17 to 21 or from 21 to 25).


## 样例 #1

### 输入

```
25 5 2
2
14
11
21
17```

### 输出

```
4```

# AI分析结果



### 综合分析与结论
本题为经典二分答案问题，核心思路是枚举最短跳跃距离的最大值，通过贪心策略统计需移除的石头数量，验证可行性。所有题解均采用二分框架，差异主要在边界处理与代码实现细节。关键点包括：必须排序、处理终点石头、正确统计移除数量。

### 高星题解推荐

#### 1. 作者：yuyer（★★★★☆）
**关键亮点**  
- 提供两种判断函数实现（统计保留数/移除数），增强理解  
- 代码结构清晰，变量命名规范，主程序逻辑简明  
- 明确终点处理与排序的必要性  

**核心代码**  
```cpp
int check(int s) {
    int j = 0, c = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] - a[j] < s) c++;
        else j = i;
    }
    return c; // 直接返回需移除的数量
}
```

#### 2. 作者：seek_my_calling（★★★★☆）
**关键亮点**  
- 代码简洁高效，直接体现二分框架  
- 明确终点石头的处理（a[n+1] = L）  
- 变量命名稍简但逻辑清晰  

**核心代码**  
```cpp
int count(int mid) {
    int j = 0, x = 0;
    for (int i = 1; i <= n+1; i++) {
        if (a[i]-a[j] < mid) x++;
        else j = i;
    }
    return x; // 移除数量
}
```

#### 3. 作者：codeboyzzb（★★★★☆）
**关键亮点**  
- 处理了n=0且m=0的特殊情况  
- 代码包含详细注释与调试经验  
- 使用更稳健的二分模板（while(l+1<r)）  

**个人心得**  
> "OJ上有一组坑人数据：0块石头...直接输出长度" —— 强调边界测试的重要性

### 关键思路总结
1. **预处理**：将终点加入数组并排序  
2. **二分框架**：左界0，右界L，每次计算mid验证  
3. **贪心验证**：遍历石头，若间距<mid则移除当前石头，统计总移除数是否≤M  
4. **边界处理**：特别注意n=0、m=0等极端情况  

### 拓展练习
1. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)（同题数据加强版）  
2. [P1824 进击的奶牛](https://www.luogu.com.cn/problem/P1824)（最大化最小间隔）  
3. [P1316 丢瓶盖](https://www.luogu.com.cn/problem/P1316)（最小化最大间隔）  

### 重点代码片段
```cpp
// 典型二分主逻辑
int l = 0, r = L, ans = 0;
while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid)) {
        ans = mid;
        l = mid + 1;
    } else {
        r = mid - 1;
    }
}
// check函数示例
bool check(int d) {
    int cnt = 0, last = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] - last < d) cnt++;
        else last = a[i];
    }
    return cnt <= m;
}
```

---
处理用时：61.11秒