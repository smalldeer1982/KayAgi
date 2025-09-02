# 「SWTR-1」Escape

## 题目背景

有一天，当 $\mathrm{Sunny}$ 闲逛的时候，发现了一个按钮。

好奇心驱使他按下了这个按钮。

突然间，天旋地转 $\dots$

## 题目描述

醒来之后，$\mathrm{Sunny}$ 发现自己站在一个奇怪的地方。

这个地方有 $n$ 个平台，**形成了一个环**。

这时，$\mathrm{Ethan}$ 的声音响起：

“哈哈哈哈哈哈，恭喜你，你是第一个来到**死亡之地**的人。”

“正如你所看到的，这个地方有 $n$ 个平台，你现在站在 $0$ 号平台上。”

“剩余平台按顺时针编号 $1,2,3\dots n-1$，也就是说，你身后的那个平台就是 $n-1$ 号平台。”

“你每次能够**顺时针**跳 $i$ 个平台，$i\in[1,n]$，每次的 $i$ 可以不一样。”

“如果你能够经过所有平台（初始 $0$ 号位置不算），那你就能逃出**死亡之地**了。”

（这里指的是一开始的 $0$ 号位置不算经过，需要再次经过 $0$ 号位置）

“不过，这样太简单了，我会给你一些数 $a_j$，表示你**不能一次顺时针跳 $a_j$ 个平台**。”

“还有，你必须要用**最少**的跳跃次数完成我的任务。”

“如果你不能满足我的上面两个要求，所有平台就会消失，你将会掉入下面的岩浆之中。”

现在，$\mathrm{Sunny}$ 想知道他是否可能逃出这个地方。

如果不行，输出```-1```，否则输出他最少所需的跳跃次数。

因为 $\mathrm{Sunny}$ 觉得死亡之地实在是太有趣了，所以他决定多玩几次，**多组数据**。

## 说明/提示

---

### 样例说明

第一组数据：

$\mathrm{Sunny}$ 每次只能顺时针跳 $5$ 个平台，易知不可能完成。

第二组数据：

$\mathrm{Sunny}$ 每次只能顺时针跳 $3$ 个平台，跳 $5$ 次即可。

---

### 数据范围与约定

$0\leq k\leq n\leq 10^6,1\leq n$。

保证 $\sum{n_i}\leq 3*10^6,a_j\leq n$，且**互不相同**。

测试点 $1:5\%,n=1$。

测试点 $2:5\%,n\leq5$。

测试点 $3:10\%,n\leq15$。

测试点 $4:15\%,n\leq300$。

测试点 $5:25\%,n\leq5000$。

测试点 $6:40\%,n\leq10^6$。

---

梦醒了……

## 样例 #1

### 输入

```
3
5 4
1 2 3 4
5 4
1 2 4 5
6 3
1 3 5```

### 输出

```
-1
5
-1```

# 题解

## 作者：Alex_Wei (赞：17)

$\color{orange}T1.\ Escape$

