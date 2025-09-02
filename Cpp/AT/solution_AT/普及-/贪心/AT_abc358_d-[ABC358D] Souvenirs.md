# [ABC358D] Souvenirs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc358/tasks/abc358_d

AtCoder Land のお土産屋に $ N $ 個の箱が売られています。

箱には $ 1,\ 2,\ \ldots,\ N $ の番号が付いており、箱 $ i $ の価格は $ A_i $ 円であり、$ A_i $ 個のお菓子が入っています。

高橋君は $ N $ 個の箱のうち $ M $ 個の箱を選んで買って帰り、$ 1,\ 2,\ \ldots,\ M $ の名前が付いた $ M $ 人の人に $ 1 $ つずつ箱を渡そうとしています。

ただし、高橋君は以下の条件を満たすことができるように箱を買いたいです。

- 各 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、人 $ i $ には $ B_i $ 個以上のお菓子が入った箱を渡す
 
$ 1 $ 人に $ 2 $ 個以上の箱を渡すことや同じ箱を複数人に渡すことはできないことに注意してください。

適切に箱を $ M $ 個買うことで条件を満たすことができるか判定し、条件を満たすことができる場合は高橋君が支払う金額の合計の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ M\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 10^9 $
- 入力される値はすべて整数
 
### Sample Explanation 1

高橋君は箱 $ 1,\ 4 $ を買い、箱 $ 1 $ を人 $ 1 $、箱 $ 4 $ を人 $ 2 $ に渡すことで条件を満たすことができます。 このとき高橋君が支払う金額の合計は $ 7 $ 円であり、支払う金額が $ 7 $ 円未満のときは条件を満たすことはできないため、$ 7 $ を出力します。

## 样例 #1

### 输入

```
4 2
3 4 5 4
1 4```

### 输出

```
7```

## 样例 #2

### 输入

```
3 3
1 1 1
1000000000 1000000000 1000000000```

### 输出

```
-1```

## 样例 #3

### 输入

```
7 3
2 6 8 9 5 1 11
3 5 7```

### 输出

```
19```

# 题解

## 作者：wei2013 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_d)
## 思路：
先考虑暴力，时间复杂度 $\mathcal{O(mn)}$，显然不行。

其实呢，可以使用一个很显然的贪心策略：肯定是要使用此时**有的比要求糖果更多的最少量**，这样才能使得需要支付的价格最少。

但是这样依旧要扫一遍原序列，复杂度仍旧一样，再看，其实我们的贪心策略是具有单调性的，设 $f(x)$ 为小于 $x$ 元的盒子数量，因为 $f(x+1) \ge f(x)$，所以完全可以使用二分。

不过，我这边用了双指针，排序一遍后，向后扫，找到足够的盒子，时间复杂度 $\mathcal{O(n \log n)}$。
## code:
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,j=1,ans=0,a[200005],b[200005],tot=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++){
		while(j<=n && b[i]>a[j]){
			j++;
		}
		if(a[j]<b[i]){
			cout<<-1;
			return 0;
		}
		ans+=a[j++];
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：stripe_python (赞：3)

D 最简单的一集。

考虑贪心，对于每个 $B_i$，找到第一个大于等于它的 $A_i$ 分配给 $i$ 号。由于不允许给多个人同一个盒子，将其删除即可。

显然是 `std::multiset` 的模板题。

```cpp
#include <bits/stdc++.h>
#define N 200005
using namespace std;

int n, m;
int a[N], b[N];

multiset<int> st;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i], st.emplace(a[i]);
	for (int i = 1; i <= m; i++) cin >> b[i];
	long long tot = 0;
	for (int i = 1; i <= m; i++) {
		auto it = st.lower_bound(b[i]);
		if (it == st.end()) return cout << -1, 0;
		tot += *it;
		st.erase(it);
	}
	cout << tot;
	return 0;
}
```

复杂度：$O(m \log n)$。

---

## 作者：COKENOTFOUND (赞：2)

# AT_abc358_d [ABC358D] Souvenirs 题解

这道题其实比 C 要简单不少。大体题意就是找 $A$ 数组中大于等于 $B_i$ 的第一个元素。可以使用具有自动排序功能的 multiset 充当 $B$ 数组，再使用 lower_bound 查询符合要求的最小值即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MX=1e6+10;
const int mod=1e9+7;
int n,m;
int a[MX];
int nd[MX];
int vis[MX];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		cin >> a[i];
	}
	for(int i=1;i<=m;i++){
		cin >> nd[i];
	}
	ll sum=0;
	multiset<int> mst;//自动排序是个好东西
	for(int i=1;i<=n;i++){
		mst.insert(a[i]);
	}
	for(int i=1;i<=m;i++){
		auto num=mst.lower_bound(nd[i]);
		// num是于第一个大于等于nd[i]（也就是价格合适）的数
		if(num==mst.end()){
			cout << "-1\n";
			return 0;
		}//没有
		sum+=*num;
		mst.erase(num);
	}
	cout << sum << "\n";
	return 0;
}
//十年OI一场空，不开long long 见祖宗
//数据不清空，爆零两行泪

