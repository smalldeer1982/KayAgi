# Free Market

## 题目描述

John Doe has recently found a "Free Market" in his city — that is the place where you can exchange some of your possessions for other things for free.

John knows that his city has $ n $ items in total (each item is unique). You can bring any number of items to the market and exchange them for any other one. Note that each item is one of a kind and that means that you cannot exchange set $ {a,b} $ for set $ {v,a} $ . However, you can always exchange set $ x $ for any set $ y $ , unless there is item $ p $ , such that $ p $ occurs in $ x $ and $ p $ occurs in $ y $ .

For each item, John knows its value $ c_{i} $ . John's sense of justice doesn't let him exchange a set of items $ x $ for a set of items $ y $ , if $ s(x)+d&lt;s(y) $ ( $ s(x) $ is the total price of items in the set $ x $ ).

During one day John can exchange only one set of items for something else. Initially, he has no items. John wants to get a set of items with the maximum total price. Find the cost of such set and the minimum number of days John can get it in.

## 说明/提示

In the first sample John can act like this:

- Take the first item ( $ 1-0<=2 $ ).
- Exchange the first item for the second one ( $ 3-1<=2 $ ).
- Take the first item ( $ 1-0<=2 $ ).

## 样例 #1

### 输入

```
3 2
1 3 10
```

### 输出

```
4 3
```

## 样例 #2

### 输入

```
3 5
1 2 3
```

### 输出

```
6 2
```

## 样例 #3

### 输入

```
10 10000
10000 9999 1 10000 10000 10000 1 2 3 4
```

### 输出

```
50010 6
```

# 题解

## 作者：Bitter_Tea (赞：4)

基本思路是**贪心+$01$背包**

显然，我们能换到的物品的$cost$越大是越优的，因为这样我们后面能换的范围也就越大，天数自然会缩短。

假设我们当前手上的物品的总价值为$cost_1$，那么由题意可知我们可以兑换的物品的最大价值$cost_2=cost_1+d$。

于是乎我们有了暴力思路，每次以$cost_1+d$为最大体积跑$01$背包，检验是否有最大价值的更新，如果没有就说明上一天就是我们期望答案。

代码就像这样:
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,d,c[55];
int maxn,t,last_maxn;
bool f[500005];
bool solve()
{
	memset(f,0,sizeof(f));
	f[0]=1;
	last_maxn=maxn;
	for(int i=1;i<=n;i++)
	for(int j=d+last_maxn;j>=c[i];j--)
	{
		if(f[j-c[i]])
		{
			f[j]=1;
			maxn=max(j,maxn);
		}
	}
	if(maxn==last_maxn) return 0;
	else return 1;
}
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)
	scanf("%d",&c[i]);
	for(int i=1;;i++)
	{
		if(solve()) continue;
		printf("%d %d\n",maxn,i-1);
		return 0;
	}
}
```

然后就$TLE$了,$qwq$。

其实我们已经成功一大半了:

因为我们根本没必要每次都跑一次$01$背包，我们只需要一开始跑一次$01$背包。然后接下来我们直接从$cost_1+d$向前扫到$cost_1$,如果最大价值有更新，那么就可行，更新$cost_1$，进行下一天的兑换操作。

~~代码实现极其简单~~$qwq$

$Code$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int N=6e5+5;
int n,d,c[51];
int last_maxn,maxn;
bool f[N];
int find(int l,int r)
{
	for(int i=r;i>=l;i--)
	if(f[i]) return i;
	return l;
}
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)
	scanf("%d",&c[i]);
	f[0]=1;
	for(int i=1;i<=n;i++)
	for(int j=N;j>=c[i];j--)
	if(f[ j-c[i] ]) f[j]=1;
	for(int i=1;;i++)
	{
		last_maxn=maxn;
		maxn=find(maxn,d+last_maxn);
		if(last_maxn!=maxn) continue;
		printf("%d %d\n",maxn,i-1);
		return 0;
	}
}

```








---

## 作者：joke3579 (赞：3)

考虑贪心。

有一个比较显然的贪心策略，即每次都换取价值和最大的物品，这样能使得兑换天数最小。假设当前持有物品的价值和为 $C$，则由题意可以知道一次换取后可以持有的物品集合价值和范围为 $[C, C + d]$。

考虑如何优化贪心。

我们首先需要知道有哪些价值和能被选择，这可以通过一次 01 背包在 $O(n^2m)$ 的时间复杂度内得到。   

然后从价值和为 0 的状态开始求解答案。若当前状态为 $C$，则只需倒序扫描 $[C+1,C+d]$ 范围内的元素可及性，若存在一个价值和可以被选择，则其一定能通过当前状态兑换得到，因此更新答案继续进行即可。反之当前状态一定是兑换次数最少且价值和最大的状态，输出扫描次数及当前状态即可。

第二部分的复杂度大致是 $O(\frac {nm}d)$ 的，然而不是很会证。如果有证法或更好的上界欢迎交流。

