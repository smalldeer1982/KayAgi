# Magician and Pigs (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ n $ and $ x $ . You can make hacks only if both versions of the problem are solved.

Little09 has been interested in magic for a long time, and it's so lucky that he meets a magician! The magician will perform $ n $ operations, each of them is one of the following three:

- $ 1\ x $ : Create a pig with $ x $ Health Points.
- $ 2\ x $ : Reduce the Health Point of all living pigs by $ x $ .
- $ 3 $ : Repeat all previous operations. Formally, assuming that this is the $ i $ -th operation in the operation sequence, perform the first $ i-1 $ operations (including "Repeat" operations involved) in turn.

A pig will die when its Health Point is less than or equal to $ 0 $ .

Little09 wants to know how many living pigs there are after all the operations. Please, print the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the operations are equivalent to repeating four times: create a pig with $ 8 $ Health Points and then reduce the Health Points of all living pigs by $ 3 $ . It is easy to find that there are two living pigs in the end with $ 2 $ and $ 5 $ Health Points.

## 样例 #1

### 输入

```
4
1 8
2 3
3
3```

### 输出

```
2```

## 样例 #2

### 输入

```
6
1 5
1 6
2 2
3
1 4
3```

### 输出

```
5```

## 样例 #3

### 输入

```
12
2 1
1 15
1 9
3
1 12
2 2
1 13
3
2 1
1 9
1 8
3```

### 输出

```
17```

# 题解

## 作者：Alex_Wei (赞：8)

直接模拟整个过程不太可行，考虑直接对每次操作 $1$，算出它会被复制多少次。

仍然是从后往前逆推，算出第一次遇到操作 $1$ 时已经减去的值 $s$。若 $s\geq x_i$，显然它不会产生贡献。否则，考虑它之后的所有操作 $3$：$p_0, p_1, \cdots, p_{k - 1}$。

预处理 $c_i$ 表示位置 $i$ 的操作 $3$ 复制一次会使得血量多减去的数值。考虑求出该操作 $1$ 在复制第 $a$ 次的时候减去的值 $s_a$，若 $s_a \geq x_i$，说明复制次数小于 $a$，否则复制次数不小于 $a$。

求 $s_a$。如果 $a$ 的第 $p_i$ 位为 $1$，则在 $p_i$ 处进入复制前的分支，$s_a$ 增加整个复制后的分支让会血量减去的值，即 $c_{p_i}$。因此，$s_a = s + \sum_{a_d = 1} c_{p_d}$，可以 $\mathcal{O}(\log a)$ 计算。

问题在于 $a$ 可能很大，因为 $c$ 的一段前缀可以等于 $0$，但一旦遇到操作 $2$，$c$ 变成非零，$c$ 就会以指数级增长，使得 $a\leq x$。特判掉等于 $0$ 的前缀即可，等价于特殊处理一开始没有操作 $2$ 的极长段。

