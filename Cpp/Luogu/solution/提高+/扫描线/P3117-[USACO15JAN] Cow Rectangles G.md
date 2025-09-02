# [USACO15JAN] Cow Rectangles G

## 题目描述

农夫约翰的 $N$ 头牛（$1 \leq N \leq 500$）的位置由二维平面上互不相同的点描述。这些牛分为两个品种：Holsteins 和 Guernseys。农夫约翰希望建造一个边与坐标轴平行的矩形围栏，仅包含 Holsteins 且不包含任何 Guernseys（即使牛位于围栏边界上也视为被包含）。在所有满足条件的围栏中，农夫约翰希望选择包含最多 Holsteins 的围栏。若存在多个这样的围栏，则选择其中面积最小的一个。请确定这个面积。允许围栏的宽度或高度为零。

## 样例 #1

### 输入

```
5 
1 1 H 
2 2 H 
3 3 G 
4 4 H 
6 6 H 
```

### 输出

```
2 
1 ```

# 题解

## 作者：素质玩家孙1超 (赞：8)

别的题解的做法都好正经啊，

我来一发 random_shuffle 的题解。

---

题意：一个平面上有好多点，分别为 $G$ 和 $H$ ，求不包含 $G$ 且包含 $H$  最多的子矩阵，并输出包含多少个 $H$ 和所有情况下最少的面积。

---

我一看到 $n \leq 500 $ 就想到了那个神奇的 random_shuffle 。

如果你不知道 random_shuffle ，这个函数就是c++内置的随机打乱一个数组的函数。
 

那么直接考虑答案基于排列顺序的假贪心。

我们直接按照数组里面的排列顺序加入点，若这个点加入了后子矩阵中包含了至少一个 $G$ ，那么就不加入这个点，否则贪心加入。


这个算法的效果：大概平均几十次随机之后就可以搞出正确答案，然而如果按照1s来算最多可以跑大约 $1$W 次左右，显然是随随便便就 $AC$ 掉了。

用二位树状数组优化一次随机的复杂度是 $O(n\times \log ^2(n))$ 。 ($n \leq 500 $ )


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int R()
{
	char c;int res,sign=1;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;
}
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
const int Maxn=505;
struct point 
{
	int x,y;
}a[Maxn],b[Maxn];
#define lowbit(x) (x&-x)
int n,ans=1,M=0,top1,top2,V[Maxn*2][Maxn*2];
void up(int x,int y)
{
	for(int i=x;i<=1001;i+=lowbit(i))
	for(int j=y;j<=1001;j+=lowbit(j))
	V[i][j]++;
}
inline int sum(int x,int y)
{
	int res=0;
	for(int i=x;i>0;i-=lowbit(i))
	for(int j=y;j>0;j-=lowbit(j))
	res+=V[i][j];
	return res;
}
inline void work()
{
	random_shuffle(a+1,a+top1+1);
	int Mix=a[1].x,Max=a[1].x,Miy=a[1].y,May=a[1].y;
	int p1,p2,p3,p4,res=1;
	for(int i=2;i<=top1;i++)
	{
		p1=Mix;p2=Max;p3=Miy;p4=May;
		Mix=min(Mix,a[i].x);Max=max(Max,a[i].x);
		Miy=min(Miy,a[i].y);May=max(May,a[i].y);
		int p=sum(Max,May);
		p+=sum(Mix-1,Miy-1)-sum(Mix-1,May)-sum(Max,Miy-1);
		if(p){res--;Mix=p1;Max=p2;Miy=p3;May=p4;}
		res++;
	}
	if(res==ans)
	{
		M=min(M,(Max-Mix)*(May-Miy));
	}
	else if(res>ans)
	{
		ans=res;
		M=(Max-Mix)*(May-Miy);
	}
}
int main()
{
	n=R();int x,y;
	for(int i=1;i<=n;i++)
	{
		x=R()+1;y=R()+1;
		char c;
		while((c=getchar())!='H'&&c!='G');
		if(c=='H') 
		{
			a[++top1].x=x;
			a[  top1].y=y;
		}
		else 
		{
			b[++top2].x=x;
			b[  top2].y=y;
			up(x,y);
		}
	}
	for(int i=1;i<=1000;i++)work();
	printf("%d\n%d\n",ans,M);
}
```

---

## 作者：伟大的王夫子 (赞：4)

这题的数据范围较小，$n$ 只有 500，仿佛就在暗示我们用 $O(n^3)$ 时间复杂度的算法来通过这道题。但由于 $x, y$ 的范围比 $n$ 要大，所以说我们要先将每个点的值进行离散化。

在这个算法中，我们枚举上下两行 $x1,x2$。然后我们考虑对中间的部分进行计算。

对于中间，我们可以将其分为好几个部分，使得每个部分都不含有 G 牛。我们枚举每一列 $y$（这一列上必须有一个 H 牛，否则我们可以将 $y$ 加上 1 使得面积更小），进行尺取，直到扫描到了一个有 G 牛的列为止。在尺取的时候，注意更新答案即可

时间复杂度为 $O(n^3)$。建议大家自己先写一遍，再去看代码。这个算法时间复杂度比较高，但对于基础相对较差的同学而言利于理解，并且也能过了此题。况且，大多数情况跑不满。为了方便统计矩阵中牛的个数，可以开二维数组记一下前缀和。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T>
inline void Rd(T &x) {
    x = 0;
    bool f = 0;
    char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    if (f)
        x = -x;
}
int n;
struct P {
    int x, y;
    bool p;
} a[505];
int b[505], c[505], bm, cm, s[505][505][2];
int calc(int x, int y, int _x, int _y, bool p) {
    return s[_x][_y][p] - s[_x][y - 1][p] - s[x - 1][_y][p] + s[x - 1][y - 1][p];
}
void Chk(int &ans, int &area, int x, int y) {
    if (x > ans)
        ans = x, area = y;
    else if (ans == x && y < area)
        area = y;
}
int main() {
    Rd(n);
    for (int i = 1; i <= n; ++i) {
        char op[5];
        scanf("%d%d%s", &a[i].x, &a[i].y, op);
        if (op[0] == 'G')
            a[i].p = 0;
        else
            a[i].p = 1;
        b[++bm] = a[i].x, c[++cm] = a[i].y;
    }
    sort(b + 1, b + bm + 1);
    sort(c + 1, c + cm + 1);
    bm = unique(b + 1, b + bm + 1) - b - 1;
    cm = unique(c + 1, c + cm + 1) - c - 1;
    for (int i = 1; i <= n; ++i) a[i].x = lower_bound(b + 1, b + bm + 1, a[i].x) - b;
    for (int i = 1; i <= n; ++i) a[i].y = lower_bound(c + 1, c + cm + 1, a[i].y) - c;
    for (int i = 1; i <= n; ++i) ++s[a[i].x][a[i].y][a[i].p];
    for (int i = 1; i <= bm; ++i)
        for (int j = 1; j <= cm; ++j)
            for (int p = 0; p <= 1; ++p) s[i][j][p] += s[i - 1][j][p] + s[i][j - 1][p] - s[i - 1][j - 1][p];
    int area = 1e9, ans = 0;
    for (int x1 = 1; x1 <= bm; ++x1)
        for (int x2 = x1; x2 <= bm; ++x2) {
            int p = 0;
            for (int y = 1; y <= cm; ++y) {
                if (calc(x1, y, x2, y, 0) == 1) {
                    p = y;
                    continue;
                }
                if (calc(x1, y, x2, y, 1) == 0) continue;
                if (p >= y)
                    Chk(ans, area, calc(x1, y, x2, p, 1), (b[x2] - b[x1]) * (c[p] - c[y]));
                while (p + 1 <= cm && calc(x1, y, x2, p + 1, 0) == 0)
                    ++p, Chk(ans, area, calc(x1, y, x2, p, 1), (b[x2] - b[x1]) * (c[p] - c[y]));
            }
        }
    printf("%d\n%d", ans, area);
}
```

