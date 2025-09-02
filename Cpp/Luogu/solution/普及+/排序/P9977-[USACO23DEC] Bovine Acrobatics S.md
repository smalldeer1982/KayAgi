# [USACO23DEC] Bovine Acrobatics S

## 题目描述

Farmer John 决定让他的奶牛表演杂技！首先，FJ 为他的奶牛称重，发现她们有 $N$（$1\le N\le 2\times 10^5$）个不同的体重。具体来说，对于全部的 $i\in [1,N]$，有 $a_i$ 只奶牛的体重为 $w_i$ 单位（$1\le a_i\le 10^9, 1\le w_i\le 10^9$）。

他最出名的节目需要奶牛叠成**平衡的奶牛塔**。一座**奶牛塔**是一些奶牛，每只奶牛站在下一只奶牛身上。一座奶牛塔是**平衡的**，当且仅当每一只被踩着的奶牛，都比**直接**踩在它身上的那只奶牛重至少 $K$（$1\le K\le 10^9$）单位。每只奶牛都可以成为奶牛塔的一部分。

如果 FJ 想要创造最多 $M$（$1 \le M \le 10^9$）座奶牛塔，最多有多少只奶牛可以成为奶牛塔的一部分？

## 说明/提示

### 样例解释 1

FJ 可以用体重为 $5,7,9$ 的奶牛创造四座平衡的奶牛塔，再用体重为 $5,7$ 的奶牛创造另一座。

### 样例解释 2

FJ 可以用体重为 $5,9$ 的奶牛创造四座平衡的奶牛塔，再用体重为 $7$ 的一只奶牛创造另一座。或者，他可以用体重为 $5,9$ 的奶牛创造四座平衡的奶牛塔，再用体重为 $5$ 的一只奶牛创造另一座。

### 测试点性质

- 测试点 $3-5$ 满足 $M \le 5000$ 且奶牛的总数不超过 $5000$。
- 测试点 $6-11$ 满足奶牛的总数不超过 $2\cdot 10^5$。
- 测试点 $12-17$ 没有额外限制。


## 样例 #1

### 输入

```
3 5 2
9 4
7 6
5 5```

### 输出

```
14```

## 样例 #2

### 输入

```
3 5 3
5 5
7 6
9 4```

### 输出

```
9```

# 题解

## 作者：Little_x_starTYJ (赞：17)

### 解题思路
这道题目代码很短，但是思路很难想。

我们先按照奶牛重量排序，不难想到，最重奶牛一定要放在奶牛塔的最底层，只有这样我们才能保证奶牛数目最大，然后向上搭上第一头满足 $w_{top}-w_i\geq k$ 的奶牛，以此类推。

然后我们就会发现，这就是贪心，于是记录当前的 $m$ 表示这头牛可以搭在多少座塔上，那么我们就可以知道，实际符合要求的放下的奶牛的头数是 $\min(m,a_i)$ 头。

当我们将奶牛搭在塔上后，会有 $\min(m,a_i)$ 个塔的塔顶被修改，也就是说，这几个塔有可能还可以继续搭下一头奶牛，也有可能不可以搭下一头奶牛，所以我们还需要再次统计一下可以搭的塔的数量。

我们又要想想怎么快速统计可以搭的塔的数量。首先，当 $m\ge a_i$ 时有 $m-a_i$ 个塔可以搭奶牛。既然有 $\min(m,a_i)$ 个塔是搭过当前重量的奶牛的，那么我们把这些塔一起处理，如果 $w_{top}-w_{i + 1}\geq k$，那么这些塔都是可以继续搭奶牛的，如果塔顶连重量较小的奶牛都搭不上，那么我们没有必要再找下去了。

AC CODE:

```c
#include <stdio.h>
#include <algorithm>
struct node {
	int a, b;
} c[200010];
bool cmp(node a, node b) {
	return a.b < b.b;
}
int ans[200010], id = 1;
long long res;
int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &c[i].b, &c[i].a);
	std::sort(c + 1, c + 1 + n, cmp);
	for (int i = 1; i <= n; i++) {
		while (id < i && c[i].b - c[id].b >= k)
			m += ans[id++];
		ans[i] = m < c[i].a ? m : c[i].a; //系统自带的min有点慢
		m -= ans[i], res += ans[i];
	}
	printf("%lld", res);
	return 0;
}
```

---

## 作者：_qingshu_ (赞：11)

# 思路：

首先我们可以知道这个塔正着放还是倒着放对于答案是没有影响的，所以我们可以假定这个塔是倒着来的。

