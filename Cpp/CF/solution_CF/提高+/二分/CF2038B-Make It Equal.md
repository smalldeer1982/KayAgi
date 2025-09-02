# Make It Equal

## 题目描述

给定一个长度为 $n$ 的整数数列 $a$，下标从 $1$ 到 $n$。

你可以进行任意次（可以为 $0$ 次）以下操作：选择一个满足 $1\le i\le n$ 的 $i$，使 $a_i$ 减少 $2$，$a_{(i\mod n)+1}$ 增加 $1$。

现询问是否有一种操作方案，使得 $a_1=a_2=\dots=a_n=p$ 且 $p\ge 0$，若有，输出最少操作次数，否则输出 $-1$。

## 样例 #1

### 输入

```
3
2
1 1
3
1 3 2
4
2 1 2 6```

### 输出

```
0
-1
3```

# 题解

## 作者：ELECTRODE_kaf (赞：7)

注意到对每一个数进行一个单位的操作相当于给每一个数减 $1$。所以答案具有单调性，可以二分目标数。

问题变为判断是否可能使所有数变为这个目标数。

考虑对于一个大于目标的数，不对它进行操作是不可能达到目标的，因为前面的数的操作只会增加它。而且对它操作时，如果不把它减少到不大于目标，我们就仍然需要继续操作，所以每一次操作必须减少到达标或小于标准。

若这个数和标准的差值是偶数就直接调整至达标即可；若是奇数则减至比标准小 $1$。特判标准为 $0$ 且当前数为奇数的情况，此时需要把这个数变为 $1$。

这里需要一个特判：若这个数 $<2$，那么无法进行操作。

重复上面这个过程直到无法继续操作即可，由于每次被操作数都减半，所以一圈的复杂度近似 $O(\log V)$，其中 $V$ 是被操作数的最大值。

```cpp
const ll N=2e5+10;
ll Q,n,a[N],st,_a[N];

bool done(ll tg){
	rep(i,2,n){
		if(a[i]!=a[1]) return 0;
	}
	
	return 1;
}

bool check(ll tg) {
//	cout<<"check("<<tg<<")\n";
//	pause;
	
	rep(i,1,n) _a[i]=a[i];

	ll _st=st;
	st=0;//记录步数 

	while(1) {
//		cout<<"a[]:";
//		
//		rep(i,1,n) cout<<a[i]<<' ';
//		
//		endl;
//		pause;
		bool flag=0;
		
		rep(i,1,n) {
			if(a[i]<=tg or a[i]<2) ctn;

			ll val;

			if((a[i]-tg)%2 and tg!=0) val=(a[i]-tg+1)/2;
			else val=(a[i]-tg)/2;

			a[i%n+1]+=val;
			a[i]-=val*2;
			st+=val;
			
			if(val) flag=1;
		}
		
		if(done(tg) or flag==0) break;
	}

	bool ret=done(tg);
	
	if(ret) {
//		cout<<"return 1\n";
		
		rep(i,1,n) a[i]=_a[i];
		
		return 1;
	}else{
//		cout<<"return 0\n";
		
		rep(i,1,n) a[i]=_a[i];
		
		st=_st;
		return 0;
	}
}

int main() {
	cin>>Q;

	count(Q) {
		st=-1;
		cin>>n;
		ll max1=-1;

		rep(i,1,n) {
			cin>>a[i];
			update(max1,a[i],max);
		}
		
		if(done(a[1])){
			cout<<"0\n";
			ctn;
		}
		
		ll l=0,r=max1,ans=-1;

		while(l<=r) {
//			cout<<"l="<<l<<",r="<<r<<'\n';
//			pause;
			ll mid=(l+r)/2;

			if(check(mid)) {
				ans=mid;
				l=mid+1;
			} else r=mid-1;
		}

		cout<<st<<'\n';
	}
}
```

---

## 作者：TTpandaS (赞：4)

一个神奇做法，应该没有一样的。

