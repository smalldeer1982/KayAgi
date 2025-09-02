# Playoff Restoration

## 题目描述

$ 2^k $ teams participate in a playoff tournament. The tournament consists of $ 2^k - 1 $ games. They are held as follows: first of all, the teams are split into pairs: team $ 1 $ plays against team $ 2 $ , team $ 3 $ plays against team $ 4 $ (exactly in this order), and so on (so, $ 2^{k-1} $ games are played in that phase). When a team loses a game, it is eliminated, and each game results in elimination of one team (there are no ties). After that, only $ 2^{k-1} $ teams remain. If only one team remains, it is declared the champion; otherwise, $ 2^{k-2} $ games are played: in the first one of them, the winner of the game " $ 1 $ vs $ 2 $ " plays against the winner of the game " $ 3 $ vs $ 4 $ ", then the winner of the game " $ 5 $ vs $ 6 $ " plays against the winner of the game " $ 7 $ vs $ 8 $ ", and so on. This process repeats until only one team remains.

After the tournament ends, the teams are assigned places according to the tournament phase when they were eliminated. In particular:

- the winner of the tournament gets place $ 1 $ ;
- the team eliminated in the finals gets place $ 2 $ ;
- both teams eliminated in the semifinals get place $ 3 $ ;
- all teams eliminated in the quarterfinals get place $ 5 $ ;
- all teams eliminated in the 1/8 finals get place $ 9 $ , and so on.

For example, this picture describes one of the possible ways the tournament can go with $ k = 3 $ , and the resulting places of the teams:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1569E/88386aa68a26b6a812a9c7358a967858cfc084f8.png)After a tournament which was conducted by the aforementioned rules ended, its results were encoded in the following way. Let $ p_i $ be the place of the $ i $ -th team in the tournament. The hash value of the tournament $ h $ is calculated as $ h = (\sum \limits_{i=1}^{2^k} i \cdot A^{p_i}) \bmod 998244353 $ , where $ A $ is some given integer.

Unfortunately, due to a system crash, almost all tournament-related data was lost. The only pieces of data that remain are the values of $ k $ , $ A $ and $ h $ . You are asked to restore the resulting placing of the teams in the tournament, if it is possible at all.

## 说明/提示

The tournament for the first example is described in the statement.

For the third example, the placing $ [1, 2, 3, 3] $ (team $ 1 $ gets place $ 1 $ , team $ 2 $ gets place $ 2 $ , teams $ 3 $ and $ 4 $ get place $ 3 $ ) could result in a hash value of $ 7020100 $ with $ A = 100 $ , but no tournament can result in such placing since teams $ 1 $ and $ 2 $ play against each other in the semifinals, so they cannot get two first places.

## 样例 #1

### 输入

```
3 1337 75275197```

### 输出

```
5 3 5 2 1 5 5 3```

## 样例 #2

### 输入

```
2 100 5040100```

### 输出

```
1 3 3 2```

## 样例 #3

### 输入

```
2 100 7020100```

### 输出

```
-1```

# 题解

## 作者：bugmaker3243 (赞：1)

首先有一个很显然的 $O(2^{2^k-1})$ 暴力，即枚举每一场比赛的胜者，但是 $k=5$ 显然会超时，稍微观察可以发现，题目里的哈希值对于每个队伍来说是独立的，于是可以考虑折半搜索。

对于前 $2^{k-1}$ 个队伍，枚举他们之间比赛的胜者，然后得到每个队的排名，算出哈希值，设为 $sum1$，并把每个可能的值用 $\text{map}$ 存起来。

于是要求就转换为后 $2^{k-1}$ 个队伍得出的哈希值是 $H-sum1$，那么只需要再执行一次这个枚举的过程，然后在 $\text{map}$ 上查询即可。

还有一个要注意的，前 $2^{k-1}$ 个队的第一和后 $2^{k-1}$ 个队的第一之间还要决出总第一，只需要在枚举的过程中钦定他们中间的胜者即可，时间复杂度 $O(2^{2^{k-1}-1})$。

主要难度还是在实现上，建议看完做法后自己写，对把控细节能力有一定帮助。

以下是代码，只给出了主要部分（有注释）。

