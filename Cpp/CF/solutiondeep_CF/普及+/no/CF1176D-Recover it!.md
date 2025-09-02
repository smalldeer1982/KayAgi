# 题目信息

# Recover it!

## 题目描述

Authors guessed an array $ a $ consisting of $ n $ integers; each integer is not less than $ 2 $ and not greater than $ 2 \cdot 10^5 $ . You don't know the array $ a $ , but you know the array $ b $ which is formed from it with the following sequence of operations:

1. Firstly, let the array $ b $ be equal to the array $ a $ ;
2. Secondly, for each $ i $ from $ 1 $ to $ n $ : 
  - if $ a_i $ is a prime number, then one integer $ p_{a_i} $ is appended to array $ b $ , where $ p $ is an infinite sequence of prime numbers ( $ 2, 3, 5, \dots $ );
  - otherwise (if $ a_i $ is not a prime number), the greatest divisor of $ a_i $ which is not equal to $ a_i $ is appended to $ b $ ;
3. Then the obtained array of length $ 2n $ is shuffled and given to you in the input.

Here $ p_{a_i} $ means the $ a_i $ -th prime number. The first prime $ p_1 = 2 $ , the second one is $ p_2 = 3 $ , and so on.

Your task is to recover any suitable array $ a $ that forms the given array $ b $ . It is guaranteed that the answer exists (so the array $ b $ is obtained from some suitable array $ a $ ). If there are multiple answers, you can print any.

## 样例 #1

### 输入

```
3
3 5 2 3 2 4
```

### 输出

```
3 4 2 ```

## 样例 #2

### 输入

```
1
2750131 199999
```

### 输出

```
199999 ```

## 样例 #3

### 输入

```
1
3 6
```

### 输出

```
6 ```

# AI分析结果

### 题目翻译
# 恢复它！

## 题目描述
出题人想出了一个由 $ n $ 个整数组成的数组 $ a $，每个整数不小于 $ 2 $ 且不大于 $ 2 \cdot 10^5 $。你不知道数组 $ a $，但你知道由它通过以下一系列操作形成的数组 $ b $：
1. 首先，令数组 $ b $ 等于数组 $ a $；
2. 其次，对于从 $ 1 $ 到 $ n $ 的每个 $ i $：
  - 如果 $ a_i $ 是质数，则将一个整数 $ p_{a_i} $ 追加到数组 $ b $ 中，其中 $ p $ 是一个无限的质数序列（$ 2, 3, 5, \dots $）；
  - 否则（如果 $ a_i $ 不是质数），将 $ a_i $ 的不等于 $ a_i $ 的最大因数追加到 $ b $ 中；
3. 然后将得到的长度为 $ 2n $ 的数组打乱顺序，并在输入中提供给你。

这里 $ p_{a_i} $ 表示第 $ a_i $ 个质数。第一个质数 $ p_1 = 2 $，第二个是 $ p_2 = 3 $，依此类推。

你的任务是恢复任何合适的数组 $ a $，使其能形成给定的数组 $ b $。保证答案存在（即数组 $ b $ 是由某个合适的数组 $ a $ 得到的）。如果有多个答案，你可以输出任何一个。

## 样例 #1
### 输入
```
3
3 5 2 3 2 4
```
### 输出
```
3 4 2
```

## 样例 #2
### 输入
```
1
2750131 199999
```
### 输出
```
199999
```

