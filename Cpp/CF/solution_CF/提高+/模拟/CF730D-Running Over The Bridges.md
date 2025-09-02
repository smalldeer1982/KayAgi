# Running Over The Bridges

## 题目描述

Polycarp is playing a game called "Running Over The Bridges". In this game he has to run over $ n $ bridges from the left to the right. Bridges are arranged one after the other, so the $ i $ -th bridge begins where the $ (i-1) $ -th bridge ends.

You have the following data about bridges: $ l_{i} $ and $ t_{i} $ — the length of the $ i $ -th bridge and the maximum allowed time which Polycarp can spend running over the $ i $ -th bridge. Thus, if Polycarp is in the beginning of the bridge $ i $ at the time $ T $ then he has to leave it at the time $ T+t_{i} $ or earlier. It is allowed to reach the right end of a bridge exactly at the time $ T+t_{i} $ .

Polycarp can run from the left side to the right one with speed $ 0.5 $ , so he will run over a bridge with length $ s $ in time $ 2·s $ . Besides, he has several magical drinks. If he uses one drink, his speed increases twice (i.e. to value 1) for $ r $ seconds. All magical drinks are identical. Please note that Polycarp can use a drink only at integer moments of time, and he drinks it instantly and completely. Additionally, if Polycarp uses a drink at the moment $ T $ he can use the next drink not earlier than at the moment $ T+r $ .

What is the minimal number of drinks Polycarp has to use to run over all $ n $ bridges? If this number is not greater than $ 10^{5} $ , then you have to find out the moments of time when Polycarp has to use each magical drink.

## 说明/提示

In the first case, there is only one bridge and it is clear that Polycarp cannot run over it without magical drinks. So, if he will use one magical drink on start (moment of time $ 0 $ ), and the second one — three seconds later (moment of time $ 3 $ ), he will be able to reach the end of the bridge in time. Please note, in this case there are several possible answers to the problem. For example, Polycarp can use the first drink at the moment of time $ 4 $ and the second one — at the moment of time $ 7 $ .

In the second case, Polycarp cannot run over all bridges even if he will use magical drinks. So, answer in this case is -1.

In the fourth case, Polycarp can run over all bridges without magical drinks.

## 样例 #1

### 输入

```
1 3
7
10
```

### 输出

```
2
0 3
```

## 样例 #2

### 输入

```
3 3
3 3 3
3 3 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 100000
5 5 5
5 7 8
```

### 输出

```
1
0 
```

## 样例 #4

### 输入

```
4 1000
1 2 3 4
10 9 10 9
```

### 输出

```
0

```

# 题解

## 作者：_edge_ (赞：0)

一血&第一篇题解

翻译已经翻译的很清楚了，我也不多说了。 (

首先看到这种最优性的问题，一般就想到 DP 或者 贪心。

这题的状态数量基本是爆炸级别的，用 DP 好像不太可行，考虑使用贪心。

怎么贪 (?

因为它没有时间上的明确限制，所以我们对于一座桥来说，如果能不用魔液，就不用。

如果要用呢？

在这里我的数学能力不太好，所以不太会推这个柿子，所以我用二分来确定速度为 $1$ 的路程要多少。

```cpp
int solve(int x,int y) {
	int l=0,r=x,ans=-1;
	while (l<=r) {
		int Mid=(l+r)>>1;
		if ((x-Mid)*2+Mid<=y) r=(ans=Mid)-1;
		else l=Mid+1;
	}
	return ans;
}
```

确定完之后，依照我们贪心的策略，如果要用也是用的节省一点，最好能够影响到下一座桥。

那就是考虑把这些路程都安排在一个后缀，对于后面的，那就有一段前缀是速度为 $1$ 的。

那我们发现，这样贪比较符合最优性，更具体的，能卡着上限就卡着。

还有点小问题要处理，就是上回的一段前缀加上去能够不用魔液那就不用。

如果要用，也是一段前缀和一段后缀。

处理完上述问题之后，发现还有一个非常棘手的东西，就是输出方案。

那在这里可以使用一个 $time$ 来表示当前的时间，注意，我们需要在任何时候都去维护这个 $time$。

另外，题目中还有一句话：

If the solution exists and the value of k is not greater than $10^5$ then output k integers on the next line — moments of time from beginning of the game when Polycarp has to use drinks. Print the moments of time in chronological order. If there are several solutions, you can output any of them.

所以这里，我们要去特判掉方案数大于 $10^5$ 的情况。

同时，暴力 $+r$ 去寻找答案会 TLE，这里也要用点数学上的推柿子。

上述推柿子留给读者自行思考，如果还是不理解可以来找我。

```cpp
/*
贪
如果一座桥能走过去就走过去，走不过去算时间最划算的决策。 
希望人没事
*/
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=2e5+5;
const int INFN=1e7+5;
int n,r,l[INF],t[INF],ans[INFN];
int solve(int x,int y) {
	int l=0,r=x,ans=-1;
	while (l<=r) {
		int Mid=(l+r)>>1;
		if ((x-Mid)*2+Mid<=y) r=(ans=Mid)-1;
		else l=Mid+1;
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>r;
	for (int i=1;i<=n;i++) cin>>l[i];
	for (int i=1;i<=n;i++) cin>>t[i];
	int la=0,tt=0;
	for (int i=1;i<=n;i++) {
		int kk=solve(l[i],t[i]);
//		cout<<la<<" "<<tt<<" "<<kk<<" ?????\n";
		if (kk==-1) {cout<<"-1\n";return 0;}
		if (kk<=la) {
			tt+=min(l[i],la);
			tt+=max(0ll,(l[i]-la)*2);
			la=max(0ll,la-l[i]);
		}
		else {
			tt+=la;int ll=la;
			kk-=la;la=0;
			int P=l[i]-kk;tt+=(P-ll)*2;
//			cout<<tt<<" endl\n";
			
			if (ans[0]>2e5) {
				ans[0]+=(l[i]-1-P+1+r-1)/r;
				int I=(l[i]-1-P)/r*r+P; 
				tt+=min(l[i]-I,r),la=max(0ll,I+r-l[i]);
			}
			else {
				for (int I=P;I<l[i];I+=r) {
					if (ans[0]<=2e5) ans[++ans[0]]=tt;
					else ans[0]++;
					tt+=min(l[i]-I,r),la=max(0ll,I+r-l[i]);
				}
			}
		}
	}
	cout<<ans[0]<<"\n";
	if (ans[0]>1e5) return 0;
	for (int i=1;i<=ans[0];i++)
		cout<<ans[i]<<" "; 
	return 0;	
}

```


---

