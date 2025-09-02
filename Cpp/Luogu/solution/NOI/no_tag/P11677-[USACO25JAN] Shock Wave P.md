# [USACO25JAN] Shock Wave P

## 题目描述

Bessie 正在试验一种能够产生巨大冲击波的强大的蹄部植入物。她有 $N$（$2 \leq N \leq 10^5$）块砖块排开在面前，分别需要至少 $p_0,p_1,\dots,p_{N-1}$ 的力量才能击破（$0 \leq p_i \leq 10^{18}$）。

Bessie 可以通过击打特定的砖块来施加力量，但由于她的植入物的奇特性质，它不会对她所击打的那块砖块施加任何力量。相反，如果她选择击打砖块 $x$ 一次，其中 $x$ 是一个 $[0,N-1]$ 范围内的整数，对所有在 $[0,N-1]$ 范围内的整数 $i$，它将对砖块 $i$ 施加 $|i-x|$ 的力量。同时这个力量是累积的，因此对一块砖块施加两次 $2$ 的力量将对该砖块施加总共 $4$ 的力量。

请求出击破所有砖块所需要的最少击打次数。

## 说明/提示

样例 1 解释：

在第一个测试用例中，Bessie 通过两次击打击破所有砖块的唯一方法是击打砖块 $0$ 两次，施加总力量分别为 $[0,2,4,6,8]$。

在第二个测试用例中，Bessie 通过三次击打击破所有砖块的一种方法是分别击打砖块 $0$，$2$ 和 $4$ 一次，施加总力量分别为 $[6,5,4,5,6]$。

在第三个测试用例中，Bessie 通过两次击打击破所有砖块的一种方法是分别击打砖块 $0$ 和 $1$ 一次，施加总力量分别为 $[1,1,3,5,7]$。

- 测试点 $2$：所有 $p_i$ 均相等。
- 测试点 $3\sim 6$：$N\le 100$。
- 测试点 $7\sim 14$：没有额外限制。

## 样例 #1

### 输入

```
6
5
0 2 4 5 8
5
6 5 4 5 6
5
1 1 1 1 1
5
12 10 8 6 4
7
6 1 2 3 5 8 13
2
1000000000000000000 1000000000000000000```

### 输出

```
2
3
2
4
4
2000000000000000000
```

# 题解

## 作者：SnowTrace (赞：8)

场上奋战两个半小时，最后二十分钟推出来性质，最后获得零分。

---
这个题要你刻画的是若干个绝对值函数的加和的性质。

我们把问题变成维护一个一开始全为 0 的序列 $b$，每次给序列 $b$ 加上一个绝对值函数，问需要多少次使得 $\forall i,b_i\geq a_i$。

既然刻画不明白，我们先考虑一些简单的性质。首先我们可以发现一件事情是你操作不同的位置，对 $\sum b_i$ 的贡献是不同的，具体来说，操作位置 $1$ 和 $n$ 能使序列 $b$ 的和单次增加最多。

然后你发现如果同时在 $1$ 和 $n$ 上做操作相当于给每个 $b_i$ 都加上 $n-1$，从而我们可以使用这个策略通过 sub1，容易证明这是最优的。

继续观察。注意到如果你同时选了 $i$ 和 $n-i$，这个操作肯定不如选 $1$ 和 $n$，所以我们得到结论 $i$ 和 $n-i$ 不能同时选。

很可惜这个结论没有用，但是令人惊讶的是这个结论是可以推广的，具体来说，如果你操作了两个位置 $1<x<y<n$，你不如操作 $x-1$ 和 $y+1$。

由此归纳出一个结论：**在最优解中一定是选了若干个 $1$，若干个 $n$，和****一个****其他位置**。证明考虑假如现在有两个不为 $1$ 或 $n$ 的位置，一定可以通过上面的变化把其中一个变成 $1$ 或 $n$）

问题变成下面这个形式，设 $1$ 操作了 $x$ 次，$n$ 操作了 $y$ 次，还在位置 $m$ 选了一个数，则有限制 $\forall i,ix+(n-i)y+|m-i|\geq a_i$，你需要最小化 $x+y$ 的值。

我们先考虑暴力是怎么做，首先枚举一个 $m$，因为我们要求的是 $x+y$ 的最小值，把 $x+y$ 提出来处理，然后就可以二分答案，既 $(x+y)(n-i)+(2i-n)x+|m-i|\geq a_i $，可以对其二分，会得到若干对 $x$ 的限制，时间复杂度 $O(n^2\log V)$。

