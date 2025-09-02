# [ABC359E] Water Tank

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc359/tasks/abc359_e

長さ $ N $ の正整数列 $ H=(H\ _\ 1,H\ _\ 2,\dotsc,H\ _\ N) $ が与えられます。

長さ $ N+1 $ の非負整数列 $ A=(A\ _\ 0,A\ _\ 1,\dotsc,A\ _\ N) $ があります。 はじめ、$ A\ _\ 0=A\ _\ 1=\dotsb=A\ _\ N=0 $ です。

$ A $ に対して、次の操作を繰り返します。

1. $ A\ _\ 0 $ の値を $ 1 $ 増やす。
2. $ i=1,2,\ldots,N $ に対して、この順に次の操作を行う。
  - $ A\ _\ {i-1}\gt\ A\ _\ i $ かつ $ A\ _\ {i-1}\gt\ H\ _\ i $ のとき、$ A\ _\ {i-1} $ の値を $ 1 $ 減らし、$ A\ _\ i $ の値を $ 1 $ 増やす。
 
$ i=1,2,\ldots,N $ のそれぞれに対して、初めて $ A\ _\ i\ >\ 0 $ が成り立つのは何回目の操作の後か求めてください。

## 说明/提示

### ストーリー

> 長い水槽があり、高さの異なる板が等間隔に配置されています。 高橋くんは、この水槽の端へ水を注いでいったとき、板で区切られたそれぞれの領域に水が到達する時刻が知りたいです。

### 制約

- $ 1\leq\ N\leq2\times10\ ^\ 5 $
- $ 1\leq\ H\ _\ i\leq10\ ^\ 9\ (1\leq\ i\leq\ N) $
- 入力はすべて整数
 
### Sample Explanation 1