[$\color{orange}\text{题面}$](https://www.luogu.org/problem/T99077?contestId=21489)

官方题解

结论水题，部分分留给你们瞎打的（逃

结论：设所有的可行步数为 $b_1,b_2, \dots ,b_x$

- 如果 $gcd(b_1,b_2,\dots,b_x,n)=1$，则答案为 $n$

- 否则不可行，输出 $-1$

---

注意到 $k\leq n$ 而不是 $k<n$

如果 $n=k$，那么答案肯定是 $-1$

**看看你有没有特判下面这组数据**

```cpp
input
1
1 1
1
output
-1
```

---

**解析：**

设 $d=gcd(b_1,b_2,\dots,b_x,n)$

- 如果 $d>1$，易知不可能完成，即**只能**跳到编号为 $d$ 的倍数的平台

易知 “如果有一个 $b_i$ 与 $n$ 互质，就可以用 $n$ 步跳遍所有平台”

现在需要证明 **"如果 $d=1$，则一定能走遍所有平台，且步数为 $n$”**

（注：以下为这道题目结论的证明，并不是的真正实现方法）

---

**设 $d_1=gcd(b_1,n)$**

如果 $d_1=1$，则可以完成任务（跳 $n$ 次即可）

否则只能跳到 **编号是 $d_i$ 倍数的平台上**

接下来是很重要的一点！

- 如果我们能跳到 $mod\ d_1=1$ 的任意一个平台，$mod\ d_1=2$ 的任意一个平台，$\dots$，$mod\ d_1=d_1-1$ 的任意一个平台，那么我们就能跳到所有平台

因为如果你跳到了任意一个 $mod\ d_1=i$ 的平台上，那么你就能跳到 **所有** $mod\ d_1=i$ 的平台上(每次跳 $b_1$ 个)

例如 $b_1=3,b_2=4,n=12$

跳 $4$ 步 $3\ ->0,3,6,9,pos=0\ (0\ mod\ 3=0)$

跳 $1$ 步 $4\ ->0,3,4,6,9,pos=4\ (4\ mod\ 3=1)$

跳 $3$ 步 $3\ ->0,1,3,4,6,7,9,10,pos=1$

跳 $1$ 步 $4\ ->0,1,3,4,5,6,7,9,10,pos=5\ (5\ mod\ 3=2)$

跳 $3$ 步 $3\ ->0,1,2,3,4,5,6,7,8,9,10,11,pos=2$

这样，问题就从原来的

$b_1,b_2,b_3,\dots,b_x$ 遍历所有 $n$

被简化成了 $b_2,b_3,\dots,b_x$ 遍历所有 $d_1$

又因为 $d=1$，所以 **必定有一次 $gcd(b_i,d_{i-1})=1$**，于是就能完成任务啦 $qwq$

---

有了结论，代码可好打了：

```cpp
/*
DO NOT CHEAT!
author : Alex_Wei 
time : 2019.9.13
language : C++
*/
#include<bits/stdc++.h> 
using namespace std;
/*
快读 
inline void read(int &x)
{
	x=0;char s=getchar();
	while(!isdigit(s))s=getchar();
	while(isdigit(s))x=(x<<1)+(x<<3)+s-'0',s=getchar();
}
*/
int t,a[19260817];
bool pd[19260817];
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int main()
{
	scanf("%d",&t);
	for(int l=0;l<t;l++){
		int n,k,d;
		scanf("%d%d",&n,&k),d=n;
		for(int i=1;i<=k;i++)
			scanf("%d",&a[i]),pd[a[i]]=1;//标记一下
		if(n==1&&k==1){cout<<"-1\n",pd[1]=0;continue;}//特判 n=k=1 的情况
		for(int i=1;i<=n;i++)
			if(!pd[i])//如果可以走，求 gcd
				d=gcd(d,i);
		if(d>1)cout<<"-1\n";//d>1 
		else cout<<n<<endl;
		for(int i=1;i<=k;i++)
			pd[a[i]]=0;//取消标记，不然 memset （可能会）超时
	}
	return 0;
}
```

---

## 作者：Believe_R_ (赞：4)

这道题的题面已经说的很明白了。

首先我们可以从小数据出发，如果就只有一种步数 $f$ 可以走，那么就只有两种情况：
$$
ans=\begin{cases}n ,\gcd(f,n)=1 \\\\-1, \gcd(f,n) \neq 1\end{cases}
$$
那么当我们不只有一种步数可以走时，存在一个步数的集合：$f_1,f_2,\ldots,f_m$。简单想一下，我们也可以得出和上面公式一样的公式：
$$
ans= \begin{cases}n, \gcd(f_1,f_2,\ldots,f_n,n)=1 \\\\-1, \gcd(f_1,f_2,\ldots,f_n,n) \neq 1\end{cases}
$$
**特别提示：** 别忘了当 $n=1$ 时集中特殊情况！

**下面为 `c++` 代码：**

```cpp
#include <bits/stdc++.h>
#define M 1500000
using namespace std;

int n, m, t, ans=0;
int a[M], f[M];

inline int read()
{
    int re=0, f=1; char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {re=re*10+(ch-'0'); ch=getchar();}
    return re*f;
}

int main()
{
    t=read();
    while(t--)
    {
        bool flag=true;
        memset(a,0,sizeof(a));
        memset(f,0,sizeof(f));
        n=read(), m=read();
        for(int i=1;i<=m;++i) 
        {
            int x=read();
            a[x]=1;
        }
        if(n==1 && m==0) {printf("1\n"); flag=false; continue;}
        if(m==n || (n==1 && m==1)) {printf("-1\n"); flag=false; continue;}
        if(flag==true)
        {
            int k=0; ans=0;
            for(int i=1;i<=n;++i)
            {
                if(a[i]==0) ans=i, k=i;
                break;
            }
            for(int i=k+1;i<=n;++i) if(a[i]==0) ans=__gcd(ans,i);
            ans=__gcd(ans,n);
            if(ans==1) printf("%d\n",n);
            else printf("-1\n");            
        }
 
    }
    return 0;
}
```



---

## 作者：chenzexin2012 (赞：2)

# 题解：P5582「SWTR-1」Escape

[题目传送门](https://www.luogu.com.cn/problem/P5582)

这道题简要来说，就是考察 $\gcd$ 最大公约数和思维能力的。

分析一下输入，$a_i$ 到 $a_k$ 表示的是**不能走的**步数，题目中也说了，$i\in[1,n]$，所以考虑 $1-n$ 就可以了。

这一道题的思路非常简单，只需要把 $1-n$ 中可以走的步数枚举出来，与 $n$ 取最大公约数就可以了。

根据样例 $3$ 举个例子：

样例 $3$ 中共有 $6$ 平台，$\texttt{Sunny}$ 可以走 $6$ 以内除去 $1、3、5$ 外的其它步数，即 $2、4、6$ 步，而且 $2、4、6、6、(n)$ 的最大公约数为 $2$，所以整个步数把平台分成了 $n÷2$ 组，即 $3$ 组，每组有 $2$ 个平台，而这 $2$ 个平台中只有 $1$ 个能够跳到，另 $1$ 个跳不到，是因为所跳的步数**永远是偶数**，$\texttt{Sunny}$ 永远跳不到奇数平台上。

思路有了，开始干活！

我们需要一个求最大公约数的函数。
```cpp
int gcd(int x,int y){
	return !y?x:gcd(y,x%y);
}
```  
接下来是 $AC$ 代码:
```cpp
#include<bits/stdc++.h>
#define int long long//养成好习惯，避免超int
using namespace std;
int T,k,n,a[1000010];//T是多组数据，n是平台个数，k是他不能跳的平台的个数 
signed main(){//前面define了，这里就要用无符号整数signed 
	scanf("%lld",&T);
	while(T--){
		memset(a,0,sizeof a);//多测一定要记得清空 
		scanf("%lld %lld",&n,&k);//个人喜欢用scanf 
		for(int i=1;i<=k;i++){
			int t;
			scanf("%lld",&t);//输入不能跳的步数 
			a[t]=1;//打好标记 
		}
		if(k==n){//一定要记得特判，我就这么错过好几次 
			printf("-1\n");
			continue;
		}
		int cnt=n;//最大公约数，n要作为最后的结果，不能去修改，用cnt去顶替 
		for(int i=1;i<=n;i++){
			if(!a[i])
				cnt=__gcd(cnt,i);//求最大公约数，这是自带的。
		}
		if(cnt==1) printf("%lld\n",n);// 最大公约数为1，每一个都可以跳到，共n个平台，只需跳n次就足够了 
		else printf("-1\n");//最大公约数不为0,每一组中一定有平台跳不到，输出-1 
	}
	return 0;//完美结束 
}
```
谢谢各位大佬的观看。

---

## 作者：MaiJingYao666 (赞：2)

# P5582 「SWTR-1」Escape 题解  
可以不难想到，当我们不得不跳回到原来的位置时，一定是误解的情况。另向说明，如果有解，解必然是 $n$，因为没有重复的跳的位置。  
怎么判断是否有解呢？这时引理**扩展裴蜀定理**，我们设可以跳的位置为 $b_i$，可以知道 $a_1b_1+a_2b_2+...+a_{n-k}b_{n-k} \equiv c \pmod n$，其中 $c$ 表示每次意向中前进的步数，因为 $c \bmod \gcd(b_1,b_2,..,b_{n-k}) = 0$，且 $\gcd(c,n)=1$，容易推出 $\gcd(n,b_1,b_2,...,b_{n-k})=1$ 时，有解。  
### AC 代码

```cpp
#include<iostream>
using namespace std;
int T;
int n,k;
int a[1000005];
bool c[1000005];
inline int gcd(int a,int b){
	int i=0,j=0;
	while(!(a&1)) a>>=1,i++;
	while(!(b&1)) b>>=1,j++;
	if(j<i)i=j;
	while(1){
		if(a==b) return a<<i;
		if(a<b){
			int t=a;
			a=b;
			b=t;
		}
		a-=b;
		while(!(a&1))a>>=1;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		
		for(int i=1;i<=n;i++)c[i]=1;
		for(int i=1;i<=k;i++){
			cin>>a[i];
			c[a[i]]=0;
		}
		if(k==n){
			cout<<-1<<'\n';
			continue;
		}
		int t=n;
		for(int i=1;i<=n;i++){
			if(c[i]){
				t=gcd(t,i);
			}
		}
		if(t==1)cout<<n<<'\n';
		else cout<<-1<<'\n';
	}
}
```

---

## 作者：Tomwsc (赞：2)

# P5582 「SWTR-1」Escape 题解

直接放结论：

设所有可行的步数为序列 $l$，长度为 $m$。

- 若 $\gcd(l_1 , l_2 , \cdots , l_m)=1$，则答案为 $n$
- 若 $\gcd(l_1 , l_2 , \cdots , l_m)\neq1$，则输出```-1```

需要特判一下 $n=1$ 且 $k=1$ 的情况，其它就没啥了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e6 + 10;
int t;
int n , k;
int a[MAXN];
bool tot[MAXN] , flag;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> n >> k;
		memset(tot , 0 , sizeof(tot));
		int ans = n;
		for(register int i = 1;i <= k;i ++) {
			cin >> a[i];
			tot[a[i]] = true;
		}
		if(n == 1 && k == 1) {
			cout << "-1" << '\n';
			continue;
		}
		for(register int i = 1;i <= n;i ++)
			if(!tot[i])
				ans = __gcd(ans , i);
		if(ans == 1)
			cout << n << '\n';
		else
			cout << -1 << '\n';
	}
	return 0;
}
```

---

## 作者：ingo_dtw (赞：2)

# P5582 「SWTR-1」Escape
### 题目大意：
平台形成环形，编号 $0$ 到 $n-1$。起点是 $0$，每次跳跃可以选择步长（$1$ 到 $n$ 之间，除去禁止的步长）。目标是覆盖所有平台（包括再次访问 $0$），并求最少跳跃次数。
### 解题思路：
- 如果允许的步长集合与 $n$ 的最大公约数为 $1$，则可以通过 $n$ 次跳跃覆盖所有平台；否则无解。
- 计算所有允许步长与 $n$ 的 $\gcd$，然后求这些 $\gcd$ 值的最大公约数。若为 $1$，则输出 $n$；否则输出 $-1$。
- 枚举 $n$ 的所有因子 $d$，对于每个 $d$，计算 $m=n \div d$。检查是否存在步长 $a=k \times d$（$k$ 与 $m$ 互质）在允许集合中。
- 对每个 $m$，标记所有与 $m$ 互质的 $k$，并检查对应的 $a=k \times d$ 是否允许。
### Ac Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#ifdef __linux__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc _getchar_nolock
#define pc _putchar_nolock
#endif
#define int long long
#define R register
#define rint register int
#define _ read<int>()
inline bool blank(const char x) 
{
    return !(x^9)||!(x^13)||!(x^10)||!(x^32);
}
template<class T>inline T read() 
{
    T r=0,f=1;R char c=gc();
    while(!isdigit(c)) 
    {
        if(c=='-') f=-1;
        c=gc();
    }
    while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=gc();
    return f*r;
}
inline void out(int x) 
{
    if(x<0) pc('-'),x=-x;
    if(x<10) pc(x+'0');
    else out(x/10),pc(x%10+'0');
}
inline void read(char &x) 
{
    for(x=gc();blank(x)&&(x^-1);x=gc());
}
const int maxn=1000010;
int a1[maxn];
int mk[maxn];
int d1[2000];
int pr[20];
inline int gcd(int a,int b) 
{
    if(!a||!b) return a|b;
    while(b) 
    {
        a%=b;
        if(!a) return b;
        b%=a;
    }
    return a;
}
signed main() 
{
    int T=_;
    while(T--) 
    {
        int n=_,k=_;
        for(rint i=1;i<=n;++i) a1[i]=1;
        for(rint i=1;i<=k;++i) 
        {
            int a=_;
            if(a>=1&&a<=n) a1[a]=0;
        }
        int c1=0;
        if(n==1) 
        {
            d1[c1++]=1;
        } 
        else 
        {
            for(rint i=1;(long long)i*i<=n;++i) 
            {
                if(n%i==0) 
                {
                    d1[c1++]=i;
                    if(i*i!=n) d1[c1++]=n/i;
                }
            }
        }
        int g0=0;
        for(rint i=0;i<c1;++i) 
        {
            int d=d1[i];
            int m=n/d;
            for(rint j=1;j<=m;++j) mk[j]=1;
            int tm=m;
            int cp=0;
            if(tm>1) 
            {
                for(rint j=2;(long long)j*j<=tm;++j) 
                {
                    if(tm%j==0) 
                    {
                        pr[cp++]=j;
                        while(tm%j==0) tm/=j;
                    }
                }
                if(tm>1) pr[cp++]=tm;
            }
            for(rint p=0;p<cp;++p) 
            {
                for(rint j=pr[p];j<=m;j+=pr[p]) 
                {
                    mk[j]=0;
                }
            }
            bool fl=0;
            for(rint j=1;j<=m;++j) 
            {
                if(mk[j] && a1[j*d]) 
                {
                    fl=1;
                    break;
                }
            }
            if(fl) 
            {
                if(!g0) g0=d;
                else g0=gcd(g0,d);
            }
        }
        if(g0==1) 
        {
            out(n);
            pc('\n');
        } else {
            out(-1);
            pc('\n');
        }
    }
    return 0;
}
```