---

## 作者：hgzxwzf (赞：3)

# [P3117](https://www.luogu.com.cn/problem/P3117)
~~又水一道紫题~~。

## 解题思路：
首先发现最小的矩形一定满足矩阵的每一条边上都有 $\verb!H!$ 牛，显然，如果没有，我们可以平移那条边，使得那条边碰到一头 $\verb!H!$ 牛，且包含牛的个数不变。

所以我们可以枚举矩形的上下边界，在从左往右扫描。

将所有牛按照 $y$ 坐标从小到大排序，枚举矩形上边界覆盖到的牛 $j$，下边界覆盖到的牛 $i$，设 $A$ 表示 $y$ 坐标属于 $[y_i,y_j]$ 的牛的集合，按 $x$ 坐标从小到大排序，从左往右扫。

假设现在枚举到 $k$，设 $l$ 表示当前最靠左且满足 $l$ 到 $k$ 之间没有 $\verb!G!$ 牛的牛，$sum$ 表示 $l$ 到 $k$ 之间牛的个数。

如果当前 $x$ 坐标在 $[y_i,y_j]$ 上有 $\verb!G!$ 牛，那么把 $l,sum$ 清零，否则用 $sum$ 和 $(y_i-y_j)\times (x_i-x_l)$ 更新答案。

## Code:

```cpp
struct cow
{
	int x,y,ki;
}c[N];

bool comp(const cow &P,const cow &Q)
{
	return P.y<Q.y;
}

bool comp2(const cow &P,const cow &Q)
{
	return P.x<Q.x;
}

bool bo[N<<1];

int main()
{
	int n;
	scanf("%d",&n);
	rep(i,1,n)
	{
		char s[2];
		scanf("%d%d %s",&c[i].x,&c[i].y,s);
		if(*s=='H') c[i].ki=1;
	}
	sort(c+1,c+1+n,comp);
	pi ans=mk(0,0);
	rep(i,1,n)
		rep(j,i,n)
		if(c[i].ki&&c[j].ki)
		{
			int l=i,r=j;
			while(l>1&&c[l-1].y==c[i].y) l--;
			while(r<n&&c[r+1].y==c[j].y) r++;
			vector<cow>a;
			a.push_back((cow) {0,0,0});
			memset(bo,0,sizeof(bo));
			rep(k,l,r)
			{
				if(!c[k].ki) bo[c[k].x]=1;
				a.push_back(c[k]);
			}
			sort(a.begin(),a.end(),comp2);
			int mx=0;
			l=0;
			rep(k,1,(int) a.size()-1)
			{
				cow b=a[k];
				if(bo[b.x]) mx=0;
				else
				{
					if(!mx) l=b.x;
					mx++;
					if(mx>ans.fi) ans=mk(mx,(c[j].y-c[i].y)*(b.x-l));
					else if(mx==ans.fi) ans.se=min(ans.se,(c[j].y-c[i].y)*(b.x-l));
				}
			}
		}
	printf("%d\n%d",ans.fi,ans.se);
	return 0;
}

```


---

## 作者：NewErA (赞：2)

######首先，这道题涉及到了最大子矩阵等一系列问题

######这里推荐由国家集训队成员王知昆撰写的论文:http://blog.csdn.net/twtsa/article/details/8120269

这篇论文中首先提出了极大子矩阵的概念，严谨证明了最大子矩阵一定在极大子矩阵中。

因此，我们只要枚举出所有极大子矩阵即可。


文中介绍了两种算法：1、O(点的个数^2)       2、O(n\*m)

######对于本题而言，明显选用第一种算法


由于这里的注释中写不了中文，我把整个实现代码的技巧总结先写在这里：

1、首先要理清思路，分为4中情况讨论

A循环解决 所有点之间的极大子矩阵  和  右边界为整个矩形右边界的情形

B循环解决左边界为整个矩形左边界的情形

C循环解决左右边界均为矩形边界的情形


2、为了在O(1)时间内算出一定区域内h点的个数，必然要预处理

我使用的是f[i,j]表示矩形[1~i][1~j]中h点的个数


3、在进行上下界判断时=号不能丢


4、string.size()返回的是unsigned int，注意强制转换


附上代码（检索没有使用2分，可以选择用2分实现）：

