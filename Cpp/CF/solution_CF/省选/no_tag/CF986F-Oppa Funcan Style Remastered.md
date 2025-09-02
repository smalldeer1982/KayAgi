# Oppa Funcan Style Remastered

## 题目描述

Surely you have seen insane videos by South Korean rapper PSY, such as "Gangnam Style", "Gentleman" and "Daddy". You might also hear that PSY has been recording video "Oppa Funcan Style" two years ago (unfortunately we couldn't find it on the internet). We will remind you what this hit looked like (you can find original description [here](http://acm.timus.ru/problem.aspx?space=1&num=2107&locale=en)):

On the ground there are $ n $ platforms, which are numbered with integers from $ 1 $ to $ n $ , on $ i $ -th platform there is a dancer with number $ i $ . Further, every second all the dancers standing on the platform with number $ i $ jump to the platform with the number $ f(i) $ . The moving rule $ f $ is selected in advance and is not changed throughout the clip.

The duration of the clip was $ k $ seconds and the rule $ f $ was chosen in such a way that after $ k $ seconds all dancers were in their initial positions (i.e. the $ i $ -th dancer stood on the platform with the number $ i $ ). That allowed to loop the clip and collect even more likes.

PSY knows that enhanced versions of old artworks become more and more popular every day. So he decided to release a remastered-version of his video.

In his case "enhanced version" means even more insanity, so the number of platforms can be up to $ 10^{18} $ ! But the video director said that if some dancer stays on the same platform all the time, then the viewer will get bored and will turn off the video immediately. Therefore, for all $ x $ from $ 1 $ to $ n $ $ f(x) \neq x $ must hold.

Big part of classic video's success was in that looping, so in the remastered version all dancers should return to their initial positions in the end of the clip as well.

PSY hasn't decided on the exact number of platforms and video duration yet, so he asks you to check if there is a good rule $ f $ for different options.

## 样例 #1

### 输入

```
3
7 7
3 8
5 6
```

### 输出

```
YES
NO
YES
```

# 题解

## 作者：Gordon_Song (赞：10)

# 零，缘起
本地OJ推荐做本题，没先到一做就是一晚上……

![](https://cdn.luogu.com.cn/upload/image_hosting/owwlmfz4.png?x-oss-process=image)

# 一，转化
题目中 $k$ 非常的大——到了 $10$ 的 $15$ 次方，所以单是枚举因数便会超时。我们可以把将 $n$ 表示成若干个 $k$ 的因数之和转换为质因数之和。

简易证明：

 对于每个因数，都能表示成 $a \times c$（$a$ 为质数），因为这是 $k$ 的因数，所以 $a$ 也是 $k$ 的因数。又因为每个因数取的次数不受限制，所以取一个这个因数就等于取 $c$ 个 $a$。
 
# 二，分类
让我们对 $k$ 的因数个数进行分类：

### 1.零个质因数

上过小学的都知道，只有 $1$ 这一个数。
   
### 2.一个质因数

此时 $k$ 是质数。那么这时 $n$ 只能为 $k$ 的倍数，否则 $n$ 便无法表示为 $k$ 的质因数之和。

我的代码片段：
```cpp
for(auto i:it.second)//暂且不用管it
{//printf("%d\n",i.second);
    if(i.first%a[l]==0)//i.first存储n,i.second存储它的读入位置，a数组用来存储k分解质因数结果，l是最后一个位置
    {
        ans[i.second]=1;
    }
    else
    {
	    ans[i.second]=0;
    }
}
```

   
### 3.二个质因数
   那么题目等价于求方程 $a \times x + b \times y = n$ 是否有解（$a$ , $b$ 是那两个质因数）。
   
下面是求解过程：

解：

$a \times x + b \times y \equiv n \pmod a$

$\space \space \space \space \space \space \space \space \space \space \space \space \space \space b \times y \equiv n \pmod a$

$\space \space \space \space \space \space \space \space \space \space \space \space \space \space \space \space \space \space \space \space \space y \equiv n \div b \pmod a$

所以方程 $a \times x + b \times y = n$ 有解，当且仅当 $n \div b$（模 $a$ 意义下）乘 $b$ 小于等于 $n$。

没错，这一部分用到的唯一算法是逆元！！！

我的代码片段：
```cpp
for(auto i:it.second)
{
	n=i.first;//a数组,i.first,i.second的意思和上面片段一样
	if(n%a[1]==0||n%a[2]==0)
	{
		ans[i.second]=1;
		//printf("YES\n");
		continue;
	}
	if(a[2]*((((n%a[1])*qui(a[2],a[1]-2,a[1]))%a[1])%a[1])<=n)//那条柿子,qui是快速幂
	{
		ans[i.second]=1;           
		//printf("YES\n");
	}
	else
	{
		ans[i.second]=0;
		//printf("NO\n");
	}
}
```


### 4. $>2$ 个质因数
   实现这部分之前，建议先完成[P3403跳楼机](https://www.luogu.com.cn/problem/P3403)。
   
受那题的思路启发，我们可以定义 $minn_i$ 表示不用第一个质因数所组成的 $mod$ 第一个质因数为 $i$ 的最小和值。

就这样，此题正式转化成了图论题。以模数为点，边是质因数，跑一遍 SPFA 或 Dijkstra 就可求出。由于 SPFA 的常数较小（我太弱），我选择了它。记第一个质因数为 $r$，当 $minn[n \bmod r] \leq n$ 时，输出 `YES`，否则输出 `NO`。
最坏情况下，最多只会有 $10^5$ 个点，所以这个算法可以过。
```cpp
memset(in,0,sizeof(in));
for(int i=0;i<a[1];i++)
{
	minn[i]=1e18+1e9;
}
minn[0]=0;
in[0]=true;
//q.push(0);
ll=0,rr=1;
int t;
while(ll<rr)//SPFA
{
	t=q[++ll];
	in[t]=false;
	for(int i=2;i<=l;i++)
	{
		if(minn[(t+a[i])%a[1]]>minn[t]+a[i])
		{
			minn[(t+a[i])%a[1]]=minn[t]+a[i];
			if(!in[(t+a[i])%a[1]])
			{
				q[++rr]=(t+a[i])%a[1];
				//q.push((t+a[i])%a[1]);
				in[(t+a[i])%a[1]]=true;
			}
		}
	}
}
for(auto i:it.second)
{
	n=i.first;
	if(n>=minn[n%a[1]])
	{
		ans[i.second]=1;

	}
	else
	{
		ans[i.second]=0;

	}
}
```


# 三，细节
当然，如果不加点优化过不了——CF 数据 TQL。两个个人觉得比较重要的细节：

1. 如果 $k$ 相同，则可以合并处理。因为 $n$ 不同而 $k$ 相同的情况下大部分运算一致，只会在最后的判断部分不同。如果不加此优化而所有 $k$ 都是情况三的话，时间复杂度将会达到至少 $O(T \times \sqrt[3]k )$，绝对会爆。而题目中保证 $k$ 只有最多 $50$ 种，所以在经过相同的 $k$ 只处理一次这一离线操作后，时间复杂度骤降为 $O(T \times log_2(k) + 50 \times \sqrt[3]k )$。
2. 普通的分解质因数会挂。蒟蒻太弱，只会欧拉筛预处理 $\sqrt k$ 的质数，不知道其他的算法。

# 四，代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<utility>
using namespace std;
long long n,k,t;
vector<int>pr;
long long a[100001],l;
inline long long qui(register long long di,register long long mi,register long long mod)//快速幂
{
	register long long res=1; 
	while(mi)
	{
		if(mi&1)
		{
			res*=di;
			res%=mod;
		}
		mi>>=1;
		di*=di;
		di%=mod;
	}
	return res;
}
bool in[100001];
int q[10000001],ll,rr;
long long minn[100001];
map<long long,vector<pair<long long,int> > >mp;
int ans[100001];
const int AC=3.3e7;
bool hv[AC];
int main()
{
	for(int i=2;i<=AC;i++)//欧拉筛，理论上来说是线性的
	{
		if(!hv[i])
		{
			pr.push_back(i);
			//printf("%d\n",i);
		}
		for(int j=0;j<pr.size()&&pr[j]*i<=AC;j++)
		{
			hv[pr[j]*i]=true;
			if(i%pr[j]==0)
			{
				break;
			}
		}
	}
	int T;
	scanf("%d",&T);
    long long x,y;
	for(int i=1;i<=T;i++)
	{
		scanf("%lld%lld",&x,&y);
		mp[y].push_back({x,i});
	}
	for(auto it:mp)
	{
		l=0;
		k=it.first;
		if(k==1)
		{
			continue;
		}
		t=k;
		for(int i=0;i<pr.size()&&pr[i]*1ll*pr[i]<=t;i++)//分解质因数
		{
			if(t%pr[i]==0)
			{
				l++;
				a[l]=pr[i];
				while(t%pr[i]==0)
				{
					t/=pr[i];
				}
				
			}
		}
		if(t>1)
		{
			l++;a[l]=t;
		}
		if(l==1)
		{
			for(auto i:it.second)
			{//printf("%d\n",i.second);
				if(i.first%a[l]==0)
				{
					ans[i.second]=1;
                   
				}
				else
				{
					ans[i.second]=0;
				}
			}
			//printf("%d",a[l]);
		}
		else
		{
			if(l==2)
			{
				for(auto i:it.second)
				{
					n=i.first;
					if(n%a[1]==0||n%a[2]==0)
					{
						ans[i.second]=1;
                        
						//printf("YES\n");
						continue;
					}
					if(a[2]*((((n%a[1])*qui(a[2],a[1]-2,a[1]))%a[1])%a[1])<=n)//那条柿子
					{
						ans[i.second]=1;
                       
						//printf("YES\n");

					}
					else
					{
						ans[i.second]=0;
                        
						//printf("NO\n");
					}
				}
			}
			else
			{
				memset(in,0,sizeof(in));
				for(int i=0;i<a[1];i++)
				{
					minn[i]=1e18+1e9;
				}
				minn[0]=0;
				in[0]=true;
				//q.push(0);
				ll=0,rr=1;
				int t;
				while(ll<rr)//SPFA
				{
					t=q[++ll];
					in[t]=false;
					for(int i=2;i<=l;i++)
					{
						if(minn[(t+a[i])%a[1]]>minn[t]+a[i])
						{
							minn[(t+a[i])%a[1]]=minn[t]+a[i];
							if(!in[(t+a[i])%a[1]])
							{
								q[++rr]=(t+a[i])%a[1];
								//q.push((t+a[i])%a[1]);
								in[(t+a[i])%a[1]]=true;
							}
						}
					}
				}
				for(auto i:it.second)
				{
					n=i.first;
					if(n>=minn[n%a[1]])
					{
						ans[i.second]=1;
                        
					}
					else
					{
						ans[i.second]=0;
                        
					}
				}
			}
		}
	}
    for(int i=1;i<=T;i++)
    {
        if(ans[i])
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
}

```

---

## 作者：cyffff (赞：8)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF986F)

惊讶，看了看最优解发现我 300+ms，别人 6s+？

另外这题 *3300?

## 题意
给你 $n$ 和 $k$，问 $n$ 能否表示为 $k$ 的若干非 $1$ 因子之和，每个因子可用无限次。

$t$ 组数据，令 $t_k$ 表示所有数据中不同 $k$ 的数量。

$n\le 10^{18},k\le 10^{15},t\le 10^4,t_k\le 50$。
## 题解
****
引理：若 $n$ 能表示为 $k$ 的若干非 $1$ 因子之和，则 $n$ 能表示为 $k$ 的若干质因子之和。

证：设 $n=\displaystyle\sum_{i=1}^d w_i$，若 $w_i\notin\Bbb P$，则必然可以找到一个质数 $p|w_i$，显然，$p$ 是 $k$ 的质因子，$w_i$ 便可用 $\dfrac {w_i}p$ 个 $p$ 代替。
****
首先对每个 $k$ 分别计算，设 $\displaystyle k=\prod_{i=1}^dp_i^{q_i}$，其中 $p_i\le p_{i+1}$。

对 $d$ 分类讨论：
- $d=0$：很显然，$k=1$，由于要的是质因子，所以无解。
- $d=1$：很显然，$k\in\Bbb P$，由于只有 $k$ 一个质因子即它自己，直接判断 $[k|n]$ 即可。
- $d=2$：设 $k=x^{u}y^{v}$，很显然，指数在这里没用。假设有解，令 $ax+by=n$，则易得 $by\equiv n(\bmod x)$，求解逆元 $y^{-1}$，带回计算 $[y\times(n\times y^{-1}\bmod x)\le n]$ 即可。
- $d\ge 3$：看起来并不好直接求。

我们可以发现，对于 $d\ge 3$，$p_1\le\sqrt[3]{k}\le 10^5$。此时我们需要做的是，给定初始状态 $0$ 和 $d$ 种转移，第 $i$ 种转移的权值是 $p_i$，给出一堆询问，求能否通过初始状态转移到 $n$。

此时需要引入一个算法：同余最短路。

考虑令 $s_i$ 表示以 $0$ 为初始状态，能转移到的 $u\bmod p_1=i$ 的最小的 $u$。于是对于一个询问 $n$，只需考虑 $[s_{n\bmod p_1}\le n]$ 即可。（显然，之后可以一直 $+p_1$ 拼出 $n$）

那么怎么计算 $s$ 呢？

考虑图论建模，转移可以看作对于所有 $2\le i\le d,0\le j<p_1$，连边 $j\to(j+p_i)\bmod p_1$，权值为 $p_i$，从 $0$ 开始使用最短路算法即可得到答案。

可以发现，$d\le13$，边数是 $\Theta(d\sqrt[3]k)$ 的，点数是 $\Theta(\sqrt[3]k)$ 的，所以该算法的时间复杂度是对的。

另外，$k$ 很大，分解质因数要用 Pollard-Rho。

于是这道题就做完了，时间复杂度是 $\Theta(t\log k+t_kd\sqrt[3]k\log k)$，显然跑不满，可以通过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e5+10;
namespace PR{
	#define lll __int128
	inline ll qpow(ll x,ll y,const ll mod){
		ll res=1;
		while(y){
			if(y&1) res=(lll)res*x%mod;
			x=(lll)x*x%mod;
			y>>=1;
		}
		return res;
	}
	inline bool Miller_Rabin(ll x,int a){
		ll y=x-1;
		while(y){
			ll res=qpow(a,y,x);
			if(res!=1&&res!=x-1) return 0;
			if(y&1||res==x-1) return 1;
			y>>=1;
		}
		return 1;
	}
	inline bool Isprime(ll x){
		if(x<2||x==46856248255981) return 0;
		if(x==2||x==3||x==7||x==61||x==24251) return 1;
		if(x%6!=1&&x%6!=5) return 0;
		return Miller_Rabin(x,2)&&Miller_Rabin(x,61);
	}
	inline ll f(ll x,ll c,ll n){
		return ((lll)x*x+c)%n;
	}
	inline ll Pollard_Rho(ll x){
		ll s=0,t=0,c=1ll*rand()%(x-1)+1,val=1;
		int stp,g=1;
		for(;;g<<=1,s=t,val=1){
			for(stp=1;stp<=g;stp++){
				t=f(t,c,x);
				val=(lll)val*abs(t-s)%x;
				if(!(stp&127)){
					ll q=__gcd(val,x);
					if(q>1) return q;
				}
			}
			ll q=__gcd(val,x);
			if(q>1) return q;
		}	
	}
	inline void solve(ll x,ll cnt,vector<ll> &ans){
		if(x<2) return ;
		if(Isprime(x)) {for(int i=1;i<=cnt;i++)ans.push_back(x);return ;}
		ll pri=x;
		for(;pri>=x;pri=Pollard_Rho(x));
		ll s=0;
		for(;x%pri==0;x/=pri)s++;
		solve(x,cnt,ans),solve(pri,cnt*s,ans);
	}
	inline void decompose(ll x,vector<ll>&ans){
		solve(x,1,ans);
	}
}
map<ll,int>mp; 
struct nd{
	ll n;
	int id;
};
struct node{
	ll k;
	vector<nd>vec;
}tmp[70];
int cnt,T;
bool ans[N];
inline int qpow(ll x,ll y,ll p){
	ll res=1;
	x%=p;
	while(y){
		if(y&1) res=res*x%p;
		x=x*x%p;
		y>>=1;
	}
	return res;
}
int cntt,head[N];
ll dis[N];
bool vis[N];
struct Edge{
	int to,nxt;
	ll w;
}a[N*30];
inline void add(int u,int v,ll w){
	cntt++;
	a[cntt].to=v;
	a[cntt].nxt=head[u];
	a[cntt].w=w;
	head[u]=cntt;
}
struct nodeE{
	int x;
	ll d;
	inline friend bool operator<(const nodeE &a,const nodeE &b){
		return a.d>b.d;
	}
};
priority_queue<nodeE>q;
inline void Dijkstra(int s){
	memset(vis,0,sizeof(vis));
    memset(dis,127,sizeof(dis));
	dis[s]=s;
	q.push({s,dis[s]});
	while(!q.empty()){
	    nodeE p=q.top();
	    q.pop();
	    int rt=p.x;
	    if(vis[rt]) continue;
	    vis[rt]=1;
	    for(int i=head[rt];i;i=a[i].nxt){
		    int t=a[i].to;
		    if(dis[t]>dis[rt]+a[i].w){
			    dis[t]=dis[rt]+a[i].w;
			    if(!vis[t])
				    q.push({t,dis[t]});
			}
		}
	}
}
/*
4
41 236447
7 1533
128 68191
1188 267623
*/
inline void solve(node p){
	ll k=p.k;
	vector<ll>d;
	PR::decompose(k,d);
	sort(d.begin(),d.end());
	d.resize(unique(d.begin(),d.end())-d.begin());
	int sz=d.size();
	if(sz==0){
		return ;
	}else if(sz==1){
		for(auto tmp:p.vec)
			ans[tmp.id]=tmp.n%k==0;
	}else if(sz==2){
		ll x=d[0],y=d[1];
		for(auto tmp:p.vec){
			ll n=tmp.n;
			if(n%x==0) ans[tmp.id]=1;
			else{
				ll pp=n%x*qpow(y,x-2,x)%x;
				ans[tmp.id]=(lll)pp*y<=n;
			}
		}
	}else{
		cntt=0;
		memset(head,0,sizeof(head));
		for(int i=0;i<d[0];i++)
			for(int j=1;j<sz;j++)
				add(i,(i+d[j])%d[0],d[j]);
		Dijkstra(0);
		for(auto tmp:p.vec){
			ll n=tmp.n;
			ans[tmp.id]=dis[n%d[0]]<=n;
		}
	}
}
int main(){
	T=read();
	for(int i=1;i<=T;i++){
		ll n=read(),k=read();
		if(!mp[k]) mp[k]=++cnt;
		int t=mp[k];
		tmp[t].k=k;
		tmp[t].vec.push_back({n,i});
	}
	for(int i=1;i<=cnt;i++)
		solve(tmp[i]);
	for(int i=1;i<=T;i++)
		puts(ans[i]?"YES":"NO");
	flush();
}
```
再见 qwq~

---

## 作者：Avocadooo (赞：5)

### 前置知识

- **Pollard-Rho 算法**

> 一种可以快速分解质因数的算法，但事实上本题如果写得好可以用暴力分解过。

- [**P3403 跳楼机**](https://www.luogu.com.cn/problem/P3403)的**同余最短路**思想


### 主要思路

#### 1.质因数分解 

题目问 $ n $ 能否由 $ k $ 的因子求和得到。而 $ k $ 的因子显然是可以通过 $ k $ 的质因数组合求和得到的，可以感性理解，不再证明。

所以我们先将 $ k $ 进行质因数分解。

$$ k=\prod_{i=1}^{Q}p_{i}^{c_{i}} $$

为了方便，这里我们假设 $ p_i<p_{i+1}(1 \leq i < k) $。

#### 2.分类讨论

首先，若 $ k=1 $，则 $ k $ 没有质因数，显然不可分。

对于 $ k \geq 2 $，观察到 $ k \leq 10^{15} $，那么有 $ 1 \leq \sqrt[3]{k}\leq 10^{5} $。

对 $ k $ 中不同质因数的个数 $ Q $ 进行分类：

- $ Q=1 $

此时 $ k $ 为素数，那么答案显然是 $ [k \mid n] $。

- $ Q=2 $

此时 $ k $ 可以写作如下形式：

$$ k=a^{c_1}b^{c_2} $$

直接考虑为用 $ a,b $ 两个数组合得到 $ n $。即：

$$ ax+by=n $$

那么这种情况的答案即是**该二元一次不定方程是否有非负整数解**。

- $ Q \geq 3 $

因为 $ 1 \leq \sqrt[3]{k}\leq 10^{5} $，且我们规定了 $ p_i<p_{i+1}(1 \leq i < k) $。

所以这个时候有 $ 1 \leq p_{1} \leq 10^{5} $。

仿照[**P3403 跳楼机**](https://www.luogu.com.cn/problem/P3403)的思路，先不使用 $ p_{1} $，用其它数在模 $ p_{1} $ 的剩余系下**尽可能减少总和**，最后用 $ p_{1} $ 补全。

我们定义数组 $ dst_i $ 表示：由当前 $ k $ 的质因子组合出的**最小的**模 $ p_{1} $ 为 $ i $ 的数。

由此我们构建一个包含 $ p_{1} $ 个节点的图，编号从 $ 0 $ 至 $ p_{1}-1 $，第 $ i $ 号点的状态即为模 $ p_{1} $ 为 $ i $ 。

而对于 $ j\geq 2 $，从 $ i(0 \leq i < p_{1}) $ 号点向 $ (i+p_{j}) \bmod p_{1} $ 连一条边权为 $ p_{j} $ 的边，然后跑普通最短路即可。$ Q $ 最大大概是 $ 13 $，复杂度不会炸。

答案即为 $ [dst_{(n \bmod p_{1})}\leq n] $。

**注意：题意中说明不同的 $ k $ 只有 $ 50 $ 个，需要对同一个 $ k $ 的询问统一处理。**

#### 3.实现细节

总结了两点我在实现中出现的问题：

- 构建图的时候编号为 $ 0 $ 至 $ p_{1}-1 $，清空时不要忘记清编号 $ 0 $ 上的值。

- 用到乘法的时候最好使用 ```__int128``` 或者快速乘，以防溢出。

- 更多的就看代码吧

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define int ll
#define ibig __int128
const int N=500005;
struct Node{int n,k,Ans,id;}ask[N];
map< int,vector<Node> > mp;
int power(int c,int p,int mod)
{
	if(!p) return 1;
	int p2=power(c,p>>1,mod);
	if(p&1) return (ibig)p2*p2%mod*c%mod;
	else return (ibig)p2*p2%mod;
}
namespace mr{
	int ori[]={0,2,3,5,7,11,13,17,19,23,29,31,37};
	const int tot=12;
	bool check(const int bas,int p)
	{
		if(power(bas,p-1,p)!=1) return false;
		int d=p-1;
		while(d%2==0)
		{
			d/=2;
			if(power(bas,d,p)==p-1) return true;
			if(power(bas,d,p)!=1) return false;
		}
		return true;
	} 
	bool isprime(int p)
	{
		if(p<=1) return false;
		for(int i=1;i<=tot;i++) if(p==ori[i]) return true;
		for(int i=1;i<=tot;i++) if(!check(ori[i],p)) return false;
		return true;
	}
}
namespace p_rho{
	int f(int x,int c,int p){return ((ibig)x*x+c)%p;}
	int pr(int p)
	{
		int a1=0,a2=0,c=rand()%(p-1)+1,d;
		for(int len=1,total=1;;len<<=1,a1=a2,total=1)
		{
			for(int step=1;step<=len;step++)
			{
				a2=f(a2,c,p);
				total=(ibig)total*abs(a2-a1)%p;
				if(total%127==0)
				{
					if((d=__gcd(p,total))>1) return d;
				} 
			}
			if((d=__gcd(p,total))>1) return d;
		}
		return p;
	}
	void split(int p,map<int,bool> &mp)
	{
		if(p<2) return;
		if(mr::isprime(p)) return void(mp[p]=true);
		int d=p;
		while(d==p) d=pr(d);
		while(p%d==0) p/=d;
		split(d,mp),split(p,mp);
	}
	vector<int> divide(int n)
	{
		map<int,bool> d;
		vector<int> rec; 
		split(n,d);
		for(map<int,bool>::iterator it=d.begin();it!=d.end();++it)
			rec.push_back(it->first); 
		return rec;
	}
}

void re0(int k){for(Node pac:mp[k]) ask[pac.id].Ans=false;}

void re1(int k){for(Node pac:mp[k]) ask[pac.id].Ans=(pac.n%k==0);}

int exgcd(int a,int &x,int b,int &y)
{
	if(!b) return x=1,y=0,a;
	int d=exgcd(b,y,a%b,x);
	y-=a/b*x;
	return d;
}
void re2(int a,int b,int k)
{
	for(Node pac:mp[k])
	{
		int c=pac.n;
		ask[pac.id].Ans=((ibig)b*((ibig)c*power(b,a-2,a)%a)<=(ibig)c);
	}
}

namespace Chain{
	int h[N],cnt;        
	struct Edge{int next,to,v;}e[10000005];
	void AddEdge(int c,int d,int w){e[++cnt]=(Edge){h[c],d,w};h[c]=cnt;}
}
using namespace Chain;
int dst[N];
priority_queue< pair<int,int> > q;
bitset<N> vst;
void dij(int MAXN)
{
	for(int i=0;i<=MAXN;vst[i]=0,dst[i]=LLONG_MAX,i++);
	dst[0]=0;
	q.push(make_pair(-dst[0],0));
	while(!q.empty())
	{
		int r=q.top().second; q.pop();
		if(vst[r]) continue;
		vst.set(r);
		for(int i=h[r];i;i=e[i].next)
		{
			int y=e[i].to;
			if(vst[y]) continue;
			if(dst[y]>dst[r]+e[i].v) 
			{
				dst[y]=dst[r]+e[i].v;
				q.push(make_pair(-dst[y],y));
			}   
		}
		
	}
}
void re3(vector<int> &d,int k)
{
	sort(d.begin(),d.end());
	cnt=0;for(int i=0;i<=d[0];i++) h[i]=0;
	for(int i=0;i<d[0];i++)
		for(int it=1;it!=d.size();++it)
			AddEdge(i,(i+d[it])%d[0],d[it]);
	dij(d[0]);
	for(Node pac:mp[k])
		ask[pac.id].Ans=(dst[pac.n%d[0]]<=pac.n);
}

void solve(int k)
{
	vector<int> d=p_rho::divide(k);
	if(d.size()==0) re0(k);
	else if(d.size()==1) re1(k);
	else if(d.size()==2) re2(d[0],d[1],k);
	else re3(d,k);
}

signed main()
{
	signed T; scanf("%d",&T);
	for(int i=1;i<=T;i++) scanf("%lld %lld",&ask[i].n,&ask[i].k),mp[ask[i].k].push_back((Node){ask[i].n,0,0,i});
	for(map< int,vector<Node> >::iterator it=mp.begin();it!=mp.end();++it) solve(it->first);
	for(int i=1;i<=T;i++) printf(ask[i].Ans?"YES\n":"NO\n");
	return 0;
}

```

---

## 作者：DaiRuiChen007 (赞：3)

# CF986F 题解

[Problem Link](https://www.luogu.com.cn/problem/CF986F)

**题目大意**

> 给定 $n$ 与 $k$，问是否能把 $n$ 写成若干个 $k$ 的非 $1$ 因数的和的形式。
>
> 数据范围：$n\le10^{18},k\le 10^{15}$。

**思路分析**

首先发现 $k$ 的非 $1$ 因数总能拆成若干个 $k$ 的质因数之和，因此原问题变成了把 $n$ 用 $k$ 的质因数表示。

先考虑 $k$ 的质因数个数为 $1/2$ 的情况，$1$ 个因数是 trivial 的，两个因数显然用 exgcd 就可以处理，即求 $px+qy=n$ 有无自然数根，求 $x$ 最小值反解 $y$ 即可，这部分时间复杂度 $\mathcal O(\log k)$。

然后考虑 $k$ 质因子 $\ge 3$ 的情况，注意到最小质因子 $\le 10^5$，而这是一个经典的同余最短路处理多重背包的问题。

把其他的每个质因子丢进去跑一遍即可，注意到不需要用优先队列，直接找 $dis$ 最小的点转 $1$ 圈更新即可，另一种实现方式是任取一个起点转 $2$ 圈更新。

分解质因子用 Pholland-Pho，当然，暴力分解质因子常数小也能过。

时间复杂度 $\mathcal O(\sqrt k)-\mathcal O(\pi(\sqrt k+\omega(k)\sqrt[3]k)$，其中 $\omega(k)\le13$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5,MAXQ=3.2e7+5,inf=1e18;
vector <int> primes;
bitset <MAXQ> isc;
unordered_map <int,vector<array<int,2>>> Q;
bool ans[MAXN];
int dis[MAXN];
inline int exgcd(int &x,int &y,int a,int b) {
	if(!b) return x=1,y=0,a;
	int t=exgcd(y,x,b,a%b);
	return y-=x*(a/b),t;
}
inline void solve(int k,vector<array<int,2>>&qry) {
	if(k==1) return ;
	vector <int> pr;
	for(int p:primes) {
		if(k<p) break;
		if(k%p==0) {
			pr.push_back(p);
			while(k%p==0) k/=p;
		}
	}
	if(k>1) pr.push_back(k);
	if(pr.size()==1) {
		for(auto z:qry) ans[z[1]]=(z[0]%pr[0]==0);
		return ;
	} else if(pr.size()==2) {
		int x,y,g=exgcd(x,y,pr[0],pr[1]),s=pr[1]/g;
		for(auto z:qry) {
			int n=z[0];
			if(n%g) continue;
			int u=((__int128_t)x*(n/g)%s+s)%s;
			ans[z[1]]=(n>=u*pr[0]);
		}
		return ;
	}
	int p=*min_element(pr.begin(),pr.end());
	fill(dis+1,dis+p,inf),dis[0]=0;
	for(int d:pr) if(d!=p) {
		int c=__gcd(d,p);
		for(int r=0;r<c;++r) {
			int ti=0;
			for(int s=r;ti<=2;s=(s+d)%p) {
				ti+=(s==r),dis[(s+d)%p]=min(dis[(s+d)%p],dis[s]+d);
			}
		}
	}
	for(auto z:qry) ans[z[1]]=(dis[z[0]%p]<=z[0]);
}
signed main() {
	for(int i=2;i<MAXQ;++i) {
		if(!isc[i]) primes.push_back(i);
		for(int p:primes) {
			if(i*p>=MAXQ) break;
			isc[i*p]=true;
			if(i%p==0) break;
		}
	}
	int T;
	scanf("%lld",&T);
	for(int i=1,n,k;i<=T;++i) scanf("%lld%lld",&n,&k),Q[k].push_back({n,i});
	for(auto &it:Q) solve(it.first,it.second);
	for(int i=1;i<=T;++i) puts(ans[i]?"YES":"NO");
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：3)

表示并不知道楼下是怎么暴力分解过的……反正我写的pollard-rho……

首先我们要找的是置换，而置换可以分解为环，一个置换回到单位排列的次数就是环长的$lcm$，那么我们相当于要求一组$\sum a_i=n$且$\min a_i>1$且$lcm\{a_i\}|K$（因为走回单位排列之后可以循环的走，所以这个走回时间是$K$的约数即可）。

那么我们想，既然$a_i>1$它们的$lcm$还得是$K$的约数，显然每个$a_i$都必须有$k$的质因子。假设我们求出了一组$\sum a_i=n$，对于每个$a_i$都有$a_i=\prod p_j^{k_j}$，其中$p_j$是$K$的某个质因子，换而言之它一定能够写成$xp_j$的形式，那么我们干脆就将它拆为$x$个$p_j$，也就是说我们强制让每个$a_i$都是某个$p_j$，这样的话显然$lcm$仍然是$K$的约数，这由于是等价的变换所以和还是$n$，毕竟我们是在做判断并不需要考虑那么多。

那么现在我们的问题就转化为了判断$n$是不是能被$\{p_i\}$通过一些系数凑出来，如果$K$是质数那$n$就必须是$K$的倍数，否则考虑最小的$p_0<=\sqrt K$，我们可以在模$p_0$剩余系下跑一个同余类bfs（以$\{p_i\}$为边的最短路），即$dis_i$表示最小能被表示出的$\%p_0=i$的数，显然如果$dis_{n\%p_0}<=n$那么$n$一定可以通过在$dis_{n\%p_0}$上加一堆$p_0$凑出来。

然而$\sqrt K$的最短路还是过不去，他可能会出两个$3e7$质数的乘积然后卡的飞起……但是这最坏情况仅是两个质数的情况，而这相当于判断线性方程$px+qy=n$是否存在$x>=0,y>=0$的解，那么我们就先扩欧求出一个$>=0$的最小的$x$，然后这个时候$y$一定是最大的，判断$y$是否$>=0$即可。于是复杂度就是$O(T\sqrt[3]K)$了。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define ll long long
#define abs(_o) ((_o < 0) ? -(_o) : _o)
#define double long double
using namespace std;
namespace ywy {
	inline ll gsc(ll a, ll b, ll p) {
	    a %= p;
	    b %= p;
	    if (a <= 1000000000 && b <= 1000000000)
	        return ((a * b) % p);
	    ll cjr = (double)a * b / p;
	    ll res = a * b - cjr * p;
	    res %= p;
	    res += p;
	    res %= p;
	    return (res);
	}
	void exgcd(ll a, ll b, ll &x, ll &y) {
	    if (!b) {
	        x = 1;
	        y = 0;
	        return;
	    }
	    ll x1, y1;
	    exgcd(b, a % b, x1, y1);
	    x = y1;
	    y = x1 - (a / b) * y1;
	}
	inline ll mi(ll a, ll b, ll p) {
	    ll ans = 1, tmp = a;
	    while (b) {
	        if (b & 1)
	            ans = gsc(ans, tmp, p);
	        tmp = gsc(tmp, tmp, p);
	        b >>= 1;
	    }
	    return (ans);
	}
	inline ll Rand() {
	    ll a = rand(), b = rand(), c = rand(), d = rand();
	    return ((a << 48) | (b << 32) | (c << 16) | d);
	}
	vector<ll> vec;
	int pri[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	inline int check(ll n) {
	    if (n == 2 || n == 3 || n == 5 || n == 7)
	        return (1);
	    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0)
	        return (0);
	    for (register int i = 0; i < 10; i++) {
	        if (n == pri[i])
	            return (1);
	        ll tmp = n - 1;
	        while (1) {
	            ll cjr = mi(pri[i], tmp, n);
	            if (cjr == n - 1)
	                break;
	            if (cjr != 1)
	                return (0);
	            if (tmp & 1)
	                break;
	            tmp >>= 1;
	        }
	    }
	    return (1);
	}
	inline ll gcd(ll a, ll b) {
	    while (b) {
	        ll r = a % b;
	        a = b;
	        b = r;
	    }
	    return (a);
	}
	inline ll rho(ll n, int c) {
	    ll x = Rand(), y = x, k = 2;
	    while (1) {
	        ll ji = 1;
	        for (register int i = 1; i <= k; i++) x = (gsc(x, x, n) + c) % n, ji = gsc(ji, abs(y - x), n);
	        ll g = gcd(ji, n);
	        if (g > 1)
	            return (g);
	        y = x;
	        k <<= 1;
	    }
	}
	inline void pollard(ll n, int c) {
	    if (n == 1)
	        return;
	    if (check(n)) {
	        vec.push_back(n);
	        return;
	    }
	    while (1) {
	        ll cjr = rho(n, c);
	        c--;
	        if (cjr != n) {
	            while (n % cjr == 0) n /= cjr;
	            ll g = gcd(n, cjr);
	            while (n % g == 0 && g != 1) n /= g;
	            pollard(cjr, c);
	            pollard(n, c);
	            return;
	        }
	    }
	}
	ll dis[2000001];
	int que[5000001];
	unsigned char bv[2000001];
	typedef struct _n {
	    int id;
	    ll n;
	    ll k;
	    friend bool operator<(const _n &a, const _n &b) { return (a.k < b.k); }
	} node;
	node memchi[20001];
	unsigned char anss[20001];
	void ywymain() {
	    srand(19260817);
	    int q;
	    cin >> q;
	    for (register int i = 1; i <= q; i++) {
	        memchi[i].id = i;
	        cin >> memchi[i].n >> memchi[i].k;
	    }
	    sort(memchi + 1, memchi + 1 + q);
	    for (register int x = 1; x <= q; x++) {
	        int cjr = x;
	        while (cjr < q && memchi[cjr + 1].k == memchi[x].k) cjr++;
	        if (memchi[x].k == 1) {
	            x = cjr;
	            continue;
	        }
	        vec.clear();
	        pollard(memchi[x].k, 19260817);
	        sort(vec.begin(), vec.end());
	        if (vec.size() == 1) {
	            for (register int i = x; i <= cjr; i++) {
	                if (memchi[i].n % memchi[i].k == 0)
	                    anss[memchi[i].id] = 1;
	            }
	            x = cjr;
	            continue;
	        }
	        if (vec.size() == 2) {
	            ll X, y;
	            ll p = vec[1], q = vec[0];
	            exgcd(p, q, X, y);
	            X %= q;
	            X += q;
	            X %= q;
	            for (register int i = x; i <= cjr; i++) {
	                ll dx = gsc(X, memchi[i].n, q), dy = memchi[i].n - dx * p;
	                if (dy >= 0)
	                    anss[memchi[i].id] = 1;
	            }
	            x = cjr;
	            continue;
	        }
	        for (register int i = 0; i < vec[0]; i++) dis[i] = 0x7f7f7f7f7f7f7f7f;
	        int head = 0, tail = 1;
	        que[0] = 0;
	        dis[0] = 0;
	        do {
	            int me = que[head];
	            head++;
	            bv[me] = 0;
	            for (register int i = 1; i < vec.size(); i++) {
	                int dst = (me + vec[i]) % vec[0];
	                if (dis[me] + vec[i] < dis[dst]) {
	                    dis[dst] = dis[me] + vec[i];
	                    if (!bv[dst])
	                        bv[dst] = 1, que[tail] = dst, tail++;
	                }
	            }
	        } while (head < tail);
	        for (register int i = x; i <= cjr; i++) {
	            if (dis[memchi[i].n % vec[0]] <= memchi[i].n)
	                anss[memchi[i].id] = 1;
	        }
	        x = cjr;
	    }
	    for (register int i = 1; i <= q; i++)
	        if (anss[i])
	            printf("YES\n");
	        else
	            printf("NO\n");
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：elbissoPtImaerD (赞：2)

[LJ07](https://www.luogu.com.cn/user/312306) 好厉害。

显然要关于 $k$ 离线。

对于固定的 $k$，关于 $k$ 的质因子的个数讨论：

1. 如果 $k$ 是形如 $p^\alpha$ 的素数幂

只需判断 $p|n$ 即可。

2. 否则

我们可以跑类似同余最短路。

当 $\min p_i$ 很大的时候，过不去。

**但是，极限数据只能在形如 $k=p_1^{\alpha_1}p_2^{\alpha_2}$ 才能成立。**

这种情况我们可以跑 exgcd。

所以，在 $k$ 的质因子个数为 $2$ 时用 exgcd 判断不定方程存在正整数解，$>2$ 时跑同余最短路。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/986/submission/224719318)！

---

## 作者：ducati (赞：2)

## Description

[传送门](https://www.luogu.com.cn/problem/CF986F)

## Solution

根据置换环的性质，问题等价于：判断 $n$ 能否拆分为若干 $k$ 因数的和，每个因数可被用多次。

注意到，我们只会使用 $k$ 的**质因子**，不妨设为 $p_1,p_2,\cdots,p_t(p_1 < p_2 < \cdots < p_t)$。

- 当 $k$ 为质数时，有解 $\iff n \equiv 0 \pmod k$。
- 当 $k$ 有两个质因子时，使用 exgcd 即可。
- 当 $k$ 的质因子数 $>2$ 时，最小的质因子 $p_0 \le k^{\frac 1 3} \le 10^5$。考虑经典的同余最短路模型，建出 $p_0$ 个点，编号由 $0$ 至 $p_0 - 1$，对于每个质因子 $x$，$\forall i \in [0,p_0)$，连边 $i \to (i+x) \bmod p_0$，边权为 $x$，则有解 $\iff$ $0$ 到 $n \bmod p_0$ 的最短路长度 $\le n$。
  - 实际上我们不必用 dijkstra。注意到模意义下的加法有结合律、交换律，我们可以钦定先走边权为 $p_1$ 的边，再走边权为 $p_2$ 的边，以此类推。对于每一种 $p_i$，所有边权为 $p_i$ 的边组成若干个环，在每个环上绕两圈更新最短路即可。
  - 当 $k \in [1,10^{15}]$ 时有 $t \le 13$，因此边数 $\le 1.3 \times 10^6$，复杂度与边数同级。本质不同的 $k$ 不超过 $50$ 个，可以接受。
  
至于如何求 $p_1,p_2,\cdots,p_k$，可以暴力枚举 $[2,\sqrt k]$ 中的质数，复杂度 $O(\sqrt {\max k}) - O(\frac {\sqrt k} {\ln k})$；也可以使用 Pollard-Rho，单次 $O(k^{\frac 1 4})$。
  
## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define lll __int128_t
using namespace std;
const int Q=1e4+5,N=1e5+5,inf=2e18;
const int ckp[8]={2,3,5,7,11,13,82,373}; mt19937 rnd(random_device{}());

int read(){
	int s=0; char ch=getchar();
	while (ch<'0'||ch>'9')  ch=getchar();
	while (ch>='0'&&ch<='9')  s=(s<<1)+(s<<3)+(ch^'0'),ch=getchar();
	return s;
}
inline void chkmin(int x,int &y){if(x<y)y=x;}

int k,q,qn[Q],qk[Q],ans[Q],dis[N]; vector<int> primes;
int quick_power(int x,int y,const int mod){
	int res=1;
	for (;y;y>>=1,x=((lll)x*x)%mod){
		if (y&1)  res=((lll)res*x)%mod;
	}
	return res;
}
bool Miller_Rabin(int n){
	if (n==2||n==3||n==5||n==7||n==11||n==13||n==41||n==373)  return true;
	if (n<2||n==82||!(n&1)||n%3==0)  return false;

	int u=n-1,v=0;
	while (!(u&1))  u>>=1,v++;
	for (int i=0;i<8;i++){
		auto Test=[&](){
			int x=quick_power(ckp[i],u,n);
			if (x==1)  return true;
			for (int j=1;j<=v;j++){
				if (x==n-1)  return true;
				x=((lll)x*x)%n;
			}
			return false;
		};
		if (!Test())  return false;
	}
	return true;
}
int Rho(int n){
	int s=0,seed=uniform_int_distribution<int>(1,n-1)(rnd);
	for (int k=1;;k<<=1){
		int t=s,tot=1;
		for (int i=1;i<=k;i++){
			t=((lll)t*t+seed)%n;
			if (s==t)  return n;

			tot=((lll)tot*(t+n-s))%n;
			if (!(i&63)){
				int tmp=__gcd(tot,n);
				if (tmp>1)  return tmp;
			}
		}
		int tmp=__gcd(tot,n);
		if (tmp>1)  return tmp;
		s=t;
	}
}
void Pollard(int n){
	if (n<2)  return;
	if (Miller_Rabin(n)) {primes.emplace_back(n);return;}

	int mf=n;
	while (mf==n)  mf=Rho(n);
	while (n%mf==0)  n/=mf;
	Pollard(mf),Pollard(n);
}
void Pollard_Rho(int n){primes.clear(),Pollard(n);}

bool Euclid(lll n,lll u,lll v){
	lll x,y;
	function<void(lll,lll,lll)> exgcd=[&](lll u,lll v,lll w){
		if (!v) {x=w,y=0;return;}
		exgcd(v,u%v,w),x=y,y=(w-x*u)/v;
	};
	exgcd(u,v,n),y=(y%u+u)%u;
	return v*y<=n;
}
signed main(){
	q=read(),memset(ans,-1,sizeof(ans));
	for (int i=1;i<=q;i++)  qn[i]=read(),qk[i]=read();
	for (int id=1;id<=q;id++)if(ans[id]<0){
		k=qk[id],Pollard_Rho(k),sort(primes.begin(),primes.end());
		primes.erase(unique(primes.begin(),primes.end()),primes.end());
		if (primes.empty()){
			for (int j=id;j<=q;j++){
				if (qk[j]==k)  ans[j]=0;
			}
		}
		else if (primes.size()==1u){
			for (int j=id;j<=q;j++){
				if (qk[j]==k)  ans[j]=(qn[j]%primes[0]==0);
			}
		}
		else if (primes.size()==2u){
			int u=primes[0],v=primes[1];
			for (int j=id;j<=q;j++){
				if (qk[j]==k)  ans[j]=Euclid(qn[j],u,v);
			}
		}
		else{
			int p0=primes[0]; fill(dis+1,dis+p0,inf);
			for (int p:primes)if(p^p0){
				int cnt_cir=__gcd(p,p0);
				for (int s=0;s<cnt_cir;s++){
					vector<int> nd; nd.emplace_back(s);
					for (int i=s;;){
						i=(i+p)%p0;
						if (i^s)  nd.emplace_back(i);
						else break;
					}
					int sz=nd.size(); nd.emplace_back(s);
					for (int t=0;t<2;t++){
						for (int i=0;i<sz;i++)  chkmin(dis[nd[i]]+p,dis[nd[i+1]]);
					}
				}
			}
			for (int j=id;j<=q;j++){
				if (qk[j]==k)  ans[j]=(qn[j]>=dis[qn[j]%p0]);
			}
		}
	}
	for (int i=1;i<=q;i++)  puts(ans[i]?"YES":"NO");
	return 0;
}
```


---

## 作者：SIGSEGV (赞：2)

不同 $k$ 的数目不超过 $50$，因此先将询问按照 $k$ 分类。

发现如果 $n$ 能被表示成若干个 $k$ 的因子之和， 则$n$ 一定也能被表示成若干个 $k$ 的质因子之和：每个非质因子一定能被表示成 $pq$ 的形式，其中 $p$ 为质数，将该非质因子拆成 $q$ 个 $p$ 连加即可。

先将 $k$ 质因子分解。可以使用Pollard-Rho，不过$10^{7.5}$内的质数只有约 $\dfrac{10^{7.5}}{\ln{10^{7.5}}}$ 个，分解 $50$ 个数的复杂度连同筛质数的复杂度大约在 $1.2\times 10^8$ 级别，依旧可以通过。

设 $k$ 的质因子集合为 $P_k$ 。若 $|P_k|=1$ ，即 $k$ 为质数，直接判断 $n$ 是否为 $k$ 的倍数。

若 $|P_k|=2$， 设 $P_k$ 中的两个元素分别为 $x,y$ ，则题目相当于询问是否存在两个自然数 $(a,b)$ 使得$ax+by=n$。将其变形得 $by\equiv n\pmod{x}$，求解逆元再带回原式检验。

$|P_k|\ge 3$ 时，直接列出方程求方程是否有解很难做，但是 $\min\{P_k\}\le 10^5$，可以利用同余最短路解决：设 $k$ 的最小质因子为 $g$，$dis_x$ 表示满足$n\bmod g=x$的可以被表示出来的最小的 $n$，对每个质因子 $p\in P_k,p\ne g$ 和满足 $0\le x<g$ 的 $x$，都从 $x$ 向 $(x+p)\bmod g$ 连边，权值为 $p$，从 $0$ 跑最短路可解出 $dis$。之后对于每个 $n$ 判断 $dis_{n\bmod g}\le n$ 是否成立。具体可见P3403。


```cpp
const int N = 100005,M = 10005;
int n;map<ll,vector<pair<ll,int>>> mp;bool ans[M];
inline ll mul(ll x,ll y,ll P);
ll qpow(ll a,ll b,ll P);
ll gcd(ll x,ll y) {return y ? gcd(y,x % y) : x;}
namespace PR
{    
    set<ll> get_fac(ll x); // 将x质因数分解并返回质因子集合
}
ll dis[N];
int main ()
{
    ios::sync_with_stdio(false);srand(time(0));
    cin >> n;ll t1,t2;
    for (int i = 1;i <= n;i++) cin >> t1 >> t2,mp[t2].push_back({t1,i});
    for (auto &t : mp)
    {
        ll kk = t.first;if (kk == 1) continue;
        auto st = PR::get_fac(kk);
        if (st.size() == 1)
        {
            for (auto &i : t.second) ans[i.second] = !(i.first % kk);
            continue;
        }
        if (st.size() == 2)
        {
            ll x = *st.begin(),y = *st.rbegin();
            for (auto &i : t.second)
            {
                ll c = i.first;int id = i.second;if (c % x == 0) {ans[id] = 1;continue;}
                ll b = c % x * qpow(y,x - 2,x) % x;ans[id] = b * y <= c;
            }
            continue;
        }
        vector<ll> f(st.begin(),st.end());
        int x = f[0];f.erase(f.begin());
        for (int i = 0;i < x;i++) dis[i] = -1;
        dis[0] = 0;priority_queue<pair<ll,int>> pq;pq.push({0,0});
        while (!pq.empty())
        {
            auto nd = pq.top();pq.pop();int p = nd.second;if (nd.first != -dis[p]) continue;
            for (auto &i : f)
            {
                int np = (p + i) % x;
                if (dis[np] == -1 || dis[np] > dis[p] + i)
                    dis[np] = dis[p] + i,pq.push({-dis[np],np});
            }
        }
        for (auto &i : t.second) ans[i.second] = dis[i.first % x] <= i.first;
    }
    for (int i = 1;i <= n;i++) cout << (ans[i] ? "YES" : "NO") << endl;
    return 0;   
}
```

---

## 作者：Yansuan_HCl (赞：1)

首先把质因数用 Pollard-Rho 分解出来不讲。

$k$ 很大，尝试数据分治。记 $k$ 的质因子数量为 $f$。

- $f=1$ 时判断 $[k\mid n]$ 即可。
- $f=2$ 时，即求 $ax+by=n$ 是否有非负整数解，其中 $a$、$b$ 是 $k$ 的两个质因子。

> 可以 ExGCD 求出 $ax+by=\gcd(a,b)$ 的一组特解 $(x_0,y_0)$，此时该方程的通解为 $x=x_0 + t\cdot d_x, y = y_0 - t\cdot d_y$，其中 $d_x=b/\gcd(a,b)$，$d_y=a/\gcd(a,b)$。
>
> 方程乘上 $n/\gcd(a,b)$ 变为原方程，则特解的值也乘上 $n/\gcd(a,b)$，而 $d_x,d_y$ 不变。 所以可以求出原方程的通解 $x=x_1 + t\cdot d_x, y = y_1 + t\cdot d_y$。取 $x$ 为最小整数解，则 $y$ 有最大值，判断 $y$ 是否 $\ge 0$ 即可。

- $f\ge 3$ 时不足以用正常的方法求解。考虑不到 $k$ 是质因数相乘，有：最小的质因数 $F_0\le k^{1/3}$。于是可以**同余最短路**求用其余质因子凑出模 $F_0$ 为 $d$ 的最小整数，即可判定能否在 $n$ 以内凑出。

```cpp
#include <bits/stdc++.h>
#define ms(x, v) memset(x, v, sizeof(x))
#define il __attribute__((always_inline)) static
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
using namespace std;

typedef unsigned long long ull;
typedef __int128 ll;
template <class T> using BS = basic_string<T>;

//const int SZ(1 << 23);
//unsigned char buf[SZ], *S, *Q;
//#define getchar() ((S==Q)&&(Q=buf+fread(S=buf,1,SZ,stdin)),S==Q?EOF:*S++)
template <class T> void rd(T& s) {
	int c = getchar(); T f = 1; s = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { s = s * 10 + (c ^ 48); c = getchar(); }
	s *= f;
}
template <class T, class... Y> void rd(T& x, Y&... y) { rd(x), rd(y...); }
#define meow(...) fprintf(stderr, __VA_ARGS__)
#define Assert(e, v) if (!(e)) exit(v);

// 同余最短路求解不定方程

namespace PR {
	ll quick_pow(ll x, ll p, ll mod) {  // ???
	  ll ans = 1;
	  while (p) {
	    if (p & 1) ans = ans * x % mod;
	    x = x * x % mod;
	    p >>= 1;
	  }
	  return ans;
	}
	
	bool Miller_Rabin(ll p) {  // ????
	  if (p < 2) return 0;
	  if (p == 2) return 1;
	  if (p == 3) return 1;
	  ll d = p - 1, r = 0;
	  while (!(d & 1)) ++r, d >>= 1;  // ?d?????
	  for (ll k = 0; k < 10; ++k) {
	    ll a = rand() % (p - 2) + 2;
	    ll x = quick_pow(a, d, p);
	    if (x == 1 || x == p - 1) continue;
	    for (int i = 0; i < r - 1; ++i) {
	      x = x * x % p;
	      if (x == p - 1) break;
	    }
	    if (x != p - 1) return 0;
	  }
	  return 1;
	}
	
	ll absll(ll x) { return x < 0 ? -x : x; }
	ll Pollard_Rho(ll x) {
	  ll s = 0, t = 0;
	  ll c = (ll)rand() % (x - 1) + 1;
	  int step = 0, goal = 1;
	  ll val = 1;
	  for (goal = 1;; goal *= 2, s = t, val = 1) {  // ????
	    for (step = 1; step <= goal; ++step) {
	      t = ((__int128)t * t + c) % x;
	      val = (__int128)val * absll(t - s) % x;
	      if ((step % 127) == 0) {
	        ll d = __gcd(val, x);
	        if (d > 1) return d;
	      }
	    }
	    ll d = __gcd(val, x);
	    if (d > 1) return d;
	  }
	}
	
	vector<ll> f;
	void fac(ll x) {
	  if (x < 2) return;
	  if (Miller_Rabin(x)) {              // ??x???
	  	f.push_back(x);
//	    max_factor = max(max_factor, x);  // ????
	    return;
	  }
	  ll p = x;
	  while (p >= x) p = Pollard_Rho(x);  // ?????
	  while ((x % p) == 0) x /= p;
	  fac(x), fac(p);  // ??????x?p
	}
}

vector<ll> getFac(ll x) {
	vector<ll> &f = PR::f;
	f.clear();
	PR::fac(x);
	sort(f.begin(), f.end());
	f.erase(unique(f.begin(), f.end()), f.end());
	return f;
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		x = 1; y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, y, x);
	y = y - a / b * x;
	return d;
}

map<ll, vector<pair<ll, int>>> qr;

const int N = 100005;
bool ans[N];

void solve(ll k, vector<pair<ll, int>> &vec) {
	if (k == 1) {
		return;
	}
	vector<ll> f = getFac(k);
	if (f.size() == 1) {
		for (auto [n, i] : vec)
			ans[i] = !(n % f[0]);
		return;
	} else if (f.size() == 2) {
		ll x0, y0, g = exgcd(f[0], f[1], x0, y0);
		ll dx = f[1] / g, dy = f[0] / g;
		for (auto [n, i] : vec) {
			if (n % g) continue;
			ll x = x0 * (n / g);
			((x %= dx) += dx) %= dx;
			ll by = n - f[0] * x;
			if (by >= 0)
				ans[i] = 1;
		}
		return;
	}
	
	ll dis[N]; memset(dis, 0x3f, 16 * (f[0] + 2));
	static BS<pair<int, ll>> g[N]; static bool vis[N];
	U (i, 0, f[0]) g[i].clear(), vis[i] = 0;
	
	dis[0] = 0;
	for (ll i : f) if (i != f[0]) {
		U (j, 0, f[0] - 1)
			g[j].push_back({(j + i) % f[0], i});
	}
	priority_queue<pair<ll, int>> pq; pq.push({0, 0});
	while (pq.size()) {
		auto [d, u] = pq.top(); pq.pop(); d = -d;
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto &[v, w] : g[u]) if (dis[v] > d + w) {
			dis[v] = dis[u] + w;
			pq.push({-dis[v], v});
		}
	}
	
	for (auto [n, i] : vec)
		ans[i] = (n >= dis[n % f[0]]);
}

int main() {
//	freopen("arrebol.in", "r", stdin);
	
	int T; rd(T);
	U (i, 1, T) {
		ll n, k; rd(n, k);
		qr[k].push_back({n, i});
	}
	for (auto &[k, vec] : qr)
		solve(k, vec);
	U (i, 1, T)
		puts(ans[i] ? "YES" : "NO");
}
```

---

## 作者：blackname (赞：1)

转化为不同质因数能不能凑出来 $n$，证明不赘述

若 $k$ 质因数个数不超过 $1$，是平凡的

若 $k$ 质因数个数为 $2$，exgcd 算算即可，你甚至可以枚举大质因子的使用次数，然后利用小凯的疑惑那个上界可知使用次数估计也就根号级别，那 $50\sqrt{k}$ 说不定也能跑

若 $k$ 质因子个数超过 $3$，考虑最小的那两个乘起来不超过 $\sqrt{k}$，设其为 $p_1,p_2$，则只需要考虑 $p_1\times p_2-p_1-p_2$ 以内的这些数，那直接做背包就差不多了，当然乘个 $50$ 可能跑不了，但是可以 bitset 再除个 $w$，那就能跑了

若 $k$ 质因子个数为 $3$，设为 $p_1<p_2<p_3$，同样考虑小凯的疑惑的结论，只需要解决 $p_1\times p_2-p_1-p_2$ 以内的数。如果能对于每个 $k$ 枚举 $p_2,p_3$ 使用次数的话，记一下模 $p_1$ 下所有余数对应的最小的 $xp_2+yp_3$，就行了，但这玩意单次预处理复杂度 $k^{\frac{2}{3}}$，不是很行

那么设一个块长 $B$，枚举 $p_3$ 使用次数，再枚举 $p_2$ 使用次数除 $B$ 下取整，然后每次询问枚举 $p_2$ 使用次数模 $B$，如果取 $B=k^{\frac{1}{6}}$ 的话，有关 $B$ 的复杂度大概是 $Tk^{\frac{1}{6}}+50\sqrt{k}$，在算量上仍有差距，可以适当调大 $B$ 使得后面那项较小，基本可以通过（其实这玩意没啥常数，跑起来可快了）

---

## 作者：orz_z (赞：1)

### CF986F

给定 $n$ 与 $k$，问是否能将 $n$ 分为若干个 $k$ 的非 $1$ 因数之和，每个因数都可以被选多次。


一共 $T$ 组询问。

对于每组询问，若满足输出 `Yes`，否则输出 `No`。

对于 $100\%$ 的数据，保证 $1 \leq T \leq 10^4,1 \leq n \leq 10^{18},1 \leq k \leq 10^{15}$ 且最多有 $50$ 种不同的 $k$。

#### sol


首先发现，若 $n$ 能被表示成若干个 $k$ 的非 $1$ 因数之和，则 $n$ 也一定能被表示成若干个 $k$ 的质因子之和。

证明：每个 $k$ 的非质因子一定能被表示成 $pq$ 的形式，其中 $p$ 为质数，则将该非质因子拆成 $q$ 个 $p$ 相加即可。

然后考虑将$k$ 质因子分解，设 $k=\prod_{i=1}^{d}p_i^{q_i}$，其中 $p_i$ 为质数，$q_i$ 为自然数。

由于不同的 $k$ 最多只有 $50$ 个，所以可以考虑筛完质数后枚举分解，由于 $10^{7.5}$ 的质数只有约 $\frac{10^{7.5}}{\ln 10^{7.5}}$ 个，所以这部分总时间复杂度大约在 $1.2\times 10^{8}$ 级别，可过。（当然也可以用 `Pollard-Rho` 分解）

再对 $d$ 分类讨论：

* $d=0$：显然，$k=1$，无解。
* $d=1$：显然，$k \in \mathbb{P}$，直接判断 $[k|n]$ 即可。
* $d=2$：设 $k=x^u y^v$，那么题意转换为判断是否 $\exists a,b \in [0,\infty] \cap \mathbb{Z},ax+by=n$，假设有解，显然有 $b$ 的最小值 $b_{min}=n\times y^{-1} \bmod x$，最后判断 $[y \times b_{min} \leq n]$ 即可。
* $d \geq 3$：根据上面的思路，题意转换为判断是否 $\exists x_1,x_2,\cdots,x_m \in [0, \infty] \cap \mathbb{Z},\sum_{i=1}\limits^{d}p_ix_i=n$，直接检验貌似有点棘手，不过不难发现有一个性质，那就是对于任意 $x_i$ 如果 $n$ 可行，那么 $n+zp_i$ 也可行，发现这类似于同余。

于是引入一个算法：同余最短路。

考虑令 $dis_i$ 表示能被表示出来的满足 $u \bmod p_1=i$ 的最小的 $u$。

于是对于一个询问 $n$，只需判断 $[dis_{n \bmod p_1} \leq n]$ 即可。

那么怎么计算 $dis$ 呢？

转到图上，对于所有 $2 \leq i \leq d,0 \leq j < p_1$，连边 $j \to (j+p_i)\bmod p_1$，权值为 $p_i$，从 $0$  开始使用最短路算法即可得到 $dis$。 

可以发现，$d \leq 13$，边数是 $\mathcal O(d\sqrt[3]{k})$ 的，点数是 $\mathcal O(\sqrt[3]{k})$ 的，可过。

总时间复杂度为 $\mathcal O(T \log k+50\times d \sqrt[3]{k}\log k)$，可过。

~~最优解~~

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace PR
{
	typedef long long ll;
#define lll __int128

	template <class kkk>
	inline kkk qr(kkk sample)
	{
		kkk ret = 0, sgn = 1;
		char cur = getchar();
		while (!isdigit(cur))
			sgn = (cur == '-' ? -1 : 1), cur = getchar();
		while (isdigit(cur))
			ret = (ret << 1) + (ret << 3) + cur - '0', cur = getchar();
		return sgn == -1 ? -ret : ret;
	}

	ll max_factor;

	inline ll gcd(ll a, ll b)
	{
		if (b == 0)
			return a;
		return gcd(b, a % b);
	}

	inline ll qp(ll x, ll p, ll mod)
	{
		ll ans = 1;
		while (p)
		{
			if (p & 1)
				ans = (lll)ans * x % mod;
			x = (lll)x * x % mod;
			p >>= 1;
		}
		return ans;
	}

	inline bool mr(ll x, ll b)
	{
		ll k = x - 1;
		while (k)
		{
			ll cur = qp(b, k, x);
			if (cur != 1 && cur != x - 1)
				return false;
			if ((k & 1) == 1 || cur == x - 1)
				return true;
			k >>= 1;
		}
		return true;
	}

	inline bool prime(ll x)
	{
		if (x == 46856248255981ll || x < 2)
			return false;
		if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251)
			return true;
		return mr(x, 2) && mr(x, 61);
	}

	inline ll f(ll x, ll c, ll n)
	{
		return ((lll)x * x + c) % n;
	}

	inline ll PR(ll x)
	{
		ll s = 0, t = 0, c = 1ll * rand() % (x - 1) + 1;
		int stp = 0, goal = 1;
		ll val = 1;
		for (goal = 1;; goal <<= 1, s = t, val = 1)
		{
			for (stp = 1; stp <= goal; ++stp)
			{
				t = f(t, c, x);
				val = (lll)val * abs(t - s) % x;
				if ((stp % 127) == 0)
				{
					ll d = gcd(val, x);
					if (d > 1)
						return d;
				}
			}
			ll d = gcd(val, x);
			if (d > 1)
				return d;
		}
	}

	inline void fac(ll x, set<ll> &st)
	{
		if (x <= max_factor || x < 2)
			return;
		if (prime(x))
		{
			st.insert(x);
			return;
		}
		ll p = x;
		while (p >= x)
			p = PR(x);
		while ((x % p) == 0)
			x /= p;
		fac(x, st), fac(p, st);
	}

	inline set<ll> get(ll x)
	{
		set<ll> st;
		fac(x, st);
		return st;
	}
}

using namespace PR;

inline ll read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

const int _ = 1e7 + 7;

int T, ans[10007];

ll n, k, dis[_];

map<ll, vector<pair<ll, int> > > mp;

inline ll qpow(ll x, ll y, ll mod)
{
	ll res = 1;
	while(y)
	{
		if(y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}

signed main()
{
	T = read();
	for(int i = 1; i <= T; ++i)
	{
		ll x = read();
		mp[read()].push_back({x, i});
	}
	for(auto t : mp)
	{
		ll k = t.first;
		if(k == 1) continue;
		auto d = get(k);
		if(d.size() == 1)
		{
			for(auto i : t.second) ans[i.second] = !(i.first % k);
			continue;
		}
		if(d.size() == 2)
		{
			ll x = *d.begin(), y = *d.rbegin();
			for(auto i : t.second)
			{
				ll c = i.first, id = i.second;
				if(c % x == 0)
				{
					ans[id] = 1;
					continue;
				}
				ll b = c % x * qpow(y, x - 2, x) % x;
				ans[id] = b * y <= c;
			}
			continue;
		}
		vector<ll> f(d.begin(), d.end());
		int x = f[0];
		f.erase(f.begin());
		for(int i = 0; i < x; ++i) dis[i] = -1;
		dis[0] = 0;
		priority_queue<pair<ll, int>> q;
		q.push({0, 0});
		while(!q.empty())
		{
			auto now = q.top();
			q.pop();
			int p = now.second;
			if(now.first != -dis[p]) continue;
			for(auto i : f)
			{
				int tmp = (p + i) % x;
				if(dis[tmp] == -1 || dis[tmp] > dis[p] + i)
				{
					dis[tmp] = dis[p] + i;
					q.push({-dis[tmp], tmp});
				}
			}
		}
		for(auto i : t.second) ans[i.second] = dis[i.first % x] <= i.first;
	}
	for(int i = 1; i <= T; ++i) cout << (ans[i] ? "YES" : "NO") << "\n";
	return 0;
}
```



---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/986/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF986F)

~~感谢此题教会我一个东西叫做同余最短路（大雾~~

首先这个不同 $k$ 的个数 $\le 50$ 这个条件显然是让我们对每个 $k$ 进行一遍预处理并快速求出答案。怎么预处理呢？首先考虑一个非常 trivial 的性质，那就是所有 $k$ 的非质数因子显然可以表示成质因子的和对吧，所以一个数能够表示成 $k$ 的若干个质因子的和，当且仅当它能够表示成 $k$ 的若干个质因子的和。因此考虑先对 $k$ 进行一遍质因数分解——可以使用 PR 算法，但是我不会，每次 $\sqrt{k}$ 地分解会超时，这里有一个简单的技巧，之前暑假某场模拟赛出现过，就是显然我们只会用到 $\le\sqrt{k}$ 的所有**质因子**，因此可以考虑预处理出 $\le \sqrt{10^{15}}$ 的所有质数，然后每次分解遍历一遍这个质数集合即可，这样分解的复杂度可以降到 $\sqrt{10^{15}}·\dfrac{1}{\ln 10^{15}}·50$。

考虑怎样计算答案，如果 $k$ 本身就是质数那显然只有 $k$ 的倍数能够表示成 $k$ 的 $\ne 1$ 的质因子之和。直接判断一下 $n\bmod k=0$ 是否成立即可。如果 $k$ 有两个质因子，那么假设 $k$ 两个质因子分别为 $x,y$，那么我们需检验是否 $\exists a,b\in[0,\infty)\cap\mathbb{Z},s.t.ax+by=n$，显然必须有 $by\equiv n\pmod{x}$，那么 $b$ 的最小值 $b_{\min}=n·y^{-1}\bmod x$，检验一下是否有 $b_{\min}·y\le n$ 即可。

如果 $k$ 质因子个数 $\ge 3$，那么假设 $k$ 的质因子分别为 $p_1,p_2,\cdots,p_m$，那么我们需检验是否 $\exists x_1,x_2,\cdots,x_m\in[0,\infty)\cap\mathbb{Z},s.t.\sum\limits_{i=1}^mp_ix_i=n$，直接检验貌似有点棘手，不过不难发现有一个性质，那就是对于任意 $x_i$ 及 $n$，如果 $n$ 可行，那么 $n+zp_i$ 也可行，也就是说对于所有 $j\in[0,p_i)$，必然存在一个界 $lim_j$，满足所有 $\bmod x_i=j$ 的数当中，所有 $\ge lim_j$ 的数都符合要求，所有 $<lim_j$ 的数都符合要求，考虑怎样求 $lim_j$，显然 $lim_0=0$，而对于所有 $j\in[0,x_i),t\in[1,m]$，显然 $lim_{(j+p_t)\bmod p_1}\le lim_j+p_t$，这是一个最短路的形式，用 dijkstra 转移即可。并且不难发现对于 $k\le 10^{15}$，这种情况下 $k$ 最小的质因子必然 $\le 10^5$，因此我们对 $k$ 最小质因子跑同余最短路即可实现 $10^5\log 10^5·50$ 的复杂度。

~~话说这场的 D、E，尤其是那个恶心无比的 D……勾起了远古回忆~~

```cpp
const int MAXN=1e4;
const int MAXK=1e5;
const int MAXV=3.163e7;
int qpow(int x,int e,int mod){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%mod) if(e&1) ret=1ll*ret*x%mod;
	return ret;
}
int qu,pr[MAXV/8+5],prcnt,vis[MAXV+5];
void sieve(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i]) pr[++prcnt]=i;
		for(int j=1;j<=prcnt&&pr[j]*i<=n;j++){
			vis[pr[j]*i]=1;if(i%pr[j]==0) break;
		}
	}
}
int res[MAXN+5];
map<ll,vector<pair<ll,int> > > mpv;
vector<ll> decomp(ll v){
	vector<ll> ret;
	for(int i=1;i<=prcnt;i++) if(v%pr[i]==0){
		ret.pb(pr[i]);
		while(v%pr[i]==0) v/=pr[i];
	} if(v>1) ret.pb(v);
	return ret;
}
ll dis[MAXK+5];
int main(){
	sieve(MAXV);scanf("%d",&qu);
	for(int i=1;i<=qu;i++){
		ll n,k;scanf("%lld%lld",&n,&k);
		if(k!=1) mpv[k].pb(mp(n,i));
	}
	for(auto it:mpv){
		ll v=it.fi;vector<pair<ll,int> > qv=it.se;
		vector<ll> pr=decomp(v);
		if(pr.size()==1){
			for(pair<ll,int> p:qv) res[p.se]=(p.fi%pr[0]==0);
		} else if(pr.size()==2){
			ll x=pr[0],y=pr[1],ivy=qpow(y%x,x-2,x);
			for(pair<ll,int> p:qv){
				int bmin=1ll*(p.fi%x)*ivy%x;
				res[p.se]=(p.fi>=1ll*bmin*y);
			}
		} else {
			int x=pr[0];memset(dis,63,sizeof(dis));dis[0]=0;
			priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > q;
			q.push(mp(0,0));
			while(!q.empty()){
				pair<ll,int> p=q.top();q.pop();
				int cur=p.se;
				for(int i=1;i<pr.size();i++){
					if(dis[(cur+pr[i])%x]>dis[cur]+pr[i]){
						dis[(cur+pr[i])%x]=dis[cur]+pr[i];
						q.push(mp(dis[(cur+pr[i])%x],(cur+pr[i])%x));
					}
				}
			}
			for(pair<ll,int> p:qv) res[p.se]=(p.fi>=dis[p.fi%x]);
		}
	}
	for(int i=1;i<=qu;i++) printf("%s\n",(res[i])?"YES":"NO");
	return 0;
}
```



---

