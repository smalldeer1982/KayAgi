# Game on Permutation

## 题目描述

Alice and Bob are playing a game. They have a permutation $ p $ of size $ n $ (a permutation of size $ n $ is an array of size $ n $ where each element from $ 1 $ to $ n $ occurs exactly once). They also have a chip, which can be placed on any element of the permutation.

Alice and Bob make alternating moves: Alice makes the first move, then Bob makes the second move, then Alice makes the third move, and so on. During the first move, Alice chooses any element of the permutation and places the chip on that element. During each of the next moves, the current player has to move the chip to any element that is simultaneously to the left and strictly less than the current element (i. e. if the chip is on the $ i $ -th element, it can be moved to the $ j $ -th element if $ j < i $ and $ p_j < p_i $ ). If a player cannot make a move (it is impossible to move the chip according to the rules of the game), that player wins the game.

Let's say that the $ i $ -th element of the permutation is lucky if the following condition holds:

- if Alice places the chip on the $ i $ -th element during her first move, she can win the game no matter how Bob plays (i. e. she has a winning strategy).

You have to calculate the number of lucky elements in the permutation.

## 说明/提示

In the first test case of the example, the $ 3 $ -rd element of the permutation is lucky.

In the second test case of the example, there are no lucky elements.

In the third test case of the example, the $ 2 $ -nd element of the permutation is lucky.

In the fourth test case of the example, the $ 3 $ -rd and the $ 4 $ -th element of the permutation are lucky.

## 样例 #1

### 输入

```
4
3
2 1 3
2
2 1
3
1 2 3
4
2 1 4 3```

### 输出

```
1
0
1
2```

# 题解

## 作者：Crsuh2er0 (赞：8)

# CF1860C

博弈论递推

## Solution

考虑如果 $i$ 前面存在必胜状态，或前面没有能选择的状态，那么 $i$ 为必败状态，否则前面只有能选择的必败状态，那么 $i$ 为必胜状态。

不难得出解法：遍历整个数组，在遍历的过程中，记录前面**可选择的状态** $(p_j < p_i)$ 和**可选择的必胜状态**，即可。

考虑 $i$ 只能转移到前面 $j$ $(p_j < p_i)$ 的点，记录两种状态的最小 $p_j$ 即可。

时间复杂度 $O(n)$。

```cpp
#include <bits/extc++.h>
using namespace std;
#define MAXN 300030
int n,p[MAXN];

void solve(){
    cin>>n;
    for(int i = 1;i <= n;i++) cin>>p[i];
    int canTransferTo,winState,ans = 0;
    canTransferTo = winState = INT_MAX;
    for(int i = 1;i <= n;i++){
        if(canTransferTo < p[i] && p[i] < winState){
            ++ans,winState = min(winState,p[i]);
        }
        canTransferTo = min(canTransferTo,p[i]);
    }
    cout<<ans<<endl;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("C.in","r",stdin);
    #else
    cin.tie(0) -> ios::sync_with_stdio(0);
    #endif
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：8)

纪念第一次 $15$ 分钟以内切难度高于 2B 的 2C。

**【题目分析】**

注意到一个性质：一个数 $x$ 是合法的当且仅当以这个数结尾的最长上升子序列长度为 $2$。这样 Bob 只能选择唯一的小于 $x$ 的数，Alice 无数可选，获胜。否则，若以 $x$ 结尾的最长上升子序列长度大于等于 $3$，则 Bob 选择小于 $x$ 的数 $y$ 使得以 $y$ 结尾的最长上升子序列长度为 $2$，由上面分析得 Alice 必败。

于是就转化成了求最长上升子序列的板子。树状数组优化 DP 过程即可。时间复杂度 $\mathcal O(n \log n)$。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[300005],b[300005];
void add(int x,int p){for(;x <= n;x += x & -x) a[x] = max(a[x],p);}
int query(int x){int ans = 0;for(;x;x -= x & -x) ans = max(ans,a[x]);return ans;}
int main(){
    cin >> t;
    while(t --){
        cin >> n;int ans = 0;
        for(int i = 1;i <= n;i ++) cin >> b[i],a[i] = 0;
        for(int i = 1;i <= n;i ++){
            int k = query(b[i]);
            if(k == 1) ans ++;
            add(b[i],k+1);
        }cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：chlchl (赞：7)

考场被同学误导吃了一发罚时。

## Solution
显然对于每个点只有必胜必败两种状态，考虑找到所有的必胜点。

每次可以往它左边且比它小的点移动，显然这些点会成为以 $i$ 结尾的一个上升子序列。

考虑使用 $O(n\log n)$ 的二分优化 DP 求出以每个点为结尾的最长上升子序列长度 $f_i$。

- $f_i=1$，也就是 $i$ 前面没有点可以走了，一定必败。
- $f_i=2$，$i$ 前面只有一个点，Bob 只能走到那个点，那么 Alice 就没办法操作了，必胜。
- $f_i\ge 3$，Bob 只要走到倒数第二个点 $j$，此时 $f_j=2$，Bob 必胜，则 Alice 必败。

综上，当且仅当 $f_i=2$ 时 Alice 可获胜。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N = 3e5 + 10;
int T, n, a[N], q[N], f[N];
 
void solve(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		scanf("%d", &a[i]);
		f[i] = 0, q[i] = 0;
	}
	int len = 0, cnt = 0;
	for(int i=1;i<=n;i++){
		f[i] = lower_bound(q + 1, q + len + 1, a[i]) - q;
		q[f[i]] = a[i];
		len = max(len, f[i]);
		if(f[i] == 2)
			++cnt;
	}
	printf("%d\n", cnt);
}
 
int main(){
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```


