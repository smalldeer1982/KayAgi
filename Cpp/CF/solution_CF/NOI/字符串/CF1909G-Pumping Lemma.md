# Pumping Lemma

## 题目描述

有两个只含小写字母的字符串 $s$ 和 $t$，长度分别为 $n$ 和 $m$。

请计算满足下列要求的字符串三元组 $(x,y,z)$ 有几个：

- $s=x+y+z$ （$+$ 代表连接）；

- $t = x+\underbrace{ y+\dots+y }_{k \text{ 个}} + z$，其中 $k$ 为整数。

## 样例 #1

### 输入

```
4 8
abcd
abcbcbcd```

### 输出

```
1```

## 样例 #2

### 输入

```
3 5
aaa
aaaaa```

### 输出

```
5```

## 样例 #3

### 输入

```
12 16
abbababacaab
abbababababacaab```

### 输出

```
8```

# 题解

## 作者：unputdownable (赞：17)

非常小清新的题。

**特别定义**称串 $s$ 是串 $t$ 的**周期**，当且仅当存在正整数 $k$ 使 $t=s^k$，即 $t$ 是由 $k$ 个 $s$ 拼接而来。

注：可以理解为类似整周期的东西。

--------

观察样例，会发现 $x+y$ 这个串一定是 $s,t$ 的公共前缀，而 $z$ 是 $s,t$ 的公共后缀。

现在可以判断掉一种无解情况：先暴力找出 $s,t$ 的最长公共前缀（$\text{LCP}$）和最长公共后缀（$\text{LCS}$），如果他们长度和小于 $n$，那么就是无解。

接下来需要观察到两个性质：

----------

观察一下有解的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/knjsm76l.png)

将 $s$ 的两部分（前缀的 $x+y$ 和后缀的 $z$）去掉以后，剩下的是由若干个 $y$ 拼接起来的一个串，这说明 $y$ 是剩下串的一个**周期**。

可以直接用原串长度减去最长 $\text{border}$ 长度求得最短周期长度，然后枚举他的倍数就能得到所有合法周期长度。

（此处记得判找到的周期长度是否整除 $m-n$，若不整除应该直接把周期改成 $m-n$）。

---------

观察取不同长度的前后缀时的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/htxqxt3m.png)

，如果把匹配的 $\text{LCP}$ 长度减一，$\text{LCS}$ 长度加一，相当于把剩下部分的串循环移位一次（因为增减的两个字符需要相同，不然拼出来的就不是 $s$ 了）。

而循环移位并不改变（整）**周期**，因为可以理解成每个周期都做一遍循环移位。

--------

令 $p$ 为剩下串的最短周期，令 $len=m-n$。

回到原题，考虑先枚举 $y$ 的长度 $q$（需要有 $p\mid q,q\mid len$），问题相当于在 $t$ 中要找到一个子串 $[l,r]$ 使得：

1. 长度为 $len+q$（即将公共前缀中的 $y$ 也拿出来），并且要有长度为 $q$ 的周期。

2. 和最长公共前缀至少有 $q$ 的交（即至少有一个 $y$ 的交）。

3. 和最长公共后缀至少有 $q$ 的交（显然前后缀是对称的）。

由上面的分析，可以发现在满足条件 $2,3$ 时，$[l,r-q]$ 和 $[l+q,r]$ 都是观察 $2$ 中能得到的长度为 $len$，周期为 $p$ 的子串；

所以条件 $1$ 此时必然成立。

而条件 $2,3$ 都限制了左端点的一个区间，直接求区间的并即可。

更进一步的，称 $[m-\text{lcs}-len+1,\text{lcp}]$ 这一段为**可活动区间**（即能从前缀改到后缀的那一部分）;

那么对于任意一个 $y$ 的长度 $q$，方案数相当于**可活动区间**中取一个长 $q$ 的子串的方案数。

这个结论和上面区间并的结果是等价的，只是表示上稍有不同。

---------

**code:**

```c++
int n,m,pre,suf;
char s[10000007],t[10000007];
int border[10000007];
signed main() {
    n=read(); m=read();
    scanf("%s%s",s+1,t+1);
    while(s[pre+1]==t[pre+1]&&pre<n) ++pre;
    while(s[n-suf]==t[m-suf]&&suf<n) ++suf;
    if(pre+suf<n) return puts("0"),0;
    const int len=m-n;
    int l=pre+1,r=pre+len;
    border[l]=l-1;
    for(int i=l+1; i<=r; ++i) {
        border[i]=border[i-1];
        while(border[i]>=l&&t[i]!=t[border[i]+1]) border[i]=border[border[i]];
        if(t[i]==t[border[i]+1]) ++border[i];
    }
    int p=r-border[r];
    if(len%p) p=len;
    l=m-suf-len+1; r=pre;
    int lim=min(m-n,pre-l+1);
    i64 Ans=0;
    for(int i=p; i<=lim; i+=p) 
        if(len%i==0) 
            Ans+=(pre-l+1)-i+1;
    write(Ans); puts("");
    return 0;
}
```

