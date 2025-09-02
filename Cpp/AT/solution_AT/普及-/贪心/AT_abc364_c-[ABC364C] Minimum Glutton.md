# [ABC364C] Minimum Glutton

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc364/tasks/abc364_c

$ N $ 個の料理があり、$ i $ 個目の料理の**甘さ**は $ A_i $、**しょっぱさ**は $ B_i $ です。

高橋君はこれらの $ N $ 個の料理を好きな順番で並べ、その順に食べようとします。

高橋君は並べた順番の通りに料理を食べていきますが、食べた料理の甘さの合計が $ X $ より大きくなるかしょっぱさの合計が $ Y $ より大きくなるとその時点で食べるのをやめます。

高橋君が食べることになる料理の個数としてあり得る最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ X,\ Y\ \leq\ 2\ \times\ 10^{14} $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 10^9 $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ i $ 個目の料理のことを料理 $ i $ と書きます。 高橋君が $ 4 $ 個の料理を料理 $ 2,\ 3,\ 1,\ 4 $ の順に並べ替えたとき、料理 $ 2,\ 3 $ を食べた時点での食べた料理の甘さの合計が $ 8 $ となり $ 7 $ より大きくなります。したがってこの場合は高橋君が食べることになる料理の個数は $ 2 $ 個です。 高橋君が食べる料理の個数が $ 1 $ 個以下になることはないため、$ 2 $ を出力します。

## 样例 #1

### 输入

```
4 7 18
2 3 5 1
8 8 1 4```

### 输出

```
2```

## 样例 #2

### 输入

```
5 200000000000000 200000000000000
1 1 1 1 1
2 2 2 2 2```

### 输出

```
5```

## 样例 #3

### 输入

```
8 30 30
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1```

### 输出

```
6```

# 题解

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc364_c)

### 思路

这道题要求：只要甜度和咸度其中有一项超标，高桥就不会吃了。于是，我们可以分别求出光吃最甜的和光吃最咸的能吃几道菜，取两个答案的最小值即可。

**注意事项**

- 不开 `long long` 见祖宗。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e5+10;
int n,a[N],b[N];
long long x,y;
bool cmp(int xx,int yy){
	return xx>yy;
}
int calc_a(){
	long long sum_a=0;
	for(int i=1;i<=n;++i){
		sum_a+=a[i];
		if(sum_a>x)
			return i;
	}
	return n;
}
int calc_b(){
	long long sum_b=0;
	for(int i=1;i<=n;++i){
		sum_b+=b[i];
		if(sum_b>y)
			return i;
	}
	return n;
}
int main(){
	scanf("%d%lld%lld",&n,&x,&y);
	for(int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)
		b[i]=read();
	sort(b+1,b+n+1,cmp);
	printf("%d\n",min(calc_a(),calc_b()));
	return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：6)

## 题意

---

题目给了我们 $N$ 组数对，第 $i$ 个数对包含两个整数 $A_i$ 和 $B_i$。我们可以随意排序，排序后从第一个数对依次向后相加。将 $A_i$ 的相加结果记为 $S_a$，将 $B_i$ 的相加结果记为 $S_b$。找到一种排序方式使得 $S_a > X$ 或者 $S_b > Y$，且相加次数最小。
## 解法

---

考虑到 $S_a$ 和 $S_b$ 只要有一个值满足条件就可以记录答案了，不难想出将所有数对分别按照 $A_i$ 和 $B_i$ 的值从大到小排序两次，比较哪一种方法相加次数更少。但值得注意的是，不管按照以上哪种方式排序，在遍历数对的过程中，不是进行比较的值也需要相加并判断。例如按照 $A_i$ 排序，在遍历过程中 $B_i$ 的值也是需要相加的，因为在这种排序方法下，仍然可能 $S_b$ 比 $S_b$ 更早满足条件。也就是说，我们一共需要排序两次，取最小次数。
## 代码

---

在编写代码时注意可以特殊判断 $A_i > X$ 和 $B_i > Y$ 的情况，因为一个数对就可以满足条件，直接输出 $1$。

```cpp
#include<bits/stdc++.h>
#define int long long
//这道题数据很大，必须开 long long 
using namespace std;
const int N=2e5+5;
int aa=N,bb=N; //以两种方式排序的最小相加次数 
struct num{ //定义结构体以表示数对 
	int a,b;
}t[N];
bool cmpa(num p,num q){ //以a值排序 
	return p.a>q.a;
}
bool cmpb(num p,num q){ //以b值排序
	return p.b>q.b;
}
signed main(){
	int n,x,y;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>t[i].a;
		if(t[i].a>x){ //一个数对就可以满足条件 
			cout<<1;
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		cin>>t[i].b;
		if(t[i].b>y){ //特殊判断
			cout<<1;
			return 0;
		}
	}
	sort(t+1,t+n+1,cmpa); //第一种排序方式 
	int suma=0,sumb=0; //a值的和以及b值的和 
	for(int i=1;i<=n;i++){
		suma+=t[i].a;
		sumb+=t[i].b;
		if(suma>x || sumb>y){ //满足条件 
			aa=i; //记录当前次数 
			break;
		}
	}
	sort(t+1,t+n+1,cmpb); //第二种排序方式 
	suma=0,sumb=0; //初始化为0 
	for(int i=1;i<=n;i++){
		suma+=t[i].a;
		sumb+=t[i].b;
		if(suma>x || sumb>y){ //满足条件 
			bb=i;
			break;
		}
	}
	if(min(aa,bb)>n) //全部相加都满足不了条件 
		cout<<n;
	else //可以不全部相加 
		cout<<min(aa,bb);
	return 0;
}
```

---

## 作者：Barryb (赞：3)

