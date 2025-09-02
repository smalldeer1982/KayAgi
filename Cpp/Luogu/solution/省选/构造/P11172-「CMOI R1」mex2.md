# 「CMOI R1」mex2

## 题目背景

小 U 对于从一个集合映射到一个数的函数很感兴趣，而 $\text{mex}$ 是一个很好的例子。

$\text{mex}(S)$ 指的是在集合 $S$ 中没有出现过的最小非负整数。

## 题目描述

多组数据。

每组数据，给定 $c$，要求构造序列 $a_1,a_2,...,a_n\in [0,2\times 10^9]$ 满足 

$$\sum\limits_{1\le l\le r\le n}\text{mex}(a_l,a_{l+1},...,a_r)=c$$


其中要求 $1\le n\le3000$。可以证明在该题的数据范围内如果存在解，则在 $1\le n\le 3000$ 时一定存在解。

## 说明/提示

### 样例解释

对于样例 #1：只有 $\text{mex}(a_7)=1$，且 $∀1\le i\le6$ 有 $\text{mex}(a_i,a_{i+1},...,a_7)=2$，因而总和为 $13$。

### 数据范围

$id$ 为 $\text{subtask}$ 编号。

|$id$|特殊性质|分数|$id$|特殊性质|分数|
|-:|-:|-:|-:|-:|-:|
|$1$|$c\le3\times10^3$|$3$|$5$|$c\le8\times 10^6$|$10$|
|$2$|$c\le6\times 10^3$|$7$|$6$|$c\le1\times 10^8$|$10$|
|$3$|$c\le8\times10^4$|$10$|$7$|$c\le1\times 10^9$|$25$|
|$4$|$c\le4\times 10^6$|$15$|$8$|$c\le2\times 10^9$|$20$|

对于 $100\%$ 的数据，$T\le 310$，$0\le c\le 2\times 10^9$。


## 样例 #1

### 输入

```
4
13
25
32
0```

### 输出

```
7
1 9 1 9 8 1 0
13
1 1 4 5 1 4 1 9 1 9 8 1 0
8
1 2 3 9 0 7 3 8
7
1 2 3 9 7 3 8
```

# 题解

## 作者：Otomachi_Una_ (赞：3)

神题。

考虑我们要不每个数都是 $\infty$，要么从 $0,1,2,3,\dots$ 每个数只出现一次。

考虑这种构造：$0,1,2,3,\dots,k,\infty,\dots,\infty,k+1,\infty,\dots,\infty$。

这种构造能解决 $c\leq \mathcal O(n^2)$ 的情况。

考虑更牛一点，我们把 $0$ 挪到大概 $t=\frac n3$ 的位置。然后你发现每次增量都是 $t$ 的倍数，那我们强制在 $a_n$ 填最大，再左边再填一个更大的就能得到余数了。

大概是这样子的：$\infty\dots\infty,k+1,\infty\dots,\infty,0,1,2,\dots,k-1,\infty,\dots,\infty,k$。

这样子构造就是 $\mathcal O(n^3)$。

---

## 作者：Argon_Cube (赞：2)

Official Solution.

一个巨大找规律做法。如果你不知道结论怎么来的就是找规律找出来的，如果你发现哪种情况没讨论应该是没有这种情况。

发现 $n\leq 3000$ 与 $c\leq 2\times 10^9$ 的数量级差别很大，先考虑能不能构造出超过 $c_{\max}$ 的答案。

考虑如下构造，将 $0$ 放在中间，奇数放在一边，偶数放在另一边，形成一个单谷的数组：$\cdots,7,5,3,1,0,2,4,6,\cdots$

容易发现这样做，若取前 $n$ 个数可以得到的答案是 $f(n)=\begin{cases}\frac 23n^3+\frac 32n^2+\frac 56n&2|n\\\frac 23n^3+\frac 12n^2-\frac 16n&\text{otherwise}\end{cases}$，当 $n=3000$ 时 $c\approx 2.2\times 10^9$，当 $c\leq2\times 10^9$ 时 $n\leq 2883$。

