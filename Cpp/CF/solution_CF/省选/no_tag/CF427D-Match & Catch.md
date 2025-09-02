# Match & Catch

## 题目描述

Police headquarter is monitoring signal on different frequency levels. They have got two suspiciously encoded strings $ s_{1} $ and $ s_{2} $ from two different frequencies as signals. They are suspecting that these two strings are from two different criminals and they are planning to do some evil task.

Now they are trying to find a common substring of minimum length between these two strings. The substring must occur only once in the first string, and also it must occur only once in the second string.

Given two strings $ s_{1} $ and $ s_{2} $ consist of lowercase Latin letters, find the smallest (by length) common substring $ p $ of both $ s_{1} $ and $ s_{2} $ , where $ p $ is a unique substring in $ s_{1} $ and also in $ s_{2} $ . See notes for formal definition of substring and uniqueness.

## 说明/提示

Imagine we have string $ a=a_{1}a_{2}a_{3}...a_{|a|} $ , where $ |a| $ is the length of string $ a $ , and $ a_{i} $ is the $ i^{th} $ letter of the string.

We will call string $ a_{l}a_{l+1}a_{l+2}...a_{r} $ $ (1<=l<=r<=|a|) $ the substring $ [l,r] $ of the string $ a $ .

The substring $ [l,r] $ is unique in $ a $ if and only if there is no pair $ l_{1},r_{1} $ such that $ l_{1}≠l $ and the substring $ [l_{1},r_{1}] $ is equal to the substring $ [l,r] $ in $ a $ .

## 样例 #1

### 输入

```
apple
pepperoni
```

### 输出

```
2
```

## 样例 #2

### 输入

```
lover
driver
```

### 输出

```
1
```

## 样例 #3

### 输入

```
bidhan
roy
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
testsetses
teeptes
```

### 输出

```
3
```

# 题解

## 作者：oisdoaiu (赞：11)

提供一种不用广义$SAM$的做法

对$s$建$SAM$，然后用$t$去跑匹配，对于当前$i$，匹配到的节点为$cur$，匹配长度为$nowlen$
- 若$cur$不是$SAM$的$parent$树叶子节点，则continue
- 否则说明$t$中$len\in[len(fa(cur))+1,nowlen]$，$r=i$的这些子串都满足**同时在两个串中出现，且在$s$中仅出现一次**

然后对于$t$再建$SAM$，对于当前$i$，$SAM$树上对应节点为$pos$

- 若$pos$不是$SAM$的$parent$树叶子节点，则continue
- 否则说明$t$中$len\in[len(fa(pos))+1,len(pos)],r=i$的这些子串都满足**在$t$中仅出现一次**

然后对于每个$r$都可以求出对应的满足条件的$len$的区间（即上面两个区间的交），然后取最小$len$更新答案

```cpp
#include<bits/stdc++.h>
using namespace std;

template<typename T>
inline void Read(T &n){
    char ch; bool flag=false;
    while(!isdigit(ch=getchar()))if(ch=='-')flag=true;
    for(n=ch^48;isdigit(ch=getchar());n=(n<<1)+(n<<3)+(ch^48));
    if(flag)n=-n;
}

const int MAXN = 5005;

struct SAM{
    struct node{
        int son[26], fa, len;
        #define son(x,opt) t[x].son[opt]
        #define fa(x) t[x].fa
        #define len(x) t[x].len
    }t[MAXN<<1];
    int node_cnt=1, prv=1;

    inline int insert(int v){
        int x = ++node_cnt; len(x) = len(prv)+1;
        while(prv and !son(prv,v)) son(prv,v) = x, prv = fa(prv);
        if(!prv) fa(x) = 1;
        else{
            int p = son(prv,v);
            if(len(p) == len(prv)+1) fa(x) = p;
            else{
                int new_p = ++node_cnt; len(new_p) = len(prv)+1;
                fa(new_p) = fa(p); fa(p) = fa(x) = new_p;
                copy(t[p].son,t[p].son+26,t[new_p].son);
                while(prv and son(prv,v)==p) son(prv,v) = new_p, prv = fa(prv);
            }
        }
        return prv=x;
    }

    char mk[MAXN<<1];
    inline void Unique(){for(register int i=1; i<=node_cnt; i++) mk[fa(i)] = true;}
}S,T;

char a[MAXN];
int pos[MAXN];

int main(){
    scanf("%s",a+1); int n = strlen(a+1);
    for(register int i=1; i<=n; i++) S.insert(a[i]-'a'); S.Unique();
    scanf("%s",a+1); n = strlen(a+1);
    for(register int i=1; i<=n; i++) pos[i] = T.insert(a[i]-'a'); T.Unique();
    int ans = INT_MAX;
    for(register int i=1, cur=1, len=0; i<=n; i++){
        while(cur and !S.son(cur,a[i]-'a')) cur = S.fa(cur), len = S.len(cur);
        if(!cur) cur = 1, len = 0;
        else{
            cur = S.son(cur,a[i]-'a'), len++;
            if(S.mk[cur] or T.mk[pos[i]]) continue;
            if(len <= T.len(T.fa(pos[i]))) continue;
            if(T.len(pos[i]) <= S.len(S.fa(cur))) continue;
            ans = min(ans,max(S.len(S.fa(cur))+1,T.len(T.fa(pos[i]))+1));
        }
    }
    cout<<(ans==INT_MAX?-1:ans)<<endl;
    return 0;
}
```

---

## 作者：zombie462 (赞：7)

来一篇简单易懂的 hash 表的题解。

从小到大枚举字符串长度 $l$，再依次将两个字符串中长度为 $l$ 的字符串丢进 hash 表，如果都丢完了发现存在一个 hash 值恰好被两个字符串使用了一次，那么 $l$ 就是答案。

