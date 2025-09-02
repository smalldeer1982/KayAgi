# 题目信息

# Power Products

## 题目描述

现在给你$n$个正整数 $[a_1,a_2,...,a_n]$ 和一个的正整数$k\geq2$，现在请你求出有多少组 $(i,j)$ ，满足 $(1≤i<j≤n)$且存在一个整数 $x$ 满足 $a_i\times a_j=x^k$

## 说明/提示

样例中有以下几组满足条件的组合

$a_1*a_4=8=2^3$

$a_1*a_6=1=1^3$

$a_2*a_3=27=3^3$

$a_3*a_5=216=6^3$

$a_4*a_6=8=2^3$

一共五组，所以输出为$5$

## 样例 #1

### 输入

```
6 3
1 3 9 8 24 1
```

### 输出

```
5
```

# AI分析结果

### 题目翻译
#### 幂积
##### 题目描述
现在给你 $n$ 个正整数 $[a_1,a_2,\cdots,a_n]$ 和一个正整数 $k\geq2$，现在请你求出有多少组 $(i,j)$，满足 $(1\leq i < j\leq n)$ 且存在一个整数 $x$ 满足 $a_i\times a_j = x^k$。

##### 说明/提示
样例中有以下几组满足条件的组合：
$a_1\times a_4 = 8 = 2^3$
$a_1\times a_6 = 1 = 1^3$
$a_2\times a_3 = 27 = 3^3$
$a_3\times a_5 = 216 = 6^3$
$a_4\times a_6 = 8 = 2^3$
一共五组，所以输出为 $5$。

