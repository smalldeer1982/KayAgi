# Salyg1n and the MEX Game

## 题目描述

This is an interactive problem!

salyg1n gave Alice a set $ S $ of $ n $ distinct integers $ s_1, s_2, \ldots, s_n $ ( $ 0 \leq s_i \leq 10^9 $ ). Alice decided to play a game with this set against Bob. The rules of the game are as follows:

- Players take turns, with Alice going first.
- In one move, Alice adds one number $ x $ ( $ 0 \leq x \leq 10^9 $ ) to the set $ S $ . The set $ S $ must not contain the number $ x $ at the time of the move.
- In one move, Bob removes one number $ y $ from the set $ S $ . The set $ S $ must contain the number $ y $ at the time of the move. Additionally, the number $ y $ must be strictly smaller than the last number added by Alice.
- The game ends when Bob cannot make a move or after $ 2 \cdot n + 1 $ moves (in which case Alice's move will be the last one).
- The result of the game is $ \operatorname{MEX}\dagger(S) $ ( $ S $ at the end of the game).
- Alice aims to maximize the result, while Bob aims to minimize it.

Let $ R $ be the result when both players play optimally. In this problem, you play as Alice against the jury program playing as Bob. Your task is to implement a strategy for Alice such that the result of the game is always at least $ R $ .

 $ \dagger $ $ \operatorname{MEX} $ of a set of integers $ c_1, c_2, \ldots, c_k $ is defined as the smallest non-negative integer $ x $ which does not occur in the set $ c $ . For example, $ \operatorname{MEX}(\{0, 1, 2, 4\}) $ $ = $ $ 3 $ .

## 说明/提示

In the first test case, the set $ S $ changed as follows:

{ $ 1, 2, 3, 5, 7 $ } $ \to $ { $ 1, 2, 3, 5, 7, 8 $ } $ \to $ { $ 1, 2, 3, 5, 8 $ } $ \to $ { $ 1, 2, 3, 5, 8, 57 $ } $ \to $ { $ 1, 2, 3, 8, 57 $ } $ \to $ { $ 0, 1, 2, 3, 8, 57 $ }. In the end of the game, $ \operatorname{MEX}(S) = 4 $ , $ R = 4 $ .

In the second test case, the set $ S $ changed as follows:

{ $ 0, 1, 2 $ } $ \to $ { $ 0, 1, 2, 3 $ } $ \to $ { $ 1, 2, 3 $ } $ \to $ { $ 0, 1, 2, 3 $ }. In the end of the game, $ \operatorname{MEX}(S) = 4 $ , $ R = 4 $ .

In the third test case, the set $ S $ changed as follows:

{ $ 5, 7, 57 $ } $ \to $ { $ 0, 5, 7, 57 $ }. In the end of the game, $ \operatorname{MEX}(S) = 1 $ , $ R = 1 $ .

## 样例 #1

### 输入

```
3
5
1 2 3 5 7

7

5

-1

3
0 1 2

0

-1

3
5 7 57

-1```

### 输出

```
8

57

0

3

0

0```

# 题解

## 作者：One_JuRuo (赞：2)

## 思路

看着无从下手，实际上又是一道诈骗题。

假设原数列不存在 $0$，那么我们可以直接加入 $0$，然后游戏结束，假设答案是 $k$。那么，如果我们选择加入 $k$，来试图让答案变大，那么 Bob 就会移除一个数，最优的话是 $1$，这样的话，你无论加入 $1$ 还是 $0$，答案都不会超过 $1$，于是一手好牌就被你打没了，就算 Bob 不移除 $1$，移除 $x$，你的最终答案也不会超过 $x$ 了。

~~（因为 Bob 只能移除比你加入的数还要小的数，所以如果你操作不好，Bob 甚至还没法让你）~~

那么，我们直接猜测最优的操作是每次加入目前集合中不存在的最小的数。

蒟蒻大概证明一下：

假设目前最小的不存在的数是 $x$，那么 $[0,x)$ 都应该是存在的，那么加入以后 $[0,x]$ 都是存在的，答案为 $x+1$，此时 Bob 会移除中间的某个数，那么我们再加回来，直到 Bob 移除了 $0$，然后你添加了 $0$，游戏结束。

但是如果你不加入 $x$，那么，Bob 再随便移除一个数 $y$，这时，如果你使用之前的策略，答案也只是 $x$，不使用的话，Bob 再移除一个小于 $y$ 的数，答案将会再次变小，你就会无力回天了。

所以想要答案尽可能的大，我们就只能每次选择最小的不存在的数。

蒟蒻在开始想的是拿个 `set` 存，但是，显然 `set` 的常数是接受不了的，可以想象，如果数据是 $[0,n-1]$，那么 Bob 就可以和你扯大约 $n$ 次皮，加上 `set` $\log n$ 的复杂度，轻松让你 `TLE`。

当然，也可能是我操作 `set` 有问题，因为我是把前 $10^5$ 都统计进了一个 `set`，然后再转一遍到另一个 `set`，并且赛后才发现给的是有序的，连最开始的 `set` 也不需要。~~（果然 OI 学多了，会掉视力）~~

然后蒟蒻转念一想，如果最开始加入 $x$，那么 Bob 无论取走那个数，下一次最小的都一定是 Bob 取走的那个数。

~~原来这么简单，赛时交了一发 `TLE` 一定是我脑抽了。~~

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,p;
set<int>s;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		cin>>n,s.clear();
		for(int i=1;i<=n;++i) cin>>a,s.insert(a);
		for(int i=0;i<=100000;++i) if(!s.count(i)){p=i;break;}//这里只是为了方便找到第一次的答案，所以用了set
     //其实不需要的，因为给的本身就是有序的，但是赛时没看到，现在又懒得改了。。。
		while(1)
		{
			cout<<p<<endl;//上文是指这里用了set
			cin>>a;
			if(a==-1||a==-2) break;
			p=a;
		}
	}
	return 0;
}
 
