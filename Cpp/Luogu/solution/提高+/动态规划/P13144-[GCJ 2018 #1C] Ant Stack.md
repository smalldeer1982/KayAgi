# [GCJ 2018 #1C] Ant Stack

## 题目描述

Scott 有一个蚂蚁农场，里面有 $N$ 只蚂蚁。每只蚂蚁都有一定的体长和体重。

今天，Scott 给蚂蚁们设置了一个挑战：他把一些食物放在蚂蚁农场的顶部。蚂蚁们会尝试通过把自己叠成一根竖直的“蚂蚁塔”来够到食物，每只蚂蚁都直接背着下一只蚂蚁。这样，每只蚂蚁都要承受其上方所有蚂蚁的重量。Scott 的蚂蚁们非常强壮，每只蚂蚁最多可以承受自身重量的 6 倍。例如，一只重 8 毫克的蚂蚁可以承受两只各重 24 毫克的蚂蚁！每只蚂蚁也有一个体长；具体长度不重要，只要它们的长度都不相同即可。

- 蚂蚁塔必须是线性的。除了最顶上的蚂蚁外，每只蚂蚁正上方必须有且只有一只蚂蚁；除了最底下的蚂蚁外，每只蚂蚁正下方必须有且只有一只蚂蚁。
- 蚂蚁塔中蚂蚁的体长必须从下到上严格递减；这保证了每只新加入蚂蚁都能顺利爬到顶部。
- 对于塔中的每只蚂蚁，其上方所有蚂蚁的总重量不得超过该蚂蚁自身重量的 6 倍。

请问最多能有多少只蚂蚁组成这样一根蚂蚁塔？

## 说明/提示

**样例解释**

在样例 1 中，有两只蚂蚁。第一只重 9 毫克，第二只重 1 毫克，且第二只比第一只体长更长。第一只蚂蚁足够强壮，可以承受第二只蚂蚁（因为它能承受 $9 \times 6$ 毫克），但由于第二只蚂蚁体长更长，不能叠在第一只上。第二只蚂蚁无法承受第一只蚂蚁（因为它只能承受 $1 \times 6$ 毫克，小于 9 毫克）。所以只能单独选其中一只蚂蚁组成“蚂蚁塔”。

在样例 2 中，三只蚂蚁可以全部组成一根蚂蚁塔，第三只承受第二只，第二只承受第一只。

在样例 3 中，最优解是第九只蚂蚁在最底下，其上方再叠七只其它蚂蚁。

**数据范围**

- $7 \leqslant T \leqslant 100$。

**测试点 1（16 分，可见）**

- 恰有 6 组数据 $N = 100$；其余 $T-6$ 组 $2 \leqslant N \leqslant 50$。
- $1 \leqslant W_i \leqslant 1000$，对所有 $i$。

**测试点 2（27 分，隐藏）**

- 恰有 6 组数据 $N = 10^5$；其余 $T-6$ 组 $2 \leqslant N \leqslant 500$。
- $1 \leqslant W_i \leqslant 10^9$，对所有 $i$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2
9 1
3
8 4 100
9
10 10 10 10 10 10 10 10 100```

### 输出

```
Case #1: 1
Case #2: 3
Case #3: 8```

# 题解

## 作者：FS_NEO (赞：0)

考虑 DP，设 $f_i$ 表示选 $i$ 只蚂蚁后蚂蚁塔的最小重量，容易得到转移：

$$ f_i=\min f_{i-1}+a_j \; ,\; 6a_j\le f_{i-1} $$


--------

朴素 DP 是简单的，但是该怎么优化呢？

注意到答案不会太大，原因易得。

于是大胆猜测答案不超过 $10^3$，则时间复杂度变为 $O(n)$，可以通过。

Code：
```cpp
/*

		2025.7.22
		
  * Happy Zenith Noises *
   
*/
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef pair<int,int>P;
const int MAXN=1005,inf=0x3f3f3f3f3f3f3f3f;
int n,a[MAXN*100];
int f[MAXN];
void solve(){
	memset(f,0x3f,sizeof(f));
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	f[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=min(1000ll,i-1);j>=0;j--){
			if(a[i]*6>=f[j])f[j+1]=min(f[j+1],f[j]+a[i]);
		}
	}
	for(int i=MAXN-1;i>=0;i--)if(f[i]<inf){cout<<i<<"\n";return ;}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int T;cin>>T;
	for(int i=1;i<=T;i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
	return 0;
}
```

---

## 作者：wurang (赞：0)

显然从上往下比从下往上好考虑，我们要让体长从上往下递增。此时注意到题目中蚂蚁按照体长严格递增的顺序给出，这进一步证明了我们做法的正确性。

我们从 $1$ 到 $n$ 遍历每只蚂蚁，容易想出状态 $dp_i$ 表示从上往下有 $i$ 只蚂蚁的体重最小值。

当我们遍历到第 $i$ 只蚂蚁且 $dp[j-1] \le a[i] \times 6$ 时，有转移方程：

$$
dp[j] = min(dp[j], dp[j-1] + a[i])
$$

容易写出以下代码：

```cpp
	dp[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = i; j >= 1; j--) // 注意此处倒序转移，和01背包的逻辑一样
		if(a[i]*6 >= dp[j-1]) dp[j] = min(dp[j], dp[j-1] + a[i]);
	}
```

容易发现这个做法是 $n^2$ 的，考虑优化。

我们考虑蚂蚁塔有 $i$ 只蚂蚁时，最下面的蚂蚁能有多轻。

我们运行以下代码可得，当蚂蚁塔的蚂蚁数来到 $140$ 时，最下面的蚂蚁重量已经超过了 $10^9$。

```cpp
	int sum = 0, cnt = 1, n = 140;
	for(int i = 1; i <= n; i++)
	{
		while(cnt * 6 < sum)
			cnt++;
		sum += cnt;
	}
	cout << cnt;
```

所以说蚂蚁塔的蚂蚁数显然会小于等于 $140$。

于是便有了 $O(n)$ 的算法。（虽然有 $140$ 的常数但依然能轻松通过）。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}

int T;
int n;
int a[100005];
int dp[145];


signed main()
{
	T = read();
	for(int Case = 1; Case <= T; Case++)
	{
		memset(dp, 0x3f, sizeof(dp));
		cout << "Case #" << Case << ": ";
		n = read();
		for(int i = 1; i <= n; i++)
			a[i] = read();
		dp[0] = 0;
		for(int i = 1; i <= n; i++)
		{
			for(int j = min(i, 140ll); j >= 1; j--)
				if(a[i]*6 >= dp[j-1]) dp[j] = min(dp[j], dp[j-1] + a[i]);
		}
		for(int i = 140; i >= 1; i--)
		{
			if(dp[i] != 0x3f3f3f3f3f3f3f3f)
			{
				cout << i << "\n";
				break;
			}
		}
	}
	return 0;
}
```

---

