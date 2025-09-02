# Ilya and Matrix

## 题目描述

Ilya is a very good-natured lion. He likes maths. Of all mathematical objects, his favourite one is matrices. Now he's faced a complicated matrix problem he needs to solve.

He's got a square $ 2^{n}×2^{n} $ -sized matrix and $ 4^{n} $ integers. You need to arrange all these numbers in the matrix (put each number in a single individual cell) so that the beauty of the resulting matrix with numbers is maximum.

The beauty of a $ 2^{n}×2^{n} $ -sized matrix is an integer, obtained by the following algorithm:

1. Find the maximum element in the matrix. Let's denote it as $ m $ .
2. If $ n=0 $ , then the beauty of the matrix equals $ m $ . Otherwise, a matrix can be split into 4 non-intersecting $ 2^{n-1}×2^{n-1} $ -sized submatrices, then the beauty of the matrix equals the sum of number $ m $ and other four beauties of the described submatrices.

As you can see, the algorithm is recursive.

Help Ilya, solve the problem and print the resulting maximum beauty of the matrix.

## 说明/提示

Consider the second sample. You need to arrange the numbers in the matrix as follows:

`<br></br>1 2<br></br>3 4<br></br>`Then the beauty of the matrix will equal: 4 + 1 + 2 + 3 + 4 = 14.

## 样例 #1

### 输入

```
1
13
```

### 输出

```
13
```

## 样例 #2

### 输入

```
4
1 2 3 4
```

### 输出

```
14
```

# 题解

## 作者：封禁用户 (赞：2)

## 思路
我们在输入 $n$ 个数后从大到小排序，然后在 $4^n×4^n$ 中找到成立的累加即可。

## CODE
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int a[10000000];

bool cmp(int x,int y)
{
    return x>y;
}

int n;
int ans;

signed main()
{
    scanf("%lld",&n);
    
    for(int i=1;i<=n;i++)
	{
        scanf("%lld",&a[i]);
    }
    
    sort(a+1,a+n+1,cmp);
    
    for(int i=0;pow(4,i)<=n+1;i++)
	{
        for(int j=1;j<=pow(4,i);j++)
        {
            ans+=a[j];
        }
    }
    
    printf("%I64d\n",ans);
    
    return 0;
}
```


---

## 作者：_txb_ (赞：1)

### 题目：[Ilya and Matrix](https://www.luogu.com.cn/problem/CF313C)

## 思路
我们首先把数组从大到小来排序，其他大佬的图已经画的很详细了，然后我们需要两个循环来把符合的数给加到美丽值里，每一次需要循环 $4$ 的 $n$ 次方。

### [本题需要比较快的读入](https://www.luogu.com.cn/record/140576770) && [十年 oi 一场空，不开 long long 见祖宗](https://www.luogu.com.cn/record/140577462)

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2000005],ans;
bool cmp(int x,int y)
{
	return x>y;//从大到小排序 
}
signed main()//快读 
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);//快读 
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1,cmp);//从大到小排序 
	for(int i=0;pow(4,i)<=n+1;i++)//循环4的n次方 
		for(int j=1;j<=pow(4,i);j++)//循环4的n次方 
			ans+=a[j];
	cout<<ans;
	return 0;
}
```


---

## 作者：very_easy (赞：1)

