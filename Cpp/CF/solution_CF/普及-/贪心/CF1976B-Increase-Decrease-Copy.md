# Increase/Decrease/Copy

## 题目描述

You are given two integer arrays: array $ a $ of length $ n $ and array $ b $ of length $ n+1 $ .

You can perform the following operations any number of times in any order:

- choose any element of the array $ a $ and increase it by $ 1 $ ;
- choose any element of the array $ a $ and decrease it by $ 1 $ ;
- choose any element of the array $ a $ , copy it and append the copy to the end of the array $ a $ .

Your task is to calculate the minimum number of aforementioned operations (possibly zero) required to transform the array $ a $ into the array $ b $ . It can be shown that under the constraints of the problem, it is always possible.

## 说明/提示

In the first example, you can transform $ a $ into $ b $ as follows: $ [2] \rightarrow [2, 2] \rightarrow [1, 2] \rightarrow [1, 3] $ .

## 样例 #1

### 输入

```
3
1
2
1 3
2
3 3
3 3 3
4
4 2 1 2
2 1 5 2 3```

### 输出

```
3
1
8```

# 题解

## 作者：ikunTLE (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1976B)

### 思路

对序列 $a$ 和序列 $b$ 的前 $n$ 个数，我们无法改变它们，只能累计 $a_i-b_i$ 的绝对值。

那么我们该如何确定 $b_{n+1}$ 所需要的代价呢？

- 如果 $a_i$ 累加或者累减的时候恰好是 $b_{n+1}$，那么这个代价就是 $0$。

- 否则只能取与与 $b_{n+1}$ 差值最小的值作为代价。

但是答案并不是上述所求的和，因为**将 $a_i$ 复制到 $b_{n+1}$ 需要的代价为 $1$**，最终答案应该再加上 $1$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,x,a[N],b[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		long long ans=0;
		for(int i=1;i<=n;++i){
			scanf("%d",&b[i]);
			if(a[i]>b[i])//为了方便计算，我们让a[i]<=b[i]
				swap(a[i],b[i]);
			ans+=b[i]-a[i];//计算a[i]与b[i]的绝对值
		}
		scanf("%d",&x);//即b[n+1]
		int temp=0x7FFFFFFF;
		for(int i=1;i<=n;++i){
			if(a[i]<=x&&x<=b[i]){//说明b[n+1]再a[i]与b[i]之间
				temp=0;//所以代价为0
				break;
			}
			temp=min(temp,int(min(abs(a[i]-x),abs(b[i]-x))));
			//否则只能取与与b[n+1]差值最小的值作为代价
		}
		printf("%lld\n",ans+temp+1);
		//注意复制也需要大小为1的代价，所以最终答案上要+1
	}
	return 0;
}
```

---

## 作者：Louis_lxy (赞：4)

## 前言

就是一个简单的贪心加分类讨论。

## 思路

观察题目，发现其实影响最终结果的就是在什么时候复制什么数到最后。

因此考虑贪心，枚举每个 $i$，如果 $b_{n+1}\in[a_i,b_i]$（默认 $a_i$ 小于 $b_i$），那么最终一定能花费 $1$ 的代价完成复制（即无需改变），否则根据贪心的思想，只有可能复制 $b_i$ 或 $a_i$，因此分类讨论，找出最小值即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;
int a[N], b[N + 1];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, mn = INT_MAX, k;
		long long ans = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for (int i = 1; i <= n + 1; ++i) scanf("%d", &b[i]);
		for (int i = 1; i <= n; ++i)
		{
			int ma = max(a[i], b[i]), mi = min(a[i], b[i]);
			if (b[n + 1] > mi && b[n + 1] < ma) { k = b[n + 1], mn = 0; break; }
			else
			{
				if (abs(b[i] - b[n + 1]) < mn) mn = abs(b[i] - b[n + 1]), k = b[i];
				if (abs(a[i] - b[n + 1]) < mn) mn = abs(a[i] - b[n + 1]), k = a[i];
			}
		}
		a[n + 1] = k;
		for (int i = 1; i <= n + 1; ++i) ans += abs(a[i] - b[i]);
		printf("%lld\n", ans + 1);
	}
}
```

---

## 作者：FXLIR (赞：2)