# 思路
这道题是个很明显的贪心，要让高桥吃的菜尽可能少，就要让他吃的菜的甜度或咸度尽可能多。因为可以从任意一个位置开始，所以只要把两个数组分别从大到小排序，再用两个位置变量和两个求总和的变量扫两个数组，如果甜度和大于 $X$ 或咸度和大于 $Y$，直接取个最小位置，跳出循环，最后输出就好了。
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,s1,s2,a[2000010],b[2000010];
signed main()
{
	cin>>n>>x>>y;
	int minn=n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	sort(a+1,a+n+1,greater<int>());
	sort(b+1,b+n+1,greater<int>());
	for(int i=1;i<=n;i++) {
		s1+=a[i];
		if(s1>x) {
			minn=min(i,minn);
			break;
		}
	}
	for(int i=1;i<=n;i++) {
		s2+=b[i];
		if(s2>y) {
			minn=min(i,minn);
			break;
		}
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：Hughpig (赞：3)

要让高桥吃的菜尽可能少，就要让他吃的菜的甜度或咸度尽可能高。

考虑贪心，把这些菜按照甜度从大到小排序，扫一遍计算要让甜度超过 $X$ 至少要多少菜；再按咸度排序，同理计算要让咸度超过 $Y$ 至少要多少菜。两者取最小值即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define up(l,r,i) for(int i=(l);(i)<=(r);++i)
ll n,x,y,ans;

constexpr int N=2e5+7;

struct dish{
	ll a,b;
}a[N];

bool c1(dish a,dish b){
	return a.a>b.a;
}

bool c2(dish a,dish b){
	return a.b>b.b;
}

int main()
{
   	cin>>n>>x>>y;
   	up(1,n,i)cin>>a[i].a;
   	up(1,n,i)cin>>a[i].b;
   	sort(a+1,a+n+1,c1);
   	ll s=0;
   	up(1,n,i){
    	s+=a[i].a;
    	if(s>x||i==n){
    		ans=i;
    		break;
		}
	}
	s=0;
	sort(a+1,a+n+1,c2);
    up(1,n,i){
    	s+=a[i].b;
    	if(s>y||i==n){
    		ans=min(ans,(ll)i);
    		break;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：__int1024 (赞：2)

# AT_abc364_c 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc364_c)  
## 思路
贪心。  
分两种情况考虑，第一种是按甜度降序排列，第二种是按咸度降序排列，能吃菜品数的最小值一定是这两种顺序能吃菜品数的最小值。  
**注意：并不是按甜度排序咸度就不用判断了，相反也一样。**
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define debug cerr<<"The code runs successfully.\n";
#define endl '\n'
#define TRACE 1
#define tcout TRACE && cout
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int P = 998244353; 
const int Base = 3221225477;
const int INF = 0x3f3f3f3f3f3f3f3f; 
const int N = 2e5 + 10, M = 2e6 + 10;
struct node
{
	int sweet,salt;
}a[N],b[N]; //a数组按甜度降序排列，b数组按咸度降序排列
bool cmpa(node q,node p)
{
	return (q.sweet>p.sweet);
}
bool cmpb(node q,node p)
{
	return (q.salt>p.salt);
}
int n,x,y;
inline int func1()//计算a数组能吃菜品数
{
	int sum1=0,sum2=0,ans=0;
	for(int i=0;i<n;i++)
	{
		ans++;
		if((sum1+a[i].sweet)<=x&&(sum2+a[i].salt)<=y)
		{
			sum1+=a[i].sweet;
			sum2+=a[i].salt;
		}
		else
		{
			break;
		}
	}
	return ans;
}
inline int func2()//计算b数组能吃菜品数
{
	int sum1=0,sum2=0,ans=0;
	for(int i=0;i<n;i++)
	{
		ans++;
		if((sum1+b[i].sweet)<=x&&(sum2+b[i].salt)<=y)
		{
			sum1+=b[i].sweet;
			sum2+=b[i].salt;
		}
		else
		{
			break;
		}
	}
	return ans;
}
signed main()
{
	fst;
	cin>>n>>x>>y;
	for(int i=0;i<n;i++)
	{
		cin>>a[i].sweet;
		b[i].sweet=a[i].sweet;
	}
	for(int i=0;i<n;i++)
	{
		cin>>a[i].salt;
		b[i].salt=a[i].salt;
	}
	//排序
	sort(a,a+n,cmpa);
	sort(b,b+n,cmpb);
	cout<<min(func1(),func2());//取最小值输出
	return 0;
}


```

---

## 作者：ecxjs (赞：1)

定义结构体，将每一个食物中定义两个变量：酸和甜

$a$ 代表酸, $b$ 代表甜

考虑到要求吃的最小值，所以有两种情况可能最优。

1. 因为酸味超限结束。

为了最快达到超限，我们把 $a_i$ 从大到小进行排序，直到超限。

2. 因为咸味超限结束。

同理，把 $b_i$ 从大到小排序，直到超限。



最后，取两者最小值。

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,x,y;
struct cai{
	int a,b;
}c[200005];
bool cmpa(cai x,cai y){
	return x.a>y.a;
}
bool cmpb(cai x,cai y){
	return x.b>y.b;
}
signed main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>c[i].a;
	}
	for(int i=1;i<=n;i++){
		cin>>c[i].b;
	}
	int ansa=0,ansb=0;
	int na=0,nb=0;
	sort(c+1,c+n+1,cmpa);
	for(int i=1;i<=n;i++){
		na+=c[i].a;
		if(na>x){
			ansa++;
			break;
		}
		ansa++;
	}
//	cout<<"ansa="<<ansa<<endl;
	sort(c+1,c+n+1,cmpb);
	for(int i=1;i<=n;i++){
		nb+=c[i].b;
		if(nb>y){
			ansb++;
			break;
		}
		ansb++;
	}
//	cout<<"ansb="<<ansa<<endl;
	cout<<min(ansa,ansb);
	return 0;
}

---

## 作者：OIerWu_829 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc364_c)

不会有比我更笨的人了吧，调了半天结构体然后发现用数组就可以。

就因为这题排名大减，下一场得加油了啊。

---

直接按照题意模拟。分别把 $A$ 数组和 $B$ 数组从大到小排序，然后不断累加甜度和咸度，如果甜度大于 $X$ 或咸度大于 $Y$，那就输出 $i$ 结束程序。如果到最后都没有超过，就输出 $n$。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const LL N = 2e5 + 5;

LL a[N], b[N];

int main()
{
  LL n, x, y;
  cin >> n >> x >> y;
  for (LL i = 1; i <= n; i++)
  {
    cin >> a[i];
  }
  sort(a + 1, a + 1 + n, greater<int>());
  for (LL i = 1; i <= n; i++)
  {
    cin >> b[i];
  }
  sort(b + 1, b + 1 + n, greater<int>());
  LL sw = 0, sa = 0;
  for (LL i = 1; i <= n; i++)
  {
    sw += a[i];
    sa += b[i];
    if (sw > x || sa > y)
    {
      cout << i << "\n";
      return 0;
    }
  }
  cout << n << "\n";
  return 0;
}
```

---

## 作者：a1111a (赞：1)

# 思路
要让他吃的菜少，就要让他从最甜的开始吃，记录能吃的数量，再从最咸的开始吃，记录能吃的数量，再输出这两个数量的最小值。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,ans;
struct node{
	int a,b;
}c[200002];
bool cmp1(node x,node y){
	return x.a>y.a;
}
bool cmp2(node x,node y){
	return x.b>y.b;
}
int main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
		cin>>c[i].a;
	for(int i=1;i<=n;i++)
		cin>>c[i].b;
	sort(c+1,c+n+1,cmp1);
	long long cnt=0,z=n;
	for(int i=1;i<=n;i++){
		cnt+=c[i].a;
		if(cnt>x){
			z=i;
			break;
		}
	}
	ans=z;
	sort(c+1,c+n+1,cmp2);
	cnt=0;
	z=n;
	for(int i=1;i<=n;i++){
		cnt+=c[i].b;
		if(cnt>y){
			z=i;
			break;
		}
	}
	cout<<min(ans,z);
	return 0;
}
```

---

## 作者：Magus (赞：0)

## 题意

一共有 $N$ 道菜，每道菜的甜度是 $A_i$，咸度是 $B_i$。

`Magus` 按照自己喜欢的顺序排列这些菜，然后按顺序吃。

`Magus` 按照排列完后的顺序去吃料理，如果吃的料理的甜度合计比 $X$ 大或咸度合计比 $Y$ 大的话就不吃了。

求 `Magus` 吃的料理的个数可能的最小值。

## 题解

考虑贪心。

很难不发现要想让 `Magus` 吃的少那么我们就需要让 `Magus` 吃的食物甜度或咸度尽可能高。

于是我们先将 $A_i$ 和 $B_i$ 从大到小排序，然后开两个 $cnt$ 用来记录当前的甜度和咸度。再遍历，如果其中记录甜度的 $cnt$ 超过了 $X$ 或记录咸度的 $cnt$ 超过了 $Y$ 那么就输出当前吃了多少个食物并跳出循环，否则输出 $n$ 即可。

```cpp
#include<bits/stdc++.h>
#define FastIO ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define int long long
#define I using
#define AK namespace
#define NOIP2024 std
I AK NOIP2024;
const int maxn=1e7+10,maxm=1e3+10,mod=998244353;
int n,m,x,y,cnt1,cnt2,arr[maxn],arr_II[maxn],arr_2d[maxm][maxm];
int cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	FastIO;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
	{
		cin>>arr[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>arr_II[i];
	}
	stable_sort(arr+1,arr+n+1,cmp);
	stable_sort(arr_II+1,arr_II+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		cnt1+=arr[i];
		cnt2+=arr_II[i];
		if(cnt1>x or cnt2>y)
		{
			cout<<i; 
			return 0;
		}
	}
	cout<<n;
	return 0;
}
```

---

## 作者：Your_Name (赞：0)

### 思路

贪心，因为要吃的菜最少，所以优先吃更咸或者更甜的。

但我们不知道是咸的先达到阈值还是甜的先到，所有我们两个都扫一遍，最后取最小值。（但在求最多的时候就不能这么做，因为甜和咸会相互影响）

为什么可以这样单独看呢？

首先，假设只排序咸的的菜数不是最优解，那么一定是甜的超过了阈值，但这个是在只排序咸的的情况下的，按道理来说这个排序并没有保证对甜的来说是最优解，而甜的的最优解自然就是单独看的结果，因此，真正的最优解就是两边取最小。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e5 + 10;
LL n, x, y, a[N], b[N], ansx, ansy, now;
bool cmp(LL a, LL b){
    return a > b;
}
int main(){
    cin >> n >> x >> y;
    for(LL i = 1; i <= n; i ++){
        cin >> a[i];
    }
    sort(a + 1, a + n + 1, cmp);
    for(LL i = 1; i <= n; i ++){
        if(now + a[i] > x || i == n){
            ansx = i;
            break;
        }
        now += a[i];
    }
    now = 0;
    for(LL i = 1; i <= n; i ++){
        cin >> b[i];
    }
    sort(b + 1, b + n + 1, cmp);
    for(LL i = 1; i <= n; i ++){
        if(now + b[i] > y || i == n){
            ansy = i;
            break;
        }
        now += b[i];
    }
    cout << min(ansx, ansy);
    return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路

考虑贪心。

对于甜度和咸度分别**从大到小**排序，因为要让其中的一个值尽可能更快地高于阈值，所以要快速的“堆叠”其中的一个值。随后分别跑一遍即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,cnt,tmp,cnt1;
struct node{
	long long a;
	long long b;
}d[200011];
bool cmp1(node t1,node t2){
	return t1.a>t2.a;
}
bool cmp2(node t1,node t2){
	return t1.b>t2.b;
}
int main(){
	scanf("%lld%lld%lld",&n,&x,&y);
	for(int i=1;i<=n;i++) scanf("%lld",&d[i].a);
	for(int i=1;i<=n;i++) scanf("%lld",&d[i].b);
	sort(d+1,d+1+n,cmp1);
	for(int i=1;i<=n;i++){
		tmp+=d[i].a;
		cnt++;
		if(tmp>x){
			break;
		}
	}
	sort(d+1,d+1+n,cmp2);
	tmp=0;
	for(int i=1;i<=n;i++){
		tmp+=d[i].b;
		cnt1++;
		if(tmp>y){
			break;
		}
	}
	printf("%lld",min(cnt,cnt1));
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

一眼贪心。

想让高桥吃的菜尽量少，就要让它吃的菜尽量咸或甜，那么只需要将甜度和咸度排个序，从大到小吃，每吃一次，咸度和甜度都会加，当吃不了了停止。

**十年 OI 一场空，不开 ```long long``` 见祖宗。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int a[N],b[N];
signed main()
{
	int n;
	long long x,y;
	scanf("%d %lld %lld",&n,&x,&y);
	for(int i = 1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i = 1;i<=n;i++)
	{
		scanf("%d",&b[i]);
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	long long num1 = 0;
	long long num2 = 0;
	int ans = 0;
	for(int i = n;i>=1;i--)//先选甜咸度大的
	{
		num1+=a[i];//加上
		num2+=b[i];
		ans++;//吃了一道菜
		if(num1>x||num2>y)//超过限制
		{
			printf("%d",ans);//停止用餐
			return 0;
		}
	}
	printf("%d",ans);//如果一直没有超过限制，输出
	return 0;
}
```

---

## 作者：Wei_Han (赞：0)

读完题还以为是 dp，发现求菜品最小值，如果同时兼顾 $X$ 和 $Y$ 显然是更劣的，分别按照 $a_i$ 和 $b_i$ 排序之后求别累加看什么时候超过限定值再求最小值即可。

```cpp
// LUOGU_RID: 169946472
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
#define fi first
#define se second
//#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
const int N=1e6+1e5+5,M=1e7+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll x,y,n,m,c,d,e,f,g,flag=1;
string s,t;
struct node{
	ll ai,bi;
}a[N];
inline bool cmp1(node x,node y){
	return x.ai>y.ai;
}
inline bool cmp2(node x,node y){
	return x.bi>y.bi;
}
signed main(){
	read(n),read(x),read(y);
	fo(1,i,n) read(a[i].ai);
	fo(1,i,n) read(a[i].bi);
	sort(a+1,a+1+n,cmp1);
	ll sum=0,maxx=n;
	fo(1,i,n){sum+=a[i].ai;if(sum>x){maxx=min(maxx,i);break;}}
	sort(a+1,a+1+n,cmp2);
	sum=0;
	fo(1,i,n){sum+=a[i].bi;if(sum>y){maxx=min(maxx,i);break;}}
	wr(maxx);pr;
	return 0;
}	
``````

---

## 作者：IronMen (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc364_c)

[AtCoder链接](https://atcoder.jp/contests/abc364/tasks/abc364_c)

## 题目
有 $N$ 道菜，其中第 $i$ 道菜的**甜度**为 $A_i$，**咸度**为 $B_i$。

高桥打算将这 $N$ 道菜按照自己喜欢的顺序排列，然后按照这个顺序吃掉。

他会按照排列的顺序吃菜，但是他一旦吃过的菜的总甜度超过 $X$ 或总咸度超过 $Y$，他就会停止进食。

求他最终最少吃掉多少菜。

---
## 思路
想要吃掉的菜最少，那么就要尽早让甜度达到 $X$ 或让咸度达到 $Y$。显然，$A_i$ 和 $B_i$ 都要按降序排列。

然后，再计算达到甜度要吃多少，达到咸度要吃多少，最后两者最小值即为答案。

---
### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

long long n, x, y, a[200010], b[200010], ca, cb, cx, cy;

bool cmp(long long a, long long b)
{
	return a > b;
}

int main()
{
	scanf("%lld %lld %lld", &n, &x, &y);
	for (long long i = 0; i < n; i ++ )
		scanf("%lld", &a[i]);
	for (long long i = 0; i < n; i ++ )
		scanf("%lld", &b[i]);
	sort(a, a + n, cmp);
	sort(b, b + n, cmp);
	for (long long i = 0; i < n; i ++ )
	{
		ca += a[i];
		cx ++;
		if (ca > x)
			break;
	}
	for (long long i = 0; i < n; i ++ )
	{
		cb += b[i];
		cy ++;
		if (cb > y)
			break;
	}
	cout << min(cx, cy) << '\n';
	return 0;
}
```

---

## 作者：zjj2024 (赞：0)

### 思路

考虑贪心。

由于只要有一种口味超过范围，则结束，所以要么让甜味最先超过，要么让咸味最先超过，两种方法答案的最小值中最小的就是答案。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
struct T
{
	ll a,b;
}a[N];
bool cmp1(T a,T b)//按甜味排序
{
	return a.a>b.a;
}
bool cmp2(T a,T b)//按咸味排序
{
	return a.b>b.b;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n,x,y;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].a;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].b;
	}
	sort(a+1,a+n+1,cmp1);
	ll ans=0,sum=0,r;
	for(int i=1;i<=n;i++)
	{
		r=i;
		sum+=a[i].a;
		if(sum>x)break;//判断是否超过
	}
	ans=r;
	sort(a+1,a+n+1,cmp2);
	sum=0;
	for(int i=1;i<=n;i++)
	{
		r=i;
		sum+=a[i].b;
		if(sum>y)break;
	}
	ans=min(ans,r);//两种答案中最小的
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：_colin1112_ (赞：0)

# 思路

贪心。既然要让主人公吃的最少，就要让他每盘吃的咸度或甜度尽可能大，所以只需对咸度与甜度数组进行从小到大排序，分别计算出主人公什么时候会吃不下（即甜度大于 $x$ 或咸度大于 $y$），两者答案取最小值即可。

##  AC code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E = 1e6 + 5;
ll n, x, y, cnt, cnt1, sum, sum1;
ll a[E], b[E];
int main()
{
    cin >> n >> x >> y;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    sort(a + 1, a + 1 + n, greater<ll>());
    for (int i = 1; i <= n; i++)
    {
        cnt++;
        sum += a[i];
        if (sum > x)
            break;
    }
    sort(b + 1, b + 1 + n, greater<ll>());
    for (int i = 1; i <= n; i++)
    {
        cnt1++;
        sum1 += b[i];
        if (sum1 > y)
            break;
    }
    cout << min(cnt, cnt1);
    return 0;
}
```

---

## 作者：jiangruibo (赞：0)

### 思路：
要想使得她吃的菜最少，那么一定要让**咸度**或者**甜度**更高，所以我们优先考虑用**贪心**将每一道菜按咸度从大到小排序，再按甜度从大到小排序，从两种排序中选取符合条件的最小值就行了。

### 代码：

```cpp
#include <bits/stdc++.h>
#define AK 0
#define IOI ;
#define I return
#define int long long
#define lowbit(x) ((x)&-(x))
#define ull unsigned long long
using namespace std;

char c[55][55];
struct node
{
	int a,b;
};
node p[200010];
bool cmp1(node x,node y)
{
	return x.a>y.a;
}
bool cmp2(node x,node y)
{
	return x.b>y.b;
}
signed main()
{
	int n;
	cin>>n;
	int x,y;
	cin>>x>>y;
	for(int i=1;i<=n;i++) cin>>p[i].a;
	for(int i=1;i<=n;i++) cin>>p[i].b;
	sort(p+1,p+n+1,cmp1);
	int sum=0;
	int ans=n;
	for(int i=1;i<=n;i++)
	{
		sum+=p[i].a;
		if(sum>x)
		{
			ans=i;
			break;
		}
	}
	int minn=ans;
	ans=n;
	sum=0;
	sort(p+1,p+n+1,cmp2);
	for(int i=1;i<=n;i++)
	{
		sum+=p[i].b;
		if(sum>y)
		{
			ans=i;
			break;
		}
	 } 
	 minn=min(minn,ans);
	 cout<<minn<<endl;
	I AK IOI
}
/*
 */
 

```

---

## 作者：Moya_Rao (赞：0)

# 题目大意
给定 $n$ 道菜的甜度和咸度。当高桥吃的总甜度大于 $X$ 或吃的总咸度大于 $Y$ 时，他就不会吃了。现在想知道，如果能按照随意的顺序吃，最少要吃几道菜。

# 主要思路
题目很明了了。  
最少？那不就是贪心吗？难到还会往别处想？

我们来贪心。  
首先把所有的甜度和咸度**分开**装在两个数组里，**不要用一个结构体一起装**。  
接着按从大到小的顺序排个序。因为我们想吃的尽可能少，所以要优先吃甜度或咸度大的。  
再来遍历，看在每种情况下（甜度和咸度分开看）至少要吃几道菜。  
最后，取按甜度要吃的最少菜数和按咸度要吃的最少菜数的较小值，输出。

题目其实很简单，可万万不要想复杂了。

# 赛时代码
友善一点，放上一个赛时的 [AC](https://atcoder.jp/contests/abc364/submissions/56015076) 代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
long long n,x,y,a[N],b[N],ca,suma,cb,sumb;
bool cmp(long long xx,long long yy){return xx>yy;}
int main(){
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n;i++){
        suma+=a[i];
        ca++;
        if(suma>x)break;
    }
    for(int i=1;i<=n;i++){
        sumb+=b[i];
        cb++;
        if(sumb>y)break;
    }
    cout<<min(ca,cb);
    return 0;
}
```
都看到这里了，各位行行好，给个赞吧！

---

## 作者：T_TLucas_Yin (赞：0)

根据题目，想要达成没法再吃，肯定要满足甜度或咸度中的一个超过了上限（这里排除可以吃完所有菜的情况）。

那么，按一定顺序吃菜使得甜度或咸度中的一种最快超过上限的方案即是整个题目的最优方案。

所以，先看按甜度从大到小的顺序吃菜最少吃几盘，再看咸度从大到小最少吃几盘，从中取最小值即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y;
struct node{
	int x,y;
}f[1000005];
bool cmp1(node a,node b){
	return a.x>b.x;
}
bool cmp2(node a,node b){
	return a.y>b.y;
}
int sum;
signed main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++) cin>>f[i].x;
	for(int i=1;i<=n;i++) cin>>f[i].y;
	sort(f+1,f+1+n,cmp1);//按甜度排序模拟
	int i=1,cnt=0;
	sum=0x3f3f3f3f;
	while(i<=n&&x>=0) x-=f[i].x,i++,cnt++;
	sum=min(sum,cnt),cnt=0;
	i=1;
	sort(f+1,f+1+n,cmp2);//按咸度排序模拟
	while(i<=n&&y>=0) y-=f[i].y,i++,cnt++;
	sum=min(sum,cnt),cnt=0;
	cout<<sum;
	return 0;
}
```

---

## 作者：Hacker_Cracker (赞：0)

## AT_abc364_c Minimum Glutton 题解
### Solution
#### 题意
给你 $n$ 道菜的甜度 $a_i$ 和咸度 $b_i$ ，当你吃的甜度总和超过 $x$ 或咸度总和超过 $y$ 时，你就不能再吃了。你可以任意排列这些菜，求最少能吃几道菜。
#### 解法
本题采取贪心。

首先，我们把储存甜度的数组和储存咸度的数组从大到小排序，因为这样可以让我们吃尽量少的菜。又因为如果甜度总和超过上限**或**咸度总和超过上限，就必须停止，所以我们分别遍历一次 $a$ 和 $b$ 数组，将两个最少能吃得菜的数量取最小值即可。

### [AC](https://www.luogu.com.cn/record/169877412) Code
```cpp
#include<iostream>
#include<algorithm> 
using namespace std;
const int N=2e5+10;
int sw[N],sal[N],n;
long long x,y,sum1,sum2,mn1,mn2;
bool cmp(int a,int b){return a>b;}
int main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++) cin>>sw[i];
	for(int i=1;i<=n;i++) cin>>sal[i];
	sort(sw+1,sw+n+1,cmp);
	sort(sal+1,sal+n+1,cmp);
	for(int i=1;i<=n&&sum1<=x;i++) sum1+=sw[i],mn1++;
	for(int i=1;i<=n&&sum2<=y;i++) sum2+=sal[i],mn2++;
	cout<<min(mn1,mn2)<<endl;
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## [ABC364C] Minimum Glutton