```cpp
#include<bits/stdc++.h>

using namespace std;
struct cow
{
    int x,y;
    cow(int a,int b)
    {
        x=a;y=b;
    } 
};

vector<cow> g,h;
int n,km,kn,f[1005][1005];
char data[1005][1005];

bool cmp(cow a,cow b)
{
    if(a.x!=b.x) return a.x<b.x;
    else return a.y<b.y;
}

bool cmpx(cow a,cow b)
{
    if(a.y!=b.y) return a.y<b.y;
    else return a.x<b.x;
}

int calarea(int i,int j,int maxy,int miny)
{
    if(maxy<=miny) return 0;
    int m1=0,m2=0,m3=1<<27,m4=1<<27;
    for (int k=0;k<h.size();k++) 
    {
        if(h[k].x<=j && h[k].x>=i && h[k].y>=miny && h[k].y<=maxy)
        {
            m1=max(m1,h[k].x);
            m3=min(m3,h[k].x);
            m2=max(m2,h[k].y);
            m4=min(m4,h[k].y);
        }
    }
    return (m1-m3)*(m2-m4);
}

int main()
{
    cin >> n;
    g.push_back(cow(0,0));
    
    for(int i=1;i<=n;i++)
    {
        int t1,t2;char r;
        cin >> t1 >> t2 >> r;
        data[t1+1][t2+1]=r;  //这里的+1处理是为了使将0行0列空出，作为缓冲区 
        km=max(t1+1,km);
        kn=max(t2+1,kn);
        if(r=='H') 
            h.push_back(cow(t1+1,t2+1));
        else
        {
            g.push_back(cow(t1+1,t2+1));
        }            
    }
    
    g.push_back(cow(km+1,0));
    sort(g.begin(),g.end(),cmp);
    sort(h.begin(),h.end(),cmp);
    
    memset(f,0,sizeof(f));  //这里的预处理要留心，可以在O(1)时间内算出区域内的合格点的个数 
    for(int i=1;i<=km;i++)
        for(int j=1;j<=kn;j++)
        {
            f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
            if(data[i][j]=='H') f[i][j]++;            
        }
    
    int maxy,miny;
    int res=-1,area=-1;
    for(int i=1;i<g.size();i++)  //这里考虑的情况是所有点之间的极大子矩阵  和  右边界为整个矩形右边界的情形 
    {
        miny=0;maxy=kn+1;
        for(int j=i+1;j<g.size();j++)
        {
            if(g[j].x-g[i].x<2)
            {
                if(g[j].y<=g[i].y && miny < g[j].y) miny=g[j].y;
                if(g[j].y>=g[i].y && maxy > g[j].y) maxy=g[j].y;
                continue;
            }
            int cnt=f[g[j].x-1][maxy-1]-f[g[j].x-1][miny]-f[g[i].x][maxy-1]+f[g[i].x][miny];
            int mina=calarea(g[i].x+1,g[j].x-1,maxy-1,miny+1);
            if(cnt>res || (cnt==res && mina<area))
            {
                res=cnt;
                area=mina;
            }
            
            if(g[j].y<=g[i].y && miny < g[j].y) miny=g[j].y;  //这里的等于很重要，注意细节！！！ 
            if(g[j].y>=g[i].y && maxy > g[j].y) maxy=g[j].y;  //等号要单独考虑！！！ 
        }
    }
    
    for(int i=int(g.size()-2);i>=1;i--)  //这里要考虑左边界为整个矩形左边界的情形 
    {                                    //再次注意这里的强制转换！！！ 
        miny=0;maxy=kn+1;
        for(int j=i-1;j>=0;j--)
        {
            if(g[j].y<=g[i].y && miny < g[j].y) miny=g[j].y;
            if(g[j].y>=g[i].y && maxy > g[j].y) maxy=g[j].y;
                        
            if(j!=0) continue;
            
            int cnt=f[g[i].x-1][maxy-1]-f[g[i].x-1][miny]-f[g[j].x][maxy-1]+f[g[j].x][miny];
            int mina=calarea(g[j].x+1,g[i].x-1,maxy-1,miny+1);
            if(cnt>res || (cnt==res && mina<area))
            {
                res=cnt;
                area=mina;
            }
        }
    }
    
    g.push_back(cow(0,kn+1));  //这里考虑的是左右边界均为矩形边界的情形 
    sort(g.begin(),g.end(),cmpx);
    for(int i=1;i<g.size();i++)
    {
        if(g[i].y-g[i-1].y<2) continue;
        int cnt=f[km][g[i].y-1]-f[km][g[i-1].y];
        int mina=calarea(1,km,g[i].y-1,g[i-1].y+1);
        if(cnt>res || (cnt==res && mina<area))
        {
            res=cnt;
            area=mina;
        }        
    }
    
    cout << res << endl << area;
    return 0;
}
```

---

## 作者：__log__ (赞：1)

