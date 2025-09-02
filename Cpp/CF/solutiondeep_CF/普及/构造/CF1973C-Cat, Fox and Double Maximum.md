# 题目信息

# Cat, Fox and Double Maximum

## 题目描述

Fox loves permutations! She came up with the following problem and asked Cat to solve it:

You are given an even positive integer $ n $ and a permutation $ ^\dagger $ $ p $ of length $ n $ .

The score of another permutation $ q $ of length $ n $ is the number of local maximums in the array $ a $ of length $ n $ , where $ a_i = p_i + q_i $ for all $ i $ ( $ 1 \le i \le n $ ). In other words, the score of $ q $ is the number of $ i $ such that $ 1 < i < n $ (note the strict inequalities), $ a_{i-1} < a_i $ , and $ a_i > a_{i+1} $ (once again, note the strict inequalities).

Find the permutation $ q $ that achieves the maximum score for given $ n $ and $ p $ . If there exist multiple such permutations, you can pick any of them.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first example, $ a = [3, 6, 4, 7] $ . The array has just one local maximum (on the second position), so the score of the chosen permutation $ q $ is $ 1 $ . It can be proven that this score is optimal under the constraints.

In the last example, the resulting array $ a = [6, 6, 12, 7, 14, 7, 14, 6] $ has $ 3 $ local maximums — on the third, fifth and seventh positions.

## 样例 #1

### 输入

```
4
4
1 2 3 4
4
4 3 1 2
6
6 5 1 4 2 3
8
1 2 4 5 7 6 8 3```

### 输出

```
2 4 1 3
3 1 4 2
2 5 1 4 3 6
5 4 8 2 7 1 6 3```

# AI分析结果

### 题目中文重写
# 猫、狐狸与双重最大值

## 题目描述
狐狸喜欢排列！她想出了以下问题并让猫来解决：

给定一个正偶数 $n$ 和一个长度为 $n$ 的排列 $p$。

另一个长度为 $n$ 的排列 $q$ 的得分是数组 $a$（长度为 $n$，其中对于所有的 $i$（$1 \leq i \leq n$），$a_i = p_i + q_i$）中局部最大值的数量。换句话说，$q$ 的得分是满足 $1 < i < n$（注意是严格不等式）、$a_{i - 1} < a_i$ 且 $a_i > a_{i + 1}$（同样注意是严格不等式）的 $i$ 的数量。

找出对于给定的 $n$ 和 $p$ 能达到最大得分的排列 $q$。如果存在多个这样的排列，你可以任选一个。

注：长度为 $n$ 的排列是一个由 $n$ 个从 $1$ 到 $n$ 的不同整数按任意顺序组成的数组。例如，$[2, 3, 1, 5, 4]$ 是一个排列，但 $[1, 2, 2]$ 不是排列（数字 $2$ 在数组中出现了两次），$[1, 3, 4]$ 也不是排列（$n = 3$ 但数组中有 $4$）。

## 说明/提示
在第一个样例中，$a = [3, 6, 4, 7]$。该数组只有一个局部最大值（在第二个位置），所以所选排列 $q$ 的得分是 $1$。可以证明在给定约束条件下这个得分是最优的。

在最后一个样例中，得到的数组 $a = [6, 6, 12, 7, 14, 7, 14, 6]$ 有 $3$ 个局部最大值，分别在第三、第五和第七个位置。

## 样例 #1
### 输入
```
4
4
1 2 3 4
4
4 3 1 2
6
6 5 1 4 2 3
8
1 2 4 5 7 6 8 3
```

### 输出
```
2 4 1 3
3 1 4 2
2 5 1 4 3 6
5 4 8 2 7 1 6 3
```

### 综合分析与结论
这些题解主要围绕构造排列 $q$ 以最大化 $a_i = p_i + q_i$ 中局部最大值的数量展开。多数题解先分析出 $a$ 序列中局部最大值最多有 $\frac{n}{2}$ 个，然后通过不同方式构造排列 $q$。
- **思路对比**：
    - 部分题解（如 gan1234、hsy8116）先让 $p_i + q_i = n + 1$，再调整 $q$ 的奇偶位置使偶数位或奇数位增加以构造局部最大值，同时处理 $q$ 元素重复问题。
    - 部分题解（如 Cute__yhb、wfc284）根据 $1$ 的位置确定是奇数位还是偶数位作为局部最大值的候选位置，然后用贪心策略分配 $q$ 的值。
    - 部分题解（如 Robin_kool、Engulf）从让奇数位或偶数位数字尽量大的角度出发，结合贪心思想构造排列 $q$。
- **算法要点**：
    - 多数题解涉及对排列元素的排序和位置调整，以保证 $q$ 是合法排列且能使 $a$ 有最多局部最大值。
    - 部分题解使用标记数组记录元素是否被使用，方便处理元素重复问题。
- **解决难点**：
    - 处理 $q$ 元素重复问题是关键难点，不同题解采用不同方法，如用未使用的较小数替换奇数位置重复的数。
    - 确定是在奇数位还是偶数位构造局部最大值，部分题解通过判断 $1$ 的位置或偶数位是否有 $n$ 来决定。

### 所选题解
- **gan1234（5星）**
    - **关键亮点**：思路清晰，先构造 $p_i + q_i = n + 1$ 使所有数相等，再调整奇偶位置构造局部最大值，最后巧妙处理 $q$ 元素重复问题。
    - **核心代码**：
