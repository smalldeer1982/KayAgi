# Poisoned Dagger

## 题目描述

Monocarp is playing yet another computer game. In this game, his character has to kill a dragon. The battle with the dragon lasts $ 100^{500} $ seconds, during which Monocarp attacks the dragon with a poisoned dagger. The $ i $ -th attack is performed at the beginning of the $ a_i $ -th second from the battle start. The dagger itself does not deal damage, but it applies a poison effect on the dragon, which deals $ 1 $ damage during each of the next $ k $ seconds (starting with the same second when the dragon was stabbed by the dagger). However, if the dragon has already been poisoned, then the dagger updates the poison effect (i.e. cancels the current poison effect and applies a new one).

For example, suppose $ k = 4 $ , and Monocarp stabs the dragon during the seconds $ 2 $ , $ 4 $ and $ 10 $ . Then the poison effect is applied at the start of the $ 2 $ -nd second and deals $ 1 $ damage during the $ 2 $ -nd and $ 3 $ -rd seconds; then, at the beginning of the $ 4 $ -th second, the poison effect is reapplied, so it deals exactly $ 1 $ damage during the seconds $ 4 $ , $ 5 $ , $ 6 $ and $ 7 $ ; then, during the $ 10 $ -th second, the poison effect is applied again, and it deals $ 1 $ damage during the seconds $ 10 $ , $ 11 $ , $ 12 $ and $ 13 $ . In total, the dragon receives $ 10 $ damage.

Monocarp knows that the dragon has $ h $ hit points, and if he deals at least $ h $ damage to the dragon during the battle — he slays the dragon. Monocarp has not decided on the strength of the poison he will use during the battle, so he wants to find the minimum possible value of $ k $ (the number of seconds the poison effect lasts) that is enough to deal at least $ h $ damage to the dragon.

## 说明/提示

In the first example, for $ k=3 $ , damage is dealt in seconds $ [1, 2, 3, 5, 6, 7] $ .

In the second example, for $ k=4 $ , damage is dealt in seconds $ [2, 3, 4, 5, 6, 7, 10, 11, 12, 13] $ .

In the third example, for $ k=1 $ , damage is dealt in seconds $ [1, 2, 4, 5, 7] $ .

## 样例 #1

### 输入

```
4
2 5
1 5
3 10
2 4 10
5 3
1 2 4 5 7
4 1000
3 25 64 1337```

### 输出

```
3
4
1
470```

# 题解

## 作者：Tritons (赞：2)

显然，在 $i<n$ 的情况下，第 $i$ 次攻击造成的伤害为 $\min(k, a_{i+1}-a_i)$ 秒，在 $i=n$ 的情况下，总伤害为 $k+\sum\limits_{i=1}^{n-1}\min(k, a_{i+1}-a_i)$  。

可以看到，$k$的值越高，总和就越大。

所以我们可以**二分** $k$ ，找到总和大于或等于 $h$ 时的最小值。

```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
ll a[105], n, h;
int main()
{
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &n, &h);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        ll l = 1, r = 1e18;
        while (l <= r) {
            ll mid = l + r >> 1, ans = mid;
            for (int i = 1; i < n; i++) 
                ans += std::min(mid, a[i + 1] - a[i]);
            if (ans < h) l = mid + 1;
            else r = mid - 1;
        }
        printf("%lld\n", r + 1);
    }
    return 0;
}
```

---

## 作者：miao5 (赞：1)

显然，$k$ 的值越大，对龙的伤害就越高，$k$ 的值越少，对龙的伤害就越低。于是我们考虑二分答案，每次操作二分 $k$ 的值，模拟求出对龙的总伤害，最后输出最小的 $k$ 即可。

关于如何求出一个 $k$ 对龙的伤害：对于每次攻击时间 $a_i$ 判断 $a_i+k$ 与 $a_{i+1}$ 的大小，如果前者较大，那么中毒效果是会被打断的，这一次造成的伤害就会是 $a_{i+1}-a_i$，否则就是 $k$。

