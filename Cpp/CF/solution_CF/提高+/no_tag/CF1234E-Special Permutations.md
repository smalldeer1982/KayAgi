# Special Permutations

## 题目描述

我们定义 $p_i(n)$ 为如下排列：$[i, 1, 2, \dots, i - 1, i + 1, \dots, n]$。也就是说，第 $i$ 个排列几乎是一个恒等排列（即每个元素都映射到自身），但元素 $i$ 被放在了第一个位置。例如：

- $p_1(4) = [1, 2, 3, 4]$；
- $p_2(4) = [2, 1, 3, 4]$；
- $p_3(4) = [3, 1, 2, 4]$；
- $p_4(4) = [4, 1, 2, 3]$。

给定一个数组 $x_1, x_2, \dots, x_m$（$1 \le x_i \le n$）。

记 $pos(p, val)$ 表示元素 $val$ 在排列 $p$ 中的位置。例如，$pos(p_1(4), 3) = 3$，$pos(p_2(4), 2) = 1$，$pos(p_4(4), 4) = 1$。

定义函数 $f(p) = \sum\limits_{i=1}^{m - 1} |pos(p, x_i) - pos(p, x_{i + 1})|$，其中 $|val|$ 表示 $val$ 的绝对值。该函数表示在排列 $p$ 中，数组 $x$ 的相邻元素之间的位置距离之和。

你的任务是计算 $f(p_1(n)), f(p_2(n)), \dots, f(p_n(n))$。

## 说明/提示

考虑第一个样例：

$x = [1, 2, 3, 4]$，因此

- 对于排列 $p_1(4) = [1, 2, 3, 4]$，答案为 $|1 - 2| + |2 - 3| + |3 - 4| = 3$；
- 对于排列 $p_2(4) = [2, 1, 3, 4]$，答案为 $|2 - 1| + |1 - 3| + |3 - 4| = 4$；
- 对于排列 $p_3(4) = [3, 1, 2, 4]$，答案为 $|2 - 3| + |3 - 1| + |1 - 4| = 6$；
- 对于排列 $p_4(4) = [4, 1, 2, 3]$，答案为 $|2 - 3| + |3 - 4| + |4 - 1| = 5$。

再看第二个样例：

$x = [2, 1, 5, 3, 5]$，因此

