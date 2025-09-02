# Draw!

## 题目描述

你在看一场足球赛，但是你并不知道比赛的全过程，只知道在比赛过程中出现过的几个比分

现在，请你编写一个程序，算出比赛之中可能出现过的平局次数的最大值。

## 样例 #1

### 输入

```
3
2 0
3 1
3 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
0 0
0 0
0 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1
5 4
```

### 输出

```
5
```

# 题解

## 作者：da32s1da (赞：4)

分3种情况讨论。

设上一局为$a,b$，本局为$c,d$。

- 若$a=b$，$Ans+=\min(c,d)-a$。显然。
- 若$a<b$，$Ans+=\min(d-b+1,max(c-b+1,0))$。
 - 意思是，只有$c\ge b$时，才能对答案产生贡献
- 若$a>b$，$Ans+=\min(c-a+1,max(d-a+1,0))$。
 - 意思是，只有$d\ge a$时，才能对答案产生贡献
 
```
#include<cstdio>
inline int max(int u,int v){return u>v?u:v;}
inline int min(int u,int v){return u<v?u:v;}
int n,a,b,c,d,ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&c,&d);
        if(a==b)ans+=min(c,d)-a;
        if(a<b)ans+=min(d-b+1,max(c-b+1,0));
        if(a>b)ans+=min(c-a+1,max(d-a+1,0));
        a=c;b=d;
    }
    printf("%d\n",ans+1);//加上(0,0)
}
```

---

## 作者：caibet (赞：3)

[原题](https://www.luogu.com.cn/problem/CF1131B)

个人的想法是，考虑将比分抽象成区间。

假如前一次比分为 $3:1$，这一次比分为 $4:6$，则第一个玩家得分的区间为 $[3,4]$，第二个玩家得分的区间为 $[1,6]$。两个区间的重叠部分为 $[3,4]$，发现这就是可能出现的平局分数的区间。

然而，尝试之后我们会发现，某次平局可能被重复计算，如样例 $2$ 中：

```
3
0 0
0 0
0 0
```

这时可以添加一个变量 `last`，记录最后一个被计算的平局。如果新的平局区间的左端点正好是这个 `last`，则将得出的答案减一。

最终代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,sum=0;
	cin>>n;
	int px=0,py=0,x,y,last=-1;//通过迭代实现
	while(n--){
		cin>>x>>y;
		if(min(x,y)>=max(px,py)){//区间有重叠部分
			sum+=min(x,y)-max(px,py)+1;//求重叠部分大小
			if(max(px,py)==last) sum--;//去重
			last=min(x,y);//更新last
		}
		px=x;py=y;//迭代
	}
	cout<<sum<<endl;
	return 0;
}
```

---

## 作者：yty2010 (赞：2)

###### 水题一道，千万不要被难度是绿而劝退
题意就不描述了。

### 题目分析：分类讨论

我们设四个变量：$prex,prey$ 表示上一组给出的比分，$x,y$ 表示当前比分。

一共有两种情况：

第一种：$prex \ne prey$

举个例子，当 $prex=1,prey=3,x=3,y=4$ 时，显然会产生一种平局情况，即 $3:3$ 的情况。那么我们是怎么思考的呢？首先，因为 $prey$ 已经等于 $3$，不会出现 $1:1,2:2$ 的情况；其次，由于 $x$ 等于 $3$，所以还没有出现 $4:4$ 的情况，因此只有上述一种平局情况。



因此可以推得在这一种情况下的平局情况数为：
$$
\min(x,y)-\max(prex,prey)
$$
但对于一种特殊数据：当 $prex=1,prey=4,x=3,y=5$ 时，一种方法都没有，但上述公式会算出 $-1$,因此对其进行优化：
$$
\max(0,\min(x,y)-\max(prex,prey))
$$
第二种情况：$prex=prey$

再举个例子：当 $prex=3,prey=3,x=4,y=5$ 时，如果用第一种情况会有两种情况。但实际上 $3:3$ 这一种情况已经算过了，因此进行第二种判断。

因此情况数为：
$$
\min(x,y)-prex
$$

给出代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum=1,prex,prey;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		if(prex==prey)
			sum+=min(x,y)-prex;  //情况1
		if(prex!=prey)
			sum+=max(0,min(x,y)-max(prex,prey)+1);  //情况2
		prex=x;
		prey=y;             //更新上一组比分
	}
	cout<<sum;
}
```

---

## 作者：SGColin (赞：2)

答案是 $\sum \max(0,\min(x,y)-\max(lastx, lasty, last + 1) + 1)$ 。

最后的 $last = \min(lastx, lasty)$ ，是为了避免给出局面一直不变且平局的情况。


```C++
for (int i = 1, x, y; i <= n; ++i) {
  x = rd(); y = rd();
  ans += max(0ll, min(x, y) - max(lst, max(lstx, lsty)) + 1);
  lst = min(x, y) + 1;
  lstx = x; lsty = y;
}
```

