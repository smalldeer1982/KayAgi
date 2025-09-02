# 题目信息

# Bear and Friendship Condition

## 题目描述

Bear Limak examines a social network. Its main functionality is that two members can become friends (then they can talk with each other and share funny pictures).

There are $ n $ members, numbered $ 1 $ through $ n $ . $ m $ pairs of members are friends. Of course, a member can't be a friend with themselves.

Let A-B denote that members A and B are friends. Limak thinks that a network is reasonable if and only if the following condition is satisfied: For every three distinct members (X, Y, Z), if X-Y and Y-Z then also X-Z.

For example: if Alan and Bob are friends, and Bob and Ciri are friends, then Alan and Ciri should be friends as well.

Can you help Limak and check if the network is reasonable? Print "YES" or "NO" accordingly, without the quotes.

## 说明/提示

The drawings below show the situation in the first sample (on the left) and in the second sample (on the right). Each edge represents two members that are friends. The answer is "NO" in the second sample because members $ (2,3) $ are friends and members $ (3,4) $ are friends, while members $ (2,4) $ are not.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF771A/452e04bb457330535035b94604ffb28f5fa05d56.png)

## 样例 #1

### 输入

```
4 3
1 3
3 4
1 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 4
3 1
2 3
3 4
1 2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
10 4
4 3
5 10
8 9
1 2
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
3 2
1 2
2 3
```

### 输出

```
NO
```

# AI分析结果



# Bear and Friendship Condition

## 题目描述

Bear Limak 正在研究一个社交网络。其主要功能是两个成员可以成为朋友（之后他们可以互相聊天并分享有趣的图片）。

共有 $n$ 个成员，编号为 $1$ 到 $n$。给定 $m$ 对朋友关系。Limak 认为网络是合理的当且仅当以下条件满足：对于任意三个不同的成员 (X, Y, Z)，如果 X-Y 和 Y-Z 是朋友，则 X-Z 也必须是朋友。

请判断该网络是否合理，输出 "YES" 或 "NO"。

## 样例

输入样例 1：  
4 3  
1 3  
3 4  
1 4  
输出：YES  

输入样例 2：  
4 4  
3 1  
2 3  
3 4  
1 2  
输出：NO  

## 算法分类
**并查集**

---

## 题解分析与结论

题目核心要求等价于所有连通块必须为完全图。判断方法为：每个连通块的边数需满足 $m_i = \frac{n_i(n_i-1)}{2}$，总边数等于各连通块理论边数之和。

### 关键思路
1. **并查集统计连通块**：通过并查集快速合并节点并记录每个连通块的大小。
2. **完全图验证**：计算所有连通块的理论边数总和，若等于实际边数 $m$，则网络合理。

---

## 高分题解推荐

### 题解作者：xxzjbd（⭐⭐⭐⭐⭐）
**关键亮点**：
- 使用并查集维护连通块大小。
- 通过理论边数总和直接对比 $m$，思路简洁高效。
- 代码可读性强，时间复杂度 $O(nα(n))$。

**核心代码**：
```cpp
#include<cstdio>
#define int long long
using namespace std;
int fa[150010],num[150010];
int sum;

int fi(int x) { // 路径压缩
    return fa[x] == x ? x : fa[x] = fi(fa[x]);
}

void add(int x, int y) { // 合并操作
    int xx = fi(x), yy = fi(y);
    if (xx != yy) {
        fa[yy] = xx;
        num[xx] += num[yy]; // 累加连通块大小
    }
}

signed main() {
    int n, m;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        num[i] = 1;
    }
    while (m--) {
        int x, y;
        scanf("%lld%lld", &x, &y);
        add(x, y);
    }
    for (int i = 1; i <= n; i++) {
        if (fi(i) == i) // 根节点计算理论边数
            sum += num[i] * (num[i] - 1) / 2;
    }
    puts(sum == m ? "YES" : "NO");
}
```

### 题解作者：E1_de5truct0r（⭐⭐⭐⭐⭐）
**关键亮点**：
- 并查集实现与理论证明结合，逻辑严谨。
- 代码结构清晰，注释明确。

**核心代码**：
```cpp
int fa[150005];
long long tot[150005]; // 记录连通块大小

int find(int x) { 
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main() {
    // 初始化并查集
    for (int i = 1; i <= n; i++) 
        fa[i] = i, tot[i] = 1;

    // 合并操作
    while (m--) {
        int x, y;
        fa[fx] = fy;
        tot[fy] += tot[fx];
    }

    // 计算理论边数总和
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (find(i) == i)
            ans += tot[i] * (tot[i] - 1) / 2;

    puts(ans == m ? "YES" : "NO");
}
```

---

## 关键技巧总结
1. **连通块完全图性质**：将问题转化为完全图的边数验证。
2. **并查集优化**：高效维护连通块大小，避免重复计算。
3. **数学公式应用**：利用 $n(n-1)/2$ 快速判断完全图。

---

## 同类题目推荐
1. [P1111 修复公路](https://www.luogu.com.cn/problem/P1111) - 并查集判断连通性
2. [P2872 道路建设](https://www.luogu.com.cn/problem/P2872) - 最小生成树与连通性
3. [P3916 图的遍历](https://www.luogu.com.cn/problem/P3916) - 反向图遍历技巧

---
处理用时：113.57秒