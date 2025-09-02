# Racing

## 题目描述

在 2077 年，一项名为"业余无人机竞速"的运动在机器人中越来越流行。

你已经拥有一架无人机，并且想要获胜。为此，你的无人机需要飞越一个包含 $n$ 个障碍物的赛道。

第 $i$ 个障碍物由两个数字 $l_i, r_i$ 定义。设你的无人机在第 $i$ 个障碍物处的高度为 $h_i$，那么当且仅当 $l_i \le h_i \le r_i$ 时，无人机才能通过该障碍物。初始时无人机位于地面，即 $h_0 = 0$。

无人机的飞行程序由一个数组 $d_1, d_2, \ldots, d_n$ 表示，其中 $h_{i} - h_{i-1} = d_i$，且 $0 \leq d_i \leq 1$。这意味着你的无人机在障碍物之间要么保持高度不变，要么上升 $1$ 个单位。你已经有一个飞行程序，但其中某些 $d_i$ 未知并被标记为 $-1$。你需要将这些未知的 $d_i$ 替换为 $0$ 或 $1$，以创建一个能完整通过所有障碍物的飞行程序，或者报告这是不可能的。

## 说明/提示

在第一个测试用例中，一个可能的答案是 $d=[0,1,1,1]$。此时数组 $h$ 将为 $[0,0+1,0+1+1,0+1+1+1]=[0,1,2,3]$。这个数组满足题目条件。

