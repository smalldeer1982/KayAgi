# Maximum Product Strikes Back

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. For each $ i $ ( $ 1 \le i \le n $ ) the following inequality is true: $ -2 \le a_i \le 2 $ .

You can remove any number (possibly $ 0 $ ) of elements from the beginning of the array and any number (possibly $ 0 $ ) of elements from the end of the array. You are allowed to delete the whole array.

You need to answer the question: how many elements should be removed from the beginning of the array, and how many elements should be removed from the end of the array, so that the result will be an array whose product (multiplication) of elements is maximal. If there is more than one way to get an array with the maximum product of elements on it, you are allowed to output any of them.

The product of elements of an empty array (array of length $ 0 $ ) should be assumed to be $ 1 $ .

## 说明/提示

In the first case, the maximal value of the product is $ 2 $ . Thus, we can either delete the first three elements (obtain array $ [2] $ ), or the last two and one first element (also obtain array $ [2] $ ), or the last two elements (obtain array $ [1, 2] $ ). Thus, in the first case, the answers fit: "3 0", or "1 2", or "0 2".

In the second case, the maximum value of the product is $ 1 $ . Then we can remove all elements from the array because the value of the product on the empty array will be $ 1 $ . So the answer is "3 0", but there are other possible answers.

In the third case, we can remove the first two elements of the array. Then we get the array: $ [-2, 2, -1] $ . The product of the elements of the resulting array is $ (-2) \cdot 2 \cdot (-1) = 4 $ . This value is the maximum possible value that can be obtained. Thus, for this case the answer is: "2 0".

## 样例 #1

### 输入

```
5
4
1 2 -1 2
3
1 1 -2
5
2 0 -2 2 -1
3
-2 -1 -1
3
-1 -2 -2```

### 输出

```
0 2
3 0
2 0
0 1
1 0```

# 题解

## 作者：Miraik (赞：10)

由于空序列的乘积算作 $1$，容易发现答案串中一定不含 $0$，因此考虑先用相邻的 $0$ 将序列分成若干子序列。

对于每个子序列，如果它的乘积是正的，我们直接和目前的答案串比较即可。

如果乘积是负数，说明我们需要扔掉最左端或者最右端的负数，直接暴力查找再比较即可。

因为 $|a_i| \le 2$，所以对乘积产生影响的实际上就是 $2$ 与 $-2$，用前缀和即可进行比较。

注意如果子串中只有一个元素且非正数，我们直接跳过即可。如果每个子串都被跳过，说明答案即为空串（乘积为 $1$）。

总时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
//#define int ll
#define pb push_back
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define piii pair<int,pair<int,int> >
using namespace std;
typedef long long ll;
const int N=300005;
const int inf=(1<<30)-1;
const ll inff=1ll<<60;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,a[N],f[N];
int ansl,ansr;
void solve(int l,int r){
	if(l == r && a[l] < 0) return;
	int minus=0;
	for(int i=l;i<=r;i++){
		if(a[i] < 0) minus++;
	}
	if(minus%2){
		int tmp1=0,tmp2=0;
		for(int i=l;i<=r;i++) //找最左边的负数
		    if(a[i] < 0){
		    	tmp1 = i;
		    	break;
		    }
		for(int i=r;i>=l;i--) //找最右边的负数
			if(a[i] < 0){
				tmp2 = i;
				break;
			}
		if(f[r] - f[tmp1] > f[tmp2-1] - f[l-1]) l=tmp1+1;
		else r=tmp2-1;
	}
	if(f[r]-f[l-1] > f[ansr]-f[ansl-1])
	    ansr=r,ansl=l;
}
int main(){int tests=1;tests=read();
while(tests--){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++){
		f[i] = f[i-1] + (abs(a[i])==2);
	}
	if(n == 1){
		if(a[1] > 0) puts("0 0");
		else puts("1 0"); 
		continue;
	}
	int lst=0;
	a[n+1]=0;
	ansl=0,ansr=0;
	for(int i=1;i<=n+1;i++)
	    if(a[i] == 0){
	    	solve(lst+1,i-1);
	    	lst=i;
	    }
	if(ansl == 0 && ansr == 0) printf("%d 0\n",n);
    // 没有找到乘积可以为正数的子串（即每个子串都只有1个非正数），全删掉即可
	else printf("%d %d\n",ansl-1,n-ansr);
}	return 0;
}