接下来我们观察到第二个性质：**如果规定只能操作 $1$ 和 $n$，得到的答案最多比最优解多 1。**

这个结论是显然的，因为选择的 $m$ 显然可以用一个 $1$ 和一个 $n$ 代替，从而可以取到 $ans+1$。

我们可以先二分答案求出来只用 $1$ 和 $n$ 时的答案，设为 $ans$，接下来我们只需要判断 $ans-1$ 是否能被取到。

我们希望对于不同的 $m$ 同时维护 check 的结果。可以先把式子列出来，不妨设 $2i \geq n$，则需要 $x \geq \dfrac{a_i+(x+y)(n-i)+|m-i|}{2i-n}$，由于我们需要 check 的答案固定，所以右边其实是个常数。

接下来考虑 $m$ 改变对这个式子的影响，注意到对于一个 $i$，$|m-i|$ 的变化量是 $O(n)$ 的，所以实际上右边式子的值只会改变 $O(\dfrac{n}{2i-n})$ 次，这是可以维护的。

具体来说我们可以用一个优先队列维护当前最严格的限制，这样做时间复杂度是 $O(n\log n\log V)$ 的，但是注意到操作是 $O(n\log n)$ 次区间取 $\max$，只需要在最后输出每个位置的值，可以使用猫树优化，这样时间复杂度是 $O(n\log V)$ 的。

实际上 $2i-n$ 可以是一个负数，也可以是 0，需要特判。

代码正在赶工中，因为负数除负数上下取整实在写不明白了。

upd on 2.6: 奋战四个小时终于把代码写出来了，感觉其实和季风差不多，但是写不明白啊。