因此总时间复杂度 $O(n^2m)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (register int i = (a), i##_ = (b) + 1; i < i##_; ++i)
#define pre(i,a,b) for (register int i = (a), i##_ = (b) - 1; i > i##_; --i)
const int N = 1e4 + 10;
int n, d, bnd, a[51];
int f[N * 51];

signed main() {
	cin >> n >> d; rep(i,1,n) cin >> a[i];
    sort(a+1, a+1+n);
    f[0] = 1; bnd = 0;
    rep(i,1,n) {
        pre(j,bnd,0) if (f[j]) f[j + a[i]] = 1;
        bnd += a[i];
    } 
    int lst, now = 0;
    rep(i,1,n<<1) {
        lst = now;
        pre(j,lst+d,lst) if (f[j]) { now = j; break; }
        if (now == lst) {
            cout << now << ' ' << i-1 << endl;
            return 0;
        }
    }
}
```


---

## 作者：bikuhiku (赞：2)


~~我倒看看是代码先不`UKE`，还是题解先通过。~~

我们考虑一个事情：一个总价值为 $a$ 的状态一定可以以一次操作的时间转移到任意一个总价值介于 $a+1$ 与 $a+d$ 之间的状态（闭区间）。因为除去两者相同的部分后，价值差不变。

所以我们每次向一个可以达到的价值最大的的状态转移就好了。

所有可以达到的状态从一开始跑一遍01背包。

时间主要花费在01背包上，时间复杂度 $\mathcal{O}(nm^2)$。（$m$ 表示单个物品价值的值域）

[AC代码](https://codeforces.com/contest/364/submission/177617412)


---

## 作者：SMTwy (赞：1)

大概解释一下其它题解所说的贪心，只考虑总价值而不考虑具体物品为什么是对的。

贪心地选取总价值最大，直到不能再选为止。

贪心正确的原因在于，每次拿出去的交换集合是随意的，在已有的物品中，可以选任意件物品。

如果有一个状态，在当前情况最大，但是对于总答案不是最优子结构，一定可以把一些物品换出去，再扩展能达到的最优子结构。

从这个角度而言，对于最终答案其实也并不存在所谓的最优子结构。

贪心的选取最大时，如果两个状态有重复物品，没有影响，因为差值在可换范围内，只需要把不重复的那些拿出去换成更大的回来即可。

所以根本不需要考虑具体物品是什么，只需要不断扩展价值即可，只要能增大，就一定可以有交换方式使它变得更大。

复杂度第一部分好说，一个裸的背包。第二部分的复杂度挺玄学，但是显然的，最差不过是 $O(nm)$，还没有前面背包的复杂度高，完全没问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mx=50+10;
int n,d,c[mx],dp[mx*10000],ans,ma,day;
void MYH(){
    scanf("%d%d",&n,&d);
    for(int i=1;i<=n;++i){scanf("%d",&c[i]);ma=max(ma,c[i]);}
    ma=ma*n;dp[0]=1;
    for(int i=1;i<=n;++i){
        for(int j=ma;j>=c[i];--j){
            dp[j]=max(dp[j],dp[j-c[i]]);
        }
    }
    while(1){
        int pd=0;
        for(int j=ans+d;j>ans;--j){
            if(dp[j]){ans=j;day++;pd=1;}
        }
        if(pd==0)break;
    }
    printf("%d %d\n",ans,day);
    
}
int main(){
    MYH();
    return 0;
}
```


---

## 作者：AC自动机 (赞：0)

### 思路
然而并没有思路，只能想到贪心可以直接得到的最大值，例如价值a可以得到，那么a到a+d内的所有值都可以贪到，也没有去证明，应该是正确的吧qwq

看了题解后才明白了怎样dp，用dp[i]来表示能否通过挑选不同的物品来保证价值为i，因此状态转移方程可以得出：

####     if(dp[j-c[i]]==1)dp[j]=1;


后面就可以进行贪心了，如果价值为a的物品能得到，那么下一步一定是贪a到a+d之内的价值最大的可以取到的物品，直到无法继续进行为止。

#### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
#include<deque>
#include<math.h>
#include<stdio.h>
using namespace std;
int dp[550001],c[10005];
int main(){
	int n,d;
	cin>>n>>d;
	for(register int i=1;i<=n;i++){
		cin>>c[i];
	}
	memset(dp,0,sizeof(dp));
	dp[0]=1;
	for(register int i=1;i<=n;i++){
		for(register int j=550000;j>=c[i];j--){
			if(dp[j-c[i]]==1)dp[j]=1;
		}
	}
	register int now=0,t=0;
	for(;t<=550000;t++){
		//cout<<now<<endl;
		int e=now+d;
		for(register int i=e;i>=now;i--){
			if(dp[i]==1){
				now=i;
				break;
			}
		}
		if(e==now+d)break;
	}
	//cout<<dp[6]<<endl;
	cout<<now<<' '<<t<<endl;
	return 0;
}
```

---