时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define uLL unsigned long long
const int mod=12227;
const int N=10010;
struct HashMap{ //hash 表
	int eb[N],ec[mod],tot[N][2],etot;
	uLL ea[N];
	void init(){
		etot=0;memset(ec,0,sizeof(ec));
	}
	bool insert(uLL hashVal,bool tp){ //插入，tp 表示这是哪个字符串的贡献
		int x=hashVal%mod;
		for (int i=ec[x];i;i=eb[i]){ //寻找已有的 hash 值里有没有要插入的那个
			if (hashVal==ea[i]){
				tot[i][tp]++; //如果有就原地插入
				return 1;
			}
		}
		etot++; //如果没有就新建
		ea[etot]=hashVal;eb[etot]=ec[x];ec[x]=etot;
		tot[etot][tp]=1;tot[etot][tp^1]=0;
		return 0;
	}
	bool check(){
		for (int i=1;i<=etot;++i){ //枚举每一个 hash 值，如果恰好两边都用了一次，就合法
			if (tot[i][0]==tot[i][1] && tot[i][0]==1) return 1;
		}
		return 0;
	}
}hashTable;
char S[N],T[N];
const int basis=13331;
uLL A[N],B[N],P[N];
//以下两个函数求子串的 hash 值
uLL getHashA(int l,int r){
	return A[r]-A[l-1]*P[r-l+1];
}
uLL getHashB(int l,int r){
	return B[r]-B[l-1]*P[r-l+1];
}
int read(){
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0' || ch>'9'){
		if (ch=='-') f=-f;
		ch=getchar();
	}
	while (ch>='0' && ch<='9'){
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
signed main(){
	scanf("%s%s",S,T);
	int n=strlen(S),m=strlen(T);
    //以下三行预处理 hash 值
	P[0]=1;for (int i=1;i<=N-1;++i) P[i]=P[i-1]*basis;
	A[0]=0;for (int i=1;i<=n;++i) A[i]=A[i-1]*basis+S[i-1];
	B[0]=0;for (int i=1;i<=m;++i) B[i]=B[i-1]*basis+T[i-1];
	bool flag=0;
	for (int i=1;i<=min(n,m);++i){ //枚举长度
		hashTable.init();
		for (int j=i;j<=n;++j) hashTable.insert(getHashA(j-i+1,j),0); //将 S 长度为 i 的所有子串丢进 hash 表
		for (int j=i;j<=m;++j) hashTable.insert(getHashB(j-i+1,j),1); //同理
		if (hashTable.check()){
			printf("%d\n",i);flag=1;break; //找到了就结束
		}
	}
	if (!flag) puts("-1");
	return 0;
}
```

---

## 作者：2018LZY (赞：6)

题意:
>在两个串中各出现一次的最短公共子串.

# 方法1:$SAM$
~~简直是裸题.~~

其实用SAM的做法可以不用基数排序,直接跳后缀链接遍历所有的后缀就行了.

定义$f[x],g[x]$分别表示$x$在$A,B$的出现次数.

$ans=min(len[x]) ~~if(f[x]=g[x]=1)$

重点是要加一个小剪枝:
>while(x&&cnt[x]<=1) cnt[x]++,x=tr[x].fa;

$cnt[x]>1$直接跳过就行啦,因为上面全部被贡献过了,肯定也>1.

这里虽然是两个串,但是并不用按照广义后缀自动机那样打,因为这样仅仅是多了几个空节点而已.


代码很短哦~:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e4+10;

int n,last=1,tot=1,f[N],g[N],ans=N; char s[N];
struct node{int fa,len,v[26];}tr[N];
void add(int c,int *cnt) {
	int p=last,x=last=++tot; tr[x].len=tr[p].len+1;
	for(	;p&&tr[p].v[c]==0;p=tr[p].fa) tr[p].v[c]=x;
	if(!p)  tr[x].fa=1;
	else {
		int q=tr[p].v[c],y;
		if(tr[p].len+1==tr[q].len) tr[x].fa=q;
		else {
			tr[y=++tot]=tr[q]; f[y]=f[q]; g[y]=g[q];
			tr[y].len=tr[p].len+1;
			tr[q].fa=tr[x].fa=y;
			for(	;p&&tr[p].v[c]==q;p=tr[p].fa) tr[p].v[c]=y;
		}
	}
	x=last;
	while(x&&cnt[x]<=1) cnt[x]++,x=tr[x].fa;
}


int main() {
	scanf("%s",s+1);last=1;for(int i=1;s[i];i++) add(s[i]-'a',f);
	scanf("%s",s+1);last=1;for(int i=1;s[i];i++) add(s[i]-'a',g);
	for(int i=2;i<=tot;i++) if(f[i]==g[i]&&f[i]==1) ans=min(ans,tr[tr[i].fa].len+1);
	if(ans==N) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```
# 方法2:$SA$
[思路来源](https://bubbleioa.blog.luogu.org/solution-cf427d)

那里的复杂度是$O(n^2)$,但是我发现可以优化为$O(n)$.

**具体做法**:

按照SA常规操作,用一个特殊字符(如'#')把两个串先连接起来.

首先,显然子串为一个后缀的前缀,所以答案对应的串即为两个串的后缀(设为$x,y$)的前缀啦.

要满足在两个串都唯一出现,后缀$x,y$一定在排序后相邻,否则设中间有一个后缀$z$,$x,y$选择长度为$l$的前缀,那么$z$与$x,y$的公共前缀也一定$\ge l$.

如果我们枚举答案$k$,并对$height$进行分组的话.
只有一组内正好有一个来自A,一个来自B,那么就可行.

这是一个$O(n^2)$的做法:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+10;

char s[N];
int n,m,mid,ans,sa[N],wa[N],wb[N],wv[N],c[N],height[N],rk[N],f[N];
void DA() {
	int *x=wa,*y=wb,i,j,p,k;
	for(i=1;i<=m;i++) c[i]=0;
	for(i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(i=2;i<=m;i++) c[i]+=c[i-1];
	for(i=n;i>=1;i--) sa[c[x[i]]--]=i;
	for(j=p=1;p<n;m=p,j*=2) {
		for(p=0,i=n-j+1;i<=n;i++) y[++p]=i;
		for(i=1;i<=n;i++) if(sa[i]>j) y[++p]=sa[i]-j;
		for(i=1;i<=n;i++) wv[i]=x[y[i]];
		for(i=1;i<=m;i++) c[i]=0;
		for(i=1;i<=n;i++) c[wv[i]]++;
		for(i=2;i<=m;i++) c[i]+=c[i-1];
		for(i=n;i>=1;i--) sa[c[wv[i]]--]=y[i];
		swap(x,y); p=x[sa[1]]=1;
		for(i=2;i<=n;i++)
			x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+j]==y[sa[i]+j])?p:++p;
	}
	for(i=1;i<=n;i++) rk[sa[i]]=i;
	for(i=1,k=0;i<=n;height[rk[i++]]=k)
		for(k?k--:0,j=sa[rk[i]-1];s[i+k]==s[j+k];k++);
}

bool check(int k) {//答案是否>=k 
	int c1,c2; c1=c2=0;
	for(int i=2;i<=n;i++) {//排名为1的为#
		if(height[i]<k) {
			if(c1==1&&c2==1) return 1;
			c1=c2=0; 
			if(sa[i]<mid) c1=1;//A
			else c2=1;
			continue;
		}
		if(sa[i]<mid) c1++;
		else c2++;
	}
	return c1==1&&c2==1;
}

void solve() {
	int ans=-1;
	for(int i=1;i<mid;i++)
		if(check(i)) {ans=i; break;}
	printf("%d\n",ans);
}

int main() {
	scanf("%s",s+1); mid=strlen(s+1); s[++mid]='#';
	scanf("%s",s+mid+1); n=mid+strlen(s+mid+1); m=122;
	DA(); solve(); return 0;
}
```

这样当答案为-1时,判断的代价过高,我们考虑进行优化.

假设我们知道$k$,并且分组情况为$[i,i+1]$,则有:
$\begin{cases}
height[i]<k\\
height[i+1]>=k\\
height[i+2]<k\\
((sa[i]<mid)\operatorname{xor}(sa[i+1]<mid))==1
\end{cases}$

(mid为中间'#'的位置,上面这句话表示一个是A串,一个是B串).

所以我们可以反过来,有$[i,i+2]$的关系来求出最小的$k$.

容易知道:
$ k\in (max(height[i],height[i+2]),height[i+1]) [if~~~i,i+1$来自不同串$]$

所以我们$O(n)$扫描即可求出最小的$k$啦.

如果用$O(n)$求SA,整个算法就$O(n)$啦.~~(然而我并不想打)~~

如果字符总数多达1e7,字符集有很大,就能顺利把$SAM$卡掉啦.

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+10;

char s[N];
int n,m,mid,ans,sa[N],wa[N],wb[N],wv[N],c[N],height[N],rk[N],f[N];
void DA() {
	int *x=wa,*y=wb,i,j,p,k;
	for(i=1;i<=m;i++) c[i]=0;
	for(i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(i=2;i<=m;i++) c[i]+=c[i-1];
	for(i=n;i>=1;i--) sa[c[x[i]]--]=i;
	for(j=p=1;p<n;m=p,j*=2) {
		for(p=0,i=n-j+1;i<=n;i++) y[++p]=i;
		for(i=1;i<=n;i++) if(sa[i]>j) y[++p]=sa[i]-j;
		for(i=1;i<=n;i++) wv[i]=x[y[i]];
		for(i=1;i<=m;i++) c[i]=0;
		for(i=1;i<=n;i++) c[wv[i]]++;
		for(i=2;i<=m;i++) c[i]+=c[i-1];
		for(i=n;i>=1;i--) sa[c[wv[i]]--]=y[i];
		swap(x,y); p=x[sa[1]]=1;
		for(i=2;i<=n;i++)
			x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+j]==y[sa[i]+j])?p:++p;
	}
	for(i=1;i<=n;i++) rk[sa[i]]=i;
	for(i=1,k=0;i<=n;height[rk[i++]]=k)
		for(k?k--:0,j=sa[rk[i]-1];s[i+k]==s[j+k];k++);
}

void solve() {
	int ans=N;
	for(int i=2;i<n;i++) if((sa[i]<mid)^(sa[i+1]<mid)) {
		int a=max(height[i],height[i+2]),b=height[i+1];//k属于(a,b]
		if(a<b) ans=min(ans,a+1);
	}
	if(ans==N) puts("-1");
	else printf("%d\n",ans);
}

int main() {
	scanf("%s",s+1); mid=strlen(s+1); s[++mid]='#';
	scanf("%s",s+mid+1); n=mid+strlen(s+mid+1); m=122;
	DA(); solve(); return 0;
}
```






---

## 作者：He_Ren (赞：6)

z算法

枚举$S_1$的每一个后缀$T_i$

设

$$ S = T_i + \# + S_1 + \$ +S_2 $$

这样，S的每一个长度小于$T_i$的前缀就是$S_1$的一个子串（即每个后缀的每个前缀）

使用z算法，求出$z_i$

如何找可行解？

把原来$T$的位置的$z$忽略掉

然后寻找$z$最大的元素

如果这个元素唯一，那么这就是一个答案

_想一想，为什么？_

但是不难发现，这个答案不是最小的

**新的思路可有类比原来思路得出**

想一想为什么要寻找$z$最大的元素？

因为如果小于最大值，那么最大值就会包含这个序列

所以答案就是，一个元素，没有z值比这个元素大的，自然就是要选z的最大值

从上述思路，寻找如何让答案尽量小

z的次大值自然是不行的

但是发现次大值+1是满足条件的

一方面，它比最大值小，所以被唯一的最大值包含；

另一方面，它比次大值大，所以**仅**被最大值包含

所以可证，次大值+1也是唯一的

所以，按如上方法，对$S_1$的每一个后缀求最大值和次大值，再用次大值更新答案


```cpp
#include<cstdio>
#include<iostream>
#include<string>
const int MAXL = 5e3 + 5;
const int inf = 0x3fffffff;
using namespace std;

inline int min(int a,int b){ return a<b? a: b;}

string s1,s2,s;
int z[MAXL*3];

inline void calc_z(void)
{
	int l=0, r=0;
	for(int i=1; i<(int)s.size(); ++i)
	{
		z[i]=0;
		if(i<r) z[i] = min(r-i, z[i-l]);
		while(r<(int)s.size() && s[z[i]] == s[i+z[i]]) ++z[i];
		if(i+z[i] > r) l=i, r=i+z[i];
	}
}

int main(void)
{
	cin>>s1>>s2;
	
	int ans = inf;
	for(int i=0; i<(int)s1.size(); ++i)
	{
		s = s1.substr(i,s1.size()-i) + '#' + s1 + '$' + s2;
		calc_z();
		z[s1.size()+1] = 0;
		cout<<s<<"\t";
		int tmp=0, tmp2=0;
		bool flag=0;
		int pos = -1;
		for(int j=1; j<(int)s.size(); ++j)
		{
			if(z[j] > tmp)
			{
				tmp2=tmp;
				tmp=z[j];
				pos=j;
				flag=1;
			}
			else if(z[j]==tmp) flag=0;
			else if(z[j] > tmp2) tmp2=z[j];
		}
		if(flag && pos > 2*(int)s1.size() - i + 1)
			ans = min(ans, tmp2+1);
	}
	
	if(ans==inf) printf("-1");
	else printf("%d",ans);
	return 0;
}

```

---

## 作者：huayucaiji (赞：6)

我其实很疑惑，为什么全网没人用 SA？这个题用 SA 不是巨水吗？~~我洗个澡就做出来了~~

我们可以用传统拼接字符串的方式拼接一下字符串，求一遍 SA 和 `height` 数组。

然后呢？其实很简单，题目让我们求的是最短的满足各只出现一次的连续公共字串。好，我们知道对于 `height` 数组，如果一个子串只在两个串中各出现一次，一定是一个“峰值”，即如 $height_{x-1}<height_x>height_{x+1}$。那么这时候我们可以取到的最短的串是多长？我们只要比两边的串长一点就够了，因此是 $\max(height_{x-1},height_{x+1})+1$。一句话答案：

$$ans=\min\limits_{x\in (1,n)\operatorname{and}height_{x-1}<height_x>height_{x+1}} {\{\max(height_{x-1},height_{x+1})+1}\}$$

没有满足条件的 $x$，就输出 $-1$。

时间复杂度 $O(n \log n+n)$。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=2e5+10; 

int n,m;
int sa[MAXN],rnk[MAXN],height[MAXN],tmp[MAXN],a[MAXN],b[MAXN],cnt[MAXN],calc[MAXN],bel[MAXN];
char s[MAXN];

void bucket_sort(int v[]) {
	fill(cnt,cnt+m+1,0);
	for(int i=1;i<=n;i++) {
		cnt[v[i]+1]++;
	}
	for(int i=1;i<=m;i++) {
		cnt[i]+=cnt[i-1];
	}
	for(int i=1;i<=n;i++) {
		tmp[++cnt[v[sa[i]]]]=sa[i];
	}
	for(int i=1;i<=n;i++) {
		sa[i]=tmp[i];
	}
}

void get_sa() {
	for(int i=1;i<=n;i++) {
		rnk[i]=tmp[i]=s[i];
		sa[i]=i;
	}
	sort(tmp+1,tmp+n+1);
	m=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++) {
		rnk[i]=lower_bound(tmp+1,tmp+m+1,rnk[i])-tmp;
	}
	
	for(int l=1;l<n;l<<=1) {
		for(int i=1;i<=n;i++) {
			a[i]=rnk[i];
			b[i]=(i+l<=n? rnk[i+l]:0);
		}
		bucket_sort(b);
		bucket_sort(a);
		
		m=0;
		for(int i=1;i<=n;i++) {
			if(a[sa[i]]!=a[sa[i-1]]||b[sa[i]]!=b[sa[i-1]]) {
				m++;
			}
			rnk[sa[i]]=m;
		}
	}
}

