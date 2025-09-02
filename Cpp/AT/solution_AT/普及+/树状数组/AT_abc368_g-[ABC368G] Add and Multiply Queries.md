# [ABC368G] Add and Multiply Queries

## 题目描述

给定两个长度为 $ N $ 的正整数序列 $ A, B $。需要处理 $ Q $ 个按顺序给出的查询。查询有以下三种类型：

- 类型 $ 1 $：格式为 `1 i x`。将 $ A_i $ 替换为 $ x $。
- 类型 $ 2 $：格式为 `2 i x`。将 $ B_i $ 替换为 $ x $。
- 类型 $ 3 $：格式为 `3 l r`。需要解决以下问题并输出答案：
  - 初始时 $ v = 0 $。依次对 $ i = l, l + 1, \dots, r $ 进行操作，每次操作将 $ v $ 替换为 $ v + A_i $ 或 $ v \times B_i $。求最终能得到的 $ v $ 的最大值。
    需要注意的是，输入中类型 $ 3 $ 的查询的答案保证在 $ 10^{18} $ 以下。

## 说明/提示

### 制約

- $ 1 \leq N \leq 10^5 $
- $ 1 \leq A_i \leq 10^9 $
- $ 1 \leq B_i \leq 10^9 $
- $ 1 \leq Q \leq 10^5 $
- 类型 $ 1 $, $ 2 $ 的查询中，$ 1 \leq i \leq N $
- 类型 $ 1 $, $ 2 $ 的查询中，$ 1 \leq x \leq 10^9 $
- 类型 $ 3 $ 的查询中，$ 1 \leq l \leq r \leq N $
- 类型 $ 3 $ 的查询中，输出值在 $ 10^{18} $ 以下

## 样例 #1

### 输入

```
3
3 2 4
1 2 2
3
3 1 3
1 1 1
3 1 3```

### 输出

```
12
7```

## 样例 #2

### 输入

```
6
65 32 12 5 8 312
4 1 3 15 16 2
6
3 2 6
3 1 5
1 5 6
2 4 9
3 2 6
3 3 5```

### 输出

```
46080
69840
27648
1728```

# 题解

## 作者：__Allen_123__ (赞：94)

你正在回顾你的 OI 生涯。

> 你的 OI 生涯共 $n$ 天。你每天可以通过线上训练将你的实力增加 $a_i$，或线下训练将你的实力值乘上 $b_i$。
>
> 你难免会因为你 $n$ 天中的错误决定而后悔，于是你想问自己 $q$ 次，每次询问，你想知道如果可以回到过去，在第 $[l_i,r_i]$ 天之间，假设你初始的实力为 $0$，通过这几天的训练可以获得的最高的实力（不超过 $10^{18}$）。你在这几天内必须要训练且只能通过一种方式训练，即你必须要在实力 $+a_i$ 和 $\times b_i$ 中选择**恰好**一个。
>
> 同时你自己的训练条件也会发生变化，你也想假设某一天有更好或更差的训练条件，即询问中也会包含修改 $a
_i$ 和 $b_i$ 的操作。

作为一名合格的 OIer，在每一天中你必须要**贪心**地选择更优的方案来获得更高的实力。你又观察到你的实力不可能超过 $10^{18}$，如果每个 $b_i=2$，也仅需要大约 $60$ 次就会超过这个限制。于是你意识到，每次询问区间中的 $b_i$ 最多只会有 $60$ 个。

在 $b_i=1$ 的情况下，在普通的县城内过水的、资源匮乏的线下训练并不会改变你的实力，你自然会选择线上训练，将自己的实力增加 $a_i$。

于是你考虑用一个 `set` 记录所有 $b_i\ne 1$ 的点，并用线段树维护 $a_i$ 的区间和，每次询问自己时对区间内每个 $b_i=1$ 的连续子段求区间和，对 $b_i\ne 1$ 的点贪心选择，并解决了自己的所有 $q$ 个疑问。

