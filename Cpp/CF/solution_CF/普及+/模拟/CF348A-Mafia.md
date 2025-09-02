# Mafia

## 题目描述

One day $ n $ friends gathered together to play "Mafia". During each round of the game some player must be the supervisor and other $ n-1 $ people take part in the game. For each person we know in how many rounds he wants to be a player, not the supervisor: the $ i $ -th person wants to play $ a_{i} $ rounds. What is the minimum number of rounds of the "Mafia" game they need to play to let each person play at least as many rounds as they want?

## 说明/提示

You don't need to know the rules of "Mafia" to solve this problem. If you're curious, it's a game Russia got from the Soviet times: http://en.wikipedia.org/wiki/Mafia\_(party\_game).

## 样例 #1

### 输入

```
3
3 2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
2 2 2 2
```

### 输出

```
3
```

# 题解

## 作者：LRL65 (赞：12)

这题其实不需要二分，直接o(n)。

思路：

首先题目说：

其中第 $i$ 个人表示想玩 $ a_i$ 局游戏且不当主持，让求出满足每人要求的最少的局数。

也就是说：

第 $i$ 个人表示想玩 $ a_i$ 局游戏且当选手。

那么现在把他们加起来也就是有$\sum\limits_{i=1}^na_i$个选手。那现在直接除以 $n-1$ ，然后有余数的就加1，就可以得出答案了吗？答案是错。大部分情况按照这种方法算都是对的，不过有一些情况是错的，如下面这个例子：

3

1 1 5

按照这个方法，我们应算出$\dfrac{1+1+5}{n-1}=\dfrac{7}{2}=3.5$。那答案应为4。可是第三个人要玩5局，大于4了，所以不对。那么我们还要找出最大值，跟答案比较，如果大于答案，就输出最大值。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,s=0,maxn=0;//记得开long long
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a;//输入
        s+=a;//累加
        maxn=max(maxn,a);//找最大
    }
    n=n-1;
    if(s%n==0)s/=n;else s=s/n+1;
    if(s<maxn)s=maxn;
    cout<<s<<endl;//输出
}
```


---

## 作者：Starlight237 (赞：7)

# 核心算法：二分答案
这里我们要明白一个事实：既然地$i$个人只想玩$a_i$次，设有$x$次游戏能满足要求，则显然，每次游戏有$n-1$个人能玩到游戏，设$s$表示所有人一共要玩的游戏，即$s=\sum\limits^n_{i=1}a_i$，显然必有$x(n-1)>=s$。因此我们可以对这个条件进行二分答案。

下面确定$x$的取值范围。因为要保证所有人满足，显然要玩次数最多的那个人需要满足，即$x>=\max{a_i}$。又因为即使每次只给一个人玩，最多也只需要$s$次，所以$x\in[\max{a_i},\operatorname{sum}{a_i}]$。

由此得到如下代码：
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
static int a[100000],n;
static long long ma,si;
int main(){
    scanf("%d",&n);
    for(reg int i=0;i<n;++i)
        scanf("%d",a+i),ma=max(int(ma),a[i]),si+=a[i];
    long long ans=0,mid,l=ma,r=si;
    while(l<=r){
        mid=l+r>>1;
        if(mid*(n-1)>=si)ans=mid,r=mid-1;
        else l=mid+1;
    }printf("%d",ans);
    return 0;
}
```

---

## 作者：J_Kobe (赞：4)