```cpp
//非常优美的题，但是代码太毒瘤了 
#include<bits/stdc++.h>
using namespace std;
#define int long long
int Abs(__int128 x){if(x<0)return -x;return x;}
__int128 chu(__int128 x,int y){
	//向上取整
	return (x+y-1)/y;
}
__int128 Chu(__int128 x,int y){
	//向下取整
	if(x<=0 and y<0)return (-x)/(-y);
 	else return -1;
}
int n;
__int128 a[500005];int b[500005];
bool check(__int128 x){
	__int128 L = 0,R = x;
	for(int i = 0;i<=n;i++){
		if(2*i == n){
			if(x*(n-i)<a[i])return 0;
			continue;
		}
		if(2*i<n){
			//是一个负数
			__int128 C = a[i]-(n-i)*x;
			R = min(R,Chu(C,2*i-n)); 
		}else{
			__int128 C = a[i]-(n-i)*x;
			L = max(L,chu(C,2*i-n));
		}
	}
	return (L<=R);
}
struct heap{
	priority_queue<int,vector<int>,greater<int> >q,del;
	void clear(){while(q.size())q.pop();while(del.size())del.pop();}
	void Delete(int x){del.push(x);}
	void Insert(int x){q.push(x);}
	int top(){
		while(del.size() and q.top() == del.top())q.pop(),del.pop();
		return q.top();
	}
}ql,qr;
vector<int>addl[500005],dell[500005],addr[500005],delr[500005];
void Addl(int l,int r,int x,int id){
	//给一段区间加上 x 的限制
	addl[l].push_back(-x),dell[r+1].push_back(-x); 
}
void Addr(int l,int r,int x,int id){
	addr[l].push_back(x),delr[r+1].push_back(x);
}

int work(int X){
	ql.clear(),qr.clear();
	ql.Insert(0),qr.Insert(X);
	for(int i =0;i<=n+1;i++)addl[i].clear(),dell[i].clear(),addr[i].clear(),delr[i].clear();
	int i = n;
	for(int i = 0;i<=n;i++)a[i] -= (n-i)*X; 
	while(2*i>n){
		// n-2i
		int now = i;
		while(now<=n){
			// (0,a] 算一段
			//算出和这个点值相同的最远的点
			__int128 C = a[i]-abs(now-i),to = 0;
			//对于更远的点 C 的数值会减小
			if(C<=0){
				to = 0;
			}else{
				to = C/(2*i-n)*(2*i-n)+1;
				if(C%(2*i-n) == 0)to = C-(2*i-n)+1;
			}
			int r = min(Abs(to-C)+now,n);
		
			if(C>0){
				Addl(now,r,chu(C,i*2-n),i);
			}
			now = r+1;
		}
		now = i-1;
		while(now>=0){
			__int128 C = a[i]-abs(now-i),to = 0;
			if(C<=0){
				to = 0;
			}else{
				to = C/(n-2*i)*(n-2*i)+1;
				if(C%(2*i-n) == 0)to = C-(2*i-n)+1;
			} 
			int l = max(now-Abs(to-C),0ll);
			if(C>0){
				Addl(l,now,chu(C,i*2-n),i);
			}
			now = l-1;
		}
		--i;
	}
	i = 0;
	while(2*i<n){
		int now = i;
		while(now<=n){
			__int128 C = a[i]-abs(now-i),to = 0;
			if(C<=0){
				to = -C;
				if(to%(n-2*i)!=0)to += (n-2*i)-to%(n-2*i);
				else to += (n-2*i);
				--to;
				to = -to;
			}else{
				to = 0;
			}
			int r = min(Abs(to-C)+now,n);
			if(C>0)Addr(now,r,-1,i);
			else Addr(now,r,Chu(C,i*2-n),i);
			now = r+1;
		}
		now = i-1;
		while(now>=0){
			__int128 C = a[i]-abs(now-i),to = 0;
			if(C<=0){
				to = -C;
				if(to%(n-2*i)!=0)to += (n-2*i)-to%(n-2*i);
				else to += (n-2*i);
				--to;
				to = -to;
			}else{
				to = 0;
			}
			int l = max(now-Abs(to-C),0ll);
			if(C>0)Addr(l,now,-1,i);
			else Addr(l,now,Chu(C,i*2-n),i);
			now = l-1; 
		}
		++i;
	}
	for(int i = 0;i<=n;i++){
		for(auto x:addl[i])ql.Insert(x);
		for(auto x:dell[i])ql.Delete(x);
		for(auto x:addr[i])qr.Insert(x);
		for(auto x:delr[i])qr.Delete(x);
		if(n%2 == 0 and (a[n/2]-abs(n/2-i))>0)continue;
		int L = -ql.top(),R = qr.top();
		if(L<=R)return 1;
	}
	return 0;
}
void solve(){
	cin >> n;--n;
	for(int i = 0;i<=n;i++)cin >> b[i];for(int i = 0;i<=n;i++)a[i] = b[i];
	__int128 sum = 0;int mx = 0;for(int i = 0;i<=n;i++)sum += b[i],mx = max(mx,b[i]);
	int l = sum/n/n,r = 2*(mx+n-1)/n;
	while(l<r){
		int mid = l+r>>1;
		if(check(mid))r = mid;
		else l = mid+1;
	}
	int ans = r;
	if(ans>1 and work(ans-2))--ans;
	cout << ans << '\n';
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;cin >> t;;
	while(t--)solve();
	return 0;
}/*
*/
```

---

## 作者：qiuzx (赞：4)

注意到很多在中间的操作是没用的。具体来说，如果存在操作 $i,j$ 满足 $0<i<j<n-1$，则将它们换成 $i-1,j+1$，每个位置都一定不会被减去更少的值。因此至多存在一个操作不是 $0$ 或 $n-1$。

先假设所有操作都是 $0/n-1$，考虑怎么计算答案。二分答案 $lim$，则需要计算能否在 $lim$ 次操作内将所有位置清零。设使用了 $x$ 次 $0$ 操作，那么一定是使用了 $lim-x$ 次 $n-1$ 操作。此时每个位置 $i$ 的限制可以被看作 $i\times x+(n-i-1)(lim-x)\ge p_i$，这是一个与 $x$ 有关的线性不等式。综合所有不等式，可以得到 $x$ 的取值范围为若干区间的交，只需考察这个区间中是否存在一个整数 $x$ 满足 $0\le x\le lim$ 即可，复杂度 $O(n)$。

这样立刻得到了一个原题的 $O(n^2\log v)$ 做法，只需枚举中间的一次操作是哪里，然后使用上述判定方法即可。为了优化，考虑在移动中间的一次操作时所有线性不等式的变化是怎么样的。

