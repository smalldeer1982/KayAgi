# Nice Matrix

## 题目描述

A matrix of size $ n \times m $ is called nice, if all rows and columns of the matrix are palindromes. A sequence of integers $ (a_1, a_2, \dots , a_k) $ is a palindrome, if for any integer $ i $ ( $ 1 \le i \le k $ ) the equality $ a_i = a_{k - i + 1} $ holds.

Sasha owns a matrix $ a $ of size $ n \times m $ . In one operation he can increase or decrease any number in the matrix by one. Sasha wants to make the matrix nice. He is interested what is the minimum number of operations he needs.

Help him!

## 说明/提示

In the first test case we can, for example, obtain the following nice matrix in $ 8 $ operations:

```
<pre class="verbatim"><br></br>2 2<br></br>4 4<br></br>4 4<br></br>2 2<br></br>
```

In the second test case we can, for example, obtain the following nice matrix in $ 42 $ operations:

```
<pre class="verbatim"><br></br>5 6 6 5<br></br>6 6 6 6<br></br>5 6 6 5<br></br>
```

## 样例 #1

### 输入

```
2
4 2
4 2
2 4
4 2
2 4
3 4
1 2 3 4
5 6 7 8
9 10 11 18```

### 输出

```
8
42```

# 题解

## 作者：Lynkcat (赞：6)

挺容易想的一道题，考虑一个元素，发现最多可以有 $3$ 个元素与这个元素相关，设有 $x$ 个元素与这个元素相关，把这些元素反映到数轴上，就是求一个点到其他点的距离和要最小。显然就是大的 $x/2$ 个元素减去小的 $x/2$ 个元素。将整个矩阵都处理一遍即可。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define int long long 
using namespace std;

inline int read(){
    int x = 0; char ch = getchar(); bool positive = 1;
    for (; !isdigit(ch); ch = getchar())	if (ch == '-')	positive = 0;
    for (; isdigit(ch); ch = getchar())	x = x * 10 + ch - '0';
    return positive ? x : -x;
}
inline void write(int a){ 
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writesp(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
    printf(" ");
}
inline void writeln(int a){
    if(a<0){
    	a=-a; putchar('-');
    }
    write(a); puts("");
}

int T,n,m,ans,a[1005][1005],p[5],tot;

signed main()
{
	T=read();
	while(T--)
	{
		n=read(),m=read();ans=0;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
			  a[i][j]=read();
		}
		for (int i=1;i<=(n/2)+(n&1);i++)
		  for (int j=1;j<=(m/2)+(m&1);j++)
		  {
		  	tot=0;
		    tot++,p[tot]=a[i][j];
			if (n-i+1!=i) tot++,p[tot]=a[n-i+1][j];
			if (m-j+1!=j) tot++,p[tot]=a[i][m-j+1];
			if (n-i+1!=i&&m-j+1!=j) tot++,p[tot]=a[n-i+1][m-j+1];
		  	sort(p+1,p+tot+1);
		  	for (int j=1;j<=tot/2;j++) ans+=p[j+tot/2]-p[j];
		  }
		writeln(ans);
	}	
}
```

---

## 作者：Werner_Yin (赞：4)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/-solution-CF-1422-B.html)

## 题意

给你一个 $n*m$ 的矩阵，你可以每次将其中一个数 $+1$ 或 $-1$ ，求多少次可以使矩阵每一行每一列为回文的．

若一个数列 $(a_1,a_2,a_3,\dots,a_n)$ 为回文， $\forall a_i ,a_i = a_{n-i+1}$

$\texttt{Data Range:}$

$1 \leq n,m \leq 100,a_i \leq 10^9$

## 思路

我们注意到，要使每行每列都是回文的，就要使

 $a_{i,j} = a_{i,m-j+1} = a_{n-i+1,j} = a_{n-i+1,m-j+1}$ 

如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/lozeeyk2.png)

即图中的 $4$ 个绿色方块

那我们只要每次处理这 $4$ 个绿色方块，使其相同的操作次数最小。

设这 $4$ 个方块的数从小到大为 $x_1,x_2,x_3,x_4$ ，最后我们要是这些数都变为 $mid$ 。

代价为 $s = |x_1-mid| + |x_2 - mid| + |x_3 - mid| + |x_4 - mid|$ 

### 结论

当 $x_2 \leq mid \leq x_3$ ， $s$ 有最小值。

### 证明

如图：

绿色的线段和 代表 $s$ 。

![](https://cdn.luogu.com.cn/upload/image_hosting/fmpnw5r5.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/8ivahqga.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/6nq6qzq8.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/5fd6sll2.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/87hvdic0.png)

不管 $x_1,x_2,x_3,x_4$ 的大小，我们都可以发现：

$x_2 <= mid <= x_3$ 的情况最优。

因此，我们只要枚举 $mid = x_2$ 或$mid = x_3$ 就可以算答案了。

## 代码

```cpp
#define re(x) read(x)
#define ll long long

