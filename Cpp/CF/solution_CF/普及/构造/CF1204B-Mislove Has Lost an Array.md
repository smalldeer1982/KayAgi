# Mislove Has Lost an Array

## 题目描述

有一个长度为 $n$ 的整数序列 $a_1,\,a_2,\cdots,a_n$ ，满足以下条件

- 序列中不同的数的个数在区间 $[\,l,\,r\,]$ 中
- 序列中的元素只有 $1$ 和偶数，若 $a_i$ 在序列中，那么 $\frac{a_i}{2}$ 也在序列中

对于给定的 $n,\,l,\,r$ 试求出该序列所有元素加和的最大值与最小值

## 样例 #1

### 输入

```
4 2 2
```

### 输出

```
5 7
```

## 样例 #2

### 输入

```
5 1 5
```

### 输出

```
5 31
```

# 题解

## 作者：引领天下 (赞：2)

这个题实际上就是贪心

思路：先取2的0到l-1次方，保证至少有l个不同的数，算出基本答案；

然后对于最小的答案，剩下的n-l个数全部填1，对于最大的答案，我们补全2的r-1次方，然后对于剩下的n-r个数全部填$2^{r-1}$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,l,r,cnt=1,ansn,ansx;//注意，防爆int
int main(){
    cin>>n>>l>>r;
    for (int i=1;i<=l;i++)ansn+=cnt,cnt*=2;
    ansx=ansn,ansn+=n-l;//计算出基本答案后直接算出最小答案
    for (int i=l+1;i<=r;i++)ansx+=cnt,cnt*=2;
    cnt/=2;
    ansx+=(n-r)*cnt;//补上n-r个数
    cout<<ansn<<' '<<ansx;
}
```

---

## 作者：rsjw (赞：2)

CF昨天晚上的比赛第一题，大大水题。

~~比第一题简单555~~

先发发广告：[这是我搭的OJ](https://rsjoj.cf)

此题题目有些绕啊，要不然肯定当作第一题

只要看懂题目，相信水题拦不了你！

理解了就懂了，题目要求的数组去重后是一个首项为$1$，公比为$2$的等比数列。所以尽可能小，就是先都放$1$，再放完一组L项的等比数列；尽可能大，就是先放完一组$L$项的等比数列，再都放$2^{r-1}$，可以保证一定是是极端数据。

于是一行输出，一行输入，超简洁代码来了：

```cpp
#include <cstdio>
#include <cmath>
int main(){
    int n,l,r;
    scanf("%d%d%d",&n,&l,&r);
    printf("%d %d",(int)(pow(2,l)-1)+n-l,(int)(pow(2,r)-1)+(n-r)*(int)pow(2,r-1));
    return 0;
}
```

---

## 作者：tjer (赞：1)

# 思路
[题链](https://www.luogu.com.cn/problem/CF1204B)

贪心做的

初始化说明： 

$max1$ 存储最大结果 $min1$ 存储最小结果 $n$ 为序列的长度 $l,r$ 分别表示不相同的数的个数

整体思路框架：

题目要求中说中只有 1 与偶数

则只需要分别处理最小值与最大值就行了

- 1. 处理最小

使用贪心思路 如果能在序列中放入1那就尽量放的多

- 2. 处理最大

每一位都放尽量大的数 然后再最大的循环处理时会多乘上一个 $2$ 所以在循环结束后除掉

最后如果还有空位就用之前的最大数填充

# 代码

```cpp
#include<bits/stdc++.h> //万能头
using namespace std;
int max1,min1,n,l,r;
int main () {
    cin >>n >>l >>r;
    
    //最小
    min1=n-(l-1);
    //样例1中4 2 2 //最少需要两个不相同的数 则在剩下的3个空位中都塞入1
    for(register int i=2,i1=1;i<=l;i++){
        min1+=i1*2;
        i1*=2;
    }
    //处理最小情况中的剩下的序列空位
    //样例1中4 2 2//剩下1个空位 用尽量小的偶数填充（即从1一位一位往上乘2）
    
    //最大
    int i1=1;
    for(register int i=1;i<=r;i++){
        max1+=i1;
        i1*=2;
    }
    i1/=2;
    //除掉
    for(register int i=r+1;i<=n;i++){
        max1+=i1;
    }
    //填充
    cout <<min1 <<" " <<max1;
    return 0;//蕐骊的结束
}
```
纯暴力代码 勿喷

---

## 作者：Ryan_Adam (赞：0)

# CF1204B Mislove Has Lost an Array 题解
## 算法
贪心水题。

## 思路分析
题目中说**若 $a_i$ 在序列中，那么 $\frac {a_i}{2}$ 也在序列中**。从这句话可以知道我们能取的数都是**二的整数次幂**，而且必须从零次幂 $(1)$ 开始依次往后取。题目又要求**不同的数的个数**在区间 $[l,r]$ 中，说明我们至少要从 $2^0$ 取到 $2^{l-1}$。接下来还剩 $n-l$ 个数，就可以分类讨论最大最小的情况了。

在你取的不同的数的个数已经满足要求了的时候，当然是把剩下的数全部填成 $1$ 最小。所以最小值就是 $\sum_{i=0}^{l-1}2^i+(n-l)$。

要取最大值，当然就是在要求满足的情况下尽量往上取，也就是从 $2^0$ 取到 $2^{r-1}$。如果取到 $2^{r-1}$ 之后 $n$ 个数还没取完，就一直取最大的也就是 $2^{r-1}$ 即可。最大值就是 $\sum_{i=0}^{r-1}2^i+(n-r)2^{r-1}$。

注意：如果用 `pow` 函数记得要保留整数。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace Raiden
{
    signed work()
    {
        int n,l,r;
        cin>>n>>l>>r;
        int sum=0,res=0;
        for(int i=0;i<l;i++)
            sum+=pow(2,i);
        for(int i=0;i<r;i++)
            res+=pow(2,i);
        cout<<fixed<<setprecision(0)<<sum+(n-l)<<" "<<res+(n-r)*pow(2,r-1)<<endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：_d_h_f (赞：0)

## solution
这道题用贪心算法

假设序列中有 $k$ 个不同的数，很容易证得这个序列中的数都是 $2^x$，其中 $1\le x\le k$，因为题目中写着：假如 $a_i$ 在序列中，那么 $\frac{a_i}{2}$ 也在序列中，又因为序列中只能有 $1$ 和偶数组成，所以 $\frac{a_i}{2}$ 必定是个偶数，再由题目可得 $\frac{a_i}{4}$ 也是偶数，以此类推，到最后 $\frac{a_i}{2^x}$ 必定会得到一个奇数 $1$，所以 $a_i$ 就是 $2^x$。所以可以推出序列中包含有以下几个数：
$1,2,4,\ldots,2^{k-2},2^{k-1}$

根据上面的推导，我们可以假设序列的前 $k$ 个不相同的数为 $1,2,4,\ldots,2^{k-2},2^{k-1}$，前 $k$ 个数的和可以表示为 $2^k-1$，显然前 $k$ 个数的最小值为 $2^l-1$，最大值为 $2^r-1$，那么如果要取到最小值，那么我们就可以将序列中的前 $l$ 个数填充为 $1,2,4,\ldots,2^{l-2},2^{l-1}$，其他数填充为 $1$，则序列最小值为 $2^l-1+(n-l)$，最大值也是一样，将前 $r$ 个数填充为$1,2,4,\ldots,2^{r-2},2^{r-1}$，其他数填充为 $2^{r-1}$，则序列最大值为 $2^r-1+(n-r)\times2^{r-1}$。

至于 $2^x$ 怎么算，我们可以定义一个函数 $\operatorname{chk}$ 用来计算 $2^x$，具体代码如下：

```cpp
int chk(int x){
	int res=1;
	for(int i=1;i<=x;++i)
		res*=2;
	return res;
}
```
或者我们可以用 $\operatorname{pow}$ 函数计算，代码简洁省时，但是要类型转换。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[10005];
int n,l,r;
int solve(int x){
	int res=1;
	for(int i=1;i<=x;++i)
		res*=2;
	return res;
}
int main(){
	scanf("%d%d%d",&n,&l,&r);
	printf("%d %d",solve(l)+(n-l)-1,solve(r)-1+(n-r)*solve(r-1));
	return 0;
}

```