贪心，每次选某个味道最大的若干个吃，直到这个味道超过要求。

按某个味道排序，模拟即可。

题目要求严格大于，细节要注意一下。

代码：

```cpp
vector<Node> s(read());
x = read(), y = read();
for (auto &i : s) i.a = read();
for (auto &i : s) i.b = read();
sort(s.begin(), s.end(), [](Node x, Node y) { return x.a > y.a; });
for (Node i : s) {
  c1++, a1 += i.a;
  if (a1 > x) break;
}
sort(s.begin(), s.end(), [](Node x, Node y) { return x.b > y.b; });
for (Node i : s) {
  c2++, a2 += i.b;
  if (a2 > y) break;
}
printf("%lld", min(c1, c2));
```

---

## 作者：xuduang (赞：0)

### 题意

给出 $n$ 个物品，每个物品有 $a_i$ 和 $b_i$ 两个值，你需要找到一个**最小**的 $k$，使得 $\displaystyle\sum_{i=1}^{k}a_i>A$ 或者 $\displaystyle\sum_{i=1}^{k}b_i>B$。

### 分析

要使得 $a_i$ 或者 $b_i$ 超出限制，我们可以考虑贪心的取。

1. 我们想要使得 $\displaystyle\sum_{i=1}^{k}a_i>A$，那我们可以把物品按照 $a_i$ 降序排序，这样取出的物品的 $a_i$ 就会尽可能的大，能够更快的超出限制。

