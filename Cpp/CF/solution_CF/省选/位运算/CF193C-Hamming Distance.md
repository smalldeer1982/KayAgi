# Hamming Distance

## 题目描述

定义函数 $h(s,t)$ 为：
- 两个长度相等的字符串 $s,t$ 中满足 $s_i \neq t_i$ 的 $i$ 的个数。

现在给出六个数 $a,b,c,d,e,f$，要你构造出**四个长度相等的仅由字符 $\texttt{ab}$ 构成的字符串** $s_1,s_2,s_3,s_4$，满足：
- $h(s_1,s_2)=a$，$h(s_1,s_3)=b$，$h(s_1,s_4)=c$，$h(s_2,s_3)=d$，$h(s_2,s_4)=e$，$h(s_3,s_4)=f$。
- 它们长度尽可能小。

构造出一个合法的方案，无解输出 $-1$。

数据范围 $0 \leq a,b,c,d,e,f \leq 10^5$，$\max\{a,b,c,d,e,f\}>0$。

## 样例 #1

### 输入

```
4 4 4
4 4
4
```

### 输出

```
6
aaaabb
aabbaa
bbaaaa
bbbbbb
```

# 题解

## 作者：tzc_wk (赞：6)

> Codeforces 193C

> 题意：定义两个长度相同的字符串的海明距离 $h(s,t)$ 为 $s_i \neq t_i$ 的 $i$ 的个数。

> 给出六个数 $a,b,c,d,e,f$，你需要构造 $4$ 个长度相等的只由 ab 构成的字符串 $s_1,s_2,s_3,s_4$，满足：

> - $h(s_1,s_2)=a$
> - $h(s_1,s_3)=b$
> - $h(s_1,s_4)=c$
> - $h(s_2,s_3)=d$
> - $h(s_2,s_4)=e$
> - $h(s_3,s_4)=f$

> 要你求出字符串的最小长度并构造。

> $1 \leq a,b,c,d,e,f \leq 10^5$

题解：被这道难度 $2400$ 的题降智了没想出来qaq

由于对称性，我们可以将其中一个字符串全设为 a 然后填其它三个字符串上的字符。

不难发现同一位填的字符的情况只有 $8$ 种可能。还可以发现 $\texttt{aaaa}$ 是没有用的，所以只有 $7$ 种情况。于是那么我们考虑每一位对答案的增长：

- $\texttt{aaab}$ 可以使 $c,e,f$ 加 $1$
- $\texttt{aaba}$ 可以使 $b,d,f$ 加 $1$
- $\texttt{aabb}$ 可以使 $b,c,d,e$ 加 $1$
- $\texttt{abaa}$ 可以使 $a,d,e$ 加 $1$
- $\texttt{abab}$ 可以使 $a,c,d,f$ 加 $1$
- $\texttt{abba}$ 可以使 $a,b,e,f$ 加 $1$
- $\texttt{abbb}$ 可以使 $a,b,c$ 加 $1$

我们假设这七种情况的个数分别为 $x_1,x_2,\dots,x_7$，那么有：

- $x_4+x_5+x_6+x_7=a$
- $x_2+x_3+x_6+x_7=b$
- $x_1+x_3+x_5+x_7=c$
- $x_2+x_3+x_4+x_5=d$
- $x_1+x_3+x_4+x_6=e$
- $x_1+x_2+x_5+x_6=f$

