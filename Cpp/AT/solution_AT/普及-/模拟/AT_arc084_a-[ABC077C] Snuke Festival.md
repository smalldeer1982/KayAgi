# [ABC077C] Snuke Festival

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc077/tasks/arc084_a

今年もすぬけ祭の季節がやってきました。りんごさんは、まず手始めにすぬけ君召喚の儀式を執り行おうと思っています。 儀式には祭壇が必要で、祭壇は上部、中部、下部の $ 3 $ つのカテゴリーのパーツ $ 1 $ つずつからなります。

祭壇の $ 3 $ カテゴリーのパーツがそれぞれ $ N $ 個ずつあります。 $ i $ 個目の上部のパーツのサイズは $ A_i $ 、$ i $ 個目の中部のパーツのサイズは $ B_i $ 、$ i $ 個目の下部のパーツのサイズは $ C_i $ です。

祭壇を作るにあたっては、中部のパーツのサイズは上部のパーツのサイズより真に大きく、下部のパーツのサイズは中部のパーツのサイズより 真に大きくなければなりません。逆に、この条件を満たす任意の $ 3 $ つのピースを組み合わせて祭壇を作ることができます。

りんごさんが作ることのできる祭壇は何種類あるでしょうか。ただし、$ 2 $ つの祭壇が異なるとは、上部、中部、下部に使われるピースのうち 少なくとも $ 1 $ つが異なることを言います。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9(1\leq\ i\leq\ N) $
- $ 1\ \leq\ B_i\ \leq\ 10^9(1\leq\ i\leq\ N) $
- $ 1\ \leq\ C_i\ \leq\ 10^9(1\leq\ i\leq\ N) $
- 入力は全て整数である

### Sample Explanation 1

次の $ 3 $ 種類の祭壇があります。 - 上部に $ 1 $ 個目、中部に $ 1 $ 個目、下部に $ 1 $ 個目のパーツを使った祭壇 - 上部に $ 1 $ 個目、中部に $ 1 $ 個目、下部に $ 2 $ 個目のパーツを使った祭壇 - 上部に $ 1 $ 個目、中部に $ 2 $ 個目、下部に $ 2 $ 個目のパーツを使った祭壇

## 样例 #1

### 输入

```
2
1 5
2 4
3 6```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 1 1
2 2 2
3 3 3```

### 输出

```
27```

## 样例 #3

### 输入

```
6
3 14 159 2 6 53
58 9 79 323 84 6
2643 383 2 79 50 288```

### 输出

```
87```

# 题解

## 作者：Night_sea_64 (赞：3)

本蒟蒻又来写题解了。这道题~~比较简单~~。。。

[题目](https://www.luogu.com.cn/problem/AT3620)

先看看这个题用到的是什么算法。

如果我们暴力枚举，时间复杂度将是 $O(N^3)$，而 $N≤10^5$，铁定 TLE。

那怎么办呢？

我们把三个数组都排个序，这样用 lower_bound 和 upper_bound 的方法就能找出哪个零件能满足条件了。这里分成了两种方法。（对于 lower_bound 和 upper_bound，不会的可以自行百度）

## 第一种方法

第一种方法比较好想，但是代码实现比第二种难。

枚举上部零件，也就是 $A_i$。但是我们这样只能枚举到 $B_i$，然后求出满足条件的 $C_i$ 有多少个，时间复杂度还是 $O(N^2)$，还是没法做对。

怎么优化呢？可以用一个前缀和（或后缀和）的方法。定义 $posb,posc,s$ 数组。$posb_i$ 表示对于 $A_i$，第一个满足条件的 $B_i$ 在 $B$ 中的位置，$posc_i$ 表示对于 $B_i$，第一个满足条件的 $C_i$ 在 $C$ 中的位置。$s_i$ 表示 $N-posc_i+1$ 的前缀和（也就是对于 $B_1-B_i$，满足条件的 $C_i$ 的个数和。）

这样就可以用 $O(N)$ 的时间复杂度搞定了，AC 代码是这样的：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int a[100010],b[100010],c[100010];
long long s[100010];//前缀和数组要开 long long
int posb[1000010],posc[100010];
int main()
{
	int n;
	long long cnt=0;//总个数 cnt 也要开 long long
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++)
	{
		posb[i]=upper_bound(b+1,b+n+1,a[i])-b;
		posc[i]=upper_bound(c+1,c+n+1,b[i])-c;
		s[i]=s[i-1]+(n-posc[i]+1);//求前缀和 s 数组
	}
	for(int i=1;i<=n;i++)cnt+=s[n]-s[posb[i]-1];//前缀和操作。不能和上一个循环放在一起。因为 i<n 时还没有算到 s[n]。
	printf("%lld\n",cnt);
	return 0;
}
```

