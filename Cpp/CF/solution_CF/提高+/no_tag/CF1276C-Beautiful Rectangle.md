# Beautiful Rectangle

## 题目描述

You are given $ n $ integers. You need to choose a subset and put the chosen numbers in a beautiful rectangle (rectangular matrix). Each chosen number should occupy one of its rectangle cells, each cell must be filled with exactly one chosen number. Some of the $ n $ numbers may not be chosen.

A rectangle (rectangular matrix) is called beautiful if in each row and in each column all values are different.

What is the largest (by the total number of cells) beautiful rectangle you can construct? Print the rectangle itself.

## 样例 #1

### 输入

```
12
3 1 4 1 5 9 2 6 5 3 5 8
```

### 输出

```
12
3 4
1 2 3 5
3 1 5 4
5 6 8 9
```

## 样例 #2

### 输入

```
5
1 1 1 1 1
```

### 输出

```
1
1 1
1
```

# 题解

## 作者：Mr_Wu (赞：4)

我们设构造的矩阵长，宽分别为 $R, C (R<C)$。

考虑如下事实：若存在一种数，出现的次数大于 $R$，则由抽屉原理，它们是不可能放进这个矩阵且每行都互不相同的。

而当所有数都不大于 $R$ 时，我们考虑将相同的数放在一块，并按如下顺序将它们这样放进矩阵：（按 1,2,... 分别放入）