在第二个测试用例中，可以证明不存在满足条件的数组 $d$，因此答案为 $-1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
4
0 -1 -1 1
0 4
1 2
2 4
1 4
3
0 -1 -1
0 1
2 2
0 3
2
-1 -1
0 0
2 2
8
-1 -1 1 -1 -1 0 0 -1
0 0
0 1
0 2
0 2
1 3
0 4
2 5
4 5
1
0
1 1```

### 输出

```
0 1 1 1 
-1
-1
0 1 1 0 1 0 0 1 
-1```

# 题解

## 作者：Zskioaert1106 (赞：6)

题目传送门：[CF2110C Racing](https://www.luogu.com.cn/problem/CF2110C)

终究是在机房的 VP 调出来了。

### 做题过程

画个图就很明晰了。

我们以样例的第四组数据为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/k2xf5nyb.png)

发现 $l_i,r_i$ 的上下界与 $i \sim n$ 都有关系，于是考虑找出递推关系。

- 我们称最后能取的 $l_i,r_i$ 为真正的 $l_i,r_i$。

真正的 $r_i$ 肯定不大于所有的 $r_{i \sim n}$，此时每个 $d_i=1$ 会使真正的 $r_i$ 上界减 $1$。

类推 $l$。在所有 $l_{i \sim n}$ 的最大值的基础上，每个非 $0$ 的 $d_i$ 可以给真正的 $l_i$ 下界向下贡献 $1$ 个单位。

由此我们得到递推关系式：

$$
r_{i-1}=\min(r_{i-1},r_i-[d_i=1])\\
l_{i-1}=\max(l_{i-1},l_i-[d_i\neq 0])\\
$$

倒着求出所有真正的 $l_i,r_i$ 后，我们就可以正着走一遍过程了。具体地，设 $h$ 为当前无人机的高度。如果当前 $d_i = -1$：

- 如果 $h < l_i$，$d_i \leftarrow 1$；

- 如果 $h+1 > r_i$，$d_i \leftarrow 0$；

- 否则都可取，可以设为随便一个。

然后如果 $d_i = 1$ 使 $h$ 加 $1$。此时我们已经尽量使答案满足要求了，如果还是出现 $h < l_i$ 或 $h > r_i$ 的情况，输出 $-1$。

### 代码实现

```cpp
#include<iostream>
using namespace std;
const int N=200005;
int n,d[N],l[N],r[N];
bool solve(){
	for(int i=1;i<=n;i++)cin>>d[i];
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	for(int i=n;i>1;i--){
		r[i-1]=min(r[i-1],r[i]-(d[i]==1));
		l[i-1]=max(l[i-1],l[i]-(d[i]!=0));
	}
	for(int i=1,h=0;i<=n;i++){
		if(d[i]==-1){
			if(h<l[i])d[i]=1;
			if(h+1>r[i])d[i]=0;
			if(d[i]<0)d[i]=0;//随便 
		}
		if(d[i]==1)h++;
		if(h<l[i]||h>r[i])return 1;
	}
	for(int i=1;i<=n;i++)cout<<d[i]<<' ';
	return 0;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		if(solve())cout<<-1;
		cout<<'\n';
	}
	return 0;
}
```

[AC on CF](https://codeforces.com/contest/2110/submission/321616383)。

---

## 作者：Aeyone (赞：4)

## C. Racing
模拟、贪心
### 题意
你有一架无人机，一开始在 $0$ 高度位置，你需要穿过有 $n$ 个障碍物的赛道，每个障碍物能通过的高度区间为 $[l_i,r_i]$，你需要用一个 $d$ 数组控制无人机上升和不上升（不能下降），现在给出了 $d$ 数组的部分值，让你构造出剩下的值，如果不可能通过，输出 `-1`。
### 思路
由于题目说每次通过一个障碍物只能上升或者保持高度，而 $d_i$ 的意义是飞到障碍物 $i$ 时，在第 $i-1$ 个障碍物的时候需要上升还是保持高度。\
\
因此我们首先从前往后递推，在飞到每个障碍物时，求出一个区间，意义为**无人机有可能飞行的高度区间**，这个很关键。\
\
然后我们想，如果知道最后无人机有可能到的高度区间，那么高度区间的最小值是不是最有可能到的高度？显然是的，因为无人机只能选上升或者不上升，那么对于这个最小值而言，是无人机需要进行上升操作最少就能到达的高度，如果中间障碍物很多可以一直选择不上升，而如果无人机能到达任何比最小值大的高度的话，那么一定是可以到达这个最小高度的。\
\
因此，我们只需要假设所求的这个最小高度为无人机最终的高度，然后去反推出 $d_i$ 即可。
### 做法
#### Step1
这里是从前往后递推出每个位置的无人机有可能的高度区间，用最小高度 `l` 和最大高度 `r` 两个变量维护，并把每个结果存储下来。
```c++
    for(int i = 1; i <= n; i ++){
		int a = reg[i][0], b = reg[i][1];
		if(d[i] == 1)
			l ++, r ++;
		if(d[i] == -1)
			r ++;
		l = max(l, a), r = min(r, b);
		ok &= (l <= r);
		reg1[i] = {l, r};	
	}
```
根据 $d_i$ 的不同分三种情况讨论：
- 当 $d_i=1$ 的时候，是不可以保持高度飞行的，所以最小高度和最大高度都需要加一。
- 当 $d_i=0$ 的时候，是不可以上升飞行的，因此什么都不操作。
- 当 $d_i=-1$ 的时候，就是无人机即可能上升也有可能不上升，所以只需要将最大可能高度加一，最小可能高度保持不变。

然后就是边界的处理，这个可能高度当然不能超过每个通过障碍物的范围，所以有 `l = max(l, a);` 和  `r = min(r, b);`。\
\
如果存在最小高度居然还大于了最大高度，那么一定是非法的，利用 `ok &= (l <= r);` 维护合法性。
#### Step2
这里是从后往前求出每个 $d_i$ 的过程，利用了一个贪心的思想，就是能下降就尽可能下降。一句话概括就是，如果这个位置既能从前面保持高度飞行而来，又能从前面的高度上升飞行而来，那么就**优先选择上升飞行**而来的操作。\
\
关于是否可以从前面的高度上升飞行而来，做好判断条件 `if(h - 1 >= reg1[i - 1][0] && h - 1 <= reg1[i - 1][1])` 即可。
```c++
    int h = l;
	for(int i = n; i >= 1; i --){
		if(d[i] == 1)
			h --;
		if(d[i] == -1){
			if(h - 1 >= reg1[i - 1][0] && h - 1 <= reg1[i - 1][1])
				h --, d[i] = 1;
			else
				d[i] = 0;
		}
	}