这种方法还是麻烦，还不容易理解。第二种方法就简单多了。

## 第二种方法

我们发现，第一种方法枚举 $A_i$，这样的缺点就是没有办法一下子就确定 $C_i$，只能通过 $B_i$ 再算出 $C_i$。怎么解决这个缺点呢？很显然，枚举 $B_i$ 就可以了。通过 $B_i$，既可以确定 $A_i$，又可以确定 $C_i$。就不那么麻烦了。最后再用加乘原理算出总方法数就可以了，轻松加愉快！！！AC 代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int a[100010],b[100010],c[100010];
int main()
{
	int n;
	long long cnt=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++)//枚举 b[i]
	{
		long long posa=lower_bound(a+1,a+n+1,b[i])-a-1;//满足条件 a[i] 的个数。因为得小于 b[i]，所以要减一。
		long long posc=upper_bound(c+1,c+n+1,b[i])-c;
  		cnt+=posa*(n-posc+1);//加乘原理
	}
	printf("%lld\n",cnt);
	return 0;
}
```

蒟蒻题解到此结束。祝大家 RP++！！！

---

## 作者：CaiXY06 (赞：3)

本**蒟蒻**的第一篇题解

**ARC084**的第一题

被选入了我的一场模拟赛中

总体来说还是一道~~简单题~~（大雾）

但还是没能一刀切，在IOI赛制的加持下，提交$N$次才过

------------
# 题目大意

**给定三个长度为$n$的序列：$A_{1,2,3...n}$;$B_{1,2,3...n}$;$C_{1,2,3...n}$**
 
**求有多少个三元组（$i$,$j$,$k$）**

**满足$1≤i,j,k≤n$ 且 $A_{i}$＜$B_{j}$＜$C_{k}$**

**($1≤n≤10^{5},1≤A_{i},B_{j},C_{k}≤10^{9}$)**

# 解释
**很显然$O(n^{3})$或$O(n^{2})$的暴力是必定会$TLE$的，所以我们得使用一些别的东西**

**我们首先将三个序列进行 _从小到大排序_ （题目要求摆在那儿，这样更加方便）**

**由于序列$B$位于中间，so它与剩下的两个序列$A$，$C$都关联，而$A$和$C$都只与$B$关联，所以我们将$B$作为主要对象，对剩下两个序列进行操作**

**先前已经进行过排序操作，因此我们只要对于每一个$B_{j}$找到其对应的$A_{i}$和$C_{k}$，使得它们分别是 小于$B_{j}$最大的$A_{i}$和 大于$B_{j}$最小的$C_{k}$** 

**这时更新答案，$Ans+=i×(n-k+1)$**

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100010],b[100010],c[100010],sa,sb;
long long ans;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	sort(c+1,c+n+1);
	sa=sb=1;
	for(int i=1;i<=n;i++){
	    bool f=0;
	    for(int j=sa;j<=n;j++)
	    if(a[j]>=b[i]){
	            f=1;
		    sa=j;
                    //因为这里找到的是第一个大于等于Bj的Ai
                    //所以计算时记得-1
		    break;//一定要跳出循环啊
	    }
	    if(!f)sa=n+1;
	    f=0;
	    for(int j=sb;j<=n;j++)
	    if(c[j]>b[i]){
		    sb=j;
		    f=1;
		    ans+=(n-sb+1)*(sa-1);//更新答案
		    break;
	    }
	    if(!f)sb=n+1;
	}
	printf("%lld",ans);
	return 0;//好习惯
}
```


