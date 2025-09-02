# 「LAOI-12」Sigma

## 题目背景

![](bilibili:BV1Gd4y1K7Ty)

## 题目描述

给定一个长度为 $n$ 的序列 $a$，求对于所有区间 $[l,r]$ 的 $\sum\limits_{i_1=1}^{a_l}\sum\limits_{i_2=2}^{a_{l+1}}\sum\limits_{i_3=3}^{a_{l+2}}\dots\sum\limits_{i_{r-l+1}=r-l+1}^{a_{r}}i_1+i_2+i_3+\dots+i_{r-l+1}$ 值的和，若存在 $k\in[1,r-l+1]$ 满足 $k>a_{l+k-1}$ 则认为该表达式值为 $0$，结果对 $998244353$ 取模。

## 说明/提示

### 样例解释

对于样例一中的区间贡献分别如下：
1. 对于 $[1,1]$，答案即为 $\sum\limits_{i_1=1}^1i_1=1$；
2. 对于 $[2,2]$，答案即为 $\sum\limits_{i_1=1}^3i_1=6$；
3. 对于 $[3,3]$，答案即为 $\sum\limits_{i_1=1}^2i_1=3$；
4. 对于 $[1,2]$，答案即为 $\sum\limits_{i_1=1}^1\sum\limits_{i_2=2}^3i_1+i_2=7$；
5. 查询 $[2,3]$，答案即为 $\sum\limits_{i_1=1}^3\sum\limits_{i_2=2}^2 i_1+i_2=12$；
6. 查询 $[1,3]$，答案即为 $\sum\limits_{i_1=1}^1\sum\limits_{i_2=2}^3\sum\limits_{i_3=3}^2 i_1+i_2+i_3=0$，因为 $3>2$。
### 数据范围

**本题采用捆绑测试。**

|子任务编号|$n$|特殊性质|分值|
|:-:|:-:|:-:|:-:|
|$1$|$\le 6$|$a_i\le 8$|$5$|
|$2$|$\le 10^2$|无|$30$|
|$3$|$\le 5\times10^3$|所有 $a_i$ 相等|$10$|
|$4$|$\le 5\times 10^3$|无|$55$|


对于 $100\%$ 的测试数据，满足 $1\le n\le 5\times 10^3$，$1\le a_i\le 10^9$。

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
29```

## 样例 #2

### 输入

```
5
8 9 12 7 1```

### 输出

```
81303```

# 题解

## 作者：Eason_cyx (赞：4)

本题解会从最基础的开始讲，然后逐渐优化到满分做法。

以下内容中 $V$ 均代表值域，即 $\displaystyle\max_{i=1}^{n}{a_i}$。

----

### Subtask 1：我会模拟！

直接根据题目意思模拟，时间复杂度 $O(V^n)$。

期望得分：$5$ 分。

### Subtask 2：我会数学！

因为 $n \le 5000$，所以我们首先考虑枚举区间。然后思考对于每个区间怎么算这个和。下面设 $m$ 为区间长度。

由于这里都是加法，那么每个求和符号之间实际上是相互独立的。那么，这里求和符号的顺序就可以随意交换。假设在一个式子中，第 $j$ 个求和符号下界为 $d_j$，上界为 $u_j$。那么通过贡献法与乘法原理，不难发现，第 $j$ 个求和符号对答案的贡献是：

$$\dfrac{(d_j+u_j)\times(u_j-d_j+1)}{2}\times\Big(\displaystyle\prod_{i=1,i\not=j}^{m}(u_i-d_i+1)\Big)$$

直接对着这个式子算即可，时间复杂度 $O(n^4)$。

期望得分：$35$ 分。

### Subtask 3 & 4：我会逆元！

将上面式子写成另外一种形式：

$$\dfrac{(d_j+u_j)\times(u_j-d_j+1)}{2}\times\dfrac{\displaystyle\prod_{i=1}^{m}(u_i-d_i+1)}{(u_j-d_j+1)}$$

于是 $u_j-d_j+1$ 消掉了，变成了：

$$\dfrac{(d_j+u_j)}{2}\times\displaystyle\prod_{i=1}^{m}(u_i-d_i+1)$$

于是这个式子中所有式子都可以在循环的过程中算出来。由于要取模，所以需要用到 $2$ 在模 $998244353$ 意义下的逆元 $499122177$。将除以 $2$ 换成乘 $499122177$ 即可。时间复杂度 $O(n^2)$。至此，我们通过了这道题。

注意精细取模。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed a[5005], c[5005];
const int mod = 998244353;
signed main() {
    int n, ans = 0; scanf("%d", &n);
    for(int i = 1;i <= n;i++) scanf("%d", &a[i]);
    for(int i = 1;i <= n;i++) {
        int sum = 1, ssum = 0;
        for(int j = i;j <= n;j++) {
            if(a[j] < (j-i+1)) break;
            c[j] = (1ll * (j-i+1+a[j]) * 499122177) % mod;
            sum = (sum * (a[j]-j+i)) % mod; ssum = (ssum + c[j]) % mod;
            ans = (ans + (sum * (ssum % mod)) % mod) % mod;
        } 
    } printf("%d\n", ans);
    return 0;
}
```

