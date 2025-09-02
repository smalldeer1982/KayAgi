# 题目信息

# Tokitsukaze and Two Colorful Tapes

## 题目描述

Tokitsukaze has two colorful tapes. There are $ n $ distinct colors, numbered $ 1 $ through $ n $ , and each color appears exactly once on each of the two tapes. Denote the color of the $ i $ -th position of the first tape as $ ca_i $ , and the color of the $ i $ -th position of the second tape as $ cb_i $ .

Now Tokitsukaze wants to select each color an integer value from $ 1 $ to $ n $ , distinct for all the colors. After that she will put down the color values in each colored position on the tapes. Denote the number of the $ i $ -th position of the first tape as $ numa_i $ , and the number of the $ i $ -th position of the second tape as $ numb_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ba8639f69fd74760b5261096016619c105b9cbe6.png)For example, for the above picture, assuming that the color red has value $ x $ ( $ 1 \leq x \leq n $ ), it appears at the $ 1 $ -st position of the first tape and the $ 3 $ -rd position of the second tape, so $ numa_1=numb_3=x $ .

Note that each color $ i $ from $ 1 $ to $ n $ should have a distinct value, and the same color which appears in both tapes has the same value.

After labeling each color, the beauty of the two tapes is calculated as $ $$$\sum_{i=1}^{n}|numa_i-numb_i|. $ $$$

Please help Tokitsukaze to find the highest possible beauty.

## 说明/提示

An optimal solution for the first test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/eb5a2fd8a44a35877d106dc26e9dcf9fd0a2a486.png)The beauty is $ \left|4-3 \right|+\left|3-5 \right|+\left|2-4 \right|+\left|5-2 \right|+\left|1-6 \right|+\left|6-1 \right|=18 $ .

An optimal solution for the second test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ec6542f7ba45f38760ee0d113e52ba6999ceef87.png)The beauty is $ \left|2-2 \right|+\left|1-6 \right|+\left|3-3 \right|+\left|6-1 \right|+\left|4-4 \right|+\left|5-5 \right|=10 $ .

## 样例 #1

### 输入

```
3
6
1 5 4 3 2 6
5 3 1 4 6 2
6
3 5 4 6 2 1
3 6 4 5 2 1
1
1
1```

### 输出

```
18
10
0```

# AI分析结果



### 中文重写题目

**题目名称：** Tokitsukaze 和两色彩带

**题目描述：**  
Tokitsukaze 有两条彩带，每条彩带有 $n$ 种不同的颜色，颜色编号为 $1$ 到 $n$，每种颜色在每条彩带上各出现一次。记第一条彩带第 $i$ 个位置的颜色为 $ca_i$，第二条彩带第 $i$ 个位置的颜色为 $cb_i$。  

Tokitsukaze 需要为每个颜色分配一个 $1$ 到 $n$ 的唯一整数值。设颜色 $i$ 的值为 $num_i$，则第一条彩带第 $i$ 个位置的值为 $num_{ca_i}$，第二条彩带第 $i$ 个位置的值为 $num_{cb_i}$。两彩带的“美感”定义为 $\sum_{i=1}^{n} |num_{ca_i} - num_{cb_i}|$。求最大可能的“美感”。

**输入样例：**  
```
3
6
1 5 4 3 2 6
5 3 1 4 6 2
6
3 5 4 6 2 1
3 6 4 5 2 1
1
1
1
```
**输出样例：**  
```
18
10
0
```

---

### 题解分析与结论

#### 关键思路
1. **置换环模型**：将每个颜色在两个彩带中的位置对应关系建模为图，形成多个独立环。例如，颜色 $x$ 在第一条彩带的位置 $i$，对应第二条彩带的位置 $j$，形成有向边 $i \to j$，最终所有边构成多个环。
2. **最大化贡献**：每个环的贡献取决于其长度 $L$。最优策略是为每个环分配 $\lfloor L/2 \rfloor$ 对“山峰-山谷”（大数-小数），总贡献公式为 $2k(n-k)$，其中 $k$ 是所有环的 $\lfloor L/2 \rfloor$ 之和。
3. **数学推导**：通过最大化绝对值差的组合，将问题转化为统计环结构，利用排列的极值性质快速计算。

#### 最优题解摘录

**题解作者：I_am_Accepted（★★★★★）**  
- **亮点**：清晰的理论推导（山峰-山谷模型）、代码简洁高效（DFS找环）。
- **代码核心**：  
  ```cpp
  int dfs(int x) {
      vis[x] = 1;
      return vis[b[x]] ? 1 : 1 + dfs(b[x]);
  }
  void work() {
      // 输入处理构建映射关系
      For(i, 1, n) if (!vis[i]) ans += dfs(i) >> 1;
      cout << 2 * ans * (n - ans) << endl;
  }
  ```

**题解作者：Renshey（★★★★☆）**  
- **亮点**：代码高度精简，快速处理输入与环统计。
- **代码核心**：  
  ```cpp
  for (int j = i; !vis[j]; j = b[a[j]]) 
      vis[j] = true, len++;
  w += len >> 1;
  ```

**题解作者：Leasier（★★★★☆）**  
- **亮点**：详细拆解绝对值贡献，强调贪心策略。

---

### 关键代码实现
```cpp
// 以 I_am_Accepted 的代码为例
void work() {
    cin >> n;
    For(i, 1, n) {
        int x; cin >> x;
        a[x] = i; // 记录颜色x在第一条彩带的位置
    }
    For(i, 1, n) {
        int x; cin >> x;
        b[i] = a[x]; // 第二条彩带位置i的颜色对应第一条的位置
    }
    int ans = 0;
    For(i, 1, n) if (!vis[i]) ans += dfs(i) >> 1; // 统计所有环的贡献
    cout << 2 * ans * (n - ans) << endl;
}
```

---

### 拓展与相似题目
1. **置换环基础**：  
   - 洛谷 P2661 [信息传递](https://www.luogu.com.cn/problem/P2661)（最小环长度）
   - 洛谷 P5149 [会议座位](https://www.luogu.com.cn/problem/P5149)（逆序对与置换环）
2. **贪心极值问题**：  
   - 洛谷 P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)（哈夫曼树，贪心策略）

---

### 个人心得摘录
- **并查集陷阱**：某题解尝试用并查集统计环，但未正确处理映射关系，导致错误。务必验证模型正确性。
- **数学洞察**：将复杂排列问题转化为环结构，极大简化分析，体现图论与贪心的结合威力。

---
处理用时：161.21秒