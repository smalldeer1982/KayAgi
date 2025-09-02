# Heaven Tour

## 题目描述

The story was not finished as PMP thought. God offered him one more chance to reincarnate and come back to life. But before he can come back, God told him that PMP should ask $ n $ great men including prominent programmers about their life experiences.

The men are standing on a straight line. They are numbered $ 1 $ through $ n $ from left to right. The coordinate of the $ i $ -th man is $ x_{i} $ $ (x_{i}&lt;x_{i+1},i&lt;n) $ . PMP should visit all these people one by one in arbitrary order. Each men should be visited exactly once. At the beginning of his tour, he starts at location of $ s $ -th man and asks him about his experiences.

Each time PMP wants to change his location, he should give a ticket to an angel and the angel carries him to his destination. Angels take PMP from one location, fly to his destination and put him down there. Nobody else is visited in this movement. Moving from $ i $ -th man to $ j $ -th man, takes $ |x_{i}-x_{j}| $ time. PMP can get back to life as soon as he visits all men.

There are two types of angels: Some angels are going to the right and they only accept right tickets. Others are going the left and they only accept left tickets. There are an unlimited number of angels of each type. PMP has $ l $ left tickets and $ n-1-l $ right tickets.

PMP wants to get back to life as soon as possible to be able to compete in this year's final instead of the final he missed last year. He wants to know the quickest way to visit all the men exactly once. He also needs to know the exact sequence moves he should make.

## 说明/提示

Let us remind here, a great contestant of all times, who left us about a year ago. May Renat Mullakhanov rest in peace.

## 样例 #1

### 输入

```
5 2 2
0 10 11 21 22
```

### 输出

```
33
1 3 5 4
```

## 样例 #2

### 输入

```
4 3 1
0 1 2 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7 3 2
0 100 200 201 301 303 305
```

### 输出

```
409
1 3 4 7 6 5
```

# 题解

## 作者：L_zaa_L (赞：10)

## 分析
对于一个以 $S$ 为开头 $T$ 为结尾的一条路径（假设 $S<T$，如果 $S>T$ 我们直接将它），我们发现两个相邻的点中间这段路至少会被经过 $1$ 遍，然后 $[1,S]$ 这段中每个至少被经过两次，$[T,n]$ 这段中也至少被经过两次。如果我们想要使得答案更优，这两段中的路恰好经过两次一定是最好的，我们一定有种方法可以使得这两段路恰好走两次。

所以我们只剩下 $[S+1,T-1]$，这段中路过一个路不可能只被经过偶数次，而大于三次的次数一定有办法使得它降到 $1$ 或 $3$ 次，而其他的经过次数不变，然后对于这种走过 $3$ 次的路径，肯定由于有 $[1,S],[T,n]$ 这两段没有走完的 $l$ 形成的，所以我们要想使经过三次的少，而且左右两边无论用多少个 $l(l>0)$，它都可以形成一种经过两次的路径。所以就可以在两侧多用一些 $l$ 使得经过三次的的少，这样最优。

然后这种三次的显然一个 $l$，可以只使得一段路经过三次，我们每次贪心的选最小的路也就是最优的了。

然后题目给的 $S$ 是固定的，对于 $S<T$ 的我们可以从大到小的直接做，首先从小到大的加入 $l-S+1$ 个经过三段的路，每次加入一个右边的经过两次的路，然后从大到小删掉经过三段的路，然后随便构造一下走的方案就可以了。

---

## 作者：drmr (赞：1)

**题意**：给定 $N$ 个点，每个点在数轴 $A_i$ 处，现在你从 $S$ 出发，每次向左走或向右走，访问之前没有访问过的节点。当 $N$ 个点全部访问后，你恰好向左走了 $L$ 次，求最短路径并构造。

**题解**：容易知道 $R = N - 1 - L$ 表示向右走的次数。由对称性假设 $S < T$，其中 $T$ 为结束位置。

将点 $i$ 与 $i + 1$ 的线段标号为 $i$，称 $1 \le i < S$ 的线段称为『左部的』，将 $S \le i < T$ 称为『中部的』，将 $T \le i < N$ 称为『右部的』。观察得到，设左部的边数为 $l$，则 $\forall i \in [1,l]$，存在一种构造方法，在左部移动时向左走 $i$ 次，且此时在左部的路程为左部的距离的两倍。我们还可以证明，这时走完左部点的最短走法。因为 $S < T$，因此 $L$ 减小时答案不降。由于贡献不变，尽量多的在左部点中向左走一定不劣。这对于右部点相同。

