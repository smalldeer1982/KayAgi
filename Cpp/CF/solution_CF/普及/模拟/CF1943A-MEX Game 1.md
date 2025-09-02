# MEX Game 1

## 题目描述

Alice and Bob play yet another game on an array $ a $ of size $ n $ . Alice starts with an empty array $ c $ . Both players take turns playing, with Alice starting first.

On Alice's turn, she picks one element from $ a $ , appends that element to $ c $ , and then deletes it from $ a $ .

On Bob's turn, he picks one element from $ a $ , and then deletes it from $ a $ .

The game ends when the array $ a $ is empty. Game's score is defined to be the MEX $ ^\dagger $ of $ c $ . Alice wants to maximize the score while Bob wants to minimize it. Find game's final score if both players play optimally.

 $ ^\dagger $ The $ \operatorname{MEX} $ (minimum excludant) of an array of integers is defined as the smallest non-negative integer which does not occur in the array. For example:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ , because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, a possible game with a score of $ 2 $ is as follows:

1. Alice chooses the element $ 1 $ . After this move, $ a=[0,0,1] $ and $ c=[1] $ .
2. Bob chooses the element $ 0 $ . After this move, $ a=[0,1] $ and $ c=[1] $ .
3. Alice chooses the element $ 0 $ . After this move, $ a=[1] $ and $ c=[1,0] $ .
4. Bob chooses the element $ 1 $ . After this move, $ a=[\,] $ and $ c=[1,0] $ .

At the end, $ c=[1,0] $ , which has a MEX of $ 2 $ . Note that this is an example game and does not necessarily represent the optimal strategy for both players.

## 样例 #1

### 输入

```
3
4
0 0 1 1
4
0 1 2 3
2
1 1```

### 输出

```
2
1
0```

# 题解

## 作者：cute_overmind (赞：7)

考虑如何**最优**：

首先肯定一个数字的位置是**无关紧要**的，所以我们先放到桶里。

接下来对于一个值，如果他的次数大于等于 2 次，那么可以一人拿一个，谁拿都没有优势，所以爱丽丝**一定可以拿到出现次数超过 2 次的**。

那如果是 0 次，显然**无法拿到**。

接下来讨论一次的，由于爱丽丝是**先手**，一点可以拿到第一个一次的，但拿不到第二次的。

从小到大枚举值，分讨即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010;
int a[N], b[N];
void solve(){
	int n, flag = 0;
	cin >> n;
	for(int i = 0 ; i <= n ; i ++) b[i] = 0;
	for(int i = 1 ; i <= n ; i ++) cin >> a[i];
	for(int i = 1 ; i <= n ; i ++) b[a[i]] ++;
	for(int i = 0 ; i <= n ; i ++){
		if(b[i] == 1 && flag == 0) flag = 1;
		else if(b[i] == 1 && flag){
			cout << i << '\n';
			return;
		}
		else if(b[i] == 0){
			cout << i << '\n';
			return;
		}
	}
}

signed main(){
	int t;
	cin >> t;
	while(t --)
		solve();

	return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

### [CF1943A MEX Game 1](https://www.luogu.com.cn/problem/CF1943A)

首先 Alice 将出现次数为 $1$ 的数取走（如果没有就任取），如果除此以外所有数的出现次数都大于 $1$，那么若 Bob 删去了某个数，Alice 可以将被删去的数的另一次出现取走，这样无论如何 Alice 都能取走所有数至少一次。因此答案即最小的 $i$ 使得 $0\sim i$ 当中有出现次数为 $0$ 的数，或有至少两个出现次数为 $1$ 的数。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1943/submission/251732626)。

---

## 作者：梦应归于何处 (赞：2)

### 题目大意

爱丽丝和鲍勃在大小为 $n$ 的数组 $a$ 上进行另一场博弈。爱丽丝从一个空数组 $c$ 开始。双方轮流下棋，爱丽丝先开始。

轮到爱丽丝时，她从 $a$ 中选取一个元素，将其追加到 $c$ 中，然后从 $a$ 中删除。

轮到鲍勃时，他从 $a$ 中选取一个元素，然后从 $a$ 中删除。

