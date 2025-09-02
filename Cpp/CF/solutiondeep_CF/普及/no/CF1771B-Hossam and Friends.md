# 题目信息

# Hossam and Friends

## 题目描述

Hossam makes a big party, and he will invite his friends to the party.

He has $ n $ friends numbered from $ 1 $ to $ n $ . They will be arranged in a queue as follows: $ 1, 2, 3, \ldots, n $ .

Hossam has a list of $ m $ pairs of his friends that don't know each other. Any pair not present in this list are friends.

A subsegment of the queue starting from the friend $ a $ and ending at the friend $ b $ is $ [a, a + 1, a + 2, \ldots, b] $ . A subsegment of the queue is called good when all pairs of that segment are friends.

Hossam wants to know how many pairs $ (a, b) $ there are ( $ 1 \le a \le b \le n $ ), such that the subsegment starting from the friend $ a $ and ending at the friend $ b $ is good.

## 说明/提示

In the first example, the answer is $ 4 $ .

The good subsegments are:

\[1\]

\[2\]

\[3\]

\[1, 2\]

In the second example, the answer is $ 5 $ .

The good subsegments are:

\[1\]

\[2\]

\[3\]

\[4\]

\[3, 4\]

## 样例 #1

### 输入

```
2
3 2
1 3
2 3
4 2
1 2
2 3```

### 输出

```
4
5```

# AI分析结果

【题目内容】
# Hossam 和朋友们

## 题目描述

Hossam 举办了一个大型派对，并邀请了他的朋友们参加。

他有 $n$ 个朋友，编号从 $1$ 到 $n$。他们按以下顺序排成一队：$1, 2, 3, \ldots, n$。

Hossam 有一个列表，包含 $m$ 对不认识的朋友。任何不在这个列表中的朋友对都是互相认识的。

队列中的一个子段从朋友 $a$ 开始，到朋友 $b$ 结束，定义为 $[a, a + 1, a + 2, \ldots, b]$。如果一个子段中的所有朋友对都互相认识，那么这个子段被称为“好的”。

Hossam 想知道有多少对 $(a, b)$（$1 \le a \le b \le n$），使得从朋友 $a$ 开始到朋友 $b$ 结束的子段是好的。

## 说明/提示

在第一个例子中，答案是 $4$。

好的子段是：

\[1\]

\[2\]

\[3\]

\[1, 2\]

在第二个例子中，答案是 $5$。

好的子段是：

\[1\]

\[2\]

\[3\]

\[4\]

\[3, 4\]

## 样例 #1

### 输入

```
2
3 2
1 3
2 3
4 2
1 2
2 3```

### 输出

```
4
5```

【算法分类】
贪心

【题解分析与结论】
本题的核心在于如何高效地计算所有“好的”子段。题解中主要采用了贪心算法，通过维护每个起点能延伸到的最远终点，并利用单调性进行优化。

【精选题解】
1. **作者：cjh20090318 (赞：19)**
   - **星级：5星**
   - **关键亮点：**
     - 使用贪心策略，通过维护每个起点能延伸到的最远终点，确保子段的有效性。
     - 通过从大到小枚举并更新限制，确保每个起点的终点不会超过其后续起点的终点。
     - 代码简洁明了，时间复杂度为 $O(n + m)$，效率高。
   - **核心代码：**
     ```cpp
     for(int i=1;i<=n;i++) a[i]=n;
     while(m--){
         scanf("%d%d",&x,&y);
         if(x>y) swap(x,y);
         a[x]=min(a[x],y-1);
     }
     for(int i=n-1;i>=1;i--)
         a[i]=min(a[i],a[i+1]);
     long long ans=0;
     for(int i=1;i<=n;i++)
         ans+=a[i]-i+1;
     ```

2. **作者：Polaris_Australis_ (赞：2)**
   - **星级：4星**
   - **关键亮点：**
     - 通过离线处理边，并从右往左扫描，确保每个左端点的右端点不会超过其后续左端点的右端点。
     - 使用排序和双指针技巧，时间复杂度为 $O(n + m \log m)$，思路清晰。
   - **核心代码：**
     ```cpp
     sort(id+1,id+1+m,cmp);
     int now(m),rr(n);
     long long ans(0);
     for(int i(n);i;--i){
         while(now&&l[id[now]]==i){
             rr=min(rr,r[id[now]]-1);
             --now;
         }
         ans+=rr-i+1;
     }
     ```

3. **作者：nytyq (赞：0)**
   - **星级：4星**
   - **关键亮点：**
     - 使用类似贪心的策略，通过维护每个点的最远延伸距离，并利用单调性进行更新。
     - 代码结构清晰，时间复杂度为 $O(n + m)$，与最优解一致。
   - **核心代码：**
     ```cpp
     for(int i=1;i<=n;i++) ex[i]=n;
     for(int i=1;i<=m;i++){
         cin>>x[i]>>y[i];
         if(x[i]>y[i]) swap(x[i],y[i]);
         ex[x[i]]=min(ex[x[i]],y[i]-1);
     }
     for(int i=n-1;i>=1;i--) ex[i]=min(ex[i],ex[i+1]);
     int ans=0;
     for(int i=1;i<=n;i++) ans+=(ex[i]-i+1);
     ```

【最优关键思路或技巧】
- **贪心策略**：通过维护每个起点能延伸到的最远终点，确保子段的有效性。
- **单调性优化**：利用从大到小枚举并更新限制，确保每个起点的终点不会超过其后续起点的终点。
- **离线处理**：通过离线处理边，并从右往左扫描，确保每个左端点的右端点不会超过其后续左端点的右端点。

【可拓展之处】
- 类似的问题可以通过维护每个起点的最远终点，并利用单调性进行优化。例如，求最长连续子数组、最长不重复子串等问题。

【推荐题目】
1. [P11233 - CSP-S 2024 T3](https://www.luogu.com.cn/problem/P11233)
2. [P11234 - CSP-S 2024 T4](https://www.luogu.com.cn/problem/P11234)
3. [P11235 - CSP-S 2024 T5](https://www.luogu.com.cn/problem/P11235)

---
处理用时：37.78秒