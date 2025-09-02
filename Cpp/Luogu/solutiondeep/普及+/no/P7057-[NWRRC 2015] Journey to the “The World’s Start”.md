# 题目信息

# [NWRRC 2015] Journey to the “The World’s Start”

## 题目描述



Jerry Prince is the fourth grade student and he goes to New-Lodnon to visit the most popular amusement park `The World's Start`.

An airport he arrives at is next to the first stop of the metro line. This line has $n$ stops and `The World's Start` is on the last of them. The metro of New-Lodnon is pretty fast so you may assume that you can get from a stop to the next one in just one minute.

Jerry needs a travel card to use the metro. Each travel card has a range $r$ and a price $p$ . With a travel card of range $r$ Jerry may travel no more than $r$ stops at once. Therefore, if Jerry enters metro at the stop $i$ he should exit on one of the stops from $i − r$ to $i + r$ inclusive. It takes $d_{i}$ minutes to exit and reenter metro at i-th stop. There is no time required to enter the first stop or exit the last one.

Jerry is not very rich but he has some spare time, so he decided to buy the cheapest travel card that will allow him to travel from the first metro stop to the last one in no more than $t$ minutes.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
4 4
1 2 3
1 4
```

### 输出

```
2
```

# AI分析结果

### 算法分类
动态规划、二分

### 综合分析与结论
题目要求找到最便宜的车票，使得从第一个地铁站到最后一个地铁站的时间不超过给定时间。核心思路是通过二分查找确定最小的车票范围，然后利用动态规划计算在该范围内的最小时间。动态规划的转移方程涉及区间最小值，可以通过单调队列或线段树优化。

### 所选题解

#### 1. 作者：Your_Name (赞：2)
**星级：4星**
**关键亮点：**
- 使用二分查找确定最小车票范围，思路清晰。
- 动态规划转移方程简洁，利用单调队列优化区间最小值查询，时间复杂度低。
- 代码结构清晰，注释详细。

**核心代码：**
```cpp
bool check(LL x){
    q.clear();
    q.push_back(1);
    for(LL i = 2; i <= n; i ++){
        while(!q.empty() && q.front() < i - x)q.pop_front();
        f[i] = f[q.front()] + w[i];
        while(!q.empty() && f[q.back()] >= f[i])q.pop_back();
        q.push_back(i);
    }
    return f[n] <= t;
}
```
**实现思想：**
通过单调队列维护动态规划中的区间最小值，确保每次查询和更新的时间复杂度为O(1)。

#### 2. 作者：AFewSuns (赞：1)
**星级：4星**
**关键亮点：**
- 使用二分查找和线段树优化动态规划，思路清晰。
- 线段树实现区间最小值查询，代码结构合理。
- 详细解释了动态规划的转移方程和优化方法。

**核心代码：**
```cpp
bool chk(ll k){
    for(ll i=2;i<=n;i++){
        f[i]=query(1,1,n,max(1ll,i-k),i-1)+d[i];
        mdf(1,1,n,i,f[i]);
    }
    return f[n] <= t;
}
```
**实现思想：**
通过线段树维护动态规划中的区间最小值，确保每次查询和更新的时间复杂度为O(log n)。

#### 3. 作者：Mason123456 (赞：0)
**星级：4星**
**关键亮点：**
- 使用二分查找和单调队列优化动态规划，思路清晰。
- 单调队列实现区间最小值查询，代码简洁。
- 详细解释了动态规划的转移方程和优化方法。

**核心代码：**
```cpp
bool check(int k){
    hh = 1, tt = 0;
    que[++tt] = 1;
    for(int i = 2;i <= n;i++){
        while(hh <= tt && que[hh] < i - k)  hh++;
        f[i] = f[que[hh]] + d[i];
        while(hh <= tt && f[que[tt]] >= f[i])    tt--;
        que[++tt] = i;
    }
    return f[n] <= t;
}
```
**实现思想：**
通过单调队列维护动态规划中的区间最小值，确保每次查询和更新的时间复杂度为O(1)。

### 最优关键思路或技巧
1. **二分查找**：用于确定最小车票范围，减少搜索空间。
2. **动态规划**：用于计算在给定车票范围内的最小时间。
3. **单调队列/线段树优化**：用于高效查询区间最小值，优化动态规划的时间复杂度。

### 可拓展之处
类似的问题可以扩展到其他需要区间查询和优化的场景，如最短路径问题、区间最值问题等。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

### 个人心得摘录
- **Your_Name**：通过单调队列优化动态规划，减少了时间复杂度，代码简洁高效。
- **AFewSuns**：使用线段树优化动态规划，虽然代码稍复杂，但思路清晰，适合处理更大规模的数据。
- **Mason123456**：单调队列的实现简洁明了，适合快速解决区间最小值问题。

---
处理用时：22.49秒