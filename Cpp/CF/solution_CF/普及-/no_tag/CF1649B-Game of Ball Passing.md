# Game of Ball Passing

## 题目描述

Daniel is watching a football team playing a game during their training session. They want to improve their passing skills during that session.

The game involves $ n $ players, making multiple passes towards each other. Unfortunately, since the balls were moving too fast, after the session Daniel is unable to know how many balls were involved during the game. The only thing he knows is the number of passes delivered by each player during all the session.

Find the minimum possible amount of balls that were involved in the game.

## 说明/提示

In the first test case, with the only ball, the game can go like this:

 $ 2 \rightarrow 1 \rightarrow 3 \rightarrow 4 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 2 $ .

In the second test case, there is no possible way to play the game with only one ball. One possible way to play with two balls:

 $ 2 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 1 $ .

 $ 2 \rightarrow 3 \rightarrow 2 \rightarrow 1 $

In the third example, there were no passes, so $ 0 $ balls are possible.

## 样例 #1

### 输入

```
4
4
2 3 3 2
3
1 5 2
2
0 0
4
1000000000 1000000000 1000000000 1000000000```

### 输出

```
1
2
0
1```

# 题解

## 作者：Lyr_ids (赞：5)

### <题意>

一群人踢球传球，第 $i$ 个人**传出去了** $a_i$ 次球。求最小的球数。

+	什么是球数？

			从某个人开始踢第一球，直到最后一个球员接到球不传球了。此为一球。
         	球数指球的总和。

### <题意分析>

考虑把踢球数最多的球员( $Max$ )单拎出来，剩下的人“合并”成一个球员( $Union$ )。

那么题目可以简化为 $Max$ 会和 $Union$ 来回交互。

case 1:倘若 $Max$ 的传球次数超过了 $Union$ ，那么可以理解为当 $Union$ 传球结束后 $Max$ 会向 $Union$ 发球但是 $Union$ 不回传。球数为$Max - Union$ 。

case 2:如果 $Union$ 的传球次数比 $Max$ 要多，那么当 $Max$ 传球结束时 $Union$ 会自己传自己(组合体嘛自己可以传自己)，球数为 $1$ 。

特判: $Max$ 是 $0$ 答案就是 $0$ 球。

附：关于 $Union$ 大于 $Max$ 时一定可以自己传自己的证明。

		因为 Max 是序列 a 中最大的数，那么组成 Union 的每个数都比 Max 要小。假设 Union 大于 Max 时不能自己传自己，那么此时 Union 一定只有一个成员，且该成员大于 Max。因为 Max 是最大的成员，没有成员大于 Max ，所以该情况不存在。

附：代码。
```cpp
read(n);
sum=0;
int tmp=0;
for(int i=0;i<n;++i)
{
	read(a[i]);
	sum+=a[i];
	tmp=max(tmp,a[i]);
}
sum-=tmp;
if(tmp==0)
{
	puts("0");
	continue;
}
if(sum>=tmp)
	puts("1");
else
	printf("%d\n",(int)tmp-(int)sum);
```

---

## 作者：0xFF (赞：5)

#### 题目大意


------------
一共有 $n$ 个球员，现给出 $n$ 个球员的传球次数，询问最少需要几个球才能满足题设要求

#### 题目分析


------------
仔细观察不难发现如下规律

- 统计出传球总数，如果传球次数总和为 $0$ 则必定输出 $0$。
- 设 ```maxn``` 为最大的传球数，```sum``` 表示传球数之和，假设每个人的球传出去必定传给传球数最多的人，那么当 $2 \cdot maxn \le sum$ 时，必定可以构造出一种方案满足只需要一个球就可以满足题目要求。若 $2 \cdot maxn \ge sum$ 时，设 ```min``` 为答案,$ sum - min \ge 2 \cdot (maxn - min)$，同样假设每个人的球传出去必定传给传球数最多的人，那么每次传球数最多的人总会比其他人的传球总和大 $1$，这就是满足题设的最优条件，故可以推得上述式子，化简可以得到 $min \ge 2 \cdot maxn - sum$。
- 若为另一种情况，即 $2 \cdot maxn \le sum$ 时，显然可以直接用一个球解决问题。

#### 代码实现