```cpp
void work(){
    v.clear();
    memset(book,0,sizeof(book));
    cin>>n;
    for(int i=1;n>=i;i++)cin>>a[i];
    int pp=0;
    for(int i=1;n>=i;i++){
        b[i]=n+1-a[i];
        if(!(i&1)&&b[i]==n)pp=1;
    }
    for(int i=2-pp;n>=i;i+=2)
        if(b[i]<n)b[i]++,book[b[i]]=1;
    for(int i=1+pp;n>=i;i+=2)v.push_back(b[i]),pos[b[i]]=i;
    sort(v.begin(),v.end());
    
    int t=1;
    for(auto i:v){
        if(book[i]){
            while(book[t])t++;
            b[pos[i]]=t;
            book[t]=1;
        }else book[i]=1;
    }
    for(int i=1;n>=i;i++)cout<<b[i]<<" ";
    cout<<endl;
}
```
    - **核心实现思想**：先计算初始的 $q$ 数组（$b$ 数组），判断偶数位是否有 $n$ 以确定调整的起始位置。对偶数位加 $1$ 并标记，将奇数位存入向量 $v$ 并排序。遍历 $v$，若元素位置被占则用未使用的最小数替换，最后输出 $q$ 数组。
- **hsy8116（4星）**
    - **关键亮点**：思路详细，对构造过程和正确性证明清晰，代码实现规范。
    - **核心代码**：
```cpp
while (T --)
{
    memset(vis, 0, sizeof(vis));
    v.clear();
    int n;
    scanf("%d", &n);
    int flag = 0; 
    for (int i = 1; i <= n; i ++)
    {
        scanf("%d", &p[i]);
        q[i] = n + 1 - p[i];
        if (i % 2 == 0 && q[i] == n) flag = 1;
    }
    for (int i = 2 - flag; i <= n; i += 2)
    {
        q[i] ++;
        vis[q[i]] ++;
    }
    for (int i = 1 + flag; i <= n; i += 2)
    {
        v.push_back(q[i]);
        pos[q[i]] = i;
    }
    sort(v.begin(), v.end());
    int avb = 1; 
    for (int i = 0; i < (int)v.size(); i ++)
    {
        if (vis[v[i]])
        {
            while (vis[avb]) avb ++;
            q[pos[v[i]]] = avb;
            vis[avb] = 1;
        }
        else
        {
            vis[v[i]] = 1;
        }
    }
    for (int i = 1; i <= n; i ++)
    {
        printf("%d ", q[i]);
    }
    puts("");
}
```
    - **核心实现思想**：与 gan1234 思路类似，先计算初始 $q$ 数组，根据偶数位是否有 $n$ 确定调整起始位置。对偶数位加 $1$ 并标记，将奇数位存入向量 $v$ 排序。遍历 $v$，处理元素位置被占的情况，最后输出 $q$ 数组。
- **Cute__yhb（4星）**
    - **关键亮点**：思路基于明显的性质，根据 $1$ 的位置确定构造局部最大值的位置，贪心分配 $q$ 的值，代码结构清晰。
    - **核心代码**：
```cpp
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    bool f=0;
    for(int i=1;i<=n;i+=2){
        if(a[i]==1){
            f=1;
            break;
        }
    }
    if(f){
        cnt=0;
        for(int i=2;i<=n;i+=2){
            cnt++;
            b[cnt].val=a[i];
            b[cnt].id=i;
        }
        sort(b+1,b+1+cnt,cmp);
        int tot=n;
        for(int i=1;i<=cnt;i++){
            ans[b[i].id]=tot;
            tot--;
        }
        cnt=0;
        for(int i=1;i<=n;i+=2){
            cnt++;
            b[cnt].val=a[i];
            b[cnt].id=i;
        }
        sort(b+1,b+1+cnt,cmp);
        for(int i=1;i<=cnt;i++){
            ans[b[i].id]=tot;
            tot--;
        }
    }else{
        cnt=0;
        for(int i=1;i<=n;i+=2){
            cnt++;
            b[cnt].val=a[i];
            b[cnt].id=i;
        }
        sort(b+1,b+1+cnt,cmp);
        int tot=n;
        for(int i=1;i<=cnt;i++){
            ans[b[i].id]=tot;
            tot--;
        }
        cnt=0;
        for(int i=2;i<=n;i+=2){
            cnt++;
            b[cnt].val=a[i];
            b[cnt].id=i;
        }
        sort(b+1,b+1+cnt,cmp);
        for(int i=1;i<=cnt;i++){
            ans[b[i].id]=tot;
            tot--;
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    puts("");
}
```
    - **核心实现思想**：先判断 $1$ 是否在奇数位，若在则在偶数位构造局部最大值，反之在奇数位构造。将对应位置的数存入结构体数组排序，用贪心策略从大到小分配 $q$ 的值，最后输出 $q$ 数组。

### 最优关键思路或技巧
- 先构造 $p_i + q_i = n + 1$ 使所有数相等，再调整奇偶位置构造局部最大值，这种思路简化了问题。
- 利用标记数组处理 $q$ 元素重复问题，保证 $q$ 是合法排列。
- 根据 $1$ 的位置或偶数位是否有 $n$ 确定构造局部最大值的位置，避免无效构造。

### 可拓展之处
同类型题可能会改变排列的条件或局部最大值的定义，类似算法套路是先分析问题的性质，找出最优解的上限，再通过构造和贪心策略来实现。

### 洛谷相似题目推荐
- P1090 [NOIP2004 提高组] 合并果子
- P1223 排队接水
- P1803 凌乱的yyy / 线段覆盖

### 个人心得摘录与总结
- KevinHu0402：表示题目比较简单，但自己赛时没过。总结为在比赛时可能因为紧张或思路不清晰导致简单题也会出错，需要在平时练习中提高自己的心理素质和解题能力。 

---
处理用时：51.61秒