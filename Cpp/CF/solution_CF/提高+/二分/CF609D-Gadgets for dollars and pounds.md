# Gadgets for dollars and pounds

## 题目描述

一个人手上有 $s$ 卢布，他要在 $n$ 天内买 $m$ 样东西中的 $k$ 样。

每个物品有两种支付方式，要么用美元，要么用英镑。

每天有不同的支付方式代价，即换取一美元或英镑，需要付出 $x_i$ 卢布的代价。

求最早完成买 $k$ 样东西的天数。如果无法完成任务，输出 `-1`。

一种商品只能购买一次，但是一天可以买多种商品。

## 样例 #1

### 输入

```
5 4 2 2
1 2 3 2 1
3 2 1 2 3
1 1
2 1
1 2
2 2
```

### 输出

```
3
1 1
2 3
```

## 样例 #2

### 输入

```
4 3 2 200
69 70 71 72
104 105 106 107
1 1
2 2
1 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 3 1 1000000000
900000 910000 940000 990000
990000 999000 999900 999990
1 87654
2 76543
1 65432
```

### 输出

```
-1
```

# 题解

## 作者：TLE_Automat (赞：10)

## Problem D :

**（首行求赞qwq）**

题意：你手上有 $s$ 卢布，你要在 $n$ 天内从 $m$ 个物品中买走 $k$ 个。你一共有两种支付方式，但每个物品只有一种支付方式，对于第 $i$ 个物品：

- 如果 $t_i=1$ ，那么需要用 $c_i$ 美元购买。
- 如果 $t_i=2$ ，那么需要用 $c_i$ 英镑购买。

第 $i$ 天，你可以用 $a_i$ 卢布换 $1$ 美元，还可以用 $b_i$ 卢布换 $1$ 英镑。 求最早买走 $k$ 个东西的天数及方案。如果无法完成任务，输出 ```-1```。

**注意：每个物品只能购买一次，但是一天可以买多种商品**。

数据范围：$1\le n \le 2\cdot 10^5,1\le k\le m\le 2\cdot 10^5,1\le s\le 10^9,1\le a_i \le 10^6,1\le b_i\le 10^6$。

做法：首先，我们可以注意到一下两点：
- **决策单调性** ：如果我们第 $x$ 天可以买走 $k$ 个物品，那么第 $x$ 天往后一定可以买走 $k$ 个物品。

- **状态确定性**（口胡的） ：给定一个**确定的**天数 $x$，可以通过计算来**确定**在 $x$ 天之内能否买走 $k$ 件物品。

这两点性质就足以告诉我们这题的答案可以二分。

对于每一个二分的天数 $x$ ，我们可以维护一下从第 $1$ 天到第 $x$ 天美元汇率的最小值 $min\_d$ ，英镑汇率的最小值 $min\_p$ ，然后把每个物品的价格根据这个最小的汇率转化成卢布，然后从小到大排序，看排序后前 $k$ 个物品的花费总和是否大于 $s$，即可判断该方案的可行性。

时间复杂度：$O(nlog_2^2n)$ 。

$Code:$

```cpp

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Node
{
    ll cost;
    int id;
    bool biaoji;
    Node(){ biaoji=false; cost=0; }
};

int n,m,k,s;
int a[200010],b[200010];
int t[200010],c[200010];
int res[200010];
Node tmp[200010];

bool cmp(Node qwq,Node qaq){ return qwq.cost<qaq.cost; }

bool check(int x)
{
    int min_d=1e9,min_p=1e9;
    int day1=-1,day2=-1;
    for(int i=1;i<=x;i++)
    {
        if(min_d>a[i]) min_d=a[i],day1=i;
        if(min_p>b[i]) min_p=b[i],day2=i;
    }
    
    for(int i=1;i<=m;i++)
    {
        if(t[i]==1) tmp[i].cost=(ll)c[i]*min_d,tmp[i].biaoji=true;
        else tmp[i].cost=(ll)c[i]*min_p,tmp[i].biaoji=false;
        tmp[i].id=i;
    }
    sort(tmp+1,tmp+m+1,cmp);

    ll tot=0;
    for(int i=1;i<=k;i++) tot+=tmp[i].cost;

    if(tot<=s)
    {
        memset(res,0,sizeof(res));
        for(int i=1;i<=k;i++)
        {
            if(tmp[i].biaoji) res[tmp[i].id]=day1;
            else res[tmp[i].id]=day2;
        }
        return true;
    }

    return false;
}

void solve()
{
    scanf("%d%d%d%d",&n,&m,&k,&s);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=m;i++) scanf("%d%d",&t[i],&c[i]);
    
    int l=1,r=n;
    int ans=-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))
        {
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }

    if(ans==-1) puts("-1");
    else
    {
        printf("%d\n",ans);
        for(int i=1;i<=m;i++)
            if(res[i]) printf("%d %d\n",i,res[i]);
    }
}

int main()
{
    solve();
    return 0;
}

```



---

## 作者：xunhuanyihao (赞：7)

### CF609D    Gadgets for dollars and pounds
首先注意到如果可以在 $x$ 天前买完，那么肯定也可以在 $x+1$ 天前买完，即答案有单调性。

考虑二分答案，每次看在 $mid$ 天前买完，我们就选前 $mid$ 天美元 / 英镑最便宜的一天，将每个物品按那一天的汇率转化成卢布计算，再按价格从小到大排序，看看前 $k$ 个便宜的物品的价值和是否小于等于 $s$ 即可。

