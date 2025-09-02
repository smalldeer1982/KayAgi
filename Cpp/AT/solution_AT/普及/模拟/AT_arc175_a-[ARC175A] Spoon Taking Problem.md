# [ARC175A] Spoon Taking Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc175/tasks/arc175_a

$ N $ 人が円卓に座っており，各人は反時計回りに順に $ 1,\ \ldots,\ N $ と番号付けられています．各人はそれぞれ左右どちらか一方の利き手を持っています．

円卓上には $ 1,\ \ldots,\ N $ と番号付けられた計 $ N $ 本のスプーンが，隣り合う二人の間に $ 1 $ 本ずつ置いてあります．各 $ 1\ \leq\ i\ \leq\ N $ について，人 $ i $ の左側，右側にはそれぞれスプーン $ i $，スプーン $ (i+1) $ があります．ここで，スプーン $ (N+1) $ はスプーン $ 1 $ のことを指します．

$ N\ =\ 4 $ での模式図を以下に示します．

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc175_a/e6f0a6024a199111c69d24084c2b3068c72489fd.png)

$ (1,\ \dots,\ N) $ の順列 $ (P_1,\ \dots,\ P_N) $ が与えられます．$ i=1,\dots,N $ の順に，人 $ P_i $ が以下のように行動します．

- 自分の右側または左側にスプーンが残っているならば，そのうち $ 1 $ つを取る． 
  - このとき自分の両側にスプーンが残っているならば，自分の利き手の側のスプーンを取る．
- そうでないならば何もしない．
 
`L`, `R`, `?` からなる長さ $ N $ の文字列 $ S $ が与えられます．$ N $ 人の利き手の組み合わせは $ 2^N $ 通りありますが，そのうち以下の条件を全て満たすような組み合わせの数を $ 998244353 $ で割った余りを求めてください．

- $ S $ の $ i $ 番目の文字が `L` ならば，人 $ i $ は左利きである．
- $ S $ の $ i $ 番目の文字が `R` ならば，人 $ i $ は右利きである．
- 全員の行動が終了したとき，全員がスプーンを取っている．

## 说明/提示

### 制約

- 入力される数値は全て整数
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ (P_1,\ \dots,\ P_N) $ は $ (1,\ \dots,\ N) $ の順列
- $ S $ は `L`, `R`, `?` からなる長さ $ N $ の文字列
 
### Sample Explanation 1

人 $ 1,2,3 $ がそれぞれ左利き，左利き，右利きのとき，以下のように行動が行われます． - 人 $ 1 $ が行動を開始する．人 $ 1 $ の両側にスプーンが残っているので，人 $ 1 $ の利き手と同じ左側のスプーン $ 1 $ を取る． - 人 $ 2 $ が行動を開始する．人 $ 2 $ の両側にスプーンが残っているので，人 $ 2 $ の利き手と同じ左側のスプーン $ 2 $ を取る． - 人 $ 3 $ が行動を開始する．人 $ 3 $ の右側にはスプーンが残っておらず，左側にはスプーン $ 3 $ が残っているので，スプーン $ 3 $ を取る．全員の行動が終了し，このとき全員がスプーンを取っている． この利き手の組み合わせは条件を満たします．他には人 $ 1,2,3 $ がそれぞれ左利き，左利き，左利きの場合も条件を満たします．

### Sample Explanation 2

条件を満たす利き手の組み合わせが存在しません．

## 样例 #1

### 输入

```
3
1 2 3
L??```

### 输出

```
2```

## 样例 #2

### 输入

```
3
1 3 2
R?L```

### 输出

```
0```

## 样例 #3

### 输入

```
12
6 2 9 3 1 4 11 5 12 10 7 8
????????????```

### 输出

```
160```

# 题解

## 作者：whrwlx (赞：3)

# 题目翻译 [link](https://www.luogu.com.cn/problem/solution/AT_arc175_a)

有 $N$ 人围坐在一张**圆桌**旁，按逆时针顺序编号为 $1$ 至 $N$。每个人都有一个惯用手。

圆桌上有 $N$ 把勺子，编号为 $1$ 到 $N$，每对相邻的人之间放一把勺子。

给你一个 $(1, \dots, N)$ 的排列组合 $(P_1, \dots, P_N)$。在 $i=1,\dots,N$ 的顺序中，人 $P_i$ 的行为如下：

