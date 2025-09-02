# 题目信息

# Circular Spanning Tree

## 题目描述

There are $ n $ nodes arranged in a circle numbered from $ 1 $ to $ n $ in the clockwise order. You are also given a binary string $ s $ of length $ n $ .

Your task is to construct a tree on the given $ n $ nodes satisfying the two conditions below or report that there such tree does not exist:

- For each node $ i $ $ (1 \le i \le n) $ , the degree of node is even if $ s_i = 0 $ and odd if $ s_i = 1 $ .
- No two edges of the tree intersect internally in the circle. The edges are allowed to intersect on the circumference.

Note that all edges are drawn as straight line segments. For example, edge $ (u, v) $ in the tree is drawn as a line segment connecting $ u $ and $ v $ on the circle.

A tree on $ n $ nodes is a connected graph with $ n - 1 $ edges.

## 说明/提示

In the first test case, the tree looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682D/a3c1924547a7a2cf2e2e161bdb11c580efe3e855.png)In the second test case, there is only one possible tree with an edge between $ 1 $ and $ 2 $ , and it does not satisfy the degree constraints.

In the third test case,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682D/e5b3e28053fdc3d6ed84005d3e46d8276c4f8576.png) The tree on the left satisfies the degree constraints but the edges intersect internally, therefore it is not a valid tree, while the tree on the right is valid.

## 样例 #1

### 输入

```
3
4
0110
2
10
6
110110```

### 输出

```
YES
2 1
3 4
1 4
NO
YES
2 3
1 2
5 6
6 2
3 4```

# AI分析结果

### 题目中文重写
#### 环形生成树

#### 题目描述
有 $n$ 个节点按顺时针顺序排列成一个圆圈，编号从 $1$ 到 $n$。同时还给定一个长度为 $n$ 的二进制字符串 $s$。

你的任务是在给定的 $n$ 个节点上构造一棵树，使其满足以下两个条件，若不存在这样的树则报告：
- 对于每个节点 $i$（$1 \leq i \leq n$），若 $s_i = 0$，则节点的度数为偶数；若 $s_i = 1$，则节点的度数为奇数。
- 树的任意两条边在圆内不相交，边可以在圆周上相交。

请注意，所有边都画成直线段。例如，树中的边 $(u, v)$ 画成连接圆上 $u$ 和 $v$ 的线段。

$n$ 个节点的树是一个有 $n - 1$ 条边的连通图。

#### 说明/提示
在第一个测试用例中，树的样子如下：
![示例图1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682D/a3c1924547a7a2cf2e2e161bdb11c580efe3e855.png)
在第二个测试用例中，只有一种可能的树，即节点 $1$ 和 $2$ 之间有一条边，但它不满足度数约束。
在第三个测试用例中，
![示例图2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682D/e5b3e28053fdc3d6ed84005d3e46d8276c4f8576.png)
左边的树满足度数约束，但边在圆内相交，因此它不是有效的树，而右边的树是有效的。

#### 样例 #1
##### 输入
```
3
4
0110
2
10
6
110110
```
##### 输出
```
YES
2 1
3 4
1 4
NO
YES
2 3
1 2
5 6
6 2
3 4
```

### 综合分析与结论
#### 思路对比
- **无解判断**：各题解均指出当字符串 $s$ 中 `1` 的个数为奇数或没有 `1` 时无解，依据是树的总度数为偶数且树至少有一个叶子节点（度数为 1）。
- **有解构造**：
    - 部分题解（如 KiloP、D2T1）根据节点度数的奇偶性分情况构造，若所有节点度数为奇数则构造菊花图，否则选偶数度节点为根构造链。
    - 部分题解（如 zjqzjq）先按顺时针连边使部分节点符合要求，再将不符合要求的节点与一个固定节点相连。
    - 部分题解（如 DaiRuiChen007）先构造链，再通过调整边来改变节点度数奇偶性。

#### 算法要点
- **无解判断**：统计字符串 $s$ 中 `1` 的个数，判断其奇偶性和是否为 0。
- **有解构造**：
    - 菊花图构造：任选一个节点为根，将其他节点与根相连。
    - 链构造：将序列拆分成若干子序列，每个子序列连成链，再将链的一端与根节点相连。

