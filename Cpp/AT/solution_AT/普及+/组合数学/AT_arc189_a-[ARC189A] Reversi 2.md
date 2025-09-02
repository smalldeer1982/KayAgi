# [ARC189A] Reversi 2

## 题目描述

在一个由 $N$ 个格子组成的棋盘上，每个格子从 $1$ 到 $N$ 进行编号。

起初，第 $i$ 个格子上写有 $i \bmod 2$ 的数字。你可以进行以下操作若干次（可以是零次）：

- 选择两个满足条件的格子 $l$ 和 $r$（要求 $l + 1 < r$），将中间格子 $l + 1, l + 2, \dots, r - 1$ 上的数字全部改为格子 $l$ 上的数字。
  - 条件是格子 $l$ 和格子 $r$ 上的数字相同。
  - 并且中间的每个格子 $i$ （$l < i < r$）上的数字要与格子 $l$ 上的不同。
  
计算最后能使每个格子 $i$ 上的数字为 $A_i$ 的操作序列数量，并对结果取 $998244353$ 的余数。

注：若两个操作序列满足以下任一条件即视作不同：长度不同，或者存在一个正整数 $t$，使得操作中第 $t$ 次选择的 $(l, r)$ 组合不同。

## 说明/提示

- $1 \le N \le 2 \times 10^5$
- $0 \le A_i \le 1$
  
### 样例解释 1

为了使格子 $i(1 \le i \le N)$ 上的数字变为 $A_i$，可以按照以下步骤进行操作（这里用数列 $X = (X_1, X_2, \dots, X_N)$ 表示格子的状态）：
- 初始状态：$X = (1, 0, 1, 0, 1, 0)$。
- 选择格子 $2$ 和 $4$，之后状态变为 $X = (1, 0, 0, 0, 1, 0)$。
- 选择格子 $1$ 和 $5$，最终状态为 $X = (1, 1, 1, 1, 1, 0)$。

