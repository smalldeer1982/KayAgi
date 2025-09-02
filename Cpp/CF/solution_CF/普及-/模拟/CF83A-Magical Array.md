# Magical Array

## 题目描述

Valery is very interested in magic. Magic attracts him so much that he sees it everywhere. He explains any strange and weird phenomenon through intervention of supernatural forces. But who would have thought that even in a regular array of numbers Valera manages to see something beautiful and magical.

Valera absolutely accidentally got a piece of ancient parchment on which an array of numbers was written. He immediately thought that the numbers in this array were not random. As a result of extensive research Valera worked out a wonderful property that a magical array should have: an array is defined as magic if its minimum and maximum coincide.

He decided to share this outstanding discovery with you, but he asks you for help in return. Despite the tremendous intelligence and wit, Valera counts very badly and so you will have to complete his work. All you have to do is count the number of magical subarrays of the original array of numbers, written on the parchment. Subarray is defined as non-empty sequence of consecutive elements.

## 说明/提示

Notes to sample tests:

Magical subarrays are shown with pairs of indices \[a;b\] of the beginning and the end.

In the first sample: \[1;1\], \[2;2\], \[3;3\], \[4;4\], \[2;3\].

In the second sample: \[1;1\], \[2;2\], \[3;3\], \[4;4\], \[5;5\], \[1;2\], \[2;3\], \[1;3\].

## 样例 #1

### 输入

```
4
2 1 1 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
-2 -2 -2 0 1
```

### 输出

```
8
```

# 题解

## 作者：zhangyuhao9 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF83A)


---

**题目大意**

先输入一个数 $n$，接下来一行输入 $n$ 个数，第二行输入一串数字，输出找到的所有的连续并且相同的一串数字，即从第二行中选出 $m$ 组数组，使得每组数组中的所有数都相等。

---

**题目分析**

根据题意，我们只需要找到一串连续并且相同的数字。

而n个连续的相同的数字里包含 $n \times (n+1) \div 2$ 个.

这样就可以直接用 $\Theta(n)$ ~~来水过这个题~~。

---

**代码实现**

剩下具体的地方看注释吧，~~我自认为写的很详细了~~。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[100001],ans=0;
int main(){
    long long n;
    cin>>n;    //输入第一行的数
    long long num=0;   //将计数初始化为0
    for(int i=1;i<=n;i++){
        cin>>a[i];       //将数组输入
        if(a[i]!=a[i-1]){   //如果相邻两数不相等
            ans=ans+num*(num+1)/2;    //更新答案
            num=1;
        }
        else{     //如果相邻两数相等
            num++;     //答案再加一
        }
    }
    ans=ans+num*(num+1)/2;      //最后统计总数
    cout<<ans;       //输出答案
    return 0;      //好习惯
}
```

本蒟蒻首次发题解，求管理员给过。

---

## 作者：diqiuyi (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF83A)

### 思路

先翻译一下，最大值等于最小值也就是说这段区间的**每个数都相等**。

所以这题的思路就明确了，要分段做，其中每段的每个元素都相等。

至于每段区间的元素个数，设这段区间长度为 $x$ ，个数就是 $\dfrac{n(n+1)}{2}$。

然后设一个计数器，对于每个新加进的数，判断它与上一个数是否相等，再根据这个更新即可。

**证明**

设区间长度为 $len$，则该区间内

长度为 $1$ 的共有 $len$ 段；

长度为 $2$ 的共有 $len-1$ 段；

$...$

长度为 $i$ 的共有 $len-i+1$ 段；

$...$

长度为 $len$ 的共有 $1$ 段。

所以总段数就是 $1+2+3+...+len=\dfrac{n(n+1)}{2}$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return f?x:-x;
}
int ans,nowl,a,b,n;
//a是新加入的数，b是上一个数，nowl是目前区间的长度
int main(){
	n=read();
	while(n--){
		a=read();
		if(a==b)
			nowl++;
		else{
			ans=ans+(nowl*nowl+nowl)/2;
			nowl=1;
			b=a;
		}
	}
	ans=ans+(nowl*nowl+nowl)/2;
	printf("%d\n",ans);
	return 0;
}
```

