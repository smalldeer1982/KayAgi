# [NEERC 2013] Kabaleo Lite

## 题目描述

有一种棋盘游戏：棋盘上有 $n$ 个格子，每个格子上可以堆叠若干个有颜色的筹码，只有每个格子中最上方的筹码的颜色是可见的。

参加游戏的每个玩家都有各自不同的一个目标颜色，以及一些彩色筹码。每个人只知道自己的目标颜色，但各自拥有的筹码颜色和数量都是公开的。每个回合中，所有玩家轮流在棋盘上选一个格子放置筹码，同时覆盖下方的筹码。游戏结束后，数出棋盘上可见筹码数最多的颜色，以该颜色为目标颜色的玩家即获胜。若该颜色不是任何玩家的目标颜色，或者棋盘上出现最多的颜色不唯一，则游戏平局。

现在，一局游戏进行到了最后，你和其他所有玩家都只剩最后一个筹码。现在恰好轮到你操作，在不知道其他人的目标颜色的前提下，你想知道你一共有哪些操作可以保证必胜。

## 样例 #1

### 输入

```
6 3 4 2
2 1 2 3 2 2
2 1 1
```

### 输出

```
1
2
```

# 题解

## 作者：极寒神冰 (赞：2)

先考虑每次直接判断每个 $j$ 是否可行。

已经有 $b_j=l_1$，剩下的 $p-1$ 个人进行操作，可以假设这 $p-1$ 个人联合对抗你，然后就有一个显然的策略：

不管 $l_i$ 是否等于 $h_1$，总是会优先选择一个等于 $h_1$ 的数将其覆盖，然后尽量让某个 $\neq h_1$ 的数出现尽可能多。

因此需要考虑 $h_1$ 至少有几个：

设原先有 $x$ 个 $h_1$，$l_i,i\in [2,p]$ 中有 $y$ 个不等于 $h_1$ 的数，则一个显然的下界是 $\max(x-y,0)$。

特别的，当 $l_p=h_1$ 时需要对 $1$ 取 $\max$。记 $h_1$ 至少有 $N=\max(x-y,[l_p=h_1])$。

然后要考虑其他数最多能出现多少次：

对于每个数 $a\ne h_1$，统计出 $a$ 在 $b$ 中的出现次数 $p_a$，以及在 $l_i,i\in [2,p]$ 中的出现次数 $q_a$。显然 $a$ 最后最多出现 $M=\max\limits_{a\ne h_1}(p_a+q_a)$。

显然如果 $N>M$，则你是必胜的。但如果 $N\le M$，是否有可能必胜呢？

事实上，当且仅当 $n=1,l_p=h_1$ 此时有 $N=M=1$ 你才是必胜的，否则只要其他人联合起来就一定可以让 $h_1$ 出现 $N$ 次，$a$ 出现 $M$ 次。

这样直接做的时间复杂度是 $\mathcal O(n^2)$。

考虑优化，发现对于不同的 $j$，大部分的量都是相同，除了两部分：

1. 首先就是 $x$ 会发生 $\pm 1$ 的变化，而 $y$ 不变，$N$ 仍然可以快速得到。
  
2. 原先 $b_j$ 出现次数会 $-1$，$l_1$ 的出现次数会 $+1$。
  
  若 $l_1\ne h_1$，则 $p_{l_1}+q_{l_1}$ 会比原先 $+1$，需要单独判断。
  
  对于 $b_j$ 出现次数 $-1$，可以预处理出是否有其他的 $a$ 与 $b_j$ 有相同或更大的值。
  
  同样也可以快速得到。
  

时间复杂度 $\mathcal O(n+c)$。

```cpp
#include<bits/stdc++.h>
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
using namespace std;
int n,p,c,h;
int b[1111111],cnt[1111111];
int l[1111111];
vector<int>ans;
int mx,mmx,cy;
inline int check(int x)
{	
	if(n==1&&l[p]==h) return 1;
	--cnt[b[x]];
	++cnt[l[1]];
	int del=cnt[h]-cy;
	bool ok=1;
	if(del<=0) ok=0;
	if(cnt[mx]>=del) ok=0;
	if(cnt[mmx]>=del) ok=0;
	if(l[1]!=h&&cnt[l[1]]>=del) ok=0;
	++cnt[b[x]];
	--cnt[l[1]];
	return ok;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>p>>c>>h;
	R(i,1,n) cin>>b[i],++cnt[b[i]];
	R(i,1,p) cin>>l[i];
	R(i,2,p) if(l[i]!=h) ++cy,++cnt[l[i]];
	//cout<<cy<<endl;
	R(i,1,c) if(i!=h) 
	{
		if(cnt[i]>cnt[mx]) mmx=mx,mx=i;
		else if(cnt[i]>cnt[mmx]) mmx=i;
	}  
	R(i,1,n) if(check(i)) ans.emplace_back(i);
	cout<<ans.size()<<endl;
	for(int x:ans) cout<<x<<' ';
	cout<<endl;
}
```

---

## 作者：Lacuna (赞：1)

### 前言：

主播体育考试坠机了，心情~~大好~~失落，写篇题解安慰下自己。

### 思路：

若有必胜策略，显然即使所有人都针对你，你都能比别人多。所以统计一下别的人可以覆盖你的次数，设这个次数是 $sum$，当前除你外最多的数的个数是 $maxn$，你当前的个数是 $cnt$，容易得到 $sum = \sum_{\substack{l[i] \neq h}}$，那么我们就要满足 $cnt - sum > maxn$。

