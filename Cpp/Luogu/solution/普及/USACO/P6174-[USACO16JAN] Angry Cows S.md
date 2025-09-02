# [USACO16JAN] Angry Cows S

## 题目描述

Bessie 设计了一款新游戏：*Angry Cows*。在这个游戏中，玩家发射奶牛，每头奶牛落地时引爆一定范围内的干草。游戏的目标是使用一组奶牛引爆所有干草。

$N$ 捆干草排列在数轴上的不同位置。第 $i$ 捆干草的的位置为 $x_i$。如果一个威力为 $R$ 的奶牛在 $x$ 位置落地，她将引爆 $[x-R,x+R]$ 范围内的所有干草。

你现在可以发射 $K$ 头奶牛，每头奶牛的威力都是 $R$，现在你需要确定 $R$ 的最小值，使得用 $K$ 头奶牛可以引爆所有干草。

## 样例 #1

### 输入

```
7 2
20
25
18
8
10
3
1```

### 输出

```
5```

# 题解

## 作者：guoxinyugz (赞：10)

~~第一个AC祭。~~

直接求R的最小值很困难，但是如果已知R，能否引爆所有干草就容易求出。

那么，我们就在答案的可能范围内**二分答案**，将答案区间不断缩小最终得出结果。

具体地讲，如果目前确定答案在区间L到R内，就取L和R的平均值mid。

如果爆炸半径等于mid能炸完所有干草，显然答案就在区间L到mid内，令R等于mid。

否则，答案就在区间mid+1到R内，令L=mid+1。

不断进行以上操作直到L=R，就可以输出答案了。

以下是代码。

```
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,a[50003];
bool che(int x)//用于判断某个爆炸半径是否可行。
{
	int s=0,p=-2000000000;//s表示已经用了几个奶牛，p表示炸到哪了。
	for(int i=1;i<=n;i++)
	{
		if(p+x<a[i])
		{
			s++;
			p=a[i]+x;
		}
		if(s>k)
			return 0;
	}
	return 1;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);//先将位置从小到大排序。
	int l=1,r=a[n],mid;//答案一定在区间1到a[n]内。
	while(l<r)
	{
		mid=(l+r)/2;
		if(che(mid))//如果爆炸半径为mid可行，答案在区间l到mid内。
			r=mid;
		else//否则答案在区间mid+1到r内。
			l=mid+1;
	}
	printf("%d",l);
	return 0;
}
```
其实，让你求最小或最大的值，且该值要满足某个条件时很可能要用二分答案。