#### 解决难点
- **边不相交**：通过合理的构造方式保证边不相交，如将边分为从根连出的边和圆上相邻点的边，或让边贴着圆周连接。
- **度数满足要求**：通过分情况讨论和调整边的连接方式，使每个节点的度数满足字符串 $s$ 的要求。

### 所选题解
- **KiloP（5星）**
    - **关键亮点**：思路清晰，分情况讨论详细，对构造过程和边不相交的说明很清晰，代码实现简洁。
    - **核心代码**：
```cpp
if (_1 % 2!= 0 || _1 == 0) {
    puts("NO");
    continue;
}
puts("YES");
if (_0 == 0) {
    for (int i = 2; i <= n; ++i) cout << "1 " << i << endl;
} else {
    int idx = 0;
    for (int i = 1; i <= n; ++i) if (s[i] == '0' && s[(i + n - 2) % n + 1] == '1') { idx = i; break; }
    int now = idx % n + 1;
    while (now!= idx) {
        cout << idx << ' ' << now << endl;
        while(s[now]!= '1') {
            cout << now << ' ' << now % n + 1 << endl;
            now = now % n + 1;
        }
        now = now % n + 1;
    }
}
```
核心实现思想：先判断无解情况，若所有节点度数为奇数则构造菊花图，否则选一个偶数度节点为根，将序列拆分成若干子序列，每个子序列连成链，再将链的一端与根节点相连。
- **D2T1（4星）**
    - **关键亮点**：思路清晰，配有图示，代码实现规范。
    - **核心代码**：
```cpp
if(cnt == 0 || cnt & 1){
    puts("NO");
    continue;
}
puts("YES");
if(cnt == n){
    for(int i = 2; i <= n; ++ i){
        printf("1 %d\n", i);
    }
    continue;
}
int st = 0;
if(s[n] == '1' && s[1] == '0'){
    st = 1;
} else {
    for(int i = 1; i <= n; ++ i){
        if(!st && s[i] == '0' && s[i-1] == '1'){
            st = i;
        }
    }
}
#define pre(i) (i==1? n : i-1)
#define nxt(i) (i==n? 1 : i+1)
bool flg = true;
for(int i = st+1; flg || i < st; ++ i){
    if(i == n+1){
        i = 1;
        if(st == 1) break;
        flg = false;
    }
    if(pre(i) == st || s[pre(i)] == '1'){
        printf("%d %d\n", i, st);
    }
    if(s[i] == '0'){
        printf("%d %d\n", i, nxt(i));
    }
}
```
核心实现思想：先判断无解情况，若所有节点度数为奇数则构造菊花图，否则选一个位于子序列首的偶数度节点为根，将每个子序列连成链，再将链的第一个元素与根节点相连。
- **zjqzjq（4星）**
    - **关键亮点**：思路简洁，代码实现简单易懂。
    - **核心代码**：
```cpp
if(flag || cnt==0){//无解情况
    cout<<"NO\n";
    return;
}
cout<<"YES\n";
c[n+1]=c[1];
for(int i=1;i<=n;i++){
    if(c[i+1]==0){
        cout<<i<<" "<<i%n+1<<"\n";//第一步
    }
    if(c[i+1]){
        a[++len]=i;//统计第一步不合法的点
    }
}
for(int i=2;i<=len;i++){//第二步
    cout<<a[1]<<" "<<a[i]<<"\n";
}
```
核心实现思想：先判断无解情况，然后按顺时针连边使部分节点符合要求，统计不符合要求的节点，最后将这些节点与一个固定节点相连。

### 最优关键思路或技巧
- **分情况讨论**：根据节点度数的奇偶性分情况构造树，简化了构造过程。
- **合理选择根节点**：选择合适的根节点可以方便地构造出满足条件的树。
- **利用树的性质**：利用树的总度数为偶数和至少有一个叶子节点的性质，快速判断无解情况。

### 可拓展之处
同类型题可能会改变节点的排列方式（如线性排列）或增加其他约束条件（如边的权值限制），解题思路可以借鉴本题的分情况讨论和构造方法。

### 推荐题目
- [P1197 星球大战](https://www.luogu.com.cn/problem/P1197)：涉及图的连通性和树的构造。
- [P2820 局域网](https://www.luogu.com.cn/problem/P2820)：最小生成树问题，与本题的树构造有一定关联。
- [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)：经典的最小生成树问题，可加深对树的理解。

### 个人心得摘录与总结
无。

---
处理用时：47.73秒