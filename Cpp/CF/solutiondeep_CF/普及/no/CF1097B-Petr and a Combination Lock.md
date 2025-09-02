# 题目信息

# Petr and a Combination Lock

## 题目描述

Petr has just bought a new car. He's just arrived at the most known Petersburg's petrol station to refuel it when he suddenly discovered that the petrol tank is secured with a combination lock! The lock has a scale of $ 360 $ degrees and a pointer which initially points at zero:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1097B/390f775757c241d3e93f871107696e4a8b8d123d.png)Petr called his car dealer, who instructed him to rotate the lock's wheel exactly $ n $ times. The $ i $ -th rotation should be $ a_i $ degrees, either clockwise or counterclockwise, and after all $ n $ rotations the pointer should again point at zero.

This confused Petr a little bit as he isn't sure which rotations should be done clockwise and which should be done counterclockwise. As there are many possible ways of rotating the lock, help him and find out whether there exists at least one, such that after all $ n $ rotations the pointer will point at zero again.

## 说明/提示

In the first example, we can achieve our goal by applying the first and the second rotation clockwise, and performing the third rotation counterclockwise.

In the second example, it's impossible to perform the rotations in order to make the pointer point at zero in the end.

In the third example, Petr can do all three rotations clockwise. In this case, the whole wheel will be rotated by $ 360 $ degrees clockwise and the pointer will point at zero again.

## 样例 #1

### 输入

```
3
10
20
30
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
10
10
10
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
120
120
120
```

### 输出

```
YES
```

# AI分析结果

【题目内容】
# Petr 和组合锁

## 题目描述

Petr 刚买了一辆新车。他刚刚到达圣彼得堡最著名的加油站加油时，突然发现油箱上装有一个组合锁！锁的刻度为 360 度，指针初始指向零度：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1097B/390f775757c241d3e93f871107696e4a8b8d123d.png)Petr 打电话给他的汽车经销商，经销商告诉他需要精确地旋转锁的轮子 n 次。第 i 次旋转应为 a_i 度，可以是顺时针或逆时针，且在所有 n 次旋转后，指针应再次指向零度。

这让 Petr 有些困惑，因为他不确定哪些旋转应该是顺时针，哪些应该是逆时针。由于有许多可能的旋转方式，帮助他找出是否存在至少一种方式，使得在所有 n 次旋转后，指针将再次指向零度。

## 说明/提示

在第一个示例中，我们可以通过将第一次和第二次旋转顺时针，第三次旋转逆时针来实现目标。

在第二个示例中，无法通过旋转使指针最终指向零度。

在第三个示例中，Petr 可以将所有三次旋转都顺时针进行。在这种情况下，整个轮子将顺时针旋转 360 度，指针将再次指向零度。

## 样例 #1

### 输入

```
3
10
20
30
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
10
10
10
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
120
120
120
```

### 输出

```
YES
```

【算法分类】
搜索

【题解分析与结论】
该题的核心是通过搜索（DFS 或 BFS）来枚举所有可能的旋转方向组合，判断是否存在一种组合使得最终指针回到零度。由于 n 的最大值为 15，总共有 2^15 = 32768 种可能的组合，因此搜索是可行的。

【所选题解】
1. **作者：ouuan (5星)**
   - **关键亮点**：使用动态规划的思路，通过状态转移表记录每一步旋转后的可能角度，最终判断是否可以达到零度。时间复杂度为 O(n * 360)，效率较高。
   - **代码实现**：
     ```cpp
     bool f[N][M];
     f[0][0] = true;
     for (i = 1; i <= n; ++i) {
         for (j = 0; j < M; ++j) {
             f[i][j] = (f[i-1][(j+a[i])%M] | f[i-1][((j-a[i])%M+M)%M]);
         }
     }
     if (f[n][0]) puts("YES");
     else puts("NO");
     ```

2. **作者：zjinyi (4星)**
   - **关键亮点**：使用二进制枚举的方法，通过位运算表示旋转方向，简洁高效。时间复杂度为 O(2^n)，适用于 n 较小的情况。
   - **代码实现**：
     ```cpp
     for (int i = 0; i < (1 << n); ++i) {
         int sum = 0;
         for (int j = 0; j < n; ++j) {
             if ((i >> j & 1) == 1) sum += a[j];
             else sum -= a[j];
         }
         if (sum % 360 == 0) {
             cout << "YES";
             return 0;
         }
     }
     cout << "NO";
     ```

3. **作者：Jerry_heng (4星)**
   - **关键亮点**：在 DFS 中加入了剪枝优化，通过记录已经访问过的状态来避免重复计算，提高了搜索效率。
   - **代码实现**：
     ```cpp
     bool vis[16][360];
     void dfs(int k, int s) {
         if (vis[k][s]) return;
         vis[k][s] = 1;
         if (k > n) {
             if (s == 0) b = 1;
             return;
         }
         dfs(k+1, (s+a[k])%360);
         if (b) return;
         dfs(k+1, (s-a[k]+360)%360);
     }
     ```

【最优关键思路】
- **动态规划**：通过状态转移表记录每一步旋转后的可能角度，最终判断是否可以达到零度。适用于 n 较大的情况。
- **二进制枚举**：通过位运算表示旋转方向，简洁高效。适用于 n 较小的情况。
- **DFS 剪枝**：通过记录已经访问过的状态来避免重复计算，提高搜索效率。

【可拓展之处】
- 类似问题可以扩展到其他类型的组合问题，如背包问题、子集和问题等。
- 可以使用其他搜索优化技巧，如 A* 算法、双向 BFS 等。

【推荐题目】
1. P1036 选数（DFS 枚举子集）
2. P1219 八皇后（DFS 剪枝）
3. P1443 马的遍历（BFS 搜索）

---
处理用时：35.28秒