# Building a Fence

## 题目描述

You want to build a fence that will consist of $ n $ equal sections. All sections have a width equal to $ 1 $ and height equal to $ k $ . You will place all sections in one line side by side.

Unfortunately, the ground beneath the fence is not flat. For simplicity, you can think that the ground level under the $ i $ -th section is equal to $ h_i $ .

You should follow several rules to build the fence:

1. the consecutive sections should have a common side of length at least $ 1 $ ;
2. the first and the last sections should stand on the corresponding ground levels;
3. the sections between may be either on the ground level or higher, but not higher than $ k - 1 $ from the ground level $ h_i $ (the height should be an integer);

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1469C/639e8b11cbea2061b5e63469ccc4551e6fb009c3.png)One of possible fences (blue color) for the first test caseIs it possible to build a fence that meets all rules?

## 说明/提示

In the first test case, one of the possible fences is shown in the picture.

In the second test case, according to the second rule, you should build both sections on the corresponding ground levels, and since $ k = 3 $ , $ h_1 = 0 $ , and $ h_2 = 2 $ the first rule is also fulfilled.

In the third test case, according to the second rule, you should build the first section on height $ 3 $ and the third section on height $ 2 $ . According to the first rule, the second section should be on the height of at least $ 2 $ (to have a common side with the first section), but according to the third rule, the second section can be built on the height of at most $ h_2 + k - 1 = 1 $ .

## 样例 #1

### 输入

```
3
6 3
0 0 2 5 1 1
2 3
0 2
3 2
3 0 2```

### 输出

```
YES
YES
NO```

# 题解

## 作者：Mars_Dingdang (赞：5)

为了保住岌岌可危的社区贡献分，来水一篇题解（顺便抢到了截止至 2021年1月12日15点48分 的 [最优解](https://www.luogu.com.cn/record/list?pid=CF1469C&orderBy=1&status=&page=1)）。

## 一、题目大意
（好像没有翻译）

你需要用 $n$ 块底边为 $1$，高为 $k$ 的长边相邻长方形覆盖一个区域，第 $i$ 个长方形需要满足：

1. 最低高度为 $h_i$；
2. 相邻两块长方形的边的公共部分至少长为 $1$；
3. 第一块和最后一块长方形的底边高度必须是 $h_1,\ h_n$；
4. 长方形底边可以悬空，但高度不能比 $h_i$ 高出超过 $k-1$。（高度为整数）

求是否有覆盖方式满足上述所有要求。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1469C/639e8b11cbea2061b5e63469ccc4551e6fb009c3.png)

## 二、大体思路
1. 可以抽象为区间覆盖问题，将长方形看作线段，每条线段的左端点 $\ge h_i$，并且不超过左端点 $k-1$，即 $l_i\in [h_i,h_i+k-1]$。 

2. 此外，相邻两条线段要有公共部分，因此左端点可以比前一条线段左端点最小值小 $k-1$，或比前一条线段左端点最大值大 $k-1$，即 $l_i\in [l_{i-1_{\min}}-k+1,l_{i-1_{\max}}+k-1]$。

3. 最后 $l_i$ 取交集，$l_i\in \left[h_i,h_i+k-1\right]\cap\left[l_{i-1_{\min}}-k+1,l_{i-1_{\max}}+k-1\right]$，即 $l_i\in \left[\max(h_i,l_{i-1_{\min}}-k+1),\min(h_i+k-1,l_{i-1_{\max}}+k-1)\right]$。

4. 因此，需要记录每条线段左端点的位置区间 $[l_{i_{\min}},l_{i_{\max}}]$，用 $[L_i,R_i]$ 表示。

5. 再根据【题目大意】第三个要求，$L_1=R_1=h_1$，然后遍历 $2\sim n$，判断 $[L_i,R_i]$ 是否合法，最后再判断 $L_n=h_n$ 即可。

（集合运算好题，理清思路就能看懂了，代码不难）

