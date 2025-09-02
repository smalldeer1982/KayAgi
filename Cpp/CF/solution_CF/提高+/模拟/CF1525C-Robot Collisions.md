# Robot Collisions

## 题目描述

There are $ n $ robots driving along an OX axis. There are also two walls: one is at coordinate $ 0 $ and one is at coordinate $ m $ .

The $ i $ -th robot starts at an integer coordinate $ x_i~(0 < x_i < m) $ and moves either left (towards the $ 0 $ ) or right with the speed of $ 1 $ unit per second. No two robots start at the same coordinate.

Whenever a robot reaches a wall, it turns around instantly and continues his ride in the opposite direction with the same speed.

Whenever several robots meet at the same integer coordinate, they collide and explode into dust. Once a robot has exploded, it doesn't collide with any other robot. Note that if several robots meet at a non-integer coordinate, nothing happens.

For each robot find out if it ever explodes and print the time of explosion if it happens and $ -1 $ otherwise.

## 说明/提示

Here is the picture for the seconds $ 0, 1, 2 $ and $ 3 $ of the first testcase:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1525C/473eb674d2e11be570d6b54a87dfca3a963d4212.png)Notice that robots $ 2 $ and $ 3 $ don't collide because they meet at the same point $ 2.5 $ , which is not integer.

After second $ 3 $ robot $ 6 $ just drive infinitely because there's no robot to collide with.

## 样例 #1

### 输入

```
5
7 12
1 2 3 4 9 10 11
R R L L R R R
2 10
1 6
R R
2 10
1 3
L L
1 10
5
R
7 8
6 1 7 2 3 5 4
R L R L L L L```

### 输出

```
1 1 1 1 2 -1 2 
-1 -1 
2 2 
-1 
-1 2 7 3 2 7 3```

# 题解

## 作者：SSerxhs (赞：15)

首先按位置奇偶分类，只有奇偶性相同才会相撞。

不考虑反弹的情况下，如果记 $\texttt R$ 为 $\texttt ($，$\texttt L$ 为 $\texttt )$，那么碰撞情况等于括号匹配情况，用栈维护即可。

考虑从 $x=0$ 反弹，那么如果当前出现了一个失配的右括号，它不可能与前面的括号匹配，等价于坐标变为 $-x$ 并向右走。因此可以翻转括号并改变坐标，入栈。

