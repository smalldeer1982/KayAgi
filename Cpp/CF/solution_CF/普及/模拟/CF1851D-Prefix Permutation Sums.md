# Prefix Permutation Sums

## 题目描述

Your friends have an array of $ n $ elements, calculated its array of prefix sums and passed it to you, accidentally losing one element during the transfer. Your task is to find out if the given array can matches permutation.

A permutation of $ n $ elements is an array of $ n $ numbers from $ 1 $ to $ n $ such that each number occurs exactly one times in it.

The array of prefix sums of the array $ a $ — is such an array $ b $ that $ b_i = \sum_{j=1}^i a_j, 1 \le i \le n $ .

For example, the original permutation was $ [1, 5, 2, 4, 3] $ . Its array of prefix sums — $ [1, 6, 8, 12, 15] $ . Having lost one element, you can get, for example, arrays $ [6, 8, 12, 15] $ or $ [1, 6, 8, 15] $ .

It can also be shown that the array $ [1, 2, 100] $ does not correspond to any permutation.

## 说明/提示

In the fourth example, for example, the permutation $ [1, 2, 3, 4] $ is suitable. In the fifth example, for example, the permutation $ [2, 1] $ is suitable. In the seventh example, for example, the permutation $ [1, 2, 4, 3] $ is suitable.

## 样例 #1

### 输入

```
12
5
6 8 12 15
5
1 6 8 15
4
1 2 100
4
1 3 6
2
2
3
1 2
4
3 7 10
5
5 44 46 50
4
1 9 10
5
13 21 36 42
5
1 2 3 1000000000000000000
9
9 11 12 20 25 28 30 33```

### 输出

```
YES
YES
NO
YES
YES
NO
YES
NO
NO
NO
NO
NO```

# 题解

## 作者：Otue (赞：13)

感觉大家都写的很复杂。

我赛时吃了一车罚时一不小心就过了，本以为会被 hack 结果很稳？

# 思路
考虑找规律。给一个序列 $a=[4,3,1,2,5]$，前缀和 $sum=[4,7,8,10,15]$。

* 把 $sum$ 第一个数去掉，得到 $[7,8,10,15]$，差分一下 $[7,1,2,5]$。

* 把 $sum$ 第二个数去掉，得到 $[4,8,10,15]$，差分一下 $[4,4,2,5]$。

* 把 $sum$ 第三个数去掉，得到 $[4,7,10,15]$，差分一下 $[4,3,3,5]$。

* 把 $sum$ 第四个数去掉，得到 $[4,7,8,15]$，差分一下 $[4,3,1,7]$。

* 把 $sum$ 第五个数去掉，得到 $[4,7,8,10]$，差分一下 $[4,3,1,2]$。

容易发现前四种情况，$1\sim n$ 的数总有 $2$ 个没有在差分数组中出现，且差分数组和为 $\dfrac{n\times (n+1)}{2}$。证明不难。

对于第五种情况，$1\sim n$ 的数只有 $1$ 个没有出现。那么我们用 $\dfrac{n\times (n+1)}{2}$ 减去差分数组的和（记为 $t$），$t$ 就等于那个没有出现的数。直接判断差值 $t$ 是否满足 $1\leq t\leq n$ 即可。

## 代码
```c++
// 赛时代码，括号有点多，代码有点乱，见谅
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;

int t, n, a[N], b[N];
map<int, int> vis;

signed main() {
	cin >> t;
	while (t--) {
		vis.clear();
		cin >> n;
		int maxn = 0, num = 0;
		for (int i = 1; i <= n - 1; i++) cin >> a[i], b[i] = a[i] - a[i - 1], num += b[i];
		int tot = 0;	
		for (int i = 1; i <= n - 1; i++) {
			vis[b[i]]++;
		}
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) tot++; // tot为1~n查分数组没有出现的数字个数
		}
		int t = n * (n + 1) / 2;
		if (tot <= 2 && (((t == num) && tot == 2) || (((((t - num) >= 1 && (t - num) <= n)) && tot == 1)))) puts("Yes");
		else puts("No");
	}
}
```

---

## 作者：Wf_yjqd (赞：3)

就是这题被 hack 了。

没开 long long 啊。

------------

考虑缺少的那个数的位置。

分为末尾和其他两种情况。