## 完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cmath>//少用万能头可以加快速度
using namespace std;
#define rep(ii,aa,bb) for(re int ii=aa;ii<=bb;ii++)
#define Rep(ii,aa,bb) for(re int ii=aa;ii>=bb;ii--)
typedef long long ll;
typedef unsigned long long ull;
const int maxn=2e5+5;//个人习惯
namespace IO_ReadWrite{
	#define re register
	#define gg getchar()
	template <typename T>
	inline void read(T &x){
		x=0;re T f=1;re char c=gg;
		while(c>57||c<48){if(c=='-') f=-1;c=gg;}
		while(c>=48&&c<=57){x=(x<<1)+(x<<3)+(c^48);c=gg;}
		x*=f;return;
	}
	template <typename T>
	inline void write(T x){
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar('0'+x%10);
	}
}//卡常快读
using namespace IO_ReadWrite;
ll h[maxn],T,n,k;
int main(){
	read(T);
	while(T--){
		read(n);read(k);
		rep(i,1,n) read(h[i]);//输入
		ll l,r;l=r=h[1];//见 二.5
		bool flag=1;
		rep(i,2,n){
			l=max(h[i],l-k+1);
			r=min(h[i]+k-1,r+k-1);//见 二.3
         //计算左端点的位置区间
			if(l>r || l-h[i]>=k){//不合法
				puts("NO");
				flag=0;
				break;
			}
		}
		if(!flag) continue;
		if(l==h[n]) puts("YES");//见 二.5
		else puts("NO");
	}
	return 0;//完美
}
```
 

---

## 作者：caoshuchen (赞：2)

# [Building a Fence](https://www.luogu.com.cn/blog/caoshuchen/building-a-fence-zhong-zhuai)

## 思路

看到这道题最先想到的一般就是 $dp$，设 $dp_{i,j}$ 表示前 $i$ 个篱笆中，第 $i$ 个篱笆高度为 $j$ 的方案是否可行，这样我们可以进行递推找到最后 $dp_{n,j}$ 是否可行。

${\color{Red} \mathbf{但是这样有一个致命的问题} }$，那就是$\begin{cases}
1\le i \le 2 \times 10^5 \\
0\le j \le 10^8
\end{cases}$ 这就使时间和内存都超限了，于是这个方法被我们排除。

这里，我想到的另一个可行的方法是：

我们发现，每一个篱笆都是一段长度相同的区间，那我们只需要依次**从左往右**递推出每一个篱笆在只考虑前面所有限制的前提下所可以放的下界和上界，然后判断在这个范围内是否存在可以放的地方，只要每一个篱笆都有至少一个地方可以放，那么我们就称这样的情况是成立的，输出`YES`，否则输出`NO`。

然后我们说一下如何递推这个上界和下界。我们先把篱笆$\color{Red} \mathbf{下沿}$的放置下界设为 $l$，上界设为 $r$ 以便说明，接下来我们想递推 $l_i$，$r_i$，那么 $r_i=r_{i-1}+k-1$，$l_i=l_{i-1}-k+1$，这满足了条件 $2$。然后，我们再来考虑一下当前的限制，$r_i$ 最大不可越过 $h_i+k-1$ 也就是要满足条件 $3$，$l_i$ 最小不可越过 $h_i$ 也就是篱笆不能遁土。最终我们会得到以下这样的递推公式：

$$\begin{cases}l_i = \max (h_i, l_{i-1} - k + 1)\\
r_i = \min (h_i + k - 1, r_{i-1} + k - 1)\end{cases}$$

如果说某一次递推后发现 $l_i > r_i$ 那么说明 $i$ 篱笆没有可以放的位置，则输出`NO`。

最终时间复杂度为 $O(n)$，效率极高。

## 细节

注意这样是 ${\color{Red} \mathbf{没有考虑到条件 1}}$ 的，所以我们需要在初始化的时候设 $l_1=r_1=h_1$，最后还要判断：在 $[l_n,\ r_n]$ 的区间中是否包含了 $h_n$，只有所有 $l\le r$ **且这个特判也成立**才能输出`YES`。

## Code

```c++
#include <bits/stdc++.h>
using namespace std;

