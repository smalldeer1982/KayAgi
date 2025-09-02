# Binary Median

## 题目描述

Consider all binary strings of length $ m $ ( $ 1 \le m \le       60 $ ). A binary string is a string that consists of the characters 0 and 1 only. For example, 0110 is a binary string, and 012aba is not. Obviously, there are exactly $ 2^m $ such strings in total.

The string $ s $ is lexicographically smaller than the string $ t $ (both have the same length $ m $ ) if in the first position $ i $ from the left in which they differ, we have $ s[i] < t[i] $ . This is exactly the way strings are compared in dictionaries and in most modern programming languages when comparing them in a standard way. For example, the string 01011 is lexicographically smaller than the string 01100, because the first two characters are the same, and the third character in the first string is less than that in the second.

We remove from this set $ n $ ( $ 1 \le n \le \min(2^m-1,       100) $ ) distinct binary strings $ a_1, a_2, \ldots, a_n $ , each of length $ m $ . Thus, the set will have $ k=2^m-n $ strings. Sort all strings of the resulting set in lexicographical ascending order (as in the dictionary).

We number all the strings after sorting from $ 0 $ to $ k-1 $ . Print the string whose index is $ \lfloor       \frac{k-1}{2} \rfloor $ (such an element is called median), where $ \lfloor x       \rfloor $ is the rounding of the number down to the nearest integer.

For example, if $ n=3 $ , $ m=3 $ and $ a=[ $ 010, 111, 001 $ ] $ , then after removing the strings $ a_i $ and sorting, the result will take the form: $ [ $ 000, 011, 100, 101, 110 $ ] $ . Thus, the desired median is 100.

## 说明/提示

The first test case is explained in the statement.

In the second test case, the result after removing strings and sorting is $ [ $ 001, 010, 101, 110 $ ] $ . Therefore, the desired median is 010.

## 样例 #1

### 输入

```
5
3 3
010
001
111
4 3
000
111
100
011
1 1
1
1 1
0
3 2
00
01
10```

### 输出

```
100
010
0
1
11```

# 题解

## 作者：Gc㍿ (赞：10)

# 洛谷CF1360H Binary Median

我所坚持的原理便是用最简单的思路写最乱的代码

所以我们看到题目之后就可以直接利用数据的小的特性强行求解

通过对中位数的每一步操作去完成代码任务

首先确定一下原输入的中位数

然后每输入一个要删除的数就将他与我们先前确定的中位数进行比较

这里可以运用最朴素的方法将二进制转化为十进制

我们发现一共会有三种情况

1.删掉的数小于中位数，直接模拟中位数的移动过程$\times 1$

2.删掉的数等于中位数，直接模拟中位数的移动过程$\times 2$

3.删掉的数大于中位数，直接模拟中位数的移动过程$\times 3$

进一步直接模拟(当然可以直接去通过其他的`lower_bound`操作改变)

主要是考虑所删除的数的个数的奇偶性来移动中位数

注意一下我们的中位数不能是已经删掉的数，如果是的话就略过他

思路还是十分简单的

