# Cherry Bomb

## 题目描述

我们称两个长度均为 $n$ 的整数数组 $a$ 和 $b$ 是**互补的**，当且仅当存在一个整数 $x$，使得对于所有 $1 \le i \le n$，$a_i+b_i=x$。例如数组 $a=[2,1,4]$ 和 $b=[3,4,1]$ 是互补的，因为对于所有 $1 \le i \le 3$，$a_i+b_i$ 都等于 $5$。而数组 $a=[1,3]$ 和 $b=[2,1]$ 则不是互补的。

Cow the Nerd 觉得任何人都对数学感兴趣，所以他给了 Cherry Bomb 两个长度均为 $n$ 的整数数组 $a$ 和 $b$，其中元素均为非负整数且不大于 $k$。

但是 Cherry Bomb 不小心弄丢了 $b$ 中的一些数，这些数以 $-1$ 表示。请求出满足以下要求的可能的 $b$ 数组的数量：
- 数组 $a$ 和数组 $b$ 互补。
- $b$ 中的元素均为非负整数且不大于 $k$。

## 说明/提示

对于第一组数据，由 $a_3=2$ 且 $b_3=1$，可以求出 $x=3$，从而唯一满足条件的 $b$ 数组为 $[2,0,1]$。

对于第二组数据，$a_2+b_2=1$，$a_4+b_4=0$，所以不可能做到 $a$ 数组与 $b$ 数组互补。

对于第四组数据，以下是所有满足条件的 $b$ 数组：
- $[4,2,3,0,1]$
- $[5,3,4,1,2]$
- $[6,4,5,2,3]$
- $[7,5,6,3,4]$
- $[8,6,7,4,5]$
- $[9,7,8,5,6]$
- $[10,8,9,6,7]$

共有 $7$ 种可能，因此输出 $7$。

## 样例 #1

### 输入

```
7
3 10
1 3 2
-1 -1 1
5 1
0 1 0 0 1
-1 0 1 0 -1
5 1
0 1 0 0 1
-1 1 -1 1 -1
5 10
1 3 2 5 4
-1 -1 -1 -1 -1
5 4
1 3 2 1 3
1 -1 -1 1 -1
5 4
1 3 2 1 3
2 -1 -1 2 0
5 5
5 0 5 4 3
5 -1 -1 -1 -1```

### 输出

```
1
0
0
7
0
1
0```

# 题解

## 作者：linch (赞：2)

感觉不难，但 VP 时貌似不太清醒，没调出来。

## Solution
显然 $x$ 的每一种可能取值都对应着一种情况。可以分类讨论 $x$ 的可能取值。

- 若存在**不少于两个** $b_i$ 的值是确定的，由于所有 $a_i+b_i$ 的值都要相等，因此可以继续分类：
  - 如果在所有 $b_i \ne -1$ 的 $i$ 中找到不相等的 $i,j$ 使得 $a_i+b_i\ne a_j+b_j$，就没有合法的 $x$。
  - 如果不存在这样的 $i,j$，就有且仅有一个 $x$ 为它们的和 $a_i+b_i$。同时注意此时需满足 $\forall a_i\in [x-k,x]$，否则也没有合法方案。