---

## 作者：龙行龘龘 (赞：2)

# 这题我说入门都不过分

题面讲的已经快把答案告诉你了,就需要你来特判n = k = 1和d > 1的情况

如果可以走，求一下gcd就完成了!

顺便献上我的blog:https://www.luogu.org/blog/Root-std-admin/

话不多说,放代码:

```cpp
//Written By:Jason_Root
//Time Limit : 1000 MS
//Memory Limit : 65536 KB
#include<bits/stdc++.h>
#define For(e) for(unsigned i = 1;i <= e;i++)
using namespace std;
const unsigned maxn = 1e7;
inline unsigned read() {
	char ch = getchar();
	unsigned x = 0, f = 1;
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
unsigned gcd(unsigned a,unsigned b) {
	if(!b) {
		return a;
	} else {
		return gcd(b,a%b);
	}
}
unsigned T;
unsigned a[maxn];
bool pd[maxn]={0};
void func() {
	ios_base::sync_with_stdio(false);
	T = read();
	while(T--) {
		memset(pd,0,sizeof(pd));
		unsigned n,k,d;
		n = read();
		k = read();
		d = n;
		For(k) {
			a[i] = read();
			pd[a[i]] = 1;
		}
		if(n == 1&&k == 1) {
			printf("-1\n");
			pd[1] = 0;
			continue;
		}
		For(n) {
			if(!pd[i]) {
				d = gcd(d,i);
			}
		}
		if(d > 1) {
			printf("-1\n");
		} else {
			printf("%u\n",n);
		}
	}
	return;
}
int main(int argc, char const *argv[]) {
	func();
	return 0;
}

```
真心感谢大家观看,谢谢!!!

