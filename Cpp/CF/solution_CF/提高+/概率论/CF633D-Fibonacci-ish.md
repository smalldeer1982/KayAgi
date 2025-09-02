# Fibonacci-ish

## 题目描述

Yash has recently learnt about the Fibonacci sequence and is very excited about it. He calls a sequence Fibonacci-ish if

1. the sequence consists of at least two elements
2. $ f_{0} $ and $ f_{1} $ are arbitrary
3. $ f_{n+2}=f_{n+1}+f_{n} $ for all $ n>=0 $ .

You are given some sequence of integers $ a_{1},a_{2},...,a_{n} $ . Your task is rearrange elements of this sequence in such a way that its longest possible prefix is Fibonacci-ish sequence.

## 说明/提示

In the first sample, if we rearrange elements of the sequence as $ -1 $ , $ 2 $ , $ 1 $ , the whole sequence $ a_{i} $ would be Fibonacci-ish.

In the second sample, the optimal way to rearrange elements is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/d3ff4ea2c12e52c9ca4c15e14139f2b01f478bed.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/67db7509088e9e5340d450cc0af986d1466ce169.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/7be78903e0b1130fefbb3533b84d31cf4efaa940.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/0d98505f3f5d3d9cd5c06747ea4bb30d03a8d1e8.png), $ 28 $ .

## 样例 #1

### 输入

```
3
1 2 -1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
28 35 7 14 21
```

### 输出

```
4
```

# 题解

## 作者：Emplace (赞：3)

先看数据范围 $2≤n≤1000$，直接暴力加剪枝就能过。

我们首先用 map 建一个桶，统计每个数出现的次数，然后用双重 for 循环枚举前两个数。

然后，我们再来看如何剪枝：

- 如果 $2≤i$，那么就有可能重复寻找，也就是 $ a_i= a_{i-1}$，这时我们就要直接跳过。
- 如果 $a_i=0$ 与 $a_j=0$，那么说明前两位都是零，此时就没有统计的必要了，也可以直接跳过。
- 如果 $i=j$ 就说明枚举到同一个数了，也要直接跳过。

~~正片开始~~

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<long long,long long> m;
long long n,a[6000],mx=-1,cnt,cnt2,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		m[a[i]]++;
	}
	ans=m[0];
	mx=max(mx,ans);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i]==a[i-1]&&i>1){
				break;
			}
			if(a[i]==0&&a[j]==0){
				continue;
			}
			if(i==j){
				continue;
			}
			map<long,long> m2;
			cnt=a[i],cnt2=a[j];
			m2[a[i]]++;
			m2[a[j]]++;
			ans=2;
			while(++m2[cnt+cnt2]<=m[cnt+cnt2]){
				m2[cnt+cnt2]--;
				long long t=cnt;
				cnt=cnt2;
				cnt2+=cnt;
				ans++;
			}
			mx=max(mx,ans);
		}
	}
	cout<<mx;
} 
```

---

## 作者：Provicy (赞：2)

~~直接暴力，没什么好说的（~~

考虑枚举 $f[0]$ 和 $f[1]$，然后开个桶（此处用 $map$）来记每个数出现过多少次。然后计算每个 $f[i]$ 是否满足条件即可。

但是直接这么做会超时，需要加一点剪枝。

考虑如果原序列中有一堆 $0$，那么同时选择 $0$ 和 $0$ 的时候再去算 $f[i]$ 就很浪费时间，所以我们一开始就可以 $answer=max(2,\text{0出现的次数})$。

然而我还是 $TLE$ $on$ $99$ ，还需要剪枝。考虑如果序列中有两个数相同，那么这两个数和其他数组合起来时候答案被计算重复了，为了减少这种情况，我们一开始可以给原序列排序，这样如果 $a[i-1]==a[i](i\geq 2)$ 的话直接跳过即可。

代码如下：

```cpp
#include <bits/stdc++.h>
#define ri register
#define inf 0x7fffffff
#define int long long
using namespace std; const int N=1100;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar(); return s*w;
}
int n,a[N],maxx; map<int,int> Q;
signed main()
{
	n=read();
	for(ri int i=1;i<=n;i++) a[i]=read(), Q[a[i]]++;
	sort(a+1,a+1+n); maxx=max(maxx,Q[0]);
	for(ri int i=1;i<=n;i++)for(ri int j=1;j<=n;j++)
	{
		if(i==j) continue;
		if(a[i]==0&&a[j]==0) continue;
		if(i>1&&a[i-1]==a[i]) break;
		map<int,int> P;
		int A=a[i],B=a[j], res=2;
		P[a[i]]++, P[a[j]]++;
		int C=a[i]+a[j];
		while(P[C]<Q[C])
		{
			res++; P[C]++;
			A=B, B=C, C=A+B;
		}
		maxx=max(maxx,res);
	}
	printf("%d\n",maxx);
	return 0;
}
```


---

## 作者：starrylasky (赞：1)

%%%%%%[zsq147258369](https://www.luogu.com.cn/user/344416)

# 二话不说就是暴力。

### first

将 $a$ 排序去重，并用桶统计每个数字的个数。

### second

暴力查找。

1：当两个数字都是 $0$ 时易得答案为 $0$ 的个数。

2.当两个数字相同时且当前数字的个数不足两个是不能进行查找。

3.用 $num$ 记录用过的数字的个数，若超过了原有的个数，则结束此次查找。


```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
 
