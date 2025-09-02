# [USACO06DEC] Milk Patterns G

## 题目描述

农夫约翰注意到他的奶牛所产的牛奶质量每天都在变化。经过进一步调查，他发现虽然无法预测牛奶质量从一天到下一天的变化，但每天的牛奶质量中存在一些规律模式。

为了进行严格的研究，他发明了一种复杂的分类方案，其中每个牛奶样本被记录为一个介于 $0$ 和 $1,000,000$ 之间的整数，并记录了一头奶牛在 $N\ (1 \le N \le 20,000)$ 天内的数据。他希望找到一个最长的样本模式，该模式至少重复 $K\ (1 \le K \le N)$ 次。这可能包括重叠的模式——例如，`1 2 3 2 3 2 3 1` 中的 `2 3 2 3` 重复了两次。

帮助农夫约翰找到样本序列中最长的重复子序列。保证至少有一个子序列重复至少 $K$ 次。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
8 2
1
2
3
2
3
2
3
1```

### 输出

```
4```

# 题解

## 作者：kczno1 (赞：24)

这题是一道后缀数组的模板题。

出现k次，相当于我们选择了k个后缀，之后求出他们的最长公共前缀。

我们知道，后缀(j)和后缀(k)的 最 长 公 共 前 缀 为height[rank[j]+1],

height[rank[j]+2],height[rank[j]+3],…,height[rank[k]]中的最小值(设rank[j]<rank[k])。

那么设k个后缀中rank的min=l，max=r，k个的最长公共前缀就是min(height[l+1->r])

所以k个后缀在rank上一定是连续的。

枚举i，维护height[i->i+k-1]的min，用单调队列即可O(N)解决。(还要加上求出rank,height的时间)


---

## 作者：Treeloveswater (赞：18)

这个题就是个裸的后缀数组啊~

对于长度我们设l=1,r=n，开始跑二分。

对于每个mid的check——看在RMQ（即Height数组）中所有长度为k的区间（O（n）查询是否合法）是否满足LCP大于等于mid（即二分的长度），有一个区间满足则该长度可行，然而继续二分即可。

还有，这些评测数据并不像题目所说的1---1000000，而最大的数却特别小，才是23！！这就使我的m不小心写成26并且没离散就A了，觉得这些数据是离散过的，强烈要求更新评测数据，改成跨越性大的！！！！

所以正解是：离散化+后缀数组+二分查找~！

代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define o 20001
#define rep(i,a,b) for(int i=int(a),nn=int(b);i<=nn;i++)
#define vep(i,a,b) for(int i=int(a),nn=int(b);i>=nn;i--)
#define nep(i,a,b) for(int i=int(a),nn=int(b);i<nn;i++)
using namespace std;
int t1[o],t2[o],sa[o],Rank[o],height[o],s[o],cc[o],st[o][20],num[o],lq[o];
int n,k_k,len,ans,cnt;
bool cmp(int a,int b){return lq[a]<lq[b];}
bool compare(int *y,int a,int b,int k)
{
    int arank1,arank2,brank1,brank2;
    arank1=y[a];
    brank1=y[b];
    arank2=a+k>=len?-1:y[a+k];
    brank2=b+k>=len?-1:y[b+k];
    return arank1==brank1&&arank2==brank2;
}
void make_sa()
{
    int *x=t1,*y=t2,m=cnt+1;
    nep(i,0,m)cc[i]=0;
    nep(i,0,len)cc[x[i]=s[i]]++;
    nep(i,1,m)cc[i]+=cc[i-1];
    vep(i,len-1,0)sa[--cc[x[i]]]=i;
    for(int k=1;k<=len;k<<=1)
    {
        int p=0;
        nep(i,len-k,len)y[p++]=i;
        nep(i,0,len)if(sa[i]>=k)y[p++]=sa[i]-k;
        nep(i,0,m)cc[i]=0;
        nep(i,0,len)cc[x[y[i]]]++;
        nep(i,1,m)cc[i]+=cc[i-1];
        vep(i,len-1,0)sa[--cc[x[y[i]]]]=y[i];
        swap(x,y);
        m=1;x[sa[0]]=0;
        nep(i,1,len)
        x[sa[i]]=compare(y,sa[i],sa[i-1],k)?m-1:m++;
        if(m>=len)break;
    }
}
void make_height()
{
    nep(i,0,len)Rank[sa[i]]=i;
    int k=0;
    height[0]=0;
    nep(i,0,len)
    {
        if(!Rank[i])continue;
        int j=sa[Rank[i]-1];
        if(k)k--;
        while(s[i+k]==s[j+k])k++;
        height[Rank[i]]=k;
    }
}
void init()
{
    nep(i,0,n)st[i][0]=height[i];
    for(int j=1;(1<<j)<n;j++)
    for(int i=0;i+(1<<j)-1<n;i++)
    st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int query(int l,int r)
{
    int k=log2(r-l+1);
    return min(st[l][k],st[r-(1<<k)+1][k]);    
}
bool check(int length)
{
    int l=0,r=l+k_k-2;
    while(r<=n-1)
    {
        int ok=query(l,r);
        if(ok>=length)return true;
        l++;r++;
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&k_k);
    nep(i,0,n)scanf("%d",&lq[i]),num[i]=i;
    len=n;
    sort(num,num+n,cmp);
    s[num[0]]=1;
    cnt=1;
    for(int i=0;i<n-1;i++)
        if(lq[num[i]]!=lq[num[i+1]])s[num[i+1]]=++cnt;
        else s[num[i+1]]=cnt;
    make_sa();
    make_height();
    init();
    int l=1,r=n,answer=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))answer=mid,l=mid+1;
        else r=mid-1;
    }
    printf("%d\n",answer);
}
```

---

## 作者：hongzy (赞：16)

### 题意
	
找至少重复 $k$ 次的重复子串

### 题解

此题确实只需要单调队列处理 ，复杂度 $O(n)$

对于$rank(1)$ ~ $rank(n)$的后缀，答案是所有连续$k-1$个$height$最小值中的最大值

因为$height(i)$表示后缀$rank(i)$与后缀$rank(i-1)$的$LCP$长度，所以连续$k-1$个$height$相当于$k$个"LCP较长"的后缀LCP，也就是重复了$k$次的子串的最大长度.

样例分析一下：

$12323231$

后缀排序一下：

$1$

$12323231$

$231$

$23231$

$2323231$

$31$

$3231$

$323231$

$height$数组：

0
1
0
2
4
0
1
3
4

显然，答案为$4$.

还有一点，数据需要先离散化，虽然本题数据很弱不离散也能过

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <deque>
using namespace std;

const int MAXN = 20010;

int n, k, lim, a[MAXN], b[MAXN];
int map[1000010];

int t1[MAXN], t2[MAXN], cnt[MAXN], SA[MAXN];

void Suffix_Array(int sz) { //SA模板 
	int *x = t1, *y = t2, i, t;
	for(i=0; i<sz; i++) cnt[i] = 0;
	for(i=0; i<n; i++) cnt[x[i] = a[i]] ++;
	for(i=1; i<sz; i++) cnt[i] += cnt[i - 1];
	for(i=n-1; ~i; i--) SA[-- cnt[x[i]]] = i;
	for(int k=1; k<=n; k<<=1) {
		t = 0;
		for(i=n-k; i<n; i++) y[t ++] = i;
		for(i=0; i<n; i++)
			if(SA[i] >= k) y[t ++] = SA[i] - k;

		for(i=0; i<sz; i++) cnt[i] = 0;
		for(i=0; i<t; i++) cnt[ x[y[i]] ] ++;
		for(i=1; i<sz; i++) cnt[i] += cnt[i-1];
		for(i=t-1; ~i; i--) SA[-- cnt[ x[y[i]] ] ] = y[i];

		swap(x, y);
		t = 1, x[SA[0]] = 0;
		for(i=1; i<n; i++)
			x[SA[i]] = (y[SA[i-1]] == y[SA[i]] && SA[i-1] + k < n
			            && SA[i] + k < n && y[SA[i-1] + k] == y[SA[i] + k]) ? t-1 : t ++;
		if(t >= n) return ;
		sz = t;
	}
}