```cpp
#include<iostream>
#define int long long
using namespace std;
int a[105];
int n,h;
bool check(int s){
	int tot=0;
	for(int i=1;i<n;i++){
		if(a[i]+s>a[i+1]) tot+=a[i+1]-a[i];
		else tot+=s;
	}
	tot+=s;
	if(tot>=h) return true;
	else return false;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n>>h;
		for(int i=1;i<=n;i++) cin>>a[i];
		int l=1,r=h;
		int mid=(l+r)/2;
		int ans;
		while(l<=r){
			mid=(l+r)/2;
			if(check(mid)){
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：_Gakki_ (赞：0)

设不被打断的数的个数为 $cnt$。   
发现随着 $k$ 的增大不被打断的 $a_i$ 越来越少。同时每次另 $cnt$ 减少的值都为 $a$ 的一个差分值即 $a[i]-a[i-1]$。那么从小到大枚举这个值就可以求出最小的 $k$ 时 $cnt$ 的值。  
那么如何从 $cnt$ 求 $k$ 呢? 此时设没有完全执行的数的贡献为 $y$ 那么对于 $k$ 总共会造成 $k*cnt + y$的伤害，当我们求出 $cnt$ 和 $y$ 得 $k = \lfloor \frac {h-y}{cnt} \rfloor$

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(2)
#define endl "\n"
#define int long long
#define pii pair<int,int>
#define pll pair<long long,long long>
#define fi first
#define sc second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 2*1e5+10,maxm = 2*1e5+10,mod = 1e9+7;
const int inf32 = 0x3f3f3f3f;
const ll inf64 = 0x3f3f3f3f3f3f3f3f;
const double pi = acos(-1),eps = 1e-6;
mt19937 rnd(time(0));

int T;
int n,m;
int a[maxn];
int b[maxn];

int check(int x){
	int res = 0;
	int t = 0,cnt = 0;
	for(int i = 1;i <= n;i++){
		if(a[i]+x > a[i+1]){
			res += a[i+1]-a[i];
			t += a[i+1]-a[i];
		}else{
			res += x;
			cnt++;
		}
	}
	if(res >= m){
		return (m-t+cnt-1)/cnt;
	}
	return -1;
}

int solve(){
	for(int i = 1;i < n;i++){
		b[i] = a[i+1]-a[i];
	}
	b[n] = inf64;
	priority_queue<int,vector<int>,greater<int>> q;
	for(int i = 1;i <= n;i++){
		q.push(b[i]);
	}
	while(q.size()){
		int now = q.top();
		if(check(now) != -1){
			return check(now);
		}
		while(q.top() == now){
			q.pop();
		}
	}
	return -1;
}

signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
   	//freopen("in.in","r",stdin);
	//freopen("out.out","w",stdout);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i = 1;i <= n;i++){
			cin>>a[i];
		}
		a[n+1] = inf64+inf32;
		if(n >= m){
			cout<<1<<endl;
			continue;
		}
		cout<<solve()<<endl;
	}
	return 0;
}
```


---

## 作者：徐晨轩✅ (赞：0)

考虑 **二分** 求解。

我们只要依照题意，求出我们总共攻击了巨龙多少血量（就是让巨龙减少了多少血量）就行了。注意此题与别的二分题不同的是：我们算出的是不符合条件的最大值再 $+1$，因为直接求最小值不好求，而符合条件最小值就是不符合条件的最大值 $+1$。

**注意要用 `long long`！**

AC Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,h,l,r,ans,mid,a[101];
bool check(int k)
{
	int sum=k;
	for(int i=1;i<n;i++)
		sum+=min(k,a[i+1]-a[i]);
	return sum<h;
}
int binary_search()
{
	l=0,r=1e18;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	return ans+1;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> h;
		for(int i=1;i<=n;i++)
			cin >> a[i];
		cout << binary_search() << endl;
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1613C 题解

## 题目大意

勇者要砍恶龙，会在 $a_1\sim a_n$ 这 $n$ 秒向恶龙发起攻击，每次攻击会给龙带来 $x$ 秒的中毒 buff，每秒扣一滴血

#### 注意：龙每次被攻击时会刷新原有的中毒 buff，也就是说第 $t$ 秒的攻击会在第 $t+1$ 秒清除原本的中毒 buff 并且对恶龙造成新的中毒 buff

已知龙有 $h$ 滴血，求出最小的，可以砍死恶龙的 $x$

## 思路分析

那么，对于在第 $i$ 次发起的攻击，也就是第 $a_i$ 秒发起的攻击，中毒的持续时间，也就是伤害值 $w$ 为：

- $i=n$ 或者 $a_{i+1}-a_i \leq x$ 时，$w=x$

- $i\ne n$ 且 $a_{i+1}-a_i > x$ 时，$w=a_{i+1}-a_i$

总结规律，不难得到，$w=\min(x,a_{i+1}-a_i)$，且 $a_{n+1} = + \infty$

所以原题目等价于：求满足 $f(x) = \sum_{i=1}^{n}\,min(x,a_{i+1}-a_{i})>h$ 的最小整数 $x$（ $h\,,a_1\sim a_n$ 已经给出，默认 $a_1=+ \infty$ ）

因为 $f(x)$ 具有单调性，所以这是一道二分答案的题，显然 $x\in [1,h]$，直接套二分答案模板即可

## 说句闲话

#### 这个部分是关于 $f(x)$ 的单调性的证明，不想看的可以直接往下翻代码

其实就是要证明：$\forall x \in Z$，$\min(x,C) \leq \min(x+1,C)$ 为真（ $C$ 为常数 ）

证：

1. $x < C-1$ 时：

	$\min(x,C) =\min(x+1,C)=x$
    
	$\therefore min(x,C)\leq min(x+1,C)$
    
2. $C-1 \leq x < C$

   $\begin{cases}\min(x,C)=x\\\min(x+1,C)=x+1\end{cases}$
    
	$\because x < x+1$
    
	$\therefore min(x,C)\leq min(x+1,C)$
    
3. $C \leq x$ 时：

	$\min(x,C) =\min(x+1,C)=C$
    
	$\therefore min(x,C)\leq min(x+1,C)$

综上所述， $\forall x \in Z$，$\min(x,C) \leq \min(x+1,C)$ 为真

Q.E.D

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[101],n,h;
inline int judge(int k) {
	int tot=k;
	for(register int i=1;i<n;++i) {
		tot+=min(k,a[i+1]-a[i]); //按式子暴力大膜你 
	}
	return tot;
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) {
		scanf("%lld%lld",&n,&h);
		for(register int i=1;i<=n;++i) scanf("%lld",a+i);
		int l=0,r=h+1; //l,r正常二分上下界 
		while(l<=r) {
			//传统的二分答案模板 
			int mid=(l+r)>>1,v=judge(mid);
			if(v>=h) r=mid-1;
			if(v<h) l=mid+1;
		}
		printf("%lld\n",l);
	}
}
```

---

## 作者：智子 (赞：0)

## 题意

Monocarp 要斩杀一头巨龙，巨龙的血量为 $h$。Monocarp 可以发动 $n$ 次攻击，每次攻击发动于时间 $a_i$，持续时间 $k$ 秒，每持续 $1$ 秒就会让巨龙的血量 $-1$。如果两个攻击的间隔小于 $k$，后一个攻击发动时会停止前一个攻击的效果。

Monocarp 想知道斩杀这头巨龙的 $k$ 的最小值是多少。

## 思路

如果 $k$ 可以斩杀巨龙，那么 $k + 1$ 肯定也可以，所以我们可以直接愉快地二分。

`check` 时我们依次扫描每个 $a_i$，“结算”上一次攻击带来的伤害。第 $i$ 个攻击的持续时间是 $[a_i, \min(a_i + k - 1, a_{i + 1} - 1)]$，所以伤害就是 $\min(a_i + k - 1, a_{i + 1} - 1) - a_i + 1$，总伤害就是 $\sum_{i = 1}^n \min(a_i + k - 1, a_{i + 1} - 1) - a_i + 1 $，如果总伤害大于或等于 $h$，`check` 函数返回 `true`。

## 代码

```cpp
#include<cstdio>
using namespace std;

