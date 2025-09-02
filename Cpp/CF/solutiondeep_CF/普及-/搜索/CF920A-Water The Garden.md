# 题目信息

# Water The Garden

## 题目描述

It is winter now, and Max decided it's about time he watered the garden.

The garden can be represented as $ n $ consecutive garden beds, numbered from $ 1 $ to $ n $ . $ k $ beds contain water taps ( $ i $ -th tap is located in the bed $ x_{i} $ ), which, if turned on, start delivering water to neighbouring beds. If the tap on the bed $ x_{i} $ is turned on, then after one second has passed, the bed $ x_{i} $ will be watered; after two seconds have passed, the beds from the segment $ [x_{i}-1,x_{i}+1] $ will be watered (if they exist); after $ j $ seconds have passed ( $ j $ is an integer number), the beds from the segment $ [x_{i}-(j-1),x_{i}+(j-1)] $ will be watered (if they exist). Nothing changes during the seconds, so, for example, we can't say that the segment $ [x_{i}-2.5,x_{i}+2.5] $ will be watered after $ 2.5 $ seconds have passed; only the segment $ [x_{i}-2,x_{i}+2] $ will be watered at that moment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/13bc7cf6794d83f150515b3ef05c019c5a177edb.png) The garden from test $ 1 $ . White colour denotes a garden bed without a tap, red colour — a garden bed with a tap.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/7701b634db65a2b1523162fa68f6ca25374deecc.png) The garden from test $ 1 $ after $ 2 $ seconds have passed after turning on the tap. White colour denotes an unwatered garden bed, blue colour — a watered bed. Max wants to turn on all the water taps at the same moment, and now he wonders, what is the minimum number of seconds that have to pass after he turns on some taps until the whole garden is watered. Help him to find the answer!

## 说明/提示

The first example consists of $ 3 $ tests:

1. There are $ 5 $ garden beds, and a water tap in the bed $ 3 $ . If we turn it on, then after $ 1 $ second passes, only bed $ 3 $ will be watered; after $ 2 $ seconds pass, beds $ [1,3] $ will be watered, and after $ 3 $ seconds pass, everything will be watered.
2. There are $ 3 $ garden beds, and there is a water tap in each one. If we turn all of them on, then everything will be watered after $ 1 $ second passes.
3. There are $ 4 $ garden beds, and only one tap in the bed $ 1 $ . It will take $ 4 $ seconds to water, for example, bed $ 4 $ .

## 样例 #1

### 输入

```
3
5 1
3
3 3
1 2 3
4 1
1
```

### 输出

```
3
1
4
```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

现在是冬天，Max决定是时候给花园浇水了。

花园可以表示为 $n$ 个连续的花坛，编号从 $1$ 到 $n$。其中有 $k$ 个花坛装有水龙头（第 $i$ 个水龙头位于花坛 $x_{i}$），如果打开水龙头，水会开始流向相邻的花坛。如果位于花坛 $x_{i}$ 的水龙头被打开，那么经过 $1$ 秒后，花坛 $x_{i}$ 会被浇水；经过 $2$ 秒后，花坛 $[x_{i}-1,x_{i}+1]$ 会被浇水（如果存在）；经过 $j$ 秒后，花坛 $[x_{i}-(j-1),x_{i}+(j-1)]$ 会被浇水（如果存在）。秒数必须是整数，因此不能出现半秒的情况。

Max希望同时打开所有水龙头，他想知道最少需要多少秒才能让整个花园都被浇水。请你帮助他找到答案。

#### 说明/提示

第一个样例包含 $3$ 个测试：

1. 有 $5$ 个花坛，且水龙头位于花坛 $3$。如果打开它，经过 $1$ 秒后，只有花坛 $3$ 会被浇水；经过 $2$ 秒后，花坛 $[1,3]$ 会被浇水；经过 $3$ 秒后，整个花园都会被浇水。
2. 有 $3$ 个花坛，且每个花坛都有一个水龙头。如果同时打开它们，经过 $1$ 秒后，整个花园都会被浇水。
3. 有 $4$ 个花坛，且水龙头位于花坛 $1$。需要 $4$ 秒才能浇到花坛 $4$。