- 对于排列 $p_1(5) = [1, 2, 3, 4, 5]$，答案为 $|2 - 1| + |1 - 5| + |5 - 3| + |3 - 5| = 9$；
- 对于排列 $p_2(5) = [2, 1, 3, 4, 5]$，答案为 $|1 - 2| + |2 - 5| + |5 - 3| + |3 - 5| = 8$；
- 对于排列 $p_3(5) = [3, 1, 2, 4, 5]$，答案为 $|3 - 2| + |2 - 5| + |5 - 1| + |1 - 5| = 12$；
- 对于排列 $p_4(5) = [4, 1, 2, 3, 5]$，答案为 $|3 - 2| + |2 - 5| + |5 - 4| + |4 - 5| = 6$；
- 对于排列 $p_5(5) = [5, 1, 2, 3, 4]$，答案为 $|3 - 2| + |2 - 1| + |1 - 4| + |4 - 1| = 8$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 4
1 2 3 4
```

### 输出

```
3 4 6 5 
```

## 样例 #2

### 输入

```
5 5
2 1 5 3 5
```

### 输出

```
9 8 12 6 8 
```

## 样例 #3

### 输入

```
2 10
1 2 1 1 2 2 2 2 2 2
```

### 输出

```
3 3 
```

# 题解

## 作者：Kelin (赞：5)

## [题意](https://blog.csdn.net/BeNoble_/article/details/101985236)

给定一个长度为$m$的序列$x$

记：

>排列$p_i(n)=[i,1,2,...,i-1,i+1,...,n]$

>$pos(p,x)$表示$x$在排列$p$中的第几位

>$f(p)=\sum_{i=1}^{m-1}|pos(p,x_i)-pos(p,x_{i+1})|$

求$f(p_1(n)),f(p_2(n)),...,f(p_n(n))$。

$2\le n,m\le2\times10^5,1\le x_i\le n$

---

## 题解

### 方法一：暴力

观察$p_{i-1}(n)$和$p_i(n)$

$p_{i-1}(n)=[i-1,1,2,...,i,i+1,...,n]$

$p_i(n)=[i,1,2,...,i-1,i+1,...,n]$

可以发现只是交换了一下$i-1$和$i$的位置

即$pos(p_i(n),i)=1,pos(p_i(n),i-1)=i$。

其余的$pos(p_i(n),j)=pos(p_{i-1}(n),j)|j\neq i,j\neq i-1$

所以每次交换只会改变两种数$(i-1$和$i)$与左右的数的差的绝对值

记下每一种数所在的位置，每次枚举这两种数的所有位置，暴力修改答案

由于每种数最多只会被枚举两次，且总共只有$m$个数，所以总的时间还是线性的

时间复杂度$O(n+m)$

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
#define ps sr[++C]='\n'
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]=' ';
}
const int N=2e5+5;
typedef long long ll;
typedef int arr[N];
int n,m,a[N],p[N];ll ans;
vector<int>pos[N];
int main(){
	#ifndef ONLINE_JUDGE
		file("s");
	#endif
	sd(n),sd(m);
	fp(i,1,n)p[i]=i;
	fp(i,1,m)sd(a[i]),pos[a[i]].push_back(i);
	fp(i,1,m-1)ans+=abs(a[i]-a[i+1]);
	we(ans);
	fp(i,2,n){	
		fp(j,0,pos[i].size()-1){
			int k=pos[i][j];
			if(k>1)ans-=abs(i-p[a[k-1]]);
			if(k<m)ans-=abs(i-p[a[k+1]]);
		}
		fp(j,0,pos[i-1].size()-1){
			int k=pos[i-1][j];
			if(k>1&&a[k-1]!=i)ans-=abs(1-p[a[k-1]]);
			if(k<m&&a[k+1]!=i)ans-=abs(1-p[a[k+1]]);
		}
		p[i]=1;p[i-1]=i;
		fp(j,0,pos[i].size()-1){
			int k=pos[i][j];
			if(k>1)ans+=abs(1-p[a[k-1]]);
			if(k<m)ans+=abs(1-p[a[k+1]]);
		}
		fp(j,0,pos[i-1].size()-1){
			int k=pos[i-1][j];
			if(k>1&&a[k-1]!=i)ans+=abs(i-p[a[k-1]]);
			if(k<m&&a[k+1]!=i)ans+=abs(i-p[a[k+1]]);
		}
		we(ans);
	}
return Ot(),0;
}
//Tips:注意序列长度是m不是n!!!!!
```

### 方法二：差分+前缀和

对于某一对相邻的数$l,r(l<r)$，考虑他们在所有的$p_i(n)$中的相对位置$($即对答案的贡献$)$

>$1\le i<l$时：$l,r$相对位置不变，贡献均为$r-l$

>$i=l$时：$l$被移到第一位，$r$不变，贡献为$r-1$

>$l<i<r$时：每次都是$l$到$r$中的一个数被移到第一位，$l,r$距离$-1$，贡献均为$r-l-1$

>$i=r$时：$r$被移到第一位，$l$不变，贡献为$l$

>$r<i\le n$时：$l,r$相对位置不变，贡献均为$r-l$

于是这题就变成区间修改和按顺序单点查询了

用差分数组快速修改$f(p_i(n))$，最后求一遍前缀和即可

