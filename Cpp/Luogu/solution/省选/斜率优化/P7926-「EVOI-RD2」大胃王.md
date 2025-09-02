# 「EVOI-RD2」大胃王

## 题目描述

又到了一日三度的吃饭时间，大胃王开始因为吃什么饭而犯难了。

现有 $n$ 个材料，每个材料有一定的质量。大胃王可以把这 $n$ 个材料分为**连续**的任意段，然后每一段配一段质量为 $L$ 的主食。每一段的不和谐度定义为这段材料的质量和减去该段主食的质量（就是 $L$）的平方。一顿饭的不和谐度为所有段的不和谐度之和。



不用担心饭的多少的问题，因为某Code 是大胃王，所以做多少他都能吃完。

接下来，某Code 向你发起了挑战，要求你回答前 $i$ 道菜所做出的一顿饭的**最小和第二小**不和谐度。如果你回答正确，你将获得与他共享这顿饭菜的机会。

当两种分配方法得出同样最小的不和谐度时，则输出两个最小的不和谐度。即所输出的并非严格第二小不和谐度。

## 说明/提示

**样例 1 解释**

第一行：$4=(3-5)^2$  
第二行：$5=(3-5)^2+(6-5)^2$，$16=(3+6-5)^2$  
第三行：$13=(3-5)^2+(6+2-5)^2$，$14=(3-5)^2+(6-5)^2+(2-5)^2$  
第四行：$6=(3-5)^2+(6-5)^2+(2+4-5)^2$，$14=(3-5)^2+(6+2-5)^2+(4-5)^2$  
第五行：$15=(3-5)^2+(6-5)^2+(2+4-5)^2+(8-5)^2$，$23=(3-5)^2+(6+2-5)^2+(4-5)^2+(8-5)^2$


**【数据规模与约定】**

**本题采用捆绑测试。**

+ Subtask 1 (10 pts)：$1 \le n \le 10$。
+ Subtask 2 (20 pts)：$1 \le n \le 200$。
+ Subtask 3 (20 pts)：$1 \le n \le 3000$。
+ Subtask 4 (40 pts)：数据随机生成。
+ Subtask 5 (10 pts)：无特殊性质。

对于 $100\%$ 的数据，$1 \le n \le 2 \times 10^5$，$1 \le L,a_i \le 10^4$。

## 样例 #1

### 输入

```
5 5
3 6 2 4 8
```

### 输出

```
4
5 16
13 14
6 14
15 23```

## 样例 #2

### 输入

```
10 7
4 6 9 1 5 9 5 1 7 1 
```

### 输出

```
9
9 10
13 14
18 19
14 15
18 19
22 23
19 20
19 20
20 21```

# 题解

## 作者：冷月葬T魂 (赞：4)

### 这题数据难造，放过了错误解法。以下为标算：

首先设 $f(i,0)$ 为前 $i$ 道菜的最小不和谐度，$f(i,1)$ 为前 $i$ 道菜的第二小小不和谐度。令 $sum_i$ 为前 $i$ 道菜的质量之和。 列出转移方程：  
$$
f(i,0)=\min_{0 \leq j \lt i }\{ f(j,0)+(sum_i-sum_j-L)^2 \} 
$$
$$
f(i,1)=\min( \operatorname{min2}_{0 \leq j \lt i }\{ f(j,0)+(sum_i-sum_j-L)^2 \},  \min_{0 \leq j \lt i }\{ f(j,1)+(sum_i-sum_j-L)^2 \}  )
$$  
其中 $\operatorname{min2}{S}$ 代表集合 $S$ 中的第二小元素。  

将方程的 $\min$ 去掉，移项，得：  

$$
f(j)+sum_j^2+2Lsum_j=(2sum_i)sum_j+(f(i)+2Lsum_i-sum_i^2-L^2)
$$  

其中 $f(i)$ 同时代表 $f(i,0)$ 和 $f(i,1)$。  

我们要开始斜率优化动态规划啦~

