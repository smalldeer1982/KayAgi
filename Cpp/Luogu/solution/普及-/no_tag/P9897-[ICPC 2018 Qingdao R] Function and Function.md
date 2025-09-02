# [ICPC 2018 Qingdao R] Function and Function

## 题目描述

如果我们定义 $f(0) = 1$，$f(1) = 0$，$f(4) = 1$，$f(8) = 2$，$f(16) = 1$ …… 你知道函数 $f$ 意味着什么吗？

其实，$f(x)$ 计算的是 $x$ 中每个数字所产生的封闭区域的总数。下表显示了每个数字产生的封闭区域数：

![](https://cdn.luogu.com.cn/upload/image_hosting/sdv14tzu.png)

例如，$f(1234) = 0 + 0 + 0 + 1 = 1$，$f(5678) = 0 + 1 + 0 + 2 = 3$。

现在，我们用以下等式定义递归函数 $g$： 

$$\begin{cases} g^0(x) = x \\ g^k(x) = f(g^{k-1}(x)) & \text{if } k \ge 1 \end{cases}$$

例如，$g^2(1234) = f(f(1234)) = f(1) = 0$，$g^2(5678) = f(f(5678)) = f(3) = 0$。

给定两个整数 $x$ 和 $k$，请计算 $g^k(x)$ 的值。

## 样例 #1

### 输入

```
6
123456789 1
888888888 1
888888888 2
888888888 999999999
98640 12345
1000000000 0```

### 输出

```
5
18
2
0
0
1000000000```

# 题解

## 作者：ydzr00000 (赞：4)

### 题面

令 $f(x)$ 表示 $x$ 中各个数位上的数字的封闭部分的数量，再令 $g^0(x)=x$，对于 $k\ge 1$ 满足 $g^k(x)=f(g^{k-1}(x))$，给定 $T$ 组 $x,k$，试求 $g^k(x)$。

$T\leq 10^5, x,k\leq 10^9$。

### 题解

首先让我们考虑 $g^1(x)$ 的值，因为 $8$ 的封闭部分最多（有 $2$ 个），所以 $g^1(x)$ 在 $x=888,888,888$ 时取到最大值，为 $18$。

再考虑 $g^2(x)$ 的值，因为 $0\leq g^1(x)\leq 18$，计算所有可能的 $g^2(x)$，可以发现 $0\leq g^2(x)\leq 2$。

再类推一次，可以得到 $0\leq g^3(x)\leq 1$。

在 $k\ge 3$ 的时候，$g^k(x)$ 不等于 $0$ 就会等于 $1$，事实上，可以发现之后的部分为 $0,1$ 交替的循环，因为 $f(0)=1,f(1)=0$。

于是最多循环 $3$ 次，若 $k\ge 3$ 的时候判断最后的值是 $0$ 还是 $1$ 即可。

我们可以认为暴力计算 $f(x)$ 的时间复杂度是 $\log_{10}x$，于是最终时间复杂度为 $\mathcal{O}(T\log_{10}x)$。

**注意一下 $f(0)=1$，一些写法可能使得 $f(0)=0$。**

---

## 作者：strcmp (赞：3)

本场比赛真正意义的签到。

注意到，$f(x)$ 的级别大概是 $\log x$ 的。

也就意味着对于一个数求 $f^{k}(x)$ 的操作，不需要进行 $k$ 次，大概就进行不到十次，就会收敛到一个很小的数。

然后你发现，$f^k(0 \dots 9)$ 中，$2 \dots 9$ 都会最终收敛到 $0$ 或者 $1$。而 $f(0) = 1$，$f(1) = 0$。

于是我们直接枚举 $i$ 计算 $f^i(x)$ 值，直到 $i = k$，或者 $f^i(x) = 0$ 或者 $f^i(x) = 1$。

此时，$f^k(x)$ 的值即为 $f^i(x) \text{ xor } ((k - i) \bmod 2)$。

时间复杂度大概是 $\Theta(\text{T} \log^* x)$ 的。

```cpp
#include <bits/stdc++.h>
#define fr first
#define sc second
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int maxn = 2e6 + 10;
const ll mod = 1000000007LL;
const ll inf = 1e18;
ll g(ll x) {
	if (x == 0) return 1;
	else if (x >= 1 && x <= 3) return 0;
	else if (x == 4) return 1;
	else if (x == 5) return 0;
	else if (x == 6) return 1;
	else if (x == 7) return 0;
	else if (x == 8) return 2;
	else return 1;
}
ll F(ll x) {
    if (x == 0) return 1;
	ll cnt = 0;
	while (x) cnt += g(x % 10), x /= 10;
	return cnt;
}
ll dfs(ll x, ll k) {
	for (ll i = 1; i <= k; i++) {
		x = F(x);
		if (x == 1 || x == 0) return x ^ (k - i) % 2;
	}
	return x;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		ll x, k;
		scanf("%lld%lld", &x, &k);
		printf("%lld\n", dfs(x, k));
	}
	return 0;
}
```

---

## 作者：Bobxing (赞：3)

这道题不是特别难，稍微动点脑子就出来了（~~我会告诉你们我花了很久在这道题上？~~）

首先，我们把 $a$ 数组定义好，设为定值也就是题目中的 $f(0)$ 到 $f(9)$，接着，再定义一个 $f$ 函数，来模拟题目中的函数计算方法，也就是把每一个数位加在一起就可以了。

接下来我们计算 $g^k(x)$，但是我们很容易发现时间复杂度为 $O(k)$，而 $k$ 的范围到 $10^9$，直接超时，所以，我们需要优化。

很容易发现，当计算到 $f(0)$ 或者 $f(1)$ 时，$f$ 函数的值会在 $0$ 和 $1$ 之间跳跃，而最终结果和 $k$ 和 $x$ 的奇偶性有关，可以分情况讨论（手推一下即可）：
- 当 $x$ 为奇数时，返回 $k\bmod2$。
- 当 $x$ 为偶数时，返回 $1-(k\bmod2)$即可。

综上，我们只用在计算结果等于 $0$ 或 $1$ 时加个特判即可。

如果有疑问，具体详见代码，也可单独私信哦：

```cpp
#include<iostream>
using namespace std;
#define ll long long
int a[] = { 1, 0, 0, 0, 1, 0, 1, 0, 2, 1 };
ll x, k, t;
ll f( int x )
{
	ll ans = 0;
	do
	{
		ans += a[ x % 10 ], x /= 10;
	} while( x );
	return ans;
}
ll g( int k, int x )
{
	while( k-- )
	{
		x = f( x );
		if( x == 0 ) return k % 2;
		if( x == 1 ) return !( k % 2 );
	}
	return x;
}
int main()
{
	cin >> t;
	while( t-- )
	{
		cin >> x >> k;
		cout << g( k, x ) << endl;
	}
	return 0;
}

```

---

## 作者：MicroSun (赞：2)

签到题。

$g$ 函数在 $x=0$ 或 $x=1$ 时会发生循环，将 $x$ 在 $0$ 和 $1$ 之间重复转换。为了防止这种无意义的计算，只需要用奇偶性进行特判。其余步骤依据题意模拟即可。

将一个大数变为 $x=0$ 或 $x=1$ 所需要的次数是 $\log(n)$ 级的，很明显时间复杂度符合要求。

```cpp
// Problem: T402231 [ICPC2018 Qingdao R] Function and Function
// LuoguUID: 514700 
// LuoguUserName: MicroSun

#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
const int mp[]={1,0,0,0,1,0,1,0,2,1};
int f(int x){
	int ans=0;
	while(x){
		ans+=mp[x%10];
		x/=10;
	}
	return ans;
}//依照题意写出f函数
int g(int k,int x){
	if(k==0) return x;
	while(k--){
		if(x==0) return (k+1)&1;//奇偶性特判，没有这行会TLE
		x=f(x);
	}
	return x;
}
void solve(){
	int x,k;
	cin>>x>>k;
	cout<<g(k,x)<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
    return 0;
}
```

---

## 作者：linxuanrui (赞：2)

不愧是签到题。

### 思路

不难发现，$f(x)$ 的值在 $0\le x\le 10^9$ 的情况下最大不会超过 $16$。

继续往下推：

$f(x)$ 的值在 $0\le x\le 16$ 的情况下最大不会超过 $2$。

$f(x)$ 的值在 $0\le x\le 2$ 的情况下最大不会超过 $1$。

$f(x)$ 的值在 $0\le x\le 1$ 的情况下最大不会超过 $1$。

……

也就是说，$g^k(x)$ 在 $k\ge3$ 的时候只有 $0$ 和 $1$ 两种取值。

接下来，考虑何时 $g^k(x)$（$k\ge3$）什么时候会为 $0$，什么时候会为 $1$。显然，

+ 当 $g^{k-1}(x)=0$，$g^k(x)=1$；

+ 当 $g^{k-1}(x)=1$，$g^k(x)=0$。

这就说明，当我们找到第一个满足 $g^t(x)=0$ 的 $t$，如果 $k-t\bmod2=1$，输出 $0$，否则输出 $1$；如果找不到就说明 $k<3$，暴力可过。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
typedef long long ll;
using namespace std;
int t,n,q,a[10] = {1,0,0,0,1,0,1,0,2,1};
int f(int x){
	int ans = 0;
	while(x){
		ans += a[x % 10];
		x /= 10;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n >> q;
		int ans = n;
		while(q-- && ans)ans = f(ans);
		cout << (ans ? ans : (q & 1 ? 0 : 1)) << endl;
	}
}
```

---

## 作者：h_rains (赞：1)

题意描述很清楚，这里就不给简要题意了。

首先题面要我们求的是 $g^k(x)$ 然而实际上就是求 $f^k(x)$ 然后我们观察到样例，容易发现它的下降速度是很快的。因为 $f(x)$ 最大为 $f(88888888)=16$ 所以我们只需要一次迭代它就会变得很小，然后当其下降为求 $f(0)$ 时，这时候我们记 $f^{k2}(x)=0,m=k-k2$ 容易观察到此后每次操作都是 $0\rightarrow 1\rightarrow 0 \rightarrow \cdots$ 所以当 $m$ 为偶数时，答案为 $0$ 否则答案为 $1$。注意一个特判就是如果 $k$ 很小可能我们还没有迭代为 $0$ 的时候就已经结束了，这时候我们直接输出即可。具体看代码吧。

```cpp
#include <bits/stdc++.h>

using namespace std;

int b[]={1,0,0,0,1,0,1,0,2,1};//0-9 每个数字的封闭区间个数。

int f(int x)//题面中的 f 函数
{
    int ans=0;
    while(x)//取出每一位数加上它的封闭区间个数
    {
        int y=x%10;
        ans+=b[y];
        x/=10;
    }
    return ans;
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n,k;
        cin>>n>>k;
        while(k!=0&&n!=0) n=f(n),k--;
        if(k==0) cout<<n<<endl;//特判 k 比较小的情况。
        else cout<<k%2<<endl;
    }
    system("pause");
}
```

---

## 作者：Ahws_rwhy (赞：1)

妥妥的签到题（下面的图像好 2b 呀）

思路：

通过笔算找出循环节，发现，$g$ 函数经过一定次数的递推一定会在 $0$ 和 $1$ 之间变换，所以循环内加判断提前结束递推即可（看剩下的操作次数是奇数还是偶数决定答案）。

代码：

```
	while(t--) {
		cin>>n>>m;
		if(n==0) {
			if(m%2==0) {
				n=0;
			}
			else {
			n=1;
		}
		} else {
			for(int i=1; i<=m&&n; i++) {
				n=g(n);
				if(n==0) {
					if((m-i)%2==0) {
						n=0;
					} else {
						n=1;
					}
				
				break;
				}
			}
		}
		cout<<n<<endl;
	}
