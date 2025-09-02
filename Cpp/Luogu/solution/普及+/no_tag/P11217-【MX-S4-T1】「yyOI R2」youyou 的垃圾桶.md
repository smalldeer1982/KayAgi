# 【MX-S4-T1】「yyOI R2」youyou 的垃圾桶

## 题目背景

原题链接：<https://oier.team/problems/S4A>。

## 题目描述

现在有 $n$ 个垃圾桶，它们对 youyou 发起攻击。第 $i$ 个垃圾桶的初始攻击力为正整数 $a_i$。youyou 的初始生命值为正整数 $W$。

定义如下流程为一场战斗：

- 从第 $1$ 个垃圾桶开始，每个垃圾桶依次进行攻击。第 $i$ 个垃圾桶发起攻击时，youyou 的生命值 $W$ 减去 $a_i$，然后本次战斗第 $i$ 个垃圾桶的攻击力 $a_i$ 翻倍。在第 $n$ 个垃圾桶攻击完后，重复执行此流程。

当 $W\le 0$ 时，也即 youyou 死亡时，本场战斗立刻结束。然后重置 youyou 的生命值 $W$ 以及所有垃圾桶的攻击力 $a_i$ 为本场战斗之前的值。

定义本次战斗的评分为受到垃圾桶攻击的次数（不包括恰好使 youyou 死亡的垃圾桶的攻击）。

现在一共要进行 $q$ 场战斗，每场战斗给出三个数 $l,r,d$，表示先对第 $[l,r]$ 只垃圾桶进行强化，使这些垃圾桶的初始攻击力 $a_i$ 增加 $d$，然后进行一场战斗。你需要告诉 youyou 此次战斗的评分。

**每场战斗前对垃圾桶初始攻击力的增加会对之后所有的战斗产生影响。**

## 说明/提示

**【样例解释 #1】**

四场战斗前的强化分别是：

- 对 $[1,1]$ 的垃圾桶增加 $1$ 点攻击力。
- 对 $[3,5]$ 的垃圾桶增加 $3$ 点攻击力。
- 对 $[3,5]$ 的垃圾桶增加 $1$ 点攻击力。
- 对 $[3,5]$ 的垃圾桶增加 $3$ 点攻击力。

第一场战斗，垃圾桶的初始攻击力分别为 $10,1,4,5,1,4$。

youyou 首先分别依次受到这些垃圾桶的攻击各一次，此时剩余生命值 $50$。垃圾桶攻击力变为 $20,2,8,10,2,8$。

接着 youyou 受到第一只垃圾桶的攻击，剩余生命值为 $30$。

受到第二只垃圾桶攻击，剩余生命值 $28$。

受到第三只垃圾桶攻击，剩余生命值 $20$。

依次类推，受到第六只垃圾桶攻击时，剩余生命值为 $0$。因为不包括致命攻击，所以共接受了 $6+5=11$ 次攻击。

第二场战斗，垃圾桶的初始攻击力分别为 $10,1,7,8,4,4$。

第三场战斗，垃圾桶的初始攻击力分别为 $10,1,8,9,5,4$。

第四场战斗，垃圾桶的初始攻击力分别为 $10,1,11,12,8,4$。

可以得出第 $2\sim 4$ 场战斗的评分分别为 $9,8,8$。



**【样例 #2】**

见附件中的 ```wxyt/wxyt2.in``` 与 ```wxyt/wxyt2.ans```。

该组样例满足测试点 $1\sim 4$ 的约束条件。

**【样例 #3】**

见附件中的 ```wxyt/wxyt3.in``` 与 ```wxyt/wxyt3.ans```。

该组样例满足测试点 $13\sim 14$ 的约束条件。

**【样例 #4】**

见附件中的 ```wxyt/wxyt4.in``` 与 ```wxyt/wxyt4.ans```。

该组样例满足测试点 $15\sim 20$ 的约束条件。

**【数据范围】**

本题共 $20$ 个测试点，每个 $5$ 分。

| 测试点编号 | $n$ | $q$ |
| :-----------: | :-----------: | :-----------: |
| $1 \sim 4$ | $\le 2 \times 10^5$ | $\le 10$ |  
| $5 \sim 7$ | $\le 2 \times 10^5$ | $\le 10^3$ |
| $8 \sim 10$ | $\le 2 \times 10^5$ | $\le 10^5$ | 
| $11 \sim 12$ | $\le 3 \times 10^3$ | $\le 10^5$ |
| $13 \sim 14$ | $\le 3 \times 10^3$ | $\le10^6$ |
| $15 \sim 20$ | $\le 2 \times 10^5$ | $\le10^6$ |

对于全部数据，保证：$1 \le n \le 2 \times 10^5$，$1 \le q \le 10^6$，$1 \le W \le 10^{18}$，$1 \le a_i \le 10^{6}$，$1 \le l \le r \le n$，$1 \le d \le 2^{15}$。 

## 样例 #1

### 输入

```
6 4 75
9 1 4 5 1 4
1 1 1
3 5 3
3 5 1
3 5 3
```

### 输出

```
11
9
8
8
```

# 题解

## 作者：ykzzldz (赞：27)

感觉这场后面的题都太神秘了。

首先看到区间加的操作，自然想到用线段树。由于每次攻击完一轮后攻击力会翻倍，这样的话，攻击力的增长速度是极快的，所以每次攻击的轮数一定不会太多，我们可以枚举这个轮数。

枚举完轮数后，我们可以知道其剩余的生命值，设为 $res$。剩下的生命值一定是在一轮内打完的，所以我们可以二分出在哪里打出致命伤害，再用 $\log$ 的复杂度在线段树上查询一段前缀的和。这样，总复杂度是 $O(q\log^2n)$ 的，期望得分 $70$（但据说可以使用常树小的树状数组在这个复杂度下通过）。

我们想到，每次二分出再在线段树上查询，这样的效率有点太不高了，于是考虑直接在线段树上二分，这是一个比较经典的问题，大体思路是每次在线段树上找到一个节点，如果这个节点左儿子的权值大于你所求的权值，就往左儿子走，否则往右儿子走。需要注意的是，往右儿子走的时候需要减去左儿子的权值。现在，我们就做到了 $O(q\log n)$ 的复杂度，但由于本题比较卡常，且输入量非常大，所以记得加上快读。下面给出代码：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
void read(int &a){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||'9'<ch){
		if(ch=='-')w=-1;
		ch=getchar(); 
	}
	while('0'<=ch&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	a=s*w;
}
int n,m,W,i,a[N];
struct tree{
	int l,r,pre,add;
}t[N<<2];
void build(int p,int l,int r){
	t[p].l=l,t[p].r=r;
	if(l==r){
		t[p].pre=a[l];
		return;
	}
	int mid=l+r>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p].pre=t[p*2].pre+t[p*2+1].pre;
}
void spread(int p){
	t[p*2].pre+=(t[p*2].r-t[p*2].l+1)*t[p].add;
	t[p*2+1].pre+=(t[p*2+1].r-t[p*2+1].l+1)*t[p].add;
	t[p*2].add+=t[p].add;
	t[p*2+1].add+=t[p].add;
	t[p].add=0;
}
void change(int p,int x,int y,int z){
	if(x<=t[p].l&&t[p].r<=y){
		t[p].pre+=(t[p].r-t[p].l+1)*z;
		t[p].add+=z;
		return;
	}
	spread(p);
	int mid=t[p].l+t[p].r>>1;
	if(x<=mid)change(p*2,x,y,z);
	if(y>mid)change(p*2+1,x,y,z);
	t[p].pre=t[p*2].pre+t[p*2+1].pre;
}
int ask(int p,int res){
	if(t[p].l==t[p].r){
		return t[p].l;
	}
	spread(p);
	int mid=t[p].l+t[p].r>>1;
	if(t[p*2].pre*(1ll<<(i-1))>=res)return ask(p*2,res);
	else return ask(p*2+1,res-t[p*2].pre*(1ll<<(i-1)));
}
signed main(){
	cin>>n>>m>>W;
	for(int j=1;j<=n;j++){
		read(a[j]);
	}
	build(1,1,n);
	while(m--){
		int l,r,d;
		read(l),read(r),read(d);
		change(1,l,r,d);
		i=0;
		int k=2,T=t[1].pre;
		for(i=1;;i++){
			int tot=T*(k-1);
			if(tot>=W)break;
			k*=2;
		}
		int res=W-T*(k/2-1);
		int ans=ask(1,res);
		printf("%lld\n",ans+(i-1)*n-1);
	}
	return 0;
}
```

---

## 作者：what_else (赞：20)

以下设所有垃圾桶当前攻击力总和为 $S$。

我们考虑暴力，因为生命值 $W\le 10^{18}$，攻击力是翻倍递增的，因此最多只会打 $\log{W}$ 轮。因此暴力的时间复杂度是 $O(nq \log W)$。可以获得 $20$ 分。

如果我们假设这场战斗完整地打了 $k$ 轮，那么这 $k$ 轮需要消耗的生命值为 $S \times (2^0 + 2^1 + \dots + 2^{k-1}) = S \times (2 ^ k - 1)$。

接下来，我们就要求出最大的 $m$，使得 $\sum^{m}_{i=1}a_i \le W - S \times (2 ^ k - 1)$。

那么答案即为 $k \times n + m$。

显然，对于每一次修改，$S$ 只会增加 $(r_i - l_i + 1) \times d_i$。

因为能打完必须继续打下去，因此对于每一个询问，我们需要求出最大的 $k$。

假设我们枚举这个 $k$，用线段树维护区间修改，同时线段树上二分快速求出 $m$，那么时间复杂度 $O(q\log W + q \log n)$，预计可以拿到 $70$ 分（实际上可以获得 $100$）。

我们发现 $k$ 不需要每次都枚举，因为每次操作后，答案只会变小，也就是 $k$ 是递减的。我们只需检验之前求出的 $k$ 是否满足 $W \ge S \times (2 ^ k - 1)$ 即可，不满足再暴力往下求解，这样时间复杂度 $O(n \log W + q)$。

对于相同的 $k$，显然 $m$ 也在递减。于是用指针维护 $m$ 的值，同时用两个差分数组维护区间加即可。

对于不同的 $k$，暴力求解即可。

参考代码：

```cpp
#include <iostream>
using namespace std;
const int Q = 1000005;
const int N = 200005;
long long l[Q],r[Q];
long long d[Q];
int q;
long long int A,B,C;
int M;
int n;
long long a[N];
long long W;
__int128 S;
long long k,m;
long long lst[N];
long long nxt[N];
__int128 camPa,camPb;
__int128 lastW;
__int128 sumf;
long long ass;
void workfor_new()
{
	long long now = 0;
	lst[n + 1] = nxt[n + 1] = lst[0] = nxt[0] = 0;
	sumf = 0;
	for(int i = 1;i <= n;i ++)
	{
		now = now + lst[i];
		a[i] = a[i] + now;
		lst[i] = nxt[i] = 0;
	}
	long long BASE = (1ll << k) - 1;
	long long ok = W - S * BASE;
	long long ove = (1ll << k);
	for(int i = 1;i <= n;i ++)
	{
		if(ok <= a[i] * ove) 
		{
			m = i - 1;
			lastW = ok;
			break;
		}
		ok -= a[i] * ove;
	}
	return;
}
long long ans;
int main()
{
    //freopen("wxyt20.in","r",stdin);
    //freopen("wxyt20.out","w",stdout);
    cin >> n >> q >> W;
    for(int i = 1;i <= n;i ++)
    cin >> a[i],S += a[i];
    for(int i = 1;i <= q;i ++)
    {
      scanf("%lld%lld%lld",&l[i],&r[i],&d[i]);
    }
	for(k = 60;k >= 0;k --) 
	{
		camPb = S;
		camPb *= ((1ll << k) - 1ll);
		camPa = W;
		if(camPb < camPa) break;
	}
	
	workfor_new();
	for(int i = 1;i <= q;i ++)
	{
		S = S + (r[i] - l[i] + 1) * d[i];
		camPb = S;
		camPb *= ((1ll << k) - 1ll);
		camPa = W;
		lst[l[i]] += d[i];
		lst[r[i] + 1] -= d[i];
		nxt[r[i]] += d[i];
		nxt[l[i] - 1] -= d[i];
		if(camPb >= camPa)
		{
			for(;k >= 0;k --)
			{
				camPb = S;
				camPb *= ((1ll << k) - 1ll);
				camPa = W;
				if(camPb < camPa) break; 
			}
			workfor_new();
		}
		else
		{
			long long po = (1ll << k); 
			lastW -= (po - 1) * (r[i] - l[i] + 1) * d[i];
			lastW -= d[i] * po * max(min(r[i],m) - l[i] + 1,0ll); 
			if(l[i] <= m + 1 && m < r[i]) sumf += d[i];
			for(;m >= 1;m --)
			{  
				if(lastW > 0) break;
				sumf += nxt[m];
				lastW += (sumf + a[m]) * po; 
			}
		}
        printf("%lld\n",k*n+m);
	}
	
}

