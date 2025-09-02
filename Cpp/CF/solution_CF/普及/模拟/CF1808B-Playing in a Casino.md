# Playing in a Casino

## 题目描述

现有一种在太阳系中广为人知的卡牌游戏，叫做“Galaxy Luck”。

在每场游戏中，会有 $n$ 位玩家，每人 $1$ 张卡片，每张卡片上有 $m$ 个数字，每两位玩家会进行一次游戏，并且这两人之间只进行一次。例如：有四位玩家，第一位对第二位，第一位对第三位，第一位对第四位，第二位对第三位，第二位对第四位，第三位对第四位，共 $6$ 次游戏。

这种游戏有特定的获胜规则，赢家所获得的点数也有特定的计算方式；由于获胜规则很复杂，这里不会讲述。但更值得注意的是，应该给赢家多少点数。其遵循以下计算方式：第一位玩家有数字 $a_1,a_2,...,a_m$，第二位玩家有数字 $b_1,b_2,...,b_m$，那么赢家会得到的点数为：$|a_1-b_1|+|a_2-b_2|+\cdot\cdot\cdot+|a_m-b_m|$，其中， $|x|$ 代表 $x$ 的绝对值。

为了确定奖池的大小，需要编写一个程序来计算总点数。

## 说明/提示

例如第一组数据：

第一位对第二位玩家，胜者得到 $|1-7|+|4-9|+|2-2|+|8-1|+|5-4|=19$ 点。

第一位对第三位玩家，胜者得到 $|1-3|+|4-8|+|2-5|+|8-3|+|5-1|=18$ 点。

第二位对第三位玩家，胜者得到 $|7-3|+|9-8|+|2-5|+|1-3|+|4-1|=13$ 点。

总点数为 $19+18+13=50$ 点。

## 样例 #1

### 输入

```
3
3 5
1 4 2 8 5
7 9 2 1 4
3 8 5 3 1
1 4
4 15 1 10
4 3
1 2 3
3 2 1
1 2 1
4 2 7```

### 输出

```
50
0
31```

# 题解

## 作者：ran_qwq (赞：11)

答案就是 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\sum\limits_{k=1}^m\left|c_{i,k}-c_{j,k}\right|$，但是直接算时间复杂度为 $O(n^2m)$，考虑优化。

可以把式子中的 $k$ 提前，即变为 $\sum\limits_{k=1}^m\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\left|c_{i,k}-c_{j,k}\right|$。再给每一列从大到小排个序，注意到 $\left|c_{i,j}-c_{i+2,j}\right|=\left|c_{i,j}-c_{i+1,j}\right|+\left|c_{i+1,j}-c_{i+2,j}\right|$，推广一下就可以把每一列的任意两个数的绝对值像这样表示出来。对于每一列每相邻两个数的差计算贡献，乘上这个差即可。

如何计算贡献呢？设 $\left|c_{i,j}-c_{i+1,j}\right|=d_{i,j}$。则 $d_{1,j}$ 上面有 $1$ 个数，下面有 $n-1$ 个数，贡献为 $1\times(n-1)$。类似的，$d_{2,j}$ 贡献为 $2\times(n-2)$……

注意事项：

1. $n$ 可以到 $3\times10^5$，$m$ 也可以到 $3\times10^5$，所以要用 vector 动态扩容。

1. 要开 long long，不开 long long 见祖宗。

1. 多测 vector 要清空。

---

## 作者：Mellow_Orchid (赞：10)

这是鄙人的第一篇题解，用的方法也比较入门，请多关照。

言简意赅的，暴力计算是显然会超时的，又有绝对值的计算，可以先进行排序，再计算其系数并进一步运算，以达到简便运算的目的。

