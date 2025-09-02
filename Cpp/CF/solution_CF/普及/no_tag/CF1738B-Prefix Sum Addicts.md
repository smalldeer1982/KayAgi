# Prefix Sum Addicts

## 题目描述

假设$a_1,a_2,\dots,a_n$是一个长度为$n$的有序整数序列，满足$a_1\leq a_2\leq\dots\leq a_n$

定义$s_i$为$a_1,a_2,\dots,a_i$的前缀和。

$$
s_i=\sum_{k=1}^{i}a_k=a_1+a_2+\dots+a_i
$$

现在已知前缀和的最后$k$项，即$s_{n−k+1},\dots,s_{n−1},s_n$。你的任务是确定这是否可能。

形式上，给定$k$个整数$s_{n−k+1},\dots,s_{n−1},s_n$，任务是检查是否有一个序列$a_1,a_2,\dots,a_n$，该序列满足以下两个条件:
* $a_1 \leq a_2 \dots \leq a_n$
* 对于所有的$n-k+1\leq i\leq n$,满足$s_i=a_1+a_2+\dots+a_i$

## 样例 #1

### 输入

```
4
5 5
1 2 3 4 5
7 4
-6 -5 -3 0
3 3
2 3 4
3 2
3 4```

### 输出

```
Yes
Yes
No
No```

# 题解

## 作者：Alex_Wei (赞：3)

首先若 $k = 1$ 则有解。否则对于 $2\leq i < k$，若 $s_i - s_{i - 1} > s_{i + 1} - s_i$ 则无解。否则 $a_{n - k + 2} = s_2 - s_1$，因此 $a_1\sim a_{n - k + 1}$ 的和不超过 $(n - k + 1) \times (s_2 - s_1)$，若这个值大于 $s_1$ 则无解，否则有解，因为 $a_1\sim a_{n - k + 1}$ 的和没有下界。

