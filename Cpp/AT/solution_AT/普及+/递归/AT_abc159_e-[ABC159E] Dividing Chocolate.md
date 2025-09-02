# [ABC159E] Dividing Chocolate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc159/tasks/abc159_e

縦 $ H $ マス、横 $ W $ マスのグリッドに区切られたチョコレートがあります。

上から $ i $ 行目、左から $ j $ 列目にあるマス $ (i,j) $ のチョコレートは、$ S_{i,j} $ が `0` のとき普通のチョコレートであり、`1` のときホワイトチョコレートです。

このチョコレートに対して、マスの境界に沿った直線によってグリッド全体の端から端まで割る操作を何度か行い、いくつかのブロックに分割します。

分割後のどのブロックにもホワイトチョコレートのマスが $ K $ マス以下しか含まれないようにするためには、最小で操作を何回行う必要があるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H\ \leq\ 10 $
- $ 1\ \leq\ W\ \leq\ 1000 $
- $ 1\ \leq\ K\ \leq\ H\ \times\ W $
- $ S_{i,j} $ は `0` か `1`

### Sample Explanation 1

例えば左の図のように $ 1 $ 行目と $ 2 $ 行目の間と、$ 3 $ 列目と $ 4 $ 列目の間の $ 2 $ か所で割ればよいです。 右の2つの図のような割り方はできないことに注意してください。 !\[図\](https://img.atcoder.jp/ghi/ac90dd542639c04402125403b1c319d7.png)

### Sample Explanation 2

操作を行う必要はありません。

## 样例 #1

### 输入

```
3 5 4
11100
10001
00111```

### 输出

```
2```

## 样例 #2

### 输入

```
3 5 8
11100
10001
00111```

### 输出

```
0```

## 样例 #3

### 输入

```
4 10 4
1110010010
1000101110
0011101001
1101000111```

### 输出

```
3```

# 题解

## 作者：banned_xiejiayun (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc159_e)

话不多说，直接上思路：

每个空格中都可以插一刀，所以对于所有的空位，都有加一刀和不加一刀两种可能，于是就会联想到二进制，进而就是子集枚举（二进制枚举）。

再看看数据范围：

- $ 1\ \leq\ H\ \leq\ 10 $
- $ 1\ \leq\ W\ \leq\ 1000 $

因为子集枚举的时间复杂度是 $2^n$，所以至少对于横向的枚举是没有问题的。

但对于纵向的切割，就得换一个想法了。

这个时候，由于我们只用管列，又力求最少的刀，所以可以使用贪心（~~算法标签写得这么清楚~~）。

循环，从 $1$ 到 $n$，每次累加 $1$ 的个数，如果超过了 $k$ 就添一道，累加变量清零。

总体复杂度 $O(h\times w\times2^h)$，算一下$1024\times10\times1000=10240000$，虽然~~老师告诉我们~~这个时间复杂度很悬，但是时限两秒，是可以过滴。

## AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int s[11][1001];
int ans=0x7ffffff;
char c;
bool flag[11];
int cnt(){
	int _ans=0;//对于这种方案的纵向切割
	int tot=1;//上一次切割的位置+1
	for(int i=1;i<=m;i++){
		int check=0;//检验变量，统计每个区域 1 的个数
		for(int j=1;j<=n;j++){
			check+=s[j][i]-s[j][tot-1];
			if(tot==i&&check>k){
				return 0x7ffffff;
				//如果但是这一列都超出了 k 的大小的话，就没戏了
			}
			if(check>k){
				_ans++;
				tot=i;
				check=0;//注意归零
			}
			if(flag[j]){
				check=0;//从下一行开始，就不属于这个区域了
			}
		}
	}
	return _ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>c;
			s[i][j]=c-'0'+s[i][j-1];
		}
	//子集枚举：
	int U=1<<(n-1);
	for(int i=0;i<U;i++){
		int ii=i,now=n-1,sum=0;
		memset(flag,0,sizeof(flag));
		while(ii){
			if(ii%2){
				flag[now]=1;//标记那些位置切了一刀
				sum++;//统计横向切了几刀
			}
			ii/=2;now--;
		}
		ans=min(ans,cnt()+sum);
	}
	cout<<ans;
	return 0;
}

