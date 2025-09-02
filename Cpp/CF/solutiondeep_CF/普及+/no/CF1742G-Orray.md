# 题目信息

# Orray

## 题目描述

You are given an array $ a $ consisting of $ n $ nonnegative integers.

Let's define the prefix OR array $ b $ as the array $ b_i = a_1~\mathsf{OR}~a_2~\mathsf{OR}~\dots~\mathsf{OR}~a_i $ , where $ \mathsf{OR} $ represents the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). In other words, the array $ b $ is formed by computing the $ \mathsf{OR} $ of every prefix of $ a $ .

You are asked to rearrange the elements of the array $ a $ in such a way that its prefix OR array is lexicographically maximum.

An array $ x $ is lexicographically greater than an array $ y $ if in the first position where $ x $ and $ y $ differ, $ x_i > y_i $ .

## 样例 #1

### 输入

```
5
4
1 2 4 8
7
5 1 2 3 4 5 5
2
1 101
6
2 3 4 2 3 4
8
1 4 2 3 4 5 7 1```

### 输出

```
8 4 2 1 
5 2 1 3 4 5 5 
101 1 
4 3 2 2 3 4 
7 1 4 2 3 4 5 1```

# AI分析结果

### 题目翻译
你有一个由 $n$ 个非负整数组成的数组 $a$。

我们定义前缀或数组 $b$ 为 $b_i = a_1~\mathsf{OR}~a_2~\mathsf{OR}~\dots~\mathsf{OR}~a_i$，其中 $\mathsf{OR}$ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。换句话说，数组 $b$ 是通过计算 $a$ 的每个前缀的按位或得到的。

你需要重新排列数组 $a$ 中的元素，使得它的前缀或数组的字典序最大。

如果数组 $x$ 和数组 $y$ 第一个不同的位置上，$x_i > y_i$，则称数组 $x$ 的字典序大于数组 $y$。

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是利用贪心算法来解决问题。首先明确要让前缀或数组字典序最大，第一个数应取数组中的最大值。之后，通过不断选择能使当前前缀或结果最大的数，直到前缀或结果不再变化，剩余的数可以任意排列。

各题解的差异主要在于实现细节和优化方式：
- 部分题解利用位运算的特性，因为一个 `int` 类型最多 32 位，所以最多进行 32 次操作就能使前缀或达到最大值，从而减少不必要的计算。
- 有的题解通过排序来方便找到最大值，还有的题解使用标记数组来记录已使用的元素。

### 所选题解
- **沉石鱼惊旋（4星）**：
    - **关键亮点**：思路清晰，先找到数组中的最大值作为第一个元素，然后通过不断更新前缀或结果，选择能使结果最大的元素，当结果不再变化时，直接输出剩余元素，代码实现简洁易懂。
- **Larry76（4星）**：
    - **关键亮点**：对问题的性质分析深入，得出前缀或和序列存在一个位置 $j$，使得 $j$ 前面单调递增，$j$ 及其后面保持不变的结论，并据此设计贪心算法，时间复杂度分析准确。
- **Erica_N_Contina（4星）**：
    - **关键亮点**：详细阐述了按位或操作的性质，得出最多对 32 个数字进行按位或操作就能得到最大值的结论，通过枚举确定前 32 个元素，思路严谨。

### 重点代码
#### 沉石鱼惊旋的核心代码
```cpp
void solve()
{	
    vector<int>ans;
    int n,maxx=-1,id;
    cin>>n;
    int a[n+1];
    int tmp[n+1];
    bool f[n+1]={};
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        tmp[i]=a[i];
        if(a[i]>maxx)
        {
            maxx=a[i];
            id=i;
        }
    }
    f[id]=1;
    ans.push_back(maxx);
    int last=maxx;
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            tmp[j]|=maxx;
        }
        last=maxx;
        maxx=0;
        for(int j=1;j<=n;j++)
        {
            if(!f[j])
            {
                if(tmp[j]>maxx)
                {
                    maxx=tmp[j];
                    id=j;
                }
            }
        }
        f[id]=1;
        ans.push_back(a[id]);
        if(maxx==last)
        {
            for(int j=1;j<=n;j++)
            {
                if(!f[j])
                {
                    ans.push_back(a[j]);
                }
            }
            break;
        }
    }
    for(int i:ans)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}
```
**核心实现思想**：先找到数组中的最大值作为第一个元素，然后不断更新前缀或结果，选择能使结果最大的元素，当结果不再变化时，直接输出剩余元素。

