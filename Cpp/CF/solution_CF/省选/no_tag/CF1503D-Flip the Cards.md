# Flip the Cards

## 题目描述

There is a deck of $ n $ cards. The $ i $ -th card has a number $ a_i $ on the front and a number $ b_i $ on the back. Every integer between $ 1 $ and $ 2n $ appears exactly once on the cards.

A deck is called sorted if the front values are in increasing order and the back values are in decreasing order. That is, if $ a_i< a_{i+1} $ and $ b_i> b_{i+1} $ for all $ 1\le i<n $ .

To flip a card $ i $ means swapping the values of $ a_i $ and $ b_i $ . You must flip some subset of cards (possibly, none), then put all the cards in any order you like. What is the minimum number of cards you must flip in order to sort the deck?

## 说明/提示

In the first test case, we flip the cards $ (1, 9) $ and $ (2, 7) $ . The deck is then ordered $ (3,10), (5,8), (6,4), (7,2), (9,1) $ . It is sorted because $ 3<5<6<7<9 $ and $ 10>8>4>2>1 $ .

In the second test case, it is impossible to sort the deck.

## 样例 #1

### 输入

```
5
3 10
6 4
1 9
5 8
2 7```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 2
3 4```

### 输出

```
-1```

## 样例 #3

### 输入

```
3
1 2
3 6
4 5```

### 输出

```
-1```

# 题解

## 作者：7KByte (赞：7)

首先如果存在一个卡片使得 $a_i,b_i\le n$，则一定无解。

> 证明：存在一张卡片 $a_i,b_i\le n$，根据抽屉原理一定存在另外一张卡片满足$a_j,b_j>n$，这两张卡片之间一定不满足条件

所以每一张卡片一定是一个 $\le n$ 的数和一个 $>n$ 的数，我们用 $f(i)$，表示和 $i$ 在卡片上对应的数，$c(i)$ 表示这张卡片使得较小数在前是否需要反转。

那么我们将所有卡片转换为 $i,f(i)$，$(1\le i\le n)$ 。

最终的答案一定是若干个 $\{i,f(i)\}$ 使得 $i$ 递增 $f(i)$ 递减，然后将剩下的数反转，将 $\{f(i),i\}$ 接在后面，使得 $f(i)$ 递增，$i$ 递减。

转换一下，就是将原按 $i$ 排序的序列拆成两个互补的子序列，满足子序列中 $f(i)$ 递减。

这就是一个经典贪心模型，我们开两个栈记录两个序列，贪心的将当前数放入栈顶较小的序列中。这样我们就可以判断是否有解。

但是我们还需要求出最优解，就存在一种情况，就是当前数两个序列都可以放进去，究竟放哪个栈更优？

结论：存在当前位置$i$，满足 $\min\limits_{1\le j\le i} f(j)>\max\limits_{i<j\le n}f(j)$，则可以将原序列断开成 $\le i$和 $>i$ 的两段，并将答案合并。

> 证明：我们将第一段中的答案，在 $\{i,f(i)\}$ 和 $\{f(i),i\}$ 中断开，放入第二个序列的答案，这是一定存在且唯一最优的答案。

所以如果存在这样的 $i$，分开计算。

那么在一段之中任何一个位置 $i$ ，它后面一定存在一个 $j$ 使得 $f(j)$ 大于当前两个栈中一个栈的栈顶。那么我们当前的 $f(i)$ 就一定只能放在栈顶较小的序列，这样就是唯一的。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,f[N],c[N],s[N];
int main(){
	scanf("%d",&n);
	rep(i,1,n){
		int x,y;scanf("%d%d",&x,&y);
		if(x>n&&y>n){puts("-1");return 0;}
		if(x<=n)f[x]=y,c[x]=0;else f[y]=x,c[y]=1;
	}
	int p=n+n+1,q=n+n+1,u=0,v=0,cu=0,cv=0,ans=0,now=n+n+1;
	pre(i,n,1)s[i]=max(s[i+1],f[i]);
	rep(i,1,n){
		now=min(now,f[i]);
		if(p>q)swap(p,q),swap(u,v),swap(cu,cv);
		if(f[i]<p)p=f[i],u++,cu+=c[i];
			else if(f[i]<q)q=f[i],v++,cv+=c[i];
				else {puts("-1");return 0;}
		if(now>s[i+1]){
			ans+=min(cu+v-cv,cv+u-cu);
			p=q=n+n+1,u=v=cu=cv=0;
		}
	}
	printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：hater (赞：7)

含泪复盘D题 /lb 。

首先有一个有解的必要条件：$a$和$b$不能同时小于$n$。

这个比较显然，因为一旦不满足上述条件，就会出现两个数都大于 $n$ 的情况 。 

这样一来不管怎么flip都不能使这两张卡片满足偏序条件 。 

那么一来，每个$1$到$n$的数，对应着$n+1$到$2n$的数 。 

记 $f_{i}$ 是$i$对应的数 。 

有解的充要条件是能把这个新序列分成两个单调下降的子序列 。 

这个感性理解一下也不难 。 

每种可能的解（不一定最优），都对应着唯一一种子序列划分方案 。

讲到这里一个log的做法就是大力dp，数据结构维护即可。

但是官方题解这个unique way真的非常巧妙，是线性做法。

$\min\limits_{j\le i} f_{j}>\max\limits_{j>i}f_{j}$ 若干个满足条件的下标i，将序列分成若干段，那么这几段有两个很好的性质。

一是序列划分方案是唯一的，二是这几个序列决策互不相干。

那么我们对每一段贪心即可。

我们分出两个子序列，只需要选代价小的那种方案。

但是有一种情况就是假如是序列单调的呢，那么只有一个序列了啊。

这种情况会将序列分成$n$段，每个数选或不选而已，也是正确的。

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
#define i60 long long 
#define dou double  
using namespace std ; 
const int N = 4e5+10 , inf = 1e7 ; 
int a[N] , cs[N] , pre[N] , suf[N] , n ; 
int len1 , len2 , b1[N] , b2[N] , c1 , c2 ;  
int calc( int l , int r ) { 
  len1 = len2 = 0 ; c1 = c2 = 0 ; 
  fp( i , l , r ) 
  	if( !len1 || b1[len1] > a[i] ) b1[++len1] = a[i] , c1 += cs[i] ; 
	else if( !len2 || b2[len2] > a[i] ) b2[++len2] = a[i] , c2 += cs[i] ; 
	else return -1 ; 
  return min( c1+len2-c2 , c2+len1-c1  ) ; 
}  
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  cin >> n ; bool flag = 0 ; 
  int x , y , ans = 0 , p , t ;   
  fp( i , 1 , n ) { 
    cin >> x >> y ; 
    if( x > y ) swap( x , y ) , cs[x] = 1 ; 
	a[x] = y ; flag |= ( y <= n ) ; 
  } 
  if( flag ) { cout << -1 << '\n' ; return 0 ; } 
  pre[0] = inf ; suf[n+1] = 0 ; 
  fp( i , 1 , n ) pre[i] = min( pre[i-1] , a[i] ) ; 
  fq( i , 1 , n ) suf[i] = max( suf[i+1] , a[i] ) ; 
  fp( i , 1 , n ) { 
    p = i ; while( pre[p] <= suf[p+1] ) p ++ ; 
    t = calc( i , p ) ; if( t == -1 ) { flag = 1 ; break ; } 
	ans += t ; i = p ;  
  } 
  if( flag ) ans = -1 ; cout << ans << '\n' ; 
  return 0 ; 
} 
```

