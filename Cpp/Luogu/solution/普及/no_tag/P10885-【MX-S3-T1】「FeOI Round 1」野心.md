# 【MX-S3-T1】「FeOI Round 1」野心

## 题目背景

原题链接：<https://oier.team/problems/S3A>。

---

![](bilibili:BV1eZ4y1w7n1)

## 题目描述

给出一个 $1 \sim n$ 的排列 $p$，询问存在多少个数 $i$（$1 \le i <n$）满足 $[p_1,p_2,\cdots,p_i]$ 和 $[p_{i+1},p_{i+2},\cdots,p_n]$ 排序后都是等差数列。

## 说明/提示

**【样例解释 #1】**

第一组：三种拆分为 $[1,3,2][4]$，$[1,3][2,4]$，$[1][3,2,4]$。

第二组：三种拆分为 $[1][5,3,2,4]$，$[1,5][3,2,4]$，$[1,5,3][2,4]$。

**【样例解释 #2】**

第一组：两种拆分为 $[2,1][4,3,6,5]$，$[2,1,4,3][6,5]$。

第二组：每种拆分都是合法的。

第三组：每种拆分都是合法的。

第四组：不存在拆分方案，故没有方案合法。

**【数据范围】**

**本题开启捆绑测试。**

设 $\sum n$ 为单个测试点内所有的 $n$ 之和。

对于 $100\%$ 的数据，$1 \le T \le 10^5$，$1 \le n \le 10^6$，$1 \le \sum n \le 2 \times 10^6$，保证 $p$ 是排列且 $1 \le p_i \le n$。

| 子任务编号 | $n $ | $\sum n $ | 分数 |
| :-: | :-: | :-: | :-: |
| $1$ | $\le 10^3$ | $\le 5\times 10^3$ | $30$ |
| $2$ | $\le 10^5$ | $\le 5\times 10^5$ | $30$ |
| $3$ | $\le 10^6$ | $\le 2\times 10^6$ | $40$ |

**请使用较快的输入输出方式。**

**新增子任务 4 为 hack 数据，分值为 $\boldsymbol{0}$。**

## 样例 #1

### 输入

```
2
4
1 3 2 4
5
1 5 3 2 4```

### 输出

```
3
3```

## 样例 #2

### 输入

```
4
6
2 1 4 3 6 5
6
1 2 3 4 5 6
3
1 3 2
1
1```

### 输出

```
2
5
2
0```

## 样例 #3

### 输入

```
6
2
1 2
20
16 2 10 18 4 6 8 20 14 12 3 9 17 13 1 15 7 11 19 5
9
3 4 1 5 2 6 7 8 9
10
1 3 2 4 7 6 5 8 10 9
13
5 7 3 11 1 9 13 6 10 4 2 8 12
5
1 2 3 4 5```

### 输出

```
1
1
4
5
1
4```

# 题解

## 作者：Rigel (赞：18)

## 思路

在一个排序后为等差数列的数列中，定义 $l$ 为数列长度，$d$ 为**可能**的数列公差。

试分析以 $i$ 为断点形成的 $2$ 个排序后为等差数列的数列中 $d$ 与 $l$ 的关系。

先定义 $l$ 为“特殊的”，当且仅当 $l=\begin{cases}
\lfloor\frac{n}{2}\rfloor\ 或\ \lfloor\frac{n}{2}\rfloor+1&n=2x+1,\ x\in\mathbb{N+},\\
\frac{n}{2}&n=2x,\ x\in\mathbb{N+}.
\end{cases}$

存在如下 $3$ 种情况：

- 当 $l \in [1,2]$ 时，$d \in [1,n-1]$。
  
- 当 $l \in [3,n]$ 时，$d=\begin{cases} 
1\ 或\ 2& l\ 为“特殊的”,\\
1 & \mathop{\operatorname{otherwise}}.\\
\end{cases}$

再定义 $\mathop{f_i}\limits_{i \in [1,n]}=[\ [p_1,p_2,\cdots,p_i] 为等差数列]$，$\mathop{g_i}\limits_{i \in [1,n]}=[\ [p_{i},p_{i+1},\cdots,p_n]为等差数列]$。

注意到，$\forall i\in [1,n)$，$f_i=1\  \land \ g_{i+1}=1$，则 $i$ 合法，因此求出 $f_i$ 与 $g_i$ 即可。

下面以求出 $f_i$ 为例，此时 $l=i$。

正难则反，我们设出 $d$ 的值并检验 $d$ 的合法性，若 $d$ 合法，则 $f_i=1$。

显然，$l \le 2$ 时 $f_i=1$，不再赘述。

当 $l > 2$ 时，

  - 先设 $d=1$。若 $l=\mathop{\operatorname{max}}(p_1,p_2,\cdots,p_i)-\mathop{\operatorname{min}}(p_1,p_2,\cdots,p_i)+1$，则 $d$ 合法。

  - 若 $l$ 为“特殊的”，再设 $d=2$，此时遍历数列 $[p_1,p_2,\cdots,p_i]$ 判断 $d$ 的合法性（详情见代码）。

不难发现，求 $f_i$ 的过程中，“遍历数列”的操作至多进行 $2$ 次，~~不会爆时间~~。