[题目折跃门](https://www.luogu.com.cn/problem/P3117)

哈哈，可以光明正大地水题解了！

为什么（几乎）所有题解都是三次方做法？

tag：扫描线，STL。

## 第一幕

平面上有 $n$ 个点，点有黑（G）白（H）两色，要求一个内部（包括边界）没有黑（G）点的矩形，最大化覆盖白（H）点数，同时最小化面积。

## 第二幕

假设我们确定了矩形一条左边界，随着右边界向右扫，黑（G）点给的限制会越来越紧，可以直接扫描线。

具体地说：

枚举一个白（H）点，假设坐标为 $(l,pos)$，表示这个矩形永远覆盖这个白点，且以这个点的横坐标作为左边界，且维护矩形上下边界可以接受的最值。

然后向右扫右边界，如果扫到一个白点，且这个点的纵坐标在可接受的区间内，那把这个点加入矩形，用 `multiset` 维护；

如果这个点是黑点 $(x,y)$，就修改最值。

$$Max = \min(Max,y-1)(y\ge pos)$$

$$Min = \max(Min,y+1)(y \le pos)$$

然后删掉矩形内不符合新边界的点。

时间复杂度 $O(n^2\log n)$。

## 第三幕

~~玩原神玩的~~

```cpp
// I love Furina forever!
# include <bits/stdc++.h>
# define maxn 100100
# define mod 1000000007
# define inf 0x3f3f3f3f
# define mem(a, val) memset(a, val, sizeof(a))
# define rep(i, j, k) for(int i = j; i <= k; ++i)
# define per(i, j, k) for(int i = j; i >= k; --i)
using namespace std;

struct Furina {
    int x, y, c;
    inline bool operator < (const Furina tmp) const {return x == tmp.x ? (c == tmp.c ? y < tmp.y : c < tmp.c) : x < tmp.x;}
} a[505];

int n, ans1, ans2;
int b[505], siz[505];
vector<Furina> c[505];

signed main() {
    // freopen("cowrest.in", "r", stdin);
    // freopen("cowrest.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) {char ch; cin >> a[i].x >> a[i].y >> ch; a[i].c = ch == 'G'; b[i] = a[i].x;}
    sort(b + 1, b + n + 1); int pos = unique(b + 1, b + n + 1) - b - 1;
    rep(i, 1, n) a[i].x = lower_bound(b + 1, b + pos + 1, a[i].x) - b;
    rep(i, 1, pos) c[i].push_back({0, 0, 0});
    rep(i, 1, n) c[a[i].x].push_back(a[i]), siz[a[i].x]++;
    rep(i, 1, n) if(a[i].c == 0) {
        int l = a[i].x, Max = 1000, Min = 1, pos1 = a[i].y;
        multiset<int> st; st.clear();
        rep(r, a[i].x, pos) {
            rep(k, 1, siz[r]) {
                int y = c[r][k].y;
                if(c[r][k].c == 0 && Min <= y && y <= Max) st.insert(y);
                else if(c[r][k].c == 1) {
                    if(y >= pos1) Max = min(Max, y - 1);
                    if(y <= pos1) Min = max(Min, y + 1);
                    while(st.size() && *st.begin() < Min) {st.erase(st.begin());}
                    while(st.size() && *st.rbegin() > Max) {st.erase(prev(st.end()));}
                }
            }
            if(Max < Min) break;
            if(st.size() > ans1) ans1 = st.size(), ans2 = (b[r] - b[l]) * (*st.rbegin() - *st.begin());
            else if(st.size() == ans1) ans2 = min(ans2, (b[r] - b[l]) * (*st.rbegin() - *st.begin()));
        }
    }
    cout << ans1 << '\n' << ans2 << '\n';
    return 0;
}
```

---

## 作者：lndjy (赞：1)

求最大子矩阵，很容易想到悬线法。

先不考虑面积的限制，只有两种奶牛，很容易想到做法：一个当作障碍点，然后套悬线法。另一个奶牛可以通过二维前缀和维护，这样可以 $O(1)$ 计算数量。这部分的时间复杂度是 $O(n^2)$ 的，不过跑不满，因为不是每个都是障碍点。

然后再看面积最小。由于数据范围 500 ，所以可以暴力求最小面积：枚举每个包含在内的非障碍奶牛点，把外圈缩小。

总共时间复杂度是 $O(n^3)$，不过跑不满。

**注意几个坑点：**

1. 边缘也算在内。
2. 输入时坐标要+1.

代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,s;
int f[1005][1005];
struct node
{
	int x,y;
}a[600],b[600];
int cnt,cntt;
void add(int x,int y)
{
	a[++cnt]=(node){x,y};
}
void addd(int x,int y)
{
	b[++cntt]=(node){x,y};
}
bool cmp(node x,node y)
{
	return x.x<y.x;
}
int cal(int x1,int y1,int x2,int y2)
{
	return f[x2][y2]-f[x1-1][y2]-f[x2][y1-1]+f[x1-1][y1-1];
}
int cals(int x1,int y1,int x2,int y2)
{
	if(y1>y2||x1>x2) return 0;
	int xx1=0,xx2=n,yy1=0,yy2=m;
	for(int i=1;i<=cntt;i++)
	{
		if(x1<=b[i].x&&b[i].x<=x2&&y1<=b[i].y&&b[i].y<=y2)
		{
			xx1=max(xx1,b[i].x);
			xx2=min(xx2,b[i].x);
			yy1=max(yy1,b[i].y);
			yy2=min(yy2,b[i].y);
		}
	}
	return (xx1-xx2)*(yy1-yy2);
}
int main()
{
	cin>>s;
	for(int i=1;i<=s;i++)
	{
		int x,y;
		char c;
		cin>>x>>y>>c;
		x++;y++;
		n=max(n,x);m=max(m,y);
		if(c=='H') f[x][y]=1,addd(x,y);
		else add(x,y);
	}
	n++,m++;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
	add(0,0);add(n,0);add(0,m);add(n,m);
	s=cnt;
	sort(a+1,a+s+1,cmp);
	int ans=0,anss=1e9,up,down;
	for(int i=1;i<=s;i++)
	{
		up=0;down=m;
		for(int j=i+1;j<=s;j++)
		{
			if(a[i].x+1<=a[j].x-1)
			{
				int cow=cal(a[i].x+1,up+1,a[j].x-1,down-1);
				int S=cals(a[i].x+1,up+1,a[j].x-1,down-1);
				if(cow>ans)
				{
					ans=cow;
					anss=S;
				//	cout<<a[i].x<<" "<<up<<" "<<a[j].x<<" "<<down<<" "<<ans<<" "<<anss<<endl; 
				}
				else if(cow==ans&&S<anss) anss=S;
			}
			if(a[j].y>=a[i].y) down=min(down,a[j].y);
			else up=max(up,a[j].y);
		}
	}
	cout<<ans<<"\n"<<anss;
	return 0;
}

```


---

## 作者：zhenglier (赞：1)

复杂度$O(n^3)$次的暴力算法~~（不过好像能过就不是暴力）~~

把每个点的坐标离散化，把$n$从1000降为500。

然后枚举矩阵的上下界，在两条线之间整一个类似单调队列的东西。但因为这里要是矩阵最小，所以在移动右端点时要实时更新矩阵中的最大点数和最大点数时的最小面积。

为了方便，我们在纵坐标上做一个前缀和，这里$f[i][j]$指第$i$列上前$j$行的$H$点个数；$g[i][j]$指第$i$列上前$j$行的$G$点个数。

然后就可以愉快的写题了
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,X,Y;
int x[510],y[510];
char c[510];
int a[510],b[510];
int f[510][510],g[510][510];
int main(){
//	freopen("1.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;++i){
        char op[2];
        scanf("%d%d%s",x+i,y+i,op);
        c[i]=op[0];
        a[i]=x[i],b[i]=y[i];
    }
    sort(a+1,a+n+1);X=unique(a+1,a+n+1)-a-1;
    for(int i=1;i<=n;++i){
        x[i]=lower_bound(a+1,a+X+1,x[i])-a;
    }
    sort(b+1,b+n+1);Y=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i){
        y[i]=lower_bound(b+1,b+Y+1,y[i])-b;
    }
    for(int i=1;i<=n;++i){
        if(c[i]=='H'){
            f[x[i]][y[i]]++;
        }else{
            g[x[i]][y[i]]++;
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            f[i][j]+=f[i-1][j];
            g[i][j]+=g[i-1][j];
        }
    }
    int mx=0,mn=0;
    for(int i=1;i<=X;++i){
        for(int j=i;j<=X;++j){
            int l=1,r=1,ans=0;
            while(r<=Y){
                while(l<=Y&&(g[j][l]-g[i-1][l]||!(f[j][l]-f[i-1][l])))l++,ans-=f[j][l]-f[i-1][l];
                r=l;ans=0;
                while(!(g[j][r]-g[i-1][r])&&r<=Y){
                    ans+=f[j][r]-f[i-1][r];
                    if(ans>mx)mx=ans,mn=(a[j]-a[i])*(b[r]-b[l]);
                    if(ans==mx)mn=min(mn,(a[j]-a[i])*(b[r]-b[l]));
                    r++;
                }
                l=r;
            }
        }
    }
    cout<<mx<<endl;
    cout<<mn<<endl; 
}
```

---

## 作者：AZYDLL (赞：1)

2003 年，国家集训队选手王知昆在其集训队论文[《浅谈用极大化思想解决最大子矩形问题》](https://blog.csdn.net/twtsa/article/details/8120269)中阐述了 $O(n^2)$（$n$ 为平面中点数）求二维平面中最大子矩形的算法，在此向大佬致敬。

本文的做法基于这种算法，时间复杂度 $O(n^2 \log n)$。

# 思路

这里我们将论文中的定义稍作修改，“极大子矩形”的边上不能有“障碍点”，做法是一样的。如下图，红色方框是其中一个“极大子矩形”。

![样例，红色框为其中一个“极大子矩形”](https://cdn.luogu.com.cn/upload/image_hosting/kyt1b9gu.png)

首先我们将 G 牛视作“障碍点”，按照论文里的做法 $O(n^2)$ 求出所有的“极大子矩形”。显然，我们要求的最优围栏一定是某个“极大子矩形”的子矩形。于是我们扫描线分别求每个“极大子矩形”中最靠近每条边的 H 点，并将对应边收缩到该点上，即可得到最小的有效矩形，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/g40kaaad.png)

以矩形上方的边为例，我们可以将“极大子矩形”的边和 H 点放在一起按 $y$ 坐标从小到大排序，用线段树维护一个区间内 $y$ 坐标最大的点的 $y$ 坐标。扫描线从下往上扫，扫到点则将点加入线段树，扫到边则区间求最大坐标。时间复杂度 $O(k \log n)$（$k$ 为“最大子矩形”的数量），即 $O(n^2 \log n)$。

# 代码

码丑常数大，路过大佬轻喷。

```cpp
#include<bits/stdc++.h>
#define MAXN 5005
#define MAXM 10005

using namespace std;
namespace FastIO
{
	inline string _rs()
	{
		string str="";
		int ch=getchar();
		while(ch==' ' || ch=='\n' || ch=='\r') ch=getchar();
		while(ch!=' ' && ch!='\n' && ch!='\r' && ch!=EOF){
			str.push_back(ch);
			ch=getchar();
		}
		return str;
	}
	inline void _ws(string a,char b)
	{
		int len=a.size();
		for(int i=0;i<len;i++) putchar(a[i]);
		putchar(b);
		return ;
	}
	inline int _r()
	{
		int flag=1,ans=0,ch=getchar();
		while((ch<'0' || ch>'9') && ch!=EOF){
			if(ch=='-') flag=-1;
			ch=getchar();
		}
		while(ch>='0' && ch<='9'){
			ans=(ans<<1)+(ans<<3)+(ch^48);
			ch=getchar();
		}
		return flag*ans;
	}
	inline void _w(int a,char b)
	{
		if(a<0) a=-a,putchar('-');
		int sta[22],top=0;
		do{
			sta[top++]=a%10;
			a/=10;
		}while(a);
		while(top) putchar(sta[--top]+48);
		putchar(b);
		return ;
	}
}
using namespace FastIO;

struct node{int x,y;} ifo[MAXN];
struct nodeAns{int x1,y1,x2,y2;} M[MAXN*MAXN],Ans[MAXN*MAXN];
struct nodeAsk{int x,l,r,flag,p;} ifo1[MAXN+MAXN*MAXN];
int n,x[MAXN],y[MAXN],sum[MAXM][MAXM],cnt,cntM,cnt1,cntAns,ans1,ans2;
char ch[MAXN];

struct node1{int l,r,maxx,minn;};
struct XD_Tree1
{
	node1 T[MAXM*4];
	void build(int p,int l,int r)
	{
		T[p].l=l,T[p].r=r,T[p].maxx=INT_MIN,T[p].minn=INT_MAX;
		if(l==r) return ;
		
		int mid=(l+r)/2;
		build(p*2,l,mid);
		build(p*2+1,mid+1,r);
		return ;
	}
	void change(int p,int x,int k)
	{
		if(T[p].l==T[p].r){
			T[p].maxx=T[p].minn=k;
			return ;
		}
		
		int mid=(T[p].l+T[p].r)/2;
		if(x<=mid) change(p*2,x,k);
		else change(p*2+1,x,k);
		T[p].maxx=max(T[p*2].maxx,T[p*2+1].maxx);
		T[p].minn=min(T[p*2].minn,T[p*2+1].minn);
		return ;
	}
	int ask_maxx(int p,int l,int r)
	{
		if(l<=T[p].l && T[p].r<=r) return T[p].maxx;
		
		int mid=(T[p].l+T[p].r)/2,ans=INT_MIN;
		if(l<=mid) ans=max(ans,ask_maxx(p*2,l,r));
		if(r>mid) ans=max(ans,ask_maxx(p*2+1,l,r));
		return ans;
	}
	int ask_minn(int p,int l,int r)
	{
		if(l<=T[p].l && T[p].r<=r) return T[p].minn;
		
		int mid=(T[p].l+T[p].r)/2,ans=INT_MAX;
		if(l<=mid) ans=min(ans,ask_minn(p*2,l,r));
		if(r>mid) ans=min(ans,ask_minn(p*2+1,l,r));
		return ans;
	}
} T1;

int find(int num)
{
	int l=1,r=cnt,mid;
	while(l<=r){
		mid=l+(r-l)/2;
		if(num<ifo[mid].x) r=mid-1;
		else l=mid+1;
	}
	return l;
}

bool cmpX(node a,node b){return a.x<b.x;}
bool cmpY(node a,node b){return a.y<b.y;}
bool cmpAsk1(nodeAsk a,nodeAsk b){return a.x==b.x ? a.flag<b.flag : a.x<b.x;}
bool cmpAsk2(nodeAsk a,nodeAsk b){return a.x==b.x ? a.flag>b.flag : a.x<b.x;}

void solve0()
{
	sort(ifo+1,ifo+1+cnt,cmpX);
	for(int i=1;i<=cnt;i++){
		ifo[0]=(node){-1,ifo[i].y};
		ifo[cnt+1]=(node){1001,ifo[i].y};
		int p=find(ifo[i].x),maxx=1001,minn=-1,flag;
		for(int j=p;j<=cnt+1;j++){
			if(ifo[j].y>=maxx || ifo[j].y<=minn) continue;
			if(minn+1>maxx-1) break;
			if(ifo[i].x+1<=ifo[j].x-1) M[++cntM]=(nodeAns){ifo[i].x+1,minn+1,ifo[j].x-1,maxx-1};
			if(ifo[j].y>ifo[i].y) maxx=min(maxx,ifo[j].y);
			else if(ifo[j].y<ifo[i].y) minn=max(minn,ifo[j].y);
			else break;
		}
		maxx=1001,minn=-1,flag=1;
		for(int j=i-1;j>=1;j--){
			if(ifo[j].x>=ifo[i].x) continue;
			if(ifo[j].y>ifo[i].y) maxx=min(maxx,ifo[j].y);
			else if(ifo[j].y<ifo[i].y) minn=max(minn,ifo[j].y);
			else{
				flag=0;
				break;
			}
			if(minn+1>maxx-1){
				flag=0;
				break;
			}
		}
		if(flag) M[++cntM]=(nodeAns){0,minn+1,ifo[i].x-1,maxx-1};
	}
	sort(ifo+1,ifo+1+cnt,cmpY);
	ifo[0]=(node){0,-1};
	ifo[cnt+1]=(node){0,1001};
	for(int i=1;i<=cnt+1;i++) if(ifo[i-1].y+1<=ifo[i].y-1) M[++cntM]=(nodeAns){0,ifo[i-1].y+1,1000,ifo[i].y-1};
	
	return ;
}

void solve1()
{
	cnt1=0;
	for(int i=1;i<=n;i++) if(ch[i]=='H') ifo1[++cnt1]=(nodeAsk){y[i],x[i],0,0,0};
	for(int i=1;i<=cntM;i++) ifo1[++cnt1]=(nodeAsk){M[i].y2,M[i].x1,M[i].x2,1,i};
	sort(ifo1+1,ifo1+1+cnt1,cmpAsk1);
	
	T1.build(1,0,1001);
	for(int i=1;i<=cnt1;i++){
		if(ifo1[i].flag==0) T1.change(1,ifo1[i].l,ifo1[i].x);
		else{
			int ans=T1.ask_maxx(1,ifo1[i].l,ifo1[i].r);
			if(ans!=INT_MIN) Ans[ifo1[i].p].y2=ans;
		}
	}
	return ;
}

void solve2()
{
	cnt1=0;
	for(int i=1;i<=n;i++) if(ch[i]=='H') ifo1[++cnt1]=(nodeAsk){x[i],y[i],0,0,0};
	for(int i=1;i<=cntM;i++) ifo1[++cnt1]=(nodeAsk){M[i].x2,M[i].y1,M[i].y2,1,i};
	sort(ifo1+1,ifo1+1+cnt1,cmpAsk1);
	
	T1.build(1,0,1001);
	for(int i=1;i<=cnt1;i++){
		if(ifo1[i].flag==0) T1.change(1,ifo1[i].l,ifo1[i].x);
		else{
			int ans=T1.ask_maxx(1,ifo1[i].l,ifo1[i].r);
			if(ans!=INT_MIN) Ans[ifo1[i].p].x2=ans;
		}
	}
	return ;
}

void solve3()
{
	cnt1=0;
	for(int i=1;i<=n;i++) if(ch[i]=='H') ifo1[++cnt1]=(nodeAsk){y[i],x[i],0,0,0};
	for(int i=1;i<=cntM;i++) ifo1[++cnt1]=(nodeAsk){M[i].y1,M[i].x1,M[i].x2,1,i};
	sort(ifo1+1,ifo1+1+cnt1,cmpAsk2);
	
	T1.build(1,0,1001);
	for(int i=cnt1;i>=1;i--){
		if(ifo1[i].flag==0) T1.change(1,ifo1[i].l,ifo1[i].x);
		else{
			int ans=T1.ask_minn(1,ifo1[i].l,ifo1[i].r);
			if(ans!=INT_MAX) Ans[ifo1[i].p].y1=ans;
		}
	}
	return ;
}

void solve4()
{
	cnt1=0;
	for(int i=1;i<=n;i++) if(ch[i]=='H') ifo1[++cnt1]=(nodeAsk){x[i],y[i],0,0,0};
	for(int i=1;i<=cntM;i++) ifo1[++cnt1]=(nodeAsk){M[i].x1,M[i].y1,M[i].y2,1,i};
	sort(ifo1+1,ifo1+1+cnt1,cmpAsk2);
	
	T1.build(1,0,1001);
	for(int i=cnt1;i>=1;i--){
		if(ifo1[i].flag==0) T1.change(1,ifo1[i].l,ifo1[i].x);
		else{
			int ans=T1.ask_minn(1,ifo1[i].l,ifo1[i].r);
			if(ans!=INT_MAX) Ans[ifo1[i].p].x1=ans;
		}
	}
	return ;
}

int main()
{
	n=_r();
	for(int i=1;i<=n;i++){
		x[i]=_r()+1,y[i]=_r()+1;
		ch[i]=_rs()[0];
		if(ch[i]=='G') ifo[++cnt]=(node){x[i],y[i]};
		else sum[x[i]][y[i]]++;
	}
	for(int i=1;i<=1000;i++) sum[i][0]+=sum[i-1][0],sum[0][i]+=sum[0][i-1];
	for(int i=1;i<=1000;i++) for(int j=1;j<=1000;j++) sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	
	solve0();
	solve1();
	solve2();
	solve3();
	solve4();
	for(int i=1;i<=cntM;i++){
		int x1=Ans[i].x1,y1=Ans[i].y1,x2=Ans[i].x2,y2=Ans[i].y2;
		if(x1<1 || y1<1 || x2>1001 || y2>1001 || x1>x2 || y1>y2) continue;
		int num=sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1],s=(y2-y1)*(x2-x1);
		if(num>ans1) ans1=num,ans2=s;
		if(num==ans1) ans2=min(ans2,s);
	}
	_w(ans1,'\n');
	_w(ans2,'\n');
	
	return 0;
}
```

---

## 作者：FJ_OIer (赞：0)

~~卡了半天（字面意思）总算过了~~

前置：离散化，双指针。

属于是思维较简单但是实现很难的那种。看到 $N \le 500$ 提示我们用 $O(N^3)$ 的算法，于是先将坐标离散化。

接着就可以暴力枚举矩形的上下界，然后在选定的上下界内双指针从左到右扫一遍，确定最小的左右界，使用二维前缀和获取矩形内 G 和 H 的数量。因为有离散化，求面积需要先把矩形的左上点和右下点的坐标恢复原状，长宽相乘即可。细节见代码。（很繁琐。。）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,cnt,S=1e9;//cnt：最大数量 S：最小面积
int x[501],y[501],a[501],b[501];
int sum[501][501],sum2[501][501];//两个二维前缀和数组，分别保存G和H的数量
char p[501];
int calc(int x,int y,int x2,int y2){
    return sum[x2][y2]-sum[x2][y-1]-sum[x-1][y2]+sum[x-1][y-1];
}
int calc2(int x,int y,int x2,int y2){
    return sum2[x2][y2]-sum2[x2][y-1]-sum2[x-1][y2]+sum2[x-1][y-1];
}
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>x[i]>>y[i]>>p[i];
        a[i]=x[i],b[i]=y[i];
    }
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    int la=unique(a+1,a+n+1)-a-1;
    int lb=unique(b+1,b+n+1)-b-1;
    for (int i=1;i<=n;i++){
        x[i]=lower_bound(a+1,a+la+1,x[i])-a;
        y[i]=lower_bound(b+1,b+lb+1,y[i])-b;
        if (p[i]=='G'){
            sum[x[i]][y[i]]=1;
        }else{
            sum2[x[i]][y[i]]=1;
        }
    }
    //离散化
    for (int i=1;i<=la;i++){
        for (int j=1;j<=lb;j++){
            sum[i][j]+=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
            sum2[i][j]+=sum2[i][j-1]+sum2[i-1][j]-sum2[i-1][j-1];
        }
    }
    //预处理前缀和
    for (int i=1;i<=la;i++){
        for (int j=i;j<=la;j++){
            for (int l=1,r=0;l<=lb;l++){//双指针
                r=max(r,l-1);
                if (calc2(i,l,j,l)==0){//为确保求得最小面积，必须保证此时第l列有H时才能对r进行扩展
                    continue;
                }
                while (r<lb&&calc(i,l,j,r+1)==0){//扩展r
                    r++;
                    int px=a[i],py=b[l],px2=a[j],py2=b[r];//恢复坐标并更新答案
                    if (calc2(i,l,j,r)==cnt){
                        S=min(S,(px2-px)*(py2-py));
                    }else if (calc2(i,l,j,r)>cnt){
                        cnt=calc2(i,l,j,r);
                        S=(px2-px)*(py2-py);
                    }
                }
            }
        }
    }
    cout<<cnt<<endl<<S;
    return 0;
}
```

---

## 作者：yqw2486 (赞：0)

看到 NewErA 题解中推荐了一篇论文，去下载下来看了看，确实值得推荐：[浅谈用极大化思想解决最大子矩形问题](https://wenku.baidu.com/view/728cd5126edb6f1aff001fbb.html)

文中提到2种算法（图片来自上述文章）：

1.枚举障碍点作为左边界，然后依次向右扫描障碍点，并不断调整上下边界，时间复杂度O(障碍点^2)，对于本题已经足够。

例如：**以障碍点1为矩形左边界**，向右遇到障碍点2，此时分割的矩形上下边界为大矩形的上下边界

![](https://cdn.luogu.com.cn/upload/image_hosting/q6vqls80.png)


继续向后扫描遇到障碍点3，因为不能包含障碍点2，因此调整下边界

![](https://cdn.luogu.com.cn/upload/image_hosting/vw5un3s8.png)

继续往后移动，不得包含障碍3，因此调整上边界（右边界呢？）：

![](https://cdn.luogu.com.cn/upload/image_hosting/3yut4mgd.png)

易错点1：最大子矩阵的边界和大矩形的边界重合

处理技巧：额外插入4个障碍点，即大矩形的右上、右下、左上、左下四个点

易错点2：此题边界上不能有障碍点，因此需要左边界从障碍点lx向右移动1个单位，右边界从障碍点rx向左移动1个单位，要保证构成的子矩阵是合理的必须有：rx-1>=lx+1，即rx-lx>=2

快速计算子矩阵包含的H点：前缀和+容斥原理

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505,M=N<<1;
struct node{
	int x,y;
	node(int a=0,int b=0):x(a),y(b){}
	bool operator<(node a)const{return x<a.x;}
};
vector<node>h,g;
int n,mx,my,ans,s=1e9,sum[M][M];
int calS(int lx,int ly,int rx,int ry){
	if(ly>ry)return 0;
	int x=mx,xx=0,y=my,yy=0;
	for(int i=0;i<h.size();i++)
		if(h[i].x>=lx&&h[i].x<=rx&&h[i].y>=ly&&h[i].y<=ry){
			x=min(x,h[i].x);
			xx=max(xx,h[i].x);
			y=min(y,h[i].y);
			yy=max(yy,h[i].y);
		}
	return (xx-x)*(yy-y);
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	char c;
	for(int i=1,x,y,t;i<=n;i++){
		cin>>x>>y>>c;x++,y++;//为了将(0,0)设置为障碍点，因此所有点右上移动 
		if(c=='H'){
			sum[x][y]=1;
			h.push_back(node(x,y));
		}
		else g.push_back(node(x,y));
		mx=max(mx,x),my=max(my,y);
	}
	mx++,my++;
	g.push_back(node(mx,my));//右上角插入障碍点 
	g.push_back(node(0,0));//左下角插入障碍点 
	g.push_back(node(0,my));//左上角插入障碍点 
	g.push_back(node(mx,0));//右下角插入障碍点 
	sort(g.begin(),g.end());
	sort(h.begin(),h.end());
	for(int x=1;x<=mx;x++)
		for(int y=1;y<=my;y++)
			sum[x][y]+=(sum[x][y-1]+sum[x-1][y]-sum[x-1][y-1]);
	for(int i=0;i<g.size();i++){//以i为左边界的矩形，不能包含i,因此左边界 
		int miny=0,maxy=my;//上下边界 
		for(int j=i+1;j<g.size();j++){//向右扫描，不断调整上下边界 
			if(g[j].x-g[i].x>=2){//矩形不含障碍，因此lx+1<=rx-1,即rx-lx>=2 
				int t=sum[g[j].x-1][maxy-1]-sum[g[j].x-1][miny]-sum[g[i].x][maxy-1]+sum[g[i].x][miny];
				int ss=calS(g[i].x+1,miny+1,g[j].x-1,maxy-1);
				if(ans<t)ans=t,s=ss;
				else if(ans==t&&s>ss)s=ss;
			}
			if(g[j].y<=g[i].y)miny=max(miny,g[j].y);
			if(g[j].y>=g[i].y)maxy=min(g[j].y,maxy);
		}
	}
	cout<<ans<<endl;
	cout<<s<<endl;
	return 0;
} 
```

