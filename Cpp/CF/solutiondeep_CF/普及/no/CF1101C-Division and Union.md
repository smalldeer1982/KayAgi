# 题目信息

# Division and Union

## 题目描述

There are $ n $ segments $ [l_i, r_i] $ for $ 1 \le i \le n $ . You should divide all segments into two non-empty groups in such way that there is no pair of segments from different groups which have at least one common point, or say that it's impossible to do it. Each segment should belong to exactly one group.

To optimize testing process you will be given multitest.

## 说明/提示

In the first query the first and the second segments should be in different groups, but exact numbers don't matter.

In the second query the third segment intersects with the first and the second segments, so they should be in the same group, but then the other group becomes empty, so answer is $ -1 $ .

In the third query we can distribute segments in any way that makes groups non-empty, so any answer of $ 6 $ possible is correct.

## 样例 #1

### 输入

```
3
2
5 5
2 3
3
3 5
2 3
2 3
3
3 3
4 4
5 5
```

### 输出

```
2 1 
-1
1 1 2 
```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

有 $n$ 条线段 $[l_i, r_i]$，其中 $1 \le i \le n$。你需要将所有线段分成两个非空的组，使得来自不同组的线段之间没有公共点，或者说明这是不可能的。每条线段必须属于且仅属于一个组。

为了优化测试过程，题目会给出多组测试数据。

#### 说明/提示

在第一个查询中，第一条和第二条线段应该在不同的组中，但具体的组号不重要。

在第二个查询中，第三条线段与第一条和第二条线段相交，因此它们应该在同一个组中，但这样另一个组就为空，所以答案是 $-1$。

在第三个查询中，我们可以以任何方式分配线段，只要组非空即可，因此任何可能的答案都是正确的。

#### 样例 #1

##### 输入

```
3
2
5 5
2 3
3
3 5
2 3
2 3
3
3 3
4 4
5 5
```

##### 输出

```
2 1 
-1
1 1 2 
```

### 算法分类

贪心、排序

### 题解分析与结论

1. **Austin0116的题解**（4星）
   - **关键亮点**：通过按左端点排序，找到第一个不连续的左端点作为分割点，简单高效。
   - **代码实现**：先按左端点排序，找到分割点后再按原顺序排序输出。
   - **核心代码**：
     ```cpp
     sort(a+1,a+1+n,cmp1);
     mx=fl=0;
     for(int i=1;i<n;i++){
         mx=max(mx,a[i].y);
         if(mx<a[i+1].x){
             fl=a[i].x;
             break;
         } 
     } 
     sort(a+1,a+1+n,cmp2);
     if(!fl) printf("-1");
     else for(int i=1;i<=n;i++){
         if(a[i].x<=fl) printf("1 ");
         else printf("2 ");
     } 
     ```

2. **G_A_TS的题解**（4星）
   - **关键亮点**：通过合并线段找到断点，思路清晰，代码简洁。
   - **代码实现**：按左端点排序，合并线段找到断点，输出时根据断点判断组别。
   - **核心代码**：
     ```cpp
     sort(edge+1,edge+n+1,cmp);
     nowlen=edge[1].l;
     for(int i=1;i<=n;i++){
         if(edge[i].r>nowlen&&edge[i].l<=nowlen){
             nowlen=edge[i].r;
         } else {
             if(edge[i].r>nowlen){
                 POI=nowlen;
                 break;
             }
         }
     }
     if(POI==-1) cout<<-1<<endl;
     else for(int i=1;i<=n;i++){
         if(yr[i]<=POI) cout<<1<<" ";
         else cout<<2<<" ";
     }
     ```

3. **decoqwq的题解**（4星）
   - **关键亮点**：通过判断线段是否连续覆盖来确定是否可以分割，思路直接。
   - **代码实现**：按左端点排序，判断是否连续覆盖，输出时根据覆盖情况判断组别。
   - **核心代码**：
     ```cpp
     sort(e+1,e+n+1);
     int rr=-1;
     int flag=0;
     for(int i=1;i<=n;i++){
         if(i==1){
             rr=e[i].r;
             continue;
         }
         if(e[i].l>rr){
             flag=1;
             break;
         } else {
             rr=max(rr,e[i].r);
         }
     }
     if(!flag) cout<<"-1"<<endl;
     else for(int i=1;i<=n;i++){
         if(r[i]<=rr) printf("1 ");
         else printf("2 ");
     }
     ```

### 最优关键思路

通过按左端点排序，找到第一个不连续的左端点作为分割点，或者通过合并线段找到断点，然后根据断点判断组别。这种方法简单高效，适用于大多数情况。

### 可拓展之处

类似的问题可以扩展到多维空间中的区间分割，或者考虑更多组的情况。此外，可以结合其他算法如并查集来处理更复杂的区间关系。

### 推荐题目

1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1045 [NOIP2005 提高组] 采药](https://www.luogu.com.cn/problem/P1045)

---
处理用时：34.90秒