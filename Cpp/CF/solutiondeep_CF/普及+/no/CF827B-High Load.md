# 题目信息

# High Load

## 题目描述

Arkady needs your help again! This time he decided to build his own high-speed Internet exchange point. It should consist of $ n $ nodes connected with minimum possible number of wires into one network (a wire directly connects two nodes). Exactly $ k $ of the nodes should be exit-nodes, that means that each of them should be connected to exactly one other node of the network, while all other nodes should be connected to at least two nodes in order to increase the system stability.

Arkady wants to make the system as fast as possible, so he wants to minimize the maximum distance between two exit-nodes. The distance between two nodes is the number of wires a package needs to go through between those two nodes.

Help Arkady to find such a way to build the network that the distance between the two most distant exit-nodes is as small as possible.

## 说明/提示

In the first example the only network is shown on the left picture.

In the second example one of optimal networks is shown on the right picture.

Exit-nodes are highlighted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF827B/0a307dfc178cc97ead8d05d1f345ab6df68055f9.png)

## 样例 #1

### 输入

```
3 2
```

### 输出

```
2
1 2
2 3
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
3
1 2
2 3
3 4
3 5
```

# AI分析结果

### 题目内容
# 高负载

## 题目描述
阿尔卡迪再次需要你的帮助！这次他决定建立自己的高速互联网交换点。它应由 $n$ 个节点组成，通过尽可能少的线路连接成一个网络（一条线路直接连接两个节点）。其中恰好 $k$ 个节点应为出口节点，这意味着每个出口节点应恰好连接到网络中的另一个节点，而所有其他节点应至少连接到两个节点，以提高系统稳定性。

阿尔卡迪希望使系统尽可能快，因此他希望最小化两个出口节点之间的最大距离。两个节点之间的距离是一个数据包在这两个节点之间需要经过的线路数量。

帮助阿尔卡迪找到一种构建网络的方法，使得两个距离最远的出口节点之间的距离尽可能小。

## 说明/提示
在第一个示例中，唯一的网络如左图所示。

在第二个示例中，其中一个最优网络如右图所示。

出口节点已突出显示。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF827B/0a307dfc178cc97ead8d05d1f345ab6df68055f9.png)

## 样例 #1
### 输入
```
3 2
```
### 输出
```
2
1 2
2 3
```
## 样例 #2
### 输入
```
5 3
```
### 输出
```
3
1 2
2 3
3 4
3 5
```
### 算法分类
构造
### 综合分析与结论
这三道题解均围绕如何构造满足条件的网络展开。
- **流绪题解**：思路是找到一个中心节点，让它与 $k$ 个出口节点相连，再根据剩余节点数量进行扩展。通过计算 $(n - 1) / k$ 得到扩展层数，再乘以 2 得到两个出口节点间的距离，并通过特判处理余数情况。算法要点在于利用除法和余数来确定距离及输出边的方式。难点在于理解如何通过中心节点扩展以及对余数情况的准确处理。
- **wmrqwq题解**：以 $1$ 为根，先将 $k$ 个深度为 $1$ 的节点连接，再用优先队列维护将剩余节点挂在叶子节点上。时间复杂度为 $O(n \log n)$。算法要点在于优先队列的使用。难点在于对优先队列维护逻辑的理解。
- **Crosser题解**：将题意转化为对一个有 $k$ 个叶子节点的树，最小化深度最大的两叶子的深度和。先构建 $k$ 叉菊花图，再往每个分支均匀挂点。算法要点在于构建菊花图并均匀分配节点。难点在于证明该构造方式为最优解。

三道题解中，流绪和Crosser的题解思路较为清晰简洁，代码可读性也较好。wmrqwq题解使用优先队列，增加了理解难度且代码较为繁杂。
### 所选的题解
- **流绪题解**：★★★★
  - **关键亮点**：思路清晰，通过简单的数学计算和特判来确定距离和输出边，代码简洁明了。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,k;
    cin >> n >> k;
    int ans = (n - 1) / k * 2;
    if((n - 1) % k == 1)
        ans++;
    else if((n - 1) % k)
        ans += 2;
    cout << ans << endl;
    for(int i = 2; i <= k; i++)
        cout << "1 " << i << endl;
    for(int i = k + 1; i <= n; i++)
        cout << i << " " << i - k << endl;
}
```
  - **核心实现思想**：先计算出基本距离，再根据余数情况调整距离。输出边时，先输出中心节点与出口节点的连接，再输出其他节点与前一层对应节点的连接。
- **Crosser题解**：★★★★
  - **关键亮点**：将题意巧妙转化为树的深度和问题，通过构建菊花图并均匀挂点的方式解决，逻辑清晰。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k;
signed main() {
    cin >> n >> k;
    vector<pair<int, int>> v;
    vector<int> res(k);
    for(int i = 2; i <= k + 1; i++) v.emplace_back(1, i), res[i - 2]++;
    for(int i = k + 2; i <= n; i++) res[i % k]++, v.emplace_back(i - k, i);
    sort(res.begin(), res.end(), greater<int>());
    cout << res[0] + res[1] << endl;
    for(auto x : v) cout << x.first << ' ' << x.second << endl;
    system("pause");
    return 0;
}
```
  - **核心实现思想**：先构建菊花图，记录每个分支的节点数，再将剩余节点均匀分配到各分支，最后通过排序取最大的两个深度之和作为答案，并输出边的连接情况。
### 最优关键思路或技巧
- **构造思路**：通过构建特定的图结构（如以一个节点为中心连接出口节点，或构建菊花图）来满足题目条件，同时考虑如何均匀分配节点以达到最小化出口节点间最大距离的目的。
- **数学计算与特判**：利用简单的除法和余数运算来计算距离，并通过特判处理余数不同情况对距离的影响。
### 拓展
此类题目属于图的构造类型，通常需要根据题目给定的节点连接条件和优化目标来设计图结构。类似套路包括根据节点度数、距离等限制条件构建树或图。
### 推荐题目
- [P1317 低洼地](https://www.luogu.com.cn/problem/P1317)
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)

---
处理用时：44.81秒