### 题意
给你一个长度为 $n$ 的序列 $a$ 和一个长度为 $n+1$ 的序列 $b$，以及三种操作：

- 从序列 $a$ 中选定一个数字，并将其增加 $1$；

- 从序列 $a$ 中选定一个数字，并将其减少 $1$；

- 从序列 $a$ 中选定一个数字，并将其复制到序列 $a$ 的末尾。

求最少需要几次才能让序列 $a$ 与序列 $b$ 完全相等。
### 做法
首先，我们考虑如何在使用最少操作次数的情况下，让序列 $a$ 的前 $n$ 个数字与序列 $b$ 的前 $n$ 个数字相等。

不难考虑到以下解法：

- 如果 $a_i$ 和 $b_i$ 相等，不进行变换；

- 如果 $a_i$ 小于 $b_i$，将 $a_i$ 不断加上 $1$，直至 $a_i$ 和 $b_i$ 相等，需要 $b_i - a_i$ 次操作。

- 如果 $a_i$ 大于 $b_i$，将 $a_i$ 不断减去 $1$，直至 $a_i$ 和 $b_i$ 相等，需要 $a_i - b_i$ 次操作。

其中，第二种情况可以和第三种合并，即“若 $a_i$ 与 $b_i$ 不相等，花费 $a_i - b_i$ 的绝对值次操作使得 $a_i$ 与 $b_i$ 相等”。

然后，需要考虑的就是如何用最少的操作次数“造”出 $a_{n+1}$ 了。很明显，在这个过程中，肯定需要一次复制操作。

可以使用以下思路进行操作：

- 如果在前面的变换过程中出现了等于 $b_{n+1}$ 的值，直接使用一次操作将它复制过来即可。

- 如果在前面的变换过程中没有出现等于 $b_{n+1}$ 的值，从前面所变换出的数中选出与它大小最接近的数，复制过来后再通过增加 $1$ 和减少 $1$ 来使其 等于 $b_{n+1}$。选出与它大小最接近的数就是为了使最后变换所花费的操作次数最少。

### AC code

```cpp
#include<map>
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,a[N],b[N],lena,lenb,ans,minum,manum;
signed main(){
	cin>>t;
	while(t--){
		minum=1e17,manum=1e17,ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		lenb=n+1,lena=n;
		for(int i=1;i<=lenb;i++){
			cin>>b[i];
		}
		for(int i=1;i<=n;i++){
			ans+=abs(a[i]-b[i]);
			if(lenb-lena&&b[lenb]>=min(a[i],b[i])&&b[lenb]<=max(a[i],b[i])){
				ans++,lena++;
			}
			minum=min(minum,abs(min(a[i],b[i])-b[lenb]));
			manum=min(manum,abs(max(a[i],b[i])-b[lenb]));
                    
		}
		if(lena==lenb){
			cout<<ans<<"\n";
		}else{
			cout<<ans+min(minum,manum)+1<<"\n";//+1 是因为这里没有统计复制所用的操作次数
		}
	}
	return 0;
}
```

---

## 作者：littleqwq (赞：1)

# CF1976B Increase/Decrease/Copy 题解

### 题目意思：

给你两个整数数组：长度为 $n$ 的数组 $a$ 和长度为 $n + 1$ 的数组 $b$ 。

你可以按任意顺序执行下列操作任意次数：

- 从数组 $a$ 中任选一个元素，然后将其增加 $1$ ；
- 选择数组 $a$ 中的任意元素，并将其减少 $1$ ；
- 选择数组 $a$ 中的任意元素，复制并追加到数组 $a$ 的末尾。

你的任务是计算将数组 $a$ 转换为数组 $b$ 所需的最少上述操作次数(可能为零)。可以证明，在问题的限制条件下，这总是可能的。

### 大致思路：

因为我们发现，复制操作只能执行一次，因为原串长度 $n$，而目标串长度 $n + 1$，而且会追加到最后，所以我们要尽可能在对其他数字进行操作时，当与目标串相同时复制，当然还有一种情况，所有数字进行操作时，都没有变化过成目标串最后一位，那么我们就要找变化完后与目标串最后一位相差最小的数，复制，再将最后一位进行操作。

显然我们在他们原串变化时，会出现三种情况，这里 $a$ 指原串，$b$ 指目标串：