[题面传送门](https://www.luogu.com.cn/problem/CF348A)

### 题意：
有 $ n $ 个人，每局游戏有一个主持人，有 $ n - 1 $ 名选手，第 $ i $ 个人相当于第 $ i $ 局的选手，也就是不当主持人，让求出满足每人要求的最少的局数。

### 思路：
首先我们可以直接把每一个 $ a $ 给累加起来，然后直接除以 $ n - 1 $，然后如果无法整除的话就加 $ 1 $。

**注意**我们需要找出所有 $ a $ 中的最大值，最后与答案比较，如果最大值大于答案的话，则需要输出最大值。

那么这道题就做完了，接下来奉上代码。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n, a, ans = 0, mx = 0;

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        ans += a;
        mx = max(mx,a);
    }
    n--;
    if (ans % n == 0)
    {
        ans /= n;
    }
    else
    {
        ans = ans / n + 1;
    }
    ans = min(ans, mx);
    printf("%lld", ans);
    return 0;
}
```



---

## 作者：alex_liu (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF348A)

## 思路：
首先累计每个人所想玩的局数得出每个人要参与游戏总数 $s$

由于每一局游戏共需要 $n-1$ 人参与，所以需要有 $ \text{ceil}(\frac{s}{n-1}) $ 局游戏

因为游戏总局数不能少于想要参加的人的最多次数 $maxx$，所以用 $\max$ 函数输出最大值即可

注意：

1. 向上取整要强制转换为 与 $\max$ 函数中另一个数相同的类型，因为 $\max$ 函数只能比较两个相同类型的大小（手写也不是不行）

2. 要开 long long

## AC CODE:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){//快读优化 
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,x,maxx=-1,s=0;
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		x=read();
		s+=x;//累计每个人要参与游戏总数 
		maxx=max(x,maxx);//找到游戏中想要玩游戏局数最多的值 
	}
	printf("%lld\n",max(maxx,(int)ceil(1.0*s/(n-1))));//套公式 
	return 0;
}
```


---

## 作者：pandaSTT (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF348A)

[更好的阅读体验？](https://www.luogu.com.cn/blog/cathyqwq/solution-cf348a)


## 前置知识

~~学过小学二年级~~

## 思路

一看是 **CF** 的 **A** 题，应该是思维？

每一轮游戏需要 $ n-1 $ 个人的参与，而我们可以统计出所有人想参与游戏的总数，这样就可以求出至少需要多少轮游戏。

而游戏轮数不能少于所有人中想参与的最多次数，所以与最大值比较大小即可。

## 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long n,ans,x,sum;
  signed main(){
      scanf("%lld",&n);
      for(int i=1;i<=n;i++){
          scanf("%lld",&x);
          sum+=x;
          ans=max(ans,x);
      }
      n--;
      printf("%lld",max((sum+n-1)/n,ans));
      return 0;
  }
```


---

## 作者：ykuouzf (赞：3)

### 这题有o（n）算法！！！

首先我们可以考虑一般情况下的解法，如若是每个人都刚好玩好，那么玩的总数就是$sum=\sum\limits^n_{i=1}a_i$,每一次可以有$(n-1)$个人参与游戏，所以答案显然就是$ceil(sum/(n-1))$。

但还有一种情况：若是局数较少的人都已玩好，但局数最多的人仍未玩好，那么其他人就要陪他玩，答案就会大于$ceil(sum/(n-1))$，所以需要加上一个特判，判断当前面所有人都玩好后，局数最大的人是否已玩好，取其中的最大值。

可以先从小到大排一遍，算出前面除去最大值所有人的总值$sumx=\sum\limits^{n-1}_{i=1}a_i$，由于开头必然从小的值里选，再除去最大值不计在内，每玩一次减少的总数就是$(n-2)$，那么前$(n-1)$个人的局数就是$ceil(sumx/(n-2))$,将这个数与$a[n]$比较，若是小于等于$a[n]$就输出$a[n]$,否则输出前文求得的$ceil(sum/(n-1))$。

代码也很容易实现：

```
#include<bits/stdc++.h>
#define int long long 
#define li inline
#define re register
int n,sum,a[100005];
li int read()
{
	re int j=0,f=1;
	re char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())j=(j<<1)+(j<<3)+(c^48);
	return f*j;
}
li void write(re int x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
signed main()
{
	n=read();
	for(re int i=1;i<=n;i++)a[i]=read();
	std::sort(a+1,a+n+1);
	for(re int i=1;i<n;i++)sum+=a[i];
	if((sum+n-3)/(n-2)<=a[n])write(a[n]);//div运算向上取整的方法：n/m=(n+m-1)/m 
	else write((sum+a[n]+n-2)/(n-1));
	return 0;
}
```

---

## 作者：hard_learn (赞：2)

**由题可知**

共 $n$ 个人，每局都必须有个主持人，有 $n-1$ 名选手。

第 $i$ 个人是第 $i$ 局的选手，当了选手就不会当主持。

要求出满足所有人的最少局数。

最少局数一定 $\ge$ 某人的最大局数。

**思路**

将局数累加到 $ans$ 中，再求出最大的局数。

最后输出 $ans \div (n-1)$ 。

如果求出来的值 $<$ 最大的局数，输出最大的局数。

否则直接输出。

**代码如下**
```
#include<bits/stdc++.h>
using namespace std;
long long n,ans,sum;
long long a[100005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ans+=a[i]; 
		//将所有的想玩的局数加起来（统计） 
	}
	sort(a+1,a+n+1); 
	//这里方法有多种
	/*
		1.直接在循环里求最大值
		代码如下
		{
			int maxx=INT_MIN;
			for(int i=1;i<=n;i++)
			{
				cin>>a;
				if(a>maxx)
					maxx=a; 
				//注意如果用这种方法不用定义数组 
			}
		}
		2.sort 快排
		sort(a+1,a+n+1); 
		//此时要定义数组；
		//a[n]就是最大值 					 
	*/ 
	sum=ceil(ans*1.0/(n-1)); 
	//ceil是向上取整 
	//因为根据公式  总局数*1.0 ÷（n-1） 
	//n-1是因为有一个人必须当主持  *1.0是因为ans不是double 
	cout<<max(sum,a[n])<<endl;
	//如果直接输出sum 你会发现不能AC
	//开动脑筋想一想 如果sum都小于最大的想玩局数 肯定不对
	//所以去sum和最大的想玩局数当中的最大值输出就能AC 
	return 0;
}
```


---

## 作者：foryou_ (赞：2)

由于题目具有十分明显的单调性（若 $x$ 局能满足要求，则 $>x$ 局一定能满足；若 $x$ 局无法满足要求，则 $<x$ 局也无法满足），因此我们考虑进行二分答案。

二分所需要的局数 $x$，设所有人想玩的总局数为 $S$，由题意可得 $S=\sum^{n}_{i=1}a_i$。因为每局都会有 $1$ 人主持，$n-1$ 名选手，所以当局数为 $x$ 时总选手为 $(n-1) \times x$，显然这个值应当 $\ge S$ 才能满足所有人的要求。

因此在二分时，若 $(n-1) \times x \ge S$，则向右区间扩展（因为要求最少局数），否则向左区间扩展即可。需要注意二分左右边界的设定。

```cpp
#include<bits/stdc++.h>
#define int long long //（可能）需要开 long long
using namespace std;