```

---

## 作者：Xuan_qwq (赞：2)

### 题面大意
有 $n$ 个盒子，第 $i$ 个盒子价值 $a_i$ 元。有 $m$ 个人，每个人希望得到一个价值不小于 $b_i$ 元的盒子，一个盒子不能同时给两个人。确定能否满足所有人的需求，如果可以，输出所要花费的最小价值；如果不能，输出 $-1$。

### 思路
这应该是一道很明显的贪心了吧，每个人都找能满足自己需求的最便宜的盒子，冲突就找下一个。

将盒子价值与需求价值从小到大排序，找到可以满足当前人需求的最小价值的盒子，然后下一个人从下一个盒子开始遍历即可，时间复杂度是线性的，即每个盒子最多被遍历一遍。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[200005],b[200005];
long long ans;//极限数据结果是2e5*1e9左右的，所以不long long会爆炸
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<m;i++)cin>>b[i];
	sort(a,a+n);
	sort(b,b+m);
	int j=0;//当前的盒子编号
	for(int i=0;i<m;i++){
		bool flag=1;//有没有找到合法的盒子
		for(;j<n;j++){
			if(a[j]>=b[i]){//找到了合法的盒子
				ans+=a[j];
				j++;//下一次遍历从下一个盒子开始
				flag=0;//找到盒子了
				break;
			}
		}
		if(flag){//没找到
			cout<<"-1"<<endl;//遗憾结束
			return 0;
		}
	}
	cout<<ans<<endl;//完美结束！
	return 0;
}
```

---

## 作者：_determination_ (赞：2)

可以发现我们扔给一个人的礼物一定是大于等于他需要的糖果数的盒子中糖果数最少的那个盒子。

显然可以二分查找，但是不太好搞删除。`set` 的话会去重，`unset` 没有 `lower_bound` 之类的二分函数。

所以弱智的我没想到双指针，写了线段树二分。。。

