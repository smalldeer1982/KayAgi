# Recover it!

## 题目描述

Authors guessed an array $ a $ consisting of $ n $ integers; each integer is not less than $ 2 $ and not greater than $ 2 \cdot 10^5 $ . You don't know the array $ a $ , but you know the array $ b $ which is formed from it with the following sequence of operations:

1. Firstly, let the array $ b $ be equal to the array $ a $ ;
2. Secondly, for each $ i $ from $ 1 $ to $ n $ : 
  - if $ a_i $ is a prime number, then one integer $ p_{a_i} $ is appended to array $ b $ , where $ p $ is an infinite sequence of prime numbers ( $ 2, 3, 5, \dots $ );
  - otherwise (if $ a_i $ is not a prime number), the greatest divisor of $ a_i $ which is not equal to $ a_i $ is appended to $ b $ ;
3. Then the obtained array of length $ 2n $ is shuffled and given to you in the input.

Here $ p_{a_i} $ means the $ a_i $ -th prime number. The first prime $ p_1 = 2 $ , the second one is $ p_2 = 3 $ , and so on.

Your task is to recover any suitable array $ a $ that forms the given array $ b $ . It is guaranteed that the answer exists (so the array $ b $ is obtained from some suitable array $ a $ ). If there are multiple answers, you can print any.

## 样例 #1

### 输入

```
3
3 5 2 3 2 4
```

### 输出

```
3 4 2 ```

## 样例 #2

### 输入

```
1
2750131 199999
```

### 输出

```
199999 ```

## 样例 #3

### 输入

```
1
3 6
```

### 输出

```
6 ```

# 题解

## 作者：HMZHMZHMZ (赞：3)

## 题意
给定一个数组 $ b $ ,它可以由以下几种方式构成
1. 把 $ a $ 数组中的元素加入 $ b $ 中
2. 如果 $ a_i $ 是一个质数，那么把第 $ a_i $ 个质数加入 $ b $ 中
3. 如果 $ a_i $ 是一个合数，那么把 $ a_i $的最大因子(不等于 $ a_i $ )加入 $ b $ 中

要求求出原数组 $ a $

------------
## 思路
对于 $ b $ 中的元素，我们做以下几个考虑
1. 如果 $ a_i $ 是一个合数，那么它要么是 $ a $ 中的元素，要么是 $ a $ 中某一元素的最大因子。对于这一部分，我们可以把所有合数排序一遍，从大到小考虑。当我们枚举到一个没有被使用过的合数时，它显然在原数组 $ a $ 中，那么我们把它的最大因子打上标记，当遍历到他的最大因子时就不会计入总答案。

2. 如果 $ a_i $ 是一个质数，那么它要么是 $ a $ 中的元素，要么是 $ a $ 中的元素所产生的质数。有一个显然的结论，对于所有 $ a_i $ ，都有 $ prime_{a_i}> a_i $ 。所以可以把质数从小往大排，每一次判断它是否被访问过，如果未被访问过，那么它显然是 $ a $ 中的元素，并把 $ prime_{a_i} $ 打上标记。

3. 然后就是代码实现的问题了。。。代码在下方。

