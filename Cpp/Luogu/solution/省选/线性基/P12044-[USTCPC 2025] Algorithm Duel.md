# [USTCPC 2025] Algorithm Duel

## 题目背景

考虑到评测机性能差异，改为 1s 时限。USTCPC 时限为 3s。

## 题目描述

Algorithm Duel （在线算法题单挑）是大家非常喜欢的活动之一。而这样的团建活动称为  Algorithm Duel 团建活动（以下简称**团建活动**）。

社团群内共有 $n$ 位群友。克露丝卡尔酱从题库中挑选了 $m=3n-3$ 道题目，**每位群友都有至少其中的一些题没有做过**。①

一场**标准的团建活动**定义如下：对于 $m$ 道题目中的任意一道题目，有偶数位群友没有做过这道题目，这样他们能两两配对举行 Algorithm Duel。

克露丝卡尔酱很遗憾地发现无论从 $n$ 位群友挑选任何非空子集，都不能进行一场**标准的团建活动**。②

但是，她还是非常想举办一场 Algorithm Duel 团建活动，她作为活动负责人只能亲自加入该场活动。为了尽可能保证活动的公正性，她可以任意选择 $n\sim m-n+1$ 道题目给一位群友送分（即这些题目可以有奇数位位群友没有做过这道题目）。这样的活动称为**非标准的团建活动**。

好了，现在请帮助她决定应该邀请哪些群友参加这场活动能成为一场**非标准的团建活动**吧？应该能有解的，不是吗？

## 说明/提示

对于样例 $1$，邀请所有群友后，有题目 $1$ 和 $3$ 两道题目只有奇数个群友没有做过。$n=2$ 时，**非标准的团建活动**必须恰好 $2$ 道题目有奇数个群友没有做过，满足条件。

## 样例 #1

### 输入

```
2
011
110```

### 输出

```
2
1 2```

## 样例 #2

### 输入

```
4
110000000
001100000
000011000
000000111```

### 输出

```
2
3 4```

# 题解

## 作者：cyffff (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/P12044)
## 题意
给定 $n$ 个 $3n-3$ 维的 `01` 向量，保证它们线性无关。你需要选出其中一些向量，使得它们的异或结果中一的个数在 $[n,2n-2]$ 中。

$n\le 1000$。
## 题解
先将这些向量塞入线性基中，再将每个最高位位置消成只有一个向量包含其，则基内每个向量 $a_i$ 都有 $|a_i|\le 2n-2$。若存在 $|a_i|\ge n$ 则直接找到了一组解，否则有所有 $|a_i|\le n-1$。

初始令向量 $x=(0,\dots,0)$，依次将 $x$ 异或上 $a_i$，过程中必定存在一个时刻使得 $n\le |x|\le 2n-2$，原因如下：
- 最终有 $|x|\ge n$，这是因为 $n$ 个最高位都必定存在；
- 过程中 $|x|$ 单次增长不超过 $n-1$，这是因为 $|a_i|\le n-1$。

故第一次 $|x|\ge n$ 的时刻必有 $|x|\le 2n-2$。

使用 `bitset` 求解线性基，时间复杂度 $O\left(\dfrac{n^3}w\right)$。

---

## 作者：Purslane (赞：1)

# Solution

简单构造题。本题的意思是，从给定的 $n$ 个二进制串种选出若干个，使得他们的 popcount 在 $[n,2n-2]$ 之间。

首先想想题目的 2 条件是干啥用的。也就是进过线性基高斯消元之后，得到的基大小仍然为 $n$。

这样我们可以互相消元使得每一组基的大小都小于等于 $m-n+1 = 2n-2$。

如果有基的大小 $\ge n$，已经完成了目标。

