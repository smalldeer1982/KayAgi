# Baby Ehab Partitions Again

## 题目描述

Baby Ehab was toying around with arrays. He has an array $ a $ of length $ n $ . He defines an array to be good if there's no way to partition it into $ 2 $ subsequences such that the sum of the elements in the first is equal to the sum of the elements in the second. Now he wants to remove the minimum number of elements in $ a $ so that it becomes a good array. Can you help him?

A sequence $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by deleting some (possibly zero or all) elements. A partitioning of an array is a way to divide it into $ 2 $ subsequences such that every element belongs to exactly one subsequence, so you must use all the elements, and you can't share any elements.

## 说明/提示

In the first example, you can partition the array into $ [6,9] $ and $ [3,12] $ , so you must remove at least $ 1 $ element. Removing $ 3 $ is sufficient.

In the second example, the array is already good, so you don't need to remove any elements.

## 样例 #1

### 输入

```
4
6 3 9 12```

### 输出

```
1
2```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
0```

# 题解

## 作者：江户川·萝卜 (赞：15)

容易发现一个结论：数列之和为奇则原数列不是 `good array`。

则先判断一下原数列之和是否为奇。

之后再用背包判断一下原数列是不是 `good array`。

那如果原数列之和是偶呢？那好办，减掉一个奇数就行了！

如果原数列各元素全是偶呢？

容易发现，**对数列同除以一个数不影响结果**。

所以可以对原数列不断除以2，直到出现奇数为止，减掉一个奇数就可以。

具体写代码时，我们可以统计每个数含有2的几次幂，输出最小的那个数的位置即可。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[105];
bool f[200005];
int main(){
	int n,sum=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i];
	if(sum&1){
		puts("0");
		return 0;
	}
	sum/=2;
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=sum;j>=a[i];j--)
			f[j]|=f[j-a[i]];
	if(!f[sum]){
		puts("0");
		return 0;
	}
	int minc=1e5,minp=0;
	for(int i=1;i<=n;i++){
		int x=a[i],cnt=0;
		while(!(x&1)){
			x>>=1;
			cnt++;
		}
		if(cnt<minc) minc=cnt,minp=i;
	}
	printf("1\n%d",minp);
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：11)

[题目链接](https://www.luogu.com.cn/problem/CF1516C)  
[在我的Blog查看](https://blog.csdn.net/Brian_Pan_/article/details/116006051)

### 题目大意

给出一个长度为 $n$ 的序列，问最少需要删除多少个元素，满足剩下的序列不能分为两个元素和相等的集合

-----

首先，我们用背包判断原序列是否已经满足要求

如果不满足，那么我们将证明只需要删去一个元素就可以让原序列满足要求 ：
 
我们先考虑一个较为特殊的情况，也就是存在一个奇数的 $a_i$，那么我们只需要将这个奇数删去，这样剩下的元素和为奇数，就一定满足要求。

如果在这种特殊情况之外，那么就一定存在一个最大的 $k$，满足 $2^k|a_i \space (1\le i \le n)$。为了方便计算，我们将原序列统一除以 $2^k$，并删去一个奇数元素（可证此时一定有奇数）。此时，因为原序列所有数都是 $2^k$ 的倍数，所以一定会有奇数个 $2^k$ 无法被拆分，正如同上面所描述的特殊情况。  
所以，我们只需要一个满足 $\frac{a_i}{2^k} \mod 2=1$ 的数即可

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=110;
const int Maxm=200010;
bool f[Maxm];
int a[Maxn];
int n,m;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	scanf("%d",a+i),m+=a[i];
	f[0]=1;
	for(int i=1;i<=n;++i)
	for(int j=m;j>=a[i];--j)
	f[j]|=f[j-a[i]];
	if((m & 1) || !f[m>>1])
	{puts("0");return 0;}
	int ans=60,pos;
	for(int i=1;i<=n;++i)
	{
		int tmp=0;
		for(int j=30;j>=0;--j)
		if(a[i]%(1<<j)==0){tmp=j;break;}
		if(tmp<ans)ans=tmp,pos=i;
	}
	printf("1\n%d\n",pos);
	return 0;
}
```

---

## 作者：封禁用户 (赞：5)

