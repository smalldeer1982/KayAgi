# Game with Colored Marbles

## 题目描述

Alice 和 Bob 在玩一个游戏。一共有 $n$ 个石子，第 $i$ 个的颜色为 $c_i$。Alice 先手，两人轮流取走一颗石子，直到游戏结束。

Alice 的最终分数计算如下：

- 对于每一个颜色 $x$，如果 Alice 有至少一颗该颜色的石子，她获得 $1$ 分。
- 对于每一个颜色 $x$，如果她拥有全部该颜色的石子，她额外获得 $1$ 分（只考虑游戏中出现的颜色）。

比如，假设有颜色为 $[1,3,1,3,4]$ 的五颗石子，Alice 第一次拿第 $1$ 颗，Bob 拿第 $3$ 颗，然后 Alice 拿第 $5$ 颗，Bob 拿第 $2$ 颗，最后 Alice 拿第 $4$ 颗。最终，Alice 获得 $4$ 分：$3$ 分来自拿走至少一颗颜色为 $1,3,4$ 的石子，剩下 $1$ 分来自拿走全部颜色为 $4$ 的石子。**注意这一方案不一定是对双方最优的。**

Alice 想最大化她的分数，而 Bob 想最小化这个分数，假设两人都足够聪明。求 Alice 的最终得分。

## 样例 #1

### 输入

```
3
5
1 3 1 3 4
3
1 2 3
4
4 4 4 4```

### 输出

```
4
4
1```

# 题解

## 作者：Beihai_Jiang (赞：1)

## 题意

爱丽丝和鲍勃在玩一个游戏。一共有 $n$ 个弹珠，其中 $i$ 个的颜色是 $c_i$。两人轮流玩；爱丽丝先玩，然后是鲍勃，接着是爱丽丝再玩，然后是鲍勃再玩，以此类推。

在轮到自己时，玩家**必须从剩下的弹珠中拿走** $1$ 颗，并将其从游戏中移除。如果没有弹珠了(所有的 $n$ 弹珠都被拿走了)，游戏结束。

游戏结束时爱丽丝的得分计算如下：

- 每拿到一种颜色的弹珠 $x$，她就能得到 $1$ 分；
- 此外，对于每种颜色 $x$，若她拿完了该颜色的所有弹珠，她都能得到 $1$ 分(当然，只考虑游戏中出现的颜色)。

例如，假设有 $5$ 个弹珠，它们的颜色是 $[1, 3, 1, 3, 4]$，游戏进行如下：爱丽丝得到 $1$ 颗弹珠，然后鲍勃得到 $3$ 颗弹珠，接着爱丽丝得到 $5$ 颗弹珠，然后鲍勃得到 $2$ 颗弹珠，最后爱丽丝得到 $4$ 颗弹珠。然后，爱丽丝得到 $4$ 分：拥有至少一个颜色为 $1$、$3$ 和 $4$ 的弹珠得 $3$ 分，拥有所有颜色为 $4$ 的弹珠得 $1$ 分。**注意这一策略不一定对双方都是最优的**。

爱丽丝希望在游戏结束时获得最大分数。鲍勃则希望将分数最小化。双方都采取最优策略(即爱丽丝选择一种能让她尽可能多得分的策略，而鲍勃选择一种能让爱丽丝的得分最小化的策略)。

计算游戏结束时爱丽丝的得分。

## 100pts

**贪心**

分析样例，我们发现单次操作Alice最多能获得 $2$ 分。

当且仅当，目前存在一颗只出现一次弹珠时，单次获得 $2$ 分。

因此，我们贪心地想，若存在上述情况，则优先选择该情况。

记有 $x$ 颗只出现一次的弹珠。

因为Alice先手，所以该情况最多得分为 $2\times \lceil \frac{x}{2} \rceil$。

选完 $2$ 分情况后，剩余的出现次数大于 $1$，每次最多贡献 $1$ 分。

记剩余的有 $y$ 种不同颜色的弹珠。

一分情况的贡献为 $y$。