---

## 作者：lizhengdong (赞：1)

## 1.题目分析
题目让我们求最大平局的次数。

我们可以这样考虑，每次在两个比分之间算最大平均次数，最后求和。

## 2.解题思路
对于每次，我们可以分 $3$ 种情况讨论。

设本局为 $a$、$b$，下一局为 $c$、$d$。

- 若 $a=b$，`ans+=min(c,d)−a`。
- 若 $a<b$，`ans+=min(d−b+1,max(c−b+1,0))`。  
只有 $c\ge b$ 时，才会有平局。
- 若 $a>b$，`ans+=min(c−a+1,max(d−a+1,0))`。  
只有 $d\ge a$ 时，才会有平局。
## 3.AC代码
``` cpp
#include <bits/stdc++.h>
using namespace std;
int n,i,ans,a,b,c,d,a1[10010],a2[10010];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(i=1;i<=n;i++)cin>>a1[i]>>a2[i];
    ans=1;//开始时（0，0）平局
    for(i=0;i<n;i++){
        a=a1[i];b=a2[i];
        c=a1[i+1];d=a2[i+1];
        if(a==b)ans+=min(c,d)-a;//三种情况
        else if(a<b)ans+=min(d-b+1,max(c-b+1,0));
        else ans+=min(c-a+1,max(d-a+1,0));
    }
    cout<<ans; 
}
```

---

## 作者：LJC00118 (赞：1)

考虑当前状态为 $[x, y]$，下一个状态为 $[a, b]$，最大能获得几个平局

首先要使 $ x $ 和 $ y $ 相等，然后 ++$x$，++$y$，直到 $ x >= a $ 或 $ y >= b $ 时停止

分类讨论一下即可

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

int n, x, y, ans;

int main() {
    read(n);
    for(register int i = 1; i <= n; i++) {
        int a, b; read(a); read(b);
        int go = max(x, y), t = 0;
        if(x != y) ++t;
        ans += max(0, min(a - go, b - go) + t);
        x = a; y = b;
    }
    cout << ans + 1 << endl;
    return 0;
}
```

---

## 作者：lhs_chris (赞：0)

### 说句闲话
这篇题解语言比较朴实，解释的自认为比较清楚了。
# 思路
我们记上一轮的数字为 $a$ 和 $b$，这一轮的两个数字为 $x$ 和 $y$。我们可以将每次的比分抽象成两个区间 $a \sim x$ 和 $b \sim y$。我们把这两个区间丢到数轴上，我们要求的就是重合的部分的数字数量。

那我们可以分类讨论一下。

1. 第一种情况最容易想到。$a$ 和 $b$ 相等。那么此时的答案为 $\min(x-a,y-b)$。因为 $a$ 和 $b$ 相等，所以 $a$ 和 $b$ 一定会平局。所以在计算的时候左边的端点 $a$ 和 $b$ 已经被计算过了，所以不再计算，所以答案不需要加一。
2. 第二种情况就是 $a$ 和 $b$ 不相等。答案也就是 $\max(0,\min(x,y)-\max(a,b)+1)$。因为，每次给出分数肯定是递增或不变的，不会下降，也就是说在合理的情况下，在数轴之上，$a$ 和 $b$ 之中的最大值一定大于等于 $x$ 和 $y$ 之中的最小值，他们之间数字的数量就是答案。为什么此处又要加一？因为两个端点都不会被计算，$a$ 和 $b$ 之中我们选择最大值，无论如何也不会选重复。但是考虑到或许会没有重合部分，也就是说可能会算出来负数，所以答案要和零取最大值。


# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x,y,n;
int ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		if(a==b)
		{
			ans=ans+max(0,min(x-a,y-b));
		}
		else
		{
			ans=ans+max(0,min(x,y)-max(a,b)+1);
		}
		a=x;
		b=y;
	}
	printf("%d",ans+1);
}
```

---

## 作者：HEzzz (赞：0)