---

## 作者：Halberd_Cease (赞：4)

有一个比较好想的 $O(n^2)$ 做法，可以把格子抽象成图上的点，向能从这个格子到达的格子的点连边，图反向过后跑一遍 top 排序，给初始没有入度的节点的 $0$ 标记赋值为 $1$，如果一个节点的 $0$ 标记为 $1$，就把它能够扩展到的节点的 $1$ 标记设为 $1$，如果 $1$ 标记为 $1$，那就把能够扩展到的节点的 $0$ 标记设为 $1$，最后只有 $1$ 标记为 $1$ 的点就是答案。


我解释的可能有点抽象，但是主要不是讲这个做法所以没有理解到也没关系，我们看下面的正解。

### 正解：

**结论**：如果一个格子无法走到任何一个格子，那么选择这个格子就必败（必败格）。

正确性根据定义。

我们要把对手送进一个只能选择必败格的格子，选择这个格子就必胜，我们称这一格为必胜格。

如果一个格子可以到达必胜格，那么我们就不能选这个格子，否则对手会把我们送进必胜格，这时对手必胜。

对于每一个格子，只能转移到它前面的格子，因此从前往后递推即可，首先这个格子要能扩展到至少一个必败格但是不能扩展到必胜格，才可能是必胜格。

对于必败格，前面的格子中值最小的一定是必败格，因为无法扩展到其它点。

记录必胜格，一样只需要记录最小的必胜格，如果当前格子比最小必胜格还小那一定无法转移到任何一个必胜格，此时如果它不是一个必败格，那么就一定是一个必胜格，标记更新即可。

最后更新必败格。

```cpp
void work()
{
    int n;
    cin >> n;
    int ans = 0;
    int minn = 1919810, minm = 1919810;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (minn < x && x < minm)
        {
            ans++;
            minm = min(minm, x);
        }
        minn = min(minn, x);
    }
    cout << ans << endl;
}
```


---

## 作者：Wf_yjqd (赞：2)

挺有意思的题目。

切的还挺顺利，就是手速慢了。

有 $\operatorname{O}(n)$ 做法，但我看不懂啊。

------------

考虑这样一个博弈问题，一个状态无论是谁达到，相对的结果都是相同的。

所以可以考虑，若能转移一个状态的所有状态都是对手必败，那这个状态就是必胜的。

类似于递推，显然，初始状态中所以前缀最小值都是必败的。

可以转换为一个二维偏序问题，对于每个位置，求前面的权值比他小的状态是否都是必败的。

用两个树状数组维护一下就好了。

复杂度 $\operatorname{O}(n\log n)$。

------------

还是比较简单的。

