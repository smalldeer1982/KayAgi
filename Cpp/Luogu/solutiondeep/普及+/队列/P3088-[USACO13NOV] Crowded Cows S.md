# 题目信息

# [USACO13NOV] Crowded Cows S

## 题目描述

Farmer John's N cows (1 <= N <= 50,000) are grazing along a one-dimensional fence.  Cow i is standing at location x(i) and has height h(i) (1 <= x(i),h(i) <= 1,000,000,000).

A cow feels "crowded" if there is another cow at least twice her height within distance D on her left, and also another cow at least twice her height within distance D on her right (1 <= D <= 1,000,000,000).  Since crowded cows produce less milk, Farmer John would like to count the number of such cows.  Please help him.

FJ有 $N(1\le N\le50000)$ 头奶牛沿着一维的栅栏吃草，第 $i$ 头奶牛在目标点 $x_i$ ，它的身高是 $h_i (1 \le x_i,h_i\le10^9)$。

当一头奶牛左边 $D(1\le D\le10^9)$ 距离内且右边 $D$ 距离内有身高至少是它的两倍的奶牛，它就会觉得拥挤。

请计算觉得拥挤的奶牛的数量。


## 说明/提示

There are 6 cows, with a distance threshold of 4 for feeling crowded.  Cow #1 lives at position x=10 and has height h=3, and so on.


The cows at positions x=5 and x=6 are both crowded. 



## 样例 #1

### 输入

```
6 4 
10 3 
6 2 
5 3 
9 7 
3 6 
11 2 
```

### 输出

```
2 
```

# AI分析结果

### 综合分析与结论
本题主要求解在一维栅栏上满足特定拥挤条件的奶牛数量，关键在于高效找出每头奶牛左右距离 \( D \) 内身高至少为其两倍的奶牛。众多题解采用了不同算法，其中单调队列是主流方法，因其时间复杂度低且实现相对简单；也有部分题解使用线段树、平衡树、RMQ 等数据结构。

### 所选题解
- **作者：jzqjzq (赞：28)，4星**
    - **关键亮点**：思路清晰，详细阐述单调队列做法，时间复杂度为 \( O(n) \)，代码简洁易懂。
    - **核心代码**：
```cpp
struct ppap{
    int x,y;
}a[100001];
ppap qq[100001];
bool q[100001],h[100001];
inline bool cmp(ppap a,ppap b){return a.x<b.x;}
int main()
{
    int n,d;scanf("%d%d",&n,&d);
    for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=n;i++){
        while(l<=r&&qq[r].y<a[i].y)r--;
        qq[++r]=a[i];
        while(l<=r&&qq[l].x<a[i].x-d)l++;
        if(qq[l].y>=a[i].y*2)q[i]=1;
    }
    memset(qq,0,sizeof qq);l=1;r=0;
    for(int i=n;i;i--){
        while(l<=r&&qq[r].y<a[i].y)r--;
        qq[++r]=a[i];
        while(l<=r&&qq[l].x>a[i].x+d)l++;
        if(qq[l].y>=a[i].y*2)h[i]=1;
    }
    int ans=0;
    for(int i=1;i<=n;i++)if(q[i]&&h[i])ans++;
    printf("%d",ans);
    return 0;
}
```
    - **核心实现思想**：先按位置排序，然后用单调队列维护前面的合法最大值，再反向维护后面的合法最大值，最后统计左右都满足条件的奶牛数量。

- **作者：一只书虫仔 (赞：15)，4星**
    - **关键亮点**：详细解释思路和注意事项，对单调队列的使用说明清晰，代码规范。
    - **核心代码**：
```cpp
struct fjrtxdy {
    int x, h;
} a[50086];
bool fjrakioi (fjrtxdy fjr, fjrtxdy akioi) {
    return fjr.x < akioi.x;
}
deque <int> q;
deque <int> ind;
bool ans1[50086];
bool ans2[50086];
int main () {
    int n, d;
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].h);
    sort(a + 1, a + n + 1, fjrakioi);
    for (int i = 1; i <= n; i++) {
        while (!ind.empty() && a[ind.front()].x < a[i].x - d) {
            q.pop_front();
            ind.pop_front();
        }
        while (!q.empty()) {
            int tmp = q.back();
            if (tmp <= a[i].h) {
                q.pop_back();
                ind.pop_back();
            }
            else break;
        }
        q.push_back(a[i].h);
        ind.push_back(i);
        if (q.front() >= a[i].h * 2) ans1[i] = true;
    }
    q.clear(), ind.clear();
    for (int i = n; i >= 1; i--) {
        while (!ind.empty() && a[ind.front()].x > a[i].x + d) {
            q.pop_front();
            ind.pop_front();
        }
        while (!q.empty()) {
            int tmp = q.back();
            if (tmp <= a[i].h) {
                q.pop_back();
                ind.pop_back();
            }
            else break;
        }
        q.push_back(a[i].h);
        ind.push_back(i);
        if (q.front() >= a[i].h * 2) ans2[i] = true;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (ans1[i] && ans2[i])
            cnt++;
    printf("%d\n", cnt);
    return 0;
}
```
    - **核心实现思想**：同样先排序，利用双端队列维护单调队列，分别从左到右和从右到左遍历，标记满足条件的奶牛，最后统计数量。

### 最优关键思路或技巧
- **单调队列**：通过维护单调队列，保证队首元素为当前合法区间内的最大值，每个元素最多进队出队一次，时间复杂度为 \( O(n) \)。
- **两次遍历**：分别从左到右和从右到左遍历，判断每头奶牛左右两边是否满足条件。

### 可拓展之处
同类型题可考察在不同场景下的区间最值问题，如滑动窗口求最值、区间动态规划等。类似算法套路可用于解决其他需要维护区间信息的问题，如区间和、区间异或等。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)：经典的滑动窗口求最值问题，可使用单调队列解决。
2. [P1901 发射站](https://www.luogu.com.cn/problem/P1901)：与本题类似，需要维护区间内的最值信息。
3. [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)：二维的区间最值问题，可使用单调队列扩展到二维场景。

### 个人心得摘录与总结
- **作者：一只书虫仔**：教练 10min AC，帮其调试用了 1h。总结的小细节包括先双关键词对 \( x[i] \) 排序，缺少部分直接计算距离，注意计算距离的方向，以及 \( 2 \times a_i \) 要和最后单调队列跑完之后的队首比较等，提醒我们在实现单调队列时要注意细节，避免逻辑错误。

---
处理用时：42.13秒