---

## 作者：封禁用户 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P5582)

## 思路
~~废话：第一步先读题。~~
#### 下面切入正题

读完题后可以发现，顺时针能跳的**次数** $d$ 就是 $\gcd(b_1,b_2,\dots,b_x,b_n)$ 。

再用一个数组存不能一次顺时针跳过的平台。

若 $n=k=1$ 则无解。

**Sol**：

1. $d>1$ 无解。
2. $d=1$ 需要 $n$ 次。

## Code
```

#include<bits/stdc++.h> 
using namespace std;

int T,b[1000010];
bool vis[1000010];
int n,k,d;

int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		d=n;
		
		for(int i=1;i<=k;i++){//存入数组 
			cin>>b[i];
			vis[b[i]]=1;
		}
		
		if(n==1&&k==1){//特殊情况 
			printf("%d\n",-1);
			vis[1]=0;//清零 
			continue;
		}
		
		for(int i=1;i<=n;i++){
			if(vis[i]==0) d=__gcd(d,i);//求可以跳的数的最大公因数
		}
		
		if(d>1) printf("-1\n");//最大公因数不为一
		else cout<<n<<"\n";//最大公因数为一 
		
		for(int i=1;i<=k;i++){
			vis[b[i]]=0;//清零 
		}
	}
	return 0;
}
```