```

---

## 作者：TainityAnle (赞：0)

### 题目大意

每一个数字给定一个对应值，如下表：

![](https://cdn.luogu.com.cn/upload/image_hosting/sdv14tzu.png)

给定一个函数 $f(x)$，求每一位数字在上表中对应数字总和。

给定递归函数 $g^k(x)$，即将 $f(x)$ 递归 $k$ 次后的值。特别地，当 $k=0$ 时，$g^k(x)=x$。

### 思路

我们发现，$0 \le x, k \le 10^9$，即第一次递归后，剩下的最大只可能是 $18$。所以经过第一次，$x$ 的值下降得很快，我们发现，对于任何 $x$ 的取值，3 次以内必然会有 0。当 $x$ 取 0 时，判断 $k$ 的奇偶性，当 $k$ 是奇数时，取 1，否则取 0。

---

## 作者：Milthm (赞：0)

容易发现题目中的 $x$ 通过操作之后，下降是很快的。最后肯定会在 $0,1$ 两个数进行循环，具体原因是只有 $8$ 有 $2$ 个洞，但是没有个位数有 $8$ 个洞。所以 $k$ 比较大使 $x$ 下降到很小的时候答案只可能是 $0,1$。

所以按照题意模拟，如果发现 $x$ 为 $0$ 就判断剩余轮数的奇偶性就可以了。

### AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,x,k,e[15]={1,0,0,0,1,0,1,0,2,1};
int f(int x){
	int ans=0;
	if(!x)return 1;
	while(x){
		ans+=e[x%10];x/=10;
	}
	return ans;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>x>>k;
		for(int i=1;i<=k;++i){
			x=f(x);
			if(x==0){
				x=(k-i)%2;break;
			}
		}
		cout<<x<<'\n';
	}
	return 0;
}

```