int n,s,m,a[100031];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) //读入并求出 S
    	cin>>a[i],s+=a[i],m=max(m,a[i]); 
    int l=m-1,r=s+1; //注意左右边界设定
    while(l+1<r){
        int mid=(l+r)>>1;
        if(mid*(n-1)>=s) r=mid; //满足条件就向右扩展
        else l=mid; //否则向左扩展
    }
    cout<<r; //注意输出的是 r（因为是最小值）
    return 0;
}
```

---

## 作者：hjqhs (赞：1)

这有绿？  
由题意，第 $i$ 个人想当 $a_i$ 次选手。所有人一共想当 $\sum^{n}_{i=1}a_i$ 次选手，而每轮可以让 $n-1$ 人当选手，所以答案为 $\frac{\sum^{n}_{i=1}a_i}{n-1}$。注意当这个值比不上 $\max(a_i)$ 时答案应替换成 $\max(a_i)$。
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=b;i>=a;--i)
#define pv(i,p) for(int i=0;i<p.size();++i)
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
#define mp make_pair
#define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=100005;
const int MOD=998244353;
const int INF=0x3f3f3f3f3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAX(int a,int b,int c){return Max(a,Max(b,c));}
int Min(int a,int b){return a<b?a:b;}
int MIN(int a,int b,int c){return Min(a,Min(b,c));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int n,Sum,maxSum=-INF;
void solve(){
	n=read();
	rep(i,1,n){int x=read();Sum+=x;maxSum=Max(maxSum,x);}
	if(!(Sum%(n-1)))Sum/=(n-1);
	else Sum/=(n-1),++Sum;
	cout<<Max(Sum,maxSum);
}
signed main(){
	// freopen(,,stdin);
	// freopen(,,stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
	return 0;
}
```

