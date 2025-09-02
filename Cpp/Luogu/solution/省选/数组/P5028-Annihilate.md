# Annihilate

## 题目背景

前情提要：小正方形与黑暗之主展开了大战，最后小正方形击败了黑暗之主，成功从黑暗之主的手上夺下最后一个三角。

三角旋转着，净化着，正当三角即将净化完成时，黑暗之主突然到来，阻断了三角形的净化，吸收了三角的能量。

可是，因为三角的能量太过巨大，导致黑暗之主发生了变异，现在的黑暗之主一次次复制，最终成为了一条蜈蚣……

现在，小正方形还能阻止黑暗之主毁灭世界吗？

## 题目描述

黑暗之主的蜈蚣几乎可以毁灭一切，因此小正方形陷入了苦战……

小正方形现在需要减弱黑暗之主的攻击。

一个黑暗之主的攻击可以用一个仅有小写字母的字符串表示。

现在黑暗之主向小正方形发动了若干攻击，对于两个攻击，小正方形能选出它们最长的公共**子串**，并把这一段消除。

现在小正方形想要知道，对于**任意两个**黑暗之主的攻击，它们的最长公共子串长度是多少，你能帮帮它吗？

## 说明/提示

对于 $30\%$ 的数据，$n \le 5$，每个字符串长度不超过 $500$。

对于 $100\%$ 的数据，$2 \le n \le 50$，字符串长度之和不超过 $10^6$。

**注意：本题内存限制仅为 $64$ MB,请尽量使用内存运用优秀的方法。**

另外，对于占 $60$ pts 的测试点，您每通过一个点即可获得 $10$ pts。

对于剩下的测试点，您只有全部通过才能获得 $40$ pts。

**对于所有数据点，不保证数据为随机生成。**

## 样例 #1

### 输入

```
3
abb
bcc
aba```

### 输出

```
1 2
1 1
2 1```

# 题解

## 作者：Tx_Lcy (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P5028)

## 思路

算是一道简单的 $\rm SA$ 题吧，连我这种刚学 $\rm SA$ 一天的菜鸡都会做。

首先，注意到 $n \le 50,\sum |s_i| \le 10^6$，启示我们复杂度可能是 $n \times \sum |s_i|$，不然毒瘤出题人不可能把 $n$ 开的这么小。

根据 $\rm SA$ 题的一贯套路，我们需要把这些串拼起来，然后跑一遍 $\rm SA$ 求出 $\rm height$ 和 $\rm sa$。

注意到如果我们枚举到排名为 $i$ 的后缀，有这么两个数 $j1$ 和 $j2$，钦定 $j1<j2$，那么区间 $j_1,i$ 的最小 $\rm height$ 一定 $\le$ 区间 $j_2,i$ 的最小 $\rm height$，于是，我们只需要对每个 $i\ (1 \le i \le n)$ 维护一个最右指针即可。

如果出题人不卡空间，那么可以直接上 $\rm ST$ 表，不过出题人比较毒瘤，于是我们只能维护一个长度为 $n$ 的数组 $\rm minx_j$ 表示从上一个 $j$ 出现的位置到当前枚举的 $i$ 中 $\rm height$ 的最小值。

最后就是 $\rm SA$ 的实现了，设 $m=\sum |s_i|$。你可以做到 $\mathcal O(m \log m)$，不过我不喜欢动脑子，于是直接 $\mathcal O(m \log^2 m)$，在洛谷评测机状态好的情况下开 $\rm O_2$ 可以过，最慢的点大约 $\rm 1.95 \ s$。

