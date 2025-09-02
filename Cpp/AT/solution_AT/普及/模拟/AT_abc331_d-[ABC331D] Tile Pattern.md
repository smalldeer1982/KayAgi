# [ABC331D] Tile Pattern

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc331/tasks/abc331_d

縦横 $ 10^9 $ マスのグリッドがあります。上から $ i\ +\ 1 $ 行目、左から $ j\ +\ 1 $ 列目 $ (0\ \leq\ i,\ j\ \lt\ 10^9) $ にあるマスを $ (i,\ j) $ と呼びます。(通常と異なる index の割り当て方に注意してください。)  
 各マスは黒マスか白マスのいずれかです。マス $ (i,\ j) $ の色は文字 $ P[i\ \bmod\ N][j\ \bmod\ N] $ によって表されて、`B` ならばマス $ (i,\ j) $ は黒マス、`W` ならば白マスです。ここで $ a\ \bmod\ b $ は $ a $ を $ b $ で割った余りを意味します。

$ Q $ 個のクエリが与えられるので順に処理してください。  
 各クエリでは $ 4 $ つの整数 $ A,\ B,\ C,\ D $ が与えられるので、$ (A,\ B) $ を左上隅、$ (C,\ D) $ を右下隅とする長方形領域に含まれる黒マスの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ P[i][j] $ は `W` または `B`
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A\ \leq\ C\ \lt\ 10^9 $
- $ 0\ \leq\ B\ \leq\ D\ \lt\ 10^9 $
- $ N,\ Q,\ A,\ B,\ C,\ D $ は全て整数
 
### Sample Explanation 1

グリッドの左上部分を図示すると次の図のようになります。 !\[image\](https://img.atcoder.jp/abc331/2c3ff3c4018817a0839f1fbe0e7c431d.jpg) $ 1 $ 番目のクエリについて、$ (1,\ 2) $ を左上隅、$ (3,\ 4) $ を右下隅とする長方形領域は図の赤い枠線に囲まれた部分で、領域に含まれる黒マスの個数は $ 4 $ 個です。 $ 2 $ 番目のクエリについて、$ (0,\ 3) $ を左上隅、$ (4,\ 5) $ を右下隅とする長方形領域は図の青い枠線に囲まれた部分で、領域に含まれる黒マスの個数は $ 7 $ 個です。

## 样例 #1

### 输入

```
3 2
WWB
BBW
WBW
1 2 3 4
0 3 4 5```

### 输出

```
4
7```

## 样例 #2

### 输入

```
10 5
BBBWWWBBBW
WWWWWBBBWB
BBBWBBWBBB
BBBWWBWWWW
WWWWBWBWBW
WBBWBWBBBB
WWBBBWWBWB
WBWBWWBBBB
WBWBWBBWWW
WWWBWWBWWB
5 21 21 93
35 35 70 43
55 72 61 84
36 33 46 95
0 0 999999999 999999999```

### 输出

```
621
167
44
344
500000000000000000```

# 题解

## 作者：wmrqwq (赞：11)

# 题目链接：

[[ABC331D] Tile Pattern](https://www.luogu.com.cn/problem/AT_abc331_d)

# 题意简述：

有一个有 $10^9 \times 10^9$ 个方格的网格。每个方格都是黑色或白色，其中 `B` 表示黑色，`W` 表示白色，$a_{0,0} \sim a_{{n-1},{n-1}}$ 的方格颜色是给定的，之后所有的方格 $(i,j)$ 的颜色由 $a_{{i \bmod n},{j \bmod n}}$ 的颜色表示。

# 解题思路：

前置知识：前缀和。

如果你不知道什么是前缀和的话，那么下面的内容或许能帮到你。

首先，前缀和用于解决一些区间加问题。

有一个长度为 $n$ 的序列，你需要进行 $q$ 组询问，每次询问 $l \sim r$ 之间的区间和 $(1 \le n,q \le 10^5)$。

首先，如果直接暴力的话，时间复杂度为 $O(nq)$，显然不可取，但是如果这时我们用 $sum_i$ 表示 $a_1 + a_2 + \dots + a_i$ 的值，查询时结果就为 $sum_r - sum_{l-1}$，单次查询复杂度 $O(1)$。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,l,r,a[100010],sum[100010];
#define lowbit(x) x&-x
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i],sum[i]=sum[i-1]+a[i];
	while(q--)
		cin>>l>>r,cout<<sum[r]-sum[l-1]<<endl;
	QwQ;
}
```

假如我们把这个序列改成矩阵，也是一样的道理：

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,q,a[2010][2010],sum[2010][2010],x,xx,y,yy;
#define lowbit(x) x&-x
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j],sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
	while(q--)
		cin>>x>>y>>xx>>yy,cout<<sum[xx][yy]+sum[x-1][y-1]-sum[x-1][yy]-sum[xx][y-1]<<endl;
	QwQ;
}
```

