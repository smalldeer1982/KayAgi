# [POI 2010] KOR-Beads

## 题目描述

Byteasar 有 $n$ 个珠子，第 $i$ 个颜色为 $a_i$，和一台机器。

Byteasar 可以选定一个值 $k$，然后机器会让 $1\sim k$ 的珠子组成项链 $b_1$，$k+1\sim 2k$ 的珠子组成项链 $b_2$，以此类推，**最后 $n\bmod k$ 个珠子不会组成项链，而是被丢弃**。

现在让你求出一个 $k$ 值，使得在 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个项链 $b$ 中，存在 **不同的** 项链数量最多。

项链可以反转，形式化地，$b_x$ 和 $b_y$ 不同，当且仅当存在至少一个 $i$，使得 $b_{x,i}\ne b_{y,i}$ 且 $b_{x,i} \ne b_{y,k-i+1}$。

例如 $[1,2,3]$ 和 $[3,2,1]$ 是相同的，而 $[1,2,3]$ 和 $[2,3,1]$ 是不同的。

## 说明/提示

对于全部数据，$1\le n\le2\times 10^5$，且 $\forall 1\le i\le n$，有 $1\le a_i\le n$。

## 样例 #1

### 输入

```
21
1 1 1 2 2 2 3 3 3 1 2 3 3 1 2 2 1 3 3 2 1```

### 输出

```
6 1
2```

# 题解

## 作者：beng (赞：21)

## 题目大意：

给出$n$个数，可将它们分为若干个串，每个串有$k$个数（长度不足$k$则丢弃），求使得不同的串最多的$k$值及串的个数。串可翻转，即子串$1,2,3$和$3,2,1$被认为是一样的。 

## 思路：

本题朴素的思路是枚举$k$和各个串，比较各个串并记录不同的串，但这样比较和记录的时间复杂度不能做到$O(1)$，就肯定会超时。但如果比较和记录的时间复杂度是$O(1)$是不是就不会超时了呢？我们计算一下：

枚举$k$要$O(n)$的时间复杂度，而串有$\lfloor\dfrac{n}{k}\rfloor$个，所以枚举的时间复杂度为

$$\displaystyle\sum_{k=1}^n\lfloor\dfrac{n}{k}\rfloor$$

展开后得到

$$\lfloor\dfrac{n}{1}\rfloor+\lfloor\dfrac{n}{2}\rfloor+...+\lfloor\dfrac{n}{n}\rfloor$$

近似于

$$\dfrac{n}{1}+\dfrac{n}{2}+...+\dfrac{n}{n}$$

把$n$提出来得到

$$n(1+\dfrac{1}{2}+...+\dfrac{1}{n})$$

我们可以发现$1+\dfrac{1}{2}+...+\dfrac{1}{n}$为调和级数，有

$$1+\dfrac{1}{2}+...+\dfrac{1}{n}\approx\ln n<\log_2n$$

又因为我们的比较和记录的时间复杂度是$O(1)$的，所以总共的时间复杂度便是$O(n\log n)$。

所以我们便可以想到使用**哈希**。

与一般的哈希一样，我们先从头弄一个前缀哈希和幂数组，这样若要求$i$到$j$位数字的哈希值便可以用$hash[j]-hash[i-1]*power[j-i+1]$这样来进行计算。但特别的，这题规定串是可以翻转的，所以我们也要从尾弄一个后缀哈希，与前面一样，只不过顺序相反罢了。要求$i$到$j$位数字的哈希值可以这样计算：$hash[i]-hash[j+1]*power[j-i+1]$。这样，查询某个子串便可以这样实现$O(1)$查询。为了不冲突，此处$power$每次要**乘一个很大的质数**才行，这里需要注意。

那么我们的哈希怎么判重呢？我们可以用除余法，若冲突则在下一位保存。如果我们在判重时正反顺序两个都不冲突，我们才认为它是新串，并将正反顺序的哈希值保存下来。

但是我们这里每枚举一次$k$，都要清空判重数组，这样的时间复杂度是很高的，怎么办呢？我们可以用一个$time$数组，表示使用当前位的时间，若他的值为规定的时间，就说明它在当前时间被更新过了，就要对当前位的数进行判重，否则说明这个值只是在之前的时间被更新过，与现在无关，就表明当前位无值。这样就不用每次都更新判重数组了。

其他记录答案什么的就是朴素的暴力做法啦~

## 代码：

```c++
#include<cstdio>//以下为了防止不必要的错误，类型我全都开成了unsigned long long
unsigned long long n,m,i,j1,j2,k,max,nans,ans[200005],a[200005],hash[1000007],b[1000007],power[200005],ha1[200005],ha2[200005];//此处的hash为判重数组，b为time数组，power为幂数组，ha1为前缀哈希，ha2为后缀哈希
unsigned long long ha(unsigned long long x)//判重
{
	unsigned long long y=x%1000007;
	if (b[y]==m&&hash[y]!=x)
	{
		y++;
		if (y==n/m)
		y=0;
	}
	return y;
}
int main()
{
	scanf("%d",&n);
	power[0]=1;
	for (m=1;m<=n;m++)
	scanf("%d",&a[m]),power[m]=power[m-1]*19260817,ha1[m]=ha1[m-1]*19260817+a[m];//读入并预处理幂数组与前缀哈希
	for (m=n;m;m--)
	ha2[m]=ha2[m+1]*19260817+a[m];//预处理后缀哈希
	for (m=1;m<=n;m++)//枚举题目中的k
	{
		k=0;//k为不同串的个数
		for (i=m+1;i<=n+1;i+=m)
		{
			j1=ha(ha1[i-1]-ha1[i-m-1]*power[m]);
			if (hash[j1]==ha1[i-1]-ha1[i-m-1]*power[m])//判断正序是否重复
			continue;
			j2=ha(ha2[i-m]-ha2[i]*power[m]);
			if (hash[j2]==ha2[i-m]-ha2[i]*power[m])//判断反序是否重复
			continue;
			b[j1]=b[j2]=m,hash[j1]=ha1[i-1]-ha1[i-m-1]*power[m],hash[j2]=ha2[i-m]-ha2[i]*power[m],k++;//记录时间戳，保存正反顺序两个串
		}
		//以下为记录答案
		if (k>max)
		max=k,nans=1,ans[1]=m;
		else
		if (k==max)
		nans++,ans[nans]=m;
	}
	printf("%lld %lld\n",max,nans);
	for (m=1;m<=nans;m++)
	printf("%lld ",ans[m]);
	return 0;
}
```


---

## 作者：XyzL (赞：13)

此题与哈希表关系不大，只要求出哈希前缀和后缀和即可！

详细代码注释如下：