时间复杂度 $\mathcal O(m \log^2 m+nm)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=3e6+10;
char k[N];
int rk[N],w,ans[105][105],minx[105],frm[N],sum[N],oldrk[N],sa[N],height[N];
inline bool cmp(int x,int y){return rk[x]==rk[y]?rk[x+w]<rk[y+w]:rk[x]<rk[y];}
inline void SA(string s){
	int n=s.length();s=" "+s;
	for (int i=1;i<=n;++i) k[i]=s[i];
	sort(k+1,k+n+1);
	for (int i=1;i<=n;++i) rk[i]=lower_bound(k+1,k+n+1,s[i])-k,sa[i]=i;
	for (w=1;w<n;w<<=1){
		sort(sa+1,sa+n+1,cmp);
		for (int i=1;i<=n;++i) oldrk[i]=rk[i];
		for (int p=0,i=1;i<=n;++i)
			if (oldrk[sa[i]]==oldrk[sa[i-1]] && oldrk[sa[i]+w]==oldrk[sa[i-1]+w]) rk[sa[i]]=p;
			else rk[sa[i]]=++p;
	}
	for (int i=1;i<=n;++i) rk[sa[i]]=i;
	int k=0;
	for (int i=1;i<=n;++i){
		if (k) --k;int j=sa[rk[i]-1];
		while (j+k<=n && i+k<=n && s[i+k]==s[j+k]) ++k;
		height[rk[i]]=k;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;string ss="";
	for (int i=1;i<=n;++i){
		string s;cin>>s;
		int len=s.length();
		s=" "+s;for (int j=1;j<=len;++j)
			ss+=s[j],frm[ss.length()]=i;
		ss+=char(i+26);
	}
	SA(ss);int m=ss.length();
	for (int i=2;i<=m;++i){
		for (int j=1;j<=n;++j) minx[j]=min(minx[j],height[i]);
		minx[frm[sa[i-1]]]=height[i];
		int now=frm[sa[i]];
		for (int j=1;j<=n;++j) ans[now][j]=ans[j][now]=max(ans[now][j],minx[j]);
	}
	for (int i=1;i<=n;++i,cout<<'\n')
		for (int j=1;j<=n;++j)
			if (i^j) cout<<ans[i][j]<<' ';
	return 0;
}
```

$\rm upd$：有一个 $\rm s$ 写成 $\rm ms$ 了，希望管理能重新审核一下。

---

## 作者：chenly8128 (赞：3)

### 分析

题目要求求出每一对字符串的最长公共子串。
1. **最长公共子串**可以联想到后缀数组中的公式 $lcp (sa[i],sa[j]) = \min_{x=i+1}^n height_x$。
2. 经典套路：把所有字符串连在一起处理。
3. 分隔符不能少，并且要区分。
4. $n$ 非常小，所以可以暴力，$O(nm)$。

综合上述想法，可以把所有字符串连在一起（别忘了分隔符），然后求后缀数组。求出 $height$。求完了以后按照后缀排序的顺序扫一遍，对于每个后缀，枚举所有其他的字符串，求出它们与这个后缀的 $lcp$，然后更新答案。

计算 $lcp$ 的过程就是一段 $height$ 求最小值的过程。由于空间问题，最好别用数据结构（也没必要）。直接利用贪心的思想，越近越优，所以每一个不同的字符串只需要保存一个目前的 $height$ 最小值就行了，这个值就是最近的，也是所有最小值中最大的。

### 代码

AC 774 ms，30.5 MB。


```cpp

// Author: chenly8128
// Created: 2024-12-28 14:12:03

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+1000;
const int MAXM = 256;
namespace SA {
	int sa[MAXN],rk[MAXN],old[MAXN<<1],id[MAXN],cnt[MAXN<<1],cur;
	int height[MAXN];
	void Sort (const char * const s,int n) {
		memset (cnt,0,sizeof (cnt));
		int m = MAXN,p = 0,ct = 255;
		for (int i = 1;i <= n;i++) cnt[rk[i]=(s[i]=='@'?++ct:s[i])]++;
		for (int i = 1;i <= m;i++) cnt[i] += cnt[i-1];
		for (int i = 1;i <= n;i++) sa[cnt[rk[i]]--] = i;
		for (int w = 1;w <= n;w <<= 1,m = p) {
			cur = 0;
			for (int i = n-w+1;i <= n;i++) id[++cur] = i;
			for (int i = 1;i <= n;i++)
				if (sa[i] >= w) id[++cur] = sa[i]-w;
			memset (cnt,0,sizeof (cnt));
			for (int i = 1;i <= n;i++) cnt[rk[i]]++;
			for (int i = 1;i <= m;i++) cnt[i] += cnt[i-1];
			for (int i = cur;i > 0;i--) sa[cnt[rk[id[i]]]--] = id[i];
			memcpy (old,rk,sizeof (rk));
			p = 0;
			for (int i = 1;i <= n;i++)
				if (old[sa[i]] == old[sa[i-1]] && old[sa[i]+w] == old[sa[i-1]+w]) rk[sa[i]] = p;
				else rk[sa[i]] = ++p;
			if (p == n) break;
		}
	}
	void Height (const char * const s,int n) {
		for (int i = 1,k = 0;i <= n;i++) {
			if (rk[i] == 0) continue;
			k = max(0,k-1);
			while (s[i+k] != '@' && s[i+k] == s[sa[rk[i]-1]+k]) k++;
			height[rk[i]] = k;
		}
	}
	void build (const char * const s,int n) {
		Sort(s,n);
		Height(s,n);
	}
}
int n,tmp[55],ne[55],ans[55][55];
string s,p;
int main (void) {
	ios::sync_with_stdio(false);
	cin >> n;
	s = " ";
	for (int i = 1;i <= n;i++) {
		cin >> p;
		s += p;
		s += '@';
		tmp[i] = s.size()-1;
	}
	SA::build(s.c_str(),s.size()-1);
	for (int i = 1;i <= s.size()-1;i++) {
		int w = SA::sa[i],be = n;
		while (be >= 1 && tmp[be-1] >= w) be--;
		for (int j = 1;j <= n;j++) {
			ne[j] = min(ne[j],SA::height[i]);
			if (be != j) ans[be][j] = max(ans[be][j],ne[j]);
		}
		ne[be] = 0x3f3f3f3f;
	}
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++)
			if (i != j) printf ("%d ",max(ans[i][j],ans[j][i]));
		putchar ('\n');
	}
	return 0;
}
```

---

## 作者：AThousandSuns (赞：3)

出题人的题解没有代码有点难懂……这里就再发一篇题解吧。

---
最长公共子串，很明显的后缀数组。具体如何求解呢？

我们枚举 $i=1\rightarrow n$，$id[sa[i]]$ 即是排名为 $i$ 的后缀所在的串。

那么设 $ans[i][j]$ 为第 $i$ 个串和第 $j$ 个串的答案，那么就可以对每一个 $j$ 更新 $ans[id[sa[i]]][j]$。

显而易见的是 $lcp(sa[i],sa[j])\ge lcp(sa[i],sa[k])(j\ge k)$，于是可以记录一个 $pre[j]$ 表示上一个属于 $j$ 串的后缀的位置，就可以用 $pre[j]+1$ 到 $i$ 中 $height$ 的最小值来更新答案。这明显是当前的最优解。

目前时间复杂度是 $O(n\times len)$，看来区间最小值需要 $O(1)$。ST表？

`注意：本题内存限制仅为 64 MB,请尽量使用内存运用优秀的方法。`

万恶的出题人……

可以考虑 $minh[j]$ 表示当前从 $pre[j]+1$ 开始所有 $height$ 的最小值。每枚举一个 $i$，就 $O(n)$ 更新所有的 $minh$。如果 $pre[j]$ 变了，那么 $minh[j]$ 就和前面的 $height$ 无关了，重置 $minh[j]$ 即可。

时间复杂度 $O(n\times len)$，空间复杂度 $O(n^2+len)$。

---
感觉说的还不是很清楚，还是放代码吧。如果还有不懂的在评论里说哦~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2222222;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
	char ch=getchar();int x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,N,m,a[maxn],sa[maxn],rak[maxn],tmp[maxn],cnt[maxn],h[maxn],id[maxn],ans[55][55],minh[55];
char s[maxn];
bool vis[55];
void radix_sort(){
	FOR(i,0,m) cnt[i]=0;
	FOR(i,1,N) cnt[rak[tmp[i]]]++;
	FOR(i,1,m) cnt[i]+=cnt[i-1];
	ROF(i,N,1) sa[cnt[rak[tmp[i]]]--]=tmp[i]; 
}
void Suffix_array(){	//模板，不解释
	m=n+26;
	FOR(i,1,N) rak[tmp[i]=i]=a[i];
	radix_sort();
	for(int d=1,p=1;p<N;m=p,d<<=1){
		p=0;
		FOR(i,1,d) tmp[++p]=N-d+i;
		FOR(i,1,N) if(sa[i]>d) tmp[++p]=sa[i]-d;
		radix_sort();
		swap(rak,tmp);
		p=rak[sa[1]]=1;
		FOR(i,2,N) rak[sa[i]]=tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+d]==tmp[sa[i-1]+d]?p:++p;
	}
	FOR(i,1,N) rak[sa[i]]=i;
	int k=0;
	FOR(i,1,N){
		if(k) k--;
		int j=sa[rak[i]-1];
		while(a[i+k]==a[j+k]) k++;
		h[rak[i]]=k;
	}
}
void solve(){
	FOR(i,1,N){
		FOR(j,1,n){
			minh[j]=min(minh[j],h[i]);	//更新所有的minh
			if(vis[j]) ans[id[sa[i]]][j]=max(ans[id[sa[i]]][j],minh[j]);
            //前面已经有j串出现过，更新答案
		}
		if(id[sa[i]]) vis[id[sa[i]]]=true,minh[id[sa[i]]]=INT_MAX;
        //重置minh[id[sa[i]]]，因为有了一个更后的字符
        //为何这个if要放后面呢？因为h[i]的含义是lcp(sa[i],sa[i-1])，所以用i更新答案时应不考虑pre对minh的影响
        //实际上我们没有必要记录pre，只要在新出现一个字符后顺带更新一下minh就行了
	}
}
int main(){
	n=read();
	FOR(i,1,n){
		scanf("%s",s);
		int l=strlen(s);
		FOR(j,0,l-1) a[++N]=s[j]-'a'+1,id[N]=i;	//标记编号
		a[++N]=i+26;	//注意加的分隔符要不同，不然lcp可能会多1
	}
	Suffix_array();
	solve();
	FOR(i,1,n){
		FOR(j,1,n) if(i!=j) printf("%d ",max(ans[j][i],ans[i][j]));
		puts("");
	}
}
```