- **如果两边都有剩余的勺子，他们会拿自己惯用手一边的勺子；**
	- **如果左侧或右侧有剩余的勺子，他们将拿走其中一个；**
- **否则，他们什么也不会做。**

给出了一个长度为 $N$ 的字符串 $S$，由 `L`、`R` 和 `?` 组成：

- 如果 $S_i$ 是 "L"，那么 $i$ 是左撇子；
- 如果 $S_i$ 是 "R"，那么 $i$ 是右撇子。

在 $2^N$ 个可能的主手组合中，**找出有多少个满足以下所有条件的** $s$，模数为 $998244353$：

**当每个人都行动完后，每个人都拿了一把勺子。**

# 方法

## 法一

暴力枚举每种可能的 $s$，然后检验。

时间复杂度 $O{(2^X N)}$， $X$ 为 `?` 的个数。

## 法二

### 分析

**我们可以发现对于一个满足条件的 $S$ ，每个人都应该拿与第一个拿的人同侧的勺子。**

于是：

我们可以**分类讨论**：

讨论第一个拿的人是拿左边还是右边：

- 若为 `R` 只讨论右边；
- `L` 只讨论左边；
- `?` 讨论两种最后求和。

每个人拿的方向应与第一个拿的人一致，然后找规律。

#### 规律

（注：这里类似 “$P_i$ 为 `L`” 的语句其实是 “$S[P_i]$ 为 `L`”，为了简便记作 $P_i$）。

若第一个拿的人拿左边。

>对于第 $P_i$ 个人来说：
>- 如果他右边的人 $r$ 已经先拿过他左边的勺子，那么 $P_i$ 可以为 `L` 或`R`，那么 $ans$ 乘 $2$（注意，若 $P_i$ 确定，$ans$ 不变）；
>- 如果他右边的人 $r$ 后拿，那么他只能拿左边的勺子，$ans$ 不变；
>- 如果他右边的人 $r$ 没有先拿过他左边的勺子且 $P_i=$ `R`，那么第一个拿的人拿左边的情况无解，即 $ans=0$。

若第一个拿的人拿右边，可类似若第一个拿的人拿左边推出。

~~这里为了简短就不写啦。~~

**注意取模！！！~~你猜我怎么知道的~~ 警示后人。**

**代码实现：**

```c++
#include<bits/stdc++.h>
#define put(n) scanf("%lld",&n) 
#define out(n) printf("%lld\n",n)
#define int long long
#define fd(i,a,b) for(int i=a;i<=b;i=-~i)
using namespace std;
int n,p[1000100],f[1000100],mod=998244353;
//f记录第i个人第几个拿
char s[1000100];
int ans1=1,ans2=1;// 拿左边 拿右边
signed main()
{
	put(n);
	fd(i,1,n) put(p[i]),f[p[i]]=i;
	fd(i,1,n) cin>>s[i];
	//第一个拿的人拿左边
	fd(i,1,n)
	{
		int r=p[i]+1;//r 当前拿的人右边的人的编号
		if(r==n+1) r=1;//小坑
		if(s[p[i]]=='?')
		{
			if(f[r]<i) ans1*=2;
			ans1%=mod;
		}
		else if(s[p[i]]=='R')
		{
			if(f[r]>i)
			{
				i=n+1;
				ans1=0;
				break;
			}
		}
	}
	//第一个拿的人拿右边
	fd(i,1,n)
	{
		int l=p[i]-1;//l 当前拿的人左边的人的编号
		if(l==0) l=n;//小坑
		if(s[p[i]]=='?')
		{
			if(f[l]<i) ans2*=2;
			ans2%=mod;
		}
		else if(s[p[i]]=='L')
		{
			if(f[l]>i)
			{
				i=n+1;
				ans2=0;
				break;
			}
		}
	}
	if(s[p[1]]=='R') out(ans2);
	else if(s[p[1]]=='L') out(ans1);
	else out((ans1+ans2)%mod);//如果Pi为?那么算两种情况之和
	return 0;
}
```

upd: `误解` 改为 `无解`。

---

## 作者：KSCD_ (赞：2)

# 题意
在一个环上有 $N$ 个人，每两人之间有一把勺子，所有人按照 $P$ 排列顺序操作。一人操作时若左右都有勺子，则拿自己惯用手那边的；若只有一边有勺子，则直接拿；若无勺子则不操作。

给定 $P$ 和某些人的惯用手，求能使所有人都拿到勺子的惯用手方案数。
# 思路
如果把这个环画出来，环上就是一个人一个勺子交叉，如此重复 $N$ 组。