那么，我们枚举所有 $T \in (i, n]$，尝试计算贡献。$U = \max\{0, L - S + 1 - N + t\}$ 表示在中部点向左的步数。我们尽量减少在同一位置经过多次的贡献，因此，我们可以在某个 $X$ 位置进行 $X - 2$ 到 $X$ 到 $X - 1$ 到 $X + 1$ 这样的步骤解决一次向左，这会在原本的情况下增加两倍的线段 $X$ 长度。因此只需要维护最小的 $U$ 条边即可。

这样可以用优先队列做到 $O(n \log n)$，其中构造显然。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 10;
int n, s, L, R, a[N], d[N], pre[N], suf[N], tag, res, go[N];
pair<int, int> ans = make_pair(1e18, -1);
priority_queue<int> q;
stack<int> stk;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> L >> s; R = n - 1 - L;
	for(int i = 1; i <= n; i++) cin >> a[i];
	if(s != n && L > n - 2){cout << "-1\n"; return 0;}
	if(s != 1 && R > n - 2){cout << "-1\n"; return 0;}

	for(int i = 1; i < n; i++) d[i] = a[i + 1] - a[i];
	for(int i = 1; i < n; i++)
		pre[i] = pre[i - 1] + d[i];
	for(int i = n - 1; i; i--)
		suf[i] = suf[i + 1] + d[i];

	for(int t = s + 1; t <= n; t++){
		res = (pre[s - 1] + suf[t]) << 1;
		if(t != s + 1) q.push(-d[t - 1]);
		tag += d[t - 1];
		if(L - s + 1 - n + t > 0)
			tag -= 2 * q.top(), q.pop();
		ans = min(ans, make_pair(res + tag, t));
	}

	tag = res = 0;
	while(!q.empty()) q.pop();

	for(int t = s - 1; t; t--){
		res = (pre[t - 1] + suf[s]) << 1;
		if(t != s - 1) q.push(-d[t]);
		tag += d[t];
		if(R - t + 1 - n + s > 0)
			tag -= 2 * q.top(), q.pop();
		ans = min(ans, make_pair(res + tag, t));
	}

	cout << ans.first << "\n"; int t = ans.second, use;
	vector<pair<int, int> > p;
	if(t > s){
		use = L - s + 1 - n + t;
		int now = s;
		while(L > 1 && now > 1)
			cout << --now << " ", --L;
		--L; for(int i = 1; i < now; i++) cout << i << " ";
		for(int i = s + 1; i < t; i++)
			p.push_back(make_pair(d[i], i));
		sort(p.begin(), p.end());
		for(int i = 0; i < use; i++)
			go[p[i].second] = 1;
		for(int i = s + 1; i < t; i++){
			stk.push(i);
			if(!go[i]) while(!stk.empty())
				cout << stk.top() << " ", stk.pop();
			L -= go[i];
		}
		int tmp = t + 1 + L;
		for(int i = tmp; i <= n; i++) cout << i << " ";
		for(int i = tmp - 1; i >= t; i--) cout << i << " ";
		cout << "\n";
	}
	else{
		use = R - t + 1 - n + s;
		int now = s;
		while(R > 1 && now < n)
			cout << ++now << " ", --R;
		--R; for(int i = n; i > now; i--) cout << i << " ";
		for(int i = t; i < s - 1; i++)
			p.push_back(make_pair(d[i], i));
		sort(p.begin(), p.end());
		for(int i = 0; i < use; i++)
			go[p[i].second] = 1;
		for(int i = s - 1; i > t; i--){
			stk.push(i);
			if(!go[i - 1]) while(!stk.empty())
				cout << stk.top() << " ", stk.pop();
			R -= go[i - 1];
		}
		int tmp = t - 1 - R;
		for(int i = tmp; i >= 1; i--) cout << i << " ";
		for(int i = tmp + 1; i <= t; i++) cout << i << " ";
		cout << "\n";
	}
	return 0;
}
```

---