[题目跳转键](https://www.luogu.com.cn/problem/CF1131B)

## 分类讨论

因为我们的答案只取决于每一轮的比分和上一轮的比分趋势。 

所以我们令:

- $a$ 和 $b$ 表示当前这一轮的比分。

- $lsta$ 和 $lstb$ 表示前一轮的比分。 
    
然后我们就可以进行一下分类:

- 当 $lsta=lstb$，那么显然对答案的贡献即为 $\min(a,b)-lsta$。
    
- 当 $lsta<lstb$，那么对答案的贡献即为 $\min(a,b)-lstb+1$。为甚呢？因为上一局 $lsta$ 和 $lstb$ 已经固定，所以打平的情况只有在 $a \ge lstb$ 时才会出现打平。

- 当 $lsta>lstb$，那么对答案的贡献即为 $\min(a,b)-lsta+1$。为甚呢？因为上一局 $lsta$ 和 $lstb$ 已经固定，所以打平的情况只有在 $b \ge lsta$ 时才会出现打平。 
     

## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl; 
const int N=1e4;
lxl lsta,lstb,a,b,n,ans;
int main()
{   
	scanf("%lld",&n);
	_rep(i,1,n)
	{
		scanf("%lld%lld",&a,&b);
		if(lsta==lstb) ans+=min(a,b)-lsta;
		if(lsta<lstb) ans+=max(0ll,min(a,b)-lstb+1);//加点特判
		if(lsta>lstb) ans+=max(0ll,min(a,b)-lsta+1);//加点特判
     /*
     若你是像我一样的懒人，你把上面3个if换成：
     ans+=min(a,b)-max(lsta,lstb)+(lsta!=lstb);
     为什么呢？其实上式就是通过那3个if转换一下的，没有过多意义，纯懒人才用。
     */
		lsta=a;lstb=b;
	}
	printf("%lld",ans+1);//还有(0,0)的情况
	return 0;
}

```


---

## 作者：Yizhixiaoyun (赞：0)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17152257.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1131B)

好水的绿题，当放松了。

## 题目分析

为了方便表述，定义 $lsta,lstb,nowa,nowb$，分别表示上次双方的得分以及当前的得分。

考虑分讨，若 $lsta=lstb$，贡献即 $\min(nowa,nowb)-lsta$。

上次得分不同的情况有 $2$ 种，但本质上是一样的，因此我们假设 $lsta<lstb$。

显然平局只会在落后方当前得分追上了领先方的上次得分时才会发生，在此条件下，贡献为 $\min(nowa,nowb)-lstb+1$。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define debug puts("Shiina_Mashiro_kawaii")
#define ok printf("%d\n",ans2)
#define no puts("-1")
// #define int long long
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=10010;
int n;
int ans;
int flag;
int a[maxn],b[maxn];
inline void init(){
	n=read();ans=1;
	for(register int i=1;i<=n;++i){
		a[i]=read();b[i]=read();
	}
	ans+=min(a[1],b[1]);
}
int main(){
	init();
	for(register int i=2;i<=n;++i){
		if(a[i-1]<b[i-1]) flag=1;
		else if(a[i-1]>b[i-1]) flag=2;
		else flag=3;
		int minn=min(a[i],b[i]);
		if(flag==1){
			if(a[i]>=b[i-1]) ans+=minn-b[i-1]+1;
		}
		else if(flag==2){
			if(a[i-1]<=b[i]) ans+=minn-a[i-1]+1;
		}
		else ans+=minn-a[i-1];
	}
	printf("%d",ans);
}
```

---

## 作者：Siteyava_145 (赞：0)

每一次记录这一次的状态 $ba,bb$ 与上一次的状态 $a,b$。

每次的平局次数为这次的最小值与上一次的最大值的差 $+1$。

需要注意：如果原比分 $ba,bb$ 本身就是一个平局，则不能计算此次，需要将计数器 $-1$。

```
#include<bits/stdc++.h>
using namespace std;
int cnt=0,flag=-1;
int main()
{
    int n;cin>>n;
    int ba=0,bb=0;
    for(int i=1;i<=n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        if(min(a,b)>=max(ba,bb)){//判断比分之间的重叠，防止误判
			cnt+=min(a,b)-max(ba,bb)+1;//平局次数
			if(max(ba,bb)==flag)cnt--;//如果上一次的比分不相同
			flag=min(a,b);//
		}
		ba=a;//记录比分
		bb=b;
    }
    cout<<cnt;
}
```


---

## 作者：404_notfound (赞：0)

纯贪心。

设上一次比分为$a,b$,当前比分为$x,y$

分三种情况讨论：

### 1.a==b
显然最大平局数是 $min(x,y)-a$

### 2.a>b
我们发现，要想出现平局，必须有 $y>=a$ ，对答案的贡献就是 $y-a+1$。

忘了些什么？有 $x<y$ 的情况时，平局的次数最多为$x-a+1$ 

于是乎此处的贡献是 $min(x[i],y[i])-x[i-1]+1$

### 3.a>b
可以类比上面的第二种情况

这时候要出现平局就必须满足 $x>=b$

考虑 $y>x$ 的情况，贡献是 $min(x[i],y[i])-y[i-1]+1$

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
#define maxn 10009
int x[maxn],y[maxn]; 
signed main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	int ans=1;
	x[0]=0,y[0]=0;
	for(int i=1;i<=n;i++)
	{
		if(x[i-1]==y[i-1])
		{
			ans+=min(x[i],y[i])-x[i-1];
		}else if(x[i-1]>y[i-1])
		{
			if(y[i]>=x[i-1])//必定发生平局 
			{
				ans+=min(x[i],y[i])-x[i-1]+1;
			}
		}else if(x[i-1]<y[i-1])
		{
			if(x[i]>=y[i-1])
			{
				ans+=min(x[i],y[i])-y[i-1]+1;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}

```


---