对于每一头牛来说，如果这头牛有位置可以放，那么是一定会选择放这一头牛的。我们可以分为两种情况来证明：

- 如果这一头牛是塔顶。

	也就是说这一头牛是这一个塔上体重最大的，放了也不会对于其他塔以及后面的抉择有任何影响，还可以赚得 $1$ 贡献，何乐而不为？
    
- 如果这一头牛非塔顶。
	
    说明还有比他重的在后面，可以想一下，连比他重的都可以放，那么他体重更轻，对于后续抉择来说一定不会更劣。
    
那么这就是一个比较基本的贪心问题了。

---

考虑记录当前的 $m$ 为这一头牛有多少个塔是可以放的，那么我们知道实际可以放下的头数是 $\min(m,a_i)$，这个是容易证明的。

在放下牛之后也会有 $\min(m,a_i)$ 个塔的塔顶被更改，也就是说这几个塔能否继续叠放是不确定的，我们需要再次统计一下可以叠放的塔的个数。

然后考虑如何快速统计。首先前面一头牛可以放但是来不及放的也就是当 $m\ge a_i$ 时有 $m-a_i$ 个塔可以直接确定可以继续叠放。既然有 $\min(m,a_i)$ 个塔的塔顶是在这一轮更新过的，那么我们把他们归为一类，如果现在这个牛的重量比 $a_i$ 大，那么这些塔都是可以的，再从之前更新的大类往现在的扫，如果塔顶比较小的都放不了那完全是可以跳出的。