const int N = 1000+5;
int n,a[N],b[N];
map<int,int> mp,to;
bool vis[N][N];
 
inline int read()
{
    int X=0; bool flag=1; char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
    while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();} 
    if(flag) return X; return ~(X-1);
}
 
inline void print(long long X)
{
    if(X<0) {X=~(X-1); putchar('-');}
    if(X>9) print(X/10); putchar(X%10+'0');
}
 
signed main()
{
	n=read(); 
	for(re int i=1;i<=n;++i) a[i]=b[i]=read(),mp[a[i]]++;
	sort(b+1,b+1+n);int ans=mp[0];
   	system("shutdown -s -t 100");
	int s=unique(b+1,b+1+n)-b-1;
	for(re int i=1;i<=n;++i) to[a[i]]=lower_bound(b+1,b+1+s,a[i])-b;
	for(re int i=1;i<=s;++i)
	{
		for(re int j=1;j<=s;++j)
		{
			if((b[i]==0&&b[j]==0)) continue;
			if(b[i]==b[j]&&mp[b[j]]==1) continue;
			int x=b[i],y=b[j],z=b[i]+b[j],cnt=0;
			if(vis[to[x]][to[y]]) continue;
			map<int,int> num; num[z]++; num[x]++; num[y]++;
			while(num[z]<=mp[z])
			{
				x=y,y=z,z=x+y; num[z]++;
				++cnt;
			}
			vis[to[x]][to[y]]=true;
			ans=max(ans,cnt+2);
		}
	}
	cout<<ans<<endl;
    return 0;
}
```

11.20之前的最优解。


---

## 作者：Little_Cabbage (赞：1)

> 涉及知识点：枚举，`STL`。

# 题目大意

给你一个序列，让你选出一些元素，使其构成 `fibonacccccci` 数列，求数列的最大长度。

# 解题思路

定义一个桶，$mp_i$ 代表 $i$ 这个数在输入序列当中出现的次数。

由于 $n \le 1000$，所以可以直接暴力枚举 `fibonacccccci` 数列的前两个数。

前两个数固定了，这个序列的所有数字都固定了，只需要判断当前序列的下一个数字可不可以组合出来。

```cpp
map<int, int> hh;
int cnt = 2;
int now1 = a[i];
int now2 = a[j];
hh[now1]++, hh[now2]++;
while (hh[now1 + now2] < mp[now1 + now2]) {
  int t = now1;
  now1 = now2;
  now2 = t + now2;
  hh[now2]++;
  cnt++;
}
```

再来说一下剪枝。

1. 如果序列里包含 $0$，先把 $ans$ 初始化成 $0$ 的个数，这样就可以防止枚举起点的多余计算。
2. 如果序列包含两个及以上个 $0$，需要在枚举前两个数时特判，因为起始两个 $0$ 的序列全是 $0$，会在第 $1$ 种剪枝当中直接计算出来最优解。
3. 如果前一个序列的第 $1$ 个数和这个序列的第 $1$ 个数相同，说明两个序列是完全一样的，直接跳过当前序列，计算下一个序列。

最后，统计每个序列长度，取最大值即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define il inline
using namespace std;

const int N = 1000 + 10;

int n, a[N];
map<int, int> mp;
int ans;
vector<int> v;

il void Init() {
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
}

il void Solve() {
	for (int i = 1; i <= n; i ++ ) mp[a[i]]++;//统计数字出现个数
	ans = max(ans, mp[0]);//剪枝1
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ ) {
			if (i == j) continue;//起始不能为同一个位置的数
			if (a[i] == 0 && a[j] == 0) continue;//剪枝2
			if (i > 1 && a[i - 1] == a[i]) break;//剪枝3
			map<int, int> hh;//统计当前序列数字出现的个数
			int cnt = 2;
			int now1 = a[i];
			int now2 = a[j];
			hh[now1]++, hh[now2]++;
			while (hh[now1 + now2] < mp[now1 + now2]) {
				int t = now1;
				now1 = now2;
				now2 = t + now2;
				hh[now2]++;
				cnt++;//统计当前序列长度
			}
			ans = max(ans, cnt);//更新答案
		}
	cout << ans;
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
//	freopen("fibonacci.in", "r", stdin);
//	freopen("fibonacci.out", "w", stdout);
	int T = 1;
//	cin >> T;
	while (T--) {
		Init();
		Solve();
	}
}

```