模拟一下就会发现，若某两人选择勺子的方向不同，则他们之间剩下的勺子数与人数之和为奇数，这样一定不合法。

所以我们得到，合法的**取法**只有两种，即所有人都取自己左手边的勺子，或所有人都取自己右手边的勺子。

那么只需要模拟取两次，每次都直接钦定每个人所拿的勺子，再按 $P$ 的顺序依次处理。

处理时，若不拿的另一把勺子还在，就必须确定惯用手以拿到指定的那把，此时若与 $S$ 中给出的信息冲突则无解；若另一把已经不在了，那么惯用手任意，此时若给出信息为问号则方案数乘 $2$。

此处不需要考虑自己要拿的勺子是否已被取走，因为每个人都只会取自己对应的那把勺子，不会出现拿别人勺子的情况。

最后把两种取法对应的方案数相加即可。

# 代码
```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int N=2e5+10;
const int mod=998244353;
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') w=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){ s=s*10+ch-'0'; ch=getchar();}
    return s*w;
}
int n,sa=1,sb=1,p[N]; 
char s[N];
bool v[N];//勺子是否被取走 
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) p[i]=read();
	cin>>s;
	for(int i=1;i<=n;i++)//所有人都取左手边的 
	{
		if(v[(p[i]%n)+1]) //若另一把已被取走，则惯用手任意 
		{
			if(s[p[i]-1]=='?') sa=(sa*2)%mod;//若是问号则乘2 
		}
		else if(s[p[i]-1]=='R') //另一把未被取走，则需确定惯用手 
		{
			sa=0;
			break;
		}//此时若与给定信息冲突则无解 
		v[p[i]]=1;//标记已取走 
	}
	memset(v,0,sizeof(v));
	for(int i=1;i<=n;i++)//都取右手边的，同上 
	{
		if(v[p[i]]) 
		{
			if(s[p[i]-1]=='?') sb=(sb*2)%mod;
		} 
		else if(s[p[i]-1]=='L')
		{
			sb=0;
			break;
		}
		v[(p[i]%n)+1]=1;
	}
	cout<<(sa+sb)%mod;
	return 0;
}
```

---

## 作者：JuRuoOIer (赞：1)

# 题解 ARC175A - Spoon Taking Problem

[**B 题题解**](https://www.luogu.com.cn/article/qkwiu6uw/)

前排提示：本题解为 **模拟** 做法。

### 警钟

赛时由于把两次模拟的答案加在一起时忘记取模，导致吃了 $5$ 发罚时，并额外调了 $20$ 分钟，最终 perf 从约 $1620$ 掉到 $1382$，少上了好几十分。

### 题意

已提交翻译。

$n$ 个人围成一圈坐在圆桌旁，编号分别为 $1$ 到 $n$，插空放了 $n$ 把勺子，一个空放一把。给定一个长度为 $n$ 的**排列** $p$，这 $n$ 个人按照 $p_1,p_2,...,p_n$ 的顺序拿勺子，具体规则如下：
- 如果两边都有勺子，则拿惯用手的一边；
- 如果只有一边，则拿这一边的；
- 如果没有就不拿。

现在给定一个长度为 $n$ 的字符串 $S$，由 `L`、`R` 和 `?` 构成，`L` 表示惯用左手，`R` 表示惯用右手，`?` 表示未知。求有多少种填补 `?` 的方式，使得每个人都能拿到勺子，对 $998244353$ 取模。

数据范围：$2 \le n \le 2\times10^5$。

### 做法

首先一个非常重要的性质：无论惯用手如何，符合要求的填法中，**每个人最终拿到的都是自己同一边的勺子**。

原因很简单，因为如果不满足则一定存在相邻的两个人，一个拿左边一个拿右边，这时他俩中间的那个就拿不走了，而勺子数量是刚好的，所以显然不行。

于是我们分别强制全拿左边或右边来模拟。以拿左边为例，用一个变量记录答案（初始为 $1$），过程如下：
- 如果当前这个人两边都有，则惯用手不能为右手，否则无解退出循环。
- 如果当前这个人只有左边有，则惯用手任意，此时如果这个人惯用手未知，则答案乘 $2$。
- 其他情况不会出现，因为前面我们已经退出循环了。

全拿右边完全同理。最后把两个答案加在一起即可。**注意一定要再次取模！！！**

时空复杂度均为 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
const ll mod=998244353;
ll n,a[2000010],b[2000010],vis[2000010],flgl,flgr,ans=1,ans2;
string s;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		a[i]--;
	}
	cin>>s;
	for(int i=0;i<n;i++){
		if(vis[a[i]]||vis[(a[i]+1)%n]){
			vis[a[i]]=1;
			vis[(a[i]+1)%n]=1;
			if(s[a[i]]=='?')ans*=2;
			ans%=mod;
		}
		else{
			if(s[a[i]]=='R'){
				ans=0;
				break;
			}
			vis[a[i]]=1;
		}
	}
	memset(vis,0,sizeof(vis));
	ans2=ans;
	ans=1;
	for(int i=0;i<n;i++){
		if(vis[a[i]]||vis[(a[i]+1)%n]){
			vis[a[i]]=1;
			vis[(a[i]+1)%n]=1;
			if(s[a[i]]=='?')ans*=2;
			ans%=mod;
		}
		else{
			if(s[a[i]]=='L'){
				ans=0;
				break;
			}
			vis[(a[i]+1)%n]=1;
		}
	}
	cout<<(ans+ans2)%mod;
	return 0;
}

