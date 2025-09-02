# 题目信息

# Travelling Salesman and Special Numbers

## 题目描述

The Travelling Salesman spends a lot of time travelling so he tends to get bored. To pass time, he likes to perform operations on numbers. One such operation is to take a positive integer $ x $ and reduce it to the number of bits set to $ 1 $ in the binary representation of $ x $ . For example for number $ 13 $ it's true that $ 13_{10}=1101_{2} $ , so it has $ 3 $ bits set and $ 13 $ will be reduced to $ 3 $ in one operation.

He calls a number special if the minimum number of operations to reduce it to $ 1 $ is $ k $ .

He wants to find out how many special numbers exist which are not greater than $ n $ . Please help the Travelling Salesman, as he is about to reach his destination!

Since the answer can be large, output it modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, the three special numbers are $ 3 $ , $ 5 $ and $ 6 $ . They get reduced to $ 2 $ in one operation (since there are two set bits in each of $ 3 $ , $ 5 $ and $ 6 $ ) and then to $ 1 $ in one more operation (since there is only one set bit in $ 2 $ ).

## 样例 #1

### 输入

```
110
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
111111011
2
```

### 输出

```
169
```

# AI分析结果

### 题目中文重写
# 旅行商与特殊数字

## 题目描述
旅行商花费大量时间旅行，因此他很容易感到无聊。为了打发时间，他喜欢对数字进行操作。其中一种操作是取一个正整数 $x$，并将其简化为 $x$ 的二进制表示中值为 $1$ 的位数。例如，对于数字 $13$，$13_{10}=1101_{2}$，所以它有 $3$ 个值为 $1$ 的位，经过一次操作后，$13$ 将被简化为 $3$。

他将一个数字定义为特殊数字，如果将其简化为 $1$ 的最小操作次数为 $k$。

他想知道有多少个不大于 $n$ 的特殊数字。请帮助旅行商，因为他即将到达目的地！

由于答案可能很大，请将结果对 $10^{9}+7$ 取模后输出。

## 说明/提示
在第一个样例中，三个特殊数字是 $3$、$5$ 和 $6$。它们经过一次操作后会简化为 $2$（因为 $3$、$5$ 和 $6$ 的二进制表示中都有两个值为 $1$ 的位），再经过一次操作后会简化为 $1$（因为 $2$ 的二进制表示中只有一个值为 $1$ 的位）。

## 样例 #1
### 输入
```
110
2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
111111011
2
```
### 输出
```
169
```

### 综合分析与结论
这些题解主要围绕数位 DP 展开，也有部分使用组合数的方法。核心思路是先预处理出 1000 以内的数变为 1 的最小操作次数，再结合数位 DP 或组合数计算不大于 $n$ 且操作次数为 $k$ 的数的个数，同时需要对 $k = 0$ 和 $k = 1$ 等特殊情况进行特判。

数位 DP 的难点在于状态的设计和转移，要考虑当前剩余长度、1 的个数以及是否顶上界等因素。组合数方法的难点在于理解组合数的计算和应用，以及处理超出当前值的情况。

### 所选题解
- **作者：Yt_pY（5星）**
    - **关键亮点**：思路清晰，代码结构简洁，对预处理和数位 DP 的实现都有详细注释，便于理解。
- **作者：一个句号（4星）**
    - **关键亮点**：对模板化思路的阐述很详细，对数位 DP 维度设置的理解有独特见解，且给出了逻辑思考链。
- **作者：JimmyLee（4星）**
    - **关键亮点**：代码简洁，使用 `__builtin_popcount` 函数简化计算，对状态的定义和记忆化搜索的实现较为清晰。

### 重点代码
#### Yt_pY 的预处理和数位 DP 代码
```cpp
//sum[x]表示x在二进制下有多少个1
//cnt[x]表示x需要操作多少次才能变成1
inline int lowbit(int x){return x&(-x);}
//lowbit(x)就是提取x的右数第一个1表示的数
void init()
{
    sum[0]=0;
    cnt[1]=0;
    for(int i=1;i<=1000;i++)sum[i]=sum[i^lowbit(i)]+1;
    for(int i=2;i<=1000;i++)cnt[i]=cnt[sum[i]]+1;
}

int dfs(int s,int c,int lim)//还剩s长度，1有c个，lim为1/0表示顶/没顶上界 
{
    if(s==0)
    {
        if(c==0)return 0;
        else return(cnt[c]+1==k);
    }
    if(f[s][c][lim]!=-1)
        return f[s][c][lim];
    
    int res=0;
    if(lim==1)
    {
        if(num[s]==0)
            res=(res+dfs(s-1,c,1))%mod;
        else
        {
            res=(res+dfs(s-1,c,0))%mod;
            res=(res+dfs(s-1,c+1,1))%mod;
        }
    }
    else
    {
        res=(res+dfs(s-1,c,0))%mod;
        res=(res+dfs(s-1,c+1,0))%mod;
    }
    return f[s][c][lim]=res;
}
```
**核心思想**：先通过 `init` 函数预处理出 1000 以内数的二进制 1 的个数和变为 1 的操作次数，再通过 `dfs` 函数进行数位 DP，根据是否顶上界进行状态转移。