看懂了前置知识后，我们就可以来做这道题了。

我们可以把询问的矩阵拆成 $4$ 个部分：

1. 整块的部分；
2. 行数完整，列数不完整的部分；
3. 列数完整，行数不完整的部分；
4. 行数，列数都不完整的部分。

然后我们使用前缀和维护一下这 $4$ 个部分就做完了。

# 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,y,xx,yy,a[1010][1010],sum[1010][1010];
char c;
long long f(long long x,long long y)
{
	if(x<=n && y<=n)
		return sum[x][y];
	else
		return (x/n)*(y/n)*sum[n][n]+(y/n)*sum[x%n][n]+(x/n)*sum[n][y%n]+sum[x%n][y%n];
}
/*
001 001
110 110
010 010
001 001
010 010
010 010
4,5: 5
4,2: 1
*/
#define lowbit(x) x&-x
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			cin>>c;
			if(c=='W')
				a[i][j]=0;
			else
				a[i][j]=1;
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
		}
	while(m--)
	{
		cin>>x>>y>>xx>>yy;
		x++,y++,xx++,yy++;
	//	cout<<"xx,yy:"<<f(xx,yy)<<" "<<"xx,y-1:"<<f(xx,y-1)<<"x-1,yy: "<<f(x-1,yy)<<"x-1,y-1:"<<f(x-1,y-1)<<endl;
		cout<<f(xx,yy)-f(xx,y-1)-f(x-1,yy)+f(x-1,y-1)<<endl;
	}
	QwQ;
}
```

---

## 作者：Phartial (赞：8)

首先你可以通过容斥将一次询问的矩形拆成 $\mathcal{O}(1)$ 个前缀矩形。然后你考虑一次前缀矩形会长啥样：

![D](https://cdn.luogu.com.cn/upload/image_hosting/bwk2n7iw.png)

我们只需要知道一个黄色矩形、绿色矩形、蓝色矩形和紫色矩形中 `B` 的数量。而这几个矩形都是 $P$ 的一个前缀矩阵，对 $P$ 做一次二维前缀和即可 $\mathcal{O}(1)$ 得到四种颜色的矩阵中的 `B` 的数量，乘上这四种颜色的矩阵的出现次数即可。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 1001;

int n, q;
LL s[kN][kN];

LL Q(int x, int y) {
  if (x < 0 || y < 0) {
    return 0;
  }
  return s[n - 1][n - 1] * (x / n) * (y / n) + s[n - 1][y % n] * (x / n) + s[x % n][n - 1] * (y / n) + s[x % n][y % n];
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char ch;
      cin >> ch;
      s[i][j] = (ch == 'B');
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < n; ++j) {
      s[i][j] += s[i][j - 1];
    }
  }
  for (int j = 0; j < n; ++j) {
    for (int i = 1; i < n; ++i) {
      s[i][j] += s[i - 1][j];
    }
  }
  for (int xl, xr, yl, yr; q--; ) {
    cin >> xl >> yl >> xr >> yr;
    cout << Q(xr, yr) - Q(xl - 1, yr) - Q(xr, yl - 1) + Q(xl - 1, yl - 1) << '\n';
  }
  return 0;
}
```


---

## 作者：CQ_Bab (赞：2)