```

---

## 作者：zhujiangyuan (赞：1)

[[ARC175A] Spoon Taking Problem](https://www.luogu.com.cn/problem/AT_arc175_a)

Atcoder problems 评分：$\color{SeaGreen}{1132}$。

赛时切掉，忘取模罚时一发，恼。

其实这道题是个诈骗题。**仔细读题可以发现这 $n$ 个人或是都取左边的勺子，或是都取右边的勺子。如果一个人取左边且有另一个人取右边，那么最后一定有一个人取不到勺子。**

如果想明白了上面的道理，题也就不难写了。

考虑都选左边的和都选右边的两种情况，最后把方案数累加即可。

考虑都选左边的情况：
- 当前人的惯用手是左手，则判断他左边的勺子是否被取走。如果被取走，则**不存在都选左边的情况**，退出循环；如果没有被取走，将左边的勺子标记为被取走。

- 当前人的惯用手是右手，则判断他右边的勺子是否被取走。如果没有被取走，则**不存在都选左边的情况**，退出循环；如果被取走，将左边的勺子标记为被取走。

- 当前人的惯用手不确定。则判断他左边的勺子是否被取走。如果被取走，则**不存在都选左边的情况**，退出循环；如果左边勺子没有被取走，再判断右边的勺子是否被取走，如果右边勺子被取走，则将左边的勺子标记为被取走，答案乘 $2$（因为惯用手有两种选法），否则将左边的勺子标记为被取走。

一些细节：
- 第 $i$ 个人左边的勺子编号为 $i$，右边的勺子编号为 $i \bmod n + 1$；
- 记得对 $998244353$ 取模。

都选左边代码（都选右边同理）：

```cpp
//都用左手
	bool flag=0;
	LL ans1=1,ans2=1;
	for(int i=1;i<=n;i++)
	{
		if(s[p[i]]=='R')//惯用手为右手
		{
			if(vis[p[i]%n+1]){flag=1;break;}
			else vis[p[i]]=0;
		}
		else if(s[p[i]]=='L')//惯用手为左手
		{
			if(!vis[p[i]]){flag=1;break;}
			else vis[p[i]]=0;
		}
		else//惯用手不确定
		{
			if(vis[p[i]]&&vis[p[i]%n+1]) vis[p[i]]=0;
			else if(vis[p[i]]) vis[p[i]]=0,ans1=(ans1<<1)%mod;//两种选法
			else {flag=1;break;}
		}
	}
	if(flag) ans1=0;
