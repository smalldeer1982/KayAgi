# [USACO13JAN] Cow Lineup G

## 题目描述

Farmer John's N cows (1 <= N <= 100,000) are lined up in a row.  Each cow is identified by an integer "breed ID" in the range 0...1,000,000,000; the breed ID of the ith cow in the lineup is B(i).  Multiple cows can share the same breed ID.

FJ thinks that his line of cows will look much more impressive if there is a large contiguous block of cows that all have the same breed ID.  In order to create such a block, FJ chooses up to K breed IDs and removes from his lineup all the cows having those IDs.  Please help FJ figure out the length of the largest consecutive block of cows with the same breed ID that he can create by doing this.

农夫约翰的N(1 <= N <= 100,000)只奶牛排成了一队，每只牛都用编上了一个“血统编号”，该编号为范围0...1,000,000,000的整数。血统相同的奶牛有相同的编号，也就是可能有多头奶牛是相同的"血统编号"。

约翰觉得如果连续排列的一段奶牛有相同的血统编号的话，奶牛们看起来会更具有威猛。为了创造这样的连续段，约翰最多能选出k种血统的奶牛，并把他们全部从队列中赶走。


请帮助约翰计算这样做能得到的由相同血统编号的牛构成的连续段的长度最大是多少？


## 说明/提示

There are 9 cows in the lineup, with breed IDs 2, 7, 3, 7, 7, 3, 7, 5, 7. FJ would like to remove up to 1 breed ID from this lineup.


By removing all cows with breed ID 3, the lineup reduces to 2, 7, 7, 7, 7, 5, 7.  In this new lineup, there is a contiguous block of 4 cows with the same breed ID (7).


## 样例 #1

### 输入

```
9 1 
2 
7 
3 
7 
7 
3 
7 
5 
7 
```

### 输出

```
4 
```

# 题解

## 作者：NTG_Adiord (赞：19)

~~这题为啥是蓝的啊~~

离散化，然后再。。。。。算了代码解释

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
map<int,int> mp;
//离散化
int a[100001];
//存离散化后的数组
int hav[100001];
//存当前区间内，对应数字出现过的次数
int mxl;
//反正就是计数一下
int typ,k;//当前区间里有多少种
int ans;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(!mp[a[i]])mp[a[i]]=++mxl;
        //如果当前数字没有出现过，就给他分配一个新的离散化值
		a[i]=mp[a[i]];
	}
	int l=1,r=0;
    //区间
	while(r<=n){
		r++;
        //右移
		if(hav[a[r]]==0)typ++;//如果这个数字第一次出现，种类++
		hav[a[r]]++;
		while(typ==k+2){
        //删除k种，说白了允许当前区间内有k+1种
        如果是k+2种就得删除了
			hav[a[l]]--;
        //左界右移，减少左界位置上值得数量
			if(hav[a[l]]==0)typ--;
        //没了就种类--
			l++;
		}
		ans=max(ans,hav[a[r]]);
        //统计答案
	}
	printf("%d",ans);
    //输出
}

```
一开始看这道题，蓝的，打算先放放

看了好几篇题解，set,balabala,什么玩意....

~~按照多篇题解的想法打了一下，也就这样~~


---

## 作者：牛蛙丶丶 (赞：12)

#### 2-pointer 练习题

根据题意，为了创造连续排列的一段相同类型的牛，我们可以去除掉队列里 k 种血统的奶牛，所以我们的排列里最多只能有 k+1 种奶牛，所以我们可以用两个指针进行扫描，用一个 map 来记录每个类型的数量，将右指针向右移动，并将没有出现过的类型累加到答案之中，当序列中有 k+2 种奶牛时，就要将左指针向右移动直至序列中的奶牛数小于 k+2 。最后取一个右指针代表类型在序列中的数量的最大值即可。

#### code

```cpp
#include <cstdio>
#include <algorithm>
#include <map>
#define sf(x) scanf("%d",&x)
#define pf(x) printf("%d\n",x)
#define N 100077
using namespace std;

map<int,int>g;
int n,k;
int a[N];

