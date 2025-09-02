# Eels

## 题目描述

Vasya 是一个非常喜欢鱼的人，他的父母在新年时送给了他一个水族箱。Vasya 并没有鱼类学的学位，所以他认为把新水族箱装满鳗鱼是个好主意。不幸的是，鳗鱼是食肉动物，因此 Vasya 决定了解一下这个想法有多危险。

当多条鳗鱼被放进同一个水族箱时，它们会互相争斗，直到只剩下一条鱼。每当两条鳗鱼争斗时，体型较大的会吃掉体型较小的（如果它们体重相等，也会有一条吃掉另一条）。具体来说，假设水族箱里最初有 $n$ 条鳗鱼，第 $i$ 条的体重为 $x_i$。那么它们之间会发生 $n-1$ 场战斗，最终只剩下一条鳗鱼。每当两条体重分别为 $a$ 和 $b$ 的鳗鱼（$a \le b$）争斗时，体重为 $a$ 的鳗鱼会被吃掉并从水族箱中消失，而体重为 $b$ 的鳗鱼体重会增加到 $a+b$。

当两条体重为 $a$ 和 $b$ 的鳗鱼（$a \le b$）争斗时，如果 $b \le 2a$，则这场战斗被认为是危险的。对于给定的一组鳗鱼，危险值定义为：如果将这些鳗鱼放入同一个水族箱中，可能发生的危险战斗的最大数量。

现在 Vasya 正在计划要往水族箱里放哪些鳗鱼。他有一个鳗鱼集合（初始为空）。他会对这个集合进行一系列操作。每次操作，他要么向集合中加入一条鳗鱼，要么从集合中移除一条鳗鱼。每次操作后，Vasya 都会询问你当前集合的危险值。

## 说明/提示

在第三个样例中，所有操作完成后，鳗鱼集合为 $\{1, 1, 4\}$。对于这组鳗鱼，如果全部放入同一个水族箱，有多种可能的战斗顺序：

- 体重为 4 的鳗鱼先吃掉一条体重为 1 的鳗鱼，然后再吃掉另一条体重为 1 的鳗鱼。在这种情况下，没有任何一场战斗是危险的。
- 体重为 1 的鳗鱼先吃掉另一条体重为 1 的鳗鱼，这场战斗是危险的。现在水族箱中剩下体重为 4 和 2 的两条鳗鱼，体重较大的吃掉较小的，这场战斗也是危险的。在这种情况下，危险战斗的总数为 2。

因此，这组鳗鱼的危险值为 2。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
+ 1
- 1
```

### 输出

```
0
0
```

## 样例 #2

### 输入

```
4
+ 1
+ 3
+ 7
- 3
```

### 输出

```
0
0
1
0
```

## 样例 #3

### 输入

```
9
+ 2
+ 2
+ 12
- 2
- 2
+ 4
+ 1
+ 1
- 12
```

### 输出

```
0
1
1
0
0
0
0
3
2
```

# 题解

## 作者：是个汉子 (赞：12)

### Solution

先考虑不进行操作时，怎么吞噬可以得到最多的危险次数。

有一个结论是：挑最轻的两条鱼合并，可以使答案最大。

我们简单证明一下：设鱼这个集合为 $S$ ，那么一次操作就是从中取出两个最小的元素 $a$ 和 $b$ ，并把 $a+b$ 插入 $S$ 。设某次操作 $a$ 和 $b$ 操作是不危险的，那么满足 $2a\leq b$ 。则 $b$ 不曾被合并过，不然设 $b=c+d$ ，其中 $c\leq d$ ，则 $d\geq b/2>a$ ，那么 $d$ 应该是被合并的过的，和我们的结论冲突。

然后可以发现，对所有元素排序，若一个元素对答案产生贡献，是满足 $w_i\leq 2\cdot\sum_{j<i}w_j$ 的。

也就是只要能维护这个判断就行了——根据 $w_i$ 分等级： $[2^0,2^1),[2^1,2^2),[2^2,2^3),\cdots,[2^{29},2^{30})$ ，然后发现一个等级中如果有多个元素，只有最小的可能不是危险的（这个我不会证qwq），因此维护和即可。

如果有插入和删除操作直接改变区间和和元素就好了。

### 代码

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
ll q,ans,sum[40];
char ch[2];
multiset<ll> num[40];

int main(){
    scanf("%lld",&q);
    while(q--){
        ll x,i;
        scanf("%s%lld",ch,&x);
        for(i=1;(1<<i)<=x;i++);i--;
        if(ch[0]=='+'){
            sum[i]+=x;
            num[i].insert(x);
        }
        else{
            sum[i]-=x;
            num[i].erase(num[i].find(x));
        }
        ll siz=0,ans=0;
        for(int i=0;i<30;i++){
            if(!num[i].size()) continue;
            ans+=(num[i].size()-((*num[i].begin())>2*siz));
            siz+=sum[i];
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```