求 $g_i$ 时，$l=n-i+1$，过程同理，注意顺序。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x7fffffffffffffff
#define _max(a,b) ((a)>(b)?(a):(b))
#define _min(a,b) ((a)<(b)?(a):(b))
#define maxn 2000010
using namespace std;
int t,n,a[maxn],vis[maxn],f[maxn],g[maxn],ans;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
signed main(){
	t=read();
	while(t--){
		n=read(),ans=0;
		for(int i=1;i<=n;i++)a[i]=read(),vis[i]=0;
		if(n==1){printf("0\n");continue;}
		//求 f[i] 
		int cnt=0,minn=INF,mx=-INF;
		for(int i=1;i<=n;i++){
			vis[a[i]]=1;
			if(a[i]>=mx)mx=a[i];
			if(a[i]<=minn)minn=a[i];
			if(mx-minn+1==i||i<=2){f[i]=1;continue;}	
			if(((n&1)&&(i==(n>>1)||i==(n>>1)+1))||(!(n&1)&&(i==(n>>1)))){
				int k=((mx-minn)>>1)+1;
				if(k!=i){f[i]=0;continue;}
				int op=0;
				for(int j=minn;j<=mx;j+=2)if(!vis[j]){op=1;break;}
				f[i]=op^1;
			}else f[i]=0;
		}
		//求 g[i] 
		cnt=0,minn=INF,mx=-INF;
		for(int i=1;i<=n;i++)vis[i]=0;		
		for(int i=n;i>=1;i--){
			vis[a[i]]=1;
			if(a[i]>=mx)mx=a[i];
			if(a[i]<=minn)minn=a[i];
			if(mx-minn+1==(n-i+1)||(n-i+1)<=2){g[i]=1;continue;}	
			if(((n&1)&&((n-i+1)==(n>>1)||(n-i+1)==(n>>1)+1))||(!(n&1)&&(n-i+1)==(n>>1))){
				int k=((mx-minn)>>1)+1;
				if(k!=(n-i+1)){g[i]=0;continue;}
				int op=0;
				for(int j=minn;j<=mx;j+=2)if(!vis[j]){op=1;break;}
				g[i]=op^1;
			}else g[i]=0;
		}
		for(int i=1;i<=n-1;i++)if(f[i]&&g[i+1])ans++;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：lizhous (赞：10)

首先注意到是排列，所以值域上每个数属于且仅属于一个等差数列。

### subtask0

枚举 $i$，对两边排序并判断是否是等差数列。

### subtask1

枚举 $i$，使用带根号或 $\log$ 算法快速判断两边是否是等差数列。

### subtask2

有多种做法，本题解主要讲解一种较好实现的做法。

令两个等差数列的公差为 $d1,d2$ 且 $d1\le d2$。

假设我们确定 $d1,d2$，方便观察合法等差数列的情况。

当 $d1=1$ 且 $d2=1$ 时，两个等差数列把值域分成两半。维护前缀最大最小值容易判断。

当 $d1=1$ 且 $d2\neq1$ 时，此时值域被其中一个等差数列删去中间一段，前后剩余都是公差为 $1$ 的等差数列，则要满足剩下的数能组成等差数列且公差不为 $1$，前后必然只能剩余一个数。维护前缀最大最小值容易判断。

当 $d1=2$ 时，此时值域被其中一个等差数列间隔的删去，剩余的必然也是一个公差为 $2$ 的等差数列。维护前缀奇偶性容易判断。

当 $d1>2$ 时，此时 $1$ 和 $2$ 被归入不同的等差数列作为首项，而 $3$ 无法被归入任何一个等差数列，故不存在解。

于是简单判断即可。时间复杂度 $O(n)$。

---

## 作者：Hoks (赞：6)

## 前言
T1 就做复杂做法，直接硬控自己。
## 思路分析
我们考虑下怎么判定一个数列是等差数列。

设数列为 $a_1,a_2,\dots,a_n$，我想到的判定方式即为：
$$\min(a_i-a_j)\cdot (n-1)=\max(a_i-a_j)$$

其中，$i\not=j,i\in[1,n],j\in[1,n]$。

然后就是给这玩意加数带修了。

右边的东西很好维护，实时取 $\max,\min$ 即可。

$n-1$ 也很好维护，直接实时计算就可以了。

最难搞的是 $\min(a_i-a_j)$，我们需要找到新加入那个数左右两边最近的数进行更新。

考虑大力上一个 `set` 猛猛做就可以拿到 $60$ 分。

接着考虑优化掉这个 `set`。

因为我们加数的顺序是固定的，所以当一个数加入的时候，他的左右最近的数显然是固定的。

考虑正难则反，因为加的时候固定下来了，那么反过来，删到这个点的时候他的左右端点也就固定了。

所以我们倒序删数，设 $i$ 的左右端点为 $l_i,r_i$，那么 $l_i$ 的右端点就变为 $r_i$，$r_i$ 的左端点就变为 $l_i$。

然后按上面的做法做，插入一个新的数的时候直接和他的左右端点算下贡献就行了。

因为这题要满足左右两边都是等差数列，所以左右跑两遍就行了。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10,M=3,INF=0x3f3f3f3f,mod=1e9+7;
int n,a[N],b[N],c[N],d[N],l[N],r[N],e[N],ans[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='?'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    int mx=0,mn=INF,res=0;
    n=read();for(int i=1;i<=n;i++) a[i]=read(),l[i]=i-1,r[i]=i+1,ans[i]=1;
    for(int i=1;i<=n;i++)
    {
        mx=max(mx,a[i]),mn=min(mn,a[i]);
        d[i]=mx-mn;
    }mx=0,mn=INF;
    for(int i=n;i>=1;i--)
    {
        mx=max(mx,a[i]),mn=min(mn,a[i]);
        c[i]=mx-mn;
    }
    for(int i=1;i<=n;i++) r[l[a[i]]]=r[a[i]],l[r[a[i]]]=l[a[i]];e[n+1]=INF;
    for(int i=n;i>=1;i--)
    {
        e[i]=e[i+1];
        if(l[a[i]]>0) e[i]=min(e[i],a[i]-l[a[i]]);
        if(r[a[i]]<=n) e[i]=min(e[i],r[a[i]]-a[i]);
    }
    for(int i=1;i<n;i++){if(c[i+1]!=(n-i-1)*e[i+1]) ans[i]=0;l[i]=i-1,r[i]=i+1;}
    l[n]=n-1;r[n]=n+1;for(int i=n;i>=1;i--) r[l[a[i]]]=r[a[i]],l[r[a[i]]]=l[a[i]];e[0]=INF;
    for(int i=1;i<=n;i++)
    {
        e[i]=e[i-1];
        if(l[a[i]]>0) e[i]=min(e[i],a[i]-l[a[i]]);
        if(r[a[i]]<=n) e[i]=min(e[i],r[a[i]]-a[i]);
    }for(int i=1;i<n;i++) if(d[i]==(i-1)*e[i]) res+=ans[i];print(res),put('\n');
}
signed main()
{
    int T=read();while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：EricWan (赞：4)

这题比较显然，是一个小分讨，为了考虑到所有情况，我们可以想这样一个问题：

对于一个 $1$ 到 $n$ 的上升排列，选出一个等差子序列，使得它是反序列也是一个等差序列。

我们思考后发现，一共只有 $6$ 种情况：

+ 连续，从 $1$ 开始。

+ 连续，以 $n$ 结尾。

+ 所有奇数。

+ 所有偶数。

+ 除了 $1$ 和 $n$ 以外的所有数。

+ $1$ 和 $n$。

因此，我们遍历一遍输入数据，标记合法的 $i$ 最后统计即可 AC。

代码：
```cpp
cin >> n;
for (int i = 1; i <= n; i++) {
	cin >> a[i];
	s[i] = s[i - 1] + a[i] % 2;
}
if (n == 1) {
	cout << "0\n";
	continue;
}
if (n == 2) {
	cout << "1\n";
	continue;
}
if (n == 3) {
	cout << "2\n";
	continue;
}
int cnt = 0, even = n / 2, odd = n - n / 2;
if (s[even] ==   0) ans[even] = 1;
if ( s[odd] == odd)  ans[odd] = 1;
for (int i = 1; i < n; i++) {
	update(a[i]);
	if (query(i) == i || query(n - i) == 0) {
		ans[i] = 1;
	}
}
if (a[1] * a[2] == n && a[1] + a[2] == n + 1)
	ans[2] = 1;
if (a[n] * a[n - 1] == n && a[n] + a[n - 1] == n + 1)
	ans[n - 2] = 1;
for (int i = 1; i < n; i++)
	cnt += ans[i];
cout << cnt << endl;
```

---

## 作者：_sin_ (赞：3)

考虑怎么判定一个子串是不是等差数列。

类似于 P5278，我们判定等差数列要满足以下条件：
1. $\max-\min=(r-l)\times \text{相邻两数差的绝对值的gcd}$。
2. 区间 $[l,r]$ 内的数不重复。

由于是排列，所以第二个条件显然成立。

第一个条件的维护是简单的。

```cpp
#include<bits/stdc++.h>
using namespace std;

int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return f*x;
}

const int N = 1e6+5;
int T, n, a[N],b[N],c[N],pmx[N],pmn[N],smx[N],smn[N];
int pgcd[N],sgcd[N],ans;

void solve(){
	ans=0,n=read();for(int i=0;i<=n+1;i++)a[i]=0;
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i]-a[i-1];
	for(int i=n;i>=1;i--)c[i]=a[i]-a[i+1];
	pmx[1]=pmn[1]=a[1],smx[n]=smn[n]=a[n];pgcd[2]=b[2],sgcd[n-1]=c[n-1];
	for(int i=2;i<=n;i++)pmx[i]=max(pmx[i-1],a[i]),pmn[i]=min(pmn[i-1],a[i]);
	for(int i=3;i<=n;i++)pgcd[i]=__gcd(pgcd[i-1],b[i]);
	for(int i=n-1;i>=1;i--)smx[i]=max(smx[i+1],a[i]),smn[i]=min(smn[i+1],a[i]);
	for(int i=n-2;i>=1;i--)sgcd[i]=__gcd(sgcd[i+1],c[i]);
	for(int i=1;i<n;i++)
	if(pmx[i]-pmn[i]==(i-1)*abs(pgcd[i])&&smx[i+1]-smn[i+1]==(n-i-1)*abs(sgcd[i+1]))ans++;
	printf("%d\n",ans);
}

int main(){
	T=read();while(T--)solve();
	return 0;
}
```

---

## 作者：scc36 (赞：3)

[原题传送窗口](https://www.luogu.com.cn/problem/P10885)  
### 思路（暴力）
读完题后，很容易先想到一个的暴力。    
我们只需要枚举每一个（$1 \le i <n$）的 $i$，再找出 $[p_1,p_2,\cdots,p_i]$ 和 $[p_{i+1},p_{i+2},\cdots,p_n]$，对它们进行排序，再判断其是不是等差数列即可。  
于是我们就有了 30 分。
### 代码（暴力）  

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,v,s,da,o,i,j,dan,ou;
int a[1000001],b[1000001],f[1000001],c[1000001],d[1000001];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;v=0;
		for(i=1;i<=n;i++) cin>>a[i];
		for(i=1;i<n;i++){
			int fl=0,k,j;
			for(j=1;j<=i;j++)
				b[j]=a[j];
			sort(b+1,b+i+1);
			//找前面一段并排序 
			if(i!=1){
				s=b[2]-b[1];
				for(j=2;j<i;j++)
					if(b[j+1]-b[j]!=s){
						fl=1;
						break;
					}
			}
			if(fl==1) continue;
			 //判断是否为等差数列
			  
			for(j=i+1,k=1;j<=n;j++,k++)
				b[k]=a[j];
			k--;
			sort(b+1,b+k+1);
			//找后面一段并排序
			if(k!=1){
				s=b[2]-b[1];
				for(int j=2;j<k;j++)
					if(b[j+1]-b[j]!=s){
						fl=1;
						break;
					}
			}
			if(fl==1) continue;
			//判断是否为等差数列
			
			v++;//是等差数列，累加 
		}
		cout<<v<<"\n";
	}
}
```
### 思路
我们可以从等差数列的公差入手。   
假设前面一段公差为 1，也就是前面一段是一串连续的数字。不难发现，如果后面那段也是等差数列的话，它必须也是一串连续的数字。  
于是，我们可以将 $p$ 数组变成两段，使其满足题意。一段中的数字是 $1 \sim i$，另一段中的数字是 $i+1 \sim n$。当然，这两可以**反一反**。   
于是，我们有了**判定一**。   

---


然后，我们假设前面一段公差为 2，因此前面一段要么全是奇数，要么全是偶数。所以只有两种情况：“前一段全是奇数，后一段全是偶数”或“前一段全是偶数，后一段全是奇数”。    
为啥呢？？？   
~~你写不出不符合上面的条件又合法的串。~~    
如果前一段有一个奇数或偶数到了后一段，后面一段就会既有差值 2，又有差值 1，这就不是等差数列了~~  
于是，我们有了**判定二**。 

---

再想一想，如果当公差大于 2 时会发生什么？   
假设我们有一段六个数的 $p$，前一段公差为 3，假设前一段是 ${1,4}$，那么第二段就是 ${2,3,5,6}$，它不是一个等差数列。    
为啥呢？？？   
因为公差为 3，所以前一段每两个相邻的数之间就会有两个数多出来，就是上面的 ${2,3}$，它们的差值为一。   
但 3 和下一个两个数（也就是 ${5,6}$）插值就会达到 2。总结一下，当公差为 3 时，不可能有合法的 $i$ 存在。   
同理，当公差大于 3 时，也是不可能的。


---

做到这里，是不是已经万事大吉了？   
~~一听你这话就知道还没结束。~~   
来看样例一的第二组数据：$[1,5,3,2,4]$。   
样例解释中，它有一种分解方式：$[1,5][3,2,4]$。用上面的条件去看一看，这明明是错的！但它就是对的！！！   
研究一下，不难发现，这一串中，1 和 $n$ 是在一起的，且在最前面。相似的，它们也可以在最后面。   
于是，我们有了**判定三**。    


---

~~这样就没了？？？~~    
~~从目前的数据上来看没有别的可能了……~~  
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,v,s,da,o,i,j,dan,ou;
int a[1000001],b[1000001],f[1000001],c[1000001],d[1000001];
int main(){
	ios::sync_with_stdio(0);//输入输出的加速 
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		//清零 
		v=0;s=0;dan=ou=0;
		for(i=1;i<=n;i++) c[i]=0,f[i]=0,b[i]=0,d[i]=0;
		
		//特判一下（当时为啥要特判呢……） 
		if(n==1){        
			cin>>a[1];
			cout<<0<<"\n";
			continue; 
		}
		
		//判定二的前半部分…… 
		if(n%2==0) da=n/2,o=n/2;
		else da=n/2+1,o=n/2;
		
		
		for(i=1;i<=n;i++){
			cin>>a[i];
			b[a[i]]=i;d[a[i]]=n-i+1;
			
			//判定二 
			if(a[i]%2==0) ou++;
			else dan++;
			if(dan==da&&ou==0) c[i]=1;
			if(ou==o&&dan==0) c[i]=1;
		}
		
		//判定一 
		for(i=1;i<n;i++){
			s+=f[i];
			if(b[i]<=i) s++;
			else f[b[i]]=1;
			if(s==i) c[i]=1;
		}
		s=0;
		for(i=1;i<=n;i++) f[i]=0;
		for(i=1,j=n-1;i<n;i++,j--){
			s+=f[i];
			if(d[i]<=i) s++;
			else f[d[i]]=1;
			if(s==i) c[j]=1;
		}
		
		//判定三 
		if(a[1]==1&&a[2]==n) c[2]=1;
		if(a[1]==n&&a[2]==1) c[2]=1;
		if(a[n]==n&&a[n-1]==1) c[n-2]=1;
		if(a[n]==1&&a[n-1]==n) c[n-2]=1;
		//怎么这么大一坨…… 
		
		for(i=1;i<n;i++) v+=c[i];
		cout<<v<<"\n";
	}
}
```
搞定o(^▽^)o

---

## 作者：_H17_ (赞：3)

## 题目分析

考虑几种情况：

1. 前或者后 $i$ 个是 $1\sim i$（差是 $1$）；

2. 一半奇数、一半偶数（差是 $2$）；

3. 前、后两个是 $1,n$（特殊）。

第一类可以记录前后缀最大值，依次判断是否等于编号。

第二类直接判断前后一半是否奇偶性相同。

第三类特判即可，注意：$n=3$ 时这种包含了差是 $2$ 的情况。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e6+1;
int T,n,a[N],ans,maxv;
void Main(){
    cin>>n;
    ans=0,maxv=0;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    if(n==1){
        cout<<"0\n";
        return;
    }
    else if(n==2){
        cout<<"1\n";
        return;
    }
    for(int i=1;i<n;i++){
        maxv=max(maxv,a[i]);
        if(maxv==i)
            ans++;
        if(maxv==n)
            break;
    }
    maxv=0;
    for(int i=n;i>1;i--){
        maxv=max(maxv,a[i]);
        if(maxv==n-i+1)
            ans++;
        if(maxv==n)
            break;
    }
    int k=a[1]&1,t=0;
    for(int i=2;i<=n;i++)
        if((a[i]&1)==k);
        else{
            t=i-1;
            break;
        }
    if((k&&t==n/2+(n&1))||(!k&&t==n/2))
        ans++;
    if(n<=3)
        goto g;
    if((a[1]==1&&a[2]==n)||(a[1]==n&&a[2]==1)||(a[n-1]==1&&a[n]==n)||(a[n-1]==n&&a[n]==1))
        ans++;
    g:
    cout<<ans<<'\n';
    return;
}
int main(){
    for(cin>>T;T;--T)
        Main();
    return 0;
}
```

---

## 作者：CNS_5t0_0r2 (赞：3)

**update on 2024-8-20：修复公式的错误 + 修复代码使其能够通过 hack 数据。**

这是一个乱搞做法。

如果你用哈希做法做过[这题](https://www.luogu.com.cn/problem/P5278)，那么这题应该是秒杀的。

以前缀举例（后缀同理）：如何确定 $[p_1,p_2,\cdots,p_i]$ 能重排成等差数列？

首先肯定要确定公差。设 $[p_1,p_2,\cdots,p_i]$ 的最小值为 $Min$,最大值为 $Max$，它们分别对应等差数列的首项和末项，那么公差 $d = \frac{(Max - Min)}{i - 1}$（如果 $i - 1$ 不整除 $Max - Min$ 那么可以直接确定不能重排）。

设 $sq = \sum_{j = 1} ^ i p_j ^ 2$，那么应该有 $sq = \sum_{j = 0} ^ {i - 1} (Min + dj) ^ 2$。

这是一个必要不充分条件，不过其有很大概率也是充分条件，所以可以直接将其作为判定条件。

接下来就是计算的问题了：

$$\sum_{j = 0} ^ {i - 1} (Min + dj) ^ 2 = i \times Min ^ 2 + d \times Min \times i(i - 1) + d ^ 2 \sum_{j = 0}^{i - 1}j ^ 2$$

然后再使用平方和公式就做完了：

$$\sum_{j = 1}^n j^2 = \frac{n(n + 1)(2n + 1)}{6}$$

这个数显然不会爆 ``long long``，所以这题连取模都不需要。

**update on 2024-8-20：上述方法被 hack 了，不过再判一个立方和就过了。**

这里直接放公式（证明的话就是直接展开）：

$$\sum_{j = 0} ^ {i - 1} (Min + dj) ^ 3 = i \times Min ^ 3 + \frac{3}{2} \times Min ^ 2 \times d \times i(i - 1) + 3 \times Min \times d ^ 2 \sum_{j = 0}^{i - 1}j ^ 2 + d ^ 3 \sum_{j = 0}^{i - 1}j ^ 3$$

其中：

$$\sum_{j = 1}^n j^2 = \left(\frac{n(n + 1)}{2}\right) ^ 2$$

立方和会爆 ``long long``，所以需要对大质数（我取 $998244353$ 就过了）取模。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 9,MOD = 998244353;
int inv2,inv6;
int t,n;
int p[N];
bool f1[N],f2[N];
int ans;
int qpow(int base,int exp,int MOD){
	int ret = 1;
	base %= MOD;
	while(exp){
		if(exp & 1)
			ret = ret * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return ret;
}
int sq(int v){
    return v * v;
}
int cube(int v){
	return qpow(v,3,MOD);
}
int _sq_sum_(int v){//1^2+2^2+...v^2
	return v * (v + 1) * (v + v + 1) / 6;
}
int _sq_sum_2(int v){//(1^2+2^2+...v^2) % MOD
	return v * (v + 1) % MOD * (v + v + 1) % MOD * inv6 % MOD;
}
int _cube_sum_(int v){
    return sq((v * (v + 1) % MOD) * inv2 % MOD) % MOD;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	inv2 = qpow(2,MOD - 2,MOD);
	inv6 = qpow(6,MOD - 2,MOD);
	cin >> t;
	while(t--){
		ans = 0;
		cin >> n;
		for(int i = 1;i <= n;i++)
			f1[i] = f2[i] = false;
		for(int i = 1;i <= n;i++)
			cin >> p[i];
		if(n == 1){
			cout << "0\n";
			continue;
		}
		int Min = n + 1,Max = 0;
		int sum = 0,sq_sum = 0,cube_sum = 0;
		for(int i = 1;i <= n;i++){
			Min = min(Min,p[i]);
			Max = max(Max,p[i]);
			sum += p[i];
			sq_sum += sq(p[i]);
			(cube_sum += cube(p[i])) %= MOD;
			if(i == 1){
				f1[i] = true;
				continue;
 			}
			if((Min + Max) * i != (sum << 1))
				continue;
			if((Max - Min) % (i - 1))
				continue;
			int d = (Max - Min) / (i - 1);
			int tmp = i * sq(Min)
					+ d * Min * (i - 1) * i
					+ sq(d) * _sq_sum_(i - 1);
			if(tmp != sq_sum)
				continue;
			int tmp2 = (i * cube(Min) % MOD
					+ 3ll * sq(Min) % MOD * d % MOD * (i - 1) % MOD * i % MOD * inv2 % MOD
					+ 3ll * Min * sq(d) % MOD * _sq_sum_2(i - 1) % MOD
					+ cube(d) * _cube_sum_(i - 1) % MOD) % MOD;
			if(tmp2 != cube_sum)
				continue;
			f1[i] = true;
		}
		Min = n + 1,Max = 0;
		sum = sq_sum = cube_sum = 0;
		for(int i = n;i >= 1;i--){
			Min = min(Min,p[i]);
			Max = max(Max,p[i]);
			sum += p[i];
			sq_sum += sq(p[i]);
			(cube_sum += cube(p[i])) %= MOD;
			if(i == n){
				f2[i] = true;
				continue;
			}
			if((Min + Max) * (n - i + 1) != (sum << 1))
				continue;
			if((Max - Min) % (n - i))
				continue;
			int d = (Max - Min) / (n - i);
			int tmp = (n - i + 1) * sq(Min)
					+ d * Min * (n - i) * (n - i + 1)
					+ sq(d) * _sq_sum_(n - i);
			if(tmp != sq_sum)
				continue;
			int tmp2 = ((n - i + 1) * cube(Min) % MOD
					+ 3ll * sq(Min) % MOD * d % MOD * (n - i) % MOD * (n - i + 1) % MOD * inv2 % MOD
					+ 3ll * Min * sq(d) % MOD * _sq_sum_2(n - i) % MOD
					+ cube(d) * _cube_sum_(n - i) % MOD) % MOD;
			if(tmp2 != cube_sum)
				continue;
			f2[i] = true;
		}
		for(int i = 1;i < n;i++)
			ans += (f1[i] && f2[i + 1]);
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：yyyx_ (赞：2)

做法有点逆天，小心食用。

-------

**观察本题**：

1. 判断等差数列是否合法：排序后相邻数字的差是否为同一个值，即公差一定；

2. 如果数列中已经有 $m(m>1)$ 个数，则每次加入的数字 $x$ 有且仅有以下三种情况：

- $x< \min_{i=1}^m a_i$

  相当于增加了一个新的公差的可能值 $\min(a_i)-x$。

- $x> \max_{i=1}^m a_i$

  相当于增加了一个新的公差的可能值 $x-\max(a_i)$。

- $\exists i \in [1,n)$，$a_i<x<a_{i+1}$

  相当于删去了可能的公差 $a_{i+1}-a_i$，增加了两个新的可能的公差 $a_{i+1}-x$ 和 $x-a_i$。

得出以上结论后，就可以模拟上述过程了，储存正序遍历到第 $i$ 个数的等差数列合法性 $ans_i\ (ans_i∈{0,1})$。

#### 直接模拟是 $O(n^2)$ 的。

容易发现时间复杂度瓶颈在于查找唯一的 $i$ 使 $a_i<x<a_{i+1}$，时间复杂度是 $O(n)$ 的。

考虑使用树状数组优化，每次 $add(a_i,1)$，此时 $query(a_i)$ 取出的是小于等于 $a_i$ 的数字数量。

我们设小于等于 $a_i$ 的数字数量为 $cnt$。

我们要查找唯一的 $j$ 使 $a_j<x<a_{j+1}$，于是考虑二分。在树状数组上分别找出恰好使 $query(mid)=cnt-1$ 的最小的 $mid$ 的值 和 恰好使 $query(mid)=cnt+1$ 的最小的 $mid$ 的值。

注意特判 $cnt=0$ 和 $cnt=i-1$ 的情况，因为他们分别对应前文的 $1,2$ 两种情况。

然后翻转输入的 $a$ 序列，重复上述操作，判断等差数列是否合法和 $ans_{n-i}$ 的值是否为 $true$，如果是则答案 $+1$。

#### 时间复杂度 $O(n\log^2n)$。

不是很满意。

考虑[树状数组上二分](https://oi-wiki.org/ds/fenwick/#%E5%8D%95%E7%82%B9%E4%BF%AE%E6%94%B9%E6%9F%A5%E8%AF%A2%E5%85%A8%E5%B)，细节部分略有不同。

#### 时间复杂度 $O(n\log n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x)
{
    x = 0;
    register char c = getchar();
    register short f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    x *= f;
}

template <typename T, typename... Args>
inline void read(T &x, Args &...temps)
{
    read(x), read(temps...);
}

const int N = 2e5 + 5;
typedef long long ll;

signed main()
{
    int T, n, _log;
    read(T);
    while (T--)
    {
        read(n);
        _log = log2(n);
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++)
            read(a[i]);
        if (n == 1)
        {
            puts("0");
            continue;
        }
        vector<bool> ans(n + 1);
        vector<int> t(n + 1);
        unordered_map<int, int> mp;
        auto add = [&](int x)
        {
            for (; x <= n; x += x & -x)
                ++t[x];
        };
        auto query = [&](int x)
        {
            int ret = 0;
            for (; x; x -= x & -x)
                ret += t[x];
            return ret;
        };
        auto kth = [&](int k)
        {
            int sum = 0, x = 0;
            for (int i = _log; ~i; --i)
            {
                x += 1 << i;
                if (x >= n || sum + t[x] >= k)
                    x -= 1 << i;
                else
                    sum += t[x];
            }
            return x + 1;
        };
        auto solve = [&](int p, int tot)
        {
            int cnt = query(p);
            int x = 0;
            if (cnt == 0)
            {
                x = kth(1);
                ++mp[x - p];
            }
            else if (cnt == tot)
            {
                x = kth(tot);
                ++mp[p - x];
            }
            else
            {
                x = kth(cnt);
                int y = kth(cnt + 1);
                --mp[y - x];
                ++mp[p - x];
                ++mp[y - p];
            }
            add(p);
            return x;
        };
        ans[1] = ans[2] = 1;
        mp[abs(a[1] - a[2])] = 1;
        add(a[1]), add(a[2]);
        for (int i = 3; i < n; i++)
        {
            int x = solve(a[i], i - 1);
            ans[i] = i - 1 == mp[abs(x - a[i])];
        }
        mp.clear();
        fill(t.begin(), t.end(), 0);
        reverse(a.begin() + 1, a.end());
        mp[abs(a[1] - a[2])] = 1;
        add(a[1]), add(a[2]);
        int Ans = ans[n - 1] + ans[n - 2];
        for (int i = 3; i < n; i++)
        {
            int x = solve(a[i], i - 1);
            Ans += ans[n - i] && (i - 1 == mp[abs(x - a[i])]);
        }
        printf("%d\n", Ans);
    }

    return 0;
}
```

---

## 作者：fantastic_dream (赞：2)

#### 解答
初看题，发现并没有什么好方法实时判断两边的序列是否是等差序列，则考虑从排列与划分的特殊性来解题。

为了方便说明，把 $i$ 右移的过程看成取数，我们把序列 $[p_1,p_2,\cdots,p_i]$ 称为取出的序列，把序列 $[p_{i+1},p_{i+2},\cdots,p_n]$ 称为剩下的序列。于是我们发现可行的情况只有三种：

1. 取出的是 $[1,2,\dots,n]$ 的左端或右端，那剩下的就是另一端，即取出 $[1,2,\dots,i]$ 或 $[n-i,n-i+1,\dots,n]$。
2. 取出或剩下 $[1,n]$。
3. 取出所有的奇数或偶数。

剩下全部不合法。

到这就结束了，值得一提的是，你似乎需要一个 $O(n)$ 的写法，我一开始写的 set 超时了，不知道是不是人傻常数大。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int ma=1e6+5;
int n,sz[ma],vi[ma];
void sol(){
	cin>>n;
	int ans=0,a1=(n+1)/2,a2=n/2,zd1=0,zx1=n,zd2=n,zx2=1;
	for(int i=1;i<=n;i++){
		cin>>sz[i];
		vi[i]=0;
	}
	for(int i=1;i<n;i++){
		vi[sz[i]]=1;
		zd1=max(zd1,sz[i]),zx1=min(zx1,sz[i]);
		while(vi[zd2]&&zd2>=1)	zd2--;
		while(vi[zx2]&&zx2<=n)	zx2++;
		if(sz[i]%2)	a1--;
		else	a2--;
		if(zd1==i||zx1==n-i+1)	ans++;
		else if(i==2&&zx1==1&&zd1==n)	ans++;
		else if(i==n-2&&zx2==1&&zd2==n)	ans++;
		else if((!a1&&a2==n/2)||(!a2&&a1==(n+1)/2))	ans++;
	}
	cout<<ans<<'\n';
}
main(){
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)	sol();
	return 0;
}
```

---

## 作者：JYX0924 (赞：2)

这道题需要分类讨论。

题目上说 $p$ 是一个排列，所以我们可以发现答案的情况数是有限的。

1. 前 $i$ 个数或后 $i$ 构成一个公差为 $1$ 的等差数列，且数列的首项是 $1$ 或末项是 $n$。
2. 存在点 $i$ 可以将数列分成一边全是奇数和一边全是偶数。
3. 前 $n-2$ 或后 $n-2$ 个数构成的等差数列首项是 $2$，末项是 $n-1$。

我们只需要判断这三种情况即可。

下面是我的 AC 代码。

```c
#include<bits/stdc++.h>
#define ll long long 
#define maxn 1000005 
using namespace std;
ll T,n,a[maxn],num[5],flag,vis[maxn];
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n; for(int i=1;i<=n;i++) cin>>a[i];
		ll ans=1,zd=-1e9,zx=1e9; vector<ll> q;
		for(int i=1;i<n;i++)
		{
			zd=max(zd,a[i]); zx=min(zx,a[i]);
			if(zd-zx+1==i)
			{
				if(zd==n||zx==1) q.push_back(i);
				else if(n-i==2) q.push_back(i);
			}
		}
		zd=-1e9,zx=1e9;
		for(int i=n;i>=2;i--)
		{
			zd=max(zd,a[i]); zx=min(zx,a[i]);
			if(zd-zx+1==n-i+1)
			{
				if(zd==n||zx==1) q.push_back(i-1);
				else if(i==3) q.push_back(i-1);
			}
		}
		num[0]=num[1]=0;
		for(int i=1;i<n;i++)
		{
			num[a[i]%2]++;
			if(i==(n+1)/2)
			{
				if(num[1]==0||num[0]==0) q.push_back(i);
				break;
			}
			if(i==n/2&&n%2==1)
			{
				if(num[1]==0) q.push_back(i);
			}
		}
		sort(q.begin(),q.end());
		if(q.empty()) {cout<<"0\n"; continue;}
		if(q[0]>0) ans=1;
		for(int i=1;i<q.size();i++) if(q[i]!=q[i-1]&&q[i]>0) ans++;
		cout<<ans<<"\n";
	}
	return 0;
}
```
谢谢大家！！！

---

## 作者：xyx404 (赞：1)

## 思路：
题目中给出的是一个排列 $p$。  
排列说明了这个数组是由一到 $n$ 组成的，且不重复。

那么对于这个排列我们可以从一到 $n-1$ 依次枚举，对于每次访问到的第 $i$ 个数，记录最大值和最小值，相减判断是否是等差数列。

当 $i \gt 2$ 时，对于一到 $i$，排完序的数组等差数列只能是一或二。  
但是这么做只能判断等差为一的情况，所以还要特判一下。

由于 $i$ 要大于二，而 $i$ 最大为 $n-1$ 所以我们要特判一下 $n \le 3$  的情况。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
LL a[1000005];
void slove(){
	LL mx=INT_MIN,mn=INT_MAX,n,ans=0;
	bool flag1=1,flag2=1;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]%2==1&&i<=n/2)flag2=0;
		if(a[i]%2==0&&i<=(n+1)/2)flag1=0;
	}
	if(n==1){// 特判 n<=3
		printf("0\n");
		return;
	}
	else if(n==2){
		printf("1\n");
		return;
	}
	else if(n==3){
		printf("2\n");
		return;
	}
	if(flag2||flag1)ans++;
	for(int i=1;i<=n-1;i++){
		mx=max(mx,a[i]);mn=min(mn,a[i]);// 记录最大值和最小值 
		if(i==2&&mx==n&&mn==1){// 前两个数字为 1 和 n
			ans++;
			continue;
		}
		if(mx-mn+1==i&&(mx==n||mn==1))ans++;
	}
	if((a[n]==1||a[n]==n)&&(a[n-1]==1||a[n-1]==n))ans++;
	printf("%lld\n",ans);
	return;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		slove();
	}
	return 0;
}
```