------------
如若码风引起不适，勿喷

事实上，使用二分会更优，但本蒟蒻不会啊qwq！！！

---

## 作者：Chthology (赞：3)

###题目大意:

要搭一祭坛，包含上中下三层。现有一些数量相同上层部分、中层部分和、下层部分。上层部分大小分别为Ai，中层部分大小分别为Bi，下层部分大小分别为Ci，且每种部分中每个部分的重量不同。当一个上层部分比一个中层部分小，而一个下层部分比那个中层部分大，那么这三个部分就能组成一个祭坛。给你每种部分的数量和每个部分的重量，问能组成多少种不同的祭坛。

######~~蒟蒻英语不太好，dalao轻喷~~


---
###解:

输入后把三组数据从小到大排序，因为上面的要比中间的小，下面的要比中间的大，于是我们可以扫描中间部分，每扫到一个找上层比中层小的，下层比中层大的，然后把两个数量相乘，累加到ans里，最后输出ans就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF = int(1e9);
const int MAX = 1000020;
LL N;
LL a[MAX],b[MAX],c[MAX];
 
void Cin(LL a[]){
    for(int i = 1;i<=N;i++)
        scanf("%lld",&a[i]);
}
 
int main(){
    cin>>N;
    //if(N==2) return cout<<0,0;
    Cin(a),Cin(b),Cin(c);
    sort(a+1,a+1+N),sort(b+1,b+1+N),sort(c+1,c+1+N);
    LL sum = 0;
    LL ai = 0,ci = 0;
    for(int i = 1;i<=N;i++){
        while(a[ai+1]<b[i]&&ai+1<=N)
            ai++;
        while(c[ci+1]<=b[i]&&ci+1<=N)
            ci++;
        sum += ai*(N-ci);
    }
    cout<<sum<<endl;
    return 0;
}
```
本蒟蒻找上层比中层小的，下层比中层大的的部分直接打的暴力，用二分也可以。


蒟蒻的第一篇题解，dalao轻喷。


---

## 作者：_wjr_ (赞：1)

### 算法思路

当我们看到 $n \le 10^5$ 的时候，很明显，$O(n^3)$ 或者 $O(n^2)$ 的做法会 TLE 了。那么，我们现在就需要想出 $O(n)$ 的做法，才可能把这道题 AC。

那么，这个一重循环怎么用，就显得十分关键了。

我们不难发现，如果我们要建好一个祭坛，中间那一层会显得比较关键。底层必须要比它大，顶层又必须要比它小。

那么，只要我们依次枚举中间一层的大小，再计算出顶层可行的块数 $x$ 与底层可行的块数 $y$，那么对于这一块中层，他就有 $x \times y$ 种方案。

那么，似乎这道题就做完了。

但是，似乎还有一个问题：我怎么能知道顶层可行的块数 $x$ 与底层可行的块数 $y$ 呢？

可以使用 `lower_bound()` 与 `upper_bound()` 的系统自带函数，以实现 $\log_2$ 的复杂度。利用他们，我们能够知道在一个数列中，第一个大于等于（大于）某个值 $m$ 的数的下标。那么，这最后一个问题就迎刃而解了。


### AC Code

```cpp
#include<bits/stdc++.h>

using namespace std;

