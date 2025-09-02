# [POI 2006] OKR-Periods of Words

## 题目描述

一个字符串是由有限个小写英文字母组成的序列。特别地，它可以是一个空序列，即由 0 个字母组成的序列。我们用 $A=BC$ 表示字符串 $A$ 是通过连接字符串 $B$ 和 $C$（按此顺序）得到的（即一个接一个地写在一起，没有任何空格等）。字符串 $P$ 是字符串 $A$ 的前缀，如果存在一个字符串 $B$，使得 $A=PB$。换句话说，$A$ 的前缀是 $A$ 的初始片段。此外，如果 $P\neq A$ 且 $P$ 不是一个空字符串，我们称 $P$ 是 $A$ 的一个真前缀。

字符串 $Q$ 是 $A$ 的周期，如果 $Q$ 是 $A$ 的一个真前缀且 $A$ 是字符串 $QQ$ 的前缀（不一定是真前缀）。例如，字符串 abab 和 ababab 都是字符串 abababa 的周期。字符串 $A$ 的最大周期是其周期中最长的一个，或者如果 $A$ 没有任何周期，则为一个空字符串。例如，ababab 的最大周期是 abab。abc 的最大周期是空字符串。

任务：编写一个程序：

从标准输入读取字符串的长度和字符串本身，计算其所有前缀的最大周期长度的总和，将结果写入标准输出。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
8
babababa```

### 输出

```
24```

# 题解

## 作者：Ofnoname (赞：136)

`2019. 10. 26: 换了一张图`

这是一道让我们深入了解KMP算法精髓的好题。

题目中的“匹配前缀”我们可以这样理解：在A的前缀中，把这个前缀再叠加一遍后就把A包括进来，如图：

![](https://s2.ax1x.com/2019/10/26/K0Iszt.png)

那么，"abcabcab"的最长匹配子串应该是"abcabc"，长度为6。

我们设第一个图中字符串为S，第二个字符串为SS，显然有S[6..8]=SS[6..8]=SS[1..2]=S[1..2]。于是我们得到规律，匹配前缀子串满足KMP算法中“前缀等于后缀”的性质，我们要使子串最长，那么这个匹配长度应该尽可能小。比如对于S来说,next[8]应该为5，表示S[1..5]和S[4..8]是匹配的，但我们选择的是最短的匹配长度short[8]=2,S[1..2]=S[7..8]，而答案就是8-short[8]=6。

但是KMP只能求出每个前缀串的最长匹配长度，如果要求出最短匹配长度，我们可以一直递推next[i],next[next[i]]...，直到为0. 熟悉的KMP本质的人都应该知道为什么，这里举一个例子。

在S中，next[8]=5,而next[5]=2，next[2]=0了，所以next[5]=2就是8的最短匹配长度，将8-2累计到答案中即可。

最后，类似求next时的递推方法，我们可以递推short来提高效率。比如在上例中,我们得到short[8]=2后，就直接将next[8]修改为2，这样8以后的数字如果递推到8了就可以直接跳到next[2]=0，而不用跳到next[5]这里。

**答案记得long long，否则只有40分。**

```cpp
#include <bits/stdc++.h>
#define MAX (1000000+50)
using namespace std;