```



---

## 作者：lihongqian__int128 (赞：6)

我们发现，$h \le10$，而 $w \le1000$，考虑从 $h$ 入手。枚举每两行中间是否切开，再枚举每一列，使用二位前缀和求每一块中 $1$ 的个数，如果这一块中的 $1$ 的个数大于 $k$ 个，说明这一块需要切开，但如果是这一列的和大于 $k$，说明切法不行。每种切法的刀数总和的最小值就是答案。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std ;
int h , w , k , a[15][1005] , s[15][1005] , minn = INT_MAX ;
char c ;
bool p[15] ;
void dfs(int step , int sum)
{
    if(step == h)
    {
    	p[h] = 1 ;
        int lw = 0 ;
        int cnt = 0 ;
        for(int j = 1 ; j <= w ; j++)
        {
        	int lr = 0 ;
            for(int i = 1 ; i <= h ; i++)
            {
                if(p[i])
                {
			int c = s[i][j] - s[i][lw] - s[lr][j] + s[lr][lw] ;
			if(c > k)
			{
				if(j == lw + 1)	return ;
				else
				{
					cnt++ ;
					lw = j - 1 ;
					break ;
				}
			}
			lr = i ;
		}
            }
        }
        minn = min(minn , cnt + sum) ;
        return ;
    }
    p[step] = 1 ;
    dfs(step + 1 , sum + 1) ;
    p[step] = 0 ;
    dfs(step + 1 , sum) ;
}
int main()
{
    cin >> h >> w >> k ;
    for(int i = 1 ; i <= h ; i++)
    {
        for(int j = 1 ; j <= w ; j++)
        {
            cin >> c ;
            a[i][j] = c - '0' ;
            s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j] ;
        }
    }
    dfs(1 , 0) ;
    cout << minn ;
    return 0 ;
}
```

---

## 作者：ctq1999 (赞：6)

考虑暴力，暴力二进制枚举每一个可能的情况，时间复杂度为 $O(2^n \times 2^m)$ ，不能通过此题。

考虑优化，发现 $n$ 的数据范围为 $1 \leq n \leq 10$ ，$2^n$ 可以接受。暴力枚举每个行切割的情况，然后模拟列的情况。若一列加完，一个子矩阵的 $1$ 的数量大于 $k$ ，那么这列的左边需要切割。

每一次枚举行的情况，算出列至少需要多少次切割后，更新 $ans$。

至于怎么根据枚举的 $statment$ 来统计行切割出来的区间（一列列加的时候什么时候要清零开始算下一个区间），本人太菜，竟然没想出来。特别说一下。

新开一个数组 $b[]$ ，$b[i]$ 表示第 $i$ 行属于行切割出来的区间的编号。然后如此初始化：

```
now = 1;
for (int i = 0; i < n; i++) {
        b[i + 1] = now;
        if ((sta >> i) & 1) ++now;
}
```

然后再开一个数组记录和，例如

```
for (int j = 1; j <= n; j++) sum[b[j]] += a[j][i];
```

这样子就解决了。在此膜拜@Froggy提供的代码。

时间复杂度 $O(2^n \times n \times m)$ ，可以通过此题。

