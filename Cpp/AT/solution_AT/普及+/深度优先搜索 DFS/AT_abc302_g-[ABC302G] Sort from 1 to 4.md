# [ABC302G] Sort from 1 to 4

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc302/tasks/abc302_g

全ての要素が $ 1 $ 以上 $ 4 $ 以下の整数である、長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。

高橋君は次の操作を何回でも ($ 0 $ 回でも良い) 繰り返し行う事ができます。

- $ 1\leq\ i\ <\ j\leq\ N $ をみたす整数の組 $ (i,j) $ を選び、$ A_i $ と $ A_j $ を交換する。
 
数列 $ A $ を広義単調増加にするために必要な操作回数の最小値を求めてください。  
 ただし、数列 $ A $ が広義単調増加であるとは、$ 1\leq\ i\leq\ N-1 $ をみたすすべての整数について $ A_i\leq\ A_{i+1} $ が成り立つことをさします。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 4 $
- 入力はすべて整数
 
### Sample Explanation 1

次のようにして $ 3 $ 回の操作で $ A $ を広義単調増加にすることができます。 - $ (i,j)=(2,3) $ を選び、$ A_2 $ と $ A_3 $ を交換する。$ A=(3,1,4,1,2,4) $ となる。 - $ (i,j)=(1,4) $ を選び、$ A_1 $ と $ A_4 $ を交換する。$ A=(1,1,4,3,2,4) $ となる。 - $ (i,j)=(3,5) $ を選び、$ A_3 $ と $ A_5 $ を交換する。$ A=(1,1,2,3,4,4) $ となる。 $ 2 $ 回以下の操作で $ A $ を広義単調増加にすることはできないため、このとき操作回数が最小となります。 よって、$ 3 $ を出力します。

## 样例 #1

### 输入

```
6
3 4 1 1 2 4```

### 输出

```
3```

## 样例 #2

### 输入

```
4
2 3 4 1```

### 输出

```
3```

# 题解

## 作者：Ratio_Y (赞：15)

模拟赛里当签到题切的，居然是 ABC 的 G 题。


---

## 思路

读入时记录每个元素的初始下标，之后按元素大小排序，找到**每个元素排序前的下标对应的排序后元素的值**记录个数，共 $16$ 种情况。形象化后，我们就找到了**每种数占一种数的个数**。

对于如何找到最小次数，我们发现，可以将它们占对方位置的行为看作一条有向边，互相占领的情况即形成了环。对于一个混乱的大小为 $n$ 的环，将它恢复成有序需要 $n-1$ 次交换操作，因此在得到上面的数据后，我们便可以通过找环来求解答案。

首先大小为 $2$ 的环很容易找到，枚举 $6$ 次找到 $f_{i,j}$ 与 $f_{j,i}$ 中的较小值即可。剩下环的大小均为 $3$ 或 $4$，但简单手模就能发现，**四种大小为 $3$ 的环不可能同时存在**，因为若同时存在，我们完全可以将它们重组成大小为 $2$ 和 $4$ 的环，而大小为 $2$ 的环已经被找净了，所以不存在上述情况。这样一来，剩余环的数量即为**剩下最多种类的数的数量**，它存在于余下的所有环内。

## 实现

一些可能不易理解的操作标注了注释。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int Ratio=0;
const int N=2e5+5;
int n,ans;
int num[5],to[5][5];
struct rmm{int x,id;}a[N];
bool cmp(rmm a,rmm b){return a.x<b.x;}