最后给大家几道较简单的用二分答案的题：[P2678 跳石头](https://www.luogu.com.cn/problem/P2678)和[P2759 奇怪的函数](https://www.luogu.com.cn/problem/P2759)。

---

## 作者：CCCloud (赞：4)

### 暴力枚举  

------------
我的思路跟其他题解不太一样，他们是枚举**需要几个火药**，而我是枚举**覆盖掉几个稻草**;  
**题意**：有$n$个稻草在不同的位置，还有$k$个火药，每条火药炸的范围为$2*r$，求$r$的最小值；  
**数据范围**：$(1\leqslant n\leqslant5\times10^4,1\leqslant k\leqslant 10)$；  
看到这个数据范围**并不大**，所以我们就可以用**暴力枚举求解**；    
1、将$i$从1~n循环，表示**当前$r$的取值**；  
2、将$j$从1~k循环，表示**第$k$条线段**；  
3、循环**模拟覆盖的过程**，得到**最多覆盖掉的点$t$**；  
4、如果$t==n$，那么我们就**输出**当前的i的值，并且**结束程序**；  
5、如果$t!=n$，那么就**回到第1步，继续循环**；  

------------

细节：如果你将$t$**直接累加并判断**的话，那么很可能会**RE**，于是就要这样：
```cpp
	while(a[t+1]<=x&&t+1<=n)  t++;
```
**确保t不会越界**；

------------
#### 代码展示如下：
```cpp
#include <cstdio>
#include <algorithm>//sort函数所在头文件
using namespace std;

int n, k, x, r, t, a[500005];//定义变量

int main(void)
{
    scanf("%d%d", &n, &k);//读入
    for(int i=1; i<=n ;i++)
        scanf("%d", &a[i]);//读入每个的值
        
    sort(a+1, a+1+n);//sort排序，码量少又方便
    for(int i=1; i<=n; i++)
    {
        r=2*i;//一个炸弹覆盖的长度就是2*i
        x=a[1];//开始为最小的那个点的坐标
        t=0;//初始化
        for(int j=1; j<=k; j++)
        {
            x+=r;//每次加上炸弹能炸到的长度
            while(a[t+1]<=x&&t+1<=n)  t++;//累加t
            x=a[t+1];
            //如果while循环终止，那么先前的x一定小于a[t+1]，那么就直接设x为a[t+1]
            if(t==n)//如果t==n，也就是全部覆盖到
            {
                printf("%d\n", i);//输出答案
                return 0;//终止
            }
        }
    }
    return 0;
}
```


---

## 作者：cyrxdzj (赞：3)

### 一、思路

首先，$R$ 越大，干草就越有可能被引爆完。

显然，这需要使用二分算法。

$R$ 的最小值为 $0$（每个奶牛炸一堆干草），最大值为 $10^9\div2$（全场干草一个奶牛下来就被炸完了）。

二分算法的精髓在于 `check` 函数，用于检查这个答案是否符合题意。那么，这道题的 `check` 应该怎么做呢？

### 二、检查函数

首先，干草堆的位置必须有序。这不难，一个 `sort` 函数下来就搞定，数据范围也不大。

我们可以定义一个变量 `position`，代表当前已被发射的奶牛，最远可以炸到那个点上。初始值为 `-0x7fffffff`，这是 `int` 型的最小值。

然后，顺序遍历所有干草堆。如果 `position` 加上当前假设的距离小于这个干草堆的位置，就说明这个干草堆还没被炸到，因此要再多一个奶牛，并将 `position` 更新为当前干草堆的位置加上当前假设的距离。

如果使用的奶牛数量大于 $K$，就说明这个距离太小，返回 `false`。

到了最后，如果使用的奶牛数量不大于 $K$，就说明这个距离足够了，返回 `true`。

### 三、坑点

记得排序！

### 四、完整代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k;
int grass[50005];
int left,right=1000000000;
int middle;
int ans;
bool check(int x)//检查函数。
{
	int use_cow=0,position=-0x7fffffff;
	for(int i=1;i<=n;i++)
	{
		if(position+x<grass[i])
		{
			use_cow++;
			position=grass[i]+x;
			if(use_cow>k)
			{
				return false;
			}
		}
	}
	return true;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&grass[i]);
	}
	sort(grass+1,grass+1+n);//记得排序！ 
	while(left<=right)//二分。
	{
		middle=(left+right)>>1;
		if(check(middle))
		{
			right=middle-1;
			ans=middle;
		}
		else
		{
			left=middle+1;
		}
	}
	printf("%d\n",ans);
	return 0;//完结撒花！
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：miao5 (赞：3)

二分答案的裸题。

二分答案求 $R$ 找到最小爆炸半径即可。

一些细节在代码里。

code:

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n,k,a[50003];
bool check(int x){//查询函数 
	int s=0,p=-0x7fffffff;
	for(int i=1;i<=n;i++){
		if(p+x<a[i]){
			s++;
			p=a[i]+x;
		}
		if(s>k) return 0;//判断是否引爆所有甘草 
	}
	return 1;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);//输入，排序 
	int l=1,r=a[n],mid;
	while(l<r){
		mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}//二分答案 
	cout<<l;
	return 0;
}
```


---

## 作者：Velix (赞：3)

一道较为简单的二分答案题。

将R作为二分的数去检查，然后进行枚举。

可以想到，如果这个数不在上一个炸弹的覆盖范围，那它一定在新炸弹的最左端。程序也就呼之欲出了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50001],b,c,d,l,r=1000000001,m;
bool check(int x)
{
	int y=0,z=0;
	for(int i=1;i<=b;i++)
		if(z<a[i])y++,z=a[i]+x*2;
	return y<=c;
}
int main()
{
	cin>>b>>c;
	for(int i=1;i<=b;i++)scanf("%d",&a[i]);
	sort(a+1,a+b+1);
	while(l<=r)
	{
		m=l+r>>1;
		if(check(m))r=m-1,d=m;
		else l=m+1;
	}
	cout<<d;
}
```