整整代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
int qaq[200];//记录每一组数据中删掉的数的十进制
inline bool swag(long long a,long long b) {//排序  从小到大
	if(a<b)
		return true;
	return false;
}
inline long long pow1(long long a,long long k) {//快速幂当左移来用
	long long ans=1;
	while(k) {
		if(k&1)
			ans=ans*a;
		a=a*a;
		k>>=1;
	}
	return ans;
}
int main() {
	int t;
	cin>>t;
	while(t--) {
		long long n,m;
		cin>>n>>m;
		long long ans=(pow1(2,m-1))-1;//原输入的中位数
		string s;
		long long sum=0;//记录删掉了几个
		memset(qaq,-1,sizeof(qaq));//注意原序列中会有0
		long long qwq=0,cnt=0;//qwq表示删掉的数的十进制表示，cnt判断奇偶性
		for(int i=1; i<=n; i++) {
			qwq = 0;
			cin>>s;
			for(int j=0; j<m; j++) {//转到十进制
				if(s[j]=='1')
					qwq+=pow1(2,m-j-1);
			}
			qaq[++sum]=qwq;
			sort(qaq+1,qaq+sum+1,swag);
			if(qwq==ans) {//删除的数等于中位数
				cnt++;
				if(cnt%2==0) {//模拟过程1
					ans--;
					for(int j=sum; j>=1; j--)//防止中位数变成已经删掉的数
						if(ans==qaq[j])
							ans--;
				}
				if(cnt%2==1) {//模拟过程2
					ans++;
					for(int j=1; j<=sum; j++)
						if(ans==qaq[j])
							ans++;
				}
			} else if(qwq<ans) {//删除的数小于中位数
				cnt++;
				if(cnt%2==1) {//模拟过程3
					ans++;
					for(int j=1; j<=sum; j++)
						if(ans==qaq[j])
							ans++;
				}
			} else if(qwq>ans) {//删除的数大于中位数
				cnt++;
				if(cnt%2==0) {//模拟过程4
					ans--;
					for(int j=sum; j>=1; j--)
						if(ans==qaq[j])
							ans--;
				}
			}
		}
		for(int i=m-1; i>=0; i--) {//转回二进制
			if(ans>=pow1(2,i)) {
				ans-=pow1(2,i);
				printf("1");
			} else
				printf("0");
		}
		puts("");
	}
	return 0;
}
```

谢谢 一扶苏一 老神仙的代码调试服务(雾

---

## 作者：暗ざ之殇 (赞：10)

# CF1360H Binary Median

## 题解 
#### ① 最常见最暴力的做法：
将读入的二进制转化为十进制，然后依次删除，删除过程中维护中位数；

虽然思路简单，但是考虑到实际维护的过程中十分复杂，对代码能力要求较高；

#### ② 稍微巧妙一点的做法：
**其实我们并不需要维护每个过程中的中位数是几，我们关心的只是全部删除后的中位数是几；**

而且题目中给出了数据的原始个数（$2^m$）和删除个数（$n$），也就是说，**我们能知道删除完后的这 $2^m - n$ 的中位数是第几个数（设是第 $k$ 个数，根据规律可得 $k = ( 2^m - n + 1 ) / 2$）**，那么删除完后我们就输出这个位置的数就好了；

这就有了另一个思路：我们只需要在删除过程中维护哪个数变成了第 $k$ 个数 。

拿样例模拟一下：

$n = 3,m = 3$

删除的数为：$(010)_2 = 2,(001)_2 = 1 ,(111)_2 = 7 $

删除前的所有数：
![](https://cdn.luogu.com.cn/upload/image_hosting/jwvny5q3.png)


 

通过计算可以知道 $k = ( 2^3 - 3 + 1 ) / 2 = 3$，那么我们就确定了删完 $3$ 个数之后的数据中第 $3$ 个数是中位数；  

然后我们就死盯着第 $3$ 个数不放，看哪个数在删除之后移到了第 $3$ 个数的位置（红色的数字代表最后的中位数上的数）；

![](https://cdn.luogu.com.cn/upload/image_hosting/wnao4952.png)

 

由于数据是从 $0$ 开始的，所以第 $k$ 个数的大小为 $k-1$ （令 $mid = k-1$）。

删除 $2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/fm3kf3qi.png)


 

删除 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/afl265bg.png)

 

删除 $7$：

![](https://cdn.luogu.com.cn/upload/image_hosting/h2thparx.png)

 

过程中我们可以发现一个规律：

**对于我们所要维护的中位数 $mid$ 来说，如果删除的数比 $mid$ 大，那么 $mid$ 的值是不变的（参考上图删除 $7$ 的过程）；如果删除的数小于等于 $mid$，那么 $mid$ 的值就变成了右边的那个数（以下称为“ 右移一次 ”），注意要跳过已经被删除了的数；**

**这么看来，我们可以先将所需删除的数从大到小排序，对于其中的 $cnt$ 个比 $mid$ 大的数，删除了并不影响 $mid$ 的值；对于其中的 $n - cnt$ 个小于等于 $mid$ 的数，每删除一个 $mid$ 就要右移一次，总共需要右移 $n - cnt$ 次；**

其实我们也可以只存比 $mid$ 大的那些数，对于那些比 $mid$ 小的数，我们只关心它有多少个；同时这样的话，我们也不必将所删除的数从大到小排序了，因为二分查找也可以从小到大排序啊$qwq$ 


**$Code$**
```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n,m,cnt;
long long len,mid;
long long delet[1500];
bool read()              //读入单个数字 
{
	char ch=getchar();
	while(ch!='0'&&ch!='1') ch=getchar();
	return ch^48;
}
int check(long long x)   //查找x是否在delet数组里 
{
	return delet[lower_bound(delet+1,delet+1+cnt,x)-delet]==x;  //lower_bound偷懒qwq 
}
void work()
{
	for(long long i=mid+1;i<=len;i++)
	{
		if(!check(i))    //判断i是否被删除 
		{
			mid=i;       //没有被删除就来当mid 
			return ;
		}
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&m);
		len=1ll<<m;                  //len是初始数的个数 
		mid=(len-n+1)/2-1;           //删除一些数之后的中位数的位置上的数现在是几 
		memset(delet,0,sizeof(delet));
		cnt=0;                       //记录删除的数中有多少个数比mid大 
		for(int i=1;i<=n;i++)        
		{
			long long a=len/2;   
			long long num=0;         //num是转化为十进制之后的数 
			for(int j=1;j<=m;j++)    //二进制转化为十进制 
			{
				int x=read();
				if(x) num+=a;
				a/=2;
			}
			if(num>mid) delet[++cnt]=num;   //只需记录所有比mid大的数 
		}
		sort(delet+1,delet+1+cnt);   //从小到大排序,便于二分查找 
		for(int i=1;i<=n-cnt;i++)    //总共有n-cnt个数小于等于mid,就要右移n-cnt次 
		    work();
		len/=2;    
		while(len)                   //十进制转化为二进制 
		{
			if(mid>=len) 
			{
				printf("1");
				mid-=len;
			}
			else printf("0");
			len/=2;
		}
		printf("\n");
	}
	return 0;
}
```
特别鸣谢 [一扶苏一](https://www.luogu.com.cn/user/65363) 帮我 $debug$；



---

## 作者：蒟酱 (赞：2)

提供一份好看的题解。

---
$2^m-n$ 个数的中位数排名是 $\lfloor\dfrac{2^m-n-1}2\rfloor$（从 $0$ 开始）。因为所有元素是连续的，只要数出被删掉的比中位数小的元素数量，那么 $\lfloor\dfrac{2^m-n-1}2\rfloor$ 加上数量就是中位数了。  
不过不知道中位数的大小，不能确定比中位数小的元素数量。可以采取二分。更简单的方式是把元素从小到大枚举。  
略带麻烦的是输入数出，使用 `bitset` 解决很方便。  
复杂度在于读入和排序，$\mathcal O(nm+n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<bitset>
using std::cin;using std::cout;
using lolu=unsigned long long;
constexpr int N=101;
int n,m;
lolu a[N];
std::bitset<64>num;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	int T;cin>>T;while(T--){
		cin>>n>>m;
		lolu mid=((1ull<<m)-n-1)/2;
		for(int i=1;i<=n;i++)cin>>num,a[i]=num.to_ullong();
		std::sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)if(a[i]>mid)break;else mid++;
		num=mid;
		for(int i=m-1;~i;i--)cout<<num[i];
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：DHT666 (赞：1)

## 题意

从 $1$ 到 $2^m$ 一共有 $2^m$ 个数，从中删去 $n$ 个后，求剩下 $2^m-n$ 个二进制数排序后的中位数，即第 $\left\lfloor\frac{2^m-n+1}{2}\right\rfloor$ 个数。

为什么没出现题目中的二进制数？因为二进制数的长度 $1\le m \le 60$，所以用 `long long` 来表示再好不过了。

## 思路
（我简化后的）题意说的很清楚，既然我们已经知道了最终答案的下标，那么我们在原序列中一直盯着这个下标不放即可。

依次遍历被删的数，如果删掉了该下标或该下标之前的数，就右移一位，否则就不用关心，因为右边的数被删掉不影响当前的下标。

## 代码
可读性不高，其实我的思路已经够清楚了（吧）。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <cmath>
using namespace std;

typedef long long LL;

const LL N = 110, M = 70;

LL T;
LL n, m;
string a;
LL b[N];
bool res[M];

map<LL, bool> Map;

LL get() {
	LL res = 0;
	for(LL i = m, j = 1;i >= 1;i--, j <<= 1) {
		res += j * (a[i] == '1');	
	}
	return res;
}

void print(LL x) {
	memset(res, 0, sizeof res);
	for(LL i = 1;i <= m;i++) {
		res[i] = x & 1;
		x >>= 1;
	}
	for(LL i = m;i >= 1;i--) {
		if(res[i]) printf("1");
		else printf("0");
	}
	puts("");
}

int main() {
	scanf("%lld", &T);
	while(T--) {
		Map.clear();
		scanf("%lld%lld", &n, &m);
		for(LL i = 1;i <= n;i++) {
			cin >> a;
			a = " " + a;
			b[i] = get();
			Map[b[i]] = 1;
		}
		
		sort(b + 1, b + 1 + n);
		
		LL r = pow(2, m) - n, t;
		if(r & 1) t = r / 2;
		else t = r / 2 - 1;
		LL cnt = 0;
		for(LL i = 1;i <= n;i++) {
			if(b[i] <= t) cnt++;
		}
		
		LL Max = pow(2, m);
		while(cnt && t <= Max) {
			t++;
			if(Map[t] == 0) cnt--;
		}
		
		print(t);
	}
	
	return 0;
}
```

