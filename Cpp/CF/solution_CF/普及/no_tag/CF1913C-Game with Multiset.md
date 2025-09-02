# Game with Multiset

## 题目描述

In this problem, you are initially given an empty multiset. You have to process two types of queries:

1. ADD $ x $ — add an element equal to $ 2^{x} $ to the multiset;
2. GET $ w $ — say whether it is possible to take the sum of some subset of the current multiset and get a value equal to $ w $ .

## 样例 #1

### 输入

```
5
1 0
1 0
1 0
2 3
2 4```

### 输出

```
YES
NO```

## 样例 #2

### 输入

```
7
1 0
1 1
1 2
1 10
2 4
2 6
2 7```

### 输出

```
YES
YES
YES```

# 题解

## 作者：hikariyo_ (赞：7)

给定的数字都是二的次幂，所以考虑这样一个问题，如果一个数 $x$ 能被凑出来，那么一定是这样的形式：


$$
x=\sum_{i=0}^{29}a_i2^i
$$

如果能够在 $i$ 更大的时候使 $a_i$ 尽量大，这样一定是不劣的，因为这会使得 $i$ 更小的时候能够少选。

因此，从大到小枚举二进制位 $i$，用二分找到 $a_i2^i\le v$ 的最大的 $a_i$，看最后能否让 $v$ 归零。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 100010;
int n, x[N];

bool query(int v) {
    for (int i = 29; i >= 0; i--) {
        int l = 0, r = x[i];
        while (l < r) {
            int mid = (l+r+1) >> 1;
            if ((mid << i) <= v) l = mid;
            else r = mid-1;
        }
        v -= r << i;
    }
    return !v;
}

signed main() {
    cin >> n;
    for (int i = 1, t, v; i <= n; i++) {
        cin >> t >> v;
        if (t == 1) x[v]++;
        else cout << (query(v) ? "YES" : "NO") << '\n';
    }
    return 0;
}
```


---

## 作者：Sundar_2022 (赞：5)

### 【题目描述】

你有一个空的多重集，你需要处理若干下列询问：

1. ADD $ x $：加入一个数值为 $ 2^x $ 的元素到该多重集。
2. GET $ w $：判断是否存在一个该多重集的子集，使得这个子集的所有元素之和等于 $ w $。

$ 1≤m≤10^5,0≤x≤29,0≤w≤10^9 $

### 【思路】

#### 操作一：ADD

首先，这个多重集里面只有二的幂次方的数，所以我们可以定义一个 $ sum $ 数组来表示这个多重集，$ sum_i $ 表示这个多重集里面有多少个数值为 $ 2^i $ 的元素。

这样子，操作一就很好实现了，直接 $ sum_x+1 $ 就行。

####  操作二：GET

我们发现，如果要让这个多重集有一个子集加起来等于 $ w $，我们需要满足：

* 对于 $ w $ 的二进制表示法，如果倒数第 $ i $ 位为 $ 1 $（最后一位算第 $ 0 $ 位），则多重集之中一定存在一个 $ 2^{i} $。

但是现在我们的多重集可能会有多个相同的元素，他们可以“进位”成一个新元素，就像两个 $ 2^x $ 可以合并为一个 $ 2^{x+1} $ 一样。

这就难办了，我们不但需要考虑 $ w $ 需不需要当前的 $ 2^x $，还要关心“进位”。

我们可以这么想：

1. 把这个多重集复制到一个新数组 $ sum1 $ 里去（以防后面的操作改变这个多重集原本结构）。
2. 从低到高扫 $ w $ 的二进制位。
3. 如果 $ w $ 倒数第 $ i $ 位为 $ 1 $（最后一位算第 $ 0 $ 位），则它需要一个值为 $ 2^{i} $ 的元素，$ sum1_i-1 $。
4. 把其他所有当前值的元素进位（反正已经没用了）。

如果在取 $ w $ 的某一个二进制位置，发现没有这个值的元素了，就说明拼不出来。

否则就可以通过选取和“进位”拼出来。

### 【Code】

```cpp
#include <bits/stdc++.h>
using namespace std;

int sum[35],sum1[35];
int m,op,x,w;
bool Output; 

