# [ARC050D] Suffix Concat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc050/tasks/arc050_d



# 题解

## 作者：strapplE (赞：0)

我去。这题咋紫。这不就是 [P1012](https://www.luogu.com.cn/problem/P1012) 翻版？

把字母当作数字，就是 P1012，其中有一个经典结论：我们把每个字符串 $S_i$ 排序，其中的偏序（实际是全序）关系是 $i \prec j\iff S_i+S_j<S_j+S_i$。

因为最优解相邻位置一定有偏序关系，所以我们只要证明这个关系也是全序即可。这个字母串 $S_i$ 不太好看，我们把它看成数字 $T_i$。则有：

$$S_i+S_j=T_ibase^{|S_j|}+T_j$$

$$S_j+S_i=T_jbase^{|S_i|}+T_i$$

化一化：

$$S_i+S_j<S_j+S_i\iff \dfrac{T_i}{base^{|S_i|}-1}<\dfrac{T_j}{base^{|S_j|}-1}$$

然后就是全序啦！

写个类似后缀排序的过程就好了，暴力排，判关系可以拿自己喜欢的做法（哈希或者 SA 均可）来判。

时间复杂度 $O(n\log n)$ 或 $O(n\log ^2n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100005];
long long mod=1ll*1000000009*1004535809;
long long mm[100005],bs[100005],mo=131313131;
int n,p[100005];
long long get(int l,int r){
	return (mm[r]-(__int128)mm[l-1]*bs[r-l+1])%mod;
}
long long suan(int x,int y,int k){
	if(k<=n-x+1)return get(x,x+k-1);
	return ((__int128)get(x,n)*bs[k-(n-x+1)]+get(y,y+k-(n-x+1)-1))%mod;
}
int query(int x,int y,int k){
	if(k<=n-x+1)return s[x+k-1];
	return s[y+k-(n-x+1)-1];
}
int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	bs[0]=1;
	for(int i=1;i<=n;++i){
		mm[i]=((__int128)mm[i-1]*mo+s[i])%mod;
		bs[i]=(__int128)bs[i-1]*mo%mod;
	}
	for(int i=1;i<=n;++i)p[i]=i;
	sort(p+1,p+n+1,[&](int x,int y){
		int L=1,R=n-x+1+n-y+1;
		while(L<=R){
			int mid=(L+R)>>1;
			if((suan(x,y,mid)-suan(y,x,mid))%mod==0)L=mid+1;
			else R=mid-1;
		}
		if(L>n-x+1+n-y+1)return false;
		return query(x,y,L)<query(y,x,L);
	});
	for(int i=1;i<=n;++i)printf("%d\n",p[i]);
	return 0;
}
```

---

## 作者：阿丑 (赞：0)

没搜到中文题解，故写一发。可能比 std 更加麻烦。

[题目传送门](/problem/AT_arc050_d)

#### 前置知识：

后缀数组。

#### 题意：

- 给定长为 $n$ 的字符串 $S$，将所有 $S$ 的后缀按任意顺序排列，并首尾相连，形成一个新字符串 $T$。求使 $T$ 字典序最小的排列方案并输出。
- $n\le10^5$。

#### 分析：

为了方便，我们记将字符串 $A,B$ 首位相接形成的新字符串为 $A+B$；用 $nA$ 来表示将 $n$ 个 $A$ 首尾相连形成的字符串；用 $A\le B$ 来表示 $A$ 的字典序不大于 $B$，用 $A>B$ 表示 $A$ 的字典序大于 $B$。

考虑暴力。记长度为 $i$ 的后缀为 $s_i$（注意，与题面的记号并不相同！），并记最终的排列 $s_{p_1},s_{p_2},\dots,s_{p_n}$，则对于 $\forall i\in[1,n)$，有 $s_{p_i}+s_{p_{i+1}}\le s_{p_{i+1}}+s_{p_i}$。证明可以考虑微扰，即，若存在 $i$ 使得该关系不成立，则我们交换 $p_i,p_{i+1}$，字典序一定会变小，与最终的排列最优矛盾。

并且，该关系具有传递性，即 $A+B\le B+A,\,B+C\le C+B\Rightarrow A+C\le C+A$。下面给出证明。如果会证可以跳到分隔线之后。

> 引理：$\forall a\in\mathbb N^+,\,A+B\le B+A\Leftrightarrow aA+B\le B+aA$。

考虑归纳。

当 $a=1$ 时，两条件完全相同。

当 $a>1$ 时，若命题对 $a-1$ 与 $1$ 成立，则有：
$$
A+B\le B+A
\Rightarrow
\begin{aligned}
&aA+B\\
=&A+(a-1)A+B\\
\le&A+B+(a-1)A\\
\le&B+A+(a-1)A\\
=&B+aA
\end{aligned}
$$
同理，$A+B>B+A\Rightarrow aA+B>B+aA$。即 $A+B\le B+A\Leftrightarrow aA+B\le B+aA$，命题得证。

同理，还有 $\forall b\in\mathbb Z^+,\,A+B\le B+A\Leftrightarrow A+bB\le bB+A$。即 $\forall a,b\in\mathbb Z^+,\,A+B\le B+A\Leftrightarrow aA+bB\le bB+aA$。

所以我们可以放缩适当的倍数使得 $A,B$ 长度相等，就可以直接比较大小。具体地，有：
$$
\begin{aligned}
&A+B\le B+A\\
\Rightarrow&|B||C|A+|A||C|B\le|A||C|B+|B||C|A\\
\Rightarrow&|B||C|A\le|A||C|B\\
&B+C\le C+B\\
\Rightarrow&|A||C|B\le|A||B|C\\
&|B||C|A\le |A||C|B\le|A||B|C\\
\Rightarrow&|B||C|A+|A||B|C\le|A||B|C+|B||C|A\\
\Rightarrow&A+C\le C+A
\end{aligned}
$$

---

传递性表明对最终的排列，$\forall i<j$，$s_{p_i}+s_{p_j}\le s_{p_j}+s_{p_i}$。故可以按照这个顺序排序，得到的串就是答案。

现在考虑对于两个后缀 $s_i,s_j\ (i<j)$，如何比较 $s_i+s_j$ 与 $s_j+s_i$。可以先求出 $s_i$ 与 $s_j$ 的 LCP，若 LCP 长度 $<i$，则直接比较 LCP 的后一个字符即可；否则，则需要比较 $s_i+s_j$ 的后 $j$ 位字符与 $s_j+s_i$ 的后 $j$ 位字符，即 $s_j$ 与 $s_{j-i}+s_i$。同理，再求出 $s_j$ 与 $s_{j-i}$ 的 LCP，若长度 $<j-i$ 直接比较，否则比较两者的后 $i$ 位，即 $s_i$ 与 $s_i$，无需比较了。

用 SA+ST 表求 LCP，一次比较 $\mathcal O(1)$，复杂度 $\mathcal O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i=l, _=r; i<=_; ++i)
using namespace std;
typedef long long ll;

const int mN=1e5+9, mD=18;

int n, ans[mN];
char s[mN];

int sa[mN], rk[mN*2], lcp[mN], lg[mN], st[mN][mD];
void init_sa(char *s, int n) {
	static int ork, oldrk[mN*2], id[mN], buc[mN];
	auto cmp=[](int i, int j, int w) {
		return oldrk[i]==oldrk[j] && oldrk[i+w]==oldrk[j+w];
	};
	rep(i, 1, n) ++buc[rk[i]=s[i]^96];
	rep(i, 1, ork=26) buc[i]+=buc[i-1];
	rep(i, 1, n) sa[buc[rk[i]]--]=i;
	for(int w=1, m; w<n; w<<=1) {
		rep(i, 1, m=w) id[i]=n-i+1;
		rep(i, 1, n) if(sa[i]>w) id[++m]=sa[i]-w;

		memset(buc, 0, (ork+1)*4);
		rep(i, 1, n) ++buc[rk[i]];
		rep(i, 1, ork) buc[i]+=buc[i-1];
		for(int i=n; i>=1; --i) sa[buc[rk[id[i]]]--]=id[i];

		ork=0, memcpy(oldrk, rk, sizeof oldrk);
		rep(i, 1, n) rk[sa[i]]=ork+=!cmp(sa[i], sa[i-1], w);
	}
	rep(i, 1, n) {
		int &j=lcp[rk[i]]=max(lcp[rk[i-1]]-1, 0);
		while(s[i+j]==s[sa[rk[i]+1]+j]) ++j;
	}
	lg[0]=-1;
	rep(i, 1, n) lg[i]=lg[i>>1]+1;
	rep(i, 1, n) st[i][0]=lcp[i];
	rep(d, 1, lg[n]) rep(i, 1, n-(1<<d)+1) {
		st[i][d]=min(st[i][d-1], st[i+(1<<d-1)][d-1]);
	}
}
inline int cal_lcp(int i, int j) {
	i=rk[i], j=rk[j];
	if(i>j) swap(i, j);
	int d=lg[j-i];
	return min(st[i][d], st[j-(1<<d)][d]);
}
inline int cmp_suf(int i, int j) { 
	const int lcp=cal_lcp(n-i+1, n-j+1);
	if(lcp==i || lcp==j) return 0;	//返回 0 表示两串相等
	return s[n-i+1+lcp]-s[n-j+1+lcp];	//返回正数表示 si>sj，负数表示 si<sj 
}
inline bool cmp(int i, int j) {
	int res=cmp_suf(i, j);
	if(res) return res<0;
	if(i<j) return cmp_suf(j, j-i)<0;
	else return cmp_suf(i-j, i)<0;
}


int main() {

	scanf("%d\n%s", &n, s+1);
	init_sa(s, n);
	rep(i, 1, n) ans[i]=i;
	sort(ans+1, ans+n+1, cmp);
	rep(i, 1, n) {
		printf("%d\n", n-ans[i]+1);
	}
	return 0;
}
```

---

