# Rudolf and the Ball Game

## 题目描述

$n$ 个人站成一个圈，按照顺时针编号依次是 $1$ 到 $n$。

现在这 $n$ 个人玩一个传球游戏，第 $i$ 次传球可以向顺时针方向传给与自己距离为 $d_i$ 的距离，或者向逆时针方向传给与自己距离为 $r_i$ 的距离。

游戏总共进行了 $m$ 轮传球，给你初始拿到球的人的编号 $x$ 和每次传球的方向和距离 $r_i$（有可能方向未知），求出最后可能是谁拿到了球，**按编号从小到大**输出。

------------

## 说明/提示

#### 样例解释
下面是第一个测试用例的三次传球的示意图。箭头表示可能的传球方向。在传球后可能持有球的玩家被标记为灰色。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941D/de43c3cc1c4b12f903e5224359bac3a10205e9a9.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941D/1a47b05e6478f36a49179722556df26c9f84bbc8.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941D/47036b3bd9ad777cfd4d3801abb62bd85bcbcc75.png)

------------

对于 $100\%$ 的数据，$1 \le t \le 1000,1 \le x  \le n \le 1000,1 \le m \le 1000,1 \le n\cdot m \le 2\cdot10^5,1 \le r_i \le n-1$。

## 样例 #1

### 输入

```
5
6 3 2
2 ?
2 ?
2 ?
12 1 2
3 1
10 7 4
2 ?
9 1
4 ?
7 0
2 0
8 1
5 ?
5 3 1
4 0
4 ?
1 ?
4 1 1
2 ?```

### 输出

```
3
2 4 6 
1
11 
4
3 5 7 9 
3
2 3 5 
1
3```

# 题解

## 作者：GenesisCrystal (赞：7)

~~Dp万岁！！！~~

## Soulution
用 $dp_{i,j}$ 表示第 $i$ 次传球后 $j$ 号成员有没有可能拿到球。

对于每一次传球，在每一个上一次可能拿到球的人进行传球，设上一次能拿到球的人的编号是 $j$。

如果是顺时针，那么分两种情况：

1. $j + r > n$

那么传到球的会是 $j - (n - r)$ 也就是 $j + r - n$。

2. $j + r \le n$

传到球的是 $j + r$。

如果是逆时针，那么也分两种情况：

1. $j \le r$

那么传到球的会是 $j + (n - r)$ 也就是 $j +n - r$。

2. $j > r$

传到球的是 $j - r$。

最后，用一个 $c$ 记住个数，让后枚举所有 $1 \le i \le n$ 如果 $dp_{m, i}$ 是 $1$，那么就输出。

## Code