```cpp
int n,A,S,rk[N],p[N]/*A^i*/;
map<int,vector<int> >mp1,mp2;//前半队伍中的胜者是最终rk1/rk2的总值对应的rk
void dfs(int num,vector<int>v,int ty)
{//num:目前未被淘汰的人数 v:目前未被淘汰的人 ty:算前半还是后半
	if(num==1)
	{
		if(!ty)
		{
			int sum=0;
			vector<int>R;
			rk[v[0]]=1;//钦定是最终rk1
			for(int i=1;i<=(1<<(n-1));i++)
			{
				sum=(sum+(ll)i*p[rk[i]]%mod)%mod;
				R.push_back(rk[i]);
			}
			mp1[sum]=R,R.clear();
            
			sum=0,rk[v[0]]=2;//钦定是最终rk2
			for(int i=1;i<=(1<<(n-1));i++)
			{
				sum=(sum+(ll)i*p[rk[i]]%mod)%mod;
				R.push_back(rk[i]);
			}
			mp2[sum]=R;
		}
		else
		{
			int sum=0;
			rk[v[0]]=1;//钦定是最终rk1
			for(int i=(1<<(n-1))+1;i<=(1<<n);i++) sum=(sum+(ll)i*p[rk[i]]%mod)%mod;
			if(mp2.count((S-sum+mod)%mod))//则前半需要是rk2
			{
				vector<int> r1=mp2[(S-sum+mod)%mod];
				for(int x:r1) print(x),putc(' ');
				for(int i=(1<<(n-1))+1;i<=(1<<n);i++) print(rk[i]),putc(' ');
				exit(0);
			}
			sum=0,rk[v[0]]=2;
			for(int i=(1<<(n-1))+1;i<=(1<<n);i++) sum=(sum+(ll)i*p[rk[i]]%mod)%mod;
			if(mp1.count((S-sum+mod)%mod))
			{
				vector<int> r1=mp1[(S-sum+mod)%mod];
				for(int x:r1) print(x),putc(' ');
				for(int i=(1<<(n-1))+1;i<=(1<<n);i++) print(rk[i]),putc(' ');
				exit(0);
			}
		}
		return ;
	}
	for(int S=0;S<(1<<(num/2));S++)
	{
		vector<int>nex;//下一次哪些人晋级
		nex.clear();
		for(int i=0;i<num/2;i++)//0:v[i*2]赢; 1:v[i*2+1]赢
		{
			int L=v[i*2],R=v[i*2+1];
			if((S>>i)&1)
			{
				rk[L]=0,nex.push_back(L);
				rk[R]=num+1;
			}
			else
			{
				rk[L]=num+1;
				rk[R]=0,nex.push_back(R);
			}
		}
			
		dfs(num/2,nex,ty);
	}
	
}
signed main()
{
	read(n),read(A),read(S);
	p[0]=1;
	for(int i=1;i<N;i++) p[i]=(ll)p[i-1]*A%mod;
	vector<int>v;
	for(int i=1;i<=(1<<(n-1));i++) v.push_back(i);
	dfs((1<<(n-1)),v,0);
	v.clear();
	for(int i=(1<<(n-1))+1;i<=(1<<n);i++) v.push_back(i);
	dfs((1<<(n-1)),v,1);
	puts("-1");
	return 0;
}
```


---

## 作者：Yusani_huh (赞：1)

思路跟另外两篇差不多，只是给出一个我自认为比较好懂的代码（？）

设 $n=2^k$，以下所有“$16$”都是为了方便理解，实际做的时候应该是 $\frac{n}{2}$。

首先看到 $2^n$ 这个数量级属于“整个做会超时，根号级别刚刚好”的程度，限制条件 $H$ 还是一个长得跟 hash 一样的式子，那么就想到把序列折半。

具体做法：把前 $16$ 个数先枚举一遍，枚举出来前一半哈希值（设为 $H_1$）存到 `map` 里面，再去枚举后 $16$ 个数，得到后一半哈希值 $H_2$，然后直接到 `map` 里去找存不存在 $H_1=H-H_2$ 就行了，也即 meet in the middle。

