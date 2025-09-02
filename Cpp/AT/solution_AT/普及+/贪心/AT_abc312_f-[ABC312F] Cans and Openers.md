# [ABC312F] Cans and Openers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc312/tasks/abc312_f

$ N $ 個の品物があります。  
 これらはそれぞれ、缶切りが不要な缶・缶切りが必要な缶・缶切りのいずれかです。  
 $ i $ 個目の品物は、整数の組 $ (T_i,\ X_i) $ により次のように表されます。

- $ T_i\ =\ 0 $ ならば、$ i $ 個目の品物は缶切りが不要な缶で、入手すると満足度 $ X_i $ を得る。
- $ T_i\ =\ 1 $ ならば、$ i $ 個目の品物は缶切りが必要な缶で、入手した上で缶切りを使うと満足度 $ X_i $ を得る。
- $ T_i\ =\ 2 $ ならば、$ i $ 個目の品物は缶切りで、$ X_i $ 個までの缶に対して使用できる。
 
$ N $ 個の品物から $ M $ 個を選んで入手するとき、得られる満足度の合計としてあり得る最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ M\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ T_i $ は $ 0,1,2 $ のいずれか
- $ 1\ \leq\ X_i\ \leq\ 10^9 $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ 1,\ 2,\ 5,\ 7 $ 個目の品物を入手し、$ 7 $ 個目の品物である缶切りを $ 5 $ 個目の品物に対して使用すると、満足度 $ 6\ +\ 6\ +\ 15\ =\ 27 $ を得ます。 満足度が $ 28 $ 以上になる品物の入手方法は存在しませんが、上記の例において $ 7 $ 個目の品物のかわりに $ 6 $ 個目の品物や $ 8 $ 個目の品物を選んでも満足度 $ 27 $ を得ることができます。

## 样例 #1

### 输入

```
8 4
0 6
0 6
1 3
1 5
1 15
2 1
2 10
2 100```

### 输出

```
27```

## 样例 #2

### 输入

```
5 5
1 5
1 5
1 5
1 5
1 5```

### 输出

```
0```

## 样例 #3

### 输入

```
12 6
2 2
0 1
0 9
1 3
1 5
1 3
0 4
2 1
1 8
2 1
0 1
0 4```

### 输出

```
30```

# 题解

## 作者：elbissoPtImaerD (赞：4)

先把三种操作分开，不妨记做序列 $a_0,a_1,a_2$，将三个序列按 $x$ 降序排列，则最优解一定是三个序列的三段前缀。

不难想到，枚举其中的一个前缀的长度。  
枚举 $a_0$ 的好了。

考虑维护 $x_i,y_i$，表示选取 $a_0$ 的长度为 $i$ 时，最优选取的 $a_1,a_2$ 的前缀长度。

贪心地想，$x_i,y_i$ 一定在 $i$ 递减时不增，且每次变化量至多为 $1$。

那总复杂度 $\mathcal{O(n)}$，做完了啊。

```cpp
bool*MS;
int n,m;
LL ans;
sd vector<LL>a[3];
bool*MT;
void Solve()
{
  rd(n,m);
  for(int i=1,o,x;i<=n;++i) rd(o,x),a[o].push_back(x);
  sd stable_sort(rbegin(a[0]),rend(a[0]));
  sd stable_sort(rbegin(a[1]),rend(a[1]));
  sd stable_sort(rbegin(a[2]),rend(a[2]));
  for(;a[0].size()<=m;a[0].push_back(0));
  for(int i=1;i<a[0].size();++i) a[0][i]+=a[0][i-1];
  for(int i=1;i<a[1].size();++i) a[1][i]+=a[1][i-1];
  for(int i=1;i<a[2].size();++i) a[2][i]+=a[2][i-1];
  for(int i=m,x=-1,y=-1;~i;--i)// 0
    cx(ans,(~x?a[1][x]:0)+(i?a[0][i-1]:0)),x+1<(~y?a[2][y]:-1)?x+1<a[1].size()?++x:7:y+1<a[2].size()?++y:7;
  wrt(ans,'\n');
  return;
}
```

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc312/submissions/44149895)。

---

## 作者：Engulf (赞：4)

以下记 $a$ 为拉环罐子，$b$ 为普通罐头，$c$ 为开罐器。

