# Neo's Escape

## 题目描述

Neo 想要逃离矩阵世界。在他面前有一排 $n$ 个按钮，每个按钮都有一个整数权重：$a_1, a_2, \ldots, a_n$。

Neo 被固定住了，但他可以创建和移动克隆体。这意味着他可以按任意顺序执行以下两种操作，次数不限：

1. 在特定按钮前创建一个克隆体。
2. 将现有的克隆体向左或向右移动一个位置。

当一个克隆体位于尚未被按下的按钮前时（无论他是被创建还是被移动的），他会立即按下该按钮。如果按钮已经被按下过，克隆体不会做任何操作——每个按钮只能被按下一次。

为了成功逃脱，Neo 需要以特定的顺序按下所有按钮：按钮权重的序列必须是非递增的。也就是说，如果 $b_1, b_2, \ldots, b_n$ 是按按钮的顺序对应的权重，那么必须满足 $b_1 \geq b_2 \geq \cdots \geq b_n$。

你的任务是确定 Neo 需要创建的最少克隆体数量，以便能够以有效顺序按下所有按钮。

## 说明/提示

在第一个测试用例中，Neo 可以按以下方式操作：

1. 在第五个按钮（权重为 $5$）前创建一个克隆体。
2. 在第一个按钮（权重为 $4$）前创建第二个克隆体。
3. 将第二个克隆体从第一个按钮移动到第二个按钮（权重为 $3$）。
4. 将第二个克隆体从第二个按钮移动到第三个按钮（权重为 $2$）。
5. 将第一个克隆体从第五个按钮移动到第四个按钮（权重为 $1$）。

这样，按钮按下的顺序将是 $5 \rightarrow 4 \rightarrow 3 \rightarrow 2 \rightarrow 1$，满足要求。可以证明，创建的克隆体数量是最小的。

在第二个测试用例中，Neo 可以按以下方式操作：

1. 在第二个按钮（权重为 $1$）前创建一个克隆体。
2. 将该克隆体从第二个按钮移动到第三个按钮（权重为 $1$）。
3. 将该克隆体从第三个按钮移回第二个按钮（已被按下）。
4. 将该克隆体从第二个按钮移动到第一个按钮（权重为 $1$）。

