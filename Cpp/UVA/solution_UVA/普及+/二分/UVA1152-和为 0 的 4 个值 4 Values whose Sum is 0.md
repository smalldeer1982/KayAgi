# 和为 0 的 4 个值 4 Values whose Sum is 0

## 题目描述

给出四个数组  $A,B,C,D$ ，每个数组中有  $n$  个整数。求有多少组  $i,j,k,l$  满足  $A_i+B_j+C_k+D_l=0$ 。

## 说明/提示

$1\le n\le4000$ 。数组中所有数的绝对值不大于  $2^{28}$ 。

# 题解

## 作者：c60521c (赞：11)

**本题主体思路**  
- 暴力  
若是按A+B+C+D=0直接算  那么可以如下：
```cpp
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		for(int k=1;k<=n;k++)
			for(int q=1;q<=n;q++)
				if(a[i]+b[i]+c[i]+d[i]==0)
   	 				ans++;
```
------------
- 二分  
说明：  
上面四重循环直接暴力，但$O(n^4)$显然是**超时**的。

继续来说思路：将$a+b+c+d=0$进行恒等式变形： $c+d=-(a+b)$ 

再用两个数组sum1，sum2分别储存$c+d$和 $-(a+b)$。  
最后排序加二分**upper-lower**累加答案输出。

------------
本题算法：
继上文的思路，来介绍一下算法upper与lower：
- ```lower_bound(a+1,a+n+1,key) ```下界 找到第一个大于等于key的地址。  
- ```upper_bound(a+1,a+n+1,key)```  上界 找到第一个大于key的地址。  
- ```upper_bound(a+1,a+n+1,key)-lower_bound(a+1,a+n+1,key)``` 求key在数组中的连续个数。
------------
核心代码思路：  
存$-(a+b)$
```
	cnt1++;
	sum1[cnt1]=-(a[i]+b[j]); //sum1存-(a[i]+b[j])
```
存$c+d$
```cpp
	cnt2++;
	sum2[cnt2]=c[i]+d[j]; //sum2存c[i]+d[j]
```
$upperbound-lowerbound$ 求 ans
```
for(int i=1;i<=cnt2;i++)//这里<=cnt2，在cnt2个中找
{
		ans+=upper_bound(sum1+1,sum1+cnt+1,sum2[i])-lower_bound(sum1+1,sum1+cnt+1,sum2[i]);//upper-lower来找sum2[i]的连续个数，累加给ans
}
```
最后附上AC代码  
**AC Code**:
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=4005;
int n,a[maxn],b[maxn],c[maxn],d[maxn];//参考题目数据
int sum1[maxn*maxn],sum2[maxn*maxn];//这里用一维
int main()
{
		scanf("%d",&n);//读入都建议scanf不建议cin
		for(int i=1;i<=n;i++)
			scanf("%d %d %d %d",&a[i],&b[i],&c[i],&d[i]);
		int cnt1=0,cnt2=0;
   
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				cnt1++;
				sum1[cnt1]=-(a[i]+b[j]); //sum1存-(a[i]+b[j])
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				cnt2++;
				sum2[cnt2]=c[i]+d[j]; //sum2存c[i]+d[j]
			}
		}
    
		sort(sum1+1,sum1+cnt1+1);//排序，注意是加cnt1和cnt2而不是n
		sort(sum2+1,sum2+cnt2+1);
		long long ans=0;
    
		for(int i=1;i<=cnt2;i++)//这里<=cnt2，在cnt2个中找
		{
			ans+=upper_bound(sum1+1,sum1+cnt+1,sum2[i])-lower_bound(sum1+1,sum1+cnt+1,sum2[i]);//upper-lower来找sum2[i]的连续个数，累加给ans
		}
		printf("%lld\n",ans);//快乐输出，ans即Values whose Sum is 0
		return 0;
}
```
~~又调整了一些格式和LaTeX 应该能过叭。~~   
结束。

---

## 作者：Starw (赞：8)

### 思路：

题目让我们求 $A+B+C+D=0$，我们可以把它变为 $A+B=-C-D$，这样我们就可以枚举所有的 $A+B$，把它放入一个映射中，再枚举所有的 $-C-D$，看该映射中有过多少次该值。

### 代码：
```
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
gp_hash_table<int,int>m;//要用pb_ds的map，STL的太慢了
int a[4005],b[4005],c[4005],d[4005];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n,ans(0);
		m.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				m[a[i]+b[j]]++;//枚举A+B
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				ans+=m[-c[i]-d[j]];//统计-C-D之前出现的次数
		printf("%d\n",ans);
		if(T)putchar(10);//坑人的输出
	}
    return 0;//好习惯
}
```


---

## 作者：小闸蟹 (赞：5)

```cpp
#include <iostream>
#include <algorithm>
#include <array>