由于没有数据范围，主播到这里参考了一下另外两篇题解的写法，并没有很好的理解，在网上找到一个用线段树的。遂用线段树实现。

我们要统计一种筹码现有的个数，容易表示为 $cnt_{现有} + cnt_{手上}$，现有就是棋盘上已经有的，手上就是玩家手中的，在代码中分别对应 $cnt$ 和 $cnt2$。

这个区间最大值用线段树维护，只要支持单点修改，根节点的查询，比板子还弱，初始化为 $cnt + cnt2$，由于我们只统计除自己外的数，所以特判掉自身的情况。

我们枚举每个位置的情况，修改用线段树单点修改，更新 $cnt$ 的值，看看满不满足上面的条件就行，记得每次循环后要恢复。

初始要特判 $n = 1$ 的情况，发现此时最后的筹码颜色就是最后一个人手上的。此时看看最后一个人的筹码颜色就行。主播测试了一下，不加会挂掉，不知道是什么原因。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define gc getchar
#define pb push_back
#define ls u<<1
#define rs u<<1|1
template<typename T>inline void read(T&x){x=0;int f=1;char ch=gc();while(!isdigit(ch)){if(ch=='-') f=-1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=gc();}x*=f;}
template<typename T,typename ...T1>inline void read(T&x,T1&...x1){read(x);read(x1...);}
const int ri=1e6+5;
vector<int> ans;
int n,p,c,h,cnt[ri],cnt2[ri],maxn[ri<<1],sum;
void pushup(int u){
	maxn[u]=max(maxn[ls],maxn[rs]);
}
void build(int u,int l,int r){
	if(l==r){
	  if(l!=h) maxn[u]=cnt[l]+cnt2[l];
	  return;
    }
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(u);
}
void change(int u,int l,int r,int pos,int x){
	if(l==r){
	  maxn[u]+=x; return;
	}
	int mid=l+r>>1;
	if(pos<=mid) change(ls,l,mid,pos,x);
	else change(rs,mid+1,r,pos,x);
	pushup(u);
}
int main(){
	read(n,p,c,h);
	vector<int> b(n+1),l(p+1);
	for(int i=1;i<=n;i++){
	  read(b[i]); cnt[b[i]]++;
	}
	for(int i=1;i<=p;i++){
	  read(l[i]); cnt2[l[i]]++;
	  if(l[i]!=h) sum++;
    }
    if(n==1){
      if(l[p]==h) puts("1"),puts("1");
      else puts("0");
      exit(0);
	} 
	build(1,1,c);
	for(int i=1;i<=n;i++){
	  change(1,1,c,b[i],-1); 
	  cnt[b[i]]--; cnt[h]++;
	  if(maxn[1]<cnt[h]-sum) ans.pb(i);
	  change(1,1,c,b[i],1);
	  cnt[b[i]]++; cnt[h]--;
	}
	printf("%d\n",ans.size());
	for(int i:ans) printf("%d\n",i);
    return 0;
}
```

是不是，即使所有人都针对你，你还是最后的赢家。

---

## 作者：XIxii (赞：0)

## P7006 [NEERC2013] Kabaleo Lite

  当 $n=1$ 时特判，只有当最后玩家的棋子和一号玩家的胜利棋子是相同的，一号玩家才能取胜。

  剩下的，我们可以看到对于非一号玩家的胜利棋子的棋子，他的任务就是尽量覆盖一号玩家的胜利棋子，而对于和一号玩家的胜利棋子相同的棋子在最坏情况下会放在一个位置——自身覆盖。

  枚举一号玩家的覆盖点，计算当前的最多点的棋子数和一号玩家的胜利棋子的数目，严格小于则输出此位置。

  
```
#include <bits/stdc++.h>
using namespace std;
const int Maxn=1000005;
int s[Maxn],n,p,c,h,i,a[Maxn],b[Maxn],dig[Maxn],max1,max2,cnt,ext,ans;
bool Judge(int pos)
{
	int k=s[h]-cnt;
	if(k<=0) 
		k+=ext;
	return !(s[max1]>=k || s[max2]>=k || (b[1]!=h && s[b[1]]>=k));
}
int main(){
	
	scanf("%d%d%d%d",&n,&p,&c,&h);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		s[a[i]]++;
	}
	for (i=1,cnt=p-1;i<=p;i++)
	{
		scanf("%d",&b[i]);
		if(i>1 && b[i]!=h) 
			s[b[i]]++;
		if(i>1 && b[i]==h) 
			cnt--;
	}
	if(n==1)
	{
		if(b[p]!=h) 
			printf("0\n");
		else 
			printf("1\n1\n");
		return 0;
	}
	ext=(b[p]==h);
	for(i=1;i<=c;i++)
	{
		if (i!=h)
		{
			if (s[i]>s[max1]) 
				max2=max1, max1=i;
			else if (s[i]>s[max2]) 
				max2=i;
		}
	}
	s[b[1]]++;
	for(i=1,ans=0;i<=n;i++)
	{
		s[a[i]]--;
		if(Judge(i)) 
			dig[ans++]=i;
		s[a[i]]++;
	}
	printf("%d\n",ans);
	for(i=0;i<ans;i++)
		printf("%d\n",dig[i]);
	return 0;
}
```

---

