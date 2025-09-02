# Row of Models

## 题目描述

During the final part of fashion show all models come to the stage and stay in one row and fashion designer stays to right to model on the right. During the rehearsal, Izabella noticed, that row isn't nice, but she can't figure out how to fix it.

Like many other creative people, Izabella has a specific sense of beauty. Evaluating beauty of row of models Izabella looks at heights of models. She thinks that row is nice if for each model distance to nearest model with less height (model or fashion designer) to the right of her doesn't exceed $ k $ (distance between adjacent people equals 1, the distance between people with exactly one man between them equals 2, etc).

She wants to make row nice, but fashion designer has his own sense of beauty, so she can at most one time select two models from the row and swap their positions if the left model from this pair is higher than the right model from this pair.

Fashion designer (man to the right of rightmost model) has less height than all models and can't be selected for exchange.

You should tell if it's possible to make at most one exchange in such a way that row becomes nice for Izabella.

## 样例 #1

### 输入

```
5 4
2 3 5 2 5
```

### 输出

```
NO```

## 样例 #2

### 输入

```
5 2
3 6 2 2 1
```

### 输出

```
YES```

## 样例 #3

### 输入

```
5 2
5 3 6 5 2
```

### 输出

```
YES```

# 题解

## 作者：Lynkcat (赞：3)

首先有关键性质，整个序列第一个不合法的位置一定是某个前缀最小值。这个性质很重要，下文称为性质 $1$。

找到第一个不合法的位置 $i$，在这个位置之后找一个位置 $j$ 满足 $a_j< a_i$ 且 $a_j$ 最大。我们将要证明如果存在一种交换方案 $(x,y)$ 使得整个序列合法，那么方案 $(i+k,j)$ 一定也合法。

首先第一件事，若存在 $p>i+k$ 满足 $p$ 不合法，那么一定输出 NO。因为若有这种情况，那么交换的方案可能满足 $p<y\leq y+k$，这种交换必然还是有 $p$ 不合法，而当 $y=p$ 的时候由于 $a_y<a_x$ 必然会令交换之后的 $p$ 之后仍然不合法，因此上述结论得证。

接下来一个关键结论，交换 $(x,y)$ 之后若 $x$ 的位置合法，则其他位置仍然合法。首先对于 $p>y$ 的位置显然仍然合法，那对于 $(x,y)$ 中的位置 $p$，进行讨论。

首先先把 $p$ 的范围限制在 $p+k\geq y$。

若 $a_p>a_y$ 由于有性质 $1$，$a_p$ 在交换之后一定不是前缀最小值，不需要去管。

若 $a_p\leq a_y$ 由于 $a_{i+k}\geq a_i> a_j$ 所以相当于把一个大于等于 $a_p$ 的数换成一个大于等于 $a_p$ 的数，原来合法的话仍然合法。

也就是说其他位置都不用考虑了，如果 $x$ 这个位置能合法容易发现 $a_y$ 越大越好，而位置 $x$ 也是越右边越好。

因此选取 $(i+k,j)$ 一定是最优秀的方案。

剩下需要做的事情就是简单模拟上面这个过程了。很难的题。为啥只有 *2500。

```cpp
#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define sz(x) ((int)((x).size()))
#define int ll
// #define N 
using namespace std;
const int N=500005;
int n,m,a[N];
void BellaKira()
{
    cin>>n>>m;
    for (int i=1;i<=n;i++)
        cin>>a[i];
    int bl=0;
    for (int i=2,j=1;i<=n;i++)
    {
        if (a[i]<a[j])
        {
            j=i;
        } else
        if (i-j>=m)
        {
            if (bl) 
            {
                cout<<"NO\n";
                return;
            }
            int pos=0;
            for (int k=i+1;k<=n;k++)
                if (a[k]>a[pos]&&a[k]<a[j]) pos=k;
            if (!pos)
            {
                cout<<"NO\n";
                return;
            }
            bl=1;
            swap(a[j+m],a[pos]);
            j+=m;
        }
    }
    cout<<"YES\n";
}
signed main()
{
    IOS;
    cin.tie(0);
    int T=1;
    while (T--)
    {
        BellaKira();
    }
}
/*list:
1.mod 998244353 or 1e9+7 or ???
2.N
3.duipai shuju xingtai duoyidian
...
*/
```