---

## 作者：Wen_kr (赞：3)

#### 30 Pts

把两两字符串拖出来跑 dp，时间复杂度 $O(n^3)$。

#### 60 Pts

考虑使用后缀自动机，因为毒瘤出题人卡内存，只有 60 Pts.

#### 100 Pts

考虑把所有串连在一起，在中间加入分割符，使用后缀数组处理出 `height` 数组。

接着我们考虑设 $ans[i][j]$ 表示 第 $i$ 个串和第 $j$ 个串的最长公共字串。

设 pre[i] 表示从上一个属于第 i 个串的字符开头的 **后缀** 到当前位置的 height 数组的最小值，容易看出， pre[i] 就是从字符串 i 到当前后缀头字符所属的字符串的 lcp 长度

我们考虑按照 rank 从小到大枚举，对于一个后缀 p ，若它属于字符串 $i$ ，我们用 $pre[j]$ 更新 $ans[i][j] 和 ans[j][i]$，最后输出答案即可。

时间复杂度 $O(n * \sum len)$

---

## 作者：StarsIntoSea_SY (赞：2)

# Solution

SA 好题。

先按照板子求出 $sa$ 数组 和 $height$ 数组。

$height$ 数组有一个显而易见的性质，即第 $i$ 名后缀与第 $j$ 名后缀的 LCP 为：
$$
\min_{t=i+1}^{j}{height[t]}
$$
其中 $i<j$。