------------
```cpp
#include<iostream>
using namespace std;
int t,n;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n;
		long long sum=0;
		int a;
		int maxn=0;
		for(int i=1;i<=n;i++){
			cin>>a;
			sum+=a;
			maxn=max(maxn,a);
		}
		if(sum==0){
			cout<<0;
		}
		else if(maxn*2<=sum){
			cout<<1;
		}
		else{
			cout<<2*maxn-sum;
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Aya_tt (赞：2)

大体思路给大家点拨一下。

刚开始思路不好像，其实，突破口就在于要把球传给传球次数最多的人。

传球次数最多的人的传球次数乘 $2$，如果比他们总和要大，那么就必须需要多用几个球。

如果不到他们的总和，那么一个球就完了。

但是这还是拿不了满分，如果他们都不传球呢？所以就是只用 $0$ 个球就够了。

外面套个循环就结束了代码，这题很有思想难度，实现很简单，代码就不贴了。

---

## 作者：Gao_l (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1649B)

## 题意

有 $n$ 个人在传球，第 $i$ 个人传出去了 $a_i$ 次球。求最小的球数。

## 思路

将传球次数最多的人的传球次数 `maxi` 与其他人的传球次数之和 `sum` 设为一组。

则答案：

1. 当 `sum` $ \ge $ `maxi` 时 $ans=1$。

2. 当 `sum` $ < $ `maxi` 时 $ans=maxi-sum$。

3. 特判：当 `maxi` $ =0 $ 时，直接为 $0$。

## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,n,x,sum,maxi;
signed main(){
    cin >> T;
    while(T--){
        cin >> n;
        maxi=-1e18;
        sum=0;
        for(int i=1;i<=n;i++){
            cin >> x;
            sum+=x;
            maxi=max(maxi,x);
        }
        sum-=maxi;
        if(maxi==0)cout << "0\n";
        else if(sum>=maxi)cout << "1\n";
        else cout << maxi-sum << "\n";
    }
}
```

---

## 作者：tmp_get_zip_diff (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1649B)

-----

## 题意简述

有 $n$ 个人，每个人有一定的传球次数，问至少要多少个球才能满足所有人的次数。

## 思路

我们可以将传球次数最大的单独为一组，其余的人为一组。

先求出这两组的传球次数和 $(maxi,sum)$。

$ans$ 即为：

$ans=
\begin{cases}
 0 & maxi=0
 \\
 1\ &sum \le maxi
 \\
 maxi-sum &  maxi>sum
\end{cases}
$

那代码就很简单了。

## 注意事项

**数据千万条，清空第一条。  
多测不清空，爆零两行泪。  
清空不规范，超时总相伴。**  

## 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long

int t,n,x,sum,maxi; 

signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		maxi=-1e18;
		sum=0;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			maxi=max(maxi,x);
			sum+=x;
		}
		sum-=maxi;
		if(maxi==0)
			cout<<"0\n";
		else if(sum>=maxi)
			cout<<"1\n";
		else
			cout<<maxi-sum<<"\n";
	}
	return 0;
}
```

---

## 作者：氧少Kevin (赞：1)

# 取石子问题
## 描述
- 有 $n$ 堆石子，每堆石子有 $a_i$ 个
- 要求每次选**两个不同的堆**，各取走一个石子
- 现在要求将所有石子取完，问是否可行。保证 $\sum a_i$ 为偶数

## 思路
- 由于每次取石子必须从两个不同的堆取，所以应该注意到石子数量最大的堆是能否取完的关键
- 基于贪心的思想，我们要取先完石子数量最多的堆，那就需要先拿一个石子数量最多的堆的石子，再拿一个其他堆的石子与之配对
- 答案就很显然了：如果 $\max(a_i)\leq \sum(a_i)-\max(a_i)$，则可以取完，否则不行

## 例题
### CF1649B - Game of Ball Passing
- https://codeforces.com/problemset/problem/1649/B
#### 题意
- 有 $n$ 个人玩传球游戏，给出每个人**把球传出去**的次数 $a_i$
- 问：要满足条件，最少需要几个球
- 例如：$2,3,3,2$ 需要 $1$ 个球。传球的顺序可以是：$2→1→3→4→1→2→3→4→2→3→\times$
- 例如：$1,5,2$ 需要 $2$ 个球。传球的顺序可以是：$2→1→2→3→2→3→2→\times$， $2→\times$
#### 思路
- 能注意到，最后一个人是可以任意选择的，因为他不用把球传出去
- 能注意到，如果需要多个球，从第二个球开始，一定是**剩下的唯一一个**次数没达到要求的人，将球传给其他任意一个人，只传一次，这个球就结束
- 考虑前面的人，基于贪心的策略，必然是 $a_i$ 最大的先传球，接下来的过程与上文的取石子问题类似
- 因此，若 $\max(a_i)\leq \sum (a_i)-\max(a_i)$，则只需要 $1$ 个球
- 否则，$ans = \max(a_i) - ( \sum (a_i)-\max(a_i))$

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1649B) & [CF链接](http://codeforces.com/problemset/problem/1649/B)

## 思路分析：

这道题可以先求出传球数量最多的球员 $A$ 传球的数量记为 $x$，然后把剩下球员的传球数加起来记为 $s$，整个过程视为球员 $A$ 与其他所有球员都传一次球。

如果 $x=sum$，那么正好只需要一个球即可全部传完。

如果 $x>sum$，那么当 $A$ 球员与其他所有球员传完球之后，还需要传 $x-sum$ 次，剩下的球员只能接住 $A$ 球员 $x-sum$ 次的传球了，无法再回传给 $A$，因为他们的传球次数已经用完了。

如果 $x<sum$，那么也只需要 $1$ 个球即可，因为在 $A$ 球员与其他球员都传过之后，其他球员之间还可以相互传球。但如果其他球员只有一个人呢？不可能，绝对不可能！下面给出严格的证明：

假设 $x<sum$ 且 $sum$ 只有一个人，那么 $n=2$，但是 $x$ 是求出的最大值，现在有一个人组成的 $sum$ 是大于 $x$，这与传球数量最多的球员传球的数量为 $x$ 矛盾，故假设不成立。

## 代码：

```cpp
#include<iostream>
#define ll long long
using namespace std;
ll n,a[200010],maxx,sum;
ll check(){
	sum-=maxx;//减去最大值
	if(maxx<=sum&&maxx!=0){//判断
		return 1;
	}
	return maxx-sum;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		sum=maxx=0;//多组数据初始化
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			maxx=max(maxx,a[i]);//求最大值
			sum+=a[i];//记录总和
		}
		cout<<check()<<endl;//输出答案
	}
	return 0;
}
```

---

## 作者：_Fatalis_ (赞：0)

### Solution

重点在于如何利用 “每个人**传出**球的次数是给定的（传入不算次数）。”

找出踢球数最大的人，这个人的踢球数可以消耗其他人的踢球数。

若其他人的踢球数总和大于踢球数的人，这些人可以自己内部对踢（无论是一对一还是多对多，反正剩下的踢球数等于最大踢球数）。

但如果最大踢球数的人踢球的数量太大了，他跟其他人消耗后，还剩下了一些球数，只能他自己踢了（为什么？最多的情况下，即剩下人不内部踢球，只与最大踢球数的人踢，也只能消耗这些，还差一些）。

所以，

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,k,maxn=0,sum=0;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>k;
            maxn=max(maxn,k);
            sum+=k;
        }
        // sum-=maxn;
        // if(sum)
        if(maxn==0) cout<<0<<endl;
        else
        {
            int ans=max(1ll,maxn-(sum-maxn));
            cout<<ans<<endl;
        }
    }
    return 0;
}
```

---

## 作者：_edge_ (赞：0)

这题搞了我半天，但至少自己玩出来了个大概。

1. 首先要模拟一下样例，可以发现是两个队员在对拼进行消耗，每一次两个队员都会 $-1$。

1. 我们会发现，这个最大的最好不要留在最后去对拼，拼出来有可能会使得答案更劣。

1. 再观察一下性质，会发现事实上，如果没有非常非常大的数，其他队员中都可以对拼消耗掉，因为有最后一次传球的机会。

1. 那么答案和最大值就有着千丝万缕的关系。

1. 第一次对拼消耗的时候，尽可能把最大值给消耗掉一部分，这样在后面会省掉一些事情。

1. 如果一个最大值不超过总和除以 $2$ 则没有任何贡献。

1. 那么很明确了，先利用除了最大值以外的数对拼掉最大值的一部分，注意第一次有可能会多出来一个减一，就是最后传到它手上，然后接下来的球就只能一个一个传出去。

发现难题做多了，这种简单题都不会做了。

```cpp
#include <iostream>
#include <cstdio>
#include <set>
#define int long long 
using namespace std;
const int INF=1e6+5;
int t,n,a[INF];
multiset<int>s;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	while (t--) {
		cin>>n;s.clear();int sum=0,Max=0;
		for (int i=1;i<=n;i++)
			cin>>a[i],sum+=a[i],Max=max(Max,a[i]);
		if (Max==0) cout<<"0\n";
		else if (sum-Max>=Max) cout<<"1\n";
		else cout<<(Max-(sum-Max)-1)+1<<"\n";
	}
	return 0;
}
```


---

## 作者：Accepted_Error (赞：0)

### [CF1694B](https://www.luogu.com.cn/problem/CF1649B)

## 题目大意