2.第二种算法，~~才想起来，还没看~~


---

## 作者：pocafup (赞：0)

大佬们的题解都好高大尚，蒟蒻也来打一发

暴力什么的就算了，~~贪心他不香吗~~

这题其实如果分开想，就三种情况需要讨论：（~~由于不会发图，只能手打~~）

1）

5 . . . . .

4 . . . . .

3 . . . H .

2 . . G . . 

1 . H . . .

0 1 2 3 4 5

在这种情况下，下面两个H绝对不在一组（因为他们中有G）

2)

5 . . G . .

4 . . H . .

3 . . . H .

2 . H . . .

1 . G . . .

0 1 2 3 4 5

在这种情况下所有H都能拿，因为G在所有H之上/之下

3)

5 . . H . . 

4 . . G . .

3 . . . H .

2 . . . . H

1 . H . . .

0 1 2 3 4 5
在这种情况下下面所有H都能拿，但是上面那个连不了（被G挡住了）

因此，我们只需要对这三种情况进行判断就行了（判断方法见注释）

```cpp
pp find_pair(int aa, int bb){
  int mini = 1e8,maxi = 0;
  int low = aa, high = bb;
  while(cow[low-1].x==cow[aa].x) {low--;if (low==0)break;}
  while(cow[high-1].x==cow[bb].x) {high++; if (high == 0) break;}
  //这是一个很重要的判断：
  //因为我们在排序的时候有可能遇到x相等的点，这个点并不会被搜索，但是这个点仍然需要判断。在这个时候就需要往前和后搜索x相等的点
  for (int i=low;i<=high;i++){
    if (cow[i].id=='G'){
      if (cow[i].y>max(cow[aa].y,cow[bb].y)) mini = min(mini,cow[i].y);
      else if (cow[i].y<min(cow[aa].y,cow[bb].y)) maxi = max(maxi,cow[i].y);
      else posible = false;
    }
  }//如果这两个点中间有G就进行以下判断：
  //1.如果这个G的y坐标在这两个点的y之上，那么我们将最高值更新
  //2.如果这个G的坐标在y之下，我们将最小值之下，我们更新最小值
  //3.如果这个G在两个坐标中间，那么这两个点必然不可能选（因为无论怎么样连最后G都会在这个范围里）
  return make_pair(mini,maxi);
}
```