namespace Wisadel
{
    short main()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i].x),a[i].id=i,num[a[i].x]++;
        sort(a+1,a+1+n,cmp);
        // 按元素大小排序
        for(int i=1;i<=n;i++)
            if(a[i].id>=1&&a[i].id<=num[1]) to[a[i].x][1]++;
            else if(a[i].id>=num[1]+1&&a[i].id<=num[1]+num[2]) to[a[i].x][2]++;
            else if(a[i].id>=num[1]+num[2]+1&&a[i].id<=num[1]+num[2]+num[3]) to[a[i].x][3]++;
            else if(a[i].id>=num[1]+num[2]+num[3]+1) to[a[i].x][4]++;
        // 找到所占位置元素值，即连边
        for(int i=1;i<=4;i++) for(int j=i+1;j<=4;j++)
        {
            int sum=min(to[i][j],to[j][i]);
            ans+=sum,to[i][j]-=sum,to[j][i]-=sum;
        }// 找大小为 2 的环，直接交换
        int sum=0;
        for(int i=1;i<=4;i++)
        {
            int tot=0;
            for(int j=1;j<=4;j++)
                if(i!=j&&to[i][j]>0)
                    tot+=to[i][j];
            ans+=tot,sum=max(sum,tot);
            // 找环的数量
        }
        // 操作的最少次数即为 当前混乱的数的个数-环的数量
        printf("%d\n",ans-sum);
        return Ratio;
    }
}
int main(){return Wisadel::main();}
```



---

完结撒花~

---

## 作者：zhengchenxi414 (赞：9)

## Decription

给定一个长度为n的数组，仅包含  $1∼4$ 。每次可以交换任意两个数。问至少要交换多少次才能使  a  变成单调不降序列。

## Solution

看到这种交换，我们就可以考虑判环，但我的解法并不是直接判环。

---


首先我们肯定要把区间划分成四个部分，
同时记录每个部分的含有每个数的个数。那接着，我们先把能两两配对的直接交换，然后让所有的   $4$ 归位，再进行两两配对，再让所有的 $3$ 归位，再进行两两配对，如此就可以完成此题。


---


这种做法本质是相当于判环的，但是操作却不太一样，它先把三个或四个连成的环拆开，再进行的两两判环。
我感觉这种可能比较好想也比较好写。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=3e5+107;
int n,a[N],num[5];
int ans;
struct lmy
{
	int cnt[5];
	int l,r;
}s[5];
void f()
{
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=4;j++)
		{
			if(i==j) continue;
			if(s[i].cnt[j]&&s[j].cnt[i])
			{
				int x=min(s[i].cnt[j],s[j].cnt[i]);
				ans+=x;
				s[i].cnt[j]-=x; s[j].cnt[i]-=x;
				s[i].cnt[i]+=x; s[j].cnt[j]+=x;
			}
		}
	}
}
void g(int x)
{
	for(int i=1;i<=4;i++)
	{
		if(i==x) continue;
		if(s[i].cnt[x]) 
		{
			int k=0;
			s[x].cnt[x]+=s[i].cnt[x];
			ans+=s[i].cnt[x];
			for(int j=1;j<=4;j++)
			{
				if(j==x) continue;
				if(s[x].cnt[j]&&k<s[i].cnt[x])
				{
					if(s[x].cnt[j]+k<=s[i].cnt[x])
					{
						s[i].cnt[j]+=s[x].cnt[j];
						s[x].cnt[j]=0;
					}
					else 
					{
						s[i].cnt[j]+=s[i].cnt[x]-k;
						s[x].cnt[j]-=s[i].cnt[x]-k;
					}
					k+=s[x].cnt[j];
				}
			}
			s[i].cnt[x]=0;
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),num[a[i]]++;
	
	s[1].l=1; s[1].r=num[1];
	s[2].l=s[1].r+1; s[2].r=s[2].l+num[2]-1;
	s[3].l=s[2].r+1; s[3].r=s[3].l+num[3]-1;
	s[4].l=s[3].r+1; s[4].r=n;
	for(int i=1;i<=4;i++)
	{
		for(int j=s[i].l;j<=s[i].r;j++)
		{
			s[i].cnt[a[j]]++;
		}
	}
	
	f(); g(4); f(); g(3); f();
	cout<<ans<<"\n";
}

```

---

## 作者：chlchl (赞：8)


赛后秒过。。。。
## 题意
给定一个长度为 $n$ 的数组，仅包含 $1\sim 4$。每次可以交换任意两个数。问至少要交换多少次才能使 $a$ 变成单调不降序列。

## Solution
看到这种交换的，应该想到往逆序对那个方面想。

按照这个思路，我们应该先求出最后的序列形态，所以先排个序。

然后我们发现一些性质：如果排序完后的某个位置 $i$，放的是 $x$，但现在是 $y$；又有某个位置 $j$，放的是 $y$，但现在是 $x$，那我们直接交换一次 $i,j$ 即可。

这种方法的效率一定是最高的，会有 $\frac{2}{1}$ 的效率。

所以我们令 $cnt_{i,j}$ 为表示 $i$ 的最终所在位置上 $j$ 的个数。

刚刚我们讨论了两个数的情况。现在讨论三个数。

如果排序完后的某个位置 $i$，放的是 $x$，但现在是 $y$；又有某个位置 $j$，放的是 $y$，但现在是 $z$；还有某个位置 $k$，放的是 $z$，但现在是 $x$；那我们就要交换两次使得三个数都归位。

这样的效率是次高的，为 $\frac{3}{2}$。

最后就剩下四个位置的情况，效率最低，为 $\frac{4}{3}$。

不可能出现更多元了，因为你只有四个不同的数。

