# 题目信息

# [USACO11FEB] Cow Line S

## 题目描述

The N (1 <= N <= 20) cows conveniently numbered 1...N are playing yet another one of their crazy games with Farmer John. The cows will arrange themselves in a line and ask Farmer John what their line number is. In return, Farmer John can give them a line number and the cows must rearrange themselves into that line.

A line number is assigned by numbering all the permutations of the line in lexicographic order.

Consider this example:

Farmer John has 5 cows and gives them the line number of 3.

The permutations of the line in ascending lexicographic order: 1st: 1 2 3 4 5

2nd: 1 2 3 5 4

3rd: 1 2 4 3 5

Therefore, the cows will line themselves in the cow line 1 2 4 3 5.

The cows, in return, line themselves in the configuration '1 2 5 3 4' and ask Farmer John what their line number is.

Continuing with the list:

4th : 1 2 4 5 3

5th : 1 2 5 3 4

Farmer John can see the answer here is 5

Farmer John and the cows would like your help to play their game. They have K (1 <= K <= 10,000) queries that they need help with. Query i has two parts: C\_i will be the command, which is either 'P' or 'Q'.

If C\_i is 'P', then the second part of the query will be one integer A\_i (1 <= A\_i <= N!), which is a line number. This is Farmer John challenging the cows to line up in the correct cow line.

If C\_i is 'Q', then the second part of the query will be N distinct integers B\_ij (1 <= B\_ij <= N). This will denote a cow line. These are the cows challenging Farmer John to find their line number.



## 样例 #1

### 输入

```
5 2 
P 
3 
Q 
1 2 5 3 4 
```

### 输出

```
1 2 4 3 5 
5 
```

# AI分析结果

### 综合分析与结论
这些题解均围绕康托展开和逆康托展开来解决问题，核心思路是利用康托展开将排列转换为序号，逆康托展开将序号转换为排列。不同题解在实现细节和优化方式上有所差异，部分题解使用树状数组优化康托展开过程，提高了效率。

### 所选题解
- **作者：YoungNeal（5星）**
    - **关键亮点**：思路清晰，详细介绍了康托展开和逆康托展开的概念、原理及实现过程，代码简洁易懂。
    - **核心代码**：
```cpp
int contor(int x[]){
    int p=0;
    for(int i=1;i<=n;i++){
        int t=0;
        for(int j=i+1;j<=n;j++){
            if(x[i]>x[j]) t++;
        }
        p+=t*fac[n-i];
    }
    return p+1;
}

void reverse_contor(int x){
    memset(vis,0,sizeof vis);
    x--;
    int j;
    for(int i=1;i<=n;i++){
        int t=x/fac[n-i];
        for(j=1;j<=n;j++){
            if(!vis[j]){
                if(!t) break;
                t--;
            }
        }
        printf("%d ",j);
        vis[j]=1;
        x%=fac[n-i];
    }
    puts("");
}
```
- **作者：Rainybunny（4星）**
    - **关键亮点**：对康托展开进行了详细的证明，代码中使用了优化模板，提高了代码的可读性和效率。
    - **核心代码**：
```cpp
inline LL Cantor ( const int* Seq ) { // Cantor展开求k 
    LL ret = 0;
    for ( Int i = 1; i <= n; ++ i ) {
        int Total = 0;
        for ( Int j = i + 1; j <= n; ++ j ) {
            Total += Seq[i] > Seq[j];
        }
        ret += Total * FAC[n - i];
    }
    return ret;
}

inline vector<int> ReCantor ( LL k ) { // 逆康拓展开求数列 
    vector<int> v, ret;
    for ( Int i = 1; i <= n; ++ i ) {
        v.push_back ( i );
    }
    for ( Int i = n; i; -- i ) {
        LL r = k % FAC[i - 1], t = k / FAC[i - 1];
        k = r;
        sort ( v.begin (), v.end () );
        ret.push_back ( v[t] );
        v.erase ( v.begin () + t );
    }
    return ret;
}
```
- **作者：Honeta（4星）**
    - **关键亮点**：使用树状数组优化康托展开过程，在数据较大时能显著提高效率，同时给出了详细的思路点拨和前置知识链接。
    - **核心代码**：
```cpp
void add(ll x,ll y)
{
  for(;x<=n;x+=x&-x)tree[x]+=y;
}
ll ask(ll x)
{
  ll res=0;
  for(;x;x-=x&-x)res+=tree[x];
  return res;
}

// 康托展开（树状数组优化）
ans=0;
for(ll i=1;i<=n;i++)
{
  scanf("%lld",&t2);
  add(t2,-1);
  ans+=ask(t2)*fact[n-i];
}
printf("%lld\n",ans+1);

// 逆康托展开
t2--;
for(ll i=1;i<=n;i++)
{
  ll temp=t2/fact[n-i];
  for(ll j=1;j<=n;j++)
  {
    if(vis[j])continue;
    if(!temp)
    {
      printf("%lld ",j);
      vis[j]=1;
      break;
    }
    temp--;
  }
  t2%=fact[n-i];
}
```

### 最优关键思路或技巧
- **康托展开与逆康托展开**：利用康托展开将排列转换为序号，逆康托展开将序号转换为排列，实现排列与序号的相互转换。
- **树状数组优化**：在康托展开过程中，使用树状数组可以快速计算每个数后面比它小的数的个数，将时间复杂度从 $O(n^2)$ 优化到 $O(nlogn)$。

### 可拓展之处
同类型题如八数码、魔板等问题，可利用康托展开对状态进行压缩，减少空间复杂度。类似算法套路还包括哈希表的空间压缩，将复杂的排列状态映射到较小的空间中。

### 推荐洛谷题目
1. [P1379 八数码难题](https://www.luogu.com.cn/problem/P1379)
2. [P2481 [SDOI2010]代码拍卖会](https://www.luogu.com.cn/problem/P2481)
3. [P3014 [USACO11FEB] Cow Line S](https://www.luogu.com.cn/problem/P3014)

### 个人心得摘录与总结
- **Rainybunny**：花费一个午自习时间对康托展开进行证明，体现了深入探究问题的精神，有助于更好地理解康托展开的原理。
- **Boxxxxxx**：提到用树状数组维护前缀和来解决单点修改区间查询问题，可实现康托展开和逆展开，但未详细讲解树状数组实现，可引导读者进一步学习树状数组相关知识。 

---
处理用时：40.95秒