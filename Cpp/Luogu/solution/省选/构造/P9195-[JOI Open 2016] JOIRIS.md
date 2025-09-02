# [JOI Open 2016] JOIRIS

## 题目背景

**译自 [JOI Open 2016](https://contests.ioi-jp.org/open-2016/index.html) T1 「JOIRIS」**

## 题目描述

JOIRIS 的游戏区域名叫「井」，是一个宽度为 $N$，高度足够大的矩形网格。位于左数第 $i$ 列，从下往上数第 $j$ 列的格子记作 $(i,j)$。游戏过程中，每个格子要不有一个方块，要不没有方块。

开始时，在第 $i$ 列有且仅有 $(i,1), (i,2),\cdots, (i, A_i)$ 有方块。

接下来，$10^4$ 个 $1 \times K$ 的骨牌一个个下落，玩家要依次放置骨牌。每次放置骨牌按照如下方式进行：

玩家先选择骨牌是横向放置还是纵向放置。  
- 若选择纵向，玩家还需再选择一个整数 $x$（$1 \le x \le N$）。一个骨牌会下落到第 $x$ 列最上方方块的上面一行。若第 $x$ 列没有方块，骨牌会下落到井底。  
- 若选择横向，玩家还需再选择一个整数 $x$（$1 \le x \le N-K+1$）。一个骨牌会下落到第 $x$ 列至第 $x+K-1$ 列最上方方块的上面一行。若第 $x$ 列至第 $x+K-1$ 列没有方块，骨牌会下落到井底。

每个骨牌停止下落后，系统将从井底往上逐行检查，如果有一行格子被方块填满，该行的所有方块都会消失，且上方的所有方块向下移动 $1$ 格。

此时检查井中是否有方块，如果井中没有方块，游戏结束，玩家胜利，否则玩家开始放置下一个骨牌。

保证开始时最底下一行没有被方块填满。请判断玩家能否胜利，如果可能，则输出一种方案。

## 说明/提示

### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/zi0vapef.png)


### 数据规模与约定

**本题采用捆绑测试**。

对于所有数据，$2\le N\le 50$，$1\le K\le N$，$0\le A_i \le 50$。

- Subtask 1（15 points）：$K=2$ 且 $N$ 为奇数。
- Subtask 2（15 points）：$K=2$ 且 $N$ 为偶数。
- Subtask 3（15 points）：$K$ 能够整除 $N$。
- Subtask 4（55 points）：没有额外限制。

## 样例 #1

### 输入

```
4 2
1
0
1
2```

### 输出

```
4
2 2
1 1
2 3
1 2```

## 样例 #2

### 输入

```
3 2
2
0
1```

### 输出

```
3
1 2
1 3
2 1```

## 样例 #3

### 输入

```
2 2
0
1```

### 输出

```
-1```

## 样例 #4

### 输入

```
5 3
1
0
1
0
1```

### 输出

```
9
1 4
1 5
2 1
2 1
2 2
1 1
1 2
2 3
2 3```

# 题解

## 作者：APJifengc (赞：13)

神秘构造题。

先把下标改成从 $0$ 开始。

首先看到格子上的连续 $k$ 的骨牌显然能想到将格子 $k$ 染色。而由于有删除一行的操作，按照普通的染色方法好像并不好看，所以我们按列染色。这样我们统计每个颜色上的格子的数量 $\bmod k$，记 $b_i = (\sum_{i \equiv j \pmod k} a_j) \bmod k$。那么我们发现，对于横着放的一个骨牌，会使得每个 $b_i$ 同时加 $1$；对于竖着放的一个骨牌，$b_i$ 不变；对于消除一行的操作，虽然 $b_i$ 变化量不完全相同，但是发现对于 $\lbrack 0, n \bmod k)$ 与 $\lbrack n \bmod k, n)$ 这两个区间里的 $b_i$ 的相对大小不会发生改变。所以我们可以得出一个有解必要条件：$b_0 = b_1 = \cdots = b_{(n \bmod k) - 1}$ 且 $b_{(n \bmod k)} = b_{(n \bmod k) + 1} = \cdots = b_{n - 1}$。

