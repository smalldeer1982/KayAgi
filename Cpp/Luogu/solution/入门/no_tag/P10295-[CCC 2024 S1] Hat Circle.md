# [CCC 2024 S1] Hat Circle

## 题目描述

在最近的一次聚会上，$N$ 个人围坐在一张圆桌旁，其中 $N$ 是偶数。座椅按顺时针方向编号为 $1\sim N$。每个人都戴着一顶写有数字的帽子。具体来说，座位 $i$ 上的人戴着一个写有数字 $H_i$ 的帽子。

每个人都看着圆圈中与自己正对面的人。

请你求出看到戴着与自己相同号码的帽子的人的数量。

## 说明/提示

**【样例 1 解释】**

桌子周围的四个座位排布如下图所示。圆圈里的数字表示这个人的帽子上写的数字，圆圈旁边的数字表示这个人的编号。注意每个人看到的数都与自己的帽子上的数相等。坐在位置 $1$ 和 $3$ 上的人都看到了数字 $0$，坐在位置 $2$ 和 $4$ 上的人都看到了数字 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/vvym8vb6.png)

**【样例 2 解释】**

桌子周围的四个座位排布如下图所示。圆圈里的数字表示这个人的帽子上写的数字，圆圈旁边的数字表示这个人的编号。注意每个人看到的数都不与自己的帽子上的数相等。坐在位置 $1$ 和 $4$ 上的人都看到了数字 $0$，坐在位置 $2$ 和 $3$ 上的人都看到了数字 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/dc5ar3s0.png)

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证 $1\leq N\leq 10^6$，$0\leq H_i\leq 2\times 10^6$。

下面的表格显示了 $15$ 分的分配方案：

| 分值 | 描述 | $N$ 的范围 | $H_i$ 的范围 |
| :-: | :- | :-: | :-: |
| $2$ | 人数很少；只有两种可能的帽子上的数 | $N \leq 4$ | $H_i \leq 1$ |
| $1$ | 只有一种可能的帽子上的数 | $N \leq 100$ | $H_i = 1$ |
| $2$ | 坐在奇数位置上的人的帽子上数为 $1$，坐在偶数位置上的人的帽子上数为 $0$ | $N \leq 100$ | $H_i \leq 1$ |
| $5$ | 中等多少的人数 | $N \leq 2 \times 10^3$ | $H_i \leq 4 \times 10^3$ |
| $5$ | 很多人和可能的帽子上的数 | $N \leq 10^6$ | $H_i \leq 2 \times 10^6$ |

## 样例 #1

### 输入

```
4
0
1
0
1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
1
0
0
1
```

### 输出

```
0```

# 题解

## 作者：xyx404 (赞：11)

## 思路：
通过画图可知编号为 $i$ 的人的正对面的人的编号为 $i+n/2$，前提是 $i$ 小于等于 $n$ 的一半。