const int MAXN = 100 + 5;

long long a[MAXN];
int n;
long long h;

bool check(long long mid) {
    long long last = 0, sum = 0;
    for(int i = 1; i <= n; i++) {
        if(last >= a[i]) {
            last = a[i] - 1;
        }
        if(i >= 2) {
            sum += (last - a[i - 1] + 1);
        }
        last = a[i] + mid - 1;
        if(sum >= h) {
            return true;
        }
    }
    sum += (last - a[n] + 1);
    return sum >= h;
}

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%d%lld", &n, &h);
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        long long l = 1, r = h, ans = -1;
        while(l <= r) {
            long long mid = (l + r) / 2;

            if(check(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}

```

---

## 作者：Rnfmabj (赞：0)

## 题意

给定 $n$ 个时间点 $a1,a2,…an$ ，一个整数 $h$ 表示目标分数。

每个时间点向后覆盖 $k$ 秒，总得分即为总覆盖时间。注意重复覆盖只记一次。

求使得总得分不小于 $h$ 最小的 $k$ 。

##

（来自教练不让熬夜打CF的怨念……）

为了避免每次都要 $O(n)$ 扫一遍判覆盖，我们从小到大枚举区间即可。

首先差分，得到 $n-1$ 个时间区间。然后将这些区间排序。

从小到大枚举区间，先判断把这个区间拉满能不能超过 $h$ ，如果可以就直接在这个区间求解，不行就拉满这个区间，然后枚举下一个区间。

~~然后有个可能不算毒点的毒点，就是你可能把每个区间拉满都不行~~，这时候就要特判，直接输出目标得分-首尾时间之差，即 $h-(an-a1)$ 。

~~啊对了别忘了可以直接用除法求解，别觉得这题只是T3就不会卡你时间~~

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R read()
using namespace std;
inline ll read(){
	ll s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
inline void write(ll x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10),x%=10;
    putchar('0'+x);
}
ll T,n,h,a[105],b[105];//测试数据组数，n，h，时间点，区间 
int main(){
	T=R;
	while(T){
		n=R;h=R;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));//多组数据别忘了这俩…… 
		for(ll i=1;i<=n;i++)a[i]=R;
		for(ll i=1;i<n;i++)b[i]=a[i+1]-a[i];//手动处理差分 
		sort(b+1,b+n);//按区间长度排序 
		ll as=0,flag=0;//先前已经覆盖的长度，特判 
		for(ll i=1;i<n;i++){
			ll x=(n-i+1)*b[i];//直接拉满区间 
			ll ans=0;
			if(as+x>=h){//判断是否有解 
				if(as+x>h){
					ans+=(as+x-h)/(n-i+1);
					x-=ans*(n-i+1);//求解 
				}
				if(as+x<h)ans--;//防止整除带来的减过头。eg：样例第四组 
				write(b[i]-ans);
				cout<<endl;
				flag=1;
				break;
			}
			as+=b[i];//拉满区间 
		}
		if(!flag){//所有区间都不够，直接求解 
			write(h-(a[n]-a[1]));
			cout<<endl;
		}
		T--;
	}
	return 0;
}

```


---

