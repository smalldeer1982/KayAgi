# Shop

## 题目描述

Vasya plays one very well-known and extremely popular MMORPG game. His game character has $ k $ skill; currently the $ i $ -th of them equals to $ a_{i} $ . Also this game has a common rating table in which the participants are ranked according to the product of all the skills of a hero in the descending order.

Vasya decided to 'upgrade' his character via the game store. This store offers $ n $ possible ways to improve the hero's skills; Each of these ways belongs to one of three types:

1. assign the $ i $ -th skill to $ b $ ;
2. add $ b $ to the $ i $ -th skill;
3. multiply the $ i $ -th skill by $ b $ .

Unfortunately, a) every improvement can only be used once; b) the money on Vasya's card is enough only to purchase not more than $ m $ of the $ n $ improvements. Help Vasya to reach the highest ranking in the game. To do this tell Vasya which of improvements he has to purchase and in what order he should use them to make his rating become as high as possible. If there are several ways to achieve it, print any of them.

## 样例 #1

### 输入

```
2 4 3
13 20
1 1 14
1 2 30
2 1 6
3 2 2
```

### 输出

```
3
2 3 4
```

# 题解

## 作者：jiangly (赞：33)

#### 题意

给定 $k$ ($1\le k\le 10^5$) 个数 $a_1,a_2,\ldots,a_k$，有 $n$ ($1\le n\le 10^5$) 个操作，每个操作为将 $a_{j_i}$ 赋值为 / 加上 / 乘上 $b_i$。在所有操作中选最多 $m$ 个按一定顺序执行，使得所有数的乘积最大。

#### 题解

首先如果确定了执行的操作，执行顺序一定为赋值、加、乘。赋值操作只保留最大的，并可以转化为加法。每个数的加法操作按从大到小顺序排序后可以转化为乘法。最后将所有乘法操作从大到小排序选前 $m$ 个即可。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int N = 1E5;
int k, n, m;
int a[N], t[N], j[N], b[N];
pair<int, int> as[N];
vector<pair<int, int>> add[N];
vector<pair<long double, int>> mul;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> k >> n >> m;
    for (int i = 0; i < k; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i) {
        cin >> t[i] >> j[i] >> b[i];
        --j[i];
        switch (t[i]) {
            case 1:
                as[j[i]] = max(as[j[i]], make_pair(b[i], i));
                break;
            case 2:
                add[j[i]].emplace_back(b[i], i);
                break;
            case 3:
                mul.emplace_back(b[i], i);
        }
    }
    for (int i = 0; i < k; ++i)
        if (as[i].first > a[i])
            add[i].emplace_back(as[i].first - a[i], as[i].second);
    for (int i = 0; i < k; ++i) {
        sort(add[i].begin(), add[i].end(), greater<pair<int, int>>());
        LL v = a[i];
        for (const auto &p : add[i]) {
            mul.emplace_back(1.0L * (v + p.first) / v, p.second);
            v += p.first;
        }
    }
    sort(mul.begin(), mul.end(), greater<pair<long double, int>>());
    int x = min(m, (int)mul.size());
    sort(mul.begin(), mul.begin() + x, [&](const auto &lhs, const auto &rhs) {return t[lhs.second] < t[rhs.second];});
    cout << x << "\n";
    for (int i = 0; i < x; ++i)
        cout << mul[i].second + 1 << " \n"[i == x - 1];
    return 0;
}
```



---

## 作者：ww3113306 (赞：30)

[广告](https://www.cnblogs.com/ww3113306/p/10269471.html)

#### 题意：

$n$个数，有$m$个操作，形如：

1,将$x_i$​改成$val_i$​

2,将$x_i$加上$val_i$​

3,将$x_i$​乘上$val_i$

其中第$i$个操作的编号为$i$. 现在你可以从中选择最多$k$个操作(不能重复选),并按一定顺序执行，使得$\prod_{i = 1}^{n}x_i$最大。
第一行输出选择的操作个数，第二行按执行顺序输出方案。

#### 题解：

如果只有3号操作，那么因为最后的答案是乘起来，而不是加起来，因此每个乘，不管对哪个数进行操作，对ans的贡献都是相同的。所以我们可以直接按操作的值排序，贪心的取值即可。

但现在有3种操作，我们可以考虑将其转换为3号操作。

首先我们有个比较显而易见的结论：对于已经选定的$k$个操作，我们一定是先赋值，再加，再乘，即按123的操作依次进行。

我们先考虑是否可以将加法变为乘法。

基于贪心的思想，对于同一个数，我们选择加法操作，肯定是先选加得多的，因此我们将加法从高到底排序，依次操作。

那么每个加法的使用前提都是前一个加法已经被使用过了。

因此对于每个加法，它的使用前提都是固定的，即对于每个加法操作，都是把某个值为$x$的数变为一个值为$y$的数，其中$x$是这个数经过它前面的所有加法后变成的数，也就是一段前缀和。

因为每个加法使用的条件都是固定的，因此我们可以把任意一个加法看成一个$val$为$\frac{x}{y}$的乘法，于是我们就可以按照上面的方法进行贪心了。

那么如何保证这样一定合法呢？

可以知道，这样合法，当且仅当我们取的每段加法都是一段前缀，可以证明，排在后面的加法，转化为乘法后肯定也没有之前优，因此如果我们取了一个加法，那么这个加法之前的加法肯定也都取过了。

一个简单的证明：

设$a > b > c > d$,试证明前面的乘法肯定要比后面的大，即证：

$$\frac{c}{a + b} > \frac{d}{a + b + c}$$

$$c(a + b + c) > d (a + b)$$

显然成立。

又因为乘法是没有先后顺序的，因此不管我们取的加法是不是断断续续取的，反正我们可以把它调整到正确的顺序。

那么现在来考虑操作1.

首先对于任意一个数而言，最多只会进行一次操作一(因为进行多次就相当于之前的操作都无效了)。

那么我们先去掉较劣的操作1，对于每个数都只保留最大的那个(如果有的话)

可以观察到，初步筛选后，操作1实际上就相当于把原数加上一个值变为了$val_i$,因此我们可以以这个增量为新的$val_i$,把这个操作转换为加法，然后当做一个普通的加法放到操作2的数组当中去sort。

这样看上去打破了我们之前按123依次进行的约定？

其实并没有，考虑2种情况。

1，我们在取值时没有取到这个赋值操作。那么显然不会产生影响

2，我们在取值时取到了这个赋值操作，那么因为乘法可以打乱顺序，因此我们依然可以看做是在最开始进行了这个赋值操作，那么这个操作确实可以起到加上一个值的效果，并不会违背我们之前推出的性质。

简单来说，做这道题的时候注意一下几点：

1，将3个操作都转换为乘法

2，运用贪心的原则

3，记住乘法是可以随意调整顺序的。

4，因为最后求的是乘积，所以每个乘法对答案的贡献都是相同的。

#### 其中第3点非常重要，这题所有操作的正确性(包括贪心和转换部分)都是基于这个性质的！
```
#include<bits/stdc++.h>
using namespace std;
#define R register int
#define AC 101000 
#define LL long long