[你的 AC 代码](https://atcoder.jp/contests/abc368/submissions/57134045)。

你解决自己的疑问之后忽然意识到，$10^{18}$ 不仅是解决你疑问的突破口，更是你最终实力不如他人而落败的根本原因。

这奇怪的上限，是题目的保证，却是你必败之因。纵使你的 OI 生涯时间足够长，乃至到达了十万天，几百年的级别，你却依然挣脱不了它的束缚。

纵使你每次都向最好的方向选择，它却如咒语让你无法突破，如骤雨让你无法再度抬头。它为何存在？你想了半天都找不出最佳的答案。

你回忆起在刚接触 OI 时贫乏的学习资源让你不得不转而投向线上。了解一些知识后在整个县城都数一数二，却在整个省乃至仅仅市区都非常落后，甚至拿不到省一。

你深知线下训练相比线上对实力的影响是指数级的，但你也知道，不从这个基本把 OI 放一边的县城离开去训练，线下的训练对你而言已经过水，对你的实力基本上等同于 $\times1$。究竟是上限影响了资源，还是资源影响了上限？你也不清楚。你只知道，你因此已经成为了一名 OI loser。

你崩溃得嚎啕大哭。但没有人会听你发泄情绪。等你再醒过来时，面前是你的 [AC 记录](https://atcoder.jp/contests/abc368/submissions/57134045)。原来你调完[这道题](https://www.luogu.com.cn/problem/AT_abc368_g)之后疲劳过度睡着了，刚才的一切只是一场梦。

但这场梦异常真实。你也不知道为什么。

---

## 作者：gesong (赞：10)

题目传送门：[[ABC368G] Add and Multiply Queries](https://www.luogu.com.cn/problem/AT_abc368_g)。
# 思路
我们首先考虑三操作的暴力做法，首先我们贪心的想，如果以加上 $a_i$ 更优就加上 $a_i$ 否则就乘上 $b_i$，因此我们假设一开始答案变量是 $ans$，那么每次遍历一个 $i$ 就将 $ans$ 赋值为 $\max(ans+a_i,ans\times b_i)$。

但这个做法最劣的复杂度是 $O(n^2)$ 的我们考虑优化。

我们观察到题目加粗的一句话，它保证答案不超过 $10^{18}$，因此可以得到 $b$ 数组不为一的数最多只有 $\log_2 10^{18}\approx 60$ 个，我们就可以暴力维护 $b$ 数组不为一的数出现的位置，然后我们发现如果 $b_i=1$ 那么一定只会加上 $a_i$，因此在相邻两个 $b_i$ 不为一的位置的中间的贡献一定是这一段 $a_i$ 的和，可以使用树状数组维护。

这样我们就可以得到一个复杂度正确的操作三做法：首先利用二分查找来找到 $b$ 数组不为一的左右端点，设为 $L,R$，然后计算一下 $l$ 到 $L$ 之间的贡献，这里需要注意如果 $l=L$ 一开始只能加不能乘，然后计算一下两个 $b$ 数组不为一之间的贡献，最后算一下 $R$ 到 $r$ 之间的贡献即可。 

注意细节，具体的细节参考代码。
# 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&-x
using namespace std;
const int N=1e5+10;
int a[N],b[N],f[N],c[N],n;
vector<int>d;
inline void add(int i,int x){
	for (;i<=n;i+=lowbit(i)) c[i]+=x;
} 
inline int sum(int i){
	int ans=0;
	for (;i;i-=lowbit(i)) ans+=c[i];
	return ans;
}
inline int get(int l,int r){
	if (l>r) return 0;
	return sum(r)-sum(l-1);
}
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read(),add(i,a[i]);
	for (int i=1;i<=n;i++){
		b[i]=read();
		if (b[i]^1) d.push_back(i);
	} 
	d.push_back(1e18);
	int T=read();
	while(T--){
		int op=read(),l=read(),r=read();
		if (op==1) add(l,-a[l]),add(l,r),a[l]=r;
		if (op==2){
			if (b[l]^1) d.erase(lower_bound(d.begin(),d.end(),l));
			b[l]=r;
			if (b[l]^1) d.insert(lower_bound(d.begin(),d.end(),l),l);
		} 
		if (op==3){
			int xx=lower_bound(d.begin(),d.end(),l)-d.begin();
			int yy=upper_bound(d.begin(),d.end(),r)-d.begin()-1;
			if (yy<0||d[yy]<d[xx]){
				cout<<get(l,r)<<endl;
				continue;
			} 
			int ans=0;
			if (d[xx]>l) ans+=get(l,d[xx]-1);
			if (d[xx]==l){
				ans=get(l,l),xx++;
				if (xx<=yy){
					ans+=get(l+1,d[xx]-1);
				}
				else{
					printf("%lld\n",get(l,r));
					continue;
				}
			} 
			for (int i=xx;i<yy;i++){
				ans=max(ans*b[d[i]],ans+a[d[i]]);
				ans+=get(d[i]+1,d[i+1]-1);
			}
			ans=max(ans*b[d[yy]],ans+a[d[yy]]);
			if (d[yy]<r) ans+=get(d[yy]+1,r);
			cout <<ans<<endl;
		}
	}
    return 0;
}


```

---

## 作者：_AyachiNene (赞：6)

# 思路:
首先有一个显然的贪心，在每个位置选会让答案更大的操作。题目说了答案不会超过 $10^{18}$，可以发现对答案有贡献的操作次数会很少，这里分讨一下：

1. $b_i\leq 1$ 显然直接加法。
2. $b_i>1$ 用乘法答案至少增加一倍，如果要用加法，那么答案就要比乘法大，也至少增加一倍。

所以发现只有 $b_i>1$ 的位置需要枚举，其他地方都是加法，而这样的位置很少。然后就很简单了，用个 set 维护每个 $b_i>1$ 的位置， 用树状数组维护 $a_i$ 的前缀和，修改显然，查询用 set 枚举下一个可能对答案产生贡献的位置。

# Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,q;
int a[114514],b[114514];
namespace Nene
{
	int t[114514];
	inline int lowbit(int x){return x&-x;}
	inline void add(int x,int v){for(;x<=n;x+=lowbit(x))t[x]+=v;}
	inline int Query(int x){int res=0;for(;x;x-=lowbit(x))res+=t[x];return res;}
	inline int query(int l,int r){if(l>r)return 0;return Query(r)-Query(l-1);}
}
using namespace Nene;
set<int>s;
signed main()
{
	read(n);
	for(int i=1;i<=n;i++) read(a[i]),add(i,a[i]);
	for(int i=1;i<=n;i++) read(b[i]);
	for(int i=1;i<=n;i++) if(b[i]>1) s.insert(i);
	read(q);
	s.insert(n+1);
	while(q--)
	{
		int op,x,y;
		read(op,x,y);
		if(op==1) 
		{
			add(x,-a[x]);
			a[x]=y;
			add(x,y);
		}
		else if(op==2)
		{
			if(b[x]>1) s.erase(s.find(x));
			b[x]=y;
			if(y>1) s.insert(x);
		}
		else
		{
			int cnt=0,ans=a[x],p=x+1;
			while(p<=y)
			{
				int nxt=*s.lower_bound(p);
				if(nxt>y) 
				{
					ans+=query(p,y);
					break;
				}
				ans+=query(p,nxt-1);
				ans=max(ans*b[nxt],ans+a[nxt]);
				p=nxt+1;
			}
			write(ans),putch('\n');
		}
	}
	flush();
}
```

---

## 作者：Ace_FutureDream (赞：4)

ABC 怎么越来越唐了？谨记唯一一次 AC G题的 ABC 比赛，可惜了还是 Unrated。

## 题目大意：
给定长度为 $n$ 的正整数序列 $a$ 和 $b$。

按给定的顺序处理以下给出的 $q$ 次操作和询问。每个操作和询问都属于以下三种类型之一。

- 类型 $1$：以 `1 i x` 的形式给出。将 $a_i$ 替换为 $x$ 。

- 类型 $2$：以 `2 i x` 的形式给出。将 $b_i$ 替换为 $x$ 。

- 类型 $3$：以 `3 l r` 形式给出。最初，设 $v=0$。对于此询问中的 $l \le i\le r$，从左到右**依次**可选择将 $v$ 变成 $v+a_i$ 或 $v\times b_i$。请输出 $v$ 的最大可能值。保证给定类型 $3$ 查询的答案最多为 $10^{18}$。
## 题解：
我们可以发现若 $b_i=1$，那么选择 $+a_i$ 操作一定更优，若 $b_i>1$，那么可以直接贪心的选择其中一个。

由于答案上界为 $10^{18}$，那么你发现每次选择 $\times b_i$ 至少翻一倍，也就是说你选择 $\times b_i$ 的次数最多 $\log v$ 次，即 $b_i\ge 2$ 的个数最多 $\log v$ 个。

所以我们可以用一个 $\text{set}$ 存储所有 $b_i\ge 2$ 的下标，每次询问操作我们就对于 $b_i=1$ 的位置求和，$b_i\ge 2$ 的位置暴力贪心即可，时间复杂度 $O(n\log n\log v)$。

## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[100010],b[100010];
int v[100010],tot,n;
set<int>st;
struct Tree{
	int tr[200010];
	inline int lowbit(int x){return x&(-x);}
	inline void add(int x,int v){for(;x<=n;x+=lowbit(x))tr[x]+=v;}
	inline int ask(int x){int s=0;for(;x;x-=lowbit(x))s+=tr[x];return s;}
	inline int query(int l,int r){if(l>r)return 0;return ask(r)-ask(l-1);}
}T;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],T.add(i,a[i]);
	st.insert(0);st.insert(n+1);
	for(int i=1;i<=n;i++){
		cin>>b[i];
		if(b[i]!=1)
			st.insert(i);
	}
	int q;
	cin>>q;
	while(q--){
		int op,l,r;
		cin>>op>>l>>r;
		if(op==1){
			T.add(l,r-a[l]);
			a[l]=r;
		}else if(op==2){
			if(b[l]==1){
				if(r!=1)
					st.insert(l);
			}else{
				if(r==1)
					st.erase(l);
			}
			//维护set 
			b[l]=r;	
		}else{
			auto pos=st.lower_bound(l);
			tot=0;
			while(*pos<=r){
				v[++tot]=*pos;
				pos++;
			}
			if(tot==0){
				cout<<T.query(l,r)<<'\n';
				continue;
			}
			//没有bi>=2的就特判掉 
			int s=T.query(l,v[1]-1);
			for(int i=1;i<=tot;i++){
				s=max(s*b[v[i]],s+a[v[i]]);
				//贪心的取更优的 
				if(i==tot)s+=T.query(v[i]+1,r);
				else 
					s+=T.query(v[i]+1,v[i+1]-1);
			}
			cout<<s<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：3)

题解区转了一圈也没有单 $\log$ 做法，遂决定补一篇。~~我才不会告诉你这是为了卡最优解的。~~

# ABC368G Add and Multiply Queries

## 题意

给出序列 $a,b$，有 $q$ 次操作，每次操作可以单点修改、区间 $[l,r]$ 查询以下内容：

> 令变量 $x$ 值为 $0$，对于 $i=l,l+1,\dots,r$，要么令 $x\gets x+a_i$，要么令 $x\gets x\cdot b_i$。求 $x$ 的最大值。**保证答案不超过 $\bm{V=10^{18}}$。**

Data range：$n,q\le10^5$。

---

观察到乘法会让 $x$ 指数爆炸地增长。具体地，显然第一个位置会用加法，使得 $x\ge1$，那么只要再进行 $60$ 次乘 $2$ 就超过 $10^{18}$ 了。

所以我们可以断言 $b$ 数组对应区间内 $>1$ 的数只会有不超过 $59$（即 $\Theta(\log V)$）个。

而 $b_i=1$ 时显然选择加 $a_i$ 是更优的。

那么你在 $b_i>1$ 的位置取一个 $\max$，在两个相邻的大于 $1$ 的位置之间就是加上 $a$ 的区间和。

这样，用树状数组维护 $a$，用 `set` 维护 $b$ 的 $>1$ 的位置，每次询问直接先 `lower_bound` 再一直 `++` 直到那个位置 $>r$，即可做到 $\Theta(q\log n\log V)$。

---

然后讲下怎么优化到一个 $\log$。

首先（至少对于这个做法）那个 $\log V$ 是肯定优化不掉的，那么此时需要优化的地方就在于树状数组求区间和。

考虑你询问一个区间的时候，大多数的区间求和都是「相邻两个 $b_i>1$ 的位置的 $a_i$ 的和」，除了两端。那么就可以直接把这些和记下来直接调用，每次询问只需要做两次区间求和了。

还有一个小问题就是我不知道 `set` 的 `++` 的复杂度是多少（$\Theta(\log n)$？$\Theta(1)$？均摊 $\Theta(1)$？）。于是为了保证复杂度正确，可以开一个 `list`，然后用 `map` 指向每个位置在 `list` 上的迭代器，这样查询时在 `map` 上只需 `lower_bound`，后面 `++` 直接在 `list` 上面做。

于是时间复杂度为 $\Theta(q(\log n+\log V))$。

[submission](https://atcoder.jp/contests/abc368/submissions/57112866)。（这份代码在笔者写这篇题解时还是最优解。）

---

## 作者：zhujiangyuan (赞：3)

[[ABC368G] Add and Multiply Queries](https://www.luogu.com.cn/problem/AT_abc368_g)

>**It is guaranteed that the answers to the given type $3$ queries are at most $10^{18}$.**

意思就是对于每个操作 $3$ 的答案不超过 $10^{18}$。

这句话很有用。想象一下，如果对于 $i\in[l,r]$ 都选择乘上 $b_i$，那么对于有用的乘法（即 $b_i\ge 2$）不超过 $60$ 次。

那么执行乘上 $b_i$ 的次数不超过 $60$ 次，其余全是加上 $a_i$。

我们可以用一个 `set` 存储 $b$ 数组中大于 $2$ 的数字出现的位置。对于 $[l,r]$ 这段区间，找到这一段区间中 $b_i\le 2$ 的位置。对于这些位置之间，$b_i$ 肯定等于 $1$，那么一定选择加上 $a_i$；对于这些位置，比较加上 $a_i$ 和乘上 $b_i$ 哪个更优即可。

区间中 $b_i\le 2$ 的个数一定不超过 $60$，因此枚举不超过 $60$ 次，对于每两个 $b_i\le 2$ 的位置之间，要加上 $a_i$ 的和，因此 $a$ 数组要支持单点修改与区间求和，使用树状数组求和即可，单次操作时间复杂度 $\mathcal O(\log n)$。

总时间复杂度 $\mathcal O(q\log n\log V)$，其中 $V$ 为 $10^{18}$。

---

## 作者：zhangjiting (赞：3)

## 前言

最简单的一次，终于 AK 了 ABC，纪念一下。

## 思路

看到题目中有一句加粗的话

**入力で与えられるタイプ $ 3 $ のクエリの答えは $ 10^{18} $ 以下であることが保証されています。**

翻译出来是对于所有操作 $3$，答案不超过 $10^{18}$。

首先，$a_i$ 一定不会是 $0$，考虑一种情况，先加 $a_l$，然后一直乘 $b_i$，如果答案不超过 $10^{18}$，那么有意义，也就是不等于 $1$ 的 $b_i$ 在 $l$ 到 $r$ 中应该是很少的，只有 $60$ 个左右。

用平衡树维护 $b_i>1$ 的位置，用线段树维护 $a$，实现区间求和和单点修改。

查询的时候，$b_i>1$ 的位置判断 $v \times b_i$ 和 $v+a_i$ 哪个更大，就选哪个。剩下的就是一段一段的区间，把这些区间所有的 $a_i$ 都加起来就可以了。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cout<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e5+5;
int n,m;
int a[N],b[N];
int tree[N<<2];
#define ls p<<1
#define rs p<<1|1
void push_up(int p){
	tree[p]=tree[ls]+tree[rs];
}
void build(int p,int l,int r){
	if(l==r){
		tree[p]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(p);
}
void change(int p,int l,int r,int x,int v){
	if(l==r){
		tree[p]=v;
		return;
	}int mid=(l+r)>>1;
	if(x<=mid) change(ls,l,mid,x,v);
	else change(rs,mid+1,r,x,v);
	push_up(p);
}
int ask(int p,int l,int r,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr){
		return tree[p];
	}int mid=(l+r)>>1,res=0;
	if(ql<=mid) res+=ask(ls,l,mid,ql,qr);
	if(qr>mid) res+=ask(rs,mid+1,r,ql,qr);
	return res;
}
int ch[N][2],val[N],key[N],siz[N],top,x,y,z,root;
void update(int x){siz[x]=1+siz[ch[x][0]]+siz[ch[x][1]];}
int new_node(int v){siz[++top]=1;val[top]=v;key[top]=rand();return top;}
int merge(int x,int y){
    if(!x||!y) return x+y;
    if(key[x]<key[y]){
        ch[x][1]=merge(ch[x][1],y);
        update(x);
        return x;
    }
    else{
        ch[y][0]=merge(x,ch[y][0]);
        update(y);
        return y;
    }
}
void split(int now,int k,int &x,int &y){
    if(!now) x=y=0;
    else{
        if(val[now]<=k)x=now,split(ch[now][1],k,ch[now][1],y);
        else y=now,split(ch[now][0],k,x,ch[now][0]);
        update(now);
    }
}
int kth(int now,int k){
    while(true){
        if(k<=siz[ch[now][0]])now=ch[now][0];
        else if(k==siz[ch[now][0]]+1)return now;
        else k-=siz[ch[now][0]]+1,now=ch[now][1];
    }
}
void insert(int a){
	split(root,a,x,y);
    root=merge(merge(x,new_node(a)),y);
}
void del(int a){
	split(root,a,x,z);
    split(x,a-1,x,y);
    y=merge(ch[y][0],ch[y][1]);
    root=merge(merge(x,y),z);
}
int nxt(int a){
	split(root,a,x,y);
    int ans=val[kth(y,1)];
    root=merge(x,y);
    return ans;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);
	for(int i=1;i<=n;i++){
		cin>>b[i];
		if(b[i]>1) insert(i);
	}
	cin>>m;
	for(int i=1,op,l,r;i<=m;i++){
		cin>>op>>l>>r;
		if(op==1) change(1,1,n,l,r),a[l]=r;
		if(op==2){
			if(b[l]==1&&r>1) insert(l);
			else if(b[l]>1&&r==1) del(l);
			b[l]=r;
		}
		if(op==3){
			int ans=a[l],p=l+1;
			while(nxt(l)<=r&&nxt(l)!=0) {
				l=nxt(l);
				ans+=ask(1,1,n,p,l-1);
				if(ans*b[l]>ans+a[l]) ans*=b[l];
				else ans+=a[l];
				p=l+1;
			}
			if(l<=r) ans+=ask(1,1,n,l+1,r);
			cout<<ans<<endl;
		}
	}
	return 0;
}

```

---

## 作者：Field_Mouse (赞：2)

### 前言

线段树写挂导致赛后过题，遗憾离场/fn/fn/fn。

### 题意

给定两个序列 $A,B$ ，你需要支持以下三个操作：

```1 i x``` 将 $A_i$ 替换为 $x$.

```2 i x``` 将 $B_i$ 替换为 $x$.

```3 l r``` 给定初始值为 $0$ 的变量 $ans$，从 $l$ 到 $r$ 
顺序遍历 $A,B$，对于任意的 $i\in [l,r] $，可以选择将 $ans$ 替换为 $ans+A_i$ 或 $ans\times B_i$，你需要输出最后 $ans$ 的最大值。

**保证每次询问答案不超过 $10^{18}$**。

### 分析

问题关键在于保证"每次询问答案不超过 $10^{18}$"。

若满足这个条件，则询问区间中，最多只有 $\log V$ 个 $B_i$，满足 $B_i\ge 2$。其中 $V$ 是答案的值域。
如果有多于 $\log V$ 个 $B_i\ge2$，只需要将 $A_l$ 乘上所有 $\ge 2$ 的$B_i,i\in [l+1,r]$，就存在 $ans\ge 10^{18}$，不合题意。

所以我们可以暴力维护答案。具体的，使用线段树或树状数组维护带修区间和，使用 ```std::set``` 记录所有满足 $B_i \ge 2$ 的 $i$ ，查询时从 ```set``` 中找到所有在 $[l,r]$  区间内的满足 $B_i\ge 2$ 的 $i$，暴力判断此时 $+ A_i$ 还是 $\times B_i$。由于此时满足条件的 $i$ 最多只有 $\log V$ 个，所以时间复杂度是 $O(n\log n \log V)$ 的，可以通过此题。

### 代码


```cpp
#include<bits/stdc++.h>
#define AC return 0;
#define pr(n) printf("%lld",(n))
#define hh puts("")
#define ls(p) p<<1
#define rs(p) p<<1|1
#define kg putchar(' ')
#define int long long 
using namespace std;
namespace fr{
	int read()
	{
		int x=0,flag=1;
		char ch=getchar();
		for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')flag=-1;
		for(;ch<='9'&&ch>='0';ch=getchar())x=(x<<3)+(x<<1)+ch-'0';
		return flag*x;
	}
}
using namespace fr;
const int N = 1e5+5;
int sum[N<<2];
int a[N];
void pushup(int p)
{
	sum[p]=sum[ls(p)]+sum[rs(p)];
}
void build(int l,int r,int p)
{
	if(l==r)return (void)(sum[p]=a[l]);
	int mid=(l+r)>>1;
	build(l,mid,ls(p));build(mid+1,r,rs(p));
	pushup(p);
}
void upd(int l,int r,int p,int idx,int val)
{
//	cout<<l<<" "<<r<<" "<<val<<endl;
	if(l>r)return ;
	if(l==r)return (void)(a[idx]=sum[p]=val);
	int mid=(l+r)>>1;
	if(idx<=mid)upd(l,mid,ls(p),idx,val);
	if(idx>mid)upd(mid+1,r,rs(p),idx,val);
	pushup(p);
}
int get_sum(int l,int r,int L,int R,int p)
{
	if(l>r)return 0;
	if(L<=l&&r<=R)return sum[p];
	int ans=0,mid=(l+r)>>1;
	if(mid>=L)ans+=get_sum(l,mid,L,R,ls(p));
	if(mid<R)ans+=get_sum(mid+1,r,L,R,rs(p));
	return ans;
}
set<int> s;
int b[N];
signed main()
{
	int n=read();
	s.insert(0);s.insert(n+1);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){b[i]=read();if(b[i]>1)s.insert(i);}
	int q=read();
	build(1,n,1);
	while(q--)
	{
		int opt=read();
		if(opt==1)
		{
			int x=read(),val=read();
			//a[x]=val;
			upd(1,n,1,x,val);
		//	cout<<get_sum(1,n,1,1,1)<<"!\n";
		}
		if(opt==2)
		{
			int x=read(),val=read();
			b[x]=val;
			s.erase(x);
			if(val>1)s.insert(x);
		}
		if(opt==3)
		{
			int l=read(),r=read();
			auto L=s.lower_bound(l),R=s.upper_bound(r);--R;if(*L==l)++L;
			int ans=get_sum(1,n,l,*L-1,1);
			ans=max(ans+a[*L],ans*b[*L]);
			int lst=*L+1;
		//	cout<<*L<<" "<<*R<<endl;
			if(*L>*R){cout<<get_sum(1,n,l,r,1);hh;continue;}
			while(*L<*R)
			{
				auto to=L;++to;
				ans+=get_sum(1,n,lst,*to-1,1);
				ans=max(ans+a[*to],ans*b[*to]);
				lst=*to+1;
				L=to;
			}
			auto to=L;++to;
			ans+=get_sum(1,n,lst,r,1);
			cout<<ans<<endl;
			
		}
	}
	AC
}
```

---

## 作者：__O_v_O__ (赞：2)

初看这题似乎没有思路，但是题目中有一个重要的突破口：操作三的答案小于等于 $10^{18}$！

而我们发现，$2^{60}>10^{18}$。也就是说，操作三的区间中最多有 $60$ 个 $b_i$ 不为 $0$，其他 $b_i$ 全为 $1$，否则答案一定超过 $10^{18}$。

考虑利用这个性质：如果 $b_i$ 为 $1$，则选择加上 $a_i$ 必然更优。于是我们可以找出 $b_i$ 为 $1$ 的极长连续段，把答案加上段中 $a_i$ 的和（树状数组维护），再对于 $b_i$ 不为 $1$ 的位置更新答案。

我们可以维护一个 `set`，存不为 $1$ 的 $b_i$ 的下标。每次使用 `lower_bound` 函数找出下一个不为 $1$ 的 $b_i$，更新答案即可。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lb(x) x&(-x)
int c[100001],n,q,a[100001];
int b[100001];set<int>st;
void md(int x,int v){
	while(x<100001){
		c[x]+=v,x+=lb(x);
	}
}
int qr(int x){
	int an=0;
	while(x)an+=c[x],x-=lb(x);
	return an;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],md(i,a[i]);
	for(int i=1;i<=n;i++){
		cin>>b[i];
		if(b[i]>1)st.insert(i);
	}
	st.insert(n);
	cin>>q;
	while(q--){
		int i,tp,l,r,x;
		cin>>tp;
		if(tp==1){
			cin>>i>>x;
			md(i,x-a[i]);
			a[i]=x;
		}else if(tp==2){
			cin>>i>>x;
			if(b[i]>1)st.erase(i);
			b[i]=x;
			if(b[i]>1)st.insert(i);
		}else{
			cin>>l>>r;
			x=a[l++];
			while(l<=r){
				i=*st.lower_bound(l);
				x+=qr(min(i-1,r))-qr(l-1);
				if(i>r)break;
				x=max(x+a[i],x*b[i]);
				l=i+1;
			}
			cout<<x<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：what_can_I_do (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc368_g)

注意到题面有一句寻常的话：保证答案不超过 $10^{18}$。

这句话给了我们启发：因为 $2^{60}>10^{18}$，所以 $B_l$ 到 $B_r$ 中最多只有 $60$ 个不为 $1$ 的数。

那么可以写一个线段树维护 $B$ 的区间最大值，只要类似势能线段树判断，如果区间最大值为 $1$ 就直接返回，否则一直往下递归直到线段树叶子结点，并把这个叶子结点对应的下标存进 vector 中，将这个 vector 记为 $c$。

如果你的线段树写法是正常的话，那么此时的 $c$ 一定升序，那么直接枚举 $c$ 的所有元素，对于 $c$ 的相邻元素 $c_{i-1}$ 和 $c_i$ 构成左开右开区间，在这个区间中所有的 $B_j$ 都为 $1$，那么一定考虑将 $v$ 加上这个区间中 $A_j$ 的和，使用线段树实现，然后对于现在枚举到的这个 $c_i$，使用贪心，如果 $v\times B_{v_i}>v+A_{v_i}$，则让 $v$ 变为 $v\times B_{v_i}$，否则 $v$ 变为 $v+A_{v_i}$。

具体的一些细节看代码。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define lc k<<1
#define rc k<<1|1
using namespace std;
int n;
ll a[100010],b[100010];
int q;
ll tr[400010][2];
vector<int> v;
inline void change(int l,int r,int pos,int k,int f,ll c)
{
	if(l==r)
	{
		tr[k][f]=c;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) change(l,mid,pos,lc,f,c);
	else change(mid+1,r,pos,rc,f,c);
	if(!f) tr[k][f]=tr[lc][f]+tr[rc][f];
	else tr[k][f]=max(tr[lc][f],tr[rc][f]);
}
inline ll query0(int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr) return tr[k][0];
	int mid=(l+r)>>1;ll sum=0;
	if(ql<=mid) sum=query0(l,mid,ql,qr,lc);
	if(mid<qr) sum+=query0(mid+1,r,ql,qr,rc);
	return sum;
}
inline void query1(int l,int r,int ql,int qr,int k)
{
	if(tr[k][1]<=1) return;
	if(l==r)
	{
		v.push_back(l);
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid) query1(l,mid,ql,qr,lc);
	if(mid<qr) query1(mid+1,r,ql,qr,rc);
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],change(1,n,i,1,0,a[i]);
	for(int i=1;i<=n;i++) cin>>b[i],change(1,n,i,1,1,b[i]);
	cin>>q;
	while(q--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int pos;ll x;
			cin>>pos>>x;
			change(1,n,pos,1,0,x);
			a[pos]=x;
		}
		if(op==2)
		{
			int pos;ll x;
			cin>>pos>>x;
			change(1,n,pos,1,1,x);
			b[pos]=x;
		}
		if(op==3)
		{
			int l,r;ll ans=0;
			cin>>l>>r;
			query1(1,n,l,r,1);
			int la=l-1;
			for(int i=0;i<v.size();i++)
			{
				int pos=v[i];
				if(la+1<pos)
				{
					ans+=query0(1,n,la+1,pos-1,1);
				}
				if(!ans) ans+=a[pos];
				else
				{
					if(ans+a[pos]>ans*b[pos]) ans+=a[pos];
					else ans*=b[pos];
				}
				la=pos;
			}
			if(la+1<=r) ans+=query0(1,n,la+1,r,1);
			cout<<ans<<endl;
			v.clear();
		}
	}
	return 0;
}
```

---

## 作者：RandomLife (赞：2)

## ABC368G Add and Multiply

### 题外话

其实赛时是有思路的，但是被 E 题硬控了，于是没有场切。

### 正文

第一眼就感觉很难处理，肯定要用巧劲。（可能有硬做的方法吧，只是我太弱了）但是看见“答案不超过 $10^{18}$” 这句话时，我瞬间就有头绪了。

我们知道，指数的威力是很恐怖的。当询问区间 $[l,r]$ 时，答案至少为 $\prod_{i=l+1}^rb_i$。（这里 $l+1$ 是因为 $v$ 初始为 $0$ 要先选一次增加操作）然后这就进而说明了区间 $[l,r]$ 内 $b_i\geq2$ 成立时 $i$ 的个数最多只有 $\Theta(\log V)$ 个，其中 $V=10^{18}$。

除了 $b_i\geq2$ 之外就是 $b_i=1$。显然，此时选择增加操作一定更优。

于是，我们开一棵线段树，维护区间内第一个使得 $b_f\geq2$ 的 $f$（若不存在则 $f=0$） 和区间和 $s$。修改时正常修改就可以。

询问时我们就不断找到 $[l,r]$ 内的 $f$，然后 $[l,f)$ 这段显然选择增加操作更优，直接用区间求和，接着再比较是选 $+a_f$ 更优还是 $\times b_f$ 更优，然后再令 $l\to f+1$，直到 $f=0$。注意循环结束后要再将答案累加一个剩余的区间和。根据上面的证明，这样的操作不会超过 $\Theta(\log V)$。

最终时间复杂度 $\Theta(n\log n\log V)$。

### AC code

```cpp
#include<bits/stdc++.h>
#define lson p<<1
#define rson p<<1|1
using namespace std;
const int N=1e5+5;
struct SegmentTree{
	int l,r,f;
	long long sum;
	#define l(x)t[x].l
	#define r(x)t[x].r
	#define f(x)t[x].f
	#define sum(x)t[x].sum
}t[N<<2];
int n,a[N],b[N],q;
void pushUp(int p){
	if(f(lson))f(p)=f(lson);
	else f(p)=f(rson);
	sum(p)=sum(lson)+sum(rson);
}
void build(int p,int l,int r){
	l(p)=l,r(p)=r;
	if(l==r){
		sum(p)=a[l];
		if(b[l]>=2)f(p)=l;
		else f(p)=0;
		return;
	}
	int mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	pushUp(p);
}
void updateA(int p,int x,int d){
	if(l(p)==r(p)){
		sum(p)=d;
		return;
	}
	int mid=(l(p)+r(p))>>1;
	if(x<=mid)updateA(lson,x,d);
	else updateA(rson,x,d);
	pushUp(p);
}
void updateB(int p,int x,int d){
	if(l(p)==r(p)){
		if(d>=2)f(p)=x;
		else f(p)=0;
		return;
	}
	int mid=(l(p)+r(p))>>1;
	if(x<=mid)updateB(lson,x,d);
	else updateB(rson,x,d);
	pushUp(p);
}
long long getSum(int p,int l,int r){
	if(l>r)return 0;
	if(l<=l(p)&&r>=r(p))return sum(p);
	long long s=0;
	int mid=(l(p)+r(p))>>1;
	if(l<=mid)s+=getSum(lson,l,r);
	if(r>mid)s+=getSum(rson,l,r);
	return s; 
}
int getFirst(int p,int l,int r){
	if(l>r)return 0;
	if(l<=l(p)&&r>=r(p))return f(p);
	int mid=(l(p)+r(p))>>1;
	if(l>mid)return getFirst(rson,l,r);
	if(r<=mid)return getFirst(lson,l,r);
	int d=getFirst(lson,l,r);
	if(d)return d;
	return getFirst(rson,l,r);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)scanf("%d",&b[i]);
	build(1,1,n);
	scanf("%d",&q);
	while(q--){
		int op;
		scanf("%d",&op);
		if(op==1){
			int x,d;
			scanf("%d%d",&x,&d);
			updateA(1,x,d),a[x]=d;
		}else if(op==2){
			int x,d;
			scanf("%d%d",&x,&d);
			updateB(1,x,d),b[x]=d;
		}else{
			int l,r;
			long long ans=0;
			scanf("%d%d",&l,&r);
			while(1){
				int f=getFirst(1,l,r);
				if(!f)break;
				ans+=getSum(1,l,f-1);
				ans=max(ans+a[f],ans*b[f]);
				l=f+1;
			}
			ans+=getSum(1,l,r);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：_6_awa (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc368_g)

题目大意：

有两个数组 $a$ 和 $b$，支持三种操作：

$1.$ 将 $a_x$ 变成 $y$。

$2.$ 将 $b_x$ 变成 $y$。

$3.$ 有一个数 $T = 0$，依次遍历 $l$ 到 $r$，对于一个数 $i$，$T$ 可以变成 $T + a_i$ 或 $T \times b_i$。求 $T$ 的最大值。

思路分析：

暴力+贪心的思路是 $\mathcal{O(1)}$ 修改， $\mathcal{O(n)}$ 查询。在查询的时候，我们希望数越大越好，所以每次我们都取 $\max(T + a_i,T + b_i)$ 做为 $T$ 本轮的更新。因为 $a_i,b_i > 0$，所以可以证明贪心是对的。（不可能存在一乘就变成负数的情况）

似乎无论怎么样都不能优化了。但是题目中有一行粗体字，大家注意到没？

**入力で与えられるタイプ $ 3 $ のクエリの答えは $ 10^{18} $ 以下であることが保証されています。**

翻译成中文就是：保证答案在 $10^{18}$ 以下。首先第一步（即 $i = l$ 时）肯定要加上 $a_i$（不然乘起来还是为 $0$）。之后区间内如果有 $62$ 个 $b_i \ge 2$，那么每次选择 $b_i$ 结果都不会 $\le 10^{18}$。所以这句话变相的告诉我们：这个区间内肯定不超过 $62$ 个 $b_i \ge 2$ 的情况。所以当 $b_i = 1$ 的时候，肯定选择加，因为一个数乘上 $1$ 肯定比不过一个数加上正数；否则再做决断。此时复杂度变成了 $\mathcal{O(n)}$（加了 $62$ 倍的常数），是可以通过此题的。

现在只有两个问题：

$1.$ 如何快速的实现单点修改，区间查询操作？

$2.$ 如何在修改后仍能快速的查询 $b_i \ge l$ 的第一个位置？

答案是：第一个问题可以用树状数组解决，第二个问题可以用 $\text{vector}$ 或 $\text{set}$ 解决（因为笔者不太懂 $\text{set}$，所以后面均为 $\text{vector}$）。树状数组的时间是 $\mathcal{O(\log n)}$，所以对付长度为 $n$ 的查询也绰绰有余；对于第二个问题，删除和插入都可以二分找到 $\text{vector}$ 数组中该下标的位置，然后一个一个遍历。每遍历一个区间都先用树状数组求出加的答案，再用 $\max(T + a_i,T + b_i)$ 做决策。当 $b_i > r$ 时，将最后一段 $a_i$ 的和也加入 $T$ 中，此时 $T$ 就是最优答案。

注意：$\text{vector}$ 数组二分查找是要用迭代器进行的，不熟悉 $\text{vector}$ 的可以使用 $\text{set}$，效果差不多。

代码放这里。

```cpp
#include <iostream>
#include <vector>
#define lowbit(k) k&(-k)
#define int long long
using namespace std;
int n,a[200005],b[200005],tr[200005],q,opt,l,r;
vector<int>ve;
void add(int x,int k)//树状数组：单点修改，区间查询
{
  while(x <= n)tr[x] += k,x += lowbit(x);
}
int sum(int x)
{
  int su = 0;
  while(x > 0)su += tr[x],x -= lowbit(x);
  return su;
}
signed main()
{
  vector<int>::iterator pos;//迭代器
  cin >> n;
  for(int i = 1;i <= n;i ++)cin >> a[i],add(i,a[i]);
  for(int i = 1;i <= n;i ++)
  {
    cin >> b[i];
    if(b[i] > 1)ve.push_back(i);
  }
  ve.push_back(n + 1);//最后加下标n+1防止越界
  cin >> q;
  for(int i = 1;i <= q;i ++)
  {
    cin >> opt >> l >> r;
    if(opt == 1)
    {
      add(l,-a[l]);
      add(l,r);//修改
      a[l] = r;
    }
    else if(opt == 2)
    {
      if(b[l] > 1 && r <= 1)
	  {
	  	pos = lower_bound(ve.begin(),ve.end(),l);
	  	ve.erase(pos);//删除
	  }
      if(b[l] < 1 && r > 1)ve.insert(lower_bound(ve.begin(),ve.end(),r),r);//插入
      b[l] = r;
    }
    else
    {
      pos = lower_bound(ve.begin(),ve.end(),l);
      int A = distance(ve.begin(),pos),ans = 0;
      if(ve[A] > r)
      {
      	cout << sum(r) - sum(l - 1) << " \n";
      	continue ;//这里可以直接输出（代表这一段可以全部加）
	  }
	  ans += sum(ve[A] - 1) - sum(l - 1);//前面一段
	  for(;A < ve.size();A ++)
	  {
	  	if(ve[A] > r)
	  	{
	  		A --;
	  		ans += sum(r) - sum(ve[A]);//最后一段
	  		break ;
		}
		ans = max(ans + a[ve[A]],ans * b[ve[A]]);
		if(ve[A + 1] <= r)ans += sum(ve[A + 1] - 1) - sum(ve[A]);
	  }
	  cout << ans << '\n';//答案
    }
  }
}
```

---

## 作者：Dtw_ (赞：1)

# Solution
首先可以肯定的是操作一二都会，但是三不会。

因为题目要求的是最大的 $v$，所以我们会尽可能多乘非 $1$ 的数，而每次至少乘 $2$，并且答案还 $\leq 10^{18}$，所以在 $[l,r]$ 中只有 $\log K$ 个大于 $2$ 的数，其中 $K = 10^{18}$。但是有的时候乘比加小，所以我们还要取最大值。

综上：

我们只需要枚举这一段区间内大于等于 $2$ 的数，这些数大约只有 $60$ 多个，然后对于这些数，相邻两个之间的值一定是加法，所以用数据结构维护这个区间和，对于这些数在加法和乘法中取最大值。具体维护这些数用 `set` 存一下下标，找的时候直接二分找就行。

代码写的比较丑。
# Code

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n' 

#define int long long

#define fi first
#define se second

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n, a[N], b[N], q;

#define lb(o) (o) & (-o)

int d[N];

inline void update(int x, int v)
{
    for(; x<=n; x+=lb(x)) d[x] += v;
}

inline int query(int x)
{
    int res = 0;
    for(; x; x-=lb(x)) res += d[x];
    return res;
}

set<int> S;
set<int>::iterator it;

signed main()
{
    fst
    cin >> n;
    for(int i=1; i<=n; i++) cin >> a[i], update(i, a[i]);
    S.insert(0);
    for(int i=1; i<=n; i++)
    {
        cin >> b[i];
        if(b[i] != 1)
        {
            S.insert(i);
        }
    }
    S.insert(n+1);
    cin >> q;
    while(q--)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1) update(x, y - a[x]), a[x] = y; // 单点修改
        else if(op == 2)
        {
            if(b[x] != 1 && y == 1) S.erase(x); // 原先在，改完后不在了，就删了
            if(b[x] == 1 && y != 1) S.insert(x); // 原先不在，改完后在
            b[x] = y;
        }
        else if(op == 3)
        {
            int res = a[x]; // 第一个一定是加法，因为初始 v = 0
            x++; // x 用完了，往后移
            it = S.lower_bound(x); // 找 > 1 的数
            while(x <= y)
            {
                if(b[x] != 1)
                {
                    res = max(res + a[x], res * b[x]);
                    it++, x++; // 暴力改
                }
                else
                {
                    // 注意边界
                    res += query(min(*it - 1, y)) - query(x-1); // 区间和
                    x = *it; // 跳
                }
            }
            cout << res << endl;
        }
    }   
    return 0;
}
```

---

## 作者：zhlzt (赞：1)

### 题解

思路类似于 [CF992D Nastya and a Game](https://www.luogu.com.cn/problem/CF992D)。

题目保证操作 $3$ 的答案不超过 $10^{18}$，可知满足 $l\le i\le r\land B_i\ge 2$ 的正整数 $i$ 的数量小于 $60$。

对于满足 $B_i=1$ 的 $i$，显然我们选择 $v\gets v+A_i$ 而非 $v\gets v\times B_i$。于是我们可以在暴力枚举的基础上，把一个连续的 $B_i=1$ 的段当做一个整体处理。

树状数组维护 $A$ 的区间和，线段树维护对于每个 $i$，满足 $j>i\land B_j\ge 2$ 的最小的 $j$ 即可。由于要动态修改，我们还需维护对于每个 $i$，满足 $j<i\land B_j\ge 2$ 的最大的 $j$，用来辅助运算。

时间复杂度 $O(N\log N+QV\log N)$，$V$ 为操作 $3$ 要枚举到的连续的 $B_i=1$ 的段的数量的期望值，极限数据下 $V$ 可以取到将近 $60$。

### 代码实现

赛时代码写的比较匆忙，可能有些乱，敬请谅解。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int t;
typedef long long ll;
const int maxn=1e5+10;
ll tr[maxn],a[maxn],b[maxn];
int dpl[maxn],dpr[maxn];
struct node{
	int tag[maxn<<2];
	inline void addtag(t p,t k){
		tag[p]=k;
	}
	inline void pushdown(t p){
		if(!tag[p]) return;
		addtag(p<<1,tag[p]);
		addtag(p<<1|1,tag[p]);
		tag[p]=0;
	}
	inline void update(t l,t r,t p,t pl,t pr,t k){
		if(l>r) return;
		if(l<=pl and pr<=r) return addtag(p,k);
		int mid=(pl+pr)>>1; pushdown(p);
		if(l<=mid) update(l,r,p<<1,pl,mid,k);
		if(r>mid) update(l,r,p<<1|1,mid+1,pr,k);
	}
	inline int query(t d,t p,t pl,t pr){
		if(pl==pr) return tag[p];
		int mid=(pl+pr)>>1; pushdown(p);
		if(d<=mid) return query(d,p<<1,pl,mid);
		else return query(d,p<<1|1,mid+1,pr);
	}
}tree[2];
inline void upd(int p,ll k,int n){
	while(p<=n) tr[p]+=k,p+=(p&-p);
}
inline ll qry(int p){
	ll ans=0;
	while(p>=1) ans+=tr[p],p-=(p&-p);
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	dpr[n+1]=n+1;
	for(int i=n;i>=1;i--){
		if(b[i+1]!=1) dpr[i]=i+1;
		else dpr[i]=dpr[i+1];
		tree[1].update(i,i,1,1,n,dpr[i]);
	}
	dpl[0]=0;
	for(int i=1;i<=n;i++){
		if(b[i-1]!=1) dpl[i]=i-1;
		else dpl[i]=dpl[i-1];
		tree[0].update(i,i,1,1,n,dpl[i]);
		upd(i,a[i],n);
	}
	int q;cin>>q;
	for(int c=1;c<=q;c++){
		int opt,l,r;cin>>opt>>l>>r;
		if(opt==1){
			upd(l,r-a[l],n); a[l]=r;
		} 
		else if(opt==2){
			int temp1=tree[0].query(l,1,1,n);
			int temp2=tree[1].query(l,1,1,n);
			if(b[l]>1 and r==1){
				tree[1].update(max(1,temp1),l,1,1,n,temp2);
				tree[0].update(r,min(n,temp2),1,1,n,temp1);
			}
			else if(b[l]==1 and r>1){
				tree[1].update(max(1,temp1),l-1,1,1,n,l);
				tree[0].update(r+1,min(n,temp2),1,1,n,l);
			}
			b[l]=r;
		} else {
			ll v=0;
			for(int i=l;i<=r;i++){
				if(b[i]==1){
					int j=min(r,tree[1].query(i,1,1,n)-1);
					v+=qry(j)-qry(i-1); i=j;
				} else {
					v=max(v+a[i],v*b[i]);
				}
			}
			cout<<v<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：zrl123456 (赞：1)

[[ABC368G] Add and Multiply Queries ](https://www.luogu.com.cn/problem/AT_abc368_g)  

题目考察：set（STL），树状数组。  
题目简述：  
给你两个序列 $\{a_n\},\{b_n\}$，有 $q$ 次操作，每个操作可能是以下三种之一：  
1. 将 $a_{pos}$ 改为 $x$。
2. 将 $b_{pos}$ 改为 $x$。
3. 设 $f_i(x)$ 为 $\max(x+a_i,x\times b_i)$，给你区间 $[l,r]$，求 $ans=f_r(f_{r-1}(\dots(f_{l+1}(f_l(0)))))$。

数据范围：  
- $1\le n,q\le 10^5$
- $\forall i\in[1,n],1\le a_i,b_i\le 10^9$
- 在 $1,2$ 操作中，$1\le pos\le n$
- 在 $1,2$ 操作中，$1\le x\le 10^9$
- 在 $3$ 操作中，$1\le l\le r\le n$
- 在 $3$ 操作中，$1\le ans\le 10^{18}$
---
乍一看这道题既不满足前缀和的性质，也不满足 ST 表的性质，非常不可做。  

实际上我们发现在 $x\in[l,r]$ 的点中 $b_x>1$ 的最多只有 $60$ 个（因为 $ans\le 10^{18}$）。  
那么我们将加的数扔进树状数组里，将大于一的乘的数的下标扔进 set 里，查询的时候暴力去找第一个非 $1$ 的乘的数，用树状数组去求前面的和就可以了。  

时间复杂度为 $\Theta(n\log V\log n)$（$V$ 是 $ans$ 的值域）。  

[代码](https://atcoder.jp/contests/abc368/submissions/57097806)

---

## 作者：phkjy (赞：1)

### 题目大意

给两个序列 $A,B$，可以单点修改序列，每次询问 $l,r$，对于区间内每个 $i$，可以把 $ans$ 加上 $A_i$ 或减去 $B_i$，问操作完以后 $ans$ 的最大值



### 做法

考虑题目里说答案不超过 $1e18$，并且 $B_i$ 有价值当且仅当 $B_i\gt 1$，所以我们可以用链表维护有价值的 $B$，用线段树维护 $A$，贪心策略显然。

由于最多跳 $\log n$ 次 $B$，线段树查询是 $O(\log n)$ 的，所以总复杂度 $O(n \log^2 n)$。

```C++
#include<bits/stdc++.h>
using namespace std;
#define fre(x) freopen(""#x".in","r",stdin),freopen(""#x".out","w",stdout)
#define re register
#define inl inline
#define ll long long
ll ffff;
inl void read(ll &ret){
	ret=0;ffff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
		ffff=-ffff;
		ch=getchar();
	}while(ch>='0'&&ch<='9'){
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}ret*=ffff;
}
const ll N=2e5+5;
ll n,a[N],b[N],ls[N],nx[N];
ll tr[N<<2];
#define lc (x<<1)
#define rc (x<<1|1)
#define mid (l+r>>1)
void build(ll x,ll l,ll r){
	if(l==r){
		tr[x]=a[l];
		return ;
	}
	build(lc,l,mid);
	build(rc,mid+1,r);
	tr[x]=tr[lc]+tr[rc];
}
void modify(ll x,ll l,ll r,ll k,ll v){
	if(l==r){
		tr[x]=v;
		return ;
	}
	if(k<=mid) modify(lc,l,mid,k,v);
	else modify(rc,mid+1,r,k,v);
	tr[x]=tr[lc]+tr[rc];
}
ll query(ll x,ll l,ll r,ll L,ll R){
	if(l>R||r<L||L>R)return 0;
	if(l>=L&&r<=R)return tr[x];
	return query(lc,l,mid,L,R)+query(rc,mid+1,r,L,R);
}
int main(){
	//fre();
	read(n);
	for(ll i=1;i<=n;i++)
	read(a[i]);
	for(ll i=1;i<=n;i++)
	read(b[i]);
	ls[1]=0,nx[n]=n+1;
	ll t=0;
	for(ll i=1;i<=n;i++){
		ls[i]=t;
		if(b[i]!=1)t=i;
	}
	t=n+1;
	for(ll i=n;i>=1;i--){
		nx[i]=t;
		if(b[i]!=1)t=i;
	}
	// for(ll i=1;i<=n;i++)
	// printf("%d %d\n",ls[i],nx[i]);
	build(1,1,n);
	ll q;
	read(q);
	while(q--){
		ll opt,x,y;
		read(opt),read(x),read(y);
		if(opt==1){
			modify(1,1,n,x,y);
			a[x]=y;
		}
		else if(opt==2){
			if(b[x]==y)continue;
			b[x]=y;
			if(y==1){
				ll l=ls[x],r=nx[x];
				ls[r]=l;
				nx[l]=r;
			}
			else{
				ll l=ls[x],r=nx[x];
				ls[r]=x;
				ls[x]=l;
				nx[x]=r;
				nx[l]=x;
			}
		}
		else{
			ll ans=a[x];
			x++;
			if(x>y){
				printf("%lld\n",ans);
				continue;
			}
			ll j=x;
			while(j<=y){
				if(b[j]!=1){
					if(ans*b[j]<ans+a[j]){
						ans+=a[j];
						ans=ans+query(1,1,n,j+1,min(y,nx[j]-1));
						j=nx[j];
						//printf("%d ",j);
						continue;
					}
					ans*=b[j];
					ans=ans+query(1,1,n,j+1,min(y,nx[j]-1));
					j=nx[j];
				}
				else{
					ans+=a[j];
					ans+=query(1,1,n,j+1,min(y,nx[j]-1));
					j=nx[j];
				}
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：1)

首先这题如果暴力 dp 是很简单的，我们设 $f_{i}$ 为以 $i$ 为终点的答案，每次询问我们初始化 $f_{l}=a_{l}$。

转移显然 $f_{i}=\max(f_{i-1}+a_{i},f_{i-1} \times b_{i})$。

这样我们就得到了一个 $O(nq)$ 的艺术暴力。

正解实际上也很简单，题目给了一个显眼的的提示：保证答案不超过 $10^{18}$。

这说明当 $b_{i} > 1$ 时，转移到 $f_{i-1} \times b_{i}$ 的次数不会超过 $\log V$ 次，其中 $V$ 是答案的值域范围也就是 $10^{18}$。

所以我们可以记录下来 $b$ 数组中值大于 $1$ 的位置，实时维护，显然可以 set。

然后每次我们就可以暴力的枚举 set 里的数然后进行转移。因为当 $b_{i} = 1$ 的时候一定会选择加上 $a_{i}$，所以我们可以对于 set 中的数加上区间内的 $a_{i}$。这个可以使用树状数组或者线段树维护。


所以这题就完了，时间复杂度 $O(n \log n \log V)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int n,a[N],b[N],q,l,r,op,c[N];
void add(int x,int y){
	for(;x<=n;x+=x&(-x))c[x]+=y;
}
int getans(int x){
	int ans=0;
	for(;x;x-=x&(-x))ans+=c[x];
	return ans;
}
int query(int l,int r){
	if(l>r)return 0;
	return getans(r)-getans(l-1);
}
set <int> s;
void work(){
	cin >> op >> l >> r;
	if(op==1)add(l,r-query(l,l));
	else if(op==2){
		s.erase(s.find(l));
		if(r>1)s.insert(l);
		b[l]=r;
	}
	else{
		int ans=0,st=l-1;
		for(auto it=s.lower_bound(l);it!=s.end()&&*it<=r;st=*it,it++){
			ans+=query(st+1,*it-1);
			if(ans+query(*it,*it)>ans*b[*it])ans+=query(*it,*it);
			else ans*=b[*it];
		}
		ans+=query(st+1,r);
		cout << ans << "\n";
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)cin >> a[i],add(i,a[i]);
	for(int i = 1;i <= n;i++){
		cin >> b[i];
		if(b[i]>1)s.insert(i);
	}
	cin >> q;
	for(int i = 1;i <= q;i++)work();
	return 0;
}
//tlh
```

---

## 作者：Heldivis (赞：1)

## [ABC368G] Add and Multiply Queries

这道题有一个特殊的性质：**保证答案不超过 $10^{18}$**，这个性质不只是说明不用取模，同时蕴含做法。

考虑对于一个区间，如果 $B$ 序列中大于 $1$ 的个数很多，那么一定会有区间积 $M$ 很大，但是由于保证答案很小，**所以区间的 $B$ 序列中最多有 $\log_210^{18}\approx 60$ 个**。只有这些位置需要决策，其他地方一定是选择加 $A_i$ 更优。

所以使用 `std::set<int> st` 维护这些位置，每次进行决策，其他位置使用一个树状数组维护 $A$ 序列和即可。

第一种操作在树状数组上操作即可；第二种操作在序列中修改 $B_i$ 的值，并在 `st` 中删添元素即可。

时间复杂度 $O(Q\log N\log V)$。

询问部分代码：

```cpp
while (l <= r) {
  auto t = st.lower_bound(l);
  if (t == st.end() || *t > r) {
    res += bit.Query(l, r);
    l = r + 1;
  } else {
    res += bit.Query(l, (*t) - 1);
    res = max(res * b[*t], res + a[*t]);
    l = *t + 1;
  }
}
printf("%lld", res);
```

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc368_g)

## $\mathtt{Solution}$

这个题不难（~~一般题面较短的题都不会太难~~）。

对于 $b_i\ge2$ 的 $i$，可以发现如果选择乘法更优，显然这样的操作不会超过 $64$ 次，不然答案就超过 $10^{18}$ 了；如果选择加法更优显然答案会增加至少一倍，也是 $\log$
 级别的。

对于 $b_i=1$ 的 $i$，显然选择加法更优（因为 $a_i>0$）。

思路就非常清晰了，用 set 维护 $b_i\ne1$ 的位置，然后每一段选择加的位置用线段树维护。

对于每一次询问，暴力地跳下一个 $b_i\ne1$ 的位置，然后统计答案即可。

时间复杂度 $O(m\log^2n)$。

就是要注意一下 set 可能访问到 `end`，很容易 RE。

赛时代码：

```cpp
#include<bits/stdc++.h>
#define left rt * 2
#define right rt * 2 + 1
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')f = -1;ch = getchar();}
	while(isdigit(ch)){s = s * 10 + ch - '0';ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 1e5 + 5, MR = 1e6 + 5;
int n, m, a[MAXN], b[MAXN];
struct Segment_tree{
	int lf[MR], rf[MR], num[MR];
	void push_up(int rt){num[rt] = num[left] + num[right];}
	void build(int rt, int l, int r){
		lf[rt] = l, rf[rt] = r;
		if(l == r){
			num[rt] = a[l];
			return ;
		}
		int mid = l + r >> 1;
		build(left, l, mid);
		build(right, mid + 1, r);
		push_up(rt);
	}
	void change_node(int rt, int x, int y){
		if(lf[rt] > x || x > rf[rt])return ;
		if(lf[rt] == x && rf[rt] == x){
			num[rt] = y;
			return ;
		}
		change_node(left, x, y);
		change_node(right, x, y);
		push_up(rt);
	}
	int query(int rt, int l, int r){
		if(lf[rt] > r || rf[rt] < l)return 0;
		if(lf[rt] >= l && rf[rt] <= r)return num[rt];
		return query(left, l, r) + query(right, l, r);
	}
}tr;
set <int> st;
signed main(){
	n = read();
	for(int i = 1;i <= n;i ++)a[i] = read();
	for(int i = 1;i <= n;i ++){
		b[i] = read();
		if(b[i] != 1)st.insert(i);
	}
	tr.build(1, 1, n);
	m = read();
	for(int i = 1;i <= m;i ++){
		int opt = read(), l = read(), r = read();
		int res = 0;
		if(opt == 1)a[l] = r, tr.change_node(1, l, r);
		if(opt == 2){
			if(r == 1){
				if(st.find(l) != st.end())st.erase(l);
			}
			else st.insert(l);
			b[l] = r;
		}
		if(opt == 3){
			auto it = st.lower_bound(l);
			if(it == st.end()){
				printf("%lld\n", tr.query(1, l, r));
				continue;
			}
			int pos = *it, last = l;
			int res = 0;
			while(pos <= r){
				res += tr.query(1, last, pos - 1);
				if(res * (b[pos] - 1) < a[pos])res += a[pos];
				else res *= b[pos];
				last = pos + 1;
				it = st.lower_bound(pos + 1);
				if(it == st.end())break;
				pos = *it;
			}
			printf("%lld\n", res + tr.query(1, last, r));
		}
	}
	return 0;
}
```

---

## 作者：Milthm (赞：1)

拿到题：哎？三个操作，是数据结构题！稳啦！

仔细看之后：这第三个操作是什么东西，完啦！

看了底下一句话之后：稳啦！

~~其实没有那一句话也能做的，就是有点难。~~

______

首先，这个答案不大于 $10^{18}$ 的条件并不是方便你用 `long long` 存的，而是这题的解题关键点。

你发现，如果 $b_i$ 全都大于 $1$，那么乘最多 $\log V$ 次就会到达上限，这启示我们把等于 $1$ 的区间合并处理。

所以考虑每次从左端点开始倍增往后跳，跳到 $b_i$ 全 $1$ 的最长段，加上这段的区间和（因为 $b_i$ 是 $1$ 所以肯定加更优），然后后面这个位置肯定 $b_i$ 不是 $1$，这个时候对两种方案取最大值即可。

$a$ 的区间和以及 $b$ 区间是否全 $1$ 都可以用树状数组来维护，所以总时间复杂度为 $O(q \log n \log V)$。

~~可能有点复杂，但也不是很难写。~~

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int n,a[N],b[N],q;
struct BIT{
	int c[N];
	BIT(){
		memset(c,0,sizeof(c));
	}
	void add(int x,int k){
		while(x<=n){
			c[x]+=k;x+=x&-x;
		}
	}
	int ask(int x){
		int ans=0;
		while(x){
			ans+=c[x];x-=x&-x;
		}
		return ans;
	}
	int query(int l,int r){
		return ask(r)-ask(l-1);
	}
}A,B;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); 
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];A.add(i,a[i]);
	}
	for(int i=1;i<=n;++i){
		cin>>b[i];B.add(i,(b[i]==1));
	}
	cin>>q;
	while(q--){
		int op,l,r;cin>>op>>l>>r;
		if(op==1){
			A.add(l,-a[l]);a[l]=r;A.add(l,a[l]);
		}
		else if(op==2){
			B.add(l,-(b[l]==1));b[l]=r;B.add(l,(b[l]==1));
		}
		else{
			int now=l,ans=0;
			while(now<=r){
				for(int i=20;i>=0;--i){
					int k=now+(1<<i)-1;
					if(k<=r&&B.query(now,k)==k-now+1)ans+=A.query(now,k),now=k+1;
				}
				if(now>r)break;
				ans=max(ans+a[now],ans*b[now]);
				++now;
			}
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：1)

注意到题目描述中 $\text{ans}\le 10^{18}$，这说明对于所有询问的 $[l,r]$，当前的 $b$ 满足 $[l,r]$ 区间内乘积不大于 $10^{18}$。更进一步地，这说明 $[l,r]$ 内 $b$ 数组只有至多 $60$ 个大于 $1$ 的数。

考虑使用 `std::set` 维护当前 $b$ 数组中所有大于 $1$ 的数的下标和值。查询时，两个相邻大于 $1$ 的 $b_i$ 之间的区间只能取 $a$，可以使用树状数组查询区间和，决策大于 $1$ 的 $b_i$ 时根据当前得到的 $v$ 贪心即可。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define mp make_pair
#define pob pop_back
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=100007,ee=1e18;
ll n,q,a[maxn],b[maxn],ans;
set<pair<ll,ll> > st;
struct Tree{
	ll val[maxn];
	void upd(ll x,ll k){for(;x<=n;x+=x&(-x)) val[x]+=k;}
	ll sum(ll x){ll E=0; for(;x;x-=x&(-x)) E+=val[x]; return E;}
	ll qry(ll l,ll r){if(l>r) return 0; return sum(r)-sum(l-1);}
}tree;
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],tree.upd(i,a[i]);
	for(int i=1;i<=n;i++){
		cin>>b[i];
		if(b[i]!=1) st.insert(mp(i,b[i]));
	}
	st.insert(mp(n+1,0));
	cin>>q;
	for(int i=1,opt,x,y;i<=q;i++){
		cin>>opt>>x>>y;
		if(opt==1) tree.upd(x,y-a[x]),a[x]=y;
		else if(opt==2){
			if(b[x]!=1) st.erase(st.lower_bound(mp(x,0)));
			if(y!=1) st.insert(mp(x,y)); b[x]=y;
		}else{
			ans=0;
			vector<pair<ll,ll> > tmp; ll las=x;
			for(auto it=st.lower_bound(mp(x,0));it->first<=y;it++) tmp.pb(*it);
			for(auto t:tmp){
				ans+=tree.qry(las,t.first-1);
				if(ans*t.second>ans+a[t.first]) ans*=t.second;
				else ans+=a[t.first]; las=t.first+1;
			}
			ans+=tree.qry(las,y);
			cout<<ans<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

很有趣的简单题。

看三个操作，不太好实现。但是下面有一句话提醒了我们：答案保证 $\le 10^{18}$。再考虑乘法操作，假设每个乘数都是 $2$，$2^{60}>10^{18}$，因此有效的乘法不超过 $60$ 次。

考虑如何优化暴力。我们只需要把所有 $b_i>1$ 的 $i$ 放进一个 `set` 里然后查询后继，并维护区间的 $a_i$ 和，使用树状数组实现。

```cpp
// Title:  Add and Multiply Queries
// Source: ABC368G
// Author: Jerrywang
#include <cstdio>
#include <set>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=100010;
using namespace std;

int T, n, a[N], b[N]; ll c[N]; set<int> S;
void modify(int x, int y)
{
    for(; x<=n; x+=x&-x) c[x]+=y;
}
ll query(int x)
{
    ll res=0; for(; x; x-=x&-x) res+=c[x]; return res;
}

int main()
{
#ifdef Jerrywang
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d", a+i), modify(i, a[i]);
    rep(i, 1, n)
    {
        scanf("%d", b+i);
        if(b[i]>1) S.insert(i);
    }
    scanf("%d", &T);
    while(T--)
    {
        int o, l, r; scanf("%d%d%d", &o, &l, &r);
        if(o==1)
        {
            modify(l, r-a[l]);
            a[l]=r;
        }
        else if(o==2)
        {
            if(b[l]>1) S.erase(l);
            b[l]=r;
            if(b[l]>1) S.insert(l);
        }
        else
        {
            int i=l; ll x=a[i];
            while(i<=r)
            {
                auto it=S.lower_bound(i+1); int j;
                if(it==S.end() || *it>r) j=r+1; else j=*it;
                x+=query(j-1)-query(i);
                if(j<=r) x=max(x+a[j], x*b[j]), i=j;
                else break;
            }
            printf("%lld\n", x);
        }
    }
    
    return 0;
}
```

---

## 作者：Lotus_Land (赞：0)

### 题意

给定两个长度为 $N$ 由正整数组成的序列 $A$ 和 $B$，有以下 $Q$ 个操作：

- 给定两个正整数 $i,x$，把 $A_i$ 修改为 $x$；

- 给定两个正整数 $i,x$，把 $B_i$ 修改为 $x$；

- 给定两个正整数 $l,r$，求出以下问题的答案：

  - 把 $v$ 设为 $0$。按 $i=l,l+1,\dots,r$ 的顺序，把 $v$ 替换为 $\max(v+A_i,v\times B_i)$。求最终的 $v$ 值。 保证答案不超过 $10^{18}$。

### 分析

因为 $v$ 不超过 $10^{18}<2^{60}$，所以对于每次查询，乘的次数一定不超过 $60$ 次。并且如果乘的数为 $1$，显然选择加比选择乘更优。所以把大于 $1$ 的 $B_i$ 的下标都放进一个 set 里，对于每次查询，把 $[l,r]$ 区间内的那些大于 $1$ 的 $B_i$ 都挑出来用乘法，其他的部分都用加法。还需要一个支持单点修改、区间查询的树状数组来维护 $A_i$ 的区间和。时间复杂度 $O(N\log^2 N)$。

我有一个疑惑，就是为什么用 `*st.lower_bound(l)` 会比用 `*lower_bound(st.begin(),st.end(),l)` 要快很多？

[后者的提交记录](https://atcoder.jp/contests/abc368/submissions/57111547)

[前者的提交记录](https://atcoder.jp/contests/abc368/submissions/57111491)

```cpp
#include<bits/stdc++.h>
#define lc(p) ((p)*2)
#define rc(p) ((p)*2+1)
#define mkpr make_pair
#define LL long long
#define N 100005
using namespace std;
inline LL read() {
    char ch=getchar();
    LL x=0;
    bool t=0;
    while(ch<'0'||ch>'9')   t|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
    return t?-x:x;
}
int n,q;
LL A[N],B[N];
int lowbit(int x){
	return x&-x;
}
LL tr[N];
void Add(int x,int v){
	while(x<=n){
		tr[x]+=v;
		x+=lowbit(x);
	}
}
LL Query(int x){
	LL res=0;
	while(x>0){
		res+=tr[x];
		x-=lowbit(x);
	}
	return res;
}
set<int>st;
int main(){
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>A[i];
		Add(i,A[i]);
	}
	for(int i=1;i<=n;i++){
		cin>>B[i];
		if(B[i]>1){
			st.insert(i);
		}
	}
	st.insert(n+1);
	cin>>q;
	int op,i,x,l,r;
	while(q--){
		cin>>op;
		if(op==1){
			cin>>i>>x;
			Add(i,x-A[i]);
			A[i]=x;
		}else if(op==2){
			cin>>i>>x;
			if(B[i]>1)st.erase(i);
			B[i]=x;
			if(x>1)st.insert(i);
		}else{
			cin>>l>>r;
			int pos;
			LL v=A[l];
			l++;
			while(l<=r){
				pos=*st.lower_bound(l);
				//cout<<pos<<' ';
				v+=Query(min(pos-1,r))-Query(l-1);
				if(pos>r)break;
				v=max(v+A[pos],v*B[pos]);
				l=pos+1;
			}
			cout<<v<<endl;
		}
	}
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

E > F + G。

但是最后 2min 想到做法没打完，耻辱下播。

注意到 $2^{60} > 10^{18}$，故有一个重要性质：

**在 $[l,r]$ 区间内，$B_i \ge 2$ 的元素数目不会超过 $60$ 个。**

换句话说，$B$ 数组应该有大量的 $1$。对于这些段，选择 $A$ 数组相加去做一定是更优的。

那么可以用 `bitset` 压位记录 $B$ 数组元素是否为 $1$，然后将 $l$ 开始暴力跳过 $1$ 的极长段即可。使用线段树维护 $A$ 数组并统计答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int n, q, opt, l, r;
long long a[N], b[N];
bitset<N> bs;
// 省略线段树板子

void _main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i], bs[i] = (b[i] != 1);
	bs[n + 1] = 1;   // 防止找不到
	SegmentTree<long long> sgt(a, n);
	cin >> q;
	while (q--) {
		cin >> opt >> l >> r;
		if (opt == 1) {
			sgt.update_cover(l, l, r);
		} else if (opt == 2) {
			b[l] = r, bs[l] = (r != 1);
		} else if (opt == 3) {
			long long v = 0;
			while (l <= r) {
				if (bs[l]) {
					v = max(v + sgt.query_sum(l, l), v * b[l]), l++;
					continue;
				}
				int nxt = bs._Find_next(l);
				if (nxt - 1 <= r) v += sgt.query_sum(l, nxt - 1);
				else v += sgt.query_sum(l, r);
				l = nxt;
			}
			cout << v << '\n';
		}
	}
}
```

---

## 作者：liruixiong0101 (赞：0)

# G - Add and Multiply Queries
## 题意：
你有两个长度为 $n$ 的序列 $a,b$，你要处理如下 $q$ 次操作（$1\le n\le 10^5,1\le q\le 10^5$）：
1. 将 $a_x\gets y$。
2. 将 $b_x\gets y$。
3. 有一个变量 $T$ 初始值为 $0$，依次遍历 $i=l,l+1,\cdots,r$ 每次将 $v\gets v+a_i$ 或 $v\gets v\times b_i$。输出 $T$ 最后可能的最大值。

**保证第 3 种操作的答案最大为** $10^{18}$。

## 思路：
最后的条件非常重要，如果 $b_i\le 1$ 那么肯定选择将 $v\gets v+a_i$，否则将 $v\gets \max(v+a_i,v\times b_i)$。后者情况的 $b_i\ge 2$，由于 $2^{64}>10^{18}$，我们可以知道最多只有 $64$ 个 $b_i$ 大于 $1$，所以我们可以用 `set` 或 `vector` 维护这些 $b_i$ 的下标 $i$，然后在每次查询的时候遍历 `set` 或 `vector` 中在 $l$ 到 $r$ 以内的数，对于 $b_i\le 1$ 我们需要区间查询 $a$ 数组中某一段区间的和，对于 $b_i\gt 1$ 我们可以暴力处理。由于需要单点修改某个数的值，第 1 种操作可以用树状数组维护，第 2 种操作可以用用 `set` 或 `vector` 暴力处理。

## 代码：
<https://atcoder.jp/contests/abc368/submissions/57109557>

---

## 作者：xxseven (赞：0)

好玩的特殊性质题。

### 题意简述：

维护两个长为 $n$ 的正整数序列 $a,b$，支持以下操作：

- 单点修改 $a$。
- 单点修改 $b$。
- 对于一段给定的区间 $[l,r]$，给定一个变量 $v$，初始值为 $0$，对于 $i \in [l,r]$ 按 $l$ 到 $r$ 的顺序依次选择令 $v \gets v+a_i$ 或 $v \gets v\times b_i$，输出最大的可能的 $v$，**不取模且结果不超过 $10^{18}$**。

### 解题思路：

我们发现这个询问非常诡异，不仅方式诡异而且不取模对于乘法操作也不太常见。

先来考虑我们每一步的决策：如果当前位置的 $b_i=1$，那么由于 $a_i$ 是正整数，我们必然选择加法。  
如果 $b_i \ge 2$，那么加法操作和乘法操作都可以被选择。我们将这种情况称为一个决策点。

情况好像有点复杂，但我们注意到每次 $b_i \ge 2$ 的时候，$v$ 都会至少变成原来的两倍，又因为答案不超过 $10^{18}$，这样的决策点不会超过 $\log_2 10 \times 18$ 个，因此我们可以暴力取出所有的决策点进行决策。寻找决策点的过程可以使用 set。

我们又知道，两个决策点之间的所有位置都会选择加法操作，那么我们只需要一个支持单点修区间求和的数据结构即可。我选择的是树状数组。

时间复杂度 $O(n \log n)$，可以通过此题。下面是代码：


```cpp
#include<bits/stdc++.h>
#define int long long 
#define lowbit(x) (x&-x)
using namespace std;
const int N=1e5+6;
int a[N],b[N],n,q;
int t[N];
void add(int x,int v){
	while(x<=n) t[x]+=v,x+=lowbit(x); 
}
int sum(int x){
	int res=0;
	while(x) res+=t[x],x-=lowbit(x);
	return res;
}
set<int> s;
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n; s.insert(0); s.insert(n+1);
	for(int i=1;i<=n;++i) {
		cin>>a[i]; add(i,a[i]); 
	}
	for(int i=1;i<=n;++i) {
		cin>>b[i]; 
		if(b[i]!=1) s.insert(i); 
	}
	cin>>q;
	for(int op,x,y,i=1;i<=q;++i){
		cin>>op>>x>>y; 
		if(op==1){
			add(x,y-a[x]); a[x]=y; 
		}
		if(op==2){
			if(b[x]!=1) s.erase(s.lower_bound(x));
			b[x]=y;
			if(b[x]!=1) s.insert(x);
		}
		if(op==3){
			int ans=0;
			set<int>::iterator it=s.lower_bound(x);
			int pos=*it,lst=x-1;
			while(pos<=y){
				ans+=sum(pos-1)-sum(lst);//两个决策点中间的部分全都做加法
				ans=max(ans+a[pos],ans*b[pos]);
				lst=pos; it++; pos=*it; //利用迭代器自增取出所有决策点
			}
			ans+=sum(y)-sum(lst);
			cout<<ans<<'\n';
		}	
	}
	return 0;
}
```

希望这篇题解能够帮到你！

---

## 作者：Genius_Star (赞：0)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18378963)

[本题加强版。](https://www.luogu.com.cn/problem/P10399)

### 题意：

给定两个长度为 $n$ 的序列 $a,b$，进行 $m$ 次操作，需要支持 $a,b$ 的单点修，进行多次区间查询：

- 按顺序从 $l$ 走到 $r$，初始 $v=0$，设当前走到第 $i$ 个位置，可以令 $v$ 变为 $v + a_i$ 或 $v \times b_i$，问最后能取的最大值（答案 $\le 10^{18}$）。

$n,m \le 2 \times 10^5$。

### 思路：

注意到 $ans \le 10^{18}$，则如果中间都选乘的话，满足 $b_i > 1(i \in [l,r])$ 的 $i$ 最多只有 $\log ans$ 个。

那么在查询区间 $[l,r]$ 的贡献时，先令 $v = a_l$，然后再 $[l+1,r]$ 中二分出第一个 $b_j > 1$ 的 $j$，对于 $[l+1,j-1]$ 范围内的肯定都是选加，然后取 $v \gets \max(v+a_j,v \times b_j)$ 即可；后面依次。

考虑使用 `set` 维护所有 $b_i > 1$ 的 $i$，使用树状数组维护前缀和即可。

时间复杂度为 $O(N \log N \log W)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const ll N=1e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,q,op,p,x,y,v;
ll a[N],b[N],t[N];
set<ll> S;
void add(ll x,ll v){
    for(int i=x;i<=n;i+=lowbit(i))
      t[i]+=v;
}
ll query(ll x){
    ll ans=0;
    for(int i=x;i;i-=lowbit(i))
      ans+=t[i];
    return ans;
}
int main(){
    n=read();
    For(i,1,n){
        a[i]=read();
        add(i,a[i]);
    }
    For(i,1,n){
        b[i]=read();
        if(b[i]>1)
          S.insert(i);
    }
    q=read();
    while(q--){
        op=read(),x=read(),y=read();
        if(op==1){
            add(x,-a[x]);
            a[x]=y;
            add(x,a[x]);
        }
        else if(op==2){
            if(y>1&&b[x]<2)
              S.insert(x);
            if(y<2)
              S.erase(x);
            b[x]=y;
        }
        else if(op==3){
            v=a[x];
            p=x+1;
            while(p<=y){
                auto it=S.lower_bound(p);
                if(it==S.end()||(*it)>y){
                    v+=query(y)-query(p-1);
                    p=y+1;
                }
                else{
                    ll h=(*it);
                    v+=query(h-1)-query(p-1);
                    p=h+1;
                    v=max(v+a[h],v*b[h]);
                }
            }
            write(v);
            putchar('\n');
        }
    }
    return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# Part 0 - 前言闲话

啊啊啊，第一次 ABC 自己做出 G 题，不过是从赛时调到赛后。

# Part 1 - 题意疏通

有长度为 $N$ 的序列 $A$ 和 $B$。需要执行 $Q$ 次操作或询问：

- `1 i x`：将 $A_i$ 替换为 $x$。
- `2 i x`：将 $B_i$ 替换为 $x$。
- `3 l r`：首先有一个变量 $v=0$，遍历 $l$ 到 $r$，每次可以选择把 $v$ 替换为 $v+A_i$ 或 $v \times B_i$。求最后 $v$ 的最大值。

**保证第三种询问的答案最多为 $\mathbf{10^{18}}$**。

# Part 2 - 算法思路

## 2-1 算法概述

这道题并不怎么考察算法，而是重在考察思维，只涉及了数据结构的维护。

## 2-2 从题目里找出突破口

首先考虑从数据范围里寻找线索。$1 \le N,Q \le 10^5$ 说明正解至少会带一个 $\log$。

然后从题目描述中可以发现加粗的最后一句话的限制很重要。

我们发现，在遍历计算 $v$ 的时候，如果发现有 $B_i>1$，大部分时候都会选择乘法，除非当前的 $v$ 很小，$A_i$ 很大，导致 $v+A_i>v \times B_i$ 时才会选择加法。

所以可以得知在询问区间中 $B_i>1$ 的数量是 $\log 10^{18}$ 级别的，数量很少，可以在修改的过程中直接处理出来。

## 2-3 在修改中处理出 $B_i>1$

在这里，我选择了使用 set 存放，因为它具有了插入，删除，查找，排序和 lower_bound 的功能。

首先在读入 $B$ 的时候，若遇到 $B_i>1$ 时直接插入到 set 里。

在第二种修改时：

- 若 $x=1$ 且 set 里含有 $i$，就将 $i$ 从 set 里删掉。
- 若 $x>1$，就将 $i$ 插入 set。

## 2-4 第三种询问的做法

下面，记 $\sum\limits_{i=L}^{R}A_i$ 为 $sum(L,R)$。
特别地，若 $L>R$，$sum(L,R)=0$。

首先，用 set 的 lower_bound 找到第一个大于等于 $l$ 的元素的指针。需要特判，若不存在大于等于 $l$ 元素或者这个元素大于 $r$，那么说明区间内一个 $B_i>1$ 都没有，只能使用加法，答案即为 $sum(l,r)$。

设 $l$ 到 $r$ 内最小的 $B_i>1$ 的位置是 $x$，最大的是 $y$。

那么，$l$ 到 $x-1$ 的 $B_i$ 都等于 $1$，将 $v$ 加上 $sum(l,x-1)$。

对于所有 $B_i>1$ 的位置，判断 $v+A_i$ 与 $v \times B_i$ 的大小，进行更新。对于每两个相邻的位置之间，设较小者为 $i_1$，较大者为 $i_2$，那么 $v$ 直接加上 $sum(i_1+1,i_2-1)$。

根前面同理，将 $v$ 加上 $sum(y+1,r)$。

## 2-5 数据结构维护区间和

对于上文中的 $sum(L,R)$，因为涉及到修改，所以应使用数据结构维护。

这里我使用了线段树进行维护，这个就不用赘述了。

# Part 3 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll t[114514 << 2];
ll up[114514 << 2];

void build(ll rt, ll l, ll r) {
    if (l == r) {
        t[rt] = 1;
        return;
    }
    ll mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    t[rt] = t[rt << 1] + t[rt << 1 | 1];
}

void push_down(ll rt, ll l, ll r) {
    if (up[rt]) {
        ll mid = (l + r) >> 1;
        t[rt << 1] = up[rt] * (mid - l + 1);
        t[rt << 1 | 1] = up[rt] * (r - mid);
        up[rt << 1] = up[rt];
        up[rt << 1 | 1] = up[rt];
        up[rt] = 0;
    }
}

void update(ll rt, ll l, ll r, ll x, ll y, ll val) {
    if (x <= l && r <= y) {
        t[rt] = val * (r - l + 1);
        up[rt] = val;
        return;
    }
    if (up[rt])
        push_down(rt, l, r);
    ll mid = (l + r) >> 1;
    if (x <= mid)
        update(rt << 1, l, mid, x, y, val);
    if (y > mid)
        update(rt << 1 | 1, mid + 1, r, x, y, val);
    t[rt] = t[rt << 1] + t[rt << 1 | 1];
}

ll query(ll rt, ll l, ll r, ll x, ll y) {
    if (x <= l && r <= y)
        return t[rt];
    if (up[rt])
        push_down(rt, l, r);
    ll mid = (l + r) >> 1;
    ll sum = 0;
    if (x <= mid)
        sum += query(rt << 1, l, mid, x, y);
    if (y > mid)
        sum += query(rt << 1 | 1, mid + 1, r, x, y);
    return sum;
}

ll n, q, a[114514], b[114514];
set<ll> s;

int main() {
    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        update(1, 1, n, i, i, a[i]);
    }
    for (ll i = 1; i <= n; i++) {
        cin >> b[i];
        if (b[i] > 1) {
            s.insert(i);
        }
    }
    cin >> q;
    while (q--) {
        ll op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            a[x] = y;
            update(1, 1, n, x, x, y);
        } else if (op == 2) {
            b[x] = y;
            if (y == 1) {
                if (s.find(x) != s.end()) {
                    s.erase(x);
                }
            } else {
                s.insert(x);
            }
        } else {
            ll ans = 0, fst = 1;
            auto it = s.lower_bound(x);
            if (it == s.end() || *it > y) {
                cout << query(1, 1, n, x, y) << "\n";
                continue;
            }
            if (x <= *it - 1) {
                ans += query(1, 1, n, x, *it - 1);
            }
            for (; it != s.end() && *it <= y; it++) {
                ll now = *it;
                if (!fst) {
                    ll lst = *prev(it);
                    if (lst + 1 <= now - 1) {
                        ans += query(1, 1, n, lst + 1, now - 1);
                    }
                }
                fst = 0;
                if (ans * b[now] > ans + a[now]) {
                    ans *= b[now];
                } else {
                    ans += a[now];
                }
            }
            it = prev(it);
            if (*it + 1 <= y) {
                ans += query(1, 1, n, *it + 1, y);
            }
            cout << ans << "\n";
        }
    }

    return 0;
}
```

完结撒花！

---

## 作者：huangrenheluogu (赞：0)

考虑如果 $B_i=1$，那么这个地方显然是使用 $v=v+A_i$ 的操作。

我们发现 $A_i\ge 1$，说明在进行一次操作之后 $v\ge 1$，此时对于 $B_i\ge 2$ 的操作只能再进行 $\left\lfloor\log_2ans\right\rfloor=59$ 次。

于是用 set 维护哪些地方可能进行 $B$ 操作，这些地方是不超过 $\mathcal{O}(\log V)$ 的，中间部分可以线段树直接求和。复杂度 $\mathcal{O}(q\log n\log V)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid (l + r >> 1)
#define ls (p << 1)
#define rs (p << 1 | 1)
using namespace std;
const int N = 1e5 + 5;
int n, q, a[N], b[N], sum[N << 2], op, x, y, v;
set<int> s;
inline void build(int p, int l, int r){
	if(l == r){
		sum[p] = a[l];
		return ;
	}
	build(ls, l, mid);
	build(rs, mid + 1, r);
	sum[p] = sum[ls] + sum[rs];
}
inline void modify(int p, int l, int r, int x){
	if(l == r){
		sum[p] = a[l];
		return ;
	}
	if(mid >= x) modify(ls, l, mid, x);
	else modify(rs, mid + 1, r, x);
	sum[p] = sum[ls] + sum[rs];
}
inline int query(int p, int l, int r, int x, int y){
	if(x > y) return 0;
	if(x <= l && r <= y) return sum[p];
	int res = 0;
	if(mid >= x) res += query(ls, l, mid, x, y);
	if(mid < y) res += query(rs, mid + 1, r, x, y);
	return res;
}
signed main(){
//	freopen("data.in", "r", stdin);
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	build(1, 1, n);
	for(int i = 1; i <= n; i++){
		if(b[i] > 1) s.insert(i);
	}
	scanf("%lld", &q);
	while(q--){
		scanf("%lld%lld%lld", &op, &x, &y);
		if(op == 1){
			a[x] = y;
			modify(1, 1, n, x);
			continue ;
		}
		if(op == 2){
			if(b[x] > 1) s.erase(x);
			b[x] = y;
			if(b[x] > 1) s.insert(x);
			continue ;
		}
		v = 0;
		auto it = s.lower_bound(x);
		while(it != s.end() && (*it) <= y){
			v += query(1, 1, n, x, (*it) - 1);
			x = *it;
			v = max(v + a[x], v * b[x]);
			x++;
			it = s.lower_bound(x);
		}
		v += query(1, 1, n, x, y);
		printf("%lld\n", v);
	}
	return 0;
}
```

---

## 作者：small_john (赞：0)

## 思路

简单题。

首先发现，答案最多只有 $V=10^{18}$，对于 $B_i= 1$，很明显直接做加操作就行了，否则，即可以做加操作，也可以做乘操作，但是这种操作最多只有 $\log V$ 次。

所以用集合维护 $B_i>1$ 的位置 $i$，每次询问的区间最多只有 $\log V$ 个这种数，这些位置暴力遍历，具体的，二分出第一个大于等于 $l$ 的数，已知往右扫知道当前位置大于 $r$。其他的部分可以看作很多个区间，对答案有区间和的贡献，用树状数组维护。

时间复杂度 $O(n\log n+Q\log n\log V)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+5;
int n,q,a[N],b[N],t[N];
set<int> s;
#define lowbit(x) (x&(-x))
inline void add(int x,int v)
{
	for(;x<=n;x+=lowbit(x))
		t[x]+=v;
}
inline int ask(int x)
{
	int res = 0;
	for(;x;x-=lowbit(x))
		res+=t[x];
	return res;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i = 1;i<=n;i++)
		cin>>a[i],add(i,a[i]);
	for(int i = 1;i<=n;i++)
	{
		cin>>b[i];
		if(b[i]>1) s.insert(i);
	}
	cin>>q;
	while(q--)
	{
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1) add(x,y-a[x]),a[x] = y;
		else if(op==2)
		{
			if(b[x]>1) s.erase(x);
			b[x] = y;
			if(b[x]>1) s.insert(x);
		}
		else
		{
			int now = 0,las = x-1;
			auto p = s.lower_bound(x);
			for(;p!=s.end();p++)
			{
				int val = *p;
				if(val>y) break;
				now+=ask(val-1)-ask(las);
				now = max(now+a[val],now*b[val]);
				las = val;
			}
			now+=ask(y)-ask(las);
			cout<<now<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

## 闲话

众所周知，$E>G$。

## 思路

显然在 $B_i=1$ 时不可能选择 $B_i$。那么，开一个 `set` 记录 $B_i\neq 1$ 的所有 $i$，然后再开一个树状数组维护区间 $A_i$ 和，在每个 $B_i\neq 1$ 的点暴力进行决策。

什么？你说这解法时间复杂度 $O(nm)$？不不不。你需要再仔细看一下题目。

> **所有询问的答案均不超过 $10^{18}$。**

也就是说，我们可以发现，在**最坏情况下**，每个询问的决策点也不会超过 $\lfloor\log_2 V\rfloor$ 个。在这道题中，$V\le 10^{18}$，也就是说只会有最多 $60$ 个决策点。

在每次决策时暴力二分下一个决策点时间复杂度为 $O(n+m\log^2 n\log V)$，通过第一次二分寻找而后面直接利用 `set::iterator::operator++` 时间复杂度 $O(1)$ 的性质降低为 $O(n+m\log n\log V))$。

## 代码

```c++
#include <iostream>
#include <set>
using namespace std;
const int N = 1e5 + 10;
int n, m, op, x, y, a[N], b[N];
using ll = long long;
ll tr[N], ret;
set<int> st;
set<int>::iterator it;
void update(int x, int v)
{
    while (x <= n)
        tr[x] += v, x += (x & -x);
}
ll query(int x)
{
    ll res = 0;
    while (x)
    {
        res += tr[x];
        x -= (x & -x);
    }
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        update(i, a[i]);
    }
    st.insert(0);
    st.insert(n + 1);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", b + i);
        if (b[i] != 1)
            st.insert(i);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 2)
        {
            if (b[x] != 1 and y == 1)
                st.erase(x);
            if (b[x] == 1 and y != 1)
                st.insert(x);
            b[x] = y;
            continue;
        }
        if (op == 1)
        {
            update(x, y - a[x]);
            a[x] = y;
            continue;
        }
        ret = a[x];
        x++;
        it = st.lower_bound(x);
        while (x <= y)
        {
            if (b[x] != 1)
            {
                ret = max(ret + a[x], ret * b[x]);
                it++, x++;
                continue;
            }
            ret += query(min(*it - 1, y)) - query(x - 1);
            x = *it;
        }
        printf("%lld\n", ret);
    }
}
```

---

