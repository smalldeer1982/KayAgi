# Dual (Hard Version)

## 题目描述

[Popskyy &amp; tiasu - Dual](https://soundcloud.com/popskyy/popskyy-tiasu-dual)

⠀



The only difference between the two versions of this problem is the constraint on the maximum number of operations. You can make hacks only if all versions of the problem are solved.

You are given an array $ a_1, a_2,\dots, a_n $ of integers (positive, negative or $ 0 $ ). You can perform multiple operations on the array (possibly $ 0 $ operations).

In one operation, you choose $ i, j $ ( $ 1 \leq i, j \leq n $ , they can be equal) and set $ a_i := a_i + a_j $ (i.e., add $ a_j $ to $ a_i $ ).

Make the array non-decreasing (i.e., $ a_i \leq a_{i+1} $ for $ 1 \leq i \leq n-1 $ ) in at most $ 31 $ operations. You do not need to minimize the number of operations.

## 说明/提示

In the first test case, by adding $ a_1 = 2 $ to $ a_2 $ , we get the array $ [2, 3] $ which is non-decreasing.

In the second test case, the array changes as:

- $ [1, 2, -10, 3] $
- $ [1, 2, -10, 6] $
- $ [1, 2, -10, 12] $
- $ [1, 2, 2, 12] $

In the third test case, the final array is $ [2, 3, 3, 3, 3] $ .

## 样例 #1

### 输入

```
10
2
2 1
4
1 2 -10 3
5
2 1 1 1 1
8
0 0 0 0 0 0 0 0
5
1 2 -4 3 -10
10
11 12 13 14 15 -15 -16 -17 -18 -19
7
1 9 3 -4 -3 -2 -1
3
10 9 8
20
1 -14 2 -10 6 -5 10 -13 10 7 -14 19 -5 19 1 18 -16 -7 12 8
20
-15 -17 -13 8 14 -13 10 -4 11 -4 -16 -6 15 -4 -2 7 -9 5 -5 17```

### 输出

```
1
2 1
3
4 4
4 4
3 4
4
2 1
3 1
4 1
5 1
0
7
3 4
3 4
5 4
5 4
5 4
5 4
5 4
15
6 1
6 1
6 1
7 2
7 2
7 2
8 3
8 3
8 3
9 4
9 4
9 4
10 5
10 5
10 5
8
3 4
3 4
2 4
2 4
2 4
2 4
1 4
1 4
3
2 1
3 1
3 1
31
14 1
18 7
13 11
15 11
6 4
5 17
19 6
19 12
10 5
11 12
1 17
15 19
16 10
14 2
16 11
20 7
7 6
9 5
3 6
6 14
17 18
18 14
12 3
17 16
8 18
13 16
9 8
14 8
16 2
11 8
12 7
31
5 12
19 13
9 1
5 17
18 19
6 16
15 8
6 9
15 14
7 10
19 7
17 20
14 4
15 20
4 3
1 8
16 12
16 15
5 6
12 10
11 15
20 3
20 19
13 14
11 14
18 10
7 3
12 17
4 7
13 2
11 13```

# 题解

## 作者：引领天下 (赞：13)

有趣的构造题。

**提示：本题的简单版本对困难版本有一定启发作用，推荐搭配 [A1 的题解](https://www.luogu.com.cn/blog/yltx/cf1854a1-post) 食用。**

题意：

给定一个长度为 $n$ 的序列，现在可以进行以下操作：

- 选择 $i,j$（注意 $i$ 可以等于 $j$），将 $a_i\leftarrow a_i+a_j$。

做法：

我们注意到在做 A1 的 $a_n<0$ 的情况时，我们使用了一个很香的后缀和做法。

这个做法能否扩展呢？

显然是可以的。对于 $a_i$ 全负的情况，做后缀和即满足题意；对 $a_i$ 全正的情况，做前缀和即满足题意。

前缀和 和 后缀和 都需要 $n-1$ 次操作，于是问题就变成了如何在 $12$ 次内使 $a_i$ 全正或全负。

一个很自然的想法是用多的同化少的，即正的 $a_i$ 较多的时候就填平负的 $a_i$，否则填平正的。

以下以正的较多的情况展开讨论：

考虑这个做法什么时候会被卡到极限。

显然是正的 $a_i$ 的最大值（记为 $A$）远小于负的 $a_i$ 的最小值（记为 $B$），极限情况是 $A=1,B=-20$。

这种情况下我们想要让 $A>-B$ 需要 $5$ 次操作，这样一来留给我们填平负的 $a_i$ 的次数就只剩下了 $7$ 次。

那如果有 $8$ 个负数呢？

既然正的填负的超了，我们就考虑反过来负的填正的，这样的操作次数最多正好是 $20-8=12$ 次。

最后总次数刚好卡进 $31$ 次。~~妙的一笔~~

对于 $A$ 更大或者 $B$ 更小的情况，讨论后即可发现正填负和负填正总有一种是正确的，详细的讨论过程与以上类似，这里就不展开了。

而负的 $a_i$ 较多的情况与正的较多的情况极为相似，此处同样不再赘述。

我的代码存在大量重复片段，这里就不贴出来了。

---

题外话：有小天才上来看到 A1，A2 没有思路，于是去开 B ，吃了 5 发罚时，最后 82min 才过 B，然后 17min 切 A1，28min 切 A2。~~我觉得我能吹一年~~

值得一提的是，这个小天才在求 $B$ 的时候是这么写的：

```cpp
if(a[i]>0){
   cnt[0]++;
   if(a[i]>mx)mx=a[i],mxi=i;
}else{
   cnt[1]++;
   if(a[i]<mn)mn=a[i],mni=i;
}
```

然后最小值求了个 0 出来，在 #2 TLE 了一次。

此处提醒大家以我为戒，注意符号，切勿再犯。

---

## 作者：Hisaishi_Kanade (赞：6)

easy version 和 hard version 都说一下。

首先注意到两条结论：

+ 如果 $\forall a_i$，有 $a_{i}\ge0$，则可以用 $(n-1)$ 操作进行前缀和完成。
+ 如果 $\forall a_i$，有 $a_{i}<0$，则可以用 $(n-1)$ 操作进行后缀和完成。

证明显然。第一条 $a_{i}\ge0\to a_{i}+a_{i+1}\ge a_{i+1}$，第二条同理。

所以只要全正或者全负，咱就赢了。

## How to solve Easy Version?

$50$ 次意味着我们可以有 $30$ 次操作使得原序列全正或者全负。

而这种操作是简单的，我们只要选出绝对值最大的 $k$，然后将它加给每一个和他符号相反的。这样所有数的符号都是 $k$ 的符号。这是最多 $n-1$ 次。

然后就是简单的，总共 $n-1+n-1=2n-2$ 次。

## How to solve Hard Version?

上面的构造依然是很优越的。

我们设和 $k$ 相同符号的数总共有 $m$ 个，操作次数为 $p=(n-m)+n-1=2n-m-1$。当 $m\ge 8$ 时，发现 $p\le 31$，赢！

当 $m<8$ 怎么办呢，我们只要让 $m\gets n-m$ 就好了。将与 $k$ 符号相反且绝对值最大的数 $k^\prime$，使其自增绝对值超过 $k$，然后转化为 $m\ge 8$ 的情况。

我们发现，自增是 $\log V$ 的，在此题最大为 $5$，第一种情况最大的操作次数是 $20\times 2-8-1=31$，正好符合要求。第二种情况呢？最大为 $p=7$，此时次数为 $20\times 2-(20-7)-1+5=31$，依然符合要求！

这样就解决了！只放 hard version 的代码了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(i=l;i<=r;++i)
#define req(i,r,l) for(i=r;i>=l;--i)
pair<int,int> ans[55],ans1[55],ans2[55];
int cnt1,cnt2;
int a[55];
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		cnt1=cnt2=0;
		int ct=0;
		int n,i,mx=-(1<<30),mn=1<<30,psx,psn,psnn,mnn=1<<30,pos,psx2,cmx=-(1<<30);
		int cnt=0;
		scanf("%d",&n);
		rep(i,1,n)scanf("%d",a+i);
		rep(i,1,n)if(abs(a[i])>mx)mx=abs(a[i]),psx=i;
		rep(i,1,n)if(abs(a[i])<mx && abs(a[i])>cmx && a[i]*a[psx]<0) cmx=abs(a[i]),psx2=i;
//		printf("%d %d\n",psx2,psx);
		rep(i,1,n)if(a[i]<mn)mn=a[i],psn=i;
		rep(i,1,n)if(a[i]*a[psx]>0)++ct;
		if(ct>=8 || 2*n<=31)
		{
			rep(i,1,n)if(a[i]*a[psx]<0)ans[++cnt]={i,psx},a[i]+=a[psx];
			if(a[psx]>0)rep(i,2,n)ans[++cnt]={i,i-1};
			else req(i,n-1,1)ans[++cnt]={i,i+1};
		}else
		{
			while(abs(a[psx2])<abs(a[psx]))ans[++cnt]={psx2,psx2},a[psx2]+=a[psx2];
			rep(i,1,n)if(a[i]*a[psx2]<0)ans[++cnt]={i,psx2},a[i]+=a[psx2];
			if(a[psx2]>0)rep(i,2,n)ans[++cnt]={i,i-1};
			else req(i,n-1,1)ans[++cnt]={i,i+1};
		}
		printf("%d\n",cnt);
		rep(i,1,cnt)printf("%d %d\n",ans[i].first,ans[i].second);
	}
	return 0;
}
```

赛时代码，非常混乱。

---

## 作者：Wf_yjqd (赞：4)

比较简单的构造题。

------------

考虑若没有负数，直接让 $a_i$ 加上 $a_{i-1}$，求一个前缀和。

显然可以保证 $a_i\ge a_{i-1}(2\le i\le n)$。

没有负数则求后缀和，同理。

转换问题变成在 $32-n$ 次操作内消除所有负数或者正数。

考虑选一个非 $0$ 数 $a_i$ 倍增 $5$ 次后一定满足 $\left| a_i\right|>\left|a_j\right|(1\le j\le n,i\ne j)$。

则将所有符号与 $a_i$ 相反的数加上 $a_i$ 即可。

以上为 C1 做法，容易发现在正数个数或负数个数 $\le7$ 时可行。

考虑不可行的情况下，$8\le$ 正数，负数个数 $\le12$。

那我们只需要直接用当前绝对值最大的数消去所有符号相反的数，最大次数为 $31$。

------------

可以看看代码。

注意特判全 $0$ 情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[23],bun[23];
inline bool check(int *x){
    for(int i=1;i<n;i++)
        if(x[i]>x[i+1])
            return 0;
    return 1;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            bun[i]=a[i];
        }
        if(check(a)){
            puts("0");
            continue;
        }
        int maxx=-168,minn=168,maxid,minid,cntf=0,cntz=0,cnt0=0;
        for(int i=1;i<=n;i++){
            cntf+=(a[i]<0);
            cntz+=(a[i]>0);
            cnt0+=(a[i]==0);
            if(a[i]>maxx){
                maxx=a[i];
                maxid=i;
            }
            if(a[i]<minn){
                minn=a[i];
                minid=i;
            }
        }
        if(!cntf){
            for(int i=1;i<=n;i++)
                if(!bun[i])
                    bun[i]+=a[maxid];
            if(check(bun)){
                printf("%d\n",cnt0);
                for(int i=1;i<=n;i++)
                    if(!a[i])
                        printf("%d %d\n",i,maxid);
                continue;
            }
        }
        if(!cntz){
            for(int i=1;i<=n;i++)
                if(!bun[i])
                    bun[i]+=a[minid];
            if(check(bun)){
                printf("%d\n",cnt0);
                for(int i=1;i<=n;i++)
                    if(!a[i])
                        printf("%d %d\n",i,minid);
                continue;
            }
        }
        if(!cntf&&cnt0+n-1<=31){
            printf("%d\n",cnt0+n-1);
            for(int i=1;i<=n;i++)
                if(!a[i])
                    printf("%d %d\n",i,maxid);
            for(int i=2;i<=n;i++)
                printf("%d %d\n",i,i-1);
        }
        else if(!cntz&&cnt0+n-1<=31){
            printf("%d\n",cnt0+n-1);
            for(int i=1;i<=n;i++)
                if(!a[i])
                    printf("%d %d\n",i,minid);
            for(int i=n-1;i>=1;i--)
                printf("%d %d\n",i,i+1);
        }
        else if(cntf+n+4<=31){
            printf("%d\n",cntf+n+4);
            for(int i=1;i<=5;i++)
                printf("%d %d\n",maxid,maxid);
            for(int i=1;i<=n;i++)
                if(a[i]<0)
                    printf("%d %d\n",i,maxid);
            for(int i=2;i<=n;i++)
                printf("%d %d\n",i,i-1);
        }
        else if(cntz+n+4<=31){
            printf("%d\n",cntz+n+4);
            for(int i=1;i<=5;i++)
                printf("%d %d\n",minid,minid);
            for(int i=1;i<=n;i++)
                if(a[i]>0)
                    printf("%d %d\n",i,minid);
            for(int i=n-1;i>=1;i--)
                printf("%d %d\n",i,i+1);
        }
        else if(abs(maxx)>=abs(minn)){
            printf("%d\n",cntf+n-1);
            for(int i=1;i<=n;i++)
                if(a[i]<0)
                    printf("%d %d\n",i,maxid);
            for(int i=2;i<=n;i++)
                printf("%d %d\n",i,i-1);
        }
        else{
            printf("%d\n",cntz+n-1);
            for(int i=1;i<=n;i++)
                if(a[i]>0)
                    printf("%d %d\n",i,minid);
            for(int i=n-1;i>=1;i--)
                printf("%d %d\n",i,i+1);
        }
    }
    return 0;
}
```