Q : 这个傻逼怎么抄管解，粘公式，代码也像。/baojin

A : 别问 ， ~~问就是水~~ ， 问就是搬运。

#### upd 4.5 : 式子写锅了 /yun 。 

---

## 作者：__Seniorious__ (赞：3)

[我也不知道更好还是更坏的阅读体验](https://cyb1010.github.io/2023/11/29/%E5%85%B6%E4%BB%96/%E6%9D%82%E9%A2%98%E4%B9%B1%E5%81%9A3/#CF1503D-Flip-the-Cards)
## [CF1503D Flip the Cards](https://www.luogu.com.cn/problem/CF1503D)

~~因为写太长了决定投洛谷。~~ 写的很烂，求轻喷。。   
首先，不能同时有 $a_i\le n,b_i\le n$，因为这样就会存在另一组 $a_j>n,b_j>n$，这两组显然构不成题目中的偏序关系。

钦定原序列中 $a_i,b_i$ 中较小的为 $c_i$，较大的为 $d_i$，我们发现答案序列肯定是一个前缀 $k$ 对所有 $1\le i\le k$ 满足交换后 $a_i\le n,b_i>n$，对所有 $k<i\le n$ 满足 $a_i>n,b_i\le n$，即 $c$ 序列单峰， $d$ 序列单谷。  
考虑将原序列按 $c$ 升序排序，答案序列相当于将这个序列撕成两个按 $d$ 降序的子序列，再拼起来。

此时应该可以一车 $\log$ 用 ds 优化 dp 了，但是有优秀而好写的线性做法。我们对排序后的 $d$ 序列做前缀 $\min$ 和后缀 $\max$，如果存在 $\min\limits_{i=1}^kd_i>\max\limits_{j=k+1}^nd_j$，则前后两个部分互不干扰，因此我们将这样的段分开来做。然后，我声称这样的段划分方案是唯一的，因此直接划分，然后分类讨论分成的哪一段翻转即可，写法非常简单。

关于为什么是唯一的：  
假设分出的一段是 $[l,r]$，则 $d_l$ 一定不是区间 $\max$，不然会单独划分为另一段。假设区间 $\max$ 的位置为 $m$，如果区间合法，则 $[l,m)$ 区间必然满足 $d$ 单调递减，且划分时这些必然都划分到 $l$ 所在的一段。  
若 $m$ 不为 $r$，我们的划分保证存在 $m<n\le r$ 使得 $d_{m-1}<d_n$，因此区间 $[m,n]$ 内所有 $d_i\ge d_n$ 的 $i$ 都选入 $m$ 序列，其余选入 $l$ 序列。  
然后我们发现刚才的性质可以继续扩展，即：若 $n<r$，则存在 $p$ 使得 $d_p>\min\limits_{i=l}^nd_i$，因此区间 $[n,p]$ 内所有 $d_i\ge d_p$ 的 $i$ 都选入 $m$ 序列……  
于是我们发现划分方案是唯一的。

[$\texttt{code}$](https://www.luogu.com.cn/record/137413671)

```cpp
/**
 * @author : cyb1010
 * @date   : 2023-11-29 16:10:49
 * @file   : Flip_the_Cards.cpp
 */
#include <bits/stdc++.h>
using namespace std;
#define fo(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)
#define fi first
#define se second
typedef double db;
typedef long double ldb;
typedef long long ll;
typedef unsigned long long ull;
int __, n, val[200010], flip[200010], mx[200010], ans;
int solve(int l, int r) {
    int len1 = 0, len2 = 0, b1 = n + 1, b2 = n + 1, c1 = 0, c2 = 0;
    for (int i = l; i <= r; i++)
        if (b1 > val[i])
            b1 = val[i], len1++, c1 += flip[i];
        else if (b2 > val[i])
            b2 = val[i], len2++, c2 += flip[i];
        else
            printf("-1\n"), exit(0);
    return min(len1 - c1 + c2, len2 - c2 + c1);
}
int main() {
    // fo("Flip_the_Cards");
    scanf("%d", &n);
    for (int i = 1, f = 0, a, b; i <= n; i++, f = 0) {
        scanf("%d%d", &a, &b);
        if (a > b) swap(a, b), f = 1;
        if (a > n || b <= n) return printf("-1\n"), 0;
        val[a] = b - n, flip[a] = f;
    }
    for (int i = n; i; i--) mx[i] = max(mx[i + 1], val[i]);
    for (int i = 2, lst = 1, mn = val[1]; i <= n + 1; i++)
        if ((mn = min(mn, val[i - 1])) > mx[i])
            ans += solve(lst, i - 1), lst = i;
    printf("%d\n", ans);
    return 0 ^ __ ^ 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

结论：有解的必要条件是每张牌一面的数 $\le n$，另一面的数 $>n$。

否则，必然存在一张牌两面都 $\le n$，另一张牌两面都 $>n$，必定无解。

我们认为 $\le n$ 的那一面为正面。

一部分牌正面朝上，正面数递增反面数递减；另一部分反面朝上，正面数递减反面数递增，也相当于正面数递增反面数递减。

因此原题转化为：将正面排序后得到一个序列，将其划分为两个递减的子序列，每个数划分到两个子序列中有一定的代价。

“判定是否存在解”很典，开两个栈，每次贪心的放到栈顶更小的栈后面（如果可以的话）。若要加上最优化，可以使用线段树优化 DP 解决（记录当前数所在栈，以及上一个属于另一个栈的数的位置）

学习了题解区中一个有趣的线性做法。我们关心的是“如果当前数两个栈都塞得下怎么办？”

假设正面为 $i$ 的数反面是 $a_i$。如果 $\min_{1 \le j \le i} a_j > \max_{i < j \le n} a_j$，那么称 $i$ 为关键点。下面证明：相邻两个关键点 $(p_1,p_2]$ 间的答案是唯一的。

这是因为，每次栈里头必有一个是前缀最小值。当新加入的一个点是前缀最小值时，它就有两种选择。这时由于后面必存在一个数（可以证明，前缀最小值不会是最后一个数，除非这段就一个数）大于它，也大于旧的前缀最小值，因此新的前缀最小值只能替换旧的前缀最小值。也就是唯一的。

而我们划分的每一段，他们之间都是毫不相干的，直接拼一起就可以了：因此把每一段的最小答案加在一起即可。

所以容易做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,ans,a[MAXN],b[MAXN],f[MAXN],flg[MAXN],pre[MAXN],suf[MAXN];
int solve(int l,int r) {
	int val=0;
	stack<int> st1,st2;
	ffor(i,l,r) {
		if(st1.empty()||st1.top()>f[i]) val+=flg[i],st1.push(f[i]);
		else if(st2.empty()||st2.top()>f[i]) val+=1-flg[i],st2.push(f[i]);
		else {cout<<-1;exit(0);}
	}
	return min(val,r-l+1-val);
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i]>>b[i];
	ffor(i,1,n) {
		if(min(a[i],b[i])>n||max(a[i],b[i])<=n) return cout<<-1,0;
		if(a[i]<=b[i]) f[a[i]]=b[i];
		else f[b[i]]=a[i],flg[b[i]]=1;	
	}
	pre[1]=f[1];
	ffor(i,2,n) pre[i]=min(pre[i-1],f[i]);
	suf[n]=f[n];
	roff(i,n-1,1) suf[i]=max(f[i],suf[i+1]);
	vector<int> kp;
	kp.push_back(0);
	ffor(i,1,n) if(pre[i]>suf[i+1]) kp.push_back(i);
	ffor(i,1,kp.size()-1) ans+=solve(kp[i-1]+1,kp[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：MadokaKaname (赞：0)

傻逼 2600，但我是傻逼，~~虽然 duel 赢了（~~

没看懂题解都在写什么，感觉我的做法比较神秘？

-----

不妨直接钦定包含 1 的卡片的 1 这面为正面，因为如果答案 $ans>  \left\lfloor{\dfrac{n}{2}}\right\rfloor$ 时可直接改变为 $n-ans$。

因此我们考虑贪心的从小往大安排卡片，取一个中间所有没有被选的所有卡片中的一个极值来对另一端进行贪心。这么做复杂度显然是 $O(n)$ 的。

考虑这么做把序列分成了若干个区间。对此我们考虑维护一个前面的 $\min$ 和 $\max$，答案即是 $\min (val_{min},n-val_{max})$。

而对于所有区间来讲，当前的最小卡片正反情况可以发现并不用关心。因此直接做就是对的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
struct point{
	LL x,y;
}a[1000005];
LL n,i,j,k,m;
LL id[1000005];
bool flag[1000005];
bool vis[1000005];
LL cmp(point x,point y){
	return x.x<y.x;
} 
int main(){
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].x,&a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)
	  id[a[i].x]=i,id[a[i].y]=-i;
	LL minx=0,maxx=0;
	LL nowl=0,nowr=2*n+1;
	while(1){
		if(nowl==nowr-1) break;
		LL tmp=id[nowl+1];
		LL val,stat,tmp1;
		LL sum=0;
		LL prel=nowl,prer=nowr;
		if(tmp>0) val=a[tmp].y,stat=1,nowl++,tmp1=0;
		else val=a[-tmp].x,stat=1,nowl++,tmp1=1;
		while(1){
			if(stat==0){ 
				if(val==nowl+1){
					nowl++;break;
				}
				LL minx1=0x7fffffff;
				for(j=nowl+1;j<val;j++){
					if(vis[abs(id[j])]==true){
						printf("-1");
						return 0;
					}
					if(flag[abs(id[j])]==true) continue;
				    if(a[abs(id[j])].x>a[abs(id[j])].y && tmp1==0) sum++;
				    if(a[abs(id[j])].x<a[abs(id[j])].y && tmp1==1) sum++;
					vis[abs(id[j])]=true;flag[abs(id[j])]=true;
					LL val1=max(a[abs(id[j])].x,a[abs(id[j])].y);
				    if(val1>minx1){
				    	printf("-1");
				    	return 0;
					}
					minx1=min(minx1,val1);
				} 
				for(j=nowl+1;j<val;j++)
				  vis[abs(id[j])]=false;
				nowl=val;
				if(minx1==0x7fffffff) break;
				val=minx1;stat^=1;
			}
			else{
				if(val==nowr-1){
					nowr--;break;
				}
				LL maxx1=0;
				for(j=nowr-1;j>val;j--){
					if(vis[abs(id[j])]==true){
						printf("-1");
						return 0;
					} 
					if(flag[abs(id[j])]==true) continue;
					if(a[abs(id[j])].x<a[abs(id[j])].y && tmp1==0) sum++;
					if(a[abs(id[j])].x>a[abs(id[j])].y && tmp1==1) sum++;
					vis[abs(id[j])]=true;flag[abs(id[j])]=true;
					LL val1=min(a[abs(id[j])].x,a[abs(id[j])].y);
					if(val1<maxx1){
						printf("-1");
						return 0;
					}
					maxx1=max(maxx1,val1);
				}
				for(j=nowr-1;j>val;j--)
				  vis[abs(id[j])]=false;
				nowr=val;
				if(maxx1==0) break;
				val=maxx1;stat^=1;
			}
		}
		LL len=(prer-nowr)+(nowl-prel);
		len>>=1;
		minx=minx+min(len-sum,sum),maxx=maxx+max(len-sum,sum);
	}
	printf("%lld",min(n-maxx,minx));
	return 0;	  
}
```

---

## 作者：yllcm (赞：0)

首先简单转化一下模型：把 $2n$ 个数排成一排，其中 $a_i$ 和 $b_i$ 构成匹配对。现在需要把这个序列染成 A 和 B 两种颜色，要求从左到右第 $i$ 个 A 颜色位置匹配从左到右第 $n-i+1$ 个 B 颜色匹配位置。

不妨钦定第一个位置是 A 颜色，那么与它匹配的位置 $m_1$ 一定是第 $n$ 个 B 颜色，也就是说对于所有 $i>m_1$ 的位置，它的颜色一定是 A 颜色，那么这些颜色和颜色对应的排名也是可以确定的，那么找到最后一个 A 颜色并将它匹配位置之前的所有位置染成 A 颜色（因为需要保证与它匹配的 B 颜色是第一个 B 颜色），重复这样做直到没有扩展出新的点。观察到未扩展出的点是一个区间，那么可以定义 $f_{l,r}$ 表示 $[l,r]$ 区间内的点没有扩展到的最优答案，每次枚举第一个位置的颜色进行转移，可以得到一个朴素的 $\mathcal{O}(n^2)$ DP。

但是可以发现这个 DP 的决策实际上比较憨憨，因为把第一个位置换一种颜色的效果实际上就是把所有扩展到的点反色，所以说只要跑一遍然后讨论是否反色即可。复杂度是线性的。

不过还要判无解，事实上如果实现一下就可以发现扩展过程中一个点的匹配点可能已经被其它点染过色了，如果某个点的匹配点已经被染过色，并且它和它的匹配点同色就表明无解。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define FR first
#define SE second
using namespace std;
inline int read() {
    int x = 0; bool op = 0;
    char c = getchar();
    while(!isdigit(c))op |= (c == '-'), c = getchar();
    while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return op ? -x : x;
}
const int N = 1e6 + 10;
int n, ans, L, R;
int mat[N], ty[N], pt[N], fr[N];
pii a[N];
bool bfs(int st) {
    queue<int> q; q.push(st); ty[st] = 0; fr[st] = 0;
    int cnt = 0, res = 0;
    while(q.empty() == false) {
        int u = q.front(); q.pop();
        if(ty[mat[u]] != -1) {
            if(ty[mat[u]] == ty[u]) {
                return false;
            }
            continue;
        }
        A.pb(u); A.pb(mat[u]);
        ty[mat[u]] = ty[u] ^ 1; cnt++; res += (ty[u] ^ pt[u]);
        if(fr[u] == 0) {
            while(R >= 1 && ty[R] != -1)R--;
            for(int i = R; i > mat[u]; i--) {
                ty[i] = ty[u]; fr[i] = 1; q.push(i);
            }
        }
        else {
            while(L <= n && ty[L] != -1)L++;
            for(int i = L; i < mat[u]; i++) {
                ty[i] = ty[u]; fr[i] = 0; q.push(i);
            }
        }
    }
    ans += min(res, cnt - res);
    return true;
}
int main() { 
    n = read();
    for(int i = 1; i <= n; i++) {
        int x = read(), y = read();
        mat[x] = y; mat[y] = x; pt[x] = 0; pt[y] = 1;
    }
    memset(ty, -1, sizeof(ty));
    L = 1; R = (n << 1);
    for(int i = 1; i <= (n << 1); i++) {
        if(ty[i] == -1) {
            if(bfs(i) == false)return printf("-1"), 0;
        }
    }
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：luogubot (赞：0)

首先有 $(a_i,b_i)$ 里面应该有一个 $\leq n$ 和一个 $>n$ 的，否则最终一定不合法。接下来默认 $a_i<b_i,a_i=i$。

考虑最终 $a$ 序列由一段 $\leq n$ 的前缀和 $>n$ 的后缀拼接，$b$ 序列由一段和 $a$ 前缀长度相同的 $>n$ 的前缀和 $\leq n$ 的后缀拼接，于是前缀后缀是独立的，讨论一下非法的情况。

一个直觉是如果 $a_i<a_j,b_i<b_j$ 的对是特殊的，但是发现我们如果把 $i,j$ 不同时丢到前缀和后缀就不会出现问题，那么我们在这样的 $i,j$ 之间连边，最终得到的如果是二分图就可以在每个连通分量中选择代价较少的一边作为答案，否则不合法，于是得到了一个 $O(n^2)$ 的做法。

考虑当 $i<j<k,(i,j),(j,k)$ 边都存在时，那么 $(i,k)$ 之间也有边，则形成了一个奇环，就无解了。那么每个点不能同时存在向前和向后的连边。

另外一个暴力做法是从前往后先扫一遍，维护一个 `std::set`，对于 $i$ 找到 $j<i,b_j<b_i$ 的 $j$，并把 $i,j$ 连边，标记 $j$ 只能有出边，$i$ 只能有入边。如果出现类型非法的边那么就无解了。同样的从后往前扫一遍。这样就得到了所有的边。

观察到我们需要的信息并不是所有的边，而是每个点属于哪个连通分量，于是在从前往后加边之后就可以把 `set` 中第二个元素到 $j$ 全部删掉，从后往前加边之后就把 `set` 中 $j$ 到倒数第二个元素删掉，均摊就对了。正确性显然，相当于合并了 $j$ 这个前缀/后缀到一起。

时间复杂度 $O(n\log n)$，[提交记录](https://codeforces.com/contest/1503/submission/159981926)。



---