void get_height() {
	int h=0;
	for(int i=1;i<=n;i++) {
		if(h) {
			h--;
		}
		if(rnk[i]==1) {
			continue;
		}
		
		int p=i+h;
		int q=sa[rnk[i]-1]+h;
		
		while(p<=n&&q<=n&&s[p]==s[q]) {
			p++;
			q++;
			h++;
		}
		height[rnk[i]]=h;
	}
}

int solve() {
	int ans=1e9+10;
	bool flag=0;
	
	for(int i=2;i<=n;i++) {
		if(height[i]>height[i-1]&&height[i]>height[i+1]) {
			if(bel[sa[i]]!=bel[sa[i-1]]) {
				ans=min(max(height[i-1],height[i+1])+1,ans);
				flag=1;
			}
		}
	}
	
	return flag? ans:-1;
}

signed main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++) {
		bel[i]=1;
	}
	s[n+1]='$';
	scanf("%s",s+n+2);
	n=strlen(s+1);
	for(int i=1;i<=n;i++) {
		if(!bel[i]&&s[i]!='$') {
			bel[i]=2;
		}
	}
		
	get_sa();
	get_height();
	
	printf("%lld\n",solve());
	return 0;
}

```

---

## 作者：Kotobuki_Tsumugi (赞：3)

首先观察到题面和 [LCS](https://www.luogu.com.cn/problem/SP1811) 很像，可以先按照求 LCS 的思路去想。

我们在求 LCS 的时候，先对一个串建立后缀自动机，用另一个串在后缀自动机上进行匹配。

那本题可不可以这样？可以发现，本题的核心是保证子串只出现过一次。然而之前的方法无法保证这一性质。

令给定的两个字符串为 $S_1$ 和 $S_2$。我们定义数组 $f$ 标记某个子串出现的次数。其中 $f[i][0]$ 和 $f[i][1]$ 分别表示后缀自动机上第 $i$ 个节点表示的子串在 $S_1$ 和 $S_2$ 中出现的次数。

由 $f$ 数组的定义可知，在本题中，我们需要把两个字符串都插入到一个后缀自动机上。每插入完一个节点，需要沿着后缀链往上跳，并修改沿途节点的 $f$ 数组。

可以发现，建立后缀自动机实际上是在求解 $f$ 数组。

最后遍历 $f$ 数组，若 $f[i][0]$ 和 $f[i][1]$ 均为 $1$，检查子串长度，取最大值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6+10;
struct sam{
	int len,father,son[30];
}Trie[N];
int siz = -1,last,ans = 1e9;
int f[N][2];
void Newnode(int len){
	siz++;
	Trie[siz].len = len;
	Trie[siz].father = -1;
	memset(Trie[siz].son,0,sizeof(Trie[siz].son));
}
void Insert(int c,int opx){
	Newnode(Trie[last].len+1);
	int p = last,now = siz;
	while(p != -1 && Trie[p].son[c] == 0)
		Trie[p].son[c] = now,p = Trie[p].father;
	if(p == -1) Trie[now].father = 0;
	else{
		int q = Trie[p].son[c];
		if(Trie[p].len + 1 == Trie[q].len)
			Trie[now].father = q;
		else{
			Newnode(Trie[p].len+1);
			int cop = siz;
			memcpy(Trie[cop].son,Trie[q].son,sizeof(Trie[cop].son));
			f[cop][0] = f[q][0];
			f[cop][1] = f[q][1];
			Trie[cop].father = Trie[q].father;
			Trie[now].father = Trie[q].father = cop;
			while(p != -1 && Trie[p].son[c] == q)
				Trie[p].son[c] = cop,p = Trie[p].father;
		}
	}
	last = now,p = last;
	while(p != -1)
		f[p][opx]++,p = Trie[p].father;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	string s,t; cin>>s>>t;
	Newnode(0);
	int len = s.length();
	for(int i = 0;i<len;i++)
		Insert(s[i] - 'a',0);
	last = 0,len = t.length();
	for(int i = 0;i<len;i++)
		Insert(t[i] - 'a',1);
	for(int i = 1;i<=siz;i++)
		if(f[i][0] == f[i][1])
			if(f[i][0] == 1)
				ans = min(ans,Trie[Trie[i].father].len+1);
	if(ans == 1e9) cout<<-1<<endl;
	else cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Nuisdete (赞：3)

首先单串建 `SAM`，另一个串上去跑发现无法保证另一个串的出现次数为 $1$。

那么双串建出广义 `SAM` ，记两个 $cnt$ 分别统计两个串的子串出现次数，然后暴力扫所有节点用两个 $cnt$ 都是 $1$ 的节点的 `minlen` 更新答案即可。

复杂度是线性的。

代码：[https://codeforc.es/problemset/submission/427/199604071](https://codeforc.es/problemset/submission/427/199604071)

---

## 作者：zhengrunzhe (赞：3)

题解里已经有个sam的了，但是他代码不给全

显然那个什么O(n(n+m))的那个显然是不对的，哪里需要那么做..

直接对两个串建个广义sam，然后分别统计两个size，最后对所有节点看是不是满足$size[0]==1 \&\& size[1]==1$，然后因为一个节点$p$能表示的最短串长是$len[fa[p]]+1$，对这个玩意取个最小值，没得取判-1即可

```cpp
#include<cstdio>
#include<cstring>
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out<0)putchar('-'),out=-out;
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	write(out);putchar('\n');
}
template<class type>inline const int min(const type &a,const type &b)
{
	return a<b?a:b;
}
const int N=5e3+10,M=5e3+10;
template<int maxn,int maxc>class Suffix_Automaton
{
    private:
        static const int maxs=maxn<<1;
        int head[maxs],edc,to[maxs],next[maxs];
        int len[maxs],last,cnt,son[maxs][maxc],size[maxs][2],fa[maxs];
        inline const void addedge(int u,int v)
        {
            next[++edc]=head[u];to[head[u]=edc]=v;
        }
        inline const void extend(int id,int c)
        {
            int p=last;
            if (!son[p][c])
            {
                int np=++cnt;
                size[np][id]++;
                len[last=np]=len[p]+1;
                for (;p&&!son[p][c];p=fa[p])son[p][c]=np;
                if (!p)return fa[np]=1,void();
                int q=son[p][c];
                if (len[q]==len[p]+1)return fa[np]=q,void();
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(son[nq],son[q],sizeof(son[q]));
                fa[nq]=fa[q];fa[q]=fa[np]=nq;
                for (;son[p][c]==q;p=fa[p])son[p][c]=nq;
                return;
            }
            int q=son[p][c];
            if (len[q]==len[p]+1)return size[last=q][id]++,void();
            int nq=++cnt;len[nq]=len[p]+1;
            memcpy(son[nq],son[q],sizeof(son[q]));
            fa[nq]=fa[q];fa[q]=nq;
            for (;son[p][c]==q;p=fa[p])son[p][c]=nq;
            size[last=nq][id]++;
        }
        inline const void dfs(int p)
        {
            for (int son,i=head[p];i;i=next[i])
				dfs(son=to[i]),
				size[p][0]+=size[son][0],
				size[p][1]+=size[son][1];
        }
    public:
        inline Suffix_Automaton():cnt(1){}
        inline const void insert(int id,char *s)
        {
            last=1;
            int n=strlen(s+1);
            for (int i=1;i<=n;i++)extend(id,s[i]-'a');
        }
        inline const int build()
        {
            for (int i=2;i<=cnt;i++)addedge(fa[i],i);
            dfs(1);int mn=maxn;
            for (int i=2;i<=cnt;i++)
                if (size[i][0]==1&&size[i][1]==1)
                	mn=min(mn,len[fa[i]]+1);
            return mn==maxn?-1:mn;
        }
};
Suffix_Automaton<N+M,26>sam;
char s[N],t[N];
int main()
{
	scanf("%s%s",s+1,t+1);
	sam.insert(0,s);
	sam.insert(1,t);
	writeln(sam.build());
	return 0;
}
```

---

## 作者：qiyue7 (赞：3)

广义SAM裸题   

直接插入双串以后暴力枚举所有节点即可


细节看主代码：

```cpp

 
int main()
{
	ios::sync_with_stdio(false);
	EXSAM part;
	string a, b;
	cin >> a >> b;
	part.init();
	for (auto &s : a)
		part.Insert(s - 'a', 0);
	part.last = part.root;
	for (auto &s : b)
		part.Insert(s - 'a', 1);
	part.topo();
	int cnt = part.cur - EXSAM_Pool;
	for (int i = cnt - 1; i >= 1; i--)
	{
		EXpool[i]->pre->cnt[0] += EXpool[i]->cnt[0];
		EXpool[i]->pre->cnt[1] += EXpool[i]->cnt[1];
	}
	int ans = 100000;
	for (int i = cnt - 1; i >= 1; i--)
	{
		if (EXpool[i]->cnt[0] == 1 && EXpool[i]->cnt[1] == 1)
		{
			ans = min(ans, EXpool[i]->pre->step+1);
		}
	}
	if (ans != 100000)
		cout << ans << endl;
	else
		cout << -1 << endl;
	return 0;
}
 
