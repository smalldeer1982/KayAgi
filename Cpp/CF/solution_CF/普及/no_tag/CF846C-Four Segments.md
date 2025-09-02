# Four Segments

## 题目描述

You are given an array of $ n $ integer numbers. Let $ sum(l,r) $ be the sum of all numbers on positions from $ l $ to $ r $ non-inclusive ( $ l $ -th element is counted, $ r $ -th element is not counted). For indices $ l $ and $ r $ holds $ 0<=l<=r<=n $ . Indices in array are numbered from $ 0 $ .

For example, if $ a=[-5,3,9,4] $ , then $ sum(0,1)=-5 $ , $ sum(0,2)=-2 $ , $ sum(1,4)=16 $ and $ sum(i,i)=0 $ for each $ i $ from $ 0 $ to $ 4 $ .

Choose the indices of three delimiters $ delim_{0} $ , $ delim_{1} $ , $ delim_{2} $ ( $ 0<=delim_{0}<=delim_{1}<=delim_{2}<=n $ ) and divide the array in such a way that the value of $ res=sum(0,delim_{0}) $ - $ sum(delim_{0},delim_{1}) $ + $ sum(delim_{1},delim_{2}) $ - $ sum(delim_{2},n) $ is maximal.

Note that some of the expressions $ sum(l,r) $ can correspond to empty segments (if $ l=r $ for some segment).

## 样例 #1

### 输入

```
3
-1 2 3
```

### 输出

```
0 1 3
```

## 样例 #2

### 输入

```
4
0 0 -1 0
```

### 输出

```
0 0 0
```

## 样例 #3

### 输入

```
1
10000
```

### 输出

```
1 1 1
```

# 题解

## 作者：Uuuuuur_ (赞：5)

## 题目大意 ##
给定 $a_1 \text{,} a_2...a_n$，求 $i,j,k(0\le i\le j\le k\le n)$ 满足 $\sum_{x = 1}^{i}a_x - \sum_{x=i+1}^{j}a_x+ \sum_{x=j+1}^{k}a_x-\sum_{x=k+1}^{n}a_x$ 最大。

若有多种方案，输出任意一种。

## 思路 ##
###	第一步
首先考虑暴力枚举，枚举 $i,j,k$，然后利用**前缀和**计算，时间复杂度$O(n^3)$，显然超时。

### 第二步
有没有什么可以优化的地方……仔细想一想，我们要求的式子，前两项只和 $i,j$ 有关，后两项只和 $j,k$ 有关，如果 $j$ 固定了，它们就不会互相干扰了。那么，我们就可以使用**贪心**的思想。

对于给定的 $j$，我们可以枚举 $i$ 来计算出前面两项的最大值，再枚举 $k$ 计算出后面两项的最大值，它们俩的和一定是对于这个特定的 $j$ 所能得到的的最大值。

所以，我们只要枚举 $j$，然后按照上述方法计算，就能得出最优的 $i,j,k$。

时间复杂度 $O(n^2)$。

## 代码
```cpp
#include <iostream>
using namespace std;
typedef long long ll; 
const ll inf = 0x3f3f3f3f3f3f3f3f; 
int n;
ll pre[5005], ansi, ansj, ansk, anssum = -inf; //十年OI一场空，不开long long见祖宗
inline ll sum(int l, int r) {
	if (l == r) return 0;
	return pre[r] - pre[l]; //因为原式中都是x+1与y，所以我们可以算尾不算头
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		pre[i] = pre[i - 1] + x;
	}
	for (int j = 0; j <= n; j++) {
		ll maxx = -inf; //前两项或后两项的最大值
		int ri, rk; //对于当前的j，最优的i，k
		ll ls = 0;//对于当前的j，式子的最大值
		for (int i = 0; i <= j; i++) {
			ll s = sum(0, i) - sum(i, j);
			if (s > maxx) maxx = s, ri = i;
		}
		ls += maxx;
		maxx = -inf;
		for (int k = j; k <= n; k++) {
			ll s = sum(j, k) - sum(k, n);
			if (s > maxx) maxx = s, rk = k;
		}
		ls += maxx;
		if (ls > anssum) { //如果当前的最大值大于全局最大值则更新
			anssum = ls;
			ansi = ri;
			ansj = j;
			ansk = rk;
		}
	}
	cout << ansi << ' ' << ansj << ' ' << ansk << endl;
	return 0;
}
```


