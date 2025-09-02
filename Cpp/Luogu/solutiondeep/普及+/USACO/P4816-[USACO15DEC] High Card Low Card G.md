# 题目信息

# [USACO15DEC] High Card Low Card G

## 题目描述

奶牛 Bessie 是卡牌游戏的狂热爱好者，尽管她没有对生拇指，但这并不影响她的热情。遗憾的是，她的同伴们在卡牌游戏方面水平堪忧，甚至出牌顺序都完全可预测！尽管如此，Bessie 仍需精心策划才能获胜。

Bessie 和她的朋友 Elsie 正在玩一个简单的卡牌游戏。她们使用一副包含 $2N$ 张卡牌的牌组（编号为 $1 \ldots 2N$），并将牌分成各 $N$ 张。随后进行 $N$ 轮比赛：每轮双方各打出一张牌。在前 $N/2$ 轮中，打出较大数字的玩家得 1 分；在后 $N/2$ 轮中，规则反转，打出较小数字的玩家得 1 分。

已知 Bessie 可以预知 Elsie 每轮出牌的顺序，请计算 Bessie 能够获得的最大分数。

## 说明/提示

在此样例中，Bessie 手中的卡牌为 $2$、$5$、$6$ 和 $7$。她可以通过在比赛后半段保留 $2$ 这张牌，从而最多获得 2 分。

题目提供者：Brian Dean

## 样例 #1

### 输入

```
4
1
8
4
3
```

### 输出

```
2```

# AI分析结果

### 综合分析与结论
这些题解均采用贪心算法解决奶牛卡牌游戏问题，核心思路是将游戏分为前半段（大数字获胜）和后半段（小数字获胜）两部分，分别对 Elsie 和 Bessie 的牌进行排序，然后根据贪心策略出牌以获取最大分数。各题解在具体实现上略有差异，如存储牌的方式、排序方法和贪心比较的细节，但整体思路一致。

### 所选题解
- **liyilin2004（4星）**
    - **关键亮点**：思路清晰，代码简洁易懂，通过标记数组区分 Elsie 和 Bessie 的牌，分别处理前后半段游戏，逻辑清晰。
- **onepeople666（4星）**
    - **关键亮点**：详细阐述了解题步骤，包括读入存储、排序和贪心过程，将贪心思路与田忌赛马类比，易于理解。
- **__Hacheylight__（4星）**
    - **关键亮点**：对贪心策略的正确性进行了证明，代码中使用宏定义简化操作，逻辑清晰，注释详细。

### 重点代码与核心实现思想
#### liyilin2004
```cpp
// 标记 Elsie 的牌
for(int i=1;i<=n/2;i++) {
    cin>>a[i];
    b[a[i]]=1;
}
for(int i=1;i<=n/2;i++) {
    cin>>c[i];
    b[c[i]]=1;
}
sort(a+1,a+1+n/2);
sort(c+1,c+1+n/2);
// 前半段贪心
int j=2*n;
for(int i=n/2;i>=1;i--) {
    while(b[j]&&j>=1) j--;
    if(j<a[i]) continue;
    else b[j]=1,ans++;
}
// 后半段贪心
j=1;
for(int i=1;i<=n/2;i++) {
    while(b[j]&&j<=2*n) j++;
    if(j>c[i]) continue;
    else b[j]=1,ans++;
}
```
核心思想：先标记 Elsie 的牌，然后对前后半段 Elsie 的牌分别排序。前半段从大到小枚举 Elsie 的牌，找 Bessie 未用的最大牌比较；后半段从小到大枚举 Elsie 的牌，找 Bessie 未用的最小牌比较。

#### onepeople666
```cpp
// 读入 Elsie 的牌并标记
bool a[100010]= {0};
int n,e[50010],b[50010],c=1;
cin>>n;
for(int i=1; i<=n; i++) {
    cin>>e[i];
    a[e[i]]=1;
}
// 找出 Bessie 的牌
for(int i=1; i<=2*n; i++)
    if(a[i]==0) b[c++]=i;
// 排序
bool cmp(int a,int b) {
    return a>b;
}
sort(e+1,e+n/2+1,cmp);
sort(e+n/2+1,e+n+1);
// 前半段贪心
c=n/2+1,v=n;
for(int i=1; i<=n/2; i++) {
    if(b[v]>e[i]) ans++,v--;
    else c++;
}
// 后半段贪心
c=n/2,v=1;
for(int i=n/2+1; i<=n; i++) {
    if(b[v]<e[i]) ans++,v++;
    else c--;
}
```
核心思想：先读入 Elsie 的牌并标记，通过遍历找出 Bessie 的牌。对 Elsie 前后半段的牌分别按要求排序，然后用两个指针分别记录 Bessie 最小和最大的牌，进行贪心比较。

#### __Hacheylight__
```cpp
// 读入 Elsie 的牌
scanf("%d", &n);
rep(i, 1, n) scanf("%d", &a[i]);
sort(a + 1, a + n / 2 + 1, cmp1);
sort(a + n / 2 + 1, a + n + 1, cmp2);
rep(i, 1, n) app[a[i]] = 1;
// 找出 Bessie 的牌
per(i, n * 2, 1) if (!app[i]) b[++cnt] = i;
sort(b + 1, b + n / 2 + 1, cmp1);
sort(b + n / 2 + 1, b + n + 1, cmp2);
// 前半段贪心
int l = 1, r = n / 2, ll = 1, rr = n / 2;
while (l <= r && ll <= rr) {
    if (a[l] < b[ll]) {
        l++, ll++, ans++;
    } else {
        l++, rr--;
    }
}
// 后半段贪心
l = n / 2 + 1, r = n, ll = n / 2 + 1, rr = n;
while (l <= r && ll <= rr) {
    if (a[l] > b[ll]) {
        l++, ll++, ans++;
    } else {
        l++, rr--;
    }
}
```
核心思想：读入 Elsie 的牌并排序，找出 Bessie 的牌并排序。用双指针分别遍历前后半段 Elsie 和 Bessie 的牌，根据大小关系进行贪心比较。

### 最优关键思路或技巧
- **标记数组**：使用标记数组区分 Elsie 和 Bessie 的牌，方便找出 Bessie 的牌。
- **排序**：对 Elsie 和 Bessie 的牌分别按前后半段的规则进行排序，便于贪心比较。
- **贪心策略**：前半段用 Bessie 较大的牌去赢 Elsie 的牌，后半段用 Bessie 较小的牌去赢 Elsie 的牌，类似于田忌赛马的思想。

### 可拓展之处
同类型题或类似算法套路：
- 其他卡牌游戏或博弈类问题，可根据不同的游戏规则调整贪心策略。
- 区间调度问题，可根据区间的起始和结束时间进行排序和贪心选择。

### 推荐题目
- P1650 田忌赛马
- P3129 [USACO15DEC]High Card Low Card Silver
- P6179 [USACO15DEC]High Card Low Card Platinum

### 个人心得摘录与总结
- **Level_Down**：直接暴力判断会有 2 个点超时，通过将对方手牌的前半部分从小到大排序，后半部分从大到小排序进行优化，提高了效率。总结：在遇到超时问题时，可根据贪心策略对数据进行排序优化。

---
处理用时：46.34秒