using namespace std;

const int MAXN = 110;
const ll INF = 1e15;
int n,m,a[MAXN][MAXN];

int main (){
    int T; re(T);
    while(T--){
        re(n);re(m);
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= m;j++)
                re(a[i][j]);
        ll ans = 0;
        for(int i = 1;i <= n/2;i++){
            for(int j = 1;j <= m/2;j++){ //每一行正中间的一个数无需考虑
                ll tt = INF,sum;
                
                sum = a[i][j];
                tt = min(tt,abs(a[i][j]-sum) + abs(a[n-i+1][j]-sum)+abs(a[i][m-j+1]-sum) + abs(a[n-i+1][m-j+1]-sum));
                
                sum = a[n-i+1][j];
                tt = min(tt,abs(a[i][j]-sum) + abs(a[n-i+1][j]-sum)+abs(a[i][m-j+1]-sum) + abs(a[n-i+1][m-j+1]-sum));
                
                sum = a[i][m-j+1];
                tt = min(tt,abs(a[i][j]-sum) + abs(a[n-i+1][j]-sum)+abs(a[i][m-j+1]-sum) + abs(a[n-i+1][m-j+1]-sum));
                
                sum = a[n-i+1][m-j+1];
                tt = min(tt,abs(a[i][j]-sum) + abs(a[n-i+1][j]-sum)+abs(a[i][m-j+1]-sum) + abs(a[n-i+1][m-j+1]-sum));
                
                ans += tt;
//注意,当时我写的时候没有排序,而是每个数进行枚举,因为数据量很小,所以可以过
            }
            if(m&1) ans += abs(a[i][m/2+1]-a[n-i+1][m/2+1]);
//如果有居中的行,只要满足这一行为回文的.
        }
        if(n&1){
            for(int i = 1;i <= m/2;i++){
                ans += abs(a[n/2+1][i] - a[n/2+1][m-i+1]);
            }
        }
        write(ans);
    }
    return 0;
}
```

---

## 作者：cqbzpyl (赞：2)

## [CF1422B Nice Matrix](https://codeforces.com/problemset/problem/1422/B)

赛上想到了中位数的做法，但是不知道怎么布局。

对于这个问题，首先需要考虑到，对于一个回文序列，它需要满足的条件是：

$a_{i,j}=a_{i,m-j+1}=a_{n-i+1,j}=a_{n-i+1,m-j+1}$（即从四个角开始对应对称的四个点的位置）

因此，我们只需要将图中所有对应位置的四个点全部变为同一个值即可。那么，变为哪个值呢？

根据贪心的思想，可以得到，变为这四个数最中间的值，需要改变的总次数最小。（思路由[此题](https://www.luogu.com.cn/problem/CF1520E)启发）

所以，这个题就只需要针对所有对应相关的位置，将他们全部变为这四个数的中位数即可。

code:

```cpp
#include<bits/stdc++.h>
#define int long long//不开 long long 见祖宗
using namespace std;
int n,m;
int a[110][110];
int b[5];
signed main() {
	int T;
	cin>>T;
	while(T--) {
		cin>>n>>m;
		int ans=0;
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				cin>>a[i][j];
			}
		}
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				b[0]=a[i][j],b[1]=a[i][m-j+1];
				b[2]=a[n-i+1][j],b[3]=a[n-i+1][m-j+1];//相对应的四个点
				sort(b,b+3);
				int cnt=min(b[1],b[2]);//取中位数
//				cout<<cnt<<' ';
				ans+=abs(cnt-b[0])+abs(cnt-b[1])+abs(cnt-b[2])+abs(cnt-b[3]);
			}
