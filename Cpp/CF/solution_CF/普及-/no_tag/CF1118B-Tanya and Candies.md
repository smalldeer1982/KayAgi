# Tanya and Candies

## 题目描述

Tanya has $ n $ candies numbered from $ 1 $ to $ n $ . The $ i $ -th candy has the weight $ a_i $ .

She plans to eat exactly $ n-1 $ candies and give the remaining candy to her dad. Tanya eats candies in order of increasing their numbers, exactly one candy per day.

Your task is to find the number of such candies $ i $ (let's call these candies good) that if dad gets the $ i $ -th candy then the sum of weights of candies Tanya eats in even days will be equal to the sum of weights of candies Tanya eats in odd days. Note that at first, she will give the candy, after it she will eat the remaining candies one by one.

For example, $ n=4 $ and weights are $ [1, 4, 3, 3] $ . Consider all possible cases to give a candy to dad:

- Tanya gives the $ 1 $ -st candy to dad ( $ a_1=1 $ ), the remaining candies are $ [4, 3, 3] $ . She will eat $ a_2=4 $ in the first day, $ a_3=3 $ in the second day, $ a_4=3 $ in the third day. So in odd days she will eat $ 4+3=7 $ and in even days she will eat $ 3 $ . Since $ 7 \ne 3 $ this case shouldn't be counted to the answer (this candy isn't good).
- Tanya gives the $ 2 $ -nd candy to dad ( $ a_2=4 $ ), the remaining candies are $ [1, 3, 3] $ . She will eat $ a_1=1 $ in the first day, $ a_3=3 $ in the second day, $ a_4=3 $ in the third day. So in odd days she will eat $ 1+3=4 $ and in even days she will eat $ 3 $ . Since $ 4 \ne 3 $ this case shouldn't be counted to the answer (this candy isn't good).
- Tanya gives the $ 3 $ -rd candy to dad ( $ a_3=3 $ ), the remaining candies are $ [1, 4, 3] $ . She will eat $ a_1=1 $ in the first day, $ a_2=4 $ in the second day, $ a_4=3 $ in the third day. So in odd days she will eat $ 1+3=4 $ and in even days she will eat $ 4 $ . Since $ 4 = 4 $ this case should be counted to the answer (this candy is good).
- Tanya gives the $ 4 $ -th candy to dad ( $ a_4=3 $ ), the remaining candies are $ [1, 4, 3] $ . She will eat $ a_1=1 $ in the first day, $ a_2=4 $ in the second day, $ a_3=3 $ in the third day. So in odd days she will eat $ 1+3=4 $ and in even days she will eat $ 4 $ . Since $ 4 = 4 $ this case should be counted to the answer (this candy is good).

In total there $ 2 $ cases which should counted (these candies are good), so the answer is $ 2 $ .

## 说明/提示

In the first example indices of good candies are $ [1, 2] $ .

In the second example indices of good candies are $ [2, 3] $ .

In the third example indices of good candies are $ [4, 5, 9] $ .

## 样例 #1

### 输入

```
7
5 5 4 5 5 5 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
4 8 8 7 8 4 4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
9
2 3 4 2 2 3 2 2 4
```

### 输出

```
3
```

# 题解

## 作者：minVan (赞：14)

小学生第 $3$ 次发题解了！！！

看了看楼上大佬们的做法，感觉很麻烦，所以来写一篇题解。

**题目大意**

$\texttt{Tanya}$ 有 $n$ 个糖果，每个糖果都有一个重量 $a$ 。

她打算吃掉其中的 $(n-1)$ 颗糖果并将剩下的一颗给她的爸爸。她吃糖果必须按照编号递增的顺序来吃，每天吃一颗。

她的爸爸只会吃名叫 `good candy` 的糖果。如果第 $i$ 个糖果是 `good candy`，那么， $\texttt{Tanya}$ 在偶数天吃的糖果的重量等于 $\texttt{Tanya}$ 在奇数天吃的糖果的重量。

你的任务是去找 `good candy` 的数量。

**题目思路**

定义一个数组 $sum$ 用来存 $\texttt{Tanya}$ 吃的糖果的奇偶性分别的值，所以数组大小只需定 $2$。

