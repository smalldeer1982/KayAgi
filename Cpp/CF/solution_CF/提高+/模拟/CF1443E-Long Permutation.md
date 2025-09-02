# Long Permutation

## 题目描述

A permutation is a sequence of integers from $ 1 $ to $ n $ of length $ n $ containing each number exactly once. For example, $ [1] $ , $ [4, 3, 5, 1, 2] $ , $ [3, 2, 1] $ — are permutations, and $ [1, 1] $ , $ [4, 3, 1] $ , $ [2, 3, 4] $ — no.

Permutation $ a $ is lexicographically smaller than permutation $ b $ (they have the same length $ n $ ), if in the first index $ i $ in which they differ, $ a[i] < b[i] $ . For example, the permutation $ [1, 3, 2, 4] $ is lexicographically smaller than the permutation $ [1, 3, 4, 2] $ , because the first two elements are equal, and the third element in the first permutation is smaller than in the second.

The next permutation for a permutation $ a $ of length $ n $ — is the lexicographically smallest permutation $ b $ of length $ n $ that lexicographically larger than $ a $ . For example:

- for permutation $ [2, 1, 4, 3] $ the next permutation is $ [2, 3, 1, 4] $ ;
- for permutation $ [1, 2, 3] $ the next permutation is $ [1, 3, 2] $ ;
- for permutation $ [2, 1] $ next permutation does not exist.

You are given the number $ n $ — the length of the initial permutation. The initial permutation has the form $ a = [1, 2, \ldots, n] $ . In other words, $ a[i] = i $ ( $ 1 \le i \le n $ ).

You need to process $ q $ queries of two types:

- $ 1 $ $ l $ $ r $ : query for the sum of all elements on the segment $ [l, r] $ . More formally, you need to find $ a[l] + a[l + 1] + \ldots + a[r] $ .
- $ 2 $ $ x $ : $ x $ times replace the current permutation with the next permutation. For example, if $ x=2 $ and the current permutation has the form $ [1, 3, 4, 2] $ , then we should perform such a chain of replacements $ [1, 3, 4, 2] \rightarrow [1, 4, 2, 3] \rightarrow [1, 4, 3, 2] $ .

For each query of the $ 1 $ -st type output the required sum.

## 说明/提示

Initially, the permutation has the form $ [1, 2, 3, 4] $ . Queries processing is as follows:

1. $ 2 + 3 + 4 = 9 $ ;
2. $ [1, 2, 3, 4] \rightarrow [1, 2, 4, 3] \rightarrow [1, 3, 2, 4] \rightarrow [1, 3, 4, 2] $ ;
3. $ 1 + 3 = 4 $ ;
4. $ 4 + 2 = 6 $

## 样例 #1

### 输入

```
4 4
1 2 4
2 3
1 1 2
1 3 4```

### 输出

```
9
4
6```

# 题解

## 作者：AsunderSquall (赞：5)