---

## 作者：Zenith_Yeh (赞：2)

看到要求R的最小值，而 $R$ 又满足以下条件：

- 找到一个 $R_2(R_2<R)$,若 $ R_2$ 可以满足条件，则 $R$ 也一定可以。
- 找到一个 $R_2(R_2>R)$,若 $ R_2$ 可以不满足条件，则 $R$ 也一定不可以。

知道这两个特点，发现算法就是二分答案。

我们二分 $R$，再用贪心求以当前的 $R$ 炸毁所有东西的最小的 $K_2$，再判断一下是否 $K_2≤K$ 即可。

**上菜：**
```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//优美的快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
int n,k,a[50005],l=0,r=500000000;//二分范围为0～500000000，因为0≤x≤1e9,所以最大为5e8。
inline bool check(int R)
{	int res=0,last=1;
	while(last!=n+1)//贪心
	{	res++;
		int r=a[last]+R*2;
		for(register int i=last;i<=n;++i)
			if(a[i]<=r)last=i+1;
	}
    return res<=k;
}
int main()
{	n=read(),k=read();
	for(register int i=1;i<=n;++i)a[i]=read();
	sort(a+1,a+n+1);//排序
	while(l<r)
	{	int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%d",l);
	return 0;
}
```


---

## 作者：羚羊WANG (赞：1)

经过大家的读题，显然我们可以发现

答案是存在单调性的

所以，我们可以考虑二分答案的做法

我们一开始把$l,r$两个点设为0与一个极大值

每次我们把区间折半

判断区间中点是否满足题意

如果满足，就是在有区间；否则就是在左区间

