# [ABC245E] Wrapping Chocolate

## 题目描述

高桥先生有 $N$ 块巧克力。第 $i$ 块巧克力是长为 $A_i$，宽为 $B_i$ cm 的长方形。高桥先生还有 $M$ 个盒子。第 $i$ 个盒子是长为 $C_i$，宽为 $D_i$ cm 的长方形。

请问是否能在满足以下条件的情况下把所有巧克力放入盒子中。

- 一个盒子中最多放入一块巧克力。
- 当把第 $i$ 块巧克力放入第 $j$ 个盒子的时候，必须满足 $A_i\le C_j$ 并且 $B_i\le D_j$（不允许旋转）。

## 说明/提示

- $1\le N\le M\le 2\times 10^5$
- $1\le A_i,B_i,C_i,D_i\le 10^9$
- 所有数据均为整数。

—— Translated by 2c_s

## 样例 #1

### 输入

```
2 3
2 4
3 2
8 1 5
2 10 5```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2
1 1
2 2
100 1
100 1```

### 输出

```
No```

## 样例 #3

### 输入

```
1 1
10
100
100
10```

### 输出

```
No```

## 样例 #4

### 输入

```
1 1
10
100
10
100```

### 输出

```
Yes```

# 题解

## 作者：fish_love_cat (赞：7)

纯模拟的贪心恐怕行不通捏，无论是优先按什么来排序，总是可以 hack 掉的……

---

**主要的思路：**

可以发现，巧克力和盒子都是有纵横两线的，我们不管题面中什么 $A\ B\ C\ D$，把两者的横统称为 $x$，纵统称为 $y$。

我们把盒子和巧克力存在一个数组里，按 $x$ 从大到小排序，如果相等，按 $y$ 来排。若大小正好相等，则让盒子排在巧克力前面。我们可以利用 ```multiset``` 来进行查找，按排好的顺序把盒子的 $y$ 不断存进集合中。如果这里是巧克力，那么按照上面的排序方法，$x$ 比该巧克力大或者相等的盒子已经全部被存进了集合。接下来只需要利用 ```lower_bound()``` 找出第一个也就是大小最相近的 $y$ 大于等于该巧克力 $y$ 的盒子踢出集合，代表已经使用即可。

如果没有找到符合要求的盒子来装巧克力，那么接下来的盒子的 $x$ 都比该巧克力的 $x$ 小，所以是定不能装下的，输出 ```No```，结束程序。

如果最终成功跑完没有出现巧克力放不了的情况，输出 ```Yes``` 即可。

---

**放个代码吧：**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct dx{
    int x,y,op;//op用于存数据种类。
};
bool cmp(dx a,dx b){
    if(a.x==b.x){
		if(a.y==b.y){
			return a.op<b.op;//大op就是巧克力，排后面。
		}
        return a.y>b.y;
    }
    return a.x>b.x;
}
dx a[1200005];
multiset<int> st;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i].x;
        a[i].op=1;//巧克力op为1。
    }
    for(int i=1;i<=n;i++){
        cin>>a[i].y;
    }
    for(int i=n+1;i<=n+m;i++){
        cin>>a[i].x;
    }//没赋值默认盒子op为0。
    for(int i=n+1;i<=n+m;i++){
        cin>>a[i].y;
    }
    sort(a+1,a+n+m+1,cmp);
    for(int i=1;i<=n+m;i++){
        if(a[i].op==1){
        	auto it=st.lower_bound(a[i].y);
        	if(it==st.end()){//没有找到返回st.end()，切记！
        		cout<<"No";
        		return 0;
			}
			st.erase(it);
		}else{
			st.insert(a[i].y);
		}
    }
    cout<<"Yes";//如果能成功跑完……
    return 0;
}
```

~~咱就是说，都说的这么详细了，还要看代码吗？~~

---

## 作者：appear_hope (赞：4)

直接做两维条件过于复杂，我们可以通过排序 $A_i$ 和 $C_i$ 的方式消除一维条件。

