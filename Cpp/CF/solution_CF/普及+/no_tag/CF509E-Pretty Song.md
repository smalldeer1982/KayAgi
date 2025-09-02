# Pretty Song

## 题目描述

给你一个字符串，计算一下它的优美程度。
   	优美程度是指它的所有每一段连续子串优美程度的和。
    优美程度的计算方法：这一段连续子串中I，E，A，O，U，Y的总数/字符串长度。

## 说明/提示

在第一个样例中，所有的字母都是I，E，A，O，U，Y其中的一个。每个子串的优美程度为1。长度为7的字符串有28个连续子串。所以这个字符串的优美程度为28.

## 样例 #1

### 输入

```
IEAIAIO
```

### 输出

```
28.0000000
```

## 样例 #2

### 输入

```
BYOB
```

### 输出

```
5.8333333
```

## 样例 #3

### 输入

```
YISVOWEL
```

### 输出

```
17.0500000
```

# 题解

## 作者：littlez_meow (赞：2)

一种很逆天但是非常好想的做法。

[题目指路](https://www.luogu.com.cn/problem/CF509E)。

## 思路

首先发现我们不关心字母究竟是什么，我们只关心它们是不是元音。因此，把元音字母变成 $1$，其余变成 $0$，得到一个零一串 $s$。

考虑字符串经典 trick：把所有子串变成前缀的所有后缀。

对于前 $1-i$ 个字符构成的前缀，记其优美程度为 $w_i$。尝试寻找递推方法。

我们发现 $w_i$ 可以拆成 $\sum\limits_{j=1}^i\dfrac{\sum\limits_{t=j}^i s_t}{i-j+1}$。观察这个式子，当新增一个字符时，我们发现对于每项可以减去左端点的值，加上新增字符对应的值，最后再加上 $\dfrac{\sum\limits_{j=1}^i s_i}{i}$。因此有递推式：

$$w_i=w_{i-1}-\sum\limits_{j=1}^{i-1}\dfrac{s_{i-j}}{j}+s_i\sum\limits_{j=1}^{i-1}\dfrac 1 {j}+\dfrac 1 i\sum\limits_{j=1}^{i}s_i$$

最后一项预处理前缀和，倒数第二项预处理调和级数，但第二项怎么办？

把它拆开可能能看得更清楚。设其值为 $r_i$，则有：

$$r_i=\sum\limits_{j+k=i,j\neq0,k\neq 0}s_j\cdot\dfrac1{k}$$

这不卷积？

为了消除 $0$ 次项的影响，把两个多项式常数项设成 $0$ 即可。

时间复杂度卷积 $O(n\log n)$，递推 $O(n)$，总的时间复杂度为 $O(n\log n)$。虽然比正解劣，但是相当好想。

注意，FFT 的精度比较差，但 long double 会 TLE。用 double 的话，在答案较大时相对误差可以接受，但答案较小时（例如 $0$）的误差完全不能接受，记得特判。

## 附上代码
```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define ll long long
const int LEN=1<<20;
const long double pi=acos(-1.0);
using namespace std;
inline bool turn(char ch){
	switch(ch){
		case 'A':case 'E':case 'I':case 'O':case 'U':case 'Y':return 1;
		default:return 0;
	}
	return 0;
}
char str[500001];
int n;
bool s[500001];
int sum[500001];
double tiaohejishu[500001],dp[500001];
complex<double>poly[LEN+1];
int rev[LEN+1];
inline void FFT(int len,short inv){
	F(i,0,len-1) if(i<rev[i]) swap(poly[i],poly[rev[i]]);
	for(int i(1);i<len;i<<=1){
		complex<double>omega(cos(pi/i),inv*sin(pi/i));
		for(int j(0);j<len;j+=(i<<1)){
			complex<double>w(1,0);
			for(int k(0);k<i;++k,w*=omega){
				complex<double>a=poly[j+k],b=w*poly[i+j+k];
				poly[j+k]=a+b;
				poly[i+j+k]=a-b;
			}
		}
	}
	if(inv==-1) F(i,0,len-1) poly[i].imag(poly[i].imag()/2/len);
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>str;
	n=strlen(str);
	F(i,0,n-1) s[i+1]=turn(str[i]),tiaohejishu[i+1]=tiaohejishu[i]+1.0/(i+1);
	F(i,1,n) poly[i].real(s[i]),poly[i].imag(1.0/i),sum[i]=sum[i-1]+s[i];
	if(sum[n]==0) return cout<<"0",0; 
	int len(n<<1);
	len=1<<max(1,(int)ceil(log2(len)));
	F(i,0,len-1) F(j,0,log2(len-1)){
		rev[i]<<=1;
		rev[i]|=((i>>j)&1);
	}
	FFT(len,1);
	F(i,0,len-1) poly[i]*=poly[i];
	FFT(len,-1);
	dp[1]=s[1];
	F(i,2,n){
		dp[i]=dp[i-1]-poly[i].imag();
		s[i]&&(dp[i]+=tiaohejishu[i-1]);
		dp[i]+=1.0*sum[i]/i;
	}
	F(i,2,n) dp[i]+=dp[i-1];
	cout<<fixed<<setprecision(8)<<dp[n];
	return 0;
}
```

完结撒花 qwq~

---

## 作者：tyccyt (赞：1)

首先考虑DP。

其次定义 $suf_i$ 表示 $[i,n]$ 这个区间有多少个 $I,E,A,O,U,Y$（至于为什么用后缀之后再说），那么答案也就是 $\sum_{i=1}^n\sum_{j=i}^n \frac{suf_i-suf_{j+1}}{j-i+1}$ 

考虑拆贡献（转化答案）：
$$
\sum_{len=1}^n\frac{\sum_{i=1}^{i\le n-len+1} suf_i-suf_{i+len}}{len}
$$
 其中 $len$ 是在枚举长度。

接下来考虑优化，设长度为 $i$ 的答案为 $f_i$ ，我们很想利用 $f_{i-1}$ 的值快速求出答案。我发现：所有长度为 $i$ 的子串比所有长度为 $i-1$ 的子串按顺序进了一位！多进的位组成的是字符串的后缀。但是这里需要注意长度为 $i$ 的子串比长度为 $i-1$ 的子串要少一个，所以在从 $f_{i-1}$ 转移到 $f_i$ 时要记得减去长度既是 $i-1$ 的，同时是后缀的那一串的贡献，因为它无法扩展。举个例子：比如说 $i=3$（字符串长度为 $n$），那么长度为 $i-1 $ 的就是 $[1,2],[2,3],\dots,[n-1,n]$ ，考虑扩展到 $[1,3],[2,4],\dots,[n-2,n]$ ，发现增加了 $[3,n]$ 这个答案，同时减少了 $[n-1,n]$（已经到顶，无法扩展）

所以转移就是 $f_i=f_{i-1}+suf_i-suf_{n-i+2}$ ，答案就是 $\sum_{i=1}^n \frac{f_i}{i}$ 。

---

## 作者：RealKzos (赞：1)

$\quad$听说这个题目有什么二次差分，二次前缀和一些做法，但是个人在考场写的做法好像和大家都不太一样，所以就来水题解。

$\quad$首先这类题的套路就是将贡献拆分，对于每一个特殊字符求它对于最终答案的贡献，那么最后答案就是所有特殊字符的总贡献。

$\quad$于是一个显然的想法就是 $\lfloor$ 扫描线+增量 $\rceil$。那么考虑这个增量是什么。假设当前位置为 $A$，（默认字符串的下标从 $1$ 开始），当前位置是特殊的，且当前已经算完这个位置的贡献了，考虑当前贡献的式子：

$$
\sum_{x=1}^A \sum_{y=0}^{n-A} \frac{1}{x+y}
$$

（意思是左边选择一个长度，右边选择一个长度）

$\quad$考虑 $A+1$ 位置的贡献：

$$
\begin{aligned}
&=\sum_{x=1}^{A+1} \sum_{y=0}^{n-A-1} \frac{1}{x+y}\\
&=\sum_{x=1}^A \sum_{y=0}^{n-A} \frac{1}{x+y}-\sum_{x=1}^A\frac{1}{x+n-A}+\sum_{y=0}^{n-A-1}\frac{1}{A+1+y}\\
&=lastans -\sum_{x=1}^A\frac{1}{x+n-A}+\sum_{y=0}^{n-A-1}\frac{1}{A+1+y}\\
&=lastans -\sum_{x=1}^A\frac{1}{x+n-A}+\sum_{y=1}^{n-A}\frac{1}{A+y}\\
&=lastans -\sum_{x=1}^A\frac{1}{x+n-A}+\sum_{y=1}^{B}\frac{1}{y+n-B} (B=n-A)
\end{aligned}
$$

$\quad$后面的两个式子似乎是一样的，考虑这类式子：

$$
\sum_{x=1}^A \frac{1}{x+n-A}
$$

$\quad$第一眼有点懵，枚举尝试一下！

$$
\begin{aligned}
&A=1 \to \frac{1}{n}\\ 
&A=2 \to \frac{1}{n} +\frac{1}{n-1}
\end{aligned}
$$

$\quad$之后的就不一一列了，规律就是这么显然，那么这个题就结束了。

$\quad$总结一下步骤：

1. 预处理出上述式子的值

2. 扫一遍的时候记录当前的值，如果是特殊字符，那么就将当前答案加入总贡献


最后附上代码：


```cpp
const int N=5e5+10;
char s[N];
int n;
long double A[N],ans,las;

inline int check(char ch){
	if(ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U' || ch=='Y') return 1;
	return 0;
}

int main(){
	scanf("%s",s+1);
	ans=0.0;
	n=strlen(s+1);
	ROF(i,n,1) A[n-i+1]=A[n-i]+(long double)1.0/(long double)i;
	las=A[n];
	if(check(s[1])) ans+=las;
	FOR(i,2,n){
		int a=i-1,b=n-a;
		las=las-A[a]+A[b];
		if(check(s[i])) ans+=las;
	}
	printf("%.15Lf\n",ans);
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
给你一个字符串，计算一下它的优美程度。

优美程度是指它的所有每一段连续子串优美程度的和。

优美程度的计算方法：这一段连续子串中 I，E，A，O，U，Y 的总数除以字符串长度。
### 分析
先扫一遍找出所有元音字母位置存下来。

然后我们要求的是一堆分数之和，分母相同的好算贡献，所以枚举长度 $k$，现在算每个元音字母的贡献，即对与每个元音字母，包含其的长度为 $k$ 的区间个数。考虑一下左端点的选择方案，可以得到结果：
$$\min(i,n-k+1)-\max(i-k+1,1)+1$$
然后我们拆一下贡献，大力分讨：

$\sum{\min(i,n-k+1)}$ 可以二分出第一个 $i>n-k+1$ 的位置，然后维护元音字母下标的前缀和就可以简单统计了。

$\sum{\max(i-k+1,1)}$ 也差不多，二分出最后一个 $i<k$ 的位置，有前缀和简单拆一下贡献就能算了。

时间复杂度 $\mathcal O(n\log_2n)$，具体实现见代码。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=5e5+5;
int n;
string t;
double ans;
int a[maxn],cnt;
int s[maxn];
signed main(){
	cin.tie(0),cout.tie(0);
	cin>>t;
	n=t.size();
	t=' '+t;
	for(int i=1;i<=n;i++) if(t[i]=='A'||t[i]=='E'||t[i]=='I'||t[i]=='O'||t[i]=='U'||t[i]=='Y') a[++cnt]=i,s[cnt]=s[cnt-1]+a[cnt];
	for(int k=1;k<=n;k++){
		int l=1,r=cnt,pos=cnt+1;
		double res=cnt;
		while(l<=r){
			int m=(l+r)/2;
			if(a[m]>n-k+1){
				pos=m;
				r=m-1;
			}else{
				l=m+1;
			}
		}
		res+=(s[pos-1]+(n-k+1)*(cnt-pos+1));
		l=1,r=cnt,pos=0;
		while(l<=r){
			int m=(l+r)/2;
			if(a[m]<k){
				pos=m;
				l=m+1;
			}else{
				r=m-1;
			}
		}
		res-=pos;
		res-=(s[cnt]-s[pos]-k*(cnt-pos)+(cnt-pos));
		ans+=res/(1.0*k);
	}
	printf("%.10lf\n",ans);
	return 0;
}
```

---

## 作者：violetctl39 (赞：0)

# CF509E Pretty Song 题解

by ctldragon

看到这题要求每个子串对答案的贡献，于是~~想到了 SAM~~。写了一个 SAM 后才发现复杂度有大问题（

子串不好处理，我们可以想想字母 ``I,E,A,O,U,Y`` 对每个子串的贡献。

![](https://s1.ax1x.com/2022/03/13/bbJy0e.png)

如图，我们假设现在在第 $i$ 个字母，它是一个特殊字母（例如 ``I``）。包含它的子串就是在 $[1,i]$ 和 $[i,n]$ 各选取一个端点组成的子串。

我们先考虑模拟这个过程。

枚举每个左端点，看左右端点组成的子串的长度范围。

$[1,r],[2,r-1],[3,r-2]...,[l-1,l+r-2],[l,l+r-1]$

我们可以发现可以通过统计对答案有贡献的子串长度个数，最后答案就是 $\sum_{i=1}^{n}c[i]/i$。

但是这个复杂度是 $O(n^2)$ 的，依然无法通过此题。

考虑观察差分过程。

![](https://s1.ax1x.com/2022/03/13/bbJ6TH.png)

可以发现，+1 是连续的一段，-1 也是连续的一段，于是我们可以再来一次差分。

最后这个字母对二次差分数组的影响就是：

``c[1]++;c[l+1]--;c[r+1]--;c[l+r]++;``

统计完每个字母对答案的贡献最后还原原来的统计数组就行了。

代码：

```cpp
#include<bits/stdc++.h>
#define pc(x) putchar(x)
#define int long long
#define dl double
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){f=ch=='-'?-1:f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
void write(int x)
{
	if(x<0){x=-x;putchar('-');}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
int n,c[500005];dl ans;
char s[500005];
int check(int x)
{
	if(x=='I'||x=='E'||x=='A'||x=='O'||x=='U'||x=='Y')return 1;
	return 0;
}
signed main()
{
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;++i)
	{
		if(!check(s[i]))continue;
		int l=i,r=n-i+1;
		c[1]++;c[l+1]--;
		c[r+1]--;c[l+r]++;
	}
	for(int i=1;i<=n;++i)c[i]+=c[i-1];
	for(int i=1;i<=n;++i)c[i]+=c[i-1];
	for(int i=1;i<=n;++i)ans+=(dl)c[i]/i;
	printf("%.8lf",ans);
	return 0;
}
```



---

## 作者：开始新的记忆 (赞：0)

题目大意：大意：给定一个字符串s，计算其中各子串元音字母所占比例，输出比例之和。（题意来源于网络）

思路：找规律+前缀和
规律（就是最后一个for）：
对于长度为1的子串，每个元音字母都要用1次，即(ans[t]-ans[0])/1,对于长度为2的子串，a[2]到第a[t-1]的元音字母都要用2次，而第a[1]和a[t]个位置的元音字母只需用1次，即((ans[t]-ans[0])+(ans[t-1]-ans[1]))/2,
对于长度为3的子串，a[3]到第a[t-2]的元音字母都要用3次，a[2]到第a[t-1]的元音字母都要用2次，而第a[t]和a[t]个位置的元音字母只需用1次，即((ans[t]-ans[0])+(ans[t-1]-ans[1])+(ans[t-2]-ans[2]))/3，以此类推，累加即可。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<map>
using namespace std;
int main()
{   double ans1=0,ans3=0;
    int qz[500010];
    string a;
    memset(qz,0,sizeof(qz));
    cin>>a;
    int t=a.size();
    for(int i=0;i<t;i++)
    {
    	qz[i+1]=qz[i];
    	if(a[i]=='A' || a[i]=='E' || a[i]=='O' || a[i]=='I' || a[i]=='U' || a[i]=='Y')
    	    qz[i+1]++;
	}
	for(int i=0;i<t;i++)
	{
		ans1+=qz[t-i]-qz[i];
	    ans3+=(ans1/(i+1));
	}
	printf("%.6f",ans3);
	return 0;
}
```



---

