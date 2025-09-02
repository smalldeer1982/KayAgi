# 题目信息

# Destroying Bridges

## 题目描述

There are $ n $ islands, numbered $ 1, 2, \ldots, n $ . Initially, every pair of islands is connected by a bridge. Hence, there are a total of $ \frac{n (n - 1)}{2} $ bridges.

Everule lives on island $ 1 $ and enjoys visiting the other islands using bridges. Dominater has the power to destroy at most $ k $ bridges to minimize the number of islands that Everule can reach using (possibly multiple) bridges.

Find the minimum number of islands (including island $ 1 $ ) that Everule can visit if Dominater destroys bridges optimally.

## 说明/提示

In the first test case, since no bridges can be destroyed, all the islands will be reachable.

In the second test case, you can destroy the bridge between islands $ 1 $ and $ 2 $ . Everule will not be able to visit island $ 2 $ but can still visit island $ 1 $ . Therefore, the total number of islands that Everule can visit is $ 1 $ .

In the third test case, Everule always has a way of reaching all islands despite what Dominater does. For example, if Dominater destroyed the bridge between islands $ 1 $ and $ 2 $ , Everule can still visit island $ 2 $ by traveling by $ 1 \to 3 \to 2 $ as the bridges between $ 1 $ and $ 3 $ , and between $ 3 $ and $ 2 $ are not destroyed.

In the fourth test case, you can destroy all bridges since $ k = \frac{n \cdot (n - 1)}{2} $ . Everule will be only able to visit $ 1 $ island (island $ 1 $ ).

## 样例 #1

### 输入

```
6
2 0
2 1
4 1
5 10
5 3
4 4```

### 输出

```
2
1
4
1
5
1```

# AI分析结果

### 题目中文重写
# 摧毁桥梁

## 题目描述
有 $n$ 个岛屿，编号为 $1, 2, \ldots, n$。最初，每对岛屿之间都有一座桥相连。因此，总共有 $\frac{n (n - 1)}{2}$ 座桥。

埃弗鲁尔住在 1 号岛屿，喜欢通过桥梁去参观其他岛屿。多米纳特有权最多摧毁 $k$ 座桥，以最小化埃弗鲁尔通过（可能是多座）桥梁能够到达的岛屿数量。

如果多米纳特以最优方式摧毁桥梁，求埃弗鲁尔能够参观的最少岛屿数量（包括 1 号岛屿）。

## 说明/提示
在第一个测试用例中，由于不能摧毁任何桥梁，所有岛屿都可以到达。

在第二个测试用例中，你可以摧毁 1 号和 2 号岛屿之间的桥梁。埃弗鲁尔将无法参观 2 号岛屿，但仍可以参观 1 号岛屿。因此，埃弗鲁尔能够参观的岛屿总数为 1。

在第三个测试用例中，无论多米纳特怎么做，埃弗鲁尔总有办法到达所有岛屿。例如，如果多米纳特摧毁了 1 号和 2 号岛屿之间的桥梁，埃弗鲁尔仍然可以通过 $1 \to 3 \to 2$ 路线参观 2 号岛屿，因为 1 号和 3 号、3 号和 2 号岛屿之间的桥梁没有被摧毁。

在第四个测试用例中，由于 $k = \frac{n \cdot (n - 1)}{2}$，你可以摧毁所有桥梁。埃弗鲁尔将只能参观 1 个岛屿（1 号岛屿）。

## 样例 #1
### 输入
```
6
2 0
2 1
4 1
5 10
5 3
4 4
```
### 输出
```
2
1
4
1
5
1
```

### 综合分析与结论
- **思路对比**：各题解思路高度一致，均通过比较 $k$ 与 $n - 1$ 的大小来确定答案。当 $k \geq n - 1$ 时，将 1 号岛与其他岛分离，答案为 1；当 $k < n - 1$ 时，所有岛都可达，答案为 $n$。
- **算法要点**：核心在于分析出要使 1 号岛与其他岛分离需破坏 $n - 1$ 条边，进而根据 $k$ 的大小分类讨论。
- **解决难点**：关键难点在于理解图的连通性以及破坏边对连通性的影响，各题解均清晰地解决了这一难点。

### 评分情况
- zcr0202：4 星。思路清晰，代码简洁规范，有基本的输入输出优化。
- luobotianle：4 星。思路明确，代码简洁易懂。
- Guizy：4 星。不仅给出规律，还进行了证明，代码简洁。

### 所选题解
- **zcr0202（4 星）**：
    - **关键亮点**：思路清晰，代码有输入输出优化，提升效率。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, ans;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin >> T;
    while(T--) {
        cin >> n >> k;
        if(k >= n - 1) {
            cout << "1\n";
        }
        else {
            cout << n << '\n';
        }
    }
}
```
核心实现思想：通过比较 $k$ 和 $n - 1$ 的大小，输出对应的结果。
- **luobotianle（4 星）**：
    - **关键亮点**：思路简洁明了，代码简单直接。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int main(){
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(k>=n-1)cout<<1;
        else cout<<n;
        cout<<"\n";
    }
    return 0;
}
```
核心实现思想：同样比较 $k$ 和 $n - 1$ 的大小，输出结果。
- **Guizy（4 星）**：
    - **关键亮点**：给出规律并进行证明，代码简洁。
    - **核心代码**：
```cpp
cin>>n>>k;
cout<<(k>=n-1?1:n)<<"\n";
```
核心实现思想：使用三目运算符根据 $k$ 和 $n - 1$ 的大小输出结果。

### 最优关键思路或技巧
通过分析图的连通性，确定破坏边的数量与岛屿可达性的关系，进而进行分类讨论，简化问题求解。

### 拓展思路
同类型题可能涉及不同的图结构，如稀疏图、有向图等，解题关键仍在于分析图的连通性和边的破坏对其的影响。类似算法套路包括判断图的连通分量、最小割等。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：涉及图的拓扑排序和连通性问题。
- [P1341 无序字母对](https://www.luogu.com.cn/problem/P1341)：与图的欧拉路径相关，需分析图的连通性。
- [P2746 [USACO5.3]校园网Network of Schools](https://www.luogu.com.cn/problem/P2746)：考察图的强连通分量和缩点操作。

### 个人心得摘录与总结
- keep_shining：作者表示自我感觉讲解详细，未加注释。总结：强调了思路的清晰表达，认为自己已将解题思路阐述清楚。 

---
处理用时：30.99秒