~~自我感觉去掉快读后还蛮短的。~~

#### 注意事项

这里 $nowl$ 初始时其实要为 $1$，但由于第一个 $a$ 输入后 $nowl$ 一定会更新为 $1$ 且 $b$ 一定会等于 $a$，所以没有问题。~~这么说这个方法其实挺妙的，省去了对于第一次输入的特判~~。

---

## 作者：xiaomuyun (赞：3)

# CF83A Magical Array 题解
~~这个蒟蒻又来写题解了~~

[题目传送门](https://www.luogu.com.cn/problem/CF83A)
## 题目分析
首先，我们要知道，如果一个数组的最小值和最大值相同，那么这里面的所有元素都应该是**相等**的。

其次，我们就可以开始写代码了。因为子数组的所有元素都是相等的，所以我们要先在数组中找出有几个连续的子串，然后再按照子串的长度来计算这里面可以有几个答案。如果当前元素（即 $a_i$）和它的前一个元素（$a_{i-1}$）相等，就可以将一个计数器 $+1$；如果 $a_i$ 不等于 $a_{i-1}$ 时，就能开始**求连续的数之和**了。这题需要一些关于如何解决连续的数之和的公式，即（如果需要求 $1$ 到 $n$ 每个数的和）：
$$(1+n)×n/2$$
就是用这个公式，当 $a_i$ 不等于 $a_{i-1}$ 时，将公式中的 $n$ 替换成计数器来计算，然后加到 $ans$ 中。
## 代码实现
### 当 $a_i$ 等于 $a_{i-1}$ 时
因为本蒟蒻是用数组来表示计数器，所以可以得出这行代码：
```cpp
f[i]=f[i-1]+1;
```
但是如果是用 $cnt$ 来计算的话，就将它自增即可（**不要忘了初始化**为 $0$）。
### 当 $a_i$ 不等于 $a_{i-1}$ 时
```cpp
f[i]=1;
ans+=(1+f[i-1])*f[i-1]/2;
```
要注意，这里是有 $f_{i-1}$ 个数，不是 $f_i$ 个。
### 对于第 $n$ 个元素
一边输入一遍处理的时候需要在循环过后再写一次求连续的数之和的公式：
```cpp
ans+=(1+f[n])*f[n]/2;
```
### 需要注意的几个地方
1. 数据范围。$ans$ 需要开 $\operatorname{long\ long}$。
2. 这也是本蒟蒻犯的一个错误。就是给 $ans$ 开了 $\operatorname{long\ long}$ 之后，在 $\operatorname{printf}$ 的时候忘记写 %lld 了……（蒟蒻就是蒟蒻）

### ~~你们最爱的~~完整代码
```cpp
#include<cstdio>

using namespace std;

long long n,f[100001],a[100001],ans=0;

int main(){
	scanf("%d",&n);
	for(long long i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(a[i]==a[i-1]) f[i]=f[i-1]+1;//计数器+1
		else {
			f[i]=1;
			ans+=(1+f[i-1])*f[i-1]/2;//否则做连续的数的和的运算
		}
	}
	ans+=(1+f[n])*f[n]/2;//第n项的特殊运算
	printf("%lld\n",ans);//是%lld！！！
	return 0;我的代码好像是目前题解里代码最短的
}
```
## 总结
这是一道挺简单的思维题。希望大家能看懂本蒟蒻的写法，点个赞吧~

---

## 作者：_byta (赞：2)

大佬们都是直接推公式，我来弱弱的发一篇循环的题解。

考虑有一段每个数都相同的子串，设它长度为 n，那很容易得出它对答案的贡献

为 1 到 n 的累加，可以用高斯公式求。那问题就变成了寻找数组中数字相同的子串

的个数。直接循环求解即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100002;
int n,m,k,p,q,ans,sum,tot,cnt,a[N],b[N],c[N],d[N];
signed main()
{
	cin>>n;
	ans=n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		int t=1;
		k=i+1;
		while(a[k]==a[i]&&k<=n)
		{
			k++;
			t++;
		}
		if(a[i]==a[i+1])i=k-1;
		ans+=t*(t-1)/2;
	}
	cout<<ans;
}
```




---

## 作者：liupan2010 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF83A)

很明显，最大值与最小值相等，即整个子数组的数都是连续且相等的。

根据小学数学，当有 $len$ 个连续的相同的数时，那么有 $\dfrac{len^2+len}{2}$ 个 Magical 数组。

所以做法就很明显了，遍历整个数组。定义一个 $now$，如果连续就让计数器 $now$ 加一，否则就让答案加上 $\dfrac{now^2+now}{2}$，并将 $now$ 赋值为 $1$。

本题就这么做完了，还需要注意几点：
* 遍历完之后仍要更新答案！

* 答案需要开 $\texttt{long long}$！

代码如下。思路讲过了，就省掉了一些东西。

```cpp
#define int long long
using namespace std;
int n,arr[100001],now,ans;
signed main(){
	n=read();
	arr[1]=read();
	now=1;
	for(int i=2;i<=n;i++){
		arr[i]=read();
		if(arr[i]==arr[i-1]){
			now++;
		}
		else{
			ans+=now*(now+1)/2;
			now=1;
		}
	}
	ans+=now*(now+1)/2;
	write(ans);
	return 0;
}
```

---

## 作者：力巴尔 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF83A)

首先我们要知道：如果一个数组的最大值和最小值相等，那么这个数组中每个数都相等。

那么我们就可以利用上述规律，找出数组中的每一段相同数字，再求出每一段的子数组个数，相加即为答案。

最后还要再处理一下数组的最后一项。

注意这道题要开 long long。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n, s = 0, x = 1;
    cin>>n;
    long long a[n + 2];
    for (int i = 1;i <= n;i++)
    {
        cin>>a[i];
        if (i != 1)
        {
            if (a[i] == a[i - 1])
                x++;
            else
            {
                s += (x + 1) * x / 2;
                x = 1;
            }
        }
    }
    s += (x + 1) * x / 2;
    cout<<s;
}
```