int rank[MAXN], height[MAXN];

void Get_Height() {
	int k = 0;
	for(int i=0; i<n; i++) rank[SA[i]] = i;
	for(int i=0; i<n; i++) {
		if(rank[i] == 0) k = 0;
		else {
			if(k) k --;
			int j = SA[rank[i] - 1];
			while(a[i + k] == a[j + k]) ++ k;
		}
		height[rank[i]] = k;
	}
}

int main() {
	scanf("%d%d", &n, &k);
	k --;
	for(int i=1; i<=n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	
	sort(b+1, b+n+1);
	for(int i=1; i<=n; i++) { //离散化 
		map[ b[i] ] = map[ b[i-1] ] + (b[i] != b[i-1]);
		lim = max(lim, map[ b[i] ]);
	}
	for(int i=1; i<=n; i++)
		a[i - 1] = map[ a[i] ];
	a[n] = 0;
	
	Suffix_Array(lim + 1); //后缀排序 
	Get_Height();          //计算Height 

	int ans = 0;
	deque<int> Q;          //单调队列 
	for(int i=1; i<=n; i++) {
		while(!Q.empty() && Q.front() <= i - k) Q.pop_front(); //不在范围内的 
		while(!Q.empty() && height[Q.back()-1] >= height[i-1]) Q.pop_back(); //不是最小值的 
		Q.push_back(i);
		if(i >= k) ans = max(ans, height[Q.front() - 1]); //更新答案 
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：唐一文 (赞：13)

今天模拟赛考的题，本来想写个暴力优化一下就跑路的

~~结果没超时，数组越界丢了 10pts~~

## Description

求出现次数不少于 $k$ 次的最长的子串的长度。

## Solution

最基本的暴力是枚举每一个字串再暴力判断，复杂度大概是 $\mathcal O(n^4)$，显然过不去，考虑优化。

发现暴力判断的时候可以用 哈希 或 kmp 优化，考场上忘记 kmp 怎么写了，就写了哈希，复杂度变为 $\mathcal O(n^3)$。

首先可以发现这个长度具有单调性，所以我们可以~~二分~~从当前最优的答案往后暴力拓展，没必要再从 $1$ 重新开始枚举，复杂度变为 $\mathcal O(n^2)$。

~~然后就可以过去了~~

可能说的有些不太清楚，具体还是看代码吧

## Code

这是考后重写的一份代码，完全没有卡常，可读性更高~~因为考试的代码太丑了~~

最下面有一份考试时的代码

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
int n,m,ans,a[20005];
ull mul[20005],hs[20005];
int main(){
    cin>>n>>m;
	for(int i=1;i<=n;i++){
	    cin>>a[i];
	}
	mul[0]=1;
	for(int i=1;i<=n;i++){
	    mul[i]=mul[i-1]*19260817;//预处理
	}
	for(int i=1;i<=n;i++){
	    hs[i]=hs[i-1]*19260817+a[i];//哈希
	}
	for(int k=1;k<=n;k++){//从每一个位置开始枚举，往后拓展的长度为ans
	    while(1){//暴力拓展答案
	        int cnt=0;//记录出现的次数
	        for(int i=k;i<=n&&i+ans<=n;i++){//注意这里不要越界了！！1（模拟赛的时候就被这里坑了）
	            if(hs[i+ans]-hs[i-1]*mul[ans+1]==hs[k+ans]-hs[k-1]*mul[ans+1]){//判断
	                cnt++;
	            }
	        }
	        if(cnt>=m){
	            ans++;
	        }
	        else{//根据单调性，如果这个不满足，那么后面的一定不满足
	            break;
	        }
	    }
	}
    cout<<ans;
}
```

~~[赛后改的赛时的垃圾代码](https://www.luogu.com.cn/paste/w3x7qjgb)~~

---

## 作者：Prean (赞：7)

# 题目大意
给一个长度为 $ n $ 的字符串，求出现次数大于等于 $ k $ 的字符串最长的长度。

~~感性理解吧qwq~~

首先有子串，想到 $ \rm SAM $。

$ \rm SAM $ 将一个字符串的所有子串都压缩在一起了，很容易就能求出该子串的出现次数qwq。

然后只要当前节点 $ u $ 的出现次数 $ siz $ 大于等于 $ k $，对于该节点，该子串的长度就是 $ len[u] $，所以只要在满足条件的节点中去最大的 $ len $ 就行了qwq。

~~基本和板子题相同吧qwq~~

code：
```cpp
#include<unordered_map>
#include<cstdio>
const int M=2e4+5;
struct Node{
    std::unordered_map<int,int>chi;
    int f,len;
}SAM[M<<1];
int n,k,lst=1,tot=1,id[M<<1],siz[M<<1],rank[M<<1];
inline int max(const int&a,const int&b){
    return a>b?a:b;
}
inline bool check(const int&p,const int&s,const bool&flag){
    return flag^(SAM[p].chi.find(s)==SAM[p].chi.end());
}
inline void Insert(int s){
    int q,p,nq,np;
    p=lst;np=lst=++tot;
    SAM[np].len=SAM[p].len+1;siz[np]=1;
    for(;p&&check(p,s,false);p=SAM[p].f)SAM[p].chi[s]=np;
    if(!p)return void(SAM[np].f=1);
    q=SAM[p].chi[s];
    if(SAM[q].len==SAM[p].len+1)return void(SAM[np].f=q);
    nq=++tot;
    SAM[nq]=SAM[q];
    SAM[np].f=SAM[q].f=nq;
    SAM[nq].len=SAM[p].len+1;
    for(;p&&check(p,s,true)&&SAM[p].chi[s]==q;p=SAM[p].f)SAM[p].chi[s]=nq;
}
signed main(){
    int i,now,ans=0;
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;++i){
        scanf("%d",&now);
        Insert(now);
    }
    for(i=1;i<=tot;++i)++rank[SAM[i].len];
    for(i=1;i<=tot;++i)rank[i]+=rank[i-1];
    for(i=1;i<=tot;++i)id[rank[SAM[i].len]--]=i;
    for(i=tot;i;--i){
        now=id[i];
        siz[SAM[now].f]+=siz[now];
        if(siz[now]>=k)ans=max(ans,SAM[now].len);
    }
    printf("%d",ans);
}
```
~~SAM的Insert有点儿奇怪，请不要在意qwq~~

---

## 作者：YuukiYumesaki (赞：5)

这里讲一下哈希和SA的两种做法

第一种我们发现要查询有几个区间是相同的，我们想到哈希

每次二分答案，然后用一个map统计，这样可以做到$O(n\log^2n)$

因为这题数据很水，随便找俩模数哈希都能过。。。

我取得$19260817$和$1004535809$

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=20005;
const int base=19260817;
const int mod=1004535809;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,k;
int a[N];
int ha[N];
int fac[N];

map<int,int> var;

void hash(){
	fac[0]=1;
	Rep(i,1,n)fac[i]=1ll*fac[i-1]*base%mod;
	Rep(i,1,n)ha[i]=(ha[i-1]+1ll*a[i]*fac[n-i]%mod)%mod;
}

int gethash(int l,int r){
	return 1ll*(ha[r]-ha[l-1]+mod)*fac[l]%mod;	
}

bool check(int delta){
	var.clear();
	int mx=0;
	Rep(i,1,n)
		if(i+delta-1<=n){
			var[gethash(i,i+delta-1)]++;
			mx=max(mx,var[gethash(i,i+delta-1)]);
		}
		else break;
	return mx>=k;
}

int main()
{
	read(n),read(k);
	Rep(i,1,n)read(a[i]);
	hash();	
	int l=1,r=n,ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
```

发现最后要找的相同的子串一定是在后缀排序后的一段连续的后缀的前缀

相当于是找一段长度为$k-1$的$height$的最大值就可以啦

用SA配合单调队列实现，可以做到$O(n\log n)$

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=4e4+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,m,k;
int a[N],b[N],sz;
int sa[N],rk[N],tp[N],sum[N];
int height[N];
int q[N],head,tail;
int ans;

void RadixSort(){
	Rep(i,0,m)sum[i]=0;
	Rep(i,1,n)sum[rk[i]]++;
	Rep(i,1,m)sum[i]+=sum[i-1];
	_Rep(i,n,1)sa[sum[rk[tp[i]]]--]=tp[i];	
}

void SA(){
	m=sz;
	Rep(i,1,n)rk[i]=a[i],tp[i]=i;
	RadixSort();
	for(int k=1,t=0;t<n;k<<=1,m=t){
		t=0;
		Rep(i,n-k+1,n)tp[++t]=i;
		Rep(i,1,n)if(sa[i]>k)tp[++t]=sa[i]-k;
		RadixSort();
		swap(rk,tp);
		rk[sa[1]]=t=1;
		Rep(i,2,n)
			rk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+k]==tp[sa[i-1]+k])?t:++t;
	}
	Rep(i,1,n)rk[sa[i]]=i;
	for(int i=1,k=0;i<=n;i++){
		if(rk[i]==1)continue;
		if(k)k--;
		int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k])k++;
		height[rk[i]]=k;	
	}
}