---

## 作者：lukelin (赞：4)

我们暴力枚举一下$delim_{1}$  
然后对于每个$delim_{1}$，O(n)扫一遍+前缀和求出最大$delim_{0}$和$delim_{2}$，然后记录一下它们的位置就行啦

放个代码
```cpp
#include <cstdio>
#define ll long long

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

long long qzh[5005];

int main(){
    int n = read();
    for (int i = 1; i <= n; ++i)
        qzh[i] = read();
    for (int i = 1; i <= n; ++i)
        qzh[i] += qzh[i - 1];
    long long cur1, cur2, ans = 0;
    int pos1, pos3, p1 = 0, p2 = 0, p3 = 0;
    for (int i = 0; i <= n; ++i){
        cur1 = cur2 = 0;
        pos1 = 0, pos3 = i;
        for (int j = 0; j <= i; ++j)
            if (qzh[j] - (qzh[i] - qzh[j]) > cur1){
                cur1 = qzh[j] - (qzh[i] - qzh[j]);
                pos1 = j;
            }
        for (int j = i; j <= n; ++j)
            if ((qzh[j] - qzh[i]) - (qzh[n] - qzh[j]) > cur2){
                cur2 = (qzh[j] - qzh[i]) - (qzh[n] - qzh[j]);
                pos3 = j;
            }
        if (cur1 + cur2 > ans){
            ans = cur1 + cur2;
            p1 = pos1;
            p2 = i;
            p3 = pos3;
        }
    }
    printf("%d %d %d", p1, p2, p3);
    return 0;
}
```

---

## 作者：Sol1 (赞：3)

真的没有人用线性解法？？？

~~⌈这题能开到1e5的⌋~~

线性解法为分阶段dp。

进入正题：设$dp_{i,0/1/2/3}$为前$i$个元素，最后一个元素属于第$1/2/3/4$段的最大和。

转移方程为$dp_{i,j}=\max\limits_{k<j}\{dp_{i-1,k}\pm a_i\}$，其中看是第几段来选择是$+a_i$还是$-a_i$。

寻找方案时，可以用一个$0 \leq path_{i,j} \leq 3$数组来计算第$i$个位置是从哪里转移过来的。

最后从后往前扫一遍，开一个变量$pos$，最开始赋值为3，如果$path_i \neq i$则表示第$i-1$位后面有分界点，就将$j$满足$path_{i,pos} \leq j < pos$的$delim_j$全部赋值为$i-1$，最后输出就可以了。

注意long long的问题。

总时间复杂度应该是$\Theta(16N)$左右。

我的线性解法是目前的最优解，欢迎打破（

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

int n, path[5005][5];
long long dp[5005][5], a[5005];

void Read() {
	scanf("%d", &n);
	for (int i = 1;i <= n;i++) {
		scanf("%I64d", &a[i]);
	}
}

void Solve() {
	//dp要初始化为无穷小，因为可能无法达到正值
	memset(dp, 0xcf, sizeof(dp)); dp[0][1] = 0;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= 4;j++) {
			for (int k = 1;k <= j;k++) {
				long long cur = ((j & 1) ? 1 : -1) * a[i] + dp[i - 1][k];//计算转移值
				if (dp[i][j] < cur) {
					dp[i][j] = cur;//dp转移
					path[i][j] = k;//记录路径
				}
			}
		}
	}
	int pos, ans[4]; long long mx = 0xcfcfcfcfcfcfcfcf;
	//处理分界点在n上的情况
	for (int i = 1;i <= 4;i++) {
		if (dp[n][i] > mx) {
			mx = dp[n][i]; pos = i;
		}
	}
	for (int i = pos;i <= 3;i++) {
		ans[i] = n;
	}
	for (int i = n;i >= 1;i--) {
		if (path[i][pos] != pos) {
			for (int j = path[i][pos]; j < pos;j++) {
				ans[j] = i - 1;//记录分界点
			}
		}
		pos = path[i][pos];
	}
	printf("%d %d %d", ans[1], ans[2], ans[3]);
}