```
### Code
```c++
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

void solve() {
	int n;
	cin >> n;

	vector<int> d(n + 1);
	for(int i = 1; i <= n; i ++)
		cin >> d[i];

	vector<array<int, 2>> reg(n + 1);
	for(int i = 1; i <= n; i ++)
		cin >> reg[i][0] >> reg[i][1];

	int l = 0, r = 0;
	bool ok = true;
	vector<array<int, 2>> reg1(n + 1);
	for(int i = 1; i <= n; i ++){
		int a = reg[i][0], b = reg[i][1];
		if(d[i] == 1)
			l ++, r ++;
		if(d[i] == -1)
			r ++;
		l = max(l, a);
		r = min(r, b);
		ok &= (l <= r);
		reg1[i] = {l, r};
		// cout << l << " " << r << '\n';	
	}
	if(!ok){
		cout << -1 << '\n';
		return;
	}
	// cout << "@" << '\n';
	int h = l;
	for(int i = n; i >= 1; i --){
		if(d[i] == 1)
			h --;
		if(d[i] == -1){
			if(h - 1 >= reg1[i - 1][0] && h - 1 <= reg1[i - 1][1])
				h --, d[i] = 1;
			else
				d[i] = 0;
		}
	}
	for(int i = 1; i <= n; i ++)
		cout << d[i] << " ";
	cout << '\n';
}

signed main() {
//	freopen("../data/data.in", "r", stdin), freopen("../data/data.in", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr);
	int _;
	cin >> _;
	while (_ --)
		solve();
}
```

---

## 作者：fengyaun (赞：2)

## [CF2110C Racing](https://www.luogu.com.cn/problem/CF2110C)

### 分析

不难注意到，我们可以对于每个点的上界取后缀最小值，然后能加则加。

然后我们就会发现考虑不完全，可能会有加过了的情况，这时我们只需要对于每个点减去其已经固定的上升高度，就能知道未知的 $d$ 的可加量。

然后对于 $d$ 的可加量能加则加即可。

### 代码

```C++
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

struct node
{
    int l, r;
};

int T, n;

int d[N];

int ans[N];

int pre[N];

int suf[N];

node h[N];

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 1; i <= n; i++) cin >> h[i].l >> h[i].r;
    suf[n + 1] = n + 2;
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + (d[i] == -1 ? 0 : d[i]);
    for (int i = n; i >= 1; i--) suf[i] = min(h[i].r - pre[i], suf[i + 1]);
    for (int i = 1, now = 0, add = 0; i <= n; i++)
    {
        if (d[i] == -1)
        {
            if (add + 1 <= suf[i])
            { 
                ans[i] = 1;
                add++;
            }
            else ans[i] = 0;
        }
        else now += d[i];
        if (now + add < h[i].l || now + add > h[i].r) 
        {
            cout << -1 << "\n";
            return ;
        }
    }
    for (int i = 1; i <= n; i++) cout << (d[i] == -1 ? ans[i] : d[i]) << " ";
    cout << "\n";
}