当缺少的数在末尾，如果成立，一定是排列中没出现的数。

如果求差分后没出现的数超过 $1$ 个，那就不行了。

如果缺少的不在末尾，那一定是差分数组中缺少的两个数的和。

否则不成立。

整理下思路，求差分数组标记每个数出现过没有，然后分讨就好。

复杂度应为 $\operatorname{O}(n)$，然后我用了 set 硬整成了 $\operatorname{O}(n\log{n})$。

------------

放个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e5+84;
ll T,n,a[maxn];
set<ll> Set;
bitset<maxn> vis;
vector<int> vec;
inline bool check(){
    if(vec.size()==1)
        return !vis[vec[0]];
    if(vec.size()==3)
        return vec[0]+vec[1]==vec[2]&&!vis[vec[0]]&&!vis[vec[1]];
    return 0;
}
int main(){
    scanf("%lld",&T);
    while(T--){
        vis.reset();
        Set.clear();
        vec.clear();
        scanf("%lld",&n);
        for(ll i=1;i<=n;i++)
            Set.insert(i);
        for(ll i=1;i<n;i++){
            scanf("%lld",&a[i]);
            if(Set.find(a[i]-a[i-1])==Set.end())
                vec.push_back(a[i]-a[i-1]);
            else{
                vis[a[i]-a[i-1]]=1;
                Set.erase(a[i]-a[i-1]);
            }
        }
        for(auto it:Set)
            vec.push_back(it);
        sort(vec.begin(),vec.end());
        puts(check()?"Yes":"No");
    }
    return 0;
}
```


---

## 作者：lwx20211103 (赞：2)

## 题目意思

给你一个长度为 $n - 1$ 的数组，是否能找出一个长度为 $n$ 的排列，求出这个排列的前缀和，去掉前缀和数组的任意一个元素之后和原来的数组相等。

例如第一组数据的 $[6, 8, 12, 15]$，可以是排列 $[1, 5, 2, 4, 3]$ 的前缀和 $[1, 6, 8, 12, 15]$ 去掉元素 $1$。

想必大家都知道长度为 $n$ 的排列与前缀和差分的概念吧。这里就不赘述了。

## 题目分析

先观察数据范围，$t \leq 10^4$，$n \leq 2 \times 10^5$，时限 $3$ 秒钟。时间复杂度只能有 $\Theta(n)$，还必须有常数优化。有人曾经测过 cf 的评测机情况好的时候**每秒能跑 $8 \times 10^9$**，可以据此测算。

前缀和的所谓的逆运算就是差分，在这题差分可以求出原来数组的一部分，但是差分求出来的数组并不完整。

我们可以分类讨论。当然，我们可以观察一下数组的性质。


------------
特判部分：我们知道一个长度为 $n$ 的排列，数组的所有数字之和是 $\frac{n(n + 1)}{2}$，所以检查一遍数组，碰到大于这个数字的直接结束本次循环并输出 `NO`。


------------

第一种情况，差分后存在一个大于 $n$ 的数字。例如 $[6, 8, 12, 15]$ 还原成 $[6, 2, 4, 3]$，用眼睛看就知道 $6$ 能拆成 $1 + 5$，刚好凑完。

我们开一个映射表，记录每次差分后的数字，长度是 $n$。找出没有的数字与大于 $n$ 的数字 $k$。这时候判断没出现的数字之和与 $k$ 是否相等即可。


------------
第二种情况，差分后存在两个相同的数字，如 $[3, 7, 10]$ 还原成 $[3, 4, 3]$，也开一个映射表，记录每次差分后的数字与出现超过两次的数字 $k$，找出没有的数字判断它们的和是否与 $k$相等。


------------
第三种情况，既没有比 $n$ 大的数字也没有出现超过两次的数字，这个时候就可以直接输出 `YES`，显然，因为如果有不合规的排列，里面有过大或者重复的数字，不可能形成这种情况。


------------


最后的最后，一定要记得常数优化，映射表的大小可能会达到 $2n - 2$ 的地步，放在循环内容易爆炸，每次用完都得清空，别的可以不用清空。`memset` 的时间复杂度一般是 $\Theta(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define p_b push_back
#define ft first
#define nd second
#define pii pair<int, int>
#define pll pair<long long, long long>

using namespace std;

typedef long long ll;
ll mp[444444], nums[222222], pre[222222];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		ll n, temp;
		cin >> n;
		temp = n;
		bool fixed = false;//记录是否是第三种情况
		bool flag = true;
		memset(mp, 0, sizeof(mp));//清空
		nums[0] = 0;
		for (int i = 1; i < n; i++) 
		{
			cin >> nums[i];
			if (nums[i] > (n * (n + 1) / 2)) 
				flag = false; //特判
		}
		if (!flag) {cout << "NO" << "\n"; continue;}
		for (int i = 1; i < n; i++) 
		{
			pre[i] = (nums[i] - nums[i - 1]);//差分
			mp[nums[i] - nums[i - 1]]++;//记录
			if ((nums[i] - nums[i - 1]) > n) 
			{
				temp = nums[i] - nums[i - 1];fixed = true;
			}
		}
		ll k = 0;
		for (int i = 1; i <= n; i++)
		{
			if (!mp[i])
				k += i;
			if (mp[i] >= 2) {temp = i;fixed = true;}
		}
		if (!fixed) {cout << "YES" << "\n";continue;}
		if (k == temp) cout << "YES" << "\n";
		else cout << "NO" << "\n"; 
	}
	return 0;
}
```

