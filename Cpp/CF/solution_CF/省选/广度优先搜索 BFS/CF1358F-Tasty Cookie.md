# Tasty Cookie

## 题目描述

由于本场题面违反互联网相关法律，不予展示原题面。

## 说明/提示

In the first example, the arrays $ A $ and $ B $ already equal, so the number of required operations $ =0 $ .

In the second example, we need to replace $ A $ with the prefix sums $ 299999 $ times and then reverse the array. Since $ 299999>2\cdot 10^5 $ , there is no need to restore the answer.

In the fourth example, you cannot get $ B $ from the $ A $ .

## 样例 #1

### 输入

```
2
5 7
5 7```

### 输出

```
SMALL
0```

## 样例 #2

### 输入

```
2
1 1
300000 1```

### 输出

```
BIG
299999```

## 样例 #3

### 输入

```
2
10 1
13 14```

### 输出

```
SMALL
6
RPPPRP```

## 样例 #4

### 输入

```
3
1 2 1
2 1 2```

### 输出

```
IMPOSSIBLE```

# 题解

## 作者：E1_de5truct0r (赞：5)

好一道人类智慧题啊，我去。

另外建议此题评紫，毕竟是 CF Div2 的 F 题外加 `*2700` 的人类智慧构造题。

## 思路

首先我们发现 $n \leq 2 \cdot 10^5$，并没有什么思路。

考虑找操作数的上限在哪里。显然，我们相邻两个操作绝对不会都是 `reverse`，所以一定隔一个就至少有一次前缀和操作。

我们发现由于 $b_i \leq 10^{12}$，所以考虑前缀和最多加多少次就超过这个上限了：

我们令 $t$ 数组是一个长度为 $n$ 的全部为 $1$ 的数组，因为这样才能让前缀和加的最慢。

我们计算这个数组进行多少次 `P` 操作，使得最大的那个数变成 $\geq 10^{12}$ 的。稍微计算可得：

- 在 $n=2$ 的时候需要 $10^{12}$ 次；

- 在 $n=3$ 的时候需要大约 $10^6$ 次；

- 在 $n=4$ 的时候大概是 $2 \times 10^4$ 次；

- ……

- 在 $n=10^5$ 的时候只有 $3$ 次了。

可见当 $n$ 很大的时候，这个次数已经接近一个常数了，我们不妨记录这个次数为 $c$。实际上，在 CF 官方题解中说了，$c$ 可以用一个公式表达出来：（但是我不会证明 /kk）

$$c=\sqrt[n-1]{10^{12} \cdot (n-1)!}$$

假设 $ans$ 是得到最终答案的操作次数。即使我们每 `P` 操作一次就 `reverse` 一次，最多也只有 $2 \times c$ 次就达到上限了。

由于 $\forall n \geq 3,n \cdot c \leq 3 \times 10^6$，所以我们这部分直接暴力即可。具体的策略是：

- 如果 $b=a$ 或者 $b=reverse(a)$，那么直接操作；

- 如果 $b$ 单调递增，那么给 $a$ 进行 `P` 操作；

- 如果 $b$ 单调递减，那么给 $a$ 进行 `R` 操作；

- 否则，输出 `Impossible`。

复杂度 $O(n \cdot c)$，可以通过 $n \geq 3$ 的所有数据。

然后考虑 $n=2$ 和 $n=1$ 的情况。

1. 当 $k=1$：

	直接判断不进行操作行不行即可。

2. 当 $k=2$：

	首先我们应该把 $a$ 和 $b$ 都排序，让他们都单调上升，方便后面进行操作。

	- 如果 $b_1=a_1$，我们直接看 $b_2-a_2 \bmod a_1$ 是否为 $0$，不为 $0$ 就是 `Impossible`，否则，就操作 $\dfrac{b_2-a_2}{a_1}$ 次 `P` 操作。
    
	- 如果 $b_1 \neq a_1$，我们考虑每次 $b_2$ 可以变成 $b_2 \bmod b_1$，这样 $b$ 数组就变成了 $[b_2 \bmod b_1,b_1]$。然后把 $b$ 数组 `swap` 一下，再进行类似的操作，直到 $b$ 和 $a$ 相等，或者能够整除等合法条件，或者 $b$ 变成 $0$，无解。
    
		容易发现，这种操作方法和求 $\gcd$ 的算法几乎一样，次数是 $O(\log w)$ 的。另外我们发现上面的 $b_1=a_1$ 的情况也可以这么解决，所以不需要额外再写一个。
        
于是我们程序的复杂度是：

$$\begin{cases}n=1: O(1)\\n=2:O(\log n \,\operatorname{or}\, \dfrac{b_2-a_2}{a_1})\\n \geq 3: O(nc)\end{cases}$$

于是这道人类智慧题就做完了，不难发现出题人的脑子一定受到了宇宙射线的开导。

---

## 作者：RainWetPeopleStart (赞：0)

记 $\mathrm{rev}(A)$ 表示反转后的 $A$ 序列。