---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，发现只要求出数字相同的连续子序列即可。设该连续子序列的长度为 $len$，最终答案为 $ans$，则 $ans$ 需加上 $\frac{len \times (len+1)}{2}$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,a[100005],len,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(a[i]==a[i-1]){
			len++;
		}
		else{
			ans+=len*(len+1)/2;
			len=1;
		}
	}
	ans+=len*(len+1)/2;
	cout<<ans;
	return 0;
}
```


---

## 作者：Creative_sad_yosgic (赞：0)

## CF83Aの题解
### 题意
有一个长度为 $n$ 的数组，定义这个数组的子数组为一个数组中的连续的数组成的序列。当**如果一个数组的最小值和最大值相同**，则称这个数组是Magical的。即求**所有元素相等的子数组数量**。

首先，我们手搓一组数据
```cpp
5
1 1 1 4 5
```
可以明显看出，在子数组$\left[ 1,1,1\right]$中，有 $3$ 个重复的 $1$ ，那么在这个子数组中，符合条件的子数组（下标）就有$\left[1\right]$,$\left[2\right]$,$\left[3\right]$, $\left[1,2\right]$ , $\left[2,3\right]$, $\left[1,2,3\right]$,可以发现，是不是很熟悉！我们画一下图

![](https://cdn.luogu.com.cn/upload/image_hosting/b73oufxl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

显而易见，一个长度为 $L$ 的重复序列，其造成贡献为 $1+2+3+...+L-1+L$ .

化简，得一个长度为 $L$ 的重复序列，其造成贡献为 $L\times(L+1)/2$ .

所以这个时候，代码就十分好写，只需要一边读入这个数组一边判断前一个元素是否与当前元素相同，如果相同，重复序列的长度 +1 ，如果不同，就按公式累加当前长度，并把长度初始化为 **$1$**（因为一个元素也算一个重复序列） ，记得枚举到 $n+1$ （因为枚举到 $n$ 会少算 $a_n$ ）.

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[114514],b[114514];
long long vis;
int n;unsigned long long ans;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);//读入量有点大 加个优化
	cin>>n;
	vis=1;//最初长度为 1 
	a[n+1]=11451419;//把 a[n+1] 赋值为一个不可能出现的元素
	for(int i=1;i<=n+1;i++) 
	{
		if(i!=n+1) cin>>a[i];//注意只用读入 n 次
		if(i!=1){//因为没有a[0] 长度预先设置为 1
		if(a[i]==a[i-1]) vis++;//如果是相同元素就长度 +1
		else ans+=(vis)*(vis+1)/2,vis=1; //不是就累加并初始化
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Kaenbyou_Rin (赞：0)

### 1.题意分析

本题要求一段连续的数的最大值和最小值相等，很显然只有当一段区间内的数全部相等时满足题意，而一段有 $n$ 个完全相等的数对答案的贡献为 $\frac{n(n+1)}{2}$ 。

### 2.解决

用一个 $tot$ 统计有几个连续相等的数，当前后两个数不等时更新答案即可。

### 3.Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,w=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') w=-1;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+ch-'0';
	return x*w; 
}
int n,a[100005],ans,tot;
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]!=a[i-1]){
			ans+=(tot*(tot+1))>>1;
			tot=1;
		}
		else tot++;
	}
	ans+=(tot*(tot+1))>>1;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

# 题意

如果一个数组的所有数都是相同的 ， 就称这个数组是  `Magical`  的 。

给出一个数组 $ a_i $ , 求 $ a_i $ 中有多少个子数组是 `Magical` 的 。

# 思路

根据题意 ， 我们要在数组中找到连续并且相同的一串数字 。

根据推理样例 ， 不难得出连续的数之和公式是 : $ k \times ( k + 1 ) \div 2  $

找的过程中 ， 会有两种情况 ：

$ \ \ $ 1. 相邻的两个数是相等的 $ ( a_i = a_{i-1} ) $ : 记录连续数个数的 $ k+1 $ 。 

$ \ \ $ 2. 相邻的两个数是不相等的 $ ( a_i \neq a_{i-1} ) $ : 答案 $ sum $ 套用公式 $ k \times ( k + 1 ) \div 2 (sum\gets sum + k /times ( k + 1 ) \div 2) $ , 记录连续数个数的 $ k $ 变为 $ 1 $ 。 

最后输出 $ sum $ 即可 。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,sum,a[100010];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        if(a[i]==a[i-1])k++;
        if(a[i]!=a[i-1])sum+=k*(k+1)/2,k=1;
    }
    sum+=k*(k+1)/2;
    cout<<sum;
    return 0;
} 
```