# 思路
原来我一开始代入的不对，这题其实是一道画图题。
![](https://cdn.luogu.com.cn/upload/image_hosting/at1061j2.png)
图有点丑，请见谅。

显然图中的每一个**已被选中的值**一定会被再选中，也就是说要优先选较大的数，这样可以是使得大数累加的越来越大，但每一次都要 $O(n)$ 时间复杂度来找最大值就太麻烦了，不如先将数组从大到小排序一下。

# AC Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
long long n,a[N],ans;//注意要开long long 
int ksm(int a,int b){//快速幂提高效率 
	if(b==0){
		return 1;
	}
	int t=ksm(a,b/2);
	if(b&1){
		return t*t*a;
	}
	else{
		return t*t;
	}
}
bool cmp(int x,int y){
	return x>y;//从大到小排序 
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	for(int i=0;ksm(4,i)<=n+1;i++){
		for(int j=1;j<=ksm(4,i);j++){
			ans+=a[j];
		}
	}
	cout<<ans;
}
```

---

## 作者：DLDZD (赞：1)

## 思路：
  输入 n 个数后从大到小排序（定义 cmp），最后在 $4^n\times 4^n$ 中找成立的累计，最后以 printf 输出。

$pow(x,y)$：$x^y$。
# code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2000005];
bool cmp(int x,int y){
    return x>y;
}//从大到小排序
long long pow(int a,int b){
	int ans=1;
	for(int i=1;i<=b;i++) ans*=a;
	return ans;
}//n的x次方
int main(){
    int n;
    scanf("%d",&n);	//必须，不然TLE
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);//输入
    }
    sort(a+1,a+n+1,cmp);//排序
    long long ans=0;//最后答案
    for(int i=0;pow(4,i)<=n+1;i++){
        for(int j=1;j<=pow(4,i);j++)
            ans+=a[j];
    }
    printf("%I64d\n",ans);//题目说了"%I64d"输出
    return 0;
}
```



---

## 作者：ridewind2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF313C)

## 思路

 ![](https://cdn.luogu.com.cn/upload/image_hosting/a485wuuy.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这是一道画图题，美丽值就是涂了颜色的值。将 $n$ 个数从大到小排序，然后在 $4_{}^{n} \times 4_{}^{n}$ 的矩阵中依次累加。

每次循环可以直接用快速幂算出 $4_{}^{n}$ 的值：

```cpp

typedef long long ll;
ll qm(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1)res*=a;
		a*=a;
		b>>=1;
	}
	return res;
}

```

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//不开 long long 见祖宗 
ll a[2000010];
ll qm(ll a,ll b){//快速幂 
	ll res=1;
	while(b){
		if(b&1)res*=a;
		a*=a;
		b>>=1;
	}
	return res;
}
int main(){
	ll n,ans=0;
	cin>>n;
	for(ll i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,greater<ll>());//排序 
	for(ll i=0;pow(4,i)<=n+1;i++){
		for(ll j=1;j<=pow(4,i);j++){
			ans+=a[j];
		}
	}
	cout<<ans;//输出答案 
	return 0;
}
```

---

## 作者：czh___ (赞：0)

### 题目大意：

一个 $4^n$ 一个矩形，让你将这些数都放在每一个格子中。定义一个记矩阵的值是这个矩阵中最大价值 $+$ 一分为四的四个小矩阵的价值。很显然这是一个递归的过程。问最大价值。

### 思路：
我们只要规划出每个数字将会作为矩阵中最大值的次数即可。很显然，最大值会出现 $n+1$ 次，然后接下来次大值会出现 $n$ 次，次次大值也会出现 $n$ 次，次次次大值也会出现 $n$ 次，次次次次大值会出现 $n-1$ 次。依次类推我们可以得到一个规律，统计和即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define AC return 0
using namespace std;
int *a,n;
signed main(){
    while(~scanf("%lld",&n)){
    	a=new int[n+1];
    	memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
        stable_sort(a+1,a+n+1);
        reverse(a+1,a+1+n);
        int ans=0,now=0;
        while(1+1==2){
            int temp=pow(4,now);
            if(temp>n)
				break;
            else
                for(int i=1;i<=temp;i++)
                    ans+=a[i];
            now++;
        }
        printf("%lld\n",ans);
    }
    AC;
}
```


[改编于](https://blog.csdn.net/mengxiang000000/article/details/73693367?ops_request_misc=%257B%2522request%255Fid%2522%253A%252232D18171-1746-4432-B915-BE235B800174%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=32D18171-1746-4432-B915-BE235B800174&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-6-73693367-null-null.142^v100^pc_search_result_base5&utm_term=Ilya%20and%20Matrix&spm=1018.2226.3001.4187)

---

## 作者：drah_yrev (赞：0)

## 思路

如图：（丑的要死）

![](https://cdn.luogu.com.cn/upload/image_hosting/s0ijrg9a.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

可以发现，美丽值就是

矩阵最大值 $+$ 子矩阵最大值 $+$ 子子矩阵最大值 $+$子子子矩阵最大值 $+\ldots$

输入 $n$ 个数，先从大到小排序。

在循环 $4^n$（分成四份）中，在再循环 $4^n$ 次，每次都加上最大值（排序后）。

在 $4^n \times 4^n$ 找出成立的累加之和，按题目输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int a[2000005],ans,n;//要开long long
bool cmp(int x,int y){//
    return x>y;
}
int main(){
    ios::sync_with_stdio(false);//不用超时
	cin.tie(0);
	cout.tie(0);
	cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];//输入
    sort(a+1,a+n+1,cmp);
    for(int i=0;pow(4,i)<=n+1;i++)//分成四份
    	for(int j=1;j<=pow(4,i);j++)
    		ans+=a[j];
    printf("%I64d\n",ans);//按题目要求输出
    return 0;
}
```


---

## 作者：linxuanrui (赞：0)

### 思路

我们先来找一下“美丽值”到底是什么。

![](https://cdn.luogu.com.cn/upload/image_hosting/hdf3dn0t.png)

我们发现，“美丽值”其实就是涂了颜色的值。

其中，红色为整个矩阵的最大值，因此当递归下去的时候它依旧是部分矩阵最大值。

因此，我们可以考虑贪心。

因为红色从始至终都会出现，因此它得是数组中的最大值，这样“美丽值”才会最大。

同理，绿色出现了两次，因此它应该是次大值。其他以此类推。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long//本题要开 long long
using namespace std;
int n,a[2000001],ans;
int qpow(int a,int b){//快速幂
	int ans = 1;
	while(b){
		if(b & 1)ans = ans * a;
		a = a * a,b >>= 1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)cin >> a[i];
	sort(a + 1,a + n + 1,greater<int>());//将数组从大到小排序
	for(int i = 0;qpow(4,i) <= n + 1;i++){
		for(int j = 1;j <= qpow(4,i);j++){
			ans += a[j];//贪心
		}
	}
	cout << ans;
}
```

---

## 作者：yingkeqian9217 (赞：0)

## 题目大意

给一个 $m\times m$ 的矩阵 $a$，$m$ 为 $2^i$（$i\in Z$）,设它的美丽值为矩阵最大元素值加四个 $\frac m 2\times \frac m 2$ 的矩阵的美丽值之和（无法分拆则结束递归），给定 $m\times m$ 的值以及每个元素的值，求能取到的最大美丽值。

## 分析

可以发现，所谓的“美丽值”就是大矩阵的最大值+其副矩阵的最大值之和+其副副矩阵最大值之和+……简单来说，就是 $i$ 个“最大值”之和。

![](https://cdn.luogu.com.cn/upload/image_hosting/jy1kpk2p.png)

显然，前一次选中的值，下一次还会被选，所以越前面的值所占的权值就越高。而想要取到最大值，权值高的就要选较大的值，权值一样无所谓。对于每一次，最好的方法就是取最大的前几个，而因为取的值的数量在递增，所以前面取的后面必定也能取到，恰好满足条件。

所以，每一次都要取到最大，所以只要把数组排序再统计就好了QwQ。

## Code
```
#include<bits/stdc++.h>
#define int long long//十年OI一场空，不开long long见祖宗
using namespace std;
const int maxn=10000001;
int n,ans,a[maxn];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1,greater<int>());//从大到小排列，不会可以用cmp
	for(int i=0;pow(4,i)<=n+1;i++)//枚举每一次累加
	 for(int j=1;j<=pow(4,i);j++)//直接pow不香吗qwq
	  ans+=a[j];
	printf("%lld\n",ans);
	return 0;//优雅的结束
}

```
画图不易，给个赞吧！

---

