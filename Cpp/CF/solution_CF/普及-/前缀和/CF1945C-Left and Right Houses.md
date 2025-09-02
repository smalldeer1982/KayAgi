# Left and Right Houses

## 题目描述

在 Letovo 村，有 $ n $ 坐房屋。村民们决定修一条大路，把村子分成左右两部分。每个居民都想住在街道的右边或左边，这被描述为一个顺序 $ a_1, a_2, \dots, a_n $，其中 $ a_j = 0 $ 表示编号为 $ j $ 房子的居民想住在街道的左边；否则，$ a_j = 1 $。

这条路将穿过两座房子之间。它左边的房子将被宣布为左边，右边的房子将被宣布为右边。更正式的说法是，**若道路在房屋 $ i $ 和 $ i+1 $ 之间通行。那么，位于 $ 1 $ 和 $ i $ 之间的房屋将位于街道的左侧，位于 $ i+1 $ 和 $ n $ 之间的房屋将位于街道的右侧**。这条路也**可以在第一所房子前面经过，在最后一所房子后面经过**。在这种情况下，整个村庄分别被声明为右侧或左侧。

为了使设计公平，决定铺设道路，使村庄两边至少有一半的居民对选择感到满意。也就是说，在每一边的 $ x $ 个居民中，至少 $ \lceil\frac{x}{2}\rceil $ 应该想住在另一边，其中 $ \lceil x \rceil $ 表示四舍五入的实数 $ x $。

 [](https://cdn.luogu.com.cn/upload/vjudge＿pic/CF1945C/2ed555a735574721378598482dfea8442c0609da.png)
 
路的左边会有 $ i $ 栋房子，对应的 $ a_j $ 中至少有 $ \lceil\frac{i}{2}\rceil $ 个 $0$。在道路的右侧，将会有 $ n-i $ 房屋，在相应的 $ a_j $ 中必须至少有 $ \lceil\frac{n-i}{2}\rceil $ 房屋。确定道路应该铺设在哪座房子 $ i $ 之后，以满足所描述的条件，并尽可能靠近村庄的中心。正式地说，在所有合适的位置 $ i $ 中，最小化 $ \left|\frac{n}{2} - i\right| $（**注意：这里的 $\frac{n}{2}$ 不做取整操作**）。

如果有多个适合的位置 $ i $ 和最小的 $ \left|\frac{n}{2} - i\right| $，输出较小的位置（即更靠左的位置）。

## 说明/提示

让我们考虑输入数据的第一个示例。

如果我们在第一所房子之后铺设道路，将会有一所房子 $ a_1 = 1 $ 在街道的左侧，其中的居民愿意住在街道的右侧。然后 $ 0 $ 出 $ 1 $ 居民在均匀的一边会满意的选择，这意味着道路不能在房子 $ 1 $ 后铺设。

如果我们在第二所房子之后铺设道路，左侧的 $ 2 $ 个居民中的 $ 1 $ 位（$ a_1 = 1 $, $ a_2 = 0 $）和右侧 $ 1 $ 位居民中的 $ 1 $ 位（$ a_3 = 1 $）将对选择感到满意。两边一半以上的居民都对这个选择感到满意，这意味着这条路可以能在房子 $ 2 $ 后铺设。我们可以证明这是最优答案。

翻译者：[SCAR_L](https://www.luogu.com.cn/user/608703)

## 样例 #1

### 输入

```
7
3
101
6
010111
6
011001
3
000
3
110
3
001
4
1100```

### 输出

```
2
3
2
3
0
1
0```

# 题解

## 作者：spfa_ (赞：7)

[CF1945C Left and Right Houses](https://www.luogu.com.cn/problem/CF1945C)

### 题目翻译

有一个 01 串，将这个串分成 $(0,i]$ 和 $[i+1,n+1)$ 两个串（编号从 $1$ 开始），求一个 $i$ 满足 $(0,i]$ 内的 $0$ 的个数不小于区间长度的一半（下取整），$[i+1,n+1)$ 内的 $1$ 的个数不小于区间长度的一半（下取整），$|\dfrac{n}{2}-i|$ 最小。如有多个满足的 $i$，取较小的那个。

### 题目分析

直接枚举分界点 $i$，计算出 $(0,i]$ 和 $[i+1,n+1)$ 内相应数字的个数，判断下，并更新答案即可。

[code](https://codeforces.com/contest/1945/submission/252299169)

---

## 作者：Otue (赞：4)

有用的信息只有这一句：在路的左边，至少要有 $\lceil\frac{i}{2}\rceil$ 个零。路的右边至少要有 $\lceil\frac{n-i}{2}\rceil$ 个一。

那么我们来一个前缀和记录左边有多少个 0，后缀和记录右边有多少个 1。枚举每一个 $i(0
\leq i \leq n)$，表示在第 $i$ 房子后划分道路，找到满足条件的且最接近 $\dfrac{n}{2}$ 即可。

注意了，这个 $\dfrac{n}{2}$ 是个浮点数，为了避免麻烦，直接用浮点数记录就行。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;

int t, n, sum[N], pre[N];
double res, id = 2e9;
char a[N];

signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> (a + 1);
		res = 2e18, id = 2e9;
		pre[n + 1] = 0;
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (a[i] == '0');
		for (int i = n; i; i--) pre[i] = pre[i + 1] + (a[i] == '1');
		for (int i = 0; i <= n; i++) {
			if (sum[i] >= (i + 1) / 2 && pre[i + 1] >= (n - i + 1) / 2) {
				if (fabs(1.0 * n / 2 - i) < res) {
					res = fabs(n / 2 - i);
					id = i;
				}
			} 
		} 
		cout << (int)id << endl;
	}
}
```

---

## 作者：xhhhh36 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1945C)

# 题目大意
给定一个长度为 $n$ 的 $01$ 串，将这个 $01$ 串分成两部分，左边有 $i(0\le i \le n)$ 个数字，右边有 $n-i$ 个数字。求满足左边至少有 $\lceil \frac{i}{2} \rceil$ 个 $0$，右边至少有 $\lceil \frac{n-i}{2} \rceil$ 个 $1$ 的 $i$ 的值。如有多个满足的 $i$，那么输出 $|n-i|$ 最小且 $i$ 较小的解。
# 题目解法
开两个数组 $pre$ 和 $nxt$ 分别表示 $01$ 串的前缀 $0$ 的个数和后缀 $1$ 的个数。再枚举 $i$ 进行判断即可。
# AC code
```cpp
#include <bits/stdc++.h>

using namespace std;
int t,a[300005],nxt[300005],pre[300005];
int n;
signed main()
{
	cin>>t;
	while (t--)
	{
		cin>>n;
		for (int i=1;i<=n;i++)
		{
			char c;
			cin>>c;
			a[i]=c-'0';
			pre[i]=pre[i-1];
			if (!a[i]) pre[i]++;
		}
		nxt[n+1]=0;
		for (int i=n;i>=1;i--)
		{
			nxt[i]=nxt[i+1];
			if (a[i]) nxt[i]++;
		}
		if (n%2==0)
		{
			int i=n/2,tmp=0;
			while (0<=i&&i<=n)
			{
				if (pre[i]>=round(i/2.0)&&nxt[i+1]>=round((n-i)/2.0))
				{
					cout<<i<<endl;
					break;
				}
				tmp++;
				if (tmp%2)
				{
					i-=tmp;
				}
				else i+=tmp;
			}
		}
		else
		{
			int i=n/2,tmp=0;
			while (0<=i&&i<=n)
			{
				if (pre[i]>=round(i/2.0)&&nxt[i+1]>=round((n-i)/2.0))
				{
					cout<<i<<endl;
					break;
				}
				tmp++;
				if (tmp%2)
				{
					i+=tmp;
				}
				else i-=tmp;
			}
		}
	}
	return 0;
}
```

---

## 作者：jubingkun (赞：1)

[洛谷](https://www.luogu.com.cn/problem/CF1945C)

[Codeforces](https://codeforces.com/contest/1945/problem/C)
## 题目大意
对于一个长度为 $n$ 的 $0,1$ 序列 $a_i$，找到最靠近中心的点使得这个点左边的 $0$ 的数量不少于这个点左边所有点个数的一半（包括这个点），这个点右边 $1$ 的数量不少于这个点右边所有点的个数的一半（不包括这个点）。

形式化的，你需要找一个最靠近中心的点 $i$（使 $\left\vert \frac{n}{2}-i \right\vert$ 最小，注意这里的 $\frac{n}{2}$ 是不四舍五入的），使得 $i$ 满足 $(\sum_{k = 1}^{i}a_i=0) \geq \left\lceil\frac{i}{2}\right\rceil$ 且 $(\sum_{k=i+1}^{n}a_i=1) \geq \left\lceil\frac{n-i}{2}\right\rceil$。
## 题目分析
最朴素做法：对于每个点，枚举它前面 $0$ 的数量和后面 $1$ 的数量，判断是否合法，时间复杂度为 $O(n^2)$。

显然可以用前缀和维护每个点前 $0$ 的数量和后面 $1$ 的数量。用 $pre_i$ 表示第 $i$ 个点前 $0$ 的数量，用 $suc_i$ 表示第 $i$ 个点后 $1$ 的数量，那么正着跑一次即可求出 $pre_i$，倒着跑一次即可求出 $suc_i$，此时判断一个点的复杂度为 $O(1)$，总体复杂度为 $O(n)$。
## 细节问题
记得判断 $0$ 这个点，因为第 $i$ 个点向左是包括 $i$ 这个点的，向右则是不包括的（不懂的话可以考虑一下 $n$ 这个点，$0$ 正好与它是相反的）。
## 代码
```cpp
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN = 3e5 + 5;
int T;
int n;
char s[MAXN];
int pre[MAXN], suc[MAXN];
bool flag[MAXN];
int ans, minn;
bool check(int i) {
	if (pre[i] < (i >> 1) + (i & 1))	return 0;
	if (suc[i + 1] < ((n - i) >> 1) + ((n - i) & 1))	return 0;
  //为什么是 suc[i + 1]?
  //因为向右看时是不包括这个点的
	return 1;
}
int main() {
	cin >> T;
	while (T--) {
		cin >> n >> (s + 1);
		ans = 0, minn = 1e9;
		for (int i = 0; i <= n + 1; ++i)	pre[i] = suc[i] = 0, flag[i] = 0;
		for (int i = 1; i <= n; ++i) {
			pre[i] = pre[i - 1];
			if (s[i] == '0')	pre[i]++;
		}
		for (int i = n; i >= 0; --i) {
			suc[i] = suc[i + 1];
			if (s[i] == '1')	suc[i]++;
		}
		for (int i = 0; i <= n; ++i)
			flag[i] = check(i);
		for (int i = 0; i <= n; ++i) {
			if (flag[i] && fabs(n / 2.0 - i * 1.0) < minn) {
				minn = fabs(n / 2.0 - i * 1.0);
				ans = i;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 思路

用 $sum$ 和 $ed$ 数组分别记录字符串前缀 $0$  的数量和字符串后缀 $1$ 的数量，然后枚举每一个分割线，判断 $i$ 是否满足 $sum_i \ge \left \lceil \frac{n}{2} \right \rceil $ 且 $ed_{i + 1} \ge \left \lceil \frac{n - i}{2} \right \rceil $ 即可。

## Code


```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i , x , n) for (int i = (x) ; i <= (n); ++i)
#define per(i , n , x) for (int i = (n) ; i >= (x); --i)
#define umap unordered_map
#define uset unordered_set
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define frep freopen(".in","r",stdin);freopen(".out","w",stdout);

using u64 = unsigned long long ;

const int mod = 998244353 ;
const int CFMAXN = 3e5 + 10 ;
const int INF = 0x3f3f3f3f3f ;


/*----------------template----------------------*/
int sum[CFMAXN] ;
int ed[CFMAXN] ;
int idx ;
double ans ;
void solve (){
	int n ;
	string s ;
	ans = DBL_MAX ;
	idx = INF ;
	cin >> n >> s ;
	for (int i = n - 1 ; i > -1 ; i-- ){
		s[i + 1] = s[i] ;
	}
	fill ( sum , sum + 1 + n , 0 ) ;
	fill ( ed , ed + 6 + n , 0 ) ;
	for (int i = 1 ; i <= n ; i++){
		int t = ( s[i] == '0' ) ;
		sum[i] = sum[i - 1] + t ; 
	} 
	for (int i = n ; i > 0; i-- ){
		int t = ( s[i] == '1' ) ;
		ed[i] = ed[i + 1] + t ;
	}
	for (int i = 0 ; i <= n; i++){
		int t = i - 1 + 1 ;
		if ( ed[i + 1] >= (n - i + 1 ) / 2 && sum[t] >= ( i + 1 ) / 2 ){
			if ( fabs(1.0 * ( 1.0 * n / 2.0) - i) * 1.0 < ans ){
				idx = i ;
				ans = fabs(1.0 * ( 1.0 * n / 2.0) - i * 1.0) * 1.0 ;
			}
		}
	}
	cout << ((idx == INF) ? 0 : idx) << '\n' ;
}

signed main (){
	int _ = 1 ;
	cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}

```

---

## 作者：wyc0607 (赞：0)

算法：前缀和思想。

对于每组数据里的字符串 $A$，进行前缀和统计。

用 $qz1_{i}$ 表示字符串 $A$ 从位置 1 到位置 $N$，0 出现的个数。

用 $qz2_{i}$ 表示字符串 $A$ 从位置 $N$ 到位置 1，1 出现的个数。

接着，从 0 到 $N$，枚举每个 $qz1_{i}$，$qz2_{i}$。如果满足条件（由题意，即 $qz1_{i} \ge \frac {i+1}{2}$ 且 $qz2_{i+1} \ge \frac {n-i+1}{2}$）：对于这个 $i$，如果 $ \left|\frac{n}{2} - i\right| $ 比上个答案 $ans$ 的 $ \left|\frac{n}{2} - ans\right| $ 更小的话，更新 $ans=i$。

循环结束，输出 $ans$，换行。

[代码 AC 记录。](https://codeforces.com/contest/1945/submission/278709413)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int qz1[300005],qz2[300005];
main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,w;
		double tp=0x7fffffff;
		cin>>n;
		string s;
		cin>>s;
		qz2[n+1]=0;//为了第 19 行当 i=n 时做特判。 
		for(int i=1;i<=n;i++) qz1[i]=qz1[i-1]+(s[i-1]=='0');//先同步 qz1[i-1] 的数据，如果 s[i-1] 是 0 则 qz1[i]++。 
		for(int i=n;i>=1;i--) qz2[i]=qz2[i+1]+(s[i-1]=='1');//先同步 qz2[i+1] 的数据，如果 s[i-1] 是 1 则 qz2[i]++。 
		for(int i=0;i<=n;i++){
			if(qz1[i]>=(i+1)/2&&qz2[i+1]>=(n-i+1)/2){//如果满足条件。 
				if(fabs(1.0*n/2-i)<tp){//如果比原先答案更优。 
					w=i;//更新。 
					tp=fabs(n/2-i);//更新。 
				}
			}
		} 
		cout<<w<<'\n';//输出，记得换行。 
	}
}

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF1945C](https://www.luogu.com.cn/problem/CF1945C) || [CodeForces 1945 C](https://codeforces.com/contest/1945/problem/C)

### 简要题意

给出一个 $01$ 串，找出一个 $i$ 使其在 $1\le i\le n$ 的情况下满足左侧 $0$ 的数量 $\ge\lceil\frac{i}{2}\rceil$，右侧 $1$ 的数量 $\ge\lceil\frac{n-i}{2}\rceil$，并最小化 $|\frac{n}{2}-i|$。

### 思路

如果我们直接从头扫的话，时间复杂度接近 $O(n^2)$，必然超时。所以要用前缀和优化。这样查询两侧 $01$ 数量的复杂度只有 $O(1)$，整体复杂度即为 $O(n)$。

由上，我们定义前缀和数组 $s$，$s_i$ 表示 $i$ 左侧的 $1$ 的数量，**注意不包含 $i$ 的状态**。之后从头遍历整个字符串，每当找到符合条件的 $i$ 就更新 $ans$ 的值，因为要最小化 $|\frac{n}{2}-i|$，所以在更新答案的时候最小化 $|n-2i|$ 即可（对 $n$ 除以 $2$ 可能会有精度问题，所以可以整体乘 $2$ 得 $|2\times(\frac{n}{2}-i)|=|n-2i|$，再省略系数 $2$ 可避免精度问题）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100001;
int n, t, s[N*3], ans;
int main(){
	string a;
	cin >> t;
	while(t--) {
		ans = -1;
		cin >> n >> a;
		for (int i = 1;i <= n; i++) s[i] = s[i - 1] + (a[i - 1] == '1'); //计算前缀和，注意s[i]的值与a[i]的状态无关
		for (int i = 0;i <= n; i++)
			if(s[i] * 2 <= i && 2 * (s[n] - s[i]) >= n - i && abs(n - i * 2) < abs(n - ans * 2)) //更新答案
				ans = i;
		cout << ans << endl;
	}
} 
```

---

## 作者：TemplateClass (赞：0)

每次枚举中间的分割点 $i$，用前缀和计算出左右 $0$ 和 $1$ 的数量，进行判断后更新答案。

注意题目中的 $\lceil x \rceil$ 不是传统意义上的向上取整，而是四舍五入。

```cpp
const int N = 3e5 + 5;

int n, a[N];

void solve(){
	std::cin >> n;
	for(int i = 1; i <= n; ++i) {
		char c; std::cin >> c;
		a[i] = a[i - 1] + (c - '0');
	}
	
	double minsum = n; int mini = 0;
	
	for(int cuti = 0; cuti <= n; ++cuti) {
		int lsum = cuti - a[cuti];
		int rsum = a[n] - a[cuti];
		
		
		if(lsum >= std::roundl(cuti / 2.0) && rsum >= std::roundl((n - cuti) / 2.0)) {
			double sum = std::fabs(n / 2.0 - cuti);
			if(sum < minsum) {
				minsum = sum;
				mini = cuti;
			}
		}
	}
	
	std::cout << mini << "\n";
}

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1945C)

# 思路：

注意读题，本题对于左右两边的要求是：如果左边有x个人，那么要满足 $\lceil\frac{x}{2}\rceil$ 的人数都得到了满足，右边同理。

由于本题输入都是 $0$ 和 $1$，所以直接用一个前缀和的办法来判断左右 $0$ 和 $1$ 的个数。

可以 $O(N)$ 枚举划分的点的地方，这样就可以算出来左右两边的满足期望的数量，如果两边都满足了，那就判断要不要更新划分点，注意这里更新的时候要尽可能贴近中心，这里为了判断精度，要把 $\frac{n}{2}$ 转化为 ```double``` 类型。

还有一个小点，就是最左边的路划分点是 $0$，最右边是 $n$ 而不是 $n+1$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
char c[N];
int T,n,s[N];
signed main(){
	cin>>T;
	while(T--){
        cin>>n;
		scanf("%s",c+1);
		for(int i=1;i<=n;i++){
			s[i]=c[i]-'0'+s[i-1];
		}
		int f=1e9;
		for(int i=0;i<=n;i++){
			if(i-s[i]>=round(1.0*i/2)&&s[n]-s[i]>=round(1.0*(n-i)/2)){
				if(abs(1.0*i-1.0*n/2)<abs(1.0*f-1.0*n/2)){	
					f=i;
				}
			}
		}
        cout<<f<<endl;
	}
	return 0;
}
```
完结撒花~

---

## 作者：Andy_WA (赞：0)

## 分析
只要读懂题目，这一题 $60\%$ 就 OK 了！

## 思路
首先枚举每一个空隙，计算出 $1$ 的数量和 $0$ 的数量，再然后打擂台。

可以先计算出总共 $1$ 的个数，也就是第一个空隙右边总共 $1$ 的个数。每次枚举时，在当前空隙右边的数如果为 $1$，右边 $1$ 的个数减一，否则左边 $0$ 的个数加一。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MaxN=300010;
long long arr[MaxN];
long long T,n;
int main(){
    cin>>T;
    for(long long m=0;m<T;m++){
        cin>>n;
        long long Left=0,Right=0,mini;
        double minx=INT_MAX;
        for(long long i=1;i<=n;i++){
        	char x;
            cin>>x;//输入
            if(x=='0'){
				arr[i]=0;
			}else{
                arr[i]=1;
                Right++;
            }
        }
        for(long long i=0;i<=n;i++){
            if(Left>=round(i/2.0) && Right>=round((n-i)/2.0) && minx>abs(n/2.0-i)){//是否更新答案
                minx=abs(n/2.0-i);//更新答案
                mini=i;
            }
            if(arr[i+1]==0) Left++;//空隙右边的数如果为1，右边一的个数减一，否则左边零的个数加一
            else Right--;
        }
        cout<<mini<<endl;//输出 
    }
    return 0;
}
```

最后，以一句话结束：
$$
\textit{\textbf{莫抄袭，棕了少年名，空悲切。}}
$$

---

## 作者：HasNoName (赞：0)

### 思路

按顺序枚举每一个空隙，计算出左边 $0$ 的数量和右边 $1$ 的数量，再考虑是否更新答案。

可以先计算出总共一的个数，也就是第零个空隙右边总共一的个数。每次枚举时，在当前空隙右边的数如果为 $1$，右边一的个数减一，否则左边零的个数加一。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300005;
int a[N];
int ff(double x)//四舍五入
{
    int xx=x;
    if(x-xx>=0.5)xx++;
    return xx;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T,n;
    cin>>T;
    while(T--)
    {
        cin>>n;
        char ch;
        int l=0,r=0,mini;
        double minn=1e9;
        for(int i=1;i<=n;i++)//输入
        {
            cin>>ch;
            if(ch=='0')a[i]=0;
            else
            {
                a[i]=1;
                r++;
            }
        }
        for(int i=0;i<=n;i++)
        {
            if(l>=ff(i/2.0)&&r>=ff((n-i)/2.0)&&minn>abs(n/2.0-i))//是否更新答案
            {
                minn=abs(n/2.0-i);//更新答案
                mini=i;
            }
            //cout<<l<<' '<<r<<';';
            if(a[i+1]==0)//空隙右边的数如果为1，右边一的个数减一，否则左边零的个数加一。
                l++;
            else r--;
        }
        cout<<mini<<'\n';
    }
    return 0;
}

```

---

## 作者：InversionShadow (赞：0)

我们令 $p_i$ 表示 $\sum\limits_{j=1}^i[a_j=0]$，$p^{'}_i$ 维护后缀 $i\sim n$ 中 $a_j=1$ 的个数。

线性枚举 $i$ 是否满足 $p_i\ge\left\lceil\frac{n}{2}\right\rceil$ 并且 $p_{i+1}^{'}\ge\left\lceil\frac{n-i}{2}\right\rceil$，记录即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 3e5 + 100;

int t, n, a[N], suma[N], sumb[N], p;
double minn;

void solve() {
	cin >> n;
	minn = 2e18, p = 1e18;
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		a[i] = c - '0';
		suma[i] = sumb[i] = 0;
	}
	suma[0] = 0, sumb[n + 1] = 0;
	for (int i = 1; i <= n; i++) {
		suma[i] = suma[i - 1] + (a[i] == 0 ? 1 : 0);
	}
	for (int i = n; i; i--) {
		sumb[i] = sumb[i + 1] + (a[i] == 1 ? 1 : 0);
	}
	for (int i = 0; i <= n; i++) {
		if (suma[i] >= ceil(1.0 * i / 2.0) && sumb[i + 1] >= ceil(1.0 * (n - i) / 2.0)) {
			if (minn > fabs(1.0 * n / 2.0 - i)) {
				minn = fabs(1.0 * n / 2.0 - i);
				p = i;
			}
		}
	}
//	cout << "ans = ";
	cout << p << '\n';
}

signed main() {
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Cute__yhb (赞：0)

## 思路

模拟 $+$ 前缀和。

一遍前缀和统计 $0$ 的个数，一遍后缀和统计 $1$ 的个数。

枚举每个位置，求出前边 $0$ 的个数，以及后面 $1$ 的个数，与前后的总个数的 $\frac{1}{2}$ 进行比较，最后取最靠近中间的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define re register
#define ri register int
#define rll register long long
#define ld long double
#define endl '\n'
#define fi first
#define se second
#define pii pair<int,int>
#define p_q priority_queue
#define iter iterator
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define nep(i,a,b) for(int i=(a);i>=(b);i--)
#define popcount __builtin_popcount
#define pb push_back
#define mem(a,x) memset((a),x,sizeof(a))
#define eps 1e-8
#define oper operator
#define mk make_pair
int n,a[300005],a0[300005],a1[300005];
void solve(){
	cin>>n;
	a0[0]=0;
	a1[0]=0;
	a0[n+1]=0;
	a1[n+1]=0;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		a[i]=c-'0';
		a0[i]=0;
		a1[i]=0;
	}
	for(int i=1;i<=n;i++){
		if(!a[i]){
			a0[i]=a0[i-1]+1;//前缀和
		}else{
			a0[i]=a0[i-1];
		}
	}
	for(int i=n;i;i--){
		if(a[i]){
			a1[i]=a1[i+1]+1;//后缀和
		}else{
			a1[i]=a1[i+1];
		}
	}
	int ans=n+2;
	double minn=n+2;
	for(int i=0;i<=n+1;i++){
		int cnt0=a0[i];//前面的0
		int cnt1=a1[i+1];//后面的1
		if(cnt0>=(i+1)/2&&cnt1>=(n-i+1)/2){//比较
			if(fabs(n*1.0/2-i)<minn){//记录答案
				ans=i;
				minn=fabs(n*1.0/2-i);
			}else if(fabs(n*1.0/2-i)==minn){//取较小的
				ans=min(i,ans);
			}
		}
	}
	cout<<ans<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}

```

---

## 作者：Sternenlicht (赞：0)

### 思路

由于题目给的是 01 字符串，因此可以用 $sum$ 数组记录前缀和，快速计算出区间中 $0$ 和 $1$ 的个数。具体地，当整体区间被划分为 $[0,i]$ 和 $[i+1,n]$ 两个区间时，前一个区间中 $1$ 的个数为 $sum_i$，记为 $left1$；后一个区间中 $1$ 的个数为 $sum_n - sum_i$，记为 $right1$。那么区间中 $0$ 的个数就是区间长度减去 $1$ 的个数。即此时前一个区间中 $0$ 的个数为 $i - left1$，记为 $left0$；后一个区间中 $0$ 的个数为 $n - i - right1$，记为 $right0$。现在就可以判断是否满足题目要求，且为最小值了。

此题有两个技巧：

* $\frac{n}{2}$ 用 ``double`` 类型存储，取绝对值时用 ``fabs`` 函数。

* 在读入字符串的开头加上字符 ``*``，这样就相当于字符串中的有用字符的起始下标是从 $1$ 开始的，便于以后的计算。

注意多测要清空。

```cpp
#include <bits/stdc++.h>
#define il inline
namespace Fast_IO {
	template <typename T> il void read(T &x) {
		x = 0; int f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + (ch - 48), ch = getchar();
		x = f ? -x : x;
	}
	template <typename T, typename ...Args>
	il void read(T &x, Args& ...args) {read(x), read(args...);}
	template <typename T> il void write(T x, char c = '\n') {
		if (x) {
			if (x < 0) x = -x, putchar('-');
			char a[30]; short l;
			for (l = 0; x; x /= 10) a[l++] = x % 10 ^ 48;
			for (l --; l >= 0; l --) putchar(a[l]);
		} else putchar('0');
		putchar(c);
	}
} using namespace Fast_IO;
using namespace std;

const int Maxn = 300005;
int sum[Maxn];
signed main() {
	int T; read(T);
	while (T --) {
		int n; read(n);
		string a; cin >> a;
		a = "*" + a;
		for (int i = 1; i <= n; i ++) sum[i] = sum[i - 1] + a[i] - 48;
		int ans = 0; double mn = 2e9, mid = n * 1.0 / 2;
		for (int i = 0; i <= n; i ++) {
			int j = i + 1;
			int left1 = sum[i];
			int left0 = i - left1;
			int right1 = sum[n] - sum[j - 1];
			int right0 = n - j + 1 - right1;
			if (left0 >= left1 && right1 >= right0)
				if (fabs(mid - i) < mn)
					ans = i, mn = fabs(mid - i);
		}
		write(ans);
		memset(sum, 0, sizeof sum);
	}
	return 0;
}
```

---

## 作者：SCAR_L (赞：0)

（话说这题没人翻译？那我就提交咯~）

看不懂题面可以看[我的翻译](https://www.luogu.com.cn/paste/m0e6xumc)。


------------
这道题读懂题目后就比较容易了（所以是阅读理解），不过坑点挺多的（后面会讲）。   
先讲一下思路：用一个前缀和记录想在这个点左边的有多少人，用后缀和记录想在这个点右边的有多少人。再枚举道路的位置就行了。   

坑点：
1. 道路可以在可以在第一个房子的前面和最后一个房子的后面。
2. 两边满意的人数要在一半（**向上取整**）及以上。
3. 有多组解时选择距离 $\frac{n}{2}$ 最近的（**不取整！！！**）。
4. 在这个条件下，若仍有多解，则选择更靠左的。

剩下的就只剩下实现啦！  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int NR = 5e5 + 5;
int T, n;
char s[NR];
int p1[NR], p2[NR]; 
int main()
{
	cin >> T;
	while(T--)
	{
		cin >> n;
		scanf("%s", s + 1); // 我用的是字符串输入
		for(int i = 1; i <= n; i++) p1[i] = p1[i-1] + (s[i] == '0');    // 前缀和数组
		for(int i = n; i >= 1; i--) p2[i] = p2[i+1] + (s[i] == '1');    // 后缀和数组
		int ans = 1e9;
		double mid = 1.0 * (n) / 2; // 中点
		for(int i = 0; i <= n; i++)
			if(p1[i] >= (i + 1) / 2 && p2[i+1] >= (n - i + 1) / 2) // 这里用了一个小技巧：ceil(a / 2.0) = (a+1) / 2
			{
				if(abs(mid - i) < abs(mid - ans)) ans = i;  // 符合条件且离中点更近，更新（注意是小于号！因为要求的是更靠左的）
			}
		cout << ans << endl;
		for(int i = 1; i <= n; i++) p1[i] = p2[i] = 0;  // 记得清零
	}
	return 0;
}
```

---

## 作者：zxh923 (赞：0)

### 思路

思路比较简单，考虑把每个位置都试一下，如果合法并且比当前最有答案更优先，记录答案。

可以用前缀和优化一下 $1\sim i$ 的 $0$ 的个数和后缀和优化 $i\sim n$ 的 $1$ 的个数。

### 代码

```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 300005
using namespace std;
int t,n,sum1[N],sum2[N],tmp,ans,as;
char c[N];
void solve(){
	as=1e9;
	cin>>n;
	sum2[n+1]=0;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		sum1[i]=sum1[i-1]+(c[i]=='0'?1:0);//前缀和 
	}
	for(int i=n;i>=1;i--){
		sum2[i]=sum2[i+1]+(c[i]=='1'?1:0);//后缀和 
	}
	for(int i=0;i<=n;i++){
		if(sum1[i]>=(i+1)/2&&sum2[i+1]>=(n-i+1)/2&&abs(n-i*2)<as){//如果合法且优先级更高 
			as=abs(n-i*2);//记录当前优先级 
			ans=i;
		}
	}
	cout<<ans<<'\n';//输出 
}
signed main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