```


---

## 作者：stripe_python (赞：3)

# 最大子段积学习笔记

## 最大子段和

经典问题。从数组 $a$ 中取出一段 $[l, r]$，使得 $\sum_{i=l}^{r} a_i$ 最大。

这题有多种做法（如 dp、前缀和、分治）。以下介绍最常用的线性 dp 做法。

令 $dp_i$ 表示以 $a_i$ 结尾的最大子段和，有转移

$$
dp_i=\max(dp_{i-1}+a_i,a_i)
$$

答案即为 $\max dp_i$。

## 最大子段积

从数组 $a$ 中取出一段 $[l, r]$，使得 $\prod_{i=l}^{r} a_i$ 最大。

考虑这个东西和最大子段和的区别。关键点在于，负数乘负数为正数。舍弃的负数转移可能对以后产生影响。

考虑令 $f_i$ 表示以 $a_i$ 结尾的最大子段积，$g_i$ 表示以 $a_i$ 结尾的最小子段积。则转移如下。

$$
f_i=\max(f_{i-1} \times a_i, g_{i-1} \times a_i, a_i)
$$

$$
g_i=\min(f_{i-1} \times a_i, g_{i-1} \times a_i, a_i)
$$

最后答案还是 $\max f_i$。不考虑高精度等，复杂度 $O(n)$。

## 模意义下最大子段积

从数组 $a$ 中取出一段 $[l, r]$，使得 $(\prod_{i=l}^{r} a_i) \bmod p$ 最大。

这个东西就不能简单地用上述做法了。

比如 $p=7$，选择 `2 2` 比 `2 2 2` 更优。

考虑可行性 dp。令 $dp_{i,j}$ 表示以 $a_i$ 结尾的最大子段积在模 $p$ 意义下为 $j$ 是否可行。

判断 $dp_{i,j}$ 是否可行时，若删除 $a_i$ 的状态 $dp_{i-1,j\times a_i \bmod p}$ 是可行的，则 $dp_{i,j}$ 可行。

可以 bitset 优化。复杂度 $O(np)$。

参考代码：

```cpp
#include <bits/stdc++.h>
#define N 10005
using namespace std;

int n, p, a[N];
bitset<N> dp[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> p;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] = (a[i] % p + p) % p, dp[i][1] = 1;
	}
	long long res = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < p; j++) {
			if (dp[i - 1][j]) {
				long long t = j * a[i] % p;
				dp[i][t] = 1, res = max(res, t);
			}
		}
	}
	cout << res;
	
	return 0;
}
```

## 最大子段积方案输出

就是本题 [CF1660D](https://www.luogu.com.cn/problem/CF1660D)。

题意：给定长为 $n$ 的数组 $a$，$\forall 1 \le i \le n, -2 \le a_i \le 2$。从数组 $a$ 中取出一段 $[l, r]$，使得 $\prod_{i=l}^{r} a_i$ 最大。输出 $l-1,n-r$。

回归最大子段积的本质，显然最大子段积不应为 $0$，故按 $0$ 把 $a$ 切开，对每个 $[l, r]$ 分别统计。

记 $[l,r]$ 之间的负数有 $m$ 个。如果 $m$ 为偶数，则 $\prod_{i=l}^{r} a_i$ 即为最大子段积。

考虑 $m$ 为奇数，记 $x$ 为 $[l,r]$ 中第一个负数的位置，$y$ 为 $[l,r]$ 中最后一个负数的位置。由于 $1$ 和 $-1$ 不会影响子段积，判断哪边舍弃的绝对值不小于 $2$ 的数最少并选择即可。

最后本题可以用一个前缀和方便地统计绝对值不小于 $2$ 的数。

```cpp
#include <bits/stdc++.h>
#define N 200005
using namespace std;

int t, n, a[N], pre[N];
int resl, resr;