[原测评记录。](https://codeforces.com/contest/1808/submission/200648857)

下面的代码经过整理，思路不变。

```cpp
#include <iostream>
#include <algorithm>
#define ull unsigned long long
using namespace std;

ull b[300005];
int main()
{
    ull t, n, m, sum;
    cin >> t; // 总组数
    while (t--)
    {
        cin >> n >> m;
        ull a[n + 5][m + 5];
        for (ull i = 1; i <= n; i++)
            for (ull j = 1; j <= m; j++)
                scanf("%llu", &a[i][j]); // 数据读入
        sum = 0; // sum 清零
        for (ull j = 1; j <= m; j++) // 对于每一列
        {
            for (ull i = 1; i <= n; i++)
                b[i] = a[i][j]; // 放到另一个数组中，方便操作
            sort(b + 1, b + 1 + n); // 排序
            for (ull i = 1; i <= n; i++)
                sum = sum + (2 * i - n - 1) * b[i]; // 计算系数并运算
        }
        cout << sum << endl;
    }
    // system("pause");
    return 0;
}
```

对于系数的计算，个人理解为：

假定有
$$a_{1}\ \ a_{2}\ \ a_{3}\ \ a_{4}\ \ a_{5}$$
这样的数组，已经按照升序排列，那么在本题中，有
$$a_{5}-a_{1}+a_{4}-a_{1}+a_{3}-a_{1}+a_{2}-a_{1}+a_{5}-a_{2}+a_{4}-a_{2}+a_{3}-a_{2}+a_{5}-a_{3}+a_{4}-a_{3}+a_{5}-a_{4}$$
这样的计算方式。化简后，得
$$4\times a_{5}+2\times a_{4}+0\times a_{3}-2\times a_{2}-4\times a_{1}$$
可知 $a_{5}$ 被加了 $4$ 次、$a_{4}$ 被加了 $3$ 次又减了 $1$ 次……可以发现，被加的次数为 $i-1$，被减的次数为 $n-i$，可得
$$a_{i}\times((i-1)-(n-i))$$
$$\text{当前数字}\times(\text{被加次数}-\text{被减次数})$$
那么
$$\text{原式}=\sum_{i=1}^{n}a_{i}\times(2\times i-n-1)$$
大致就是这样吧。

以及，非常荣幸这道题采用了小生的翻译。

---

## 作者：luguangxing (赞：5)

思路：

$3$ $5$

$1$ $4$ $2$ $8$ $5$

$7$ $9$ $2$ $1$ $4$

$3$ $8$ $5$ $3$ $1$

这组数据输出是 $50$ 题目上也有解释，一开始我的思路是用循环把他跑一遍，但一看范围就肯定会 t 于是就要开始优化，我们把这组数据分成 $5$ 小组竖着分，看 $1$ $7$ $3$ 我们先把他从小到大排序是 $1$ $3$ $7$，把他由下标简化成另一个式子：$7 \times 2 + 3 \times 1 + 1 \times 0 - 7 \times 0 - 3  \times 1 - 1 \times 2$。 这个式子的结果与 $| 1 - 7 | + |1 - 3 | + | 7 - 3 |$ 的结果是一样的但比这个式子优化了不少。

于是就由这个思路写起了第一份程序。

用数组写的第一份代码：还是 t 了。

[数组代码](https://www.luogu.com.cn/record/117023833)

于是就继续优化使用了 $2$ 维 `vector` 减少空间复杂度就过了。

代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		vector<vector<int>>v(m,vector<int>(n,0));//定义2维vector把所有位都初始化为0
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				cin>>v[j][i];
			}
		}
		long long res=0;
		for(long long j=0;j<m;j++)
		{
			sort(v[j].begin(),v[j].end());//排序
			for(long long i=0;i<n;i++)
			{
				long long sub=n-1-i;
				res+=i*v[j][i]-sub*v[j][i];
			}
		}
		cout<<res<<endl;
	} 
	return 0;
}
```

---

## 作者：Zimo_666 (赞：1)

## B. Playing in a Casino

不妨考虑一个数对这个列的贡献。

显然是对于大于它的数是负贡献，对于小于它的数是负贡献。

排序然后扫一遍即可。

[Code](https://codeforces.com/contest/1808/submission/224233919)

---

## 作者：Binary_Lee (赞：1)

## [题面传送门](https://www.luogu.com.cn/problem/CF1808B)

### 解决思路

来一种小丑的做法。

首先，题目没有给定 $n,m$ 的具体范围，所以可以用 $\text{vector}$ 来存储这个矩阵，这里不再细讲。

然后考虑如何求每一列数两两之间差的绝对值之和。

题目相当于维护一些点之间的距离，而且值域比较小，所以我们想到了使用树状数组。具体怎么维护呢？

考虑加入一个数。我们把它与已经存在的数所产生的答案分为两部分：比它小的和比它大的。假设这个数为 $x$，比它小的数有 $cnt_1$ 个，比它小的数的总和为 $sum_1$ ，则对于比它小的数，对答案产生的贡献为 $x\times cnt_1-sum_1$。同理，假设比它小的数有 $cnt_2$ 个，比它小的数的总和为 $sum_2$，对于比它大的数，对答案产生的贡献为 $sum_2-x\times cnt_2$。

然后我们就只需要用两个树状数组，分别维护每个数字的出现次数与总和就可以了。还有一点需要注意的是，每组数据直接清空会超时，可以每次做完后只把出现过的数清空。具体可以看代码。

### AC Code

```cpp
//If, one day, I finally manage to make my dreams a reality...
//I wonder, will you still be there by my side?
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
#define y1 cyy
#define fi first
#define se second
#define cnt1(x) __builtin_popcount(x)
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lbt(x) (x&(-x))
using namespace std;
int n,m,x,T;
struct BIT{
	int tr[1000005][2];
	void add(int x,int k,int k1){
		for(int i=x;i<=1e6;i+=lbt(i)) tr[i][0]+=k,tr[i][1]+=k1;
	}
	int query(int x){
		int ans=0;
		for(int i=x;i>0;i-=lbt(i)) ans+=tr[i][0];
		return ans;
	}
	int query1(int x){
		int ans=0;
		for(int i=x;i>0;i-=lbt(i)) ans+=tr[i][1];
		return ans;
	}
}bit;
 