```cpp
#include <bits/stdc++.h>

#define MAXN 10010
#define ll long long
#define mod 1000000007

using namespace std;

int n, m, k, tot, ans, sum;

int a[MAXN][MAXN];
int h[MAXN], l[MAXN];
int b[MAXN];
int s[MAXN];

int count(int sta) {
	memset(b, 0, sizeof(b));
	memset(s, 0, sizeof(s));
	int now = 1, res = 0;
	for (int i = 0; i < n; i++) {
		b[i + 1] = now;
		if ((sta >> i) & 1) ++now;
	}
	
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) s[b[j]] += a[j][i];
		bool f = 1;
		for (int j = 1; j <= n; j++)
			if (s[b[j]] > k) {
				res++;
				f = 0;
				break;
			}
		if (!f) {
			memset(s, 0, sizeof(s));
			for (int j = 1; j <= n; j++) {
				s[b[j]] += a[j][i];
				if (s[b[j]] > k) return n + m;
			}	
		}
	}
	return res;
}

int main() {
	int t, now = 0;
	scanf("%d%d%d", &n, &m, &k);
	ans = n + m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c;
			cin >> c;
			a[i][j] = c - '0';
		}
	
	for (int i = 0; i < (1 << (n - 1)); i++) {
		int num = 0;
		for (int j = 0; j < n; j++)
			if ((i >> j) & 1) num++;
		ans = min(ans, count(i) + num);
	} 
	
	cout << ans << endl;
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：6)

### 题目翻译

有一个 $H\times W$ 的矩阵，切若干次，使得每一块中 $1$ 个数 $\leq k$，只能一切到底，问最少用几刀。

### 题目思路

直接暴力枚举每一行每一列绝对不行，复杂度 $\mathcal O(2^{H+W})$。

我们发现 $H$ 很小，我们可以枚举 $H$ 在哪里切割，复杂度 $\mathcal O(2^H)$。其实最多只有 $H-1$ 刀，为了方便描述，统一用 $H$。

接着，我们对于 $W$ 考虑贪心，每一块有尽量多的 $1$，最后肯定花费最小，也是可以证明的。

综上所述，我们枚举 $2^H$ 种方案，接着扫一遍 $W$ 确定切割次数。

时间复杂度 $\mathcal O(2^H\times W\times H)$，可以通过此题。

但是还不完美，如果 $H\leq 15,W\leq 10^6$，明显是会炸掉的。

我们扫 $W$ 时，这里 $1$ 个数肯定是单调不增的，可以考虑进行二分或者倍增来找。这一段的时间复杂度一下子变成了 $\mathcal O(\log W)$，总时间复杂度 $\mathcal O(2^H\times \log W\times H)$。

但上述做法在面对全是 $1$ 时，每次只能前进一步，实际上会退化成 $\mathcal O(W)$。其余数据效果比最初做法时间上较佳。

### 完整代码

代码很长，不贴了，发个链接。

[Code 1](https://atcoder.jp/contests/abc159/submissions/38882298)

[Code 2](https://atcoder.jp/contests/abc159/submissions/38882293)

---

## 作者：Scintilla (赞：3)

[AT传送门](https://atcoder.jp/contests/abc159/tasks/abc159_e) && [洛谷传送门](https://www.luogu.com.cn/problem/AT4897)

### 思路

一看数据范围，$H \leq 10$，$W \leq 1000$，长宽边界不同，肯定是从这里入手的。

考虑将横向的所有切法枚举出来，分别算出答案，再从中取最小值。

对于任意一种切法，可以贪心。从左到右扫一遍，如果某一部分的白巧克力数大于要求就切一刀，最后切的刀数就是横向刀数与竖向刀数的和。

需要注意的是，如果把某一列单独切出来还不能满足要求的话，那么这个方案就是不可行的，不能用来更新最后的答案。

统计白巧克力数可以用前缀和。我代码中的 $sum[i][j]$ 就是第 $i$ 列前 $j$ 小块中白巧克力的个数。

总时间复杂度： $O(2^HHW)$，可以通过此题。

### $Code:$
```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define Rep(i, s, e) for (re int i = s; i <= e; ++i)

const int H = 11;
const int W = 1010;

const int MAXVAL = 1030;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = false; c = getchar();}
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

int h, w, K;
char s[W];

int sum[H][W];
il int Get(int c, int l, int r) {
    return sum[r][c] - sum[l - 1][c];
}

int tot, pos[H], now[H], tp[H];
int ans = 0x3f3f3f3f;

int main() {
    h = read(), w = read(), K = read();
    Rep(i, 1, h) {
        gets(s + 1);
        Rep(j, 1, w) sum[i][j] = sum[i - 1][j] + (s[j] == '1');
    }
    int MAX = (1 << (h - 1)) - 1;
    Rep(i, 0, MAX) {
    	memset(now, 0, sizeof(now));
        tot = 0; int tp_ans = 0;
        Rep(j, 0, h - 2) {
            if (i & (1 << j)) pos[++tot] = j + 1;
        }
        tp_ans = tot, pos[++tot] = h;
        bool failed = false;
        Rep(j, 1, w) {
        	Rep(k, 1, tot) {
        		tp[k] = Get(j, pos[k - 1] + 1, pos[k]);
        		if (tp[k] > K) {failed = true; break;}
			}
			if (failed) break;
        	Rep(k, 1, tot) {
        		now[k] += tp[k];
        		if (now[k] > K) {
        			Rep(l, 1, tot) now[l] = tp[l];
        			++tp_ans; break;
				}
			}
		}
	    if (failed) continue;
        ans = min(ans, tp_ans);
    } 
    return printf("%d", ans) & 0;
}