2. 我们想要使得 $\displaystyle\sum_{i=1}^{k}b_i>B$，那我们可以把物品按照 $b_i$ 降序排序，这样取出的物品的 $b_i$ 就会尽可能的大，能够更快的超出限制。

统计答案时，在两种方案中取小的。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10;
inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = (s << 3) + (s << 1) + (ch ^ 48);
        ch = getchar();
    }
    return s * w;
}
int n, x, y;
int a[N], b[N];
struct node
{
    int a, b;
}p[N];//拿结构体存利于排序
bool cmp1(node a, node b)
{
    if(a.a == b.a) return a.b > b.b;
    return a.a > b.a;
}
bool cmp2(node a, node b)
{
    if(a.b == b.b) return a.a > b.a;
    return a.b > b.b;
}
signed main()
{
    cin >> n >> x >> y;
    for(int i = 1; i <= n; i++) p[i].a = read();
    for(int i = 1; i <= n; i++) p[i].b = read();
    sort(p + 1, p + n + 1, cmp1);//按a排
    int mi = n;
    int nx = 0, ny = 0;
    for(int i = 1; i <= n; i++)
    {
        nx += p[i].a, ny += p[i].b;
        if(nx > x || ny > y)//超出限制了
        {
            mi = min(mi, i);
            break;
        }
    }
    sort(p + 1, p + n + 1, cmp2);//按b排
    nx = 0, ny = 0;
    for(int i = 1; i <= n; i++)
    {
        nx += p[i].a, ny += p[i].b;
        if(nx > x || ny > y)
        {
            mi = min(mi, i);//取最小的
            break;
        }
    }
    cout << mi << endl;
    return 0;
}