---

## 作者：metrixgo (赞：0)

### 题目大意
一道模拟题。题目大意就是定义函数 $f(x)$ 代表 $x$ 当中每一个数字中封闭区域的数量和，然后再有一个函数 $g^k(x)$，可以理解为 $g(x,k)$，简单来看就是 $k$ 个 $f(x)$ 套在一起，比如 $g(x,3)$ 是 $f(f(f(x)))$ 的意思。现在给定 $x,k$，求 $g(x,k)$。

### 思路
由于是递归，又注意到 $k\le10^9,T\approx10^5$，那么一步步模拟只会爆掉。但是 $x\le10^9$ 代表 $x$ 最多 $9$ 位，如果对它取 $f(x)$，那么最大也就 $18$，再取一次就是 $2$，再取一次就是 $0$ 了。而注意到 $0$ 这个数如果不停取函数值那么只会在 $0,1$ 之间横跳，此时根据 $k$ 的奇偶性就可以出结果了，不用再递归下去。所以思路就是当把数化到一位数后分个类直接出结果就可以了，最多递归 $2$ 次，时间复杂度为 $O(T)$。

### 实现
建一个数组存储每一个数字的封闭区域数量。

```int f[11]={1,0,0,0,1,0,1,0,2,1};```

然后读入数据，$x$ 和 $k$，然后进行递归，并进行分类：

