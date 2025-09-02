# [XJTUPC 2025] Beat Verdict: Precision Strike

## 题目描述

**这是一道交互题。**

你正在玩一款名为「乌蒙滴叉」的音乐游戏。在专家模式中，需要精确校准音符的击打时机参数，该参数是一个 $[1,n]$ 内的神秘正整数 $x$。

为了确定这个参数，你可以进行至多 $4$ 次校准测试。每次测试时，你选择一个正整数测试值 $y$ ($1 \le y \le n$)，系统将告知你 $y > x$ 是否成立。最终你需要给出一个正整数参数估计值 $x'$ ($1 \le x' \le n$)，且满足 $x' \in \left[0.5x, 2x\right]$。

注意：最终给出的估计值 $x'$ 不计入上述至多 $4$ 次测试次数。

## 说明/提示

在第一组测试用例中，可以唯一确定 $x = 1$，因此我们直接提交 $x' = 1$。

在第二组测试用例中，隐藏的参数 $x = 3$，交互过程如下：

- 测试 $y=6$，响应为 $y>x$ 为真；
- 测试 $y=4$，响应为 $y>x$ 为真；
- 测试 $y=2$，响应为 $y>x$ 为假；
- 测试 $y=3$，响应为 $y>x$ 为假；
- 提交 $x' = 3$。

请注意，此示例仅用于演示交互格式。不能保证提供的查询是最优的或唯一确定答案。

## 样例 #1

### 输入

```
2
1

8

1

1

0

0

```

### 输出

```


! 1

? 6

? 4

? 2

? 3

! 3```

# 题解

## 作者：XuZile (赞：3)

# P12531 题解
## 解法思路
经过观察可以得知 $x\in [0.5a,2a]$，然而我们至多只能进行 4 次询问，这时我们就可以去考虑使用二分进行分组。我们可以把 $[1,n]$ 分成 16 组，$[1,4][5,20]\cdots[1431655765,5726623060]$，这 16 组分别代表 $2,10\cdots2863311530$。然后用二分算法可以发现不论 $n$ 是多大，最多也只会进行 4 次操作，满足题意。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int ans,t,n,f[20],L,R;
signed main() {
	cin >> t;
	for(int i = 1 ;i <= 17; i++) f[i] = f[i - 1] * 4 + 1;
	while(t--) {
		cin >> n;
		L = 1;R = 1;
		while (f[R+1] <= n) R++;
		while (L < R){
			int mid = (L + R + 1) / 2;
			printf("? %lld\n",f[mid]);
			int x;
			cin >> x;
			if(x) R = mid - 1;
			else L = mid;
		}
		printf("! %lld\n",min(f[L] * 2,n));
	}
	return 0;
}
```

---

## 作者：dongzirui0817 (赞：3)

## 思路

发现 $[0.5n, \, 2n]$ 的范围中，在 $x$ 很大时会包含很多数，所以考虑将一个区间的数用一个代表记下，这个范围的数在输出代表时均满足。

于是得到如下表格：

| 区间 | 代表 | 区间 | 代表 |
|:-:|:-:|:-:|:-:|
| $[1, \, 4]$ | $2$ | $[87381, \, 349524]$ | $174762$ |
| $[5, \, 20]$ | $10$ | $[349525, \, 1398100]$ | $699050$ |
| $[21, \, 84]$ | $42$ | $[1398101, \, 5592404]$ | $2796202$ |
| $[85, \, 340]$ | $170$ | $[5592405, \, 22369260]$ | $11184810$ |
| $[341, \, 1364]$ | $682$ | $[22369261, \, 89478484]$ | $44739242$ |
| $[1365, \, 5460]$ | $2730$ | $[89478485, \, 357913940]$ | $178956970 $ |
| $[5461, \, 21844]$ | $10922$ | $[357913941, \, 1431655764]$ | $715827882 $ |
| $[21845, \, 87380]$ | $43690$ | $[1431655765, \, 5726623060]$ | $2863311530$ |

~~事实上不看表格也行。~~

总之，设第 $i$ 个区间代表为 $f_i$，那么 $f_1 = 2$，$f_i = (2 \times f_{i - 1} + 1) \times 2$，对应区间为 $[0.5f_i, \, 2f_i]$。

然后你发现刚好 $16$ 个区间，用二分刚好就能在 $4$ 次询问内解决。

然后，就没有然后了。

## 思路

先预处理代表 $f_i$，之后每一次测试二分。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll c[20];
int T;

int main() {
	c[1] = 2;
	for (int i = 2 ; i <= 16 ; i++)
		c[i] = (c[i - 1] * 2 + 1) * 2;
	for (int i = 1 ; i <= 16 ; i++)
		printf("%lld %lld %lld\n", c[i] / 2, c[i], c[i] * 2);
	cin >> T;
	for (ll n ; T-- ; ) {
		cin >> n;
		int L = 1, R = 2;
		for (int i = 1 ; i <= 16 ; i++)
			if (c[i] * 2 < n) ++R;
		while (L < R - 1) {
			int mid = (L + R) >> 1, k;
			cout << "? " << c[mid] / 2 << endl;
			cin >> k;
			if (k) R = mid;
			else L = mid;
		}
		if (c[L] > n) cout << "! " << n << endl;
		else cout << "! " << c[L] << endl;
	}
	return 0;
}
```

