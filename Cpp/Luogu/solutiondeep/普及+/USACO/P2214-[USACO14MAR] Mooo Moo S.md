# 题目信息

# [USACO14MAR] Mooo Moo S

## 题目描述

Farmer John has completely forgotten how many cows he owns!  He is too embarrassed to go to his fields to count the cows, since he doesn't want the cows to realize his mental lapse.  Instead, he decides to count his cows secretly by planting microphones in the fields in which his cows tend to gather, figuring that he can determine the number of cows from the total volume of all the mooing he hears.

FJ's N fields (1 <= N <= 100) are all arranged in a line along a long straight road.  Each field might contain several types of cows; FJ owns cows that come from B different breeds (1 <= B <= 20), and a cow of breed i moos at a volume of V(i) (1 <= V(i) <= 100).  Moreover, there is a strong wind blowing down the road, which carries the sound of mooing in one direction from left to right: if the volume of mooing in some field is X, then in the next field this will contribute X-1 to the total mooing volume (and X-2 in the field after that, etc.). Otherwise stated, the mooing volume in a field is the sum of the contribution due to cows in that field, plus X-1, where X is the total mooing volume in the preceding field.

Given the volume of mooing that FJ records in each field, please compute the minimum possible number of cows FJ might own.

The volume FJ records in any field is at most 100,000.

### 题目背景
农夫约翰完全忘了他有多少头牛了！他不好意思到牧场里去数牛，因为他不想让牛意识到他的健忘。取而代之的是，他决定在奶牛聚集的牧场里安装麦克风，秘密计算出他能从中听到的所有牛叫声的总音量，以便以此确定奶牛的数量。
### 题目描述
$FJ$ 的 $N(1\le N\le 100)$ 个牧场都是沿着一条笔直的道路分布的。每一个牧场可能有许多种品种的奶牛； $FJ$ 拥有 $B(1\le B\le 20)$ 个不同品种的奶牛，而第 $i$ 种奶牛的叫声音量为 $V_i(1\le V_i \le 100)$ 。此外，有一股强风沿着道路吹来，将牛的叫声从左往右传递，如果某个牧场的总音量是 $x$ ，那么它将传递 $x-1$ 的音量到右边的下一个牧场。这就意味着，一个牧场里的总音量是处在该牧场的奶牛所发出的音量加上左边前一个牧场的总音量 $-1$ 。数据保证，每一个牧场内由该牧场所有奶牛所发出的总音量最多为$10^5$。
### 输入格式
第 $1$ 行：两个用空格分隔的整数 $N$ 和 $B$。      
第 $2...B+1$ 行：第 $i+1$ 行包含整数 $V_i$ 。        
第 $B+2...B+N+1$ 行：第 $B+i+1$ 行表示在第 $i$ 个牧场内所能监听到的总音量。
### 输出格式
共一行，即 $FJ$ 拥有的最小奶牛数量。

如果 FJ 不可能拥有一种牧场配置满足给出的条件，输出 `-1`。
### 说明/提示
#### 输入说明：
$FJ$ 拥有 $5$ 个牧场，每个牧场总音量从左到右分别为为$0、17、16、20、19$。 $FJ$ 有两种不同品种的奶牛；第一种奶牛的叫声音量是 $5$，第二种奶牛的叫声音量是 $7$ 。
#### 输出说明：
$2$ 号牧场场有  $2$ 头 $1$ 号品种的奶牛， $1$ 头 $2$ 号品种奶牛；还有一头牛在 $4$ 号牧场，共 $4$ 头奶牛。

## 说明/提示

INPUT DETAILS:


FJ owns 5 fields, with mooing volumes 0,17,16,20,19.  There are two breeds

of cows; the first moos at a volume of 5, and the other at a volume of 7.

OUTPUT DETAILS:


There are 2 cows of breed #1 and 1 cow of breed #2 in field 2, and there is

another cow of breed #1 in field 4.


Source: USACO 2014 March Contest, Silver


## 样例 #1

### 输入

```
5 2
5
7
0
17
16
20
19```

### 输出