考虑如何构造答案。

先判掉 $n=1$。

发现一个性质，就是 `P` 操作完之后序列递增，考虑从 $B$ 还原回 $A$，流程如下：

1. 如果 $B=A$ 或 $\mathrm{rev}(B)=A$ 则有解。

2. 否则，若 $B$ 单增，用 $B$ 的差分序列取代 $B$。

3. 否则，若 $\mathrm{rev}(B)$ 单增，用 $\mathrm{rev}(B)$ 的差分序列取代 $\mathrm{rev}(B)$。

4. 否则，无解，反之则重复 1-3。

此时复杂度为 $O(nt)$，$t$ 表示轮数。

因为要保证 $B$ 单增，故考虑一个序列 $S={1,1,1,\dots,1}$，对其做 $c$ 次前缀和得到 $S_c$，则 $t$ 的一个上界为最小的使得 $S_c$ 的第 $n$ 项大于 $V$ 的 $c$，可以归纳证 $S_c$ 的第 $n$ 项为 $\binom{n+c-1}{c}$，可得在 $n\ge 3$ 时这样做可接受。

否则考虑优化，第一步时对于 $A$ 判断是否有 $A_1=B_1,A_2=B_2-kB_1$，对 $\mathrm{rev}(B)$ 同理，不过这里需要额外考虑 $\mathrm{rev}(A)$ 的影响，把原来的 $A$ 换成 $\mathrm{rev}(A)$ 再 check 一遍即可。

在转化为差分序列的时候，我们应该让 $B_2=B_2\bmod B_1$（类似辗转相除），因为 $B_2=B_2-kB_1$ 的情况已经在 check 时被考虑到了，而且不这样做复杂度还是 $O(nt)$。

这样优化完后在 $n=2$ 时复杂度变为 $O(\log V+C)$，本题中 $C=2\times 10^5$。 

代码：