若 $k=0$，那么直接返回 $x$；

否则若 $x\le9$，即 $x$ 为一位数,那么查看 $x$ 的封闭区间数量。**此时若 $k=1$，那么直接返回该值。** 否则若值为 $1$ 或 $2$：

- 就说明再取一次函数值就变为 $0$ 了，此时若 $k$ 为偶数，就说明变成 $0$ 后重复奇数次，会变成 $1$，所以此时返回 $1$，否则说明变成 $0$ 后重复偶数次，还会变为 $0$，所以此时返回 $0$。

- 否则值为 $0$，那么此时若 $k$ 为偶数，返回 $0$，否则返回 $1$。

否则说明 $x$ 为多位数，此时分离每一位数，将每一个数字的封闭区域数量相加，然后进行下一步递归就可以了。

以上就是本代码的实现，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,x,k,t;
int f[11]={1,0,0,0,1,0,1,0,2,1};
int g(int x,int k)
{
	int cnt=0;
	if(k==0) return x;
	if(x<=9)
	{
		cnt=f[x];
		if(k==1) return f[x];
		if(cnt==2||cnt==1)
		{
			if(k%2==1) return 1;
			return 0;
		}
		if(k%2==1) return 0;
		return 1;
	}	
	while(x)
	{
		cnt+=f[x%10];
		x/=10;
	}
	return g(cnt,k-1);	
} 
int main()
{
  	scanf("%d",&t);
  	while(t--)
  	{
  		scanf("%d%d",&x,&k);
  		printf("%d\n",g(x,k));
	}
    return 0;
}
```

---

## 作者：小小小朋友 (赞：0)

题面很好理解。由于询问的数不超过 $10^9$，所有数在迭代不超过 $3$ 次后就会变为 $1$ 或者 $0$，而 $1$ 和 $0$ 会互相跳，那么只需判断下剩余次数奇偶性就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;cin>>T;
    while(T--){
        string s; cin>>s;
        int b;cin>>b;
        int ans=0;
        if(b==0) {cout<<s<<endl;continue;}
        while(1){
        	ans=0;
        	for(char i:s){
        		if(i=='0'||i=='8'||i=='9'||i=='6'||i=='4') ans++;
        		if(i=='8') ans++;
			}
			b--;
			if(b==0){
				cout<<ans<<endl;
				break;
			}
			else if(ans==1) {
				cout<<(b&1?0:1)<<endl;
				break;
			}
			else if(ans==0){
				cout<<(b&1?1:0)<<endl;
				break;
			}
			s=to_string(ans);
		} 
    }
    return 0;
}
```

