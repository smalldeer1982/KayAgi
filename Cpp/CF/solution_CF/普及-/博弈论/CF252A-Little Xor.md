# Little Xor

## 题目描述

Little Petya likes arrays that consist of non-negative integers a lot. Recently his mom has presented him one such array consisting of $ n $ elements. Petya immediately decided to find there a segment of consecutive elements, such that the $ xor $ of all numbers from this segment was maximal possible. Help him with that.

The $ xor $ operation is the bitwise exclusive "OR", that is denoted as "xor" in Pascal and "^" in C/C++/Java.

## 说明/提示

In the first sample one of the optimal segments is the segment that consists of the first and the second array elements, if we consider the array elements indexed starting from one.

The second sample contains only one optimal segment, which contains exactly one array element (element with index three).

## 样例 #1

### 输入

```
5
1 2 1 1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 2 7
```

### 输出

```
7
```

## 样例 #3

### 输入

```
4
4 2 4 8
```

### 输出

```
14
```

# 题解

## 作者：雨季 (赞：10)

# 题解
由于异或具有前缀和性质，即 $a[l]$ ^ $a[l+1]$ ^ $a[l+2]...$ ^ $a[r]=a[r]$ ^ $a[l-1]$   
所以记下前缀和，暴力枚举所有的区间即可，复杂度 $O(n^2)$

# 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int n;
int a[105],b[105];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),b[i]=(b[i-1]^a[i]);
	int ans=0;
	for(int i=1;i<=n;++i) {
		for(int j=i;j<=n;++j) {
			ans=max(ans,b[j]^b[i-1]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：luckydrawbox (赞：7)

## solution 1

此解法复杂度为 $O(n^3)$。

由于数据很小，所以我们暴力枚举左右端点，暴力计算前缀和即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int n,a[N],mx,sum;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			sum=a[i];
			for(int k=i+1;k<=j;k++)
				sum^=a[k];
			mx=max(mx,sum);
		}
	}
	cout<<mx<<endl;
	return 0;
}
```

如果 $n$ 的范围扩大到 $1000$ 呢？

## solution 2

此解法复杂度为 $O(n^2)$。

我们设这个序列为 $a_1,a_2,…,a_n$，$s_i=a_1\ xor\ a_2\ xor\ …\ xor \ a_i=s_{i-1}\ xor\ a_i$，其中 $s_0=0$。

此时，
$a_i\ xor\ a_{i+1}\ xor\ …\ xor \ a_j$

$=0\ xor\ (a_i\ xor\ a_{i+1}\ xor\ …\ xor \ a_j)$

$=(a_1\ xor\ a_2\ xor\ …\ xor \ a_{i-1})\ xor\ (a_1\ xor\ a_2\ xor\ …\ xor \ a_{i-1})\ xor\ (a_i\ xor\ a_{i+1}\ xor\ …\ xor \ a_j)$

$=(a_1\ xor\ a_2\ xor\ …\ xor \ a_{i-1})\ xor\ (a_1\ xor\ a_2\ xor\ …\ xor \ a_{i-1}\ xor\ a_i\ xor\ a_{i+1}\ xor\ …\ xor \ a_j)$

$=s_{i-1}\ xor\ s_j$

这就是**异或前缀和**。

这样我们只要暴力枚举 $i,j$，就只有 $O(n^2)$ 的时间复杂度。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int n,a,s[N],mx; 
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a;
    	s[i]=s[i-1]^a;
	}
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			mx=max(mx,s[j]^s[i-1]);
	cout<<mx<<endl;
	return 0;
}
```

如果 $n$ 继续扩大到 $10^4,10^5,10^6$ 呢？

## solution 3

此解法复杂度为 $O(n)$。

考虑改进 solution 2。

在求出了异或前缀和的前提下，我们的问题变成了：

>在给定的 $n+1$ 个整数 $s_0,s_1,s_2,…,s_n$ 中选出两个进行 $xor$（异或）运算，得到的结果最大是多少？

我们考虑所有的二元组 $(i,j)$ 且 $i<j$，那么本题的目标就是在其中找到 $s_i\ xor\ s_j$ 的最大值。也就是说，对于每个 $i(0\le i\le n)$，我们希望找到一个 $j(0\le j<i)$，使 $s_i\ xor\ s_j$ 最大，并求出这个最大值。

我们可以把每个整数看作长度为 $30$ 的二进制 $01$ 串（数值较小时在前面补 $0$），并且把 $s_0～s_{i-1}$ 对应的 $30$ 位二进制串插入一棵 $\text{Trie}$ 树（其中最低二进制位为叶子节点）。

接下来。对于 $s_i$ 对应的 $30$ 位二进制串，我们在 $\text{Trie}$ 中进行一次与检索类似的过程，每一步都尝试沿着“与 $s_i$ 的当前位相反的字符指针”向下访问。若“与 $s_i$ 的当前位相反的字符指针”指问空节点，则只好访问与 $s_i$ 当前位相同的字符指针。根据 $xor$ 运算“相同得 $0$，不同得 $1$”的性质，该方法即可找出与 $s_i$ 做 $xor$ 运算结果最大的 $s_j$。

