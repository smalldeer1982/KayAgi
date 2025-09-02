# Makes And The Product

## 题目描述

After returning from the army Makes received a gift — an array $ a $ consisting of $ n $ positive integer numbers. He hadn't been solving problems for a long time, so he became interested to answer a particular question: how many triples of indices $ (i, j, k) $ ( $ i&lt;j&lt;k $ ), such that $ a_{i}·a_{j}·a_{k} $ is minimum possible, are there in the array? Help him with it!

## 说明/提示

In the first example Makes always chooses three ones out of four, and the number of ways to choose them is $ 4 $ .

In the second example a triple of numbers $ (1,2,3) $ is chosen (numbers, not indices). Since there are two ways to choose an element $ 3 $ , then the answer is $ 2 $ .

In the third example a triple of numbers $ (1,1,2) $ is chosen, and there's only one way to choose indices.

## 样例 #1

### 输入

```
4
1 1 1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 3 2 3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
6
1 3 3 1 3 2
```

### 输出

```
1
```

# 题解

## 作者：Coros_Trusds (赞：2)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15431544.html)

考前写题解 $\rm rp++$。

# 题目大意

给定 $n$ 个数 $a[1\cdots n]$ 问你满足 $a[i]\times a[j]\times a[k]$ 的值最小，且 $i<j<k$ 的有序对有几个？

# 题目分析

很妙的一道题。

来一个 $\operatorname{O(n~log~n)}$ 的做法。

看到求三个数相乘的最小值，再看到 $3\le n\le10^5$ 的数据范围，妥妥的 $\log~n$ 啊！

可以马上想到将数组升序排列一遍，然后看整段序列有多少个数与 $a[3]$ 相等，答案即为 $tmp$。

接下来分类讨论：

* 当 $a[1]=a[2]=a[3]$ 时，直接在 $tmp$ 里选 $3$ 个数出来即可。

答案为 

$$C_{tmp}^3$$

$$=\dfrac{tmp!}{(tmp-3)!\times 3!}$$

$$=\dfrac{tmp\times(tmp-1)\times(tmp-2)\times\cdots\times 2\times1}{(tmp-3)\times(tmp-4)\times\cdots\times2\times1\times3\times2\times1}$$

$$=\dfrac{tmp\times(tmp-1)\times(tmp-2)}{3\times2\times1}$$

* 当 $a[1]\neq a[2]$ 但 $a[2]=a[3]$ 时，第一个必然应该选择，剩下的就从 $tmp$ 中选 $2$ 个出来即可。

答案为

$$C_{tmp}^2$$

$$=\dfrac{tmp!}{(tmp-2)!\times2!}$$

$$=\dfrac{tmp\times(tmp-1)}{2\times1}$$

* 其他情况。

这个时候，前两个数必然应该选择，剩下一个数直接在 $tmp$ 里任意选 $1$ 个即可。

故此时输出 $tmp$。

# 代码

```cpp
const int ma=100005;

int a[ma];

int n;

#undef int

int main(void)
{
	#define int long long
	
	n=read();
	
	for(register int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	
	sort(a+1,a+n+1);
	
	int tmp=0;
	
	for(register int i=1;i<=n;i++)
	{
		if(a[i]==a[3])
		{
			tmp++;
		}
	}
	
	if(a[1]==a[2] && a[2]==a[3])
	{
		printf("%lld\n",tmp*(tmp-1)*(tmp-2)/(3*2*1));
	}
	
	else if(a[2]==a[3])
	{
		printf("%lld\n",tmp*(tmp-1)/2);
	}
	
	else
	{
		printf("%lld\n",tmp);
	}
	
	return 0;
}
```

你看我熬夜写的这么认真，不点个赞吗 $\mathcal{QwQ}$。

---

## 作者：sto__Liyhzh__orz (赞：1)

很水一道题。

