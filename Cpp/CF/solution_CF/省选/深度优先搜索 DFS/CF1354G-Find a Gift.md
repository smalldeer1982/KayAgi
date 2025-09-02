# Find a Gift

## 题目描述

This is an interactive problem. Don't forget to flush output after printing queries using cout.flush() or fflush(stdout) in C++ or similar functions in other programming languages.

There are $ n $ gift boxes in a row, numbered from $ 1 $ to $ n $ from left to right. It's known that exactly $ k $ of them contain valuable gifts — other boxes contain just lucky stones. All boxes look the same and differ only in weight. All boxes with stones have the same weight and are strictly heavier than boxes with valuable items. But valuable gifts may be different, so the boxes with valuable items may have different weights.

You can ask no more than $ 50 $ queries (printing an answer doesn't count). By each query you can compare total weights of two non-intersecting subsets of boxes $ a_1, a_2, \dots, a_{k_a} $ and $ b_1, b_2, \dots, b_{k_b} $ . In return you'll get one of four results:

- FIRST, if subset $ a_1, a_2, \dots, a_{k_a} $ is strictly heavier;
- SECOND, if subset $ b_1, b_2, \dots, b_{k_b} $ is strictly heavier;
- EQUAL, if subsets have equal total weights;
- WASTED, if the query is incorrect or the limit of queries is exceeded.

Using such queries (or, maybe, intuition) find the box with a valuable gift with the minimum index.

## 说明/提示

Additional separators "–" in the sample are used only to increase the readability of the sample. Don't print any unnecessary symbols or line breaks in your solution when you send it to the system.

 Hacks are forbidden in this task.

## 样例 #1

### 输入

```
2
2 1
-
-
-
FIRST
-
5 2
-
-
-
FIRST
-
-
-
SECOND
-
-
-
EQUAL
-```

### 输出

```
-
-
? 1 1
1
2
-
! 2
-
? 1 1
1
2
-
? 2 3
4 2
1 3 5
-
? 1 1
4
5
-
! 1```

# 题解

## 作者：ZMQ_Ink6556 (赞：3)

## 题解：CF1354G Find a Gift

### 题意简述

有 $n$ 个盒子，每个盒子要么有石头，要么有礼物，石头重量均相等，礼物重量可能不同但严格小于石头的重量。

你有一个可以使用 $50$ 次的天平，可以称出任意两组（不一定是一个）物品哪组更重或一样重。

请你找到编号最小的礼物。

多测。

### 解题思路

我们先假设第一个箱子是石头，尝试找到一些可行的解法。

可以使用倍增的思想快速跳过所有第一个礼物前的石头，如图所示：

![pic](https://cdn.luogu.com.cn/upload/image_hosting/6pb28bq7.png)

只要前 $2^k$ 个数和第 $2^k + 1$ 到 $2^{k + 1}$ 的重量相等，那么就可以证明前 $2^{k + 1}$ 都相等。反之则可以证明答案在第 $2^k + 1$ 到 $2^{k + 1}$ 之间。

此时，我们可以进行标准的二分查找，在前 $2^k$ 个之中选择和 $2^k + 1$ 到 $mid$ 数量相等的箱子（因为前面的都是石头，后面的有可能有礼物）。如果重量相等：$l \gets mid + 1$，否则 $r \gets mid - 1$，直到 $r - l \le 1$ 即为答案。

我们到目前总共用了 $2\log n$ 最多 $20$ 次操作。

可是，我们目前的所有做法都基于第一个箱子不是礼物。

为了保证这个做法成立，我们需要先判断第一个礼盒是不是礼物（如果是，直接输出 `! 1` 结束）。

方式也很简单，暴力找最多 $30$ 个位置（我找了 $20$ 个也过了），和第一个点比较，如果出现有大于第一个点的数，那么第一个点就是礼物，否则，就认为第一个点是石头（因为如果第一个点是礼物，结合题面给出礼物数量小于 $\frac{n}{2}$，所以错误率也小于 $(\frac{1}{2})^{30}$）。

附毫秒级随机种子代码：

```cpp

void seed()
{
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto t = ms.time_since_epoch().count();
	srand(t);
	return;
}
```

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t , n , k , p , l , r , mid , ans;
string s;
void seed()
{
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto t = ms.time_since_epoch().count();
	srand(t);
	return;
}
void ask(int as , int ae , int bs , int be)
{
	cout << "? " << ae - as + 1 << ' ' << be - bs + 1 << endl;
	for(int i = as ; i <= ae ; i++)
	{
		cout << i << ' ';
	}
	cout << endl;
	for(int i = bs ; i <= be ; i++)
	{
		cout << i << ' ';
	}
	cout << endl;
	cin >> s;
	if(s == "WASTED")
	{
		cout << "ERROR" << endl;
		exit(0); 
	}
	return;
}
bool first()
{
	for(int i = 1 ; i <= 20 ; i++)
	{
		int tmp = rand() % (n - 1) + 2;
		ask(1 , 1 , tmp , tmp);
		if(s == "SECOND")
		{
			return 1;
		}
	}
	return 0;
}
bool check(int q)
{
	ask(1 , q - p , p + 1 , q);
	if(s == "FIRST")
	{
		return 1;
	}
	return 0;
}
int main()
{
	seed();
	cin >> t;
	while(t--)
	{
		cin >> n >> k;
		if(first())
		{
			cout << "! 1" << endl;
			continue; 
		}
		p = 1;
		while(p < n)
		{
			if(p * 2 >= n)
			{
				l = p + 1;
				r = n;
				break;
			}
			ask(1 , p , p + 1 , p * 2);
			if(s == "FIRST")
			{
				l = p + 1;
				r = p * 2;
				break;
			}
			p *= 2;
		}
		while(l <= r)
		{
			mid = (l + r) / 2;
			if(check(mid))
			{
				ans = mid;
				r = mid - 1;
			}
			else
			{
				l = mid + 1;
			}
		}
		cout << "! " << ans << endl;
	}
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：2)

如果我知道其中 $x$ 个是石头，那么我就能用这 $x$ 个去确定另外 $x$ 个数当中有没有石头。那么先找到 $1$ 个石头，然后从头开始倍增找到第一个没有石头的区间。要确定这段有石头的区间的第 $1$ 个石头位置，可以二分。

如何找到一个石头？不知道，采用随机化。随机找到一些位置，找到当中最重的，那么可以确定那个是石头。一次有 $\frac 1 2$ 的概率选到礼物，那么选 $25$ 次，最终出错的概率就只有 $\frac 1 {2^{25}}\le  10^{-7}$，可以接受。

```cpp
#include <bits/stdc++.h>
using namespace std; 

mt19937 Rand(time(0)); 
int rnd(int l, int r) { return uniform_int_distribution<>(l, r)(Rand); }

int n, k, buc[1005];
int a[1005], b[1005]; // a 全是石头
int ask(int p) {
    for (int i = 1; i <= p; ++i) ++buc[a[i]]; 
    for (int i = 1; i <= p; ++i) ++buc[b[i]]; 
    int t = 0; for (int i = 1; i <= n; ++i) if (buc[i] == 2) ++t; 
    cout << "? " << p - t << " " << p - t << "\n"; 
    for (int i = 1; i <= p; ++i) if (buc[a[i]] != 2) cout << a[i] << " "; cout << "\n"; 
    for (int i = 1; i <= p; ++i) if (buc[b[i]] != 2) cout << b[i] << " "; cout << endl; 
    memset(buc, 0, sizeof buc); string s; cin >> s; 
    if (s == "FIRST") return 1; 
    if (s == "SECOND") return -1; 
    return 0; 
}
void answer(int x) { cout << "! " << x << endl; }

int main(void) {
    ios::sync_with_stdio(0); 
    int T; cin >> T; 
    while (T--) {
        cin >> n >> k; a[1] = 1; 
        for (int i = 1; i <= 25; ++i) {
            b[1] = rnd(1, n); while (a[1] == b[1]) b[1] = rnd(1, n); 
            if (ask(1) == -1) a[1] = b[1]; 
        } b[1] = 1; 
        if (a[1] != 1 && ask(1) == 1) { answer(1); continue; }
        for (int i = 1; i <= n; ++i) a[i] = i; 
        int l = 1, r = 2; 
        while (l < n) {
            int m = r - l; 
            for (int i = 1; i <= m; ++i) b[i] = i + l; 
            if (ask(m) == 1) break; 
            l = r; r = min(n, r * 2); 
        } 
        int L = l + 1, R = r; 
        while (L < R) {
            int mid = L + R >> 1; // 礼物在 [l, mid] 
            for (int i = L; i <= mid; ++i) b[i - L + 1] = i; 
            if (ask(mid - L + 1) == 1) R = mid; 
            else L = mid + 1; 
        }
        answer(R); 
    }
    return 0; 
}
```

---

## 作者：FutaRimeWoawaSete (赞：2)

**CF1354G sol**

考虑问题的数据结构意义：使用数量级 $O(\log n)$ 的区间比较信息查找非全局绝对众数（即出现次数至少有 $\lfloor \frac{n}{2} \rfloor$）在序列的第一个出现位置。保证全局存在绝对众数且为全局最大值。

其实不一定要约束全局最大值的限制，只是由于本题的区间比较信息仅支持和比较，如果是自己做题倒还可以维护一些其它的半群信息来代替。

对于这个问题我们不难想到先找到该全局绝对众数是谁，根据概率，我们若选出全局中 $x$ 个数，则其中没有全局绝对众数的概率是 $\frac{1}{2 ^ x}$，将 $x$ 调成 $O(\log n)$ 则是一个期望正确的做法。

不难想到倍增。发现有了具体的全局绝对众数之后，我们可以倍增跳长为 $2 ^ i$ 的前缀，刻画数量为 $2 ^ i$ 的全局绝对众数和信息，直到跳到一个前缀存在非绝对众数为止。

肢解掉前缀前面已经确定的是全局绝对众数的区间，我们发现该区间也可以倍增跳区间的前缀，因为所有需要用到的长度都在前面倍增跳长为 $2 ^ i$ 的前缀时刻画好了。

这样就做到了 $O(3 \log n)$ 回答问题。

```cpp
/*
考虑我们可以先找到 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e3 + 5;
int n,k,T;
mt19937 rnd(1919810);
uniform_int_distribution<int> op1(1 , 1000);
int sto;
char s[15];
inline bool check(int x)
{
	if(x == sto) return 0;
	cout << "?" << " " << "1" << " " << "1" << endl;
	cout << sto << endl;
	cout << x << endl;
	cin >> s;
	if(s[0] == 'F') return 1;
	return 0;
}
int lg[1005];
int main()
{
	lg[1] = 0;
	for(int i = 2 ; i <= 1000 ; i ++) lg[i] = lg[i >> 1] + 1;
	scanf("%d",&T);
	while(T --)
	{
		scanf("%d %d",&n,&k);
		int w = 15;sto = 1;
		int x;
		while(w --)
		{
			x = 0;
			do
			{
				x = op1(rnd) % n + 1;
			}while(x == sto);
			cout << "?" << " " << "1" << " " << "1" << endl;
			cout << sto << endl;
			cout << x << endl;
			cin >> s;
			if(s[0] == 'F');
			else sto = x;
		}
		if(check(1)){cout << "! " << 1 << endl;continue;}
		int l = 1 , len = 2 , r = 0;
		while(1)
		{
			r = l + len - 1;
			int mid = (l + r) >> 1;
			cout << "?" << " " << mid - l + 1 << " " << r - mid << endl;
			for(int i = l ; i < mid ; i ++) cout << i << " ";
			cout << mid << endl;
			for(int i = mid + 1 ; i < r ; i ++) cout << i << " ";
			cout << r << endl;
			cin >> s;
			if(s[0] != 'E')
			{
				if(s[0] == 'F') l = mid + 1;
				else r = mid;
				int LEN = (len >> 1);
				while(LEN > 1)
				{
					mid = (l + r) >> 1;
					const int llen = mid - l + 1;
					cout << "?" << " " << llen << " " << llen << endl;
					for(int i = 1 ; i < llen ; i ++) cout << i << " ";
					cout << llen << endl;
					for(int i = l ; i < mid ; i ++) cout << i << " ";
					cout << mid << endl;
					cin >> s;
					if(s[0] == 'F') r = mid;
					else if(s[0] == 'E') l = mid + 1;
					LEN >>= 1;
				}
				cout << "! " << l << endl;
				break;
			}
			if((len << 1) > n) 
			{
				l = len + 1 , r = n;
				const int mx = r - l + 1;
				for(int i = lg[mx] ; i >= 0 ; i --) 
				{
					int llen = (1 << i);
					if(l + llen - 1 > r) continue;
					cout << "?" << " " << llen << " " << llen << endl;
					for(int j = 1 ; j < llen ; j ++) cout << j << " ";
					cout << llen << endl; 
					for(int j = l ; j < l + llen - 1 ; j ++) cout << j << " ";
					cout << l + llen - 1 << endl;
					cin >> s;
					if(s[0] == 'E') l = l + llen;
				}
				cout << "! " << l << endl;
				break;
			}
			len <<= 1;
		}
	}
	return 0;
}
```

---

## 作者：Mirasycle (赞：1)

$\mathrm{Trick:}$ 看到 $> \dfrac{n}{2}$，就要想到随机化。

可以发现石子的个数大于一半，且重量唯一最大，于是随机 $\log n$ 个位置取重量最大的就几乎肯定是石子了。

现在我们得到了一个石子，要求出最前面的一个礼物。前缀长度最值可以考虑倍增。

每次询问一段长度为 $2^{k-1}$ 的前缀，前 $k$ 次询问了 $\sum\limits_{i=0}^{k-1}2^{i}=2^{k}-1$ 长度的一个前缀，配合上我们第一次找到的石子点就可以得到一个 $2^k$ 大小的集合。以此来询问第 $k+1$ 次的 $2^k$ 大小的集合。

当然由于提问要求是不重叠的两个集合，所以我们找到某个石子之后可以用它来验证第一个盒子里是否是石子，然后以第一个盒子里的石子为基础来验证。如果是以随机一个石子为基准的话，可能会同时在询问的两个集合内出现。

在某一次中，我们发现了新增的集合重量小于之前的集合，于是就代表礼物在这个新增集合中，对于这个集合内部二分就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int n,k,c,vis[maxn];
vector<int> qa,qb; int num=0; 
int random(int x){ return rand()%x+1; }
void query(){
	cout<<"? "<<qa.size()<<" "<<qb.size()<<endl;
	for(auto v:qa) cout<<v<<" "; cout<<endl;
	for(auto v:qb) cout<<v<<" "; fflush(stdout);
	qa.clear(); qb.clear(); num++;
	assert(num<=50);
}
int read(){
	char c[10]; cin>>c;
	if(c[0]=='F') return 1;//大于 
	if(c[0]=='S') return 2;//小于
	if(c[0]=='E') return 3;//等于
	if(c[0]=='W') exit(0);
}
void solve(){
	cin>>n>>k; for(int i=1;i<=n;i++) vis[i]=0; num=0;
	int c=random(n),cnt=0; vis[c]=1;
	while(cnt<=max((int)log2(n),5)){
		int d=random(n); if(vis[d]) continue;
		qa.push_back(c); qb.push_back(d); 
		query(); if(read()==2) c=d;
		vis[d]=1; cnt++;
		int sum=0; for(int i=1;i<=n;i++) sum+=vis[i];
		if(sum==n) break; 
	}
	if(n<=4){
		for(int i=1;i<=n;i++){
			if(c==i) continue;
			qa.push_back(c); qb.push_back(i);
			query(); if(read()==1){ cout<<"! "<<i<<endl;  return ; }
		}
	}
	if(c!=1){
		qa.push_back(c); qb.push_back(1);
		query(); if(read()==1){ cout<<"! 1"<<endl; return ; }
	}
	int l,r,nl=2,nr=2;
	while(1){
		l=nl,r=nr;
		for(int i=1;i<=r-l+1;i++) qa.push_back(i);
		for(int i=l;i<=r;i++) qb.push_back(i);
		query(); if(read()==1) break;
		nl=r+1,nr=min(r+2*(r-l+1),n);
	}
	while(l<r){
		int mid=(l+r)>>1;
		for(int i=1;i<=mid-l+1;i++) qa.push_back(i);
		for(int i=l;i<=mid;i++) qb.push_back(i);
		query();
		if(read()==1) r=mid;
		else l=mid+1;
	}
	cout<<"! "<<l<<endl;
}
int main(){
	srand((unsigned)time(0));
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

首先要搞清楚第一个盒子里到底装的啥。

注意到 $1\le k\le \dfrac{n}{2}$，说明至少一半以上的盒子里都是石头，那随机选一个盒子是石头的概率不小于 $\dfrac{1}{2}$。于是用这个随机出的盒子拿去跟第一个盒子进行询问，如果是 $w_1<w_x$，那第一个盒子里装的就是礼物。随机选 $15$ 次都选不到石头的概率不高于 $\dfrac{1}{2^{15}}$，足够小了。

现在只用思考第一个盒子里是石头的情况。尝试通过倍增确定第一个礼物盒的位置。第 $i$ 次询问 $[1,2^{i-1}]$ 与 $(2^{i-1},2^i]$，如果左边比右边重说明礼物在右边，否则继续。因为倍增是从小到大的，所以每次左边一定全为石头，不然不会进入这次询问。

找到第一个礼盒的范围后在区间里二分即可，具体实现可结合代码理解。

# Code

```cpp
#include<bits/stdc++.h>
std::mt19937 rnd(time(0));
inline int ask(int l1,int r1,int l2,int r2){
	printf("? %d %d\n",r1-l1+1,r2-l2+1);
	for(int i=l1;i<=r1;++i)
		printf("%d%c",i," \n"[i==r1]);
	for(int i=l2;i<=r2;++i)
		printf("%d%c",i," \n"[i==r2]);
	fflush(stdout);
	static char s[10];
	scanf("%s",s);
	return s[0]=='F'?1:s[0]=='E'?0:-1;
}
int T,n,m,l,r,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1,x;i<=15;++i){
			x=rnd()%(n-1)+2;
			if(ask(1,1,x,x)==-1){
				puts("! 1");fflush(stdout);
				goto nxt;
			}
		}
		for(int i=1;;i<<=1){
			if((i<<1)>n){
				l=i+1;r=n;
				break;
			}
			if(ask(1,i,i+1,i<<1)==1){
				l=i+1;r=i<<1;
				break;
			}
		}
		while(l<=r){
			int mid=l+r>>1;
			if(ask(1,mid-l+1,l,mid))ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("! %d\n",ans);fflush(stdout);
		nxt:;
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2600}$
---
### 解题思路：

很厉害的随机题。

---
假设现在已经知道了某一些位置是石头，取出一个与已知的石头集合大小相等的未被选中的位置集合进行比较，如果两者重量相等，则说明新的集合中也全是石头，否则说明新的集合里面有礼物。找到这样的一个集合的最多次数为 $\lceil\log_2n\rceil$。

然后在新的集合里面每一次选取集合的一半，并将其余另一个已知的全是石头的集合比较，如果重量相等，说明这个集合里面全是石头，礼物在另一半里面。反之则说明这个集合里面有礼物，再次进行同样的操作。这样从一个确定有礼物的集合中找到礼物最多需要 $\lceil\log_2n\rceil$。实际上应该会少一点，但一定不会超过。

注意要求编号最小的礼物，新的集合的选取需要尽可能往前。

---
然后问题就是如何找到一个石头。

可以考虑利用石头超过一半这点，每一次随机某一个位置，更新最重的一个的位置。如果进行了 $n$ 次操作，则出错的概率为 $\dfrac{1}{2^n}$。

上面最后找到礼物的操作不会超过 $20$ 次，分配给这一步 $30$ 次能使出错率降到 $10^{-9}$，可以忽略不计了。

---
### 代码：

```
#include<cstdio>
#include<ctime>
#include<algorithm>
using namespace std;
int T,n,k,st,x,u[1005],len,l,r,mid,ans;
int get(){
	char c1=getchar(),c;
	while(c1==' '||c1=='\n'||c1=='\r')
	c1=getchar();
	if(c1=='F'){
		for(int i=1;i<=4;i++)c=getchar();
		return 1;
	}
	if(c1=='S'){
		for(int i=1;i<=5;i++)c=getchar();
		return 2;
	}
	if(c1=='E'){
		for(int i=1;i<=4;i++)c=getchar();
		return 3;
	}
}
void work(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)u[i]=0;
	st=rand()%n+1;
	u[st]=1;
	for(int i=1;i<=min(n-1,30);i++){
		x=rand()%n+1;
		while(u[x]==1)x=rand()%n+1;
		u[x]=1;
		printf("? 1 1\n");
		printf("%d\n%d\n",st,x);
		fflush(stdout);
		if(get()==2)st=x;
	}
	if(st!=1){
		printf("? 1 1\n");
		printf("%d\n%d\n",st,1);
		fflush(stdout);
		ans=get();
		if(ans==1){
			printf("! 1\n");
			fflush(stdout);
			return;
		}
		if(ans==2)st=1;
	}
	len=1;l=r=-1;
	while(len*2<=n){
		printf("? %d %d\n",len,len);
		for(int i=1;i<=len;i++)
		printf("%d ",i);printf("\n");
		for(int i=1;i<=len;i++)
		printf("%d ",i+len);printf("\n");
		fflush(stdout);
		ans=get();
		if(ans==1){
			l=len+1;
			r=len*2;
			break;
		}
		len*=2;
	}
	if(l==r&&l==-1){
		l=len+1;
		r=n;
	}
	while(l<r){
		int mid=(l+r)/2;
		printf("? %d %d\n",mid-l+1,mid-l+1);
		for(int i=1;i<=mid-l+1;i++)
		printf("%d ",i);printf("\n");
		for(int i=l;i<=mid;i++)
		printf("%d ",i);printf("\n");
		fflush(stdout);
		ans=get();
		if(ans==1)r=mid;
		else l=mid+1;
	}
	printf("! %d\n",l);
	fflush(stdout);
}
int main(){
	scanf("%d",&T);
	srand(time(0));
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：DJRzjl (赞：1)

注意到 $k\le \frac n2$，也就是至少一半是石头，那么我们极端情况下就很难之间找到礼物的位置，所以我们考虑通过某个石头的位置确定编号最小的礼物的位置。

假设我们已经知道了某个石头的位置 $p$，进行如下操作：

1. 先询问 $p$ 和 $1$ 谁重，若不等则说明 $1$ 是礼物，答案直接就是 $1$，否则说明 $1$ 号位是石头；
2. 若目前已经确定前 $t$ 个位置是石头，令 $len=\min(2t,n)-t$，询问区间 $[1,len]$ 和区间 $[t+1,t+len]$ 两段长均为 $len$ 的区间重量和的大小关系。
3. 当上一次 $2$ 中询问返回值为 `EQUAL` 时进入下一步操作，否则重新进行操作2和3。
4. 此时 $[1,t]$ 全为石头，$[t+1,t+len-1]$ 重量与 $[1,len]$ 不等说明编号最小的礼物就在 $[t+1,t+len+1]$​ 中，我们在这一段中二分，不断询问 $[t+1,mid]$ 与和其等长的前缀（因为 $len\le t$，于是这些前缀一定都是石头）以比较重量，判断编号最小礼物是在 $mid$ 前面还是后面，最后得到答案。

这其实就是一个倍增，之后二分的过程，最劣情况下约询问 $2\log_2n$​​ 次，$n$ 为最大值 $1000$ 时，约为操作 $20$ 次。

这样问题就转化为了在限定步数内确定出任意一石头的位置，因为石头数量不少于一半，且质量比礼物大，考虑用随机化更新最大重量以及所在位置。

考虑先随机选取两个位置 $u1,u2$​ 进行询问，然后将其中更重的一个与随机出的新位置 $u3$ 比较，即询问 $\max(u1,u2),u3$，然后再取 $u4\dots$，重复这个过程。

假设像这样询问了 $x$​ 次，那么我们就会得到 $x+1$​ 个随机位置的最大重量以及所在位置，只要询问的这些位置中存在一个石头，因为它最重，它就会被保留到最后成为这 $x+1$​ 个中最大重量，也就得到我们想要的了。每一个随机位置取不到石头的概率不多于 $\frac 12$​，所以操作 $x$​ 次，找不到石头的概率就不多于 $\frac 1{2^{x+1}}$​​，取 $x=30(代码中为20)$​​​，我们找不到石头的概率就小于十亿分之一，所以就可以基本认为，在我们这样操作完得到的最大重量所在位置一定是某个石头的位置。

综上我们可以在合法的询问步数内找到答案，失败的概率可以忽略不记。

---
### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e3;

int T,n,k;
bool vis[N];
char op[10];

int ask(int l1,int r1,int l2,int r2){
	printf("? %d %d\n",r1-l1+1,r2-l2+1);
	for(int i=l1;i<r1;++i) printf("%d ",i);
	printf("%d\n",r1);
	for(int i=l2;i<r2;++i) printf("%d ",i);
	printf("%d\n",r2);
	fflush(stdout);
	scanf("%s",op+1);
	if(op[1]=='F') return -1;
	if(op[1]=='S') return 1;
	return 0;
}

int solve(int L,int R){
	int l=L,r=R,mid,res=R;
	while(l<=r){
		mid=(l+r)>>1;
		if(ask(1,mid-L+1,L,mid)) r=mid-1,res=mid;
		else l=mid+1;
	}
	return res;
}

int main(){
	srand(time(0));
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		int flag=0;
		for(int i=1;i<=n;i++) vis[i]=0;
		int mx=min(20,n-1);
		for(int i=1,pos;i<=mx;i++){
			while(vis[pos=rand()%(n-1)+2]);
			vis[pos]=1;
			if(ask(1,1,pos,pos)>0) {flag=1;break;}
		}
		if(flag) {
			printf("! %d\n",1);
			fflush(stdout);
			continue;
		}
		int base=1,ans=0;
		while(true){
			if((base<<1)>n) {ans=solve(base+1,n);break;}
			if(ask(1,base,base+1,base<<1)) {ans=solve(base+1,base<<1);break;}
			base<<=1;
		}
		printf("! %d\n",ans);
		fflush(stdout);
	}
	return 0;
}
```



---

## 作者：Purple_wzy (赞：1)

[题面](https://www.luogu.com.cn/problem/CF1354G)

[英文题面](http://codeforces.com/problemset/problem/1354/G)

题意：有点长，去洛谷上看吧~

题解：首先挖掘题目的性质：发现如果两个集合都只有一个元素，且询问的结果不是EQUAL，那么小的那个一定就是礼物。那么我们希望能找到一个石头，这样判断起来就能方便很多。

考虑随意指定30个位置$p(p\neq 1)$，依次询问$(1,p)$。如果有返回SECOND的，那么1就一定是礼物。发现由于礼物个数少于$\frac{n}{2}$，每次询问位置$p$都有至少$\frac{1}{2}$的概率是石头，那么如果在30次询问后一直没有SECOND，那么我们可以断定1是个石头。考虑只有当这30次询问的位置上都是礼物，且权值都比1小时才有可能犯错，因此这样的犯错概率是小于$\frac{1}{2^{30}}$的，可以忽略。

当我们确定了一个石头后，我们就可以进行倍增了。每次询问$[1,2^{k-1}]$和$[2^{k-1}+1,2^k]$，如果返回EQUAL，那么继续倍增；如果是FIRST，那么区间$[2^{k-1}+1,2^k]$中就一定有礼物。通过二分查找，我们就能找到最靠左的那个礼物的位置。

总查询次数是$30+2logn$的，刚好50次。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline int
#define C(x,y) memset(x,y,sizeof(x))
#define STS system("pause")
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
mt19937 rnd(time(0));
char c[10];
int T,n,m,ans,v[1010],p;
IN Rand(int Mod){
	re res=rnd();if(res<0)res=-res;res%=Mod;return res;
}
I getit(int x,int y,int len){
	if(x==y)return cout<<"! "<<x<<endl,void();
	re mid=(x+y)>>1,ln=(len+1)>>1;
	cout<<"? "<<ln<<" "<<ln<<endl;
	F(i,x-ln,x-1)cout<<i<<" ";cout<<endl;
	F(i,x,mid)cout<<i<<" ";cout<<endl;
	cout.flush();cin>>c+1;if(c[1]=='W')exit(0);
	if(c[1]=='F')getit(x,mid,ln);
	else getit(mid+1,y,len-ln);
}
int main(){
	srand(time(0));
	cin>>T;
	while(T--){
		cin>>n>>m;C(v,0);ans=0;
		F(i,1,min(30,n-1)){
			while(1){
				p=Rand(n-1)+2;if(!v[p])break;
			}
			v[p]=1;
			cout<<"? 1 1"<<endl<<"1"<<endl<<p<<endl;cout.flush();
			cin>>c+1;if(c[1]=='W')return 0;
			if(c[1]=='S'){ans=1;break;}	
		}
		if(ans){cout<<"! "<<ans<<endl;cout.flush();continue;}
		re r=1,mid;
		while((r<<1)<=n){
			r<<=1;mid=r>>1;cout<<"? "<<mid<<" "<<mid<<endl;
			F(i,1,mid)cout<<i<<" ";cout<<endl;
			F(i,mid+1,r)cout<<i<<" ";cout<<endl;
			cout.flush();cin>>c+1;if(c[1]=='W')return 0;
			if(c[1]=='F'){
				getit(mid+1,r,mid);ans=1;
				break;
			}
		}
		if(ans)continue;
		getit(r+1,n,n-r);
	}
	return 0;
}

```

---

## 作者：2018LZY (赞：1)

这是一道蓝题吧，然而我一开始没看出来。。。。

首先$k*2\le n$,这说明如果我们随机一个位置的话，这个位置是礼物的概率$\le \frac 1 2$.

我们不妨先判段第一个箱子内是否装有礼物。

显然，如果有箱子的质量>第一个箱子的话，我们就直接判定第一个箱子不装石头。

进行30次操作仍然不行的话，假设第一个箱子是礼物的话，那么说明选到的也都是礼物（欧皇），概率<$\frac 1 2^{30}$。

由于这个实在太小，我们可以认为第一个箱子就是石头了。

之后我们倍增区间，找到最大的区间$[1,2^k]$满足这个区间内的都是石头，那么$(2^k,\min(2^{k+1},n)]$就一定含有礼物。

最后二分查找即可。

第一个为啥是30呢，因为后面两个最多用10*2个询问啊。

当然你也可以第一次弄$50-2\log n$次。。

```cpp
#include<ctime>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<iostream>
using namespace std;
const int N=1010;

int T,n,k,ys[150],flag;
char s[9];
void qr(int &x) {scanf("%d",&x);}

int ask(int l,int r,int L,int R) {
	printf("? %d %d\n",r-l+1,R-L+1);
	for(int i=l;i<=r;i++) printf("%d ",i);
	puts("");
	for(int i=L;i<=R;i++) printf("%d ",i);
	puts("");
	fflush(stdout);
	scanf("%s",s); return ys[s[0]];
}

int main() {
	ys['F']=1; ys['S']=2; ys['E']=3; ys['W']=4;
	srand(time(0));
	qr(T);while(T--) {
		qr(n); qr(k); flag=0;
		int x=rand()%(n-1)+2;
		for(int i=1;i<=30;i++) {
			int y=ask(1,1,x,x);
			if(y==2) {puts("! 1"); flag=1; break;}
			x=rand()%(n-1)+2;
		}
		if(!flag) {
			for(x=1;x*2<=n;x*=2)
				if(ask(1,x,x+1,2*x)^3) break;
			int l=x+1,r=min(2*x,n),mid;
			while(l<r) {
				mid=(l+r)>>1;
				if(ask(l,mid,1,mid-l+1)==3) l=mid+1;
				else r=mid;
			}
			printf("! %d\n",l);
		}
		fflush(stdout);
	}
	return 0;
}
```


---

## 作者：tzc_wk (赞：0)

> 摘自我的 [杂题选做Ⅴ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp5.html) 中的第 $103$ 题。

首先考虑我们假如知道某个盒子里是石头怎么求解答案。考虑倍增，具体来说我们先假设第一个盒子里是石头，否则直接返回 $1$ 即可。那么我们第一次拿 $1$ 和 $2$ 比较，如果不相等说明 $2$ 是礼物，否则说明 $1,2$ 都是石头，我们再拿 $1,2$ 与 $3,4$ 比较，如果不相等则说明 $3,4$ 中有礼物，否则说明 $1\sim 4$ 都是石头，我们继续比较 $1,2,3,4$ 与 $5,6,7,8$，以此类推。这样我们可以求出一个 $k$，使得第一个装有礼物的盒子在 $2^{k-1}+1$ 与 $2^k$ 之间，然后再二分即可。这样询问次数上界为 $2\log n$。

接下来考虑如何求出一个装有石头的盒子。直接做看起来不太容易，不过注意到题目中“$k>\dfrac{n}{2}$”的条件，这意味着我们可以考虑**随机化**。我们考虑找到一个局部重量最大的盒子 $x$，初始 $x=1$，然后每次随机一个盒子 $y$ 并比较 $x,y$ 的重量，如果 $y$ 的重量大于 $x$ 那么令 $x$ 等于 $y$，如此随机 $T$ 次之后出错的概率就降到了 $\dfrac{1}{2^T}$，取 $T=20$ 就差不多了。

```cpp
int n, k;
int query(vector<int> a, vector<int> b) {//0: a < b, 1: a > b, 2: a = b
	if (a == b) return 2;
	printf("? %llu %llu\n", a.size(), b.size());
	for (int x : a) printf("%d ", x); printf("\n");
	for (int x : b) printf("%d ", x); printf("\n");
	fflush(stdout); string ss; cin >> ss;
	if (ss == "WASTED") exit(0xfe);
	if (ss == "SECOND") return 0;
	if (ss == "FIRST") return 1;
	return 2;
}
int calc(int l, int r) {
	int L = l, R = r, p = 0;
	while (L <= R) {
		int mid = L + R >> 1;
		vector<int> A, B;
		for (int i = l; i <= mid; i++) A.pb(i - l + 1), B.pb(i);
		if (query(A, B) != 2) p = mid, R = mid - 1;
		else L = mid + 1;
	}
	return p;
}
int solve() {
	int T = 20, cur = 1;
	while (T--) {
		int x = rand() % n + 1;
		while (x == cur) x = rand() % n + 1;
		if (query(vector<int>{x}, vector<int>{cur})) cur = x;
	}
	if (query(vector<int>{1}, vector<int>{cur}) != 2)
		return 1;
	int L;
	for (L = 2; L <= n; L <<= 1) {
		vector<int> A, B;
		for (int j = 1; j <= (L >> 1); j++) A.pb(j);
		for (int j = 1; j <= (L >> 1); j++) B.pb(j + (L >> 1));
		if (query(A, B) != 2) return calc((L >> 1) + 1, L);
	}
	L >>= 1;
	return calc(L + 1, n);
}
int main() {
	srand(time(0));
	int qu; scanf("%d", &qu);
	while (qu--) {
		scanf("%d%d", &n, &k); int res = solve();
		printf("! %d\n", res); fflush(stdout);
	}
	return 0;
}
```

---