---

## 作者：redfull66 (赞：2)

注意到 $x' \in \left[0.5x, 2x\right]$，$1\le n \le 5 \times 10^9$ 和至多 $4$ 次测试次数而考虑分组二分。

将 $\left[1, n\right]$ 分为 $\left[1, 4\right]$，$\left[5, 20\right]$，$\left[21, 84\right] \cdots$ 与之对应的数为 $2$，$10$，$42 \cdots$ 最多 $16$ 段，二分最多询问 $4$ 次，满足题意。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,t,n,a,m,l,r,d[20];
int main(){
	cin>>t;
	for(int i=1;i<=17;i++)d[i]=d[i-1]*4+1;
	while(t--){
		cin>>n,l=r=1;
		while(d[r+1]<=n)r++;
		while(l<r){
			m=(l+r+1)/2;
			cout<<"? "<<d[m]<<endl;
			cin>>a;
			if(a)r=m-1;
			else l=m;
		}
		cout<<"! "<<min(d[l]*2,n)<<endl;
	}
	return 0;
}

```

---

## 作者：Ewig_Milan (赞：2)

观察到：
$$
\begin{aligned}
x^{\prime}\in[0.5x,2x]
\end{aligned}
$$
于是我们贪心地把尽可能大范围的答案统一：
$$
\begin{aligned}
ans(1\sim4)&=2\\
ans(5\sim20)&=10\\
ans(21\sim84)&=42\\
\dots\\
ans(1431655765\sim5726623060)&=2863311530\\
\end{aligned}
$$

以上正好十六个可能的 ans ，二分即可。

论我如何发现这是 16 个：~~手算算到十万时发现身边有台电脑~~。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ll l = 1, r = 0;
    while(l <= 5e9) {
        r = l << 2;
        printf("    {%lld, %lld, %lld},\n", l, r, l << 1);
        l = r + 1;
    }
    return 0;
}
```

事已至此，复制粘贴算了，然后预处理都不用了。  
~~反正不多，谁乐意补写一个预处理~~？

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int T;
ll qy[17][3] = {
    {0, 0, 0},
    {1, 4, 2}, 
    {5, 20, 10}, 
    {21, 84, 42}, 
    {85, 340, 170}, 
    {341, 1364, 682}, 
    {1365, 5460, 2730}, 
    {5461, 21844, 10922}, 
    {21845, 87380, 43690}, 
    {87381, 349524, 174762}, 
    {349525, 1398100, 699050}, 
    {1398101, 5592404, 2796202}, 
    {5592405, 22369620, 11184810}, 
    {22369621, 89478484, 44739242}, 
    {89478485, 357913940, 178956970}, 
    {357913941, 1431655764, 715827882}, 
    {1431655765, 5726623060, 2863311530}, 
};