int size,nxt[MAX];
char s[MAX];
unsigned long long ans;//记得开long long

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cin>>size>>(s+1);
	for (register int i=2,j=0; i<=size; i++)
	{
		while (j && s[i]!=s[j+1]) j=nxt[j];
		if (s[i]==s[j+1]) j++; nxt[i]=j;
	}//KMP求解next数组
	for (register int i=2,j=2; i<=size; i++,j=i)
	{
		while (nxt[j]) j=nxt[j]; //递推求最短匹配长度
		if (nxt[i]) nxt[i]=j; //修改next[i]的值
		ans+=i-j;//统计答案
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：Orion545 (赞：99)

# 广告

[蒟蒻のblog](http://www.cnblogs.com/dedicatus545/p/8900630.html)

# 思路

先把题面转成人话：

对于给定串的每个前缀i，求最长的，使这个字符串重复两边能覆盖原前缀i的前缀（就是前缀i的一个前缀），求所有的这些“前缀的前缀”的长度和

利用$next$的性质：前缀$i$的长度为$next[i]$的前缀和后缀是相等的

这说明：如果有i一个公共前后缀长度为j，那么这个前缀i就有一个周期为i-j

见下图

![](http://images.cnblogs.com/cnblogs_com/dedicatus545/1199264/o_POI2006%20p1.png)

显然图中蓝色线段是黑色线段的一个周期

那么接下来的问题就容易了：

先求出$next$数组

对于每个前缀$i$，令$j=i$，然后在$j>0$的情况下令$j=next[j]$，最小的$j$就是答案，此时$ans+=i-j$

一个优化：求出$j$以后，令$j=fail[i]$，这样能加快递归速度（相当于记忆化了）

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
char a[1000010];int n,fail[1000010];
int main(){
    scanf("%d",&n);scanf("%s",a);int i,j;ll cnt=0;
    fail[0]=fail[1]=0;j=0;
    for(i=1;i<n;i++){//求解next
        while(j&&(a[i]!=a[j])) j=fail[j];
        j+=(a[i]==a[j]);fail[i+1]=j;
    }
    for(i=1;i<=n;i++){
        j=i;
        while(fail[j]) j=fail[j];
        if(fail[i]!=0) fail[i]=j;//记忆化
        cnt+=i-j;
    }
    printf("%lld",cnt);
}
```

---

## 作者：RPChe_ (赞：34)

让窝来贡献一个$O(n\log n)$算法。~~讲解很详细哦~~
****************************
联系kmp算法中的next数组和题目中提到的周期，我们可以发现一个结论：一个字符串的最大周期长度就是这个字符串的长度减去它最短的公共前后缀长度，而且这个公共前后缀的长度必须小于等于字符串长度的一半，否则不存在周期。

举个简单的例子，假设我们要求串$S$的某个周期长度，且这个串存在一个小于其长度一半的公共前后缀T，如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/d0nowb03.png)

因为$ab$段与$cd$段一样，我们可以把$ac$段子串向右移动到$a$点与$c$点重合，这样就得到了如下一个新串$ae$：
![](https://cdn.luogu.com.cn/upload/image_hosting/zdm0llvo.png)

在这个新串中，$ac$与$ce$对应，$ab$与$cd$对应，$bc$与$de$对应，那么我们可以发现，$ac$的长度就是这个周期的长度，因为$ac$是$S$的前缀，且$S$是$ac$+$ac$，即$ae$的前缀。所以接下来我们要使得这个$ac$的长度尽量长，就是$cd$的长度尽量短，那么问题就转化为了求取$S$的最短公共前后缀长度。

这个很好办，我们只需要不断往前跳next数组寻找合法解就好了。

注意到以上的论述建立在一个前提上：$ab$的长度小于等于$S$的一半，所以这个最短公共前后缀的长度还必须小于等于字符串长度的一半，否则无解。

接下来就是代码实现了。我一开始就暴力跳next数组，结果TLE了几个点。但是窝太菜了，根本没有想到记忆化，而是想到了一个非常优雅的暴力——倍增。

如果不知道倍增，可以去研究一下倍增求LCA的算法，这里不再赘述。

于是我们便得到了以下代码——
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
#define maxn 1000005
using namespace std;

int len,nxt[maxn],f[maxn][21];
long long ans;
string s;

void kmp() {
	nxt[0]=-1;
	f[1][0]=0;
	int j=-1;
	rep(i,0,len-1) {
		while(j>-1&&s[j+1]!=s[i+1]) j=nxt[j];
		if(s[j+1]==s[i+1]) j++;
		nxt[i+1]=j;
		f[i+2][0]=j+1;//因为倍增数组涉及到以字符的位置作下标，为了方便处理，我们把字符的位置加1
	}
}//kmp模板

void pretreat() {
	rep(i,0,len-1) {
		rep(j,1,20) {
			f[i+1][j]=f[f[i+1][j-1]][j-1];
		}
	}
}//预处理出倍增数组

void check() {
	rep(i,0,len-1) {
		int x=i+1;
		for(register int j=20;j>=0;j--) {
			if(f[x][j]) {
				x=f[x][j];
			}
		}
		if(i+1==x||x>i+1>>1) continue;//判断解是否合法
		ans+=(long long)(i+1)-x;//更新答案
	}
}//倍增找到最短公共前后缀长度

int main() {
	ios::sync_with_stdio(false);
	cin>>len;
	cin>>s;
	kmp();
	pretreat();
	check();
	cout<<ans;
	return 0;
}
```


---

## 作者：tzc_wk (赞：10)

### 一道 $KMP$ 入门的好题

题意：对于每一个前缀 $i$，那么我们要找到一个$j\ (1 \leq j \leq i)$，满足 $s_1s_2\dots s_i$ 是 $s_1s_2\dots s_js_1s_2\dots s_j$ 的前缀。

首先，题意说得有些隐晦，先把它翻译成我们熟悉的语言：因为$s_1s_2\dots s_i$ 是 $s_1s_2\dots s_js_1s_2\dots s_j$ 的前缀，所以$T1=s_{j+1}s_{j+2}\dots s_i$ 也是 $T2=s_1s_2\dots s_j$ 的前缀。又根据我们要找最大的 $j$，因此我们希望 $i-j$ 的值，也就是 $T2$ 的长度，尽可能的小。也就是说，我们要对于每一个前缀 $i$，找出最小公共前后缀的长度 $j$，那么 $i-j$ 就是前缀 $i$ 的最大周期。

乍一看，这和 $KMP$ 中 $next$ 数组的含义几乎完全一样，只不过此处是**最小**前后缀。假设我们在计算前缀 $i$ 的值，我们开一个指针 $j$，初始值为 $i$，不断令 $j=next_j$，直到 $next_j=0$，此时的 $j$ 就是我们要求的值。

但是仅仅这样做是过不了的（我们会发现上述过程中 $j$ 变化的次数最高可达 $\mathcal O(n)$ 级别，这样最坏时间复杂度会退化为 $\mathcal O(n^2)$），我们需要进行一个小小的优化，每算出来一个前缀 $i$ 的答案 $j$ 就令 $next_i=j$，相当于记忆化。

$code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define int long long
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
int n,nxt[1000005];
char s[1000005];
inline void getnext(){//求next数组
	int j=0;
	nxt[1]=0;
	for(int i=2;i<=n;i++){
		while(j!=0&&s[j+1]!=s[i])	j=nxt[j];
		if(s[j+1]==s[i])			j++;
		nxt[i]=j;
	}
}
signed main(){
	cin>>n>>s+1;
	getnext();
	int ans=0;
	fz(i,1,n){
		int j=i;
		while(nxt[j])	j=nxt[j];//往前跳
		if(nxt[i])		nxt[i]=j;//记忆化
		ans+=i-j;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Clever_Jimmy (赞：6)

【洛谷】P3435 [POI2006]OKR-Periods of Words

### 题意简述：

给定一个字符串 $S$，求：

$$
\sum_{i = 1}^{n}\max\limits_{S_i\sqsubset S_j^2}\{j\}
$$

$1 \le \left|S\right| \le 10^6$。

[题目链接](https://www.luogu.com.cn/problem/P3435)

### 解题思路：

我们单独考虑某个字符串 $S_i \sqsubset S$，则 $\forall k \in \pi^{\star}[i]$，都有 $S_{i - k} \sqsubset S_i^2$。

考虑让 $i - k$ 最大（题目要求），即让 $k$ 最小，也就是我们 $\forall i \in [1, n]$，求 $\pi^{\star}[i]$ 中的非零最小值。

对每个 $i \in [1, n]$ 都求一次最小值，会被卡成 $O(\left|S\right|^2)$，考虑记忆化。

我们每次求出来了 $\pi^{\star}[i]$ 中的非零最小值 $k$ 时，直接令 $\pi[i] \gets k$。

答案即为（之后的）
$$
\sum_{i = 1}^{n}(i - \pi[i])
$$

### 参考代码：

```cpp
#include <bits/stdc++.h>
#define LL long long

const int N = 1e6 + 5;

int n, pi[N];
LL ans;
char str[N];

void calcPi() {
	for(int i = 2, k = 0; i <= n; ++i) {
		while(k > 0 && str[k + 1] != str[i])
			k = pi[k];
		if(str[k + 1] == str[i])
			++k;
		pi[i] = k;
	}
}

int32_t main() {
	scanf("%d", &n);
	scanf("%s", str + 1);
	calcPi();
	for(int i = 1; i <= n; ++i) {
        int k = i;
        while(pi[k])
        	k = pi[k];
        if(pi[i])
        	pi[i] = k;
        ans += i - k;
    }
    printf("%lld", ans);
	return 0;
}
```


---

## 作者：SamariumPhosphide (赞：4)

### 题意

这道题目的题面不是给人看的/kk

对于一个长度为 $k$ 的字符串 $A$ 的每个前缀 $\text{pre}(A, i)$，求出最长的字符串 $S_i$ 使得 $|S_i|<i$ 且 $A_i$ 是若干个 $S_i$ 连接在一起的前缀。求出 $|S_1|+ |S_2| + \cdots + |S_k|$。

### 题解

首先考虑 $S_i$，必然是 $\text{pre}(A,i)$ 的一个循环节，而每个循环节都对应着一个 $\text{Border}$，同时 $\text{Border}$ 的长度与该循环节长度的和为原串长度。因此我们可以从 $\text{Border}$ 角度考虑此问题，找出最短的 $\text{Border}$ 即找出最长的循环节。

可以运用失配树的思想，在失配树中一个节点的最短 $\text{Border}$ 为其到根节点的路径上除根节点外离跟根节点最近的点。

所以直接使用并查集维护这棵树即可。

### 细节

注意并查集中有一点比较容易出错。在 $\text{find}$ 函数中当 $\text{fa}[x]=0$ 时返回而不是 $\text{fa}[x]=x$ 时返回。（因为根节点不统计在内）

[Code Here](https://www.luogu.com.cn/paste/jh430sxt)

---

## 作者：whyl (赞：4)

发现这道水题，网上还没有题解用哈希。

~~（本萌新不会kmp）
~~

那我就补发一篇hash的题解

其实判断前缀很好想

只要考虑怎么判断后缀即可

看A是不是QQ的前缀

就是判断A-Q与Q的对应部分是不是相等即可

答案具有单调性，满足二分条件

用线段树维护区间最值即可

时间复杂度（nlogn）

注意哈希要用unsigned long long的自然溢出

unsigned int 很容易被卡hash WA。。。

字符串里hash还是很好用的

但是KMp千万不要像我这种萌新一样不会啊。。。。

```cpp
//code by luotc
#include<bits/stdc++.h>

using namespace std;

#define mid ((l+r)>>1)
#define lson k<<1,l,mid
#define rson k<<1|1,mid+1,r
#define ull unsigned long long 

const int maxn=1e6+5,base=131;
int n,tree[maxn<<2];
ull hsh[maxn],bas[maxn];
char s[maxn];
ull ans;

inline bool check(int ll,int rr){
	return (hsh[rr-ll+1]==hsh[rr]-hsh[ll-1]*bas[rr-ll+1]);
}

inline void update(int k,int l,int r,int L,int R,int dat){
	if(L==l&&r==R){
		tree[k]=max(tree[k],dat);
		return;
	}
	if(R<=mid) update(lson,L,R,dat);
	else if(L>mid) update(rson,L,R,dat);
	else update(lson,L,mid,dat),update(rson,mid+1,R,dat);
}

inline int query(int k,int l,int r,int pos){
	if(l==r) return tree[k];
	if(pos<=mid) return max(tree[k],query(lson,pos));
	else return max(tree[k],query(rson,pos));
}

int main(){
	cin>>n;
	cin>>(s+1);
	for(int i=1;i<=n;i++)
		hsh[i]=hsh[i-1]*base+s[i]-'a';
	bas[0]=1;
	for(int i=1;i<=n;i++) bas[i]=bas[i-1]*base;
//	cout<<check(3,4)<<endl;
	for(int i=1;i<n;i++){
		int l=i+1,r=min(n,2*i),ret=0;
		while(l<=r){
			if(check(i+1,mid)) ret=mid,l=mid+1;
			else r=mid-1;
		}
	//	cout<<i<<' '<<ret<<endl;
		if(ret!=0) update(1,1,n,i+1,ret,i);
	}
	for(int i=2;i<=n;i++) ans+=query(1,1,n,i);
	cout<<ans<<endl;
	return 0;
}
```




---

## 作者：shadowice1984 (赞：2)

我们发现A需要是QQ的前缀才行

发现应该前缀是这样的一个图

CCCBBBBBBCCCBBBBB

XXXAAAAAANNN

设CCCBBBBB为原来的Q

上面的字符串是QQ，底下的是A串

发现因为标号为B的字符串并不对A是否是QQ的前缀有影响

只要标号为X的部分等于标号为N的部分

A就是QQ的前缀，Q的长度等于A的长度-标号为X或N的长度

所以我们要求的是X或N的最小长度，且不得等于零

就是A的最小公共前缀后缀长度（不为零），和next的定义刚好相反

那么从A的next开始枚举，每次枚举next的next，就可以遍历

A所有的公共前缀后缀，然后取最小的就可以了

但是这样做是会T的，我们发现每次转移时会用到上一个点的

解，而且如果这个解已被求出它就是恒定的

（具体的话把我代码里的注释打开，就可以非常清楚的看到原理）

那么把nxt更新成这个问题的解，就可以保存了

上代码~





```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int nxt[1000010];
char mde[1000010];
int n;long long res;
void gnxt()//求nxt
{
    nxt[1]=0;
    for(int i=2;i<=n;i++)
    {
        int p=i-1;
        while(1)
        {
            p=nxt[p];
            if(mde[p+1]==mde[i])
            {
                nxt[i]=p+1;
                break;
            }
            if(p==0)break;
        }
    }
    return;
}
int main()
{
    scanf("%d",&n);
    scanf("%s",mde+1);
    gnxt();
    for(int i=1;i<=n;i++)
    {
        //printf("%d:",i);
        int p=i;
        while(nxt[p]!=0)//枚举所有公共前后缀
        { 
            //printf("%d->",p);
            p=nxt[p];
        }
        if(nxt[i]!=0)//避免洗掉终止条件
        {
            nxt[i]=p;//保存解
        }
        //printf("%d\n",p);
        res+=i-p;//计算
    }
    printf("%lld",res);
    return 0;//拜拜程序~
}

```

---

## 作者：Steven_Meng (赞：1)

广告：[Blog里观赏更佳](https://stevenmhy.tk/archives/620a89de.html)

### $Pro$

定义一个串$A$是$Q$的周期，仅当$A$是$Q$的$proper$前缀（即$A!=Q$的意思），而且$Q$是$AA$的前缀（没有$proper$的限制）。比如说$abab$和$ababab$是$abababa$的周期。

给你一个字符串，求出它所有前缀的最大周期长度之和。

### $Sol$

![](https://ae01.alicdn.com/kf/H591e3227195a424c945a85bc4cc14babH.png)

首先先把$A,Q$画出来。

![](https://ae01.alicdn.com/kf/H055fd29a953c41cbac6dc5b555642ffcW.png)

发现绿色部分是相等的，而且绿色部分是$A$的真$border$（既是$A$的前缀又是$A$的后缀而且不等于$A$）。

发现周期长度为$len(Q)-len(border)$，于是想让周期尽量长，就要$border$尽量短。

问题转化为求$A$的每个前缀的最短非空$border$。

这就提示我们建立$fail$树，何谓$fail$树，就是$i$向$next[i]$连边形成的树形结构。

发现$i$到根节点的路径上的节点代表$A[1 \to i]$的所有$border$。

具体证明参见[这篇博客](https://stevenmhy.tk/archives/428b39ea.html)。

![](https://ae01.alicdn.com/kf/H1e53b6bbd96b4f088a1f7d3a97f8c897d.png)

建出$fail$树之后，发现对于和$0$相邻的所有节点，它的子树里面的所有节点的最短非空$border$的长度都为这个节点的标号，很好理解。

于是可以通过一个类似于染色的方法，$O(n)$地计算出来对于每个节点的最短非空$border$的长度。

最后统计答案扫一遍即可，记得开long long。

```cpp
#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9'){
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^'0');
		ch=getchar();
	}
	return x*f;
}
char a[MAXN];
int nex[MAXN];
vector<int>G[MAXN];
int num[MAXN];
inline void dfs(int u,int father,int color){
	num[u]=color;
	for (register int i=0;i<G[u].size();++i){
		if (color==0) dfs(G[u][i],u,G[u][i]);
		else dfs(G[u][i],u,color);
	}
}
int main(){
	int n=read();
	scanf("%s",a+1);
	int j=0;
	for (register int i=2;i<=n;++i){
		while (j&&a[j+1]!=a[i]) j=nex[j];
		if (a[j+1]==a[i]) ++j;
		nex[i]=j;
	}
	for (register int i=1;i<=n;++i){
		G[nex[i]].push_back(i);
	}
	dfs(0,0,0);
	long long ans=0;
	for (register int i=1;i<=n;++i){
		ans+=i-num[i];
	}
	printf("%lld\n",ans);
}
```



---

## 作者：ButterflyDew (赞：1)

考虑对每个 $i$ 求出 $s[i,n]$ 与 $s[1,n]$ 的 lcp

对位置 $i$ ，假设 lcp 长度为 $p$ ，那么显然以区间 $[i,i+p-1]$ 为结束的前缀都可以使用 $[1,i-1]$ 作为周期

事实上需要实现一个区间取 $\max$ ，直接暴力是带 $\log$ 的

但是我们考虑用扩展 kmp 实现的时候，加入 $[i,n]$ 的 lcp 一定比 $[j,n](j<i)$ 更优，于是我们维护一个单调栈即可

---

**Code:**
```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define ll long long
using std::min;
#define gc() getchar()
template <class T>
void read(T &x)
{
    x=0;char c=gc();
    while(!isdigit(c)) c=gc();
    while(isdigit(c)) x=x*10+c-'0',c=gc();
}
const int N=1e6+10;
int n,sta[N],z[N],tot;
char s[N];
ll ans;
int main()
{
    read(n),scanf("%s",s+1);
    for(int mx=0,l=0,i=2;i<=n;i++)
    {
        z[i]=i<=mx?min(z[i-l+1],mx-i+1):0;
        while(s[i+z[i]]==s[z[i]+1]) ++z[i];
        if(i+z[i]-1>=mx) l=i,mx=i+z[i]-1;
        if(z[i]) sta[++tot]=i;
        while(tot&&i>=sta[tot]+z[sta[tot]]) --tot;
        if(tot) ans+=sta[tot]-1;
    }
    printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：渡海 (赞：1)

感谢will7101点拨。


这个题并非朴素求next数组，楼下的思路是正确的但Code并不正确。


一开始读题没读懂题意。


举个例子：aba的proper period是ab，因为ab是aba的前缀且aba是abab的周期。


交叉重叠部分就是题目要求的周期


朴素的next数组为：0 0 1 2 3 4 5 6


正确的next数组应该是用长度减掉两段交叉的部分（两段交叉的部分是最小周期，所以剪掉后就是最大的题目要求的周期）


即对next求出后再进行一次处理，将后面的指向前面的找到交叉部分然后用长度减掉。


code:
    
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
long long ans;
char s[1000005];
int next[1000005];
int main(){
    int n;
    scanf("%d",&n);
    scanf("%s",s+1);
    int j=0;
    for(int i=2;i<=n;i++){
        while(j!=0&&s[i]!=s[j+1]){
            j=next[j];    
        }
        if(s[i]==s[j+1]){
            j++; 
            next[i]=j;    
        } 
    }
    for(int i=1;i<=n;i++){
        if(next[next[i]]!=0){
            next[i]=next[next[i]];
        }
    }
    for(int i=1;i<=n;i++){
        if(next[i]!=0){
            ans+=i-next[i];
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：oscar (赞：1)

【POI补全计划#19 POI2006 OKR】

根据数据范围猜算法！这题一看就要求出next数组

接下来想一下题目里说的“周期”代表着什么——某段后缀与某段前缀相等且没有重叠部分

于是求最长周期串就等价于求最短前缀使得该前缀等于一个等长的后缀

这个信息可以通过next数组不停往前跳（直到最后一个非0位置）得到

P.S.不要忘记开long long（我就是因为这个挂了两次orz）

最后贴代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char str[1234567];
int fail[1234567],to[1234567];
int main()
{
    int len;
    scanf("%d",&len);
    scanf("%s",str+1);
    int k=0;
    long long ans=0;
    for(int i=2;i<=len;++i)
    {
        while(k&&str[k+1]!=str[i])k=fail[k];
        if(str[k+1]==str[i])++k;
        fail[i]=k;
    }
    for(int i=1;i<=len;++i)
    {
        if(fail[i])to[i]=to[fail[i]];
        else to[i]=i;
        ans+=i-to[i];
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：我要考北大 (赞：0)

1468：OKR-Periods of Words

时间限制: 1000 ms         内存限制: 65536 KB
提交数: 276     通过数: 123 
【题目描述】
原题来自：POI 2006

串是有限个小写字符的序列，特别的，一个空序列也可以是一个串。一个串 P 是串 A 的前缀，当且仅当存在串 B，使得 A=PB。如果P≠A并且 P 不是一个空串，那么我们说 P 是 A 的一个 proper 前缀。

定义 Q 是 A 的周期，当且仅当 Q 是 A 的一个 proper 前缀并且 A 是 QQ 的前缀（不一定要是 proper 前缀）。比如串 abab 和 ababab 都是串 abababa 的周期。串 A 的最大周期就是它最长的一个周期或者是一个空串（当 A 没有周期的时候），比如说，ababab 的最大周期是 abab。串 abc 的最大周期是空串。

给出一个串，求出它所有前缀的最大周期长度之和。

【输入】
第一行一个整数 k，表示串的长度。

接下来一行表示给出的串。

【输出】
输出一个整数表示它所有前缀的最大周期长度之和。

【输入样例】
8
babababa
【输出样例】
24
【提示】
数据范围:

对于全部数据，1<k<106​​ 。

【来源】

No




对于一个串 如果要求他的最长周期
先要求出最短的前缀后缀相同的前缀的位置
例如babab  位置就是0
这个位置对应到右边也有一个相同的b
babab 减去最后一个b 就是最长周期baba
答案为i减去这个位置

再如bbcaefbbc  那个位置是2

怎么求这个位置
由kmp算法
next[i]表示0到i中 最长的前缀后缀相同的前缀的位置

若要求最短的前缀后缀相同的前缀的位置
则递归
在0到i中
这个位置j=next[next[next[i]] 要递归好多次
		int j=i;
		while(f[j]!=-1)j=f[j];
        
        
```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
char st[1000000+100];
int f[1000000+100];
int main()
{
	scanf("%d",&k);
	scanf("%s",st);
	f[0]=-1;
	long long ans=0;
	for(int i=1;i<k;i++)
	{
		int j=f[i-1];f[i]=-1;
		while(j>=0&&st[j+1]!=st[i])j=f[j];		
		if(st[j+1]==st[i])f[i]=j+1;
		else 
		{
			f[i]=-1;
			continue;
		}
	}

	for(int i=1;i<k;i++)
	{
		if(f[i]==-1)continue;
		int j=i;
		while(f[j]!=-1)j=f[j];
		f[i]=j;
		
		ans+=i-j;
		
	}
	printf("%lld\n",ans);
	return 0;
}
```
























---

## 作者：长江豚 (赞：0)

**题解**
*1.分析*
先翻译一下这道让人无法看懂的题。
给出一个数组，长度为n。
你需要对它的n个前缀进行操作
操作：比如现在我们需要操作前缀i。你需要找出该i字符串的最大周期。并且把n个前缀的最大周期的值加起来。
既然需要加上最大周期，那么怎么求最大周期呢？
如图，每个字符串都可以分为三个小字符串，我们称为1,2,3号；（从左往右的顺序）
当1号3号完全相等时，1和2，或者2和3就构成了一个周期；
最大：也就是1和3越小时周期T就会越大
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190829163603821.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzg4OTEyMQ==,size_16,color_FFFFFF,t_70)
根据前后相等的性质（1号和3号），我们很自然就想到了KMP中的next数组（我习惯用p数组来表示）。那么怎么求最小呢，我们一直递归下去就好了
放一段伪代码吧；

```cpp
ll print()
{
	for(int i=1;i<=n;i++)
	{
		int j=i;
		while(next[j]) j=next[j];
		ans+=i-j;
		if(next[i]) next[i]=j;
		 //这里是一个优化，相当于以后我在访问next[i]，可以一步到位，有点像并查集的优化
		 //如果这里不优化的化应该会有60分
      //这个优化我是在题解里面抄来的，感谢那位大佬
	}
	return ans;
}
```
*2.附上AC代码+注释*

```c
#include<bits/stdc++.h>
#define maxn 1000005
#define ll long long int 
using namespace std;
int n;
char a[maxn];
int next[maxn];
void pre()
{
	next[1]=0;
	int j=0;
	for(int i=1;i<n;i++)
	{
		while(j>=1&&a[i+1]!=a[j+1]) j=next[j];
		if(a[i+1]==a[j+1]) j++;
		next[i+1]=j;
	}
}
ll ans=0;
ll print()
{
	for(int i=1;i<=n;i++)
	{
		int j=i;
		while(next[j]) j=next[j];
		ans+=i-j;
		if(next[i]) next[i]=j; 
	}
	return ans;
}
int main()
{
	cin>>n;
	cin>>a+1;//数组首项从a[1]开始
	pre();
	cout<<print();
	return 0;
}
```


---