或者（这份代码看起来怪怪的，好像强制转换有点奇怪，但还是过了）

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,l,r;
int main(){
	scanf("%d%d%d",&n,&l,&r);
	printf("%d %d\n",int(pow(2,l))+(n-l)-1,int(pow(2,r))-1+(n-r)*int(pow(2,r-1)));
	return 0;
}
```



---

## 作者：fengxiaoyi (赞：0)

### 思路
这题所要求的序列，一定包含（设不同的个数为 $k$）：
$$1,2,2^2,2^3,2^4,\cdot\cdot\cdot,2^{k-1}$$
证明很简单：

------------

#### 证明1
题目说:若 $a_i$ 在序列中，则 $\frac{a_i}{2}$ 也在序列中（要注意没有 $0$）。

所以当序列最大正整数 $2^k$，那么这个序列就有 $k+1$ 个不同的数；

------------

接着我们来分析序列和的最大值和最小值怎么求。

显然，题目给的 $l$ 就是当序列和最小是这个序列数不同的个数，$r$ 就是当序列和最大是这个序列数不同的个数.

所以我们先往和最小的序列里放上
$$1,2,\cdot\cdot\cdot,2^{l-1}$$
我们为了和最小，所以会用 $1$ 来填充剩余的部分。

答案就是：
$$2^l+n-l-1$$

再往和最大的序列里放上
$$1,2,\cdot\cdot\cdot,2^{r-1}$$
我们为了和最大，所以会用 $2^{r-1}$ 来填充剩余的部分。

答案就是：
$$2^r-1+(n-r)\ast 2^{r-1}$$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,mi,ma;
int main(){
	cin>>n>>l>>r;
	cout<<(1<<l)+n-l-1<<' '<<(1<<r)-1+(n-r)*(1<<(r-1));
	return 0;
}

```