```cpp
//#pragma GCC optimize(3)

#include<bits/stdc++.h>

using namespace std;

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if(c == '-') {
			f = -1;
		}
		c = getchar();
	}
	while (c <= '9' && c >= '0') {
		x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	}
	return x * f;
}

#define Mem(a, x) memset(a, x, sizeof(a))
#define Binary l + r >> 1
#define Inf 2147483647

using namespace std;

const unsigned int kM = 10000007;  // 质数
const unsigned int kB = 19260817;  // 进制底数
const int Maxn = 200003;

int h[kM];  // 哈希表，标记按k切分是否占用
int a[Maxn], l[Maxn];
unsigned long long pre[Maxn], suf[Maxn], pw[Maxn];  // 前缀哈希和、后缀哈希和、底数指数 
int n, m, ans, ansc;

void Init() {  // 初始化哈希和
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) {
		pw[i] = pw[i - 1] * kB % kM;           // 指数累乘
		pre[i] = (pre[i - 1] * kB + a[i]) % kM;  // 前缀累加
	}
	for (int i = n; i >= 1; --i) {
		suf[i] = (suf[i + 1] * kB + a[i]) % kM;  // 后缀累加
	}
	return; 
}

int main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	Init();
	for (int k = 1; n / k >= ans; ++k) {              // 切割长度
		int t = 0;                                      // 不同子序列个数
		for (int i = k; i <= n; i += k) {               // 切割
			int p = (pre[i] - pre[i - k] * pw[k]) % kM;  // 正向序列哈希
			if (h[p] == k) {                              // 出现
				continue;
			}
			t++;                                              // 累加答案
			h[p] = k;                                         // 标记正向序列
			p = (suf[i - k + 1] - suf[i + 1] * pw[k]) % kM;  // 反向序列哈希
			h[p] = k;                                         // 标记反向序列
		}
		if (t > ans) {  // 更新答案
			ans = t;
			ansc = 0;
		}
		if (t == ans) {
			l[++ansc] = k;
		}
	}
	// 输出答案
	printf("%d ", ans);
	printf("%d\n", ansc);
	for (int i = 1; i <= ansc; ++i) {
		printf("%d ", l[i]);
	}
	puts("");
	return 0;
}
```


---

## 作者：zhangxiao666 (赞：7)

### 前言：
最近在做哈希的题，发现了这道好题，看题解里很多大佬的方法都很巧妙，自己就发一个较为朴素的方法吧。

### 题意：