---

## 作者：封禁用户 (赞：0)

# 题意

如果一个数组的最小值和最大值相同，则称这个数组是符合要求的。定义一个数组的子数组为一个数组中的连续的数组成的序列。给你一个数组，求这个数组中符合要求的子数组有多少个。

# 思路

根据题意，我们在数组中找到一串连续并且相同的数字。

解决连续的数之和的公式就是：$(k \times k + k) \div 2$。

在找的时候，我们会遇到两种情况：

情况一，相邻两数相等，即 $a_i$ 等于 $a_i$ 的前一项：

连续的个数加一。

情况二，相邻两数不相等，即 $a_i$ 不等于 $a_i$ 的前一项：

套用公式，`sum` 加上 $(k \times k + k) \div 2$，然后 $k$ 变回 $1$。

循环结束后，在套用公式，统计总数。

最后输出 `sum`。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,sum;
int a[100010];
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=n; i++)
	{
		if(a[i]==a[i-1]) k++;//情况一
		else sum+=(k*k+k)/2,k=1;//情况二
	}
	sum+=(k*k+k)/2,k=1;//最后再套用一次，统计总数
	cout<<sum;
	return 0;
} 
```

---

## 作者：Starw (赞：0)

### 思路：

不难想到，一个数列的最小值和最大值相同的话这个数列的所有的数都相同。

一个长度为 $n$ 的连续的所有的数相同的数列中会有 $\sum\limits_{i=1}^n i$ 个那样的子数列。

我们想，在一个连续的所有的数相同的数列后增加一个数，那么那个数可以到原先有的任何一个数一起新增一个那样的子数列，自己又是一个，所以又会增加 $n$（$n$ 指加上那个数后的数列长度）,故上结论成立。

$\sum\limits_{i=1}^n i$ 我们可以用~~小学二年级学过的~~等差数列求和公式求，即为：$\dfrac{(1+n) \cdot n}{2}$。

直接扫一遍，统计每个连续的所有的数相同的数列的长度再计算一下即可。

### 代码:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	ll n,a,b,len(1),ans(0);//开long long
	scanf("%lld%lld",&n,&b);
	for(int i=2;i<=n;i++){
		scanf("%lld",&a);
		if(a!=b)ans+=(1+len)*len/2,len=1;
		else len++;
		b=a;//滚动数组
	}
	ans+=(1+len)*len/2;//注意最后的长度还要算一下
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：sysong (赞：0)

# 题解CF83A Magical Array

### 题目描述

如果一个数组的最小值和最大值相同，则称这个数组是Magical的。定义一个数组的子数组为一个数组中的连续的数组成的序列。给你一个数组，求这个数组中Magical的子数组有多少个。

### 题意分析

一个 ***最小值和最大值相同的数组*** 中显然每个元素都相同（这个很好想吧）。

要求统计这个数组中所有子数组。

**子数组：一个数组中的连续的数组成的序列。**

那么这个序列的最小长度为 $1$，最大为这个数组长度 $k$。

长度为 $1$ 的序列有 $k$ 个，长度为 $2$ 的有 $k-1$ 个，$\cdots$，长度为 $k-1$ 的有 $2$ 个，长度为 $k$ 的有 $1$ 个。

显然是一个从 $1$ 到 $k$ 的求和，即为 $\dfrac{k \times (k + 1)}{2}$。

### $C++ \quad Code$

**小优化：这里每一个元素只会被用到两次，第一次是与前一个元素比较，第二次是与后一个元素比较。**

**那么我们不需要开一个数组来记录，只要用一个变量存储就行了。**

（~~节约不少空间~~）

**注意点：**

1. **开 $long \ long$**

2. **$k$ 的初始值为 $1$ 不为 $0$，因为数字的长度也算 $1$。**

```c++
#include <bits/stdc++.h>
#define R register
#define gc() getchar()
#define ll long long
using namespace std;

