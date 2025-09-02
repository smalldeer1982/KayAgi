# [AGC012A] AtCoder Group Contest

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc012/tasks/agc012_a

AtCoder Group Contestの参加者に $ 3N $ 人が参加します。 $ i $ 番目の参加者の *強さ* は整数 $ a_i $ で表されます。 参加者が $ 3 $ 人 $ 1 $ 組となるようにチームを $ N $ 組作ることにしました。$ 1 $ 人の参加者が複数のチームに所属することはできません。

チームの強さはチームメンバーの強さのうち $ 2 $ 番目に大きい値で表されます。 例えば、強さが $ 1,5,2 $ のメンバーからなるチームの強さは $ 2 $ になり、強さが $ 3,2,3 $ のメンバーからなるチームの強さは $ 3 $ になります。

$ N $ 組のチームの強さの和としてありうる値のうち、最大の値を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ a_i\ ≦\ 10^{9} $
- $ a_i $ は整数

### Sample Explanation 1

例えば以下のようにチームを作ったとき、チームの強さの和が最大となります。 - チーム $ 1 $：$ 1,4,5 $ 番目の参加者からなる。 - チーム $ 2 $：$ 2,3,6 $ 番目の参加者からなる。

### Sample Explanation 2

チームの強さの和は非常に大きくなることがあります。

## 样例 #1

### 输入

```
2
5 2 8 5 1 5```

### 输出

```
10```

## 样例 #2

### 输入

```
10
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
10000000000```

# 题解

## 作者：封禁用户 (赞：3)

### 前言

[cnblogs](https://www.cnblogs.com/CM-0728/p/14459125.html)

### $\sf{Solution}$

显然要用到贪心的思想。

既然最终的结果只与每组强度第二大选手有关，那就考虑如何让他的值尽可能大。

其实，从小到大排个序就能解决，越靠后的值越大，使得每组强度第二大选手的值最大。

最后 $O(n)$ 扫一遍，更新 $ans$ 的值。

### $\sf{Code}$

代码短得可怜。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
ll n,a[300005],ans;
inline bool cmp(int x,int y){return x<y;}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	int mn=n*3;
	for(int i=1;i<=mn;++i)
		cin>>a[i];
	sort(a+1,a+mn+1,cmp);//排序
	for(int i=mn-1;i>=n+1;i-=2)
		ans+=a[i];//逐一统计每组的值，更新ans
	cout<<ans<<"\n";//atcoder 换行
	return 0;
}
```

---

## 作者：Anaxagoras (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT2361)

### 0x01 思路

既然由第二的人决定队伍强度，那么我们就要让强度第二的人能力尽量大，所以肯定是要排序的。那么拍完序后，从第 $n+1$ 个开始，隔一个挑一个即可做到能力值和最大。

### 0x02 AC Code（远古代码）

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cctype>
#include<string>
#include<cstring>
#include<algorithm>
#define int long long
int a[1000005];
using namespace std;
inline int read()
{
	char s=getchar();
	int x=0,f=1;
	while(s<'0'||s>'9')
	{
		if(s=='-')
		f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=x*10+s-'0';
		s=getchar();
	}
	return x*f;
}
inline void write(int x)
{
    if(x<0)
	{
		putchar('-');
		x=-x;
    }
    if(x>9)
    write(x/10);
    putchar(x%10+'0');
    return;
}
signed main()
{
	register int n=read();
	register int nn(n*3);
	for(register int i(1);i<=nn;++i)
	{
		a[i]=read();
	}
	sort(a+1,a+nn+1);
	register int sum(0);
	for(register int i(nn-1);i>=n+1;i-=2)
	{
		sum+=a[i];
	}
	write(sum);
	cout<<'\n';
	return 0;
}
```

---

## 作者：kaceqwq (赞：2)

# 题目大意:
共有 $3N$ 名参加者。参加者每三人组成一个小队，一共组成 $N$ 个小队。每个参加者都只能加入一个小队。小队的强度由队伍中第二强的队员的强度决定，例如，强度分别为 $1 , 5 , 2$ 的队员组成的小队强度为 $2$，强度分别为 $3 , 2 , 3$ 的队员组成的小队强度为 $3$。请求出这 $N$ 组小队的强度和中最大的数值。

