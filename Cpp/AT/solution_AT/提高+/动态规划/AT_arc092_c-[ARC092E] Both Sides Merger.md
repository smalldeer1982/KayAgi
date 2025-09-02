# [ARC092E] Both Sides Merger

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc092/tasks/arc092_c

あなたは，長さ $ N $ の数列 $ a_1,\ a_2,\ ...,\ a_N $ を持っています。

あなたは，この数列の長さが $ 1 $ になるまで，繰り返し以下の操作を行います。

- まず，数列の要素を $ 1 $ つ選ぶ。
- もしその要素が数列の端だった場合，その要素を削除する。
- もしその要素が数列の端でない場合，その要素を，選んだ要素の両隣の要素の和に書き換える。そしてその後，両隣の要素を削除する。

あなたは，最終的な数列の要素の値を最大化したいです。

最終的な数列の要素の値の最大値と，それを達成する手順を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \leq\ N\ \leq\ 1000 $
- $ |a_i|\ \leq\ 10^9 $

### Sample Explanation 1

数列は以下のように変化します。 - $ 1 $ 回目の操作後の数列 : $ 4,\ 3,\ 7,\ 5 $ - $ 2 $ 回目の操作後の数列 : $ 4,\ 3,\ 7 $ - $ 3 $ 回目の操作後の数列 : $ 11(4+7) $

### Sample Explanation 2

\- $ 1 $ 回目の操作後の数列 : $ 100,\ 200(100+100) $ - $ 2 $ 回目の操作後の数列 : $ 200 $

### Sample Explanation 3

\- $ 1 $ 回目の操作後の数列 : $ -4,\ 1,\ 2,\ 3 $ - $ 2 $ 回目の操作後の数列 : $ 1,\ 2,\ 3 $ - $ 3 $ 回目の操作後の数列 : $ 4 $

## 样例 #1

### 输入

```
5
1 4 3 7 5```

### 输出

```
11
3
1
4
2```

## 样例 #2

### 输入

```
4
100 100 -1 100```

### 输出

```
200
2
3
1```

## 样例 #3

### 输入

```
6
-1 -2 -3 1 2 3```

### 输出

```
4
3
2
1
2```

## 样例 #4

### 输入

```
9
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
5000000000
4
2
2
2
2```

# 题解

## 作者：hyj0824 (赞：2)

> 口胡错结论真是害人不浅

### 经典套路

如果我们给奇偶位置上的数分别染成黑白色，不难看出只有同种颜色才有可能合并，且在任意操作后该性质不变。问题就变成在奇数位或偶数位上选一些数使他们和最大。

开始以为奇偶分开，选的数必须连续，直接跑区间最大子段和。结果结论错了……事实上合并时可以跳过一些数不合并：

`1 0 -1 0 1`

如果跑最大子段和，那么答案是 $1$。而我们依次选第三个数、第二个数，最后答案是 $2$。所以奇偶分开，直接 $O(n)$ 只选正数求和即可，全是非正数就取最大值，顺便把选择的数的坐标存起来。

```cpp
// 下面以奇数为例：Jpos是选择的奇数的坐标
LL maxpos=1,SUM=0;
for(int i=1; i<=n; i+=2) {
	if(a[i]>0) SUM+=a[i],Jpos.push_back(i);
	if(a[maxpos] < a[i]) maxpos=i;
}
LL ANS1;
if(SUM) ANS1 = SUM;
else ANS1 = a[maxpos], Jpos.push_back(maxpos);
```

### 构造方案

逆着来操作，先把`n`到`pos.back()+1`删掉；

对于`pos`内部的相邻两个坐标 $l,r$ 取其中点坐标 $mid$，依次选择 $mid,mid-1,...,l+1$ 合并；

最后删`1`到`pos.front()-1`。

总复杂度 $O(n)$，具体细节看代码吧，欢迎 hack：


```cpp
#include <bits/stdc++.h>
using std::cin;
using std::cout;
using LL = long long;
using ull = unsigned long long;
using ld = long double;

const int maxn = 1010;

LL a[maxn];
int n;
std::vector<int> Jpos,Opos;

std::vector<int> ans;
void print(std::vector<int> &pos) {
	int i=n;
	while(i!=pos.back()) {
		ans.push_back(i),i--;
	}
	for(int p=pos.size()-1;p>=1;p--){
		int mid = (pos[p]+pos[p-1])>>1;
		int RE = pos[p]-mid;
		while(RE--) ans.push_back(mid--);
	}
	i = 1;
	while(i<pos.front()) {
		ans.push_back(1);
		i++;
	}
	cout << ans.size() << '\n';
	for(int j : ans){
		cout << j << '\n';
	}
}

int main() {
	std::ios::sync_with_stdio(0);

	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
	}

	// ji
	LL maxpos=1,SUM=0;
	for(int i=1; i<=n; i+=2) {
		if(a[i]>0) SUM+=a[i],Jpos.push_back(i);
		if(a[maxpos] < a[i]) maxpos=i;
	}
	LL ANS1;
	if(SUM) ANS1 = SUM;
	else ANS1 = a[maxpos], Jpos.push_back(maxpos);

	maxpos=2,SUM=0;
	for(int i=2; i<=n; i+=2) {
		if(a[i]>0) SUM+=a[i],Opos.push_back(i);
		if(a[maxpos] < a[i]) maxpos=i;
	}
	LL ANS2;
	if(SUM) ANS2 = SUM;
	else ANS2 = a[maxpos], Opos.push_back(maxpos);

	cout << std::max(ANS1,ANS2) << '\n';
	if(ANS1==std::max(ANS1,ANS2)) {
		print(Jpos);
	} else {
		print(Opos);
	}
	return 0;
}
```