---

## 作者：UniGravity (赞：1)

## Solution P10885 【MX-S3-T1】「FeOI Round 1」野心
提供一种不需要找性质的无脑做法。

先考虑对于一个前缀如何判断其是等差数列。既然是**等差**，可以想到使用**桶**维护相同差的个数。这样当**非空**的桶数量为 $1$ 时即为等差数列。

正向从 $1$ 扫到 $n$，每次新加入一个数字时可以使用 set 维护其前驱 $pre$ 和后继 $nxt$。那么桶中只需删除 $nxt-pre$ 再加上 $a_i-pre$ 和 $nxt-a_i$ 即可。

但是这样只能拿到 $60$ 分，这是因为加数不是很好维护。考虑变成删数，只需要倒序扫，使用链表维护即可。

时间复杂度 $O(n)$。注意要做两次操作，同时特判没有差值的情况。

```cpp
#include<bits/stdc++.h>
#define reg register
#define rnt reg int
#define forto(i,a,b) for(rnt i=(a);i<=(b);i++)
#define forbk(i,a,b) for(rnt i=(a);i>=(b);i--)
#define forv(i,a) for(rnt i=0;i<(a);i++)
#define il inline
using namespace std;
il int read(){
	rnt x=0,f=1;reg char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

const int N=2000005;
int n,a[N],cnt[N];
bool fg1[N],fg2[N];

struct List{
	int from[N],to[N];
	il void init(){
		from[1]=to[n]=-1;
		forto(i,1,n-1){
			from[i+1]=i;
			to[i]=i+1;
		}
	}
	il void del(rnt x){
		rnt pre=from[x],nxt=to[x];
		to[pre]=nxt;from[nxt]=pre;
	}
}qwq;

il void solve(bool fg[]){
	forto(i,0,n)cnt[i]=0;
	cnt[1]=n-1;
	rnt valc=1;
	qwq.init();
	forbk(i,n,1){
		if(valc==1)fg[i]=1;
		rnt pre=qwq.from[a[i]],bck=qwq.to[a[i]];qwq.del(a[i]);
		if(pre!=-1&&bck!=-1){
			if(cnt[bck-pre]==0)valc++;
			cnt[bck-pre]++;
		}
		if(pre!=-1){
			cnt[a[i]-pre]--;
			if(cnt[a[i]-pre]==0)valc--;
		}
		if(bck!=-1){
			cnt[bck-a[i]]--;
			if(cnt[bck-a[i]]==0)valc--;
		}
	}
	fg[1]=1;
}

il void work(){
	n=read();
	forto(i,1,n)a[i]=read();
	solve(fg1);
	reverse(a+1,a+n+1);solve(fg2);reverse(fg2+1,fg2+n+1);
//	forto(i,1,n)printf("%d ",fg1[i]);puts("");
//	forto(i,1,n)printf("%d ",fg2[i]);puts("");
	rnt c=0;
	forto(i,1,n-1){
		if(fg1[i]&&fg2[i+1])c++;
	}
	printf("%d\n",c);
	forto(i,1,n)fg1[i]=fg2[i]=0;
}

signed main(){
	rnt t=read();
	while(t--)work();
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：1)

我们发现合法的位置 $i$ 只会有三种情况：

- 开头两个数或者结尾两个数分别等于 $1, n$。这时候 $i = 2$ 或者 $n - 2$。

- 开头的 $\left \lfloor \dfrac{n}{2} \right \rfloor$ 或者结尾的 $\left \lfloor \dfrac{n}{2} \right \rfloor$ 个数组成公差为 $2$ 的等差数列。这时候 $i = \left \lfloor \dfrac{n}{2} \right \rfloor$ 或者 $n - \left \lfloor \dfrac{n}{2} \right \rfloor$。

- 某个前缀满足其排序后为以 $1$ 为首项 $1$ 为公差的等差序列，或者某个后缀满足其排序后为以 $1$ 为首项 $1$ 为公差的等差序列。这里可以等价为前缀的 $\max - \min = i$。后缀同理。

这些情况都讨论一下去重即可。

```cpp
// 1. 1, n, ......
// 2. 1, 2, 3, 4, ..., x, ....
// 3. 1, 3, 5, 7, ..., 2, 4, 6, 8, ...

