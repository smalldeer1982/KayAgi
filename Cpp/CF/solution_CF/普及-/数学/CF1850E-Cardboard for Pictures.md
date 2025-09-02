# Cardboard for Pictures

## 题目描述

Mircea有n张照片。第i张照片是一个边长为si厘米的正方形。

他将每张照片装在一个正方形的纸板上，使得每张照片的四周都有w厘米的纸板边框。总共，他使用了c平方厘米的纸板。根据照片的尺寸和c的值，你能找出w的值吗？
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1850E/8be93a707152c424940afd3c547aecafb34ece9f.png)
c=50=5²+4²+3²，所以w = 1 是本题目的答案。请注意，纸板的一角会出现在每张图片的后面，而不仅仅是边框上。

## 说明/提示

```
在第一个测试用例中，根据题目给出的例子
```
我们需要使用1张照片，因此可以选择任意宽度的边框w。

在第二个测试用例中，假设我们选择的宽度w为22，那么每张照片需要的纸板面积为(2w+6)^2=10^2=100平方厘米。
```
在第三个测试用例中，假设我们选择的宽度w为44，那么每张照片需要的纸板面积为
```
(2w+2)^2×5=10^2×5=100×5=500平方厘米。

## 样例 #1

### 输入

```
10
3 50
3 2 1
1 100
6
5 500
2 2 2 2 2
2 365
3 4
2 469077255466389
10000 2023
10 635472106413848880
9181 4243 7777 1859 2017 4397 14 9390 2245 7225
7 176345687772781240
9202 9407 9229 6257 7743 5738 7966
14 865563946464579627
3654 5483 1657 7571 1639 9815 122 9468 3079 2666 5498 4540 7861 5384
19 977162053008871403
9169 9520 9209 9013 9300 9843 9933 9454 9960 9167 9964 9701 9251 9404 9462 9277 9661 9164 9161
18 886531871815571953
2609 10 5098 9591 949 8485 6385 4586 1064 5412 6564 8460 2245 6552 5089 8353 3803 3764```

### 输出

```
1
2
4
5
7654321
126040443
79356352
124321725
113385729
110961227```

# 题解

## 作者：Andy_Li (赞：9)

# CF1850E Cardboard for Pictures 题解
### 题意
给定 $t$ 组数据，对于每组数据，给定 $n,c$ 和长度为 $n$ 的序列 $a$。求一个整数 $w$，使得 $ \sum \limits_{i=1}^{n}(a_i+2w)^2=c$。 

### 思路
赛后看到很多人使用二分，但是做为一个学了二分和没学一样的蒟蒻，我还是选择推数学式子。

通过读题，我们知道：$ \sum \limits_{i=1}^{n}(a_i+2w)^2=c$。
 
利用完全平方公式 $(a+b)^2=a^2+2ab+b^2$，

我们推出：
$$c= \sum \limits_{i=1}^{n}{a_i}^2 + \sum \limits_{i=1}^{n} 4 \times a_i \times w + 4 \times n \times w^2$$

我们设 $sq=\sum \limits_{i=1}^{n}{a_i}^2$,$ sum=\sum \limits_{i=1}^{n} a_i $。

所以刚才推的式子就可以化简为：
$$c=sq + 4 \times sum \times w + 4 \times n \times w^2$$

接着化简：

$$ c-sq = 4 \times sum \times w + 4 \times n \times w^2 $$

$$ c-sq = n \times (2 \times w)^2+4 \times sum \times w $$

$$ \frac{c-sq}{n} = (2 \times w)^2 + \frac{4 \times w \times sum}{n} $$

$$ \frac{c-sq}{n} + \frac{sum}{n}^2 = (2 \times w)^2 + \frac{2 \times (2 \times w) \times sum}{n} + ( \frac {sum}{n})^2 $$

$$ \frac{c-sq}{n} + ( \frac{sum}{n})^2 = (2 \times w + \frac{sum}{n})^2 $$

$$ \sqrt{ \frac{c-sq}{n} + ( \frac{sum}{n})^2} = 2 \times w + \frac{sum}{n} $$

$$ \sqrt{ \frac{c-sq}{n} + ( \frac{sum}{n})^2} - \frac{sum}{n} = 2 \times w $$