不妨枚举 $b$ 的个数，这样 $c$ 的个数就确定了下来，然后 $a$ 的个数也确定了下来。

先把 $a,b,c$ 三个数组从大到小排序，对于 $a$ 和 $b$ 来说，优先取大的总是更优。对于 $c$ 来说，优先取能开更多罐头的开罐器能让 $a$ 和 $b$ 取更多。

再对 $a,b,c$ 做个前缀和，$c$ 有了单调性，可以直接二分求出最小的开罐器个数使之开完所有的罐头。

实现上有一些细节。


```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int inf = 0x3f3f3f3f;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a, b, c;
    for (int i = 1, t, x; i <= n; i++) {
        cin >> t >> x;
        if (t == 0) a.emplace_back(x);
        if (t == 1) b.emplace_back(x);
        if (t == 2) c.emplace_back(x);
    }
    sort(a.begin(), a.end(), greater<>());
    sort(b.begin(), b.end(), greater<>());
    sort(c.begin(), c.end(), greater<>());
    for (int i = 1; i < a.size(); i++) a[i] += a[i - 1];
    for (int i = 1; i < b.size(); i++) b[i] += b[i - 1];
    for (int i = 1; i < c.size(); i++) c[i] += c[i - 1];
    int ans = a.empty() ? 0 : a[min(m - 1, (int)a.size() - 1)]; // 不取普通罐头
    for (int i = 0; i < b.size(); i++) {
        int l = 0, r = c.size() - 1, res = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (c[mid] >= i + 1) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        if (res == -1) continue; // 开不完这么多罐头
        int remain = m - (i + 1) - (res + 1);
        if (remain >= 0)
            ans = max(ans, b[i] + (remain ? a[min((int)a.size() - 1, remain - 1)] : 0)); // 要考虑拉环罐头不足的情况
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Fire_flame (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc312_f)

关于赛时想到枚举 $2$ 物品的个数然后假了的事情。

## $\mathtt{Solution}$

考虑枚举 $1$ 物品的个数，二分查找求出最少需要用到的 $2$ 物品的数量，最后贪心地选择 $0$ 物品。

如果 $1$ 物品的个数加上 $2$ 物品的个数超过了 $m$，需要舍去。

当然如果 $1$ 物品的个数大于 $2$ 物品能够开启的 $1$ 物品的数量，也须舍去。

最后每次贪心选择，排序和前缀和预处理就可以了。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5;
int n, m, ans, cnt1, cnt2, cnt3, s1[MAXN], s2[MAXN], s3[MAXN];
struct node{
	int x, y;
	bool operator < (const node &ll)const{
		if(ll.x != x)return x < ll.x;
		return y > ll.y;
	}
}a[MAXN];
signed main(){
	n = read(), m = read();
	for(int i = 1;i <= n;i ++)a[i] = {read(), read()};
	sort(a + 1, a + n + 1);
	for(int i = 1;i <= n;i ++){
		if(a[i].x != 0)continue;
		s1[++ cnt1] = a[i].y;
	}
	for(int i = 1;i <= n;i ++){
		if(a[i].x != 1)continue;
		s2[++ cnt2] = a[i].y;
	}
	for(int i = 1;i <= n;i ++){
		if(a[i].x != 2)continue;
		s3[++ cnt3] = a[i].y;
	}
	for(int i = 1;i <= n;i ++)s1[i] += s1[i - 1];
	for(int i = 1;i <= n;i ++)s2[i] += s2[i - 1];
	for(int i = 1;i <= n;i ++)s3[i] += s3[i - 1];
	for(int i = 0;i <= cnt2;i ++){
		if(i > s3[cnt3])break;
		int h = lower_bound(s3 + 1, s3 + cnt3 + 1, i) - s3;
		if(i == 0)h = 0;
		if(h + i > m)break;
		ans = max(ans, s2[i] + s1[m - i - h]);
//		printf("%lld %lld %lld\n", i, h, s2[i] + s1[m - i - h]);
	}
	write(ans);
	return 0;
}
```

---

## 作者：Neil_Qian (赞：3)

# [ABC312F] Cans and Openers 题解

## 题目描述