赛时代码比较凌乱，见谅了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+84;
namespace Sherry{
    int res,T[maxn][2];
    inline int lowbit(int x){
        return x&(-x);
    }
    inline int Query(int x){
        res=0;
        while(x){
            res+=T[x][0];
            x-=lowbit(x);
        }
        return res;
    }
    inline void Modify(int x,int n){
        while(x<=n){
            T[x][0]++;
            x+=lowbit(x);
        }
        return ;
    }
    inline int Query1(int x){
        res=0;
        while(x){
            res+=T[x][1];
            x-=lowbit(x);
        }
        return res;
    }
    inline void Modify1(int x,int n){
        while(x<=n){
            T[x][1]++;
            x+=lowbit(x);
        }
        return ;
    }
}
using namespace Sherry;
int Tt,n,a,cnt;
set<int> st;
int main(){
    scanf("%d",&Tt);
    while(Tt--){
        scanf("%d",&n);
        for(int i=0;i<=n+5;i++)
            T[i][0]=T[i][1]=0;
        cnt=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a);
            if(Query1(a-1)&&!Query(a-1)){
                cnt++;
                Modify(a,n);
            }
            Modify1(a,n);
        }
        printf("%d\n",cnt);
    }
    return 0;
}
```


---

## 作者：ax_by_c (赞：1)

这题很明显是一道博弈论。

我们知道，在博弈论中有一个经典的转移：

只要先手能够把当前状态转移成一个先手必败的状态，则先手必胜，否则先手必败。

当然，这只是针对没有平局的游戏。

为什么呢？

因为现在的后手就是下一次的先手，如果要让**先手必胜**，就是**后手必败**，也就是**下一个状态的先手必败**。

如果不行，就是**下一个状态的先手必胜**，也就是**后手必胜**，所以**先手必败**。

证毕。

然后来设计一下状态。

开两个数组来记录，其中 $win_i$ 记录 chip **已经**在第  $i$ 个位置时先手是否必胜， $lose_i$ 记录 chip **已经**在第 $i$ 个位置时先手是否必败。

注意， chip 已经移动到第 $i$ 个位置了，不是先手将它移到这里的，是上一步将它移到这里的。

注意，这里的先手指的不一定是两个人中的一个。也就是说，我们只要考虑输赢，而不用考虑先手是谁。

注意，这里的先手不是整个决策过程中的先手，而是指把整个决策过程看成从当前位置开始时的先手。

那么答案就是 $ \sum_{i=1}^n [ lose_i = 1 ] $，因为 alice 第一手后的先手是 bob。

那么怎么转移呢？

首先，第一个点一定是先手必胜的，因为已经移动不了了。

然后朴素的 $ O(n^2) $ 转移显然会超时，要考虑优化。

发现每个数只能够从在左边且比当前数小的数那里转移过来。

所以我们可以开两个树状数组来记录对于每个值，当前是否有必胜或者必败的策略。

这样小的数就会被计算进前缀和，大的数则不会。

那么计算时要判断：

如果无法转移到任何策略，则先手必胜。

如果能够转移到必败策略，则先手必胜。

否则先手必败。

然后将状态再次加入树状数组即可。

核心代码如下：
```cpp
int n;
int a[N];
int tr[N];
int lb(int x)
{
	return x&(-x);
}
void update(int pos,int vu)
{
	for(;pos<=n;pos+=lb(pos))
	{
		tr[pos]+=vu;
	}
}
int Q(int pos)
{
	int res=0;
	for(;pos;pos-=lb(pos))
	{
		res+=tr[pos];
	}
	return res;
}
int tre[N];
void upd(int pos,int vu)
{
	for(;pos<=n;pos+=lb(pos))
	{
		tre[pos]+=vu;
	}
}
int Qe(int pos)
{
	int res=0;
	for(;pos;pos-=lb(pos))
	{
		res+=tre[pos];
	}
	return res;
}
bool win[N];
bool lose[N];
void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		tr[i]=tre[i]=0;
	}
	win[1]=1;
	lose[1]=0;
	update(a[1],1);
	for(int i=2;i<=n;i++)
	{
		if(!Q(a[i])&&!Qe(a[i]))
		{
			win[i]=1;
			lose[i]=0;
		}
		else if(Qe(a[i]))
		{
			win[i]=1;
			lose[i]=0;
		}
		else
		{
			win[i]=0;
			lose[i]=1;
		}
		if(win[i])
		{
			update(a[i],1);
		}
		if(lose[i])
		{
			upd(a[i],1);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(lose[i])
		{
			ans++;
		}
	}
	cout<<ans<<'\n';
}
```

---

## 作者：Mr_Az (赞：1)

## Question 问题 [CF1860C Game on Permutation](https://codeforces.com/contest/1860/problem/C)

有一个有 $n$ 个元素的全排列，Alice 先放一个筹码在第 $i$ 个元素上，在每次下一步中，当前玩家必须将筹码移动到同时向左且严格小于当前元素的任何元素。若当前玩家**无法移动**，则**该玩家胜利**。

称其中第 $i$ 个元素是幸运的仅当 Alice 把筹码放置在第 $i$ 个元素的时候，无论 Bob 怎么移动 Alice 都可以获胜。

## Analysis 分析

研究样例可发现若一旦放置在第 $i$ 个元素的时候就无法动了，那么此时肯定是 Bob 获胜。那我们需要往后找到直到这个元素可以动。那么这就是第一个幸运元素。

后面的元素何时会是幸运的呢？观察到如果 Bob 可以从第 $i$ 个元素移动到前面任意一个幸运元素，则 Bob 获胜。所以我们要满足第 $i$ 个元素的大小要小于其前面所有幸运元素。

只需要记一个数组 $mn_i$ 代表第 $i$ 个元素前最小的幸运元素即可。

## Code 代码

```cpp
const int N=3e5+8;
int T,n,p[N],mn[N];
bool f[N];
int main(){
    read(T);
    while(T--){
        read(n);int Min=inf;mn[0]=inf;ll cnt=0;
        for(rint i=1;i<=n;i++) f[i]=0;
        for(rint i=1;i<=n;i++){
            read(p[i]);
            if(p[i]<Min) f[i]=1,Min=p[i];//f[i] 代表第 i 个点 0:可以移动 1:不可移动
        }
        for(rint i=1;i<=n;i++){
            if(!f[i]){
                if(p[i]<mn[i-1]) mn[i]=min(mn[i-1],p[i]),cnt++;
                else mn[i]=mn[i-1];
            } 
            else mn[i]=mn[i-1];
        }
        printf("%lld\n",cnt);
    }
    return 0;
}
```

---

## 作者：Natori (赞：0)

>[CF1860C Game on Permutation](https://www.luogu.com.cn/problem/CF1860C)

~~人生第一场 CF，然而 10 min 写完 A 就去睡觉了（逃）。~~

------------


考虑判断每个数 $a_i$ 是否是 $\text{lucky}$ 的，然后统计到答案里。

先给出结论：

- 数 $a_i$ 是 $\text{lucky}$ 的，当且仅当以 $a_i$ 结尾的 $\text{LIS}$ 长度为 $2$。

其中 $\text{LIS}$ 表示最长 **严格** 上升子序列（当然在本题中严不严格无所谓，因为给出的 $\{a_n\}$ 是排列）。下设 $len_i$ 表示以 $a_i$ 结尾的 $\text{LIS}$ 长度。

先证必要性，分类讨论：

- $len_i=1$

$\text{Alice}$ 在第 $i$ 个位置放石子，由于 $len_i=1$，即 $i$ 之前没有比 $a_i$ 更小的数，那么$\text{Bob}$ 就没法走了，因此 $\text{Bob}$ 获胜。

所以 $len_i=1$ 不满足要求。

- $len_i \ge 3$

$\text{Alice}$ 在第 $i$ 个位置放石子，由于 $len_i \ge 3$，所以 $\text{Bob}$ 可以把石子移到以 $a_i$ 结尾的 $\text{LIS}$ 的第二个元素处，然后 $\text{Alice}$ 就只能将石子移到 $\text{LIS}$ 的第一个元素处。这样就转化成了上面 $len_i=1$ 的情况，同样是 $\text{Bob}$ 获胜。

所以 $len_i \ge 3$ 不满足要求。

必要性得证。

然后证充分性：

$\text{Alice}$ 将石子放在 $i$，由于 $len_i=2$，$\text{Bob}$ 只能将石子放在 $\text{LIS}$ 的第一个元素，$\text{Alice}$ 就没法走了，$\text{Alice}$ 获胜。

充分性得证。

------------
关于 $\mathcal{O}(n \log n)$ 求 $\text{LIS}$ 的 $\text{DP}$，可以参考[这道题](https://www.luogu.com.cn/problem/AT_chokudai_S001_h)，本篇题解就不再赘述。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
namespace Fast_In_Out{
	char buf[1<<21],*P1=buf,*P2=buf;
	#define gc (P1==P2&&(P2=(P1=buf)+fread(buf,1,1<<21,stdin),P1==P2)?EOF:*P1++)
	int read(){
		int f=1,x=0;
		char c=gc;
		while(c<'0'||c>'9'){
			if(c=='-')
			    f=-1;
			c=gc;
		}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';
			c=gc;
		}
		return f*x;
	}
	void write(int x){
		if(x<0)
			x=-x,putchar('-');
		if(x>9)
			write(x/10);
		putchar(x%10+'0');
	}
	#undef gc
}
using namespace Fast_In_Out;
const int N=3e5+8;
int n,a[N];
int stc[N],top;
void solve(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		stc[i]=0;
	top=0;
	int ans=0;
	for(int i=1,pos;i<=n;i++){
		pos=lower_bound(stc+1,stc+top+1,a[i])-stc;
		stc[pos]=a[i];
		if(pos>top)
			top=pos;
		if(pos==2)
			ans++;
	}
	write(ans),putchar('\n');
}
bool Mend;
int main(){
//	File_Work();
	fprintf(stderr,"%.3lf MB\n\n\n",(&Mbegin-&Mend)/1048576.0);
	int testnum=read();
	while(testnum--)
		solve();
	fprintf(stderr,"\n\n\n%.0lf ms",1e3*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：rabbitohh (赞：0)

提供一种 $\operatorname{O}(n)$ 做法。  
遇到博弈论问题，我们先从终止条件入手，若先手将旗子放在某个位置后，后手无法将其移动，那么是后手胜利，我们将这样的位置称为终止位置。若先手放在某个位置后，后手能且仅能将其移动到终止位置，则先手胜利，我们将这样的位置称为次级终止位置。若先手放在某个位置后，存在一种方案可以移动多次，那么后手只要选择将其移动至次级终止位置，即为后手胜利。  
因此，当且仅当一个位置是次级终止位置，这个位置是幸运的。  
我们考虑如何寻找这样的位置。我们可以正序遍历数组，维护 $minn$ 表示左边的值里最小的， $minn\_m$ 表示非终止位置里值最小的，若 $a_i < minn$，则 $i$ 是终止位置，用 $a_i$ 来更新 $minn$，若 $a_i > minn\_m$，则 $i$ 显然不是次级终止位置，跳过。若 $minn < a_i < minn\_m$，则 $a_i$ 显然不能接在前面任何一个非终止位置的后面，且能接在终止位置的后面，因此 $i$ 是次级终止位置，用 $a_i$ 更新 $minn\_m$，同时将 $ans$ 增加 $1$。  
Code：
```cpp
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<unordered_map>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<queue>
#include<map>
#include<set>
#define int long long
using namespace __gnu_pbds;
using namespace std;
const int inf=0x3f3f3f3f;
const int N=3e5+10;
int p[N];
void ans()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>p[i];
    }
    int minn=inf,minn_m=inf;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(minn_m<p[i]) continue;
        if(minn>p[i])
        {
            minn=p[i];
            continue;
        }
        ans++;
        minn_m=p[i];
    }
    cout<<ans<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        ans();
    }
    return 0;
}

