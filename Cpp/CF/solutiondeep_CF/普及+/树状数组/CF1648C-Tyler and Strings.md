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

### 题目内容中文重写
### Tyler和字符串

#### 题目描述
小男孩Tyler看着厨房的冰箱时，注意到上面有带符号的磁铁，这些磁铁可以排成一个字符串 $ s $。

Tyler喜欢字符串，尤其喜欢那些字典序小于另一个字符串 $ t $ 的字符串。他在冰箱上摆弄磁铁后，想知道通过重新排列字符串 $ s $ 中的字母，可以组成多少个不同的字符串，使得得到的字符串字典序小于字符串 $ t $。Tyler太小了，无法回答这个问题。而且Tyler使用的字母表非常大，为了方便起见，他已经将 $ s $ 和 $ t $ 中相同的字母替换为相同的整数，不同的字母替换为不同的整数。

如果满足以下条件之一，我们称字符串 $ x $ 的字典序小于字符串 $ y $：
- 存在一个符号位置 $ m $，该位置同时出现在两个字符串中，使得在第 $ m $ 个符号之前两个字符串相等，并且字符串 $ x $ 的第 $ m $ 个符号小于字符串 $ y $ 的第 $ m $ 个符号。
- 字符串 $ x $ 是字符串 $ y $ 的前缀，且 $ x \neq y $。

由于答案可能非常大，请将结果对 $ 998\,244\,353 $ 取模后输出。

#### 说明/提示
在第一个样例中，我们感兴趣的字符串是 $ [1\, 2\, 2] $ 和 $ [2\, 1\, 2] $。字符串 $ [2\, 2\, 1] $ 的字典序大于字符串 $ [2\, 1\, 2\, 1] $，因此我们不将其计入。

在第二个样例中，除了 $ [4\, 3\, 2\, 1] $ 之外的所有字符串都符合条件，因此答案是 $ 4! - 1 = 23 $。

在第三个样例中，只有字符串 $ [1\, 1\, 1\, 2] $ 符合条件。

#### 样例 #1
##### 输入
```
3 4
1 2 2
2 1 2 1
```
##### 输出
```
2
```

#### 样例 #2
##### 输入
```
4 4
1 2 3 4
4 3 2 1
```
##### 输出
```
23
```

#### 样例 #3
##### 输入
```
4 3
1 1 1 2
1 1 2
```
##### 输出
```
1
```

### 综合分析与结论
这些题解的核心思路都是逐位比较字符串 $s$ 和 $t$，对于每一位考虑放小于 $t$ 对应位的字符和等于 $t$ 对应位的字符两种情况。算法要点在于利用可重集排列公式 $\frac{n!}{\prod x_i!}$ 计算排列数，并使用树状数组维护字符出现次数的前缀和，方便快速计算小于某个字符的字符数量。

解决的难点主要有：
1. 如何处理相同字符的排列，避免重复计数，通过可重集排列公式解决。
2. 如何高效计算每一位放小于 $t$ 对应位字符时的方案数，使用树状数组维护前缀和来优化。
3. 处理 $n$ 和 $m$ 大小关系不同时的边界情况，如 $n<m$ 时 $s$ 可能是 $t$ 的前缀。

### 所选题解
- **作者：include_BM（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对每一步操作的解释明确，使用树状数组和快速幂取模解决问题。
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
- **作者：enucai（4星）**
    - **关键亮点**：详细解释了思路和难点，代码实现简洁，对取模操作有明确提示。
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
- **作者：Alarm5854（4星）**
    - **关键亮点**：对不同情况进行分类讨论，详细推导了公式，代码实现规范，对细节处理有明确提示。
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

### 最优关键思路或技巧
1. **可重集排列公式**：利用 $\frac{n!}{\prod x_i!}$ 计算可重集的排列数，避免相同字符排列的重复计数。
2. **树状数组**：使用树状数组维护字符出现次数的前缀和，能在 $O(\log n)$ 时间内完成单点修改和区间查询，优化了计算小于某个字符的字符数量的过程。
3. **分类讨论**：根据 $n$ 和 $m$ 的大小关系分类讨论，处理 $s$ 是 $t$ 前缀等边界情况。

### 可拓展之处
同类型题或类似算法套路：
1. 其他字典序比较的排列组合问题，如求字典序大于某个字符串的排列数。
2. 涉及可重集排列的计数问题，可能需要结合不同的数据结构和算法进行优化。
3. 数位 DP 问题，逐位考虑状态转移，与本题逐位比较的思路类似。

### 推荐洛谷题目
1. [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：考查全排列和字典序的知识。
2. [P1338 末日的传说](https://www.luogu.com.cn/problem/P1338)：涉及排列的字典序和逆序对的计算。
3. [P3182 [HAOI2016]放棋子](https://www.luogu.com.cn/problem/P3182)：可重集排列和组合计数的应用。

### 个人心得摘录与总结
- **HoshizoraZ**：赛时写出来但因忘取模出错，提醒要注意取模操作，同时提到若 $n<m$ 枚举到第 $n$ 位时的特殊处理以及枚举某一位无可用数时的退出条件。总结为做题时要注意细节，特别是取模操作，同时要考虑边界情况。
- **enucai**：纪念第一次在 div2 考场上做出 E 题，提醒考场上要注意取模，避免罚时。总结为考试时要细心处理取模等细节。
- **Alarm5854**：提醒若 $n<m$ 最后一个位置对答案加一时要记得取模，赛时有很多人因此 FST。总结为处理边界情况时要注意取模，避免错误。 

---
处理用时：79.34秒