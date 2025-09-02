# [SDOI2008] Sandy 的卡片

## 题目描述

Sandy 和 Sue 都热衷于收集干脆面中的卡片。

然而，Sue 收集卡片是因为卡片上漂亮的人物形象，而 Sandy 则是为了积攒卡片兑换超炫的人物模型。

每一张卡片都由一些数字进行标记，第 $i$ 张卡片的序列长度为 $M_i$，要想兑换人物模型，首先必须要集够 $N$ 张卡片，对于这 $N$ 张卡片，如果他们都有一个相同的子串长度为 $k$，则可以兑换一个等级为 $k$ 的人物模型。相同的定义为：两个子串长度相同且一个串的全部元素加上一个数就会变成另一个串。

Sandy 的卡片数远远小于要求的 $N$，于是 Sue 决定在 Sandy 的生日将自己的卡片送给 Sandy，在 Sue 的帮助下，Sandy 终于集够了 $N$ 张卡片，但是，Sandy 并不清楚他可以兑换到哪个等级的人物模型，现在，请你帮助 Sandy 和 Sue，看看他们最高能够得到哪个等级的人物模型。

## 说明/提示

$30\%$ 的数据保证 $n\le50$

$100\%$ 的数据保证 $n\le1000,M\le1000,2\le M_i\le101$

update：题面上数据范围 $M_i$ 和 $M$ 的范围其实是一个东西… 真实数据范围: $40\le n\le1000,2\le M_i\le101$,字符串中的每个数字的大小范围为 $[0,1864]$。


## 样例 #1

### 输入

```
2
2 1 2
3 4 5 9
```

### 输出

```
2```

# 题解

## 作者：xMinh (赞：32)

抵制mhr(@明月の卫——AH)暴力题解 从我做起！

SA多好啊

本题有多种解法 但是本蒟蒻只会后缀数组

关于后缀数组的详细讲解：

[蒟蒻的博客](https://xminh.github.io/)

我们先把所有串连接在一起，用后缀数组求出LCP，然后二分长度，每次从头到尾扫一遍。

但是要注意连接的时候要加分割标记，这个只需要往两个串中间放一个大数就可以了。

根据LCP Theorem(证明过程见我博客)

LCP(i,k)=min(LCP(j,j-1)) 对于任意1<i<=j<=k<=n

设height[i]=LCP(i,i-1)

只要有n个>=len的height且其首字母属于不同的串就可以了

上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#define Big (1000000000 + 10)
#define maxn 111111
using namespace std;
int sa[maxn],rk[maxn],b[maxn],c[maxn],x[maxn],y[maxn];
int height[maxn],stack[maxn],id[maxn],len[1010],a[1010][1010];
int num,cnt,n,m,l,r,maxx,minn,ans,top;
bool vis[maxn]; 

int read() {
	char c=getchar();
	int r=0,f=1;
	while (!isdigit(c)) {
		if (c=='-') f=-1;
		c=getchar();
	}
	while (isdigit(c)) {
		r=(r*10)+(c^48);
		c=getchar();
	}
	return r*f;
}

int min(int x,int y) {return x<y?x:y;}
int max(int x,int y) {return x>y?x:y;}

void Get_SA() {
	for (int i=1;i<=n;i++) ++c[x[i]=b[i]];
	for (int i=2;i<=m;i++) c[i]+=c[i-1];
	for (int i=n;i>=1;i--) sa[c[x[i]]--]=i;
	
	for (int k=1;k<=n;k<<=1) {
		cnt=0;
		for (int i=n-k+1;i<=n;i++) y[++cnt]=i;
		for (int i=1;i<=n;i++) if (sa[i]>k) y[++cnt]=sa[i]-k;
		
		for (int i=1;i<=m;i++) c[i]=0;
		for (int i=1;i<=n;i++) ++c[x[i]];
		for (int i=2;i<=m;i++) c[i]+=c[i-1];
		for (int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
		
		swap(x,y);
		x[sa[1]]=1; cnt=1;
		for (int i=2;i<=n;i++) 
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k])?cnt:++cnt;
		if (cnt==n) break;
		m=cnt;
	}
}

void Get_Height() {
	int k=0;
	for (int i=1;i<=n;i++) rk[sa[i]]=i;
	for (int i=1;i<=n;i++) {
		if (rk[i]==1) continue;
		if (k) --k;
		int j=sa[rk[i]-1];
		while (j+k<=n && i+k<=n && b[i+k]==b[j+k]) ++k;
		height[rk[i]]=k;
	}
}

bool check(int x) {
	while (top) vis[stack[top--]]=0;
	for (int i=1;i<=n;i++) {
		if (height[i]<x) {
			while (top) vis[stack[top--]]=0;
		}
		if (!vis[id[sa[i]]]) {
			vis[id[sa[i]]]=1;
			stack[++top]=id[sa[i]];
			if (top==num) return 1; 
		}
	}
	return 0;
}

int main() {
	num=read(); 
	l=0;r=minn=Big;
	for (int i=1;i<=num;i++) {
		len[i]=read();
		for (int j=1;j<=len[i];j++) {
			a[i][j]=read();
			if (j!=1) maxx=max(maxx,a[i][j]-a[i][j-1]);
		}
		r=min(r,len[i]-1);
	}
	for (int i=1;i<=num;i++) {
		for (int j=2;j<=len[i];j++) {
			b[++n]=a[i][j]-a[i][j-1];
			id[n]=i;
			minn=min(minn,b[n]);
		}
		b[++n]=++maxx;
	}
	for (int i=1;i<=n;i++) {
		b[i]=b[i]-minn+1;
		m=max(m,b[i]);
	}
	Get_SA();
	Get_Height();
	while (l<=r) {
		int mid=(l+r)>>1;
		if (check(mid)) {
			l=mid+1;
			ans=mid;
		}
		else r=mid-1;
	}
	printf("%d",ans+1);
}
```

---

## 作者：Adove (赞：26)

我又来发题解了

没错我们教练考场上又发了这道题~~（然后我又用暴力A掉了~~

不要差分，直接二分长度暴力匹配，遇到不匹配的跳出即可，期望复杂度O(n·mlog min(m))，实际情况下不开O2，20ms，最优解第三。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int INF=2e9;

int n;
int che[105];
struct rp{
	int num[105];
}m[1005];

bool cmp(rp a,rp b){
	return a.num[0]<b.num[0];
}

bool check3(int len,int x){
	for(register int i=1;i<=m[x].num[0]-len+1;++i){
		int ck=che[1]-m[x].num[i];
		bool fl=0;
		for(register int j=2;j<=len;++j){
			if(che[j]-m[x].num[i+j-1]!=ck){
				fl=1;
				break;
			}
		}if(!fl) return 1;
	}return 0;
}

bool check2(int len){
	for(register int i=2;i<=n;++i){
		if(!check3(len,i)) return 0;
	}return 1;
}

bool check(int len){
	for(register int i=1;i<=m[1].num[0]-len+1;++i){
		for(register int j=1;j<=len;++j){
			che[j]=m[1].num[i+j-1];
		}if(check2(len)) return 1;
	}return 0;
}

int main(){
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
	
	scanf("%d",&n);m[0].num[0]=INF;
	for(register int i=1;i<=n;++i){
		scanf("%d",&m[i].num[0]);
		for(register int j=1;j<=m[i].num[0];++j){
			scanf("%d",&m[i].num[j]);
		}
	}sort(m+1,m+n+1,cmp);
	m[0].num[0]=m[1].num[0];
	
	int l=1,r=m[0].num[0];
	while(l<r){
		int mid=(l+r+1)>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
	}printf("%d\n",l);
	
	return 0;
}
```
跟我一起大声喊：
打表找规律！
骗分过样例！
暴力出奇迹！

---

## 作者：Pine (赞：17)

# 此题纯暴力可过

不明白为什么没人打暴力呢，我暴力都跑108ms，AC绰绰有余啊！

# 思路

将序列变成差值序列，这样只需要找完全相同的连续的公共子序列就可以了。