```

---

## 作者：Louis_lxy (赞：8)

提供一种不用动脑子的做法，顺便吐槽一下，出题组就不能少出一点这类不动脑子的数据结构题吗，虽然有线性做法但是谁会去想啊？

显然能想到先直接模拟能进行多少轮（即从 $1\sim n$ 执行一次），这是 $\log V$ 的，然后我们二分能继续进行多少次，每次检查前面的所有数的和是否大于剩下的生命值，就做完了，这是 $\log^2n$ 的，计算一下 $O(q\log V+q\log^2n) \approx64\times10^6+18^2\times10^6=3.88 \times10^8$，可以通过（洛谷评测机每秒约 $1.5\times10^9$），维护可以用 zkw 线段树或者树状数组，我用的是树状数组，当然你也可以线段树上二分，这样复杂度是 $O(q\log V+q\log n)\approx 64\times10^6+18\times10^6=8.2\times10^7$，另外这题可能需要开 `__int128`，不过参考代码中没有开。

[参考代码](https://www.luogu.com.cn/record/183542598)。

---

## 作者：liukangyi (赞：7)

# 题目大意
给你 $n$ 个数，以及操作数 $q$，还有生命值 $W$。每次操作中，将一段区间内的数全部加 $d$，每次从第一个数开始多轮循环，第 $i$ 次遍历到第 $j$ 个数时，生命值减去 $a_i \times 2^{i-1}$，现在要求出每次操作后生命值最多可以被减的次数。

---
# 分析
首先这题非常好模拟，但数据范围打消了这一想法，由于 $1\le q \le 10^6$，所以我们每一次询问需要在较短的时间内完成。

观察一下，很容易维护 $n$ 个数的总和，每次操作对总和的贡献为 $(r-l+1) \times d$。记总和为 $sum$，那么第 $i$ 次循环减去的生命值即为 $sum \times 2^{i-1}$，不难看出，此值是指数级增长的，所以我们可以先通过模拟得出 $W$ 的生命值能撑到第几轮，从而也可以计算出剩余生命值。

仔细思考一下，剩余生命值能减到第几轮取决于每一个数的值，而目前我们还尚未维护数组。那么很显然，我们需要用线段树来维护每一个区间和。线段树如何实现就不细说了。

重点讲一下如何求剩余生命值可以减几轮，首先考虑二分轮数，但我们发现这样二分里面还要用 $O(\log n)$ 的时间来计算前缀和，那么每次操作时间复杂度总体来讲就是 $O(\log^2 n)$，这样的时间已经很优，但显然无法在一秒时限内完成。

继续来想如何优化，有没有什么冗余的地方？细想询问前缀和时的操作，分成左右两半，分治处理，那么能不能再这一过程中求出答案呢？显然是可以的，如果左半部分的总和不及剩余生命量，则说明答案在右半部分，反之在左半部分。所以，我们只需要从 $1$ 至 $n$ 这一区间开始递归，按照上述所讲逐渐求出答案，时间复杂度就优化到了 $O(q \times \log n)$，可以通过。

---
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
//记得快读快写 
int read(){
	int x=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9'){  
		if(ch=='-')
			w=-1;        
    	ch=getchar();
  	}
  	while(ch>='0'&&ch<='9'){ 
    	x=x*10+(ch-'0'); 
    	ch=getchar(); 
  	}
  	return x*w; 
}
void write(int x){
	static int sta[35];
	int top=0;
  	do{
    	sta[top++]=x%10,x/=10;
  	}while(x);
  	while(top)
		putchar(sta[--top]+48); 
}
const int N=2e5;
int n,q,w;
int tot,pos,cur;
int a[N+10];
struct Node{
	int l,r;
	int sum,tag;	
}Tree[N<<2];
void push_up(int now,int lson,int rson){
	Tree[now].sum=Tree[lson].sum+Tree[rson].sum;
}
void push_down(int now,int lson,int rson){
	int mid=Tree[now].l+Tree[now].r>>1;
	Tree[lson].sum+=(mid-Tree[now].l+1)*Tree[now].tag;
	Tree[rson].sum+=(Tree[now].r-mid)*Tree[now].tag;
	Tree[lson].tag+=Tree[now].tag;
	Tree[rson].tag+=Tree[now].tag;
	Tree[now].tag=0;
}
void buildTree(int now,int L,int R){
	Tree[now].l=L,Tree[now].r=R;
	if(L==R){
		Tree[now].sum=a[L];
		return ;
	}
	int mid=L+R>>1;
	int lson=now<<1;
	int rson=lson|1;
	buildTree(lson,L,mid);
	buildTree(rson,mid+1,R);
	push_up(now,lson,rson);
}
void update(int now,int L,int R,int val){
	if(L<=Tree[now].l&&Tree[now].r<=R){
		Tree[now].sum+=(Tree[now].r-Tree[now].l+1)*val;
		Tree[now].tag+=val;
		return ;
	}
	int lson=now<<1;
	int rson=lson|1;
	push_down(now,lson,rson);
	if(L<=Tree[lson].r)
		update(lson,L,R,val);
	if(Tree[rson].l<=R)
		update(rson,L,R,val);
	push_up(now,lson,rson);
}
int dfs(int now,int L,int R,int tmp){
	if(Tree[now].l==Tree[now].r)
		return Tree[now].l;
	int lson=now<<1;
	int rson=lson|1;
	if(Tree[now].tag)
		push_down(now,lson,rson);
	int mid=Tree[now].l+Tree[now].r>>1;
	if(Tree[lson].sum*cur>=tmp)//如果答案在左区间 
		return dfs(lson,L,mid,tmp);
	return dfs(rson,mid+1,R,tmp-Tree[lson].sum*cur);
}
signed main(){
	n=read(),q=read(),w=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		tot+=a[i];//数组总和 
	}
	buildTree(1,1,n);//建树 
	while(q--){
		int l,r,d;
		l=read(),r=read(),d=read();
		tot+=(r-l+1)*d;//维护总和 
		update(1,l,r,d);//区间修改 
		cur=1;
		int tmp=w;
		int ans=0;
		//模拟每一轮 
		while(tmp>cur*tot){
			ans+=n;
			tmp-=cur*tot;
			cur<<=1;
		}
		ans+=dfs(1,1,n,tmp)-1;//递归求出答案 
		write(ans);
		putchar('\n');
	}
	return 0;
}

```

---

## 作者：The_foolishest_OIer (赞：6)

# P11217题解

## Part 0 致谢：