七个未知数六个方程，我们可以枚举自由元然后消元求解了

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int a,b,c,d,e,f;
/*
aaaa -> 0 0 0 0 0 0
aaab -> 0 0 1 0 1 1
aaba -> 0 1 0 1 0 1
aabb -> 0 1 1 1 1 0
abaa -> 1 0 0 1 1 0
abab -> 1 0 1 1 0 1
abba -> 1 1 0 0 1 1
abbb -> 1 1 1 0 0 0

x4+x5+x6+x7=a      1
x2+x3+x6+x7=b      2
x1+x3+x5+x7=c      3
x2+x3+x4+x5=d      4
x1+x3+x4+x6=e      5
x1+x2+x5+x6=f      6

x2+x6-x3-x7=f-c		6-3
x2+x3-x6-x7=d-a		4-1
2(x2-x7)=f-c+d-a
2(x6-x3)=f-c-(d-a)
x2+x3-x4-x5=b-a		2-1
x2-x3-x4+x5=f-e		6-5
2(x2-x4)=b-a+f-e
2(x3-x5)=b-a-(f-e)
x2+x4-x1-x7=d-c		4-3
x1+x4-x2-x7=e-b		5-2
2(x4-x7)=d-c+e-b
2(x2-x1)=d-c-(e-b)
x1+x3-x4-x6=c-a
x1+x3+x4+x6=e
2(x1+x3)=c-a+e
*/
char s[1000005][4];
signed main(){
	cin>>a>>b>>c>>d>>e>>f;
	if((f-c+d-a)%2!=0)	return puts("-1"),0;
	if((b-a+f-e)%2!=0)	return puts("-1"),0;
	if((d-c+e-b)%2!=0)	return puts("-1"),0;
	if((c-a+e)%2!=0)	return puts("-1"),0;
	fz(x2,0,100000){
		int x7=x2-(f-c+d-a)/2;
		int x4=x2-(b-a+f-e)/2;
		int x1=x2-(d-c-e+b)/2;
		int x3=(c-a+e)/2-x1;
		int x6=(f-c-(d-a))/2+x3;
		int x5=x3-(b-a-(f-e))/2;
//		cout<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<x5<<" "<<x6<<" "<<x7<<endl;
		if(x1<0||x2<0||x3<0||x4<0||x5<0||x6<0||x7<0)	continue;
		int j=0;
		cout<<x1+x2+x3+x4+x5+x6+x7<<endl;
		fz(i,1,x1)	s[++j][0]='a',s[j][1]='a',s[j][2]='a',s[j][3]='b';
		fz(i,1,x2)	s[++j][0]='a',s[j][1]='a',s[j][2]='b',s[j][3]='a';
		fz(i,1,x3)	s[++j][0]='a',s[j][1]='a',s[j][2]='b',s[j][3]='b';
		fz(i,1,x4)	s[++j][0]='a',s[j][1]='b',s[j][2]='a',s[j][3]='a';
		fz(i,1,x5)	s[++j][0]='a',s[j][1]='b',s[j][2]='a',s[j][3]='b';
		fz(i,1,x6)	s[++j][0]='a',s[j][1]='b',s[j][2]='b',s[j][3]='a';
		fz(i,1,x7)	s[++j][0]='a',s[j][1]='b',s[j][2]='b',s[j][3]='b';
		fz(i,1,x1+x2+x3+x4+x5+x6+x7)	cout<<s[i][0];puts("");
		fz(i,1,x1+x2+x3+x4+x5+x6+x7)	cout<<s[i][1];puts("");
		fz(i,1,x1+x2+x3+x4+x5+x6+x7)	cout<<s[i][2];puts("");
		fz(i,1,x1+x2+x3+x4+x5+x6+x7)	cout<<s[i][3];puts("");
		return 0;
	}
	puts("-1");
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：2)

首先，最终答案的每一位都是互相独立的。我们可以考虑每位究竟应该填入什么字符组合。

一共有$2^4=16$种不同的字符组合。删去```aaaa```和```bbbb```两种删去对答案也没有影响的，剩下$14$组。因为在一组组合中，将所有的```a```与```b```互换也没有影响，所以一共有 $\dfrac{14}{2}=7$ 组。

下面我们就贴一张表格表示每个字符组合对每个$h$的影响：

|  | ```aaab``` | ```aaba``` | ```abaa``` | ```baaa``` | ```aabb``` | ```abab``` | ```abba``` |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $(1,2)$ | 0 | 0 | 1 | 1 | 0 | 1 | 1 |
| $(1,3)$ | 0 | 1 | 0 | 1 | 1 | 0 | 1 |
| $(1,4)$ | 1 | 0 | 0 | 1 | 1 | 1 | 0 |
| $(1,5)$ | 0 | 1 | 1 | 0 | 1 | 1 | 0 |
| $(1,6)$ | 1 | 0 | 1 | 0 | 1 | 0 | 1 |
| $(1,7)$ | 1 | 1 | 0 | 0 | 0 | 1 | 1 |

我们如果把$h(x,y)$贴到矩阵的最右边，发现就是一个高斯消元的矩阵。

因为有$6$行等式，却有$7$个变量，因此有一个自由元。

因为我们的目标是最小化所有变量的和，所以我们可以枚举那个自由元的取值（$[1,10^5]$），然后高斯消元剩下的部分，并找到变量和最小的那一组解。

