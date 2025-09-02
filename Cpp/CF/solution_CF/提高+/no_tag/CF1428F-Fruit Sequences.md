# Fruit Sequences

## 题目描述

Zookeeper is buying a carton of fruit to feed his pet wabbit. The fruits are a sequence of apples and oranges, which is represented by a binary string $ s_1s_2\ldots s_n $ of length $ n $ . $ 1 $ represents an apple and $ 0 $ represents an orange.

Since wabbit is allergic to eating oranges, Zookeeper would like to find the longest contiguous sequence of apples. Let $ f(l,r) $ be the longest contiguous sequence of apples in the substring $ s_{l}s_{l+1}\ldots s_{r} $ .

Help Zookeeper find $ \sum_{l=1}^{n} \sum_{r=l}^{n} f(l,r) $ , or the sum of $ f $ across all substrings.

## 说明/提示

In the first test, there are ten substrings. The list of them (we let $ [l,r] $ be the substring $ s_l s_{l+1} \ldots s_r $ ):

- $ [1,1] $ : 0
- $ [1,2] $ : 01
- $ [1,3] $ : 011
- $ [1,4] $ : 0110
- $ [2,2] $ : 1
- $ [2,3] $ : 11
- $ [2,4] $ : 110
- $ [3,3] $ : 1
- $ [3,4] $ : 10
- $ [4,4] $ : 0

The lengths of the longest contiguous sequence of ones in each of these ten substrings are $ 0,1,2,2,1,2,2,1,1,0 $ respectively. Hence, the answer is $ 0+1+2+2+1+2+2+1+1+0 = 12 $ .

## 样例 #1

### 输入

```
4
0110```

### 输出

```
12```

## 样例 #2

### 输入

```
7
1101001```

### 输出

```
30```

## 样例 #3

### 输入

```
12
011100011100```

### 输出

```
156```

# 题解

## 作者：zhoukangyang (赞：38)