---

## 作者：lzqy_ (赞：5)

挺神仙的一道数据结构题，算是我目前独立切题的巅峰水平了（

## 前置说明：

- 为了方便讨论，以下的所有证明不考虑不等号取等的情况。显然不影响证明的正确性。

- 以下全文称危险合并为合法合并。

- 用 $\text{merge}(x,y)$ 表示合并 $x,y$，其中 $y \ge x$。


## 思路

首先考虑没有修改怎么做。



考虑对于目前序列中最小的两个数 $a,b$，分几种情况来讨论（为了方便，不考虑取等问题）：

- 存在序列中第三小的数 $c$，满足 $\text{merge}(b,c)$ 是合法的：

	若 $a+b<c$，易得 $\text{merge}(a+b,c)$ 是合法的；若 $a+b>c$，由于 $a<c,b<c$，所以 $c<a+b<2c$，$\text{merge}(c,a+b)$ 也是合法的。显然合并 $a,b$ 不会使合法合并次数变小。
    
- 不存在序列中第三小的数 $c$，满足 $\text{merge}(b,c)$ 是合法的：

	显然合并 $a,b$ 不会更劣，且有可能使 $\text{merge(a+b,c)}$ 成为合法的合并。
    
又因为三者合并完之后的和为定（$a+b+c$），归纳法可证明最优的合并方法即为每次选择最小的两个数合并。

如果不带修直接用优先队列跑一遍就行了。

-------

然后考虑如何维护插入&删除。

可以发现一些性质：

若 $\text{merge}(a,b)$ 的合并是合法的，那么 $[a,a+b]$ 之间的合并都是合法的。
	
   - **证明**：假设 $[a,a+b]$ 之间还存在最小的数 $c$，按照合并的方式可知，$c>a,c>b$。又因为 $c<a+b,\frac{a+b}{2}<b<c$，所以 $\text{merge}(c,a+b)$ 是合法的，由此可推出 $\text{merge}(c,x)(x\in [c,a+b])$ 是合法的。归纳可知整个区间的合并都是合法的。
   
由该性质可知，若只考虑初始序列中存在的数，那么可以将整个区间（升序排列）划分成若干个块，**每个块内的数可以通过合法合并变成一个数，每两个块合并时需要通过一次不合法的合并**。大致是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/xeco7tkm.png)
    
按照不合法合并的定义可知，每次跳块的时候，数的大小至少成为原来的两倍。也就是说，**最多只会有 $\log V$ 个块**。




**换句话说，合并过程只有不超过 $\log V$ 次不合法合并。**
    

---


所以考虑如何维护不合法的合并。
   
   
首先，$a_{x}$ 与 $a_{x+1}$ 属于不同的块，等价于 $\sum\limits_{i=1}^x a_i<\frac{a_{x+1}}{2}$（按照合并的过程推一下就好）。
   
然后你会发现，插入的时候很好维护，只需要把最多 $\log V$ 个块合并就好了，可是删除的时候无法迅速找到需要拆开的位置。

然后突发奇想，满足 $a_x<\frac{a_{x+1}}{2}$ 的位置最多也只有 $\log V$ 个，且满足 $\sum\limits_{i=1}^x a_i<\frac{a_{x+1}}{2}$ 的位置一定满足 $a_x<\frac{a_{x+1}}{2}$。

然后突然发现这个东西带修之后没有前效性也没有后效性，只和当前块有关。


然后这道题就做完了。

## 实现

开一个vector维护满足 $a_x<\frac{a_{x+1}}{2}$ 的位置，再开一棵平衡树维护整个序列。

对于插入和删除操作，判断一下前后两个位置的状态，进行对应的vector内的插入删除。

对于操作完之后的询问，暴力遍历 vector 内的所有元素，依次判断是否满足 $\sum\limits_{i=1}^x a_i<\frac{a_{x+1}}{2}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define il inline
#define ll long long
using namespace std;
const int N=500010;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
il int cread(){
	char c=getchar();
	for(;c!='+'&&c!='-';c=getchar());
	return c=='+';
}
ll w2[N],d2[N];
int son[N][2],d1[N],w1[N],fa[N];
int m,n=1,cnt,rt;