```


---

## 作者：Kobe303 (赞：2)

提供一种 $\Theta(n^2)$ 的 DP 做法。

**思路来自 CF 官方题解**。

这里均默认字符串下标从 $1$ 开始。

我们先对字符串 $s_1$ 求出它本身的 $\text{LCP}$，并求出对于每一个 $i\in [1,\left |s_1 \right |]$ 它的最短唯一子串的长度。对字符串 $s_2$ 也做这样的操作。

然后我们对于字符串 $s_1$ 和 $s_2$ 求出它们的 $\text{LCP}$。

最后枚举一遍，统计答案。

具体实现以及细节可以看代码，若觉得上面说的有点抽象也可以通过看代码并手玩几个样例来加深理解。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5005, inf = 0x3f3f3f3f;
int lcp[N][N];
char a[N], b[N];
int mUA[N], mUB[N];
int ans = inf;
int n, m;

void calcLCP(char a[N], char b[N], int LCP[N][N]) {
	n = strlen(a + 1), m = strlen(b + 1);
	for (int i = n; i; --i)
		for (int j = m; j; --j) {
			if (a[i] == b[j]) LCP[i][j] = LCP[i + 1][j + 1] + 1;
			else LCP[i][j] = 0;
		}
}

int main() {
	scanf("%s%s", a + 1, b + 1);
	calcLCP(a, a, lcp);
	n = strlen(a + 1);
	for (int i = 1; i <= n; ++i) {
		int len = 0;
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue;
			len = max(len, lcp[i][j]);
		}
		++len;
		mUA[i] = len;
	}
	memset(lcp, 0, sizeof lcp);
	calcLCP(b, b, lcp);
	m = strlen(b + 1);
	for (int i = 1; i <= m; ++i) {
		int len = 0;
		for (int j = 1; j <= m; ++j) {
			if (i == j) continue;
			len = max(len, lcp[i][j]);
		}
		++len;
		mUB[i] = len;
	}
	memset(lcp, 0, sizeof lcp);
	calcLCP(a, b, lcp);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (lcp[i][j] >= max(mUA[i], mUB[j]))
				ans = min(ans, max(mUA[i], mUB[j]));
	if (ans == inf) ans = -1;
	printf("%d", ans);
	return 0;
}
```