## 样例 #3
### 输入
```
1
3 6
```
### 输出
```
6
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心算法，根据质数和合数的不同性质来恢复原数组 $ a $。具体做法是对数组 $ b $ 中的元素按质数和合数分类，合数从大到小处理，质数从小到大处理。
- **思路**：利用质数产生更大质数，合数产生更小因数的特性，通过排序和标记来确定哪些数属于原数组 $ a $。
- **算法要点**：需要线性筛预处理质数，对数组 $ b $ 排序，根据元素性质进行分类处理并标记已使用的元素。
- **解决难点**：处理重复元素和正确标记已使用的元素，确保每个元素只被处理一次。

### 所选题解
- **作者：HMZHMZHMZ (4星)**
  - **关键亮点**：思路清晰，对合数和质数的处理逻辑明确，代码实现规范，有详细的注释。
  - **核心实现思想**：先线性筛预处理质数，对输入数组排序，从大到小处理合数，将未使用的合数加入答案并标记其最大因子；再从小到大处理质数，将未使用的质数加入答案并标记其产生的质数。
  - **核心代码**：
```cpp
inline void init(){
    for(register int i=2;i<=2750131;++i){
        if(!g[i]) prime[++cnt]=i;
        for(register int j=1;j<=cnt&&i*prime[j]<=2750131;j++){
            g[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
    g[1]=1;
}
int main(){
    init();
    n=read();
    n<<=1;
    for(register int i=1;i<=n;++i) a[i]=read();
    sort(a+1,a+n+1);
    for(register int i=n;i>=1;--i){
        if(!g[a[i]]||used[i]) continue;
        ans[++p]=a[i];
        int s=fnd(a[i]);
        int l=lower_bound(a+1,a+n+1,s)-a+sum[s];
        used[l]=used[i]=1;
        sum[s]++;
    }
    for(register int i=1;i<=n;++i){
        if(used[i]) continue; 
        int l=lower_bound(a+1,a+n+1,prime[a[i]])-a+sum[prime[a[i]]];
        used[l]=used[i]=1;
        sum[prime[a[i]]]++;
        ans[++p]=a[i];
    }
    for(register int i=1;i<=p;++i) printf("%d ",ans[i]);
    return 0;
}
```
- **作者：米奇 (4星)**
  - **关键亮点**：通过自定义排序规则将所有数排成链状，使处理过程更清晰，代码简洁。
  - **核心实现思想**：先欧拉筛预处理质数和每个数的相关信息，自定义排序函数将合数在前、质数在后排序，遍历排序后的数组，根据元素性质选择并标记。
  - **核心代码**：
```cpp
void work(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(!vis[i])prim[++cnt]=i;
        for(int j=1;j<=cnt;j++)
        {
            if(i*prim[j]>n)break;
            vis[i*prim[j]]=1;
            xu[i*prim[j]]=i;
            if(i%prim[j]==0)break;
        }
    }
}
bool cmp(int a,int b)
{
    if(vis[a]==0)
    {
        if(vis[b]==0)return a<b;
        else return 0;
    }
    if(vis[b]==0)
    {
        return 1;
    }
    return a>b;
}
int main()
{
    work(2750131);
    cin>>n;
    for(int i=1;i<=2*n;i++)
    {
        scanf("%d",&a[i]);
        b[a[i]]++;
    }
    sort(a+1,a+2*n+1,cmp);
    for(int i=1;i<=2*n;i++)
    {
        if(b[a[i]])
        {
            printf("%d ",a[i]);
            b[a[i]]--;
            if(vis[a[i]]==0&&a[i]<=cnt)b[prim[a[i]]]--;
            if(vis[a[i]])b[xu[a[i]]]--;
        }
    }
}
```
- **作者：wucstdio (4星)**
  - **关键亮点**：思路简洁明了，将质数和合数分类处理，通过线性筛和排序实现恢复原数组。
  - **核心实现思想**：线性筛预处理质数和最小质因子，将输入数组按质数和合数分类，合数从大到小、质数从小到大处理，标记并删除相关元素。
  - **核心代码**：
```cpp
void pre(int n)
{
    flag[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!flag[i])
        {
            prime[++num]=i;
            mind[i]=i;
        }
        for(int j=1;j<=num&&prime[j]*i<=n;j++)
        {
            flag[i*prime[j]]=1;
            mind[i*prime[j]]=min(mind[i],prime[j]);
            if(i%prime[j]==0)break;
        }
    }
}
int main()
{
    pre(5000000);
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++)
    {
        int x;
        scanf("%d",&x);
        if(flag[x])b[++top2]=x;
        else a[++top1]=x;
    }
    sort(b+1,b+top2+1);
    sort(a+1,a+top1+1);
    for(int i=top2;i>=1;i--)
    {
        if(s[b[i]])
        {
            s[b[i]]--;
            continue;
        }
        printf("%d ",b[i]);
        s[b[i]/mind[b[i]]]++;
    }
    for(int i=1;i<=top1;i++)
    {
        if(s[a[i]])
        {
            s[a[i]]--;
            continue;
        }
        printf("%d ",a[i]);
        s[prime[a[i]]]++;
    }
    printf("\n");
    return 0;
}
```

### 最优关键思路或技巧
- **线性筛预处理质数**：可以高效地得到质数表和每个数的最小质因子等信息。
- **排序**：对数组 $ b $ 排序，根据质数和合数的性质分别从大到小或从小到大处理，方便确定原数组 $ a $ 的元素。
- **标记已使用元素**：使用标记数组或桶来记录元素是否已被使用，避免重复处理。

### 可拓展之处
同类型题目可能会改变元素的变换规则，如变换成其他数学运算的结果，或者改变数组的构造方式。类似算法套路可以应用于需要根据元素性质进行分类处理和贪心选择的题目。

### 推荐题目
1. [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
2. [P1075 [NOIP2012 普及组] 质因数分解](https://www.luogu.com.cn/problem/P1075)
3. [P1579 哥德巴赫猜想（升级版）](https://www.luogu.com.cn/problem/P1579)

### 个人心得
部分题解未提及个人心得，整体题解主要关注思路和代码实现。 

---
处理用时：68.00秒