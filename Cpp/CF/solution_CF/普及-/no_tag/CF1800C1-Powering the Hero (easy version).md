# Powering the Hero (easy version)

## 题目描述

This is an easy version of the problem. It differs from the hard one only by constraints on $ n $ and $ t $ .

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

## 作者：szhqwq (赞：4)

## 分析

对于此题，我们可以考虑使用**优先队列**来解决，因为优先队列可以自动排好序，就不需要去考虑丢不丢弃牌以及寻找最大值的问题了，这里就建立一个**大根堆**。此外，使用一个变量记录最后答案。

每次输入 $s_i$，将其加进优先队列里，当 $s_i = 0$ 的时候，将其当前队头元素加入变量当中，并将队头元素出队。最后，输出变量的值即可。

[Link](https://codeforces.com/contest/1800/submission/195909589)

赛时也是被这道题折磨了很久，没想到可以使用优先队列来解决，所以做题的时候思维一定要打开。

---

## 作者：Jasoncwx (赞：2)

## 题目翻译
有 $n$ 张卡片，每张卡片上都有一个数字表示能量。这个数字是 $0$ 的卡片称为"英雄卡"，而其他卡片称为"奖励卡"。

你可以对这 $n$ 张卡片进行以下操作：

- 在最前面拿走一张卡片。
- 如果这张卡片是"奖励卡"，可以把它放在卡片的最前面，或不要这张卡片。
- 如果这张卡片是"英雄卡"，可以把能量最大的卡片的能量值添加进你的能量值（仅当卡片数量不为 $0$ 时才可以进行这个操作），并丢弃这张卡片，或不要这张"英雄卡"。

问你最多可以获得多少能量？
## 题目思路
按照题意模拟即可。

这道题目模拟的是一个优先队列 `priority_queue`，常见操作见[这里](https://baike.baidu.com/item/优先队列/9354754?fr=aladdin)。

详细解释请见代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ll t;
    cin>>t;
    while(t--){
        ll n,ans=0,t;
        cin>>n;
        priority_queue<ll> q;//优先队列
        while(n--){
          cin>>t;
          if(q.size()!=0&&t==0){//英雄卡
              ans+=q.top();//添加能量
              q.pop();//丢弃卡片
          } 
          else if(t>0)q.push(t);//奖励卡
    	}
    	printf("%lld\n",ans);//结果
	}
    return 0;
}
```

---

## 作者：Larryyu (赞：1)

## _Description_
简单版和困难版的唯一区别在于 $n$ 和 $t$ 的数据范围。

桌上有 $n$ 张牌每张牌都有一个能量值 $s_i$，英雄牌的能量值为 $0$，加分牌的能量值为正整数。

每次从桌上的牌堆顶部拿一张牌直到无牌可拿。
- 若该牌为加分牌，你可以将其放在加分牌堆的顶部或丢弃此牌。
- 若该牌为英雄牌，那么加分牌堆堆顶的牌的能量值将赋予该英雄牌，英雄牌加入军队，且该加分牌丢弃。

问军队的总能量值的最大值。

共 $t$ 组数据。

## _Solution_
每次取当前还在加分牌堆顶的最大值即可。

例：```1187090```

若所有加分牌都加入堆的话第一张英雄牌取得的是 ```7```，而当前最大值为 ```8```，明显在取 ```7``` 时弃牌即可。

例：```1187010```

将所有加分牌放入堆时，第一张英雄牌的当前最大值为 ```8```，而想要取到只可能弃 ```7```，此时军队最大值为 ```15```，明显不是最优。其实换个角度想，第一张英雄牌取 ```7```，第二张英雄牌取 ```8```，本质相同。

总结，若第 $i,j(i<j)$ 两张英雄牌（可以扩展到多张牌），$j$ 取 $i$ 前面的牌最优，就说明 $i,j$ 中没有加分牌能在前 $i-1$ 张牌中在前二大（例子中第二大为 ```7``` 而 $i,j$ 中只有 ```1```，取 $j$ 时最大为 ```7```,实则为 ```8```）,否则说明 $i,j$ 中有更大的牌，定为 $j$ 时最大的牌（因为前 $i-1$ 的最大 ```8``` 已经取走）。

所以满足取当前加分牌堆最大值的结论，即使当时那张英雄牌取不到（例子二），但后面的英雄牌仍能补上。

取最大值用大根堆维护。

时间复杂度：$O(n \log n)$，明显可以过简单版和困难版。

## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int t;
int a[500500];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	int n=read();
	long long ans=0;
	priority_queue<int> q;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]>0) q.push(a[i]);
		else if(a[i]==0) {
			if(q.size()>0){
				ans+=q.top(),q.pop();//记得弹出
			}
		}
	}
	cout<<ans<<endl;
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}

```

---

## 作者：minVan (赞：0)

**题目大意**

有一副由 $n$ 张卡组成的牌，每一张牌有一个力量值 $s_i$，卡牌分为两种类型：

- 当 $s_i = 0$ 时，这张卡为英雄卡。
- 当 $s_i > 0$ 时，这张卡为力量卡。

对于第 $i$ 张卡片：

- 如果这张牌是力量卡，你可以把它放到你的力量卡片堆的**堆顶**，或者直接丢弃。

- 如果这张牌是英雄卡，那么力量牌堆顶的牌的力量值会赋给当前英雄卡，并且会加入你的军队，并且消耗所用力量卡。

你的任务是用这些操作集结一支**最大总力量值的**军队。

**数据结构**

```cpp
const int N = 5005;
int s[N], n, ans = 0;
bool vis[N];
```

**解题思路**

如果 $s_i = 0$，则答案加上在 $s_1$ 到 $s_{i-1}$ 中没选过的里面的最大，并且标记它。

此部分代码为：

```cpp
int p = 0, maxi = -1; // p 为最大值的下标，maxi 时最大值。
for(int j = i - 1; j >= 1; j--) {
	if(!vis[j]) {
		if(maxi < s[j]) {
        maxi = s[j];
			p = j;
		}
	}
}
vis[p] = 1;
ans += maxi;
```

**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5005;
int s[N];
bool vis[N];
signed main() {
    int t;
    cin >> t;
    while(t--) {
        memset(vis, 0, sizeof(vis));
        int n, ans = 0;
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> s[i];
            if(!s[i] && i > 1) {
                int p = 0, maxi = -1;
                for(int j = i - 1; j >= 1; j--) {
                    if(!vis[j]) {
                        if(maxi < s[j]) {
                            maxi = s[j];
                            p = j;
                        }
                    }
                }
                vis[p] = 1;
                ans += maxi;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
```C

---

## 作者：WaterSun (赞：0)

2023/3/12：修改了笔误（鸣谢 winds888 大佬）。

# 题意

给定一个有 $n$ 张牌的牌堆，其中有两种牌：

- 英雄牌：权值为 $0$。

- 奖励牌：权值不为 $0$。

你要从牌堆顺序取牌（从左至右）。

当你取到奖励牌时，你有两种选择：放入新的牌堆的顶部；弃置这张牌。

当你取到英雄牌时，从新的牌堆顶取出一张牌，将其权值加入答案，并弃置。

求：答案的最大值。

# 思路

很裸的一道贪心。

有一个结论：当你遇到英雄牌的时候，你必定能取到还在的新牌堆中的奖励牌的最大值。

因为，你对于单个英雄牌在选择是否将当前奖励牌放入新牌堆中的时候，你可以选择丢弃，那么，你可以在遇到英雄牌之前将所有不优的奖励牌全部丢弃。

如果，你对于多张英雄牌也是如此，因为你先取权值大的，再取权值小的和先取权值小的，再取权值大的效果一样。（加法交换律）

那么，我们在简单版本中，我们就可以暴力 $\Theta(n^2)$ 的时间复杂度过这道题。

对于，加强版，我们就可以用堆优化，以 $\Theta(n \log n)$ 的时间复杂度过掉。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

int T,n,ans;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	T = read();
	while (T--){
		priority_queue<int> q;
		ans = 0;
		n = read();
		for (re int i = 1;i <= n;i++){
			int x;
			x = read();
			if (x) q.push(x);//加入堆 
			else{
				if (!q.empty()){//必须判断是否为空 
					ans += q.top();//累加答案 
					q.pop();
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
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

## 作者：Lovely_Elaina (赞：0)

### 题目解释

妥妥暴力枚举题。

有 $t$ 组测试数据，每组给你一个 $n$，然后给你一个长度为 $n$ 序列 $a$。

当 $a_i=0$ 时，查出序列 $a$ 的区间 $[1,i-1]$ 中的最大值，累加到 $sum$ 里面，并将该值移出序列。

最后输出 $sum$。

### 思路和代码

每次输入时，如果输入的数的值为 $0$，那么遍历之前输入的数，找到最大的累加，并且将最大的那个值标记，然后下次跳过。

优化：使用优先队列，全部输入完后遍历，如果 $a_i=0$，则累加并且丢弃最顶上的值（也就是最大的值），否则就压到队列里面。注意要特判队列为空的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,a[5010];

int main(){
    
    scanf("%d",&t);
    
    while(t--){
        
        priority_queue<int> q;
        scanf("%d",&n);
        
        for(int i = 1; i <= n; i++)
            scanf("%d",&a[i]);
        
        long long sum = 0;
        for(int i = 1; i <= n; i++){
            if(a[i] != 0){
                q.push(a[i]);
            }else{
                if(q.empty()) continue;
                sum += q.top();
                q.pop();
            }
        }
        
        printf("%lld\n",sum);
    }
    return 0;
}
```

---