using ll = long long;

constexpr int MaxN = 4000 + 5;
int n, c;
std::array<int, MaxN> A{ 0 }, B{ 0 }, C{ 0 }, D{ 0 };
std::array<int, MaxN * MaxN> Sums{ 0 }; // 存放A[i]和B[j]两两相加的和

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> n;
        for (int i = 0; i < n; ++i)
        {
            std::cin >> A[i] >> B[i] >> C[i] >> D[i];
        }

        // 这一题的思路十分直白：
        // 就是把每一组(A[i] + B[j])的组合都算出来，
        // 然后存在Sums[]中，
        // 接着对Sums[]排序，
        // 然后寻找每一组(-C[i] - D[j])在Sums[]中出现了多少次，把这些次数都加起来，
        // 相加后的结果即是答案

        c = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                Sums[c++] = A[i] + B[j];    // A[i]和B[j]两两相加
            }
        }
        std::sort(Sums.begin(), Sums.begin() + c); // 排序，为了后面二分方便

        ll cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                // 其实就是在找Sums[]中有多少个连续的(-C[i] - D[j])，然后加起来
                cnt += std::upper_bound(Sums.cbegin(), Sums.cbegin() + c, -C[i] - D[j])
                     - std::lower_bound(Sums.cbegin(), Sums.cbegin() + c, -C[i] - D[j]);
            }
        }

        std::cout << cnt << std::endl;

        if (T)
        {
            std::putchar('\n');
        }
    }

    return 0;
}
```

---

## 作者：封禁用户 (赞：4)

# Ads
个人博客同步：

wordpress版：[点我](https://oldblog.cinema000.xyz/1619.ruby)

hexo版：[点我](https://blog.cinema000.xyz)

想要支持我可以点击wordpress版链接（已加入Google Adsense）

# 分析

最暴力的就是四层循环枚举，但是我们有更快的，枚举$a,b$，把所有$a+b$记录下来放入`map`中，然后枚举$c,d$，查询$-c-d$有多少种方法写成$a+b$。

这样是$O(n^2\log n)$，这个$\log$源自`map`的自动排序，然后大概率不能AC。

但是，在C++11中，STL提供了`unordered_map`，头文件与其同名，操作几乎一样，只是不再以红黑树做底层，而是以hash表为底层，使用自定义类时需要重载`==`操作符。

这样就是$O(n^2)$啦

# 代码

```cpp
#include<cstdio>
#include<cctype>
#include<unordered_map>
typedef long long int64;
const int MAXN = 4000 + 6;
std::unordered_map<int,int> hash;
int A[MAXN],B[MAXN],C[MAXN],D[MAXN];

inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    if (s == t) {
        t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
        if (s == t) return -1;
    }
    return *s++;
}

inline bool read(int &x) {
    static bool iosig;
    static char c;
    for (iosig = false, c = read(); !isdigit(c); c = read()) {
        if (c == '-') iosig = true;
        if (c == -1) return false;
    }
    for (x = 0; isdigit(c); c = read())
        x = (x + (x << 2) << 1) + (c ^ '0');
    if (iosig) x = -x;
    return true;
}