int main(){
	sf(n),sf(k);
	for(int i=1;i<=n;++i) sf(a[i]);
	int l=1,r=0,cnt=0,ans=0;
	while(r<=n){
		if(++g[a[++r]]==1) cnt++;
		while(cnt==k+2)
			if(!(--g[a[l++]])) cnt--;
		ans=max(ans,g[a[r]]);
	}
	pf(ans);return 0;
}	
```



---

## 作者：1saunoya (赞：9)

$\text{单调队列的裸题}$

转换一下题意。。 就是一个序列中不能有 $k + 2$ 种奶牛

我们考虑$l$ 和 $r$ 指针

所以当$k+2$种的时候我们就将左指针往右不停移 那么就可以做到$\mathcal{0(N)}$的了

相对于其他题解 我的题解比较简洁

$\mathcal Code$

```cpp
#include<cstdio>
#include<map>
int n , k ;

std :: map < int  , int > cnt ;

const int N = 1e5 + 10 ;
int a[N] ;
inline int max(int x , int y) {
	return x > y ? x : y ;
}
signed main() {
	scanf("%d %d" , & n , & k) ;
	for(register int i = 1 ; i <= n ; i ++) scanf("%d" , & a[i]) ;
	int l = 1 , r  = 0 ;
	int kind = 0 ;
	int ans = 0 ;
	while( r <= n ) {
		if(++ cnt [ a[++ r]] == 1) kind ++ ;
		while( kind == k + 2 ) {
			if(-- cnt[ a[l ++]] == 0) kind -- ;
		}
		ans = max (ans , cnt[a[r]]) ;
	}
	printf("%d\n" , ans) ;
	return 0 ;
}

---

## 作者：icypenguin (赞：2)

提供一种无脑做法。

题目要求求出连续段的长度最大的值，我们想到二分，每次 ```check``` 这个值是否合法，二分的区间是 $1 \sim n$。

怎么 ```check``` 呢？我们先把奶牛的编号离散化，然后把奶牛按照编号分类，即创建一个 ```vector``` 按照编号放奶牛的位置。我们在 
 ```check``` 连续段的长度最大的值是否能达到 $x$ 时，我们可以通过 ```vector``` 找到在同一个编号 ```vector``` 的下标距离为 $x$ 的所有区间，并把这些区间存储下来，供查询使用。显然，接下来需要判断一个区间是否有不超过 $k + 1$ 个不同的值（因为包含这个编号），这个可以使用一个桶来记录，然后这些区间的查询通过莫队来维护——我们直接维护区间的值的出现次数即可，当出现次数从 $1$ 变成 $0$ 时，将答案减少一个数，当出现次数从 $0$ 变成 $1$ 时。
 
