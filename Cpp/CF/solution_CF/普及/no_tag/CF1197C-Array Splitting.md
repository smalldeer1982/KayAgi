# Array Splitting

## 题目描述

You are given a sorted array $ a_1, a_2, \dots, a_n $ (for each index $ i > 1 $ condition $ a_i \ge a_{i-1} $ holds) and an integer $ k $ .

You are asked to divide this array into $ k $ non-empty consecutive subarrays. Every element in the array should be included in exactly one subarray.

Let $ max(i) $ be equal to the maximum in the $ i $ -th subarray, and $ min(i) $ be equal to the minimum in the $ i $ -th subarray. The cost of division is equal to $ \sum\limits_{i=1}^{k} (max(i) - min(i)) $ . For example, if $ a = [2, 4, 5, 5, 8, 11, 19] $ and we divide it into $ 3 $ subarrays in the following way: $ [2, 4], [5, 5], [8, 11, 19] $ , then the cost of division is equal to $ (4 - 2) + (5 - 5) + (19 - 8) = 13 $ .

Calculate the minimum cost you can obtain by dividing the array $ a $ into $ k $ non-empty consecutive subarrays.

## 说明/提示

In the first test we can divide array $ a $ in the following way: $ [4, 8, 15, 16], [23], [42] $ .

## 样例 #1

### 输入

```
6 3
4 8 15 16 23 42
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4 4
1 3 3 7
```

### 输出

```
0
```

## 样例 #3

### 输入

```
8 1
1 1 2 3 5 8 13 21
```

### 输出

```
20
```

# 题解

## 作者：徐敬 (赞：9)

# 思路：
将一个数列分成k段，必会有k-1个切点。拿样例为例，分成3段则应有：

[1,a[i]] [a[i+1],a[j]] [a[j+1],n]三段

#### 所求值即为：(a[n]-a[j+1])+(a[j]-a[i+1])+(a[i]-a[1])
#### 整理可得：=a[n]-a[1]-(a[j+1]-a[j])-(a[i+1]-a[i])
### 即数列中的最大数（a[n]）与最小数（a[1]）的差减去k-1个连续两数之差

因为要求最小值，那么应选取从第1大到k-1大的数差


------------
# 代码实现：

当时本蒟蒻的真实想法是，把所有的数存起来，然后sort，因为
## ~~暴力nb！！~~

