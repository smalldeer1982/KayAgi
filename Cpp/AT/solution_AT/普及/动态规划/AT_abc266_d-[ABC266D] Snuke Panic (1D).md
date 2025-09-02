# [ABC266D] Snuke Panic (1D)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc266/tasks/abc266_d

高橋君はすぬけ君たちを捕まえようとしています。

数直線上の座標 $ 0,1,2,3,4 $ の $ 5 $ 箇所に穴があり、すぬけ君たちの巣につながっています。

これから $ N $ 匹のすぬけ君が穴から出てきます。$ i $ 番目のすぬけ君は時刻 $ T_i $ に座標 $ X_i $ の穴から出てきて、大きさは $ A_i $ であることがわかっています。

高橋君は時刻 $ 0 $ に座標 $ 0 $ におり、数直線上を単位時間あたり $ 1 $ 以下の速さで移動することができます。  
すぬけ君が穴から出てきたのと同じ時刻に同じ座標に高橋君がいるとき、かつ、そのときに限り、高橋君はすぬけ君を捕まえることができます。  
すぬけ君を捕まえるのにかかる時間は無視できます。

高橋君が適切に行動したとき、捕まえることができるすぬけ君の大きさの合計の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ <\ T_1\ <\ T_2\ <\ \ldots\ <\ T_N\ \leq\ 10^5 $
- $ 0\ \leq\ X_i\ \leq\ 4 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

次のように行動するのが最適です。 - 座標 $ 0 $ で待機し、時刻 $ 1 $ に $ 1 $ 番目のすぬけ君を捕まえる - 座標 $ 4 $ へ移動し、時刻 $ 5 $ に $ 3 $ 番目のすぬけ君を捕まえる $ 1 $ 番目と $ 2 $ 番目のすぬけ君を両方とも捕まえることはできないので、これが最大です。

### Sample Explanation 2

高橋君はすぬけ君を $ 1 $ 匹も捕まえることができません。

## 样例 #1

### 输入

```
3
1 0 100
3 3 10
5 4 1```

### 输出

```
101```

## 样例 #2

### 输入

```
3
1 4 1
2 4 1
3 4 1```

### 输出

```
0```

## 样例 #3

### 输入

```
10
1 4 602436426
2 1 623690081
3 3 262703497
4 4 628894325
5 3 450968417
6 1 161735902
7 1 707723857
8 2 802329211
9 0 317063340
10 2 125660016```

### 输出

```
2978279323```

# 题解

## 作者：DengDuck (赞：6)

略加转换，假设我们是上帝，把所有时刻的坑摆列在一起，形成一个二维矩阵，我们往下走。