---

## 作者：信息向阳花木 (赞：3)

这道题在 [C1](https://www.luogu.com.cn/problem/CF1854A1) 的基础上将答案的范围缩小到了 $31$ 次，这就似乎很困难了。前（后）缀和最多要 $19$ 步，也就是说我们要用最多 $12$ 步来让 $a$ 变得全非负或全非正。要求变得“苛刻”，我们需要用最优的方案来解决问题。

~~由于我太弱了，C2 赛时没调完，诶。~~

~~蒟蒻 C1 的 [题解](https://www.luogu.com.cn/blog/314625/solution-cf1854a1)，真的尽力了，自认为对这题有帮助。~~



C1 的做法是将 $a$ 序列变得全非负或全非正。那么究竟是将 $a$ 变得全非负还是全非正呢？假如我们靠 $a$ 中绝对值最大的数 $x$ 的正负性来判断，显然是不合理的。例如，$n = 4$ 时，$a = \{4, 6, -8, 7\}$，我们不应该让所有数都加上 $-8$，让 $a$ 全为负数 ，这样要用 $3$ 步；我们可以让 $7$ 加上它本身变成 $14$，在让 $-8$ 加上 $14$，将 $a$ 全变为正数，只用 $2$ 步。所以，想要卡进 $31$ 步的限制，我们需要考虑转换 $a$ 的两种方式，谁更优，

通过上面的情况，我们已经可以发现正解：记录负数绝对值最大的数 $x$ 和正数绝对值最大的数 $y$。我们将 $a$ 转换为全非负 **和** 全非正，选取最优。$x$、$y$ 中有一个数的绝对值可能不是最大的，我们需要将其倍增至最大，然后再进行类似 C1 的操作。


------------

接下来是证明这种做法一定能在 $31$ 步以内让 $a$ 非递减。

设 $x1$，$x2$ 分别表示将 $x$ 倍增的次数和将一些数加上 $x$ 使得 $a$ 序列全非正的最少步数。$y1$，$y2$ 同理（$y2$ 表示的是全非负的最小步数）。

显然，对于 $x2$ 和 $y2$，我们只需要将正负性和 $x$ 或 $y$ 不同的数进行操作即可。换句人话说，$x2$ 等于 $a$ 中正数的个数，$y2$ 等于 $a$ 中负数的个数。显然，$x2 + y2 \le n \le 20$。再看 $x1$ 和 $y1$，想到 $x$，$y$ 中只有一个数需要倍增。也就是说，$x1$ 和 $y1$ 中，一个数为 $0$，另一个数不会超过 $5$。（倍增 $5$ 次即可到 $32$）所以 $x1+y1 \le 5$。

这样，两个不等式左边加左边小于等于右边加右边，即 $x1 + x2 + y1 + y2 \le 25$，又 $x1$，$x2$，$y1$，$y2$ 都为整数，所以 $\min\{x1+x2,y1+y2\} \le 12$，正好卡进限制。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 50;

inline void in(int &x)
{
	x = 0; bool f = 0; char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	x = f ? -x : x;
}

inline void out(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x / 10) out(x / 10);
	putchar((x % 10) | 48);
}

typedef pair<int, int> PII;

int n, t, maxx;
int a[N], k[2];
vector<PII> ans;

bool get_res(int flag)
{
	if(!k[flag]) return 0;
	
	ans.clear();
	
	int t = a[k[flag]];
	while (abs(t) < maxx)
	{
		ans.push_back({k[flag], k[flag]});
		t *= 2;
	} //倍增至绝对值最大
	for (int i = 1; i <= n; i ++ )
	{
		if(!flag && a[i] <= 0) continue;
		if(flag && a[i] >= 0) continue;
		ans.push_back({i, k[flag]});
	}
	if(!flag) for (int i = n; i > 1; i -- ) ans.push_back({i - 1, i});
	else for (int i = 1; i < n; i ++ ) ans.push_back({i + 1, i});
	
	return (ans.size() < 32); //判断是否在 31 步内
}

int main()
{
	in(t);
	while (t -- )
	{
		in(n);
		
		k[0] = k[1] = 0; maxx = 0;
		for (int i = 1; i <= n; i ++ )
		{
			in(a[i]);
			if(a[i] < 0 && abs(a[i]) > abs(a[k[0]])) k[0] = i;
			if(a[i] > 0 && a[i] > a[k[1]]) k[1] = i;
			maxx = max(maxx, max(abs(a[k[0]]), abs(a[k[1]]))); //所有数中绝对值最大
		}
		if(maxx == 0) puts("0");
		else if(get_res(0)) //将 a 变为全部非正
		{
			printf("%d\n", ans.size());
			for (int i = 0; i < ans.size(); i ++ )
			{
				printf("%d %d\n", ans[i].first, ans[i].second);
			}
			continue;
		}
		else if(get_res(1)) //将 a 变为全部非负
		{
			printf("%d\n", ans.size());
			for (int i = 0; i < ans.size(); i ++ )
			{
				printf("%d %d\n", ans[i].first, ans[i].second);
			}
		}
	}
	return 0;
}

```

语文不好，废话较多，请大佬轻喷	QwQ

---

## 作者：liujy_ (赞：3)

首先一个很显然的结论，如果序列全是非负数或全是非正数我们可以通过 $n-1$ 次操作进行前缀或后缀和使得序列满足条件。这一步我们最多花费掉 $19$ 步，也就是说我们还有 $12$ 步可以用来使得序列没有负数或没有正数。  
以把所有数变成非负数为例。我们可以先找到一个绝对值最大的非负数，用 $x_1$ 步把它变成一个绝对值大于任意一个序列中的负数的绝对值的数。因为 $a_i\le 20$ 易证明 $x_1\le 5$。假设有 $x_2$ 个负数，我们把这 $x_2$ 个负数分别加上创造出来的这个绝对值最大的正数就可以使序列变为非负序列。同理我们可以在 $y_1+y_2$ 步内把序列变为一个非正数序列。  
接下来我们证明上述两种方案取步数较小的一定是满足条件的。   
显然 $x_2+y_2\le n$，也就是说 $x_2+y_2\le 20$。然后 $x_1$ 和 $y_1$ 中必然有一个是 $0$，因为无论正数还是负数整个序列中必然存在绝对值最大的那个数，此时不需要额外的操作把它变大。所以 $x_1+y_1\le 5$。也就是说 $x_1+x_2+y_1+y_2\le 25$。那么显然 $\min(x_1+x_2,y_1+y_2)\le \left\lfloor\dfrac{x_1+x_2+y_1+y_2}{2}\right\rfloor=\left\lfloor\dfrac{25}{2}\right\rfloor=12$。   
具体代码实现可以直接把两种方案都试一遍取步数较小的。  
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=2e5+5;
int t,n,a[N];
int tot1,tot2;
struct node{
	int i,j;
}ans1[N],ans2[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);int mx=0,mn=0,id=0;tot1=0,tot2=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),mx=max(mx,a[i]),mn=min(mn,a[i]);
		int tmp=mx;
		if(mx==0)tot1=N;
		else {
			for(int i=1;i<=n;i++)if(a[i]==mx)id=i;
			while(abs(mx)<abs(mn))mx=mx+mx,ans1[++tot1]={id,id};
			for(int i=1;i<=n;i++)
				if(a[i]<0)ans1[++tot1]={i,id};
			for(int i=2;i<=n;i++)ans1[++tot1]={i,i-1};
		}
		mx=tmp;
		if(mn==0)tot2=N;
		else {
			for(int i=1;i<=n;i++)if(a[i]==mn)id=i;
			while(abs(mn)<abs(mx))mn=mn+mn,ans2[++tot2]={id,id};
			for(int i=1;i<=n;i++)
				if(a[i]>0)ans2[++tot2]={i,id};
			for(int i=n-1;i>=1;i--)ans2[++tot2]={i,i+1};
		}
		if(tot1==N&&tot2==N)printf("0\n");
		else {
			if(tot1<tot2){
				printf("%d\n",tot1)
				for(int i=1;i<=tot1;i++)printf("%d %d\n",ans1[i].i,ans1[i].j);
			}else {
				printf("%d\n",tot2);
				for(int i=1;i<=tot2;i++)printf("%d %d\n",ans2[i].i,ans2[i].j);
			}
		}
	}
	return 0;
}

```


---

## 作者：_Only_this (赞：2)

### CF1854A2 Dual (Hard Version) 题解

------------

C1 都过了，C2 赛时竟没写出来，还是自己太废了。

------------

如果序列本来就有序，直接输出 $0$。

如果全是正数，直接模拟前缀和。

如果全是负数，模拟后缀和。

然后就只剩既有正数也有负数这种情况了，考虑分情况讨论。

当正、负数数量的较小值 $\leq 7$ 时，将数量多的那种数的一个值倍增 $5$ 次，使其一定大于所有数的绝对值。

然后将相反符号的数全都加上这个倍增过的数，使得序列中都是正数或都是负数，最后再模拟前缀和或后缀和即可。

当正、负数数量的较小值 $>7$ 时，必然可以得出 $8\leq$ 正数、负数数量 $\leq 12$。

求出序列中所有数绝对值的最大值，再将其相反的数都加上它，使整个序列全是正数或全是负数，最后再模拟前缀和或后缀和即可。

在极限情况下，最大操作次数为 $5+7+19$ 或 $12+19$，都刚好等于 $31$，此题结束。

代码有些繁琐，凑合着看吧。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e1+5;
int T,n;
int a[maxn];
inline bool Check(){
	for(int i=2;i<=n;i++){
		if(a[i]<a[i-1]){
			return 0;
		}
	}
	return 1;
}
inline bool Check1(){
	for(int i=1;i<=n;i++){
		if(a[i]<0){
			return 0;
		}
	}
	return 1;
}
inline bool Check2(){
	for(int i=1;i<=n;i++){
		if(a[i]>0){
			return 0;
		}
	}
	return 1;
}
inline void Solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	if(Check()){
		printf("%d\n",0);
		return ;
	}
	if(Check1()){
		printf("%d\n",n-1);
		for(int i=2;i<=n;i++){
			printf("%d %d\n",i,i-1);
		}
		return ;
	}
	if(Check2()){
		printf("%d\n",n-1);
		for(int i=n-1;i>=1;i--){
			printf("%d %d\n",i,i+1);
		}
		return ;
	}
	int tot1=0,tot2=0;
	for(int i=1;i<=n;i++){
		tot1+=(a[i]>0),tot2+=(a[i]<0);
	}
	vector<pair<int,int> >A;
	if(min(tot1,tot2)>7){
		int maxx=-111,pos;
		for(int i=1;i<=n;i++){
			if(maxx<abs(a[i]))
				maxx=abs(a[i]),pos=i;
		}
		if(a[pos]>0){
			for(int i=1;i<=n;i++){
				if(a[i]<0){
					a[i]+=a[pos];
					A.push_back({i,pos});
				}
			}
			for(int i=2;i<=n;i++){
				A.push_back({i,i-1});
			}
		}
		else{
			for(int i=1;i<=n;i++){
				if(a[i]>0){
					a[i]+=a[pos];
					A.push_back({i,pos});
				}
			}
			for(int i=n-1;i>=1;i--){
				A.push_back({i,i+1});
			}
		}
		printf("%d\n",A.size());
		for(auto it: A){
			printf("%d %d\n",it.first,it.second);
		}
		return ;
	}
	if(tot1>tot2){
		int loc;
		for(int i=1;i<=n;i++){
			if(a[i]>0){
				loc=i;
				break;
			}
		}
		a[loc]*=1<<5;
		for(int i=1;i<=5;i++){
			A.push_back({loc,loc});
		}
		for(int i=1;i<=n;i++){
			if(a[i]<0){
				a[i]+=a[loc];
				A.push_back({i,loc});
			}
		}
		for(int i=2;i<=n;i++){
			A.push_back({i,i-1});
		}
	}
	else{
		int loc;
		for(int i=1;i<=n;i++){
			if(a[i]<0){
				loc=i;
				break;
			}
		}
		a[loc]*=1<<5;
		for(int i=1;i<=5;i++){
			A.push_back({loc,loc});
		}
		for(int i=1;i<=n;i++){
			if(a[i]>0){
				a[i]+=a[loc];
				A.push_back({i,loc});
			}
		}
		for(int i=n-1;i>=1;i--){
			A.push_back({i,i+1});
		}
	}
	printf("%d\n",A.size());
	for(auto it: A){
		printf("%d %d\n",it.first,it.second);
	}
	return ;
}
int main(){
	scanf("%d",&T);
	while(T--){
		Solve();
	}
	return 0;
}
```


---

## 作者：sz_jinzikai (赞：1)

[洛谷传送门](/problem/CF1854A2) & [CF 传送门](//codeforces.com/problemset/problem/1854/A2)
# 思路
这题是 [C1](/problem/CF1854A1) 的增强版，可以先看看 [C1 的题解](/blog/jzk/solution-cf1854a1)，可以帮助理解这题。

显然，这题要在 C1 的基础上进行优化，我们需要优化把所有数变成非负数这部分。谁说一定要变成非负数了？非正数也可以呀！这样，我们在变成非正数和非负数的步骤数中间取个最小值即可。
# 代码
```cpp
//CF1854A2
# include <bits/stdc++.h> //万能头 
using namespace std;
typedef pair <int, int> pii; //缩写
int t, n, a[25], maxi, mini, x;

