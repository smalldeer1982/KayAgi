# Powering the Hero (hard version)

## 题目描述

This is a hard version of the problem. It differs from the easy one only by constraints on $ n $ and $ t $ .

There is a deck of $ n $ cards, each of which is characterized by its power. There are two types of cards:

- a hero card, the power of such a card is always equal to $ 0 $ ;
- a bonus card, the power of such a card is always positive.

You can do the following with the deck:

- take a card from the top of the deck;
- if this card is a bonus card, you can put it on top of your bonus deck or discard;
- if this card is a hero card, then the power of the top card from your bonus deck is added to his power (if it is not empty), after that the hero is added to your army, and the used bonus discards.

Your task is to use such actions to gather an army with the maximum possible total power.

## 说明/提示

In the first sample, you can take bonuses $ 1 $ and $ 2 $ . Both hero cards will receive $ 3 $ power. If you take all the bonuses, one of them will remain unused.

In the second sample, the hero's card on top of the deck cannot be powered up, and the rest can be powered up with $ 2 $ and $ 3 $ bonuses and get $ 6 $ total power.

In the fourth sample, you can take bonuses $ 1 $ , $ 2 $ , $ 3 $ , $ 5 $ and skip the bonus $ 6 $ , then the hero $ 4 $ will be enhanced with a bonus $ 3 $ by $ 5 $ , and the hero $ 7 $ with a bonus $ 5 $ by $ 4 $ . $ 4+5=9 $ .

## 样例 #1

### 输入

```
5
5
3 3 3 0 0
6
0 3 3 0 0 3
7
1 2 3 0 4 5 0
7
1 2 5 0 4 3 0
5
3 1 0 0 4```

### 输出

```
6
6
8
9
4```

# 题解

## 作者：_Haoomff_ (赞：3)

用 priority_queue （优先队列）即可过。