---

## 作者：fls233666 (赞：0)

我们可以发现，这个序列的第二个限制条件很奇怪：

**序列中的元素只有$1$和偶数，如果$a_i$在序列中，那么$\frac{a_i}{2}$也在序列中。**

来看看在这个限制条件下能产生哪些偶数：

- 因为$1$在序列中，所以$2$可以在序列中。
- 因为$2$在序列中，所以$4$可以在序列中。
- 因为$4$在序列中，所以$8$可以在序列中。
- 因为$8$在序列中，所以$16$可以在序列中。

.........

我们会发现，能加入序列的数都是形如$2^n$这样的数字。

也就是说，这个数列里面只有形如$2^n$的数字。

那么下面，我们就可以来**贪心**解决此题了。

对于最小值，在满足不同数的个数为$l$的情况下，使用尽量多的$1$。

对于最大值，先尽可能的产生不同的数，直到不同数个数为$r$，如果此时数列中的数的个数还没有满$n$个，就用刚才产生的不同数中的最大数把数列填满。

至此，此题得解，下面是代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n,l,r,js=0,x=1,mn,mx;
	scanf("%d%d%d",&n,&l,&r);
  //数据读入
  
	for(int i=0;i<l;i++,x*=2)
		js+=x;
	mx=mn=js;
    //先产生l个不同数，记入max与min中
                           
	mn+=n-l;   //min只需要n-l个1就可以得到答案
                           
	x/=2; 
	for(int i=l;i<n;i++){
		if(i<r)
			x*=2;
		mx+=x;
	}//产生最大值
                
	printf("%d %d",mn,mx);   //输出答案
	return 0;
}
```


---

## 作者：世末OIer (赞：0)

~~你们真聪明，老实点把这个数组贪心的算出来不好吗~~

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
ll n,x,y;
ll a[100005];
int main(){
	cin>>n>>x>>y;
	ll mn=0,mx=0;
	mn=0;
	a[n]=1<<(x-1);
	for(int i=n-1;i;--i){        //越小越好
		if(a[i+1]>1)a[i]=a[i+1]/2;
		else a[i]=1;
		mn+=a[i];
	}
	mn+=a[n];
	memset(a,0,sizeof(a));
	a[1]=1;
	for(int i=2;i<=n;++i){       //越大越好
		if(i>y)a[i]=a[i-1];
		else a[i]=a[i-1]*2;
		mx+=a[i];
	}
	mx+=a[1];
	cout<<mn<<' '<<mx<<endl;
}
```

---

## 作者：Meatherm (赞：0)

如果要求最小，那么我们就要让尽可能多的数为 $1$。

由于至少要有 $l$ 个不同的数，于是我们可以让前 $n-l+1$ 个数为 $1$，剩下的数为 $2,4,8,16,···$。

如果要求最大呢？

我们可以将第 $i(1\leq i \leq r)$ 个数 设为 $2^{i-1}$。然后把剩下的数全都设为 $2^{r-1}$。这样就可以最大。

```
# include <bits/stdc++.h>
# define rr register
# define int long long
int n,l,r;
int Minx,Maxx;
signed main(void){
	scanf("%I64d%I64d%I64d",&n,&l,&r);
	Minx=(n-l+1);
//	printf("%I64d\n",Minx);
	int base=2;
	for(rr int i=1;i<=n-(n-l+1);++i){
		Minx+=base;
//		printf("%I64d\n",Minx);
		base<<=1;
	}
	base=1;
	for(rr int i=1;i<=r;++i){
		Maxx+=base;
		base<<=1;
	}
	base>>=1;
	for(rr int i=r+1;i<=n;++i){
		Maxx+=base;
	}
	printf("%I64d %I64d",Minx,Maxx);
	return 0;
}
```

