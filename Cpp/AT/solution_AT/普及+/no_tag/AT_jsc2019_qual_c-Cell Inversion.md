# Cell Inversion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jsc2019-qual/tasks/jsc2019_qual_c

$ 2N $ 個のマスが左右一列に並んでおり、各マスの色を表す長さ $ 2N $ の文字列 $ S $ が与えられます。

左から $ i $ 番目のマスの色は、$ S $ の $ i $ 文字目が `B` のとき黒色で、`W` のとき白色です。

あなたは異なる $ 2 $ マスを選んで、それらのマスおよびそれらの間にあるマスの色を反転する操作をちょうど $ N $ 回行います。 ここで、マスの色を反転するとは、そのマスの色が黒色なら白色に、白色なら黒色にすることです。

ただし、操作を通して同じマスを $ 2 $ 回以上選ぶことはできません。 つまり、各マスがちょうど $ 1 $ 回ずつ選ばれることになります。

$ N $ 回の操作終了後に全てのマスを白色にする方法が何通りあるかを $ 10^9+7 $ で割った余りを求めてください。

ここで、条件を満たす $ 2 $ つの方法が異なるとは、$ 1 $ つ目の方法で $ i $ 番目に選んだ $ 2 $ つのマスの組と $ 2 $ つ目の方法で $ i $ 番目に選んだ $ 2 $ つのマスの組が異なるような $ i $ $ (1\ \leq\ i\ \leq\ N) $ が存在することをいいます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ |S|\ =\ 2N $
- $ S $ の各文字は `B` または `W` である。

### Sample Explanation 1

全てのマスを白色にする方法は次の $ 4 $ 通りあります。 - 最初の操作では $ 1,\ 3 $ 番目のマスを選び、次の操作では $ 2,\ 4 $ 番目のマスを選びます。 - 最初の操作では $ 2,\ 4 $ 番目のマスを選び、次の操作では $ 1,\ 3 $ 番目のマスを選びます。 - 最初の操作では $ 1,\ 4 $ 番目のマスを選び、次の操作では $ 2,\ 3 $ 番目のマスを選びます。 - 最初の操作では $ 2,\ 3 $ 番目のマスを選び、次の操作では $ 1,\ 4 $ 番目のマスを選びます。

## 样例 #1

### 输入

```
2
BWWB```

### 输出

```
4```

## 样例 #2

### 输入

```
4
BWBBWWWB```

### 输出

```
288```

## 样例 #3

### 输入

```
5
WWWWWWWWWW```

### 输出

```
0```

# 题解

## 作者：HD0X (赞：2)

鲜花：太愚蠢，只会 $O(n \log n)$，喜提最劣解。

请叫我模拟赛多测不清空仙人。

题意略。

## 思路
容易发现，所有的情况都是由一种情况变化来的，所以只要找出一种合法情况，就可以推出所有情况。

先说结论，对于每个未选位置，找到最近的下一个未选的相同字符，且中间差偶数（ $\text{0}$ 也行）个位置。如果这样选的方案合法，就一定有解，否则无解。

关于正确性，可以从有解的方案通过交换左或右节点得到。

容易得到，两端区间可以交换，当且仅当它们有相交部分，因为每个位置我们只关心被覆盖次数的奇偶性。

当方案中存在奇区间时，一定另外存在奇数数个相交的奇区间，所以可以变化。

关于判断合法，可以使用差分（虽然模拟赛时只想起用线段树）。

而每次向后找下一个相同字符且下标差为偶数的位置时，可以用类似并查集思想维护，是一个完全跑不满的 $O(n \log n)$，完全可以接受。

统计答案时，对每个区间开始位置，乘上这个点被覆盖次数，最后乘上全排列 $A_{n}^{n}$ 即是答案，因为覆盖顺序并不重要。证明留作读者思考~~其实是打表发现的，会的大佬请教教我。~~