int main(){
    int T,n;int64 ans = 0;read(T);
    while(T--){
        ans = 0;
        read(n);
        for(int i = 0;i < n;i++) read(A[i]),read(B[i]),read(C[i]),read(D[i]);
        for(int i = 0;i < n;i++) for(int j = 0;j < n;j++) hash[A[i] + B[j]]++;
        for(int i = 0;i < n;i++) for(int j = 0;j < n;j++) ans += hash[-C[i] - D[j]];
        printf("%lld\n",ans);
        if(T) puts("");
        hash.clear();
    }
    return 0;
}
```



---

## 作者：Konnyaku_LXZ (赞：3)

这题比较套路，要求四个元素相加等于零，复杂度却要求 $n^2$ 左右，我们可以将他们分成两组考虑： $a,b$ 两个数组分成一组,$c,d$ 两个数组分成一组。

显然，我们可以对每一组暴力计算出所有可能的和，将他们记录下来后排序，得到数组 $x$ 和数组 $y$。

接下来问题转换为：分别从数组 $x,y$ 中取出一个数，求有多少种取法使得取出的两个数相加等于零，即 [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)。

直接用 `upper_bound` 减去 `lower_bound` 即可。

时间复杂度：$O(N^2logN)$，对于9s的时限来说绰绰有余。

输出格式需要特别注意，每两组数据之间有一个空行，最后一组数据后面没有空行。

Code:

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

const int MAXN=4050;
typedef long long LL;

LL N,T,t,a[MAXN],b[MAXN],c[MAXN],d[MAXN],Ans=0;
LL x[MAXN*MAXN],y[MAXN*MAXN],cntx=0,cnty=0;

void Init(){
	Ans=0;cntx=0;cnty=0;//初始化 
	scanf("%lld",&N);
	for(int i=1;i<=N;++i) scanf("%lld%lld%lld%lld",&a[i],&b[i],&c[i],&d[i]);
}

void Solve(){
	for(int i=1;i<=N;++i) for(int j=1;j<=N;++j) x[++cntx]=a[i]+b[j];//暴力枚举所有可能的和 
	for(int i=1;i<=N;++i) for(int j=1;j<=N;++j) y[++cnty]=c[i]+d[j];//同上 
	sort(x+1,x+1+cntx);sort(y+1,y+1+cnty);//排序 
	for(int i=1;i<=cntx;++i) Ans+=upper_bound(y+1,y+1+cnty,-x[i])-lower_bound(y+1,y+1+cnty,-x[i]);//统计个数 
}

void Print(){
	printf("%lld\n",Ans);
	if(t!=T) printf("\n");//注意输出格式 
}

int main()
{
	cin>>T;
	for(t=1;t<=T;++t){
		Init();
		Solve();
		Print();	
	}	
	return 0;
}
```

---

## 作者：yoyiETO (赞：3)

 _这题是怎么评成绿题的?
 
 2020/3/18 AC(在别的网站上测的,洛谷绑定不了)
 
 2020/3/20 初稿
 
 2020/3/21 修改&MarkDown&提交
 
 一篇题解花了4天时间,所以...点个赞?
 
/***** 进入正文 *****/


先介绍一种(n^4)超时算法：
```cpp
//这里只写一下核心代码
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		for(int k=1;k<=n;k++)
			for(int t=1;t<=n;t++)
				if(a[i]+b[i]+c[i]+d[i]==0)
    				ans++;
```
可是4000^4明显>2e9,所以需要优化。

但考试是实在不会也可以~~骗分~~预计30分。

接下来算一下最慢AC时间复杂度:4000^2*log 4000<2e9<4000^3,即O(n^2long n).

含log n的算法一般都是二分查找/二分答案,而二分答案是求最优值的,所以考虑**二分查找**.

介绍三个二分查找经典函数:
```cpp
int quickfind(int a[],int l,int r,int x)
{
	int m;
	while(l<=r)
	{
		m=(l+r)/2;
		if(a[m]==x) break;
		if(x>a[m]) l=m+1;
		else r=m-1;
	}
	if(a[m]==x) return m;
	return -1;
}//二分查找
int lower(long long a[],long long l,long long r,long long x)
{
	while(l<r)
	{
		int mid=(l+r)/2;
		if(a[mid]>=x) r=mid;
		else l=mid+1;
	}
	return l;
}//求上界
int upper(long long a[],long long l,long long r,long long x)
{
	while(l<r)
	{
		int mid=(l+r)/2;
		if(a[mid]>x) r=mid;
		else l=mid+1;
	}
	return l;
}//求下界
```
其中求上界为第一个出现的元素编号,求下界为最后一个出现的元素编号+1,虽然C++系统里有,但我不推荐。

实现方法:存储A,B数组中各选一个的所有累加和,在在里面查找-c[i]-d[i].

**重要:上界减下界==连续个数**
```
for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		ans+=upper(q,1,x,-c[i]-d[j])-lower(q,1,x,-c[i]-d[j])<<' ';
```

最后给出AC代码:

