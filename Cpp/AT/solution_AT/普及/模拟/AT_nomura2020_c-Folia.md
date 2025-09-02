# Folia

## 题目描述

[问题网址](https://atcoder.jp/contests/nomura2020/tasks/nomura2020_c)

给定一个长度为 $N+1$ 的非负整数序列 $A_0,A_1,A_2,\cdots,A_N$。问是否存在一棵深度为 $N$ 的二叉树，对于每一个 $d=0,1,2,\cdots,N$，使得在深度 $d$ 处正好有 $A_d$ 个叶子结点。如果存在，则输出此类二叉树的最大顶点数量，如果不存在，则输出 $-1$。

## 说明/提示

### 注释

- 二叉树是一棵有根树，每个结点最多有两个子结点。
- 二叉树中的叶子是没有子结点的结点。
- 二叉树中结点 $v$ 的深度是从根结点到 $v$ 的距离（根结点的深度为 $0$）。
- 二叉树的深度是树中结点的最大深度。


- $0\le N\le 10^5$
- $0\leq A_i\le 10^8$（$0\le i\le N$）
- $A_N\ge 1$
- 所有输入均为非负整数。


对于样例 $1$，以下是一种可能的答案：  
![0d8d99d13df036f23b0c9fcec52b842b.png](https://img.atcoder.jp/nomura2020/0d8d99d13df036f23b0c9fcec52b842b.png)   
翻译@[ans_mod998244353](https://www.luogu.com.cn/user/582360)。

## 样例 #1

### 输入

```
3
0 1 1 2```

### 输出

```
7```

## 样例 #2

### 输入

```
4
0 0 1 0 2```

### 输出

```
10```

## 样例 #3

### 输入

```
2
0 3 1```

### 输出

```
-1```

## 样例 #4

### 输入

```
1
1 1```

### 输出

```
-1```

## 样例 #5

### 输入

```
10
0 0 1 1 2 3 5 8 13 21 34```

### 输出

```
264```

# 题解

## 作者：zhangyuhaoaa (赞：2)

## 题意

问是否存在一个深度为 $n$ 的二叉树，使得这个二叉树第 $i$ 层的叶子节点数为 $a_i$。

## 思路

这道题我们要先判断是否能有这么多的节点让他成为叶子节点，我们可以求出这一层中最多能有多少节点，然后在判断这个数是否比这一层要求的节点多，如果多，那么直接输出 $-1$ 即可，记录下为 $b_i$。

然后我们在从后往前遍历，每一次只要 $w$ 比 $b_i$ 大，那么就把 $w$ 替换成 $b_i$，然后继续即可。

## code

```cpp
#include <bits/stdc++.h>
#define re register
#define il inline
#define int long long
#define endl '\n'
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int P = 998244353;
const int INF = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e6 + 5;

il int read() {
	re int x = 0, f = 1; re char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * f;
}

int n;
int ans = 0;
int a[maxn];
int b[maxn];

signed main() {
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    fst;
	
	cin >> n;
	for (int i = 1; i <= n + 1; ++ i ) {
		cin >> a[i];
	}
	for (int i = 1; i <= n + 1; ++ i ) {
		if (i == 1) {
			b[i] = 1;
		} else {
			if (b[i - 1] < 1e18) {
				b[i] = b[i - 1] * 2;
			} else {
				b[i] = 1e18;
			}
		}
		b[i] -= a[i];
		if (b[i] < 0) {
			cout << -1;
			return 0;
		}
	}
	
	int w = 0;
	for (int i = n + 1; i >= 1; -- i ) {
		if (w > b[i]) {
			w = b[i];
		}
		w += a[i];
		ans += w;
	}
	cout << ans;
	
    return 0;
}
```

---

## 作者：_LX_ (赞：2)

二叉树中任意一个非叶子节点最多只能有 $2$ 个子节点，因此我们可以从根节点向下计算出每一层最多有多少非叶子节点。如果计算出某一层的最多非叶子节点数量为负数，即无论如何都无法实现题中要求的二叉树形态，那么可以直接输出 `-1` 。代码如下：
```cpp
for(int i=0;i<n;i++){
	if(i==0) limit[i]=1;
	limit[i]-=a[i];
	if(limit[i]<0){
		write(-1);
		return 0;
	}
}
```
由于每个非叶子节点最多有 $1$ 个或 $2$ 个子节点，根据题中给定了叶子节点的数量，为了使树上总节点数尽可能多，要使只有 $1$ 个子节点的非叶子节点尽可能多。我们可以从底向顶运行，先默认每个非叶子节点只对应一个子节点，如果某一层的非叶子节点数超过了之前计算出的这一层的的最大非叶子节点数，那么这一层的非叶子节点数即为之间计算出的最大非叶子节点数。代码如下：
```cpp
for(int i=n-1;i>=0;i--){
	if(k>limit[i]) k=limit[i];
	k+=a[i];
	ans+=k;
}
```
温馨提醒：本题需要开 `long long` 且可能需要对运行过程中超过 $10^{18}$ 的数直接改为 $10^{18}$ 以防止数字过大。  
AC代码：
```cpp
#define MAXN 500005
#define int long long
int n,a[MAXN],k,ans,lm[MAXN];
signed main(){
	read(n);
	n+=1;
	for(int i=0;i<n;i++) read(a[i]);
	for(int i=0;i<n;i++){
		if(i==0) lm[i]=1;
		else lm[i]=lm[i-1]<1e18?(lm[i-1]<<1):1e18;
		lm[i]-=a[i];
		if(lm[i]<0){
			write(-1);
			return 0;
		}
	}
	for(int i=n-1;i>=0;i--){
		if(k>lm[i]) k=lm[i];
		k+=a[i];
		ans+=k;
	}
	write(ans);
	return 0;
}
```

---

## 作者：JOE_ZengYuQiao_0928 (赞：1)

### 思路分析
本题可以分为两个步骤：
- 判断无解。很简单，根据二叉树的定义，这一层最多能存在的节点数是上一层非叶子节点数的两倍。只需要根据上一层的最多节点数减去上一层的叶子节点数就可以得出这一层的最多节点数，随后判断这一层在最好情况下，能否存在 $a_i$ 个叶子节点。
- 找节点数量，按照每一层的叶子节点数反向贪心即可推出。

**注意：由于这一层的最大节点数量可能大到爆炸，所以我们定一个极大数为节点数的上界，即可有效防止此类情况发生。**
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,M=1e18;
int n,a[N],num[N],ans,cnt=0;
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	cin>>n;
	++n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(i==1)num[i]=1-a[i];
		else if(num[i-1]<M)num[i]=num[i-1]*2-a[i];
		else num[i]=M-a[i];
		if(num[i]<0){
			cout<<"-1";
			return 0;
		}
	}
	for(int i=n;i>=1;i--){
		ans=min(ans,num[i]);
		ans+=a[i];
		cnt+=ans;
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：_czy (赞：0)

这道题可以先判断是否存在，再通过贪心求最小解。

判断是否存在非常容易，因为是二叉树，每层的最大叶子节点个数为上一层的非叶子个数的二倍。

至于最小解，可以倒着做，每次取最小，答案自然也最小。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
int n,a[N];
long long k,s,b[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=0;i<=n;i++){
		cin>>a[i];
		if(i)b[i]=b[i-1]*2;
		else b[i]=1;
		b[i]-=a[i];
		if(b[i]>1e16)b[i]=1e16;
		if(b[i]<0){
			cout<<"-1";
			return 0;
		}
	}
	for(int i=n;~i;i--){
		if(k>b[i])k=b[i];
		k+=a[i],s+=k;
	}
	cout<<s;
}
```

---