我们给读入的  Snuke 的位置打上标记，然后接下来得到一个类似 [数字三角形](https://www.luogu.com.cn/problem/P1216) 的问题。

设 $f_{i,j} $ 表示从 $(0,0)$ 走到 $(i,j)$  可抓到的 Snuke 总大小最大值。

$$
	f_{i,j} = \max(f_{i-1,j-1},f_{i-1,j},f_{i-1,j+1})+a_{i,j}
$$

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, x, y, z, f[100005][7], a[100005][7];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y >> z;
        y++;
        a[x][y] += z;
    }
    memset(f, -1, sizeof(f));
    f[0][1] = 0;
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= 5; j++) {
            f[i][j] = max(f[i - 1][j], max(f[i - 1][j - 1], f[i - 1][j + 1]));
            if (f[i][j] != -1)
                f[i][j] += a[i][j];
        }
    }
    cout << max(f[x][1], max(f[x][2], max(f[x][3], max(f[x][4], f[x][5]))));
}
```

---

## 作者：xiaomuyun (赞：3)

- [洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc266_d)
- [AtCoder 题目传送门](https://atcoder.jp/contests/abc266/tasks/abc266_d)

## 思路分析

考虑 dp。

设 $dp_{i,j}$ 为在第 $i$ 时刻，高桥在 $j$ 位置的答案。

因为每秒高桥只能移动一个位置，所以 $dp_{i,j}=\max(dp_{i-1,j-1},dp_{i-1,j},dp_{i-1,j+1})+x$，其中 $x$ 表示当前位置 Snuke 的大小，没有 Snuke 则为 $0$。

## 代码实现

有几点要注意：

1. 一开始高桥在 $0$ 位置，所以在第 $1$ 时刻他到不了 $2,3,4$ 的位置，第 $2$ 时刻到不了 $3,4$ 的位置，以此类推。所以在 $dp$ 第二层循环的时候要注意限制一下循环的范围。
2. 在最后一个 Snuke 出现之后，再跑来跑去已经没有意义了，所以 $dp$ 第一层循环的范围应该是从 $1$ 到 $mxt$，其中 $mxt$ 为最后一个 Snuke 出现的时间。这个时间可以在输入时维护。
3. 答案应为 $\max\limits_{i=0}^4 dp_{mxt,i}$，其中 $mxt$ 为最后一个 Snuke 出现的时间。
4. 找 $x$ 可以用 `lower_bound` 找，因为每个时刻最多只会出现一只 Snuke（见数据范围），所以非常方便。
5. $dp$ 时 $dp_{i-1,j-1}$ 和 $dp_{i-1,j+1}$ 有可能越界，需要特判。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include<algorithm>
#include<cstdio>
#define int long long
using namespace std;
const int maxn=1e5+1;
int n,t[maxn],x[maxn],a[maxn],dp[maxn][5],mxt=0;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld%lld%lld",&t[i],&x[i],&a[i]);
		mxt=max(t[i],mxt);//统计最后一个Snuke出现的时间。
	}
	for(int i=1;i<=mxt;++i){
		for(int j=0;j<=min(i,4ll);++j){//限制循环范围。
			dp[i][j]=dp[i-1][j];
			if(j>0) dp[i][j]=max(dp[i-1][j-1],dp[i][j]);//dp，注意特判。
			if(j<4) dp[i][j]=max(dp[i-1][j+1],dp[i][j]);
			int pos=lower_bound(t+1,t+1+n,i)-t;//二分找x。
			if(t[pos]==i&&x[pos]==j) dp[i][j]+=a[pos];
		}
	}
	printf("%lld\n",max(max(max(max(dp[mxt][0],dp[mxt][1]),dp[mxt][2]),dp[mxt][3]),dp[mxt][4]));
	return 0;
}
```

输入似乎是按照 $t$ 值排序的。

~~因为“中文句子句末不加句号”的奇怪原因被打回了，现在加上了注释的句号。~~

---

## 作者：rai1gun (赞：2)

### 1.题意

高桥在 $0$ 点。$(0,1,2,3,4)$ 这些点会有 Snuke 出现，逮捕的价值为 $v_i$。高桥每秒移动 $1$ 个单位，问最大价值。

### 2.解法

简单 dp 题。

$dp_{i,j}$ 为高桥第 $i$ 秒在在 $j$ 点的最大价值。

现在所处的位置必然由左，右或当前位置转移而来。

转移方程易得为：

$$dp_{i,j}=max\{dp_{i,j-1},dp_{i-1,j-1},dp_{i+1,j-1}\}+v_i$$

当 $t>\sum\limits_{i=1}^n\max t_i$ 时，不会有 Snuke 出现，因此最终的状态是 $\sum\limits^{n}_{i=1}\max dp_{\sum\limits_{j=1}^n \max t_j,i}$

---

## 作者：_qingshu_ (赞：1)

# 题意：

有一个长度为 $5$ 的线段，坐标为 $0,1,2,3,4$。一开始我们在 $0$ 的位置，每一次可以移动 $1$ 单位或者不移动。

有 $N$ 个得分点会在 $T_i$ 时刻在 $X_i$ 出现，如果此时我们在这个点上，可以得到 $A_i$ 的得分。

询问最大得分。

# 思路：

考虑 DP。

