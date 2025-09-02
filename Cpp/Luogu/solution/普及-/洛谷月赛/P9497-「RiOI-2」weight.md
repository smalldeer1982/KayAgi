# 「RiOI-2」weight

## 题目背景

在小树林间坐落着一个幻想的城堡。这里是 E 国的领地，而小 E，则是 E 国之王。

树木，是 E 国抵挡袭击的法宝。树木越高，越能蒙蔽敌人的视线。

可是，随着自然条件的退化，小 E 却不知怎么处理。怎么办呢？

## 题目描述

给定一个 $n$ 行 $n$ 列 的矩阵 $a$。

有 $q$ 组询问，每次给定一个 $v$，请将矩阵每一行任意重排（可以不重排），最大化**最大值不小于** $v$（也就是说，至少有一个不小于 $v$ 的数）的列数。请输出这个列数。

询问之间相互独立。换言之，每次询问前可以重新排列。


## 说明/提示

### 样例解释

原矩阵为 $\begin{bmatrix}9&9&8\\2&4&4\\3&5&3\end{bmatrix}$。

对于第一次询问，每一列的最大值 $9,9,8$ 均不小于 $v=5$，所以每一列都符合条件，答案为 $3$。显然无论怎么重排都不可能超过 $3$ 列（因为总共只有 $3$ 列），所以答案为 $3$。

### 数据规模与约定

**本题开启捆绑测试。**

| $\text{Subtask}$ | 分值 | $n \leq$ | $q \leq$ |
| :--------------: | :--: | :------: | :------: |
| $0$ | $10$ | $3$ | $10$ |
| $1$ | $40$ | $100$ | $10^3$ |
| $2$ | $50$ | $10^3$ | $5\times 10^5$ |

对于所有数据，$1 \leq n \leq 10^3$，$1 \leq q \leq 5\times 10^5$，$1 \leq a_{i,j}, v \leq 10^9$。

## 样例 #1

### 输入

```
3 3
9 9 8
2 4 4
3 5 3
5
9
10```

### 输出

```
3
2
0```

# 题解

## 作者：include13_fAKe (赞：7)

## 前言
这是我第一次自己完成洛谷月赛的 Div.2B。

但因为这天下午我在和小伙伴下棋，没能按时参与月赛。

## 题意
给定一个 $n$ 行 $n$ 列 的矩阵 $a$。

有 $q$ 组询问，每次给定一个 $v$，请将矩阵每一行任意重排（可以不重排），最大化**最大值不小于** $v$（也就是说，至少有一个不小于 $v$ 的数）的列数。请输出这个列数。

询问之间相互独立。换言之，每次询问前可以重新排列。
## 思路
### Subtask 1:
枚举重排的所有情况，时间复杂度 $O(qn!^{n})$。
### Subtask 2:
首先发现一个性质：**既然矩阵可以重排，则最好要把大的数放在不同的列中。**

然后，我们可以发现：**一个数无论在哪一行，都可以被放在任何一列。**

我们可以将 $a$ 数组里的数从大到小排序（我是从小到大排序的，这样做很麻烦）。

然后，顺序枚举 $a$ 数组中的每一个数。计算有多少个数 $\ge v$。

但是，$\ge v$ 的数的数量可能会 $\ge n$，此时，肯定有多个 $\ge v$ 的数被放在了同一列。此时直接输出 $n$ 即可。

时间复杂度 $O(nq)$。

其实，即使不排序也能过。时间复杂度 $O(n^{2}q)$。
### Subtask 3:
实现得较好、常数较小的 $O(nq)$ 算法已经可以过了。

但我们排了序的，又可以怎样优化呢？**二分！**
 
此外，我们可以先判断 $\ge v$ 的数的数量是否 $\ge n$，以及 $\ge v$ 的数的数量是否 $=0$。

然后我们在前 $n$ 大的数中二分即可。