# 1.前言
[题目链接](http://codeforces.com/contest/1516/problem/C)

题目大意：

$n$ 个数字，分成两个子序列，如果两个序列之和相等，则是不美好的。现在希望去掉若干个数字，要求 $n$ 个数字无法拆成两个集合，这两个集合的和是相等的。
# 2.解析：
假设 $n$ 个数字分成集合 $a[x]$ 和 $b[y]$，并且 $sum(a)=sum(b)$，那么 $sum(a)=sum(n)/2$。

假如 $sum(a)=sum(b)$，那么只要去掉一个集合 $a$ 或者 $b$ 中的最小的数字，那么必然会出现 $sum(a)!=sum(b)$。
 
所以问题就变成，题目中是否存在一个解，使得 $sum(a)==sum(b)$。

如果存在，则去掉 $n$ 个数字中最小的那个；如果不存在，则不需要去掉任何数字；
 
如果要判断 $n$ 个数字中，能不能凑出来 $sum(n)/2$ 的数字，这就直接使用背包求解即可。

warning：
 ```
4 4 6 6 8 8
 去掉4之后
 4 6 6
 8 8
 去掉8之后
 4 4 6
 6 8
 去掉6 之后，因为6/2=3，剩余数字无法凑出数字和为奇数
 
 那如果是
 4 4 4 4 8 呢？（4+4+4=4+8）
```

 
综合上面的考虑，我们发现直接找一个数字最小、最大都无法直接确定。
 
我们回到最初判断，我们会首先认为，如果 $sum(n)$ 是奇数，则无解；那么假如数组中存在一个奇数，我们只要去掉这个奇数即可。

那如果数组中一个奇数都没有呢？

假如数组都是偶数，假设最终分出来的两个集合 $a$ 和 $b$，我们对两边的集合除以 2，不影响 $sum(a)=sum(b)$。

如果还是没有奇数，我们可以继续这样操作。容易知道，这样是一定可以找到一个奇数。

根据上面的思路，我们把每一个数字看成二进制，最右边 1 出现之后，就是奇数了。那么即是寻找 $n$ 个数字中，最右边 1 最早出现的位置。
 
# 3.code
最后在放上 ~~阴阳怪气~~ 的代码~~~
```cpp
typedef long long lld;

class Solution {
    static const int N = 101, M = 101*2000;
public:
    int n, m;
    int a[N], dp[M], ans[N];
    
    int bitpos(int n) {
        int pos = 0;
        while (n % 2 == 0) {
            n /= 2;
            pos++;
        }
        return pos;
    }
    
public:
    void solve() {
        cin >> n;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            sum += a[i];
        }
        
        bool ok = 1;
        if (sum % 2) {
            ok = 0;
        }
        else {
            sum /= 2;
            dp[0] = 1;
            
            for (int i = 0; i < n; ++i) {
                for (int j = sum; j > 0; --j) {
                    if (j >= a[i]) {
                        dp[j] |= dp[j-a[i]];
                    }
                }
            }
            ok = dp[sum];
        }
                
        if (ok) {
            int minIndex = 0, minPos = bitpos(a[0]);
            for (int i = 1; i < n; ++i) {
                if (bitpos(a[i]) < minPos) {
                    minPos = bitpos(a[i]);
                    minIndex = i;
                }
            }
            cout << 1 << " " << minIndex + 1 << endl;
        }
        else {
            cout << 0 << endl;
        }
    }
    
}
ac;

int main(){
    ac.solve();
    return 0;
}
```


---

## 作者：RYANGSJ (赞：2)

# 题目解析

设 $f[i]$ 表示在 $n$ 个数中,能否选出若干个数,使得它们的和为 $j$。

设 $siz[i]$ 表示选出的数和为 $i$ 时,最少需要 $siz[i]$ 个数。

设 $pos[i]$ 表示选出的数和为 $i$ 并且选的数最少时,是从选出的数和为 $pos[i]$ 时转移来的。

设 $add[i]$ 表示选出的数和为 $i$ 并且选的数最少时,选择的最后一个数的编号为 $add[i]$。

我们考虑枚举删掉的数的和 $j$,如果删掉和为 $j$ 的 $siz[j]$ 个数后满足不可以把数组分成两个子序列，这两个子序列的元素之和相等,那么这就是一个合法的方案。

答案就是取最小合法的 $siz[j]$。

统计答案时,记录下 $siz[j]$ 最小时的 $j$。输出时类似于传递闭包

# 代码

```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
using namespace std;
inline int read(){int f=1,res=0;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){res*=10;res+=ch-'0';ch=getchar();}return f*res;}
inline void write(int x){if(x<0){putchar('-');write(-x);}else if(x<=9){putchar(x+'0');}else{write(x/10);putchar((x%10)+'0');}return;}
int n,a[2000005];
PII b[2000005];
bool f[105][200005];
int siz[2000005];
int pos[2000005],add[2000005];
signed main(){
	n=read();
	int sum=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum+=a[i];
	}
	f[0][0]=1;
	memset(siz,0x3f,sizeof(siz));
	siz[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=sum;j++){
			f[i][j]=f[i-1][j];
			if(j>=a[i]){
				if(siz[j]>siz[j-a[i]]+1){
					siz[j]=siz[j-a[i]]+1;
					pos[j]=j-a[i],add[j]=i;
				}
				f[i][j]|=f[i-1][j-a[i]];
			}
		}
	}
	int ans=0x7fffffff,cnt=0;
	for(int i=0;i<=sum;i++){
		if(f[n][i]&&((!f[n][(sum-i)/2])||(sum-i)%2==1)){
			if(siz[i]<ans){
				ans=siz[i],cnt=i;
			}
		}
	}
	write(ans),puts("");
	int tmp=cnt;
	while(tmp!=0){
		write(add[tmp]),putchar(' ');
		tmp=pos[tmp];
	}
	return 0;
}
/*
*/
```


---

## 作者：huayucaiji (赞：2)

~~这个题比 B 简单吧~~

比赛时花了 $23$ 分钟切了。

其实我们可以得出结论，最多去掉一个数。

至于为什么需要在分析的过程中解释。

首先，如果 $n$ 个数的和为奇数一定输出 $0$。这个很好理解。

其次，我们再来考虑是否存在一种划分方式满足一些数之和为 $\frac{sum}{2}$。这个其实很简单，裸的背包。没有这种划分方式输出 $0$，否则要删掉一个数。

我们可能不发通过删除一个数导致无法划分，但是我们可以让 $sum$ 的奇偶性发生改变。

如果此时全都是偶数，就 $\div 2$，直到出现了奇数为止。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=1e5;

int n,sum;
int a[MAXN];
bool f[2][MAXN];

void div() {
	while(1) {
		for(int i=1;i<=n;i++) {
			if(a[i]&1) {
				cout<<1<<endl<<i<<endl;
				return ;
			}
			a[i]>>=1;
		}
	}
}

signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		a[i]=read();
		sum+=a[i];
	}
	if(sum&1) {
		cout<<0<<endl;
		return 0;
	}
	
	int m=sum/2;
	fill(f[0],f[0]+m+1,0);
	f[0][0]=1;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=m;j++) {
			f[i%2][j]=f[(i-1)%2][j];
			if(j>=a[i]) {
				f[i%2][j]=f[i%2][j]|f[(i-1)%2][j-a[i]];
			}
		}
	}
	if(!f[n%2][m]) {
		cout<<0<<endl;
		return 0;
	}
	
	div();
	return 0;
}