inline ll rd(){
	R ll x=0,f=1;R char c=gc();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=gc();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x*f;
}

int main(){
	R ll n=rd(),pre=rd(),now,k=1,ans=0;
	for(R ll i=1;i<n;i++){
		now=rd();
		if(now==pre)++k;
		else pre=now,ans+=k*(k+1)/2,k=1;
	}
	printf("%lld\n",ans+k*(k+1)/2);
	return 0;
}

```





***by jsntsys***

$2020.12.5$



---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的序列 $a_1,a_2,a_3,...,a_n$。定义一个“神奇数组”为在上面的序列中最大值和最小值相等的子序列。求出这个序列中“神奇数组”的个数。

**数据范围：$1\leqslant n\leqslant 10^5,0\leqslant|a_i|\leqslant 10^9$。**
## Solution
这个题目直接模拟肯定会爆炸，所以我们考虑一个更高效率的算法。

首先，我们明显知道，最小值与最大值都相等的序列就是所有元素都相等的序列。

我们先通过样例来找找规律：

- 长度为 $4$ 的序列 $\{2,1,1,4\}$ 的答案是 $5=1\times(1+2)\div2+2\times(2+3)\div2+1\times(1+2)\div2$。
- 长度为 $5$ 的序列 $\{-2,-2,-2,0,1\}$ 的答案是 $8=3\times(3+1)\div2+2\times1\times(1+2)\div2$。

是不是发现规律了？

我们可以归纳出来：如果有一个长度为 $k$，且最小值与最大值都相等的序列，那么这里面的“神奇数组”有 $\dfrac{k(k+1)}{2}$ 个。

那么，这道题目很明显就出来了。

注意这里数据范围大，要开 $\texttt{long long}$。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, a[100007];
long long ans, cnt = 1;

int main() {
	scanf("%d%d", &n, &a[1]);
	for(int i = 2; i <= n; ++i) {
		scanf("%d", &a[i]);
		if(a[i] == a[i - 1])	cnt++;
		else {
//			printf("%d\n", cnt * (cnt + 1) / 2);
			ans += cnt * (cnt + 1) / 2;
			cnt = 1;
		}
	}
	ans += cnt * (cnt + 1) / 2;
	printf("%lld", ans);
}
```

