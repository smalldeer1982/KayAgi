# SUMFOUR - 4 values whose sum is 0

## 题目描述

The SUM problem can be formulated as follows: given four lists A, B, C, D of integer values, compute how many quadruplet (a, b, c, d ) belongs to A x B x C x D are such that a + b + c + d = 0 . In the following, we assume that all lists have the same size n

## 样例 #1

### 输入

```
6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45```

### 输出

```
5```

# 题解

## 作者：天王星 (赞：19)

这道题当然可以套四个循环，但是嘿嘿嘿。。。可能连样例都过不了。~~我没试过~~。

因此，根据（~~题目上的标签~~）英明的判断，我们会想到二分搜索。

这里再介绍一下二分，我是蒟蒻，可能解释的不到位，欢迎大佬补充。

二分就像我们小时候玩过的猜数字。如果你心里想一个数字，比如35，让别人来猜，一般都会先猜50（二分）。接着你会告诉他：“猜大了”，那么他就会猜25（二分）。然后你会告诉他：“猜小了”，那么他可能猜（（50+25）/2）。~~懒得算~~。 一直循环，直到猜中为止。
二分也一样，大概像这样
```
int mid;

	while(l<=r)
	{
		mid=(l+r)/2;//取中间的
		if(c[mid]<k) l=mid+1;//在右面找
		else if(c[mid]>k) r=mid-1;//在左面找
		else if(c[mid]==k) break;//找到了
					
	}

```
这段代码意思是在c数组里找k。
当然，二分搜索要求在范围内是单调的（一直增加或一直减少）

这道题当然可以用传统二分，就像上面。但是还有一个问题，就是如果出现下面这种情况

1 3 3 3 5

二分只能找到一个3，再做修改当然可以，但我觉得太过繁琐。这里可以用STL中的lower_bound和upper_bound，找到数组里第一个不小于目标值的指针和第一个大于目标值的指针。

下面我说一下具体思路：
首先将A与B合起来为c，C与D合起来为d（都是数组），（便于二分）。
接着sort排序，（便于二分×2。）
然后在d数组里找c数组中每一个元素的负值（加起来为0）。

