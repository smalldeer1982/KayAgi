# [NWRRC 2017] Joker

## 题目描述

Joker 准备了一种新的纸牌戏法，具有强烈的数学背景。你被要求帮助 Joker 进行计算。

有一排 $n$ 张牌，上面写着非零数字 $a_{i}$。我们称所有正数的和为 $P$，所有负数的和为 $N$。每张牌 $i$ 的权重为 $w_{i} = a_{i}/P$ 如果 $a_{i} > 0$，否则为 $a_{i}/|N|$。

我们用 $s_{i} = ( \sum_{j=1}^{j \le i}{w_j})$ 表示。Joker 需要知道使 $s_{i}$ 最大的正整数 $i$。如果有多个这样的 $i$，他对最小的一个感兴趣。

但静态的戏法很无聊，所以 Joker 想要改变一些牌上的数字，并且在每次改变后，他需要知道最大的 $s_{i}$ 在哪里。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 7
1 -5 3 -5
4 -1
2 -1
3 10
4 10
1 -1
2 1
3 -1
```

### 输出

```
3
1
3
3
1
4
4
4
```

# 题解

## 作者：agicy (赞：11)

本文将同步发布于：

- [洛谷博客](https://www.luogu.com.cn/blog/Lu-Anlai/solution-p7028)；
- [csdn](https://blog.csdn.net/Lu_Anlai/article/details/117381947)；
- [博客园](https://www.cnblogs.com/Lu-Anlai/p/14824907.html)；
- [简书](https://www.jianshu.com/p/052a4e936683)。

## 题目

题目链接：[洛谷 P7028](https://www.luogu.com.cn/problem/P7028)、[gym101612J](https://codeforces.com/gym/101612/problem/J)。

### 题意概述

有一个长度为 $n$ 的数列，第 $i$ 个元素的值为 $a_i$，其中 $a_i\neq 0$，定义 $P$ 为数列中所有正整数的和，$N$ 为所有负整数的和。定义一个元素的重要值 $w_i=\begin{cases}\dfrac{a_i}{P}&a_i>0\\
\dfrac{a_i}{|N|}&\text{otherwise}\end{cases}$
，并定义 $s_i$ 为前 $i$ 个元素的重要值之和，即 $\sum\limits_{j=1}^iw_j$。

请先求出当前数列中使 $s_i$ 最小的 $i$。然后有 $m$ 次操作，每次操作将某个元素改成一个给定的值，请在每次操作后求出当数列中使 $s_i$ 最大最小下标 $i$。

## 题解

### 分析性质

事实上，我们要求的就是最小的 $i$ 使得

$$s_i=\max_{j=1}^n\{s_j\}$$

考虑到 $P$ 和 $|N|$ 均为正整数（若有一项是 $0$，则显然答案为 $n$），我们给等式两边同时乘上 $P\cdot |N|$，得到

$$s_i\cdot P\cdot |N|=\max_{j=1}^n\left\{s_j\cdot P\cdot |N|\right\}$$

拆开 $s_i$ 的定义式，得到

$$\sum_{k=1}^iw_k\cdot P\cdot |N|=\max_{j=1}^n\left\{\sum_{k=1}^jw_k\cdot P\cdot |N|\right\}$$

再代入 $w_i$ 的定义式，得到单个点的值为

$$
\begin{aligned}
&\sum_{k=1}^i\left(\frac{a_k[a_k<0]}{|N|}P|N|+\frac{a_k[a_k>0]}{P}P|N|\right)\\
=&\sum_{k=1}^i\left(a_k[a_k<0]\cdot P+a_k[a_k>0]\cdot |N|\right)\\
=&\sum_{k=1}^i\left(a_k[a_k<0]\cdot P+a_k[a_k>0]\cdot |N|\right)\\
=&\left(\sum_{a_k<0,k\leq i}^ia_k\right)\cdot P+\left(\sum_{a_k>0,k\leq i}a_k\right)\cdot|N|\\
=&-\left(\sum_{a_k<0,k\leq i}^i-a_k\right)\cdot P+\left(\sum_{a_k>0,k\leq i}a_k\right)\cdot |N|\\
=&\left(\sum_{a_k>0,k\leq i}a_k\right)\cdot |N|-\left(\sum_{a_k<0,k\leq i}^i-a_k\right)\cdot P
\end{aligned}
$$

### 图形转换

我们观察上式，不难发现它与叉积的形式类似。

我们不妨定义

$$\vec{p}_i=
\begin{cases}
(a_i,0),&a_i>0\\
(0,-a_i),&a_i<0
\end{cases}
$$

再定义 $\overrightarrow{\texttt{sum}}_i=\sum\limits_{j=1}^i\vec{p}_j$

那么

$$\left(\sum_{a_k>0,k\leq i}a_k\right)\cdot |N|-\left(\sum_{a_k<0,k\leq i}^i-a_k\right)\cdot P$$

就可以转化为

$$\overrightarrow{\texttt{sum}}_i\times \overrightarrow{\texttt{sum}}_n$$

现在问题转化为了给定一个向量 $\overrightarrow{\texttt{sum}}_n$ 和一堆向量 $\overrightarrow{\texttt{sum}}_i$，求解其叉积的最大值。

我们不难得到，叉积的最大值一定在 $\overrightarrow{\texttt{sum}}_i$ 对应的下凸包上取到。

### 分析时间复杂度

现在我们需要维护一个下凸包，每次询问在凸包上二分得到答案，而每次修改我们需要暴力重构凸包。

- 询问：时间复杂度为 $\Theta(\log_2n)$；
- 修改：由于这些点的横纵坐标都具有单调性，无需排序，时间复杂度为 $\Theta(n)$。

两种操作的时间复杂度不均衡，而操作次数却相同，这提示我们用 **序列分块** 的方法均衡时间复杂度。

### 序列分块

考虑对每 $B$ 个操作分一块，每个操作只考虑自己 块内的所有向量。

根据叉积分配率 $\bold{a}\times(\bold{b}+\bold{c})=\bold{a}\times\bold{b}+\bold{a}\times\bold{c}$，我们不难得出，这样在每个块内部查询到的最大值一定是块的局部最大值。

- 修改：我们每次修改都暴力重构一个块内部的下凸包，并维护前缀和，时间复杂度 $\Theta(B+\log_2n)$；
- 查询：我们每次查询都询问所有块的局部最大值，再通过快速查询前缀和（树状数组）得到真实最大值，时间复杂度 $\Theta(\frac{q}{B}\log_2B+\frac{q}{B}\log_2n)$。

理论分析得到 $B=\sqrt{n\log_2n}$ 时复杂度最优（为了方便，视 $\log_2B$ 与 $\log_2n$ 同阶，$n$ 与 $q$ 同阶），为 $\Theta(n\sqrt{n\log_2n})$。

### 参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
	inline Vector operator-(void)const{
		return Vector(-x,-y);
	}
};

inline ll dot(const Vector& a,const Vector& b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}

inline ll cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

typedef Vector Point;

const int MAXN=5e4+5;
const int MAXM=5e4+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m;
int a[MAXN];
int lef[MAXN],rig[MAXN],id[MAXN];

struct Node{
	int id;
	Point p;
	inline Node(reg int id,const Point& p):id(id),p(p){
		return;
	}
};

vector<Node> S[MAXN];

inline void build(reg int id){
	S[id].clear();
	Point sum(0,0);
	for(reg int i=lef[id];i<=rig[id];++i){
		if(a[i]>0)
			sum=sum+Point(a[i],0);
		else
			sum=sum+Point(0,-a[i]);
		while(S[id].size()>=2u&&cross(S[id].back().p-(S[id].end()-2)->p,sum-S[id].back().p)<0)
			S[id].pop_back();
		S[id].push_back(Node(i,sum));
	}
	return;
}

inline int query(reg int id,const Vector& p){
	reg int _l=0,_r=S[id].size()-1,_mid;
	while(_l<_r){
		_mid=(_l+_r)>>1;
		if(cross(S[id][_mid+1].p-S[id][_mid].p,p)>0)
			_l=_mid+1;
		else
			_r=_mid;
	}
	return S[id][_l].id;
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	Vector unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,const Vector& a){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=unit[i]+a;
		return;
	}
	inline Vector query(reg int id){
		Vector res;
		for(reg int i=id;i;i^=lowbit(i))
			res=res+unit[i];
		return res;
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	BIT::Init(n);
	for(reg int i=1;i<=n;++i)
		if(a[i]>0)
			BIT::update(i,Vector(a[i],0));
		else
			BIT::update(i,Vector(0,-a[i]));
	reg int B=max(100,int(sqrt(n*log2(n)))),tot=(n+B-1)/B;
	pair<ll,int> ans=make_pair(inf,-1);
	for(reg int i=1;i<=tot;++i){
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
		for(reg int j=lef[i];j<=rig[i];++j)
			id[j]=i;
		build(i);
		Vector sum=BIT::query(n);
		int pos=query(i,sum);
		ans=min(ans,make_pair(-cross(BIT::query(pos),sum),pos));
	}
	writeln(ans.second);
	while(m--){
		static int p,v;
		p=read(),v=read();
		if(a[p]>0)
			BIT::update(p,-Vector(a[p],0));
		else
			BIT::update(p,-Vector(0,-a[p]));
		a[p]=v;
		if(a[p]>0)
			BIT::update(p,Vector(a[p],0));
		else
			BIT::update(p,Vector(0,-a[p]));
		build(id[p]);
		ans=make_pair(inf,-1);
		Vector sum=BIT::query(n);
		for(reg int i=1;i<=tot;++i){
			int pos=query(i,sum);
			ans=min(ans,make_pair(-cross(BIT::query(pos),sum),pos));
		}
		writeln(ans.second);
	}
	flush();
	return 0;
}
```