一共有 $n$ 个球员，两个球员间可以传球，现给出 $n$ 个球员的传球次数，询问最少需要几个球才能满足次数。

## 题目分析

重点在于利用题干中的 **每个人传出球的次数是给定的（传入不算次数）。**

那么可以得出一个人接受球不消耗次数，球从他手里出去，再回到他手上则可以消耗自己和其他人共两次传球次数。

如果有一个人的传球次数最大，其他人的次数之和都比他少，他传给其他人再回到他手中后，**仍然剩下一些传球次数**，
那么需要多增加一颗球来消耗他的传球次数。

那么我们可以总结出一个思路：

**其他人要尽可能地把球传给传球次数最多的人，如果一个球传到次数最多的人手中后，他的传球次数仍没有耗尽，那么球的个数需要增加直到耗尽传球次数。**

------------

**注意要判断踢球次数为 $0$ 的情况!**

## AC Code :

```cpp
#include<bits/stdc++.h>
#define ll long long //由于传球次数最大到1e9,所以需要开 long long 
using namespace std;
const int N=1e5+10;
ll t,n,sum,maxn; //sum记录每个球员传球次数之和, maxn求得传球次数的最大值 
ll a[N]; //记录传球次数 
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
	{
        cin>>n;
        for(int j=1;j<=n;j++)
		{
            cin>>a[j];
            sum+=a[j]; //记录总和 
            maxn=max(maxn,a[j]); //求最大值 
        }
        if(maxn==0) cout<<"0"<<endl; //判 0 
        else
        {
        	sum-=maxn; //计算除传球次数最大的人之外的人的传球次数 
        	cout<<max(1ll,maxn-sum)<<endl;
//maxn-sum代表传球次数最大的人剩余的传球次数, 如果传球次数小于等于1, 说明只需要使用1个球, 否则需要使用maxn-sum个球 
		}
        sum=0;
        maxn=0;
    }
    return 0;
}

```


---

## 作者：Disjoint_cat (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1649B)

题意：有 $n$ 个人在练习传球。第 $i$ 个人传了 $a_i$ 次球。求至少用了多少个球。

首先，很直觉地感觉：好像都只要用 $1$ 个球啊。

那么，我们可以想：什么情况下只需要用 $1$ 个球？

~~鱿鱼~~由于第 $2$ 组数据答案不是 $1$，所以我们可以考虑一下这组数据。

我们发现，这里的 $1$ 和 $2$ 都比较小，而 $5$ 很大。

所以我们考虑把非最大的数字加起来，记为 $othr$，同时把最大的数字记为 $ma$。

- 如果 $othr\ge ma$：

那么传球最多的人可以和其他人互传 $ma$ 次，其他 $(othr-ma)$ 次可以是其他人互传，答案为 $1$。

- 如果 $$

- 如果 $othr+1<ma$：

那么可以先让传球最多的人给其他人传 $(ma-othr-1)$ 次球，此时 $ma$ 就缩小到了 $othr+1$，那么再用 $1$ 个球就可以了，答案为 $(ma-othr-1)+1=ma-othr$。

**最后，注意要判 $0$！！！**

好了上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
long long a[100005],ma,othr;
bool all0;
int main()
{
	cin>>T;
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		all0=1,ma=othr=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i])all0=0;
			ma=max(ma,a[i]),othr+=a[i];
		}
		othr-=ma;
		if(all0)puts("0");
		else printf("%lld\n",max(1ll,ma-othr));
	}
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

## 题目分析
很显然，**你为了让球的个数尽可能的少，一定会想让一个球在人们的手中传递的次数尽可能的多**。

然后我们就会发现一个巨大的问题：**当其他人的传球次数都用完的时候，很可能传球次数最多的人还有许多次球要传。**

比如对于这一组样例：

$3$

$1 \ 5 \ 2$

我们发现不管怎么样第二个人都会多出一次传球次数。所以我们迫不得已只能再增加一个球。此时最少就要用两个球。

所以我们可以总结出一个贪心思路：**其他人要尽可能地每次都把球传给传球次数最多的人。如果无法使用一个球，那么迫不得已必须要增加球的个数。**

更具体的，我们结合上面这组样例进行分析：

为了让二号球员剩余的传球次数尽可能少，所以我们选择**从他开始传球，并且传到球的每个人都立即把球回传给二号，让二号尽可能多传**，那么最优的传球序列就是：

第一个球：$2→1→2→3→2→3→2→3$ 或 $2→1→2→3→2→3→2→1$