然后定义一个数组 $p$ 用来存爸爸吃的糖果的奇偶性分别的值，所以数组大小也只需定 $2$。

如果 $sum$ 里的奇数的值加上 $p$ 里的偶数的值等于 $sum$ 里的偶数的值加上 $p$ 里的奇数的值，则答案数加 $1$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[200005], ans;
int sum[2];
int p[2];
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		sum[i % 2] += a[i];
	}
	for(int i = 1; i <= n; i++)
	{
		sum[i % 2] -= a[i];
		if(p[0] + sum[1] == p[1] + sum[0])
			ans++;
		p[i % 2] += a[i];
	}
	cout << ans;
	return 0;
}
```

---

## 作者：qpzc (赞：7)

## 题意：
定义某数的 $X$ 表示序列中**取出该数前**的除它之外的所有**奇数**编号的数的和，某数的 $Y$ 表示序列中**取出该数前**的除它之外的所有**偶数**编号的数的和。输出序列中所有满足 $X=Y$ 的数的个数。
## 思路：
我们先枚举每一个数，然后判断该数的 $X$ 是否等于 $Y$。但是如果暴力计算 $X$ 和 $Y$，那么循环一遍再加上计算 $O(n^2)$ 的复杂度绝对超时，所以要做到 $O(1)$ 计算 $X$ 和 $Y$。那么如何做到呢？

观察后可以发现，第 $i$ 个数的 $X$ 即为第 $1 \sim i-1$ 个数中第**奇数个**数的和加上第 $i+1 \sim n$ 个数中第**偶数个**数的和。第 $i$ 个数的 $Y$ 即为第 $1 \sim i-1$ 个数中第**偶数个**数的和加上第 $i+1 \sim n$ 个数中第**奇数个**数的和。因为计算 $X$ 和 $Y$ 只涉及到**一连串**数的和，所以我们可以先预处理出序列中的奇前缀和与偶前缀和，需要计算 $X$ 和 $Y$ 时直接取出处理好的前缀和即可做到 $O(1)$ 计算。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int ji[200005],ou[200005];//奇前缀和数组和偶前缀和数组
int main(){
	int n,ans=0; cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>x,ji[i]=ji[i-1],ou[i]=ou[i-1];//先把上一个数复制过来
		if(i&1)ji[i]+=x;
		else ou[i]+=x;
	}
	for(int i=1;i<=n;i++)
		if(ji[i-1]+(ou[n]-ou[i])==ou[i-1]+(ji[n]-ji[i]))ans++;//判断
	cout<<ans;
	return 0;
}
```

---

## 作者：06ray (赞：4)



首先预处理出每个数的奇前缀和和偶前缀和，奇前缀和就是前i个数中下标为奇数的数的和，偶前缀和同理。

然后枚举每个数，如果删去了这个数，那么它后面的奇偶性将改变，即奇的变偶，偶的变奇。

最后你只要判断那个数的奇前缀和与它后面的偶数之和是不是等于偶前缀和与他后面的奇数之和即可，用前缀和一减就得到了。

代码：

```cpp
#include <iostream>
using namespace std;
int even[200100];
int odd[200100];
int main()
{
	int n;
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		int a;
		cin>>a;
		even[i]=even[i-1];
		odd[i]=odd[i-1];
		if(i%2==1) 
		{
			odd[i]+=a;
		}
		else
		{
			even[i]+=a;
		}
	}//得到奇前缀和与偶前缀和
	int ans=0;
	for(int i=1; i<=n; i++)
	{
		int x=odd[n]-odd[i];
		int y=even[n]-even[i];
		if(x+even[i-1]==y+odd[i-1]) ans++;
	}
	cout<<ans;
	return 0;
}
```




---

## 作者：Purple_Circle (赞：3)

由题意，需要我们判断序列 $a$ 中的"good candy"的数量。

而"good candy"的维护则需要用前缀和优化。

不过由于分奇偶，所以需要两个前缀和，分别维护奇数与偶数。

设 $f1,f2$ 分别为第 $i$ 的奇偶数之和，$s1,s2$ 分别为奇偶前缀和。