---

## 作者：JWRuixi (赞：0)

## P7028 [NWRRC2017] Joker

### 题意

给定长度为 $n$ 的序列 $a$，定义 $A = \sum\limits_{i \le n} a_i [a_i \ge 0]$，$B = -\sum\limits_{i \le n} a_i [a_i < 0]$，定义序列 $b$ 满足 $b_i = \begin{cases} a_i / A & a_i \ge 0 \\ a_i / B & a_i < 0 \end{cases}$，求 $b$ 的前缀和的最大值的位置。有 $q$ 此修改，每次修改形如 $a_x \gets y$，再初始时和每次修改后输出上述问题的答案。

$n, q \le 1.2 \times 10^5$，任意时刻 $A, B \le 10^9$。

### 分析

考虑记 $f_i = \sum\limits_{j \le i} b_j [a_i \ge 0], g_i = -\sum\limits_{j \le i} b_j [a_i < 0]$，那么问题所求即 $\arg\max\limits_i (f_i / A - g_i / B)$，转化一下即 $\arg\max\limits_i (f_i - g_i \times \dfrac{A}{B})$。

可以将这个看作是凸包上求截距最大值，显然可以直接通过分块（重构所在块，其它打标记）做到在线 $\mathcal O(m \sqrt{n \log n})$，但是离线有更优秀的做法。

