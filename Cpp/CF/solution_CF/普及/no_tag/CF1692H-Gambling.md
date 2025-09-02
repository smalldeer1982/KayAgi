# Gambling

## 题目描述

Marian 在一个赌场，赌场的游戏规则如下：

每一轮开始前，玩家选一个在 $1$ 到 $10^9$ 。然后，掷出一个有着 $10^9$ 面的骰子，会随机出现一个在 $1$ 与 $10^9$ 之间的数。如果玩家猜对了，他们的钱就会翻一番，否则他们的钱会被折半。

Marian 可以预测未来，他知道在接下来 $n$ 轮里骰子上的数，即 $x_1,x_2,...,x_n$。

Marian 会选择三个整数 $a,l$ 和 $r$（$l \le r$）。他会玩 $r-l+1$ 轮。每一轮，他都猜同一个数 $a$。一开始（在第 $l$ 轮之前）他有 $1$ 美元。

Marian 请你帮助他决定 $a,l$ 和 $r$（$1\le a\le 10^9,1\le l\le r\le n$），让他最后的钱最多。

注：在折半或翻番的过程中不会进行游戏，也不会有精度问题。举个例子，Marian 在游戏中可能会有 $\frac{1}{1024},\frac{1}{128},\frac{1}{2},1,2,4$ 等等（任何可以表示为 $2^t$ 的数，其中 $t$ 为非 $0$ 整数）。

## 说明/提示

对于第一组数据，最好的选择是 $a=4,l=1,r=5$，游戏会这样进行：
- Marian 最开始有 $1$ 美元。
- 第一轮结束后，Marian 会有 $2$ 美元，因为骰子上掷出的数与 Marian 猜的数相同。
- 第二轮结束后，Marian 会有 $4$ 美元，因为他又猜对了。
- 第三轮结束后，Marian 会有 $2$ 美元，因为他猜了 $4$，而 $3$ 是正确答案。
- 第四轮结束后，Marian 又会有 $4$ 美元，因为他又又猜对了。
- 最后一轮结束后，Marian 会 $8$ 美元，因为他又又又猜对了。

第二组数据有多种答案，但可以证明 Marian 最后最多只有 $2$ 美元，因此只要 $l=r$ 且 $a$ 的数字合理，都是正确答案

## 样例 #1

### 输入

```
4
5
4 4 3 4 4
5
11 1 11 1 11
1
1000000000
10
8 8 8 9 9 6 6 9 6 6```

### 输出

```
4 1 5
1 2 2
1000000000 1 1
6 6 10```

# 题解

## 作者：D2T1 (赞：10)