下面上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,A[100000],B[100000],C[100000],D[100000],c[100000000],d[100000000];
int t=0,s=0,w;
void search(int k)
{
        int *g=lower_bound(c,c+s,k);//第一个不小于，返回值是一个指针，用法和sort类似。
        int *h=upper_bound(c,c+s,k);//第一个大于
        int q=h-g;//中间的都是相同的值，也要加上
        t+=q;
}
int main()
{	
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>A[i];
        cin>>B[i];
        cin>>C[i];
        cin>>D[i];
        
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            c[s]=A[i]+B[j];
            d[s]=C[i]+D[j];
            s++;
        }
    }
    sort(c,c+s);
    sort(d,d+s);
    for(int i=0;i<s;i++)
    {
        w=-d[i];
        search(w);
    }
    cout<<t;
 
 
} 
```
题解就是这样了，这是我第一遍题解，看在本蒟蒻这么辛苦，你们不点个赞吗？

---

## 作者：Wind_Smiled (赞：3)

## 题意

给定 $4$ 个数列 $A,B,C,D$。要从每个数列中取出 $1$ 个数，使 $4$ 个数的和为 $0$。求出这样的组合个数。当一个数列中有多个相同的数字时，把他们作为不同的数字看待。

输入：第一行：$n$

以下 $n$ 行，每行 $4$ 个数，第 $i$ 行为 $a_i,b_i,c_i,d_i$。

输出：组合数个数。

$n \le 4000 , |a_i ,b_i,c_i,d_i| \le 2^{28}$。

------------
### 介绍
`lower_bound(begin,end,num,greater<type>())` ：从数组的 `begin` 位置到 `end-1` 位置二分查找第一个小于或等于 `num` 的数字，找到返回该数字的地址，不存在则返回 `end`。通过返回的地址减去起始地址 `begin` ,得到找到数字在数组中的下标。

`upper_bound(begin,end,num,greater<type>())` ：从数组的 `begin` 位置到 `end-1` 位置二分查找第一个小于 `num` 的数字，找到返回该数字的地址，不存在则返回 `end`。通过返回的地址减去起始地址 `begin`，得到找到数字在数组中的下标。

由于这两个函数是用二分查找得出的值，所以时间复杂度较低 ~~（比什么四重循环模拟快多了）~~，再利读入优化一下，就可以过了。

与二分查找相同的是，该储存变量必须为单调递增或递减，即有序数列，否则会各种出错。

### 分析
利用函数所得到的下标相减，把我们所要求的值用 $A+B$ 和 $C+D$，暴力枚举其中一者，用函数查找另一种可能的地址下标，如果和为零（即后者等于前者的相反数），则可能的情况就增加。最后输出即可。

------------

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4005],b[4005],c[4005],d[4005],sum1[4005*4005],sum2[4005*4005],n,len1,len2,ans;//二维数组用乘方级的一维数组模拟即可 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			sum1[++len1]=a[i]+b[j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			sum2[++len2]=c[i]+d[j];//每次读入数组位置用++len进行按位模拟
		}
	}
	sort(sum1+1,sum1+len1+1);//归并数组使其有序 
	sort(sum2+1,sum2+len2+1);//上文所提到的函数属于查找类，所以必须面对有序数组 
	for(int i=1;i<=len1;i++){
		ans+=upper_bound(sum2+1,sum2+len2+1,-sum1[i])-lower_bound(sum2+1,sum2+len2+1,-sum1[i]);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：xixike (赞：3)

~~这道题我们可以用4层循环做，复杂度~~$10^4$（肯定过不了）。

于是我们考虑优化，不难想到利用二分优化，我们可以进行两次二分。

第一次是思想上的，就是把$A+B+C+D=0$，转化为$-（A+B）=C+D$。（这样写是因为我的代码里是这样找的当然也可以写成$A+B=-(C+D)$ ）

第二次是真正的二分，我们先用$sum1$存下来$a_i+b_j$的所有情况，用$sum2$存下来$c_i+d_j$的所有情况。枚举$sum1$中的每一个值，用二分查找在$sum2$中找所有满足和为0的数的个数，求和再输出就可以啦。

**前置知识**：

lower_bound(a+1,a+n+1,b); 意思是在下角标为$1-n$的数组a中找第一个**大于等于**b的**地址**，如果想要去值，需要减去a数组地址，即lower_bound(a+1,a+n+1,b)-a;

upper_bound(a+1,a+n+1,b);找的是第一个**大于**b的数的**地址**，剩下的与lower_bound()都一样。

**注意：上面的两个函数都是二分（$\log{n}$）的复杂度**

~~如果太懒不想写二分的话，可以用这两个函数代替~~（比如我qwq）

**附代码**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 4010

using namespace std;

int a[N],b[N],c[N],d[N];
int sum1[N*N],sum2[N*N];         //预处理a+b和c+d，因为要二分，所以只能开一维数组
int len1,len2;

int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
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
		ans+=upper_bound(sum2+1,sum2+len2+1,-sum1[i])-lower_bound(sum2+1,sum2+len2+1,-sum1[i]);   //因为可能有多个符合条件的组合，所以要这样写（自己理解一下）
	printf("%d\n",ans);
	return 0;
} 
```


---

## 作者：Watermatter (赞：2)

## 题意：
从四个序列中取一个数，问其相加有多少种可能。
$$a_i+b_i+c_i+d_i=0$$
即求
$$a_i+b_i=-c_i-d_i $$
至此，我们可以选择ai+bi或-ci-di存入哈希表，并用另外一个值去到哈希表中寻找。只不过本题可以用邻接表来优化哈希表（~~至少我是这么做的~~），注意因为答案可能会有负数，所以取模需要加上mod值再进行取模。