然后随便找一个序列（找第一个就可以），枚举一个左端点，让其它n-1个序列都从这个左端点开始匹配，最后取一个匹配最短的，去和ans取max就可以了。

当然我们再匹配的时候如果当前匹配的长度已经超过了之前的一个最小值了，我们就直接结束匹配，因为再匹配就没有用了。

虽然时间复杂度看似不可过，但是它就是过了，而且还跑得飞快！

# 代码

```
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#define R register
#define eps 1e-12
#define INF (1<<30)
#define LL long long
#define MM(x, y) memset(x, y, sizeof x)
#define Fo(i, x, y) for(R int i=x; i<=y; ++i)
#define Ro(i, x, y) for(R int i=x; i>=y; --i)
using namespace std;
template<typename T> inline T Max(R T x, R T y) {return x > y ? x : y;}
template<typename T> inline T Min(R T x, R T y) {return x < y ? x : y;}
template<typename T> inline void in(R T &x)
{
    static int ch; static bool flag;
    for(flag=false, ch=getchar(); ch<'0'||ch>'9'; ch=getchar()) flag |= ch=='-';
    for(x=0; ch>='0'&&ch<='9'; ch=getchar()) x = (x<<1) + (x<<3) + ch - '0';
    x = flag ? -x : x;
}
/**********************************Samle***************************************/
int n, A[1005][1005];
int main()
{
	in(n);
	Fo(i, 1, n)
	{
		in(A[i][0]);
		Fo(j, 1, A[i][0]) in(A[i][j]);
	}
	Fo(i, 1, n)
	{
		A[i][0]--;
		if(A[i][0] == 0)
		{
			puts("1");
			return 0;
		}
		Fo(j, 1, A[i][0]) A[i][j] = A[i][j+1] - A[i][j];
	}
	R int ans = 0;
	Fo(l, 1, A[1][0])
	{
		R int r = A[1][0];
		Fo(i, 2, n)
		{
			R int MX = 0;
			Fo(j, 1, A[i][0])
			{
				if(A[i][j] == A[1][l])
				{
					R int p = j, re = l;
					while(A[i][p] == A[1][re] && p<=A[i][0] && re<=r) ++re, ++p;
					MX = Max(MX, re-1);
				}
			}
			r = Min(r, MX);
		}
		ans = Max(ans, r-l+1);
	}
	printf("%d\n", ans+1);
	return 0;
}

```

---

## 作者：ecnerwaIa (赞：16)