注意到第 $i$ 个位置的限制形如 $(2i-n)x\ge V_i+p_i$，其中 $V_i$ 是一个定值，与 $p_i$（即中间的操作选在哪里）无关。而中间位置的不同会使得 $p_i$ 变化不超过 $n$。因此中间位置的变动会使得这个限制中 $x$ 的整数取值范围发生变化的次数是 $O(\frac{n}{|2i-n|})$，特判一下 $2i=n$ 的情况，然后对剩余的情况求和，可以发现总的变化量是 $O(n\log n)$。

于是我们处理出所有所有这些限制变化的位置，将它们在序列对应位置上打标记。然后做扫描线枚举中间位置，使用两个 set 分别维护当前所有 $x\ge v$ 和 $x\le v$ 的限制。在遇到标记时做对应的插入删除操作即可，复杂度 $O(n\log^2n)$。这样我们得到了一个 $O(n\log^2n\log v)$ 的做法，显然不能通过。

但可以发现一次中间的操作对于整体局面的影响是很小的，如果在不考虑中间操作的情况下不合法，那么考虑它也很可能是不合法的。具体来说，如果在使用一次中间操作的情况下合法，那么将它替换为两个操作 $0,n-1$ 一定是严格更优的。从而如果在不考虑中间操作的情况下算出来的答案为 $v$，那么考虑中间操作时答案至少也得是 $v-1$。所以我们只需在二分结束后 check 一次中间操作能否使得答案变为 $v-1$ 即可。这样复杂度就变为 $O(n\log^2n+n\log v)$，可以通过。

实际上也有一些方式将 check 的复杂度做到 $O(\log n)$，不过会增加一些实现的难度，故没有必要。

