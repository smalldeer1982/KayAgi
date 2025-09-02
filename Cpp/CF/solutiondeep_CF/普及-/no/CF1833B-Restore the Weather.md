# 题目信息

# Restore the Weather

## 题目描述

You are given an array $ a $ containing the weather forecast for Berlandia for the last $ n $ days. That is, $ a_i $ — is the estimated air temperature on day $ i $ ( $ 1 \le i \le n $ ).

You are also given an array $ b $ — the air temperature that was actually present on each of the days. However, all the values in array $ b $ are mixed up.

Determine which day was which temperature, if you know that the weather never differs from the forecast by more than $ k $ degrees. In other words, if on day $ i $ the real air temperature was $ c $ , then the equality $ |a_i - c| \le k $ is always true.

For example, let an array $ a $ = \[ $ 1, 3, 5, 3, 9 $ \] of length $ n = 5 $ and $ k = 2 $ be given and an array $ b $ = \[ $ 2, 5, 11, 2, 4 $ \]. Then, so that the value of $ b_i $ corresponds to the air temperature on day $ i $ , we can rearrange the elements of the array $ b $ so: \[ $ 2, 2, 5, 4, 11 $ \]. Indeed:

- On the $ 1 $ st day, $ |a_1 - b_1| = |1 - 2| = 1 $ , $ 1 \le 2 = k $ is satisfied;
- On the $ 2 $ nd day $ |a_2 - b_2| = |3 - 2| = 1 $ , $ 1 \le 2 = k $ is satisfied;
- On the $ 3 $ rd day, $ |a_3 - b_3| = |5 - 5| = 0 $ , $ 0 \le 2 = k $ is satisfied;
- On the $ 4 $ th day, $ |a_4 - b_4| = |3 - 4| = 1 $ , $ 1 \le 2 = k $ is satisfied;
- On the $ 5 $ th day, $ |a_5 - b_5| = |9 - 11| = 2 $ , $ 2 \le 2 = k $ is satisfied.

## 样例 #1

### 输入

```
3
5 2
1 3 5 3 9
2 5 11 2 4
6 1
-1 3 -2 0 -5 -1
-4 0 -1 4 0 0
3 3
7 7 7
9 4 8```

### 输出

```
2 2 5 4 11
0 4 -1 0 -4 0
8 4 9```

# AI分析结果

### 题目翻译
# 恢复天气

## 题目描述
给定一个数组 $a$，它包含了 Berlandia 过去 $n$ 天的天气预报。也就是说，$a_i$ 是第 $i$ 天（$1 \le i \le n$）的预计气温。

同时，还给定了一个数组 $b$，它表示每天实际出现的气温。然而，数组 $b$ 中的所有值都是打乱的。

如果你知道实际天气与预报的温差从不超过 $k$ 度，即如果第 $i$ 天的实际气温为 $c$，那么等式 $|a_i - c| \le k$ 总是成立，请确定每一天对应的实际气温。

例如，给定一个长度 $n = 5$ 的数组 $a = [1, 3, 5, 3, 9]$，$k = 2$，以及数组 $b = [2, 5, 11, 2, 4]$。那么，为了使 $b_i$ 对应第 $i$ 天的实际气温，我们可以将数组 $b$ 重新排列为 $[2, 2, 5, 4, 11]$。实际上：
- 在第 $1$ 天，$|a_1 - b_1| = |1 - 2| = 1$，满足 $1 \le 2 = k$；
- 在第 $2$ 天，$|a_2 - b_2| = |3 - 2| = 1$，满足 $1 \le 2 = k$；
- 在第 $3$ 天，$|a_3 - b_3| = |5 - 5| = 0$，满足 $0 \le 2 = k$；
- 在第 $4$ 天，$|a_4 - b_4| = |3 - 4| = 1$，满足 $1 \le 2 = k$；
- 在第 $5$ 天，$|a_5 - b_5| = |9 - 11| = 2$，满足 $2 \le 2 = k$。

## 样例 #1
### 输入
```
3
5 2
1 3 5 3 9
2 5 11 2 4
6 1
-1 3 -2 0 -5 -1
-4 0 -1 4 0 0
3 3
7 7 7
9 4 8
```