[题目](https://www.luogu.org/problemnew/show/P2463)

此题真有趣啊，但是不难（后缀数组瞬秒）

题目中的相同定义为**两个子串长度相同且一个串的全部元素加上一个数就会变成另一个串。**

如果A串和B串相同,那么他们$a[pos]-a[pos+1]$都要相同，而如果$A,B$的相邻原素差值相同也能退出$A,B$是相同的

比如给定 $A:1,3,4,6 B :2,4,5,7 $，将前一个减去后一个变成$A:-2,-1,-2,6 ,B:-2,-1,-2,7$但是发现最后一个不一定相同，所以为lcp+1（注意！可能最后一个元素相同,那么+1就不对了，这时随机化就厉害了,我们**给末尾+rand()%p**,p随意取这样就容易接解决这个问题了，除非rp很差被卡）

这是两个串的情况,考虑转化为$n$个串的情况，我们先**将n个串串起来**，中间连上一个>1864的数,这样两个不同的串就不会当成一个串算lcp了，否则假如有$A:1,2\ \ B:3,2,3 4\ \ C:1,2,3 5$(已差分),那么串起来变成:$1,2,3,2,3,4,1,2,3,5$发现其实算出来3个的lcp为2，但实际上应该是1

因为2的前半部分被当成1的后半部分算了，为了不出现这种情况，就要在中间加个分割的数

串起来后跑后缀数组，得到rank(后缀排名),sa(第x名在字符串的位置)，我们只要求出n个后缀（属于不同字符串）的lcp+1就好了（什么？这还不如暴力？那你可能要回去再学一下后缀数组）

假设$A$的排名为$x$,$B$的排名为$y(x<=y)$，如果存在一个串$C$的排名为$z$，如果$z<x$，那么会有$lcp(B,C)<=lcp(A,C)$，如果$x<z<y$就会有lcp(B,C)>=lcp(A,C)（不知道的去模板题题解看看吧）

这样发现其实有单调性,我们假设只考虑排名为$[1,R]$中的后缀，（最后一个在R），发现如果$[2,R]$也出现了$n$个字符串的某个后缀，$[2,R]$答案一定>=$[1,R]$的答案，那么可以得出如果排名为$[L+1,R]$是合法的([L,R]肯定合法，因为$R$增加不会导致某个字符串出现在[L,R]的后缀次数减少，只会增加)，L++就好了，直到一个$[L+1,R]$不合法的位置，就可以更新答案了，当然$cnt>=n$(就是$\sum{i=1}^{n}[num[i]!=0]$(num[i]为第$i$个串在排名$[L,R]$区间存在的后缀个数))才能更新

其实就变成了对一个字符串A在总串上的起始位置到末尾位置染色（就很简单了吧）

上代码（还有不懂得估计看代码也都会了吧）

```cpp
// luogu-judger-enable-o2
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
inline void read(int &x){
    x=0;int f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
}
#define min_(a,b) (a<b?a:b)
#define max_(a,b) (a>b?a:b)
const int N=1010,M=N*105;
int n,m,c,cl,a[M],num[N],col[M],cnt;
struct my_SA{
    int tax[M],rank[M],sa[M],tp[M],he[M],bit[M],s[20];
    int to[M][20];
    inline void qsort(){
        for(int i=1;i<=m;++i)tax[i]=0;
        for(int i=1;i<=c;++i)tax[rank[i]]++;
        for(int i=1;i<=m;++i)tax[i]+=tax[i-1];
        for(int i=c;i>=1;--i)sa[tax[rank[tp[i]]]--]=tp[i];
    }inline void suffix_sort(){
        m=5000;
        for(int i=1;i<=c;++i){rank[i]=a[i];tp[i]=i;}
        qsort();
        for(int i=1,p=0;p<c;m=p,i<<=1){
            p=0;
            for(int j=1;j<=i;++j)tp[++p]=c-i+j;
            for(int j=1;j<=c;++j)if(sa[j]>i)tp[++p]=sa[j]-i;
            qsort();swap(rank,tp);
            rank[sa[1]]=p=1;
            for(int j=2;j<=c;++j)rank[sa[j]]=(tp[sa[j]]==tp[sa[j-1]]&&tp[sa[j]+i]==tp[sa[j-1]+i]?p:++p);
        }
    }inline void get_pre(){
        int last=2;int x=0;
        for(int i=1;i<=c;++i){bit[i]=x;if(i==last){x++;last<<=1;}}
        int maxn=bit[c];s[0]=1;for(int i=1;i<=maxn;++i)s[i]=s[i-1]<<1;
    }inline void get_he(){
        int j,k=0;
        for(int i=1;i<=c;++i){
            if(k)k--;
            j=sa[rank[i]-1];
            while(a[i+k]==a[j+k]&&i+k<=c&&j+k<=c)k++;
            he[rank[i]]=k;
        }
    }inline void pre_rmq(){
        for(int i=1;i<=c;++i)to[i][0]=he[i];
        for(int i=1;i<=bit[c];++i){
            int p=s[i],q=s[i-1];
            for(int j=1;j<=c;++j){
                if(j+p-1<=c)to[j][i]=min_(to[j][i-1],to[j+q][i-1]);
                else break;
            }
        }
    }inline void init(){get_pre();suffix_sort();get_he();pre_rmq();}
    inline int rmq(int L,int R){
        if(L==R)return c-sa[L]+1;
        L++;
        int len=R-L+1,p=bit[len],q=s[p];
        return min_(to[L][p],to[R-q+1][p]);
    }
    inline void slove(){
        int L=1,R=1,ans=0;
        for(;R<=c;++R){
            if(col[sa[R]]>0){if(++num[col[sa[R]]]==1)cnt++;}
            while(num[col[sa[L]]]>1){num[col[sa[L]]]--;L++;}
            if(cnt>=n)ans=max_(ans,rmq(L,R)+1);
        }printf("%d\n",ans);
    }
}T;
int x;
const int mod=93;
inline int get_rand(){x=x*x+7;return x%mod;}
int main(){
    read(n);cl=1864;int p;x=7;
    for(int i=1;i<=n;++i){
        read(m);p=get_rand();
        for(int j=1;j<=m;++j){read(a[++c]);a[c]+=p;col[c]=i;}
        for(int j=1;j<m;++j){a[c-m+j]-=a[c-m+j+1];}
        a[++c]=++cl;col[c]=-1;
    }int minn=1<<30;
    for(int i=1;i<=c;++i)minn=min_(minn,a[i]);minn--;
    for(int i=1;i<=c;++i)a[i]-=minn;
    T.init();T.slove();
    return 0;
}

```
（求随机数居然用了2ms）

---

## 作者：Orion545 (赞：11)

# 广告

[蒟蒻のblog](http://www.cnblogs.com/dedicatus545/p/8900736.html)

# 思路

这道题里面有三个主要问题：

1.由“数值相等”变成了“加上一个整数以后数值相等”（减去等价于加负数）

2.由“最多匹配多少位（从第一位开始）”变成了从“任意一位开始匹配”

3.由“单文本串”变成了“多文本串”，而且是文本串内部自己匹配

我们按照难度顺序（3-1-2）来依次解决他们

### 问题三：多文本串

这个问题是最简单的，因为每个串长度不超过100，最多1000个串

所以，我们搞一个串出来成为模式串，然后用它去匹配剩下的串，结果取min就行了

### 问题一：数值加上整数相等

这个问题中我们要贯彻一个思想：取不变量

考虑一个序列，当它的每一个元素都增加了一定值以后，什么还是不变的？

没错，相邻元素（或者说任意两个元素）的**差值**

所以，本题中，我们只要把原来的序列变成长度小了1，元素为原来序列相邻两位之差的新序列来跑匹配，最后把答案加一就好了

### 问题二：可以从每一位开始匹配

这个问题，在解决了问题三以后也能迎刃而解：**数据范围实在是太！小！了！**

我们完全可以枚举模式串的开始位置，求出next数组，然后对于剩下的串每一个匹配一下，还能腾出一半的运行时间，大声喊出：

## “zcy吊打集训队！”

# Code：

```cpp
// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define inf 1e9
using namespace std;
inline int read(){
    int re=0,flag=1;char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-') flag=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') re=(re<<1)+(re<<3)+ch-'0',ch=getchar();
    return re*flag;
}
int a[1010][110],b[110];int N,n,m[1010],fail[110],ans=0,tans=inf,tmp;
int main(){
    N=read();int i,j,t1,t2,k,l;
    n=read();t1=read();for(i=0;i<n-1;i++) t2=read(),b[i]=t2-t1,t1=t2;
    b[n-1]=b[n]=b[n+1]=-inf;
    for(j=1;j<N;j++){
        m[j]=read();t1=read();
        for(i=0;i<m[j]-1;i++) t2=read(),a[j][i]=t2-t1,t1=t2;
        a[j][m[j]-1]=a[j][m[j]]=inf;
    }
    for(k=n-1;k>=1;k--){
        memset(fail,0,sizeof(fail));
        j=0;tans=inf;
        for(i=1;i<k;i++){
            while(j&&(b[i]!=b[j])) j=fail[j];
            j+=(b[i]==b[j]);fail[i+1]=j;
        }
        for(l=1;l<N;l++){
            j=0;tmp=0;
            for(i=0;i<m[l]-1;i++){
                while(j&&a[l][i]!=b[j]) j=fail[j];
                j+=(a[l][i]==b[j]);
                tmp=max(tmp,j);
                if(j==k) break;
            }
            tans=min(tans,tmp);
        }
        for(i=0;i<k-1;i++) b[i]=b[i+1];b[k]=-inf;
        ans=max(ans,tans);
    }
    printf("%d",ans+1);
}
```

---

## 作者：何俞均 (赞：9)

广告：食用[$blog$](https://www.cnblogs.com/heyujun/p/10305521.html)体验更佳

首先题目的区间加很丑对吧，

将每个串差分一下，就可以转化为

求：

给定$N$个串，求他们的最长公共子串。

怎么办呢，按照后缀数组常用套路

我们用不同的未曾用过的字符将这些串连接起来

我们将$lcp$大于$mid$的串分组

如果一组内串的个数大于等于$N$个，就证明可以$return\;1$

否则若没有一组大于等于$N$返回$0$

代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring> 
#include <cmath> 
#include <algorithm>
using namespace std; 
inline int gi() {
    register int data = 0, w = 1;
    register char ch = 0;
    while (!isdigit(ch) && ch != '-') ch = getchar(); 
    if (ch == '-') w = -1, ch = getchar();
    while (isdigit(ch)) data = 10 * data + ch - '0', ch = getchar();
    return w * data; 
}
const int MAX_N = 2e6 + 5; 
int N, T, a[MAX_N], b[MAX_N], vis[MAX_N]; 
int sa[MAX_N], rnk[MAX_N], lcp[MAX_N]; 
void GetSA() {
#define cmp(i, j, k) (y[i] == y[j] && y[i + k] == y[j + k]) 
    static int x[MAX_N], y[MAX_N], bln[MAX_N];
    int M = 1e6; 
    for (int i = 1; i <= N; i++) bln[x[i] = a[i]]++; 
    for (int i = 1; i <= M; i++) bln[i] += bln[i - 1]; 
    for (int i = N; i >= 1; i--) sa[bln[x[i]]--] = i; 
    for (int k = 1; k <= N; k <<= 1) { 
        int p = 0; 
        for (int i = 0; i <= M; i++) y[i] = 0; 
        for (int i = N - k + 1; i <= N; i++) y[++p] = i; 
        for (int i = 1; i <= N; i++) if (sa[i] > k) y[++p] = sa[i] - k; 
        for (int i = 0; i <= M; i++) bln[i] = 0; 
        for (int i = 1; i <= N; i++) bln[x[y[i]]]++; 
        for (int i = 1; i <= M; i++) bln[i] += bln[i - 1]; 
        for (int i = N; i >= 1; i--) sa[bln[x[y[i]]]--] = y[i]; 
        swap(x, y); x[sa[1]] = p = 1; 
        for (int i = 2; i <= N; i++) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p; 
        if (p >= N) break;
        M = p; 
    } 
}
void GetLcp() { 
    for (int i = 1; i <= N; i++) rnk[sa[i]] = i; 
    for (int i = 1, j = 0; i <= N; i++) {
        if (j) --j; 
        while (a[i + j] == a[sa[rnk[i] - 1] + j]) ++j; 
        lcp[rnk[i]] = j; 
    } 
} 
int col[MAX_N], tot; 
bool check(int v) {
    ++tot; int cnt = 0; 
    for (int i = 1; i <= N; i++) { 
        if (lcp[i] < v) ++tot, cnt = 0; 
        if (col[vis[sa[i]]] != tot) col[vis[sa[i]]] = tot, ++cnt; 
        if (cnt == T) return 1; 
    } 
    return 0; 
} 
const int dlt = 5e4; 
int main () { 
    T = gi(); 
    for (int i = 1; i <= T; i++) { 
        int m = gi(); 
        for (int j = 1; j <= m; j++) b[j] = gi(); 
        for (int j = 1; j <= m; j++) b[j] = b[j + 1] - b[j] + dlt; 
        for (int j = 1; j <= m; j++) a[++N] = b[j], vis[N] = i; 
        a[++N] = i + 5e5; 
    }
    GetSA(); GetLcp(); 
    int l = 0, r = N, ans = 0; 
    while (l <= r) { 
        int mid = (l + r) >> 1; 
        if (check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1; 
    } 
    printf("%d\n", ans + 1); 
    return 0; 
} 
```

---

## 作者：Creeper_LKF (赞：8)

既然大家都用KMP或后缀数组，那本蒟蒻发一发后缀自动机的题解吧。

可以先了解一下后缀自动机，在本题中，它的应用是统计子串出现次数及长度。

后缀自动机可以匹配（接受）给定母串的所有子串。

于是在这道题中，我们把输入差分一下，发现样例转换成

1 1
1 1 4
然后答案是2？

然而第一个数无效（显然的）。答案应该是去掉第一个数之后的所有串的

最长公共###子串 +1

子串？符合胃口。于是我们要求最长公共子串在n个串中都出现过。

现在先假设你已经学完了后缀自动机

如何统计出现了n次？

我们以某一个位置作为开头，然后扫描这个字符所对应在后缀自动机的节点（注意不要重复），然后跟着pre数组向上走，每走一个节点给它的次数++，于是如果一个点被走了n次，那么说明它在n个串中都出现过了（可以根据pre数组的定义推导）。

如何获取长度？

其实就是step，也是定义，也就是原定义中跳转节点的长度。

代码如下（理论复杂度O(nm)\*O(n-)）：







```cpp
#include <cstring>
#include <cstdio>
#include <cctype>
#include <map>
using namespace std;
#define MAXN 1010
#define MAXM 2000020
#define INF 0x3f3f3f3f
inline char get_char(){
    static char buf[500001], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 500000, stdin), p1 == p2) ? EOF : *p1 ++;
}
inline int read(){
    int num = 0;
    char c;
    while (isspace(c = get_char()));
    while (num = num * 10 + c - 48, isdigit(c = get_char()));
    return num;
}
inline int upmax(int &a, const int &b){
    if(a < b) a = b;
    return a;
}
int n, m[MAXN], s[MAXN][MAXN], size[MAXM];
namespace SAM{
    int cnt = 1, lst = 1;
    map<int, int> son[MAXM];
    int pre[MAXM], step[MAXM];
    inline void Insert(int tar){
        int p = lst, np = ++cnt;
        for(lst = np, step[np] = step[p] + 1;p && !son[p][tar]; p = pre[p]) son[p][tar] = np;
        if(!p) pre[np] = 1;
        else {
            int q = son[p][tar];
            if(step[p] + 1 == step[q]) pre[np] = q;
            else {
                int nq = ++cnt;
                step[nq] = step[p] + 1;
                son[nq] = son[q];
                for(pre[nq] = pre[q], pre[q] = pre[np] = nq; son[p][tar] == q; p = pre[p]) son[p][tar] = nq;
            }
        }
    }
}
int vis[MAXM];
inline int Get_Ans(){
    int ret = 1;
    for(int i = 1; i <= n; i++){
        int p = 1, *tp = s[i];
        for(int j = 2; j <= m[i]; j++){
            p = SAM::son[p][tp[j] - tp[j - 1]];
            int tmp = p;
            while(vis[tmp] != i){
                vis[tmp] = i;
                size[tmp]++;
                tmp = SAM::pre[tmp];
            }
        }
    }
    for(int i = 1; i <= SAM::cnt; i++)
        if(size[i] == n)
            upmax(ret, SAM::step[i] + 1);
    return ret;
}
int main(){
    n = read();
    for(int i = 1; i <= n; i++){
        m[i] = read();
        int *p = s[i];
        for(int j = 1; j <= m[i]; j++){
            p[j] = read();
            if(j != 1) SAM::Insert(p[j] - p[j - 1]);
        }
    }
    printf("%d", Get_Ans());
    return 0;
}

```

---

## 作者：asuldb (赞：5)

被$mhr$的暴力干翻了

这道题做法还是非常好想的

先做一遍差分，在每个串的某尾插入一个特殊字符，再将所有的串拼接在一起

现在的问题就转化为找到一个最长的公共子串使得其出现了$n$次，但是在一个串内出现多次出现只算一次

先考虑一下没有第二个限制的做法

那就是最简单的$SA$+二分了，就是扫一遍$height$数组，之后根据$height$进行分组使得一个组内所有的$height$都大于等于当前二分出来的$mid$，之后一个组内有多少个就代表这个子串出现了多少次

现在有了限制，就是不能来自于同一个串

于是我们给每一个$sa_i$打一个标记，标记好其来自哪一个数组，之后对于一个组内出现的同一个串内的我们只需要算一次就够了

代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define LL long long
#define maxn (1000*100+1000+5)*2
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define pt putchar(1)
inline int read()
{
	char c=getchar();int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
int a[maxn],f[maxn],c[maxn];
int tp[maxn],sa[maxn],rk[maxn],tax[maxn],het[maxn],b[maxn];
int n,m,K,r,t;
inline void qsort()
{
	for(re int i=0;i<=K;i++) tax[i]=0;
	for(re int i=1;i<=n;i++) tax[rk[i]]++;
	for(re int i=1;i<=K;i++) tax[i]+=tax[i-1];
	for(re int i=n;i;--i) sa[tax[rk[tp[i]]]--]=tp[i];
}
inline int check(int x)
{
	int num=0,now=1;
	if(f[sa[1]]) num++,b[f[sa[1]]]++;
	for(re int i=2;i<=n;i++)
	{
		if(het[i]<x)
		{
			if(num>=m) return 1;
			for(re int j=now;j<i;j++) b[f[sa[j]]]=0;
			num=0,now=i;
			if(f[sa[i]]) num++,b[f[sa[i]]]++;
			continue;
		}
		if(!b[f[sa[i]]]&&f[sa[i]]) b[f[sa[i]]]++,num++;
	}
	return num>=m;
}
int main()
{
	m=read();
	for(re int i=1;i<=m;i++)
	{
		t=read();r=max(t,r);
		for(re int j=1;j<=t;j++) a[++n]=read(),f[n]=i;
		a[++n]=i+101,f[n]=0;
	}
	for(re int i=1;i<=n;i++) c[i]=a[i]-a[i-1];
	for(re int i=1;i<=n;i++) c[i]+=2001,K=max(c[i],K);
	c[1]=0;
	for(re int i=1;i<=n;i++) tp[i]=i,rk[i]=c[i];
	qsort();
	for(re int w=1,p=0;p<n;K=p,w<<=1)
	{
		p=0;
		for(re int i=1;i<=w;i++) tp[++p]=n-w+i;
		for(re int i=1;i<=n;i++) if(sa[i]>w) tp[++p]=sa[i]-w;
		qsort();
		for(re int i=1;i<=n;i++) std::swap(rk[i],tp[i]);
		rk[sa[1]]=p=1;
		for(re int i=2;i<=n;i++) rk[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
	}
	int k=0;
	for(re int i=1;i<=n;i++)
	{
		if(k) --k;
		int j=sa[rk[i]-1];
		while(c[i+k]==c[j+k]) ++k;
		het[rk[i]]=k;
	}
	int l=1,ans=0;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid)) l=mid+1,ans=mid;
			else r=mid-1;
	}
	printf("%d\n",ans+1);
 	return 0;
}
```

---

## 作者：huangzirui (赞：4)

题意：

给定 $N$ 个字符串 $S_1,S_2\ ...\ S_n$ ，求最长的相同子串长度。

相同的定义：设长度相等的字符串 $S_1,S_2$ ，若字符串 $S_1$ 的每个字符加上(减去)某个数都恰好和 $S_2$ 的对应字符相等，则称它们相同。

$n\ ,|S_i| \leq 1000$

字符集 $[0,1864]$

---
将原字符串差分，可以证明所求的就是若干个字符串的公共最长子串。

这是因为（题目的）**相同** 其实就是令相邻字符之差相等。

考虑怎么求多个字符串的公共最长子串。

连接它们，然后建立 SAM ，然后只要找每个节点表示的 endpos 集合即可。

为了防止连在一起出锅，中间要加上分隔符。

求 endpos 集合直接上线段树合并。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ls(x) tree[x].son[0]
#define rs(x) tree[x].son[1]
#define sum(x) tree[x].sum
#define Mid ((L+R)>>1)
using namespace std;
typedef pair<int,int> pii;
inline int read(){
	char c;int x=0;int b=1;do{c=getchar();if(c==45)b=-1;}while(c>57||c<48);
	do x=x*10+c-48,c=getchar();while(c<=57&&c>=48);x*=b;return x;
}
const int maxn=250010;
int i,j,k,n,m;
int S[1010][110],S2[maxn];
struct node{
	map<int,int>C;
	int sum,num,link,len;
}a[maxn];int len=1;
struct edge{
	int next,to;
}e[maxn];
int head[maxn],Len;
void add(int x,int y){
	e[++Len]={head[x],y};
	head[x]=Len;
}
struct ST{
	int son[2],sum;
}tree[maxn*10];
int lenth,Root[maxn];
int ans=0;
inline void update(int root){
	sum(root)=sum(ls(root))+sum(rs(root));
}
void insert(int &root,int L,int R,int S){
	if(!root)root=++lenth;
	if(L==R)sum(root)=1;
	else{
		if(S<=Mid)insert(ls(root),L,Mid,S);
		else insert(rs(root),Mid+1,R,S);
		update(root);
	}
}
int merge(int x,int y,int L,int R){
	if(!x)return y;
	if(!y)return x;
	if(L==R){sum(x)|=sum(y);return x;}
	ls(x)=merge(ls(x),ls(y),L,Mid);
	rs(x)=merge(rs(x),rs(y),Mid+1,R);
	update(x);
	return x;
}
int dfs(int now){
	Root[now]=++lenth;
	if(a[now].num)insert(Root[now],1,n,a[now].num);
	int B=0;
	for(int i=head[now];i;i=e[i].next){
		int u=e[i].to;B|=dfs(u);
		if(!B)merge(Root[now],Root[u],1,n);
	}if(B)return 1;
	if(sum(Root[now])==n){ans=max(ans,a[now].len);return 1;}
	return 0;
}
int main() {
	freopen("P2463.in","r",stdin);
	freopen("P2463.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++){
		S[i][0]=read();
		for(j=1;j<=S[i][0];j++)
			S[i][j]=read();
	}
	for(i=1;i<=n;i++){
		for(j=1;j<S[i][0];j++)S2[++m]=S[i][j+1]-S[i][j];
		S2[++m]=-2e9;
	}
	int now=1,Num=1;
	for(i=1;i<=m;i++){
		int sum=S2[i],d=++len,p=now;
		if(sum==-2e9)++Num;
		a[d].len=a[p].len+1;
		a[d].sum=1;a[d].num=Num;
		while(p && !a[p].C[sum]){
			a[p].C[sum]=d;
			p=a[p].link;
		}if(!p)a[d].link=1;
		else{
			int to=a[p].C[sum];
			if(a[to].len-a[p].len==1)a[d].link=to;
			else{
				int clone=++len;
				a[clone]=a[to];
				a[clone].len=a[p].len+1;
				a[clone].sum=a[clone].num=0;
				while(p && a[p].C[sum]==to){
					a[p].C[sum]=clone;
					p=a[p].link;
				}
				a[to].link=a[d].link=clone;
			}
		}now=d;
	}
	for(i=1;i<=len;i++)add(a[i].link,i);
	dfs(1);cout<<ans+1<<endl;
	//cerr << 1.0*clock()/CLOCKS_PER_SEC << endl;
	return 0;
}
```

---

## 作者：attack (赞：4)

蒟蒻不会SA，也不会SAM，只好用hash

显然直接把原序列做差，然后二分+hash找公共最长的子串即可

hash数组要用vector存，不然会爆空间

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define ull unsigned long long 
using namespace std;
const int MAXN = 1e6 + 10;
const ull base = 27;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, mx;
ull po[MAXN];
vector<ull> ha[MAXN];
vector<int> v[MAXN];
map<ull, int> mp, vis;
ull getha(int id, int l, int r) {
	if(l == 0) return ha[id][r];
	else return ha[id][r] - ha[id][l - 1] * po[r - l + 1];
}
int check(int len) {
	mp.clear();
	for(int i = 1; i <= N; i++) {
		vis.clear();
		for(int j = 0; j < v[i].size() - len + 1; j++) {
			ull tmp = getha(i, j, j + len - 1);
			if(!vis[tmp]) vis[tmp] = 1, mp[tmp]++;
			if(mp[tmp] == N) return 1;
		}
	}
	return 0;
}
int main() {	
	N = read();
	po[0] = 1;
	for(int i = 1; i <= 10001; i++) po[i] = base * po[i - 1];
	for(int i = 1; i <= N; i++) {
		int num = read(); mx = max(mx, num);
		for(int j = 1; j <= num; j++) v[i].push_back(read());
		for(int j = num - 1; j >= 1; j--) v[i][j] = v[i][j] - v[i][j - 1];
		ha[i].reserve(v[i].size() + 1);
	}
	for(int i = 1; i <= N; i++) {
		for(int j = 0; j < v[i].size(); j++) {
			if(!j) ha[i][j] = 0;
			else ha[i][j] = (ha[i][j - 1] + v[i][j]) * base;
		}
	}
	int l = 1, r = mx, ans = 0;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << ans + 1;
    return 0;
}
```

---

## 作者：ShaunWang (赞：3)

##KMP + 枚举/暴力

根据题意,问题可以转化为求若干个字符串的最长公共子串的长度(事实上需要先进行一下差分处理即可 即d[i]=a[i]-a[i-1] 找d数组的最长公共字串)

一个很显然的做法就是以第一个串作为模式串,枚举其每一个子串,看是否在其他每一个串中出现过,但这样子复杂度过高,只能通过约30%的数据

所以想到可以改进KMP算法的一部分,只枚举第一个串的后缀,然后算出其后缀在其他所有串中出现的最大长度MAXL,然后取其对其他所有串的MAXL的最小值即为一个可行答案,再在可行答案中取最大值即可.

这样大概可以通过100%的数据了 当然也可以用效率高得多的后缀数组来做

代码如下:

```cpp
/*
    自己选择的路，跪着也要走完。
    Programed By Harry·Shaun·Wang
    2016.12.27
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 0x3f3f3f3f
#define MAXN 1005
#define debug(x) cout<<#x<<" : "<<x<<endl
namespace IO
{
    inline int getint()
    {
        int x=0,f=1;char c=getchar();
        while(c<'0' || c>'9') { if(c=='-') f=-1; c=getchar(); }
        while(c>='0' && c<='9') x=x*10+c-48,c=getchar();
        return x*f;
    }
    inline void putint(int x)
    {
        char c[15];int k=0;
        if(x<0) putchar('-'),x=-x;
        do { c[++k]=x%10+48; x/=10; } while(x);
        while(k) putchar(c[k--]);
    }
}
using namespace std;
using namespace IO;
int n,m,k;
int a[MAXN][MAXN];
int next[MAXN];
int ans=1;
inline void getnext(int P[],int m)
{
    memset(next,0,sizeof(next));
    for(int i=1; i<m; ++i)
    {
        int j=i;
        while(j>0)
        {
            j=next[j];
            if(P[j]==P[i])
            {
                next[i+1]=j+1;
                break;
            }
        }
    }
}
int KMP(int T[],int n,int P[],int m)
{
    if(n<m) return 0;
    int t=0;
    for(int i=0,j=0; i<n; ++i)
    {
        if(j<m && T[i]==P[j]) ++j;
        else while(j>0)
        {
            j=next[j];
            if(T[i]==P[j])
            {
                ++j;
                break;
            }
        }
        t=max(t,j);
        if(j==m) break;
    }
    return t;
}
int main()
{
    n=getint();
    for(int i=1; i<=n; ++i)
    {
        a[0][i]=getint();
        for(int j=0; j<a[0][i]; ++j) a[i][j]=getint();
        for(int j=0; j<a[0][i]; ++j) a[i][j]=a[i][j+1]-a[i][j];
        --a[0][i];
    }
    for(int i=0; i<a[0][1]; ++i)
    {
        k=INF;
        getnext(a[1]+i,a[0][1]-i);
        for(int j=2; j<=n; ++j)
            k=min(KMP(a[j],a[0][j],a[1]+i,a[0][1]-i),k);
        ans=max(ans,k+1);
    }
    putint(ans);
    return 0;
}
```

---

## 作者：狛枝凪斗 (赞：2)

一种后缀自动机的做法：

给定了n个字符串，对于其中一个串建立SAM（最短的串最优不过通常来讲应该无所谓），然后让其它串在SAM上跑匹配。

从根出发走字符的转移路径，记录当前匹配到的最长长度l以及当前所在的节点now。如果失配就沿着后缀链接向更短的后缀跳直到到达根或者找到能继续往后匹配的节点。l要及时与所在节点的len取min。

每一次我们记录一个maxx数组，表示这个串匹配后，SAM上的每个节点的最长（被）匹配到的长度。走到每个节点的时候用当前的l去更新这个数组就可以了。跑完匹配以后，要dfs一遍后缀链接树，用子节点的maxx去更新父节点的maxx。因为一个字串如果被匹配到了，那么它的后缀也一定被匹配到，跑匹配的时候只走了子节点。

最后的答案是共n-1个跑匹配的串的maxx数组进行比较，每个节点的n-1个maxx取min就是它在所有串里都出现的最长长度，这个min值可以在dfs处理maxx的时候顺便维护，用不着记录n-1个数组。

最后的ans就是每个节点的min值的max。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
const int N=3e5+10;
int fro,n,siz,lst,lens,num=1,first,ans,maxx[N];
int s[N];
struct node{
	int len,link,minn;
	map<int,int>mp;
}a[N];
int ver[N],head[N],tot,Next[N];
void add(int x,int y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}
void build(){
	a[0].link=-1;
}
void insert(int c){
	int cur=++siz;
	a[cur].len=a[lst].len+1;
	a[cur].minn=N;
	int p=lst;
	while(p!=-1&&!a[p].mp.count(c)){
		a[p].mp[c]=cur;
		p=a[p].link;
	}
	if(p==-1){
		a[cur].link=0;
	}
	else{
		int q=a[p].mp[c];
		if(a[p].len+1==a[q].len){
			a[cur].link=q;
		}
		else{
			int clone=++siz;
			a[clone].len=a[p].len+1;
			a[clone].link=a[q].link;
			a[clone].minn=N;
			a[clone].mp=a[q].mp;
			while(p!=-1&&a[p].mp[c]==q){
				a[p].mp[c]=clone;
				p=a[p].link;
			}
			a[cur].link=a[q].link=clone;
		}
	}
	lst=cur;
}
void change(){
	int now=0,l=0;
	for(int i=1;i<=lens;i++){
		while(!a[now].mp.count(s[i])&&now!=0){
			now=a[now].link;
			l=min(l,a[now].len);
		}
		if(!now)l=0;
		if(a[now].mp.count(s[i])){
			now=a[now].mp[s[i]];
			l++;
			l=min(l,a[now].len);
			maxx[now]=max(maxx[now],l);
		}
	}
}		
void dfs(int x){
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		dfs(y);
		maxx[x]=max(maxx[x],maxx[y]);
	}
	a[x].minn=min(a[x].minn,min(maxx[x],a[x].len));
}
void dfs1(int x){
	ans=max(ans,a[x].minn);
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		dfs1(y);
	}
}
int main(){
	build();
	scanf("%d",&n);
	scanf("%d",&lens);
	first=lens;
	for(int i=1,x;i<=lens;i++){
		scanf("%d",&x);
		if(i!=1)insert(x-fro);
		fro=x;
	}
	for(int i=1;i<=siz;i++)add(a[i].link,i);
	for(int i=2;i<=n;i++){
		scanf("%d",&lens);
		for(int j=1,x;j<=lens;j++){
			scanf("%d",&x);
			if(j!=1)s[j-1]=x-fro;
			fro=x;
		}
		memset(maxx,0,sizeof(maxx));
		num++;
		change();
		dfs(0);
	}
	if(num==1)printf("%d\n",first);
	else{
		dfs1(0);
		printf("%d\n",ans+1);
	}
	return 0;
}
```


---

## 作者：JZYshuraK (赞：1)

# Sandy的卡片

题解：
这个题跟一个$USACO$的题特别像。我们把这些串差分

现在我们要求的就是公共子串且出现次数不少于$k$的最长长度。

紧接着把这$n$新串拼一起建立后缀数组。

两种做法：

第一种是二分。我们直接二分答案然后暴力扫验证，复杂度为$O(nlogn)$。

第二种就是双指针保证当前指针中间是满足条件的最短区间，顺便用单调

队列求区间$ht$最小值即可。

Code:
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1000050
int r[N],sa[N],wa[N],wb[N],wv[N],rk[N],ht[N],n,Ws[N],cnt,idx[N],H[1050],tot,ans,Q[N],m;
int w[100050];
inline char nc() {static char *p1,*p2,buf[100000]; return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
int rd() {int x=0; char c=nc(); while(!isdigit(c)) c=nc(); while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=nc(); return x;}
void build_sa()
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++) Ws[i]=0;
    for(i=0;i<n;i++) Ws[x[i]=r[i]]++;
    for(i=1;i<m;i++) Ws[i]+=Ws[i-1];
    for(i=n-1;i>=0;i--) sa[--Ws[x[i]]]=i;
    for(p=j=1;p<n;j<<=1,m=p)
	{
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]-j>=0) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) Ws[i]=0;
        for(i=0;i<n;i++) Ws[wv[i]]++;
        for(i=1;i<m;i++) Ws[i]+=Ws[i-1];
        for(i=n-1;i>=0;i--) sa[--Ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,i=p=1,x[sa[0]]=0;i<n;i++)
		{
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+j]==y[sa[i-1]+j]) x[sa[i]]=p-1;
            else x[sa[i]]=p++;
        }
    }
    for(i=1;i<n;i++) rk[sa[i]]=i;
    for(i=p=0;i<n-1;ht[rk[i++]]=p)
        for(p?p--:0,j=sa[rk[i]-1];r[i+p]==r[j+p];p++);
}
int main()
{
    int i,j=0;
    cnt=rd();
    int minn=1<<30,maxx=0;
    for(j=1;j<=cnt;j++)
	{
        int lim;
        lim=rd();
        for(i=0;i<lim;i++) w[i]=rd();
        for(i=1;i<lim;i++) idx[n]=j,r[n++]=w[i]-w[i-1],minn=min(minn,r[n-1]),maxx=max(maxx,r[n-1]);
        n++;
    }
    m=maxx-minn+1;
    for(i=0;i<n;i++)
	{
        if(idx[i]) r[i]-=minn-1;
        else r[i]=m+1;
    }
    r[n++]=0; m+=2;
    build_sa();
    int ll=0,rr=0; j=0;
    for(i=0;i<n;i++)
	{
        H[idx[sa[i]]]++; if(H[idx[sa[i]]]==1&&idx[sa[i]]) tot++;
        while(ll<rr&&ht[Q[rr-1]]>ht[i]) rr--;
        Q[rr++]=i;
        if(tot!=cnt) continue;
        while(j<i&&tot==cnt)
		{
            H[idx[sa[j]]]--;
            if(H[idx[sa[j]]]==0&&idx[sa[j]]) tot--;
            j++;
        }
        j--; H[idx[sa[j]]]++;
        if(H[idx[sa[j]]]==1&&idx[sa[j]]) tot++;
        while(ll<rr&&Q[ll]<=j) ll++;
        if(tot==cnt)
		{
            ans=max(ans,ht[Q[ll]]);
        }
    }
    printf("%d\n",ans+1);
	return 0;
}
```