---

## 作者：_zjzhe (赞：4)

## 区间 DP

设 $f_{i,j}$ 为区间 $[i,j]$ 的答案，$g_{i,j}$ 为区间 $[i,j]$ 的运算次数，有状态转移方程

$$
f_{i,j} = \begin{cases} \sum _ {x=1}^{a_{j}} x & i = j \\ 0 & j-i+1 > a_{j} \\ f_{i,j}=f_{i,j-1}\times(a_{j}-j+i)+g_{i,j-1}\times\sum_{x=j-i+1}^{a_{j}}x & \text others \end{cases}
$$

$$
g_{i,j} = \begin{cases} a_{j}  & i = j \\ 0 & j-i+1 > a_{j} \\ g_{i,j}=g_{i,j-1}\times(a_{j}-j+i) & \text others \end{cases}
$$

下面做出解释：当 $i=j$ 时，区间长度为 1，依题意即可得出 $f_{i,j}=\sum _ {x=1}^{a_{j}} x$。当 $j-i+1\ge a_{i}$ 时，根据题意可得 $f_{i,j}=0$。对于正常情况，我们已知 $f_{i,j-1}$ 的答案，仅需加上 $a_{j}$ 对答案的影响即可推出 $f_{i,j}$。

观察下面两个式子：

$$f_{i,j-1}=\sum\limits_{i_1=1}^{a_i}\sum\limits_{i_2=2}^{a_{i+1}}\sum\limits_{i_3=3}^{a_{i+2}}\dots\sum\limits_{i_{j-i}=j-i}^{a_{j-1}}i_1+i_2+i_3+\dots+i_{j-i}$$

$$f_{i,j}=\sum\limits_{i_1=1}^{a_i}\sum\limits_{i_2=2}^{a_{i+1}}\sum\limits_{i_3=3}^{a_{i+2}}\dots\sum\limits_{i_{j-i+1}=j-i+1}^{a_{j}}i_1+i_2+i_3+\dots+i_{j-i+1}$$

注意到由于 $a_{j}$ 的加入，区间 $[i,j-1]$ 的贡献被计算了 $a_{j}-(j-i+1)+1$ 即 $a_{j}-j+i$ 次。相应的，$a_{j}$ 的贡献被计算了 $\prod\limits_{k=1}^{j-i}(a_{i+k-1}-k+1)$ 次。这样就能推出

$$f_{i,j}=f_{i,j-1}\times(a_{j}-j+i)+g_{i,j-1}\times\sum_{x=j-i+1}^{a_{j}}x$$

其中 $g_{i,j-1}$ 即为上面提到的 $\prod\limits_{k=1}^{j-i}(a_{i+k-1}-k+1)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5,P=998244353;
int T,n,a[N],f[N][N],g[N][N],ans;
int get(int x){
    return (1ll+x)*x%P*499122177%P;
}
#undef int
int main(){
#define int long long
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],f[i][i]=get(a[i]),g[i][i]=a[i],ans=(ans+f[i][i])%P;
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            if(len>a[j])f[i][j]=0,g[i][j]=0;
            else {
                g[i][j]=g[i][j-1]*(a[j]-len+1)%P;
                f[i][j]=(f[i][j-1]*(a[j]-len+1)%P+g[i][j-1]*(get(a[j])-get(len-1)+P+P)%P)%P;
            }
            ans=(ans+f[i][j])%P;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Joushi_Ikita (赞：3)