你维护一个值域线段树即可，懒得写线段树上二分写了个线段树套二分。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
#define debug cout << "114514" << endl
int n,m;
int a[200010],b[200010],c[400010];
int ans;
struct node{
    int l,r,sum;
}t[1600010];
void build(int x,int l,int r)
{
    t[x].l=l;
    t[x].r=r;
    if(l==r)return;
    int mid=(l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
}
void upd(int x,int p,int v)
{
    int lf=t[x].l,rt=t[x].r;
    if(p<=lf&&rt<=p)return t[x].sum+=v,void();
    if(rt<p||p<lf)return;
    upd(x<<1,p,v);
    upd(x<<1|1,p,v);
    t[x].sum=t[x<<1].sum+t[x<<1|1].sum;
}
int calc(int x,int l,int r)
{
    int lf=t[x].l;
    int rt=t[x].r;
    if(l<=lf&&rt<=r)return t[x].sum;
    if(rt<l||r<lf)return 0;
    return calc(x<<1,l,r)+calc(x<<1|1,l,r);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> n >> m;
    for ( int i = 1 ; i <= n ; i++ )
    {
        cin >> a[i];
        c[i]=a[i];
    }
    for ( int i = 1 ; i <= m ; i++ )
    {
        cin >> b[i];
        c[i+n]=b[i];
    }
    sort(c+1,c+1+n+m);
    int k=unique(c+1,c+1+n+m)-c-1;
    for ( int i = 1 ; i <= n ; i++ )
    {
        a[i]=lower_bound(c+1,c+1+k,a[i])-c;
    }
    for ( int j = 1 ; j <= m ; j++ )
    {
        b[j]=lower_bound(c+1,c+1+k,b[j])-c;
    }
    build(1,1,k);
    for ( int i = 1 ; i <= n ; i++ )
    {
        upd(1,a[i],c[a[i]]);
    }
    int ans=0;
    for ( int i = 1 ; i <= m ; i++ )
    {
        int l=b[i],r=k;
        if(calc(1,b[i],k)==0)
        {
            cout << -1;
            return 0;
        }
        while(l<r)
        {
            int mid=(l+r)/2;
            if(calc(1,b[i],mid))r=mid;
            else l=mid+1;
        }
        ans+=c[l];
        upd(1,l,-c[l]);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：luobotianle (赞：2)

运用贪心的思想，我们可以发现，对于任意一个 $b_i$，我们都应在 $a$ 数组中找出**大于等于 $b_i$ 且未被使用过的最小的数**。

我们可以先给 $a$ 和 $b$ 排序，然后对于每一个 $b_i$，设 $last$ 表示 $b_{i-1}$ 在 $a$ 中对应的位置；

由于 $a$ 和 $b$ 数组均已排序，而 $b_i \ge b_{i-1}$，所以 $b_i$ 对应的数也一定大于等于 $b_{i-1}$ 对应的数；

所以直接在 $a_{last+1}$ 到 $a_n$ 中查找第一个大于等于 $b_i$ 的数即可。

记得开 `long long`。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
ll a[N],b[N],ans=0;
ll n,m,lst;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(b+1,b+1+m);
	for(int i=1;i<=m;i++){
		int pos=lower_bound(a+lst+1,a+1+n,b[i])-a;
		if(pos>n){
			cout<<-1;
			return 0;
		}
		ans+=a[pos];
		lst=pos;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Barryb (赞：2)

# 思路
这题我们可以先将两个数组排序，再设一个位置变量，然后遍历第二个数组，一直判断位置计数器是否小于等于 $n$ 并且 $a_{now} \le b_i$，如果这样位置就加一。如果位置小于等于 $n$，最小值计数器就加 $a_{now}$，位置加一。否则就直接输出，
结束。最后输出最小值计数器就好了。
# 注意
本题最大高达 $2 \times 10^5 \times 10^9$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,sum,now=1;
long long a[200010],b[200010];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
		cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++)
	{
		while(now<=n&&a[now]<b[i]) now++;
		if(now<=n) sum+=a[now++];
		else return cout<<-1,0;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：lostxxx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_d)

# 题目大意

有 $n$ 个礼品和 $m$ 个人，要给一共 $i$ 个人买不小于 $b_i$ 的礼品。求最小花费。

# 题目分析

我们可以先将 $a$ 数组和 $b$ 数组排序，以便于我们更好的查找。先遍历 $1$ 到 $m$ ，二分查找第一个大于等于 $b_i$ 的数的下标，用 $cnt$ 存下，$ans$ 加上 $a_{cnt}$ ，然后再继续遍历，每次再从数组 $a$ 的第 $cnt+1$ 个到第 $n$ 个进行二分查找。其中，如果未找到则直接退出循环。

代码如下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
ll a[200100];
ll b[200100];
ll ans=0;
int main(){
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        cin>>a[i];
    }
    for (int i=1;i<=m;i++){
        cin>>b[i];
    }
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    ll cnt=0;
    for (int i=1;i<=m;i++){
        ll k=upper_bound(a+1+cnt,a+n+1,b[i]-1)-a;
        if (k>n){
            cout<<-1;
            return 0;
        }
        cnt=k;
        ans+=a[k];
    }
    cout<<ans;
}
```

---

## 作者：__zhuruirong__ (赞：1)

## 做法分析

显然，如果 $a_i$ 最小，那就只需要最小的 $b_j$ 满足 $a_i\le b_j$，然后把它们两个分别从 $a$、$b$ 中移除，继续这个操作直到无法继续做为止。

所以做法就很明显了。

## AC代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

const int N = 2e5 + 10;
int n, m, a[N], b[N];
priority_queue<int, vector<int>, greater<int> > q; // 小根堆

signed main() {

//	ios::sync_with_stdio(0);
//	cin.tie(0);
//  cout.tie(0);
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		q.push(a[i]);
	}
	for(int i = 1; i <= m; i++) {
		cin >> b[i];
	}
	sort(b + 1, b + m + 1);
	int i = 1, ans = 0;
	while(!q.empty() and i <= m) {
		int now = q.top(); q.pop();
		if(now >= b[i]) {
			ans += now;
			i++;
		}
	}
	if(i <= m) {
		cout << "-1\n";
	}
	else {
		cout << ans << "\n";
	}
	

	return 0;
}

```

---

## 作者：kkxacj (赞：1)

#### 思路

提供一个二分做法。

显然先对两个数组都排个序，对于每个数 $a_i$ 我想求第一个比它大的数 $b_j$ 是多少，但可能多个数会求到同一个数，怎么办呢。

由于 $a_i$ 是单调递增的，所以 $a_i$ 找到的数 $b_i$ 也是单调递增，可能存在相等的情况，每次二分完的位置设为 $o$，下一次直接二分 $o+1$ 到 $n$ 就行了，如果没有 $o$ 说明无解。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int n,m,a[200010],b[200010],c,v[200010],ans,l,r,mid,o;
signed main()
{
	read(n),read(m);
	for(int i = 1;i <= n;i++) read(b[i]);
	for(int i = 1;i <= m;i++) read(a[i]);
	sort(a+1,a+1+m); sort(b+1,b+1+n);
	c = 1;
	for(int i = 1;i <= m;i++)
	{
		l = c,r = n,o = 0;
		while(l <= r)
		{
			mid = (l+r)/2;
			if(b[mid] >= a[i]) o = mid,r = mid - 1;
			else l = mid + 1;
		}
		if(o == 0)
		{
			cout<<"-1";
			return 0;
		}
		c = o+1;
		ans += b[o];
	}
	print(ans); flush();
	return 0;
}

```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_d)

## 思路

贪心。

读入数据后把每个盒子存入一个 ``multiset`` 中。读入每个人的要求，并在这个 ``multiset`` 中用 ``lower_bound()`` 快速找到最小的能满足这个人要求的盒子，把结果加上这个值，**并把这个盒子从中删除**。如果对于某个人找不到满足其要求的盒子，说明不可能全匹配上，直接输出 ``-1`` 并结束程序。

- $N\times A_i$ 最大能到 $2\times 10^{14}$，记得开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll k=0,flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	return k*flag;
}
const int N=2e5+10;
multiset<ll>st;
int n,m;
ll ans;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)st.insert(read());
	for(int i=1;i<=m;++i){
		ll x=read();
		auto p=st.lower_bound(x);
		if(p==st.end()){
			cout<<-1;
			return 0;
		}
		ans+=*p;//先加再删指针，不然会访问一个空数据。
		st.erase(p);
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/162289292)

---

## 作者：OIer_Tan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_d)

为什么赛时用 `lower_bound` 寄了？

## 题意

在 $a_1,a_2,a_3,\cdots,a_n$ 中选 $m$ 个数，每一被选出的数 $c_i$ 都有 $c_i\ge b_i$ 且满足条件的 $b_i$ 不重。

## 思路

考虑使用可重集保存 $a_1,a_2,a_3,\cdots,a_n$，然后对于每一个 $b_i$ 二分找最小的那个，然后删掉。

时间复杂度 $O(n\log n +m\log n)$，可过。

但是为什么给 $a$ 排序后在 $a$ 上直接 `lower_bound` 会寄？我也不知道。

## 代码

注释的就是赛时寄掉的，有好心人帮我看一下吗？

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n , m , a [N] , b [N] , ans = 0 ;

multiset <ll> s ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> m ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> a [i] ;
		s.insert ( a [i] ) ;
	}
	for ( ll i = 1 ; i <= m ; i ++ )
	{
		cin >> b [i] ;
		auto it = s.lower_bound ( b [i] ) ;
		if ( it == s.end () )
		{
			cout << -1 << endl ;
			exit ( 0 ) ;
		}
		ans += * it ;
		s.erase ( it ) ;
	}
//	sort ( a + 1 , a + 1 + n ) ;
//	sort ( b + 1 , b + 1 + m ) ;
//	ll last = 0 ;
//	for ( ll i = 1 ; i <= m ; i ++ )
//	{
//		if ( last > n )
//		{
//			cout << -1 << endl ;
//			exit ( 0 ) ;
//		}
//		auto place = lower_bound ( a + last + 1 , a + 1 + n , b [i] ) ;
//		if ( place == a + 1 + n )
//		{
//			cout << -1 << endl ;
//			exit ( 0 ) ;
//		}
//		else
//		{
//			ans += * place ;
//			while ( ( * place ) == ( * prev ( place ) ) ) place -- ;
//			last = place - a ;
////			cout << * place << endl ;
//		}
//	}
	cout << ans << endl ;
	return 0 ;
}
```

---

## 作者：zzhbpyy (赞：0)

### [传送门](https://atcoder.jp/contests/abc358/tasks/abc358_d)

## 思路

考虑贪心，对 $A$ 数组和 $B$ 数组分别排序。由于我们需要让总金额尽量小，选取的 $A_i$ 也应尽量小。用变量 $ct$ 作为一个指针找到大于 $B_i$ 的最小的可用的 $A_{ct}$，累加答案即可。若 $ct>n$ 时都无法满足条件，则无解。

## 完整代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005],ans,b[200005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	int ct=1;
	for(int i=1;i<=m;i++){
		while(a[ct]<b[i]){
			ct++;if(ct>n)cout<<-1,exit(0);
		}
		ans+=a[ct];ct++;
	}
	cout<<ans;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
我们可以用双指针来解决这道题目。

将输入的两个数组进行从小到大排序，用 $i$ 和 $j$ 分别表示 $a$ 和 $b$ 数组的下标。如果 $b_j<a_i$，那么答案加上 $a_i$，并且 $j+1$，否则 $i+1$。最后输出答案。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#define int long long
#define il inline
il int read(){
 int x=0,t=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
 return x*t;
}
il void write(int x){
 if(x<0){putchar('-');x=-x;}
 if(x>9)write(x/10);
 putchar(x%10+'0');
}
#define rd read()
#define N 200005
int n,m,a[N],b[N];
signed main(){
	n=rd,m=rd;
	for(int i=0;i<n;i++)a[i]=rd;
	for(int i=0;i<m;i++)b[i]=rd;
	std::sort(a,a+n);
	std::sort(b,b+m);
	int j=0,i=0,ans=0;
	while(i<n&&j<m){
		if(a[i]>=b[j])ans+=a[i],j++;
		i++;
	}
	if(j==m)write(ans);
	else write(-1);
}
```

---

## 作者：T_TLucas_Yin (赞：0)

注意到，糖果数越少，礼盒花的钱就越少。所以要让给 $m$ 个人买礼物的总花费最少，就要让送出的总糖数最少；也就要在满足下限要求的情况下，送出的每个盒子里的糖都尽可能地少。

那么我们可以把 $m$ 个人的要求数量从小到大排序，再把 $n$ 个盒子里糖的数量从小到大排序。接下来顺序枚举每一个人，每人都分配给能满足要求的最少的一盒糖，总的花费自然就最少了。如果枚举到了最后一盒糖而人还没有送完，就说明无解。

最简单的一集。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[1000005],b[1000005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	long long k=1,sum=0;
	for(int i=1;i<=m;i++){
		while(a[k]<b[i]&&k<=n) k++;
		if(k<=n) sum+=a[k],k++;//跳出循环后k是满足要求的第一盒糖。注意一盒糖送出后就不能再用了，所以这里也要k++
		else{
			cout<<-1;
			return 0;
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：xixisuper (赞：0)

# AT_abc358_d [ABC358D] Souvenirs 题解

题外话，感觉这次 abc 怎么这么水啊。

本题解采用双指针。

## 思路

双指针裸题啊。

通过注意力不难想到对于任意一个 $B_i$，对应到大于等于 $B_i$ 且最小的那个 $A_j$ 最优，所以取的 $B_i$ 也是越小越好。

所以我们对 $A$ 和 $B$ 都排个序，双指针分别指向 $A$ 和 $B$ 首部，对于 $B_i$ 来说，如果当前 $A_j$ 小于 $B_i$ 则让 $A$ 上的指针右移，直至 $B_i \leq A_j$，然后答案加上 $A_j$，再让 $A$ 和 $B$ 上的指针都向右移。

当 $B$ 被取完或 $A$ 没得取的时候结束，输出当前答案即可。

时间复杂度 $O(n\log n + n)$。

## 代码

D 真的是我做过最水的一次，感觉这次最难的题是 E。

```cpp
#include <iostream>
#include <algorithm>
#define ll long long 
using namespace std;
const ll N=2e5+10;
ll n,m,A[N],B[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=n;i++) cin>>A[i];
	for(ll i=1;i<=m;i++) cin>>B[i];
	sort(A+1,A+1+n);
	sort(B+1,B+1+m);
	ll tpA=1,ans=0;
	for(ll i=1;i<=m;i++){
		while(tpA<=n&&A[tpA]<B[i]) tpA++;
		if(tpA>n){
			cout<<"-1";
			return 0;
		}
		ans+=A[tpA];
		tpA++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_d)
### 思路
我们可以将两个序列从小到大排序，此时，对于每个 $B_i$，它所需的糖果数必然大于 $B_{i-1}$，所以它所需的糖果数必然比上一次的糖果数高，也就只有比上次选择的糖果数多的糖果数可能满足条件，那么我们就可以设立一个指针，指向上一次选择糖果数的位置，每次将指针不断右移即可。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n,m;
	cin>>n>>m;
	long long a[n];
	long long b[m];
	for (long long i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for (long long j=0;j<m;j++)
	{
		cin>>b[j];
	}
	sort(a,a+n);
	sort(b,b+m);
	long long l=0,ans=0;
	for (long long i=0;i<m;i++)
	{
	  while(a[l]<b[i]&&l<n)
	  {
	    l=l+1;
	  }
	  if (l==n)
	  {
	    cout<<-1<<endl;
	    return 0;
	  }
	  ans=ans+a[l];
	  l=l+1;
	}
	cout<<ans<<endl;
}
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_d)
## 思路
一道贪心。先将 $a$，$b$ 从小到大排序，再枚举 $a$ 能选就选，不能选就跳过，最后判断是否都选了。

温馨提示：十年 OI 一场空，不开 long long 见祖宗。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, m;
int a[N], b[N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
    	scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++)
    	scanf("%d", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
    long long cur = 1, ans = 0;
    for (int i = 1; i <= n; i++)
    {
    	if (cur <= m && b[cur] <= a[i])
    	{
    		ans += a[i];
    		cur++;
		}
	}
	if (cur <= m) printf("-1\n"); // 注意判断 -1
	else printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Guoguo2013 (赞：0)

这题吧，说难不难，说简单那是真简单啊！

### 思路：
首先，先把两个数组从小到大排个序，然后遍历 $A$ 数组，依次判断这个礼物能否给 $B_1$，因为两个数组都是从小到大排序的，所以如果这个礼物能给 $B_1$，那肯定就是花费最小的，让答案加上这个礼物的价钱，然后以同样的方法再去判断 $B_2 \sim B_M$，由于 $B_i$ 一定大于等于 $B_{i-1}$，所以从当前位置接着往后判断就行了。  
如果整个 $A$ 数组都遍历完了而还有人没收到合适的礼物，那就肯定没有礼物分给他们了，输出 $-1$ 即可。

### 代码：
```
#include<bits/stdc++.h>
#define int long long
#define PII pair< int, int >
#define MII map< int, int >
#define MIB map< int, bool >

using namespace std;

const int N = 2e5 + 5, mod = 998244353;
int n, m, a[N], b[N], dn = 1, daan; // dn就是到哪，daan就是答案
signed main(){
//    freopen("a.in", "r", stdin);
//    freopen("a.out","w",stdout);
	scanf("%lld %lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= m; i++) scanf("%lld", &b[i]);
	sort(b + 1, b + m + 1);
	for (int i = 1; i <= n; i++){
		if (a[i] >= b[dn]){
			daan += a[i];
			dn++; // 接着判断下一个
		}
		if (dn == m + 1) break; // 如果所有人都遍历完了就退出
	}
	if (dn == m + 1) printf("%lld", daan);
	else printf("-1");
	return 0;
}

```

---

## 作者：wfirstzhang (赞：0)

# ABC358D
## 思路
### 选择方法
贪心思想。

如果当前要给需要 $B_i$ 个糖果的人发一个盒子，并且最省钱，那么需要选择剩余可以给并且满足他的要求的的糖果盒子中最便宜的。如果没有一个满足要求，即输出 $-1$ 并退出。

既然提到了最便宜，不妨先把盒子的价格从小到大排序，再用一个变量 $it$ 标记左端点。每次需要寻找时就把左端点一直增加，直到找到符合要求的第一个盒子，这个盒子即为最便宜的。

为了满足左端点 $it$ 不能左移的要求，需要使得需要糖果的数量也从小到大排一遍序。

选择的核心代码：

#### 预处理：
```cpp
sort(boxes.begin(), boxes.end());
sort(person.begin(), person.end());
```
#### 寻找符合的盒子
```cpp
while (it != boxes.end() && (*it < person[i] || vis[it - boxes.begin()]))
			it++;               //右移左端点
		if (it == boxes.end()) {//搜索不到符合要求的
			cout << -1 << endl;
			return 0;
		}
```
### 标记
首先考虑获取下标，用于在布尔数组中标记。有一个前置知识：假设声明了一个 `vector<long>::iterator it` 和一个 `vector<long> v`。那么获取 `it` 所在的下标就是 `it - v.begin()`。

如此，就可以直接用寻找到的 $it$ 标记了，而不需要重新开一个下标变量来寻找。

核心代码：
```cpp
vis[it - boxes.begin()] = true;//打标记
```
### 统计
每次买第 $i$ 个盒子用 $A_i$ 元，可以用变量 $sum$ 统计。每次使得 $sum \gets sum + A_i$。

核心代码：
```cpp
sum += *it;
```
### 注意事项
1. 需要使用 `int64_t` 长整数类型，因为最多就是 $M$ 个人全选上盒子了，每个盒子都有 $10^9$ 元。一共就是 $2 \times 10^5 \times 10^9 = 2 \times 10^{14}$ 元，用 `int` 肯定是不够的。
1. `vector` 在声明时直接指定初始长度，如 `vector<long> boxes(n);`，否则最开始不能使用下标访问，而要一个一个 `push_back()`。
## AC Code
```cpp
#include <bits/stdc++.h>
long n, m, sum;
bool vis[524288];//标记数组
int main() {
	using namespace std;
	cin >> n >> m;
	vector<long> boxes(n);
	vector<long> person(m);
	for (int i = 0; i < n; i++)
		cin >> boxes[i];
	for (int i = 0; i < m; i++)
		cin >> person[i];
	sort(boxes.begin(), boxes.end());
	sort(person.begin(), person.end());
	auto it = boxes.begin();//从头开始
	for (int i = 0; i < m; i++) {
		while (it != boxes.end() && (*it < person[i] || vis[it - boxes.begin()]))
			it++;               //右移左端点
		if (it == boxes.end()) {//搜索不到符合要求的
			cout << -1 << endl;
			return 0;
		}
		sum += *it;
		vis[it - boxes.begin()] = true;//打标记
	}
	cout << sum << endl;
	return 0;
}
```

---

## 作者：yegengghost (赞：0)

如果我早知道有那么简单……

这个题可以用双指针来做：

该题考虑贪心，因为最小答案得让我们对获得糖数最小的人花钱最少。

对两个数组排序，用一个指针找最前面的符合答案值，再依次累加即可。

或者看下代码也未尝不可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m;
int a[N];
int req[N]; 
int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
signed main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=m;i++)
		req[i]=read();
	sort(a+1,a+1+n);
	sort(req+1,req+1+m);
	int ptr1,ptr2,ans=0;
	//类似于head与tail。 
	ptr1=ptr2=1;
	while(ptr2<=m)
	{
		while(ptr1<=n&&a[ptr1]<req[ptr2])
			ptr1++;//核心：找到第一个有贡献的答案。
		if(ptr1>n)//若数组越界则无解
		{
			cout<<-1<<'\n';
			return 0;
		}
		ans+=a[ptr1++];
		ptr2++;//每一次将后面的指针后移
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/AT_abc358_d)
## 题目翻译
AtCoder 乐园出售 $N$ 种纪念品盒子，标号依次为 $1\sim N$，盒子 $i$ 的价格为 $A_i$ 元，有 $A_i$ 个糖果。

高桥要从中买 $M$ 个盒子，然后分别给每个人各一个盒子，第 $i$ 个人的盒子中至少要有 $B_i$ 个糖果。

请问高桥是否能买到符合要求的 $M$ 个盒子，如果能就输出高桥所需要的最小金额，如果不能就输出 `-1`。
## 题目分析
为了让金额最小，所以给第 $i$ 个人买的盒子中的糖果数量得是大于等于 $B_i$ 的数中，最小的一个。如果 $A$ 和 $B$ 都是升序序列，再设 $A$ 中大于等于 $B_i$ 的数中的最小的一个是 $A_j$，那么 $A$ 中大于等于 $B_{i+1}$ 的数中最小的一个数的下标绝对大于 $j$。所以可以先将 $A$ 和 $B$ 进行升序排序，然后一个个寻找。需要注意的是，再续找的过程中还要判断是否有可行的方案。
## Code
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n,m,a[200000],b[200000],ans=0;
	cin>>n>>m;
	for(int i=0;i<n;++i) cin>>a[i];
	for(int i=0;i<m;++i) cin>>b[i];
	sort(a,a+n);
	sort(b,b+m);
	for(int i=0;i<m;++i)
		for(static int j=0;j<n;++j) {
			if(n-j<m-i||(a[j]<b[i]&&n-j==m-i)) {//如果剩余的盒子数量不够就输出-1
				cout<<-1;
				return 0;
			}
			if(a[j]>=b[i]) {
				ans+=a[j];//累加最小金额
				++j;//这里还要将下标加1
				break;
			}
		}
	cout<<ans;
	return 0;
}
```

---

## 作者：qhr2023 (赞：0)

## 题意

有 $N$ 个盒子，盒子 $i$ 的价格为 $A_i$，有$A_i$ 个糖。

从中买 $M$ 个，使第 $i$ 个能至少有 $B_i$ 个糖。

求是否有满足条件的 $M$，如有，求最小总金额。

## 思路

贪心，对于每个 $B_i$，我们要在 $A$ 中找到第一个小于他的数，这样匹配下去一定是最优策略，如果没有找到，就不合法。

用贪心加双指针实现即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a[200005], b[200005];
long long ans;
int main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++)
		cin >> a[i];
	for(int i=1; i<=m; i++)
		cin >> b[i];
	sort(a+1, a+n+1);
	sort(b+1, b+m+1);
	for(int i=1, j=1, f=0; i<=m; i++, j++){
		for( ; j<=n; j++)
			if(a[j]>=b[i]){
				f++;
				ans+=a[j];
				break;
			}
		if(f!=i){
			cout << -1;
			return 0;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc358_d [ABC358D] Souvenirs
### 题目大意

有 $N$ 个盒子，每个盒子里有 $A_i$ 个糖。现在有 $M$ 个人，每个人需要至少 $B_i$ 颗糖，并且每个人只能拿一个盒子。问能否满足所有人，满足时输出最少的糖需要量，不满足输出 $-1$。

数据范围为 $1 \le N,M \le 2 \times 10^5,1 \le A_i,B_i \le  10^9$。

---
### 题解

看到“至少”和“最少”，我们可以想到“最大的最小”——二分。不过，这道题有一个条件，就是盒子不能重复。所以，我们开一个数组 `vis` 来记录盒子的访问情况，在二分找到解时向糖果更多的盒子方向遍历找到第一个未被访问的盒子。

具体地，我们为了将时间控制在 $O(n \log n)$ 中，我们采取倍增实现这个遍历的功能。为了在倍增时保持 `vis` 数组的局部有序使得倍增正确，我们可以同样将 $B$ 数组排序，这样就可以保证在当前找到的最小值到 $N$ 的 `vis` 数组实现有序。

**注意：开 `long long`，`vis` 开双倍！**

完整代码：
```cpp