int main()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&x);
			sum[x]++;
		}else{
			scanf("%d",&w);
			Output=false;
			for(int i=0;i<=31;i++) sum1[i]=sum[i]; //1.分离临时数组 
			for(int i=0;i<=31;i++){                //2.从小到大枚举二进制位 
				int flag=w&(1<<i);                 //3.检查当前位是否需要元素 
				if(flag){
					if(sum1[i]==0){ //需要，但是没有
						puts("NO");
						Output=true;
						break;
					}else{          //否则就用掉 
						sum1[i]--;
					}
				}
				sum1[i+1]+=sum1[i]/2;              //4.“进位”
			}
			if(!Output) puts("YES");
		}
	} 
	return 0;
}
```





---

## 作者：Withershine (赞：2)

## 翻译
初始时你有一个空序列，共 $m$ 次操作，每次操作读入两个数 $t_i$，$v_i$，分为以下两种操作：
1. 当 $t_i=1$ 时，在空序列中加入 $2^{v_i}$ 这一元素。（此时 $0 \le v_i \le 29$）
2. 当 $t_i=2$ 时，询问是否存在：取当前序列的某些元素，使它们的的和等于 $v_i$（此时 $0 \le v_i \le 10^9$）。若存在输出 `YES`，否则输出 `NO`。

## 思路
学过倍增求 LCA 的人都知道，每次倍增向上跳时的，会选择从大到小跳。在本题中，当判断是否存在时，从大到小判断选择的数，与倍增求 LCA 有异曲同工之妙。

最开始本来打算用一个数组 $q$ 存值，然后每次询问时从大到小暴力查询，假设当前数组中有 $k$ 个数，则单次复杂度为 $O(k)$，明显复杂度不够优秀（~~吃了一发 TLE~~）。

转变思路，对于每个操作一，考虑用 $q$ 存 $v_i$ 的数量。再通过前面的小结论，每次查询时，通过查询出当前 $v_i$ 可减去的最大 $x \times 2^j$，$j$ 表示当前枚举到的幂次，$x$（$1 \le x \le q_j$）表示对应的倍数。

然后自信提交~~后又 TLE 了。~~

再次发现虽然幂次只有 $30$。但 $q_j$ 可能会很大，单次枚举任然有极高的复杂度，所以这里直接使用二分枚举。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define mod 998244353
#define ll long long
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
using namespace std;
//priority_queue <ll> q;
//priority_queue <ll , vector<ll> , greater<ll>> q;
inline ll QuickPow(ll a , ll b)
{
    if(a == 1 || b == 0)
    {
        return 1;
    }
    ll k = QuickPow(a , b >> 1);
    if(b & 1)
    {
        return k * k * a;
    }
    return k * k;
}
ll m , opt , x;
ll q[100005] , top;
ll max_num;
signed main()
{
    // freopen("in.in" , "r" , stdin);
    // freopen("out.out" , "w" , stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> m;
    while(m--)
    {
        cin >> opt >> x;
        if(opt == 1)
        {
            q[x]++;
            max_num += QuickPow(2 , x);
        }
        else
        {
            if(x > max_num)
            {
                cout << "NO" << '\n';
                continue;
            }
            fo(i , 29 , 0)
            {
                if(!q[i])
                {
                    continue;
                }
                ll l = 0 , r = q[i] , ans = 0;
                ll mid;
                ll now = QuickPow(2 , i);
                while(l <= r)
                {
                    mid = (l + r) / 2;
                    if(now * mid > x)
                    {
                        r = mid - 1;
                    }
                    else
                    {
                        ans = mid;
                        l = mid + 1;
                    }
                }
                x -= now * ans;
                if(x <= 0)
                {
                    break;
                }
            }
            if(x == 0)
            {
                cout << "YES" << '\n';
            }
            else
            {
                cout << "NO" << '\n';
            }
        }
    }
    return 0;
}
```


---

## 作者：harmis_yz (赞：0)

## 分析

考虑暴力。

题目很显然想让我们用二进制来求解每个询问。把 $w$ 分解为 $2^0 \times p_0 + 2^1 \times p_1 +\dots+ 2^{30} \times p_{30}$。对于 $p_i$ 为 $1$ 的情况，由于 $2^{j} \times 2^{i-j}$ 能凑成 $1$ 个 $2^{i}$。所以可以将所有没用过的幂次不比 $2^i$ 大的数写成：$\sum\frac{cnt_{2^{j}}}{2^{i-j}}$。只要这个值不低于 $1$，就表示有解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second
 
const int N=60;
int n,cnt[N];
 