------
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
const int maxn=3e6+10;
int prime[N],cnt,n,a[N],sum[maxn],ans[maxn],p;
bool g[maxn],used[N];
inline void init(){
	for(register int i=2;i<=2750131;++i){//线性筛模板，不会的可以去看P3383,这里不细讲
		if(!g[i]) prime[++cnt]=i;
		for(register int j=1;j<=cnt&&i*prime[j]<=2750131;j++){
			g[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	g[1]=1;
}
inline int read(){
	int s=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while(ch<='9'&&ch>='0'){
		s=(s<<3)+(s<<1)+(ch^48);
		ch=getchar();
	}
	return s;
}
inline int fnd(int x){//用来找最大因子的函数
	if(x%2==0) return x/2;
	for(register int i=3;i*i<=x;i+=2) if(x%i==0) return x/i;
	return -1;
}
int main(){
	init();
	n=read();
	n<<=1;//因为输入的是原数组的两倍，所以n要*2
	for(register int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+n+1);//把整体从小往大排
	for(register int i=n;i>=1;--i){//从大的合数往小的合数枚举
		if(!g[a[i]]||used[i]) continue;//如果不是合数或者已经被用过了就continue
		ans[++p]=a[i];//将当前数推入答案中
		int s=fnd(a[i]);//寻找它的最大因子
		int l=lower_bound(a+1,a+n+1,s)-a+sum[s];//lower_bound找到它最大因子的位置，把它打上标记
		used[l]=used[i]=1;
		sum[s]++;//sum[i]记录有多少个i被使用过，方便找下标
	}
	for(register int i=1;i<=n;++i){//处理质数
		if(used[i]) continue; 
		int l=lower_bound(a+1,a+n+1,prime[a[i]])-a+sum[prime[a[i]]];//找到它所产生的下一个质数
		used[l]=used[i]=1;//跟合数的处理方法相同，打上标记并记录位置
		sum[prime[a[i]]]++;
		ans[++p]=a[i];//将当前数推入答案中
	}
	for(register int i=1;i<=p;++i) printf("%d ",ans[i]);//愉快的输出答案
	return 0;
}
```


---

## 作者：米奇 (赞：3)

## 思维题

首先我们发现，从长度为n的串，变成长度为
2*n的串。由于每个数最多变出一个数，所以对于2*n的串中的每个数，要么选，要么选能变成它的数。

相当于一条链a->b->c->d......

我们选a，不选b，选c，不选d

那我们就找出关系，一选一不选即可

先O(n)欧拉筛筛出每个数会变成那个数

由于要变成上面说的链的情况，所以我们把所有数排一下序，使其成链状即可

怎么排序：
发现如果是质数，那么一定变大，所以质数是从小到大排

如果不是质数，那么一定变小，所以合数从大到小排

由于合数能变成质数，而质数不能变成合数，所以合数在前，质数在后。

## 代码：
```cpp
#pragma GCC opertime(2)
#pragma GCC opertime(3)
#include<bits/stdc++.h>
using namespace std;
const int N=2750133;
int n,cnt,a[N],b[N],prim[N],vis[N],xu[N];
void work(int n)
{
 	for(int i=2;i<=n;i++)
    {
        if(!vis[i])prim[++cnt]=i;
        for(int j=1;j<=cnt;j++)
        {
            if(i*prim[j]>n)break;
            vis[i*prim[j]]=1;
            xu[i*prim[j]]=i;
            if(i%prim[j]==0)break;
        }
    }
}
bool cmp(int a,int b)
{
    if(vis[a]==0)
    {
        if(vis[b]==0)return a<b;
        else return 0;
    }
    if(vis[b]==0)
    {
        return 1;
    }
    return a>b;
}
int main()
{
    work(2750131);
    cin>>n;
    for(int i=1;i<=2*n;i++)
    {
        scanf("%d",&a[i]);
        b[a[i]]++;
    }
    sort(a+1,a+2*n+1,cmp);
    for(int i=1;i<=2*n;i++)
    {
        if(b[a[i]])
        {
            printf("%d ",a[i]);
            b[a[i]]--;
            if(vis[a[i]]==0&&a[i]<=cnt)b[prim[a[i]]]--;
            if(vis[a[i]])b[xu[a[i]]]--;
        }
    }
}
```

---

## 作者：wucstdio (赞：3)

蛮有意思的一道题。

首先考虑$a$是如何变到$b$的。

1、如果$a_i$是一个质数，那么它会变成它自己和一个比它大的质数。

2、如果$a_i$是一个合数，那么它会变成它自己和一个比它小的数。

想明白了这件事，做法就出来了：

首先将$b$中的元素按照质数和合数分类，然后合数从大到小枚举，每枚举到一个数就删掉它除以它最小的质因子。

然后质数从小到大枚举，没枚举到一个数就删掉$prime[a[i]]$。

容易发现，对于每一个不合法的数，都会在枚举到对应的$a_i$的时候被删除，所以这个做法是正确的。

当然需要加上一个线性筛，时间复杂度是$O(n\log n)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
int n,prime[5000005],a[500005],b[500005],mind[5000005],num,top1,top2;
bool flag[5000005];
map<int,int>s;
void pre(int n)
{
	flag[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!flag[i])
		{
			prime[++num]=i;
			mind[i]=i;
		}
		for(int j=1;j<=num&&prime[j]*i<=n;j++)
		{
			flag[i*prime[j]]=1;
			mind[i*prime[j]]=min(mind[i],prime[j]);
			if(i%prime[j]==0)break;
		}
	}
}
int main()
{
	pre(5000000);
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++)
	{
		int x;
		scanf("%d",&x);
		if(flag[x])b[++top2]=x;
		else a[++top1]=x;
	}
	sort(b+1,b+top2+1);
	sort(a+1,a+top1+1);
	for(int i=top2;i>=1;i--)
	{
		if(s[b[i]])
		{
			s[b[i]]--;
			continue;
		}
		printf("%d ",b[i]);
		s[b[i]/mind[b[i]]]++;
	}
	for(int i=1;i<=top1;i++)
	{
		if(s[a[i]])
		{
			s[a[i]]--;
			continue;
		}
		printf("%d ",a[i]);
		s[prime[a[i]]]++;
	}
	printf("\n");
	return 0;
}
```

---

## 作者：nynkqh_yzp (赞：1)

考虑当前最大的数。

如果是质数，那么，这个质数不在 $a$ 中，可以产生这个质数的质数在 $a$ 中。因为如果这个质数在 $a$ 中，那么就会产生更大的质数，不符合，这个质数也不可能是由合数产生的，否则这个合数更大。

如果是合数，那么这个合数在 $a$ 中，可以被这个合数产生的数不在 $a$ 中，因为如果这个合数不在 $a$ 中，那么它只能由更大的合数产生，不满足这个合数是最大数。
```
#include <bits/stdc++.h>
using namespace std;
int n,cn[300900],cnt,m=2750151,a[500900],f[3800900],q[3800900];
bool v[3800900],vv[500900];
vector<int>ss[3800900];
int main(){
	v[0]=v[1]=1;
	for(int i=2;i<=m;i++){
		if(v[i]==0)
			cn[++cnt]=i;
		for(int j=1;j<=cnt&&i*cn[j]<=m;j++){
			v[i*cn[j]]=1;
			if(q[i*cn[j]]==0)
				q[i*cn[j]]=i;
			if(i%cn[j]==0)
				break;
		}
	}
	scanf("%d",&n);
	n*=2;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		if(v[a[i]]==0){
			if(a[i]<=199999)
				f[cn[a[i]]]=a[i];
		}
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		ss[a[i]].push_back(i);
	for(int i=n;i>0;i--)
		if(vv[i]==0){
			if(v[a[i]]==1){
				printf("%d ",a[i]);
				vv[i]=1;
				ss[a[i]].pop_back();
				vv[ss[q[a[i]]].back()]=1;
				ss[q[a[i]]].pop_back();
			}
			else{
				printf("%d ",f[a[i]]);
				vv[i]=1;
				ss[a[i]].pop_back();
				vv[ss[f[a[i]]].back()]=1;
				ss[f[a[i]]].pop_back();
			}
		}
	return 0;
}
```


---

## 作者：Nightingale_OI (赞：1)

这道题有很多种方法与证明，这里只提供一种思路。

在 $ b $ 中从大往小考虑：

1. 如果目前最大的是质数，那么它一定不在 $ a $ 中，并且可以找到产生它的数（显然第 $ i $ 个质数比 $ i $ 大）。

2. 如果目前最大的是合数，那么它一定在 $ a $ 中，并且也可以找它到产生的数（不然它无法由任何数产生来）。

3. 已经确定是否存在的数要记得从 $ b $ 中删除。

那么我们可以把 $ b $ 中的数用一个桶记录下来，再从大往小跑一遍即可。

------------

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
int a[2750132],b[2750132],c[2750132],pri[200000];
bool ip[2750132];
inline void ycl(int n){//3e6建议线筛，不用也可
    int pc=0;
	for(register int i=2;i<=n;i++)ip[i]=true;
	for(register int i=2;i<=n;i++){
		if(ip[i])b[i]=pri[++pc]=i;
		for(int j=1;j<=n;j++){
			if(pri[j]>n/i)break;
            b[i*pri[j]]=pri[j];//最小（质）因子
			ip[i*pri[j]]=false;
			if(i%pri[j]==0)break;
		}
	}
    for(register int i=1;i<=pc;++i)a[pri[i]]=i;//每个质数的排名
}
int main(){
	ycl(2750131);
    cin>>n;
    for(register int i=1;i<=n*2;++i){
        scanf("%d",&m);
        ++c[m];//每个数的出现次数
    }
    m=0;
    for(register int i=2750131;i;--i){
        while(c[i]--){
            if(ip[i]){
                --c[a[i]];
                printf("%d ",a[i]);
            }else{
                --c[i/b[i]];
                printf("%d ",i);
            }
        }
    }
	return 0;
}
```

---

## 作者：llqqhh (赞：0)

# cf1176d Recover it!

可以试着考虑再当前序列中最大的数。

若这个数是质数，那么它一定不属于 $a$ 序列。因为任何一个 $p_{a_i}$ 一定都大于 $a_i$（~~这点显然吧~~），当前这个数又是最大的质数，所以它一定是被生成的，我们只需要找到这个质数的下标，并将下标在 $b$ 数组中删除即可。

若这个数是合数，那么它一定属于 $a$ 序列。因为任何一个合数的最大因子一定小于这个合数，而这个数是当前序列中最大的数，那么它一定不可能是从别的合数生成出来的。

上述过程中的删除和找最大值可以用 ``multiset`` 来维护。

上代码：

```cpp
#include<bits/stdc++.h>
#define mk make_pair
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5+10, M = 2e7+10;
int n, a[N], tot;

int prime[M], mpri[M], idx, rnk[M];
void sieve() {//素数筛，prime[i]表示第i个质数，mpri[i]表示i的最小质因子，rnk[i]表示i这个质数是第几个质数
    for(int i = 2; i <= 2e7; i ++) {
        if(mpri[i] == 0) prime[++ idx] = i, mpri[i] = i, rnk[i] = idx;
        for(int j = 1; j <= idx && i * prime[j] <= 2e7; j ++) {
            mpri[i * prime[j]] = prime[j];
            if(i % prime[j] == 0) break;
        }
    }
}

int main() {
    sieve();
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    multiset<int> b;
    for(int i = 1, x; i <= n << 1; i ++) {
        cin >> x;
        b.insert(x);
    }
    while(b.size()) {
        int u = *b.rbegin();//找到最大的数
        if(mpri[u] == u) {//若当前数是质数
            int v = rnk[u];
            a[++ tot] = v;
            b.erase(b.find(v));//删除质数的排名
            b.erase(b.find(u));//删除当前数
        } else {//若当前数是合数
            a[++ tot] = u;
            b.erase(b.find(u / mpri[u]));//删除最大因子
            b.erase(b.find(u));//删除当前数
        }
    }
    for(int i = 1; i <= tot; i ++)
        cout << a[i] << ' ';
    return 0;
}
```

---

## 作者：__LiChangChao__ (赞：0)

## 思路
分质数和合数？考虑**分类讨论**。

显然的是：

* 对于一个目前最大的合数，其必然出现在数组 $a$ 中，因为其不可能是现有任意一个数的因数。

* 对于一个目前最大的质数，其必然不是在数组 $a$ 中，因为其不能映射成其他任意一个质数。

那我们怎么统计这些数有没有在之前的操作中使用过呢？使用桶来统计。

对数组排序后从后往前筛，筛到一个数时，若其在桶中有值，则分情况：

* 是合数，其最大的质因子在桶中的值减去 $1$。

* 是质数，其质数排名（第几个质数）在桶中的值减去 $1$。

然后将这个数输出即可。

注意：在筛质数的时候，我们还可以统计一下最大的因子，否则如果在要用的时候 $O(\sqrt n)$ 计算会超时。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxp=4e6+5,maxn=4e5+5;
long long prime[maxn],n,ans[maxn],a[maxn],b[maxp],s[maxp],cnt,num;
int p[maxp];
bool g[maxp];
inline void init() {
	for(int i=2; i<=2750132; ++i) {
		if(!g[i]) prime[++cnt]=i;
		for(int j=1; j<=cnt&&i*prime[j]<=2750132; j++) {
			s[i*prime[j]]=prime[j];
			g[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	g[1]=1;
}
int main() {
	init();
	for(int i=1; i<=cnt; i++)p[prime[i]]=i;
	scanf("%lld",&n);
	n<<=1;
	for(int i=1; i<=n; i++) {
		scanf("%lld",&a[i]);
		b[a[i]]++;
	}
	sort(a+1,a+n+1);
	for(int i=n; i>=1; i--) {
		if(b[a[i]]) {
			b[a[i]]--;
			if(g[a[i]]) printf("%lld ",a[i]),b[a[i]/s[a[i]]]--;
			else printf("%lld ",p[a[i]]),b[p[a[i]]]--;
		}
	}
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1176D)
## 思路
首先，观察题目，我们可以得出下面的规律：

+ 质数只能变成比它大的质数
+ 合数只能变成比它小的质数或合数

我们发现质数的确定需要先确定合数，于是我们先枚举合数。

又因为合数变成的是比它小的数，所以要先排序，然后从大往小枚举。

这里有一个坑点，这些数字很有可能是有重复的，这样在二分的时候可能会多次访问到相同的数字，所以我们需要记录一个 $first_i$ 表示当前值为 $i$ 的数最小的没有被访问过的下标。

由于题目保证有解，所以直接模拟即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=3e6+10;
int prime[N],vis[N],p[N],first[N],ans[N],ps[N],a[N];
inline int findmax(int x){for (int i=2;i*i<=x;++i) if (x%i==0) return x/i;}
signed main(){
	ios::sync_with_stdio(false),
	cin.tie(0),cout.tie(0);
	int cnt=0;
	for (int i=2;i<=2800000;++i){
		if(!vis[i]) prime[++cnt]=i;
		for (int j=1;j<=cnt && i*prime[j]<=2800000;++j){
			vis[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
	vis[1]=1;
	int n;cin>>n;
	n<<=1;int k=0;
	for (int i=1;i<=n;++i) cin>>a[i];sort(a+1,a+n+1);
	for (int i=1;i<=n;++i) if (a[i]!=a[i-1]) first[a[i]]=i;
	for (int i=n;i>=1;--i){
		if (!vis[a[i]] || p[i]) continue;
		int maxn=findmax(a[i]);
		ans[++k]=a[i];
		p[first[maxn]]=1;first[maxn]++;
	}
	for (int i=1;i<=n;++i){
		if (vis[a[i]] || ps[i] || p[i]) continue;
		int to=prime[a[i]];
		ps[first[to]]=1;first[to]++;
		ans[++k]=a[i];
	}
	for (int i=1;i<=k;++i) cout<<ans[i]<<' ';
	cout<<'\n';
	return 0;
}
```


---

## 作者：81179332_ (赞：0)

我们将给定的 $b$ 序列中的数按照合数和质数排序

对于合数，我们从大到小贪心地将数字 $x$ 加入 $a$ 序列，并将 $x$ 的除自身外的最大因子从 $a$ 序列中删去

对于质数，我们从小到大贪心地将数字 $x$ 加入 $a$ 序列，并将第 $x$ 个质数从序列中删去

为什么这么做是对的呢？

对于最大的那个合数，$b$ 序列中没有任何的数可以将它删掉，因为质数只会删掉质数而合数只会删掉比它小的数，所以最大的合数一定在 $a$　序列中，所以一定要贪心地选最大的

对于最小的那个质数，$b$　序列中没有任何的数可以将它删掉，因为质数只会删掉比它大的质数，而合数此时已经莫得了，所以最小的质数一定在 $a$　序列中，所以一定要贪心选最小的

```cpp
const int N = 5000010;
int prime[N],tot,minn[N];bool vis[N];
void init(int n)
{
	vis[1] = 1;
	for(int i = 2;i <= n;i++)
	{
		if(!vis[i]) minn[prime[++tot] = i] = i;
		for(int j = 1,k;j <= tot && (k = i * prime[j]) <= n;j++)
		{
			vis[k] = 1,minn[k] = min(minn[i],prime[j]);
			if(i % prime[j] == 0) break;
		}
	}
}
int n,book[N];
vector<int> p,q;
int main()
{
	init(5000000);
	n = read();
	for(int i = 1;i <= 2 * n;i++)
	{
		int x = read();
		if(vis[x]) q.push_back(x);
		else p.push_back(x);
	}
	sort(q.begin(),q.end(),greater<int>());
	sort(p.begin(),p.end());
	for(auto x:q)
	{
		if(book[x]) { book[x]--;continue; }
		pprint(x),book[x / minn[x]]++;
	}
	for(auto x:p)
	{
		if(book[x]) { book[x]--;continue; }
		pprint(x),book[prime[x]]++;
	}
}
```

---