#### 样例 #1

##### 输入

```
3
5 1
3
3 3
1 2 3
4 1
1
```

##### 输出

```
3
1
4
```

### 题解分析与结论

#### 综合分析

本题的核心是计算每个花坛被浇水的最短时间，并找出所有花坛中的最大值。题解主要分为两类：

1. **数学计算法**：通过计算水龙头之间的距离，直接推导出每个花坛被浇水的时间。这种方法时间复杂度较低，通常为 $O(k)$，适合大规模数据。
2. **搜索算法**：使用 BFS 或 DFS 模拟水流的扩散过程，记录每个花坛被浇水的时间。这种方法直观但时间复杂度较高，通常为 $O(n \times k)$，适合小规模数据。

#### 最优思路与技巧

- **数学计算法**：通过计算水龙头之间的距离，推导出每个花坛被浇水的时间。具体来说，对于相邻的两个水龙头，它们之间的花坛被浇水的时间为它们距离的一半加 1。对于最左和最右的水龙头，它们分别需要覆盖到花园的左端和右端。
- **BFS 算法**：将每个水龙头的位置入队，然后逐层扩展，记录每个花坛被浇水的时间。这种方法虽然直观，但时间复杂度较高。

#### 推荐题解

1. **作者：nenugdi (赞：9)**
   - **星级**：★★★★★
   - **关键亮点**：通过数学计算直接得出结果，时间复杂度低，代码简洁。
   - **核心代码**：
     ```cpp
     int main() {
         int i,j,t,n,k,x,pre,maxn;
         cin>>t;
         while(t--) {
             cin>>n>>k;
             cin>>pre;
             maxn=pre;
             for(i=2;i<=k;i++) {
                 cin>>x;
                 maxn=max(maxn,(x-pre)/2+1);
                 pre=x;
             }
             maxn=max(maxn,n-pre+1);
             cout<<maxn<<endl;
         }
         return 0;
     }
     ```

2. **作者：Great_Influence (赞：2)**
   - **星级**：★★★★
   - **关键亮点**：代码简洁，直接通过公式计算得出结果，适合快速解题。
   - **核心代码**：
     ```cpp
     inline void solve() {
         static int ans;ans=max(p[1],n-p[k]+1);
         Rep(i,1,k-1)Chkmax(ans,(p[i+1]-p[i])/2+1);
         printf("%d\n",ans);
     }
     ```

3. **作者：2132B (赞：3)**
   - **星级**：★★★★
   - **关键亮点**：通过数学计算直接得出结果，代码简洁，适合快速解题。
   - **核心代码**：
     ```cpp
     int main() {
         cin >> m;
         while (m--) {
             cin >> n >> k >> x[1];
             maxx = x[1];
             for (int i = 2;i <= k;i++) {
                 cin >> x[i];
                 maxx = max(maxx, (x[i] - x[i - 1]) / 2 + 1);
             }
             maxx = max(maxx, n - x[1] + 1);
             cout << maxx << endl;
         }
         return 0;
     }
     ```

#### 可拓展之处

- **类似题目**：可以扩展到多个水龙头同时工作的情况，或者水龙头的覆盖范围不同的问题。
- **算法优化**：对于大规模数据，数学计算法是最优选择；对于小规模数据，BFS 算法直观且易于实现。

#### 推荐题目

1. **P1886 滑动窗口**：考察区间覆盖问题，与本题类似。
2. **P1047 校门外的树**：考察区间覆盖与计算，与本题类似。
3. **P1090 合并果子**：考察贪心算法与区间覆盖，与本题类似。

#### 个人心得

- **调试经历**：在使用 BFS 算法时，容易忘记清空队列或初始化数组，导致错误。
- **顿悟感想**：通过数学计算法可以直接得出结果，避免了复杂的模拟过程，提高了代码效率。

---
处理用时：39.92秒