对于这道题目的数学解法，[这篇题解](https://www.luogu.com.cn/article/vuioixmi)讲解的已经很好，所以，我在这里讲一个更加信竞的解法——递推。

---
# 题目分析
对于数组 $a$ 的区间 $[l,r]$ 的 $\sum\limits_{i_1=1}^{a_l}\sum\limits_{i_2=2}^{a_{l+1}}\sum\limits_{i_3=3}^{a_{l+2}}\dots\sum\limits_{i_{r-l+1}=r-l+1}^{a_{r}}i_1+i_2+i_3+\dots+i_{r-l+1}$，我们定义 $cnt1[l][r]$ 为这个式子的值，$cnt2[l][r]$ 为这个式子的运算次数。

那么：
$$
cnt1_{l,r}=\sum\limits_{i_1=1}^{a_l}\dots\sum\limits_{i_{r-l+1}=r-l+1}^{a_{r}}i_1+\dots+i_{r-l+1}
$$
$$
cnt1_{l,r+1}=\sum\limits_{i_1=1}^{a_l}\dots\sum\limits_{i_{r-l+1}=r-l+1}^{a_{r}}\sum\limits_{i_{r+1-l+1}=r+1-l+1}^{a_{r+1}}i_1+\dots+i_{r+1-l+1}
$$
对第二个式子进行变形可得：

$$
cnt1_{l,r+1}=\sum\limits_{i_1=1}^{a_l}\dots\sum\limits_{i_{r-l+1}=r-l+1}^{a_{r}}(i_1+\dots+i_{r-l+1})\times(a_{r+1}-i_{r+1-l+1}+1)+\frac{(a_{r+1}+i_{r+1-l-1})\times(a_{r+1}-i_{r+1-l+1}+1)}{2}\\
=\left(\sum\limits_{i_1=1}^{a_l}\dots\sum\limits_{i_{r-l+1}=r-l+1}^{a_{r}}(i_1+\dots+i_{r-l+1})\times(a_{r+1}-i_{r+1-l+1}+1)\right)+\left(\sum\limits_{i_1=1}^{a_l}\dots\sum\limits_{i_{r-l+1}=r-l+1}^{a_{r}}\frac{(a_{r+1}+i_{r+1-l-1})\times(a_{r+1}-i_{r+1-l+1}+1)}{2}\right)
$$
观察可得：
$$
cnt1_{l,r+1}=cnt1_{l,r}\times(a_{r+1}-i_{r+1-l+1}+1)+cnt2_{l,r}\times\frac{(a_{r+1}+i_{r+1-l-1})\times(a_{r+1}-i_{r+1-l+1}+1)}{2}
$$
$$
cnt2_{l,r+1}=cnt2_{l,r}\times(a_{r+1}-i_{r+1-l+1}+1)
$$
这两个式子一出，不就可以进行递推了吗？

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100005];
__int128 ans,mod=998244353,cnt1,cnt2;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int j=0;j<n;j++){
    //枚举区间左端点的前一位
        cnt1=0;
        cnt2=1;
        for(int i=1;j+i<=n;i++){
        //区间长度（式子会比枚举右端点简洁一点）
            if(a[j+i]<i)break;
            //如果a[j+i]<i，后续的cnt就都等于零了，直接跳出循环（不跳就可能算出负的cnt）
            cnt1*=a[j+i]-i+1;
            cnt1%=mod;
            cnt1+=cnt2*((a[j+i]-i+1)*(a[j+i]+i)/2);
            //a[i]<=1e9,a[i]*a[i]<=1e18,不会爆long long,哪怕我不用__int128这里套个取模也可以省下乘法逆元的功夫
            cnt1%=mod;
            cnt2*=a[j+i]-i+1;
            cnt2%=mod;
            ans+=cnt1;
            ans%=mod;
        }
    }
    cout<<(long long)ans;
    return 0;
}
```

---

## 作者：Nahida_Official (赞：3)

## [P12374 「LAOI-12」Sigma](https://www.luogu.com.cn/problem/P12374)
令需要求和的数组为 $a$，当前数组的一个区间为 $[l,r]$，其中第 $k$ 个元素在原数组的位置为 $pos=l+k-1$，且必须满足 $k \le a_{pos}$。

我们已知 $k$ 的取值范围为 $1 \le k \le a_{pos}$，令在当前位置 $k$ 的选择数与当前的单位置和项分别为 $N_k,S_k$，有：
$$N_k=a_{pos}-k+1$$
$$S_k=\sum^{a_{pos}}_{i=k} i=\frac{(k+a_{pos}) \times (a_{pos}-k+1)}{2}= \frac{(k+a_{pos}) \times N_k}{2}$$

对于每个位置 $k$，假定贡献值不为零，则式子为：

$$\sum_{i_1=1}^{a_l} \sum_{i_2=2}^{a_{l+1}} \dots\sum\limits_{i_{r-l+1}=r-l+1}^{a_{r}}i_1+i_2+i_3+\dots+i_{r-l+1}$$

并且对于这个位置，$i_k \in \set{k,k+1,a_{pos}}$，并且该位置有 $N_k$ 种选择，那么总贡献可以进行分解：

$$\sum_{i_1} \sum_{i_2} \cdots \sum_{i_m}(
\sum^m_{k=1}i_k
)$$

进行线性分解，可以得到每个位置的贡献为：

$$\sum_{k=1}^m(S_k \times \prod_{j \not=k}N_j)$$

将已经求出来的单位置和代入，令总贡献为 $ans$，进行化简：
$$ans=\sum_{k=1}^m(\frac{(k+a_{pos}) \times N_k}{2} \prod_{j \not=k}N_j)=(\prod_{k=1}^m N_k) \times \sum_{k=1}^m \frac{k+a_{pos}}{2}$$

为了好看，把常数项提出来：

$$ans=\sum_{k=1}^m(\frac{(k+a_{pos}) \times N_k}{2} \prod_{j \not=k}N_j)=(\prod_{k=1}^m N_k)(\frac{1}{2} \times \sum_{k=1}^m (k+a_{pos}))$$

代码实现上，我们维护外层循环 $i$，内层循环 $j$，那么此时 $a_{pos}=i+j-1$，并且进行如下操作：

- 检查当前 $a_{pos}$ 是否满足 $j \le a_{pos}$；
- 更新 $pro$（区间内所有元素的合法选择数的乘积），即 $pro=pro \times a_{pos}-j+1$；
- 计算当前元素的单项和并累加到 $sum$，即 $sum=sum+\frac{a_{pos}+j}{2}$；
- 累加最终答案 $ans=pro \times sum$。

你就可以完成这道题了。
## P12374 Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define Sangonomiya signed
#define Kokomi main()
#define Love return
#define Nahida 0
#define Forever ;
#define IOS cin.tie(nullptr)->sync_with_stdio(false)
#define cin std::cin
#define cout std::cout
const int N=1e6;
const int mod=998244353;
int n,ans;
int a[N];
int pro,sum,pos;
int cnt,ps;
Sangonomiya Kokomi{
	IOS;
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++){
        pro=1;
        sum=0;
        for(int j=1;j+i-1<n;j++){
            pos=j+i-1;
            if(a[pos]<j) break;
            cnt=a[pos]-j+1;
            pro=(pro*cnt)%mod;
            ps=(a[pos]+j)%mod;
            ps=ps*499122177%mod;
            sum=(sum+ps)%mod;
            ans=(ans+pro*sum)%mod;
        }
    }
    cout<<ans<<'\n';
	Love Nahida Forever;
}
```
upd on 21:34 :修改了些许错误。