---

## 作者：Kizuna_AI (赞：0)

比赛提交能一次过，~~说明这道题很水~~

题目不解释了，~~大家应该看得懂~~，我就说说看我的思路吧

思路：
1. 他要求求最小值和最大值。那么，我把最小值全部赋值为1，最大值全部赋值为$2^n$  
2. 对于最小值来说，是否满足他$l$的条件呢？如果$l>1$，我们就加上他的差额
3. 同理，对于最大值来说，是否满足$r$的条件呢？如果不满足，我们就减去差额

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,l,r;
long long mini,maxi,tmp;
long long quick_pow(long long a) {
	long long ans=1;
	for(int i=1;i<=a;i++)
		ans*=2;
	return ans;
}
int main() {
	scanf("%d%d%d",&n,&l,&r);
	mini=n;tmp=quick_pow(r-1);maxi=tmp*n;
	for(int i=1;i<l;i++)
		mini+=quick_pow(i)-1;
	for(int i=1;i<r;i++)
		maxi-=tmp-quick_pow(i-1);
	printf("%I64d %I64d",mini,maxi);
	return 0;
}
```

Note：CF的long long输出要用`%I64d`

---

## 作者：zzbzzbzzb (赞：0)

**题意**：你需要设计出一个长度为n，不同数字个数为l-r之间的序列满足：序列中含有1且其他数偶数且它的1/2出现在序列中过。  

**solotion**：原本序列中只有1，那么只有1*2可以加入序列，这样不断递推可得只有2^k可以加入序列，k∈Z并且k>=0，所以利用贪心思想。                                    

我们可以知道最小值应该让尽可能多的数是1，并使不同的数尽可能的少，才能使的1尽可能多，对于前面n-l+1个数都取1，后面的l-1个数取2^k，且k是逐个递增才能是总和尽可能的小。    

我们再来考虑最大值，最大值也是贪心，且显然是要使1的个数尽量小（即为1）。但是其他数出现前提是其1/2在序列中出现过，所以我们还是一次枚举k，不断累加2^k，因为是取最大值，所以只有不同的数尽可能多才可以让2^k枚举到更大，所以不同数的个数应取r。剩下n-r个数怎么办呢？既然不能再加入不同的数，又要去最大值，那么可以贪心的将当前最大值重复加入，直到序列长度为n。

**代码实现**：
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#define re register
#define ll long long
using namespace std;
int n,l,r;
int main(){
	scanf("%d%d%d",&n,&l,&r);
	int tot=1,minn=n-l+1;//前n-l+1的数全用1填充
	for(re int i=2;i<=l;i++){
		tot*=2;//枚举2^k并不断累加
		minn+=tot;
	}
	
	int maxx=1;tot=1;
	for(re int i=2;i<=r;i++){
		tot*=2;//枚举2^k并不断累加
		maxx+=tot;
	}
	maxx+=(tot*(n-r));//剩余的数用最大值补全
	
	printf("%d %d",minn,maxx);
    return 0;
}
```
**首次写题解，大佬们不喜勿喷**

---

## 作者：SilverStar (赞：0)

### 题意

有一个长度为 $n$ 的整数序列 $a_1,\,a_2,\cdots,a_n$ ，满足以下条件

- 序列中不同的数的个数在区间 $[\,l,\,r\,]$ 中
- 序列中的元素只有 $1$ 和偶数，若 $a_i$ 在序列中，那么 $\frac{a_i}{2}$ 也在序列中

对于给定的 $n,\,l,\,r$ 试求出该序列所有元素加和的最大值与最小值

### 题解
考虑贪心，对于最小值，显然我们希望有尽可能多的 $1$ 在序列中，此时的序列必然形如 $1,\,1,\cdots,2^{l-2},\,2^{l-1}$ ，可以直接计算

对于最大值，同理，我们希望序列中的 $2^{r-1}$ 最多，此时序列形如 $1,\,2,\,4,\cdots,2^{r-1},\,\cdots$ ，同样可以直接计算，时间复杂度为 $O(n)$

### $\text{Code}$

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

int n,l,r;
long long Max, Min;

int main(){
    scanf("%d%d%d",&n,&l,&r);
    Min = n-l, Max = 1ll*(n-r)*(1 << (r-1));
    for(int i = 0; i<l; i++)
        Min += (1 << i);
    for(int i = 0; i<r; i++)
        Max += (1 << i);
    printf("%I64d %I64d",Min,Max);
    return 0;
}
```

---