只有一维条件后，对于一个巧克力我们贪心地选择在盒子中第一个大于等于 $B_i$ 的 $D_i$，那么这个盒子就被用了，支持这种操作的可以使用 `multiset`。

为了方便代码实现，且我们需要满足条件：$C_j \ge A_i$，所以可以把巧克力和盒子放在一起排序。

排序后，我们发现能用的盒子是从大到小的，我们与其先加入盒子的信息，不如一边加入信息一边使用盒子。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 5;

struct Node{
    int l, r, id;
}a[N];

int n, m;
multiset<int> s;

void Solve(int x, int y, int op){
    for(int i = x; i <= y; i++){
        cin >> a[i].l;
        a[i].id = op;
    }
    for(int i = x; i <= y; i++){
        cin >> a[i].r;
    }
}

int main(){
    cin >> n >> m;
    Solve(1, n, 0), Solve(n + 1, n + m, 1);
    sort(a + 1, a + n + m + 1, [](const Node &a, const Node &b){ return a.l < b.l || a.l == b.l && a.id < b.id; }); //魔鬼细节，如果长相同我们应先把巧克力放在前面
    for(int i = n + m; i >= 1; i--){
        if(!a[i].id){
            auto it = s.lower_bound(a[i].r);
            if(it == s.end()){
                cout << "No";
                return 0;
            }
            s.erase(it);
        }
        else{
            s.insert(a[i].r);
        }
    }
    cout << "Yes";
    return 0;
}
```

---

## 作者：hsy8116 (赞：3)

本题算法为贪心，这里主要来证明贪心的正确性。

因为对于每个盒子和巧克力都有两个属性，长和宽，不便于判断，于是考虑对 $B$ 和 $D$ 进行排序；又由于 _当遇到每一个巧克力就想要在前面的盒子中找最合适的_ ，于是必须保证前面盒子的 $D$ 值比当前巧克力的 $B$ 值要大，所以从大到小对 $B$ 和 $D$ 排序；还观察到盒子和巧克力的属性十分相似，于是将它们两个放在一个数组里排序，若 $B$ 与 $D$ 一致，那么盒子排在前。

但是这个贪心策略还不完善，尤其是那句斜体的话：当遇到每一个巧克力就想要在前面的盒子中找最合适的。最合适的是什么？其实应该是在前面的盒子中找最小的一个 $\ge A$ 的 $C$ 值。

那么为什么就对了？咱们来证明一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/u3lf9grw.png)

 _图片中白色为盒子，棕色为巧克力。_ 

先看图1，对 $B$ 和 $D$ 排好序后，我们考虑第一块巧克力的匹配，一眼看去，第二个盒子的6，10最适合，但如果将第一块巧克力放到第二个盒子后，第二块巧克力该如何放置呢？还不如把第一块巧克力放在 $C$ 值更优的第一个盒子里，这样第二块巧克力也可以放下了。

**对于每块需要放置的巧克力，我们首先知道前面的 $D$ 值都能满足这块巧克力的 $B$ 值。其次，我们不知道，这块巧克力之后有没有比它的 $A$ 值更大的，所以我们需要选前面盒子中 $C$ 值尽可能小的盒子，以为后面留准备。**

所以可证这种贪心策略一定最优，满足可行性原则。

$Code$


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
using namespace std;

const int NR = 2e5 + 10;
multiset<int> s;

struct node
{
	int a, b, t;
	bool operator < (const node &y) const
	{
		if (b != y.b) return b > y.b;
		return t > y.t;
	}
}p[NR * 2];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++)
	{
		scanf("%d", &p[i].a);
		p[i].t = 1;
	}
	for (int i = 1; i <= n; i ++)
	{
		scanf("%d", &p[i].b);
	}
	for (int i = 1; i <= m; i ++)
	{
		scanf("%d", &p[i + n].a);
		p[i + n].t = 2;
	}
	for (int i = 1; i <= m; i ++)
	{
		scanf("%d", &p[i + n].b);
	}
	sort(p + 1, p + n + m + 1);
	for (int i = 1; i <= n + m; i ++)
	{
		if (p[i].t == 2) s.insert(p[i].a);
		else
		{
			if (s.lower_bound(p[i].a) == s.end())
			{
				puts("No");
				return 0;
			}
			s.erase(s.lower_bound(p[i].a));
		}
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：cwxcplh (赞：2)

~~我绝对不会告诉你我打比赛时没做出来这道题。~~

题目简化：给定每个巧克力和盒子的长宽，已知每个盒子只能放一块巧克力，并且必须保证巧克力能放下，求是否所有巧克力都能放入。

思路：贪心、二分、排序、STL。

首先看到这道题，最容易想到的算法就是暴力枚举。当然这是不可能的。所以时间复杂度只能是 $O(n\log_2(n))$ 或 $O(n)$ 的。

$O(n)$ 的我是没想出来，但我一看到 $\log_2(n)$，瞬间就想到了两个东西：二分和排序。因为二分就需要排序，所以这里肯定两种都用了。

那排序我们只能排序一个量，但题目中有长宽两个变量，我们怎么排序呢？这时，我们就需要 OI 中一个很重要的思想：化二维为一维。

我们可以这么干：首先按照长排序（具体怎么排大家自己想），然后对于每一个巧克力的宽，我们在盒子中找到能包含它的，全部推入一个数组中，接着对这个数组二分找第一个能容下它的。这一步是贪心，想必大家都能想明白。

最后，如果没有能容下这块巧克力的盒子，直接输出 `No` 就对了。如果能装下，只需要把这个盒子弹出就行了。（这里就需要思考如何排序了。）

问题：二分需要排序，而快排是 $O(n\log_2(n))$ 的，这样一循环不就超时了吗？很简单，只需要用 `multiset` 就好了，它的排序是 $O(\log_2(n))$ 级别的。

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct wc {
	int x,y;
} a[200006],b[200006];
int n,m;
inline bool cmp(wc x,wc y) {
	return x.x>y.x;
}
inline bool cmp1(wc x,wc y) {
	return x.x<y.x;
}
signed main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		cin>>a[i].x;
	}
	for(int i=1; i<=n; i++) {
		cin>>a[i].y;
	}
	for(int i=1; i<=m; i++) {
		cin>>b[i].x;
	}
	for(int i=1; i<=m; i++) {
		cin>>b[i].y;
	}
	sort(a+1,a+n+1,cmp);//具体原因自己想
	sort(b+1,b+m+1,cmp1);
	multiset<int>ms;
	int j=m;
	for(int i=1; i<=n; i++) {
		for(; b[j].x>=a[i].x&&j>=1; j--) {
			ms.insert(b[j].y);
		}
		auto it=ms.lower_bound(a[i].y);
		if(it==ms.end()) {
			cout<<"No";
			return 0;
		}
		ms.erase(it);//弹出盒子
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：XiaoQuQu (赞：2)

题解区怎么这么多人没讲明白为什么这么贪心是对的/yun

考虑这个题其实要满足两个限制，也就是 $a_i\le c_i,b_i\le d_i$，于是我们直接将盒子和巧克力放一起按照 $b_i$ 或者 $d_i$ 降序排序，这样我们遍历的时候就一定满足了后面出来的巧克力的 $b_i$ 一定小于等于前面的 $d_i$。

现在我们考虑满足 $a_i\le c_i$ 的限制，不难想到一个贪心，由于我们不知道后面的情况，所以我们可以贪心地选取**能满足 $a_i\le c_i$ 的最小的 $c_i$**。

贪心算法的正确性证明：对于一次为 $a_i$ 选取 $c_i$ 的时候，如果我们没有选取最小的满足 $a_i\le c_i$ 的 $c_i$（这里设为 $c_m$），而是选取了某个满足 $a_i\le c_n$ 的 $c_n(c_n\ge c_m)$，则我们可以使用 $c_m$ 替换 $c_n$，使得答案一定不劣。

实际实现中，可以使用 multiset 维护选取 $a_i\le c_i$ 的 $c_i$ 的过程。

```cpp
const int MAXN = 2e5 + 5;
int n, m;
multiset<int> s;
struct _node {
	int a, b, t;
	bool operator < (const _node _) const {
		if (b == _.b) return t > _.t;
		return b > _.b;
	}
} a[MAXN * 2];