const int NR = 1e5 + 10;
int a[NR], b[NR], c[NR];

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	sort (a + 1, a + n + 1);
	sort (b + 1, b + n + 1);
	sort (c + 1, c + n + 1);
	long long ans = 0;//答案会爆int，要用long long
	for (int i = 1; i <= n; i++)
	{
		int x = lower_bound (a + 1, a + n + 1, b[i]) - a - 1;//确定顶层有多少块能够被应用
		int y = n - (upper_bound(c + 1, c + n + 1, b[i]) - c) + 1;//确定底层有多少块能够被应用
		ans += 1ll * x * y;
	}
	cout << ans << endl;
	return 0;
}
```

完结撒花！谢谢观看喵~

---

## 作者：封禁用户 (赞：1)

首先本蒟蒻来说说题目大意：

有三个集合 $A,B,C$ 每个集合都有 $n$ 个数。

现在要从每个集合里任取 $1$ 个数使得 $1 \leq i,j,k \leq n$ 且 $A_i>B_j>C_k$ 。

问一共有几种取数方法。

首先最容易想到的是暴力。

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[100005],b[100005],c[100005];

int main(){
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int i=1;i<=n;++i){
		cin>>b[i];
	}
	for(int i=1;i<=n;++i){
		cin>>c[i];
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			for(int k=1;k<=n;++k)
				if(a[i]<b[j]&&b[j]<c[k]){
					++ans;
				}
	cout<<ans<<endl;
	return 0;
}
```
这个方法的时间复杂度是 $O(n^3)$ ，可是 $n \leq 100000$ ，这一定会超时。

让我们再次看题目，发现它的三个集合中的数与顺序无关，只和大小相关，于是就想到了排序。

我们可以先把三个集合都排序，再看看 $A$ 集合中哪个数是小于 $B_i$ ，$B$ 集合中哪些数是小于 $C_i$ 的，把他们相乘，累加到 $ans$ 里，最后再输出 $ans$。

这次的时间复杂度是 $O(n^2)$ ，比上次好一点。

我们可以把它优化一下，用二分查找，时间复杂度是 $O(nlogn)$ ，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[100005],b[100005],c[100005];