$$ \frac{\sqrt{ \frac{c-sq}{n}+( \frac{sum}{n})^2} - \frac{sum}{n}}{2} = w $$

**所以最后的式子就是：**
$$ w = \frac{\sqrt{ \frac{c-sq}{n}+( \frac{sum}{n})^2} - \frac{sum}{n}}{2} $$

### 赛时代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		ll n,c;
		cin>>n>>c;
		ll sq=0,sum=0;
		for(int i=1;i<=n;i++)
		{
			ll x;
			cin>>x;
			sq+=x*x;
			sum+=x;
		}
		cout<<(ll)floor((sqrt((c-sq)/n+(sum*sum)/(n*n))-sum/n)/2)<<endl; 
	}
	return 0;
}  
```

感谢 [mahaoming](https://www.luogu.com.cn/user/399051) 提供的思路。

---

## 作者：_Only_this (赞：5)

### CF1850E Cardboard for Pictures 题解

------------

一道二分的水题竟然调了我 40 分钟......

仔细读题后不难发现，边框宽度越宽，总面积就越大，而且宽到一定限度之后总面积就 $>c$ 了，在之后总面积只会越来越大，没有 $\leq c$ 的可能性，因此本题具有单调性，考虑二分答案。

但是要注意越界的情况，开 long long 也存在越界的可能。

最后附上代码，

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5+5;
int T,n;
ll S;
int a[maxn];
ll Sq(ll x){
	return x*x;
}
bool Check(ll x){
	x<<=1;
	ll tot=0,SS=S;
	for(int i=1;i<=n;i++){
		if(a[i]+x>(ll)sqrt(S)){
			S=SS;
			return 0;
		}
			
		S-=Sq(a[i]+x);
	}
	S=SS;
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld",&n,&S);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		ll l=1,r=1e18,mid,ans;
		while(l<=r){
			mid=l+r>>1;
			if(Check(mid))
				l=mid+1,ans=mid;
			else
				r=mid-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：_sunkuangzheng_ (赞：4)

**【题目大意】**

长度为 $n$ 的正整数序列 $a$，求一个整数 $w$，满足 $\sum \limits_{i=1}^n(a_i+w)^2 = c$。$1 \le n \le 2 \times 10^5,1\le a_i \le 10^4,1 \le c \le 10^{18}$。

**【题目分析】**

注意随着 $w$ 的上升原式的值单调上升，因此可以二分答案。每次二分 $w$，$\Theta(n)$ 判断原式的值比 $c$ 大或小，调整二分区间。

为保险开了 `__int128`。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define iint __int128
int t,n,a[500005],cc,k;
iint b[500005],c;
iint check(iint s){
    iint ans = 0;
    for(iint i = 1;i <= n;i ++) ans += (b[i] + 2 * s) * (b[i] + 2 * s);
    if(ans == c) return 1;
    if(ans < c) return 0;
    return 2;
}
signed main(){
    cin >> t;
    while(t --){
        cin >> n >> cc,c = cc;
        for(int i = 1;i <= n;i ++) cin >> a[i],b[i] = a[i];
        iint l = 1,r = 1e9,ans = 0;
        while(l <= r){
            iint mid = (l + r) / 2;
            if(check(mid) == 1) {ans = mid;break;}
            else if(check(mid) == 0) l = mid + 1;
            else r = mid - 1;
        }
        cout << (int)ans << "\n";
    }
}
```

---

## 作者：xlpg0713 (赞：3)

题意简介：你有 $n$ 张正方形照片，第 $i$ 张照片的边长为 $s_i$。现在每一张照片都有一个宽为 $x$ 的边框。现在已知所有照片和边框的面积和 $c$。求出 $x$。

考虑数学解法。一张边长为 $s$ 的边框宽为 $x$ 的照片所占据的面积应为 $(s+2x)^2$ 化简得  $s^2+4sx+4x^2$。 

由于 $s$ 已知，我们可以得到关于 $x$ 的二元一次方程： $\sum\limits_{i=1}^ns_i^2+4s_ix+4x^2=c$。

再化简得：$4nx^2+\sum\limits_{i=1}^n4s_ix+(\sum\limits_{i=1}^ns_i^2-c)=0$。

对其进行方程求解即可。