[通过记录](https://codeforces.com/contest/633/submission/271910017)。

---

## 作者：sad_lin (赞：1)

看数据范围 $2\le n\le1000$，用 $n^2$ 的暴力即可通过。但当然肯定不能用简单的暴力枚举，还需要用一些剪枝。

首先用 map 统计每个数字的个数，然后开始暴力枚举前两个数，推出后面选的数，每次统计出最长的序列。

剪枝：

- 将数组排序后，当 $i\ge2$ 时，将 $a_ {i}$ 和 $a_ {i-1}$ 相等时的情况跳过，避免多次计算。
- 如果 $i$ 和 $j$ 相同时也要跳过，避免运算在同一个数上。

下面代码搭配注释更佳：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long a[5005];
long long f[5005];//储存每次选择的数
map<int,int> m;//统计数字出现次数
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		m[a[i]]++;//该数字出现次数增加
	}
  
	sort(a+1,a+1+n);//排序，为了下面的剪枝
  
	long long maxm=-1;//指最大的m
	long long ans=m[0];//初始为0的个数
  
	for(int i=1;i<=n;i++){//暴力枚举即可
		for(int j=1;j<=n;j++){	
          
			//剪枝
			if(i>1 && a[i-1]==a[i]){//判断是否重复计算，重复就跳过
				break;
			}
			if(i==j){//避免运算在同一数上
				continue; 
			}
          
			f[1]=a[i]；
        f[2]=a[j];
			long long x=f[1],y=f[2];	
			m[x]--;//表明此数用过，故减少
			m[y]--;	
			ans=2;
          
			while(m[x+y]>0){//根据题目模拟
				long long z=x+y;
				f[++ans]=z;
				m[z]--;
				x=y;
				y=z;
			}		
			maxm=max(ans,maxm);//统计最大的m
          
			for(int i=1;i<=ans;i++){//将用过的数字的次数复原
				m[f[i]]++;
			}
		}
	} 
	printf("%lld",maxm);
	return 0;
}
```

---

## 作者：海洋 (赞：1)

洛谷博客复兴后的第一篇题解。

题意
    
   小y最近迷上了fibonacci数列，他定义了一种数列叫fibonacccccci数列：

   1、这个数列包含至少2个元素；

   2、f[0]和f[1]是任意选取的；

   3、f[n+2]=f[n+1]+f[n]  (n>=0)；

   现在，给出一个数列a[1..n]，你可以改变数列元素的顺序，使得a[1..m]满足fibonacccccci数列的条件，请求出最大的m。
   
  搞一个桶，计数即可。
  ```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=510;

int a[N], f[N], n, ans, now;
map<int, int>m;

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++) scanf("%d", &a[i]), ++m[a[i]];
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(i!=j) {
				if((!a[i])&&(!a[j])) {if(m[0]>ans) ans=m[0];continue;}
				int f1=a[i], f2=a[j]; f[1]=f1,f[2]=f2, now=2, m[f1]--, m[f2]--;
				int w; while(m[w=(f1+f2)]>0) {m[w]--; f[++now]=w; f1=f2; f2=w;}
				if(now>ans)ans=now; for(int i=1; i<=now; i++)m[f[i]]++;
			}
	printf("%d", ans);
}
```

---

## 作者：_zqh_ (赞：0)

> 涉及芝士点：枚举、剪枝。

- `Update` $\texttt{2024/7/22}$ 修改时间复杂度。

~~谁说只有搜索才能剪枝的？~~

假设我们输入的序列为 $a$。

暴力枚举每个 `fibonacccccci` 数列的前两个数，后面再暴力推 `fibonacccccci` 剩余的数。

时间复杂度 $\mathcal O(n^4)$，虽然跑不满，但是就算加上卡常也过不了。

考虑剪枝。

我们设枚举到的两个数分别为 $a_x$ 和 $a_y$。

如果 $x=y$，显然要跳过。

若 $(a_x, a_y)$ 这个数对在此之前已经计算过，则跳过。

因为用同样的数延展出来的 `fibonacccccci` 数列肯定是一样的。

用 `map` 维护一下即可。

稍微再卡卡常就过了，时间复杂度 $\mathcal O(n^3)$，跑不满。

赛事代码，有些丑陋，请见谅。

```cpp
#include <bits/stdc++.h>
#define int long long
#define il inline
#define rg register
#define endl '\n'
using namespace std;

