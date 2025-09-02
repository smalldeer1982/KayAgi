# 题目信息

# Holidays

## 题目描述

School holidays come in Berland. The holidays are going to continue for $ n $ days. The students of school № $ N $ are having the time of their lives and the IT teacher Marina Sergeyevna, who has spent all the summer busy checking the BSE (Berland State Examination) results, has finally taken a vacation break! Some people are in charge of the daily watering of flowers in shifts according to the schedule. However when Marina Sergeyevna was making the schedule, she was so tired from work and so lost in dreams of the oncoming vacation that she perhaps made several mistakes. In fact, it is possible that according to the schedule, on some days during the holidays the flowers will not be watered or will be watered multiple times. Help Marina Sergeyevna to find a mistake.

## 说明/提示

Keep in mind that in the second sample the mistake occurs not only on the second day, but also on the sixth day, when nobody waters the flowers. However, you have to print the second day, i.e. the day with the minimal number.

## 样例 #1

### 输入

```
10 5
1 2
3 3
4 6
7 7
8 10
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
10 5
1 2
2 3
4 5
7 8
9 10
```

### 输出

```
2 2
```

## 样例 #3

### 输入

```
10 5
1 2
3 3
5 7
7 7
7 10
```

### 输出

```
4 0
```

# AI分析结果

【题目内容中文重写】
# 假期

## 题目描述

在Berland，学校假期即将到来，假期将持续$n$天。学校№$N$的学生们正在享受他们的美好时光，而IT老师Marina Sergeyevna在忙碌了整个夏天检查BSE（Berland国家考试）成绩后，终于迎来了她的假期！一些人按照轮班表负责每天浇花。然而，当Marina Sergeyevna制定这个轮班表时，她因工作疲惫且沉浸在即将到来的假期梦想中，可能犯了一些错误。事实上，根据这个轮班表，假期中的某些天花可能没有被浇水，或者被多次浇水。帮助Marina Sergeyevna找出错误。

## 说明/提示

请注意，在第二个样例中，错误不仅发生在第二天，还发生在第六天，那天没有人浇花。然而，你需要输出第二天，即编号最小的那一天。

## 样例 #1

### 输入

```
10 5
1 2
3 3
4 6
7 7
8 10
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
10 5
1 2
2 3
4 5
7 8
9 10
```

### 输出

```
2 2
```

## 样例 #3

### 输入

```
10 5
1 2
3 3
5 7
7 7
7 10
```

### 输出

```
4 0
```

【题解分析与结论】
本题的核心是检查在$n$天内，每天是否恰好被浇水一次。多个题解采用了不同的方法，包括模拟、差分、树状数组等。以下是对各题解的简要分析与评分：

1. **模拟法**（作者：songxiao，赞：11）
   - **评分：4星**
   - **关键亮点**：直接模拟每天浇水次数，思路清晰，代码简洁。
   - **核心代码**：
     ```cpp
     int x[n]={0};
     for(int i=0;i<m;i++) {
         cin>>a>>b;
         for(int i=a-1;i<b;i++) x[i]++;
     }
     for(int i=0;i<n;i++) {
         if(x[i]!=1) {
             cout<<i+1<<' '<<x[i];
             return 0;
         }
     }
     cout<<"OK";
     ```
   - **个人心得**：无需复杂数据结构，直接模拟即可。

2. **差分法**（作者：ziiidan，赞：9）
   - **评分：4星**
   - **关键亮点**：利用差分数组优化区间修改，时间复杂度低。
   - **核心代码**：
     ```cpp
     for(register int i = 1; i <= m; i++) {
         fr = read(); to = read();
         c[fr]++; c[to + 1]--;
     }
     for(register int i = 1; i <= n; i++) {
         c[i] = c[i - 1] + c[i];
         if(c[i] == 0 || c[i] > 1) {
             cout << i << ' ' << c[i] << '\n';
             return 0;
         }
     }
     cout << "OK" << '\n';
     ```
   - **个人心得**：差分法适用于区间修改问题，代码简洁高效。

3. **树状数组**（作者：曼恩薄荷，赞：4）
   - **评分：3星**
   - **关键亮点**：使用树状数组实现区间修改和单点查询，代码量较大但思路清晰。
   - **核心代码**：
     ```cpp
     void add(int x,int v) {
         while(x<=n) {
             tree[x] += v;
             x += lowbit(x);
         }
     }
     int sum(int x) {
         int ret = 0;
         while(x != 0) {
             ret += tree[x];
             x -= lowbit(x);
         }
         return ret;
     }
     ```
   - **个人心得**：树状数组适用于更复杂的区间操作，但本题中略显复杂。

【最优关键思路】
- **模拟法**：直接模拟每天浇水次数，适用于数据范围较小的情况，代码简洁易理解。
- **差分法**：利用差分数组优化区间修改，适用于数据范围较大的情况，时间复杂度低。

【拓展思路】
- 类似问题：区间修改、单点查询问题，如洛谷P3372（线段树模板题）、P3368（树状数组模板题）、P3374（树状数组模板题）。

【推荐题目】
1. 洛谷P3372 【模板】线段树 1
2. 洛谷P3368 【模板】树状数组 1
3. 洛谷P3374 【模板】树状数组 2

---
处理用时：43.12秒