有 $n$ 个物品，可以选 $m$ 个，物品分为 $3$ 种类型：\
第一种：直接获得 $x_i$ 的喜悦值。\
第二种：如果被一把钥匙打开，获得 $x_i$ 的喜悦值。\
第三种：获得 $x_i$ 把钥匙。\
求最大喜悦值。

## 解决方案

第一眼可能想到是背包，然而 $x$ 太大。注意到选所有物品代价均为 $1$，而且第二种、第三种物品有关联性，考虑**枚举第一种物品的个数**，然后得到剩下两种物品之和，**计算能够选多少个第二种类型的物品的最大喜悦值**（因为需要考虑拿多少把钥匙）。

然后思考细节。显然，在代价相同的情况下将三种物品**各自按 $x_i$ 降序排序**。第一种物品的最大喜悦值可以通过前缀和计算，而第二部分维护 $have$，每次检查是否可以取 $have$ 个类型二，不行就减一，直到符合条件或者一个都取不了。不难发现，第一部分每次是常数级别的，第二部分 **$have$ 整个程序最多检查 $O(n)$ 次**，均摊 $O(1)$ 次，每次检查二分答案即可。最终，时间复杂度 $O(n\log n)$。

## 代码

~~码风不好，赛时乱写的。~~

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
ll n,m,opt,x,nw,have,ans;vector<ll> w,lmw,buy;
inline bool cmp(ll x,ll y){return x>y;}//降序排序
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//IO优化
	cin>>n>>m;//输入+预处理
	for(ll i=1;i<=n;i++){
		cin>>opt>>x;
		if(opt==0)w.push_back(x);
		else if(opt==1)lmw.push_back(x);
		else buy.push_back(x);
	}
	sort(w.begin(),w.end(),cmp),sort(buy.begin(),buy.end(),cmp),
	sort(lmw.begin(),lmw.end(),cmp);//排序+前缀和
	for(ll i=1;i<(ll)w.size();i++)w[i]+=w[i-1];
	for(ll i=1;i<(ll)buy.size();i++)buy[i]+=buy[i-1];
	for(ll i=1;i<(ll)lmw.size();i++)lmw[i]+=lmw[i-1];
	have=(buy.size()?min(*(buy.end()-1),m):0);//注意have初始化，我因此WA了一次
	for(ll i=0;i<=(ll)w.size()&&i<=m;i++){//枚举第一部分
		nw=0;
		if(i&&w.size())nw=w[i-1];//计算第一部分
		while(have&&have+(lower_bound(buy.begin(),buy.end(),have)-
			buy.begin()+1)>m-i)have--;//计算第二部分
		if(have&&lmw.size())nw+=lmw[min(have,(ll)lmw.size())-1];
		ans=max(ans,nw);//统计答案
	}
	return cout<<ans<<"\n",0;
}
```

---

## 作者：康立扬 (赞：2)

[洛谷 题目传送门](https://www.luogu.com.cn/problem/AT_abc312_f)

[Atcoder 题目传送门](https://atcoder.jp/contests/abc312/tasks/abc312_f)


## $\mathtt{Solution}$

考虑枚举 $2$ 物品的个数。

记选了 $a$ 个 $2$ 物品，能够打开 $b$ 个 $1$ 物品。

此时的答案即为在 $0$ 和 $1$ 类物品中选出 $m-a$ 个，且选出的 $1$ 类物品的个数小与等于 $b$ 的情况下，获得的最大贡献。

考虑反悔贪心，用一个小根堆维护已经选的物品的贡献，每次添加一个新的物品，如果新的物品的贡献大于堆顶的值，就将堆顶弹出，并将新的物品加入堆中。时间复杂度 $O(n \log n)$。

答案即为堆中每个数的和的最大值。

具体细节见代码。

[提交记录](https://atcoder.jp/contests/abc312/submissions/44077835)

---

## 作者：igAC (赞：2)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc312_f)

[ATlink](https://atcoder.jp/contests/abc312/tasks/abc312_f)

简要题意：

给定 $n$ 个操作：

1. 获得 $x$ 的分数。

2. 花费一次机会获得 $x$ 的分数。

3. 获得 $x$ 次机会。

你需要在这些操作中选择 $m$ 次操作（任意顺序），使得你的分数最大。

# $\text{Solution}$

简单贪心。

只有 1,2 操作会产生分数，考虑分别将 1,2 操作从大到小排序。

用 ``priority_queue`` 来存储最大的可以选的值，首先把前 $m$ 大的 1 操作压入队列。

接着枚举使用多少次 3 操作，每次计算队列中前 $m-i$ 大的统计答案（用了 $i$ 次 3 操作），其余的踢出队列。

正确性显然，具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,a[N],b[N],c[N],n1,n2,n3;
int ans,sum,cnt;
priority_queue<int,vector<int>,greater<int>>q;
signed main(){
	n=read(),m=read();
	while(n--){
		int op=read(),x=read();
		if(op==0) a[++n1]=x;
		if(op==1) b[++n2]=x;
		if(op==2) c[++n3]=x;
	}
	sort(a+1,a+n1+1),reverse(a+1,a+n1+1);
	sort(b+1,b+n2+1),reverse(b+1,b+n2+1);
	sort(c+1,c+n3+1),reverse(c+1,c+n3+1);
	for(int i=1;i<=n1;++i) q.push(a[i]),sum+=a[i];
	for(int i=0;i<=n3;++i){
		for(int j=cnt+1;j<=m && j<=cnt+c[i];++j){
			q.push(b[j]);
			sum+=b[j];
		}
		cnt+=c[i];
		while(!q.empty() && q.size()>m-i) sum-=q.top(),q.pop();
		ans=max(ans,sum);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 题意：

有 $N$ 个物品。

每个物品是以下三种之一：拉环罐头、普通罐头或开罐器。

第 $i$ 个物品由一个整数对 ($T_i$, $X_i$) 描述，如下所示：

- 如果 $T_i = 0$，则第 $i$ 个物品是一个拉环罐头；如果你获得它，你会得到 $X_i$ 的幸福值。
- 如果 $T_i = 1$，则第 $i$ 个物品是一个普通罐头；如果你获得它并使用开罐器打开它，你会得到 $X_i$ 的幸福值。
- 如果 $T_i = 2$，则第 $i$ 个物品是一个开罐器；它可以用来打开最多 $X_i$ 个罐头。

找出在 $N$ 个物品中获得 $M$ 个物品时的最大总幸福值。

### 思路：

~~有点儿水的 F 题……~~

提供一种 $O(n)$ 的思路，如果我们要选 $k$ 个拉环罐头，那么我们肯定尽量选幸福值前 $k$ 大的，选普通罐头也是。

如果直接这样去维护，肯定会 TLE，所以考虑使用前缀和，首先将拉环罐头的幸福值存入数组 $a$ 里面，普通罐头的幸福值存入数组 $b$ 里面，将开罐器的使用次数存入数组 $c$ 中。

我们设其中有 $l_1$ 个拉环罐头，$l_2$ 个普通罐头，$l_3$ 个拉罐器。首先将 $a,b,c$ 三个数组都从大到小排序，然后将 $a$ 数组的前缀和存入 $A$ 中，$b$ 数组的前缀和存入 $B$ 中。

这样可以保证选拉环罐头或者普通罐头的时候，幸福值是当前最大的，那么为什么要将可开罐次数从大到小排序呢？因为我们使用开罐器需要消耗一个物品的选择的，所以尽量从最大使用次数开始。

重点来了，如何找出在 $N$ 个物品中获得 $M$ 个物品时的最大总幸福值呢？

我们发现，可以通过枚举使用普通罐头的数量来确定答案，为什么呢？因为普通罐头与开罐器直接相关，设 $j$ 为当前选择的普通罐头数量。

因为可以不选普通罐头，所以 $j$ 从 $0$ 开始枚举到 $m$，现在在定义一个变量 $cnt$，表示总共可以开多少个普通罐头。

这个 $cnt$ 我们可以用一个 while 循环进行维护，定义一个 $c$ 数组的指针 $p$，从第一个数开始逐渐加到 $cnt$ 里面，只要 $cnt \ge j$ 或者指针指遍历完了，那么就退出循环。

因为之前我们将 $c$ 数组从大到小排序了的，所以这样可以保证可以选择最少的开罐器开 $j$ 个普通罐头，当然，如果所有开罐器的次数都加起来，还是小于 $j$ 的话，我们就开不了 $j$ 个普通罐头，就可以结束枚举。

否则，我们需要判断一下还剩下几个物品的选择，就可以选择拉环罐头。剩余的选择为 $k=m-p-j$，如果 $k < 0$，那么代表选多了，也退出枚举。

否则，我们就可以计算选择 $j$ 个普通罐头的最大幸福值，即 $ans=A_k+B_j$，最后我们只用输出 $ans$ 中的最大值即可。

注意一下如果 $k > l1$ 了， 前缀和如果只计算到了 $l1$ 就停止了的话，那么这个位置的值就是 $0$ 了，有两种解决方法，一种是将前缀和计算到 $m$ 这个位置，还有一种是如果 $k>l1$ 了，那么就直接加上 $A_{l1}$。

对于 $j > l2$ 也是可以用一样的处理方法。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200;
inline ll read(){ //快读 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){ //快输 
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll m,n,p,cnt,t,l1,l2,l3,ans=0,sum=0;
ll A[N],B[N],a[N],b[N],c[N];
int main(){
    n=read(),m=read();
    for(ll i=0;i<n;++i){
    	t=read(); 
        if(t==0)
		  a[l1++]=read();
        if(t==1)
          b[l2++]=read();
        if(t==2)
          c[l3++]=read();
    }
    sort(a,a+l1,greater<ll>());
    sort(b,b+l2,greater<ll>());
    sort(c,c+l3,greater<ll>());
    for(ll i=1;i<=l1;++i)
	  A[i]=A[i-1]+a[i-1];
    for(ll i=1;i<=l2;++i)
	  B[i]=B[i-1]+b[i-1];
    for(ll j=0;j<=m;j++){
        while(cnt<j&&p<l3){
            cnt+=c[p];
			p++;
        }
        if(cnt<j)
		  break;
        ll k=m-j-p;
        if(k<0)
		  break;
        ans=A[k<l1?k:l1]+B[j<l2?j:l2];
        sum=max(sum,ans); 
    }
    write(sum);
    return 0;
}
```