一些注释看代码吧。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
int n,a[4001],b[4001],c[4001],d[4001];
const int mod=7999997;
int ans=0,sum;
struct node{
    int u,v;
}e[4001*4001];
int head[mod],cnt=0;
void add(int a,int b){
    //cout<<a<<" "<<b<<endl;
    e[++cnt].u=head[a];
    head[a]=cnt;
    e[cnt].v=b;
}//像极了链式存图
void find(int x){
    int u=(x%mod+mod)%mod;
    for(int i=head[u];i;i=e[i].u){
        int v=e[i].v;
        if(v==x)ans++;
    }
}//和访问图的节点一样去访问哈希表内的元素
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sum=a[i]+b[j];
            //cout<<sum<<endl;
            add((sum%mod+mod)%mod,sum);//存入哈希表，注意是先存哈希值再存键值
        }
    }
    //cout<<"done"<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int need=-c[i]-d[j];
            find(need);//访问哈希表内的元素
            //cout<<ans<<endl;
        }
    }
    //cout<<ans<<endl;
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：happybob (赞：1)

## 题意

给定 $4$ 个长度均为 $n$ 的序列 $a,b,c,d$。求有多少组 $(i,j,k,p)$ 满足 $a_i + b_j + c_k + d_p = 0$。

## 解法

考虑将这个柿子转化成 $a_i + b_j = -c_k-d_p
$。

把 $a_i+b_j$ 用 $O(n^2)$ 的复杂度暴力算出来，用哈希存一下数量，然后 $O(n^2)$ 枚举 $c$ 和 $d$，把每个 $-c_k-d_p$ 统计答案即可。

注意不要使用 `map/umap`，会被卡，我使用的是 `pbds` 的 `gp_hash_table`。

```cpp
#pragma GCC optimize("-Ofast")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

const int N = 4005;
gp_hash_table<int, int> mp;
int n, a[N], b[N], c[N], d[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			mp[a[i] + b[j]]++;
		}
	}
	int ret = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			ret += mp[-c[i] - d[j]];
		}
	}
	printf("%d\n", ret);
	return 0;
}
```


---

## 作者：NotaKoala (赞：1)

先把C、D中取数字的n^2种方案全部枚举出来，将这些和排好序，这样就可以二分搜索了。

复杂度是O(n^2 log n)

代码如下

```cpp
#include <cstdio>
#include <algorithm>
#include <cctype>

using namespace std;

typedef long long ll;

const int MAX_N = 4000;

int n, T;
int A[MAX_N], B[MAX_N], C[MAX_N], D[MAX_N];

int CD[MAX_N * MAX_N]; // C和D中的数字的组合方法 

void solve() {
	// 枚举从C和D中取出数字的所有方法 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			CD[i * n + j] = C[i] + D[j];
		}
	}
	sort(CD, CD + n * n);
	
	ll res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int cd = -(A[i] + B[j]);
			// 取出C和D中和为cd的部分 
			res += upper_bound(CD, CD + n * n, cd) - lower_bound(CD, CD + n * n, cd);
		}
	}
	
	printf("%lld\n", res);
}

ll read() {
	ll x = 0, s = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') s = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * s;
}

int main() {
	n = read();
	for (int i = 0; i < n; i++) {
		A[i] = read(); B[i] = read(); C[i] = read(); D[i] = read();
	}
	solve();
	return ~~(0-0);
}
```


---

## 作者：黄俊豪 (赞：1)