#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>

using namespace std;

const int N = 2000010;
int a[N], mx[N], mn[N], n, ans, T;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T -- ) {
		cin >> n;
		set<int> s;
		for (int i = 1; i <= n; i ++ )
			cin >> a[i];
		if (n == 1) { cout << 0 << endl; continue; }
		if (n == 2) { cout << 1 << endl; continue; }
		mx[1] = mn[1] = a[1];
		for (int i = 2; i <= n; i ++ )
			mx[i] = max(mx[i - 1], a[i]),
			mn[i] = min(mn[i - 1], a[i]);
		for (int i = 1; i < n; i ++ ) 
			if (mn[i] == 1 and mx[i] - mn[i] == i - 1) 
				s.insert(i);
		for (int i = 1; i < n; i ++ )
			if (mx[i] == n and mx[i] - mn[i] == i - 1)
				s.insert(i);
		if (a[1] == 1 and a[2] == n)
			s.insert(2);
		if (a[2] == 1 and a[1] == n)
			s.insert(2);
		if (a[n] == 1 and a[n - 1] == n)
			s.insert(n - 2);
		if (a[n] == n and a[n - 1] == 1)
			s.insert(n - 2);
		bool flg = 1; // 判断前 n / 2 项是不是以 2 为公差
		for (int i = 1; i <= n / 2; i ++ )
			if (a[i] & 1) flg = 0;
		if (flg) s.insert(n / 2);
		flg = 1;
		for (int i = 1; i <= (n + 1) / 2; i ++ )
			if (a[i] % 2 == 0) flg = 0;
		if (flg) s.insert((n + 1) / 2);
		cout << s.size() << endl;
	}
	return 0;
}
```

---

## 作者：wwwwwza (赞：1)

看见判断是否等差数列，就要想到[P3792 由乃与大母神原型和偶像崇拜](https://www.luogu.com.cn/problem/P3792)。

这题可以枚举分割点 $i$，判断区间 $[1,i]$ 和 $[i+1,n]$，排序后是否为等差数列即可。

如果一段区间 $[l,r]$ 排序后是等差数列，设其中最小值为 $s$，最大值为 $t$，则公差 $d=\frac{t-s}{r-l}$。


我们就可以进行判断了，如果 $\sum\limits_{i=l}^r a_i=\sum\limits_{i=1}^{r-l+1} s+(i-1)\times d$ 且 

$\sum\limits_{i=l}^r a_i^2=\sum\limits_{i=1}^{r-l+1} (s+(i-1)\times d)^2$

$=\sum\limits_{i=1}^{r-l+1} s^2+2\times(i-1)\times d\times s +(i-1)^2\times d^2$

$=s^2\times(r-l+1) +(r-l+1)\times(r-l)\times s\times d+\frac{(2(r-l)+1)\times(r-l+1)\times (r-l)}{6}\times d^2$

这样就可以轻松地过掉这道题了。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
int t,n,p[N],premin[N],premax[N],sufmin[N],sufmax[N],a[N],b[N];
int calc(int n){
	return (2*n+1)*(n+1)*n/6;
}
bool check(int s,int t,int len,int ii,int jj){
	if(len==1||len==2){
		return 1;
	}
	if((s+t)*len/2!=ii){
		return 0;
	}
	int d=(t-s)/(len-1);
	int tot=len*s*s+len*(len-1)*s*d+calc(len-1)*d*d;
	return tot==jj;
}
signed main(){
	cin >>t;
	while(t--){
		cin >>n;
		for(int i=1;i<=n;i++){
			cin >>p[i];
			a[i]=a[i-1]+p[i];
			b[i]=b[i-1]+p[i]*p[i];
		}
		premin[0]=sufmin[n+1]=n+1;
		premax[0]=sufmax[n+1]=0;
		for(int i=1;i<=n;i++){
			premin[i]=min(premin[i-1],p[i]);
			premax[i]=max(premax[i-1],p[i]);
		}
		for(int i=n;i>=1;i--){
			sufmin[i]=min(sufmin[i+1],p[i]);
			sufmax[i]=max(sufmax[i+1],p[i]);
		}
		int ans=0;
		for(int i=1;i<n;i++){
			if(i!=1&&(premax[i]-premin[i])%(i-1)!=0)continue;
			if(i!=n-1&&(sufmax[i+1]-sufmin[i+1])%(n-i-1)!=0)continue;
			if(check(premin[i],premax[i],i,a[i],b[i])&&check(sufmin[i+1],sufmax[i+1],n-i,a[n]-a[i],b[n]-b[i]))ans++;
		}
		cout <<ans<<endl;
	}
	return 0;
}
```

