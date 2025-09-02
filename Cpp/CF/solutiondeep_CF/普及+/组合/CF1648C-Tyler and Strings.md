# 题目信息

# Tyler and Strings

## 题目描述

While looking at the kitchen fridge, the little boy Tyler noticed magnets with symbols, that can be aligned into a string $ s $ .

Tyler likes strings, and especially those that are lexicographically smaller than another string, $ t $ . After playing with magnets on the fridge, he is wondering, how many distinct strings can be composed out of letters of string $ s $ by rearranging them, so that the resulting string is lexicographically smaller than the string $ t $ ? Tyler is too young, so he can't answer this question. The alphabet Tyler uses is very large, so for your convenience he has already replaced the same letters in $ s $ and $ t $ to the same integers, keeping that different letters have been replaced to different integers.

We call a string $ x $ lexicographically smaller than a string $ y $ if one of the followings conditions is fulfilled:

- There exists such position of symbol $ m $ that is presented in both strings, so that before $ m $ -th symbol the strings are equal, and the $ m $ -th symbol of string $ x $ is smaller than $ m $ -th symbol of string $ y $ .
- String $ x $ is the prefix of string $ y $ and $ x \neq y $ .

Because the answer can be too large, print it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the strings we are interested in are $ [1\, 2\, 2] $ and $ [2\, 1\, 2] $ . The string $ [2\, 2\, 1] $ is lexicographically larger than the string $ [2\, 1\, 2\, 1] $ , so we don't count it.

In the second example, all strings count except $ [4\, 3\, 2\, 1] $ , so the answer is $ 4! - 1 = 23 $ .

In the third example, only the string $ [1\, 1\, 1\, 2] $ counts.

## 样例 #1

### 输入

```
3 4
1 2 2
2 1 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
4 4
1 2 3 4
4 3 2 1```

### 输出

```
23```

## 样例 #3

### 输入

```
4 3
1 1 1 2
1 1 2```

### 输出

```
1```

# AI分析结果

### 题目中文重写
#### Tyler和字符串

### 题目描述
小男孩Tyler看着厨房的冰箱时，注意到上面有带符号的磁铁，可以排成一个字符串 $ s $。

Tyler喜欢字符串，尤其是那些字典序小于另一个字符串 $ t $ 的字符串。他在冰箱上摆弄磁铁后，想知道通过重新排列字符串 $ s $ 中的字母，可以组成多少个不同的字符串，使得得到的字符串在字典序上小于字符串 $ t $。Tyler太小了，无法回答这个问题。而且Tyler使用的字母表非常大，为了方便起见，他已经将 $ s $ 和 $ t $ 中相同的字母替换为相同的整数，同时保证不同的字母被替换为不同的整数。

如果满足以下条件之一，我们称字符串 $ x $ 在字典序上小于字符串 $ y $：
- 存在一个符号位置 $ m $ 同时出现在两个字符串中，使得在第 $ m $ 个符号之前，两个字符串相等，并且字符串 $ x $ 的第 $ m $ 个符号小于字符串 $ y $ 的第 $ m $ 个符号。
- 字符串 $ x $ 是字符串 $ y $ 的前缀且 $ x \neq y $。

由于答案可能非常大，请将结果对 $ 998244353 $ 取模后输出。

### 说明/提示
在第一个样例中，我们感兴趣的字符串是 $ [1, 2, 2] $ 和 $ [2, 1, 2] $。字符串 $ [2, 2, 1] $ 在字典序上大于字符串 $ [2, 1, 2, 1] $，因此我们不将其计入。

在第二个样例中，除了 $ [4, 3, 2, 1] $ 之外的所有字符串都符合条件，因此答案是 $ 4! - 1 = 23 $。

在第三个样例中，只有字符串 $ [1, 1, 1, 2] $ 符合条件。

### 样例 #1
#### 输入
```
3 4
1 2 2
2 1 2 1
```
#### 输出
```
2
```

### 样例 #2
#### 输入
```
4 4
1 2 3 4
4 3 2 1
```
#### 输出
```
23
```

### 样例 #3
#### 输入
```
4 3
1 1 1 2
1 1 2
```
#### 输出
```
1
```

### 题解综合分析与结论
这些题解的核心思路都是逐位比较字符串 $ s $ 和 $ t $，通过计算排列组合数来统计满足字典序小于 $ t $ 的 $ s $ 的排列数量。主要步骤包括：
1. 统计 $ s $ 中每个字符的出现次数。
2. 逐位考虑，对于每一位，分两种情况：放小于 $ t $ 当前位的字符和放等于 $ t $ 当前位的字符。
3. 计算排列组合数，处理相同字符的重复排列问题。
4. 考虑 $ n $ 和 $ m $ 的大小关系，处理 $ s $ 是 $ t $ 前缀的情况。