总体难在思路，代码并不复杂。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
struct _qingshu_{
    int a,w;
}c[5200010];
bool cmp(_qingshu_ x,_qingshu_ y){
    return x.w<y.w;
}
int tot=1,qa[5200010];
long long ans;
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>c[i].w>>c[i].a;
    }
    stable_sort(c+1,c+n+1,cmp);
    for(int i=1;i<=n;i++){
        while(tot<=i-1&&c[i].w-c[tot].w>=k){
            m+=qa[tot++];
        }
        qa[i]=min(m,c[i].a);
        m-=qa[i];
        ans+=qa[i];
    }
    cout<<ans;
}
```

update：

---

## 作者：tanghg (赞：9)

首先发现将这个塔翻转一下结果不会改变。

之后先按照体重排个序。然后我们有一个贪心策略是优先放体重小的在当前的 $M$ 座塔上，并且在当前的 $M$ 座塔上能放的可以随便放。这就是我们排序的作用，之后的体重更大，当前能放的之后所有奶牛肯定都能放，所以不存在“让位”的说法。

之后用一个小根堆去维护塔顶重量相同的组数即可。维护每一个塔顶重量和它有几个塔。然后从小到大考虑和替换即可。
```cpp
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const ll MAXN=2e5+5;
ll n,m,k;
struct node{
    ll w,num;
    bool operator<(const node&K)const{
        return w>K.w;
    }
}a[MAXN];
priority_queue<node>q;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i].w>>a[i].num;
    }
    sort(a+1,a+n+1);
    q.push({-100000000000,m});
    ll ans=0;
    for(int i=n;i>=1;--i){
        ll v=0;
        while(!q.empty()){
            node t=q.top();
            q.pop();
            if(t.w+k>a[i].w){
                q.push(t);
                break;
            }
            if(t.num>=a[i].num){
                ans+=a[i].num;
                q.push(a[i]);
                if(t.num>a[i].num){
                    t.num-=a[i].num;
                    q.push(t);
                }
                break;
            }
            v+=t.num;
            ans+=t.num;
            a[i].num-=t.num;
        }
        if(v){
            q.push({a[i].w,v});
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：zsyzsy_2012 (赞：5)

思路清新的贪心思维题。

首先，易证一个结论：倒换一个奶牛塔不影响答案。其次，我们可以得到一个朴素的贪心思路：把奶牛从小到大按体重排序，对于每个塔我们存塔顶，用小根堆存塔，然后遍历奶牛，遇到能放的塔就立刻放。用这种做法，我们可以通过三个测试点。

然后考虑优化。我们容易发现这道题的复杂度瓶颈包括塔数太大了。我们发现，塔顶奶牛的数量有可能重复。所以，我们可以把塔顶相等的塔当作一类存，并记录每一类塔的数量。我们可以通过九个测试点。

继续优化。我们发现如果朴素的执行上述做法，可能会有很多塔顶相同的同类项没有合并。相继取出的两个塔顶相差最小，如果发现相等，我们可以立即合并。这种做法可以通过本题。

下面给代码。一些详细注释在代码里了。

```
#include "bits/stdc++.h"
#define int long long//十年OI一场空，不开LL见祖宗
#define N 200010
using namespace std ;
const int inf = (int)1e18 ;
struct node {
	int w , num ;
	bool operator <(const node &cmp)const{
		return w > cmp.w ;
	}
}s[N];
priority_queue<node>q ;//小根堆
signed main() {
	int n , m , k , ans = 0 ;
	scanf("%lld%lld%lld" , &n , &m , &k) ;
	for(int i = 1 ; i <= n ; i++) {
		scanf("%lld%lld" , &s[i].w , &s[i].num) ;//INPUT
	}
	sort(s + 1 , s + 1 + n) ;//排序
	q.push((node){-inf , m}) ;//初始化，负无穷可以表示没有这个塔
	for(int i = n ; i ; i--) {
		while(q.size()) {
			node t = q.top() ;
			q.pop() ;
			if(q.size()) {
				node p = q.top() ;
				if(t.w == p.w) {
					q.pop() ;
					q.push((node){t.w , t.num + p.num}) ;
					continue ;//合并同类项
				}
			}
			q.push(t) ;
			if(s[i].w >= t.w + k) {
				q.pop() ;
				ans += min(s[i].num , t.num) ;
				if(s[i].num >= t.num) {
					q.push((node){s[i].w , t.num}) ;
					s[i].num -= t.num ;
					if(s[i].num == 0) break ;
				}//一些基本操作
				else {
					q.push((node){s[i].w , s[i].num}) ;
					q.push((node){t.w , t.num - s[i].num}) ;
					break ;
				}
			}
			else {
				break ;
			}
		}
	}
	printf("%lld" , ans) ;//OUTPUT
	return 0 ;
}
```


---

## 作者：naoliaok_lovely (赞：5)

看了一圈，很多人都用了小根堆？

## 分析
首先肯定要对身高排序，后面处理方便一点。

考虑新加入一个奶牛。容易想到，如果我们可以选择它，那一定是要选择它的。证明也很简单，后续的奶牛都比他高，那么既然我们选择了后面的那只奶牛，为什么不选择当前这一只呢？既然都可以选择，肯定是选择当前这个造成的限制小。因为接在它后面的奶牛要至少大 $k$ 嘛。

于是这个东西可以直接使用单调队列维护。记录 $m$ 表示当前有几座塔可以添加奶牛，不能添加奶牛的塔丢进队列里。  
时间复杂度 $O(n\log n)$，瓶颈在于排序。
```
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define PII pair<int, int>

const int N = 2e5 + 10;
int n, m, k;
PII x[N];
LL ans;
LL q1[N], q2[N], hh = 1, tt;

int main()
{
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) scanf("%d%d", &x[i].first, &x[i].second);
	sort(x + 1, x + n + 1);
	
	for(int i = 1; i <= n; i++)
	{
		while(hh <= tt && x[i].first - q1[hh] >= k) m += q2[hh++];
		q1[++tt] = x[i].first, q2[tt] = min(x[i].second, m), m -= q2[tt], ans += q2[tt];
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：kczw (赞：4)

# 题意
有 $n$ 种奶牛，每一种奶牛有重量 $w$ 和数量 $a$。

现在有一个规则，可以最多放置 $m$ 堆奶牛，奶牛可以重叠，但是上面的奶牛必须比下面的奶牛重量少 $k$。

问最多摆放多少奶牛。

# 思路
我们使用贪心的思路。

题目说从大往小地放置，但是想想就可以知道，从小往大来算也是可以的。

其次，易得，假如有重 $a$ 和 $a-1$ 的两头牛,我们从小往大地去找定然是选择 $a-1$，因为这样下一次选择我们就可以选择从 $a+k-1$ 开始选择，否则就要从 $a+k$ 往上去选择，明显的，择更小的重量可以获得更广的选择牛的重量的范围（当然，如果你选择从大往小去选择，择更大的是更优的策略）。

然后我们注意到这个数据的范围 $n\le2\times10^5$ 并且 $a,w,m\le10^9$，所以我们不只能简单地去贪心，而是要一点算法上的优化。

我们发现，不同种的牛是多种的，而如果我们从小往大地去枚举，那么按照我们贪心的整体思路，一定是要尽量多放的，所以我们可以用一个变量去存储可以放置当前这一种奶牛的堆的数量。

说到堆的数量，会发现它可以达到 $10^9$，所以我们这里需要一种特殊的方式去存储这些不同的堆。

联想到上面对于放置的优化，会发现，每一次的放置都会更新一波一定范围内的堆顶牛的重量，那我们可以对于每一种牛的放置都存储它存放的个数，那么只要把可以放的堆顶牛的所有种类所占的堆的个数加起来，就是可以放的位置了。然后就可以反复更新每一种牛的放置结果，最后得出答案。
# 代码
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int ans,n,m,k,t,num[200005];
pair<int,int> a[200005];
signed main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].first,&a[i].second);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        while(t<=i-1&&a[i].first-a[t].first>=k)m+=num[t++];
        num[i]=min(a[i].second,m);
        m-=num[i];
        ans+=num[i];
    }printf("%lld",ans);
    return 0;
}
```

---

## 作者：听取MLE声一片 (赞：4)

考虑暴力，动态维护奶牛塔当前最底层的重量。

但是不可能维护每个奶牛塔，考虑对底层重量相同的奶牛塔进行合并。具体的，动态维护奶牛塔最底层的重量以及这样的个数，这样总个数是 $O(n)$ 的。

用一个堆来维护（小根堆），对体重从小到大排序，初始时把最小重量的奶牛全部放入奶牛塔。顺序枚举体重，如果能放在目前的底部就放，直到放完或没有奶牛塔可以放。如果遇到相同的就直接合并。

总元素个数为 $O(n)$，时间复杂度 $O(n\log n)$。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#include<random>
#define int long long
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
const int inf=1e9;
int n,m,k,ans;
priority_queue<pii>q;
struct node{
	int x,y;
}a[N];
int cmp(node a,node b){
	return a.x<b.x;
}
signed main()
{
	n=read(),m=read(),k=read();
	q.push(mkp(inf,m));
	for(int i=1;i<=n;i++)
		a[i].x=read(),a[i].y=read();
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		int x=a[i].x,y=a[i].y,res=0;
		while(!q.empty()){
			pii ret=q.top();
			q.pop();
			int u=-ret.fi,v=ret.se;
			if(x-u<k){
				q.push(ret);
				break;
			}
			if(v>=y){
				q.push(mkp(-x,y));
				ans+=y;
				if(v-y)q.push(mkp(-u,v-y));
				break;
			}
			res+=v;
			ans+=v;
			y-=v;
		}
		if(res)q.push(mkp(-x,res));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ダ月 (赞：4)

凭什么这题这么难，感觉很水，难度远小于 T2，T3。半个小时就整出来了。

首先，考虑一个贪心，我们依次考虑每个奶牛塔。我们首先加入当前拥有的最轻的奶牛，然后加入体重大于等于最轻奶牛体重加上 $K$ 的奶牛一只，然后不断加入大于等于上一只奶牛的体重加 $K$ 的奶牛。直接做，时间复杂度：$O(N\sum a_i)$。

一个一个考虑太慢了。我们不妨 $M$ 个奶牛塔一起考虑。我们依次考虑重量为 $w_i$ 的奶牛，我们设当前手头闲置的奶牛塔有 $m$ 个。我们可以获得 $\min(m,a_i)$ 的贡献，此时有 $\min(m,a_i)$ 的奶牛塔不再闲置，但是这 $\min(m,a_i)$ 的奶牛塔在 $w_i+K$ 这个体重时起又闲置了，我们只用在 $w_i+K$ 这个体重处打个大小为 $\min(m,a_i)$ 的标记即可。

因此，具体的，我们考虑将 $w_i$ 和 $w_i+K$ 丢在一起离散化。对于每个体重 $i$（注意，下面的 $a_i$ 代表体重为 $i$ 的奶牛的个数。），我们设当前手头闲置的奶牛塔有 $m$ 个，显然 $m$ 加上继承过来的标记，然后将 $m$ 减去 $\min(m,a_i)$，答案加上 $\min(m,a_i)$，$i+K$ 处打上大小为 $\min(m,a_i)$ 标记。时间复杂度：$O(n\log n)$。$m$ 初始为 $M$。

代码如下：

```
void solve(){
	int n,m,K;
	IO::cin>>n>>m>>K;
	ve<std::pair<int,int>>v(n);
	for(auto &p:v)IO::cin>>p.first>>p.second;
	std::sort(all(v));
	ve<int> b;
	for(int i=0;i<n;i++)b.pd(v[i].first),b.pd(v[i].first+K);
	std::sort(all(b));b.erase(std::unique(all(b)),b.end());
	for(auto &p:v)p.first=std::lower_bound(all(b),p.first)-b.begin(); 
	std::vector<ll> c(b.size()+10),D(b.size()+10);
	for(auto &p:v)c[p.first]+=p.second;
	ll rs=m/*rs 就是题解中的 m，m 是题解中的 M*/,ans=0;
	for(int i=0;i<=b.size();i++){
		rs+=D[i];
		int d=std::min(c[i],rs);
		ans+=d;c[i]-=d;rs-=d;
		D[lower_bound(all(b),b[i]+K)-b.begin()]+=d;
	}
	std::cout<<ans<<'\n';
}
```


是不是我脑回路太新奇，T1 过了 T2，T3 没过。




---

## 作者：Zi_Gao (赞：4)

> 题意：
>
> 给你 $n$ 种牛，每种牛有 $a_i$ 个，同种牛的重量都相同为 $w_i$，现在牛要叠牛塔，每座牛塔都是由若干个牛叠成，并且要求相邻两头牛在上面和下面的重量分别为 $a,b$，要求满足 $a\leq b+k$ 其中 $k$ 是给定常数。现在要叠 $m$ 做牛塔，问最多由多少头牛参与叠塔。
>
> $n\leq 3\cdot 10^5$ 并且 $a_i,b_i\leq 10^9$

我猜你在想 `dp`，实际上这个题很像是一个 `dp` ，我一开始也这样想的，但是做不出来。放开思路，不妨考虑贪心，先按照牛种类的重量从大到小排序，依次考虑，并且维护当前有多少座牛塔可以往上叠设为 $m$，贪心地想现在 $v_i$ 头牛要尽可能的叠上去，那么肯定会选出 $\min\left(v_i,m\right)$ 头牛放在可以堆叠的塔顶上，然后 $m$ 减少 $\min\left(v_i,m\right)$。如何实现呢？先按照 $w_i$排序，然后双指针，一个指针 $i$ 指着当前考虑的牛种类，另一个指针 $j$ 指着比当前牛种类重量大 $k$ 的重量的牛种类，对于每个牛种类记录选中了多少个放在塔顶 $cho_i=\min\left(v_i,m\right)$，并且 $m$ 减去 $cho_i=\min\left(v_i,m\right)$。然后考虑挪动另一个指针，若能挪动说明这个种类的牛以成为的塔顶的 $cho_j$ 个塔，已经可以被现在的牛拿去继续叠了，所以 $m$ 加上 $cho_j$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

struct COW{
    int w,v;
    bool operator < (const COW o) const{
        return (w==o.w)?(v<o.v):(w<o.w);
    }
}cows[500010];

int dp[500010];

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    #endif

    register int i,j,ans=0;
    int n=read();
    int m=read();
    int k=read();

    for(i=1;i<=n;++i){
        cows[i].w=read();
        cows[i].v=read();
    }

    std::sort(cows+1,cows+1+n);

    for(i=n,j=n+1;i;--i){
        while(cows[j-1].w-cows[i].w>=k) m+=dp[--j];
        ans+=(dp[i]=std::min(m,cows[i].v));
        m-=dp[i];
    }

    print(ans);

    #ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    #endif
    return 0;
}
```


---

## 作者：heyx0201 (赞：1)

# P9977 [USACO23DEC] Bovine Acrobatics S 题解
## Des.
> 给定 $N,M,K$，还有 $N$ 个整数 $w_i, a_i$，要把其中一些数加入一些集合中，每个集合中相邻的数最小差为 $K$，求最多有多少个数可以在集合中。

## Sol.
本题提供 $2$ 种**正解**思路，还有 $2$ 种暴力思路，但只提供一种正解代码。

万物之始：按 $w$ 从小到大排序。

### PtSol. 1 (Test 3-5) 纯暴力，无优化
$5000$ 头奶牛，$M \le 5000$，考虑暴力。

对于每头奶牛，每次在已有的塔中找一个重量符合要求的塔底，任意一个符合要求的塔均可以。没有塔符合要求时新建一个塔。但是新建塔时应该判断是否可以添加（塔数 $\le M$）。

时间复杂度 $O(M \sum \limits_{i=1}^{N} a_i)$。

### PtSol. 2 (Test 3-11) 优先队列优化
现在有了 $2 \times 10^5$ 头奶牛，PtTk. 1 中可以使用优先队列（小根堆）优化 "每次在已有的塔中找一个重量符合要求的塔底"，因为最小的塔底是最优的。

时间复杂度 $O(\sum \limits_{i=1}^{N} a_i \log(\sum \limits_{i=1}^{N} a_i))$。

### AcSol. 1 优先队列正解
可以对同一塔底重量的塔一起处理，即维护相同重量的塔的数量，在优先队列中状态就是（重量，数量）。

叠塔时，也是对每种奶牛处理，而不是对每头奶牛处理。

时间复杂度 $O(N \log N)$。

### AcSol. 2 单调队列
奶牛已经排序过了，每个塔的塔底的重量具有单调性，所以可以用单调队列。

时间复杂度同 AcSol. 1。

## Cod.
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;

struct Node {
  int w, a;
} a[MAXN];

int n, m, k;
queue<pair<int, int>> q;

bool cmp(const Node &i, const Node &j) {
  return i.w < j.w;
}

int main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].w >> a[i].a;
  }
  sort(a + 1, a + n + 1, cmp);
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    for (; !q.empty() && q.front().first + k <= a[i].w; q.pop()) {
      m += q.front().second;
    }
    int v = min(a[i].a, m);
    q.push({a[i].w, v});
    m -= v, ans += v;
  }
  cout << ans;
  return 0;
}
// 此为 AcSol. 2 实现。
```

---

## 作者：快斗游鹿 (赞：1)

## 思路

显然，从重量最小的牛开始放肯定不劣。考虑维护一个 $k$ 表示当前第 $i$ 头牛有 $k$ 个塔可以放，那么实际能放入的牛数就是 $\min(k,a_i)$。这一轮没有被影响的位置有 $k-\min(k,a_i)$ 个。考虑被影响的这些位置什么时候能再次被启用，因为重量已经排序，所以遇到 $a_j\ge a_i+k$ 时，这些塔又可以放了，用双指针就可以了。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
struct Node{
	int w,a;
}e[N];
int n,m,k,num[N],ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bool cmp(Node xxx,Node yyy){
	return xxx.w<yyy.w;
}
signed main(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)e[i].w=read(),e[i].a=read();
	sort(e+1,e+1+n,cmp);
	int l=1;
	for(int i=1;i<=n;i++){
		while(l<=n&&e[i].w-e[l].w>=k)m+=num[l],l++;
		num[i]=min(m,e[i].a);
		m-=num[i];
		ans+=num[i];
	}
	cout<<ans;
}

```


---

## 作者：MoyunAllgorithm (赞：1)

S 组最难题，可以评蓝。现有的题解都写得略显简略，我在参考官方题解后给出了一篇更为详细且包括部分分做法的题解。

## 形式化题意

给你一个序列 $c$，用 $N(1 \le N \le 2 \times 10^5)$ 个二元组表示。第 $i$ 个二元组  $(w,n)(1 \le w,n \le 10^9)$ 表示 $c$ 数组中有 $n$ 个数的权值为 $w$。

将 $c$ 从小到大排序后，你需要构造 $M(1 \le M \le 2 \times 10^5)$ 个 $c$ 的单调递增子序列，且满足相邻两项权值的差至少为 $K(>0)$，且这些子序列中不包含公共元素（但值可以相同）。最大化这 $M$ 个子序列的长度和。

## 分析

不妨先不管为什么用这种奇怪的方式输入 $c$ 数组。不如直接在 $c$ 数组上先思考暴力。

将 $c$ 从大到小排序，目前 $M$ 个子序列是空的。从大到小，对于 $c$ 的每个元素 $c_i$：

- 找到 $M$ 个子序列中，首项（也就是最小的那一项）最大的一个。如果该首项仍然小于 $c_i+K$，则不作改动；否则将 $c_i$ 插到该子序列的开头，作为它的首项。

时间复杂度是 $O(|c|M)$。

考虑证明其正确性。

- 首先，只要 $c_i$ 能被插入，那必然可以插入到首项最大的。这是显然的。

- 而且，只要 $c_i$ 能被插入，那插入它是不劣的。假如不插入它而插入一个更轻的，那会给接下来的插入作出更多限制。

得证。

事实上，你可以用堆、单调队列等数据结构，优化“找首项最大的子序列”这一操作。只需要在这类数据结构中存储这些子序列的首项，每次查询最值即可。可以将时间复杂度优化为 $O(|c|+M)$ 或者 $O(|c| \log M)$。

然而在本题中，$|c|$ 可以达到 $2 \times 10^{14}$，但是 $N$ 只有 $2 \times 10^5$。我们考虑如何恰当地结合二元组的输入方式解决本问题。

我们把所有二元组 $(w,n)$ 按照 $w$ 从大到小排序。之后，我们从大到小枚举权值 $i \in [1,10^9]$。令 $\text{rest}$ 表示目前有多少个子序列的首项 $\ge i+K$。

- 如果该权值被打了标签（至于标签是什么，看下一条），则 $\text{rest}$ 加上该标签；

- 如果目前的权值 $i$ 在 $c$ 中存在，那么设对应的二元组为 $p$。则根据上面的贪心策略，我需要将 $\operatorname{min}(\text{rest},p_n)$ 个子序列的前头插入一个 $i$。之后，不管还有多少个是 $i$ 的元素在 $c$ 中，我都不能插了，因为 $K>0$。设 $\text{use}=\operatorname{min}(\text{rest},p_n)$。将 $\text{rest}$ 减去 $\text{use}$；**在 $i-K$ 处打上 $\text{use}$ 的标签**。

通过打标签的形式，我使得无论在什么时候，$\text{rest}$ 都准确地表示了当前可用的队列数量，而不用每次都找。

如何打标签？如何优化枚举权值 $i$ 的过程？非常简单：把所有 $w$ 和 $w-K$ 都离散化就行。

时间复杂度为 $O(N \log N)$。

具体见代码。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2e5+5;
struct Cows
{
    int w,n;
    bool operator<(const Cows &j) const
    {
        return w<j.w;//这里我还是从小到大排序了。因为在这里我通过从大到小枚举权值，代替了权值从大到小枚举元素。从小到大排序易于 lower_bound 查找。但你也可以从大到小排序之后指针维护。
    }
}c[MAXN];
int N,M,K;
int tot=0;
int wei[MAXN<<1],tag[MAXN<<1];//注意：我需要将权值-K也离散化，因此要开两倍空间
LL ans=0;
int main()
{
    scanf("%d %d %d",&N,&M,&K);
    for(int i=1;i<=N;i++)
    {
        scanf("%d %d",&c[i].w,&c[i].n);
        wei[++tot]=c[i].w;
        wei[++tot]=c[i].w-K;
    }
    sort(wei+1,wei+tot+1);
    tot=unique(wei+1,wei+tot+1)-wei-1;
    for(int i=1;i<=N;i++) c[i].w=lower_bound(wei+1,wei+tot+1,c[i].w)-wei;//离散化
    sort(c+1,c+N+1);
    int rest=M;
    for(int i=tot;i;i--)
    {
        rest+=tag[i];//加标签
        int p=lower_bound(c+1,c+N+1,(Cows){i,0})-c;//当前权值是否是 c 中权值
        if(c[p].w!=i) continue;
        int use=min(rest,c[p].n);
        ans+=use;
        rest-=use;//如果是，进行一系列上述操作
        tag[lower_bound(wei+1,wei+tot+1,wei[i]-K)-wei]+=use;
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：_radio_ (赞：0)

# p9977 [USACO23DEC] Bovine Acrobatics S 题解
## 题意
有一些奶牛，它们有 $n$ 种体重，第 $i$ 种奶牛体重为 $a_i$，数量为 $b_i$。

农夫想将这些奶牛堆成 $m$ 座奶牛塔，一座奶牛塔是好的，当且仅当对于所有 $i$，第 $i+1$ 层的奶牛比第 $i$ 层的奶牛轻 $k$ 以上。

请问最多能堆成多少座好的奶牛塔？
## 思路
**part 1**

可以放奶牛时放不放？

答案是一定要放，原因如下：我们知道，在排序后越靠后的奶牛越轻，可以放当前这一头，一定可以放后面的。但对于最大化答案而言，最好的方案是将尽可能重的奶牛放在塔顶，理由也很简单：为了接下来可以放尽可能多的多奶牛。

**part 2**

模拟的基本思路？

记录 $p_i$ 为排序后第 $i$ 头奶牛放的头数，$m$ 为可以放的头数。所以，$p_i=\min(b_i,m)$。用 $ans$ 记录答案的总和即可。

**part 3**

如何统计 $m$？

每次统计 $p_i$ 时，用 $m$ 减去 $p_i$，表示当前的奶牛占据了 $p_i$ 的位置，应从 $m$ 中删除。相应的，奶牛的体重会增加，因此要在每次计算 $p_i$ 前统计新增的合法的 $m$。

如果你觉得过于抽象，无法理解，可以看这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/b6wva96e.png)

计算 $11$ 时，$m$ 初始值为灰色部分和第 $i$ 层的蓝色部分，原因为灰色部分奶牛的重量大于 $13$，在计算 $12$ 时就已经被考虑，而第 $i$ 层的蓝色部分为 $m$ 的初始值中未被减去的部分。

计算 $m$，此时 $13$ 满足条件，红色部分加入 $m$。

计算 $p_i$，由于体重为 $11$ 的奶牛无法满足所有 $m$，$13$ 在灰线以后的部分在 $m-p_i$ 后被保留。

计算 $10$，绿色部分加入 $m$。计算 $p_i$，由于体重为 $10$ 的奶牛数量大于等于 $m$，所以 $m$ 全部被占用，$m$ 归零。

**part 4**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,cnt,p[200010],ans;
struct node{
	int x,y;
}a[200010];
bool cmp(node p,node q){
	return p.x>q.x;
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		while(cnt<i&&a[cnt+1].x-a[i].x>=k) m+=p[++cnt];
		p[i]=min(a[i].y,m);
		m-=p[i];
		ans+=p[i];
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：__HHX__ (赞：0)

# 思路
## 前提
我们先将每种奶牛的重量排序（从重到轻），时间复杂度 $O(N \log N)$。

为了让大家更清晰的算法时间复杂度，我将不会算排序时间复杂度到时间复杂度。
## 思路一（贪心+暴力的暴力）（25分）
枚举每头奶牛，遇到能加入的平衡塔就加入。

时间复杂度 $O(M\sum a_i)$。
## 思路二（贪心+暴力的优先队列）（55分）
枚举每头奶牛，加入的最小平衡塔。

时间复杂度 $O(\sum a_i \log \sum a_i)$。
## 思路三（贪心+优化的优先队列）（100分）
我们可以发现，同种的奶牛可以进行批量处理。

所以我们可以在加一个属性：数量。

时间复杂度 $O(N \log N)$。
## 思路四（贪心+单调队列）（100分）
我们可以发现，每次叠成的塔底重量有单调性。

所以不难想到单调队列。

时间复杂度 $O(N)$。

所以在不考虑排序的情况下，思路四最优，所以我只给思路四代码（~~就是剩下三种我不想写~~）。
# 代码
```cpp
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 2e5 + 3;

const long long Max = 1e18 + 3;

struct Node {
  long long w, v;
} a[N];

deque<Node> qwq;

long long n, m, k;

int main() {
  long long ans = 0;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].w >> a[i].v;
  }
  sort(a + 1, a + n + 1, [](Node x, Node y) { return x.w > y.w; } );
  qwq.push_back({Max, m});
  for (int i = 1; i <= n; i++) {
    Node t = qwq.front(), tk = {a[i].w - k, 0};
    while (qwq.size() && a[i].v >= t.v && a[i].w <= t.w) {
      ans += t.v;
      tk.v += t.v;
      a[i].v -= t.v;
      qwq.pop_front();
      if (qwq.size()) t = qwq.front();
    }
    if (a[i].w <= t.w && qwq.size()) {
      ans += a[i].v;
      tk.v += a[i].v;
      qwq.pop_front();
      t.v -= a[i].v;
      qwq.push_front(t);
    }
    qwq.push_back(tk);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

一开始没有奶牛的 $m$ 个可以直接看成 $m$ 个最上面是重量 $\infty$ 的奶牛的塔，然后考虑重量从大到小叠加，每次叠加选择一个可以接受 $a_i + k$ 重量的以 $w_j$ 为顶的塔 $j$ 即可，如果塔数量不够再找一些即可，之后再把用掉的 $a_i$ 存储进入。  
此时需要一种数据结构，支持插入和删除指定元素，支持查询 $\geq$ 某个值的元素，选择你喜欢的进行维护，我用的 `set`。

发现空间/时间爆了，原因是因为 $m=10^9$，最多有 $10^9$ 个同时存在，肯定炸空间时间了，但是由于重量只有 $n$ 种，所以把每种重量暂存起来统一入 `set` 就可以解决。

```cpp
#define pii pair<int, int>
pii a[201010];
signed main() {
	int n = read(), m = read(), k = read(), ans = 0;
	for (int i = 1; i <= n; ++i) {
		read(a[i].first, a[i].second);
	}
	set<pii> st;
	sort(a + 1, a + 1 + n);
	st.insert({1e18, m});
	for (int i = n; i; i--) {
		auto x = st.lower_bound({a[i].first + k, 0});
		int cnt = 0;
		while (x != st.end()) {
			pii _ = *x;
			st.erase(x);
			if (_.second >= a[i].second) {
				cnt += a[i].second;
				_.second -= a[i].second;
				a[i].second = 0;
			} else {
				cnt += _.second;
				a[i].second -= _.second;
				_.second = 0;
			}
			if (_.second > 0) st.insert(_);
			if (a[i].second <= 0) break;
			x = st.lower_bound({a[i].first + k, 0});
		}
		ans += cnt;
		st.insert({a[i].first, cnt});
	}
	write(ans, '\n');
	return 0;
}
```

---