```
#include<bits/stdc++.h>
using namespace std;
long long n,a[4001],b[4001],c[4001],d[4001],q[16000001],x,ans;//sum存放a[i]和b[j]两两相加的和
int lower(long long a[],long long l,long long r,long long x)
{
	while(l<r)
	{
		int mid=(l+r)/2;
		if(a[mid]>=x) r=mid;
		else l=mid+1;
	}
	return l;
}
int upper(long long a[],long long l,long long r,long long x)
{
	while(l<r)
	{
		int mid=(l+r)/2;
		if(a[mid]>x) r=mid;
		else l=mid+1;
	}
	return l;
}
int main()
{
	ios::sync_with_stdio(0);//输入输出优化
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i]>>c[i]>>d[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		q[++x]=a[i]+b[j];
	sort(q+1,q+x+1);//为方便查找,需要排序
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		ans+=upper(q,1,x,-c[i]-d[j])-lower(q,1,x,-c[i]-d[j])<<' ';
	cout<<ans;
	return 0;
}
```


---

## 作者：xixike (赞：1)

~~这道题我们可以用4层循环做，复杂度~~$10^4$（肯定过不了）。

于是我们考虑优化，不难想到利用二分优化，我们可以进行两次二分。

第一次是思想上的，就是把$A+B+C+D=0$，转化为$-（A+B）=C+D$。（这样写是因为我的代码里是这样找的当然也可以写成$A+B=-(C+D)$ ）

第二次是真正的二分，我们先用$sum1$存下来$a_i+b_j$的所有情况，用$sum2$存下来$c_i+d_j$的所有情况。枚举$sum1$中的每一个值，用二分查找在$sum2$中找所有满足和为0的数的个数，求和再输出就可以啦。

**前置知识**：

lower_bound(a+1,a+n+1,b); 意思是在下角标为$1-n$的数组a中找第一个**大于等于**b的**地址**，如果想要去值，需要减去a数组地址，即lower_bound(a+1,a+n+1,b)-a;

upper_bound(a+1,a+n+1,b);找的是第一个**大于**b的数的**地址**，剩下的与lower_bound()都一样。

**注意：上面的两个函数都是二分（$\log{n}$）的复杂度**

~~如果太懒不想写二分的话，可以用这两个函数代替~~（比如我qwq）

这道题要卡输出格式，每一组后面要输出一个空行，最后一组除外

**附代码**
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4010

using namespace std;

int a[N],b[N],c[N],d[N];
int sum1[N*N],sum2[N*N];   //预处理a+b和c+d，因为要二分，所以只能开一维数组
int len1,len2;

int main(){
	int n,t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		memset(sum1,0,sizeof(sum1));
		memset(sum2,0,sizeof(sum2));
		for(int i=1;i<=n;i++)
			scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
		len1=0;
		len2=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				sum1[++len1]=a[i]+b[j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				sum2[++len2]=c[i]+d[j];
		sort(sum1+1,sum1+len1+1);
		sort(sum2+1,sum2+len2+1);
		int ans=0;
		for(int i=1;i<=len1;i++)
			ans+=upper_bound(sum2+1,sum2+len2+1,-sum1[i])-lower_bound(sum2+1,sum2+len2+1,-sum1[i]);    //因为可能有多个符合条件的组合，所以要这样写（自己理解一下）
		printf("%d\n",ans);
		if(t) printf("\n");
	}
	return 0;
} 
```


---

## 作者：JK_LOVER (赞：1)

不多说

先移项  a[]+b[] == -c[]-d[]

就两循环枚举答案加一个logn的查找

自然想到了set，但是set没有计数功能

所以multiset登场

比起set，multiset可以记录数字出现的次数

代码就比较简单了

时间复杂度为O(n^2logn)

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while(ch<'0'||ch>'9') if(ch == '-') f = -1,ch = getchar();
	while(ch>='0'&&ch<='9') x = x*10 + ch - '0',ch = getchar();
	return f*x;
}
multiset<int> s;
int T,n;
int a[17000000],b[17000000],c[17000000],d[17000000];
int main()
{
	T = read();
	while(T--)
	{
		n = read();
		s.clear();
		for(int i = 0;i < 4*n;i++)
		{
			int A = read();
			if(i%4 == 0) a[i/4] = A;
			if(i%4 == 1) b[i/4] = A;
			if(i%4 == 2) c[i/4] = A;
			if(i%4 == 3) d[i/4] = A;
		}
		int ans = 0;
		for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
		{
			s.insert(a[i]+b[j]);
		}
		for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
		{
			if(s.count(-c[i]-d[j])!=0)
			{
				ans += s.count(-c[i]-d[j]);
			}
		}
		cout<<ans<<endl;
	}
}
/*

1
6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45

*/
```


---

