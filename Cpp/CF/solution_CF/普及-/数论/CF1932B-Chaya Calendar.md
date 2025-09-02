# Chaya Calendar

## 题目描述

某部落相信启示有 $n$ 个迹象。随着时间的推移，人们发现第 $i$ 个迹象每隔 $a_i$ 年出现一次（在 $a_i$ 年、$2\cdot a_i$ 年、$3\cdot a_i$ 年等）。

根据传说，为了发生启示，这些迹象必须按顺序出现。也就是说，首先他们等待第一个迹象的出现，然后严格在其之后，第二个迹象将出现，依此类推。也就是说，如果第 $i$ 个迹象出现在第 $x$ 年，部落将从第 $(x+1)$ 年开始等待第 $(i+1)$ 个迹象的出现。值得注意的是，**等待后面的迹象发生时，前面的所有迹象都可以多次在出现**。

第 $n$ 个迹象将在哪一年出现，启示将会第一次发生？

## 样例 #1

### 输入

```
4
6
3 2 4 5 9 18
5
1 2 3 4 5
5
1 1 1 1 1
6
50 30 711 200 503 1006```

### 输出

```
36
5
5
2012```

# 题解

## 作者：jiangjiangQwQ (赞：5)

### 思路
先给个题目翻译，有 $n$ 个世界末日，第一个世界末日的时间为 $a_1$，从第二个时间开始，这个时间要严格大于前一次世界末日时间且为 $a_i$ 的倍数，求第 $n$ 次世界末日的时间。直接模拟就行了，例如上次末日为 $t$，那么我们要先求出一个**不大于 $t$ 的为 $a_i$ 的倍数的数**，然后用这个数加上 $a_i$，就是这次末日时间，总结一下就是 $now=t/a_i\times a_i+a_i$。
### 代码
```cpp
#include<iostream>
using  namespace std;
const int N=1e2+5;
int T,n,a[N];
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        int ans=-1;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(i==1) ans=a[i];
            else ans=(ans/a[i]+1)*a[i];
            // cout<<ans<<' ';
        }cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：2huk (赞：3)

不难发现对于每一个 $a$ 的前缀 $1 \sim i$ 的答案，实际上在就是前缀 $1 \sim i - 1$ 的基础上增加了若干年使得这个时间是 $a_i$ 的倍数。也就是最小的 $a_i$ 的倍数满足这个数大于上一个答案。

由于 $a_i$ 的倍数一定可以写成 $a_i \cdot x$ 的形式，其中 $x$ 为正整数，所以我们可以二分这个 $x$，然后判断 $a_i \cdot x$ 是否大于上一个答案即可。

```cpp
int solve() {
	int n = read();
	int x = 0;
	while (n -- ) {
		int t = read();
		int l = 1, r = 1e9, res = 0;
		while (l <= r) {
			int mid = l + r >> 1;
			if (t * mid > x) res = t * mid, r = mid - 1;
			else l = mid + 1;
		}
		x = res;
	}
	return x;
}
```

---

## 作者：2c_s (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1932B)

## 思路

如果我们已经经历了第 $i\space (0\le i<n)$ 个迹象，那么接下来的迹象有三种情况：

- 下一个迹象发生的周期大于当前时间，那么世界末日延迟到下一个迹象发生的时间。

- 下一个迹象发生的周期等于当前时间，那么世界末日延迟到当前时间 $+$ 下一个迹象发生的周期。

- 否则世界末日延迟到下一个迹象下次发生的时间。

计算最后一种情况的方法：设 $ans$ 为当前计算的世界末日时间（当前时间），下一个迹象发生的周期为 $x$：

- 下一个迹象上次发生就是在这个迹象的第 $\Large\lfloor \frac{ans}{x}\rfloor$ 轮；

- 上次发生在第 $\Large\lfloor \frac{ans}{x}\rfloor \normalsize\times x$ 年；

- 下次将在 $\Large\lfloor \frac{ans}{x}\rfloor \normalsize\times x+x$ 年发生。

**提示**：有多组测试数据，记得清空所用变量。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int n,a[N];
int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)scanf("%d",a+i);
        int ans=0;
        for(int i=1;i<=n;++i){
            if(ans<a[i]){
                ans=a[i];
                continue;
            }
            if(ans%a[i]==0){
                ans+=a[i];
                continue;
            }
            ans=ans/a[i]*a[i]+a[i];
        }
        cout<<ans;
        putchar('\n');
    }
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/147913093)

---

## 作者：2021zjhs005 (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1932B)。


Despriction
------------
给定 $n$ 个迹象发生的时间为 $a_i$ 的倍数，每观察完一个迹象就继续观察下一个迹象。求第 $n$ 个迹象发生的时间。

注：一共有 $T$ 组数据。


Solution
------------
拿到这道题，很多人第一时间会想到分类讨论。

设 $last$ 表示当前迹象发生的时间，则有：

$$\begin{cases}last=a_i & last<a_i\\last=2\times a_i& last=a_i\\last=(1+\lfloor\frac{last}{a_i}\rfloor)\times a_i&last>a_i\end{cases}$$

- 第一种情况，$last<a_i$，那么下一个迹象发生的时间为 $a_i$。

- 第二种情况，$last=a_i$，那么下一个迹象发生的时间不能是 $a_i$，是 $a_i$ 的倍数并且大于 $a_i$ 的最小数为 $2\times a_i$。

- 第三种情况，$last>a_i$，那么下一个迹象发生的时间即为 $a_i\times y$，其中 $y$ 必须保证 $a_i\times y>last$ 并且 $y$ 最小，所以 $y$ 的取值为 $(1+\lfloor\frac{last}{a_i}\rfloor)$，下一个迹象发生的时间即为 $(1+\lfloor\frac{last}{a_i}\rfloor)\times a_i$。

将三种情况合起来，其实就是第三种情况的思路，所以不难得到递推式 $(1+\lfloor\frac{last_{i-1}}{a_i}\rfloor)\times a_i$（这里 $last$ 为数组）。


Code
------------
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
#define stg string
#define vct vector
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

ll T,n,last,a[105];

int main(){
  T=read();
  while(T--){//注意有 T 组数据。
    n=read();
    rep(i,1,n) a[i]=read();
    last=a[1];
    rep(i,2,n) last=(last/a[i]+1)*a[i];//递推公式。
    pr("%lld\n",last);
  }
  return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/148367883)。

---

## 作者：Super_Builder (赞：1)

## 思路
我们设 $nowt$ 为处理完当前迹象开始处理下一个迹象的第一年，由于是从第一天开始所以把初值赋为 $1$。

接着我们开始处理每一个迹象，假设当前正在处理 $i$ 迹象。  

- 如果 $nowt$ 不是 $a_i$ 的整数倍，那么 $nowt$ 需要增加 $a_i-nowt\bmod a_i$，使得 $nowt$ 变成 $a_i$ 的整数倍。然后再加上 $1$，可以看 $nowt$ 的定义，因为处理下一个迹象要到下一年再开始处理。
- 如果 $nowt$ 是 $a_i$ 的整数倍，只需要是 $nowt+1$ 就好了，原因和上面一样。

最后答案是 $nowt-1$，因为最后一个迹象后就没有下一个要处理了，而最后还加了 $1$，所以要减去。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[105];
signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        int nowt=1;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(nowt%a[i]){
                nowt=nowt+a[i]-nowt%a[i];
            }
            nowt++;
        }
        cout<<nowt-1<<endl;
    }
    return 0;
}
```