```cpp
#include<bits/stdc++.h>
#define int __int128//这种做法不开__int128会寄
using namespace std;
int n, t, c, s, p, q; // px^2 + qx = c
void scan(__int128 &x){
    x = 0;
    int f = 1;
    char ch;
    if((ch = getchar()) == '-') f = -f;
    else x = x*10 + ch-'0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = x*10 + ch-'0';
    x *= f;
}
void print(__int128 x){
    if(x < 0) {
        x = -x;
        cout << '-';
    }
    if(x > 9) print(x/10);
    putchar(x%10 + '0');
}
inline void solve(){
	scan(n); scan(c); p = q = 0;
    for(int i = 1; i <= n; i++){
        scan(s); c -= s * s;
        p += 4; q += 4 * s;
    }
    c /= 4; p /= 4; q /= 4;
    int ans = (int)((-q+sqrt(double(q*q+4*p*c)))/(2*p));//带入求解公式
    print(ans); cout << '\n'; return;
}
signed main(){
   	scan(t);
   	while(t--)solve();
		return 0;
}

```

---

## 作者：zhicheng (赞：3)

### 思路

将题目条件转化后就是

$$\sum\limits_{i=1}^{n} (s_i+2w)^2=c$$

化简得


$$\sum\limits_{i=1}^{n}s_i^2+4nw^2+4w\sum\limits_{i=1}^{n}s_i=c$$


预处理出 $\sum\limits_{i=1}^{n}s_i^2$ 和 $\sum\limits_{i=1}^{n}s_i$ 后（以下记作 $p$、$sum$）把 $w$ 作为未知数带入二次方程求根公式即可。

有：

$$4nw^2+4w\times sum+p-c=0$$

所以：

$$w=\dfrac{-4sum \pm \sqrt{16sum^2-16n(p-c)}}{8n}$$

舍去负根，也即

$$w=\dfrac{-sum + \sqrt{sum^2+n(c-p)}}{2n}$$

实现的时候要写成

$$w=\sqrt{\dfrac{sum^2}{4n^2}+\dfrac{c-p}{4n}}-\dfrac{sum}{2n}$$

不然会爆 long long。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200010],sum[200010],p[200010];
int main(){
	int t,n;
	long long c;
	scanf("%d",&t);
	while(t--){
		scanf("%d%lld",&n,&c);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			sum[i]=sum[i-1]+a[i];  //预处理
			p[i]=p[i-1]+a[i]*a[i];
		}
        //计算答案
		printf("%lld\n",((long long)sqrt(sum[n]*sum[n]/4/n/n+(c-p[n])/4/n)-sum[n]/2/n));
	}
}
```

---

## 作者：cjh20090318 (赞：3)

## 题意

给你 $n$ 个整数 $s$ 和一个整数 $c$，你需要找到一个整数 $w$ 满足 $\sum\limits_{i=1}^n(2w+s_i)^2=c$。

## 分析

很显然这是一个一元二次方程。

将上式根据完全平方公式化简可以得到，我们要求的方程是：
$$
4nw^2+(2\sum\limits_{i=1}^ns_i)w+\sum\limits_{i=1}^ns_i^2=c
$$
移项又可以得到：
$$
4nw^2+(2\sum\limits_{i=1}^ns_i)w+(\sum\limits_{i=1}^ns_i^2)-c=0
$$
所以直接用求根公式可以解得：
$$
w=\dfrac{-2\sum\limits_{i=1}^ns_i+\sqrt{4(\sum\limits_{i=1}^ns_i)^2-16n\sum\limits_{i=1}^ns_i^2}}{8n}
$$

## 注意事项

可能需要用到 `__int128`，需要使用 C++20，并且需要手写 `sqrt` 函数。（但是 `long double` 强转好像也可以过）。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
typedef long long LL;
int n;LL c;
__int128 mySqrt(__int128 x){if(!x)return 0;__int128 left=1;__int128 right=x>>1;while(left<right){__int128 mid=(right+left)/2+1;if(mid>x/mid) right=mid-1;else left=mid;}return(__int128)left;}//手写二分 sqrt。
void solve(){
	scanf("%d%lld",&n,&c);
	LL A=(n<<2),B=0,C=0;//一元二次方程的三个系数。
	for(int i=1,s;i<=n;i++){
		scanf("%d",&s);
		B+=s,C+=s*s;
	}
	B<<=2ll;
	printf("%lld\n",LL((-B+mySqrt((__int128)B*B-(__int128)4*A*(C-c)))/2/A));//根据求根方程求解。
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve(); 
	return 0;
}
```