[题目传送门：](https://www.luogu.com.cn/problem/CF817B)

（~~`Liyhzh` 敲可爱的啦！~~）

**我的思路**：

显而易见，我们将原数组从小到大排序后，得到数组 $b$，最小值应为 $b_1 \times b_2 \times b_3$。

那最小值出现次数怎么求呢？

别急，`Liyhzh` 敲可爱的啦！所以：

我们设最小值出现次数为 $x$，次小值出现次数为 $y$，次次小值出现次数为 $z$。

* 若 $x \ge 3$，则全部选择最小值，有 $C^3_x$ 种。

* 若 $x = 2$，则只用在 $y$ 个次小值中选择一个，方案数为 $y$ 种。

* 若 $x = 1$，

  我们继续分类：
  
    * $y \ge 2$，则需在 $y$ 个次小值中选择 $2$ 个，方案数为 $C^2_y$ 种。
    
    * $y=1$，则只用在 $z$ 个次次小值中选择一个，方案数为 $z$ 种。
    
代码：

**不开 `long long` 见祖宗！！！**

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;
const db eqs=1e-6;
const int inf=1e9;
void cmax(int &a,int b){a=max(a,b);}
void cmin(int &a,int b){a=min(a,b);}
bool db_eq(db a,db b){return fabs(a-b)<eqs;}

const int MAXN=100000+5;
int a[MAXN],n;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	ll cnt1=0,cnt2=0,cnt3=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]==a[1]) ++cnt1;
		if(a[i]==a[2]) ++cnt2;
		if(a[i]==a[3]) ++cnt3;
	}
	if(cnt1>=3) cout<<cnt1*(cnt1-1)*(cnt1-2)/6<<endl;
	else if(cnt1==2) cout<<cnt3<<endl;
	else 
	{
		if(cnt2>=2) cout<<cnt2*(cnt2-1)/2<<endl;
		else cout<<cnt3<<endl; 
	}
	return 0;
}
```

---

## 作者：Strelitzia_ (赞：1)

## 题目大意

给出一个序列 $\{a_n\}$，求三元组 $\{i,j,k\}$ 满足 $1\le i<j<k\le n$ 且使 $a_i\times a_j\times a_k$ 最小的个数。

------------
## 思路

我们先考虑如何使 $a_i\times a_j\times a_k$ 最小。因为对于任意的 $1\le i\le n$ 都有 $a_i\ge 1$，所以方法是显然的：将序列按数值升序排列，选前三个数即可满足乘积最小。

现在我们考虑怎么统计答案。我们分类讨论：

+ 设 $c$ 为最小的数的数量，若 $c\ge 3$，那么就是 $c$ 个选 $3$ 个，根据排列组合有答案为 $\dbinom{c}{3}$，即 $\dfrac{c(c-1)(c-2)}{6}$；
+ 若 $c=2$，那么设次小值有 $b$ 个，答案就是 $b$ 个选 $1$ 个，答案就是 $b$；
+ 若 $c=1$，那么我们再分类。如下：

------------

- 若 $b>1$，那么答案就是 $b$ 个选 $2$ 个，与第一种情况同理有答案为 $\dfrac{b(b-1)}{2}$；
- 若 $b=1$，设次次小值个数为 $d$，与第二种情况同理有答案为 $d$。

在实现上，我们直接使用 `map<int, int>` 记录每个数出现的次数，便于查询；再将序列排个序，然后大力分类讨论即可。

代码如下：

```cpp
int a[N], n, ans;
map<int, int> mp;
signed main() {
	n = slow_IO::read();
	for (int i = 1; i <= n; i++) a[i] = slow_IO::read(), mp[a[i]]++;
	sort(a + 1, a + n + 1);
	if (mp[a[1]] >= 3) return printf("%lld\n", mp[a[1]] * (mp[a[1]] - 1) * (mp[a[1]] - 2) / 6), Strelitzia_;
	if (mp[a[1]] == 2) return printf("%lld\n", mp[a[3]]), Strelitzia_;//没去重，所以此时 a[3] 为次小值
	if (mp[a[1]] == 1) {
		if (mp[a[2]] == 1) return printf("%lld\n", mp[a[3]]), Strelitzia_;
		return printf("%lld\n", (mp[a[2]] - 1) * (mp[a[2]]) / 2ll), Strelitzia_;
	}
	return Strelitzia_;
}
```

---

## 作者：wzy2021 (赞：1)

我们来看一下这道题：

1. 先排序，显然前三个的积是最小的 （$a[i]$ > 0）

2. 设最小三个为 $a[1]$ , $a[2]$ , $a[3]$ ，记 $ans$ 为序列中有多少个与 $a[3]$ 相同

3. 结果需分情况讨论：

- 若$a[1] = a[3]$ ，即最小三个相同，只要从序列中与 $a[3]$ 相同的数中取三个，可得答案：$ans * (ans - 1) * (ans - 2) ÷ 6$  

- 若不满足以上条件，$a[2] = a[3]$ ，那么 $a[1]$ 必须选，再从与 $a[3]$ 相同的数中取两个，可得答案：$ans * (ans - 1) ÷ 2$

- 若不满足以上条件，即都是前两个必须选，再从与 $a[3]$ 相同的数中取一个，可得答案：$ans$ 

具体可看代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long

int a[100010];

signed main() {
	int n, ans = 0; cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	} 
	sort (a + 1, a + n + 1); // 排序
	for (int i = 1; i <= n; ++i) {
		if (a[i] == a[3]) ans ++;
	} // 找出于 a[3] 相同的数有多少个
	if (a[1] == a[3]) cout << ans * (ans - 1) * (ans - 2) / 6 << endl; // 第一种情况
	else if (a[2] == a[3]) cout << ans * (ans - 1) / 2 << endl; // 第二种情况
	else cout << ans << endl;
	return 0; // 以三种情况
}
```