---

## 作者：incra (赞：1)

upd 2023/08/22 句号漏了怎么过审了 qwq，麻烦管理员大大再审核一下。
### 题解
记 $x_i$ 为第 $i$ 个人当主持时玩的局数。

则有 $\displaystyle(\sum_{j=1}^{n}x_j)-x_i\ge a_i$，也就是一个人当主持人时，别的人的答案都会加一。

把上面对于 $1\le i\le n$ 的式子相加，得到 $(n-1)(\displaystyle\sum_{i=1}^nx_i)\ge \displaystyle\sum_{i=1}^na_i$。

两边同时除以 $n-1$ 得到 $\displaystyle\sum_{i=1}^nx_i\ge\left\lceil\frac{\displaystyle\sum_{i=1}^na_i}{n-1}\right\rceil$。

注意到 $ans$ 可能小于 $a_i$，所以答案还要和 $a_i$ 取最大值，即 $ans=\max\left\{\left\lceil\frac{\displaystyle\sum_{i=1}^na_i}{n-1}\right\rceil\displaystyle\max_{i=1}^{n}\{a_i\}\right\}$。
### 代码
```cpp
#include <bits/stdc++.h>
#define rep(i,l,r) for (LL i = (l),SIZE = (r);i <= SIZE;i++)
#define per(i,l,r) for (LL i = (l),SIZE = (r);i >= SIZE;i--)
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair <int,int> PII;
int n;
int main () {
	cin >> n;
	LL sum = 0;
	LL maxx = 0;
	rep (i,1,n) {
		LL x;
		cin >> x;
		maxx = max (maxx,x);
		sum += x;
	}
	cout << max ((sum + n - 2) / (n - 1),maxx) << endl;
	return 0;
}
```

---

## 作者：Shikita (赞：1)

# 题目翻译
啦啦啦

有nn个人在玩一款叫“Mafia”的游戏。每局游戏都要1个人作为裁判，其他n−1个人作为队员。第i个人要玩尽兴至少需要作为队员玩a​i​​ 局游戏（注意不包括作为裁判）。

请计算至少需要进行多少局游戏，使得每个人能都能玩尽兴。

# 刚开始做这道题还以为很简单事实上并非如此