---

## 作者：shao0320 (赞：2)

### CF427D Match & Catch

考虑暴力到不能再暴力的一个玩意儿。

枚举答案 $i$ ，找出 $S_1$ 中所有长度为 $i$ 的子串，看看它在 $S_1$ 和 $S_2$ 中出现的次数。

咋优化？

可以先枚举一遍，再暴力枚举子串统计，拿个 $\text{map}$ 存一下。

但还是歇，咋整？

哈希！

但 $O(N^2 \log N)$还是过不了，咋办？

哈希表！手写个哈希表代替 $\text{map}$ 就过啦！

---

## 作者：chenxia25 (赞：2)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF427D) & [CodeForces题目页面传送门](https://codeforces.com/contest/427/problem/D)

>给定$2$个字符串$a,b,|a|=n,|b|=m$，求最长的既在$a$中出现恰好$1$次又在$b$中出现恰好$1$次的非空字符串的长度，如果不存在输出$-1$。

>$n,m\in[1,5000]$。

emmm，数据范围很不友好，$\mathrm O(nm)$带$\log$都不行。。。

考虑枚举$a$的子串。枚举子串可以转化为枚举所有后缀的所有前缀，这样一来就有了“前缀”这个东西可以利用。

我们在枚举$a$的后缀$a_{i\sim n}$的时候，令$c=a_{i\sim n}+\texttt{!}+a+\texttt{@}+b,s=|c|$。对$c$跑一遍Z算法（如果聪明的读者还不知道Z算法是什么，please点击[这个](https://www.luogu.org/blog/Chenxiao-Yan/Z-algorithm)），就可以知道后缀$a_{i\sim n}$在$a,b$中的出现情况了。

我们先把$z_{c,n-i+3\sim 2n-i+2},z_{c,2n-i+4\sim s}$分别装在$2$个桶$buc1,buc2$里，即$buc1_j$表示使得从$a$的这个位置往后和$a_{i\sim n}$的前缀匹配最长长度为$j$的位置数，$buc2$类似。可是我们想要的是使得从$a$的这个位置往后和$a_{i\sim n}$的前缀匹配**最长长度${\ge j}$**的位置数，也就是使得从$a$的这个位置往后和$a_{i\sim n}$的前缀**能够匹配$ j$这么长**的位置数。于是我们可以从$j=n-i+1$到$j=1$从大到小枚举即将被check的$a_{i\sim n}$的前缀的长度$j$，每次若$buc1_j=buc2_j=1$，则check成功，更新答案$ans=\max(ans,j)$，然后令$buc1_{j-1}=buc1_{j}+buc1_{j-1},buc2_{j-1}=buc2_{j}+buc2_{j-1}$即可。考虑为什么这么从大到小递推是对的：首先$buc1_{n-i+1},buc2_{n-i+1}$本来就有我们想要的意思。每次更新$buc1_{j-1},buc2_{j-1}$都会把它们变成我们想要的意思下的值~~（感性理解理解）~~，于是每到一个$j$，$buc1_j,buc2_j$都会是我们想要的意思咯。（想一想就会发现，上述那个递推就是$[1,buc1_j/buc2_j]$区间$+1$的差分。当然如果想不到差分的话，线段树或树状数组是比较容易想的，但是带$\log$，过不掉。。。）

这样复杂度就是$\mathrm O(n(n+m))$~~，侥幸过~~。

下面考虑哈希怎么做。很显然是做不了的。。。最快也就是按上述方法，用哈希+二分求$z$数组，但数据范围不友好啊QWQ

对了，数据不清空，爆零两行泪。每枚举一个$a$的后缀时，都要清空$2$个桶！！！

下面上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5000,M=5000;
int n,m,s;//|a|，|b|，|c| 
char a[N+5],b[M+5],c[2*N+M+5]/*a的后缀+'!'+a+'@'+b*/;
int z[2*N+M+1];//z数组 
void z_init(){//Z算法 
	int zl=0,zr=0;
	for(int i=2;i<=s;i++)
		if(zr<i){
			z[i]=0;
			while(i+z[i]<=s&&c[i+z[i]]==c[1+z[i]])z[i]++;
			if(z[i])zl=i,zr=i+z[i]-1;
		}
		else if(i+z[i-zl+1]<=zr)z[i]=z[i-zl+1];
		else{
			z[i]=zr-i+1;
			while(i+z[i]<=s&&c[i+z[i]]==c[1+z[i]])z[i]++;
			zl=i;zr=i+z[i]-1;
		}
//	cout<<"z";for(int i=2;i<=s;i++)cout<<z[i];puts("");
}
int buc1[N+1],buc2[N+1];//2个桶 
int main(){
	cin>>a+1>>b+1;
	n=strlen(a+1);m=strlen(b+1);
	int ans=inf; 
	for(int i=1;i<=n;i++){//枚举后缀的左端点 
		s=0;
		for(int j=i;j<=n;j++)c[++s]=a[j];
		c[++s]='!';
		for(int j=1;j<=n;j++)c[++s]=a[j];
		c[++s]='@';
		for(int j=1;j<=m;j++)c[++s]=b[j];
		c[s+1]=0;
		//上面都在造c 
//		cout<<c+1<<"\n";
		z_init();
		memset(buc1,0,sizeof(buc1));memset(buc2,0,sizeof(buc2));//数据不清空，爆零两行泪 
//		for(int j=n-i+3;j<=2*n-i+2;j++)cout<<c[j];cout<<" ";for(int j=2*n-i+4;j<=s;j++)cout<<c[j];puts("");
		for(int j=n-i+3;j<=2*n-i+2;j++)buc1[z[j]]++;//装到桶里面 
		for(int j=2*n-i+4;j<=s;j++)buc2[z[j]]++;//同上 
		for(int j=n-i+1;j;j--){//枚举后缀的前缀的长度 
//			printf("buc1[%d]=%d buc2[%d]=%d\n",j,buc1[j],j,buc2[j]);
			if(buc1[j]==1&&buc2[j]==1)ans=min(ans,j);//如果各出现恰好1次，则更新答案 
			buc1[j-1]+=buc1[j];buc2[j-1]+=buc2[j];//将buc1[j-1],buc2[j-1]变为我们想要的意思 
		}
//		puts("");
//		cout<<"ans="<<ans<<"\n";
	}
	printf("%d",ans<inf?ans:-1);
	return 0;
}
```

---

## 作者：I_AK_IoI_2030 (赞：1)

### 题意
给定两个字符串，求最短的满足各只出现一次的（连续）公共子串。

### 做法
提供一种 $O(n^2)$ 的线性 DP 做法。

首先我们可以 $O(n^2)$ 地求出 $s_1$ 与 $s_2$ 的 LCS（最长公共子串）。这是基本模型，不再赘述。

题目要求的子串在 $s_1$ 与 $s_2$ 中均**不重复**，在这里定义 $f_{1,i,j}$ 表示 $s_1$ 到下标 $i$ 为止的前缀与其到下标 $j$ 为止的前缀的后缀 LCS，$fmax_{1,i}$ 表示 $s_1$ 到下标 $i$ 为止的 $s_1$ 前缀与 $s_1$ **其他部分**的后缀 LCS，则有 $fmax_{1,i}=\max_{j=0}^{|s|-1} f_{1,i,j}(i  \ne j)$，$f_{2,i}$ 类似。子串不重复，即其长度大于重复子串的最长长度（即 $\max(fmax_{1,i},fmax_{2,j})$），那么合法的子串长度值域为 $\{ len \mid len
\in(\max (fmax_{1,i},fmax_{2,j}),LCS_{i,j}],i\in [0,|s_1|),j\in [0,|s_2|) \}$，所以答案如果存在，就是最小的 $len$。

$f_{1,i,j}$ 与 $f_{2,i,j}$ 亦可以用类似 LCS 的算法求出，算法总时间复杂度为 $O(n^2)$。

附代码如下：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string s[2];
int n[2];
int ans=5010,f[5010][5010];
int g[2][5010][5010],maxg[2][5010];
void pre_work(int (&gg)[5010][5010],int (&maxgg)[5010],string &ss,int nn){
	for(int i=1;i<=nn;i++){
		for(int j=1;j<=nn;j++){
			if(i==j) continue;
			if(ss[i-1]==ss[j-1]) maxgg[i]=max(gg[i][j]=gg[i-1][j-1]+1,maxgg[i]);
		}
	}
}
int main(){
	cin>>s[0]>>s[1];n[0]=s[0].length(),n[1]=s[1].length();
	pre_work(g[0],maxg[0],s[0],n[0]);pre_work(g[1],maxg[1],s[1],n[1]);
	for(int i=1;i<=n[1];i++){
		for(int j=1;j<=n[0];j++){
			if(s[1][i-1]==s[0][j-1]){
				f[i][j]=f[i-1][j-1]+1;
				if(f[i][j]>max(maxg[0][j],maxg[1][i])) ans=min(ans,max(maxg[0][j],maxg[1][i])+1);
			}
		}
	}
	printf("%d",ans == 5010 ? -1 : ans);
	return 0;
}
```

谢谢阅读。如有可行的优化或者题解出现问题，请私信。

---

## 作者：Jsxts_ (赞：1)

SAM 裸题。

对 $S$ 和 $T$ 都建出 SAM，由于这题允许 $O(n^2)$，就在 $S$ 中枚举左端点，然后再枚举右端点，在 $S$ 和 $T$ 的 SAM 中同时匹配，右端点往右就往后跳一个字符。如果出现次数都是 $1$ 就更新答案然后跳出循环，如果在 $T$ 中的出现次数为 $0$ 就直接跳出循环。

求 SAM 每个状态的出现次数可以参考模板。

实在看不懂的话，就看代码理解好了，非常简单易懂。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
char s[5010],t[5010];
struct Suffix_Automaton {
	struct node {
		int len,link;
		int nxt[26];
	}st[10010];
	int sum[10010],cnt[10010],pre[10010];
	int sz,last;
	Suffix_Automaton() {
		sz = last = 1;
	}
	void insert(char ch) {
		int x = ++sz,p = last; last = x;
		st[x].len = st[p].len + 1;
		sum[x] = 1;
		for (;!st[p].nxt[ch];p = st[p].link) st[p].nxt[ch] = x;
		if (!p) st[x].link = 1;
		else {
			int q = st[p].nxt[ch];
			if (st[p].len + 1 == st[q].len) st[x].link = q;
			else {
				int y = ++sz;
				st[y] = st[q], st[y].len = st[p].len + 1;
				for (;st[p].nxt[ch] == q;p = st[p].link) st[p].nxt[ch] = y;
				st[x].link = st[q].link = y;
			}
		}
	}
	void init() {
		for (int i = 1;i <= sz;i ++ ) cnt[st[i].len] ++;
		for (int i = 1;i <= sz;i ++ ) cnt[i] += cnt[i-1];
		for (int i = 1;i <= sz;i ++ ) pre[cnt[st[i].len]--] = i;
		for (int i = sz;i >= 1;i -- ) {
			int x = pre[i];
			sum[st[x].link] += sum[x];//求在这个状态中每个子串的出现次数
		}
	}
}S,T;
int main() {
	scanf("%s%s",s+1,t+1);
	int ls = strlen(s+1),lt = strlen(t+1);
	for (int i = 1;i <= ls;i ++ ) S.insert(s[i] - 'a');
	for (int i = 1;i <= lt;i ++ ) T.insert(t[i] - 'a');
	S.init(); T.init();
	int ans = 2e9;
	for (int i = 1;i <= ls;i ++ ) {
		int us = 1,ut = 1;//同时在 SAM 上 匹配
		for (int j = i;j <= ls;j ++ ) {
			us = S.st[us].nxt[s[j] - 'a'];
			if (!T.st[ut].nxt[s[j] - 'a']) break;
			ut = T.st[ut].nxt[s[j] - 'a'];
			if (S.sum[us] == 1 && T.sum[ut] == 1) {
				ans = min(ans,j - i + 1);//更新答案
				break;
			}
		}
	}
	printf("%d\n",ans == 2e9 ? -1 : ans);
	return 0;
}
```


---

## 作者：Y_ATM_K (赞：0)

提供一种简单的 SAM 做法。设 $s(l,r)$ 为字符串 $s$ 第 $l$ 位到第 $r$ 位形成的子串，$len_i$ 为 $i$ 号结点的最大长度，$link_i$ 为 $i$ 号结点的后缀链接。

先对 $s_1$ 建 SAM，对每个 $s_2$ 的每个前缀跑匹配，设匹配到 $s_2$ 第 $i$ 个前缀时对应的 SAM 结点为 $p_i$ ，匹配长度为 $nowlen_i$。

显然 $p_i$ 长度在 $[len_{link_{p_i}}+1,nowlen_i]$ 的后缀与 $s_2(1,i)$ 的后缀匹配。显然可以有多个 $x$ 满足 $s_2(1,x)$ 的后缀与同一结点匹配，设结点 $i$ 与 $s_2$ 的最长匹配长度为 $max1len_{i}$，次长匹配长度为 $max2len_{i}$（可以相等）。

因为符合题意的公共子串要满足在 $s_1$ 中只出现一次，所以只需要考虑所有结束位置只有一个的 $p_i$，也就是 parent 树的叶子结点。

1. 不存在 $j \not = i,p_j = p_i$，即 $p_i$ 是唯一的。此时 $p_i$ 的所有长度在 $[len_{link_{p_i}}+1,nowlen_i]$ 的后缀均只在 $s_2$ 中出现一次，对答案贡献 $len_{link_{p_i}}+1$。
2. 存在 $j \not = i,p_j = p_i$，即 $p_i$ 不唯一，但是 $max1len_{p_i} > max2len_{p_i}$，即最长的匹配只在 $s_2$ 中出现了一次。此时 $p_i$ 的所有长度在 $[max2len_{p_i}+1,max1len_{p_i}]$ 的后缀均只在 $s_2$ 中出现一次，对答案贡献 $max2len_{p_i}+1$。
3. 存在 $j \not = i,p_j = p_i$，即 $p_i$ 不唯一，且 $max1len_{p_i} = max2len_{p_i}$，即最长的匹配在 $s_2$ 中出现了多次。此时 $p_i$ 的所有后缀都不满足条件。

直接维护 $max1len,max2len$ 即可。

时间复杂度 $O(|s_1| + |s_2|)$。

[通过记录](https://codeforces.com/problemset/submission/427/259860752)

---

## 作者：冒泡ioa (赞：0)

> [博客链接](http://bubbleioa.top/archives/915)
## 题解
题目大意：求最小不重复相同子串。

考虑把两个字符串合并起来，求出sa，rk和Height数组。

我们可以从小到大枚举子串长度k，然后再枚举后缀。  
具体来说，我们是根据子串字典序从小到大枚举后缀的  
如果Height[i]不小于k（即第i-1个子串和第i个子串的最长公共前缀不小于k），  
并且如果此后缀的起始点在第一个字符串，cnt1++  
否则cnt2++

cnt1和cnt2分别代表最长公共子串出现在第一个字符串和第二个字符串的次数，由于是连续更新的，所以假如上一轮cnt1=1，现在更新cnt2=1那么说明这两个子符串有相同的长度大于k的公共子串，但是不是唯一还不知道。  
也就是说这个数字只在两轮更新中有用，如果cnt1>1或cnt2>1都没有价值了（要么没有公共子串，要么有重复的）。  
如果要确保唯一性，就要当Height[i]枚举到小于k的时候，如果此时cnt1==1&&cnt2==1的话，则有解。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s1,s2,str;
int len1,tot,m;
const int MAXN=10004;
int a[MAXN],Height[MAXN],tax[MAXN],tp[MAXN],sa[MAXN],rk[MAXN];

void RSort(){
    for(int i=1;i<=m;i++)tax[i]=0;
    for(int i=1;i<=tot;i++)tax[rk[i]]++;
    for(int i=1;i<=m;i++)tax[i]+=tax[i-1];
    for(int i=tot;i>=1;i--)sa[tax[rk[tp[i]]]--]=tp[i];
}


bool cmp(int *f,int x,int y,int w){
    return f[x]==f[y]&&f[x+w]==f[y+w];
}

void Suffix(){
    m=127;
    for(int i=1;i<=tot;i++)rk[i]=a[i],tp[i]=i;
    int p=0;RSort();
    for(int w=1;p<tot;w+=w,m=p){
        p=0;for(int i=tot-w+1;i<=tot;i++)tp[++p]=i;
        for(int i=1;i<=tot;i++)if(sa[i]>w)tp[++p]=sa[i]-w;
        RSort();swap(rk,tp);rk[sa[1]]=p=1;
        for(int i=2;i<=tot;i++)rk[sa[i]]=cmp(tp,sa[i],sa[i-1],w)?p:++p;
    }
    int j=0,k=0;
    for(int i=1;i<=tot;Height[rk[i++]]=k){
        for(k=k?k-1:k,j=sa[rk[i]-1];a[i+k]==a[j+k];k++);
    }
}

bool solve(int k,int div){
    int cnt1=0,cnt2=0;
    for(int i=1;i<=tot;i++){
        if(Height[i]<k){
            if(cnt1==1&&cnt2==1){
                return true;    
            }
            cnt1=0;cnt2=0;
            if(sa[i]<=div)cnt1++;
            else if(sa[i]>=div)cnt2++;
            continue;
        }
        if(sa[i]<=div)cnt1++;
        else if(sa[i]>=div)cnt2++;
    }
    return cnt1==1&&cnt2==1;//如果枚举完了也要判断一下
}

int main(){
    cin>>s1>>s2;
    len1=s1.length();
    str=s1+'#'+s2;//将两个字符串隔开来，避免sa等数组重叠
    tot=len1+s2.length()+1;
    for(int i=1;i<=tot;i++)a[i]=str[i-1]; 
    Suffix();//后缀数组
    int ans=-1;
    for(int i=1;i<=len1;i++){//枚举长度
        if(solve(i,len1)){
            ans=i;break;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```


---

