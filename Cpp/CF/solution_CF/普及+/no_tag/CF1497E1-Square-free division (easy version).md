# Square-free division (easy version)

## 题目描述

### 题意描述

- 这是简单版，此题中 $k=0$。

给出一串长为 $n$ 的序列 $a_1,a_2,a_3...a_n$。

把它分成尽量少的块使每一块中任意两数的乘积不是一个完全平方数。

输出最少的块数。

## 样例 #1

### 输入

```
3
5 0
18 6 2 4 1
5 0
6 8 1 24 8
1 0
1```

### 输出

```
3
2
1```

# 题解

## 作者：redintonc (赞：9)

  首先我们知道如果两个数的乘积为一个完全平方数，那么它所有的质因子的指数都为偶数。
  所以我们可以在输入阶段对每个数先进行处理，将其已经有的指数为偶数的质因子给除掉，这样处理之后只有当两个数相同时相乘才会是完全平方数。我这里用map进行判断是否已经出现了这个数，实现起来比较简单。
  

------------

  ```cpp
#include<iostream>
#include<map>
using namespace std;
int a[200005];
int main() {
	int t; cin >> t;
	while (t--) {
		int n, k; cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			int now = a[i];
			for (int j = 2; j * j <= a[i]; j++) {
				int cnt = 0;
				while (now % j == 0)cnt++, now /= j;
				for (int s = 1; s <= cnt -cnt%2; s++) a[i] /= j;
			}
		}
		int ans = 0;
		map<int,bool>q;
		for (int i = 1; i <= n; i++) {
			if (q[a[i]]) q.clear(), ans++;
                  q[a[i]] = 1;
		}
		cout << ++ans << endl;
	}
	return 0;
}
```


---

## 作者：江户川·萝卜 (赞：3)

题目要求两个数相乘不能为平方数，我们可以先把每一个数的平方数因子除掉，不影响结果。

这时，只要每个小数组里都没有相同的数即可。

粗劣的证明：

此时，每一个数都能表示为 $\prod^m_{i=1}p_{a_i}$，即若干个互不相同的质因子相乘。

要相乘为平方数，必须满足乘积的每一个质因子的指数都为偶数。所以另一个数必须是 $k\cdot \prod^m_{i=1}p_{a_i}$，这样才能使乘积为 $k\cdot\prod^m_{i=1}p_{a_i}^2$，且 $k$ 必须是平方数。因为每个数已经没有了平方数因子，所以 $k$ 只可能为 $1$。也即两数相等。

---
所以，整个程序分为两步：
1. 消平方数因子，可用枚举做。
2. 分段，可采取记录每个数值最后出现的位置的方法来做。

### Code:
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[200005],d[10000005];
int stk[200005],top;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,k;
		scanf("%d%d",&n,&k);//k=0
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			int x=a[i];
			for(int j=2;j*j<=x;j++){
				int cnt=0;while(x%j==0){cnt++;x/=j;}
				for(int k=1;k<=cnt/2*2;k++) a[i]/=j;
			}//消平方数因子
		}
		top=0;
		int ans=0,st=1;
		for(int i=1;i<=n;i++){
			if(d[a[i]]>=st) ans++,st=i;
			if(!d[a[i]]) stk[++top]=a[i];
			d[a[i]]=i;
		}
		ans++;
		printf("%d\n",ans);
		while(top) d[stk[top]]=0,top--;
     //采用栈的方法来减小还原数组的时间
	}
	return 0;
}
```

---

## 作者：Gold14526 (赞：2)

# CF1497E1 Square-free division (easy version) 题解
## 1、题意简化
保证每一个块没有两个数乘积为完全平方数的前提下，把一个序列分成最少的块。
## 2、主要思路
$x\times y\times z^2$ 是否为完全平方数，与 $x\times z=y\times z$ 是否成立结果相同，又等同于 $x=y$ 是否成立，其中 $z$ 没有任何作用，所以，我们如果把每个数的完全平方数因数全部除掉，题目就变成了：

保证每个块没有相同数的情况下，将序列分为最少的块。

至于块怎么分，以贪心解决。
## 3、Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int num;
char ch;
int read()
{
	ch=getchar();
	num=0;
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+ch-'0';
		ch=getchar();
	}
	return num;
}
int a[3162],pr[1000],siz;
void find_pr(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(a[i]==1)pr[++siz]=i;
		for(int j=1;j<=siz;j++)
		{
			if((long long)i*pr[j]>n)break;
			a[i*pr[j]]=0;
			if(i%pr[j]==0)break;
		}
	}
}
int f(int x)
{
	for(int i=1;i<=siz;++i)
	{
		while(x%(pr[i]*pr[i])==0)
		{
			x/=pr[i]*pr[i];
		}
	}
	return x;
}
bool used[10000001];
int c[200001];
int main()
{
	fill(a+1,a+3162,1);
	find_pr(3161);
	int T=read();
	int n;
	int l,ans;
	while(T-->0)
	{
		l=1;
		ans=0;
		n=read();
		read();
		for(int i=1;i<=n;++i)
		{
			c[i]=f(read());
		}
		used[c[1]]=1;
		for(int i=2;i<=n;++i)
		{
			if(used[c[i]])
			{
				for(int j=l;j<i;++j)used[c[j]]=0;
				++ans;
				l=i;
			}
			used[c[i]]=1;
		}
		for(int i=l;i<=n;++i)used[c[i]]=0;
		++ans;
		printf("%d\n",ans);
	}
	return 0;
}
```
## 4、写在最后
如果有什么疑问，或者对题解有什么意见，可以在评论区指出。