但由于本题数据较大，全存显然会爆and暴力sort显然会tle，那么我们就在输入的时候直接处理数据，再加个奇妙的堆优化就好了：
### 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
bool cmp(int x,int y){
	return x>y;
}
int a[300001];
priority_queue<int> q;
int main(){
	int n,k,summ=0;
	int t1,t2,minx,maxx,linee=100000001,count=0,cha;
	scanf("%d%d",&n,&k);
	k--;
	scanf("%d",&t1);
	minx=t1;
	for(register int i=2;i<=n;i++){ 
		scanf("%d",&t2);
		cha=t2-t1;
		if(count<k){		 //输入时判断能否进堆
			count++;
			q.push(-cha);	//因为是大根堆所以取相反数进堆
			linee=min(linee,cha);
		}
		else if(cha>linee) {
				q.pop();
				q.push(-cha);
				linee=-q.top();
			}
		t1=t2;
	}
	maxx=t1;
	summ=maxx-minx;
	int ans=0;
	for(register int i=1;i<=k;i++){ 	//从堆顶一一输出
		ans-=q.top();
		q.pop();
	}
	printf("%d",summ-ans);
	return 0;
}
```



---

## 作者：Waddles (赞：5)

这题其实想通了就很简单啦

考虑一刀不切，和就为所有数的和

现在要求和最小，能切k刀

肯定切最大的k刀划算啊

（在两个数之间切一刀只会在总和里减少他们两数之间的差）

代码实现加总和减大往小k个差或者小往大加n-k个~~随便乱搞~~都行

这个题真的只是考思维qwq

code:

```
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
template<class Read>void in(Read &x){
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
int n,k,ans,a[500005],s[500005];
int main(){
	in(n);in(k);
	for(int i=1;i<=n;i++)in(a[i]);
	for(int i=2;i<=n;i++)s[i-1]=a[i]-a[i-1];//统计两数差
	sort(s+1,s+n);
	for(int i=1;i<=n-k;i++)ans+=s[i];//加一下就好啦
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Eismcs (赞：4)

明显的思维题，代码很短，但需要思维迅速的转换

可以以前缀和思想来看，每个区间最大值减最小值，不就是此区间相邻元素差的和吗？（区间为升序）

而分为$k$个区间，也就是减去$k-1$个相邻元素差呀！

所以此题成了贪心
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
#define int long long
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int a[300005],f[300005],ss;
signed main(){
    int n=read(),k=read();
    if(k==n){cout<<0<<endl;return 0;}
    for(int i=1;i<=n;i++){
    	a[i]=read();
    	if(i>1){f[i-1]=a[i]-a[i-1];ss+=f[i-1];}
      //记录相邻两数差，ss记录总之（即整个区间最大值减最小值）
    }
    sort(f+1,f+n);//贪心，排序
    for(int i=n-1;i>=n-k+1;i--){
    	ss-=f[i];//减去大的差，让答案最小
    }
    cout<<ss<<endl;
    return 0;
}
```


---

## 作者：Burnside (赞：3)

# 我也不知道为什么就是非常喜欢这个题

先说说思路叭，考虑这个序列是有序的，又因为要求分成$~k~$段后用最大值减最小值。设断点是$~p~$和$~p+1~$之间的这个位置，因为要分成$~k~$段，所以一共有$~k-1~$个断点，假设有一个序列$~a~$如下：

$$\{~a_1~,~a_2~,~\dots,~~a_n~\}$$

现在设置$~k-1~$个断点，分别为$~p_1~,~p_2~,~\dots~,~p_{k-1}~$，使之变成：

$$\{~a_1~,~\dots~,a_{p_1}~\}~\{~a_{p_1+1}~,~\dots~,a_{p_2}~\}\dots\{~a_{p_{k-1}+1}~,~\dots~,a_n~\}$$

因为保证了序列$~a~$是单调递增的，所以这个时候的$~cost=a_{p_1}-a_1+a_{p_2}-a_{p_1+1}+\dots+a_n-a_{p_{k-1}+1}~$。我们发现，这个式子的第一位，也就是$~a_1~$一定是负的，最后一位$~a_n~$一定是正的，断点的左右两边，即$~a_{p_i}~$和$~a_{p_i+1}~$一定是一正一负，所以化简一下这个$~cost~$，就变成了：

$$~cost=a_n-a_1+a_{p_1}-a_{p_1+1}+a_{p_2}-a_{p_2+1}+\dots+a_{p_{k-1}}-a_{p_{k-1}+1}$$

$$cost=a_n-a_1+\sum_{i=1}^{k-1}a_{p_i}-a_{p_i+1}$$

由于$~a_{p_i}~$和$~a_{p_i+1}~$是恰好相邻的两个元素，又因为我们要让$~cost~$最小，也就是要最小化$~\sum_{i=1}^{k-1}a_{p_i}-a_{p_i+1}~$，所以只需要求一个差分数组$~d[i]=a[i]-a[i+1]~$，并取出$~d[i]~$的最小的$~k-1~$个元素之和就可以了，设$~d[i]~$的最小$~k-1~$个元素之和是$~sum_d~$，那么最终$~cost_{min}=a_n-a_1+sum_d~$即为所求，具体实现见下方代码。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cmath>
template<typename _sp>
inline void qread(_sp &_x){
    char _ch=getchar(),_lst=' ';
    while(_ch<'0'||_ch>'9') _lst=_ch,_ch=getchar();
    while(_ch>='0'&&_ch<='9') _x=(_x<<3)+(_x<<1)+(_ch^48),_ch=getchar();
    if(_lst=='-') _x=-_x;
}
int n,k;
int a[300005];
int d[300005];
int ans;
int main(){
	qread(n);qread(k);
	for(register int i=1;i<=n;i++){
		qread(a[i]);
		if(i!=1) d[i-1]=a[i-1]-a[i];//d[i-1]=a[i-1]-a[i]相当于d[i]=a[i]-a[i+1]。
	}
	std::sort(d+1,d+n);//d[i]中只有n-1个元素，取最小的k-1个元素
	for(register int i=1;i<k;i++) ans+=d[i];//取前k-1位
	printf("%d\n",ans+a[n]-a[1]);//最后加上a[n]减去a[1]就是最终结果
	return 0;
}
```

完结撒花！

---

## 作者：Believe_R_ (赞：2)

第一眼看到这道题目：CF比赛Ct题，我就觉得这题不简单，肯定既考思维又考代码实现能力，第二眼看过去，这是一到**蓝题**【提高+ / 省选-】，就决定一晚上专攻这题！But......

### 千万不能相信洛谷的标签 QwQ ！！！



好了，回归正题。看到这道题目，洛谷已经将中文的一句话题意告诉我们了： **给出一个长度为 $n$ 的严格单调增的序列，将其分成 $k$ 段，使得每一段的极差的和最小，求这个最小的和。（每段长度至少为1，当长度为1时，其极差为0）**。

乍一看这题，我确实一点思路都没有~~（大佬们别喷我）~~，但是只要一分析样例，稍加一思考，这题的算法就显而易见了（我们以第一个样例为例）：

```cpp
样例输入：
6 3
4 8 15 16 23 42
样例输出：
12
```

题目中已经说明，做法是将这个样例砍成 3 段，分别是 $[4,8,15,16][23][32]$ 。

我们设样例中给我们的几个数字分别是 $a[1],a[2]\ldots a[n] \ (n\le 300000)$ ，一共要分成 $3$ 段。那么这三段就分别是：$a[1]\ldots a[i] , a[i+1]\ldots a[j] , a[j+1]\ldots a[n]$ 。
因为题目中为我们的序列是严格单调递增的，那么对于给序列中的任何一个子序列，最后一个元素肯定是最大的，第一个元素肯定是最小的。
根据这一点，那么这三段子序列的极差和 $Sum_{min}$ 即为：$a[i]-a[1]+a[j]-a[i+1]+a[n]-a[j+1]$ 。化简一下，即可得到 $Sum_{min} = (a[n]-a[1])-(a[i+1]-a[i])-(a[j+1]-a[j])$ 
因为 $a[n]-a[1]$ 的值是固定的，所以要使 $Sum_{min}$ 最小，就要使 $a[i+1]-a[i]，a[j+1]-a[j]$ 最大。



从以上样例分析中，我们可以将结论推到所有情况当中去了：

### $Sum_{min}=(a[n]-a[1])-$ 前 $k$ 大的相邻两数差

而至于前 $k$ 大的相邻两数差怎么求，我们就可以再读入的时候将其存起来，之后 $sort$ 一遍就可以了（ $n$ 最大也才300000，$sort$ 的复杂度是 $n \log n$，并不会超时）！

#### 下面附上c++代码（sort版）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,sum=0;
int a[500000],cha[500000];
int cmp(int x,int y)
{
    return x>y;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        if(i>=2) cha[i-1]=a[i]-a[i-1];
    }
    //for(int i=1;i<n;++i) printf("%d\n",cha[i]);
    sum=a[n]-a[1];
    sort(cha+1,cha+n,cmp);                          //从大到小排序
    //for(int i=1;i<n;++i) printf("%d\n",cha[i]);
    for(int i=1;i<=k-1;++i) sum-=cha[i];
    printf("%d\n",sum);
    return 0;
}
```



#### 堆排版：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int M=500000;
int a[M];
int n,m,k,ans=0,sum=0;
priority_queue<int> q;				//定义一个大根堆
inline int read()					//快读不说了
{
    int re=0, f=1; char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {re=re*10+(ch-'0'); ch=getchar();}
    return re*f;
}
int main()
{
    n=read(); k=read();
    for(int i=1;i<=n;++i)
    {
        a[i]=read();
        if(i>=2)
        {
            int x=a[i]-a[i-1];
            //printf("%d\n",x);
            q.push(x);				//将相邻两数差直接丢到堆里面去
        }
    }
    sum=a[n]-a[1];
    for(int i=1;i<k;++i)
    {
        int x=q.top();
        q.pop();
        sum-=x;
    }
    printf("%d\n",sum);
    return 0;
}
```



---

## 作者：_bql (赞：2)

### 算法

贪心

### 思路

首先看题面 其实很像DP的经典题 但数组都是排好序的 所以其实贪心就可以解决

先处理出所有相邻两数之差 然后降序排序 取差值最大的k-1个 就在这k-1处分割 然后统计答案就行了

### Code主要部分

重要部分有注释

```cpp
#include<bits/stdc++.h>
#define maxn 300005
using namespace std;

int n,k,a[maxn],ans=0,b[maxn],mini=1;
struct node
{
 	int num,o;
}c[maxn];
bool cmp(node x,node y)
{
	return x.num>y.num;
}

int main()
{
	cin>>n>>k;
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		c[i].num=a[i]-a[i-1];//计算差值
		c[i].o=i-1;//处理编号 方便后面统计
	}
	if(n==k) 
	{
		cout<<0;
		exit(0);
	}//特判（不加也可以）
	if (k==1)
	{
		cout<<a[n]-a[1];
		return 0;
	}//同上
	sort(c+2,c+2+n,cmp);
	for (int i=2;i<=k;++i) b[c[i].o]=1;//在需要分割的地方打标记
	for (int i=1;i<=n;++i)
		if (b[i])
		{
			ans+=a[i]-a[mini];//统计
			mini=i+1;
		}
	if (!b[n]) ans+=a[n]-a[mini];//细节 最后一段的结果要加上
	cout<<ans;
	return 0;
}
```

---

## 作者：woshishei (赞：1)

## 思路：差分+贪心

### 浓缩版

维护一个差分数组，只选最小的$n-k$个数相加即为答案。

### 详细版

这道题需要计算$\sum^{k}_{i=1}(max(i)-min(i))$，而差分能直接给出相邻两个数之间的差，所以很容易想到差分。

记$b_i=a_{i+1}-a_i$，所以对于第$i$个区间$[l,r]$，很容易看出$max(i)-min(i)=a_r-a_l=\sum^{r-1}_{j=l}b_j$。

而对于第$i$个区间的最大值$a_j$和第$i+1$个区间的最小值$a_{j+1}$来说，不用考虑$b_j$的值，也就是$a_{j+1}$与$a_j$的差。

所以在差分数组$b_1,b_2,...,b_{n-1}$中一共不用考虑$k-1$个值。也就是只需要考虑$n-k$个值。

最后的答案就是$b$中最小的$n-k$个值之和。

时间复杂度$O(nlog_2n)$

### 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
int n,k,a[300010],b[300010];
ll sum=0;
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i-1]=a[i]-a[i-1];//差分
	}
	sort(b+1,b+n);//对n-1个值排序
	for(int i=1;i<=n-k;i++)
		sum+=(ll)b[i];//只取最小的n-k个值
	printf("%I64d",sum);
	return 0;
}
```

---

## 作者：yizr_cnyali (赞：0)

由于题目要求将序列分成$k$段后每一段的极差的和最小,我们可以用前缀和的思想来考虑:一个区间的极差就是其中相邻元素的差之和。 

分成$k$个区间后,切断的位置很明显就不是相邻元素了，这$k - 1$个相邻元素的差自然就要从答案中去除。由于要求极差和最小，我们应该选取最大的$k - 1$个相邻元素差

综上，将原数组处理成前缀和数组后进行快速排序，排序后将极差和减去最大的$k - 1$个相邻元素差即可

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
 
using namespace std;
 
template <typename T> inline int Chkmax (T &a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline int Chkmin (T &a, T b) { return a > b ? a = b, 1 : 0; }
 
template <typename T> inline T read(){
    T sum = 0;
    int fl = 1,ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') fl = -1;
    for(; isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + ch - '0';
    return sum * fl;
}
 
const int maxn = 300000 + 5;
 
int n,k,sum;
int a[maxn];
 
int main(){
	n = read<int>();
	k = read<int>();
	for(int i = 1; i <= n; i++){
		a[i] = read<int>();	
	}
	for(int i = n; i >= 2; i--){
		a[i] -= a[i - 1];
		sum += a[i];
	}
	sort(a + 2,a + n + 1,greater<int>());
	for(int i = 2; i <= k; i++) sum -= a[i];
	printf("%d\n",sum);
	return 0;
}
```


