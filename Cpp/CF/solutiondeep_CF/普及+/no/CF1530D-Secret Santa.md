# 题目信息

# Secret Santa

## 题目描述

Every December, VK traditionally holds an event for its employees named "Secret Santa". Here's how it happens.

 $ n $ employees numbered from $ 1 $ to $ n $ take part in the event. Each employee $ i $ is assigned a different employee $ b_i $ , to which employee $ i $ has to make a new year gift. Each employee is assigned to exactly one other employee, and nobody is assigned to themselves (but two employees may be assigned to each other). Formally, all $ b_i $ must be distinct integers between $ 1 $ and $ n $ , and for any $ i $ , $ b_i \ne i $ must hold.

The assignment is usually generated randomly. This year, as an experiment, all event participants have been asked who they wish to make a gift to. Each employee $ i $ has said that they wish to make a gift to employee $ a_i $ .

Find a valid assignment $ b $ that maximizes the number of fulfilled wishes of the employees.

## 说明/提示

In the first test case, two valid assignments exist: $ [3, 1, 2] $ and $ [2, 3, 1] $ . The former assignment fulfills two wishes, while the latter assignment fulfills only one. Therefore, $ k = 2 $ , and the only correct answer is $ [3, 1, 2] $ .

## 样例 #1

### 输入

```
2
3
2 1 2
7
6 4 6 2 4 5 6```

### 输出

```
2
3 1 2
4
6 4 7 2 3 5 1```

# AI分析结果

### 题目翻译
# 秘密圣诞老人

## 题目描述
每年12月，VK公司传统上都会为员工举办一个名为“秘密圣诞老人”的活动。活动流程如下：

有 $n$ 名员工，编号从 $1$ 到 $n$ 参加此次活动。每个员工 $i$ 会被分配到另一个不同的员工 $b_i$，员工 $i$ 需要给员工 $b_i$ 准备一份新年礼物。每位员工只会被分配到另一名员工，且不能分配到自己（但两名员工可以互相分配）。形式上，所有的 $b_i$ 必须是 $1$ 到 $n$ 之间的不同整数，并且对于任意的 $i$，都有 $b_i \ne i$ 。

分配通常是随机生成的。今年，作为一项实验，所有活动参与者都被询问了他们想给谁送礼物。每个员工 $i$ 都表示希望给员工 $a_i$ 送礼物。

请找到一种有效的分配方案 $b$，使得满足员工愿望的数量最大化。

## 说明/提示
在第一个测试用例中，存在两种有效的分配方案：$ [3, 1, 2] $ 和 $ [2, 3, 1] $ 。前一种方案满足两个愿望，而后一种方案只满足一个愿望。因此，$ k = 2 $ ，唯一正确的答案是 $ [3, 1, 2] $ 。