```

---

## 作者：PeyNiKge (赞：1)

## 题目大意

定义一个数组是好的当且仅当不能把数组分成两个序列，使这两个序列的元素之和相等。

给定数组 $a$，求将 $a$ 变成好的最少需要删除的元素个数。

## 分析

首先，易证一个数组的和为奇数，该数组一定是好的。

进一步思考，发现如果一个数组是好的，那把数组 $a$ 中每一个数都乘一个数, 处理后的数组 $a$ 也是好的。

对于一个不好的数组，把数组 $a$ 中每一个数都除以数组 $a$ 中所有元素的最大公约数，经过处理后的数组 $a$ 其中一定有一个数是奇数，删除这个数, 可以使得处理后的数组的和为奇数，就可以使原数组是好的了。

判断数组 $a$ 是否是好的，使用 $01$ 背包即可。

具体细节见代码。

```c++
#include<bits/stdc++.h>
#define int long long
#define PII pair<int, int>
#define Kg putchar(' ')
#define Ed puts("")
using namespace std;
const int N = 2e6 + 10, M = 5e3 + 10;
void read(int &ans){ans = 0;int f = 1;char ch = getchar();while(ch < '0' || ch > '9'){if(ch == '-'){f = -1;}ch = getchar();}while(ch >= '0' && ch <= '9'){ans = (ans << 1) + (ans << 3) + (ch ^ 48), ch = getchar();}ans *= f;}
void print(int x){if(x < 0){putchar('-'), print(-x);}else if(x < 10){putchar(x % 10 + '0');}else{print(x / 10);putchar(x % 10 + '0');}}
void file(){freopen(".in", "r", stdin), freopen(".out", "w", stdout);}
int n, a[N], sum;
int dp[N];
int gcd;
signed main(){
	read(n);
	for(int i = 1; i <= n; i++){
		read(a[i]);
		sum += a[i];
		gcd = (i == 1) ? (a[i]) : (__gcd(gcd, a[i]));
	}
	if(sum % 2 == 1){
		print(0);
		return 0;
	}
	sum /= 2;
	dp[0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = sum; j >= a[i]; j--){
			dp[j] |= dp[j - a[i]];
		}
	}
	if(dp[sum] == 0){
		print(0);
		return 0;
	}
	for(int i = 1; i <= n; i++){
		if((a[i] / gcd) % 2 == 1){
			print(1), Ed;
			print(i);
			break;
		}
	}
	return 0;
}
```

---

## 作者：LeavingZzz (赞：1)

## $\mathsf{Solution\space To\space CF1516C}$
### $\mathsf{Description}$
给出一个数组，你需要从其中删去最少的元素使得不存在任何能将数组划分为两个元素和相等的子序列的方案，输出删去的元素。  
### $\mathsf{Analysis}$  
结论：当原数组所有元素都是偶数时，所有元素都除一次 $2$ 得到的新数组和原数组等价。  

证明：因为偶数加偶数等于偶数，所以如果原数组存在一种合法的划分方案，那么划分出来的两个子序列元素和一定都是偶数，所有元素除以 $2$ 之后两个子序列的和仍然相等，不相等的划分方案也一定还是不相等的，所以等价。  

回到本题，如果一开始就不存在合法的划分方案，那么答案就是 $0$ 个。  

否则当前所有元素之和一定是偶数（如果和是奇数是不可能有合法的划分方案的），此时在数组中找到一个奇数删去即可（偶数减奇数等于奇数，元素和为奇数时没有合法划分方案）。  

如果没有奇数，那么就运用上面的结论，所有元素都除以 $2$，继续找奇数，如此进行直到找到奇数为止。  

时间复杂度 $O(n\sum\limits_{i=1}^n a_i+n\log a_i)$  
### $\mathsf{Code}$  
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<ctime>
using std::max;
using std::min;
using std::sort;
using std::swap;
const int maxn=107;
const int maxv=200007;
int A[maxn];
int N;
int f[maxv];
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    scanf("%d",&N);
    int sum=0;
    int lim=200000;
    f[0]=1;
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&A[i]);
        sum+=A[i];
        for(int k=lim;k>=A[i];k--)
            f[k]|=f[k-A[i]];
    }
    if((sum&1)||!f[sum/2])
    {
        printf("%d",0);
        return 0;
    }
    int mn=1000,p=0;
    int tmp;
    while(1)
    {
        for(int i=1;i<=N;i++)
        if(A[i]&1) p=i;
        if(p) break;
        for(int i=1;i<=N;i++) A[i]>>=1;
    }
    printf("1\n%d",p);
    return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 提速偷懒小技巧
使用 bitset 自带的位运算配上 01 背包，真是又快速又省代码长度！
# 思路
首先设 $s=\sum a_i$，若 $s\bmod2=1$，显然最开始就是好的，不用删；否则可以先用 01 背包判断是否存在子序列之和为 $\frac s2$ 的，如果不存在，说明最开始也是好的，也不删。

否则，我们只要设 $g$ 表示每个 $a_i$ 都除得尽的最大的 $2^g$，这时只要删去任意一个 $a_i\bmod2^{g+1}\ne0$ 的数即可使 $s\bmod2^{g+1}\ne0,s\bmod2^g=0$。

本人喜欢使用位运算，如果代码看不懂我会在注释中写等价代码。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, sum, a[105], g = 2048;
bitset <2000005> dp;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)
		cin >> a[i], sum += a[i];
	if (sum & 1) { //奇数
		cout << 0;
		return 0;
	}
	dp[0] = 1;
	for (int i = 0; i < n; ++ i)
		dp |= dp << a[i]; //bitset 自带的位运算，用法详见 OI-wiki
	if (! dp[sum >> 1]) { //没有 sum 的一半
		cout << 0;
		return 0;
	}
	for (int i = 0; i < n; ++ i)
		sum = min (sum, a[i] & -a[i]); //lowbit 算法
	for (int i = 0; i < n; ++ i)
		if (a[i] & sum) { //如果 a[i] / sum % 2 = 1，则 a[i] 的二进制位上一定有 sum 这一位，否则没有
			cout << "1\n" << i + 1;
			return 0;
		}
	cout << -1;
	return 0;
}
```