- $a_i$ 和 $b_i$ 均大于 $b_{n + 1}$，那么取小的那个与目标串最后一位相减，公式 $mn = \min(mn, \min(a_i, b_i) - b_{n + 1});$

- $a_i$ 和 $b_i$ 均小于 $b_{n + 1}$，那么取大的那个与目标串最后一位相减，公式 $mn = \min(mn, b_{n + 1} - \max(a_i, b_i));$

- 剩余情况肯定会在其他数变化时，变化成目标串最后一位，所以直接复制就好，$mn$ 赋值为 $0$，跳出循环即可。

这里 $mn$ 存的是复制后的数最少变化几次，变成目标串最后一位，接着我们用 $ans$ 表示其他数变成对应数的总次数。

那么只要输出 $ans + mn + 1$，就好了。

### 代码实现：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
struct Stream {
    enum {
        SIZE = 1000001
    };
    char ibuf[SIZE], *s, *t, obuf[SIZE], *oh;
    bool eof;
 
    Stream() : s(), t(), oh(obuf), eof(false) {}
 
    ~Stream() { fwrite(obuf, 1, oh - obuf, stdout); }
 
    explicit operator bool() const {
        return static_cast<bool>(eof == false);
    }
 
    inline char read() {
        if (s == t) t = (s = ibuf) + fread(ibuf, 1, SIZE, stdin);
        return s == t ? -1 : *s++;
    }
 
    inline Stream &operator>>(char *x) {
        static char c;
        for (c = read(); isspace(c); c = read())
            if (c == -1) {
                eof = true;
                return *this;
            }
        for (; !isspace(c); c = read()) *x = c, ++x;
        *x = 0;
        return *this;
    }
 
    template<typename T>
    inline Stream &operator>>(T &x) {
        static char c;
        static bool iosig;
        for (c = read(), iosig = false; !isdigit(c); c = read()) {
            if (c == -1) {
                eof = true;
                return *this;
            }
            iosig |= c == '-';
        }
        for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
        if (iosig) x = -x;
        return *this;
    }
 
    inline void print(char c) {
        if (oh == obuf + SIZE) {
            fwrite(obuf, 1, SIZE, stdout);
            oh = obuf;
        }
        *oh++ = c;
    }
 
    template<typename T>
    inline void print(T x) {
        static int buf[40], cnt;
        if (x != 0) {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
            while (cnt) print((char) buf[cnt--]);
        } else print('0');
    }
 
    template<typename T>
    inline Stream &operator<<(const T &x) {
        print(x);
        return *this;
    }
 
    inline void print(const char *x) {
        for (; *x; x++)
            print(*x);
    }
} io;
 
#ifndef DEBUG
#define cin io
#define cout io
#define endl '\n'
#endif

int T;
int n, a[N], b[N], c;
signed main()
{
	cin >> T;
	while(T --)
	{
		cin >> n;
		int mn = 1e9 + 7, ans = 0;
		for(int i = 1;i <= n; ++ i)
		{
			cin >> a[i];
		}
		for(int i = 1;i <= n + 1; ++ i)
		{
			cin >> b[i];
			if(i <= n) ans += abs(a[i] - b[i]);
		}
		for(int i = 1;i <= n; ++ i)
		{
			if(a[i] > b[n + 1] && b[i] > b[n + 1])//都比他大，取小的 
			{
				mn = min(mn, min(a[i], b[i]) - b[n + 1]);
			}
			else if(a[i] < b[n + 1] && b[i] < b[n + 1])//缩小复制 
			{
				mn = min(mn, b[n + 1] - max(a[i], b[i]));
			}
			else
			{
				mn = 0;break;//可以再其中一个数变化的过程中复制
			}
		}
		cout << ans + mn + 1 << "\n";
	}
	return 0;
}
```

这样这道题就完成啦。

---

## 作者：Miracle_1024 (赞：0)

## 思路：
  考虑最后一个位置的步数。有两种方法，一是去 $a$ 数组找到合适的放在最后一个位置，二是在 $a$ 向 $b$ 发生变化的时候去放在最后一个位置，找到两个方法的最小的步数就可以了。 别的位置直接用 abs，然后这道题就解决了。
  
## 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
const int INF=0x3f3f3f3f;
const int N=1e6+10;
ll t,n,a[N],b[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n+1;i++)cin>>b[i];
		ll x=b[n+1],s=INF,ans=0ll;
		for(int i=1;i<=n;i++){
			ans+=(ll)abs(a[i]-b[i]);
			if(a[i]<b[i]){
				if(a[i]<=x&&x<=b[i])s=0;
				else if(a[i]>x)s=min(s,a[i]-x); 
				else if(x>b[i])s=min(s,x-b[i]);
			}
			else{
				if(b[i]<=x&&x<=a[i])s=0;
				else if(b[i]>x)s=min(s,b[i]-x); 
				else if(x>a[i])s=min(s,x-a[i]);
			}
		}
		ans+=(s+1);
		cout<<ans<<endl;
	}
}
```