# 分析:
首先，根据题意，小队强度是队伍中第二强的队员的强度，所以我们可以先将每一个队员的强度进行排序，接着把每两个强度挑出来，最后把挑出来的强度加起来输出即可。

# Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[10000005];
signed main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=3*n;i++)  //根据题意，总人数为3n。
		cin>>a[i];
	sort(a+1,a+1+3*n);    //sort从小到大排序
	for(int i=3*n-1;i>=n+1;i-=2)   //每两个强度存起来
	ans+=a[i];
	cout<<ans<<'\n';   //最后输出总和
	return 0;
}

```


---

## 作者：Night_sea_64 (赞：1)

本蒟蒻来水一波 AT 的黄题（~~毕竟只有 AT 有这么简单的黄题啊~~）。

本题主要考察的知识点是贪心。

题目意思：长度为 $3N$ 的序列 $a$，平均分成 $N$ 组，每组 $3$ 个数。求每组中次大值之和最大为多少。

我们先把 $a$ 从大到小排序。我们需要让每组中的次大值尽量大，也就是在排序后的数列中位置尽量靠前。

而因为数列中第 $k$ 个每组中的次大值之前一定有这组中的最大值。所以第 $k$ 个每组中的次大值最靠前的位置一定是 $2\times k$。因此答案就是 $a_{2}+a_4+a_6+\dots+a_{2\times N}$。

如果您已经看懂了，可以跳过下一个段落，直接看代码。

如果您还没看懂，我们就来举个例子。假设 $N=2,a=\{5,2,8,6,1,7\}$。排序后是 $\{8,7,6,5,2,1\}$。我们可以取 $7$，这时这组的最大值一定是 $8$。同理，还可以取 $5$，这组的最大值一定是 $6$。剩下的两个数分别作为两组中的最小值。如果你取 $8$ 作为一组中的次大值，就是一个错误答案。因为 $8$ 是整个数列中的最大值，如果它作为一组中的次大值，那前面就找不到这组的最大值了。话不多说，直接上 AC 代码！

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[300010];//记得数组大小要开到 n*3。
bool cmp(int x,int y){return x>y;}
int main()
{
    int n;
    long long sum=0;//不加 long long 见祖宗！！！
    cin>>n;
    n*=3;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n/3;i++)sum+=a[i*2];
    cout<<sum<<endl;
    return 0;
}
```

快乐地 AC 了一道黄题~~~

本次题解就到这里，求各位 dalao 点个赞吧~~~

---

## 作者：_xxy_ (赞：1)

题意：

给定一个长度为 $ 3n $ 的序列，每三个数分一组，求每组数的中位数相加最大为多少。

解法：

**贪心** 

思路：

先将数组排序，让最小的 $ n $ 个数分别作为每组中的最小值，对答案不产生影响，之后从数组最后开始，每次取两个数，分别作为每组的最大值和次大值，累加两个数中的较小数即可。