int main() {
	Read(); Solve();
	return 0;
}
```

---

## 作者：fpjo (赞：2)

## 题意

给定长度为n的序列a，求出三个点i,j,k(0<=i<=j<=k<=n)，使得a[1]+...+a[i]-a[i+1]-...-a[j]+a[j+1]+...+a[k]-a[k+1]-...-a[n]最大

## 思路

最开始没想出来,然后看了题解

先对序列求前缀和,设为$sum$

那么最大值为$max\{ sum_i-(sum_j-sum_i)+(sum_k-sum_j)-(sum_n-sum_k)\}$

化简后就是求$max\{sum_i+sum_k-sum_j\}$时$i,j,k$的位置

题解里面是枚举$j$,然后再$O(n)$扫前缀和求$sum_i,sum_k$的最大值

但$j$是逐渐变化的,我们可以用单调队列来维护$sum_k$的最大值,至于$sum_i$的最大值直接维护即可

时间复杂度$ O(n)$

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ansi,ansj,ansk,l=1,r=0;
int a[5010],q[5010];
signed main(){
	long long ans=(-(1ll<<62));
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){scanf("%lld",&a[i]);a[i]+=a[i-1];}
	for(int i=1;i<=n;i++){
		while(l<=r && a[i]>a[q[r]])r--;
		q[++r]=i;
  }
	int ki=0,kk,sum1,sum2,sum3;
	for(int j=0;j<=n;j++){
		if(q[l]<j)l++;kk=q[l];
		if(a[ki]<a[j])ki=j;
		if(a[kk]+a[ki]-a[j]>ans)ans=a[kk]+a[ki]-a[j],ansi=ki,ansj=j,ansk=kk;
	}
	printf("%lld %lld %lld\n",ansi,ansj,ansk);
	return 0;
}
```



---

## 作者：泠小毒 (赞：1)

# Four Segments
给定长度为n的序列a，求出三个点i,j,k(0<=i<=j<=k<=n)，使得a[1]+...+a[i]-a[i+1]-...-a[j]+a[j+1]+...+a[k]-a[k+1]-...-a[n]最大
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190514/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190514.html)
## 解法
如果暴力就是n的立方，无法接受啊QAQ

想一想优化，对于每个点都可以O(n)求出以它为j点的最优i点和k点，且i点和k点不相干

就可以优化成n方了
## ac代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
long long n,a[5010],l[5010],r[5010],sl,sr,suml,sumr,sum,ans=-23333333333333,res=0;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[i]+=a[i-1];
	for(int i=0;i<=n;i++)
	{
		l[i]=0,r[i]=i;
		sl=0,sr=a[i];
		for(int j=1;j<=i;j++)
		{
			suml=a[j]-a[0],sumr=a[i]-a[j];
			if(suml-sumr>sl-sr)sl=suml,sr=sumr,l[i]=j;
		}
		sum=sl-sr;
		sl=0,sr=a[n]-a[i];
		for(int j=i+1;j<=n;j++)
		{
			suml=a[j]-a[i],sumr=a[n]-a[j];
			if(suml-sumr>sl-sr)sl=suml,sr=sumr,r[i]=j;
		}
		sum+=sl-sr;
		if(sum>ans)ans=sum,res=i;
	}
	printf("%lld %lld %lld\n",l[res],res,r[res]);
	return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定长度为 $n$ 的序列 $a$，求出三个点$d_0,d_1,d_2(0 \le d_0 \le d_1 \le d_2 \le n)$，使得 $\sum_{i=1}^{d_0}a_i-\sum_{i=d_0+1}^{d1}a_i+\sum_{i=d_1+1}^{d_2}a_i-\sum_{i=d_2+1}^na_i$ 最大。

## 思路1

其实这道题就相当于把序列 $a$ 割成 4 段，正由于此我们才有了暴力枚举解法：时间复杂度为 $O(n)$，由于 $n$ 较小，因此不做预处理写成时间复杂度为 $O(n^2)$ 的代码也行。

下面来讲暴力的思路，你可以枚举 $d_1$ 的位置，然后相应的找出 $d_0$ 与 $d_2$ 的位置。