这道题首先可以想到暴力枚举，用O(n^4）来解决，但这里n太大，所以需要一个跟高效的方法————————折半枚举（双向搜索）来解决


  具体思路：首先2*n^2处理出a和b的所有和和c和d的所有和。
  
  然后可以排序后枚举一个和数组，再在另一个数组中二分查找对应的数值，但要注意一个数值可能有多个相同数值与之对应，解决方法就是二分找到数值后，再在l和r中枚举判断一下就可以了,至于为什么可以从二分什么时候缩区间去想。
  
  
  代码如下：
  ```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,ans;
int num[5][4005],x[16000006],y[16000006];
void find(int,int,int);
int main()
{
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
      for(j=1;j<=4;++j)
        scanf("%d",&num[j][i]);
    int cnt=0; 
    for(i=1;i<=n;++i)
      for(j=1;j<=n;++j)
      {
      	x[++cnt]=num[1][i]+num[2][j];
      	y[cnt]=num[3][i]+num[4][j];
      }
    sort(x+1,x+cnt+1);
    sort(y+1,y+cnt+1);
    for(i=1;i<=cnt;++i)
        find(1,cnt,-y[i]); 
    printf("%d",ans);
    return 0;
}

void find(int l,int r,int num)
{
    int i,j,mid,ci=0;
    bool flag=1,c=1;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(x[mid]<num)  l=mid+1;		  
        if(x[mid]>num)  r=mid-1;
        if(x[mid]==num)
        {
            flag=0;
            break;
        }
    }
    if(!flag)
    {
        for(;l<=r;++l)
        {
            if(x[l]==num)
            {
                ans++;
                c=0;
//				printf("-->>%d %d\n",x[l],num);
            }
            if(c==0&&x[l]!=num)  break;
        }
    }
    return;
}
```

---

## 作者：Unnamed114514 (赞：0)

本题时限很大，但数据也不一定很小，我们一点一点地讨论。

## 方法一：暴力
此处暴力很好打，枚举每个数组的位置即可，时间复杂度 $O(N^4)$，代码不予展示。

## 方法二：二分优化
因为单调性，我们可以使用二分优化，即先对 $d$ 数组进行排序，然后枚举 $a$，$b$，$c$ 中的位置，并二分查找 $d$ 中的值，时间复杂度为 $O(N^3 \log N)$，实际情况不能过。

## 方法三：分组二分
我们继续优化，可以想到把 $4$ 个数组两两分组，这样求出两组的和，然后枚举一个数组，二分另一个数组，时间复杂度为 $O(N^2 \log N^2)$，需要卡常才能过。
### Code:
```
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[4005],b[4005],c[4005],d[4005],t[16000005],tot,ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            t[++tot]=a[i]+b[j];
    sort(t+1,t+tot+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            int u=c[i]+d[j];
            ans+=upper_bound(t+1,t+tot+1,-u)-lower_bound(t+1,t+tot+1,-u);
        }
    printf("%d\n",ans);
    return 0;
}
```

## 方法四：二分查找
其实上面那种方法也会被卡常，虽然复杂度正确，所以我们可以使用二分查找来优化常数。
### AC Code:
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[4005],b[4005],c[4005],d[4005],t[16000005],tot,ans;
void f(int n){
	int l=1,r=tot;
  	bool flag=0;
  	while(l<=r){
      	int mid=(l+r)>>1;
      	if(t[mid]<n)
		  	l=mid+1;
      	else if(t[mid]>n)
		  	r=mid-1;
      	if(t[mid]==n){
          	flag=1;
          	break;
      	}
  	}
  	if(flag)
      	for(;l<=r;l++)
          	ans+=(t[l]==n);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            t[++tot]=a[i]+b[j];
    sort(t+1,t+tot+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            int u=c[i]+d[j];
            f(-u);
        }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Bitter_Tea (赞：0)

# 勘误
由于出现$a_i+b_j=0$的情况，原代码的去重方法存在一定的瑕疵，我们只需要特判一下便可以了，其他无改动。
```
4
0 0 -3 0
0 0 6 5
0 1 -3 5
6 2 5 0 
```

答案应是$0$


------------


基本思路是**二分+数组去重**

我们直接先双重循环把$a_i,b_j$进行相加，用$map$存储值的个数。

对于后面的我们也是只需要双重循环把$c_i,d_j$相加，加上$map$中对应的相反数的个数即可。

~~但是它超时了。~~


我们其实可以排序后自己进行储存值的操作，进行数组去重的同时统计每个数的数量。


然后我们二分去重后的数组即可。

总的时间复杂度大约是$O(n^2logn)$,可以通过本题。

### $Code$
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=4005;
int a[N],b[N],c[N],d[N];
int s[N*N],sn[N*N],sum[N*N];
int n,ans,tot,cnt;
int find(int x)
{
	int l=1,r=cnt;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(sn[mid]>x) r=mid-1;
		if(sn[mid]<x) l=mid+1;
		if(sn[mid]==x) return mid;
	}
	return 0;
}
int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
	for(int i=1; i<=n; i++)
	for(int j=1; j<=n; j++)
	s[++tot]=a[i]+b[j];
	sort(s+1,s+tot+1);
	s[0]=2147483647;			//特判
	for(int i=1; i<=tot; i++)
	{
		if(s[i]!=s[i-1]) sn[++cnt]=s[i],sum[cnt]=1;
		else sum[cnt]++;
	}
	for(int i=1; i<=n; i++)
	for(int j=1; j<=n; j++)
	ans+=sum[find(-c[i]-d[j])];
	printf("%d\n",ans);
	return 0;
}

