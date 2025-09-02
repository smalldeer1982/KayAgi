# [SEERC 2020] Codenames

## 题目描述

有 $q$ 个 $5 \times 5$ 的图表，给出每个点的颜色（只可能是 `r`、`b`、`n`、`x`），具体颜色分配为：$9$ 个 `r`，$8$ 个 `b`，$5$ 个 `n`，一个 `x`。

图表中每个点对应的字符始终确定，分别为：

```
abcde
fghij
klmno
pqrst
uvwxy
```

图表中某些颜色已经翻开来了（用其颜色的大写字母表示已显示），然后你需要从一个 $n$ 个字符串的列表内选择一个字符串 $w$ 和一个数字 $g$，按下述规则进行操作 $g$ 次。

- 如果当前 $w_i$ 字符代表的格子颜色已经被公示，不进行操作，令 $i \gets i + 1$。
- 否则，翻开 $w_i$ 代表的格子，如果 $w_i$ 的颜色为 `n`、`b` 或 `x`，就输了。然后再令 $i \gets i+1$。
- 当 $g$ 次操作完成或所有 `r` 色块都翻出来时结束操作。

你想要使得所有 `r` 色块都翻出来，求一组满足条件的 $w$ 与 $g$。

## 说明/提示

答案还可能是 `actor 4`，`zeta 2` 等。

## 样例 #1

### 输入

```
3
actor
cheat
zeta
1
rBBnR
NRnbB
nRRnR
NRxBr
nBRbB```

### 输出

```
actor 2```

# 题解

## 作者：DeepSeaSpray (赞：1)