---

## 作者：sfqxx1 (赞：0)

### **题目大意**

给出 $x$ 和 $k$，计算 $g^{k}(x)$。

### 思路

注意到 $g^{k}(x)$ 函数经过一定次数的递推一定会在 $0$ 和 $1$ 之间变换，所以在循环内加判断提前结束递推即可。

**注意： $f(0)=1$ ！**

### 代码

提示：多测时使用 PyPy3 用的时间会更少哦，但要小心内存超限。

```
t = int(input())
b = [1,0,0,0,1,0,1,0,2,1]
for _ in range(t):#多测
    c, d = map(int,input().split())
    e = c
    for g in range(1, d+1):
        if e == 0:
            if (d - g) % 2:
                e = 0
            else:
                e = 1
            break
        f = 0
        while e:
            f += b[e%10]
            e //= 10
        e = f
    print(e)
```
    

---

## 作者：Dream_poetry (赞：0)

### 题意：
相当友好的英语题面，他甚至还给我了~~没啥大用的~~递归范例。

**对应关系**

整数 $x$ 的各个数位上的 $0,1,4,9$ 对应 $1$，$8$ 对应 $2$，其他为零。

定义函数 $f(x)= \text{x 各个数位对应数之和}$。

然后让你执行 $k$ 次就好了。

### 思路：
既然题面都说递归了，那就递归呗。

```cpp
int dg(int kk,int nn){
	if (kk==0) return nn;
	else return dg(kk-1,f(nn));
}
```
$f$ 函数过于简单，就不打了。

来测样例。。。

很好，第四个数据挂了。。!

递归炸了。。。

#### 解决问题
我们一眼就能从表里看出，$0$ 和 $1$ 这俩是不断相互转换的。

也就是说，我们程序执行数据四时，干了几亿次 $0$ 和 $1$ 相互转换的废活。。。

那就搞个特判，$n$ 为 $0$ 时，如果 $k$ 剩余奇数个，最后肯定会变为 $1$，偶数次则还是 $0$。

好，加上特判，AC。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
int k,n;
int f(int x){
	int ans=0;
	while (x!=0){
		if (x%10==4 || x%10==9 || x%10==0 || x%10==6){
			ans++;
		}
		if (x%10==8){
			ans+=2;
		}
		x/=10;
	}
	return ans;
}
int dg(int kk,int nn){
	if (nn==0){
		if (kk%2) return 1;
		else return 0;
	}
	if (kk==0) return nn;
	else return dg(kk-1,f(nn));
}

