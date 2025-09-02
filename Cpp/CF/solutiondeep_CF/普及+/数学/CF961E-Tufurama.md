# 题目信息

# Tufurama

## 题目描述

One day Polycarp decided to rewatch his absolute favourite episode of well-known TV series "Tufurama". He was pretty surprised when he got results only for season 7 episode 3 with his search query of "Watch Tufurama season 3 episode 7 online full hd free". This got Polycarp confused — what if he decides to rewatch the entire series someday and won't be able to find the right episodes to watch? Polycarp now wants to count the number of times he will be forced to search for an episode using some different method.

TV series have $ n $ seasons (numbered $ 1 $ through $ n $ ), the $ i $ -th season has $ a_{i} $ episodes (numbered $ 1 $ through $ a_{i} $ ). Polycarp thinks that if for some pair of integers $ x $ and $ y $ ( $ x<y $ ) exist both season $ x $ episode $ y $ and season $ y $ episode $ x $ then one of these search queries will include the wrong results. Help Polycarp to calculate the number of such pairs!

## 说明/提示

Possible pairs in the second example:

1. $ x=1 $ , $ y=2 $ (season 1 episode 2 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 2 episode 1);
2. $ x=2 $ , $ y=3 $ (season 2 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 2);
3. $ x=1 $ , $ y=3 $ (season 1 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 1).

In the third example:

1. $ x=1 $ , $ y=2 $ (season 1 episode 2 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 2 episode 1);
2. $ x=1 $ , $ y=3 $ (season 1 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 1).

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3
8 12 7
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
3 2 1
```

### 输出

```
2
```

# AI分析结果



### 题目重写（中文）

#### Tufurama

**题目描述**  
某天，Polycarp 决定重温他最喜欢的电视剧《Tufurama》的某一集。当他搜索 "在线免费高清观看《Tufurama》第3季第7集" 时，结果却只显示了第7季第3集。这让他想到：若将来要重温整个系列，可能会因搜索错误而找不到正确剧集。现在，Polycarp 想计算有多少次会因这种问题被迫更换搜索方式。

电视剧共有 $n$ 季（编号1到$n$），第 $i$ 季有 $a_i$ 集（编号1到$a_i$）。请帮助 Polycarp 计算满足以下条件的整数对 $(x,y)$ 的数量：  
- $x < y$  
- 存在第 $x$ 季第 $y$ 集  
- 存在第 $y$ 季第 $x$ 集  

**输入输出样例**  
见原题描述，格式保持不变。

---

### 题解综合分析

#### 核心思路与关键技巧
1. **二维数点转化**：将条件 $j \le a_i$ 与 $i \le a_j$ 转化为二维平面上的点统计问题。
2. **离线处理与排序**：按 $i$ 递增顺序处理，动态维护满足 $a_j \ge i$ 的 $j$ 集合。
3. **树状数组优化**：利用树状数组高效维护可用元素集合，支持快速插入、删除和范围查询。
4. **值域裁剪技巧**：将 $a_i > n$ 的值截断为 $n$，避免无效计算。

#### 推荐题解
1. **YellowBean_Elsa（★★★★☆）**  
   **亮点**：树状数组 + 双指针扫描，清晰展示离线处理流程  
   **关键代码**：
   ```cpp
   for(int i=1,now=1;i<=n;i++){
       // 删除i自身及a_j < i的j
       while(now<=n && p[now].a<i){
           if(!out[p[now].x]) add(p[now].x,-1),out[p[now].x]=1;
           ++now;
       }
       ans += query(a[i]); // 查询满足j≤a_i的j数量
   }
   ```

2. **antiquality（★★★★☆）**  
   **亮点**：简洁的树状数组实现，利用排序优化删除操作  
   **个人心得**：提出将 $a_i > n$ 截断的关键优化，避免无效查询。

3. **Tx_Lcy（★★★☆☆）**  
   **亮点**：主席树在线处理，适合动态范围查询  
   **代码核心**：
   ```cpp
   for(int i=2;i<=n;++i){
       int r = min(i-1,a[i]); 
       ans += query(rt[r],1,1e9,i);
   }
   ```

---

### 关键思路总结
1. **离线排序**：将元素按 $a_j$ 排序，配合双指针动态维护有效集合。
2. **树状数组维护**：以下标为维度，支持快速插入/删除和范围查询。
3. **条件分解**：将 $i < j$ 转化为循环顺序，$j \le a_i$ 转为查询范围，$i \le a_j$ 转为预筛选条件。

---

### 拓展与相似题目
1. **二维数点类**  
   - [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)  
   - [P1972 HH的项链](https://www.luogu.com.cn/problem/P1972)（离线+树状数组）
   
2. **树状数组高级应用**  
   - [CF1042D Petya and Array](https://www.luogu.com.cn/problem/CF1042D)（区间和统计）

3. **主席树应用**  
   - [P3834 可持久化线段树2](https://www.luogu.com.cn/problem/P3834)（静态区间第k小）

---

### 关键代码实现（树状数组版）
```cpp
int main() {
    scanf("%d", &n);
    for(int i=1; i<=n; i++) {
        a[i] = min(read(), n); // 关键优化：裁剪超限值
        p[i] = {i, a[i]};
        add(i, 1); // 初始化树状数组
    }
    sort(p+1, p+n+1, [](auto& x, auto& y){return x.a < y.a;});

    int ptr = 1;
    ll ans = 0;
    for(int i=1; i<=n; i++) {
        // 删除已处理的i和a_j < i的j
        while(ptr <=n && p[ptr].a < i) {
            if(!vis[p[ptr].x]) add(p[ptr].x, -1);
            ptr++;
        }
        ans += query(a[i]); // 统计满足j≤a_i的j数量
    }
    printf("%lld\n", ans);
}
```

---
处理用时：57.89秒