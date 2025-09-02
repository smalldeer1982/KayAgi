# 题目信息

# [USACO08MAR] Pearl Pairing G

## 题目描述

At Bessie's recent birthday party, she received $N(2 \le N \le 10^5,N\equiv0\pmod{2})$ pearls, each painted one of C different colors ($1\le C \le N$).

Upon observing that the number of pearls $N$ is always even, her creative juices flowed and she decided to pair the pearls so that each pair of pearls has two different colors.

Knowing that such a set of pairings is always possible for the supplied testcases, help Bessie perform such a pairing. If there are multiple ways of creating a pairing, any solution suffices.

在 Bessie 最近的生日聚会上，她收到 $N(2\le N \le 10^5,N\equiv0\pmod{2})$ 颗珍珠。一共有 $C$ 种颜色的珍珠（$1\le C \le N$），第 $i$ 种颜色的珍珠有 $C_i$ 颗。


观察到珍珠的数量 $N$ 总是偶数，她的创意来了，决定配对珍珠，使每对珍珠有两种不同的颜色。数据保证存在答案。请帮助 Bessie 执行这样的配对，如果有多种配对的方法，输出任意一种即可。

## 说明/提示

There are $8$ pearls and $3$ different colors. Two pearls have color $\mathrm{I}$; two have color $\mathrm{II}$; four have color $\mathrm{III}$.


Bessie pairs each pearl of color $\mathrm{III}$ with one of color $\mathrm{I}$ and $\mathrm{Ii}$.

说明：有 $8$ 颗珍珠和 $3$ 种不同的颜色。两颗珍珠颜色为 $1$，两颗珍珠颜色为 $2$，四颗珍珠颜色为 $3$。

Bessie 将每颗颜色为 $3$ 的珍珠与颜色为 $1$ 和 $2$ 的珍珠配对。

感谢@[线段木](https://www.luogu.com.cn/user/33930) 提供翻译，@[PineappleSummer](https://www.luogu.com.cn/user/880187) 修正翻译以及提供 $\LaTeX$。

## 样例 #1

### 输入

```
8 3 
2 
2 
4 
```

### 输出

```
1 3 
1 3 
2 3 
3 2 
```

# AI分析结果



### 综合分析与结论  
本题要求将N颗珍珠两两配对（颜色不同），核心条件是任何颜色数量≤N/2。最优解法利用该条件，将珍珠按颜色展开成数组后，前半与后半直接配对。该方法时间复杂度O(N)，无需排序，正确性由题目条件保证。其他解法（如优先队列、复杂贪心）正确但效率或复杂度略逊。

---

### 精选题解  
1. **作者：Waddles（5星）**  
   **关键亮点**：  
   - 思路极简：将颜色展开为数组后直接i与i+n/2配对。  
   - 时间复杂度O(N)，代码极短（仅10行核心）。  
   **代码核心**：  
   ```cpp
   for(int i=1;i<=n/2;i++) 
       printf("%d %d\n",a[i],a[i+n/2]);
   ```

2. **作者：Exber（5星）**  
   **关键亮点**：  
   - 与Waddles解法一致，代码更加简洁（无快读模板）。  
   - 数组命名清晰，直接体现核心逻辑。  
   **代码核心**：  
   ```cpp
   for(int i=1;i<=n/2;i++)
       printf("%d %d\n",num[i],num[i+n/2]);
   ```

3. **作者：御·Dragon（4星）**  
   **关键亮点**：  
   - 详细分析抽屉原理，解释正确性。  
   - 指出“数据太水无需排序”，强调算法核心。  
   **代码核心**：  
   ```cpp
   for(rg int i=1;i<=n; ++i)
       out(s[i]),cout<<" ",outn(s[i + n]);
   ```

---

### 最优思路总结  
**关键技巧**：  
- **数组分割法**：展开颜色后，前半与后半配对。由题目条件（颜色数量≤N/2）保证同一颜色不会同时出现在i和i+n/2位置。  
- **无需排序**：输入顺序不影响正确性，直接展开即可。  

---

### 同类题目推荐  
1. **P1094 纪念品分组**（贪心，两两配对最小化组数）  
2. **P1102 A-B 数对**（数组配对问题，哈希优化）  
3. **P3143 [USACO16OPEN] Diamond Collector S**（滑动窗口，极值配对）  

---

### 个人心得摘录  
- **御·Dragon**：“数据太水，不排序也能过”——强调题目条件的重要性。  
- **qingfengwuhui**：“最后余下6颗同色珍珠需交换配对”——复杂贪心的陷阱，反衬最优解法的简洁性。  
- **木木！**：“找不出反例就对了”——正确性证明的直观理解。

---
处理用时：47.21秒