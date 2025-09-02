# Sage's Birthday (easy version)

## 题目描述

This is the easy version of the problem. The difference between the versions is that in the easy version all prices $ a_i $ are different. You can make hacks if and only if you solved both versions of the problem.

Today is Sage's birthday, and she will go shopping to buy ice spheres. All $ n $ ice spheres are placed in a row and they are numbered from $ 1 $ to $ n $ from left to right. Each ice sphere has a positive integer price. In this version all prices are different.

An ice sphere is cheap if it costs strictly less than two neighboring ice spheres: the nearest to the left and the nearest to the right. The leftmost and the rightmost ice spheres are not cheap. Sage will choose all cheap ice spheres and then buy only them.

You can visit the shop before Sage and reorder the ice spheres as you wish. Find out the maximum number of ice spheres that Sage can buy, and show how the ice spheres should be reordered.

## 说明/提示

In the example it's not possible to place ice spheres in any order so that Sage would buy $ 3 $ of them. If the ice spheres are placed like this $ (3, 1, 4, 2, 5) $ , then Sage will buy two spheres: one for $ 1 $ and one for $ 2 $ , because they are cheap.

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
2
3 1 4 2 5```

# 题解

## 作者：dead_X (赞：2)

## 前言
好像是重题。

抱歉觉得 D1 没什么价值就直接把 D2 的题解 Copy 过来了。
## 题意
给定 $n$ 个数 $a_i$ ，重排它们使得 $|S|$ 最大，其中 $S=\{x|1<x<n,a_{x-1}>a_x<a_{x+1}\}$
## 思路
二分答案。

显然如果答案为 $x$ ，我们只需要构造 $2x+1$ 个数并判断是否满足即可。

构造的方法如下：小配小，大配大。

也就是 $\red{a_{n-x}},a_1,\red{a_{n-x+1}},a_2,\red{a_{n-x+2}},a_3,\cdots,\red{a_{n-1}},a_x,\red{a_n}$。

为了方便理解，这里区分了颜色，红色为最大的数，黑色为最小的数，两者都从小到大排序。

注意一下二分的右区间。
## 代码
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003],b[1000003],c[1000003];
bool check(int n,int x)
{
	int t=n-x-1;
	for(int i=1; i<=x; i++) b[i*2-1]=a[++t],b[i*2]=a[i];
	b[x*2+1]=a[++t];
	
	for(int i=1; i<=x; i++) if(b[i*2-1]<=b[i*2] || b[i*2]>=b[i*2+1]) return 0;
	
	t=x;
	for(int i=1; i<=x*2+1; i++) c[i]=b[i];
	for(int i=x*2+2; i<=n; i++) c[i]=a[++t];
	return 1;
}
int main()
{
	int n=read();
	for(int i=1; i<=n; i++) c[i]=a[i]=read();
	sort(a+1,a+n+1);
	int l=1,r=(n-1)/2;
	int res=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(n,mid)) res=mid,l=mid+1; else r=mid-1;
	}
	printf("%d\n",res);
	for(int i=1; i<=n; i++) printf("%d ",c[i]);
	return 0;
}
```

---

## 作者：king_xbz (赞：1)

不难的构造题，此题为简单版。然而好像没有详细讲述如何构造的，我来发一发。
# 题意简述
当i位置价格比i-1位置和i+1位置低时，就买i位置物品，**物品价格各不相同**，求最多能买多少个
# 思路分析
很显然，我们想让有最多的“山”字序列（中间低，两边高）。这样即为最优解。

那么，如何构造呢？

我们可以考虑进行排序，把前$i/2$小的从小到大放在偶数位上，剩下的从小到大依次放到奇数位上，这样一定满足“山”字序列最多。
# 代码实现
```cpp
int main()
{
	int n;
	cin>>n;
	for(fint i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+n+1);
	int cnt=0;
	for(fint i=2;i<=n;i+=2)
	s[i]=a[++cnt];
	for(fint i=1;i<=n;i+=2)
	s[i]=a[++cnt];
	int ans=0;
	for(fint i=1;i<=n;i++)
	if(s[i]<s[i-1]&&s[i]<s[i+1])
	ans++;
	cout<<ans<<endl;
	for(fint i=1;i<=n;i++)
	cout<<s[i]<<" ";
	return 0;
}
```
祝大家AC愉快哦！

---

## 作者：Ryo_Yamada (赞：1)

~~D1 和 D2 都是构造题，CF = Code Forces ×，CF = Construct Forces √.~~

> 若 $a_{i-1} > a_i$ 且 $a_{i+1} > a_i$，则 $a_i$ 可以买。保证 $a_i$ 不重复，问在 $a_i$ 的所有排列中能买的个数的最大值，$a_1$ 和 $a_n$ 不能买。

