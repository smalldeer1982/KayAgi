# 题目信息

# Rumor

## 题目描述

Vova promised himself that he would never play computer games... But recently Firestorm — a well-known game developing company — published their newest game, World of Farcraft, and it became really popular. Of course, Vova started playing it.

Now he tries to solve a quest. The task is to come to a settlement named Overcity and spread a rumor in it.

Vova knows that there are $ n $ characters in Overcity. Some characters are friends to each other, and they share information they got. Also Vova knows that he can bribe each character so he or she starts spreading the rumor; $ i $ -th character wants $ c_{i} $ gold in exchange for spreading the rumor. When a character hears the rumor, he tells it to all his friends, and they start spreading the rumor to their friends (for free), and so on.

The quest is finished when all $ n $ characters know the rumor. What is the minimum amount of gold Vova needs to spend in order to finish the quest?

Take a look at the notes if you think you haven't understood the problem completely.

## 说明/提示

In the first example the best decision is to bribe the first character (he will spread the rumor to fourth character, and the fourth one will spread it to fifth). Also Vova has to bribe the second and the third characters, so they know the rumor.

In the second example Vova has to bribe everyone.

In the third example the optimal decision is to bribe the first, the third, the fifth, the seventh and the ninth characters.

## 样例 #1

### 输入

```
5 2
2 5 3 4 8
1 4
4 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
10 0
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
55
```

## 样例 #3

### 输入

```
10 5
1 6 2 7 3 8 4 9 5 10
1 2
3 4
5 6
7 8
9 10
```

### 输出

```
15
```

# AI分析结果



# 谣言传播

## 题目描述

Vova 需要在一个有 $n$ 个居民的城镇中传播谣言。每个居民可以被贿赂花费 $c_i$ 金币，贿赂后该居民会将谣言免费传播给所有朋友（朋友的朋友也会传播）。求让所有居民都知晓谣言的最小花费。

## 输入输出样例

### 样例 #1
输入：
5 2
2 5 3 4 8
1 4
4 5
输出：
10

### 样例 #2
输入：
10 0
1 2 3 4 5 6 7 8 9 10
输出：
55

### 样例 #3
输入：
10 5
1 6 2 7 3 8 4 9 5 10
1 2
3 4
5 6
7 8
9 10
输出：
15

**算法分类**：并查集

---

## 题解综合分析

### 核心思路
所有题解均采用并查集处理连通性问题。关键点在于维护每个连通块的最小贿赂值，最终将各连通块的最小值求和。实现差异主要在于维护最小值的方式：
1. **动态更新根节点法**：合并时将较小值节点设为父节点，最终根节点即为最小值
2. **集合最小值维护法**：合并时比较两个集合的最小值，保持祖先节点存储当前集合最小值

### 最优题解亮点

#### 1. Ptilopsis_w（5星）
**关键亮点**：
- 在合并时动态选择较小值节点作为根节点
- 使用标记数组避免重复计算
- 代码简洁高效（时间复杂度 $O(nα(n))$）

核心代码片段：
```cpp
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (a[fx] > a[fy]) f[fx] = fy;  // 较小值作为父节点
    else f[fy] = fx;
}
```

#### 2. EDqwq（4星）
**关键亮点**：
- 合并时显式维护每个集合的最小值
- 使用独立数组存储最小值，逻辑更直观
- 代码结构清晰易读

核心代码片段：
```cpp
void join(int x, int y) {
    int xx = find(x), yy = find(y);
    if (xx != yy) {
        pre[xx] = yy;
        a[yy] = min(a[xx], a[yy]); // 更新集合最小值
    }
}
```

#### 3. 小小蒟弱（4星）
**关键亮点**：
- 在合并时直接修改原数组维护最小值
- 使用辅助数组记录已处理集合
- 包含详细注释和快读实现

核心代码：
```cpp
void Merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        fa[fx] = fy;
        w[fx] = w[fy] = min(w[fx], w[fy]); // 同步更新双亲值
    }
}
```

---

## 关键技巧总结

1. **并查集优化**：路径压缩保证接近常数时间复杂度
2. **极值维护技巧**：通过合并策略或附加存储维护集合属性
3. **标记去重**：使用vis数组避免重复计算根节点值
4. **类型选择**：必须使用long long防止求和溢出

---

## 扩展应用

同类问题套路：
1. 连通分量极值问题（如P1551 亲戚）
2. 动态维护集合属性（如P1197 星球大战）
3. 最小生成树变种（如CF76A Gift）

推荐练习：
1. [P1551 亲戚](https://www.luogu.com.cn/problem/P1551) - 基础并查集应用
2. [P1111 修复公路](https://www.luogu.com.cn/problem/P1111) - 并查集维护连通性
3. [P1197 星球大战](https://www.luogu.com.cn/problem/P1197) - 逆向并查集应用

---

## 题解心得知己

1. **类型强制转换**：多位作者强调必须使用 `long long` 存储结果（"不开long long见祖宗"）
2. **路径压缩优化**：多位题解在find函数中使用路径压缩提升效率
3. **合并策略选择**：部分作者通过调试发现直接比较节点值比维护额外数组更高效
4. **虚拟节点技巧**：有题解通过构造虚拟节点0实现最小生成树转化思路

---
处理用时：51.22秒