### 输出
```
2 2 5 4 11
0 4 -1 0 -4 0
8 4 9
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路一致，都利用贪心思想，认为在保证有解的情况下，让 $|a_i - b_i|$ 尽可能小就能满足 $|a_i - b_i| \le k$。具体做法是将数组 $a$ 和 $b$ 排序，使它们对应位置的元素差值最小。由于最终要按 $a$ 的原顺序输出 $b$ 数组，所以需要用结构体或数组记录 $a$ 中元素的原始编号。

### 所选题解
- **作者：Coffee_zzz (赞：6)，4星**
    - **关键亮点**：思路清晰，详细解释了为何可以忽略 $|a_i - b_i| \le k$ 这个条件，代码中使用了快速读入优化，提高了输入效率。
- **作者：Furina_Hate_Comma (赞：2)，4星**
    - **关键亮点**：代码简洁，直接点明这是一个典型的贪心思路，逻辑清晰易懂。
- **作者：EmptyAlien (赞：0)，4星**
    - **关键亮点**：对思路的解释详细，从题目条件逐步推导出贪心策略，代码使用了 `vector` 容器，实现较为规范。

### 重点代码
#### Coffee_zzz 的代码
```c++
struct Nod{
    int id,val;
}a[N];
bool cmp(Nod a,Nod b){
    return a.val<b.val;
}
void solve(){
    int n=read(),k=read();
    for(int i=1;i<=n;i++) a[i].val=read(),a[i].id=i;
    for(int i=1;i<=n;i++) b[i]=read();
    sort(b+1,b+1+n);
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        tmp[a[i].id]=b[i];
    }
    for(int i=1;i<=n;i++) cout<<tmp[i]<<' ';
    cout<<'\n';
}
```
**核心实现思想**：用结构体 `Nod` 存储数组 $a$ 的元素及其原始编号，对 $a$ 按元素值排序，对 $b$ 直接排序，然后将排序后的 $b$ 元素按 $a$ 的原始编号对应存储到 `tmp` 数组中，最后按顺序输出 `tmp` 数组。

#### Furina_Hate_Comma 的代码
```cpp
struct tem{
    int d,t;
}a[114514];
int b[114514];
bool cmp1(tem a,tem b){return a.t<b.t;}
bool cmp2(tem a,tem b){return a.d<b.d;}
signed main()
{
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>a[i].t;
            a[i].d=i;
        }for(int i=1;i<=n;i++)
            cin>>b[i];
        sort(a+1,a+1+n,cmp1);
        sort(b+1,b+1+n);
        for(int i=1;i<=n;i++)a[i].t=b[i];
        sort(a+1,a+1+n,cmp2);
        for(int i=1;i<=n;i++)
            cout<<(a[i].t)<<" ";
        cout<<"\n";
    }
    return 0;
}
```
**核心实现思想**：用结构体 `tem` 存储数组 $a$ 的元素及其原始编号，先对 $a$ 按元素值排序，对 $b$ 直接排序，将排序后的 $b$ 元素赋值给 $a$ 中对应位置的元素，再对 $a$ 按原始编号排序，最后按顺序输出 $a$ 中的元素。

#### EmptyAlien 的代码
```cpp
struct Node {
    int x;
    int id;
};
bool cmp(Node x, Node y)
{
    return x.x < y.x; // 按照值排序
}
void Solve()
{
    int n, k;
    cin >> n >> k;
    vector<Node> a(n); // 开一个长度为 n，类型为 Node 的数组
    vector<int> b(n), ans(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x;
        a[i].id = i; // 记录原始位置
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end(), cmp); // 排序
    sort(b.begin(), b.end());
    for (int i = 0; i < n; i++) {
        ans[a[i].id] = b[i]; // 把b[i]对应到a[i]的原始位置上
    }
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;
}
```
**核心实现思想**：用结构体 `Node` 存储数组 $a$ 的元素及其原始编号，使用 `vector` 存储数组 $a$、$b$ 和结果数组 `ans`，对 $a$ 按元素值排序，对 $b$ 直接排序，将排序后的 $b$ 元素按 $a$ 的原始编号对应存储到 `ans` 数组中，最后按顺序输出 `ans` 数组。

### 最优关键思路或技巧
- **贪心思想**：在保证有解的情况下，通过排序使两个数组对应位置的元素差值最小，从而满足题目条件。
- **记录原始编号**：使用结构体或数组记录数组 $a$ 中元素的原始编号，以便按原顺序输出重排后的 $b$ 数组。

### 拓展思路
同类型题目通常会涉及数组元素的重排和匹配，可能会有不同的约束条件。例如，可能会要求在满足某些条件下使某个目标函数值最大或最小，解题时可以先分析问题的本质，尝试找到贪心策略，再通过排序等操作实现。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，通过每次合并最小的两堆果子来使总代价最小。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：同样是贪心问题，通过对每个人的接水时间排序，使所有人的等待时间总和最小。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：利用贪心策略，按单位价值从高到低选择物品，以获取最大价值。

### 个人心得
部分题解提到不要过度纠结于样例，因为本题有多个解，输出其一即可。这提醒我们在做题时要理解题目的本质要求，不要被样例的具体形式所局限。

---
处理用时：54.80秒