直接上代码
## 代码
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long llx;
inline llx read()
{
    llx x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9'){if(c=='-')flag=1;   c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+c-'0';c=getchar();}
    return flag?-x:x;
}
llx a[1000005]={0};
llx ans=0;
int main()
{
    llx n=read();
    for(int i=1;i<=n;++i)
      a[i]=read();
    sort(a+1,a+1+n);
    if(a[1]==a[2]&&(a[1]+a[2])>a[n])
    ans=a[n];
    else
    ans=max(a[1]+a[2],a[n]);
    cout<<ans<<endl;
}
```
看起来非常对，只要最后两个轮流当裁判，如果中间有人完成了那么就那个人当裁判继续
### 然而事实并非如此
随便出一组数据就可以hack掉这个代码

下面才出示正解
#### 其实这题是暴力二分哒

代码
```
#include<bits/stdc++.h>
#define INF 100000000000
using namespace std;
typedef long long llx;
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9'){if(c=='-')flag=1;   c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+c-'0';c=getchar();}
    return flag?-x:x;
}
int a[100010],n;
int cmp(int a,int b)
{
    return a>b;
}
int main()
{
	n=read();
    for(int i=0; i<n; i++) a[i]=read();
    sort(a,a+n,cmp);  
    llx r=INF,l=0,ans=(l+r)/2;
    while(l<r)
    {
        llx left=ans,i;
        for(i=0;i<n;i++)
        {
            if(a[i]>ans)  
            {
                l=ans+1;
                ans=(r+l)/2;
                break;
            }
            else
            {
                left=left-(ans-a[i]); 
                if(left<=0) 
                {
                    r=ans;
                    ans=(r+l)/2;
                    break;
                }
            }
        }
        if(i==n&&left>0)
        {
            l=ans+1;
            ans=(r+l)/2;
        }
    }
    cout<<ans<<endl;
}
```
这篇题解就简单写到这里，欢迎各位大佬多多指教

---

## 作者：tallnut (赞：0)

为什么大家都用二分做的啊……是不是被 [CF](https://codeforces.com/contest/348/problem/A) 上的标签给误导了？
# 思路
显然，要玩的局数至少要保证大于等于所有人局数的最大值，记为 $a$。此外，我们再求一下要玩的局数之和，再 $\div (n-1)$（类似于求平均数，但是这道题里每局只有 $n - 1$ 个玩家），记为 $b$。最后输出 $\max(a,b)$ 即可。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/138287117)。
```
#include <iostream>
using namespace std;
const int N = 1e5 + 1;
long long n,maxx,sum,avg;
long long a[N];
long long ceil_divide(long long a,long long b) { return (a + b - 1) / b;}
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		maxx = max(maxx,a[i]);
		sum += a[i];
	}
	avg = ceil_divide(sum,n - 1);
	cout << max(maxx,avg);
}
```

---

## 作者：liwenxi114514 (赞：0)

#### 题意：
有 $n$ 个人，每局游戏有 $1$ 个主持，$n-1$ 名选手，第 $i$ 个人想当 $a_i$ 局选手，问至少需要多少局游戏。
#### 思路：
很多大佬用的是**二分**，~~本蒟蒻不会~~，只好用**数学**。

根据题意，一局游戏有 $n-1$ 名选手，这 $n$ 个人总共就有 $\sum_{i=1}^{n}a_i$ 名选手，所以，直接用 $\left \lceil \frac{\sum_{i=1}^{n}a_i}{n-1}  \right \rceil $ 就可以得出局数啦！
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100005],sum;//不开long long见祖宗
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];//sum记录总选手数
	}
	long long ans=(sum%(n-1)==0)?sum/(n-1):sum/(n-1)+1;//向上取整，有余数就加一
	cout<<ans;
	return 0;
}
```
恭喜你，在第六个点 `WA` 了。这是为什么呢？我们来看一组数据。

$3$

$1$ $1$ $1000$

很明显，这个样例要输出 $1000$，但是用我们刚刚的方法会输出 $501$，那怎么办？其实很简单，只要把原本求出来的答案与 $a_i$ 中的最大值取最大就好了。

#### `AC` 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100005],sum,maxn;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
		maxn=max(maxn,a[i]);//取出a数组中的最大值
	}
	long long ans=(sum%(n-1)==0)?sum/(n-1):sum/(n-1)+1;
	cout<<max(ans,maxn);//将最大值与答案进行比较
	return 0;
}
```


---

## 作者：tanghairong (赞：0)

真的很简单

## 思路

+ 每局游戏有且仅有 $n-1$ 人，则局数不能少于 $\lceil\dfrac{\sum_{i=1}^n a_i(1\leq i\leq n)}{n-1}\rceil$。

+ 又因为第 $i$ 个人想玩 $a_i$ 局游戏，故局数不能少于 $\max(a_i)(1\leq i\leq n)$。

取两者最大值即可。

## 注意

+ 记得转换 ```int``` 和 ```double```

+ 记得用 ```long long```

## 代码

```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
signed main(){
    int n,sum=0,maxn=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        sum+=a;
        maxn=max(maxn,a);
    }
    cout<<max(maxn,(int)ceil(sum*1.0/(n-1)));
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 思路
因为每局有 $n-1$ 个人参加游戏，所以显然局数为 $\lceil \frac{\sum{a_i}} {n-1}\rceil$，然后因为局数至少为 $\max a_i$，所以在这两个数中取最大值即为答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
int n,x;
signed main(){
	cin>>n;
	int maxn=-1,sum=0;
	for(int i=1;i<=n;i++){
		cin>>x;
		maxn=max(maxn,x);//最大值
		sum+=x;//求和
	}
	int ans=1.0*sum/(n-1)+0.5;//向上取整
	cout<<max(maxn,ans)<<endl;//取max
	return 0;
}
```


---