signed main(){
	cin>>T;
	while (T--){
		cin>>n>>k;
		cout<<dg(k,n)<<endl;
	}
	return 0;
} 
```


---

## 作者：lidagua1004 (赞：0)

~~*貌似是第一篇题解*~~

[翻译](https://www.luogu.com.cn/paste/f16jivyn)

这道题首先考虑 $f(x)$，$f(x)$ 求起来很简单，只要将数位拆分再按规定的值相加即可。

规定的值用数组储存即可。

代码如下：
```cpp
int mp[10]={1,0,0,0,1,0,1,0,2,1};//储存值
int f(int x){
	if(x<10) return mp[x];//特判
	int sum=0;
	while(x) sum+=mp[x%10],x/=10;//拆分，求和
	return sum;
}
```
下一步对 $g(x)$ 处理，可以发现 $g(x)=f^k(x)$，枚举求肯定过不了，但是稍微探索就可以发现规律。

因为 $x<10^9$ 所以 $f(x)$ 最大为 $16$。所以 $f^2(x)$ 最大为 $2$。接下来 $f^k(x)$ 的值就成交替的 $01$ 串出现，只要判断 $k$ 的奇偶性即可。

代码如下：
```cpp
int g(int x,int a){
	if(a==0) return x;//特判a
	x=f(x),a--;
	if(a==0) return x;//特判a
	x=f(x),a--;
	if(a==0) return x;//特判a
	if(a&1) return mp[x];
	else return !mp[x];
}
```
最后这道题就简单了。

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int mp[10]={1,0,0,0,1,0,1,0,2,1};
int f(int x){
	if(x<10) return mp[x];
	int sum=0;
	while(x) sum+=mp[x%10],x/=10;
	return sum;
}
int g(int x,int a){
	if(a==0) return x;
	x=f(x),a--;
	if(a==0) return x;
	x=f(x),a--;
	if(a==0) return x;
	if(a&1) return mp[x];
	else return !mp[x];
}
int main(){
	int n;cin>>n;
	while(n--){
		int a,b;cin>>a>>b;
		cout<<g(a,b)<<"\n";
	}
	return 0;
} 
```

---

## 作者：zheng_zx (赞：0)

## P9897 Function and Function