接下来我们构造一种方案来证明这是充分条件。

1. 首先我们通过添加若干竖着的骨牌，使得骨牌数量从左到右单调不降；

	![image](https://cdn.luogu.com.cn/upload/image_hosting/3m8pj0cc.png)


2. 然后我们通过横着平铺，从下到上依次填满每一行；

	![image](https://cdn.luogu.com.cn/upload/image_hosting/9dbhelay.png)


3. 容易发现，此时对于 $\lbrack k - 1, n)$ 列，高度完全相等。那么，我们通过不断的往 $[0, k - 2]$ 内插入竖着的骨牌，使得 $\lbrack k - 1, n)$ 全部被删除；

	![image](https://cdn.luogu.com.cn/upload/image_hosting/br1iw2fa.png)


4. 此时我们一定有 $b_{k - 1} = 0$。由我们的条件可知，$b_{(n \bmod k)} = b_{(n \bmod k)} = \cdots = b_{k - 1} = 0$，那么也就是说对于这些列的 $a_i$ 一定是 $k$ 的整数倍，那么我们可以直接插入若干个竖骨牌将这些骨牌删除；

	![image](https://cdn.luogu.com.cn/upload/image_hosting/vrsi3zye.png)


5. 此时一定仅有 $\lbrack 0, n \bmod k)$ 内有格子了。而由于 $b_0 = b_1 = \cdots = b_{(n \bmod k) - 1}$，那么我们可以先将左边补齐，然后在右面横着铺满，即可全部消除。

	![image](https://cdn.luogu.com.cn/upload/image_hosting/8y7hkxwx.png)



```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;
int n, k;
int a[MAXN];
int b[MAXN];
vector<pair<int, int>> ans;
void op(int x, int y) {
    ans.push_back({ x, y });
    if (x == 1) {
        a[y] += k;
    } else {
        for (int i = 0; i < k; i++) {
            a[y + i]++;
        }
    }
    int mn = INT_MAX;
    for (int i = 0; i < n; i++) {
        mn = min(mn, a[i]);
    }
    for (int i = 0; i < n; i++) {
        a[i] -= mn;
    }
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i % k] = (b[i % k] + a[i]) % k;
    }
    if (k == 1) {
        int mx = 0;
        for (int i = 0; i < n; i++) {
            mx = max(mx, a[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = a[i]; j < mx; j++) {
                ans.push_back({ 1, i });
            }
        }
        printf("%lu\n", ans.size());
        for (auto p : ans) {
            printf("%d %d\n", p.first, p.second + 1);
        }
        return 0;
    }
    for (int i = 0; i < k - 1; i++) if (i != (n % k) - 1) {
        if (b[i] != b[i + 1]) {
            printf("-1\n");
            return 0;
        }
    }
    for (int i = 1; i < n; i++) {
        while (a[i] < a[i - 1]) {
            op(1, i);
        }
    }
    for (int i = 1; i < n - 1; i++) {
        int delta = a[i + 1] - a[i];
        for (int j = i - k + 1; j >= 0; j -= k) {
            for (int t = 0; t < delta; t++) {
                op(2, j);
            }
        }
    }
    for (int l = 1; l <= k - 1; l++) {
        for (int i = 0; i < l; i++) {
            int delta = a[n - 1] - a[i];
            while (delta > 0) {
                delta -= k;
                op(1, i);
            }
        }
    }
    int mx = 0;
    for (int i = n % k; i < k; i++) {
        mx = max(mx, a[i]);
    }
    for (int i = 0; i < n; i++) {
        int delta = mx - a[i];
        while (delta > 0) {
            delta -= k;
            op(1, i);
        }
    }
    mx = 0;
    for (int i = 0; i < n % k; i++) {
        mx = max(mx, a[i]);
    }
    for (int i = 0; i < n % k; i++) {
        while (a[i] < mx) op(1, i);
    }
    for (int i = n % k; i < n; i += k) {
        for (int j = 0; j < mx; j++) {
            op(2, i);
        }
    }
    for (int i = 0; i < n; i++) {
        assert(a[i] == 0);
    }
    printf("%lu\n", ans.size());
    for (auto p : ans) {
        printf("%d %d\n", p.first, p.second + 1);
    }
    return 0;
}
```

---

## 作者：5ab_juruo (赞：4)

考虑模 $k$ 意义下的差分数组 $d_i=a_i-a_{i-1}$，则当且仅当在 $x$ 放横块时，会对 $d_x$ 和 $d_{x+k}$ 产生影响。除去包含开头和结尾的，其余模 $k$ 相同的 $i$ 对应 $d_i$ 的和应为 $0$，否则显然无解。下面证明这是充要的。

不妨设 $a_i$ 都在 $[0,k)$ 中，考虑把 $d_x$ 转移 $v$ 到 $d_{x+k}$（反之则为 $k-v$）。先在 $x$ 处放 $v$ 个横块，然后在 $[x,x+k)$ 以外的区域各放两个竖块。此时横块的高度小于 $2k$，而其余部分都不低于 $2k$，所以所有横块都能消掉。为了维持 $a_i$ 的值域，还需要在 $[x,x+k)$ 中每个位置放不超过两个竖块。

显然总共会进行不超过 $n$ 次转移，每次转移最多进行 $3n$ 次操作，一开始最多会进行 $\sum a_i$ 次调整，所以总操作数不超过 $3n^2+\sum a_i\le 10^4$。

代码里没有维护 $a_i$ 的值域，而是最后再一起调整，可以证明这不劣于实时调整。

```cpp
const int max_n = 50;

vector<pair<int, int>> ops;
int a[max_n];

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, k;
	
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	
	auto df = [&](int i) { return (i < n ? a[i] : 0) - (i > 0 ? a[i - 1] : 0); };
	
	auto op = [&](int i, int adv)
	{
		adv = (adv % k + k) % k;
		if (adv == 0)
			return;
		int ps = 0;
		for (int j = 0; j < k; j++)
			chmax(ps, a[i + j]);
		for (int j = 0; j < adv; j++)
			ops.emplace_back(2, i);
		for (int j = 0; j < n; j++) if (j < i || j >= i + k)
		{
			while (a[j] < ps + adv)
			{
				ops.emplace_back(1, j);
				a[j] += k;
			}
			a[j] -= adv;
		}
	};
	
	for (int i = (n / k - 1) * k; i >= 0; i -= k)
		op(i, df(i + k));
	for (int i = 1; i <= n - k; i++)
		op(i, -df(i));
	
	int mx = *max_element(a, a + n);
	for (int i = 0; i < n; i++)
	{
		if (mx % k != a[i] % k)
		{
			cout << "-1\n";
			return 0;
		}
		while (a[i] != mx)
		{
			ops.emplace_back(1, i);
			a[i] += k;
		}
	}
	
	cout << size(ops) << "\n";
	for (auto [x, y] : ops)
		cout << x << " " << y + 1 << "\n";
	
	return 0;
}
```

---

## 作者：TonviaSzt (赞：3)

**题目大意** 

tetr 只有 I 块，没有旋、没有 hold，消行无 attack。

要求你打出无伤 all clear。

---
---

给一份效率喜人的做法。

**思路分析**

构造题重在一个方向。

首先如果任意 $a_i$ 之间相差 $k$ 的倍数，解法是显然的，竖着插到同一高度即可。

所以需要考虑的情况只在模 $k$ 意义下进行。故以下 $=$ 均为模 $k$ 意义下同余。

考虑平放块，当一个平放块覆盖 $[i,i+k)$ 时，这时其余行竖着插直到高过这个块，消掉的该行可以看做 $[i,i+k)$ 每列升高一格。

可以发现这个操作是很强的，相当于区间加的操作。

我们对原序列从左向右扫描，每次向 $i$ 加平放块（注意落点在 $[i,i+k)$ 最高的位置）执行区间加操作直到 $a_i=a_{i-1}$。

扫描一遍之后序列 $[1,n-k+1]$ 都相等，对于 $(n-k+1,n]$ 部分倒序再处理一遍即可。

操作上界一眼以为是 $n\cdot k\cdot (n-k)$ 的，实际上因为落点在 $[i,i+k)$ 的最高点，根本跑不满。

**Code**

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dec(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
int n,k,a[55];
vector<pair<int,int> > ans;
void Op(int x,int y){ans.push_back({x,y});}
void upd(int l,int r,int x){rep(i,l,r){while (a[i]<=x) Op(1,i),a[i]+=k;a[i]--;}}  //make a[l,r]>x
int main(){
    scanf("%d%d",&n,&k);
    rep(i,0,n-1) scanf("%d",a+i);
    rep(i,1,n-k){
        int mx=*max_element(a+i,a+i+k);
        while (a[i]%k!=a[i-1]%k) upd(0,i-1,mx),upd(i+k,n-1,mx),Op(2,i);
    }
    dec(i,n-k-1,0){
        int mx=*max_element(a+i,a+i+k);
        while (a[i+k]%k!=a[i+k-1]%k) upd(0,i-1,mx),upd(i+k,n-1,mx),Op(2,i);
    }
    rep(i,1,n-1) if(a[i]%k!=a[i-1]%k) return puts("-1"),0;
    rep(i,0,n-1) upd(i,i,*max_element(a,a+n));
    printf("%d\n",int(ans.size()));
    for(pair<int,int> v:ans) printf("%d %d\n",v.first,v.second+1);
    return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

其实是简单题……为什么有人会觉得他很困难。

我们思考一下不同加块方式对 $a_i \bmod k$ 的影响。

如果所有 $i$ 的 $a_i \bmod k$ 都相等，那么显然可以稍微操作几次使得所有列等高，这样就能消干净了。所以我们的目标就是 $a_i \bmod k$ 全相等。

如果竖着加一列，显然 $a_i \bmod k$ 不变。如果横着加一行，我们可以先不管是否产生空格，给这 $k$ 列的 $a$ 增加 $1$。

那么枚举最后 $a_i \bmod k$ 是多少，看能否存在一组区间加 $1$ 的操作使最后 $\bmod k$ 相等。（这部分其实可以用一些数论手段规避枚举，但是看起来没必要）

如何让一些列的 $a_i$ 相对加 $1$（如，让其他列减一）这个好办，在这一列上加一行，将其他列补齐至至少不低于这一行，就可以消除了。

这样操作次数是 $O(nk)$ 的，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50+10;
int n,k,a[MAXN],b[MAXN],pre[MAXN],bs=-1;
int check(int g) {
	ffor(i,1,n) b[i]=((g-a[i])%k+k)%k;
	memset(pre,0,sizeof(pre));
	ffor(i,1,n-k+1) {
		pre[i]+=pre[i-1];
		b[i]=((b[i]-pre[i])%k+k)%k;
		pre[i+1]+=b[i],pre[i+k]-=b[i];
	}
	ffor(i,n-k+2,n) {
		pre[i]+=pre[i-1];
		if((b[i]-pre[i])%k!=0) return 0;	
	}
	return 1;
}
vector<pair<int,int>> ans;
void clear(void) {
	int mn=*min_element(a+1,a+n+1);
	ffor(i,1,n) a[i]-=mn;
	if(*max_element(a+1,a+n+1)>=k) {
		int mx=*max_element(a+1,a+n+1);	
		ffor(i,1,n) while(mx-a[i]>=k) a[i]+=k,ans.push_back({1,i});
	}
	mn=*min_element(a+1,a+n+1);
	ffor(i,1,n) a[i]-=mn;
	return ;
}
int main() {
//	freopen("tetris.in","r",stdin);
//	freopen("tetris.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) cin>>a[i];
	ffor(i,0,k-1) if(check(i)) {bs=i;break ;}
	if(bs==-1) return cout<<-1,0;
	int flg=0;
	ffor(i,1,n) b[i]=((bs-a[i])%k+k)%k;
	ffor(i,1,n-k+1) {
		int add=(b[i]%k+k)%k,mx=0;
		if(add) {
			ffor(j,i,i+k-1) mx=max(mx,a[j]);
			mx+=add;
			ffor(j,1,add) ans.push_back({2,i});
			ffor(j,1,n) if(!(i<=j&&j<=i+k-1)) {
				while(a[j]<mx) ans.push_back({1,j}),a[j]+=k;
				a[j]-=add;
			}
			ffor(j,i,i+k-1) b[j]=(b[j]-add)%k;
			flg=1,clear();
		}
	}
	if(!flg) ans.push_back({1,1}),a[1]+=k;
	int mx=*max_element(a+1,a+n+1);
	ffor(i,1,n) while(a[i]<mx) a[i]+=k,ans.push_back({1,i});
	cout<<ans.size()<<'\n';
	for(auto pr:ans) cout<<pr.first<<' '<<pr.second<<'\n';
	return 0;
}
```

---

## 作者：Eznibuil (赞：1)

采用最暴力的写法即可通过。虽然看似次数 $O(n^3)$，但是实测绝大多数情况次数没有超过 3000。

考虑贪心地从前往后调整，依次检查相邻的 $a_i$ 和 $a_{i+1}$ 模 $K$ 的值，如果不相等则需要放置横块。暴力使需要放置的横块区间外面的高度高于横块区间里的高度，这样一旦横块放入就会消行，所以不用维护任何的浮空。

依次对于 $1\le i\le n-k$ 做上述操作调整。然后你会发现过不了。这是因为，在 $n\bmod k\ne0$ 的情况下，对于 $i\bmod k=0$ 的情况需要从后往前贪心，读者自证不难。于是反过来单独对 $i\bmod k=0$ 做一遍调整即可。

最后因为所有的 $a_i\bmod k$ 的值都相同了，所以调整到同一高度，然后判一下无解就行了。
```cpp
#include<algorithm>
#include<iostream>
int a[51],ans[10001][2];
int main()
{
	std::cin.tie(0)->sync_with_stdio(0);
	int n,k;
	std::cin>>n>>k;
	for(int i=0;i<n;i++)
		std::cin>>a[i];
	int la=0;
	for(int i=0;i<n-k;i++)
		while(a[i]%k!=a[i+1]%k)
		{
			int x=0;
			for(int j=i+1;j<=i+k;j++)
				x=std::max(x,a[j]);
			for(int j=0;j<=i;j++)
				while(a[j]<=x)
					a[j]+=k,ans[la][0]=1,ans[la++][1]=j+1;
			for(int j=i+k+1;j<n;j++)
				while(a[j]<=x)
					a[j]+=k,ans[la][0]=1,ans[la++][1]=j+1;
			for(int j=0;j<=i;j++)
				a[j]--;
			for(int j=i+k+1;j<n;j++)
				a[j]--;
			ans[la][0]=2,ans[la++][1]=i+2;
		}
	for(int i=(n-1)/k*k;i;i-=k)
		while(a[i-1]%k!=a[i]%k)
		{
			int x=0;
			for(int j=i-k;j<i;j++)
				x=std::max(x,a[j]);
			for(int j=0;j<i-k;j++)
				while(a[j]<=x)
					a[j]+=k,ans[la][0]=1,ans[la++][1]=j+1;
			for(int j=i;j<n;j++)
				while(a[j]<=x)
					a[j]+=k,ans[la][0]=1,ans[la++][1]=j+1;
			for(int j=0;j<i-k;j++)
				a[j]--;
			for(int j=i;j<n;j++)
				a[j]--;
			ans[la][0]=2,ans[la++][1]=i-k+1;
		}
	int x=0;
	for(int i=0;i<n;i++)
		x=std::max(x,a[i]);
	for(int i=0;i<n;i++)
		while(a[i]<x)
			a[i]+=k,ans[la][0]=1,ans[la++][1]=i+1;
	for(int i=1;i<n;i++)
		if(a[i]!=a[0])
			return std::cout<<"-1",0;
	std::cout<<la;
	for(int i=0;i<la;i++)
		std::cout<<'\n'<<ans[i][0]<<' '<<ans[i][1];
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

简单题。

整个问题看上去不好下手，于是考虑先从一些角度看问题以寻找有解的充分或者是必要条件。

由于可以对被填满的层做消除，尝试将所有列调整到一个高度相同且没有空出来的夹层的状态，不妨记 $a_i$ 表示第 $i$ 列骨牌数量，我们可以做的操作有区间 $a_i$ 加 $1$，单点 $a_i$ 加 $k$ 以及某些情况下可以使得所有 $a_i$ 减去 $1$。

不妨记 $d_i$ 表示 $a_i - a_{i-1}$，根据上文，有解的必要条件是 $z \not = 1$ 且 $z \not = (n+1) \bmod k$ 时有 $\sum_{z + i \times k} d_z$ 是 $k$ 的倍数。

下面我们来思考能否让这个条件是充分的，也就是满足条件即可构造出解。

首先我们将局面调整到一个简单的形式，也就是所有 $a_i < k$ 且不存在空出来的夹层，这个是简单的，给所有低于原先最高列的列不断加 $k$ 即可。

然后考虑怎么进行区间加 $1$ 操作后不要有空出来的夹层，你发现你只需要在区间加 $1$ 后给区间外所有低于这个区间的列不断加 $k$，就可以让区间加可能形成的夹层被消除，然后你可以再次仿照前面的方法将局面调整回简单形式。

但是你发现操作次数是 $O(n^3)$ 的，你发现每次做上一段描述的操作时花费了那么多操作次数却只调整了一个位置上的一个值，于是你考虑一个不行就多个，将一个位置上多个需要调整的值通过多次区间加调整，调整后再统一处理使得局面变回简单形式，就直接做到了 $O(n^2)$ 次操作次数，常数不是特别大，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 114;
int a[maxn],n,k;
int d[maxn];
vector< pair<int,int> > opt;
void maintain(){
    int mx=0;
    for(int i=1;i<=n;i++) mx=max(mx,a[i]);
    for(int i=1;i<=n;i++){
        while(a[i]<mx){
            opt.push_back(make_pair(1,i));
            a[i]+=k;
        }
    }
    int mi=1e9;
    for(int i=1;i<=n;i++) mi=min(mi,a[i]);
    for(int i=1;i<=n;i++) a[i]-=mi;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i],d[i]=a[i]-a[i-1],d[i]=(d[i]+50*k)%k;
    //d[1] 和 d[n-k+1] 是没有限制的
    int v=0;
    for(int i=2;i<=k;i++){
        int sum=0;
        for(int j=i;j<=n;j+=k) sum=(sum+d[j])%k;
        if(i%k==(n+1)%k){
            v=sum;
            continue;
        }
        if(sum!=0){
            cout<<"-1\n";
            exit(0);
        }
    }
    maintain();
    v=(k-v)%k;
    for(int i=1;i<=v;i++){
        opt.push_back(make_pair(2,n-k+1));
        d[n-k+1]++;
        d[n-k+1]%=k;
        for(int j=n-k+1;j<=n;j++) a[j]++;
    }
    int h=0;
    for(int i=n-k+1;i<=n;i++) h=max(h,a[i]);
    for(int i=1;i<n-k+1;i++){
        while(a[i]<h){
            opt.push_back(make_pair(1,i));
            a[i]+=k;
        }
    }
    maintain();
    for(int i=n;i>k;i--){
        for(int j=1;j<=d[i];j++){
            opt.push_back(make_pair(2,i-k));
            d[i-k]++;
            d[i-k]%=k;
            for(int p=i-k;p<i;p++) a[p]++;
        }
        d[i]=0;
        int h=0;
        for(int p=i-k;p<i;p++) h=max(h,a[p]);
        for(int p=1;p<i-k;p++){
            while(a[p]<h){
                a[p]+=k;
                opt.push_back(make_pair(1,p));
            }
        }
        for(int p=i;p<=n;p++){
            while(a[p]<h){
                a[p]+=k;
                opt.push_back(make_pair(1,p));
            }
        }
        maintain();
    }
    cout<<opt.size()<<"\n";
    for(pair<int,int> now:opt) cout<<now.first<<" "<<now.second<<"\n";
    return 0;
}
```

---