时间复杂度$O(n+m)$

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
#define ps sr[++C]='\n'
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]=' ';
}
const int N=2e5+5;
typedef long long ll;
typedef int arr[N];
int n,m,a[N];ll f[N];
inline void mdy(int l,int r,int x){f[l]+=x,f[r+1]-=x;}
int main(){
	#ifndef ONLINE_JUDGE
		file("s");
	#endif
	sd(n),sd(m);
	fp(i,1,m)sd(a[i]);
	fp(i,1,m-1){
		int l=a[i],r=a[i+1];
		if(l==r)continue;
		if(l>r)swap(l,r);
		mdy(1,l-1,r-l);
		mdy(l,l,r-1);
		mdy(l+1,r-1,r-l-1);
		mdy(r,r,l);
		mdy(r+1,n,r-l);
	}
	fp(i,1,n)we(f[i]+=f[i-1]);
return Ot(),0;
}
```

---

## 作者：Nightingale_OI (赞：4)

整理可得每次 $ p_i(n) $ 对于 $ p_1(n) $ 只改变了一个数的位置。

我们只需求 $ f(p_1(n)) $ ，再把每次答案的变化记录下来就可以了。

记 $ a_i $ , $ b_i $ 为 $ x $ 相邻的位置的较小、较大值。

即对于$ 1 \leq i < m $ ，$ a_i = \min(x_i,x_{i+1}) $ , $ b_i = \max(x_i,x_{i+1}) $ 。

分类讨论一下规律：

0. 答案原来是 $ b_i - a_i $ 。

1. 对于 $ p_{a_i} $ ，答案变为了 $ b_i - 1 $ ， 增加了 $ a_i - 1 $ ，直接用数组记录。

2. 对于 $ p_j \space ( a_i < j < b_i ) $ ，答案变为了 $ b_i - a_i - 1 $ ，减少了 $ 1 $ ，这里可以用树状数组差分。

3. 对于 $ p_{b_i} $ ，答案变为了 $ a_i $，增加了 $ 2a_i - b_i $ ，直接用数组记录。

程序复杂度 $ O(n + m \log_{2}{n}) $ ，已经能过了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
const int maxn=202020;
int b[maxn],c[maxn];
long long f[maxn];
void add(int x,int v){
    for(register int i=x;i<=n;i+=(-i&i))c[i]+=v;
}
int sum(int x){
    int re=0;
    for(register int i=x;i;i-=(-i&i))re+=c[i];
    return re;
}
int main(){
    cin>>n>>m;
    long long ans=0;
    for(register int i=1;i<=m;++i)scanf("%d",&b[i]);
    for(register int i=1;i<m;++i){
        s=min(b[i],b[i+1]);
        l=max(b[i],b[i+1]);
        if(s==l)continue;
        ans+=l-s;
        add(s+1,-1);
        add(l,1);
        f[s]+=s-1;
        f[l]+=(s<<1)-l;
    }
    for(register int i=1;i<=n;++i)printf("%lld ",ans+sum(i)+f[i]);
    return 0;
}
```

观察发现只在预处理使用了差分，所以可以记前缀和直接统计。

这样程序就优化成 $ O(n + m) $ 了。

最终代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
const int maxn=202020;
int b[maxn],c[maxn];
long long f[maxn];
int main(){
    cin>>n>>m;
    long long ans=0;
    for(register int i=1;i<=m;++i)scanf("%d",&b[i]);
    for(register int i=1;i<m;++i){
        s=min(b[i],b[i+1]);
        l=max(b[i],b[i+1]);
        if(s==l)continue;
        ans+=l-s;
        ++c[l];
        --c[s+1];
        f[s]+=s-1;
        f[l]+=(s<<1)-l;
    }
    for(register int i=1;i<=n;++i)printf("%lld ",ans+(c[i]+=c[i-1])+f[i]);
    return 0;
}
```

---

## 作者：minVan (赞：3)

**题目大意**

定义排列 $p_i(n) = [i, 1, 2, \dots\, i - 1, i + 1, \dots, n]$，定义 $pos(p, val)$ 表示 $val$ 在排列 $p$ 中的位置，给定序列 $x$，定义函数 $f(p) = \sum\limits_{i=1}^{m - 1} |pos(p, x_i) - pos(p, x_{i + 1})|$，求 $f(p_1)$ 到 $f(p_n)$。

**解题思路**

模拟、数学。我们可以发现排列的变化：
```
1 2 3 4
2 1 3 4
3 1 2 4
4 1 2 3
```
第 $i$ 个排列与第 $i-1$ 个排列，只有两个数字的位置不同，这说明我们在计算第 $i$ 个排列的答案时，只需要考虑在上一个答案的基础上，单独计算变动位置的那两个数字所产生的影响即可。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, x[N];
vector<int> edge[N];
long long sum;
int main() {
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		cin >> x[i];
		if(i != 1 && x[i] != x[i - 1]) {
			edge[x[i]].push_back(x[i - 1]);
			edge[x[i - 1]].push_back(x[i]);
			sum += abs(x[i] - x[i - 1]);
		}
	}
	cout << sum << " ";
	for(int i = 2; i <= n; i++) {
		long long cnt1 = 0, cnt2 = 0;
		for(int j = 0; j < edge[i - 1].size(); j++) {
			int v = edge[i - 1][j];
			if(v > i - 1) {
				cnt1 += v - 1;
			} else {
				cnt1 += v;
			}
		}
		for(int j = 0; j < edge[i].size(); j++) {
			int v = edge[i][j];
			if(v == i - 1) {
				continue;
			}
			if(v < i) {
				cnt2 += i - v - 1;
			} else {
				cnt2 += v - i;
			}
		}
		sum -= (cnt1 + cnt2);
		cnt1 = cnt2 = 0;
		for(int j = 0; j < edge[i].size(); j++) {
			int v = edge[i][j];
			if(v < i) {
				cnt1 += v;
			} else {
				cnt2 += v - 1;
			}
		}
		for(int j = 0; j < edge[i - 1].size(); j++) {
			int v = edge[i - 1][j];
			if(v == i) {
				continue;
			}
			if(v < i - 1) {
				cnt2 += i - 1 - v;
			} else {
				cnt2 += v - i;
			}
		}
		sum += cnt1 + cnt2;
		cout << sum << " ";
	}
	return 0;
}
```

