# Permutation Sum

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

Petya decided to introduce the sum operation on the set of permutations of length $ n $ . Let's assume that we are given two permutations of length $ n $ : $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ . Petya calls the sum of permutations $ a $ and $ b $ such permutation $ c $ of length $ n $ , where $ c_{i}=((a_{i}-1+b_{i}-1)\ mod\ n)+1 $ $ (1<=i<=n) $ .

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Obviously, not for all permutations $ a $ and $ b $ exists permutation $ c $ that is sum of $ a $ and $ b $ . That's why Petya got sad and asked you to do the following: given $ n $ , count the number of such pairs of permutations $ a $ and $ b $ of length $ n $ , that exists permutation $ c $ that is sum of $ a $ and $ b $ . The pair of permutations $ x,y $ $ (x≠y) $ and the pair of permutations $ y,x $ are considered distinct pairs.

As the answer can be rather large, print the remainder after dividing it by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
3
```

### 输出

```
18
```

## 样例 #2

### 输入

```
5
```

### 输出

```
1800
```

# 题解

## 作者：huayucaiji (赞：3)

## 解题思路

这个题，我一看，哦，$n\leq 16$，而且又是输入只有 $n$。果断打表啊！

关键在于如何快速打表。

我们可以先找出 $C=(1,2,\cdots,n)$ 的方案数，然后再乘以 $n!$ 就是总方案数了。我们如果爆搜的话就是 $O(n\cdot n!)$。看起来好像跑的很慢 ，其实加上合理剪枝跑的速度还可以接受。

我们如果手玩一下 $n\leq 5$ 的结果，或者让程序跑 $n\leq 12$ 的答案（这部分跑的飞快），你就会发现 $n$ 为偶数的时候，答案是 $0$。这样我们对于 $n$ 为偶数的情况又可以不算了。

如果你像追求更高的效率，可以使用 Meet-in-the-middle。当然，不加这个优化也可以在 $6\ min$ 内跑完，最后打表即可。

## 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=16,MOD=1e9+7; 

int n;
int ans[MAXN],jc[MAXN];
bool vis[MAXN][2];

void dfs(int n,int x) {
	if(x==n+1) {
		ans[n]++;
		return ;
	}
	for(int i=1;i<=n;i++) {
		if(!vis[i][0]) {
			int j=(x-1-i+2+n)%n;
			if(!j) {
				j=n;
			}
			if(!vis[j][1]) {
				vis[i][0]=1;
				vis[j][1]=1;
				dfs(n,x+1);
				vis[i][0]=0;
				vis[j][1]=0;
			}
		}
	}
}

int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);

	int t=16;
	jc[0]=1;
	for(int i=1;i<=t;i++) {
		jc[i]=1ll*jc[i-1]*i%MOD;
		if(i&1) {
			dfs(i,1);
			ans[i]=1ll*ans[i]*jc[i]%MOD;
		}
		else {
			ans[i]=0;
		}
		printf("ans[%d]=%d;\n",i,ans[i]);
	}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

```

不会有人直接交这个程序吧。。。。

这个是打表用的（坑一下直接抄题解的人）

---

## 作者：ncwzdlsd (赞：2)

~~打表大法好~~

### 题面翻译
对于从 $1$ 到 $n$ 的排列 $a$，$b$，定义序列 $c$ 满足 $c_i=(a_i+b_i-2)\bmod{n}+1$，求对于多少对 $(a,b)$ 满足对应的 $c$ 是一个从 $1$ 到 $n$ 的排列。

注意如果 $a\neq b$，$(a,b)$ 与 $(b,a)$ 算作不同的组合。$1\le n\le 16$。

### 题解
$a$ 和 $b$ 全排列共有 $n!$ 种，先固定排列 $a$ 中的元素从 $0\sim n-1$，然后DFS求得排列 $b$。显然这种做法消耗时间很多，但是考虑到 $n\leq16$，可以打表。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[20],b[20],count;
bool flag[20];
void dfs(int now, int num) 
{
    if(now == num) count++;
    for(int i=0;i<num;i++) 
    {
        if(b[i]) // b[i]已经使用过
            continue;
        int c=(a[now]+i)%num+1;
        if(flag[c])// c不构成全排列，忽略
            continue;
        flag[c]=1;
        b[i]=1;
        dfs(now+1,num);
        flag[c]=0;
        b[i]=0;
    }
}
int main() 
{
    for(int i=0;i<16;i++) a[i] = i;//a固定
    for(int i=0;i<16;i++) //DFS b
    {
        count = 0;
        memset(flag, 0, sizeof(flag));
        memset(b, 0, sizeof(b));
        dfs(0,i+1);
        cout << "num=" << i+1 << ' ' << "count=" << count << endl;
    }
}
```

打完表可以得到的数据（用于给大家检验）：
```
num=1 count=1
num=2 count=0
num=3 count=3
num=4 count=0
num=5 count=15
num=6 count=0
num=7 count=133
num=8 count=0
num=9 count=2025
num=10 count=0
num=11 count=37851
num=12 count=0
num=13 count=1030367
num=14 count=0
num=15 count=36362925
```

然后就可以愉快地写代码啦！代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long int a[20],b[20];
int mod = 1e9+7;
int main() 
{
    a[1]=1;
    a[3]=3;
    a[5]=15;
    a[7]=133;
    a[9]=2025;
    a[11]=37851;
    a[13]=1030367;
    a[15]=36362925;
    b[1]=1;
    for(int i=2;i<=16;i++) b[i]=(b[i-1]*i)%mod;
    long long n;
    cin >> n;
    cout << a[n]*b[n]%mod;
}
```