# 思路
其实挺一眼的吧。我们其实很容易找出规律，如果对于一块矩阵我们可以分成四个部分，如下图。
![](https://img.atcoder.jp/abc331/68901ebfe4b324117324d6d8f1c3ff72.jpg)

这里我们可以用到一种前缀和相减的思想，将总的算出来再减去多余的。

然后我们只需要分别算贡献即可。

- 首先是 A 部分，我们可以发现就是对于一个矩阵中与原矩阵可完全覆盖的位置，那么就是原矩阵的贡献乘上 $\lfloor\frac{l}{n}\rfloor\times\lfloor\frac{r}{n}\rfloor$，这个应该很好理解。

- 对于 B 部分我们可以发现其实高和 A 是一样的，那么只需要求长即可，就为 $S_{0,0,(l+1)\bmod n-1,n-1}\times \lfloor\frac{r}{n}\rfloor$ 这里的 $S_{a,b,c,d}$ 表示原矩阵从 $a,b$ 到 $c,d$ 的总贡献。

- 对于 C 部分，我们可以用与 B 部分同理的方法解决，最后可得出贡献为 $S_{0,0,n-1,(r+1)\bmod n-1}\times \lfloor\frac{l}{n}\rfloor$。

- 对于最后的 D 部分，可以发现其长和宽分别和 B 和 C 部分相同那么也很容易得出公式为 $S_{0,0,(l+1)\bmod n-1,(r+1)\bmod n-1}$。

那么我们根据前缀和的思想可以得出对于一个矩阵 $a,b,c,d$ 其答案为 $A_{c,d}-A_{a-1,d}-A_{c,b-1}+A_{a-1,b-1}$，这里的 $A_{i,j}$ 表示为从大矩阵的 $0,0$ 到 $i,j$ 的数量和。
# 代码
其实也挺短的。
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
const int N=1e3+10;
int n,m;
int c[N][N],cnt;
char ma[N][N];
int s(int x,int y) {
	if(x<0||y<0||x>=n||y>=n) return 0;
	return c[x][y];
}
int k(int a,int b,int c,int d) {
	return s(c,d)-s(a-1,d)-s(c,b-1)+s(a-1,b-1);
}
int q(int x,int y) {
	if(x<0||y<0) return 0;
	int tot=(x+1)/n,to=(y+1)/n;
	int res=cnt*tot*to;
	int t1=(x+1)%n-1,t2=(y+1)%n-1;
	res+=to*k(0,0,t1,n-1)+tot*k(0,0,n-1,t2)+k(0,0,t1,t2);
	return res;
}
fire main() {
	in(n),in(m);
	rep(i,0,n-1) rep(j,0,n-1) cin>>ma[i][j],c[i][j]=(ma[i][j]=='B');
	 rep(i,0,n-1) rep(j,0,n-1) c[i][j]+=s(i-1,j)+s(i,j-1)-s(i-1,j-1);
	 cnt=s(n-1,n-1);
	 while(m--) {
	 	int a,b,c,d;
	 	cin>>a>>b>>c>>d;
	 	cout<<q(c,d)-q(a-1,d)+q(a-1,b-1)-q(c,b-1)<<endl;
	 }
	return false;
}
```

---

## 作者：CWzwz (赞：2)

[ABC331D Tile Pattern](https://www.luogu.com.cn/problem/AT_abc331_d) 题解

[Atcoder](https://atcoder.jp/contests/abc331/tasks/abc331_d)

------------

题意简单，因为格子 $(i,j)$ 的颜色是 $P[i\operatorname{mod}n][j\operatorname{mod}n]$，容易看出其实整个网格就是 $P$ 的重复。

然后就很容易了。

分割一下，黄色部分是整块的 $n\times n$，其他部分单独计算。

实现的时候，可以二维前缀和维护块内矩形和。因为前缀和的原因，这里我把坐标值域从 $[0,10^9)$ 移到了 $[1,10^9]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/2w56z4o9.png)

时间 $O(n^2+q)$，空间 $O(n^2)$。

```cpp
//Problem: abc331d
#include<iostream>
#include<algorithm>
#include<string.h>
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define i32 INT_MAX
#define i64 LONG_LONG_MAX
#define pii std::pair<int, int>
#define pll std::pair<long long, long long>
#define pb push_back
#define fore(i,u,v) for(int i=head[u],v;i;i=e[i].nxt)
typedef long long ll;
const int N = 1e3 + 10;
ll read(){ll x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}return x*f;}
void print(ll x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10+48);}
char gc(){char c=getchar();while(c==' '||c=='\n')c=getchar();return c;}
void pc(char Char){std::putchar(Char);}