具体怎么枚举：考虑 $16$ 个人两两之间会有 $15$ 次比赛，再加上前一半的胜者和后一半的胜者之间的一次，总共就有 $16$ 次，所以直接 $2^{16}$ 次枚举这 $16$ 次比赛的胜者，即可得出前后 $16$ 人各自的最终排名。 

~~代码中另有解释。~~ 代码里不给解释，在这里给出两个 `for` 中的代码理解（不想看代码可先尝试自己实现）：

考虑一下比赛过程，先是相邻两人之间比赛，然后是相邻四人中的两个胜者，以此类推。因为我们要将所有这些结果压入一个状态里，所以要把每一位分别对应的场次分离出来。把比赛分为若干个层次，相邻两人比赛称为第一层，相邻四人比赛称为第二层，以此类推，然后把状态一层一层拆分出来，具体实现可见代码。于是可以用一个队列维护，这样每一场都是队头两人的比赛，根据状态判断谁赢，赢家再次入队。跟另一半 $16$ 人比的那场单独讨论，根据这场比赛的输赢将当前状态分别存进两个 `map`，便于枚举对面时跟对面呼应。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 103
#define LL long long
#define INF 0x3f3f3f3f
#define MOD 998244353
int k,n,m,p[N];
LL a,h,pa[N];
queue<int>q;
map<int,vector<int>>mp[2];
int main(){
	scanf("%d%d%d",&k,&a,&h);
	n=1<<k,m=1<<k-1,pa[0]=1;
	for(int i=1;i<=20;++i) pa[i]=pa[i-1]*a%MOD;
	int cnt,lim,nw;
//	需要解释一下此处的三个变量。
//	cnt表示已经在当前层枚举了几场，lim表示当前层总共有几场，
//	nw+1表示在当前层输掉的会获得第几名（注意是 nw+1）。
	for(int s=0;s<(1<<m);++s){ //前16人
		cnt=0,lim=m>>1,nw=m;
		for(int i=1;i<=m;++i) q.push(i);
		for(int i=m-1;i;--i){ //前15场直接得到结果
			cnt++;
			int u=q.front();q.pop();
			int v=q.front();q.pop();
			if(s>>i&1) p[v]=nw+1,q.push(u); //赢家再次入队
			else p[u]=nw+1,q.push(v);
			if(cnt==lim) cnt=0,lim>>=1,nw>>=1;
		}
		if(s&1) p[q.front()]=1; //最后一场因为是跟对面比，所以单独讨论
		else p[q.front()]=2;
		LL res=0; 
		for(int i=1;i<=m;++i)
			res=(res+i*pa[p[i]])%MOD;
		if(!mp[s&1].count(res)) //跟对面比是输是赢分别存进两个map
			for(int i=1;i<=m;++i)
				mp[s&1][res].push_back(p[i]);
		while(!q.empty()) q.pop();
	}
	for(int s=0;s<(1<<m);++s){ //后16人，过程跟上面差不多
		cnt=0,lim=m>>1,nw=m;
		for(int i=m+1;i<=n;++i) q.push(i);
		for(int i=m-1;i;--i){
			cnt++;
			int u=q.front();q.pop();
			int v=q.front();q.pop();
			if(s>>i&1) p[v]=nw+1,q.push(u);
			else p[u]=nw+1,q.push(v);
			if(cnt==lim) cnt=0,lim>>=1,nw>>=1;
		}
		if(s&1) p[q.front()]=2;
		else p[q.front()]=1;
		LL res=0; 
		for(int i=m+1;i<=n;++i)
			res=(res+i*pa[p[i]])%MOD;
		res=(h+MOD-res)%MOD;
		if(mp[s&1].count(res)){ //检查map里是否有对应哈希值
			for(int i:mp[s&1][res])
				printf("%d ",i);
			for(int i=m+1;i<=n;++i)
				printf("%d ",p[i]);
			return puts(""),0;
		}
		while(!q.empty()) q.pop();
	}
	puts("-1");
	return 0;
}
```

---

## 作者：RyexAwl (赞：0)

因为每场比赛都是编号相邻的两个队伍 pk，因此考虑将这个过程看成线段树 pushup 。

> 任意一棵 $n$ 个节点的树都可以看成一棵 $n-1$ 个节点的树添加叶子构造而成。
>
> $n$ 个节点的二叉树可以挂（添加）$n+1$ 个叶子。
>
> 因此有 $n$ 个叶子节点的二叉树，节点数是 $2n-1$ 。

因此，一共会 pushup $2^k-1$ 次。 

一个直接的暴力做法就是枚举这 $2^k-1$ 次 pushup 的结果。

对于 $2^{32}$ 这种级别的计算量，我们考虑将其折半，也就是 meet in the middle。

注意到，$[1,2^{k-1}],(2^{k-1},2^k]$ 在最后一次 pushup （也就是 pushup 根节点）前的状态互不影响，并且我们只关心最终的哈希值。

因此我们可以考虑分别枚举两边的 pushup 状态，开两个哈希表存储前一半的哈希值与排名，分别最后一个元素排名为 $1/2$ 的情况。

枚举后一半时在哈希表中查询即可。

对于计算哈希值，枚举每个位置在第几轮淘汰即可，代码很好写。
```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl
#define int long long