不太理解题意的可以上 CodeForces 看原版英文题面：[Link](https://codeforces.com/gym/103102/problem/K) 。

上面也有英文原版题解。

首先我们直接令 $g = 9$ 即可，因为 `r` 最多只有 $9$ 个，而翻完就会自动停止。

接着我们考虑转化一下问题。

首先我们必须翻出所有的 `r`，并且不能翻出其他的小写字母，对于大写字母翻了也没事。

那么我们可以考虑转化成一个字符串匹配的问题。

对于输入的字符串，我们将它们的所有前缀（取前缀是因为可能翻到某一步就停止了）作为文本串。并将一个字母对应的位置设成 `1`，其余的设成 `0`，`z` 不做处理。

例如：`azcex` 对应 `1010100000000000000000010`。

对于输入的表格，我们将它们作为模式串。具体来说，`r` 对应 `1`，其余小写字母对应 `0`，大写字母对应通配符 `?`。

例如：`rnnnB rnBBb nrBrr RBBrR rxnnb` 对应：`1000?10??001?11???1?10000`。

我们的任务是对于每一个模式串找到与之匹配的文本串。

我们考虑这一件事情，设 $cnt_0$，$cnt_1$，$cnt_q$ 分别表示 模式串中为 `0`，`1`，`?` 的数量。

由于平均值原理：

$$
\min(cnt_0,cnt_1,cnt_q) \leq \frac{cnt_0+cnt_1+cnt_q}{3} = \frac{25}{3} \leq 9
$$

所以如果我们有分别与 $cnt_0$，$cnt_1$，$cnt_q$ 相关的算法，我们就可以在较优秀的时间复杂度内解决问题。

## 与 $cnt_q$ 相关

暴力枚举通配符的取值即可。实现上可以用枚举子集简单实现。

单词操作时间复杂度 $O(2^9)$。

## 与 $cnt_1$ 相关

我们考虑如何数出一个模式串的与之匹配的文本串。

对于通配符我们并不好处理，由于文本串实际上是二进制数，这启发我们使用高维前缀和，直接令通配符取值 `1`。

但是这样我们模式串中要求为 `1` 的位就无法达成限制，所以我们考虑容斥掉这一部分。

具体来说，我们把一些为 `1` 的位设成 `0`，设这样的位有 $t$ 个，那么容斥系数即为 $(-1)^t$。

容斥可以用枚举子集简单实现。

如果存在这样的文本串，我们还需要考虑如何求出这一个文本串。

我们对于每一个 `?` 先将其设为 `0` 计算对应文本串个数，如果存在，那么这一位填 `0`，否则这一位填 `1`。

这一部分可以用 Lowbit 简单实现。

单次操作时间复杂度 $O(18 \times 2^9)$

## 与 $cnt_0$ 相关

与 $cnt_1$ 的部分本质相同，各位可以自行思考，我将修改过的部分写在下面。

我们使用高维**后缀**和，直接令通配符取值 `0`。

容斥掉要求为 `0` 的部分。

我们把一些为 `0` 的位设成 `1`，设这样的位有 $t$ 个，那么容斥系数即为 $(-1)^t$。

如果存在这样的文本串，我们还需要考虑如何求出这一个文本串。

我们对于每一个 `?` 先将其设为 `1` 计算对应文本串个数，如果存在，那么这一位填 `1`，否则这一位填 `0`。

其中高维前缀和预处理时间复杂度是 $O(2^{25})$ 的，常数优秀，可以通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
const int maxm=30;
const int maxk=25;
const int maxs=1<<maxk;
int n,m;
char str[maxn+5][maxm+5];
int id[maxs+5];
int f[maxs+5],g[maxs+5];
int tmpq,tmp0,tmp1;
int cntq,cnt0,cnt1;
inline char Getch(){
	char ch=getchar();
	while(!(('a'<=ch&&ch<='z')||('A'<=ch&&ch<='Z')))
		ch=getchar();
	return ch;
}
inline int Lowbit(int x){return x&(-x);}
inline int Count0(){
	int res=0;
	for(int s=tmp0;;s=(s-1)&tmp0){
		if(__builtin_popcount(s)&1) res-=g[s|tmp1|tmpq];
		else res+=g[s|tmp1|tmpq];
		if(!s) break;
	}
	return res;
}
inline int Count1(){
	int res=0;
	for(int s=tmp1;;s=(s-1)&tmp1){
		if((cnt1-__builtin_popcount(s))&1) res-=f[s|tmpq];
		else res+=f[s|tmpq];
		if(!s) break;
	}
	return res;
}
signed main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	int len,tmp;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",str[i]);
		len=strlen(str[i]),tmp=0;
		for(int j=0;j<len;j++){
			if(str[i][j]!='z'){
				tmp|=1<<(str[i][j]-'a');
				id[tmp]=i;
				f[tmp]++,g[tmp]++;
			}
		}
	}
	for(int i=0;i<maxk;i++){
		for(int j=0;j<maxs;j++){
			if((j>>i)&1) f[j]+=f[j^(1<<i)];
			else g[j]+=g[j^(1<<i)];
		}
	}
	char ch;
	int res;
	scanf("%d",&m);
	while(m--){
		tmpq=tmp0=tmp1=0;
		cntq=cnt0=cnt1=0;
		for(int i=0;i<maxk;i++){
			ch=Getch();
			if('A'<=ch&&ch<='Z') tmpq|=1<<i,cntq++;
			else if(ch=='r') tmp1|=1<<i,cnt1++;
			else tmp0|=1<<i,cnt0++;
		}
		if(cnt0==min({cnt0,cnt1,cntq})){
			int s=tmpq;tmpq=0;
			if(Count0()){
				for(;s;s-=Lowbit(s)){
					tmpq+=Lowbit(s);
					if(!Count0()) tmpq-=Lowbit(s);
				}
				res=tmp1|tmpq;
			}
			else res=-1;
		}
		else if(cnt1==min({cnt0,cnt1,cntq})){
			int s=tmpq;
			if(Count1()){
				for(;s;s-=Lowbit(s)){
					tmpq-=Lowbit(s);
					if(!Count1()) tmpq+=Lowbit(s);
				}
				res=tmp1|tmpq;
			}
			else res=-1;
		}
		else{
			res=-1;
			for(int s=tmpq;;s=(s-1)&tmpq){
				if(id[tmp1|s]) res=tmp1|s;
				if(!s) break;
			}
		}
		if(~res) printf("%s 9\n",str[id[res]]);
		else puts("IMPOSSIBLE");
	}
	return 0;
}
```

---

## 作者：oMin0 (赞：0)

## 分析

首先不需要考虑 $g$，因为当所有 `r` 色块都翻出来时会自动结束操作。我们只需找到任意串的一个前缀，使得这个前缀覆盖了所有 `r` 色块，并没有覆盖任何一个 `n`、`b` 或 `x` 色块即可。

不妨对所有格子进行状压，把每个字符串对应的前缀记作 $T_1,T_2,\dots,T_{\sum|w_i|}$。可以看出每张图表把 $5\times 5$ 个格子分成了三类，分别是必选的（记作 $S_1$），可选的（记作 $S_2$），和不能选的（记作 $S_0$），则我们要找到一个 $S_1\subset T\subset S_1\bigcup S_2$。

先考虑快速判定一组 $(S_0,S_1,S_2)$ 是否有解。我们讨论 $|S_0|,|S_1|,|S_2|$ 的大小关系：

- 如果 $|S_2|\leq \min(|S_0|,|S_1|)$，则直接枚举 $S_2$ 的子集即可做到 $O(2^{|S_2|})$。

- 如果 $|S_1|\leq \min(|S_0|,|S_2|)$，则枚举 $S_1$ 的子集做容斥，显然 $\sum [S_1\subset T\subset S_2]=\sum\limits_{P\subset S_1} (-1)^{|P|}[T\subset (S_2\setminus P)]$，那么预处理高维前缀和后可做到 $O(2^{|S_1|})$。

- 如果 $|S_0|\leq \min(|S_1|,|S_2|)$，则类似地预处理高维后缀和，复杂度 $O(2^{|S_0|})$。

记格子总数为 $k$，则综合以上三个做法，预处理复杂度 $O(k2^k)$，单次判定复杂度降低至 $O(2^{\frac{k}{3}})$。

再考虑原题中如何找出一个解，这个直接逐位确定 $S_2$ 即可，复杂度是判定复杂度乘上 $|S_2|$，也就是 $O(k2^{\frac{k}{3}})$。

于是做完了，最终总复杂度 $O(k2^k+qk2^{\frac{k}{3}})$，预处理部分常数极小，因此很容易通过。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define mod 998244353
#define G 3
#define Gi 332748118
mt19937 rnd(time(0));
mt19937_64 rndl(time(0));
#define endl "\n"
#define lowbit(x) (x&(-x))

int n,bh[34000005],sum[34000005],sum2[34000005],q;
string s[100005];
char t[6][6];

int ck0(int nr0,int nr1,int nr2)
{
	int na=sum2[nr1];
	for(int i=nr0;i>0;i=(i-1)&nr0)
	{
		na+=((__builtin_popcount(i)&1)?-1:1)*sum2[nr1|i];
	}
	return na;
}
int ck1(int nr0,int nr1,int nr2)
{
	int na=sum[nr2|nr1];
	for(int i=nr1;i>0;i=(i-1)&nr1)
	{
		na+=((__builtin_popcount(i)&1)?-1:1)*sum[nr2|(nr1^i)];
	}
	return na;
}
int ck2(int nr0,int nr1,int nr2)
{
	if(bh[nr1]) return 1;
	for(int i=nr2;i>0;i=(i-1)&nr2) if(bh[nr1|i]) return 1;
	return 0;
}
int ck(int nr0,int nr1,int nr2)
{
	int mn=min(__builtin_popcount(nr0),min(__builtin_popcount(nr1),__builtin_popcount(nr2)));
	if(__builtin_popcount(nr2)==mn) return ck2(nr0,nr1,nr2); 
	else if(__builtin_popcount(nr1)==mn) return ck1(nr0,nr1,nr2); 
	else if(__builtin_popcount(nr0)==mn) return ck0(nr0,nr1,nr2);
}

signed main()
{
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i]; int nr=0; 
		for(int j=0;j<s[i].length();j++) 
		{
			if(s[i][j]!='z') nr|=(1<<(s[i][j]-'a')); 
			bh[nr]=i,sum[nr]=sum2[nr]=1;
		}
	}
	for(int len=1;len<(1<<25);len<<=1) for(int j=0;j<(1<<25);j+=(len<<1)) for(int p=0;p<len;p++) sum[j+p+len]+=sum[j+p],sum2[j+p]+=sum2[j+p+len];
	cin>>q;
	while(q--)
	{
		int nr0=0,nr1=0,nr2=0;
		for(int i=1;i<=5;i++) for(int j=1;j<=5;j++) 
		{
			cin>>t[i][j];
			if(t[i][j]>='A'&&t[i][j]<='Z') nr2|=(1<<((i-1)*5+j-1));
			else if(t[i][j]=='r') nr1|=(1<<((i-1)*5+j-1)); else nr0|=(1<<((i-1)*5+j-1));
		}
		if(!ck(nr0,nr1,nr2)) {cout<<"IMPOSSIBLE"<<endl; continue;}
		while(nr2)
		{
			int mn=lowbit(nr2); nr2-=mn;
			if(ck(nr0+mn,nr1,nr2)) nr0+=mn; else nr1+=mn;
		}
		cout<<s[bh[nr1]]<<" "<<"9"<<endl;
	}
}
```

---