---

## 作者：开始新的记忆 (赞：3)

题目大意：给你n个数，让你计算出一些东西然后输出（详见题目，有f(p)=……）。

大致思路：用上差分的思想，每次计算发现都会使某些地方有变动，稍微手动模拟一下即可。

PS：感谢Alex_Wei


```
#include<bits/stdc++.h> 
using namespace std;
long long n,m,a[200010],f[200010];
 
int main()
{	cin>>n>>m;
	for(int i=1;i<=m;++i)
		cin>>a[i];
	for(int i=1;i<m;++i)
	{
		if(a[i]==a[i+1])
			continue;
		int x=a[i],y=a[i+1],di=fabs(x-y);
		if(x>y)
			swap(x,y);
		f[1]+=di;f[x]-=di;
		f[x]+=y-1;f[x+1]-=y-1;
		f[x+1]+=di-1;f[y]-=di-1;
		f[y]+=x;f[y+1]-=x;
		f[y+1]+=di;
	} 
	for(int i=1;i<=n;++i)
		f[i]+=f[i-1],cout<<f[i]<<' ';
	cout<<endl;
    return 0;
}
```


---

## 作者：_Above_the_clouds_ (赞：2)

# 思路：
第 $i$ 次排列就是在上一次排列中交换 $i$ 和 $i-1$ 的位置，那么只会影响 $i$ 和 $i-1$ 的贡献。

先预处理一遍初始贡献，每一次减去 $i$ 和 $i-1$ 原先的贡献，再交换，最后加上他们的贡献。

注意 $i$ 和 $i-1$ 可能会有重复的贡献被减去或加上，所以用数组标记一下。

# 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}

void write(long long x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}