综上，Alice的总得分为 $2\times \lceil \frac{x}{2} \rceil+y$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int T,n,c[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		int x=0,y=0;
		unordered_map<int,int> num;
		unordered_map<int,bool> vis;
		for(int i=1;i<=n;i++)
			cin>>c[i],num[c[i]]++;
		for(int i=1;i<=n;i++){
			if(vis.find(c[i])==vis.end()){
				vis[c[i]]=1;
				if(num[c[i]]==1)
					x++;
				else
					y++;
			}
		}
		cout<<2*ceil(x*1.0/2)+y<<endl;
	}
	return 0;
}
```

---

## 作者：GeYang (赞：1)

# 题意

地上有一些不同颜色的弹珠，两个人捡弹珠，每人每次取一颗，捡完时游戏结束。

先手的得分方式是捡一颗得一分，如果某种颜色的弹珠全部由先手捡走，则先手再得一分。

假设先手和其对手都足够聪明，求游戏结束后先手的得分。

# 思路

因为每次取一颗，所以为了让自己的分数尽可能多，先手会选择只有一颗且颜色与其它任何弹珠，包括已经被捡走的弹珠都不同的弹珠，这颗被选择的弹珠就是先手要优先捡的。

被选择的弹珠可能会有多个，那么后手就要尽可能多地捡这种被选择的弹珠。

此时先手所得分数应为被选择的弹珠数量的一半向下取整后再乘二。

但实际上先手的分数还要加上剩余的不同颜色的弹珠数量。

设“被选择的”弹珠有 $m$ 个，剩余不同颜色的弹珠有 $n$ 个，则最后先手得 $[\frac{m}{2}]\times2+n$ 分。

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

要使 Alice 得分最大，她的最优策略是先取单个的弹珠子。剩下的数量大于 $1$ 的弹珠，每一种只能得到 $1$ 分。

然后模拟就好了。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 1e3 + 10;
ll T, n, shu[MAXN], ans = 0;
void read () {
	ans = 0;
	memset (shu, 0, sizeof (shu));
    cin >> n;
    for (ll i = 1; i <= n; i ++) {
        ll x; cin >> x;
        shu[x] ++;
    }
    sort (shu + 1, shu + n + 1);
    bool flag = 1;
    for (ll i = 1; i <= n; i ++) {
        if (shu[i] == 1) {
            ans += 2 * flag;
            flag ^= 1;
        }
        else if (shu[i] >= 2) {
            ans ++;
            flag ^= (shu[i] & 1);
        }
    }
    cout << ans << endl;	
}
int main () {
    cin >> T;
    while (T --) read ();
    return 0;
}
```

---

## 作者：long_long__int (赞：0)

# 题目翻译

Alice 和 Bob 在玩弹珠游戏，有 $n$ 颗弹珠，颜色分别为 $a_{1\sim n}$，Alice 先取，取完为止。

最终计算得分的方式如下：

- 如果取到了该颜色的一个及以上个弹珠，得分加一。

- 如果把该颜色的所有弹珠都取完了，得分再加一。

Alice 想取得尽可能高的分数，Bob 想尽可能减少 Alice 的分数，所以他们都会鞍最优策略取弹珠。

# 题目解法

Alice 肯定会先取只有一个的弹珠，这样就能得两分。而 Bob 肯定也会去这样的弹珠。令 $o$ 等于这样的弹珠的颜色数量，Alice 能得到 $\lceil o\div 2\rceil\times 2$ 分。然后，因为其他颜色的弹珠数量都大于一，所以 Alice 能取得所有这样颜色的弹珠的一分，即 $n-o$ 分。

最后得分的计算公式为 $\lceil o\div2\rceil\times2+n-o$ 分。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T; 
int n;
int b[1005];
void work(){
	memset(b,0,sizeof b);//多测不清空，保龄两行泪 
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		b[x]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(b[i]==1){
			ans++;
		}
	}
//	cout<<"ans:"<<ans<<"\n";
	ans=ceil(ans/2.0)*2+n-o;
	cout<<ans<<"\n";
}
int main(){
	cin>>T;
	while(T--) work();
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

有道翻译坑我两年半（Codeforces better 炸了）。

贪心。

对于 Alice，她一共有两种得分方式：

- 对于一种颜色的球，只要取了一个，就可以得 $1$ 分，所以 Alice 取球时要尽可能地取颜色不同的球。

- 如果 Alice 把一种颜色的球取完了，她可以额外获得一分，也就是意味着，她取一种颜色的球且这种颜色的球的数量只有一个，她可以直接获得 $2$ 分。

因为 Bob 要最小化 Alice 的得分，他也要尽可能地抢这样的球。

设有 $x$ 种颜色的球有且仅有一个，因为 Alice 先取，所以她一共可以拿到 $\lfloor \frac{x + 1}{2} \rfloor$ 个这样的球。

对于其他颜色的球（设有 $y$ 个），在两人都足够聪明的情况下，Alice 一共可以得到 $y$ 分。

总得分就是 $\lfloor \frac{x + 1}{2} \rfloor \times 2 + y$。

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

要使 Alice 得分最大，她的最优策略是先取单个的弹珠，因为她可以得到 $2$ 分。剩下的数量大于 $1$ 的弹珠，每一种只能得到 $1$ 分，因为她拿了 $1$ 个后，Bob 一定可以再拿使 Alice 不能拿完这种弹珠，因此她最多得 $1$ 分。

然后模拟并计分就好了。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;

constexpr int MAXN = 1e3 + 24;
int T;
int n;
int c,apr[MAXN];
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--)
    {
        memset(apr,0,sizeof(apr));
        cin >> n;
        for(int i = 1;i <= n;i++)
        {
            cin >> c;
            apr[c]++;
        }
        sort(apr + 1,apr + n + 1);
        bool turn = 1;
        int ans = 0;
        for(int i = 1;i <= n;i++)
        {
            if(apr[i] == 1)
            {
                ans += 2 * turn;
                turn ^= 1;
            }
            else if(apr[i] >= 2)
            {
                ans += 1;
                turn ^= (apr[i] & 1);
            }
        }
        cout << ans << "\n";
    }
}
```

---