先来看看对于一个 $d_1$ 如何找 $d_0$。根据题意，在 $d_1$ 前（包括 $d_1$）的这些数的和为 $\sum_{i=1}^{d_0}a_i-\sum_{i=d_0+1}^{d1}a_i$，我们可以将 $\sum_{i=d_0+1}^{d1}a_i=\sum_{i=1}^{d_1}a_i-\sum_{i=0}^{d_0}a_i$ 带入得和为 $2 \times \sum_{i=1}^{d_0}a_i-\sum_{i=1}^{d1}a_i$，其中 $\sum_{i=1}^{d1}a_i$ 为常数，因此我们只需要最大化 $\sum_{i=1}^{d_0}a_i$。

同样的，我们可以找到 $d_2$，这里简略的写一下
:

$\sum_{i=d_1+1}^{d_2}a_i-\sum_{i=d_2+1}^na_i=(\sum_{i=d_1+1}^{n}a_i-\sum_{i=d_2+1}^{n}a_i)-\sum_{i=d_2+1}^na_i=\sum_{i=d_1+1}^n-2 \times \sum_{i=d2+1}^n$。

同样的 $\sum_{i=d_1+1}^n$ 为常量，我们只需要最小化 $\sum_{i=d2+1}^n$ 即可。

我们记 $P_{d_1}$ 表示 $(\sum_{i=1}^{d_0})_{max}$， $S_{d_1}$ 表示 $(\sum_{i=d2+1}^n)_{min}$，那么对于这个 $d_1$，最后的结果就是 $2 \times P_{d_1}-\sum_{i=1}^{d_1}a_i+\sum_{i=d_1+1}^n a_i-2 \times S_{d_1}$。最后取最大的即可。

## 代码1

下面放上我的代码，大家可以借鉴一下。

```
#include<bits/stdc++.h>
using namespace std;
long long n,a[5005],sum[5005],s[5005],ans=-1e18,p,q,r;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)sum[i]=a[i]+sum[i-1];
    for(int i=n-1;i>=0;i--)s[i]=a[i+1]+s[i+1];
    for(int i=0;i<=n;i++){
	long long maxi=-1e18,mini=1e18,mp=0,mr=0;
	for(int j=0;j<=i;j++){
	    if(sum[j]>maxi){
		maxi=sum[j];
		mp=j;
	    }
	}
	for(int j=n;j>=i;j--){
	    if(s[j]<mini){
		mini=s[j];
		mr=j;
	    }
	}
	if(2*sum[mp]-sum[i]+s[i]-2*s[mr]>ans){
	    ans=2*sum[mp]-sum[i]+s[i]-2*s[mr];
            p=mp,q=i,r=mr;
	}
    }
    cout<<p<<" "<<q<<" "<<r<<endl;
    return 0;
}
```


## 思路2

动态规划。

动态规划可以解决不论分成几段的题，思路是这样的：

$dp(i,j)$ 表示前缀 $a_0,a_1,…,a_i$。$a_i$ 属于第 $j$ 段时的最优值。

那么对于 $a_{i+1}$ 一共可以分以下三种情况：

第一种，将 $a_{i+1}$ 归为第 $j$ 段，那么可以得到 $dp(i+1,j)=max(dp(i,j)+(-1)^j a_{i+1})$。

第二种，将 $a_{i+1}$ 归为第 $j+1$ 段，那么可以得到 $dp(i+1,j+1)=max(dp(i,j)+(-1)^{j+1} a_{i+1})$。

第三种，$j+1$ 段为空，那么我们可以得到 $dp(i,j+1)=max(dp(i,j))$。

大家可以自行思考以下如果要输出方案数怎么办？（提示：定义 $from(i,j)$ 表示从那个状态转移过来。）

## 代码2

此处我本不想放代码，因为那位大神写的不是 C++，此处放上 Java 代码，各位可以欣赏一下。