时间复杂度是 $O(n \sqrt n \log n)$ 的，但是由于莫队常数小，最大点的用时不超过一百毫秒。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, k, b[100005], cntx = 0, cnt = 0, bel[100005], blocks, t[100005];
map<ll, ll> mp, mp2;
struct node{
    ll l, r, idx;
};
vector<ll> vc2[100005];
vector<node> vc[100005];
bool cmp1(node a, node b){
    return a.r < b.r;
}
bool check(ll mid){
    for (ll i = 1; i <= cnt; i++){
        vc[i].clear();
    }
    ll tot = 0;
    for (ll i = 1; i <= n; i++){
        if (vc2[i].empty()){
            continue;
        }
        for (ll j = 0; j < vc2[i].size(); j++){
            ll k = j + mid - 1;
            if (k >= vc2[i].size()){
                break;
            }
            tot++;
            vc[bel[vc2[i][j]]].push_back(node{vc2[i][j], vc2[i][k], tot});
        }
    }
    for (ll i = 1; i <= cnt; i++){
        sort(vc[i].begin(), vc[i].end(), cmp1);
    }
    ll nowl = 1, nowr = n, as = 0;
    for (ll i = 1; i <= n; i++){
        t[b[i]] = 0;
    }
    for (ll i = 1; i <= n; i++){
        t[b[i]]++;
        if (t[b[i]] == 1){
            as++;
        }
    }
    for (ll i = 1; i <= cnt; i++){
        for (ll j = 0; j < vc[i].size(); j++){
            while (nowl < vc[i][j].l){
                t[b[nowl]]--;
                if (t[b[nowl]] == 0){
                    as--;
                }
                nowl++;
            }
            while (nowl > vc[i][j].l){
                nowl--;
                t[b[nowl]]++;
                if (t[b[nowl]] == 1){
                    as++;
                }
            }
            while (nowr < vc[i][j].r){
                nowr++;
                t[b[nowr]]++;
                if (t[b[nowr]] == 1){
                    as++;
                }
            }
            while (nowr > vc[i][j].r){
                t[b[nowr]]--;
                if (t[b[nowr]] == 0){
                    as--;
                }
                nowr--;
            }
            ll qs = as - 1;
            if (qs <= k){
                return true;
            }
        }
    }
    return false;
}
int main(){
    scanf("%lld %lld", &n, &k);
    blocks = sqrt(n);
    for (ll i = 1; i <= n; i += blocks){
        cnt++;
        for (ll j = i; j <= i + blocks - 1; j++){
            bel[j] = cnt;
        }
    }
    for (ll i = 1; i <= n; i++){
        scanf("%lld", &b[i]);
        mp[b[i]]++;
    }
    for (auto it : mp){
        mp2[it.first] = ++cntx;
    }
    for (ll i = 1; i <= n; i++){
        b[i] = mp2[b[i]];
    }
    for (ll i = 1; i <= n; i++){
        vc2[b[i]].push_back(i);
    }
    ll l = 1, r = n, ans = 0;
    while (l <= r){
        ll mid = (l + r) / 2;
        if (check(mid)){
            ans = mid;
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：SBofGaySchool (赞：2)

这题我大意了啊，看到树状数组的标签满脑子想的都是树状数组……那我就来一篇 **树状数组 × 二分** 的题解吧。

### 1. 求解区间内有多少种不同元素

这等价于求解在这个区间内 **有多少个元素的后面没有与之相同的元素**，这样正好可以做到每种元素恰好计算一次。

显然，如果在这个区间内，某个元素的后面有一个与之相同的元素，那么前面的这个元素就可以“作废”了。如果我们能够求出区间内所有被“作废”的元素个数，再用区间长度减去这一数量，即为答案。

对于区间 $[L, R]$ 的询问，我们扫描 $1$ 到 $R$ 之间的所有元素。对于每个元素，我们将 **与其相同的上一个元素（这个元素即“作废”）的位置** 插入到一个负责存储作废元素位置的树状数组中，然后询问这个树状数组中有多少元素的值在 $[L, R]$ 范围内，即可求出 $[L, R]$ 内有多少个元素“作废”了。

更多详情请看 [P1972 \[SDOI2009\]HH的项链 题解](https://www.luogu.com.cn/problem/solution/P1972)。

### 2. 本题思路

显然，答案序列一定会以某头奶牛结尾，并且 **选择该头奶牛的血统（踢出其他血统的奶牛）**。

那么我们枚举每头奶牛：

1. 先求出以 **该奶牛作为结尾的，最长的，血统种数不超过 $K+1$** 的奶牛区间；
2. 再求出 **这个区间内，与该奶牛血统相同的奶牛的数量**，并更新答案；

即可完成本题。

对于第一步，可以观察到，对于以某头奶牛为结尾的区间，随着长度不断变长，**奶牛血统种数单调不减**。所以，使用二分法即可求解出 **以该奶牛为结尾的，最长的，血统种数不超过 $K+1$** 的奶牛区间。

在二分的过程中，我们需要求解某个区间内奶牛血统种数。可以用题解中第一部分描述的方法进行求解。

得到最长区间后，我们要求出 **该区间内，与最后一头奶牛血统相同的奶牛的数量**。我们可以分别记录每种血统的奶牛出现的所有位置，再使用二分法求出该区间内有多少头对应血统的奶牛即可。

当然，由于奶牛血统取值范围太广，我们需要首先进行离散化。

由于要枚举每头奶牛，又要二分求解以其为结尾的最长区间，每次二分判断的时候还要涉及到树状数组操作，故整体时间复杂度为 $O(N\log ^2 N)$。慢的一批，但是由于数据规模和常数都比较小，因此可以轻松通过本题。

### 3. 代码实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXN 100005
int N, K, B[MAXN];
pair<int, int> A[MAXN];
// 每种奶牛最后一次出现的位置
int prv[MAXN];
// 树状数组
int tn[MAXN];
// 存储每种血统的奶牛出现的位置
vector<int> cnt[MAXN];
int tot = 0;
// 树状数组操作
inline void add(int i, int x) {
    if (!i) {
        return;
    }
    while (i <= N) {
        tn[i] += x;
        i += i & (-i);
    }
}
inline int get(int i) {
    int res = 0;
    while (i) {
        res += tn[i];
        i -= i & (-i);
    }
    return res;
}
int ans = 0;
// 枚举第i头奶牛以为结尾
void get_ans(int i) {
    int l = 1, r = i;
    // 二分法求出最长的，血统种类数不超过K+1的区间
    while (l < r) {
        int m = l + (r - l) / 2;
        // i-(m-1)为区间长度，get(i)-get(m-1)为这个区间内“作废”的奶牛数量
        // 两者相减即为区间内奶牛血统种类总数
        if (i - (m - 1) - (get(i) - get(m - 1)) - 1 <= K) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    int x = l;
    // 求解区间内有多少头奶牛的血统和第i头奶牛一致
    l = 0, r = cnt[B[i]].size();
    while (l < r) {
        int m = l + (r - l) / 2;
        if (cnt[B[i]][m] < x) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    if (ans < cnt[B[i]].size() - l) {
        ans = cnt[B[i]].size() - l;
    }
}
int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> A[i].first;
        A[i].second = i;
    }
    // 离散化
    sort(A + 1, A + N + 1);
    for (int i = 1; i <= N; i++) {
        B[A[i].second] = A[i].first == A[i - 1].first ? tot : ++tot;
    }
    // 枚举每头奶牛
    for (int i = 1; i <= N; i++) {
        // 将相同血统的上一头奶牛的位置加入树状数组中，即将其“作废”
        add(prv[B[i]], 1);
        prv[B[i]] = i;
        // 记录自己出现的位置
        cnt[B[i]].push_back(i);
        // 求解并更新答案
        get_ans(i);
    }
    cout << ans << endl;
	return 0;
}
```

---

## 作者：高天 (赞：2)

```cpp
#include<iostream>
#include<queue>
#include<map>
using namespace std;
int main() {
	int n, cnt, k, a[100005], sum[100005] = {0};
	deque<int> dq;
	map<int, int> mp; //键key 值 value
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		a[i] = x;
		if(mp[x] == 0) { //之前没出现过这种血统
			cnt++;
			mp[x] = cnt; //离散化 ，血统为x的奶牛数量为cnt,统x改成血统cnt，保证血统的编号在1到100000
		}
	}
	int ans = 0, kind = 0; //最后的结果、牛的种类数
	for(int i = 1; i <= n; i++) {
		int x = a[i]; //血统
		if(sum[mp[x]] == 0) { //第一次出现该血统
			kind++;
		}
		sum[mp[x]]++; //血统为x的奶牛数量++
		dq.push_back(i); //入队
		while(kind > k + 1) {
			int tmp = dq.front();
			dq.pop_front();//弹出 
			int y = a[tmp];//离散化 
			sum[mp[y]]--; 
			if(sum[mp[y]] == 0) {
				kind--;//不满足 
			}
		}
		ans = max(ans, sum[mp[x]]); //维护最大值，可以放在while之前吗？
	}
	cout << ans;
	return 0;
}
```


---

## 作者：浮尘 (赞：2)

感觉这道题略水，看代码吧

```
#include<iostream>
#include<queue> 
#include<map>
using namespace std;
int main()
{
	int n, cnt, k, a[100005], sum[100005] = {0};
	deque<int> dq; 
	map<int, int> mp; //键key 值 value
	cin >> n >> k;
	for(int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		a[i] = x;
		if(mp[x] == 0) //之前没出现过这种血统 
		{
			cnt++;
			mp[x] = cnt; //离散化，把血统x改成血统cnt，保证血统的编号在1到100000
		}
	}
	int ans = 0, kind = 0; //最后的结果、牛的种类数 
	for(int i = 1; i <= n; i++)
	{
		int x = a[i]; //血统 
		if(sum[mp[x]] == 0) //第一次出现该血统 
		{
			kind++;
		}
		sum[mp[x]]++; //血统为x的奶牛数量++
		dq.push_back(i); //入队 
		while(kind > k + 1)
		{
			int tmp = dq.front();
			dq.pop_front();
			int y = a[tmp];
			sum[mp[y]]--;
			if(sum[mp[y]] == 0)
			{
				kind--;
			}
		}
		ans = max(ans, sum[mp[x]]); //维护最大值，可以放在while之前吗？ 
	}
	cout << ans;
    return 0;
}

```


---

## 作者：Cutest_Junior (赞：1)

## 题解 P3069 【[USACO13JAN]Cow Lineup G】

### 题意

+ $n$ 头牛排成一队，每头牛有一个编号；
+ 最多选 $k$ 个数，把编号在这些数里的牛删掉；
+ 求删掉后，编号相同的连续段的最大长度；
+ $n\le100000$，编号 $\le10^9$。

### 解法

把编号相同的牛看成是同一种类的牛。

可以把题目看成是：在每个只有 $k+1$ 种牛的区间中，求数量最多的种类的牛的数量。（有点像绕口令，但我的语文能力有限，我尽力了>_<）

这点不难证明，只有 $k+1$ 种牛的区间，删掉 $k$ 种，一定是编号相同的、连续的区间。

--------

现在的难点是，如何求数量最多的种类的牛的数量。

这点其他题解讲的不是很清楚，我看题解的时候想了好久才想明白，所以我会重点讲一下这部分。

#### 朴素算法

1. 求出每个区间的总复杂度是 $O\left(n\right)$;
1. 朴素地每次比较所有种类的牛的数量，因为比较的个数永远是 $k$，所以复杂度为 $O\left(k\right)$
1. 编号 $\le10^9$，所以肯定要用 map，也就是要有 $O\left(\log n\right)$ 的查询复杂度；

综上，朴素算法的复杂度为 $O\left(nk\log n\right)$

我没找到 $k$ 的范围，翻译没有，我英语又不好，~~谷歌生草机还是阴间翻译~~。

但我们知道 $k$ 一定不会比 $n$，所以上述复杂度不可过。

#### 贪心

也许可以想到一种贪心：以每头牛结尾的区间，用该头牛的种类的数量更新答案。

证明：

设在区间 $\left[l,r\right]$ 中，编号为 $x$ 的数量是最优解，区间中最后一个编号为 $x$ 的牛的位置为 $i$。

那么在扫到以 $i$ 结尾的区间时，$x$ 的数量一定不小于 $\left[l,r\right]$ 中 $x$ 的数量（自己思考一下)。

综上所述，贪心正确。

### 代码

终于讲完了，好累啊。

```cpp
# include <iostream>
# include <map>

using namespace std ;

const int N = 100005 ;

int arr [ N ] ;

int main ( )
{
    int n , k ;
    cin >> n >> k ;
    
    for ( int i = 1 ; i <= n ; ++ i )
    {
        cin >> arr [ i ] ;
    }
    
    map < int , int > ma ; // 编号 -> 数量
    
    int ans = 0 ;
    
    int first = 1 ; // 区间左端点
    
    for ( int i = 1 ; i <= n ; ++ i )
    {
        ++ ma [ arr [ i ] ] ; // 加入区间
        
        while ( ma . size ( ) > k + 1 ) // 大于区间最大数量就把 first 前移
        {
            -- ma [ arr [ first ] ] ;
            
            if ( ma [ arr [ first ] ] == 0 )
            {
                ma . erase ( arr [ first ] ) ;
            }
            
            ++ first ;
        }
        
        ans = max ( ans , ma [ arr [ i ] ] ) ; // 应用贪心，更新答案
    }
    
    cout << ans ;
}
```

---

## 作者：优少 (赞：1)

看了看其他大佬的文章，为什么要控制右端呢

其实就是一个很简单的**模拟队列**趴。。。

难点就在于根据题意我们可以分析得一段合法区间内，**不同种类个数不能超过k+2**

哦当然，由于种类数范围过大，要对种类进行**离散化**，可以使用STL的map

剩下的就是模拟了,详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> f;
int ty,tot,k,n,ans;
int type[100010];                   
int num[100010];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){            //输入+离散化 
		scanf("%d",&ty);                             
		if(f[ty]) type[i]=f[ty];     //出现过的给原来的编号 
		else type[i]=++tot,f[ty]=tot;   //没出现的更新编号并记录 
	}
	int cnt=1,head=1;num[type[1]]++;    
	for(int i=2;i<=n;i++){
		while(cnt>=k+2){                //当区间内种类数量大于k+2时左端点右移直到个数小于k+2 
			num[type[head]]--;         
			if(num[type[head]]==0)      //当一个种类数量减为零，区间内种类减一 
			   cnt--;
			head++;
		}
		if(!num[type[i]]) cnt++;       //更新 
		num[type[i]]++;
		ans=max(ans,num[type[i]]);	  //用当前种类更新 
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：heyuhhh (赞：1)

## 思路
考虑比较朴素的解法，枚举每个长度为$k+1$的区间，然后统计区间中出现次数最多的颜色。这样的话复杂度为$O(n*k)$的，显然不行。

观察到统计每个区间中出现次数最多的颜色中，可以只用看每种颜色在区间中出现的最后一个位置，这样的话只需要我们开个桶统计一下数量就行。

所以就类似于尺取那样，维护颜色种类不超过$k+1$的区间，对于每次新加进来的值令其$cnt++$，并且维护ans。当颜色种类超过$k+1$时，就减去区间前面的值，因为它们与后面的颜色不可能再连在一起了。

因为每个位置都会被指针扫到最多两次，所以复杂度是$O(n)$的。

直接看代码好了，注意要离散化一下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int n, k;
int a[N], b[N];
int cnt[N];
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i] ;
    sort(b + 1, b + n + 1);
    int D = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
    int num = 0, ans = 1;
    for(int l = 1, r = 0; r <= n;) {
        r++;
        if(cnt[a[r]]++ == 0) num++;
        while(num > k + 1) {
            cnt[a[l++]]--;
            if(!cnt[a[l - 1]]) num--;
        }
        ans = max(ans, cnt[a[r]]) ;
    }
    cout << ans;
    return 0;
}

```

---

## 作者：CrayonDing (赞：1)

对于这道题，我们首先可以推出一个事实：

在任意一个符合条件的区间里，答案是区间内最多的那类牛的数量。

我们只需要从左到右扫描整个队列，找到每一个只含k+1种牛的区间（删除k种+保留的一种），取每个区间内数量最多牛的数量即可。

注意点：
1、血统编号在0-1,000,000,000之间，需要离散化。

~~2、想不起来了，直接看代码吧 #滑稽~~


------------

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
const int maxn = 100010;
int n,k,cow[maxn],a[maxn];
int cnt;
map<int,int> l;

int getid(int num){//map离散化  
	if(!l[num])l[num]=++cnt;
	return l[num];
}

int main(){
	//freopen("lineup.in","r",stdin);
	//freopen("lineup.out","w",stdout);
	cin>>n>>k;
	int t;
	for(int i=1;i<=n;i++){//读入 
		cin>>t;
		a[i]=getid(t);
	}

	int ans = 1;
	int l=1,r=0,typ=0;
	while(r<=n){//滑动区间 
		r++;//右边界右移 
		if(cow[a[r]]==0)typ++;//发现新血统的牛 
		cow[a[r]]++;//区间内新血统牛数+1 
		while(typ>k+1){//区间内有超过k+1种血统的牛时，需要将左边界右移，既从队列中移除这种牛 
			cow[a[l]]--;
			if(cow[a[l]]==0)typ--;
			l++;
		}
		ans=max(ans,cow[a[r]]);//判断当前最右端的牛可以连成的最长数量 
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：devout (赞：0)

~~最差解来了~~

思路还是挺好想的一道题，但是看题解貌似和大家略微不同？（

就是我们找到一个拥有$k+1$种奶牛的区间，然后区间中**数量最多**的那种的数量再取一个$\max$就是答案，这个东西可以使用区间伸缩/尺取法/双指针 ~~都是一个东西~~ 来实现

然后~~听信算法标签~~往$\log$数据结构那里想了，然后因为要维护两个量（最大值和不同的种类有多少个），所以就写了个权值线段树。。。不过这题操作还挺简单，代码也没写多长

然后注意这里不同种类的数量是不能用前缀和维护的（估计只有我这么菜的才会想成前缀和吧），所以我们把他扔到权值树里面

然后就是极慢的$O(n\log n)$的代码了，~~不过这题要离散化必须有个log~~，但是查询复杂度稍慢一些，实际上跑出来在$700ms$左右，差不多中间水平吧

```
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,k;
int a[N],b[N];
int sz;
int head,tail;
int ans;

struct node{
    int l,r,max,tim;//权值线段树维护两个量，max表示数量最多的种类的数量，tim表示数量的个数(orz TimMc)
}seg[N<<2];

# define lc (u<<1)
# define rc (u<<1|1)

void pushup(int u){
    seg[u].max=max(seg[lc].max,seg[rc].max);
    seg[u].tim=seg[lc].tim+seg[rc].tim;
}

void build(int u,int l,int r){
    seg[u].l=l,seg[u].r=r;
    if(l==r)return;
    int mid=l+r>>1;
    build(lc,l,mid);
    build(rc,mid+1,r);
}

void update(int u,int x,int k){
    if(seg[u].l==seg[u].r){
        seg[u].max+=k;
        if(seg[u].max)seg[u].tim=1;
        else seg[u].tim=0;
        return;
    }
    int mid=seg[u].l+seg[u].r>>1;
    if(x<=mid)update(lc,x,k);
    else update(rc,x,k);
    pushup(u);
}//以上是权值线段树板子

int main()
{
    read(n),read(k);
    k++;//注意是删掉k种牛，所以区间可以用k+1种牛
    Rep(i,1,n)read(a[i]),b[i]=a[i];
    sort(b+1,b+n+1);
    sz=unique(b+1,b+n+1)-b-1;//离散化
    Rep(i,1,n)a[i]=lower_bound(b+1,b+sz+1,a[i])-b;
    build(1,1,sz);//建树
    head=1,tail=1;
    update(1,a[1],1);
    while(tail<=n){//这里我一般习惯固定右指针
        while(head<=tail&&seg[1].tim>k)update(1,a[head],-1),head++;//如果当前区间种类数比k大（其实是k+1但是我前面+过了），就head++
        ans=max(ans,seg[1].max);//更新答案
        tail++,update(1,a[tail],1);//右移一格
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：king_xbz (赞：0)

好像还没有用STL来写单调队列的题解，那我就来发一个吧!

这道题是一道比较裸的单调队列题，只不过需要离散化一下。

作为一个C++党，自然想到了STL。

那么废话不多说，我们开始解决问题，

先来离散化，我们需要用到映射————map。

map是STL中的关联容器，使用需要定义头文件
```cpp
#include<map>
```
我们利用其关联映射的性质，对数组进行离散化处理
```cpp
map <int,int>mp;
inline void pre(int x)
{
	if(!mp[a[x]])
	mp[a[x]]=++num;//若没出现过，就更新并记录
	a[x]=mp[a[x]];用a数组继续储存原a数组的关联值（可以省事少开一个数组）
	return ;
}
```
有了pre函数，我们就可以一边输入一边进行离散化处理了；
```cpp
for(fint i=1;i<=n;i++)
a[i]=read(),pre(i);
```
接下来就是单调队列。

如果不了解单调队列的同学可以->[单调队列模板](https://www.luogu.com.cn/problem/P1886)
模板AC代码->[点我](https://www.luogu.com.cn/paste/rczjks1o)

单调队列有许多的写法，大多是用模拟队列或者deque来做。However，受到我打单调栈模板题的思路的影响，这次我口胡了一个很神奇的双队列做法（[有兴趣的可以来看看我单调栈的双栈做法](https://www.luogu.com.cn/blog/kingxbz/solution-p5788)）
先上代码：
```cpp
queue <int>q; //处理种类
queue <int>s;//处理头指针
inline int begin_todo()
{
	int tot=0;
	q.push(1),s.push(1),ans[a[q.size()]]=1;//先把第一个入队
	for(fint i=2;i<=n;i++)
	{
		while(q.size()>=k+2)
		{
			ans[a[s.size()]]--;//若区间内种类数量大于k+2，左端点右移直到个数小于k+2 
			if(!ans[a[s.size()]])
			q.pop();
			s.push(i);//头指针增加
		}
		if(!ans[a[i]])
		q.push(i);//随着i的增加，种类增加
		ans[a[i]]++;
		tot=max(tot,ans[a[i]]);//求最大值
	}
	return tot;
}
```
这神奇的算法还是蛮巧妙的

最后上完整代码
```cpp
#include<bits/stdc++.h>
#define fint register int
#define h 5001
#define p 435433
#define int long long
using namespace std;
int num;
int n,k;
int a[p];
int ans[p];
map <int,int>mp;
queue <int>q; 
queue <int>s;
inline int read();
inline void pre(int x);
inline int begin_todo();
signed main()
{
    n=read();
    k=read();
    for(fint i=1;i<=n;i++)
    a[i]=read(),pre(i);
    cout<<begin_todo();
	return 0; 
}

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

inline void pre(int x)
{
	if(!mp[a[x]])
	mp[a[x]]=++num;
	a[x]=mp[a[x]];
	return ;
}

inline int begin_todo()
{
	int tot=0;
	q.push(1),s.push(1),ans[a[q.size()]]=1;
	for(fint i=2;i<=n;i++)
	{
		while(q.size()>=k+2)
		{
			ans[a[s.size()]]--;
			if(!ans[a[s.size()]])
			q.pop();
			s.push(i);
		}
		if(!ans[a[i]])
		q.push(i);
		ans[a[i]]++;
		tot=max(tot,ans[a[i]]);
	}
	return tot;
}
```
祝大家ac愉快

---

## 作者：小手冰凉 (赞：0)

STL真好用.jpg

这题首先我们可以发现只要区间内没有超过k+1中类型的牛，答案就是区间内最多的那一类

所以我们只要用上区间伸缩大法就好了

然后区间内最多的怎么求呢，map离散+set记录即可

十分无脑

```cpp
#include<bits/stdc++.h>
#define pa pair<int,int>
#define mk make_pair
using namespace std;
#define ll long long
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
    return x*f;
}
inline void write(ll x)
{
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
inline void writeln(ll x)
{
    write(x);
    puts("");
}
const int N=100005;
int a[N];
map<int,int>mmp;
int l,r,t,n,k;
set<pa>s;
int main()
{
	n=read();k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		s.insert(mk(0,a[i]));
	}
	l=1;
	t=0;
	int ans=0;
	for(int r=1;r<=n;r++){
		s.erase(mk(mmp[a[r]],a[r]));
		mmp[a[r]]++;
		s.insert(mk(mmp[a[r]],a[r]));
		if(mmp[a[r]]==1)t++;
		while(t>k+1){
			s.erase(mk(mmp[a[l]],a[l]));
			mmp[a[l]]--;
			s.insert(mk(mmp[a[l]],a[l]));
			if(mmp[a[l]]==0)t--;
			l++;
		}
		ans=max((*s.rbegin()).first,ans); 
	}
	writeln(ans);
}
```

---