那么问题来了，怎么保证找的G在两个H的中间呢？

~~还用问吗，加个sort就好了~~

*注意事项：在找G的时候，我们要记住如果这个G和H的x坐标相等，在sort的时候未必会在他的范围内。那怎么办？

~~还用问吗，如果x坐标相等就减/加到他不相等为止~~
```cpp
while(cow[low-1].x==cow[aa].x) {low--;if (low==0)break;}
  while(cow[high-1].x==cow[bb].x) {high++; if (high == 0) break;}
```
找完G之后，我们对两点之间的所有H进行判断：

如果这个H在上下G的y的范围以内，那么我们更新最大/最小值。（相当于更新高）

```cpp
pp in_range(int aa, int bb, pp bo){
  int maxi = 0,mini = 1e8;
  for (int i=aa;i<=bb;i++){
    if (cow[i].id!='G'){
      if (between(bo,cow[i].y)){
        maxi = max(maxi,cow[i].y);
        mini = min(mini,cow[i].y);
        temp++;
      }
    }
  }//现在已经找出了在这个点上面最低的G点和下面最高的G点
  //我们在这个范围里面搜索所以的H，更新最高点和最低点（前提是要在G点的范围内）
  return make_pair(maxi,mini);
}
```
找完之后怎么办？

~~还用问吗，当然找面积啊~~