upd on 21:44 :增加了循环内关于 $a_{pos}$ 的解释。

---

## 作者：Anemones (赞：2)

首先我们先把要求的式子化一下。

$$\sum\limits_{i_1=1}^{a_1}\sum\limits_{i_2=2}^{a_{2}}\sum\limits_{i_3=3}^{a_{3}}\dots\sum\limits_{i_{k}=k}^{a_{k}}i_1+i_2+i_3+\dots+i_{k}$$

把 $i$ 分别提出来，令 $t=\prod\limits_{i=1}^k (a_i-i+1)$。

$$\sum_{i=1}^k \frac{(a_i-i+1)\times(a_i+i)}{2}\times\frac{t}{a_i-i+1}$$

$$\frac{t\times \sum\limits_{i=1}^k \frac{(a_i-i+1)\times(a_i+i)}{a_i-i+1}}{2}$$

上述式子可以做到 $O(n)$ 求，假如在上述式子右边再加上一个 $a_{k+1}$，容易发现 $\frac{(a_i-i+1)\times(a_i+i)}{a_i-i+1}=a_i+i$ 这个玩意是不会变的，那么先不考虑 $i_{k+1}$，则会发生的权值变化即为：

$$\frac{(a_{k+1}-k-1)\times \sum\limits_{i=1}^k (a_i+i)}{2}$$

而 $i_{k+1}$ 所带来的权值即为 $\frac{(a_{k+1}-k)\times(a_{k+1}+k+1)}{2}\times t$。

然后更新 $t$ 为 $t\times a_{k+1}$。

