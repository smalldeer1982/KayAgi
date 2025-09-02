# DDoS

## 题目描述

现在有越来越多的关于DDoS攻击网站的新闻。
Arseny是一个管理员，他认为如果一段时间内请求的总数超过100*t，那么网站就会受到DDoS攻击，其中t是时间段的秒数。
Arseny知道从服务器启动以来每秒请求次数的统计数据。他知道序列R1、R2、R3 …… Rn，其中Ri是启动后第i秒的请求数。
确定Arseny认为是DDoS攻击的最长连续时间段的长度。查找时间在1~n以内。

## 样例 #1

### 输入

```
5
100 200 1 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
101 99
```

### 输出

```
1
```

# 题解

## 作者：_JF_ (赞：3)

## CF1057B DDoS 

前缀和练习题。

大概是普及组第二题的难度。

题目大意：给出一个序列，问你的某一段连续序列 $[i,j]$ 的和是否大于一个 $100\times (j-i+1)$，找这个序列的长度最大。

由于是静态查询区间和，显然可以用前缀和算法，由于 $n \le 5000$，显然可以使用 $n^2$ 的办法去遍历每一个区间，而前缀和优化的就是这个查询这个区间和的过程。

最后统计区间长度最大就结束了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int a[N],s[N];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],s[i]=s[i-1]+a[i];
	int maxx=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++)
			if(s[i]-s[j]>100*(i-j))
				maxx=max(maxx,i-j);
	cout<<maxx<<endl;
	return 0;
}
```


---

## 作者：Milthm (赞：3)

## CF1057B 题解

sjh：喵喵小课堂开课啦！我是蒟蒻 sjh，今天我们来学习 CF1057B 的解法！

喵喵们：好耶！

sjh：好的，fzj 你说一下思路。

fzj：这题十分的简单，我认为需要暴力枚举。

sjh：说的好，但是直接枚举的复杂度是 $O(n^3)$，所以怎么办呢？

lxx：前缀和！

sjh：很有道理，次掉。所以只需要双重循环枚举区间和，如果满足条件判断就可以啦！来，zzy 你把代码写出来。

zzy:（顺手加上了注释，我哭死）
```cpp
#include<iostream>
using namespace std;
int n,a[5005],f[5005],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		f[i]=f[i-1]+a[i];//前缀和
	}
	for(int i=1;i<=n;++i){
		for(int j=i;j<=n;++j){//枚举判断，注意i与j相等时也算区间
			if(f[j]-f[i-1]>(j-i+1)*100){//如果区间和大于长度*100，注意题目中的“超过”是大于不是大于等于！
				ans=max(ans,j-i+1);//取ans的max值
			}
		}
	}
	cout<<ans;
	return 0;
}
```

~~好了，下课。~~

---

## 作者：BinarySearchTree (赞：1)

关于 [DDoS](https://baike.baidu.com/item/%E5%88%86%E5%B8%83%E5%BC%8F%E6%8B%92%E7%BB%9D%E6%9C%8D%E5%8A%A1%E6%94%BB%E5%87%BB/3802159?fromtitle=DDOS%E6%94%BB%E5%87%BB&fromid=177090&fr=aladdin) 攻击，一定是很多人都害怕的攻击了。

但这道题与 DDoS 毫无关联。

#### 题意

给你个数组 $a$，找到 $a$ 中最长的一个序列，这个序列的左右坐标分别为 $l$ 和 $r$，满足 $a_l$ 至 $a_r$ 的和大于 $100 \times (r-l+1)$。

#### 题解

算出前缀和，暴力求就好了。

所有的序列包括：

$l=1,r=2$ ~ $n$

$l=2,r=3$ ~ $n$

$l=3,r=4$ ~ $n$

……

$l=n-1,r=n$

所以近似复杂度是 $O(n^2)$

就 $\texttt{AC}$ 了

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[5005];
int q[5005];
int main(int argc, const char * argv[]) {
    // insert code here...
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        q[i]=q[i-1]+a[i];
    }
    int MAX=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(100*(j-i+1)<(q[j]-q[i-1])){
                MAX=max(MAX,j-i+1);
            }
        }
    }
    printf("%d",MAX);
    return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有一个长度为 $n$ 的数列 $a_1,a_2,...,a_n$，求出满足 $\sum\limits_{i=l}^r a_i>100\times(r-l+1)$ 的区间 $[l,r]$ 长度的最大值。

**数据范围：$1\leqslant n\leqslant 5000,0\leqslant a_i\leqslant 5000$。**
## Solution
前缀和简单题，我们预处理出所有的前缀和之后，再直接 $\mathcal{O}(n^2)$ 枚举所有满足条件的区间长度，取其最大值即可。
## Code
```cpp
int n, r, s[5007], ans;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {scanf("%d", &r); s[i] = s[i - 1] + r;}
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
			if(s[j] - s[i - 1] > 100 * (j - i + 1)) ans = max(ans, j - i + 1);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：zgy_123 (赞：0)

~~这个题为什么黄？~~

大意：找出最长一段数，平均数大于 $100$。