---

## 作者：GI录像机 (赞：1)

## 思路

### $O(n\log n)$ 做法

考虑开一个桶，桶里装排序后相邻数差为 $d$ 的数量。从左往右（或从右往左）每次加入一个数并修改桶内的值，如果当前桶内只有一个地方有值，那么该前缀（或后缀）是等差数列。由于需要找当前的前驱、后继，要带一个 $\log$。常数优秀可以通过。

### $O(n)$ 做法

提供一个优化 $\log$ 做法常数的方法，如果把 $10^6$ 变成 $5\times 10^5$，$\log$ 做法少 $2$ 的常数就大概能过。于是考虑特殊判断公差为 $1$ 的等差数列（因为长度大于 $5\times 10^5$ 的前后缀公差只能为 $1$）。一个区间是公差为 $1$ 的等差数列当且仅当其最大值减最小值等于区间长度。

然后你就会发现其实有线性做法。如果一个前缀的长度小于 $\lfloor \frac{n}{2}\rfloor$，那么它对应的后缀长度就一定大于 $\lceil \frac{n}{2}\rceil$，于是这个后缀要么不是等差数列，要么公差为 $1$。

假设长度大于 $\lceil \frac{n}{2}\rceil$ 的一半值域为 $[L,R]$，那么另一半值域就为 $[1,L-1]\cup[R+1,n]$，容易发现只要 $[1,L-1]$ 和 $[R+1,n]$ 中只要有一个长度大于一，该等差数列的公差就只能为 $1$。