```



---

## 作者：Drind (赞：0)

这题是博弈论，我们先考虑什么时候先手必胜。

显然先手必胜就是后手走完先手没得走了，也就是先手上一轮操作过后到达了只有一步就结束游戏的地方。

那么后手如果想要仿照必胜策略走的话很简单，后手只需要走到一个只有一步就结束游戏的地方即可，所以先手最初选定的位置不能走到一个只有一步就结束游戏的地方，也不能是直接结束游戏的地方（那样后手还是赢了），所以先手只能一开始选定一个只有一步就结束游戏的地方。

我们先处理哪些地方直接结束游戏，也就是偏序关系最小的几个数，显然第一个数就是，然后我们往下找一个值比他小的数，然后再找一个值比刚才那个数还小的数...构成一个下降子序列，就是直接结束游戏的几个点。

那么只有一步就结束游戏的地方要怎么处理呢？我们可以仿照前面的步骤，先选定第一个不会立刻结束游戏的地方（显然它就是一个只有一步就结束游戏的地方），然后往下找偏序关系跟他相等的即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e6+10;

int a[N];
void fake_main(){
	int n,p=1,ans=0,pos=0; a[0]=1e9;//p是立刻结束游戏的地方的指针，pos是只有一步就结束游戏的地方的指针，注意到pos的初始值不能设为1
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
		if(a[i]<a[p]){//立刻结束游戏的地方
			 p=i;
		}else{
			if(a[i]>a[pos]) continue;
			else{
				pos=i;//只有一步就结束游戏的地方
				ans++;
			}
		}
	}
	cout<<ans<<endl;
}	

signed main(){
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--) fake_main();
}

```