```



---

## 作者：pengyule (赞：0)

看到 $n=4000$ 的数据和绿题的标签，我们很清楚不可以四层循环暴力枚举。

观察式子 $A_i+B_j+C_k+D_l=0$，得到 $(A_i+B_j)=-(C_k+D_l)$。

我们运用整体思想，把括号中的式子看做一个整体。把所有的 $(A_i+B_j)$  和 $(C_k+D_l)$ 算出来，看看有多少对可以匹配，完成。

1. 两个暴力循环算出所有 $(A_i+B_j)$ 和 $(C_k+D_l)$。
2. 将所有 $(A_i+B_j)$ 和 $(C_k+D_l)$ 分别排序（当然排不排 $(A_i+B_j)$ 无所谓）。
3. 枚举所有 $(A_i+B_j)$，看看有多少个 $(C_k+D_l)$ 与之匹配【这一步要用到二分查找，查找第一个大于等于 $-(A_i+B_j)$ 的 $(C_k+D_l)$。】。
4. 从这个找到的下标开始往后寻找满足 $A_i+B_j+C_k+D_l=0$ 的 $(C_k+D_l)$，一旦不满足就放弃寻找。

完整代码如下。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int A[4005],B[4005],C[4005],D[4005],p[16000010],q[16000010];
ll solve(int n){
    ll ans=0,s=0,t=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) p[++s]=A[i]+B[j];
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) q[++t]=C[i]+D[j];
    sort(p+1,p+s+1);sort(q+1,q+t+1);
    int L,R,mid;
    for(int i=1;i<=s;i++){
        L=0,R=t;
        while(L<R-1){
            mid=(L+R)/2;
            if(q[mid]<0-p[i]) L=mid;
            else R=mid;
        }
        while(R<=t && p[i]+q[R]==0) ans++,R++;
    }
    return ans;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d %d %d %d",&A[i],&B[i],&C[i],&D[i]);
    printf("%lld\n",solve(n));
    return 0;
}
```
谢谢观看，希望对您有帮助。

---

## 作者：gyheva (赞：0)

### 不用二分也可以做

本蒟蒻的第一个题解hiahia...
看到各位大佬都用了二分，但我觉得好像扫一遍也可以？？
废话不多说: )

首先我们把a,b和c,d分成两队，用m和p数组储存他们和，并排序（为了后面扫描的方便性，我取了cd和的相反数：
    
