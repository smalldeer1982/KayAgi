# 题目信息

# [ABC354G] Select Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc354/tasks/abc354_g

$ N $ 個の英小文字からなる文字列 $ S_1,S_2,\ldots,S_N $ と $ N $ 個の正整数 $ A_1,A_2,\ldots,A_N $ があります。

ある $ \lbrace\ 1,2,\ldots,N\ \rbrace $ の部分集合 $ T $ は $ i,j\ \in\ T\ (i\ \neq\ j) $ で $ S_i $ が $ S_j $ の部分文字列となるような $ i,j $ の組がないとき**良い集合**であるといいます。

良い集合 $ T $ を選んだ時 $ \displaystyle\ \sum_{i\ \in\ T}\ A_i $ としてありえる値の最大値を求めてください。

 部分文字列とは？ $ S $ の**部分文字列**とは、$ S $ の先頭から $ 0 $ 文字以上、末尾から $ 0 $ 文字以上削除して得られる文字列のことをいいます。 例えば、`ab` は `abc` の部分文字列ですが、`ac` は `abc` の部分文字列ではありません。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ S_i $ は英小文字からなる文字列である
- $ 1\ \leq\ |S_i| $
- $ |S_1|+|S_2|\ +\ \ldots\ +\ |S_N|\ \leq\ 5000 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
 
### Sample Explanation 1

良い集合 としてありえる $ T $ とそれぞれに対する $ \displaystyle\ \sum_{i\ \in\ T}\ A_i $ は以下の通りです。 - $ T\ =\ \lbrace\ 1\ \rbrace $ のとき $ \displaystyle\ \sum_{i\ \in\ T}\ A_i\ =\ 5 $ - $ T\ =\ \lbrace\ 2\ \rbrace $ のとき $ \displaystyle\ \sum_{i\ \in\ T}\ A_i\ =\ 2 $ - $ T\ =\ \lbrace\ 3\ \rbrace $ のとき $ \displaystyle\ \sum_{i\ \in\ T}\ A_i\ =\ 3 $ - $ T\ =\ \lbrace\ 4\ \rbrace $ のとき $ \displaystyle\ \sum_{i\ \in\ T}\ A_i\ =\ 4 $ - $ T\ =\ \lbrace\ 2,3\ \rbrace $ のとき $ \displaystyle\ \sum_{i\ \in\ T}\ A_i\ =\ 5 $ - $ T\ =\ \lbrace\ 2,4\ \rbrace $ のとき $ \displaystyle\ \sum_{i\ \in\ T}\ A_i\ =\ 6 $ このうち最大値は $ 6 $ なので、$ 6 $ を出力します。

## 样例 #1

### 输入

```
4

atcoder

at

coder

code

5 2 3 4```

### 输出

```
6```

## 样例 #2

### 输入

```
10

abcd

abc

ab

a

b

c

d

ab

bc

cd

100 10 50 30 60 90 80 70 40 20```

### 输出

```
260```

# AI分析结果



**唯一算法分类**  
组合数学

---

**综合分析与结论**  
题目要求选出互不包含的字符串集合，最大化权重和。核心思路是将问题建模为DAG最大权反链问题，应用Dilworth定理转化为网络流最小割模型。关键步骤如下：

1. **包含关系建图**：预处理所有字符串的包含关系，构建有向边（若S_i是S_j子串则i→j）。
2. **处理重复字符串**：合并相同字符串，仅保留最大权重。
3. **网络流建模**：拆点构造二分图，源点连左部（容量a_i），右部连汇点（容量a_i），包含关系连无穷边。
4. **最大流计算**：总权重减去最小割即为答案。

**可视化设计**：  
- **像素动画**：每个字符串显示为像素块，包含关系用箭头连接，拆点后源/汇点以不同颜色高亮。  
- **流动效果**：红色高亮被割边，绿色显示选中节点。  
- **音效提示**：割边时播放“切割”音效，选中节点时播放“收集”音效。

---

**题解清单 (≥4星)**  
1. **王华 (5星)**：严谨应用Dilworth定理，正确处理传递闭包与拆点网络流。  
2. **ケロシ (5星)**：代码简洁，合并重复字符串并明确处理偏序关系。  
3. **Linge_Zzzz (4星)**：清晰分步实现网络流模型，注释详细。

---

**最优思路提炼**  
- **数学核心**：DAG最大权反链 → 最小割模型（总权 - 最大流）。  
- **优化技巧**：预处理字符串去重，KMP快速判断子串关系。  
- **实现关键**：拆点建图时，用无穷边阻断矛盾关系，确保割边对应合法解。

---

**同类型题套路**  
- **通用模型**：互斥选择问题 → 网络流最小割。  
- **常见扩展**：DAG最长反链、最小路径覆盖均可用类似网络流方法。

**推荐题目**  
1. [洛谷 P4298](https://www.luogu.com.cn/problem/P4298)（DAG最长反链）  
2. [洛谷 P2764](https://www.luogu.com.cn/problem/P2764)（最小路径覆盖）  
3. [洛谷 P4177](https://www.luogu.com.cn/problem/P4177)（权值取舍网络流）

---

**个人心得摘录**  
- **预处理陷阱**：未合并重复字符串会WA，需优先取最大权。  
- **传递性优化**：若i→j且j→k，可不显式建i→k边，因网络流自动传递阻断。  

---

**代码片段 (ケロシ题解核心)**  
```cpp
// 预处理去重并建图
map<string, int> vis;
for(int i=1; i<=n; i++){
    if(!vis.count(s[i])) vis[s[i]] = a[i];
    else vis[s[i]] = max(vis[s[i]], a[i]);
}
// 网络流建边
for(int i=1; i<=n; i++){
    add_edge(S, i, a[i]);       // 源点→左部
    add_edge(i+n, T, a[i]);     // 右部→汇点
    for(int j=1; j<=n; j++){
        if(s[i].find(s[j]) != string::npos)
            add_edge(i, j+n, INF); // 矛盾关系
    }
}
// 计算答案
cout << total_sum - max_flow() << endl;
```

---

**可视化实现要点**  
```javascript
// 伪代码：Canvas绘制网络流模型
function drawGraph() {
    ctx.fillStyle = '#8B00FF'; // 像素紫
    nodes.forEach(node => {
        drawPixelBlock(node.x, node.y); // 左部节点
        drawPixelBlock(node.x + 20, node.y); // 右部节点
    });
    edges.forEach(edge => {
        if(edge.cap === INF) ctx.strokeStyle = '#FF4500'; // 无穷边
        drawArrow(edge.from, edge.to); 
    });
    // 播放音效
    if(cutEdge) playSound('cut.mp3');
}
```

---
处理用时：87.78秒