直接上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
int k;
int a[50010];
int l,r;
inline bool check(int x){
	int sum=0;
	int h=0;
	for(register int i=1;i<=n;++i)
		{
			if(a[i]>h)
				{
					h=x+x+a[i];
					sum++;
				}
		}
	if(sum>k)
		return false;
	return true;
}
signed main(){
	n=read();
	k=read();
	for(register int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	l=1;
	r=5000000;
	while(l<r)
		{
			int mid=(l+r)/2;
			if(check(mid))
				r=mid;
			else
				l=mid+1;
		}
	write(l);
	return 0;
}
```


---

## 作者：tribool4_in (赞：1)

首先看题：

> 现在你需要确定 $R$ 的最小值，使得用 $K$ 头奶牛可以引爆所有干草

感觉像是二分答案？

再仔细分析可知：

1. 若 $R$ 可以满足，则任意一个 $\ge R$ 的值也满足；
2. 若 $R$ 不满足，则任意一个 $\ge R$ 的值也不满足。

说白了就是**满足单调性**！**二分答案**！

然后就是 ```check``` 函数了。

考虑贪心，对于第 $i$ 个干草，如果暂时无法被引爆，则在 $a[i] + r$ 处发射一个爆炸奶牛，最终再判断一下即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, k, a[50005], l = 0, r = 5e8;
bool check(int R) {
	int cnt = 0, last = 1;
	while (last < n + 1) {
		cnt++;
		int right = a[last] + R * 2;
		for(int i = last; i <= n; ++i)
			if (a[i] <= right) last = i + 1;
	}
	return cnt <= k;
}
int erfen() {
	int l = 0, r = 5e8;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	return l;
}
int main() {
	scanf("%d%d", &n, &k);
	for(register int i = 1; i <= n; i++) scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	printf("%d\n", erfen());
	return 0;
}
```


---

## 作者：SingularPoint (赞：1)

### 题目大意
给出直线上的若干点和炸弹数量，求一个炸弹能够影响到的**最小半径**，使得在规定的数量内炸弹可以覆盖所有点。

### 分析
一读题就是二分答案啊（

------
#### 二分答案
适用范围：求能使的题目所述条件得到满足的答案的**最值**。

前提条件：答案在区间内有**单调性**。

实现方式：先确定答案所在的数据范围，每次**取区间的中点数值**，并询问这个值能否用做答案，以此为基础逐步缩小答案的范围，最后使得区间的左右边界重合或左右交换，此时的边界数值就是所求的答案啦~

二分答案在适用的条件下只用几十次询问就可以得到答案，经常与DP等算法放在一起考察，能够对题目进行很好的简化，是一种常用的算法思想。

------
本题就是一道典型的二分答案题，我们**每次二分炸弹的爆炸半径**，其最小为一，最大就是当前所有点坐标的最值之差除以二（然鹅本人代码里用的是最大点坐标QAQ）

判断是否符合条件时直接模拟就可以啦~

我在这里用了贪心的思想，把炸弹认为是一个区间的话，这个炸弹的最大效用一定是在它以当前最近的点的作为区间起点的时候，以此来进行对答案可行性的判断。

分析结束就上代码罢
### Code
```cpp
#include<bits/stdc++.h>
#define ull uneigned long long
#define ll long long
#define db double
using namespace std;
const int M=50005;
int n,m;
int a[M];
bool check(int x)
{
	int len=a[1]+x*2,cnt=1;
	for(int i=1;i<=n;i++){
		if(a[i]<=len) continue;
		else{
			len=a[i]+2*x;
			cnt++;
		}
		if(cnt>m) return 0;//当此时用到的炸弹数量大于题目条件时return 
	}
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	int l=1,r=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);//将点的位置从小到大排序 
	r=a[n];
	while(l<=r){//二分答案 
		int mid=(l+r)>>1;
		if(check(mid))
			r=mid-1;
		else l=mid+1;
	}
	printf("%d",l);//要输出左边界，输出右边界会导致错误的（原因可以自己手动模拟一下） 
    return 0;
}
```
完结撒fa~

---

## 作者：georgehe (赞：1)

# 题目的核心：二分答案

前面的题解二分答案已经讲得很清楚了，如果不明白二分答案可以看前面大佬的分析。

本苣蒻调判断函数调了1个小时没调出来:(

模拟一直写不出来，转念一想排序后用 upper_bound 函数每次查找n个草堆中第一个目前草堆无法覆盖的草堆然后转移过去。如此转移k次，如果草堆位置大于 n 那么必定可以全部覆盖，否则无法覆盖。

迫不得已用了 upper_bound ~~考试可能就挂了~~~~。~~

## upper_bound

简单介绍一下 upper_bound:

upper_bound(a+1,a+n+1,x);

上面这一行代码可以返回a数组下标 [1]-[n] 中第一个大于x的地址。

C++ 中数组名也相当于数组第一个值的地址。

因此，如果我们用 upper_bound(a+1,a+n+1,x)-a; 那么可以返回一个 int 值代表a数组 a[1]-a[n] 中第一个大于 x 的下标值。

[如果实在不懂点这里阅读，里面有 C++ 的 upper_bound 范例程序。](http://www.cplusplus.com/reference/algorithm/upper_bound/)

## 判断函数

判断函数核心覆盖判断：

```cpp
for(int i=1;i<=k;i++)//k个覆盖范围
  pos=upper_bound(hay+pos,hay+n+1,hay[pos]+2*r)-hay;
```

pos 初始值为1。r 是目前牛的爆炸半径。 hay 数组存每个干草堆的位置，并且已经升序排序。

我的判断函数会执行 k 次，每次用 upper_bound 函数找到第一个大于 hay(pos) 的位置，并把它赋值给 pos 。这样相当于跳跃 k 次，每次从 hay(pos) 的位置用 upper_bound 函数找到 hay 数组中第一个大于 hay(pos)+2*r 的位置，这个位置是我们如果想要用一头牛覆盖 hay (pos) 时无法覆盖的干草堆，因此也是下一次跳跃的起点。 

判断退出：

```cpp
if(pos>n)
      return true;
```

如果目前跳跃的干草堆已经超过了 n 个干草堆，换言之，我上次跳跃时已经跳过了 hay(n) 的位置，那么 k 头牛的爆炸半径 r 可以覆盖 n 个干草堆。

## 上代码

```cpp
#include <cstdio>
#include <algorithm>//upper_bound头文件
#include <iostream>
using namespace std;

int n,k,hay[50010];

bool check(int r)//判断函数，如果k头奶牛在爆炸半径r的情况下能够覆盖所有n个干草堆，return true,否则return false
{
  int pos=1;//从1号干草堆开始计算
  for(int i=1;i<=k;i++)//k个覆盖范围
  {
    pos=upper_bound(hay+pos,hay+n+1,hay[pos]+2*r)-hay;//每个覆盖范围是当前pos到2*r的位置，那么第一个大于hay[pos]+2*r的位置是下一次覆盖需要覆盖的第一个干草堆
    if(pos>n)//如果已经覆盖完第n个干草堆，r的半径成立
      return true;//返回true，使半径减少
  }
  return false;//如果经过k次覆盖pos<=n，那么代表没有完全覆盖，返回false，使半径增加
}

int main()
{
  cin>>n>>k;//n个干草堆，引爆k次奶牛
  for(int i=1;i<=n;i++)
    cin>>hay[i];//存每个干草堆的位置
  sort(hay+1,hay+n+1);//sort默认升序排序
  int l=1,r=hay[n],mid;//最小每头奶牛需要引爆半径1，最大每头奶牛需要引爆半径hay[n]
  while(l<=r)//二分模版
  {
    mid=(l+r)/2;
    if(check(mid))
      r=mid-1;
    else
      l=mid+1;
  }
  cout<<l<<endl;//小于等于r的check都是false，大于等于l的check都是true，所以输出l
  return 0;
}

```



---

## 作者：hensier (赞：1)

~~这道题的题号勾起了本蒟蒻无限的回忆。~~

本题可以使用**二分答案**。在本题中，其核心就是判断威力是否能够满足题意，然后根据是否满足来二分。具体可以写一个$\text{check}$函数来实现。


当然，这题也可以$\mathcal O(n^2)$暴力踩点$\text{AC}$。具体的暴力代码就不贴了。

详细来看二分答案的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l,r,a[50001];
int read()//用快读简单优化一下
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
bool check(int x)
{
    int cur=0,cnt=0;//cur表示当前的坐标，cnt表示需要使用的奶牛数量
    for(int i=1;i<=n;i++)
    {
        if(cur>=a[i])continue;//如果坐标超出了发射的范围，则不需要再增加新的奶牛
        cnt++;//需要的奶牛数量加1
        cur=a[i]+(x<<1);//把坐标重新赋值，加上威力的2倍即可
    }
    return cnt<=k;//如果需要的奶牛个数小于等于k，说明威力为x的时候是满足题意的，否则不满足。
}
int main()
{
    n=read();
    k=read();
    for(int i=1;i<=n;i++)a[i]=read();
    sort(a+1,a+n+1);//达成二分的前提条件——数组单调不递减
    l=a[1];//初始左边界为最靠左的奶牛
    r=a[n];//初始右边界为最靠右的奶牛
    while(l<=r)//开始二分
    {
        int mid=(l+r)>>1;//首先确定mid
        if(check(mid))r=mid-1;//如果mid（即威力）满足条件就执行（因为找到满足条件的之后，就要尽可能找到更小的，所以右边界向左逼近1）
        else l=mid+1;//否则左边界向右（因为找不到就要增大威力，设法找到答案）
    }
    printf("%d",l);
    return 0;
}
```

---

