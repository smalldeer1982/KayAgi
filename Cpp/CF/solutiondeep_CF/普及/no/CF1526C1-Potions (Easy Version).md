# 题目信息

# Potions (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ n \leq 2000 $ . You can make hacks only if both versions of the problem are solved.

There are $ n $ potions in a line, with potion $ 1 $ on the far left and potion $ n $ on the far right. Each potion will increase your health by $ a_i $ when drunk. $ a_i $ can be negative, meaning that potion will decrease will health.

You start with $ 0 $ health and you will walk from left to right, from first potion to the last one. At each potion, you may choose to drink it or ignore it. You must ensure that your health is always non-negative.

What is the largest number of potions you can drink?

## 说明/提示

For the sample, you can drink $ 5 $ potions by taking potions $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ and $ 6 $ . It is not possible to drink all $ 6 $ potions because your health will go negative at some point

## 样例 #1

### 输入

```
6
4 -4 1 -3 1 -3```

### 输出

```
5```

# AI分析结果

### 题目内容重写
#### 题目描述
这是问题的简单版本。唯一的区别是在这个版本中 $n \leq 2000$。只有当两个版本的问题都解决时，你才能进行hack。

有 $n$ 瓶药水排成一行，第 $1$ 瓶在最左边，第 $n$ 瓶在最右边。每瓶药水在喝下后会增加你的健康值 $a_i$。$a_i$ 可以是负数，意味着这瓶药水会减少你的健康值。

你从 $0$ 健康值开始，从左到右依次走过每一瓶药水。在每瓶药水前，你可以选择喝下它或忽略它。你必须确保你的健康值始终非负。

你能喝下的最多药水数量是多少？

#### 说明/提示
对于样例，你可以喝下 $5$ 瓶药水，选择第 $1$、$3$、$4$、$5$ 和 $6$ 瓶。不可能喝下所有 $6$ 瓶药水，因为你的健康值会在某个时刻变为负数。

#### 样例 #1
##### 输入
```
6
4 -4 1 -3 1 -3
```
##### 输出
```
5
```

### 算法分类
贪心

### 题解分析与结论
本题的核心是贪心算法，通过优先队列（堆）来动态调整选择喝下的药水，确保健康值始终非负。大部分题解都采用了贪心+优先队列的思路，时间复杂度为 $O(n \log n)$，适合本题的数据范围。

### 评分较高的题解
#### 1. 作者：Hilte (5星)
**关键亮点**：
- 使用优先队列（小根堆）来动态调整选择喝下的药水。
- 代码简洁，思路清晰，时间复杂度为 $O(n \log n)$。

**核心代码**：
```cpp
priority_queue<ll,vector<ll>,greater<ll> > q;
ll a[200001];

int main() {
    ll n, cur=1, ans=0, tot=0;
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
    ans=n;
    while(cur<=n) {
        tot+=a[cur];
        q.push(a[cur]);
        if(tot<0) {
            tot-=q.top();
            q.pop();
            ans--;
        }
        cur++;
    }
    printf("%lld\n",ans);
    return 0;
}
```

#### 2. 作者：cwd2023 (4星)
**关键亮点**：
- 详细解释了贪心策略，特别是当健康值变为负数时的反悔机制。
- 代码注释详细，适合新手理解。

**核心代码**：
```cpp
priority_queue<ll,vector<ll>,greater<ll> > q;
ll a[200010];

int main() {
    ios::sync_with_stdio(0);
    cout.tie(0),cin.tie(0);
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>a[i];
    for(ll i=1;i<=n;i++) {
        cur+=a[i],q.push(a[i]),ans++;
        if(cur<0) cur-=q.top(),q.pop(),ans--;
    }
    cout<<ans;
    return 0;
}
```

#### 3. 作者：_xxxxx_ (4星)
**关键亮点**：
- 提供了贪心和DP两种解法，适合不同需求的读者。
- 代码实现清晰，特别是贪心部分的优先队列使用。

**核心代码**：
```cpp
priority_queue<int> p;
int a[N];

signed main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int now = 0, ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] >= 0) {
            now += a[i];
            ans++;
            continue;
        }
        now += a[i];
        ans++;
        p.push(-a[i]);
        if(now < 0) {
            now += p.top();
            p.pop();
            ans--;
        }
    }
    cout << ans << endl;
    return 0;
}
```

### 最优关键思路
使用优先队列（小根堆）来动态调整选择喝下的药水，当健康值变为负数时，将最小的药水（即对健康值影响最大的负数）从队列中移除，以确保健康值始终非负。

### 可拓展之处
类似的问题可以在需要动态调整选择的情况下使用贪心+优先队列的策略，例如在资源分配、任务调度等问题中。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

### 个人心得摘录
- **Hilte**：通过优先队列动态调整选择，确保健康值始终非负，代码简洁高效。
- **cwd2023**：详细解释了贪心策略，特别是当健康值变为负数时的反悔机制，适合新手理解。
- **_xxxxx_**：提供了贪心和DP两种解法，适合不同需求的读者，代码实现清晰。

---
处理用时：30.75秒