复杂度$O(10^5*6^3)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int eps=1e-9;
const int n=6;
int mx;
int gg[10][10]=
{
{},
{0,0,1,1,0,1,1},
{0,1,0,1,1,0,1},
{1,0,0,1,1,1,0},
{0,1,1,0,1,1,0},
{1,0,1,0,1,0,1},
{1,1,0,0,0,1,1}
};
int res=0x3f3f3f3f,ans[10],now[10],sum;
double g[10][10];
void work(int x){
	for(int i=1;i<=n;i++)for(int j=0;j<=n+1;j++)g[i][j]=gg[i][j];
	for(int i=1;i<=n;i++)g[i][n+1]-=g[i][0]*x;
//	for(int i=1;i<=n;i++){for(int j=1;j<=n+1;j++)printf("%lf ",g[i][j]);puts("");}puts("");
	for(int i=1;i<=n;i++){
//		printf("%d:\n",i);for(int j=1;j<=n;j++){for(int k=1;k<=n+1;k++)printf("%lf ",g[j][k]);puts("");}puts("");
		int mp=i;
		for(int j=i+1;j<=n;j++)if(fabs(g[j][i])>fabs(g[mp][i]))mp=j;
		if(mp!=i)swap(g[mp],g[i]);
		if(fabs(g[i][i])<eps)return;
		for(int j=1;j<=n;j++){
			if(j==i)continue;
//			if(g[j][i]%g[i][i])return;
			double tmp=g[j][i]/g[i][i];
			for(int k=i;k<=n+1;k++)g[j][k]-=tmp*g[i][k];
		}
	}
//	puts("IN");
	for(int i=1;i<=n;i++){
//		if(g[i][n+1]%g[i][i])return;
		now[i]=(int)(g[i][n+1]/g[i][i]+0.25);
	}
	now[0]=x,sum=0;
//	for(int i=0;i<=n;i++)printf("%d ",now[i]);puts("");
	for(int i=0;i<=n;i++)if(now[i]<0)return;
	for(int i=1;i<=n;i++){
		int ss=0;
		for(int j=0;j<=n;j++)ss+=now[j]*gg[i][j];
		if(ss!=gg[i][n+1])return;
	}
	for(int i=0;i<=n;i++)sum+=now[i];
	if(sum>=res)return;
	res=sum;
	for(int i=0;i<=n;i++)ans[i]=now[i];
}
void print(int ip){
	for(int i=0;i<=6;i++){
//		printf("%d ",ip%10);
		for(int j=1;j<=ans[i];j++)putchar(ip%10?'a':'b');
		ip/=10;
	}
	puts("");
}
int main(){
	for(int i=1;i<=n;i++)scanf("%d",&gg[i][n+1]),mx=max(mx,gg[i][n+1]);
//	for(int i=1;i<=n;i++){for(int j=1;j<=n+1;j++)printf("%2d ",gg[i][j]);puts("");}puts("");
	for(int i=0;i<=mx;i++)work(i);
	if(res==0x3f3f3f3f){puts("-1");return 0;}
	printf("%d\n",res);
	print(1110111);
	print(  11011);
	print( 101101);
	print(1001110);
	return 0;
}
```


---

## 作者：xyf007 (赞：0)

继续提供阴间做法（

题意：定义两个长度相同的字符串的 Hamming 距离 $h(s,t)$ 为 $s_i \neq t_i$ 的 $i$ 的个数。给出六个数 $a,b,c,d,e,f$，你需要构造 4 个长度相等的只由 $\texttt{ab}$ 构成的字符串 $s_1,s_2,s_3,s_4$，满足 $h(s_1,s_2)=a,h(s_1,s_3)=b,h(s_1,s_4)=c,h(s_2,s_3)=d,h(s_2,s_4)=e,h(s_3,s_4)=f$，并且它们的长度最小。如果有多解输出任意一个。

可以发现，$s_1$ 填什么值并不影响答案，因此不妨 $s_1=\texttt{aa\ldots a}$。这时每一位上 $s_2,s_3,s_4$ 只有 8 种情况，分别是 $\texttt{aaa},\texttt{aab},\texttt{aba},\texttt{abb},\texttt{baa},\texttt{bab},\texttt{bba},\texttt{bbb}$。又发现 $\texttt{aaa}$ 是没用的，于是只有 7 种情况。

考虑直接写出 $s_1,s_2,s_3,s_4$
$$
\begin{aligned}
    s_1&=\texttt{aa\ldots a|aa\ldots a|aa\ldots a|aa\ldots a|aa\ldots a|aa\ldots a|aa\ldots a}\\
    s_2&=\texttt{aa\ldots a|aa\ldots a|aa\ldots a|bb\ldots b|bb\ldots b|bb\ldots b|bb\ldots b}\\
    s_3&=\texttt{aa\ldots a|bb\ldots b|bb\ldots b|aa\ldots a|aa\ldots a|bb\ldots b|bb\ldots b}\\
    s_4&=\texttt{bb\ldots b|aa\ldots a|bb\ldots b|aa\ldots a|bb\ldots b|aa\ldots a|bb\ldots b}
\end{aligned}
$$

把连续的 $\texttt{ab}$ 段长度分别设为 $l_1,l_2,\ldots,l_7$。则
$$
\begin{aligned}
t_4+t_5+t_6+t_7&=a\\
t_2+t_3+t_6+t_7&=b\\
t_1+t_3+t_5+t_7&=c\\
t_2+t_3+t_4+t_5&=d\\
t_1+t_3+t_4+t_6&=e\\
t_1+t_2+t_5+t_6&=f
\end{aligned}
$$
七个未知数六个方程，有一个自由变元。其他题解的做法都是枚举其中一个，然后高斯消元。但是你发现这个方程组其实很好解（  
不妨枚举 $t_7$，然后前三个方程两两相加，后三个方程两两相加可以直接算出每一个值。即
$$
\begin{aligned}
t_1&=\frac{e+f-a-b}{2}+t_7\\
t_2&=\frac{d+f-a-c}{2}+t_7\\
t_3&=\frac{b+c-f}{2}-t_7\\
t_4&=\frac{d+e-b-c}{2}+t_7\\
t_5&=\frac{a+c-e}{2}-t_7\\
t_6&=\frac{a+b-d}{2}-t_7
\end{aligned}
$$
因此总长为 $t_1+t_2+t_3+t_4+t_5+t_6+t_7=\dfrac{d+e+f}{2}+t_7$。先判断奇偶性再判断是否能都大于等于 0 即可。
```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
int a, b, c, d, e, f, min, t[8];
void checkmin(int &x, int y)
{
    if (x > y)
    {
        x = y;
    }
}
int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> a >> b >> c >> d >> e >> f;
    if (((e + f - a - b) & 1) || ((d + f - a - c) & 1) || ((b + c - f) & 1) || ((d + e - b - c) & 1) || ((a + c - e) & 1) || ((a + b - d) & 1))
    {
        std::cout << -1;
        return 0;
    }
    t[1] = (e + f - a - b) >> 1;
    t[2] = (d + f - a - c) >> 1;
    t[3] = (b + c - f) >> 1;
    t[4] = (d + e - b - c) >> 1;
    t[5] = (a + c - e) >> 1;
    t[6] = (a + b - d) >> 1;
    bool ok = std::all_of(t + 1, t + 7, [](const int &x) -> bool { return x >= 0; });
    for (; !ok && t[7] <= a && t[7] <= b && t[7] <= c; t[7]++)
    {
        t[1]++;
        t[2]++;
        t[3]--;
        t[4]++;
        t[5]--;
        t[6]--;
        ok |= std::all_of(t + 1, t + 7, [](const int &x) -> bool { return x >= 0; });
    }
    if (!ok)
    {
        std::cout << -1;
        return 0;
    }
    std::cout << (min = (d + e + f) / 2 + t[7]) << '\n';
    for (int i = 1; i <= min; i++)
    {
        std::cout << 'a';
    }
    std::cout << '\n';
    for (int i = 1; i <= t[1] + t[2] + t[3]; i++)
    {
        std::cout << 'a';
    }
    for (int i = 1; i <= t[4] + t[5] + t[6] + t[7]; i++)
    {
        std::cout << 'b';
    }
    std ::cout << '\n';
    for (int i = 1; i <= t[1]; i++)
    {
        std::cout << 'a';
    }
    for (int i = 1; i <= t[2] + t[3]; i++)
    {
        std::cout << 'b';
    }
    for (int i = 1; i <= t[4] + t[5]; i++)
    {
        std::cout << 'a';
    }
    for (int i = 1; i <= t[6] + t[7]; i++)
    {
        std::cout << 'b';
    }
    std::cout << '\n';
    for (int i = 1; i <= t[1]; i++)
    {
        std::cout << 'b';
    }
    for (int i = 1; i <= t[2]; i++)
    {
        std::cout << 'a';
    }
    for (int i = 1; i <= t[3]; i++)
    {
        std::cout << 'b';
    }
    for (int i = 1; i <= t[4]; i++)
    {
        std::cout << 'a';
    }
    for (int i = 1; i <= t[5]; i++)
    {
        std::cout << 'b';
    }
    for (int i = 1; i <= t[6]; i++)
    {
        std::cout << 'a';
    }
    for (int i = 1; i <= t[7]; i++)
    {
        std::cout << 'b';
    }
    return 0;
}
```

---