- 若**有且仅有一个** $b_i$ 的值是确定的，此时 $x$ 值也只有 $a_i+b_i$ 一种。此时仍需满足 $\forall a_i\in [x-k,x]$，否则也没有合法方案。
- 若所有 $b_i$ 都不确定，那么此时 $x$ 最大为 $a$ 中最小值能加到的最大，即 $\min{(a_1,a_2\cdots ,a_n)}+k$，最小为 $\max{(a_1,a_2\cdots ,a_n)}$。答案即为 $\min{(a_1,a_2\cdots ,a_n)}+k-\max{(a_1,a_2\cdots ,a_n)}+1$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+10;
int n, t, k, a[maxn], b[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> k;
		int x = -1;
		bool flag = false;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> b[i];
		for (int i = 1; i <= n; i++) {
			if (b[i] != -1) {
				if (x == -1) x = b[i] + a[i];
				else if (a[i] + b[i] != x) {
					cout << "0\n";
					flag = true;
					break;
				}
			}
		}
		if (flag) continue;
		if (x != -1) {
			for (int i = 1; i <= n; i++) {
				if (a[i] == x) continue;
				if (a[i] > x || a[i] + k < x) {
					flag = true;
					cout << "0\n";
					break;
				}
			}
			if (flag) continue;
			cout << "1\n";
		} else {
			int s = *min_element(a + 1, a + n + 1);
			int t = *max_element(a + 1, a + n + 1);
			int ans = k - t + s + 1;
			ans = ans > 0 ? ans : 0;
			cout << ans << "\n";
		}
	}
	return 0;
}
```
[AC record](https://codeforces.com/contest/2106/problem/C)

---

## 作者：Aaq777 (赞：0)

## 前言
这是本蒟蒻第一次写题解，请各位大佬多多请教。

## 思路
这一题可以分类讨论， 一共有两种情况。

1. $b$ 有一个以上确定的数。
 
   这个时候只有 $1$ 种或 $0$ 种情况，因为有确定值我们就可以知道互补值，我们就得遍历一遍 $a$，如果某个元素的所有可能的互补值都不等于以知的互补值，那么输出 $0$， 否则输出 $1$。

2. $b$ 没有确定的数。

   那么 $b$ 的最大值最小是 $ \max(a_1, a_2, ..., a_n) - \min(a_1, a_2, ... a_n)$，最大是 $k$，所以一共有 $k - (\max(a_1, a_2, ..., a_n) - \min(a_1, a_2, ..., a_n)) + 1$ 种方案。但如果前面算式的值小于 $0$，那就输出 $0$。
## AC代码
``` cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

#define int long long

const int P = 998244353; 
const int Base = 2281701377;
const int INF = 0x3f3f3f3f3f3f3f3f; 