---

## 作者：LKY928261 (赞：1)

首先序列合法的条件可以转化为：

$$\forall i\in [1,n-k],\exists j\in [i+1,i+k],a_i>a_j$$

先考虑对于一个固定的序列如何判定其是否合法。

按照 $a_i$ 从小到大的顺序枚举每个数，若在其后面 $k$ 个位置中存在之前加入过的数 $a_j$，那么就将当前的 $a_i$ 也加入，否则序列不合法。若每个数都能依次加入即序列合法。

至于具体如何判定是否存在满足条件的 $a_j$，只需在枚举过程中维护当前所有被加入位置的下标的最小值 $s$，当 $i+k\ge s$ 时一定存在合法的 $j$。

另外由于 $a_i$ 必须严格大于 $a_j$，所以相等的数应该按位置从左到右枚举。

---

接下来考虑在能够交换逆序对时如何判定。

如果在某次枚举中出现了 $i+k<s$ 的情况，那么就只能从后面的序列中找一个比当前 $a_i$ 小的 $a_j$ 换到前面来，使得 $a_i$ 能够跟后面接上，并且拿走 $a_j$ 之后不能让后面的序列断开。

具体有以下两种情况：

1. 记 $t$ 表示已经加入的数中下标的次小值，可以将 $a_s$ 往前挪到 $t-k$ 的位置，此时需要满足 $i+k\ge t-k$，即 $i+2k\ge t$；
2. 若后面的某个 $a_j$ 可以直接取出且不造成影响，那么将它挪到 $s-k$ 的位置，此时需要满足 $i+k\ge s-k$，即 $i+2k\ge s$。

如何判定是否存在某个上述第二种情况的 $a_j$？考虑在我们加入 $a_i$ 的过程中，如果 $i<s$ 且 $i+k\ge t$，那么 $a_s$ 就可以直接拿出来；如果 $i\ge s$，那么 $a_i$ 就可以直接拿出来，此时显然也满足 $i+k\ge t$。综上所述，在尝试加入 $a_i$ 时，只需 $i+k\ge t$，就一定会出现一个可以被取出的 $a_j$，打上标记即可。

