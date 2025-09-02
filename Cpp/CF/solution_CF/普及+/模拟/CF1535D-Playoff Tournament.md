# Playoff Tournament

## 题目描述

$ 2^k $ teams participate in a playoff tournament. The tournament consists of $ 2^k - 1 $ games. They are held as follows: first of all, the teams are split into pairs: team $ 1 $ plays against team $ 2 $ , team $ 3 $ plays against team $ 4 $ (exactly in this order), and so on (so, $ 2^{k-1} $ games are played in that phase). When a team loses a game, it is eliminated, and each game results in elimination of one team (there are no ties). After that, only $ 2^{k-1} $ teams remain. If only one team remains, it is declared the champion; otherwise, $ 2^{k-2} $ games are played: in the first one of them, the winner of the game " $ 1 $ vs $ 2 $ " plays against the winner of the game " $ 3 $ vs $ 4 $ ", then the winner of the game " $ 5 $ vs $ 6 $ " plays against the winner of the game " $ 7 $ vs $ 8 $ ", and so on. This process repeats until only one team remains.

For example, this picture describes the chronological order of games with $ k = 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1535D/c7e451b61d4040a41b998ad855d9eabb637fb38d.png)Let the string $ s $ consisting of $ 2^k - 1 $ characters describe the results of the games in chronological order as follows:

- if $ s_i $ is 0, then the team with lower index wins the $ i $ -th game;
- if $ s_i $ is 1, then the team with greater index wins the $ i $ -th game;
- if $ s_i $ is ?, then the result of the $ i $ -th game is unknown (any team could win this game).

Let $ f(s) $ be the number of possible winners of the tournament described by the string $ s $ . A team $ i $ is a possible winner of the tournament if it is possible to replace every ? with either 1 or 0 in such a way that team $ i $ is the champion.

You are given the initial state of the string $ s $ . You have to process $ q $ queries of the following form:

- $ p $ $ c $ — replace $ s_p $ with character $ c $ , and print $ f(s) $ as the result of the query.

## 样例 #1

### 输入

```
3
0110?11
6
5 1
6 ?
7 ?
1 ?
5 ?
1 1```

### 输出

```
1
2
3
3
5
4```

# 题解

## 作者：HoshizoraZ (赞：8)

看到简洁的合并操作，不难想到线段树求解。

记 $f_i$ 为第 $i$ 局可能的获胜者个数。

对于**同一层**的第 $i,j \ (i<j)$ 局比赛，假设两场比赛的胜利者会在**下一轮**第 $k$ 局比赛相遇，那么可以得到如下结论：

- 若 $s_k=0$，由于第 $i$ 局的胜利者编号一定小于第 $j$ 局的胜利者，所以 $f_k=f_i$。
- 若 $s_k=1$ 则和上面的结论相反，$f_k=f_j$。
- 若 $s_k=$ `?`，那么两边的参赛者都可能获胜，有 $f_k=f_i+f_j$。

而比赛的晋级规则每次都是二选一，所以很适合用线段树来合并信息。

----

不过我们发现这题的比赛编号和线段树的节点存储编号的方式不同，根节点编号最大，叶子结点最小。

这个时候，我们可以改变存储比赛编号的方式。使得其能够被线段树结构存储，如下图（从这里开始，凡是数字外有圆括号的编号均为**新编号**）：