AC Code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){
    int x=0,f=1;
    char ac=getchar();
    while(ac<'0'||ac>'9'){
        if(ac=='-') f=-1;
        ac=getchar();
    }
    while(ac>='0'&&ac<='9'){
        x=x*10+(ac-'0');
        ac=getchar();
    }
    return x*f;
}
int a[300010],n;
long long num;
int main(){
    ios::sync_with_stdio(false);
    n=read();
    for(int i=1;i<=3*n;i++) a[i]=read();
    sort(a+1,a+n*3+1);
    for(int i=n*3-1;i>=n+1;i-=2){
        num+=a[i];
    }
    cout<<num<<endl;
    return 0;
}
```

---

## 作者：little_rubbish (赞：1)

## 思路
看到这种最值问题，马上想到了贪心。

因为“小队的强度由队伍中第二强的队员的强度决定”，所以在一个小组中就至少有较两个大强度的队员。

既然团队的强度只跟第二强有关，所以我们要让第三强尽可能的小，以让强度高的人到别的队发挥作用。

所以只需排序一遍，统计每队的强度并加上就好了。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[300001],n; 
ll ans;
int main(){
	cin>>n;
	for(int i=1;i<=n*3;i++)cin>>a[i];
	sort(a+1,a+n*3+1);
	for(int i=n*3-1;i>=n;i-=2)ans+=a[i];//n*3-1，i-=2 是因为第一强与队伍的强度无关。只需要枚举 n 个队伍的强度。
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：良辰、 (赞：1)

### [题目链接qaq](https://www.luogu.org/problemnew/show/AT2361)  

看一遍题，会很自然地联想到这道题是贪心，很显然会用到排序（小声）  

~~sort真好用~~


------------

# 正文部分

我们要求的是每3个人一组，每组中位数之和的最大值既然是中位数，而第3n个数又是这组数中最大的。那第3n个数一定对答案**没有贡献**（任何排列都无法使最大值成为某三个数的中位数）  

既然最大值没用，那就尽量让第二大的有用（大哥走了二哥上），而最小值又是我们最不想要的（小弟去勾引），所以很显然第一个三个数的排列就是【最小值，第二大的值，最大值】，答案增加的就是第二大的值。将这三个数去掉后又有了一组新的序列，和刚才做法一样对新序列进行操作，依此类推最后的边界就是第n-1个数。  


------------

下面给出一组例子（样例1）：  
n=2  
5 2 8 5 1 5  
标号：  
n-1，n，3 , 4 , 3n-1 , 3n；  
对应代码进行理解吧各位TT

排序过后：  
1 2 **5** 5 **5** 8  

排列方式：  
【1,5,8】
【2,5,5】  

答案：  
ans=5+5;  


------------

上代码咯：   
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=300000+10;
//因为n是100000，所以有300000个人，数组记得开够emm 
long long n,a[maxn],ans=0;//下意识开long long

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=3*n;i++){
		scanf("%lld",&a[i]);//输入也要3*n 
	}
	sort(a+1,a+1+3*n);//排序也要3*n 
	for(int i=(3*n)-1;i>=n+1;i-=2){
//		枚举也要3*n 
		ans+=a[i];
//		从倒数第二位开始向前枚举，每次跳过一个再加上一个 
	}
	printf("%lld\n",ans);
}
```  

呜呜呜我被这个“3倍”坑了好几次qaq  

结束。

---

## 作者：桃雨凪丝 (赞：0)

题目拿到手一看，贪心！


------------
因为只和第二大有关，所以只需要让第二大最大。

举个例子：
	5 2 8 5 1 5

对其进行排序（ stl 快排大法好）：

	1 2 5 5 5 8
    
8 作为第一组里的第一大数，5 是第二组里第二大数，发现是从后往前隔一个取数，for 循环就行啦！

贴贴：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int rd(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0' || ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
ll n,a[300010],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n*3;i++) cin>>a[i];
	sort(a+1,a+n*3+1);
	for(int i=n*3-1;i>=n+1;i-=2) ans+=a[i];
	cout<<ans<<"\n";
	return 0;
}
```



---

## 作者：EthanC_ (赞：0)

### 题意：
有 $3n$ 名参与者，求出每 $ 3 $ 个选手中能力第二强的选手的能力总和。
### 思路：
贪心，排序。排序后从 $3n$ 的位置开始 $ 2 $ 个 $ 2 $ 个取。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,m[1000001];
int main(){
    cin>>n;
    for(int i=0;i<n*3;++i)
        cin>>a[i];//输入每个参与者的强度
    sort(a,a+n*3);//sort排序
    for(int i=n*3;i>=n;i-=2)
        m+=a[i];//取第二大的值的总和
    cout<<m<<endl;//输出总和(别忘了换行)
    return 0;
}
```



---

## 作者：SalN (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT2361)
AT2361

-------------------

### 题目大意
给你 3n 个数，3个数一组，每组数的次大值之和最大是多少？

------------------

### 解题思路

贪心，让每组次大值尽量大，我们对数从大到小进行排序。

最大值显然不可能是次大值，所以最大值和次大值组成一组，以此类推，第 i 组的次大值是第 2*i 大的值，对次大值进行累加即可求出答案。