int n, m, k, tot1, tot2, tot3, cnt;
LL s[AC];

struct node{
    int opt, id, x;LL v, w;//w为分母
}m1[AC], m2[AC], m3[AC], ans[AC];//不需要知道具体值……所以减1再比较也不影响结果，知道哪些是我要的操作就好了

inline bool cmp1(node a, node b){return (a.x != b.x) ? (a.x < b.x) : (a.v < b.v);}//给操作1去重
inline bool cmp2(node a, node b){return (a.x != b.x) ? (a.x < b.x) : (a.v > b.v);}//上面去重所以从小到大，这里贪心所以从大到小
inline bool cmp3(node a, node b){return a.opt < b.opt;}//先1再2再3,且取走的加法是一段前缀才能保证结果正确性
inline bool cmp4(node a, node b){return a.v * b.w > a.w * b.v;}//分数比较

inline int read()
{
    int x = 0;char c = getchar();
    while(c > '9' || c < '0') c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}

void pre()
{
    n = read(), m = read(), k = read();
    for(R i = 1; i <= n; i ++) s[i] = read();
    for(R i = 1; i <= m; i ++)
    {
        int a = read(), b = read(), c = read();
        if(a == 1 && c > s[b]) m1[++ tot1] = (node){1, i, b, c, 1};//如果改了反而不优就算了
        else if(a == 2) m2[++ tot2] = (node){2, i, b, c, 1};
        else if(a == 3) m3[++ tot3] = (node){3, i, b, c, 1};//默认分母为1
    }
}

