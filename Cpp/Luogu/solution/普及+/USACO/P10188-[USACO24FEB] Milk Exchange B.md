# [USACO24FEB] Milk Exchange B

## 题目描述

Farmer John 的 $N$（$1\le N\le 2\cdot 10^5$）头奶牛排成一圈，使得对于 $1,2,\ldots,N−1$ 中的每个 $i$，奶牛 $i$ 右边的奶牛是奶牛 $i+1$，而奶牛 $N$ 右边的奶牛是奶牛 $1$。第 $i$ 头奶牛有一个容量为整数 $a_i$（$1\le a_i\le 10^9$）升的桶。所有桶初始时都是满的。

每一分钟，奶牛都会根据一个字符串 $s_1s_2\ldots s_N$
传递牛奶，该字符串仅由字符 `L` 和 `R` 组成。当第 $i$ 头奶牛至少有 $1$ 升牛奶时，如果 $s_i=\texttt{L}$，她会将 $1$ 升牛奶传递给她左边的奶牛，如果 $s_i=\texttt R$ 则传递给右边的奶牛。所有交换同时发生（即，如果一头奶牛的桶是满的，送出一升牛奶，但也收到一升，则她的牛奶量保持不变）。如果此时一头奶牛的牛奶量超过 $a_i$，则多余的牛奶会损失。

FJ 想要知道：经过 $M$ 分钟（$1\le M\le 10^9$）后，所有奶牛总共还余下多少牛奶？ 

## 说明/提示

### 样例解释 1

奶牛 $2$ 和 $3$ 互相传递一升牛奶，因此她们的牛奶得以保留。当奶牛 $1$ 将牛奶传递给奶牛 $2$ 时，奶牛 $2$ 的桶会溢出，从而一分钟后损失了一升牛奶。 

### 样例解释 2

 每头奶牛都将一升牛奶传递给左边的奶牛，并从右边的奶牛那里获得一升牛奶，因此无论经过多长时间所有牛奶都会被保留下来。 
 
### 样例解释 3

初始时，共有 $51$ 升牛奶。$5$ 分钟后，奶牛 $3$，$6$ 和 $7$ 将分别损失 $5$，$3$ 和 $5$ 升牛奶。因此，总共还剩下 $38$ 升牛奶。

### 测试点性质

- 测试点 $4-8$：$N,M\le 1000$。
- 测试点 $9-16$：没有额外限制。

## 样例 #1

### 输入

```
3 1
RRL
1 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5 20
LLLLL
3 3 2 3 3```

### 输出

```
14```

## 样例 #3

### 输入

```
9 5
RRRLRRLLR
5 8 4 9 3 4 9 5 4```

### 输出

```
38```

# 题解

## 作者：yuyc (赞：8)

## 题意
有 $N$ 头奶牛围成一圈，第 $i$ 头奶牛有一个容量为 $a_i$ 的桶，初始时桶满，每一时刻，每头奶牛都会根据一个操作序列 $s$ 来将自己桶中的 $1$ 升牛奶倒给自己左边或右边的奶牛（如果桶里有牛奶的话），传递完之后，大于桶的容量那部分牛奶将会溢出，问 $M$ 时刻后，所有的桶里一共还剩多少牛奶。

## 解析
如果 $s_i$ 是 `R`，$s_{i+1}$ 是 `L`，那么我们就将这两个操作方向对应的两头奶牛称为两头 “溢牛”，或一个 “溢牛对”。 

为什么这样称呼呢？
注意到每次操作，溢牛对内部的总奶量不变，因为左边的溢牛总是能给右边的溢牛倒 $1$ 升牛奶，右边的溢牛也总是能给左边的溢牛倒 $1$ 升牛奶，相当于是每次互相交换 $1$ 升牛奶。

这就意味着，只要有牛奶被传递给溢牛对，这部分牛奶必定溢出，因为溢牛对内部奶量总是满的，故对于每一个溢牛对，只需求出可能被传递给它左右边的奶量，分别对 $m$ 取最小值即可求出每个溢牛对溢出的奶量。

其实就是求每个溢牛对左边连续的 `R` 所对应的奶牛的奶量和右边连续的 `L` 所对应的奶牛的奶量。

## 代码
尤其注意奶牛们围成一个圈。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll a[N],b[N];
int main(){
   	ios::sync_with_stdio(false);
   	cin.tie(0);
	ll n,m;
	ll ans = 0,sum = 0;
	cin>>n>>m;
	string s;
	cin>>s;
	s = s[n - 1] + s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum += a[i];	
	}
	for(int i=0;i<=n;i++){
		if(s[i] == 'R' && s[i + 1] == 'L'){
			ll l = 0,r = 0;
			int lpos = i - 1 <= 0 ? i - 1 + n : i - 1,rpos = i + 2 > n ? i + 2 - n : i + 2;
			while(s[lpos] == 'R'){
				l += a[lpos];
				lpos--;
				if(lpos <= 0) lpos += n;
			}
			while(s[rpos] == 'L'){
				r += a[rpos];
				rpos++;
				if(rpos > n) rpos -= n;
			}
//			cout<<l<<' '<<r<<'\n';
			ans += min(m,l) + min(m,r);
		}
	}
	cout<<sum - ans;
    return 0;
}