int n, q;
int map[N][N];
int Sum[N][N];

int query(int x1, int y1, int x2, int y2) {
    return Sum[x2][y2] + Sum[x1 - 1][y1 - 1] - Sum[x2][y1 - 1] - Sum[x1 - 1][y2];
}

int main() {
    std::cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            char c = gc();
            if(c == 'B') map[i][j] = 1;
            else map[i][j] = 0;
            Sum[i][j] = map[i][j] + Sum[i - 1][j] + Sum[i][j - 1] - Sum[i - 1][j - 1];
        }
    }
    while(q--) {

        ll x1 = read() + 1, y1 = read() + 1, x2 = read() + 1, y2 = read() + 1;
        ll X1 = (x1 - 1) / n * n + n + 1, Y1 = (y1 - 1) / n * n + n + 1, X2 = (x2 - 1) / n * n, Y2 = (y2 - 1) / n * n; // 求出浅黄色部分位置

        ll ans = ((X2 - X1 + 1) / n) * ((Y2 - Y1 + 1) / n) * Sum[n][n];                           // 这个是浅黄色部分的和
        ans += query(x1 - (X1 - n) + 1, y1 - (Y1 - n) + 1, n, n) + query(1, 1, x2 - X2, y2 - Y2); // 蓝色（左上，右下）
        ans += query(x1 - (X1 - n) + 1, 1, n, y2 - Y2) + query(1, y1 - (Y1 - n) + 1, x2 - X2, n); // 蓝色（左下，右上）
        ans += (Y2 - Y1 + 1) / n * (query(x1 - (X1 - n) + 1, 1, n, n) + query(1, 1, x2 - X2, n)); // 绿色部分
        ans += (X2 - X1 + 1) / n * (query(1, y1 - (Y1 - n) + 1, n, n) + query(1, 1, n, y2 - Y2)); // 红色部分

        print(ans); puts("");

    }
    return 0;
}
```

---

## 作者：xu222ux (赞：2)

# [D - Tile Pattern](https://atcoder.jp/contests/abc331/tasks/abc331_d)

## 思路

二维前缀和我就不多说了，相信大家都会，但还是要给个图。

![](https://i.postimg.cc/T35BpNRx/2024-01-04-183701.png)


这个图是求红色矩形面积。

会发现图中不管是哪个矩形，其坐上角的点都是 $(0,0)$。

然后就要想，咋算一个左上角是 $(0,0)$ 矩形？我们可以把它大卸八块成这样。



![](https://img.atcoder.jp/abc331/e8da0bfe389093ed4cc50c44ebb7b5bb.jpg) 

然后就是一道纯模拟了，把这些块分别算就行。


## code
```cpp
#include<bits/stdc++.h>
using namespace std;
# define int long long
int n,q;
int sum[1003][1003],cntall;
int getsum(int x,int y){
	return (x/n)*(y/n)*cntall+(x/n)*sum[n-1][y%n]+(y/n)*sum[x%n][n-1]+sum[x%n][y%n];
}
signed main(){
	cin>>n>>q;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			char a;cin>>a;
			if(j!=0)sum[i][j]+=sum[i][j-1];
			if(i!=0)sum[i][j]+=sum[i-1][j];
			if(i!=0&&j!=0)sum[i][j]-=sum[i-1][j-1];
			if(a=='B')sum[i][j]++,cntall++;
		}
	}
	while(q--){
		int x,y,xx,yy;cin>>x>>y>>xx>>yy;
		cout<<getsum(xx,yy)-getsum(x-1,yy)-getsum(xx,y-1)+getsum(x-1,y-1)<<endl;
	}
	return 0;
}
```

---

## 作者：yhx0322 (赞：1)

## Description
给你一个 $10^9 \times 10^9$ 的矩阵，并给出字符数组 $P$，大小为 $n
 \times n$。

正方形中 $(i,j)$ 格子的颜色为 $P[i \bmod n][j \bmod n]$。

每次询问给出四个变量 $A,B,C,D$，表示左上角坐标 $(A,B)$ 和右下角坐标 $(C,D)$ 的正方形中黑色格子的数量。

## Solution
思想不难，难在代码调试与边界讨论。

对 $n \times n$ 的矩阵记录二维前缀和 $sm_{i,j}$。

假设目前要求 $\text{query}(x,y)$，对 $x,y$ 可以分三种情况讨论：

- 若 $x \ge n,y \ge n$，则答案等于
$$sm_{n-1,n-1} \times \lfloor \dfrac{x}{n} \rfloor \times \lfloor \dfrac{y}{n} \rfloor+\text{query}(x \bmod n,y)+\text{query}(x-(x \bmod n)-1,y \bmod n)$$

- 若 $x \ge n$，则答案等于
$$sm_{n-1,y} \times \lfloor \dfrac{x}{n} \rfloor  +\text{query}(x \bmod n,y)$$
- 若 $y \ge n$，则答案等于
$$sm_{x,n-1} \times \lfloor \dfrac{y}{n} \rfloor+\text{query}(x,y \bmod n)$$
- 否则，答案等于 $sm_{x,y}$。

## Code
```cpp
#include <bits/stdc++.h>