void build()
{
    sort(m1 + 1, m1 + tot1 + 1, cmp1);	
    int tmp = 0;
    for(R i = 1; i <= tot1; i ++)
        if(m1[i].x != m1[i + 1].x) m1[++ tmp] = m1[i];//对于同一个数的赋值操作只保留最大的,否则影响贪心正确性
    tot1 = tmp;
    for(R i = 1; i <= tot1; i ++) 
        m1[i].v = m1[i].v - s[m1[i].x], m2[++ tot2] = m1[i];//把赋值变成加法后加入m2中
    sort(m2 + 1, m2 + tot2 + 1, cmp2);//因为要每个数单独看，所以还是要先按数排序，再按大小排序
    LL sum = 0;
    for(R i = 1; i <= tot2; i ++) 
    {
        if(m2[i].x != m2[i - 1].x) sum = s[m2[i].x];//对于新的一段就重置一下
        m2[i].w = sum, sum += m2[i].v;//v不用修改，因为统一-1了，所以分子要-sum
    }	
    for(R i = 1; i <= tot3; i ++) m3[i].v --;//统一-1不会影响比较结果
    for(R i = 1; i <= tot2; i ++) m3[++ tot3] = m2[i];
}

void work()
{
    sort(m3 + 1, m3 + tot3 + 1, cmp4);
    int tmp = min(tot3, k);
    for(R i = 1; i <= tmp; i ++) ans[++ cnt] = m3[i];	
    printf("%d\n", cnt);
    sort(ans + 1, ans + cnt + 1, cmp3);
    for(R i = 1; i <= cnt; i ++) printf("%d ", ans[i].id);
    printf("\n");
}

int main()
{
    //freopen("in.in", "r", stdin);
    pre();
    build();
    work();
//	fclose(stdin);
    return 0;
}
```

---

## 作者：Kinandra (赞：6)

标签:贪心

#### Part 1

容易发现, 必定存在一种最优方案, 使得每个位置至多**赋值**一次, 并且每个位置先执行**赋值**, 后执行**加法**, 最后执行**乘法**. 我们不妨构造这种最优方案.

首先如果所有操作都是**乘法**那就十分简单, 因为**乘法**的对答案的贡献与其作用的位置无关, 按 $b$ 由大至小排序即可.

#### Part 2

**加法**看起来似乎不是很好做.

假设不存在**赋值**, 那么每个位置的执行的**加法**必然是 $b$ 最大的几个. 如果我们由大至小依次执行这些**加法**, 每个**加法**执行前后当前位置的值就是已知的了(前记为 $t$, 后记为 $s$), 那么**加法**可以转化为一个 $s/t$ 的**乘法**.

#### Part 3

由于**赋值**在最先进行, 那么可以转化为**加法**, 进而转化为**乘法**.

需要注意的是**赋值**操作不能直接转化成**乘法**, 因为**赋值**的执行与否对**加法**的执行前后的指是有影响的, 我们需要先转化成**加法**就可以巧妙化解了.

时间复杂度 $\mathcal O(n\log n)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int K, n, m;
int a[200005];

struct P {
    double x;
    int i, op;
} mx[200005];
bool cmp(P a, P b) { return a.x > b.x; }
vector<P> v1[200005], v2;
vector<int> res[3];

int main() {
    K = read(), n = read(), m = read();
    for (int i = 1; i <= K; ++i) a[i] = mx[i].x = read();
    for (int i = 1, op, p, b; i <= n; ++i) {
        op = read(), p = read(), b = read();
        if (op == 1) (b > mx[p].x) ? mx[p] = (P){b, i, 0} : mx[p];
        if (op == 2) v1[p].push_back((P){b, i, 1});
        if (op == 3) v2.push_back((P){b, i, 2});
    }

    for (int i = 1; i <= K; ++i) {
        if (mx[i].i) v1[i].push_back((P){mx[i].x - a[i], mx[i].i});
        sort(v1[i].begin(), v1[i].end(), cmp);
        double s, t = a[i];
        for (vector<P>::iterator p = v1[i].begin(); p != v1[i].end(); ++p)
            s = t + p->x, p->x = s / t, v2.push_back(*p), t = s;
    }

    sort(v2.begin(), v2.end(), cmp), m = min(m, (int)v2.size());
    printf("%d\n", m);
    for (int i = 0; i < m; ++i) res[v2[i].op].push_back(v2[i].i);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < res[i].size(); ++j) printf("%d ", res[i][j]);
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```

---

## 作者：yeaDonaby (赞：4)

$Part 1$:暴力（$40-100$分）

暴力枚举所有情况，取排序后字典序最小的合法解即可。

$Part 2$:理性分析：（$0-100$分）

如果只有$ty=3$，那么因为最后的答案是乘起来，而不是加起来，因此每个乘，不管对哪个数进行操作，对$ans$的贡献都是相同的。所以我们可以直接按操作的值排序，贪心的取值即可。