除了上述方法外，还有另外两种操作方法可以实现每个格子 $i$ 上的数字变为 $A_i$，因此答案是 $3$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
1 1 1 1 1 0```

### 输出

```
3```

## 样例 #2

### 输入

```
10
1 1 1 1 1 0 1 1 1 0```

### 输出

```
9```

# 题解

## 作者：Drifty (赞：17)

你是一位刚刚打完 NOIP 的魔怔 OIer。

面对自己挂的惨不忍睹的分数，你决定打一下 unr 的 ARC 发泄一下。

打开了 T1，发现是一道神秘的计数问题，跟之前的 NOIP T2 都是【数据删除】的数数题。

于是你就开始数了，你先从全是 $1$ 的序列开始考虑，你发现对于一个长度为 $n$ 的全是 $1$ 的序列，如果 $n$ 为偶数，那么显然这是无解的，而当 $n$ 是奇数的时候，你会发现它的方案数实际上就是 [A001147](https://oeis.org/A001147)。具体地，你计一个 $f_{i}$ 代表长度为 $2i + 1$ 的序列的方案数，你容易发现，对于每一种 $f_{i - 1}$ 都可以从左右两边转移（除了中间的两个 $0$ 消掉变成 $1$ 的那种），那么就有递推式 $f_{i} = f_{i - 1} \times (2i - 1)$，这样我们就迈出了第一步。

然后你又会发现这个问题，由于各个连续相等的子段互相不关联，那么就等价于在保证局部有序的情况下乱排的个数，然后你就觉得太麻烦了，于是乱交了几发就下播睡觉了。

在睡梦中，你发现我们如果记这些连续相等的子段的长度为 $(l_1, l_2, \ldots, l_m)$，那么由于每一个长度为 $l_i$ 的序列必须且只能通过 $\lfloor \frac{l_i}{2} \rfloor$ 次操作解决，那么这个问题就变成了一个 [多重集的排列数](https://oi-wiki.org/math/combinatorics/combination/#%E5%A4%9A%E9%87%8D%E9%9B%86%E7%9A%84%E6%8E%92%E5%88%97%E6%95%B0--%E5%A4%9A%E9%87%8D%E7%BB%84%E5%90%88%E6%95%B0) 的问题，当然，这里的 $n_i=\lfloor \frac{l_i}{2} \rfloor$，又由于每一个子序列都有 $f_{\lfloor \frac{l_i}{2} \rfloor}$ 种方案，那么我们再把答案乘上 $\prod_{i = 1}^{n} f_{\lfloor \frac{l_i}{2} \rfloor}$，秒掉了。

第二天起来，你生气地敲着你的代码，看来不仅 NOIP 没有 RP，ARC 也没有 RP，你的人生也没有 RP 啊。越练越菜啊。没有天赋啊。

在胡思乱想中，终于，你敲出了一份正确的 [代码](https://atcoder.jp/contests/arc189/submissions/60603260)。

---

## 作者：Cx114514 (赞：8)

### 题目链接：[[ARC189A] Reversi 2](https://www.luogu.com.cn/problem/AT_arc189_a)

首先考虑这个操作，无论怎么变，一个极长同色连续段的长度永远是奇数，且极长同色连续段的两边颜色一定和原来相同。

不满足上述条件的就是无解，输出 $0$ 即可，这样剩下的序列就一定是若干个长度为奇数的极长连续段。

考虑怎么把一个 $1010\cdots0101$ 变为 $1111\cdots1111$。（$0101\cdots1010$ 变为 $0000\cdots 0000$ 是等价的）

如果把原序列中的一个 $010$ 合并，这段就会变为 $000$，在后续操作中与 $0$ 等价；如果把原序列中的一个 $101$ 合并，这段就会变为 $111$，在后续操作中与 $1$ 等价。

这也就意味着，对于一个长度为 $n$ 的 $1010\cdots0101$ 进行一次操作，就转化为了长度为 $n-2$ 的 $1010\cdots 0101$，而这样的操作有 $n-2$ 种。

令 $f_i$ 表示把一个长度为 $i$ 的 $1010\cdots0101$ 变为 $1111\cdots1111$ 的方案数。

则易得转移：

$f_i=f_{i-2} \times \left(i-2\right)$

这样我们就求得了每个连续段的操作方案数。

令极长连续段个数为 $m$，每一段的长度为 $len$。

首先钦定每一个连续段中使用的是哪一种操作，这样有 $\prod\limits_{i=1}^{m} f_{len_i}$ 种。

再考虑每一步操作的先后顺序。

每一个连续段需要操作 $\left \lfloor 
\frac{len_i}{2}  \right \rfloor$ 次，一共需要操作 $\sum\limits_{i=1}^{m}\left \lfloor 
\frac{len_i}{2}  \right \rfloor$ 次。可以看作每一个连续段在操作序列中选一些位置。

令 $k=\sum\limits_{i=1}^{m}\left \lfloor 
\frac{len_i}{2}  \right \rfloor$。

第 $1$ 个连续段选择的方案数有 $\binom{k}{\left \lfloor 
\frac{len_1}{2}  \right \rfloor}$，在第 $2$ 段选择的时候，第 $1$ 段选择的位置已经不能再选了，故方案数为 $\binom{k-\left \lfloor 
\frac{len_2}{2}  \right \rfloor}{\left \lfloor 
\frac{len_1}{2}  \right \rfloor}$。以此类推，总方案数为 $\prod\limits_{i=1}^m\binom{k-\sum\limits_{j=1}^{i-1}\left \lfloor 
\frac{len_j}{2}  \right \rfloor}{\left \lfloor 
\frac{len_i}{2}  \right \rfloor}$。

答案为：

$$\prod\limits_{i=1}^{m} f_{len_i}\times\prod\limits_{i=1}^m\binom{k-\sum\limits_{j=1}^{i-1}\left \lfloor 
\frac{len_j}{2}  \right \rfloor}{\left \lfloor 
\frac{len_i}{2}  \right \rfloor}$$

---

## 作者：MspAInt (赞：1)

我重生了，重生在吃掉山椒味香脆笋的前一分钟，我忽然意识到做题比吃山椒味香脆笋更重要，于是我放下山椒味香脆笋打开 kenkoooo。

---

首先发现连续段互不影响，于是单独考虑。

连续段的两端 $l,r$ 要满足 $A_l=l\bmod2,A_r=r\bmod2$，如果不满足说明被修改过，则相邻一定还有和它一样的，与其是边界矛盾。现在判断完 0 方案。

然后一段的方案数是什么？设 $f_i$ 表示一个长度为 $i$ 的全 0/1 段的方案数。考虑现在是 01010…… 的形式，把 101 变成 111，然后串变成 01110，发现此后等价于对 010 的操作。可知 $f_i=(i-2)f_{i-2}$。每一段方案数乘起来。

再说操作顺序。相当于每一段的操作混起来，但段内操作不能乱。每一段乘上 $(\lfloor\frac{i}{2}\rfloor!)^{-1}$，再乘上 $(\sum {\lfloor\frac{i}{2}\rfloor})!$。

Code:

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=2e5+10,mod=998244353;
int n,f[N],len,a[N],ans=1,fct[N],sum;

int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1)ret=1ll*ret*x%mod;
        y>>=1;x=1ll*x*x%mod;
    }
    return ret;
}

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    scanf("%d",&n);f[1]=fct[0]=1;
    for(int i=3;i<=n;i+=2)f[i]=(i-2ll)*f[i-2]%mod;
    for(int i=1;i<=n;i++)fct[i]=1ll*i*fct[i-1]%mod,scanf("%d",&a[i]);
    if(!a[1])return puts("0"),0;
    a[0]=a[n+1]=-1;len=1;
    for(int i=2;i<=n+1;i++){
        if(i<=n&&(a[i]!=a[i-1]||a[i]!=a[i+1])&&a[i]!=(i&1)){ans=0;break;}
        if(a[i]!=a[i-1])ans=1ll*ans*f[len]%mod,ans=1ll*ans*qpow(fct[len/2],mod-2)%mod,sum+=len/2,len=0;
        len++;
    }
    ans=1ll*ans*fct[sum]%mod;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：A2_Zenith (赞：1)

好的我们来做一下这个题。

首先看到这个 $i \bmod 2$ 以及这样的一个区间修改状物，不难联想到差分数组。

那么考虑对于一次操作我们做了什么。

容易发现这个操作要满足的条件其实是差分序列上 $d_{l+1}=1$，$d_r = 1$，且 $d_{l+2}$ 到 $d_r$ 全是 $0$。

然后一次操作实质上是将 $d_{l+1}\leftarrow 0$，$d_{r} \leftarrow 0$。

容易发现操作完之后的序列一定是若干段极长的 $0/1$ 连续段交替来，由上面的结论，这些个零连续段的长度是偶数，因为我们一次消灭两个一。

那考虑我们将一个长 $2l$ 的全一序列削成全零序列的方案数 $f_l$ 。

注意到，我们的第一步操作有 $2l-1$ 中操作手段，后面是 $2l-2$ 的子问题，所以 $f_l = f_{l-1} \times (2l-1)$。

设结果序列总共有 $2x$ 个零，这些个极长零连续段的长度是 $2l_1,2l_2 \cdots 2l_k$，那么方案数是 $\dbinom{x}{l_1,l_2 \cdots l_k} \prod\limits_{i=1}^kf_{l_i}$。

做完了，时间复杂度是 $\mathcal{O}(n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fir first
#define sec second
#define mp make_pair
#define endl '\n'
using namespace std;
const int maxn=5e5+7;
const int mod=998244353;
int n;
int f[maxn];
int a[maxn];
vector<int> A;
int Fac[maxn];
int iFac[maxn];
inline int qpow(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
inline void Init(){
    Fac[0]=1;
    for(int i=1;i<=n;i++)Fac[i]=Fac[i-1]*i%mod;
    iFac[n]=qpow(Fac[n],mod-2);
    for(int i=n-1;i>=0;i--)iFac[i]=iFac[i+1]*(i+1)%mod;
}
signed main(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    cin>>n;
    Init();
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=n;i>=1;i--)a[i]^=a[i-1];
    f[1]=1;
    for(int i=2;i<=n;i++)f[i]=f[i-1]*(2*i-1)%mod;
    int l=1,r=0;
    while(l<=n){
        while(a[l]&&l<=n)++l;
        if(l>n)break;
        int r=l-1;
        while((a[r+1]==0)&&r<n)++r;
        A.push_back(r-l+1);
        if((r-l+1)&1){
            cout<<0<<endl;
            cout.flush();
            return 0;
        }
        l=r+1;
    }
    int o=0;
    for(auto l:A)o+=(l>>1);
    int ans=Fac[o];
    for(auto l:A){
        int t=iFac[l>>1]*f[l>>1]%mod;
        (ans*=t)%=mod;
    }
    cout<<ans<<endl;
    cout.flush();
    return 0;
}
```