```

---

## 作者：lcy0506 (赞：0)

# AT_abc364_c Minimum Glutton

这道题希望让我们求出吃的菜的数量的最小值，即我们应该让他所吃的菜的咸度或甜度之和最大。因此，我们将菜分别按甜度和咸度排序，计算最多可以吃的最少数量，再取最小值，就是答案。

## 代码如下（附注释）
```
#include <bits/stdc++.h>
using namespace std;
struct node
{
	long long x,y;//x是甜度,y是咸度
}q[1000001];
long long cmp(node a,node b)
{
	return a.x>b.x;
}//按甜度排序
long long cmp1(node a,node b)
{
	return a.y>b.y;
}//按咸度排序
int main()
{
	long long n,m,p,ans=0;//记得开long long
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++)
	cin>>q[i].x;
	for(int i=1;i<=n;i++)
	cin>>q[i].y;
	sort(q+1,q+n+1,cmp);//按甜度排序
	long long sum=0,sum1=0;
	for(long long i=1;i<=n;i++)
	{
		sum+=q[i].x;
		sum1+=q[i].y;
		if(sum>m||sum1>p||i==n)
		{
			ans=i;
			break;
		}//当其中有一个超出条件限制,就退出
	}
	sort(q+1,q+n+1,cmp1);//按咸度排序
	sum=0,sum1=0;
	for(long long i=1;i<=n;i++)
	{
		sum+=q[i].x;
		sum1+=q[i].y;
		if(sum>m||sum1>p||i==n)
		{
			ans=min(ans,i);//对ans进行取min操作
			break;
		}//当其中有一个超出条件限制,就退出
	}
	cout<<ans;
}
```

---

## 作者：_Hzx_ (赞：0)

【**题目大意**】

有 $n$ 道菜，第 $i$ 道菜甜度为 $a_i$，咸度为 $b_i$，吃的菜的甜度总合超过 $x$，就不会再吃了，咸度总合超过 $y$，也不会再吃了，求最后能吃的菜的最少个数。

---

【**解法**】

不难想到了贪心，到貌似不是很好贪，因为要全面考虑到甜度和咸度。

但是仔细想想，因为为了使吃的菜最少，我们肯定是优先吃当前咸度和甜度最多的菜，因为有两个参数，所以直接排序来贪肯定不行。

然后就不难想到，咸度和甜度其实是独立的，我们把甜度和咸度分开来考虑。

可以这么理解，在考虑甜度的过程中，我们吃当前最甜的食物，如果在途中就恰好把咸度吃满了，那很好，更优。

也就是说，分别把甜度和咸度能吃的最大数量取个 $\min$，就是最后的答案。

这里要尤其注意，是吃的超过了之后才不吃了，也就是说无论如何，最后的甜度总合是要大于 $x$ 或者咸度总合大于 $y$。

---

【**代码**】 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, a[N], b[N];
ll x, y;

bool cmp(const int &u, const int &v) {
	return u > v;
}

int main(){
	scanf("%d%lld%lld", &n, &x, &y);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &b[i]);
	sort(a + 1, a + n + 1, cmp);
	sort(b + 1, b + n + 1, cmp);
	ll resa = 0, resb = 0, suma = 0, sumb = 0;
	for (int i = 1; i <= n; i++) 
		if (suma + a[i] > x) {
			resa++;
			break;
		} else {
			resa++;
			suma += a[i];
		}
	for (int i = 1; i <= n; i++) 
		if (sumb + b[i] > y) {
			resb++;
			break;
		} else {
			resb++;
			sumb += b[i];
		}
	printf("%lld\n", min(resa, resb));
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路
对于不再吃的情况，有两种，一种是过甜，一种是过咸。

两种计算最小值的方法一致，都可以按照从大到小的顺序排列，然后从第一道菜开始加，直到总甜度值或咸度值大于上限，然后保存循环次数。

这个过程是可逆的，所以我们也可以用上限依次减去，直到上限小于 $0$。

这两次计算可以合并到一个循环中，只要有任何一个上限被减成负数，就输出当前的循环次数就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, x, y, a[200005], b[200005];
bool cmp(int x, int y) {
	return x > y;
}
signed main() {
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	sort(a + 1, a + n + 1, cmp);
	sort(b + 1, b + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		x -= a[i];
		y -= b[i];
		if (x < 0 || y < 0) {
			cout << i;
			return 0;
		}
	}
	cout << n;
	return 0;
}
```

---

## 作者：xzz_0611 (赞：0)

小蒟蒻又来水 tj 啦！