```java
//package educational.round28;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.InputMismatchException;

public class C {
	InputStream is;
	PrintWriter out;
	String INPUT = "";
	
	void solve()
	{
		int n = ni();
		int[] a = na(n);
		long[] cum = new long[n+1];
		for(int i = 0;i < n;i++)cum[i+1] = cum[i] + a[i];
		long[][] dp = new long[4][n+1];
		for(int i = 0;i < 4;i++){
			Arrays.fill(dp[i], Long.MIN_VALUE / 10);
		}
		dp[0][0] = 0;
		dp[1][0] = 0;
		dp[2][0] = 0;
		dp[3][0] = 0;
		for(int i = 0;i < n;i++){
			dp[0][i+1] = dp[0][i] + a[i];
			dp[1][i+1] = Math.max(dp[0][i+1], dp[1][i] - a[i]);
			dp[2][i+1] = Math.max(dp[1][i+1], dp[2][i] + a[i]);
			dp[3][i+1] = Math.max(dp[2][i+1], dp[3][i] - a[i]);
		}
		int K = 3, cur = n;
		int[] sep = new int[4];
		while(cur > 0){
			while(K > 0 && dp[K-1][cur] == dp[K][cur]){
				sep[K] = cur;
				K--;
			}
			cur--;
		}
		out.println(sep[1]+ " " + sep[2] +" " + sep[3]);
	}
	
	void run() throws Exception
	{
		is = oj ? System.in : new ByteArrayInputStream(INPUT.getBytes());
		out = new PrintWriter(System.out);
		
		long s = System.currentTimeMillis();
		solve();
		out.flush();
		tr(System.currentTimeMillis()-s+"ms");
	}
	
	public static void main(String[] args) throws Exception { new C().run(); }
	
	private byte[] inbuf = new byte[1024];
	public int lenbuf = 0, ptrbuf = 0;
	
	private int readByte()
	{
		if(lenbuf == -1)throw new InputMismatchException();
		if(ptrbuf >= lenbuf){
			ptrbuf = 0;
			try { lenbuf = is.read(inbuf); } catch (IOException e) { throw new InputMismatchException(); }
			if(lenbuf <= 0)return -1;
		}
		return inbuf[ptrbuf++];
	}
	
	private boolean isSpaceChar(int c) { return !(c >= 33 && c <= 126); }
	private int skip() { int b; while((b = readByte()) != -1 && isSpaceChar(b)); return b; }
	
	private double nd() { return Double.parseDouble(ns()); }
	private char nc() { return (char)skip(); }
	
	private String ns()
	{
		int b = skip();
		StringBuilder sb = new StringBuilder();
		while(!(isSpaceChar(b))){ // when nextLine, (isSpaceChar(b) && b != ' ')
			sb.appendCodePoint(b);
			b = readByte();
		}
		return sb.toString();
	}
	
	private char[] ns(int n)
	{
		char[] buf = new char[n];
		int b = skip(), p = 0;
		while(p < n && !(isSpaceChar(b))){
			buf[p++] = (char)b;
			b = readByte();
		}
		return n == p ? buf : Arrays.copyOf(buf, p);
	}
	
	private char[][] nm(int n, int m)
	{
		char[][] map = new char[n][];
		for(int i = 0;i < n;i++)map[i] = ns(m);
		return map;
	}
	
	private int[] na(int n)
	{
		int[] a = new int[n];
		for(int i = 0;i < n;i++)a[i] = ni();
		return a;
	}
	
	private int ni()
	{
		int num = 0, b;
		boolean minus = false;
		while((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'));
		if(b == '-'){
			minus = true;
			b = readByte();
		}
		
		while(true){
			if(b >= '0' && b <= '9'){
				num = num * 10 + (b - '0');
			}else{
				return minus ? -num : num;
			}
			b = readByte();
		}
	}
	
	private long nl()
	{
		long num = 0;
		int b;
		boolean minus = false;
		while((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'));
		if(b == '-'){
			minus = true;
			b = readByte();
		}
		
		while(true){
			if(b >= '0' && b <= '9'){
				num = num * 10 + (b - '0');
			}else{
				return minus ? -num : num;
			}
			b = readByte();
		}
	}
	
	private boolean oj = System.getProperty("ONLINE_JUDGE") != null;
	private void tr(Object... o) { if(!oj)System.out.println(Arrays.deepToString(o)); }
}
```


---