はじめ $ 5 $ 回の操作では以下のようになります。 それぞれの行が一回の操作に対応し、左端が $ 1 $ 番の操作を、それ以外が $ 2 $ 番の操作に対応します。 !\[\](https://img.atcoder.jp/abc359/570466412318b9902952c408a421be0c.png) この図から、$ A\ _\ 1\gt0 $ が初めて成り立つのは $ 4 $ 回目の操作の後、$ A\ _\ 2\gt0 $ が初めて成り立つのは $ 5 $ 回目の操作の後です。 同様にして、$ A\ _\ 3,A\ _\ 4,A\ _\ 5 $ に対する答えは $ 13,14,26 $ です。 よって、`4 5 13 14 26` を出力してください。

### Sample Explanation 2

出力すべき値が $ 32\operatorname{bit} $ 整数に収まらない場合があることに注意してください。

## 样例 #1

### 输入

```
5
3 1 4 1 5```

### 输出

```
4 5 13 14 26```

## 样例 #2

### 输入

```
6
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
1000000001 2000000001 3000000001 4000000001 5000000001 6000000001```

## 样例 #3

### 输入

```
15
748 169 586 329 972 529 432 519 408 587 138 249 656 114 632```

### 输出

```
749 918 1921 2250 4861 5390 5822 6428 6836 7796 7934 8294 10109 10223 11373```

# 题解

## 作者：Sorato_ (赞：5)

# ABC359E Water Tank

## 题目大意

给定一个长度为 $N$ 的序列 $H$，和一个长度为 $N+1$ 初始为 $0$ 的序列 $A$。每一轮在 $A$ 上进行如下操作：

- 将 $A_0$ 的值增加 $1$。
- 依次遍历 $1\sim N$，若 $A_{i-1}>A_i$ 且 $A_{i-1}>H_i$，则将 $A_{i-1}$ 减 $1$，将 $A_i$ 加 $1$。

求对于 $i=1,2,\dots,N$，需要多少轮操作能使 $A_i>0$。

## Solve

![](https://cdn.luogu.com.cn/upload/image_hosting/mni1q94u.png)

如果要使 $A_1>0$，首先要将 $A_0$ 填满，耗费 $3$，再向 $A_1$ 填 $1$。

如果要使 $A_2>0$，要将 $H_2$ 左侧的都填满，共耗费 $12$。

如果要使 $A_5>0$，要将 $H_5$ 左侧的都填满，共耗费 $40$。

以此类推，若 $H_i$ 是前缀最大值，那么就要耗费 $i\times H_i$ 的代价把 $H_i$ 左侧全填满，也就是填成一个矩形。

那如果 $H_i$ 不是前缀最大值呢？以 $H_4$ 为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/sjl2exl2.png)

忽略墙的厚度，则相当于把 $H_2$ 和 $H_4$ 间填成一个矩形，共耗费 $H_4\times(4-2)$。

以此类推，若 $H_i$ 不是前缀最大值，那么需要去找 $H_i$ 左侧第一个比它高的 $H_j$，花费即为 $H_i\times(i-j)$。

单调栈实现之。

## Code

```c++
// LUOGU_RID: 163040327
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n,h[200010],sum[200010];
stack<int>s;
signed main()
{
	n=read();
	for(int i=1;i<=n;i=-~i)
	{
		h[i]=read();
		while(!s.empty()&&h[s.top()]<=h[i])	s.pop();
		if(s.empty())	sum[i]=i*h[i];
		else	sum[i]=sum[s.top()]+(i-s.top())*h[i];
		printf("%lld ",sum[i]+1);
		s.push(i);
	}
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：5)

## 背景

中考结束了，但是暑假只有一天，这就是我现在能在机房里面写题解的原因……

## 分析

这道题就是个单调栈。

题目上问你第一滴水流到每个位置的时间。我们考虑，答案其实就是比当前木板高且距离当前木板最近的那一个位置的答案加上当前木板的高度与那一个位置的距离构成的矩形面积再减去中间较低木板构成的矩形面积。这个思路联想到单调栈的话还是很好想到的。

所以我们存一个结构体栈，两个参数分别表示这个位置木板的高度和与上一个比它高的木板的距离。

在更新的时候，先按照一般单调栈操作用当前木板高度去更新栈的信息，用一个变量统计距离之和，并把每个栈位最终会影响答案的矩形面积累加一下。放一下代码：

```cpp
  while(!st.empty()&&st.top().h<=h[i])
  {
    int now=st.top().h,sum=st.top().sum;
    dat+=now*sum;
    t+=sum;
    st.pop();
  }
```

然后按照思路更新当前答案并输出，再让当前木板高度和距离进栈即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int maxn=1e6+10;
int n,h[maxn];
int ans=1;
struct no
{
	int h,sum;
};
stack<no> st; 
signed main()
{
//  freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)h[i]=read();
	for(int i=1;i<=n;i++)
	{
		int t=1,dat=0;
		while(!st.empty()&&st.top().h<=h[i])
		{
			int now=st.top().h,sum=st.top().sum;
			dat+=now*sum;
			t+=sum;
			st.pop();
		}
		ans=ans+h[i]*t-dat;
		st.push({h[i],t});
		printf("%lld ",ans);
	}
	return 0;
}
```

---

## 作者：back_find (赞：2)

一个单调栈优化 dp 题。（大概黄？）

先解释下题目：水缸中间 $n$ 个板子，求水最早到 $i$ 个隔板后的时刻。

那这个怎么算呢？考虑如果有一个板子 $i$，找到前面一个 $j$,使得 $h_j>h_i$ 且 $j+1$ 到 $i$ 没有比 $h_i$ 大的数时，$j+1$ 到 $i$ 之间形成了一个能装 $h_i(i-j)$ 水的区块。

定义 $f_i$ 为上面 $i$ 对应的 $j$（如果 $j$ 不存在就为零），发现可以使用单调栈解决。

定义 $dp_i$ 为水最早到 $i$ 个隔板后的时刻的**前一刻**。

可列出如下方程：

$$dp_0=0$$

$$dp_i=h_i(i-f_i)+dp_{f_i}$$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long i64;
const int mod=998244353;
const int N=2e5+5;
i64 n,h[N],f[N],ans[N];
int main(){
	ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    stack<i64>s;
    for(int i=1;i<=n;i++){
		while(!s.empty()&&h[s.top()]<=h[i])s.pop();
		if(s.empty())f[i]=0;
		else f[i]=s.top();
		s.push(i);
	}
    ans[0]=0;//边界条件
    for(int i=1;i<=n;i++){
        ans[i]=(i-f[i])*h[i]+ans[f[i]];
        cout<<ans[i]+1<<' ';//前一刻！
    }
}

```

---

## 作者：HasNoName (赞：1)

### 思路
由于每次一定是一整个水平线相同的一块一起增加，所以可以将同水平线的一整块压缩成一个。

后面的把前面的覆盖之后，前面的就和后面的一样了，不用考虑，所以可以使用单调栈。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
const ll INF=1e18;
ll a[N];//隔板高度
struct T
{
	ll l,r,w;//从l到r，水平线高度为w
}c[N];//栈
int top;//栈顶
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	c[++top]={-1,-1,INF};//假设第0位为无穷高，这样可以不用考虑越界情况
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		int l=i-1;
		while(c[top].w<=a[i])//单调栈
		{
			l=c[top].l;//水位线延长
			ans+=(c[top].r-c[top].l+1)*(a[i]-c[top].w);//提高将l到r中一格加一
			top--;//弹出
		}
		c[++top]={l,i-1,a[i]};
		ans+=a[i];//加上最近的高度
		cout<<ans+1<<' ';//因为刚好要过一格水，故答案加一
	}
	cout<<'\n';
	return 0;
}
```

---

## 作者：Vitamin_B (赞：1)

# 思路
设 $x$ 表示最后一个满足 $h_x\ge h_i$ 且 $x<i$ 的模板，显然要使 $i$ 号点灌到水那么就要把 $x$ 以后的地方全都淹没到 $h_i$ 为止，所以 $ans_i=ans_x+(i-x)\times h_i$。

怎么求 $x$ 呢？显然，若 $h_j<h_i$，则 $x_i\ge x_j$。所以，我们只要从 $i-1$ 开始，一路往上跳，直到 $h_j\ge h_i$ 为止。然后把 $x_i,ans_i$ 存下来输出就行。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, h[200005], lst[200005];
ll ans[200005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	h[0] = 1e9 + 5, ans[0] = 1;
	for (int i = 1; i <= n; ++ i) {
		cin >> h[i];
		lst[i] = i - 1;
		while (h[i] > h[lst[i]])
			lst[i] = lst[lst[i]];
		cout << (ans[i] = ans[lst[i]] + (ll) (i - lst[i]) * h[i]) << ' ';
	}
	return 0;
}
```

---

## 作者：MightZero (赞：0)

## 题意

有一个水箱，其中有 $n$ 块不同高度且间距相同的垂直挡板，第 $i$ 块挡板的高度为 $h_i$。这些挡板将水箱分为 $n+1$ 个部分。将这 $n+1$ 个部分以 $0,1,\dots,n$ 标号。

定义一个单位的水量为底面面积占据 $1$ 个部分且高度为 $1$ 的立方体的容积。

现在从 $0$ 号位置开始注水，每秒注水一个单位，求水到达 $1,2,\dots,n$ 位置的时间。

## 思路

我们不妨先考虑**注满**每个位置需要的时间（即使得第 $i$ 个位置的水位高度为 $h_{i+1}$ 所需的时间），那么水到达每个位置的时间就是注满前一个位置所需的时间加 $1$。

采用动态规划，设 $dp_i$ 为**注满**第 $i$ 个位置所需要的时间。

对于每个 $dp_i$，我们可以从当前位置向前查找第一个高度大于 $h_{i+1}$ 的挡板，然后将两个挡板之间的位置注水到 $h_{i+1}$ 即可。

转移：
$$dp_i=dp_j+(i-j)\times h_i,j=\max([1,i])\ 且\ h_j>h_{i+1}$$

可以使用记忆化搜索解决，但是直接向前枚举会 `TLE`，所以还需要利用单调栈提前预处理每个挡板 $i$ 对应的 $j$。

## Code

```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
using namespace std;
using ll = long long;
const ll N=2e5+5;
ll h[N],n,pre[N];
ll dp[N];
stack<ll> st;
ll dfs(ll p)
{
    if(dp[p])return dp[p];
    ll res=0,pos=0;
    res+=(p-pre[p])*h[p];
    if(pre[p])res+=dfs(pre[p]);
    return dp[p]=res;
}
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
inline void write(ll x)
{
    if(x<0){putchar('-');x=-x;}
    if(x%10==x){putchar(x+'0');return;}
    write(x/10);putchar(x%10+'0');
}
signed main()
{
    n=read();
    loop(i,1,n)h[i]=read();
    rloop(i,1,n)
    {
        while(!st.empty()&&h[st.top()]<h[i])
        {
            pre[st.top()]=i;
            st.pop();
        }
        st.push(i);
    }
    rloop(i,1,n)if(!dp[i])dfs(i);
    loop(i,1,n){write(dp[i]+1);putchar(' ');}
    return 0;
}
```
[AC Record](https://atcoder.jp/contests/abc359/submissions/54826916)

---

## 作者：Ivan422 (赞：0)

难度建议：单调栈加动态规划，建议黄到绿左右最为合适。

题目大意：直接看图，一个大箱子，中间有 $n$ 个隔板，高为 $a_i$，从第 $1$ 个板前面开始注水，每次注水一个单位，耗费一个单位时间。按照现实世界的原则水会溢出，落到隔板的右边，每一次溢出都要记录当前的时间。水落到最后一个隔板右边就终止模拟倒水，输出记录的时间。

思路：对于每一个隔板 $a_i$，最大的阻碍就是前面第一个比隔板高的板，设阻碍隔板高为 $tp$。而这两个隔板中间的水会全部与 $a_i$ 齐平后才会溢出，而之前的水就可以直接转移 $ans_j$ 的。最终得出转移式 $ans_i=ans_j+(i-j)\times a_i$。最后输出每一个结果即可，注意这里的定义是水满的时刻，而不是水溢出的时刻，所以答案要加 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,M=55;
int n,a[N],ans[N],tp;
stack<int>st;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        while(st.size()&&a[st.top()]<=a[i])st.pop();
        tp=(st.size()>0)?st.top():0;
        st.push(i);
        ans[i]=ans[tp]+(i-tp)*a[i];
    }
    for(int i=1;i<=n;i++)cout<<ans[i]+1<<" ";
    return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

### Idea

对于一个柱子无非只有两种情况：

- 它比之前每一个柱子高度低。
- 它是目前最高的。

如果比一个柱子高度低，由题意模拟，我们找到**最靠右的比它高的**柱子，把答案加上即可。

设那个找到的柱子坐标为 $x$，现在模拟到了 $i$，则下一个答案答案应为：$(i-x+1)h_i+(ans_{i}-1)+1=(i-x+1)h_i+ans_i$。

如果它是最高的，则前面所有的都要填满，则下一个答案是 $h_i(i+1)+1$。

实现起来，为了找到最靠右的比它高的柱子，可以使用单调栈。如果一根柱子在另一个柱子左边还比它矮，它一定没用，扔掉就行了。一遍遍的枚举，最后剩下的一定是**最靠右的比它高的**柱子。

每一个柱子只会进出栈一次，因此时间复杂度是 $\operatorname{O}(n)$。

### Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int h[200005];
long long ans[200005],ju[200005];
int st[200005],id[200005];
int top=200001;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>h[i];
	ans[0]=1;ju[0]=h[1];
	st[0]=2147483647;
	st[1]=h[1]; id[1]=0;
	for(int i=1;i<=n;i++){
		ans[i]=ju[i-1]+1;
		while(top!=0&&st[top]<=h[i+1])top--;
		id[++top]=i;
		st[top]=h[i+1];
		int t=top-1;
		if(t!=0)ju[i]=ju[id[t]]+(i-id[t])*h[i+1];
		else ju[i]=h[i+1]*(i+1);
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：Double_Light (赞：0)

手搓一下，我们容易发现当第 $i$ 位可以灌入水的时候，前 $(i-1)$ 位必须比 $h_i$ 大。

显然只要当高度比当前的下一位大 $1$，就会溢出到下一个，长度是单调递增的，所以可以用单调栈模拟。

栈中需要维护两个东西，柱子的高度和柱子的下标。

每一次进栈时，把栈中所有高度小于当前柱子的柱子全部出栈，然后将这跟柱子进栈。设这是第 $i$ 根栈中的柱子，$h_i$ 代表第 $i$ 跟柱子的高度，$a_i$ 代表栈中第 $i$ 根柱子的下标，则该柱子的贡献是 $(a_i-a_{i-1})\times h_i$。

注意：
- 减去出栈柱子的贡献。
- 栈底初始放一根高度为 $\infty$ 的柱子，下标为 $0$。

代码如下：

```cpp
#include<iostream>
#include<stack>
#define int long long
using namespace std;
int n;
int h[200005];
int a[200005],tot;
int ans;
pair<int,int> st[200005];
int top;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>h[i];
	}
	st[++top].first=1e18;
	st[top].second=0;
	for(int i=1;i<=n;i++){
		while(st[top].first<h[i]){
			ans-=a[tot--];
			top--;
		}
		a[++tot]=(i-st[top].second)*h[i];
		ans+=a[tot];
		st[++top]={h[i],i};
		cout<<ans+1<<' ';
	}
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：0)

