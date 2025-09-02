# 题目信息

# TV Subscriptions (Hard Version)

## 题目描述

The only difference between easy and hard versions is constraints.

The BerTV channel every day broadcasts one episode of one of the $ k $ TV shows. You know the schedule for the next $ n $ days: a sequence of integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le k $ ), where $ a_i $ is the show, the episode of which will be shown in $ i $ -th day.

The subscription to the show is bought for the entire show (i.e. for all its episodes), for each show the subscription is bought separately.

How many minimum subscriptions do you need to buy in order to have the opportunity to watch episodes of purchased shows $ d $ ( $ 1 \le d \le n $ ) days in a row? In other words, you want to buy the minimum number of TV shows so that there is some segment of $ d $ consecutive days in which all episodes belong to the purchased shows.

## 说明/提示

In the first test case to have an opportunity to watch shows for two consecutive days, you need to buy a subscription on show $ 1 $ and on show $ 2 $ . So the answer is two.

In the second test case, you can buy a subscription to any show because for each show you can find a segment of three consecutive days, consisting only of episodes of this show.

In the third test case in the unique segment of four days, you have four different shows, so you need to buy a subscription to all these four shows.

In the fourth test case, you can buy subscriptions to shows $ 3,5,7,8,9 $ , and you will be able to watch shows for the last eight days.

## 样例 #1

### 输入

```
4
5 2 2
1 2 1 2 1
9 3 3
3 3 3 2 2 2 1 1 1
4 10 4
10 8 6 4
16 9 8
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3
```

### 输出

```
2
1
4
5
```

# AI分析结果

### 题目内容重写

#### TV Subscriptions (Hard Version)

#### 题目描述

简单版本和困难版本之间的唯一区别是约束条件。

BerTV频道每天播出一集$k$个电视节目中的一个。你知道接下来$n$天的节目安排：一个整数序列$a_1, a_2, \dots, a_n$（$1 \le a_i \le k$），其中$a_i$表示第$i$天播出的节目。

订阅某个节目后，可以观看该节目的所有剧集，每个节目的订阅是独立的。

为了能够连续观看$d$天（$1 \le d \le n$）的节目，你需要购买最少多少个节目的订阅？换句话说，你需要购买最少数量的电视节目，使得存在一段连续的$d$天，所有播出的节目都属于你购买的节目。

#### 说明/提示

在第一个测试用例中，为了能够连续观看两天的节目，你需要购买节目$1$和节目$2$的订阅，因此答案是$2$。

在第二个测试用例中，你可以购买任意一个节目的订阅，因为对于每个节目，你都可以找到一段连续的三天，所有播出的节目都属于该节目。

在第三个测试用例中，在唯一的四天时间段内，有四个不同的节目，因此你需要购买所有这四个节目的订阅。

在第四个测试用例中，你可以购买节目$3,5,7,8,9$的订阅，这样你就可以连续观看最后八天的节目。

#### 样例 #1

##### 输入

```
4
5 2 2
1 2 1 2 1
9 3 3
3 3 3 2 2 2 1 1 1
4 10 4
10 8 6 4
16 9 8
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3
```

##### 输出

```
2
1
4
5
```

### 算法分类
滑动窗口

### 题解分析与结论

本题的核心是找到一段连续的$d$天，使得这段区间内的不同节目数量最少。由于数据范围较大，直接暴力枚举会超时，因此需要优化。大多数题解采用了滑动窗口的思路，通过维护一个窗口内的节目种类数来高效求解。

### 所选高星题解

#### 题解1：Meatherm (5星)

**关键亮点：**
- 使用滑动窗口优化，时间复杂度为$O(n)$。
- 通过维护$cnt$数组和$sum$变量来统计窗口内的不同节目数量。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
inline void add(int x){
    if(!sum[a[x]])
        ++cnt;
    ++sum[a[x]];	
    return;
}
inline void del(int x){
    --sum[a[x]];
    if(!sum[a[x]])
        --cnt;
    return;	
}
int main(void){
    scanf("%d",&T);
    while(T--){
        memset(sum,0,sizeof(sum));
        cnt=0;
        scanf("%d%d%d",&n,&k,&d);
        for(rr int i=1;i<=n;++i){
            scanf("%d",&a[i]);
        }
        for(rr int i=1;i<=d;++i)
            add(i);
        ans=cnt;
        for(rr int i=d+1;i<=n;++i){
            del(i-d);
            add(i);		
            ans=std::min(ans,cnt);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

#### 题解2：杨铠远 (4星)

**关键亮点：**
- 使用滑动窗口和队列维护窗口内的节目种类数。
- 代码实现较为直观，适合初学者理解。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    t[a[i]]++;
    q[++tail]=i;
    if(t[a[i]]==1)sum++;
    while(head<=tail&&i-q[head]>=d){
        t[a[q[head]]]--;if(t[a[q[head]]]==0)sum--;head++;
    }
    if(i-q[head]+1>=d)ans=min(ans,sum);
}
```

#### 题解3：傅思维666 (4星)

**关键亮点：**
- 滑动窗口的经典应用，通过维护$cnt$数组和$sum$变量来统计窗口内的不同节目数量。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
for(int i=1;i<=d;i++){
    if(!cnt[a[i]])
        sum++;
    cnt[a[i]]++;
}
ans=sum;
for(int i=d+1;i<=n;i++){
    cnt[a[i-d]]--;
    if(!cnt[a[i-d]])
        sum--;
    if(!cnt[a[i]])
        sum++;
    cnt[a[i]]++;
    ans=min(ans,sum);
}
```

### 最优关键思路或技巧
- **滑动窗口**：通过维护一个固定大小的窗口，高效地统计窗口内的不同元素数量。
- **维护$cnt$数组**：记录每个元素在当前窗口内的出现次数，通过$sum$变量统计不同元素的数量。

### 可拓展之处
- 类似的问题可以使用滑动窗口来解决，如统计区间内满足某些条件的最小/最大值。
- 滑动窗口也可以用于解决字符串匹配、最长无重复子串等问题。

### 推荐题目
1. [P1972 HH的项链](https://www.luogu.com.cn/problem/P1972)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)

---
处理用时：37.72秒