#include <algorithm>
#include <vector> 
#include <cstdio>
using namespace std;

#define int long long
int vis[400010];//倍增时可能超一倍，所以开双倍空间，要不要RE 
int a[200010];
int b[200010];
int n, m, ans;

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= m; ++i) {
		scanf("%lld", &b[i]);
	}
	sort(b + 1, b + 1 + m);
	for (int i = 1; i <= m; ++i) {
		int k = lower_bound(a + 1, a + 1 + n, b[i]) - a;//二分 
		int t = 1;//倍增 
		while (vis[k] && t) {
			while (t && vis[k + t] == 0)	t >>= 1;
			k += t;
			t <<= 1;
		}
		if (vis[k])	k++;
		if (k == n + 1)	{//判无解 
			ans = -1;
			break;
		}
		ans += a[k];
		vis[k] = 1;
	}
	printf("%lld", ans);
	return 0;
}

```

---

## 作者：Cosine_Func (赞：0)

二分加贪心。半小时场切。

看到 $2 \times 10^{5}$ 的数据范围就知道，肯定是 $O(n \log n)$ 的解法。题目要求最小值，明显是贪心。

先给两个数组升序排序（保证最近，从而使差距最小），然后遍历 $B$，每次二分找到第一个未被访问且大于等于 $B_i$ 的数，并计入答案。如果此时找到的数 $x$ 不满足 $x \ge B_i$，那么已经无解，输出 `-1`。

注意：要开 `long long` ！！！

[血的教训](https://atcoder.jp/contests/abc358/submissions/54586332)

[参考代码](https://atcoder.jp/contests/abc358/submissions/54586856)

---

