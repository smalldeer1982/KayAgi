# Greetings

## 题目描述

There are $ n $ people on the number line; the $ i $ -th person is at point $ a_i $ and wants to go to point $ b_i $ . For each person, $ a_i < b_i $ , and the starting and ending points of all people are distinct. (That is, all of the $ 2n $ numbers $ a_1, a_2, \dots, a_n, b_1, b_2, \dots, b_n $ are distinct.)

All the people will start moving simultaneously at a speed of $ 1 $ unit per second until they reach their final point $ b_i $ . When two people meet at the same point, they will greet each other once. How many greetings will there be?

Note that a person can still greet other people even if they have reached their final point.

## 说明/提示

In the first test case, the two people will meet at point $ 3 $ and greet each other.

## 样例 #1

### 输入

```
5
2
2 3
1 4
6
2 6
3 9
4 5
1 8
7 10
-2 100
4
-10 10
-5 5
-12 12
-13 13
5
-4 9
-2 5
3 4
6 7
8 10
4
1 2
3 4
5 6
7 8```

### 输出

```
1
9
6
4
0```

# 题解

## 作者：foryou_ (赞：13)

容易发现每个人在行进过程中不会追上其他任何一个人，

因此一对人 $i,j$ 会问候当且仅当 $b_i>b_j$，这时 $i$ 会在 $b_j$ 处问候 $j$。

于是我们考虑对所有人 $i$ 按 $a_i$ 排序，

根据上述推论，便可得 $b_i$ 的逆序对数总和即为答案。

然后这题就成逆序对板子了。

---

## 作者：ThySecret (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1915F)

### 前置知识：排序 + 逆序对

## 题目大意

数线上有 $n$ 个人，第 $i$ 个人在点 $a \times i$，想去点 $b \times i$。对于每个人来说，$a \times i \lt b \times i$ 以及所有人的起点和终点都是不同的（也就是说，所有的 $2n$ 数 $a \times 1, a \times 2, \dots, a \times n, b \times 1, b \times 2, \dots, b \times n$ 都是不同的）。

所有的人将以每秒 $1$ 个单位的速度同时开始移动，直到到达终点 $b_i$。当两个人在同一点相遇时，他们会互相问候一次。会有多少次打招呼？

请注意，即使一个人到达了最终点，他仍然可以向其他人打招呼。

## 解题思路