首先我们有个比较显而易见的结论：对于已经选定的$k$个操作，我们一定是先赋值先进行$ty=1$，再加$ty=2$的，再乘$ty=3$的，即按$123$的操作依次进行。

对于一个位置，$ty=1$的显然至多进行一次，选的一定是最大的值。因此可以将$ty=1$的情况转成$ty=2$的情况。

同样，对于一个位置$x$，我们将位于这个位置的值从大到小排序。假设有$l$个数，我们将他们记为$w1,w2,w3……,wl$。假设这个位置进行了$1$次$ty=2$的，那么$Ax$一定变为$(Ax+w1)$，等价于乘上$(Ax+w1)/Ax$。以此类推，记$Si=w1+w2+……+wi$，第$i$个$ty=2$的可以转化为值为$(Ax+Si)/(Ax+Si-1)$的$ty=3$的。

现在所有的都为$ty=3$，就可以做了。

注意：
### 按**执行**顺序输出方案

所以记录$t$y值按字典序输出。

贴一波~~伪~~代码：
```
#include<stdio.h>
#include<vector>
#include<algorithm>
#define R register
#define I inline
#define ll long long
#define pianitr pair<int,int>
using namespace std;
const int maxn=(1<<19)|1;
int n,k,m,ty,x,y;
int a[maxn],nidgd[maxn],mid[maxn];
struct node
{
	ll l,r;
	int id;
};
vector<int> ans;
vector<node> cmp;
vector<pianitr > t2[maxn];
I bool operator<(node a,node b)
{
	ll res=a.l*b.r-b.l*a.r;
	return res==0?a.id<b.id:res>0;
}
I bool cmp1(pianitr a,pianitr b)
{
	return a.first==b.first?a.second<b.second:a.first>b.first;
}
int main(void)
{
	scanf("%d%d%d",&n,&k,&m);
	for(R int i=1; i<=n; i++)
	{
		scanf("%d",&a[i]);
		nidgd[i]=a[i];
	}
	for(R int i=1; i<=k; i++)
	{
		scanf("%d%d%d",&ty,&x,&y);
		if(ty==1)
		{
			if(y>nidgd[x])
			{
				nidgd[x]=y;
				mid[x]=i;
			}
		}
		else if(ty==2)
		{
			t2[x].push_back(make_pair(y,i));
		}
		else if(y!=1)
		{
			cmp.push_back((node)
			{
				y-1,1,i
			});
		}
	}
	for(R int i=1; i<=n; i++)
	{
		if(nidgd[i]>a[i])
		{
			t2[i].push_back(make_pair(nidgd[i]-a[i],mid[i]));
		}
	}
	for(R int i=1; i<=n; i++)
	{
		ll v=a[i];
		int kkk=(int)t2[i].size();
		sort(t2[i].begin(),t2[i].end(),cmp1);
		for(R int guoguo=0; guoguo<kkk; guoguo++)
		{
			pianitr p=t2[i][guoguo];
			cmp.push_back((node)
			{
				p.first,v,p.second
			});
			v+=1LL*p.first;
		}
	}
	sort(cmp.begin(),cmp.end());
	int GG=(int)cmp.size();
	GG=GG<m?GG:m;
	for(R int i=0; i<GG; i++)
	{
		ans.push_back(cmp[i].id);
	}
	sort(ans.begin(),ans.end());
	int ANSWER=(int)ans.size();
	printf("%d\n",ANSWER);
	for(R int i=0; i<ANSWER; i++)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}
```
$vector$有点丑，但挺好用大~。

---

## 作者：Alkaid_Star (赞：4)

### [博客食用更佳QvQ](https://www.luogu.com.cn/blog/AlwaysOnTheWay/cf521d-tan-xin-ti-xie)
## 题面：
>
有 $k$ 个整数 $a_1,a_2,\dots,a_k$ ， $n$ 个操作，格式为 $opt,i,val$ ， $opt$ 是操作类型，可能为1、2、3，分别代表将 $a_i$ 赋值为 $val$ ，将 $a_i$ 加上 $val$ ，将 $a_i$  乘以 $val$ 。现在要从这 $n$ 个操作里选 $m$ 个，要使$\prod \limits_{i=0}^na_i$最大。
$k,n \le 10^5$,
$0 \le m \le n$.
>

## 分析：
题外话：看了@ww3113306大佬的题解才想出来的，所以题解可能跟他的有所相似，见谅$QvQ$

一下子考虑3种操作，很难再短时间内想到解法（~~也可能是我太菜了~~）

我们从简单的开始，如果只有3号操作，那么因为乘法满足结合律，因此答案与每次操作的对象无关。所以我们可以直接按操作的乘法的值排序从大到小取就可以了。