算法要点方面，多数题解使用树状数组来维护字符出现次数的前缀和，方便快速计算小于某个字符的字符数量。同时，使用快速幂和逆元来处理取模运算下的除法。

解决的难点主要在于：
1. 处理相同字符的重复排列，通过除以每个字符出现次数的阶乘来消除重复。
2. 高效计算排列组合数，避免重复计算。
3. 处理 $ n $ 和 $ m $ 大小不同的情况，特别是 $ s $ 是 $ t $ 前缀的情况。

### 评分较高的题解
- **作者：include_BM（5星）**
    - **关键亮点**：思路清晰，代码注释详细，使用树状数组维护字符出现次数的前缀和，通过快速幂计算逆元，处理取模运算。
    - **个人心得**：无
    - **核心代码**：
```cpp
const int N=1e6+10,P=998244353;
int n,m,a[N],b[N],sum[N],fac[N],ans,mul=1;

void chg(int x,int k){for(;x<=1e6;x+=x&-x) sum[x]+=k;}
int que(int x){int res=0;for(;x;x-=x&-x)res+=sum[x];return res;}

inline ll ksm(ll a,ll k){
    ll ans=1;
    for(;k;a=(a*a)%P,k>>=1)
        if(k&1) ans=(ans*a)%P;
    return ans;
}

signed main(){
    for(int i=(fac[0]=1);i<N;++i) fac[i]=(fac[i-1]*i)%P;
    n=read(),m=read();
    for(int i=1;i<=n;++i) a[i]=read(),chg(a[i],1);
    for(int i=1;i<=m;++i) b[i]=read();
    for(int i=1;i<=1e6;++i) mul=(mul*fac[que(i)-que(i-1)])%P;
    for(int i=1;i<=n+1;++i){
        if(i>n){
            if(n<m) ans=(ans+1)%P;
            break;
        }
        if(i>m) break;
        ans+=(que(b[i]-1)*fac[n-i])%P*ksm(mul,P-2)%P,ans%=P;
        if(que(b[i])-que(b[i]-1)){
            mul=(mul*ksm(que(b[i])-que(b[i]-1),P-2))%P;
            chg(b[i],-1);
        }
        else break;
    }
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：先预处理阶乘和逆元，使用树状数组维护字符出现次数的前缀和。逐位比较 $ s $ 和 $ t $，对于每一位，计算放小于 $ t $ 当前位字符的方案数，并更新字符出现次数和排列组合数。

- **作者：enucai（4星）**
    - **关键亮点**：思路清晰，详细解释了如何统计排列组合数，使用树状数组维护前缀和。
    - **个人心得**：纪念第一次在div2考场上做出E题，提醒注意取模，考场上没取模吃了罚时。
    - **核心代码**：
```cpp
#define int long long
int n,m,N,a[200010],b[200010];
int fac[200010],ifac[200010];
int cnt[200010];
bool ok[200010];
int c[200010];
int qry(int x){
    int res=0;
    while(x) res+=c[x],x-=x&(-x);
    return res;
}
void upd(int x,int val){
    while(x<=200000) c[x]+=val,x+=x&(-x);
}
int now;
signed main(){
    read(n,m);N=max(n,m);
    fac[0]=1;
    int ninv=minv(n);
    For(i,1,N) fac[i]=fac[i-1]*i%mod;
    ifac[N]=minv(fac[N]);
    Rof(i,N-1,0) ifac[i]=ifac[i+1]*(i+1)%mod;
    For(i,1,n) read(a[i]);
    For(i,1,m) read(b[i]);
    For(i,1,n) cnt[a[i]]++;
    now=fac[n];
    For(i,1,n) if(!ok[a[i]]){
        now=now*ifac[cnt[a[i]]]%mod;
        upd(a[i],cnt[a[i]]);
        ok[a[i]]=1;
    }
    int ans=0;
    For(i,1,n){
        if(i>m) break;
        ans+=now*qry(b[i]-1)%mod*ninv%mod;
        ans%=mod;
        int thi=qry(b[i])-qry(b[i]-1);
        if(thi==0) break;
        upd(b[i],-1);
        now=now*thi%mod*minv(qry(200000))%mod;
        if(i==n&&n<m) ans++;
    }
    cout<<ans%mod<<endl;
}
```
核心实现思想：预处理阶乘和逆元，使用树状数组维护字符出现次数的前缀和。逐位比较 $ s $ 和 $ t $，计算放小于 $ t $ 当前位字符的方案数，并更新字符出现次数和排列组合数。

- **作者：Alarm5854（4星）**
    - **关键亮点**：将问题分类讨论，详细推导了排列组合数的计算公式，使用树状数组维护字符出现次数的前缀和。
    - **个人心得**：提醒注意细节，如 $ t_i $ 用完时跳出循环，$ n < m $ 时最后一个位置对答案加一要取模，赛时有很多人因此FST。
    - **核心代码**：
```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#define ll long long
using namespace std;
const int N=2e5+7;
const ll p=998244353;
ll read(){
    char c;
    ll x=0,f=1;
    while(!isdigit(c=getchar()))
        f-=2*(c=='-');
    while(isdigit(c)){
        x=x*10+f*(c^48);
        c=getchar();
    }
    return x;
}
ll n,m,mx,res,tmp,s[N],t[N],cnt[N],fac[N],inv[N];
ll qpow(ll a,ll b=p-2){
    ll res=1;
    while(b){
        if(b&1)
            res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
ll c[N];
void add(int x,ll k){
    for(;x<=mx;x+=x&-x)
        c[x]+=k;
}
ll ask(int x){
    ll k=0;
    for(;x;x-=x&-x)
        k+=c[x];
    return k;
}
void solve1(){
    for(int i=1;i<=n;++i){
        tmp=tmp*inv[n-i+1]%p;
        tmp=tmp*fac[n-i]%p;
        res=(res+ask(t[i]-1)*tmp)%p;
        if(!cnt[t[i]])
            break;
        if(i==n)
            res=(res+1)%p;
        tmp=tmp*fac[cnt[t[i]]]%p;
        add(t[i],-1);
        --cnt[t[i]];
        tmp=tmp*inv[cnt[t[i]]]%p;
    }
}
void solve2(){
    for(int i=1;i<=m;++i){
        tmp=tmp*inv[n-i+1]%p;
        tmp=tmp*fac[n-i]%p;
        res=(res+ask(t[i]-1)*tmp)%p;
        if(!cnt[t[i]])
            break;
        tmp=tmp*fac[cnt[t[i]]]%p;
        add(t[i],-1);
        --cnt[t[i]];
        tmp=tmp*inv[cnt[t[i]]]%p;
    }
}
int main(){
    n=read();
    m=read();
    for(int i=1;i<=n;++i){
        s[i]=read();
        if(mx<s[i])
            mx=s[i];
        ++cnt[s[i]];
    }
    for(int i=1;i<=m;++i){
        t[i]=read();
        if(mx<t[i])
            mx=t[i];
    }
    fac[0]=1;
    for(int i=1;i<=n;++i)
        fac[i]=fac[i-1]*i%p;
    inv[n]=qpow(fac[n]);
    for(int i=n-1;~i;--i)
        inv[i]=inv[i+1]*(i+1)%p;
    for(int i=1;i<=mx;++i)
        add(i,cnt[i]);
    tmp=fac[n];
    for(int i=1;i<=mx;++i)
        tmp=tmp*inv[cnt[i]]%p;
    if(n<m)
        solve1();
    else
        solve2();
    printf("%lld\n",res);
    return 0;
}
```
核心实现思想：根据 $ n $ 和 $ m $ 的大小关系分类讨论，预处理阶乘和逆元，使用树状数组维护字符出现次数的前缀和。逐位比较 $ s $ 和 $ t $，计算放小于 $ t $ 当前位字符的方案数，并更新字符出现次数和排列组合数。

### 最优关键思路或技巧
- 使用树状数组维护字符出现次数的前缀和，可快速计算小于某个字符的字符数量，时间复杂度为 $ O(\log n) $。
- 预处理阶乘和逆元，处理取模运算下的除法，避免重复计算。
- 逐位比较 $ s $ 和 $ t $，分情况讨论放小于和等于 $ t $ 当前位字符的情况，逐步计算方案数。

### 可拓展之处
同类型题或类似算法套路：
- 字符串比较和排列组合问题，如计算满足特定条件的字符串排列数量。
- 数位DP问题，逐位考虑数字的选择，计算满足条件的数字组合数量。
- 树状数组的应用，如区间求和、单点修改等问题。

### 洛谷相似题目推荐
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：考察树状数组的区间求和和单点修改。
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：树状数组的基础应用，单点修改和区间求和。
3. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)：可以使用树状数组或线段树解决区间修改和单点查询问题。

### 个人心得摘录与总结
- enucai：纪念第一次在div2考场上做出E题，提醒注意取模，考场上没取模吃了罚时。总结：在处理大数运算时，一定要注意取模操作，避免结果溢出。
- Alarm5854：提醒注意细节，如 $ t_i $ 用完时跳出循环，$ n < m $ 时最后一个位置对答案加一要取模，赛时有很多人因此FST。总结：在处理边界条件和细节时要格外小心，避免因小错误导致错误结果。
- HoshizoraZ：本来赛时写出来了，然后有一两个地方忘取模了。总结：取模操作要贯穿整个代码，确保每个可能产生大数的地方都进行取模。 

---
处理用时：85.26秒