显然这个操作的转移是 $O(1)$ 的，所以我们枚举起始点后直接扫过去即可，时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#include<ext/rope>
using namespace __gnu_cxx;
#define mp make_pair
#define pb push_back
#define dbg puts("-------------qaqaqaqaqaqaqaqaqaq------------")
#define pl (p<<1)
#define pr ((p<<1)|1)
#define pii pair<int,int>
#define int long long
#define mod 998244353
#define eps 1e-9
#define ent putchar('\n')
#define sp putchar(' ')
using namespace std;
inline int read(){
    char c=getchar(),f=0;int t=0;
    for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
    for(;c>='0'&&c<='9';c=getchar()) t=(t<<1)+(t<<3)+(c^48);
    return f?-t:t;
}
inline void write(int x){
    static int t[25];int tp=0;
    if(x==0) return(void)(putchar('0'));else if(x<0) putchar('-'),x=-x;
    while(x) t[tp++]=x%10,x/=10;
    while(tp--) putchar(t[tp]+48);
}
int n,ans;
int a[5009];
int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
int inv(int x){return qpow(x,mod-2);}
signed main(){
    for(int p=1;p<=1;p++){
        char awa[30];
        //sprintf(awa,"sigma%d.in",p);
	    //freopen(awa,"r",stdin);
		//sprintf(awa,"sigma%d.out",p);
		//freopen(awa,"w",stdout);
        n=read(),ans=0;
        memset(a,0,sizeof(a));
        int inv2=inv(2);
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        for(int i=1;i<=n;i++){
            int t=a[i],res=a[i]*(a[i]+1)%mod*inv2%mod;
            ans=(ans+res)%mod;
            int sum=a[i]+1;
            for(int j=i+1;j<=n;j++){
                int k=j-i+1;
                if(k>a[j]){
                    res=0;
                    break;
                }
                int temp=a[j]-k+1,calc=0;
                calc+=(temp-1)*sum%mod*inv2%mod,calc%=mod;
                calc+=temp*(a[j]+k)%mod*inv2%mod*t%mod,calc%=mod;
                sum=((sum+a[j])%mod+k)%mod;
                t=t*a[j]%mod;
                res=(res+calc)%mod;
                ans=(ans+res)%mod;
            }
        }
        write(ans),ent;
    }
    return 0;
}
```

---

## 作者：modfish_ (赞：1)

## 思路
考虑对每个位置 $i$ 分别计算贡献。

先枚举左端点 $l$，记 $s_i=i-l+1$，则对于某个 $l\le i\le n$，它提供的权值为 $\displaystyle\sum_{x=s_i}^{a_i}x=\frac{(a_i+s_i)(a_i-s_i+1)}{2}$。

再考虑它会被计算的次数。记 $b_j=\max(a_j-s_j+1)$，很容易推出是：

$$\sum_{r=i}^n(\prod_{j=l}^{i-1}b_j\times \prod_{j=i+1}^rb_j)$$

注意：此处定义，若 $a>b$，则认为：

$$\prod_{j=a}^bb_j=1$$

不可能再枚举一维 $r$，不然会超时。注意到左边一项与 $r$ 无关，可以提出来：

$$\prod_{j=l}^{i-1}b_j\times \sum_{r=i}^n\prod_{j=i+1}^rb_j$$

记 $g_i=\displaystyle\sum_{r=i}^n\prod_{j=i+1}^rb_j$，可以发现：

$$g_i=b_{i+1}g_{i+1}+1$$

特别地，$g_n=1$。于是倒着枚举 $i$ 递推即可。

顺便还预处理一个 $f_i=\displaystyle\prod_{j=l}^ib_i$，就可以得到 $i$ 的贡献：

$$f_ig_i\frac{(a_i+s_i)(a_i-s_i+1)}{2}$$

枚举 $l$ 和 $i$ 计算，时间复杂度为 $O(n^2)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3 + 5, p = 998244353;

int a[maxn], f[maxn];

long long sum(int l, int r){
    if(l > r) return 0;
    return (1ll * (l + r) * (r - l + 1) / 2) % p;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
    int ans = 0;
    for(int l = 1; l <= n; l ++){
        f[l - 1] = 1;
        for(int i = l; i <= n; i ++) f[i] = 1ll * f[i - 1] * max(a[i] - (i - l + 1) + 1, 0) % p;
        int v = 1;
        for(int i = n; i >= l; i --){
            ans = (ans + sum(i - l + 1, a[i]) * v % p * f[i - 1] % p) % p;
            v = (1ll * v * max(a[i] - (i - l + 1) + 1, 0) % p + 1) % p;
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