---

## 作者：NOI_O2 (赞：0)

## AT_arc189_a [ARC189A] Reversi 2 题解

### 题目大意(很长)

给定一个长度为 $N$ 的序列，初始时每个位置的值为 $i \bmod 2$（即奇数位置为 $1$，偶数位置为 $0$）。你可以进行若干次操作（也可以不操作），每次操作可以选择两个位置 $l$ 和 $r$（$l+1 < r$），将位置 $l+1$ 到 $r-1$ 的所有值改为与位置 $l$ 相同的值，前提是位置 $l$ 和位置 $r$ 的值相同，且位置 $l+1$ 到 $r-1$ 的所有值与位置 $l$ 的值不同。求有多少种操作序列可以使序列变为给定的目标序列 $A$，答案对 $998244353$ 取模。

### 解题思路

每次操作实际上是在将一段连续的、与两端不同的值替换为与一端相同的值。这说明，如果序列中存在连续的一段值相同，那么这段值可以通过若干次操作变为任意值（因为可以从两端向中间进行操作）。由于初始序列是交替的 $1$ 和 $0$，要使序列变为目标序列 $A$，必须保证 $A$ 中连续的 $1$ 或 $0$ 的个数是偶数（因为每次操作可以改变一段连续值的奇偶性）。如果存在连续的奇数个 $1$ 或 $0$，则无法通过操作达到目标序列。如果目标序列满足上述条件，那么每个连续的 $1$ 或 $0$ 段都可以独立地变为目标值，且每个段有两种选择（保持原样或通过操作改变）。因此，操作序列的个数等于每个连续段的个数的乘积。

