# 题目信息

# [USACO1.4] 母亲的牛奶 Mother's Milk

## 题目描述

农民约翰有三个容量分别是 $a,b,c$ 升的桶。  

最初，$a,b$ 桶都是空的，而 $c$ 桶是装满牛奶的。有时，农民把牛奶从一个桶倒到另一个桶中，直到被灌桶装满或原桶空了。  

当然每一次灌注都是完全的。由于节约，牛奶不会有丢失。

写一个程序去帮助农民找出当 $a$ 桶是空的时候，$c$ 桶中牛奶所剩量的所有可能性。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le a,b,c \le 20$。

题目翻译来自NOCOW。

USACO Training Section 1.4


## 样例 #1

### 输入

```
8 9 10
```

### 输出

```
1 2 8 9 10
```

## 样例 #2

### 输入

```
2 5 10```

### 输出

```
5 6 7 8 9 10```

# AI分析结果



### 综合分析与结论
该题核心是穷举所有可能的倒牛奶状态，DFS/BFS是主流解法，难点在于状态判重与倒奶逻辑的正确实现。所有题解均采用暴力搜索，差异主要体现在状态表示、倒奶逻辑简化、代码优化等方面。最优解法应具备清晰的状态转移逻辑和高效判重策略。

---

### 精选题解与亮点分析

#### 1. 远航之曲（★★★★☆）
**核心亮点**：  
- 使用三维数组判重，逻辑清晰  
- 循环处理6种倒法，代码简洁  
- 全局数组复用减少参数传递  

**核心代码**：
```cpp
void dfs(int a[]) {
    if (vis[a[0]][a[1]][a[2]]) return;
    vis[a[0]][a[1]][a[2]] = true;
    if (a[0] == 0) milk[a[2]] = true;
    for (int i = 0; i < 3; ++i) { // 枚举倒出桶
        for (int j = 0; j < 3; ++j) { // 枚举倒入桶
            if (j == i) continue;
            int rec = min(bkt[j] - a[j], a[i]); // 计算可倒量
            int b[3]; memcpy(b, a, sizeof(int)*3);
            b[i] -= rec, b[j] += rec;
            dfs(b);
        }
    }
}
```

#### 2. xun薰（★★★★☆）
**核心亮点**：  
- 使用二维数组判重（利用总牛奶量不变）  
- 对称处理倒奶逻辑，减少冗余代码  
- 显式排序输出结果  

**调试心得**：  
> "一开始没判重导致死循环，后来发现需记录状态防止重复处理"

**核心代码**：
```cpp
void dfs(int nowa,int nowb,int nowc){
    if(vis[nowa][nowb][nowc])return;
    vis[nowa][nowb][nowc]=1;
    if(nowa==0)ans[++k]=nowc;
    // 处理C倒A/B的逻辑
    if(nowc){
        if(nowa<ta) dfs(min(ta,nowa+nowc),nowb,nowc-(min(ta,nowa+nowc)-nowa));
        if(nowb<tb) dfs(nowa,min(tb,nowb+nowc),nowc-(min(tb,nowb+nowc)-nowb));
    }
    // 类似处理其他倒法...
}
```

#### 3. Kewth（★★★★☆）
**核心亮点**：  
- 三目运算符简化倒奶逻辑  
- 分离倒出桶与倒入桶的判断  
- 状态压缩存储优化空间  

**核心代码**：
```cpp
void dfs(int a,int b,int c) {
    if(vis[a][b][c]) return;
    vis[a][b][c] = 1;
    if(a == 0) s[c] = 1;
    // C倒A/B的两种情形
    c>=a-x ? dfs(a-(c-(a-x)),b,a) : dfs(c+x,b,0);
    // 类似处理其他5种倒法...
}
```

---

### 关键思路总结
1. **状态判重**：使用三维数组`vis[a][b][c]`或二维数组`vis[a][b]`（利用c=总牛奶量-a-b）
2. **倒奶逻辑优化**：通过`min(可倒量, 目标桶剩余容量)`计算转移量，避免分支过多
3. **代码简化技巧**：  
   - 双重循环枚举倒出/倒入桶（i→j）  
   - 使用memcpy或结构体传递状态  
   - 预处理总牛奶量减少参数传递

---

### 拓展训练题目
1. [P2744 倒水问题](https://www.luogu.com.cn/problem/P2744) - 同类经典问题  
2. [P1432 倒水问题II](https://www.luogu.com.cn/problem/P1432) - 状态压缩优化  
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443) - BFS路径记录训练

---
处理用时：52.14秒