int main() {
    scanf("%d", &T);
    while(T--) {
        ll n; scanf("%lld", &n);
        int l = 1, r = 16;
        for(int i = 1; i <= 4; i++) {
            int mid = l + r >> 1;
            if(qy[mid][0] > n) {
                r = mid;
                continue;
            }
            printf("? %lld\n", min(qy[mid][1] + 1, n));
            fflush(stdout);
            int flag; scanf("%d", &flag);
            if(flag) r = mid;
            else l = mid + 1;
        }
        printf("! %lld\n", min(qy[l][2], n));
        fflush(stdout);
    }
    return 0;
}
```

---

## 作者：01bit (赞：1)

赛时只想到了 $n\le2^{32}$ 的做法 QAQ。

首先发现如果已知 $x\in[l,r]$，且 $2l\ge\lceil0.5r\rceil$，即 $4l\ge r$ 时，那么回答 $\min(2l,n)$ 一定是符合条件的。

然后可以想到将原条件转化为 $2+\log_2l\ge\log_2r$，每次二分取 $\log_2\mathrm{mid}=\dfrac{\log_2l+\log_2r}{2}$ 即 $\mathrm{mid}=\sqrt{lr}$ 就可以在 $4$ 次询问处理 $2^{32}$ 规模的数据了。

但是 $5\times10^9>2^{32}$，怎么办？可以将 $[1,n]$ 划分为 $[1,4],[5,20],[21,84],\ldots$ 等至多 $16$ 个一定能有答案的区间，每个区间的左端进行预处理计算。这之后再二分确定 $x$ 在哪个区间即可。此时最后一个区间的右端为 $5726623061$，可保证覆盖整个 $[1,n]$。

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
ll n, f[17];
void solve() {
    cin >> n;
    ll l = 1, r = 0;
    while (r < 16 && f[r + 1] <= n)
        r++;
    while (l < r) {
        ll mid = (l + r + 1) >> 1, res;
        cout << "? " << f[mid] << endl;
        cin >> res;
        if (res)
            r = mid - 1;
        else
            l = mid;
    }
    cout << "! " << min(f[l] * 2, n) << endl;
}
int main() {
    f[1] = 1;
    for (ll i = 2; i <= 16; i++)
        f[i] = f[i - 1] * 4 + 1;
    ll t;
    cin >> t;
    for (ll i = 1; i <= t; i++)
        solve();
    return 0;
}
```

---

## 作者：wdl_ (赞：1)

由于次数很少范围又很大，因此考虑分组。

每一个数都有一个对应的答案区间，所以考虑 $i$ 和 $j$ 的答案区间有交集的边界情况，即 $2 \times i \ge 0.5 \times j$ 的解。解得 $j \le 4 \times i$。所以 $i$ 到 $4 \times i$ 的答案区间都是有交集的。显然这个交集就是 $2 \times i$。

所以就可以从 $1$ 开始分组：$[1,4][5,20],[21,48]$...

这样分组不会超过 $\log_{4}{n}$ 种。经实测最多是 $16$ 组。可以用二分在 $\log_{2}{16}=4$ 次内确定 $x$ 所在组。然后输出区间左边界的两倍即可。