然后考虑把加法变成乘法。同样，我们从大到小进行排序取值。我们可以把任意一个加法看成一个$val$为$\frac{x}{y}$ 的乘法。

然后再看赋值，在前面两点想清楚的情况下赋值也挺好想了：在 $val$ 大于 $a_i$ 大的情况下，我们把它看成 $val$ 为 $val-a_i$ 的加法， $val$ 小于等于 $a_i$ 的情况下肯定是不取的。

上述思路可以用多个$vector$实现。

## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200010;

int n,m,k,op,sum;
long long x,y;
long long a[N],Rec[N];
pair<long long,int> vec1[N];
vector< pair<long long,int> > vec2[N],vec3;
priority_queue< pair<long double,int> >Q;
vector<int> ans;

inline int read(){
    int x=0,f=1;
	char ch=getchar();
    while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
    while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}

inline void Print(){		//输出部分 
	for (int i=1;i<=k;i++){
		for (int j=0;j<=Rec[i]-1;j++)
			if (vec2[i][j].second<0) ans.push_back(-vec2[i][j].second);
		for (int j=0;j<=Rec[i]-1;j++)
			if (vec2[i][j].second>0) ans.push_back(vec2[i][j].second);
	}
	while (!vec3.empty()){		//把所有操作转化为乘法后统计答案 
		ans.push_back(vec3.back().second);
		vec3.pop_back();
	}
	printf("%d\n",ans.size());
	for (vector<int>::iterator it=ans.begin();it!=ans.end();it++)
		printf("%d ",*it);
	printf("\n");
}

signed main(){
	//freopen("CF521D.in","r",stdin);
	//freopen("CF521D.out","w",stdout);
	k=read(),n=read(),m=read();
	for (int i=1;i<=k;i++)
		a[i]=read();
	for (int i=1;i<=n;i++){
		op=read(),x=read(),y=read();
		if (op==1) vec1[x]=max(vec1[x],make_pair(y,i));
		if (op==2) vec2[x].push_back(make_pair(y,i));
		if (op==3) vec3.push_back(make_pair(y,i));
		//根据操作的类别放入不同的vector中 
	}
	for (int i=1;i<=k;i++){
		if (vec1[i].first>a[i]) vec2[i].push_back(make_pair(vec1[i].first-a[i],-vec1[i].second));
		//如果赋值操作后的值比原来的大，就把它转化成加法操作
		sort(vec2[i].begin(),vec2[i].end(),greater< pair<long long,int> >());//从大到小排序
		sum+=vec2[i].size();
	}
	sort(vec3.begin(),vec3.end(),greater< pair<long long,int> >());
	while (vec3.size()>m) vec3.pop_back();	//把m之后的较劣操作去掉
	if (sum+vec3.size()<=m){		//加法和乘法加起来不到m，全部选取 
		for (int i=1;i<=k;i++)
			Rec[i]=vec2[i].size();
		Print();
		return 0;
	}
	for (int i=1;i<=k;i++){
		if (Rec[i]<vec2[i].size())
			Q.push(make_pair(1.0L*vec2[i][Rec[i]++].first/a[i],i));
		//把加法转化为乘法 
	}
	for (int i=vec3.size();i<=m-1;i++){
		int x=Q.top().second;
		Q.pop();
		a[x]+=vec2[x][Rec[x]-1].first;
		if (Rec[x]<vec2[x].size())
			Q.push(make_pair(1.0L*vec2[x][Rec[x]++].first/a[x],x));
		//把加法转化为乘法
	}
	while (!vec3.empty()){
		int x=Q.top().second;
		long long val1=vec2[x][Rec[x]-1].first;
		long long val2=vec3.back().first;
		if (val1<=a[x]*(val2-1)) break;
		Q.pop();
		vec3.pop_back(),a[x]+=val1;
		if (Rec[x]<vec2[x].size())
			Q.push(make_pair(1.0L*vec2[x][Rec[x]++].first/a[x],x));
	} 
	while (!Q.empty()){
		int x=Q.top().second;
		Q.pop();
		Rec[x]--;
	}
	Print();
	return 0;
}
```


---

## 作者：xht (赞：3)

> [CF521D Shop](https://codeforces.com/contest/521/problem/D)

## 题意

- 有 $k$ 个正整数 $a_{1\dots k}$。
- 有 $n$ 个操作，每个操作给定正整数 $b$，有三种可能：将 $a_i$ 赋值为 $b$，将 $a_i$ 加上 $b$，将 $a_i$ 乘以 $b$。
- 你可以从 $n$ 个操作中选择最多 $m$ 个操作，并按照一定顺序执行。
- 你的目标是最大化 $\prod_{i=1}^k a_i$ 的值。
- $k,n \le 10^5$。

## 题解

首先赋值可以转化成加法，只是要注意赋值必须在加法之前。

其次加法可以转化成乘法，不过必须按照从大到小贪心的转化，且加法也要在乘法之前。

对于加法转乘法，有一个麻烦一点的等价方法是，同样对每个数从大到小贪心的选择，只不过动态维护。

一开始假设所有乘法操作都要选，如果乘法操作的个数多于 $m$ 个，则去掉多出来贡献最小的。

对 $k$ 个数上的加法操作进行排序，我们要从大到小贪心的选择，可以用 $k$ 个指针维护。

用一个堆，每次取出贡献最大的加法操作，然后与贡献最小的乘法操作相比较。若加法操作的贡献更大，则去掉这个贡献最小的乘法操作，同时加入贡献最大的加法操作；否则说明此时达到最优解。

若 $n,m,k$ 同阶，则总时间复杂度为 $\mathcal O(n \log n)$。

## 代码

```cpp
const int N = 1e5 + 7;
int n, m, k, s;
ui t[N];
ll a[N], b;
pair <ll, int> v1[N];
vector <pair <ll, int> > v2[N], v3;
pq <pair <ld, int> > q;
vi ans;