---

## 作者：fengxiaoyi (赞：2)

先将 $c$ 减去 $\displaystyle\sum_{i=1}^n s_i$，那么得到的 $c$ 就是空白部分的总面积。

#### 接下来考虑怎么求空白部分的总面积

![](https://cdn.luogu.com.cn/upload/image_hosting/c1575ibv.png)

将每个图片抽象成上图，红色部分的面积就是空白部分的面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/3huzrorz.png)

蓝色的线就表示空白部分的宽 $w$，由图可得 $S_{i}=4\times w^2+4\times w \times s_i$（$S_{i}$ 表示第 $i$ 张图的空白部分的面积）。

那么，空白部分的总面积为
$$\displaystyle\sum_{i=1}^n S_i=\displaystyle\sum_{i=1}^n 4\times w^2+4\times w \times s_i$$
$$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =4\times n\times w^2+4\times w\times \displaystyle\sum_{i=1}^n s_i$$
其中 $\displaystyle\sum_{i=1}^n s_i$ 可以预处理得到。

显然，$\displaystyle\sum_{i=1}^n S_i$ 具有单调性，考虑二分答案 $w$，套用上面的公式算即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s[200010];
long long c;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%lld",&n,&c);
		long long o=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&s[i]);
			c-=1ll*s[i]*s[i];
			o+=1ll*s[i];
		}
		long long l=1,r=c+1;
		while(l<r-1){
			long long mid=l+r>>1;
			if(c/mid/4/n<mid){
				r=mid;
				continue;
			}
			long long h=c-1ll*mid*mid*4*n;
			if(h/o/4<mid){
				r=mid;
				continue;
			}
			l=mid;
		}
		printf("%lld\n",l);
	}
	return 0;
}
```


---

## 作者：Crazyouth (赞：2)

**翻译**

给定正整数列 $s$ 与正整数 $c$，求一个正数 $w$ 使 $\displaystyle\sum_{i=1}^{n}(s_i+2w)^2=c$。

**分析**

考虑数学做法。将原式用完全平方公式展开得 $\displaystyle\sum_{i=1}^ns_i^2+4w\cdot\displaystyle\sum_{i=1}^n s_i+4nw^2=c$，整理为一元二次方程基本形式：$4n\cdot w^2+(4\displaystyle\sum_{i=1}^n s_i)\cdot w+(\displaystyle\sum_{i=1}^ns_i^2-c)=0$。令 $a=4\displaystyle\sum_{i=1}^n s_i,b=\displaystyle\sum_{i=1}^ns_i^2-c$，将整个式子代入求根公式可得 $w_1=\frac{-a+\sqrt{a^2-16nb}}{8n},w_2=\frac{-a-\sqrt{a^2-16nb}}{8n}$，保留其中为正数的 $w_1$，输出就搞定了。

再处理一下细节问题。会发现这个做法可能导致溢出，考虑使用 `__int128`，由于 `__int128` 与 `cin`,`cout` 不适配，需手写输入输出。另外 `__int128` 与 `sqrt()` 函数也不适配，但会发现 $a^2-16nb$ 在 `double` 范围内，考虑将 $a^2-16nb$ 转换为 `double` 再来使用 `sqrt()` 函数。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
__int128 s[int(2e5+10)];
__int128 read()//手写读入
{
	__int128 f=1,x=0;
	char c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return f*x;
}
void write(__int128 x)//手写输出
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x / 10);
	putchar(x%10+'0');
	return;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		__int128 n,c,sum=0,sump=0,a,b,w;
		n=read();
		c=read();
		for(int i=1;i<=n;i++)
		{
			s[i]=read();
			sum+=s[i];//求和
			sump+=s[i]*s[i];//求平方的和
		}
		a=4*sum;//换元，使代码更简洁
		b=sump-c;
		w=(-a+sqrt((double)(a*a-16*n*b)))/(8*n);//保留为正数的w1
		write(w);
		cout<<endl;
	}
	return 0;
}

---

## 作者：___w (赞：1)

### [CF1850E Cardboard for Pictures](https://www.luogu.com.cn/problem/CF1850E)

#### 题意简述
有 $n$ 张正方形图片，长度分别为 $s_i$，外有 $s_i+2w$ 宽的框，共用 $c$ 面积大小。求出 $w$。

#### 题目分析
![图](https://cdn.luogu.com.cn/upload/image_hosting/swq8mnks.png)

如上图，我们可以讲每个图片的外面一圈划分为 $4$ 个部分，那么外面一圈的面积为 $4w(w+s_i)$。

我们把 $c-\sum_{i=1}^{n}s_i^2\to c$，即把 $c$ 变为外圈的面积和。

我们记 $sum=\sum_{i=1}^ns_i$，那么有

$$c=\sum_{i=1}^n4w(w+s_i)=4w(n\times w+sum)=4n\times w^2+4sum\times w$$

转化一下，得

$$4n\times w^2+4sum\times w-c=0$$

不难发现这是一个一元二次方程，带入求根公式，得

$$w=\frac{-4sum\pm\sqrt{16sum^2+16n\times c}}{8n}=\frac{-sum\pm\sqrt{sum^2+n\times c}}{2n}$$

舍去负根，即

$$w=\frac{-sum+\sqrt{sum^2+n\times c}}{2n}$$

为避免爆 ```long long```，我们要将上式转化为

$$w=\frac{-sum}{2n}+\sqrt{\frac{sum^2}{4n^2}+\frac{c}{4n}}$$

当然你也可以开 ```__int128```。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t, n, c;

signed main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n >> c;
		int sum = 0;
		for (int i = 1, s; i <= n; ++i) {
			cin >> s;
			sum += s;
			c -= s*s;
		}
		cout << -sum/2/n+(int)sqrt(sum*sum/4/n/n+c/4/n) << '\n';
	}
	return 0;
}
```