[洛谷传送门](/problem/AT_abc364_c)  
[AtCoder 传送门](https://atcoder.jp/contests/abc364/tasks/abc364_c)

本题思路简单，建议评橙。
### Step 1：题目大意
有 $N$ 道菜，第 $i$ 道菜的甜度与咸度分别为 $A_i$ 和 $B_i$。

高桥吃的菜的甜度总和最高为 $X$，咸度总和最高为 $Y$，并且，只要他还能吃他就会继续吃下去。

问：高桥最少能吃几道菜。
### Step 2：思路分析
显然，要吃的最少，就要吃的食物的咸度或甜度尽可能高。

所以就可以将咸度和甜度分别从大到小排序，分别计算最少吃多少个菜才能使甜度或咸度超标，再输出小的值减 $1$ 即可（减 $1$ 是因为实际上甜度和咸度不能超过 $X$ 或 $Y$）。
### Step 3：Code
~~你们最爱的来了。~~

[洛谷 AC 记录](/record/list?pid=AT_abc364_c&user=1005749&status=12&page=1)（由于开了完隐只能用这种方法展示）  
[AtCoder AC 记录](https://atcoder.jp/contests/abc364/submissions/56174168)
```cpp
#include <iostream>
#include <algorithm>
#define int long long//不开 long long 见祖宗
using namespace std;
bool cmp(int x, int y) {//从大到小排序
	return x > y;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n, a[200000], b[200000], x, y;
	cin >> n >> x >> y;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	sort(a, a + n, cmp);//排序
	sort(b, b + n, cmp);//排序
	int ans1 = 0, ans2 = 0;
	for (int cnt = 0; cnt <= x && ans1 < n; cnt += a[ans1], ++ans1);//计算最多能吃几个
	for (int cnt = 0; cnt <= y && ans2 < n; cnt += b[ans2], ++ans2);//计算最多能吃几个
	cout << min(ans1, ans2);//输出小的值
	return 0;//完结撒花，qwq
}
```

---

## 作者：Down_syndrome (赞：0)

## 题意

共有 $n$ 碟料理，每碟料理有一个甜度 $a$ 和咸度 $b$。高桥想要吃尽量少的料理。当他吃的料理甜度累计达到 $x$ 或咸度达到 $y$ 他就会觉得恶心，就会停止吃料理。现在请你安排他吃料理的顺序，使得他能吃尽量多的料理，并输出他最多能吃的料理的数量。

## 思路

容易发现甜度和咸度互不影响，因此可以分别考虑甜度大于 $x$ 而停下与咸度大于 $y$ 而停下的不同情况。对于甜度，按甜度从大到小吃即可；对于咸度，按咸度从大到小吃即可。最后取两个答案中的较小值。

[code](https://atcoder.jp/contests/abc364/submissions/56012546)

---

## 作者：Fantasy_Segment_Tree (赞：0)

给定 $n$ 道甜菜和 $n$ 道咸菜，每道菜有甜度或咸度，当甜度大于 $X$ 或咸度大于 $Y$ 时就会停止吃菜。问最少能吃下多少个菜。

既然要问最少，就要从甜度、咸度最大的开始吃，并且只吃甜、咸中的一种。所以把甜咸度从大到小排序，然后取甜菜、咸菜中吃得更少的一种即可。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

long long a[200005], b[200005], n, x, y, minx, miny;

bool cmp(long long x, long long y) {
  return x > y;
}

int main() {
   cin >> n >> x >> y;
   for(int i = 1; i <= n; i++) cin >> a[i];
   for(int j = 1; j <= n; j++) cin >> b[j];
   minx = n, miny = n;
   sort(a + 1, a + n + 1, cmp);
   sort(b + 1, b + n + 1, cmp);
   long long sum1 = 0, sum2 = 0;
   for(int i = 1; i <= n; i++){
     sum1 += a[i];
     sum2 += b[i];
     int flag = 0;
     if(sum1 > x || sum2 > y) flag = 1, cout << i;
     if(flag) return 0;
   }
   cout << n;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
题目中说要使吃的菜最少，所以我们贪心地做。

首先，我们先将每道菜以 $A_i$ 为关键字进行排序，$A_i$ 越大那么排序后的位置越前（因为要使吃的菜最少）。遍历每一道菜，每次累加当前吃的菜的 $A_i$ 和 $B_i$，并且答案 $+1$，如果此时吃完的菜的 $A_i$ 总和大于 $X$ 或者此时吃完的菜的 $B_i$ 总和大于 $Y$，那么立刻结束。

然后，我们再将每道菜以 $B_i$ 为关键字进行排序，$B_i$ 越大那么排序后的位置越前。遍历每一道菜，每次累加当前吃的菜的 $A_i$ 和 $B_i$，并且答案 $+1$，如果此时吃完的菜的 $A_i$ 总和大于 $X$ 或者此时吃完的菜的 $B_i$ 总和大于 $Y$，那么立刻结束。

最后将两次排序后得到的答案取最小值输出即可。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#define int long long 
#define N 200005
struct Node{int a,b;}p[N];
bool cmp1(Node a,Node b){return a.a>b.a;}
bool cmp2(Node a,Node b){return a.b>b.b;}
int n,x,y;
signed main(){
	std::cin>>n>>x>>y;
	for(int i=1;i<=n;i++)std::cin>>p[i].a;
	for(int i=1;i<=n;i++)std::cin>>p[i].b;
	std::sort(p+1,p+1+n,cmp1);
	int sum1=0,sum2=0,ans1=0;
	for(int i=1;i<=n;i++){
		sum1+=p[i].a,sum2+=p[i].b,ans1++;
		if(sum1>x||sum2>y)break;
	}
	std::sort(p+1,p+1+n,cmp2);
	int sum3=0,sum4=0,ans2=0;
	for(int i=1;i<=n;i++){
		sum3+=p[i].b,sum4+=p[i].a,ans2++;
		if(sum3>y||sum4>x)break;
	}
	std::cout<<std::min(ans1,ans2);
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

题意：有一些盘子，每个盘子有两个属性值 $a_i$ 和 $b_i$，你需要把盘子排成一定的顺序。现在从左往右一个一个拿，如果拿到的 $a_i$ 总和 $>x$，则停止继续拿；如果拿到的 $b_i$ 总和 $>y$，则停止继续拿。求最少能拿多少个。

很简单。贪心。我们只需要把两种属性分别从大到小排序就好了，这样每一种盘子都能取到最小值。得到两个最小值之后直接求 min 即可。因为取到最小值的是先被取完了，就不用考虑另一个属性怎样了。

---

## 作者：201012280925LSY (赞：0)

## 题意
有 $N$ 道菜，每道菜有不同的甜度和咸度，如果前几道菜的甜度之和超过了高桥的甜度忍耐值 $X$，或者咸度之和超过了咸度忍耐值 $Y$，那么高桥就会停止吃菜。把菜按照某种顺序排列，问高桥最少要吃几道菜。
## 思路
显然，如果想让高桥吃菜吃的尽量少，那么前几道的甜度之和或者是咸度之和就得尽量大。

所以，我们可以把菜按照甜度从高到低排列，然后统计他能吃几道菜，再把菜按照咸度从高到低排列，统计能吃几道菜，最后输出两个答案较小的那个。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,answer,sum;
struct dish
{
	long long salt,sweet;
}a[200010];
bool cmpsalt(dish a,dish b)//把咸度从高到低排列
{
	return a.salt>b.salt;
}
bool cmpsweet(dish a,dish b)//把甜度从高到低排列
{
	return a.sweet>b.sweet;
}
int main()
{
	scanf("%lld%lld%lld",&n,&x,&y);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i].salt);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i].sweet);
	}
	sort(a+1,a+n+1,cmpsalt);
	answer=n;
	for(int i=1;i<=n;i++)
	{
		sum+=a[i].salt;
		if(sum>x)
		{
			answer=min(int(answer),i);//记录答案
			sum=0;
			break;
		}
	}
	sum=0;
	sort(a+1,a+n+1,cmpsweet);
	for(long long i=1;i<=n;i++)
	{
		sum+=a[i].sweet;
		if(sum>y)
		{
			answer=min(answer,i);//两个答案比较
			break;
		}
	}
	printf("%lld",answer);//输出
	return 0;
}
```

---

## 作者：lcfollower (赞：0)

明显，我们可以按照甜度和咸度两种量从大到小排序。

首先按甜度排序，求出答案；再按照咸度排序，求出答案。两种答案比较最小值就是最终的答案啦。

正确性显然，但是当求最多吃的菜品数量时就不正确了，因为我们可以选择甜度高一点的来保证咸度不过大。

时间复杂度为 $\mathcal O(n\log n)$，瓶颈在于排序。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define up(i,x,y) for(register int i=x;i<=y;++i)
#define dn(i,x,y) for(register int i=x;i>=y;--i)

using namespace std;

inline int read(){int x=0;bool f=0;char ch=getchar();while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return (f?-x:x);}
inline void write(int x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10|48);}
inline void writeln(int x){write(x),putchar('\n');}
int n ,x ,y ,sweet ,salty ,ans;
struct node{
  int s ,sa;
}a[200005];
inline void solve(){
  n = read() ,x = read() ,y = read();
  up(i,1,n) a[i].s = read();
  up(i,1,n) a[i].sa = read();
/* 先按照甜度排序作贪心。 */
  sort(a + 1, a + 1 + n ,[](node &s1 ,node &s2){return (s1.s == s2.s) ? (s1.sa > s2.sa) : (s1.s > s2.s);});
  ans = n;
  up(i,1,n){
   sweet += a[i].s;
   salty += a[i].sa;
   if(sweet > x || salty > y) {ans = i;break;}
  }
/* 再按照咸度排序贪心。 */
  sort(a + 1 ,a + 1 + n ,[](node &s1 ,node &s2){return (s1.sa == s2.sa) ? (s1.s > s2.s) : (s1.sa > s2.sa);});
  sweet = salty = 0;
  up(i,1,n){
   sweet += a[i].s;
   salty += a[i].sa;
   if(sweet > x || salty > y) {ans = min(ans ,i);break;}
  }
  writeln(ans);
  return;
} signed main(){
  int Tcases = 1;
  while(Tcases --) solve();
  return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[[ABC364C] Minimum Glutton](https://atcoder.jp/contests/abc364/tasks/abc364_c)

想吃掉尽量少的菜，就应该让 $a_i$ 之和尽量快速达到 $X$，让 $b_i$ 之和尽量快速达到 $Y$。

考虑将 $a_i$ 从大到小排序，按照从前往后的顺序吃，累加当前的 $a_i$，如果当前 $a_i$ 之和大于 $x$，便记录 $i$ 并跳出循环。可以证明这种吃法一定是不劣的。$b_i$ 是同理的。答案为两次记录的 $i$ 的较大值。

时间复杂度 $O(n\log n)$，瓶颈在于排序。

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc364_c)

## 思路

贪心。

读入数据后先按照**甜度**从大到小排序。之后累加甜度、咸度。如果到某一位置甜度**或**咸度超标了，那么记录答案为这道菜的下标。

之后再按照**咸度**从大到小排序。后面的内容和上一段相同。

在第二遍计算结果之前记得要将记录当前吃饭甜咸度的变量**清空**。

- $1\le X,Y\le 2\times 10^{14}$，记得开 `long long`。

## 代码

我这里用了 `pair` 类型来记录甜咸度，方便排序。但是 `pair` 排序是按照 `first` 第一优先级，`second` 第二优先级来排序的。所以在进行第二次排序之前要**交换 `first` 与 `second`**，并记得**交换甜咸度上限**。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll,ll>
#define fi first
#define se second
using namespace std;
ll read(){
	ll x=0;bool f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(f)return x;return ~x+1;
}
const int N=2e5+10;
ll n,x,y,ans=1e9;//结果变量赋极大值。
pll a[N],now;
signed main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;++i)a[i].fi=read();
	for(int i=1;i<=n;++i)a[i].se=read();
	sort(a+1,a+1+n,greater<pll>());
	for(int i=1;i<=n;++i){
		now.fi+=a[i].fi;
		now.se+=a[i].se;
		if(now.fi>x||now.se>y){
			ans=i;
			break;//之后不能再吃，跳出循环。
		}
	}
	for(int i=1;i<=n;++i)swap(a[i].fi,a[i].se);
	sort(a+1,a+1+n,greater<pll>());
	now={0,0};
	for(int i=1;i<=n;++i){
		now.fi+=a[i].fi;
		now.se+=a[i].se;
		if(now.fi>y||now.se>x){
			ans=min((int)ans,i);//与之前记录的进行大小比较。
			break;
		}
	}
	cout<<min(n,ans);//如果都吃了那么此程序不会记录任何值，应当输出 n。
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc364/submissions/56099352)

---

## 作者：linch (赞：0)

个人认为橙吧，一个比较好想的贪心。

## 题意
有 $N$ 盘菜，每盘菜有一个甜度 $A_i$ 和咸度 $B_i$。可以将这些菜按任意的顺序给高桥吃，当累计的甜度大于 $X$ 或 咸度大于 $Y$ 时，就会停止。求他最少吃几盘菜？

## 核心思路
考虑贪心。

容易发现，当 $X,Y$ 不变，菜的咸度或甜度越大时，吃的菜的数量就越少。那么就可以先吃咸度或甜度较大的菜，这样能让甜度尽快超过 $X$ 或让咸度尽快超过 $Y$，最终吃的数量就最少。

## 实现
先将两个代表甜度和咸度的数组排序，然后**分别**遍历数组，一旦超过对应的最大值，立即停止，记录此时答案。两个答案中的较小者即为最终答案。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
long long n,a[maxn],b[maxn];
long long sum,x,y,ans;//开 longlong，不开 WA 17 个点。
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}//输入。
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);//分别排序。
	
	//接下来考虑甜度。
	ans=n;//不要忘记提前赋值，如果都不超过 X。
	for(int i=n;i>=1;i--){//遍历。注意 sort 默认升序，此题需要降序。
		sum+=a[i];//加上甜度。
		if(sum>x){//如果超出。
			ans=n-i+1;//记录答案。
			break;
		}
	}
	
	//接下来考虑咸度，方法同上。
	sum=0;
	for(int i=n;i>=1;i--){
		sum+=b[i];
		if(sum>y){
			ans=min(ans,n-i+1);//取较小值。
			break;
		}
	}
	cout<<ans;//输出。
	return 0;
}
```