这样，按钮按下的顺序将是 $1 \rightarrow 1 \rightarrow 1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
5
4 3 2 1 5
3
1 1 1
6
7 8 1 5 9 2
10
1 7 9 7 1 10 2 10 10 7```

### 输出

```
2
1
2
3```

# 题解

## 作者：c_legg (赞：1)

先说结论：高度去重然后数极大值。

再说理由：首先应发现，如果 $a_i=a_{i+1}$，那在哪里放克隆体都可以，所以去重；然后发现去重后所有不是极大值的位置上都**不用**放克隆体，而是可以选择等待旁边的克隆体过来按按钮；而是极大值的位置不可能等旁边的克隆体过来，故要放一个克隆体。所以得出上面的结论。

[代码](https://codeforces.com/contest/2108/submission/317989292)

---

## 作者：ZAYNAab (赞：1)

## 解题分析
每一个克隆的 Neo 都可以将自己附近比自己序号小的处理了。

所以我们只用判断哪些位置比两边都要大即可。

记得要将数组清空到下标 $n+1$，因为比大小要用。

然后将连续的重复元素化为同一个元素即可处理细节。

```cpp
//赛时代码 317989183
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[200005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n;
        int ans=0,front=0,cnt=0;
        for(int i=1;i<=n+1;i++)a[i]=0;
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            if(x==front)continue;
            else{
                front=x;
                a[++cnt]=x;
            }
        }
        for(int i=1;i<=cnt;i++){
            if(a[i]>a[i-1] and a[i]>a[i+1])ans++;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：Eous (赞：1)

## 题意

给你一个长度为 $n$ 的数组 $a$。你可以选择在某个位置创建一个克隆体。一个克隆体可以做以下事情：

- 删除它当前位置上的数。
- 往左或者往右走一格。能从 $u$ 走到 $v$ 当且仅当 $v$ 这个位置的数被删了或者 $a_u \ge a_v$。

求出删完 $a$ 数组里的所有数所需的最小克隆体个数。

## 题解

为了最优我们肯定是要让一个克隆体一次删掉一个区间的。所以我们可以 dp。

设 $dp_i$ 表示删除前 $i$ 个数所需的最小克隆体个数。有转移：$dp_i = \min \{dp_{j - 1} + 1\}$，但是能转移当且仅当区间 $[i,j]$ 能被一个克隆体一次删完。如何判断？

> 设我们要删的是区间 $[l,r]$。钦定一个初始位置 $i$，这个区间能删完当且仅当
>
> 1. 对于 $\forall j \in (l,i]$，有 $a_{j - 1} \le a_j$。
> 2. 对于 $\forall j \in [i,r)$，有 $a_{j} \ge a_{j + 1}$。
>
> 证明很简单，这里不说了。

怎么维护？我们对于每个 $i$ 维护一个 $lft_i$ 表示 $(lft_i,i]$ 这个区间满足条件 1。再维护一个 $rht_i$ 表示 $[i,rht_i)$ 满足条件 2。维护方法见代码。

那么维护这么个东西有什么用呢？我们结合上面的条件可以发现，$[lft_i,rht_i]$ 这个区间的所有子区间肯定都是合法的。感性理解，$dp$ 一定是单调不减的，所以转移的 $j$ 肯定是越小越好。所以对于每个 $i$，$[lft_i,rht_i]$ 区间内的每个点所对应的最优的 $j$ 肯定不会在 $lft_i$ 右边。我们用一个线段树维护最优决策点 $j$，支持区间取 $\min$，单点查询。对于每个 $i$，我们让区间 $[lft_i,rht_i]$ 内的每个数都对 $lft_i$ 取 $\min$。转移的时候单点查询就行。

## code

```cpp
#include<bits/extc++.h>
#define int long long
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const int maxn = 2e5 + 5;
int n;
int tree[maxn << 2];
int a[maxn],dp[maxn];
int lft[maxn],rht[maxn];
void build(int l,int r,int rt)
{
    tree[rt] = inf;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l,mid,ls);
    build(mid + 1,r,rs);
}
void upd(int ql,int qr,int x,int l = 1,int r = n,int rt = 1)
{
    if (ql <= l && r <= qr)
    {
        tree[rt] = min(tree[rt],x);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid)
        upd(ql,qr,x,l,mid,ls);
    if (qr > mid)
        upd(ql,qr,x,mid + 1,r,rs);
}
int que(int pos,int res = inf,int l = 1,int r = n,int rt = 1)
{
    res = min(res,tree[rt]);
    if (l == r)
        return res;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return que(pos,res,l,mid,ls);
    else
        return que(pos,res,mid + 1,r,rs);
}
void solve()
{
    scanf("%lld",&n);
    for (int i = 1; i <= n; i++)
        scanf("%lld",a + i);
    a[0] = a[n + 1] = inf;
    for (int i = 1; i <= n; i++)
    {
        if (a[i - 1] <= a[i])
            lft[i] = lft[i - 1];
        else
            lft[i] = i;
    }// 维护 lft[i]
    for (int i = n; i >= 1; i--)
    {
        if (a[i] >= a[i + 1])
            rht[i] = rht[i + 1];
        else
            rht[i] = i;
    }// 维护 rht[i]
    build(1,n,1);// 线段树初始值 inf
    for (int i = 1; i <= n; i++)
        upd(lft[i],rht[i],lft[i]);// 区间对 lft[i] 取 min
    for (int i = 1; i <= n; i++)
    {
        int j = que(i);// 单点查询
        dp[i] = dp[j - 1] + 1;// dp 转移
    }
    printf("%lld\n",dp[n]);
}
signed main()
{
    int t;
    scanf("%lld",&t);
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：Ag2WO4 (赞：1)

由于不增顺序操作只禁阻了从低到高的按钮操作，所以找到所有单台机器无法跨越的“谷地”，即连续若干个相同的数比其左右都低，答案为谷地数加一（两边肯定不是谷地，谷地外还有要按的按钮）。复杂度 $O(n)$。
```python
for _ in range(int(input())):
    n=int(input());a=list(map(int,input().split()));b=c=0
    for j in [a[i+1]-a[i]for i in range(n-1)]:
        if j==0:continue
        if b<0 and j>0:c+=1
        b=j
    print(c+1)
```

---

## 作者：AK_400 (赞：0)

首先，可以把权值相同且连续的按钮缩成一个。

按权值从大到小枚举。

如果一个按钮旁边有被按过的按钮，那么可以直接按，因为一定有一个机器人可以经过若干个按过的按钮到达这个按钮。

否则在这个位置增加一个机器人，因为从大到小枚举，所以没按过的按钮的权值一定小于等于当前按钮。

由于我们把权值相同且连续的按钮缩成一个，所以与当前的相邻的没被按的按钮只能权值更低，其他机器人无法在不经过这两个按钮的情况下按当前按钮。

code：


```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace __gnu_pbds;
using namespace std;
#define fls fflush(stdout)
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,c),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int n,w;
map<int,vector<int>>mp;
bool vis[200005];
void slv(){
    mp.clear();
    for(int i=1;i<=n;i++)vis[i]=0;
    read(n);
    int tot=0,lst=0;
    for(int i=1;i<=n;i++){
        read(w);
        if(w==lst)continue;
        mp[w].push_back(++tot);
        lst=w;
    }
    int ans=0;
    for(auto it=mp.end();it!=mp.begin();){
        it--;
        for(int x:it->second){
            if(!vis[x+1]&&!vis[x-1])ans++;
            vis[x]=1;
        }
    }
    cout<<ans<<endl;
    return;
}   
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：zzldd (赞：0)