---

## 作者：SusieRain (赞：1)

感觉这道题好像没用到什么算法啊 $n$ 很小可以直接从最开始暴力模拟删除每一个数只需要在中间稍微讨论一下即可。
单组时间复杂度为 $O( n ^ 2 \log n )$ 因为 $n$ 很小所以暴力也没什么问题。

代码如下：（注释中有解释）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long // 我开了define int long long 不开的话记得手动写long long
const int N = 1e5 + 10;
typedef long long ll;
int n , m ;
void solve(){
    cin >> n >> m ;
    vector<string> s(n) ;
    vector<int> a(n) ;
    for(int i=0;i<n;i++) cin >> s[i] ;
    for(int i=0;i<n;i++){ // 01串转化为数字不多做解释
        ll res = 0 , k = 1 ;
        for(int j=m-1;j>=0;j--){
            res += k * (s[i][j] - '0') ;
            k *= 2 ;
        }
        a[i] = res ;
    }
    int mid = ( (1ll<<m) - 1 - 1 ) / 2 ;
    // 0 1 2 3 4 5 6 7
    // 0 1 2 3 4 5 6
    int res = (1ll<<m) ; // 当前剩下的字符串的数量
    map<int,int> vis; // 用来记录这个数字是否被删除过
    for(int i=0;i<n;i++){
        vis[a[i]] = 1 ;
        if(res%2==0){
            if(a[i]<=mid) { // 如果当前长度为偶数且删除的数比当前中位数大就找下一个数
                // 具体讨论情况可以对着上面捏的两组看
                mid ++ ;
                while (vis[mid]) mid ++ ; // 如果已经被删掉了就找下一个
            }
        } else {
            if(a[i]>=mid) { // 讨论与上面那部分同理
                mid -- ;
                while (vis[mid]) mid -- ;
            }
        }
        res -- ;
    }
    string ans(m,'0');
    for(int i=0;i<m;i++){
        ans[i] = '0' + ((mid>>i)&1) ;
    }
    std::reverse(ans.begin(), ans.end()) ;
    cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(false) ;
    cin.tie(0) ;
    int tt = 1 ;
    cin >> tt ;
    while (tt--) solve() ;
    return 0 ;
}
```


---

## 作者：Dovе (赞：1)

### 题意简述
***

&#8195;&#8195;给你 $n,m$,让你求出 $2^m$ 内所有二进制排列的中位数是多少

### 大致思路
***
&#8195;&#8195;我们考虑将所有二进制转换为整数，便于运算，然后算出删除后中位数的位置

```cpp
int mid=((1ll<<m)-n-1)/2;
```

&#8195;&#8195;我们不难发现，如果删除的数是小于或等于 $mid$ 的，那么在删除前后，$mid$ 的位置向前了 $1$ 位。也就是说，我们在删除后进行还原时，对于该数小于等于 $mid$ 的情况，我们需要将 $mid+1$

&#8195;&#8195;同时，为了避免输入删除的数的大小关系影响 $mid$ 的增减，我们先将 $n$ 个删除的数进行排序，在逐个比较

&#8195;&#8195;在完成上述步骤后，我们发现：当前的 $mid$ 就是我们需要就的中位数。紧接着，我们将 $mid$ 转成二进制输出即可

### 代码
***
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=60+50;
int n,m;
int a[maxn];
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		int mid=((1ll<<m)-n-1)/2;
//		printf("%d\n",mid);
		for(register int i=1;i<=n;++i)
		{
			string s; cin>>s;
			int Ans_=0;
			for(register int j=0;j<s.length();++j)
			  if(s[j]=='1') Ans_+=1ll<<m-j-1;
			a[i]=Ans_; // 将删除的数转成十进制
//			printf("%d\n",Ans_);
		}
		sort(a+1,a+n+1);
		
		for(register int i=1;i<=n;++i)
		  if(a[i]>mid) break;
		  else mid++; // 处理 mid
		
//		printf("%d\n",mid);
		 
		vector<int> res;
		
		while(mid)
		{
			res.push_back(mid%2);
			mid/=2;
		} 
		reverse(res.begin(),res.end()); // 将 mid 转为 二进制
        
		for(register int i=1;i<=m-res.size();++i) printf("0");
		for(register int i=0;i<res.size();++i) printf("%d",res[i]);
		printf("\n"); // 输出答案
	}
	return 0;
 } 
```