---

## 作者：Heartlessly (赞：0)

## Description

给出一个长度为 $n$ 的单调不下降序列 $\{ a \}$，现要将其分成 $k$ 段，使得每一段的极差的和最小，求这个最小的和（每段长度至少为 $1$，当长度为 $1$ 时，其极差为 $0$）。

$(1 \leq k \leq n \leq 3 \times 10^5,1 \leq a_i \leq 10^9, \forall a_i \geq a_{i - 1})$

## Solution

直接求似乎很难？考虑转化问题。

我们不妨把分成 $k$ 段看作断开 $k - 1$ 处，假设我们断在了第 $i$ 个数和第 $i + 1$ 个数中间，那么第 $i$ 个数贡献为正，第 $i + 1$ 个数贡献为负，贡献和为 $a_i - a_{i + 1}$ 。

显然我们让断开的地方贡献和最小时最优，因此我们可以预处理出 $f_i = a_i - a_{i + 1}$，然后将 $f$ 数组从小到大排序，选前 $k - 1$ 个的和即可。第 $1$ 个数的贡献为负，第 $n$ 个数的贡献为正，这里没有算进去，所以最后应当加上 $a_n - a_1$ 。时间复杂度为排序的复杂度 $O(n \log n)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
 
template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}
 
template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}
 
