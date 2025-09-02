# Subway Pursuit

## 题目描述

### 题目大意：
交互题

在 $1$ 到 $n$ 里有一个运动的点，要求找到这个点，每次可以查询一个区间内有没有这个点，每次这个点往左或者往右移动 $0$ 到 $k$ 个位置，要求要在 $4500$ 次查询内找到这个点的位置。

## 样例 #1

### 输入

```
10 2

Yes

No

Yes

Yes
```

### 输出

```
3 5

3 3

3 4

5 5
```

# 题解

## 作者：Dispwnl (赞：5)

一道可爱的交互题

首先这道题可以用二分缩小范围，把范围缩小到一个合适的~~看心情~~范围的范围内

然后就可以$rand$一个这个区间内的数，判断是不是，不是的话肯定会增加范围，如果超过这个范围就继续二分缩小，重复这个过程

为什么这样能找到正确答案呢？假设$rand$了$t$次，合适区间长度为$l$，那么找到正确答案的概率大约是$1-(\frac{l-1}{l})^t$

$t$最大能达到$4000+$这样子，这个概率什么概念呢？就是给你几十个球，让你抓$4000$多次来找到一个指定的球，显然基本上就是十拿九稳的事了

然而一个真正的非酋是不会相信概率这些东西的![](https://a-failure.github.io/img/study/feiqiu.png)

代码：
```
# include<iostream>
# include<cstring>
# include<cstdlib>
# include<cstdio>
# include<ctime>
# include<algorithm>
# define LL long long
using namespace std;
LL n,L,R;
int k;
char a[10];
bool query(LL l,LL r)
{
	cout<<l<<" "<<r<<endl;
	fflush(stdout);
	scanf("%s",a);
	if(a[0]=='Y') return 1;
	return 0;
}
int main()
{
	srand(time(0));
	cin>>n>>k,L=1,R=n;
	while(1)
	{
		while(R-L>50)
		{
			LL mid(L+R>>1);
			if(query(L,mid)) R=mid;
			else L=mid+1;
			L=max(1ll,L-k),R=min(n,R+k);
		}
		LL p=rand()%(R-L+1)+L;
		if(query(p,p)) return 0;
		L=max(1ll,L-k),R=min(n,R+k);
	}
	return 0;
}
```

---

## 作者：Nicrobot (赞：2)

其他题解关于策略讲得其实挺详细，这里重点讲讲为什么这样做很对。

首先考虑二分确定点的大致位置，确定到一个长度为 $50$ 的区间 $[l,r]$。需要 $60$ 次左右操作。

由于机器人不断动，我们只能考虑随机询问点来确定位置。设在二分后已经进行了 $m$ 次询问，我们在 $[l-mk,r+mk]$ 中询问随机点，询问的长度为 $50+2mk$。

这个概率看起来极低但事实上还比较高。正难则反，只要猜对一次就行，考虑计算 $4440$ 次操作**全部**错误的概率，则能猜出答案概率即为 $1$ 减去它的值。若长度为 $len$ 每次错误的概率为 $\dfrac{len-1}{len}$，猜对概率

$$p=1-\prod_{i=1}^{4440}\dfrac{50+2ki-1}{50+2ki}$$

取 $k=10$，得概率约为 $31.9\%$，完全不能通过，但已经有点高了。

注意到当询问进行很久以后，进行询问很不优秀，不妨再进行二分把长度“拉回来”再在区间随机询问。当区间长度 $>300$ 时，不妨再在可能的这个区间中，用不到 $10$ 次二分确定精确到 $50$ 的大致位置，再进行猜测。

此时不好直接计算概率，可以写下如下代码：

```cpp
int cnt=4440,len=50;
double p=1;
while(cnt>=0){
	--cnt;
	p*=(double)(len-1)/(len);
	len+=20;
	//重点：
	if(len>300)len=50,cnt-=10;
}
cout<<fixed<<setprecision(10)<<(1-p)<<'\n';
//输出 0.9999999960
```

这样，失败概率约为 $4\times10^{-9}$，已经足够通过本题。

也可以尝试更加优秀的参数，例如调整重构的区间阈值长度，调整每次二分到的长度，都能取得更优的操作次数。

实测，使用比较好的参数，~~配合好的运气~~，能在询问限制为 $1000$ 时通过这道题的大概 $150$ 个测试点。

但是，只要别太丑就能过。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, k;
ll cnt = 4500;
mt19937 rnd(time(0) * (unsigned long long)(new char));

bool ask(ll l, ll r) {
	l = max(l, 1ll);
	r = min(r, n);
	--cnt;
	if (cnt < 0) {
		cout << "Miao, I can't solve it.\n";
		exit(0);
	}
	cout << l << ' ' << r << endl;
	string s;
	cin >> s;
	return (s == "Yes");
}

ll rndll() {
	return rnd();
}

ll rs(ll l, ll r) {
	l = max(l, 1ll);
	r = min(r, n);
	return (rndll() % (r - l + 1)) + l;	
}

int main() {
	cin >> n >> k;
	ll l = 1, r = n;
	while (r - l + 1 > 50) {
		ll mid = (l + r) / 2;
		if (ask(l, mid)) l = max(1ll, l - k), r = min(n, mid + k);
		else l = max(1ll, mid - k), r = min(n, r + k);
	}
	while (cnt > 0) {
		while (r - l + 1 > 50) {
			ll mid = (l + r) / 2;
			if (ask(l, mid)) l = max(1ll, l - k), r = min(n, mid + k);
			else l = max(1ll, mid - k), r = min(n, r + k);
		}
		while (r - l + 1 <= 300) {
			ll t = rs(l, r);
			if (ask(t, t)) {
				return 0;
			}
			l = max(l - k, 1ll);
			r = min(r + k, n);
		} 
	}
	cout << "Miao, I can't solve it.\n";
	return 0;
}

```

---

## 作者：MspAInt (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1039B)

好题！！！狠狠地赞了！！！1

把这个答案点称为 bot。

我们发现 bot 的行动轨迹极其难以预测，因此使用人类智慧算法——盲猜。

bot 走得非常慢，我们可以二分确定出其移动到的大致区间（$60$ 次左右操作）：

```cpp
while(l+100<r){
    ll mid=l+r>>1;
    if(query(l,mid))l=max(l-k,1ll),r=min(mid+k,n);
    else r=min(r+k,n),l=max(1ll,mid-k);
    op--;
}
```

左右端点加减 $k$ 是为了保证 bot 始终走不出区间，`op` 是目前剩下的操作次数。

接下来 bot 就会乱动了，开始随机猜点（$50$ 次左右操作）。

但随着猜点次数越来越多，其可能移动到的区间范围越来越大，我们的正确率也越来越小。

因此我们在区间长度大于 $10^3$ 时，进行上面的二分重新收敛区间长度为 $100$ 以下（此时只要二分 $10$ 次左右）。

```cpp
while(r-l<1000){
    ll p=l+qpow(rand(),rand(),r-l+1);
    if(query(p,p))return 0;
    l=max(l-k,1ll);r=min(r+k,n);
    op--;
}
```

这样不停地重构、猜点，正确率非常之高（大约为 $99.9955\%$），可以自行用程序计算验证。

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,l,r,k;
int op=4500;
bool query(ll x,ll y){
    printf("%lld %lld\n",x,y);
    fflush(stdout);
    string str;
    cin>>str;
    return str=="Yes";
}
ll qpow(int x,int y,ll mod){
    ll ret=1;
    while(y){
        if(y&1)ret=ret*x%mod;
        y>>=1;x=1ll*x*x%mod;
    }
    return ret;
}
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    srand(time(0));
    scanf("%lld%lld",&n,&k);
    l=1;r=n;
    while(op>60){
        while(l+100<r){
            ll mid=l+r>>1;
            if(query(l,mid))l=max(l-k,1ll),r=min(mid+k,n);
            else r=min(r+k,n),l=max(1ll,mid-k);
            op--;
        }
        while(r-l<1000){
            ll p=l+qpow(rand(),rand(),r-l+1);
            if(query(p,p))return 0;
            l=max(l-k,1ll);r=min(r+k,n);
            op--;
        }
    }
    // system("pause");
    return 0;
}
```

这份代码可以通过调参来获得更优秀的表现，大家可以自行尝试。

[record](https://www.luogu.com.cn/record/133096986)

---

## 作者：LTb_ (赞：1)

> [Link](<https://codeforces.com/contest/1039/problem/B>)
>
> Author: LTb

一道挺有意思的交互

看自己的代码评测的时候有一种看着自己的孩子的感觉（？

发现值域很大但是这个点每次变化的幅度很小（$k \le 10$）于是想到二分这个点所在的区间，缩小到一定范围之后在这个区间内随机询问位置。

区间大小理论最小值应该是 $4k$ ，你可以取 $5k$ 或者 $6k$ 或者直接取 $50 / 60$，$k$ 很小所以无论怎么搞都无所谓（

我的代码也许有不必要的特判（

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,k;
string s;
int query(int l,int r){
	cout<<l<<' '<<r<<endl;
	cin>>s;
	if (s=="Yes") return 1;
	else return 0;
}

signed main()

{
	random_device rd;
	cin>>n>>k;
	if (n==1){
		cout<<"1 1"<<endl;
		return 0;
	}

	int l=1,r=n;
	while (1){
		l=max(1ll,l-k*2);r=min(n,r+k*2);//这里理论上不需要 k*2 只需要 k，但是这样会导致区间调整的太慢
		int mid=l+r>>1;
		int tmp=query(l,mid);
		if (tmp==1) r=mid;
		else l=mid+1;

		if (l==r && k==0){
			cout<<l<<" "<<l<<endl;
			cin>>s;
			return 0;
		}

		if (l+6*k>=r){
			tmp=rd()%(r-l+1)+l;	
			int res=query(tmp,tmp);
			if (res==1) return 0;
		}
	}
	return 0;
}
```



---

## 作者：RDFZchenyy (赞：0)

## 题目大意

有 $n$  个站点（$n\le10^{18}$）和一个失控的地铁。你应通过至多 $4500$ 次询问找到地铁的当前位置。

每一次询问你可以给定 $l,r$：询问地铁是否在站点 $[l,r]$ 之中。每次询问后地铁将向左或移动至距当前位置 $k$ 站以内的站点（$1\le k\le 10$），即从 $x$ 移动至 $[\max(1,x-k),\min(n,x+k)]$ 中的任一站点。

你可以猜测地铁当前位于站点 $x$，通过询问 $l=x,r=x$，若交互库返回是，你应结束程序，随后交互结束。

注意：交互库不是自适应的。

## 按步分析

### 问题 #1

我们能不能精确确定最终结果的答案？这说明什么？
### 解答 #1

不能。$k$ 的随机性使得两步之间没有很强的关联性。比如 $n=11,k=10$ 的时候，每一步结束后下一步的位置都无法确定。
这说明我们可能需要随机猜测。

### 问题 #2

不考虑 $k$ 的影响（即假设 $k=0$ 时），能不能快速地找到地铁的位置？

### 解答 #2

可以，我们二分地询问即可找到地铁的位置。

### 问题 #3

假设我们已经确定了地铁现在在区间 $[a,b]$，我们能否知道地铁移动一次后到达的位置？
如果此时随机猜测一次，成功率怎样？这说明什么？
如果地铁移动一次后随机猜测一次，成功率怎样？这说明什么？
### 解答 #3

可以，新的位置必然是 $[\max(1,l-k),\min(1,r+k)]$ 中的一站。
移动前猜测成功率为 $\frac{1}{b-a+1}$。这说明在随机猜测前，我们需要把区间缩短到一定长度。
移动后猜测成功率可能达到 $\frac{1}{b-a+2k+1}$，其会减小一定量。这说明在随机猜测后，我们可能需要随时调整区间。

结合问题 2 与解答 2，我们还能知道缩短区间时应当使用二分的做法。

## 思路分析

我们不妨重复以下流程：

+ 用二分缩短当前区间到一定长度 $L$ 以下，注意二分时区间可能变化；
+ 在区间中进行一次随机猜测，注意在其后更新区间。

可以看出 $L$ 的值只对第一次二分的过程和其后的随机猜测有影响，故选择较小的 $L=4k$。

> 这里请读者注意，原长为 $K$ 的区间最劣仅能变化为 $K'=\frac{K}{2}+2k$，这个值应当缩小，即范围应当缩小。故我们至少取 $K'=K=\frac{K}{2}+2k$，此时可得 $K=4k$。

计算随机猜测的准确度，我们至少进行了 $2000$ 次随机询问（每两次询问分别是随机猜测和二分缩小区间，故实际上可能还会比这多出 $200$ 左右），每次长度至多 $4k=40$，故 $2000$ 次询问后错误概率仅为 $(1-\frac{1}{40})^{2000}=1\times 10^{-22}$。

> 这个概率约是雷雨天时你走进彩票店后连续买到双色球的一等奖和刮出刮刮乐的一等奖，开心之余刚走出门就被闪电击中的概率。
> 然而作者提交后仍错了一次。这种情况建议改改种子。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,k,av;
long long l,r;

bool sts=false;

bool query(long long l,long long r){
    string s;
    cout<<l<<" "<<r<<endl;
    cin>>s;
    if(l==r&&s=="Yes"){
        exit(0);
    }
    return s=="Yes";
}

bool query(long long x){
    string s;
    cout<<x<<" "<<x<<endl;
    cin>>s;
    if(s=="Yes"){
        exit(0);
    }
    return s=="Yes";
}

int main(){
    ios::sync_with_stdio(false);
    
    cin>>n>>k;
    av=4*k;
    l=1;
    r=n;
    
    srand(139);
    
    while(!sts){
	    // binary-search >-<
        while(r-l>av){
            long long mid=(l+r)>>1;
            if(query(l,mid)){
                r=mid;
            }else{
                l=mid+1;
            }
            
            // expand <->
            l=max(1ll,l-k);
            r=min(n,r+k);
        }
        
		// random-guess
        while(r-l<=av){
            sts=query(rand()%(r-l+1)+l);
            if(sts){
                break;
            }
            
            // expand <->
            l=max(1ll,l-k);
            r=min(n,r+k);
        }
    }
    
    return 0;
}
```

---

## 作者：野生林登万 (赞：0)

## 思路

虽然咱很喜欢随机化，但是没想到这题也能随机化啊（）。其实稍微想想容易清楚就是随机化。  

首先观察题目一个裸的二分，但是位置会随机移动。假设我们确定它所在区间的长度为 $len$，那么我们每次二分可以使得区间长度减少 $\frac {len} 2$，但是又会增加 $2 \times k$（他可能从左边走出区间或者右边走出区间，每次最多走出 $k$ 距离）  

那么当长度为 $4 \times k$ 的时候我们就卡死了，因为每次减少的长度为 $2 \times k$，而增加的长度也是 $2 \times k$，确定区间没有变。  

我们观察到这个 $k$ 实际上是非常小的，所以......自信随机化！每次当确定长度小于一个你定的值（这个地方有讲究，下面可以说一下）的时候，就随机选择区间中的一个值 $x$ 询问 $[x,x]$，如果成功就结束程序，失败的话就继续二分（记得扩大区间 $2 \times k$，因为执行了一次操作）直到区间长度小于我们定的值，继续随机化。  

依旧考虑正确性，假设 $n = 10 ^ {18},k = 10$ 并且使得区间长度为 $40$（最小可确定长度），最开始我们会花费 $60$ 次找到目标区间，然后每次有 $\frac 1 {40}$ 的概率猜对，如果失败我们会花费 $5$ 次重新把区间长度定位回 $40$，所以我们保守（偏小）可以执行 $800$ 多次操作，错误率仅有 $2 \times 10^{-10}$，可以忽略  

另外理论上最低长度是 $40$，不过有更优秀的长度！根据以下程序，我们发现 $59$ 才是最优区间长度，错误率仅有 $2 \times 10 ^ {-33}$。  

```cpp
const int times = 4400;
inline double Solve(int minLen){
	int cnt = 0;
	double ans = 1;
	long long len = minLen + 20;
	while(len > minLen){
		len /= 2;
		len += 20;
		cnt++;
	}
	double poss = (double(minLen-1) / double(minLen));
	for(int i = 1;i <= times / cnt;i++){
		ans *= poss;
	}
	return ans;
}
```  

这是因为从 $60$ 次变回 $40$ 次的代价太高，我们如果调整长度，虽然单次错误率（底数）会变大，但是尝试的次数（指数）也会变大，而指数的影响比起底数要大一点，所以如果这道题稍微卡一下的话可以列一个刚才的测试程序打表看看哪个长度更优（不过为了降低随机性，这种题目一般无论什么参数正确率都很高，理论上来讲正确做法的参数不太离谱都能过）  

## 代码

```cpp
#include<bits/stdc++.h>
#define Akano 1
#define pure__Elysia 0
#define loves ^
using namespace std;
using ll = long long;
ll n,k;
mt19937_64 rng(time(0));
inline ll rd(ll l,ll r){
	return (rng() % (r - l + 1)) + l;
}
inline bool Get(ll l,ll r){
	cout<<l<<" "<<r<<endl;
	string res;
	cin>>res;
	if(res == "Yes"){
		if(l == r)exit(0);
		return true;
	}
	return false;
}
int main(){
	cin>>n>>k;
	ll l = 1,r = n+1;
	while(true){
		l -= k,r += k;
		l = max(l,1ll),r = min(r,n);
		while(l + 4 * k < r){
			const ll mid = (l + r) >> 1;
			if(Get(l,mid)){
				r = mid;
			}else{
				l = mid + 1;
			}
			l -= k,r += k;
			l = max(l,1ll),r = min(r,n);
		}
		const ll now = rd(l,r);
		Get(now,now);
	}
	return not(Akano loves pure__Elysia);
}
```

~~励志打完所有交互题~~

---