于是最终的答案分为三种情况：

1. 前缀与后缀都是公差为 $1$ 的等差数列
2. 其中一个是长度为 $n-2$ 的公差为 $1$ 的等差数列
3. 是长度分别为 $\lfloor \frac{n}{2}\rfloor$ 和 $\lceil \frac{n}{2}\rceil$ 的公差为 $2$ 的等差数列。

## 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int x = 0, f = 1;
	char c = getchar();
	while(c > '9' || c < '0') {
		if(c == '-')f = -f;
		c = getchar();
	}
	while(c <= '9' && c >= '0') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
void write(int x) {
	if(x < 0) {
		putchar('-');
		x = -x;
	} if(x > 9)write(x / 10);
	putchar((x % 10) + '0');
}
const int N = 1e6 + 10, INF = 0x3f3f3f3f, MOD = 1e9 + 7;
int t = read(), n, p[N];
signed main() {
	while(t--) {
		n = read();
		int minn = INF, maxn = 0, ans = 0;
		for(int i = 1; i <= n; i++) {
			p[i] = read();
			minn = min(minn, p[i]), maxn = max(maxn, p[i]);
			if(i == n);
			else if((maxn == n || minn == 1) && i == maxn - minn + 1)ans++;
			else if(i == 2 && maxn == n && minn == 1)ans++;
			else if(n - i == 2 && i == maxn - minn + 1)ans++;
		}
		if(n <= 3) {
			write(n - 1);
			putchar('\n');
			continue;
		}
		bool flag = 1;
		for(int i = 2; i <= n / 2; i++)flag = flag && (!(abs(p[i] - p[1]) & 1));
		if((n & 1) && (p[1] & 1))flag = flag && (p[n / 2 + 1] & 1);
		if(flag)ans++;
		write(ans);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Dream_poetry (赞：1)

### 思路：

因为是分为两部分，所以显然可以分三种情况考虑。

1. 划分的两部分每部分内部元素的奇偶性相同，等差数列内的差值为 $2$。
2. 划分的两部分的元素分别是 $1$ 到 $i$ 和 $i+1$ 到 $n$，差值为 $1$。
3. 一部分的元素是 $1$ 和 $n$，另一部分是 $2$ 到 $n-1$。

为什么结果是这样的呢？我们来简单分析一下。

首先，因为这是一个长度为 $n$ 的排列，所以内部元素可以显然分为奇数和偶数，此时只要可以找到一个交接点，使得该点左边和右边分别奇偶性相同，那就会对答案产生 $1$ 的贡献。

步骤二结论显然，就不赘述了。

考虑步骤三，可以保证一部分是差值为 $n-1$ 的等差数列，另一部分是差值为 $1$ 的等差数列。

为什么不会有其他的答案呢？显然由于只会分成两个等差数列，所以每个等差数列内部元素的差值都要小于 $3$，否则就必然无法成立。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
int n;
int a[1000005];
int ans;

struct node{
	int minn,maxn;
}tree[4000005];

inline void update(int p){
	tree[p].maxn=max(tree[p<<1].maxn,tree[p<<1|1].maxn);
	tree[p].minn=min(tree[p<<1].minn,tree[p<<1|1].minn);
}

inline void build(int p,int l,int r){
	if (l==r){
		tree[p].minn=a[l];
		tree[p].maxn=a[r];
		return;
	}
	int mid=(l+r)/2;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	update(p); 
}

inline int ask_min(int p,int l,int r,int L,int R){
	if (L<=l && r<=R){
		return tree[p].minn;
	}
	int mid=(l+r)/2;
	int minn=1e12;
	if (L<=mid){
		minn=min(minn,ask_min(p<<1,l,mid,L,R));
	}
	if (mid<R){
		minn=min(minn,ask_min(p<<1|1,mid+1,r,L,R));
	}
	return minn;
}

inline int ask_max(int p,int l,int r,int L,int R){
	if (L<=l && r<=R){
		return tree[p].maxn;
	}
	int mid=(l+r)/2;
	int maxn=-1e9;
	if (L<=mid){
		maxn=max(maxn,ask_max(p<<1,l,mid,L,R));
	}
	if (mid<R){
		maxn=max(maxn,ask_max(p<<1|1,mid+1,r,L,R));
	}
	return maxn;
}


inline void solve(){
	ans=0;
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	if (n==1){
		cout<<0<<"\n";
		return;
	}
	if (n==2){
		cout<<1<<"\n";
		return;
	}
	if (n==3){
		cout<<2<<"\n";
		return;
	}//三个特判，避免出错 
	int op=a[1]%2;
	int cnt=0;
	for (int i=2;i<=n;i++){
		if (a[i]%2!=op){
			cnt++;
			op=a[i]%2;
			if (cnt==2) break;
		}
	}
	if(cnt!=2){
		ans++;
	}//判断奇偶性贡献 
	if ( a[1]==1 && a[2]==n || a[1]==n && a[2]==1 || a[n]==n && a[n-1]==1 || a[n]==1 && a[n-1]==n    ){
		ans++;
	}//判断情况三的贡献 
	for (int i=1;i<n;i++){
		int u=ask_max(1,1,n,1,i);//因为我太菜了，所以只会用线段树来存区间最值，其实只需要四个记录前、后缀最值的数组即可 
		int v=ask_min(1,1,n,1,i);
		if ( u-v+1==i && (u==n || v==1)){
			ans++;
		}
	}//记录方案二的贡献 
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>T;
	while (T--){
		solve();
	}
	return 0;
} 
```



### 结语：
放了薛之谦的歌！好评！

---

## 作者：Wei_Han (赞：1)

对拍立大功。

先考虑公差，能够发现，公差为 $1$ 时一定合法，为 $2$ 时只有前 $\frac{n}{2}$ 个数的奇偶性相同才合法，大于 $2$ 在不考虑个数的情况下一定不合法。

然后分别做 $1$ 和 $2$，当公差为 $2$ 时直接把前 $\frac{n}{2}$ 个数记录出来排序验证即可，注意 $n$ 为奇数时 $\frac{n}{2}$ 上下取整都要验证。当公差为 $1$ 时还要讨论，假设当前取了 $i$ 个数，那么这些数可能是 $[1,i]$，可能是 $[n-i+1,n]$，当 $i=2$ 时可以是 $1$ 和 $n$，当 $i=n-2$ 时可以是 $[2,n-1]$，特判掉即可。

时间复杂度线性。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
//#pragma GCC optimize(2)
using namespace std;
typedef int ll;
const int N=1e6+10;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll n,m,a[N];
unordered_map<ll,ll> vis,mp,anss;

inline void solve(){
	read(n);vis=mp;anss=mp;
	fo(0,i,n+10) a[i]=0;
	fo(1,i,n) read(a[i]);
	if(n==1){wr(0);pr;return;}
	ll maxx=0,minn=n+1,sum=0,now=0;
	if(((a[1]==1&&a[2]==n)||(a[1]==n&&a[2]==1))&&n>2) sum++,anss[2]=1;
	fo(1,i,n-1){
		maxx=max(maxx,a[i]),minn=min(minn,a[i]);
		if((maxx==i&&minn==1)||(maxx==n&&maxx-minn+1==i)||(maxx==n-1&&minn==2&&i==n-2)) sum+=(!anss[i]),anss[i]=1;
	}
	now=1;vis=mp;ll ansss=0;
	fo(1,i,(n-1)/2+1) vis[a[i]]=1;
	while(vis[now]) now+=2,ansss++;
	if(ansss==(n-1)/2+1) sum+=(!anss[(n-1)/2+1]),anss[(n-1)/2+1]=1;
	vis=mp;ansss=0;
	fo(1,i,n/2) vis[a[i]]=1;
	now=2;
	while(vis[now]) now+=2,ansss++;
	if(ansss==n/2) sum+=(!anss[n/2]),anss[n/2]=1;
//	fo(1,i,n) if(anss[i]) wr(i),pr;
 	wr(sum);pr;
}
signed main(){
	ll tt;read(tt);while(tt--){solve();} 
	return 0;
}	
``````

---

## 作者：潘德理2010 (赞：0)

一个似乎比较直观的做法。

首先，考虑等差数列的性质。发现一个数列是等差数列，等价于这个数列排序后每一项与前一项的差全部相等。

那么，我们为了检测一个数列是否为等差数列，可以维护其排序后的序列的差分数组（本文中的差分数组从第二项减去第一项开始，不包括第一项）中，每个数各出现了多少次。如果只有一个数出现次数不为 $0$，那么就说明这个数列是等差数列。

对于每个 $i$，我们都要判断 $p_1$ 至 $p_i$ 的数列是否为等差数列（$p_{i+1}$ 到 $p_n$ 同理）。对此，我们可以维护一个数据结构。遍历整个序列，每遍历到一个数，就将其插入数据结构中。插入一个数后，我们需要更新差分数组，那么我们需要知道这个数的前驱和后继（也就是比这个数小的最大数，以及比这个数大的最小数）。更新完差分数组后，根据上一段所说的判断方式，即可判断插入完这个数后，数列是否为等差数列。所以，我们需要一个可以支持插入数，查询前驱和后继的数据结构。可以使用 set 和平衡树。时间复杂度 $O(n\log n)$。

本题时间似乎卡的比较死（对于这种做法），因此请特别注意常数。

代码如下。此代码可能卡不过去，请谨慎参考。


```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	set<int> t;
	int mi=1<<30,ma=0;
	inline void cl(){
		t.clear();
		mi=1<<30,ma=0;
	}
	inline void ins(int x){
		t.insert(x);
		mi=min(mi,x);
		ma=max(ma,x);
	}
	inline int sz(){
		return t.size();
	}
	inline int bk(int x){
		auto it=t.lower_bound(x);
		it--;
		return *it;
	}
	inline int ne(int x){
		auto it=t.upper_bound(x);
		return *it;
	}
}t;
inline int read(){
	int re=0;
	char ch=getchar();
	while(ch>='0'&&ch<='9') re=(re*10)+ch-48,ch=getchar();
	return re;
}
int q,n,a[1000100],ans,cnt;
bool r[1000100];
map<int,int> m;
int main(){
	q=read();
	while(q--){
		n=read();
		ans=cnt=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			t.ins(a[i]);
			if(i==1){
				r[i]=1;
				continue;
			}
			if(t.mi==a[i]){
				int u=t.ne(a[i]);
				if(m[u-a[i]]++==0) cnt++;
			}
			else if(t.ma==a[i]){
				int u=t.bk(a[i]);
				if(m[a[i]-u]++==0) cnt++;
			}			
			else{
				int x=t.bk(a[i]),y=t.ne(a[i]);
				if(--m[y-x]==0) cnt--;
				if(m[y-a[i]]++==0) cnt++;
				if(m[a[i]-x]++==0) cnt++;
			}
			if(cnt==1) r[i]=1;
		}
		m.clear();
		t.cl();
		cnt=0;
		for(int i=n;i>=2;i--){
			t.ins(a[i]);
			if(i==n){
				if(r[i-1]==1) ans++;
				continue;
			}
			if(t.mi==a[i]){
				int u=t.ne(a[i]);
				if(m[u-a[i]]++==0) cnt++;
			}
			else if(t.ma==a[i]){
				int u=t.bk(a[i]);
				if(m[a[i]-u]++==0) cnt++;
			}			
			else{
				int x=t.bk(a[i]),y=t.ne(a[i]);
				if(--m[y-x]==0) cnt--;
				if(m[y-a[i]]++==0) cnt++;
				if(m[a[i]-x]++==0) cnt++;
			}
			if(cnt==1&&r[i-1]==1) ans++;
		}
		m.clear();
		t.cl();
		for(int i=1;i<=n;i++){
			r[i]=0;
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：wbqhasvcf (赞：0)

先看数据范围，保证 $\sum n\le2\times10^{6}$，说明此题代码的时间复杂度必须为 $O(n)$ 或者 $O(n\log{n})$ 才能保证不超时。

再说说解题思路，注意到此题明确指出保证数列 $p$ 为 $1\sim n$ 的排列，根据此特殊性质我们可以列举出如下三种符合题意的情况：

$1.$ 满足左右两端排序后都是公差为 $1$ 的等差数列：满足前半段数列中所有数的最大值为 $i$，最小值为 $1$，并且后半段数列中所有数的最大值为 $n$，最小值为 $i+1$，或者满足前半段数列中所有数的最大值为 $n$，最小值为 $i+1$，并且后半段数列中所有数的最大值为 $i$，最小值为 $1$（在 $1\le i<n$ 的前提下）。

$2.$ 满足左右两端排序后都是公差为 $2$ 的等差数列：如果 $n$ 为偶数，当 $i=\frac{n}{2}$ 时，对于数列 $[p_{1},p_{2},\cdot\cdot\cdot,p_{i}]$ 满足数列中所有数均为偶数或均为奇数；如果 $n$ 为奇数，当 $i=\frac{n}{2}$ 时（向下取整），对于数列 $[p_{1},p_{2},\cdot\cdot\cdot,p_{i}]$ 满足数列中所有数均为偶数，或者当 $i=\frac{n}{2}+1$ 时，对于数列 $[p_{1},p_{2},\cdot\cdot\cdot,p_{i}]$ 满足数列中所有数均为奇数。

$3.$ 最特殊的情况（也是最容易被忽略的情况），一端为排序后公差为 $1$，首项为 $2$，末项为 $n-1$ 的等差数列，即另一端的数列中只有两个数（$1$ 和 $n$），排序后为公差为 $n-1$ 并且只有两个数的等差数列：判断是否满足 $p_{1}=1,p_{2}=n$ 或者 $p_{1}=n,p_{2}=1$ 或者 $p_{n-1}=1,p_{n}=n$ 或者 $p_{n-1}=n,p_{n}=1$ 即可。

注意符合题意的情况有且仅有以上三种，也就是说可以证明不存在两端有排序后公差为 $3$ 到 $n-2$ 的等差数列，并且任意两种情况有可能重合（举例将数列 $[1,3,2]$ 拆分成 $[1,3][2]$，此种拆分同时满足上述提到的情况 $2$ 和情况 $3$），所以最保险的办法就是用 STL 里的 set 存储满足条件的 $i$，输出 set 的长度，这样可以减少大量特判，因为 set 具有自动去重功能。

因此这道题我们就分析完了，根据上述思路很容易便能够打出一个时间复杂度为 $O(n)$ 的满分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n,p[1000005];
bool check(int k,int x)//判断是否满足情况2的函数 
{
	for(int i=1;i<=k;i++)
	    if(p[i]%2!=x)
	        return false;
	return true;
}
set<int> st;//用set存储下标减少特判 
int main()
{
    cin>>t;
	while(t--)
	{
		cin>>n;
		st.clear();//一定要记得初始化，清空所有元素
		for(int i=1;i<=n;i++)
			cin>>p[i];
		//判断是否满足情况2 
		if(n%2==0)
		{
			if(check(n/2,0)||check(n/2,1))
			    st.insert(n/2);
		}
		else if(n>1)//注意在n为奇数的情况下必须要特判n是否为1 
		{
			//这里可以写成多分支即else if，因为两种情况不可能同时出现
			if(check(n/2,0)) 
		        st.insert(n/2);
		    else if(check(n/2+1,1))
		        st.insert(n/2+1);
		}
		//判断是否满足情况3 
		if(n>2) 
		{
			//这里同样也可以写成多分支 
			if(p[2]==n&&p[1]==1||p[1]==n&&p[2]==1) st.insert(2);
			else if(p[n-1]==n&&p[n]==1||p[n-1]==1&&p[n]==n) st.insert(n-2);//注意这里不要插成n-1 
		}
		//判断是否满足情况1 
		int minp=1e9,maxp=0;
		for(int i=1;i<n;i++)
		{
			minp=min(minp,p[i]),maxp=max(maxp,p[i]);
			if(minp==1&&maxp==i||minp==n-i+1&&maxp==n) st.insert(i);
		}
		//输出set的长度即可 
		cout<<st.size()<<endl;
	}
	return 0;
}
```

另外本人发现这道题只要是时间复杂度为 $O(n)$ 的代码，不用较快的输入输出方式也可以 AC，不会超时。

---