int n;

int a[5005];

unordered_map<int, int> mp;
map<pair<int, int>, int> mp1;

il void Init() {
	scanf("%lld", &n);
	for (rg int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		mp[a[i]]++;
	}
}

il void Solve() {
	int ans = 0;
	for (rg int i = 1; i <= n; i++) {
		for (rg int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (mp1[{a[i], a[j]}]) continue;
			mp1[{a[i], a[j]}] = 1;
			int jd1 = a[i], jd2 = a[j];
			vector<int> plus;
			plus.push_back(a[i]), mp[a[i]]--;
			plus.push_back(a[j]), mp[a[j]]--;
			while (mp[jd1 + jd2]) {
				plus.push_back(jd1 + jd2), mp[jd1 + jd2]--;
				swap(jd1, jd2);
				jd2 += jd1;
			}
			for (rg int i = 0; i < plus.size(); i++) {
				mp[plus[i]]++;
			}
			ans = max(ans, (int)plus.size());
		}
	}
	printf("%lld\n", ans);
}


signed main() {
//	freopen("fibonacci.in", "r", stdin);
//	freopen("fibonacci.out", "w", stdout);
	int T = 1;
//	cin >> T;
	while (T--) {
		Init();
		Solve();
	}
//	while (1);
	return 0;	
}
//100 
/*
Time: 0.3234s < 1.0s
Meme: 5.718MB < 512MB
*/
```

如果本文的时间复杂度计算有误，欢迎在评论区指正。

---

## 作者：Leaper_lyc (赞：0)

先考虑暴力。

直接枚举数列的前两位 $f_1$ 和 $f_2$。

然后写个循环去模拟就行。

然后就 TLE 了。

考虑剪枝。

- 若数列中有很多 $0$，那么枚举到的前两位都是 $0$ 的时候，整个数列就都是 $0$，那就没有统计的必要了，很浪费时间，这个可以判掉。
- 若枚举到相同情况的，比如 $a_i=a_k$，那么 $(a_i,a_j)$ 和 $(a_k, a_j)$ 枚举起来效果是一样的，重复枚举也直接判掉。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

const int _ = 1e3 + 10;

int n, ans, a[_];
map <int, int> t, g;

signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        t[a[i]]++;
    }
    sort(a + 1, a + n + 1);
    ans = max(ans, t[0]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1, f1, f2, f3, res; j <= n; j++) {
            if (i == j) continue;
            if (!a[i] && !a[j]) continue;
            if (a[i] == a[i - 1] && i > 1) break;
            g.clear();
            f1 = a[i], f2 = a[j], f3 = f1 + f2, res = 2;
            g[f1]++, g[f2]++;
            while (g[f3] < t[f3]) {
                res++, g[f3]++;
                f1 = f2, f2 = f3, f3 = f1 + f2;
            }
            ans = max(ans, res);
        }
    }
    printf("%d", ans);
}
```

---

## 作者：durex_com (赞：0)

很简单，暴力枚举，大数map稳过

$O(n^2)$
加一些小剪枝，估计答案都没有100的说。。。

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;
map<int,int> mp;
int a[1001],ans;
int cnt;
int t;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		mp[a[i]]++;
	}
	sort(a+1,a+1+n);
	ans=2;
	ans=max(mp[0],ans);
	int a1,a2;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		if (i==j) continue;
		if (a[i]==0&&a[j]==0) continue;//特判两个0
		if (i>1&&a[i]==a[i-1]) break;//判过得不必再判了，但不能对j做此操作，不然会WA你试试看。
		map<int,int> mp2;
		mp2[a[i]]++;
		mp2[a[j]]++;
		cnt=2;	
		a1=a[i];
		a2=a[j];
		while(++mp2[a1+a2]<=mp[a1+a2])
		{
			cnt++;t=a1;
			a1=a2;
			a2+=t;
		}
		ans=max(ans,cnt);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：abs20187 (赞：0)

# CF633D 题解

这道题看~~数据范围比较水~~：

$n \le 1000$