## 其他

这次代码包括清空数组进行了四次循环，$n$ 是 $2 \times 10^5$，在乘上 $t$ 就是 $8 \times 10^9$，而我的提交记录显示只用了不到一秒，可以 cf 的评测机之快。


---

## 作者：xzyg (赞：2)

题意：

```
你的朋友有一个 n 个元素的数组，计算它的前缀和数组并传递给你，
在传递过程中不小心丢失了一个元素。
你的任务是找出给定的数组是否能匹配 1~n 的一个排列。
```

把数组差分一下，记录已经出现了 $ 1 \sim n $ 排列中的哪些数。若在记录中发现差分出来的数大于 $ n $，或之前已经出现过这个数，就记录下大小。

统计完后，扫一遍桶，找出出现次数为 $ 0 $ 的两个数（前缀和少一个元素，原数组少两个元素并增加一个元素等于两个元素和），判断这两个数相加是否为上一步找出来的数即可。

**注意特判。**

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 200010
using namespace std;
 
ll read(){
	char ch=getchar();
	ll s=0, w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w; 
}
 
ll a[MAXN];
ll b[MAXN];
bool vis[MAXN];
 
int main(){
	ll T = read();
	
	while(T--){
		ll n;
		n = read();
		
		ll pos = 0;
		
		for(ll i = 1; i <= 2 * n; i++){
			vis[i] = false;
		}
		
		bool f = true;
		
		for(ll i = 1; i <= n-1; i++){
			a[i] = read();
		}
		
		for(ll i = 1; i <= n-1; i++){
			if(a[i] > n * (n+1) / 2){
				f = false;
				break;
			}
			b[i] = a[i] - a[i-1];
			if(vis[b[i]] || b[i] > n){
				if(pos){
					f = false;
					break;
				}
				pos = b[i];
			}
			vis[b[i]] = true;
		}
		
		if(!f){
			cout << "NO\n";
			continue;
		}
		
		if(pos == 0){
			cout << "YES\n";
			continue;
		} 
		
		ll pos1 = 0, pos2 = 0;
		
		for(ll i = 1; i <= n; i++){
			if(!vis[i]){
				if(pos1 == 0){
					pos1 = i;
				}else{
					pos2 = i;
				}
			}
		}
		
		cout << (pos1 + pos2 == pos ? "YES" : "NO") << endl;
		
	}
	return 0;
}
```


---

## 作者：Lucky_Cloud (赞：1)

貌似我与大家后面的判断不太一样？

### 分析

由于前缀和的定义，我们可以知道他们的差分便是原数组，下面的差分数组，是题目给出的前缀和的差分。
 
于是，我们可以用个桶将 $1 \sim N$ 出现的数存起来。

随后判断每个数是否出现过，若没出现过，使计数器加一。

这里我们假设输出 `YES`。因为前缀和少了一个数，那么我们得到的差分数组则会比原数组少一个元素。如果 $cnt = 2$，则差分数组相较于原数组会有一个不同的元素，而这一个元素便是原数组在差分数组中，没有出现的两个元素的和。如果 $cnt = 1$，那么一定是前缀和的最后一个数加上差分数组缺少的那一个数等于 $1 \sim N$ 之和。

这个时候我们分三种情况：

1. 如果 $cnt > 2$，我们根据定义可以得出是不可行的，直接输出 `NO`。
2. 如果 $cnt = 2$，我们则需判断前缀和数组中最后一个元素是否是 $1 \sim N$ 的和，若相等则输出 `YES`，否则 `NO`。
3. 如果 $cnt = 1$，我们则判断前缀和的最后一个数加上差分数组缺少的那一个数是否等于 $1 \sim N$ 之和。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define vint vector<int>
#define ull unsigned ll 
using namespace std;
 
const int N = 4e5 + 5;
ll t, n, c[N], pre, now;
 
int main() {
	ios::sync_with_stdio(0);
    cin >> t;
    while (t--) {
        pre = 0;
        cin >> n;
        // ll sum = 0;
        memset(c, 0, sizeof c); 
        for (int i = 1; i < n; i++) {
            cin >> now;
            if (now - pre <= 4e5) c[now - pre]++;//标记数已经出现过
            pre = now;
        }
        int cnt = 0, x[N] = {0};//x 数组保存差分数组缺少的数
        for (int i = 1; i <= n; i++) {
            if (!c[i]) {
                cnt++;
                x[cnt] = i;
            }
        }
        if (cnt > 2) puts("NO");
        else if (cnt == 1) {
            if (x[1] + now == (1 + n) * n / 2) puts("YES");
            else puts("NO");
        }
        else {
            if (now != (1 + n) * n / 2) {
                puts("NO");
                continue;
            }
            else {
                puts("YES");
            }
        }
        
    }
    return -1;
}
```