---

## 作者：Zaku (赞：1)

### $\mathrm{Problem:}$
给定 $n$ 个正方形的边长序列 $s$，需要在第 $i$ 块正方形后放一块边长为 $s_i+w\times 2$ 的正方形框子（$w$ 为未知数），这些框子的面积总和为 $c$。求 $w$ 的最小值。

### $\mathrm{Sol:}$
我们发现符合要求的 $w$ 值是单调上升的，所以想到二分。

然后就是一个裸的二分答案，不过需要分三种情况讨论二分区间的变化：

- 框子面积总和大于 $c$，则缩小右区间，```r = mid - 1```。
- 框子面积总和等于 $c$，则缩小右区间，并记录答案。```r = mid - 1, ans = mid```。
- 框子面积总和小于 $c$，则缩小左区间，```l = mid + 1```。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int s[N];
int check(int w, int c, int n){
    int sum = 0;
    for (int i = 1; i <= n; i ++ ){
        sum += (s[i] + w * 2) * (s[i] + w * 2);
        if (sum > c) return 1;
    }
    if (sum == c) return 0;
    if (sum < c) return -1;
}
signed main() {
    int T;
    cin >> T;
    while (T -
        int n, c;
        cin >> n >> c;
        for (int i = 1; i <= n; i ++ )
            cin >> s[i];
        int l = 0, r = 2e9;
        int ans = 0;
        while (l <= r){
            int mid = (l + r) / 2;
            int t = check(mid, c, n);
            if (t == 0) ans = mid, r = mid - 1;
            else if (t == 1) r = mid - 1;
            else l = mid + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：I_am_kunzi (赞：1)

# CF1850E 题解

### 题目翻译

有 $ t $ 组测试数据，每组给定 $ n $ 代表有 $ n $ 个图片，现在要你求出一个 $ w $ 使得每幅画用一块 $ s_i + w + w $ 为边长的正方形纸板后纸板的总面积可以达到 $ c$。（对这一部分不理解请参考题目中插图）

### 题目思路

观察数据规模发现 $ c \le 10 ^ {18}$，如果用暴力枚举的话最多需要枚举到 $ 10 ^ 9 $ 的范围（$ {10 ^ 9} ^ 2 = 10 ^ {18} $）。所以想到二分答案，如果最后计算的答案偏大则缩小 $ w $ 的值，否则放大知道最后计算的答案与 $ c $ 相等，但需要防止中途爆 long long 或者 __int128，因此如果中途发现某一部分已经超过 $ c $ 的值则需立刻结束函数并返回 $ 0$。

### 题目代码

```cpp
#define int long long // 因为全部改为 long long 比较麻烦，因此直接使用 #define 替换，但正式考试中不建议使用
long long a[200005];
bool pd(long long x , int n , long long c) // x 为目前二分的 w，n 是正方形个数，c 是给定的使用纸板面积
{
	long long now = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		now += (a[i] + x + x) * (a[i] + x + x);
		if(now > c) // 如果已经超过 c 则立刻返回，防止爆掉 long long
		{
			return 0;
		}
	}
	return now <= c; // 等价于 return (now <= c ? 1 : 0);
}
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		memset(a , 0 , sizeof(a)); // 使用数组前需要清空，防止不必要的错误
		int n;
		cin >> n;
		long long c = llfr; // 防止数据范围过大，使用快读，此处可以替换为 long long c; cin >> c;
		for(int i = 1 ; i <= n ; i++)
		{
			a[i] = llfr; // 同上
		}
		long long l = 0 , r = 1e9; // r = 1e9 是因为 w 最大只能到达 1e9
		while(l < r) // 此处因为 l 从 0 开始枚举
		{
			long long mid = (l + r + 1) >> 1; // 同上，此处也需使用 l + 1
			if(pd(mid , n , c)) // 如果最后没有超过 c 则说明 w 过小，让 l = mid（原因同上）
			{
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		cout << l << endl;
	}
    return 0;
}
```

---

## 作者：JuRuoOIer (赞：1)

# 题解 CF1850E Cardboard for Pictures

~~行吧，这么个小破题我赛时调了一个多点，以至于水题 F&G 没空做了……~~

### Part 1 题意

给定 $n$ 个正方形，第 $i$ 个正方形边长为 $s_i$，将所有正方形的四边往外拓宽 $w$ 后，总面积为 $c$，求 $w$ 的值。

$1 \le t \le 1000,1 \le \sum n \le 2\times 10^5,1 \le c \le 10^{18},1 \le s_i \le 10^4$。

### Part 2 做法

我们先带着 $w$ 求一波面积。

- 显然正方形的面积等于边长的平方，于是 $c=\sum_{i=1}^n(s_i+w)^2$。

于是你就错了。

- **四边都往外拓宽，新的边长相当于在原来边长的两边都加了一个** $w$（可以看题面给的图），即 $s_i+2w$，因此 $c=\sum_{i=1}^n(s_i+2w)^2$。
- 接着我们展开，也就是 $c=\sum_{i=1}^n(s_i^2+4s_iw+4w^2)=\sum_{i=1}^ns_i^2+\sum_{i=1}^n4s_iw+4nw^2$。
- 而我们可以循环求出 $\sum_{i=1}^ns_i$ 和 $\sum_{i=1}^ns_i^2$，设这两个数分别为 $a,b$，则 $c=a+4bw+4nw^2$。
- 移项，得到 $4nw^2+4bw+a-c=0$。

这是什么？一个关于 $w$ 的一元二次方程！

由于题目保证有正整数解，因此我们可以直接公式法解一下：
- $\Delta=(4b)^2-4(4n)(a-c)$
- 由于保证有正整数解，所以公式直接取加号即可。$w=\dfrac{-4b+\sqrt{\Delta}}{2\cdot4n}$。

循环算出 $a,b$ 就可以解了。

### Part 3 代码

直接套公式的活，不需要注释吧。

注意：
- 解方程时不开 `__int128` 会炸。
- 多测不清空，爆零两行泪。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,c,s[200010],a,b;
__int128 aa,bb,cc;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>c;
		b=0;cc=c;
		for(int i=0;i<a;i++){
			cin>>s[i];
			b+=s[i];
			cc-=s[i]*s[i];
		}
		b*=4;
		a*=4;
		aa=a;bb=b;
		cout<<(ll)((sqrtl(bb*bb+4*aa*cc)-bb)/(aa*2))<<endl;
	}
	return 0;
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1850E)    
## 题意    
现在有 $n$ 个正方形，第 $i$ 个正方形的边长为 $a_i+2\times w$，它们的总面积为 $S$，$a$ 给定，求出 $w$。    
## 解法    
我们先推一下式子。     
$\begin{aligned}S&=\sum\limits^n_{i=1}(a_i+2\times w)^2\\&=\sum\limits^n_{i=1}a_i^2+4\times w\times a_i+4\times w^2\\&=(\sum\limits^n_{i=1}a_i^2)+4\times (\sum\limits^n_{i=1}a_i)\times w+n\times4\times w^2\end{aligned}$      

那么这题就转换为了一个一元二次方程，我们只需要求出它的正数根即可。    
一点小优化：   
- 我们可以先让 $S$ 减掉 $\sum\limits^n_{i=1}a_i^2$，再除以 $4$，这样更好求。     

注意本题求根相乘时会爆 long long，需要开 `__int128`，开根时使用 `sqrtl`。     
[CODE](https://www.luogu.com.cn/paste/xippd43i)

---

## 作者：Special_Judge (赞：0)



阅读题目，我们可以将题意简化为：给定 $s_1,s_2,...,s_n$ 与 $c$，求解下面的方程。
$$
(2w+s_1)^2+(2w+s_2)^2+(2w+s_3)^2+...+(2w+s_n)^2=c
$$

注意：是 $2w$ 而不是 $w$！因为宽度有两边！

拆开括号，化简可得：
$$
4nw^2+4\sum_{i=1}^ns_i\times w+\sum_{i=1}^n{s_i}^2-c=0
$$
此处为了简便，设 $\sum_{i=1}^ns_i=suma$，设 $\sum_{i=1}^n{s_i}^2=sumb$。

那么上述方程即为：
$$
4nw^2+4\times suma\times w+sumb-c=0
$$


再运用一元二次方程的求根公式，得：
$$
w=\frac{-4\times suma\pm \sqrt{16\times suma^2-4\times 4n(sumb-c)}}{8n}=\frac {-suma \pm \sqrt{suma^2-n(sumb-c)}}{2n}
$$
即：

$$
w_1=\frac {-suma + \sqrt{suma^2-n(sumb-c)}}{2n}
$$
$$
w_2=\frac {-suma - \sqrt{suma^2-n(sumb-c)}}{2n}
$$

我们关注到，题目中给出了 $w\ge1$，但是由于 $-suma<0,-\sqrt{suma^2-n(sumb-c)}\le0,2n>0$，$w_2$ 不可能是一个正数，可以舍去，只取根 $w_1$ 即可。

代码实现就很简单了，唯一需要注意的是代码中的运算会炸`long long`，需要使用`__int128`，此处仅给出核心代码。

PS:如果你想在 Codeforces 上使用`__int128`，请在提交时选择 **C++20**，否则就会 **CE**！

```cpp
long long n,s[N],c;
__int128 suma,sumb;
__int128 x;
void write(__int128 x) //对__int128进行读写不能使用cin/cout/scanf/printf，需要快读快写
{
	if(x<0)
	{
    	x=-x;
    	putchar('-');
    }
  	if(x>9)write(x/10);
  	putchar(x%10+'0');
}
void work()
{
	suma=sumb=0;
	scanf("%lld%lld",&n,&c);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&s[i]);
		suma+=s[i];
		sumb+=s[i]*s[i];
	}
	x=(sqrt((suma*suma-n*(sumb-c))*1.0)-suma)/(2*n);
	write(x);
    printf("\n");
}
```





---

## 作者：zct_sky (赞：0)

### Description:
-----
给你一个长为 $n$ 的序列，第 $i$ 个元素为 $a_i$。

已知 $\sum\limits_{i=1}^{n} (a_i+2w)^2 =c$。

给定 $c$，求 $w$。

该题有多组数据。
### Solution:
-----
典型二分。

将原式进行拆解，可得 $\sum\limits_{i=1}^{n} a_i^2 +4w \times \sum\limits_{i=1}^{n} a_i + n \times 4w^2=c$。

记 $s_1=\sum\limits_{i=1}^{n} a_i^2,s_2=\sum\limits_{i=1}^{n} a_i$，则原式可化为 $s_1+4w \times s_2+n\times 4w^2 = c$。

其实到这一步已经可以解方程了，但由于判别式 $s_2^2-4s_1n$ 可能会炸 `long long`，于是我们只能用二分。

二分 $w$，判断 $n \times w^2 + s_2 \times w$ 和 $\dfrac{c-s_1}{4}$ 的大小关系，大于则更新 $r$，小于则更新 $l$，等于则输出答案。

注意开始二分时 $r$ 的大小，过小则找不到答案，过大则会炸 `long long`，详见代码。

时间复杂度为 $\Theta(t \log (r-l))$（$l,r$ 为二分边界）。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);
    putchar(x%10+48);
}
const int N=2e5+7;
ll n,a[N],c; 
ll t;
ll s1,s2;
int main(){
	t=read();
	while(t--){
		n=read();c=read();
		s1=s2=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			s1+=a[i]*a[i];
			s2+=a[i];
		}
		c-=s1;
		c/=4;
		ll l=1,r=(ll)sqrt(c/n)+7,ans;
		while(l<=r){
			ll mid=(l+r)>>1,tmp=s2*mid+mid*mid*n;
			if(tmp==c){
				ans=mid;
				break;
			}else if(tmp<c)l=mid+1;
			else r=mid-1;
		}
		write(ans);
		puts(""); 
	}
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1850E)