首先，若 $a_{i-1} > a_i$ 且 $a_{i+1} > a_i$，$a_{i-1}$ 和 $a_{i+1}$ 就肯定不能买。我们构造，让 $a_{i \times 2}$ 都能买，不过注意一点，若 $n$ 为偶数则需要 $-1$，$a_n$ 是不能买的。于是 $\operatorname{ans} = \dfrac{n}{2} - (n \!\!\mod 2 = 0)$。我们把最小的 $\operatorname{ans}$ 个放到我们构造的要买的位置。

顺便一说我刚开始~~装*~~写位运算结果没加括号吃罚时了，我直接裂开。

~~所以千万不要装*~~

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int a[100005], cnt1, cnt2;

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	int k = n / 2;
	if((n & 1) == 0) --k;
	cout << k << endl;
	sort(a + 1, a + n + 1);
	cnt1 = k;
	for(int i = 1; i <= n; i++) {
		if((i & 1) == 0 && cnt2 < k) printf("%d ", a[++cnt2]);
		else printf("%d ", a[++cnt1]); 
	}
	return 0;
}

```


---

## 作者：Forever1507 (赞：0)

简单构造题。

答案特别明显是 $(n-1) \div 2$ 吧，大小交汇即可。

奇数情况特别明显，偶数时最后一个不算所以要减 $1$ 。

构造上面也已经说了，代码走起：
```
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cout<<(n-1)/2<<'\n';//个数
	sort(a+1,a+n+1);//排个序，输出时大小交错
	for(int i=1;i<=n/2;i++){
		cout<<a[i+n/2]<<' '<<a[i]<<' ';//一大一小
	}
	if(n%2==1)cout<<a[n];//奇数时再补一个
	return 0;
}

```


---

## 作者：Trollz (赞：0)

又是一个看起来好难 ~~实际上仔细观察一下就可以做出来的~~CF题呢

**话不多说，直接讲正题**

### 看题
首先，我们看一看题目。就是给你一个数列，让你求出一个夹在两个大数之间的数的数量最多的一个数列。

说白了，给你一个这样的数列（H表示较大的数，S表示较小的数）：
```
H H H S S S
```
让你求一个这样子的数列：
```
H S H S H S
```
顺便把夹在两个大数之间的数的数量输出来。
### 做题
就根据上面的图例来说，想要求出这个数列是不是有点为难呢。

~~是不是还要DFS BFS DP反正各种奇奇怪怪的算法来做呢~~

实际上，你只需要记住一个规律：

### CF要是标为入门但是看起来很难的题，一定会有规律可循！
比如说，我们可以把这个数列$sort$一下，然后把这个数列的每两个相邻的数字交换一下，隔一个数字再交换一下，反正后面的数字一定比前面的数字大，这样，不就交换出一个理想的数列了嘛！

比如说，原数列是这个样子的：
```
1 2 3 4 5 6
```
然后依次交换：
```
2 1 4 3 6 5
```
完美的符合要求的数列不就出来了嘛！

于是，我们求出数列的代码就是这样：
```cpp
for(int i=1;i<=n;i++){
	cin>>a[i];
}
sort(a+1,a+n+1,ioi);
for(int i=2;i<=n;i+=2/*隔一个再交换*/){
	swap(a[i],a[i-1]);
}
```
可能这时候就有同学有疑问了：
#### 为什么i=2而不是i=1呢？？
因为我们是隔一个交换一次，如果$i=1$的话，最开始交换的时候会把$a_0$和$a_1$交换一次，由于我们输入的时候没有把$a_0$赋值，所以就会导致$a_0$的空数值交换到了$a_1$上。这是我们所不希望出现的。所以我们从$a_2$开始，就不会把那些无用的东西给交换上来了。

处理完了数列，还有这个商品数量没有解决。很简单，我们只要再搜索一次，如果一个元素的数值比周围都小，就说明它是一个符合题意的数字，那么解决这个问题的代码也有了：
```cpp
for(int i=2;i<=n-1;i++){
	if(a[i]<a[i+1]&&a[i]<a[i-1]){
		sum++;
	}
}
同样的，i<=n-1和i=2也是为了不会检查到一些奇奇怪怪的东西。
```

那么，闪亮的主代码程序就有了！

$\text{Code:}$
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[100001];
int n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=2;i<=n;i+=2){
		swap(a[i],a[i-1]);
	}
	int sum=0;
	for(int i=2;i<=n-1;i++){
		if(a[i]<a[i+1]&&a[i]<a[i-1]){
			sum++;
		}
	}	
	cout<<endl<<sum<<endl;
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
} 
```
顺嘴提一句，数组一定要开大一点，$a[1001]$是过不了的。