[赛时 AC 记录](https://atcoder.jp/contests/abc364/submissions/56033450)

---

## 作者：__O_v_O__ (赞：0)

题目要求吃的菜最少，容易想到先吃甜度或咸度大的。

继续考虑，我们发现，对于甜度或咸度，我们很容易就能算出它超限所需的最少菜数（排序后循环枚举）。

显然，甜度和咸度中只要其中有一个超限就会停止进食，所以它们互不相关，则最后答案为甜度和咸度超限次数中的最小值。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,x,y,a[1000001],b[1000001];
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	sort(a+1,a+n+1,[=](int x,int y){return x>y;});//排序
	sort(b+1,b+n+1,[=](int x,int y){return x>y;});
	int an1=0,an2=0,su1=0,su2=0;
	for(int i=1;i<=n;i++){//甜度
		su1+=a[i];//累计当前甜度
		if(su1>x){//如果超限
			an1=i;//记录超限最小菜数
			break;
		}
	}
	if(!an1)an1=n;//如果最后都没超限，则最多菜数为n
	for(int i=1;i<=n;i++){//咸度（同理）
		su2+=b[i];
		if(su2>y){
			an2=i;
			break;
		}
	}
	if(!an2)an2=n;
	cout<<min(an1,an2);//求最小值
	return 0;
}
```

---

## 作者：__Q_w_Q__ (赞：0)

### 题面大意

有 $N$ 盘食物，第 $i$ 盘食物包含 $A_i$ 的甜度与 $B_i$ 的咸度，求最少吃几盘食物才能使甜度的总和超过 $X$ **或**咸度的总和超过 $Y$。

## 思路

![pkqz9UK.md.png](https://s21.ax1x.com/2024/07/29/pkqzC4O.png)

先看数据范围，注意到 $N$ 的大小是 $2\times 10 ^5$ 也就是说，基本只能使用时间复杂度为 $O(N\times\log{N})$ 或 $O(N)$ 的算法。考虑贪心。



注意本题的边界条件是**或**，也就说，可以进行分类讨论。



首先，贪心计算出甜度总和超过 $X$ 所需的食物盘数。然后使用同样的方法计算出咸度总和超过 $Y$ 所需的食物盘数，最后进行比较，输出较小的值。



至于计算甜/咸度总和超过 $X$ / $Y$ 的过程也不难理解，两个排序就行。这样最后的时间复杂度刚好是 $O(N\times\log{N})$ 级别的，不至于 TLE 。但是需要注意一下，本题无法使用冒泡排序等其他最坏时间复杂度为 $O(N^2)$ 的排序算法。而 GCC 的 Sort 函数加入了随机化，最坏时间复杂度不至于掉到 $O(N^2)$ 因此在本题不会超时。



### Code

最后，放上代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200010],b[200010];
bool cmp(int x,int y){
    return x>y;
}
signed main(){
    int n,x,y;
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+n+1,cmp);
    int cnt=0,sum=0,res=n;
    for(int i=1;i<=n;i++){
        cnt+=a[i];
        sum=i;
        if(cnt>x){
            break;
        }
    }
    cnt=0;
    res=min(res,sum);
    for(int i=1;i<=n;i++){
        cnt+=b[i];
        sum=i;
        if(cnt>y){
            break;
        }
    }
    res=min(res,sum);
    cout<<res;
    return 0;
}
```

最后解释一下这句 ``#define int long long`` 这句其实就是把代码中所有 ``int`` 转换成 ``long long``

但是 ``main()`` 函数的返回值又必须是 ``int`` 类型，所以就只能写 ``signed main()``。

---

## 作者：donnieguo (赞：0)

## 题意简述

有 $N$ 个盘子，第 $i$ 道菜有甜度 $A_i$ 和咸度 $B_i$，你可以以任意顺序吃这些菜，当你吃的菜的总甜度大于 $X$ 或总咸度大于 $Y$ 时你就会停下。

求你**最少**能吃几道菜。

## 思路

考虑贪心。

显然从大到小排序更优。