## 思路

这题 $c$ 的范围是 $1\le c\le 10^{18}$，肯定不可能暴力枚举，所以我们考虑用二分答案的做法解决此题。

读入数据后二分查找答案，判断如果边框宽度取当前的 $mid$（平均）值时能否使得边框面积等于 $c$，大了就减小范围，小了就增大范围。找到符合要求的值后，输出 $mid$ 即可。 

- 数据范围很大，别忘开 ``long long``。

- 有多组测试数据，记得清空数组和标记变量等。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
long long n,c,s[N],ans;
bool check(long long x){//判断是否符合要求。
	long long sum=0;
	for(int i=1;i<=n;++i){
		sum+=(2*x+s[i])*(2*x+s[i]);
		if(sum>c)return 0;
	}
	return 1;
}
void solve(){
	scanf("%lld%lld",&n,&c);
	for(int i=1;i<=n;++i)scanf("%lld",s+i);
	long long l=0,r=1e10;//10 的 10 次方已经足够。
	while(l<=r){//二分答案模板。
		long long mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%lld\n",ans);//记得换行 。
}
int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

[已 AC](https://www.luogu.com.cn/record/116996564)

---

## 作者：Phartial (赞：0)

题意：给你一个长为 $n$ 的正整数序列 $s_i$ 和一个正整数 $c$，你需要找到正整数 $w$ 使得 $\displaystyle\sum_{i=1}^n(s_i+2w)^2=c$。保证有解。

记 $f(x)=\displaystyle\sum_{i=1}^n(s_i+2x)^2$，显然 $f(x)$ 是单调递增的，于是考虑二分。

维护当前的可能答案区间 $[l,r]$，每次取其中点 $m=\lfloor\frac{l+r}{2}\rfloor$，计算 $f(m)$，将其与 $c$ 比较：

- 如果 $f(m)\ge c$：说明我们取的 $m$ 要大于等于 $w$，将可能答案区间由 $[l,r]$ 缩小至 $[l,m]$ 即可；
- 如果 $f(m)< c$：说明我们取的 $m$ 小于 $w$，将可能答案区间由 $[l,r]$ 缩小至 $[m+1,r]$ 即可。

当 $l=r$，说明我们找到了解，输出即可。否则重复此过程。

初始的可能答案区间可以取 $[1,\lfloor\sqrt{c}\rfloor]$。

注意 $f(m)$ 有可能超出 $64$ 位整数的表达范围，需要使用 `__int128_t` 或每次加上一个 $(s_i+2x)^2$ 就判断当前的和是否 $\ge c$。

```cpp
#include <cmath>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int t, n;
LL c, a[kN];

bool C(LL w) {
  LL s = 0;
  for (int i = 1; i <= n; ++i) {
    s += (a[i] + w * 2) * (a[i] + w * 2);
    if (s >= c) {
      return 1;
    }
  }
  return 0;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--; ) {
    cin >> n >> c;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    LL l = 1, r = sqrt(c);
    while (l < r) {
      LL w = l + r >> 1;
      if (C(w)) {
        r = w;
      } else {
        l = w + 1;
      }
    }
    cout << l << '\n';
  }
  return 0;
}
```


---