const int N = 2e5 + 10, M = 2e6 + 10; 
// 前面纯属个人代码习惯
int n, k;
int a[N];
int b[N]; //定义变量
void solve()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> b[i];
	} //输入
	int cnt = 0, sum = 0; // cnt是确定值数量，sum是确定值
	for(int i = 1; i <= n; i++) {
		if(b[i] != -1) { // 特判有没有确定值
			if(cnt > 0 && a[i] + b[i] != sum) {
				cout << 0 << endl;
				return; // 如果确定值的互补值不相同，那么直接输出0并推出函数
			}
			sum = a[i] + b[i];
			cnt++;
		}
	}
	if(cnt > 0) { // 情况一
		for(int i = 1; i <= n; i++) {
		    if(b[i] == -1) {
			    int x = sum - a[i];
			    if(x < 0 || x > k) { // 如果没有值等于互补值，那么输出0并退出函数
				    cout << 0 << endl;
				    return;
			    }
		    }
	    }
		cout << 1 << endl; //否则输出1并退出函数
		return;
	}
    // 情况二 
	int ans = INF, v = 0;
	for(int i = 1; i <= n; i++) {
		ans = min(ans, a[i]);
		v = max(v, a[i]);
	}
	int ans2 = k - (v - ans) + 1;
	if(ans2 < 0) { //特判是否小于0
		cout << 0 << endl;
	}
	else {
		cout << ans2 << endl;
	}
}
signed main() {
    int t;
    cin >> t;
    while(t--) {
    	solve();
	}
    //多测模板
	return 0;
}
```

---

## 作者：mc_xiexie (赞：0)

### 题意

假设有大小为 $ n $ 的两个数组 $a$ 和 $b$ 当且仅当对于所有 $1 \le i \le n$，$a_i+b_i=x$ 时称 $a$ 和 $b$ 是 $x$ 互补。

### 结论

1. 如果我们知道 $a$ 的每一个值，并且我们知道 $x$，我们可以唯一地确定 $b$ 的元素。

2. 如果 $a$ 和 $b$ 是 $x$ 互补的，则 $b$ 的最大元素位于 $a$ 的最小元素所在的索引。这是因为当 $a_i$ 最小时，为了使 $a_i+b_i=s$ 成立，$b_i$ 必须最大化。

3. $b$ 的最大元素必须至少为 $\max a-\min a$，即 $a$ 的最大元素与最小元素之差。

### 解法

这道题有两种情况。

1. $b$ 中有至少有一个元素没有缺失。

根据结论一，此时我们可以算出 $x$ 的唯一值，如果其他没缺失的元素 $a_i+b_i=s$ 答案就是唯一的，否则不存在 $a$ 和 $b$ 互补的情况。

2. $b$ 中元素全部缺失。

通过结论三，我们可以假设 $b$ 的最大元素为 $\max a-\min a，\max a-\min a+1, \ldots ,k$。

这时我们得到了一个元素，情况二就变为了情况一，并且只有一个元素。

所以情况二有 $k-\max a+\min a+1$ 个解。

---

## 作者：Damon77 (赞：0)

# 0x00 题目大意
题中给的很清晰了。
# 0x01 题目分析
注意到 $k \le 10^9$ 范围，可以直接否定掉枚举整数 $x$ 这个做法了。

同时注意到 $n \le 2 \times 10^5$，同样也可以排除 $O(T \times N^2)$ 的做法了。

这里提供的是一种 $O(T \times N)$ 的做法。

这里我们分情况讨论。
- $b$ 数组内没有 $-1$：此时要么有一种可能，要么没有可能性。我们看每一项之和是否相等，相等时答案为 $1$ ，否则答案为 $0$。
- $b$ 数组内有 $-1$，同时也有不是 $-1$ 的数：同样要么只有答案为 $1$ 或者 $0$ 两种情况，如果 $b$ 所有不为 $-1$ 的项与对应 $a$ 数组这一项的和不相等，答案为 $0$；如果 $b$ 数组为 $-1$，$a$ 数组内当前项最小值加上 $k$ 无法到达 $x$（此时 $x$ 是确定的），那么答案也为 $0$；如果 $a$ 的某一项要比 $x$ 还大，同样答案也为 $0$；其他情况答案为 $1$。
- $b$ 数组内全是 $-1$：如果 $maxx$ 要大于 $a$ 中任意一数加上 $k$ 的结果，那么答案为 $0$。其他情况下答案为  $k-maxx+1+minn$。这里的 $maxx$ 为 $b_i=-1$ 时 $a_i$ 的最大值，$minn$ 为 $b_i=-1$ 时 $a_i$ 的最小值。

# 0x02 AC CODE
[AC](https://codeforces.com/problemset/submission/2106/318107472) 记录，洛谷无法提交，请移步至 [CF](https://codeforces.com/problemset/problem/2106/C) 上提交。

```cpp
#include<bits/stdc++.h>
using namespace std；补药复制粘贴代码，养成自己打代码的好习惯
#define ll long long
#define ld long double
#define FOR(x,a,b,c) for(int x=a；x<=b；x+=c)
#define MFOR(x,a,b,c) for(int x=a；x>=b；x-=c)
#define MPFOR(x,a,b,c) for(int x=a；a<=b；x*=c)
#define lowbit(x) x&(-x)
#define dbug printf("qwq")
const int N3=1e3+10；
const int N=1e6+10；
const ll inf=1e18；
const long double esp=1e-8；

ll a[N],b[N]；

int mian(){//多测！多测！多测！
	ll n,k；
	cin>>n>>k；
	ll maxx=0；
	ll minn=inf；
	ll sm1=-1；//记录题目中x的值
	ll ans=0；
	for(int i=1；i<=n；i++){
		cin>>a[i]；
	}
	for(int i=1；i<=n；i++){
		cin>>b[i]；
	}
	for(int i=1；i<=n；i++){
		if(b[i]!=-1){
			if(sm1==-1){
				sm1=a[i]+b[i]；
			}
			else if(sm1!=a[i]+b[i]){//统计答案为0情况
				cout<<0<<"\n"；
				return 0；
			}
		}
		else{
			maxx=max(maxx,a[i])；
			minn=min(minn,a[i])；
		}
	}
	for(int i=1；i<=n；i++){//统计答案为0情况
		if((a[i]+k<maxx&&sm1==-1)||(a[i]>sm1&&sm1!=-1)||(a[i]+k<sm1&&sm1!=-1)) {
			cout<<0<<"\n"；
			return 0；
		}
	}
	if(sm1!=-1){//特殊判断答案为1的情况
		cout<<1<<"\n"；
		return 0；
	}
	ans=k-maxx+1+minn；//求出答案
	
	cout<<ans<<"\n"；
	return 0；
}