否则，考虑取一个前缀异或起来。显然一次基的大小最多增加 $n-1$，所以不会出现从 $<n$ 直接跳到 $> 2n-2$ 的情况。而全部异或起来至少有 $n$ 个位置是 $1$，也就是肯定有一次从 $<n$ 跳到了 $\ge n$ 的位置。那么肯定会落在 $[n,2n-2]$ 内，完成构造。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e3+10;
int n,m;
bitset<MAXN> bs[MAXN],cs[MAXN];
void insert(bitset<MAXN> ab,bitset<MAXN> pp) {
	ffor(i,1,m) if(ab[i]) {
		if(!bs[i][i]) return bs[i]=ab,cs[i]=pp,void();
		ab^=bs[i],pp^=cs[i];	
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,m=3*n-3;
	ffor(i,1,n) {
		string S;
		cin>>S;
		bitset<MAXN> ab,pp;
		ab.reset(),pp.reset();
		ffor(j,1,m) if(S[j-1]=='1') ab[j]=1;
		pp[i]=1;
		insert(ab,pp);	
	}
	ffor(i,1,m) if(bs[i][i]) ffor(j,i+1,m) if(bs[j][j]&&bs[i][j]) bs[i]^=bs[j],cs[i]^=cs[j];
	ffor(i,1,m) if(bs[i].count()>=n) {
		vector<int> vc;
		ffor(j,1,m) if(cs[i][j]) vc.push_back(j);
		cout<<vc.size()<<'\n';
		for(auto id:vc) cout<<id<<' ';
		return 0;	
	}
	bitset<MAXN> emp,cc;
	emp.reset(),cc.reset();
	ffor(i,1,m) {
		emp^=bs[i],cc^=cs[i];
		if(emp.count()>=n&&emp.count()<=n+n-2) {
			vector<int> vc;
			ffor(j,1,m) if(cc[j]) vc.push_back(j);
			cout<<vc.size()<<'\n';
			for(auto id:vc) cout<<id<<' ';
			return 0;	
		}
	}
	return 0;
}
```

---

## 作者：VinstaG173 (赞：1)

神秘构造。

形式化题意：给定 $n$ 个 $\mathbb{F}_2^m$ 中的向量，其中 $m=3n-3$（即 $m$ 维的 $01$ 向量），保证整体线性无关，选出其中一部分向量使其异或和中 $1$ 的位数在 $[n,m-n+1]$ 之间。

首先我们容易想到求出线性基，设线性基中元素的最高位从大到小排序为 $h_1,\dots,h_n$，则接下来可以用高斯消元把 $i<j$ 的基的第 $h_j$ 位消成 $0$。在求基的过程中我们同时可以维护出基中的每个元素是由原序列中哪些向量求和得来的。

那么在这样的基中，第 $i$ 个元素的第 $h_j(j\neq i)$ 位均为 $0$，因此其 $1$ 的位数不超过 $m-n+1$。若存在一个元素中 $1$ 的位数不少于 $n$，直接取这个元素即可。否则所有元素中 $1$ 的位数均不超过 $n-1$，这时我们一个一个将基中元素加入答案中，由于基中所有元素求和后每个 $h_i$ 位上均为 $1$，至少有 $n$ 个，故总有一个时刻 $1$ 的位数第一次不少于 $n$，又由于这次加入的元素 $1$ 的位数不超过 $n-1$，而上一个时刻的答案 $1$ 的位数不超过 $n-1$，故此时答案 $1$ 的位数不超过 $n-1+n-1=m-n+1$，故这是一组满足要求的构造。

用 bitset 优化，时间复杂度 $O(\frac{n^3}w)$，空间复杂度 $O(n)$。

Code:
```cpp
int n,m,fl;
char c[3007];
int id[1003];
int vs[3007];
int ht[1003];
bitset<3007>s[1003];
bitset<3007>b[1003],res;
bitset<1003>v[1003],ans;
inline bool cmp(int x,int y){
	return ht[x]<ht[y];
}

inline void solve(){
	cin>>n;m=n*3-3;
	for(int i=1;i<=n;++i){
		cin>>c;id[i]=i;
		for(int j=0;j<m;++j)
			s[i][j]=c[j]^'0';
	}for(int i=1,t;i<=n;++i){
		b[i]=s[i];v[i][i]=1;
		t=b[i]._Find_first();
		while(vs[t])
			b[i]^=b[vs[t]],v[i]^=v[vs[t]],\
			t=b[i]._Find_first();
		vs[t]=i,ht[i]=t;
	}sort(id+1,id+n+1,cmp);
	for(int _i=2,i;_i<=n;++_i){
		i=id[_i];
		for(int _j=1,j;_j<_i;++_j){
			j=id[_j];
			if(!b[j][ht[i]])continue;
			b[j]^=b[i];v[j]^=v[i];
		}
	}fl=0;
	for(int i=1,t;i<=n;++i){
		t=b[i].count();
		if(t>=n&&t<=m-n+1){
			fl=1;res=b[i];ans=v[i];
			break;
		}
	}if(!fl){
		for(int _i=1,i,t;_i<=n;++_i){
			i=id[_i];if(res[ht[i]])continue;
			res^=b[i];ans^=v[i];
			t=res.count();
			if(t>=n&&t<=m-n+1)break;
		}
	}
	cout<<ans.count()<<"\n";
	for(int i=1;i<=n;++i)
		if(ans[i])cout<<i<<" ";
}
```

---

## 作者：ethan_zhou (赞：0)

宣传博客：[USTCPC25 F&K 题解](https://www.blog-e.top/p/%E9%A2%98%E8%A7%A3ustcpc25-fk%E9%A2%98%E8%A7%A3/)

这题是寒假想到的，USTCPC 赛前听说缺题，突然感觉可以出成妙妙构造题。但是当时事情有点多，因此题面和数据都是 @Grand_Dawn 写的，感谢（

如下是该题的一个等价转换：

### 命题

设 $n \ge 3(d - 1)$，且 $V \subset \mathbf{F}_2^n$ 是一个维度为 $d$ 的线性子空间。那么，存在一个向量 $\mathbf{x} \in V$，使得其 Hamming weight 满足：

$$
d \le |\mathbf{x}| \le n - d + 1.
$$


### 证明

取 $V$ 的一组行最简形式（保证主元对应的列消的只剩下一个 1，可以参考 [Menci 的写法](https://oi.men.ci/linear-basis-notes/)）下的线性基 $\mathbf{b}_1, \mathbf{b}_2, \ldots, \mathbf{b}_d$。因为每个基向量中至少有 $d-1$ 个 0，所以可以保证每个基向量的 Hamming weight 满足：

$$
|\mathbf{b}_i| \le n - (d - 1) = n - d + 1.
$$

接下来讨论两种情况：

#### 情况 1：

存在某个 $i$，使得 $|\mathbf{b}_i| \in [d, n - d + 1]$。此时，$\mathbf{b}_i$ 本身即满足结论。

#### 情况 2：

对于所有 $i$，都有 $|\mathbf{b}_i| \in [1, d - 1]$，即每个基向量的 Hamming weight 都小于 $d$。定义如下的前缀和向量：

$$
\mathbf{x}_k = \sum_{j = 1}^{k} \mathbf{b}_j, \quad 1 \le k \le d.
$$

由于每个 $\mathbf{b}_i$ 的 Hamming weight 小于 $d$，所以相邻两个前缀和向量之间的 Hamming weight 差满足：

$$
\left|\, |\mathbf{x}_k| - |\mathbf{x}_{k-1}| \,\right| \le |\mathbf{b}_k| < d.
$$

又因为基底是行最简的形式，可以保证 $\mathbf{x}_d$ 至少有 $d$ 个非零位，即：

$$
|\mathbf{x}_d| \ge d, \quad |\mathbf{x}_0| = 0.
$$

因此，由于 Hamming weight 从 $0$ 增加到至少 $d$，且每一步变化最多为 $d - 1$，根据离散中值定理，存在某个 $k \in [d]$，使得：

$$
|\mathbf{x}_k| \in [d, n - d + 1].
$$

所以存在一个满足条件的向量 $\mathbf{x} = \mathbf{x}_k \in V$，证毕。

### 算法

最终算法就呼之欲出了，先进行高斯消元，随后检查每个向量以及前缀异或和是否满足条件即可，复杂度 $O(\frac{n^3}{w})$。

---