//			cout<<endl;
		}
		cout<<ans/4<<endl;//由于遍历了四个角，所以答案要除以四
	}
	return 0;
}
```

[AC 记录](https://codeforces.com/problemset/submission/1422/277720403)

---

## 作者：龙潜月十五 (赞：2)

## 一、题意

有一个 $n \times m$ 的矩阵，每次操作可以选择一个数使其 $+1$ 或是 $-1$，问最少操作几次能使每一行和每一列都是回文的（即 $a_i = a_{n-i+1}$）。

## 二、思路

初看之下不知该怎么处理，怎么能使每一行和每一列都是回文的呢？

但是思考一下容易发现，其实所谓的每一行每一列回文，就是让最多四个数在相同。如表：

| **1** | $2$ | $3$ | **4** |
| :----------: | :----------: | :----------: | :----------: |
| $5$ | $6$ | $7$ | $8$ |
| **9** | $10$ | $11$ | **18** |

对于 $1$ 来说，为了使它这一行是回文的，相当于要通过操作后使 $4$ 与 $1$ 相同；为了使它这一列是回文的，相当于要通过操作后使 $9$ 与 $1$ 相同。对于 $9$ 与 $4$ 来说，有需要和 $18$ 相同。那么最后也就是让这四个数字相同。

为什么说是最多四个数呢？因为有可能出现像 $6$ 和 $7$ 这样的只有两个数字的情况，我们可以用一个 `bool` 数组来标记一下。

那么如何用 **最少** 的操作使几个数字相同，也就是使 $|x-a_1|+|x-a_2|+|x-a_3|+|x-a_4|$ 最小。这里就是数学问题了，$x$ 取 $a$ 的 **中位数** 时最小。

## 三、代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
    ll sum = 0, ff = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') {
            ff = -1;
        }
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
    	sum = sum * 10 + ch - 48;
        ch = getchar();
    }
    return sum * ff;
}

void write(ll x) {
	 if(x < 0) {
		putchar('-');
		x = -x;
	 }
	 if(x > 9)
		write(x / 10);
	 putchar(x % 10 | 48);
}

const int N = 101;
int n, m, t, cnt;
bool mp[N][N];
ll a[N][N], ans, tmp[7];

int main() {
	t = read();
	while(t--) {
		memset(mp, false, sizeof(mp));
		ans = 0;
		n = read(), m = read();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				a[i][j] = read();
		
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(!mp[i][j]) {
					mp[i][j] = true;
					cnt = 0;
					tmp[++cnt] = a[i][j];
					if(!mp[n - i + 1][j])
						mp[n - i + 1][j] = true, tmp[++cnt] = a[n - i + 1][j];
					if(!mp[i][m - j + 1])
						mp[i][m - j + 1] = true, tmp[++cnt] = a[i][m - j + 1];
					if(!mp[n - i + 1][m - j + 1])
						mp[n - i + 1][m - j + 1] = true, tmp[++cnt] = a[n - i + 1][m - j + 1];
					sort(tmp + 1, tmp + 1 + cnt);
					int mid = (cnt + 1) / 2;
					for(int i = 1; i <= cnt; i++)
						ans += abs(tmp[i] - tmp[mid]);
				}
		write(ans), puts("");
	}
    return 0;
}


```


---

## 作者：sodak (赞：1)

## 思路分析
易发现，当前位置上的数，最多与三个数有关，所以问题就转化成了，在数轴上找一个数与这四个数的距离之和最近，显然这个数就是这四个数的中位数，然后就能解决整个矩阵了

## 代码
```cpp

#include<bits/stdc++.h>
#define gc getchar()
#define re register 
#define ll long long
#define int ll
#define getch while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=gc;}
#define getnu while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=gc;}
using namespace std;
inline ll read(){ll s=0,f=1;char ch=gc;getch;getnu;return s*f;}
const int maxn=100+10;
int a[maxn][maxn];
int sta[5],top;
int get(int a,int b,int c,int d){
	top=0;
	sta[++top]=a;
	sta[++top]=b;
	sta[++top]=c;
	sta[++top]=d;
	sort(sta+1,sta+top+1);
	return sta[2];
}
signed main(){
	int T=read();
	while(T--){
		int n=read(),m=read();
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=read();
		int ans=0;
		for(int i=1;i<=n/2;i++){
			for(int j=1;j<=m/2;j++){
				int a1=a[i][j],a2=a[i][m-j+1],a3=a[n-i+1][j],a4=a[n-i+1][m-j+1];
				int ave=get(a1,a2,a3,a4);
				ans+=abs(ave-a1)+abs(ave-a2)+abs(ave-a3)+abs(ave-a4);
				a[i][j]=a[i][m-j+1]=a[n-i+1][j]=a[n-i+1][m-j+1]=ave;
			}
		}
		if(n%2){
			for(int j=1;j<=m/2;j++){
				int a1=a[n/2+1][j],a2=a[n/2+1][m-j+1];
				int ave=a1;
				ans+=abs(ave-a1)+abs(ave-a2);
				a[n/2+1][j]=a[n/2+1][m-j+1]=ave;
			}
		}
		if(m%2){
			for(int i=1;i<=n/2;i++){
				int a1=a[i][m/2+1],a2=a[n-i+1][m/2+1];
				int ave=a2;
				ans+=abs(ave-a1)+abs(ave-a2);
				a[i][m/2+1]=a[n-i+1][m/2+1]=ave;
			}
		}
		printf("%lld\n",ans);
	}
}
```