const int Max = 1e6 + 5;
int n,m;
long long ans;
bool vis[Max];
int x[Max],pos[Max];
vector<int>edge[Max];
signed main() {
	n=read(),m=read();
	for(int i=1;i<=m;i++) x[i]=read(),edge[x[i]].push_back(i);
	for(int i=1;i<=n;i++) pos[i]=i;
	for(int i=1;i<m;i++) ans+=abs(x[i]-x[i+1]);
	write(ans),putchar(' ');
	for(int i=2;i<=n;i++){
		for(int j=0;j<edge[i].size();j++){
			int y=edge[i][j];
			if(!vis[y]&&y!=m) ans-=abs(pos[x[y]]-pos[x[y+1]]),vis[y]=1;
			if(!vis[y-1]&&y!=1) ans-=abs(pos[x[y]]-pos[x[y-1]]),vis[y-1]=1;
		}
		for(int j=0;j<edge[i-1].size();j++){
			int y=edge[i-1][j];
			if(!vis[y]&&y!=m) ans-=abs(pos[x[y]]-pos[x[y+1]]),vis[y]=1;
			if(!vis[y-1]&&y!=1) ans-=abs(pos[x[y]]-pos[x[y-1]]),vis[y-1]=1;
		}
		swap(pos[i],pos[i-1]);
		for(int j=0;j<edge[i].size();j++){
			int y=edge[i][j];
			if(vis[y]&&y!=m) ans+=abs(pos[x[y]]-pos[x[y+1]]),vis[y]=0;
			if(vis[y-1]&&y!=1) ans+=abs(pos[x[y]]-pos[x[y-1]]),vis[y-1]=0;
		}
		for(int j=0;j<edge[i-1].size();j++){
			int y=edge[i-1][j];
			if(vis[y]&&y!=m) ans+=abs(pos[x[y]]-pos[x[y+1]]),vis[y]=0;
			if(vis[y-1]&&y!=1) ans+=abs(pos[x[y]]-pos[x[y-1]]),vis[y-1]=0;
		}
		write(ans),putchar(' ');
	}
	return 0;
}
/*
第i回合，交换i和i-1的位置 
*/
```

---

## 作者：_lxy_ (赞：2)

### 题意

略。

### 分析

观察发现，每个 $p_a$ 相较于 $p_1$ 只是将 $a$ 提到了最前面。因此，当排列为 $p_a$ 时，对于相邻的 $x_i$ 和 $x_{i+1}$，令 $mx \leftarrow \min(x_i,x_{i+1}),mn=\leftarrow \max(x_i,x_{i+1})$，此时其对最后 $f$ 函数值增加的贡献 $t$ 可以分情况讨论得到：

$$
t=\begin{cases} \begin{cases} 0 &x_i,x_{i+1}<a \bigvee a<x_i,x_{i+1} \\ 1&mn<a<mx \\ \end{cases}&x_i=a \bigvee x_{i+1}=a\\\begin{cases} mn-1 &mx=a\\mn-mx+mn&mn=a\\\end{cases}&x_i \neq a \bigwedge x_{i+1} \neq a\end{cases}

$$

因此，可以先预处理出 $f(p_1)$ 的值，每次询问输出加上增加贡献的和即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fre(z) freopen(z".in","r",stdin),freopen(z".out","w",stdout)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;
typedef pair<int,int> Pair;
const int inf=2139062143;
static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf;
#define gc() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define getchar gc
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
    register T1 x=0;register bool f=false;char ch=getchar();
    while(ch<'0') f|=(ch=='-'),ch=getchar();
    while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=(f?-x:x);a=x;qread(b...);
}
template<class T> T qmax(T x,T y){return x>y?x:y;}
template<class T,class ...Arg> T qmax(T x,T y,Arg ...arg){return qmax(x>y?x:y,arg...);}
template<class T> T qmin(T x,T y){return x<y?x:y;}
template<class T,class ...Arg> T qmin(T x,T y,Arg ...arg){return qmin(x<y?x:y,arg...);}
template<class T> T randint(T l,T r){static mt19937 eng(time(0));uniform_int_distribution<T>dis(l,r);return dis(eng);}
const int MAXN=2e5+7;
int n,m,x[MAXN];
namespace Seg_tree
{
    const int MX=1000007;
    int tree[MX],tag[MX];
    inline int ls(int p){return p<<1;}
    inline int rs(int p){return p<<1|1;}
    inline void push_up(int p){tree[p]=tree[ls(p)]+tree[rs(p)];}
    void f(int p,int l,int r,int k)
    {
        tree[p]+=(r-l+1)*k;
        tag[p]+=k;
    }
    void push_down(int p,int l,int r)
    {
        int mid=(l+r)>>1;
        f(ls(p),l,mid,tag[p]);
        f(rs(p),mid+1,r,tag[p]);
        tag[p]=0;
    }
    void build(int a[],int p,int l,int r)
    {
        if(l==r) tree[p]=a[l];
        else
        {
            int mid=(l+r)>>1;
            build(a,ls(p),l,mid);
            build(a,rs(p),mid+1,r);
            push_up(p);
        }
    }
    void update(int p,int l,int r,int L,int R,int k)
    {
        if(L<=l&&r<=R) tree[p]+=(r-l+1)*k,tag[p]+=k;
        else
        {
            int mid=(l+r)>>1;
            push_down(p,l,r);
            if(L<=mid) update(ls(p),l,mid,L,R,k);
            if(R>mid) update(rs(p),mid+1,r,L,R,k);
            push_up(p);
        }
    }
    int query(int p,int l,int r,int L,int R)
    {
        if(L<=l&&r<=R) return tree[p];
        else
        {
            int mid=(l+r)>>1,res=0;
            push_down(p,l,r);
            if(L<=mid) res+=query(ls(p),l,mid,L,R);
            if(R>mid) res+=query(rs(p),mid+1,r,L,R);
            return res;
        }
    }
}
using namespace Seg_tree;
int ans,t[MAXN];
signed main()
{
    qread(n,m);int i,j;for(i=1;i<=m;i++) qread(x[i]);
    for(i=1;i<m;i++) 
    {
        if(x[i]==x[i+1]) continue;
        ans+=abs(x[i+1]-x[i]);
        int ta=x[i],tb=x[i+1];if(ta<tb) swap(ta,tb);
        t[tb]+=tb-1;t[ta]+=tb-(ta-tb);
        if(ta-tb<2) continue;
        update(1,1,n,tb+1,ta-1,1);
    }printf("%lld ",ans);
    for(i=2;i<=n;i++)
        printf("%lld ",ans-query(1,1,n,i,i)+t[i]);
    return 0;
}
```