---

## 作者：Seqfrel (赞：0)

# 题解：CF1976B Increase/Decrease/Copy

开篇说句闲话，本人在调这道题的时候，理解题意错误调了 $40$ 分钟，调完之后交了几遍发现一直答案错误，跑到 CF 上一看发现错误信息是数据溢出，换了 `long long` 才过了，总耗时 $1$ 小时，望周知。

## 题目大意

给定一个长度为 $n$ 的数组 $a$ 和一个长度为 $n+1$ 的数组 $b$，每次操作可以把 $a_i$ 加上或减去 $1$，或者把 $a_i$ 复制到 $a$ 的末尾，操作顺序可以任意，求最少操作几次可以把 $a$ 变成 $b$。

## 解题思路

由于只能把一个 $a_i$ 复制到 $a$ 的末尾，而其他数只能通过加减进行转换，那么如何选择这个 $a_i$ 可以使得操作最小便成了至关重要的问题。

我们首先想到的是选择一个与 $b_{n+1}$ 最接近的 $a_i$ 来进行复制。那么我们用样例 $3$ 来模拟一下，看看结果是否正确：

![](https://cdn.luogu.com.cn/upload/image_hosting/43h1no7y.png)

显然不是正确答案。

那么我们来思考一下，哪里浪费了这多的一次操作呢？

我们发现，$4$ 在变 $2$ 的时候，是要先变成 $3$ 的，而这个时候我们把 $4$ 复制过去，不就不用复制过后再加 $1$ 了吗？

于是这就是这道题最关键的地方，~~也是坑了我半个小时的地方~~。

那我们遍历每个 $i$，看看这个 $b_{n+1}$ 是不是在 $a_i$ 和 $b_i$ 之间，如果是，那么就不用再复制过去重新操作了，直接把 $a_{n+1}$ 变成 $b_{n+1}$，其余的 $a_i$ 依次转换成 $b_i$ 并相加操作次数即 $|a_i-b_i|$ 即可。

那么如果所有 $a_i$ 在转变成 $b_i$ 的时候都不会经过 $b_{n+1}$ 呢？那我们沿用老思路，选择一个与 $b_{n+1}$ 最接近的。但这里还要注意一点，我们要把 $a_i$ 变成 $b_i$ 后的情况算上，因为这时有可能会更接近，而且不用花费额外的操作次数。设最接近的 $a_i$ 或者 $b_i$ 为 $k$，那么把 $a_{n+1}$ 变成 $k$，之后相加所有的 $|a_i-b_i|$ 即可（注意是所有的，因为 $a_{n+1}$ 还需要进一步转换）。

最后别忘了把结果 $+1$，因为复制也算一次操作次数。

设所有 $n$ 相加的值为 $N$，时间复杂度即为 $O(N)$，$N \le 2 \times 10^5$，稳过。

## 代码实现

```cpp
#include<iostream>
#include<cmath> 
#define int long long
using namespace std;
const int maxn=2e5+10;
const int maxx=1e9+10;
int t;
int n,a[maxn],b[maxn],minc,ans;
bool flag;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		minc=maxx,ans=0;
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(int i=1;i<=n+1;i++) scanf("%lld",&b[i]);
		for(int i=1;i<=n;i++){//寻找可能经过的情况，同时寻找最接近的。 
			if(min(a[i],b[i])<=b[n+1]&&max(a[i],b[i])>=b[n+1]){
				a[n+1]=b[n+1];
				break;
			}else{
				if(abs(b[n+1]-a[i])<minc){
					minc=abs(b[n+1]-a[i]);
					a[n+1]=a[i];
				}
				if(abs(b[n+1]-b[i])<minc){
					minc=abs(b[n+1]-b[i]);
					a[n+1]=b[i];
				}
			}
		}
		for(int i=1;i<=n+1;i++){//相加所有的操作次数。
			ans+=abs(b[i]-a[i]);
		}
		ans++;//复制所需的操作次数。
		printf("%lld\n",ans);
	}
	return 0;
} 
```

## 注意事项

极端数据下每个 $a_i$ 与 $b_i$ 的差值能达到 $10^9-1$，而一共有 $2 \times 10^5$ 个这样的差值，那么答案就能达到 $(10^9-1) \times (2 \times 10^5) \approx 2 \times 10^{14}$，需要开 `long long`。

---

## 作者：leo120306 (赞：0)

## 基本思路

首先，我们考虑前 $n$ 个元素的修改。题目只给了 $+1$ 和 $-1$ 两种基本操作，那么显然最优的修改方案是：

- 如果 $a_i<b_i$，那么就不断 $+1$ 直到 $a_i=b_i$。修改次数是 $b_i-a_i$。
- 如果 $a_i>b_i$，那么就不断 $-1$ 直到 $a_i=b_i$。修改次数是 $a_i-b_i$。

前 $n$ 个元素的修改搞定了，接下来只要考虑怎么造 $b_{n+1}$ 就行了。我们分类讨论：

- 如果存在 $i$，使得 $a_i\le b_{n+1}\le b_i$ 或 $b_i\le b_{n+1}\le a_i$：

换句话说，$a_i$ 在变成 $b_i$ 的一系列中间状态中，曾经成为过 $b_{n+1}$，那么只需要把这个中间状态贴到数组最后就行了。操作次数 $1$ 次。

- 如果不存在：

那么就只能把变化过程中曾经出现过的最接近 $b_{n+1}$ 的数贴到数组最后了。容易发现这个数一定在 $a_1,\cdots,a_n$ 和 $b_1,\cdots,b_n$ 中。暴力查找即可。

为了把这个数变成 $b_{n+1}$，假设找到的数是 $k$，那么还需要 $\left|k-b_{n+1}\right|$ 次变化（与前 $n$ 个元素的修改讨论类似）才能把 $b_{n+1}$ 变化正确。

最后，把修改次数全部加起来，就大功告成了。

## 代码

一个小细节：考虑 $sum$ 最大为 $2 \times 10^5 \times 10^9$ 数量级，别忘了开 long long。
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int a[200005],b[200005];
#define betw(x,y,z) x<=y&&y<=z

int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin >> n;
		for(int i=1; i<=n; i++) cin>>a[i];
		for(int i=1; i<=n+1; i++) cin>>b[i];
		long long sum=1; // 把a[i]赋值到b[n+1]是一次操作 
		int minx=0x7f7f7f7f;
		for(int i=1; i<=n; i++){
			if(a[i]<b[i]){ // 操作1 
				sum+=b[i]-a[i];
				if(betw(a[i],b[n+1],b[i])) minx=0; // 过程中可以造出b[n+1] 
			}else{ // 操作2 
				sum+=a[i]-b[i];
				if(betw(b[i],b[n+1],a[i])) minx=0; // 过程中可以造出b[n+1] 
			}
		}
		if(minx!=0){
			for(int i=1; i<=n; i++) minx=min(
				minx,
				min(abs(a[i]-b[n+1]),abs(b[i]-b[n+1])) // 左右端点造b[n+1] 
			);
		}
		sum+=minx;
		cout<<sum<<endl; 
	}
    return 0;
}
```
~~第一篇题解，还请 dalao 勿喷。~~

---

## 作者：Beacon_wolf (赞：0)

## 题目思路
对于前 $n$ 个元素：

- 如果 $a_i>b_i$，将 $a_i$ 不断加 $1$ 直至等于 $b_i$ 为止。
- 如果 $a_i>b_i$ ，将 $a_i$ 不断减 $1$ 直至等于 $b_i$ 为止。

综上，可合并为：

对于前 $n$ 个元素，修改花费为 $| a_i - b_i |$。

接下来，对于最后一个元素，判断是否在上述修改过程中出现了等于 $b_{n + 1}$ 的元素，如果有，那么只需要将它复制过来就可以了；否则，现将最接近它的元素复制过来，再不断加减直至等于 $b_{n + 1}$。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[200010],b[200010];
void solve(){
	long long n,ans = 0,kk = 1000000010;
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n + 1;i++) cin >> b[i];
	for(int i = 1;i <= n;i++){
		ans += abs(a[i] - b[i]);
		kk = min(kk,abs(b[n + 1] - a[i]));
		kk = min(kk,abs(b[n + 1] - b[i]));
		if(max(a[i],b[i]) >= b[n + 1] && min(a[i],b[i]) <= b[n + 1]) kk = 0;
	}
	cout << ans + kk + 1 << endl;
}
int main(){
	int t;
	cin >> t; 
	while(t--){
		solve();
	}
	return 0;
} 

```