```

---

## 作者：君のNOIP。 (赞：2)

#### ~~很明显の暴力枚举~~

------------
#### 数据范围：

- $H \le 10$ ， $W\le 1000$

于是我们发现， $H$ 很小，我们可以直接 $O(2^H)$ **暴力枚举横着切**。

然后对于每一种情况，从 $1$ 到 $W$ 遍历一遍，竖着必须切の时候才切，答案取各种情况最小值。

总复杂度： $O(2^H W)$ 

注意：枚举の有些情况可能无解（如横着一刀不切），需特判。


------------
#### 完整代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define MAX_N 200005
#define LL long long
int n,m,k;
string s;
int sum[12][1005];
bool mp[12][1005];
int ans=99999999;
int a[12];

bool check(int cnt,int j,int la){  //判断需不需要切。
	int s=0;
	for(int i=1;i<=cnt;i++){
		s=sum[a[i]][j]-sum[a[i]][la]-sum[a[i-1]][j]+sum[a[i-1]][la];
		if(s>k)return 0;
	}
	return 1;
}

void work(int t){     //枚举竖着切。
	int s=t,la=0;
	a[t+1]=n;
	for(int i=1;i<=m;i++)if(!check(t+1,i,la))s++,la=i-1;
	if(check(t+1,m,m-1))ans=min(ans,s); //细节，最后1列可能超过K个，需特判。
}

void dfs(int now,int t){ //枚举横着切。
	if(now==n){
		work(t);
		return;
	}
	a[t+1]=now,dfs(now+1,t+1);
	dfs(now+1,t);
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=1;j<=m;j++)
			mp[i][j]=s[j-1]-'0',sum[i][j]=sum[i][j-1]+mp[i][j]+sum[i-1][j]-sum[i-1][j-1];
	}
	dfs(1,0);
	cout<<ans;
}

```

------------
### 完结撒花~~~

~~我不会说我考场因为没特判无解の情况 22个点 WA了2个导致暴零。~~


---

## 作者：TLEWA (赞：1)

## 思路

注意到 $H$ 和 $W$ 的数量范围相差极大（$H \le 10,W \le 1000$），我们行的分法可能的方案是 $2^H$，最大为 $1024$，于是我们考虑枚举每一种行上的分法，对于列，我们可以贪心地处理出操作数最小的分法：

显然，在 $1$ 的数量不超过给定上界的情况下，我们每次切割都希望更多列被包含进来，我们可以不断往后扫，直到达到上界才切一刀。对于枚举的每一种方案，我们跑一遍这个贪心，前缀和优化一下 check，最后取最小值输出即可。总时间复杂度 $O(2^HWH)$，可以通过此题。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

bool arr[15][1005];
int w,h,k;
int ans=1000000;

int q[15][1005]; //前缀和 

int get(bitset<15> b) {
	int las=0,cnt=0;
	
	for(int i=1;i<=w;++i) {
		int num=0;
		for(int j=1;j<=h;++j) {
			num+=q[j][i]-q[j][las];
			if(las==i-1 && num>k) return 1000000; //如果切了一刀之后单这一列超过上界则说明在这种行的分法下无解 
			if(num>k) {cnt++,las=i-1,j=0,num=0;} //如果达到了上界就切一刀 
			if(b[j]) num=0;
		}
	}
	
	return cnt;
}

void dfs(bitset<15> b,int now,int cost) { //枚举每一种行的可能方案 
	if(now!=h) {
		dfs(b,now+1,cost);
		b[now]=1;
		dfs(b,now+1,cost+1);
	}else
		ans=min(ans,get(b)+cost);
}

int main() {
	cin >> h >> w >> k;
	
	char c;
	for(int i=1;i<=h;++i) {
		for(int j=1;j<=w;++j) {
			cin >> c;
			arr[i][j]=(c=='1');
			q[i][j]=q[i][j-1]+arr[i][j];
		}
	}
	
	dfs(0,1,0);
	
	cout << ans;
	return 0;
}