const int MAXN = 3e5;
int n, k, a[MAXN + 5], f[MAXN + 5];
LL ans;
 
int main() {
    read(n), read(k);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        f[i - 1] = a[i - 1] - a[i];//转化为相邻两数之差 
    }
    sort(f + 1, f + n + 1);//从小到大排序 
    ans = a[n] - a[1];
    for (int i = 1; i < k; ++i) ans += f[i];//取前 k - 1 个 
    write(ans);
    putchar('\n');
    return 0;
}
```



---

## 作者：AC_Automation (赞：0)

感觉这题没有蓝题难度吧，CF的题恶评太严重了。

言归正传，我们考虑先分成$n$段，然后合并成$k$段。

每次计算合并后造成的影响，合并影响最小的。

以样例1为例：
```
6 3
4 8 15 16 23 42

```
计算两数之间的差值为：4，7，1，7，19

我们分别将差值为1，4，7的两个数合并，合并后原序列变成4~8，15~23，42（或者4~16，23，42），统计后得到答案为12。

考虑如何方便计算。

我们可以先计算$a[n]-a[1]$的差值，在减去没有被合并的差值。这里可以用堆来找出前$n$小的差值贪心地来合并（当然排序也行了）

时间复杂度$O(n\ log\ n)$

最后放代码：
```cpp
#include<iostream>
#include<queue>
#include<algorithm> 
#include<functional>
using namespace std;
int a[300005];
priority_queue<int,vector<int>,greater<int> > pq;
int main(){
	int n,sum,k;
	cin>>n>>k;sum=n;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<n-1;i++){
		pq.push(a[i+1]-a[i]);//计算差值
	}
	while(sum>k){
		pq.pop();
		sum--;//找到前k小差值
	}
	int ans=a[n-1]-a[0];
	while(!pq.empty()){
		ans-=pq.top();//计算答案
		pq.pop();
	}
	cout<<ans;
	return 0;
}
```

---