---

## 作者：123zbk (赞：1)

考虑在序列 $x$ 中相邻的两个数 $x_i$ 和 $x_{i+1}$ 对答案产生的贡献。(默认 $x_{i+1}\ge x_i$)

当 $1\le i<x_i$ 或 $i>x_{i+1}$ 时，此时 $x_i$ 和 $x_{i+1}$ 位置都后移一位，贡献都是 $x_{i+1}-x_i$。

当 $i=x_i$ 时，$x_i$ 提到了第一位，$x_{i+1}$ 不变，此时贡献为 $x_{i+1}-1$。

当 $i=x_{i+1}$ 时，$x_{i+1}$ 提到第一位，$x_i$ 往后一位，此时贡献为 $x_i$。

当 $x_i<i<x_{i+1}$ 时，它们中间的一个数被提到了前面，所以贡献就是 $x_{i+1}-x_i-1$。

用差分的思想，最后前缀和求一下即可。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e5+5;
int n,m,a[maxn],f[maxn];
void update(int l,int r,int x)
{
    f[l]+=x;
    f[r+1]-=x;
}
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<m;i++)
    {
        int l=a[i],r=a[i+1];
        if(l==r)
        {
            continue;
        }
        if(l>r)
        {
            swap(l,r);
        }
        update(1,l-1,r-l);
        update(l,l,r-1);
        update(l+1,r-1,r-l-1);
        update(r,r,l);
        update(r+1,n,r-l);
    }
    for(int i=1;i<=n;i++)
    {
        f[i]+=f[i-1];
        printf("%lld ",f[i]);
    }
    return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：1)

搬到了学校考试的 T4，场切成为 rnk1。

首先观察式子我们发现相当于两个 $x$ 的距离。

那么拆贡献，考虑 $x_p,x_{p+1}$ 对 $p_i(n)$ 产生的贡献。

令 $l=\min(x_p,x_{p+1}),r=\max(x_p,x_{p+1})$

1. 当 $r<i$ 或 $i<l$ 时，贡献不变为 $r-l$。

1. 当 $l<i<r$ 时，贡献为 $r-l-1$。

1. 当 $i=l$ 时贡献为 $r-1$。

1. 当 $i=r$ 时贡献为 $l$。