[Luogu 题目链接](https://www.luogu.com.cn/problem/CF1692H)

[CF 题目链接](https://codeforces.com/problemset/problem/1692/H)

## 题解 CF1692H

首先，题意可以转化为：

求一个区间 $[l,r]$，一个数 $a$，使得 $\sum\limits_{i=l}^r[x_i=a]-\sum\limits_{i=l}^r[x_i\neq a]$ 最大。若有多组解输出任意一组。

那么首先考虑确定 $a$，那么把原序列等于 $a$ 的数改为 $1$，不等于 $a$ 的数改为 $-1$，就变成了一个最大子段和问题，可以 $O(n)$ dp 求解。

如果枚举 $a$ 呢？那么这题的复杂度就是 $O(n^2)$，过不了。

------------

怎么优化呢？在 dp 求解最大子段和的过程，我们可以把连续的 $-1$ 段合并为一个数，这样只用在出现 $1$ 的时候进行 dp。对于下标 $i$，在所有 $a$ 中必然只会存在一个 $1$，即 $a=x_i$ 的情况。所以我们只会 dp $n$ 次。复杂度降至 $O(n)$。

设 $ls_i$ 表示使 $k<i,x_k=x_i$ 的最大的 $k$，则状态转移方程为：

$$f_i=\max(f_{ls_i}-(i-ls_i-1), 0)+1$$

输出方案的话可以记录下 $f_i$ 是从哪个地方转移过来的。具体可以参考代码。

------------

求解 $ls_i$ 也很简单，在读入时用 `map` 预处理一下即可，复杂度 $O(n\log n)$。所以总复杂度也为 $O(n\log n)$。

```cpp
//CF1692H
#include <cstdio>
#include <map>
using namespace std;

const int N = 2e5 + 10;
int t, n, x[N], ls[N], f[N], l[N];

int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		map<int, int> mp;
		for(int i = 1; i <= n; ++ i){
			scanf("%d", &x[i]);
			ls[i] = mp[x[i]];
			mp[x[i]] = i;
		}
		int ans = 0, pos;
		for(int i = 1; i <= n; ++ i){
			if(f[ls[i]] - (i-ls[i]-1) > 0){
				f[i] = f[ls[i]] - (i-ls[i]-1) + 1;
				l[i] = l[ls[i]];
			} else {
				f[i] = 1;
				l[i] = i;
			}
			if(f[i] > ans){
				ans = f[i]; pos = i; 
			}
		}
		printf("%d %d %d\n", x[pos], l[pos], pos);
	}
}
```

---

## 作者：Withers (赞：2)

[题目传送门](https://codeforces.com/contest/1692/problem/H)
# 题目大意
给定数组 $x[]$ 和 $n$，求出数组中的一个值 $a$ 和区间 $[l,r]$，使得在区间 $[l,r]$ 中等于 $a$ 的值和不等于 $a$ 的值得个数的差最大。
# 思路
离散化数组，枚举每一个数，显然可以发现如果要最优，开头和结尾必须是 $a$。于是，我们可以记录所有和 $a$ 的相等的下标，然后转移，记录现在这个区间的答案是多少，每次减去其中不和 $a$ 相等的。如果小于0，就把这个区间的开始设为现在这里，每次打擂台决定最后答案即可，具体见代码。

# 代码

```cpp
	map<int,vector<int> > b;
	cin>>n;
	b.clear();
	for(int i=1;i<=n;i++) cin>>a[i],b[a[i]].push_back(i);
	l=1,x=a[1];
	int sum=1,ans=1,l=1,r=1,tot=a[1],ll=1,rr=1,lst;
	for(auto i=b.begin();i!=b.end();i++)
	{
		sum=1,l=lst=(i->second)[0];
		x=i->first;
		//cout<<x<<"qwq"<<endl;
		for(int j=1;j<(i->second).size();j++)
		{
			y=(i->second)[j];
			sum-=(y-lst-2);
			if(sum<=0) sum=1,l=y;
			//cout<<sum<<" "<<l<<" "<<y<<endl;
			if(sum>ans)
			{
				ll=l;
				rr=y;
				ans=sum;
				tot=x;
			}
			lst=y;
		}
	}
	cout<<tot<<" "<<ll<<" "<<rr<<endl;
```



---

## 作者：aCssen (赞：0)

### Solution

这个最大收益其实就是要 $2$ 的幂次最大，那么根据 $2^a2^b=2^{a+b}$，就变成了等于 $a$ 的减去不等于 $a$ 的数量最大。

首先有一个结论，假设你选了 $a$，那么区间的两个端点都会是 $a$，否则，你把它删到 $a$ 一定不劣。

那么现在有一个暴力了，枚举每种颜色，然后对于每种颜色枚举它的所有可能选择的 $l,r$，更新答案。假设 $[l,r]$ 中 $a$ 有 $x$ 个，那么答案就是 $x-(r-l+1-x)=2x-(r-l+1)$。

同时又注意到这个问题在枚举 $a$ 后等价于把 $=a$ 的设为 $1$，不等于的设为 $-1$，求最大子段和，这样做时间复杂度也是 $n^2$ 的。因为要输出方案，所以用前缀和会比较方便。

现在我们有两个暴力了，而且只有一个和 $n$ 有关，考虑**根号分治**，记一个阈值 $B$，对于出现次数 $\le B$ 的执行第一种暴力，因为这些数最多有 $\frac{n}{B}$ 个，时间复杂度是 $\frac{n}{B}B^2=nB$。对于出现次数 $>B$ 的数执行第二种暴力，复杂度是 $\frac{n^2}{B}$。总复杂度就是 $\mathcal{O}(\frac{n^2}{B}+nB)$，取 $B=\sqrt n$ 则时间复杂度 $\mathcal{O}(n\sqrt n)$。

其实直接在求最大子段和的时候把 $-1$ 缩起来做就好了。。。
### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
	template<typename T=int> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
const int maxn=2e5+5;
int a[maxn],raw[maxn],s[maxn];
vector<int>v[maxn];
void solve(){
	int n=read(),B=(int)sqrt(n),ans=0;
	for(int i=1;i<=n;i++) a[i]=raw[i]=read();
	sort(raw+1,raw+n+1);
	int len=unique(raw+1,raw+n+1)-raw-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(raw+1,raw+len+1,a[i])-raw;
	for(int i=1;i<=len;i++) v[i].clear();
	for(int i=1;i<=n;i++) v[a[i]].push_back(i);
	for(int i=1;i<=len;i++){
		int M=v[i].size();
		if(M>B){
			for(int j=1;j<=n;j++){
				s[j]=s[j-1];
				if(a[j]!=i) s[j]--;
				else s[j]++;
			}
			int Minpos=0,Mn=0;
			for(int j=1;j<=n;j++){
				ans=max(ans,s[j]-Mn);
				if(s[j]<Mn) Mn=s[j],Minpos=j;
			}
		}
		else{
			for(int j=0;j<M;j++){
				for(int k=j;k<M;k++)
					ans=max(ans,2*(k-j+1)-(v[i][k]-v[i][j]+1));
			}
		}
	}
	for(int i=1;i<=len;i++){
		int M=v[i].size();
		if(M>B){
			for(int j=1;j<=n;j++){
				s[j]=s[j-1];
				if(a[j]!=i) s[j]--;
				else s[j]++;
			}
			int Minpos=0,Mn=0;
			for(int j=1;j<=n;j++){
				if(s[j]-Mn==ans){
					printf("%d %d %d\n",raw[i],Minpos+1,j);
					return;
				}
				if(s[j]<Mn) Mn=s[j],Minpos=j;
			}
		}
		else{
			for(int j=0;j<M;j++){
				for(int k=j;k<M;k++){
					if(2*(k-j+1)-(v[i][k]-v[i][j]+1)==ans){
						printf("%d %d %d\n",raw[i],v[i][j],v[i][k]);
						return;
					}
				}
			}
		}
	}
}
int main(){
	int t=read();
	while(t--) solve();
	return 0;
}
```

---

## 作者：zct_sky (赞：0)

### Solution:
-----
首先区间中等于 $a_i$ 的贡献为 $1$，不等于的贡献为 $-1$。

然后变成了最大字段和问题。

考虑离散化，将 $a_i$ 的值域缩小为 $[1,2\times 10^5]$。

然后第一层遍历每个数值，第二层遍历所在位置（从小到大），根据位置来更新答案（记录区间开头、末尾，知道区间长度、贡献为 $1$ 个数，就能更新答案）。

若当前区间总贡献 $<1$，说明还不如只取末尾的贡献，更新开头。

由于每个元素只会被取到一次，所以最大字段和部分复杂度为 $\mathcal{O}(n)$。

算上离散化时间复杂度，则该程序时间复杂度为 $\mathcal{O}(n \log n)$。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;

}
const int N=2e5+7;
int n,a[N],b[N],t;
bool cmp(int x,int y){
	return (a[x]==a[y])?x<y:a[x]<a[y];
} 
vector<int> c[N];
int l,r,ans,answer;
int main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			b[i]=i;
		}
		sort(b+1,b+1+n,cmp);
		int tot=0;
		for(int i=1;i<=n;i++){
			if(a[b[i]]!=a[b[i-1]])tot++;
			c[tot].push_back(b[i]);
		}
		answer=0;
		for(int i=1;i<=tot;i++){
			int tmp=0,l1=c[i][0],r1;
			for(int j:c[i]){
				tmp++;
				r1=j;
				//区间长度 r1-l1+1，贡献 1 个数 tmp 
				//tmp - (r1+l1+1 - tmp) 为字段和（贡献和） 
				if(answer<2*tmp-(r1-l1+1)){
					answer=2*tmp-(r1-l1+1);
					ans=a[l1];
					l=l1,r=r1;
				}
				if(1>2*tmp-(r1-l1+1))l1=j,tmp=1;
			}
			c[i].clear();
		}
		printf("%d %d %d\n",ans,l,r);
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

## 思路（详细）

首先我们这个题目可以进行一下简单的转化，下面是转化后的题意。

> 对于每组数据，给定一个长度为 $n$ 的数列 $a$，在该数列中取一个区间 $[l,r]$，在 $[l,r]$ 中取一个数 $a_i\land i\in[l,r]$，它的贡献是该区间内 $a_i$ 的数量减去不是 $a_i$ 的数的数量，对于任意区间的任意 $a_i$，找到最大贡献。

容易发现从区间难以着手，我们不妨试着从每个 $a_i$ 入手，首先对每个 $a_i$ 进行离散化操作。接着容易发现这样一个性质：

- 性质 $1$：如果我取到了一段连续的 $a_i$ 中的一部分，我肯定会把这段给取完。

接下来定义使得贡献最大时，我选择的 $a_i$ 为 $x$。

明显，由于我想要取的数是 $x$，既然我都取到了这一段里面，那我把这段取完的贡献会增加。于是我们能够发现这样一个推论：

- 推论 $1$：从性质 $1$ 出发，容易发现贡献最大的 $[l,r]$ 满足 $l$ 是一段连续 $x$ 的左端，$r$ 是一段连续 $x$ 的右端。

假设我现在得到了每个数在 $a$ 中的每一个连续段的信息（这很好实现），我如何知道对于每个数它应该怎么取更好？不妨从时间复杂度开始分析，明显本题应该做到复杂度 $O(n^2)$ 以下，我们不妨考虑线性。很容易发现我们先枚举数，再枚举该数分成的连续段，这两个循环乘起来是 $O(n)$ 的，我们考虑做 $O(1)$ 的贪心。

我们不妨对于考虑这样的三段：$[l_1,r_1],[l_2,r_2],[l_3,r_3]$。我们假设目前已经取了 $[l_1,r_1]$ 和 $[l_2,r_2]$。那么有结论：

- 性质 $2$：若 $[l_1,r_2]$ 的贡献，再减去为了取到 $l_3$ 中间要扣掉的数的个数的这个值 $s$ 小于等于 $0$，那么我如果取了 $[l_3,r_3]$，我必然不取 $[l_1,r_2]$ 这一部分。

这个结论是同样显然的，如果这一段和 $[l_3,r_3]$ 组合在一起，那么对于 $[l_3,r_3]$ 来说是一个负贡献或者没用，还不如不取，所以我不如直接把它给断开，$[l_3,r_3]$ 就不要和前面的放在一起了。

这个结论因此可以被扩展为：

- 推论 $2$：若 $[l_i,r_j]$ 的贡献，再减去为了取到 $l_{j+1}$ 中间要扣掉的数的个数的这个值 $s$ 小于等于 $0$，那么我如果取了 $[l_{j+1},r_{j+1}]$，我必然不取 $[l_1,r_j]$ 这一部分。

反过来，如果 $s>0$，那么我必须取走这一段，因为这可以扩大我的答案。这样做之后，这些连续段就可以被划分为几个集合，我的答案必然来自这些集合中的某一个。

实现的时候，我遇到一个 $s\leqslant 0$ 的情况我就去统计前面那一段的答案，然后算贡献就行。

注意边界情况可能会叉了你。

## 记录

[AC 记录](https://www.luogu.com.cn/record/78159780)

---

## 作者：Cocoly1990 (赞：0)

考虑枚举每次选择哪个数，可以发现每次对于选择的数对幂次带来的贡献为 $1$，否则为 $-1$，问题转化为 $1,-1$ 最大子段和，然后对于每次枚举的这个我们选择的数，我们不妨记作 $x$，显然我们不需要每个数都打标记做一次，我们只需要把原数列按 $x$ 分段，关心每段的和

![1655436194300.png](https://img-kysic-1258722770.file.myqcloud.com/b396da11c4f1843ba8414c5a7591eb98/e909f854dbfec.png)

比如这张图，红色的部分是 $x$，那我们只需要把每块红色和白色看作整体做最大子段和，这样的有效段数是 $cnt_x$ 的。

这个问题是平凡的，势能分析得复杂度线性。瓶颈在于离散化。

实现过程要精细一点，不然一不小心就炸了，比如你做最大子段和的时候全部撸了一遍标记啊之类的。

我没写代码，但是三月写了，你们参考一下也行：

[代码](https://codeforces.com/contest/1692/submission/160547718)

---

## 作者：npqenqpve (赞：0)

div4 没打，感觉我的做法做赛时很难冲出来，毕竟前面还有 $7$ 题。

### 思路：

考虑转化题意，即求得一段区间使得**不等于 $k$ 的数的出现次数**减去 **$k$ 的出现次数**最小化。

显然如果 $k$ 是选中的数，答案区间 $l$ 和 $r$ 必然有 $a_l=a_r=k$。

那么考虑枚举 $k$ 并记录每个数出现的位置，即 $g_{i,j}$ 表示 $i$ 第 $j$ 次在原数组 $g_{i,j}$ 这一位置出现。

那么对每一个 $k$ 枚举右端点，显然只有 $n$ 种。

利用 $g$ 数组对每一种 $k$ 的右端点 $r$ 找最优的左端点 $l$，那么就是对于 $l<r$ 求 $g_{k,r}-g_{k,l}+1-2\times(r-l+1)$ 的最小值；

解释一下：其中的 $g_{k,r}-g_{k,l}+1-(r-l+1)$ 是求得这段区间内除以 $2$ 的次数，再减去一次 $r-l+1$ 就求得了最终要除多少次。

然后对 $g_{k,r}-g_{k,l}+1-2\times(r-l+1)$ 分组，分成 $g_{k,r}-2\times r-1$ 的和剩下 $2\times l-g_{k,l}$，显然前者是常数，需要最大化后者，后者对于每个 $l$ 形式都一样，直接线段树维护即可。

### 代码：[link](https://codeforces.com/contest/1692/submission/160739963)

实现细节较多

---