[代码](https://codeforces.com/contest/1738/submission/174183678)。

---

## 作者：fqEason (赞：2)

同步发表于[CSDN](https://blog.csdn.net/m0_63954165/article/details/127434613?spm=1001.2014.3001.5501)
## 题意
[CF1738B](https://www.luogu.com.cn/problem/CF1738B)

## 思路：
由于 $a$ 序列是一个不下降子序列，所以这个序列的前缀和之间的差（即元素大小）必定也是不下降的。
考虑记录每相邻两个前缀和的差，开两个数组，一个存原数据，另一个进行排序。
两数组逐位比较，若不相等则不合法。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k;
long long a[100001],b[100001],c[100001];
int main() {
	cin >> t;
	while(t--) {
		bool flag=false;
		cin >> n >> k;
		a[0]=0LL;
		for (int i=1;i<=k;i++) {
			cin >> a[i];
			b[i]=a[i]-a[i-1];//b数组存有序前缀和差
			c[i]=a[i]-a[i-1];//c数组存原数据
		}
		if (n!=k) b[1]=c[1]=ceil(a[1]*1.0/(n-k+1));//此处要注意，若没给出全序列的前缀和，则要特判前n-k个元素能否构成不下降序列，此处利用贪心思想，
		//将前n-k项全设成1，若前缀和依然不合法，则输出"NO"。
		sort(b+1,b+k+1);
		for (int i=1;i<=k;i++) {
			if (c[i]!=b[i]) {//逐位比较
				cout << "NO\n";
				flag=true;
				break;
			}
		}
		if (!flag) cout << "YES\n";
	}
	return 0;
}
```

---

## 作者：Kindershiuo (赞：0)

# 解题思路
我的思路就是先根据给前缀和把数组的倒数 $k-1$ 项预处理出来，倒数第 $k$ 项也就是正数第 $n-k+1$ 我们不能预处理出来，因为数组的前面 $n-k+1$ 我们要确保是递增的，所以我们根据我们刚刚所剩的那个前 $n-k+1$ 项的和去处理前面 $n-k+1$ 个元素，这里我们处理的话是有点技巧的，我们要贪心的去处理，也就是平均分配给这 $n-k+1$ 项，然后肯定不会很理想的能全部分均匀，会有那么几项有波动，这个时候我们要再考虑，如果前 $n-k+1$ 项的和是负数，我们的波动就要放在前几项，因为是负数，也就是说后面的数字越大加上负号就会越小，而如果前 $n-k+1$ 项的和是正数，波动就是正常放在后面几项就行。如果我们都这样很贪心的去考虑了，但是这个数组还是不能满足单调不减，那就说明无解。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
#define endl '\n'
int T;
int a[N];
int s[N];

void solve() {
	int n,k;
	cin>>n>>k;
	for(int i=n-k+1;i<=n;i++)cin>>s[i];
	if(k==1){cout<<"YES"<<endl;return;}
	for(int i=n;i>=n-k+2;i--){
		a[i]=s[i]-s[i-1];
	}
	int sum=s[n-k+1];
	int t=0;
	if(sum<0){
		if(a[n-k+2]>0){
			for(int i=n-k+1;i>=1;i--){
				if(i==1){
					a[i]=sum;
				}else{
					a[i]=t;
				}
			}
		}else{
			int t=sum/(n-k+1);
			int d=sum%(n-k+1);
			for(int i=1;i<=n-k+1;i++){
				a[i]=t;
			}
			d=-d;
			for(int i=1;i<=n-k+1;i++){
				if(d==0)break;
				a[i]--;
				d--;
			}
		}
	}else{
		if(sum<a[n-k]){
			a[n-k+1]=sum;
			for(int i=1;i<=n-k;i++){
				a[i]=0;
			}
		}else{
			int t=sum/(n-k+1);
			int d=sum%(n-k+1);
			for(int i=1;i<=n-k+1;i++){
				a[i]=t;
			}
			for(int i=n-k+1;i>=1;i--){
				if(d==0)break;
				a[i]++;
				d--;
			}
		}
	}
	int f=0;
	for(int i=2;i<=n;i++){
		if(a[i]<a[i-1]){
			f=1;
			break;
		}
	}
	if(!f)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	for(int i=1;i<=n;i++){
		s[i]=0;
		a[i]=0;
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：atomic_int (赞：0)

## 题意：
题目翻译中已有。

## 分析：
- 如果 $k=1$ 一定存在序列 $a$。
- 如果存在序列 $a$，设 $s$ 每两个数的差为 $d$，$d_i=s_i-s_{i-1}(2 \leq i \leq k)$，就有 $d_i \leq d_{i+1}(2 \leq i < k)$。
- 对于 $n-k+1$ 的部分，设 $a_i$ 为 $d_2$，因为前面提到 $d_i \leq d_{i+1}(2 \leq i < k)$，也就是说 $d$ 是不下降的，那么如果 $a_i \times (n-k+1) \geq s_1$ 存在序列 $a$，否则不存在。

## 代码：
```cpp
inline void solve() {
    int n, k; cin >> n >> k;
    vector<int> s(k + 1), d(k + 1);
    for (int i = 1; i <= k; i ++) {
        cin >> s[i];
        d[i] = s[i] - s[i - 1];
    }
    if (k == 1) {
        cout << "Yes\n";
        return ;
    }
    for (int i = 2; i < k; i ++) {
        if (d[i] > d[i + 1]) {
            cout << "No\n";
            return ;
        }
    }
    if (d[2] * (n - k + 1) >= s[1]) {
        cout << "Yes\n";
    }
    else {
        cout << "No\n";
    }
}
```

---

## 作者：晨曦墨凝 (赞：0)

### 题目大意
给你序列 $a$ 的连续的前缀和 $s$ 的一部分，让你判断序列 $a$ 是否是一个不下降子序列。

### 思路
设 $l = n - k + 1$，$r = n$。
1. $\forall i \in [l + 1,r]$，$a_i = s_i - s_{i - 1}$，然后判断是否不下降即可；
2. 对于剩下部分，考虑贪心，因为使序列不下降即可，那么就索性令 $\forall i \in [2,l]$，$a_i = a_{l + 1}$，则 $a_1 = s_l - a_{l + 1} \cdot (l - 1)$，然后判断 $a_1$ 是否小于等于 $a_{l+1}$ 即可。

**需要注意的地方**
1. $k = 1$ 时必有解；
2. 不要忘了开 long long。

```
#include <iostream>
#include <cstdio>
#define MAXN 100005
using namespace std;
typedef long long ll;

int t, n, k, l, r;
ll a[MAXN], s[MAXN];
int aye;

int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

void init()
{
    aye = 1;
    n = read(), k = read();
    l = n - k + 1, r = n;
    for (int i = l; i <= r; ++i)
        s[i] = read();
}

void solve()
{
    for (int i = l + 1; i <= r; ++i)
        a[i] = s[i] - s[i - 1];
    a[1] = s[l] - a[l + 1] * (l - 1);
    if (a[1] > a[l + 1]) aye = 0;
    for (int i = l + 2; i <= r && aye; ++i)
        if (a[i] < a[i - 1])
            aye = 0;
    if (aye || k == 1) printf("Yes\n");
    else printf("No\n");
}

int main()
{
    t = read();
    while (t--)
    {
        init();
        solve();
    }
    return 0;
}
```


---

## 作者：Land_ER (赞：0)

## 题意简述
- 有一数列 $a_1, a_2, \dots, a_n$，其中 $1 \leqslant n \leqslant 10^5$。
- 另有一数列 $s_1, s_2, \dots, s_n$，其中 $s_i = \sum_{d=1}^i a_d$，也即数列 $a$ 的前缀和。
- 给定 $s_{n-k+1}, \dots, s_n$ 共 $k$ 项，确定是否存在不减的数列 $a$，即 $a_1 \leqslant a_2 \leqslant \dots \leqslant a_n$，满足前 $i$ 项的和为 $s_i$。

## 解题思路
考虑数列 $a$ 单调不减在 $s$ 中如何体现。

首先，可以得出 $a_i = s_i - s_{i-1}$。我们可以计算出 $a_{n-k+2}, \dots, a_n$，若其不满足单调不减，则不存在符合要求的数列 $a$。

其次，考虑样例四的情况：

```
Input
3 2
3 4

Output
No
```

由数列 $a$ 单调不减，可以得出 $a_1, \dots, a_{n-k+1}$ 每项最大值为 $a_{n-k+2}$。若前 $n-k+1$ 项均取最大值，而其前缀和仍小于 $s_{n-k+1}$，则不存在符合要求的数列 $a$。

另外，$k=1$ 时总存在符合要求的数列 $a$，需要特判。

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long int

vector<int> s;

void solve(void) {
    int n, k;
    cin >> n >> k;
    s.clear();
    for(int i = 0, ss; i < k; ++ i) {
        cin >> ss;
        s.push_back(ss);
    }

    if(k == 1) {
        puts("YES");
        return;
    }

    for(int i = 2; i < k; ++ i) {
        if(s[i] - s[i-1] < s[i-1] - s[i-2]) {
            puts("NO");
            return;
        }
    }

    if((n - k + 1ll) * (s[1] - s[0]) >= s[0])
        puts("YES");
    else
        puts("NO");

    return;
}

#undef int

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
```

---