int main(){
	//freopen(".in","r",stdin)；
	//freopen(".out","w",stdout)；
    ios::sync_with_stdio(false)；
	ll t；
	cin>>t；
	while(t--){
		mian()；
	}
	//fclose(stdin)；
	//fclose(stdout)；
	return 0；
}
```

---

## 作者：Noah2022 (赞：0)

### 思路
采用分类讨论的方式：
#### 可能1：
对于每一个 $i(1 \le i \le n)$，若 $b_i$ 都为 $-1$，由于 $a_i$ 的最小值对应的是 $b_i$ 的最大值，易得 $b_i$ 的最大值 $k_1$ 应为 $\max(a_1,a_2,\dots,a_n)-\min(a_1,a_2,\dots,a_n)$ 。所以答案就为 $k-k_1+1$。
#### 可能2：
有 $b_i \ne -1$，那么我们可以得到 $a_i+b_i$ 的值，然后枚举判断是否合法即可，答案只有 $0$ 和 $1$。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005],t,n,k;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=1;i<=n;++i)cin>>b[i];
        int s=-1,bj=0;
        for(int i=1;i<=n;++i){
            if(b[i]!=-1){
                if(s==-1)s=a[i]+b[i];
                else{
                    if(s!=a[i]+b[i]){
                        cout<<0<<'\n';
                        bj=1;
                        break;
                    }
                }
            }
        }
        if(bj)continue;
        if(s==-1){
            sort(a+1,a+n+1);
            cout<<k-a[n]+a[1]+1<<'\n';
            continue;
        }
        for(int i=1;i<=n;++i){
            if(a[i]>s||s-a[i]>k){
                cout<<0<<'\n';
                bj=1;
                break;
            }
        }
        if(!bj)
        cout<<1<<'\n';
    }
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF2106C)
# 思路
不难发现，本题可以分为两种情况。

1. 当 $b$ 数组全都是 $-1$。我们可以发现 $b$ 数组最大数最小的情况为 $a$ 数组的最大数减去最小数。而 $b$ 数组最大数最大为 $k$。所以此时答案为 $k-(maxx-minx)+1$，$maxx$ 表示 $a$ 数组的最大数，$minx$ 表示 $a$ 数组的最小数。
2. 当 $b$ 数组有一个不是 $-1$。那么答案只有可能是 $0$ 或 $1$。当 $b$ 数组中未知的数超出了 $0 \sim k$ 的范围或存在四个数 $a_i+b_i \ne a_j+b_j$ 且 $b_i$ 和 $b_j$ 都不为 $-1$ 时答案就为 $0$，否则答案为 $1$。
# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N];
int b[N];
void solve()
{
	int n,k;
	cin >>n>>k;
	for(int i=1;i<=n;i++) cin >>a[i];
	for(int i=1;i<=n;i++) cin >>b[i];
	bool flag=1;
	for(int i=1;i<=n;i++)
	{
		if(b[i]!=-1)
		{
			flag=0;
			break;
		}
	}
	if(flag)
	{
		int maxx=0,minx=2e9;
		for(int i=1;i<=n;i++)
		{
			maxx=max(maxx,a[i]);
			minx=min(minx,a[i]);
		}
		cout <<k-(maxx-minx)+1<<'\n';
	}
	else
	{
		int sum=-1;
		for(int i=1;i<=n;i++)
		{
			if(b[i]!=-1)
			{
				int ans=a[i]+b[i];
				if(sum==-1) sum=ans;
				else
				{
					if(sum!=ans)
					{
						cout <<0<<'\n';
						return ;
					}
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			int bb=sum-a[i];
			if(bb<0 || bb>k)
			{
				cout <<0<<'\n';
				return ;
			}
		}
		cout <<1<<'\n'; 
	}
}
int main()
{
	int t;
	cin >>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