则有：$f1=s1_{i-(i\%2)-1}+s2_{n-(n\%2)}-s2_{i-(i\%2)}$。

原因：我们对于 $i$ 号糖果，进行分类讨论：

情况1：
当第 $i$ 天为奇数天，则要加上前一天的 $s1_{i-2}$，后半段也要看奇偶，也就是求闭区间 $[i+1,n-1]$ 的区间和，也就是 $s2_{n-1}-s2_{i-1}$ 或 $s2_n-s2_{i-1}$ ，整理为 $s2_{n-(n\%2)}-s2_{i-1}$。整理一下，为   $s1_{i-2}+s2_{n-(n\%2)}-s2_{i-1}$。

情况2：当第 $i$ 天为偶数天，则为 $s1_{i-1}+s2_{n-(n\%2)}-s2_{i}$。 
 
而取模运算可以很方便的帮助我们分辨奇偶，所以最后整合为 $s1_{i-(i\%2)-1}+s2_{n-(n\%2)}-s2_{i-(i\%2)}$。

而 $f2$ 即为总和减 $(f1+a_i)$，此时只需判断 $f1$ 是否等于 $f2$ 即可，也就是判断 $f1$ 是否等于 $sum-f1-a_i$。

如果是，则第 $i$ 颗糖果可以选作 "good candy"。


代码如下：

```cpp
#include<bits/stdc++.h>
#define rd read()
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}
int n,a[200010],sum,ans;
int s1[200010],s2[100010];
int main(){;
	n=rd;
	for(int i=1;i<=n;i++){
		a[i]=rd;
		sum+=a[i];
		if(i%2){
			s1[i]=s1[i-2]+a[i];
		}else{
			s2[i]=s2[i-2]+a[i];
		}
	}
	for(int i=1;i<=n;i++){
		int f=(s1[i-(i%2)-1]+s2[n-(n%2)]-s2[i-(i%2)]);
		if(f==sum-f-a[i]){
			ans++;
		}
	}
	cout << ans;
	return 0;
}
```

成功挤进 [最优解](https://www.luogu.com.cn/record/90414408)

---

## 作者：Lips (赞：2)

# 自己提交的翻译题，当然要做一下

题目其实不难，暴力的话在 $n\le 2\times 10^5$ 这种数据下妥妥 $T$ 飞，所以，必须以一个 $O(n)$ 的做法来解决，对于枚举到的每一个糖果，以 $O(1)$ 的复杂度查询，想必各位大佬早已想到了一个好用的东西——前缀和。

### 前置芝士：前缀和

当我们要高效查找一个数列 $a$ 中，前 $i$ 项的和为多少时，便可用到`前缀和`来解决。~~自认为，~~ 类似 $dp$ 的思想，定义一个数组 $sum$，其中 $sum_i$ 表示数列前 $i$ 项的和，便有~~状态转移方程~~公式：$sum_i=sum_{i-1}+a_i$。废话不多说了，回到原题吧。

### 正题：

由题意可得一个很简单、清晰思路：从 $1$ 到 $n$ 枚举，如果这个糖果为`good candy`，那么 $ans++$

进一步，一个难题出现了：怎么判断是否为`good candy`。先康一张~~高清手绘~~的图便于理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/pv2qcqho.png)


**注：** 红色为奇数，蓝色为偶数，上面数字为编号，下面数字为糖果重量。

~~当然画图就是为了举栗子的。~~ 若选择编号为 $4$ 的糖果给爸爸，则 $\texttt{Tanya}$ 在奇数天吃的糖果编号为 $1,3,6$，将它们的重量加和便可；若选择编号为 $3$ 的糖果给爸爸，则 $\texttt{Tanya}$ 在奇数天吃的糖果编号为 $1,4,6$。

这样不妨搞 $2$ 个前缀和，一个为 $odd$，代表在奇数天糖果重量前缀和；一个为 $even$，代表在偶数天糖果重量的前缀和。