---

## 作者：Zhl2010 (赞：1)

## 题目概括
背景十分长，但是主要内容就几个字：

有一个从 $1$ 到 $n$ 的环，让你每次跳指定的距离，不重不漏经过每一个点。

## 思路
这道题还是很水，主要是用分类讨论。

用 $pd_i$ 表示距离 $i$ 能否走。

对于每一个可以走的长度 $x_i$，如果 $\gcd(b_1,b_2,...,b_{n-1},n)$ 为 $1$，就代表每一个点都可以走到，又因为有 $n$ 个点，所以答案为 $n$，否则，答案为 $-1$。
 ### gcd 函数（模板）
 ```cpp
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
```

**别忘了这题还有特殊情况**：当 $n$ 和 $k$ 都为 $1$ 时，当然不可能走完所有点，因为一种走法都没有。

**还有一个小细节**：有多组测试数据，注意数组 $pd$ 的赋值。

## 代码+注释
```cpp
#include<bits/stdc++.h> 
using namespace std;
int T,a[1000010];
bool pd[1000010];
int gcd(int a,int b){//最大公因数模板 
	return b==0?a:gcd(b,a%b);
}
int main(){
	scanf("%d",&T);
	while(T--){
		int n,k,d;
		scanf("%d%d",&n,&k);
		d=n;
		/*将数据存入pd数组*/
		for(int i=1;i<=k;i++)scanf("%d",&a[i]),pd[a[i]]=1;
		if(n==1&&k==1){//不可能完成的特殊情况 
			cout<<"-1"<<endl,pd[1]=0;
			/*pd[1]=0 是赋值*/
			continue;
		}
		for(int i=1;i<=n;i++){
			if(!pd[i])d=gcd(d,i);//求这一堆数的最大公因数
		}
		/*最大公因数不为一，是不可能的情况*/
		if(d>1)cout<<"-1"<<endl;
		else cout<<n<<endl;//成立的情况因为有n个数，所以答案为n 
		for(int i=1;i<=k;i++)pd[a[i]]=0;//赋值 
	}
	return 0;
}
```

