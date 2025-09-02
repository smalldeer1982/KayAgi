# [USACO25OPEN] Sequence Construction S

## 题目描述

最近，农夫约翰农场里的奶牛们迷上了观看《炼乳神探》这档节目。节目讲述了一头聪明的奶牛侦探CowCow解决各类案件的故事。贝茜从节目中发现了新的谜题，但答案要等到下周的下一集才会揭晓！请帮她解决这个问题。

给定整数 $M$ 和 $K$ $(1 \leq M \leq 10^9, 1 \leq K \leq 31)$。请选择一个正整数 $N$ 并构造一个包含 $N$ 个非负整数的序列 $a$，满足以下条件：

- $1 \le N \le 100$。
- $a_1 + a_2 + \dots + a_N = M$。
- $\text{popcount}(a_1) \oplus \text{ popcount}(a_2) \oplus \dots \oplus \text{ popcount}(a_N) = K$。

如果不存在这样的序列，输出 $-1$。

$\dagger \text{ popcount}(x)$ 表示整数 $x$ 的二进制表示中 $1$ 的位数。例如，$11$ 的 popcount 是 $3$，$16$ 的 popcount 是 $1$。

$\dagger \oplus$ 表示按位异或运算符。

输入包含 $T$ ($1 \le T \le 5 \cdot 10^3$) 组独立测试用例。

## 说明/提示

在第一个测试用例中，数组 $a = [2, 0]$ 的元素之和为 $2$。其 popcount 的异或和为 $1 \oplus 0 = 1$，因此所有条件均被满足。

在第二个测试用例中，数组 $a = [3, 23, 7]$ 的元素之和为 $33$。其 popcount 的异或和为 $2 \oplus 4 \oplus 3 = 5$，因此所有条件均被满足。

其他有效数组包括 $a = [4, 2, 15, 5, 7]$ 和 $a = [1, 4, 0, 27, 1]$。

可以证明第三个测试用例不存在有效数组。

- 测试点 $2$：$M \leq 8, K \leq 8$。
- 测试点 $3\sim 5$：$M > 2^K$。
- 测试点 $6\sim18$：无额外限制。

## 样例 #1

### 输入

```
3
2 1
33 5
10 5```

### 输出

```
2
2 0
3
3 23 7 
-1```

# 题解

## 作者：Little_x_starTYJ (赞：11)

## 前言
把此题放到 T4 然后模拟考最为期末成绩，目前感觉快 AFO 了。最后 $20 + 100 + 20 + 10 = 150pts$。想要考试的四道原题的家人们可以私信我要题号。

## 解题思路
防止读者在阅读时忘记 $\text{popcount}(x)$ 时什么意思，所以就放在这里了。

$\text{popcount}(x)$ 表示整数 $x$ 的二进制表示中 $1$ 的位数。例如，$\text{popcount}(11) = 3$，$\text{popcount}(16) = 1$。


乍眼一看似乎很不可做的样子，实则因人而异。

赛时看到异或，首先想到 01trie，然后想了一阵发现不会，于是就没想了。

赛后瞅一眼题解，发现了一条重要性质：$\text{popcount}(1) = \text{popcount}(2)$。我赛时怎么没想到！

相信大家看到题目可能会先想着去构造序列 $a$，使得其满足 $a_1 + a_2 + \cdots + a_N = M$ 吧，但是这样很难再进行构造使得 $\text{popcount}(a_1) \oplus \text{popcount}(a_2) \oplus \cdots \oplus \text{popcount}(a_N) = K$，所以我们可以先使得其满足条件 $3$，再来想办法让其满足条件 $2$。

我们先构造一个满足条件的序列 $a$，使此序列的和最小（不是异或和）。其实我们并不需要考虑类似 $x\oplus x = 0, x \oplus x \oplus x = x$ 的情况，我们要求和最小就是为了避免初步构造时出现上述复杂情况（因为如果这些数的某一位上重复出现很多次 $1$，那么它们的总和一定不是最小的，我们可以使得这一位只出现 $0$ 次或 $1$ 次 $1$ 来达到同样的效果），即我们需要一步一步来，不能做到一步到位。