将所有的盘子进行两次排序，第一次按照甜度从大到小进行排序，第二次按照咸度从大到小进行排序，统计两次吃的菜的数量，取最小值就是答案。

记得开 `long long`。

## AC code
```cpp
#include <iostream>
#include <algorithm>
#define N 200010
#define int long long
using namespace std;

int n, x, y;
int ans1 = -1, ans2 = -1;
struct dishes{
	int a, b;
}d[N];

bool cmp1(dishes d1, dishes d2) {return d1.a > d2.a;}
bool cmp2(dishes d1, dishes d2) {return d1.b > d2.b;}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) cin >> d[i].a;
	for (int i = 1; i <= n; i++) cin >> d[i].b;
	sort(d + 1, d + n + 1, cmp1);
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (sum + d[i].a > x) {ans1 = i; break;}
		sum += d[i].a;
	}
	sort(d + 1, d + n + 1, cmp2);
	sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (sum + d[i].b > y) {ans2 = i; break;}
		sum += d[i].b;	
	}
	if (ans1 == -1 && ans2 == -1) {cout << n << '\n'; return 0;}
	if (ans1 == -1 && ans2 != -1) {cout << ans2 << '\n'; return 0;}
	if (ans1 != -1 && ans2 == -1) {cout << ans1 << '\n'; return 0;}
	cout << min(ans1, ans2) << '\n';
	return 0;
}
```

---

## 作者：Guoguo2013 (赞：0)

这次 Atcoder 不知道为啥那么饿，A，C，E 三道题都是关于吃的。

### 题意简介：
有 $N$ 道菜，第 $i(1 \leq i \leq N)$ 道菜，分别有着 $A_i$ 的甜度和 $B_i$ 的咸度。

Atcoder 吃的菜的甜度总和不能超过 $X$，不然他就会觉得太齁，咸度也不能超过 $Y$，要不然他就会觉得太咸，一旦超过了，他就不能再吃其他菜了，**不然他就会一直吃**。

Atcoder 要减肥，所以他只能尽量少吃菜，所以问题问他**最少**能吃多少菜。

### 思路：
其实思路挺简单的，我们直接把甜度和咸度分开来看，看他如果从最甜的一直吃，最多能吃多少，再看从最咸的开始吃，看最多能吃多少，取个 $\min$ 就可以。

毕竟每一道菜按甜度从大往小吃，肯定比按其他方案吃要吃的少一点或相等的，咸度也一样，最后按吃的菜的数量小的吃法吃就行呗。

剩下有些细节见代码。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair< int, int >
#define MII map< int, int >
#define MIB map< int, bool >

using namespace std;

const int N = 2e5 + 5, mod = 998244353;
int n, x, y, a[N], b[N], daan = INT_MAX; // 答案要设为一个极大值（拼音党万岁）

template<typename T>inline void read(T &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
int ksm(int a, int b, int p){
    int ans = 1;
    while(b){
        if(b & 1)ans =(ans*a)%p;
        b >>= 1;
        a = (a*a) % p;
    }
    return ans;
}
signed main(){
//	freopen("a.in", "r", stdin);
//	freopen("a.out","w",stdout);
	scanf("%lld %lld %lld", &n, &x, &y);
	daan = n;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	sort(b + 1, b + n + 1); // 由于甜度和咸度没有什么关联，分别排序就行了。
	for (int i = n; i >= 1; i--){ // 从小到大反着遍历就变成从大到小了，懒得写 cmp。
		a[i] += a[i+1]; // 后缀和都知道吧。
		if (a[i] > x){
			daan = min(daan, n - i + 1); // 由于是吃的甜度超了之后才不吃的，所以这一道菜实际上他也吃了（重点！！！）。
			break;
		}
	}
	for (int i = n; i >= 1; i--){
		b[i] += b[i+1];
		if (b[i] > y){
			daan = min(daan, n - i + 1); // 毕竟要选吃菜数量的少的。
			break;
		}
	}
	printf("%lld", daan);
	return 0;
}

```

---

## 作者：Cosine_Func (赞：0)

题意：对于两个数组 $A$ 和 $B$，对两个数组进行重排使得存在一个数字 $K$ 满足  $\sum_{i-1}^{K}A_i>X$ 或 $\sum_{i-1}^{K}B_i>Y$ 且 $K$ 尽可能小。如果数列的和小于 $X$ 或 $Y$，输出 $N$。

由于所有数字都是正数，所以在 $K$ 相同的条件下前 $K$ 大的数的和**大于等于**任意 $K$ 个数列中元素的和。可以使用贪心实现这一算法。先对数组**降序**排序，然后从小到大遍历 $K$ 直到前 $K$ 个数的和**严格大于** $X$ 或 $Y$，最后取两个数列计算结果的最小值并输出。

注意一下：$X$ 和 $Y$ 的范围较大，要开 `long long`。

[代码链接](https://atcoder.jp/contests/abc364/submissions/56020882)

---

## 作者：shitingjia (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc364_c)

### 题目思路

一道普通的贪心题。

为了使答案（食物数量）最小，要尽可能让甜度大于 $X$ **或者**咸度大于 $Y$，满足其一即可。

可以用 od1 和 od2 两个数组，od1 以甜度为关键字，od2 以咸度为关键字，从大到小排序。

从头开始，od1 累加甜度，直到累加值大于 $X$；od2 和 od1 类似。两种都记录下能吃几个菜，最后输出两种方案之中更小的一种。

记得开 long long 啊！

### AC Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=2e5+5;
int n;
LL x,y;
struct node{
	LL sweet,salt;
}od1[N],od2[N];
bool cmp1(node s1,node s2){
	return s1.sweet>s2.sweet; 
}
bool cmp2(node s1,node s2){
	return s1.salt>s2.salt;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>od1[i].sweet;
		od2[i].sweet=od1[i].sweet;
	}
	for(int i=1;i<=n;i++){
		cin>>od1[i].salt;
		od2[i].salt=od1[i].salt;
	}
	sort(od1+1,od1+n+1,cmp1);
	sort(od2+1,od2+n+1,cmp2);
	LL sum1=0,sum2=0,ans=n;
	for(LL i=1;i<=n;i++){
		sum1+=od1[i].sweet;
		if(sum1>x){
			ans=min(ans,i);
			break;
		}
	}
	for(LL i=1;i<=n;i++){
		sum2+=od2[i].salt;
		if(sum2>y){
			ans=min(ans,i);
			break;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc364_c [ABC364C] Minimum Glutton
---
### 题目大意
给定 $N$ 盘菜，甜度和咸度分别为 $A_i$ 和 $B_i$。甜度和大于 $X$ 或咸度和大于 $Y$ 时停止吃。要找到一种选取方案，使得停下时吃的最少。

---
### 题解
停下的条件有三种：甜度和大于 $X$，咸度和大于 $Y$，全部吃完。由于甜、咸度本身是无关的，所以可以分开讨论。前两种可以各自排序后从大往小加，满足停止条件时更新答案。最后一种条件就是前两种都不满足，所以直接在最后特判即可。

### 代码
**注意开 `long long`!**
```cpp

#include <algorithm>
#include <cstdio>
#define int long long
using namespace std;

int a[200010], b[200010];
int ans = 0x3f3f3f3f3f3f3f3f;//答案 
int sumx, sumy;//甜、咸度和 
int n, x, y;

signed main() {
	scanf("%lld%lld%lld", &n, &x, &y);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &b[i]);
	}
	
	sort(a + 1, a + 1 + n);//分开排序 
	sort(b + 1, b + 1 + n);
	
	for (int i = n; i >= 1; --i) {
		sumx += a[i];//累加甜、咸度和 
		sumy += b[i];
		if (sumx > x) {//甜度满足条件 
			ans = min(n - i + 1, ans);//更新答案，注意 i 从 n 开始 
		}
		if (sumy > y) {//咸度满足条件 
			ans = min(n - i + 1, ans);//同样的 
		}
	}
	printf("%lld", min(ans, n));//若 ans 还等于初值，说明吃完了，输出 n 
	return 0;
}

```

---