面积 = 底*高 = (x2-x1)*abs(y2-y1) [因为sort了，所以x2一定>=x1]

```cpp
if (temp){
        if(temp>breed){
          //如果H的数量大于之前的，直接更新
          breed = temp;
          ans = abs(res.first-res.second)*abs(cow[j].x-cow[i].x);
        }else if (temp==breed) ans = min(ans,abs(res.first-res.second)*abs(cow[j].x-cow[i].x));//否则更新面积（底『x的差』乘高『最高y值和最低y值的差』
      }
```

由于判断不需要储存，这个程序用500的空间其实就够了（800-KB应该够小了吧）

完整代码如下：

```cpp
#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;
#define pp pair<int,int>
struct node{
  int x,y;
  char id;
}cow[505];
int tot = 0, temp = 0;
int a,b,c; char d;
void add(int aa, int bb, char cc){
  cow[++tot].x = aa;
  cow[tot].y = bb;
  cow[tot].id = cc;
}
bool sorted(node aa, node bb){
  return aa.x<bb.x;
}
bool between(pp aa,int b){
  return aa.first>b && aa.second<b;
}//这个是表示一个数是否在两个数之间
bool posible = true;
pp find_pair(int aa, int bb){
  int mini = 1e8,maxi = 0;
  int low = aa, high = bb;
  while(cow[low-1].x==cow[aa].x) {low--;if (low==0)break;}
  while(cow[high-1].x==cow[bb].x) {high++; if (high == 0) break;}
  //这是一个很重要的判断：
  //因为我们在排序的时候有可能遇到x相等的点，这个点并不会被搜索，但是这个点仍然需要判断。在这个时候就需要往前和后搜索x相等的点
  for (int i=low;i<=high;i++){
    if (cow[i].id=='G'){
      if (cow[i].y>max(cow[aa].y,cow[bb].y)) mini = min(mini,cow[i].y);
      else if (cow[i].y<min(cow[aa].y,cow[bb].y)) maxi = max(maxi,cow[i].y);
      else posible = false;
    }
  }//如果这两个点中间有G就进行以下判断：
  //1.如果这个G的y坐标在这两个点的y之上，那么我们将最高值更新
  //2.如果这个G的坐标在y之下，我们将最小值之下，我们更新最小值
  //3.如果这个G在两个坐标中间，那么这两个点必然不可能选（因为无论怎么样连最后G都会在这个范围里）
  return make_pair(mini,maxi);
}
pp in_range(int aa, int bb, pp bo){
  int maxi = 0,mini = 1e8;
  for (int i=aa;i<=bb;i++){
    bool update = true;
    while(update){
      if (cow[i].id!='G'){
        if (between(bo,cow[i].y)){
          maxi = max(maxi,cow[i].y);
          mini = min(mini,cow[i].y);
          temp++;
        }
      }
    }
  }//现在已经找出了在这个点上面最低的G点和下面最高的G点
  //我们在这个范围里面搜索所以的H，更新最高点和最低点（前提是要在G点的范围内）
  return make_pair(maxi,mini);
}
int main(){
  ios::sync_with_stdio(0);
  cin >> a;
  for (int i=0;i<a;i++){
    cin >> b >> c >> d;
    add(b,c,d);
  }
  int ans = 0, breed = 1;
  sort(cow+1,cow+tot+1,sorted);
  //以上不解释
  for (int i=1;i<=a;i++){
    for (int j=i+breed;j<=a;j++){
      if (cow[i].id=='G'||cow[j].id == 'G') continue;//如果两个点中有G就不需要判断
      posible = true;
      temp = 0;
      pp bounds = find_pair(i,j);//先找G的范围
      if (!posible) continue;
      pp res = in_range(i,j,bounds);//再找H的范围
      if (temp){
        if(temp>breed){
          //如果H的数量大于之前的，直接更新
          breed = temp;
          ans = abs(res.first-res.second)*abs(cow[j].x-cow[i].x);
        }else if (temp==breed) ans = min(ans,abs(res.first-res.second)*abs(cow[j].x-cow[i].x));//否则更新面积（底『x的差』乘高『最高y值和最低y值的差』
      }
    }
  }
  cout << breed << endl << ans;
}

```

~~你抄任你抄，过得了算我输~~

---