### [AT_abc359_e [ABC359E] Water Tank](https://www.luogu.com.cn/problem/AT_abc359_e)
如果一个水桶即将有水，那么之前的所有低于他的桶一定都装满了水，否则水不会过来。\
所以需要维护一个高度单调递减的栈就行，就是单调栈板子题，时间复杂度 $\mathcal{O}(n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e5+10;
int n,h[N],f[N],head,tail,q[N];
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	n=read();int ans=0;
	h[0]=2e18;
	for(int i=1;i<=n;++i){
		h[i]=read();
		int pos=0;
		while(head<=tail&&h[i]>h[q[tail]]){--tail;}
		pos=q[tail],q[++tail]=i;
		f[i]=f[pos]+(i-pos)*h[i];
		std::cout<<f[i]+1<<' ';
	}
}
```

---

## 作者：kkxacj (赞：0)

#### 思路

容易发现，假设当前执行到了 $i$，$h_i$ 是最大的，那么第 $i$ 个答案为 $h_i \times i + 1$ 因为只有第 $i-1$ 个地方的水比 $i$ 的水位高且至少跟 $h_i$ 一样高才能向 $i$ 流。

当第 $i$ 个不是最高的，发现只需要找到从 $i$ 往前第一个 $j$ 使得 $h_j \ge h_i$，记录 $ans_i$ 为前 $i-1$ 个位置都被填满，再加水就会向 $i$ 流的时间，那么当前点的答案就为 $ans_j + \left(i-j\right) \times h_i + 1$。

找第一个比 $h_i$ 大的直接用线段树维护就行了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls (p<<1)
#define rs ((p<<1)+1)
#define mid ((c[p].l+c[p].r)>>1) 
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
int n,a[200010],b[200010],x = 1,t,mx,l,sum[200010],cnt,ans;
map<int,int>mp;
struct w
{
	int l,r,dat,ad;
}c[1000010];
void build(int p,int l,int r)
{
	c[p].l = l; c[p].r = r;
	if(l == r) 
	{
		return;
	}
	build(ls,l,mid); build(rs,mid + 1,r);
	c[p].dat = max(c[ls].dat,c[rs].dat);
}
void change(int p,int l,int r,int k)
{
	if(l <= c[p].l && c[p].r <= r)
	{
		c[p].dat = k;
		return;
	}
	if(l <= mid) change(ls,l,r,k);
	if(mid < r) change(rs,l,r,k);
	c[p].dat = max(c[ls].dat,c[rs].dat);
}
void ask(int p,int l,int r)
{
	if(l <= c[p].l && c[p].r <= r)
	{
		ans = max(ans,c[p].dat);
		return;
	}
	if(l <= mid) ask(ls,l,r);
	if(mid < r) ask(rs,l,r);
}
signed main()
{
	read(n);
	for(int i = 1;i <= n;i++) read(a[i]),b[i] = a[i];
	sort(b+1,b+1+n);
	for(int i = 1;i <= n;i++) if(!mp[b[i]]) mp[b[i]] = ++cnt;
	build(1,1,cnt);
	sum[1] = a[1]; mx = a[1];
	change(1,mp[a[1]],mp[a[1]],1);
	print(sum[1]+1),pc(' ');
	for(int i = 2;i <= n;i++)
	{
		ans = 0;
		ask(1,mp[a[i]],cnt);
		change(1,mp[a[i]],mp[a[i]],i);
		sum[i] = sum[ans] + (i-ans)*a[i];
		print(sum[i]+1),pc(' ');
	}
	flush();
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

~~有多少人是看了图例后恍然大悟的。~~

这题其实是让你模拟一个水罐储水的过程。水罐被隔成了若干个隔间，$H$ 数组就是每道墙的高度，$A$ 数组就是每个隔间内的水量。水超过隔墙高度后会自动溢出到下一个隔间，输出向第一个隔间内分别注多少水能让每个隔间内有水。

我们考虑一道墙和它之前第一道比它高的墙之间的隔间。要使得水溢出到这道墙后的那个隔间，则该区间可以看成一个大的隔间，中间的每一堵墙高度都没有影响，因为它们都比区间的端点低，不影响水的溢出。所以使得其后的隔间有水需要的最少水量就是把改区间之前的隔间全部装满，再把这个区间装满，再进一单位的水，之和。

这样我们就很容易写了。第一位的答案为 $H_1+1$。对于第 $i$ 个元素，若它前面第一个大于它的元素位置为 $K$，设第 $K-1$ 位的答案为 $x+1$，则第 $i$ 位的答案为 $x+(i-K)H_i+1$。

如何求出每个元素前第一个比它大的元素呢？只需要把单调栈模板的遍历顺序倒过来就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int id,x;
}a[1000005];
stack<node> s;
int n,f[1000005];
int f1[1000005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x;
	for(int i=1;i<=n;i++) a[i].id=i;
	for(int i=n;i>=1;i--){
		while(!(s.empty()||a[i].x<=s.top().x)) f[s.top().id]=i,s.pop();
		s.push(a[i]);
	}//以上为单调栈模板，唯一的区别是入栈时的遍历顺序 
	for(int i=1;i<=n;i++){
		f1[i]=f1[f[i]]+(i-f[i])*a[i].x;//如上递推式。为了方便后一位，f1数组存的其实是每一位的答案-1 
		cout<<f1[i]+1<<" ";//+1才是真正的答案 
	}
	return 0;
}
```

---