##### 管理大大求通过qwq

---

## 作者：Aiopr_2378 (赞：0)

# 思路

- 按题目要求输入

- 按照从小到大的顺序排序，原因见后

- 要想要结果最大，就必须要小数在中间，大数在两边。同事开头不要是小数，因为这样会白白浪费一个购买的机会。

- 结果就出来了！！

- 题目输入量较大，最好用$scanf$和$printf$读取和输出，这样输入较快。

#### 上代码
~~（你们喜欢看这个）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt,sum;
long long a[100005],ans[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+1+n);
	for(int i=2;i<=n;i+=2) ans[i]=a[++cnt];
	for(int i=1;i<=n;i+=2) ans[i]=a[++cnt];
	for(int i=1;i<=n;i++) if(ans[i]<ans[i-1]&&ans[i]<ans[i+1]) sum++;
	cout<<sum<<endl;
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);//“%lld”后面有空格哦，亲
	return 0;
}
```

~~亲，这边建议您点赞再走~~

---

## 作者：daniEl_lElE (赞：0)

想要让“山谷”更多，我们最好使用一高一低相结合的方法。

所以，我们从低到高格一个放一个，轮流放，小的配比较小的，大的配比较大的，很容易。

最后会组成这样：

$A_x$ $A_1$ $A_{x+1}$ $A_2$ $A_{x+2}$ $A_3$ $...$ $A_n$

根据奇偶型会有细微差别。

然后，先把数列排好，再进行计算有多少商品可以购买。

代码如下：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int n,sum=0;
	cin>>n;
	int a[n+1],b[n+1];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n/2;i++){
		b[i*2]=a[i];
	}
	if(n%2==1){
		for(int i=n/2+1;i<=n;i++){
			b[i*2-n]=a[i];
		}
	}
	else{
		for(int i=n/2+1;i<=n;i++){
			b[i*2-n-1]=a[i];
		}
	}
	for(int i=2;i<n;i++){
		if(b[i-1]>b[i]&&b[i]<b[i+1]){
			sum++;
		}
	}
	cout<<sum;
	cout<<endl;
	for(int i=1;i<=n;i++){
		cout<<b[i]<<" ";
	}
	return 0;
}
```

---

## 作者：black_trees (赞：0)


一道比较简单的构造题；

-----

我们分析一下样例不难发现：

如果是 $n=5$ ，$a[]={1,2,3,4,5}$
的情况，那么最多也就拿 $1,2$ 这两个物品。

所以就输出 $\lfloor n/2 \rfloor$ 就行了吗？

但是CF的构造题……样例只给你一组数据……

很可能就有多种情况，让你不考虑这些然后直接吃罚时。

所以再分析几组。

$n=6$ , $a[]={1,2,3,4,5,6}$

那么一种最佳的排列是这样的：

$2,1,4,3,6,5$

很明显。$\lfloor n/2 \rfloor$ 是错的。

因为这题只有奇偶数两种情况，所以可以推出

$ans = \lfloor \ ( n-1 \ )/2 \rfloor$

具体实现直接用位运算。

~~~cpp
        sort(a+1,a+1+n);//排序方便输出
        cout<<((n-1)>>1)<<endl;
        for(register int i=1;i<=(n>>1);++i){
            cout<<a[i*2]<<" "<<a[i*2-1]<<" ";
        }

~~~

但是在输出的时候，如果两边都按一种方式输出，那么奇数的情况就会少输出一个数，所以这时再后面补 $a[n]$ 就可以了。

---

~~不愧是构造forces~~




---

## 作者：人间凡人 (赞：0)

### 题意：给定 $n$ 个数 , 任意排列使得严格低于左右两边的数最多的个数和状态。


### 思路：

$1:$ 求个数，要有一个满足条件的数，我们至少会需要 $3$ 个数。之后，没多一个满足的数，都会需要 $2$ 个新的数，所以如果要有 $x$ 个满足的数，我们就至少有 $2x+1$,所以，若有 $n$ 个数，则至多会有 $\frac{n-1}{2}$ 个满足条件的数，那么就输出$\frac{n-1}{2}$即可。

$2:$ 求状态，贪心! 现将所有数从小到大排一遍序，找到中间的那一个数。假设排完序后为 $a[1],a[2]...a[n]$.

那么 $a[1]<a[\frac{n-1}{2}+1],a[2]<a[\frac{n-1}{2}+2]...a[\frac{n-1}{2}]<a[2*\frac{n-1}{2}].$

至于其它那些数，只要随便输出即可(无论啥顺序都不会有一个满足条件的数了).

$Code:$
```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,a[100009],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);ans=(n-1)/2;
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)printf("%d %d ",a[ans+i],a[i]); 
	for(int i=2*ans+1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}
```


---