```

---

## 作者：WA_WonderfulAnswer (赞：6)

[题目在这里](https://www.luogu.com.cn/problem/P10188)

## 思考
只有奶牛被指向两个方向时，我们才会失去牛奶，因为它输出一个单位，但获得两个单位的牛奶。当我们有 $\texttt{RRR}\cdots\texttt{RL}\cdots\texttt{LLL}$
的子串时，中间有两头牛是缺失的。
***
当一头奶牛的牛奶不足时，如果她要想停止减少牛奶，需要使其停止一侧的供奶。由于两头亏损牛奶的奶牛会无限循环，牛奶供应永远不会在它们相遇的那一边停止，这就是缺奶的奶牛总是有满满一桶牛奶的原因。让奶源停止的唯一方法就是等待另一边结束。
***
非循环侧必须是供应牛奶的链（奶牛的连续序列面向相应的亏损牛奶的奶牛的方向）。在本链中，牛奶会被记录，因为所有牛奶总是朝一个方向流动。亏损奶牛损失的牛奶数量是链上 $a_i$ 的总和，不包括亏损奶牛。例如，对于相邻对中的靠左的亏损牛奶的牛(假设索引为 $i$），并且 $j$ 是最左边的奶牛，使得 $s_j,s_{j+1},s_{j+2}\dots=\texttt R$，那么可以损失的牛奶量为 $\sum_{k=1}^{i-1}a_k$。由于每分钟只丢失一个牛奶单位，因此总金额也以 $M$ 为上限。
***
我们可以计算非循环边的 $a_{i}$ 的和对于一对亏空的奶牛。如果 $S$ 是链和，母牛在 $M$ 分钟内使我们损失的牛奶量为 $\min(S,M)$。
***
这种方法的时间复杂度为 $O(N)$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
string s;
vector<long long> a(n);
vector<bool> bL(n), bR(n);
long long ans, total;



int main() {
	cin >> n >> m;
	cin >> s;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	for (int i = 0; i < n; i++) {
		if (s[i] == 'R' && s[(i + 1) % n] == 'L') {
			bL[i] = true;
			bR[(i + 1) % n] = true;
		}
	}
	ans = accumulate(a.begin(), a.end(), 0LL);
	for (int i = 0; i < n; i++) {
		total = 0;
		if (bL[i]) {
			int j = (i - 1 + n) % n;
			while (s[j] == 'R') {
				total += a[j--];
				j = (j < 0 ? j + n : j);
			}
		}
		if (bR[i]) {
			int j = (i + 1) % n;
			while (s[j] == 'L') {
				total += a[j++];
				j = (j >= n ? j - n : j);
			}
		}
		ans -= min(total, (long long)m);
	}
	cout << ans;
	return 0;
}
```
~~求赞 & 求过审~~

---

## 作者：_O_v_O_ (赞：6)

当有 $s_i$ 满足 $s_i=\texttt{R},s_{i+1}=\texttt{L}$ 时，很明显它们之间永远是满的。  
那么假设有 $x,y$ 满足 $s_{x}=s_{x+1}=s_{x+2}=\cdots=s_{i-1}=\texttt{R},s_{i+2}=s_{i+3}=s_{i+4}=\cdots=s_{y}=\texttt{L}$，很明显那么 $[x,i),(i+1,y]$ 之间的牛奶都会被浪费。  
而浪费的牛奶数量为 $\min(\sum\limits_{j=x}^{i-1}a_i,m)+\min(\sum\limits_{j=i+2}^ya_i,m)$。

所以根据上述思路模拟即可。

---

## 作者：timmark (赞：3)

# P10188 题解

神奇妙妙题？

Fly, my cow。

## 思路

考虑牛的传递方向。

如果所有牛的传递方向一致，那么显然的，牛奶总量不变。

接下来的重点，就是存在不同的情况。

考虑对于两只相邻且向对方传递牛奶的牛（？）。