```cpp
/// @author WUYIXUAN_
#include <iostream>

using namespace std;

const int kMaxN = 1001;

int t, n, m, x, r;
char c;

int main() {
  for (cin >> t; t; t--) {
    cin >> n >> m >> x;
    bool dp[kMaxN][kMaxN] = {};
    dp[0][x] = 1;
    for (int i = 1; i <= m; i++) {
      cin >> r >> c;
      for (int j = 1; j <= n; j++) {
        if (c != '0') {
          if (j <= r) {
            dp[i][j + (n - r)] |= dp[i - 1][j];
          } else {
            dp[i][j - r] |= dp[i - 1][j];
          }
        }
        if (c != '1') {
          if (j + r > n) {
            dp[i][j - (n - r)] |= dp[i - 1][j];
          } else {
            dp[i][j + r] |= dp[i - 1][j];
          }
        }
      }
    }
    int c = 0;
    for (int i = 1; i <= n; i++) {
      c += dp[m][i];
    }
    cout << c << '\n';
    for (int i = 1; i <= n; i++) {
      if (dp[m][i]) {
        cout << i << ' ';
      }
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：Infinite_Loop (赞：3)

# CF1941D
## 题意
有 $n$ 个人围成一圈扔球，从第 $x$ 个人开始，进行 $m$ 轮，已知第 $i$ 轮扔的距离 $r _ {i}$ 和 $c _ {i}$。

- $c _ {i} = 0$，则往顺时针扔球。
- $c _ {i} = 1$，则往逆时针扔球。
- $c _ {i} = ?$，则往顺时针或逆时针扔球。

问最终球可能在哪几个人手中。
## 思路
本题可以使用数据结构 set（set 可以去重）。考虑枚举 $m$ 轮，当在第 $i$ 轮时，先取出上一轮可能有球的人的编号，然后根据 $c _ {i}$ 计算出这轮后可能有球的人的编号，以此类推，最终输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000+10;
int t,n,m,x,r[N];
char c[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>x;
		for(int i=1;i<=m;i++)cin>>r[i]>>c[i];
		set<int>ans;
		ans.insert(x);
		for(int i=1;i<=m;i++){
			set<int>now;
			if(c[i]=='0'){
				for(auto j:ans){
					int x=(j+r[i]-1)%n+1;
					now.insert(x);
				}
			}else if(c[i]=='1'){
				for(auto j:ans){
					int x=(n+j-r[i]-1)%n+1;
					now.insert(x);
				}
			}else{
				for(auto j:ans){
					int x=(j+r[i]-1)%n+1;
					int y=(n+j-r[i]-1)%n+1;
					now.insert(x);
					now.insert(y);
				}
			}
			ans=now;
		}
		cout<<ans.size()<<'\n';
		for(auto i:ans)cout<<i<<" ";
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：lalaji2010 (赞：2)

# CF1941D
## 分析
传球的可能方向一共有三种情况：

* 顺时针传。
* 逆时针传。
* 既顺时针传又逆时针传。

很显然的dp。

那么我们考虑初始球在编号为 $x$ 的人手里，在传球距离为 $dis$ 的情况下，设 $dp_{i,j}$表示 第 $i$ 轮编号为 $j$ 的人手里是否有可能有球。当然 $dp_{0,x}=1$。

1.若本轮顺时针传球：

* 当 $j+dis \leq n$，$dp_{i,j+dis}\leftarrow dp_{i-1,j}$
* 当 $j+dis>n$，$dp_{i,j+dis-n}\leftarrow dp_{i-1,j}$

2.若本轮逆时针传球：

* 当 $j-dis \geq 1$，$dp_{i,j-dis}\leftarrow dp_{i-1,j}$
* 当 $j-dis<1$，$dp_{i,j+n-dis}\leftarrow dp_{i-1,j}$

3.若本轮既可以顺时针传球又可以逆时针传球：

* 当 $j+dis \leq n$，$dp_{i,j+dis}\leftarrow dp_{i-1,j}$

* 当 $j+dis>n$，$dp_{i,j+dis-n}\leftarrow dp_{i-1,j}$

* 当 $j+dis \leq n$，$dp_{i,j+dis}\leftarrow dp_{i-1,j}$
* 当 $j+dis>n$，$dp_{i,j+dis-n}\leftarrow dp_{i-1,j}$

依此推论进行状态转移即可。

最后对每一个满足 $dp_{m,i}=1$ 的 $i$ 进行计数并输出即可。
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,x;
int dp[1005][1005];
int main(){
    cin>>t;
    while(t--){
    	memset(dp,0,sizeof dp);
        cin>>n>>m>>x;;
        dp[x][0]=1;
        int dis;
        char twd;
        for(int i=1;i<=m;i++){
            cin>>dis>>twd;
            for(int j=1;j<=n;j++){
                if(twd=='0'){
                    if(j+dis>n){
                        dp[j+dis-n][i]|=dp[j][i-1];
                    }else{
                        dp[j+dis][i]|=dp[j][i-1];
                    }
                }else if(twd=='1'){
                    if(j-dis<1){
                        dp[j+n-dis][i]|=dp[j][i-1];
                    }else{
                        dp[j-dis][i]|=dp[j][i-1];
                    }
                }else{
                    if(j+dis>n){
                        dp[j+dis-n][i]|=dp[j][i-1];
                    }else{
                        dp[j+dis][i]|=dp[j][i-1];
                    }
                    if(j-dis<1){
                        dp[j+n-dis][i]|=dp[j][i-1];
                    }else{
                        dp[j-dis][i]|=dp[j][i-1];
                    }
                }
            }
        }
        long long res=0;
        for(int i=1;i<=n;i++){
            res+=dp[i][m];
        }
        cout<<res<<"\n";
        for(int i=1;i<=n;i++){
            if(dp[i][m]){
                cout<<i<<" ";
            }
        }
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：luqyou (赞：2)

# 思路

我们考虑如何从一次传球过后的可能性转移到下一次传球过后的可能性。

如果这一次传球可以顺时针传，则当前可能的顺时针传 $r$ 个单位就是下一次可能的。逆时针同理。

不确定的话只要取个或就可以了。更多细节在代码。

时间复杂度 $O(nm)$。

# code
 
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn=2e5+10;
int n,m,x,a[maxn],b[maxn],c[maxn];
void solve(){
	cin>>n>>m>>x;
	a[x]=1;
	while(m--){
		int r;
		char op;
		for(int i=1;i<=n;i++){
			b[i]=c[i]=0;
		}
		cin>>r>>op;
		if(op=='0'||op=='?'){
			for(int i=1;i<=n;i++){
				int pos=(i+r-1)%n+1;
				b[pos]=a[i];
			}
		}
		if(op=='1'||op=='?'){
			for(int i=1;i<=n;i++){
				int pos=(i+r-1)%n+1;
				c[i]=a[pos];
			}
		}
//		for(int i=1;i<=n;i++){
//			cout<<b[i]<<" "<<c[i]<<endl;
//		}
		for(int i=1;i<=n;i++){
			a[i]=b[i]|c[i];
		}
	}
	int res=0;
	for(int i=1;i<=n;i++){
		res+=a[i];
	}
	cout<<res<<endl;
	for(int i=1;i<=n;i++){
		if(a[i]) cout<<i<<" ";
		a[i]=0; 
	}
	cout<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：2huk (赞：1)

有 $n$ 个人围成一圈。最开始第 $x$ 个人拿着一个球。

接下来会发生 $m$ 个事件，每个事件形如 $(r_i, c_i)$，其中：

- $c_i = \texttt 0$ 表示当前手中有球的人将球**顺时针**传给第 $x_i$ 个人。
- $c_i = \texttt 1$ 表示当前手中有球的人将球**逆时针**传给第 $x_i$ 个人。
- $c_i = \texttt ?$ 表示这个事件不清楚，当前手中有球的人将球**顺时针**或**逆时针**传给第 $x_i$ 个人。

求最终哪些人可能有球。

---

我们设 bool 状态 $f_{i, j}$ 表示第 $i$ 个事件结束后，第 $j$ 个人是否有可能拿着球。开始 $f_{0, x} = \text{true}$。

转移极易，我们令 $F(x, y)$ 表示从 $x$ 顺时针第 $y$ 个人的编号，$G(x, y)$ 表示从 $x$ 逆时针第 $y$ 个人的编号。那么有

$$
f_{i + 1, F(j, r_i)} = f_{i +1 , G(j, r_i)} = f_{i, j}
$$

最后看哪些 $j$ 满足 $f_{n, j} = \text{true}$ 即可。

<https://codeforces.com/contest/1941/submission/251204743>

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1941d-rudolf-and-the-ball-game-de-ti-jie/)
## 题目大意
有 $n$ 个人投球，投了 $m$ 次。第 $i$ 次投球时想左、右或者随便一个方向投掷 $r_i$ 个人。从第 $x$ 个人开始投球，询问最后球在最后有可能在谁的手里。

其中 $1\le n,m \le 1000,1\le x,r\le n,\sum n\cdot m \le 2\times 10^5$。
## 思路
如果遇到方向不确定的情况，可以暴力的考虑直接枚举。考虑在最坏的情况下，全部的投球肯能方向不确定，那么我们就需要枚举 $2^m$，因为这些人一共会接到 $2^m$ 次球。

在一轮投球中只有 $n$ 个人但是却接到了 $2^m$ 次球，可见一个人可能会多次接到球。因为在一轮中，不论一个人接到多少次球那么效果其实都是一样的。

所以设 $f_{i,j}$ 表示在第 $i$ 次投球时，第 $j$ 个人是否有可能拿到球。假设 $g(j,r_i)$ 表示第 $j$ 个人移动 $r_i$ 后的位置，发么状态转移方程为 
$$f_{i,g(j,r_i)}=\max(f_{i,g(j,r_i)},f_{i-1,j})$$
## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1005;
int n,m,a[N],f[N][N],x;
char c[N];
void solve(){
	cin>>n>>m>>x;
	for(int i=1;i<=m;i++) cin>>a[i]>>c[i];
	for(int i=0;i<=m;i++) for(int j=0;j<=n;j++) f[i][j]=0;
	f[0][x-1]=1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<n;j++){
			if(c[i]=='0'||c[i]=='?') f[i][(j+a[i])%n]|=f[i-1][j];
			if(c[i]=='1'||c[i]=='?') f[i][(j-a[i]+n)%n]|=f[i-1][j];
		}
	}
	vector<int> ans;
	for(int i=0;i<n;i++) if(f[m][i]) ans.push_back(i+1);
	cout<<ans.size()<<'\n';
	for(int i:ans) cout<<i<<' ';
	cout<<'\n';
}signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：haokee (赞：0)

我们发现，虽然有可能每一次 $m$ 都是 `?` 的形式，可以产生出 $2^{1000}$ 种状态。但是由于 $n$ 只有 $1000$，而相同位置的状态是可以合并的，因此每一次之后的状态就最多只有 $1000$ 种。设 $dp_{i,j}$ 表示为经过了 $i$ 次操作后能否传到编号为 $j$ 的人，那么这就是一道简简单单的 dp 了。

这里好渴鹅使用了滚动数组的方法，用 $f$ 存储 $dp_{i-1}$，用 $a$ 存储 $dp_i$，然后记得清空。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int kMaxN = 1005;

int f[kMaxN], a[kMaxN], t, n, m, x;
char c;

int forward(int u, int v) { return (u + v - 1) % n + 1; }

int reverse(int u, int v) { return u > v ? u - v : n - (v - u); }

int main() {
  for (cin >> t; t; t--) {
    cin >> n >> m >> x;
    fill(f + 1, f + n + 1, 0), f[x] = 1;
    for (int r; m; m--) {
      cin >> r >> c;
      fill(a + 1, a + n + 1, 0);
      for (int i = 1; i <= n; i++) {
        if (c == '0') {
          a[forward(i, r)] |= f[i];
        } else if (c == '1') {
          a[reverse(i, r)] |= f[i];
        } else {
          a[forward(i, r)] |= f[i];
          a[reverse(i, r)] |= f[i];
        }
      }
      for (int i = 1; i <= n; i++) {
        f[i] = a[i];
      }
    }
    cout << count(a + 1, a + n + 1, 1) << '\n';
    for (int i = 1; i <= n; i++) {
      if (a[i]) {
        cout << i << ' ';
      }
    }
    cout << '\n';
  }
  return 0;
}
```

---