![](https://cdn.luogu.com.cn/upload/image_hosting/gpt5bxpc.png)

比如对样例，将相同的数放在一块后是 ``5 5 5 3 3 1 1 9 8 6 4``，按上述方法放入：

```
5 3 1 6
4 5 3 9
8 2 5 1
```

就能有合法的构造方案。

这是因为每次我们总将相同的数按斜行放入，由于出现次数不大于 $R$，因此必然不会重合。

所以我们只需要知道 $R,C$ 的具体取值就好了。显然我们让 $R,C$ 尽量靠近，所以我们预处理 $R_x$ 表示大小为 $x$ 的矩阵的 $R$。然后我们倒序枚举 $x$，每次将次数最大的数删一个，再看能不能放进大小为 $x$ 的矩阵即可。可以考虑使用 ``std::map`` 或 ``std::set`` 支持这种贪心策略。

时间复杂度 $O(n\log n)$，预处理 $R_x$ 和贪心都是这个复杂度。

代码就不贴了，写得太丑。。

---

## 作者：AKPC (赞：3)

本文已过，修改一下错误。
### 前言
模拟考的一道比较简单的题，但是在学校的数据下悲痛拿到了 $95$ 分的好成绩（WA 一个点），在 CF WA 了第五十个点，发现是数字放置的顺序错了。

赛后的讲解里面用的是跟题解区相同的枚举方式，在这里给一个跟题解区不同的方法。
### 思路
首先假设矩形短边长 $x$，长边长 $y$，则选择 $xy$ 个数字，但是如果同一个数字被选中的数量大于 $x$，不考虑其他数字，显然怎么放都是不符合要求的。

所以也就说明了，选择数字的时候可以让选择的数字的种类尽量多，尽量把每种数字的个数平均分配。

可以根据上述条件，写一个 `sort` 的 `comp`，设一个 $t$ 数组，$t_i$ 表示排序后的 $\displaystyle\max_{j=1}^if(a_i)$，其中 $f(a_i)$ 表示 $a_i$ 在 $a_{1\sim i}$ 中出现的次数（节省时间复杂度，之后的枚举直接先特判）。

接着我们考虑，选择 $k$ 个数时的情况，显然短边越长，对于同种数字个数的约束就更小，从 $\lfloor\sqrt k\rfloor$ 开始不断减一寻找因数，找到的第一个因数即为短边最长的长度。

找到之后，枚举一遍数列的数字，这里需要再给数列按照数字在整个数列出现次数从大到小排序（省的到时候还要麻烦地给数字腾出空位），按照斜线摆放数字，具体摆放顺序可以参考下面的表格：

| $01$ | $05$ | $09$ | $13$ | $17$ |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $18$ | $02$ | $06$ | $10$ | $14$ |
| $15$ | $19$ | $03$ | $07$ | $11$ |
| $12$ | $16$ | $20$ | $04$ | $08$ |


然后注意同一种数字不要摆放超过短边长度个数。

这样做法就很显然了，直接枚举 $k$，即数字个数，然后求两边长，最后直接摆放就行了。时间复杂度可能较优，但常数较大。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int clac(const int x){
	int l=sqrt(x);
	while (x%l&&l>=1) l--;
	return l;
}
int n,t[1000005];
struct node{int v,id;}a[1000005];
unordered_map<int,int>mp;
map<pair<int,int>,int>ans;//ans[x][y]
inline bool comp(node o,node p){return o.id<p.id;}
inline bool compprint(node o,node p){
	if (mp[o.v]!=mp[p.v]) return mp[o.v]>mp[p.v];
	return o.v<p.v;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for (register int i=1;i<=n;i++) cin>>a[i].v,a[i].id=++mp[a[i].v];
	sort(a+1,a+n+1,comp);
	for (register int i=1;i<=n;i++) t[i]=max(t[i-1],a[i].id);
	sort(a+1,a+n+1,compprint);
	for (register int i=n;i>=1;i--){
		const int x=clac(i),y=i/x;
		if (t[i]>x) continue;
		int tipx=1,tipy=1,tip;
		for (register int j=1;j<=n;j++){//这一部分只会运行一次
			if (a[j].v!=a[j-1].v) tip=1;
			else tip++;
			if (tip>x) continue;
			ans[make_pair(tipx,tipy)]=a[j].v;
			tipx++,tipy++;
			if (tipx>x) tipy=(tipy-x+1+y)%y,tipx-=x;
			if (tipy>y) tipy-=y;
			if (tipx==0) tipx=x;
			if (tipy==0) tipy=y;
		}
		cout<<x*y<<'\n'<<x<<' '<<y<<'\n';
		for (register int j=1;j<=x;j++){
			for (register int k=1;k<=y;k++) cout<<ans[make_pair(j,k)]<<' ';
			cout<<'\n';
		}
		return 0;
	}
	return 0;
}
```


---

## 作者：wjh2011 (赞：3)

由于总共有 $n$ 个数，所以较短的边至多为 $\sqrt n$。我们可以直接枚举较短边的长度，较短边的长度固定后较长边的长度也可以直接确定。

设长为 $a$，宽为 $b$ 的矩形是满足要求的最大矩形，所以每个数最多可以放进矩形 $min\{b, num\}$ 个，其中 $num$ 表示这个数出现的次数。

我们把每个数按 $num$ 从大到小排序，然后从前往后依次放入这些数就可以了。

**注意：由于相同的数不能在同一行或同一列，所以斜着放一定是最优的。**

时间复杂度为 $O(n \log n)$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ans, r, c, nowr = 1, nowc = 1, a[400005], p[400005], sump[400005], f[400005];
map<int, int> mp;
vector<int> v[400005];
int get(int i, int j) { return (i - 1) * c + j; }
void solve(int cnt, int val) {
    for (int i = 1; i <= cnt; i++) {
        f[get(nowr, nowc)] = val;
        if (nowr == r) nowr = 1, nowc -= r - 2;
        else if (nowc == c) nowr++, nowc = 1;
        else nowr++, nowc++;
        if (nowc < 1) nowc += c;
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    for (int i = 1; i <= n; i++)
        if (mp[a[i]] > 0) {
            p[mp[a[i]]]++;
            v[mp[a[i]]].push_back(a[i]);
            mp[a[i]] = 0;
        }
    for (int i = n; i; i--) sump[i] = sump[i + 1] + p[i];
    for (int i = 1; i * i <= n; i++) {
        int sum = sump[i] * i;
        for (int j = 1; j < i; j++) sum += p[j] * j;
        if (i * i > sum) continue;
        int j = sum / i;
        if (i * j > ans) ans = i * j, r = i, c = j;
    }
    cout << ans << "\n" << r << " " << c << "\n";
    for (int i = n; i; i--) {
        for (int j : v[i]) {
            if (!ans) break;
            solve(min({ans, r, i}), j);
            ans -= min({ans, r, i});
        }
        if (!ans) break;
    }
    for (int i = 1; i <= r * c; i++) cout << f[i] << (i % c ? ' ' : '\n');
    return 0;
}
```

---

## 作者：Randyhoads (赞：2)

[blog](https://www.cnblogs.com/wlzs1432/p/12048761.html)

显然出现次数最多的数出现次数一定小于行，这个时候列数也一定要大于行数，不然放不下

按出现次数将每个数排序

考虑从大到小枚举行，每次最大化列数

对于每个数，按从大到小的顺序把大于行数的减掉，同时更新可用的元素

显然你从大到小枚举的行，现在用不到的以后也用不到了

由于每个元素只会删一次，所以是O（n)的

填数的时候斜着填

代码如下

```
#include<bits/stdc++.h>

using namespace std;

#define re register 

inline int read()
{
	int x = 0,f = 1;
	char ch;
	do
	{
		ch = getchar();
		if(ch == '-') f = -1;
	}while(ch < '0'||ch > '9');
	do
	{
		x = (x<<3) + (x<<1) + ch - '0';
		ch = getchar();
	}while(ch >='0' && ch <='9');
	return f*x;
}

const int MAXN = 4e5 + 10;

int n;
int a[MAXN];
int b[MAXN],sum;
map<int,int>vis;
int tot;
int ansx,ansy;
pair<int,int>c[MAXN];
int M[MAXN];
int res;

int main()
{
	 n = read();
	 for(int i=1;i<=n;i++) a[i] = read();
	 sort(a+1,a+n+1);
	 for(int i=1;i<=n;i++)
	 {
	 	if(a[i]!=a[i-1]) b[i] = ++sum;
	 	else b[i] = sum;
	 	vis[b[i]] = a[i];
	 }
	 for(int i=1;i<=sum;i++) c[i].second = i;
	 for(int i=1;i<=n;i++) c[b[i]].first++;
	 sort(c+1,c+sum+1);tot = n;
	 for(int i=n;i>=1;i--)
	 {
	 	for(int j=sum;j&&c[j].first>i;j--)
	 	{
	 		c[j].first--;
			tot--;	
		}
		int p = tot / i;
		if(p < i) continue;
		if(res < p * i)
		{
			res = p * i;
			ansx = i,ansy = p;
		}
	 }
	 for(int i=1;i<=sum;i++)
	 {
	 	c[i].first = 0;c[i].second = i;
	 }
	 for(int i=1;i<=n;i++) c[b[i]].first++;
	 cout << res << endl << ansx << " " <<ansy << endl;
	 sort(c+1,c+sum+1);
	 for(int i=sum;i>=1;i--)
	 {
	 	if(c[i].first>=ansx) c[i].first = ansx;
	 	else break;
	 }
	 int p = sum;
	 for(int i=1;i<=ansy;i++)
	 {
	 	for(int j=1;j<=ansx;j++)
	 	{
	 		if(c[p].first==0) p--;
	 		M[(j-1)*ansy+(i+j)%ansy+1] = vis[c[p].second];
	 		c[p].first--;
		}
	 }
	 for(int i=1;i<=res;i++)
	 {
	 	cout << M[i] << " ";
	 	if(i%ansy==0) cout << endl;
	 }
}
```




---

## 作者：Hoks (赞：1)

## 前言
恶心题，不必多言。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。
## 思路分析
估计是代码难度干到 $2300$ 去了，没有任何思维难度吧。

考虑对于一个大小为 $x,y(x<y)$ 的矩形，根据鸽巢定理，不能放入大于 $x$ 个相同的数。

那卡满的情况，就是每个数刚好都在每行每列出现一次，也就是斜着放的时候。

那么我们枚举 $x$ 计算 $y$，这时就是要实现最多能放几个元素进去。

那么就是个数小于 $x$ 的直接取原个数，个数大于 $x$ 的取 $x$ 个。

全部枚举一遍数出来最大情况最后输出就行了。

然后还要记得离散化一下。
## 代码

```cpp
#include<bits/stdc++.h>
#define get(x) (lower_bound(b+1,b+1+m,x)-b)
#define int long long
using namespace std;
constexpr int N=5e5+10,V=2e5,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,a[N],b[N],c[N],o[N];vector<int>e[N];
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r0'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void ot(int x,int y)
{
    int l=1,r=1,s=0,g[x+1][y+1]={0};
    for(int i=n;i>=1;i--) for(auto w:e[i])
        for(int j=1;j<=min(i,x);j++)
        {
            if(g[l][r]) r++;if(r==y+1) r=1;
            g[l][r]=w;l++,r++;s++;
            if(r==y+1) r=1;
            if(l==x+1) l=1;
            if(s==x*y) goto play;
        }
    play:;print(x*y),put('\n');
    print(x),put(' '),print(y),put('\n');
    for(int i=1;i<=x;i++,put('\n')) for(int j=1;j<=y;j++) print(g[i][j]),put(' ');
}
inline void solve()
{
    n=read();for(int i=1;i<=n;i++) b[i]=a[i]=read();
    sort(b+1,b+1+n);m=unique(b+1,b+1+n)-b-1;int s=0,t=0,ans=0,ll=0,rr=0;
    for(int i=1;i<=n;i++) c[get(a[i])]++,o[get(a[i])]=a[i];
    for(int i=1;i<=m;i++){e[c[i]].emplace_back(o[i]);s+=c[i];}
    for(int i=n;i>=1;i--)
    {
        int r=(s+i*t)/i;
        if(r>=i&&i*r>ans) ans=i*r,ll=i,rr=r;
        s-=e[i].size()*i;t+=e[i].size();
    }ot(ll,rr);
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
	genshin:;flush();return 0;
}
```

---