## 样例 #1
### 输入
```
2
3
2 1 2
7
6 4 6 2 4 5 6
```
### 输出
```
2
3 1 2
4
6 4 7 2 3 5 1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先尽量满足员工的愿望，当出现冲突时，采用一定的策略进行调整，以保证每个人都能收到礼物且不会送给自己，同时最大化满足愿望的数量。
- **思路对比**：大部分题解都是先统计每个人被希望送礼物的情况，对于没有冲突的直接满足愿望，有冲突的进行调整；部分题解从图论的角度出发，将问题转化为图的环结构来处理。
- **算法要点**：主要包括统计入度、记录未收到礼物的人、处理自环情况等。
- **解决难点**：主要难点在于处理冲突和自环情况，不同题解采用了不同的策略，如交换礼物、调整分配等。

### 所选题解
- **jiayixuan1205（4星）**
    - **关键亮点**：思路清晰，通过入度的概念来理解和处理问题，代码实现简洁易懂。
- **Vii_Truly（4星）**
    - **关键亮点**：通过具体例子详细解释了处理自环的方法，便于理解。
- **Tiago（4星）**
    - **关键亮点**：对处理冲突和自环的思路进行了详细的文字说明，逻辑清晰。

### 重点代码
#### jiayixuan1205
```cpp
for(int i=1;i<=n;i++)
{
    cin>>a[i];
    in[a[i]]++;//入度++ 
    mp[a[i]]=i;
}
for(int i=1;i<=n;i++)
{
    if(!in[i]) v.push_back(i);//如果这个人没有礼物收 
}
for(int i=1;i<=n;i++)
{
    if(in[a[i]]==1)//如果刚好这个人能收到一份礼物 
    {
        cnt++;//无需改动 
        ans[i]=a[i];//不产生冲突，直接让这个人如愿， 
    }
    else
    {
        ans[i]=v.back();//如果一个人有很多礼物收，把礼物匀给没有礼物收的人 
        in[a[i]]--;//分完礼物后入度-- 
        v.pop_back();//收到礼物后出队 
    }
}
for(int i=1;i<=n;i++)
{
    if(i==ans[i])//如果礼物送给了自己 
    {
        ans[i]=a[i];
        ans[mp[a[i]]]=i;//让他把礼物送给原本想送的人 
        mp[a[i]]=i;//交换礼物 
    }
}
```
**核心实现思想**：先统计每个人的入度和未收到礼物的人，对于入度为1的直接满足愿望，入度大于1的将礼物匀给未收到礼物的人，最后处理自环情况。

#### Vii_Truly
```cpp
for (int i = 1;i <= n; i++) {
    scanf("%d", &p[i]);
    st[p[i]]++; //想要给 p[i] 送礼物的人数
    mp[p[i]] = i; //最后一个想要给p[i] 送礼的人的编号
}
for (int i = 1;i <= n; i++) if (!st[i]) v.push_back(i);//没有人想要给i送礼物
for (int i = 1;i <= n; i++) {
    if (st[p[i]] == 1) ans[i] = p[i], cnt++; //没有人和i争了，那就让i如愿以偿
    else { //有多个人想要给p[i]送，那就让i送给那些没有礼物收的人
        ans[i] = v.back();
        st[p[i]]--;
        v.pop_back();
    }
}
for (int i = 1;i <= n; i++) {
    if (i == ans[i]) { //出现了自己送给自己
        ans[i] = p[i]; //满足这个人的想法
        ans[mp[p[i]]] = i; //让原本送给p[i]的那个人将礼物送给i
        mp[p[i]] = i;
    }
}
```
**核心实现思想**：统计每个人想送礼物的情况和未收到礼物的人，对于无冲突的满足愿望，有冲突的调整分配，最后处理自环。

#### Tiago
```cpp
For(i,1,n)cin>>a[i],in[a[i]]++,t[a[i]]=i;
same[0]=0;
For(i,1,n)if(in[i]==0)same[++same[0]]=i;
sum=0;
For(i,1,n)
    if(in[a[i]]==1)ans[i]=a[i],sum++;
    elif(in[a[i]]!=0)
    {
        ans[i]=same[same[0]--];
        in[a[i]]--;
    }
For(i,1,n)
    if(ans[i]==i)
    {
        ans[i]=a[i];
        ans[t[a[i]]]=i;
        t[a[i]]=i;
    }
```
**核心实现思想**：统计入度和未收到礼物的人，对于入度为1的满足愿望，入度大于1的调整分配，最后处理自环。

### 最优关键思路或技巧
- 使用入度的概念来统计每个人被希望送礼物的情况，便于处理冲突。
- 对于自环情况，通过交换礼物的方式进行调整，保证满足条件。

### 可拓展之处
同类型题可能会有更多的限制条件，如礼物的价值、员工之间的关系等。类似算法套路可以应用于资源分配、任务调度等问题，核心思路都是先尽量满足需求，再处理冲突。

### 推荐题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得
无

---
处理用时：54.20秒