bool f;

vector <pii> v;
int main () {
	cin >> t;
	while (t --) { //多组数据通用写法
		mini = maxi = 0; //多组数据要重置
		cin >> n;
		for (int i = 1; i <= n; ++ i) {
			cin >> a[i];
			if (a[i] > a[maxi])
				maxi = i;
			if (a[i] < a[mini])
				mini = i;
		}
		if (a[mini] >= 0) { //全是非负数
			cout << n - 1 << '\n';
			for (int i = 1; i < n; ++ i)
				cout << i + 1 << ' ' << i << '\n';
			continue ;
		}
		if (a[maxi] <= 0) { //全是非正数
			cout << n - 1 << '\n';
			for (int i = n; -- i;)
				cout << i << ' ' << i + 1 << '\n';
			continue ;
		}
		v.clear ();
		x = a[maxi]; //记录下来，用于回溯
		while (a[maxi] < -a[mini])
			v.push_back ({maxi, maxi}), a[maxi] <<= 1; //倍增
		for (int i = 1; i <= n; ++ i)
			if (a[i] < 0) //负数，都要改成非负数
				v.push_back ({i, maxi});
		for (int i = 1; i < n; ++ i)
			v.push_back ({i + 1, i});
		if (v.size () < 32) { //合法
			cout << v.size () << '\n';
			for (pii i : v)
				cout << i.first << ' ' << i.second << '\n'; //输出方案
			continue ;
		}
		a[maxi] = x; //回溯
		v.clear (); //全变非正数，同理
		while (-a[mini] < a[maxi])
			v.push_back ({mini, mini}), a[mini] *= 2;
		for (int i = 1; i <= n; ++ i)
			if (a[i] > 0)
				v.push_back ({i, mini});
		for (int i = n; -- i;)
			v.push_back ({i, i + 1});
		cout << v.size () << '\n';
		for (pii i : v)
			cout << i.first << ' ' << i.second << '\n';
	}
	return 0; //结束程序
}
```

---

## 作者：rabbitohh (赞：0)

看此文章前请看：[CF1854A1 题解](https://www.luogu.com.cn/blog/zhangjianxi/solution-cf1854a1)  
我们现在的操作次数变为了 $31$，如果我们延续刚才前/后缀和的思路，那我们需要在 $12$ 次以内的操作将序列变为全非正或全非负。  
设序列中正整数有 $A$ 个，负整数有 $B$ 个，最小值为 $x$，最大值为 $y$。若 $x\le0$ 或 $y\ge0$ 直接前/后缀和即可。所以接下来我们讨论 $x<0$ 且 $y>0$ 的情况。  
如果我们想将序列变为全非正，那么先不断地将序列中的最小值 $x$ 加到自身，直到 $\lvert x \rvert>\lvert y\rvert$。然后将所有正元素加上 $x$ 即可。需要的操作次数为 $\lceil \log_2 \lceil \frac{\lvert y\rvert}{\lvert x \rvert} \rceil \rceil+A$。  
同理，将序列变为全非负需要的操作次数为 $\lceil \log_2 \lceil \frac{\lvert x \rvert}{\lvert y\rvert} \rceil \rceil+B$。  
注意到，$\lceil \log_2 \lceil \frac{\lvert y\rvert}{\lvert x \rvert} \rceil \rceil$ 与 $\lceil \log_2 \lceil \frac{\lvert x \rvert}{\lvert y\rvert} \rceil \rceil$ 两项必定有一项是 $0$，而另外一项在最坏情况下是 $5$。同时，在最坏情况下，序列中没有 $0$，此时 $A+B=20$。  
在最坏情况下，我们在将序列变为全非正/全非负两种操作中选择较优的一种，次数为 $\operatorname{min}(0+x,5+20-x)$。
![](https://cdn.luogu.com.cn/upload/image_hosting/3oo5pivp.png)  
画出图像后我们发现该函数在整数域上最大值恰好是 $12$，证明了该方法是正确的。  
Code:
```cpp
#include<unordered_map>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<queue>
#include<map>
#include<set>
#define int long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5;
int a[N],b[N];
int cti[N],ctj[N],idx=0;
void add(int j,int i)
{
    cti[++idx]=i;
    ctj[idx]=j;
}

