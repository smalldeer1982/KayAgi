# Royal Flush

## 题目描述

Consider the following game. There is a deck, which consists of cards of $ n $ different suits. For each suit, there are $ 13 $ cards in the deck, all with different ranks (the ranks are $ 2 $ , $ 3 $ , $ 4 $ , ..., $ 10 $ , Jack, Queen, King and Ace).

Initially, the deck is shuffled randomly (all $ (13n)! $ possible orders of cards have the same probability). You draw $ 5 $ topmost cards from the deck. Then, every turn of the game, the following events happen, in the given order:

1. if the cards in your hand form a Royal Flush (a $ 10 $ , a Jack, a Queen, a King, and an Ace, all of the same suit), you win, and the game ends;
2. if you haven't won yet, and the deck is empty, you lose, and the game ends;
3. if the game hasn't ended yet, you may choose any cards from your hand (possibly, all of them) and discard them. When a card is discarded, it is removed from the game;
4. finally, you draw cards from the deck, until you have $ 5 $ cards or the deck becomes empty.

Your goal is to find a strategy that allows you to win in the minimum expected number of turns. Note that the turn when the game ends is not counted (for example, if the $ 5 $ cards you draw initially already form a Royal Flush, you win in $ 0 $ turns).

Calculate the minimum possible expected number of turns required to win the game.

## 样例 #1

### 输入

```
1```

### 输出

```
3.598290598```

## 样例 #2

### 输入

```
2```

### 输出

```
8.067171309```

# 题解

## 作者：gdf_yhm (赞：1)

### [M. Royal Flush](https://codeforces.com/contest/2038/problem/M)

[my blog](https://yhddd123.github.io/post/2024-2025-icpc-nerc-southern-and-volga-russian-regional-contest-zuo-ti-ji-lu/)

### 思路

设 $dp_{i,a}$ 表示剩 $i$ 张牌，当前 $n$ 种花色的 $[10,14]$ 各持 $a_i$ 张，$a$ 是一个降序的 vector，里面只存没有被删过的花色的降序数量。枚举各种策略取最小值，枚举扔牌之后每种牌各进多少张，算概率，记搜。

注意取一个 $a$ 的前缀转移不一定最优，例如当前 $n=2$，有 $4$ 张 $x$ 和一张 $y$，扔掉 $y$ 之后一次只能摸一张扔一张，不如扔掉 $4$ 张 $x$。策略是枚举一个子集。常数极小，60ms 以内。

### code

```cpp
int n;
map<vector<int>,db> dp[55];
map<vector<int>,bool> vis[55];
db C(int m,int n){
	if(m<n||m<0||n<0)return 0;
	db ans=1;
	for(int i=1;i<=n;i++)ans=ans*(m-i+1)/(1.0*i);
	return ans;
}
db dfs(int dep,vector<int> a){
	if(dep<=0)return -1;
	if(a.front()==5)return -1;
	if(vis[dep][a])return dp[dep][a];vis[dep][a]=1;
	vector<int> aa=a;
	db ans=inf;
	int num=0;while(a.size()&&!a.back())a.pop_back(),++num;
	vector<int> aaa=a;
	for(int s=0;s<(1<<aaa.size());s++){
		a.clear();
		for(int i=0;i<aaa.size();i++)if(s&(1<<i))a.pb(aaa[i]);
		for(int i=1;i<=num;i++)a.pb(0);
		if(!a.size())continue;
		db res=0;
		int sum=0;for(int i:a)sum+=5-i;
		int in=5;for(int i:a)in-=i;
		if(!in)continue;
		for(int i=0;i<=(a.size()>0?5-a[0]:0);i++){
			if(i)a[0]+=i;
			for(int j=0;j<=(a.size()>1?5-a[1]:0)&&i+j<=in;j++){
				if(j)a[1]+=j;
				for(int k=0;k<=(a.size()>2?5-a[2]:0)&&i+j+k<=in;k++){
					if(k)a[2]+=k;
					for(int l=0;l<=(a.size()>3?5-a[3]:0)&&i+j+k+l<=in;l++){
						if(l)a[3]+=l;
						vector<int> aaaa=a;
						db val=C((a.size()>0?5-a[0]+i:0),i)*C((a.size()>1?5-a[1]+j:0),j)*C((a.size()>2?5-a[2]+k:0),k)*C((a.size()>3?5-a[3]+l:0),l)*C(dep-sum,in-i-j-k-l);
						val=val/C(dep,in);
						sort(a.begin(),a.end(),greater<int>());
						res+=val*(dfs(dep-in,a)+1);
						a=aaaa;
						if(l)a[3]-=l;
					}
					if(k)a[2]-=k;
				}
				if(j)a[1]-=j;
			}
			if(i)a[0]-=i;
		}
		ans=min(ans,res);
	}
	if(ans==inf)ans=-1;
	return dp[dep][aa]=ans;
}
void work(){
	n=read();
	vector<int> a(n,0);
	printf("%.9lf\n",dfs(13*n,a));
}
```

[https://codeforces.com/contest/2038/submission/292324178](https://codeforces.com/contest/2038/submission/292324178)

---

