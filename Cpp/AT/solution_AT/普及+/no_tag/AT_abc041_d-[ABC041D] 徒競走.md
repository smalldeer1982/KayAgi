# [ABC041D] 徒競走

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc041/tasks/abc041_d



## 样例 #1

### 输入

```
3 2
2 1
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5
1 2
2 3
3 5
1 4
4 5
```

### 输出

```
3
```

## 样例 #3

### 输入

```
16 1
1 2
```

### 输出

```
10461394944000
```

# 题解

## 作者：syzxzqy (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc041_d)  
状压 DP 的模板题。  
如果你不会状压 DP，请看这篇[博客](https://www.luogu.com.cn/blog/xcg--123/ti-xie-p1896-scoi2005-hu-fou-qin-fan)。  
我们对选取情况进行状态压缩，一个位置上为 1，那么表示这个位置已经选择;这个位置上为 0，那么表示这个位置没选择。  
$dp_{i,j}$ 表示选择了第 $i$ 个数，状压情况为 $j$ 的方案数。  
我们枚举当前选取第几个数 ($i$)、之前选取的情况（$pre$）和新选的位置（$j$），计算出现在选取的情况（$now=pre+2^j$）。  
如果当前情况满足每个 $x_j$ 出现在 $y_j$ 前面（时刻满足不出现有了 $y_j$ 但没有 $x_j$ 的情况），当前情况的方案数（$dp_{i,now}$）就会增加 $dp_{i-1,pre}$。  
时间复杂度：$O(n^2m2^n)$。  
由于过程中会有不符合的情况，直接跳过循环，所以时间还是充裕的。  
### 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,N,m,i,pre,now,j,f[20],x[400],y[400];
ll dp[20][65546];
bool check(int now){
	int i,t=0;
	for(i=1;i<=n;++i) f[i]=0;//清空 
	while(now) f[++t]=now&1,now>>=1;//求出每个位置是否选过 
	for(i=1;i<=m;++i)
		if(f[y[i]]&&!f[x[i]])//如果yi选了，但xi没选，这个方案就不成立 
			return 0;
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=1;i<=m;++i) cin>>x[i]>>y[i];
	dp[0][0]=1;N=1<<n;
	for(i=1;i<=n;++i)//枚举当前选取第几个数
		for(pre=0;pre<N;++pre){ //枚举之前选取的所有情况
			if(dp[i-1][pre]==0) continue;
			//dp[i-1][pre]=0时就表示之前选取的情况不可能实现，无需继续操作。 
			for(j=0;j<n;++j){//枚举当前选取的数
				now=pre|(1<<j);
				if(now!=pre&&check(now))
				//如果j没选过，并满足条件，方案数增加
					dp[i][now]+=dp[i-1][pre];
			}
		}
	cout<<dp[n][N-1];
}
```


---

## 作者：StayAlone (赞：3)

[例题](https://www.luogu.com.cn/problem/AT_abc041_d)

此题可以直接转化为对 $x_i\to y_i$ 连边后，拓扑排序的方案数。此问题无多项式复杂度解，可以通过状压做到 $\mathcal O(n\cdot2^n)$。

设 $f_s$ 表示选择点集为 $s$，满足要求的方案数。转移时通过类似拓扑的顺序转移。

若当前的点集为 $s$，考虑新增一个点 $x$。定义增加后的点集为 $s'$。若这个点的所有儿子都在点集 $s$ 中，且这个点不在点集 $s$ 中，则可以钦定 $x$ 放在最前面，那么 $f_{s'}$ 中就要累加一个 $f_s$。因此，找到所有满足条件的 $x$，就可以获得答案。换句话说，就是对于一个点集，累加当某个点在最前面时的方案数。

写了两种写法，一种顺推，一种记搜。都还挺好理解的。

写法一：
```cpp
int n, m, son[MAXN]; ll f[MAXN];

int main() {
	read(n, m);
	rep1(i, 1, m) {
		int x, y; read(x, y);
		son[x] |= 1 << y - 1;
	} f[0] = 1;
	rep1(s, 0, (1 << n) - 1) rep1(x, 1, n) {
		if ((son[x] & s) == son[x] && !(s >> x - 1 & 1)) f[s | (1 << x - 1)] += f[s];
	} printf("%lld", f[(1 << n) - 1]);
	rout;
}
```

写法二：
```cpp
int n, m, son[MAXN]; ll f[MAXN];

il ll dfs(int s) {
	if (~f[s]) return f[s];
	f[s] = 0;
	rep1(i, 1, n) {
		int s2 = s ^ (1 << i - 1);
		if (s >> (i - 1) & 1 && (son[i] & s2) == son[i]) f[s] += dfs(s2);
	} return f[s];
}

int main() {
	read(n, m);
	rep1(i, 1, m) {
		int x, y; read(x, y);
		son[x] |= 1 << y - 1;
	} f[0] = 1; fill(f + 1, f + (1 << n), -1);
	printf("%lld", dfs((1 << n) - 1));
	rout;
}

```

---

## 作者：zzx0102 (赞：1)

状压 DP 好题。

首先，考虑 $dp_i$ 为目前已经遍历过的点集为 $i$ 的方案数。

那么假如现在要新增加一个节点 $j$，必须满足：

1. $j$ 不在点集中

1. $j$ 的所有儿子都在点集中

此时可以加入 $j$ 节点。

这里用逆推，初始化时 $dp_{0}=1$，即没有点权为一种方案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 17; int son[N], n, dp[1 << N], m;
signed main() {
	cin >> n >> m;
	while(m--) {
		int x, y; cin >> x >> y; x--, y--;
		son[x] |= (1 << y);
	}
	dp[0] = 1;
	for(int i = 0; i < (1 << n); i++) {
		for(int j = 0; j < n; j++) {
			if(i & (1 << j)) continue;
			if((i & son[j]) != son[j]) continue;
			dp[i | (1 << j)] += dp[i];
		}
	}
	cout << dp[(1 << n) - 1];
	return 0;
}
```

---

## 作者：Walter_Fang (赞：0)

翻译已经非常言简意赅了，题目大意就不说了。

### 思路/解析

状压 dp。

我们用 $f_i$ 保存已经遍历过的点集为 $i$ 的方案数量，那么当要加入一个新节点 $j$ 时，节点 $j$ 的所有子节点必须全部在点集 $i$ 中。

需要注意的是，最初我们将没有点权看作第一种方案，即 $f_0=1$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+10;
ll n,m,x,y,i,j,a[N],f[N]={1};
int main(){
	cin>>n>>m;
	for(i=1;i<=m;i++)cin>>x>>y,a[x]|=1<<y-1;
	for(i=0;i<(1<<n);i++)
		for(j=1;j<=n;j++)
			if((a[j]&i)==a[j]&&!(i>>j-1&1))
				f[i|(1<<j-1)]+=f[i];
	cout<<f[(1<<n)-1];
}
```

---