---

## 作者：Leaper_lyc (赞：1)

一道分类讨论的好题。
## 题目简意
给定长为 $n-1$ 的序列 $a$，问能否在任意一个位置添加一个数 $x$ 使得新的序列为一个排列的前缀和。

## 分析
先计算原数组的差分数组 $b$，然后开个桶记录每个数出现次数。

不合法的有以下情况：
- 存在至少 $2$ 个数大于 $n$。
- 存在一个数字出现了 $3$ 次及以上，或者有 $2$ 个数字出现了 $2$ 次及以上。

合法情况：
- 如果数列 $b$ 中有大于 $n$ 的数字，那么判断数 $n$ 是否等于没有出现过的数字和。
- 否则，如果数列 $b$ 所有数字都只出现一次且每个数字都在 $n$ 以内，那么合法。
- 如果有一个数字出现 $2$ 且等于没有出现的数字的和，那么合法。

## 代码实现：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define int long long
#define maxn 500005

int T, n, a[maxn], m, k, h, b[maxn], t[maxn];

bool solve(){
    int s = 0;
    memset(t, 0, sizeof(t));
    for (int i = 1; i < n; i++){
        b[i] = a[i] - a[i-1];
        if (b[i] == 0) return false;
        else if (b[i] <= n) t[b[i]] ++;
        else{
            if (s) return false;
            s = b[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        if (t[i] > 1) {
            if (s) return false;
            s = i;
        }
        if (t[i] >= 3) return false;
    }
    if (!s) for (int i = 1; i <= n; i++) if (!t[i]) s = i;
    for (int i = 1; i <= n; i++) if (!t[i]) s -= i;
    return (s == 0) ? true : false;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i < n; i++) cin >> a[i];
        cout << (solve() ? "YES\n" : "NO\n");
    }
}
```

---

## 作者：_sunkuangzheng_ (赞：1)

**【题目大意】**

给定长为 $n-1$ 的序列 $a$，问能否在任意一个位置添加一个数 $x$ 使得新的序列为一个排列的前缀和。

**【题目分析】**

分讨题。先对原数组相邻项相减得到数组 $b$，然后开个桶记录每个数出现次数。注意到以下情况是**不合法**的：

- 有 $\ge2$ 个大于 $n$ 的数字。

- 有一个数字出现了 $3$ 次及以上或者有两个出现了 $\ge 2$ 次的数字。

先把它们判掉，然后：

- 如果数列 $b$ 中有大于 $n$ 的数字，那么判断数 $n$ 是否等于没有出现过的数字和。

- 否则，如果数列 $b$ 所有数字都只出现一次且在 $n$ 以内，那么直接合法。

- 如果有一个数字出现两次且等于没有出现的数字的和，那么合法。

据此写代码即可。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[500005],m,k,h,b[500005],c[500005];
bool work(){
    int s = 0;
    for(int i = 1;i <= n;i ++) c[i] = 0;
    for(int i = 1;i < n;i ++){
        b[i] = a[i] - a[i-1];
        if(b[i] == 0) return 0;
        else if(b[i] <= n) c[b[i]] ++;
        else{
            if(s) return 0;
            s = b[i];
        }
    }
    for(int i = 1;i <= n;i ++) {if(c[i] > 1) {if(s) return 0;s = i;} if(c[i] >= 3) return 0;}
    if(!s) for(int i = 1;i <= n;i ++) if(!c[i]) s = i;
    for(int i = 1;i <= n;i ++) if(!c[i]) s -= i;
    return s == 0;
}
signed main(){
    cin >> t;
    while(t --){
        cin >> n;
        for(int i = 1;i <= n-1;i ++) cin >> a[i];
        cout << (work() ? "YES\n" : "NO\n");
    }
    return 0;
}
```