inline void solve(int l, int r) {
	if (l > r || r > n) return;
	//cout << l << ' ' << r << endl; 
	int neg = 0;
	for (int i = l; i <= r; i++) {
		if (a[i] < 0) neg++;
	}
	if (neg & 1) {
		int x = 0, y = 0;
		for (int i = l; i <= r; i++) {
			if (a[i] < 0) {x = i; break;}
		}
		for (int i = r; i >= l; i--) {
			if (a[i] < 0) {y = i; break;}
		}
		if (pre[r] - pre[x] > pre[y - 1] - pre[l - 1]) l = x + 1;
		else r = y - 1;
	} 
	if (pre[r] - pre[l - 1] > pre[resr] - pre[resl - 1]) resl = l, resr = r;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> t;
	while (t--) {
		memset(a, 0, sizeof(int) * (n + 1));
		memset(pre, 0, sizeof(int) * (n + 1));
		cin >> n; 
		resl = 1, resr = 0;
		for (int i = 1; i <= n; i++) cin >> a[i], pre[i] = pre[i - 1] + (abs(a[i]) >= 2);
		
		if (n == 1) {
			if (a[1] >= 1) cout << "0 0\n";
			else cout << "1 0\n";
			continue;
		}
		int last = 0;  // 上一个0 
		for (int i = 1; i <= n; i++) {
			if (a[i] == 0) solve(last + 1, i - 1), last = i;
		}
 		if (a[n] != 0) solve(last + 1, n);
		//cout << resl << ' ' << resr << '\n';
		cout << resl - 1 << ' ' << n - resr << '\n';
	}
	
	return 0;
}
```

---

## 作者：卷王 (赞：1)

注意到一个结论：答案是一段区间 $[l,r]$，其中不能有 $0$（因为如果有 $0$，那么序列的积就等于 $0$，显然不是最优），符号为正（即区间内必须有 **偶数个** 负数）。在满足上述情况下，让 $-2$ 和 $2$ 的数量最多（因为 $-1$ 和 $1$ 都不会改变积的值）。

定义一个 $sum$ 数组表示 $2$ 和 $-2$ 数量的前缀和，然后扫一遍序列，每次把两个 $0$ 之间的序列都操作一下，与答案 $ansl$ 和 $ansr$ 的结果进行比较更新即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 1, ansl = 0, ansr = 0;
int a[200007];
int sum[200007];

void dfs(int l, int r) {
//	printf("%d %d\n", l, r);
	if(l == r && a[l] < 0) return ;
	int num = 0;
	up(i, l, r) {
		if(a[i] < 0) {
			num++;
//			if(num == 2) num = 0;
		}
	}
	if(num & 1) {
		int x = l, y = r;
		up(i, l, r) if(a[i] < 0) { x = i; break; }
		down(i, r, l) if(a[i] < 0) { y = i; break; }
//		printf("%d %d\n", x, y);
		if(sum[r] - sum[x] > sum[y - 1] - sum[l - 1]) l = x + 1;
		else r = y - 1; //取更优
	}
	if(sum[r] - sum[l - 1] > sum[ansr] - sum[ansl - 1]) {
		ansl = l, ansr = r;
//		printf("%d %d good\n", l, r);
	}
}

signed main() {
	T = read();
	while(T--) {
		n = read();
		up(i, 1, n) {
			a[i] = read();
			sum[i] = sum[i - 1];
			if(a[i] == 2 || a[i] == -2) {
				sum[i]++;
//				printf("%d %d\n", i, sum[i]);
			}
		}
		a[n + 1] = 0; ansl = 0, ansr = 0;
		int lst = 0;
//		printf("ok\n");
		up(i, 1, n + 1) {
			if(a[i] == 0) {
//				printf("%d %d dfs\n", lst, i);
				dfs(lst + 1, i - 1);
				lst = i;
			}
		}
//		printf("%d %d\n", ansl, ansr);
		if(ansl == 0 && ansr == 0) printf("%d 0\n", n);
		else printf("%d %d\n", ansl - 1, n - ansr);
	}
	return 0;
}
```

---

## 作者：zzhbpyy (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1660D)

## 思路

直接用数列中的 $0$ 将数列分割成若干个部分。因为若剩下的数中包括 $0$，显然乘积为 $0$，不如空数组的 $1$。

