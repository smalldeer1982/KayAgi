# [ABC135F] Strings of Eternity

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc135/tasks/abc135_f

英小文字からなる二つの文字列 $ s,\ t $ が与えられます。次の条件を満たす非負整数 $ i $ の個数が有限であるか判定し、有限である場合はそのような $ i $ の最大値を求めてください。

- ある非負整数 $ j $ が存在し、$ t $ を $ i $ 個連結して得られる文字列は、$ s $ を $ j $ 個連結して得られる文字列の部分文字列である。

## 说明/提示

### 注記

- 文字列 $ a $ が文字列 $ b $ の部分文字列であるとは、ある整数 $ x $ $ (0\ \leq\ x\ \leq\ |b|\ -\ |a|) $ が存在して任意の整数 $ y $ $ (1\ \leq\ y\ \leq\ |a|) $ に対して $ a_y\ =\ b_{x+y} $ であることです。
- 任意の文字列に対し、それを $ 0 $ 個連結して得られる文字列は空文字列であるとします。また、上記の定義より、空文字列は任意の文字列の部分文字列です。したがって、任意の二つの文字列 $ s,\ t $ に対して $ i\ =\ 0 $ は問題文中の条件を満たします。

### 制約

- $ 1\ \leq\ |s|\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ |t|\ \leq\ 5\ \times\ 10^5 $
- $ s,\ t $ は英小文字からなる。

### Sample Explanation 1

$ t $ を $ 3 $ 個連結して得られる文字列 `ababab` は、$ s $ を $ 2 $ 個連結して得られる文字列 `abcabababcabab` の部分文字列であるため、$ i\ =\ 3 $ は条件を満たします。 一方で、$ t $ を $ 4 $ 個連結して得られる文字列 `abababab` は、$ s $ を何個連結しても部分文字列として現れないため、$ i\ =\ 4 $ は条件を満たしません。 同様に、$ 5 $ 以上の任意の整数も条件を満たしません。よって条件を満たす非負整数 $ i $ の個数は有限で、その最大値は $ 3 $ です。

### Sample Explanation 2

任意の非負整数 $ i $ に対し、$ t $ を $ i $ 個連結して得られる文字列は、$ s $ を $ 4i $ 個連結して得られる文字列の部分文字列です。したがって条件を満たす非負整数 $ i $ は無限に存在します。

### Sample Explanation 3

注記で述べたように、$ i\ =\ 0 $ は必ず条件を満たします。

## 样例 #1

### 输入

```
abcabab
ab```

### 输出

```
3```

## 样例 #2

### 输入

```
aa
aaaaaaa```

### 输出

```
-1```

## 样例 #3

### 输入

```
aba
baaab```

### 输出

```
0```

# 题解

## 作者：MikukuOvO (赞：5)

如果$|S|>|T|$，不难发现只要将$S$倍长，那么最长重复子串就一定在$SS$中，否则就一定是无穷，找这个可以通过$hash$来实现，否则我们将$S$倍长到$T$的两倍即可，实现时为了方便判断无穷需要多倍长几遍。

```cpp
const int N=2e7+5;
const int base=131;
const ll mod=192608179;

string a,b;
int tag[N];
ll ha[N],hb[N],fac[N];

ll gethash(int x)
{
    if(x+b.size()>a.size()) return -1;
    return (ha[x+b.size()-1]-ha[x-1]*fac[b.size()]%mod+mod)%mod;
}
int main()
{
    fio();
    cin>>a>>b;
    while(a.size()<b.size()*2) a=a+a;
    a=a+a,a=a+a,a=a+a;
    fac[0]=1,ha[0]=a[0]-'a',hb[0]=b[0]-'a';
    for(int i=1;i<a.size();++i) fac[i]=fac[i-1]*base%mod;
    for(int i=1;i<a.size();++i) ha[i]=(ha[i-1]*base%mod+a[i]-'a')%mod;
    for(int i=1;i<b.size();++i) hb[i]=(hb[i-1]*base%mod+b[i]-'a')%mod;
    for(int i=0;i<a.size();++i) tag[i]=hb[b.size()-1]==gethash(i);
    int ans=0;
    for(int i=a.size()-b.size();i>=0;--i) if(tag[i]) tag[i]+=tag[i+b.size()],ans=max(ans,tag[i]);
    if(ans+1>=a.size()/b.size()) print(-1);
    else print(ans);
    end();
}
```