#### 一个句号的预处理和数位 DP 代码
```cpp
int getbit(int x){
    int ans=0;
    while(x){
        if(x&1)++ans;
        x>>=1;
    }
    return ans;
}//获得十进制数的二进制表达中的1的个数（十进制输出）

int get_cnt(int x){
    if(x==1) return 0;
    return get_cnt(getbit(x))+1;
    //如果是其他数，我getbit得到的本身就是个十进制表示数字，递归获取他的值即可
    //操作一次加一次，如代码所示
}//获取操作次数

ll DFS(int pos,int sum,bool flag,bool zero){//看二进制是否符合
    //sum代表当前的1的数量
    if(!pos)
        return (!zero)&&(f[sum]+1==k);//满足就算是有一个数啦！
    if(!zero&&!flag&&dp[pos][sum]!=-1)
        return dp[pos][sum];
    ll cnt=0,max_num=1;
    if(flag)max_num=num[pos];
    //num里存的不再是十进制数字，而是二进制的01
    //上界使我们第一次求出来的num数组，如果上一个数位没限制，可以取最大1
    //如果有限制，那么我只能取上界对应位置的数及其往下了
    for(int i=0;i<=max_num;i++){
        cnt+=DFS(pos-1,sum+(i==1),flag&&(i==max_num),zero&&(i==0));
        cnt%=mod;
    }
    if(!zero&&!flag)dp[pos][sum]=cnt;
    return cnt;
}
```
**核心思想**：通过 `getbit` 函数计算二进制 1 的个数，`get_cnt` 函数递归计算操作次数，`DFS` 函数进行数位 DP，根据是否顶上界和是否有前导零进行状态转移。

#### JimmyLee 的预处理和数位 DP 代码
```cpp
void init()
{
    for(int i=2;i<=1000;i++)
        ks[i]=ks[popc(i)]+1;
}

int dfs(int n, int cnt=0, bool la=0, bool lim=1)
{
    if(!lim&&~dp[n][cnt][la]) return dp[n][cnt][la];
    if(!n) return cnt==1&&la?0:cnt&&ks[cnt]==k-1;
    int ret=0, up=lim?bs[n]:1;
    for(int i=0;i<=up;i++)
        ret=(ret+dfs(n-1, cnt+i, i, lim&&i==up))%mod;
    if(!lim) dp[n][cnt][la]=ret;
    return ret;
}
```
**核心思想**：通过 `init` 函数预处理操作次数，`dfs` 函数进行数位 DP，根据是否顶上界进行状态转移。

### 最优关键思路或技巧
- **预处理**：由于一次操作后数字会变为 1000 以内，所以预处理 1000 以内的数变为 1 的最小操作次数，可减少重复计算。
- **数位 DP**：通过记录当前剩余长度、1 的个数和是否顶上界等状态，利用记忆化搜索避免重复计算，提高效率。
- **特判**：对 $k = 0$ 和 $k = 1$ 等特殊情况进行特判，避免错误结果。

### 可拓展之处
同类型题或类似算法套路：
- 其他数位统计问题，如计算某个区间内满足特定条件的数字个数。
- 状态压缩 DP 问题，通过二进制表示状态进行状态转移。

### 洛谷相似题目
- [P2657 [SCOI2009] windy 数](https://www.luogu.com.cn/problem/P2657)
- [P4127 [AHOI2009]同类分布](https://www.luogu.com.cn/problem/P4127)
- [P3413 SAC#1 - 萌数](https://www.luogu.com.cn/problem/P3413)

### 个人心得摘录与总结
- **一个句号**：提到数位 DP 很板，但状态设计比较难，$flag$ 为 $0$ 时才可以记录答案，$flag$ 为 $1$ 时有限制，需要单独进行枚举；$zero$ 为 $1$ 代表有前导零，前导零无效，进行统计时 $zero$ 为 $0$ 时才可以使用。还给出了特判的逻辑思考链，因为预处理时已经处理了一次，所以实际要判断的操作次数为 $k - 1$，$k$ 为 $0$ 和 $1$ 时需要特判。
- **弦巻こころ**：提到被特判恶心死，说明特判在本题中的重要性和容易出错的特点。 

---
处理用时：63.21秒