signed main(){
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int i=1;i<=n;++i){
		cin>>b[i];
	}
	for(int i=1;i<=n;++i){
		cin>>c[i];
	}
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	sort(c+1,c+1+n);
	int t1,t2;
	for(int i=1;i<=n;++i){
		t1=lower_bound(a+1,a+1+n,b[i])-a;
		t2=upper_bound(c+1,c+1+n,b[i])-c;//注意这里是upper_bound不是lower_bound
		ans+=(t1-1)*(n-t2+1);//这里t1和t2求出来的是位置，要减一
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Lysea (赞：0)

## 思路

我们先放一组数据：
```
4
6 3 7 9
4 2 10 3
4 11 9 7
```
把它们排序后：
```
3 6 7 9
2 3 4 10
4 7 9 11
```
如果我们每次先选出 $a$ 数组中的一个数，在 $b$ 数组中找出第一个比它大的数，最后再对 $c$ 数组进行同样的操作，加上 $c$ 数组剩余的数，便可以得到答案了！

这就是一道暴力题（开心）。

## 样例

```
3 6 7 9
2 3 4 10
4 7 9 11
```
我们先从 $\mathit{a}_{1}$ 开始枚举情况，在 $b$ 数组中，第一个比 $\mathit{a}_{1}$ 大的是 $\mathit{b}_{3}$。

题目中很明确的说明了不能将相等的情况算进去，所以并不能选 $\mathit{b}_{2}$。

而因为 $\mathit{b}_{4}$ 肯定比 $\mathit{b}_{3}$ 大，所以 $\mathit{b}_{3,4}$ 都满足结果。

再从 $c$ 数组中找到第一个比 $\mathit{b}_{3}$ 大的数，是 $\mathit{c}_{2}$。

因为 $\mathit{c}_{3}$ 和 $\mathit{c}_{4}$ 肯定比 $\mathit{c}_{2}$ 大，所以 $\mathit{c}_{2,3,4}$ 都满足结果，共有 $3$ 种结果。

最后从 $c$ 数组中找到第一个比 $\mathit{b}_{4}$ 大的数，是 $\mathit{c}_{4}$，共有 $1$ 种结果。

这就是 $\mathit{a}_{1}$ 枚举情况的过程，共 $4$ 种可能，以此类推。

## 代码
```c
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,a[N],b[N],c[N],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	sort(a+1,a+1+n),sort(b+1,b+1+n),sort(c+1,c+1+n);
	for(int i=1;i<=n;i++){
		int h2,tail1,tail2;
		tail1=0;
		while(b[++tail1]<=a[i]);
		for(int j=tail1;j<=n;j++){
			h2=n,tail2=0;
			while(c[++tail2]<=b[j]) h2--;
			ans+=h2;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：W_fly_K (赞：0)


## 题意

要建造一个祭坛，由上部，中部，下部零件构成。要求：上部零件 $<$ 中部零件 $<$ 上部零件 。

## 思路

看到要求，不就是递增吗 ， ``upper_bound`` 刚好就是求递增的吗！

 ``upper_bound`` 用法：
 
 $a$ 是一个数组，$n$ 是数组长度， ``upper_bound(a,a+n,x)`` 返回数组 $a$ 中，大于 $x$ 的数中，最小的数的指针 （ 这个 $a$ 须递增的 )。

# _code_

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans;
int a[100005];
int b[100005];
int c[100005];
int f[100005];
int num1[100005];
int num2[100005];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	sort(a+1,a+n+1);                             //排序，因为upper_bound使用要求数组是递增的
	sort(b+1,b+n+1);
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++)
	{
		num1[i]=upper_bound(b+1,b+n+1,a[i])-b;//在b数组中找大于a[i]的数
		num2[i]=upper_bound(c+1,c+n+1,b[i])-c;//在c数组中找大于b[i]的数
		f[i]=f[i-1]+n-num2[i]+1;
	}
	for(int i=1;i<=n;i++)
	ans+=f[n]-f[num1[i]-1];
	cout<<ans<<endl;                           
	return 0;
}
```


---

## 作者：Composite_Function (赞：0)

# 思路

由于自己做这题时在学二分，就考虑用二分做了。

## 1 - 暴力

暴力枚举 $3$ 个数组，每找到一组 $a _ i < b _ j < c _ k$，就是一组满足的条件。时间复杂度 $O(N ^ 3)$。



## 2 - 暴力中的优化

枚举两个数组，二分找出剩下一个数组可以做到的数量。时间复杂度 $O(N ^ 2\log N)$。

STL 中给出函数 `lower_bound`，就不用打二分板子了。

## 3 - 正解

枚举数组 $b$。使用二分找出对于 $b _ j$，$a _ i$ 与 $c _ k$ 的有多少种取法。时间复杂度 $O(N\log ^ 2 N)$。

# 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

# define int long long
const int N = 1e5 + 10;

int n, a[N], b[N], c[N];
int num_a[N], num_c[N];

signed main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];
	for (int i = 1; i <= n; ++i) cin >> c[i];
	
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	sort(c + 1, c + n + 1);
	
	for (int i = 1; i <= n; ++i)
		num_a[i] = lower_bound(a + 1, a + n + 1, b[i]) - a - 1;
	for (int i = 1; i <= n; ++i)
		num_c[i] = n - (upper_bound(c + 1, c + n + 1, b[i]) - c - 1);
	
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += num_a[i] * num_c[i];
	cout << ans << endl;
	
	return 0;
}
```


---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT3620)

做题的第一件事就是看范围。

注意到范围，想到应该要使用  $O(n\times \log  n)$  的办法。

进而联想到**排序与二分**。

事实证明的确要使用排序与二分。

不说废话，我的思路是读入时顺便给三个数组排序，当然是从小到大。

然后，我们枚举第二个数组。

为什么枚举第二个呢？

因为它和另外两个都有直接的大小关系，可以帮助我们**卡范围**！

利用[算法库自带的二分函数](https://blog.csdn.net/weixin_43237242/article/details/90450726)，来算出上中与中下的范围。

再利用加乘原理即可。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define N (int)(1e5 + 5)
using namespace std;
int n, a[N], b[N], c[N];
void QwQ(int x[])  //作用：读入并排序。 
{
	for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
	sort(x+1, x+n+1);
}
int main()
{
	//以下四行读入。 
	scanf("%d", &n);
	QwQ(a);
	QwQ(b);
	QwQ(c);
	//下面就是重点代码，注意 sum 的所使用的数据范围。 
	long long sum = 0; 
	for (int i = 1; i <= n; i++)
	{
		long long cntA = lower_bound(a+1, a+n+1, b[i]) - a - 1;
		long long cntC = upper_bound(c+1, c+n+1, b[i]) - c - 1;
		cntC = n - cntC;  //上面的得出的是起始位置，还要卡范围。 
		sum += (cntA * cntC);  //加乘原理。 
	}
	printf("%lld", sum);
	return 0;
}
```