时间复杂度 $O(q$ $log$ $n)$。
## 代码
我就是从小到大排序的，这样做很麻烦（前面已经说过了）。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
int n;
int q;
int cnt;
int a[N];
void solve(int v){
	int l=n*(n-1)+1;
	int r=n*n;
	if(v<=a[l]){
		printf("%d\n",n);
		return;
	}
	if(v>a[r]){
		printf("0\n");
		return;
	}
	int mid=l+r>>1;
	while(l<r){
		if(v<=a[mid])	r=mid;
		else	l=mid+1;
		mid=l+r>>1;
	}
	printf("%d\n",n*n+1-l);
	return;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int num;
			scanf("%d",&num);
			a[++cnt]=num;
		}
	}
	sort(a+1,a+cnt+1);
	while(q--){
		int v;
		scanf("%d",&v);
		solve(v);
	}
} 
```


---

## 作者：Meny__love (赞：4)

# 传送门
[P9497 「RiOI-2」weight](https://www.luogu.com.cn/problem/P9497)
# 思路
其实理解一下题目，可以发现只要大于查询数 $v$ 的数有几个，就代表每列可以有几个，
那就可以直接将所有数存到一个数组里，再用 ```
sort``` 排序将数组弄为有序的（为方便使用，我选用升序），再用二分查询数组里第一个大于或等于查询数 $v$ 的数，对应其下标 $i$ ，用 $n-i+1$ 输出即可得列数。
# Code
```
#include<bits/stdc++.h>
using namespace std;
int a[1000005],len;
bool cmp(int a,int b){
	return a>b;
}
int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[++len]);
		}
	}
	sort(a+1,a+1+len);
	for(int i=1;i<=q;i++){
		int x;
		scanf("%d",&x);
		int mid=lower_bound(a+1,a+len+1,x)-a;
		int mid1=upper_bound(a+1,a+len+1,x)-a;//对于这个函数不是太熟悉，所以用了俩
		if(a[mid]==x) printf("%d\n",min(len-mid+1,n));
		else if(a[mid1]>x) printf("%d\n",min(len-mid1+1,n));
		else printf("0\n");
	}
	return 0;
} 
```


---

## 作者：ruanshaochuan______ (赞：1)

由于每一行都可以随意移动，所以我们只需要统计矩阵中  $a_{i,j}\ge v$ 的个数，如果直接暴力枚举时间复杂度为 $O(n^2q)$ 肯定会超时，于是我们使用一维数组存储，将数组从大到小排序，输出便为矩阵中最小的 $a_{i,j}\ge v$ 的下标，二分查找即可。   
时间复杂度为 $O(\log{n^2}q)$ 不会超时。  
code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[1000005],t,maxx,sum,mini=1e9;
int find(int x)
{
	int lt=0,rt=n+1;
	while(lt+1!=rt)
	{
		int mid=(lt+rt)/2;
		if(a[mid]<x)
			rt=mid;
		else
			lt=mid;
	}
	return lt;
}
bool cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	cin>>n>>q;
    n=pow(n,2);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		mini=min(mini,a[i]);
	}	
	while(q--)
	{
		cin>>t;
		if(t<mini)
        {
            cout<<sqrt(n)<<endl;
            continue;
        }
        int t1=sqrt(n);
		cout<<min(t1,find(t))<<endl;
	}
}
```


---

## 作者：251Sec (赞：1)

首先原题意相当于：对于每一列，在原矩阵每一行选择一个未被选择过的数，对 $n$ 列依次进行这样的决策。

一个显然的观察是：答案不可能超过「大于等于 $x$ 的数的个数」，也不可能超过 $n$，我们考虑证明这个上界是可以达到的。

考虑贪心，对于每一列，我们在某一行选择一个大于等于 $x$ 的数之后，在其它行**都选择小于 $x$ 的数**。那么最终符合条件的列数是大于等于 $x$ 的数的个数和 $n$ 取 $\min$。

你可能会说，这个贪心不一定成立啊？的确。那么什么时候上述贪心无法进行呢？我们发现，无法进行这样的贪心当且仅当，某次决策时，未被决策的数里，某一行的所有数都大于等于 $x$。而某一行的所有数都大于等于 $x$，那么剩下的列无论怎么选择，都满足**至少一个数大于等于 $x$**。

于是我们得到：答案就是大于等于 $x$ 的数的个数，和 $n$ 取 $\min$。