为了方便下文讨论，我们认为一开始未经调整的数列 $a$ 第一个数是 $n-1$，如果不满足该条件将数列翻转即可。

我们考虑找到 $f(n)\geq c$ 的最小的 $n$，并通过交换 $a$ 中数的顺序使得当前的答案 $c_0$ 减小到 $c$。可以找规律发现，每次交换 $n-1$ 与它右边的数，答案减少的量会形成一个以 $3$ 为首项，$2$ 为公差的等差序列。于是我们让 $n-1$ 在不越过 $0$ 且 $c_0\geq c$ 的前提下尽可能移动。

同时也可以发现，此时我们交换 $a_i,a_{i+1}$（要求 $a_{i+1}$ 在 $n-1$ 前面）会使答案减少 $2i+3$。于是我们**在大部分情况下**成功构造出了 $c_0-c<5$ 的序列：除了 $3\leq c_0-c\leq 4$，我们都可以找到一个 $i$ 使得 $0\leq c_0-c-(2i+3)\leq 1$。

进入第一个讨论，我们在刚刚的那一步中可能无法找到合法的 $i$（按刚才的方法算会发现 $a_{i+1}=n-1$），此时若 $c_0-c\leq 4$ 我们就以后处理，否则令 $a_m=n-1$，交换 $a_{m-1},a_{m-2}$ 即可化为 $c_0-c=2$ 的情况处理。

接下来就是对 $c_0-c$ 的 $5$ 种情况讨论：

* $c_0-c=0$，我们找到了一组合法解！

* $c_0-c=1$，我们将 $n-1$ 替换为 $n$ 即可。

* $c_0-c=2$，$a_n\gets a_n-(2-[a_1=n-1])$。

* $c_0-c=3$，
	* 若 $n$ 为奇数：交换 $0$ 和 $1$ 的位置，并将 $a$ 的最后一个数加 $1$。
   * 若 $n$ 为偶数：将 $n-1$ 替换为 $n$，并将 $a$ 的第一个数减 $1$，最后一个数减 $2$。

* $c_0-c=4$，将 $a$ 的最后两个数交换，若 $a_2\neq n-1$ 则需要将 $n-1$ 替换为 $n$。

至于怎么找到这些方案的？想要可控一些的微调只可能是对很大（$n-1,n$）或很小（$0,1,2$）的数进行修改，人工枚举每一种可能的修改方式就找出来了。

我的程序需要特判 $c\in\{0,4,8,14,28,35\}$ 的情况。容易构造这些情况的合法解。

比出题人构造出来的解优一点（最终解的长度更短）。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> vals;