当第 $i$ 个糖果要给爸爸时，就需分情况讨论。若第 $i$ 个糖果为奇数天要吃的，不难想到，在第 $i$ 个糖果之前的最近的一个糖果便为第 $(i-2)$ 个糖果，将临时变量 $odd\_ans$ （用来存奇数天重量和）加上 $odd_{i-2}$ 便可，后半段也要看 $n$ 的奇偶，若为奇数，便直接求 $[i+1,n-1]$ 区间的和，便可将 $n-1$ 的前缀和（这里指 $even$）减去 $i-1$ 的前缀和，有公式：$even_{n-1}-eve n_{i-1}$，若 $n$ 为偶数，则有公式：$even_n-even_{i-1}$，这里直接可以把两个柿子合并成一个：$even_{n-(n\%2)}-even_{i-1}$。综上加和：$odd\_ans=odd\_ans+odd_{i-2}+(even_{n-(n\%2)}-even_{i-1})$。

同理，若 $i$ 为偶数，便也可得公式：$odd\_ans=odd\_ans+odd_{i-1}+(even_{n-(n\%2)}-even_i)$，这里就不再有过多解释了。

当然也可以把上述两个柿子合并：
$$odd\_ans=odd\_ans+odd_{i-1-(i\%2)}+even_{n-(n\%2)}-even_{i-(i\%2)}$$

~~这样就成功的做完压行工作~~

而偶数天的重量和便为总重量和减奇数天重量和减当天的重量：$even\_ans=sum-odd\_ans-a_i$

比较一下是否相等便可。

$Code:$

```cpp
#include<cstdio>
using namespace std;
const int MAXN=200010;
int n,a[MAXN],odd[MAXN],even[MAXN],sum,ans;
//总个数，重量，奇数，偶数，总和，答案 
inline int read()//快读 
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++) 
	{
		a[i]=read();//输入 
		sum+=a[i];//总重量更新 
		if(i%2) odd[i]=odd[i-2]+a[i];//判断奇偶来做前缀和 
		else even[i]=even[i-2]+a[i];
	}
	for(register int i=1;i<=n;i++)
	{
		int odd_ans=0,even_ans=0;//初始临时变量 
		odd_ans=odd_ans+odd[i-1-(i%2)]+even[n-(n%2)]-even[i-(i%2)];//公式 
		even_ans=sum-odd_ans-a[i];//计算偶数天 
		if(odd_ans==even_ans) ans++;//比较 
	}
	printf("%d\n",ans);//输出 
	return 0;
}
```
~~这道题的难度是橙吧~~


---

## 作者：jiangjiangQwQ (赞：0)