void work() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i].a, a[i].t = 1;
	for (int i = 1; i <= n; ++i) cin >> a[i].b;
	for (int i = 1; i <= m; ++i) cin >> a[i + n].a, a[i + n].t = 2;
	for (int i = 1; i <= m; ++i) cin >> a[i + n].b;
	sort(a + 1, a + 1 + n + m);
	for (int i = 1; i <= n + m; ++i) {
		if (a[i].t == 2) s.insert(a[i].a);
		else {
			if (s.lower_bound(a[i].a) == s.end()) 
				return cout << "No" << endl, void();
			s.erase(s.lower_bound(a[i].a));
		}
	}
	cout << "Yes" << endl;
}
```


---

## 作者：fengenrong (赞：2)

这题我们可以用多重集合的贪心，我们不管它是盒子还是巧克力全部一起存入一个结构体当中再排序。我们先按 $x$ 由大到小进行排序，如果相等则按 $y$ 由大到小进行排序。要是 $x$ 和 $y$ 都是相等的，我们就先将盒子排在前面。

排完序后，我们从 $1$ 开始遍历到 $n+m$，我们可以利用 `multiset` 进行查找。如果是巧克力的话，用 `lower_bound()` 即可，`lower_bound()` 可以找出第一个也就是大小最相近的 $y$ 大于等于该巧克力 $y$ 的盒子。如果没找到则输出 `No`，并结束程序。这是因为：没有找到符合要求的盒子来装巧克力，那么接下来的盒子的 $x$ 都比该巧克力的 $x$ 小，所以是不符合题意的。


否则将第一个也就是大小最相近的 $y$ 大于等于该巧克力 $y$ 的盒子踢出集合。如果是盒子的话，就把当前盒子放入集合中。

### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct op{
	int x,y;//分别表示两条边的长度 
	bool pd;//判断是否为巧克力 
}a[1000005];
int n,m;
bool cmp(op a,op b)//比较函数 
{
	return (a.x==b.x?(a.y==a.y?a.pd<b.pd:a.y>b.y):a.x>b.x);//排序方法，见上 
}
multiset<int> q;
signed main()
{
	cin>>n>>m;
	for(register int i=1;i<=n;i++)
	{
		cin>>a[i].x;
		a[i].pd=true;//标记为巧克力 
	}
	for(register int i=1;i<=n;i++)
	{
		cin>>a[i].y;
	}
	for(register int i=n+1,j=1;j<=m;j++,i++)//注意是从n+1开始的，否则会重复 
	{
		cin>>a[i].x;
		a[i].pd=false;//标记为盒子 
	}
	for(register int i=n+1,j=1;j<=m;j++,i++)
	{
		cin>>a[i].y;
	}
	sort(a+1,a+n+m+1,cmp);
	for(register int i=1;i<=n+m;i++)
    {
    	if(a[i].pd==true)//巧克力 
    	{
    		auto now=q.lower_bound(a[i].y);//查询 
        	if(now==q.end())//没有 
			{
        		cout<<"No";
        		return 0;
			}
			q.erase(now);//删除 
		}
		else
		{
			q.insert(a[i].y);//插入 
		}
    }
    cout<<"Yes";
	return 0;
}
```