第二个球：$2→1$ 或 $2→3$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t,n;
ll a[100005];
int main(){
    cin>>t;
    while (t--){
        cin>>n;
        ll s=0;
        for (int i=1;i<=n;i++) {
            cin>>a[i];
            s+=a[i];//记录所有人传球次数的总和
        }
        sort(a+1,a+n+1);//其实并不用排序，直接记录最大值就可以了
        if (s==0){
            cout<<0<<'\n';//特判没有人传球的情况
        }else{
            s-=a[n];// a[n] 就是最多的传球次数，把它减掉就是其他人加起来的传球次数
            cout<<max(1ll, a[n]-s)<<'\n';// a[n]-s 表示传球最多的人还要传这么多次，如果它小于等于1，就表示一个球足够了，不然就要用 a[n]-s 个球
        }
    }
    return 0;
}
```


---

## 作者：__vector__ (赞：0)

## UPD:  
修理了一些空格问题，修了一下爆炸的 markdown。  
## 前言：  
~~赛场上想了一个做法但自认为是错的，结果赛后看了官方题解做法差不多~~   
我自认为球可以自己传给自己，如果错了请大佬指出来。  
## 题目大意：  
有 $n$ 个球员，每两个球员之间可以互相传球。  
给定一个长度为 $n$ 的数组 $a$，$a_i$ 代表第 $i$ 个球员传球次数。  
问最少有多少个球。  
## 题目分析：  
模拟一下，可以发现第个球员可以消掉 $a_i \cdot 2$ 个传球次数（其中 $a_i$ 个球是消掉自己的传球次数，另外 $a_i$ 个球是消掉别人的传球次数）。  
也就是说，让他们互相抵消就行了，一对球员互相消完之后再传给下一个球员继续。最后如果只剩下了一个球员没有消完，假设这个球员还剩下 $x$ 个球，那么再拿来 $x$ 个球，自己传给自己就行了。  
最后方法就是：  
1. 定义一个变量 $imax$ 代表 $a$ 数组中所有元素的最大值。  
2. 定义一个变量 $cnt$ 代表 $\Sigma^{n}_{i} a_i$  
3. 如果 $imax \cdot 2 \le cnt$，那么只需要一个球，原因是模拟让一个球员去消掉别的所有球员的传球次数的情况，如果自己会被消掉，说明所有球员一定可以通过某种方案互相消掉。  
4. 如果 $imax \cdot 2 \ge cnt+1$，那么需要 $imax \cdot 2 - cnt$ 个球，原因是模拟让一个球员去消掉别的所有球员的传球次数的情况，如果自己不会被消掉，说明无论如何一定不能只通过一个球，使所有球员互相消掉。需要引入 $imax \cdot 2 - cnt$ 个球使得最后剩下没被消掉的球员通过自己传给自己把自己传球次数消掉。  

注：  
需要判断所有球员传球次数都为 $0$ 的情况。  
## AC代码：    
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n;
const int maxn=1e5+5;
typedef long long ll;//hacker造出了爆int的数据！
int a[maxn];
ll cnt=0;
int imax;
bool flag;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        flag=1;
        scanf("%d",&n);
        imax=-1;
        cnt=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            imax=max(imax,a[i]);
            cnt+=(ll)a[i];
            flag&=(a[i]==0);
        }
        if(flag)
        {
            printf("0\n");
            continue;
        }
        if(((ll)imax<<1)<=cnt)
        {
            printf("1\n");
        }
        else{
            printf("%lld\n",(ll)(imax<<1)-cnt);
        }
    }
    return 0;
}
```


---

## 作者：RocksonLee (赞：0)

## Problem

[luogu](https://www.luogu.com.cn/problem/CF1649B)

[codeforces](https://codeforces.com/contest/1649/problem/B)

## Solution

接受球不消耗次数，球从一个人手里出去，再回到他手上可以消耗两次

如果有一个人的次数多到其他人都没办法消耗他的次数

即其他人的次数之和应该比他少

那么他需要传出一颗球消耗一个次数

注意特判没有传递球，就不需要有球

可得 

$$
ans=
\begin{cases}
2 \times maxn-sum & (2*max \geq sum)\\
1 & (2*max < sum)\\
\end{cases}
$$

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    unsigned long long t, temp, n, sum, maxn;
    scanf("%llu", &t);
    for (int kkz = 0; kkz < t; kkz++)
    {
        maxn = 0, sum = 0;
        scanf("%llu", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%llu", &temp);
            sum += temp;
            maxn = max(temp, maxn);
        }
        if (maxn == 0)
            printf("0\n");
        else if (maxn * 2 <= sum)
            printf("1\n");
        else
            printf("%llu\n", maxn * 2 - sum);
    }
    return 0;
}
```

---