inline void print() {
	for (int i = 1; i <= k; i++) {
		for (ui j = 0; j < t[i]; j++)
			if (v2[i][j].se < 0) ans.pb(-v2[i][j].se);
		for (ui j = 0; j < t[i]; j++)
			if (v2[i][j].se > 0) ans.pb(v2[i][j].se);
	}
	while (v3.size()) ans.pb(v3.back().se), v3.pop_back();
	print(ans.size());
	for (auto x : ans) print(x, ' ');
}

inline void get(int x) {
	if (t[x] < v2[x].size())
		q.push(mp(1.0L * v2[x][t[x]++].fi / a[x], x));
}

int main() {
	rd(k), rd(n), rd(m);
	for (int i = 1; i <= k; i++) rd(a[i]);
	for (int i = 1, o, x; i <= n; i++) {
		rd(o), rd(x), rd(b);
		if (o == 1) v1[x] = max(v1[x], mp(b, i));
		if (o == 2) v2[x].pb(mp(b, i));
		if (o == 3) v3.pb(mp(b, i));
	}
	for (int i = 1; i <= k; i++) {
		if (v1[i].fi > a[i])
			v2[i].pb(mp(v1[i].fi - a[i], -v1[i].se));
		sort(v2[i].begin(), v2[i].end());
		reverse(v2[i].begin(), v2[i].end());
		s += v2[i].size();
	}
	sort(v3.begin(), v3.end());
	reverse(v3.begin(), v3.end());
	while ((int)v3.size() > m) v3.pop_back();
	if (s + (int)v3.size() <= m) {
		for (int i = 1; i <= k; i++) t[i] = v2[i].size();
		return print(), 0;
	}
	for (int i = 1; i <= k; i++) get(i);
	for (int i = v3.size(); i < m; i++) {
		int x = q.top().se;
		q.pop(), a[x] += v2[x][t[x]-1].fi, get(x);
	}
	while (v3.size()) {
		int x = q.top().se;
		ll b1 = v2[x][t[x]-1].fi, b2 = v3.back().fi;
		if (b1 <= a[x] * (b2 - 1)) break;
		q.pop(), v3.pop_back(), a[x] += b1, get(x);
	}
	while (q.size()) {
		int x = q.top().se;
		q.pop(), --t[x];
	}
	return print(), 0;
}
```

---

## 作者：81179332_ (赞：2)

首先，我们的赋值操作一定是要放在最开始进行的，因为加完或乘完再赋值就相当于只进行了赋值

对于每一个位置，我们只进行一次赋值，因为赋值两次相当于一次赋值

加法一定在乘法前，设初始值为 $x$，加的值为 $a$，乘的值为 $b$。如果先加后乘，$ans=(x+a)\times b=xb+ab$；如果先乘后加，$ans=xb+a$，由于 $b\ge 1$，则显然前者更优

容易发现，对于赋值操作，我们对于每一个位置都保留最大值，如果最大值比原数大，那么我们可以将其视为一个加 ”最大值-原数“ 的加法操作

以上，我们将赋值操作转换为了加法操作，下面，我们尝试将加法操作转换为乘法操作：$a+b\Leftrightarrow a\times\dfrac{a+b}a$

最后我们将原有的乘法操作和转换来的乘法操作一起从大到小排序，取前 $m$ 大即可，输出的时候记得按照先赋值、再加法、最后乘法的顺序排个序

```cpp
//timeused:40 min
const int N = 100010;
struct modify
{
	double x;int id;
	friend bool operator < (modify u,modify v) { return u.x > v.x; }
}c[N];
int n,m,k,a[N],op[N];
vector<modify> add[N],mul;
int ans[N];