---

## 作者：λᴉʍ (赞：1)

写一种$O(nm)$的做法，也就是$O(\sum 串长)$的。

先通过差分转化，把每个数变成这个数与上一个数的差，第一个数去掉，答案就是最长公共子串+1

按照套路把所有串拼起来，中间加一个分隔符号，然后用[DC3](https://www.cnblogs.com/jianglangcaijin/p/6035937.html)求出SA以及height

（DC3我也不会，蒯的板子，因为一般用倍增SA足够了）

对每个后缀可以知道它在原来的第几个串，那么求出SA以后，答案就是一段区间$[l,r]$，即排名为$[l,r]$的这些后缀，而且必须覆盖原来的所有串，长度就是这些后缀的LCP，就是一段height的最小值

枚举左端点，那么最小的右端点一定不小于上一个的最小右端点，所以直接维护右端点以及这一段区间包括原来每一个串的数量就好了

最小值可以直接单调队列维护

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef unsigned long long ulint;
namespace input
{
    const int bufl = 1<<14;
    char buf[bufl],*s=buf,*t=buf;
    inline int fetch()
    {
        if(s==t){t=(s=buf)+fread(buf,1,bufl,stdin);if(s==t)return EOF;}
        return *s++;
    }
    inline int gi()
    {
        register int a=0,b=1,c=fetch();
        while(!isdigit(c))b^=c=='-',c=fetch();
        while(isdigit(c))a=a*10+c-48,c=fetch();
        return b?a:-a;
    }
}
using input::gi;
const int N = 202007 , N3 = N*3 , maxalpha = 99999;
int wa[N3],wb[N3],wv[N3],buc[N3];
inline void bsort(int *s,int *a,int *b,int n,int m)
{
    register int i;
    for(i=0;i<n;i++)wv[i]=s[a[i]];
    for(i=0;i<m;i++)buc[i]=0;
    for(i=0;i<n;i++)buc[wv[i]]++;
    for(i=1;i<m;i++)buc[i]+=buc[i-1];
    for(i=n-1;i>=0;i--)b[--buc[wv[i]]]=a[i];
}
inline int c0(int *s,int a,int b)
{
    return s[a]==s[b] && s[a+1]==s[b+1] && s[a+2]==s[b+2];
}
inline int c12(int k,int *s,int a,int b)
{
    if(k==2)return s[a]<s[b] || (s[a]==s[b] && c12(k-1,s,a+1,b+1));
    return s[a]<s[b] || (s[a]==s[b] && wv[a+1]<wv[b+1]);
}
#define f(x) ((x)/3+((x)%3==1?0:tb))
#define g(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
void dc3(int *s,int *sa,int n,int m)
{
    int i,j,*sn=s+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
    s[n]=s[n+1]=0;
    for(i=0;i<n;i++)if(i%3!=0)wa[tbc++]=i;
    bsort(s+2,wa,wb,tbc,m),bsort(s+1,wb,wa,tbc,m),bsort(s,wa,wb,tbc,m);
    for(sn[f(wb[0])]=0,p=1,i=1;i<tbc;i++)sn[f(wb[i])]=c0(s,wb[i-1],wb[i])?p-1:p++;
    if(p<tbc)dc3(sn,san,tbc,p);
    else for(i=0;i<tbc;i++)san[sn[i]]=i;
    for(i=0;i<tbc;i++)if(san[i]<tb)wb[ta++]=san[i]*3;
    if(n%3==1)wb[ta++]=n-1;
    bsort(s,wb,wa,ta,m);
    for(i=0;i<tbc;i++)wv[wb[i]=g(san[i])]=i;
    for(i=j=p=0;i<ta && j<tbc;p++)sa[p]=c12(wb[j]%3,s,wa[i],wb[j])?wa[i++]:wb[j++];
    for(;i<ta;p++)sa[p]=wa[i++];
    for(;j<tbc;p++)sa[p]=wb[j++];
}
#undef f
#undef g
void calheight(int *s,int *sa,int n,int *rk,int *ht)
{
    register int i,j,k=0;
    for(i=1;i<=n;++i)rk[sa[i]]=i;
    for(i=0;i<n;ht[rk[i++]]=k)for(k?k--:0,j=sa[rk[i]-1];s[i+k]==s[j+k] && k<n;++k);
    return;
}
char s[N3];
int n,ss[N3],sa[N3],rk[N3],ht[N3];
int p[N3],S[N3];
int que[N3],hd,tl,cnt[N3];
int main()
{
    int NN=gi(),n=0,sep=0;
    if(NN==1)return printf("%d\n",gi()),0;
    while(NN--){
        int t=gi(),lst=gi();
        while(--t){
            int x=gi();
            S[n++]=lst-x+10000;
            lst=x;
        }
        S[n++]=++sep;
    }
    s[n]=0;
    dc3(S,sa,n+1,20000);
    calheight(S,sa,n,rk,ht);
    int k=1;
    for(int i=0;i<n;++i)if(S[i]>1000)p[i]=k;else ++k;//p[i]是后缀i属于原来的第几个串
    int CNT=0,r=k,Mx=0;//cnt是原来每个串的出现次数，CNT是总的
    hd=tl=0;
    --k;
    for(int i=k+1;i<=n;++i){
        while(r<=n&&CNT<k){
            if(cnt[p[sa[r]]]++==0)++CNT;
            if(r){
                while((hd^tl)&&ht[que[tl-1]]>ht[r])--tl;
                que[tl++]=r;
            }
            ++r;
        }
        if(CNT<k)break;
        while((hd^tl)&&que[hd]<=i)++hd;
        if(hd^tl)Mx=std::max(Mx,ht[que[hd]]);
        if(--cnt[p[sa[i]]]==0)--CNT;
    }
    printf("%d\n",Mx+1);
    return 0;
}
```

（大括号换行的是蒯的板子，不换行的也就是核心代码是我自己写的，DC3只是为了保证复杂度而已）

---

## 作者：beng (赞：1)

# 主要算法：差分+二分答案+KMP（还有一点点的暴力）

~~（写了一天的题怎么能不发篇题解纪念一下呢qwq）~~

本题要求我们在所有数列中找出最长的公共子串，但略有特殊的是：只要一个数列的所有数同时加上一个相同的数就可以变成另一个数列，例如$(1,3,6,7,10)$和$(2,4,7,8,11)$和$(11,13,16,17,20)$等数列是等价的。

我们可以发现，虽然数列中的值会有所变化，但相邻两个数的差是不会变的。这样我们就可以把原始数列变成**差分**数列，这样问题就转化成了普通的**在所有数列中找出最长的公共子串**的问题。

于是我们可以先固定一个模式串，再与其他数列一一匹配，若都匹配通过，则这个答案是可以达到的。

现在我们怎么确定这个模式串呢，其实随便选一个数列都可以为格式串，但最优我们可以选那个**最短的数列为格式串**，并保证了格式串长度一定小于等于其他的数列。

但我们可以发现：一个模式串与其他数列匹配不一定要从第一个开始，事实上它从任意位置开始匹配都是可行的。

因此我们KMP匹配时，可以用许多个$fail$数组，来分别表示该模式串后$i$个数组成的数列的$fail$数组。例如$(2,3,1,3)$这个模式串，我们就可以记录$(2,3,1,3)$、$(3,1,3)$、$(1,3)$、$(3)$这四个数列的$fail$数组。（有点小暴力qwq）

接下来就要开始搜索答案了。我们可以比较容易的发现，这题的答案是满足**二分答案**的性质的，因此我们可以二分这个公共子串的长度，再验证答案。

~~（这就是我花了一天时间才写完的题qwq）~~

------------

pascal代码如下：
```pascal
var n,m,i,j,l,x,y,r,mid,min:longint;
a:array[1..1000,1..100]of longint;//各个数列
len:array[0..1000]of longint;//各个数列的长度
f:array[1..100,1..100]of longint;//模式串的各个fail数组
function go(x:longint):boolean;
var i,j,k,l:longint;
ch:boolean;
begin
  for k:=1 to len[min]-x+1 do//每个点为起点的情况都搜一遍
  begin
    for l:=1 to n do//与每个数列作比较
    if l<>min then
    begin
      j:=0;
      ch:=false;
      for i:=1 to len[l] do
      begin
        //因起点不同，所以这里的以下关于j的操作要非常小心，思维不清晰很容易出错
        while (j>0)and(a[l,i]<>a[min,j+k]) do
        j:=f[k,j+k-1];
        if a[l,i]=a[min,j+k] then
        begin
          inc(j);
          if j=x then//找到该模式子串，退出
          begin
            ch:=true;
            break;
          end;
        end;
      end;
      if not ch then//如果该数列不包含该模式子串，直接退出并以模式串的下一个点为起点继续搜
      break;
    end;
    if ch then//每个数列都包含该模式子串
    exit(true);
  end;
  exit(false);
end;
begin
  readln(n);
  len[0]:=maxlongint;
  for m:=1 to n do//读入时直接把原始数列变为差分数列
  begin
    read(len[m],x);
    dec(len[m]);
    if len[m]<len[min] then
    min:=m;//最短的数列为模式串
    for l:=1 to len[m] do
    begin
      read(y);
      a[m,l]:=y-x;
      x:=y;
    end;
    readln;
  end;
  for l:=1 to len[min] do
  begin
    j:=0;
    for i:=l+1 to len[min] do//生成模式串中各个点为第一个点的fail数组
    begin
      //因起点不同，所以这里的以下关于j的操作要非常小心，思维不清晰很容易出错
      while (j>0)and(a[min,j+l]<>a[min,i]) do
      j:=f[l,j+l-1];
      if a[min,j+l]=a[min,i] then
      inc(j);
      f[l,i]:=j;
    end;
  end;
  l:=1;
  r:=len[min];
  while l<=r do//二分答案
  begin
    mid:=(l+r) div 2;
    if go(mid) then
    l:=mid+1
    else
    r:=mid-1;
  end;
  writeln(r+1);//因我们是用查分数列比较，而原始数列比查分数列多一个数，所以答案+1
end.
```

---

## 作者：Kelin (赞：1)

### 题意

给你$n$个串,求最长公共子串

定义两个如果长度相同,并且他们都加上一个数会变成一样的就相同

---

### 题解

其实说白了就是两个串的差分数组相同他们就相同

当然如果两个差分数组的第一个数不同也没关系

所有答案就是原来所有串的差分数组的$Len(LCS)+1$

多串$lcs$参考~~模板~~[$[Spoj1812]LCS2$](https://kelin.blog.luogu.org/solution-sp1812)

~~只需要变下输入就好了~~

嗯,毕竟多年的老题目了,其实$\sum m$可以开到$10^6$的

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
const int N=1e5+5,M=2*N;
typedef int arr[N];
struct SAM{
    int las,T,fa[M],len[M];map<int,int>ch[M];
    SAM(){las=T=1;}
    inline void ins(int c){
        int p=las,np;fa[las=np=++T]=1,len[T]=len[p]+1;
        for(;p&&!ch[p][c];p=fa[p])ch[p][c]=np;
        if(p){
            int q=ch[p][c],nq;
            if(len[p]+1==len[q])fa[np]=q;
            else{
                fa[nq=++T]=fa[q],len[T]=len[p]+1;ch[nq]=ch[q];
                for(fa[q]=fa[np]=nq;ch[p][c]==q;p=fa[p])ch[p][c]=nq;
            }
        }
    }
    int c[M],b[M];
    inline void pre(){
        fp(i,1,T)++c[len[i]];
        fp(i,1,T)c[i]+=c[i-1];
        fp(i,1,T)b[c[len[i]]--]=i;
        memset(mi,63,sizeof mi);
    }
    int mx[M],mi[M];
    inline void work(int*s,int n){
        int l=0,x=1,c;
        fp(i,2,n){
		    c=s[i]-s[i-1];while(x&&!ch[x][c])x=fa[x],l=len[x];
            if(x)++l,x=ch[x][c],cmax(mx[x],l);else x=1,l=0;
        }
        fd(i,T,1){
            int u=b[i],f=fa[u];
            cmax(mx[f],min(mx[u],len[f]));
            cmin(mi[u],mx[u]);mx[u]=0;
        }
    }
}p;
int n,m,ans,s[N];
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n);sd(m),sd(s[1]);
    fp(i,2,m)sd(s[i]),p.ins(s[i]-s[i-1]);
    p.pre();
	fp(i,2,n){
		sd(m);fp(i,1,m)sd(s[i]);
    	p.work(s,m);
	}
    fp(i,1,p.T)cmax(ans,p.mi[i]);
    printf("%d",ans+1);
return 0;
}
```

---

## 作者：lxd150039 (赞：0)

既然都用KMP，我来讲讲后缀数组吧。

先要把所有差分后的串搞到一起，注意加分割符号，而且，每个分割符号都应该不同！！！！！

然后，求出height[]。二分答案，对于一个可能的长度t，我们看看height里面所有大于t的连续段看成一整段，判断是否存在一段中是否包含了所有串。若有，则成功，否则失败。

···cpp


    
    
```cpp
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 1505
const long inf=0xfffffff;
using namespace std;
struct tzy{long a,p;};
long l[N],f[N][N],s[N*N/10],len=0,bl[N*N/10],pos[N*N/10];
long n,nn,m,i,j,k,p,ans,height[N*N/10],rk[N*N/10],sa[N*N/10],H[N*N/10];
long tmp[N*N/10],x[N*N/10];
bool mark[N];
tzy e[N*N/10];
bool cmp(tzy a,tzy b){return a.a<b.a;}
bool eq(long f[],long a,long b,long w){return f[a]==f[b]&&f[a+w]==f[b+w];}
void Rsort()
{
    long i;
    for (i=0; i<=m; i++) tmp[i]=0;
    for (i=1; i<=n; i++) tmp[rk[x[i]]]++;
    for (i=1; i<=m; i++) tmp[i]+=tmp[i-1];
    for (i=n; i; i--) sa[tmp[rk[x[i]]]]=x[i],tmp[rk[x[i]]]--;
}
void getSA()
{
    long i,w,p;
    for (i=1; i<=n; i++) rk[i]=s[i],x[i]=i;
    Rsort();
    for (w=1,p=1; p<n; w*=2,m=p)
    {
        for (p=0,i=n-w+1; i<=n; i++) p++,x[p]=i;
        for (i=1; i<=n; i++) if (sa[i]>w) p++,x[p]=sa[i]-w;
        Rsort();
        memcpy(x,rk,sizeof(x)); rk[sa[1]]=p=1;
        for (i=2; i<=n; i++) rk[sa[i]]=eq(x,sa[i],sa[i-1],w)?p:++p;
    }
}
void getHeight()
{
    long i,j,k=0;
    for (i=1; i<=n; i++)
    {
        for (k=k?k-1:k,j=sa[rk[i]-1]; s[i+k]==s[j+k]; k++);
        H[i]=k;
    }
    for (i=1; i<=n; i++) height[rk[i]]=H[i];
}
bool chk(long t)
{
    long i,j,d=0;
    t--;
    for (i=1; i<=n; i++)
    {
        if (height[i]>=t&&bl[i]) mark[bl[i]]=mark[bl[i-1]]=1;
        else{
            d=1;
            for (j=1; j<=nn; j++) if (!mark[j]) d=0;
            if (d) {return 1;}
            for (j=i-1; j&&height[j]>=t; j--) mark[bl[j]]=mark[bl[j-1]]=0;
        }
        if(!bl[i]) break;
    }
    return 0;
}
int main()
{
    cin>>n; nn=n;
    long L=1,R=N,M;
    for (i=1; i<=n; i++)
    {
        cin>>l[i]; R=min(R,l[i]);
        for (j=1; j<=l[i]; j++) {cin>>f[i][j]; if (j>1) len++,e[len].a=f[i][j]-f[i][j-1],e[len].p=len,pos[len]=i;}
        len++; e[len].a=inf+i,e[len].p=len,pos[len]=0;
    }
    sort(e+1,e+len+1,cmp);
    for (i=1,m=0; i<=len; i++) m=(i==1||e[i].a!=e[i-1].a)?m+1:m,s[e[i].p]=m;//li sanhua!
    n=len; getSA(); getHeight();
    for (i=1; i<=n; i++) bl[i]=pos[sa[i]];
    while (L<R)
    {
        memset(mark,0,sizeof(mark));
        M=(L+R)/2;
        if (chk(M+1)) L=M+1; else R=M;
    }
    cout<<L;
}
```
```cpp

---