---

## 作者：lfxxx (赞：0)

显然是一个博弈论题，考虑 dp。

定义状态 $dp_i$ 表示先手走到 $i$ 之后是否有必胜策略，不难发现以下几点：

1. 若走到 $i$ 之后无路可走，那么就必败。

2. 若走到 $i$ 之后对手只能走到一个必败点那么这就是必胜点。

3. 除开以上两种情况都是必败点。

用 $1$ 表示必胜，$0$ 表示必败，所有操作就是对 dp 数组的单点修改和前缀最大值。

考虑用树状数组维护即可。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define lowbit(x) (x&-(x))
using namespace std;
const int maxn = 3e5+114;
const int top = 3e5;
int dp[maxn],tr[maxn];
void add(int x,int v){
	while(x<=top) tr[x]=max(tr[x],v),x+=lowbit(x);
}
int pre(int x){
	int res=0;
	while(x>0) res=max(res,tr[x]),x-=lowbit(x);
	return res;
}
int n,p[maxn],T;
int main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
cin>>T;
while(T--){
memset(dp,0,sizeof(dp));
memset(p,0,sizeof(p));
for(int i=1;i<maxn;i++) tr[i]=0;
cin>>n;
int mi=100000007;
for(int i=1;i<=n;i++){
	cin>>p[i];
	if(pre(p[i])==0&&p[i]>mi) dp[i]=1;
	else dp[i]=0;
	add(p[i],dp[i]);
	mi=min(mi,p[i]);
}
int ans=0;
for(int i=1;i<=n;i++){
	if(dp[i]==1){
		ans++;
	}
}	
cout<<ans<<'\n';
}

