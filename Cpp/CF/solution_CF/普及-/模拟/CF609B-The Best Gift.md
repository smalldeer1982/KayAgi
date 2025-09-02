# The Best Gift

## 题目描述

Emily's birthday is next week and Jack has decided to buy a present for her. He knows she loves books so he goes to the local bookshop, where there are $ n $ books on sale from one of $ m $ genres.

In the bookshop, Jack decides to buy two books of different genres.

Based on the genre of books on sale in the shop, find the number of options available to Jack for choosing two books of different genres for Emily. Options are considered different if they differ in at least one book.

The books are given by indices of their genres. The genres are numbered from $ 1 $ to $ m $ .

## 说明/提示

The answer to the first test sample equals 5 as Sasha can choose:

1. the first and second books,
2. the first and third books,
3. the first and fourth books,
4. the second and third books,
5. the third and fourth books.

## 样例 #1

### 输入

```
4 3
2 1 3 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
7 4
4 2 3 1 2 4 3
```

### 输出

```
18
```

# 题解

## 作者：asasas (赞：4)

这题是一个对于桶的运用。

先看下数据范围：$n$<=$2\times10^5$,看起来不可做啊。

但:$m$<=10。那很明显就是一个桶啊。

于是，我们开一个桶，把每种物品的个数存下来，然后枚举两两物品的搭配总数（就是两种物品的种数的乘积）的总和，最后输出即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[10005],n,m;//a数组是桶
int main(){
	long long ans=0;//以防万一
	cin >> n >> m;
	int q;
	for (int i=1;i<=n;i++){
		cin >> q;//读入 
		a[q]++;//这种物品的个数就加一 
	}
	for (int i=1;i<=m;i++){
		for (int j=i+1;j<=m;j++){//枚举，注意j从i+1开始
		ans=ans+a[i]*a[j];//算出第i种物品搭配第j种物品的个数，加入ans中 
		}
	} 
	cout << ans;
}
```


---

## 作者：Miraik (赞：4)


这是一道桶的好题。

题面写了：杰克希望知道有多少种不同的方案能够买**两本不同种类的书**给Emily。

因此珂以这么考虑：

1.先用桶存下 $2$ 到 $m$ 出现的次数。

2.从 $m$ 到 $2$ 降序枚举，每次先将当前**未计算的书的数量减去当前数出现的次数**，然后**答案加上当前数出现的次数乘以未计算的书的数量**。

这样这道题就迎刃而解了。

完整代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,m,f[15],ans;
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)f[read()]++;
	for(int i=m;i>=2;i--)
	    n-=f[i],ans+=f[i]*n;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：hxhhxh (赞：2)

## 大意

给一个数组，求从中选出两个元素，使得其不相等的方案数。保证方案数不超过 $ 2 \times 10^9 $ 。

## 做法

首先，可以把暴力代码写出来：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(a[i]!=a[j]) ans++;
	printf("%d",ans);
	return 0;
```

但这样时间复杂度是 $ O(n^2) $ 的，显然过不了。

考虑优化。可以看出，里面的一层循环表示 $ ans $ 加上 $ a $ 数组里和 $ a_i $ 不同的个数。我们就可以用一个桶记录下来每一种书出现的次数记录下来，这个数就是 $ n-t_i $ （ $ t $ 是桶数组）。

这样的话每一种可能性都记录了两次，所以结果要出 $ 2 $ 。题目保证了答案 $ \leq 2 \times 10^9 $ ，所以 $ ans \leq 4 \times 10^9 $ 会爆`int`，用这种方法写**要开**`long long`（如果你想，也可以用` unsigned int `）。