当数组 $a$ 为空时，游戏结束。爱丽丝的分数定义为 $c$ 的 $\text{mex}$。爱丽丝希望最大化她的得分，而鲍勃希望最小化她的得分。如果双方都以最优方式下棋，求爱丽丝的最终得分。


### 思路

我们发现如果某一个数的个数大于 $1$，则我们无论如何都能获得这个数，所以我们只需要考虑某个数的个数小于等于 $1$ 的情况，我们从小到大枚举数，如果这个数没有则这个数就是 $\text{mex}$，否则我们发现我们只能得到个数为 $1$ 的数当中最小的那个数，其他的都拿不到，最后输出即可。

### 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp make_pair
#define pll pair<ll,ll>
#define prq priority_queue
using namespace std;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			f = -1;
		}
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
ll cnt[200005];
ll x[200005];
vector<ll> g[200005];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll _ = read();
	while (_--) {
		ll n = read();
		for (int i = 1; i <= n; i++) {
			x[i] = read();
			cnt[x[i]]++;
		}
		bool flag = 0;
		for (int i = 0; i <= n; i++) {
			if (!cnt[i]) {
				cout << i << endl;
				break;
			}
			if (cnt[i] == 1 && !flag) {
				flag = 1;
			} else if (cnt[i] == 1) {
				cout << i << endl;
				break;
			}
		}
		for (int i = 1; i <= n; i++) {
			cnt[x[i]] = 0;
		}
	}
	return 0;
}
~~~

---

## 作者：wxzzzz (赞：2)

### 题意

有一个长度为 $n$ 的序列 $a$，Alice 和 Bob 轮流对 $a$ 进行操作，Alice 是先手。

- 轮到 Alice 时，她会将 $a$ 中选一个元素移到序列 $c$ 中（$c$ 初始为空）。

- 轮到 Bob 时，他会将 $a$ 中选一个元素移除。

Alice 的目标是使 $c$ 的 $\operatorname{mex}$ 最大，Bob 的目标是使 $c$ 的 $\operatorname{mex}$ 最小，二者都会采取最优策略，求最终 $c$ 的 $\operatorname{mex}$。

### 思路

显然，如果 Alice 能使 $c$ 的 $\operatorname{mex}$ 为 $k$，就一定能使其为 $k-1$。因此 $c$ 的 $\operatorname{mex}$ 满足单调性，考虑二分答案。

接下来考虑判断一个二分的答案 $mid$ 是否合法。

对于一个合法的 $mid$，$c$ 中必然存在所有小于 $mid$ 的元素。

因此，若 $a$ 中缺少任意一个小于 $mid$ 的元素，$mid$ 不合法。

然后可以发现，对于一个出现两次及以上的 $a_i\ (a_i<mid)$，不论 Bob 取走其中哪一个，Alice 都可以取走剩下一个。

同时，若存在只出现了一次的 $a_i\ (a_i<mid)$，Alice 只能凭借先手取走其中一个。

