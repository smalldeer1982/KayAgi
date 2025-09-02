# 题目信息

# [USACO09DEC] Bobsledding S

## 题目描述

Bessie has entered a bobsled competition because she hopes her hefty weight will give her an advantage over the L meter course (2 <= L <= 1,000,000,000).

Bessie will push off the starting line at 1 meter per second, but her speed can change while she rides along the course. Near the middle of every meter Bessie travels, she can change her speed either by using gravity to accelerate by one meter per second or by braking to stay at the same speed or decrease her speed by one meter per second.

Naturally, Bessie must negotiate N (1 <= N <= 100,000) turns on the way down the hill. Turn i is located T\_i meters from the course start (1 <= T\_i <= L-1), and she must be enter the corner meter at a speed of at most S\_i meters per second (1 <= S\_i <= 1,000,000,000). Bessie can cross the finish line at any speed she likes.

Help Bessie learn the fastest speed she can attain without exceeding the speed limits on the turns.

Consider this course with the meter markers as integers and the turn speed limits in brackets (e.g., '[3]'):

```cpp

|   1   2   3   4   5   6   7[3]
|---+---+---+---+---+---+---+
|                            \
Start                         + 8    
                               \
                                + 9    
                                 \
                                  + 10       +++ 14 (finish)
                                   \         /
                              11[1] +---+---+
                                        12  13[8]
```
Below is a chart of Bessie's speeds at the beginning of each meter length of the course:

````
Max:                              3               1       8 
Mtrs: 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14 Spd:  1   2   3   4   5   5   4   3   4   3   2   1   2   3   4 
```
Her maximum speed was 5 near the beginning of meter 4. 

贝茜从山顶滑雪到山脚，山顶到山脚距离是L(2<L<10^9)米.贝茜在起点的速度是1米每 秒，但是他的速度是可以改变的，在每一米的速度可以是前一米的速度加1、减1，或者等于前一米 的速度.在滑行的过程中，贝茜会遇到N<=100000)个转弯处，第i个转弯处位于距离出发 Ti米处，为了安全，贝茜到达第i个转弯处的速度不能超过Si(1<Si<10^9)米 每秒.当然贝茜到达终点时的速度没有最大限制.请你计算贝茜在滑雪过程中最大的速度可以是多 少？


## 样例 #1

### 输入

```
14 3 
7 3 
11 1 
13 8 
```

### 输出

```
5 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕贝茜滑雪问题展开，核心思路大多是先处理每个拐角的最大速度限制，再计算每两个拐角间的最大速度。整体上可分为贪心和动态规划两种方法。

贪心方法通过从后往前预处理每个拐角的最大速度限制，确保后续拐角能顺利通过，再从前往后模拟计算最大速度；动态规划方法则以每个转弯点为状态，通过预处理消除后效性，进而计算最大速度。

各题解在思路清晰度、代码可读性和优化程度上有所差异，但都能解决问题。

### 所选题解
- **作者：1124828077ccj（4星）**
  - **关键亮点**：思路清晰，代码简洁，通过结构体存储拐角信息，先排序再从后往前推出最大速度限制，最后从前往后模拟计算最大速度。
  - **个人心得**：无
- **作者：Lolierl（4星）**
  - **关键亮点**：对贪心思路的解释详细，证明了引理，通过数学推导得出计算最大速度的公式，代码中对边界情况处理细致。
  - **个人心得**：认为楼下题解解释不清，自己补充思路，提到代码可能因保险开 `ll` 码风丑陋，细节较多需注意边界情况。
- **作者：Usada_Pekora（4星）**
  - **关键亮点**：采用动态规划方法，思路明确，通过预处理消除后效性，代码实现简洁。
  - **个人心得**：无

### 重点代码及核心实现思想
#### 作者：1124828077ccj
```cpp
// 结构体存储拐角信息
typedef struct{
    int t,s,q;
}P;
bool cmp(P aa,P bb){
    return (aa.t<bb.t);
}
P p[100002];

// 从后往前推出最大速度限制
for (int i=n;i>=2;i--)
    p[i-1].q=min(p[i-1].s,p[i].q+p[i].t-p[i-1].t);

// 从前往后模拟计算最大速度
for (int i=2;i<=n;i++)
{
    if (m+p[i].t-p[i-1].t<=p[i].q) ans=max(ans,m+p[i].t-p[i-1].t);
    else ans=max(ans,(p[i].q+p[i].t-p[i-1].t+m)/2);
    m=min(p[i].q,m+p[i].t-p[i-1].t);
}
```
核心思想：先对拐角按位置排序，从后往前处理每个拐角的最大速度限制，再从前往后模拟，根据当前速度和距离计算最大速度。

#### 作者：Lolierl
```cpp
// 结构体存储拐角信息
struct h
{
    int t, s; 
}b[100005]; 

int cmp(h a, h b)
{
    return a.t < b.t; 
}

// 从后往前算出每个拐弯角让后面所有拐弯角都能满足限制的速度最大值
for(int i = n; i >= 1; i--)
    ok[i] = ((b[i].s > ok[i + 1] + (b[i + 1].t - b[i].t)) ? ok[i + 1] + (b[i + 1].t - b[i].t) : b[i].s); 

// 计算最大速度
for(int i = 0; i <= n; i++)
    maxn = (((ans[i] + (b[i + 1].t - b[i].t + ans[i + 1] - ans[i]) / 2) > maxn) ? ans[i] + (b[i + 1].t - b[i].t + ans[i + 1] - ans[i]) / 2 : maxn); 
```
核心思想：先对拐角按位置排序，从后往前预处理每个拐角的最大速度限制，再根据公式计算每两个拐角间的最大速度。

#### 作者：Usada_Pekora
```cpp
// 结构体存储拐角信息
struct node{
    int s,t;
}a[100005];
inline bool cmp(const node x,const node y){
    return x.t<y.t; 
}

// 预处理消除后效性
for(int i=n;i>=1;--i)
    a[i].s=min(a[i].s,a[i+1].s+a[i+1].t-a[i].t);

// 动态规划计算最大速度
for(int i=1;i<=n+1;++i){
    f[i]=min(a[i].s,f[i-1]+a[i].t-a[i-1].t);
    ans=max((f[i]+f[i-1]+a[i].t-a[i-1].t)/2,ans);
}
```
核心思想：先对拐角按位置排序，从后往前预处理每个拐角的最大速度限制，消除后效性，再以每个转弯点为状态进行动态规划，计算最大速度。

### 最优关键思路或技巧
- **预处理拐角速度限制**：从后往前处理每个拐角的最大速度限制，确保后续拐角能顺利通过，消除后效性。
- **数学推导计算最大速度**：根据速度变化规则和距离，推导出计算每两个拐角间最大速度的公式。

### 可拓展之处
同类型题可能会改变速度变化规则、增加更多限制条件等。类似算法套路可应用于其他有状态限制和状态转移的问题，如路径规划、资源分配等。

### 推荐题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心算法。
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：考察动态规划算法。
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：考察动态规划算法。

---
处理用时：41.75秒