---

## 作者：洛璟 (赞：0)

## Solution：

简单的橙题。

观察题目，我们不难想到先给三个数组排个序，但是接下来的做法有点棘手，虽然我看题解区接下来好像很多较为暴力的方法都可以过，但是出于谨慎，我觉得暴力查找，还是不行，毕竟极端数据还是会爆炸……

那么，查找这件事，遇到有序数组，应该都很明白，二分是最好的选择。

（蒟蒻太懒了，只想用STL）

那么我们直接用upper_bound来二分查找出 $a_{i}$ 中有多少数小于 $b_{i}$中任意一个的数。

upper_bound略析：使用二分法找出一个数组中第一个大于确定的数的地址。

用法：upper_bound(查找起始地址，查找终止地址，确定的数，大小顺序（默认为大于，可用 greater<int>()改为小于）)，由于返回地址，最后应减去一个地址变为下标，具体操作方法可代码。

随后我们在 $c$ 数组中找出比 $b_{i}$ 大的数，仍然是二分，根据乘法原理，就可得出答案。

上面的表述可能不大清楚，推荐与代码一同食用

code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, a[114514], b[114514], c[114514], d[114514];
long long ans;
inline long long read() {
    long long x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }
    for (int i = 1; i <= n; i++) {
        b[i] = read();
    }
    for (int i = 1; i <= n; i++) {
        c[i] = read();
    }
    swap(a[rand() % n + 1], a[rand() % n + 1]);
    swap(b[rand() % n + 1], b[rand() % n + 1]);
    swap(c[rand() % n + 1], c[rand() % n + 1]);
    //这里的操作，不要也罢，我只是担心可能会有duliu数据卡快排的退化。
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    sort(c + 1, c + n + 1);
    for (int i = 1; i <= n; i++) {
        int qwq = upper_bound(b + 1, b + n + 1, a[i]) - b;
        d[qwq] += 1;//详见下一个循环
    }
    for (int i = 1; i <= n; i++) {
        d[i] = d[i - 1] + d[i];
    }//使用差分，统计出a中有多少数小于b中每个数字
    for (int i = 1; i <= n; i++) {
        int qwq = upper_bound(c + 1, c + n + 1, b[i]) - c;
        ans += (n - qwq + 1) * d[i];//乘法原理，可自行bdfs
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：极寒神冰 (赞：0)

对$a,b,c$三个数组升序排序后。
由于枚举$a$中的元素并不能确定$b,c$两个元素之间关系(虽然可以直接暴力或者二分

那么考虑枚举$b$中的元素$b_i$,然后在$a$寻找最后一个小于$b_i$的元素$a_{posa}$和在$c$中寻找第一个大于$b_i$的元素$c_{posc}$

对于每一个$i$，根据乘法原理，答案为$posa\times (n-posc)$

最终答案为$\sum_{i=1}^n posa\times (n-posc)$

复杂度大概均摊$O(n)$

```
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
const int mod=19930726;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=1e5+10;
int a[N],b[N],c[N];
int n;
int res;
int posi,posk;
inline int fpow(int a,int b){
	int res=1;while(b){if(b&1)res=res*a;a=a*a;b>>=1;}return res;
}
signed main()
{
	n=read();
	R(i,1,n) a[i]=read();
	R(i,1,n) b[i]=read();
	R(i,1,n) c[i]=read();
	sort(a+1,a+n+1),sort(b+1,b+n+1),sort(c+1,c+n+1);
	R(i,1,n)
	{
		for(;a[posi+1]<b[i]&&posi+1<=n;) posi++;
		for(;c[posk+1]<=b[i]&&posk+1<=n;) posk++;
		res+=posi*(n-posk);
	}
	printf("%lld\n",res);
}
```


---