vector<int> a[300005];
void solve(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) a[i].clear();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>x;
			a[j].pb(x);
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		for(int j=0;j<a[i].size();j++){
			int tmp=bit.query(a[i][j]-1),cnt=bit.query1(a[i][j]-1);
			ans+=cnt*a[i][j]-tmp;
			tmp=bit.query(1e6)-bit.query(a[i][j]);
			cnt=bit.query1(1e6)-bit.query1(a[i][j]);
			ans+=tmp-cnt*a[i][j];
			bit.add(a[i][j],a[i][j],1);
		}
		for(int j=0;j<a[i].size();j++){
			bit.add(a[i][j],-a[i][j],-1);
		}
	}
	cout<<ans<<endl;
}
signed main(){
	IOS;TIE;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：InversionShadow (赞：1)

## CF1808B Playing in a Casino 题解

### 思路：

题目求的是 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\sum\limits_{k=1}^m|c_{i,j}- c_{j,k}|$。

一列一列单独处理。

将一列的数值排序后，算每个数字和在它前面的数字的贡献。因为一对数只算一次，所以我们考虑到大的数字的时候再算这一对，这样能把外面的绝对值符号去掉。

对于 $a_i$ 需要算 $a_i-a_{i-1}+a_i-a_{i-2}+\dots  + a_i-a_1$，即 $(i-1)\times a_i-sum_{i-1}$。

$sum_i$ 表示前 $i$ 个数之和，用前缀和实现，[代码](https://codeforces.com/contest/1808/submission/203745229)。

坑点：开 `long long`，不要用 `memset`。




---

## 作者：masonpop (赞：0)

直接考虑每一列。显然，设其为 $a_1,a_2,\cdots ,a_n$。则该列的贡献为 $\sum\limits_{1\le i<j\le n}|a_i-a_j|$。

这个东西怎么计算是经典套路了。将其升序排序后，由于任意 $i<j$，$(a_j-a_i)=(a_{i+1}-a_i+a_{i+2}-a_{i+1}+\cdots +a_j-a_{j-1}$。

因此，考虑计算每相邻两数之差的出现次数，统计贡献即可。单组复杂度 $O(nm\log n)$。[代码](https://codeforces.com/contest/1808/submission/219973868)。

---

## 作者：minVan (赞：0)

**题目大意**

在一款卡牌游戏中，有 $n$ 张卡牌，每张卡牌上写着 $m$ 个数字，$n$ 名玩家分别拿到其中的一张卡牌。

所有玩家会成对地进行游戏，例如总共有 $3$ 名玩家时，会进行 $3$ 局游戏：第 $1$ 位玩家对第 $2$ 位玩家、第 $1$ 位玩家对第 $3$ 位玩家、第 $2$ 位玩家对第 $3$ 位玩家。

对于每一场对局，若其中一名玩家的卡牌上的数字为 $a_1,a_2,\cdots a_m$，另一名玩家的卡牌上的数字为 $b_1,b_2,\cdots b_m$，则这场对局的胜者会得到 $\sum\limits^m_{i=1}|a_i-b_i|$ 分。

求所有玩家的总得分。

**解题思路**

直接暴力时间复杂度为 $O(tn^2m)$，肯定过不了。

我们可以将所有人的第 $i$ 张牌从小到大排序，使得对于任意 $i>j$，第 $i$ 个人的这张牌一定比第 $j$ 个人的这张牌大，从而去掉绝对值。

所以对于第 $i$ 个人的第 $j$ 张牌，减它的必定是编号比 $i$ 大的第 $j$ 张牌，它减的必定是编号比 $i$ 小的第 $j$ 张牌，从而第 $i$ 个人的第 $j$ 张牌赢得的应该是 $(i-1)\times C_{i,j}-\sum\limits^{i-1}_{k=1} C_{k,j}$，这里我们又可以用前缀和来优化，所以总时间复杂度为 $O(tnm)$，可以过。

当然用数组空间会爆，所以可以用动态数组。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5;
vector<int> v[N], sum[N];
signed main() {
    int t;
    cin >> t;
    while(t--) {
        int n, m, ans = 0;
        cin >> n >> m;
        for(int i = 1; i <= m; i++) {
            v[i].clear(), sum[i].clear();
        }
        for(int i = 1; i <= m; i++) {
            v[i].push_back(0);
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                int x;
                cin >> x;
                v[j].push_back(x);
            }
        }
        for(int i = 1; i <= m; i++) {
            sort(v[i].begin() + 1, v[i].end());
        }
        for(int i = 1; i <= m; i++) {
            sum[i].push_back(0);
            for(int j = 1; j <= n; j++) {
                sum[i].push_back(sum[i][j - 1] + v[i][j]);
            }
            for(int j = 1; j <= n; j++) {
                ans += (j - 1) * v[i][j] - sum[i][j - 1];
            }
        }
        cout << ans << '\n';
    }
	return 0;
}
```

---

## 作者：Zirnc (赞：0)

暴力。

按照题意，枚举两张卡，$O(n^2m)$。

其实只要计算出每一列中任意两个数之差的绝对值的和就行。为了方便计算，可以先给这一列的所有值排个序，然后一遍扫过去求得答案。$O(mn\log n+mn)$


```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m;
vector<int> c[3000000];
long long sum[3000005];
int main()
{
	ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		
		for (int i = 0; i < m; i++) c[i].clear(), sum[i] = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int t;
				cin >> t;
				c[j].push_back(t);
				sum[j] += t;
			}
		}
		if (n == 1) { cout << 0 << endl; continue; }
		long long ans = 0;
		for (int i = 0; i < m; i++) {
			sort(c[i].begin(), c[i].end());
			for (int j = 0; j < n; j++) {
				sum[i] -= c[i][j];
				ans += sum[i]-(long long)c[i][j]*(long long)(n-j-1);
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