---

## 作者：dthythxth_Huge_Brain (赞：1)

## 题目大意

有 $n$ 个天象，每个天象出现的周期为 $a_i$ 年。现在有一个人从第一个天象开始观察，当观察到此天象，则下一年开始观察下一个天象，求这个人观察完最后一个天象所花的年数。

## 思路

设第 $i$ 个天象答案为 $f_i-1$，则可以推出递推式。
$$f_i=\begin{cases}
  \text{if}((f_{i-1}\equiv0\pmod{a_i})\text{or}(f_{i-1}=0))&\lfloor\frac{f_{i-1}}{a}\rfloor\times a+a+1\\
  \text{else}&f_{i-1}+1
\end{cases}$$

输出答案为 $f_n-1$，单次询问复杂度 $O(n)$。

## 参考代码

```
#include<bits/stdc++.h>
#define int long long
int t,n,a[114],f[114];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n),f[0]=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			if(f[i-1]%a[i]!=0||f[i-1]==0)f[i]=f[i-1]/a[i]*a[i]+a[i]+1;
			else f[i]=f[i-1]+1;
		}
		printf("%lld\n",f[n]-1);
	}
	return 0;
}
```

---

## 作者：minVan (赞：1)

**题目大意**

第 $i$ 个征兆将在 $a_i\cdot k$ 年里发生，每一年都最多只能接受一次征兆，求最少的 $x$，使得在 $1\sim x$ 内依次接收了 $1\sim n$ 每条征兆。

**解题思路**

