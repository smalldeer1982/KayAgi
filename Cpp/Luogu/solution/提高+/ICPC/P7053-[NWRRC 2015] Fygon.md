# [NWRRC 2015] Fygon

## 题目描述

# [NWRRC2015] Fygon 翻译


弗雷德里克是一名年轻的程序员。他参加了所有能找到的编程比赛，并总是使用他最喜欢的编程语言 Fygon。不幸的是，他经常收到 "超过时间限制 "的结果，即使他的算法是渐近最优的。这是因为 Fygon 解释器非常慢。尽管如此，弗雷德里克还是非常喜欢 Fygon，所以他使用了非渐进优化的方法来使求解符合时间限制。为了方便起见，他要求你写一个程序，能够估算出他的 Fygon 程序所做的确切操作次数。

为了简单起见，我们假设 Fygon 只有两条语句。第一条语句是滞后的。它几乎可以替代任何其他语句。第二条语句是 for 循环：

for in range $():$

这意味着遍历从 $0$ 到 $-1$ 的值。 在 Fygon 中是从 $a$ 到 $z$ 的小写字母，并且要么是已经定义的，要么是正整数常数。循环语句缩进四个空格，至少包含一条语句。

程序接收变量 $n$ 的输入。该变量具有特殊含义，不能用作循环变量。您的任务是根据变量 $n$ 的值，找出计算 Fygon 程序执行滞后操作次数的公式。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

## 样例 #1

### 输入

```
for i in range(n):
    for j in range(i):
        lag
for x in range(5):
    for y in range(n):
        for z in range(n):
            lag
    lag
```

### 输出

```
1/2 * n * (n-1) + 5 * (n*n + 1)
```

# 题解

## 作者：ix35 (赞：3)

这篇题解有点水。

因为只有六重循环，所以答案最多是关于 $n$ 的六次多项式。

只需要求出 $0,1,2,3,4,5,6$ 处的点值再插值回去就行了。

求点值直接暴力，而插值这里我采用了范德蒙德矩阵的逆，我直接打出了 $7\times 7$ 的表，实际上想要算的话可以看我上一篇题解里的链接 https://www.luogu.com.cn/blog/ix-35/solution-p7016。

注意分数类运算。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=45;
struct Frac {
	Frac (int a=0,int b=0) {x=a,y=b;}
	ll x,y;
}px[MAXN],py[MAXN],xs[MAXN];
int n,m,l,sj[MAXN],op[MAXN],ox[MAXN],oy[MAXN],nv[MAXN];
ll v[7][7]={  // 这表大概是范德蒙德逆矩阵的一个分子，具体的有点忘了
{720,-1764,1624,-735,175,-21,1},
{0,-720,1044,-580,155,-20,1},
{0,-360,702,-461,137,-19,1},
{0,-240,508,-372,121,-18,1},
{0,-180,396,-307,107,-17,1},
{0,-144,324,-260,95,-16,1},
{0,-120,274,-225,85,-15,1}};
ll b[7]={720,-120,48,-36,48,-120,720};
string s;
ll gcd (ll a,ll b) {return (b?gcd(b,a%b):a);}
Frac yf (Frac a) {
	if (a.x==0) {a.y=1;return a;}
	ll tmp=gcd(a.y,a.x);
	a.y/=tmp,a.x/=tmp;
	return a;
}
Frac add (Frac a,Frac b) {
	ll tmp=gcd(a.y,b.y);
	tmp=a.y/tmp*b.y;
	Frac c;
	c.y=tmp;
	c.x=a.x*(tmp/a.y)+b.x*(tmp/b.y);
	return yf(c);
}
Frac neg (Frac a) {
	a.x*=-1,a.y*=-1;
	return yf(a);
}
Frac minus (Frac a,Frac b) {
	return yf(add(a,neg(b)));
}
Frac mult (Frac a,Frac b) {
	Frac c;
	c.x=a.x*b.x,c.y=a.y*b.y;
	return yf(c);
}
Frac ds (Frac a) {
	swap(a.x,a.y);
	return yf(a);
}
Frac divs (Frac a,Frac b) {
	return yf(mult(a,ds(b)));
}
int solve (int l,int r,int in) {
	if (l==r) {return 1;}
	int las=l,res=0;
	for (int i=l+1;i<=r;i++) {
		if (sj[i]==in) {
			if (op[las]==1) {
				for (int j=0;j<nv[oy[las]];j++) {
					nv[ox[las]]=j;
					res+=solve(las+1,i-1,in+1);
				}
			} else {
				res++;
			}
			las=i;
		}
	}
	if (op[las]==1) {
		for (int j=0;j<nv[oy[las]];j++) {
			nv[ox[las]]=j;
			res+=solve(las+1,r,in+1);
		}
	} else {
		res++;
	}
	//cout << l << "  " << r << "  " << res << endl;
	return res;
}
int main () {
	int nw=0;
	while (getline(cin,s)) {
		l=s.length();
		int cur=0;
		nw++;
		while (s[cur]==' ') {
			cur+=4;
			sj[nw]++;
		}
		if (s[cur]=='l') {op[nw]=2;}
		else {
			op[nw]=1;
			ox[nw]=s[cur+4]-'a'+10;
			oy[nw]=(s[cur+15]>='a'&&s[cur+15]<='z')?(s[cur+15]-'a'+10):(s[cur+15]-'0');
		}
	}
	for (int i=1;i<=9;i++) {nv[i]=i;}
	for (int i=0;i<=6;i++) {
		nv['n'-'a'+10]=i;
		px[i]=Frac(i,1);
		int tmp=solve(1,nw,0);
		py[i]=Frac(tmp,1);
	}
	for (int i=0;i<=6;i++) {
		xs[i].y=1;
		for (int j=0;j<=6;j++) {
			xs[i]=add(xs[i],divs(mult(py[j],Frac(v[j][i],1)),Frac(b[j],1)));
		}
	}
	for (int j=6;j>=0;j--) {
		if (xs[j].x<0) {
			xs[j].x*=-1,xs[j].y*=-1;
		}
		if (xs[j].y<0) {printf("-");xs[j].y*=-1;}
		else if (j<6) {printf("+");}
		printf("%lld/%lld",xs[j].x,xs[j].y);
		for (int k=1;k<=j;k++) {printf("*n");}
	}
	return 0;
}

```


---