## 思路
这个题数据范围小，可以前缀和 + 双循环枚举区间。

需要注意的是，由于题目中要求长度最大，所有外层循环枚举长度更好。

注意题目中说如果没有就输出 $0$，所以最好的方法是找到符合条件的长度后直接 `return 0`，可以避免多余的特判

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5005],p[5005];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p[i]=p[i-1]+a[i];//前缀和
	}
	for(int i=n;i>0;i--)
		for(int j=i;j<=n;j++)//j代表结束的位置
			if(p[j]-p[j-i]>i*100){//注意不是j-i-1而是j-i
				cout<<i;
				return 0;//避免多次输出
			}
	cout<<0;
	return 0;
}

```

---

## 作者：kimidonatsu (赞：0)

# CF1057B DDoS 题解

## 题意简述

输出受 $\texttt{DDoS}$ 攻击的最长时段。

* 有一个长度为 $n$ 的序列 $a$
* 若 $a_i \sim a_j$ 的请求总数大于了 $100 \times (j - i + 1)$，则判定为正在受 $\texttt{DDoS}$ 攻击中。
* 求一段受 $\texttt{DDoS}$ 攻击的最长的时间段的长度

## 思路分析

暴力枚举，需要 **前缀和** 优化，为了叙述方便，我们将左指针设置为 $l$，右指针设置为 $r$。

由题意得，我们需要找到最长区间，要求：

$$\sum_{l = i}^{r} a_i \gt 100 \times (r - l + 1)$$

如果我们一边枚举长度，一边枚举 $l$，一边枚举 $r$ 的话，时间复杂度是 $\mathcal{O}(n^3)$，明显会 T 飞。

考虑优化，使用前缀和。在输入到第 $i$ 个时，统计从 $a_1 \sim a_i$ 的访问总和，我们只需要枚举 $l$ 和 $r$，找满足条件的区间即可，以 $\mathcal{O}(n^2)$ 的时间复杂度通过此题。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 5050;

int n, ans = 0;
int r[N];

int main() {
    scanf("%d", &n);
    for (int i = 1, in; i <= n; i++) {
        scanf("%d", &in);
        r[i] = r[i - 1] + in;
    }

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            if (r[j] - r[i - 1] > 100 * (j - i + 1))
                ans = max(ans, j - i + 1);

    printf("%d\n", ans);
    return 0;
}

```

代码小注：

1. 承接上文，之所以使用 $j - i + 1$ 可以类比一下 $1 \sim 2$ 的长度为 $2$，但是如果直接使用 $2 - 1$ 的话计算出的长度为 $1$，所以我们需要加上 $1$ 来计算出区间长度。（如上述题目分析）
2. 此处的 ans 不建议初始化为一个很小的 $\texttt{INF}$ 值（如 $-1e9$），题目中要求无答案返回 $0$，数据范围也保证为正数，所以初始化 $ans$ 为 $0$ 即可。（不加上特判直接使用 $-1e9$ 会在第二个点挂掉）


---

## 作者：dingshengyang (赞：0)

这题有一个 naive 的做法，即枚举长度 $i$，如果 $\sum_j^{i+j-1}\gt 100\times i$，说明是一个 ddos 攻击。代码就不放了。因为 $O(N^3)$ 根本就过不了。~~因为我压根儿就没写~~

怎样优化呢？

看到 $\sum$，我们就想到了前缀和。令 `s[i]` 为 $\sum_1^i$。

$\sum_l^r$ = ```s[r]-s[l-1]```。

读不懂？感性理解。首先拿到 $1\sim r$ 的总和，然后把 $1\sim l-1$的和扣掉，就是 $l \sim r$ 的总和。$O(N^2)$，十分优秀。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[5005]; 
int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		scanf("%d",&a[i]);
		a[i] += a[i-1];//偷懒，直接在原数组上改了
	} 
	int longest = 0;
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j+i-1 <= n;j ++){
			if(a[j+i-1]-a[j-1]>i*100){
				longest = i;
				break;
			}
		}
	}
	cout << longest << endl;
	return 0;
}


```

---

## 作者：jimmyfj (赞：0)

这道题其实是一道简单的前缀和模板题。

先计算每一位的前缀和，然后再判断第 $j$ 位到第 $i$ 位的请求总数是否大于 $100 \times \left(j - r + 1\right)$，再与 $len$ 比较，如果大于 $len$，则将值存入 $len$；否则，继续寻找下一段满足条件的长度与 $len$ 比较，直至无法寻找为止。

参考代码 ：

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n, k;
int len = 0, s[10005];

int main()
{
    scanf("%d", &n);
    s[0] = 0;
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &k);
        s[i] = s[i - 1] + k;//前缀和
    }
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= n; j ++)
        {
            int l = j - i + 1;//因为是左开右闭区间,所以还要加1
            if((s[j] - s[i - 1]) > (100 * l)) len = max(len, l);//判断是否满足条件，满足的话就与len比较
        }
    }
    printf("%d\n", len);
    return 0;
}
```


---

