# 题目信息

# Sea Battle

## 题目描述

Galya is playing one-dimensional Sea Battle on a $ 1×n $ grid. In this game $ a $ ships are placed on the grid. Each of the ships consists of $ b $ consecutive cells. No cell can be part of two ships, however, the ships can touch each other.

Galya doesn't know the ships location. She can shoot to some cells and after each shot she is told if that cell was a part of some ship (this case is called "hit") or not (this case is called "miss").

Galya has already made $ k $ shots, all of them were misses.

Your task is to calculate the minimum number of cells such that if Galya shoot at all of them, she would hit at least one ship.

It is guaranteed that there is at least one valid ships placement.

## 说明/提示

There is one ship in the first sample. It can be either to the left or to the right from the shot Galya has already made (the "1" character). So, it is necessary to make two shots: one at the left part, and one at the right part.

## 样例 #1

### 输入

```
5 1 2 1
00100
```

### 输出

```
2
4 2
```

## 样例 #2

### 输入

```
13 3 2 3
1000000010001
```

### 输出

```
2
7 11
```

# AI分析结果



# 海战（Sea Battle）

## 题目描述

Galya 在一个 $1×n$ 的网格上进行一维海战游戏。该游戏中有 $a$ 艘船，每艘船占据 $b$ 个连续单元格，且船只不能重叠（但可以相邻）。Galya 不知道船的位置，但她已经进行了 $k$ 次射击且均为未命中。求她至少需要再射击多少个单元格才能确保击中至少一艘船，并输出这些位置。

**输入格式**  
第一行四个整数 $n,a,b,k$  
第二行一个长度为 $n$ 的字符串，'0' 表示未射击的位置，'1' 表示已射击的位置

**输出格式**  
第一行一个整数表示最少射击次数  
第二行按升序输出射击位置（任意合法解均可）

## 算法分类
贪心

---

## 题解分析与结论

### 核心思路
1. **连续区域划分**：遍历网格，统计连续未被射击（'0'）的区间。
2. **关键点射击**：在每个连续区间中，每隔 $b$ 个位置设置一个必射点，确保覆盖所有可能的船只位置。
3. **最优化调整**：最终射击次数为总必射点数量减去 $(a-1)$，因为只需确保击中至少一艘船。

### 解决难点
- **间隔处理**：正确处理连续 '0' 区域的划分，确保每个长度为 $b$ 的子区间都被覆盖。
- **数学推导**：理解为什么总必射点减 $(a-1)$ 即为最优解（排除其他 $a-1$ 艘船的放置可能）。

---

## 精选题解

### 题解1：Yizhixiaoyun（★★★★★）
**关键亮点**  
- 代码简洁高效，直接维护计数器统计连续0的个数。
- 使用数组存储必射点，逻辑清晰。
- 时间复杂度 $O(n)$，空间复杂度 $O(n)$。

**核心代码**  
```cpp
for(register int i=0;i<n;++i){
    if(s[i]=='1') cnt=0;
    else if(++cnt == b) {
        f[++ans]=i+1; // 记录射击位置
        cnt=0; // 重置计数器
    }
}
ans -= a-1; // 优化射击次数
```

### 题解2：AC_love（★★★★☆）
**关键亮点**  
- 通过最不利原则类比抽屉问题，增强思路理解。
- 详细推导间隔划分的数学原理，适合初学者。

**个人心得**  
> "将每个连续 $0$ 区间视为多个抽屉，射击 $p-a+1$ 次即可确保命中。这种转化思想值得借鉴。"

**核心代码**  
```cpp
for(int i = 0; i < n; i++){
    if(s[i] == '0') itv++;
    else itv = 0;
    if(itv >= b){
        s[i] = '1'; // 标记为已覆盖
        ans++;
        itv = 0;
    }
}
cout << ans - a + 1;
```

### 题解3：codeLJH114514（★★★★☆）
**关键亮点**  
- 预处理字符串末尾添加 '1' 简化边界判断。
- 使用向量动态存储射击点，避免数组越界。

**核心代码**  
```cpp
s += "1"; // 简化边界处理
for(int i=0; i<=n; i++){
    if(s[i] == '0') LenZero++;
    else {
        ANS += LenZero / b; // 计算必射点
        LenZero = 0;
    }
}
ANS -= a-1; // 优化结果
```

---

## 关键技巧总结
1. **贪心覆盖**：在连续区域中每 $b$ 个单位设置检查点，确保覆盖所有可能情况。
2. **边界处理**：在字符串末尾补 '1' 可简化循环中的边界判断。
3. **数学优化**：通过 $ans - (a-1)$ 快速计算最少射击次数，避免复杂逻辑。

---

## 同类题目推荐
1. [P1325 雷达安装](https://www.luogu.com.cn/problem/P1325)（区间覆盖问题）
2. [P1209 修理牛棚](https://www.luogu.com.cn/problem/P1209)（贪心间隔处理）
3. [P2870 最佳牛围栏](https://www.luogu.com.cn/problem/P2870)（最大化平均值，贪心结合二分）

---
处理用时：75.56秒