```

---

## 作者：Natori (赞：1)

>[CF1867C Salyg1n and the MEX Game](https://www.luogu.com.cn/problem/CF1867C)

简单博弈论题。

------------
设给出序列的 $\text{mex}$ 为 $x$，那么 Alice 第一次操作时加入 $x$ 一定是最优的。此时显然有 $\text{mex(s)} \ge x$。

因为如果加入的数 $y<x$，此时数列中有不小于 $2$ 个 $y$。如果 Bob 删掉了一个数，那么 Alice 可以将这个数重新加入以抵消 Bob 的操作，对数列的 $\text{mex}$ 没有影响。因此第一次加入 $y<x$ 不会使数列的 $\text{mex}$ 变大，显然是不优的。

而如果加入的数 $y>x$，由于 $x$ 没有在 $s$ 中出现，所以 $\text{mex(s)}$ 仍然是 $x$，相当于进行无效操作。因此第一次加入 $y>x$ 也是不优的。

对于之后的操作，Alice 可以将 Bob 上次删除的数重新加入回来，以抵消 Bob 的操作，从而维持最终的 $\text{mex}$ 不小于原序列的 $\text{mex}$。

因此排一遍序求 $\text{mex}$ 即可，时间复杂度 $\mathcal{O}(n \log n)$。

---

## 作者：Wunsch (赞：1)

# CF1867C Salyg1n and the MEX Game

[并不会更好的阅读体验](https://www.luogu.com.cn/blog/CA931/cf1867c-salyg1n-and-the-mex-game)

交互题。

### 提墓描述

给定长度为 $n$ 的序列，保证单增，你先手，每回合可以往序列中添加一个**原来没有**的数，对方后手，每回合会删掉一个序列中**原来存在**的数，并且**严格小于**你上一次放进去的那个数。目标是让最后序列的 Mex 最大。

输出每次你放进去的数。

多测。

### 输入格式&&输出格式

第一行一个数 $T (1 \le T \le 10^5)$，表示测试组数。

接下来 $T$ 组，每组的第一行为一个整数 $n$ $(1 \le n \le 10^5)$，表示数组长度。

接下来一行 $n$ 个整数 $s_i$ $ (1 \le s_i \le 10^9)$。

接下来输出一个整数 $x$ $(1 \le x \le 10^9)$，表示你想放进集合里的数，集合中必须不包含 $x$。

然后读入一个整数 $y$ $(-2 \le y \le 10^9)$。

-	如果 $0 \le y \le 10^9$，对方将从集合中删掉 $y$，轮到你的回合了。

-	如果 $y = -1 $，游戏结束，继续处理下一组数据，如果是最后一组则终止程序。

-	如果 $y = -2 $，说明你的查询无效，就是你代码写错了，应该立刻终止程序，否则会收到其他的判决。

每次输出你想放进集合里面的数，记得输出换行并使用　`fflush(stdout) ` 或者 `cout.flush()`来刷新输出。

## 思路

很明显这题对我们来说往里面放的数的大小是没有限制的，而我们可以通过改变我们放的数的大小来把对方逼到死局，那么现在就只需要考虑怎么让最后的集合的 Mex 值最大就行了。

由于每次对方只能拿走**严格小于**我们上一次放下的数的那些数，设上一次我们放下的数为 $x$，放$x$之前这个集合的 Mex 值为 $mx$，那么放完 $x$ 后有两种情况：

-	$x>mx$，那么放完后集合的 Mex 值不变。

-	$x=mx$，放完后集合的 Mex 值会变大。

（由于放入的 $x$ 必须是集合中没有的数，所以不会存在 $x<mx$ 的情况，因为如果有不存在的数比 $mx$ 还小了，那当前集合的 Mex 值一定是那个不存在的更小的数。）

再考虑到我们的目的，要让最后集合的 Mex 尽量大，所以肯定第二种操作更优。

然后到对方删数，由于他删掉的数一定**严格小于**我们最后放进去的数 $x$ ，而通过第二种操作后，当前序列的 Mex 值 $mx$ 一定会是大于等于 $x+1$ 的，那么这次删数之后 $mx$ 必定会减小，准确的说，是变成对方删去的数。

那么我们只需要每次对方删什么我们加什么就好了。

所以这题的做法如下：

-	第一次加入当前集合的 Mex 值，来保证最后的答案最大。

-	再之后对方删什么我们就加什么，保证答案不会减少。

在极限数据(像 $n=4,S=\{0,1,2,3\}$ 这样，且对方每次都会删去能删的最大的数)下会进行 $ 2 \times n +1 $ 次，提墓让在这种情况下判断并退出的，但是实测发现退早了会少读进来一个 $-1$ 导致获得 TLE 的好成绩，而且程序最多也就只能进行 $ 2 \times n +1 $，所以这种情况根本不用管。

AC Code:

```cpp
#include"iostream"
#define ll long long
// #define int long long