//////////////////////////
//Splay
il void update(int x){
	d1[x]=d1[son[x][0]]+d1[son[x][1]]+w1[x];
	d2[x]=d2[son[x][0]]+d2[son[x][1]]+w1[x]*w2[x];
}
il void Rotate(int x){
	int y=fa[x],z=fa[y],k=(son[y][1]==x);
	son[z][son[z][1]==y]=x,fa[x]=z;
	son[y][k]=son[x][k^1],fa[son[x][k^1]]=y;
	son[x][k^1]=y,fa[y]=x,update(y),update(x);
	fa[0]=son[0][0]=son[0][1]=0;
}
il void Splay(int x){
	int y,z;
	while(fa[x]){
		y=fa[x],z=fa[y];
		if(z) ((son[y][0]==x)^(son[z][0]==y))?Rotate(y):Rotate(x);
		Rotate(x);
	}
	rt=x;
	return ;
}
il void Insert(int x){
	if(!rt){
		rt=++cnt;
		w1[rt]=d1[rt]=1;
		w2[rt]=d2[rt]=x;
		return ;
	}
	int t=rt;
	while(w2[t]!=x&&son[t][x>w2[t]]) 
		t=son[t][x>w2[t]];
	if(w2[t]==x){
		d1[t]++,w1[t]++;
		d2[t]+=x;
		return Splay(t);
	}
	++cnt;
	w1[cnt]=d1[cnt]=1;
	w2[cnt]=d2[cnt]=x;
	son[t][x>w2[t]]=cnt,fa[cnt]=t;
	return Splay(cnt);
}
il void Erase(int x){
	int t=rt,tmp;
	while(w2[t]!=x) t=son[t][x>w2[t]];
	d1[t]--,w1[t]--;
	d2[t]-=x;
	Splay(t);
	if(!d1[t]){
		if(!son[t][0]&&!son[t][1]){rt=0;return ;}
		if(!son[t][0]){
			rt=son[t][1],fa[son[t][1]]=0;
			return ;
		}
		else if(!son[t][1]){
			rt=son[t][0],fa[son[t][0]]=0;
			return ;
		}
		else{
			rt=son[t][0],fa[rt]=0;
			tmp=son[t][1],t=rt;
			while(son[t][1]) t=son[t][1];
			son[t][1]=tmp,fa[tmp]=t;
			return Splay(tmp);
		}
	}
}
il int rk(int x){
	int t=rt,sum=0;
	while(w2[t]!=x&&son[t][x>w2[t]]){
		if(x>w2[t]) sum+=d1[son[t][0]]+w1[t];
		t=son[t][x>w2[t]];
	}
	if(x>w2[t]) sum+=w1[t]+d1[son[t][0]];
	else if(x==w2[t]) sum+=d1[son[t][0]];
	return Splay(t),sum+1;
}
il int nm(int rk){
	if(rk>n) return 0;
	int t=rt;
	while(1){
		if(rk<=d1[son[t][0]]) t=son[t][0];
		else{
			rk-=d1[son[t][0]];
			if(rk<=w1[t]) return Splay(t),w2[t];
			rk-=w1[t],t=son[t][1];
		}
	}
}
il ll pre(int rk){
	nm(rk);
	return d2[son[rt][0]]+(rk-d1[son[rt][0]])*w2[rt];
}
//Splay
//////////////////////////


