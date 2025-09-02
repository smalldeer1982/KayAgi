# [ONTAK2015] Tasowanie

## 题目描述

给定两个数字串 $A$ 和 $B$，通过将 $A$ 和 $B$ 进行二路归并得到一个新的数字串 $T$，请找到字典序最小的 $T$。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n, m \leq 2 \times 10^5$，组成 $A, B$ 的每个数字为不超过 $10^3$ 的正整数。

- 2023.9.10 添加两组 hack 数据。

## 样例 #1

### 输入

```
6
1 2 3 1 2 4
7
1 2 2 1 3 4 3```

### 输出

```
1 1 2 2 1 2 3 1 2 3 4 3 4```

# 题解

## 作者：_XHY20180718_ (赞：6)

## 前言：

此道题目中大部分后缀数组和贪心做法都是有问题的，这里提供一种正确的贪心做法，感觉挺好想的，代码也不长，但是细节较多。

Hack 数据见：[link](https://www.luogu.com.cn/discuss/679722)。

## 题解：

首先我们确定一个很显然的结论：当前放置的字符一定要最小。

我们从 $a$ 和 $b$ 串的字符一起扫一遍来确定答案：

若当前 $a$ 和 $b$ 串上的字符若不同，则选择较小的那一个。

问题来了，相同的时候怎么办？

其次，我们~~根据样例~~手玩一下可一发现：如果当前字符相同，我们需要想办法让后面的字典序尽量小。

显然，我们可以确定另一个结论：下一个不同的字符如果比当前字符小，那么就要尽快把这个字符放好，所以**当前放置的字符仅对下一个不同的字符有影响**。

所以我们设两个 $nxt$ 数组，分别表示 $a$ 和 $b$ 串上每个字符下一个最近的不同的字符的位置。

接下来是重点：

1. 如果 $a[nxta_i]>a[i]$ 且 $b[nxtb_i]>b[i]$，则说明你前面的字符怎么乱放你后面都不会有影响，反正要先把前面的全部放完，然后再放后面那个较小的 $s[nxt_i]$（实际上还是要把距离远的先放完，）。

2. 如果 $a[nxta_i]<a[i]$ 且 $b[nxtb_i]<b[i]$，那么我们需要比较下一个较小的字符到当前字符的距离，然后把较近的那一个先放了，这样才能保证字典序更小，如果距离相同，则比较 $a[nxta_i]$ 和 $b[nxtb_i]$ 的大小，哪个小先放哪个。

3. 如果大小关系不一样，优先放那个 $s[nxt_i]$ 值更小的即可。

问题又来了，当 $a[nxta_i]$ 和 $b[nxtb_i]$ 也相同怎么办？

这个时候就需要用到一点指针的思想了，当以上距离、数值均相同的时候，我们直接改变我们的 $nxt$ 数组，直到字符串结尾或是 $nxt$ 信息有所不同。

但是如果每一次都需要暴力跳，那么复杂度可能会被卡成 $O(n^2)$。

这个时候我们利用并查集的思想：路径压缩。也就是每次跳 $nxt$ 的时候顺便帮父亲也跳一下 $nxt$。

在这个操作之后有会出现问题，在上述的重点 $1$ 当中，我们要先把距离下一个不同的远的字符先放完，然后再去放更近的，这样才能保证更小，比如：
```
3 1 1 4
3 1 2 4
```
如果先放第二行 `3 1`，那么就会导致第一行放出 `3 1 1` 放在后面，明显不如 `3 1 1 3 1`。

这样复杂度至少不会高于 $O(n\log n)$，并且常数很小，$n$ 在 $
10^7$ 之内都能跑得飞快。

## 代码：
```cpp
#include<bits/stdc++.h>
#define na nxta[ida]
#define nb nxtb[idb]
using namespace std;
const int N=2e5+5;
int a[N],b[N];
int ida,idb,n,m;
int nxta[N],nxtb[N];
signed main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
// 	ios::sync_with_stdio(0);
// 	cin.tie(0),cout.tie(0);
	cin>>n;for(int i=1; i<=n; ++i)cin>>a[i];
	cin>>m;for(int i=1; i<=m; ++i)cin>>b[i];
	ida=idb=1,a[n+1]=N+1,b[m+1]=N+1;
	for(int i=n; i>=1; --i)
		if(a[i]==a[i+1])nxta[i]=nxta[i+1];
		else nxta[i]=i+1;
	for(int i=m; i>=1; --i)
		if(b[i]==b[i+1])nxtb[i]=nxtb[i+1];
		else nxtb[i]=i+1;
	while(ida<=n&&idb<=m){
		if(a[ida]<b[idb])cout<<a[ida++]<<' ';
		else if(a[ida]>b[idb])cout<<b[idb++]<<' ';
		else{
		    int lna=ida,lnb=idb;
			while(na-ida==nb-idb&&a[na]==b[nb]&&na<=n&nb<=m)
				lna=na,na=nxta[na],lnb=nb,nb=nxtb[nb];
			if(a[na]<a[lna]&&b[nb]<b[lnb]){
				if(na-ida<nb-idb)cout<<a[ida++]<<' ';
				else if(na-ida>nb-idb)cout<<b[idb++]<<' ';
				else{
					if(a[na]<b[nb])cout<<a[ida++]<<' ';
					else if(a[na]>b[nb])cout<<b[idb++]<<' ';
					else cout<<a[ida++]<<' ';
				}
			}else{
			    if(a[na]>a[lna]&&b[nb]>b[lnb]){
			        if(na-ida>nb-idb)cout<<a[ida++]<<' ';
    				else if(na-ida<nb-idb)cout<<b[idb++]<<' ';
    				else{
    					if(a[na]<b[nb])cout<<a[ida++]<<' ';
    					else if(a[na]>b[nb])cout<<b[idb++]<<' ';
    					else cout<<a[ida++]<<' ';
    				}
			    }else {
    				if(a[na]<b[nb])cout<<a[ida++]<<' ';
    				else if(a[na]>b[nb])cout<<b[idb++]<<' ';
    				else cout<<a[ida++]<<' ';
			    }
			}
		}
	}
	for(;ida<=n;++ida)cout<<a[ida]<<' ';
	for(;idb<=m;++idb)cout<<b[idb]<<' ';
	return 0;
}
```

---

## 作者：huhengrui2013 (赞：3)

~~jiyu大佬曾说：这是一道归并+二分+哈希的好题。~~

### 前置知识：[哈希](https://oi-wiki.org/string/hash/)

### 思路
合并字典序可以用归并的思想，但正常归并一定会挂。

为什么归并会出错呢？  

因为在正常归并排序中，$a$、$b$有序，任选一个不会影响合并的答案。但在这题不同，$a_i = b_j$ 时不能随便放。

在字典序中，当两个元素相等时，就一定要比较后面元素，但最坏时，暴力会卡到 $O((n+m)^2)$（全相同）。

所以我们思考字符串比较可以靠哈希优化到 $O(1)$ 的时间复杂度。

还可以用二分，二分的作用是快速比较两个子数组的字典序，以优化合并过程的效率（避免逐字符比较）（为什么能用二分此处不推了）。

### 哈希快速比较模板

```cpp
void build(){
    pw[0]=1;
    for(int i=1;i<=n+m+2;i++){
        hs[i]=(hs[i-1]*base+a[i])%mod; //哈希数组
        pw[i]=(pw[i-1]*base)%mod;
    }
}
int get(int l,int r){
    if(l>r) return 0;//防止越界
    return ((hs[r]-hs[l-1]*pw[r-l+1])%mod+mod)%mod;
}
```

### AC Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10;
int mod=1e9+7;
int base=13331;
int a[N],b[N],n,m;
int pw[N],hs[N];
void build(){//哈希
    pw[0]=1;
    for(int i=1;i<=n+m+2;i++){
        hs[i]=(hs[i-1]*base+a[i])%mod; 
        pw[i]=(pw[i-1]*base)%mod;
    }
}
int get(int l,int r){//查询
    if(l>r) return 0;
    return ((hs[r]-hs[l-1]*pw[r-l+1])%mod+mod)%mod;
}
bool erfen(int i,int j){//二分
    int l=0,r=min(n+m+2-i,n+m+2-j);//r的边界处理，不然会越界
    int lcp;
    while(l<=r){
        int mid=(l+r)/2;
        if(get(i,i+mid-1)==get(j,j+mid-1)){
            lcp=mid;
            l=mid+1;
        }else r=mid-1;
    }
    if(i+lcp>n+m+2) return 1;//i后缀更短
    if(j+lcp>n+m+2) return 0;//j后缀更短
    return a[i+lcp]<a[j+lcp];//比较LCP后的第一个字符
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    a[n+1]=1e9+1;//分界处理
    cin>>m;
    for(int i=1;i<=m;i++) cin>>a[n+i+1];
    a[n+m+2]=1e9+1;//分界处理
    build();//用同一个哈希数组
    int i=1,j=n+2;
    while(i<=n||j<=n+m+1){//合并（直接输出）
        if(j>n+m+1) cout<<a[i++]<<" ";
        else if(i>n) cout<<a[j++]<<" ";
        else{
            if(erfen(i,j)){
                cout<<a[i++]<<" ";
            }else cout<<a[j++]<<" ";
        }
    }
}
```
~~（码风较丑，不喜勿喷）~~

时间复杂度：$O((n+m) \times \log(\max(n,m)))$。

---

## 作者：yukimianyan (赞：3)

看到（目前）AC 提交都是后缀数组，我来整个二分 + hash 的做法。

题目想让我们做归并排序中的并，字典序最小。但序列不一定是有序的，不能直接并。比如这组数据：
```cpp
4
1 6 6 1
4
1 6 6 5
```
直接并就会出现 `1 1 6 6 5 6 6 1`（如果不是这样，试试 $a,b$ 反过来），但还有更小的 `1 1 6 6 1 6 6 5`。

为什么会这样？看代码：
```cpp
while(i<=n&&j<=m){
    if(a[i]<b[j]) t[cnt++]=a[i++];
    else t[cnt++]=b[j++];
}
```
我们并没有判断 $a_i=b_j$ 的情况，因为在正常归并排序中，$a,b$ 有序，不会影响合并的答案。但在这题不同，$a_i=b_j$ 时不能随便放。

那 $a_i=b_j$ 时应该放哪个呢？要字典序最小，可以比较 $a_{i+1}$ 与 $b_{j+1}$，优先放小的进去，比如：
```cpp
2
1 4
2
1 5
```
我们会优先放 `1 4` 而不是 `1 5`，最终输出为 `1 1 4 5`。

但比较 $a_{i+1}$ 和 $b_{j+1}$ 还有一个问题：它们也相同怎么办？继续比较？如果继续比较复杂度就会变成 $O((n+m)^2)$（全相同），这不好。

我们可以二分相同的部分的长度，因为如果 $a_{[i,i+k-1]}=b_{[j,j+k-1]}$，那么 $\forall l<k$，$a_{[i,i+l-1]}=b_{[j,j+l-1]}$；如果 $a_{[i,i+k-1]}\ne b_{[j,j+k-1]}$，那么 $\forall l>k$，$a_{[i,i+l-1]}\ne b_{[j,j+l-1]}$。存在单调性，可以二分。

为了快速比较，用 hash 预处理，$O(1)$ 求出字串 hash 值。具体做法：设 $sum_i$ 为 $a_{[1,i]}$ 的 hash 值，显然 $sum_i=(Bsum_{i-1}+a_i)\bmod P$，那么 $a_{[l,r]}=sum_r-B^{r-l+1}sum_{l-1}$（类似于前缀和）。这题不怎么卡 hash，$B,P$ 随便选都行。

给个代码：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
template<int N,int B=233,int P=(int)1e9+7> struct hasher{
    LL h[N+10],b[N+10];
    hasher(){for(int i=b[h[0]=0]=1ll;i<=N;i++) b[i]=1ll*b[i-1]*B%P;}
    void build(int a[],int n=N){for(int i=1;i<=n;i++) h[i]=(1ll*h[i-1]*B+1ll*a[i])%P;}
    int operator()(int l,int r){return l<=r?(h[r]-h[l-1]*b[r-l+1]%P+P)%P:0;}
};
int n[2],a[2][200010],nxt[2][200010],t[500010];
hasher<200010,1145,(int)1e9+7> h[2];
int binary(int L,int R,int i[2]){
    int ans=L-1;
    while(L<=R){
        int mid=(L+R)>>1;
        if(h[0](i[0],i[0]+mid-1)==h[1](i[1],i[1]+mid-1)) ans=mid,L=mid+1;
        else R=mid-1;
    }
    return ans;
}
void merge(){
    int cnt=1,i[2]={1,1};
    //相等，后面小
    while(i[0]<=n[0]&&i[1]<=n[1]){
        int len=binary(1,min(n[0]-i[0],n[1]-i[1])+1,i);
        int k=a[0][i[0]+len]>a[1][i[1]+len];
        t[cnt++]=a[k][i[k]++];
    }
    while(i[0]<=n[0]) t[cnt++]=a[0][i[0]++];
    while(i[1]<=n[1]) t[cnt++]=a[1][i[1]++];
}
int main(){
    memset(a,0x3f,sizeof a);
    for(int k=0;k<=1;k++){
        scanf("%d",&n[k]);
        for(int i=1;i<=n[k];i++) scanf("%d",&a[k][i]);
        h[k].build(a[k],n[k]);
    }
    merge();
    for(int i=1;i<=n[0]+n[1];i++) printf("%d%c",t[i]," \n"[i==n[0]+n[1]]);
    return 0;
}
```
时间复杂度：$O((n+m)\log(n+m))$。

---

## 作者：Augen_stern (赞：2)

update：修改了一些细节，以通过 hack。

# Part 1 分析求解：


来一篇 SA 后缀数组的题解；

相信读完题后大家都知道原题要让我们做归并排序中的并，字典序最小；

所以这时候我们可以用上 $Rk$ 数组，这样将 $A$ 串和 $B$ 串看作一个类似于队列的东西，左边端点为队首，每一次操作比较队首的 $Rk$ 值就行了。

**值得注意的是两串之间和末尾都要加上一个相同的特殊符号，以至于不会出现空字符的情况。**

# Part 2 CODE：

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<math.h>
#include<algorithm>
#include<queue>
#define INF 0x7fffffff/2
using namespace std;
string s;
int T,n,p=0,q=1,k=1,kk,mx; 
int n1,n2,now1,now2;
int a[1001505],rk[2][1001505],vst[1000005],sa[2][1001505];
void MUL(int *rk,int *sa,int *RK,int *SA) {
	for(int i=1;i<=n;i++) vst[rk[sa[i]]]=i;
	for(int i=n;i>=1;i--) {
		if(sa[i]>k) SA[vst[rk[sa[i]-k]]--]=sa[i]-k;
	}
	for(int i=n-k+1;i<=n;i++) SA[vst[rk[i]]--]=i;
	for(int i=1;i<=n;i++) RK[SA[i]]=RK[SA[i-1]]+(rk[SA[i]]!=rk[SA[i-1]]||rk[SA[i]+k]!=rk[SA[i-1]+k]);
}
void PRE() {
	for(int i=1;i<=n;i++) vst[a[i]]++;
	for(int i=1;i<=10000;i++) vst[i]+=vst[i-1];
	for(int i=1;i<=n;i++) sa[p][vst[a[i]]--]=i;
	for(int i=1;i<=n;i++) rk[p][sa[p][i]]=rk[p][sa[p][i-1]]+(a[sa[p][i]]!=a[sa[p][i-1]]);
	for(k=1;k<n;k<<=1,swap(p,q)) MUL(rk[p],sa[p],rk[q],sa[q]);
} // 不需要求 height 数组，以上板子。
signed main() {
	scanf("%d",&n1);
	for(int i=1;i<=n1;i++) scanf("%d",&a[i]);
	scanf("%d",&n2);
	for(int i=1;i<=n2;i++) scanf("%d",&a[n1+i+1]); // 将两串拼接起来
	a[n1+1]=3001; // 一个类似于特殊字符的操作，赋值随意但一定要大于两串中的元素
	a[n1+n2+2]=3001; // 最后也要加特殊字符
	n=n1+n2+2;
	PRE(); // SA 后缀数组板子
	now1=1,now2=n1+2; // 两串左端点
	for(int i=1;i<n;i++) {
		if(rk[p][now1]<rk[p][now2]) printf("%d ",a[now1]),now1++;
		else printf("%d ",a[now2]),now2++; // 比较 Rk 数组的值
		if(now1==n1+1) {
			for(int j=now2;j<n;j++) printf("%d ",a[j]);
			break;
		}
		if(now2==n+1) {
			for(int j=now1;j<=n1;j++) printf("%d ",a[j]);
			break;
		} // 当一个串用尽时输出剩下的另一个串
	}
	return 0;
}
```


---

## 作者：朝夕晨曦_L (赞：1)

[P8023 [ONTAK2015] Tasowanie ](https://www.luogu.com.cn/problem/P8023)

题目要求求出在字典序最小的新序列，考虑如何保证字典序最小。

首先当前局面，我们肯定会选择两个序列中字典序较小的那个元素放进新序列。

但是万一两个序列队首元素字典序相同呢？那么我们就要有预知能力。

而后缀排序就赋予我们预知能力，我们把其中一个序列看做主序列，在接下来有来自次序列的元素插入，打乱了主序列，这会不会影响答案正确性？当前选择排名较小的会不会错误？

显然不会，因为这因为排名小实际上是预知了接下来谁会更早的解救出字典序小的元素，当前局面选谁都一样，就要考虑选了谁，能快速获得字典序小的元素，这样就完美解决了这个问题。

见代码：


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 400050
char buf[1<<21],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
long long read(){
	long long res=0,f=1;char ch;
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar())
		if(ch=='-') f=-1;
	for(;ch>='0'&&ch<='19';ch=getchar())
		res=(res<<3)+(res<<1)+ch-'0';
	return res*f;
}
void wt(int x){
	if(x<0) return putchar('-'),wt(-x);
	if(x>=10) wt(x/10);
	putchar(x%10+'0');
	return ;
}
int wa[N],wb[N],s[N],la,lb;
int a[N],b[N];
int n, m = 1001, l, t, p;
int y[N], x[N], c[N], sa[N], rk[N], height[N];
void get_sa() {
	for(int i = 1; i <= n; ++i) ++c[x[i] = s[i]];
	for(int i = 2; i <= m; ++i) c[i] += c[i - 1];
	for(int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
	for(int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for(int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for(int i = 1; i <= n; ++i)
			if(sa[i] > k) y[++num] = sa[i] - k;
		for(int i = 1; i <= m; ++i) c[i] = 0;
		for(int i = 1; i <= n; ++i) ++c[x[i]];
		for(int i = 2; i <= m; ++i) c[i] += c[i - 1];
		for(int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		swap(x, y);
		x[sa[1]] = 1;
		num = 1;
		for(int i = 2; i <= n; ++i) {
			if(y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
				x[sa[i]] = num;
			else
				x[sa[i]] = ++num;
		}
		if(num == n) break;
		m = num;
	}
}
int main(){
    la=read();
    int i; 
    for(i=1;i<=la;i++){
        a[i]=read();
        s[++n]=a[i];
    }
    lb=read();
    s[++n]=1001;//有一个用完，只能用另外一个，所以只好给个极大值
    for(i=1;i<=lb;i++){
        b[i]=read();
        s[++n]=b[i];
    }
    s[++n]=1001;//hack数据的优化
    get_sa();
	for(int i=1;i<=n;i++){
		rk[sa[i]]=i;
	}
    int j=1,k=la+2;
    while(j<=la&&k<=n-1){
        if(rk[j]<rk[k]) wt(s[j++]),printf(" ");
        else wt(s[k++]),printf(" ");
    }
    while(j<=la) wt(s[j++]),printf(" ");
    while(k<=n-1) wt(s[k++]),printf(" ");
    return 0;
}
```

---

## 作者：Coffee_zzz (赞：0)

由于题目要求 $T$ 的字典序最小，容易想到最朴素的贪心：同时从前往后枚举 $A$ 和 $B$ 的每个元素，设当前枚举到了 $A_i$ 和 $B_j$：

- 若 $A_i \lt B_j$，则把 $A_i$ 加入到 $T$ 的末尾，并把 $i$ 增加 $1$；
- 若 $A_i \gt B_j$，则把 $B_j$ 加入到 $T$ 的末尾，并把 $j$ 增加 $1$。

但是当 $A_i = B_j$ 的时候，选择 $A_i$ 或 $B_j$ 可能会有不同的影响。这时，我们可以继续考虑贪心。

我们可以通过二分和 Hash 函数，找到最大的非负整数 $l$，使得 $A[i,i+l-1]=B[j,j+l-1]$，然后比较 $A_{i+l}$ 和 $B_{j+l}$。  
如果 $A_{i+l} \lt B_{j+l}$，则选择 $A_i$ 一定更优，否则选择 $B_j$ 一定更优。注意，如果 $i+l=n+1$，则选择 $B_j$ 更优；同理，如果 $j+l=m+1$，则选择 $A_i$ 更优。我们可以通过在 $A$ 和 $B$ 的末尾添加一个极大值的方式来更方便地处理。

时间复杂度 $\mathcal O(n \log n)$。

参考代码：<https://www.luogu.com/paste/71alnyun>。

---

## 作者：Engulf (赞：0)

考虑贪心，为了让 $T$ 的字典序最小，假设现在 $a$ 与 $b$ 开头的数字分别是 $x$ 与 $y$，若 $x \neq y$ 显然放小的，需要考虑的就是 $x=y$ 的情况。

因为 $x=y$，字典序不可能再小了，所以只能寄希望于新的数上，所以我们得让新的能选的数尽量小。做法就是跳过相等的数，然后哪个小就优先选哪边。

注意一个细节，如果当前 $x$ 开头的这段后缀是 $y$ 这段后缀的其中一个前缀，即没有不相等的数的情况，此时 **优先取 $y$**，因为 $y$ 后面还存在可能更小的数，如果先取 $x$，取完后只剩下 $y$，字典序不一定最小。

实现上使用二分加哈希即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

const int base = 233;

int n, m;

int a[N], b[N];

ull ha[N], hb[N];
ull pw[N];

ull geta(int l, int r) {return ha[r] - ha[l - 1] * pw[r - l + 1];}
ull getb(int l, int r) {return hb[r] - hb[l - 1] * pw[r - l + 1];}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> b[i];
    if (n > m) swap(n, m), swap(a, b);
    pw[0] = 1;
    for (int i = 1; i <= m; i++) pw[i] = pw[i - 1] * base;
    for (int i = 1; i <= n; i++) ha[i] = ha[i - 1] * base + a[i];
    for (int i = 1; i <= m; i++) hb[i] = hb[i - 1] * base + b[i];
    int x = 1, y = 1;
    for (; x <= n && y <= m; cout << " ") {
        if (a[x] != b[y]) {
            if (a[x] < b[y]) cout << a[x++];
            else cout << b[y++];
        } else {
            int l = 0, r = min(n - x + 1, m - y + 1), res = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (geta(x, x + mid - 1) == getb(y, y + mid - 1)) res = mid, l = mid + 1;
                else r = mid - 1;
            }
            assert(res != -1);
            if (x + res - 1 == n) cout << b[y++];
            else if (y + res - 1 == m) cout << a[x++];
            else {
                if (a[x + res] < b[y + res]) cout << a[x++];
                else cout << b[y++];
            }
        }
    }
    while (x <= n) cout << a[x++] << " ";
    while (y <= m) cout << b[y++] << " ";
    return 0;
}
```

---