---

## 作者：Catcats (赞：1)

[题目传送门](/problem/CF817B)

### 题面简化

给定一个长为 $n$ 的有序序列 $a$，求 同时满足 $a_ia_ja_k$ 是所有序列中的任意三个数的乘积中最小的，且 $i<j<k$ 的三元组 $(i,j,k)$ 的个数。

### 思路

梳理一下重要信息：
1. 让 $a_ia_ja_k$ 最小，那么 $a_i,a_j,a_k$ 就得分别是前三个。
2. $i,j,k$ 有序。
3. $a_i,a_j,a_k$ 可能相同。

又因为 $a$ 的原始序列与排序后都要保留，那么应该有个想法：

用 $2$ 个数组 $a,b$ 存储原始序列与排序后的序列，再用一个 $ans$ 数组存储前 $3$ 小的出现次数，再代入组合数公式。

那具体如何代呢？可以**分情况讨论**。

令 $x,y,z$ 为前三个数，$r,s,t$ 为 $x,y,z$ 的出现次数。

- $x=y=z$：$3$ 个数相当于无序，那么答案是 $\text{C}_r^3=\frac{r(r-1)(r-2)}{6}$。
- $x=y<z$：$x$ 与 $y$ 一样，可以看作 $\text{C}_r^2$，则总数是 $\text{C}_r^2\times t=\frac{r(r-1)t}{2}$。
- $x<y=z$：与 $x=y<z$ 类似，总数是 $\text{C}_t^2\times r=\frac{t(t-1)r}{2}$。
- $x<y<z$：$3$ 个数都不相等，即有序，总数是 $rst$。

### 代码

讲了这么多，让我们看看代码实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    #define int unsigned long//此题有较大结果的乘法，要开ll
	int n;cin>>n;
    int a[n+1],b[n+1],ans[4]={0};//a是排序前，b是排序后,ans是前三小的次数
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(int i=n;i;i--){//统计前三小的个数，ans[1],ans[2],ans[3]相当于讲解里的r,s,t
		if(a[i]==b[1])ans[1]++;
		if(a[i]==b[2])ans[2]++;
		if(a[i]==b[3])ans[3]++;
	}
	cout<<(b[1]==b[3]/*三个数相等*/?ans[1]*(ans[1]-1ll)*(ans[1]-2ll)/6ll:b[1]==b[2]/*前两个相等*/?ans[3]*ans[2]*(ans[2]-1ll)/2ll:b[2]==b[3]/*后两个相等*/?ans[1]*ans[2]*(ans[2]-1ll)/2ll:/*都不相等*/ans[1]*ans[2]*ans[3]);
}
```

---

## 作者：InversionShadow (赞：0)

首先排序。

记 $k$ 表示 $\sum\limits_{i=1}^{n}[a_i=a_3]$。

+ $a_1=a_3$ 

表示前三小相同，那么只要从序列中与 $a_3$ 相同的数中取三个，即 $C_{k}^3=\dfrac{k\times (k-1)\times(k-2)}{6}$。

+ $a_1\neq a_3$，但是 $a_2=a_3$

那么 $a_1$ 必须取，从 $k$ 中取 $2$ 个数，即 $C_{k}^2=\dfrac{k\times (k-1)}{2}$。

+ 否则，就是前两个都选，从 $k$ 中取 $1$ 个数，即 $C_{k}^1=k$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 100;

int n, a[N];

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int ans = 0;
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    ans += (a[i] == a[3]);
  }
  if (a[1] == a[3]) {
    cout << ans * (ans - 1) * (ans - 2) / 6;
  } else if (a[2] == a[3]) {
    cout << ans * (ans - 1) / 2;
  } else {
    cout << ans;
  }
  return 0;
}
```