---

## 作者：EuphoricStar (赞：2)

是 [CF1844C Particles](https://codeforces.com/problemset/problem/1844/C) 的原题。

Key observation：每个元素的下标奇偶性不改变。

于是讨论最后一个数是下标为奇数还是偶数加起来的数。将下标奇偶性相同的元素分开考虑。对于下标奇偶性相同的元素，不难发现答案的上界是所有 $> 0$ 的元素之和（没有 $> 0$ 的元素时选一个最大的），并且一定能够构造方案以达到上界。

例如，下面 `O` 代表对答案有贡献的元素，`.` 代表没有贡献的元素：

`.O.O...O`

方案是 `.O.O...O` $\to$ `O.O...O` $\to$ `O...O` $\to$ `O.O` $\to$ `O`。

因为 $n \le 10^3$，构造方案就直接模拟即可，复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/arc092/submissions/43670387)

---

## 作者：dd_d (赞：2)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16269670.html)  
### Sol  
首先，答案肯定是原序列的一个子序列之和。  
然后观察这个合并操作，很容易发现奇数位置只能与奇数位置合并，偶数位置只能与偶数位置合并。  
那么问题转化为要在奇数位置上选一些数或者偶数位置上选一些数使他们和最大。  
直接 dp 就行。  
构造方案的话先删两端的，然后每次取中点一个一个合并即可。  
时间复杂度 $O(n^2)$
### Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=5e3+10;
vector<int> G,Ans;
int n,a[N],dp[N],pre[N],ans,now,ff;
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read();
	for (int i=1;i<=n;i++)
	{
		a[i]=read();
		if (a[i]>0) ff=1;
	}
	if (!ff)
	{
		int j=1;
		for (int i=1;i<=n;i++)
			if (a[i]>a[j]) j=i;
		writeln(a[j]); writeln(n-1);
		for (int i=1;i<j;i++)
			writeln(1);
		for (int i=n;i>j;i--)
			writeln(i-j+1);
		return 0;
	}
	for (int i=1;i<=n;i++)
	{
		dp[i]=a[i];
		for (int j=i-2;j>=1;j-=2)
			if (dp[j]+a[i]>dp[i]) dp[i]=dp[j]+a[i],pre[i]=j;
	}
	for (int i=1;i<=n;i++)
		if (ans<dp[i]) ans=dp[i],now=i;
	writeln(ans);
	while (pre[now])
	{
		G.push_back(now);
		now=pre[now];
	}
	G.push_back(now);
	reverse(G.begin(),G.end());
	for (int i=1;i<G[0];i++)
		Ans.emplace_back(1);
	int tot=G[0]-1;
	for (int i=n;i>=G[G.size()-1]+1;i--)
		Ans.emplace_back(i-tot);
	for (int i=0;i<(int)G.size()-1;i++)
	{
		int X=G[i+1]-G[i]+1-1;
		if (G[i+1]-G[i]==2)
		{
			Ans.emplace_back(2);
			continue;
		}
		for (int j=G[i]+1;j<G[i+1]-1;j+=2)
			Ans.emplace_back(3);
		Ans.emplace_back(2);
		tot+=X;
	}
	writeln(Ans.size());
	for (auto x:Ans)
		writeln(x);
}





```

---

## 作者：_JF_ (赞：0)

模拟赛出了这题的改编版本，差点场切，但挂 $5$。

写一下自己的思考过程。

[[ARC092E] Both Sides Merger ](https://www.luogu.com.cn/problem/AT_arc092_c)

首先我们关注到一个事实，如果我们从当前的 $i$ 开始进行合并的话，合并一定能从左到右进行。

因为发现，考虑 $[i,j]$，如果我按 $[k,j]$，$[i,k-1]$ 顺序合并，和 $[i,k-1]$，$[k,j]$ 是等价的，就都是获得两个区间的贡献。

注意到在这里删除操作不会造成影响。

继续考察，我们发现对于一个位置 $i$，如果想要合并，那么中间至少要间隔奇个位置，且间隔完了的下一个位置 $j$ 必须满足 $a_j\ge 0$，才有合并意义。

然后我们就可以得到，合并的方式只有两种，从 $1$ 位置开始合并；或者从 $2$ 位置开始合并（也就是分奇偶），你注意到你开始的位置越左，你的答案一定不劣。

于是我们就在 $O(n)$ 求到了最值。

方案的话，直接模拟我们取的过程即可。

---