---

## 作者：yyz_100110 (赞：0)

## [Baby Ehab Partitions Again 题解](https://www.luogu.com.cn/problem/CF1516C)

### 题意：

给定一个 $n$，有 $n$ 个数字，分成两个子序列，若序列和相等，则是不美好的。要求删除一些数字，满足剩下的序列不能分为两个元素和相等的集合。

### 思路：

可以使用[背包](https://baike.so.com/doc/5989126-6202093.html)解决这道题。我们可以用背包去判断原数列是否满足要求。假设我们的序列之和为偶数，我们要想让序列不能再分为两个集合，就必须在序列中减去一个奇数，使序列之和为奇数。如果本来就是奇数，可以直接解决问题。

但是这时若我们的数列都为偶数呢？我们要如何找出奇数呢？数列中的是都为 $2^x$ 幂，那么这个时候我们可以让这个特殊的数组不断除 $2$，知道除出了一个奇数，把他删掉，这样序列之和就能变化为奇数了，最后在输出 $x$ 最小的那个数的下标即可。

### Accode：
```cpp
#include<cstdio>

using namespace std;

int a[1001],n,sum=0;
bool f[200008];

signed main(void){
    scanf("%d",&n);
	for(int i=1;i<=n;i++){
	    scanf("%d",&a[i]);
	    sum+=a[i];//求序列和
	}
	if(sum%2) return puts("0"),0;
	f[0]=true;
	for(int i=1;i<=n;i++)
	    for(int j=sum/2;j>=a[i];j--)
	        f[j]|=f[j-a[i]];//背包
	if(f[sum/2]){
		int mini=1e9,ans;
    	for(int i=1;i<=n;i++){
    		int x=a[i],summ=-114514;
    		while(!(x%2))//不断除2去找奇数
    		    x/=2,summ++;
    		if(summ<mini){//找出那个最小得数
    		    mini=summ;
             ans=i;
         }
    	}
    	printf("1\n%d",ans);
	}else printf("0\n");
}
```

谢谢观看！

---

## 作者：plank_black (赞：0)

## 题目大意

&emsp;&emsp;在一个数组中去掉一些数字，使得最后剩下的数无论怎么分成两组都无法试两组数和相同，求出最小删除数字的个数。

## 思路

&emsp;&emsp;首先考虑本身就无法分成和相同的两组的情况，一种情况是整个数组的和是奇数，其二是数组无法选出一些数和为 $\frac{sum}{2}$。后者用一个背包判断就行。

&emsp;&emsp;剩下的情况就是有解的情况，我们考虑怎么才能使得所删除的数字最小。

&emsp;&emsp;因为如果整个数组和为奇数就无解，我们容易想到删除一个奇数，这样就使得整个数组的和为奇数了。但是如果数组中没有奇数怎么办呢？我们可以注意到以下一个性质：

- 在这个题目中，数组 $A$ 与将数组 $A$ 中每一个元素除以 $2$ 所得数组等效。

&emsp;&emsp;证明很简单就省略了。有了以上结论，我们就可以每次把数组每个元素除以 $2$，再判断是否有奇数，如果有就随便输出一个就行了。

## 代码
```cpp
#include<iostream>
using namespace std;

const int N = 110, M = 200010;
int n;
int A[N];
bool f[M];

int main( ) {
	cin >> n;
	
	int sum = 0;
	f[0] = true;
	for(int i = 1; i <= n; i++) {
		cin >> A[i];
		sum += A[i];
		for(int j = 200000; j >= A[i]; j--)
			f[j] |= f[j - A[i]];
	}
	
	if(sum % 2 || !f[sum / 2]) {
		cout << '0' << endl;
		return 0;
	}
	
	int pt = 0;
	bool flag = true;
	while(flag) {
		for(int i = 1; i <= n; i++)
			if(A[i] % 2) {
				flag = false;
				pt = i;
			}
		for(int i = 1; i <= n; i++) A[i] /= 2;
	}
	
	cout << "1" << endl;
	cout << pt << endl;
	return 0;
}
```


---