[不一定更好的体验](https://www.cnblogs.com/zkyJuruo/p/13833960.html)

## $\texttt{Bullshit}$
蒟蒻 $\texttt{7 min}$ 切 $\texttt{F}$, 挽回了本一定掉分的局面/cy
![qwq.png](https://i.loli.net/2020/10/18/R8d6bZaW3CKcYzT.png)
~~分竟然还没有别人 5 题高~~

(本题解为目前 cf 上的最短代码解！)
## $\texttt{Solution}$

考虑计算对于每一个左端点的贡献。

所以可以考虑算这个左端点比后面的那个左端点多了多少贡献。

对于一个位置 $l$ : 
1. 这个位置是 `0` : 没有多余贡献。
1. 这个位置是 `1` : 如果这个位置到这个联通块底部的长度为 $k$, 那么找到后面第一个出现连通块长度为 $k$ 的位置 $d$，那么右端点在 $[l, d - 1]$ 的答案都会加一，比左端点为 $l+1$ 的贡献多了 $d - l$; 如果找不到，右端点在 $[d, n]$ 的答案都会加一，那么比左端点为 $l+1$ 的贡献多了 $n + 1 - l$。

给一张图以便理解：

![Codeforces-Fruit.png](https://i.loli.net/2020/10/22/9Y6QlOVwgERB8ie.png)

然后考虑怎么维护这东西。

由于我们要找的是第一个出现联通块长的位置, 那么我们可以在计算完长度为 $k$, 初始位置为 $t$ 的连通块的贡献后，从左到右更新联通块长度为 $1$ 到 $k$ 的第一次出现的位置。长度为 $p$ 第一次出现的位置更新为 $t + p - 1$。

因此直接用数组维护就好啦！

## $\texttt{Code}$
不是给人看的代码: 
```cpp
#include<cstdio>
int n,f[555555],now;long long ans,sum;char s[555555];int main(){scanf("%d%s",&n,s+1);for(int i=n;i>=1;i--){if(s[i]-'0')now++,sum+=(!f[now]?n+1:f[now])-i;else while(now)f[now]=i+now,now--; ans+=sum;}printf("%lld\n", ans);}
```
给人看的代码: 
```cpp
#include<bits/stdc++.h>
const int N = 1e6 + 7;
int n, f[N], now; 
// f[i] : 记录联通块大小为 i 的第一次出现的位置 
// now : 记录现在的连通块大小 
long long  ans, sum;
// ans : 记录答案
// sum : 目前这个左端点的答案 
char s[N];
int main() {
	scanf("%d%s", &n, s + 1);
	for(int i = 1; i <= n; i++) f[i] = n + 1;
	for(int i = n; i >= 1; i--) {
		if(s[i] - '0') now++, sum += f[now] - i; // 联通块大小++, 计算比左端点为 i + 1 的贡献多了多少 
		else while(now) f[now] = i + now, now--; // 一个连通块的结束，更新 f 的值 
		ans += sum; 
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Soulist (赞：13)


将答案差分，我们考虑对于 $i=1,2...$ 计算有多少个区间答案至少是 $i$

我们先把连续的 $1$ 缩起来，那么现在这个序列必然 01 交错，然后每一段的大小我们都知道，这样计算答案是方便的（对于 $0$ 维护最近合法的 $l$ 端点，$1$ 的贡献可以直接算）

然后每次增大 $i$，我们将那些长度小于 $i$ 的全 $1$ 区间视为 $0$ 并和它前面以及后面的 $0$ 缩起来。

单次扫是 $\mathcal O(\text{段数})$ 的，显然段数 $\le \frac{n}{i}$，所以复杂度不会超过 $n\ln n$

然后我早上起来分析了一下，发现他是 $\mathcal O(n)$ 的，因为段数不会超过连续 $1$ 的数量乘以 $2$，然后考虑初始每段 $1$ 会被计算多少次，显然长度为 $a_i$ 的连续 $1$ 会被考虑 $a_i$ 次，所以复杂度小于 $2\sum a_i$，即 $\mathcal  O(n)$


$Code$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 5e5 + 5 ; 
char s[N] ; 
int n, cnt, g[N], ww[N], f[N], w[N], top, Ans ; 
int S(int x) {
	return x * (x + 1) / 2 ; 
}
signed main()
{
	n = gi() ; 
	scanf("%s", s + 1 ) ; 
	s[0] = 0 ; 
	rep( i, 1, n ) {
		if( s[i] != s[i - 1] ) {
			f[++ top] = i, w[top] = 1 ; 
		}
		else ++ w[top] ;  
	}
	rep( i, 1, n ) s[i] -= '0' ; 
	rep( k, 1, n ) {
		int flag = 1 ; cnt = 0 ;
		for( re int j = 1; j <= top; ++ j) {
			if( (s[f[j]] == 1) && (w[j] >= k) ) {
				ww[++ cnt] = w[j], g[cnt] = f[j], flag = 1 ; 
			}
			else if( flag ) 
				flag = 0, ww[++ cnt] = w[j], g[cnt] = f[j], s[f[j]] = 0 ; 
			else ww[cnt] += w[j] ; 
		}
		top = cnt ; 
		for( re int j = 1; j <= top; ++ j) w[j] = ww[j], f[j] = g[j] ; 
		int l = n + 1, id = 0 ;
		for(re int j = 1; j <= top; ++ j) {
			id += w[j] ; 
			if( s[f[j]] ) {
				int len = w[j] ; 
				if( l != (n + 1) ) Ans += (k - 1) * l ; 
				Ans += (len - k + 1) * (id - w[j]) ; 
				Ans += S(len - k + 1) ; 
				l = id - k + 1 ; 
			}
			else {
				if( l == n + 1 ) continue ; 
				Ans += w[j] * l ; 
			}
		}
	}
	cout << Ans << endl ; 
	return 0 ;
}
```

---

## 作者：Imitators (赞：6)

题目大意：给你一个字符串`s` 求$\sum_{l=1}^n\sum_{r=l}^{n}f(l,r)$

其中$f(l,r)$ 表示`s[l,r]`中最长连续的1的长度。

如给出字符串为`s='111011',`$f(1,6)=3$

----

那么对于求原串全体子串的`f`的值，我们可以给出结尾$l$,对于$l$,求出$S_l=\sum_{i=1}^{r}f(i,l)$
那么答案$ans=\sum_{i=1}^{n}S_i$

考虑如何求$S_l$:

如果当前字符`s[l]`为`0`时，那么，$S_l=S_{l-1}$。

否则我们找出从`l`开始的连续的`1`,在`r`处结尾。

![](https://cdn.luogu.com.cn/upload/image_hosting/gl1htov9.png)

如上图所示。

我们可以发现当$S_{x-1}$ 已经计算出时，$S_{x}$只需要把红线框起来的地方$+1$即可。

设左节点为`pre`

那么$S_x=S_{x-1}+x-pre+1$

发现，红线右端点显然是`x`,左端点就是 最靠右的，且后缀长度为`x-l+1`的位置。

由于我们一直向右移动，这个最靠右的东西很好维护。

$\text{code}$

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int N=6e5;
int n;
char s[N];
int bef[N];
long long pro=0,ans=0;
int main()
{
    freopen("res","w",stdout);
    ios::sync_with_stdio(false);
    cin>>n;
    cin>>(s+1);
    for(int i=1;i<=n;i++)
    {
        if(s[i]=='0') ans+=pro;
        else if(s[i-1]!='1')
        {
            int r=i;
            while(s[r+1]=='1') r++;
            for(int x=i;x<=r;x++)
            {
                pro+=x-bef[x-i+1];
                ans+=pro;
            }
            for(int x=i;x<=r;x++)
                bef[r-x+1]=x;
        }
    }
    cout<<ans;
}
```

---

## 作者：xuanxuan001 (赞：4)

又一篇题解。我的解法又和题解的不一样，所以就发了这篇题解。

这题考虑分治，假设目前要求出区间 $[l,r]$ 的答案，那么设 $mid=\lfloor \dfrac{l+r}{2} \rfloor$。

那么先求出 $[l,mid]$ 和 $[mid+1,r]$ 的答案，设统计的答案是所有区间 $[i,j]$ 的 $f$ 值和，下面只需考虑 $l \le i \le mid$ 且 $mid < j \le r$ 的答案。

设 $x$ 为满足区间 $[x,mid]$ 只有 1 且 $l \le x$ 的最小的 $x$，$y$ 为满足区间 $[mid+1,y]$ 且 $y \le r$ 的最大的 $y$。那么先预处理出一个数组 $a_i(l \le i \le r)$：
$$\begin{cases}
f(i,mid)&&i \le mid\\
f(mid+1,j)&&i > mid\\
\end{cases}$$
我们再将这类答案分为三类：

1. $x \le i$ 且 $j \le y$，这部分的答案 $f$ 值即为区间长度，一个式子即可。
1. $x \le i$ 且 $y < j$，这部分考虑枚举 $i$，然后找到最大的 $y < p \le r$ 使得 $a_i \le a_p$，那么对于 $p \le j \le r$，答案为 $a_p$，其余答案为 $a_i$，如果知道了 $p$，那么这个结果可以预处理后缀和然后 $O(1)$ 解决，发现 $p$ 随 $i$ 的升高而单调不升，可以用双指针。

接下来我们将 $a$ 数组的区间 $(mid,y]$ 的每个数加上 $mid-x+1$，然后可以将 $i < x$ 的情况作为一类考虑，不需要再讨论 $y$。

这一类其实和上面的第二类是一样的，只不过 $i$ 的枚举范围变成了 $l \le i < x$，$j$ 和 $p$ 的范围变成了 $mid < p \le r$。

我不知道按照连续 1 段分治，保证每次分的时候分割两端的值不同时为 0 能不能简便一些，但我不想再考虑了。

复杂度 $O(n \log n)$。

代码（为了方便求，我的代码中的 $x$ 比题解中描述的少 1，$y$ 比题解描述的大 1）：

```
#include<cstdio>
#define TY ll
#define MAXN 500002
#define debug if(1)
#define FOR(i,a,b) for(TY i=(a);i<=(b);++i)
#define fOR(i,a,b) for(TY i=(a);i<(b);++i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);--i)
#define rOF(i,a,b) for(TY i=(a);i>(b);--i)
using namespace std;
typedef long long ll;
const TY M=998244353;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(b&1)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n')ch=getchar();return ch;}
TY js(TY a){return a*(a+1)>>1;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10,'\0');putchar(a%10+'0');
	if(ch!='\0')putchar(ch);
}TY n,ans,a[MAXN];char s[MAXN];
void findans(TY l,TY r){
	if(l==r){ans+=s[l]^'0';return;}
	TY mid=l+r>>1,x=l-1,y=r+1,cnt,sum;
	findans(l,mid);findans(mid+1,r);
	a[mid]=cnt=s[mid]-'0';a[mid+1]=s[mid+1]-'0';//处理 a 数组
	ROF(i,mid-1,l){
		if(s[i]=='1')++cnt;
		else cnt=0;
		a[i]=maxn(a[i+1],cnt);
	}FOR(i,l,mid)if(s[i]=='0')x=i;cnt=a[mid+1];
	FOR(i,mid+2,r){
		if(s[i]=='1')++cnt;
		else cnt=0;
		a[i]=maxn(a[i-1],cnt);
	}rOF(i,r,mid)if(s[i]=='0')y=i;
	ans+=js(mid-x)*(y-mid-1)+js(y-mid-1)*(mid-x);//第一类
	rOF(i,mid,x)a[i]+=y-mid-1;
	fOR(i,mid+1,y)a[i]+=mid-x;cnt=r;sum=0;
	FOR(i,x+1,mid){//第二类
		while(cnt>=y&&a[cnt]>a[i])sum+=a[cnt--];
		ans+=sum+a[i]*(cnt-y+1);
	}ROF(i,r,y)a[i]=maxn(a[i],a[y-1]);cnt=r;sum=0;//修改 a 数组
	FOR(i,l,x){//第三类
		while(cnt>mid&&a[cnt]>a[i])sum+=a[cnt--];
		ans+=sum+a[i]*(cnt-mid);
	}
}int main(){
	n=qr();scanf("%s",s+1);
	findans(1,n);qw(ans,'\0');
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：3)

数据结构学傻了属于是。

考虑从前到后扫一遍右端点，用数据结构维护每个左端点的答案。

如果右端点是 $0$，那么这个点自己不可能更新答案，直接算贡献。

如果右端点是 $1$，我们记录最后这一段连续的 $1$ 的左端点 $pos$，考虑他会怎样影响答案。

如果左端点在 $[pos,i)$ 这个区间，那么整个区间全部是 $1$，在右端点添加一个 $1$ 会使答案加一；

如果左端点在 $[1,pos)$ 这个区间，那么最后一段 $1$ 和之前一定有 $0$ 隔开，那么用 $i-pos+1$ 去更新前面的答案；

操作完之后把当前点加入数据结构。

这样总结一下，这个数据需要支持区间加，区间取 $\max$，于是吉司机线段树就好了。因为对每个点的操作一定是先加法后取 $\max$，所以复杂度是 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
#define int long long
int n,ans[500001<<2],minn[500001<<2][2],cnt[500001<<2],tag[500001<<2][2],sum;
string s;
inline int ls(int k)
{
    return k<<1;
}
inline int rs(int k)
{
    return k<<1|1;
}
inline void push_up(int k)
{
    ans[k]=ans[ls(k)]+ans[rs(k)];
    if(minn[ls(k)][0]==minn[rs(k)][0])
    {
        minn[k][0]=minn[ls(k)][0];
        cnt[k]=cnt[ls(k)]+cnt[rs(k)];
        minn[k][1]=min(minn[ls(k)][1],minn[rs(k)][1]);
    }
    if(minn[ls(k)][0]<minn[rs(k)][0])
    {
        minn[k][0]=minn[ls(k)][0];
        cnt[k]=cnt[ls(k)];
        minn[k][1]=min(minn[ls(k)][1],minn[rs(k)][0]);
    }
    if(minn[ls(k)][0]>minn[rs(k)][0])
    {
        minn[k][0]=minn[rs(k)][0];
        cnt[k]=cnt[rs(k)];
        minn[k][1]=min(minn[ls(k)][0],minn[rs(k)][1]);
    }
}
inline void push_down(int k,int l,int r)
{
    int mid=(l+r)>>1;
    if(tag[k][0])
    {
        ans[ls(k)]+=(mid-l+1)*tag[k][0];
        ans[rs(k)]+=(r-mid)*tag[k][0];
        tag[ls(k)][0]+=tag[k][0];
        tag[rs(k)][0]+=tag[k][0];
        minn[ls(k)][0]+=tag[k][0];
        minn[ls(k)][1]+=tag[k][0];
        minn[rs(k)][0]+=tag[k][0];
        minn[rs(k)][1]+=tag[k][0];
        tag[k][0]=0;
    }
    if(tag[k][1])
    {
        if(tag[k][1]>minn[ls(k)][0]&&tag[k][1]<minn[ls(k)][1])
        {
            ans[ls(k)]+=(tag[k][1]-minn[ls(k)][0])*cnt[ls(k)];
            minn[ls(k)][0]=tag[k][1];
            tag[ls(k)][1]=max(tag[ls(k)][1],tag[k][1]);
        }
        if(tag[k][1]>minn[rs(k)][0]&&tag[k][1]<minn[rs(k)][1])
        {
            ans[rs(k)]+=(tag[k][1]-minn[rs(k)][0])*cnt[rs(k)];
            minn[rs(k)][0]=tag[k][1];
            tag[rs(k)][1]=max(tag[rs(k)][1],tag[k][1]);
        }
        tag[k][1]=0;
    }
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        minn[k][0]=minn[k][1]=1ll<<60;
        return;
    }
    int mid=(l+r)>>1;
    build(ls(k),l,mid);
    build(rs(k),mid+1,r);
    push_up(k);
}
void update1(int node,int l,int r,int k,int p)
{
    if(l==r)
    {
        ans[k]=p;
        cnt[k]=1;
        minn[k][0]=p;
        return;
    }
    push_down(k,l,r);
    int mid=(l+r)>>1;
    if(node<=mid)
        update1(node,l,mid,ls(k),p);
    else
        update1(node,mid+1,r,rs(k),p);
    push_up(k);
}
void update2(int nl,int nr,int l,int r,int k)
{
    if(nl>nr)
        return;
    if(l>=nl&&r<=nr)
    {
        ans[k]+=r-l+1;
        ++minn[k][0];
        ++minn[k][1];
        ++tag[k][0];
        return;
    }
    push_down(k,l,r);
    int mid=(l+r)>>1;
    if(nl<=mid)
        update2(nl,nr,l,mid,ls(k));
    if(nr>mid)
        update2(nl,nr,mid+1,r,rs(k));
    push_up(k);
}
void update3(int nl,int nr,int l,int r,int k,int p)
{
    if(nl>nr)
        return;
    if(l>=nl&&r<=nr)
    {
        if(p<=minn[k][0])
            return;
        if(p>minn[k][0]&&p<minn[k][1])
        {
            ans[k]+=(p-minn[k][0])*cnt[k];
            minn[k][0]=p;
            tag[k][1]=max(tag[k][1],p);
            return;
        }
    }
    push_down(k,l,r);
    int mid=(l+r)>>1;
    if(nl<=mid)
        update3(nl,nr,l,mid,ls(k),p);
    if(nr>mid)
        update3(nl,nr,mid+1,r,rs(k),p);
    push_up(k);
}
signed main()
{
    cin>>n>>s;
    s=" "+s;
    build(1,1,n);
    int lst=0,len=0;
    for(int i=1;i<=n;++i)
    {
        if(s[i]=='1')
        {
            ++len;
            update1(i,1,n,1,1);
            update2(lst+1,i-1,1,n,1);
            update3(1,lst,1,n,1,len);
        }
        else
        {
            lst=i;
            len=0;
            update1(i,1,n,1,0);
        }
        sum+=ans[1];
    }
    cout<<sum<<endl;
    return 0;
}
```

---

## 作者：Leap_Frog (赞：3)

### P.S.
![](//xn--9zr.tk/zm)个做法，挺垃圾的，被完全吊打  
upd：现在优化成了 $O(n)$，相当于不同思路  
upd：补充了代码，短期之内是初 python 外的最短解 ![](//xn--9zr.tk/fn)

### Solution.
考虑枚举右端点，用数据结构维护每个点作为左端点的答案。  
每次插入一个 $0$ 没啥用，本质一样。  
如果每次插入一个 $1$，首先把一段极长连续 $1$ 区间加一。  
然后需要对所有其他位置对当前这段长度取最大值。  
然后询问全局和。  

第二步有点恶心，但是发现当前所有左端点的答案肯定递减。  
所以直接用线段树维护之，加上一个线段树二分即可。  

复杂度 $O(n\log n)$

upd：优化到 $O(n)$。  
发现我们每次是对一段后缀赋值。   
**且赋的值每次只会多一！**  
那我们直接维护每次会被更新的长度。  
然后每段极长连续子段结束后直接暴力更新即可。  
线段树被去掉了，复杂度 $O(n)$。  

### Coding.
```cpp
#include<cstdio>
int n,F[500005],nw=0;char ch[500005];long long rs=0,sm=0;
int main()
{
	scanf("%d%s",&n,ch+1);
	for(int i=1;i<=n;rs+=sm,i++) if(ch[i]&1) sm+=i-F[++nw];else for(;nw;nw--) F[nw]=i-nw;
	return printf("%lld\n",rs),0;
}
```

---

## 作者：wgyhm (赞：3)

## 【计数记录】CF1428F Fruit Sequences

### Description

给定一个 01 串 $a$ ，设 $f(l,r)$ 为从 $l$ 到 $r$ 的子串中，最长的全部为 $1$ 的子串的长度。

求 $\sum\limits_{l=1}^n\sum\limits_{r=l}^n f(l,r)$。

$1\le n\le 5\times 10^5$

### Solution

令 $S_i=\sum\limits_{l=1}^i f(l,i)$ ，这样答案 $ans=\sum\limits_{l=1}^n\sum\limits_{r=l}^n f(l,r) =\sum\limits_{i=1}^n S_i$

如果 $a_i=0$ 显然 $S_i=S_{i-1}$

否则我们来计算增加的贡献。

假设一段长度为 $11$ 的序列 `1 1 0 1 1 1 1 0 1 1 1 `，现在 $i=11$。

相较于 $S_{i-1}$ 来说，之前的不变。$f(l,10)$ 到 $f(l,11),6\le l\le 9$ 都是从 $2$ 变成 $3$ ，$f(10,10)$ 到 $f(10,11)$ 从 $1$ 变成 $2$ ，$f(11,11)$ 从 $0$ 变成 $1$ 。换句话说，左端点从 $6$ 开始的每一个子区间的贡献都增加了 $1$。

因为在 $[5,7]$ 中，已经有全为 $1$ 长度为 $3$ 的子区间了。所以 $[9,11]$ 的子区间对其之前的区间没有贡献。所以我们维护一个数组 $\text{pre}$ ，$\text{pre}_i$ 表示后缀连续是 $q$ 长为 $i$ 的子区间最后出现的左端点为 $\text{pre}_i$。而且这个东西也很好维护。

那么 $S_i=S_{i-1}+i-\text{pre}_i$。

### Code

```cpp
#define int long long 
#define maxn 500005
int n;
int a[maxn],f[maxn],pre[maxn];
signed main(){
    rg int i,j,k,sum=0;rg char ch;
    read(n);cin>>ch;
    for (i=1;i<=n;i++) a[i]=ch-'0',ch=getchar();
    for (i=1;i<=n;i++){
    	if (a[i]==0) {f[i]=f[i-1];continue;}
    	for (j=i;j<=n;j++) if (!a[j]) break;k=j-1;
    	for (j=i;j<=k;j++) f[j]=f[j-1]+j-pre[j-i+1];
    	for (j=i;j<=k;j++) pre[k-j+1]=j;
    	i=k;
	}
	for (i=1;i<=n;i++) sum+=f[i];
	printf("%lld",sum);
    return 0;
}
```

   



---

## 作者：intel_core (赞：2)

将答案的求和式从值域角度考虑，只需求出满足 $f(l,r)=k$ 的 $l,r$ 个数 $c_k$。

转换为 $c_k$ 的前缀和数组 $t_k$，表示 $f(l,r) \ge k$ 的个数。

从小到大依次扫每个 $k$，如果一段连续为 `1` 的极长子串长度不够 $k$，那么可以把这个子串全体换成 `0`。

现在的字符串有若干段 `1`，如果一个子串包含了一整段的 `1` 一定满足 $f(l,r) \ge k$。

接着考虑不包含完整 `1` 段的子串。

这种子串一定夹在两个 `1` 连通块中间；左右端点可以取的范围知道，可以用组合数求出不满足条件的个数。

因为求 $t_k$ 的时候最多有 $\frac{n}{k}$ 个长度 $\ge k$ 的 `1` 串；所以复杂度 $O(n \times \sum_{i=1}^n)=O(n \ln n)$。 

---

## 作者：w4p3r (赞：2)

~~我是笨比，受CF1458F的影响，打vp时写了一个复杂无数倍的分治~~

如大部分分治题一样的，考虑$l \le l' \le mid,mid<r' \le r$的$l',r'$的答案和。

我们枚举$r'$，可以发现对于所有$l'$可以分成至多3段（假设为三类不同的贡献）：

1.最长的$1$段横跨$mid$。

2.最长的$1$段完全在$mid$左边。

3.最长的$1$段完全在$mid$右边。

并且若三段都存在，这三段的顺序一定是$2,1,3$。但是发现并不好求每一段的端点（因为第$1$类贡献和$l',r'$都有关），于是我们退而求其次维护下面两个指针：

（假设$v_{x,i}$表示$l'=x$时第$i$类的贡献）

$t1:$对于$x \in [l,t1]$，满足$v_{t,2}>=v_{t,1}$

$t2:$对于$x \in [t2,mid]$，满足$v_{t,3}>=v_{t,1}$

可以发现这两个指针都是有单调性的，于是可以分别维护，然后可以分成两种情况：

$1.t1<t2$：此时，$l'$分成的三段的端点都已经已知，直接求即可。（注意第$1$类贡献是一个等差数列加上一些相等的值）

$2.t1 \ge t2$：此时，可以确定第$1$类并不存在，但是我们并不能确定第$2$类贡献和第$3$类贡献的分界点，可以考虑二分求出。

~~（这个东西其实应该也可以维护一个类似的指针，但我偷懒不想写了qaq）~~

这样就可以A掉本题了，时间复杂度$O(nlog^2n)$

```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register ll
#define fr first
#define sd second
#define pa pair<ll,ll>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define MEM(a) memset(a,0,sizeof(a))
#define N 500010
#define mid ((l+r)>>1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline ll lowbit(ll x){return x&(-x);}
ll n,ans,tl,tr;
char s[N];
ll g[N],a[N],sum[N];
inline ll qval(ll l,ll r)
{
	r=min(r,tr);l=max(l,tl);
	return r-l+1;
}//第1类贡献
void Solve(ll l,ll r)
{
	if(l==r){ans+=a[l];return ;}
	REP(i,mid,l)
	{
		if(i==mid){g[i]=a[i];continue;}
		else g[i]=a[i]?g[i+1]+1:0;
	}
	REP(i,mid-1,l)g[i]=max(g[i],g[i+1]);//第2类贡献
	FOR(i,l,mid)if(i==l)sum[i]=g[i];else sum[i]=sum[i-1]+g[i];
	FOR(i,mid+1,r)
	{
		if(i==mid+1){g[i]=a[i];continue;}
		else g[i]=a[i]?g[i-1]+1:0;
	}
	FOR(i,mid+2,r)g[i]=max(g[i],g[i-1]);//第3类贡献
	tl=mid+1,tr=mid;
	while(a[tl-1]==1&&tl>l)tl--;
	while(a[tr+1]==1&&tr<r)tr++;//tl,tr用来求第1类贡献的
	ll t1=mid,t2=mid+1;
	FOR(R,mid+1,r)
	{
		while(g[R]>=qval(t2-1,R)&&t2>l)t2--;
		while(qval(t1,R)>=g[t1]&&t1>=l)t1--;
		if(t2>t1)
		{
			ans+=(t1>=l?sum[t1]:0)+(mid-t2+1)*g[R];
			ll sx=qval(t2-1,R),mx=qval(tl,R),xs=t2-tl;
			ans+=(sx+mx)*xs/2;
			ans+=(tl-t1-1)*mx;
		}//情况1
		else
		{
			ll l1=t2,r1=t1,pos=l1-1;
			while(l1<=r1)
			{
				ll Mid=(l1+r1)>>1;
				if(g[Mid]>=g[R])pos=Mid,l1=Mid+1;
				else r1=Mid-1;
			}
			ans+=(pos>=l?sum[pos]:0)+(mid-pos)*g[R];
		}//情况2
	}
	Solve(l,mid);Solve(mid+1,r);
	
}
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();scanf("%s",s+1);
	FOR(i,1,n)a[i]=s[i]-'0';
	Solve(1,n);
	cout<<ans<<'\n';
	return 0;
}
//gl



```
**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**


---

## 作者：gyh20 (赞：1)

对于每一段连续的 $1$ 单独考虑，则答案分为 $4$ 部分。

$1.$ 内部不含边界（不含两个边界点的内部情况）（不清楚能不能 $O(1)$ 算但暴力 $O(n)$ 算没有关系。

$2.$ 每一个非整串的前缀被计算多少次，找到前方第一个连续值大于它长度的，则这个区间内所有串都能计算。

$3.$ 后缀，定义同上，但大于应变为大于等于，否则同时包含这两个串的会被算两遍。

$4.$ 整串，同上定义，但需要同时求出左边界和右边界。

以上所有的"边界"都可以正反两个单调栈求出，总时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,a[1000002],b[1000002],f[2][1000002],stk[1000002],l[1000002],r[1000002],tp;
long long ans;
char s[1000002];
signed main(){
	n=read();
	scanf("%s",s+1);
	for(re int i=1;i<=n;++i)if(s[i]=='1')f[0][i]=f[0][i-1]+1;
	for(re int i=n;i;--i)if(s[i]=='1')f[1][i]=f[1][i+1]+1;
	for(re int i=1;i<=n;++i){
		if(s[i]=='1'){
			re int j=i;
			while(s[j]=='1')++j;--j;
			re int pos=tp;
			for(re int k=i;k<j;++k){
				while(pos&&f[1][stk[pos]]<=k-i+1)--pos;
				if(pos)ans+=1ll*(k-i+1)*(i-stk[pos]);
				else ans+=1ll*(k-i+1)*i;
			}
			while(pos&&f[1][stk[pos]]<=j-i+1)--pos;
			l[i]=stk[pos];
			for(re int k=i;k<=j;++k){
				while(tp&&f[1][k]>=f[1][stk[tp]])--tp;
				stk[++tp]=k;
			}
			i=j+1;
		}
	}tp=0;
	for(re int i=n;i>=1;--i){
		if(s[i]=='1'){
			re int j=i;
			while(s[j]=='1')--j;++j;
			re int pos=tp;
			for(re int k=i;k>j;--k){
				while(pos&&f[0][stk[pos]]<i-k+1)--pos;
				if(pos)ans+=1ll*(i-k+1)*(stk[pos]-i);
				else ans+=1ll*(i-k+1)*(n-i+1);
			}
			while(pos&&f[0][stk[pos]]<i-j+1)--pos;
			r[j]=(pos?stk[pos]:n+1);
			for(re int k=i;k>=j;--k){
				while(tp&&f[0][k]>=f[0][stk[tp]])--tp;
				stk[++tp]=k;
			}
			i=j-1;
		}
	}
	for(re int i=1;i<=n;++i){
		if(s[i]=='1'){
			re int j=i;
			while(s[j]=='1')++j;--j;
			for(re int k=1;k<=j-i-1;++k)ans+=1ll*k*(j-i-1-k+1);
			ans+=1ll*(i-l[i])*(r[i]-j)*(j-i+1);
			i=j+1;
		}
	}
	printf("%lld",ans);
}
```


---

## 作者：奇米 (赞：1)

# 题解 - $\mathrm{CF1428F}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/CF1428F)

## $\mathrm{Sol}$

考虑对于每个 $1$ 单独算贡献。

假设 $a_i=1$ 那么以其为结尾的连续 $1$ 的长度为 $l$，那么在 $[1,i-l]$ 的区间找一个最远的 $j$ 满足 $a_j=1$ 且以其为起头的 连续 $1$ 段的长度 $L\leq l$。这个我们可以用线段树维护区间 $\max$ 标记来轻松实现。

假设我们找到了 $j$ 考虑如何加入贡献，显然 $[j,i-l]$ 这段区间的贡献要加 $l$ ，$[i-l+1,i]$ 这段区间整体加 $1$（每个下标 $i$ 作为一个个体）。

这样我们只要维护区间加，区间 $\max$ 就可以了。时间复杂度 $O(n\log n)$

## $\mathrm{Code}$

```cpp
const int N=5e5+5;

int n,m,tr[N*4],laz[N*4],tr2[N*4],tag[N*4];
int ans,las;
char a[N];

inline void pd(int x,int l,int r,int t1,int t2) 
{
	if(t1) tag[x]=0,tr[x]=(r-l+1)*t1,tr2[x]=laz[x]=t1;
	if(t2) tr[x]+=(r-l+1)*t2,tag[x]+=t2,tr2[x]+=t2; 
}

inline void pushdown(int x,int l,int r) 
{
	if(laz[x]||tag[x]) 
	{
		int mid=l+r>>1;
		pd(x<<1,l,mid,laz[x],tag[x]);
		pd(x<<1|1,mid+1,r,laz[x],tag[x]);
		laz[x]=tag[x]=0;
	}
}

inline int query(int x,int l,int r,int goal) 
{
	if(l==r) return l;
	int mid=l+r>>1;
	pushdown(x,l,r);
	if(tr2[x<<1|1]>=goal) return query(x<<1|1,mid+1,r,goal);
	else return query(x<<1,l,mid,goal);
}

inline void add(int x,int l,int r,int ll,int rr,int v) 
{
	if(ll>r||rr<l) return;
	if(ll<=l&&r<=rr) 
	{
		tr[x]+=(r-l+1)*v,tag[x]+=v,tr2[x]+=v;
		return;
	}
	int mid=l+r>>1;
	pushdown(x,l,r);
	add(x<<1,l,mid,ll,rr,v),add(x<<1|1,mid+1,r,ll,rr,v);
	tr[x]=tr[x<<1]+tr[x<<1|1];
	tr2[x]=max(tr2[x<<1],tr2[x<<1|1]);
}

inline void Add(int x,int l,int r,int ll,int rr,int v) 
{
	if(ll>r||rr<l) return;
	if(ll<=l&&r<=rr)
	{
		tr[x]=(r-l+1)*v,tr2[x]=v,laz[x]=v;
		tag[x]=0;
		return;
	}
	int mid=l+r>>1;
	pushdown(x,l,r);
	Add(x<<1,l,mid,ll,rr,v),Add(x<<1|1,mid+1,r,ll,rr,v);
	tr[x]=tr[x<<1]+tr[x<<1|1];
	tr2[x]=max(tr2[x<<1],tr2[x<<1|1]);
}

signed main()
{
	scanf("%d",&n);
	scanf("%s",a+1);
	For(i,1,n) 
	{
		if(a[i]=='1') 
		{
			if(!las) las=i;
			int can_reach=query(1,1,n,i-las+1); 
			add(1,1,n,las,i,1);
			if(can_reach<las) Add(1,1,n,can_reach,las-1,i-las+1);
		}
		else las=0;
		ans+=tr[1];
	}
	io.write(ans),puts("");
	return 0;
}
```


---

## 作者：TernaryTree (赞：0)

模拟赛考了这个题我直接扔一个分治上去还调了半天，属于是没思维的套路学傻选手。

分治每次计算 $l\in [L,mid]$，$r\in [mid+1,R]$ 的答案。前缀后缀预处理 $\Theta(n)$ 的信息可以 $\Theta(1)$ 合并得到 $[l,r]$ 的答案。不妨设 $mid$ 往左极长的连续 $1$ 个数为 $u$，$mid+1$ 往右为 $v$；$p_i$ 表示 $[i,mid]$ 的极长 $1$ 个数，$q_j$ 表示 $[mid+1,j]$ 的极长 $1$ 个数。有

$$
f(i,j)=\begin{cases}
j-i+1&(mid-u+1\le i\land j\le mid+v) \\
\max(v + mid + 1 - i, q_j)&(mid-u+1\le i\land mid+v<j) \\
\max(p_i, u + j - mid)&(i\lt mid-u+1\land j\le mid+v) \\
\max(u + v, p_i, q_j)&(i\lt mid-u+1\land mid+v<j) \\
\end{cases}
$$

那么我们从大到小枚举 $i$，分讨四种情况：

- 第一种情况：等差数列求和，简单的。
- 第二种情况，注意到 $q_j$ 不减，$v+mid+1-i$ 单增，拿个指针扫一下，顺便维护 $q$ 的和。
- 第三种情况：由于枚举 $i$，所以 $p_i$ 固定，可以算出两种值 $j$ 的分界点，然后又是等差数列求和；
- 第四种情况：式子看成 $\max(\max(u+v,p_i),q_j)$，与第二种情况一样拿个指针扫一下。

注意 $j$ 的范围问题。

时间复杂度 $T(n)=2T(n/2)+\Theta(n)=\Theta(n\log n)$。

---

## 作者：JiaY19 (赞：0)

使用了一种和大多数题解不同的做法。

虽然是带 $log$ 的。

### 思路

首先考虑如何求一个固定左端点的答案。

我们发现，每个答案会随着右端点的递增单调不降。

而每个答案在增加时会形成若干个区间。

例如：

```
11101010111111
```

我们答案增加的区间即为：

```
11100000000111
```

可以发现，这个区间就是不断往前找到第一个长度大于当前极长连续段的极长连续段。

那么我们对于每个点统计出往后的全一极长连续段的长度。

就可以将所有询问简单的用堆维护。

### Code


```cpp
/**
 * @file 1428F.cpp
 * @author mfeitveer
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define mp(x, y) make_pair(x, y)
#define fro(i, x, y) for(int i = (x);i <= (y);i++)
#define pre(i, x, y) for(int i = (x);i >= (y);i--)
#define dbg cerr << "Line " << __LINE__ << ": "
#define EVAL(x) #x " = " << (x)

typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<int, int> PII;

bool ed;

const int N = 1000010;
const int mod = 998244353;

int n, m, a[N], sz[N], len[N], sum[N];
string s;

inline void solve()
{
	cin >> n >> s;
	fro(i, 1, n) a[i] = s[i - 1] - '0';
	fill(sz + 1, sz + n + 1, 1);
	fro(i, 1, n) if(a[i])
	{
		int j = i; while(a[j + 1]) j++;
		fro(k, i, j) len[k] = j - k + 1; i = j;
	}
	priority_queue<PII, vector<PII>, greater<PII>> q;
	fro(i, 1, n)
	{
		while(!q.empty() && q.top().x < len[i])
		{
			int x = q.top().y;
			sum[i + len[x]] += sz[x];
			sum[i + len[i]] -= sz[x];
			sz[i] += sz[x], q.pop();
		}
		q.emplace(len[i], i);
		sum[i] += 1, sum[i + len[i]] -= 1;
	}
	i64 ans = 0, num = 0, all = 0;
	fro(i, 1, n) num += sum[i], all += num, ans += all;
	cout << ans << "\n";
}

bool st;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	double Mib = fabs((&ed-&st)/1048576.), Lim = 250;
	assert(Mib<=Lim), cerr << " Memory: " << Mib << "\n";
	solve();
	return 0;
}

```

---

## 作者：Galex (赞：0)

好像没人和我的方法一样，那就发个题解吧。

首先 $f(l,r)$ 显然是可以 $O(n\log n)$ 预处理，$O(1)$ 算的，用 st 表维护 $f(i,j)$，左端最长连续 $1$ 个数，右端最长连续 $1$ 个数即可。

记 $f_i=\sum_{j=1}^i f(j,i)$，即所有右端点为 $i$ 的区间的答案的和。

$s_i=0$ 时，显然 $f_i=f_{i-1}$。所有接下来只考虑 $s_i=1$ 的情况。

我们发现 $f_i$ 与 $f_{i-1}$ 有一定关联。显然对于 $\forall j \in [1,i-1]$，有 $f(j,i)-f(j,i-1)\in[0,1]$。我们只需找到 $f(j,i)\not = f(j,i-1)$ 的 $j$ 的个数即可算出 $f_i$。具体来讲，设 $k$ 表示以 $i-1$ 结尾的连续的 $1$ 的个数，则 $f_i$ 比 $f_{i-1}$ 多的就是那些满足最大连续段在区间的最右边的区间个数以及 $f(i,i)$。

我们又发现若 $i$ 固定，则对于所有的 $0<j<i$，$f(j,i-1)$ 不降。所以所有满足 $f(j,i-1)\not=f(j,i)$ 的 $j$ 一定恰好可以组成一个区间 $[l,r]$。又注意到 $j=i-1$ 一定满足条件，所以 $r=i-1$。而 $l$ 显然是可以二分出来的。

总复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n;
char s[500005];

#define pw(x) (1 << (x))

int st[500005][20];
int l[500005][20], r[500005][20];

void init() {
	for (int i = 1; i <= n; i++)
		l[i][0] = r[i][0] = st[i][0] = s[i] == '1';
	for (int j = 1; pw(j) <= n; j++)
		for (int i = 1; i + pw(j) - 1 <= n; i++) {
			st[i][j] = max(max(st[i][j - 1], st[i + pw(j - 1)][j - 1]), r[i][j - 1] + l[i + pw(j - 1)][j - 1]);
			l[i][j] = l[i][j - 1] + (l[i][j - 1] == pw(j - 1)) * l[i + pw(j - 1)][j - 1];
			r[i][j] = r[i + pw(j - 1)][j - 1] + (r[i + pw(j - 1)][j - 1] == pw(j - 1)) * r[i][j - 1];
		}
}

int qry(int x, int y) {
	int i = log(y - x + 1) / log(2);
	return max(max(st[x][i], st[y - pw(i) + 1][i]), r[x][i] + l[y - pw(i) + 1][i] - (x - y + pw(i) * 2 - 1));
}

signed main() {
	scanf("%lld\n%s", &n, s + 1);
	init();
	int sum = 0, ans = 0, lst = 0;
	for (int i = 1; i <= n; i++) {
		int l = 0, r = max(i - 1, 1ll), num = lst;
		while (r - l > 1) {
			int mid = (l + r) >> 1;
			qry(mid, i - 1) == min(sum, i - mid) ? r = mid : l = mid;
		}
		if (s[i] == '1')
			num += i - r + 1;
		ans += num, lst = num;
		sum = s[i] == '1' ? sum + 1 : 0;
	}
	printf("%lld", ans);
	return 0;
}
```


---