---

## 作者：backkom (赞：1)

太菜了，这道题想了很久。写篇题解，详细证明一下。

题面读完，不难转换，**有解**的条件为: 



是否存在一组整数序列$k_1,k_2,....k_n$,使得:

​	$gcd(b_1*k_1+b_2*k_2+b_3*k_3+...b_k*k_k,n)==1     (一)$ 

其中b_i表示可以“用”的步长.



但是问题转换到这里还不行，求解还是很复杂，~~我就是在这凉凉~~。

看完官方题解，感觉很神奇：

​	$gcd(b_1,b_2,..,b_n,n)==1$

WTF? 这个条件就够了嘛？官方给的证明过程，感觉有点乱，想了很久，自己证明一下这个式子。

- 首先，对于$d_1=gcd(b_1,n)$,我们易知，这意味着我们可以遍历1~n中$d_1$倍数的数。也即是说，在当前局面(遍历到$d_1$时),我们能够遍历$d_1$的倍数的数，那么显然有解的情况为**某种局面下di=1**。

- 其次，我们知道：设$d_i$为$(b_1,b_2,b_3...b_i)$条件下，我们能够使用的最小倍数(这个话有点绕)。那么$d_{i+1}=gcd(d_i,b_{i+1})$,原因如下:

  ​	首先，对于$d_{i+1}$的更新我们不需要去考虑$b_1...b_i$，**因为$d_i$已经等价的表示了它们线性组合能够到达的最小倍数**，其次，对于$b_{i+1}$为什么可以通过与$d_i$求gcd的方式来更新$d_{i+1}$，证明如下：	$d_i*x+b_{i+1}*y = k*gcd(d_i,b_i+1)$,**一定有整数解**。这个公式意味着d_{i}与b_{i+1}通过线性变换（有整数解的情况下）所能达到的最小倍数是gcd（k=1）。

- 最后我们通过递推/DP，就可以得到那个神奇的表达式了，并且可以理解它与（一）式在内涵上是等价的。~~比较自信的说~~，甚至我们可以通过扩欧求出每一个系数呢~~。

---

## 作者：Angelastar (赞：0)

**题意抽象**

令序列 $l$ 为所有可以走的步数，若 $l$ 中存在一组 $l_{i}$ 和 $l_{j}$，使得其互质，则可以过关，反之则无法过关。

---

**注意**

1. 特判 $n=1$ 且 $k=1$ 的情况，答案为 $-1$。
2. 若可以过关，则最小一定为 $n$ 步。
3. 数组记得清零，判断时需判断可行步数的 $\gcd$。