![](https://img.picgo.net/2025/05/31/swap28150c866526b7e9.png)

我们会发现在一次传递后相当于什么都没干！

那么考虑一条同一方向的链（首位**不**相连）

![](https://img.picgo.net/2025/06/17/line-newdb1dae30cc1e1b68.png)

我们发现，第一头牛会给出一桶牛奶，但无法收到任何牛奶，因此它的牛奶数量会 $-1$。中间的牛，会收到一桶牛奶，同时给出一桶牛奶，因此其牛奶数量不变。最后一头牛，不会给出牛奶，同时会收到一桶牛奶，但因为它的桶是满的，所以它的牛奶数量也不变。

所以对于这样的一条链，进行一次传递等同于倒掉第一头牛 $1$ 体积的牛奶。~~大萧条。~~

但是原题是一个环，而且存在不同的传递方向，因此这个链必定会遇到一个方向不一样的牛。如图。

![](https://img.picgo.net/2025/06/18/line-endf62f396edfa872d3.png)

同理，我们发现最左边的牛失去牛奶，中间的牛牛奶不变，而最右边的二位，可以发现也是不变的。因此对于这样的一条“链”，进行一次传递还是等同于倒掉第一头牛 $1$ 体积的牛奶。

而当第一头牛的牛奶倒光了，会发生什么逝呢。

![](https://img.picgo.net/2025/06/18/-new9c383ed9d413a75f.png)

此时第一头牛后面的牛就无法收到牛奶，并会开始接替它失去牛奶，而第一头牛就没有意义了，我们可以直接把它解放了。

![](https://img.picgo.net/2025/06/18/0132a710a29e82f22798790028206dfad9ea6bc13e035bf1c72b1b28.jpg)

而后中间的牛的牛奶也会被逐渐耗尽，直到时间到达 $M$。

因此，所谓传递，就是链底的牛像弹药包一样，一个接一个被打空的过程。

但是注意到时间和牛奶数量巨大，一点一点倒显然不现实。考虑采用类似于拓扑排序的方式找到链的开始，然后往上爬，并对链上的牛计算答案。最后输出即可。

可能会有人问，出现下图中的情况会怎么样（反正我写的时候想到了这个问题，可能是我太菜了）

![](https://img.picgo.net/2025/06/18/dottle125030e132aca4f3.png)

但实际上并不需要担心，手模可以发现这和两条分开的链是本质相同的。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int maxn=2e6+5;
int n,m,a[maxn],b[maxn],nxt[maxn],sum;
char s[maxn];
bool flag;
queue <int> q;
int id(int x){return (!x ? n : (x-1)%n+1);}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> s+1 ;
	for(int i=1;i<=n;i++) cin >> a[i] ,sum+=a[i];
	for(int i=1;i<=n;i++) b[i]=(s[i]=='R' ? 1 : -1);//为了方便实现，将方向转化为偏移量
	b[0]=b[n],b[n+1]=b[1];//对于环的处理
	for(int i=1;i<=n;i++) if(b[i]!=b[i-1]) flag=1;
	if(!flag){
		cout << sum ;
		return 0;
	}for(int i=1;i<=n;i++){
		if(b[i+b[i]]!=b[i]) continue;
		if(b[i-b[i]]!=b[i]) q.push(i);
		else nxt[id(i-b[i])]=i;
	}while(!q.empty()){
		int x=q.front(),tmp=m;
		q.pop();
		while(x){//结算以 x 为开头的链
			if(tmp>=a[x]) tmp-=a[x],sum-=a[x];//如果时间足够消耗掉这头牛
			else sum-=tmp,tmp=0;//时间到了
			x=nxt[x];
			if(!tmp) break;
		}
	}cout << sum ;
	return 0;
}
```

给个赞吧。

---

## 作者：zcq_qwq (赞：2)

## 说在前面

这题不是很难，对代码能力和思维能力的要求有点高。这里分享一种简单粗暴的做法。就是代码有点长（反正我代码挺长）。

## 题目分析

容易发现，如果相邻的两头奶牛形成了 $\texttt{RL}$ 的形式，那么这两头奶牛的奶量永远不会减少。如果有其他奶牛把牛奶传进来，那么奶量一定会减少。我们把样例三中的传递路径画出来，就是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/8pqx2jar.png)

不难发现，用绿框框起来的奶牛奶量会减少。当绿框里的奶牛的牛奶消耗完后，会接着消耗它下面的一个结点的奶牛的牛奶，以此类推，直到这一条路径消耗完，下面的环不会被消耗。

具体点说，就是 $\texttt{LL...L}$ 最左边的节点和 $\texttt{RR...R}$ 最右边的结点的奶量会被消耗。

所以，思路来了：

1. 以 $\texttt{RL}$ 作为块与块的分隔符，对序列进行分块。
2. 把每个小块里面再分成 $\texttt{RR...R}$ 和 $\texttt{LL...L}$ 的小块，以它作为最终的块。
3. 如果可以的话，首尾相连。
4. 计算答案。

那答案怎么计算呢？

对于每个块，优先消耗它最左边或最右边的奶牛的牛奶，如果不够，就消耗下一头奶牛，直到这一块消耗完或时间结束。把每一个块消耗的总牛奶量加起来就是答案。

## 注意事项

1. 这是一个环！！！
2. 处理每个块时优先处理第一块（因为第一块最特殊，他是首尾相连的块）。
3. 如果整体是一个大环，也不会消耗牛奶。

## 完整代码（真的有点长，165行）

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 200000 + 5;

int a[N], belong[N], st[N], ed[N];

int n, m, tot;

char x[N];

signed main() {
	cin >> n >> m;
	cin >> (x + 1);
	memset(st, 0x3f, sizeof st);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ans += a[i];
	}
	int tmp = 0;
	if (x[1] == 'L' && x[n] == 'R') { // 因为是个环，判一下首尾是否能组成不会消耗牛奶的结构。
		tot++;
		tmp++;
	}
	int sta = tmp + 1, en = n - tmp, fr = 0x3f3f3f3f3f3f3f3f;
	for (int i = sta; i <= en; i++) {
		if (x[i] == 'R' && x[i + 1] == 'L') {
			tot++;
			i++;
			tmp++;
			continue;
		}
		if (x[i] != x[i - 1]) {
			++tot;
		}
		fr = min(fr, tot); // 记录第一个块
		belong[i] = tot; // 记录每一位所在的块的位置
	}
	if (n % 2 == 0 && tmp == n / 2) { // 如果全是不会消耗牛奶的结构
		cout << ans;
		return 0;
	}
	for (int i = 1; i <= n; i++) { // 记录块的起始与结束
		st[belong[i]] = min(st[belong[i]], i);
		ed[belong[i]] = max(ed[belong[i]], i);
	}
	if (tot == 1 && st[1] == 1 && ed[1] == n) { // 如果整体是一个大环
		cout << ans;
		return 0;
	}
	if (x[1] == x[n]) { // 首尾相连
		st[belong[1]] = st[belong[n]];
		for (int i = st[belong[n]]; i <= ed[belong[n]]; i++) {
			belong[i] = belong[1];
		}
		tot--;
	}
	if (x[st[fr]] == 'R') { // 处理第一块，因为是首尾相连，所以起始位置可能大于结束位置
		if (st[fr] > ed[fr]) {
			int t = m;
			bool flag = false;
			for (int i = st[fr]; i <= n; i++) { // 计算答案
				if (t > a[i]) {
					t -= a[i];
					ans -= a[i];
				} else {
					flag = true;
					ans -= t;
					break;
				}
			}
			if (!flag) {
				for (int i = 1; i <= ed[fr]; i++) {
					if (t > a[i]) {
						t -= a[i];
						ans -= a[i];
					} else {
						ans -= t;
						break;
					}
				}
			}
		} else {
			int t = m;
			for (int i = st[fr]; i <= ed[fr]; i++) {
				if (t > a[i]) {
					ans -= a[i];
					t -= a[i];
				} else {
					ans -= t;
					break;
				}
			}
		}
	} else {
		if (st[fr] > ed[fr]) {
			int t = m;
			bool flag = false;
			for (int i = ed[fr]; i >= 1; i--) {
				if (t > a[i]) {
					t -= a[i];
					ans -= a[i];
				} else {
					flag = true;
					ans -= t;
					break;
				}
			}
			if (!flag) {
				for (int i = n; i >= st[fr]; i--) {
					if (t > a[i]) {
						t -= a[i];
						ans -= a[i];
					} else {
						ans -= t;
						break;
					}
				}
			}
		} else {
			int t = m;
			for (int i = ed[fr]; i >= st[fr]; i--) {
				if (t > a[i]) {
					ans -= a[i];
					t -= a[i];
				} else {
					ans -= t;
					break;
				}
			}
		}
	}
	for (int i = fr + 1; i <= tot; i++) {
		if (st[i] == 0x3f3f3f3f3f3f3f3f || ed[i] == 0) continue; // 一定要注意这个地方，因为块的编号不是连续的，不加这句会 RE
		if (x[st[i]] == 'R') {
			int t = m;
			for (int j = st[i]; j <= ed[i]; j++) {
				if (t > a[j]) {
					ans -= a[j];
					t -= a[j];
				} else {
					ans -= t;
					break;
				}
			}
		} else {
			int t = m;
			for (int j = ed[i]; j >= st[i]; j--) {
				if (t > a[j]) {
					ans -= a[j];
					t -= a[j];
				} else {
					ans -= t;
					break;
				}
			}
		}
	}
	cout << ans;
	return 0;
}
```

**注：后来发现不用这么麻烦，只需要把块内的的都加起来，直接用和去减就行了。**

## 第二种代码（这下简单得多了）


```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 200000 + 5;

int a[N], belong[N], st[N], ed[N], sum[N];

int n, m, tot;

char x[N];

signed main() {
	cin >> n >> m;
	cin >> (x + 1);
	memset(st, 0x3f, sizeof st);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ans += a[i];
	}
	int tmp = 0;
	if (x[1] == 'L' && x[n] == 'R') { // 因为是个环，判一下首尾是否能组成不会消耗牛奶的结构。
		tot++;
		tmp++;
	}
	int sta = tmp + 1, en = n - tmp, fr = 0x3f3f3f3f3f3f3f3f;
	for (int i = sta; i <= en; i++) {
		if (x[i] == 'R' && x[i + 1] == 'L') {
			tot++;
			i++;
			tmp++;
			continue;
		}
		if (x[i] != x[i - 1]) {
			++tot;
		}
		fr = min(fr, tot); // 记录第一个块
		belong[i] = tot; // 记录每一位所在的块的位置
	}
	if (n % 2 == 0 && tmp == n / 2) { // 如果全是不会消耗牛奶的结构
		cout << ans;
		return 0;
	}
	for (int i = 1; i <= n; i++) { // 记录块的起始与结束
		st[belong[i]] = min(st[belong[i]], i);
		ed[belong[i]] = max(ed[belong[i]], i);
	}
	if (tot == 1 && st[1] == 1 && ed[1] == n) { // 如果整体是一个大环
		cout << ans;
		return 0;
	}
	if (x[1] == x[n]) { // 首尾相连
		st[belong[1]] = st[belong[n]];
		for (int i = st[belong[n]]; i <= ed[belong[n]]; i++) {
			belong[i] = belong[1];
		}
		tot--;
	}
	for (int i = 1; i <= n; i++) {
		sum[belong[i]] += a[i];
	}
	for (int i = 1; i <= tot; i++) {
		if (st[i] == 0x3f3f3f3f3f3f3f3f || ed[i] == 0) continue; // 一定要注意这个地方，因为块的编号不是连续的，不加这句会 RE
		ans -= min(sum[i], m);
	}
	cout << ans;
	return 0;
}
```

于是这篇简单粗暴又不失优雅的题解到此结束。

## 说在后面

果然，越粗暴的做法越复杂。（但是好理解，所以我选择粗暴的做法）

若题目或代码讲解有误，欢迎提出。

---

## 作者：rnf5114 (赞：2)

我们要知道最后剩多少牛奶，只需要统计出来有多少牛奶被浪费了即可，显然的，我们可以以奶牛之间的传递牛奶的关系建成一条有向边，将这头奶牛指向它传递牛奶的奶牛即可，互相传递牛奶的奶牛是不会产生浪费的，所以我们把这些边删掉即可，之后我们只要将剩下的所有链上除去终点的元素和和 $m$ 取个最小值，再用牛奶总数减去这些值，最后得到就是答案。

特别的，此方法无法处理建出来的图有环的情况，但我们发现只有 $n-1$ 条边，所以最多只会出现一个包括所有奶牛环，我们特判一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[200010],v[200010],lsum,rsum,sum,edu[200010];
string s;
struct node{
	int p,v;
};
queue<node>q;
void bfs(){
	while(!q.empty()){
		node tmp=q.front();
		q.pop();
		if(v[tmp.p]==0){
			sum-=min(tmp.v,m);
			continue;
		}
		q.push({v[tmp.p],tmp.v+a[tmp.p]});
		v[tmp.p]=0;
	}
}
signed main(){
	cin>>n>>m>>s;
	for(int i=0;i<n;i++){
		lsum+=(s[i]=='L');
		rsum+=(s[i]=='R');
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(lsum==n||rsum==n){
		cout<<sum;
		return 0;
	}
	for(int i=0;i<n;i++){
		if(s[i]=='L'){
			if(i==0){
				v[1]=n;
				edu[n]++;
				continue;
			}
			else
				v[i+1]=i;
			edu[i]++;
		}
		else{
			if(i==n-1){
				v[n]=1;
				edu[1]++;
				continue;
			}
			else
				v[i+1]=i+2;
			edu[i+2]++;
		}
	}
	if(v[1]==n&&v[n]==1){
		v[1]=v[n]=0;
		edu[1]--,edu[n]--;
	}
	for(int i=1;i<n;i++){
		if(v[i]==i+1&&v[i+1]==i){
			v[i]=v[i+1]=0;
			edu[i]--;
			edu[i+1]--;
		}
	}
	for(int i=1;i<=n;i++){
		if(!edu[i]){
			q.push({i,0});
		}
	}
	bfs();
	cout<<sum;
	return 0;
}
```


---

## 作者：qiutian120529 (赞：1)

# 洛谷 P10188 题解
## 题意
一共有 $N$ 头奶牛，第 $i$ 头的初始奶量为 $a_i$。再给定一个模式串 $S$，对于第 $i$ 位，如果 $S_i = L$，则表示每分钟向左传递 $1$ 升牛奶；如果 $S_i = R$，则表示每分钟向右传递 $1$ 升牛奶。求 $M$ 分钟后，奶牛还总共还剩下几升牛奶。
## 思路
对于每头奶牛，对被其传奶的牛建立一条有向边，同时记录入度。接着拓扑排序，每头入度为零的奶牛每分钟会损失 $1$ 升牛奶。如果该头奶牛的奶已全部传完，则被它传奶的奶牛的入度减一。环不会损失牛奶因为入度始终为一。实际上，构建的图是个基环树。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5 + 10;

int n, m;
vector<int> g[N];
int ind[N], a[N], ans, rec[N];
char ch;
queue<int> q;

signed main(){
  cin >> n >> m;
  for(int i = 1; i <= n; i++){
    cin >> ch;
    if(ch == 'L'){
      if(i == 1){
        g[i].push_back(n);
        ind[n]++;
      }
      else{
        g[i].push_back(i - 1);
        ind[i - 1]++;
      }
    }
    else if(ch == 'R'){
      if(i == n){
        g[i].push_back(1);
        ind[1]++;
      }
      else{
        g[i].push_back(i + 1);
        ind[i + 1]++;
      }
    }
  }
  for(int i = 1; i <= n; i++){
    cin >> a[i];
    ans += a[i];
  }
  for(int i = 1; i <= n; i++){
    if(ind[i] == 0){
      q.push(i);
    }
  }
  while(!q.empty()){
    int u = q.front();
    q.pop();
    if(a[u] < m - rec[u]){
      ans -= a[u];
      for(int i : g[u]){
        ind[i]--;
        rec[i] = max(rec[i], a[u] + rec[u]);
        if(!ind[i]){
          q.push(i);
        }
      }
    }else{
      ans -= m - rec[u];
    }
  }
  cout << ans;
  return 0;
}

```

---

## 作者：Walrus (赞：1)

## 题意

一共 $N$ 头奶牛，其围成一个圈。第 $i$ 头奶牛原始拥有 $a_i$ 升奶，$N$ 头奶牛**同时**进行 $M$ 次操作。

你会得到一个长度为 $N$ 的字符串，其编号为 $s_1$ 至 $s_N$。

- 若 $s_i=L$，则第 $i$ 头奶牛每次向其左边的奶牛传递 $1$ 升奶。
- 若 $s_i=R$，则第 $i$ 头奶牛每次向其右边的奶牛传递 $1$ 升奶。

注意：操作必须在当前奶牛手中还有奶的前提下发生。



## 做法

首先考虑暴力，$O(NM)$ 显然过不去，但可以尝试通过暴力获得信息。

![](https://cdn.luogu.com.cn/upload/image_hosting/3dn06p5y.png)

就像这样，我们写出一个暴力，通过输出每一时刻的 $a$ 数组来观察。

其变化分为两种（指的是样例，所有情况当然不止两种）。

- 数值一直未发生变化。
- 数值每次减少 $1$。

为什么会有这些变化？因为每头奶牛在每一时刻所增加的奶的数量不同，通过上述方法，我们可以通过一个 $cnt$ 数组记录最初每头奶牛在每一时刻所增加的奶的数量，当然其有可能是负数。由于每头牛在有奶的情况下会向左右传递，于是我们将 $cnt$ 数组初始化为 $-1$。

```cpp
memset(cnt, -1, sizeof cnt);
for(int i = 1; i <= n; ++i)
	cnt[s[i] == 'L' ? (i == 1 ? n : i - 1) : (i == n ? 1 : i + 1)]++;
```

当然，$cnt$ 数组的最小值也为 $-1$，如果 $cnt_i=-1$，那意味着什么？说明此牛**有可能**会在某一时刻其的奶全部流失，这样会导致其向其他牛传递的奶数也会变化，简单来说，会影响其 $cnt$ 的值。

所以我们考虑通过**递归**的方法处理 $cnt$，计算出每头奶牛会流失的奶的总数，用原来的总数减去流失的总数，即为答案。

有个小优化，一头牛并没有必要处理两次，假设其 $cnt$ 的值为 $1$，意味着有两头牛向其传递，则一定不会出现两牛都影响它的情况，这很容易证明，所以时间复杂度 $O(N)$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

char s[N];
int n, m, ans, res, a[N], b[N];
int cnt[N], vis[N];

void solve(int x, int lt) {
	vis[x] = 1;
	if(a[x] >= lt) {
		res += lt;
		return;
	}
	res += a[x]; 
	if(s[x] == 'L') {
		int t = x == 1 ? n : x - 1;
		--cnt[t];
		if(cnt[t] == -1)
			solve(t, lt - a[x]);
	}
	else {
		int t = x == n ? 1 : x + 1;
		--cnt[t];
		if(cnt[t] == -1)
			solve(t, lt - a[x]);
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);

	memset(cnt, -1, sizeof cnt);

	cin >> n >> m;
	cin >> (s + 1);
	for(int i = 1; i <= n; ++i)
		cin >> a[i], ans += a[i];
	
	for(int i = 1; i <= n; ++i)
		cnt[s[i] == 'L' ? (i == 1 ? n : i - 1) : (i == n ? 1 : i + 1)]++;
	
	for(int i = 1; i <= n; ++i)
		if(cnt[i] == -1 && !vis[i])
			solve(i, m);	
	

	cout << ans - res;
	return 0;
}
```

---

## 作者：xrz114514 (赞：0)

# P10188 题解
## [题目转送门](https://www.luogu.com.cn/problem/P10188)
## 思路
发现传来传去就像是一条边，所以可以将奶牛当节点，传给的操作当有向边，这样就变成了有向图上问题。

在图上，每个点的出度都为 1，总共有 $n$ 条边，这样的图就是**内向基环树**。接下来考虑一个点 $m$ 分钟后剩的牛奶。
- 如果一个点他在环上，则它传出去 1 点，别的在环上的又给它 1 点，始终不会变。
- 如果不在环上，那它如果没有连向它的边，或是没有连向它的奶牛能传给他，那他就会在之后慢慢传给下一个直到没了。
  - 所以可以定义 $dp_u$ 表示最早什么时候 $u$ 号奶牛没有了供给，根据定义，只有所有连向 $u$ 的点没牛奶时才会没有了供给。即 $dp_u = \max\limits \{dp_v + a_v\}$ 其中 $v$ 为连向 $u$ 的一个点。
  - $dp$ 数组的转移要按拓扑序进行，我们不妨直接在进行拓扑序时转移，~~顺便再求个环~~。

有了 $dp$ 数组，在 $m$ 分钟时剩多少牛奶就确定了，最后求和即可，**注意环上的点要直接加上 $a_i$**。

### 时空复杂度
时间 $O(n+m)$。
空间 $O(n)$。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 1;

int n, m, a[N], inv[N], vis[N];
ll sum, dp[N];
string s;
vector<int> g[N];
queue<int> q;

void Topo_sort(){
  for(int i = 1; i <= n; ++i){
    if(!inv[i]){
      q.push(i);
    }
  }
  while(!q.empty()){
    int u = q.front();
    vis[u] = 1;
    q.pop();
    for(int v : g[u]){
      dp[v] = max(dp[v], dp[u] + a[u]);
      inv[v]--;
      if(inv[v] == 0){
        q.push(v);
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> s;
  for(int i = 0; i < s.size(); ++i){
    int x;
    if(s[i] == 'L'){
      x = i == 0 ? n : i;
    }else if(s[i] == 'R'){
      x = i == s.size() - 1 ? 1 : i + 2;
    }
    g[i + 1].push_back(x);
    inv[x]++;
  }
  for(int i = 1; i <= n; ++i){
    cin >> a[i];
  }
  Topo_sort();
  for(int i = 1; i <= n; ++i){
    if(!vis[i]){
      sum += a[i];
    }else{
      sum += max(0ll, a[i] - max(0ll, m - dp[i]));
    }
  }
  cout << sum << '\n';
  return 0;
}
```

 _不开 long long 见祖宗_

---

## 作者：_Chronostatis_ (赞：0)

## 题意
有 $n$ 头奶牛围成一圈，每次他们会按照一个法则 $s$ 来传牛奶：对于 $1 \le i \le n$，如果 $s_i = $ `L`，那么第 $i$ 头奶牛会传给它左边的奶牛，反之如果是 `R`，就传给它右边的奶牛。每头奶牛有一个大小为 $a_i$ 的桶，一开始桶都是满的。每次传牛奶后，可能会有牛奶损失。求传 $m$ 次后还剩多少牛奶。

## 思路
首先研究性质。按照 $s$ 建图后，会发现这张图是[内向基环森林](https://oi-wiki.org/graph/concept/#%E7%89%B9%E6%AE%8A%E7%9A%84%E5%9B%BE)。即每个点出度为 $1$ 的图。以第三个样例为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/z9r4y0vd.png)

然后会发现，每个连通块内一定**有且仅有**一个环。因为一个连通块的大小和边数相等。

对于一个连通块，不在环上的点，一定会一直损失牛奶，且每分钟损失一个单位，直到这棵树的牛奶耗尽。

所以我们可以使用 dfs 找环，然后对于每个环上的点，求出以这个节点为根的子树和 $S_i$，那么过了 $\max S_i$ 分钟，牛奶就会形成循环，不会再有损失。因为环上的点的牛奶总是满的。

一开始将答案置为 $\sum a_i$，对于不超过 $m$ 的 $S_i$，答案减去 $S_i$，否则减去 $m$。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 10;

int n, p, a[MAXN], f[MAXN];
ll cnt[MAXN], vis[MAXN], m;
vector<int> g[MAXN], v, G[MAXN];
bool onring[MAXN];
string s;

void dfs(int u) {
  if (vis[u]) {
    if (vis[u] == 1) {
      bool f = 0;
      for (int k : v) {
        f |= k == u;
        onring[k] |= f;
      }
    }
    return;
  }
  vis[u] = 1; v.push_back(u);
  for (int v : g[u]) dfs(v);
  vis[u] = -1; v.pop_back();
}

void dfs2(int u) {
  if (u != p && onring[u]) return;
  cnt[p] += a[u];
  for (int v : G[u]) dfs2(v);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> s;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'L') {
      g[i + 1].push_back((i + n - 1) % n + 1);
      G[(i + n - 1) % n + 1].push_back(i + 1);
    } else {
      g[i + 1].push_back((i + 1) % n + 1);
      G[(i + 1) % n + 1].push_back(i + 1);
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ans += a[i];
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i);
  }
  for (p = 1; p <= n; p++) {
    if (onring[p]) {
      dfs2(p);
      cnt[p] -= a[p];
      ans -= min(cnt[p], m);
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：lbhlgzh (赞：0)

#### 前言

做这道题的时候想到了一种思路，翻遍题解区没有这种解法，遂产生了这篇题解。


---


#### 思路

一个显然的事实是：当一段时间内，没有任何一头奶牛的牛奶桶发生变化时（变化指由有牛奶到没有牛奶），每个时刻失去的牛奶总量是固定的，而每次变化至多改变左边或右边一头奶牛所获得的牛奶数，而且奶桶已经空了的奶牛不会再由没有牛奶变为有牛奶，于是，我们可以以每次最先发生变化的奶牛为跳板来跳跃时间，并统计答案。

具体的，我们用一个数组 $delta$ 表示现在时刻每只奶牛经过一次交换后桶中牛奶的变化量，一个变量 $nowtime$ 表示现在是什么时刻。为了快捷地取出下一个空的奶桶所在的奶牛位置，我们维护一个优先队列 $q$ 并在其中维护两个变量 $intime$ 和 $cap$，分别表示这只奶牛进入队列的时间和奶桶容量，则 $cap-nowtime+intime$ 是这只奶牛的奶桶剩余容量。当取出一只奶牛时，我们先检查倒空它的奶桶所需时间是否超过 $M$，若超过便直接统计并输出。否则，我们将 $nowtime$ 加上剩余容量，并更新 $dekta$ 数组，并将现在奶桶里的奶会随时间减少的奶牛加入队列。重复上述操作直至队列为空，输出答案即可。


---

#### 代码

注意奶牛是围成圈的，不然会错一个点

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m;
string s;
int delta[N],a[N];
bool use[N];
long long nowtime;
struct node{
	int cap,intime,pos;
	bool operator <(const node b)const{
		return cap-(nowtime-intime)>b.cap-(nowtime-b.intime);
	}
	node(int a,int b,int c){
		cap=a;
		intime=b;
		pos=c;
	}
};
priority_queue<node> q;
int main(){
	//freopen("P10188_12.in","r",stdin);
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	cin>>s;
	long long ans=0;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		ans+=a[i];
	}
	//printf("%lld\n",ans); 
	for(int i=0;i<s.size();i++){
		if(s[i]=='L'){
			if(i!=0) {
				delta[i]++;
				delta[i+1]--;
			}
			else {
				delta[n]++;
				delta[1]--;
			}
		}
		else{
			if(i!=n-1) {
				delta[i+2]++;
				delta[i+1]--;
			}
			else {
				delta[1]++;
				delta[n]--;
			}
		}
	}
	long long lose=0;
	for(int i=1;i<=n;i++){
		//printf("%d ",delta[i]);
		if(delta[i]<0) q.push(node(a[i],0,i));
		else lose+=delta[i];
	} 
	//int cnt=0;
	while(!q.empty()){
		//printf("%lld\n",nowtime);
		node t=q.top();
		q.pop();
		long long t1=t.cap,t2=t.intime,t3=t.pos;
		//printf("%d %d %d\n",t1,t2,t3);
		long long left=t1-(nowtime-t2);
		if(nowtime+left>=m){
			//printf("%d\n",nowtime);
			ans-=(m-nowtime)*lose;
			nowtime=m+1;
			break;
		}
		use[t3]=1;
		//cnt++;
		nowtime+=left;
		ans-=lose*left;
		if((t3==1&&s[t3-1]=='L'&&!use[n])||(s[t3-1]=='L'&&!use[t3-1])){
			if(t3==1){
				if(delta[n]<=0){
					delta[n]--;
					q.push(node(a[n],nowtime,n));
				}
				continue;
			}
			if(delta[t3-1]<=0){
				delta[t3-1]--;
				q.push(node(a[t3-1],nowtime,t3-1));
			}
			else lose-=1;
		}
		else if((t3==n&&!use[1])||(!use[t3+1])){
			if(t3==n){
				if(delta[1]<=0){
					delta[1]--;
					q.push(node(a[1],nowtime,1));
				}
				continue;
			}
			if(delta[t3+1]<=0){
				delta[t3+1]--;
				q.push(node(a[t3+1],nowtime,t3+1));
			}
			else lose-=1;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：MicroSun (赞：0)

考虑分点统计贡献。

发现如果存在相邻的两只奶牛，左边的奶牛传递方向为 `R` 且右边的奶牛传递方向为 `L`，则这两头奶牛在任意分钟后都不会对损失的总奶量做出任何贡献。但是，如果有人向这两头奶牛中的任意一只传递牛奶，都会造成损失。

于是很容易写出类似下面的代码：

```cpp
ll sum=0;//rep(i,1,n)：for(int i=1;i<=n;++i)
rep(i,1,n){
	cin>>b[i];
	sum+=b[i];
}
rep(i,1,n){
	if(w[i]=='R'){
		if(i==n) ++indeg[1];
		else ++indeg[i+1];
	}
	else{
		if(i==1) ++indeg[n];
		else ++indeg[i-1];
	}
}
ll cnt=0;
rep(i,1,n)
	if(indeg[i]>1){
		if(w[i]=='R'){
			int l=i==1?n:i-1;
			cnt+=min(b[l],m);
		}
		else{
			int r=i==n?1:i+1;
			cnt+=min(b[r],m);
		}
	}
cout<<sum-cnt;
```

但是这份代码忽视了一个问题：有可能一直在损失牛奶的这头牛也正在接受牛奶。

于是考虑建边，计算每头牛在无限分钟后会损失多少奶。因为要考虑在 $m$ 分钟内的损失，所以要和 $m$ 取最小值。

有点丑的考场代码：

```cpp
// Problem: Problem 2. Milk Exchange
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int maxn=2e5+10;

ll b[maxn];
char w[maxn];
int indeg[maxn];
struct edge{
	int nxt,to;
}a[maxn];
int head[maxn],cnt;
void add(int u,int v){
	++indeg[v];
	a[++cnt]={head[v],u};
	head[v]=cnt;
}
ll n,m;
bool vis[maxn];
ll sz[maxn];
void dfs(int u){
	if(vis[u]) return;
	vis[u]=1;
	int l=u==1?n:u-1;
	int r=u==n?1:u+1;
	if((w[u]=='L'&&w[l]=='R')||(w[u]=='R'&&w[r]=='L')){
		sz[u]=0;
		return;
	}
	sz[u]=b[u];
	for(int i=head[u];i;i=a[i].nxt){
		int t=a[i].to;
		dfs(t);
		if(!sz[t]) sz[u]=0;
		else if(sz[u]) sz[u]+=sz[t];
	}
}
void solve(){
	cin>>n>>m;
	rep(i,1,n) cin>>w[i];
	ll sum=0;
	rep(i,1,n){
		cin>>b[i];
		sum+=b[i];
	}
	rep(i,1,n){
		if(w[i]=='R'){
			if(i==n) add(n,1);
			else add(i,i+1);
		}
		else{
			if(i==1) add(1,n);
			else add(i,i-1);
		}
	}
	rep(i,1,n)
		if(!vis[i]) dfs(i);
	ll cnt=0;
	rep(i,1,n)
		if(indeg[i]>1){
			if(w[i]=='R'){
				int l=i==1?n:i-1;
				cnt+=min(sz[l],m);
			}
			else{
				int r=i==n?1:i+1;
				cnt+=min(sz[r],m);
			}
		}
	//rep(i,1,n) cerr<<sz[i]<<' ';
	cout<<sum-cnt;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	//cin>>t;
	while(t--) solve();
    return 0;
}
```

---