---

## 作者：shinkuu (赞：1)

听说没人写，那就来一发。

这种偏序问题大概率是要排个序的。将盒子和巧克力视为一个东西，$c$ 视为 $a$，$d$ 视为 $b$，放在一起以 $a$ 为第一关键字，$b$ 为第二关键字降序排序。此时，我们发现前面的盒子的 $a$ 值一定是满足后面巧克力的 $b$ 值的。所以记录还没被用的所有盒子的 $b$ 值，每次有巧克力就在其中找到其 $b$ 值的后继，即最小的 $b'\geq b$ 来装。这样一定是最优的。

再举一个具体一点的例子：

![](https://i.328888.xyz/2023/03/18/MUw2t.png)

（横为 $a$，纵为 $b$）

在这种情况下，如果两个盒子都满足，选择 $2$ 仍然是更优的，因为 $a$ 的条件两个都一定能满足，$b$ 却不一定。

用一个 multiset 维护即可。还要注意排序的时候如果有同等大小的巧克力和盒子，盒子要排在前面。

code：


```cpp
int n,m;
struct node{
	int x,y,op;
}e[N<<1];
multiset<int> st;
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&e[i].x);
		e[i].op=1;//要记录是盒子还是巧克力
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&e[i].y);
	}
	for(int i=n+1;i<=n+m;i++){
		scanf("%d",&e[i].x);
	}
	for(int i=n+1;i<=n+m;i++){
		scanf("%d",&e[i].y);
	}
	sort(e+1,e+n+m+1,[&](node a,node b){return a.x!=b.x?a.x>b.x:(a.y!=b.y?a.y>b.y:a.op<b.op);});
	for(int i=1;i<=n+m;i++){
		if(e[i].op){
			auto it=st.lower_bound(e[i].y);
			if(it==st.end()){
				puts("No");
				return;
			}
			st.erase(it);
		}else{
			st.insert(e[i].y);
		}
	}
	puts("Yes");
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

2023.4.25 upd，求通过。

---

## 作者：zyc418 (赞：0)

# E - Wrapping Chocolate
[题目](https://atcoder.jp/contests/abc245/tasks/abc245_e)

这题一看就是**贪心**，对于某个物品来说，我们要尽量放到小的箱子里。

我们只需考虑巧克力的长或宽与盒子的长或宽的大小，这只需一个 `sort`。

考虑长和宽两个因素比较困难，因此我们可以对其按长排序，只考虑长，若不存在某个宽度满足条件，则说明无法放入。

但在进行贪心时，需要考虑长的大小，并进行排序，还需用**二分**来查找。

毕竟
- $ 1\ \leq\ N\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i,B_i,C_i,D_i\ \leq\ 10^9 $

所以在具体的实现中，可以使用 `multiset` 来维护箱子的宽度，然后使用 `lower_bound` 来遍历物品和箱子。

最后记得把用过的数删掉。
## E - Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define mod 1e9+7
#define inf 2e18
using namespace std;
const ll N=2e5+5;
struct node {
    ll x,y;
}a[N],b[N];
ll n,m;
multiset<ll> s;
string str="Yes";
bool cmp(node a,node b) {
    return a.x<b.x;
}
int main() {
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i].x;
    }
    for(ll i=1;i<=n;i++) {
        cin>>a[i].y;
    }
    for(ll i=1;i<=m;i++) {
        cin>>b[i].x;
    }
    for(ll i=1;i<=m;i++) {
        cin>>b[i].y;
    }
    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+m,cmp);
    ll num=m;
    for(ll i=n;i>=1;i--) {
        while(num>=1&&a[i].x<=b[num].x) {
            s.insert(b[num].y);
            num--;
        }
        auto it=s.lower_bound(a[i].y);
        if(it==s.end()) {
            str="No";
            break;
        }
        s.erase(it);
    }
    cout<<str;
    return 0;
}
```

---

## 作者：Melo_DDD (赞：0)

我们发现不论是巧克力还是盒子，都存在横、竖两个限制，我们不妨以横着的长度为第一关键字，竖着的长度为第二关键字把它们揉到一起降序排序，如果遇到盒子，就存起来。

一个不显然的贪心策略是，当我们遇到一个巧克力的时候，注意到在它前面存进去的盒子在横着的长度上面一定满足它的限制，那么我们用 ``lower_bound`` 查找出纵长与之最接近且能够满足限制的盒子即可。

口胡证明。从横纵两个方面考虑。

首先横向方面，我们在枚举到一个巧克力的时候，它的前面的盒子在横向上一定会满足条件，所以它占用哪一个盒子在横向上对其后面的巧克力都是无异的，都是少了一个。

纵向上，正确性显然，我们仅需要考虑当前巧克力的选择对之后的影响，如果它没有选与它最接近的，而是选择了纵向上更长的一个，必定对之后纵向上比它更长的不优。

对于之后纵向上比它短的不存在影响，可以自行思考。

当我们钦定了一个盒子的时候，需要把它删除。

如果要二分查找，那么存进去的盒子必须具有单调性。

多重集对我们来说肥肠合适。

~~为什么我不用字母表达，因为我不想切换全半角了。~~


```cpp
struct item {
	int x ,y ;
	bool typ ;
	bool operator < (const item &cmp) const { 
		return x == cmp.x ? y == cmp.y ? typ < cmp.typ : y > cmp.y : x > cmp.x ; 
	}
} th[N << 1] ;
multiset < int > se ;
int main () {
	read (n) ,read (m) ;
	f (i ,1 ,n ,1) {
		read (th[i].x) ;
		th[i].typ = 1 ;
	} 
	f (i ,1 ,n ,1) 
		read (th[i].y) ;
	f (i ,1 ,m ,1) {
		read (th[i + n].x) ;
		th[i + n].typ = 0 ;
	}
	f (i ,1 ,m ,1) 
		read (th[i + n].y) ;
	sort (th + 1 ,th + n + m + 1) ;
	f (i ,1 ,n + m ,1) {
		if (! th[i].typ) 
			se.insert (th[i].y) ;
		else {
			multiset < int > :: iterator it = se.lower_bound (th[i].y) ;
			if (it == se.end ()) 
				return puts ("No") ,0 ;
			else 
				se.erase (it) ;
		}
	}
	return puts ("Yes") ,0 ;   
}
```
如果你通过了全部样例，但是不知名地错了，那么是排序比较函数出了问题。注意有这一句话：

``x == cmp.x ? y == cmp.y ? typ < cmp.typ``

在横竖都相同的情况下，我们必须优先放盒子。

---

## 作者：_zhx (赞：0)

# AT_abc245_e [ABC245E] Wrapping Chocolate

### 思路

如果直接暴力，必然 `TLE`，所以，要找一种方法。

看到两个条件：长和宽。我就在想：能不能只满足一个条件，就一定不会错呢？

这肯定是有的，我们先把巧克力和盒子的长按从大到小的顺序排序，然后排宽，顺序也一样。如果都一样，优先级为巧克力大于盒子。

排好序后，就可以开始判断了：

先看是不是巧克力：

- 如果是：用二分找出长宽都大于巧克力且最小的盒子，没找到就 `No`，然后退出程序；找到就删除盒子；

- 如果不是： 就插入一个盒子。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct kkksc03{int a,b,c;}p[600600];  
int n,m;
bool cmp(kkksc03 x,kkksc03 y)
{
	if(x.a==y.a)
	{
		if(x.b==y.b) return x.c<y.c;
		else return x.b>y.b;	
	}
	else return x.a>y.a;
}
multiset<int>s; 
int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>p[i].a,p[i].c=1;
	for (int i=1;i<=n;i++) cin>>p[i].b;
	for (int i=n+1;i<=n+m;i++) cin>>p[i].a;
	for (int i=n+1;i<=n+m;i++) cin>>p[i].b;
	sort(p+1,p+1+n+m,cmp);
	for(int i=1;i<=n+m;i++)
	{
		if(p[i].c==1)
		{
			auto it=s.lower_bound(p[i].b);  
			if(it==s.end()) cout<<"No\n",exit(0);
			s.erase(it);	
		}
		else s.insert(p[i].b);
	}
	cout<<"Yes\n";
	return 0;
}
```

---

## 作者：Mingrui_Yang (赞：0)

[luogu 传送门](https://www.luogu.com.cn/problem/AT_abc245_e)

## 思路

巧克力和盒子都是有两个元素 $x, y$ 确定，所以考虑将它们放在一起排序（这样更为方便）。

按 $x$ 为第一关键字，$y$ 为第二关键字进行从大到小进行排序，大小相同的情况将盒子放在巧克力之前。

排序后，将巧克力或盒子一个一个取出来，将取出来的**盒子**的 $y$ 存下来；如果是**巧克力**，就利用二分找到比巧克力大的第一个盒子，只用查找 $y$ 就可以了（因为排序时是按 $x$ 为第一关键字，$y$ 为第二关键字进行从大到小进行排序，所以存下来的 $y$ 所对应的 $x$ 一定比当前的巧克力的 $x$ 大）。

利用多重集合 `multiset<int> s` 将取出来的**盒子**的 $y$ 进行存储并排序。

如果二分时没找到，就输出 `No`。   
否则就输出 `Yes`。

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m;
struct thing {int x, y, op; } a[N * 2]; // op为1表示是巧克力，否则是盒子 
multiset<int > s;
inline bool cmp(thing a, thing b) {
	if (a.x == b.x) 
		if (a.y == b.y) return a.op < b.op; // 盒子排前面 
		else return a.y > b.y;
	return a.x > b.x;
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ ) cin >> a[i].x;
	for (int i = 1; i <= n; i ++ ) cin >> a[i].y, a[i].op = 1;
	for (int i = 1; i <= m; i ++ ) cin >> a[n + i].x;
	for (int i = 1; i <= m; i ++ ) cin >> a[n + i].y;
	sort(a + 1, a + n + m + 1, cmp);
	for (int i = 1; i <= n + m; i ++ ) {
		if (a[i].op) {
			auto t = s.lower_bound(a[i].y);
			if (t == s.end()) return puts("No"), 0;
			s.erase(t);
		}
		else s.insert(a[i].y);
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：Demons_Killer (赞：0)

# 解题思路：
考虑使用多重集合的贪心。

将盒子和巧克力存到一个数组里，数组的类型是一个结构体，对其进行排序，看一下哪些的宽可以满足。再利用多重队列的单调性，确定哪些长可以满足。如果有巧克力找不到合适的盒子，就直接输出 `No`，程序结束。如果都找到了合适的盒子，就输出 `Yes`。

# code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
struct node{
	int x,y,op;
}a[N<<1];
int c[N];
int n,m;
bool vis[N];
multiset<int> st;
bool cmp(node a,node b){
    if(a.x==b.x){
		if(a.y==b.y){
			return a.op<b.op;
		}
        return a.y>b.y;
    }
    return a.x>b.x;
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	int cnt1=n,cnt2=m;
	for(int i=1;i<=n;i++) {
		cin>>a[i].x;
		a[i].op=1;
	}
	for(int i=1;i<=n;i++) cin>>a[i].y;
	for(int i=n+1;i<=n+m;i++) cin>>a[i].x;
	for(int i=n+1;i<=n+m;i++) cin>>a[i].y;
	sort(a+1,a+1+n+m,cmp);
	for(int i=1;i<=n+m;i++){
        if(a[i].op==1){
        	set<int>::iterator it=st.lower_bound(a[i].y);
        	if(it==st.end()){
        		cout<<"No";
        		return 0;
			}
			st.erase(it);
		}
		else{
			st.insert(a[i].y);
		}
    }
	cout<<"Yes"<<endl;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc245_e)

## 思路

用 STL 中的 multiset 和结构体排序来做。

把两组数据合并成为一个序列排序，然后在结构体中定义一个 ``flag`` 变量标记这组数是盒子还是巧克力。之后按照长度第一标准、类型第二标准**从大到小**排序。

从 $1$ 到 $n+m$ 循环，如果当前这组数是盒子，就把宽度放入集合中。经过集合和排序的处理后，这时就可以保证能找到**最小的又可以装下巧克力**的盒子序列。

循环时，如果当前这组数是巧克力，那就从集合中利用 ``lower_bound `` 函数查找能把当前巧克力装下的**最小的**盒子。如果找到的位置是 ``end()``，就说明没有能装下的，输出``No``，直接结束程序。循环完后如果没输出过 ``No``，就说明所有巧克力都能装下，输出 ``Yes`` 结束程序。

- 每次找到配对的巧克力盒子后记得删除这个盒子，否则可能出现一个盒子装多个巧克力的情况。

这里不放代码了，根据上面的思路一步步写即可。

---