---

## 作者：kdy20100729 (赞：0)

## 题意简述：  
给你 $n$ 个数 $a_1,a_2,a_3...a_n$。问满足 $a_i \times a_j \times a_k$ 的值最小，且 $i<j<k$ 的有序对有几个。

## 解题思路：  
首先给这 $n$ 个数字排序，我们得到最小的三个数字 $b_1,b_2,b_3$。  
经过思考，可以联想到这肯定和排列组合有关。
>+ 最简单的情况是这三个数字互不相同，那么方案数就是这三个数字出现次数的乘积，即 $suf_1 \times suf_2 \times suf_3$。  
>+ 如果这三个数字全部一样呢，那么问题变成了从 $suf_1$ 个中选 $3$ 个，即 $C_{suf_1}^{3}$。  
>+ 如果这三个数字中 $b_1=b_2$ 呢，那么问题变成了从 $suf_1$ 中选 $2$ 个，$suf_3$ 中选 $1$ 个，即 $C_{suf_1}^2 \times suf_3$。  
>+ 如果这三个数字中 $b_2=b_3$ 呢，与上面类似，问题变成了从 $suf_2$ 中选 $2$ 个，$suf_1$ 中选 $1$ 个，即 $C_{suf_2}^2 \times suf_1$。

至此，所有情况讨论完毕。

## Code:  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,suf[15],a[100005],b[100005];
signed main()
{
    cin >> n;
    for(int i=1; i<=n; i++)
    {
        cin >> a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);//排序获取最小的 3 个数字
    for(int i=n; i>=1; i--)//分别统计第 1 小的数字、第 2 小的数字、第 3 小的数字出现了多少次
    {
        if (a[i]==b[1])
            suf[1]++;
        if (a[i]==b[2])
            suf[2]++;
        if (a[i]==b[3])
            suf[3]++;
    }
    //分类讨论
    if (b[1]==b[3])//三个数字都相同
        ans=suf[1]*(suf[1]-1)*(suf[1]-2)/6;
    else if (b[1]==b[2])//前两个数字相同
        ans=suf[3]*suf[1]*(suf[1]-1)/2;
    else if (b[2]==b[3])//后两个数字相同
        ans=suf[1]*suf[2]*(suf[2]-1)/2;
    else//三个数字都不相同
        ans=suf[1]*suf[2]*suf[3];
    cout << ans;
    return 0;
}
```

---

## 作者：SalomeJLQ (赞：0)

2021.5.8 Update：把非公式 LaTeX删了

### 推荐难度：绿

看到这题，我们要求三个数 $a_i,a_j,a_k$ 乘积最小，有一点可以肯定的是这三个数的数值无论如何选都是不变的。

因此我们对数组排序、离散化并映射到一个桶中，然后我们对桶中的数据分类讨论。

因为是有序对，所以这是一个组合问题。依次考虑桶b中 $b_1,b_2,b_3$ 三项即可。

- $b_1>2$，此时对 $b_1$ 进行三个数的组合即可。
- $b_1=2$，此时对 $b_1$ 进行两个数的组合，对 $b_2$ 进行一个数的组合，相乘即可。
- $b_1=1$ 且 $b_2=1$，直接对 $b_3$ 进行一个数的组合。
- $b_1=1$ 且 $b_2>1$，对 $b_2$ 进行两个数的组合。

综上，每次读入都排序、离散化、映射入桶中，然后分类计算组合数即可。值得注意的是此题需要开long long。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
const int N=100005;
ll a[N],b[N],n,m,ans;
void discrete(){
	sort(a+1,a+n+1);
	memset(b,0,sizeof(b));
	ans=0,m=0;
	for(int i=1;i<=n;i++)
		if(a[i]!=a[i-1])b[++m]++;	
		else b[m]++;
}
int main(){
	while(cin>>n){
		for(int i=1;i<=n;i++)a[i]=read();
		discrete();
		if(b[1]>=3)ans=b[1]*(b[1]-1)*(b[1]-2)/6;
		if(b[1]==1){
			if(b[2]==1)ans=b[3];
			if(b[2]>=2)ans=b[2]*(b[2]-1)/2;
		}
		if(b[1]==2)ans=b[2];
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