对于第一个方程，维护一个凸壳转移即可。重点在第二个方程。  

首先对于 $f(i,0)$ 维护**两个**凸壳，第一个（$q0$）是 $f(i,0)$ 正常的凸壳，第二个（$q2$）是 $q0$ 中弹出的点所构成的凸壳。如图：（蓝色为凸壳 $q0$，橙色为凸壳 $q2$）  

![evoi2.png](https://cdn.luogu.com.cn/upload/image_hosting/6clnkar4.png?x-oss-process=image/resize,m_lfit,h_840,w_1024)  

我们可以看到，对于直线 QC ，它与 $q0$ 相切于点 C ，它的平行线与 $q2$ 相切于点 H ，此时转移方程的第一项 $\operatorname{min2}_{0 \leq j \lt i }\{ f(j,0)+(sum_i-sum_j-L)^2 \}$ 只需考虑从B，D，H三点转移而来。  

转移方程的第二项用另一个凸壳 $q1$ 单独维护即可，此处不再赘述。  

接下来考虑维护这两个凸壳的问题。如图，假设插入点 Q 。  

![evoi3.png](https://cdn.luogu.com.cn/upload/image_hosting/71yt0ang.png?x-oss-process=image/resize,m_lfit,h_840,w_1024)  

首先 Q 把点 C，D，E，F 都弹了出来，先把它们记录下来（注意不能一边弹一边塞进 $q2$，否则顺序不对）  

然后注意：找到凸壳 $q2$ 中第一个**横坐标**大于点 C 的点（此例子中是J），把这个及以后的点都从 $q2$ 中弹出去。为什么？因为这些点都恒比 C 差，而 C 又比 B，Q 差，因此这些点连第二都没机会，丢掉即可。  

接着按顺序把“凸壳断片” C-D-E-F 按顺序插入 $q2$ 即可。最后 $q0=[A,B,Q], q2=[G,H,C,D,E,F]$。  

每次用二分查找找到直线与凸壳的“切点”，时间复杂度 $O(n \log n)$。  

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define clr(a,v) memset(a,v,sizeof(a))
#define int long long
using namespace std;

const int N=1e6+5;

// f[i] = min{ f[j]+(sum[i]-sum[j]-L)^2 }
//      = min{ f[j]+sum[i]^2+sum[j]^2+L^2-2*sum[i]*L-2*sum[i]*sum[j]+2*sum[j]*L }
//      = min{ (f[j]+sum[j]^2+2*L*sum[j]) + (sum[i]^2-2*L*sum[i]+L^2) - 2*sum[i]*sum[j] }
//
// f[j]+sum[j]^2+2*L*sum[j] = (2*sum[i])*sum[j] + (f[i]+2*L*sum[i]-sum[i]^2-L^2)

int n,L,a[N],f[N][2],sum[N];
int q[3][N],h[3],t[3];

int ff(int j,int c)
{
	return f[j][c&1]+sum[j]*sum[j]+2*L*sum[j];
}

int find(int k,int c)
{
	int l=h[c],r=t[c]-1;
	
	while(l<r){
		int mid=(l+r)>>1;
		if( ff(q[c][mid+1],c)-ff(q[c][mid],c) > (sum[q[c][mid+1]]-sum[q[c][mid]])*k ) r=mid;
		else l=mid+1;
	}
	
	return l;
}

int sqr(int x)
{
	return x*x;
}

signed main()
{
	cin>>n>>L;
	
	For(i,1,n) cin>>a[i];
	
	For(i,1,n) sum[i]=sum[i-1]+a[i];
	
	For(c,0,1){
		h[c]=t[c]=0;
		q[c][t[c]++]=0;
	}
	
	h[2]=t[2]=0;
	
	f[0][0]=0;
	f[0][1]=1e12;
	
	For(i,1,n){
		int p=find(2*sum[i],0);
		
		int j=q[0][p];
		
		f[i][0]=f[j][0]+sqr(sum[i]-sum[j]-L);
		
		f[i][1]=1e18;
		
		if(p>h[0]){
			j=q[0][p-1];
			f[i][1]=min(f[i][1],f[j][0]+sqr(sum[i]-sum[j]-L));
		}
		
		if(p<t[0]-1){
			j=q[0][p+1];
			f[i][1]=min(f[i][1],f[j][0]+sqr(sum[i]-sum[j]-L));
		}
		
		if(h[2]<t[2]){
			p=find(2*sum[i],2);
			
			j=q[2][p];
			
			f[i][1]=min(f[i][1],f[j][0]+sqr(sum[i]-sum[j]-L));
		}
		
		p=find(2*sum[i],1);
		
		j=q[1][p];
        
		f[i][1]=min(f[i][1],f[j][1]+sqr(sum[i]-sum[j]-L));
		
		int tt0=t[0];
		
		while(h[0]<t[0]-1 && 1.0*(ff(q[0][t[0]-1],0)-ff(q[0][t[0]-2],0))*(sum[i]-sum[q[0][t[0]-1]])
							> 1.0*(ff(i,0)-ff(q[0][t[0]-1],0))*(sum[q[0][t[0]-1]]-sum[q[0][t[0]-2]]) ){
			t[0]--;
		}
		
		if(t[0]<tt0){
			int l=h[2],r=t[2];
			
			while(l<r){
				int mid=(l+r)>>1;
				if(sum[q[2][mid]]>sum[q[0][t[0]]]) r=mid;
				else l=mid+1;
			}
			
			t[2]=l;
        
			For(k,t[0],tt0-1){
				int u=q[0][k];
				while(h[2]<t[2]-1 && 1.0*(ff(q[2][t[2]-1],0)-ff(q[2][t[2]-2],0))*(sum[u]-sum[q[2][t[2]-1]])
									> 1.0*(ff(u,0)-ff(q[2][t[2]-1],0))*(sum[q[2][t[2]-1]]-sum[q[2][t[2]-2]]) ){
					t[2]--;
				}
				q[2][t[2]++]=q[0][k];
			}
		}
		
		q[0][t[0]++]=i;
		
		while(h[1]<t[1]-1 && 1.0*(ff(q[1][t[1]-1],1)-ff(q[1][t[1]-2],1))*(sum[i]-sum[q[1][t[1]-1]])
							> 1.0*(ff(i,1)-ff(q[1][t[1]-1],1))*(sum[q[1][t[1]-1]]-sum[q[1][t[1]-2]]) ){
			t[1]--;
		}
		
		q[1][t[1]++]=i;
	}
	
	cout<<f[1][0]<<endl;
	For(i,2,n) printf("%lld %lld\n",f[i][0],f[i][1]);
	cout<<endl;
	
	return 0;
}

/*
4 6071
831 9651 9357 65
*/




```

---

## 作者：spider_oyster (赞：3)

好像没人用李超线段树？我来写一发。

记 $a$ 的前缀和数组为 $s$，可以得出状态转移方程：

$f_i=\min\limits_{j=0}^{i-1}f_j+(s_i-s_j-L)^2$。

设 $g_i=s_i-L$，化简式子如下：

$f_i=\min\limits_{j=0}^{i-1}f_j+g_i^2+s_j^2-2\times s_j\times g_i$。

$f_i=\min\limits_{j=0}^{i-1}(-2\times s_j\times g_i+s_j^2)+g_i^2$。

于是直接李超线段树维护上述式子最小值次小值。

记上述式子的次小值为 $se$，第二小不和谐度为 $f'$，则

$f'_ i=\min\{ \min\limits_{j=0}^{i-1}f'_ j+g_i^2+s_j^2-2\times s_j\times g_i,se\}$。

由于懒，前面的那一坨我还是选择用李超维护。

但这题数据太强了，细节有点多。我初始化写挂了，调了半天。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define mi first
#define se second
#define mid ((l+r)>>1)
using namespace std;

const int N=2e5+5;
int n,L,id2[N<<2];
ll s[N],f[N],f2[N];
pii id[N<<2];
inline ll g(int i) {return s[i]-L;}

struct line{
    ll k,b;
    ll operator()(const int &i) {return k*g(i)+b;}
}p[N],p2[N];

//只能有一条编号 0 的直线，我就是这里挂了
void init() {for(int i=1;i<=n*4;i++) id[i]={n+1,n+1};id[1]={0,n+1};}

void upd(int u,int k=1,int l=1,int r=n)
{
    pii &v=id[k];
    if(p[u](mid)<p[v.mi](mid)) swap(v.mi,v.se),swap(v.mi,u);
    else if(p[u](mid)<p[v.se](mid)) swap(v.se,u);
    if(p[u](l)<max(p[v.mi](l),p[v.se](l))) upd(u,k<<1,l,mid);
    if(p[u](r)<max(p[v.mi](r),p[v.se](r))) upd(u,k<<1|1,mid+1,r);
}
pii query(int x,int k=1,int l=1,int r=n)
{
    pii u=id[k],v;
    if(l==r) return u;
    v=(x<=mid?query(x,k<<1,l,mid):query(x,k<<1|1,mid+1,r));
    int a[4]={u.mi,u.se,v.mi,v.se};
    //懒，直接排序了
    sort(a,a+4,[x](int &a,int &b){return p[a](x)<p[b](x);});
    return {a[0],a[1]};
}

void upd2(int u,int k=1,int l=1,int r=n)
{
    int &v=id2[k];
    if(p2[u](mid)<p2[v](mid)) swap(u,v);
    if(p2[u](l)<p2[v](l)) upd2(u,k<<1,l,mid);
    if(p2[u](r)<p2[v](r)) upd2(u,k<<1|1,mid+1,r);
}
int query2(int x,int k=1,int l=1,int r=n)
{
    int u=id2[k],v;
    if(l==r) return u;
    v=(x<=mid?query2(x,k<<1,l,mid):query2(x,k<<1|1,mid+1,r));
    return p2[u](x)<p2[v](x)?u:v;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>L;
    for(int i=1;i<=n;i++) cin>>s[i],s[i]+=s[i-1];
    init();
    p[n+1].b=f2[0]=f2[1]=1e16;//把直线 n+1 的值设为 inf
    for(int i=1;i<=n;i++)
    {
        auto [j1,j2]=query(i);
        int j3=query2(i);
        f[i]=f[j1]+(g(i)-s[j1])*(g(i)-s[j1]);
        ll x=f[j2]+(g(i)-s[j2])*(g(i)-s[j2]);
        ll y=f2[j3]+(g(i)-s[j3])*(g(i)-s[j3]);
        p[i]={-2*s[i],f[i]+s[i]*s[i]};
        upd(i);
        cout<<f[i];
        if(i!=1)
        {
            f2[i]=min(x,y);
            p2[i]={-2*s[i],f2[i]+s[i]*s[i]};
            upd2(i);
            cout<<' '<<f2[i];
        }
        cout<<'\n';
    }
}
```


---

## 作者：wxzzzz (赞：0)

### 思路

记 $f_{i,0/1}$ 表示前 $i$ 个数能得到的最小值（$0$）和次小值（$1$），$\displaystyle s_i=\sum_{j=1}^i a_j$，有：

$$f_{i,0}=\max_{j=0}^{i-1}\{f_j+(s_i-s_j-L)^2\}$$

令 $pos$ 为 $f_{i,0}$ 的任意一个最优转移点，即 $f_{i,0}=f_{pos}+(s_i-s_{pos}-L)^2$，有：

$$f_{i,1}=\max\Big(\max_{j=0}^{i-1}\{f_{j,1}+(s_i-s_j-L)^2\},\max_{j=0,j\ne pos}^{i-1}\{f_{j,0}+(s_i-s_j-L)^2\}\Big)$$

先考虑转移 $f_{i,0}$ 令 $t_i=s_i-L$，有：

$$\begin{aligned}
f_{i,0}&=f_{pos,0}+(s_i-s_{pos}-L)^2\\
&=f_{pos,0}+(t-s_{pos})^2\\
&=f_{pos,0}+t^2-2t\times s_{pos}+{s_{pos}}^2
\end{aligned}$$

开始斜率优化，令 $b_i=f_{i,0}-t^2,y_{pos}=f_{pos}+{s_{pos}}^2,k_i=2t,x_{pos}=s_{pos}$，有：

$$b_i=y_{pos}-k_ix_{pos}$$

将转移点 $i$ 看作平面直角坐标系上的一点，坐标 $(s_i,f_i+{s_i}^2)$，斜率优化转移即可。

考虑次大值可以从哪些地方转移。

如果直接转移需要实时维护一个除 $pos$ 之外所有点的凸壳，这很麻烦，考虑将其分为几部分：

1. 维护一个 $1\sim i-1$ 的次小值凸壳，类似最小值转移。

1. 求出最小值之后得到其在最小值凸壳上的最优转移点 $pos$，除了该点之外最优转移点便是 $pos$ 在凸壳上的前驱或后继，分别转移一遍即可。

   ![](https://cdn.luogu.com.cn/upload/image_hosting/jvqmdqr4.png)

1. 对于不在最小值凸壳上的所有点（在维护最小值凸壳过程中出栈的点），如果没有 $pos$ 它们也可能在凸壳上。
  
    以下图为例，如果没有 H 那么 C 就会在凸壳上。

    ![](https://cdn.luogu.com.cn/upload/image_hosting/jdzsx0ov.png)

   另外再维护一个这些点的凸壳，类似地在上面找最优转移点即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, top[4];
long long s[200005];
struct point {
    long long x, y;
} st[4][200005];
//st[0] f1 min
//st[1] f1 min -> f1 out
//st[2] f1 out
//st[3] f2 min
double slope(point p1, point p2) {
    return (double)(p1.y - p2.y) / (p1.x - p2.x);
}
void push(int g, point p) {
    while (top[g] > 1) {
        point p1 = st[g][top[g] - 1], p2 = st[g][top[g]];

        if (p2.x >= p.x || slope(p1, p2) >= slope(p2, p)) {
            if (!g)
                st[1][++top[1]] = p2;

            top[g]--;
        } else
            break;
    }

    st[g][++top[g]] = p;

    if (!g)
        while (top[1])
            push(2, st[1][top[1]--]);
}
int get(int g, double k) {
    int l = 1, r = top[g] - 1, mid, ret = top[g];

    while (l <= r) {
        mid = l + r >> 1;

        if (slope(st[g][mid], st[g][mid + 1]) >= k)
            ret = mid, r = mid - 1;
        else
            l = mid + 1;
    }

    return ret;
}
int main() {
    cin >> n >> m;

    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        s[i] = s[i - 1] + x;
    }

    push(0, {0, 0});

    for (int i = 1, pos; i <= n; i++) {
        long long t, k, f1, f2;
        t = s[i] - m, k = 2 * t;
        pos = get(0, k);
        point j1 = st[0][pos];
        f1 = j1.y - k * j1.x + t * t;
        cout << f1;

        if (i > 1) {
            point j2;
            f2 = 1e18;

            if (top[2]) {
                j2 = st[2][get(2, k)];
                f2 = min(f2, j2.y - k * j2.x + t * t);
            }

            if (top[3]) {
                j2 = st[3][get(3, k)];
                f2 = min(f2, j2.y - k * j2.x + t * t);
            }

            if (pos > 1) {
                j2 = st[0][pos - 1];
                f2 = min(f2, j2.y - k * j2.x + t * t);
            }

            if (pos < top[0]) {
                j2 = st[0][pos + 1];
                f2 = min(f2, j2.y - k * j2.x + t * t);
            }

            cout << ' ' << f2;
            push(3, {s[i], f2 + s[i]*s[i]});
        }

        cout << '\n';
        push(0, {s[i], f1 + s[i]*s[i]});
    }

    return 0;
}
```

---

