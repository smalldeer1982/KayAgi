# [RC-06] Minimum and Maximum

## 题目背景

受洛谷限制，本题数据有所删减。评测全套数据请到 [InfOJ](http://119.27.163.117/contest/7/)。

## 题目描述

给定长度为 $n$ 的序列 $[a_1,a_2,\dots ,a_n]$。

$m$ 次询问，每次给出四个正整数 $L_1,R_1,L_2,R_2\ (1\le L_1\le R_1\le 4000,1\le L_2\le R_2\le 4000)$，问有多少个区间 $[l,r]\ (1\le l\le r\le n)$ 满足 $a_l,a_{l+1},\dots,a_r$ 中的最大值属于 $[L_1,R_1]$、最小值属于 $[L_2,R_2]$。

询问次数很大，所以询问是在程序内生成的。请自行阅读提示说明一栏的代码。

## 说明/提示

**样例 1 解释**

五次询问的 $(L_1,R_1,L_2,R_2)$ 分别为 $(1,5,1,5),(1,2,2,4),(3,4,2,2),(2,4,2,2),(2,5,2,5)$，答案分别为 $15,1,1,2,6$。

输出 $(1\times 15)\ \mathrm{xor}\ (2\times 1)\ \mathrm{xor}\ (3\times 1)\ \mathrm{xor}\ (4\times 2)\ \mathrm{xor}\ (5\times 6)=24$。

**样例程序**

下面是我们提供的样例程序，你可以直接以其为基础编写你的程序。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace Generator{
typedef unsigned long long ull;
typedef __uint128_t L;
ull seed;
int p,q;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
}F(2);
void init(){
	cin>>p>>q>>seed;//读入 p,q,seed 
	assert(p!=q);
	F=FastMod(q-p+1);
}
unsigned long long rd () {
	seed ^= (seed << 13);
	seed ^= (seed >> 7);
	seed ^= (seed << 17);
	return seed;
}
void getlr(int &l1,int &r1,int &l2,int &r2){
	//将 l1,r1,l2,r2 作为参数传入，即可得到一组询问 
	l1=F.reduce(rd())+p;
	r1=F.reduce(rd())+p;
	l2=F.reduce(rd())+p;
	r2=F.reduce(rd())+p;
	if(l1>r1)swap(l1,r1);
	if(l2>r2)swap(l2,r2);
}

}
int n,m,a[100005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	Generator::init();
	long long xorsum=0;
	for(int i=1,l1,r1,l2,r2;i<=m;i++){
		Generator::getlr(l1,r1,l2,r2);
		long long ans=/*ans保存你的答案*/;
		xorsum^=ans*i;
	}
	cout<<xorsum;
}
```

**数据范围**

本题有四个子任务。子任务一时间限制 $0.5$ 秒，其它子任务时间限制 $5$ 秒。

所有数据均满足：$1\le n\le 10^5$，$1\le m\le 2\times 10^7$，$1\le a_i\le 4000$，$1\le p\lt q\le 4000$，$0\le seed\lt 2^{64}$。

- 子任务 $1$（$5$ 分）：$n,m,a_i,q\le 10$。
- 子任务 $2$（$20$ 分）：$n\le 10^4$。
- 子任务 $3$（$20$ 分）：$a_i,q\le 10$。
- 子任务 $4$（$55$ 分）：无特殊限制。

## 样例 #1

### 输入

```
5 5
2 4 1 3 5
1 5 1145141919810```

### 输出

```
24```

## 样例 #2

### 输入

```
10 20000000
1 3 4 10 5 5 2 7 10 7
1 10 23333333333333333```

### 输出

```
548722417```

# 题解

## 作者：_•́へ•́╬_ (赞：7)

## 思路

预处理 $b[i][j]$ 表示区间里所有值都在 $i,j$ 之间的区间有多少个。

回答问题时按下图容斥：大正方形减去黄正方形减去绿正方形再加上黄绿重叠就是红色要求的，白色为 $0$ 所以不考虑。$\mathcal O(1)$ 回答。

![](https://cdn.luogu.com.cn/upload/image_hosting/xwgsnrff.png)![](https://cdn.luogu.com.cn/upload/image_hosting/1smqn7iq.png)

预处理 $b$ 很简单。$\mathcal O(nV)$ 预处理。

## code

```cpp
#include<stdio.h>
#include<vector>
#define ull unsigned long long
#define N 100005
#define M 4002
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
inline void read(ull&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int p,q,l[N],r[N];ull xorsum,s,b[M][M];
struct mod
{
	ull b;__int128 m;
	inline mod(const ull&b):b(b),m(((__int128)(1)<<64)/b){}
	inline ull reduce(const ull&a)
	{
		ull q=m*a>>64;
		ull r=a-q*b;
		return r>=b?r-b:r;
	}
}f(2);
inline ull rd(){return s^=s<<13,s^=s>>7,s^=s<<17,s;}
inline void getlr(int&l1,int&r1,int&l2,int&r2)
{
	l1=f.reduce(rd())+p;
	r1=f.reduce(rd())+p;
	l2=f.reduce(rd())+p;
	r2=f.reduce(rd())+p;
	if(l1>r1)l1^=r1^=l1^=r1;
	if(l2>r2)l2^=r2^=l2^=r2;
}
int n,m,a[N];vector<int>c[M];
main()
{
	read(n);read(m);
	for(int i=0;i<n;read(a[i]),c[a[i]].emplace_back(i),++i);
	read(p);read(q);read(s);
	f=mod(q-p+1);
	for(int i=p;i<=q;++i)
	{
		for(int i=0;i<n;l[i]=r[i]=-1,++i);
		for(int j=i;j<=q;++j)
		{
			b[i][j]=b[i][j-1];
			for(int k=0,o;k<c[j].size();++k)
			{
				o=c[j][k];l[o]=r[o]=o;++b[i][j];
				if(o&&~l[o-1])b[i][j]+=o-l[o-1],r[l[o-1]]=o,l[o]=l[o-1];
				if(o<n-1&&~l[o+1])
					b[i][j]+=(o-l[o]+1ll)*(r[o+1]-o),
					l[r[o+1]]=l[o],r[l[o]]=r[o+1];
			}
		}
	}//预处理
	for(int i=1,l1,r1,l2,r2;i<=m;++i)
	{
		getlr(l1,r1,l2,r2);
		if(l2>r1)continue;
		xorsum^=(b[l2][r1]-b[l2][l1-1]-b[r2+1][r1]+b[r2+1][l1-1])*i;
	}
	printf("%llu",xorsum);
}
```


---

## 作者：Wf_yjqd (赞：1)

模拟赛的最后一题，考场 $25$ 分。

部分分思路是 RMQ+ 二维前缀和，就不细讲了。

放一点核心代码：

```cpp
mnn[i][j]=min(mnn[i][j-1],mnn[i+(1<<j-1)][j-1]),mxx[i][j]=max(mxx[i][j-1],mxx[i+(1<<j-1)][j-1]);
```

```cpp
mx=max(mxx[l][lg[r-l+1]],mxx[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
mn=min(mnn[l][lg[r-l+1]],mnn[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
ewqzh[mx][mn]++;
```

```cpp
ewqzh[i][j]+=ewqzh[i][j-1]+ewqzh[i-1][j]-ewqzh[i-1][j-1];
```

------------

个人认为此题主要难度就在预处理上，于是自己琢磨了很久，写一篇题解吧。

------------

考虑一个区间，并不是所有位置都影响答案，可以没用的位置跳过。

没用的位置即既不影响最大值，又不影响最小值的位置。

考虑维护从 $i$ 个位置出发，右侧第一个比区间最小值小的位置 $L_i$ 和第一个比区间最大值大的位置 $R_i$。 

为了在节省空间的情况下只统计右侧的点，先倒序枚举 $L_i$ 和 $R_i$，然后枚举 $i$。

这样也利于答案的计算，我们只用每次跳到 $L_i$ 和 $R_i$ 中位置较小的一点，然后更新二维前缀和即可。

总体复杂度 $\operatorname{O}(n\times q)$，即忽略常数最多 $4\times10^8$，这题 $5$ 秒跑过很稳好吧！

------------

代码就只放预处理了，别的都直接复制的题目中的模板。
```cpp
for(ll i=0;i<=4001;i++)
    L[i]=R[i]=n+1;
ll xorsum=0,l,r;
for(ll i=n;i>=1;i--){
	for(ll j=1;j<=4000;j++){
		if(j==a[i])
			L[j]=R[j]=i;
		else if(j<a[i])
			R[j]=i;
		else
			L[j]=i;
	}
	l=r=a[i];
	for(ll j=i;j<=n;j=min(L[l-1],R[r+1])){
		l=min(l,a[j]);
		r=max(r,a[j]);
		ewqzh[l][r]+=min(L[l-1],R[r+1])-j;
    }
}
//haiwang_tjn
```


---