对于每一个分割出来的数列，我们直接统计数列中负数的个数，记作 $ans$。接着，我们对 $ans$ 的奇偶性进行讨论。

1. $ans$ 为奇数。为了让结果为正数，我们必须去掉一个负数。考虑 $O(n)$ 找到开头和结尾的第一个负数模拟结果并选择最优方案。
2. $ans$ 为偶数。无须删数，直接统计比对答案即可。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],ans1,ans2;
vector<int>k;
int solve(){
	int fhui=0,ans=0;//fhui统计剩余数列中2或-2的个数，代替统计乘积
	for(int i=0;i<k.size();i++)
		if(k[i]<0)ans++;
	if(ans&1){
		int y=0,x=0;
		for(int i=0;i<k.size();i++){
			if(k[i]==2||k[i]==-2)y++;
			if(k[i]<0){ans1=i+1;break;}
		}
		for(int i=k.size()-1;i>=0;i--){
			if(k[i]==2||k[i]==-2)x++;
			if(k[i]<0){ans2=k.size()-i;break;}
		}
		if(x>y)ans2=0;
		else ans1=0;
	}
	else ans1=ans2=0;
	for(int i=ans1;i<k.size()-ans2;i++){
		if(k[i]==2||k[i]==-2)fhui++;
	}
	return fhui;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t,ch1,ch2,tmp,ct=0;
	cin>>t;vector<int>len;
	while(t--){
		cin>>n;tmp=-1;//tmp记录迄今为止最多“2”的个数
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==0){int y=solve();
				if(y>tmp)ch1=i-k.size()-1+ans1,ch2=n-i+1+ans2,tmp=y;
				k=vector<int>();
			}
			else k.push_back(a[i]);
		}
		if(a[n]!=0){
			int y=solve();
			if(y>tmp)ch1=n-k.size()+ans1,ch2=ans2,tmp=y;k=vector<int>();
		}
		cout<<ch1<<' '<<ch2<<'\n';
	}
}
```

---

## 作者：GWBailang (赞：1)

#### [原题传送](https://www.luogu.com.cn/problem/CF1660D)
思路比较简单就是有点不好想。

数组为空的话乘积为 $1$，所以我们最终得到的这一串数一定要满足一下条件，不然的话还不如选空串：

- 没有 $0$，否则乘积就是 $0$。
- 有偶数个负数，否则乘积就是负数。

根据不能选 $0$ 这一条限制，我们可以把 $0$ 当做“分割点”，例如：
```
1 2 -1 -2 0 2 1 0 -2 -1 2
```
这串数最优解只能在```1 2 -1 -2```，```2 1```，```-2 -1 2```和空串中，下文为了方便我们管这些组数字叫“数字串”。

我们可以每找到一个“数字串”，来判断是否有偶数个负数。

有偶数个负数就很简单，负负得正，跟目前的最大值做比较，最大值记录的是有这一段里有几个数的绝对值为 $2$。

如果这一段有奇数个负数，我们要找到这一段最左边和最右边的两个负数，他们俩有可能是同一个数，然后我们就看，是去掉从左边到左边的第一个负数会“损失”的绝对值为 $2$ 的个数少，还是去掉从右边到右边的第一个负数会“损失”的绝对值为 $2$ 的个数少。去掉“损失”少的那一边，留下剩下的和刚才的最大值作比较。

#### 举个例子：

例如我们要看这个“数字串”：```1 2 -1 2 1 -2 2 -2 1 2```。

这一串有奇数个负数。

首先先找到最左边的负数，是第三项，$-1$。然后再找最右边的负数，是第八项，$-2$。接下来比较是删掉```1 2 -1```损失的小还是删掉```-2 1 2```损失的小。显然是左边这一串数字包含的绝对值为 $2$ 的数少。我们把左边这一串给删掉，写程序时可以将左边界变成 $4$。

最后对于这个“数字串”，在有偶数个负数的情况下有最多就有 $5$ 个数的绝对值为 $2$，跟之前的最大值做比较即可。

#### 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long a[200005];
long long qzhf[200005];//有几个负数(前缀和)
long long qzh2[200005];//有几个数的绝对值为2(前缀和)
long long da,l,r;
long long f1,f2;//对与每段，第一个负数和最后一个负数
void hanshu(long long zuo,long long you){
	if(zuo>=you&&a[zuo]<=0)return;
	if((qzhf[you]-qzhf[zuo-1])%2==1){//如果有奇数个负数
		f1=zuo;f2=you;//分别从左，右两边开始找负数
		while(a[f1]>0)f1++;//从左边开始，如果这个数不是负数就继续找
		while(a[f2]>0)f2--;//同上，从右边开始找第一个负数
		if(qzh2[you]-qzh2[f2-1]>qzh2[f1]-qzh2[zuo-1])zuo=f1+1;//左边的2少就删掉左边
		else you=f2-1;//否则删掉右边
	}
	//有偶数个负数就不用再改变边界了
	if(qzh2[you]-qzh2[zuo-1]>da){//如果这一段2的个数比之前的最大值多
		da=qzh2[you]-qzh2[zuo-1];//更新最大值
		l=zuo;r=you;//更新左边界
	}
}
int main(){
	long long t,n,zuo;
	cin>>t;
	while(t--){
		cin>>n;
		zuo=1;da=0;//将左边界与最大值初始化
		l=1;r=0;//初始化
		qzh2[0]=0;qzhf[0]=0;//初始化
		for(long long i=1;i<=n;i++){
			cin>>a[i];
			qzh2[i]=qzh2[i-1];qzhf[i]=qzhf[i-1];
			if(abs(a[i])==2)qzh2[i]++;//前缀和预处理
			if(a[i]<0)qzhf[i]++;
		}
		a[n+1]=0;//为了最后不越界，要将a[n+1]设置成0
		qzh2[n+1]=qzh2[n];//将第n+1项也预处理了
		qzhf[n+1]=qzhf[n];
		for(long long i=1;i<=n+1;i++){
			if(a[i]==0){//如果这一项是0
				hanshu(zuo,i-1);
				zuo=i+1;//更新左边界
			}
		}
		cout<<l-1<<" "<<n-r<<endl;//输出
	}
	return 0;
}
```