[题目传送门](https://www.luogu.com.cn/problem/P9897)

### 分析

---

没啥好说的，一道签到题，找规律即可。



通过观察发现，到了后面就是在 $0$ 和 $1$ 之间循环，所以值到达 $0$ 之后，根据还需要进行的次数的奇偶性再判断即可。

注：

- $k \le 10^9$，直接递归算会超时。


### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[]= {1, 0, 0, 0, 1, 0, 1, 0, 2, 1};
int x, k, T;
int f(int n){
    if(!n)
        return 1;
    int num = 0;
    for(; n; n /= 10)
        num += a[n % 10];
    return num;
}

int g(int x, int k){
    while(k--){
        x = f(x);
        if(!x)
            return k & 1;
    }
    return x;
}

int main(){
    cin >> T;
    while(T--)
        cin >> x >> k, cout << g(x, k) << endl;
    return 0;
}
```

---

## 作者：Yuki_Ever (赞：0)

## 题目大意

多测，每组测试数据给定两个整数 $n$ 和 $k$，我们规定 $f(x)$ 为 $x$ 中每一个数字图形围成的封闭区间数之和。

例如，数字 $6$ 与数字 $9$ 各有一个封闭区域，所以 $f(6)=1$，$f(9)=1$，$f(69)=2$；同理， $f(8)=2$；而像数字 $1$、$7$ 就没有封闭图形，故 $f(1)=0$、$f(7)=0$。

除此之外，规定：$g^k(x)=f(f(f…f(x)…))$，其中有 $k$ 层括号。

特别的，当 $k$ 为 $0$ 时，$g^0(x)=x$。

## solution

首先我们定义一个函数来求解 $f(x)$。

不停地将 $x$ 除以 $10$ 并通过模 $10$ 来取到 $x$ 的每一位，判断有几个封闭图形。

```cpp
while (tmp>0){
	if(tmp%10==4)res++;
	if(tmp%10==6)res++;
	if(tmp%10==8)res+=2;
	if(tmp%10==9)res++;
	if(tmp%10==0)res++;
	tmp/=10;
   //这里只判有封闭图形的，没有的都是0
}
```


对于 $g^k(x)$ 最先想到直接进行递推求解，执行 $k$ 层循环。但简单观察数据范围后就会发现超时。于是继续研究性质。考察每层循环中 $x$ 的大小，容易发现，当 $k$ 极大时，几次之后 $x$ 就大概率会变为 $0$，然后在 $1$ 和 $0$ 中不断变化。

因此我们在循环中进行特判。

当 $x=1$ 时，若剩余需要循环的次数 $k$ 为奇数，直接把 $x$ 设为 $0$，然后直接返回掉。

同理，若 $k$ 为偶数，无需改变，直接返回即可。

```cpp
if(x==1 && k%2==1){ x=0; break;}
else if(x==1 && k%2==0) break;
```

此外，要加初始时 $x=1$ 的特判。因为最初 $x$ 为 $1$ 的话，进不了循环，直接返回 $0$。

在 $k=0$ 时再加个特判，直接返回 $x$，算法完成。

完整代码略。

## 后记
英文题目有点晦涩难懂，看懂后就发现其实很简单。























---

## 作者：__O_v_O__ (赞：0)

## 题目大意

定义函数 $f(x)$ 表示 $x$ 的每个数位上的数的“洞”的个数之和。

定义函数 $g^{k}(x)$ 表示 $x$ 做 $k$ 遍 $f$ 函数的结果。

多组数据，给出 $x,k$，输出 $g^{k}(x)$。

## 思路

此题显然不能模拟，那么有什么办法呢？

观察样例后发现：一个八位数经过一次操作就变成了两位数，减少得非常快。

于是我手模了一下，发现任何数小于 $10^9$ 的数经过小于等于六次操作后必然变为零，而且之后零到一，一到零循环。

所以此题不用把过程模拟完，只需模拟到变为零即可。

变为零后，只要剩余操作次数是奇数答案就为一，否则答案为零。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
int t,x,k,nu,an[10]={1,0,0,0,1,0,1,0,2,1}/*每个数字的答案*/,ti;
int f(int &a){//计算f函数的值
	int su=0;
	while(a)su+=an[a%10],a/=10;
	return a=su;
}signed main(){
	ios::sync_with_stdio(0)/*读入优化*/,cin>>t;
	afor(i,1,t,STB){
		cin>>x>>k,ti=0;
		while(x>0&&ti<k)f(x),ti++;//循环直到原数等于零或次数等于k
		if(ti==k){cout<<x<<'\n';continue;}
		k-=ti;//剩余次数
		if(k%2)cout<<"1\n";
		else cout<<"0\n";
	}return 0;
}
```

---

## 作者：Xdwjs (赞：0)

容易发现 $g^k(x)$ 就等于在 $x$ 外面嵌套 $k$ 层 $f$ 函数。暴力跑 $k$ 次 $f$ 函数肯定是不行的，但是我们发现所有不大于 $1000000000$ 的非负整数跑到最后都会陷入 $0$、$1$、$0$、$1$ 的循环。因此我们只需要先让 $x$ 跑几次 $f$ 函数，直到不需要再跑或者 $x$ 变成 $0$，如果还需要跑的话再将剩余要跑的次数对 $2$ 取模，就是最终的结果。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[15]={1,0,0,0,1,0,1,0,2,1};
int f(int x)
{
    int ans=0;
    while(x)
    {
        ans+=a[x%10];
        x/=10;
    }
    return ans;
}
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int x,k;
        cin>>x>>k;
        if(k==0)
        {
            cout<<x<<endl;
            continue;
        }
        int flag=0;
        while(x!=0)
        {
            x=f(x);
            k--;
            if(k==0)
            {
                flag=1;
                cout<<x<<endl;
                break;
            }
        }
        if(flag==0) cout<<k%2<<endl;
    }
    //system("pause");
    return 0;
}
```

---