---

## 作者：Na2PtCl6 (赞：2)

## 前言
[题目链接](https://www.luogu.com.cn/problem/CF1497E1)

此题出题人仁慈了， $n$ 如果给 $10^7$ 一点也不过分。

## 分析题目
### 1.转化
要是这个问题是“使每一段中没有相同的数”我就会了，用一个数组记录一下每个数上次在数组中出现的位置，如果发现当前数上次出现的位置在现在这个数段里，就要再分一段。

所以可见转化是此题关键的一步。

根据唯一分解定理，一个任意数 $x$ 可以表示成 $p_1^{a_1} \times p_2^{a_2} \times \cdot \cdot \cdot \times p_n^{a_n}$。如果一个数是平方数，则 $a_1$ 到 $a_n$ 都是偶数，所以如果把平方数的任意一个 $p_i^{a_i}$ 给去掉，它还是平方数。

根据这一性质，我们可以给每个数“减重”，把它所有满足 $a_i \mod 2 =0$ 的 $p_i^{a_i}$ 去掉，然后就变成了“使每一段中没有相同的数”的问题了。

### 2.进行“减重”
我们可以用欧拉筛筛出 $[2,10^7]$ 的数“减重”后的结果。

欧拉筛把所有数分成三类：1.素数 2.一个数乘上一个不被它整除的素数 3.一个数乘上一个可被它整除的素数。
>对于1，它“减重”后的结果就是它本身。

>对于2，减重后它等于它除以这个素数得到的数“减重”后的结果乘以当前素数。

>对于3.又要分两类讨论，如果这个数除以这个素数得到的数“减重”后的结果可以整除这个素数，这个数“减重”后就等于这个数除以这个素数得到的数“减重”后的结果除以这个素数；否则就和2一样。

如果觉得第二段话不太好理解建议结合代码。

其实还有一种上界 $O(nlogn)$ 的做法，要筛每个数的最小质因子 $p_1$ 以及它对应的 $a_1$，可以自己想想。

## 代码实现
代码中 `pr` 是“prime”的简写，存储素数；`lw` 是 “lose weight”的简写，存储每个数“减重”后的结果;`a` 和唯一分解定理的 $a$ 意义不同，指的是题目中的a数组。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000004;
int t,n,k,top;
int pr[maxn],lw[maxn],vis[maxn],a[maxn],stk[maxn];

signed main(){
	scanf("%d",&t);
	lw[1]=1;
	for(int i=2;i<maxn;i++){
		if(vis[i]==0){
			pr[++top]=i;
			lw[i]=i;
		}
		for(int j=1;pr[j]*i<maxn&&j<=top;j++){
			vis[pr[j]*i]=1;
			if(i%pr[j]==0){
				if(lw[i]%pr[j]==0)
					lw[i*pr[j]]=lw[i]/pr[j];
				else
					lw[i*pr[j]]=lw[i]*pr[j];
				break;
			}
			lw[i*pr[j]]=lw[i]*pr[j];
		}
	}
	top=0;
	memset(vis,0,sizeof(vis));
	while(t--){
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		int now=1,res=0;
		for(int i=1;i<=n;i++){
			if(vis[lw[a[i]]]>=now){
				++res;
				now=i;
			}
			if(vis[lw[a[i]]]==0)
				stk[++top]=lw[a[i]];
			vis[lw[a[i]]]=i;
		}
		++res;
		while(top>0)
			vis[stk[top--]]=0;
		printf("%d\n",res);
	}
	return 0;
}
```

---

## 作者：Creeper_l (赞：2)

题意：给定一个长度为 $n$ 的序列，求最少能将这个序列分成多少段使得任意一段中不存在两个数的积为完全平方数。

一个小 Trick：如果两个数乘起来为平方数，可以先将每个数的平方因子除掉，然后这两个数必然相等。于是这道题被转化为了一个区间不能有相等的值，这就很典了。

设 $pos_{a_{i}}$ 表示上一个 $a_{i}$ 出现在哪里（也就是最远可以满足条件的位置），那么有 dp 转移方程 $dp_{i}=dp_{pos_{a_{i}}}+1$，时间复杂度 $O(n)$。

注意分解质因数的时候可以先将质数线性筛出来，这样效率更高。

代码是 E2 的，于是在这里就不贴了，[评测记录](https://codeforces.com/contest/1497/my)。

---

## 作者：naroto2022 (赞：1)

# CF1497E1 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1497E1)

### 思路

看到 $n\leqslant2\times10^5,k\leqslant20$，自然想到 $O(nk)$ 或 $O(nk^2)$ 的 DP。

设 $f[i][j]$ 表示前 $i$ 个数中修改 $j$ 个划分的最小段数，$g[i][j]$ 表示表示以 $i$ 为终点，在 $i$ 所在段内修改了 $j$ 次向左最远能扩充到的点。

则有 $f[i][j]=\min(f[g[i][x]-1,j-x]+1)$，那么如何求 $g$ 呢？

我们发现在 $g[i][j]$ 中，对于一个确定的 $j$，当 $i$ 增加时，$g[i][j]$ 必然单调不减，所以对于一个 $j$ 能双指针 $O(n)$ 求，所以预处理 $g$ 的复杂度是 $O(nk)$。

DP 的复杂度是 $O(nk^2)$，故我们使用 $O(nk^2)$ 的复杂度通过本题。

### 后记

1. 在本题中，尽量不要使用 memset 函数给数组进行赋值。memset 函数的时间复杂度为 $O(n)$，其中 $n$ 为数组的字节大小。本题可以通过构造数据使得 memset 函数 TLE。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=2e5+10,K=25,S=1e7+10,INNF=0x3f3f3f3f;
int T,n,k,ans,a[N],num[S],f[N][K],g[N][K];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
} 
int main(){
	T=read();
	while(T--){
		n=read();k=read();ans=INNF;
		for(int i=1; i<=n; i++){
			a[i]=read();
			for(int j=2; j*j<=a[i]; j++) 
				while(a[i]%(j*j)==0)
					a[i]/=j*j;
		}
		for(int i=0; i<=k; i++){
			for(int j=1; j<=n; j++) num[a[j]]=0;
			for(int l=1,r=1,t=0; r<=n; r++){
				num[a[r]]++;
				t+=(num[a[r]]>1);
				while(t>i&&l<r){
					t-=(num[a[l]]>1);
					num[a[l]]--;
					l++;
				}
				g[r][i]=l;
			}
		}
		for(int i=1; i<=n; i++)
			for(int j=0; j<=k; j++){
				f[i][j]=INNF;
				for(int x=0; x<=j; x++)
					f[i][j]=min(f[i][j],f[g[i][x]-1][j-x]+1);
		}
		for(int i=0; i<=k; i++) ans=min(ans,f[n][i]);
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：czy0323 (赞：1)

先通过欧拉筛预处理出 $\leq 10^7$ 的所有质数，并用一个数组记下每个质数的编号，这个编号为它是第几个质数，合数则编号为 $0$。

求最少划分段，肯定是用贪心来解决，关键在于如何判断任意两个数的乘积是不是完全平方数。

一个数是完全平方数，则一定满足每个质因子的次数都是偶数次，所以我们对于所有的 $a_i$ 将它质因数分解，我们希望处理出一个串表示该数 $a_i$ 所有质因子出现的奇偶性，举个例子：

若 $1$ 表示该编号的质因子数量为奇数，$0$ 表示数量为偶数。

则当 $a_i=15$ 时，这个串就应该为 $011$。

那么，怎么用这个串？很简单，要凑成完全平方数，肯定要把串中的 $1$ 都消掉，找一个一模一样的串即可，易证若两串不一样，则一定组不成完全平方数。

但是这个串有可能很长（一般认为 $n$ 以内的质数个数为 $\frac{n}{\log n}$ 个），所以直接硬匹肯定是会 TLE 的，很容易能想到用哈希和 map 解决，那么这道题就做完了，复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5, M = 1e7+1;
#define ull unsigned long long
ull data[N], base[N];
int prime[N], pt;
int isprime[M], v[M];
map<int, int> mp;

inline void solve(){
	int n, k, ans = 1;
	cin >> n >> k;
	
	mp.clear();
	for(int i = 1; i <= n; i++)
		data[i] = 0;
	
	for(int i = 1; i <= n; i++){
		cin >> k;
		while( k != 1 ){
			int num = 1;
			while( v[k] == v[k / v[k]] ){
				k /= v[k];
				num++;
			}
			if( num & 1 )
				data[i] += base[isprime[v[k]]]; 
			k /= v[k];
		}
	}
	
	for(int i = 1; i <= n; i++){
		if( mp.count(data[i]) ){
			ans++;
			mp.clear();
		}
		mp[data[i]] = 1;
	}
	cout << ans << "\n";
	return;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	for(int i = 2; i < M; i++){
		if( !isprime[i] ){
			isprime[i] = ++pt;
			prime[pt] = i;
			v[i] = i;
		}
		for(int j = 1; j <= pt && i * prime[j] < M; j++){
			isprime[i * prime[j]] = 1;
			v[i * prime[j]] = prime[j];
			if( i % prime[j] == 0 )
				break;
		}
	}
	
	base[0] = 1;
	for(int i = 1; i <= pt; i++)
		base[i] = base[i - 1] * 233;
	
	int T;
	cin >> T;
	while( T-- )
		solve();
	return 0;
}
```

---