void ans()
{
    idx=0;
    int n;
    cin>>n;
    int pid=0;
    int nid=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]>0)
        {
            if(!pid) pid=i;
            if(a[i]>a[pid]) pid=i;
        }
        if(a[i]<0)
        {
            if(!nid) nid=i;
            if(a[i]<a[nid]) nid=i;
        }
    }
    {//尝试变成全非正
        idx=0;
        for(int i=1;i<=n;i++)
        {
            b[i]=a[i];
        }
        while(-b[nid]<b[pid])
        {
            b[nid]*=2;
            add(nid,nid);
        }
        for(int i=1;i<=n;i++)
        {
            if(a[i]>0) add(nid,i);
        }
        for(int i=n-1;i>=1;i--)
        {
            add(i+1,i);
        }
        if(idx<=31)
        {
            cout<<idx<<'\n';
            for(int i=1;i<=idx;i++)
            {
                cout<<cti[i]<<' '<<ctj[i]<<'\n';
            }
            return;
        }
    }
    {//尝试变成全非负
        idx=0;
        for(int i=1;i<=n;i++)
        {
            b[i]=a[i];
        }
        while(b[pid]<-b[nid])
        {
            b[pid]*=2;
            add(pid,pid);
        }
        for(int i=1;i<=n;i++)
        {
            if(a[i]<0) add(pid,i);
        }
        for(int i=1;i<=n-1;i++)
        {
            add(i,i+1);
        }
        if(idx<=31)
        {
            cout<<idx<<'\n';
            for(int i=1;i<=idx;i++)
            {
                cout<<cti[i]<<' '<<ctj[i]<<'\n';
            }
            return;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        ans();
    }
    return 0;
}

```



---