发现是个连续区间的贡献，打上一个小差分就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans[1000005];
int n,m,a[1000005];
void add(int l,int r,int x){
	if(l>r)return;
	ans[l]+=x;
	ans[r+1]-=x;
	
}
void modify(int x,int y){
	if(x==y)return;
	int l=x,r=y;
	if(l>r)swap(l,r);
	//x_i<x_{i+1}<p  p=[x_{i+1}+1,n]
	add(r+1,n,r-l);
	//p<x_i<x_{i+1} p=[1,x_i-1]
	add(1,l-1,r-l);
	//x_i<p<x_{i+1} p=[x_i+1,x_{i+1}-1]
	add(l+1,r-1,r-l-1);
	add(l,l,r-1);
	add(r,r,l);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	for(int i=1;i<m;i++){
		modify(a[i],a[i+1]);
	}
	for(int i=1;i<=n;i++)ans[i]+=ans[i-1];
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	cout<<"\n";
} 
```

---

## 作者：littleseven (赞：1)

### 题目解析：

很有趣的题。拿到手首先想到模拟，发现暴力过不了emmm……。

但是却很清楚的知道解法一定是暴力上搞事情，于是找到差分。

那……差分啥东西？？？

选择差分区间（对答案贡献）。

之后前缀和维护答案，当前点的前缀和就是当前点的答案。

也就是说差分维护贡献，前缀和维护不同的序列。

那么如何用差分维护贡献：

- 当$1\le i\le l$时，$l,r$的相对位置不变，贡献为$r-l$

- 当$i=l$时，$r$不变，贡献为$r-1$
- 当$l\lt i \lt r$时，$l \sim r$之间总有一个数被提到最前边 ，$l,r$距离$-1$，贡献为$r-l-1$
- 当$i=r$时，$r$被提到最前边，$l$不变，贡献为$l$
- 当$r \lt i \le n$时，$l，r$的相对位置不变，贡献为$r-l$

这样就可以了。

```cpp
#include <bits/stdc++.h>

using namespace std;

char *p1, *p2, buf[100000];
#define int long long

#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1 ++ )

int rd() {
	int x = 0, f = 1;
	char c = nc();
	while (c < 48) {
		if (c == '-') {
			f = -1;
		}
		c = nc();
	}
	while (c > 47) {
		x = (((x << 2) + x) << 1) + (c ^ 48);
		c = nc();
	}
	return x * f;
}

const int N = 2e5 + 10;

int n, m, now, num[N], tmp[N];

void fix(int l, int r, int val) {
	tmp[l] += val;
	tmp[r + 1] -= val;
}

signed main() {
	n = rd(), m = rd();
	for (int i = 1; i <= m; i ++ ) {
		num[i] = rd();
	}
	for (int i = 1; i <= m - 1; i ++ ) {
		int l = num[i], r = num[i + 1];
		if (l == r) {
			continue ;
		}
		if (l > r) {
			swap(l, r);
		}
		fix(1, l - 1, r - l);
		fix(l ,l, r - 1);
		fix(l + 1, r - 1, r - l - 1);
		fix(r, r, l);
		fix(r + 1, n, r - l);
	}
	for (int i = 1; i <= n; i ++ ) {
		tmp[i] += tmp[i - 1];
		printf("%I64d ", tmp[i]);
	}
	return 0;
}
```

---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
这道题需要用到一点点数学逻辑思维就可以完成了。~~个人认为评蓝有一点过了，算是上位绿吧。~~

我们可以发现每一次更改我们其实只是把一个数字提到了第一位，那么计算贡献的话也就只和当前这一个数字的左右两个数字有关系，那么我们就可以去用一张图去存当前这位在哪里出现过的，然后如果左边或右边的数在当前数后面那么这一轮的贡献明显就是增加当前数的值减一，并在以后的计算中会减少一的贡献一直到左边或者右边的数也被前提。如果在当前数的前面那就把之前减一的贡献删去，在这一轮中直接把之前二者的差距删去加上当前数字减去之前贡献即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
signed a[1000005];
vector<signed>s[1000005];
signed main(){
	signed n=read(),m=read();int sum=0;
	for(int i=1;i<=m;i++){
		a[i]=read();
		if(i!=1)sum+=abs(a[i]-a[i-1]);
		s[a[i]].push_back(i);
	}
//	sum1=sum;
	for(int i=1;i<=n;i++){
		int num=sum;int op=0;
		for(int j=0;j<s[i].size();j++){
			int y=s[i][j];
			if(y!=1 && a[y-1]!=a[y])
			if(a[y-1]<=i){sum=(sum+i-(-a[y-1]+i)*2)+1;op++;}//如果在前面就直接算，去除贡献
			else{sum=sum+i-1;op--;}//后面这轮就加上当前数值，累计贡献
			if(y!=m && a[y+1]!=a[y])
			 if(a[y+1]<=i){sum=(sum+i-(-a[y+1]+i)*2)+1;op++;}
			else{sum=sum+i-1;op--;}
		}
		write(sum),putchar(' ');sum=num+op;
	}
	return 0;
}
```

---