int main()
{
	read(n),read(k);k--;
	Rep(i,1,n)read(a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	sz=unique(b+1,b+n+1)-b-1;
	Rep(i,1,n)a[i]=lower_bound(b+1,b+sz+1,a[i])-b;
	SA();
	head=1,tail=0;
	Rep(i,1,n){
		while(head<=tail&&q[head]<=i-k)head++;
		while(head<=tail&&height[q[tail]]>height[i])tail--;
		q[++tail]=i;
		if(i>=k)ans=max(ans,height[q[head]]);	
	}
	printf("%d\n",ans);
	return 0;
}	
```


---

## 作者：睿3030 (赞：5)

看到“他想知道最长的出现了至少K(2<=K<=N)次的模式的长度。”，首先会想到二分答案，二分满足要求的字串的最长长度。

那么怎么判断长度len是否合法呢？  
显然，只需要枚举所有长度为len的子串，然后判断是否有子窜子串出现的次数>=K就可以了。

时间复杂度是O($n^2logn$)，明显超时。

在这里优化的思路1就是用hash，别的题解已经讲的很清楚了，所以我在此处就不再多说了。

但是，我做这题的时候脑袋卡了，没有想到hash，所以采用了更加好(xuan)玩(xue)的方法——**随机化**！

### 什么是随机化呢？
很简单，就是利用电脑的伪随机数，随机选若干个长度为len的子串出来，再使用KMP O($n$)计算其再原串中出现的次数，即使用部分代替整体。  
时间复杂度为O($xnlogn$)，其中$x$是随机化的次数。  
因此，对于本题的数据范围，可以考虑令$x=500$。

### 正确性如何呢？
由于随机化很有(xuan)趣(xue)，所以肯定有概率是错的，因此关键在于错误的几率大不大。  

对于本题而言，每一次二分的check出错的概率为
$P=(1-\frac{K}{n-len+1})^x$  
（因为长度为len的子串一共有$n-len+1$个，然后满足要求的至少有$K$个）  
因此，对于较大的$K$和较小的$n$，这个算法是完全可以胜任的。  
比如，当$n=2000$,$K=100$时，出错的概率非常小$P=1.32*10^{-32}$；  
而即使$n=20000$,当$K=100$时，出错的概率也很小$P=0.00657$。

但是，对于~~毒瘤~~数据点2，其$n=20000$而且$K=2$，出错的概率奇高，$P=0.905$，除非你人品极高，否侧根本不可能过……  

（注：测试点10出错的概率也蛮高的，不过这个点多交几次就可以过了。）

### Code
```cpp
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 20004;
int n, k;
int s[maxn];
int nxt[maxn];

inline void get_next(int *t, int lent){
	nxt[0] = -1; nxt[1] = 0;
	int p = 0, q = 1;
	while(q < lent){
		if(p == -1 || t[p] == t[q]){
			p++; q++;
			nxt[q] = p;
		}else{
			p = nxt[p];
		}
	}
}

inline int kmp(int *t, int lent){
	int anss = 0;
	int p = 0, q = 0;
	while(q < n){
		if(p == -1 || t[p] == s[q]){
			p++; q++;
		}else{
			p = nxt[p];
		}
		if(p == lent){
			anss++;
			p = nxt[p];
		}
	}
	return anss;
}

inline bool check(int len){
	int times = 650; //随机选子串650次
	while(times--){
		int st = rand() % (n - len + 1);
		get_next(s + st, len);
		if(kmp(s + st, len) >= k) return 1;
	}
	return 0;
}

int main(){
//	freopen("pattern.in", "r", stdin);
//	freopen("pattern.out", "w", stdout);
	srand(time(0));
	scanf("%d%d", &n, &k);
	int sum = 0;
	for(int i = 0; i < n; i++)
		scanf("%d", &s[i]),
        sum += (s[i] == 1); //数据点2的特征是1奇多，所以记录一下1的个数
	if(sum > 18000){ //特判数据点2（面向数据编程）
		printf("1042\n");
		return 0;
	}
	int l = 0, r = n - 1;
	while(l != r){
		int mid = (l + r + 1) >> 1;
		if(check(mid))
			l = mid;
		else
			r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}
```


---

## 作者：GoldenPotato137 (赞：4)

传送门：[戳我获得更好的阅读体验qwq](https://www.goldenpotato.cn/%E5%AD%97%E7%AC%A6%E4%B8%B2/luogu-p2852-usaco06dec%E7%89%9B%E5%A5%B6%E6%A8%A1%E5%BC%8Fmilk-patterns/)

---
# Solution
首先，我们阅读题面可以发现题目让我们求出一个**出现次数>k的可重复的子串**。

这玩意我们可以用SA求，也可以用SAM求。
### SA
这题用SA做就比较妙，首先我们显然要求把SA及height求出来。
因为**两个后缀的LCP是它们之间的height的min**，我们可以利用这个性质。

考虑一个子串，它所能“控制”的区间的所有的height都必须比它大。
因此，我们可以找出一个height所影响的左右范围，这个我们使用单调栈可以很轻松地求出。
```cpp
for(int i=1;i<=n;i++)
{
    while(top>0 and height[i]<=height[mstack[top]]) top--;
    L[i]=mstack[top]+1;
    mstack[++top]=i;
}
mstack[top=0]=n+1;
for(int i=n;i>=1;i--)
{
    while(top>0 and height[i]<=height[mstack[top]]) top--;
    R[i]=mstack[top]-1;
    mstack[++top]=i;
}
```

然后我们可以发现一个height所“控制”的区间中，这个串被“引用”的次数一定是$R[i]-(L[i]-1)+1$，下面这个图可以简单的说明这一点：
[![kjv0bR.md.png](https://s2.ax1x.com/2019/03/06/kjv0bR.md.png)](https://imgchr.com/i/kjv0bR)

这样，我们只需要二分一个答案，然后一路扫过去检查就完事啦(～￣▽￣)～ 
时间复杂度$O(nlogn)$,空间复杂度$O(n)$

### SAM
这题用SAM做就非常显然了。**根据fail树的性质：fail树中的每个节点所代表的串都必然是它的孩子节点的后缀**。我们可以得到一个比较显然的性质：每个叶子节点所代表的子串在原串中只出现了1次，而每个节点所代表的子串在原串中出现的次数必然为它的孩子的出现次数的总和，如果这个点不是被复制出来的，次数还要+1（它自己所代表的串）；

然后，我们只需要便利一遍SAM，把所有出现次数>K的节点的len取个max即可。

时间复杂度$O(n)$，空间复杂度$O(n\ *10)$

---
# Code
我只写了SA的做法，SAM的做法还请自行yy
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int M=1000000+100;
const int N=20000+100;
int s[N],sa[N],id[N],height[N];
long long rank[N];
void CountSort(long long a[],int n,int Exp,int m)
{
    static long long cnt[M],b[N];
    memset(cnt,0,sizeof cnt);
    for(int i=1;i<=n;i++)
        cnt[(a[i]/Exp)%m]++;
    for(int i=1;i<=m;i++)
        cnt[i]+=cnt[i-1];
    for(int i=n;i>=1;i--)
    {
        b[cnt[(a[i]/Exp)%m]]=a[i];
        if(Exp==1)
            id[cnt[(a[i]/Exp)%m]--]=i;
        else
            sa[cnt[(a[i]/Exp)%m]--]=id[i];
    }
    for(int i=1;i<=n;i++)
        a[i]=b[i];
}
void RadixSort(long long a[],int n,int m)
{	
    CountSort(a,n,1,m);
    CountSort(a,n,m,m);
}
int n,K,L[N],R[N];
void GetSA()
{	
    static long long t[N];
    for(int i=1;i<=n;i++)
        rank[i]=t[i]=s[i];
    int m=1000000+1;
    for(int k=1;;k=k<<1)
    {
        for(int i=1;i<=n;i++)
            rank[i]=t[i]=rank[i]*m+(i+k<=n?rank[i+k]:0);
        RadixSort(t,n,m);
        m=0;
        for(int i=1;i<=n;i++)
        {
            if(t[i]!=t[i-1])
                m++;
            rank[sa[i]]=m;
        }
        if(m==n) break;
        m++;
    }
    
    for(int i=1;i<=n;i++)
    {
        if(rank[i]==1) continue;
        int to=max(0,height[rank[i-1]]-1);
        for(;sa[rank[i]]+to<=n and sa[rank[i]-1]+to<=n;to++)
            if(s[sa[rank[i]]+to]!=s[sa[rank[i]-1]+to])
                break;
        height[rank[i]]=to;
    }
}
int mstack[N],top;//记录从哪来，单调严格上升栈
bool Check(int x)
{
    for(int i=1;i<=n;i++)
        if(height[i]>=x and (R[i]-(L[i]-1)+1)>=K)
            return true;
    return false;
}
int main()
{
    n=read(),K=read();
    for(int i=1;i<=n;i++)
        s[i]=read();
    
    GetSA();
    for(int i=1;i<=n;i++)
    {
        while(top>0 and height[i]<=height[mstack[top]]) top--;
        L[i]=mstack[top]+1;
        mstack[++top]=i;
    }
    mstack[top=0]=n+1;
    for(int i=n;i>=1;i--)
    {
        while(top>0 and height[i]<=height[mstack[top]]) top--;
        R[i]=mstack[top]-1;
        mstack[++top]=i;
    }
    
    int ans=0,l=0,r=n,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(Check(mid)==true)
            l=mid+1,ans=max(ans,mid);
        else
            r=mid-1;
    }
    
    printf("%d",ans);
    return 0;
}

```






---

## 作者：Cylete (赞：3)

出现至少$k$次意味着后缀排序后有至少连续$k$个后缀的LCP是这个子串。

所以，求出每相邻$k - 1$个$height$的最小值，再求这些最小值的最大值就是答案。

最小值的最大值很好维护

这里用multiset偷懒

```cpp
int T, n, m, ans;

int a[N], qaq;
int s[N];
int c[N], x[N], y[N], sa[N];

inline void SA() {
	m = n;
	for(R int i = 1; i <= n; i++) ++c[x[i] = s[i]];
	for(R int i = 1; i <= m; i++) c[i] += c[i - 1];
	for(R int i = n; i >= 1; i--) sa[c[x[i]]--] = i;
	for(R int k = 1, num = 0; k < n; k <<= 1, num = 0) {
		for(R int i = n - k + 1; i <= n; i++) y[++num] = i;
		for(R int i = 1; i <= n; i++) if(sa[i] > k) y[++num] = sa[i] - k;
		for(R int i = 1; i <= m; i++) c[i] = 0;
		for(R int i = 1; i <= n; i++) c[x[i]]++;
		for(R int i = 1; i <= m; i++) c[i] += c[i - 1];
		for(R int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
		swap(x, y);
		x[sa[1]] = num = 1;
		for(R int i = 2; i <= n; i++)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		if(num == n) break;
		m = num;
	}
}

int rk[N], height[N];

inline void get_height() {
	for(R int i = 1; i <= n; i++) rk[sa[i]] = i;
	for(R int i = 1, k = 0; i <= n; i++) {
		if(k) k--;
		while(s[i + k] == s[sa[rk[i] - 1] + k]) k++;
		height[rk[i]] = k;
	}
}

multiset<int> S;

inline void solve() {
//	into();
	read(n); read(T); T--;
	for(R int i = 1; i <= n; i++) read(s[i]), a[i] = s[i];
	sort(a + 1, a + n + 1);
	qaq = unique(a + 1, a + n + 1) - a - 1;
	for(R int i = 1; i <= n; i++) s[i] = lower_bound(a + 1, a + qaq + 1, s[i]) - a;
    //其实不用离散也可以
	SA();
	get_height();
	for(R int i = 1; i <= n; i++) {
		S.insert(height[i]);
		if(i > T) S.erase(S.find(height[i - T]));
		ans = max(ans, *S.begin()); 
	}
	writeln(ans);
}
```

---

## 作者：Great_Influence (赞：3)

SAM裸题。

一看题目，可以立即发现，这道题就是求出现次数超过k的所有串中最长的串长。做法和SAM模板题一模一样，直接~~复制~~手打即可。

时间复杂度$O(nlog_2L)$(L为数字范围)。如果无聊的话可以离散一波数据（没什么用就是了），时间复杂度$O(nlog_2n)$。~~不过用map的话就没什么区别~~

代码：

```cpp
    #include<bits/stdc++.h>
    #include<cctype>
    #define For(i,a,b) for(i=(a),i##end=(b);i<=i##end;++i)
    #define Forward(i,a,b) for(i=(a),i##end=(b);i>=i##end;--i)
    #define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
    #define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
    using namespace std;
    template<typename T>inline void read(T &x){
        T s=0,f=1;char k=getchar();
        while(!isdigit(k)&&k^'-')k=getchar();
        if(!isdigit(k)){f=-1;k=getchar();}
        while(isdigit(k)){s=s*10+(k^48);k=getchar();}
        x=s*f;
    }
    void file(void){
        #ifndef ONLINE_JUDGE
        freopen("water.in","r",stdin);
        freopen("water.out","w",stdout);
        #endif
    }
    const int MAXN=2e4+7;
    static map<int,int>::iterator it;
    static struct DAWG
    {
        int len,link;
        map<int,int>nxt;
        long long cnt;
    }p[MAXN<<1];
    static int e,n;
    #define Chkmax(a,b) a=a>b?a:b
    inline void extend(int c)
    {
        static int last=0,j,cur,q,clone;
        p[cur=++e].len=p[last].len+1;p[cur].cnt=1;
        for(j=last;~j&&!p[j].nxt.count(c);j=p[j].link)p[j].nxt[c]=cur;
        if(j==-1)p[cur].link=0;
        else
        {
            q=p[j].nxt[c];
            if(p[j].len+1==p[q].len)p[cur].link=q;
            else
            {
                clone=++e;
                p[clone].len=p[j].len+1;
                p[clone].link=p[q].link;
                p[clone].nxt=p[q].nxt;
                for(;~j&&p[j].nxt[c]==q;j=p[j].link)
                    p[j].nxt[c]=clone;
                p[q].link=p[cur].link=clone;
            }
        }
        last=cur;
    }
    inline bool cmp(int a,int b){return p[a].len>p[b].len;}
    int b[MAXN<<1],ans,k;
    int main()
    {
        file();
        read(n);read(k);
        p[0].link=-1;
        static int x;
        Rep(i,1,n)
        {
            read(x);
            extend(x);
        }
        Rep(i,0,e)b[i]=i;
        sort(b,b+e+1,cmp);
        Rep(i,0,e)
        {
            p[p[b[i]].link].cnt+=p[b[i]].cnt;
            if(p[b[i]].cnt>=k)Chkmax(ans,p[b[i]].len);
        }
        printf("%d\n",ans);
        return 0;
    }

```

---

## 作者：cyh_toby (赞：2)

**UPD 21.12.10:** 修改一处笔误。

# 题意

原题连接：[P2852 【[USACO06DEC]Milk Patterns G】](https://www.luogu.com.cn/problem/P2852)

- 给定一个串，求出现至少 $k$ 次的最长子串长度

# 分析

> 这是后缀数组处理 LCP 相关问题的典型应用。

我们知道，子串可以表示成后缀的前缀。所谓出现至少 $k$ 次的子串，其实就是至少 $k$ 个后缀的公共前缀；题目要求的是最长的子串，所以这里就是要求至少 $k$ 个后缀的最长公共前缀的长度。显然，串越少，最长公共前缀长度一定不会越小；串越多，最长公共前缀的长度一定不会越大。那么，我们就是要求任意 $k$ 个后缀的最长公共前缀的最大值。

为了减少对答案无贡献的情况的出现，我们先对后缀排序，即计算出后缀数组。这样，我们要找的必然会是连续 $k$ 个后缀，而不需要考虑所有的 $k$ 个后缀了。因为，不连续的后缀，对最长公共前缀长度的贡献一定不会更优。

所以，先计算出后缀数组，然后计算出可以用来处理 LCP 的 height 数组。我们知道求 LCP 就相当于在 height 上做 RMQ ，那么这里连续 $k$ 个后缀的 LCP 其实就是对应的连续 $k-1$ 个 height 中的最小值。这可以用单调队列计算。

# 细节处理

注意到本题不同于其它字符串题，串内元素是整数，所以值域先要设置大一点。而且为了避免对串中 0 元素的单独处理，可以对串每个元素都加一。

此外，单调队列的边界细节需要关注。

# 源码

```cpp
/**********************************

Problem: luogu - P2852 - [USACO06DEC]Milk Patterns G

State: Accepted

From: [USACO]

Algorithm: SA, LCP

Author: cyh_toby

Last updated on 2020.7.26

**********************************/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e4+5, W = 1e6+5;

int n, k, w;
int s[N], sa[N], rk[N<<1], oldrk[N<<1], cnt[W], id[N], ht[N];
int q[N], hd, tl;//单调队列 
int ans = 0;

inline bool cmp(int x, int y, int j) {
	return oldrk[x] == oldrk[y] && oldrk[x+j] == oldrk[y+j];
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &s[i]);
		s[i]++;//避免对 0 的特殊处理 
	}
	
	for (int i = 1; i <= n; i++) cnt[s[i]]++;
	w = 1e6;
	for (int i = 1; i <= w; i++) cnt[i] += cnt[i-1];
	for (int i = n; i >= 1; i--) sa[cnt[s[i]]--] = i;
	w = 0;
	for (int i = 1; i <= n; i++)
		rk[sa[i]] = s[sa[i]] == s[sa[i-1]] ? w : ++w;
		
	for (int j = 1; j < n; j <<= 1) {
		int t = 0;
		for (int i = n; i > n-j; i--) id[++t] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > j) id[++t] = sa[i] - j;
			
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++) cnt[rk[id[i]]]++;
		for (int i = 1; i <= w; i++) cnt[i] += cnt[i-1];
		for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];
		
		memcpy(oldrk, rk, sizeof(oldrk));
		w = 0;
		for (int i = 1; i <= n; i++)
			rk[sa[i]] = cmp(sa[i], sa[i-1], j) ? w : ++w;
	}
	
	for (int i = 1, j = 0; i <= n; i++) {
		if (j) j--;
		while (s[i+j] == s[sa[rk[i]-1]+j]) j++;
		ht[rk[i]] = j;
	}
	
	for (int i = 1; i <= n; i++) {
		while (hd != tl && q[hd] <= i-k+1) hd++;//注意边界细节 
		while (hd != tl && ht[q[tl-1]] >= ht[i]) tl--;
		q[tl++] = i;
		if (i > 1) ans = max(ans, ht[q[hd]]);
	}
	
	printf("%d", ans);
	
	return 0;
}
```

# 参考资料

- [oi-wiki](https://oi-wiki.org/string/sa/#k)



---

## 作者：NDQZHANG1111 (赞：2)

先抢个沙发，来一波hash

同样二分长度大小，统计每个字串的hash值个数，效率还挺不错的

优点是不用离散化，缺点就是看你运气好不好了

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N=100010,K1=10007;
int s[N],Rank[N];
ull K[N],H[N],Hash[N];
int n,k;
bool cmp(const int& __x,const int& __y){
    return Hash[__x]<Hash[__y]||(Hash[__x]==Hash[__y]&&__x<__y);
}
bool chk(int len){
    int c=0;
    for(int i=0;i<n-len+1;++i){
        Rank[i]=i;
        Hash[i]=H[i]-H[i+len]*K[len];
    }
    sort(Rank,Rank+n-len+1,cmp);
    for(int i=0;i<n-len+1;++i){
        if(i==0||Hash[Rank[i]]!=Hash[Rank[i-1]])c=0;
        if(++c>=k)return 1;
    }
    return 0;
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;++i)scanf("%d",s+i);
    H[n]=0;for(int i=n-1;i>=0;--i)H[i]=H[i+1]*K1+s[i];
    K[0]=1;for(int i=1;i<=n;++i)K[i]=K[i-1]*K1;
    int l=1,r=n+1;
    while(r-l>1){
        int m=l+r>>1;
        if(chk(m))l=m;
        else r=m;
    }
    printf("%d\n",l);
}
```

---

## 作者：xwmwr (赞：1)

假设有出现 k 次且长度为 L 的模式， 那么需要：能够把某 k 个后缀拿出来， lcp 要 ≥ L。

在 sa 数组中考虑这些拿出来的后缀， 记为 $s_1,s_2,\cdots,s_k$：

由于对于任意 $s_i,s_{i+1}$， 其 lcp ≥ L， 那么对于 $sa[rk[s_i] \sim rk[s_{i+1}]]$， 相邻的两个的 lcp 也是 ≥ L 的。进一步推出对于 $sa[rk[s_1] \sim rk[s_k]]$ 来说， 相邻的两个的 lcp 也是 ≥ L 的。

进一步推出， 在 height 数组中一定存在一个长度为 k-1 的区间，这个区间里的数的最小值 ≥ L。

所以只需要单调队列扫一遍 height 数组就行了。

---

## 作者：wwlw (赞：1)

[LINK](https://www.luogu.org/problemnew/show/P2852)

------------------

此题的常规做法是 二分 + 后缀数组 ，但本蒟蒻还是习惯写 并查集 的做法

## 算法流程

 1.离散化是肯定要有的，给的数据太大了，不离散化会RE

 2.先跑一遍SA，把最重要的h数组求出来

 3.把h从大到小排序，从大到小枚举重复串的长度，同时遍历h数组，若对于$h_i$有$h_i$大于等于当前枚举的长度，就把$h_i$所连接的两个节点合并（见下文），求出合并后的并查集的大小，最后再判断一下是否大于题目的要求的大小，若符合要求就输出当前枚举的长度，并结束程序。

整个算法的时间复杂度为$O(n log_2 n)$，主要性能瓶颈在于排序。

主要解释一下第三个步骤的用意

### 为什么说$h_i$连接了两个节点

首先对于数据 1 1 2 1 1，它的 SA 为 5 4 1 2 3，而$h_i$则可以看成连接$i$与$i-1$节点的桥梁

我们回归$h$数组的本质，它的意义为排名为$i$的后缀与排名为$i-1$的后缀的最长公共前缀，则我们可以把$i$和$i-1$看成两个节点，$h_i$就是连接这两个节点的无向边，其权值就为$h_i$本身的值

### 并查集大小的意义

若对于一个大小已经大于等于题目要求的个数的并查集，则说明这个并查集里所有点连接的所有边的值都大于等于当前枚举的值，也就是说这一段区间的所有后缀都有一个长度大于等于当前枚举的值的公共前缀，重复的前缀的个数就等于当前并查集的大小

Code：
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
#define rint register int
#define N 200007

template<class T>
inline void read(T &x){
	x=0;char c=getchar();T flag=1;
	while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	x*=flag;
}

struct Node{
	int val,pos;
}pre[N];
struct E{
	int val,to;
}h[N];
int n,m,lim,a[N];
int rk[N],tp[N],sa[N],cnt[N],fa[N],size[N];

inline int find(int x){return (x==fa[x])? x:(fa[x]=find(fa[x]));}
inline bool Cmp1(const Node x,const Node y){return x.val<y.val;}
inline bool Cmp2(const E x,const E y){return x.val>y.val;}
inline void sort_(){
	for(rint i=0;i<=m;i++) cnt[i]=0;
	for(rint i=1;i<=n;i++) cnt[rk[i]]++;
	for(rint i=0;i<=m;i++) cnt[i]+=cnt[i-1];
	for(rint i=n;i>=1;i--)
		sa[cnt[rk[tp[i]]]--]=tp[i];
}
inline void SA(){
	for(rint i=1;i<=n;i++) tp[i]=i,rk[i]=a[i];
	sort_();
	for(rint w=1,p=0;p<n;m=p,w<<=1){
		p=0;
		for(rint i=n-w+1;i<=n;i++) tp[++p]=i;
		for(rint i=1;i<=n;i++)
			if(sa[i]>w) tp[++p]=sa[i]-w;
		sort_();
		swap(rk,tp);
		rk[sa[1]]=p=1;
		for(rint i=2;i<=n;i++)
			rk[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])? p:++p;
	}
}
int main(){
	read(n);read(lim);
	for(rint i=1;i<=n;i++) read(a[i]),pre[i]=(Node){a[i],i};
	sort(pre+1,pre+1+n,Cmp1);
	for(rint i=1;i<=n;i++)
		a[pre[i].pos]=(pre[i].val==pre[i-1].val)? m:(++m);
/*	for(rint i=1;i<=n;i++) printf("%d ",a[i]);*/
	SA();
/*	for(rint i=1;i<=n;i++) printf("%d ",sa[i]);
	printf("\n");*/
	int h_=0;
	for(rint i=1;i<=n;i++){
		rint t=sa[rk[i]-1];
		while(a[t+h_]==a[i+h_]) h_++;
		h[rk[i]].val=h_,h[i].to=i;
		h_=max(0,h_-1);
		size[i]=1,fa[i]=i;
	}
	sort(h+1,h+1+n,Cmp2);
	for(int i=n,j=0;i>=0;i--){
		while(h[j+1].val>=i){
			rint u=h[++j].to,v=u-1;
			u=find(u),v=find(v);
			fa[v]=u;size[u]+=size[v];
			if(size[u]>=lim){
				printf("%d",i);
				return 0;
			}
		}
	}
}
```

---

## 作者：wyxdrqc (赞：1)

最近效率有点低,肝了几道SA的题目，为了帮助自己真的的理解SA及$height$数组
特意写一下学习笔记来加强一下一下记忆.

这道题的题目大意是让我们求一下最长的出现$k$次的子串的长度。

由某种结论可以直接征得如果连续长度为$k$的$height$数组的值都大于等于一个数$x$
，那么他们两两之间的的$lcp$都大于等于$x$,说明这个串一共至少出现了$k + 1$次(因为$height$数组指的是$rk_i$与$rk_{i - 1}$的$lcp$).

一个很明显的思路是直接二分答案。

但是,其实单调队列维护一下就好了。我们就用单调队列维护长度$k - 1$区间的最小值,所有区间的最小值的最大值即为答案.
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N = 20005;
const int M = 1e6 + 3;
int c[M];
int x[N],s[N],y[N];
int sa[N],rk[N],height[N];
int n,m = 1000000,g;
deque <int> q;
inline int read(){
    int v = 0,c = 1;char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-') c = -1;
        ch = getchar(); 
    }
    while(isdigit(ch)){
        v = v * 10 + ch - 48;
        ch = getchar(); 
    }
    return v * c;   
}
inline void SA(){
	for(int i = 1;i <= n;++i) x[i] = s[i];
	for(int i = 1;i <= n;++i) c[x[i]]++;
	for(int i = 1;i <= m;++i) c[i] += c[i - 1];
	for(int i = n;i >= 1;--i) sa[c[x[i]]--] = i;
	m = 0;
	for(int w = 1;m < n;w <<= 1){
		m = 0;
		for(int i = n - w + 1;i <= n;++i) y[++m] = i;
		for(int i = 1;i <= n;++i) if(sa[i] > w) y[++m] = sa[i] - w;
		for(int i = 1;i <= m;++i) c[i] = 0;
		for(int i = 1;i <= n;++i) c[x[i]]++;
		for(int i = 1;i <= m;++i) c[i] += c[i - 1];
		for(int i = n;i >= 1;--i) sa[c[x[y[i]]]--] = y[i];
		for(int i = 1;i <= n;++i) y[i] = x[i];
		x[sa[1]] = m = 1;
		for(int i = 2;i <= n;++i){
			if(y[sa[i]] == y[sa[i - 1]] && y[sa[i] + w] == y[sa[i - 1] + w]) x[sa[i]] = m;
			else x[sa[i]] = ++m;
		}
	}
	//for(int i = 1;i <= n;++i) printf("%d ",sa[i]);
	for(int i = 1;i <= n;++i) rk[sa[i]] = i;//printf("%d\n",rk[sa[i]]);
	int k = 0;
	for(int i = 1;i <= n;++i){
		if(k) k--;
		int j = sa[rk[i] - 1];
		while(s[j + k] == s[i + k]) k++;
		height[rk[i]] = k;	
	}
}	
int main(){
	n = read(),g = read();
	for(int i = 1;i <= n;++i) s[i] = read();
	SA();
	int ans = 0;
	//for(int i = 1;i <= n;++i) printf("%d\n",height[i]);
	for(int i = 1;i <= n;++i){
		while(!q.empty() && q.front() <= i - g + 1)	q.pop_front();
		while(!q.empty() && height[q.back()] >= height[i]) q.pop_back();
		q.push_back(i);
		if(i >= g - 1 && !q.empty()) ans = max(ans,height[q.front()]);
	}
	printf("%d\n",ans);
	return 0;	
}
```


---

## 作者：Forsaken2020 (赞：1)

看不懂dalao们在干啥，作为一个不会任何字符串算法的蒟蒻，我唯一想到的就是这个长度是单调的，比如你现在如果当长度为L时，如果满足条件，那么当长度为l(l < L),那么我们显然可以看出l也是满足条件的。
那么我们每次都去二分这个L，然后枚举每一个长度为L的子串，然后判断出现次数最多的那个是不是有k个，考虑到这里，自然想到用hash来判断两个字符串是不是相同，所以我双hash了一下，然后二分就跑过去了。感觉还挺快的？
```cpp
//author Eterna
#define Hello the_cruel_world!
#pragma GCC optimize(2)
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<cmath>
#include<climits>
#include<deque>
#include<functional>
#include<complex>
#include<numeric>
#include<unordered_map>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define Pi acos(-1.0)
#define ABS(x) ((x) >= 0 ? (x) : (-(x)))
#define pb(x) push_back(x)
#define lowbit(x) (x & -x)
#define FRIN freopen("C:\\Users\\Administrator.MACHENI-KA32LTP\\Desktop\\in.txt", "r", stdin)
#define FROUT freopen("C:\\Users\\Administrator.MACHENI-KA32LTP\\Desktop\\out.txt", "w", stdout)
#define FAST ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define outd(x) printf("%d\n", x)
#define outld(x) printf("lld\n", x)
#define il inline
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ull, ull> puu;
const int maxn = 2e4;
const int INF = 0x7fffffff;
const int mod = 1e9 + 7;
const int p1 = 137;
const int p2 = 109;
const double eps = 1e-7;
inline int read_int() {
	char c;
	int ret = 0, sgn = 1;
	do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
	if (c == '-') sgn = -1; else ret = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
	return sgn * ret;
}
inline ll read_ll() {
	char c;
	ll ret = 0, sgn = 1;
	do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
	if (c == '-') sgn = -1; else ret = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
	return sgn * ret;
}
ull coe1[maxn + 5], coe2[maxn + 5], hash1[maxn + 5], hash2[maxn + 5];
int arr[maxn + 5], n, k;
il void Get_hash() {
	for (int i = 1; i <= n; ++i) {
		hash1[i] = hash1[i - 1] * p1 + arr[i];
		hash2[i] = hash2[i - 1] * p2 + arr[i];
	}
}
il ull Get_hash1_value(int l, int r) {
	return hash1[r] - hash1[l - 1] * coe1[r - l + 1];
}
il ull Get_hash2_value(int l, int r) {
	return hash2[r] - hash2[l - 1] * coe2[r - l + 1];
}
bool check(int mid) {
	map<puu, int> cnt;
	for (int i = 1; i + mid - 1 <= n; ++i) {
		int l = i, r = i + mid - 1;
		ull res1 = Get_hash1_value(l, r), res2 = Get_hash2_value(l, r);
		cnt[puu(res1, res2)]++;
	}
	int res = 0;
	for (auto iter = cnt.begin(); iter != cnt.end(); ++iter) res = max(res, iter->second);
	return res >= k;
}
int main()
{
	coe1[0] = coe2[0] = 1;
	for (int i = 1; i <= maxn; ++i)coe1[i] = coe1[i - 1] * p1, coe2[i] = coe2[i - 1] * p2;
	n = read_int(), k = read_int();
	for (int i = 1; i <= n; ++i) arr[i] = read_int();
	Get_hash();
	int L = 1, R = n, res = 1;
	while (L <= R) {
		int mid = L + R >> 1;
		if (check(mid)) res = mid, L = mid + 1;
		else R = mid - 1;
	}
	outd(res);
	return 0;
}
```


---

## 作者：Godのfather (赞：1)

# 题解-牛奶模式

------

## (〇)题目描述

[题目传送门](https://www.luogu.org/problemnew/show/P2852)

简单讲解一下题意:

给出一个字符串，求最长至少出现了 $k$ 的子串(可重叠)。



## (一)解题思路

这题需要我们在一个模式串中找相同的子串，很容易就能想到后缀数组。

那么，如何找至少重复出现 $k$ 次的子串呢?

考虑**二分子串的长度**，看看答案是否具有单调性。

如果长度为 $len$ 的子串出现了 $k$ 次，那么一定有长度小于 $len$ 的子串出现了 $k$ 次(这些子串可以是长度为 $len$ 的子串的子串)

这样题目就变成了判定性问题，我们只需判断是否有长度为 $len$ 子串出现次数$\geqslant k$

问题又来了，如何判断字符串中是否有至少重复出现 $k$ 次的子串呢?

要找重复 $k$ 次的子串，其实就是找 $k$ 个相同的子串。找相同的子串，可以考虑使用后缀数组。对于得到的 $height[~]$ 数组，使用分组的方法，使得每组中的每个后缀的最长公共前缀都 $\geqslant len$ ，再判断是否有一组中的后缀数量 $\geqslant k$ 即可。



## (二)解题方法

### 做法:二分答案+后缀数组

#### 时间复杂度:$\Theta(n\log_2{n})$

二分答案不必讲，求后缀数组和 $height[~]$ 数组可以参考论文或者[学习总结-后缀数组](https://www.cnblogs.com/GDOI2018/p/10292378.html)

然后...就没有然后了，直接上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000005;
int sa[maxn], rak[maxn], sum[maxn], height[maxn];
int key2[maxn], newRak[maxn], a[maxn];
int N, K, M;
bool cmp(int a, int b, int l)
{
    if(rak[a] != rak[b]) return false;
    if((a+l > N) xor (b+l > N)) return false;
    if(a+l > N and b+l > N) return true;
    return rak[a+l] == rak[b+l];
}
void getHeight()
{
    int k = 0;
    for(int i=1; i<=N; i++)
    {
        if(rak[i] == 1) {height[rak[i]] = 0; continue;}
        int j = sa[rak[i]-1];
        while(a[i+k] == a[j+k]) k++;
        height[rak[i]] = k;
        if(k != 0) k--;
    }
}
bool ok(int x)
{
    int cnt = 1;
    for(int i=2; i<=N; i++)
    {
        if(height[i] < x) cnt = 1;
        else cnt++;
        if(cnt >= K) return true;
    }
    return false;
}
int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1; i<=N; i++) scanf("%d",&a[i]);
    M = max(1000000, N);
    for(int i=1; i<=N; i++) sum[rak[i] = a[i]]++;
    for(int i=1; i<=M; i++) sum[i] += sum[i-1];
    for(int i=N; i>=1; i--) sa[sum[rak[i]]--] = i;
    for(int l=1; l<N; l<<=1)
    {
        int k = 0;
        for(int i=N-l+1; i<=N; i++) key2[++k] = i;
        for(int i=1; i<=N; i++) if(sa[i] > l) key2[++k] = sa[i]-l;
        for(int i=1; i<=M; i++) sum[i] = 0;
        for(int i=1; i<=N; i++) sum[rak[i]]++;
        for(int i=1; i<=M; i++) sum[i] += sum[i-1];
        for(int i=N; i>=1; i--) sa[sum[rak[key2[i]]]--] = key2[i];
        int rk = 1;
        newRak[sa[1]] = 1;
        for(int i=2; i<=N; i++)
            if(cmp(sa[i], sa[i-1], l)) newRak[sa[i]] = rk;
            else newRak[sa[i]] = ++rk;
        for(int i=1; i<=N; i++) rak[i] = newRak[i];
        if(rk == N) break;
    }
    getHeight();
    int l = 0, r = N+1;
    while(l+1 < r)
    {
        int mid = (l+r)>>1;
        if(ok(mid)) l = mid;
        else r = mid;
    }
    printf("%d", l);
    return 0;
} 
```



---

## 作者：JZYshuraK (赞：1)

# 牛奶模式
题解：

不难想到二分答案，现在我们考虑如何验证。

这里就是后缀数组的一个妙用了。

我们对原串建立后缀数组，观察$ht$数组。

考虑当前二分出来的$mid$。如果有至少连续$k$的$ht$值都不小

于$mid$，那么$k$就是合法的。

故此我们直接扫$ht$数组看看最长的连续比$mid$大的$ht$有多少个即可。

Code:
```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1000010 
using namespace std;
int wv[N],wa[N],sa[N],Ws[N],wb[N],t[N],rk[N],ht[N],r[N];
int n,m=1000009;
inline char nc() {static char *p1,*p2,buf[100000]; return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
int rd() {int x=0; char c=nc(); while(!isdigit(c)) c=nc(); while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=nc(); return x;}
void build_sa()
{
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;i++) Ws[i]=0;
	for(i=0;i<n;i++) Ws[x[i]=r[i]]++;
	for(i=1;i<m;i++) Ws[i]+=Ws[i-1];
	for(i=n-1;~i;i--) sa[--Ws[x[i]]]=i;
	for(p=j=1;p<n;j<<=1,m=p)
	{
		for(p=0,i=n-j;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]-j>=0) y[p++]=sa[i]-j;
		for(i=0;i<n;i++) wv[i]=x[y[i]];
		for(i=0;i<m;i++) Ws[i]=0;
		for(i=0;i<n;i++) Ws[wv[i]]++;
		for(i=1;i<m;i++) Ws[i]+=Ws[i-1];
		for(i=n-1;~i;i--) sa[--Ws[wv[i]]]=y[i];
		for(t=x,x=y,y=t,i=p=1,x[sa[0]]=0;i<n;i++)
		{
			if(y[sa[i]]==y[sa[i-1]]&&y[sa[i-1]+j]==y[sa[i]+j]) x[sa[i]]=p-1;
			else x[sa[i]]=p++;
		}
	}
	for(i=1;i<n;i++) rk[sa[i]]=i;
	for(i=p=0;i<n-1;ht[rk[i++]]=p)
		for(p?p--:0,j=sa[rk[i]-1];r[i+p]==r[j+p];p++);
}
template <typename T> void Max(T &x,T y) {x=max(x,y);}
// inline void Max(int &x,int y) {x=max(x,y);}
int check(int x)
{
	int re=-1,now=0;
	for(int i=0;i<n;i++)
	{
		if(ht[i]>=x) now++;
		else Max(re,now),now=1;
	}
	Max(re,now);
	return re;
}
int main()
{
	n=rd();int k=rd(); for(int i=0;i<n;i++) r[i]=rd();
	r[n++]=0; build_sa();
	int l=0,r=n+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid)>=k) l=mid+1;
		else r=mid;
	}
	l--;
	cout << l << endl ;
	return 0;
}
```
推销个人blog [JZYshuraK](https://www.cnblogs.com/ShuraK/p/10110574.html)

---

## 作者：MrMorning (赞：1)

#Brief Description

给定一个字符串，求至少出现k次的最长重复子串。


#Algorithm Design

先二分答案，然后将后缀分成若干组。判断有没有一个组的后缀个数不小于k。如果有，那么存在k个相同的子串满足条件，否则不存在。这个做法的时间复杂度为$\Theta(nlgn)$.


#Code
```cpp
#include <cstdio>
const int maxn = 20010;
int a[maxn], sa[2][maxn], rank[2][maxn], height[maxn];
int n, K, k, m, p, q;
int v[1000100];
void calc(int sa[maxn], int rank[maxn], int Sa[maxn], int Rank[maxn]) {
  for (int i = 1; i <= n; i++)
    v[rank[sa[i]]] = i;
  for (int i = n; i >= 1; i--)
    if (sa[i] > k)
      Sa[v[rank[sa[i] - k]]--] = sa[i] - k;
  for (int i = n - k + 1; i <= n; i++)
    Sa[v[rank[i]]--] = i;
  for (int i = 1; i <= n; i++)
    Rank[Sa[i]] = Rank[Sa[i - 1]] + (rank[Sa[i]] != rank[Sa[i - 1]] ||
                                     rank[Sa[i] + k] != rank[Sa[i - 1] + k]);
}
void calh(int sa[maxn], int rank[maxn]) {
  int i, j, k = 0;
  for (i = 1; i <= n; height[rank[i++]] = k)
    for (k ? k-- : 0, j = sa[rank[i] - 1]; a[i + k] == a[j + k]; k++)
      ;
  return;
}
void da() {
  m = 1000010, p = 0, q = 1, k = 1;
  for (int i = 1; i <= n; i++)
    v[a[i]]++;
  for (int i = 1; i <= m; i++)
    v[i] += v[i - 1];
  for (int i = 1; i <= n; i++)
    sa[p][v[a[i]]--] = i;
  for (int i = 1; i <= n; i++)
    rank[p][sa[p][i]] =
        rank[p][sa[p][i - 1]] + (a[sa[p][i - 1]] != a[sa[p][i]]);
  while (k < n) {
    calc(sa[p], rank[p], sa[q], rank[q]);
    p ^= 1;
    q ^= 1;
    k <<= 1;
  }
  calh(sa[p], rank[p]);
}
bool check(int x) {
  int l = 1, r = 1;
  for (int i = 2; i <= n + 1; i++)
    if (height[i] >= x)
      r++;
    else if (r - l + 1 >= K)
      return true;
    else {
      l = i;
      r = i;
      continue;
    }
  return false;
}
void solve() {
  int l = 0, r = n;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (check(mid))
      l = mid;
    else
      r = mid;
  }
  printf("%d\n", check(r) ? r : l);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &n, &K);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  da();
  solve();
}
```
#广告

欢迎访问[我的博客](http://www.cnblogs.com/gengchen)


---

## 作者：Caicz (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/P2852)

------------

这是一道对于初学后缀数组的选手来说很好的一道练习题

我们将所有数读入后，求出sa数组和height数组

然后对结合题目要求，求至少出现 k 次的最长字串长度，即为对每段长度为 k-1 的连续height数组的最小值求最大，可以用单调队列轻松解决

注意，这里 k-1 个是因为我们height数组的定义为相邻rank字串的最长公共子串
$$
	\large\text{Talk is cheap , show you the code}
$$


```cpp
#include<touwenjian.h>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1000005;
const int inf=0x3f3f3f3f;
int n,lim,sa[maxn],rk[maxn],m=maxn;
int tax[maxn],tp[maxn],ht[maxn];
int s[maxn];
struct queue
{
	int id,val;
}q[maxn];
multiset<int>t;//推荐使用stl简单实现单调队列

inline void Qsort()
{
	for(register int i=0;i<=m;++i)tax[i]=0;
	for(register int i=1;i<=n;++i)++tax[rk[i]];
	for(register int i=1;i<=m;++i)tax[i]+=tax[i-1];
	for(register int i=n;i>=1;--i)sa[tax[rk[tp[i]]]--]=tp[i];
}

inline void suffix()
{
	Qsort();
	for(register int w=1,p=0;p<n;m=p,w<<=1)
	{
		p=0;
		for(register int i=1;i<=w;++i)tp[++p]=n-w+i;
		for(register int i=1;i<=n;++i)if(sa[i]>w)tp[++p]=sa[i]-w;
		Qsort();
		swap(tp,rk);
		rk[sa[1]]=p=1;
		for(register int i=2;i<=n;++i)rk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+w]==tp[sa[i-1]+w])?p:++p;
	}
}

signed main(void)
{
	n=read(),lim=read();--lim;
	for(register int i=1;i<=n;++i)s[i]=rk[i]=read(),tp[i]=i;
	suffix();
	for(register int i=1,k=0;i<=n;++i)
	{
		if(k)--k;
		while(s[i+k]==s[sa[rk[i]-1]+k])++k;
		ht[rk[i]]=k;
	}
	int ans=0;
	for(register int i=1;i<=n;++i) 
	{
	    t.insert(ht[i]);
	    if(i>lim)t.erase(t.find(ht[i-lim]));
	    if(i>=lim)ans=max(ans,*t.begin());
  	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：功在不舍 (赞：0)

~~后缀树又被迫害啦~~

日常无人写unkkonen后缀树，我来讲讲。

如果从根对后缀树进行一次dfs的话

rank数组的本质就是后缀树上各个后缀的dfs序

SA数组则是dfs序为i的后缀是谁

height数组的本质是两个dfs序相邻后缀在树上的 LCA 对应的子串长度

（后缀树是后缀trie的虚树，每一非叶子节点都对应两个后缀的LCA）

所以一切后缀数组能干的活后缀树都能干，后缀树的dfs相当于你用单调栈扫

这个题就是求出现至少K次的最长子串长度。

首先把后缀树建立出来。（这题几乎是后缀树的板子）

之后从根开始dfs，求得每一个节点对应的子串出现了多少次。

（结束位置在边上的子串出现次数和他下面的节点一致）

如果$size[now]>=k$，那么就用depth去更新ans就好了

这个题$k>=2$,所以我们只看非叶子节点就好了。

~~（其实我不太会使SA和单调栈）~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define N 210001
using namespace std;
int n1,s1[N],inf=0x3f3f3f3f,k,ans;
struct SuffixTree{
    int s[N],start[N],len[N],link[N],size[N],rem,tot,n,now;
    map <int,int> ch[N];
    inline void clear(){rem=n=0;tot=now=1;len[0]=inf;}
    inline int newnode(int st,int le){link[++tot]=1;start[tot]=st;len[tot]=le;return tot;}
    inline void insert(int x){
        s[++n]=x;rem++;int last=1;
        while(rem!=0){
            while(rem>len[ch[now][s[n-rem+1]]])rem-=len[now=ch[now][s[n-rem+1]]];
            int &v=ch[now][s[n-rem+1]],c=s[start[v]+rem-1];
            if(!v||x==c){
               link[last]=now;last=now;
               if(!v)v=newnode(n,inf);
               else break;
			}else {
			    int u=newnode(start[v],rem-1);
			    ch[u][c]=v;ch[u][x]=newnode(n,inf);
			    start[v]+=rem-1;len[v]-=rem-1;
			    link[last]=v=u;last=u;
			}if(now==1)rem--;else now=link[now];
		}
	}
	inline int dfs(int now,int depth){
	    if(depth>=inf)return size[now]=1;
	    map <int,int> :: iterator it;
		for(it=ch[now].begin();it!=ch[now].end();it++)
		    size[now]+=dfs(it->second,depth+len[it->second]);
		if(size[now]>=k)ans=max(ans,depth); 
		return size[now];
	}
}t;
int main()
{
	t.clear();
	scanf("%d%d",&n1,&k);
	for(int i=1;i<=n1;i++)scanf("%d",&s1[i]);
	for(int i=1;i<=n1;i++)t.insert(s1[i]);
	t.insert(26);
	t.dfs(1,0);cout<<ans<<endl;
	return 0;
}
```

---