由于至多只能进行一次操作，所以在碰到不合法情况并进行交换后直接打个标记，之后再出现不合法的情况那就是整个序列不合法了。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=5e5+5;
ll n,k,x,s,t,a[_],i;pair<ll,ll>b[_];bool f,g;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;s=n;t=1e9;
	for(i=0;i<n;i++)cin>>a[i],b[i]={a[i],i};
	sort(b,b+n);
	for(i=0;i<n;i++){
		x=b[i].second;
		if(x+k<s){
			if(f||(!g&&x+(k<<1)<t)||x+(k<<1)<s)return cout<<"NO\n",0;
			s=x;f=1;
		}
		else{
			if(x+k>=t)g=1;
			if(x<s)t=s,s=x;
		}
	}
	cout<<"YES\n";
}
```

---

## 作者：yyyyxh (赞：1)

这种题怎么只有 2500*……看着难度做自闭了。

这是一道非常好的贪心题，评分低可能只是场上被各种数据结构爆过了。

先从做数据结构题的角度入手：

称满足 $p_i-i>k$ 的元素为坏元素，考虑你交换的那个 $x,y$ 会怎么影响序列的好坏。

对于在 $x$ 左边的所有数，由于小的数更靠近了所以会有一些数从坏变好，对于 $x,y$ 中间的所有元素的状态只有可能变坏，因为一个小的数被换出去了。

$x,y$ 本身的好坏变化似乎不太确定。首先我们发现 $x$ 一定原来是好的，否则 $y$ 一换到这不可能变好。可以考虑枚举一下 $y$ 的好坏性，由于我们想将所有元素变好，所以除了 $y$ 以外所有坏数都在 $x$ 左边。

然后考虑一下什么样的 $x,y$ 可以将所有 $x$ 左边的数变好，这需要满足 $a_y<\min_{i\text{ is bad}\land i<y} a_i,x\leq k+\min_{i\text{ is bad}} i$。

同时还要防止中间的数变坏，所以要对所有 $p_i=y$ 的数求一个次大值一类的东西，剩下关于 $x,y$ 的限制都是一些关于位置与值域的偏序限制，于是就可以用线段树二分疯狂叠不等式。一开始做的时候写了好久这个硬维护做法，后来发现似乎很不可写……

接下来考虑更细致地分析性质：

上面那个数据结构做法很多地方憨了，但是许多分析都是有一定启发性意义的。

比如说枚举 $y$ 的好坏性这一步就很憨，事实上我们最后可以发现 $x,y$ 都是好元素一定更优。为此我们要找到一个比较好的切入点。

切入点就是 $a_y<\min_{i\text{ is bad}\land i<y}$ 这个偏序限制。我们可以发现最小的坏元素具有一些美妙的性质。考虑这样一个过程，从小到大加入 $a_i$ 直到加入第一个坏元素，发现在这个过程种最小值加入时想要变好只能是其坐标 $\geq n-k+1$，继续分析下去，剩下的元素加入时，它能变好的位置一定是一段后缀！第一个不在这个后缀里的元素便是最小的坏元素。

此时我们就可以发现 $y$ 不可能坏了，因为 $a_y$ 比在它前面的最小的坏元素还小，说明它就是最小的坏元素，能够让它变好的元素都在它后面，现在它还往左边挪，怎么可能变好？

我们称比最小的坏元素还小的集合为 $\text{Min}$ 集合。

我们顺水推舟就可以完成最后的分析了。剩下的 $x,y$ 只需要满足的限制是：能让 $x$ 左边的元素变好，能让中间的元素不变坏，$y$ 挪到前面去依然好。

对于第一个限制，我们可以贪心取 $x$ 为 $k+\min_{i\text{ is bad}} i$。容易发现根据我们接下来的一大堆分析，$a_x$ 的值多少已经不重要了。

对于第三个限制，我们贪心取 $y$ 为 $\text{Min}$ 中值最大的任意一个元素。这样更容易在后面找到 $p_i$。

此时我们发现如果一、三限制同时满足，第二个限制一定满足。首先对于在中间的 $\text{Min}$ 集合元素，由于拿走的是 $\text{Min}$ 集合的最大值，一定不影响。对于不是 $\text{Min}$ 集合里的如果它的坐标比我们挖去了最大值后的 $\text{Min}$ 集合中最小的元素减 $k$ 还大肯定能找剩下的 $\text{Min}$ 集合元素，否则它如果找不到了，那么我们挪到前面去的 $a_y$ 比它前还比它小，而到它之前还没有任何的 $\text{Min}$ 集合的元素，只能到它的后面去找，它不是好的那么 $y$ 也不会依然好。

综上结论证完了！其实求出 $x,y$ 之后不用再求一遍 $p_i$，根据上面的讨论我们实际上只用判一下交换后第三个限制是否成立就行了。

```cpp
// wssb
// You can greedy instead of ds!
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int INF=0x3f3f3f3f;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
const int N=500003;
int n,k;
int a[N],p[N];
int stk[N],tp;
int main(){
	n=read();k=read();
	for(int i=1;i<=n;++i) a[i]=read();
	stk[0]=n+1;
	for(int i=n;i;--i){
		while(tp&&a[stk[tp]]>=a[i]) --tp;
		p[i]=stk[tp];
		stk[++tp]=i;
	}
	int cur=INF,mnpos=0,mxpos=0;
	for(int i=1;i<=n;++i)
		if(p[i]-i>k){
			if(!mnpos) mnpos=i;
			mxpos=i;
			cur=min(cur,a[i]);
		}
	if(cur==INF){puts("YES");return 0;}
	int pos=mnpos+k;
	if(pos<=mxpos){puts("NO");return 0;}
	int mx=-INF;
	for(int i=n;i;--i)
		if(a[i]<cur&&a[i]>mx) mx=a[i];
	if(mx<0){puts("NO");return 0;}
	if(pos+k>n){puts("YES");return 0;}
	for(int i=pos+1;i<=pos+k;++i)
		if(a[i]<mx){puts("YES");return 0;}
	puts("NO");
	return 0;
}
```

---

