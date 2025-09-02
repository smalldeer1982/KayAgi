# 题目信息

# Three Sevens

## 题目描述

Lottery "Three Sevens" was held for $ m $ days. On day $ i $ , $ n_i $ people with the numbers $ a_{i, 1}, \ldots, a_{i, n_i} $ participated in the lottery.

It is known that in each of the $ m $ days, only one winner was selected from the lottery participants. The lottery winner on day $ i $ was not allowed to participate in the lottery in the days from $ i+1 $ to $ m $ .

Unfortunately, the information about the lottery winners has been lost. You need to find any possible list of lottery winners on days from $ 1 $ to $ m $ or determine that no solution exists.

## 说明/提示

In the first test case, one of the answers is $ [8, 2, 1] $ since the participant with the number $ 8 $ participated on day $ 1 $ , but did not participate on days $ 2 $ and $ 3 $ ; the participant with the number $ 2 $ participated on day $ 2 $ , but did not participate on day $ 3 $ ; and the participant with the number $ 1 $ participated on day $ 3 $ . Note that this is not the only possible answer, for example, $ [8, 9, 4] $ is also a correct answer.

In the second test case, both lottery participants participated on both days, so any possible lottery winner on the day $ 1 $ must have participated on the day $ 2 $ , which is not allowed. Thus, there is no correct answer.

In the third test case, only one participant participated on days $ 2 $ , $ 3 $ , $ 4 $ , and on day $ 1 $ there is only one participant who did not participate in the lottery on days $ 2, 3, 4 $ — participant $ 2 $ , which means $ [2, 1, 4, 3] $ is the only correct answer to this test case.

## 样例 #1

### 输入

```
3
3
4
1 2 4 8
3
2 9 1
2
1 4
2
2
1 2
2
2 1
4
4
1 2 3 4
1
1
1
4
1
3```

### 输出

```
8 2 1 
-1
2 1 4 3```

# AI分析结果

### 题目内容重写

#### 题目描述

彩票活动“Three Sevens”持续了 $m$ 天。在第 $i$ 天，有 $n_i$ 个人参与彩票活动，他们的编号分别为 $a_{i, 1}, \ldots, a_{i, n_i}$。

已知在每一天的彩票活动中，只有一位中奖者被选出。第 $i$ 天的中奖者不能在之后的天数（即从 $i+1$ 到 $m$ 天）中再次参与彩票活动。

不幸的是，关于中奖者的信息已经丢失。你需要找出从第 $1$ 天到第 $m$ 天的任何可能的中奖者列表，或者确定不存在这样的解。

#### 说明/提示

在第一个测试用例中，其中一个答案是 $[8, 2, 1]$，因为编号为 $8$ 的参与者只在第 $1$ 天参与，没有在第 $2$ 天和第 $3$ 天参与；编号为 $2$ 的参与者只在第 $2$ 天参与，没有在第 $3$ 天参与；编号为 $1$ 的参与者只在第 $3$ 天参与。注意，这并不是唯一的正确答案，例如 $[8, 9, 4]$ 也是一个正确的答案。

在第二个测试用例中，两位彩票参与者都在两天都参与了，因此第 $1$ 天的中奖者必须也在第 $2$ 天参与，这是不允许的。因此，没有正确的答案。

在第三个测试用例中，只有一位参与者参与了第 $2$、$3$、$4$ 天的活动，而在第 $1$ 天只有一位参与者没有在第 $2$、$3$、$4$ 天参与——参与者 $2$，因此 $[2, 1, 4, 3]$ 是这个测试用例的唯一正确答案。

### 算法分类
构造

### 题解分析与结论

这道题的核心思路是通过记录每个人最后一次参与彩票的天数，然后根据这些信息构造出每天的中奖者。如果某一天没有人在这一天最后一次参与彩票，则无解。

#### 关键思路
1. **记录最后一次参与的天数**：使用一个数组或哈希表记录每个人最后一次参与彩票的天数。
2. **构造中奖者列表**：遍历每一天，选择在这一天最后一次参与彩票的人作为中奖者。
3. **判断无解情况**：如果某一天没有人在这一天最后一次参与彩票，则输出 `-1`。

### 评分较高的题解

#### 题解1：EdenSky (5星)
**关键亮点**：
- 使用 `unordered_map` 记录每个人最后一次参与的天数，避免了数组的局限性。
- 通过 `day` 数组记录每一天的中奖者，简洁高效。
- 代码清晰，逻辑严谨。

**核心代码**：
```cpp
unordered_map<int,int> last;
int day[N];
for(int i=1;i<=m;i++){
    cin>>n;
    for(int j=1;j<=n;j++)
        cin>>a,last[a]=i;
}
for(auto &i: last){
    if(!day[i.second]) M--;
    day[i.second]=i.first;
}
if(M) cout<<-1;
else for(int i=1;i<=m;i++) cout<<day[i]<<' ';
```

#### 题解2：Larryyu (4星)
**关键亮点**：
- 使用 `vector` 存储每天的参与者，避免了数组空间不足的问题。
- 通过 `last` 数组记录每个人最后一次参与的天数，逻辑清晰。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
vector<int> a[500500];
int last[50050],ans[50050];
for(int i=1;i<=m;i++){
    int n=read();
    for(int j=1;j<=n;j++){
        int x=read();
        a[i].emplace_back(x);
        last[x]=max(last[x],i);
    }
}
for(int i=1;i<=m;i++){
    bool f=0;
    for(int j=0;j<a[i].size();j++){
        if(last[a[i][j]]==i){
            f=1;
            ans[i]=a[i][j];
            break;
        }
    }
    if(f==0){
        cout<<-1<<endl;
        return;
    }
}
```

#### 题解3：AzureHair (4星)
**关键亮点**：
- 使用 `vis` 数组记录每一天的中奖者，逻辑简洁。
- 通过 `a` 数组记录每个人最后一次参与的天数，代码清晰。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
int a[50010],vis[50010];
for(int i=1;i<=m;i++){
    n=read();
    for(int j=1;j<=n;j++){
        int x=read();
        a[x]=i;
    }
}
for(int j=1;j<=50000;j++)
    if(a[j])
        vis[a[j]]=j;
bool flag=0;
for(int j=1;j<=m;j++){
    if(!vis[j]){
        flag=1;
        break;
    }
}
if(flag)
    cout<<-1<<endl;
else{
    for(int j=1;j<=m;j++)
        cout<<vis[j]<<' ';
    cout<<endl;
}
```

### 最优关键思路
使用哈希表或数组记录每个人最后一次参与彩票的天数，然后根据这些信息构造出每天的中奖者。如果某一天没有人在这一天最后一次参与彩票，则无解。

### 可拓展之处
类似的问题可以通过记录最后一次出现的时间或位置来解决，例如在字符串处理中查找某个字符的最后出现位置。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
3. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)

### 个人心得摘录
- **EdenSky**：使用 `unordered_map` 替代数组，避免了数组的局限性，代码更加简洁。
- **Larryyu**：使用 `vector` 存储参与者，避免了数组空间不足的问题，逻辑清晰。
- **AzureHair**：通过 `vis` 数组记录每一天的中奖者，逻辑简洁，代码易于理解。

---
处理用时：41.34秒