![](https://cdn.luogu.com.cn/upload/image_hosting/dgjf0mpx.png)

这样存储的优点是，每一局的选拔规则与原来相同，第 $(i)$ 局的胜利者与第 $(2i),(2i+1)$ 局的胜利者相关。

不过缺点也有，就是给比赛编号比较麻烦。如果能有一种办法能快速编号就好了。

如果我们试着在**同一层**更换编号的顺序，得到如下编号：

![](https://cdn.luogu.com.cn/upload/image_hosting/88sorcjt.png)

易发现，`Game x` 所替代的编号刚好是 $(2^k-x)$。同时第 $(i)$ 局的信息也与第 $(2i),(2i+1)$ 局相关。

不过需要注意，这样编号的合并操作有所不同：

- 以上图为例，`Game 7` 的选拔规则如果是字符 `0`，那么代表胜利者为编号小的参赛者，即 $f_7=f_5$。
- 而 `Game 7` 代替的点 $(1)$ 需要合并点 $(2),(3)$ 的信息，如果以相同规则合并，那么由于 $(2)<(3)$，`Game 7` 的胜利者就和 `Game 6` 的胜利者相同，即 $f_7=f_6$，与 $f_7=f_5$ 不同。

所以，如果选拔规则以 `0` 表示，那么应该是 $f_{(i)}=f_{(2i+1)}$；如果以 `1` 表示，那么 $f_{(i)}=f_{(2i)}$。

每次操作后，$f_{(1)}$ 就是当前答案。 

**代码**

```cpp
#include <cstdio>
#define INF 1e9
#define eps 1e-6
typedef long long ll;

int k, q, ans[1000010], n;
char s[1000010], c[1000010], ss[2];

void build(int i, int l, int r){
	// 只有一个 team 时赋初值 1
	if(l == r){
		ans[i] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
	// 接下来是合并操作
	if(s[i] == '0') ans[i] = ans[i << 1 | 1];
	if(s[i] == '1') ans[i] = ans[i << 1];
	if(s[i] == '?') ans[i] = ans[i << 1] + ans[i << 1 |1];
}

int main(){

	scanf("%d%s", &k, c + 1), n = (1 << k);
	for(int i = 1; i < n; i++)	// 翻转字符串就可以得到新的编号
		s[i] = c[n - i];
	scanf("%d", &q);
	build(1, 1, n);
	for(int i = 1, u; i <= q; i++){
		// 注意每次操作对后面的所有操作都有影响，所以原串也要修改
		scanf("%d%s", &u, ss + 1), u = n - u, s[u] = ss[1];
		while(u){				// 这里合并操作没有写递归
			if(s[u] == '0') ans[u] = ans[u << 1 | 1];
			if(s[u] == '1') ans[u] = ans[u << 1];
			if(s[u] == '?') ans[u] = ans[u << 1] + ans[u << 1 | 1];
			u >>= 1;
		}
		printf("%d\n", ans[1]);
	}

	return 0;
}
```

---

## 作者：Ivan422 (赞：3)

校内 S 组模拟题。

容易发现淘汰制的树是二叉树。

但是呢，这颗二叉树不太对，没法使用常规方式存储。

容易发现，把顺序倒过来就是一颗二叉树，并且可以以常规方式存储。

但是，题目的胜利又是跟选手顺序给出的，这时就要注意调换了。

知道了这件事，我们就可以~~按题意模拟即可~~使用动态规划，记录每个点胜利可能点，转移自子节点，叶子节点就是按照题意，`?` 是两个，其他是一个。答案就是 $1$ 根节点。每次修改就递归向上修改即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
// A B
const int N=6e5+10;
int q,k,p;
string s,FILE_NAME="tournament";
LL f[N];
char ch;
LL idt(int p){return((1<<k)-1-p+1);}
void rev(int p){
	if(p==0)return;
	if(idt(p)<=(1<<(k-1))){
		if(s[idt(p)]=='?')f[p]=2;
		else f[p]=1;		
	}else{
		if(s[idt(p)]=='?')f[p]=f[p*2]+f[p*2+1];
		if(s[idt(p)]=='0')f[p]=f[p*2+1];
		if(s[idt(p)]=='1')f[p]=f[p*2];
	}
	rev(p/2);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>k>>s>>q;s=" "+s;
	for(int i=(1<<k)-1;i>=1;i--){
		if(idt(i)<=(1<<(k-1))){
			if(s[idt(i)]=='?')f[i]=2;
			else f[i]=1;	
		}else{
			if(s[idt(i)]=='?')f[i]=f[i*2]+f[i*2+1];
			if(s[idt(i)]=='0')f[i]=f[i*2+1];
			if(s[idt(i)]=='1')f[i]=f[i*2];
		}
	}
	while(q--){
		cin>>p>>ch;
		s[p]=ch;
		rev(idt(p));
		cout<<f[1]<<"\n";
	}	
	return 0;
}
```

---

## 作者：Lynkcat (赞：3)

首先重标号，我们将所有的标号反转一下就会发现 $i$ 的儿子是 $i\times 2$ 和 $i\times 2+1$ 。


设 $dp[i][0/1]$ 为第 $i$ 场比赛选 $0$ 或 $1$ 的赢家个数。


容易发现若选 $0$ 的话必然是小的儿子赢，否则比虽然是大的儿子赢。也就是 $dp[i][0]=dp[i\times 2 +1][0]+dp[i\times 2 +1][1],dp[i][1]=dp[i\times 2 ][0]+dp[i\times 2 ][1]$ 。由于重标号了所以标号大的原来反而小，编号小的原来反而大。

修改操作容易发现只对当前节点到根的链的答案有影响，这条链最长为 $k$ 。

所以这道题就做完了 $O(qk)$

---

## 作者：littlebug (赞：1)

看来我还是适合写 CF 题。

## Solution

首先发现这个东西是个完全二叉树，然后叶子节点是确定的，而且这是个顺序排列，于是**左子树的所有数一定比右子树小**，发现这个性质之后这道题就基本上做出来了。

考虑 dp，设 $f_i$ 为节点 $i$ 的答案，则分讨 $s_i$ 是否可以取 $0/1$ 然后加法原理从 $i$ 的子树上加过来即可。

关于在线维护，直接跑一遍与 $p$ 有关的 dp 即可，也就是从 $p$ 开始往父亲方向依次跳，注意到树的深度只有 $k$，于是复杂度 $O(qk)$，可过。

## Code

关于实现，为了方便可以把字符串倒过来，于是 dp 的时候就可以用一个类似于线段树的方式找叶子节点和父节点了。

```cpp
int k,n,q,f[1<<18+1];
string s;

signed main()
{
	read(k),read(s),n=s.size();
	reverse(s.begin(),s.end()),s="$"+s;
	
	auto sol=[&](int i)
	{
		f[i]=0;
		
		if(i>(1ll<<k-1)-1) f[i]=1+(s[i]=='?');
		else (s[i]=='1' || s[i]=='?') && (f[i]+=f[i<<1]),
             (s[i]=='0' || s[i]=='?') && (f[i]+=f[i<<1|1]);
	};
	
	rpe(i,n,1) sol(i);
	
	read(q);
	int p; char c;
	while(q--)
	{
		read(p),read(c),p=n-p+1;
		
		s[p]=c;
		while(p) sol(p),p>>=1;
		
		write(f[1],'\n');
	}
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Rushroom (赞：1)

先把标号重新排序（根节点为 $0$）：

```cpp
int cur = s.size(), lst;
rep(i, n)
{
	lst = cur;
	cur -= 1 << i;
	for (int j = cur; j < lst; j++)
	{
		to[j] = t.size();
		t += s[j];
	}
}
s = t;
```
可以发现，节点 $k$ 的父亲是 $(k-1)/2$ ，儿子是 $k\times2+1$ 和 $k\times2+2$  

设 $f_i$ 为第 $i$ 场比赛获胜队伍有几种可能，很容易看出：

- 如果 $s_i$ 为 $0$，则 $f_i=f_{i\times2+1}$ ;

- 如果 $s_i$ 为 $1$，则 $f_i=f_{i\times2+2}$ ;

- 如果 $s_i$ 为 $?$，则 $f_i=f_{i\times2+1}+f_{i\times2+2}$ 。

就可以顺利通过了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define ld long double
#define forr(i, a, n) for (int i = a; i < n; i++)
#define rep(i, n) forr(i, 0, n)
#define repp(i, n) forr(i, 1, n + 1)
#define foreach(it, t) for (__typeof(t.begin()) it = t.begin(); it != t.end(); it++)
#define pb push_back
#define mp make_pair
#define all(a) a.begin(), a.end()
#define init(a, i) memset(a, i, sizeof(a))
#define pii pair<int, int>
#define vvi vector<vector<int>>
#define MAXN 0x3f3f3f3f
int n, q, a;
char b;
string s, t;
int to[1000006]; //记录编号的对应关系
int f[1000006];
void solve()
{
    cin >> n >> s >> q;
    int cur = s.size(), lst;
    rep(i, n)
    {
        lst = cur;
        cur -= 1 << i;
        for (int j = cur; j < lst; j++)
        {
            to[j] = t.size();
            t += s[j];
        }
    }
    s = t;
    rep(i, 1 << n + 1) f[i] = 1;
    rep(i, (1 << n) - 1)
    {
        a = to[i];
        if (s[a] == '0')
            f[a] = f[a * 2 + 1];
        if (s[a] == '1')
            f[a] = f[a * 2 + 2];
        if (s[a] == '?')
            f[a] = f[a * 2 + 1] + f[a * 2 + 2];
    }
    while (q--)
    {
        cin >> a >> b;
        a = to[a - 1];
        s[a] = b;
        while (1)
        {
            if (s[a] == '0')
                f[a] = f[a * 2 + 1];
            if (s[a] == '1')
                f[a] = f[a * 2 + 2];
            if (s[a] == '?')
                f[a] = f[a * 2 + 1] + f[a * 2 + 2];
            if (!a)
                break;
            a = (a - 1) / 2;
        }
        cout << f[0] << endl;
    }
}
int main()
{
    int T;
    T = 1;
    //cin>>T;
    while (T--)
        solve();
    return 0;
}
```


---

## 作者：elonzhang (赞：0)

# [CF1535D Playoff Tournament](https://www.luogu.com.cn/problem/CF1535D)
## 思路
很多人其实是被读入给恶心住了，那么我们就先将读入反转过来，然后把读入的每个 $p$ 变为 $|s|-p$。按题意模拟即可，可以发现题目中的比赛好像一个线段树，我们可以把每场比赛的三种状态分别看成：

- 当 $s_i=0$ 时，只取左儿子的权值
- 当 $s_i=1$ 时，只取右儿子的权值
- 当 $s_i =\ ?$ 时，取两个儿子的权值

在变化时只要单点修改，搜索到被修改的节点然后更新其权值。

## ACcode:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define endl '\n'
#define inf 0x7f7f7f7f7f7f7f7f
const int N=(1<<19)+1;
int k,n,q,i,fl[N],sum[N],lo;
string s;

void pushup(int id){
	int l=id<<1,r=id<<1|1;
	sum[id]=0;
	if(fl[id]==0||fl[id]==2) sum[id]+=sum[l];
	if(fl[id]==0||fl[id]==1) sum[id]+=sum[r];
}
void build(int id,int l,int r){
	if(l==r){
		sum[id]=1;
		return ;
	}
	int mid=(l+r)>>1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
	pushup(id);
}
void cg(int x,int id,int l,int r,int op,int dep){
	if(id==x){
		fl[id]=op;
		pushup(id);
		return ;
	}
	int mid=(l+r)>>1;
	if(x>>(lo-dep-2)&1) cg(x,id<<1|1,mid+1,r,op,dep+1);
	else cg(x,id<<1,l,mid,op,dep+1);
	pushup(id);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
  freopen("tournament.in","r",stdin);
  freopen("tournament.out","w",stdout);
//↑以上为初始化 ↑
//------------------------------
	cin >> k >> s;
	n=(1<<k);
	for(i = s.size()-1;i>=0;--i)
	 fl[n-i-1]=(s[i]=='?'?0:(s[i]=='0'?1:2));
	build(1,1,n);
	cin >> q;
	for(i = 1;i<=q;++i){
		int x;char c;
		cin >> x >> c; 
		x=n-x;
		lo=ceil(log2(x));
//		for(int i = 1;i<n;++i) cout << fl[i] << ' ';
//		cout << endl;
		cg(x,1,1,n,(c=='?'?0:(c=='0'?1:2)),0);
		cout << sum[1] << endl;
	}
//	for(int i = 1;i<n;++i) cout << fl[i] << ' ';
	return 0;
}
```

---

## 作者：Hope5365 (赞：0)

我也不知道这是什么算法，兴许是 `DP` 吧。

广告：在[博客](https://www.luogu.com.cn/article/lal0zt15)内食用更佳！

设 $f_i$ 表示比赛到第 $i$ 场时的可能情况数。这里再加一个辅助数组 $son_{i,j}$ 代表第 $i$ 场比赛的第 $j$ 个儿子节点，$fa_i$ 代表第 $i$ 场比赛的父亲节点

那这里的儿子节点和父亲节点是什么意思呢？

我们把题目里面的图片翻转过来：

![](https://cdn.luogu.com.cn/upload/image_hosting/ymt1tqpi.png)

有没有发现很像二叉树？

这里的第 $i$ 个节点的父亲就是第 $i$ 个节点决出胜负以后，胜出的队伍打的下一场比赛。

$son_i$ 和 $fa_i$ 我们待会再考虑，先考虑 $f_i$ 怎么推导。

在第一轮比赛的时候，没有其他的可能，所以当 $i \le 2^{k-1}$ 时（这里代表第一轮比赛的场数）：
- 当 $s_i$ 为 $1$ 或 $2$ 时，$f_i = 1$
- 当 $s_i$ 为 `?` 时， $f_i = 2$

考虑转移。

我们知道 $son_{i,1}$ 一定小于 $son_{i,2}$，那么我们便可以确定 $s_i = 1$ 和 $s_i = 2$ 的情况了。

那 $s_i$ 为 `?` 的情况呢？因为这两个儿子都有可能赢，所以我们只需要将两个儿子的可能加起来就可以了。

我们先预处理一遍。因为我们每一次修改 $i$ 都只会影响 $i$ 和 $i$ 的父节点，就可以在每一次修改时用 $O(k)$ 的时间复杂度完成全局修改。

那怎么计算 $son_i$ 和 $fa_i$ 呢？

我们设现在枚举到了第 $i$ 轮比赛，那么怎么记录 $i$ 的儿子呢？

设用 $j$ 枚举第 $i$ 轮，用 $k$ 枚举第 $i - 1$ 轮，只要 $j$ 每比一轮比赛， $k$ 就比两轮比赛，在过程中记录 $son_i$。 $fa_i$ 同理。记录出 $son_i$ 和 $fa_i$ 时，就可以按照上述方法转移了。

最后是 AC 代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define int long long

const int N = 1 << 20,M = 20;
int k,n,cs[N],q,f[N],son[N][4],fa[N];
char a[N];

signed main()
{
	cin >> k;
	n = (1 << k) - 1;
	int tot = (1 << (k - 1)),sum = 0;
	for(int i = 1;i <= n;i ++) cin >> a[i];
	for(int i = 1;i <= (1 << (k - 1));i ++)
	{
		if (a[i] == '1' || a[i] == '0') f[i] = 1;
		else f[i] = 2;
	}
	for(int i = 2;i <= k;i ++)
	{
		int last_start = sum + 1;
		sum += (1 << (k - i + 1));
		int now_start = sum + 1;
		for(;last_start <= sum;)
		{
			son[now_start][1] = last_start;
			fa[last_start] = now_start;
			last_start ++;
			son[now_start][2] = last_start;
			fa[last_start] = now_start;
			last_start ++,now_start ++;
		}
	}
	for(int i = tot + 1;i <= n;i ++)
	{
		if (a[i] == '1') f[i] = f[son[i][2]];
		else if (a[i] == '0') f[i] = f[son[i][1]];
		else f[i] = f[son[i][1]] + f[son[i][2]];
	}
	cin >> q;
	while (q --)
	{
		int i;
		char c;
		cin >> i >> c;
		a[i] = c;
		while (i != 0)
		{
			if (i <= (1 << (k - 1)))
			{
				if (a[i] == '?') f[i] = 2;
				else f[i] = 1;
			}
			else
			{
				if (a[i] == '1') f[i] = f[son[i][2]];
				else if (a[i] == '0') f[i] = f[son[i][1]];
				else f[i] = f[son[i][1]] + f[son[i][2]];
			}
			i = fa[i];
		}
		cout << f[n] << endl;
	}
	return 0;
}
```

---

## 作者：_299817_ (赞：0)

## Part 1：主要思路

通过观察题目中的图，我们不难发现，这个结构和线段树一模一样，于是我们考虑用类似线段树的方法来解决这道题。

然后我们考虑题目中给我们每个点对应的字符有什么用。

易知题目中的每一层的编号是单调的，所以不论我们上一层的结果是什么，只要这一层的字符不是问号，它的最后答案属于哪边就与答案无关。

然后我们来考虑具体每个字符对应的操作是什么（也就类似于考虑线段树中的 `PushUp` 函数），`0` 对应着从右子节点上传，`1` 对应着从左子节点上传，`?` 对应着这个节点的值是它的两个子节点值的和，再把叶子节点赋值成 $1$ 即可。

修改操作我们只需要从修改的节点开始不断向上更新即可。

注意这里的节点的编号与线段树的节点编号不同，不难发现两者的和为 $2^k$，我们可以通过这个关系算出每个字符对应这哪个节点。

## Part 2：代码
```cpp
// LUOGU_RID: 143597390
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#include<list>
#define rep(i, l, r) for(int i = signed(l); i <= signed(r); i++)
#define per(i, l, r) for(int i = signed(l); i >= signed(r); i--)
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

const int MAXN = 300010;

struct node{ // 定义线段树的节点
    int l, r; // 每个节点所代表的区间
    char c; // 每个节点对应的字符，注意这里叶子节点是没有对应字符的，应为每个人不可能和自己比赛
    int val; // 每个节点的值
};

int k, q;
node tree[300010 << 2]; // 这里开大一点， 之前开小了被卡了

void build(int l, int r, int now){ // 建树
    tree[now].l = l, tree[now].r = r; // 记录区间
    if(l == r){ // 如果是叶子节点
        tree[now].val = 1; // 叶子结点的值为 1
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, now * 2);
    build(mid + 1, r, now * 2 + 1); // 下传
    if(tree[now].c == '1'){ // 计算每个节点的值，按照上面给的公式算即可
        tree[now].val = tree[now * 2].val;
    }else if(tree[now].c == '0'){
        tree[now].val = tree[now * 2 + 1].val;
    }else{
        tree[now].val = tree[now * 2].val + tree[now * 2 + 1].val;
    }
}

void update(int now){ // 修改，同时也只需要不断上传更新
    if(now == 0){
        return;
    }
    if(tree[now].c == '1'){ // 跟上面的计算方法是一样的
        tree[now].val = tree[now * 2].val;
    }else if(tree[now].c == '0'){
        tree[now].val = tree[now * 2 + 1].val;
    }else{
        tree[now].val = tree[now * 2].val + tree[now * 2 + 1].val;
    }
    update(now / 2); // 往上走
}

int main(){
    #ifdef QwQ_ATM
        freopen("input.in", "r", stdin);
        freopen("output.out", "w", stdout);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> k;
    int n = (1 << k);
    rep(i, 1, n - 1){
        cin >> tree[n - i].c; // 输入，转换节点
    }
    build(1, n, 1); // 建树
    cin >> q;
    while(q--){
        int p;
        char op;
        cin >> p >> op;
        p = n - p; // 转换节点
        tree[p].c = op;
        update(p); // 修改更新
        cout << tree[1].val << endl; // 输出
    }
    return 0;
}
```


---

## 作者：Xiphi (赞：0)

考虑转化题意。发现每次比赛可以抽象成一颗完全二叉树，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rsutyw1t.png)

然后我们发现这个东西有点像线段树（但要注意到它是翻过来的），$i$ 的“左右儿子分别是 $2\times i$ 以及 $2\times i+1$”这一特点。考虑用 $tr_i$ 表示第 $i$ 场比赛的胜者有几个。转移式有三种：

- $s_i=1$，$tr_i=tr_{i\times 2}$。
- $s_i=0$，$tr_i=tr_{i\times 2+1}$。
- $s_i= \text{?}$，$tr_i=tr_{i\times 2}+tr_{i\times 2+1}$。

每次询问就变得很简单了，因为每次修改的东西不超过 $\log n$ 个，$n$ 是 $2^k$。然后每次回答 $tr_1$ 就行。

最后我们回答一下为什么要把原串翻过来这个问题，因为在转移过程中，我们很难找到当前位置对应哪一场比赛，翻过来后，编号对应的比赛就是 $2^k-id$，$id$ 是现在转移的编号。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k,T;
int tr[1000005];
void build(int p,int l,int r){
	if(l==r){
		tr[p]=1;
		return ;
	}
	int mid=l+r>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	if(s[p]=='0') tr[p]=tr[p<<1|1];
	else if(s[p]=='1') tr[p]=tr[p<<1];
	else if(s[p]=='?') tr[p]=tr[p<<1|1]+tr[p<<1];
}
void change(int p,char c){
	s[p]=c;
	while(p){
		if(s[p]=='0') tr[p]=tr[p<<1|1];
		else if(s[p]=='1') tr[p]=tr[p<<1];
		else if(s[p]=='?') tr[p]=tr[p<<1|1]+tr[p<<1];
		p>>=1;
	}
	cout<<tr[1]<<'\n';
}
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>k>>s;
	reverse(s.begin(),s.end());//编号是翻过来的
	s=" "+s;
	int n=(1<<k);
	build(1,1,n);
	cin>>T;
	while(T--){
		int p;
		char c;
		cin>>p>>c;
		p=n-p;
		change(p,c);
	}
	return 0;
}
```

---

## 作者：meyi (赞：0)

(注：本文中的 $n$ 指的是原题中的 $2^k-1$)

简述一下如何转换模型：将给定的字符串倒着按bfs序建树，$n$ 号节点为根，非叶子节点对应的字符为 `0` 则向左儿子连边， 为 `1` 则向右儿子连边，为 `?` 则同时向两个儿子连边，叶子节点对应的字符为 `0` 或 `1` 则大小设为 1，为 `?` 则大小设为 2。答案就是 $n$ 号节点的子树大小。建树的时间复杂度为 $O(n)$。

修改操作只需将当前节点对应连边进行修改，并更新自己到根节点的路径上所有点的子树大小即可，由于这是一棵深度为 $k$ 的完全二叉树，所以一次修改操作的时间复杂度为 $O(k)$。

总时间复杂度为 $O(n+qk)$，可以通过本题。

细节实现就看代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define DEBUG(k...) fprintf(stderr,k)
typedef long long ll;
template<class T>inline bool chmax(T &x,const T &y){return x<y?x=y,true:false;}
template<class T>inline bool chmin(T &x,const T &y){return x>y?x=y,true:false;}
const int maxn=3e5+10;
int siz[maxn],f[maxn],l[maxn],r[maxn],m,n,t_case;
char s[maxn],op[maxn];
ll ans;
queue<int>q;
inline void build1(){
	q.push(n);
	ri cnt1=n,cnt2=n;
	while(q.size()){
		ri p=q.front();q.pop();
		op[p]=s[cnt2--];
		if(cnt1)r[p]=--cnt1,q.push(cnt1);
		if(cnt1)l[p]=--cnt1,q.push(cnt1);
	}
}
inline void update(int p){
	if(!l[p]&&!r[p]){
		if(op[p]=='?')siz[p]=2;
		else siz[p]=1;
		return;
	}
	if(op[p]=='?')siz[p]=siz[l[p]]+siz[r[p]];
	else{
		if(op[p]=='0')siz[p]=siz[l[p]];
		if(op[p]=='1')siz[p]=siz[r[p]];
	}
}
inline void build2(int p){
	if(!l[p]&&!r[p]){
		if(op[p]=='?')siz[p]=2;
		else siz[p]=1;
		return;
	}
	f[l[p]]=p;
	build2(l[p]);
	f[r[p]]=p;
	build2(r[p]);
	update(p);
}
inline void modify(int pos,char x){
	op[pos]=x;
	update(pos);
	while(f[pos])pos=f[pos],update(pos);
}
int main(){
	scanf("%d%s",&n,s+1);
	n=(1<<n)-1;
	build1();
	build2(n);
	scanf("%d",&m);
	while(m--){
		ri pos;
		char x[5];
		scanf("%d%s",&pos,x);
		modify(pos,*x);
		printf("%d\n",siz[n]);
	}
	return 0;
}
```

---

## 作者：Ryanhao (赞：0)

# [CF1535D（淘汰赛）](https://www.luogu.com.cn/problem/CF1535D)

模拟（类似线段树和树状数组）

## 思路（解题过程）

处理字符串 $\to$ 推导初始答案（建树）$\to$ 单点修改，单点查询。

### 处理字符串

为什么要处理字符串？

对于样例 `0110?11` 来说，我们可以很快的发现，这是二叉树的**后序遍历**（左，右，根）。

由于字符串长度 $=2^k-1$，我们发现这是一棵**满二叉树**，然后就想到**完全二叉树**，然后又想到它的存储方式：当前节点为 $u$, 左儿子在 $2u$，右儿子在 $2u+1$。为了把树按照这种方式存储，我们需要把他从**后序遍历**变成**先序遍历**（根，左，右）。

第一步：将字符串整体翻转，样例翻转过后，可得`11?0110`。然后我们发现它变成了右，左，根的奇妙遍历方式。模拟一下发现，为了把他变成正常先序遍历形式，我们需要**将字符串里每一层都翻转**。

第二步：将字符串里每一层都翻转。样例每一层翻转过后，可得`1?10110`。
```cpp
int k,q;
scanf("%d\n%s%d",&k,G+1,&q);
//------处理字符串
len = pow(2,k)-1; // 求长度
reverse(G+1,G+len+1); // 第一步：整体翻转
for (int i = 1, l = 1; i <= len+1; i<<=1) { // 第二步：翻转每一层
  // i 枚举长度，l枚举每层开头。
  reverse(G+l,G+i+l); 
  l += i; // 下一层在本层末尾的下一位。
} 
```
然后我们就能拿完全二叉树的存储方法来存了。
### 推导初始答案（建树）

首先明确一点：对于任意两个队伍，编号小的在编号大的右边。

#### 叶子

按题意，当叶子节点是 `?` 时，两个队伍都可能晋级。否则，只能晋级一个。

#### 非叶子

当自己是 `?` 时，两个子结点的“候选晋级队伍”都有可能晋级。否则，只能晋级一个子结点的。

```cpp
// 递归求初始答案
int init(int u) {
  if (u > len/2) { // 叶子
    if (G[u] == '?') val[u] = 2; // 两支队伍都会晋级
    else val[u] = 1; // 否则只有一个
    return val[u]; // 模拟晋级
  }
  int se0 = init(lch(u)), se1 = init(rch(u)); // 非叶子
  if (G[u] == '1') val[u] = se1; // 大的（右儿子）
  else if (G[u] == '0') val[u] = se0; // 小的（左儿子）
  else val[u] = se0+se1; // 两边的队伍都会晋级。
  return val[u]; // 模拟晋级
}

```

### 单点修改，单点查询
#### 处理 $p$

由于刚才处理过字符串，所以要处理一下 $p$。

首先，字符串颠倒过一次。所以 $p$ 也要在整体颠倒一次。

然后，因为每层都颠倒了一次，所以 $p$ 也要在自己的层内颠倒一次。

```cpp
int does(int p) {
  p = len-p+1; // 整体颠倒
  for (int i = 1, j = 1; j <= len; i<<=1,j+=i) { // 找到p所在的层，i表示当前层的长度，j表示当前层的最后一个节点的位置。
    if (p <= j) {
      // 层内颠倒，我只讲1遍：
      /*
        1.把它前面的节点先拿走，一共i-1个。
        2.这下剩的就是当前层的节点了，颠倒。
        3.把拿走的节点放回去。
        效果如下。
      */
      return i-(p-(i-1)/*1.*/)+1/*2.*/+(i-1)/*3.*/;
    }
  }
}

```

#### 修改

每次修改都整体再次求解，你问评测机愿不愿意，你的良心愿不愿意。（该做法时间复杂度 $O(n\log_2n)$）

所以我们只需要修改从自己到根的路径上的节点的值即可。注意到之前推初始答案时我们把他存在一个 $val$ 数组里，现在，我们就可以利用他来求解了。该做法时间复杂度 $O(\log_2n)$）

```cpp

void change(int u) {
  for (;u;u>>=1) { // 莫名像树状数组？
    if (u > len/2) { 
      if (G[u] == '?') val[u] = 2;
      else val[u] = 1;
      continue;
    }
    int se0 = val[lch(u)], se1 = val[rch(u)];
    if (G[u] == '1') val[u] = se1;
    else if (G[u] == '0') val[u] = se0;
    else val[u] = se0+se1;
    
  }
}
// 和init()几乎一模一样，只是把递归换成递推而已。
```

完结撒花！（总时间复杂度 $O(n\log_2n)$）

## ACCode

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define open(s) freopen(s".in","r",stdin);freopen(s".out","w",stdout)
using namespace std;
#define lch(x) (x<<1)
#define rch(x) (x<<1|1)

char G[2700005];
int val[2700005],len;
int does(int x) {
  x = len-x+1;
  for (int i = 1, j = 1; j <= len; i<<=1,j+=i) {
    if (x <= j) {
      return i-(x-(i-1))+1+(i-1);
    }
  }
}

int init(int u) {
  if (u > len/2) { // leaf
    if (G[u] == '?') val[u] = 2;
    else val[u] = 1;
    return val[u]; 
  }
  int se0 = init(lch(u)), se1 = init(rch(u));
  if (G[u] == '1') val[u] = se1;
  else if (G[u] == '0') val[u] = se0;
  else val[u] = se0+se1;
  return val[u];
}
void change(int u) {
  for (;u;u>>=1) {
    if (u > len/2) { // leaf
      if (G[u] == '?') val[u] = 2;
      else val[u] = 1;
      continue;
    }
    int se0 = val[lch(u)], se1 = val[rch(u)];
    if (G[u] == '1') val[u] = se1;
    else if (G[u] == '0') val[u] = se0;
    else val[u] = se0+se1;
    //printf("val[%d]=%d\n",u,val[u]);
  }
}

int main() {
  //open("tournament")
  int k,q;
  scanf("%d\n%s%d",&k,G+1,&q);
  len = pow(2,k)-1;
  reverse(G+1,G+len+1);
  for (int i = 1, l = 1; i <= len+1; i<<=1) {
    reverse(G+l,G+i+l);
    l += i;
  }
  //printf("%s\n",G+1); 
  init(1);
  while(q--) {
    int x;
    char op;
    scanf("%d %c",&x,&op);
    x = does(x);
    G[x] = op;
    change(x);
    printf("%d\n",val[1]);
  }
  return 0;
} 

```

## 后记

我的做法其实有点复杂，体现在树的存储上。欢迎大佬来研究更方便的做法！

### update

2024OCT18：被打回，原因：键盘又双叒叕坏了，后文被整段粘贴到前面去了。修改已知问题，增加时间复杂度表示。

---