---

## 作者：wenge (赞：0)

题目里说Magical Array是最大值和最小值相同的数字组成的连续串，就是一串连续并且相同的数字。而$n$个连续的相同的数字里包含$n \times (n+1) \div 2$个，这样就可以$O(n)$解决问题，还是很好想的。

AC代码：
```cpp
#include <iostream>
using namespace std;
long long a[100005];
long long ans=0;
int main(){
    long long n,j=1;
    cin>>n>>a[1];
    for(int i=2;i<=n;i++){
        cin>>a[i];
        if(a[i]!=a[i-1]){
            ans+=j*(j+1)/2;
            j=1;
        }
        else{
            j++;
        }
    }
    ans+=j*(j+1)/2;
    cout<<ans;
    return 0;
}
```

---

## 作者：YuanZihan1225 (赞：0)

[可能更好的阅读体验](https://yzhnb.blog.luogu.org/)
# 题目大意
我认为题目已经讲的很清楚了，还没看的[点这里](https://www.luogu.com.cn/problem/CF83A)。

# 题意分析

给你一个 $n$ 和一个长为 $n$ 的整数序列 $a$ ，让你求这个序列中有多少个数字相同的字串。现在它就成为了成为了一道裸题。

# 思路分析

我们可以通过循环来找这样的字串，用 $cnt$ 标记长度，用 $flag$ 记录当前值，再用 $ans$ 记录当前答案，每当 $a_i$ 不等于 $flag$ ，就更新答案

具体如何更新呢？需要用到一点**小学奥数**知识（数学恐惧者也可入！）。

我们可以把它变成：**一条线段上有 $n$ 个点，求能被划分成多少个线段。** 于是，我们要用到：
## 高斯求和公式：
$$
\sum \limits _ {i = 1} ^ n =\frac{(1 + n)n}{2}
$$

于是我们就能用以上思路写出一篇正确的代码。

# 代码见下
```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗 
using namespace std;
int cnt, flag, n, a[1000010], ans;
inline int read()//一个用来优化时间的好东西 
{
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')
			f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
signed main()
{
	n = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	cnt = 1, flag = a[1], ans = 0;//初始化变量 
	for(int i = 2; i <= n; i++)
	{
		if(a[i] == flag)//如果和前面的一样，计数器加一 
			cnt++;
		else//否则更新答案 
			ans += (1 + cnt) * cnt / 2, cnt = 1, flag = a[i];
	}
	ans += (1 + cnt) * cnt / 2;//处理一下最后的一个字串 
	cout << ans;//完美的结束
	return 0;
}
```

---