### 思路
这题运用到的算法知识点是前缀和。不了解的可以百度学习，比较容易。我们用两个前缀和数组分别计算奇数和偶数位置上的数的和。在遍历每一个糖果，根据当前位置的奇偶性，在相应的前缀和数组减去它。计算如果这个糖果给爸爸，剩下的奇数位置糖果和偶数位置糖果和是否相同，统计答案。
### 坑点
当我们枚举每一个糖果，这个糖果给爸爸吃。那么这个位置往后的奇数位置会变成 Tanya 吃糖果顺序中的偶数位置，同理偶数位置变成奇数位置。解决的方法是将后面本应是奇数位置的变成统计后面偶数位置的和。偶数位置同理。
### 代码
```cpp
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define int long long
#define re register
#define For(i,l,r) for(re int i=l;i<=r;i++)
#define Rep(i,l,r) for(re int i=l;i>=r;i--)
const int N=3e5+5;
inline void fast() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int n,suma[N],sumb[N],a[N],ans;
int getsum(int l,int r,int p) {
	return (p==1?suma[r]-suma[l-1]:sumb[r]-sumb[l-1]);
}
signed main() {
	fast();
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		if(i&1) suma[i]=suma[i-1]+a[i],sumb[i]=sumb[i-1];
		else suma[i]=suma[i-1],sumb[i]=sumb[i-1]+a[i];
	}
	for(int i=1; i<=n; i++) {
		int t=getsum(1,i-1,1)+getsum(i+1,n,2);
		int k=getsum(1,i-1,2)+getsum(i+1,n,1);
		ans+=(t==k);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：EDqwq (赞：0)

非常显然的一点，当你拿走了一个糖之后，这个糖后面的糖的奇偶会全部相反。

所以我们记录一下奇偶糖的后缀和，然后枚举拿走哪一个糖，最后把奇偶改变判断一下即可。

具体就是，一开始两个记录奇偶的变量为原来的奇偶的和，然后我们枚举到一个糖果，就把记录奇的变量减去后面的和，加上偶数和，记录偶的同理。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n;
int a[200010];
int pre1[200010];
int pre2[200010];
int ans;
int ans1,ans2;

signed main(){
	cin>>n;
	for(int i = 1;i <= n;i ++)a[i] = read();
	for(int i = n;i >= 1;i --){
		if(i % 2 == 1)pre1[i] = pre1[i + 2] + a[i],pre2[i] = pre2[i + 1];
		else pre2[i] = pre2[i + 2] + a[i],pre1[i] = pre1[i + 1];
	}
//	cout<<pre1[2]<<" "<<pre2[2]<<endl;;
	ans1 = pre1[1];
	ans2 = pre2[1];
//	cout<<ans1<<" ans1ans2 "<<ans2<<endl;
	for(int i = 1;i <= n - 1;i ++){
		ans1 -= pre1[i + 1];
		ans1 += pre2[i + 1];
		ans2 -= pre2[i + 1];
		ans2 += pre1[i + 1];
		if(i % 2 == 1)ans1 -= a[i];
		else ans2 -= a[i];
		if(ans1 == ans2)ans ++;
		ans1 = pre1[1];
		ans2 = pre2[1];
	}
	ans1 = ans2 = 0;
	for(int i = 1;i <= n - 1;i ++){
		if(i % 2 == 1)ans1 += a[i];
		else ans2 += a[i];
	}
	if(ans1 == ans2)ans ++;
	cout<<ans;
}
```

---

## 作者：Xdl_rp (赞：0)

一看数据 $1≤n≤2 \times 10^5$ 就知道暴力一定过不了。

但是一看那些区间的操作，不禁想到了一个神奇的东西，

前缀和！

这样就可以 $O(1)$ 查询每一个和啦！

进入正题：
- 首先定义两个数组 $even,odd$ 
- 状态转移方程 $even_i=even_{i-1}+a_i$ 和 $odd_i=odd_{i-1}+a_i$

代码区：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005];
int even[200005], odd[200005];
int read() {
	char c = getchar();
	int g = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') g = (g << 1) + (g << 3) + (c ^ 48), c = getchar();
	return g;
}/*快读没啥用*/
int main() {
	int n, ans = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		even[i] = even[i - 1], odd[i] = odd[i - 1];
		if (i % 2 == 1) odd[i] += a[i];
		else even[i] += a[i];
	}//输入和前缀和
	for (int i = 1; i <= n; i++) {
		if (odd[n] - odd[i] + even[i - 1] == even[n] - even[i] + odd[i - 1]) ans++;//累加，如果是就计数器加一
	}
	cout << ans;
	return 0;
}
```


---

## 作者：WinterRain208 (赞：0)

CF1118B 【Tanya and Candies】

这题就是一个枚举，只不过在枚举每个数时需要用到前面若干个数字的和。

其实也很好做，用前缀和即可，注意要把编号为奇数的和编号为偶数的分开记录。

用两个前缀和数组即可。

### $CODE$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,r) for(int i=j;i<=r;++i)
#define D(i,j,r) for(int i=j;i>=r;--i)
#define INF 0x3f3f3f3f

using namespace std;
const int N=1e5+5;

long long read(){
	long long f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<3)+(x<<1)+s-'0';s=getchar();}
	return x*f;
}

ll even[200100],odd[200100];
ll n,a,ans=0; 
int main(){
	n=read();
	F(i,1,n){
		a=read();
		even[i]=even[i-1],odd[i]=odd[i-1];
		if(i%2)odd[i]+=a;
		else even[i]+=a;
	}
	F(i,1,n){
		ll x=odd[n]-odd[i],y=even[n]-even[i];
		if(x+even[i-1]==y+odd[i-1])++ans;
	}
	printf("%lld",ans);
    return 0;
}

```
完结撒花。

---