如下页图所示，在一棵插入了 $2(010),5(101),7(111)$ 三个数的 $\text{Trie}$ 中，分别查询与 $6(110),3(011)$做 $xor$ 运算结果最大的数。（为了简便，图中使用了 $3$ 位二进制数代替 $30$ 位二进制数。）

![](https://cdn.luogu.com.cn/upload/image_hosting/5h8u19q5.png)

综上所述，我们可以循环 $i=1～n$，对于每个 $i$，$\text{Trie}$ 树中应该存储了 $s_0～s_{i-1}$ 对应的 $30$ 位二进制串（实际上每次 $i$ 增长前，把 $s_i$ 插入 $\text{Trie}$ 即可)。根据我们刚才提到的“尽量走相反的字符指针”的检索策略，就可以找到所求的 $s_j$，更新答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int n,a,s[N],trie[N*32][2],tot=1,mx;
void Trie_insert(int x)//插入 
{
	int p=1;
	for(int k=30;k>=0;k--)
	{
		int ch=(x>>k)&1;
		if(trie[p][ch]==0)
			trie[p][ch]=++tot;
		p=trie[p][ch];
	}
}
int Trie_search(int x)//搜索 
{
	int p=1,ans=0;
	for(int k=30;k>=0;k--)
	{
		int ch=(x>>k)&1;
		if(trie[p][!ch])//相反的位 
			p=trie[p][!ch],ans+=1<<k;
        else
			p=trie[p][ch];
	}
	return ans;
}
int main()
{
    cin>>n;
    Trie_insert(s[0]);//s[0]也要插入 
    for(int i=1;i<=n;i++)
    {
    	cin>>a;
    	s[i]=s[i-1]^a;
    	Trie_insert(s[i]);
    	mx=max(mx,Trie_search(s[i]));
	}
	cout<<mx<<endl;
	return 0;
}
```


---

## 作者：zjyqwq (赞：6)

### CF252A Little Xor 题解
c++题解。

------------
#### 解题思路

这题让我想起了一题。

——[最大子段和](https://www.luogu.com.cn/problem/P1115)。推荐做一做。

而这题就是最大异或和，最大子段和的升级版。

我们可以先创建一个“前异或和”数组。 $s[i]$ 就是从 $a[1$ ~ $i]$ 的异或总值。

然后我们可以用 $O(n*n)$ 的时间复杂度的方法来解决。

我们使用两个循环，枚举子序列个起点和终点。

最后，我们只要用（“前异或和”数组 的 终点） 异或（ “前异或和”数组 的 起点减一 ）即可。

------------
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
inline int mmax(R int x,R int y){return x>y?x:y;}
inline int mmin(R int x,R int y){return x<y?x:y;}
void swap(R int &x,R int &y){R int t=x;x=y;y=t;}inline void read(R int &y){
   R int s=0,w=1;
   R char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   y=s*w;
}
inline void write(R int x){
    if(x < 0){
        putchar('-');
        write(-x);
        return;
    }
    if(x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}//快读快输，不管他
 int main(){
 	int a[105]={0},s[105]={0},n,ans=0;//局部变量，赋初值。
 	read(n);
 	for(R int i=1;i<=n;++i)
	 read(a[i]);//输入数组
 	for(R int i=1;i<=n;++i)
 	 s[i]=a[i]^s[i-1];//创建前异或和数组。
 	for(R int i=1;i<=n;++i)
 	for(R int j=i;j<=n;++j){
 		ans=mmax(ans,s[j]^s[i-1]);
	 }//使用手打max，因为STL库太慢了。
	write(ans);//输出。
    return 0;
}
```
------------
结束了！！！

---

## 作者：SIXIANG32 (赞：2)

第100道橙题，故此纪念qwq。  
闲话少说，切入正题。


------------
这题是个裸的前缀和。（可是我因为把左右指针写反了 WA 了好几次/kk wtcl）。  

相信大家都知道前缀和是个什么东东（$qz_i=qz_{i-1}+x$），那么异或前缀和是什么呢？和这个前缀和差不多，就是 $qz_i=qz_{i-1}\bigoplus x$。  
然后我们暴力枚举左右端点，计算异或和就可以惹。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int qzh[100100],maxn=-1;
int main()
{
	int n;
	cin>>n;
	for(int p=1,x;p<=n;p++)
		cin>>x,qzh[p]=((p==1)?(x):(qzh[p-1]^x));//预处理异或前缀和，特判当p=1时，qzh[1]=x
	for(int p=1;p<=n;p++)//暴力枚举左端点
		for(int i=p;i<=n;i++)//暴力枚举右端点
			maxn=max(maxn,qzh[p-1]^qzh[i]);//计算异或和，注意不能写反左右端点（就像我这样/kk wtcl）
	cout<<maxn<<endl;//完美输出
}
```
众所周知，前缀和预处理的时间复杂度为 $O(n)$，异或前缀和当然如此（废话），暴力枚举左右端点时间复杂度为 $O(n^2)$，时间复杂度为 $O(n+n^2)$，如果是暴力就是 $O(n^3)$，显然效率大大提升了。 

对于$n \le 100$的~~弱~~数据来说可以完美通过。  

---

## 作者：chufuzhe (赞：1)

这题数据范围很小，可以用暴力，时间复杂度$O(n^3)$。

先枚举前后两个端点，再计算子段的异或和，最后取出最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int main(){
	int n,ans=0; //ans表示最大的异或和
	cin>>n; //输入
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){ //i表示前面的端点
		for(int j=i;j<=n;j++){ //j表示后面的端点
			int s=a[i]; //s表示i-j子段的异或和
			for(int k=i+1;k<=j;k++){ //计算异或和									s^=a[k];
			}
			ans=max(ans,s); //取最大值
		}
	}
	cout<<ans<<endl; //输出
	return 0;
}

```

