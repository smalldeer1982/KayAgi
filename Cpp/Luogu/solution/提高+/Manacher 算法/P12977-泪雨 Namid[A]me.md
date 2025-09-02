# 泪雨 Namid[A]me

## 题目背景

> 涙目 変わらずの雨模様\
泪眼不变的烟雨迷蒙\
その夢の淵ギリギリで\
在那梦的深渊倾盆而下\
—— ヒトリエ《Namid[A]me》

最终，只剩我一人了。

## 题目描述

给定小写英文字母和 ```?``` 组成的字符串 $s$。

“泪雨”定义为这样的串：这是一个回文串，并且 ```?``` 的个数大于等于小写英文字符的个数。

请对于是“泪雨”的 $s$ 的所有子串，求出它们问号位置的和之和。（位置下标从 $1$ 开始）

**形式化题意**：定义：
$$
f(l,r)=
\sum_{i=l}^{r} [s_i=\texttt{?}]\cdot i
\\
g(l,r)=\big[\sum_{i=l}^r{[s_i=\texttt{?}] \geq} \frac{r-l+1}{2}\big]\big[ s[l,r]\text{ is a palindrome} \big]
$$

请你求出 $\sum_{l=1}^{n} \sum_{r=l}^{n} g(l,r)\cdot f(l,r)$，其中 $n=\lvert s\rvert$。

## 说明/提示

**样例解释：** 样例 $1$ 中，$[2,2],[3,3],[1,4],[2,3]$ 都是符合要求的回文串，并且所求的问号位置之和为 $2+3+(2+3)+(2+3)=15$。

以下是数据范围。

| Subtask | $n$ | 特殊性质 | 分值 | 子任务依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leq 500$ | 无 | $10$ | - |
| $2$ | $\leq 7000$ | 无 | $15$ | $1$ |
| $3$ | $\leq 2\times 10^6$ | $s$ 中仅有 ```?``` | $5$ | - |
| $4$ | $\leq 2\times 10^6$ | 字符串随机生成 | $10$ | $1$ |
| $5$ | $\leq 2\times 10^6$ | $s$ 中有且仅有两种字符 | $10$ | - |
| $6$ | $\leq 3\times 10^5$ | 无 | $15$ | $1,2$ |
| $7$ | $\leq2\times 10^6$ | 无 | $15$ | $1\sim 6$ |
| $8$ | $\leq 5\times10^6$ | $\text{timelimit}=1.5s$ | $20$ | $1\sim 7$ |

对于 $100\%$ 的数据满足 $1\leq n\leq 5\times 10^6$，且 $s$ 仅包含小写英文字母和 ```?```。

除了 $\text{subtask 8}$ 之外，时限皆为 $1s$。

时间限制已开到了 std 的 2 倍以上，空间限制开到了 std 的 1.25 倍以上，但仍需 **注意程序的运行时空常数**。

## 样例 #1

### 输入

```
4
a??a```

### 输出

```
15
```

## 样例 #2

### 输入

```
10
?a?aa?a?a?```

### 输出

```
115```

# 题解

## 作者：bluedream (赞：8)

无需其它数据结构的辅助，对 Manacher 算法进行朴素地收缩的复杂度即为正确的。
****
对于本题很容易想到直接使用 Manacher 算法，维护当前回文半径内的问号数量，并在拓展时动态维护所有合法串的问号数量和。

令 $l_i$ 为以 $i$ 为回文中心的最长回文半径。主要问题为，Manacher 算法的流程需要把 $l_i$ 初始化为 $\min(l_{2mid-i},r-i)$，其中 $r,mid$ 分别为目前回文串右端点的最大值与对应的回文中心，**如果有多个回文中心取到同样的右端点，$mid$ 取其中最大的**。此时如果 $l_{2mid-i}>r-i$，我们无法直接得到收缩至 $r-i$ 的信息。