int main()
{
    cin >> T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：WYX1210 (赞：2)

**思路**

先正向处理，确定每个障碍物 $i$ 的可能高度范围 $[lo_i,hi_i]$。初始高度为 $0$，逐步计算每个障碍物的高度范围：

若 $d_i$ 已知，则当前高度范围由前一个范围加上 $d[i]$，并与当前障碍物的区间取交集。

若 $d_i$ 未知，则当前高度范围由前一个范围可能的两种变化 $[+0,+1]$，再与当前障碍物的区间取交集。

再逆推处理：从最后一个障碍物开始，确定每个未知的 $d_i$ 的值。维护当前允许的高度范围 $[cl,ch]$，尝试选择 $0$ 或 $1$ 使得前一个障碍物的高度范围有效：

优先尝试 $d_i=1$，若可行则选择，否则尝试 $d_i=0$。

处理到第一个障碍物时，需确保初始高度为 $0$。

---

## 作者：yanbinmu (赞：1)

考虑到我们的飞行器是单调不降的，那么我们的上下限也是单调不降的。

这样我们就可以递推出上下界。

但是有一个小细节，如果某一个位置我确定了要向上升一格，那么前面的一格就要预留出相应的空间，不能顶到原本的最大。

代码也不复杂。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int d[N], l[N], r[N];// lr数组分别为上下限
int sum[N];

void solve() {
    int n;
    cin >> n;
    for(int i = 1;i <= n;i ++ ) {
        cin >> d[i];
        sum[i] = sum[i - 1] + (d[i] == 1);
    }
    for(int i = 1;i <= n;i ++ ) {
        cin >> l[i] >> r[i];
        l[i] = max(l[i], l[i - 1]);
    }
    for(int i = n - 1;i >= 1;i -- ) { // 第 n 个不用动
        r[i] = min(r[i + 1] - (d[i + 1] == 1), r[i]);
    }
    int h = 0;
    for(int i = 1;i <= n;i ++ ) {
        if(d[i] != -1) h += d[i];
        else {
            if(h < r[i]) d[i] = 1, h ++ ;
            else d[i] = 0;
        }
        if(h < l[i]) {
            cout << "-1\n";
            return ;
        }
        if(h > r[i]) {
            cout << "-1\n";
            return ;
        }
    }
    for(int i = 1;i <= n;i ++ ) cout << d[i] << " ";
    cout << "\n";
}

int main() {
    int T;
    cin >> T;
    while(T -- ) {
        solve();
    }
    return 0;
}
```

---

## 作者：ZHR100102 (赞：1)

[Blog](https://www.cnblogs.com/zhr0102/p/18901497)


你怎么知道这个唐题卡了我 20min？？？

注意到**高度单调不降**且**相邻两个数最多差 $1$** 的性质，不难发现合法的高度上下界 $l_i,r_i$ 实际上是**单调不降**的。于是可以前缀后缀扫一遍求出这个合法上下界，当合法上界小于下界的时候直接返回无解即可。

如果无需构造方案，直接维护两个合法高度指针即可。

但此题需要给出详细方案，于是考虑**调整法**。注意到**只有上下界两个限制**，因此我们先**尽可能地满足不超过上界的限制**，即对于每个位置尽可能地赋 $0$；在对于无法满足下界的位置时，对曾经赋 $0$ 的位置进行调整即可。因为一个位置赋 $1$ 会导致后缀全部加 $1$，为了影响尽可能少的位置，需要贪心地**从后往前**赋 $1$，否则一定不优。这个操作可以利用栈来维护。

构造完方案后，再判断一遍调整之后方案合不合法即可。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=200005;
int n,d[N],l[N],r[N],h[N];
void solve()
{
    stack<int>stk;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>d[i];
    for(int i=1;i<=n;i++)
        cin>>l[i]>>r[i];
    for(int i=2;i<=n;i++)
        l[i]=max(l[i],l[i-1]);
    for(int i=n-1;i>=1;i--)
        r[i]=min(r[i],r[i+1]);
    memset(h,0,sizeof(h));
    int lx=0;
    for(int i=1;i<=n;i++)
    {
        if(d[i]==1)
        {
            lx++;
            h[i]=1;
        }
        else if(d[i]==-1)
            stk.push(i);
        while(!stk.empty()&&lx<l[i])
        {
            h[stk.top()]=1;
            stk.pop();
            lx++;
        }
        if(lx<l[i]||l[i]>r[i])
        {
            cout<<"-1\n";
            return;
        }
    }
    int cur=0;
    for(int i=1;i<=n;i++)
    {
        cur+=h[i];
        if(cur<l[i]||cur>r[i])
        {
            cout<<"-1\n";
            return;            
        }
    }
    for(int i=1;i<=n;i++)
        cout<<h[i]<<" ";
    cout<<'\n';
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：lw393 (赞：1)

这道题是本场比较有区分度的题。

我们注意到 $h$ 是单调不降的，所以我们可以枚举出在第 $i$ 个位置时，可以到达的高度的最大值 $high_i$ 与最小值 $low_i$。

但是我们有限高与限低，所以在每个位置上还要对 $[l_i,r_i]$ 与 $[low_i, high_i]$ 取并集。若并集为空集，则没有满足条件的 $d$。否则按限高与限低去更新 $low_i$ 与 $high_i$。

处理完了以后，倒着检查一遍，看看能不能在上述条件下构造出 $d$。这个靠贪心给出。

详见代码（较为丑陋）：
```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
  int n;
  cin >> n;
  vector<int>d(n + 1), l(n + 1), r(n + 1);
  vector<int>low(n + 1), high(n + 1);
  for(int i = 1; i <= n; i++) cin >> d[i];
  for(int i = 1; i <= n; i++) cin >> l[i] >> r[i];
  low[0] = high[0] = 0;
  for(int i = 1; i <= n; i++){
    int dn = d[i], ll = l[i], rr = r[i];
    if(dn == 0) {
      int cl = low[i - 1], ch = high[i - 1];
      cl = max(cl, ll), ch = min(ch, rr);
      if(cl > ch) { cout << -1 << '\n'; return; }
      low[i] = cl, high[i] = ch;
    }else if(dn == 1){
      int cl = low[i - 1] + 1, ch = high[i - 1] + 1;
      cl = max(cl, ll), ch = min(ch, rr);
      if(cl > ch) { cout << -1 << '\n'; return; }
      low[i] = cl, high[i] = ch;
    }else{
      int cl = low[i - 1], ch = high[i - 1] + 1;
      cl = max(cl, ll), ch = min(ch, rr);
      if(cl > ch) { cout << -1 << '\n'; return; }
      low[i] = cl, high[i] = ch;
    }
  }
  int nowh = high[n];
  vector<int>ans = d;
  for(int i = n; i >= 1; i--){
    int dn = ans[i];
    int prel = low[i - 1], preh = high[i - 1];
    if(dn == 0) { if(nowh < prel || nowh > preh) { cout << -1 << '\n'; return; } }
    else if(dn == 1) { int newh = nowh - 1; if(newh < prel || newh > preh) { cout << -1 << '\n'; return; } nowh = newh; }
    else {
      bool ok = 0; int newh = nowh - 1;
      if(newh >= prel && newh <= preh) { ans[i] = 1; nowh = newh; ok = 1; }
      else { newh = nowh; if(newh >= prel && newh <= preh){ ans[i] = 0;ok = 1; } }
      if(!ok) { cout << -1 << '\n'; return; }
    }
  }
  if(nowh != 0) { cout << -1 << '\n'; return; }
  for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
  cout << '\n';
}