[题目传送门](https://www.luogu.com.cn/problem/P3498)

给你一个序列，需要求出数 $k$，使划分的子串长度为 $k$ 时，不同的子串数量最多。还要注意几件事：

1. 子串可以反转，比如 $(1,2,3)$ 看做与 $(3,2,1)$ 相同。

1. 如果不能正好划分完，剩下的部分不计算。

1. $k$ 可能有多个，这时要输出所有的 $k$，顺序任意。

最后输出两行，第一行两个数，表示最多的不同的子串数量和所有可能的 $k$ 的数量。第二行为每一个 $k$。

### 思路：

这道题肯定要用哈希的（~~题目标签~~），因为我们要判断子串是否相同，而如果每一次都去从头到尾匹配，时间复杂度很高，一定会 TLE 飞。但如果用哈希，就可以 $O(1)$ 比较。

不过，考虑子串可以翻转，可以做一个后缀哈希，即从后往前哈希一次，求出的哈希值即为子串反转后的哈希值。

接下来就好写了，用一个 ``map`` 来记录某个子串是否出现过，没出现过则记录并统计，最后更新答案即可。

注意每一次循环结束之后 ``map`` 要清零（因为存的是这一次的，下一次就用不到了）。

### 代码：

~~请勿抄袭~~。

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int base=10000007;
const int N=2e5;
int n,tot,cnt;
int a[N+10];
ull h1[N+10],h2[N+10],power[N+10];
map<ull,bool> mp;
int ans[N+10];
inline void init()
{
	power[0]=1;
	for(int i=1;i<=n;i++) power[i]=power[i-1]*base;
	for(int i=1;i<=n;i++) 
	{
		h1[i]=h1[i-1]*base+a[i];
	}
	for(int i=n;i>=1;i--)
	{
		h2[i]=h2[i+1]*base+a[i];
	}
}
inline ull get_hash(int l,int r,bool f)
{
	if(f==0) return h1[r]-h1[l-1]*power[r-l+1];
	else return h2[l]-h2[r+1]*power[r-l+1];
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	init();
	for(int i=1;i<=n;i++)
	{
		if(n/i<tot) break;
		int sum=0;
		for(int j=i;j<=n;j+=i)
		{
			int hash1=get_hash(j-i+1,j,0);
			int hash2=get_hash(j-i+1,j,1);
			if(!mp[hash1]&&!mp[hash2])
			{
				mp[hash1]=1;
				mp[hash2]=1;
				sum++;
			}
		}
		if(sum>tot)
		{
			tot=sum;
			cnt=1;
			ans[cnt]=i;
		}
		else if(sum==tot) ans[++cnt]=i;
		mp.clear();
	}

	printf("%d %d\n",tot,cnt);
	for(int i=1;i<=cnt;i++)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}
```

写题解不易，点个赞呗。

---

## 作者：Poncirus (赞：6)

**Upd：抱歉，没有注意到 md 炸了 qwq**

### Description

[题目传送门](https://www.luogu.com.cn/problem/P3498)

有 $n$ 个数 $a_1\sim a_n$，将这 $n$ 个数分割为连续的、长度为 $k$ 的 $\large\lfloor\frac nk\rfloor$ 段，问有哪些 $k$ 可以使得包含数不同的段数最多。

注：段可以翻转，如 $1,2,3$ 在本题等价于 $3,2,1$。

***

### Solution

一个很好想到的暴力打法就是，把 $a$ 用正反两个 `string` 存储，枚举 $k$，模拟分割过程，以 $k$ 为起点，不断截取长度为 $k$ 的子串，用 `set<string>` 或 `map<string,bool>` 判重。

此时清空 $\mathcal O(\log n)$，更新 $\mathcal O(\log n)$，查询 & 判重 $\mathcal O(\log n)$，总体时间复杂度 $\large\mathcal O(\sum\limits_{i=1}^n\frac ni\times \log n)$。

欸？那么上面这一大坨大概是个什么数量级呢？

不知道大家有没有听说过一个名为 [调和级数](https://baike.baidu.com/item/%E8%B0%83%E5%92%8C%E7%BA%A7%E6%95%B0/8019971) 的东西。

> $$
> \sum_{i=1}^n\frac1i=\ln(n+1)+\gamma
> $$
>
> 注：来自于 [调和级数_百度百科](https://baike.baidu.com/item/%E8%B0%83%E5%92%8C%E7%BA%A7%E6%95%B0/8019971)。

其中，$\gamma$ 表示 [欧拉常数](https://baike.baidu.com/item/欧拉常数/5371177)，其值约为 $0.57721$；$\ln(n+1)\approx\log_2(n)$

所以我们大可以在计算时省略掉它。接着对式子变形。
$$
\begin{aligned}
\sum_{i=1}^n\frac ni\times\log_2(n)&=n\times \log_2(n)\times\sum_{i=1}^n\frac1i\\
&=n\times\log_2(n)\times[\ \ln(n+1)+\gamma\ ]\\
&\approx n\log n\log n
\end{aligned}
$$
嗯，看起来 $2\times10^5$ 的数据很吃力的样子。我们可以进行优化。

#### 优化1：字符串 Hash

这个优化可以直接让代码效率提升一个档次。

同样使用正反两个 `hash` 数组对 $a$ 进行哈希，即可将低效的 `string` 更换为效率更高的 `ull`。

主要是注意初始化和查询哈希值时的正反问题。

#### 优化2：最优性 ~~剪枝~~

假设统计到 $[\ i,i+k)$ 这个子串时共有 $tot$ 个互不相同的子串，剩余的部分（即 $[\ i+k,n\ ]$ ）中，按剩下的每一串都与前面的不相同来算，最多也就 $(n-i+k)\div k$ 个，若 $tot+(n-i+k)\div k$ 仍然没有当前最大答案多，即按最优可能性来算，仍然无法更新答案，直接 `break`。

#### 优化3：数据结构优化

能用 STL 干嘛要手写判重呢？

经过作者实验，在 O2 环境下，算上评测姬波动等原因，以下数据结构用时依次为 `unordered_map/hash_map > set ≈ map`，且均能AC。

经过上述优化，你的代码就可以从 TLE $\to$ 较优解了。

***

### Code

```cpp
#include<set>
#include<cstdio>
#define GetHash0(l,r) HasH[0][r]-HasH[0][l-1]*PoW[r-l+1]
#define GetHash1(l,r) HasH[1][l]-HasH[1][r+1]*PoW[r-l+1]
#define int unsigned long long
const int maxn=2e5+5;
const int LEN=(1<<20);
const int _P_=1504831;  //第 114514 个质数
int n,tot,cnt,mx;
std::set<int>vis;
int a[maxn],HasH[2][maxn],PoW[maxn],ans[maxn];
inline int nec(){
    static char buf[LEN],*p=buf,*e=buf;
    if(p==e){
        if((e=buf+fread(buf,1,LEN,stdin))==buf)
            return EOF;
        p=buf;
    }
    return *p++;
}
inline bool read(int&x){
    static char neg=0,c=nec();
    neg=0,x=0;
    while((c<'0'||c>'9')&&c!='-'){
        if(c==EOF)return 0;
        c=nec();
    }
    if(c=='-'){
        neg=1;
        c=nec();
    }
    do{x=x*10+c-'0';}while((c=nec())>='0');
    if(neg)x=-x;
    return 1;
}
inline void init(void){
    PoW[0]=1;
    for(int i=1;i<=n;++i){
        HasH[0][i]=HasH[0][i-1]*_P_+a[i];			//正向 hash
        HasH[1][n-i+1]=HasH[1][n-i+2]*_P_+a[n-i+1];	//反向 hash
        PoW[i]=PoW[i-1]*_P_;						//快速幂
    }
    return;
}
signed main(){
    read(n);
    for(int i=1;i<=n;++i)
        read(a[i]);
    init();
    for(int i=1;i<=n;++i){
        vis.clear();tot=0;
        for(int j=i;j<=n;j+=i){
            if(tot+(n-j+i)/i<mx)break;				//保证答案最优性
            if(vis.find(GetHash0((j-i+1),j))==vis.end()){
                vis.insert(GetHash0((j-i+1),j));
                vis.insert(GetHash1((j-i+1),j));
                ++tot;
            }
        }
        if(tot>mx){mx=tot;ans[cnt=1]=i;}else if(tot==mx)	//更新答案 & 存答案序列
        ans[++cnt]=i;
    }
    printf("%llu %llu\n",mx,cnt);
    for(int i=1;i<=cnt;++i)
        printf("%llu ",ans[i]);
    return 0;
}
```

***

**end.**



---

## 作者：cjh20090318 (赞：5)

大家好，我是 CQ-FZOIer，C2024 级蒟蒻 CJH。

~~暑假作业太多了，来补一篇题解。~~

此题 tag：枚举，暴力；哈希，HASH。

洛谷：[P3498 [POI2010]KOR-Beads](https://www.luogu.com.cn/problem/P3498)

---

# 题意

给定一个长度为 $n$ 的序列，问在序列中连续选取长度为 $k(1 \le k \le n)$ 的序列时字串最多（子串都是可以反转的，一个字串的正序和倒序为一个子串）。

# 分析题目

1. 因为数组没有办法使用 `STL map`，所以我们还是只有使用哈希算法来预处理出序列的前后缀，这里我们仿照字符串哈希的 BKDR 算法。

2. 在 $1 \sim n$ 中枚举 $k$，求出每一段序列的哈希值后再用 `map`（就可以不需要哈希了）存储，判断是否这段哈希值是否存在，如果不存在就可以增加不同子串的数量。

# 注意事项

1. `map` 每一次用完以后一定要**清空**！

2. 哈希前缀**从前往后**处理，哈希后缀**从后往前**处理。

# 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
#define MAXN 200002
using namespace std;
typedef long long LL;//用 LL 替换 long long，简短代码量。
int n,a[MAXN];
LL Hash1[MAXN],Hash2[MAXN],pn[MAXN];//分别为：前缀哈希、后缀哈希、p 的 n 次幂。
map<LL,bool> M;//判断是否有重合的 Hash1&Hash2。
const int p=103;//选取一个远离 2 的整数次幂的质数。
int kkk[MAXN],size=0;//所有的 k 和能获得最大值的k的个数。
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	pn[0]=1;//这一句很重要！初始化 p^0=1。
	for(int i=1;i<=n;i++)
		Hash1[i]=Hash1[i-1]*p+a[i],pn[i]=pn[i-1]*p;//预处理哈希前缀和 p 的 n 次幂。
	for(int i=n;i;i--)
		Hash2[i]=Hash2[i+1]*p+a[i];//预处理哈希后缀。
	int ans=0;//能获得的最大不同的子串个数。
	for(int k=1;k<=n;k++){
		int s=0;M.clear();//当前长度为 k 能获得的不同的子串个数。
		for(int i=1;i<=n-k+1;i+=k){
			LL hs1=Hash1[i+k-1]-Hash1[i-1]*pn[k],hs2=Hash2[i]-Hash2[i+k]*pn[k];//求区间哈希前缀 & 后缀。
			hs1*=hs2;//两数相乘进行计算。
			if(M[hs1]) continue;//如果已经存在就判断下一个字串。
			M[hs1]=1,s++;//标记此子串已存在，个数增加。
		}
		if(s>ans)
			ans=s,kkk[size=1]=k;//更新答案，个数赋值为 1 后存储当前的 k。
		else if(s==ans)
			kkk[++size]=k;//相等则累加
	}
	printf("%d %d\n",ans,size);
	for(int i=1;i<=size;i++)
		printf("%d ",kkk[i]);//输出所有 k。
	return 0;
}

```

*谢谢大家！*

---

## 作者：_zhy (赞：5)

[link](https://www.luogu.com.cn/problem/P3498)。

## 题目大意

给定 ${n}$ 个数，将它们分成 **等长** 的若干段，每一段的长度为 ${k}$（长度不足 ${k}$ 的不用管）。

问 ${k}$ 为多少时使不重复段的数量最多，求出这个数量及 ${k}$ 的值。

**注意：若两个串只是正反颠倒，那么也算相同。**

## 思路

首先看到数据范围：${1 \leq n \leq 2 \times 10 ^ 5}$，就立马打消了暴力的念头。

要比较某一段相等我想到可以使用哈希（[不会的戳这里](https://www.luogu.com.cn/problem/P3370))。

但是这道题求的是整个串中的子串情况，所以应该是一个区间的哈希值，
自然想到用前缀和维护。

但由于若两个串只是正反颠倒也算相同，所以还需维护一个后缀数组。

另外，为了保证哈希算法的正确率更高，我们可以将数组定义为 `long long` 类型，并且适当把进制 $base$ 调大。

还有，其实我们并不用去对哈希值取模，可以让它自然溢出，从而使哈希值在 `long long` 类型中进行循环（~~其实好像和取模没什么两样~~）。

**注意：此时我们并不能用数组来记录每个哈希值是否被标记过，一是数组根本开不了这么大，二是数组下标不能为负！**

所以我们可以使用 `set` 来记录，正好 `set` 也可对数据去重。

代码中附有注释。

## code
```cpp
#include <cstdio>
#include <set>
#define ll long long

static char buf[10000], *p1 = buf, *p2 = buf;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++	//加快 getchar 的速度，本地编译器及比赛慎用。 
inline void read(ll &t) {
	t = 0;
	ll a = 1;
	char ch = getchar();
	while (ch < 48 || ch > 57) {
		if (ch == '-')
			a = -1;
		ch = getchar();
	}
	while (ch >= 48 && ch <= 57) {
		t = (t << 1) + (t << 3) + (ch ^ 48);
		ch = getchar();
	}
	t *= a;
}

inline void write(ll t) {
	if (t < 10) {
		putchar(t + 48);
		return ;
	}
	write(t / 10);
	putchar(t % 10 + 48);
}	//以上是卡常。 

const int N = 2e5 + 5, base = 1331;

using namespace std;

ll n, a[N], sum1[N], sum2[N], p[N], res, l, x[N], s;
bool f[N];
set<ll> Hash;
int main() {
	read(n);
	p[0] = 1;
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		if (!f[a[i]])	//区间长为 1 时答案就是不同元素个数，输入时统计即可。 
			f[a[i]] = true, s++;
		sum1[i] = sum1[i - 1] * base + a[i];	//sum1 表示 Hash 值前缀和。 
		p[i] = p[i - 1] * base;	//求 base 的幂（方便后续计算）。 
	}
	for (int i = n; i; i--)
		sum2[i] = sum2[i + 1] * base + a[i];	//因为 sum2 为 Hash 值的后缀和，所以要在输入完毕后从后往前循环求到。 
	res = s, x[l = 1] = 1;	//区间长为 1 的情况。 
	for (int i = 2; i <= n; i++) {
		Hash.clear();	//每次记得初始化。 
		for (int j = i; j <= n; j += i)
			Hash.insert((sum1[j] - sum1[j - i] * p[i]) * (sum2[j - i + 1] - sum2[j + 1] * p[i]));	//把一个串的正序哈希值与倒序哈希值乘起来，增加正确率。
		int ans = Hash.size();	//去重后的数量就是当前长度的答案。 
		if (ans > res)
			res = ans, l = 1, x[l] = i;		//更新答案。 
		else if (ans == res)
			x[++l] = i;		//若与当前解相同，增加此答案。 
	}
	write(res), putchar('\n'), write(l), putchar('\n');
	for (int i = 1; i <= l; i++)
		write(x[i]), putchar(' ');
	return 0;
}
```

## 优化
虽然这样可以过了，但这个[时间](https://www.luogu.com.cn/record/80682162)……

~~好像比最优解慢 $40$ 多毫秒~~。

我想一定有什么方法可以优化，但算法中枚举子串的循环不可省，也无法继续优化。

于是我把目光放在了枚举子串的长度的循环上。

```cpp
	for (int i = 2; i <= n; i++)
```
好像并不需要从 $1$ 枚举到 $n$，因为当前已经有最优答案 $res$ 了。

而枚举一个长度 $i$，最优时就算每一段都不同，也只有 ${\lfloor \dfrac{n} {i}\rfloor}$ 种，所以当 ${\dfrac{n} {i} > res}$ 时我们就不用继续枚举了。

如下：

```cpp
	for (int i = 2; i <= n / res; i++)
```

现在就快多了：[link](https://www.luogu.com.cn/record/80680314)。

---

## 作者：神犇的蒟蒻 (赞：5)

有一个神奇的东西（调和级数）：



n1+n2+n3+n4+⋅⋅⋅nn≈lnn<logn

知道了这个以后，这道题就是简单的字符串哈希了。

原本想用Hash判重，结果交了一面的WA…于是就用set了。但是网上看题解，貌似有一个Hash用的B特别强，在此先记下：


**上代码**

```cpp
#include<stdio.h>
#include<iostream>
#include<set>
#define ll unsigned long long
#define B 200019
#define M 200005
using namespace std;
ll Base[M],H1[M],H2[M];
int A[M],Ans[M];
set<ll>S;
void Rd(int &res){
    char c;res=0;
    while(c=getchar(),!isdigit(c));
    do{
        res=(res<<1)+(res<<3)+(c^48);
    }while(c=getchar(),isdigit(c));
}
int main(){
    int n,ans=0,sz=0;
    Rd(n);
    for(int i=1;i<=n;i++)
        Rd(A[i]);
    Base[0]=1;
    for(int i=1;i<=n;i++)
        Base[i]=Base[i-1]*B;
    for(int i=1;i<=n;i++)
        H1[i]=H1[i-1]*B+A[i];
    for(int i=n;i>=1;i--)
        H2[i]=H2[i+1]*B+A[i];
    for(int k=1;k<=n;k++){
        if(n/k<ans)break;
        S.clear();
        int cnt=0;
        for(int j=k;j<=n;j+=k){
            ll t1=H1[j]-H1[j-k]*Base[k];
            ll t2=H2[j-k+1]-H2[j+1]*Base[k];
            ll t3=t1*t2;
            if(S.count(t3))continue;
            S.insert(t3);
            cnt++;
        }
        if(cnt>ans){
            ans=cnt;
            sz=0;
            Ans[++sz]=k;
        }else if(cnt==ans)Ans[++sz]=k;
    }
    printf("%d %d\n",ans,sz);
    for(int i=1;i<=sz;i++)
        printf("%d%c",Ans[i],i==sz?'\n':' ');
    return 0;
}
```

---

## 作者：FLAMEs_ (赞：3)

这道题应该是一道不错的哈希题。

知道那个调和级数（大家可以在某度上找到定义）应该就可以直接用哈希求解了。

哦，对，差点忘了，我们应该用$set$去判重。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 200005
const int base=998344353;
int n,a[N],hash_fr[N],hash_be[N],power[N],cnt,tot,num;
int ans[N];
set <int> st;
signed main()
{
	cin>>n;
	power[0]=1;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),hash_fr[i]=hash_fr[i-1]*base+a[i],power[i]=power[i-1]*base;
	for(int i=n;i;i--)hash_be[i]=hash_be[i+1]*base+a[i];
	for(int k=1;k<=n;k++)
	{
		st.clear();cnt=0;
		for(int i=k;i<=n;i+=k)
		{
			int now=(hash_fr[i]-hash_fr[i-k]*power[k])*(hash_be[i-k+1]-hash_be[i+1]*power[k]);
			if(st.count(now))continue;
			st.insert(now);
			cnt++;
		}
		if(cnt>tot)tot=cnt,num=1,ans[1]=k;
		else if(cnt==tot)ans[++num]=k;
	}
	cout<<tot<<" "<<num<<"\n";
	for(int i=1;i<=num;i++)
	cout<<ans[i]<<" ";
	return 0;
}
```


---

## 作者：kczno1 (赞：3)

题意:给你一个串，你要选一个k，之后这个串会被分成类似1..k,k+1..2k的几个子串，

如果最后一截<k就不要了。之后如果两个子串相同或者翻转后相同，就去掉一个。

问最多剩下多少个子串，输出所有可以的k。

题解:暴力枚举，hash之后用sort或者hash去重 nlogn


---

## 作者：CheemsaDoge (赞：2)

> 对于数列 $\{A_i\}$ ，求 $k$ 使数列被分为 $\lfloor \frac{n}{k}\rfloor$ 个部分后不同子数列种类最多（子串翻转前后为一类子串）

- 很容易想到：枚举 $k\ \in\ [1,n]$ ，记录每个 $k$ 下不同种类数，然后取最优即可，那么问题来了：如何计算种类数？

  - 暴戾算法：

    一种纯粹的暴戾算法（雾）便是：对于每个 $k$ 使用 `map` 与 `string` 记录当前串是否出现过，但问题在于字符串需要不断改变，即需要 $2e5$ 的 `string` 变量，无论是时间复杂度还是空间复杂度都是不可接受的。

  - 正解哈希：

    因此我们直接使用 `hash` 算法，并选择 `map` 或者 `set` 判重。

    ```cpp
    /*code by CheemsaDoge*/
    #include <bits/stdc++.h>//用了万能头，我就是啸纣老师口中的低水平（哭
    template<typename T> inline void read(T &x) {/*...*/}//fast input
    template<typename T> inline void write(T x){/*...*/}
    const int MAXM=1e6+1145;const int MAXN=200000+11145;const int INF=2147483647ll;//2^31-1
    #define pc putchar('\n')
    #define pk putchar(' ')
    #define ull unsigned long long
    /*---------------------------------pre------------------------------------*/
    std::set<ull>hash;//直接用unsigned long long让他自己溢出来
    const ull sp=19260817;
    ull s1[MAXN],s2[MAXN],pp[MAXN];
    int a[MAXN],n;
    ull get1(int l,int r) {return s1[r]-s1[l-1]*pp[r-l+1];} //获得hash值（从前往后计算
    ull get2(int l,int r) {return s2[l]-s2[r+1]*pp[r-l+1];} //获得hash值（从后往前计算
    template <typename T> T min(const T _a,const T _b) {return _a<_b?_a:_b;} //手写 min 函数
    int get_ans(int k) {
    	hash.clear();
    	for(int i=0;i*k+k<=n;i++) hash.insert(min<ull>(get1(i*k+1,i*k+k),get2(i*k+1,i*k+k))); //插入当前字符串（子串）的hash值
    	return hash.size(); //返回种类数（set不允许出现相同元素，所以前面可以安心插
    }//得到答案
    std::vector<int>ans;//动态数组存储满足条件的k
    int maxn=-1;//最大的种类数
    int main(){
    	read(n);
    	for(int i=1;i<=n;i++) read(a[i]);
    	pp[0]=1;
    	for(int i=1;i<=n;i++) {
    		s1[i]=1ull*a[i]+s1[i-1]*sp;
    		pp[i]=pp[i-1]*sp;
    	}
    	for(int i=n;i>=1;i--) s2[i]=a[i]+s2[i+1]*sp;//初始化hash
    	for(int i=1;i<=n;i++) {
    		int ma=get_ans(i);//获得k的种类数
    		if(maxn<ma) { //更新答案
    			ans.clear();
    			ans.push_back(i);
    			maxn=ma;
    		}
    		else if(maxn==ma) ans.push_back(i);
    	}
    	write(maxn);pk;write(ans.size());pc;//输出（pc是putchar('\n')，前面的宏有定义
    	for(int i=0;i<(int)ans.size();i++) write(ans[i]),pk;//pk是putchar(' ')
    	return 0; //好习惯捏
    }
    ```

  关于模数：这道题如果 `sp` 被设为 `10007` 亲测会挂，机房里的 $dalao$ 就有这么挂的。

  所以一个好的模数是必不可少的，建议用 `13331` 或者某人的生日 `19260817` 。

---

## 作者：离散小波变换° (赞：2)

## 题目简述

$n$个数，可以按照长度为$k$分为$[1,k],[k+1,2\times k],\cdots$共$\left\lfloor\dfrac{n}{k}\right\rfloor$条数字串。要求互不相同的串尽量多。**一条串翻转后被认为是同一条串**。

## 题解

非常好的字符串哈希题。

### 求哈希值

很显然，我们可以枚举每个$k$，然后判断$\left\lfloor\dfrac{n}{k}\right\rfloor$个串中互不相同的串有多少个。我们可以用哈希表判重。但是如何快速算出$[(i-1)\times k+1,i\times k]$这个子串的哈希值呢？

我们可以按照这样的方法进行字符串哈希：

$$H(S)=\left(\sum_{i=1}^{S.length}S_i\times seed^{i-1}\right) \bmod 2^{64}$$

这种方法，**本质上**就是把字符串转成了$seed$进制的数，并对$2^{64}$取模（即$\text{unsigned long long}$自然溢出）
。举个栗子：一个十进制数$1145141919810$，我们要取出它从左往右第三位到第七位，那么就是$1145141-11\times 10^5=45141$。$seed$进制同理，

$$H(S_{sub[l,r]})=\left(pre_r-pre^{l-1}\times seed^{r-l+1}\right) \bmod 2^{64}$$

其中$pre_i$表示$S$的前$i$个字符的哈希值。翻转的数字串同理即可。

然后是关于哈希表的问题。

### 建哈希表

最简单的方法，就是用$\rm map$直接插入哈希值。这样时间复杂度单次其实是$\mathcal O(\log N)$。我们希望更快的时间复杂度，又希望较少的空间复杂度，还不希望因此增加哈希碰撞的概率，怎么办？这里给出更快的方法。

图论中的链式前向星，给每个邻接表添加节点$\operatorname{add}(u,v)$，本质上就是给链表$u$增加了一个元素$v$。那么我们完全可以将$u$变为哈希值对分配的内存$SIZE$取模后的结果，而$v$变为哈希值本来的值。

```
\\链式前向星加点
void add(int u,ULL v){
    ver[++tot]=v,nxt[tot]=head[u],head[u]=tot;
}
\\给哈希表增加元素
add(h%SIZ,h);
```

关于查询操作，为了减少哈希碰撞，我们扫描一遍哈希值取模后的值所对应的邻接表的元素，检查是否存在元素的值等于它。

```
bool fnd(ULL hsh){
    int p=hsh%SIZ; for(int i=head[p];i;i=nxt[i])
    if(ver[i]==hsh) return true; return false;
}
```
这样可以在最大程度避免哈希碰撞的情况下减少了空间损耗。

### 算复杂度

虽然好像枚举了一遍$k$，又枚举了每个块，但是时间复杂度是$\sum\limits_{i=1}^{N}\left\lfloor\dfrac{N}{i}\right\rfloor\le N \log N$，近似为$\mathcal O(N \log N)$，可以通过本题。

用哈希表替代$\text{map}$，有个好处就是时间极短，在$\text{171ms}$就可以通过本题。是所有不开$\rm O2$的程序中较快的程序。最大的点也只需要$\rm 60+ms$。

~~开$\sout{\rm{O2}}$被$\sout\text{map}$吊打，我也很无奈呀~~


## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
typedef unsigned long long ULL;
const int SIZ =999997,MAXN=2e5+3;
int head[SIZ+3],nxt[SIZ+3],tot;ULL ver[SIZ+3];
void add(int u,ULL v){ver[++tot]=v,nxt[tot]=head[u],head[u]=tot;}
ULL seed[MAXN]={19260817},pre[MAXN],suf[MAXN];
ULL getA(int l,int r){return pre[r]-pre[l-1]*seed[r-l];}
ULL getB(int l,int r){return suf[l]-suf[r+1]*seed[r-l];}
bool fnd(ULL hsh){
    int p=hsh%SIZ; for(int i=head[p];i;i=nxt[i])
    if(ver[i]==hsh) return true; return false;
}
int P[MAXN],vis[MAXN*2],res[MAXN],cnt,flg,top,ans,n;
int main(){
    n=qread(); up(1,n,i) P[i]=qread();
    up(1,n,i) seed[i]=seed[i-1]*seed[0];
    up(1,n,i) pre[i]=pre[i-1]*seed[0]+P[i];
    dn(n,1,i) suf[i]=suf[i+1]*seed[0]+P[i];
    up(1,n,i){
        up(1,cnt,i) head[vis[i]]=0; tot=cnt=flg=0;
        if(n/i<ans) break;
        for(int j=1;i*j<=n;++j){int l=(j-1)*i+1,r=j*i;
            ULL wA=getA(l,r),wB=getB(l,r);
            if(!(fnd(wA)||fnd(wB))){
                add(wA%SIZ,wA),add(wB%SIZ,wB),++flg;
                vis[++cnt]=wA%SIZ,vis[++cnt]=wB%SIZ;
            }
        }
        if(flg==ans) res[++top]=i; else if(flg<ans) continue;
        else top=0,ans=flg,res[++top]=i;
    }
    printf("%d %d\n",ans,top);
    up(1,top,i) printf("%d ",res[i]); puts("");
    return 0;
}
```

---

## 作者：小塘空明 (赞：2)

~~绝了，我随口向老师讲了几道hash水题，老师隔天就放出来给学弟们考了233~~

参考了claris的讲解。

暴力枚举k。对于每个k，一共有⌊n/k⌋个子串，这个的和值是调和级数，复杂度约等于(nlogn).

正向反向预处理一遍，每次求hash值取正反hash值中的较小值。在hash表中查找是否已经出现过了。

但我们发现因为要针对多个长度k进行多次hash，将数组清空会浪费大量时间。所以用vis数组表示当前位的时间，当前位vis数组更新时将其head设为0即可，这样就可以忽略之前进行的操作从而避免清空数组了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<queue>
using namespace std;
typedef long long ll;
const int N=200010,P=2333333,D=1000173169,M=1048575;
int n,i,j,tot,head[M],ver[M],next[M],pow[N],a[N],pre[N],suf[N],val[N],ans,cnt,now,vis[M+1];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline int hash(int l,int r){
	return min((ll)(pre[r]-(ll)pre[l-1]*pow[r-l+1]%D+D)%D,(ll)(suf[l]-(ll)suf[r+1]*pow[r-l+1]%D+D)%D);
}
inline bool ins(int v){
	int u=v&M;
	if(vis[u]<i) vis[u]=i,head[u]=0;
	for(int s=head[u];s;s=next[s]) if(ver[s]==v) return 0;
	++tot;next[tot]=head[u];head[u]=tot;ver[tot]=v;
	return 1;
}
int main(){
	n=read();pow[0]=1;
	for(i=1;i<=n;i++){a[i]=read();}
	for(i=1;i<=n;i++){pow[i]=(ll)((ll)pow[i-1]*P)%D;}
	for(i=1;i<=n;i++){pre[i]=(ll)((ll)pre[i-1]*P+a[i])%D;}
	for(i=n;i>=1;i--){suf[i]=(ll)((ll)suf[i+1]*P+a[i])%D;}
	for(i=1;i<=n;i++){
		for(tot=0,j=i;j<=n;j+=i){
			if(ins(hash(j-i+1,j))) val[i]++;
		}
	}
	for(i=1;i<=n;i++) if(val[i]>ans) ans=val[i],cnt=1;else if(val[i]==ans) cnt++;
	printf("%d %d\n",ans,cnt);
	for(i=1;i<=n;i++){
		if(val[i]==ans){
			printf("%d ",i);
		}
	}
	return 0;
}
```





---

## 作者：一只书虫仔 (赞：1)

#### Description

> 给定一个长度为 $n$ 的序列 $a_i$，求所有满足要求的 $k$ 使得将 $a_i$ 分为 $\lfloor\frac n k\rfloor$ 段 $[1,k],[k+1,2k],\cdots,[(\lfloor\frac n k\rfloor -1) \times k,\lfloor\frac n k\rfloor \times k]$，使得这 $\lfloor\frac n k\rfloor$ 段中不同的子序列数量最多，其中 $1,2,3=3,2,1$（翻转后序列相同）。

#### Solution

哈希水题。

直接从暴力开始考虑，枚举 $k \in [1,n]$ 做子序列长度，再枚举左端点 $i$，每次用哈希进行比较，具体细节就是对哈希值建立一个 map，意义就是对应哈希值是否有区间与之对应，然后每次没有重复的就更新答案，统计完一次 $k$ 之后再统计一下答案，就没了？就没了。

~~哈哈哈草。~~ 我们来分析一下复杂度，外层循环是 $\mathcal O(n)$ 的，内层循环是 $\mathcal O(\ln n)$ 的（如果不明白可以看底下的代码细节），预处理哈希也就 $\mathcal O(n)$，最多带个 map 的 $\log$，就没了。

最后说一下翻转算同一序列的处理方式，就正反都来一遍哈希，然后统计哈希值时正反两端同时操作即可。

#### Code

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const ull P = 1000000007;
int n;
int a[200010];
ull h1[200010];
ull h2[200010];

map<ull, bool> mp;

ull binpow (ull b, ull p) {
	ull res = 1;
	while (p > 0) {
		if (p & 1)
			res = res * b;
		b = b * b;
		p >>= 1;
	}
	return res;
}

ull getHash1 (int l, int r) {
	return h1[r] - h1[l - 1] * binpow(P, r - l + 1);
}

ull getHash2 (int r, int l) {
	return h2[l] - h2[r + 1] * binpow(P, r - l + 1);
}

int answer[200010];
int cnt[200010];

int main () {
	scanf("%d", &n);
	int ans = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) h1[i] = h1[i - 1] * P + a[i];
	for (int i = n; i >= 1; i--) h2[i] = h2[i + 1] * P + a[i];
	for (int k = 1; k <= n; k++) {
		mp.clear();
		int C = 0;
		for (int i = 1; i + k - 1 <= n; i += k) {
			ull gh1 = getHash1(i, i + k - 1);
			ull gh2 = getHash2(i + k - 1, i);
			if (mp.count(gh1) || mp.count(gh2)) continue;
			else mp[gh1] = true, mp[gh2] = true, C++;
		}
		ans = max(ans, C);
		answer[k] = C;
	}
	int A = 0;
	for (int i = 1; i <= n; i++)
		if (answer[i] == ans)
			cnt[++A] = i;
	printf("%d %d\n", ans, A);
	for (int i = 1; i <= A; i++) printf("%d ", cnt[i]); 
	return 0;
}
```

---

## 作者：斜揽残箫 (赞：1)

###【思路分析】

都标着 $Hash$ 的标签，所以一般要用 $Hash$ 做~~瞎编中~~；
此方法极其暴力，但是至少我 $AC$ 了。

**总体思路** : 
可以求这 $n$ 个数的**前后缀 $Hash$值**，之后从每 $1$ 个分为一段到每 $n - 1$ 个分为一段，依次进行判断。

因为题目中说 ： **子串都是可以反转的** ，所以首先求前后缀 $Hash$ 值，后缀 $Hash$ 值就是把前缀 $Hash$ 值的求法反过来。

**【Code】**
```cpp
void prepare()//前后缀Hash值和进制。 
{
	po[0] = 1;
	for(int i = 1;i <= n;i ++) {//进制
		po[i] = po[i - 1] * p;
	}
	for(int i = 1;i <= n;i ++) {
		Hash_z[i] = Hash_z[i - 1] * p + s[i];//前缀Hash值
	}
	for(int i = n;i >= 1;i --) {
		Hash_f[i] = Hash_f[i + 1] * p + s[i];//后缀Hash值
	}
	return;
}
```
如何来求一个子串的 $Hash$ 值 ：

如果我们已知字符串 $S$ 的 $Hash$ 值是 $H(S)$ ，字符串 $S + T$ 的 $Hash$ 值是 $H(S + T)$ ，那么字符串 $T$ 的 $Hash$ 值就是 

$$H(T) = (H(S +  T) - H(S) * p^{length(T)})\ mod\ M$$

根据这个性质就可以进行运算。

所以在这个题目中前缀 $Hash$ 值可以 $$Hash[k] = Hash[i] - Hash[i - k] * power[k]$$

后缀 $Hash$ 值 $$Hash[k] = Hash[i - k + 1] - Hash[i + 1] * power[k]$$

之后就开始进行对每次分割的计算，对每次的结果进行比较和储存，得出答案，但是，我试了一下，发现 $TLE$ 了两个点 第七个和第九个 (其实吸氧也能 $AC$ )。

于是开始了我们的剪枝之路，发现了两个规率 ： 

1. 因为存的是正反两个子串，所以再判重的时候只需判断前缀 $Hash$ 是否相等即可，优化 $0.1$ 秒。
2. 对于每一个求出的答案，如果在后面的枚举中可分的段数还比已知答案要小，肯定不是最优解，所以直接排除即可，优化 $0.69$ 秒。

之后我也想不出什么可以优化的方法了，吸了口小氧就过去了，最后不吸氧的情况下是 $1.5$ 秒(第九个点超时)，吸了氧是 $339ms$ 。（ $STL$ 的常数太大了，用数组来模拟时间要少）。

-----
#### 【Code】
```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<map>
#include<vector>
#include<set>
#define ull unsigned long long
#define ll long long
#define M 1000010
#define N 1010
#define INF 0x3f3f3f3f
using namespace std;
const int p = 10007;
/*================================================*/

int n;
int s[M];
ull Hash_z[M], Hash_f[M], po[M];;//正Hash值 ，反Hash值，进制
int cnt;//计算有几个最优解
int ans_cnt;//看可分为几段不同的值
vector<ull> qp;//储存每次分割的答案
int maxn = -1e5;//计算最终的可分的最大的段数
vector<int> ans;//储存每个最优解
int m; //剪枝用


/*================================================*/

inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void prepare()//前后缀Hash 值和进制位 
{
	po[0] = 1;
	for(int i = 1;i <= n;i ++) {
		po[i] = po[i - 1] * p;
	}
	for(int i = 1;i <= n;i ++) {
		Hash_z[i] = Hash_z[i - 1] * p + s[i];
	}
	for(int i = n;i >= 1;i --) {
		Hash_f[i] = Hash_f[i + 1] * p + s[i];
	}
	return;
}

bool check(int x)//判断函数，判断是否有这个子串
{
	for(int i = 0;i <qp.size(); i ++) {
		if(qp[i] == x) return false;
	}
	return true;
}

void solve(int k)
{	
	ans_cnt = 0;
	for(int i = k;i <= n;i += k) {
		int sum_z = Hash_z[i] - Hash_z[i - k] * po[k];
		//这个子串前缀Hash值
		int sum_f = Hash_f[i - k + 1] - Hash_f[i + 1] * po[k];//后缀
		if(check(sum_z)) {//判断
			qp.push_back(sum_z);
			ans_cnt++;//累加可分的段数
			//if(check(sum_f)) //剪枝 1 ,效果如上
			qp.push_back(sum_f);
		}
	}
	if(maxn == ans_cnt) {//当已知的最优解和新求出的解相同时
		ans.push_back(k);//记录k 值 
		cnt++;//最优解个数++
	} else if(maxn < ans_cnt) {//又新求出更优的解
		ans.clear();//清空原来的答案序列
		ans.push_back(k);//添加解
		maxn = ans_cnt;
		cnt = 1; 
	}
	if(ans_cnt != 0) {
		m = min(m,n / ans_cnt);//剪枝 2 效果如上
	}
	qp.clear();//多次分割记得清空
}
/*=================================================*/

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = read();
	for(int i = 1;i <= n;i ++) {
		s[i] = read();
	}
	prepare();
	m = n;
	for(int i = 1;i <= m;i ++) solve(i);
	printf("%d %d\n",maxn,cnt);
	for(int i = 0;i <ans.size();i ++) printf("%d ",ans[i]);//输出
	return 0;
}
```
**小错误**

取底数的时候要取个大点的值(或者写双 $Hash$)，利用 $unsigned$ $long$ $long$ 的自然溢出来判断，否则很容易和我一样，用 $31$ 来做进制，使得 $WA$ 声一片。




---

## 作者：爷，无限霸气 (赞：1)

~~一道很好的哈希题！~~

## 一：暴力验证

从一枚举到n，逐一验证。

时间复杂度约为:n(n/1+n/2+...+n/n)约等于$n^2logn$,而此题的$n<=2e5$
早已不知道爆到哪里去了

## 二：哈希值的判重

代码（我们取2^64+1为模数，溢出就相当于作模了）：

```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
#define Maxn 200005
const ll p=1e9+7;
using namespace std;
ll read()
{
	ll r=0,f=1;char c=getchar();
	while((c<'0'||c>'9')&&(c!='-')) c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(c>='0'&&c<='9') r=r*10+c-'0',c=getchar();
	return r*f;
}
ll n,s1[Maxn],s2[Maxn],mi[Maxn],a[Maxn],ans[Maxn],cnt,num;
map<ll,bool> pd;
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	mi[0]=1;
	for(int i=1;i<=n;i++) mi[i]=mi[i-1]*p;//预处理p的k次方
	for(int i=1;i<=n;i++) s1[i]=s1[i-1]*p+a[i];//双哈希，s1,s2,这里是顺着一遍哈希
	for(int i=n;i;i--) s2[i]=s2[i+1]*p+a[i];//反过来哈希
	for(int i=1;i<=n;i++)
	{
		if(n/i<num) break;//总段数如果比答案还小，就不用找了，相当于一个剪枝
		ll c=0;//c-》当前找到的长度下找到的重复段数
		pd.clear();
		for(int j=i;j<=n;j+=i)//j是每一段的终点，起点是j-i+1
		{
			if(c+(n-j+i)/i<num) break;//当前找到的+剩余的比答案还小，也不用找了
			ll t1=s1[j]-s1[j-i]*mi[i];
			if(pd[t1]) continue;
			ll t2=s2[j-i+1]-s2[j+1]*mi[i];
			++c;
			pd[t1]=pd[t2]=true;
		}
		if(c==num) ans[++cnt]=i;//存路
		else if(c>num) cnt=0,num=c,ans[++cnt]=i;//重新开始
	}
	printf("%lld %lld\n",num,cnt);
	for(int i=1;i<=cnt;++i) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：子归 (赞：1)

### 后缀数组smg？抱歉蒟蒻只会普通Hash
这道题要求选取子串如果反着也被选了的话就不能选,所以很容易想到正反两遍hash.  
在这里有很多方式判重，比如lower_bound，链表啊，我在此处使用的是链表.
### 优化
可以考虑提高代码效率.  
比如说如果当前已经分配了的子串加上之后能够得到的最大子串都没有已知的最多子串多，那么就没必要继续做了。  
每次只选择可能大于最大值的k去做.
具体实现也不是特别难，可以对比看一下.
#### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
/*
    正着一遍倒着一遍哈希.
    每次去一个就将两个哈希都存进去.
*/
#define ull unsigned long long
using namespace std;
const int maxn=200005,p=100007;
int n,maxx,cnt,k;
int a[maxn],b[maxn],head[p+5];
ull h1[maxn],h2[maxn],bas[maxn];
struct Kano{
	int nxt;
	ull val;
}kano[maxn];
ull get(int l,int r){
	return min(h1[r]-h1[l-1]*bas[r-l+1],h2[l]-h2[r+1]*bas[r-l+1]);
}
void add(ull x,int y){
	kano[++cnt].val=x;
	kano[cnt].nxt=head[y];
	head[y]=cnt;
}
bool check(ull x){
	int y=x%p;
	for (int i=head[y];i;i=kano[i].nxt){
		if (kano[i].val==x) return 0;
	}
	add(x,y);
	return 1;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) h1[i]=h1[i-1]*p+a[i];
    for(int i=n;i>=1;i--) h2[i]=h2[i+1]*p+a[i];
    bas[0]=1;
    for(int i=1;i<=n;i++)bas[i]=bas[i-1]*p;
    for(int i=1;i<=n;i++){
    	if(n/i<maxx) continue;
    	int num=0;
    	for(int j=1;j<=n;j+=i){
    		if(j+i-1>n) break;
    		if(num+(n-j+1)/i<maxx) break;//剪枝？
    		if(check(get(j,j+i-1))) num++;
		}
		if(num>maxx){
    		maxx=num;
    		k=1;
    		b[k]=i;
		}else if(num==maxx) b[++k]=i;
	}
	printf("%d %d\n",maxx,k);
	for (int i=1;i<=k;i++)
	printf("%d ",b[i]);
	return 0;
}
```


---

## 作者：Rainsleep (赞：0)

**前置芝士：字符串哈希、$\text{set}$**

枚举长度 $k$，暴力检测不相同的串数。判重时用字符串哈希和 $\text{set}$ 维护就行。

具体来说，我们前后做一遍，各维护出前后缀的哈希值，结合求子段哈希值的柿子就不难得出一个字串翻转前和翻转后的哈希值，插到 $\text{set}$ 就行了。

+ 前缀哈希求长度为 $k$ 子段哈希值的柿子:
$$hash(l,r) = hsh[r] - hsh[(r - k - 1) + 1] \times p^{k}$$
$$hash(l,r) = hsh[r] - hsh[r - k] \times p ^ k$$
+ 后缀哈希求长度为 $k$ 子段哈希值的柿子：
$$Ohash(l,r) = Ohsh[r - k + 1] - Ohsh[r + 1] \times p^k$$

$\text{set}$ 维护时不妨用前后缀哈希值相乘的结果插入集合中。

剩下的就是代码啦：
```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N = 2e5 + 10, P = 13331;
int n, a[N], maxx = INT_MIN, res[N], cnt = 0;
typedef unsigned long long ull;
ull p[N], hsh[N], Ohsh[N];

inline int get(int l, int r)
{
	return hsh[r] - hsh[l - 1] * p[r - l + 1];
}

inline int Oget(int l, int r)
{
	return hsh[l] - hsh[r + 1] * p[r - l + 1];
}

signed main()
{
	scanf("%lld", &n);
	p[0] = 1;
	for(int i(1);i <= n; ++ i)
	{
		scanf("%lld", &a[i]);
		hsh[i] = hsh[i - 1] * P + a[i];
		p[i] = p[i - 1] * P;
	}
	for(int i(n);i >= 1; -- i)
		Ohsh[i] = Ohsh[i + 1] * P + a[i];
	set<int>s;
	for(int i(1);i <= n; ++ i)
	{
		int sum = 0;
		s.clear();
		for(int j(i);j <= n; j += i)
		{
			int val = hsh[j] - hsh[j - i] * p[i];
			int Oval = Ohsh[j - i + 1] - Ohsh[j + 1] * p[i];
			if(s.count(val * Oval))
				continue;
			s.insert(val * Oval);
			++ sum;
		} 
		if(sum > maxx)
			cnt = 0, maxx = sum, res[++ cnt] = i;
		else if(sum == maxx)
			res[++ cnt] = i;
	}
	printf("%lld %lld\n", maxx, cnt);
	for(int i(1);i <= cnt; ++ i)
		printf("%lld ", res[i]);
	return 0;
}
```

---

## 作者：Bulyly (赞：0)

### 前言
取进制底数一定要注意，因为这东西真的很玄学。

### 解析
- 不难看出这道题考察的是哈希，用于判断是否是不同的段。该段对答案有贡献，当且仅当该段本身序列与它的翻转序列都是第一次被遍历。然后将原序列与翻转序列都记录。

- 对于答案的求解，从小到大枚举 $k$，令 $k$ 的贡献为 $x$，将 $k$ 加入不同 的 $k$ 贡献皆为 $x$ 的集合 。

- 总时间复杂度 $O(n\log n)$。

下附代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector> 
using namespace std;

typedef unsigned long long ULL;
const int N=2e5+10,P1=19260817,P2=2e5+1,Mod1=1e9+9,Mod2=1e9+7;
int p[3][N],pp[3][N],hh[5][N],h[5][N];
int a[N],b[N];
int n; 
int ans[N],cnt;
map<int,int> S1;
int idx1;
inline int read()
{
	int ans=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			sign=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*sign;
}

int query1(int l,int r,int type)
{
	return ((h[type][r]-1LL*h[type][l-1]*p[1][r-l+1])%Mod1+Mod1)%Mod1;
}

int main()
{
	n=read();
	for(int i=1;i<=n;++i)  a[i]=read(),b[n-i+1]=a[i];
	pp[1][0]=p[1][0]=pp[2][0]=p[2][0]=1;
	for(int i=1;i<=n;++i)
	{
	   p[1][i]=((1LL*p[1][i-1]*P1))%Mod1;
//	   pp[1][i]=(pp[1][i-1]*P2+Mod1)%Mod1;
//	   p[2][i]=(p[2][i-1]*P1)%Mod2;
//	   pp[2][i]=(pp[2][i-1]*P2)%Mod2;
	   
	   h[0][i]=((1LL*h[0][i-1]*P1+a[i]))%Mod1; 
	   h[1][i]=((1LL*h[1][i-1]*P1+b[i]))%Mod1;
	}
	int res=0;
	for(int k=1;k<=n;++k)
	{
		int tot=0;
		S1.clear();
		for(int i=1;i+k-1<=n;i+=k)
		{
		   int j=i+k-1;
		   int t1=query1(i,j,0),t2=query1(n-j+1,n-i+1,1);
		   int tt=min(t1,t2);
		   if(!S1.count(tt))  
		   {
		   	 ++tot;
		   	 S1[tt]=1;
		   }
		}
		if(res<tot)  res=tot,cnt=0,ans[++cnt]=k;
		else if(res==tot)  ans[++cnt]=k;
	}
	
	printf("%d %d\n",res,cnt);
	
	for(int i=1;i<=cnt;i++)  printf("%d ",ans[i]);
	
	return 0;
}
```
完结撒花~


---

## 作者：naroanah (赞：0)

## 分析题目：
数据范围为 $2 \times 10^5$，显然时间复杂度为 $O(n \log n)$。

容易想到，我们必须枚举每一个 $k$ 值和它的子串，而子串共有     $\sum\limits_{k=1}^n\left\lfloor\dfrac{n}{k}\right\rfloor$ 个，展开后可以化为调和级数，而调和级数近似于 $\log n$ ,所以枚举的复杂度即为 $O(n \log n)$。

查询和判重应该怎么做呢？

往往这类字符串题，都可以使用字符串哈希这一利器，把查询优化为 $O(1)$。

对于这道题，可以进行正反两次哈希，来处理子串反转的情况。

判重可以使用哈希表，不过STL里面有自带的 set 和 map，懒人必备。

如果用STL的话，时间复杂度应为 $O(n \log n \log n)$，仍然可以通过本题 ~~（开了O2似乎跑的飞快）~~。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
unsigned int a[200010];
const int M=1145141;
int num[200010],len;
unsigned int hash_front[200010],hash_back[200010],ppow[200010];
void init(){
	for(int i=1;i<=n;i++) hash_front[i]=hash_front[i-1]*M+a[i];
	for(int i=n;i>=1;i--) hash_back[i]=hash_back[i+1]*M+a[i];
	ppow[0]=1;
	for(int i=1;i<=n;i++) ppow[i]=ppow[i-1]*M;
}
unsigned int Hash(int l,int r){
	unsigned a=hash_front[r]-hash_front[l-1]*ppow[r-l+1],b=hash_back[l]-hash_back[r+1]*ppow[r-l+1];
	return a*b;
}
set<unsigned int> st;
int check(int k){
	int ans=0;
	for(int i=k;i<=n;i+=k){
		unsigned int t=Hash(i-k+1,i);
		if(!st.count(t)){
			st.insert(t);
			ans++;
		}
	}
	return ans;
}
int tot;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	init();
	for(int i=1;i<=n;i++){
		st.clear();
		int t=check(i);
		if(tot<t){
			num[1]=i;
			len=1;
			tot=t;
			continue;
		}
		if(tot==t){
			num[++len]=i;
		}
	}
	printf("%d %d\n",tot,len);
	for(int i=1;i<=len;i++) printf("%d ",num[i]);
	return 0;
}
```


---