using ll = long long;

using namespace std;

const int N = 1e3 + 10;
int A, B, C, D, n, p[N][N];
char s[N];
ll sm[N][N];

ll query(int x, int y) {
    if (x < 0 || y < 0) return 0;
    if (x >= n && y >= n)
        return sm[n][n] * (x / n) * (y / n) + query(x % n, y) + query(x - (x % n) - 1, y % n);
    if (x >= n)
        return sm[n][y + 1] * (x / n) + query(x % n, y);
    if (y >= n)
        return sm[x + 1][n] * (y / n) + query(x, y % n);
    return sm[x + 1][y + 1];
}

int main() {
    scanf("%d", &n);
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= n; ++j) {
            p[i][j] = (s[j] == 'B');
            sm[i][j] = p[i][j] + sm[i - 1][j] + sm[i][j - 1] - sm[i - 1][j - 1];
        }
    }
    while (q--) {
        scanf("%d%d%d%d", &A, &B, &C, &D);
        printf("%lld\n", query(C, D) - query(A - 1, D) - query(C, B - 1) + query(A - 1, B - 1));
    }
    return 0;
}
```

---

## 作者：解方橙 (赞：1)

来一个直接硬做的。

第一眼看到题：这题我会！把要求的矩形拆了不就做完了？

于是把矩形拆成四个角、四条边和中间的大块。

左上角为单位方阵的右下角，右上角为单位方阵的左下角，左下角为单位方阵的右上角，右下角为单位方阵的左上角。上边为一堆单位方阵的下边，左边为一堆单位方阵的右边，下边为一堆单位方阵的上边，右边为一堆单位方阵的左边。中间为一堆整的单位方阵。全部加起来，再特判一下长/宽不满一个方阵的情况，就做完了。听起来是不是很简单呢？

于是就做完了。上代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1010;
int n,q,jz[N][N],pre[N][N];
char s[N];
int sq(int a,int b,int c,int d){
    return pre[c][d]-pre[a-1][d]-pre[c][b-1]+pre[a-1][b-1];
}
int to(int x){
    if(x%n==0) return n;
    return x%n;
}
signed main(){
    scanf("%lld%lld",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=n;j++) jz[i][j]=pre[i][j]=(s[j]=='B');
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) pre[i][j]+=pre[i][j-1];
    for(int j=1;j<=n;j++) for(int i=1;i<=n;i++) pre[i][j]+=pre[i-1][j];
    while(q--){
        int a,b,c,d;scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
        a++;b++;c++;d++;
        //cerr<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
        int ans=0;
        int e=(a%n==0)?a:a-a%n+n;
        int f=(b%n==0)?b:b-b%n+n;
        int g=(c%n==0)?c-n:c-c%n;
        int h=(d%n==0)?d-n:d-d%n;
        //cerr<<e<<" "<<f<<" "<<g<<" "<<h<<endl;
        if(e>=c&&f>=d){
            //cerr<<1<<endl;
            printf("%lld\n",sq(to(a),to(b),to(c),to(d)));
            continue;
        }
        if(e>=c){
            //cerr<<2<<endl;
            ans+=sq(to(a),to(b),to(c),n)+sq(to(a),1,to(c),to(d));
            ans+=sq(to(a),1,to(c),n)*(h-f)/n;
            printf("%lld\n",ans);
            continue;
        }
        if(f>=d){
            //cerr<<3<<endl;
            ans+=sq(to(a),to(b),n,to(d));
            ans+=sq(1,to(b),to(c),to(d));
            ans+=sq(1,to(b),n,to(d))*(g-e)/n;
            printf("%lld\n",ans);
            continue;
        }
        //cerr<<to(a)<<" "<<to(b)<<" "<<to(c)<<" "<<to(d)<<endl;
        ans+=sq(to(a),to(b),n,n)+sq(1,to(b),to(c),n)+sq(to(a),1,n,to(d))+sq(1,1,to(c),to(d));
        //cerr<<ans<<endl;
        ans+=sq(1,to(b),n,n)*(g-e)/n;
        ans+=sq(to(a),1,n,n)*(h-f)/n;
        ans+=sq(1,1,to(c),n)*(h-f)/n;
        ans+=sq(1,1,n,to(d))*(g-e)/n;
        ans+=(g-e)/n*(h-f)/n*pre[n][n];
        printf("%lld\n",ans);
    }
}

```