首先考虑二分答案，那么就可以得到最后所有数的值，设为 $x$，令 $g_i=a_i-x$，设 $f_i$ 表示第 $i$ 个位置要被操作的次数（第 $i$ 个位置被操作是指选择 $i$ 将 $a_i-2,a_{i \% n + 1}+1$），那么可以得到 $f_i=2f_{i \% n +1}-g_{i \% n +1}$。有 $n$ 个未知数和 $n$ 个方程，所以可以解出 $f_n=\dfrac{\sum_{i=1}^{n}2^{i-1}g_i}{2^n-1}$，然后判断 $f_n$ 是否为整数，接着带回去算出每个 $f_i$ 是否为非负整数即可。

关键是 $n \leq 2\times 10^5$，无法直接求出 $\dfrac{\sum_{i=1}^{n}2^{i-1}g_i}{2^n-1}$，但是这个值并不会太大，所以可以取两个互质的模数，判断在两个不同的模数意义下 $\dfrac{\sum_{i=1}^{n}2^{i-1}g_i}{2^n-1}$ 的值是否相同即可。

实测采用 $10^9+7$ 和 $10^9+9$ 可过。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod1=1e9+7,mod2=1e9+9;
int T=1;
int n,a[N];
int g[N],f[N];
int p1[N],p2[N];
int qpow(int x,int p,int mod){
	int res=1;
	while(p){
		if(p&1){
			res=res*x%mod;
		}
		x=x*x%mod;
		p>>=1;
	}
	return res;
}
bool check(int mid){
	for(int i=1;i<=n;i++){
		g[i]=a[i]-mid;
	}
	int res1=0,res2=0;
	for(int i=1;i<=n;i++){
		res1=(res1+(g[i]+mod1)%mod1*p1[i-1]%mod1)%mod1;
		res2=(res2+(g[i]+mod2)%mod2*p2[i-1]%mod2)%mod2;
	}
	res1=res1*qpow(p1[n]-1,mod1-2,mod1)%mod1;
	res2=res2*qpow(p2[n]-1,mod2-2,mod2)%mod2;
	if(res1!=res2){
		return 0;
	}
	if(res1<0){
		return 0;
	}
	f[n]=res1;
	for(int i=n-1;i>=1;i--){
		f[i]=2*f[i+1]-g[i+1];
		if(f[i]<0){
			return 0;
		}
	}
	return 1;
}
void solve(){
	cin>>n;
	int sum=0;
	p1[0]=p2[0]=1;
	for(int i=1;i<=n;i++){
		p1[i]=p1[i-1]*2%mod1;
		p2[i]=p2[i-1]*2%mod2;
		cin>>a[i];
		sum+=a[i];
	}
	int l=0,r=sum/n,res=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			res=mid;
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	if(res==-1){
		cout<<-1<<'\n';
		return;
	}
	cout<<sum-res*n<<'\n';
}
signed main(){
	cin>>T;
	while(T--){
		solve(); 
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF2038B Make It Equal](https://www.luogu.com.cn/problem/CF2038B)

# 题意简述

这东西好久没写了啊。

阿瓦在一个幻想王国里。

他走在草坪上，发现有 $1 \le n \le 2 \times 10^5$ 个数字精灵祝他生日快乐。

阿瓦非常开心。因为最多可能会有 $2 \times 10^5$ 个精灵为他庆生。

但是，对于每个数字精灵都有一个饱食度 $1 \le a_i \le 10^9$，如果有任意两个数字精灵的饱食度不同，那么他们就会不开心。

不过此时，机智的阿瓦想到了一个策略：那就是跟数字精灵们玩一个游戏。顺便趁这个时候改变数字精灵的饱食度状况。

这个游戏的实质内容就是将这 $n$ 个数字精灵围成一个圈，你可以进行对相邻的两个数字精灵更改饱食度的一次操作，具体的，将左边的数字精灵的饱食度 $-2$，将右边的数字精灵的饱食度 $+1$。

你需要求出最少的操作次数。

# 解题思路

发现这东西是可以二分答案的。

为啥呢？

你发现你将所有的人做一次操作，就是全局减一。

那么你可以将所有的 $a_i$ 尽量减少到最小的 $a_i$，这么做操作，你感性理解，发现这种操作的数量一定不多，为啥呢？你发现一次整体操作之后，那么它们所有数字的值可能都只会推到一个数字上，其余数字的差将会不超过 $1$，那么你会发现，后面几次操作都在调整最后一个数字，而你最后一个数字是持续推动的，所以操作次数一定小于 $\log n$ 次，直接暴力做就行了。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define cll const ll
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define forll(i,a,b,c) for(re ll (i)=(a);i<=(b);(i)+=(c))
#define forrr(i,a,b,c) for(re ll (i)=(a);i>=(b);(i)-=(c))
#define forL(i,a,b,c) for(re ll (i)=(a);((i)<=(b)) && (c);(i)++)
#define forR(i,a,b,c) for(re ll (i)=(a);((i)>=(b)) && (c);(i)--)
#define forLL(i,a,b,c,d) for(re ll (i)=(a);((i)<=(b)) && (d);(i)+=(c))
#define forRR(i,a,b,c,d) for(re ll (i)=(a);((i)>=(b)) && (d);(i)-=(c))
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
ll _t_;
void _clear(){}
ll n;
ll a[1000010];
ll L,R;
ll b[1000010];
ll nxt(ll x)
{
    if(x==n)
        return 1;
    return x+1;
}
ll check(ll Mid)
{
    ll sum=0;
    forl(i,1,n)
        b[i]=a[i];
    forl(_,1,40)
        forl(i,1,n)
            if(b[i]>Mid)
            {
                ll need=(b[i]-Mid+1)/2;
                sum+=need;
                b[i]-=need*2;
                b[nxt(i)]+=need;
            }
    forl(i,1,n)
        if(b[1]!=b[i] || b[i]<0)
            return 1e18;
    return sum;
}
void solve()
{
    _clear();
    cin>>n;
    forl(i,1,n)
        cin>>a[i];
    L=0,R=2e9;
    while(L<R)
    {
        ll Mid=(L+R+1)/2;
        if(check(Mid)!=1e18)
            L=Mid;
        else
            R=Mid-1;
    }
    if(check(L)!=1e18)
        cout<<check(L)<<endl;
    else
        cout<<-1<<endl;
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
    cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：RoamingDuck (赞：1)

### 题意简述
每次让 $a_i$ 等于 $a_i-2$，并将 $a_{i\mod n}$ 加上 $1$，求最少次数使得每个元素都相等。 **都是非负整数才可以。**

### 思路
二分。

观察得到：
- 数组相等时，每个元素操作一次，它仍是相等的。

- 一个数组能通过操作使得它们相等，且最大相等的非负整数为 $x$，那么一定能得到一个以 $x-1$ 相等的数组，一直到 $x=0$，因为要求其非负。

重点在于设计检查函数 $\operatorname{check}(x)$，令 $x$ 为使得数组相等的最大元素。

对于 $a_i\le x$，便不用操作；当 $a_i\gt x$ 时，就要把它降到 $a_i\le x$，设 $y$ 为把 $a_i$ 操作成 $x$ 的次数，那么就可以在 $a_i-x$ 为偶数时对 $a_i$ 操作 $\frac{a_i-x}{2}$，奇数时便可以先对 $a_{i-1}$ 操作一次，使得 $a_i$ 减去一，再操作 $\frac{a_i-x}{2}$ 次就可以了。

实现起来，个人认为时间复杂度应该为 $O(n\log a)$（对于每个测试点）。

---

## 作者：IdnadRev (赞：1)

可以发现问题确有单调性，于是我们二分答案，问题变为判断一个序列是否可以操作到 $0$。

我们虽然能解出每个位置要操作多少次，但是数太大了算不了，可以考虑一些更加暴力的手段。

我们从前往后，对每个位置操作到不能操作为止。然后你可以发现基本不需要操作几次序列就都小于等于一了，那么剩下的所有数必须全零或者全一才行，可以直接判断。

我赛时认为要操作 $O(\log V)$ 轮（大概是每次除二），但是仔细想想可以意识到操作 $O(1)$ 轮其实就足够了（第一轮基本就推平了，剩下的部分只会往后走 $O(\log V)$ 步），因此复杂度是 $O(n\log V)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=500005;
int n,m,T,ans,flg;
int a[maxn];
long long b[maxn];
long long sum;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n),sum=0;
		for(int i=1; i<=n; i++) {
			scanf("%d",&a[i]);
			sum+=a[i];
		}
		int L=-1,R=1000000001;
		while(L+1<R) {
			int mid=(L+R>>1);
			for(int i=1; i<=n; i++)
				b[i]=a[i]-mid;
			while(1) {
				long long flg=0;
				for(int i=1; i<=n; i++)
					if(b[i]>=2) {
						long long c=b[i]/2;
						b[i]-=2*c,b[i%n+1]+=c;
						flg|=c;
					}
				if(flg==0)
					break;
			}
			int tag=1;
			for(int i=1; i<=n; i++)
				tag&=b[i]==b[i%n+1],tag&=b[i]>=0;
			if(tag)
				L=mid;
			else R=mid;
		}
		if(L==-1)
			puts("-1");
		else printf("%lld\n",sum-1ll*n*L);
	}
	return 0;
}
```

---

## 作者：xueruhao (赞：0)

~~感觉这题评蓝有点虚高，当然也有可能是我对题目难度不敏感。~~
## 题意概述
给你一个大小为 $n$ 的整数数组 $a$。数组元素的编号从 $1$ 到 $n$ 。

可以执行以下任意次数的操作（可能为 $0$ 次）：从 $1$ 到 $n$ 中选择一个下标 $i$；将 $a_i$ 减少 $2$ 并将 $a_{(i \bmod n) + 1}$ 增加 $1$ 。

执行这些操作后，数组中的所有元素都应非负且相等。

需要计算最少需要执行的操作次数。


## 解题思路
核心思路就是将数组所有元素通过操作变为相等的最大值 $x$，并且寻找最合适的 $x$ 值。多模拟几组数据，可以观察到，对于任意一个数组，如果我们能够将其所有元素调整为一个相等值 $x$，那么也一定可以调整为比 $x$ 小的所有值，于是不难想到数据具有二分性，可以通过二分来找到最小的 $x$。

思考如何检查，其核心是逐步将数组中的元素调整到不超过目标值 $x$。具体地，遍历数组中所有大于 $x$ 的元素，通过一系列操作将其变为 $x$ 或更小。对于一个值 $a_i$，如果其大于 $x$，我们需要通过减半操作逐步缩小它和 $x$ 的差距。每次操作将 $a_i$ 减去其值的一半，直到它小于等于 $x$。这种减半操作有效地降低了大数的值，从而缩短了整体的调整次数。

时间复杂度 $\text{O}(n \log V)$，其中 $V$ 为值域。


[link](https://codeforces.com/contest/2038/submission/292726109)

---

## 作者：Prophesy_One (赞：0)

首先注意到对所有数操作 $1$ 次对答案的判定不变。于是我们可以随意操作到所有数相等，再调整到最优状态，不妨直接考虑将所有数变成 $0$。

扫的过程中，如果某个时刻已经符合条件就退出；如果某个时刻不合法且都无法操作则无解。

实现过程中，每个数每次除以 $2$，一个数最多对 $\log V$ 次操作有贡献，时间复杂度 $\text{O}(n \log V)$。

[link](https://codeforces.com/contest/2038/submission/292186089)

---

