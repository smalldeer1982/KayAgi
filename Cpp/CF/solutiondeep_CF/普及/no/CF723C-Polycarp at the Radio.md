# 题目信息

# Polycarp at the Radio

## 题目描述

Polycarp is a music editor at the radio station. He received a playlist for tomorrow, that can be represented as a sequence $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is a band, which performs the $ i $ -th song. Polycarp likes bands with the numbers from $ 1 $ to $ m $ , but he doesn't really like others.

We define as $ b_{j} $ the number of songs the group $ j $ is going to perform tomorrow. Polycarp wants to change the playlist in such a way that the minimum among the numbers $ b_{1},b_{2},...,b_{m} $ will be as large as possible.

Find this maximum possible value of the minimum among the $ b_{j} $ ( $ 1<=j<=m $ ), and the minimum number of changes in the playlist Polycarp needs to make to achieve it. One change in the playlist is a replacement of the performer of the $ i $ -th song with any other group.

## 说明/提示

In the first sample, after Polycarp's changes the first band performs two songs ( $ b_{1}=2 $ ), and the second band also performs two songs ( $ b_{2}=2 $ ). Thus, the minimum of these values equals to $ 2 $ . It is impossible to achieve a higher minimum value by any changes in the playlist.

In the second sample, after Polycarp's changes the first band performs two songs ( $ b_{1}=2 $ ), the second band performs three songs ( $ b_{2}=3 $ ), and the third band also performs two songs ( $ b_{3}=2 $ ). Thus, the best minimum value is $ 2 $ .

## 样例 #1

### 输入

```
4 2
1 2 3 2
```

### 输出

```
2 1
1 2 1 2 
```

## 样例 #2

### 输入

```
7 3
1 3 2 2 2 2 1
```

### 输出

```
2 1
1 3 3 2 2 2 1 
```

## 样例 #3

### 输入

```
4 4
1000000000 100 7 1000000000
```

### 输出

```
1 4
1 2 3 4 
```

# AI分析结果



# Polycarp at the Radio

## 题目描述

Polycarp是电台的音乐编辑。他收到了明天的播放列表，该列表可以表示为序列 $a_{1},a_{2},...,a_{n}$，其中 $a_{i}$ 表示第 $i$ 首歌曲的表演乐队。Polycarp喜欢编号为 $1$ 到 $m$ 的乐队，对其他乐队无感。

定义 $b_{j}$ 为乐队 $j$ 明天表演的歌曲数量。Polycarp希望通过修改播放列表，使得最小值 $\min(b_{1},b_{2},...,b_{m})$ 尽可能大。

求这个最大可能的极小值，以及达成该目标所需的最小修改次数。每次修改可将任意位置的乐队替换为其他乐队。

## 说明/提示

第一个样例中，修改后两个乐队各表演2首，最小值达到最大可能值2。  
第二个样例中，三个乐队分别表演2、3、2首，最小值为2。  
第三个样例中，所有乐队必须至少出现1次，需要4次修改。

## 样例

### 样例1输入
```
4 2
1 2 3 2
```

### 样例1输出
```
2 1
1 2 1 2 
```

### 样例2输入
```
7 3
1 3 2 2 2 2 1
```

### 样例2输出
```
2 1
1 3 3 2 2 2 1 
```

### 样例3输入
```
4 4
1000000000 100 7 1000000000
```

### 样例3输出
```
1 4
1 2 3 4 
```

---

**算法分类**：贪心

---

### 题解分析与结论

题目要求最大化各乐队出现次数的最小值，属于典型的资源均匀分配问题。各题解均采用贪心策略，核心思路为：

1. **确定理论最大值**：最大可能的最小值 $k = \lfloor n/m \rfloor$
2. **两阶段处理**：
   - **保留合法元素**：统计原数组中1~m的乐队出现次数，保留不超过k次的元素
   - **填补空缺**：将未被保留的位置分配给未达到k次的乐队

**关键难点**在于如何高效分配修改位置，确保每个乐队恰好达到k次。暴力遍历数组的时间复杂度为 $O(mn)$，在数据范围 $n,m \le 2000$ 时可行。

---

### 精选题解

#### 题解作者：Ninelife_Cat（⭐⭐⭐⭐⭐）  
**核心亮点**：  
- 使用`vis[]`数组标记保留位置，逻辑清晰  
- 双重循环填补空缺，代码简洁易懂  
- 正确性证明完整，给出理论最大值推导  

**关键代码**：  
```cpp
int n,m,a[N],cnt[N],ans,vis[N];
int main() {
    n=read();m=read(); int p=n/m;
    for(int i=1;i<=n;++i) {
        a[i]=read();
        if(a[i]<=m && cnt[a[i]]<p) 
            ++cnt[a[i]], vis[i]=1; // 保留合法元素
    }
    for(int i=1;i<=m;++i) 
        while(cnt[i]<p) 
            for(int j=1;j<=n;++j) // 遍历寻找可修改位置
                if(!vis[j]) { 
                    vis[j]=1, a[j]=i; 
                    ++cnt[i], ++ans; break; 
                }
    cout<<p<<" "<<ans<<endl;
    for(int i=1;i<=n;++i) cout<<a[i]<<" ";
}
```

---

### 最优思路总结

1. **理论极值计算**：直接通过 $\lfloor n/m \rfloor$ 确定目标值  
2. **双标记策略**：  
   - 用`cnt[]`记录各乐队当前计数  
   - 用`vis[]`标记无需修改的位置  
3. **贪心填补**：按乐队顺序补足空缺，优先利用可修改位置  

**同类问题拓展**：  
- 资源均匀分配类问题（如P1250 种树）  
- 最大化最小值问题（如P2218 [HAOI2007]覆盖问题）  

---

### 推荐练习
1. P1250 种树（贪心策略）
2. P2218 [HAOI2007]覆盖问题（二分+贪心）  
3. P2985 [USACO10OPEN] Cow Eating Twigs（资源分配）

---
处理用时：65.09秒