比赛时没做出来，现在来补课。  
![](https://cdn.luogu.com.cn/upload/image_hosting/2iwkk7r8.png)
[官方题解通道](https://codeforces.com/blog/entry/84298)  

# 题意
你需要维护一个长度为$n$的排列$P$，和$q$次操作  
- $1 \ l \ r$ 查询$\sum_{i=l}^r P_i$  
- $2 \ x$ 将$P$替换成下$x$个排列  

$n,q\leq2\times10^5,x \leq 10^5$  

# 题解  
思路：每次$2$操作时只需要将$sum+=x$，查询操作的时候考虑第$sum+1$个排列的情况即可。

注意到$x$比较小，就算所以操作都是$2$，最终的和也不超过$2\times 10^{10}$（官方题解里说的是$10^{10}$，不知道为什么，影响不大）  
我们又发现$15!>>2\times 10^{10}$，也就是说，在过程中会改变的数在最后$15$个之内，前面的数都不会变。  
那么我们查询的时候只需要将后$15$个的情况处理出来，前面的都是一样的。  
考虑怎么处理后$15$个的信息。  
我们可以逆康托展开处理。  
关于康托展开，可以看看[这一个](https://www.luogu.com.cn/problem/P5367)

用线段树优化的康托展开和逆康托展开时间复杂度可以达到$O(n\ logn)$，但是由于这里只要算出$15$个数，所以$O(n^2)$暴力展开即可
# 代码
```cpp

#include<bits/stdc++.h>
#define int long long 
#define rd(x) x=read()
using namespace std;
const int N=2e5+5;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int sum,n,q;
int a[16];
int P[16];
int fac[16];
bool vis[16];
void get(int sum)
{
    //求出长度为15的第sum+1个排列
    long long res=0;
    for(int i=1;i<n;i++)
        res=(res+a[i])*(n-i);
    for (int i=1;i<=15;i++)
    {
        a[i]=sum/fac[15-i];
        sum%=fac[15-i];
    }
    memset(vis,0,sizeof(vis));
    for (int i=1;i<=15;i++)
    {
        int cnt=0;
        for (int j=1;j<=15;j++)
        {
            if (!vis[j]) cnt++;
            if (cnt==a[i]+1)
            {
                P[i]=j;
                vis[j]=1;
                break;
            }
        }
    }
}
signed main()
{
    rd(n);rd(q);
    fac[0]=1;
    for (int i=1;i<=15;i++) fac[i]=fac[i-1]*i;
    while (q--)
    {
        int opt;
        rd(opt);
        if (opt==1)
        {
            int l,r;
            rd(l);rd(r);
            //前面1-(n-15)个数分别为1,2,3...(n-15)
            //后面(n-14)->n不一样
            int ans=0;
            get(sum);
            if (r>n-15)
            {
                if (l>n-15)
                {
                    //全在后15个里面
                    for (int i=l-n+15;i<=r-n+15;i++) ans+=P[i];
                    ans+=(r-l+1)*(n-15);
                }
                else
                {
                    //l->(n-15)+(n-14)->r
                    ans+=(l+n-15)*(n-14-l)/2;
                    for (int i=1;i<=r-n+15;i++) ans+=P[i];
                    ans+=(r-n+15)*(n-15);
                }
            }
            else ans=(l+r)*(r-l+1)/2;
            printf("%lld\n",ans);
        }
        if (opt==2) {int x;rd(x);sum+=x;}
    }
}
```

---

## 作者：shinzanmono (赞：0)

首先使用计算器可以知道 $14!>2\times 10^{10}$，所以操作二最多改变最后面 $B=14$ 个位置。使用 Cantor 展开可以在 $O(B^2)$ 内解决求第 $x$ 个排列。

然后我们预处理出前面的答案即可。时间复杂度可以做到 $O(qB^2)$。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using ll=long long;
const int sz=2e5+10;
struct Query{int l,r,id;};
std::vector<Query>query[sz];
ll ans[sz],t[sz];
int p[17],sum[17];
std::vector<int>V;
ll fact(int n){
    if(n<=1)return 1;
    return n*fact(n-1);
}
void find(ll rnk){
    int n=V.size();
    std::vector<int>cv(V);
    ll f=fact(n-1);
    for(int i=1;i<n;f/=n-i,i++)p[i]=cv[rnk/f],cv.erase(cv.begin()+rnk/f),rnk%=f;
    p[n]=cv[0];
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+p[i];
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,q;
    std::cin>>n>>q;
    int k=1,qq=0;
    for(int i=1,op,x,y;i<=q;i++){
        std::cin>>op>>x;
        if(op==2)++k,t[k]=t[k-1]+x;
        else std::cin>>y,query[k].push_back(Query{x,y,++qq});
    }
    int b=std::max(1,n-13);
    for(int i=b;i<=n;i++)V.push_back(i);
    for(int i=1;i<=k;i++){
        for(auto &Q:query[i]){
            int &l=Q.l,&r=Q.r;
            if(l<b)ans[Q.id]=(std::min(r,b-1)-l+1ll)*(std::min(r,b-1)+l)/2;
            if(r<b)l=1,r=0;
            else l=std::max(1,l-b+1),r=r-b+1;
        }
    }
    for(int i=1;i<=k;i++){
        find(t[i]);
        for(auto Q:query[i])ans[Q.id]+=sum[Q.r]-sum[Q.l-1];
    }
    for(int i=1;i<=qq;i++)std::cout<<ans[i]<<"\n";
    return 0;
}

```

---

## 作者：lfxxx (赞：0)

不难发现排列的排名不会很大，只有 $2 \times 10^{10}$ 左右，也就是说你的排列一定是前面一段 $p_i = i$ 后面一段不超过 $15$ 的任意组合，后面的一段可以逆康托展开暴力求暴力算，前面的一段查询时直接等差数组求和即可。更多细节看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+114;
int fac[16];
int pre,rk,n,q;
vector<int> D,f,a;
void work(){
	pre=0;
	int k=rk-1;
	fac[0]=1;
	for(int i=1;i<=15;i++) fac[i]=fac[i-1]*i;
	for(int i=1;i<=15;i++){
		pre=n-i;
		if(fac[i]>k) break;
	}
	D.clear();
	f.clear();
	a.clear();
	for(int i=pre+1;i<=n;i++) D.push_back(i),f.push_back(k/fac[n-i]),k%=fac[n-i];
	for(int x:f){
		a.push_back(D[x]);
		D.erase(find(D.begin(),D.end(),a.back()));
	}
	//现在 f 数组处理出来了	
}
int ask(int l,int r){
	int R=min(r,pre);
	int ans=0;
	if(l<=R) ans+=(l+R)*(R-l+1)/2;
	for(int i=max(R,l-1)+1;i<=r;i++){
		ans+=a[i-pre-1];
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	rk=1;
	cin>>n>>q;
	work();
	while(q--){
		int opt;
		cin>>opt;
		if(opt==1){
			int l,r;
			cin>>l>>r;
			cout<<ask(l,r)<<'\n';
		}else{
			int x;
			cin>>x;
			rk+=x;
			work();
		}
	}
	return 0;
}
```


---

## 作者：cosf (赞：0)

## [CF1443E](https://www.luogu.com.cn/problem/CF1443E)

不一定有用的前置知识：逆[康托展开](https://www.luogu.com.cn/problem/P5367)。

我们知道，长度为 $n$ 的排列有 $n!$ 个。在本题中，最多有 $2 \times 10^5$ 次操作 $2$，每次操作 $2$ 最多变成下 $10^5$ 个排列。也就是说，最多只会访问到下 $2\times 10^{10}$ 个排列。而 $n=14$ 时 $n!$ 就已经达到 $8 \times 10^{10}$，所以，无论怎么操作，改变的只有最后的 $14$ 个数字。

对于操作 $2$，我们记录它的排列次序即可。

对于操作 $1$，如果 $[l, r]$ 与 $[n - 13, n]$ 没有交集，等差数列求和即可；如果有，用类似逆康托展开的方式求出最后 $14$ 个的具体数值，暴力算这一段的和即可，其他不变。当然，如果 $n \le 14$ 要特殊处理，但思路一样。

时间复杂度 $O(q)$。常数主要源于求 $1 \sim 14$ 的排列的暴力算法。

给一下具体的公式。这些公式不难推。

假设 $n \gt 14$，有如下公式：

如果 $[l, r] \cup [n - 13, n] = \varnothing$，则答案 $sum = \frac{(l + r)(r - l + 1)}{2}$。

否则记 $val_i$ 表示 $1 \sim \min\{14, n\}$ 的第 $p$（即操作 $2$ 中 $x$ 的累加和）中排列。

若 $l \lt n - 13$，则 

$$sum = \frac{(l + n - 14)(n - 13 - l)}{2} + (r - n + 14)(n - 14) + \sum_{i = 1}^{r - n + 14}val_i$$

否则

$$
sum = \frac{(r - l + 1)(n - 14)}{2} + \sum_{i = l - n + 14}^{r - n + 14}val_i
$$

若 $n \le 14$，则 $sum = \sum_{i = l - n + 14}^{r - n + 14}val_i$。

## 代码

```cpp
#include <iostream>
using namespace std;

using ll = long long;

#define MAXN 25

ll n, m;

ll p;

int val[MAXN];
ll fac[MAXN];
bool use[MAXN];

void gp(int mx)
{
    for (int i = 1; i <= mx; i++)
    {
        use[i] = false;
    }
    ll cp = p;
    for (int i = 1; i <= mx; i++)
    {
        ll x = (cp / fac[mx - i]);
        cp -= fac[mx - i] * x;
        x++;
        ll j = 0;
        while (true)
        {
            j++;
            if (!use[j])
            {
                x--;
            }
            if (!x)
            {
                break;
            }
        }
        use[j] = true;
        val[i] = j;
    }
}

int main()
{
    cin >> n >> m;
    fac[0] = 1;
    for (int i = 1; i <= 14; i++)
    {
        fac[i] = fac[i - 1] * i;
    }
    if (n >= 14)
    {
        while (m--)
        {
            int op;
            cin >> op;
            if (op == 1)
            {
                ll l, r;
                cin >> l >> r;
                if (r <= n - 14)
                {
                    cout << (l + r) * (r - l + 1) / 2 << endl;
                }
                else
                {
                    gp(14);
                    ll sum = 0;
                    if (l <= n - 14)
                    {
                        sum = (l + n - 14) * (n - 13 - l) / 2 + (r - n + 14) * (n - 14);
                        for (int i = 1; i <= r + 14 - n; i++)
                        {
                            sum += val[i];
                        }
                    }
                    else
                    {
                        sum = (r - l + 1) * (n - 14);
                        for (int i = l + 14 - n; i <= r + 14 - n; i++)
                        {
                            sum += val[i];
                        }
                    }
                    cout << sum << endl;
                }
            }
            else
            {
                ll x;
                cin >> x;
                p += x;
            }
        }
    }
    else
    {
        while (m--)
        {
            int op;
            cin >> op;
            if (op == 1)
            {
                ll l, r;
                cin >> l >> r;
                gp(n);
                ll sum = 0;
                for (int i = l; i <= r; i++)
                {
                    sum += val[i];
                }
                cout << sum << endl;
            }
            else
            {
                ll x;
                cin >> x;
                p += x;
            }
        }
    }
    return 0;
}

```


---

## 作者：intel_core (赞：0)

因为 $15!=1,307,674,368,000$，所以只有后 $15$ 位会改变。

所以只需要每次把后 $15$ 位的康托展开次序记录一下，再反展开就行。

一共 $2\times 10^5$ 次修改，只需要单次操作 $O(15^2)$ 就行。

我用的这种实现其实可以做 $x$ 很大并且初始排列不同的情况。。

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
const int NR=2e5+10;
#define int long long
int n,q,a[NR],s[NR],fac[20];

int c[NR];
int lowbit(int x){
	return x&(-x);
}
void add(int x,int y){
	while(x<=n){
		c[x]+=y;
		x+=lowbit(x);
	}
}
int sum(int x){
	int res=0;
	while(x){
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
} 
int calc(int l,int r){return sum(r)-sum(l-1);}

int query(int pos){
	int res=0;
	for(int i=n;i>=pos;i--)
		res+=calc(1,a[i])*fac[n-i],add(a[i],1);
	for(int i=pos;i<=n;i++)add(a[i],-1);
	return res;
}
int v[NR],len,cnt[NR];
void rebuild(int pos,int x){
	len=0;
	for(int i=pos;i<=n;i++)v[++len]=a[i];
	for(int i=1;i<=len;i++)cnt[i]=i-1;
	sort(v+1,v+1+len);
	for(int i=pos;i<=n;i++){
		int k=x/fac[n-i];x-=k*fac[n-i];
		for(int j=1;j<=len;j++)
			if(v[j]&&cnt[j]==k){
				a[i]=v[j];v[j]=0;
				for(int l=j+1;l<=len;l++)cnt[l]--;
				break;
			}
	}
}

signed main(){
	fac[0]=1;
	for(int i=1;i<=15;i++)fac[i]=fac[i-1]*i;
	cin>>n>>q;
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(a[i]=i);
	while(q--){
		int opt;scanf("%lld",&opt);
		if(opt==1){
			int l,r;scanf("%lld%lld",&l,&r);
			printf("%lld\n",s[r]-s[l-1]);
		}
		else{
			int x,pos=n,now=n,cnt=1;scanf("%lld",&x);
			while(cnt<=x){
				pos=now;
				cnt+=calc(a[now],n)*fac[n-now];
				add(a[now],1);now--;
			}
			for(int i=pos;i<=n;i++)add(a[i],-1);
			rebuild(pos,query(pos)+x);
			for(int i=pos;i<=n;i++)s[i]=s[i-1]+a[i];
		}
	}
	return 0;
}








```

---

## 作者：tommymio (赞：0)

很 $\text{Naive}$ 的一道题啊。

看到这种和全排列编号相关的问题，首先想到 $\text{Cantor Expansion}$。$\text{Cantor Expansion}$ 无非就是两个性质，一个逆序对，一个进制。

而将排列映射到一个编号，实则是将一个排列映射到一个进制串。这是康托展开的实质，即建立自然数域到序列的映射，若自然数过大，可以采用进制串的形式表示。明白了这几点，这题真的很一眼（

有一个非常容易想到的思路，把排列通过 $\text{Cantor Expansion}$ 变为进制串，但不求出这个进制串具体的值。因为我们可以直接在这个进制串上 $+x$。那么，我们维护这个进制串，并在查询区间和的时候将这个进制串转为排列即可。但是这样似乎会 $\text{TLE}$？我们观察到，极限数据下只会求编号 $2\times 10^{10}$ 对应的排列。而这个排列，事实上与初始给出的排列，最多只相差最后的 $15$ 位。$14!\leq 2\times 10^{10}$，在进制串上 $0!\sim 14!$ 就是 $15$ 位，这是非常显然的。

所以，我们只需要维护末 $15$ 位的进制串的变化，由于初始给出的是一个顺序排列，除去这 $15$ 位的部分在进制串中必然都是 $0$。

至于通过进制串得到一个排列，其实就是根据逆序对还原排列。直接用 $\text{BIT}$ + 二分或者权值线段树就好。前者是 $O(\log ^2)$ 的而后者是一只 $\log$ 的，我太懒了只写了两只 $\log$（

UPDATE：由于只需要 $15$ 位，直接暴力维护前缀和就好了（$\text{DS}$ 学傻的我只能当场爬走 

```cpp
#include<cstdio>
typedef long long ll;
int s[200005],a[200005],A[200005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline void add(int n,int x,int val) {for(;x<=n;x+=x&(-x)) s[x]+=val;} 
inline int ask(int x) {int res=0; for(;x;x-=x&(-x)) res+=s[x]; return res;}
inline ll getAns(int n,int R) {
    ll res=(n-15+1)*1ll*(n-15)/2;
    if(R>n-15) {
        res=(n-15+1)*1ll*(n-15)/2;
        for(register int i=n-14;i<=R;++i) res+=a[i];
    } 
    else {
        res=(1+R)*1ll*R/2;
    }
    return res;
}
inline int find(int n,int k) {
    int l=1,r=n,res=1;
    while(l<=r) {
        int mid=l+r>>1;
        if(ask(mid)>=k) r=mid-1,res=mid;//find the most left index
        else l=mid+1;
    }
    return res;
}
int main() {
    int n=read(),T=read();
    while(T--) {
        int op=read();
        if(op==1) {
            int l=read(),r=read();
            if(n<=15) {
                for(register int i=1;i<=n;++i) s[i]=0;
                for(register int i=1;i<=n;++i) add(n,i,1);
                for(register int i=1;i<=n;++i) {
                    int x=find(n,A[i]+1);
                    add(n,x,-1); a[i]=x;
                }
                ll sum=0;
                // for(register int i=1;i<=n;++i) printf("%d ",a[i]); printf("\n");
                for(register int i=l;i<=r;++i) sum+=a[i];
                printf("%lld\n",sum);
            }
            else {
                for(register int i=n-14;i<=n;++i) s[i]=0;
                for(register int i=n-14;i<=n;++i) add(n,i,1);
                for(register int i=n-14;i<=n;++i) {
                    int x=find(n,A[i]+1);
                    add(n,x,-1); a[i]=x;
                }
                printf("%lld\n",getAns(n,r)-getAns(n,l-1));
            }
        }
        else {
            int x=read();
            A[n]+=x;
            for(register int i=n;i>=2&&A[i]/(n-i+1)!=0;--i) {
                A[i-1]+=A[i]/(n-i+1);
                A[i]%=(n-i+1);
            }
        }
    }
    return 0;
}
```




---

## 作者：Mint_Flipped (赞：0)

这道题无非两个操作：一个求区间和另一个改变一段区间内的数。很明显我们可以用一个线段树来维护，或是树状数组。变成下一个排列很明显是要单点修改，那么那么大的数据范围不会炸吗？很明显，不会。

操作范围1e5，操作次数2e5，乘起来是2e10，我们算一下排列，到13位就超过了这个数，所以我们取14位。即：我们修改排列的后14位就可以题目的预设。

为什么不是13位？假设我们这个排列后13位已经处于最后几个排列了，所以你换成更后面的排列就炸了。所以取14位。

怎么实现？康托展开+逆康托展开，计算后14位（不足的话取其所有位数）的康托展开值，然后加上要求的后几位这个值，逆康托展开得到后14位排列，最后线段单点修改（最多14位修改，不会炸的）。

代码如下：
```cpp
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first
#define sec(a) a->second
const int inf=0x3f3f3f3f;
const int maxn=2e5+5;
const int mod=1e9+7;
const double eps=1e-7;
int n,m,l,r,cnr;
int sum[20],num[20];
ll FAC[20]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,87178291200};
ll lazy[maxn<<2],t[maxn<<2],a[maxn],b[maxn];
bool vis[20];
inline void push_up(int k){
    t[k]=t[k<<1]+t[k<<1|1];
}
void build_tree(int k,int l,int r){
    lazy[k]=0;
    if(l==r){
        t[k]=a[l];
        return ;
    }
    int mid=(l+r)>>1;
    build_tree(k<<1,l,mid);
    build_tree(k<<1|1,mid+1,r);
    push_up(k);
}
void update(int L,int k,int l,int r,ll val){
    if(r<L||l>L) return;
    if(l==r&&l==L){
        t[k]+=val;
        return ;
    }
    int mid=(l+r)>>1;
    update(L,k<<1,l,mid,val);
    update(L,k<<1|1,mid+1,r,val);
    push_up(k);
}
ll query(int L,int R,int k,int l,int r){
    ll ans=0;
    if(L<=l&&r<=R){
        return t[k];
    }
    int mid=(l+r)>>1;
    if(L<=mid)
        ans+=query(L,R,k<<1,l,mid);
    if(R>mid)
        ans+=query(L,R,k<<1|1,mid+1,r);
    return ans;
}
ll cantor(int x){
    ll res=0;
    int cnr=0;
    for(int i=l;i<=r;++i){
        x--;
        res+=(ll)sum[++cnr]*FAC[x];
    }
    return res;
}
void decantor(ll x,int y){
    int z=r-l+1;
    x+=(ll)y;
    sort(num+1,num+1+cnr);
    mem(vis,0);
    for(int i=l;i<=r;++i){
        z--;
        int pp=1+x/FAC[z];
        x=x%FAC[z];
        for(int j=1;j<=r-l+1;++j){
            if(!vis[j]) pp--;
            if(!pp) {pp=j; break;}
        }
        vis[pp]=1;
        b[i]=num[pp]-a[i];
        a[i]=num[pp];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    fo2(i,n) a[i]=(ll)i;
    build_tree(1,1,n);
    fo2(i,m){
        int x,y,z;
        scanf("%d",&x);
        if(x==1){
            scanf("%d%d",&y,&z);
            ll ans=query(y,z,1,1,n);
            printf("%lld\n",ans);
        }
        else{
            scanf("%d",&y);
            mem(sum,0);
            r=n,l=max(1,n-14);
            cnr=0;
            mem(vis,0);
            for(int i=l;i<=r;++i){
                num[++cnr]=a[i];
                for(int j=l;j<=r;++j){
                    if(!vis[j-l+1]&&a[i]>a[j])
                    sum[cnr]++;
                }
                vis[cnr]=1;
            }
            ll Can=cantor(r-l+1);
            decantor(Can,y);
            for(int i=l;i<=r;++i){
                update(i,1,1,n,b[i]);
            }
        }
    }
    return 0;
}

```


---

## 作者：Theophania (赞：0)

由于 $q \le 2\times 10^5$，$x \le q\times 10^5$，最后产生的最大的排列也不会超过 $2 \times 10^{10}$，而 $15!$ 就超过了 $2 \times 10^{10}$，也就是说最多只有 $15$ 位会产生改变。

所以只需要维护前缀和，修改的时候把排列算出来暴力修改最后那几位就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
template <typename T>
inline void read(T &x)
{
    T data = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        data = (data << 3) + (data << 1) + ch - '0';
        ch = getchar();
    }
    x = f * data;
}
template <typename T, typename... Args>
inline void read(T &t, Args &... args)
{
    read(t);
    read(args...);
}

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int maxn = 2e5 + 9;
const ll mod = 998244353;
ll frac[20];
ll s[maxn];
bool vis[maxn];
signed main()
{
    int n, q;
    read(n, q);
    frac[0] = 1;
    for (ll i = 1; i <= 16; ++i)
        frac[i] = frac[i - 1] * i;
    int st = max(1, n - 15);
    ll cnt = 1;
    for (ll i = 1; i <= n; ++i)
        s[i] = s[i - 1] + i;
    int op, l, r, x;
    while (q--)
    {
        read(op);
        if (op == 1)
        {
            read(l, r);
            printf("%lld\n", s[r] - s[l - 1]);
        }
        else
        {
            read(x);
            cnt += x;
            ll now = cnt;
            for (int i = st; i <= n; ++i)
                vis[i] = false;
            for (int i = st; i < n; ++i)
            {
                ll tmp = 0;
                for (int j = st; j <= n; ++j)
                {
                    if (!vis[j])
                    {
                        tmp += frac[n - i];
                        if (tmp >= now)
                        {
                            now -= tmp - frac[n - i];
                            s[i] = s[i - 1] + j;
                            vis[j] = true;
                            break;
                        }
                    }
                }
            }
            for (int i = st; i <= n; ++i)
                if (!vis[i])
                    s[n] = s[n - 1] + i;
        }
    }
    return 0;
}
```


---