return 0;
}
```


---

## 作者：__ex (赞：0)

题解怎么很多都是树状数组优化呀 QaQ

其实不用那么麻烦。

- 若一个点左边没有比它小的，那必输。

- 若一个点左边有大于 $1$ 个点比它小的，那也必输（另一个人可以选一个 LIS 为 $2$ 的点，以至下次就只能选左边没有比它小的的点了，同情况 $1$）

那只用求 LIS 为 $2$ 的点的个数了。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>inline T read(){
    T a=0;bool s=0;
    char ch=getchar();
    while(ch>'9' || ch<'0'){
        if(ch=='-')s^=1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        a=(a<<3)+(a<<1)+(ch^48);
        ch=getchar();
    }
    return s?-a:a;
}
const int mn=3e5+10;
int t,n,a[mn],b[mn],len;
int main(){
    t=read<int>();
    for(int cas=1;cas<=t;cas++){
        n=read<int>();len=0;
        for(int i=1;i<=n;i++)
            a[i]=read<int>();
        int ans=0;
        b[++len]=a[1];
        for(int i=2;i<=n;i++){
            int o;
            if(a[i]>b[len])b[++len]=a[i],o=len;
            else o=lower_bound(b+1,b+len+1,a[i])-b,b[o]=a[i];
            if(o==2)ans++;
        }
        printf("%d\n",ans);
    }
    // while(1)getchar();
    return 0;
}
```

因为只用求 LIS 固定为 $2$ 的点，应该可以不用二分做到线性，由于是赛时代码，没有细想。时间复杂度 $O(n\log n)$。

---

## 作者：信息向阳花木 (赞：0)

~~关于这场我 BC 加起来都没 A 做的时间长这件事。~~

很水的 LIS 板子题。每次只能跳到比这个数小且在这个数左边的数，很显然求 LIS。注意是谁跳不了了谁赢。如果 Alice 赢，LIS 长度必须为 $2$。如果 LIS 长度为 $1$，则 Bob 跳不了，Bob 获胜。如果 LIS 长度大于 $2$，则 LIS 至少有 $3$ 个数。Bob 可以跳到 LIS 上第二个数，Alice 只能跳到第一个数。接下来 Bob 跳不了，Bob 获胜。

对于每个数求其 LIS，时间复杂度 $O(n\log_2n)$。


赛时代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 300010;

int t, n, res, cnt;
int p[N], f[N];

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		memset(f, 0, sizeof f);
		
		scanf("%d", &n);
    	for (int i = 1; i <= n; i ++ ) scanf("%d", &p[i]);
    
    	cnt = 0;
	    f[++ cnt] = p[1]; res = 0;
	    for (int i = 2; i <= n; i ++ )
	    {
	    	int k;
		    if(p[i] > f[cnt]) f[++ cnt] = p[i], k = cnt;
		    else
		    {
		        int l = 1, r = cnt;
		        while (l <= r)
		        {
		            int mid = l + r >> 1;
		            if(f[mid] >= p[i]) r = mid - 1;
		            else l = mid + 1;
		        }
		        f[l] = p[i];
		        k = l;
		    }
	        if(k == 2) res ++;
	    }
	    printf("%d\n", res);
	}
	return 0;
}
```

---