---

## 作者：naroanah (赞：1)

首先把询问全部 $+1$，让下标从 $1$ 开始。

利用容斥，把询问变成询问左上角为 $(1,1)$，右下角为 $(x,y)$ 的矩形中黑色块个数，记作 $f(x, y)$，最后答案即为 $f(C,D) - f(A - 1,D) -f(C, B - 1) + f(A - 1, B - 1)$。

考虑如何计算 $f(x, y) $，发现 $x, y$ 的范围很大，而 $n$ 的范围很小，在所询问的矩形中，会产生很多 $n \times n$ 的矩形，这部分答案可以简单统计。设 $n \times n$ 的矩形中有 $cnt$ 个黑色块，$p = \dfrac{x}{n}, q = \dfrac{y}{n}$ ，这部分的贡献即为 $p \times q \times cnt$。

接下来计算剩余部分的贡献，把 $x, y$ 分别对 $n$ 取模。此类题画图找规律很重要。如图，下面横着的贡献是 $f(x, n) \times q$，右边竖着的贡献是 $f(n,y) \times p$，最后一块右下的贡献是 $f(x,y)$，全部加起来即可。



![fHJljWypYreihqv.png](https://s2.loli.net/2023/12/02/fHJljWypYreihqv.png)

```cpp
#include<bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define req(i, r, l) for(int i = (r); i >= (l); i--)
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define fi first
#define se second
#define all(x) begin(x), end(x)
using namespace std;
constexpr int N = 1e5 + 10, inf = 0x3f3f3f3f, INF = 0x7f7f7f7f; constexpr double eps = 1e-9;
int n, q, cnt;
int sum[1010][1010];
ll q1(int x, int y) {
    ll t1 = x / n, t2 = y / n;
    ll k = 1ll * t1 * t2; ll res = k * cnt;
    x %= n, y %= n; 
    res += sum[x][n] * t2, res += sum[n][y] * t1;
    res += sum[x][y];
    return res;
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> q;
    rep(i, 1, n) {
        rep(j, 1, n) {
            char c; cin >> c;
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (c == 'B');
            if(c == 'B') cnt++;
        }
    }
    while(q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d; a++, b++, c++, d++;
        cout << q1(c, d) - q1(a - 1, d) - q1(c, b - 1) + q1(a - 1, b - 1) << "\n";
    }
    return 0;
}
```

---