---

## 作者：7KByte (赞：1)

我们发现对于一个不在中轴线上的点，它最终要与另外三个点相同。这三个点分别是关于纵向中轴线对称点，关于横向中轴线对称点，关于中心点中心对称的点。

现在我们要花最小代价使四个数相等，经典模型是将四个数变为中位数，这里的中位数就取四个数中的次大值。

当$n$或$m$为奇数时，特殊考虑中轴线上的点，中轴线上的点只用和另外一个点相同。

当$n$和$m$都为奇数时，中心点不用与任何其他点相同，不用特判。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 105
using namespace std;
int a[N][N],n,m;long long ans;
long long calc(long long x,long long y,long long u,long long v){
	long long c[4];c[0]=x;c[1]=y;c[2]=u;c[3]=v;
	sort(c,c+4);long long sum=0;
	rep(i,0,3)sum+=abs(c[1]-c[i]);
	return sum;
}
void solve(){
	scanf("%d%d",&n,&m);ans=0;
	rep(i,1,n)rep(j,1,m)scanf("%d",&a[i][j]);
	rep(i,1,n>>1)rep(j,1,m>>1)ans+=calc(a[i][j],a[i][m-j+1],a[n-i+1][j],a[n-i+1][m-j+1]);
	if(n&1){
		rep(i,1,m>>1)ans+=abs(a[(n+1)>>1][i]-a[(n+1)>>1][m-i+1]);
	}
	if(m&1){
		rep(i,1,n>>1)ans+=abs(a[i][(m+1)>>1]-a[n-i+1][(m+1)>>1]);
	}
	printf("%lld\n",ans);
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：ql12345 (赞：1)

## [Codeforces Round #675 (Div. 2) B](https://codeforces.com/contest/1422/problem/B)

有一个矩阵，每次可以让一个元素加1或减1，求最少次数使得矩阵行列回文

### Solution：

显然对每个位置，要求的回文中与它有关的只有至多4个点，所以找出这4个点，找出其平均数，将所有数都变成其平均数即可

然鹅，__这个解法是错的！__

为什么错呢？这也使考场上的我百思不得其解！不可能呀？

看这个样例：

```
1
2 2
9 6
10 9
```

它的答案是多少？

按照我们刚刚的方法算出来是把所有数都变为8（平均数下取整为8），也就是答案为6

但是，如果把所有数都变为9，答案为4！

问题出在了“我们在将平均数上下取整的时候并不精确，实际上这个应该上取整还是下取整并不只与它%4的余数有关，还与小于这个平均数的数的个数与大于这个平均数的个数有关！”

换句话说，其实应该是**中位数！**

于是，对于每一个这4个数，我们得到他们对答案的贡献：

将这四个数放入b数组从小到大排序

```cpp
ans+=abs(b[4]-b[2])+abs(b[3]-b[2])+abs(b[2]-b[2])+abs(b[1]-b[2])
```

取绝对值得：

```cpp
ans+=b[4]+b[3]-b[2]-b[1]
```

实际情况中还会有一些靠近中间的数出现“4个数有重叠”的现象，我们还像这样记录答案，最后ans/=4的时候对这些数也是适用的，读者可以自己手模验证

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[110][110],b[7];
signed main(){
	int t;cin>>t;
	while(t--){
		int n,m,ans=0;cin>>n>>m;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)cin>>a[i][j];
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j){
				b[1]=a[i][j],b[2]=a[n-i+1][j],b[3]=a[n-i+1][m-j+1],b[4]=a[i][m-j+1];
				sort(b+1,b+5);
				ans+=b[4]+b[3]-b[1]-b[2];
			}
		cout<<ans/4<<endl;
	}
	return 0;
}
```

# 记得CF的题都要#define int long long!!!

---

## 作者：YYen (赞：0)

### 思路：构造
假设原矩阵为 $ a_{i,j} $ ，本题解题思路是构造出来一个符合题目要求的行列回文矩阵 $ b_{i,j} $ ，然后使得 $ \sum abs(a_{i,j}-b_{i,j}) $ 最小。
另外要留意到，当行列回文矩阵已经生成之后，必定存在 $ b_{i,j} = b_{i,m+1-j} = b_{n+1-i,j} = b_{n+1-i,m+1-j} $ ，其中 $ n $ 为行数， $ m $ 为列数。

举一个具体的例子：假如 $ n = 4$ ， $ m = 4 $ 的行列回文矩阵 $ b_{i,j} $：

$$\begin{bmatrix}
1 & 2 & 2 & 1 \\
3 & 4 & 4 & 3 \\
3 & 4 & 4 & 3 \\
1 & 2 & 2 & 1 \\
\end{bmatrix}$$
其中 $ b_{1,1} = b_{1,4} = b_{4,1} = b_{4,4} $ ，其他位置也是同理。

接下来就是考虑要如何根据 $ a_{i, j} $ 构造 $ b_{i, j} $ 了。我一开始的想法，是计算 $ a_{i,j} $ 、 $ a_{i,m+1-j} $ 、 $ a_{n+1-i,j} $ 、 $ a_{n+1-i,m+1-j} $ 的平均值填入到 $ b_{i,j} $ 及其对应另外三个位置，后来想一想这种填法不一定正确。正确填法应该是**找出  $ a_{i,j} $ 、 $ a_{i,m+1-j} $ 、 $ a_{n+1-i,j} $ 、 $ a_{n+1-i,m+1-j} $ 中的第2大和第3大的数，把任意在第2大和第3大之间的整数填入到 $ b_{i,j} $ 及其对应另外三个位置**就可以了（这个应该比较容易想明白，就不给证明了）。
### 代码
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;
LL a[105][105];
LL b[105][105];
LL s[10];

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
		
        for (int i = 1; i <= ceil(n / 2.0); i++)
        {
            for (int j = 1; j <= ceil(m / 2.0); j++)
            {
                s[1] = a[i][j];
                s[2] = a[i][m + 1 - j];
                s[3] = a[n + 1 - i][j];
                s[4] = a[n + 1 - i][m + 1 - j];
                sort(s + 1, s + 4 + 1); // 排序找出第2大和第3大的数
                b[i][j] = s[2]; // 填入第2大
                b[i][m + 1 - j] = s[2]; // 填入第2大
                b[n + 1 - i][j] = s[2]; // 填入第2大
                b[n + 1 - i][m + 1 - j] = s[2]; // 填入第2大
            }
        }
        // 计算原矩阵和回文矩阵的元素差的绝对值之和
        LL ans = 0;
        for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans += abs(a[i][j] - b[i][j]);
        cout << ans << endl;
    }
    return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

观察到其实在大多数情况下每四个数是绑在一起的，它们只会互相影响。    
除非是在行/列为奇数时才会呈两两配对状。        

而我们此时只需要解决四/两个数的子问题即可。这个在数轴上随便画一画就出来了，初一数学。         
       
所以我们特判一下两个数的子问题即可：        

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 105;
int n,m,a[Len][Len];
long long ans;
int A[8];
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		ans = 0;
		scanf("%d %d",&n,&m);
		for(int i = 1 ; i <= n ; i ++)
			for(int j = 1 ; j <= m ; j ++) scanf("%d",&a[i][j]);
		for(int i = 1 ; i <= (n + 1) / 2 ; i ++)
		{
			for(int j = 1 ; j <= (m + 1) / 2 ; j ++)
			{
				A[1] = a[i][j] , A[2] = a[i][m - j + 1] , A[3] = a[n - i + 1][j] , A[4] = a[n - i + 1][m - j + 1];
				sort(A + 1 , A + 1 + 4);//printf("%d %d %d %d\n",A[1],A[2],A[3],A[4]);
				if((n % 2 == 1 && i == (n + 1) / 2) || (m % 2 == 1 && j == (m + 1) / 2)) ans += A[3] - A[2]; 
				else ans += A[2] - A[1] + A[3] - A[2] + A[4] - A[2];
			}	
		}	
		printf("%lld\n",ans);
	}
	
	return 0;
}
```

---