---

## 作者：yanhao40340 (赞：1)

### 题意
给定一个长度为 $n$ 的序列，求这个序列的最大字串积。空串的积为 $1$。
### 分析
因为空串的积为 $1$，那么如果答案不为空串，则一定不能为 $0$ 或负数。

所以，我们可以把整个序列以 $0$ 为间隔，分成 $x$ 段。

对于每一段，我们可以分别来求它的最大字串积。答案取最大的那一段的积左边去掉的和右边去掉的即可。

接下来，我们只用对每一段求最大字串积：
### 最大字串积
如果这一段的乘积本来就是正数，那么整个段就是最大字串。

如果这一段的乘积是负数，我们就对该段的左右分别进行统计。

找到最左边和最右边的负数，计算出如果要删除此负数后积会少多少。删掉对答案损失小的一边。

最后因为 $n \leq 200000$，所以不能直接计算字串的积。由于 $|a_i| \leq 2$，所以字串的积一定可以用 $2$ 的幂，直接计算指数部分即可。

时间复杂度 $O(n)$，可以通过。

核心代码大概长这样：
```cpp
void solve(vector<int> v,int fr,int bk){
	short fl=1;int val=0;
	for (auto i:v){
		if (i==-2||i==2) val+=1;
		fl*=(i>0?1:-1);
	}
	if (fl>0){
		if (val>ans) ans=val,l=fr,r=bk-1;
		return;
	}
	int left=0,right=v.size()-1,lval=0,rval=0;
	while (v[left]>0){
		if (v[left]==2) lval+=1;
		++left;
	}
	if (v[left]==-2) lval+=1;
	while (v[right]>0){
		if (v[right]==2) rval+=1;
		--right;
	}
	if (v[right]==-2) rval+=1;
	if (lval<=rval) fr+=left+1,val-=lval;
	else bk-=v.size()-right,val-=rval;
	if (val>ans) ans=val,l=fr,r=bk-1;
	return;
}
```
完整代码见 [link](https://codeforces.com/contest/1660/submission/160911025) 。

---

## 作者：Stars_visitor_tyw (赞：0)

## CF1660D Maximum Product Strikes Back 题解
### 思路
因为题目中说了 $|a_i| \le 2$，也就是 $-2 \le a_i \le 2$。我们可以先假设 $a_i \neq 0$，非常容易发现删 $1$ 并不会对数组绝对值符号有任何影响，删 $-1$ 只会控制数组乘积的符号，$2$、$-2$ 才对数组绝对值起绝对性影响。

因此得出结论：

若数组乘积为正，不用删任何数，若数组乘积为负，则在数组收尾两边中选 $|a_i|=2$ 较少的一边删除其所在前缀或后缀

现在我们把假设去掉来分析：

- 题目说明，若数组为空，默认乘积为 $1$，所以 $0$ 是坚决不能存在于数组之中，必须全部删除。

- 本题相当于拿 $0$ 做挡板，把原数组分为很多细分的除 $0$ 的区间，只需要对这部分取 $|a_i|=2$ 较多的区间作为留下的数组即可。

### 代码

```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
#define ulll unsigned long long
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int t, n, ansl, ansr;
int a[200005];
struct node
{
	int u, v, dis;
}b[200005];
int solve(int l,int r)
{
	int num1=0, num2=0, mini2=1e9, maxi2=0;
	for(int i=l;i<=r;i++)
	{
		if(a[i]>0)
		{
		    num1++;
		}
		else 
		{
			num2++;
			mini2=min(mini2,i);
			maxi2=i;
		}
	}
	if(num2%2==0)
	{
		ansl=l-1;
		ansr=n-r;
	}
	else
	{
		int w1=0,w2=0;
		bool flag=false;
		for(int i=l;i<=mini2;i++)
		{
			if(abs(a[i])==2)
			{
			    w1++;
			}
		} 
		for(int i=maxi2;i<=r;i++)
		{
			if(abs(a[i])==2)
			{
			    w2++;
			}
		}
		if(w1>=w2)
		{
			ansl=l-1;
			ansr=n-maxi2+1;
		}
		else 
		{
			ansl=mini2;
			ansr=n-r;
		}
	}
	int answer=0;
	for(int i=ansl+1;i<=n-ansr;i++)
	{
		if(abs(a[i])==2)
		{
		    answer++;
		}
	}
	return answer;
}
bool cmp(node x,node y)
{
    return x.dis>y.dis;
}
int main()
{
	cin>>t;
	while(t--)
	{
		int cnt0=0, tot=0;
		n=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			if(a[i]==0)
			{
			    cnt0++;
			}
		}
		if(cnt0==n)
		{
			cout<<n<<" "<<0<<"\n";
		}
		else if(n==1)
		{
			if(1>=a[1])
			{
			    cout<<1;
			}
			else
			{
			    cout<<0;
			}
			cout<<" "<<0<<endl;
		}
		else if(cnt0>0)
		{
			int k=1,k1=n;
			while(a[k]==0)
			{
			    k++;
			}
			while(a[k1]==0)
			{
			    k1--;
			}
			int x,y;
			x=y=k;
			if(k==k1)
			{
			    tot++;
				b[tot].u=x;
				b[tot].v=y;
				b[tot].dis=solve(b[tot].u,b[tot].v);
				b[tot].u=ansl;
				b[tot].v=ansr;
			}
			for(int i=k+1;i<=k1;i++)
			{
				if(a[i-1]==0&&a[i]!=0)
				{
				    x=y=i;
				}
				if(a[i]!=0&&a[i-1]!=0)
				{
				    y++;
				}
				if(a[i]==0||i==k1)
				{
				    tot++;
					b[tot].u=x;
					b[tot].v=y;
					b[tot].dis=solve(b[tot].u,b[tot].v);
					b[tot].u=ansl;
					b[tot].v=ansr;
				}		
			}
			sort(b+1,b+tot+1,cmp);
			cout<<b[1].u<<" "<<b[1].v<<"\n";
		}
		else 
		{
			int meishayong=solve(1,n);
			cout<<ansl<<" "<<ansr<<"\n";
		}
	}
	return 0;
} 

---

## 作者：shaozhehan (赞：0)

题目大意：

给你一个长度为 $n$ 的数组 $a$，对于 $\forall a_i$，都有 $-2\leq a_i\leq 2$。现在，你可以从左边删除 $x$ 个元素，从右边删除 $y$ 的元素，输出剩下元素成绩的最大值。若剩下 $0$ 个元素，那么乘积默认为 $1$。本题有 $t$ 组数据。

思路：

我们可以发现，剩下的数中显然不能有 $0$，所以我们可以把 $a$ 分成一个个由 $0$ 分开的子段，然后分别去处理就行了。我们可以维护两个前缀和数组 $pre\_2$ 和 $pre\_minus$，分别前缀和出来 $|a_i|=2$ 和 $a_i<0$ 的满足要求的 $i$ 的个数。接着，如果一段子段中的负数个数为奇数，那么我们就找到最左边和最右边的负数，比较一下删掉最左边的负数和删掉最右边的负数后剩余的 $2$ 或 $-2$ 的个数来决定删哪一边最好。前面的统计操作都可以使用维护的两个前缀和数组来实现。我们可以定义两个变量 $ans\_l$ 和 $ans\_r$ 来记录答案，初始值都为 $0$。

为了不漏算最后一个区间，我们可以把 $a_{n+1}$ 设为 $0$。如果 $n=1$，如果 $a_1>0$，那么不删为好，输出 $0\space0$；否则输出 $1\space0$ 或者 $0\space1$。如果最终 $ans\_l$ 和 $ans\_r$ 都还是 $0$ 的话，那么全删了，也就是输出 $n\space 0$。否则，输出 $ans\_l-1$ 和 $n-ans\_r$。

坑点：

1. 本题有 $t$ 组数据！
1. 前面提到的特判要注意！
1. 输出 $ans\_l-1$ 和 $n-ans\_r$，不是 $ans\_l$ 和 $ans\_r$！

上代码：

```cpp
#include <iostream>
using namespace std;

int a[200002], pre_2[200002], pre_minus[200002];

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }
        if (n == 1){
            if (a[1] > 0){// 特判
                cout << "0 0\n";
            } else {
                cout << "1 0\n";
            }
        } else {
            int lft = 0;
            a[n + 1] = 0;
            for (int i = 1; i <= n + 1; i++){// 维护前缀和数组
                pre_2[i] = pre_2[i - 1];
                if (a[i] == 2 || a[i] == -2){
                    pre_2[i]++;
                }
            }
            for (int i = 1; i <= n + 1; i++){
                pre_minus[i] = pre_minus[i - 1];
                if (a[i] < 0){
                    pre_minus[i]++;
                }
            }
            int ans_l = 0, ans_r = 0;
            for (int i = 1; i <= n + 1; i++){
                if (a[i] == 0){// 分段
                    int l = lft + 1, r = i - 1;
                    if (l != r || a[l] >= 0){
                        int minus = pre_minus[r] - pre_minus[l - 1];
                        if (minus & 1){// 判断是不是奇数个负数
                            int lft_minus = 0, rght_minus = 0;
                            for (int j = l; j <= r; j++){
                                if (a[j] < 0){
                                    lft_minus = j;
                                    break;
                                }
                            }
                            for (int j = r; j >= l; j--){
                                if (a[j] < 0){
                                    rght_minus = j;
                                    break;
                                }
                            }
                            if (pre_2[r] - pre_2[lft_minus] > pre_2[rght_minus - 1] - pre_2[l - 1]){
                                l = lft_minus + 1;
                            } else {
                                r = rght_minus - 1;
                            }
                        }
                        if (pre_2[ans_r] - pre_2[ans_l - 1] < pre_2[r] - pre_2[l - 1]){
                            ans_l = l;
                            ans_r = r;
                        }
                    }
                    lft = i;
                }
            }
            if (ans_l == 0 && ans_r == 0){// 特判
                cout << n << " 0\n";
            } else {
                cout << ans_l - 1 << " " << n - ans_r << "\n";// 输出要注意
            }
        }
    }
    return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