```
[完整代码](https://atcoder.jp/contests/arc175/submissions/51770504)，时间复杂度 $O(n)$。

如果觉得这篇题解写得好，请不要忘记点赞，谢谢！

---

## 作者：Sorato_ (赞：0)

# ARC175A Spoon Taking Problem

## 题目大意

有 $n$ 个人围成一个环，第 $i$ 个人左手边是第 $i$ 个勺子，右手边是第 $i\bmod n+1$ 个勺子。每个人的惯用手用一个字符 $a_i=$ `L`/`R`/`?` 表示，即左手/右手/未知。

给定 $1\sim n$ 的一个排列 $P_1,\dots,P_n$ 表示这 $n$ 个人行动的顺序。第 $i$ 个人行动时，若他两边的勺子都没被拿走，他将拿走惯用手那边的，否则拿走有勺子那边的。

问存在多少种惯用手组合，使得每个人恰好拿到一个勺子。

## Solve

有一个性质：所有人要么都拿左手边，要么都拿右手边的。因为对于相邻的两人，如果左边的选左手，右边的选右手，那么他们之间的勺子就没人拿了，显然是非法的。

接下来考虑什么情况会对答案产生贡献。

当全部选左手时，如果一个人的右边已经被选过，此时不管他的惯用手是什么，他都只能选左手。所以有：

记答案为 $ans$，初值为 $1$。用 $vis_i$ 表示第 $i$ 个勺子是否被选过。若 $a_i=$ `?` 且 $vis_{i\bmod n+1}=1$，则 $ans=ans\times2$。

什么情况会无解呢？显然，如果一个人惯用手为右手且到他行动时右手的勺子未被拿走，那么他会选择右手边的，此时不符合全部选左手。即：

若 $a_i=$ `R` 且 $vis_{i\bmod n+1}=0$，则 $ans=0$。

全部右手时同理。

## Code

```c++
#include<bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
using namespace std;
#define int long long
#define mod 998244353
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
inline int readc()
{
	char c=getchar();
	while(c==' '||c=='\n')	c=getchar();
	return c;
}
int n,p[200010],ans;
char a[200010];
bool vis[200010];
inline int calc(int op/*全部左(0)/右(1)手*/)
{
	int sum=1;
	for(int i=1;i<=n;i=-~i)	vis[i]=0;
	vis[p[1]+op]=1;
	for(int i=2;i<=n;i=-~i)
	{
		if((!vis[p[i]%n+1]&&!op&&a[p[i]]=='R')
			||(!vis[p[i]]&&op&&a[p[i]]=='L'))
			return 0;
		if((vis[p[i]%n+1]&&!op&&a[p[i]]=='?')
			||(vis[p[i]]&&op&&a[p[i]]=='?'))
			sum=(sum<<1)%mod;
		if(!op)	vis[p[i]]=1;
		else	vis[p[i]%n+1]=1;
	}
	return sum;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i=-~i)	p[i]=read();
	for(int i=1;i<=n;i=-~i)	a[i]=readc();
	if(a[p[1]]=='L'||a[p[1]]=='?')	ans+=calc(0);
	if(a[p[1]]=='R'||a[p[1]]=='?')	ans=(ans+calc(1))%mod;
	return printf("%lld",ans),0;
}
```

---

## 作者：Elysian_Realme (赞：0)

# ARC175A

## 解题思路

易得：如果在一种方案中有一个人拿了左边的，一个人拿了右边的，总可以导出他们拿的这一边会有一个人左右都空了（手模几遍样例可得）。

那么代码就好写了，先摸拟一遍都拿右边，再模拟一遍都拿左边，结果数加起来即可。

```cpp
// Problem: A - Spoon Taking Problem
// Contest: AtCoder - AtCoder Regular Contest 175
// URL: https://atcoder.jp/contests/arc175/tasks/arc175_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-04-05 19:02:09

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int sum,ans;
int n,p[200005];
bool tk[200005];
string s;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>p[i];
	cin>>s;s=" "+s;
	sum=1;
	for(int i=1;i<=n;i++){
		if(tk[p[i]]||tk[p[i]%n+1]){
			if(s[p[i]]=='?')
				sum*=2;
		}else{
			if(s[p[i]]=='R'){
				sum=0;break;
			}
		}sum%=mod,tk[p[i]]=1;;
	}
	ans+=sum,sum=1;
	memset(tk,0,sizeof(tk));
	for(int i=1;i<=n;i++){
		if(tk[p[i]]||tk[p[i]%n+1]){
			if(s[p[i]]=='?')
				sum*=2;
		}else{
			if(s[p[i]]=='L'){
				sum=0;break;
			}
		}sum%=mod,tk[p[i]%n+1]=1;;
	}
	ans+=sum;
	cout<<ans%mod<<endl;
	return 0;
}