![](https://cdn.luogu.com.cn/upload/image_hosting/7a6jdljw.png)

得知了编号为 $i$ 的人和他的正对面的人的编号就可以直接判断他们帽子的号码是不是相同的就可以了。

已提交测试。

## 完整代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define CPPname using namespace std
CPPname;
LL n;
const int MAX=1000010;
LL a[MAX];
int main(){
	cin>>n;
	LL ans=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	const int c=n/2;
	for(int i=1;i<=n/2;i++){
		if(a[i]==a[i+c])ans+=2;
		//cout<<i<<" "<<i+n/2<<" ";
	}
	
	cout<<ans;
	return 0;
}

```

---

## 作者：_iridescent (赞：5)

### 题目大意

有 $N$ 个人坐在一个圆桌上，桌上的每个人都带着一个帽子，帽子上有一个数，每个人都只能看到自己正对面的人帽子上的数，求看到戴着与自己相同号码的帽子的人的数量。

### 分析

对于这种带有环的问题，常规思路一般都是破环为链，即对于每一个 $h_{i}$，我们都将 $h_{i+n}$ 定义为 $h_{i}$ 的值，这样问题就被大大简化了。

我们接下来只需要枚举桌上的每个人，如果他对面的人，即 $h_{i+n\div2}$ 与他的值相同，答案就加一，最后输出答案即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int maxn=2000005*2;//由于要破环为链，所以数组大小要开成两倍
int n,ans,h[maxn]; 
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>h[i];
		h[n+i]=h[i];//破环为链
	}
	for(int i=1;i<=n;i++){
		if(h[i+n/2]==h[i])ans++;//对面人的值与自己相等，答案+1
	}
	cout<<ans<<endl;
}
```

---

## 作者：TheForgotten (赞：3)

# [CCC 2024 S1] Hat Circle

## 题目描述

$N$ 个人围坐在一张圆桌旁，求出看到戴着与自己相同号码的帽子的人的数量，数据保证 $N$ 是偶数。

## 思路

因为 $N$ 是偶数，那么设 $p=N/2$，所以 $a_i$ 相对的人是 $a_{i+p}$。枚举一遍所有人，寻找相等的人即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000005],cnt,u; 
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	u=n/2;
	for(int i=0;i<n;i++){
		if(a[i]==a[(i+u)%n]) cnt++;//取模n是因为怕i+u超出数组范围 
	}
	cout<<cnt;
	return 0;
}
```
> 任何一个伟大的思想，都有一个微不足道的开始。

---

## 作者：Pyrf_uqcat (赞：2)

竟然还有能写题解的红题，赶紧来水一波。

从第 $1$ 个人开始遍历，遍历到总人数的一半。因为一共有 $n$ 个人且 $n$ 是偶数，所以第 $i$ 个人对面就是第 $\frac{n}{2}+i$ 个人，判断面对面的两人是否数字一样，是则累加答案。

### 代码
```cpp
#include <bits/stdc++.h>
#define N 1000005
using namespace std;
int a[N],ans;//ans统计答案
int main() {
	int n;cin>>n;//输入n
	for(int i=1;i<=n;i++) cin>>a[i];//输入每个人的数字
	for(int i=1;i<=n/2;i++) {//从1到第n/2人开始遍历
		if(a[i]==a[n/2+i]) //如果面对面两人数字相同
			ans+=2;
			//如果相同，那么第i人符合要求，且他对面上的人也符合要求，所以加2
	}
	cout<<ans<<endl;//输出答案
	return 0;//好习惯
} 
```
~~请看懂了再抄。~~

---

## 作者：封禁用户 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P10295)

## 思路

水。

如果是围绕圆桌，那么枚举 $1\le i\le \dfrac{n}{2}$，如果 $a_i=a_{i+n\div2}$，那么 $ans$ 要加 $2$，因为对面的那个人看向这边，看到的帽子颜色肯定也一样，应该挺好理解的。

```cpp
#include <iostream>
using namespace std;
int a[1000010];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0;
    for (int i = 1; i <= n / 2; i++)
        if (a[i] == a[i + n / 2]) ans += 2;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：DL_Lingkong (赞：1)

# P10295 [CCC 2024 S1] Hat Circle 题解

[题目传送门](https://www.luogu.com.cn/problem/P10295)

大水题。

## 题目大意

$N$ 个人围坐在一张圆桌旁，每个人都戴着一顶写有数字的帽子且都看着圆圈中与自己正对面的人，请你求出看到戴着与自己相同号码的帽子的人的数量。

## 题目分析

假设一个人编号为 $i$，那么，他可以看到的人编号为 $i + \frac {n}{2}$（别问我为什么），因为编号为 $i$ 和 $i + \frac {n}{2}$ 的人是可以互相看见的，所以只用从 $1$ 遍历到 $\frac {n}{2}$，编号为 $i$ 和 $i + \frac {n}{2}$ 的人号码一样的话计数器加 $2$ 即可。

## 上代码！！！

```cpp
#include <iostream>
using namespace std;
int a[1919810],n,ans;
void be() // init & input
{
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
	}
	return ;
}
void kin() // programming
{
	for(int i = 1;i <= (n / 2);i++)
	{
		if(a[i] == a[i + n / 2])
		{
			ans += 2;
		}
	}
	return ;
}
void ei() // output
{
	cout << ans << endl;
	return ;
}
int main()
{
	be();
	kin();
	ei();
	return 0;
}
```

---

## 作者：hexuchen (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10295)

[更好的阅读体验？](https://www.luogu.com.cn/article/y3ri1yyu)

## 题目大意

有 $n$ 个人（$n$ 为偶数）围成一圈，每个人头上有一个数字。每个人可以看到自己对面的人头上的数字。请问有几个人看到的对面的人头上的数字与自己相同？

## 思路分析

一道水题。

思路简单，先输入，然后我们观察一下样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/vvym8vb6.png)

分析一下，得出一个结论，每个人自己和对面的人分别都在圆的左右两边。再举一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ij1yeikz.png)