---

## 作者：OIer_Hhy (赞：0)

~~一道大水题~~。

这道题，我们用贪心。

由题意知，前 $n$ 项需改动的次数为 $\sum _ {i=1} ^ {n}\operatorname{abs}(a_{i}-b_{i})$。

所以我们要让最后一项改动的尽量小。

枚举每个 $a_{i}$ 和 $b_{i}$，如果闭区间 $[ a_{i},b_{i} ]$ 中包含了 $b_{n+1}$，则最后一项只需要复制（从 $a_{i}$ 变成 $b_{i}$ 时 $a_{i}=b_{n+1}$）。

否则最后一项要改动 $\min _ {i=1} ^ {n}  \min( \operatorname{abs}(a_{i}-b_{n+1}),\operatorname{abs}(b_{i}-b_{n+1}))$ 次。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+20;
int t,n,a[maxn],b[maxn];
void solve(){
	cin>>n;
	int x=1e18,y=0; // x为最后一项改动次数，y为前 n 项的差。
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n+1;i++) cin>>b[i];
	for(int i=1;i<=n;i++){
		if(min(a[i],b[i])<=b[n+1]&&max(a[i],b[i])>=b[n+1]){
			x=0;
			break;
		}
		x=min(x,min(abs(b[i]-b[n+1]),abs(a[i]-b[n+1])));
	}
	for(int i=1;i<=n;i++)
		y+=abs(a[i]-b[i]);
	cout<<x+y+1<<endl; // 还有一次复制！
	
}
signed main(){
	cin>>t;
	while(t--)
		solve();
	return 0;
}