[代码](https://www.luogu.com.cn/paste/w16bjrqw)

---

## 作者：NoirCube1 (赞：1)

- [Link](https://www.luogu.com.cn/problem/P11677), USACO 2025 Jan Plantinum T2.

好题，做个记录。

读者可以根据个人需求选择跳读标有**实现上**的部分。

笔者根据习惯把这个题变成 1-indexed 的了，希望影响不大。

最终还是没能全靠自己写出来这个题。

## Solution

### Hint 1：

不如先手玩一些性质。如果有任意两次操作 $(x,y)$，满足 $1<x\leq y<n$，那么我们可以尝试操作 $(x-1,y+1)$，这样对每个 $a_i$ 的削减效果一定会增强。我们用绝对值的几何意义显然可以证明。

那么对于一个最优的操作序列，对于任何两个操作，总有一个是 $1$ 或者 $N$，换句话说，最优的操作序列满足：在 $1<x<N$ 的操作 $x$ 只有最多一次。

### Hint 2：

考虑如果忽略这个多出来的 $x$ 操作，我们只考虑在 $1$ 和 $N$ 的位置上操作，那么你会注意到如果少了一次 $x$ 并且多了 $1$ 和 $N$ 两次操作依旧可以达到要求。因此我们就注意到忽略 $x$ 操作得到的答案最多比正确答案大 $1$。

于是放心思考如果只存在 $1$ 操作和 $N$ 操作，那么考虑二分答案，检验能否在 $m$ 次操作内完成要求。如果有 $b$ 次 $1$ 操作，$m-b$ 次 $N$ 操作，我们显然可以知道每个位置上会产生多少击打效果。因此，我们只需要解 $n$ 个形如 $f_i(b)\ge a_i$ 的不等式，显然可以单次 $\mathcal O(n)$ 判定可行性，可以接受。

### Hint 2.5

**实现上**，具体的来说，这个式子就是 $(2i-1-N)b\ge a_i-(N-i)m$，注意要讨论左面系数的正负，当然 $0$ 也要特判。当然，你只需要保留 $b$ 的整数解，但是显然你需要考虑取整的方向。

可能要注意一下二分的上界。

### Hint 3

考虑加入这个题最抽象并且难写的一部分：$x$ 操作。

根据我们在 Hint 2 中写到的结论：忽略 $x$ 操作得到的答案最多比正确答案大 $1$，我们只需要判定是否可以在执行了一次 $x$ 操作之后是否有可能在**原答案减二次操作内**解决问题就行了。如果沿用上面的解不等式方式，显然会复杂度爆炸，但是注意到如果我们枚举 $x$ 从 $2$ 到 $N-1$，相邻两个要检查的序列之间每个数只会相差一，所以我们原先的计算方法必然有很大的浪费。

着手观察我们手上的式子：$(2i-1-N)b\ge a'_i-(N-i)m$，事实上，在 $a'_i$ 改变的时候，只会有很少的情况下会改变该不等式的正整数解集。对于每个 $i$ 号不等式，显然只会有 $\dfrac{N}{|2i-1-N|}$ 次解的调整。

鉴于 $\mathcal O\left(\displaystyle\sum_{i=1}^{N}\dfrac{N}{|2i-1-N|}\right)=\mathcal O(N\ln N)$，理论是可行的。

### Hint 3.5

非常难写的取整。笔者的一生之敌，所以借鉴了一些简便的写法。

**实现上**，对于 $n$ 个不等式分别维护解集 $[l_i,r_i]$，枚举 $x$，此时只需要在需要的时候维护区间 $l_i\gets \max(l_i, V)$ 和区间 $r_i\gets \min(r_i,V)$。这里采用一种 ST 表的聪明用法：因为我们只需要维护结果序列，而不用在中间过程中询问，所以我们只要在修改的时候放 $[L,R]$ 的标记，在最后维护序列的时候从高位往低位放标记就行了。

综上，理论上你应该可以写出一份正确的代码了。不过各人还是见仁见智，题解区提到的把上下取整交给常数也是考场求稳的方法。

文章完成于联合省选前夜，祝看到这的你可以在 OI 上打出自己的一片天地。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P11677)

**题目大意**

> 给定 $a_1\sim a_n$，每次操作可以选择 $x\in[1,n]$，然后令每个 $a_i$ 减去 $|i-x|$，求让所有 $a_i\le 0$ 的最小代价。
>
> 数据范围：$n\le 10^5$。

**思路分析**

首先注意到操作 $1<x\le y<n$ 一定不如操作 $x-1,y+1$。

那么我们不断调整，最终 $(1,n)$ 中的操作只有 $\le 1$ 个。

先考虑全部在 $1,n$ 上操作的情况，二分答案 $z$，并假设有 $k$ 个操作在 $1$ 上，则 $k(i-1)+(n-i)(z-k)\ge a_i$，化简得到 $(2i-n-1)k\ge a_i-(n-i)z$。

简记为 $d_ik\ge s_i$，则我们求出所有 $k$ 解集的交，如果非空说明合法。

可以 $\mathcal O(n\log V)$ 求解，枚举 $(1,n)$ 中的操作 $x$，然后分别二分，可以做到 $\mathcal O(n^2\log V)$。

注意到如果我们在 $(1,n)$ 中操作了 $x$，那么把这个操作替换成 $1,n$ 两次操作一定也合法。

因此假设 $z_0$ 是不操作 $(1,n)$ 的最优解，$z_1$ 是操作 $(1,n)$ 的最优解，则 $z_1+1\le z_0$。

那么我们只要判断是否有 $z_1=z_0-1$，也就是操作 $x$ 后剩下的数是否能在 $z_0-2$ 次操作内完成，复杂度 $\mathcal O(n^2)$。

对每个 $x$，我们统一维护 $k$ 的上下界 $l_x,r_x$。

对于 $d_i>0$ 的点，我们会让 $r_x$ 和 $\left\lfloor\dfrac{s_i-|i-x|}{d_i}\right\rfloor$ 取 $\min$。

可以发现这个函数可以分成 $\mathcal O\left(\dfrac{n}{d_i}\right)$ 段，而 $d$ 是 $n-1,n-3,\dots$，那么总段数均摊 $\mathcal O(n\log n)$，对于 $d_i<0$ 的点也是类似的。

那么我们只要支持快速区间 chkmin，并且最终求出所有 $r_x$。

可以用类似 ST 表的结构，$f(i,k)$ 表示对 $r[i,i+2^k)$ 的修改，求答案的时候按 $k$ 从大到小下放标记，可以做到 $\mathcal O(1)-\mathcal O(n\log n)$。

时间复杂度 $\mathcal O(n\log  V+n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline void chkmin(ll &x,const ll &y) { x=y<x?y:x; }
inline void chkmax(ll &x,const ll &y) { x=y>x?y:x; }
const int MAXN=1e5+5;
int n;
ll a[MAXN],b[MAXN];
bool chk(ll z) {
	ll l=0,r=z;
	for(int i=1;i<=n;++i) {
		ll s=b[i]-(n-i)*z,d=2*i-n-1; //dk>=s
		if(d==0) {
			if(s>0) return false;
		}
		else if(d<0) {
			if(s<=0) r=min(r,(-s)/(-d));
			else return false;
		} else {
			if(s>=0) l=max(l,(s+d-1)/d);
		}
		if(l>r) return false;
	}
	return true;
}
ll sol() {
	ll l=0,r=(*max_element(b+1,b+n+1)+n-2)/(n-1)*2,p=r;
	while(l<=r) {
		ll mid=(l+r)>>1;
		if(chk(mid)) p=mid,r=mid-1;
		else l=mid+1;
	}
	return p;
}
ll fl[20][MAXN],fr[20][MAXN];
int bit(int x) { return 1<<x; }
void chkL(int l,int r,ll z) {
	int k=__lg(r-l+1);
	chkmax(fl[k][l],z),chkmax(fl[k][r-bit(k)+1],z);
}
void chkR(int l,int r,ll z) {
	int k=__lg(r-l+1);
	chkmin(fr[k][l],z),chkmin(fr[k][r-bit(k)+1],z);
}
int findL(int x,int d,int r) {
	int z=x/d*d+r;
	return max(1,z>x?z-d:z);
}
int findR(int x,int d,int r) {
	int z=x/d*d+r;
	return min(z<x?z+d:z,n);
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i],b[i]=a[i];
	ll ans=sol();
	if(ans<2) return cout<<ans<<"\n",void();
	ll z=ans-2,*L=fl[0],*R=fr[0];
	for(int x=1;x<=n;++x) for(int k=0;k<20;++k) fl[k][x]=0,fr[k][x]=z;
	for(int i=1;i<=n;++i) {
		ll s=a[i]-(n-i)*z,d=2*i-n-1; //dk>=s-|i-x|
		if(d==0) {
			if(s>0) for(int x=1;x<=n;++x) if(abs(i-x)<s) R[x]=-1;
		} else if(d<0) {
			d*=-1;
			for(int p=i,q,r=((i-s+1)%d+d)%d;p>=1;p=q-1) {
				q=findL(p,d,r);
				chkR(q,p,i-p<s?-1:(i-p-s)/d);
			}
			for(int p=i,q,r=((i+s-1)%d+d)%d;p<=n;p=q+1) {
				q=findR(p,d,r);
				chkR(p,q,p-i<s?-1:(p-i-s)/d);
			}
		} else {
			for(int p=i,q,r=(d-(s-i+d-1)%d)%d;p>=1;p=q-1) {
				q=findL(p,d,r);
				if(i-p<=s) chkL(q,p,(s-i+p+d-1)/d);
			}
			for(int p=i,q,r=((s+i+d-1)%d+d)%d;p<=n;p=q+1) {
				q=findR(p,d,r);
				if(p-i<=s) chkL(p,q,(s-p+i+d-1)/d);
			}
		}
	}
	for(int k=19;k;--k) for(int i=1;i+bit(k)-1<=n;++i) {
		chkmax(fl[k-1][i],fl[k][i]),chkmax(fl[k-1][i+bit(k-1)],fl[k][i]);
		chkmin(fr[k-1][i],fr[k][i]),chkmin(fr[k-1][i+bit(k-1)],fr[k][i]);
	}
	for(int x=1;x<=n;++x) if(L[x]<=R[x]) return cout<<ans-1<<"\n",void();
	cout<<ans<<"\n";
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

实际上是简单题，

先调整最优结构。如果存在两个打击点 $1 < i \le j < n$，则 $(i,j) \to (i-1,j+1)$ 更优。所以宣称：最优解中，至多只有一个打击点在 $2$ 到 $n-1$ 中。

先考虑打击点只能在 $1$ 和 $n$ 的情形。显然可以二分答案，然后解不等式，判断交集是否为空。

如果有一个打击点在 $2$ 到 $n-1$ 中，最多使得答案减少 $1$（因为它可以被一头一尾的一个操作代替）。

问题变为：给定首尾操作次数的和 $s$，能否在中间加一次操作使得完成目标。设首位操作的次数是 $x$，每个位置只看首尾获得的贡献一定能写成 $ax+bs$ 的形式。其中 $a$ 差不多为 $-n$ 到 $n$ 中的一个等差数列。

而中间那次打击最多对这个位置产生 $O(n)$ 的贡献。所以每个位置实际上只有 $O(\dfrac{n}{|a|})$ 个本质不同的 $x$（当 $ax+bs \ge lim_i$ 的时候，没有限制；否则，只有 $O(\dfrac{n}{|a|})$ 个 $x$ 满足 $ax+bs \ge lim_i - n$，而且他们还是连续的）求和，得到 $O(n \ln n)$。

> 注意特判 $a=0$。此时中间打击的位置与 $x$ 无关，是一个全局的限制。

我们直接狂暴枚举 $x$，然后扫一遍看看对不对即可（即，对于每个 $x$ 他们有一些限制，限制个数和为 $O(n \ln n)$。而对于 $m$ 个限制，由于他们的补是连续区间，可以直接排序之后看并集是否是全集）。

复杂度 $O(n \log^2 n)$。

snowtrace 老师在题解中提到，这题各种上取整下取整非常麻烦。但是我们可以通过大概求出一个解微调的方式来处理，虽然常数大了点但是不用动脑子。

```cpp
#include<bits/stdc++.h>
#define int long long
#define Int __int128
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int T,n,a[MAXN];
Int _=1;
int check(int s) {
	Int xmn=0,xmx=s;
	ffor(i,1,n) {
		if(2*i==n+1) {
			if(_*(n-i)*s<a[i]) return 0;
			continue ;	
		}
		Int k=2*i-1-n,v=a[i]-_*(n-i)*s;
		if(k>0) {
			Int dvd=(v+k-1)/k;
			while(k*dvd<v) dvd++;
			while(k*(dvd-1)>=v) dvd--;
			xmn=max(xmn,dvd);
		}
		else {
			Int dvd=(-v)/(-k);
			while(k*dvd<v) dvd--;
			while(k*(dvd+1)>=v) dvd++;
			xmx=min(xmx,dvd);
		}
	}
	return xmn<=xmx;
}
int bfind(int l,int r) {
	int ans=-1;
	while(l<=r) {
		int mid=(l+r>>1);
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	int tc=0;
	while(T--) {
		cin>>n;
		ffor(i,1,n) cin>>a[i];
		int lst=bfind(0,2000000000000000000);
		if(lst>=2) {
			map<int,vector<pair<int,int>>> lim;
			int s=lst-2,flg=0,nmd=0,pl=1,pr=n;
			Int tl=0,tr=s;
			ffor(i,1,n) {
				Int k=2*i-1-n,v=a[i]-_*(n-i)*s;
				if(k==0) {
					if(v>n) {flg=1;break ;}
					else if(v>0) nmd=1,pl=max(pl,i-(int)v+1),pr=min(pr,i+(int)v-1);
					continue ;
				}
				if(k>0) {
					Int dvd=(v+k-1)/k;
					while(k*dvd<v) dvd++;
					while(k*(dvd-1)>=v) dvd--;
					dvd=min(dvd,_*s+1);
					while(1) {
						dvd--;
						if(dvd<0) break ;
						if(k*dvd<v-n) {tl=max(tl,dvd+1);break ;}
						int dt=v-k*dvd;
						lim[dvd].push_back({i-dt,i+dt}); 
					}
				}
				else {
					Int dvd=(-v)/(-k);
					while(k*dvd<v) dvd--;
					while(k*(dvd+1)>=v) dvd++;
					dvd=max(dvd,_*(-1));
					while(1) {
						dvd++;
						if(dvd>s) break ;
						if(k*dvd<v-n) {tr=min(tr,dvd-1);break ;}
						int dt=v-k*dvd;
						lim[dvd].push_back({i-dt,i+dt}); 
					}
				}
			}
			if(!flg&&!(nmd==1&&pl==1&&pr==n)) {
				int ok=0;
				ffor(id,tl,tr) {
					vector<pair<int,int>> seg;
					if(nmd) seg.push_back({pl,pr});
					if(lim.count(id)) for(auto p:lim[id]) seg.push_back({max(1ll,p.first+1),min(n,p.second-1)});
					seg.push_back({0,0}),seg.push_back({n+1,n+1});
					sort(seg.begin(),seg.end());
					int tmp=0,mx=seg[0].second;
					ffor(j,1,seg.size()-1) if(seg[j].first>mx+1) tmp=1; else mx=max(mx,seg[j].second);
					if(tmp) {ok=1;break ;}
				}
				if(ok) cout<<lst-1<<'\n';
				else cout<<lst<<'\n';
			}
			else cout<<lst<<'\n';
		}
		else cout<<lst<<'\n';
	}
	return 0;
}
```

---