时间复杂度 $O(n \log^2 n)$。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
int n, m, k, a[N], b[N], op[N], c[N];
ll s;
pair<ll, pii> p[N];
bool check(int x, bool flag) {
    int dollar = 1 << 30, pound = 1 << 30, day1, day2;
    for (int i = 1; i <= x; i++) if (a[i] < dollar) dollar = a[i], day1 = i;
    for (int i = 1; i <= x; i++) if (b[i] < pound) pound = b[i], day2 = i;
    for (int i = 1; i <= m; i++) {
        if (op[i] == 1) p[i].first = 1ll * c[i] * dollar;
        else p[i].first = 1ll * c[i] * pound;
        p[i].second = {op[i], i};
    }
    sort(p + 1, p + m + 1);
    ll sum = 0;
    for (int i = 1; i <= k; i++) sum += p[i].first;
    if (flag == 1 && sum <= s) {
        printf("%d\n", x);
        for (int i = 1; i <= k; i++) {
            printf("%d %d\n", p[i].second.second, p[i].second.first == 1 ? day1 : day2);
        }
    }
    return sum <= s;
}
int main() {
    scanf("%d%d%d%lld", &n, &m, &k, &s);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= m; i++) scanf("%d%d", &op[i], &c[i]);
    int L = 0, R = n + 1;
    while (L + 1 < R) {
        int mid = (L + R) >> 1;
        if (check(mid, 0)) R = mid;
        else L = mid;
    }
    if (!check(n, 0)) {
        puts("-1");
        return 0;
    }
    check(R, 1);
    return 0;
}
```
但是，注意到我们这个 `check` 函数中有很多冗余操作，比如找最便宜的一天可以在外面前缀最小值预处理，排序其实也可以省去，我们先在外面分别将美金 / 英镑排序，然后类似归并排序，用一个双指针将两个有序数组合并成一个有序数组再累计其前 $k$ 个的和就行。

时间复杂度 $O(n \log n)$。

Code：
```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 1e6 + 10;
    typedef long long ll;
    typedef pair<int, int> pii;
    int n, m, k, a[N], b[N], op[N], c[N], t1, t2;
    ll s;
    pii c1[N], c2[N], d[N], p[N];
    bool check(int x) {
        ll sum = 0;
        for (int i = 1, j = 1; i + j < k + 2;) { //一共选了(i - 1 + j - 1)个, 故 i - 1 + j - 1 < k, 即 i + j < k + 2
            if (1ll * c1[i].first * d[x].first <= 1ll * c2[j].first * p[x].first) {
                sum += 1ll * c1[i].first * d[x].first;
                i++;
            } else sum += 1ll * c2[j].first * p[x].first, j++;
        }
        return sum <= s;
    }
    int main() {
        scanf("%d%d%d%lld", &n, &m, &k, &s);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &op[i], &c[i]);
            if (op[i] == 1) c1[++t1] = {c[i], i};
            else c2[++t2] = {c[i], i};
        }
        d[0] = p[0] = {1 << 30, -1};
        for (int i = 1; i <= n; i++) {
            d[i] = d[i - 1], p[i] = p[i - 1];
            if (a[i] < d[i].first) {
                d[i].first = a[i];
                d[i].second = i;
            }
            if (b[i] < p[i].first) {
                p[i].first = b[i];
                p[i].second = i;
            }
        }
        c1[t1 + 1] = c2[t2 + 1] = {1 << 30, -1};
        sort(c1 + 1, c1 + t1 + 1); sort(c2 + 1, c2 + t2 + 1);
        int L = 0, R = n + 1;
        while (L + 1 < R) {
            int mid = (L + R) >> 1;
            if (check(mid)) R = mid;
            else L = mid;
        }
        if (!check(n)) {
            puts("-1");
            return 0;
        }
        printf("%d\n", R);
        for (int i = 1, j = 1; i + j < k + 2;) {
            if (1ll * c1[i].first * d[R].first <= 1ll * c2[j].first * p[R].first) {
                printf("%d %d\n", c1[i].second, d[R].second);
                i++;
            } else printf("%d %d\n", c2[j].second, p[R].second), j++;
        }
        return 0;
    }
```

---

## 作者：Naganorhara_Yoimiya (赞：2)

# 题解：CF609D Gadgets for dollars and pounds

## 思路
校内模拟赛的题目，考场上这个蒟蒻写挂了。

一开始想到了堆，没打出来。

然后想到了二分答案。

既然二分答案，就需要使用贪心检验答案正确性。贪心策略十分显然：选出这段时间内**汇率最低的一天**，并**挑选最便宜的东西买**。

那么接下来就是如何记录，**考场上就是这个地方写挂了**。

我们只需要标记一下每个物品是否购买，然后记录时间即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Obj{
    ll cost = 0,id;
    bool biaoji = false;
    //考场上写挂了！
};
const int maxn = 1e5+10;
bool cmp(Obj a,Obj b){ return a.cost==b.cost?a.id<b.id:a.cost<b.cost; }
ll n,m,k,s,a[maxn],b[maxn],t[maxn],c[maxn],res[maxn];
Obj tmp[maxn];

bool check(int x){
    ll min1=1e11,min2=1e11;
  //分别记录美元和英镑最便宜的日子
    ll day1=-1,day2=-1,tot=0;
    for(ll i=1;i<=x;i++){
        min1>a[i]? min1=a[i],day1=i;
        min1>b[i]? min2=b[i],day2=i;
    }
    for(ll i=1;i<=m;i++){
        if(t[i]==1) tmp[i].cost=(ll)c[i]*min1,tmp[i].biaoji=true;
        else tmp[i].cost=(ll)c[i]*min2,tmp[i].biaoji=false;
        tmp[i].id=i;
    }
    sort(tmp+1,tmp+m+1,cmp);
    for(ll i=1;i<=k;i++) tot+=tmp[i].cost;
    //对于当前答案进行标记
    if(tot<=s){
        memset(res,0,sizeof(res));
        for(int i=1;i<=k;i++) tmp[i].biaoji? res[tmp[i].id]=day1 :res[tmp[i].id]=day2;
        return 1;
    }
    return 0;
}

int main(){
	//freopen("cf609d_6.in","r",stdin);
	//freopen("test,out","w",stdout);
    scanf("%lld%lld%lld%lld",&n,&m,&k,&s);
    for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(ll i=1;i<=n;i++) scanf("%lld",&b[i]);
    for(ll i=1;i<=m;i++) scanf("%lld%lld",&t[i],&c[i]);
    ll l=1,r=n,ans=-1;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(check(mid)) ans = mid,r = mid-1;
        else l = mid+1;
    }
    if(ans==-1) printf("-1\n");
    else{
        printf("%lld\n",ans);
        for(ll i=1,cnt=0;cnt<=k;i++)
          if(res[i]){
            printf("%lld %lld\n",i,res[i]);
            cnt++;
          } 
    }
    return 0;
}
```