```

管理员审核辛苦了！

---

## 作者：ttq012 (赞：0)

超弱 test，纪念达成新成就。

![](https://cdn.luogu.com.cn/upload/image_hosting/r0fycqw9.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

------

首先题目中的 `possibly zero` 就是诈骗。复制一下一个元素就已经完成了 $1$ 次操作。

然后如果不考虑最后一个元素的话，前 $n$ 个元素必然是直接从 $a_i\to b_i$ 走过去的。但是加上了最后一个元素的贡献，那么就考虑枚举最后一个元素是从哪一个元素的一次操作中复制出来的。

设当前枚举到了一个元素 $i$。若 $a_i\to b_i$ 的最短操作路径中出现了 $b_{n+1}$ 那么很显然在出现这个元素的时刻复制一下即可。

如果不存在怎么办？~~很显然~~不存在的话一定是从一个 $a_i$ 或者一个 $b_i$ 的时候复制然后再走过去的。枚举一下即可。

时间复杂度为 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define F(i,x,y) for(int i=x;i<=y;i++)
#define G(i,x,y) for(int i=x;i>=y;i--)
#define inf (7611257611378358090ll/2)
using namespace std;
const int N = 550010, mod = 1e9 + 7;
int a[N], b[N];
auto main() [[O3]] -> signed {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        F(i, 1, n) cin >> a[i];
        F(i, 1, n + 1) cin >> b[i];
        int diff = 0;
        F(i, 1, n) diff += abs(a[i] - b[i]);
        // 处理 b[n+1]
        bool ok = true;
        F(i, 1, n) {
            if (a[i] <= b[n + 1] && b[n + 1] <= b[i] || a[i] >= b[n + 1] && b[n + 1] >= b[i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            int mi = inf;
            F(i, 1, n) {
                mi = min({mi, abs(a[i] - b[n + 1]), abs(b[i] - b[n + 1])});
            }
            diff += mi;
        }
        cout << diff + 1 << '\n';
    }
}
```

---