我们定义 $f_{i,j}$ 为在第 $i$ 时刻走到了 $j$ 号坐标的最大得分。因为我们可以选择不动，所以我们可以继承 $f_{i-1,j}$。再因为我们每一次可以移动一单位，那么我们也可以继承 $f_{i-1,j-1}$ 与 $f_{i-1,j+1}$。最后判断当前时刻的得分点与现在为止是否相同就好了。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[520000][5],ans;
int n,a,t,x,maxt;
pair<int,int>s[5200010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t>>x>>a;
		s[t]={x,a};
		maxt=max(t,maxt);
	}
	for(int i=1;i<=maxt;i++){
		for(int j=0;j<=min(i,4);j++){
			dp[i][j]=dp[i-1][j];
			if(j!=0){
				dp[i][j]=max(dp[i][j],dp[i-1][j-1]);
			}
			if(j!=4){
				dp[i][j]=max(dp[i][j],dp[i-1][j+1]);
			}
			if(s[i].first==j){
				dp[i][j]+=s[i].second;
			}
//			cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
			if(i==maxt){
				ans=max(ans,dp[maxt][j]);
			}
		}
	}
	cout<<ans;
	
}

```

---

## 作者：hanyuchen2019 (赞：1)

### part 1 思路

简单 DP。

设 $dp_{i,j}$ 表示在时间 $i$ 时，他处在第 $j$ 个洞边。

那么~~很显然~~，如果此时刚好有一条 `snuke` 从洞里钻出来，那么：

```cpp
dp[i][j]+=max(dp[i-1][j-1],max(dp[i-1][j+1],dp[i-1][j]))+a[i];
```

由于一开始他处在第一个洞的位置，所以要把其它的洞预先设成 $-\infty$。

但根据上面的做法，$5\times 10^{10}$ 的运算量显然会 TLE，所以需要一个优化：

由于题目保证 `snuke` 出现时间升序排列，所以可以维护一个指针，记录当前处理到哪一只。

### part 2 code

[赛时AC code](https://atcoder.jp/contests/abc266/submissions/34383909)


---

## 作者：Epoch_L (赞：1)

## D
简单 dp，令 $f(i,j)$ 表示第 $i$ 个时间在第 $j$ 个位置的最大价值，从上一个时间转移，可以向左，向右或者不动，即：
$$
f(i,j)=\max\{f(i-1,j-1),f(i-1,j),f(i-1,j+1)\}+s(i,j)
$$
$s(i,j)$ 就是读入，注意其中有一些限制。

[Code](https://atcoder.jp/contests/abc266/submissions/34441427 "Code")

---

## 作者：Swirl (赞：0)

# 思路简述

这是一道普通的 Dp，难度不大。

不妨令 $Dp_{i,j}$ 为在第 $i$ 个时刻走到 $j$ 的最多 Snuke 数。

由于我们每次移动只能走一格或不走，所以可推出状态转移方程：

$$
Dp_{i,j}=\max\{Dp_{i-1,j},Dp_{i-1,j-1},Dp_{i-1,j+1}\}+a_{i,j}
$$

由于最后一个 Snuke 已经出现，就没必要再走了。

最后依照状态转移方程写出代码即可。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0)
// #pragma GCC optimize(2)
#define int long long
using namespace std;

int n;
int a[100005][8], Dp[100005][8];//将数组开大一点，避免 Dp[i-1][j+1] 下标越界
int tmp;

void dd(int i, int j) {//进行 Dp
    Dp[i][j] = Dp[i - 1][j];
    Dp[i][j] = max(Dp[i - 1][j - 1], Dp[i][j]);
    Dp[i][j] = max(Dp[i - 1][j + 1], Dp[i][j]);
    Dp[i][j] += a[i][j];
}

signed main() {
    ios;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        y++;//这里将 y++ 巧妙解决了 Dp[i-1][j-1] 越界的情况
        a[x][y] += z;
        tmp = max(tmp, x);//计算最后一个 Snuke 出现的位置
    }
    memset(Dp, 0xff, sizeof(Dp));
    Dp[0][1] = 0;
    for (int i = 1; i <= tmp; i++) {
        for (int j = 1; j <= 5; j++) {
            dd(i, j);
        }
    }
    cout << max(max(Dp[tmp][4], Dp[tmp][1]), max(Dp[tmp][2], max(Dp[tmp][3], Dp[tmp][5])));//计算最终答案
    return 0;
}
```