考虑直接暴力收缩，事实上这样的复杂度是正确的。考虑如果 $l_{2mid-i}>r-i$，那么 $(i,i+l_i)$ 必定会更新 $(mid,r)$，每次收缩都会带来 $2(r-mid)$ 至少减 $1$，同时每次扩张都最多让 $2(r-mid)$ 增加 $2$。由于 Manacher 算法流程最多扩张 $O(n)$ 次，故收缩次数也同样为 $O(n)$ 的。

时间复杂度 $O(n)$。

参考代码：

```cpp
const int N=1e7+10;
int n,m,rp[N],cur[N];
ll sum[N];
lll ans;
char s[N];
inline int len(int l,int r){ return (r+1>>1)-(l>>1); }
int main(){
	n=read();
	s[0]='~';
	for(int i=1;i<=n;i++)
		s[i*2-1]=getc(),s[i*2]='|';
	n*=2;
	for(int i=1,r=0,mid;i<=n;i++){
		if(r>=i){
			int p=mid*2-i;
			rp[i]=rp[p],cur[i]=cur[p],sum[i]=sum[p];
			while(rp[i]>r-i){
				if(cur[i]*2>=len(p-rp[i],p+rp[i])&&s[p+rp[i]]!='|') sum[i]-=cur[i];
				cur[i]-=(s[p+rp[i]]=='?')*2,rp[i]--;
			}
		}else{
			if(s[i]=='?') cur[i]=sum[i]=1;
		}
		while(s[i-rp[i]-1]==s[i+rp[i]+1]){
			rp[i]++,cur[i]+=(s[i+rp[i]]=='?')*2;
			if(cur[i]*2>=len(i-rp[i],i+rp[i])&&s[i+rp[i]]!='|') sum[i]+=cur[i];
		}
		ans+=(lll)sum[i]*(i+1)/2;
		if(i+rp[i]>=r) r=i+rp[i],mid=i;
	}
	write(ans);
	flush();
}
```

---

## 作者：xuanxuan001 (赞：2)

奇妙简单做法，感觉是线性但不会严谨证，欢迎大佬给出证明或 hack。最慢点 <190ms，目前仅次于 AI 的回文树，但为啥我的提交记录上的时间是某个神秘算法算出来的啊，既不是总时间也不是最慢点也不是最慢 subtask，为什么出题人的提交就是最慢时间啊。

首先观察数据范围和时限发现这题应该要线性。所以考虑 manacher，但好像还需要维护一个前缀信息，发现有些问题，考虑回文自动机，查阅曾经代码后发现~~已经忘光了~~并不是很可行，这个带 $|\Sigma|$ 的常数的空间约等于带了个 $\log$，搞一些哈希表什么的压空间显然也不是很优雅，时间常数也会很大。

那么考虑这个前缀信息发现其实只需要对从回文中心出发的某个方向的子串统计即可，需要找到所有问号不少于一半的前缀，那么它所对应的这个回文子串对答案的贡献实际上就是去区间里的问号个数乘中心位置下标，因为问号的位置和由于回文跟另一边的取平均刚好是中心位置，后文中认为需要求的就是问号个数之和。

所以记录传统的以某个位置为中心的回文串长度的同时也记录现在这个前缀的问号减非问号数量以及现在的所有合法前缀的答案和，那么在拓展的过程中可以同时更新这些东西。

遇到的问题就是 manacher 算法在继承值的时候可能会砍断，那么在这个时候直接暴力一个个回退前缀直到符合长度限制。具体怎么证明这里的回退次数为线性我还没想到，当时这么想主要是感性理解这个过程和在回文树上 dfs 的过程类似，可能可以通过与它的对应证明。

实现的时候我为了不用分讨两类回文串的情况（主要是奇数的还得讨论中间那个是不是问号，感觉有些烦）就直接将每个字符变成两个拼成一个长度为 $2n$ 的串，这样就只需要考虑长度为偶数的回文串，会简单很多。

核心代码：