确实，每个人的对面都在圆的两边。所以每两个人之间的距离就是 $n \div 2$。只要判断第 $i$ 个人与第 $i + (n \div 2)$ 个人（$i \le n \div 2$）的数字是否相同即可。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s[1000001],ans=0;
int main(){
    cin>>n;
    int a=n/2; //两个人之间的距离
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    for(int i=1;i<=a;i++){ //只要循环到中点
        if(s[i]==s[i+a]) //如果对面两个人头上的数字相同
            ans+=2; //因为有两个人
    }
    cout<<ans; //输出
    return 0; //完结撒花~
}
```

---

## 作者：Alystkia (赞：1)

这道题其实就是一道数学题，只需要开一个数组 $a$ 大于 $10^6$，再进行判断有几对帽子上的数字相同。

通过观察题里给出的样例解释，可以看出当座位号为 $i$ 时，其正对面的编号为 $(i + n/2)  \bmod  n$，知道了这个就可以开始写了。

```
#include<iostream>
int a[1000010];
using namespace std;
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>a[i];
    int ans=0;
    for(int i=0;i<n;i++)
    {
        if(a[i]==a[(i+n/2)%n])
        {
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：DFs_YYDS (赞：1)

## 题外话
挺水的，读懂了题目就行，蒟蒻建议评红。
## 题目大意
给 $n$ 个数，问这个 $n$ 个数围成一圈，自己和对面的数一样的有几个。
## 具体思路
很容易就能发现，如果有 $n$ 个数围成一圈，那么第 $i$ 个数的对面就是第 $i+n/2$ 个，那么只需要枚举每一个数，看它的对面和它相不相等就行了。当然，如果一个数的对面和它相等，那么对面的数和它也相等，所以只需要枚举到 $n/2$，每次遇到计数器加 $2$ 就行了，这样还能避免越界的问题。

时间复杂度 $O(n)$，可以很轻松的通过本题。
## 完整代码
```cpp
#include<bits/stdc++.h>//万能头。 
using namespace std;
int a[1000005];//定义数组。 
int main(){
	int n,cnt=0;//n个数和计数器cnt。 
	cin>>n;//输入n。 
	for(int i=0;i<n;i++)cin>>a[i];//读入第i个数。 
	for(int i=0;i<n/2;i++)if(a[i]==a[i+n/2])cnt+=2;//最重要的一句，一定要理解！ 
	cout<<cnt;//输出。 
	return 0;//华丽结束。 
}
```

---

## 作者：_Deer_Peach_ (赞：1)

一道大水题。

只要遍历前一半的人就行了，如果满足答案加一，最后再乘以二就可以了。

用样例说明：
```
4
1
0
1
0
```
编号为 $1$ 的数字为 $1$，编号为 $2$ 的数字为 $0$，编号为 $3$ 的数字为 $1$，编号为 $4$ 的数字为 $0$。

$1$ 号对面的人是 $3$ 号，$2$ 号对面的人是 $4$ 号，数字刚好相等，答案为 $2$，最后乘 $2$。

至于为什么乘二很好想，就不过多解释。

再讲一下怎么计算对面的人，很简单，当前编号加上总人数的一半就是对面的编号。

具体代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n;
	cin>>n;
	int ans=0;
	int h[n+1];
	for(int i=1;i<=n;i++)cin>>h[i];
	for(int i=1;i<=n/2;i++)if(h[i]==h[i+n/2])ans++;
	cout<<ans*2;
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

[P10295 [CCC 2024 S1] Hat Circle](https://www.luogu.com.cn/problem/P10295)

考虑将环展开为一条链，需要在第 $n$ 个数后再补上 $n$ 个数。

此时第 $i(1 \le i \le n)$ 个人对面坐着的是第 $i + \dfrac{n}{2}$ 个人，判断这两个数是否相等，累加到答案里即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 2e6 +10;
int n, a[N], ans; 
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i + n] = a[i];
	for (int i = 1; i <= n; i++) ans += (a[i] == a[i + (n >> 1)]);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：dongrunxuan (赞：0)

# P10295 题解
## 前言
一道类似[小苹果](https://www.luogu.com.cn/problem/P9748)的简单入门题，适合新手尝试。
## 思路
依照题意模拟即可。当 $1\le i \le \frac{n}{2} $ 时，坐在 $i$ 号位置对面的人对应编号为 $i+\frac{n}{2}$。又因为看到对面编号与自己编号相同时，面对的人也能看到你的编号与他相同，所以答案为 $1\le i \le \frac{n}{2} $ 时统计的答案的 $2$ 倍。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,ans;
const int maxn=1e6+10;
int a[maxn];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n/2;i++)
	{
		if(a[i]==a[n/2+i])
		{
			ans++;
		}
	}
	cout<<ans*2;
	return 0;
}
```

---

## 作者：DHT666 (赞：0)

## 题意
有 $N$ 个人坐圆桌，第 $i$ 个人有数字 $a_i$，求桌**正对面**的人得数字和自己的数字一样的人的人数。

## 思路
要明确一点~~常识~~：

- 第 $i$ 个人桌**正对面**的人的编号是 $i+N\div 2\ (1\le i\le N\div 2)$。

故暴力枚举即可，因为每一对人对答案的贡献是一样的，所以可以只枚举一半的人，每组人的贡献为 $2$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 10;

int n,ans;
int a[N];

signed main() {
	cin >> n;
	for(int i = 1;i <= n;i++) {
		cin >> a[i];
	}
	
	for(int i = 1;i <= n / 2;i++) { // 枚举一半的人
		if(a[i + n / 2] == a[i]) ans += 2; // 有一组人数字相同
	}
	
	cout << ans;
	
	return 0;
}
```

---

## 作者：_Epsilon_ (赞：0)

# 题意

给一个正偶数 $N$，代表有 $N$ 个人。

接下来 $N$ 行，每行一个数。第 $i$ 行表示第 $i$ 个人的数字 $a_i$。

最后这些人围成一个圈，求有几个面对的人的数字和自己相同。

# 思路

![](https://cdn.luogu.com.cn/upload/image_hosting/06l8zcam.png)
如上图样例，第一个人面对的是第四个人，第二个人面对第五个人，第三个人面对第六个人。不难发现，每个人与面对的人的编号相差三。

多举几个例子就可以发现，上面所谓的“三”其实是由 $N\div2$ 得到的。由于 $N$ 是正偶数，所以我们只用去判断第 $i$ 个人和第 $i+(N\div2)$ 是否相同即可。相同的话答案变量增加 $2$。
## ans 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000005],ans,ls;
int main()
{
	std::cin>>n;
	for(int i=1;i<=n;++i)
	{
	    std::cin>>a[i];
	}
	n=n/2;
	for(int i=1;i<=n;++i)
	{
	    if(a[i]==a[i+n])
	    {
	        ans+=2;
	    }
	}
	cout<<ans;
	return 0;
}
```

## 常见问题

1. 循环的时候到底是 $N$ 次还是 $N\div2$ 次。
2. 值一样时 $ans$ 只增加了 $1$。

---

## 作者：A_grasser (赞：0)

## 题意简化

有 $n$ 个人围着圆圈坐，每个人能看到正对面的人，求看到对面的人与自己所拥有的数相同的人的个数。

## 解法分析

画张图就明白了：

![](https://cdn.luogu.com.cn/upload/image_hosting/16xp5ug6.png)

不难发现，有 $n$ 个人，当 $i$ 小于等于它的一半时，$i$ 对应的是 $i+\frac{n}{2}$。所以只要枚举 $n$ 的一半，遇到一对相同的答案加二即可。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int n;
int a[1000009];
int main(){
	cin>>n;
	int ans=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n/2;i++){//枚举一半 
		if(a[i]==a[(int)(n/2)+i]) ans+=2;//对应相同 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

假设有 $n$ 个人围成一圈（$n$ 为偶数），那么与他对面的人的编号为 $\frac{n}{2} + i$，这时必须满足 $i\le \frac{n}{2}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/oluwawb3.png)

但是有一个对称性，如果 $a_i = a_{\frac{n}{2} + i}$，那么 $a_{\frac{n}{2} + i} = a_i$，因此如果满足上面的式子，对答案的贡献为 $2$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define sc scanf
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

const int N=1e6+10;
int n,ans,h[N];

signed main(){
  n=read();
  rep(i,1,n) h[i]=read();
  rep(i,1,n >> 1)
    if(h[i]==h[(n >> 1) + i]) ans+=2;//如果一样，则对答案的贡献为 2。
  pr("%lld\n",ans);
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10295)
## 解题思路
一看到这种题目，第一步就是画图。
### $n=6$
![6](https://cdn.luogu.com.cn/upload/image_hosting/mq0r7b8d.png)
### $n=8$
![8](https://cdn.luogu.com.cn/upload/image_hosting/p3ghspjw.png)

可以发现，如果当前位置是 $x$，那么它的对面就是 $x+\dfrac{n}{2}$。

那我们就从 $1$ 到 $\dfrac{n}{2}$ 遍历数组（因为如果当前的人与对面的人相同，只记录一次就够了，没必要重复），如果当前的人与对面的人相同，计数器 $s \gets s+2$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,s=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n/2;i++)
        if(a[i]==a[i+n/2])s+=2;
    cout<<s;
    return 0;
}
```

---

## 作者：gloomy_ (赞：0)

观察题干给的图片。  
![](https://cdn.luogu.com.cn/upload/image_hosting/yes1286i.png)  
显而易见地，我们发现面对面的两个人编号之差为 $\frac{n}{2}$。那么只要从 $1$ 遍历到 $\frac{n}{2}$ 就行了。注意，题目要求的是人数并非对数，所以一次要加二。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int ans=0;
	for(int i=1;i<=n/2;i++)
	{
		if(a[i]==a[i+n/2])
		{
			ans+=2;//这里要特别注意
		}
	}
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：LG086 (赞：0)

### 分析

输入 $N$ 个数，围成一圈，判断**多少个**正对面的数字相等。

画图找规律，以 $N=8$ 为例时如下图。  
![](https://cdn.luogu.com.cn/upload/image_hosting/lniwngtq.png)   
得出 $H_i$ 和 $H_j$ 面对面且 $i < j$ 时，满足 $i + 4 = j$。  
而 $8\div 2=4$，所以得出输入的 $H_i$ 与 $H_{i+n\div 2}$ 面对面。

所以可以统计有多少**对**数字面对面且相等，输出时再乘以 $2$。

------------
### 代码

```cpp
#include<iostream>
#define LG086 signed
LG086 main(){
    int n,i,ans,a[1000010];
    std::cin>>n,ans=0;
    for(i=1;i<=n;i++)
    std::cin>>a[i],
    ans+=((i>n/2&&a[i]==a[i-n/2])?1:0);
    std::cout<<ans*2;
}
```

---

## 作者：gavinliu266 (赞：0)

# 思路
观察样例，可以发现，编号为 $i (1 \le i \le \frac{n}{2})$ 的人对面的人编号为 $i + \frac{n}{2}$。

![样例](https://cdn.luogu.com.cn/upload/image_hosting/vvym8vb6.png)

当然，反过来，编号为 $i (\frac{n}{2} < i \le n)$ 的人对面的人编号为 $i - \frac{n}{2}$。

显然，上面的这两组是重复的，因此可以只检查其中的一组，然后将答案 **乘二**，就能得到正确的结果了。

可以写出如下程序：
```cpp
for(int i = 1; i <= (n / 2); ++i)
    if(a[i] == a[i + n / 2])
        ++ans;
ans *= 2;
```

注意到这里当 $a_i = a_{i + \frac{n}{2}}$ 时 if 内表达式返回值为 $1$，否则返回值为 $0$，可以利用该表达式的返回值统计答案，写成这样：
```cpp
for(int i = 1; i <= (n / 2); ++i)
    ans += (a[i] == a[i + n / 2]);
//   为真时返回一，ans 加一，否则加零
ans *= 2;
```
# 代码实现
```cpp
#include <cstdio>
using namespace std;
int n, a[1000005], ans;
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for(int i = 1; i <= (n / 2); ++i)
        ans += (a[i] == a[i + n / 2]);  // 主要部分就是这个 for 循环。
    printf("%d\n", ans * 2);
      // 这里只统计了一半，别忘记乘二。
}
```

---

## 作者：_Jocularly_ (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/nzvhonl7.png)

观察这张图，编号小于等于个数一半的数，例如一对四，二对五，三对六，我们能发现，编号为 $i$ 的数所对 $i + n/2$ 的数。那么当编号个数大于个数一半的时候，例如四对一，五对二，六对三，此时的规律为，编号为 $i$ 的数所对的位置为编号为 $i + n/2 - n$ 的数，此时只要按照这个规律判断即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[2000005];
int ans;
int main(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		a[i+n] = a[i];
	}
	for(int i=1;i<=n;i++){
		int now = a[i];
		int opposite = a[(i+n/2 > n ? i+n/2-n : i+n/2)];
		if(now == opposite) ans ++;
	}
	cout << ans;
	return 0;
}

```

---