## 作者：pengzy (赞：0)

### 思路：

本题使用前缀和算法来优化时间复杂度。

什么是前缀和？详见[模板](https://www.luogu.com.cn/problem/P8218)。

预处理前缀和后，只需要用二重循环枚举满足条件的 **最大** 区间长度即可，一边枚举一边更新答案。

### 代码：

```cpp
for(int i=1;i<=n;i++)cin>>x,s[i]=s[i-1]+x;
for(int i=1;i<=n;i++)
	for(int j=i/*因为 r>=l 所以 j 从 i 开始*/;j<=n;j++)
		if(s[j]-s[i-1]>100*(j-i+1))
		    ans=max(ans,j-i+1);
```

---

## 作者：Steven_lzx (赞：0)

在博客园食用以获取更好的体验，请点 [这里](https://www.cnblogs.com/2020gyk080/p/cf_1057B.html)。

# 思路

**前缀和**，预处理出 $r$ 的前缀和 $s$ 后，只需用 $s_y-s_{x-1}$ 就能得出 $\sum^{i=x}_yr_i$ 的值。

暴力枚举 $l$ 和 $r$ 的位置，若满足条件，则更新最大值。

时间复杂度 $\Theta(n^2)$.

# 代码

```cpp
int main()
{
	n=fastio_read();
	for(int i=1;i<=n;i++)
	{
		a=fastio_read();
		s[i]=s[i-1]+a;		//预处理前缀和
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			if(s[j]-s[i-1]>100*(j-i+1))		//满足条件，更新
			{
				ans=max(ans,j-i+1);
			}
		}
	}
	fastio_write(ans);
	putchar('\n');
	return 0;
}
```

---

## 作者：gyc18 (赞：0)

#### 题目大意
给一个序列，选择一个区间，假设区间所有元素之和为 $X$，长度为 $Y$，问所有符合 $X \ge 100 \times Y$ 的序列中最长的 $Y$ 是多少？
#### 解题思路
选用前缀和求解。枚举每一个区间的左端点和右端点，$n^2$ 模拟，不会超时。设前缀和数组 $Q$，则和为 $Q_r - Q_{l-1}$，按照题目大意计算取最大值，就是结果。
#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[5005];
int q[5005];
int main() {
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        q[i]=q[i-1]+a[i];
    }
    int MAX=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(100*(j-i+1)<(q[j]-q[i-1])){
                MAX=max(MAX,j-i+1);
            }
        }
    }
    printf("%d",MAX);
    return 0;
}
```


---

## 作者：QcpyWcpyQ (赞：0)

- 一句话题意：找出最长一段平均数大于 $100$ 的数列。

考虑前缀和，预处理后枚举满足条件的最大区间长度即可，一边枚举一边更新答案。时间复杂度为 $O(n^2)$，$n\leq5000$，可以通过此题。

- code:

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

inline int read(){
	int f=1,s=0;char ch=getchar();
	while(ch<'0' or ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' and ch<='9')s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f*s;
}

inline void write(int num){
	if(num<0)num=-num,putchar('-');
	if(num>9)write(num/10);
	putchar(num%10+48);
}

const int N=5e3+5;
int n,a[N],sum[N],ans;

int main(){
    n=read();
    for(int i=1;i<=n;++i)
        a[i]=read(),sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(100*(j-i+1)<sum[j]-sum[i-1])
                ans=max(ans,j-i+1);
    write(ans);
	return 0;
}
```


---

## 作者：Xiphi (赞：0)

前缀和板子，$n^2$ 时间枚举范围的左端点和右端点，然后用前缀和数组 $O(1)$ 计算是否符合要求，最后找到长度最大值即可，总复杂度 $O(n^2)$。

代码：
```cpp
#include<bits/stdc++.h>
#define N 5005
using namespace std;
int a[N],sum[N];//sum为前缀和数组
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i],sum[i]=sum[i-1]+a[i];//初始化前缀和数组
    int ans=0;//设为int的最小值
     for(int i=1;i<=n;++i)//枚举范围的左端点和右端点
        for(int j=1;j<=n;++j)
           if(100*(j-i+1)<sum[j]-sum[i-1])
                ans=max(ans,j-i+1);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：sunson (赞：0)

这题使用前缀和 

设一个数组为a,那么它的前缀和s[i],
顾名思义就是前面i个数的总和。

数组a在经过这样的操作之后，对于每次的询问，我们只需要计算s[i]-s[j]就能得到[j,i]的区间和；

我们这里直接枚举i与j的位置，如果大于100*(i-j)，就更新max

时间复杂度O(n^2)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maxnn=0,maxmm=0;
int a[5050],s[5050];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int t;cin>>t;
        a[i]=t;
        s[i]=s[i-1]+t;
    }
    for(int i=n;i>=1;i--){
        for(int j=0;j<i;j++){
            if((s[i]-s[j])>(100*(i-j))&&i-j>maxnn){
                maxnn=i-j;
                break;
            }
        }
    }
    cout<<maxnn<<endl;
    return 0;
}
```

---