那如果$n$扩大到5000呢？

$O(n^3)$显然过不了，我们可以用前缀和优化，每次计算异或和的时间复杂度就变成了$O(1)$，整体的时间复杂度就是$O(n^2)$。

$l$到$r$的异或和就是1-($l$-1)的异或和异或1-$r$的异或和。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],f[105];
int main(){
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		f[i]=f[i-1]^a[i]; //前缀和优化
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			int s=f[j]^f[i-1]; //i-j子段的异或和
			ans=max(ans,s);
		}
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：伟大的王夫子 (赞：1)

先安利一下[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)

反正$n$只有$100$，不如来个$O(n^3)$

暴力枚举所有区间$l,r$，暴力算异或和

$a_l$ ^ $a_{l+1}$ $\cdots$ ^ $a_r$即可

$code$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[101], ans;
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) cin >> a[i];
	for (register int i = 1; i <= n; ++i)  {//暴力枚举每个区间
		for (register int j = i; j <= n; ++j) {
			int val = 0;
			for (register int k = i; k <= j; ++k) {//暴力算这段区间的xor和
				val ^= a[k];
			}
			ans = max(ans, val);//更新答案
		}
	}

	cout << ans;
}
```

万一$n$有$10^3$呢?
~~开O2~~

就要在上一次算的的异或和上，直接异或这个数，便可得到新的异或和

设$val = a_l$ ^ $a_{l+1}\cdots$ ^ $a_{r - 1}$为上一次的答案，那么更新数据只需算出$a_l$ ^ $a_{l+1}$ $\cdots$ ^ $a_r$，只用把$val$异或$a_r$即可



$O(n^2)$

$code$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[101], ans;
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) cin >> a[i];
	for (register int i = 1; i <= n; ++i)  {//暴力枚举每个区间
		int val = 0;
		for (register int j = i; j <= n; ++j) {
			val ^= a[j];
			ans = max(ans, val);
		}
	}

	cout << ans;
}
```



---

## 作者：szkzyc (赞：0)



这道题的题目意思为给出一个正整数序列，将这些数求异或和后求出最大的连续子段和。

看到这道题我们就很容易联想到一个东西——前缀和。

因为这道题要求出最大的连续子段和，所以与普通前缀和很是类似的。

已知普通前缀和的递推公式为 

$S_i=S_{i-1}+A_i$

所以我们异或和版本的前缀和就对应为 

$xorS_i=xorS_{i-1}⊕A_i$  

所以再与普通前缀和一样的方法枚举和的前后端点就行了。

### AC代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 105;
int xor_a[N], a[N], n, maxn = -1;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) {
    	cin >> a[i];  
    	xor_a[i] = xor_a[i - 1] ^ a[i]; //生成异或前缀和 
	}
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j++){
			maxn = max(maxn, xor_a[j] ^ xor_a[i - 1]);//枚举左右端点取最大值 
		}
	}
	cout << maxn << endl;
	return 0;
}
//CF252A 
//Accepted in 2021/2/28
//by szkzyc 

```

### $---end---$


---

## 作者：Happy_Dream (赞：0)

前缀和的练手题，具体思路：

1，把所有数输入。

2，把所有区间的和求出来。

3，求一下那个区间异或和最大，并存给ANS。

4，输出ANS。

代码如下：

***

```cpp
// luogu-judger-enable-o2
#include <iostream>//头文件
using namespace std;
int a[105],s[105];//定义两个数组A用来输入，S用来存储异或和
int main()
{
	int n,ans=-1e9;//ANS是答案
	cin>>n;//输入一下N
	for(int i=1;i<=n;i++)
	cin>>a[i];//输入那几个数
	s[1]=a[1];//S数组的第一个永远都是A数组的一个
	for(int i=2;i<=n;i++)
	s[i]=a[i]^s[i-1];//把异或求出来
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			ans=max(ans,s[j]^s[i-1]);//把最大的异或和存下来
		}
	}
	cout<<ans;//输出异或和
	return 0;//结束
}
```
***

珍惜生命，远离抄袭。。。


---