------------

后记：

用 $\text{KMP}$ 算法求出的周期不整除原串长度当且仅当 $\text{border}$ 长度小于一半，但是场上的数据并没有卡这个，所以我和 $\text{c}\red {\text{mll02}}$ 没判这个也过了，第二天我们讨论的时候才发现能 $\text{hack}$。


---

## 作者：Graygoo (赞：12)

  比较巧妙的字符串题。首先由于题面给出了条件 $m > n$，因此 $k$ 为正整数。不妨枚举一些东西，比如 $S$ 中 $\texttt{xy}$ 和 $\texttt{z}$ 的分界线就是不错的枚举对象。
  
  枚举好以后，首先当然是判断上述两个串是否与 $T$ 的对应前后缀相匹配。如果是，我们就得到了 $\texttt{y}^{k-1}$。根据弱周期引理，我们只需要找出这么一个长度为 $m-n$ 的串的最小周期即可，剩余周期都会是最小周期的倍数。
  
  很不巧，对于所有长度相同的串找最小周期即最大 border 并没有线性对数以下的算法，这是我们所不能接受的。这说明我们进行了过多的一般化。考虑观察这个问题中的特殊性质。容易发现，找到的最小周期 $G$ 必须满足 $|G| \leq \text{LCS}(\texttt{xy},\texttt{y}^{k-1})$，对后者进行观察，发现每将指针向后移动一格，这个 $\text{LCS}$ 要么直接归零，要么增加一。那么我们在其增加一时判一下这次增加能否带来新的周期即可，这是可以接受的。
  
  找到最小周期后，我们要求的问题相当于被转化为了给定 $a,b$，求出有多少 $x$ 满足 $a|x,x|m-n,x \leq b$。这个东西在线是不好做了，离线下来处理，按照 $b$ 从小到大扫过去，每扫到一个 $m-n$ 的因数就直接枚举它的因数，把贡献打上去，询问时候调用数组即可。
  
  复杂度 $O(n + d(n)n^{0.5})$，不需要用到任何高级算法。
  ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