```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 1e18
#define lowbit(x) (x & -x)
#define fo(i,j,k,l) for(int i = j;i <= k;i += l)
using namespace std;
int L[100],R[100];
int n;
int T;
int cnt;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	for(int i = 1;i <= 5000000000;i = R[cnt] + 1)
	{
		cnt ++;
		L[cnt] = i;
		R[cnt] = i * 4;
	}
	cin >> T;
	while(T --)
	{
		cin >> n;
		int now;
		fo(i,1,cnt,1)
		{
			if(L[i] <= n && n <= R[i])
			{
				now = i;
				break;
			}
		}
		int l = 1,r = now;
		while(l < r)
		{
			int mid = (l + r + 1) >> 1;
			cout << "? " << L[mid] << endl;
			int op;
			cin >> op;
			if(op)r = mid - 1;
			else l = mid;
		}
		cout << "! " << min(2 * L[l],n) << endl;
		cout.flush();
	}
	return 0;
}


```

---

## 作者：modfish_ (赞：1)

## 思路
注意到只要把范围限制在某个区间 $[a,4a]$ 之中，然后猜 $2a$ 即可。

那就把 $[1,n]$ 分成若干个这样的区间。即 $[1,4],[5,20],[21,84],\dots$，最后会发现，当 $n=5\times 10^9$ 时，正正好好 $16$ 个区间。二分地询问区间左端点，问四次即可确定。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll ls[35], rs[35], tot = 0;

int main(){
    int T;
    scanf("%d", &T);
    while(T --){
        ll n;
        scanf("%lld", &n);
        tot = 0;
        while(rs[tot] < n) tot ++, ls[tot] = rs[tot - 1] + 1, rs[tot] = min(ls[tot] * 4, n);
        int l = 1, r = tot;
        for(int i = 1; i <= 4; i ++){
            if(l == r + 1) break;
            int mid = ((l + r - 1) >> 1) + 1;
            cout << "? " << ls[mid] << endl;
            int res = 0;
            scanf("%d", &res);
            if(res == 1) r = mid - 1;
            else l = mid;
        }
        cout << "! " << min(rs[l], ls[l] * 2) << endl;
    }
    return 0;
}
```

---

## 作者：_Lazy_zhr_ (赞：0)

二分。

将 $1\sim n$ 分为 $1\sim 4$，$5\sim 20$，$21\sim 84\dots$ 每一段只要一个数就能覆盖到整个段。

最多是 $16$ 段，最多询问 $4$ 次，满足要求。

代码如下：

```cpp
int L[20],R[20];
int n,ans;
void init(){ for(int i=1;i<=16;i++) L[i]=R[i-1]+1,R[i]=L[i]<<2; }
bool ask(int x){
	cout<<"? "<<x<<endl;
	bool in;
	cin>>in;
	return in;
}
void solve(){
	cin>>n;
	if(n==1){
		cout<<"! 1"<<endl;
		return ;
	} int best=1,l=1,r=16;
	while(l<=r)
		if(n<=R[mid]||ask(min(n,R[mid]+1))) best=mid,r=mid-1;
		else l=mid+1;
	cout<<"! "<<min(n,L[best]<<1)<<endl;
}
```
---
感谢 [Vitamin_B](https://www.luogu.com.cn/user/743373) 的帮助。

---

## 作者：Ag2WO4 (赞：0)

考虑将答案对数化考虑。显然 $\log_2x'$ 需要落在 $[\log_2x-1,\log_2x+1]$ 之间。

注意到 $5\times 10^9$ 略大于 $2^{32}=4294967296$，直接四次二分插眼 $16$ 个覆盖不完，考虑将所有数离散地分段：$[1,4],[5,20],[21,84]$，以此类推，第 $16$ 项的结尾为 $5726623060$ 就够用了。

在线打表二分即可。询问一个组的下限是否高于目标数排除组。
```python
x=[1]
for i in range(15):x.append(x[-1]*4+1)
for i in range(int(input())):
    a=int(input());b=8
    for c in[4,2,1]:b-=c if'1'==input(f'? {min(x[b],a)}\n')else-c
    if'1'==input(f'? {min(x[b],a)}\n'):b-=1
    print('!',min(x[b]<<1,a))
```

---