```

## 代码解释

解释一下代码里的这行 `if(las==i-1 && num>k) return 1000000;`：

不一定是每一种行的分法都是有解的。如果有一列不管在列上怎么切都超过上界，则无解，所以需要判断一下。

---

## 作者：封禁用户 (赞：1)

# AT_abc159_e [ABC159E] Dividing Chocolate 题解

## 思路

1. 看到这道题肯定先想到枚举，但是 $(1 \le W \le 1000)$ 显然会 $TLE$。
2. 但是因为 $(1 \le H \le 10)$，所以我们可以枚举横着切的地方时间复杂度 $O(2^H)$。
3. 然后我们可以通过贪心找到竖着怎么切 $O(W \times H)$。
4. 总的时间复杂度是 $O(W \times H \times 2^H)$ $ 1000*10*2^{10}=10240000$ 因为是 2 秒，所以不需要优化，可以直接过。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int Maxn=1001;
const int maxn=11;
int h,w,k;
int a[maxn][Maxn],sum[maxn][Maxn],ans=1e18;
bool flag[Maxn];

int summ(int x_1,int y_1,int x_2,int y_2)
{
	return sum[x_2][y_2]-sum[x_1-1][y_2]-sum[x_2][y_1-1]+sum[x_1-1][y_1-1];
}

int check()
{
	int cnt=0;
	for(int i=1,y=0;i<=w;i++)
	{
		int sum=0;
		for(int j=1;j<=h;j++)
		{
			sum+=a[j][i]-a[j][y];
			if(y==i-1&&sum>k)
			{
				return 1e18;
			}
			else if(sum>k)
			{
				cnt++;
				y=i-1;
				j=1;
				sum=0;
			}
			if(flag[j])
			{
				sum=0;
			}
		}
	}
	return cnt;
}

void dfs(int cnt,int id)
{
	if(id>=h)
	{
		ans=min(ans,cnt+check());
		return;
	}
	dfs(cnt,id+1);
	flag[id]=true;
	dfs(cnt+1,id+1);
	flag[id]=false;
}

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>h>>w>>k;
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		{
			char ch;
			cin>>ch;
			a[i][j]=ch-'0';
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
			a[i][j]+=a[i][j-1];
		}
	}
	dfs(0,1);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[ABC159E Dividing Chocolate ](https://www.luogu.com.cn/problem/AT_abc159_e)。

非常好的一道题目。

## 思路

首先映入眼帘的是 $H$ 的范围特别小。

对于 $H$ 个格子，我们有 $H-1$ 个位置可以切，于是容易想到二进制枚举，由于 $H\leq10$，所以，二进制枚举的思路是可行的。 

易发现我们可以对 $H$ 进行二进制枚举，判断每次是否可行即可，对 $W$ 进行贪心。

定义变量 $lst$ 表示上一次遍历到的位置。

每次找到一个位置，使得这一段的白色巧克力个数大于 $K$ 时，就将现在的位置 $lst$ 更新为现在的位置，但是要注意的是需要判断每种解的可行性，**如果更新后 $lst$ 没有发生变化**就说明无解，如果缺少这次判断的话就会出现明明无解，仍然判定有解，然后输出答案的情况。

最后，给一个小小的优化，在计算每个区域白色巧克力个数时，可以使用二维前缀和优化，最坏时间复杂度 $O(2^H HW)$，可过。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
#define vi vector<int>

const int mod=998244353,N=300005,INF=1<<30;

int g[15][1010];
int q[15][1010];

inline int cal(int x,int y) { 
	return q[x-1][y]+q[x][y-1]-q[x-1][y-1]; 
}
inline int query(int x2,int y2,int x1,int y1) { 
	return q[x2][y2]-q[x1-1][y2]-q[x2][y1-1]+q[x1-1][y1-1];
}

void solve() {
	int h,w,k;
	cin>>h>>w>>k;
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j) {
			char ch;
			cin>>ch;
			if(ch=='0') g[i][j]=0;
			else if(ch=='1') g[i][j]=1;
			else --j;
		}
	int ans=INF;
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j)
			q[i][j]=cal(i,j)+g[i][j];
	//cout<<query(h,w,1,1)<<'\n';
	for(int task=0;task<(1<<(h-1));++task) {
		vi vec;
		vec.pb(0);
		int lst=0;
		for(int i=0;i<h-1;++i)
			if((task>>i)&1)
				vec.pb(i+1);
		vec.pb(h);
		int res=vec.size()-2;
		bool flag=1;
		for(int i=1;i<=w;++i)
			for(int j=1;j<vec.size();++j)
				if(query(vec[j],i,vec[j-1]+1,lst+1)>k) {
					if(i==lst+1) {
						flag=0;
						break;
					}
					lst=i-1,res++;
				}
		if(flag) ans=min(ans,res);
	}
	cout<<ans<<'\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t=1;
  //cin>>t;
  while(t--)
    solve();
  return 0;
}
```