---

## 作者：operator_ (赞：1)

# Gadgets for dollars and pounds

[题目传送门](https://www.luogu.com.cn/problem/CF609D)

## 题解

给一个单 $\log$ 题解。

“求最早完成买 $k$ 样东西的天数。”——很明显的二分答案。

在检验函数中，我们应当把前 $k$ 小的物品费用之和与总金额作比较，其它题解大多使用直接排序的方法，于是就多了一只 $\log$。其实没有必要，因为总共只有两种物品，我们使用类似归并排序的双指针法，这样只需要在二分的外层 $O(n\log n)$ 排序，二分内层 $O(n)$ 归并，总复杂度 $O(n\log n)$。

但是这题居然要输出方案，需要记录排序前的位置，实在多少有点恶心。

代码：

```cpp
/*
 * @Author: operator_ 
 * @Date: 2024-02-13 11:40:49 
 * @Last Modified by: operator_
 * @Last Modified time: 2024-02-13 12:12:14
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
int n,m,k,s,v[3][200005],p[3][200005],l[3];
struct QWQ{int v,id;} a[3][200005];
bool cmp(QWQ a1,QWQ a2) {return a1.v<a2.v;}
bool check(int mid) {
    int i=0,j=0,sum=0;
    while(i+j<k)
        if(a[1][i+1].v*v[1][mid]<a[2][j+1].v*v[2][mid])
            sum+=a[1][++i].v*v[1][mid];
        else sum+=a[2][++j].v*v[2][mid];
    return sum<=s;
}
signed main(){
    cin>>n>>m>>k>>s;
    v[1][0]=v[2][0]=INT_MAX;
    for(int i=1;i<=n;i++) {
        v[1][i]=rd();
        if(v[1][i-1]>v[1][i]) p[1][i]=i;
        else p[1][i]=p[1][i-1],v[1][i]=v[1][i-1];
    }
    for(int i=1;i<=n;i++) {
        v[2][i]=rd();
        if(v[2][i-1]>v[2][i]) p[2][i]=i;
        else p[2][i]=p[2][i-1],v[2][i]=v[2][i-1];
    }
    p[1][n+1]=p[2][n+1]=n+1;
    for(int i=1,t,d;i<=m;i++)
        t=rd(),d=rd(),a[t][++l[t]]={d,i};
    a[1][++l[1]].v=a[2][++l[2]].v=INT_MAX;
    sort(a[1]+1,a[1]+l[1]+1,cmp);sort(a[2]+1,a[2]+l[2]+1,cmp);
    int ll=1,rr=n+1,ans=0;
    while(ll<=rr) {
        int mid=(ll+rr)>>1;
        if(!check(mid)) ll=mid+1;
        else ans=mid,rr=mid-1;
    }
    if(ans==n+1) return puts("-1"),0;
    cout<<ans<<endl;
    int i=0,j=0;
    while(i+j<k)
        if(a[1][i+1].v*v[1][ans]<a[2][j+1].v*v[2][ans])
            printf("%lld %lld\n",a[1][++i].id,p[1][ans]);
        else printf("%lld %lld\n",a[2][++j].id,p[2][ans]);
    return 0;
}
```

其实感觉还有一种更快的 $O(A+n+\log^2n)$ 做法，但是我没有实现，感兴趣的可以试试（）

---

## 作者：AlicX (赞：1)

## Solution 

[Codeforces](https://codeforces.com/problemset/problem/609/D)

发现答案具有单调性：如果在第 $x$ 天可以买完 $k$ 件商品，那么以后的每一天都可以买完他们。所以考虑二分。

因为有三种货币不好计算，所以统一将他们变成卢比，然后有一个非常明显的贪心：每一次都买最便宜的，一定是最优的。所以对他们的价值排序。最后判断前 $k$ 个物品的价值是否可以买下就可以了。 

注意在转换货币的过程中开 `long long`。其余细节看代码。

```cpp
// Celestial Cyan 
// Luogu uid : 706523 
// Luogu : https://www.luogu.com.cn/problem/CF609D
// CF : https://www.luogu.com.cn/problem/CF609D
// AT : 
// FTOJ : 
// Contest : Educational Codeforces Round 3 
// Cnblogs : died
// Memory Limit: 256 MB
// Time Limit: 2000 ms 
// 2023/7/17     

#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
#define il inline 
#define db double
#define low(x) x&-x
#define ls(x) x<<1
#define rs(x) x<<1|1 
#define pb(x) push_back(x)
#define gcd(x,y) __gcd(x,y) 
#define lcm(x,y) x*y/gcd(x,y) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=2e6+10,INF=1e9+7;  
int n,m; 
int k,s; 
pii del[N]; 
pii res[N];
int a[N],b[N]; 
int t[N],c[N]; 
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il bool cmp(pii a,pii b){
	return a.x<b.x; 
}
il bool check(int mid){ 
	int Min1=INF,Min2=INF; int Day1=0,Day2=0; 
	for(int i=1;i<=mid;i++){ 
		if(a[i]<Min1) Min1=a[i],Day1=i; 
		if(b[i]<Min2) Min2=b[i],Day2=i; 
	} for(int i=1;i<=m;i++){ 
		if(t[i]&1) del[i].x=c[i]*Min1; 
		else del[i].x=c[i]*Min2; del[i].y=i; 
	} sort(del+1,del+m+1,cmp); int sum=0; 
	for(int i=1;i<=k;i++) sum+=del[i].x; 
	if(sum>s) return false; 
	for(int i=1;i<=k;i++){ 
		res[i].x=del[i].y; 
		if(t[res[i].x]&1) res[i].y=Day1; 
		else res[i].y=Day2; 
	} return true; 
} 
signed main(){ 
	n=read(),m=read(),k=read(),s=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read(); 
	for(int i=1;i<=m;i++) t[i]=read(),c[i]=read(); 
	int l=1,r=n,ans=0;  
	while(l<=r){ 
		int mid=l+r>>1; 
		if(check(mid)) r=mid-1,ans=mid; 
		else l=mid+1; 
	} if(ans==0){ 
		puts("-1"); 
		return 0; 
	} printf("%lld\n",ans); 
	for(int i=1;i<=k;i++) printf("%lld %lld\n",res[i].x,res[i].y); 
	return 0; 
} /* */ 
```

---

## 作者：Code_星云 (赞：1)

看到这题首先想到带 $\log$ 的算法，反悔贪心，二分等。但考虑到此题具有决策侧单调性，即若前一天能满足，则后一天也一定能满足，因此我们用二分答案。

此时 $\operatorname{chck}$ 函数比较容易，对于英镑和美元的物件，我们只需要预处理出前 $mid$ 天前缀美元或英镑的最小值，并在此天购买相应物件，然后排序求得前 $k$ 项即可。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
#define int long long

const int N = 200005;
int n, m, k, s, cnt = 0, a[N], b[N], m1[N], m2[N];
struct node{
	int op, val;
}p[N];
struct node2{
	int val, d, tp;
}bar[N];

bool cmp(node2 x, node2 y){
	return x.val < y.val;
}
bool cmp2(node2 x, node2 y){
	return x.d < y.d;
}
bool chck(int day, bool flag){
	cnt = 0;
	for(int i = 1; i <= m; i ++){
		if(p[i].op == 1) bar[++ cnt].val = p[i].val * m1[day];
		else bar[++ cnt].val = p[i].val * m2[day];
		bar[cnt].d = i;
		bar[cnt].tp = p[i].op;
	}
	sort(bar + 1, bar + cnt + 1, cmp);
	int sum = 0;
	for(int i = 1; i <= k; i ++) sum += bar[i].val;
	if(sum > s) return false;
	if(! flag) return true;
	int d1, d2;
	for(int i = 1; i <= day; i ++){
	    if(m1[day] == a[i]) d1 = i;
	    if(m2[day] == b[i]) d2 = i;
	}
	sort(bar + 1, bar + k + 1, cmp2);
	for(int i = 1; i <= k; i ++) 
	  printf("%lld %lld\n", bar[i].d, (bar[i].tp == 1) ? d1 : d2);
	return true;
}
signed main(){
	scanf("%lld %lld %lld %lld", &n, &m, &k, &s);
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i ++) scanf("%lld", &b[i]);
	m1[1] = a[1]; m2[1] = b[1];
	for(int i = 2; i <= n; i ++){
		m1[i] = min(m1[i - 1], a[i]);
		m2[i] = min(m2[i - 1], b[i]);
	}
	for(int i = 1; i <= m; i ++) scanf("%lld %lld", &p[i].op, &p[i].val);
	int l = 1, r = n;
	if(! chck(n, false)){
		puts("-1");
		return 0;
	}
	while(l < r){
		int mid = (l + r) >> 1;
		if(chck(mid, false)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);
	chck(l, true);
	return 0;
}
```


---

## 作者：Create_Random (赞：1)

[D. Gadgets for dollars and pounds](https://codeforces.ml/contest/609/problem/D)

~~VP的时候像傻了一样只往DP想~~

感谢同机房dalao @[He_Ren](https://www.luogu.com.cn/user/73687) @[TLE_Automat](https://www.luogu.com.cn/user/116060)提供的思路

解法：

考虑二分。

因为在前 $x$ 天中如果想让自身花费最少，必然需要在前 $x$ 天中汇率最小的一天进行兑换。

可以二分可能存在的天数 $x$，

然后贪心计算前 $x$ 天中美元和英镑的最小汇率，将其转化为相应需要花费的卢布。

随后找到前 $x$ 天中购买 $k$ 个最便宜物品花费的卢布数量，将其与现有的 $s$ 相比较，

如果可以买到即可将二分边界左移，否则右移即可。

时间复杂度 $O(m\log m\log n)$

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,s;
int a[200010],b[200010],num[200010];
long long v[200010];
struct node
{
	int num;
	long long v;
}cnt[200010],dollar,pound,ok[200010];
long long ans;
bool cmp(node a,node b)
{
	return a.v<b.v;
}
bool check(int x)
{
	long long res=0;
	memset(cnt,0,sizeof(cnt));
	dollar.v=1e9,pound.v=1e9;
	dollar.num=0,pound.num=0;
	for(int i=1;i<=x;i++)
	{
		if(dollar.v>a[i])
		{
			dollar.v=a[i];
			dollar.num=i;
		}
		if(pound.v>b[i])
		{
			pound.v=b[i];
			pound.num=i;
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(num[i]==1)
		{
			cnt[i].v=v[i]*dollar.v;
			cnt[i].num=i;
		}
		else
		{
			cnt[i].v=v[i]*pound.v;
			cnt[i].num=i;
		}
	}
	sort(cnt+1,cnt+m+1,cmp);
	for(int i=1;i<=k;i++)
	{
		res+=cnt[i].v;
	}
	if(res<=s)
	{
		for(int i=1;i<=k;i++)
		{
			ok[i].num=cnt[i].num;
			if(num[cnt[i].num]==1)
			{
				ok[i].v=dollar.num;
			}
			else
			{
				ok[i].v=pound.num;
			}
		}
		return 1;
	}
	return 0;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&s);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%lld",&num[i],&v[i]);
	}
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	if(!ans)
	{
		printf("-1");
		return 0;
	}
	printf("%d\n",ans);
	for(int i=1;i<=k;i++)
	{
		printf("%d %lld\n",ok[i].num,ok[i].v);
	}
	return 0;
}
```

---

## 作者：He_Ren (赞：1)

看到这道题其实思路还是很好想的，只是因为觉得题目冗长，比赛的时候就跳过了，实在可惜

答案有单调性，不难想到二分答案

**结合$2 \times 10^5$的数据范围就几乎可以确定是二分答案**

确定了天数，不难想到使用同一种货币的产品一定在那种货币汇率最小的那天购买

这点可以预处理得到

接下来确定使用每一种货币的产品购买多少

先排序，然后我使用的是类似尺取法（或许叫two pointers更为合适）的方法

先考虑第一种产品尽量多买（程序里是$i_1$尽可能大），然后逐渐减小$i_1$，同时尽可能让$i_2$变大，只要$i_1+i_2 \geq k$，就说明这是一种可行的方案

**在写程序时误把乘想成除，这种低级错误不应再犯**

**程序的变量名还是有点乱，这一点上应该多积累经验**

```cpp
#include<cstdio>
#include<algorithm>
typedef long long ll;
typedef long double db;
const int MAXN = 2e5 + 5;
const int MAXM = 2e5 + 5;
const int inf = 1e6;
const db eps = 1e-7;
using namespace std;

inline db Fabs(db x){ return x<0? -x: x;}
inline bool eq(db x,db y){ return Fabs(x-y)<=eps;}
inline bool leq(db x,db y){ return x<y || eq(x,y);}
inline int min(int a,int b){ return a<b? a: b;}
inline void chk_min(int &a,int b){ if(a>b) a=b;}

int a[MAXN],b[MAXN];
int mda[MAXN],mdb[MAXN];
struct Node
{
	int id,c;
}c1[MAXM],c2[MAXM];
ll s1[MAXM],s2[MAXM];
int cnt1=0,cnt2=0;
inline bool cmp(const Node x,const Node y){ return x.c<y.c;}

int p,s;
int i1,i2;
inline bool check(int d)
{
	int ma=a[mda[d]], mb=b[mdb[d]];
	
	i1=0,i2=0;
	for(i1=1; i1<=cnt1 && s1[i1]*ma<=s; ++i1);
	--i1;
	
	for(; i1>=0; --i1)
	{
		for(; i2<=cnt2 && s1[i1]*ma + s2[i2]*mb <=  s; ++i2);
		--i2;
		if(i1+i2>=p) return 1;
	}
	return 0;
}

int main(void)
{
	int n,m;
	scanf("%d%d%d%d",&n,&m,&p,&s);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&b[i]);
	
	for(int i=1; i<=m; ++i)
	{
		int t,x;
		scanf("%d%d",&t,&x);
		if(t==1)
			c1[++cnt1] = (Node){i,x};
		else
			c2[++cnt2] = (Node){i,x};
	}
	sort(c1+1, c1+cnt1+1, cmp);
	sort(c2+1, c2+cnt2+1, cmp);
	for(int i=1; i<=cnt1; ++i) s1[i] = s1[i-1] + c1[i].c;
	for(int i=1; i<=cnt2; ++i) s2[i] = s2[i-1] + c2[i].c;
	
	a[0]=b[0]=inf;
	for(int i=1; i<=n; ++i)
	{
		if(a[i]<a[mda[i-1]]) mda[i]=i;
		else mda[i] = mda[i-1];
		
		if(b[i]<b[mdb[i-1]]) mdb[i]=i;
		else mdb[i] = mdb[i-1];
	}
	
	int l=1, r=n+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	
	if(l==n+1)
	{
		printf("-1");
		return 0;
	}
	
	check(l);
	printf("%d\n",l);
	for(int i=1; i<=i1 && i<=p; ++i) printf("%d %d\n",c1[i].id, mda[l]);
	for(int i=1; i1+i<=p; ++i) printf("%d %d\n",c2[i].id, mdb[l]);
	return 0;
}
```


---

## 作者：Hoks (赞：0)

## 前言
水题，但是我为什么要折磨自己去写单 log 做法。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
显然的是，假设我们 $x$ 天做到买 $k$ 件物品，肯定是在换美元/英镑代价最小的那天买。

对于我们买的物品，肯定也是买要美元最少的或者是要英镑最少的物品。

这个单调性就很显然了，所以我们考虑二分出天数 $x$ 去 check。

check 也非常简单，用 ST 表 $O(1)$ 找出前 $x$ 天美元/英镑最小代价，然后暴力枚举买了 $i$ 件要美元支付的和 $k-i$ 件要用英镑支付的。

计算这个代价考虑先排序然后前缀和直接算就行了。

如果找到了任意一个可行的，就存下答案为 $x$ 天，买了 $i$ 件要美元支付的物品。

无解即当答案天数还为初始值时。

最后的输出也比较简单，因为我们存下了 $x$ 天，买了 $i$ 件要美元支付的物品，所以直接找出前 $x$ 天到底哪天美元/英镑代价最小。

然后枚举买的 $i$ 件美元支付的物品都在美元代价最小那天买，英镑物品同理即可。
## 代码
非常好写，一遍就过了。

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,M=3,INF=0x3f3f3f3f,mod=1e9+7;
int n,m,k,s,b[N],c[N],ss[M][N];vector<pair<int,int>>a[M];pair<int,int>ans;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='?'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
struct ST
{
    int st[20][N];
    void get_ST(int a[])
    {
        for(int i=1;i<=n;i++) st[0][i]=a[i];
        for(int j=1;j<=19;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    int get(int l,int r){int k=log2(r-l+1);return min(st[k][l],st[k][r-(1<<k)+1]);}
}st[2];
inline bool check(int x)
{
    int mn1=st[0].get(1,x),mn2=st[1].get(1,x);
    for(int i=0;i<=k;i++)
    {
        int res=mn1*ss[1][i]+mn2*ss[2][k-i];
        if(res<=s) return ans=min(ans,{x,i}),1;
    }return 0;
}
inline void solve()
{
    n=read(),m=read(),k=read(),s=read();ans={INF,INF};
    for(int i=1;i<=n;i++) b[i]=read();st[0].get_ST(b);
    for(int i=1;i<=n;i++) c[i]=read();st[1].get_ST(c);
    for(int i=1,op;i<=m;i++) op=read(),a[op].emplace_back(read(),i);
    sort(a[1].begin(),a[1].end());sort(a[2].begin(),a[2].end());
    for(int i=1;i<=k;i++) ss[1][i]=ss[2][i]=INF;
    for(int i=0;i<a[1].size();i++) ss[1][i+1]=ss[1][i]+a[1][i].first;
    for(int i=0;i<a[2].size();i++) ss[2][i+1]=ss[2][i]+a[2][i].first;
    int l=1,r=n;while(l<=r) if(check(mid)) r=mid-1;else l=mid+1;
    int k1=1,k2=1,mn1=INF,mn2=INF;if(ans.first==INF) return put("-1\n");
    for(int i=1;i<=ans.first;i++)
    {
        if(mn1>b[i]) k1=i,mn1=b[i];
        if(mn2>c[i]) k2=i,mn2=c[i];
    }print(ans.first),put('\n');
    for(int i=0;i<ans.second;i++) print(a[1][i].second),put(' '),print(k1),put('\n');
    for(int i=0;i<k-ans.second;i++) print(a[2][i].second),put(' '),print(k2),put('\n');
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：wangzikang (赞：0)

个人建议降绿，感觉没那么难想，greedy 也很显然。

---

考虑二分答案。

显然的，该问题满足单调性，可以二分答案。

`check` 怎么写？

我们贪心的求出美元和英镑的最低价，然后直接算最低价买这些商品的价格，把他们 sort 一下，取前 $k$ 项的和，假如这个和大于 $s$，check 返回 0，否则返回 1。

当 $check(n)=0$ 时，无解。

方案很好构造，详情自己看代码：

```cpp
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
int n,m,k,s,p[200005],d[200005],w[500001];
bitset<200005>b;
vector<pair<int,int> >q;
int check(int a,int P=0){
    int m1=0x7f7f7f7f,m2=0x7f7f7f7f,z,x;
    for(int i=1;i<=a;++i){
        if(m1>p[i])m1=p[i],z=i;
        if(m2>d[i])m2=d[i],x=i;
    }
    for(int i=1;i<=m;++i){
    	q.push_back(make_pair(w[i]*(b[i]?m2:m1),i)); 
	} 
	sort(q.begin(),q.end());
	int tmp=s;
	for(int i=1;i<=k;++i){
		tmp-=q[i-1].first;
		if(P)cout<<q[i-1].second<<' '<<(b[q[i-1].second]?x:z)<<'\n';
	}
    q.resize(0);
    return(tmp>=0);
    cout<<"I Love CCF";
}
int main(){
	cin>>n>>m>>k>>s;
	for(int i=1;i<=n;++i){
		cin>>p[i]; 
	} 
	for(int i=1;i<=n;++i){
		cin>>d[i]; 
	} 
	for(int i=1;i<=m;++i){
		int c;
		cin>>c>>w[i]; 
		b[i]=c-1;
	} 
	int l=1,r=n,mid;
//	cout<<check(3);
	if(!check(n)){
		cout<<"-1";
		return 0;
	}
	while(l<=r){
//		cout<<l<<' '<<r<<'\n';
		mid=(l+r)>>1;
		if(check(mid)){
			r=mid;
			if(!check(mid-1)){
				cout<<mid<<'\n';
				check(mid,1);
				return 0;
			}
		}else{
			l=mid+1; 
		}
	}
	cout<<mid<<'\n';
	check(mid);
	return 0;
}
```


---

## 作者：ncwzdlsd (赞：0)

观察到如果第 $x$ 天可以买完 $k$ 件物品，第 $x+1$ 天也可以，此问题具有决策单调性。

考虑二分最少需要的天数 $x$。对于当前二分到的天数，找到当前的最小汇率，计算最少需要的花费钱数，与 $s$ 进行比较判断是否可行即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long

const int maxn=2e5+5;
int a[maxn],b[maxn],s,m,n,k;
struct node{int t/*type*/,c/*cost*/,id;ll v;}p[maxn];
struct nod{int d,q;}out[maxn];

bool cmp(node a,node b){return a.v<b.v;}

bool check(int x)
{
	int mina=INT_MAX,minb=INT_MAX,d1=1,d2=1;
	for(int i=1;i<=x;i++)
	{
		if(a[i]<mina) mina=a[i],d1=i;
		if(b[i]<minb) minb=b[i],d2=i;
	}
	for(int i=1;i<=m;i++) 
	{
		if(p[i].t==1) p[i].v=p[i].c*mina;
		else p[i].v=p[i].c*minb;
	}
	sort(p+1,p+m+1,cmp);
	ll sum=0;
	for(int i=1;i<=k;i++) sum+=p[i].v;
	if(sum>s) return 0;
	for(int i=1;i<=k;i++)
	{
		out[i].q=p[i].id;
		if(p[i].t==1) out[i].d=d1;
		else out[i].d=d2;
	}
	return 1;
}

signed main()
{
	cin>>n>>m>>k>>s;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=m;i++) cin>>p[i].t>>p[i].c,p[i].id=i;
	int l=0,r=n,ans=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	if(ans) 
	{
		cout<<ans<<'\n';
		for(int i=1;i<=k;i++) cout<<out[i].q<<' '<<out[i].d<<'\n';
	}
	else cout<<"-1";
	return 0;
}
```

---

## 作者：Deamer (赞：0)

## 前言：

这是本人在板刷 CF 时一眼秒了并很快写对的一道蓝，故写一篇题解纪念一下。

## 分析：

我们注意到第 $x$ 天能买到 $k$ 件商品，那么第 $x$ 天之后也都能买到，既然满足决策单调性，我们理所当然的先考虑二分。

我们已经把问题转化为了判断前 $x$ 天能否买到 $k$ 件商品，我们贪心的考虑，对于只能用美元购买的商品，我们肯定是在前 $x$ 天兑换美元代价最少的那一天兑换美元再进行购买，英镑同理。那么我们维护出前 $x$ 天兑换美元和英镑代价最少的那一天，就可以算出前 $x$ 天买每一件商品的最少代价，其中代价最少的 $k$ 件商品的代价之和，就是前 $x$ 天买到 $k$ 件商品的最少代价，从而完成判断。

说几个需要注意的点吧：

- 记得开 ```long long ```。

- 输出时先输出商品编号，再输出购买日期的编号。

~~readers : Talking is cheap , show me the code !!!~~ 

##  _Code:_ 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int N=2e5+10;
const int INF=0x7f7f7f7f;
int n,m,k,s;
int a[N],b[N];
struct node { int id,op; ll cost; } c[N],d[N];
struct Node { int x,y; } mina[N],minb[N];
struct Ans { int  id,day; } ans[N];

bool cmp(node a,node b) { return  a.cost<b.cost; }

bool chck(int mid){
	for(int i=1;i<=m;i++){
		d[i].id=i;
		d[i].op=c[i].op;
		if(c[i].op==1) d[i].cost=mina[mid].x*c[i].cost;
		else d[i].cost=minb[mid].x*c[i].cost;
	}
	sort(d+1,d+m+1,cmp);
	ll sum=0;
	for(int i=1;i<=k;i++){
		sum+=d[i].cost;
		if(sum>s) return false;
	}
	for(int i=1;i<=k;i++){
		ans[i].id=d[i].id;
		if(d[i].op==1) ans[i].day=mina[mid].y;
		else ans[i].day=minb[mid].y;
	}
	return true;
}

int main(){
	scanf("%d%d%d%d",&n,&m,&k,&s);
	mina[0].x=minb[0].x=INF;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]<mina[i-1].x){
			mina[i].x=a[i];
			mina[i].y=i;
		}
		else mina[i]=mina[i-1];
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		if(b[i]<minb[i-1].x){
			minb[i].x=b[i];
			minb[i].y=i;
		}
		else minb[i]=minb[i-1];
	}
	for(int i=1;i<=m;i++) scanf("%d%lld",&c[i].op,&c[i].cost);
	int l=1,r=n;
	while(l<=r){
		int mid=(l+r)>>1;
		if(chck(mid)) r=mid-1;
		else l=mid+1;
	}
	if(l>n){
		printf("-1\n");
		return 0;
	}
	printf("%d\n",l);
	for(int i=1;i<=k;i++) printf("%d %d\n",ans[i].id,ans[i].day);
	return 0;
}
```

[完结撒花！！！](https://www.luogu.com.cn/record/121892648)


---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$
---
### 解题思路：

平凡的二分。

如果在某一天之前能够达成要求，在这一天之后的任意一天都一定可以达成要求，所以先对于天数进行一个二分。

然后问题就转化为了在前若干天中是否能够买到 $k$ 件物品。可以发现，对于某一种货币可以购买的东西，一定是从价格比较便宜的开始买，这样就可以直接枚举某一种货币购买的物品数量，从而算出另一种货币购买的物品数量和需要的两种货币数量。

然后考虑货币的转化，发现一定是在换取率最高的一天将所有的货币换过去最划算，直接前缀取最小值就可以了。

总复杂度 $O(k\log n)$。

----
### 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=200005;
struct str{
	int id,cost;
	bool operator < (str a){
		return cost<a.cost;
	}
}c1[MAXN],c2[MAXN];
int n,m,k,s,a[MAXN],b[MAXN],pa[MAXN],pb[MAXN],opt,cnt1,cnt2,mid,ans,res,l,r;
bool check(int num){
	int ma=a[pa[num]],mb=b[pb[num]];
	for(int i=0;i<=k;i++)
	if(ma*c1[i].cost+mb*c2[k-i].cost<=s&&i<=cnt1&&(k-i)<=cnt2){
		res=i;
		return 1;
	}
	return 0;
}
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&k,&s);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
	for(int i=1;i<=m;i++){
		scanf("%lld",&opt);
		if(opt==1)scanf("%lld",&c1[++cnt1].cost),c1[cnt1].id=i;
		else scanf("%lld",&c2[++cnt2].cost),c2[cnt2].id=i;
	}
	sort(c1+1,c1+cnt1+1);
	sort(c2+1,c2+cnt2+1);
	for(int i=1;i<=cnt1;i++)c1[i].cost+=c1[i-1].cost;
	for(int i=1;i<=cnt2;i++)c2[i].cost+=c2[i-1].cost;
	pa[1]=pb[1]=1;
	for(int i=2;i<=n;i++){
		if(a[pa[i-1]]>a[i])pa[i]=i;
		else pa[i]=pa[i-1];
		if(b[pb[i-1]]>b[i])pb[i]=i;
		else pb[i]=pb[i-1];
	}
	l=1;r=n;ans=-1;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	if(ans==-1)return 0;
	for(int i=1;i<=res;i++)printf("%lld %lld\n",c1[i].id,pa[ans]);
	for(int i=1;i<=k-res;i++)printf("%lld %lld\n",c2[i].id,pb[ans]);
	return 0;
} 
```


---

## 作者：hxhhxh (赞：0)

## 大意

`Nura`手中有 $ s $ 块某货币，他想买 $ m $ 样东西里的 $ k $ 样东西。每一天都有两个参数 $ a_i $ 和 $ b_i $ ； $ k $ 样东西也有两个参数 $ t_j $ 和 $ c_j $ ，表示在第 $ i $ 天，`Nura`卖第 $ j $ 个东西需要花费

$$
c_j \times
\begin{cases}
a_i & (t_i = 1) \\
b_i & (t_i = 2)
\end{cases}
$$

块某种货币。

求`Nura`最少要几天可以达成愿望，或者说不可能。

## 思路

首先答案具有可二分性，我们可以先二分答案。

让后问题就落到了如何写`check`函数。

首先在前 $ mid $ 天里选出一天来集中卖 $ t = 1 $ 的东西。显然，选出 $ a_i $ 最小的一天来集中购买这种东西是最优的， $ t = 2 $ 同理。另外，同种东西肯定选尽量便宜的。

然后枚举一下选几个 $ t=1 $ 的东西和几个 $ t=2 $ 的东西，一旦成功直接 `return true`。

最后记得记一下答案，无解不要忘了输出，**计算价格时记得开**`long long`。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,s,a[200005],b[200005],am,bm;
struct st{
	int id,x;
}ca[200005],cb[200005];
vector<pair<int,int> >ans;
bool doing(int x){
	int ad=x,bd=x,sum=0;
	for(int i=1;i<x;i++){
		if(a[i]<a[ad]) ad=i;
		if(b[i]<b[bd]) bd=i; 
	}
	for(int i=1;i<=k;i++) sum+=ca[i].x*a[ad];
	for(int i=0;i<k;i++){
		if(sum<=s){
			ans.clear();
			for(int j=1;j<=k-i;j++) ans.push_back(make_pair(ca[j].id,ad));
			for(int j=1;j<=i;j++) ans.push_back(make_pair(cb[j].id,bd));
			return true; 
		}
		sum+=cb[i+1].x*b[bd];
		sum-=ca[k-i].x*a[ad];
	}
	if(sum<=s){
		ans.clear();
		for(int j=1;j<=k;j++) ans.push_back(make_pair(cb[j].id,bd));
		return true; 
	}
	return false;
}
bool cmp(st a,st b){
	return a.x<b.x;
}
signed main(){
	cin>>n>>m>>k>>s;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	for(int i=1,j,k;i<=m;i++){
		scanf("%lld %lld",&j,&k);
		if(j==1) ca[++am]=(st){i,k};
		else cb[++bm]=(st){i,k};
	}
	sort(ca+1,ca+am+1,cmp);
	sort(cb+1,cb+bm+1,cmp);
	for(int i=am+1;i<=k;i++) ca[i].x=1000000000;
	for(int i=bm+1;i<=k;i++) cb[i].x=1000000000;
	if(!doing(n)) printf("-1");
	else{
		int l=1,r=n,mid;
		while(l<r){
			mid=l+r>>1;
			if(doing(mid)) r=mid;
			else l=mid+1;
		}
		printf("%lld\n",r);
		for(int i=0;i<k;i++) printf("%lld %lld\n",ans[i].first,ans[i].second);
	}
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

学校二分题单中的又一道贪心 `check()` 题目。

# 正文

想法：这么大的 $N, M$ 肯定要二分。

验证一下决策单调：第 $x_0$ 天能买到 $K$ 件东西，那么第 $x > x_0$ 天肯定也能买到 $K$ 件东西。

然后考虑 `check()` 怎么写。

由于一天可以买不限数量的物品，于是可以考虑先把前 $mid$ 天的最小美元、英镑汇率搞出来，然后把每个要买的物品的具体价格算出来。

最后排个序，取前 $K$ 个的物品的价格之和，判断一下是否大于 $S$ 即可。

正确性：

显然是个贪心，考虑：用美元支付的就在前 $mid$ 天的美元汇率最小日时全买了，用英镑支付的就在前 $mid$ 天的英镑汇率最小日时全买了，这样一定耗钱最小。

~~（毕竟也没有像“每天发工资”的东西。）~~

复杂度 $\mathcal{O}(M \log_2 M \log_2 N)$, 显然能过。

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

int N, M, K, S;
int dollar[200005], pound[200005];
int t[200005], c[200005];

struct Element {
	int pos = 0;
	long long rate;
} tmp[200005];

struct Gadget{
	int number = 0, pos = 0;
	long long cost;
} res[200005], ans[200005];

bool operator <(Element __a, Element __b)
{
	return __a.rate < __b.rate;
}

bool operator <(Gadget __a, Gadget __b)
{
	return __a.cost < __b.cost;
}

bool check(int mid)
{
	long long sum = 0ll;
	Element mind, minp;
	memset(tmp, 0, sizeof(tmp));
	memset(res, 0, sizeof(res));
	mind.rate = 1e15;
	minp.rate = 1e15;
	for(int i = 1; i <= mid; ++ i)
	{
		if(mind.rate > dollar[i])
		{
			mind.rate = dollar[i];
			mind.pos = i;
		}
		if(minp.rate > pound[i])
		{
			minp.rate = pound[i];
			minp.pos = i;
		}
	}
	
	for(int i = 1; i <= M; ++ i)
	{
		if(t[i] == 1)
		{
			res[i].cost = c[i] * mind.rate;
			res[i].number = i;
			res[i].pos = mind.pos;
		}
		if(t[i] == 2)
		{
			res[i].cost = c[i] * minp.rate;
			res[i].number = i;
			res[i].pos = minp.pos;
		}
	}
	
	sort(res + 1, res + M + 1);
	for(int i = 1; i <= K; ++ i)
		sum += res[i].cost;
		
	if(sum > S)
		return false;
	else
		return true;
}

int main()
{
	cin >> N >> M >> K >> S;
	for(int i = 1; i <= N; ++ i)
		cin >> dollar[i];
		
	for(int i = 1; i <= N; ++ i)
		cin >> pound[i];
		
	for(int i = 1; i <= M; ++ i)
		cin >> t[i] >> c[i];
		
	int l, r, dhfksdhf = 0;
	l = 1, r = N;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			dhfksdhf = mid;
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	
	if(dhfksdhf == 0)
		puts("-1");
	else
	{
		cout << dhfksdhf << endl;
		Element mind, minp;
		memset(tmp, 0, sizeof(tmp));
		memset(res, 0, sizeof(res));
		mind.rate = 1e15;
		minp.rate = 1e15;
		for(int i = 1; i <= dhfksdhf; ++ i)
		{
			if(mind.rate > dollar[i])
			{
				mind.rate = dollar[i];
				mind.pos = i;
			}
			if(minp.rate > pound[i])
			{
				minp.rate = pound[i];
				minp.pos = i;
			}
		}
		
		for(int i = 1; i <= M; ++ i)
		{
			if(t[i] == 1)
			{
				res[i].cost = c[i] * mind.rate;
				res[i].number = i;
				res[i].pos = mind.pos;
			}
			if(t[i] == 2)
			{
				res[i].cost = c[i] * minp.rate;
				res[i].number = i;
				res[i].pos = minp.pos;
			}
		}
		
		sort(res + 1, res + M + 1);
		for(int i = 1; i <= K; ++ i)
		{
			cout << res[i].number << ' ' << res[i].pos << endl;
		}
	}
	return 0;
}
```

# 后言

代码有点长，请勿喷。

---