vector<int>g;
int main(){
	m=read();
	int opt,x,val;
	Insert(0);
	while(m--){
		opt=cread(),x=read();
		if(opt==1){
			int loc=rk(x),x1=nm(loc-1),x2=nm(loc);
			Insert(x),n++;
			for(int i=0;i<g.size();i++)
				if(g[i]==x2){g.erase(g.begin()+i);break;}
			if(x1*2<x)
				g.insert(upper_bound(g.begin(),g.end(),x),x);
			if(x*2<x2)
				g.insert(upper_bound(g.begin(),g.end(),x2),x2);
		}
		else{
			int loc=rk(x),x1=nm(loc-1),x2=nm(loc+1);
			Erase(x),n--;
			for(int i=0;i<g.size();i++)
				if(g[i]==x){g.erase(g.begin()+i);break;}
			if(x1*2<x2&&x*2>=x2) g.insert(upper_bound(g.begin(),g.end(),x2),x2);
		}
		val=0;
		for(int i=0;i<g.size();i++)
			if(pre(rk(g[i])-1)*2<g[i]) val++;
		printf("%d\n",n-1-val);
	}
	return 0;
}
```


---

## 作者：do_while_true (赞：4)

暴力是，每次挑出最小的两个合并。

需要观察到没有产生贡献的次数很小。考虑最小的那个数的大小，如果一次合并没有产生贡献，那么最小的数至少 $\times 2$．所以最多会有 $\mathcal{O}(\log (qx))=\mathcal{O}(\log q+\log x)$ 次。

根据这个来观察还有什么性质，考虑如果一次合并没有产生贡献，那么那个时刻的最小值一定是所有数从小到大排序后的一段前缀合并出来的，并且发生合并的只有这个前缀。所以将所有鱼的重量 $a$ 从小到大排序后，一个位置的前缀和 $s_i\times 2 <a_{i+1}$ 时不会产生贡献。

最后是套路，每 $2^i$ 分个块（$[2^0,2^1),[2^1,2^2),[2^2,2^3),\cdots$）。这样的从小到大排序后，“ $s_i\times 2<a_{i+1}$ ” 也就是不合法的情况出现的位置一定是块与块之间。所以每个块开一个可删堆 / `multiset` 即可解决。时间复杂度是 $\mathcal{O}(q\log x)$ 的。

```cpp
// LUOGU_RID: 93542170
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<set>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int N=500010;
int n,cnt;
multiset<int>s[31];
ll sum[31];
signed main(){
	read(n);
	for(int i=1;i<=n;i++){
		char ch=getchar();while(ch!='-'&&ch!='+')ch=getchar();
		int x,k;read(x);
		k=31-__builtin_clz(x);
		if(ch=='+')sum[k]+=x,s[k].insert(x),++cnt;
		else sum[k]-=x,s[k].erase(s[k].lower_bound(x)),--cnt;
		ll all=0;
		int ans=-1;
		for(int o=0;o<=30;o++){
			if(s[o].empty())continue;
			if(all && all*2<(*s[o].begin()))--ans;
			all+=sum[o];
		}
		cout << max(0,cnt+ans) << '\n';
	}
	return 0;
}
```

---

## 作者：lyreqwq (赞：2)

和 @james1BadCreeper duel。

设鱼的重量为 $a_i$。每次选最小的两个 $a_i$ 合并是不劣的。

大概感受一下可以发现失败合并只有 $O(\log V)$ 次，原因是每次失败合并会让全局最小值倍增。

设 $x$ 为最小值，$y$ 为次小值，则一次失败合并要求 $2x < y$。这个条件等价于 $2s_{i - 1} < a_i$，其中 $s$ 是 $a$ 排序后的前缀和。

然后注意到 $s_{i - 1}$ 和 $a_i$ 的 highbit 必然不同。进一步有 $a_{i - 1}$ 和 $a_i$ 的 highbit 必然不同。按 highbit 分类维护即可。

代码跟上面的题解差不多。

---

## 作者：intel_core (赞：1)

有唐氏把唐题写成了史山。

考虑怎么求危险攻击的最大次数。首先我们把 $\{a_i\}$ 排序，求出前缀和数组 $s$。注意到如果 $2s_i<a_{i+1}$，那么任意一个只包含 $[1,i]$ 中元素的块和至少包含一个 $[i+1,n]$ 的块合并的时候一定不可能是危险攻击，而这种合并至少会发生一次。因此我们得到了一个答案的上界 $n-\sum [2s_i<a_{i+1}]$。

我们直接每次取两个最小的数进行合并，不难发现两个数合并之后不会超过大的那个数的两倍，因此只有在 $2s_i<a_{i+1}$ 时不会是危险攻击，其余情况一定都是危险攻击。

注意到 $2s_i<a_{i+1}$ 可以推出 $2a_i<a_{i+1}$，而这样的 $i$ 只有 $\log V$ 个，直接开个桶维护 $a_{i+1}-2s_i$ 的值即可。复杂度 $O(n\log V)$。

---

## 作者：RainPPR5 (赞：0)

UPD 20240726 题解被打回后：修改了缺少的逗号（

### 分析合并策略

设一次合并 $A$ 和 $B$，我们钦定 $A\ge B$。

若这次合并是危险的，那么有 $A\le2B$，

我们考虑证明结论，**从小到大合并可以最大化危险合并次数**。

考虑证明对于一个小的集合 $S=\{A,B,C\}$，其中 $C\ge A\ge B$，

---

如果合并了当前鱼的集合 $S$ 中最小的两个 $A,B$，

那么下一次合并，若 $A+B\ge C$ 那么一定满足 $A+B\le 2C$。

---

反过来，如果合并了较大的两个 $C,A$，

那么下一次合并，有 $A+C\ge B$，但是 $A+C\le 2B$ 一定不成立。

---

因此，我们证明了对于任意大小为 $3$ 的集合成立，

也就是说，对于任意原集合的大小为 $3$ 的子集都成立，

容易得出，对于原集合也成立。

### 统计答案

我们使用经典策略，将鱼分为以下若干块，

$$
[1,2),[2,4),\dots,[2^i,2^{i+1}),\dots
$$

我们发现，每个块内的合并一定都是危险的，

也就是不危险的合并一定存在于不同的块之间。

我们考虑证明结论，**不危险的合并一定发生于块首**。

根据前面的结论，我们从小到大合并，

因此对于每一个位置，一定是前面都合并完了，

那么一个位置 $i$ 的贡献为，

$$
\left[2\sum_{j<i}a_j<a_i\right]
$$

我们分类讨论，

+ 若 $a_i$ 是块首元素，那么直接判断这个式子即可；

+ 若 $a_i$ 不是块首元素，注意到 $2a_{i-1}>a_i$ 的，那么上式一定不成立。

于是，我们使用可删堆（`multiset`）维护这若干个块即可。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl "\n"

using ll = long long;

ll sum[30];
multiset<int> app[30];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int Q;
	cin >> Q;
	while (Q--) {
		string op;
		int x;
		cin >> op >> x;
		int k = __lg(x);
		if (op == "+") sum[k] += x, app[k].insert(x);
		else sum[k] -= x, app[k].erase(app[k].find(x));
		ll pre = 0, ans = 0;
		for (int i = 0; i < 30; ++i) {
			if (app[i].empty()) continue;
			ans += app[i].size();
			if (*app[i].begin() > 2 * pre) --ans;
			pre += sum[i];
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Nelofus (赞：0)

想一想这个 dangerous battle 意味着什么，意味着这会令当前值至少为 $a$ 的两倍。

每次令权值翻一倍的这个事情让我们联想到一些关于倍增的结构，自然考虑倍增值域分块。

考虑到这个之后就能注意到暴力是每次合并两个最小的。那只要思考每个位置能否产生贡献，一个位置不能产生贡献当且仅当比它小的全部加起来的和 $\times 2$ 比它小，否则总是能把它换到前面合并的步骤中产生贡献。

那么同一个块里面只有最小值可能不会产生贡献。暴力维护即可。时间复杂度 $\mathcal O(n\log V)$。

[Code](https://codeforces.com/contest/1098/submission/261208290)

---

## 作者：Mashu77 (赞：0)

首先我们证明一个结论：每次取最小的两个数合并，可以取得最大的危险合并次数。方便起见，称 
$x
,
y$
 是危险合并为 
$x
,
y$
 合法。

设最小两值为 
$a
,
b$。若不合并 
$a
,
b$，那么 
$a
,
b$
 中先与其他数合并的那个，不妨设为 
$b$。考虑 
$b
,
c$
 合并，其中 
$c
≥
b$：

若 
$b
,
c$
 合法。若 
$a
+
b
≤
c$，则显然 
$a
+
b
,
c$ 合法。若 
$a+b>c$，由 $a≤
c
,
b
≤
c$，有 
$a
+
b
≤
2
c$，则 
$a
+
b
,
c$
 也合法。那么贪心先合并 
$a
,
b$。
若 
$b
,
c$
 不合法。因为 
$2
b
<
c$，所以 
$a
+
b
<
c$。显然先合并 
$a
,
b$
 不会更劣。
于是不带修直接用小根堆即可。那么带修呢？

再证明一个结论：若最小二值 
$a
,
b$
 合法，则接下来的所有合并 
$x
,
y$，若 
$x
,
y
∈
[
b
,
a
+
b
]$，则 
$x
,
y$
 合法。

证明很简单，$y
≤
2
x
⟺
y
−
x
≤
x$，因为 
$y
−
x
≤
a$，故成立。有了这个结论，我们可以做很多事。

我们可以证明，将初始元素升序排序后，合法合并一定是一段段的。

且所有不合法合并一定是形如 $2\sum\limits_{i=1}^{x-1}a_i<a_{x}$。于是我们就将原来动态的合并转化为了静态问题。

按值域分块，$[
2
0
,
2
1
)
,
[
2
1
,
2
2
)
⋯
[
2
29
,
2
30
)$。则每块内只有第一个元素可能非法。逐块判断即可。复杂度 
$O
(
n
\log
x
)$。

---

