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
小男孩Tyler看着厨房的冰箱时，注意到上面有带符号的磁铁，这些磁铁可以排成一个字符串 $ s $。

Tyler喜欢字符串，尤其喜欢那些字典序小于另一个字符串 $ t $ 的字符串。在冰箱上摆弄完磁铁后，他想知道，通过重新排列字符串 $ s $ 中的字母，可以组成多少个不同的字符串，使得得到的字符串在字典序上小于字符串 $ t $ ？Tyler还太小，无法回答这个问题。Tyler使用的字母表非常大，所以为了方便起见，他已经将 $ s $ 和 $ t $ 中相同的字母替换为相同的整数，同时保证不同的字母被替换为不同的整数。

我们称字符串 $ x $ 在字典序上小于字符串 $ y $，如果满足以下条件之一：
- 存在一个符号位置 $ m $，它同时出现在两个字符串中，使得在第 $ m $ 个符号之前，两个字符串相等，并且字符串 $ x $ 的第 $ m $ 个符号小于字符串 $ y $ 的第 $ m $ 个符号。
- 字符串 $ x $ 是字符串 $ y $ 的前缀，且 $ x \neq y $。

由于答案可能非常大，请将其对 $ 998\,244\,353 $ 取模后输出。

### 说明/提示
在第一个样例中，我们感兴趣的字符串是 $ [1\, 2\, 2] $ 和 $ [2\, 1\, 2] $。字符串 $ [2\, 2\, 1] $ 在字典序上大于字符串 $ [2\, 1\, 2\, 1] $，所以我们不将其计入。

在第二个样例中，除了 $ [4\, 3\, 2\, 1] $ 之外的所有字符串都符合条件，所以答案是 $ 4! - 1 = 23 $。

在第三个样例中，只有字符串 $ [1\, 1\, 1\, 2] $ 符合条件。

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

### 综合分析与结论
这些题解的核心思路都是逐位比较字符串 $s$ 和 $t$，通过枚举 $s$ 与 $t$ 相同前缀的长度，计算当前位小于 $t$ 对应位时的排列方案数。
- **思路**：先计算可重集的全排列数，然后根据当前位的情况更新方案数。若当前位放小于 $t$ 对应位的字符，则后续位可任意排列；若放等于 $t$ 对应位的字符，则继续处理下一位。
- **算法要点**：
    - 计算可重集排列数：$\frac{n!}{\prod_{i} x_i!}$，其中 $n$ 是元素总数，$x_i$ 是第 $i$ 种元素的出现次数。
    - 用树状数组维护元素出现次数的前缀和，方便计算小于某个值的元素个数。
    - 快速幂计算逆元，处理取模运算。
- **解决难点**：
    - 处理相同字符的排列：通过除以相同字符的阶乘来消除重复排列。
    - 动态更新方案数：在选择字符后，更新元素出现次数和总方案数。
    - 处理边界情况：如 $n < m$ 时，$s$ 可能是 $t$ 的前缀。

### 所选题解
- **作者：include_BM（5星）**
    - **关键亮点**：思路清晰，代码注释详细，使用树状数组维护元素出现次数的前缀和，方便计算小于某个值的元素个数。
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
核心实现思想：先预处理阶乘，用树状数组维护元素出现次数的前缀和。遍历每一位，计算当前位小于 $t$ 对应位时的方案数，并更新总方案数。若当前位可以放等于 $t$ 对应位的字符，则更新元素出现次数和总方案数，继续处理下一位。

- **作者：enucai（4星）**
    - **关键亮点**：详细解释了思路和处理细节，代码简洁，通过取模避免溢出。
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
核心实现思想：预处理阶乘和逆元，用树状数组维护元素出现次数的前缀和。计算初始的可重集排列数，遍历每一位，计算当前位小于 $t$ 对应位时的方案数，并更新总方案数。若当前位可以放等于 $t$ 对应位的字符，则更新元素出现次数和总方案数，继续处理下一位。

- **作者：Alarm5854（4星）**
    - **关键亮点**：将问题分类讨论，对式子进行化简，便于维护和计算，详细说明了处理细节。
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
核心实现思想：根据 $n$ 和 $m$ 的大小关系分类讨论，预处理阶乘和逆元，用树状数组维护元素出现次数的前缀和。计算初始的可重集排列数，遍历每一位，计算当前位小于 $t$ 对应位时的方案数，并更新总方案数。若当前位可以放等于 $t$ 对应位的字符，则更新元素出现次数和总方案数，继续处理下一位。

### 最优关键思路或技巧
- **可重集排列数公式**：利用 $\frac{n!}{\prod_{i} x_i!}$ 计算可重集的全排列数，处理相同字符的排列问题。
- **树状数组**：维护元素出现次数的前缀和，快速计算小于某个值的元素个数，时间复杂度为 $O(\log n)$。
- **快速幂求逆元**：在取模运算中，使用快速幂计算逆元，避免除法运算带来的精度问题。

### 可拓展之处
同类型题目可能会改变字符串的比较规则，或者增加其他限制条件。类似算法套路可以用于解决排列组合问题，如计算满足特定条件的排列数、组合数等。

### 洛谷相似题目推荐
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：涉及排列的生成和查找，与本题的排列组合思想相关。
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：需要运用组合数和快速幂，与本题的取模运算和组合数计算有相似之处。
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)：需要对数据进行预处理和统计，与本题的元素统计和方案计算有一定关联。

### 个人心得摘录与总结
- **include_BM**：无。
- **enucai**：纪念第一次在div2考场上做出E题，提醒注意取模，考场上没取模吃了罚时。总结：在涉及大数计算和取模的题目中，要时刻注意取模操作，避免结果溢出。
- **Alarm5854**：提醒注意一些细节，如 $n < m$ 时最后一个位置对答案加一要取模，赛时有很多人因此FST。总结：处理边界条件和特殊情况时要格外小心，确保代码的正确性。
- **HoshizoraZ**：赛时写出来了，但有一两个地方忘取模，丢掉一千多分。总结：取模操作要贯穿整个代码，避免遗漏。
- **mango2011**：聪慧的作者在处理第二种情形时写错，吃了一发罚时。总结：对于简单情形也不能掉以轻心，要仔细思考和处理。 

---
处理用时：82.12秒