int main()
{
	freopen("random.in","r",stdin);
	freopen("sol.out","w",stdout);
	n = read(),m = read(),k = read();
	for(int i = 1;i <= n;i++) a[i] = read();
	for(int i = 1;i <= m;i++)
	{
		op[i] = read();int x = read(),y = read();
		if(op[i] == 1) c[x] = min(c[x],{y,i});
		if(op[i] == 2) add[x].push_back({y,i});
		if(op[i] == 3) mul.push_back({y,i});
	}
	for(int i = 1;i <= n;i++) if(c[i].x > a[i]) add[i].push_back({c[i].x - a[i],c[i].id});
	for(int i = 1;i <= n;i++)
	{
		sort(add[i].begin(),add[i].end());
		ll num = a[i];
		for(auto j:add[i])
			mul.push_back({(num + j.x) / num,j.id}),num += j.x;
	}
	sort(mul.begin(),mul.end());
	fprint(k = min((int)mul.size(),k));
	for(int i = 0;i < k;i++) ans[i] = mul[i].id;
	sort(ans,ans + k,[&](int u,int v) { return op[u] < op[v]; });
	for(int i = 0;i < k;i++) pprint(ans[i]);
}
```

---

## 作者：ShuYuMo (赞：2)

[MyBlog](https://shuyumo2003.github.io/2020/%E3%80%8C%E9%A2%98%E5%8D%95%E3%80%8DIOI2020%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F%E4%BD%9C%E4%B8%9A-Part-1/#CF521D-Shop)
# CF521D Shop
- 有 $k$ 个正整数 $a_{1\dots k}$。
- 有 $n$ 个操作，每个操作给定正整数 $b$，有三种可能：将 $a_i$ 赋值为 $b$，将 $a_i$ 加上 $b$，将 $a_i$ 乘以 $b$。
- 你可以从 $n$ 个操作中选择最多 $m$ 个操作，并按照一定顺序执行。
- 你的目标是最大化 $\prod_{i=1}^k a_i$ 的值。
- $k,n \le 10^5$。

化归思想，考虑如果只有乘法，那一定是把操作数字从大到小排序，然后以此操作。

考虑操作顺序，最优的操作一定是先赋值，再加法，最后乘法。其中赋值只可能选相应位置最大的赋值，加法也是从大到小考虑。

显然赋值可以直接转化成加法，而加法如果从大到小考虑也可以直接转化成乘法（乘一个实数）。

这样就把所有操作转化成了乘法。 贪心考虑即可。

最后输出有顺序，应按照上面的策略（先赋值，再加法，最后乘法）以此输出（操作顺序）。

## code
{% note info CF521D Shop %}
```cpp
#include <climits>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int _ = 1e5 + 100;
#define LL long long
int read() { int x; scanf("%d", &x); return x; }
int n, m, k;
int v[_];
pair<int, int> Give[_];
vector<pair<int, int > > add[_];
vector<pair<double, int> > mul[_];
vector<pair<double, int> > All;
int T[_];
int id[_];
#define double long double
bool ICMP  (const pair<int, int> & x, const pair<int, int> & y) { return (x > y); }
bool ICMP_D(const pair<double, int> & x, const pair<double, int> & y) { return (x > y); }
bool MAGIC(const int &x, const int &y) { return T[x] < T[y]; }
int main(){
	k = read(), n = read(), m = read();
	for(int i = 1; i <= k; i++) v[i] = read();

	for(int i = 1; i <= n; i++){
		int type = read(); T[i] = type;
		int a = read(), b = read();
		if(type == 1){
			Give[a] = max(Give[a], make_pair(b, i)); 
		} else if(type == 2){
			add[a].push_back(make_pair(b, i));
		} else {
			mul[a].push_back(make_pair((double)(b), i));
		}
	}
	for(int i = 1; i <= k; i++)
		if(Give[i].first)
			add[i].push_back(make_pair(Give[i].first - v[i], Give[i].second));
	for(int i = 1; i <= k; i++) sort(add[i].begin(), add[i].end(), ICMP);
	for(int i = 1; i <= k; i++){
		LL now = v[i];
		for(int j = 0; j < add[i].size(); j++){
			mul[i].push_back( 
				make_pair( 
					(double)(now +0ll+ add[i][j].first) / (double)(now),
					add[i][j].second
				) 
			); now += add[i][j].first;
		}
	}
	for(int i = 1; i <= k; i++) for(int j = 0; j < mul[i].size(); j++) All.push_back(mul[i][j]);
	sort(All.begin(), All.end(), ICMP_D);
	int tot = 0;
	for(int i = 0; i < All.size(); i++) if(All[i].first > 1) { tot++; }
	tot = min(tot, m);
	for(int i = 1; i <= tot; i++) id[i] = All[i - 1].second;
	sort(id + 1, id + 1 + tot, MAGIC);	printf("%d\n", tot);
	for(int i = 1; i <= tot; i++) printf("%d%c", id[i], " \n"[i == n]);
	return 0;
}
```
{% endnote %}


---

## 作者：VenusM1nT (赞：2)

先来考虑 1 操作，即赋值操作，发现一定是在操作序列的最前面，且每个数只能进行一次，否则会使之前的操作失效。  
其次，3 操作，即乘操作一定放在最后面，这样才能使 2 操作，即加操作的贡献最大化。  
接下来考虑怎么计算贡献，最简单的无非是 3 乘操作，因此考虑把另外两个也表现成 乘 的形式。那么对于操作 $(\text{opt},i,\text{val})$，若 $\text{opt}=3$，那么对应的贡献 $+\text{val}$；若 $\text{opt}=2$，那么对应的贡献 $+\frac{a_i+\text{sum}+\text{val}}{a_i+\text{sum}}$，其中 $\text{sum}$ 为先前进行的所有 2 操作的 $\text{val}$ 之和；若 $\text{opt}=1$，则选取其中 $\text{val}$ 最大的一个，将其转换为 2 操作，再进行操作（这一步可以在预处理时完成）。最终答案序列以 $1\to 2\to 3$ 的方式输出，保证取值最大。  
代码挂了，咕了。

---

## 作者：StudyingFather (赞：2)

如果只有乘法操作的话，做法是显然的。

现在还多了加法和赋值操作，就稍微显得麻烦了一些。

首先有两个显然的结论：

1. 三种操作的执行顺序是：先赋值，后加法，最后乘法。
2. 一个数最多被赋值一次（赋值两次闲得无聊？）。

接下来我们考虑减少操作种类。

有了赋值在加法之前的前提，我们就可以将赋值操作转变为加法操作。

现在我们只剩下加法和乘法两个操作了。

我们对于每个数，将其加法操作按降序排序（显然先加大的更划算），接下来将这些加法操作转变为乘法操作即可（和上面一样，转变的前提是加法一定在乘法之前）。

现在我们只剩下乘法操作了，这道题就容易解决了。

```cpp
// Problem : D. Shop
// Contest : Codeforces - Codeforces Round #295 (Div. 1)
// URL : https://codeforces.com/contest/521/problem/D
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
typedef pair<double,int> pdi;
pii as[100005];
vector<pii> add[100005];
vector<pdi> mul;
vector<int> ans;
int a[100005],op[100005];
bool cmp(int x,int y)
{
 return op[x]<op[y];
}
int main()
{
 int k,n,m;
 cin>>k>>n>>m;
 for(int i=1;i<=k;i++)
  cin>>a[i];
 for(int i=1;i<=n;i++)
 {
  int x,y;
  cin>>op[i]>>x>>y;
  if(op[i]==1)as[x]=max(as[x],make_pair(y,i));
  if(op[i]==2)add[x].emplace_back(y,i);
  if(op[i]==3)mul.emplace_back(y,i);
 }
 for(int i=1;i<=k;i++)
  if(as[i].first>a[i])
   add[i].emplace_back(as[i].first-a[i],as[i].second);
 for(int i=1;i<=k;i++)
 {
  sort(add[i].begin(),add[i].end(),greater<pii>());
  long long num=a[i];
  for(auto p:add[i])
  {
   mul.emplace_back(1.0*(num+p.first)/num,p.second);
   num+=p.first;
  }
 }
 sort(mul.begin(),mul.end(),greater<pdi>());
 m=min((int)mul.size(),m);
 cout<<m<<endl;
 for(int i=0;i<m;i++)
  ans.push_back(mul[i].second);
 sort(ans.begin(),ans.end(),cmp);
 for(auto x:ans)
  cout<<x<<' ';
 return 0;
}
```

---