#### Larry76的核心代码
```cpp
signed main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        int a[MAX_SIZE] = {};

        for (int i = 1; i <= n; i++)
            cin >> a[i];

        sort(a + 1, a + 1 + n, [](int a, int b) {
            return a > b;
        });
        vector <int> ans;
        unsigned long long now = a[1];
        ans.push_back(a[1]);
        a[1] = -1;

        for (int i = 30; i >= 1; i--) {
            unsigned long long maxnow = now;
            int nowpos = 1;

            for (int j = 2; j <= n; j++) {
                if (maxnow < (now | a[j]) && a[j] != -1) {
                    nowpos = j;
                    maxnow = now | a[j];
                }
            }

            if (a[nowpos] != -1) {
                now = maxnow;
                ans.push_back(a[nowpos]);
                a[nowpos] = -1;
            }
        }

        for (int i = 2; i <= n; i++)
            if (a[i] != -1)
                ans.push_back(a[i]);

        for (auto v : ans)
            cout << v << ' ';

        cout << endl;
    }
    return 0;
}
```
**核心实现思想**：先对数组降序排序，将最大值作为第一个元素，然后循环 $\lceil \lg a_{\max} \rceil$ 次，每次选择能使当前前缀或结果最大的元素，最后将剩余元素加入答案。

#### Erica_N_Contina的核心代码
```cpp
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    int sum=0;
    for(int i=1;i<=max(32ll,n);i++){
        int mxid=0;
        for(int j=1;j<=n;j++){
            if(vis[j])continue;
            if((sum|a[j])>(sum|a[mxid]))mxid=j;
        }
        if(!mxid)break;
        vis[mxid]=i;
        sum|=a[mxid];
        q.push(mxid);
    }
    while(q.size()){
        cout<<a[q.front()]<<' ';
        q.pop();
    }
    
    for(int i=1;i<=n;i++){
        if(!vis[i])cout<<a[i]<<' ';
    }
    cout<<endl;
    
    for(int i=1;i<=n;i++)vis[i]=0;
}
```
**核心实现思想**：通过枚举确定前 32 个元素，每次选择能使当前前缀或结果最大的元素，将其加入队列，最后依次输出队列中的元素和剩余元素。

### 最优关键思路或技巧
- **利用位运算特性**：由于一个 `int` 类型最多 32 位，最多进行 32 次操作就能使前缀或达到最大值，从而减少不必要的计算。
- **贪心策略**：每次选择能使当前前缀或结果最大的元素，保证前缀或数组的字典序最大。

### 拓展思路
同类型题或类似算法套路：
- 涉及位运算和贪心策略的题目，如求最大异或和、最小按位与和等。
- 构造类题目，需要根据特定条件重新排列元素，使某个指标达到最优。

### 推荐洛谷题目
- [P1850 换教室](https://www.luogu.com.cn/problem/P1850)：涉及位运算和动态规划，与本题的位运算和贪心思想有一定关联。
- [P2197 【模板】nim 游戏](https://www.luogu.com.cn/problem/P2197)：涉及位运算和博弈论，可锻炼对位运算的理解和应用。
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的动态规划问题，与本题的贪心思想类似，都是在一定条件下求最优解。

### 个人心得
部分题解中提到要注意按位或运算的优先级，在代码中使用括号明确运算顺序，避免出现错误。同时，对于多组输入，要记得清空标记数组等变量，防止数据干扰。 

---
处理用时：56.58秒