感谢 [mengzdd](https://www.luogu.com.cn/user/1351685) 大佬对该题解提出的宝贵建议。

## Part 1 读题 & 分析

该题解做法：线段树 + 二分。

题目大意：

youyou 要去打仗，打仗前有一部分敌人的战斗力会上升，接着，youyou 会一个接着一个打过去，直到 Ta 死了，当 youyou 战胜了一个敌人之后（剩余血量无法被那个敌人一击致命），那个敌人便会重新“满血复活”，并且战斗力提高至原来的 $2$ 倍，求 youyou 最多能打倒多少个敌人 **（最后一个不算，一个敌人可以被打多次）**。

看到这里，我们可以发现，要实现两种操作，区间修改和区间查询，所以我们立刻想到了线段树。

## Part 2 修改

题目要求在战斗开始前要修改一部分连续垃圾桶的战斗力，这是一个线段树十分典型的运用（~~就是板子~~），不会的请出门左转：[【模板】线段树1](https://www.luogu.com.cn/problem/P3372) 。

## Part 3 计算评分

我们可以发现，youyou 打敌人时，肯定是先打了 $k$（$k \ge 0$）轮之后，又打了几个敌人，因为敌人的战斗力是在不断翻倍的，所以 $k \le \log W$（最坏情况是只有一个敌人，初始战斗力为 $1$ ），所以我们先统计出 $x$ 的值（$x = \sum_{i = 1}^{n} a_i$ ，即为所有垃圾桶再修改后的初始战斗力之和），再去暴力枚举，代码如下：


```cpp
int level = 1;
int ans = 0;
int blood = w;
int all = query(1,1,n,1,n); // 统计战斗力之和，query函数见下面 
while(1){
    if (blood <= all) break; // 如果剩余血量不够杀一整排敌人了，退出循环 
    blood -= all; // 扣血 
    all *= 2; // 因为敌人的血量会翻倍，所以要乘 2 
    ans += n; // 又战胜了 n 个敌人 
    level *= 2;
}
```

接下来我们要统计，youyou 还能杀多少个敌人，于是我们立刻就想到了二分。

但是我们会发现，我们并没有修改战斗力，因为所有敌人的战斗力都乘上了 $2^k$（$k$ 的定义见上方），所以我们只需要维护一个变量，计算这些敌人的战斗力翻了的倍数即可，这就解释了上面的这条语句：`level *= 2;`

二分代码如下：

```cpp
int L = 1,R = n,tmid,p = 0;
    while(L <= R){
        tmid = (L + R) >> 1;
    if (query(1,1,n,1,tmid) * level < blood){
        p = tmid;
        L = tmid + 1;
    }else{
        R = tmid - 1;
    }
}
```

## Part 4 优化

我们会发现，计算评分的时间复杂度是 $O(q \log^2 n)$ 的，会被卡掉，所以考虑优化。

二分放在外面是十分浪费时间的，我们可以直接对线段树进行二分，如果左儿子的权值**大于**所求权值，则递归右子树，否则递归左子树，做法显然是正确的。

但是，还是有一点坑的，比如这个。

你不能写成这样：

```cpp
if (blo >= sum[o << 1] * lev) return query2(o << 1 | 1,mid + 1,r,lev,blo - sum[o << 1] * lev);
```

而应该写成这样：

```cpp
if (blo > sum[o << 1] * lev) return query2(o << 1 | 1,mid + 1,r,lev,blo - sum[o << 1] * lev);
```

这是因为，**最后一个不算**，如果一个人的血量刚好能被那个敌人击败，那么是不算的，所以**不能写成大于等于号**。

最后的答案显然是 $nk + p - 1$（$p$ 表示 youyou 在战斗了 $k$ 轮 后，还能杀多少个敌人）。

闲话：如果你写成了 `blo >= sum[o << 1] * lev` ，你过不了第一个样例，但是可以 AC，所以本题 hack 数据就是第一个样例（赛时）。

本部分代码：

```cpp
int query2(int o,int l,int r,int lev,int blo){
	if (l == r) return l; // 返回最多能打到的编号
	int mid = (l + r) >> 1;
	pushdown(o,l,r);
	if (blo > sum[o << 1] * lev) return query2(o << 1 | 1,mid + 1,r,lev,blo - sum[o << 1] * lev); // 左儿子的权值大于所求权值，递归右子树，不要忘记血量要减少
	else return query2(o << 1,l,mid,lev,blo); // 递归左子树
}
```

## Part 5 AC Code

时间复杂度是 $O(q \log W + q \log n)$。

线段树空间开 $4$ 倍！！！


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
int n,q,w;
int a[N],sum[N << 2],lzy[N << 2];
void pushup(int o){
	sum[o] = sum[o << 1] + sum[o << 1 | 1];
}
void build(int o,int l,int r){
	if (l == r){
		sum[o] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1,l,mid);
	build(o << 1 | 1,mid + 1,r);
	pushup(o);
}
void pushdown(int o,int l,int r){
	int mid = (l + r) >> 1;
	sum[o << 1] += lzy[o] * (mid - l + 1);
	sum[o << 1 | 1] += lzy[o] * (r - mid);
	lzy[o << 1] += lzy[o];
	lzy[o << 1 | 1] += lzy[o];
	lzy[o] = 0;
}
void update(int o,int l,int r,int ql,int qr,int x){
	if (ql <= l && r <= qr){
		sum[o] += (r - l + 1) * x;
		lzy[o] += x;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(o,l,r);
	if (ql <= mid) update(o << 1,l,mid,ql,qr,x);
	if (qr > mid) update(o << 1 | 1,mid + 1,r,ql,qr,x);
	pushup(o);
}
int query(int o,int l,int r,int ql,int qr){
	if (ql <= l && r <= qr)
	    return sum[o];
	int mid = (l + r) >> 1;
	int ret = 0;
	pushdown(o,l,r);
	if (ql <= mid) ret += query(o << 1,l,mid,ql,qr);
	if (qr > mid) ret += query(o << 1 | 1,mid + 1,r,ql,qr);
	return ret;
}
int query2(int o,int l,int r,int lev,int blo){
	if (l == r) return l;
	int mid = (l + r) >> 1;
	pushdown(o,l,r);
	if (blo > sum[o << 1] * lev) return query2(o << 1 | 1,mid + 1,r,lev,blo - sum[o << 1] * lev);
	else return query2(o << 1,l,mid,lev,blo);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q >> w;
	for (int i = 1 ; i <= n ; i++) cin >> a[i];
	build(1,1,n);
	for (int i = 1 ; i <= q ; i++){
		int l,r,d;
		cin >> l >> r >> d;
		update(1,1,n,l,r,d);
		int level = 1;
		int ans = 0;
		int blood = w;
		int all = query(1,1,n,1,n);
		while(1){
			if (blood <= all) break;
			blood -= all;
			all *= 2;
			ans += n;
			level *= 2;
		}
		int p = query2(1,1,n,level,blood);
		cout << ans + p - 1 << '\n';
	}
	return 0;
}
```

---

## 作者：fish_love_cat (赞：4)

CSP 原来还考线段树啊，我只会改板子到时候要爆零了额……

---

首先，发现有个很可怕的翻倍，于是开始推式子。

我们可以先求出能总的跑几圈。

用 $W-1$ 除去不翻倍情况下总的一圈伤害和，得到不翻倍时能跑的圈数 $s$。注意跑完 $s$ 时必须要活着，所以要 $W-1$ 而非 $W$。

然后再思考翻倍。

注意到，此时能跑 $i$ 圈必须满足 $s\ge2^i-1$。

我们可以预处理 $f_i=2^i$，然后二分求出最多圈数 $o$。

然后就把翻倍给搞定了，剩下的全部以 $2^o$ 为伤害单位。

警示后人：不要像这个制杖一样因为以为 $2^1=1$ 而调 2.5h。

---

接下来看到一个更可怕的区间修改，而且不是相互独立的。

那么我们可以想到线段树。

~~于是我复制了 P3372 的码（~~

发现不到一圈答案越大伤害越多。

~~然后可以想到二分答案。~~

二分答案是 $O(q \log ^2 n)$ 的，会似的很惨，大样例三秒往上了。但是应该能拿一些分。

在同学的启示下发现可以线段树上二分。

如果左子树的和不能杀掉的话那就进行攻击后进右子树。否则原封不动进左子树。

然后就可以找到最后一轮死哪了。

输出记得减掉死的这个点。

警示后人：善用预处理或位运算，不要使用快速幂达到神金负优化谔谔。

---

然后就做完了。

代码：

你可以看到很多神金错误，不建议参考。一些不明意义的东西是套模版的时候不想改了随机乱写的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define ll long long
#define mod 2000000000000000000
const int maxn=2e5+10;
int n,W;
ll a[maxn],w[maxn<<2],z[maxn<<2],L[maxn<<2],R[maxn<<2];//存储，树，懒标记
void pushup(const int u){w[u]=w[u<<1]+w[(u<<1)+1];}//合并（满足结合律！）
void build(const int u,int l,int r){//建树
	L[u]=l,R[u]=r;
    if(l==r){w[u]=a[l]; return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build((u<<1)+1,mid+1,r),pushup(u);
}
bool inrg(int l,int r,int l2,int r2){return (l2<=l)&&(r<=r2);}//包含？
bool outrg(int l,int r,int l2,int r2){return (l>r2)||(r<l2);}//无交集？
void mktag(int u,int l,ll x){z[u]+=x,w[u]+=l*x;}//更改
void pushdown(int u,int l,int r){//更新儿子
    int mid=(l+r)>>1;
    mktag(u<<1,mid-l+1,z[u]),mktag((u<<1)+1,r-mid,z[u]),z[u]=0;
}
void update(int u,int l,int r,int l2,int r2,ll x){//二分修改
    if(inrg(l,r,l2,r2)) mktag(u,r-l+1,x);
    else if(!outrg(l,r,l2,r2)){
        int mid=(l+r)>>1;
        pushdown(u,l,r),update(u<<1,l,mid,l2,r2,x),update((u<<1)+1,mid+1,r,l2,r2,x),pushup(u);
    }
}
int awa[105],o;
int sum;
//long long qpow(long long a,long long b,long long p){
//	long long ans=1;
//	if(b==0){
//		return 1;
//	}
//	while(b){
//		if(b&1){
//			ans*=a;
//			ans%=p;
//		}
//		a*=a;
//		b>>=1;
//		a%=p;
//	}
//	return ans;
//}
ll query(int u,int flc){//记和
    if(L[u]==R[u]) return L[u];
    //if(!outrg(l,r,l2,r2)){
        int mid=(L[u]+R[u])>>1; pushdown(u,L[u],R[u]);
        if(w[u*2]*awa[o]<flc)return query((u<<1)+1,flc-w[u*2]*awa[o]);
		return query((u<<1),flc);
    //}
    return 0;
}
//bool check(int x){
//    int flc=query(1,1,n,1,x)*qpow(2,o,mod);
//    return flc<W-qpow(2,o,mod)*sum;
//}
void init(){
    awa[0]=1;
    for(int i=1;i<=60;i++)
    awa[i]=awa[i-1]*2;
}
int read(){
    int sum=0,fish=1;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')fish=-1,c=getchar();
    while(c>='0'&&c<='9')sum=sum*10+(c-'0'),c=getchar();
    return sum*fish;
}
void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else print(x/10),putchar(x%10+'0');
}
signed main(){
    init();
    int q;
    n=read(),q=read(),W=read();
    for(int i=1;i<=n;i++)
    a[i]=read(),sum+=a[i];
    build(1,1,n);
    //cout<<"KDLAKIOI  "<<query(1,1,n,1,4)<<endl;
    while(q--){
        int l=read(),r=read(),d=read();
        sum+=(r-l+1)*d;
        update(1,1,n,l,r,d);
        o=upper_bound(awa,awa+1+60,(W-1)/sum+1)-awa-1;

//        int L=1,R=n;
//        while(L<R){
//            int mid=(L+R)/2;
//            if(check(mid))L=mid;
//            else R=mid-1;
//        }
		int ans=query(1,W-(awa[o]-1)*sum);
		
        print(ans+o*n-1);
		putchar('\n');
    }
    return 0;
}
//在题解里拉了坨大的谔谔
```

[记录](https://www.luogu.com.cn/record/183638052)。

---

> 隔壁家风铃草姐姐，今年期中考前还在打梦熊，不写作业不复习，你可千万不能变成她那样。

---

## 作者：forever_nope (赞：3)

本题解时间复杂度为 $\mathcal O(q\log^2n)$ 的卡常做法，优点是思维难度小、实现较容易。

---

设进行了 $k$ 轮完整的，我们假设最后恰好的一轮不算。设 $R=\sum_{i=1}^na_i$ 表示一轮、不计系数的总伤害，根据等比数列求和，我们知道要求 $k$ 恰好满足：

$$
\begin{aligned}
(2^{k+1}-1)R&\ge W\\
2^{k+1}-1&\ge\dfrac WR=\lambda\\
2^{k+1}&\ge\lambda+1\\
k+1&\ge\log_2(\lambda+1)\\
k&=\lceil\log_2(\lambda+1)-1\rceil
\end{aligned}
$$

那么，在经过 $k$ 轮之后，记现在的血量为 $T=W-(2^k-1)R$，记 $S$ 为 $a_i$ 的前缀和，我们需要找到第一个 $p$ 满足：

$$
\begin{aligned}
2^kS(p)&\ge T\\
S_p&\ge\dfrac{T}{2^k}\\
S_p&\ge\left\lceil\dfrac{T}{2^k}\right\rceil
\end{aligned}
$$

可以二分查找、使用数据结构维护，那么答案就是 $nk+p-1$。

---

代码实现上，为了实现区间加、区间查询，我们可以使用线段树，但是会被卡常。因此我们使用两个树状数组维护，具体的，假设我们维护了一个差分数组，我们要查询：

$$
\begin{aligned}
S(x)&=\sum_{i=1}^xa_i\\
a_x&=\sum_{i=1}^xd_i
\end{aligned}
$$

那么，

$$
S(x)=\sum_{i=1}^x\sum_{j=1}^id_j=\sum_{i=1}^xd_i(x-i+1)
$$

![](https://cdn.luogu.com.cn/upload/image_hosting/t6flhcrh.png)

如上图所示，整理得：

$$
S(x)=(x+1)\sum_{i=1}^xd_i-\sum_{i=1}^xi\cdot d_i
$$

使用树状数组维护前缀和、乘下标的前缀和即可。区间加法使用差分维护即可，这是经典技巧。

---

代码（包含了赛时被卡 TLE 的线段树代码）：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl "\n"

using ll = long long;

#define int ll

constexpr int N = 2e5 + 10;

int n, q, w;

int b[N];

namespace seg {
	// #define ls(k) ((k) << 1)
	// #define rs(k) ((k) << 1 | 1)
	// #define avg(l, r) (((l) + (r)) >> 1)

	// struct node {
	// 	int l, r;
	// 	int v, tag;
	// } a[N << 2];

	// void action(int k, int v) {
	// 	a[k].tag += v;
	// 	a[k].v += (a[k].r - a[k].l + 1) * v;
	// }

	// void push_down(int k) {
	// 	if (a[k].tag == 0)
	// 		return;
	// 	action(ls(k), a[k].tag);
	// 	action(rs(k), a[k].tag);
	// 	a[k].tag = 0;
	// }

	// void push_up(int k) {
	// 	a[k].v = a[ls(k)].v + a[rs(k)].v;
	// }

	class fenwick {
		private:

			#define lowbit(x) ((x) & -(x))

			int m;

			int s[N], a[N];

		public:

			void resize(int n) {
				m = n;
				memset(s, 0, sizeof(int) * (n + 1));
				memset(a, 0, sizeof(int) * (n + 1));
			}

			void modify(int x, int v) {
				for (; x <= m; x += lowbit(x))
					s[x] += v;
			}

			int query(int x) {int r = 0;
				for (; x; x -= lowbit(x))
					r += s[x];
				return r;
			}
	} a, ai;

	void build(int k, int l, int r) {
		a.resize(r - l + 1);
		ai.resize(r - l + 1);
		for (int i = l; i <= r; ++i) {
			a.modify(i, b[i] - b[i - 1]);
			ai.modify(i, i * (b[i] - b[i - 1]));
		}
		// a[k] = node{l, r, 0, 0};
		// if (l == r)
		// 	return action(k, b[l]);
		// int mid = avg(l, r);
		// build(ls(k), l, mid);
		// build(rs(k), mid + 1, r);
		// push_up(k);
	}

	void modify(int k, int p, int q, int v) {
		a.modify(p, v);
		ai.modify(p, v * p);
		if (q != n) {
			a.modify(q + 1, -v);
			ai.modify(q + 1, -v * (q + 1));
		}
		// int l = a[k].l, r = a[k].r;
		// if (l >= p && r <= q)
		// 	return action(k, v);
		// push_down(k);
		// int mid = avg(l, r);
		// if (q <= mid)
		// 	modify(ls(k), p, q, v);
		// else if (p >= mid + 1)
		// 	modify(rs(k), p, q, v);
		// else {
		// 	modify(ls(k), p, q, v);
		// 	modify(rs(k), p, q, v);
		// }
		// push_up(k);
	}

	int query(int k, int p, int q) {
		assert(p == 1);
		return (q + 1) * a.query(q) - ai.query(q);
		// int l = a[k].l, r = a[k].r;
		// if (l >= p && r <= q)
		// 	return a[k].v;
		// push_down(k);
		// int mid = avg(l, r);
		// if (q <= mid)
		// 	return query(ls(k), p, q);
		// if (p >= mid + 1)
		// 	return query(rs(k), p, q);
		// return query(ls(k), p, q) + query(rs(k), p, q);
	}
}

int query() {
	int W = w;
	int R = seg::query(1, 1, n);
	// cout << "QUERY: " << endl;
	// R 2R 4R 8R ...
	// R 3R 7R 15R
	// 2 4  8  16-1
	int k = ceil(log2(W * (long double)1.0 / R + 1) - 1);
	// cout << W << " " << R << " " << k << endl;
	int T = W - R * ((1ll << k) - 1);
	int S = (T + (1ll << k) - 1) >> k;
	// cout << "| R " << R << endl;
	// cout << "| k " << k << endl;
	// cout << "| T " << T << endl;
	// cout << "| S " << S << endl;
	int l = 1, r = n;
	int ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		int res = seg::query(1, 1, mid);
		// cout << "  | " << mid << ": " << res << endl;
		if (res >= S)
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	return ans + n * k - 1;
}

void Main() {
	cin >> n >> q >> w;
	for (int i = 1; i <= n; ++i)
		cin >> b[i];
	seg::build(1, 1, n);
	while (q--) {
		int l, r, d;
		cin >> l >> r >> d;
		seg::modify(1, l, r, d);
		cout << query() << endl;
	}
	return;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	return Main(), 0;
}

```

---

## 作者：xz001 (赞：3)

首先轮数不会太多，最多 $\log W$ 轮，我们一轮一轮的枚举，在最后一轮，由于不会所有垃圾桶都进行攻击了，我们二分停止攻击的位置，线段树求和判断即可，但是线段树常数较大，会超时，所以使用可以区间加区间求和的特殊的树状数组即可。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long
#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)

using namespace std;

const int N = 2e5 + 5;

int n, q, w, a[N], t[2][N];

inline void upd (const int at, register int x, const int k) {
	while (x <= n) {
		t[at][x] += k;
		x += x & -x;
	}
	return;
} 

inline int que (const int at, register int x) {
	register int ans = 0;
	while (x) {
		ans += t[at][x];
		x ^= x & -x;
	}
	return ans;
}

inline void build (const int l, const int r) {
	for (register int i = 1; i <= n; ++ i ) {
		upd (0, i, a[i]);
		upd (0, i + 1, -a[i]);
		upd (1, i, (i - 1) * a[i]);
		upd (1, i + 1, -i * a[i]); 
	}
	return;
} 

inline void update (const int l, const int r, const int d) {
	upd (0, l, d);
	upd (0, r + 1, -d);
	upd (1, l, (l - 1) * d);
	upd (1, r + 1, -r * d); 
	return;
}

inline int query (const int l, const int r) {
	return (r * que (0, r) - (l - 1) * que (0, l - 1)) - (que (1, r) - que (1, l - 1)); 
} 

inline int solve () {
	register int x = 1, sum = query (1, n), g = query (1, n), cnt = 0;
	while (g < w) {
		cnt += n;
		x <<= 1;
		g += x * sum;
	}
	g -= x * sum;
	register int l = 1, r = n, ans = 0;
	while (l <= r) {
		const int mid = (l + r) >> 1;
		if (query (1, mid) * x + g < w) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return cnt + ans;
}

signed main() {
	scanf("%lld%lld%lld", &n, &q, &w);
	for (int i = 1; i <= n; ++ i ) scanf("%lld", a + i);
	build (1, n);
	while (q -- ) {
		int l, r, d;
		scanf("%lld%lld%lld", &l, &r, &d);
		update (l, r, d);
		printf("%lld\n", solve());
	}
	return 0;
} 
```

---

## 作者：Genius_Star (赞：3)

线段树二分板子题，建议绿吧。

### 思路：

首先考虑进行操作的轮数设为 $t$，则 $(2^t - 1) sum \ge w$，故可以二分或者使用 `log2` 函数求得。

现在问题转化为找到一个位置 $i$，使得 $(a_1+a_2+\cdots+a_i) 2^{t-1} \ge w - (2^{t-1} - 1) sum$，由于是多组询问，区间修改，在线段树上二分即可。

时间复杂度为 $O(Q \log W + Q\log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10; 
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Node{
	int l, r;
	ll sum;
	ll tag;
}X[N << 2];
int n, q, l, r, v;
ll w, sum, base, t, ans;
ll a[N], poww[N];
inline void init(){
	poww[0] = 1;
	for(int i = 1; i <= 63; ++i)
	  poww[i] = poww[i - 1] << 1ll;
}
inline void add(int k, ll v){
	X[k].sum += 1ll * (X[k].r - X[k].l + 1) * v;
	X[k].tag += v;
}
inline void push_down(int k){
	if(X[k].tag){
		add(k << 1, X[k].tag);
		add(k << 1 | 1, X[k].tag);
		X[k].tag = 0;
	}
}
inline void pushup(int k){
	X[k].sum = X[k << 1].sum + X[k << 1 | 1].sum;
}
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l==r){
		X[k].sum = a[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void update(int k, int l, int r, int v){
	if(X[k].l == l && r == X[k].r){
		add(k, v);
		return ;
	}
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  update(k << 1, l, r, v);
	else if(l > mid)
	  update(k << 1 | 1, l, r, v);
	else{
		update(k << 1, l, mid, v);
		update(k << 1 | 1, mid + 1, r, v);
	}
	pushup(k);
}
inline int query(int k, ll base, ll w){
	if(X[k].l == X[k].r)
	  return X[k].l;
	push_down(k);
	if(X[k << 1].sum * base >= w)
	  return query(k << 1, base, w);
	else
	  return query(k << 1 | 1, base, w - X[k << 1].sum * base);
}
bool End;
int main(){
//	open("A.in", "A.out");
	init();
	n = read(), q = read(), w = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		sum += a[i];
	}
	build(1, 1, n);
	while(q--){
		ans = 0;
		l = read(), r = read(), v = read();
		update(1, l, r, v);
		sum += 1ll * (r - l + 1) * v;
		int L = 0, R = log2(w / sum) + 2;
		while(L <= R){
			int mid = (L + R) >> 1;
			if((poww[mid] - 1) * sum >= w){
				t = mid;
				R = mid - 1;
			}
			else
			  L = mid + 1;
		}
//		cerr << t << '\n'; 
		ans = n * (t - 1);
		base = poww[t - 1];
		if(t)
		  t = (poww[t - 1] - 1) * sum;
//		cerr << ans << ' ' << t << ' ' << base << '\n';
		ans += query(1, base, w - t);
		write(ans - 1);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：jdfz2251533 (赞：1)

# 题解：P11217 【MX-S4-T1】「yyOI R2」youyou 的垃圾桶

## 思路

看到区间加，想到线段树。

设最开始的攻击力之和为 $sum$，对于**强化**操作，令 $sum \gets sum + d(r - l + 1)$，然后 update 一下就好了。

接下来要算答案了，不难发现，致死之前的每一轮造成的伤害总和可以用等比数列求和算出来，那就可以设轮数为 $k$ 的时候致死，拿数据范围估计一下 $k$ 只有几十，一个 while 循环就搞定。

然后把前 $k - 1$ 轮的伤害减掉：$W \gets W - sum \times (2^{k - 1} - 1)$，如果此时已经死了，则答案为 $n(k-1) - 1$。

接下来要找致死点，如果是朴素的查找显然会 TLE，但是别忘了：刚才建了一颗线段树，所以可以搞一个线段树二分，把致死点二分出来，加上刚才的 $n(k-1) - 1$ 就是答案了。

## 复杂度

此题氢微卡常，$O(q\log^2{n})$ 的复杂度大抵会寄（貌似有人能过），所以建议用 $O(q\log{n} )$ 的线段树二分做。本人的结构体较慢，所以加了一车 inline 和快读。

## code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;

int n, q, l, r;
ll W, a[N], d, pw[50], sum;
struct node {
	int l, r;
	ll tag, sum;
} t[N << 2];

inline int ls(int p) {
	return p << 1;
}

inline int rs(int p) {
	return p << 1 | 1;
}

inline ll read() {
	char c = getchar();
	int tot = 1;
	while ((c < '0' || c > '9') && c != '-') {
		c = getchar();
		if (c == '-') {
			tot = -1;
			c = getchar();
		}
	}
	ll sum = 0;
	while (c >= '0' && c <= '9') {
		sum = sum * 10 + c - '0';
		c = getchar();
	}
	return sum * tot;
}

inline void pushup(int p) {
	t[p].sum = t[ls(p)].sum + t[rs(p)].sum;
}

inline void pushdown(int p) {
	if (t[p].tag != 0) {
		t[ls(p)].sum += ((t[ls(p)].r - t[ls(p)].l + 1) * t[p].tag);
		t[ls(p)].tag += t[p].tag;
		t[rs(p)].sum += ((t[rs(p)].r - t[rs(p)].l + 1) * t[p].tag);
		t[rs(p)].tag += t[p].tag;
		t[p].tag = 0;
	}
}

inline void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	if (l == r) {
		t[p].sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	pushup(p);
}

inline void update(int p, int l, int r, ll k) {
	if (l <= t[p].l && r >= t[p].r) {
		t[p].sum += (t[p].r - t[p].l + 1) * k;
		t[p].tag += k;
		return;
	}
	pushdown(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) {
		update(ls(p), l, r, k);
	}
	if (r > mid) {
		update(rs(p), l, r, k);
	}
	pushup(p);
	return;
}

inline int solve(int k) {
	int p = 1, l = 1, r = n, res = 0;
	while (l <= r) {
		if (l == r && t[p].sum * pw[k] >= W) {
			break;
		}
		if (t[p].sum * pw[k] < W) {
			return res + r - l + 1;
			break;
		}
		int mid = (l + r) >> 1;
		pushdown(p);
		if (t[ls(p)].sum * pw[k] < W) {
			res += (mid - l + 1);
			W -= t[ls(p)].sum * pw[k];
			p = rs(p);
			l = mid + 1;
		} else {
			p *= 2;
			r = mid;
		}
	}
	return res;
}

signed main() {
	n = read();
	q = read();
	W = read();
	for (int i = 1; i <= n; i++) {
		a[i] = read();
		sum += a[i];
	}
	pw[0] = 1;
	for (int i = 1; i <= 45; i++) {
		pw[i] = pw[i - 1] * 2;
	}
	build(1, 1, n);
	while (q--) {
		l = read();
		r = read();
		d = read();
		ll w = W;
		int k = 0;
		update(1, l, r, d);
		sum += (r - l + 1) * d;
		while (W >= sum * (pw[k] - 1)) {
			k++;
		}
		k--;
		W -= sum * (pw[k] - 1);
		if (W == 0) {
			printf("%d\n", n * k - 1);
			W = w;
			continue;
		}
		int ans = n * k;
		ans += solve(k);
		printf("%d\n", ans);
		W = w;
	}
}
```

---

## 作者：xixisuper (赞：1)

# P11217 【MX-S4-T1】「yyOI R2」youyou 的垃圾桶 题解

这题切了吗？如切，场上开了 `__int128` 挂成了 $0$ 分，结果改成 `long long` 就过了，不嘻嘻。

特别板的线段树上二分，感觉绿差不多。

## 思路

不难发现我们需要实现区间加这个操作，所以我们选择线段树来维护。

显然我们需要看进行多少次整个序列的操作，然后我们注意到每一次操作整个序列后，序列里的每个数都会变为原先的二倍，所以说不会进行超过 $\log_2W$ 次整段的操作，我们只需要维护当前是原来的数的多少倍，暴力统计即可。

对于最后不足整段的操作，由于必然是从整个序列的头部开始进行操作，所以我们可以直接**线段树上二分**。详细的说，就是如果当前剩余的 $W$ 大于所在线段树上左儿子的和，则让 $W$ 减去左儿子的和，然后上右儿子递归；否则直接上左儿子递归。不难发现我们至多递归 $\log_2n$ 次。

综上所述，我们就能够在 $O(q\log n+q\log W)$ 的时间复杂度下解决该问题了。

## 代码

下次不用 `__int128` 了。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define ll long long
#define lc (x<<1)
#define rc ((x<<1)|1)
#define mid ((l+r)>>1) 
using namespace std;
const ll N=2e5+10;
inline ll read(){
	register ll x=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
ll n,q,W,a[N],sum[N<<2],tag[N<<2];
inline void push_up(ll x){sum[x]=sum[lc]+sum[rc];}
inline void push_down(ll x,ll l,ll r){
	if(!tag[x]) return;
	tag[lc]+=tag[x],tag[rc]+=tag[x];
	sum[lc]+=(mid-l+1)*tag[x];
	sum[rc]+=(r-mid)*tag[x];
	tag[x]=0; 
}
void build(ll x,ll l,ll r){
	if(l==r){
		sum[x]=a[l];
		return;
	}
	build(lc,l,mid);
	build(rc,mid+1,r);
	push_up(x);
}
void ad(ll x,ll l,ll r,ll L,ll R,ll v){
	if(L<=l&&r<=R){
		tag[x]+=v;
		sum[x]+=(r-l+1)*v;
		return;
	}
	push_down(x,l,r);
	if(L<=mid) ad(lc,l,mid,L,R,v);
	if(R>mid) ad(rc,mid+1,r,L,R,v);
	push_up(x);
}
ll erfen(ll x,ll l,ll r,ll bei,ll T){
	ll ret=0;
	if(l==r) return 0;
	push_down(x,l,r);
	if(T<=sum[lc]*bei) return erfen(lc,l,mid,bei,T);
	ret=(mid-l+1);
	ret+=erfen(rc,mid+1,r,bei,T-sum[lc]*bei);
	return ret;
}
int main(){
	n=read();q=read();W=read();
	for(ll i=1;i<=n;i++) a[i]=read();
	build(1,1,n);
	while(q--){
		ll l=read(),r=read(),d=read();
		ad(1,1,n,l,r,d);
		ll ans=0,bei=1,T=W;
		while(bei*sum[1]<T){
			T-=bei*sum[1];
			bei<<=1;
			ans+=n;
		}
		ans+=erfen(1,1,n,bei,T);
		long long oott=ans;
		cout<<oott<<"\n";
	}
	return 0;
} 
```

---

## 作者：Dtw_ (赞：0)

# Solution
区间加直接用线段树维护一下。

然后观察一下，就可以发现 $W$ 减掉**整个序列**的次数很小。当序列只有 $1$ 个 $1$ 的时候，减掉整个序列的次数是 $\log10^{18}$ 只有 $60$ 左右，所以减的时候直接暴力，减掉整个序列，不够的时候直接线段树二分出第一个 $\ge$ 当前剩余的位置就好。

时间复杂度 $O(Q(\log W + \log n))$。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define fi first
#define se second

#define int long long

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int inf = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 2e5 + 10;

int n, q, a[N], w;

struct Node
{
	int x, sz;
	int tag;
} tr[N << 2];

#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define mid ((l + r) / 2)

inline void push_up(int rt)
{
	tr[rt].x = tr[lson].x + tr[rson].x;
}

inline void build(int rt, int l, int r)
{
	tr[rt].sz = r - l + 1;
	if (l == r)
	{
		tr[rt].x = a[l];
		return;
	}
	build(lson, l, mid);
	build(rson, mid + 1, r);
	push_up(rt);
}

inline void push_down(int rt)
{
	int &u = tr[rt].tag;
	if (u != 0)
	{
		tr[lson].x += u * tr[lson].sz;
		tr[rson].x += u * tr[rson].sz;
		tr[lson].tag += u;
		tr[rson].tag += u;
		tr[rt].tag = 0;
	}
}

void update(int rt, int l, int r, int sp, int ep, int v)
{
	if (sp <= l && r <= ep)
	{
		tr[rt].x += tr[rt].sz * v;
		tr[rt].tag += v;
		return;
	}
	push_down(rt);
	if (sp <= mid) update(lson, l, mid, sp, ep, v);
	if (ep > mid) update(rson, mid + 1, r, sp, ep, v);
	push_up(rt);
}

int qry(int rt, int l, int r, int k, int p)
{
	if (l == r) return l;
	push_down(rt);
	if (p * tr[lson].x >= k) return qry(lson, l, mid, k, p);
	return qry(rson, mid + 1, r, k - p * tr[lson].x, p);
}

#undef mid

signed main()
{
//	freopen("wxyt4.in", "r", stdin);
//	freopen("1.txt", "w", stdout);
	fst
	cin >> n >> q >> w;
	for (int i=1; i<=n; ++i) cin >> a[i];
	build(1, 1, n);
	while (q--)
	{
		int a, b, d;
		cin >> a >> b >> d;
		update(1, 1, n, a, b, d);
		int res = 0, p = 1, u = w, k = tr[1].x; // 整个序列的和
		int i = 1; // p 是当前翻了几倍
		while (u > 0) // 暴力删
		{
			if (u > p * k) // 能删整个序列就删掉
			{
				u -= p * k;
				res += n;
				p *= 2;
			}
			else // 否则线段树二分
			{
				res += qry(1, 1, n, u, p) - 1; // 致命伤不算，所以 -1
				break;
			}
		}
		cout << res << endl;
	}
	return 0;
}



```

---

## 作者：许多 (赞：0)

非常明显的一道线段树二分题。

每场战斗前的强化就相当于区间加操作。

我们先对整个区间进行整体操作，计算 youyou 被所有垃圾桶攻击一遍后剩余血量，并用 $k$ 记录当前垃圾桶攻击力翻了多少倍。

当 youyou 的血量不足以支撑被全部垃圾桶攻击时，直接在线段树上二分，查找最多还能被攻击几次。

细节看代码。

# CODE

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define LL long long 
#define N 222222 
#define pushup(now) sum[now]=sum[now<<1]+sum[now<<1|1]
inline LL read(){
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
using namespace std;
LL n,q,W;
LL sum[N<<2],add[N<<2];
void build(LL l,LL r,LL now){
    if(l==r){
        sum[now]=read();
        return ;
    }
    LL mid=l+r>>1;
    build(l,mid,now<<1);build(mid+1,r,now<<1|1);
    pushup(now);
    return ;
}
void Add(LL l,LL r,LL now,LL v){
    sum[now]+=(r-l+1)*v;
    add[now]+=v;
    return ;
}
void pushdown(LL l,LL r,LL now){
    if(!add[now])return ;
    LL mid=l+r>>1;
    Add(l,mid,now<<1,add[now]);
    Add(mid+1,r,now<<1|1,add[now]);
    add[now]=0;
    return ;
}
void modify(LL l,LL r,LL now,LL x,LL y,LL v){
    if(l>=x&&r<=y)return Add(l,r,now,v);
    LL mid=l+r>>1;
    pushdown(l,r,now);
    if(x<=mid)modify(l,mid,now<<1,x,y,v);
    if(y>mid)modify(mid+1,r,now<<1|1,x,y,v);
    pushup(now);
    return ;
}
int main(){
    // freopen("wxyt4.in","r",stdin);
    // freopen("wxyt.out","w",stdout);
    n=read();q=read();W=read();
    build(1,n,1);
    while(q--){
        LL l=read(),r=read(),d=read(),w=W,ans=0,now=1,k=1;
        modify(1,n,1,l,r,d);
        while(w>sum[1]*k){
            w-=sum[1]*k;
            ans+=n;
            k<<=1;
        }
        //以下为线段树二分
        l=1,r=n;
        while(l!=r){
            LL mid=l+r>>1;
            pushdown(l,r,now);//注意在此处下传懒标记
            if(sum[now<<1]*k<w)ans+=mid-l+1,w-=sum[now<<1]*k,l=mid+1,now=now<<1|1;
            else r=mid,now<<=1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/P11217)

一套思路下来还是挺清晰的吧？不用怎么动脑的签到题，就是写。

先抛开那个区间加的问题不看，我们研究一下查询。

容易想到，我们应该先关系整个的 $[1,n]$ 操作了多少次，也就是“重复循环”的次数。

记当前 $[1,n]$ 和为 $s$，显然观察到 $s$ 我们可以提出来，然后因为是翻倍，所以 $s$ 前面的系数就是 $1,2,4,...,2^n$ 的东西。做一遍前缀和，我们就得出了循环了 $x$ 次的系数 $S_x$。

因为 $a_i>0$，所以这个和显然具有单调性，我们直接二分就可以计算出来。

然后是计算剩余的血量还能打多少个垃圾桶。还是根据和有单调性，我们去二分这个位置 $x$，查询 $[1,x]$ 的和即可，这样做是两只 $\log$ 的，肯定过不了。

但是二分加上线段树查询前缀和的这种，应该挺常见的吧，直接线段树二分就可以优化掉，因为我们显然可以 $O(1)$ 决策往左还是往右走。

注意计算剩余这里，应该注意要乘上对应的系数。

因为“致命伤害”不能计算到答案里面，所以还要分类讨论一下。。。

所以我们现在只用维护区间和，所以这样看来，这个区间加就是平凡的了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =2e6+10;
#define int long long 
struct node{
	int sum,lzy;
}d[N];
int n,q,W,a[N],tot;
__int128 S[N],Dus[N],lst,Sum;
void push_down(int s,int mid,int t,int p){
	d[p<<1].sum+=(mid-s+1)*d[p].lzy,d[p<<1|1].sum+=(t-mid)*d[p].lzy;
	d[p<<1].lzy+=d[p].lzy,d[p<<1|1].lzy+=d[p].lzy;	
	d[p].lzy=0;
}
void build(int s,int t,int p){
	if(s==t){
		d[p].sum=a[s];
		return ;
	}
	int mid=(s+t)>>1;
	build(s,mid,p<<1),build(mid+1,t,p<<1|1);
	d[p].sum=d[p<<1].sum+d[p<<1|1].sum;
}
void update(int l,int r,int s,int t,int p,int ch){
	if(l<=s&&t<=r){
		d[p].sum+=(t-s+1)*ch,d[p].lzy+=ch;
		return ;
	}
	int mid=(s+t)>>1; push_down(s,mid,t,p);
	if(l<=mid)	update(l,r,s,mid,p<<1,ch);
	if(r>mid)	update(l,r,mid+1,t,p<<1|1,ch);
	d[p].sum=d[p<<1].sum+d[p<<1|1].sum;
}
void Query(int s,int t,int p,int Lst,int Xi){
	int mid=(s+t)>>1; push_down(s,mid,t,p);
	if(s==t){
		if(d[p].sum*Xi>=Lst)	tot+=s-1;
		else	tot+=s;
		return ;	 
	}
	if((t-s+1)==2){
		if(d[p<<1].sum*Xi>=Lst)	tot+=s-1;
		else if(d[p].sum*Xi==Lst)	 tot+=t-1;
		else if(Lst>d[p].sum*Xi)	tot+=t;
		else	tot+=t-1;
		return ;
	}
	if(d[p<<1].sum*Xi>=Lst)	Query(s,mid,p<<1,Lst,Xi);
	else	Query(mid+1,t,p<<1|1,Lst-(d[p<<1].sum*Xi),Xi);
} 
int Slove_First(){
	int l=-1,r=61;
	while(l+1<r){
		int mid=(l+r)>>1;
		__int128 S1=S[mid]*(__int128)(Sum);
		if(S1>=W)	r=mid;
		else	l=mid;
	}
	return l;	
}
inline int read(){
	char c; c=getchar();
	int sum1=0;
	while(c<'0'||c>'9')	c=getchar();
	while(c>='0'&&c<='9')	sum1=sum1*10+(c-'0'),c=getchar();
	return sum1;
}
signed main(){
//	freopen("wxyt4.in","r",stdin);
//	freopen("ans.out","w",stdout);
	n=read(),q=read(),W=read();
	for(int i=1;i<=n;i++)	a[i]=read(),Sum+=a[i];
	for(__int128 i=1,j=1;i<=1e18;j++)	S[j]=S[j-1]+i,Dus[j]=i,i*=2;
	build(1,n,1);
//	cout<<(long long)Sum<<endl;
	while(q--){
		int l,r,d;
		l=read(),r=read(),d=read();
		update(l,r,1,n,1,d);
		
		Sum+=d*(r-l+1); 
//		if(pll==2)	cout<<(long long)Sum<<endl;
		int prenum=Slove_First();	

		lst=W-Sum*S[prenum],tot=prenum*n;
		
//		if(pll==1)cout<<prenum<<endl;
//		if(pll==1)	cout<<(long long)lst<<" "<<(long long)tot<<endl;
		Query(1,n,1,lst,Dus[prenum]*2);
		printf("%lld\n",tot);
	}	
	return 0;
} 
/*
6 1 46
9 1 4 5 1 4
1 1 1
*/
```

---

## 作者：sansesantongshun (赞：0)

这题在本次比赛中还是很简单的，按照题意模拟即可。

看这个操作，区间修改，区间查询，显然想到线段树。

具体做法是：对于每一次战斗，计算出所有垃圾桶的总攻击力，将血量减去这个数值，再将总攻击力乘 $2$，直到血量小于等于总攻击力为止。这一部分时间复杂度是 $O(\log n)$ 的。

然后二分前多少个垃圾桶的总攻击力小于现在的血量，将上一步统计出的答案加上这个数值就是最终答案，这一部分时间复杂度是 $O(\log^2 n)$ 的。

总时间复杂度为 $O(n\log^2 n)$，可以通过此题。由于 $m$ 比较大，可以把线段树换为常数更小的超级树状数组。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,y=0,z,l,mid,r,ans;
long long m,a[2][200005],num,sum,aans;
char qgetchar()
{
    static char buf[1048576],*p1,*p2;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,1048576,stdin),p1==p2)?EOF:*p1++;
}
long long read()
{
	long long result=0;
	char ch=qgetchar();
	while (ch<'0' || ch>'9')
	ch=qgetchar();
	while ('0'<=ch && ch<='9')
	{
		result=result*10+(ch^48);
		ch=qgetchar();
	}
	return result;
}
void write(long long x)
{
    if (x>=10)
    write(x/10);
    putchar(x%10|48);
}//快读快写
void gai(bool k,int x,long long y)
{
	while (x<=n)
	{
		a[k][x]+=y;
		x+=x&-x;
	}
}
long long cal(bool k,int x)
{
	long long result=0;
	while (x)
	{
		result+=a[k][x];
		x-=x&-x;
	}
	return result;
}
void modify(int l,int r,int x)
{
	gai(0,l,x);
	gai(0,r+1,-x);
	gai(1,l,(long long)(l-1)*x);
	gai(1,r+1,-(long long)r*x);
}
long long query(int x)
{
	return x*cal(0,x)-cal(1,x);
}//超级树状数组
int main()
{
	n=read();
	q=read();
    m=read();
	for (int i=1;i<=n;++i)
	{
		x=read();
		gai(0,i,x-y);
		gai(1,i,(long long)(i-1)*(x-y));
		y=x;
	}//初始化
	while (q--)
	{
		x=read();
		y=read();
		z=read();
		modify(x,y,z);
		num=query(n);
		sum=m;
		aans=0;
		x=0;
		while (sum>num<<x)
		{
			sum-=num<<x;
			aans+=n;
			++x;
		}//整的
		l=1;
		r=n-1;
		ans=0;
		while (l<=r)
		{
			mid=l+r>>1;
			if (query(mid)<<x<sum)
			{
				ans=mid;
				l=mid+1;
			}
			else
			r=mid-1;
		}//散的，二分
		write(aans+ans);
		putchar('\n');
	}
}
```

---

## 作者：Night_sea_64 (赞：0)

首先因为每次攻击完伤害翻倍，所以可以知道被攻击的次数不超过 $O(n\log w)$。$w$ 是值域。

于是可以先暴力枚举，求被攻击了多少轮（攻击一轮就是 $1\sim n$ 依次攻击一次）。

然后就是求剩下的血量可以抵挡住几次攻击，相当于一个前缀和 lower_bound。这个操作再加上区间加都可以在线段树上 $O(\log n)$ 完成。

关于线段树上求前缀和的 lower_bound，步骤如下：

- 叶子结点返回它自己即可。
- 其他结点，如果查询的值大于等于它的左区间和，就将查询的值减去左区间和，进入右区间递归。
- 否则进入左区间递归。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#define lowbit(x) x&-x
#define int long long
using namespace std;
int n,q,m,b[200010],ans,s;
struct segtree{int l,r,sum,lazy;}a[800010];
void pushup(int x){
    a[x].sum=a[x*2].sum+a[x*2+1].sum;
}
void build(int x,int l,int r)
{
    a[x].l=l,a[x].r=r;
    if(l==r)
    {
        a[x].sum=b[l];
        return;
    }
    int mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    pushup(x);
}
void pushdown(int x)
{
    a[x*2].lazy+=a[x].lazy,a[x*2].sum+=(a[x*2].r-a[x*2].l+1)*a[x].lazy;
    a[x*2+1].lazy+=a[x].lazy,a[x*2+1].sum+=(a[x*2+1].r-a[x*2+1].l+1)*a[x].lazy;
    a[x].lazy=0;
}
void add(int x,int l,int r,int k)
{
    if(a[x].l==l&&a[x].r==r)
    {
        a[x].sum+=(a[x].r-a[x].l+1)*k;
        a[x].lazy+=k;
        return;
    }
    pushdown(x);
    int mid=(a[x].l+a[x].r)/2;
    if(l<=mid)add(x*2,l,min(r,mid),k);
    if(r>mid)add(x*2+1,max(l,mid+1),r,k);
    pushup(x);
}
int query(int x,int k)
{
    if(a[x].l==a[x].r)
    {
        if(k)return a[x].l;
        else return a[x].l-1;
    }
    pushdown(x);
    int mid=(a[x].l+a[x].r)/2;
    if(k>=a[x*2].sum)return query(x*2+1,k-a[x*2].sum);
    else return query(x*2,k);
}
signed main()
{
    scanf("%lld%lld%lld",&n,&q,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&b[i]);
        s+=b[i];
    }
    build(1,1,n);
    while(q--)
    {
        int l,r,x;
        scanf("%lld%lld%lld",&l,&r,&x);
        add(1,l,r,x);
        s+=(r-l+1)*x;
        int p=0,k=m;
        int ss=s;
        while(k>=ss)p++,k-=ss,ss*=2;
        printf("%lld\n",p*n+query(1,k/(1ll<<p))-1);
    }
    return 0;
}
```

---

## 作者：Walter_Fang (赞：0)

### 前言
这题卡人的地方很多，做法是线段树加二分。

听说标程时间复杂度线性，期待住了。
### 解析
读完题再结合数据范围即可发现每个垃圾桶的伤害数组要用线段树或树状数组维护。这里我开了一个线段树。然后计算每场战斗的评分就需要二分了。我们二分查找一个尽可能大的位置 $p$ 使得 $s\times2^p\leq W$，其中 $s$ 表示当前这轮战斗每个垃圾桶的伤害总和。得出 $p$ 之后的输出直接调用线段树即可。注意若伤害刚好等于 $W$ 时要加个特判。
### 几个坑点
 - $1$ 要写成 `unsigned long long` 类型不然会炸掉 $10$ 分。
 - 要写快读不然实测 $2$ 秒的程序会跑到 $10$ 秒。
### 代码
写的有点丑了。
```cpp
#include<bits/stdc++.h>
#define ls p<<1ull
#define rs p<<1ull|1ull
namespace FastIO{
	char *p1,*p2,buf[1<<14];
	#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,(1<<14),stdin),p1==p2)?EOF:*p1++)
	template <typename T>
	inline void read(T& x){
    	x=0;
    	register int t=1;
    	register char ch=getchar();
    	while(ch<'0'||ch>'9'){
        	if(ch=='-')t=-1;
        	ch=getchar();
    	}
    	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    	x*=t;
	}
	template <typename T>
	void write(T x){
    	if(x<0)putchar('-'),x=-x;
    	if(x>9)write(x/10);
    	putchar(x%10^48);
	}
	template <typename T>
	inline void writeln(T x,char sep='\n'){
		write(x);putchar(sep);
	}
}
using namespace FastIO;
using namespace std;
typedef long long ll;
const ll N=2e5+10;
ll n,q,W,s,i,p,l,r,k,mid,a[N];
struct info{ll s,id,tag;}tr[N<<2];
void Build(ll p,ll l,ll r){
    if(l==r)return tr[p].s=a[l],tr[p].id=l,void();
    ll mid=(l+r)>>1ull;
    Build(ls,l,mid);Build(rs,mid+1ull,r);
    tr[p].s=tr[ls].s+tr[rs].s;
}
void Pushdown(ll p,ll l,ll r){
    ll mid=(l+r)>>1ull;
    if(tr[p].tag)tr[ls].s+=tr[p].tag*(mid-l+1ull),tr[rs].s+=tr[p].tag*(r-mid),tr[ls].tag+=tr[p].tag,tr[rs].tag+=tr[p].tag,tr[p].tag=0;
}
void change(ll p,ll l,ll r,ll L,ll R,ll k){
    if(L<=l&&R>=r)return tr[p].tag+=k,tr[p].s+=(r-l+1ull)*k,void();
    Pushdown(p,l,r);
    ll mid=(l+r)>>1ull;
    if(L<=mid)change(ls,l,mid,L,R,k);
    if(R>mid)change(rs,mid+1ull,r,L,R,k);
    tr[p].s=tr[ls].s+tr[rs].s;
}
ll Query(ll p,ll l,ll r,ll k,ll now){
    if(tr[p].id) return tr[p].id;
    Pushdown(p,l,r);
    ll mid=(l+r)>>1ull;
    if(tr[ls].s*k>=now)return Query(ls,l,mid,k,now);
    return Query(rs,mid+1ull,r,k,now-tr[ls].s*k);
}
int main(){
    cin>>n>>q>>W;
    for(i=1ull;i<=n;i++)read(a[i]),s+=a[i];
    Build(1ull,1ull,n);
    while(q--){
        read(l);read(r);read(k);p=0;
        change(1ull,1ull,n,l,r,k);
        s+=(r-l+1ull)*k;
        l=1ull;r=log2(W/s);
        while(l<=r){
            mid=(l+r)>>1ull;
            if((((1ull<<mid+1ull)-1ull)*s)<=W)p=max(p,mid),l=mid+1ull;
            else r=mid-1ull;
        }
        if((((1ull<<p+1ull)-1ull)*s)==W)write(n*(p+1ull)-1ull),putchar('\n');
        else write(Query(1ull,1ull,n,(1ull<<p+1ull),W-(((1ull<<p+1ull)-1ull)*s))+n*(p+1ull)-1ull),putchar('\n');
    }
}
```

---

## 作者：菲斯斯夫斯基 (赞：0)

简单数据结构题，但是为啥要放在 CSP-S 模拟赛第一题？？？？赛时写了 $\mathcal O(q\log^2 n)$ 的还被卡了。

首先修改部分直接上线段树就好了，没什么好说的。

然后因为每次打完 $a_i$ 都会翻倍，做多了题你就会发现每个垃圾桶最多攻击 $\log$ 次就会大于 $w$ 了。

预处理出所有的和，可以暴力求出 $n$ 个垃圾桶**都**攻击了多少次，记为 $cnt$ 次。

剩下就是要找到最大的 $x$ 使得 $\sum \limits _{i=1}^{x}a'_i<w'$，注意这里的 $w'$ 和 $a'_i$ 都是做完 $cnt$ 次后新的 $a_i$ 和 $w$。

最后上面那个式子显然是可以二分的，树状数组或者线段树可以 $\mathcal O(q\log^2 n)$ 解决，但是线段树常数实在太大了，只能得到 70 pts。在线段树上二分能优化到 $\mathcal O(q\log n)$。

代码实现基本没有什么细节。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,m,w,sum;
int a[N];
struct ccf
{
	int len,la,x;
}f[N];
void pushdown(int k)
{
	if(!f[k].la)return ;
	int &x=f[k].la,l=k*2,r=k*2+1;
	f[l].x+=f[l].len*x,f[l].la+=x;
	f[r].x+=f[r].len*x,f[r].la+=x;
	x=0;
}
void build(int k,int l,int r)
{
	f[k].len=r-l+1;
	if(l==r)return f[k].x=a[l],void();
	int mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	f[k].x=f[k*2].x+f[k*2+1].x;
}
void add(int k,int l,int r,int x,int y,int z)
{
	if(x<=l&&r<=y)return f[k].x+=f[k].len*z,f[k].la+=z,void();
	pushdown(k);
	int mid=(l+r)/2;
	if(x<=mid)add(k*2,l,mid,x,y,z);
	if(y>mid)add(k*2+1,mid+1,r,x,y,z);
	f[k].x=f[k*2].x+f[k*2+1].x;
}
int ask(int k,int l,int r,int z,int w)
{
	if(l==r)return l-1;
	pushdown(k);
	int mid=(l+r)/2,s=f[k*2].x;
	assert(f[k].x*z>=w);
	if((__int128)s*z>=w)return ask(k*2,l,mid,z,w);
	return ask(k*2+1,mid+1,r,z,w-s*z);
}
int solve(int w)
{
	int cnt=0,s=sum;
	while(w>s)
		w-=s,s*=2,cnt++;
	assert(f[1].x*(1ll<<cnt)>=w);
	return cnt*n+ask(1,1,n,1ll<<cnt,w);
}
signed main()
{
	cin>>n>>m>>w;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),sum+=a[i];
	build(1,1,n);
	while(m--)
	{
		int l,r,k;
		scanf("%lld%lld%lld",&l,&r,&k);
		sum+=(r-l+1)*k;
		add(1,1,n,l,r,k);
		printf("%lld\n",solve(w));
	}
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

考虑到这个游戏只会进行 $O(\log V)$ 场战斗，我们就枚举这个轮数，直到再进行一场战斗 youyou 就死了。

接下来要看还能玩几轮。接下来显然是一个前缀的垃圾桶来打 youyou。

如果你二分前缀的长度并且求前缀和，这样的复杂度是 $O(q \log ^ 2 n)$。如果你写线段树很有可能 T。

发现这个二分过程和前缀和其实可以一起在线段树上进行。所以线段树二分就可以了。

```cpp
const int N = 1000010;
int n, q, W;
int s[N], a[N], tag[N], len[N];
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid (l + r >> 1)
#define lb ls, l, mid
#define rb rs, mid + 1, r
inline void up(int u) { s[u] = s[ls] + s[rs]; }
inline void push(int u, int v) { tag[u] += v, s[u] += len[u] * v; }
inline void down(int u) { if (tag[u]) push(ls, tag[u]), push(rs, tag[u]); tag[u] = 0; }
void build(int u, int l, int r) {
	len[u] = r - l + 1;
	if (l == r) { s[u] = a[l]; return; }
	build(lb); build(rb); up(u);
}
void chg(int u, int l, int r, int L, int R, int v) {
	if (l > R or L > r) return;
	if (l >= L and r <= R) return push(u, v), void();
	down(u); chg(lb, L, R, v), chg(rb, L, R, v); up(u);
}
int solve(int u, int l, int r, int W, int k) {
	if (l == r) return 0; down(u);
	int o = s[ls] * (1ll << k);
	if (o >= W) return solve(lb, W, k);
	else return len[ls] + solve(rb, W - o, k);
}
signed main() {
	read(n, q, W);
	rep(i, 1, n) read(a[i]); 
	build(1, 1, n);
	int sum = 0; rep(i, 1, n) sum += a[i];
	while (q -- ) {
		int tmp = W;
		int l, r, d; read(l, r, d);
		chg(1, 1, n, l, r, d);
		sum += (r - l + 1) * d;
		int ans = 0, t = sum, k = 0;
		while (tmp > t) tmp -= t, ans += n, t *= 2, k ++ ;
		ans += solve(1, 1, n, tmp, k);
		write('\n', ans);
	} return 0;
}
```

---

## 作者：modfish_ (赞：0)

## 思路
首先区间修改可以用线段树实现。然后，记当前所有元素之和为 $s$。

假设垃圾桶总共进行了 $k$ 轮整的攻击，那么应有：

$$\sum_{i=1}^n\sum_{j=1}^ka_i\times 2^{j-1}\le W$$

也就是：

$$s\times\sum_{j=0}^{k-1}2^j=(2^k-1)s\le W$$

可以化成：

$$k\le\log_2(\frac{W}{s}+1)$$

取最大的 $k$，即：

$$k=\lfloor\log_2(\frac{W}{s}+1)\rfloor$$

接下来考虑计算还要进行几次攻击才能打倒。设之后进行了 $r$ 次攻击，则：

$$(2^k-1)s+\sum_{i=1}^ra_i\times 2^k\ge W$$

即：

$$\sum_{i=1}^ra_i\ge\frac{W-(2^k-1)s}{2^k}$$

因为左边是整数，故可以将右边向上取整：

$$\sum_{i=1}^ra_i\ge\lceil\frac{W-(2^k-1)s}{2^k}\rceil$$

在线段书上二分出 $r$ 即可。答案为 $kn+r-1$。

时间复杂度 $O(n(\log n+\log V))$。其中 $V$ 为值域。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 2e5 + 5;

ll a[maxn];

namespace seg{
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
ll sum[maxn << 2], tag[maxn << 2], len[maxn << 2];
void up(int x){
	sum[x] = sum[l(x)] + sum[r(x)];
}
void down(int x){
	tag[l(x)] += tag[x], sum[l(x)] += tag[x] * len[l(x)];
	tag[r(x)] += tag[x], sum[r(x)] += tag[x] * len[r(x)];
	tag[x] = 0;
}
void build(int x, int l, int r){
	len[x] = r - l + 1;
	if(l == r){
		sum[x] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(l(x), l, mid), build(r(x), mid + 1, r);
	up(x);
}
void update(int x, int l, int r, int ql, int qr, ll k){
	if(ql <= l && r <= qr){
		sum[x] += k * len[x], tag[x] += k;
		return;
	}
	down(x);
	int mid = l + r >> 1;
	if(ql <= mid) update(l(x), l, mid, ql, qr, k);
	if(qr > mid) update(r(x), mid + 1, r, ql, qr, k);
	up(x);
}
ll query(int x, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr) return sum[x];
	down(x);
	int mid = l + r >> 1;
	ll res = 0;
	if(ql <= mid) res += query(l(x), l, mid, ql, qr);
	if(qr > mid) res += query(r(x), mid + 1, r, ql, qr);
	return res;
}
int query2(int x, int l, int r, ll k){
	if(k == 0) return 0;
	if(l == r) return l;
	down(x);
	int mid = l + r >> 1;
	if(sum[l(x)] >= k) return query2(l(x), l, mid, k);
	else return query2(r(x), mid + 1, r, k - sum[l(x)]);
}}
ll qpow(ll a, ll x){
	ll res = 1;
	while(x){
		if(x & 1) res *= a;
		a *= a;
		x >>= 1;
	}
	return res;
}

int main(){
	int n, q;
	ll W;
	scanf("%d %d %lld", &n, &q, &W);
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	seg::build(1, 1, n);
	while(q --){
		int l, r;
		ll d;
		scanf("%d %d %lld", &l, &r, &d);
		seg::update(1, 1, n, l, r, d);
		ll sum = seg::query(1, 1, n, 1, n), rnd = logl(1.0 * W / sum + 1) / logl(2), po = qpow(2, rnd);
		ll now = (po - 1) * sum;
		ll rst = seg::query2(1, 1, n, (W - now - 1) / po + 1);
		printf("%lld\n", rnd * n + rst - 1);
	}
	return 0;
}
```

---