```
//man为最长长度，nm为当前所有合法前缀的贡献和，sm为当前前缀和
//r为上一个最长回文子串的中心，记录在中心的后面一个位置上
if(r+man[r]>i){
	man[i]=man[(r<<1)-i];nm[i]=nm[(r<<1)-i];sm[i]=sm[(r<<1)-i];//从对称位置继承
	while(i+man[i]>r+man[r]){//超出这个回文串的一个个退掉
		--man[i];if(!(1&(i^man[i]))&&sm[i]>=0)nm[i]-=(man[i]+1+sm[i]>>1);
		if(s[(r<<1)-i+man[i]]=='?')--sm[i];else ++sm[i];
		//不难发现这里其实是下面的逆运算，注意这里的下标还要按对称过去的位置来，因为是在那里拓展的
	}
}for(;i>man[i]+1&&i+man[i]<=n&&s[i-man[i]-1]==s[i+man[i]];++man[i]){
	if(s[i+man[i]]=='?')++sm[i];else --sm[i];
	if(!(1&(i^man[i]))&&sm[i]>=0)nm[i]+=(man[i]+1+sm[i]>>1);
}ans+=(__int128)nm[i]*i;if(r+man[r]<i+man[i])r=i;
```

---

## 作者：SnowTrace (赞：2)

小常数好写好调做法，完全没卡常的最大点 250ms。

很容易发现求问号的位置的标号和实际上在骗哥们，因为回文串左半部分和右半部分相等，因此两边会互相抵消，如果枚举了回文中心就相当于只需要求问号的个数的和。

首先考虑如何刻画这个要求问号出现次数比其他字符出现次数多的限制，设 $pre_{1,i}$ 表示 $[1,i]$ 前缀中问号的个数，$pre_{2,i}$ 表示前缀中其他非问号字符的个数，限制相当于 $pre_{1,r}-pre_{1,l}\geq pre_{2,r}-pre_{2,l}$，移项后是二维偏序的形式，$pre_{1,r}-pre_{2,r}\geq pre_{1,l}-pre_{2,l}$。

然后考虑回文串的统计手法，我们尝试固定一个回文中心来统计，由于回文串前半段和后半段相等，因此我们不妨只关心后半段是否满足条件，也就是我们枚举回文中心 $i$，每个点有个回文半径 $p_i$，我们要求的就是左端点是 $i+1$，右端点在 $[i,i+p_i-1]$ 的子串（可以是空串）中有多少是合法的，以及它们串中问号个数的总和。

如果 $p_i$ 是一个随便给定的数组肯定不太好做，但是这里 $p_i$ 是回文半径，因此肯定存在一些性质。字符串题利用性质太难了，所以尝试直接魔改求回文半径的算法。

在 manacher 算法中，我们需要维护一个目前右端点最远的回文子串，设为 $[l,r]$，从前往后遍历 $i$，先在 $[l,r]$ 区间内找到 $i$ 的对称点，沿用这个对称点的信息，然后再尝试往外拓展，此时一次拓展会导致右端点（维护的那个 $r$）增加 1，因此这个算法是线性的。

在运行 manacher 算法的过程中进行讨论：