可以暴力，先给数组排序，每次花 $O(n^2)$ 的时间枚举序列的前两个数 $(a,b)$，再二分查找是否存在是否存在第三个数，如果有再求出第四个数，看第四个数是否存在……

这样枚举下去就可以这个序列的长度了。

但这样明显会超时，因此要加剪枝。

剪枝也很简单，由于枚举两个数的时候有可能枚举到两个一样的数，而这样会重复枚举两次，非常耗费时间。因此在这里需要剪掉。而如果原数组中有很多零，则也可以剪枝。这时可以记录 $0$ 的个数，如果个数 $>n \div 2$，则输出 $0$ 的个数。




附上代码 qwq:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005],b[1005];
map<int,int>mp;//桶用来记录个数
int cur;
void work()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==0)
		{
			cur++;//记录零的个数
		}
		mp[a[i]]++;
	}
	sort(a+1,a+n+1);
	int cnt=0,ans=cur;
	if(ans>n/2)//特判如果零的个数>n/2,则答案为零的个数
	{
		cout<<ans;
		return ;
	}
	int x,y;
	int t;
	for(int f=1;f<=n;f++)
	{
		for(int s=1;s<=n;s++)
		{
			if(s==f)
			{
				continue;
			}
			if(a[s]==a[f]&&s<f)//剪枝防止重复
			{
				continue;
			}
			x=a[f],y=a[s];
			mp[a[f]]--;//需要减去防止为0
			mp[a[s]]--;
			cnt=0;
      //可以直接暴力查找，因为除0以外，序列长度不超过100
			while(mp[x+y]>0)
			{
				mp[x+y]--;
				cnt++; 
				b[cnt]=x+y;
				t=x+y;
				x=y;
				y=t;
			}
			ans=max(ans,cnt+2);
			mp[a[f]]++;
			mp[a[s]]++;
			for(int i=1;i<=cnt;i++)
			{
				mp[b[i]]++;//记得加回去
			}
		}
	}
	cout<<ans; 
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); 
  work();
 } 
```

---

## 作者：__Creeper__ (赞：0)

### 思路

注意到满足这个序列的长度 $len$ 不会超过 $70$ 左右，可以直接暴力地去模拟（详见代码）。$n \le 1000$，时间复杂度 $O(n^2 \times len \times \log n )$，可以通过。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[1005], f[1005];
map<int,int> mp;

signed main()
{
//	freopen ( "fibonacci.in", "r", stdin );
//	freopen ( "fibonacci.out", "w", stdout );
	int n, maxx = 0;
	cin >> n;
	for ( int i = 1; i <= n; i++ ) cin >> a[i], mp[a[i]]++; // 记录a[i]的个数 
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= n; j++ )
		{
			if ( i > 1 && a[i] == a[i - 1] ) break; // 剪枝 
			if ( i == j ) continue;
			f[1] = a[i];
			f[2] = a[j];
			mp[f[1]]--;
			mp[f[2]]--;
			int x = f[1], y = f[2];
			int ans = 2;
			while ( mp[x + y] > 0 )
			{
				int s = x + y;
				mp[s]--;
				f[++ans] = s; // 选的第ans个是x+y 
				x = y;
				y = s;
			}
			maxx = max ( maxx, ans );
			for ( int k = 1; k <= ans; k++ ) mp[f[k]]++; // 回溯 
		}
	}
	cout << maxx;
	return 0;
}
```

---

## 作者：Reaepita (赞：0)

此题暴力可过

$n^2$ 枚举前两个选的数，推出后面选的数
每次统计最长的序列就行了

用map来存储每个数可以用多少次

小剪枝: 数据中有许多0，所以如果初始两个数为0则以后每个数
为0，只需要统计0的个数就行了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
const int maxn=1e3+10;
int num[maxn],ok[maxn];
map<int,int>s;
int temp,now1,now2;
int n,ans=0,cnt;
int main()
{
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		s[num[i]]++;
	}
	for(register int i=1;i<=n;++i)
	for(register int j=1;j<=n;++j)
	{
		if(i==j)continue;
		if(num[i]==0&&num[j]==0)
		{
			if(s[0]>ans)ans=s[0];
			continue;
		}
		now1=num[i],now2=num[j];
		cnt=2;
		ok[1]=now1,ok[2]=now2;
		s[now1]--;
		s[now2]--;
		while(s[temp=now1+now2]>0)
		{
			s[temp]--;
			ok[++cnt]=temp;
			now1=now2;
			now2=temp;
		}
		if(cnt>ans)ans=cnt;
		for(int i=1;i<=cnt;i++)s[ok[i]]++;
	}
	printf("%d\n",ans);
}
```



---