可以往任意位置放人，每个人可以从权值大的地方往小的地方走，问最少需要多少人能走完。\
注意到对于每个单峰区间，只需要 1 人就可以走完，所以只需要统计单峰区间的数量即可。\
使用 $ f $ 记录当前状态，数值递增时值为 $0$，数值递减时值为 $1$，当由递减状态变为递增状态时，答案数量 $+1$。由于我们统计时没有记录第一个单峰区间，所以答案数 $ans$ 初始值为 $1$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
void sol(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int ans=1,f=0;
	if(a[1]>a[2]) f=1;
	for(int i=1;i<=n-1;i++){
		if(a[i]>a[i+1]&&f==0) f=1;
		if(a[i]<a[i+1]&&f==1){
			f=0;
			ans++;
		}
	}cout<<ans<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--) sol();
}

```

---

## 作者：Manki23333333 (赞：0)

#### 闲话

交错题了，B 题交到 C 题上了，令人汗颜！

#### 简化题目（非原题目翻译，是原题目的等价描述）

现在有一座山，可以看成一个数组 $a$，$a_i$ 代表位置 $i$ 的高度。你可以在任意一个位置上倒水（水没有厚度），水会从高处往低处流。与 Minecraft 中的水不一样，它可以在平地上流无限远。求最少的倒水次数以覆盖整座山。

#### 解析

注意到如果对于 $i$，存在 $i < j$ 且 $a_i \le a_j$ 且 $\min (a_{i+1}, a_{i+2}, \cdots, a_{j - 1}) \ge a_i$ ，那么在 $j$ 倒水一定可以覆盖掉 $i$，$j < i$ 同上，并且这也是必要条件。

而如果有 $i < j < k$，那么如果 $k$ 倒水可以覆盖 $i$，$j$ 倒水也可以覆盖 $i$；反之，如果 $j$ 流不到 $i$，$k$ 也流不到 $i$。

所以对于一个 $i$ 每次我们只需要考虑一个最小的 $j > i, a_j > a_i$ 或一个最大的 $k$ 使得 $k < i, a_k > a_i$。如果 $j$ 或 $k$ 能够流到 $i$，那么 $a_i$ 就一定**不需要**倒水，不需要统计答案。

上述的 $j, k$ 显然跑单调栈就可以求出来，判断能不能流是个简单的 RMQ。RMQ 自然不需要赘述，使用各种各样的算法都可以解决。

以上。

#### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a [200005], pre [200005], nxt [200005];

stack <int> st;

int f [200005] [32];
int t_log2 [200005];

int query (int x, int y) {
	int p = t_log2 [y - x + 1];
	
	return min (f [x] [p], f [y - (1 << p) + 1] [p]);
}

void init_st () {
	for (int j = 1 ; (1 << j) <= n ; j ++) {
		for (int i = 1 ; i + (1 << j) - 1 <= n ; i ++) {
			f [i] [j] = min (f [i] [j - 1], f [i + (1 << (j - 1))] [j - 1]);
		}
	}
	
	for (int i = 2 ; i <= n ; i ++) {
		t_log2 [i] = t_log2 [i - 1] + ((i & (i - 1)) == 0);
	}
}

void Turn () {
	decltype (st) (). swap (st);
	cin >> n;
	
	for (int i = 1 ; i <= n ; i ++) {
		cin >> a [i];
		pre [i] = nxt [i] = 0;
		f [i] [0] = a [i];
	}
	
	init_st ();
	
	for (int i = 1 ; i <= n ; i ++) {
		while (!st. empty () && a [st. top ()] <= a [i]) {
			nxt [st. top ()] = i;
			st. pop ();
		}
		
		if (!st. empty ()) {
			pre [i] = st. top ();
		}
		
		st. push (i);
	}
	
	int ans = 0;
	for (int i = 1 ; i <= n ; i ++) {
		if (pre [i] && query (pre [i], i) >= a [i]) {
			continue;
		}
		
		if (nxt [i] && query (i, nxt [i]) >= a [i]) {
			continue;
		}
		
		ans ++;
		
//		cout << i << ": pre = " << pre [i] << ", nxt = " << nxt [i] << endl;
	}
	
	cout << ans << endl;
}

signed main () {
	int T = 1;
	cin >> T;
	
	while (T --) {
		Turn ();
	}
	
	return 0;
}
```

---

