# Lipshitz Sequence

## 题目描述

**【题目翻译】**

对于一个序列 $v_{1...n}$，当 $1\leq x<y\leq n$ 且 $x,y$ 均为整数时，同样满足$|v_x-v_y|\leq K\times |x-y|$，则称 $K$ 的最小整数值为序列 $v$ 的 Lipschitz 常数。现在给你一个长度为 $n$ 的序列 $v$ 并给出 $q$ 个询问，对于每对询问 $[l,r]$， 你需要求出 $v_{l...r}$ 的所有连续子序列（子段）$v_{x,y}(l\leq x<y\leq r)$ 的 Lipschitz 常数之和。

## 样例 #1

### 输入

```
10 4
1 5 2 9 1 3 4 2 1 7
2 4
3 8
7 10
1 9
```

### 输出

```
17
82
23
210
```

## 样例 #2

### 输入

```
7 6
5 7 7 4 6 6 2
1 2
2 3
2 6
1 7
4 7
3 5
```

### 输出

```
2
0
22
59
16
8
```

# 题解

## 作者：Algha_Porthos (赞：10)

Orz \_Wallace_!

让我重新翻译一次题面吧。

![pic1](http://47.103.204.220/picture_bed/uploads/2020/02/$HO2J7_XGZZI1KRTLE~HB_J.png)

来自[这个博客](https://blog.csdn.net/qaq__qaq/article/details/53116479)，侵权删除。

那么我们发现，我们要斜率的绝对值最大化。

对于相邻两者斜率相同的情况，直接带入就OK，问题不大。

对于相邻两者斜率不同的情况，我们来手模一下几种情况。

![pic2](http://47.103.204.220/picture_bed/uploads/2020/02/CF601B2.png)

我们发现黑线的斜率都比不过红线或者绿线的斜率的绝对值！

其实也好性感理解，**因为两者斜率不一样**，一定存在斜率小的那个把斜率大的那个**稀释**掉了。

得到关键条件：

## 一个区间的斜率最大值一定是（相邻两者的斜率）最大值。

那么我们预处理出每一个斜率的最大值就OK了。

对于q个请求，使用单调栈的“靠山”模型来解决。

![pic1](http://47.103.204.220/picture_bed/uploads/2020/02/CF817D1.png)

假如每个竖的线段的高度代表每一组相邻斜率，我们当前要求斜率的最大值的总和。那么我们需要考虑红的和绿的分别会作为哪些区间的最大值。

红：(2,2)

绿：(2,4)(3,4)(4,4)(2,5)(3,5)(4,5)

我们发现，作为区间最大值的区间数量其实就是

到左边“靠山”的距离  乘上  到右边的“靠山”的距离。

![pic2](http://47.103.204.220/picture_bed/uploads/2020/02/CF817D2.png)

然后就好啦。

单调栈扫一遍。

需要注意的是，如果所有元素都遍历完了，还有元素在单调栈里，我们需要在$n+1$的位置放一个“巨型靠山”，否则会出错。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105005;
int n,q,v[N],b[N];
int st[N],Right[N],Left[N],top,pos[N];
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;++i)
		scanf("%lld",&v[i]);
	for(int i=1;i<=n-1;++i)
		b[i]=abs(v[i+1]-v[i]);
	for(int _=1,l,r,ans=0;_<=q;++_){
		memset(Left,0,sizeof(Left));
		memset(Right,0,sizeof(Right));
		scanf("%lld%lld",&l,&r);
		r--;//由于是线段变区间，所以要-1 
		ans=0;
		for(int i=l,j=1;i<=r;++i,++j)//把[l,r]变成[1,nn],方便操作 
			b[j]=abs(v[i+1]-v[i]);
		int nn=r-l+1;
		for(int i=1;i<=nn;++i){
			while(top!=0&&st[top]<b[i]){//维护单调栈递减。st[]表示单调栈，存放元素的具体数值。top表示顶指针。  
				Right[pos[top]]=i-pos[top];//Right[]是右边的靠山。
				top--;
			}
			Left[i]=i-pos[top];//Left[]是左边的靠山。
			st[++top]=b[i];
			pos[top]=i;
		}
		while(top)//栈内剩余元素处理（巨型靠山）
			Right[pos[top]]=nn+1-pos[top],top--;
		for(int i=1;i<=nn;++i)//计算贡献 
			ans+=(b[i]*(Left[i])*(Right[i]));
		cout<<ans<<endl;
	}
}
```

## 后记

我运用了一点昨天写的[CF817D的题解](https://53058.blog.luogu.org/solution-cf817d)的图片和代码，请管理员不要误伤。

感谢洛谷提供评测和博客服务。

感谢ISP项目组提供私人图床服务。

---

## 作者：Deamer (赞：1)

## 题意：

$m$ 个询问，对于每个询问 $[l,r]$ ，你需要求出 $[l,r]$ 所有子段的区间斜率最大值之和。

## 分析：

显然对于每个询问我们暴力枚举子串太慢了，我们考虑区间斜率最大值的特点。

我一开始做这个题的时候，看了眼样例解释，便胡了一个结论是区间斜率最大值为区间内相邻两个数斜率的最大值，然后简单证了一下：

假设区间内相邻两个数斜率的最大值为 $x$，那么对于其他的解，我们可以拆成若干个相邻的斜率拼在一起，我们想让这个解不劣于 $x$，就必须让这些相邻斜率都大于等于 $x$，但是这些相邻的斜率一定小于等于 $x$，那么这个解肯定不比 $x$ 优，可以看做这个解被比 $x$ 小的相邻斜率给稀释了。证毕。

那么问题被我们转化为了询问区间所有子段的最大值之和，很典的一个套路就是我们考虑一个相邻斜率对哪些区间有贡献。

显然它贡献的区间左边界为左边第一个大于这个值的位置，右边界同理，这个东西的经典做法是单调栈。

所以我们对于每个询问 $[l,r]$ 我们可以用单调栈维护出 $[l,r]$ 每个位置贡献的左右边界，再把贡献加在一起就行。

- 记得开 ```long long ```。

- 边界处理要注意，而且想清楚左右边界在哪里，注意一些在区间内找不到左右比它大的情况。

 _~~**readers : Talk is cheap , show me the code !!!**~~_ 
 
#  Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int N=1e5+10;
int n,m;
int a[N];
int b[N];
int top;
int sta[N][2],L[N],R[N];
ll ans;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=abs(a[i]-a[i-1]);						//记得 abs 
	}
	int l,r;
	for(int i=1;i<=m;i++){
		ans=0;
		scanf("%d%d",&l,&r);
		l++;										//由于b[i]=a[i]-a[i-1]，所以 l 要 +1  
		for(int j=l;j<=r;j++){
			while(top && sta[top][0]<b[j]){
				R[sta[top][1]]=j-sta[top][1];
				top--;
			}
			if(top) L[j]=j-sta[top][1];
			else L[j]=j-l+1;						//注意栈空时的边界，区间内没左边有比它大的值，所以左边界为 l  
			sta[++top][0]=b[j]; sta[top][1]=j;
		}
		while(top){
			R[sta[top][1]]=r-sta[top][1]+1;			//注意没有出栈元素的边界，区间内右边没有比它大的值，所以右边界为 r  
			top--;
		}
		for(int j=l;j<=r;j++) ans+=(ll)b[j]*L[j]*R[j];	//记得 long long  
		printf("%lld\n",ans);
	}
	return 0;
}
```
这是本人独立想出的一道蓝，便写了一篇题解，如有错误请在评论区指出，谢谢啦！

[完结撒花！！！](https://www.luogu.com.cn/record/119207989)


---

## 作者：Areka6219 (赞：1)

## 题意

给出一个序列，多组询问，需要找出区间 $[l,r]$ 的子段 $K$ 值的和。

$K$ 值的定义是：对于区间 $[l,r]$ 序列上最大的斜率（还不明白的话接着看）。

## 分析

这题是个好题，是机房模拟赛时候考到的，需要对斜率有一个大致的了解。

- 首先通过对式子进行移项可以发现：原始式子变成了 $\frac{\lvert a_x-a_y \rvert}{ \lvert{x-y}\rvert } \le K$，这个和斜率的式子很像对吧。
- 那么这个题就是在让我们求最大斜率之和，但是如果直接枚举的话复杂度会变为 $O(qn^4)$，很不可接受。
- 接下来我们考虑证明一个东西：任意两点的割线斜率肯定没有切线斜率大（这里其实不严谨，因为切线的定义是两点无限趋近，但是在数列上两点只能差一），也就是说，若有两点 $x, y$，另有一点 $z$，那么 $\frac{\lvert{a_x-a_y}\rvert}{\lvert{x-y}\rvert} \le \lvert{a_z-a_{z+1}}\rvert$。
- ![](https://cdn.luogu.com.cn/upload/image_hosting/op4nz3s6.png)

- 其实也就是在说无论怎么移动绿线始终没有红线斜率大。
- 证明是这样的：绿线若想要比红线斜率大，那么必须将 $A,B$ 两点进行移动，在移动过程中，不论函数的形状如何，肯定存在一点使得 $K_{AB} \le \max(K_{AC},K_{CB})$，当 $C$ 越来越趋近于 $A$ 或 $B$ 时，取 $C$ 点即可。证毕。
- 其实证明感性理解一下就好，严谨的我也不会证。
- 证明完这个我们就可以发现，问题变得很简单了。
- 还记得上面提到的 $z$ 吗？ 我们有 $K = \max(\lvert{a_z - a_{z + 1}\rvert})$，发现和差分的形式很像，于是就差分出来。
- 那么这题就是在让我们求：区间子段上的最大值的和，$O(n^2)$ 枚举区间，RMQ $O(1)$ 得到最大值即可，复杂度 $O(qn^2)$。
- 发现仍然不可接受，接下来的优化其实就是板子题了，考虑枚举最大值，判断这个最大值对答案贡献了几次。
- 考虑这个数若可以成为最大值，那么这个子段最大的左边界就是这个数前面第一个比它大的数的位置，右边界同理，若预处理出左右边界，那么就可以计算贡献。
- 这让我们想到，我们将权值（指差分后的值）从大到小排序，每次 $O(logn)$ 得到前驱后继即可，所以需要一颗 FHQ（你写别的我也不拦着）。
- 总的复杂度是 $O(qn + 2nlogn)$ 的，可以通过本题。

- 接下来就是喜闻乐见的代码时间啦！

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e5 + 1;

int n, q, tot, Rt;
int a[maxn], dif[maxn], lst[maxn], nxt[maxn];

class Seqs_of_Array {
    public:
        int pos, val;
        inline bool operator < (const Seqs_of_Array &g) const {
            return g.val < val;
        }
};

class Fhq_Treap{
    private :
        class Tree{
            public :
                int ls, rs;
                int dat, val;
                int sz;
        }T[maxn];

        inline void Upd(int p) {
            T[p].sz = T[T[p].ls].sz + T[T[p].rs].sz + 1;
        }

        inline void Split(int p, int k, int& x, int& y) {
            if(p == 0) {
                x = y = 0;
                return;
            }
            
            else {
                if(T[p].val <= k) {
                    x = p;
                    Split(T[p].rs, k, T[p].rs, y);
                }
                else {
                    y = p;
                    Split(T[p].ls, k, x, T[p].ls);
                }
            }
            Upd(p);
            return;
        }

        inline int Marge(int x, int y) {
            if(x == 0 or y == 0) 
                return x + y;

            if(T[x].dat < T[y].dat) {
                T[x].rs = Marge(T[x].rs, y);
                Upd(x);
                return x;
            }
            else {
                T[y].ls = Marge(x, T[y].ls);
                Upd(y);
                return y;
            }
        }

        inline int New_Node(int k) {
            int p = ++tot;
            T[p].sz = 1; T[p].rs = T[p].ls = 0;
            T[p].dat = rand(), T[p].val = k;
            return p;
        }
    public :

        inline void Insert(int k) {
            int x, y;
            // cout << Rt << endl;
            Split(Rt, k, x, y);
            int New = New_Node(k);
            Rt = Marge(Marge(x, New), y);
            return;
        }

        inline int Get_Pre(int k) {
            int x, y, p;
            Split(Rt, k - 1, x, y);
            p = x;
            while(T[p].rs)
                p = T[p].rs;
            int ans = T[p].val;
            Rt = Marge(x, y);
            return ans;
        }

        inline int Get_Nxt(int k) {
            int x, y, p;
            Split(Rt, k, x, y);
            p = y;
            while(T[p].ls)
                p = T[p].ls;
            int ans = T[p].val;
            Rt = Marge(x, y);
            return ans;
        }
};

Fhq_Treap T;


Seqs_of_Array p[maxn];

signed main() {
    // #define Areka
    #ifdef Areka
        freopen("b.in", "r", stdin);
        freopen("b.out", "w", stdout);
    #endif
    n = read(), q = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read(), dif[i] = abs(a[i] - a[i - 1]),
        p[i].pos = i, p[i].val = dif[i];
    sort(p + 1, p + n + 1);
    T.Insert(1), T.Insert(n + 1);
    for(int i = 1; i <= n; ++i) {
        lst[p[i].pos] = T.Get_Pre(p[i].pos),
        nxt[p[i].pos] = T.Get_Nxt(p[i].pos);
        T.Insert(p[i].pos);
    }

    for(int i = 1; i <= q; ++i) {
        int l = read(), r = read();
        int res = 0;
        for(int j = l + 1; j <= r; ++j) {
            int lt = lst[j], nt = nxt[j];
            (lt < l) and (lt = l), (nt > r) and (nt = r + 1);
            res += (dif[j] * ((j - lt) * (nt - j)));
        }
        printf("%lld\n", res);
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}

```



---

## 作者：Refined_heart (赞：1)

这种题第一眼看上去不可做，我们考虑证明一个结论：

对于一个区间的 $Lipschitz$ 常数 $k$ ,应满足：

$$k=\max_{i=l}^{r-1} \left\{\frac{a[i+1]-a[i]}{i+1-i}\right\}$$

即

$$k=\max_{i=l}^{r-1} \left\{|a[i+1]-a[i]|\right\}$$

证明：

考虑三个数的情况，设它们分别是：$\left\{0,x,\infty\right\}$

那么，相邻的区间的 $Lipschitz$ 常数 $k=\left\{x,\infty-x\right\}$

而整体区间的 $Lipschitz$ 常数 $k=\frac{\infty}{2}$

那么考虑 $x$ 的取值会发现，无论 $x$ 怎么取值，相邻区间的 $Lipschitz$ 常数 $k$ 必然要大于整体区间的 $k.$ 而根据三个数的区间进行推广即可。

证毕。

那么我们接下来的任务就是回答询问了，观察到询问数目很少，所以我们用 $O(nq)$ 的复杂度就可以了。

考虑如何 $O(n)$ 回答一组询问：

观察相邻区间的 $k$ 会出现多少次。我们求出左边和右边第一个大于它的数的位置，那么在这个区间中，任意一个包含它的区间都会让 $k$ 出现一次。那么如果我们可以 $O(n)$ 求出这个东西，问题就解决了。

显然单调栈可以完成这个任务。

于是这题做完了。单调栈内部维护数值递减的序列下标，每次弹出栈的时候更新栈顶元素的目标值就好了。

总复杂度：$O(nq).$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=2e5+10;
const int inf=(1<<30);
int n,q,a[MAXN],h[MAXN];
inline int Abs(int x){if(x<0)return -x;return x;}
int st[MAXN],top;
int l[MAXN],r[MAXN];
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;++i)scanf("%lld",&h[i]);
	for(int i=1;i<n;++i)a[i]=Abs(h[i+1]-h[i]);
	for(;q;q--){
		int L,R;
		scanf("%lld%lld",&L,&R);
		R--;
		memset(l,0,sizeof l);
		memset(r,0,sizeof r);
		int ans=0;
		for(int i=L,j=1;i<=R;++i,++j)a[j]=Abs(h[i+1]-h[i]);
		int len=R-L+1;
		top=0;
		for(int i=1;i<=len;++i){
			while(top&&a[st[top]]<a[i]){
				r[st[top]]=i-st[top];
				top--;
			}
			l[i]=i-st[top];
			st[++top]=i;
		}
		while(top)r[st[top]]=len+1-st[top],top--;
		for(int i=1;i<=len;++i)ans+=a[i]*l[i]*r[i];
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：wmrqwq (赞：0)

怎么没人写好写的 ST 表呢。

# 题目链接

[CF601B Lipshitz Sequence (luogu)](https://www.luogu.com.cn/problem/CF601B)

[CF601B Lipshitz Sequence (codeforces)](https://codeforces.com/problemset/problem/601/B)

# 解题思路

其实一眼可以发现选相邻的是最优的。

证明：

若这个区间中的数字为 $[a,b,c]$，此时若选择 $a,c$ 这两个数字，则必有 $\frac{|a - c|}{2} \ge |a - b|$，$\frac{|a-c|}{2} \ge |b - c|$，两式相加得 $|a - c| \ge |a - b| + |b - c|$，此时分讨三个数的大小关系：

- $a \le b \le c$，此时式子为 $c - a \ge b - a + c - b$，化简得 $0 \ge 0$，说明此时选相邻两个数与选 $a,c$ 两个数相比不劣。

- $a \le c \le b$，此时式子为 $c - a \ge b - a + b - c$，化简得 $2c \ge 2b$，由于 $c \le b$，因此 $2c \le b$，不符合原命题，说明此时选相邻两个数与选 $a,c$ 两个数相比不劣。

- $b \le a \le c$，此时式子为 $c - a \ge a - b + c - b$，化简得 $2b \ge 2a$，由于 $b \le a$，因此 $2b \le 2a$，不符合原命题，说明此时选相邻两个数与选 $a,c$ 两个数相比不劣。

- $b \le c \le a$，此时式子为 $a - c \ge a - b + c - b$，化简得 $2b \ge 2c$，由于 $b \le c$，因此 $2b \le 2c$，不符合原命题，说明此时选相邻两个数与选 $a,c$ 两个数相比不劣。

- $c \le a \le b$，此时式子为 $a - c \ge b - a + b - c$，化简得 $2a \ge 2b$，由于 $a \le b$，因此 $2a \le 2b$，不符合原命题，说明此时选相邻两个数与选 $a,c$ 两个数相比不劣。

- $c \le b \le a$，此时式子为 $a - c \ge a - b + b - c$，化简得 $0 \ge 0$，说明此时选相邻两个数与选 $a,c$ 两个数相比不劣。

因此选相邻两个数字一定不劣，此时设 $i \in [1,n-1]$，$b_i = |a_i - a_{i+1}|$，则答案为 $\sum_{i=l}^{r-1} \sum_{j=i}^{r-1} \max_{k=i}^{j} b_k$。

  这是一个经典的问题，直接 ST 表加二分即可，注意此时需要预处理每个 $L,R$ 的节点，这样复杂度是 $O(n \log n + nq)$ 的，不会 TLE，否则直接做是 $O(qn \log n)$ 的，会 TLE。

直接单调栈也能做，我写的是 ST 表。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll int
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define QwQ return 0;
ll pw(ll x){return 1ll<<x;}
ll _t_;
ll lg[1000110];
void Init(){
    forl(i,2,1e6+5)
        lg[i]=lg[i>>1]+1;
}
ll n,q;
ll a[100010];
ll b[100010];
ll l,r;
ll maxn[100010][20];
ll nL[100010],nR[100010];
ll query(ll l,ll r)
{
    if(l>r)
        return (ll)2e9;
    ll LG=lg[r-l+1];
    return max(maxn[l][LG],maxn[r-pw(LG)+1][LG]);
}
long long ans;
void _clear(){}
void solve()
{
    _clear();
    cin>>n>>q;
    forl(i,1,n)
        cin>>a[i];
    forl(i,1,n-1)
        b[i]=abs(a[i+1]-a[i]),
        maxn[i][0]=b[i];
    n--;
    forl(j,1,19)
        forl(i,1,n-pw(j)+1)
            maxn[i][j]=max(maxn[i][j-1],maxn[i+pw(j-1)][j-1]);
    l=1,r=n;
    ans=0;
    forl(i,l,r)
    {
        ll L=l,R=i;
        while(L<R)
        {
            ll Mid=(L+R)/2;
            if(query(Mid,i-1)<b[i])
                R=Mid;
            else
                L=Mid+1;
        }
        ll nl=L;
        L=i,R=r;
        while(L<R)
        {
            ll Mid=(L+R+1)/2;
            if(query(i+1,Mid)<=b[i])
                L=Mid;
            else
                R=Mid-1;
        }
        ll nr=L;
        if(query(nl,i)==b[i] && query(i,nr)==b[i])
            nL[i]=nl,
            nR[i]=nr;
        else
            nL[i]=nR[i]=i;
    }
    while(q--)
    {
        cin>>l>>r;
        r--;
        forl(i,l,r)
        {
            ll nl=max(nL[i],l),nr=min(nR[i],r);
            ans+=1ll*b[i]*(i-nl+1)*(nr-i+1);
        }
        cout<<ans<<endl;
        ans=0;
    }
}
int main()
{
	Init();
    IOS;
    _t_=1;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：Enoch006 (赞：0)

对关于 $k$ 的式子移项：
$$k\ge \frac{|V_i-V_j|}{|i-j|}[k\in \Z]$$
注意到右边的式子是**斜率的绝对值**：
$$k\ge \frac{|y_i-y_j|}{|x_i-x_j|}[k\in \Z]$$
若有 $x$ 坐标连续的三个点，那么这三个点两两之间斜率绝对值的最大值一定在下标连续的两点之间。

因为斜率代表着一条直线的倾斜程度，下标不连续的两点直线倾斜程度“均摊”下标连续的两点直线的倾斜程度。

![](https://cdn.luogu.com.cn/upload/image_hosting/cgdq9eup.png)

如图，蓝色的两条直线斜率绝对值都不是最大值。

所以，推广一下，一个序列的 Lipschitz 常数一定是相邻下标贡献的。

注意到每个 Lipschitz 常数的贡献的区间数等于大根笛卡尔树左右子树大小相乘。

当然你可以建笛卡尔树，也可以使用 ST 表找最大值下标。后者时间复杂度是 $O(n\log n+qn)$ 的，可以通过本题。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 100005
#define maxn 1005
#define inf 0x3f3f3f3f3f3f
using namespace std;
int T,n,m,ans;
int a[maxm],b[maxm],f[maxm][25];
int CMP(int x,int y){return a[x]>a[y]?x:y;}
int Ask(int l,int r){
	int k=__lg(r-l+1);
	return CMP(f[l][k],f[r-(1<<k)+1][k]);
}
void Dfs(int l,int r){
	if(l>r)return;
	int mid=Ask(l,r);
	ans+=(mid-l+1)*(r-mid+1)*a[mid];
	Dfs(l,mid-1);Dfs(mid+1,r);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	cin>>n>>T;
	for(int i=1;i<=n;i++)cin>>b[i];n--;
	for(int i=1;i<=n;i++)a[i]=abs(b[i]-b[i+1]),f[i][0]=i;//Lipschitz 常数
	for(int j=1;j<=20;j++)for(int i=1;i+(1<<j)-1<=n;i++)f[i][j]=CMP(f[i][j-1],f[i+(1<<j-1)][j-1]);
	while(T--){
		int l,r;
		cin>>l>>r;
		r--;ans=0;
		Dfs(l,r);
		cout<<ans<<"\n";
	}
    return 0;
}
```

---

## 作者：123456xwd (赞：0)

[CF601B Lipshitz Sequence](https://www.luogu.com.cn/problem/CF601B)

居然没有一个人是预处理的。

题目就是在平面直角坐标系上给你 $n$ 个点，点 $i$ 的坐标为 $(i,v_{i})$，询问区间 $[l,r]$ 的每个子区间内的任意两点构成的直线的斜率的最大值的和。

我们发现，一个区间斜率最大值为区间内相邻两个点斜率的最大值。

证明一下：

假设区间内相邻两个点的斜率最大值为 $k$，那么对于两个非相邻点的斜率，我们想让这个解优于 $k$，就必须让那两个点之间的点的相邻两点的斜率至少有一个优于 $k$，与 $k$ 的定义矛盾，得证。

设 $a_{i}=\left|h_{i}-h{i+1}\right|$，$L_{i},R_{i}$ 分别表示在 $a_i$ 左边**大于** $a_i$ 的点的下标加一，右边第一个**大于等于** $a_i$ 的点的下标减一，我们可以预处理出来。

那么，每次查询就这样：

```c++
scanf("%d%d",&l,&r);
ans=0;r--;
for(int i=l;i<=r;i++){
    ans+=(ll)a[i]*(ll)((ll)(i-max(l,L[i]))*(min(r,R[i])-i)+1+(i-max(l,L[i]))+(min(r,R[i])-i));//横跨了i的区间，i自己，只在i左边/右边的区间
}
printf("%lld\n",ans);
```

---

## 作者：傅思维666 (赞：0)



## 题解：

其实原题面能对思路进行启发，翻译过来毕竟漏掉了很多东西。

其实这个$Lipshitz$值是啥啊，就是这个东西呀：
$$
L(h)=\max\lceil\frac{|h[j]-h[i]|}{|j-i|}\rceil
$$
其中，$i,j$要遍历所有位置。

这个是啥啊，这个不就是这个散点型函数的斜率么！

于是我们对一个区间进行子区间枚举，并且在子区间再暴力枚举$i,j$。就可以暴力地得到这个东西。时间复杂度为$O(qn^4)$。可以通过20pts（真是良心出题人）。

然后思考优化。发现可以剪枝呀！

不用枚举那么多，可以证明的一个贪心是：对于任意三个点来讲，其最大斜率绝对不可能出现在一号点和三号点之间，而只会出现在1、2，或2、3之间。

于是先预处理出所有的$h[i+1]-h[i]$，然后架一棵线段树求区间max，可以把一重$n^2$优化成$\log n$。复杂度为$O(qn^2\log n)$。可以通过60pts。

还能不能更优秀呢？能，可以换种思路，把问题变成：询问区间中有多少子区间是以$a[i]$做最大值的（$a[i]=|h[i+1]-h[i]|$）

发现这个可以用单调栈维护出左右第一个大于它的。设左右分别为$l,r$，那么最后每个$a[i]$对答案的贡献就是，这个点到左的距离*这个点到右的距离 *这个点的权值.

于是我们只需要每次扫一遍即可。

时间复杂度$O(n+qn)$。

可以得满分。

```cpp
#include<cstdio>
#include<cmath>
#define lll long long
using namespace std;
const int maxn=1e5+5;
int n,q;
int h[maxn],a[maxn];
int st[maxn],top;
int cnt[maxn];
lll query(int l,int r)
{
	lll ret=0;
	top=0;
	st[0]=l-1;
	for(int i=l;i<r;i++)
	{
		while(top && a[i]>a[st[top]])
		{
			ret+=(1ll*cnt[top]*a[st[top]]*(i-st[top]));
			top--;
		}
		st[++top]=i;
		cnt[top]=i-st[top-1];
	}
	while(top)
	{
		ret+=(1ll*cnt[top]*a[st[top]]*(r-st[top]));
		top--;
	}
	return ret;
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	for(int i=1;i<n;i++)
		a[i]=abs(h[i+1]-h[i]);
	for(int i=1;i<=q;i++)
	{
		int ll,rr;
		scanf("%d%d",&ll,&rr);
		printf("%lld\n",query(ll,rr));
	}
	return 0;
}
```





---