---

## 作者：EnofTaiPeople (赞：4)

### Part1 前言
显然我是入门 OIer，只会本题的大常数暴力做法。

显然这是一道水题，但我还是会暴力写挂。

真是沦落了！

### Part2 问题转化
首先，可能会出现 $|S|<|T|$ 的情况，我们需要将其补至 $|S|\ge|T|$，于是，$T$ 有两种情况：

1. $T$ 可以是两个 $S$ 拼起来的中间结果；
2. $T$ 是 $S$ 的子串。

由于有 1 的存在，我们需要将 $S$ 再复制一遍，查询 $T$ 的最大连续出现次数，记为 $res_1$。

然而，$T$ 可能会能进行进一步复制，这样的话，我们将 $S$ 在复制一遍，接在后面，记此时的答案为 $res_2$。

注意到 $S$ 复制了多次，可以证明，如果 $res_2>res_1$，则答案趋于 $+\infty$，这时需要输出 `inf`，否则，输出 $res_1$。

### Part3 具体实现
发现我们只需要求 $T$ 在 $S$ 中的最大连续出现次数，可以对 $S$ 建后缀自动机，然后在上面跳就可以了，如果发现节点为空，就说明该串已经不能在加一次了。

然而，后缀自动机的 $O(n|\sum|)$ 的空间有点寄，虽然也没有卡空间。

但是，我居然错了两处！一处连续状态转移的判定 `ln[y]+1==ln[t[y][p]]+1`，一处 `memset(t,0,sizeof(cnt));`，神奇的是，这样还只 `WA` 了一个点！

好了，其实改完之后是可以通过的：
```cpp
#include<icecream>
using namespace std;
string S,T,s;
const int N=8e6+6;好像空间卡得有点紧，但只有 900MB。
struct sfxatmt{suffix-automaton
    int t[N][28],f[N],ln[N],ls,cnt;
    sfxatmt(){ls=cnt=1;}
    void clear(){
        while(cnt){
            memset(t[cnt],0,sizeof(t[cnt]原来这里是“cnt”));
            f[cnt]=ln[cnt]=0,--cnt;
        }ls=cnt=1;
    }
    void append(int p){
        int x=++cnt,y,z,r;ln[x]=ln[ls]+1;
        for(y=ls;y&&!t[y][p];t[y][p]=x,y=f[y]);
        if(!y)f[x]=1;
        else if(ln[y]+1==ln[z=t[y][p]]原来这里有一个”+1“)f[x]=z;
        else{
            ln[r=++cnt]=ln[y]+1,f[r]=f[z];
            memcpy(t[r],t[z],sizeof(t[r]));
            while(y&&t[y][p]==z)t[y][p]=r,y=f[y];
            f[x]=f[z]=r;
        }ls=x;
    }
    int get(string &s){
        int x=1,res=-1;
        while(x){
            ++res;
            for(char c:s)x=t[x][c-'a'+1];
            在后缀自动机上跳状态，x=0 就结束
        }return res;
    }
}A;
int r1,r2;
int main(){
    ios::sync_with_stdio(false);
    cin>>S>>T;
    if(S.size()<T.size()){
        for(s=S;s.size()<T.size();s+=S);
        不停地复制！不停地复制！不停地复制！不停地复制！不停地复制！
    }else S+=S;
    S+=S;
    for(char c:S)A.append(c-'a'+1);
    r1=A.get(T),S+=S,A.clear();
    for(char c:S)A.append(c-'a'+1);
    r2=A.get(T);
    if(r2>r1)puts("-1");
    else printf("%d\n",r1);
    return 0;
}
```