令当前年份为 $x$，则在 $x$ 及以后第一次出现 $i$ 征兆是在 $\left\lceil\dfrac{x}{a_i}\right\rceil\cdot x$，但如果 $x$ 没变即一年接受了两次征兆，那么就要到下一次征兆来临，即 $x\gets x+a_i$。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    int n, x, ans = 1;
    cin >> n;
    for(int i = 1; i <= n; i++) {
      cin >> x;
      int tmp = ans;
      ans = int(ceil(ans * 1.0 / x)) * x;
      if(tmp == ans && i != 1) { ans += x; }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：rainbow_cat (赞：0)

### 思路：
通过简单的思考，我们发现，会出现第 $i$ 个迹象的年份，是比现在的年份大的第一个是 $a_i$ 倍数的年份，那这就很简单了，直接用数学求就好了。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,ans,a[110];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		ans=a[1];
		for(int i=2;i<=n;i++)ans=(ans/a[i]+1)*a[i];//求比现在的年份大的第一个是 a[i] 倍数的年份。
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：OyamaMahiro_qwq (赞：0)

设第 $i$ 个天象出现时间为第 $f_{i}$ 天。

则 $f_i$ 为最小的，大于 $f_{i - 1}$ 的，且能被 $a_i$ 整除的数。

由此写出递推式：$f_i = (\dfrac{f_{i - 1}}{a_i} + 1) \times a_i$。

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		vector <int> a(n + 1);
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			ans = (ans / a[i] + 1) * a[i];
		}
		cout << ans << endl;
	}
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1932B
## 题意
给定 $n$ 个征兆，第 $i$ 个征兆会在 $a _ {i}$ 的整数倍年出现，求第 $n$ 个征兆的出现年份。
## 思路
如果已经经历了第 $i (0 \le i < n)$ 个迹象，那么接下来的迹象的时间有下面三种可能：

- 如果下一个迹象的周期大于当前时间，则世界末日延迟到下一个迹象发生的时间。
- 如果下一个迹象的周期等于当前时间，则世界末日延迟到当前时间 $+$ 下一个迹象发生的周期。
- 如果下一个迹象的周期小于当前时间，则世界末日延迟到下一个迹象下次发生的时间。

综上，我们只要枚举 $n$ 个征兆发生的时间，把答案 $ans$ 替换为当前的征兆下次发生的时间，最后输出 $ans$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100+10;
int t,n,a[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int ans=0;
		for(int i=1;i<=n;i++){
			if(ans<a[i])ans=a[i];
			else if(ans==a[i])ans+=a[i];
			else ans=(ans/a[i]+1)*a[i];
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Cure_Wing (赞：0)

[CF1932B Chaya Calendar](https://www.luogu.com.cn/problem/CF1932B)

### 思路

假设观测上一个迹象是第 $y$ 年，由于第 $i$ 个迹象每 $a_i$ 年出现，每一年不能同时观测两个迹象，于是我们要找到一个最小的周期 $k$，满足 $ka_i>y$，显然 $k=\lfloor\frac{y}{a_i}\rfloor+1$。然后我们让 $y=ka_i$，这是观测第 $i$ 个迹象的最早时间。不断这么做知道观测完为止。

时间复杂度 $O(tn)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
int t,n,a,ans;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cout<<ans<<'\n'){
		cin>>n;ans=0;
		for(int i=1;i<=n;++i){
			cin>>a;
			ans=(ans/a+1)*a;//计算第 i 次观测的时间
		}
	}
	return 0;
}
```

---

## 作者：RyanLi (赞：0)

传送门：洛谷 [Chaya Calendar](https://www.luogu.com.cn/problem/CF1932B) | Codeforces [B. Chaya Calendar](https://codeforces.com/contest/1932/problem/B)

更佳的阅读体验：[CF1932B 题解](https://blog.ryanli.top/index.php/archives/35/)

---

**简要题意**：有 $n$ 个征兆，每个征兆每 $a_i$ 年就会出现一次。征兆必须按 $1$ 到 $n$ 的顺序出现，求出现第 $n$ 个征兆在哪一年。

根据题意，可以知道第 $i$ 个征兆一定在第 $i - 1$ 征兆**之后**发生，因此我们只需要记录第 $i - 1$ 个征兆在哪一年发生即可。

对于第 $i$ 个征兆，每隔 $a_i$ 年就会出现一次，所以直接求出 $a_i$ 的**大于第 $i - 1$ 个征兆发生年份的最小倍数**即可。

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int t, n, x;
ll ans;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        ans = 0;
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> x, ans = x * ((ans + x) / x);
        cout << ans << '\n';
    } return 0;
}
```



---

## 作者：Programming_Konjac (赞：0)

# 赛时思路
先设答案变量 $k$ 为 $0$。

循环 $i:1\rightarrow n$。

对于每次循环：
1. 设 $x$ 为第一个大于 $k$ 的并且可以整除的 $a_i$ 的数。

2. 把 $k$ 赋值为 $x$。

然后就写出了以下代码：
```cpp
int k=0;
for(int i=1;i<=n;i++){
	int x=a[i];
	while(x<=k){
		x+=a[i];
	}
	k=x;
}
```
比赛的时候过了，但是结束之后，我就变成了这个情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/9zuobyzl.png)

我才发现，是循环时间复杂度太高，因此，我就推出了与循环等价的公式：

$$(\lfloor \frac{k}{a_i} \rfloor+1) \times a_i$$

这样就完美解决了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[105];
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int k=0;
		for(int i=1;i<=n;i++){
			int x=floor((double)k/a[i])*a[i]+a[i];
			k=x;
		}
		cout<<k<<"\n";
	}
	return 0;
}
```

---