[![piXS0MR.png](https://s11.ax1x.com/2023/12/31/piXS0MR.png)](https://imgse.com/i/piXS0MR)

画图后可以看出，由于 $a \times i \lt b \times i$，所有人都在去往右边走，并且速度相同，此时相遇有两种可能：

- $l_i < l_j$ 并且 $r_i > r_j$
- $l_i > l_j$ 并且 $r_i < r_j$

我们只需要稍加排序，就可以转化为一种思路：

> 将所有人的初始点从小到大进行排序，求出他们的终点的逆序对之和。

这不就是逆序对么？把样例丢尽逆序对模板，十分正确的。

接下来就可以愉快的写代码了。

## AC Code

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
#define int long long

int a[N], c[N], ans;
struct Node
{
    int l, r;
    bool operator<(const Node &u) const
    {
        return l < u.l;
    }
}tmp[N];

void mergesort(int bg, int ed)
{
    if (bg == ed)
        return;
    int mid = (bg + ed) / 2, i = bg, j = mid + 1, k = bg;
    mergesort(bg, mid), mergesort(mid + 1, ed);
    while (i <= mid && j <= ed)
    {
        if (a[i] <= a[j])
            c[k++] = a[i++];
        else
            c[k++] = a[j++], ans += mid - i + 1;
    }
    while (i <= mid)
        c[k++] = a[i++];
    while (j <= ed)
        c[k++] = a[j++];
    for (int l = bg; l <= ed; l++)
        a[l] = c[l];
}

void solve()
{
	int n; cin >> n;
	for (int i = 1; i <= n; i ++) cin >> tmp[i].l >> tmp[i].r;
	sort(tmp + 1, tmp + 1 + n);
	
	for (int i = 1; i <= n; i ++) 
		a[i] = tmp[i].r;
	ans = 0;
	mergesort(1, n);
	cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
```

赛事代码当时想复杂了，不过也可以过。大抵是目前题解里最简单的一篇罢。

---

## 作者：wxzzzz (赞：4)

### 题意

给定 $n$ 个区间 $[a_i,b_i]$，求有多少个区间对 $x,y$，满足 $a_x\le a_y\le b_y\le b_x$。

### 思路

根据题意，答案表示为：

$$\sum_{i=1}^{n-1}\sum_{j=i+1}^n [a_j\le a_i,b_j\ge b_i]$$

按区间左端点大小对所有区间排序，答案可转化为：

$$\sum_{i=1}^n \sum_{j=1}^{i-1}[b_j\ge b_i]$$

即：

$$\sum_{i=1}^n\Big(i-\sum_{j=1}^{i-1}[b_j<b_i]\Big)$$

其中 $i-\displaystyle\sum_{j=1}^{i-1}[b_j<b_i]$ 可用树状数组维护。

注意 $a_i,b_i\in[-10^9,10^9]$，要离散化。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, nv, tp[1000005 << 1];
long long ans, c[1000005];
pair<int, int> p[1000005];
map<int, bool> flag;
void add(int x, int k) {
    while (x <= nv) {
        c[x] += k;
        x += (x & -x);
    }
}
int query(int x) {
    int ret = 0;

    while (x) {
        ret += c[x];
        x -= (x & -x);
    }

    return ret;
}
int main() {
    cin >> t;

    while (t--) {
        for (int i = 0; i <= n * 2; i++)
            c[i] = 0;

        cin >> n;
        ans = nv = 0, flag.clear();

        for (int i = 1; i <= n; i++) {
            cin >> p[i].first >> p[i].second;

            if (!flag[p[i].first]) {
                tp[++nv] = p[i].first;
                flag[p[i].first] = 1;
            }

            if (!flag[p[i].second]) {
                tp[++nv] = p[i].second;
                flag[p[i].second] = 1;
            }
        }

        sort(tp + 1, tp + nv + 1);
        nv = unique(tp + 1, tp + nv + 1) - tp - 1;

        for (int i = 1; i <= n; i++) {
            p[i].first = lower_bound(tp + 1, tp + nv + 1, p[i].first) - tp;
            p[i].second = lower_bound(tp + 1, tp + nv + 1, p[i].second) - tp;
        }

        sort(p + 1, p + n + 1);

        for (int i = 1; i <= n; i++) {
            ans += i - query(p[i].second - 1) - 1;
            add(p[i].second, 1);
        }

        cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：DrAlfred (赞：1)

摘要：二维偏序，数据结构

[传送门：https://www.luogu.com.cn/problem/CF1915F](https://www.luogu.com.cn/problem/CF1915F)

## 题意

数轴上有 $n$ 个人。他们一开始在 $a_i$，然后以每秒 $1$ 个单位长度的时间向他们的终点 $b_i$ 移动（保证有 $ a_i < b_i $）。

如果某个时刻两个人在同一个位置，他们就会打招呼（注意，到了终点也可以和别人打招呼）。求最终打招呼发生了几次。

## 分析思路

如果一个人 $ i $ 最终会在他的运动过程中遇到 $ j $，则一定是 $a_i < a_j$，然后等到 $ j $ 到达其终点 $b_j$ 之后，$ i $ 仍在运动，并且他的终点 $b_i > b_j$。

简而言之，我们就是要求这样的点对 $(i, j)$，使得 $a_i < a_j < b_j < b_i$。考虑先将每个人按照起始位置从小到大排序，则只需要统计在第 $ i $ 个数后面且终点比 $ i $ 小的 $ j $ 的个数即可。

由于需要动态插入，动态统计比一个数小的数的个数，可以考虑树状数组。由于位置的值域太大，考虑使用离散化。注意离散化之后可能有 $2n$ 个不同的数，树状数组要开两倍空间（比赛的时候就挂这里了 QAQ ）。

## 代码

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;
const int N = 200010;
int t, n, a[N], b[N], c[2 * N]; // c 开 2 * n !!!
template <class _Tp>
struct Mess {
    vector<_Tp> v;
    inline void insert(_Tp x) { v.push_back(x); }
    inline void init(void) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    inline int query(_Tp x) {
        return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
    }
};  // 离散化模板
struct Node {
    int a, b;
    inline bool operator<(const Node &x) const { 
        return a < x.a; 
    }
} d[N];
inline void add(int x) {
    for (; x < 2 * N; x += lowbit(x)) c[x]++;
}
inline int query(int x) {
    int ans = 0;
    for (; x; x ^= lowbit(x)) ans += c[x];
    return ans;
}
inline void solve(void) {
    cin >> n;
    Mess<int> M;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i], M.insert(a[i]), M.insert(b[i]);
    }
    M.init(); // 离散化初始化，树状数组清空
    for (size_t i = 1; i <= M.v.size(); i++) c[i] = 0;
    for (int i = 1; i <= n; i++) {
        d[i] = {M.query(a[i]), M.query(b[i])};
    }
    long long ans = 0;
    sort(d + 1, d + 1 + n);
    for (int i = n; i >= 1; i--) {
        ans += query(d[i].b), add(d[i].b);
    }
    cout << ans << endl;
}
int main(int argc, char const *argv[]) {
    cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：AlicX (赞：1)

## Solution 

不难想到与第 $i$ 个人相遇的人肯定在 $i$ 的左侧，与考虑将 $n$ 个人以 $a_i$ 作为关键字排序。那么与第 $i$ 个人相遇的人数即为 $\sum \limits_{j=1} ^{i-1} [b_j > b_i]$，离散化后用树状数组维护即可。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=4e5+10; 
int n; 
pii a[N];  
int b[N]; int tr[N]; 
int low(int x){
	return x&-x; 
} 
void add(int x){ 
	for(int i=x;i>=1;i-=low(i)) tr[i]++; 
} 
int query(int x){ 
	int res=0; 
	for(int i=x;i<=2*n;i+=low(i)) res+=tr[i]; 
	return res; 
} 
void work(){ 
	cin>>n; int num=0; 
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y,b[++num]=a[i].y,b[++num]=a[i].x; 
	sort(b+1,b+num+1);  
	for(int i=1;i<=n;i++) a[i].y=lower_bound(b+1,b+num+1,a[i].y)-b,a[i].x=lower_bound(b+1,b+num+1,a[i].x)-b; 
	sort(a+1,a+n+1); int cnt=0; 
	for(int i=1;i<=n;i++){ 
		cnt+=query(a[i].y); 
		add(a[i].y); 
	} cout<<cnt<<endl; 
	for(int i=1;i<=2*n;i++) tr[i]=0;
} 
signed main(){ 
	int T; scanf("%lld",&T); 
	while(T--) work(); return 0; 
} 

```


---

## 作者：Natori (赞：1)

>[CF1915F Greetings](https://www.luogu.com.cn/problem/CF1915F)

你说得对，但是二维偏序板题。

------------
我们考虑两个人会相遇的充要条件。由于所有人速度是一样的，所以还没到终点的两个人是不可能相遇的，所以只可能是一个人走到另一个人的终点处。因此会相遇的充要条件是一个人的区间包含另一个人的。

形式化地，我们需要统计有序点对 $(i,j)$ 的个数，满足：$a_i<a_j,b_i>b_j$。裸的二维偏序了吧。

先将 $b$ 取相反数转化成 $b_i<b_j$，然后和 $a$ 一起离散化。按 $a$ 排序之后就相当于求顺序对了。时间复杂度 $\mathcal{O}(n \log n)$。

注意树状数组要开两倍空间，因为离散化后值域是 $2n$。~~笔者因为这个交了三发罚时，糖丸了属于是~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
const int N=5e5+8,oo=1e12;
int n,a[N],b[N],lsh[N],lshcnt;
struct Element{
	int a,b;
	void clear(){
		a=b=0;
	}
	friend bool operator <(Element x,Element y){
		if(x.a!=y.a)
			return x.a<y.a;
		return x.b<y.b;
	}
}emt[N];
struct Binary_Indexed_Tree{
	int sum[N];
	int lowbit(int x){
		return x&(-x);
	}
	void clear(int pos){
		if(pos==0)
			return;
		while(pos<=lshcnt){
			sum[pos]=0;
			pos+=lowbit(pos);
		}
	}
	void modify_add(int pos,int va){
		if(pos==0)
			return;
		while(pos<=lshcnt){
			sum[pos]+=va;
			pos+=lowbit(pos);
		}
	}
	int query_sum(int pos){
		int res=0;
		while(pos){
			res+=sum[pos];
			pos-=lowbit(pos); 
		}
		return res;
	}
}bit;
void mian(){
	for(int i=1;i<=n;i++)
		emt[i].clear();
	cin>>n;
	lshcnt=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		b[i]=-b[i];
		lsh[++lshcnt]=a[i];
		lsh[++lshcnt]=b[i];
	}
	sort(lsh+1,lsh+lshcnt+1);
	lshcnt=unique(lsh+1,lsh+lshcnt+1)-lsh-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(lsh+1,lsh+lshcnt+1,a[i])-lsh;
		b[i]=lower_bound(lsh+1,lsh+lshcnt+1,b[i])-lsh;
	}
	for(int i=1;i<=n;i++){
		emt[i].a=a[i];
		emt[i].b=b[i];
	}
	sort(emt+1,emt+n+1);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=bit.query_sum(emt[i].b-1);
		bit.modify_add(emt[i].b,1);
	}
	cout<<ans<<'\n';
	for(int i=1;i<=n;i++)
		bit.clear(emt[i].b);
}
bool Mend;
signed main(){
//	File_Work();
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cerr<<fixed<<setprecision(3)<<(&Mbegin-&Mend)/1048576.0<<" MB\n\n\n";
	int testnum=1;
	cin>>testnum;
	while(testnum--)
		mian();
	cerr<<"\n\n\n"<<fixed<<setprecision(0)<<1e3*clock()/CLOCKS_PER_SEC<<" ms";
	return 0;
}
```

CF 网友好像有一种奇妙做法，在[评论区](https://codeforces.com/blog/entry/123876)里，[代码](https://codeforces.com/contest/1915/submission/239387414)。

---

## 作者：_O_v_O_ (赞：0)

首先，让我们讨论只有 $2$ 个人时的情况：

- 二人路程不相交（即 $a_1\le b_1<a_2\le b_2$）：一眼看出不会相遇；
- 二人路程相交不包含(即 $a_1<a_2\le b_1<b_2$)：因为两人速度相同且终点在 $b_1$ 的人永远不会走到 $b_2$，所以也不会相遇。
- 二人路程包含(即 $a_1\le a_2\le b_2\le b_1$)：第二个人会在 $b_2$ 等第一个人，所以会相遇。

经过上面的分讨，我们得出结论：

若有 $(i,j)$ 满足 $a_i\le a_j\le b_j\le b_i$ 则可相遇。

所以我们可以将 $a$ 升序排序，$b$ 中有 $(i,j)$ 满足 $b_i\ge b_j$ 则计数器 $+1$，这就是逆序对。

这样我们就愉快的把这题转换成逆序对板子了。

---

## 作者：harmis_yz (赞：0)

## 分析

注意到所有人的速度相同，运动方向相同。所以两个人人相遇有且仅有其中一个人停止且另一个人运动到停止的人的位置。

不难发现对于 $i$，在他停下后能遇到的人的数量就是 $a_j \le a_i \land b_i \le b_j$ 的数量。按照 $b$ 为关键字从大到小排序然后树状数组即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second
 
il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
il void write(int x) {    
    if(x<0) putchar('-'),x=-x;    
    if(x>9) write(x/10);    
    putchar(x%10+'0');    
    return;    
}
 
const int N=2e5+10;
int n;
struct node{
	int a,b;
}s[N];
int b[N],idx,ans;
int tr[N<<2];

il bool cmp(node a,node b){
	return a.b>b.b;
}
il void add(int x){
	while(x<=idx*2) tr[x]++,x+=x&(-x);
}
il int query(int x){
	int ans=0;
	while(x) ans+=tr[x],x-=x&(-x);
	return ans;
}
 
il void solve(){
	n=read(),idx=ans=0;
	for(re int i=1;i<=n;++i) s[i].a=read(),s[i].b=read(),b[++idx]=s[i].a;
	sort(b+1,b+idx+1),idx=unique(b+1,b+idx+1)-(b+1);
	for(re int i=1;i<=n;++i) s[i].a=lower_bound(b+1,b+idx+1,s[i].a)-b;
	for(re int i=0;i<=idx*2;++i) tr[i]=0;
	sort(s+1,s+n+1,cmp);
    for(re int i=1;i<=n;++i)
		ans+=query(s[i].a),add(s[i].a);
	printf("%lld\n",ans);
	return ;
}
 
signed main(){
	int t=read();while(t--)
	solve();
	return 0;
}
```


---

## 作者：MicroSun (赞：0)

很明显，因为两个人速度相同，起点不同，只有当一个人停下来时，另一个人才可以追上他。

形式化地说，令 $i$ 为追逐者，$j$ 为被追逐者。$i$ 能追上 $j$，当且仅当 $a_i<a_j$ 且 $b_i>b_j$。

结合图理解：
![](https://cdn.luogu.com.cn/upload/image_hosting/cz8yoed5.png)

考虑用树状数组结合差分维护 $a_j$ 与 $b_j$ 之间的 $b_i$ 数量，加和即可。

注意：数字范围较大，需要离散化。

代码：
```cpp
// Problem: F. Greetings
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define me(a,x) memset((a),(x),sizeof(a))
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)
#define lowbit(x) ((x)&-(x))

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

void exgcd(ll a,ll b,ll &x,ll &y){
	if(!b) x=1,y=0;
	else exgcd(b,a%b,y,x),y-=a/b*x;
}
void ckmax(ll &a,ll b){a=max(a,b);}
void ckmin(ll &a,ll b){a=min(a,b);}

const int maxn=2e5+10;

struct line{
	ll l,r;
}a[maxn];
ll t[maxn<<1],n;
struct _{
	ll t,k,w;
}lsh[maxn<<1];//离散化辅助数组
int cnt;
ll sum(int x){
	ll ans=0;
	while(x){
		ans+=t[x];
		x-=lowbit(x);
	}
	return ans;
}
void add(int x,int k){
	while(x<=2*n) t[x]+=k,x+=lowbit(x);
}//树状数组板子
void solve(){
	cin>>n;
	cnt=0;
	rep(i,1,n){
		cin>>a[i].l>>a[i].r;
		lsh[++cnt]={i,a[i].l,1};
		lsh[++cnt]={i,a[i].r,2};
	}
	sort(lsh+1,lsh+(n<<1)+1,[](_ a,_ b){return a.k<b.k;});
	rep(i,1,(n<<1)){
		if(lsh[i].w==1) a[lsh[i].t].l=i;
		else a[lsh[i].t].r=i;
	}
	sort(a+1,a+1+n,[](line a,line b){return a.l<b.l;});
	ll ans=0;
	rep(i,1,n){
		ans+=sum(a[i].r);
		add(a[i].l,1);
		add(a[i].r+1,-1);//差分
	}
	rep(i,1,n){
		add(a[i].l,-1);
		add(a[i].r+1,1);
	}
	cout<<ans<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	cin>>t;
	while(t--) solve();
   	return 0;
}
```


---