```
4
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是先分离出每个牧场的实际音量，再利用完全背包求出每个音量对应的最少奶牛数，最后累加每个牧场实际音量对应的奶牛数得到结果。在实现过程中，都对不合法情况（如音量为负、音量无法由给定牛的音量组合得到）进行了特判。

### 所选题解
- **作者：Nuyoah_awa (赞：11)，4星**
    - **关键亮点**：思路清晰，代码简洁，对完全背包的运用和不合法情况的处理都很清晰。
- **作者：Gumbo (赞：2)，4星**
    - **关键亮点**：在代码实现上进行了一定优化，边读入边加入DP的考虑，并且对思路的解释较为清晰。
- **作者：__HHX__ (赞：1)，4星**
    - **关键亮点**：明确指出可以预处理，做到 $O(1)$ 回答，时间复杂度分析准确，代码规范。

### 重点代码
#### Nuyoah_awa的核心代码
```cpp
for(int i = 1;i <= b;i++)
{
    scanf("%d", &v[i]);
    for(int j = v[i];j <= N;j++)
        f[j] = min(f[j], f[j - v[i]] + 1);
}
for(int i = 1, x;i <= n;i++)
{
    scanf("%d", &x);
    x -= now, now += x;
    now -= now ? 1 : 0;
    if(x < 0)
    {
        printf("-1");
        return 0;
    }
    if(f[x] == INF)
    {
        printf("-1");
        return 0;
    }
    ans += f[x];
}
```
**核心实现思想**：先通过完全背包预处理出每个音量对应的最少奶牛数，再遍历每个牧场，分离出实际音量，判断是否合法，合法则累加最少奶牛数。

#### Gumbo的核心代码
```cpp
while(b--){
    scanf("%d",&u);
    for(int i=0;i<=100000;++i){
        f[i+u]=min(f[i+u],f[i]+1);
    }
}
int nw=0;
int ans=0;
while(n--){
    scanf("%d",&u);
    u-=nw;
    nw+=u;
    if(nw)--nw;
    if(u<0){
        printf("-1");
        return 0;
    }
    if(f[u]==0x3f3f3f3f){
        printf("-1");
        return 0;
    }
    ans+=f[u];
}
```
**核心实现思想**：边读入牛的音量边进行完全背包预处理，然后遍历每个牧场，分离实际音量，判断合法性，合法则累加最少奶牛数。

#### __HHX__的核心代码
```cpp
fill(dp + 1, dp + MaxN - 1, MaxN + 1);
for (int i = 1; i <= b; i++) {
    cin >> v[i];
}
for (int i = 1; i <= MaxN - 3; i++) {
    for (int j = 1; j <= b; j++) {
        if (i - v[j] >= 0) {
            dp[i] = min(dp[i - v[j]] + 1, dp[i]);
        }
    }
}
for (int i = 1, x, sum = 0; i <= n; i++) {
    cin >> x;
    if (x - sum < 0 || dp[x - sum] == MaxN + 1) {
        ans = -1;
        break;
    }
    ans += dp[x - sum] - 1, sum = max(x - 1, 0);
}
```
**核心实现思想**：先初始化DP数组，然后通过完全背包预处理，最后遍历每个牧场，分离实际音量，判断合法性，合法则累加最少奶牛数。

### 最优关键思路或技巧
- **完全背包预处理**：利用完全背包求出每个音量对应的最少奶牛数，避免重复计算。
- **预处理优化**：先预处理出所有可能的音量对应的最少奶牛数，后续可以 $O(1)$ 回答，提高效率。
- **不合法情况特判**：在遍历牧场时，对音量为负和音量无法由给定牛的音量组合得到的情况进行特判，避免错误结果。

### 可拓展之处
同类型题或类似算法套路：
- 其他背包问题变种，如多重背包、分组背包等，可通过改变状态转移方程和循环顺序来解决。
- 动态规划结合贪心的问题，先通过贪心策略简化问题，再用动态规划求解最优解。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的01背包问题。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题。
- [P1833 樱花](https://www.luogu.com.cn/problem/P1833)：混合背包问题，综合了01背包、完全背包和多重背包。

### 个人心得摘录与总结
- **lovely_hyzhuo**：提到用 memset 初始化在第三个 hack 数据过不去，但不清楚原因，提醒在初始化时要注意细节。
- **ztntonny**：指出要注意无方案的情况（音量为负），避免越界 RE，以及更新时要保证更新对象的可取性。 

---
处理用时：38.51秒