考虑根号重构，记每 $B$ 次询问重构一次。将询问涉及到的位置标为关键点，显然至多有 $B$ 个。不难发现对于每一个块，$A / B$ 是固定的，可以直接算出。

一个直接的想法是对于整个数组建上凸壳，那么按斜率排序后结合指针移动可以做到线性查询 $B$ 个询问。发现问题在于 $B$ 个关键点的值可能发生变化，于是考虑分段，满足只有第一个元素可能是关键点，显然可以将序列分为不超过 $B$ 段。

记 $f', g'$ 表示这 $B$ 次修改之前的 $f, g$ 数组。那么对于每一段，我们可以对 $B$ 个询问各算出一个额外的贡献 $h$，表示实际上的值是 $f'_i - g'_i \times \dfrac{A}{B} + h$，显然对于一个固定的询问这一段中的 $i$ 对应的$h$ 是相同的。那么直接结合上述提到的做法就可以解决这一段的贡献了，由于最多 $B$ 段，所以这一部分的复杂度是 $\mathcal O(n + B^2)$。

总复杂度是 $\mathcal O((n + B^2) \times \dfrac{m}{B})$。平衡一下，最优复杂度 $\mathcal O(m \sqrt n)$。

### Code

代码：<https://pastebin.com/25tF3pqK>。

---