---

## 作者：极寒神冰 (赞：3)

(不知道为什么在后台公式炸了前台就没事

(这里字符串默认第一个位置从$0$开始)

简化一下题意:$t$在$s'$中连续出现的最大次数是多少,其中$s'$是字符串$s$的无限重复.

对于$0$到$\left |s\right|-1$的每一个整数$i-1$,假设我们已经知道$s'$子串第$i$个字符到第$i+\left| t \right|-1$个字符是否等于$t$ ( $match_i=1$代表匹配上).然后可以直接通过模拟在$O(\left|s\right|)$中找到答案.

因为$s'$是具有周期性的.用图论的术语来说,答案是有向图的最长路径:

- 这张图有 $\left|s\right|$ 个顶点,分别称作 $0,1,\cdots,\left|s\right|-1$ 
- 该图具有有向边 $i \to (i+ \left| t \right| ) \bmod \left|s \right| \mbox{if }  match_i =1$ .否则没有边.

剩下的任务是求出所有的 $match_0,\cdots ,match_{\left|s\right|-1}$ .显然不能naive的暴力比较$s'$和$t$,这样最坏复杂度是$O((|s|+|t|)\times |t|)$.当然事实上有很多算法可以在线性时间解决这个问题

[KNP algorithm(a link to Wikipedia article)](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)

[Z algorithm (A link to GeeksforGeeks article)](https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/)

(事实上你谷也有 [【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375),[【模板】扩展 KMP（Z 函数）](https://www.luogu.com.cn/problem/P5410)

否则，你还可以使用 $hash$ 解决,但是注意不要用自然溢出,否则将会被卡.推荐模数为 $10^{16}+61$ 

以上大部分翻译自官方题解.

附上菜鸡的代码

```
signed main()
{
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	for(;n<(m<<1);cpy(s+1+n,s+1,n),n<<=1); 
	cpy(s+1+n,s+1,n),n<<=1;
	for(int i=2,j=0;i<=m;i++)
	{
		while(j&&t[i]!=t[j+1]) j=nxt[j];
		if(t[i]==t[j+1]) j++;
		nxt[i]=j;
	}
	for(int i=1,j=0;i<=n;i++)
	{
		while(j&&s[i]!=t[j+1]) j=nxt[j];
		if(s[i]==t[j+1]) j++;
		if(j==m) {
			tmp[i]=tmp[i-m]+1;
			ckmax(ans,tmp[i]);
		}
	}
	if(ans>=n/m-1) puts("-1");
	else printf("%lld\n",ans);
}
```

---

## 作者：RandomLife (赞：2)

[原题链接](https://www.luogu.com.cn/problem/AT_abc135_f)

### 简要题意

给定字符串 $s,t$，求最大整数 $k$，使 $t$ 首尾相接复制 $k$ 次是 $s$ 首尾相接复制无穷次的子串，若 $k$ 是无穷大则输出 $-1$。

### Solution

以下字符串下标均以 $0$ 开头。

设初始时 $s$ 长度为 $n$，$t$ 长度为 $m$。

首先我们先将 $s$ 复制一遍接在结尾，然后不断重复直到长度达到 $m$ 的两倍。

然后用滚动哈希遍历一遍 $s$ 所有开头下标在 $0\sim n-1$ 之间且长度为 $m$ 的子串，对于每个 $s_{i\sim i+m-1}$ 等于 $t$ 的 $i$，标记 $tag_i=1$。

具体的滚动哈希请见代码。注意：哈希不要 unsigned long long 自然溢出，会被毒瘤的 atcoder 卡掉。

然后我们就是要求一个最长的序列 $p$，使得对于所有 $i\geq 2$，有 $p_i-p_{i-1}\equiv m\pmod n$，且 $tag_{p_i}$ 和 $tag_{p_{i-1}}$ 都为 $1$。

我们可以对于所有满足上述条件的 $p_i$ 和 $p_{i-1}$ 之间连一条边（$p_{i-1}$ 连向 $p_i$）。显然，最终会形成若干条链和若干个环组成。如果出现环，则答案为 $-1$，否则为最长的链长。

### AC Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,mod=998244353;
string s,t;
int n,m,ans=0,Next[N],sum=0,c=0;
long long p=1,h1=0,h2=0;
bool tag[N],isHead[N],vis[N];
int main(){
	cin>>s>>t;
	n=s.size(),m=t.size();
	while(s.size()<m*2)s+=s;
	s+=s;
	for(int i=0;i<m;++i)h1=(h1*131+s[i])%mod;
	for(int i=0;i<m;++i)h2=(h2*131+t[i])%mod;
	for(int i=1;i<m;++i)p=p*131%mod;
	if(h1==h2)tag[0]=1,c++;
	for(int i=1;i<n;++i){
		h1=(h1-p*s[i-1]%mod+mod)%mod,h1=(h1*131+s[i+m-1])%mod;
		if(h1==h2)tag[i]=1,c++;
	}
	for(int i=0;i<n;++i)Next[i]=-1;
	for(int i=0;i<n;++i)
		if(!vis[i]&&tag[i]){
			isHead[i]=1;
			for(int j=i,pre=-1;tag[j];pre=j,j=(j+m)%n){
				if(pre!=-1)Next[pre]=j,isHead[j]=0;
				if(vis[j])break;
				vis[j]=1;
			}
		}
	for(int i=0;i<n;++i)
		if(isHead[i]){
			int cnt=0;
			for(int j=i;j!=-1;j=Next[j])cnt++;
			ans=max(ans,cnt),sum+=cnt;
		}
	if(sum<c)ans=-1;
	cout<<ans;
	return 0;
}
```

---

## 作者：L_zaa_L (赞：2)

## 解题思路
显然，这道题最开始我们需要倍长原字符串 $s$，让他的长度起码大于 $2\times M$ 这样可以避免判断不了`-1`、匹配数少了等情况。

不妨用 KMP 匹配一遍，看看 $S$ 中那些位置能和 $T$ 进行匹配，我们设当前位置是 $x$ 满足了匹配要求，则匹配数就应该是 $x-|T|$ 位子上的匹配数加上 $1$，可以记录一个 $dp$ 来存每个位置上的答案，特别的对于无解的情况就是我们的答案大于等于 $\frac {|S|}{|T|}-1$。 

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*f;
}
const int N=5014514;
int n;
bool flag[N];
char S[N],T[N],s[N];
int p[N];
int dp[N];
int ans=0;
signed main(){
	//freopen("AT_abc135_f.in","r",stdin);
	//freopen("zaa.out","w",stdout);
	scanf("%s%s",S+1,T+1);
	int N=strlen(S+1),M=strlen(T+1);
	int ggg=1;
	for(int i=1;i<=N;i++){
		s[i]=S[i];
	}
	while((ggg-5)*N<M*2){//倍长，多复制几遍，防止出问题
		ggg++;
		for(int i=1;i<=N;i++){
			s[i+(ggg-1)*N]=S[i];
		}
	}
	n=ggg*N;
	int j=0;
    for(int i=1;i<M;++i){
        while(j>0&&T[j+1]!=T[i+1])
			j=p[j];
        if(T[i+1]==T[j+1])
			++j;
		p[i+1]=j;
    }
    j=0;
    for(int i=0;i<n;++i){//KMP板子
        while(j>0&&T[j+1]!=s[i+1])
			j=p[j];
        if(T[j+1]==s[i+1])
			++j;
        if(j==M){
			flag[i-M+2]=1;
			j=p[j];
		}
    }
	for(int i=1;i<=M;i++){
	
		dp[i]=flag[i];
		ans=max(ans,dp[i]);
	}
	for(int i=M+1;i<=n;i++){//计算每个位置上的答案
		if(flag[i])dp[i]=dp[i-M]+1;
		ans=max(ans,dp[i]);
	}
	if(ans>=n/M-1)puts("-1");//判断无解条件
	else printf("%d\n",ans);
	return 0;
}
```


---

## 作者：优秀的渣渣禹 (赞：1)

描述一下题面：
给两个字符串$s$和$t$，记符号$str * x$表示字符串$str$重复$x$次。
定义一个正整数 $k$ 合法，当且仅当满足：存在一个正整数 $j$ ，使得 $t* k$ 是 $s* j$ 的子串
找到最大的合法正整数 $k$，或者判断可以取到无穷大。
$|s|,|t|\leq500000$



容易发现s至多重复两次，否则那么必定取到无穷大
所以对s复制一份，做一遍kmp即可。

代码就不放了QwQ

---

## 作者：zyn_ (赞：0)

题目大意：给定两个字符串 $s,t$。记 $f(s,x)$ 代表将 $x$ 个 $s$ 拼接得到的字符串。求最大的 $k$ 使得存在 $j$ 使 $f(t,k)$ 是 $f(s,j)$ 的子串。

首先固定 $k$ 时 $j$ 当然越大越好，因此可以不妨设 $j$ 趋近于无穷大，设这时的 $f(s,j)$ 为 $S$。

考虑此时 $t$ 在 $S$ 中的哪里作为子串出现，发现出现的位置每 $|s|$ 位就会循环一次。考虑找出这些位置，设为 $[l_i,r_i]$，则连边 $l_i\to r_i+1$（下标模 $|s|$）。

连边形成的图中，一条边对应 $t$ 在 $S$ 中的一次出现；一条长为 $k$ 的链对应 $t$ 在 $S$ 中的连续 $k$ 次出现；一个环对应 $t$ 循环地覆盖了 $S$。

于是答案就是这个图中的最长链的长度，这个容易求出。

现在只需找出：$t$ 在 $S$ 中的哪里作为子串出现。直接在无穷的 $S$ 中找肯定不行，但是可以在某个 $f(s,j)$ 中找。发现只要 $|f(s,j)|\ge |s|+|t|$ 就可以找全了。判断某个子串是否为 $t$ 只需要使用字符串哈希即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000009
int n,m;
char s[N],t[N];
#define ll long long
const ll bs=182376,md=998244353;
ll p[N],f[N],g;
#define w(l,r) ((f[r]-f[(l)-1]*p[(r)-(l)+1]%md+md)%md)
bool u[N],vis[N];int dp[N],ans;
void dfs(int p,int t){
	if(vis[p])return;
	vis[p]=1;
	if(u[p]){
		int nxt=(p+m-1)%n+1;
		if(nxt==t){puts("-1");exit(0);}
		dfs(nxt,t);
		dp[p]=dp[nxt]+1;
	}
	else dp[p]=0;
}
int main(){
	scanf("%s%s",s+1,t+1);
	for(n=1;s[n+1];++n);for(m=1;t[m+1];++m);
	for(int i=n+1;i<=n+m;++i)s[i]=s[(i-1)%n+1];
	p[0]=1;
	for(int i=1;i<=n+m;++i)p[i]=p[i-1]*bs%md,f[i]=(f[i-1]*bs+s[i])%md;
	for(int i=1;i<=m;++i)g=(g*bs+t[i])%md;
	for(int i=1;i<=n;++i)if(w(i,i+m-1)==g)u[i]=1;
	for(int i=1;i<=n;++i)dfs(i,i);
	for(int i=1;i<=n;++i)ans=max(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：_Yonder_ (赞：0)

板子题。

先将 $s$ 补至 $|s|\ge|t|$。

子串有两种情况，一是两个 $s$ 拼起来的中间段，二是 $s$ 原本的子串。

于是将 $s$ 复制一遍，求此时答案。具体的，从后往前跑哈希，当与 $t$ 匹配成功时 $f_i=f_{i+|t|}+1$，答案即为最大的 $f_i$。

对于判断无穷，我们将 $s$ 再复制一遍，若是答案变大了即为无穷。

---