---

## 作者：ademik (赞：0)

#### 分析:

贪心。

由于拉片罐提供的贡献完全只和选择的数量有关，我们先不考虑拉片罐。对于剩下的两种罐头，我们完全可以贪心的选择，得到在选择 $i$ 个这两种物品时所能获得的最大的价值。对于每个 $i$，剩下的 $m - i$ 个额度都用来选择拉片罐，显然在降序排序求前缀和后可以快速得到最大的价值，最后将两者的价值相加取最大值即可。

#### Code :

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
typedef long long i64;
const int N = 2 * 1e5 + 50;
int n, m;
vector < int > a, b, c;
i64 x[N], y[N];
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n >>m;
	for(int i = 1, t, x; i <= n; i ++) {
		cin >>t >>x;
		if(t == 0) a.push_back(x);
		else if(t == 1) b.push_back(x);
		else c.push_back(x);
	}
	sort(a.begin(), a.end(), greater <> ());
	sort(b.begin(), b.end());
	sort(c.begin(), c.end());

	for(int i = 0; i < n; i ++) {
		if(i < a.size()) x[i + 1] = x[i] + a[i];
		else x[i + 1] = x[i];
	}
	int rr = 0;
	for(int i = 0; i < n; i ++) {
		if(b.empty()) y[i + 1] = y[i];
		else if(rr == 0) {
			if(!c.empty()) {
				rr += c.back();
				c.pop_back();
			}
			y[i + 1] = y[i];
		}	
		else {
			rr --;
			y[i + 1] = y[i] + b.back();
			b.pop_back();
		}
	}
	i64 ans = 0;
	for(int i = 0; i <= m; i ++) {
		ans = max(ans, 1ll * x[i] + y[m - i]);
	}
	cout <<ans <<endl;
	cerr <<TIME <<" ms" <<endl;
	return 0;
}
```

---

## 作者：WanderingTrader (赞：0)

upd on 2023-08-01：修复了 Markdown 的一些问题。

贪心+调整做法。

观察到同一类物品之间除了**价值**（开罐的幸福度或者钥匙的开罐数）以外没有别的差异，所以可以分别把三类物品排序。罐子按照幸福度从高到低排，钥匙按照开罐数从大到小排。

首先，我们按照从价值大到小的顺序，尽可能多的选择 0 类物品，假设数量为 $n_0$。如果 $n_0\ge m$，那么把前 $m$ 个 0 类物品选完即可。反之，则还有多余的物品栏。记 $rem$ 表示当前**无需新开钥匙就能打开的 1 类物品数**。如果 $rem=0$，那么就消耗一个物品栏，新开一把当前价值最大的钥匙，反之则消耗一个物品栏（同时让 $rem$ 减一），打开当前价值最大的 1 类物品，直到剩余的 $m-n_0$ 个物品栏全部耗尽为止。

以上过程结束后就形成了初始状态，将此时的幸福度记为 $ans$，并拷贝一份给一个临时变量 $t$ 备用。

接下来进行调整。每次我们先把已经打开的 0 类物品中价值最低的一个剔除，得到一个空闲的物品栏。接下来与上面类似。如果 $rem=0$，那么新开一把当前价值最大的钥匙，否则打开当前价值最大的 1 类物品，一直到不能再进行以上操作为止。每进行一步就更新所选罐子的价值和 $t$，同时与 $ans$ 比大小进行维护即可。

其中，“不能再进行以上操作”是指以下三种情况**之一**：

- 我们最初选出的 $n_0$ 或 $m$ 个 0 类物品已经全部被剔除，无法再开辟新的空闲物品栏。
- 所有的 1 类物品已经全部收入囊中，即使再剔除已有的 0 类物品也无法使得 $ans$ 更大。
- 所有的钥匙已经用完，**同时** $rem=0$，没有打开新的 1 类物品的权限。

注意第三点中的同时。如果忽略了 $rem=0$ 的条件，将会得到 42 个 AC 和 4 个 WA 的好成绩。

代码实现中首先在输入时进行分类处理。此处将 0,1,2 类物品分别存入 x,y,z 数组。然后分别从大到小排序：

```cpp
scanf("%d%d",&nTotal,&m);
for(int i=1,op,a;i<=nTotal;++i)
{
	scanf("%d%d",&op,&a);
	if(op==0) x[++nX]=a;
	else if(op==1) y[++nY]=a;
	else z[++nZ]=a;
}
sort(x+1,x+1+nX,greater<LL>());
sort(y+1,y+1+nY,greater<LL>());
sort(z+1,z+1+nZ,greater<int>());
```
接下来设置初始状态，开钥匙+用钥匙开罐的过程采用双指针 `iY,iZ`（其实是三指针，此处只用到了 `iY` 和 `iZ`）维护：
```cpp
int iX,iY,iZ;
if(m<=nX) //X类物品数量比m大 
{
	ans=tmp=accumulate(x+1,x+1+m,0LL);
	iX=m; iY=1; iZ=1; rem=0;
}
else
{
	ans=accumulate(x+1,x+1+nX,0LL);
	rem=0; iX=nX; iZ=1;iY=1;
	for(int i=nX+1;i<=m;++i) //通过开钥匙把剩余m-nX个空格填满 
	{
		if(!rem) rem=z[iZ++]; //开新钥匙
		else{ans+=y[iY++];--rem;} //开罐
	}
	tmp=ans;
}
```

由于 $m\le n$，不需要担心 `iZ` 或 `iY` 会越界。

注意初始化结束后 `iY,iZ,rem` 三个变量都不需要清零，因为等下的调整是直接基于初始状态进行的。

接下来采用三指针进行调整，注意边界条件：
```cpp
for(;(iZ<=nZ||rem>0)&&iX>=1&&iY<=nY;) //注意边界条件
{
	tmp-=x[iX--];
	if(!rem) rem=z[iZ++];
	else {tmp+=y[iY++];--rem;}
	ans=max(ans,tmp); //每剔除一个X物品都要取最大值
}
```
全部代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=2e5+5;
LL x[N],y[N],ans,tmp;
int z[N],nX,nY,nZ,nTotal,m,rem;
int main()
{
	scanf("%d%d",&nTotal,&m);
	for(int i=1,op,a;i<=nTotal;++i)
	{
		scanf("%d%d",&op,&a);
		if(op==0) x[++nX]=a;
		else if(op==1) y[++nY]=a;
		else z[++nZ]=a;
	}
	sort(x+1,x+1+nX,greater<LL>());
	sort(y+1,y+1+nY,greater<LL>());
	sort(z+1,z+1+nZ,greater<int>());
	int iX,iY,iZ;
	if(m<=nX)
	{
		ans=tmp=accumulate(x+1,x+1+m,0LL);
		iX=m; iY=1; iZ=1; rem=0;
	}
	else
	{
		ans=accumulate(x+1,x+1+nX,0LL);
		rem=0; iX=nX; iZ=1;iY=1;
		for(int i=nX+1;i<=m;++i)
		{
			if(!rem) rem=z[iZ++];
			else{ans+=y[iY++];--rem;}
		}
		tmp=ans;
	}
	for(;(iZ<=nZ||rem>0)&&iX>=1&&iY<=nY;)
	{
		tmp-=x[iX--];
		if(!rem) rem=z[iZ++];
		else {tmp+=y[iY++];--rem;}
		ans=max(ans,tmp);
	}
	printf("%lld\n",ans);
	return 0;
}
```