------------

### 代码实现

```cpp
#include<bits/stdc++.h>
#define MN 300300 
//总共是 3n 个数要开三倍空间
typedef long long LL;
using namespace std;
int n;
LL a[MN],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n*3;i++)
		scanf("%lld",a+i);
	sort(a+1,a+1+n*3,*[](LL x,LL y){
		return x>y;});
  //匿名函数，需要 c++11，可以写 cmp
	for(int i=1;i<=n;i++)
		ans+=a[i*2]; //累加次大值
	printf("%lld\n",ans);//AT 要换行
	return 0;
}
```


---

## 作者：cjZYZtcl (赞：0)

## 这题就是一个贪心
考虑怎么贪心。

对于每一组来说，第二大的值要尽可能的大，所以我们可以先把数组排序，然后从最后开始，每两个取一个小的（大的那个是每一组的最大值，小的是第二大的值），求一个总和即可。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[300005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read();
	for(int i = 1; i <= n * 3; i++){
		a[i] = read();
	}
	sort(a + 1, a + n * 3 + 1);
	int sum = 0;
	for(int i = 1; i <= n; i++){
		sum += a[i * 2 + n - 1];
	}
	write(sum);
}
```


---

## 作者：chufuzhe (赞：0)

## 题意：

将 $n * 3$ 个数每三个一组分成 $n$ 组，求最大的中位数之和。

## 思路：

每三个一组，贡献为第二个数，所以最小的数越小越好，第二大的数越接近最大的数越好，因此现将数组排序，然后从最大的开始两个两个取，加上小的那个的值。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace io {
    char buf[1 << 21], *p1 = buf, *p2 = buf, buf1[1 << 21];
    inline char gc() {
        if (p1 != p2)
            return *p1++;
        p1 = buf;
        p2 = p1 + fread(buf, 1, 1 << 21, stdin);
        return p1 == p2 ? EOF : *p1++;
    }
    #define G gc

    #ifndef ONLINE_JUDGE
    #undef G
    #define G getchar
    #endif

    template <class I>
    inline void read(I &cn) {
        char c; int sig = 1;
        while(!isdigit(c = G())) if(c == '-') sig = 0;
        if(sig) {cn = c-48; while(isdigit(c = G())) cn = (cn<<3)+(cn<<1)+(c-48); }
        else    {cn = 48-c; while(isdigit(c = G())) cn = (cn<<3)+(cn<<1)+(48-c); }
    }
    inline void write(int n) {
    	if(n < 0) {
    		putchar('-');
    		n = -n;
		}
        if(n < 10) {
            putchar(n % 10 + '0');
            return ;
        }
        write(n / 10);
        putchar(n % 10 + '0');
    }
}
using namespace io;
int a[300005];
int main()
{
	ios::sync_with_stdio(false);
	int m; //m表示组数
	read(m);
	int n = m * 3; //n表示人数
	for(int i = 1; i <= n; i++)
		read(a[i]);
	sort(a + 1, a + n + 1); //排序
	long long ans = 0; //注意用long long
	for(int i = n - 1; i > m; i -= 2) //两个两个取
		ans += a[i]; //累加答案
	cout << ans << endl;
	return 0;
}

```


---

## 作者：Lithium_Chestnut (赞：0)

### 大概思路

没啥的，就是把数列拆分一下，排个序（`STL` 大法妙啊），把中位数求和输出解决！

注意 `AtCoder` 的题里面一般都是 $2 \times n,3 \times n$ 之类的,所以我就开了一个 $p$ 表示求和,循环里直接引用就行了，还有此题一定开个 `long long`，最后唠叨一句：`AtCoder` 的题一定要换行！！

### $std$

```
#include<bits/stdc++.h>
using namespace std;
long long n,a[300001],p,ans;
int main()
{
	cin>>n;
	p=n*3;
	for(int i=1;i<=p;i++) cin>>a[i];
	sort(a+1,a+p+1);
	for(int i=p-1;i>=n+1;i-=2) ans+=a[i];
	cout<<ans<<endl;
	return 0;
}
```


---