然后就可以愉快地通过了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,cnt[15],a[200005],ans;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		cnt[a[i]]++;
	}
	for(int i=1;i<=n;i++) ans+=(n-cnt[a[i]]);
	printf("%lld",ans/2);
}
```

---

## 作者：SnapYust (赞：0)

## 题目传送门

[The Best Gift](https://www.luogu.com.cn/problem/CF609B)

## 思路

虽然但是，这道题作为绿题还是水了点，建议降橙。

看到这种有 $n$ 个物品，$m$ 个种类的题，很自然的想到**桶**。

最开始先读入 $n$ 和 $n$ 个 $a_i$，对于每个 $a_i$ 都有 $g_{a_i}\leftarrow g_{a_i}+1$，读入完后 $g_{i}(1\le i\le m)$ 即为第 $i$ 种书的本数。

根据乘法原理，假设有 $k$ 本书和 $l$ 本书进行搭配，那会有 $k\times l$ 种方案，易得：

$$ans=\sum^m_{i=1}\sum^m_{j=i+1}{a_ia_j}$$

$m$ 不大，时间复杂度为 $O(m^2)$，可以切爆本题。

代码实现比较简单，就不放代码了。

---

## 作者：Epoch_L (赞：0)

## Solution
记种类 $i$ 有书 $a_i$ 本，那么显然答案为：
$$
\sum_{i=1}^n\sum_{j=i+1}^na_i\times a_j
$$
$$
=\sum_{i=1}^n(a_i\times \sum_{j=i+1}^n)
$$

最后一个求和式在循环时开个变量记一记就可以了，在代码里面就是 $sum$。时间复杂度 $O(n)$。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=2e5+7;
int s[N];
main(){
  int n,m,ans=0,sum=0;read(n);read(m);
  for(int i=1,x;i<=n;i++)read(x),s[x]++;
  for(int i=1;i<=m;i++)sum+=s[i],ans+=s[i]*(n-sum);
  cout<<ans;
  return 0;
}
```

---

## 作者：AzureMist (赞：0)

从 $n$ 本书中选 $2$ 本至多有 $\text{C}_ {n}^{2}$ 种方法，但是这其中还有不可行的。如果一种书的数量多于 $2$ 本，那么就可能选到两本这种书，这些方法就应该被从最初的 $\text{C}_ {n}^{2}$ 中减去（从 $k$ 本相同种类的书中选 $2$ 本共有 $\text{C}_ {k}^{2}$ 种方法）。

AC Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,mfs[11],ans;
int main()
{
	cin>>n>>m;
	ll a[n];
	for(ll i=0;i<=n-1;i++)
	{
		cin>>a[i];
		mfs[a[i]]++;//记录每种书的本数
	}
	ans=n*(n-1)/2;//至多有多少种选书方法
	for(ll i=1;i<=10;i++)
		if(mfs[i]>=2)
			ans=ans-mfs[i]*(mfs[i]-1)/2;//不可行的方法数
	cout<<ans;
	return 0;
}
```

---

## 作者：damage (赞：0)

## 题解

本题就是统计不同种类的书的本数，然后用简单的组合知识即可。

即累加任意两类书数量的成绩，但是因为它是组合，而不是排列，所以没有顺序之分，这样的话会重复，答案$/2$即可。

但是其实只要在最后循环统计答案的时候$j$的循环范围由$i$~$m$变为$i+1$~$m$即可

其实就是求$\sum\limits^{m}_{i=1}\sum\limits^{m}_{j=i+1}C_{i}C_{j}$，其中$C_{i}$表示种类为$i$的书的数量

统计数量的话利用桶的思想即可

> 楼上大佬其实多虑了，原题也说了：

```
It is guaranteed that the answer doesn't exceed the value 2·10^9
```

> 所以根本就没有必要开$long\ long$（但是有这个想法是好的~~谨以$\sout{LL}$纪念今年$\sout{1}$分错失省一大佬学长~~）

---

## 代码

```cpp
#include<stdio.h>
int n,m,x,count[20],res;
int main()
{
	scanf("%d%d",&n,&m);
	while(n--) //重复n次，因为后面n没用不到了，所以可以直接用while省事
	{
		scanf("%d",&x);
		++count[x]; //利用桶的思想
	}
	for(register int i=1;i<m;++i) //注意下一行j的上下界
		for(register int j=i+1;j<=m;++j) res+=count[i]*count[j]; //求和
	printf("%d\n",res);
	return 0;
}
```

~~题解写到一半突然发现黄题变成了绿题~~

---

## 作者：frankchenfu (赞：0)

这道题目并不难，是一道比较基础的组合数学题。

我们考虑统计每种书的数量，然后再暴力枚举所选取两本书的种类，最后累加方案数即可，注意结果要开`long long`。

表示成公式就是$ans=\displaystyle\sum_{i=1}^{m} \displaystyle\sum_{j=i+1}^{m} a_i\times a_j$。

代码：
```cpp
#include<cstdio>
#include<cstring>
const int MAXN=15;
int a[MAXN];

int main()
{
	for(int n,m;scanf("%d%d",&n,&m)==2;memset(a,0,sizeof(a)))
	{
		for(int i=1;i<=n;i++)
		{
			int val;scanf("%d",&val);
			a[val]++;
		}
		long long ans=0;
		for(int i=1;i<=m;i++)
			for(int j=i+1;j<=m;j++)
				ans+=a[i]*(long long)a[j];
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

