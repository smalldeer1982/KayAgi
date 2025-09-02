# [PA 2013] Iloczyn

## 题目描述

给定正整数 $n$ 和 $k$，问能否将 $n$ 分解为 $k$ 个不同正整数的乘积。

## 说明/提示

对于 $100\%$ 的数据，$1\le T\le 4\times 10^3$，$1\le n\le 10^9$，$1\le k\le 20$。

## 样例 #1

### 输入

```
3
15 2
24 4
24 5```

### 输出

```
TAK
TAK
NIE```

# 题解

## 作者：STA_Morlin (赞：17)

[P5973 [PA2013] Iloczyn の 题目传送门。](https://www.luogu.com.cn/problem/P5973)

# 题目简化
RT，题目足够简单。

# 思路讲解
黄至绿，DFS。

刚开始是想用 DP 做的，不会推方程……  
然后发现 STD 就是 DFS……

首先可以看到 $n$ 的范围是 $1$ 至 $10^9$，再计算一下 $20! \thickapprox 2 \times 10^{18}$，经过二分可以快速得到在 $k = 13$ 时，已经无法拆分 $n$ 了 $(13! \thickapprox 6 \times 10^9)$。

为了更加速度，我们还可以推算出来，只有在 $k \le n$ 时，才可以拆分，可以自证，不进行详解。

容易知道，希望划分的 $k$ 个数一定是 $n$ 的约数，所以应先求其约数。

---
# 代码实现
我们知道极限数据是 $4 \times 10^{12}$，如果是直接使用从 $1$ 至 $n$ 的循环会 T 飞掉。  
但容易知道，除平方数以外，所有自然数都具有偶数个因数，并且平均分布在 $\sqrt n$ 两侧。可以反证：若某一侧比另一侧含有更多的因数，那么将无法成功配对，将有某两个因数的乘积大于或小于 $n$。  
这样就可以求约数了，$\sqrt {10^9} \thickapprox 3 \times 10^4$。

### _CODE_
```cpp
fors(i, 1, i <= sqrt(n), 1) 
	if (!(n%i)) {
		a.push_back(i);
		if (i*i != n) a.push_back(n/i);
	}
sort(a.begin(), a.end());
```
求完约数就可以写 dfs 了。

### 约定：
$d$ 代表还需要 $d$ 个数才能达到 $k$ 个数。  
$p$ 代表还需要除以 $p$ 才能将 $n$ 除尽。  
$m$ 代表正在考虑第 $m$ 个约数。

首先从 $k, n, 0$ 开始。

终止条件：$d = 0$。

然后判断剩余的约数能否被取走。  
因为在前面排了序，所以接下来的一定是比后面更小的，如果前面小的都除不尽的话就说明大的也没戏。

### _CODE_
```cpp
int l = d, u = 1;
fors(i, m, i<a.size() && l--, 1) if ((u*=a[i]) > p) return 0;
```

接下来挨个找可以被整除的约数。  
$u$ 代表的是接下来 $d$ 个约数的积。

### _CODE_
```cpp
fors(i, m, i<a.size() &&  && i+d-1<=a.size() && u<=p, 1) {
	if (i != m) u = u/a[i-1]*a[i];// 如果不是第一个且 a[i-1] 不符合要求，就代表接下来还需要 a[i]。
	if (!(p%a[i]) && dfs(d-1, p/a[i], i+1)) return 1;// 如果 p 能整除 a[i] 且 a[i] 配对成功的话就说明可行，直接真值返回。
}
```
# E.N.D.

---

## 作者：FZY_CZY (赞：5)

# 题意
其实题意还是蛮简单的，就是把一个数拆分成 $k$ 个整数相乘的形式，问能不能这样拆？

# 思路
先看范围，$1\le T\le4 \times 10^3,1\le n\le10^9$，爆搜就别想了（反正我一开始也没考虑爆搜）。

讲一个数论的小知识。

我们在枚举一个数 $x$ 的因子的时候，只需要枚举到 $\sqrt {x}$ 就可以了，因为对于每一个 $x \bmod i=0$，都有一个 $x\bmod j=0$ 与之相对应（有可能 $i=j$），因此，根号 $x$ 就够了，在本题中，就是 $O(T \times \sqrt x)$ 的时间复杂度，大约是 $10^8$ 的时间复杂度，但是常数小，完全是可以过的。

你以为到这里就结束了？不可能（我一开始也是这么想的，然后就 WA 了）！！！

它问我们能否拆分成 $k$ 个正整数相乘，我们直接 dfs 求解即可。

这就是大概的思路，当然，我们完全可以对其进行优化，我们通过暴力可以知道一个点，那就是 $12 \ne 479001600 > 10^9$，所以我们的深度到 $11$ 就 OK 了，当然，深度也不会大于 $n$ 本身。

代码就不给了，完结撒花！！！

---

## 作者：shiranui (赞：4)

# 题目大意
给定正整数 $n$ 和 $k$ ，问能不能把 $n$ 拆成 $k$ 个不同正整数的乘积。
# 思路
同机房的六年级小学生一看题目激动了：“呀，可以用动规写！”

想了一想，动规似乎可以，但我还是用我的 **$DFS$** 做了，~~让他 $AC$ 了以后自己写一篇动规题解好了，估计他写不出来~~。
## No.1
我们可以发现，**$12! = 479001600$**，**$13! = 6227020800$**。由于 **$1 ≤ n ≤ 10^9$**，所以 **$k ≥ 13$** 时，我们**无论怎么拆都不可能将 $n$ 拆出来**，那么就直接快乐输出 "$NIE$" 啦。

```cpp
if(k>=13)
{
	cout<<"NIE"<<endl;
	continue;
}
```

## No.2
很明显，**拆成的 $k$ 个正整数一定是 $n$ 的因数**，那么咱就来统计一下 $n$ 的因数吧。

```cpp
int yueshu[1000001],cnt=0;
for(int i=1;i*i<=n;i++)
	if(n%i==0)
	{
		yueshu[++cnt]=i;
		if(i*i!=n)yueshu[++cnt]=n/i;
	}
sort(yueshu+1,yueshu+1+cnt);//记得给因数排序
```

## No.3
进入核心代码。

我们创建一个 **$bool$** 型的 $dfs$ 函数，传入 **$dep$** 表示 _**目前已经选择了 $dep$ 个因数组成 $n$**_ ， **$ned$** 表示 _**需要因数的乘积是多少**_ ， **$now$** 表示 _**现在正在考虑填第 $now$ 个因数**_ 。

我们可以通过 $dfs$ 传入的 $dep$ 计算出我们**还需要选择几个因数**。

```cpp
int nedmny=k-dep;;//需要再选择几个因数
```

接着，我们来判断一下**剩余要取的因数个数能不能是不是还在需要的范围内**。

```cpp
long long used=1;//再选择了 nedmny 个因数后的乘积 
for(int i=now+1;i<=cnt;i++)
{
	if(nedmny==0)break;
	nedmny--;
	used*=yueshu[i];
	if(used>ned)return 0;
}	
```

可以选择边做边判断，也可以结束了以后再判断。

作为一个合格的 $dfs$ ，它要疯狂调用自己。

```cpp
nedmny=k-dep;
for(int i=now+1;i<=cnt;i++)
{
	if(i+nedmny-1>cnt)return 0;//剩下没有那么多因数可以拆
	if(used>ned)return 0;//拆出的因数乘积过大
	if(i!=now+1)used=used/yueshu[i-1]*yueshu[i];//计算因数乘积
	if(ned%yueshu[i]==0&&dfs(dep+1,ned/yueshu[i],i)==1)return 1;//选中的因数可以整除现在需要的乘积，并且下一层dfs返回可行，那么这一层也是可行的
}
```

# 代码
代码上没有注释，各位大佬请自己理解，看懵了请看思路部分，毕竟本萌新码风不太好。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int yueshu[1000001],cnt; 
bool dfs(int dep,long long ned,int now)
{
	if(dep==k+1&&ned==1)return 1;
	int nedmny=k-dep;
	long long used=1;
	for(int i=now+1;i<=cnt;i++)
	{
		if(nedmny==0)break;
		nedmny--;
		used*=yueshu[i];
		if(used>ned)return 0;
	}
	nedmny=k-dep;
	for(int i=now+1;i<=cnt;i++)
	{
		if(i+nedmny-1>cnt)return 0;
		if(used>ned)return 0;
		if(i!=now+1)used=used/yueshu[i-1]*yueshu[i];
		if(ned%yueshu[i]==0&&dfs(dep+1,ned/yueshu[i],i)==1)return 1;
	}
	if(dep==k&&ned==1)return 1;
	return 0; 
}
int main()
{
	cin>>t;
	for(int I=1;I<=t;I++)
	{
		cnt=0;
		cin>>n>>k;
		if(k>=13)
		{
			cout<<"NIE"<<endl;
			continue;
		}
		for(int i=1;i*i<=n;i++)
			if(n%i==0)
			{
				yueshu[++cnt]=i;
				if(i*i!=n)yueshu[++cnt]=n/i;
			}
		sort(yueshu+1,yueshu+1+cnt);
		if(dfs(1,n,1)==1)cout<<"TAK"<<endl;
		else cout<<"NIE"<<endl;
	}
	return 0;
}
```

如果有地方表述不清，或者错误，请各位大佬指出。

希望能帮助到大家。

---

## 作者：dulinfan2023 (赞：3)

## 题意：

共 $T$ 组询问，每一次询问会问你 $n$ 是否能被表示为 $k$ 个正整数相乘。

## 思路：

**dfs 搜索**，遍历每一个能被 $n$ 整除的 $i$，再搜索下一层 $\frac{n}{i}$ 的情况，进而推出结果与 $k$ 作比较。

因为 $13! \ge 10^9$，当 $k \ge 13$ 时，将无法拆成 $k$ 个正整数相乘，输出 `NIE`。

## 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
#define debug() cout<<"here"<<'\n'
int noip,k,ch;
void dfs(int dep,int noip,int stoljkorz){
	if(ch==1)return;
	if(dep==k){
		if(noip>stoljkorz)ch=1;
		return;
	}
	int maxxljk=pow(noip,1.0/(k-dep+1));
	for(int i=stoljkorz+1;i<=maxxljk;i++){
		if(noip%i==0)dfs(dep+1,noip/i,i);//%%% @ljk8886
	}
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>noip>>k;
		if(k>=13){
			cout<<"NIE"<<'\n';
			continue;
		}
		dfs(1,noip,0);
		if(ch==1)cout<<"TAK"<<'\n';//%%% ljk
		else cout<<"NIE"<<'\n';
		ch=0;
	}
    return 0;
}
```

---

## 作者：Alexandr (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P5973)

## 前言

是一道挺棒的搜索题，可用于复习剪枝方法。

## 解析

观察数据范围，我们发现 $k\le 20$，又有 $13!=6227020800\ge 10^9$，所以当 $k\ge13$ 时，无论如何都无法构造出来，输出 `NIE`。

而对于 $k<13$ 的情况，我们直接暴力搜索每一个数字，但这样显然过不了。这里我们掏出套路，把每一层的搜索的上下界给尽量缩小。

- 对于下界，这是很好处理的。我们钦定我们搜索的数字是单调上升的，那么下界就是上一层搜索的数字加一。

- 对于上界，我们在搜索时带入一个 $now$，表示还需要的乘积；以及一个 $cur$ 表示搜索的层数。为了让这一层最大，那么我们后面搜到的数字要尽量小，即与之相同。但这个规定不能符合条件，只是我们对于仅仅这一层的猜想。也就是说这个上界应该是 $now^{\frac{1}{k-cur+1}}$。

这样我们就大大减少了搜索的复杂度了，为了更加的剪枝，我们对于每一层搜索的数字须要满足是 $now$ 的因数。

到了这里我们发现还是不能快速通过，我们最后再用一个剪枝操作。就是我们发现到了搜索的最后一层，我们我们这一层的上界 $now^{\frac{1}{k-cur+1}}$ 退化成了 $now$，这是很有可能十分恐怖的大。怎么办呢？很简单啊，因为是最后一层，所以这一层要想满足条件必须把这整个 $now$ 都要了，所以我们直接去判断这个 $now$ 是否大于我们上一层搜索的数来处理是否可行。

因为题目中要我们的做的只是判断有没有满足条件的解法，所以在搜索的过程中，为了防止已经发现有解了但还在寻找解法的情况发生，我们得加一个 $ans$ 的布尔变量来判断是否已经找到满足条件的解法了。在后面的搜索中一旦 $ans$ 表示有解了，我们可以直接退出搜索，减少了很多复杂度。

## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--) 
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
#define sz(s) (int)(s.size())
//#pragma GCC optimize(3,"Ofast","inline")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define int LL
using namespace std;
typedef long long LL;
typedef double db;
const int N=5e3+5;   
inline void write(int x);
inline int read(); 
int n,k;
bool ans;
void dfs(int cur,int now,int lst)//lst表示上一层搜索的数字是什么
{
    if(ans) return;
    if(cur==k)
    {
        if(now>lst) ans=true;
        return;
    }
    int Max=pow(now,1.0/(k-cur+1));
    _rep(i,lst+1,Max)
        if(now%i==0) dfs(cur+1,now/i,i);

}
signed main()
{       
    int T=read();
    while(T--)
    {
        n=read();k=read();
        if(k>=13) {puts("NIE");continue;}
        ans=false;
        dfs(1,n,0);
        if(ans) puts("TAK");
        else puts("NIE");
    }      
	return 0;
} 
inline void write(int x)
{
	if(x<0)putchar('-'),x=-x;
	static int sta[35];int top=0;
	do{sta[top++]=x%10,x/=10;}while(x);
	while(top)putchar(sta[--top]+48);
}
inline int read()
{
	int x=0,w=1;char ch=0;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')
	{x=((x<<1)+(x<<3))+(ch-'0');ch=getchar();}
	return x*w;
}
```
完结撒花啦，祝你们天天开心 qwq。

---

## 作者：wangbotao (赞：2)

本人的第一篇题解：

这道题的想法并不难，直接暴搜（×），但是发现数据范围太大，肯定会TLE，所以得加上剪枝来减小时间复杂度。

具体做法是：首先分解质因数，用sort从小到大进行排序，从头开始搜，不合法就return。记得要加上剪枝（可行性剪枝）：

如果从原状态的基础上，继续乘上后面最小的t(还没选的数的个数）个数大于n，就return

所以dfs这么写：

```
int dfs(int a,int t,int s)
{
	if(!t) return s==n;
	for(--t;a+t<=top;++a)
	{
		if(f[a][t]<0) return 0;
		if(1ll*f[a][t]*s>n) return 0;
		if(dfs(a+1,t,sta[a]*s)) return 1;
	}
	return 0;
}
```
还有一个要点：如果k！>n，或k>12,就continue进行下一次操作，本次操作直接判为“NIE”。

其中，12！=479001600>1000000000，所以一个n最多分解为11个数的乘积形式，即：
```
if(num[k]>n||k>12)
{
	puts("NIE");
	continue;
}
```

所以最后的代码是（其实用不用快读对于这个题来说都没什么用处）：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=2000;
int n,k,sta[maxn],top,f[maxn][22];
long long num[22];

inline int qread()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}

int dfs(int a,int t,int s)
{
	if(!t) return s==n;
	for(--t;a+t<=top;++a)
	{
		if(f[a][t]<0) return 0;
		if(1ll*f[a][t]*s>n) return 0;
		if(dfs(a+1,t,sta[a]*s)) return 1;
	}
	return 0;
}

int main()
{
	int T;
	T=qread();
	num[0]=1;
	for(int i=1;i<=12;i++)
		num[i]=num[i-1]*i;
	while(T--)
	{
		n=qread(),k=qread();
		top=0;
		if(num[k]>n||k>12)
		{
			puts("NIE");
			continue;
		}
		for(int i=1;i*i<=n;i++)
			if(n%i==0)
			{
				sta[++top]=i;
				if(i*i!=n)
					sta[++top]=n/i;
			}
		sort(sta+1,sta+1+top);
		for(int i=1;i<=top;i++)
		{
			long long t=1;
			for(int j=0;j<k&&i+j<=top;f[i][j++]=t)
				if(t>0)
				{
					t=t*sta[i+j];
					if(t>n) t=-1;
				}
		}
		puts(dfs(1,k,1)?"TAK":"NIE");
	}
	return 0;
}
```



---

## 作者：_7xingyue7_ (赞：1)

# P5973 [PA 2013] Iloczyn 题解
## [题目传送门](https://www.luogu.com.cn/problem/P5973)
![听取WA声一片](data:image/png;base64,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)
## 题意
回答用 $k$ 个**不同**的正整数相乘是否能够得到 $n$。
## 分析
观察范围 $1\le n\le 10^9$，而 $13!\approx 6.22\times 10^9$ 超过了 $n$ 的范围，故**当** $k\ge 13$ **时可以直接输出**`NIE`。

令 $n$ 的因数个数为 $x$，那么不可能有任何一种 $k$ 个数相乘得到 $n$ 的方式，也可以直接输出`NIE`。

很明显的一道 DFS 题，考虑到暴搜会超时。易得划分的 $k$ 个数肯定是 $n$ 的因数，所以我们可以使用**分解质因数**来降低时间复杂度。
### CODE
```cpp
//因数预处理
void prime(int n){
    factor.clear();
    for(int i=1;i<=sqrt(n);i++){
        if(n%i==0){
            factor.push_back(i);
            if(i!=n/i) factor.push_back(n/i);
        }
    }
    sort(factor.begin(),factor.end());
    return ;
}
```
## 约定
$pos$ 为 $n$ 的第 $pos$ 个因数。

$mul$ 为当前乘积。

$used$ 为为了得到 $mul$ 已使用了 $used$ 个 $n$ 的因数。
## 实现
不妨设 $n=x^p$，考虑题目极限情况 $10^9$ 以内因数最多的数 $2^{29}$ 会有 $30$ 个因数(分别为 $2^0,2^1,2^2,...,2^{29},2^{30}$)，即 $p_{\max}=30$，那么暴搜的时间复杂度就是 $O(T\times 2^p)$，最大值即 $4\times 10^3\times 2^{30}\approx 4.29\times 10^{12}$，显然大于 $10^8$，**不可接受**，~~毕竟连 int 都存不下了~~故我们需要**剪枝优化**。

一开始我想到了使用**后缀积**进行优化，当当前乘积 $mul$ 乘以后面可乘得的最大乘积小于 $n$ 时不满足题意。
### CODE
```cpp
//后缀积预处理
void suffix(){
    suf=vector<int>(factor.size()+5);
    suf[factor.size()]=1;
    for(int i=factor.size()-1;i>=0;i--)
        suf[i]=suf[i+1]*factor[i];
    return ;
}
```
但如果 $n$ 足够大，相应地它的因数也会很大，后缀积的就会爆`int`，即使使用`long long`也依然会超，所以**该方案不可行**。

借鉴后缀积的思路，容易想到，我们不需要到最后一个因数的乘积，**只需要** $mul$ **乘以** $k-used$ **个** $pos$ **及以后因数的乘积小于** $n$ **即可**。
### CODE
```cpp
//判断剩余取的因数是否还在要求范围内
bool check(int pos,int deq,int rem){
    ll mul=1; //乘积有可能会爆int
    for(int i=0;i<deq;i++) mul*=factor[pos+i];
    if(mul>rem) return true;
    else return false;
}
```
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n,k;
bool ans;
vector<int> factor;
//因数预处理
void prime(int n){
    factor.clear();
    for(int i=1;i<=sqrt(n);i++){
        if(n%i==0){
            factor.push_back(i);
            if(i!=n/i) factor.push_back(n/i);
        }
    }
    sort(factor.begin(),factor.end());
    return ;
}
//判断剩余取的因数是否还在要求范围内
bool check(int pos,int deq,int rem){
    ll mul=1; //乘积有可能会爆int
    for(int i=0;i<deq;i++) mul*=factor[pos+i];
    if(mul>rem) return true;
    else return false;
}
//搜索
void dfs(int pos,int used,int mul){
    if(used==k){
        if(mul==n) ans=true;
        return ;
    }
    if(pos+k-used>factor.size()) return ;
    if(mul==0||check(pos,k-used,n/mul)) return ; //虽然我不知道为什么mul会等于0，但我大为震撼
    dfs(pos+1,used,mul);
    if(ans) return ;
    dfs(pos+1,used+1,mul*factor[pos]);
    return ;
}
int main(){
	#ifndef ONLINE_JUDGE
		freopen("factorization.in","r",stdin);
		freopen("factorization.out","w",stdout);
	#endif
    scanf("%d",&t);
    for(int task=1;task<=t;task++){
        ans=false;
        scanf("%d%d",&n,&k);
        if(k>=13){
            printf("NIE\n");
            continue;
        }
        prime(n);
        if(k>factor.size()){
            printf("NIE\n");
            continue;
        }
        dfs(0,0,1);
        if(ans) printf("TAK\n");
        else printf("NIE\n");
    }
	return 0; 
}
```
##### Update 2025.07.09 删除了 $\LaTeX$ 公式与中文标点符号之间的空格。

##### Update 2025.07.12 删除了部分大 $O$ 符号。

##### Update 2025.07.14 修改文章中极限情况下的数据错误。

---

## 作者：TH911 (赞：1)

> [题目传送门](https://www.luogu.com.cn/problem/P5973)

# 题意分析

对于正整数 $n,k$，求能否将 $n$ 划分为 $k$ 个不同的正整数的乘积，多测。

## 搜索

观察数据范围，可以发现 $1\leq k\leq 20$，拆出来数的个数不会太多，因此考虑 DFS。

很容易写出一个暴力 DFS 的判断函数：

```cpp
//last用于防止重复
bool check(int n,int k,int last=0){
	if(k==1){//边界：拆分为1个数
		return n>last;
	}
	for(int i=last+1;i<=n;i++){
		if(n%i==0){
			if(check(n/i,k-1,i)){
				return true;
			}
		}
	}
	return false;
}
```

但是这样显然是过不了的，实测只能获得 $\text{54pts}$。

因此我们考虑**剪枝**。

## 剪枝之一

在 `check()` 中枚举因数 $i$ 可以优化，因为 $i$ 如果取到 $\sqrt[k]{n}$ 以上的时候是一定无解的。

那么优化后的判断函数为：

```cpp
bool check(int n,int k,int last=0){
	if(k==1){ 
		return n>last; 
	}
	int Max=pow(n,1.0/k);
	for(int i=last+1;i<=Max;i++){
		if(n%i==0){
			if(check(n/i,k-1,i)){
				return true;
			}
		}
	}
	return false;
}
```

## 剪枝之二

显然，能够拆分为 $k$ 个正整数的乘积的数必须大于等于 $k!$。

而众所周知，阶乘的增长是非常迅速的，由计算器可得 $13!=6227020800>10^9$。

因此当 $k\geq13$ 的时候，直接输出 `NIE` 即可。

## 其他优化

意义不大，因为上面两个简单易懂的剪枝已经足以通过此题，但可以参考。

比如说预处理出 $1\sim12$ 的阶乘，每次二分检验能否直接输出 `NIE`。

或者说 $\mathcal O(\sqrt n)$ 求出 $n$ 的因数，然后在因数中枚举。

# AC 代码

```cpp
//#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
using namespace std;
bool check(int n,int k,int last=0){
	if(k==1){ 
		return n>last; 
	}
	int Max=pow(n,1.0/k);
	for(int i=last+1;i<=Max;i++){
		if(n%i==0){
			if(check(n/i,k-1,i)){
				return true;
			}
		}
	}
	return false;
}
int main(){
	/*freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);*/
	
	int T;
	scanf("%d",&T);
	while(T--){
		int n,k;
		scanf("%d %d",&n,&k);
		printf("%s\n",(k<=12 && check(n,k)?"TAK":"NIE"));
	}
	
	/*fclose(stdin);
	fclose(stdout);*/
	return 0;
}
```

---

## 作者：czh___ (赞：1)

首先将 $n$ 的约数从小到大排序，设 $dfs(x,y,z)$ 表示当前可以选第 $x$ 个到第 $m$ 个约数，还要选 $y$ 个，之前选的乘积为 $z$ 是否可能。

爆搜的时候，如果从 $x$ 开始最小的 $y$ 个相乘也超过了 $n$，那么就不合法，加上这个剪枝即可。

上代码！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m,k,j,i,q[2001],f[2001][22];
int dfs(int x,int y,int z){
  	if(!y)
  		return n==z;
  		for(y--;x+y<=m;x++){
    		if(!(f[x][y]>=0))
				return 0;
			if(1LL*f[x][y]*z>n)
				return 0;
   			if(dfs(x+1,y,z*q[x]))
		   		return 1;
  	}
  	return 0;
}
signed main(){
 	scanf("%d",&T);
  	while(T--){
    	scanf("%d%d",&n,&k);
    	for(m=0,i=1;i*i<=n;i++)
			if(n%i==0){
      			q[++m]=i;
      			if(i*i!=n)
				  	q[++m]=n/i;
    		}
    	stable_sort(q+1,q+m+1);
    	for(i=1;i<=m;i++){
      		int t=1;
      		for(j=0;j<k&&i+j<=m;f[i][j++]=t)
			  	if(t>0){
        			t*=q[i+j];
        			if(t>n)t=-1;
      			}
    	}
    	if(dfs(1,k,1))
    		cout<<"TAK\n";
    	else
    		cout<<"NIE\n";
  	}
  	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/166407821)

---

## 作者：DFM_O (赞：1)

## [P5973 题目](https://www.luogu.com.cn/problem/P5973)

### 解题思路
首先，$13!=6,227,020,800$，$13!$ 已经比 $10^9$ 大了，所以当 $k=13$ 时，直接输出 `NIE`。

不难发现，这道题可以用深搜解决，但如果每次搜索都枚举到 $n$，肯定会超时，需要优化。

设我们已经选了 $m$ 个数，这 $m$ 个数分别为 $a_1,a_2,a_3,\dots,a_m$，令 $p=\frac{n}{a_1\times a_2\times\cdots\times a_m}$，则第 $m+1$ 个数不能超过 $\sqrt[k-m]{p}$，这样可以大大缩短时间，不会超限。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,pd;
void dfs(int dep,int n,int sh)
{
	if(pd==1)
		return;
	if(dep==k)
	{
		if(n>sh)
			pd=1;
		return;
	}
	int maxx=pow(n,1.0/(k-dep+1));
	for(int i=sh+1;i<=maxx;i++)
	{
		if(n%i==0)
			dfs(dep+1,n/i,i);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		if(k>=13)
		{
			cout<<"NIE\n";
			continue;
		}
		dfs(1,n,0);
		if(pd==1)
			cout<<"TAK\n";
		else
			cout<<"NIE\n";
		pd=0;
	}
    return 0;
}
```

---