本题求每个串的最长公共子串，可以把所有串放在一起跑 SA。我们先用一个数组 $d$ 表示第 $i$ 个后缀所属串。那么任意两个串的最长公共子串显然为**两个串的所有后缀的 LCP 的最大值。**

因为卡空间，所以不能用 st 表，开一个数组维护枚举时所属串的最值即可。

时间复杂度 $O(m \log_{2} m+nm)$，$n$ 为字符串的数量，$m$ 表示所有字符串的长度。

# Code


```cpp
#include <iostream>
#include <string.h>
const int N=2e6+5;
char s[N];
int x[N],y[N],c[N],sa[N],d[N],rk[N],height[N],n,m;
int w[55],ans[55][55];
void get_sa(){
	for(int i=1;i<=n;++i) c[x[i]=s[i]]++;
	for(int i=1;i<=m;++i) c[i]+=c[i-1];
	for(int i=n;i;i--) sa[c[x[i]]--]=i;
	for(int t=1;t<=n;t<<=1){
		memset(c,0,sizeof c);
		for(int i=1;i<=n;++i) y[i]=sa[i];
		for(int i=1;i<=n;++i) c[x[y[i]+t]]++;
		for(int i=1;i<=m;++i) c[i]+=c[i-1];
		for(int i=n;i;i--) sa[c[x[y[i]+t]]--]=y[i];
		memset(c,0,sizeof c);
		for(int i=1;i<=n;++i) y[i]=sa[i];
		for(int i=1;i<=n;++i) c[x[y[i]]]++;
		for(int i=1;i<=m;++i) c[i]+=c[i-1];
		for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i];
		m=0;
		for(int i=1;i<=n;++i) y[i]=x[i];
		for(int i=1;i<=n;++i){
			if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+t]==y[sa[i-1]+t])
				x[sa[i]]=m;
			else x[sa[i]]=++m;
		}
		if(m==n) return ;
	}
}
void get_rk(){
	for(int i=1;i<=n;++i) rk[sa[i]]=i;
	for(int i=1,k=0;i<=n;++i){
		if(rk[i]==1) continue;
		if(k) k--;
		int j=sa[rk[i]-1];
		while(i+k<=n && j+k<=n && s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}
}
int main(){
	int p;scanf("%d",&p);
	n=0;
	for(int i=1;i<=p;++i){
		char t[N];
		scanf("%s",t+1);
		int k=strlen(t+1);
		for(int j=1;j<=k;++j) s[++n]=t[j],d[n]=i;
		s[++n]=(char)i;
	}
	m=150;
	get_sa();
	get_rk();
	memset(w,0x7f,sizeof w);
	for(int i=2;i<=n;++i){
		for(int j=1;j<=p;++j) w[j]=std::min(w[j],height[i]);
		w[d[sa[i-1]]]=height[i];
		int now=d[sa[i]];
		for(int j=1;j<=p;++j) ans[now][j]=ans[j][now]=std::max(ans[now][j],w[j]); 
	}
	for(int i=1;i<=p;++i,printf("\n"))
		for(int j=1;j<=p;++j) if(i!=j) printf("%d ",ans[i][j]);
}
```