考虑如何求大于等于 $x$ 的数的个数。我们可以把矩阵中所有数排序，然后利用二分查找。复杂度 $O((n^2+q)\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, q;
int w[1000005];
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n * n; i++) {
        scanf("%d", w + i);
    }
    sort(w + 1, w + n * n + 1);
    while (q--) {
        int x;
        scanf("%d", &x);
        printf("%lld\n", min(1ll * n, 1ll * n * n - (lower_bound(w + 1, w + n * n + 1, x) - w) + 1));
    }
    return 0;
}
```

---

## 作者：rainygame (赞：0)

赛时 5min 想出来方法。

翻译一下题意：给定 $n$ 个长度为 $n$ 的数列。有 $q$ 次询问，每次询问 $n$ 个数列不小于 $v$ 的数的和与 $n$ 的最小值。

考虑离线，首先把 $n$ 个数列都降序排序，然后再对询问进行降序排序。对于每一个数列，设一个指针表示扫到哪里。

这样，对于每一次询问，我们就可以对每个指针扫一下，看一下能扫到哪里。然后每个指针的走过的长度就是这次询问的答案。因为询问是降序的，所以往前扫一定可以使得指针不降。

最后记得和 $n$ 取 $\min$。

代码实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 1001
#define MAXM 500001

int n, q, v, ind;
int it[MAXN], ans[MAXM];
int a[MAXN][MAXN];

struct Node{
	int ind, v;
}nodes[MAXM];

bool cmp(Node a, Node b){
	return a.v > b.v;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> q;
    for (int i(1); i<=n; ++i){
    	for (int j(1); j<=n; ++j) cin >> a[i][j];
    	sort(a[i]+1, a[i]+n+1, greater<int>());
    	it[i] = 1;
	}
	for (int i(1); i<=q; ++i){
		cin >> nodes[i].v;
		nodes[i].ind = i;
	}
	sort(nodes+1, nodes+q+1, cmp);
	
	for (int i(1); i<=q; ++i){
		v = nodes[i].v;
		ind = nodes[i].ind;
		for (int j(1); j<=n; ++j){
			while (it[j] <= n && a[j][it[j]] >= v) ++it[j];
			ans[ind] += it[j]-1;
		}
		ans[ind] = min(ans[ind], n);
	}
	for (int i(1); i<=q; ++i) cout << ans[i] << '\n';

    return 0;
}
```

可以发现操作指针的 `++it[j]` 至多跑 $n^2$ 次，所以最内层的循环直接算成一个 $n^2$。

时间复杂度 $O(n^2 \log n+q \log q+qn + n^2)=O(n^2 \log n+q(n+\log q))$，卡卡也能过。

但是如果 $q$ 开到 $5\times 10^6$ 的话，很有可能卡不过去了。

所以考虑优化。我们发现每次求和太麻烦了，所以可以储存一下上一次的答案，然后再计算比上一次加了多少，这样就不用每次都求和了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 1001
#define MAXM 500001

int n, q, v, ind, lans, cnt;
int it[MAXN], ans[MAXM];
int a[MAXN][MAXN];

struct Node{
	int ind, v;
}nodes[MAXM];

bool cmp(Node a, Node b){
	return a.v > b.v;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> q;
    for (int i(1); i<=n; ++i){
    	for (int j(1); j<=n; ++j) cin >> a[i][j];
    	sort(a[i]+1, a[i]+n+1, greater<int>());
    	it[i] = 1;
	}
	for (int i(1); i<=q; ++i){
		cin >> nodes[i].v;
		nodes[i].ind = i;
	}
	sort(nodes+1, nodes+q+1, cmp);
	
	for (int i(1); i<=q; ++i){
		v = nodes[i].v;
		ind = nodes[i].ind;
		cnt = 0;
		for (int j(1); j<=n; ++j){
			while (it[j] <= n && a[j][it[j]] >= v){
				++it[j];
				++cnt;
			}
		}
		ans[ind] = min(lans+cnt, n);
		lans = ans[ind];
	}
	for (int i(1); i<=q; ++i) cout << ans[i] << '\n';

    return 0;
}
```

时间复杂度 $O(n^2 \log n+n^2+q)=O(n^2 \log n+q)$。看起来挺假的，因为实际上有两层明显看出运行次数的循环，而且跑的也挺慢的。

---

## 作者：Aegleseeker_ (赞：0)

## 题目思路

首先考虑贪心，为了让尽可能多列的最大值大于等于 $v$，我们希望把大于等于 $v$ 的所有数**平均地**分配在每一列，也就是说每一列只需要保留 $1$ 个大于等于 $v$ 的数就行了，所以答案为 $\min(n,cnt_v)$，其中 $cnt_v$ 表示矩阵中大于等于 $v$ 的数的个数。

经过思考可以发现，其实用二维数组存一个矩阵是完全没有必要的，因为我们只需要计算矩阵中大于等于 $v$ 的数的个数，所以完全可以开一个大小为 $n^2$ 的数组，统计数组中大于等于 $v$ 的数的个数即可。

另外，在查找“数组中大于等于 $v$ 的数的个数”中，我们可以使用二分法优化，利用 STL 中的 `lower_bound` 函数实现查找，这个函数的功能是用二分法以 $\log$ 的时间复杂度查询**第一个大于等于要查找元素的元素的位置**，这样就可以解决此题了并且不会 TLE。

温馨提示：二分前一定要先排序。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,q;
int a[N*N];
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
}
int main(){
	n=read();
	q=read();
	for(int i=0;i<n*n;i++){	//n^2数组维护
		a[i]=read();
	}
	sort(a,a+n*n);	//一定要先排序！注意数组大小
	while(q--){
		int v=read();
		int p=lower_bound(a,a+n*n,v)-a;	//函数返回的是地址，要-a
		if(p==n*n){
			puts("0");
		}else{
			write(min(n,n*n-p));	//答案要和n取min，因为答案最多为n
			puts("");
		}
	}
	return 0;
}
```


