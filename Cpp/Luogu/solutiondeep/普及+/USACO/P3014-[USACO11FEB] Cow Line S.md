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
这些题解均围绕康托展开和逆康托展开来解决问题。思路上都是先理解康托展开和逆康托展开的原理，再根据题目中的 `P` 和 `Q` 指令分别进行逆展开和展开操作。算法要点在于正确实现康托展开和逆康托展开的计算过程，难点在于理解康托展开的原理以及如何高效实现逆展开。部分题解使用树状数组优化了康托展开的计算过程。

### 所选题解
- **作者：YoungNeal（5星）**
    - **关键亮点**：思路清晰，对康托展开和逆康托展开的原理讲解详细，代码实现简洁易懂，有完整的注释。
- **作者：Rainybunny（4星）**
    - **关键亮点**：对康托展开进行了详细的证明，代码使用了优化模板，提高了代码的效率和可读性。
- **作者：Honeta（4星）**
    - **关键亮点**：使用树状数组对康托展开进行了优化，在数据较大时能提高效率，同时给出了详细的思路点拨和前置知识链接。

### 重点代码
#### YoungNeal 的题解
```cpp
// 康托展开
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

// 逆康托展开
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
**核心实现思想**：`contor` 函数通过遍历数组，统计每个数后面比它小的数的个数，乘以对应位数的阶乘并累加，最后加 1 得到该排列的序号。`reverse_contor` 函数先将序号减 1，然后依次计算每一位的数字，通过标记数组 `vis` 记录已使用的数字。

#### Rainybunny 的题解
```cpp
// Cantor展开求k
inline LL Cantor ( const int* Seq ) {
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

// 逆康拓展开求数列
inline vector<int> ReCantor ( LL k ) {
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
**核心实现思想**：`Cantor` 函数与 `contor` 函数类似，统计每个数后面比它小的数的个数，乘以对应位数的阶乘并累加。`ReCantor` 函数使用 `vector` 存储未使用的数字，通过序号计算每一位的数字，并从 `vector` 中删除已使用的数字。

#### Honeta 的题解
```cpp
// 树状数组更新
void add(ll x,ll y)
{
  for(;x<=n;x+=x&-x)tree[x]+=y;
}

// 树状数组查询
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
  add(t2,-1); // 划掉这个数
  ans+=ask(t2)*fact[n-i]; // 运用树状数组求这位数字在它和它以后的所有数字中是第几大的数
}
printf("%lld\n",ans+1); // 记得求出来的结果要加1

// 逆康托展开
scanf("%lld",&t2);
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
printf("\n");
```
**核心实现思想**：使用树状数组 `add` 函数更新数组元素，`ask` 函数查询前缀和。在康托展开中，通过树状数组快速统计每个数后面比它小的数的个数。逆康托展开与其他题解类似。

### 最优关键思路或技巧
- **树状数组优化**：在康托展开中，使用树状数组可以快速统计每个数后面比它小的数的个数，将时间复杂度从 $O(n^2)$ 优化到 $O(nlogn)$。
- **预处理阶乘**：提前计算好阶乘的值，避免在每次计算时重复计算，提高效率。

### 可拓展之处
同类型题或类似算法套路包括八数码、魔板等问题，这些问题都可以使用康托展开进行状态压缩，减少空间复杂度。

### 推荐洛谷题目
- P1379 八数码难题
- P2481 [SDOI2010]代码拍卖会
- P3014 [USACO11FEB] Cow Line S

### 个人心得
- **Rainybunny**：花费一个午自习的时间对康托展开进行证明，帮助理解康托展开的原理。
- **Boxxxxxx**：使用树状数组和二分查找实现逆展开，复杂度为两个 log，也可以使用线段树优化到一个 log。
- **Honeta**：提醒一定要开 long long，避免数据溢出。

---
处理用时：48.91秒