时间复杂度 $\mathcal{O}(n\log ^ 2x)$，[代码](https://codeforces.com/contest/1774/submission/185744343)。将二分换成从高位到低位贪心即可做到 $\mathcal{O}(n\log x)$，[代码](https://codeforces.com/contest/1774/submission/185744486)。

---

## 作者：Little09 (赞：7)

[书接上回](https://www.luogu.com.cn/blog/LJA001111/solution-cf1774f1)。

考虑倒着做的那个解法。原本是要对 $\log$ 个数，求有多少个子集和 $< x$。然而这些数是有性质的。从小到大排列以后，每个数大于前面所有数的和。因为每个数至少要 $\times 2$。

根据这个性质，我们可以更优地做背包。对于要求 $<x$，从大到小考虑每个元素：如果元素 $\ge x$，那么一定不选；如果 $<x$，那么要是不选的话，后面的元素可以随便选，因为后面元素的和不到 $x$，怎么选都没问题。这样可以递推下去了。

所以对于每个 $1$ 操作，我们按照上述过程做，时间复杂度是 $O(\log x)$ 的。总复杂度 $O(n\log x)$。

双 log 的话看写法，可能还是放过去了很多。我本来以为 $8\times 10^5$ 可以卡掉的。主要我不敢让 IO 量太大。

代码短得可怜。

```cpp
const int N=800005;
int n,m; 
ll a[N],b[N],c[N],cnt,s[N],d[N],cntd;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	ll maxs=1e9,sum=0;
	for (int i=1;i<=n;i++)
	{
		cin >> a[i];
		if (a[i]!=3) cin >> b[i];
		if (a[i]==2) sum+=b[i];
		sum=min(sum,maxs);
		if (a[i]==3) b[i]=sum,sum=sum*2;
		sum=min(sum,maxs);
	}
	sum=0;
	ll res=1,ans=0;
	for (int i=n;i>=1;i--)
	{
		if (a[i]==2) sum+=b[i];
		else if (a[i]==3)
		{
			if (b[i]==maxs) continue;
			if (b[i]==0) 
			{
				res=res*2%mod;
				continue;
			}
			c[++cnt]=b[i];
		}
		else
		{
			b[i]-=sum;
			if (b[i]<=0) continue;
			ll su=0,r=b[i];
			for (int j=1;j<=cnt;j++)
			{
				if (r>c[j])
				{
					su=(su+(1ll<<(cnt-j)))%mod;
					r-=c[j];
				}
			}
			su=(su+1)%mod;
			ans=(ans+su*res)%mod;
		}
	}
	cout << ans;
	return 0;
}

```


------------

花絮（2）

这个问题被我从初三拖到了高一。初三那个时候想过 $x\le 10^9$，但可能大概想了 5min 感觉做不了就弃了。奇怪的是验题的时候也没人告诉我可以做 $x\le 10^9$。后来有一天放学的时候我突然就会了。然后把 F 代码改了改就交上去，然后发现过了。于是 F2 诞生了。

anton 还亲自来写了这道题，感谢 anton 的支持。


---

## 作者：Demeanor_Roy (赞：6)

- [原题链接](https://www.luogu.com.cn/problem/CF1774F2)。

---

不妨思考操作三的本质：对于先前插入的某个当前值为 $x$ 的数，将其分裂为 $x$ 与 $x-w$。其中 $w$ 是如果执行一次当前操作三，期间所有二操作的和。这样转化的正确性是显然的。

考虑 $w$ 如何更新，显然遇到二操作就加上对应的 $x$，遇到三操作则翻倍即可。

进一步地，我们这样描述问题：对于某一个插入操作，我们考虑它后面的二三操作，遇到二操作则减去对应的 $x$，遇到三操作则可以选择减去对应的 $w$ 或不变，求最后有多少种可能的 $x'>0$，再对所有插入操作求和。

注意到相邻两个三操作的 $w_1,w_2$ 满足 $2w_1 \leq w_2$。故除开一段 $w=0$ 的前缀，剩下的三操作只有 $\log v$ 个是有意义的，因为后面的三操作你必须选择不变。

$w=0$ 的三操作对插入的贡献即为 $ans \gets 2ans$。此时剩余部分转化为：有一个大小不超过 $\log v$ 的集合 $S$，且满足 $\forall i>1,2S_i \leq S_{i-1}$，求它有多少子集和小于 $x$。从大到小，枚举当前元素选不选，选则继续递归，不选则剩下的数可以任意选择，直接计算即可。

时间复杂度 $O(n \log v)$。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=8e5+10,inf=1e9,mod=998244353;
int n,w,C,ans,cnt,a[N],op[N],val[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&op[i]);
		if(op[i]!=3) scanf("%d",&val[i]);
		if(op[i]==2) w=min(inf,w+val[i]);
		else if(op[i]==3) val[i]=w,w=min(inf,w<<1);
	}
	w=0;C=1;
	for(int i=n;i>=1;i--)
	{
		if(op[i]==2) w=min(inf,w+val[i]);
		else if(op[i]==3)
		{
			if(!val[i]) C=(C+C)%mod;
			else if(val[i]==inf) continue;
			else a[++cnt]=val[i];
		}
		else
		{
			int x=val[i]-w;
			if(x>0)
			{
				int d=1;
				for(int i=1;i<=cnt;i++)
					if(x>a[i])
					{
						x-=a[i];
						d=(d+(1ll<<(cnt-i)))%mod;
					}
				ans=(ans+1ll*d*C)%mod;
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：xzzduang (赞：4)

[传送门](https://codeforces.com/contest/1774/problem/F2)

分别考虑每一只猪对于答案的贡献。发现每一次 3 操作其实就是把目前生命值为 $x$ 的猪变成一个 $x$ 和一个 $x-w$，$w$ 是先前造成伤害的总和。而对于一个生命值为 $x$ 的猪，后面有意义的 3 操作最多有 $\log V$ 个，因为 $w$ 每经过一个操作 3 就会乘 2（$w=0$ 的特殊处理一下）。

后面的操作 2 显然可以提前减掉，现在就变成一个这样的问题：有若干个数 $w_i$，每个数选或不选，问选出来的数总和小于一个数的方案数，如果暴力枚举选或不选，再在别的地方稍微优化一下就可以通过 Easy Version 了。

但是我们发现待选的数 $w_i$ 的后一个数至少是前一个数的两倍，所以它有和二的整数次幂类似的性质，即 $\forall i,w_i>\sum_{j=1}^{i-1}w_j$，这说明我们可以像二进制一样一位一位填来解决上面那个问题了。具体一点的话看一下代码应该很好懂。

时间复杂度 $\mathcal{O}(n\log V)$。

```cpp
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<vector>
#include<algorithm>
#define ll long long
#define ld long double
#define fi first
#define se second
#define pii pair<int,int>
#define lowbit(x) ((x)&-(x))
#define popcount(x) __builtin_popcount(x)
#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f3f
#define umap unordered_map
#define all(x) x.begin(),x.end()
#define mk make_pair
#define pb push_back
#define ckmax(x,y) x=max(x,y)
#define ckmin(x,y) x=min(x,y)
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define N 800005
#define int long long
using namespace std;
inline int read(){
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch==45),ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int mo=998244353;
inline void red(int &x){x>=mo?x-=mo:0;}
int n,op[N],a[N],dam,sum[N],bas[N],ans;
vector<int> mp,vec;
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		bas[i]=1,op[i]=read();
		if(op[i]!=3) a[i]=read();
		else a[i]=dam;
		if(op[i]==2) dam+=a[i];
		else if(op[i]==3) dam*=2;
		dam=min(dam,(long long)(inf)+1ll);
		sum[i]=sum[i-1]+(op[i]==2)*a[i];
		if(op[i]==3){
			if(a[i]==0) bas[i]=2;
			else if(a[i]<=inf) mp.pb(i);
		}
	}
	for(int i=n-1;i>=1;--i) (bas[i]*=bas[i+1])%=mo;
	for(int i=1;i<=n;++i){
		if(op[i]!=1) continue;
		vec.clear();
		for(int v:mp) if(v>=i) vec.pb(a[v]);
		reverse(all(vec));
		int res=0,tmp=a[i]-(sum[n]-sum[i])-1;
		if(tmp<0) continue;
		for(int j=0;j<vec.size();++j){
			int k=(int)vec.size()-j-1;
			if(tmp>=vec[j]) red(res+=(1<<k)),tmp-=vec[j];
		}
		red(res=res+1);
		red(ans+=res*bas[i]%mo);
	}
	cout<<(ans%mo+mo)%mo;
	return 0;
}

```



---

## 作者：intel_core (赞：2)

直接处理这个 3 有些奇怪，先把 3 去掉不管。

统计一个加入的数 $x$ 的减小过程不好弄，我们算出 $x$ 加入之前总共减掉的数 $cnt$，把加入 $x$ 看成在一开始加入 $x+cnt$。

这样就可以轻松 $O(n)$ 解决。

把 3 操作放回来，我们还是依照刚才的思路，把所有加数都等效成在一开始加数。

这时候考虑后面的 3 操作对加的数的影响，假设后面 3 操作一共有 $m$ 个，进行之前 2 操作减掉的数是 $x_i$，$x_i$ 可以很轻松求出。

显然，对于每个 3 操作，操作前和操作后两种情况，所以等效于加上 $x+0/1x_1+0/1x_2+\cdots+0/1x_k$ 这 $2^k$ 个数。

现在的难点是求出有多少个数能挺到最后。注意到 $2x_i\le x_{i+1}$，因为在 $i+1$ 次 3 操作之前，$i$ 3 操作之前的部分已经重复了两次。

所以我们一个一个求，类似于二进制的方法就可以求出有多少个能挺到最后。

但这样还不够，注意到 $x\le 10^9$，而 $x_i \ge 2^{i-1}$，所以 $x$ 在位数很大的时候是起不到作用的，我们只需要从 $\log 10^9$ 位开始考虑 $x$ 的贡献即可。

复杂度 $O(n \log V)$。

---

## 作者：Cxny (赞：1)

延续 [$\text{Easy\ Version}$](https://www.luogu.com.cn/blog/Cxny/solution-cf1774f1) 的思路。

影响最大的是值域达到了 $10^9$，没法暴力维护 $sum$。

但我们没必要维护整个 $sum$ 数组：其中有实际意义的“拐点”只有 $\log X$ 个。将拐点存起来大力跳即可。

操作 $1$ 单次时间复杂度变为 $O(\log X)$，操作 $3$ 单次复杂度 $O(1)$，空间复杂度 $O(n)$。

赛时 `pw[0] = 1; for(int i = 2; i < 40; i++) pw[i] = pw[i - 1] * 2ll % mod;` 没调出来，极限没过。

[记录](https://codeforces.com/contest/1774/submission/185756815)。

---

## 作者：Mr_罗 (赞：0)

维护可重集 $S\gets\varnothing$ 和变量 $t\gets 0$ ，把三种操作重写成以下形式：

- $1\ x:\quad S\to S\cup\{x\}$
- $2\ x:\quad S\to \{k-x\mid k\in S\},t\to t+x$
- $3\ {\color{white}x}:\quad S\to \{k-t\mid k\in S\}\cup S,t\to 2t$

最后查询 $|\{x\mid x\in S,x>0\}|$ 。

如果是 F1 那么 [扔到平衡树上就做完了](https://www.luogu.com.cn/article/zx8arw03) ，但这里值域是 $10^9$ ，因此我们要~~挑战 $\sout{\mathcal O(V\log^2V)}$ 过十亿~~换一个思路。

考察某个操作 $1$ 的贡献：在后面遇到操作 $2$ 就修改，遇到操作 $3$ 时**选择**要么修改要么不变，求最后有多少种结果 $>0$ 。显然它后面所有操作 $2$ 一定都会起作用，因此可以直接在 $x$ 上减掉。于是只要解决操作 $3$ 即可。

容易将现在的问题改写成对于所有操作 $3$ 对应的 $t$ 构成的集合 $T$ ，有多少个子集 $T'\subseteq T$ 满足 
$$x-\sum_{k\in T'}k>0$$
由于那些 $t=0$ 的操作不会产生任何影响，因此可以把它们扔出来，最后给答案乘上一个 $2^k$ 的系数，这样 $|T|=\mathcal O(\log V)$ 。

直接做的话只能做到 01 背包的 $\mathcal O(V\log V)$ ，但是由于我们保证了 $\forall x\in T,y\in T,x<y$ 都有 $2x\le y$ ，因此有
$$\forall x\in T,x>\sum_{\substack{y\in T\\y<x}}y$$
这是一个极好的性质，它允许我们从大到小直接做。具体地，如果当前数选不了则不管它，否则讨论当前数选不选：选就继续做下去，不选的话比它小的那些元素都可以任意选，直接累加起来就对了。

这样我们就做完了，时间复杂度 $\mathcal O(n\log V)$ 。

```cpp
int n;
vi vt;
mint ans;
int op[N], a[N];

void mslv() {
    int t = 0;
    rep(i, 1, n = ri) {
        rd(op[i]);
        if (op[i] == 3) a[i] = t, chkmn(t <<= 1, inf);
        else {
            rd(a[i]);
            if (op[i] == 2) chkmn(t += a[i], inf);
        }
    } t = 0;
    mint pw = 1;
    per(i, n, 1) switch (op[i]) {
        case 1: if (int b = a[i] - t; b > 0) {
            mint x = 1;
            req(k, 0, vt.size()) if (b > vt[k]) 
                b -= vt[k], x += bit(kEnd - k - 1);
            ans += x * pw;
        } break;
        case 2: chkmn(t += a[i], inf); break;
        case 3: {
            if (!a[i]) pw *= 2;
            else if (a[i] == inf) continue;
            else vt.eb(a[i]);
        } break;
    } prs(ans);
}
```

---