string s,t;
#define ull unsigned long long
ull h1[10000005];
ull h2[10000005];
ull pw[10000005];
ull gth1(int l,int r){
	return h1[r]-h1[l-1]*pw[r-l+1];
}
ull gth2(int l,int r){
	return h2[r]-h2[l-1]*pw[r-l+1];
}
vector<int> w[10000005];//a|x x|m-n x<=i
int val[10000005];
void ad(int x){
	for(int i=1;i*i<=x;i++){
		if(x%i!=0)continue;
		val[i]++;
		if(i*i!=x)val[x/i]++;
	}
	return ;
}
signed main(){
	pw[0]=1;
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;cin>>s>>t;
	s=" "+s;t=" "+t;
	for(int i=1;i<=m;i++)pw[i]=pw[i-1]*137;
	for(int i=1;i<=n;i++)h1[i]=h1[i-1]*137+s[i];
	for(int i=1;i<=m;i++)h2[i]=h2[i-1]*137+t[i];
	int lcsnow=0,mnzq=INT_MAX;
	for(int i=0;i<=n;i++){
		if(mnzq!=INT_MAX and gth1(1,i)==gth2(1,i) and gth1(i+1,n)==gth2(m-n+i+1,m)){
			w[lcsnow].push_back(mnzq);
		}
		if(i==n)break;
		if(t[i+1]==t[i+m-n+1]){
			lcsnow=min(lcsnow+1,m-n);
			if((m-n)%lcsnow==0 and gth2(i+1,i+1+m-n-lcsnow)==gth2(i+lcsnow+1,i+m-n+1))mnzq=min(mnzq,lcsnow);
		}else lcsnow=0,mnzq=INT_MAX;
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		if((m-n)%i==0)ad(i);
		for(auto v:w[i])ans+=val[v];
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：fjy666 (赞：4)

题意简述：

给定字符串 $S,T$，计数三元组 $(x,y,z)$ 的个数，使得：
- $S=x+y+z$
- $T=x+y^k+z$

数据范围：$|S|<|T|\le 10^7$，$|\Sigma|$ 不重要。

****

看到 $10^7$ 的数据范围告诉我们不能使用任何高级字符串结构（SAM，SA，*基本border字典*）。

考虑确定 $x+y$ 和 $z$ 在 $S$ 中的分界线，则有：
- $S = (x+y)+(z)$
- $T = (x+y) + y^k + (z)$

我们就可以确定 $y^k$ 是个啥（后文设 $A=y^k$），接下来我们需要找到 $y$。

Weak Periodicity Lemma：假设字符串 $S$ 有循环节 $p,q$，且满足 $p+q\le |S|$，则 $\gcd(p,q)$ 为 $S$ 的循环节。

假设 $A=y_1^{k_1}=y_2^{k_2}$，则因为 $y_1,y_2\le \dfrac{|S|}{2}$（$y_1, y_2 \mid |S|$），所以 $y_1+y_2\le |S|$ 适用于 Weak Periodicity Lemma，则 $\gcd(y_1,y_2)$ 也是 $S$ 的循环节。

换句话说。我们如果找到了最小的 $y$（最小指长度） 满足 $A=y^k$，那么其他 $A=y'^{k'}$ 都会满足 $y'=p\times y$。（$p$ 为任意正整数）

证明：如果 $y'\neq p\times y$，则 $\gcd(y', y)<y$，且 $\gcd(y',y)$ 为 $A$ 的循环节，与 $y$ 的最小性矛盾。

问题转换成求出所有 $[L, L + (m-n))$ 区间的最小循环节。如果该循环节不是 $m-n$ 的因数则无解（证明留待读者自证，和上面的证明有一定相似性）。

由循环节和 Border 可以相互转化，这个问题就最后化简成了：**求出所有 $[L, L+ (m-n))$ 的区间的最长 Border**。

这个问题为 [P4482](/problem/P4482) 的弱化版，但是没有什么特殊解法。目前最优解为 $\mathcal{O}(n\log n) - \mathcal{O}(\log n)$ 的基本 Border 字典。

不过这个问题有它的特殊性。

****

这个周期还需要满足什么条件？

$T=(x+y)+y^k+z$，$y$ 显然需要是 $x+y$ 和 $y^k$ 的共同后缀，即 $|y|\le \operatorname{LCS}(x+y, y^k)$。

看起来这点增加了条件，其实不是。

在 $[L, L + (m-n))$ 到 $[L + 1, L + 1 + (m-n)]$ 的过程中，
- Case 1 $s_L\neq s_{L+1+(m-n)}$，则 $\operatorname{LCS}=0$，$y$ 不存在。
- Case 2 $s_L= s_{L+1+(m-n)}$，此时 $[L, L + (m-n))$ 的所有周期都会转移到 $[L+1, L+1+(m-n)]$ 中，因为 $\operatorname{LCS} + 1$（周期长度的上界增加了 $1$），只需要判断这个新增的潜在周期即可。

判断周期可以使用 hash，那么我们就在 $\mathcal{O}(m)$ 的复杂度内解决了这个问题。

****

求到最小周期之后，所有潜在的 $|y|$ 都是这个周期的倍数，而且有限制 $|y|\le \operatorname{LCS}(x+y, y^k)$。

简化问题后，给定 $a,b$，求满足 $a|c, c|m-n, c\le b$ 的 $c$ 的个数。

把 $m-n$ 的所有因数拿出来，排序之后做双指针就可以了，复杂度 $\mathcal{O}(d^2(m))$。

那么我们在线性复杂度内解决了该问题。不需要 z 函数。

****

赛时我直接使用 $\lfloor\dfrac{\operatorname{LCS}(x+y, y^k)}{|y|}\rfloor$ 过了所有样例，谴责一下样例强度，这种做法会被以下数据卡掉：
```plain
2 5
aa
aaaaa
```

赛后我花 10min 改完了代码并且[通过了](https://codeforces.com/contest/1909/submission/238615070)。

唉。菜是原罪。

---

## 作者：yllcm (赞：2)

先求出 $s$ 和 $t$ 的最长公共后缀的长度 $l$，那么对于 $s[1,n-l]$，它一定只能作为串 $x$ 中的一部分，于是可以把它和 $t$ 中的一段前缀匹配之后删掉。

此时 $s$ 是 $t$ 的一段后缀。考虑 $y$ 在 $s$ 和 $t$ 的出现位置：

* $s=x+y+z$。
* $t=x+y^k+z$。

由于 $s$ 是 $t$ 的后缀，所以串 $x=y'y^i$，其中 $y'$ 是 $y$ 的一段后缀。从另一个方面讲，串 $x+y^k$ 具有周期 $|y|$。

于是可以用 [NOIP2020] 字符串匹配 的技巧，枚举 $|y|$（$(m-n)\bmod |y|=0$），然后考虑 $t$ 的后缀 $t[|y|+1,n]$ 和 $t$ 的 LCP，设为 $l$，那么 $t[1,l+|y|]$ 是一个具有周期 $|y|$ 的串，$x+y^k$ 必然是它的一个前缀。考虑 $|x|$ 的取值范围，需要满足 $|x|+|y^k|\leq l+|y|$，由于 $|y^k|=|y|+m-n$，所以合法的 $|x|$ 的个数可以很快求出来。

可以使用 Z 函数处理 LCP，复杂度 $\mathcal{O}(n)$。

[Submission #238814822 - Codeforces](https://codeforces.com/contest/1909/submission/238814822)


---

## 作者：intel_core (赞：1)

设 $s$ 和 $t$ 的 LCP 是 $s[1,p_1]$，LCS 是 $t[p_2,n]$。

假设 $y$ 在原串中对应的位置是 $[l,r]$。注意到 $x+y$ 是 $s$ 和 $t$ 的公共前缀，那么 $r\le p_1$；类似的，$p_2\le l$。因此有 $p_2\le l\le r\le p_1$。

现在我们知道 $s[p_2,p_1]$ 是 LCP 和 LCS 的重叠部分，因此我们可以在 $t$ 中找到两个对应的子串 $t_A=t[l_A,r_A]$ 和 $t_B=t[l_B,r_B]$（不妨 $l_A<l_B$），不难发现应有 $l_B-l_A=m-n$。

设 $k$ 个 $y$ 在 $t$ 当中的位置是 $c_1=[l_1,r_1],c_2=[l_2,r_2],\cdots,c_k=[l_k,r_k]$。注意到 $(k-1)|y|=m-n$，所以 $l_k-r_k=m-n$，这意味着 $c_1$ 在 $t_A$ 中，$c_k$ 在 $t_B$ 中的出现位置一致。又因为 $t_A=t_B$，所以我们可以知道 $t[r_A+1,r_B]$ 以 $y$ 的一个循环位移作为整周期。

所以直接求出 $t[r_A+1,r_B]$ 的所有整周期即可，相当于求出最小整周期后直接枚举倍数（同时需要时 $m-n$ 的因数），不难发现枚举了 $y$ 的长度 $L$ 后方案数就是 $(p_1-p_2+1)-L+1$。对所有 $L$ 求和即可。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e7+10;
#define int long long
int n,m,len,p1,p2,fail[NR];
char s1[NR],s2[NR],str[NR];

void getFail(){
	int now=0;
	for(int i=2;i<=len;i++){
		while(now&&str[now+1]!=str[i])now=fail[now];
		if(str[now+1]==str[i])now++;
		fail[i]=now;
	}
}

signed main(){
	cin>>n>>m;
	scanf("%s %s",s1+1,s2+1);
	for(int i=1;i<=n;i++)
		if(s1[i]==s2[i])p1=i;
		else break;
	p2=n+1;
	for(int i=n;i>=1;i--)
		if(s1[i]==s2[i+m-n])p2=i;
		else break;
	if(p1<p2){
		puts("0");
		return 0;
	}
	for(int i=p2;i<p2+m-n;i++)str[++len]=s2[i];
	getFail();
	int d=len,now=fail[len];
	while(now){
		if(len%(len-now)==0){
			d=len-now;
			break;
		}
		now=fail[now];
	}
	if((m-n)%d){
		puts("0");
		return 0;
	}
	int ans=0,k=p1-p2+1;
	for(int i=d;i<=m-n&&i<=k;i+=d)
		if((m-n)%i==0)ans+=k-i+1;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：pikiuk (赞：1)

记 $pre$ 表示 $s,t$ 的最长前缀，$suf$ 同理（下图中红色部分）。

记 $len=(pre+suf)-n$，即前后缀中重复长度（下图绿色部分）。

记 $p_1=pre$，$p_2=n-suf+1$，即下图两个绿色部分的边界。

![1704980851285.png](https://img.macesuted.moe/381f0d2aa6e229208593ef4e08fc2d3d/6fac775eb1e77.png)

考虑题目要求找出 $t[l:r]$，满足 $t[l:r]=y^{k-1}$，则 $r-l+1=m-n$。

记 $p$ 为 $t[l:r]$ 的最小整周期，由一些 border 理论不难得知若 $t[l:r]$ 有小于其长度的最小整周期，则一定是最小周期。

显然，类似于周期平移，当满足 $l\in[p_1-len+1,p_1+1]$ 时，任意的 $t[l,r]$ 的最小整周期都是 $p$。且由于 $pre$ 和 $suf$ 是最长前后缀，则 $l$ 一定只能在 $[p_1-len+1,p_1+1]$ 间取值。

枚举 $p$ 的倍数 $q|(m-n)$，则我们论证以下结论，从 $pre$ 绿色部分中选择一个长度为 $q$ 的串作为 $y$，都是合法的：

![1704981697864.png](https://img.macesuted.moe/149678f89e71f2277fb174b56dede6fa/94c8161985878.png)

我们选择下图蓝色框出的作为 $t[l:r]$，黑色框出的作为 $q$，那么由于绿色部分的对称性，$q$ 也是 $t[l:r]$ 的一个周期，因此此时一定是一个合法的 $x+y^k+z$。

那么我们只需要处理出 $t[p_1+1,p_1+m-n]$ 的最小整周期 $p$，枚举 $q$ 满足 $p\vert q\vert (m-n)$，只要 $q$ 是绿色部分的子串，则对应一组合法的 $(x,y,z)$。而若 $q$ 不是绿色部分的子串，则一定不合法。综合时间复杂度 $\mathcal{O}(n)$。

---

## 作者：tzc_wk (赞：1)

这个题思考角度很多，做法也很多。这里介绍一种 @asmend 和我讲的做法。

设 $d=m-n$，那么我们枚举 $|x|=i,|y|=j$，设 $s,t$ 的 LCP 长为 $l_1$，LCS 长为 $l_2$，那么可以得到这组 $(i,j)$ 合法的充要条件是：

- $i\le l_1$
- $m-i-j-d\le l_2$。
- $d\bmod j=0$。
- $t[i,i+d-1]=t[i+j,i+j+d-1]$。

考虑第四条限制，我们将所有长度为 $d$ 的子串的哈希值排序，这样对于每种子串，我们可以知道其出现的位置 $p_1,p_2,\cdots,p_c$。考虑 occurrence 序列的一个性质：对于极长的满足 $p_{l+1}-p_l\le d,p_{l+2}-p_{l+1}\le d,\cdots,p_r-p_{r-1}\le d$ 的连续段 $[l,r]$，必然有 $p_{l+1}-p_l=p_{l+2}-p_{l+1}=\cdots=p_r-p_{r-1}$，这个可以用 WPL 证明。这样考虑对每个这样的连续段统计贡献，设等差数列的公差为 $t$，长度为 $c$，因为是等差数列，因此这个连续段内部可能出现的 $j$ 只有 $t,2t,\cdots,(c-1)t$ 这 $O(c)$ 种，枚举之，那么第一、二条限制的作用是将 $i$ 限制在一个区间内，这样相当于求等差数列中在这个区间内的数的个数，这容易 $O(1)$。因为 $\sum c=O(n)$，所以后面复杂度为线性。复杂度瓶颈在排序，如果使用三个与 $n$ 同阶的质数作为哈希模数并桶排则可以线性。但我直接 `sort` 以 1996ms 卡了过去就没管了（

```cpp
const int MAXN=1e7;
const int MOD1=1e9+21;
const int MOD2=1e9+33;
const int BS1=191;
const int BS2=193;
int qpow(int x,int e,int mod){int ret=1;for(;e;e>>=1,x=1ll*x*x%mod)if(e&1)ret=1ll*ret*x%mod;return ret;}
char s[MAXN+5],t[MAXN+5];int n,m,d,pw1,pw2;
struct _hash{
	int hs1,hs2,pos;
	_hash(){hs1=hs2=pos=0;}
	void append(int x){
		hs1=(1ll*hs1*BS1+x)%MOD1;
		hs2=(1ll*hs2*BS2+x)%MOD2;
	}
	void del(int x){
		hs1=(hs1+1ll*(MOD1-pw1)*x)%MOD1;
		hs2=(hs2+1ll*(MOD2-pw2)*x)%MOD2;
	}
	friend bool operator <(const _hash &X,const _hash &Y){
		if(X.hs1!=Y.hs1)return X.hs1<Y.hs1;
		if(X.hs2!=Y.hs2)return X.hs2<Y.hs2;
		return X.pos<Y.pos;
	}
	friend bool operator ==(const _hash &X,const _hash &Y){
		return (X.hs1==Y.hs1&&X.hs2==Y.hs2);
	}
}a[MAXN+5],cur;
int limL,limR;ll res=0;
int calc(int l,int r,int stp,int rem){
	if(l>r)return 0;
	return (r-rem+stp)/stp-(l-1-rem+stp)/stp;
}
void work(int l,int r){
	for(int i=l;i<r;i++)res+=(a[i+1].pos-a[i].pos==d);
	for(int L=l,R;L<=r;L=R+1){
		if(a[L].pos>limR)break;
		R=L;while(R<r&&a[R+1].pos-a[R].pos<d)++R;
		if(L!=R){
			int d0=a[L+1].pos-a[L].pos;
			for(int j=1;j<=R-L;j++)if(d%(j*d0)==0){
				int _R=limR,_L=limL-j*d0;
				res+=calc(max(_L,a[L].pos),min(_R,a[R-j].pos),d0,a[R].pos%d0);
			}
		}
	}
}
int main(){
	scanf("%d%d%s%s",&n,&m,s+1,t+1);d=m-n;
	pw1=qpow(BS1,d,MOD1);pw2=qpow(BS2,d,MOD2);
	for(int i=1;i<=m;i++){
		cur.append(t[i]);
		if(i>d)cur.del(t[i-d]);
		if(i>=d)a[i-d+1]=cur,a[i-d+1].pos=i-d+1;
	}
	sort(a+1,a+m-d+2);
//	for(int i=1;i<=m-d+1;i++)printf("(%d,%d,%d) %d\n",a[i].hs1,a[i].hs2,a[i].hs3,a[i].pos);
	int len1=0,len2=0;
	while(len1<n&&s[len1+1]==t[len1+1])++len1;
	while(len2<n&&s[n-len2]==t[m-len2])++len2;
	limR=len1+1;limL=m-len2-d+1;
	for(int l=1,r;l<=m-d+1;l=r){
		r=l;while(r<=m-d+1&&a[r]==a[l])++r;
		work(l,r-1);
	}
	printf("%lld\n",res);
	return 0;
}
```



---

## 作者：快斗游鹿 (赞：0)

有点深刻。

首先求一下 $\text{LCP},\text{LCS}$，可以得到 $x+y$ 必然是 $\text{LCP}$ 的一个前缀，$y+z$ 必然是 $\text{LCS}$ 的一个后缀。

你先假定你知道了一个合法的解，假设它长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/jn3l7m5a.png)

然后你小做变化：

![](https://cdn.luogu.com.cn/upload/image_hosting/z0yp34tz.png)

你发现把 $x$ 右移一位，$z$ 也跟着右移一位，一样存在合法方案。进一步地，$x$ 的长度一定会被限定在 $[n-LCS+1,LCP]$ 内，如果比 $n-LCS+1$ 还短，会导致 $y+z$ 长度超过 $\text{LCS}$，而如果比 $\text{LCP}$ 还长显然不合法。结合上面的观察，可以发现当 $x$ 在这个区间内移动时，只要某个时刻有一种划分 $y,z$ 的方案，且 $y$ 长度为 $q$，那么这 $LCP-(n-LCS+1)+1$ 种可能的 $x$ 方案都存在对应的划分出长为 $q$ 的 $y$ 的方案（其实就是 $y$ 做了循环移位）。

考虑你先钦定 $y^{k-1}$ 的范围为 $[\text{LCP}+1,\text{LCP}+m-n]$，然后使用 KMP 求一下最短周期。接下来枚举一下 $y$ 的长度 $q$，则有 $p|q$。可以发现 $y$ 还会有额外的限制，即它必然会被完全包含在 $[n-LCS+1,LCP]$ 内，证明是类似的。那么此时的方案就是在这段区间内选出长为 $q$ 的子串的方案数，容易计算。可以做到线性。

---

## 作者：qczrz6v4nhp6u (赞：0)

不会 border 理论，来点自己的理解。

### Solution

首先 $y+z$ 得是 $s$ 和 $t$ 的公共后缀。记 $L={\rm LCS}(s,t)$（即 $s,t$ 的最长公共后缀），那么 $|x|$ 至少为 $n-L$，考虑将 $x$ 从小到大枚举。

然后注意到 $(k-1)|y|=n-m$，中间 $(k-1)y$ 的长度是不会改变的。所以我们考虑 $(k-1)y$ 做一个类似滑动窗口的东西。

设 $c=(k-1)y$。当 $x\gets x+1$ 时，$c$ 整体向右移了一位，由于 $y$ 是 $c$ 的周期，这个操作相当于将 $y$ 循环位移一下，我们只需要检查 $c$ 的第一位与最后一位即可判断合不合法。

接着我们还需要判断剩下的后缀（即 $t$ 除去 $x$ 与 $c$ 后形成的字符串）是否存在一个前缀 $y$。设 $P$ 为当前的答案集合（即 $P$ 包含所有是 $c$ 的周期的 $y$ 的长度），不难发现 $|y|$ 越大越难满足。所以把 $P$ 降序排序，每次更新 $x$ 时把不合法的丢掉即可，这个可以 hash 或 kmp 做。

时间复杂度是 $O(n)$ 的。注意判断 $x$ 是否合法。[submission](https://codeforces.com/contest/1909/submission/289135392)。

---

## 作者：262620zzj (赞：0)

# 解法

当 $y$ 确定了，那么整个划分方案就确定了，所以枚举 $y$，来计算方案数。

## 计算某一长度的 $y$

首先显然，合法的 $y$，必须同时在 $s,t$ 的公共前缀和公共后缀之中

现在，假设我们已知 $y=s_{l\sim r}$，如何判断 $y'=s_{l+1\sim r+1}$ 是否合法呢？由于 $y\in prefix,s_l=t_l$，那么 $x$ 必然相等。$z$ 变短了仍然相等。而对于 $y$ 来说，只需要 $s,t$ 最后分别新增的那一位相等即可。又因为 $t$ 中间是 $y^k$，所以只需要满足 $s_{r+1}=t_{r+1}$，我们发现这竟然就等价于 $y'$ 在公共前缀之中。同理 $y'$ 也需要在公共后缀之中，于是对于所有 $|y|=len,y\in prefix,y\in suffix$，他们要么都合法，要么都不合法。

## 所有长度的 $y$ 

由于 $y\mid m-n$，所以 $len_y$ 只有 $O(\sqrt{m-n})$ 种，于是直接枚举长度，然后对于每个长度，随便取一个 $y$，判断 $t$ 去除 $x,z$ 后是不是等于 $y^k$。采用哈希比较即可。如果一个字符串是若干倍的另一字符串，那么他们哈希值之间的倍数关系应该是等比数列前几项的和。算等比数列求和需要逆元 $O(\log MOD)$

至此问题就解决了，复杂度 $O(m+\sqrt m \log MOD)$

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e7+5;
typedef long long ll;
constexpr ll base=20081023;
int n,m,pre,suf;
string s,t;
ll qpow(ll a,int b,int p){
	ll res=1;
	while(b){
		if(b&1)res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}
struct Hashhh{
	ll pow[N],H1[N],H2[N],MOD;
	unordered_map<ll,ll> inver;
	inline ll inv(ll x){return inver[x]?inver[x]:inver[x]=qpow(x,MOD-2,MOD);}
	inline void figure(int mmm){
		MOD=mmm;
		pow[0]=1;
		for(int i=1;i<=m;i++)pow[i]=pow[i-1]*base%MOD;
		for(int i=1;i<=n;i++)H1[i]=(H1[i-1]*base+s[i])%MOD;
		for(int i=1;i<=m;i++)H2[i]=(H2[i-1]*base+t[i])%MOD;
	}
	inline bool judge(int ls,int rs,int lt,int rt){
		int lens=rs-ls+1,lent=rt-lt+1;
		if(lent%lens)return 0;
		ll pat=((H1[rs]-H1[ls-1]*pow[lens])%MOD+MOD)%MOD;
		ll text=((H2[rt]-H2[lt-1]*pow[lent])%MOD+MOD)%MOD;
		return pat*(pow[lent]-1)%MOD*inv(pow[lens]-1)%MOD==text;
	}
}hash1,hash2;
bool equal(int ls,int rs,int lt,int rt){return hash1.judge(ls,rs,lt,rt)&&hash2.judge(ls,rs,lt,rt);}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>s>>t;
	s="$"+s;t="$"+t;
	pre=0;
	while(pre<n&&s[pre+1]==t[pre+1])pre++;
	suf=n+1;
	while(suf>1&&s[suf-1]==t[m-n+suf-1])suf--;
	// cerr<<pre<<' '<<suf<<endl;
	hash1.figure(998244353);
	hash2.figure(1000000007);
	ll ans=0;int len=pre-suf+1;
	for(int i=1;i*i<=m-n;i++){
		if((m-n)%i)continue;
		if(i<=len&&equal(pre-i+1,pre,pre-i+1,m-n+pre))ans+=len-i+1;//cerr<<ans<<' ';
		int ii=(m-n)/i;
		if(i!=ii&&ii<=len&&equal(pre-ii+1,pre,pre-ii+1,m-n+pre))ans+=len-ii+1;//cerr<<ans<<endl;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：eastcloud (赞：0)

[更好的阅读体验](https://www.cnblogs.com/eastcloud/p/18113021)

题目要求我们对合法三元组进行计数，直接做是困难的，因此考虑通过枚举确定一部分元素再进行判定求解，那我们固定什么呢？固定 $x$ 和 $y+z$ 的分界线没啥用，因此我们枚举确定 $S$ 中 $x+y$ 和 $z$ 的分界线，这样能确定一长串 $y^{k-1}$ 所在的区间。

接着我们不难想到一个 $O(n^2)$ 的做法，每次找到这次被钦定为 $y^{k-1}$ 所在的区间的最小周期，枚举这个区间的每个周期作为 $y$，然后判一下这个方案行不行，具体来说，我们有两个要求：

- $y^{k-1}$ 串前后必须包括在两个字符串的 $\text{lcp}$ 和 $\text{lcs}$ 内。

- $\text{lcp}(S,T)>|z+y|$（也即 $x+y$ 部分必须要包括一个 $y$，不难发现这两个条件是等价的）。

利用手段优化这个做法不太容易，因为 $z$ 和 $x+y$ 改变的时候整个周期会跟着一起变，而我们又没有快速求区间 Border 的算法，但周期的变化真的那么彻底吗？如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0nnjd4um.png)

你发现当我们将分割 $x+y$ 和 $z$ 的分界线右移时，如果这两个字符串的 $\text{lcp} > |x+y|$，也即上面 $z$ 串第一个字符和 $y^{k-1}$ 串第一个字符相同（其实这必然满足，不然你的移动是不合法的），然后又有红色部分相同，因此右移边界不过是把 $y^{k-1}$ 作了循环移位，而循环移位不会改变周期。

因此，就有所有满足上面条件一的 $y^{k-1}$ 区间周期都相同，而这些区间的左端点取值范围是 $[m-\text{lcs}-(m-n)+1,\text{lcp}+1]$，这个由条件一可以很方便地得到。

最后，我们还剩一个条件二没有处理，但是你发现假设我们枚举了一个周期，只要把区间左端点取值范围改成 $[m-\text{lcs}-(m-n)+1+|y|,\text{lcp}+1]$ 就可以了，这个条件的充分性显然，而必要性只要考虑如果扩展 $\text{lcp}$ 就会不满足条件。

总结一下我们要怎么求：直接求出任意一个合法 $y^{k-1}$ 的最小周期，然后枚举所有周期加上对应合法左端点取值区间的长度即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 10000007
using namespace std;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')f=(ch=='-'?-1:f),ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x/10)write(x/10);
    putchar(x%10+'0');
}
char s[N],t[N];
ll nex[N];
ll get_nex(ll l,ll r){
    for(ll i=l+1,j=0;i<=r;i++){
        while(j && t[j+l]!=t[i])j=nex[j];
        if(t[j+l]==t[i])j++;
        nex[i-l+1]=j;
    }
    return nex[r-l+1];
}
int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    ll n=read(),m=read();
    scanf("%s",s+1);scanf("%s",t+1);
    ll lcp=0,lcs=0;
    while(lcp!=n && s[lcp+1]==t[lcp+1])lcp++;
    while(lcs!=n && s[n-lcs]==t[m-lcs])lcs++;
    ll border=get_nex(lcp+1,lcp+m-n),len=m-n,per=len-border;
    if(len%per!=0)per=len;
    ll l=m-lcs-len+1,r=lcp+1,ans=0;
    for(ll i=per;i<=min(len,r-l+1);i+=per){
        if(len%i==0)ans+=(r-l+1)-i;
    }
    write(ans);
}
```

---

## 作者：王熙文 (赞：0)

纪念一下自己独立切掉的 3000，而且做法与众不同。

## 思路

设 $y$ 的长度为 $len$，发现 $m-n=(k-1)len$，所以 $len$ 是 $m-n$ 的因数，可以枚举。

考虑一种暴力的做法：求出来 $s$ 和 $t$ 从左、右的相同个数 $le,ri$，枚举 $len$ 和 $y$ 的起点 $st$（$st$ 需要满足 $1 \le st,st+len-1 \le le,r \le st+k\cdot len \le m+1$），然后使用哈希判断 $t$ 的 $[st,st+(m-n)-1]$ 与 $[st+len,st+k \cdot len-1]$ 是否相同，如果相同说明 $[st,st+k \cdot len-1]$ 是 $y$ 重复 $k$ 次，满足条件。

上面的做法提示我们对每个位置处理一个布尔值 $b_i=[t_i=t_{i+len}]$，那么只需要求 $[st,st+(m-n)-1]$ 之间有多少个长度为 $m-n$ 的子串满足 $b$ 全都是 $1$。

考虑使用某种复杂度中出现 $\dfrac{1}{m-n}$ 的算法，因为花了 $d(m-n)$ 的时间枚举因数。考虑拎出来所有与 $st$ 的距离是 $m-n$ 的倍数的位置，那么一个满足条件的子串至少包含这些位置中的一个。因此枚举这些位置，并向前、后二分，找到极长的全 $1$ 连续段，那么不在这些连续段中的位置都可以视为 $0$。将这些连续段合并，就找到了所有长度大于等于 $m-n$ 的连续段，将长度减去 $m-n-1$ 再求和即为答案。

复杂度为 $\mathcal O(\dfrac{d(m-n)\cdot n \cdot \log m}{m-n})$。如果想要更好的复杂度可以对 $m-n$ 数据分治，$m-n$ 较小时暴力计算。不过直接这么做已经可以通过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
long long base[10000010];
int n,m;
string s,t;
long long hsh[10000010];
long long get_hsh(int l,int r)
{
	return (hsh[r]-hsh[l-1]*base[r-l+1]%mod+mod)%mod;
}
bool check(int l,int r,int len)
{
	return get_hsh(l,r)==get_hsh(l+len,r+len);
}
pair<int,int> range[10000010];
int get_ans(int l,int r,int len) // 求 [l,r] 中长度为 m-n，全为 1 的子串个数 
{
	int cnt=r-l+1,tot=cnt/(m-n);
	for(int i=1; i<=tot; ++i)
	{
		if(t[l+i*(m-n)-1]!=t[l+i*(m-n)+len-1]) { range[i]={0,0}; continue; }
		int el=(i-1)*(m-n)+1,er=i*(m-n),wz1;
		while(el<=er)
		{
			int mid=el+er>>1;
			if(check(l+mid-1,l+i*(m-n)-1,len)) wz1=mid,er=mid-1;
			else el=mid+1;
		}
		el=i*(m-n),er=min((i+1)*(m-n)-1,cnt); int wz2;
		while(el<=er)
		{
			int mid=el+er>>1;
			if(check(l+i*(m-n)-1,l+mid-1,len)) wz2=mid,el=mid+1;
			else er=mid-1;
		}
		range[i]={wz1,wz2};
	}
	int ans=0;
	for(int i=1; i<=tot; ++i)
	{
		if(range[i].first==0) continue;
		int now=i+1;
		while(now<=tot && range[now].first!=0 && range[now].first<=range[now-1].second+1) ++now; --now;
		ans+=max(range[now].second-range[i].first+1-(m-n)+1,0);
		i=now;
	}
	return ans;
}
int main()
{
	base[0]=1; for(int i=1; i<=1e7; ++i) base[i]=base[i-1]*131%mod;
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>n>>m>>s>>t; s=' '+s,t=' '+t;
	for(int i=1; i<=m; ++i) hsh[i]=(hsh[i-1]*131+t[i])%mod;
	int le=1;
	while(le<=n && s[le]==t[le]) ++le; --le;
	int ri=n;
	while(ri>=1 && s[ri]==t[m-n+ri]) --ri; ++ri;
	long long ans=0;
	for(int len=1; len<=m-n; ++len)
	{
		if((m-n)%len!=0) continue;
		int k=(m-n)/len+1;
		int l=max(1,ri-len*k),r=min(le-len+1,m-len*k+1);
		ans+=get_ans(l,r+(m-n)-1,len);
	}
	cout<<ans;
	return 0;
}
```

---