```cpp
	for(i=1;i<=n;i++)
	    for(j=1;j<=n;j++)
	        m[(i-1)*n+j]=a[i]+b[j];
	sort(m+1,m+n*n+1);
	
	for(i=1;i<=n;i++)
	    for(j=1;j<=n;j++)
	        p[(i-1)*n+j]=-(c[i]+d[j]);
	sort(p+1,p+n*n+1);
```
接着就是从两个队列中统计相同数的对数，用pa存数组m扫描到的位置，用pb存数组p扫描到的位置。

我们以数组m为基准，往后扫，当 m[pa+1]==m[pa] 时就往后走，直到扫完那段连续的相同的数字，并用numa累加个数。

接着我们推进数组p，直到p[pb]>=m[pa]。如果等于，我们就继续将pb往后推进，用numb累加出相同的个数，我们将ans加上numa*numb；如果大于，就说明对于这个m[pa]，在数组p中没有相同的数字，我们就把pb--，保证p[pb]始终小于或等于m[pa],最后pa++，继续循环以上。

下面贴出代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
long long i,n,a[5000],b[5000],c[5000],d[5000],j,sum,ans,m[16000001],p[16000001],pa,pb,numa,numb;
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		scanf("%lld%lld%lld%lld",&a[i],&b[i],&c[i],&d[i]);
	}
	
	//预处理：m数组为a,b和的枚举，p数组为c,d和的相反数的枚举，并排好序 
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			m[(i-1)*n+j]=a[i]+b[j];
	sort(m+1,m+n*n+1);
	
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			p[(i-1)*n+j]=-(c[i]+d[j]);
	sort(p+1,p+n*n+1);
	
	//统计答案 
	pa=1,pb=1;
	while(pa<=n*n&&pb<=n*n){
		numa=1;
		while(m[pa]==m[pa+1]&&pa<n*n){
			pa++;
			numa++;
		}
		while(p[pb]<m[pa]&&pb<n*n){
			pb++;
			if(p[pb]>m[pa]){
				pb--;
				break;
			}
		}
		if(p[pb]==m[pa]&&pa<=n*n&&pb<=n*n){
			numb=1;
			while(p[pb]==p[pb+1]&&pb<n*n){
				pb++;
				numb++;
			}
			ans+=numa*numb;
		}
		pa++;
	}
	cout<<ans<<endl;
}
```


---

## 作者：wxwoo (赞：0)

[$$\color{#0e90d2}\huge{\texttt{my blog}}$$](https://wxwoo.github.io/2019/04/23/solution-sp1296/)

******

[原题目链接](https://www.luogu.org/problemnew/show/SP1296)

首先想到$\Theta(n^4)$的暴力枚举，但$n\le 4000$显然不行。

考虑先预处理出c数组和d数组的和，再暴力计算答案。

由于c数组和d数组的和可能会有重复，排序后使用二分来降低时间复杂度

最终时间复杂度$\Theta (n^2\log n)$

代码如下

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=4010;
int n,nn,a[N],b[N],c[N],d[N],sum[N*N],ans=0;
inline void read(int &x)
{
    char ch=getchar();
    int f=1;
    x=0;
    while(!('0'<=ch&&ch<='9'))
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    do
    {
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }while('0'<=ch&&ch<='9');
    x*=f;
}
inline int calc(int x,int y)//降维，将二维转化成一维
{
	return (x-1)*n+y;
}
int main()
{
	read(n);
	nn=n*n;
	for(int i=1;i<=n;++i)
		read(a[i]),read(b[i]),read(c[i]),read(d[i]);
	for(int i=1;i<=n;++i)//预处理出c数组和d数组的和
		for(int j=1;j<=n;++j)
		{
			sum[calc(i,j)]=c[i]+d[j];
		}
	sort(sum+1,sum+nn+1);//排序，因为二分需要单调性
	for(int i=1;i<=n;++i)//暴力枚举a数组和b数组的和
	{
		for(int j=1;j<=n;++j)
		{
			ans+=upper_bound(sum+1,sum+nn+1,-a[i]-b[j])-lower_bound(sum+1,sum+nn+1,-a[i]-b[j]);//二分计算有多少个重复答案
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