## CODE
树状数组版

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10,mod=1e9+7;
int a[MAXN],c[MAXN],n,T,nxt[MAXN][2][2],pre[MAXN];
string s;
bool vis[MAXN],st[MAXN];
int lowbit(int x) 
{
	return x&-x;
}
int sum(int num)
{
	int ret=0;
	for(int i=num;i;i-=lowbit(i))
	{
		ret+=c[i];
	}
	return ret;
}
void add(int x,int k)
{
	for(int i=x;i<=n*2+1;i+=lowbit(i)) c[i]+=k;
}
int find(int x,int u)
{
	if(vis[x])
	{
		return nxt[x][u][1]=find(nxt[x][u][1],u);
	}
	else return x;
}
signed main()
{
	T=1;
	pre[0]=1;
	for(int i=1;i<=MAXN-10;i++) pre[i]=pre[i-1]*i%mod;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=2*n+1;i++) c[i]=0;
		cin>>s;
		for(int i=1;i<=2*n;i++) a[i]=(s[i-1]=='B'),vis[i]=0;
		nxt[2*n][1][0]=nxt[2*n][1][1]=nxt[2*n][0][0]=nxt[2*n][0][1]=2*n+1;
		for(int i=2*n-1;i>=1;i--) 
		{
			if(a[i+1]==a[i]) nxt[i][a[i]][0]=i+1,nxt[i][a[i]^1][0]=nxt[i+1][a[i]^1][1];
			else nxt[i][a[i]][0]=nxt[i+1][a[i]][1],nxt[i][a[i]^1][0]=i+1;
			nxt[i][a[i]][1]=nxt[i+1][a[i]][0];
			nxt[i][a[i]^1][1]=nxt[i+1][a[i]^1][0];
		}
		bool f=0;
		for(int i=1;i<2*n;i++)
		{
			nxt[i][a[i]][0]=find(nxt[i][a[i]][0],a[i]);
			if(vis[i]==1) 
			{
				continue;	
			}
			else if(nxt[i][a[i]][0]<=2*n) 
			{
				st[i]=1;
				vis[nxt[i][a[i]][0]]=1;
				add(i,1);
				add(nxt[i][a[i]][0]+1,-1);
				nxt[i][a[i]][0]=nxt[nxt[i][a[i]][0]][a[i]][1];
			}
			else 
			{
				f=1;
				break;
			}
		}
		if(f)
		{
			for(int i=1;i<=2*n;i++) vis[i]=st[i]=0; 
			cout<<0<<endl;
			continue;
		}
		for(int i=1;i<=2*n;i++)
		{
			if(sum(i)%2!=a[i])
			{
				f=1;
				break;
			}
		}
		if(f)
		{
			for(int i=1;i<=2*n;i++) vis[i]=st[i]=0; 
			cout<<0<<endl;
			continue;
		}
		int ans=pre[n];
		for(int i=1;i<=2*n;i++)
		{
			if(st[i])
			{
				ans=ans*sum(i)%mod;
			}
			st[i]=vis[i]=0;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
差分版~~其实没什么差别~~

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10,mod=1e9+7;
int a[MAXN],b[MAXN],n,T,nxt[MAXN][2][2],fac[MAXN];
string s;
bool vis[MAXN],st[MAXN];
int find(int x,int u)
{
	if(vis[x])
	{
		return nxt[x][u][1]=find(nxt[x][u][1],u);
	}
	else return x;
}
signed main()
{
	T=1;
	fac[1]=1;
	for(int i=2;i<=MAXN-10;i++) fac[i]=1ll*fac[i-1]*i%mod;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=2*n+1;i++) b[i]=0;
		cin>>s;
		for(int i=1;i<=2*n;i++) a[i]=(s[i-1]=='B'),vis[i]=0;
		nxt[2*n][1][0]=nxt[2*n][1][1]=nxt[2*n][0][0]=nxt[2*n][0][1]=2*n+1;
		for(int i=2*n-1;i>=1;i--) 
		{
			if(a[i+1]==a[i]) nxt[i][a[i]][0]=i+1,nxt[i][a[i]^1][0]=nxt[i+1][a[i]^1][1];
			else nxt[i][a[i]][0]=nxt[i+1][a[i]][1],nxt[i][a[i]^1][0]=i+1;
			nxt[i][a[i]][1]=nxt[i+1][a[i]][0];
			nxt[i][a[i]^1][1]=nxt[i+1][a[i]^1][0];
		}
		bool f=0;
		for(int i=1;i<2*n;i++)
		{
			nxt[i][a[i]][0]=find(nxt[i][a[i]][0],a[i]);
			if(vis[i]==1) 
			{
				continue;	
			}
			else if(nxt[i][a[i]][0]<=2*n) 
			{
				st[i]=1;
				vis[nxt[i][a[i]][0]]=1;
				b[i]++;
				--b[nxt[i][a[i]][0]+1];
				nxt[i][a[i]][0]=nxt[nxt[i][a[i]][0]][a[i]][1];
			}
			else 
			{
				f=1;
				break;
			}
		}
		if(f)
		{
			for(int i=1;i<=2*n;i++) vis[i]=st[i]=0; 
			cout<<0<<endl;
			continue;
		}
		for(int i=1;i<=2*n;i++)
		{
			b[i]=b[i-1]+b[i];
			if(b[i]%2!=a[i])
			{
				f=1;
				break;
			}
		}
		if(f)
		{
			for(int i=1;i<=2*n;i++) vis[i]=st[i]=0; 
			cout<<0<<endl;
			continue;
		}
		int ans=fac[n];
		for(int i=1;i<=2*n;i++)
		{
			if(st[i])
			{
				ans=1ll*ans*b[i]%mod;
			}
			st[i]=vis[i]=0;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：qzhwlzy (赞：0)

## 题目大意

有 $2\times n$ 个格子排成一排，每个格子非黑即白。定义一次操作为选择 $1\le l<r\le n$，将 $[l,r]$ 之间的格子全部反色（黑变白，白变黑）。求每个格子恰好均被选择一次作为端点且最终格子全为白色的操作方案数。

## 思路

显然每个格子均恰好被选择一次作为端点意味着一共只有 $n$ 次操作。若一个格子最初是黑色，那么它必须被进行奇数次反色，否则需要偶数次。

首先不难发现，操作之间的顺序不会影响最终格子的颜色。因为对于固定的操作 $[l_1,r_1],[l_2,r_2],\ldots,[l_n,r_n]$，每个格子被包含于对应操作区间的个数是一定的，即 $\forall i$，满足 $i\in [l_x,r_x]$ 的 $x$ 的个数是一定的，所以每个格子被反色的次数也是一定的，这也就意味着最终结果是一定的。

其次，若确定了每个格子作为左端点或右端点，最终的结果也是一定的。因为操作 $[l_i,r_i],[l_j,r_j]$ 和 $[l_i,r_j],[l_j,r_i]$ 的效果是一样的（假设 $l_i<l_j<r_i<r_j$，画图可得，两种方案的效果均为将 $[l_i,l_j)\cap(r_i,r_j]$ 反色）。所以现在的问题就是确定每个格子是作为左端点还是右端点。

对于格子 $i$，假设其左边有 $l$ 个格子作为左端点，$r$ 个格子被作为右端点（$l+r = i-1$）。那么，若格子 $i$ 为左端点，就有 $(l-r+1)$ 个操作区间“穿过”了格子 $i$，否则有 $(l-r)$ 个。注意到它们的奇偶性不同，所以两种只有一种可取，也就是说，此时 $i$ 作为左端点还是右端点被唯一确定了。又因为第 $1$ 个格子一定是左端点，所以我们用这种类似归纳法的方法确定了每个格子会作为左端点还是右端点。

对于左起第 $i$ 个作为右端点的格子，假设其左边作为左端点的格子数量为 $p_i$。那么，对于左起第 $1$ 个作为右端点的格子，其有 $p_1$ 种左端点的选法；第 $2$ 个作为右端点的格子就有 $(p_2 - 1)$ 种，如此下去。所以一共有 $\prod\limits_{i=1}^n(p_i - i + 1)$ 种左右端点配对的方法。又因为这 $n$ 个操作有 $n!$ 种排列顺序，所以一共的方案数就是 $n!\times\prod\limits_{i=1}^n(p_i - i + 1)$。

```cpp
#include<iostream>
#include<cstdio>
#define maxn 100005
#define ll long long
#define mod 1000000007
using namespace std;
int n,a[maxn*2],numl,numr,totl; char x; ll ans=1LL;
// numl 表示左起还有多少个左端点未被配对，即上文中的穿过 i 的区间数量 (l-r)
// numr 表示左起有几个格子作为右端点
// totl 表示一共有几个格子作为左端点
int main(){
      scanf("%d\n",&n); for(int i=1;i<=n*2;i++){scanf("%1c",&x); a[i]=(x=='B'); if(i<=n) ans=ans*i%mod;}
      numl=totl=1; for(int i=2;i<n*2;i++){
            if(a[i]!=numl%2){numl++; totl++;} // a[i] 应为左端点
            else{numl--; numr++; ans=(ans*(totl-numr+1)%mod)%mod;} // a[i] 应为右端点
      } numr++; ans=(ans*(totl-numr+1)%mod)%mod;
      if(totl!=n||!a[1]||!a[2*n]) printf("0"); else printf("%lld",ans);
      // 若 a[1] 或 a[2*n] 是白色或左右端点数量不等则不可能全为白
      return 0;
}
```

---