怎么构造和最小且满足条件 $3$ 的序列呢？想到异或与二进制有关，因此可以考虑对于 $K$ 进行二进制分解。这一步可能有点绕且难以描述，所以我们以第二组数据进行模拟再进行解释。

$M = 33, K = 5$，首先二进制分解 $K$ 得到 $(101)_2$，向答案数组里面添加 $2^4 - 1, 1$，因为第一个 $1$ 代表 $2^2 = 4$，所以得到 $2^4 - 1$。

为什么要这么做？别忘了 $K$ 代表的是所有数在二进制下 $1$ 的个数的和，那么将其二进制拆分则代表第 $1$ 个数的 $1$ 的个数为 $4$，那么最小的数即 $(1111)_2 = 2^4 - 1$。

那么我们选出来的这些数即我们的初始元素。将 $M$ 减去这些数的和，记为 $M_2$。
- 如果 $M_2 < 0$，显然无解。
- 否则如果 $M_2 = 0$，那么我们构造的 $a$ 已经同时满足条件 $1,2$ 了，直接输出即可。
- 否则如果 $M_2 = 1$，则我们还差 $1$ 才能同时满足条件 $1,2$。
- - 如果已构造出来的序列中有 $1$，由于 $\text{popcount}(1) = \text{popcount}(2)$，所以我们可以将序列中的 $1$ 变成 $2$ 来达到条件。
- - 如果已构造出来的序列中没有 $1$，那么一定无解，因为不存在某个数与序列中的所有数同时满足为 $2^i,2^j$ 且 $|2^i - 2^j| = 1$。
- 否则如果 $M_2$ 为偶数，直接往答案序列中加入两个 $\frac{M_2}{2}$ 即可（两个相同的数异或后值为 $0$，不影响条件 $3$）。
- 否则即 $M_2$ 为奇数，由于 $\text{popcount}(1) = \text{popcount}(2)$ 且 $M_2 \geq 3$（$M_2 = 1$ 的情况处理过了），因此我们可以从 $M_2$ 中取出来一个 $1$ 和 $2$ 就可以将 $M_2$ 转化为偶数的情况。（因为取出来一个 $2$ 虽然可能会导致 $M_2$ 的二进制排列差异过大，但是取出来一个 $1$ 和 $2$ 过后，后面两个数都为 $\frac{(m - 3)}{2}$，异或后为 $0$，前面只有 $1,2$ 且 $\text{popcount}(1) \oplus \text{popcount}(2) = 0$，所以 $0 \oplus 0 = 0$，$1 + 2 + \frac{(m - 3)}{2} \times 2 = M_2$，所以此方案可行。）

对于条件 $1$ 就懒得说了，大家可以看看代码，满打满算 $5 + 1 + 4 = 10 < 100$。