设 $i$ 在 $[l,r]$ 内的对称点是 $i'$，如果 $p_{i'}<r-i+1$，这意味着 $p_i = p_{i'}$，那么 $i$ 点直接继承 $i'$ 点的信息即可。

否则，以 $i$ 为中心的最长回文串的右端点一定 $\geq r$，我们需要求的就是左端点是 $i+1$，右端点在 $[i,r]$ 区间内的满足条件的串的信息。

这是很容易维护的，因为 $r$ 只增不减，$r$ 自增 1 时往数据结构里插入 $r$，在我们维护的数据结构上查询即可。

用树状数组维护，时间复杂度 $O(n\log n)$，但是很显然这个过不去 $n = 5\times10^6$。

设 $x_i = pre_{1,i}-pre_{2,i}$，则子串 $[l+1,r]$ 满足条件的要求是 $x_r\geq x_l$，但是注意到 $|x_i-x_{i-1}| \leq 1$，这说明每次我们查询（查询是后缀和）的位置距离差不超过 1，树状数组是不必要的，只需要写个移动指针的结构维护即可，复杂度线性。

感觉讲的挺抽象，建议配合代码理解。


```cpp
/*
魔改 manacher 算法。
*/
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&(-x))
int cnt[10000005],pre[10000005],pre1[10000005],pi[10000005];
#define int long long
const int X = 5000001;
int n,m;
int sum[10000005],cc[10000005];
int l,r;//最长回文串
int L = 10000002,SUM = 0,SUMC = 0;
//莫队维护查询个数
char t[5000005],s[10000005];
void add(int pos){
	sum[pre[pos]+X] += pre1[pos];
	cnt[pre[pos]+X]++;
	if(pre[pos]+X>=L)SUM += pre1[pos],SUMC++;
}
void del(int pos){
	sum[pre[pos]+X] -= pre1[pos];
	cnt[pre[pos]+X]--;
	if(pre[pos]+X>=L)SUM -= pre1[pos],SUMC--;
}
void find(int p){
	while(L>p)--L,SUM+=sum[L],SUMC+=cnt[L];
	while(L<p)SUM-=sum[L],SUMC-=cnt[L],++L;
}
void work(){
	//维护 [i,r] 的点值
	for(int i = 1;i<=m;i++){
		if(s[i] == '#')pre[i] = pre[i-1],pre1[i] = pre1[i-1];
		else{
			if(s[i]=='?')pre[i] = pre[i-1]+1,pre1[i] = pre1[i-1]+1;
			else pre[i] = pre[i-1]-1,pre1[i] = pre1[i-1];
		}
	}
	for(int i = 1;i<=m;i++){
		if(s[i] == '#')del(i-1);
		if(i<=r){
			pi[i] = min(r-i+1,(int)pi[l+r-i]);
			if(pi[l+r-i]<r-i+1){cc[i] = cc[l+r-i];continue;}
		}else{
			pi[i] = 1;
			if(s[i]!='#')add(i);
		}
		while(i-pi[i]>=1 and i+pi[i]<=m and s[i-pi[i]] == s[i+pi[i]]){
			if(s[i+pi[i]]!='#')add(i+pi[i]);
			++pi[i];
		}
		l = i-pi[i]+1,r = i+pi[i]-1;
		int need = pre[i]+X+(s[i]!='?' and s[i]!='#');
		find(need);
		cc[i] = SUMC*(s[i] == '?')+(SUM-SUMC*pre1[i])*2;
	}
}
signed main(){
//	freopen("T589768_2.in","r",stdin);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 1;i<=n;i++)cin >> t[i];
	m = 2*n-1;
	for(int i = 1;i<=n;i++)s[2*i-1] = t[i],s[2*i] = '#';
	work();
	__int128 ans =0 ;
	for(int i = 1;i<=m;i++){
		if(i%2 == 1){
			ans = (ans+(__int128)cc[i]*((i+1)/2));
		}else{
			ans = (ans+(__int128)cc[i]/2*(i+1));
		}
	}
	vector<int>p;
	while(ans)p.push_back(ans%10),ans/=10;
	for(int i=p.size()-1;i>=0;i--)cout << p[i];
	cout << endl;
	return 0;
}
```

---

## 作者：Comentropy (赞：2)

## 泪雨 solution

upd: 赛时疑似有人发现了常数大幅度优秀的算法。

### subtask 1&2

利用哈希和前缀和就可以做到 $O(n^2)$，具体说，你可以用 hash 来判断每个区间是不是回文的，利用前缀和可以快速求出其中问号的位置的和。

### subtask 3

这是一个简单的数学问题，因为任意一个区间都是一个回文串。（计算每个问号被覆盖多少次即可）
$$
\sum_{i=1}^{n}{i\cdot i(n-i+1)}
$$

### subtask 4

由于字符串随机生成，可以预见的是回文串的个数真的很少。所以我们直接枚举回文中心向外暴力扩展就行。大概有多少呢？一共有 $27$ 个字母，扩展一次就是左右两个字符相等。

于是总的期望扩展次数：

$$
T(n)=n\sum_{i} (\frac{1}{27})^i = O(n) 
$$

### subtask 5

其实和后面的 sub 几乎等强，有分析能力的人或许可以从里面看出点什么，提示了这道题较强数据的造法。

### subtask 6,7(solution from @GGapa)

给不精通字符串但是很强的人的部分分，或许足够优秀又可以直接 AC。

我们把区间 $[l,r]$ 看成一个点，那么我们遇到的有两个限制，以下假设枚举的是回文中心 $l$：

1. 问号个数 $\geq$ 确定字符个数，设前者的前缀和 $A$，后者前缀和 $B$，则 $A_r-A_l \geq B_r-B_l$，那么有 $A_r-B_r\geq A_l-B_l$。
2. $r-l+1\leq$ 回文半径。

于是转化成了类二维数点问题。按 $A_i-B_i$ 从大到小的顺序加入点（相同的要先加完再统计）。对于某个回文中心 $l$，假设其右端回文最远能到 $r$，那么，就统计 $[l,r]$ 内可能的右端点有多少个，以及对应的问号的前缀和的和，这样利用对称性就容易计算。需要注意奇偶长度的区别。

### Bonus 线性做法: subtask 8

#### 做法一 Tl.dr:

我们知道 Manacher 实际上是能够表示出所有的回文串的，以下是 Manacher 的模板代码。

```cpp
    for(int i=1,mid=0,lim=0;i<=idx;i++){
        if(i<=lim)
            p[i]=min(p[(mid<<1)-i],lim-i+1);
        while(s[i+p[i]]==s[i-p[i]])
            p[i]++;
        if(i+p[i]>lim)
            mid=i,lim=i+p[i]-1;
        if(p[i]-1>ans)
            ans=p[i]-1;
    }
```

在第一个 ```if``` 中，当前这一段如果没有被右边界截断，那么显然可以直接转移（如果我们知道了左边对称过来的串的权值）。

那么如果被右端截断了呢？

我们考虑每次扩展的时候，把当前这个回文串的 ```hash``` 值和其权值记录下来，并且将它丢到 ```hash_table``` 里。那么下次遇到某个被截断的串，直接在里面找就可以了。这样可以做到近乎 $O(n)$ 的时间。（可能查找的串的个数和向右扩展的次数一致，是 $O(n)$ 的）

因为各种概率和常数问题说实话并不优美，那我们能不能考虑去掉 ```hash``` 呢？

（甚至于这道题的 `hash` 表并没有跑得比带 $\log$ 的算法快，还慢了很多，不管是手写还是 ```gp_hash_table``` 都没啥用。）

#### 做法二 正解：

如果能够快速处理所谓被切断的部分就好了。实际是简单的，把 Manacher 所有的转移化成一棵树，然后在树上 dfs，每次向下搜索将扩展了长度的回文串的对应答案更新即可，回来的时候回溯就行，时间复杂度和扩展次数同级别，仍然是 $O(n)$ 的。这样就不使用 hash 地做完了这道题。

一个更好的总结是：由于本质不同回文串只有 $O(n)$ 种，把 Manacher 过程建操作树就好了。这一点其实在我们使用 hash 做法的时候就能看出。

但是！你发现普通深搜根本跑不过去，手动把递归展开会有点卡常。这要求你发现一些不错的遍历方法。这里是一种：

首先是这棵树结点的父亲有 $fa_i<i$，于是正着遍历过去就是拓扑序，你可以使用如下方法递推出 dfs 序：

1. 统计出每个子树的大小 $s_i$；
2. 这一步类似计数排序。按拓扑序遍历（就是正着），遍历到一个点的时候，继承下当前父亲的大小数组的值，即 $s_i\leftarrow s_{fa_i}$，然后把当前子树从父亲里摘掉。
3. 最后 $s_i$ 就是其 dfs 序。

以下代码用 `dfn[i]`，表示 dfs 序为 $i$ 的点。

```cpp
  fill(siz+1,siz+1+len,1);
  for(int i=len;i>=1;i--)
      siz[fa[i]]+=siz[i];
  for(int i=1,t;i<=len;i++)
      t=siz[i],siz[i]=siz[fa[i]],siz[fa[i]]-=t;
  for(int i=1;i<=len;i++)
      dfn[siz[i]]=i;
```

[Code Link](https://www.luogu.com.cn/paste/vgme5y5p).

本来部分树状数组代码常数太小了就没卡掉。又怕被说太卡常，就把时间开大了点，标程最慢点大概 600ms。

（其实原因是，当时造数据的时候，我还没办法往洛谷传比较多的数据。并且再开大数据感觉空间常数就撑不住了，就没必要了。）

大概感受了一下，疑似有诸如 PAM 或者 SA 加上一坨东西的做法。如果有的话，欢迎分享。

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

宣扬一波 PAM 邪教。经过不懈努力终于把空间 [卡进去了](https://www.luogu.com.cn/record/221821227)，可喜可贺。~~唯一的缺点是场上没有调出来。~~

一个比较重要的性质就是如果你知道一个串长什么样子，或者说你知道了它的问号的分布情况，那么在知道它最后一位的位置 $i$ 的情况下你可以直接计算出这一个子串的贡献。

建出 PAM，转移字符时只需要考虑新增的这一个字符对答案额外的贡献，也就是其 fail 指针的答案加上该回文串的答案。注意若该回文串不满足问号个数超过区间一半的性质仍然需要统计其 fail 指针的答案，只是不需要额外把当前串答案考虑在内而已。

考虑把一个子串的贡献记为 $kx+b$ 的形式。$k$ 表示总共存在多少个问号，$b$ 为需要减掉的常数，$x$ 为子串末尾编号。转移是简单的。额外记录 $cn_p$ 表示 $p$ 代表的回文串共有多少个问号。转移时先统计 fail 指针的答案再统计当前串答案。这里如果不理解怎么处理贡献可以参考下面的代码。

接下来就是 PAM 的板子没有什么好说的，每跳到一个位置这个回文串对应的 $k,b$ 都算出来了直接加就完事。

这一切写完之后你会惊奇地发现得到了 [80pts](https://www.luogu.com.cn/record/221820657)，原因是 PAM 的空间复杂度过大。

观察一下发现最慢的点也只跑了不到 200ms。由于 PAM 的转移数和节点数均为线性，启发我们以时间换空间做到空间的线性，做法很简单，用链式前向星存储 PAM 的每条边，转移时遍历该节点的每一条边找到对应字符的转移即可。一条边最多有字符集个转移，保证了时间复杂度的正确。

时间复杂度 $O(nV)$。$V$ 是字符集。空间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define lint __int128
// #define int long long
#define fi first
#define se second
#define Il inline
#define vec vector
#define pb push_back
#define IT ::iterator
#define p_q priority_queue

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef double db;
const int N=5e6,Inf=1e9;
const db eps=1e-9,pi=acos(-1.0);

mt19937 rnd(time(0));
Il int rint(int l,int r){return rnd()%(r-l+1)+l;}

Il void write(lint x){
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
    return;
}

int n,id=1,lk[N+5],le[N+5],cn[N+5];
int Id=0,hd[N+5],nx[N+5],vl[N+5],ed[N+5];//链式前向星
lint ans=0;
pair<lint,lint>va[N+5],Va[N+5];
//va 表示一个串造成的总贡献，Va 表示单论这一个串不考虑其 fail 指针造成的总贡献
string s;

Il int fai(int md,int p){while(p-le[md]-1<1||s[p-le[md]-1]!=s[p])md=lk[md];return md;}

Il void add(int x,int y,int c){Id++;ed[Id]=y,vl[Id]=c,nx[Id]=hd[x],hd[x]=Id;return;}//PAM 加边

Il int jmp(int p,int c){for(int i=hd[p];i;i=nx[i])if(vl[i]==c)return ed[i];return 0;}//找到 PAM 上对应的转移

signed main(){
    cin>>n>>s;s=" "+s;lk[0]=lk[1]=1,le[1]=-1;
    for(int i=1,p=0;i<=n;i++){
        int c=(s[i]=='?'?0:s[i]-'a'+1);p=fai(p,i);
        int t=jmp(p,c);
        if(!t){
            id++,lk[id]=jmp(fai(lk[p],i),c),le[id]=le[p]+2,add(p,id,c);
            cn[id]=cn[p]+(c?0:(p^1?2:1)),Va[id]={Va[p].fi,Va[p].se-cn[p]};//减去 cn[p] 的原因是所有问号都往前移了一位
            if(!c){
                if(p^1)Va[id].fi+=2ll,Va[id].se-=le[p]+1;//这里减去的是位置 i 对应过去的问号的编号
                else Va[id]={1,0};//此时为单个问号字符特殊处理
            }
            va[id]=va[lk[id]];//继承 fail 指针答案
            if((cn[id]<<1)>=le[id])va[id].fi+=Va[id].fi,va[id].se+=Va[id].se;//如果当前串合法才统计其贡献
        }
        p=jmp(p,c);ans+=va[p].fi*i+va[p].se;
    }
    write(ans);
    return 0;
}
/*
16
?aba?a?aaa??a?ab
134
*/
```

---

## 作者：KiDDOwithTopTree (赞：0)

[传送门](https://www.luogu.com.cn/problem/P12977)。

诡异 PAM 做法，成功跑到接近最劣解。

貌似找回文串然后找问号位置有点难，可以转化思路考虑统计每个 $i$ 总共出现几次。

代码总体分五段：

1. 正着做 PAM，构建 fail 树。
2. 遍历**回文树**，统计满足“```?``` 的个数大于等于小写英文字符的个数”的回文树节点。
3. 遍历 **fail 树**，统计有子串关系的满足“```?``` 的个数大于等于小写英文字符的个数”的总数。这样每个满足条件的回文串都必定会在结尾时统计一次。
4. 反着做一遍，将回文串的开头统计一遍。
5. $3. 4.$ 两步使用**差分**，就可以统计出 $i$ 出现几次。

最后，PAM 的空间爆炸，可以使用链式前向星，应该也可以使用 map，~~但是我并不会~~。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=5e6+10;
struct edge_node{
	int to;
	int val;
	int nxt;
};
struct edge{
	edge_node e[N];
	int head[N],tot;
	edge(){memset(head,-1,sizeof head);}
	inline void add(int from,int to,int val){
		e[tot].to=to;
		e[tot].val=val;
		e[tot].nxt=head[from];
		head[from]=tot++;
	}
	void clear(){
		memset(head,-1,sizeof head);
		tot=0;
	}
};
edge e,ch;
string s;
int a[N];
int fail[N],lth[N],tot=1;
int sum[N];
__int128 ans[N];
__int128 res;
bool bo[N];
void dfs1(int u){
	if(sum[u]*2>=lth[u]&&u>=2) bo[u]=true;
	for(int i=ch.head[u];~i;i=ch.e[i].nxt){
		int v=ch.e[i].to,w=ch.e[i].val;
		sum[v]=sum[u];
		if(w==26)
			if(u!=1) sum[v]+=2;
			else sum[v]++;
		dfs1(v);
	}
}
int dep[N];
void dfs2(int u){
	for(int i=e.head[u];~i;i=e.e[i].nxt){
		int v=e.e[i].to;
		dep[v]=dep[u]+bo[v];
		dfs2(v);
	}
}
int check(int u,int v){
	for(int i=ch.head[u];~i;i=ch.e[i].nxt)
		if(ch.e[i].val==v) return ch.e[i].to;
	return false;
}
int sta[N],top;
signed main(){
	int len;
	cin>>len>>s;
	for(int i=1;i<=len;i++)
		a[i]=(s[i-1]=='?'?26:s[i-1]-'a');
	a[0]=a[len+1]=-1;
	int last=0;
	fail[0]=1,fail[1]=0;
	lth[0]=0,lth[1]=-1;
	for(int i=1;i<=len;i++){
		while(a[i-lth[last]-1]!=a[i])
			last=fail[last];
		if(!check(last,a[i])){
			lth[++tot]=lth[last]+2;
			int j=fail[last];
			while(a[i-lth[j]-1]!=a[i])
				j=fail[j];
			fail[tot]=check(j,a[i]);
			ch.add(last,tot,a[i]);
		}
		last=check(last,a[i]);
	}
	dfs1(0),dfs1(1);
	for(int i=2;i<=tot;i++)
		e.add(fail[i],i,0);
	dfs2(0),dfs2(1);
	last=0;
	for(int i=1;i<=len;i++){
		while(a[i-lth[last]-1]!=a[i])
			last=fail[last];
		last=check(last,a[i]);
		ans[i+1]-=dep[last];
	}
	e.clear(),ch.clear();
	memset(bo,false,sizeof bo);
	tot=1,last=0;
	fail[0]=1,fail[1]=0;
	lth[0]=0,lth[1]=-1;
	for(int i=len;i>=1;i--){
		while(a[i+lth[last]+1]!=a[i])
			last=fail[last];
		if(!check(last,a[i])){
			lth[++tot]=lth[last]+2;
			int j=fail[last];
			while(a[i+lth[j]+1]!=a[i])
				j=fail[j];
			fail[tot]=check(j,a[i]);
			ch.add(last,tot,a[i]);
		}
		last=check(last,a[i]);
	}
	dfs1(0),dfs1(1);
	for(int i=2;i<=tot;i++)
		e.add(fail[i],i,0);
	dfs2(0),dfs2(1);
	last=0;
	for(int i=len;i>=1;i--){
		while(a[i+lth[last]+1]!=a[i])
			last=fail[last];
		last=check(last,a[i]);
		ans[i]+=dep[last];
	}
	for(__int128 i=1;i<=len;i++){
		ans[i]+=ans[i-1];
		if(a[i]==26) res=res+i*ans[i];
	}
	while(res){
		sta[++top]=res%10;
		res/=10;
	}
	if(!top) cout<<"0\n";
	while(top) cout<<sta[top--];
}
/*
5
?aaa?
*/
```

---

## 作者：zyn_ (赞：0)

首先当然可以求出所有回文子串。PAM 的空间是 $O(n|\Sigma|)$ 难以接受，因此考虑 Manacher。长度为奇数与长度为偶数的串是类似的，这里只讲长为偶数的回文子串的答案的求法。

对于位置 $i$ 设 $a_{(i-l_i+1)\dots (i+l_i)}$ 为回文串且 $l_i$ 最大。考虑首尾配对易知所有 `?` 的位置的平均值是 $i+0.5$，现在只需求出 $a_{(i-l_i+1)\dots i}$ 的所有 `?` 占至少一半的后缀中，`?` 的个数之和即可。

考虑令 $w_{n+1}=0$，$w_i=w_{i+1}+\Delta w_i$，其中若 $a_i$ 为 `?` 则 $\Delta w_i=1$，否则 $\Delta w_i=-1$。于是若 $w_{p+1}\ge w_{i+1}$ 则 $a_{(p+1)\dots i}$ 中 `?` 占至少一半。设 $a_{(p+1)\dots i}$ 中有 $x_p$ 个 `?`，则有 $i-p-x_p$ 个非 `?` 字符。由 $w_i$ 的定义可列方程 $w_{i+1}+x_p-(i-p-x_p)=w_{p+1}$，得 $x_p=\dfrac{w_{p+1}-w_{i+1}+i-p}{2}$。

现在要对每个 $i$ 求出满足 $p\ge i-l_i+1$，$w_{p+1}\ge w_{i+1}$ 的 $p$ 的 $x_p$ 之和。根据 $x_p$ 的表达式可知需要维护这些 $p$ 的个数与 $w_{p+1}-p$ 之和。按 $w_i$ 从大到小加入，可以用树状数组维护这些值的区间和。这样的时间复杂度是 $O(n\log n)$。

实际实现时，树状数组的 $\log$ 常数小，但是对 $w_i$ 排序的 $\log$ 需要省去。可以使用计数排序，并且需要卡空间，精细实现可以通过。

[submit record](https://www.luogu.com.cn/record/221671286)

所以感觉这题难度不止蓝啊。

---