int t;
int n, k;
int h[200005];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++)
			scanf("%d", h + i);
		int l = h[1], r = h[1];
		bool f = true;
		for (int i = 2; i <= n; i++) {
			l = max(h[i], l - k + 1);
			r = min(h[i] + k - 1, r + k - 1);
			if (r < l) {
				f = false;
				break;
			}
		}
		if (f && l <= h[n] && h[n] <= r)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}

```

---

## 作者：zjjws (赞：2)

本来觉得没什么好写的，毕竟太水了，但是其他五题都写了题解干脆凑个一套。

就当纪念一下第一次好好打 CF，毕竟前几场乱打的只做了 AB。

---

我们可以记录一下每一个木板的 **底部所能放置的范围** $[l,r]$。

很显然因为第一块木板必须着地，所以 $l_1=r_1=h_1$。

然后，我们考虑当前的 $[l_i,r_i]$ 受哪些条件影响。

- $l_i\ge h_i$ 不能塞到地下。

- $l_i< h_i+k$ 题目要求，不能留出大于 $k-1$ 的空隙。

- $l_i+k>l_{i-1}$ 且 $r_i<r_{i-1}+k$ 题目要求两块木板至少要有长度为 $1$ 的重合。

那么只要模拟这个过程，不断维护 $l,r$ 即可。

注意无解的情况：

- $\exists i\in[1,n]\cap \mathbb Z,l_i>r_i$

- $\exists i\in[1,n]\cap \mathbb Z,l_i\ge h_i+k$

- $l_n>h_n$

```cpp
inline void work()
{
    int n=rin();
    LL k=rin();
    for(int i=1;i<=n;i++)h[i]=rin();
    LL l,r;
    l=r=h[1];
    bool if_true=true;
    for(int i=2;i<=n;i++)
    {
        LL l_,r_;
        l_=max(h[i],l+1-k);
        r_=min(h[i]+k-1,r-1+k);
        l=l_;r=r_;
        if(l>r||l-h[i]>=k)if_true=false;
        // printf("i:%d l:%lld r:%lld\n",i,l,r);
    }
    if(if_true&&l==h[n])puts("YES");else puts("NO");
    return;
}
```



---

## 作者：pyyyyyy (赞：1)

> 有$n$个高度为$k$的栅栏，宽都是$1$，地面的高度为$h_i$，栅栏可以放在地面上，也可以浮空(最多浮空高度为$k-1$)，第$1$个和第$n$个栅栏必须在地面上，问能不能使得每个栅栏之间都有边。

看完题之后感觉思路应该是计算出每个栅栏的区间，但是我竟然把每个栅栏能取值(无论合法与否)的区间求出来然后判断了..........

正确思路应该是从第一个区间开始往后退，每一个合法区间的下界和上界。

第一个栅栏最大为$maxn_1=h[1]+k$，最小$minn_1=h[1]$，第二个为$minn_2=max(h[2],minn_1-k+1)$第二项加$1$是因为至少要有长$1$的边，$maxn_2=min(h[2]+2*k-1,maxn_1+k-1)$，第一项是浮空$k-1$，第二项是和上一次最大值只有$1$的边

只需要判断一下中途会不会出现$maxn_i<minn_i$,$maxn-k<h[i]$,$minn>h[i]+k-1$，然后看一下最后一个能不能在地面上即可。

```cpp
const int N = 2e5 + 2020;
int T, n, k, h[N]; 
int main()
{
	T = read();
	while(T--){
		n = read(), k = read();
		for(int i = 1; i <= n; ++i) h[i] = read();
		int maxn = 0, minn = 0;
		int flag = 1;
		for(int i = 1; i <= n; ++i){
			if(i == 1){
				maxn = h[1] + k;
				minn = h[1];
			}
			else {
				minn = max(h[i], minn - k + 1);
				maxn = min(h[i] + 2 * k - 1, maxn + k - 1); 
			}
			if(maxn < minn || minn > h[i] + k - 1 || maxn - k < h[i]){
				flag = 0;
				break;
			}
		}
		if(minn != h[n]) flag = 0;
		if(flag == 0) cout << "NO";
		else cout << "YES";
		puts("");
	}
	return 0;
}
```


---

## 作者：Star_101 (赞：0)

###### **本蒟蒻第一次写题解！~~（纯粹是为了涨咕值~~**
## **题意规则**
**下面 $h_i$ 指 $i$ 处地面高度，$d_i$ 指第 $i$ 个栅栏离地的高度**
$$d_1 = h_1,d_n = h_n$$
$$h_i \leq d_i \leq h_i + k$$
$$d_i - (k - 1) \leq d_{i+1} \leq d_i + (k - 1)$$
若交换其中的 $i$ 和 $i+1$ 也一样
## **解题思路：**
可以看到，每个栅栏可以放的位置只和**它旁边的栅栏**以及**地面的高度**有关。于是考虑从左到右遍历整块地面，分析**每个栅栏能放置的区间**，一旦发现**一个栅栏不可能放在合法的位置就说明无法实现目标**，而如果**所有栅栏都可以合法放置就一定能实现目标**。
## **代码实现：**
下面是本题的核心代码：（每次询问solve一次）
```cpp
ll t,n,k,h[200005],ans,l,r;
void solve()
{
    //读入
	cin>>n>>k;
	for(ll i=1;i<=n;i++)cin>>h[i];
	l=h[1],r=h[1];//l和r表示栅栏能放的区间，初始只能放在h[1]（规则1）
	for(ll i=2;i<=n;i++)
	{
        //规则2和3，栅栏的位置有两个限制条件
		l=max(h[i],l-k+1);//根据上一次的l和r（即其左边的栅栏可能放的位置）更新这次的区间
		r=min(h[i],r)+k-1;
		if(l>r)//无法合法放置栅栏
		{
			cout<<"NO"<<endl;
			return;
		}
	}
	if(l<=h[n]&&r>=h[n])//确保最后一个栅栏可以放在地面（规则1）
        cout<<"YES"<<endl;
	else
        cout<<"NO"<<endl;
	return;
}
```

---

## 作者：LXH5514 (赞：0)

### CF1469C Building a Fence

### 题目大意

翻译已经很简明了，直接[传送门](https://www.luogu.com.cn/problem/CF1469C?contestId=41151)。

### 思路

由条件2可得，每个篱笆都是相邻有接触的，就是说明篱笆的高度会受到相邻的篱笆所影响。

一开始我是想既然是要覆盖，那么肯定越高越好，那么我们就从最边端一点点扩展，就是每次高度都加上 $k-1$，这样肯定高度最大，如果这样都无法覆盖，那么肯定不行，然后由于条件1的限制，因此我就左右都来一遍就好了。

当时忘记了条件3，后来看到了，有上面的思路类比可得，我们就在满足覆盖的条件下，往下扩展，这样也是在为了满足条件3的最优情况。并且往上扩展和往下扩展实际就是求每一块的篱笆可放的范围。

然后由于我们记录了最低点，可以直接判断条件1，那么其实就不用再从另一边再来一遍了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2*1e5+10;
int read()
{
	int f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
int n,k,t;
int a[MAXN];
int h=0;
int b[MAXN],c[MAXN];
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		k=read();
		for(int i=1;i<=n;i++)
		a[i]=read();
		int sum=a[1],num=a[1];
		for(int i=2;i<=n;i++)
		{
			num=max(num-k+1,a[i]);//最低点,向下扩展
            //这里不用考虑 a[i] 比num高无法扩展的情况，因为sum会帮忙处理的。
			sum+=k-1;//最高点，向下扩展
			if(sum<a[i])
			{
				h=1;
				break;//无法覆盖
			}
			if(num>a[i]+k-1)
			{
				h=1;
				break;//不满足条件3
			}
			sum=min(sum,a[i]+k-1);//条件3限制
		}
		if(num>a[n])h=1;//条件1
		if(h==1)
			printf("NO\n");
		else printf("YES\n");
		h=0;//多测清空
	}
	return 0;
}
```



---