在输入数列时，特判当前输入的数 $a_i$ 是否等于 $0$，若为 $0$ 且队列非空（即队列有数），累加最大值；否则，将数 $a_i$ 入队。
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll t,n,ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(;t--;){
		priority_queue<ll> q;
		ans=0;
		cin>>n;
		for(;n--;){
			int a;
			cin>>a;
			if(a==0){
				if(!q.empty()){
					ans+=q.top();
					q.pop();
				}
			}//这里的括号不加会出问题
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：szhqwq (赞：1)

## 分析

相较于 C1，C2 的数据范围变大了：$1 \leq n \leq 2 \cdot 10^5$

但是使用**优先队列**的话，同样可以过这道题。建立一个**大根堆**，每次输入 $s_i$，将其加进优先队列里，当 $s_i = 0$ 的时候，将其当前队头元素加入存储答案的变量当中，并将队头元素出队。最后，输出变量的值即可。

[Link](https://codeforces.com/contest/1800/submission/195909674)

---

## 作者：Loser_Syx (赞：0)

## 思路

这题大水题了，只要用优先队列（`priority_queue`） 将数组从大到小排序就好了。

与 easy version 不同的是数据范围，但是无伤大雅，优先队列是能过的。

对于每次 $a_i=0$ 的情况，我们只需将队列中的最大值加入答案，并移除此值，不过要特判队列是否为空，不然 RE 等着你。

对于其他情况，只需让 $a_i$ 入队即可。

温馨提示：让优先队列从大到小排序初始化时是 `priority_queue<int> q;`，而不是 `priority_queue<int, vector<int>, greater<int>> q;`，我一开始搞错了 WA 的。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[214514];
main(){
	int T;
	scanf("%lld", &T);
	while(T--){
		memset(a, 0, sizeof a);
		int n, ans = 0;
		scanf("%lld",&n);
		priority_queue<int> q;
		for(int i = 1; i <= n;i++){
			scanf("%lld", &a[i]);
			if(a[i] == 0){
				if(!q.empty()){
					ans += q.top();
					q.pop();
				}
			}else{
				q.push(a[i]);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑一个十分显然的贪心。

每个英雄一定取到前面最大的没有被取的附加牌。

由于答案与**顺序**无关。

所以前 $k$ 个英雄一定可以取到前 $k$ 大的附加牌。

那么考虑用一个堆维护即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
void work(){
    int ans=0;
    priority_queue<int> s;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(x==0&&s.size()>0){
            ans+=s.top();
            s.pop();
        }
        else{
            s.push(x);
        }
    }
    cout<<ans<<'\n';
}
signed main(){
    cin>>T;
    while(T--) work(); 
}
```


---

## 作者：Rainsleep (赞：0)

## 题意

有一副由 $n$ 张卡组成的牌，每一张牌有一个力量值，卡牌分为两种类型：
+ 对于一张英雄卡，它的力量值总是 $0$。
+ 对于一张附加卡，其力量值总为 **正数**。

你可以对这副牌做以下操作：
+ 从牌堆顶端取走一张牌；
+ 如果这张牌是附加牌，你可以把它放到你的附加牌堆的 **堆顶**，或者直接丢弃；
+ 如果这张牌是英雄牌，那么附加牌堆顶的牌的力量值会赋给当前英雄卡（如果附加牌堆非空），之后其会加入你的军队，并且消耗所用附加牌。

你的任务是用这些操作集结一支 **最大总力量值的** 军队。

## $\text{Solution}$

有点诈骗。考虑每一张英雄卡的力量值获取范围，由于我们每一张卡都 **必须直接决策力量值**，所以其力量值只能从前 $i-1$ 张牌中的附加牌获取，那么形如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/6o3qw45c.png)
考虑贪心，对于每一张英雄牌，选择其前 **没用过的附加牌中的最大力量值**，正确性显然。

或许会有同学考虑到附加牌堆是一个 **栈**，怎么能保证其要的牌就一定在栈顶呢。

这个其实简单，其实跟栈没什么关系，我们把不会用到的牌直接丢弃即可，那么无论是当前英雄牌要的附加牌还是当前英雄牌抢了后面要的附加牌，答案都是相同的，因为我们要求的是最大值的 **总和**，那么力量值放前放后对答案的贡献都是一样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/xq5gaj30.png)

例如图中两张绿牌即为两张需要的附加卡，无论给谁的总和都是相同的。

实现时我们每遇到一张英雄牌就暴力寻找其前 **没用过的附加牌中的最大力量值**，然后加上，并对其打标记表示用过即可。时间复杂度 $O(n^2)$，简单版本可以通过。

---

考虑加强版，不难发现我们每一次做的事情是 **取前缀最值，并动态删除，加入**，这样的操作不妨用一个大根堆维护，每一次取最大值，然后删除，否则加入附加牌。

代码：
```cpp
// LUOGU_RID: 103804378
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>

using namespace std;

int T, n, x;

int main()
{
	scanf("%d", &T);
	while(T -- )
	{
		long long res = 0;
		priority_queue<int>heap;
		scanf("%d", &n);
		for(int i(1);i <= n; ++ i)
		{
			scanf("%d", &x);
			if(x == 0 and !heap.empty())
				res += heap.top(), heap.pop();
			else if(x)
				heap.push(x);
		}
		printf("%lld\n", res);
	}
	return 0;
} 
```


---

## 作者：ダ月 (赞：0)

### 题目分析：

对于每张 H 牌，我们不妨放在左端，对于每张 B 牌，不妨放在右端。其中每张排有个依次从小到大的编号 $1,2,3\dots n$，同时 B 牌有权值。

我们从每张 H 牌连一条无向边指向**编号**小于它的 B 牌。第四组样例大致长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/mvmtwgyf.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（~~怎么有点像二分图匹配~~。）



由图像清晰地可以看到，$4$ 能走到的所有值，$7$ 都能走到。显然先让 $4$ 走它能走到的最大值，接下来再 $7$ 来挑。

我们把这个结论推广：

若有 $p$ 张 H 牌，让第一张 H 牌先挑它能到的最大值，然后再让第二张挑它能到的除第一张已经挑过以外的最大值，依次类推。

所以，我们只要统计在当前 H 牌前面所有未被使用过的牌的最大值即可。直接暴力，时间复杂度 $O(n^2)$。能过 easy version。

我们只需要一个能维护当前最大值，删除当前最大值的数据结构来维护，可以选择用堆或者平衡树。时间复杂度：$O(n\log n)$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n;
typedef long long ll;
ll a[N];
priority_queue<int> q;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		while(!q.empty()) q.pop();
		ll ans=0;
		for(int i=1;i<=n;i++){
			if(!a[i]&&!q.empty()) ans+=q.top(),q.pop();
			else q.push(a[i]);
		}
		printf("%lld\n",ans);
	}return 0;
}
```

提醒：如果当前堆没有任何元素，显然当前 H 牌取不到任何 B 牌。

备注：

H 牌指 Hero card，B 牌指 Bonus card。

---