---

## 作者：朝夕晨曦_L (赞：1)

[P5028 Annihilate ](https://www.luogu.com.cn/problem/P5028)

首先揣摩一番，真不错，好一个卡空间，出题人真是心思细腻啊。

仔细一想，出题人远远没有你想象的那么简单，它不仅卡掉了后缀自动机，他甚至不让你用 ST 表。

多个串求后缀数组，一个一个建立显然不现实（超时大礼包），那么我们就全部拼接在一起，来一个大锅菜。

那么，前面偷懒了，统计答案可就没那么好过了。

我们遍历整个后缀数组，对于任意两串的最长公共前缀，我们必须要取目前遍历到的 $height$ 数组最小值；对于每次遍历到一个串的某个字符，要给当前串的最小长度数组重新赋极大值，因为接下来的操作与前一个该串元素所构成的后缀无关，只与新遍历到的该串元素构成的后缀有关；对于每两个串之间产生的答案，我们统一取最大值。

这样思路就了然了，见代码：

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 55 , Inf = 1e9;
int height[Len],id[Len],rk[Len],sa[Len],cnt[Len],px[Len],odrk[Len],p,ID[Len],lst[Len],Minn[55],Ans[55][55];
int n,m;
char s[Len],ss[Len];
bool cmp(int x,int y,int w){return odrk[x] == odrk[y] && odrk[x + w] == odrk[y + w];}
int main(){
    int x = 1;
    int T;
    scanf("%d",&T);
    for(int j = 1 ; j <= T ; j ++){
        scanf("%s",ss + 1);
        int lenss = strlen(ss + 1);
        for(int i = 1 ; i <= lenss ; i ++){
            s[++ n] = ss[i];//拼接
            ID[n] = j;
        }
        while('a' <= x && x <= 'z') x++;
        s[++ n] = char(x);
        x ++;
    }
    //sa
    m = max(300 , n);
    for(int i = 1 ; i <= n ; i ++) ++ cnt[rk[i] = s[i]];
    for(int i = 1 ; i <= m ; i ++) cnt[i] += cnt[i - 1];
    for(int i = n ; i >= 1 ; i --) sa[cnt[rk[i]] --] = i;
    for(int w = 1 ; ; w <<= 1 , m = p){
        p = 0;
        for(int i = n ; i > n - w ; i --) id[++ p] = i;
        for(int i = 1 ; i <= n ; i ++) if(sa[i] > w) id[++ p] = sa[i] - w;
        memset(cnt , 0 , sizeof cnt);
        for(int i = 1 ; i <= n ; i ++) ++ cnt[px[i] = rk[id[i]]];
        for(int i = 1 ; i <= m ; i ++) cnt[i] += cnt[i - 1];
        for(int i = n ; i >= 1 ; i --) sa[cnt[px[i]] --] = id[i];
        memcpy(odrk , rk , sizeof(rk));
        p = 0;
        for(int i = 1 ; i <= n ; i ++) rk[sa[i]] = cmp(sa[i - 1] , sa[i] , w) ? p : ++ p;
        if(p == n){
            for(int i = 1 ; i <= n ; i ++) rk[sa[i]] = i;
            break;
        }
    }  
    //lcp
    for(int i = 1 , len = 0 ; i <= n ; i ++){
        if(rk[i] == 1) continue;
        if(len) len --;
        while(s[i + len] == s[sa[rk[i] - 1] + len]) len ++;
        height[rk[i]] = len;
    }
    
    for(int i = 1 ; i <= T ; i ++) {
        Minn[i] = Inf;
        for(int j = 1 ; j <= T ; j ++) Ans[i][j] = 0;
    }//初始化
    for(int i = 1 ; i <= n ; i ++) {
        int irui = ID[sa[i]];
        if(irui){
            for(int j = 1 ; j <= T ; j ++){
                Minn[j] = min(Minn[j] , height[i]);
                if(Minn[j] == Inf || irui == j) continue;
                Ans[irui][j] = max(Ans[irui][j] , Minn[j]);
                Ans[j][irui] = Ans[irui][j];
            }
            Minn[irui] = Inf;
        }
    }
    for(int i = 1 ; i <= T ; i ++){
        for(int j = 1 ; j <= T ; j ++) if(i != j) printf("%d ",Ans[i][j]);
        puts("");
    }
    return 0;
}
```



---

## 作者：SoyTony (赞：1)

先思考如果只是求两个串该如何解决？

用分隔符分开，拼接求 $\text{SA}$ 后，在后缀排序的数组上，对排名相邻且来自两个不同串的位置，更新最终答案。

正确性在于，所有不相邻的 $\operatorname{lcp}$，一定会跨过相邻的 $\operatorname{lcp}$，即最终的贡献不大于相邻的 $\operatorname{lcp}$。

推广到多个串，不能只考虑相邻，如果去掉除这两个位置以外的后缀，实际上是求前驱后继。如果枚举两个后缀的来源并更新答案，复杂度是 $O(n|s|\log|s|)$，由于使用了 $\text{ST}$ 表，空间时间都不优秀。

尝试枚举其他的东西。

如果只钦定一个后缀的来源，将整个串的所有后缀都打上标记，那么对于其他后缀来说，自己对于整个串的答案贡献，就是与这些标记的位置中的前驱后继产生的。

因此可以直接正反扫一遍，维护一个最小值，表示上一个标记点到当前位置的 $\operatorname{lcp}$。这样可以做到 $O(|s|\log|s|+n|s|)$。

**分隔符应当两两不同**。

```cpp
int n,len;
char s[maxn],t[maxn];
int lpos[55],rpos[55],bel[maxn];
int sa[maxn],rk[maxn<<1],cnt[maxn],oldsa[maxn],oldrk[maxn<<1],tmp[maxn];
int height[maxn];
inline bool cmp(int x,int y,int l){
    return oldrk[x]==oldrk[y]&&oldrk[x+l]==oldrk[y+l];
}
inline void get_sa(){
    int siz=max(len,127);
    for(int i=1;i<=len;++i) ++cnt[rk[i]=s[i]];
    for(int i=1;i<=siz;++i) cnt[i]+=cnt[i-1];
    for(int i=len;i>=1;--i) sa[cnt[rk[i]]--]=i;
    for(int l=1,k;;l<<=1){
        k=0;
        for(int i=len;i+l>len;--i) oldsa[++k]=i;
        for(int i=1;i<=len;++i) if(sa[i]>l) oldsa[++k]=sa[i]-l;
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=len;++i) ++cnt[tmp[i]=rk[oldsa[i]]];
        for(int i=1;i<=siz;++i) cnt[i]+=cnt[i-1];
        for(int i=len;i>=1;--i) sa[cnt[tmp[i]]--]=oldsa[i];
        for(int i=1;i<=len;++i) oldrk[i]=rk[i];
        k=0;
        for(int i=1;i<=len;++i) rk[sa[i]]=cmp(sa[i],sa[i-1],l)?k:++k;
        if(k==len) break;
        siz=k;
    }
    for(int i=1,k=0;i<=len;++i){
        if(k) --k;
        while(s[i+k]==s[sa[rk[i]-1]+k]) ++k;
        height[rk[i]]=k;   
    }
}
int ans[55][55];
int main(){
    n=read();
    for(int i=1;i<=n;++i){
        scanf("%s",t+1);
        int l=strlen(t+1);
        lpos[i]=len+1,rpos[i]=len+l;
        for(int j=1;j<=l;++j) s[len+j]=t[j],bel[len+j]=i;
        len+=l;
        s[++len]='a'-i;
    }
    get_sa();
    for(int i=1;i<=n;++i){
        bool chk=0;
        int mn=inf;
        for(int j=1;j<=len;++j){
            if(bel[sa[j]]==i) chk=1,mn=inf;
            else if(chk){
                mn=min(mn,height[j]);
                ans[i][bel[sa[j]]]=max(ans[i][bel[sa[j]]],mn);
            }
        }
        chk=0;
        mn=inf;
        for(int j=len;j>=1;--j){
            if(bel[sa[j]]==i) chk=1,mn=inf;
            else if(chk){
                mn=min(mn,height[j+1]);
                ans[i][bel[sa[j]]]=max(ans[i][bel[sa[j]]],mn);
            }
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(i==j) continue;
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

SA 简单应用题。

先考虑对于任意两个串求公共子序列。即将两个串拼在一起中间加特殊字符，对每个位置标记属于第一个串还是第二个串，对于拼在一起的字符串后缀排序后每个位置与后面第一个非同串位置求 $lcp$ 后最长的 $lcp$ 即是答案。

考虑拓展做法。由于 $\sum_{i = 1} ^ n |S_i| \leq 10 ^ 6$，将 $n$ 个字符串拼在一起中间用特殊字符隔开，对 $n$ 种串的每种串都维护一个在后缀排序好的后缀中正着扫时最后一个出现的位置。

然后按照 $n = 2$ 时的做法，每次暴力更新，暴力维护答案即可。

时间复杂度 $O(n\sum |S|)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 55 , Inf = 1e9;
int ht[Len],n,m,id[Len],rk[Len],sa[Len],cnt[Len],px[Len],odrk[Len],p,ID[Len],lst[Len],Minn[55],Ans[55][55];
char s[Len],ss[Len];
bool cmp(int x,int y,int w){return odrk[x] == odrk[y] && odrk[x + w] == odrk[y + w];}
int main()
{
	int x = 1;
	int T;scanf("%d",&T);
	for(int j = 1 ; j <= T ; j ++)
	{
		scanf("%s",ss + 1);
		int lenss = strlen(ss + 1);
		for(int i = 1 ; i <= lenss ; i ++) 
		{
			s[++ n] = ss[i];
			ID[n] = j;
		}
		while('a' <= x && x <= 'z') x ++;
		s[++ n] = char(x);
		x ++;
	}
	m = max(300 , n);
	for(int i = 1 ; i <= n ; i ++) ++ cnt[rk[i] = s[i]];
	for(int i = 1 ; i <= m ; i ++) cnt[i] += cnt[i - 1];
	for(int i = n ; i >= 1 ; i --) sa[cnt[rk[i]] --] = i;
	for(int w = 1 ; ; w <<= 1 , m = p)
	{
		p = 0;
		for(int i = n ; i > n - w ; i --) id[++ p] = i;
		for(int i = 1 ; i <= n ; i ++) if(sa[i] > w) id[++ p] = sa[i] - w;
		memset(cnt , 0 , sizeof cnt);
		for(int i = 1 ; i <= n ; i ++) ++ cnt[px[i] = rk[id[i]]];
		for(int i = 1 ; i <= m ; i ++) cnt[i] += cnt[i - 1];
		for(int i = n ; i >= 1 ; i --) sa[cnt[px[i]] --] = id[i];
		memcpy(odrk , rk , sizeof(rk));
		p = 0;
		for(int i = 1 ; i <= n ; i ++) rk[sa[i]] = cmp(sa[i - 1] , sa[i] , w) ? p : ++ p;
		if(p == n)
		{
			for(int i = 1 ; i <= n ; i ++) rk[sa[i]] = i;
			break;
		}
	}  
	for(int i = 1 , len = 0 ; i <= n ; i ++)
	{
		if(rk[i] == 1) continue;
		if(len) len --;
		while(s[i + len] == s[sa[rk[i] - 1] + len]) len ++;
		ht[rk[i]] = len;
	}
	//for(int i = 1 ; i <= n ; i ++) printf("%d %d %d %d %d\n",i,ht[i],rk[i],sa[i],ID[sa[i]]);
	for(int i = 1 ; i <= T ; i ++) 
	{
		Minn[i] = Inf;
		for(int j = 1 ; j <= T ; j ++) Ans[i][j] = 0;
	}
	for(int i = 1 ; i <= n ; i ++) 
	{
		int bel = ID[sa[i]];
		if(bel)
		{
			for(int j = 1 ; j <= T ; j ++)
			{
				Minn[j] = min(Minn[j] , ht[i]);
				if(Minn[j] == Inf || bel == j) continue;
				Ans[bel][j] = max(Ans[bel][j] , Minn[j]);
				Ans[j][bel] = Ans[bel][j];
			}
		}
		if(bel) Minn[bel] = Inf;
	}
	for(int i = 1 ; i <= T ; i ++)
	{
		for(int j = 1 ; j <= T ; j ++) if(i != j) printf("%d ",Ans[i][j]);
		puts("");
	}
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

## 简要题意

给定 $n$ 个字符串 $s_1 \sim s_n$。求两两之间的最长公共子串。

## 题目分析

考虑到后缀的前缀就是子串，所以用后缀数组来搞。首先将所有字符串用分隔符分开后拼起来，然后跑一边后缀数组。由于排名相邻的两个后缀的 $\mathrm{LCP}$ 具有极大性，所以两个排名为 $i, j$ 的后缀的最长公共前缀就是 $\min \limits_{k = i}^{j - 1} \{ \mathrm{LCP(k, k + 1)}\}$。

这样可以搞个 ST 表跑，但是~~丧心病狂~~精益求精的出题人卡了空间。所以考虑将每个后缀染色，染色值即为它的第一个字符原本属于那个字符串。然后对于每个后缀 $i$，存储排名在它前面的与它最近的所有颜色的后缀 $j$ 与它的段 $\mathrm{LCP}$（即 $\mathrm{LCP[j, i]}$）。然后从前往后扫的时候暴力更新即可。

若记所有字符串的总长度为 $|S|$，这样的时间复杂度就是 $O(|S| \log |S| + n |S|)$，空间复杂度为 $O(|S| + n)$。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )
#define per(i, a, b) for (int i = (a); i >= (b); i -- )

using namespace std;

const int N = 60;
const int L = 1000010;
const int INF = 2e9;

int n, c[L + N];
int f[N][N], minn[N];
char s[L], block = 0;
char S[L + N];

namespace SA {
	int ls, sz, tt, hs[L + N], hr[L + N];
	int tp[L + N], rk[L + N], sa[L + N], bin[L + N];
	void build(char *s) {
		ls = strlen(s + 1);
		sz = max(ls, 255);
		rep(i, 1, sz) bin[i] = 0;
		rep(i, 1, ls) bin[rk[i] = s[i]] ++ ;
		rep(i, 1, sz) bin[i] += bin[i - 1];
		per(i, ls, 1) sa[bin[rk[i]] -- ] = i;
		
		for (int j = 1; j <= ls; j <<= 1, tt = 0) {
			rep(i, ls - j + 1, ls) tp[ ++ tt] = i;
			rep(i, 1, ls) if (sa[i] > j) tp[ ++ tt] = sa[i] - j;
			rep(i, 1, sz) bin[i] = 0;
			rep(i, 1, ls) bin[rk[i]] ++ ;
			rep(i, 1, sz) bin[i] += bin[i - 1];
			per(i, ls, 1) sa[bin[rk[tp[i]]] -- ] = tp[i];
			swap(rk, tp); rk[sa[1]] = 1;
			rep(i, 2, ls) {
				int x = (tp[sa[i]] != tp[sa[i - 1]]);
				x |= (tp[sa[i] + j] != tp[sa[i - 1] + j]);
				rk[sa[i]] = rk[sa[i - 1]] + x;
			}
			if (rk[sa[ls]] == ls) break;
			sz = rk[sa[ls]];
		}
		rep(i, 1, ls) {
			hs[i] = max(hs[i - 1] - 1, 0);
			while (s[i + hs[i]] == s[sa[rk[i] - 1] + hs[i]]) hs[i] ++ ;
			hr[rk[i]] = hs[i];
		}
	}
}
#define build SA::build
#define sa SA::sa
#define rk SA::rk
#define hr SA::hr

int get_min(int l, int r) {
	int ans = INF;
	rep(i, l, r) ans = min(ans, hr[i]);
	return ans;
}
int main() {
	scanf("%d", &n); int ls = 0;
	rep(i, 1, n) {
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		rep(j, 1, len)
		S[ ++ ls] = s[j], c[ls] = i;
		S[ ++ ls] = ++ block;
	}
	build(S);
	memset(f, -0x3f, sizeof f);
	memset(minn, 0x3f, sizeof minn);
	rep(i, 1, ls) {
		if (!c[sa[i]]) continue;
		rep(j, 1, n) {
			if (j == c[sa[i]]) continue;
			minn[j] = min(minn[j], hr[i]);
			f[c[sa[i]]][j] = f[j][c[sa[i]]] = max(f[c[sa[i]]][j], minn[j]);
		}
		minn[c[sa[i]]] = INF;
	}
	for (int i = 1; i <= n; i ++ , puts(""))
		for (int j = 1; j <= n; j ++ )
			if (i != j)
				printf("%d ", f[i][j]);
	return 0;
}
```

个人认为自己的后缀数组板子很好看。

---