如果本题解有什么写错的地方可以在评论区踹我一脚，我好修改，没看懂的也可以踹我一脚，我好写得更详细。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> v;
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int m, k, sum = 0;
		cin >> m >> k;
		bool flag1 = false;
		v.clear();
		for (int i = 5; i >= 1; i--) {
			int p = (1 << i);
			if (k >= p) {
				k -= p;
				v.emplace_back((1 << p) - 1);
       //emplace_back = push_back，据说跑得要快点而已。
				sum += (1 << p) - 1;
			}
		}
		if (k) {
			flag1 = true;
			v.emplace_back(1);
			sum++;
		}
		if (sum > m) {
			cout << "-1\n";
			continue;
		}
		m -= sum;
		if (m == 1) {
			if (flag1) {
				v.pop_back();
				v.emplace_back(2);
			} else {
				cout << "-1\n";
				continue;
			}
		} else if (m) {
			if (m & 1) {
				v.emplace_back(1);
				v.emplace_back(2);
				if (m > 3) {
					v.emplace_back((m - 3) / 2);
					v.emplace_back((m - 3) / 2);
				}
			} else {
				v.emplace_back(m / 2);
				v.emplace_back(m / 2);
			}
		}
		cout << v.size() << "\n";
		for (auto u : v) {
			cout << u << ' ';
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：lhz2022 (赞：6)

构造题，题面给的已经很明确了。

首先我们思考：什么时候一定无解？

我们知道，我们需要使构造出来的数组中所有元素的异或和为 $k$，我们拿样例中的第二个来举例，那么它在二进制下是这样的：

$5_{10}=101_2=100_2+1_2=4_{10}+1_{10}$，

那么在数组元素二进制中 $1$ 的个数的异或和一定情况下，这个数组如果要使和最小，那么它一定是这样的：

$[1111_2,1_2]$。

我们令这个最小的和为 $ct$，这个数组为 $a$，那么如果有题目中的 $m<ct$，那么一定无解。

那么有没有一种方案能使这个异或和不变的情况下，增加数组的和呢？

有的兄弟，有的。我们令 $v=m-ct$，开始分类讨论。

如果 $v=0$：直接输出 $a$ 即可。

如果 $v=1$: 如果 $a$ 中含有 $1$，把它改成 $2$ 即可，由于它们在二进制下 $1$ 的个数相同，不会对异或和产生影响。如果没有，则无解。

否则我们把 $v$ 在二进制下表示出来，如果从右往左数第 $i$ 个数是 $1$，那么将 $2^i$ 插入 $a$。举个例子，如果 $v=5_{10}=101_2$，则向 $a$ 中插入 $100_2,1_2$。

这是如果我们插入了偶数次，由于每次插入的元素在二进制下有且仅有一个 $1$，所以最后的异或和不会变，输出即可。

反之，如果插入了奇数次，则将其中的一项 $2^k(k>1)$ 变成两项 $2^{k-1}$ 后输出即可。

最后我们来计算所得的元素最多的个数：

$a$ 数组一开始：最多 $30$ 个数。

根据 $v$ 插入，最多 $30$ 个数。

如果插入了奇数次，则再增加一个数。

满打满算我们构造出的数组也只有 $61$ 个元素，远小于题目中的 $100$ 个元素的限制。

[代码](https://www.luogu.com.cn/paste/94i5u5mz)

---

## 作者：CommandSR (赞：4)

## 题意简述

构造序列使得：

- $1 \le N \le 100$。
- $a_1 + a_2 + \dots + a_N = M$。
- $\text{popcount}(a_1) \oplus \text{ popcount}(a_2) \oplus \dots \oplus \text{ popcount}(a_N) = K$。

若无解输出 $-1$。

## 基本思路

因为 $k$ 是一堆东西的异或和，不难想到对 $k$ 进行二进制分解。

以 $k=5$ 为例，$(5)_{10} = (101)_{2}$。

对于第一位 $1$，它由一个 $x$ 满足 $\text{popcount}(x) = 4$ 贡献而来，这个 $x$ 最小为 $2^4-1 = 15$，故我们将 $15$ 加入序列，同样的对于最后一位 $1$，将 $2^1-1=1$ 加入序列。

该样例对应的 $m=33$，减去 $15$ 和 $1$ 后还剩下 $17$。

我们需要之后的元素 $1$ 的个数异或和为 $0$。

$17$ 是一个奇数，因为 $1$ 和 $2$ 二进制下都只含一个 $1$，我们先从中取出一个 $1$ 和一个 $2$，再取出两个 $(m-3) \div 2$。

对于一个偶数，直接取两个 $n \div 2$ 则满足条件。

考虑无解情况，若 $m$ 在某一步小于了 $0$，则无解。

若剩余的 $m$ 为 $1$，如果当前序列有一个 $1$，改为 $2$ 可以凑出一组解，否则无解。


## AC Code

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define _F(i, a, b) for (int i = a; i >= b; --i)
#define ll long long
using namespace std;
ll rd() {
	ll p = 0, f = 1; char ch = getchar();
	while (ch>'9' || ch<'0') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch>='0' && ch<='9') p = p*10+ch-'0', ch = getchar();
	return p * f;
}
ll m, k, a[110], tot = 0;
void Solve() {
	tot = 0;
	m = rd(), k = rd();
	_F(i, 5, 0) {
		if (k & (1<<i)) {
			ll cur = (1<<(1<<i))-1;
			m -= cur, a[++tot] = cur;
			if (m < 0) {
				cout << -1 << '\n';
				return ;
			}
		}
	}
	if (m == 1) {
		if (a[tot] != 1) {
			cout << -1 << '\n';
			return ;
		}
		++a[tot];
	} else if (m % 2 == 0) {
		a[++tot] = m/2, a[++tot] = m/2;
	} else {
		a[++tot] = 1, a[++tot] = 2, a[++tot] = (m-3)/2, a[++tot] = (m-3)/2;
	}
	cout << tot << '\n';
	F(i, 1, tot) cout << a[i] << ' ';
	cout << '\n';
}
int main() {
	ll T = rd(); while (T--) Solve();
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：3)

这是本蒟蒻写过的最长的题解了，除本句共 2111 字符，可放心食用。

这题实在有点抽象了，简直是本次银组思维含量最高的题了，这数学想法怎么能那么简约、难想呢？！

## 思路分析
本题是一道有关二进制的数学题。

看到题面，数据组数高达 $5⋅10^3$，而需构造的序列长又很小。我们自然想到两种思路：DP 或是数学。然而看到 $1≤M≤10^9$ 的限制，我们便可想到这大概率是数学思维题了。不过看到 $\text{popcount}$ 和异或，我们又陷入了疑惑……

还是特殊性质有提示作用。注意到 $M>2^K$ 特殊性质，这也许是切入点。我们发现，此时可使 $a_1\gets 2^K-1$，则只需使后面的拆分中有偶数个 $2$ 的幂次即可（偶数个 $1$ 异或和为 $0$）。我们知道任何正整数都能二进制拆分。那么假如拆分后有奇数个 $2$ 的幂次呢？我们只需进一步拆解其中一个 $2$ 的幂次即可。此时仅有 $1$ 无法进行此类拆解。**至此，本题第一个玄机顺利破解！**

再看其余情况，二进制拆分的玄机破解后，我们容易想到，只要找出无法满足条件的下界，在下界基础上进行如上拆分，问题就迎刃而解了。**下界是本题的第二个玄机**。  
怎么寻找呢？这就考察我们异或运算的性质了。我们试图再将 $K$ 二进制分解。由于异或运算结果位数不超过参与运算数的位数，而若干数异或运算结果总是不大于该几数相加，因而，要使每个参与的 $\text{popcount}$ 尽可能小，它们应正好符合 $K$ 的为 $1$ 的位，再从而得出尽可能小的 $a_i$（此处不再详细赘述）。  
那么，怎么进一步保证 $a_i$ 和最小呢？注意到当 $a,b$ 为正整数时，$2^a+2^b \le 2^{a+b}$ 恒成立，那么，我们应进一步细细拆分为 $2$ 的整数幂，这样我们就得到了 $M$ 在该 $K$ 下的下限。  
显然，这种拆分方式能保证 $N \le 100$。

另，注意到大于下限的数中与下限正好相差 $1$ 的数依此无法满足，若 $k$ 是奇数，把拆出的 $2^0$ 对应 $a_i$ 由 $1$ 改为 $2$ 即可；否则不能实现。

实现细节见代码。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,m,k,pow2[31]={1};
//T1 is a hard math problem!!!
int main()
{cin>>t;
 for(int i=1;i<=30;i++)
 pow2[i]=pow2[i-1]*2;
 while(t--)
 {cin>>m>>k;
  int j=-1,cnt=0,lim=0,kk=k,a[40]={};
  //二进制拆分k
  while(k>0)
  {j++;
   if(k&1)
   {lim+=pow2[pow2[j]]-1;
    a[++cnt]=pow2[pow2[j]]-1;
   }
   k>>=1;
  }
  if(m<lim)
  {cout<<"-1\n";
   continue;
  }
  if(m==lim+1)
  {if(kk&1)
   {cout<<cnt<<'\n';
    cout<<"2 ";
   for(int i=2;i<=cnt;i++)
   cout<<a[i]<<' ';
   cout<<'\n';
   continue;
   }
   else
   {cout<<"-1\n";
    continue;
   }
  }
  if(m==lim)
  {cout<<cnt<<'\n';
   for(int i=1;i<=cnt;i++)
   cout<<a[i]<<' ';
   cout<<'\n';
   continue;
  }
  int num=m-lim,jj=0,b[40]={};j=0;
  //二进制拆分m-lim
  while(num!=0)
  {if(num&1)
   b[++jj]=pow2[j];
   j++;num>>=1;
  }
  if(jj%2==1)
  {b[jj]=b[jj+1]=b[jj]/2;
   jj++;
  }
  cout<<cnt+jj<<'\n';
  for(int i=1;i<=cnt;i++)
  cout<<a[i]<<' ';
  for(int i=1;i<=jj;i++)
  cout<<b[i]<<' ';
  cout<<'\n';
 }
}
```
附：创作背景：3 月 23 日上午 10:00～11:00，完成 T2，T3 后，面对银组 T1，我焦头烂额地搜索各种算法，终于，数学的想法攻入我的脑海，破解了它。我隐约地感受到，**这是本次银组思维含量最高的题了**。返回比赛题目总界面，上面已写着 AK 的祝贺，我感慨万千：原本只想随便打打，以为不可逾越的银组就这样过了，我可是连 CSP-S 2024 都没拿到一等奖的初二蒟蒻啊！

---

## 作者：Swordmaker (赞：1)

# P12025 [USACO25OPEN] Sequence Construction S

# 思路分析

首先对于 $k$，由于其是一个比较不太寻常的异或和，就可以从进制的方向进行考虑。

考虑对 $k$ 进行二进制分解。

对于一个数，假设其从低位到高位第 $x$ 位为 $1$，其对应的十进制数为 $y$，则该位需要一个 $\text{popcount}(y)=x$ 来进行贡献。

若在操作中出现 $m$ 小于 $0$ 的状态，则无解。

如此操作后，我们还需要剩下的数的 $1$ 的个数异或和为 $1$。

若剩下的数为奇数，则需要：
```
a[++len]=1,a[++len]=2,a[len+1]=a[len+2]=(m-3)/2,len+=2;
```

若剩下的数为偶数，则需要：
```
a[len+1]=a[len+2]=m/2,len+=2;
```

别忘了特判剩下的数为 $1$ 的情况。

# code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e2+5;
int t,m,k,len=0;
int a[N];
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c-'0');
		c=getchar();
	}
	return x*f;
}
void solve()
{
	for(int i=0;i<=5;i++)//二进制分解 
	{
		if(!(k&(1<<i))) continue;
		int x=(1<<(1<<i))-1;
		if(m-x<0)
		{
			cout<<-1<<"\n";
			return;
		}
		m-=x;
		a[++len]=x;
	}
	if(m==1)//特判剩下的数等于1的情况 
	{
		if(a[1]!=1)
		{
			cout<<-1<<"\n";
			return;
		}
		a[1]++;
	}
	else if(!(m&1))//为偶数 
	{
		a[len+1]=a[len+2]=m/2;
		len+=2;
	}
	else//为奇数 
	{
		a[++len]=1;
		a[++len]=2;
		a[len+1]=a[len+2]=(m-3)/2;
		len+=2;
	}
	cout<<len<<"\n";
	for(int i=1;i<=len;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<"\n";
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	t=read();
	while(t--)
	{
		len=0;//多测要清空 
		memset(a,0,sizeof(a));
		m=read(),k=read();
		solve();
	}
	return 0;
} 
```

---

## 作者：chenwenmo (赞：1)

### [P12025 [USACO25OPEN] Sequence Construction](https://www.luogu.com.cn/problem/P12025)

> 简要题意：
>
> 给定 $m(1 \le m \le 10^9)$ 和 $k(1 \le k \le 31)$，要求构造长度为 $n(1 \le n \le 100)$ 的序列，满足 $a_1+a_2+\cdots+a_n=m$，且 $\mathrm{popcount}(a_1)\oplus \mathrm{popcount}(a_2)\oplus\cdots\oplus\mathrm{popcount}(a_n)=k$。

考虑部分分 $m>2^k$，可以构造 $\{a_1=2^k-1,\{b\}\}$，设 $\sum b = x=m-a_1$，

- 若 $x$ 为偶数，构造 $b=\{\frac{x}{2},\frac{x}{2}\}$。
- 若 $x$ 为奇数，构造 $b=\{\frac{x-3}{2},\frac{x-3}{2},1,2\}$。

考虑一般情况，类似地，构造 $\{\{a\},\{b\}\}$，使得 $\sum a+\sum b = m$，$\bigoplus\mathrm{popcount}(a)=k$，$\bigoplus\mathrm{popcount}(b)=0$（这样的构造方案正确性是显然的，因为若存在解，那一定能找出这样一种形式）。

- 假设已经构造出 $a$，
  - 如果 $\sum b>1$，我们可以按照上面的方法构造，
    - 若 $\sum b$ 是偶数，构造 $b=\{\frac{\sum b}{2}, \frac{\sum b}{2}\}$。
    - 若 $\sum b$ 是奇数，构造 $b=\{\frac{\sum b-3}{2}, \frac{\sum b-3}{2},1,2\}$。
  - 如果 $\sum b=0$，显然满足 $b$ 的条件。
  - 如果 $\sum b = 1$ 和 $\sum b<0$，我还不会做，怎么办呢？
- 因为 $\sum b>1$ 的情况已经讨论出来，那么我们可以让 $\sum a$ 尽量小，就能让 $\sum b$ 尽量大。
  - 设 $k=2^{i_1}+2^{i_2}+\cdots+2^{i_p}(i互不相同)$，也就是把 $k$ 二进制上的 $1$ 拆下来，因为我们要保证 $\bigoplus\mathrm{popcount}(a)=k$，因此我们能构造出的 $\sum a$ 最小的 $a$ 序列为 $\{(2^{2^{i_1}}-1),(2^{2^{i_2}}-1),\cdots,(2^{2^{i_p}}-1)\}$，并且是唯一最小的。
  - 这样构造了 $a$ 之后。若 $\sum b > 1$，我们上面已经讨论过了。若 $\sum b<0$，那显然无解了。下面讨论在这种构造下 $\sum b=1$ 的情况。
  - 由于 $\sum b=1$，这样的 $b$ 序列是没办法构造的，于是我们只能让 $\sum a$ 在 $\bigoplus\mathrm{popcount}(a)=k$ 不变的条件下增加 $1$。
  - 发现当且仅当 $1\in a$ 时，把 $1$ 变成 $2$，可以满足条件，也就是 $k$ 为奇数时。
  - $k$ 是偶数时，每次不改变 $\bigoplus\mathrm{popcount}(a)=k$ 的前提下变动 $a$，至少会将 $\sum a$ 加 $2$，因此无解。

---

## 作者：TZR087_42_Chaser (赞：1)

## 闲话

那个 $N \le 100$ 的条件是不是太宽了。用我的思路最多不超过 $10$ 个数。

## 思路

先讨论有解的情况。注意到 $K \le 31$，所以考虑暴力。

第一步：先将 $K$ 转为二进制。以样例 $2$ 为例，$(5)_{10}=(101)_2$。所以我们考虑找一个二进制下有 $4$ 个 $1$ 的数和有 $1$ 个 $1$ 的数。显然，前者最小为 $2^4-1=15$，后者最小为 $2^1-1=1$。从 $33$ 中减去 $15+1=16$，剩余 $17$。

第二步：接下来考虑将 $17$ 拆分为任意多个数，这些数二进制下 $1$ 的个数异或之后为 $0$。由于 $1$ 和 $2$ 在二进制下均只有 $1$ 个 $1$，所以减去 $1+2=3$，剩余 $14$，为偶数，分成 $2$ 个 $7$ 即可。

以上思路得到的结果是 $15\ 1\ 1\ 2\ 7\ 7$。如果按第一步操作之后得到偶数，则直接分成两个相等的数即可。如 $34\ 5$，答案为 $15\ 1\ 9\ 9$。由于 $31$ 的二进制只有 $5$ 位，所以最多只需要 $5+4=9$ 个数就能凑出答案。

接下来考虑无解。一种显然的情况是 $2$ 的（不超过 $K$ 的最大的 $2$ 的整数次幂）次幂减 $1$ 大于 $M$。如样例 $3$ 的 $10\ 5$，至少要有 $1$ 个二进制下有 $4$ 个 $1$ 的数，而这个数最小为 $15$，大于 $10$，故不可能。

还有一种情况，如 $19\ 6$，进行完第一步操作之后只剩下 $19-15-3=1$，也不可能。

最后就是在进行第一步操作后，$M$ 已经减少到负数，如 $17\ 7$，最少需要 $15+3+1=19$，执行完后 $M=-2$，同样不可能。

于是本题就非常欢愉的结束了。

## 赛时代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,m,k,cnt,a[105];
const int bin[]={0,65535,255,15,3,1};
int find(int k,int m){
	int i=0;
	while((((1<<k)-1)<<i)<=m)i++;
	return ((1<<k)-1)<<(i-1);
}
int maxbin(int m){
	return 1<<(int(log2(m)));
}
void solve(){
	cin>>m>>k;cnt=0;
	if((1<<k)-1==m){
		cout<<1<<endl<<m<<endl;
		return;
	}
	if((1<<maxbin(k))-1>=m){
		cout<<-1<<endl;
		return;
	}
	for(int i=1;i<=5;i++){
		if((k&(int(log2(bin[i]+1))))){
			if(m>=bin[i])a[++cnt]=bin[i],m-=bin[i];
			else{
				cout<<-1<<endl;
				return;
			}
		}
	}
	if(m==1){
		if(a[cnt]!=1){
			cout<<-1<<endl;
			return;
		}
		a[cnt]++;
	}
	else if(m&1){
		a[++cnt]=(m-3)/2;
		a[++cnt]=(m-3)/2;
		a[++cnt]=1;
		a[++cnt]=2;
	}
	else{
		a[++cnt]=m/2;
		a[++cnt]=m/2;
	}
	cout<<cnt<<endl<<a[1];
	for(int i=2;i<=cnt;i++){
		cout<<" "<<a[i];
	}
	cout<<endl;
}
int main(){
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：tiantianyang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12025)

### 题目大意

题目大意明确，并且很清楚可以发现是一道构造题。

### 思路

他要我们满足两个条件：

- $a_1 + a_2 + a_3 + \cdots + a_n = M$。
- $a_1$ 二进制下一的个数 $\operatorname{xor} a_2$ 二进制下一的个数 $\operatorname{xor} \cdots\operatorname{xor} a_n$ 二进制下一的个数 $= K$。

很明显第二个条件更难实现所以我们先考虑实现这一个。我们先来枚一组，看看：

当 $k=8$ 时，很明显 $a_1=(11111111)_{2}$ 这种方法肯定是满足的，将 $k$ 个位全叠上 $1$，但是很明显这种方法的和肯定不是最小的，他达到了 $255_{10}$。

而最优的方法应该是 $8_{10}=(101)_{2}=(100)_{2}+(1)_{2}=(100)_{2}\operatorname{xor}(1)_{2}=4_{10}\operatorname{xor}1_{10}$ 所以 $a_1=(1111)_{2}$ 以及 $a_2=(1)_{2}$ 将其每一个位上的 $1$ 都单独拎出来计算，这样整体的和最小只有 $16_{10}$ 我们把这个数设为 $minm$。

现在我们就来分类讨论一下：

- $m<minm$ 我们可以得知 $minm$ 已经是最小的值了，所以当 $m<minm$ 时可以得出是无解的。
- $m=minm$ 我们就可以直接得出 $a_1=minm$，直接得到答案。
- $m=minm+1$ 我们再次分为两种情况讨论 $minm\operatorname{and} 1=1$ 则 $a_1= minm-1，a_2=2$
 $minm\operatorname{and} 1\ne 1$ 则无解。

为什么会有这样的情况呢？因为 $2$ 与 $1$ 拥有一的个数是相同的，我们可以将 $1$ 替换成 $2$ 来让 $a_1+a_2$ 多 $1$。

- $m>minm$ 我们可以发现现在 $k$ 的情况已经满足了，但是第一个条件还差 $m-minm$ 将其设为 $c$。所以后面的 $a$ 的异或值必须为零，如果 $c$ 为偶数则可以分为 $c/2$ 和 $c/2$，如果为奇数则可以分为 $(c-3)/2,(c-3)/2,1$ 和 $2$（这也用到了刚才说的 $2$ 与 $1$ 拥有一的个数是相同的）。

大体思路已经说清楚了，剩下的就来看代码吧。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;	
int T,m,k,x,d,flag; 
int main(){ 
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>m>>k;
		vector<int> a;x=0;
		for(int i=0;i<5;i++)
			if(k&(1<<i)){a.push_back((1<<(1<<i))-1);x+=a.back();}//计算有哪些位含有一
		
		d=m-x;//算出差值
		vector<int> b;flag=0; 
		if(d<0) flag=1;//m<minm
		else if(d>=2){
			if(d%2==0) b={d/2,d/2};//d为偶
			else b={1,2,(d-3)/2,(d-3)/2};//d为奇
		}else if(d==0) b={};//d为零不需要其他数
		else if(a[0]==1) a[0]=2;//minm+1==m 且 k&1==1
		else flag=-1;//否则无解
		if(flag)cout<<"-1\n";
		else{
			cout<<a.size()+b.size()<<endl;
			for(int i:a) cout<<i<<" ";
			for(int i:b) cout<<i<<" ";
			cout<<endl;
		}
	}
	return 0;//完美收官
}
```

---

## 作者：Carey2012 (赞：0)

## 传送门
>[传送门](/problem/P12025)
## 思路
先看看这个序列 $a$ 的生成方式。
>给定整数 $M$ 和 $K$ $(1 \leq M \leq 10^9, 1 \leq K \leq 31)$。请选择一个正整数 $N$ 并构造一个包含 $N$ 个非负整数的序列 $a$，满足以下条件：
>
>- $1 \le N \le 100$。
>- $a_1 + a_2 + \dots + a_N = M$。
>- $\text{popcount}(a_1) \oplus \text{ popcount}(a_2) \oplus \dots \oplus \text{ popcount}(a_N) = K$。
> 
>$\dagger \text{ popcount}(x)$ 表示整数 $x$ 的二进制表示中 $1$ 的位数。例如，$11$ 的 popcount 是 $3$，$16$ 的 popcount 是 $1$。\
>$\dagger \oplus$ 表示按位异或运算符。

通过这个序列的生成方式，可以得到满足 $K$ 的最小整数 $M$ 和最小序列 $a$，\
我们先设这个序列为 $b$，最小整数为 $M_{min}$，则我们要解决的是 $M-M_{Min}$。

### 第一种：$M-M_{Min} < 0$
因为给出的 $M$ 小于 $M_{Min}$，依照题意，应该输出`-1`。
### 第二种：$M-M_{Min} = 0$
很明显，$M$ 正好与 $M_{Min}$ 相等，直接输出 $b$。
### 第三种：$M-M_{Min} = 1$
最为特殊的情况，处理样例中`2 1`的情况。
### 第四种：$M-M_{Min} > 1$
设 $N = M-M_{Min}$，因为两个相同的数异或之后为 $0$，\
并且两个相同的数的 $1$ 的位数也相同，\
所以只需额外添加两个 $\frac{N}{2}$ 即可，但前提是 $n$ 为偶数，\
那 $n$ 为奇数呢？\
我们只需塞入 $1,2,\frac{N-3}{2},\frac{N-3}{2}$ 即可。

## data([AC_link](https://www.luogu.com.cn/record/221549123))
```CPP
//#pragma GCC optimianse(2)
//#define gets(S) fgets(S,sianseof(S),stdin);
#include<bits/stdc++.h>
//#define f first
//#define s second
using namespace std;
const int MAX=2e5+10,NAX=1e6,mod=1e9+7;
const long double eps=1e-6;
typedef long long ll;
typedef pair<ll,ll> pll;
int lowbit(int x){return x&(-x);}
int t;
int m,k;
int Min;
vector<int> ans;
int main(){
	scanf("%d",&t);
	while(t--){
		ans.clear();
		Min=0;
		scanf("%d%d",&m,&k);
		for(int i=0;i<5;i++){
			if(k&(1<<i)){
				ans.push_back((1<<(1<<i))-1);
				Min+=ans.back();
			}
		}
		int x=m-Min;
		if(x<0){
			printf("-1\n");
			continue;
		}else if(x>1){
			if(x%2){
				ans.emplace_back(1);
				ans.emplace_back(2);
				ans.emplace_back((x-3)/2);
				ans.emplace_back((x-3)/2);
			}else{
				ans.emplace_back(x/2);
				ans.emplace_back(x/2);
			}
		}else if(x==0){/*占位符QwQ*/}
		else if(ans[0]==1){ans[0]=2;}
		else{
			printf("-1\n");
			continue;
		}
		printf("%d\n",ans.size());
		for(auto it:ans){printf("%d ",it);}
		puts("");
	}
	return 0;
}
```

---