il void solve(){
	cin>>n;
	for(re int i=1,op,x;i<=n;++i){
		cin>>op>>x;
		if(op==1) ++cnt[x];
		else{
			int len=0,sum=0;
			while(x){
				int k=x%2;
				sum/=2,sum+=cnt[len];
				if(sum<k){cout<<"NO\n";goto over;}
				sum-=k,x/=2,++len;
			}
			cout<<"YES\n";
			over:;
		}
	}	
	return ;
}
 
 
signed main(){
	int t=1;/*cin>>t;*/while(t--)
	solve();
	return 0;
}
```


---

## 作者：yyrwlj (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1913C)

## 1. ADD

对于插入操作，使用一个桶来记录即可。

## 2. GET

首先，两个 $2^x$ 可以拼成一个 $2^{x+1}$，但是一个 $2^{x+1}$ 不能拆分成两个 $2^x$。

所以将给定的 $w$ 的二进制表示从低位到高位枚举，当无法拼出当前这一位的 $1$ 时，就直接无解。

为了方便，用一个变量 $sum$ 来存储最多能拼出多少个当前的 $2^i$。

统计到第 $i$ 位时，先令 $sum$ 加上当前这一位对应桶里的数量，若 $w$ 的二进制表示中这一位是 $1$，且 $sum = 0$，则无解，否则 $sum$ 减一。检查完后要使 $sum = \lfloor \frac{sum}{2} \rfloor$，因为两个小的可以拼成一个大的，若 $sum$ 为奇数，则多余的一个就只能扔掉了。

注意枚举的位数要够多，询问之间互相独立。

## Code

```cpp
#include <iostream>
using namespace std;
const int N = 35;
int S[N];
void get(int x)
{
    int sum = 0;
    for (int i=0;i<=30;i++)
    {
        sum += S[i];
        if (x >> i & 1)
        {
            if (!sum)
            {
                puts("NO");
                return;
            }
            else
                sum --;
        }
        sum >>= 1;
    }
    puts("YES");
}
int main()
{
    int m;
    scanf("%d", &m);
    while (m--)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1)
            S[x] ++;
        else
            get(x);
    }
    return 0;
}
```

---

## 作者：yuyc (赞：0)

### 题意
判断能否取多集中若干个数使得它们的和等于 $w$。
### 解析
由于给的数都是 $2$ 的幂，所以我们可以每次让 $w$ 减去不大于它的在集合中存在的二进制位数最多的数，如果能减完那么就说明可以，否则说明不可能。

怎么保证这种策略是最优的？


假设 $n=\lfloor \log_2w\rfloor$，则有 $2^n \le w$。

如果不减 $2^n$ 也能让 $w$ 变成 $0$，那么：

$$w=t_{n-1} \times 2^{n-1}+t_{n-2} \times 2^{n-2}+\dots+t_{0} \times 2^{0}\ge2^n$$

显然，在上式中必定有一些 $t$ 大于 $1$，我们不妨把它看成一个**还没有处理进位**的二进制数，第 $i$ 位的数值为 $t_i$。

那么，在处理完进位后，这个二进制数必定有第 $n$ 位大于等于 $1$，这实际上是由若干个 $2^i(0\le i<n)$ 组成的，于是我们就可以用 $2^n$ 来替代这若干个 $2^i$。

故如果不减 $2^n$ 能让 $w$ 变成 $0$，那么减去 $2^n$ 也可以把 $w$ 变成 $0$，并且这样我们还省了若干个 $2^i$。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int cnt[30];
bool find(int x,int pos){ //x：当前 w 还剩多少，pos：将要减去的二进制数的位数
	if(!x) return true;   
	if(pos < 0) return false;
	int num = x >> pos;   //计算 x 可以减去多少个2^pos
	if(cnt[pos] >= num) x -= num << pos; 
	else x -= cnt[pos] << pos;
	return find(x,pos - 1);
}
int main(){
	int T;
	cin>>T;
	while(T--){
		int t,x;
		cin>>t>>x;
		if(t == 1){
			cnt[x]++;
		}else{
			cout<<(find(x,29) ? "YES" : "NO")<<endl;
		}
	}
	return 0;
}
```


---

## 作者：myyyIisq2R (赞：0)

## [CF1913C Game with Multiset](https://www.luogu.com.cn/problem/CF1913C)

## 题意
给出 $m$ 次操作，每次操作输入 $t$ 和 $v$ 两个数，当 $t$ 为 $1$ 时，将 $2^v$ 加入集合，否则询问能否通过已经加入的数凑出 $v$。

## 思路
$v$ 很小，最大只有 $29$，开桶存。

询问的时候贪心地从大往小减已经输入过的 $2^v$。
- 如果减到 $0$ 则有解；
- 如果减不到 $0$ 则无解。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e3;
int a[N];
signed main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(0);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	cin.tie(0);
	cout.tie(0); 
	int n;	
	cin >> n;
	

	for(int i{1}; i <= n ; i++)
	{
		int op,x;
		cin >> op >> x;
		if(op == 1)
		{
			a[x]++;
		}
		else
		{
			for(int i{31};i>=0;i--)
			{
				int tmp = 1 << i;
				if(x < tmp || !a[i]) continue;
				for(int j{1};j<=a[i];j++)
				{
					if(x < tmp) break;
					x -= tmp;
				}
			}
			if(!x) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	
}
```
~~赛时以为选的子序列需要连续，太zz了~~

---