---

## 作者：KidzzZip (赞：0)

## 题目大意
给出 $n×n$ 的矩阵，有 $q$ 次询问，给出 $v$ 求有几个数 $≥v$，如果 $≥v$ 的数字的数量 $≥n$，输出 $n$。
## 题目思路
根本不需要管什么矩阵，和什么重新排列，我们只需要找有多少个数 $≥v$ 即可，将数据用一维数组存起来然后排序。
```cpp
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			scanf("%d",&a[++cnt]);
		}
	}
	
	sort(a+1,a+cnt+1);
```
接着我们来找v在数组中的位置，因为 $1≤n×n≤10^6$，我们使用二分来找。
```cpp
int getnum(int x)
{
	int l=1,r=cnt,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(a[mid]<x)l=mid+1;
		else r=mid-1;
	}
	return r;//返回右端点而不是左端点因为要包括v自己。
}
```
最后如果 $cnt-getnum(x)≥ n$ 输出 $n$。
## 代码

```cpp
#include<bits/stdc++.h>
#define N 10000001
using namespace std;

int a[N],cnt=0,n,q,maxn;

int getnum(int x)
{
	int l=1,r=cnt,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(a[mid]<x)l=mid+1;
		else r=mid-1;
	}
	return r;
}

int main() {
	
	
	scanf("%d%d",&n,&q);
	
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			scanf("%d",&a[++cnt]);
		}
	}
	
	sort(a+1,a+cnt+1);
	
	
	for(int i=1;i<=q;i++) {
		int x;
		scanf("%d",&x);
		int sum=getnum(x);
		printf("%d\n",min(n,cnt-sum));
	}
	
	
	return 0;
}
```




---

## 作者：fuwei123 (赞：0)

由于每行可以无限制的交换，每行只要有任意一个数 $x\ge v$，就可以去看下一行了。所以，这个数到底在哪一行就是不重要的，我们可以把整个矩阵看成一个序列，将整个序列排序之后二分查找第一个 $a_i<v$ 的位置，$\min(i-1,n)$ 就是答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005], n, q, cnt;

bool cmp(int a, int b){
	return a > b;
}
signed main(){
	ios::sync_with_stdio(0);
	cin >> n >> q;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			cin >> a[++cnt];
		}
	}
	sort(a + 1, a + cnt + 1, cmp);
	while(q--){
		int x;
		cin >> x;
		int ans = 0, l = 1, r = cnt;
		while(l <= r){
			int mid = (l + r) / 2;
			if(a[mid] < x)r = mid - 1;
			else{
				l = mid + 1;
				ans = mid;
			}
		}
		cout << min(ans, n) << "\n";
	}
	return 0;
}
```

---

## 作者：_Joseph_ (赞：0)

# P9497 题解

## 题目描述：

给定一个 $n$ 行 $n$ 列的矩阵 $a$；有 $q$ 组询问，每次给定一个 $v$,请将矩阵每一行任意重排（可以不重排），最大化最大值不小于 $v$（也就是说，至少有一个不小于 $v$ 的数）的列数。请输出这个列数。

询问之间相互独立。换言之，每次询问前可以重新排列。

## 思路讲解：

1. 我们可以把这个 $n \times n$ 的图用一维数组来存。

```cpp
scanf("%lld%lld", &n, &q);//输入n和q
	for (int i = 1; i <= n * n; i++) scanf("%lld", &a[i]);//存这个图
```

2. 然后再排一下序，最后再枚举一下。

```cpp
for (int i = 1; i <= n * n; i++) {
			if (a[i] >= m) res++;
			else break;
			if (res == n) break;
			
		}
```
注意这里有一个细节，就是在：

```cpp
a[i] < m;
```

时就可以退出循环了。当：

 ```cpp
res == n;
```

时也要退出循环这是一个小小的优化。如果不退出的话会 TLE。

**完整代码也不难就不放了，就放一个 [AC 记录](https://www.luogu.com.cn/record/119717438)，要自己思考。**

---