long long maxsum_mex(long long n)
{
    bool flag=!(n&1);
    return ++n>>=1,(flag?(4*n+9)*n+5:(4*n+3)*n-1)*n/6;
}

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testcnt;
    cin>>testcnt;
    while(testcnt--)
    {
        int targ,cpytarg;
        cin>>targ;
        cpytarg=targ;
        if(!targ)
            vals={1};
        else if(targ==4)
            vals={1,3,0};
        else if(targ==8)
            vals={1,4,0,4};
        else if(targ==14)
            vals={2,5,0,3,1};
        else if(targ==28)
            vals={0,1,2,3,4,5,6};
        else if(targ==35)
            vals={4,2,7,0,3,1,5};
        else
        {
            int cnt=0;
            while(maxsum_mex(++cnt)<targ);
            targ=maxsum_mex(cnt)-targ;
            vals.clear();
            for(int i=0;i<cnt;i++)
                vals.push_back(i<cnt/2?cnt-2+!(cnt&1)-i*2:i-cnt/2<<1);
            if(cnt&1)
                reverse(vals.begin(),vals.end());
            for(int i=1;i<cnt&&vals[i]&&targ>=(i<<1|1);i++)
                swap(vals[i],vals[i-1]),targ-=i<<1|1;
            if(targ>4)
                if(vals[targ-3>>1]==cnt-1)
                    targ-=2,swap(vals[targ-5>>1],vals[targ-3>>1]),targ=2;
                else
                    swap(vals[targ-5>>1],vals[targ-3>>1]),targ=!(targ&1);
            if(targ==1)
                ++*find(vals.begin(),vals.end(),cnt-1);
            else if(targ==2)
                *find(vals.begin(),vals.end(),cnt-2)-=1+(vals[0]!=cnt-1);
            else if(targ==4)
                *find(vals.begin(),vals.end(),cnt-1)+=vals[1]!=cnt-1,swap(vals.back(),vals[vals.size()-2]);
            else if(targ==3)
            {
                auto pos0=find(vals.begin(),vals.end(),0);
                if(cnt&1)
                     ++vals.back(),swap(*pos0,*(pos0+1));
                else
                    ++*find(vals.begin(),vals.end(),cnt-1),--vals[0],vals.back()-=2;
            }
        }
        cout<<vals.size()<<'\n';
        for(int i:vals)
            cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：Grand_Dawn (赞：2)

## mex2 题解

小清新构造题。欢迎踩部分分。

首先可以证明在该题数据范围内一定有解，证明请参考以下的构造方式获得构造性证明。

以下提供正解的构造方式，可能不唯一：

首先构造前面有 $x$ 个 $0$，后面有 $y$ 个从 $1\sim y$ 的正整数。

左右端点都在第一段对答案的贡献有 $\frac{x(x+1)}{2}$。而左右端点在不同的两端的贡献显然为 $x$ 的倍数。

则先调整第一段使得其剩下的贡献为 $x$ 的倍数。第一段中将连续的长度为 $z$ 的一段改为 $\max$ 值会使答案减去 $\frac{z(z+1)}{2}$。

每次都取最大的 $z$，对 $x\le 3000$ 都成立。

左右端点在不同的两端的贡献为 $x\frac{(y+1)(y+2)}{2}$。

若在 $z$ 之后加入一个相同的数，对答案有贡献 $x(z+1)$，其中 $z\in[1,y]$。

则唯一形如 $x\frac{y^2+3y+4}{2}$ 的数有问题，则调整 $x$ 即可。

大概 $x=\frac{1}{3}n,y=\frac{2}{3}n$ 时有最大值 $\frac{2}{27}n^3$，刚好满足条件。

存在一些更强的做法可以做到 $\frac{1}{12}n^3$，请参考其它题解。

```cpp
#include<bits/stdc++.h>
#define N 3009
using namespace std;
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+'0'); 
}
int pre[N],a[N],n,c;
void init(){
	for(int i=1;i<N;i++)
		for(int j=1;j*(j-1)/2<=i;j++)pre[i]=j;
}
bool trial(int c,int dif=0){
	fill(a,a+N,0);n=1;
	if(c==0)return a[1]=1;
	for(;c>0&&n<=1000+dif;n++)c-=n;n--;
	int now=1,t=(c<=0?-c:c/n*n+n-c);
	while(t){
		for(int i=now;i<now+pre[t]-1;i++)a[i]=3000;
		now+=pre[t];
		t-=pre[t]*(pre[t]-1)/2;
	}
	if(c>0){
		c=c/n+2;int p=0;n--;
		for(p=1;c>=p;p++)c-=p;p--;
		if(c==1)return 0;//need troubleshooting
		for(int i=1;i<=p;i++){
			a[++n]=i-1;
			if(i==c)a[++n]=i-1;
		}			
	}
	return 1;
}
void print(){
	write(n);putchar('\n');
	for(int i=1;i<=n;i++)write(a[i]),putchar(' '); 
	putchar('\n');
} 
void solve(){
	int c;cin>>c;
	if(trial(c))return print();
	for(int dif=0;;dif++){
		if(trial(c,dif))return print();
		if(trial(c,-dif))return print();
	}
	assert(0);
}
int main(){
	//freopen("4.in","r",stdin);
	//freopen("a.out","w",stdout);
	init();
	int t;cin>>t;
  while(t--)solve();
	return 0;
}
```

---

## 作者：RainySoul (赞：0)

我这里有一个比较不牛的构造。

首先考虑填 $01234\dots (n-1)$ 这样一共 $n$ 个数，这一段答案是 $\frac{(1+n)\times n}{2}$，然后考虑将一段后缀全部减一会使答案减小 $\lceil$ 后缀长度 $\rfloor$，于是我们可以贪心地调整，能减则减。这里可以构造出 $\frac{3000\times (3000+1)}{2}=4501500$ 的。

看到数据范围有个 $4\times 10^6 \to 8\times 10^6$，启示我们能否考虑加倍，然后在最前面填一个 $\text{inf}$ 就可以实现 $k \to 2k$ 的加倍，填 $0$ 可以实现 $k \to 2k+1$。于是拿到了 $45$ 分。

感觉这个做法还比较有前途，考虑前面填一堆 $0$ 后面填 $01234\dots (y-1)$ 然后调整。设填了 $x$ 个 $0$，则此时最大可以构造出 $\frac{x(x+1)}{2}+x\frac{y(y+1)}{2}$，并且有 $y=n-x$。大约在 $x=\frac{1}{3}n$ 时取到最大值，堪堪能过 $2\times 10^9$。

但是因为我们填的是 $x(\frac{x+1}{2}+num)$（$num$ 是后面调整之后的值），这样显然填不出一些大质数，考虑在前面全 $0$ 段塞一点 $\text{inf}$，发现填 $\text{inf}$ 使 $x\times num$ 部分是不变的，而在前面 $x$ 个 $0$ 中间插入连续的 $k$ 个 $\text{inf}$ 会使得答案减小 $\frac{k(k+1)}{2}$。

于是现在是 $c=1001 \times num+\frac{1000\times(1000+1)}{2}-res$，其中 $res$ 部分就是在前面全 $0$ 段里若干次插入连续的 $\text{inf}$ 带来的贡献。直接令 $num=\frac{c-\frac{1000\times 1001}{2}}{1001}+1$ 可以保证 $res < 1000$，仍然贪心地调整，如果可以减 $\frac{k\times (k+1)}{2}$ 就减。

不过比较不牛的地方是你需要判掉 $c < 500500$ 的部分不然 $num$ 算出来是错的。

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (int)2e9
using namespace std;
const int N=3010;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
int ans[N],ans1[N];
signed main(){
    int T=read();
    while(T--){
        int c=read(); 
        if(c<=3000){
            if(c==0){
                cout<<1<<'\n';
                cout<<1<<'\n';
                continue;
            }
            cout<<c<<"\n";
            cout<<0<<" ";
            for(int i=2;i<=c;i++)cout<<inf<<" ";
            cout<<"\n";
            continue;
        }
        else if(3000<c&&c<=500500){
            int t=3000;
            cout<<t<<'\n';
            for(int i=1;i<=t;i++)ans[i]=i-1;
            int sum=(1+t)*t/2;
            for(int i=2;i<=t;i++){
                if(sum-(t-i+1)>=c){
                    sum-=t-i+1;
                    for(int j=i;j<=t;j++){
                        ans[j]--;
                        if(ans[j]==0)ans[j]=inf;
                    }
                }
            }
            for(int i=1;i<=t;i++)cout<<ans[i]<<" ";
            cout<<'\n';
            continue;
        }
        c-=1000*1001/2;
        int num=c/1001+1,res=1001*num-c,lenz=2000,leny=1000;
        if(num<=2000){
            lenz=num;
            ans[1]=0;
            for(int i=2;i<=lenz;i++)ans[i]=inf;
        }
        else{
            for(int i=1;i<=lenz;i++)ans[i]=i-1;
            int sum=(1+lenz)*lenz/2;
            for(int i=2;i<=lenz;i++){
                if(sum-(lenz-i+1)>=num){
                    sum-=lenz-i+1;
                    for(int j=i;j<=lenz;j++){
                        ans[j]--;
                        if(ans[j]==0)ans[j]=inf;
                    }
                }
            }
        }
        for(int i=1;i<=leny;i++)ans1[i]=0;
        for(int i=1;i<leny;i++){
            for(int j=leny-i;j>0;j--){
                if(res>=j*(j+1)/2){
                    res-=j*(j+1)/2;
                    for(int k=i;k<=i+j-1;k++)ans1[k]=inf;
                    i+=j;
                    break;
                } 
                
            }
        }
        cout<<leny+lenz<<'\n';
        for(int i=1;i<=leny;i++)cout<<ans1[i]<<" ";
        for(int i=1;i<=lenz;i++)cout<<ans[i]<<" ";
        cout<<'\n';
    }
    return 0;
}
```

稳稳拿下最劣解。

---

## 作者：sunkuangzheng (赞：0)

> - 构造一个序列 $a$ 满足所有子区间 $\text{mex}$ 的和等于 $c$。
> - $0 \le c \le 2\cdot 10^9$，你需要保证构造的序列长度 $n \le 3000$。

首先拆 $\text{mex}$ 的贡献，$\sum \text{mex} = \sum d_i$，其中 $d_i$ 表示同时包含 $0,1,\ldots,i$ 的子区间数量。

注意到 $c$ 大概是 $\mathcal O(n^3)$ 级别的，有一种很自然的构造是 $[\inf,\inf,\ldots,\inf,0,1,2,\ldots,x]$，不妨记 $0$ 的位置是 $i$，贡献是 $f_i = i \cdot \sum \limits_{j=1}^{n-i+1}j = \dfrac{i(n-i+2)(n-i+1)}{2}$。我们把 $f_i$ 叫做 $i$ 位置的上界。

考虑一个 $0$ 开头的序列，我们钦定后面的数字除了 $\inf$ 外互不相同。每个位置我们选择填 $\inf$ 或者上一个非 $\inf$ 数加 $1$，前者没有贡献，后者贡献 $n-i+1$。那么不难发现，$\forall x \in [1,\dfrac{n(n+1)}{2}]$ 的数字都可以通过数字和 $\inf$ 的组合凑出来，构造是一个经典的贪心：能减就减。

如果 $c$ 存在一个因数 $x$ 满足 $f_x \ge c$，那么直接在 $x$ 位置填 $0$，然后后面去按照上面构造一个 $\dfrac{c}{x}$。否则，不难想到将 $c$ 拆成 $y+b$，使得 $y$ 满足上面 $c$ 的性质，然后在 $b$ 位置放上后面填的最大非 $\inf$ 值 $+1$。

举个例子，考虑下面的构造：$c = 33$，我们令 $y = 32,b = 1$，构造 $[3,\inf,\inf,0,1,\inf,2]$，其中 $0 \sim 2$ 贡献了 $4 \times (4+3+1)=32$，而最后的 $3$ 填在 $b$ 位置。

但是上面的构造其实存在一些小问题：

- $y$ 的因子 $x$ 必须满足 $x > b$，否则最后一步填 $b$ 无法造成贡献。
- 如果序列末尾填的是 $\inf$，那么填 $b$ 位置造成的贡献其实乘上了一个系数（$n$ 减去序列最后一个非 $\inf$ 数字的位置）。解决办法是我们钦定序列末尾一定不填 $\inf$，这就要求 $\dfrac{c}{x} \ne 2$。然而 $c$ 比较小时实际上不一定存在合法的 $x$，请特判。

~~感觉写的好抽象啊，要是没看懂还是看看代码吧（~~

```cpp
/**
 *    author: sunkuangzheng
 *    created: 05.10.2024 15:17:34
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
mt19937 rd(time(0));
namespace A{ // c 比较小的时候的特判
    int T,n,posl,c,posr;
    int fp(int x,int k){
        for(int i = max(k + 1,posl);i <= posr;i ++)
            if(x % i == 0) return i;
        return -1;
    }void los(int c){
        if(!c) return cout << "1\n1\n",void();
        if(c == 1) return cout << "1\n0\n",void();
        posl = -1,posr = -1;
        for(int i = 1;i <= 3000;i ++){
            if(1ll * i * (3000 - i + 1) * (3000 - i + 2) / 2 >= c) {posl = i; break;}
        }for(int i = 3000;i >= 1;i --){
            if(1ll * i * (3000 - i + 1) * (3000 - i + 2) / 2 >= c) {posr = i; break;}
        }
        if(posl == -1) return cout << "-1\n",void();
        for(int i = c;i >= c - 2700;i --){
            if(fp(i,c - i) != -1){
                int s = fp(i,c - i),sm = i / s;
                // debug(sm);
                vector<int> t;
                for(int j = 3000 - s + 1;j >= 1;j --) if(sm >= j) t.push_back(j),sm -= j;
                if(sm > 0) continue;
                assert(sm == 0);
                // debug(sm);
                n = s + t.front() - 1;
                assert(n <= 3000);
                vector<int> as(n + 1,1e9);
                as[s] = 0;
                for(int j = 1;j < t.size();j ++)
                    as[n - t[j] + 1] = j;
                as[c - i] = t.size();
                cout << n << "\n";
                for(int j = 1;j <= n;j ++) cout << as[j] << " ";
                cout << "\n";
                // {
                //     //check
                //     ll smx = 0;
                //     for(int j = 1;j <= n;j ++){
                //         vector<int> vis(n + 5,0); int mex = 0;
                //         for(int k = j;k <= n;k ++){
                //             if(as[k] <= n + 1){
                //                 vis[as[k]] = 1;
                //                 while(vis[mex]) mex ++;
                //             } smx += mex;
                //         }
                //     }assert(smx >= c);
                //     // cerr << smx << "\n";
                // }
                return ;
            }
        }assert(0);
    }
}
int T,n,posl,c,posr;
int fp(int x,int k){
    for(int i = k + 1;i <= min(3000,(x - 1) / 2);i ++)
        if(1ll * i * (3000 - i + 1) * (3000 - i + 2) / 2 >= c && x % i == 0) return i;
    return -1;
}void los(){
    cin >> c;
    if(c <= 4000) return A::los(c);
    // c = rd() % 8000000 + 1;
    if(!c) return cout << "1\n1\n",void();
    if(c == 1) return cout << "1\n0\n",void();
    // cerr << c << " ";
    for(int i = c;i >= c - 2700;i --){
        if(fp(i,c - i) != -1){
            int s = fp(i,c - i),sm = i / s;
            // debug(sm);
            vector<int> t;
            sm --;
            for(int j = 3000 - s + 1;j >= 2;j --) if(sm - j >= 2 || sm - j == 0) 
                t.push_back(j),sm -= j;
            if(sm > 0) continue;
            assert(sm == 0);
            t.push_back(1);
            // debug(sm);
            n = s + t.front() - 1;
            assert(n <= 3000);
            vector<int> as(n + 1,1e9);
            as[s] = 0;
            for(int j = 1;j < t.size();j ++)
                as[n - t[j] + 1] = j;
            as[c - i] = t.size();
            cout << n << "\n";
            for(int j = 1;j <= n;j ++) cout << as[j] << " ";
            cout << "\n";
            // {
            //     //check
            //     ll smx = 0;
            //     for(int j = 1;j <= n;j ++){
            //         vector<int> vis(n + 5,0); int mex = 0;
            //         for(int k = j;k <= n;k ++){
            //             if(as[k] <= n + 1){
            //                 vis[as[k]] = 1;
            //                 while(vis[mex]) mex ++;
            //             } smx += mex;
            //         }
            //     }cerr << smx << "\n";
            //     assert(smx == c);
                
            // }
            return ;
        }
    }assert(0);
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