```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
#define lb(x) ((x)&(-(x)))
#define gp(i,j) (((i)>>(j-1))&1)
#define ppc __builtin_popcount
#define db long double
using namespace std;
const int N=2e5+10,mod=1e9+7;
const int inf=1e9+10;
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
int n,LM=2e5;
ll a[N],b[N],c[N];
ll opt=0;
vector<char> opr;
bool eq(ll *arr1,ll *arr2){
    for(int i=1;i<=n;i++){
        if(arr1[i]!=arr2[i]) return 0;
    }return 1;
}
bool chk(ll *arr){
    for(int i=2;i<=n;i++){
        if(arr[i-1]>=arr[i]) return 0;
    }for(int i=1;i<=n;i++){
        if(arr[i]<=0) return 0;
    }return 1;
}
void rev(ll *arr){
    for(int i=1;i<=n;i++){
        if(i<n+1-i) swap(arr[i],arr[n+1-i]);
    }
}
void modify(ll *arr,int op=0){
    if(n==2){
        ll cnt=arr[2]/arr[1];
        opt+=cnt;
        if(op) for(int i=1;i<cnt;i++) opr.push_back('P');
        arr[2]%=arr[1];
    }else{
        for(int i=n;i>=1;i--) arr[i]-=arr[i-1];
        opt++;
    }
}
bool chkeq(ll *arr,int op=0){
    if(n==2){
        //cout<<arr[1]<<endl;
        if(a[1]==arr[1]&&arr[2]>=a[2]&&(arr[2]-a[2])%a[1]==0){
            ll cnt=(arr[2]-a[2])/a[1];opt+=cnt;
            if(op){
                for(int i=1;i<=cnt;i++) opr.push_back('P');
            }return 1;
        }rev(a);//cout<<arr[1]<<endl;
        if(a[1]==arr[1]&&arr[2]>=a[2]&&(arr[2]-a[2])%a[1]==0){
            ll cnt=(arr[2]-a[2])/a[1];opt+=cnt;//cout<<arr[1]<<endl;
            if(op){
                for(int i=1;i<=cnt;i++) opr.push_back('P');
                opr.push_back('R');
            }
            rev(a);return 1;
        }//cout<<"OK"<<endl;
        return 0;
    }else{
        if(eq(a,arr)) return 1;
        else return 0;
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    if(n==1){
        if(a[1]==b[1]){
            cout<<"SMALL"<<endl;
            cout<<0<<endl<<endl;
        }else{
            cout<<"IMPOSSIBLE"<<endl;
        }
    }else{
        for(int i=1;i<=n;i++) c[i]=b[i];
        while(1){
            //for(int i=1;i<=n;i++) cout<<c[i]<<' ';cout<<endl;
            if(chkeq(c)) break;rev(c);
            //for(int i=1;i<=n;i++) cout<<c[i]<<' ';cout<<endl;
            if(chkeq(c)) break;rev(c);
            if(chk(c)){
                modify(c);
            }else{
                rev(c);
                if(!chk(c)){
                    opt=-1;break;
                }modify(c);
            }
        }
        if(opt==-1){
            cout<<"IMPOSSIBLE"<<endl;
        }else if(opt>LM){
            cout<<"BIG"<<endl;cout<<opt<<endl;
        }else{
            cout<<"SMALL"<<endl;
            while(1){
                //cout<<opr.size()<<endl;
                if(chkeq(b,1)) break;rev(b);
                opr.push_back('R');
                if(chkeq(b,1)) break;rev(b);
                opr.pop_back();
                if(chk(b)){
                    modify(b,1);
                    opr.push_back('P');
                }else{
                    rev(b);
                    opr.push_back('R');
                    opr.push_back('P');
                    modify(b,1);
                }
            }cout<<opr.size()<<endl;
            reverse(opr.begin(),opr.end());
            for(auto ed:opr) cout<<ed;cout<<endl;
        }
    }
    cout.flush();
    return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

标题有点神金，最近精神状态欠佳。

感觉这个题就完全无法下手哈！这种时候我们可以试着倒着构造，从最终状态变成初始状态。这样有什么好处呢？现在我们可以做的操作变成了差分和翻转整个序列，而差分后的序列必须依旧全是正数。这意味着整个序列必须单调递增或单调递减。

所以我们的操作只可能有以下四种情况（用 $R(a)$ 表示反转后的 $a$ 序列）：

- $a=b$：直接结束。

- $a=R(b)$：反转一次后直接结束。

- $b$ 单调递增：做一次差分。

- $b$ 单调递减：反转一次后做一次差分。

如果不满足四个条件中的任意一个，则必定无解。模拟这个过程即可，最终的真实操作序列需要反过来。

分析一下时间复杂度：我们发现操作次数的量级应该在 $\mathcal O(V^{\frac{1}{n-1}})$ 量级左右，也就是说复杂度为 $\mathcal O(nV^{\frac{1}{n-1}})$。这在 $n\ge 3$ 时显然是可以接受的。

于是我们只剩下 $n=1$ 和 $n=2$ 的 casework。$n=1$ 显然只需要判断 $a_1=b_1$ 是否成立，$n=2$ 可以用类似欧几里得算法求 gcd 的过程辗转相除，将 $a,b$ 都排序后，如果 $a_1=b_1$，且 $b_2-a_2\equiv 0\pmod {a_1}$，那么直接构造出来了。否则递归到 $(b_2\bmod b_1,b_1)$ 后继续做。

注意细节：$n=2$ 的时候，即使有解也不一定是 `BIG`。为了不在递归过程中求解递归序列，可以把 $n=2$ 也放到 $n\ge 3$ 的暴力里面跑 $2\times 10^6$ 轮，如果没有得到答案就再做递归。

感觉很不简单。咋是 *2700？

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=2e5+9;
ll n,a[N],b[N],tmp[N];
vector<char>ans;
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,1,n)a[i]=read();
    rep(i,1,n)b[i]=read(),tmp[i]=b[i];
    if(n==1){
        if(a[1]==b[1])return puts("SMALL\n0"),0;
        puts("IMPOSSIBLE");
        return 0;
    }
    rep(j,1,2000000){
        ll fl=1;
        rep(i,1,n)fl&=(a[i]==b[i]);
        if(fl)break;
        fl=1;
        rep(i,1,n)fl&=(a[i]==b[n-i+1]);
        if(fl){
            reverse(b+1,b+n+1);
            ans.push_back('R');
            break;
        }
        fl=1;
        rep(i,1,n-1)fl&=(b[i]<=b[i+1]);
        if(fl){
            ans.push_back('P');
            per(i,n,2)b[i]-=b[i-1];
            continue;
        }
        fl=1;
        rep(i,1,n-1)fl&=(b[i]>=b[i+1]);
        if(fl){
            ans.push_back('R'),ans.push_back('P');
            reverse(b+1,b+n+1);
            per(i,n,2)b[i]-=b[i-1];
            continue;
        }
        return puts("IMPOSSIBLE"),0;
    }
    ll fl=1;
    rep(i,1,n){
        if(a[i]!=b[i])fl=0;
    }
    if(fl){
        ll cnt=0;
        for(char c:ans)cnt+=(c=='P');
        if(cnt>200000)return puts("BIG"),write(cnt),0;
        puts("SMALL");
        reverse(ans.begin(),ans.end());
        write(ans.size()),putchar('\n');
        for(char c:ans)putchar(c);
        putchar('\n');
        return 0;
    }
    ll ans=0;
    if(a[1]>a[2])swap(a[1],a[2]);
    rep(i,1,n)b[i]=tmp[i];
    while(b[1]>0&&b[2]>0){
        if(b[1]>b[2])swap(b[1],b[2]);
        if(b[1]==a[1]&&(b[2]-a[2])%a[1]==0){
            puts("BIG");
            write(ans+(b[2]-a[2])/a[1]);
            return 0;
        }
        ans+=b[2]/b[1],b[2]%=b[1];
    }
    puts("IMPOSSIBLE");
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

