# 题目信息

# Similar Arrays

## 题目描述

Vasya had an array of $ n $ integers, each element of the array was from $ 1 $ to $ n $ . He chose $ m $ pairs of different positions and wrote them down to a sheet of paper. Then Vasya compared the elements at these positions, and wrote down the results of the comparisons to another sheet of paper. For each pair he wrote either "greater", "less", or "equal".

After several years, he has found the first sheet of paper, but he couldn't find the second one. Also he doesn't remember the array he had. In particular, he doesn't remember if the array had equal elements. He has told this sad story to his informatics teacher Dr Helen.

She told him that it could be the case that even if Vasya finds his second sheet, he would still not be able to find out whether the array had two equal elements.

Now Vasya wants to find two arrays of integers, each of length $ n $ . All elements of the first array must be distinct, and there must be two equal elements in the second array. For each pair of positions Vasya wrote at the first sheet of paper, the result of the comparison must be the same for the corresponding elements of the first array, and the corresponding elements of the second array.

Help Vasya find two such arrays of length $ n $ , or find out that there are no such arrays for his sets of pairs.

## 样例 #1

### 输入

```
1 0
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3 1
1 2
```

### 输出

```
YES
1 3 2 
1 3 1 
```

## 样例 #3

### 输入

```
4 3
1 2
1 3
2 4
```

### 输出

```
YES
1 3 4 2 
1 3 4 1 
```

# AI分析结果

### 题目内容
# 相似数组

## 题目描述
瓦夏有一个包含 \( n \) 个整数的数组，数组中的每个元素取值范围是从 \( 1 \) 到 \( n \) 。他选择了 \( m \) 对不同的位置，并将它们记录在一张纸上。然后，瓦夏比较了这些位置上的元素，并将比较结果记录在另一张纸上。对于每一对位置，他记录了“大于”“小于”或“等于”。

几年后，他找到了第一张纸，但找不到第二张纸了。而且，他也不记得原来的数组是什么样的了。特别是，他不记得数组中是否有相等的元素。他把这个悲伤的故事告诉了他的信息学老师海伦博士。

海伦博士告诉他，即使他找到了第二张纸，也有可能仍然无法确定数组中是否有两个相等的元素。

现在，瓦夏想找到两个长度为 \( n \) 的整数数组。第一个数组的所有元素必须是不同的，而第二个数组必须有两个相等的元素。对于瓦夏在第一张纸上记录的每一对位置，第一个数组和第二个数组中对应位置元素的比较结果必须相同。

帮助瓦夏找到这样的两个长度为 \( n \) 的数组，或者确定对于他所记录的这些位置对，不存在这样的数组。

## 样例 #1
### 输入
```
1 0
```
### 输出
```
NO
```

## 样例 #2
### 输入
```
3 1
1 2
```
### 输出
```
YES
1 3 2 
1 3 1 
```

## 样例 #3
### 输入
```
4 3
1 2
1 3
2 4
```
### 输出
```
YES
1 3 4 2 
1 3 4 1 
```

### 算法分类
构造

### 综合分析与结论
两题解均围绕构造满足条件的两个数组展开。
 - **思路方面**：rui_er题解从整体情况出发，依据 \( m \) 与 \( \frac{n(n - 1)}{2} \) 的关系判断是否有解，有解时构造两个几乎完全相等的数组；Ryder00题解将输入约束关系建图，通过对边定向、贪心选点赋值及按度数从小到大对剩余点赋值来构造数组。
 - **算法要点**：rui_er题解重点在于找到无偏序关系的下标对，利用其构造数组；Ryder00题解关键在于将问题转化为图论问题，借助贪心和类似拓扑排序的方式解决。
 - **解决难点**：两题解都需处理如何在满足给定位置对比较关系的前提下，构造出符合要求的两个数组。rui_er题解通过特殊情况判断和特定位置赋值解决；Ryder00题解通过图的构建、点的选择和度数相关的赋值策略解决。

### 所选的题解
 - **rui_er题解**：
   - **星级**：4星
   - **关键亮点**：思路简洁清晰，通过简单数学关系判断无解情况，构造方式巧妙，代码实现简洁明了。
   - **核心代码片段**：
```cpp
int main() {
    scanf("%d%d", &n, &m);
    rep(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    if(m == n * (n - 1) / 2) return puts("NO")&0;
    int pa = -1, pb = -1, now = 0;
    rep(i, 1, n) {
        if((int)e[i].size() == n - 1) continue;
        for(int j : e[i]) vis[j] = 1;
        rep(j, 1, n) if(i!= j &&!vis[j]) {pa = i; pb = j; break;}
        break;
    }
    rep(i, 1, n) if(i!= pa && i!= pb) a[i] = ++now;
    a[pa] = n - 1; a[pb] = n;
    puts("YES");
    rep(i, 1, n) printf("%d%c", a[i], " \n"[i==n]);
    rep(i, 1, n) printf("%d%c", min(a[i], n-1), " \n"[i==n]);
    return 0;
}
```
核心实现思想：先判断 \( m \) 是否等于 \( \frac{n(n - 1)}{2} \) 确定有无解，再找出无偏序关系的下标对，对其余位置顺序赋值，最后按要求输出两个数组。

### 最优关键思路或技巧
利用数学关系快速判断无解情况，以及通过寻找无偏序关系的下标对来构造满足条件的数组，是解决本题的关键技巧。

### 同类型题或类似算法套路拓展
此类构造题通常需根据给定条件，巧妙利用特殊情况或关系，逐步构建符合要求的数据结构。常见套路是先分析极端或特殊情况，再寻找可利用的未约束部分进行构造。

### 洛谷相似知识点题目推荐
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及组合与构造，从给定数字中选取若干个数，构造满足特定条件的组合。
 - [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：通过构造满足价格限制的点菜方案，考察构造思想与简单的动态规划结合。
 - [P1464 Function](https://www.luogu.com.cn/problem/P1464)：需根据函数关系构造出满足条件的函数值，锻炼构造思维和逻辑推理能力。 

---
处理用时：38.78秒