int main(){
  int t = 1;
  cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
```

---

## 作者：tyr_04 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF2110C)

### 思路

判断有无解是简单的，定义 $L_i,R_i$ 表示走过前 $i$ 的位置后高度的范围 $L_i \sim R_i$，如果第 $i$ 个位置为 $1$ 或 $-1$，$L_{i + 1} = L_{i},R_{i + 1} = R_i + 1$，否则 $L_{i + 1} = L_{i},R_{i + 1} = R_i$，由于第 $i$ 个位置有高度限制 $l_i \sim r_i$，所以 $R_i$ 要对 $r_i$ 取  $\min$，$L_i$ 要对 $l_i$ 取  $\max$，一旦 $R_i < l_i$ 或 $L_i > r_i$（即可走的高度范围与限制的范围不交），输出 $-1$。

接下来，从 $L_n \sim R_n$ 中任选一个数作最后的高度都一定有解，由于 $L_{1 \sim n}$ 单调不降（$L_{n \sim 1}$ 单调不增），从最终高度倒推，遇见 $1$ 的位置就高度减 $1$，遇见 $0$ 则不变，遇见 $-1$ 则判断当前高度是否大于上一个位置的限制，如果是高度减 $1$ 并且当前位置填 $1$，因为高度限制的 $L$ 随着位置越来越靠前逐渐减小，当前高度也尽量小，更有可能满足前面的限制，总时间复杂度 $O(n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,d[200005],l[200005],r[200005],ans,now;
struct node
{
	int l,r;
}s[200005];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans=1;
		for(int i=1;i<=n;i++)
		{
			cin>>d[i];
		}
		for(int i=1;i<=n;i++)
		{
			cin>>s[i].l>>s[i].r;
		}
		l[0]=0;
		r[0]=0;
		for(int i=1;i<=n;i++)
		{
			l[i]=l[i-1];
			r[i]=r[i-1];
			if(d[i]==-1)
			{
				r[i]++;
			}
			else if(d[i]==1)
			{
				l[i]++;
				r[i]++;
			}
			if(l[i]>s[i].r||r[i]<s[i].l)
			{
				ans=0;
				break;
			}
			r[i]=min(r[i],s[i].r);
			l[i]=max(l[i],s[i].l);
		}
		if(ans==0)
		{
			cout<<-1<<'\n';
			continue;
		}
		now=l[n];
		for(int i=n;i>=1;i--)
		{
			if(d[i]==1)
			{
				now--;
			}
			else if(d[i]==-1)
			{
				if(now>l[i-1])
				{
					d[i]=1;
					now--;
				}
				else
				{
					d[i]=0;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			cout<<d[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Shadow_T (赞：0)

主包太菜了，感觉这一场 C 比 D 难调。

复杂度是带 $\operatorname{log}$ 的，但是不难想。

首先可以考虑类似贪心的做法。我们每一次先给不确定的 $d_i$ 全部填上 $1$。然后当某一次填一发现太大的时候，就往前回溯补成 $0$，降低这一次的高度，直到达到要求就行。

很明显的，因为每一次数值的影响会一直往后面延续下去，所以往前回填的时候这些回填位置下标尽量大，造成的影响就会最小。如果这时候这些回填补 $0$ 还是让前面的某一步低于了限制，那我们也无力回天了，即为无解。

因为可以往前填的位置每个只能用一次，所以可以把这些丢到一个 set 里，每次取当前可以用的最大那一个用，然后弹掉就可以了。

```
#include <bits/stdc++.h>
using namespace std;
void Ios()
{
	ios::sync_with_stdio (0);
	cin.tie(0);
	cout.tie(0);
}
const int maxn=2e5+10;
int d[maxn],l[maxn],r[maxn];
void solve()
{
	int n;
	cin>>n;
	set<int> id;
	for(int i=1;i<=n;i++) cin>>d[i];
	for(int i=1;i<=n;i++)
	cin>>l[i]>>r[i];
	int lh=0,rh=0;
	for(int i=1;i<=n;i++)
	{
		if(d[i]!=-1) lh+=d[i],rh+=d[i];
		else rh++,d[i]=1,id.insert(-i);
		if(rh>r[i])
		{
			int g=rh-r[i],k=1;
			for(auto it=id.begin();it!=id.end()&&k<=g;k++)
			{
				d[-*it]=0;
				auto IT=it;
				it++;
				id.erase(IT);
			}
		}
		rh=min(rh,r[i]);
	}
	lh=0;
	for(int i=1;i<=n;i++)
	{
		lh+=d[i];
		if(l[i]<=lh&&lh<=r[i]);
		else
		{
			cout<<-1<<"\n";
			return;
		}
	}
	for(int i=1;i<=n;i++) cout<<d[i]<<" ";
	cout<<"\n";
}
int main()
{
	Ios();
	int t;
	cin>>t;
	while(t--) solve();
 }
```

[Submission](https://codeforces.com/contest/2110/submission/321094900)

---

## 作者：muling1437 (赞：0)

# CF2110C Racing 题解

## 原题链接
- [CF2110C Racing](https://codeforces.com/contest/2110/problem/C)

## 解题思路

首先，以时间递推看无人机能否完整通过所有障碍物。使用两个数组 $low[i]$ 和 $hi[i]$ 记录第 $i$ 个时间点能到达的最低点和最高点。当 $hi[i] < low[i]$ 时无人机无法通过所有障碍物。

### 状态转移方程
当 $a[i] = -1$ 时（自由移动）：
$$ low[i] = \max(low[i - 1], l[i]) $$
$$ hi[i] = \min(hi[i - 1] + 1, r[i]) $$

当 $a[i] = 1$ 时（强制上升）：
$$ low[i] = \max(low[i - 1] + 1, l[i]) $$
$$ hi[i] = \min(hi[i - 1] + 1, r[i]) $$

当 $a[i] = 0$ 时（强制不变）：
$$ low[i] = \max(low[i - 1], l[i]) $$
$$ hi[i] = \min(hi[i - 1], r[i]) $$

### 方案构造
从最终时刻的 $low[n]$ 和 $hi[n]$ 中任选一个点逆推：
1. 强制下降时根据前驱状态选择操作
2. 强制上升时必然执行上升操作
3. 自由移动保持当前位置

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
#define INF 1e18

int t;
int n, m, k;
int a[200005];
int l[200005], r[200005];
int low[200005], hi[200005];

void slove()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        low[i] = 0, hi[i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> l[i] >> r[i];
    }
    low[0] = 0, hi[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == -1)
        {
            low[i] = max(low[i - 1], l[i]);
            hi[i] = min(hi[i - 1] + 1, r[i]);
        }
        else if (a[i] == 1)
        {
            low[i] = max(low[i - 1] + 1, l[i]);
            hi[i] = min(hi[i - 1] + 1, r[i]);
        }
        else
        {
            low[i] = max(low[i - 1], l[i]);
            hi[i] = min(hi[i - 1], r[i]);
        }
        if (hi[i] < low[i])
        {
            cout << -1 << endl;
            return;
        }
    }
    vector<int> ans;
    int now = low[n];
    for (int i = n; i >= 1; i--)
    {
        if (a[i] == -1)
        {
            if (low[i - 1] <= now && now <= hi[i - 1])
            {
                ans.push_back(0);
            }
            else
            {
                now--;
                ans.push_back(1);
            }
        }
        else if (a[i] == 1)
        {
            now--;
            ans.push_back(1);
        }
        else
        {
            ans.push_back(0);
        }
    }
    for (int i = ans.size() - 1; i >= 0; i--)
    {
        cout << ans[i] << ' ';
    }
    cout << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--)
    {
        slove();
    }
    return 0;
}
```

---

## 作者：denominator (赞：0)

> [原题](https://www.luogu.com.cn/problem/CF2110C) / [CF 原题](https://codeforces.com/problemset/problem/2110/C)
>
> - 有 01 序列 $d$，部分位置上的数值不知道（记为 $-1$）。
> - 现在需要合理赋值，使得对 $i=1,2,\cdots,n$：
>   - $l_i\leq \sum\limits_{j=1}^id_j\leq r_i$；
> - 或报告无解。
> - $1\leq n\leq 2\times10^5$。

~~社贡分掉 0 了，找道赛题写写题解。~~

真的清楚在做什么的话，其实这题写写 ~15min 完全足够。

先将 $i$ 从 $1$ 到 $n$ 枚举，更新 $l_i$ 与 $r_i$——因为原题的上下界可能在满足前面要求的情况下是不能达到的。

具体地：

- 不妨 $l_0=r_0=0$。
- 若 $d_i=0$，令 $l_i\gets\max(l_i,l_{i-1})$，$r_i\gets\min(r_i,r_{i-1})$；
- 若 $d_i=1$，令 $l_i\gets\max(l_i,l_{i-1}+1)$，$r_i\gets\min(r_i,r_{i-1}+1)$；
- 否则，令 $l_i\gets\max(l_i,l_{i-1})$，$r_i\gets\min(r_i,r_{i-1}+1)$。

中间出现 $l_i>r_i$ 就直接判无解。

这个 $l_i$ 与 $r_i$ 给我们兜了个底——因为显然地，对任意一个 $x=l_i,l_i+1,\cdots,r_i$，都会存在满足要求的 $d$ 使得 $\sum\limits_{j=1}^id_j=x$。

现在，将 $i$ 从 $n$ 到 $1$，枚举 $[L,R]$——表示能够使得 $i\sim n$ 的条件都满足，需要 $L\leq \sum\limits_{j=1}^id_j\leq R$。之所以要枚举它们，而不是直接使用 $l_i,r_i$，是因为后面的条件可能也会对前面有所限制，不能顶到地下。

这时候，如果 $d_i=-1$，就可以知道 $d_i$ 是啥了！

- 如果 $r_i+1=L$，这说明 $d_i$ 不得不是 $1$；
- 如果 $l_i=R$，这说明 $d_i$ 不得不是 $0$；
- 否则 $d_i$ 其实无所谓，这是因为上面的性质。我的代码里设为 $0$。

现在还需要维护 $L$ 和 $R$。$i=n$ 时，$L=l_n$，$R=r_n$。注意我们有一个未提及的点，就是说 $L,R$ 的选择是与 $d$ 同步的，我们应该在选完 $d$ 之后再去维护。具体地，令 $d_i$ 为 $0$ 或 $1$：

- 若 $d_i=0$，则 $L\gets\max(L,l_{i-1})$，$R\gets\min(R,r_{i-1})$；
- 若 $d_i=1$，则 $L\gets\max(L-1,l_{i-1})$，$R\gets\min(R-1,r_{i-1})$。

但是其实我们大可以不需要 $L=l_n$，$R=r_n$，设 $L=R=l_n$ 是完全可行的，表示这些数的和必须是 $l_i$。这时 $L$ 和 $R$ 就是可以设为同一个变量，~~但是这是赛后才发现的就不改代码了~~。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200010;
int T, n, d[N], l[N], r[N];
int main () {
	scanf ("%d", &T);
	while (T --> 0) {
		scanf ("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf ("%d", &d[i]);
		}
		for (int i = 1; i <= n; i++) {
			scanf ("%d%d", &l[i], &r[i]);
		}
		int x = 0, y = 0;
		bool flag = false;
		for (int i = 1; i <= n; i++) {
			if (d[i] == 1) {
				x = l[i - 1] + 1;
			} else {
				x = l[i - 1];
			}
			if (d[i] == 0) {
				y = r[i - 1];
			} else {
				y = r[i - 1] + 1;
			}
			if (y < l[i] || x > r[i]) {
				flag = true;
				break;
			}
			l[i] = max (x, l[i]);
			r[i] = min (y, r[i]);
		}
		if (flag) {
			puts ("-1");
		} else {
			x = l[n], y = r[n];
			for (int i = n; i >= 1; i--) {
				if (d[i] == -1 && r[i - 1] + 1 == x) {
					d[i] = 1;
				} else if (d[i] == -1) {
					d[i] = 0;
				}
				if (d[i] == 1) {
					x = max (x - 1, l[i - 1]);
					y = min (y - 1, r[i - 1]);
				} else {
					x = max (x, l[i - 1]);
					y = min (y, r[i - 1]);
				}
			}
			for (int i = 1; i <= n; i++) {
				printf ("%d%c", d[i], " \n"[i == n]);
			}
		}
	}
	return 0;
}
```

---