namespace wxy{

const int N = 50,mod = 998244353;

int k,n,m,A,H,power[N];

std::map<int,std::vector<int>> mp[2];

int d[10];

int fpow(int a,int b) {
	int res = 1;
	for (; b ; b >>= 1) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    per(i,5,1) d[i] = fpow(2,i-1) + 1;
    d[0] = 1; power[0] = 1;
    gin >> k >> A >> H; n = (1 << k); m = (1 << k - 1);
    rep(i,1,40) power[i] = power[i-1] * A % mod;
    for (int S = 0; S < (1 << m); ++S) {
		std::vector<int> p; int hash = 0;
		for (int i = 1; i <= m; i++) {
			int u = i + m - 1,t = k;
			while (t) {
				if (((S >> (u >> 1)) & 1) ^ (u & 1)) break;
				u >>= 1; --t;
			}
			hash = (hash + i * power[d[t]] % mod) % mod;
			p.push_back(d[t]);
		}
		mp[S&1][hash] = p;
	}
	for (int S = 0; S < (1 << m); ++S) {
		std::vector<int> p; int hash = 0;
		for (int i = 1; i <= m; i++) {
			int u = i + m - 1,t = k;
			while (t) {
				if (((S >> (u >> 1)) & 1) ^ (u & 1)) break;
				u >>= 1; --t;
			}
			hash = (hash + (i + m) * power[d[t]] % mod) % mod;
			p.push_back(d[t]);
		}
		int val = (H - hash + mod) % mod;
		if (mp[S&1^1].count(val)) {
			std::vector<int> pre = mp[S&1^1][val];
			for (int j = 0; j < pre.size(); j++) prt << pre[j] << " ";
			for (int j = 0; j < p.size(); j++) prt << p[j] << " ";
			return;
		}
	}
	puts("-1");
}

}signed main(){wxy::main(); return 0;}
```


---

## 作者：Leap_Frog (赞：0)

### P.S.
![](//xn--9zr.tk/zm)一下题解。  

### Description.
淘汰赛，每个人的排名定义如下：
- 他没被淘汰：排名为 $1$
- 他在倒数第 $k$ 轮被淘汰了：排名为 $2^{k-1}+1$

定义第 $i$ 个人的排名为 $p_i$，给定 $H=\sum_{i=1}^{2^k}i\times A^{p_i}$，构造一个合法的 $p_i$ 序列。

### Solution.
哈希这种东西一看就不能优化。  
而且数据范围是 $k\le 5$ 是什么毒瘤。  

考虑有一个很显然的 $O(2^{2^k-1}\times\text{poly}(2^k))$ 的暴力，就是枚举 $2^k-1$ 场比赛的情况。  
复杂度完全爆炸，很不可接受。  

考虑折半，枚举前 $2^{k-1}$ 个队伍的相对胜负，存到数据结构里。  
枚举后 $2^{k-1}$ 个队伍相对胜负，再查询是否可行。  
肉眼可见有亿点点、巨大多细节，是一道高质量的屑题。  

### Coding.
不是都说了是嘴巴了吗，建议直接去 CF 上找代码。  
~~我找过来贴这边其实是一件很没意义的事情的说~~

---