我们发现，空数组答案都是 $1$ 了，所以这个区间里不可能出现 $0$。我们把 $a_0$ 看作 $0$，把 $a_{n+1}$ 看作 $0$,则删去了前后缀后的答案区间一定夹在原来的两个零之间。

我们发现，空数组答案都是 $1$ 了，所以这个区间里的积不可能是负数，换句话说，这段区间内的负数个数只可能是偶数。所以我们只需要在这个 $0$ 与 $0$ 夹的区间里，再去掉一段有奇数个负数的区间，同时满足剩下的区间的积最大就可以了。

我们发现，因为我们剩下的这个区间的积为正数，而两个正数，绝对值大的那个数更大，又因为这个区间内没有 $0$，所以不管是 $1,-1,2,-2$，都能使这个区间的积的绝对值增加（$\pm 2$）或不变（$\pm 1$）所以我们考虑删掉最左的且删除数字个数最少一段或者最右的且删除数字个数最少的一段，将这两种方案取最优解，即是在这两个 $0$ 之间能取到的最大连续区间乘积。

我们发现，每两个 $0$ 之间的区间是互不干扰的。所以我们只要对于每个区间求出最优解，然后对于每个最优解求出最优解就可以了。

我们发现，只有绝对值为 $2$ 的数才会对答案的绝对值产生影响，且一定是正整数。所以最大积一定形如 $2^x$ 形式（$x$ 为非负整数），我们只需要记录 $x$ 的值就能判断大小，就不用写高精了。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
void cf(){
	int n=read();
	int a[200005];
	int zero[200005];
	int cnt=0;
	for(int i=1;i<=n;i++)
		a[i]=read();
	a[0]=0;
	a[n+1]=0;
	for(int i=0;i<=n+1;i++)
		if(!a[i]){
			cnt++;
			zero[cnt]=i;
		}
	int sum=0;
	int x=1,y=0;
	for(int i=1;i<cnt;i++){
		if(zero[i]+1==zero[i+1]) continue;
		int xx=0;
		int f=1;
		for(int j=zero[i]+1;j<zero[i+1];j++){
			if(a[j]<0) f*=-1;
			if(abs(a[j])==2) xx++;
		}
		if(sum<xx&&f>0){
			sum=xx;
			x=zero[i]+1;
			y=zero[i+1]-1;
		}
		if(f<0){
			int xxx=xx;
			for(int j=zero[i]+1;j<zero[i+1];j++){
				if(abs(a[j])==2) xxx--;
				if(a[j]<0) f*=-1;
				if(f>0){
					if(sum<xxx){
						sum=xxx;
						x=j+1;
						y=zero[i+1]-1;
					}
					break;
				}
			}
			xxx=xx;
			f=-1;
			for(int j=zero[i+1]-1;j>zero[i];j--){
				if(abs(a[j])==2) xxx--;
				if(a[j]<0) f*=-1;
				if(f>0){
					if(sum<xxx){
						sum=xxx;
						x=zero[i]+1;
						y=j-1;
					}
					break;
				}
			}
		}
	}
	if(x>y){
		x=1;
		y=0;
	}
	printf("%d %d\n",x-1,n-y);
	return;
}
int main(){
    int t=read();
    for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：0)

### Analysis

其实题意就是**选一个子串使得乘积最大**。

设 $b_i=[a_i<0]$。首先，**答案至少为** $1$，因为可以是空串。所以接下来我们只需要考察**区间内 $b_i=\text{True}$ 的个数为偶数**的子串。

将原序列按照 $a_i=0$ 的位置分段，在每段求答案后取最大值即可。

发现每个数**只有两种因子** $-1$ 和 $2$。

设当前段为 $[l,r]$，其中 $b_i=\text{True}$ 的个数为 $cnt$。

若 $2\ |\ cnt$，则直接选取整段 $[l,r]$ 作为答案即为乘积最大。

否则，设第一个和最后一个 $b_i=\text{True}$ 的位置分别为 $x,y$，则此段答案为 $[l,y-1]$ 和 $[x+1,r]$ 答案中的较大值。

时间 $O(n)$

### Code

[Link（代码较丑，见谅）](https://codeforces.com/contest/1660/submission/152282315)

---