因此，若存在两个及以上只出现了一次的 $a_i\ (a_i<mid)$，$mid$ 不合法。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005], cnt[200005];
bool check(int x) {
    for (int i = 1; i <= n; i++)
        cnt[a[i]] = 0;

    for (int i = 1; i <= n; i++)
        if (a[i] < x)
            cnt[a[i]]++;

    int sum = 0;

    for (int i = 0; i < x; i++) {
        if (!cnt[i])
            return 0;

        if (cnt[i] < 2)
            sum++;
    }

    return sum <= 1;
}
int main() {
    cin >> t;

    while (t--) {
        for (int i = 1; i <= n; i++)
            cnt[a[i]] = 0;

        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> a[i];

        int l = 0, r = n, mid, ans;

        while (l <= r) {
            mid = l + r >> 1;

            if (check(mid))
                ans = mid, l = mid + 1;
            else
                r = mid - 1;
        }

        cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：Accepted_Error (赞：1)

### [传送门](https://www.luogu.com.cn/problem/CF1943A)

## 题目翻译：
Alice 和 Bob 在玩一个游戏，Alice 每次从数组 $a$ 中选取一个数放在自己的数组 $c$ 中，然后从原数组里删除此数，Bob 则每次都从数组 $a$ 中删除一个数。

定义一个函数 $\operatorname{mex}$ 代表最小的**不在**某数组中的**非负**整数。Alice 想使自己的数组 $c$ 取到 $\operatorname{mex}$ 的最大值，而 Bob 则想使其取到最小值。假如他们都十分聪明，那么请求出最终的 $\operatorname{mex}$ 是多少。

## 思路：
我们使用桶 $f_{i}$ 记录 $i$ 在数组中的出现次数。

容易想到当 $f_{i}\geq2$，也就是存在重复的 $i$ 数时，只要 Bob 删除了 $i$ 数且 Alice 还没有选取过 $i$，那么 Alice 下一步一定会选择 $i$，因此这种情况可以不考虑。

当 $f_{i} = 1$ 时，如果 $i$ 是最小的满足 $f_{i} = 1$ 的数，那么此数一定会被 Bob 删除，所以 Alice 只能拿到第二小满足 $f_{i} = 1$ 的数。当 $f_{i} = 0$ 时，我们将此数与上一种情况的数比较大小，求出最小的数即为答案 $\operatorname{mex}$。

对于此处的处理，我们可以将 $i$ 从前往后遍历一遍，如果先找到 $f_{i} = 0$ 的数或找到第二个满足 $f_{i} = 1$ 的数时便直接输出，跳出循环。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 10;
constexpr bool testcases = true;
template<typename T>
void read(T& x)
{
	x = 0;
	ll f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	x *= f;
}
template<>
void read(string& x)
{
	x.clear();
	x += '#';
	char ch = getchar();
	while (isspace(ch)) ch = getchar();
	while (!isspace(ch)) {
		x.push_back(ch);
		ch = getchar();
	}
}
template<typename T, typename ...Args>
void read(T& x, Args&... r)
{
	read(x);
	read(r...);
}
int n;
int a[N], b[N];
void solve()
{
	memset(b, 0, sizeof(b));
	read(n);
	for (int i = 1; i <= n; i++)
	{
		read(a[i]);
		b[a[i]]++;
	}
	int cnt = 0;
	for (int i = 0; i <= n; i++)
	{
		if (b[i] == 1) cnt++;
		if (cnt == 2 || b[i] == 0)
		{
			cout << i << endl;
			return;
		}
	}
}
int main()
{
	if (testcases)
	{
		int T;
		cin >> T;
		while (T--) solve();
	}
	else solve();
	return 0;
}
```

---

## 作者：wosile (赞：1)

有点好玩的简单题。

首先，如果 Bob 拿光了序列中所有的 $x$，那么分数一定最多是 $x$。也就是答案就是 Bob 可以拿完的最小的数。

如果 $x$ 在序列 $a$ 中出现两次或以上，那么如果 Bob 拿了一个 $x$，Alice 就可以立刻拿走剩下的 $x$，这样的 $x$ 是不会被 Bob 拿完的，只有出现一次或以下的 $x$ 会被拿完。

只要轮到 Bob 拿，Bob 就可以拿走一个只出现一次的 $x$。但是因为是 Alice 先手，所以 Bob 只能拿到第二小的这样的 $x$。

注意特判最小的出现一次或以下的 $x$ 只出现了零次的情况。

时间复杂度 $O(\sum n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int a[200005];
int cnt[200005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=0;i<=n;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[a[i]]++;
		int pa=-1,pb=-1;
		for(int i=0;i<=n;i++)if(cnt[i]<2){
			if(pa==-1)pa=i;
			else if(pb==-1)pb=i; 
		}
		if(cnt[pa]<=0)printf("%d\n",pa);
		else printf("%d\n",pb);
	}
	return 0;
	//quod erat demonstrandum
}
```

---

## 作者：Wf_yjqd (赞：0)

哦哦被神奇的贪带偏思路了。

------------

其实发现一个数出现不少于 $2$ 次就一定能选上。

只需要对手选谁，我们选相同数即可。

由于先手优势，我们还可以得到一个只出现 $1$ 次的数。

将这次机会用在从小到大第一个只出现 $1$ 次的数上即可。

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+26;
int T,n,a,cnt[maxn],ans,b;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<=n;i++)
            cnt[i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a);
            cnt[a]++;
        }
        ans=0;
        b=1;
        for(int i=0;i<=n;i++)
            if(!cnt[i]){
                ans=i;
                break;
            }
            else if(cnt[i]==1){
                if(b)
                    b=0;
                else{
                    ans=i;
                    break;
                }
            }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：SJH__qwq (赞：0)