### 一些不太重要的细节

**预处理**：读取输入，检查目标序列是否满足条件（即连续的 $1$ 或 $0$ 的个数是偶数）。

**计算答案**：如果满足条件，遍历目标序列，统计连续的 $1$ 或 $0$ 段的个数，计算乘积并对 $998244353$ 取模。

### 赛时代码
无。

---

## 作者：Richard_Whr (赞：0)

将两个序列都进行下列变换：

$$a_i \leftarrow [a_i\not=a_{i-1}]$$

令 $a_1=0$。

原始操作是选一段和两侧都不相同的连续段，然后取反。

对应到现在的序列就是选两个 $1$ 变成 $0$，要求中间不能有额外的 $1$。

然后就比较简单了，注意两个序列某位置都是 $0$ 直接删去不用考虑，两个都是 $1$ 一定不能动，将整个序列切割成若干段。设每一段有 $c_i$ 个 $1$，那么我们只需要考虑每一段的方案数以及合并的方案数。

设 $f(n)$ 表示 $c_i=n$ 的答案。

第一次可以任选一个位置删掉相邻两个 $1$，由于中间不能有 $1$，方案数为 $(n-1)$，之后的方案数为 $f(n-2)$。

有递推式： $f(n)=(n-1) \times f(n-2),f(0)=1$

合并只需要考虑两段合并即可推广，其实就是两个有序序列任意归并的方案数：$\binom{n+m}{n}$。

一个易错点是当要求序列 $s_1=0$ 的时候无解，注意特判。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,mod=998244353;
int fac[N],ifac[N];
int f[N];
int n;
int s[N],t[N];

int qmi(int a,int k)
{
	int res=1;
	while(k)
	{
		if(k&1) res=res*a%mod;
		k>>=1;
		a=a*a%mod;
	}
	return res;
}

void init(int n)
{
	f[0]=1;
	for(int i=2;i<=n;i++) f[i]=f[i-2]*(i-1)%mod;
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	ifac[n]=qmi(fac[n],mod-2);
	for(int i=n-1;i>=0;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
}

int C(int a,int b)
{
	if(a<b) return 0;
	return fac[a]*ifac[b]%mod*ifac[a-b]%mod;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n;
	init(n);
	int cnt=0,res=1,sum=0;
	s[1]=0;
	for(int i=2;i<=n;i++) s[i]=1;
	for(int i=1;i<=n;i++) cin>>t[i];
	if(t[1]==0) res=0;
	for(int i=n;i>1;i--) t[i]=(t[i]!=t[i-1]);
	t[1]=0;
	
	for(int i=1;i<=n;i++)
	{
		if(s[i]<t[i]) res=0;
		if(s[i]==t[i] && s[i]) res=res*f[cnt]%mod*C(sum/2+cnt/2,cnt/2)%mod,sum+=cnt,cnt=0;
		if(s[i]>t[i]) cnt++; 
	}
	res=res*f[cnt]%mod*C(sum/2+cnt/2,cnt/2)%mod,sum+=cnt,cnt=0;
	cout<<res<<"\n";
	
	return 0;
}
```

---