小彩蛋：一开始写的时候忘记在打开一个 Y 类物品后进行 `--rem` 操作了，也就是说只要打开一把钥匙就可以无限打开 Y 类物品，居然还通过了所有的三个样例和 12 个测试点。

可以看到主体部分由于采用了双指针，复杂度仅为 $O(n)$，瓶颈在于排序，总复杂度 $O(n\log n)$.

$$\text{The End.}$$

---

## 作者：FL_sleake (赞：0)

[传送门](https://atcoder.jp/contests/abc312/tasks/abc312_f)

好题，~~但是建议放E题位置~~

## 题目大意

有 $n$ 个物品，现要从中选 $m$ 个，物品分为  $3$ 类。

第 $1$ 类：直接使用，获得 $a_i$ 喜悦值。

第 $2$ 类：需要用第 $3$ 类物品打开，打开后获得 $a_i$ 喜悦值。

第 $3$ 类：可一共打开 $a_i$ 个第 $2$ 类物品。

求最大能获得的喜悦值。

## 解题思路

~~赛时想了个假的贪心~~

我们可以枚举第 $2$ 类物品的数量。考虑选 $x$ 个第 $2$ 类物品时需要多少个第 $3$ 类物品。显然这个可以通过处理一个前缀和二分得到。当第 $2$ 类和第 $3$ 类物品个数确定时，可以贪心地取第 $1$ 类物品。于是问题就解决了。

## 代码示例
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a0[200010],a1[200010],a2[200010];
int cnt0=0,cnt1=0,cnt2=0,ans=0;
int num0[200010],num1[200010],num2[200010];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int t,x;
		cin>>t>>x;
		if(t==0) a0[++cnt0]=x;
		else if(t==1) a1[++cnt1]=x;
		else a2[++cnt2]=x;
		//分三类 
	}
	sort(a0+1,a0+cnt0+1),sort(a1+1,a1+cnt1+1),sort(a2+1,a2+cnt2+1);
	
	for(int i=1;i<=cnt0/2;i++) swap(a0[i],a0[cnt0-i+1]);
	for(int i=1;i<=cnt1/2;i++) swap(a1[i],a1[cnt1-i+1]);
	for(int i=1;i<=cnt2/2;i++) swap(a2[i],a2[cnt2-i+1]);
	//倒转处理，先贪心地取最大的 
	
	for(int i=1;i<=cnt0;i++) num0[i]=num0[i-1]+a0[i]; 
	for(int i=1;i<=cnt1;i++) num1[i]=num1[i-1]+a1[i];
	for(int i=1;i<=cnt2;i++) num2[i]=num2[i-1]+a2[i];
	//预处理前缀和 
	
	for(int i=0;i<=cnt1;i++){
		if(i>num2[cnt2]) continue;//第3类物品不够
		int it=lower_bound(num2+1,num2+cnt2+1,i)-num2;
		if(i==0) it=0;
		if(i+it>m) continue;//超过m个
		int Max=min(m-i-it,cnt0);//没写这个多挂了一发。。。 
		ans=max(ans,num1[i]+num0[Max]);//取i个2类，Max个1类 
	}
	cout<<ans<<endl;
	return 0;
}
```

---