##### 样例 #1
###### 输入
```
6 3
1 3 9 8 24 1
```
###### 输出
```
5
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于数学原理，利用唯一分解定理将问题转化为质因数指数的匹配问题。对于每个数，将其分解质因数，把质因数的指数对 $k$ 取模，然后寻找与之互补的质因数指数组合。不同题解在实现细节上有所差异，主要体现在质数筛选、哈希方法、数据结构的选择上。

### 所选题解
- **作者：Melon_Musk (4星)**
    - **关键亮点**：思路清晰，代码实现规范，使用质数筛和哈希结合 `map` 的方式解决问题，易于理解。
    - **核心实现思想**：先筛出质数，对每个数分解质因数，计算其质因数指数对 $k$ 取模后的哈希值，以及与之互补的哈希值，通过 `map` 统计互补哈希值的出现次数。
    - **核心代码**：
```cpp
map<ll,ll> mp;
int tot,n,k;
ll ans;
ull p[maxn];
int isp[maxn],P[maxn],Pid[maxn],a[maxn];
void shai(int n)     //筛一遍质数 
{
    isp[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!isp[i])	P[++tot]=i,Pid[i]=tot;
        for(int j=1;j<=tot && i*P[j]<=n;j++)
        {
            isp[i*P[j]]=1;
            if(i%P[j]==0) break;
        } 
    }
    return ; 
} 
int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++) a[i]=read();
    shai(100000);
    p[0]=1;
    for(int i=1;i<=tot;i++)
        p[i]=p[i-1]*(ull)base;
    for(int l=n;l;l--)
    {
        int x=a[l];
        ull ha=0,ah=0;
        for(int i=1;i<=tot;i++)
        {
            int cnt=0;
            if(x==1) break;
            if(P[i]*P[i]>x) break;
            if(x%P[i]) continue;
            while(x%P[i]==0) { x/=P[i]; cnt++;} 
            cnt%=k;
            if(cnt==0) continue;
            ha+=p[i]*cnt; ah+=p[i]*(k-cnt);
        }
        if(!isp[x])
            ha+=p[Pid[x]], ah+=p[Pid[x]]*(k-1);
        ans+=mp[ah]; mp[ha]++;
    } 
    printf("%lld\n",ans);
    return 0;
}
```
- **作者：aRenBigFather (4星)**
    - **关键亮点**：思路详细，步骤清晰，对问题的分析和转化过程有详细阐述，代码实现简洁高效。
    - **核心实现思想**：同样是先筛质数，然后对每个数分解质因数，计算其哈希值和互补哈希值，利用 `map` 统计互补哈希值的数量。
    - **核心代码**：
```cpp
void solve(int x){
    ull xhash = 0;
    ull aimhash = 0;
    int bakx = x;
    for(rg int i=1;i<=cnt;i++){
        if(x == 1) break;
        if(prime[i] * prime[i] > x) break;
        if(x % prime[i] == 0){
            int pcnt = 0;
            while(x % prime[i] == 0){
                x /= prime[i];
                pcnt++;
                if(pcnt >= k) pcnt -= k;
            }
            xhash += hashfac[i] * pcnt;
            if(pcnt != 0){
                aimhash += hashfac[i] * (k - pcnt);
            }
        }
    }
    if(x != 1){
        xhash += hashfac[primeid[x]];
        aimhash += hashfac[primeid[x]] * (k-1);
    }
    if(mp.count(aimhash)){
        ans += mp[aimhash];
    }
    mp[xhash]++;
}
int main(){
    n = read(),k = read();
    for(rg int i=1;i<=n;i++){
        a[i] = read();
    }
    initPrime();
    initHash();
    
    for(rg int i=n;i>=1;i--){
        solve(a[i]);
    }
    
    printf("%lld\n",ans);
    return 0;
}
```
- **作者：reyik (4星)**
    - **关键亮点**：使用 `vector` 存储质因数分解结果，代码简洁，思路直接，易于理解。
    - **核心实现思想**：对每个数分解质因数，将质因数指数对 $k$ 取模后存储在 `vector` 中，同时记录互补的状态，利用 `map` 统计互补状态的出现次数。
    - **核心代码**：
```cpp
map <vector< pair<int,int> > , int > mp;
vector<pair<int,int>> x,x1; 
int n,k,a[300005];
long long ans=0;
int main() {
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;++i) {
        scanf("%d",&a[i]);
        x.clear();x1.clear();
        int aa=a[i];
        for (int j=2;j*j<=a[i];++j) {
            int tot=0;
            while(aa%j==0) {
                ++tot;
                aa/=j;
                tot%=k;
            }
            if(!tot) continue;
            x.push_back({j,tot});
            x1.push_back({j,k-tot});
        }
        if(aa!=1) {
            x.push_back({aa,1});
            x1.push_back({aa,k-1});
        }
        ans=ans+mp[x1];
        ++mp[x];
    }
    printf("%lld\n",ans);
}
```

### 最优关键思路或技巧
- **数学原理**：利用唯一分解定理，将问题转化为质因数指数的匹配问题，即两个数的质因数指数之和为 $k$ 的倍数。
- **哈希与 `map` 结合**：通过哈希将质因数指数组合映射为一个唯一的值，使用 `map` 统计互补哈希值的出现次数，降低时间复杂度。
- **质数筛选**：预先筛出一定范围内的质数，方便后续分解质因数。

### 可拓展之处
同类型题可能会有不同的限制条件或数据范围，例如 $k$ 的值更大，或者数的范围更广。类似算法套路可以应用于其他涉及质因数分解和指数匹配的问题，如判断一个数是否为完全平方数、完全立方数等。

### 推荐题目
- [P1072  Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)：涉及数论和质因数分解。
- [P1463  [POI2002][HAOI2007]反素数](https://www.luogu.com.cn/problem/P1463)：需要对质因数分解和数学原理有深入理解。
- [P2152  [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)：考察高精度和数论知识。

### 个人心得摘录与总结
- **逆流之时**：尝试用字典树的解法，遇到了字典树空间大、边数设定、数据范围特判等问题，经过调试和优化才解决。总结是在使用复杂数据结构时要充分考虑细节和边界情况。
- **int1**：在 $k = 2$ 的情况下，因为质数个数略大于 $64$，用 $64$ 位整数压不下质因子指数奇偶性，导致罚时，提醒要注意数据范围和数据类型的选择。

---
处理用时：67.29秒