---

## 作者：sz_jinzikai (赞：0)

[洛谷传送门](/problem/CF1851D) &[CF 传送门](//codeforces.com/problemset/problem/1851/D)
# 题目大意
给定前缀和数组，但是少了一个数，即只剩 $n-1$ 个数了，问如果这个数组没缺少，是否可能为一个长度为 $n$ 的排列的前缀和。
# 思路
遇到前缀和还原，我们肯定要差分一下（即前缀和逆操作）。我们看看样例中第 $4$ 组数据，发现它只少了一个元素，这里我们特判就可以了。

其他情况下，我们发现肯定是少了两个元素和多了一个 $>n$ 或已经出现过的奇怪数字，我们只要看看这两个少了的元素之和是否等于这个奇怪数字即可。
# 代码
```cpp
//CF1851D
# include <bits/stdc++.h> //万能头 
using namespace std;
typedef long long ll; //long long 可简写为 ll
ll t, n, a[200005], x, y, temp; //不开 long long 见祖宗
bool vis[200005], flag;
bool solve () {
	cin >> n;
	for (ll i = 1; i < n; ++ i)
		cin >> a[i], vis[i] = 0; //别忘记清空！
	vis[n] = 0;
	for (ll i = n - 1; i; -- i)
		a[i] -= a[i - 1]; //差分
	x = y = flag = 0; //多组数据要清空
	for (ll i = 1; i < n; ++ i)
		if (a[i] <= 0) //不合法
			return 0;
		else if (a[i] > n || vis[a[i]]) {
			if (flag) //已经有不合法过了，最多只允许不合法一次
				return 0;
			temp = a[i], flag = 1;
		} else
			vis[a[i]] = 1; //标记掉
	for (ll i = 1; i <= n; ++ i)
		if (! vis[i]) //没来过
			if (x)
				y = i;
			else
				x = i;
	return x + y == temp || ! y; //判断是否合法
}
int main () {
	cin >> t;
	while (t --) //多组数据通用写法
		cout << (solve () ? "YES\n" : "NO\n");
	return 0; //结束程序
}
```

---

## 作者：NBest (赞：0)

## 题意
给你一个前缀和数组，但是缺少了一个数值，问原数组能否是 $n$ 的排列。

## 思路
首先遇到前缀和数组当然得先给它差分一下得到一个序列了，我们看到样例 $4$，发现当少的是最后一个时，可以得到一个 $n-1$ 的排列，这里特判即可。

那其他情况呢？在差分之后我们会发现 $[1,n]$ 至少少了两个值，可能会出现一个在 $[1,n]$ 中重复的，也可能出现 $\le n$ 的，但是因为前缀和最后一个值不变，所以原序列的和也不变，故少的两个值必然相加等于那个不正常的值。

相应的，当少的数超过两个或者不正常的数不止一个，那么就不可能组成一个排列。

细节很多，结合代码理解更佳。
## $Code$
```cpp
int T,n;
ll a[200005];
bool pd[200005];
bool check(){
    ll los1=0,los2=0,mor=0;//los 少的数,mor是不正常的数
    for(int i=n-1;i;--i){
        a[i]-=a[i-1];
        if(a[i]>n||pd[a[i]]){
            if(mor)return 0;//不止一个不正常
            mor=a[i];
            continue;
        }
        pd[a[i]]=1;
    }
    for(int i=1;i<=n;i++){
        if(!pd[i]){
            if(!los1)los1=i;
            else if(!los2)los2=i;
            else return 0;//少的不止两个
        }
    }
    if(!los2&&!mor)return 1;//少的是最后一个值的情况
    if(los1+los2!=mor)return 0;//不相同也不行
    return 1;
}
int main(){
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<n;i++){
            a[i]=read();
            pd[i]=0;
        }
        pd[n]=0;
        if(check())puts("YES");
        else puts("NO");
    }
}
```

---

## 作者：Zkl21 (赞：0)

一道很有意思的思维 + 分类讨论题。
## 题目大意
给定一个长度为 $n-1$ 的序列，求是否存在一个长度为 $n$ 的排列，使得该排列的前缀和序列删去一项后与给定序列相同。
## 思路
首先通过差分可以求出每一项的值。

我们尝试找到丢失的一项。差分后记录一下每一项，如果有一项大于 $n$，显然这一项是不合法的，如果有一项出现了两次，说明其中一项是不合法的。如果有两项是不合法的，说明一定没有解。

如果丢失的是最后一项，说明前面全是确定的值，我们只要检验前面所有项是否合法即可。

如果丢失的不是最后一项，那么如果给定序列合法，由于某一项是丢失的，因此差分后其中有一项一定是原来排列中的两个数相加得到的。我们可以维护一个 sum，每次找到合法解后更新 sum，最后判断剩下的两项和最后的 sum 是否相等即可。

具体还是有很多细节的，看看代码也许可以加深理解。
## 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=2e5+10;
typedef long long ll;
int n,cnt[N];//cnt记录每一个数出现的次数
ll a[N];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		memset(cnt,0,sizeof cnt);//多测不清空，爆零两行泪
		ll sum=(1+n)*(ll)n/2,flag=0;//sum是排列的所有数的和
		for(int i=1;i<n;i++)cin>>a[i];
		for(int i=n-1;i;i--)a[i]-=a[i-1];//差分求原值
		for(int i=1;i<n;i++)
		{
			if(a[i]>n||cnt[a[i]])//当前位不合法
			{
				if(flag>0)//找到两项不合法的解，说明无解
				{
					flag=-1;
					break;
				}
				flag=a[i];//否则记录一下当前数的值
				continue;
			}
			sum-=a[i];//对于合法的解更新一下 sum
			cnt[a[i]]++;//记录当前数出现的次数+1
		}
		if(flag==-1)//无解
		{
			puts("NO");
			continue;
		}
		if(!flag)//没有找到不合法的情况，说明丢失的是最后一项，并且前面的所有项都是合法的，一定有解
		{
			puts("YES");
			continue;
		}
		puts(sum==flag?"YES":"NO");//根据sum判断是否有解
	}	
	return 0;
}
```

---

## 作者：_Only_this (赞：0)

### CF1851D Prefix Permutation Sums 题解

------------

就是这题，赛时因为分支结构没写好挂了，掉大分。。

------------

给定缺少一个元素的前缀和数组，问你补上一个元素后原数组是否能成为一个排列。

------------

这题就是个结论，首先将前缀和数组差分，然后分讨一下。

丢失的元素一种在末尾，一种不在末尾。

将差分数组和排列中相同的数约掉。

在末尾的，如果成立，差分数组剩余的数在排列中肯定没出现过，但如果有多个没出现过，那就说明不可能。

不在末尾的，如果成立，差分数组剩余的数一定是排列中剩余两个数的和，否则就不成立。

贴个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 2e5+5;
ll T,n;
ll a[maxn],d[maxn];
inline bool Check(){
	set<ll>A;
	vector<ll>vec;
	map<ll,ll>vis,mp;
	for(ll i=1;i<=n;i++)
		A.insert(i);
	for(ll i=1;i<n;i++){
		if(A.find(d[i])!=A.end()){
			A.erase(d[i]),vis[d[i]]=1;
		}
		else{
			vec.push_back(d[i]);
		}
	}
	for(auto it: A){
		vec.push_back(it);
	}
	sort(vec.begin(),vec.end());
	if(vec.size()==3){
		if(vec[0]+vec[1]==vec[2] && !vis[vec[0]] && !vis[vec[1]])
			return 1;
	}
	if(vec.size()==1 && !vis[vec[0]])
		return 1;
	else
		return 0;
}
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(ll i=1;i<n;i++)
			scanf("%lld",&a[i]),d[i]=a[i]-a[i-1];
		printf("%s\n",(Check()) ? "Yes" : "No");
	}
	return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1851D)   
思路好想，但是代码量不少。      
## 题意
我们定义“前缀和排列”为：如果 $a$ 为一个长度为 $n$ 的排列，那么如果数列 $b$ 满足 $\forall i\in[1,n]$ 有 $b_i=\sum\limits^i_{j=1}a_j$，那么我们说 $b$ 是 $a$ 的“前缀和排列”。   
现在有一个长度为 $n-1$ 的数列 $a$，$a$ 是一个前缀和数列且丢失了其中一项。求每次的 $a$ 能否通过补全成为完整的“前缀和排列”。    
## 解法
我们定义 $a$ 的差分数组为 $b$。     
我们易知，一个普通的“前缀和排列”的差分数组必然就是这个排列。   
所以我们建一个桶来记录 $b$ 中所有元素是否出现过。这扫一遍即可（下面设扫到 $i$），但是有一些特殊情况：    
- 如果 $b_i$ 已经出现过，那么这个 $b_i$ 应为两个数的和，把它记录下来。    
- 如果 $b_i$ 不属于 $[1,n]$ 的范围，那么它也是两个数的和，也把它记录下来。     
- 如果记录了多于一个数，那么就不能通过补全得到“前缀和排列”。   

那么我们最后只要判断记录的数字是否等于丢下的两个数字即可。这里有特殊情况：没有记录的数字。这种情况我们需要判断桶里的数是否是正好 $n-1$ 个，如果是，就是正确的，反之为否。         
时间复杂度为 $O(N),N=\sum\limits^t_{i=1}n_i$，可以通过。    
[CODE](https://www.luogu.com.cn/paste/70jcr5zj)

---

## 作者：MornStar (赞：0)

# CF1851D Prefix Permutation Sums 题解

## 题目大意

$T$ 组数据。

每组数据给定一个 $n$ 和一个长度为 $n-1$ 的序列 $a$。

问是否有某个长度为 $n$ 的排列，将其前缀和组成的序列删去一项，恰好与 $a$ 相同？

## 思路

首先将 $0$ 加在序列 $a$ 前面，在用序列里的后一项减去前一项，得到 $n-1$ 个差。

如果序列 $a$ 是某个排列的前缀和删去一项，那么这 $n-1$ 个差中一定有 $n-2$ 个数在原排列之中，而剩的一个数一定就是原排列中剩下两个之和。

我们在找到一个差大于 $n$ 或是已经出现过时，记录下它，但一旦这种数出现第二次，那么序列 $a$ 就不符合要求。

最后遍历 $1$ 到 $n$ ，看看多出来的数是不是没有出现过的两个数之和就行了。

## code

```cpp
//by MornStar
#include<bits/stdc++.h>
using namespace std;
long long a[200005];
int t[200005];
int T,n,flag,tmp,ff;
int main(){
	cin>>T;
	while(T--){
		memset(t,0,sizeof(t));
		flag=tmp=ff=0;
		cin>>n;
		for(int i=1;i<n;i++)	cin>>a[i];
		for(int i=0;i<n-1;i++){
			if(a[i+1]-a[i]>=n*2){
				cout<<"no\n";
				flag=1;//因为 1 到 n 的排列中两数加起来不可能大于 n*2。
				break; //所以这时候就已经不满足要求了。
			}else{
				if(a[i+1]-a[i]>n||t[a[i+1]-a[i]]){
					if(ff){
						cout<<"no\n";
						flag=1;
						break;
					}else{
						ff=1;
						tmp=a[i+1]-a[i];
					}
				}else{
					t[a[i+1]-a[i]]=1;
				}
			}
		}
		if(ff){
			for(int i=1;i<=n;i++){
				if(!t[i])	tmp-=i;
			}
		}
		if(!flag){
			if(tmp!=0)	cout<<"no\n";
			else	cout<<"yes\n";
		}
	}
}

```


---

