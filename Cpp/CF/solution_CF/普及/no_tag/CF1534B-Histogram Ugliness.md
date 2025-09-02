# Histogram Ugliness

## 题目描述

Little Dormi received a histogram with $ n $ bars of height $ a_1, a_2, \ldots, a_n $ for Christmas. However, the more he played with his new histogram, the more he realized its imperfections, so today he wanted to modify it to his liking.

To modify the histogram, Little Dormi is able to perform the following operation an arbitrary number of times:

- Select an index $ i $ ( $ 1 \le i \le n $ ) where $ a_i>0 $ , and assign $ a_i := a_i-1 $ .

Little Dormi defines the ugliness score of his histogram (after performing some number of operations) as the sum of the vertical length of its outline and the number of operations he performed on it. And to make the histogram as perfect as possible, he would like to minimize the ugliness score after modifying it with some number of operations.

However, as his histogram is very large, Little Dormi is having trouble minimizing the ugliness score, so as Little Dormi's older brother, help him find the minimal ugliness.

Consider the following example where the histogram has $ 4 $ columns of heights $ 4,8,9,6 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/5d4fda0f26b85e9fedc3c103ba4d223f004efdcd.png)The blue region represents the histogram, and the red lines represent the vertical portion of the outline. Currently, the vertical length of the outline is $ 4+4+1+3+6 = 18 $ , so if Little Dormi does not modify the histogram at all, the ugliness would be $ 18 $ .

However, Little Dormi can apply the operation once on column $ 2 $ and twice on column $ 3 $ , resulting in a histogram with heights $ 4,7,7,6 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/a49f3980f3c9ed62a810c32f51757eb225af4b4f.png)Now, as the total vertical length of the outline (red lines) is $ 4+3+1+6=14 $ , the ugliness is $ 14+3=17 $ dollars. It can be proven that this is optimal.

## 说明/提示

Example $ 1 $ is the example described in the statement.

The initial histogram for example $ 2 $ is given below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/a6df0f8291f71b8395f619c7fb85ca44f7963294.png)The ugliness is currently $ 2+1+6+3+4=16 $ .

By applying the operation once on column $ 1 $ , six times on column $ 3 $ , and three times on column $ 4 $ , we can end up with a histogram with heights $ 1,1,1,1,0,0 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/2079ec37e337586787093a1ba717d5a002aae17f.png)The vertical length of the outline is now $ 1+1=2 $ and Little Dormi made $ 1+6+3=10 $ operations, so the final ugliness is $ 2+10=12 $ , which can be proven to be optimal.

## 样例 #1

### 输入

```
2
4
4 8 9 6
6
2 1 7 4 0 0```

### 输出

```
17
12```

# 题解

## 作者：_xbn (赞：3)

考虑怎样才能使答案减少。

我们不难发现，当一个直方柱的两侧直方柱都比它低时，我们的操作数是丑陋度的一般，也就是说操作数小于丑陋度的减少量，此时我们可以进行操作。