我的 [AC 记录](https://atcoder.jp/contests/abc159/submissions/38835603)。

---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4897) & [AtCoder题目页面传送门](https://atcoder.jp/contests/abc159/tasks/abc159_e)

>给定一个$n\times m$的01字符矩阵$a$。求最少需要多少次水平或竖直切割，使得切出的每一块都包含不超过$s$个$\texttt1$。

>$n\in[1,10],m\in[1,1000]$。

看到$n$如此之小，不难想到暴力枚举水平切割的$2^{n-1}$种状态。对于每一种状态，从左往右贪心，每到一列就将水平切割切成的每一块当前的$\texttt1$的个数增加若干，如果至少有$1$块当前的$\texttt1$的个数超过了$s$，便在本列与上一列之间竖直切割一刀，如果仍然超过，那么此种水平切割状态就不能要。贪心的正确性显然。对于每种水平切割状态，如果能要的话更新答案即可。时间复杂度$\mathrm O(2^nnm)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int inf=0x3f3f3f3f;
const int N=10,M=1000;
int n,m,s;
char a[N+1][M+5];
int main(){
	cin>>n>>m>>s;
	for(int i=1;i<=n;i++)cin>>a[i]+1;
	int ans=inf;
	for(int i=0;i<1<<n-1;i++){//暴力枚举2^(n-1)种水平切割状态 
		vector<int> pos;//水平切割处 
		pos.pb(0);
		for(int j=1;j<n;j++)if(i&1<<j-1)pos.pb(j);
		pos.pb(n);
		int now=pos.size()-2;//此水平切割状态当前切割次数 
		vector<int> cnt(pos.size()-1,0);//水平切割的每一块当前'1'的个数 
		for(int j=1;j<=m;j++){//从左往右贪心 
			bool ok=true; 
			vector<int> cnt0(pos.size()-1,0);//本列水平切割的每一块'1'的个数 
			for(int k=0;k<cnt.size();k++){//枚举水平切割的每一块 
				for(int o=pos[k]+1;o<=pos[k+1];o++)cnt0[k]+=a[o][j]^48;
				if(cnt0[k]>s)goto label_end;//不能要 
				if(cnt[k]+cnt0[k]>s)ok=false;//需要竖直切割 
			}
			if(ok)for(int k=0;k<cnt.size();k++)cnt[k]+=cnt0[k];//不竖直切割
			else now++,cnt=cnt0;//竖直切割 
		}
		ans=min(ans,now);//更新答案 
	label_end:;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：qiuzijin2026 (赞：0)

# [ABC159E] Dividing Chocolate

## [题面](https://www.luogu.com.cn/problem/AT_abc159_e)

## 思路

本题明显是枚举。

如果直接暴力枚举的话，时间复杂度 $O(2^{H+W})$，显然会超时。

但观察数据范围 $1 \le H \le 10$，我们就可以枚举横着在哪切，再判断最少要竖着切几刀，取最小即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long h,w,k;
string s[15];
long long sum[15][1005];
bool flag[15];
long long a[15],l;
long long ans;
bool work(long long x,long long y){
	for(long long i=1;i<=l;i++) 
		if(i==1){
			if(sum[a[i]][y]-sum[a[i]][x-1]>k){
				return false;		
			} 
		}
		else{
			if(sum[a[i]][y]-sum[a[i-1]][y]-sum[a[i]][x-1]+sum[a[i-1]][x-1]>k){
				return false;		
			} 
		}
	return true;
}
long long pd(){
	memset(a,0,sizeof(a));
	l=0;
	for(long long i=1;i<=h;i++) if(flag[i]) a[++l]=i;
	a[++l]=h;
	long long tmp=1;
	long long cnt=0;
	for(long long i=1;i<=w;i++)
		if(!work(tmp,i)){
			if(i==tmp) return INT_MAX;
			cnt++;
			tmp=i;
		}
	cnt++;
	return cnt-1;
}
void dg(long long x,long long s){
	if(x==h){
		ans=min(s+pd(),ans);
		return ;
	}
	dg(x+1,s);
	flag[x]=true;
	dg(x+1,s+1);
	flag[x]=false;
}
int main(){
	scanf("%lld%lld%lld",&h,&w,&k);
	ans=INT_MAX;
	for(long long i=1;i<=h;i++){
		cin>>s[i];
		for(long long j=1;j<=w;j++) sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+(s[i][j-1]-'0');
	}
	dg(1,0);
	printf("%lld",ans);
	return 0;
}
```

---