---

## 作者：Demons_Killer (赞：0)

# 思路:
本体算法为动态规划。

因为高桥每次只能向前或向后移动一格，我们可得状态转移方程为 $f_{i, j} = \max(f_{i - 1, j + 1}, f_{i - 1, j - 1}) + k$
        其中 $k$ 表示 $i$ 时再第 $j$ 个坑里能捕获的价值，$f_{i, j}$ 则表示在 $i$ 时，第 $j$
        个坑里捕获的最大价值。可用动态数组来存贮对应时刻出现的物品的下标，如果当前时刻对应坑中出现了物品， $f_{i, j}$
        就加上对应价值。最后答案为结束时刻各个坑所得最大价值的最大值。

注意在左移和右移中判断是否越界。

# code：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
ll x[N], a[N];
ll f[N][5];
ll n;
int ttt;
vector<int> t[N];//用于存储对应时刻出现物品的下标

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int tt;
		cin >> tt >> x[i] >> a[i];
		ttt = max(ttt, tt);
		t[tt].push_back(i);
	}

	for (int i = 1; i <= ttt; i++) {
		for (int j = 0; j <= min(i, 4); j++) {
			f[i][j] = f[i - 1][j];
			if (j > 0) {//判断是否越界
				f[i][j] = max(f[i][j], f[i - 1][j - 1]);
			}
			if (j < 4) {
				f[i][j] = max(f[i][j], f[i - 1][j + 1]);
			}
			for (int k = 0; k < t[i].size(); k++) {
				if (x[t[i][k]] == j) {
					f[i][j] += a[t[i][k]];
				}
			}
		}
	}

	cout << max({f[ttt][0], f[ttt][1], f[ttt][2], f[ttt][3], f[ttt][4]});//输出答案
	return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

## 思路

一道 $\xcancel{easy}$ DP。

- 用 $dp_{i,j}$ 表示时间为 $i$，处于第 $j$ 位能取到的最大值。

- 用 $mp_{i,j}$ 表示时间为 $i$，第 $j$ 位的 Snuck 的长度，即获得的收益，如果不存在 Snuck，$mp_{i,j}=0$。

对于每一个 $dp_{i,j}$，可以由上一时间不动得到，也可以由上一时间向左或向右移动一步得到。

于是有 

$dp_{i,j}=\operatorname{max}(dp_{i-1,j},dp_{i-1,j-1},dp_{i-1,j-1})+mp_{i,j}$。

#### 考虑特殊情况。

无法取到 $dp_{i,j}$，那么可以把所有 $dp_{i,j}$ 初始化为 $-1$。

由于从 $0$ 号开始取，$dp_{0,0}=0$。

只有能取到，才能加上 $mp_{i,j}$。

## AC代码

```cpp
#include<bits/stdc++.h>
#define int long long//养成良好习惯
using namespace std;
int n,mp[1000001][5],dp[10001][5],ans,mx;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		mp[x][y]+=z;
		mx=max(mx,x);
	}
	memset(dp,-1,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=mx;i++)
		for(int j=0;j<5;j++){
			if(j>0)dp[i][j]=max(dp[i][j],dp[i-1][j-1]);
			if(j<4)dp[i][j]=max(dp[i][j],dp[i-1][j+1]);
			dp[i][j]=max(dp[i-1][j],dp[i][j]);
			if(dp[i][j]!=-1)dp[i][j]+=mp[i][j];
		}
	for(int i=0;i<5;i++)ans=max(ans,dp[mx][i]);
	cout<<ans;
	return 0;
} 
```


---