所以我们可以扫一遍数组，对于上述情况进行操作，这样一定是最优的。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 600002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, b[N], c[N], a[N];
inline int read()
{
    register int x = 0, f = 1;
	char ch = getchar();
    while(!isdigit(ch))
	{
		if(ch == '-') f=-1;
		ch = getchar();
	}
    while(isdigit(ch))
	{
		x=(x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
    return x * f;
}
signed main()
{
    int T = read();
    while(T--)
    {
    	n = read();
    	ans = 0;
    	a[n + 1] = 0;
    	for(int i = 1; i <= n; i++)
    	{
    		a[i] = read();
    		if(a[i] > a[i - 1]) ans += a[i] - a[i - 1];
    		else ans += a[i - 1] - a[i];
		}
		ans += a[n];
    	for(int i = 1; i <= n; i++)
    	{
    		if(a[i - 1] < a[i] && a[i + 1] < a[i])
    		{
    			t = max(a[i - 1], a[i + 1]);
    			ans -= a[i] - t;
    			a[i] = t;
			}
		
		}
		cout << ans << endl;
	}
    
    return 0;
}

```


---

## 作者：BotDand (赞：2)

# $\text{Problems}$

给定一个 $n$ 列的直方图，第 $i$ 列的高度为 $a_i$。定义一个直方图的丑陋度为：该直方图所有裸露在外的竖线长度之和。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/5d4fda0f26b85e9fedc3c103ba4d223f004efdcd.png)

如图，该直方图裸露在外的竖线已用红色标出，可知该直方图的丑陋度为 $4+4+1+3+6=18$。

现在你可以进行如下操作：在直方图中选定一列，将该列高度减少 $1$。请最小化 操作数 $+$ 操作后直方图丑陋度 的值。

# $\text{Answer}$

考虑删除某列对答案产生的影响：

* 如果该列均处于山峰，则删除这列使直方图丑陋度减 $1$；

* 如果该列均处于山谷，则删除这列使直方图丑陋度加 $3$；

* 如果该列有一边比这列低，则删除这列使直方图丑陋度加 $1$。

因为要最小化，所以不难考虑只做操作 $1$。

贪心即可。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n;
int a[400002];
int ans,x;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
inline void work()
{
    n=read();
    a[0]=a[n+1]=0;
    for(int i=1;i<=n;++i) a[i]=read();
    ans=0;
    for(int i=1;i<=n+1;++i) ans+=abs(a[i]-a[i-1]);
    for(int i=1;i<=n;++i)
    {
        x=max(a[i-1],a[i+1]);
        if(a[i]>x) ans-=(a[i]-x);
    }
    print(ans);
}
signed main()
{
    t=read();
    while(t--) work();
    return 0;
}
```


---

## 作者：到底几只鱼呢 (赞：2)

# [题面](https://www.luogu.com.cn/problem/CF1534B)

对于这个问题，我们考虑每次操作对于减少答案以达到最优的贡献，可以发现：
- 若每次消去单独的一个，那么操作数 $+1$，红线长度 $-2$，对减少答案贡献 $+1$。

- 若消去同排连着的两个，则操作数 $+2$，红线长度 $-2$，对减少答案贡献 $+0$，即相当于没有消去。

以此类推，我们可以发现消去同排连着的越多，对答案有负贡献。

综上所述，当有单独的一个时我们将它消去，一定是最优的。

所以一开始算出红线长度，再减去操作数即为答案。

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace HMFS{
	#define int long long
	const int maxn=4e5+10;
	int a[maxn],n,T;
	void work() {
		cin>>T;
		while(T--) {
			memset(a,0,sizeof a);
			cin>>n;
			for(int i=1;i<=n;i++) {
				cin>>a[i];
			}
			int ans=0;
			for(int i=1;i<=n+1;i++) {
				ans+=abs(a[i]-a[i-1]);
			}
			for(int i=1;i<=n;i++) {
				int tmp=max(a[i-1],a[i+1]);
				if(a[i]>tmp) ans-=(a[i]-tmp);
			}
			cout<<ans<<'\n';
		}
	}
	#undef int
}
int main() {
	return HMFS::work(),0;
}
```

---

## 作者：HerikoDeltana (赞：1)

# B Histogram Ugliness

[CF1534B Histogram Ugliness](https://www.luogu.com.cn/problem/CF1534B)

## 题意简述

现有一个直方图，定义这个直方图的丑值为对它进行操作的次数 + 左右边缘长度（即图上红色线条），

可以对它进行的操作为：让其中一列的高度减一。

现在问你对于这个直方图，它能达到的**最小的丑值**。

每个测试点有多组数据，

对于每个直方图的输入：

第一行，总列数 $n$；

第二行，每一列的高度 $a_i$。

## 思路简述

这个题唯一的减少丑值的途径就是对这个直方图进行操作，于是我们从这里入手。

可以发现，对于某一列，若它的高度 $a_i$ 满足 $ a_i > a_{i-1}\ $ 且 $a_i > a_{i+1} $ ，那么对这一列进行操作就能减少 1 丑值。

换句话说，对这种“独峰”操作一次，能够减去两个单位的边缘长度，增加了一次操作，故总的来说丑值减一。

然后我们来看同时对相邻且与其他列相互孤立的两列进行操作的情况，

也就是 $ a_i = a_{i+1}$ 且 $ a_i > a_{i-1}$ 且 $ a_{i+1} > a_{i+2} $ 时。

可以发现这种情况下减去了两个单位的长度，但是操作次数也是加上了两次，所以这种操作不会对丑值减少造成贡献。

至于一次操作更多的情况，显然操作次数已经超过了减去的边缘长度，没有做这种操作的必要了。

简单总结一下就是，对“孤峰”操作可以帮助我们减去 1 丑值，

对“双峰”操作对我们达到最小丑值的目标毫无贡献，

而对“平原”的操作会让我们离达到最小丑值目标越来越远。

于是我们只需要考虑对“孤峰”进行操作。

在输入的时候先算出原始丑值，即最初的边缘长度，然后对“孤峰”进行判断即可。

## Code

```cpp
#include <bits/stdc++.h>
#define Heriko return
#define Deltana 0
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false)
using namespace std;
I void fr(LL & x)
{
    LL f=1;
    char c=getchar();
    x=0;
    while(c<'0' or c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' and c<='9') 
    {
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    x*=f;
}
I void fw(LL x)
{
    if(x<0) putchar('-'),x=-x;
    static LL stak[35];
    LL top=0;
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    putchar('\n');
}
CI MXX=5e5+5;
LL t,n,a[MXX],ans;
S main()
{
    fr(t);
    while(t--)
    {
        fr(n);ans=0;a[n+1]=a[0]=0;
        for(R LL i=1;i<=n;++i) fr(a[i]),ans+=abs(a[i]-a[i-1]);
        ans+=a[n];
        for(R LL i=1;i<=n;++i)
        {
            if(a[i]>a[i-1] and a[i]>a[i+1])
            {
                LL mid=max(a[i+1],a[i-1]);
                ans-=(a[i]-mid);
                a[i]=mid;
            }
        }
        fw(ans);
    }
    Heriko Deltana;
}
```
审核大大辛苦

---

## 作者：jiangtaizhe001 (赞：0)

[题目传送门](https://codeforces.com/problemset/problem/1534/B)  
## 题目大意
给定一个 $n$ 列的直方图，第 $i$ 列的高度为 $a_i$。定义一个直方图的丑陋度为：该直方图所有裸露在外的竖线长度之和。现在你可以在直方图中选出一列，将这一列的高度减 $1$ ，现在求操作数+操作后直方图丑陋度的最小值。  
## 题目解析
我们发现，只有将中间凸出来的方格去掉才能减小丑陋值。  
我们发现，将中间凸出的方格的高度减去 $1$ 之后就能将丑陋值减小 $2$ ,那么我们就只能去掉宽度为 $1$ 凸出来的方格了，因为只有这样才能减小答案。  
删的时候记得记录删的次数，保证删完之后当前列不能小于左右两边的任意一列，最后扫一遍得到丑陋值就可以了。  
丑陋值的计算公式（这里设 $a_0=a_{n+1}=0$ ）：
$$s=\sum^{n+1}_{i=1}|a_i-a_{i-1}|$$
```cpp
#include<cstdio>
#define maxn 400039
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
//#define debug
typedef long long ll;
typedef long long Type;
inline int abs(int x){ return x>0?x:-x; }
inline Type read(){
	Type sum=0;
	int flag=0;
	char c=getchar();
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') c=getchar(),flag=1;
	while('0'<=c&&c<='9'){
		sum=(sum<<1)+(sum<<3)+(c^48);
		c=getchar();
	}
	if(flag) return -sum;
	return sum;
}
int T;
int n;
ll a[maxn];
ll res,ans,tmp;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    T=read();
    while(T--){
    	n=read();
    	for(int i=1;i<=n;i++) a[i]=read();
    	a[0]=a[n+1]=res=ans=0;
		for(int i=1;i<=n;i++)
    	    if(a[i]>a[i-1]&&a[i]>a[i+1]){//这里代表是中间凸出来的
    	    	tmp=max(a[i-1],a[i+1]);
    	    	ans+=a[i]-tmp;
    	    	a[i]=tmp;
			}
		for(int i=1;i<=n+1;i++)
			res+=abs(a[i]-a[i-1]);
		printf("%lld\n",ans+res);
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

## 题目描述

给出柱状图，一次操作将一根柱子高度减一，求柱状图两侧总长+操作次数的最小值。

## 题解

可以证明，若 $a_{i-1}<a_i>a_{i+1}$，则需要把 $a_i$ 减至 $max(a_{i-1},a_{i+1})$。

证明：

设柱状图两侧总长 $x$，则原来指标为 $x$。

设 $max(a_{i-1},a_{i+1})$ 为 $y$。

现将 $a_i$ 变成 $y$，则两侧总长为 $x-2(a_i-y)$，即 $x+2y-2a_i$。

操作次数为 $a_i-y$。则指标为 $x+y-a_i$。

由于 $a_{i-1}<a_i>a_{i+1}$，所以 $y<a_i$，所以 $x+y-a_i<x$，所以答案比原来更优，故要删除。

同样可以证明其他情况不必删除。

这样贪心思路就出来了，模拟即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+2];
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		a[0]=0;
		a[n+1]=0;
		int sum2=0;
		for(int i=1;i<=n;i++){
			if(a[i]>a[i-1]&&a[i]>a[i+1]){
			    sum2+=(a[i]-max(a[i-1],a[i+1]));
				a[i]=max(a[i-1],a[i+1]);
			}
		}
		int sum=0;
		for(int i=1;i<=n+1;i++){
			sum+=llabs(a[i]-a[i-1]);
		}
		cout<<sum+sum2<<endl;
	}

	return 0;
}

```

---

## 作者：BorisDimitri (赞：0)

# 题意

给出一个由序列 $a$ 绘制而成的柱状图,

![](https://cdn.luogu.com.cn/upload/image_hosting/xt48swg5.png)

定义 $ugliness\;score $ 为上图的红边长度的和，即 $ugliness\;score = 4+4+1+3+6=18$

现在你可以选择一个下标 $i$ , 将 $a_i = a_i-1$ ，并付出 $1$ 点的 $ugliness\;score$ 代价。

![](https://cdn.luogu.com.cn/upload/image_hosting/tdw2z3rf.png)

如上图，我们将 $a_3 $ 减 $1$ ，$ugliness\;score = 4+3+1+6+1=12$ ，其中最后加的那个 $1$ 是付出的额外代价。

# 分析

我们发现，只有当 $a_i$ 为 **波峰** (即 $a_{i-1} < a_i < a_{i+1}$) 时，对 $a_i$ 进行 $-1$ 操作既可以减少 $1$  $ugliness\;score$ 。

否则操作后不会有影响或会增加 $ugliness\;score$ 。

> #### PROOF
> 将 $a_i -1$ 后,
>
> 当 $a_{i-1} < a_i < a_{i+1}$ 时， $ugliness\;score = ugliness\;score -2 +1 = ugliness\;score - 1$。
>
> 当 $a_{i-1} = a_i $ 或 $ a_i = a_{i+1}$ 时，$ugliness\;score = ugliness\;score -1 +1 = ugliness\;score$。
>
> 当 $a_{i-1} > a_i $ 或 $ a_i < a_{i+1}$ 时，$ugliness\;score = ugliness\;score -1 +1 +1 = ugliness\;score+1$。

所以，我们若 $a$ 序列中有 $t$ 个波峰，那么答案为不操作时的 $ugliness\;score -t $。



# Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int t;
int n;
const int N = 400005;

LL a[N];

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        memset(a , 0, sizeof a);
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);

        LL sub = 0;

        for(int i=1;i<=n;i++)
        {
            if(a[i-1] < a[i] && a[i] > a[i+1])
            {
                sub += a[i] - max(a[i-1],a[i+1]);
            }
        }

        LL sum = 0;
        for(int i=0;i<=n;i++) sum+=abs(a[i+1]-a[i]);
        cout<<sum-sub<<endl;
    }

    return 0;
}
```

---