```

---

## 作者：wyyqwq (赞：0)

发现一个性质，要么所有人都拿左手，要么所有人都拿右手，若有人拿左手有人拿右手，则不会满足条件。

**考虑都选左边：**

若当前人右边的人取过了，于是无论当前这个人是左撇子还是右撇子都只会取左边，如果这个人是惯用手未知，答案乘 $2$ 即可。

若当前人右边的人没取过，如果这个人惯用手为右手，则退出循环，因为不符合都取左边的条件。



取右边的情况相似，类比去写就行。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 7;
const int mod = 998244353;
int p[N];
int ans1 = 1, ans2 =1;
string s;
int flag;
int vis[N];
signed main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> p[i];
    cin >> s;
    s = ' ' + s;
    //left
    flag = 1;
    for(int i = 1; i <= n; i ++) {
        int r = (p[i] == n) ? 1 : p[i] + 1;
        if(vis[r]) {
            if(s[p[i]] == '?') ans1 *= 2, ans1 %= mod;
        }
        else {
            if(s[p[i]] == 'R') {
                flag = 0;
                break;
            }
        }
        vis[p[i]] = 1;
    }
    ans1 *= flag;
    flag = 1;
    memset(vis, 0, sizeof vis);
    for(int i = 1; i <= n; i ++) {
        int l = (p[i] == 1) ? n : p[i] - 1;
        if(vis[l]) {
            if(s[p[i]] == '?') ans2 *= 2, ans2 %= mod;
        }
        else {
            if(s[p[i]] == 'L') {
                flag = 0;
                break;
            }
        }
        vis[p[i]] = 1;
    }
    ans2 *= flag;
    cout << (ans1 + ans2) % mod << endl;
}
```

---

## 作者：TankYu (赞：0)

可以注意到，第一个拿勺子的人拿完勺子以后事实上所有人拿哪个勺子已经确定。

这是因为假设第一个拿勺子的人拿左手边勺子，则第一个拿勺子的人左边的人也得拿左手边勺子，同理可得所有人都得拿左手边勺子。第一个拿勺子的人拿右手边勺子是同理的。

接下来就可以直接考虑贡献。

对一个人，如果他的惯用手不确定，此时他身边若有两个勺子则他必须取和第一个拿勺子的人相同方向的勺子，故此时没贡献，若他身边只有一个勺子，则他惯用手哪边都可以，此时答案乘上 $2$。

注意可能无解。

对于第一个拿勺子的人惯用手未知的情况，只需枚举他的惯用手即可。

```cpp
// 记第i个人右边的勺子是spoon[i]
// 那第i个人左边的勺子就是spoon[i - 1]
// 第一个人左边的勺子是spoon[n]

LL ans;
S s;
int spoon[200010];
int p[200010];
int n;

int L(int x)
{
    if (x == 1)
    {
        return n;
    }
    return x - 1;
}

int R(int x)
{
    return x;
}

const LL mod = 998244353;

LL check()
{
    LL ans = 1;
    for (int i = 1; i <= n; i++)
    {
        spoon[i] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        int x = p[i];
        if (spoon[L(x)] + spoon[R(x)] == 0)
        {
            return 0;
        }
        else if (spoon[L(x)] + spoon[R(x)] == 1)
        {
            spoon[L(x)] = spoon[R(x)] = 0;
            if (s[x] == '?')
            {
                ans *= 2;
                ans %= mod;
            }
        }
        else
        {
            if (s[x] != '?' && s[x] != s[p[1]])
            {
                return 0;
            }
            else
            {
                if (s[p[1]] == 'L')
                {
                    spoon[L(x)] = 0;
                }
                else
                {
                    spoon[R(x)] = 0;
                }
            }
        }
    }
    return ans;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    cin >> s;
    s = ' ' + s;
    if (s[p[1]] == '?')
    {
        s[p[1]] = 'L';
        ans += check();
        s[p[1]] = 'R';
        ans += check();
    }
    else
    {
        ans += check();
    }
    cout << ans % mod;
    return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

非常好滞胀题，使我 performance 疯狂贬值。

# 正文

显然每个人都只能统一从左手或右手拿勺子，因为勺子守恒。

那么我们分别钦定这两种情况。先考虑全部从左边拿勺子。

考虑到第 $i$ 位。如果他的右手边那位（或者叫他第 $i + 1$ 位）比他先拿了勺子，那么这位老哥是啥惯用手都没关系；如果他的右手边那位比他后拿勺子，那么这位老哥只能是左撇子

（否则这位老哥如果是右撇子，因为两边都有勺子，所以他会先拿他右手边的勺子，不符合我们钦定的情况了）。

这样我们就讨论完了。全部从右边拿勺子的情况亦然。

# 代码

参照：[Atcoder 官方题解代码](https://atcoder.jp/contests/arc175/submissions/51499067)

---