跑个循环处理二元、三元的情况，剩下的所有必定是四元，直接加到答案里即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, tot, a[N], b[N];
int cnt[6][6]; 

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b + 1, b + 1 + n);
	for(int i=1;i<=n;i++)
		if(b[i] != a[i])
			++tot, cnt[b[i]][a[i]]++;
	int ans = 0;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(i == j)
				continue;
			while(cnt[i][j] && cnt[j][i])
				++ans, tot -= 2, --cnt[i][j], --cnt[j][i];
		}
	}
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			for(int k=1;k<=4;k++){
				if(i == j || j == k || i == k)
					continue;
				while(cnt[i][j] && cnt[j][k] && cnt[k][i])
					ans += 2, tot -= 3, --cnt[i][j], --cnt[j][k], --cnt[k][i];
			}
		}
	}
	printf("%d\n", ans + tot / 4 * 3);
	return 0;
}
```

---

## 作者：崔化博 (赞：5)

## 题目大意
给你一个序列，定义一次操作为交换任意两个元素，问最少几次操作使得序列变成单调不降，其中**值域为 1~4**
## 思路
我的思路有点奇怪。

一眼看去好像可以先把随便一个 1 先交换到最前面，其次是 2,3,4。然后看一下样例二是对的，然而样例一是错的。

样例一发现有两个 1 可以交换到第一个位置，然而我们随机选了一个，实际上是要把第二个 1 换过来，因为 3 正好换到单调不降后它应该在的位置，就节省了操作。

于是大致思路就出来了，对于每个位置，先优先找**当前位置上的数**应当在的**位置范围**内，如果有**当前位置应当有的数**的话，就优先换过来，否则我们默认换第一个。这个东西直接用一个 set 维护即可。

时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$

我的代码可能实现的并不好，可以自己实现一下试试。
```cpp
#include <bits/stdc++.h>
#define N 500005
#define ll long long
using namespace std;
int n,a[N],vis[N];
//这个函数表示找到值为zhi的数在排完序后应在的区间 
pair<int,int> zhao(int zhi) {
	int ans1=0,ans2=0;
	for(int i=1; i<=n; ++i) {
		if(a[i]==zhi) {
			++ans2;
		}
		if(a[i]<zhi) {
			++ans1;
		}
	}
	return make_pair(ans1+1,ans1+ans2);
}
priority_queue<int> s;
pair<int,int> chu[5];
signed main() {
	cin>>n;
	for(int i=1; i<=n; ++i) {
		cin>>a[i];
	}
	//提前预处理一下，方便O(1)查询 
	chu[1]=zhao(1);
	chu[2]=zhao(2);
	chu[3]=zhao(3);
	chu[4]=zhao(4);
	int lst=1,xian=0;//lst表示当前执行到了lst，xian是为了方便遍历 
	int ans=0;
	for(int qwq=1; qwq<=4; ++qwq) {//qwq表示当前已经排序到了值为qwq的数 
		xian=1;
		set<int> ying;
		for(int i=chu[qwq].second+1;i<=n;++i){
			if(a[i]==qwq)
				ying.insert(i);
			//找到应与当前区间换的数 
		}
		int lstt=lst;
		for(;xian<=chu[qwq].second-chu[qwq].first+1; ++lst,++xian) {//先优先找到换之后还能满足的 
			if(a[lst]==qwq)continue;
			auto it=ying.lower_bound(chu[a[lst]].first);
			bool flag=0;
			if(it==ying.end())//没找到 
				flag=1;
			if((*it)>chu[a[lst]].second)//没找到 
				flag=1;
			if(!flag){//交换并删除 
				swap(a[*it],a[lst]);
				ying.erase(it);
				vis[lst]=1;
			}
			++ans;
		}
		for(lst=lstt,xian=1;xian<=chu[qwq].second-chu[qwq].first+1;++lst,++xian){//再次遍历当前区间，换之前没换的 
			if(a[lst]==qwq)continue;
			if(!vis[lst]){//没有被换过就换 
				swap(a[*ying.begin()],a[lst]);
				ying.erase(ying.begin());
				vis[lst]=1;
			}
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：igAC (赞：4)

# $\text{Describe}$

[AT link](https://atcoder.jp/contests/abc302/tasks/abc302_g)

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc302_g)

题意：给定序列 $A$，只包含 $1 \sim 4$，每次操作交换两个数，问使得这个序列排列为升序的最小操作次数。

# $\text{Solution}$

~~感觉这道题放 G 太简单了。~~

设 $c_{i,j}$ 表示这里本来应该填 $j$ 但是填了 $i$ 的二元组的个数。

因为序列 $A$ 仅包含 $1 \sim 4$。

所以我们有以下操作选择：

1. 进行 $1$ 次操作，让 $2$ 个位置合法。

2. 进行 $2$ 次操作，让 $3$ 个位置合法。

3. 进行 $3$ 次操作，让 $4$ 个位置合法。

显然 $\omega_1 > \omega_2 > \omega_3$。

$\omega$ 表示贡献。

于是我们可以枚举分别枚举 二、三、四元组，进行交换操作。

具体实现可参考代码。

# $\text{Code}$

时间、空间复杂度均为 $\mathcal{O}(n)$

~~直接排序会更简单，但是能 $\mathcal{O}(n)$ 为什么要 $\mathcal{O}(n \log n)$ 呢？~~

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,a[N],b[N],c[5][5],ans;
int cnt1,cnt2,cnt3,cnt4;
int min3(int a,int b,int c){return min({a,b,c});}
int min4(int a,int b,int c,int d){return min({a,b,c,d});}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		cnt1+=(a[i]==1);
		cnt2+=(a[i]==2);
		cnt3+=(a[i]==3);
		cnt4+=(a[i]==4);
	}
	cnt2+=cnt1,cnt3+=cnt2,cnt4+=cnt3;
	for(int i=1;i<=n;++i){
		if(i>cnt3) b[i]=4;
		else if(i>cnt2) b[i]=3;
		else if(i>cnt1) b[i]=2;
		else b[i]=1;
	}
	for(int i=1;i<=n;++i) if(a[i]!=b[i]) ++c[a[i]][b[i]];
	//(a,b)
	for(int i=1;i<=4;++i){
		for(int j=1;j<=4;++j){
			int d=min(c[i][j],c[j][i]);
			ans+=d;
			c[i][j]-=d,c[j][i]-=d;
		}
	}
	//(a,b,c)
	for(int i=1;i<=4;++i){
		for(int j=1;j<=4;++j){
			for(int k=1;k<=4;++k){
				int d=min3(c[i][j],c[j][k],c[k][i]);
				ans+=2*d;
				c[i][j]-=d,c[j][k]-=d,c[k][i]-=d;
			}
		}
	}
	//(a,b,c,d)
	for(int i=1;i<=4;++i){
		for(int j=1;j<=4;++j){
			for(int k=1;k<=4;++k){
				for(int t=1;t<=4;++t){
					int d=min4(c[i][j],c[j][k],c[k][t],c[t][i]);
					ans+=d*3;
					c[i][j]-=d,c[j][k]-=d,c[k][t]-=d,c[t][i]-=d;
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：2huk (赞：4)

## 题目描述

有一个长度为 $N$ 的序列 $A$，其中满足 $\forall i\in[1, N],\ A_i \in [1, 4]$。

问至少经过几次交换操作使得 $A$ 成为一个非降序列。

- $2 \le N \le 2 \times 10^5$
- $1 \le A_i \le 4$

## 分析

首先我们可以先找到正确的序列 $B$，然后统计 $f_{i, j}$ 表示实际应该填 $i$，但却填了 $j$ 的位置数量，其中 $\{i, j\} \in [1, 4]$。

```cpp
n = read();
for (int i = 1; i <= n; i ++ ) a[i] = b[i] = read();
sort(b + 1, b + n + 1);
for (int i = 1; i <= n; i ++ ) f[b[i]][a[i]] ++ ;
```

接下来分类讨论。

如果存在 $A_i = B_i$，也就是说这个位置上的数不需要跟别的数交换，那么不处理这个数。

否则，如果存在 $A_i = B_j,\ A_j = B_i$，也就是说这两个位置上的数反了，那么一定会交换它们。因为这样是 $1$ 次纠正 $2$ 个错误，效率是原来的 $\dfrac 12$。

```cpp
for (int i = 1; i <= 4; i ++ )
	for (int j = 1; j <= 4; j ++ )
		if (i != j)
		{
			int K = min(f[i][j], f[j][i]);
			res += K, f[i][j] -= K, f[j][i] -= K;
		}
```

再否则，如果存在 $A_i = B_j,\ A_j = B_k,\ A_k = B_i$，那么就可以将这 $3$ 个位置上的数依次交换。此时由于已经把所有形如 $A_i = B_j,\ A_j = B_i$ 的交换完了，所以此时一定会交换这 $3$ 个数。因为这样是 $2$ 次纠正 $3$ 个错误，效率是原来的 $\dfrac 23$。

```cpp
for (int i = 1; i <= 4; i ++ )
	for (int j = 1; j <= 4; j ++ )
		if (i != j)
			for (int k = 1; k <= 4; k ++ )
				if (i != k && j != k)
				{
					int K = min({f[i][j], f[j][k], f[k][i]});
					res += K * 2, f[i][j] -= K, f[j][k] -= K, f[k][i] -= K;
				}
```

剩下的就全是形如 $A_i = B_j,\ A_j = B_k,\ A_k = B_u,\ A_u = B_i$ 的了。此时剩下的数字只能依次交换，所以我们先要统计出剩下的 $f_{i, j}$ 的和 $num$，然后其中的每 $4$ 个数都需要交换 $3$ 次，因此答案需要加上 $num \times \dfrac 34$。

```cpp
for (int i = 1; i <= 4; i ++ )
	for (int j = 1; j <= 4; j ++ )
		if (i != j)
			num += f[i][j];
```

然后输出答案即可。

[$\text{Code}$](https://atcoder.jp/contests/abc302/submissions/41667970)



---

## 作者：_hxh (赞：2)

### 题意

给定一个长度为 $n$ 的序列 $A$，其中每个元素都是介于 $1$ 到 $4$ 之间的整数。可以选择一对整数 $(i,j)$ 并交换 $A_i$ 和 $A_j(1 \le i < j \le n)$，求使序列 $A$ 变为非递减序列所需的最小操作次数。

### 分析

先用另外一个数组 $f$ 记下 $A$ 序列变为非递减序列后的样子，然后和序列 $A$ 比较。总结下来只有以下几种情况：

1. $A_i = f_i(1 \le i \le n)$，这个数在正确的位置，由于我们要求最小操作次数，所以这个数当然不去动它；
2. $A_i = f_j,A_j = f_i(1 \le i,j \le n)$，这两个数直接交换就能到正确的位置上，即 $1$ 次交换调整 $2$ 个数；
3. $A_i = f_j,A_j = f_k,A_k = f_i(1 \le i,j,k \le n)$，这种情况可以用 $2$ 次交换调整 $3$ 个数；
4. $A_i = f_j,A_j = f_k,A_k = f_l,A_l = f_i(1 \le i,j,k,l \le n)$，同上，这种情况可以用 $3$ 次交换调整 $4$ 个数。

由于总共只有四种数，所以只会出现这 $4$ 种情况。

显然，除了第一种情况以外，第二种情况的“性价比”最高，第三种其次，第四种最低，所以我们肯定优先把元素看作第二种情况处理，如果没有元素符合第二种情况了，那就把元素看作第三种情况处理，以此类推，这样能保证最少的操作次数。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
const int M = 10;
int n,a[N],f[N],cnt[M][M],diff,ans;
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		f[i] = a[i];
	}
	sort(f + 1,f + n + 1);
	for (int i = 1;i <= n;i++)
		if (a[i] != f[i])
		{
			diff++;
			cnt[a[i]][f[i]]++;//cnt[x][y]记录本来这里应该是 x，现在是 y 的情况的个数 
		}
	for (int i = 1;i <= 4;i++)//第二种情况 
		for (int j = 1;j <= 4;j++)
			for (;cnt[i][j] > 0 && cnt[j][i] > 0 && i != j;cnt[i][j]--,cnt[j][i]--)
			{
				ans++;
				diff -= 2;
			}
	for (int i = 1;i <= 4;i++)//第三种情况 
		for (int j = 1;j <= 4;j++)
			for (int k = 1;k <= 4;k++)
				for (;cnt[i][j] > 0 && cnt[j][k] > 0 && cnt[k][i] > 0 && (i != j && i != k && j != k);cnt[i][j]--,cnt[j][k]--,cnt[k][i]--)
				{
					ans += 2;
					diff -= 3;
				}
	ans += diff / 4 * 3;//小技巧：因为现在只剩下第四种情况了，所以不需要再循环遍历计算，直接计算即可 
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Charlie_ljk (赞：2)

$O(n)$ 桶排序，知道每个数最后应该去哪，那么对于需要交换的只有三种情况：

1. 二者错排，交换一次。
2. 三者错排，交换两次。
3. 四者错排，交换三次。

当然这几种情况优先处理第一种，其次第二种，最后第三种，由此处理即可，最后总的复杂度是线性的。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=2e5+10;
template<typename Tp> inline void read(Tp&x)
{
	x=0;register bool z=true;
	register char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
	for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(z?x:~x+1);
}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y){read(x);read(y...);}
template<typename Tp> inline void wt(Tp x)
{if(x>9)wt(x/10);putchar((x%10)+'0');}
template<typename Tp> inline void write(Tp x)
{if(x<0)putchar('-'),x=~x+1;wt(x);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x);putchar(' ');write(y...);}
int n,a[N],sum[5],b[N],cnt[5][5],ans,tot;
signed main()
{
	read(n);
	for(int i=1;i<=n;i++) 
	{
		read(a[i]);
		sum[a[i]]++;
	}
	for(int i=1,pre=0;i<=4;i++)
	{
		for(int j=1;j<=sum[i];j++)
			b[pre+j]=i;
		pre+=sum[i];
	}
	for(int i=1;i<=n;i++)
		if(a[i]!=b[i])
		{
			tot++;
			cnt[a[i]][b[i]]++;
		}
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			if(i!=j)
			{
				int s=min(cnt[i][j],cnt[j][i]);
				ans+=s,tot-=s<<1;
				cnt[i][j]-=s,cnt[j][i]-=s;
			}
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			if(i!=j) for(int k=1;k<=4;k++)
				if(i!=k&&j!=k)
				{
					int s=min({cnt[i][j],cnt[j][k],cnt[k][i]});
					ans+=s<<1,tot-=(s<<1)+s;
					cnt[i][j]-=s,cnt[j][k]-=s,cnt[k][i]-=s;
				}
	write(ans+tot/4*3);
}
```

---

## 作者：tiantianyang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc302_g)
### 题目大意
有一个长度为 $N$ 的序列 $A$，通过交换两个数的操作，让这个序列单调不递减，求最小操作次数。
### 思路
这个数据范围是最大突破口 $A_i$ 数值只有一至四！我们首先对这个序列进行一下排序，得到其最终应该形成的序列，然后将每一种错误的都统计一遍。

这个时候我们来进行一下分类讨论：

- 一个数字为一但它现在位置在二的地方以及一个数字为二但它现在位置在一的地方，不难发现将两者交换就可以得到正确位置。我们也只需要付出一的代价，就可以让两个数字还原。

- 一个数字为一但它现在位置在二的地方以及一个数字为二但它现在位置在三的地方以及一个数字为三但它现在位置在一的地方，不难发现将三者进行交换就可以得到正确位置。我们也只需要付出二的代价，就可以让三个数字还原。

- 一个数字为一但它现在位置在二的地方以及一个数字为二但它现在位置在三的地方以及一个数字为三但它现在位置在四的地方以及一个数字为四但它现在位置在一的地方，不难发现将四者进行交换就可以得到正确位置。我们也只需要付出三的代价，就可以让四个数字还原。

同时易得第一种方案更优，其次是第二种，最后是第三种。我们只需要依次暴力枚举就可以得到最终答案。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,a[N],b[N],tong[10][10];
int ans,tmp,tot;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) {cin>>a[i];b[i]=a[i];}//读入 
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++) tong[a[i]][b[i]]++;//统计每一种错误的个数 
	
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++){
			if(i==j) continue;
			tot+=tong[i][j];//不想写四重循环用的 
		}//将一共种类数统计 
	//两者位置不同的情况 
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			if(i!=j){
				tmp=min(tong[i][j],tong[j][i]);//取其中最小值 
				ans+=tmp;
				tot-=tmp*2;
				tong[i][j]-=tmp;//减掉这种方案的个数 
				tong[j][i]-=tmp;
			}
	//三者位置不同的情况
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			for(int k=1;k<=4;k++){
				if(i==j||j==k||i==k) continue;
				tmp=min(tong[i][j],min(tong[j][k],tong[k][i]));
				ans+=tmp*2;
				tot-=tmp*3;
				tong[i][j]-=tmp;
				tong[j][k]-=tmp;
				tong[k][i]-=tmp;
			}
	
	cout<<ans+tot/4*3;//通过最后剩余数量，直接算出第三种的个数 
	return 0;//完美收官 
}
```

---

## 作者：juzi75 (赞：1)

## 题目大意

有一个长度为 $n$ 的序列 $a$，其中 $a_i=k(k=1,2,3,4)$，每次可以选两个数互换位置，求最少需要多少次操作才能使序列单调不增。

## 思路

整体来说，由于排完之后的序列是固定的，因此可以按照最后序列中每个数字所占区域进行划分，把错的换掉。

重点是互换的思路。由于此题 $a_i$ 范围极小，只有四种情况，不难想到，互换只有三种情况，两个互换、三轮换、四轮换。之所以要讨论轮换的情况，是因为如果仅是简单的两两互换，交换顺序不好确定，先交换的可能会影响后交换的，从而影响整体最优。而按照二、三、四个轮换的方式分类进行，相当于对排错的数字进行分组。因为最后显然会得到正确数组，所以显然不会互相干扰，所以可得最优解。

例子：

```cpp
6
3 4 1 1 2 4
```

按顺序排完之后是：

```cpp
1 1 2 3 4 4
```

对原序列的划分：

```cpp
3 4|1|1|2 4
//二元换 
3     1
1 4|1|3|2 4 //ans+1
//三元换 
  4 1   2
1 1|2|3|4 4 //ans+2
//无四元换 
```

因此答案为 $3$。

补充：由于二元、三元计算完之后，只剩四元的，因此可以直接用剩余错误数字个数计算得到对答案的贡献值，详见代码。

## 参考代码

（我明明只有一个快读加速，程序速度竟然能跑到 $3$ ms，~~主要是我提交的时候莫名其妙还抢到了当时最优解~~）

~~（压行好习惯）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[6],t[6][6],a[200002],l[6],r[6],ans,cnt;
inline int read(){  //快读 
	int x=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i) a[i]=read(),++p[a[i]];  //输入并统计每个数字出现个数，以进行区块划分，可以避免直接排序浪费O(nlogn)的时间 
	for(int i=1;i<=4;++i) l[i]=p[0]+1,r[i]=l[i]+p[i]-1,p[0]+=p[i];  //确定区块左右端点（这其实可要可不要，下面就用到了一次） 
	for(int i=1;i<=4;++i) for(int j=l[i];j<=r[i];++j) a[j]==i?(++t[i][a[j]]):(++t[i][a[j]],++cnt);  //统计每个区块各个数字出现次数以及位置错误的数字数 
	for(int i=1;i<=4;++i) for(int j=1;j<=4;++j) if(i!=j) while(t[i][j]&&t[j][i]) cnt-=2,++ans,--t[i][j],--t[j][i],++t[i][i],++t[j][j];  //二轮换 
	for(int i=1;i<=4;++i) for(int j=1;j<=4;++j) for(int k=1;k<=4;++k) if(i!=j&&j!=k&&i!=k) while(t[i][j]&&t[j][k]&&t[k][i]) cnt-=3,ans+=2,--t[i][j],--t[j][k],--t[k][i],++t[i][i],++t[j][j],++t[k][k];  //三轮换 
	printf("%d",ans+cnt/4*3);  //输出时加上四轮换贡献数 
	return 0;
}
```

完结撒花 ~~（我的题解简直和我的代码一样简短）~~

（写的第一篇题解，求过审~~~）

---

## 作者：aulive (赞：1)

我的思路可能有一点奇怪。

## Solution

我们可以先处理出在最终序列中每个数的区间里有几个其他数分别的个数。  
那么我们可以通过刚才的处理知道各个数如果要归位，要将哪些数给挤出去。  
那么我们便可以在 $1$ 到 $4$ 之间连边，边权是相应情况数的个数。

容易知道答案的最大值是错位的数的个数（每次交换至少使一个数归位）。

考虑一种特殊情况，便是如果两个数交换之后恰好归位，则答案还要减一。  
对于这种情况的解决方法是：在图上遍历，如果形成了环那便减去沿途最小的边权，还要给边权减一下（因为这几个数已经归位了）。

又因为边权要减，根据贪心的思想，我们肯定先找边数小的环，所以要在 dfs 的过程中判个长度。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e5;
int n,a[maxn+5],num[5],vis[5],rood[5][5];//rood[i][j]:在i的区间里j的个数
int dfs(int now,int minn,int up,int pos){
	if(pos>=up)return 0;
	if(vis[now]||!minn){
		return minn;
	}
	vis[now]=1;
	int res=0;
	for(int i=1;i<=4;i++){
		if(i==now)continue;
		int fw=dfs(i,min(minn,rood[now][i]),up,pos+1);
		res+=fw;
		rood[now][i]-=fw;
	}
	vis[now]=0;
	return res;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		num[a[i]]++;
	}
	for(int i=1;i<=num[1];i++){
		rood[1][a[i]]++;
	}
	for(int i=num[1]+1;i<=num[1]+num[2];i++){
		rood[2][a[i]]++;
	}
	for(int i=num[1]+num[2]+1;i<=num[1]+num[2]+num[3];i++){	
		rood[3][a[i]]++;
	}
	for(int i=num[1]+num[2]+num[3]+1;i<=num[1]+num[2]+num[3]+num[4];i++){
		rood[4][a[i]]++;
	}//建边 
	int ans=0;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(i==j)continue;
			ans+=rood[i][j];//先求出最大值 
		}
	}
	for(int ed=0;ed<=5;ed++){//限制环的长度 
		for(int i=1;i<=4;i++){//枚举搜索起点 
			ans-=dfs(i,1e8,ed,0);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zhangjyoi (赞：1)

## AT_abc302_g [ABC302G] Sort from 1 to 4题解
### 题目大意
给你一个序列 $A_1,A_2 \dots A_N$，其中 $1 \le A_i \le 4$，$N \le 2 \cdot 10^5$，求你至少要交换多少次才能使序列 $A$ 有序。
### 思路
由于 $1 \le A_i \le 4$，
我们可以将 $A$ 分成四段，
处理出二维数组 $C$。

我们可以交换 1 次使 2 个数归位，交换 2 次使 3 个数归位，交换 3 次使 4 个数归位。
我们优先选择操作 1，再操作 2，最后 3。

我们用 $x$ 记录有几个数未归位。

将 $A$ 排序，与原序列对比，记录 $x$。
时间复杂度 $O(n \log n)$。

### ACode
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200050],b[200050],c[5][5],x;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i])x++,c[b[i]][a[i]]++;
	}
	int ans=0;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			int t=min(c[i][j],c[j][i]);
			ans+=t;
			x-=t*2;
			c[i][j]-=t;
			c[j][i]-=t;
		}
	}
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			for(int k=1;k<=4;k++){
				int y=min(c[i][j],min(c[k][i],c[j][k]));
				ans+=y*2;
				x-=y*3;
				c[i][j]-=y;
				c[j][k]-=y;
				c[k][i]-=y;
			}
		}
	}
	printf("%d",ans+x/4*3);
	return 0;
}
```
### 注意事项
这道题一定要先操作 1，再 2，最后 3！（~~我被卡了好几次~~）

---

## 作者：FlyMe2TheMoon_ (赞：0)

# 题目大意
给你一个长为 $n$ 的序列 $A$ ，其中元素都是介于 $[1,4]$ 的整数。可以将任意两个元素交换位置，问使序列单调不降的最小操作数

# 思路
观察到元素只有 $1，2，3，4$，要使序列单调不降，最终一定是 $（1\cdots1,2\cdots2,3\cdots3,4\cdots4）$ 的形式，所以不难想出统计 $1,2,3,4$ 的个数，将序列分成 $4$ 块，第 $i（1 \le i\le4）$ 块的长度为数字 $i$ 出现的总次数。
当第 $i$ 块中出现不为 $i$ 的元素，我们就要将它交换到别的位置,因此对答案产生贡献。

所以我们接下来用 $cnt_{i,j}$ 来表示第 $i$ 块中数字 $j$ 出现的个数。当 $cnt_{i,j}>0$ 且 $cnt_{j,i}>0$ 时，我们就可以将第 $i$ 块中的大小为 $j$ 的元素换到第 $j$ 块中，对答案产生 $\min (cnt_{i,j},cnt_{j,i})$ 的贡献。

但考虑到传递可能是链状的，如下图
![](https://cdn.luogu.com.cn/upload/image_hosting/miqgzwqk.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


第 $1$ 块中的 $2$ 想要从第 $2$ 块中交换 $1$ ，而第 $2$ 块中没有 $1$ ，因此第 $2$ 块想与第 $3$ 块交换 $1$ ，而第 $3$ 块没有 $1$ ，它只能和第 $4$ 块交换 $1$。整个传递的过程形成的链长为 $3$，对答案产生了大小为 $3$ 的贡献。

因为有 $4$ 块，所以链的长度可能为 $1$ 或 $2$ 或 $3$ 。我们只要写三个 `for` 循环模拟交换的过程就可以通过此题。

时间复杂度 $\mathcal O(n)$ 

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt[10][10],len[10],ans;
int n,s[5000001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) 
		cin>>s[i],len[s[i]]++;
	for(int i=1;i<=len[1];i++)
		cnt[1][s[i]]++;
	for(int i=len[1]+1;i<=len[1]+len[2];i++)  
		cnt[2][s[i]]++;
	for(int i=len[1]+len[2]+1;i<=n-len[4];i++)  
		cnt[3][s[i]]++;
	for(int i=n-len[4]+1;i<=n;i++)  
		cnt[4][s[i]]++;
	for(int i=1;i<=4;i++)
		for(int j=i+1;j<=4;j++)
			if(cnt[i][j] && cnt[j][i])
			{
				int x=min(cnt[i][j],cnt[j][i]);
				cnt[i][j]-=x;cnt[j][i]-=x;
				cnt[i][i]+=x;cnt[j][j]+=x;
				ans+=x;
			}
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=4;j++)
		{
			if(i==j) continue;
			for(int k=1;k<=4;k++)
			{
				if(k==i || k==j) continue;
				if(cnt[i][k] && cnt[k][j] && cnt[j][i])
				{
					int x=min(cnt[i][k],min(cnt[k][j],cnt[j][i]));
					cnt[i][k]-=x;cnt[k][j]-=x;cnt[j][i]-=x;
					cnt[i][i]+=x;cnt[k][k]+=x;cnt[j][j]+=x;
					ans+=2*x;
				}
			}		
		}		
	}
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=4;j++)
		{
			if(j==i) continue;
			for(int k=1;k<=4;k++)
			{
				if(k==i || k==j) continue;
				for(int u=1;u<=4;u++)
				{
					if(u==i || u==j || u==k)  continue;
					if(cnt[i][j] && cnt[j][k] && cnt[k][u] && cnt[u][i])
					{
						int x=min(min(cnt[i][j],cnt[j][k]),min(cnt[k][u],cnt[u][i]));
						cnt[i][j]-=x;cnt[j][k]-=x;cnt[k][u]-=x;cnt[u][i]-=x;
						cnt[i][i]+=x;cnt[k][k]+=x;cnt[j][j]+=x;cnt[u][u]+=x;
						ans+=3*x;
					}
				}
			}		
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：tmp_get_zip_diff (赞：0)

[弱化版题目](https://www.luogu.com.cn/problem/P1459)。

## 题意

给你一个 $1 \sim n$ 的序列 $a_{1 \sim n}$，每次操作可以选择 $1 \le i < j \le n$，交换 $a_i,a_j$，要求最少多少此操作可以使得序列 $a$ 单调不下降。$1 \le n \le 2 \times 10^5$，$1 \le a_{i} \le 4$。

## 思路

用 $b$ 数组表示一个位置将要改成多少。

统计 $cnt_{i,j} (1 \le i,j \le 4)$ 代表原来是 $i$，要改成 $j$ 的位置个数。

那么对于这样一种情况（对于 $1 \le i,j\le n$，$a_i=b_j\; \wedge \; a_j=b_i$ ）：
```txt
a: 2 4
b: 4 2
```
直接用一次交换即可使两个位置满足条件。

另一种情况（对于 $1 \le i,j,k \le n$，$a_i=b_j\;\wedge\;a_j=b_k\;\wedge\;a_k=b_i$）：
```txt
a: 2 1 4
b: 1 4 2
```
那么可以通过两次交换使得三个位置满足条件。

最后一种情况（对于 $1 \le i,j,k,p \le n$，$a_i=b_j\;\wedge\;a_j=b_k\;\wedge\;a_k=b_p\;\wedge\;a_p=b_i$）：
```txt
a: 4 3 1 2
b: 3 1 2 4
```
这种情况可以通过三次交换使得四个满足条件。

当然，统计不正确的个数可以优化掉最后一种情况。

## 代码

```
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n,a[N],b[N],cnt[5][5],z,ans;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
		if(b[i]!=a[i])
			z++,cnt[a[i]][b[i]]++;
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
		{
			int t=min(cnt[i][j],cnt[j][i]);
			ans+=t*1; //可以简写，但这样更容易理解 
			z-=t*2;
			cnt[i][j]-=t;
			cnt[j][i]-=t;
		}
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			for(int k=1;k<=4;k++)
			{
				int t=min(cnt[i][j],min(cnt[k][i],cnt[j][k]));
				ans+=t*2;
				z-=t*3;
				cnt[i][j]-=t;
				cnt[k][i]-=t;
				cnt[j][k]-=t;
			}
	cout<<ans+z/4*3;
	return 0;
}
```

----

不喜勿喷！！！欢迎私信。

---

## 作者：云浅知处 (赞：0)

~~[ABC 的 G 怎么出了个橙题](https://www.luogu.com.cn/problem/P1459)~~

简单题。考虑算出 $1,2,3,4$ 各自的个数，然后把序列分成四段。设 $a_{i,j}$ 表示在第 $i$ 段中 $=j$ 的元素个数，其中 $1\le i,j\le 4$。我们的目标是让所有 $i\neq j$ 的 $a_{i,j}$ 都变成 $0$。

显然，同一段内的操作是没用的。每次操作如果交换了两个数 $x,y$，他们分别在 $i,j$ 这两段里，那么对 $a$ 的影响就是：

- $a_{i,x}\leftarrow a_{i,x}-1,a_{i,y}\leftarrow a_{i,y}+1$
- $a_{j,x}\leftarrow a_{j,x}+1,a_{j,y}\leftarrow a_{j,y}-1$

然后对每行依次考虑，发现最优策略一定是先把形如 $(i,j)$ 和 $(j,i)$ 这样的位置消成 $(i,i),(j,j)$，然后剩下的再匹配。由于 $A_i\le 4$，就算是第一行在匹配的时候也必然会在某一侧只留下一个非零元素，因此匹配方案是唯一的，可以保证最优。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=1e9+7;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=2e5+5;
int a[N],cnt[10],n,w[10][10];

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	n=read();
	for(int i=1;i<=n;i++)cnt[a[i]=read()]++;
	for(int i=1;i<=n;i++){
		int x=0;
		if(i<=cnt[1])x=1;
		else if(i<=cnt[1]+cnt[2])x=2;
		else if(i<=cnt[1]+cnt[2]+cnt[3])x=3;
		else if(i<=cnt[1]+cnt[2]+cnt[3]+cnt[4])x=4;
		w[x][a[i]]++;
	}
	int ans=0;
	for(int i=1;i<=4;i++){
		for(int j=i+1;j<=4;j++){
			int val=min(w[i][j],w[j][i]);
			w[i][i]+=val,w[j][j]+=val,w[i][j]-=val,w[j][i]-=val;
			ans+=val;
		}
		for(int j=i+1;j<=4;j++){
			for(int k=i+1;k<=4;k++){
				int val=min(w[i][j],w[k][i]);
				w[i][i]+=val,w[k][j]+=val,w[i][j]-=val,w[k][i]-=val;
				ans+=val;
			}
		}
	}
	cout<<ans<<endl;

	return 0;
}
```

---