#define  f(i,a,b) for(int i=a;i<=b;i++)
#define ff(i,a,b) for(int i=a;i>=b;i--)

using namespace std;

ll rd()<%ll x=0,w=1;char c=getchar();while(c<'0'||c>'9')<%if(c=='-')w=-1;c=getchar();%>while(c<='9'&&c>='0')<%x=x*10+(c-'0');c=getchar();%>return x*w;%>

ll T=rd();

ll n;
ll len;
ll ac[100005];
namespace Wunsch<%

    void work()<%
        n=rd();
        ll qaq=-1;
        f(i,0,n-1)<%
            i[ac]=rd();
            if(qaq==-1&&i[ac]!=i)<%
                qaq=i;
            %>
        %>
        if(qaq==-1)qaq=n;
        printf("%lld\n",qaq);
        fflush(stdout);
        while(1)<%
            ll y=rd();
            if(y==-1)break;
            printf("%lld\n",y);
            fflush(stdout);
        %>
        return ;
    %>

    bool main()<%
        while(T--)<%
            work();
        %>
        return 1;
    %>

%>

bool ztt=Wunsch::main();

main()<%;%>

```

~~a马蜂不建议学。~~




---

## 作者：lfxxx (赞：0)

先把当前序列的 mex 填进去，不难发现 mex 一定增大且这是唯一的让 mex 增大的方法，故是不劣的。

然后考虑，交互库删除 $0$ 后 mex 马上变成 $0$ 但我们把 $0$ 填回来就可以抵消影响并结束游戏。

如果是其他的数呢？

不难发现交互库总有办法把最终的 mex 限制在最开始填了一个数的 mex 往下走，所以重复交互库删什么你填什么的策略就能做到最优。

下面是去年的赛时代码：

```cpp
#include<bits/stdc++.h>
//#define int long long
//#define lowbit(x) (x&-(x))
using namespace std;
const int maxn = 1e5+114;
int a[maxn];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	if(a[1]!=0){
		cout<<0<<endl;
		fflush(stdout);
		int x;
		cin>>x;
		return ;
	}
	else{
		int y=a[n]+1;
		for(int i=2;i<=n;i++){
			if(a[i]!=a[i-1]+1){
				y=a[i-1]+1;
				break;
			}
		}
		cout<<y<<endl;
		fflush(stdout);
		while(1){
			int x;
			cin>>x;
			if(x==0){
				cout<<0<<endl;
				fflush(stdout);
				int z;
				cin>>z;
				return ;
			}
			else if(x==-1){
				return ;
			}
			else{
				cout<<x<<endl;
				fflush(stdout);
			}				
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();

	return 0;
}
```


---

## 作者：Engulf (赞：0)

很水的交互题。

作为 Alice，为了让 mex 最大，我们每次应该都添加 $s$ 中最小的没有的那个数也就是 mex。

每次求 mex 是不优的。

题目中有个对 Bob 的限制，每次移除的数都小于 Alice 上次添加的数，我们上次添加的数是 mex，也就是说 $[0, \tt{mex}]$ 都出现过了，而 Bob 移除了这当中的一个数，那新的 mex 肯定就是 Bob 移除的数了。

所以最终的策略就是第一次输出 mex，然后每次都输出 Bob 移除的那个数即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        unordered_map<int, int> s;
        for (int i = 0, x; i < n; i++) cin >> x, s[x] = 1;
        auto getmex = [&]() {int mex = 0; while (s[mex]) mex++; return mex;};
        int mex = getmex();
        cout << mex << "\n";
        fflush(stdout);
        s[mex] = 1;
        int y;
        cin >> y;
        while (y != -1) {
            s[y] = 0;
            mex = y;
            cout << y << "\n";
            fflush(stdout);
            s[mex] = 1;
            cin >> y;
        }
    }
    return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

## Problem
交互题。给定一个 $n$ 个元素的集合 $S$，元素记为 $s_i(1 \le i \le n)$。每一回合，你可以选择一个数 $x(0\le x \le 10^9)$ 插入集合中，交互机会选择一个 $\le x$ 的数，并将其从 $S$ 中删除，**保证总回合数不超过 $2n-1$**。

游戏最后的答案为 MEX，你要最大化这个结果，交互机要最小化这个结果。设 $R$ 为你和交互机操作的最佳策略下的答案，请你规定一个策略，使最终答案至少为 $R$。
## Solve
脑瘫交互。

注意到每次交互机会选择一个 $\le x$ 的数，并将其从 $S$ 中删除。那么就很有可能删除掉你的 MEX。不过，你是先手。那么就能将问题转化：你先选择一个数插入，再变为交互机先手，你后手。

你先选择并插入的的数肯定是数列的 MAX，因为你要最大化 MEX。然后交互机删什么，你就填什么即可。

时间复杂度 $O(Tn)$。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 1e5 + 10;

int T, n, y, a[N];

void solve() {
  read(n);
  For(i,1,n) cin >> a[i];
  sort(a + 1, a + n + 1);
  int MEX = 0;
  For(i,1,n) {
    if(a[i] == MEX) MEX++;
  }
  cout << MEX << '\n';
  fflush(stdout);
  while(cin >> y) {
    if(y == -1) return ;
    cout << y << '\n';
    fflush(stdout);
  }
}

signed main() {
  read(T);
  while(T--) {
    solve();
  }
  return 0;
} 
```
这可能是我人生第一次自己做的交互题了。

---

## 作者：Erica_N_Contina (赞：0)

# Salyg1n and the MEX Game

## 描述

给定长度为 $n$ 的序列 $A$，你先手，每回合可以往序列中添加一个当前 $A$ 中**没有**的数，BOT 后手，每回合会删掉一个当前 $A$ 中**存在**的数，并且**严格小于**你上一次放进去的那个数。BOT 的目标是让最后序列的 mex 最小，而你的目标是让最后序列的 mex 最大。

输出每次你放进去的数。

每次输出你想放进集合里面的数，记得用 `endl` 输出换行或者使用 `fflush(stdout)` 或者 `cout.flush()` 来刷新输出。

## 思路

> mex 运算（minimum exclusion）定义为不属于集合 $A$ 中的最小**非负整数（注意包含0）。**
例如，$\operatorname{mex} (0 ,1,2) = 3 $，$\operatorname{mex}(1,2) = 0$。

我们称 $S=\{x|x\in \N_+,x\notin A\}$。

这道题目其实很简单，假设当前的 mex 值为 $me$，那么我们要考虑我们加入的数 $x$。结合 mex 的定义我们知道，$S$ 中一定不存在比 $me$ 更小的数了。我们选择的 $x$ 一定满足 $x\in S$，那么我们现在本质上只有两种选择：

- $x=me$

- $x≠me(x>me)$

再次结合 mex 的定义我们知道，只有第一种方法能让 $A$ 的 mex 变大，所以我们就选择第一种方法。（由于我们不知道后面还有几轮，并且如果我们选择不选择 $me$ 的话，后面我们还是迟早要选择填上 $me$ 这个数的）

现在轮到 BOT 操作了。由于 BOT 会删掉一个序列中序列中**存在**的数，并且**严格小于 $x$**，所以为了达到 BOT 的目标，它一定会删除可以删除的最小的那个数字，我们假设这个数字为 $y$。

现在又轮到我们先手了，我们可以知道当前的 $me=y$。延续上面的想法，我们当然是选择 $x=y$ 最优了。如此往复，在我们填入第一个数之后，我们就和 BOT 不断拉扯，它删哪个数，我们就把它填回来，这样我们就可以保证答案不劣。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=1e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,p,q,T,y,a[N],ans;

void solve(){
	cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		int me=a[n]+1;
		for(int i=1;i<=n;i++){
			if(a[i]!=i-1){
				me=i-1;break;
			}
		}
		cout<<me<<endl;
		while(cin>>y){
			if(y==-1||y==-2){
				return ;
			}
			else {
				cout<<y<<endl;
			}
		}
}

signed main(){
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```




---