---

**code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+5;
int t,n,k,a[N],ans,l[N];
int gcd(int a,int b){return !b?a:gcd(b,a%b);}//最大公因数
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		ans=n;
		memset(l,0,sizeof(l));//一定要清零！！！
		for(int i=1;i<=k;i++){
			cin>>a[i];
			l[a[i]]=1;//l数组标记不可行
		}
		if(n==1&&k==1){//特判
			cout<<-1<<endl;
			continue;
		}
		for(int i=1;i<=n;i++){
			if(!l[i])ans=gcd(ans,i);//记住是判断可行步数
		}
		if(ans==1){
			cout<<n<<endl;
		}else{
			cout<<-1<<endl;
		}
	}
	return 0;//好习惯
}
```

---

## 作者：Vincent_SyNc (赞：0)

## 题意简述
给定序列 $a_1,a_2,a_3,...,a_k$，这 $k$ 个数不能使用，那么能用的只有在正整数 $1\sim n$ 中不在序列里的数，要求顺时针经过每个位置的跳跃总次数。

那么如何用剩下的数求出答案呢？

## 算法详解
可以先从简单的数据来想：

若 $n=k=1$，则无解，因为唯一的跳法也被堵死了，必然无解。

然后不难发现，如果想要经过每个位置的话，就一定要有**只走一步**的能力。如果有，那么我们至少需要 $n$ 步（起点不算，不用 $+1$），否则，也无解。所以我们只需判断有没有这个能力就行。

如果在剩余的数中，没有任意两个数互质，那么说明没有**只走一步**的能力，因为只有互质可以通过跳来回得出走 $1$ 步。

对于互质的判断只需把剩下的数求一遍 $\operatorname{gcd}$，如果最终结果是 $1$ 说明有两数互质，否则无解。

假设 $d$ 是最终数列 $\operatorname{gcd}$ 的结果，则有以下情况：

$d>1$ 时，无解。

$d=1 $ 时，需要 $n$ 次。

## 警钟
多组数据别忘初始化！

$\operatorname{gcd}$ 函数不要写反！

## AC Code
```cpp
#include<bits/stdc++.h> 
using namespace std;
int a[1000010],n,k,d;
bool used[1000010];
int main(){
	int t;cin>>t;
	while(t--){
		cin>>n>>k;d=n;
		if(n==1&&k==1){cin>>k;cout<<"-1\n";continue;}//无解，记得把第一个数读入 
		for(int i=1;i<=k;i++)cin>>a[i],used[a[i]]=1;//标记每个不许用的数 
		
		for(int i=1;i<=n;i++)
		if(!used[i])//剩余数的最大公约数
		d=__gcd(d,i);
		
		if(d!=1)cout<<"-1\n";//无解
		else cout<<n<<"\n";//否则至少n步
		
		for(int i=1;i<=k;i++)used[a[i]]=0;//初始化方便下次用 
	}
}
```

---

## 作者：a_123_a (赞：0)

### 思路
读完题目,我们可以发现他就是一道数学题，而且答案几乎都告诉你了而我们只需要判断当 $ n = k = 1 $ 时，很明显它是不成立的。判断完之后，我们在跑一遍 $ \gcd $ 就可以了。

我们令所有可行步数是 $ b_1,b_2,\cdots ,b_x $，如果 $ \gcd(b_1,b_2,\cdots,b_x,n) = 1$，那么他每一个格子就都能跳到且只用跳 $ n $ 次，否则就不行，输出 $ -1 $。

```c
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
#define For(i,a,b) for(int i = a;i <= b;i++)
int a[N],n,k,d;
bool vis[N];
int main() {
	int T;cin>>T;
	while(T--) {
		memset(vis,0,sizeof(vis));
		cin>>n>>k;
		d=n;
		For(i,1,k) {
			cin>>a[i];
			vis[a[i]]=1;//装桶 
		}
		if(n == k && k == 1) { //特判 n == k == 1 
			printf("-1\n");vis[1] = 0;
			continue;
		}
		For(i,1,n)
			if(!vis[i])
				d = __gcd(d,i);
		if(d > 1) printf("-1\n");//d大于一，所以他只能调到d的倍数的台子上 
		else      printf("%d\n",n);
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：
记 $b$ 为可用步数序列，长度为 $m$。

考虑必要性，即每个点都能通过 $b$ 的线性组合在模 $n$ 意义下表示出来。

即 $b_1 \times x_1+b_2 \times x_2+\cdots+b_m \times x_m+n \times x_{m+1}$ 能表示出来 $[0,n]$ 中的每个数，这一部分根据裴蜀定理可得。

这个条件可能是充要的，考虑证明。

**定理：**

对于任意正整数 $a$ 和 $n$，若 $d=\gcd(a,n)$，则在 $\mathbb{Z}_n$ 中，$\langle a\rangle = \langle d\rangle$。

**引理：**

环大小为 $n$，若初始在位置 $p$，每次跳 $k$ 步，$k \mid n$，则到达的位置一定是 $x\equiv p \pmod k$。

**证明：**

考虑原先到达的位置 $x\equiv 0 \pmod k$，初始位置在 $p$ 可看做初始位置在 $0$，跳完后再向右跳一次 $p$ 步，因为跳 $k$ 步能取遍且互不相同的位置 $x\in[0,n],k\mid x$，所以你再向右跳显然也能取遍，且互不相同。

考虑先跳 $b_1$，即记 $d=\gcd(b_1,n)$，跳完了 $d,2 \times d\cdots (n/d-1) \times d,0$，那么考虑只要每次跳完这样的一个循环，能够位移到组内另一个地方即可。

这样每一次跳到的都是不一样的。

即问题变成了 $b_2,b_3 \cdots b_m$ 跳完 $[0,d]$，考虑结构一样，如此操作下去，最终变成 $b_m$ 跳完 $[0,\gcd(n,b_1,b_2 ... b_{m-1})]$，显然在 $\mathbb{Z}_{\gcd(n,b_1,b_2 ... b_{m-1})}$ 中，$|\langle b_m\rangle|=\gcd(n,b_1,b_2 ... b_{m-1})$，因此可以跳完。

然后子问题可以完成，则上级问题推回去也可以完成。
### 完整代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N=(int)(1e6+5);
bool vis[N];
int n,m;
int gcd(int x,int y){
	return !y?x:gcd(y,x%y);
}
void sol(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) vis[i]=0;
	for(int i=1;i<=m;i++) {
		int x; cin>>x; vis[x]=1; 
	}
	int qwq=0;
	for(int i=1;i<=n;i++) {
		if(vis[i]) 
		  continue ;
		if(!qwq) 
		  qwq=gcd(i,n);
		else 
		  qwq=gcd(qwq,gcd(i,n));
	}
	if(!qwq){
		cout<<"-1\n"; 
		return ;
	}
	for(int i=1;i<=n;i++) {
		if(i%qwq!=0) {
			cout<<"-1\n";
			return ;
		}
	}
	cout<<n<<'\n';
}
signed main(){
	int T; 
	cin>>T; 
	while(T--) 
	  sol();
	return 0; 
}
```


---

## 作者：AoPSer (赞：0)

比较朴素的数学题

首先分析题目：

可以发现：题面读完，不难转换，有解的条件为:

是否存在一组整数序列 $k_1 , k_2 , \dots , k_n$ ,使得: $\gcd(b_1\times k_1+b_2\times k_2+\dots+b_n\times k_n,n)=1$

这个式子的推导实际上没那么复杂

由裴蜀定理：即存在 $x,y(x,y\in Z)$ ,使得 $(\Sigma_{i=1}^{n}x\times k_i\times b_i)+y\times n=1$

从而由裴蜀定理知 $\gcd(b_1,b_2,\dots,b_n,n)=1$

然后就能很轻松地做出来了

代码(虽然我觉得不大重要)：
```
#include<bits/stdc++.h>
using namespace std;
int t,n,k,gcdd;
bool a[3000001];
int gcd(int num1,int num2)
{
	if(num2==0)return num1;
	return gcd(num2,num1%num2);
}
int main(){
	scanf("%d",&t);
	while(t--)
	{
		memset(a,0,sizeof(a));
		scanf("%d%d",&n,&k);
		gcdd=n;
		for(register int i=1,x;i<=k;i++)scanf("%d",&x),a[x]=true;
		if(n==1&&k==1){cout<<"-1\n";continue;}
		for(register int i=1;i<=n;i++)if(!a[i])gcdd=gcd(gcdd,i);
		if(gcdd==1)printf("%d\n",n);
		else printf("-1\n");
	}
}
```

---