简单题。容易发现答案有单调性，所以考虑二分答案。

问题在于判定 $\text{mex}$ 的值是否可以大于等于 $p$。

设 $b_i$ 表示 $i$ 在 $a_i$ 中出现的次数。很显然，若 $\exists i\in [0,p)$ `s.t.` $b_i=0$，则显然无法满足条件。

然后考虑 $b_i\ge 2$。容易发现，对于这种 $i$，倘若 Bob 选择了一个 $i$ 则 Alice 可以立马选择另一个 $i$。这样 Bob 这一次选择就无效了。

问题在于 $b_i=1$ 的情况。明显的，设 $c$ 表示 $b_i=1$ 的 $i$ 的数量（$0\le i<p$），则若 $c=0$ 则显然无事，$c\ge 2$ 则 Alice 选择一个 Bob 可以选择另一个，必然不行；$c=1$ 则 Alice 可以抢占，满足条件。

直接二分即可。时间复杂度为 $O(n\log n)$。

---

## 作者：Luzhuoyuan (赞：0)

闲话：Div.2 C 策略错完了导致 4 发罚时调一万年没时间写 D。下大分。

Links: [[Codeforces]](https://codeforces.com/problemset/problem/1943/A) [[Luogu]](https://www.luogu.com.cn/problem/CF1943A)

### 题意简述

有一个长为 $n$ 的非负整数序列 $a$ 和一个初始为空的序列 $c$，Alice 和 Bob 玩游戏，一个回合如下：

- Alice 从 $a$ 中选出一个数并加入 $c$ 中并将其从 $a$ 中删除；
- Bob 从 $a$ 中选出一个数并将其删除。

当 $a$ 为空时游戏结束（游戏可能在某回合中间结束）。

定义一个序列的 MEX 值为该序列中最小的未出现的非负整数。Alice 希望使最终 $c$ 的 MEX 值最大化，Bob 希望最小化。两人都使用最优策略，求最终 $c$ 的 MEX 值。

$$1\le t\le 2\cdot 10^4;1\le n,\sum n\le 2\cdot 10^5;0\le a_i<n$$

### 思路

考虑最优策略是什么。

首先答案有一个显然的上界为 $\lfloor\dfrac{n+1}2\rfloor$，因为最多只能取到这么多数；同时，初始 $a$ 的 MEX 也要用来更新答案上界，因为这个值在 $a$ 中没出现，在 $c$ 中也一定不会出现。

之后，考虑 Bob 的策略。他的第一步必然是在答案范围内选择最小的仅出现一次的值删掉（没有就随便咯），这样就把答案范围缩到最小了。之后，在答案范围内的值 Alice 一定都能取到，因为每个值都出现至少两次，Alice 可以先在第二轮任选一个，之后每次都选上一轮 Bob 选的值。这样答案就是第一轮 Bob 删的值。

但是由于 Alice 先选，所以她可以尽力扩大答案范围。所以她的最优策略是第一轮先把答案范围内最小的仅出现一次的值取走（没有就随便咯），这样 Bob 就只能取第二小的了，答案就变成第二小的这个值。

所以我们的答案就是下面三者的最小值：

- $\lfloor\dfrac{n+1}2\rfloor$;
- 最小的出现 $0$ 次的值；
- 次小的出现 $1$ 次的值。

复杂度 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=2e5+5;
int T,n,a[N],num,mn;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
signed main(){
    T=read();
    while(T--){
        n=read();num=0,mn=2e5+5;for(int i=0;i<=n;i++)a[i]=0;
        for(int i=1;i<=n;i++)a[read()]++;
        int ans=(n+1)/2;
        for(int i=0;i<=n;i++)if(!a[i]){ans=min(ans,i);break;}else if(a[i]==1){num++;if(num==2){ans=min(ans,i);break;}}
        printf("%d\n",ans);
    }
    return 0;
}
```

（逃

---