---

## 作者：_edge_ (赞：1)

给出一种折半搜索的题解。

然而这题比较卡，还是要加点极限数据的特判。

我们把这个序列分成两半，一段是 $[1,\dfrac{n}{2}]$ 另外一段是 $[\dfrac{n}{2}+1,r]$，然后我们进行暴力搜。

为了更加简单的搜索，我们只考虑 $c$ 为 $1,2,3,4,\dots,n$ 的情况，对于答案乘一个阶乘即可。

然后我们搜的过程中，打表证明了，对于每一个确定的 $a_i$ 和 $c_i$ 都有一个确定的 $b_i$，因此，我们只需要搜一下当前的 $a_i$ 即可。

然后我们再开个 map 记录当前出现过的 $a$ 中的数和 $b$ 中的数，在后一段扫的时候，可以把出现的数的集合取反得到需要的。

注意这里特判 $n=15$ 以及 $n$ 为偶数的情况。

前者直接搜出答案打表输出，后者为 $0$。

```cpp
#include <iostream>
#include <cstdio>
#include <unordered_map>
#define int long long 
using namespace std;
const int INF=25;
const int INFN=10;
const int Mod=1e9+7;
unordered_map <int,unordered_map<int,int> > Map;
int n,ans,C[INF][INF];
void DFS(int x,int S,int S1) {
	if (x>n/2) {
		// cout<<S<<" "<<S1<<" over?\n";
		Map[S][S1]++;
		return ;
	}
	for (int i=1;i<=n;i++) {
		if (S&(1<<(i-1))) continue;
		int fl=0,xx=0;
		for (int j=C[x][i];j<=C[x][i];j++)
			if ((i+j-2)%n+1==x) {
				// j
				if (S1&(1<<(j-1))) 
					fl=1;
				xx=j;
				break;
			}
		if (fl) continue;
		// cout<<i<<" "<<xx<<" yiw111\n";
		DFS(x+1,S|(1<<(i-1)),S1|(1<<(xx-1)));
	}
	return ;
}
void DFS1(int x,int S,int S1) {
	if (x>n) {
		ans+=Map[(1<<n)-1-S][(1<<n)-1-S1];
		return ;
	}
	for (int i=1;i<=n;i++) {
		if (S&(1<<(i-1))) continue;
		int fl=0,xx=0;
		for (int j=C[x][i];j<=C[x][i];j++)
			if ((i+j-2)%n+1==x) {
				// j
				if (S1&(1<<(j-1))) 
					fl=1;
				xx=j;
				break;
			}
		if (fl) continue;
		// cout<<i<<" "<<xx<<" yiw\n";
		DFS1(x+1,S|(1<<(i-1)),S1|(1<<(xx-1)));
	}
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	// if (n % 2 == 0) {cout<<"0\n";return 0;}
	// if (n == 15) { cout << 150347555; return 0; }
	for (int c=1;c<=n;c++) {
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				if ((i+j-2)%n+1==c) {
					C[c][i]=j;
					break;
				}
			}
		}
	}
	DFS(1,0,0);
	DFS1(n/2+1,0,0);
	for (int i=1;i<=n;i++) ans*=i,ans%=Mod;
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：panyanppyy (赞：0)

复杂度正确的 meet-in-the-middle。
## Solution
直接 $a,b$ 全排列复杂度 $\mathcal O(n!^2)$ 直接爆炸。

考虑一个性质，假设 $a$ 是从 $1\sim n$ 的递增数列，然后枚举 $b$ 的全排列。

这样答案只要乘以 $n!$ 也就是 $a$ 全排列的答案就可以了。

考虑第二个性质，$n$ 是偶数时答案为 $0$，具体证明看楼上吧，贴个 CF 的[链接](https://codeforces.com/blog/entry/7093?#comment-127153)。

具体 dfs 过程可以开一个二维数组存下第一次 $b,c$ 两个集合的贡献，然后第二次 dfs 的时候统计一下它的补集贡献就可以了。

dfs 的枚举是不断衰减的，所以复杂度是 $\mathcal O(2\times\operatorname{A}(n,\dfrac{n}{2}))\approx 5\times10^8$，3s 时限能过。
## Code
```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
using namespace std;
const int p=1e9+7,N=7000;
int n,ans,All,f[N][N],cnt;
gp_hash_table<int,int>s;
inline int id(int x){return s[x];}
inline void dfs1(int i,int b,int c){
	if(i==n/2)return f[id(b)][id(c)]++,void();
	for(int j=0;j<n;j++)
		if(~b>>j&1&&~c>>((i+j)%n)&1)
			dfs1(i+1,b^1<<j,c^1<<((i+j)%n));
}
inline void dfs2(int i,int b,int c){
	if(i==n){
		b^=All,c^=All;
		(ans+=f[id(b)][id(c)])%=p;
		return;
	}
	for(int j=0;j<n;j++)
		if(~b>>j&1&&~c>>((i+j)%n)&1)
			dfs2(i+1,b^1<<j,c^1<<((i+j)%n));
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,All=(1<<n)-1;
	if(~n&1)return cout<<"0\n",0;
	for(int i=0;i<1<<n;i++)
		if(__builtin_popcount(i)==n/2)s[i]=++cnt;
	dfs1(0,0,0),dfs2(n/2,0,0);
	for(int i=2;i<=n;i++)ans=1ll*ans*i%p;
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：jijidawang (赞：0)

upd 2022/1/26. 我草口胡了，dbqdbq . 顺便修了下语言描述
## 简要题面
两个 $1$ 到 $n$ 的排列 $a,b$，令
$$c_i=(a_i+b_i-2)\bmod n+1$$
问有多少对 $a,b$ 满足 $c$ 是排列 .
***
$n\le 16$，时限 $3s$ .
## 简要题解
### 基本分析

对于 $a$ 取每个排列时的情况显然方案数都相等 .

于是直接令 $a$ 为单位排列（$1,2,3,\cdots$），然后方案数乘一个 $n!$ 即可 .
### $n$ 为偶数
结论：答案为 $0$ .

为啥？证明如下：
> Lemma. 
> 
> 当且仅当 $n$ 为奇数时
> $$\dfrac{n(n-1)}2\equiv 0\pmod n$$
> ***
> Proof.
> 
> 显然当 $n$ 为奇数时等式成立，因为 $2$ 对 $n$ 的逆元存在，于是
> $$\dfrac{n(n-1)}2\equiv n(n-1)2^{-1}\equiv 0\cdot (n-1)2^{-1}=0\pmod n$$
> 当 $n$ 为偶数时，若原式成立，则存在整数 $k$ 使得
> $$\dfrac{n(n-1)}2=kn$$
> 解得 $k=\dfrac{n-1}2$，因为 $n$ 为偶数，故 $k$ 必然不是整数 . 矛盾！故原式不成立 .
>
> 证毕 .

假设 $n$ 是偶数且答案不为 $0$（即存在一个排列 $c$），此时：

考虑 $0$ 到 $n-1$ 的排列，每个排列的各数之和显然是：
$$0+1+\dots+n-1= \dfrac{n(n-1)}2$$


于是 $c\equiv a+b\pmod n$ 的元素之和为
$$2\cdot \dfrac{n(n-1)}2=n(n-1)\equiv 0\pmod n$$

又 $c$ 是排列，故 $\dfrac{n(n-1)}2\equiv 0\pmod n$（对 $c$ 求和），这也即意味着 $n$ 是奇数，矛盾！

从而答案为 $0$，证毕 .

（Reference：<https://codeforces.com/blog/entry/7093?#comment-127153>）
### 一般做法
手玩出前几组，去掉 $0$，丢到 OEIS 上，一看：握草 [A006717](http://oeis.org/A006717)！

仔细一看：
> Also the number of "good" permutations on $2n+1$ elements [Novakovich]. - N. J. A. Sloane, Feb 22 2011

倒是挺合理的吧，发现 OEIS 上有 $13$ 个数据，完全可以应对 $n\le 27$ 哦！

贺下来打个表，分奇偶性讨论即可 .
### Bonus
你这时限开 $3s$ 为啥正解可能是打表 ~~还真是~~

CF 官方题解给了一个 Meet-In-The-Middle 的做法，不是很懂 .
## 简要代码
```cpp
using namespace std;
const int N = 4e7 + 500, P = 1e9+7;
typedef long long ll;
const ll A006717[] = {/**/};
int n;
int main()
{
	scanf("%d", &n);
	if (n&1^1){puts("0"); return 0;}
	ll ans = A006717[(n-1)/2];
	for (int i=1; i<=n; i++) ans = ans * i % P;
	printf("%lld\n", ans);
	return 0;
}
```

---