考虑从 $x=m$ 反弹，显然是进行完所有括号匹配后剩下的 $\texttt ($ 有一部分反弹，且反弹的恰好为剩下的一半。那么同样坐标变为 $2m-x$ 再翻转括号即可。

```cpp
struct Q
{
	int u,v,w;//坐标，是否为 L，原下标
	bool operator<(const Q &o) const {return u<o.u;}
};
void cal()
{
	sort(a+1,a+n+1);tp=0;
	for (i=1;i<=n;i++) if (a[i].v)
	{
		if (!tp)
		{
			a[i].u=-a[i].u;a[i].v=0;
			st[++tp]=a[i];
		}
		else
		{
			ans[a[i].w]=ans[st[tp].w]=a[i].u-st[tp].u>>1;
			--tp;
		}
	}
	else
	{
		st[++tp]=a[i];
	}
	if (tp<=1) return;
	if (tp&1) {for (i=1;i<tp;i++) st[i]=st[i+1];--tp;}
	for (i=2;i<=tp;i+=2) st[i].u=2*m-st[i].u;
	for (i=1;i<=tp;i+=2) ans[st[i].w]=ans[st[i+1].w]=st[i+1].u-st[i].u>>1;
}
```

---

## 作者：ZCETHAN (赞：5)

[传送门](http://codeforces.com/problemset/problem/1525/C)
## 题目大意
在一条数轴上有 $n$ 个机器人，每个机器人有一个初始的朝向，之后每一秒，它会向着它朝向的方向走一个单位，如果到达了 $0$ 或者 $m$ 那么就会立即掉头。如果多个机器人在同一整数点相遇，那么它们就会碰撞炸掉，在此之后就不会与其他机器人碰撞了。现需要你求出每个机器人最早在第几时刻炸掉，如果不会，则输出 `-1`。

## Solution
首先是注意一点：当且仅当两个机器人奇偶性相同时才会相撞，并且没有意外是一定会相撞的。

可以很简单地证一下，每一次移动每一个机器人的位置奇偶性都会改变，如果两个机器人的奇偶性不同，那么任意时刻其奇偶性都是不同的，也就不可能同时在一个整数点相遇了。

所以我们可以对每个点进行奇偶分类。

然后对于每组，我们考虑机器人相撞，可以发现如果两个机器人是相对的并且中间没有其他机器人，那么必定是这两个机器人相撞……等等，这不就是括号匹配么。所以用一个栈维护一下就可以把所有相对的机器人处理掉，最后只剩下：`L...LR...R` 这样的朝向，此时，我们对两边分别进行处理，对于向左的，最左边转向后必定和左边第二个相撞，左边第三个必定转向后和左边第四个相撞……右边也是同理。

这样处理完后，可能会剩下 $1$ 个或者 $2$ 个机器人，如果是 $1$ 个，那么没有人与之相撞，则答案为 `-1`，否则，剩下 $2$ 个朝向是这样的：`LR`，让它们两个走到头再转向回来相撞即可。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1<<30
#define int long long
using namespace std;
const int MAXN=3e5+10;
struct node{
	int pos,id;
	char dir;
	node(){}
	node(int _pos,int _id,char _dir){
		pos=_pos;id=_id;dir=_dir;
	}
	bool friend operator<(node a,node b){
		return a.pos<b.pos;
	}
}odd[MAXN],eve[MAXN],bas[MAXN];
int stk[MAXN],top,ans[MAXN];
int bin[MAXN],hed;
void solve(){
	int n,m,ocnt=0,ecnt=0;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&bas[i].pos),bas[i].id=i;
	for(int i=1;i<=n;i++)
		scanf(" %c",&bas[i].dir);
	sort(bas+1,bas+1+n);//记得排序
	for(int i=1;i<=n;i++){
		if(bas[i].pos&1) odd[++ocnt]=bas[i];
		else eve[++ecnt]=bas[i];
	}//奇偶分组
	
	top=0;hed=0;
	for(int i=1;i<=ocnt;i++){
		if(odd[i].dir=='R') stk[++top]=i;
		else{
			if(!top) bin[++hed]=i;//如果栈空，说明这个向左的是多出来的，存着就行
			else{
				int j=stk[top--];
				ans[odd[i].id]=ans[odd[j].id]=(odd[i].pos-odd[j].pos)/2;
			}
		}
	}//做括号匹配，把相对的消去，变成 L...LR...R 的形式
	for(int i=1;i<hed;i+=2){
		ans[odd[bin[i]].id]=ans[odd[bin[i+1]].id]=(odd[bin[i+1]].pos-odd[bin[i]].pos)/2+odd[bin[i]].pos;
	}//处理向左多出来的部分，两两相撞
	for(int i=top;i>1;i-=2){
		ans[odd[stk[i]].id]=ans[odd[stk[i-1]].id]=(odd[stk[i]].pos-odd[stk[i-1]].pos)/2+m-odd[stk[i]].pos;
	}//stk 中多出来的就是向右多余的，也是一样处理
	if(hed%2&&top%2){//如果两个都有 1 个剩余，那么把它们继续撞
		ans[odd[bin[hed]].id]=ans[odd[stk[1]].id]=(odd[bin[hed]].pos+m-odd[stk[1]].pos+m)/2;
	}else if(hed%2) ans[odd[bin[hed]].id]=-1;
	else if(top%2) ans[odd[stk[1]].id]=-1;//否则答案就是 -1
	/*                处理奇数                  */
	top=0;hed=0;
	for(int i=1;i<=ecnt;i++){
		if(eve[i].dir=='R') stk[++top]=i;
		else{
			if(!top) bin[++hed]=i;
			else{
				int j=stk[top--];
				ans[eve[i].id]=ans[eve[j].id]=(eve[i].pos-eve[j].pos)/2;
			}
		}
	}
	for(int i=1;i<hed;i+=2){
		ans[eve[bin[i]].id]=ans[eve[bin[i+1]].id]=(eve[bin[i+1]].pos-eve[bin[i]].pos)/2+eve[bin[i]].pos;
	}for(int i=top;i>1;i-=2){
		ans[eve[stk[i]].id]=ans[eve[stk[i-1]].id]=(eve[stk[i]].pos-eve[stk[i-1]].pos)/2+m-eve[stk[i]].pos;
	}if(hed%2&&top%2){
		ans[eve[bin[hed]].id]=ans[eve[stk[1]].id]=(eve[bin[hed]].pos+m-eve[stk[1]].pos+m)/2;
	}else if(hed%2) ans[eve[bin[hed]].id]=-1;
	else if(top%2) ans[eve[stk[1]].id]=-1;
	//和奇数完全一样
	/*                处理偶数                  */
	for(int i=1;i<=n;i++)
		printf("%lld ",ans[i]);
	printf("\n");
}
signed main()
{
	int T;
	for(scanf("%lld",&T);T--;)
		solve();
}
```

---

## 作者：lsj2009 (赞：2)

### Solution

比较好的膜你题。

考虑到两个机器人最初坐标分别为 $x_1,x_2$，经过若干时刻后为 $x_1',x_2'$，那么显然的是 $|x_1-x_2|$ 和 $|x_1'-x_2'|$ 奇偶性相等，进一步得，只有最开始都在偶数处得机器人可以相撞，都在奇数处的机器人可以相撞。

那么我们将奇、偶两种情况分开了考虑。

容易把两个机器人的碰撞类似的看作一个括号匹配，即将向右的机器人看作 ``(``，向左的机器人看作 ``)``，然后相邻的一对 ``()`` 成功爆炸。

则将所有直接爆炸的机器人全部配对后，只剩下形如 ``)))(((((`` 的情况，手膜一下可以发现，我们把前半部分和后半部分分开来，变成 ``)))`` 和 ``(((((``。

对于 ``))...)`` 而言，依次为第 $1,2$，然后第 $2,3$……个机器人依次碰撞。

对于 ``(...((`` 而言，依次为倒数第 $1,2$，然后倒数第 $2,3$……个机器人依次碰撞。

最终可能左右会各自余下多余至多 $1$ 个机器人；如果剩一个，那那个机器人就永远炸不掉，否则剩两个再炸一次即可。

然后就做完了，复杂度瓶颈在于排序，为 $\Theta(n\log{n})$。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=3e5+5;
struct node {
	int x,v,belong;
	bool operator < (const node &tmp) const {
		return x<tmp.x;
	}
}; 
int a[N],ans[N],n,m;
void solve(vector<node> vec) {
	sort(vec.begin(),vec.end());
	stack<node> s;
	for(auto t:vec) {
		int x=t.x,v=t.v,b=t.belong;
		if(!s.empty()&&s.top().v==1&&v==-1) {
			int x1=s.top().x,b1=s.top().belong; s.pop();
			ans[b]=ans[b1]=(x-x1)/2;
		} else
			s.push(t);
	}
	vector<node> v1,v2;
	for(auto t:vec) {
		if(ans[t.belong]!=-1)
			continue;
		if(t.v==-1)
			v1.push_back(t);
		else
			v2.push_back(t);
	}
	reverse(v2.begin(),v2.end());
	int lx=-1,lb=-1,tx=-1,tb=-1;
	for(auto t:v1) {
		int x=t.x,b=t.belong;
		if(lb!=-1) {
			ans[lb]=ans[b]=lx+(x-lx)/2;
			lx=lb=-1;
		} else
			lb=b,lx=x;
	}
	if(lb!=-1) {
		tb=lb; tx=lx;
		lb=lx=-1;
	}
	for(auto t:v2) {
		int x=t.x,b=t.belong;
		if(lb!=-1) {
			ans[lb]=ans[b]=m-lx+(lx-x)/2;
			lx=lb=-1;
		} else
			lb=b,lx=x;
	}
	if(tb!=-1&&lb!=-1)
		ans[tb]=ans[lb]=(tx+m-lx+m)/2;
}
void solve() {
	cl(ans,-1);
	vector<node> v1,v2;
	scanf("%d%d",&n,&m);
	rep(i,1,n)
		scanf("%d",&a[i]);
	rep(i,1,n) {
		char ch;
		cin>>ch;
		if(a[i]&1)
			v1.push_back({a[i],ch=='L'? -1:1,i});
		else
			v2.push_back({a[i],ch=='L'? -1:1,i});
	}
	solve(v1); solve(v2);
	rep(i,1,n)
		printf("%d ",ans[i]);
	puts("");
}
signed main() {
	int testcase;
	scanf("%d",&testcase);
	while(testcase--)
		solve();
    return 0;
}
```

---

## 作者：灵茶山艾府 (赞：2)

显然坐标奇偶性不同的机器人不会相撞。

那么按照坐标奇偶性分为两组。对于每一组，按坐标排序，然后用栈来维护相撞，类似括号匹配的过程，把向右的当成是左括号，向左的当成是右括号，每一对括号就是一次相撞。

撞完之后剩下的机器人，必然是若干个向左的，以及若干个向右的。

这些向左的会与在遇到墙之后反向，然后与其他向左的相撞。对于向右的同理。

最后向左的至多剩下一个，向右的至多剩下一个。若都剩下一个，那就再撞一次。

AC 代码：（Golang）

```go
package main

import (
	"bufio"
	. "fmt"
	. "os"
	"sort"
)

type robot struct {
	x, i  int
	right bool
}

func main() {
	in := bufio.NewReader(Stdin)
	out := bufio.NewWriter(Stdout)
	defer out.Flush()

	var T, n, m int
	var dir string
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n, &m)
		robots := [2][]robot{}
		pos := make([]int, n)
		for i := range pos {
			Fscan(in, &pos[i])
		}
		for i, x := range pos {
			Fscan(in, &dir)
			robots[x&1] = append(robots[x&1], robot{x, i, dir == "R"})
		}

		ans := make([]int, n)
		for _, a := range robots {
			sort.Slice(a, func(i, j int) bool { return a[i].x < a[j].x })
			var l, r []robot
			for _, p := range a {
				if p.right {
					r = append(r, p)
				} else if len(r) == 0 {
					l = append(l, p)
				} else {
					q := r[len(r)-1]
					r = r[:len(r)-1]
					t := (p.x - q.x) / 2
					ans[p.i] = t
					ans[q.i] = t
				}
			}
			for len(l) > 1 {
				p, q := l[0], l[1]
				l = l[2:]
				t := (p.x + q.x) / 2
				ans[p.i] = t
				ans[q.i] = t
			}
			for len(r) > 1 {
				p, q := r[len(r)-1], r[len(r)-2]
				r = r[:len(r)-2]
				t := (2*m - p.x - q.x) / 2
				ans[p.i] = t
				ans[q.i] = t
			}
			if len(l) == 1 && len(r) == 1 {
				p, q := l[0], r[0]
				t := (2*m - q.x + p.x) / 2
				ans[p.i] = t
				ans[q.i] = t
			}
		}
		for _, t := range ans {
			if t == 0 {
				t = -1
			}
			Fprint(out, t, " ")
		}
		Fprintln(out)
	}
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

只有奇偶性相同的机器人才会发生碰撞。

所以分奇偶考虑，假设现在考虑其中一种奇偶性：

把向右走的机器人看成 `(`，向左走的看成 `)`。那么原序列离散化之后就是一个括号序列，我们可以先跑一遍括号匹配。

剩下的一定是 `))...))((...(` 的形式，不难发现左边的第奇数个括号反弹之后会和第偶数个相撞爆炸。

那么就剩下 1~2 个括号，如果是 1 个那就是 -1，否则这两个会反弹之后相撞。

复杂度 $O(n \log n)$。

## 代码

[Code & Submission](https://codeforces.com/contest/1525/submission/219993426)

---