---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1360H](https://www.luogu.com.cn/problem/CF1360H)

# 解题思路

发现你可以十分高效的统计小于等于 $x$ 的合法的数字数量。

并且你可以发现，当 $x$ 递增时，合法的数字数量是不递减的，因此合法的数字数量是**具有单调性**的。

于是可以进行二分答案。

那么如何进行 check 呢？我们先将不可选用的二进制数字给转化成数字，然后假设我们是找小于 $x$ 可选用的数字数量，直接用 $x + 1$ 再减去小于等于 $x$ 的不可选用的数字数量即可。

因此单次 check 根据是 $O(n)$ 的。

总时间复杂度为 $O(nm)$，非常优秀。

注意输出的时候需要带前导零补齐输出。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
ll _t_;
void _clear(){}
ll L,R;
ll n,m;
ll a[110];
string s;
ll pw(ll x){
	return 1ll<<x;
}
ll f(string s)
{
	ll k=0,sum=0;
	reverse(s.begin(),s.end());
	for(auto i:s)
		sum+=pw(k++)*(i=='1');
	return sum;
}
bool check(ll x)
{
	ll sum=x+1; // 注意 0 
	forl(i,1,n)
		if(a[i]<=x)
			sum--;
///	if(x==4)
//		cout<<"???"<<sum<<endl;
	return sum<((pw(m)-n+1)/2);
}
void print(ll x)
{
	if(x==0)
	{
		forl(i,1,m)
			cout<<0;
		cout<<endl;
		return ;
	}
	string s="";
	while(x)
		s+=x%2+'0',x/=2;
	ll sz=s.size();
	forl(i,1,m-sz)
		s+='0';
	reverse(s.begin(),s.end());
	cout<<s<<endl;
}
void solve()
{
	_clear();
	cin>>n>>m;
	L=0,R=pw(m)-1;
	forl(i,1,n)
		cin>>s,a[i]=f(s);
	sort(a+1,a+1+n);
	while(L<R)
	{
		ll Mid=(L+R)/2;
		if(check(Mid))
			L=Mid+1;
		else
			R=Mid;
	}
	print(L);
//	cout<<L<<endl;
}
int main()
{
	IOS;
	_t_=1;
	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：紊莫 (赞：0)

考虑一个数删除后对中位数有什么影响。

假如删除了左边，分两种情况讨论，当前总个数为奇数时，答案不变，总个数为偶数时，中位数右移一位。

删除右边同理。删除了自己时，奇数左移，偶数右移。因为数据范围很小，所以直接暴力一定操作即可，注意这里的移动是要跳过被删除了的空点的，因为数字很大，而 $n$ 很小，所以 ``map`` 即可。

[示例代码。](https://www.luogu.com.cn/paste/1obveoh0)

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2100}$
---
### 解题思路：

在元素全部不相同的序列中，中位数是有恰好 $\lfloor\dfrac{len}{2}\rfloor$ 个不比这个数大的数。

那么考虑二分中位数，并通过删除的数和这个数本身的大小来计算出当前数的排名。直接通过这个就能计算出中位数的大小了。

单组数据的复杂度为 $O(nm)$，可以通过将给出的删除的数的序列排序并在其中二分的方法优化到 $O(n\log n+m\log n)$，但是由于数据范围较小，没有必要。

注意本题需要用长整型进行存贮，以及输出格式中前导 $0$ 的处理。


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int T,n,m,a[105],l,r,mid,ans,res[105],len,k,M;
int get(){
	int num=0;char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())num=num*2+c-'0';
	return num;
}
void put(int num){
	if(num>=2)put(num/2);
//	putchar(num%2+'0');
	res[++len]=num%2;
}
bool check(int num){
	int cnt=num+1;
	for(int i=1;i<=n;i++){
		if(a[i]<=num)cnt--;
	}
	return cnt<k;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)a[i]=get();
		M=1ll<<m;
		k=(M-n+1ll)/2ll;
		l=0ll;r=M-1ll;
		while(l<=r){
			mid=l+r>>1ll;
			if(check(mid))l=mid+1ll;
			else r=mid-1ll,ans=mid;
		}
		len=0ll;
		for(int i=1;i<=m;i++)
		res[i]=0ll;
		put(ans);
		for(int i=1ll;i<=m-len;i++)
		printf("0");
		for(int i=1;i<=len;i++)
		printf("%lld",res[i]);
		putchar('\n');
	}
	return 0;
}
/*
1 
3 3
000
001
010

*/
```


---

