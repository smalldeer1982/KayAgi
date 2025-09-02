# 题目信息

# Yet Another Card Deck

## 题目描述

You have a card deck of $ n $ cards, numbered from top to bottom, i. e. the top card has index $ 1 $ and bottom card — index $ n $ . Each card has its color: the $ i $ -th card has color $ a_i $ .

You should process $ q $ queries. The $ j $ -th query is described by integer $ t_j $ . For each query you should:

- find the highest card in the deck with color $ t_j $ , i. e. the card with minimum index;
- print the position of the card you found;
- take the card and place it on top of the deck.

## 说明/提示

Description of the sample:

1. the deck is $ [2, 1, 1, 4, \underline{3}, 3, 1] $ and the first card with color $ t_1 = 3 $ has position $ 5 $ ;
2. the deck is $ [3, \underline{2}, 1, 1, 4, 3, 1] $ and the first card with color $ t_2 = 2 $ has position $ 2 $ ;
3. the deck is $ [2, 3, \underline{1}, 1, 4, 3, 1] $ and the first card with color $ t_3 = 1 $ has position $ 3 $ ;
4. the deck is $ [\underline{1}, 2, 3, 1, 4, 3, 1] $ and the first card with color $ t_4 = 1 $ has position $ 1 $ ;
5. the deck is $ [1, 2, 3, 1, \underline{4}, 3, 1] $ and the first card with color $ t_5 = 4 $ has position $ 5 $ .

## 样例 #1

### 输入

```
7 5
2 1 1 4 3 3 1
3 2 1 1 4```

### 输出

```
5 2 3 1 5```

# AI分析结果

### 题目内容重写
# 又一个卡牌堆

## 题目描述

你有一个包含 $n$ 张卡牌的卡堆，卡牌从顶部到底部依次编号，即顶部的卡牌编号为 $1$，底部的卡牌编号为 $n$。每张卡牌有一个颜色：第 $i$ 张卡牌的颜色为 $a_i$。

你需要处理 $q$ 个查询。第 $j$ 个查询由整数 $t_j$ 描述。对于每个查询，你需要：

- 找到卡堆中颜色为 $t_j$ 的最高卡牌，即编号最小的卡牌；
- 输出你找到的卡牌的位置；
- 将该卡牌取出并放到卡堆的顶部。

## 说明/提示

样例解释：

1. 卡堆为 $[2, 1, 1, 4, \underline{3}, 3, 1]$，第一个查询 $t_1 = 3$ 的卡牌位置为 $5$；
2. 卡堆为 $[3, \underline{2}, 1, 1, 4, 3, 1]$，第二个查询 $t_2 = 2$ 的卡牌位置为 $2$；
3. 卡堆为 $[2, 3, \underline{1}, 1, 4, 3, 1]$，第三个查询 $t_3 = 1$ 的卡牌位置为 $3$；
4. 卡堆为 $[\underline{1}, 2, 3, 1, 4, 3, 1]$，第四个查询 $t_4 = 1$ 的卡牌位置为 $1$；
5. 卡堆为 $[1, 2, 3, 1, \underline{4}, 3, 1]$，第五个查询 $t_5 = 4$ 的卡牌位置为 $5$。

## 样例 #1

### 输入

```
7 5
2 1 1 4 3 3 1
3 2 1 1 4
```

### 输出

```
5 2 3 1 5
```

### 算法分类
模拟

### 题解分析与结论
本题的核心逻辑是模拟卡牌堆的操作，即每次查询时找到指定颜色的最上面的卡牌，输出其位置并将其移动到顶部。由于卡牌的颜色值域较小（$a_i \leq 50$），可以通过预处理每种颜色最上面的卡牌位置，并在每次查询时更新这些位置。

### 所选高星题解
1. **作者：_xbn (赞：4)**
   - **星级：4**
   - **关键亮点：** 使用数组记录每种颜色第一次出现的位置，并在每次查询时更新这些位置。代码简洁，思路清晰。
   - **核心代码：**
     ```cpp
     int n,q,p[1000001],a[1000001],o=0;
     int main()
     {
         cin>>n>>q;
         for(int i=1;i<=n;i++)
         {
            cin>>a[i];
            o=max(o,a[i]);
            if(!p[a[i]])p[a[i]]=i;
         }
         int x;
         for(int i=1;i<=q;i++)
         {
             cin>>x;
             cout<<p[x]<<" ";
             for(int j=1;j<=o;j++)
                if(p[j]<p[x])p[j]++;
             p[x]=1;	
         }
         return 0;
     }
     ```

2. **作者：pitiless0514 (赞：1)**
   - **星级：4**
   - **关键亮点：** 同样使用数组记录每种颜色第一次出现的位置，并在查询时更新位置。代码简洁，易于理解。
   - **核心代码：**
     ```cpp
     int n,q,a[N],b[N];
     int main(){
         ios::sync_with_stdio(0);
         cin.tie(0),cout.tie(0);
         cin>>n>>q;
         for(int i=1;i<=n;i++){
             cin>>a[i];
             if(!b[a[i]]) b[a[i]]=i;
         }
         for(int i=1;i<=q;i++){
             int x;
             cin>>x;
             cout<<b[x]<<" ";
             for(int j=1;j<=50;j++){
                 if(b[j]<b[x]) b[j]++;
             }
             b[x]=1;
         }
         return 0;
     }
     ```

3. **作者：云浅知处 (赞：1)**
   - **星级：4**
   - **关键亮点：** 预处理每种颜色最上面的卡牌位置，并在查询时更新位置。代码结构清晰，易于理解。
   - **核心代码：**
     ```cpp
     int n,q,a[MAXN],t[MAXN];
     int p[100];
     signed main(void){
         cin>>n>>q;
         int maxx=0;
         for(int i=1;i<=n;i++)cin>>a[i],maxx=max(maxx,a[i]);
         for(int i=1;i<=n;i++){
             if(!p[a[i]])p[a[i]]=i;
         }
         for(int i=1;i<=q;i++){
             cin>>t[i];
         }
         for(int i=1;i<=q;i++){
             cout<<p[t[i]]<<" ";
             for(int j=1;j<=maxx;j++){
                 if(j==t[i])continue;
                 if(p[j]<p[t[i]])p[j]++;
             }
             p[t[i]]=1;
         }
         return 0;
     }
     ```

### 最优关键思路
通过预处理记录每种颜色最上面的卡牌位置，并在每次查询时更新这些位置。由于颜色值域较小，可以直接使用数组进行记录和更新，时间复杂度为 $O(50(n+q))$。

### 可拓展之处
类似的问题可以扩展到更大的值域或更复杂的操作，例如需要处理多个卡牌堆的合并或分裂操作。此时可以考虑使用更高效的数据结构，如平衡树或线段树来维护卡牌的位置。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

---
处理用时：41.81秒