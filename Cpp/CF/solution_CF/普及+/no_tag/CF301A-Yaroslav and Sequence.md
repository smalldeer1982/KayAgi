# Yaroslav and Sequence

## 题目描述

现有 $2n-1$ 个整数，每次操作可以使其中的 $n$ 个数 $\times (-1)$。

现在请问进行任意次操作后，这些整数的最大和是多少？

---

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le100,1\le|x|\le1000$

## 样例 #1

### 输入

```
2
50 50 50
```

### 输出

```
150
```

## 样例 #2

### 输入

```
2
-1 -100 -1
```

### 输出

```
100
```

# 题解

## 作者：fuxuantong123 (赞：4)

# CF301A Yaroslav and Sequence 题解
## 思路 
考虑贪心，要尽可能把负数翻转为整数，剩下的负数绝对值尽量小。

如果两次翻转 $n$ 个，并使得其中 $n-i$ 个数相同，则可以看做直接翻转 $2 \times i$ 个数，所以如果有偶数个负数，一定可以全部翻成正数。

如果有奇数个负数，则分两种情况。

若 $n$ 为奇数，则先翻出 $n$ 个奇数，则此时负数总数就变为了偶数，一定也可以全部翻成正数。

若 $n$ 为偶数，则一定有一个数是负数（为 $0$ 也可以），而最优情况显然是使绝对值最小的一个数是负的。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[110];
int main(){
	int n;
	int mi=2147483647;
	int cnt=0;
	int ans=0;
	scanf("%d",&n);
	for(int i=1;i<2*n;i++){
		scanf("%d",&a[i]);
		int x=abs(a[i]);
		mi=min(mi,x);
		ans+=x;
		if(a[i]<0){
			cnt++;
		}
	}
	if(cnt%2==0){
		printf("%d",ans);
		return 0;
	}
	if(n%2!=0){
		printf("%d",ans);
		return 0;
	}
	printf("%d",ans-mi*2);
	return 0;
}

```


---

## 作者：maomao233 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF301A)

[原 OJ 传送门](https://codeforces.com/problemset/problem/301/A)

---

简单分讨，具体地：

- 若 $n$ 为奇数，则**一定可以**将所有的负数都变为正数。

  举个栗子，设序列为：
  $$[-100,-100,-100,-100,-100]$$
  此时 $n=3$，为奇数。于是可以：
  $$[\color{red}100,100,100,\color{black}-100,-100]$$
  $$[\color{red}-100,-100,\color{black}100,\color{red}100,\color{black}-100]$$
  $$[\color{red}100,100,\color{black}100,100,\color{red}100\color{black}]$$
  这样就将所有的负数都变为了正数。
- 若 $n$ 为偶数，则分两种情况：

  - 若序列里负数的个数为偶数个，也可以证明**一定可以**将所有的负数都变为正数。

      再举个栗子，设序列为：
      $$[100,100,100,100,100,-100,-100]$$
      此时 $n=4$，为偶数。于是可以：
    $$[100,100,\color{red}-100,-100,-100,100,\color{black}-100]$$
    $$[100,100,\color{red}100,100,100,\color{black}100,\color{red}100\color{black}]$$
      这样就将所有的负数都变为了正数。
    
  - 若序列里负数的个数为奇数个，可以证明，**一定不可以**将所有的负数都变为正数。

      再举个栗子，设序列为：
      $$[100,100,100,100,-100,-100,-100]$$
      此时 $n=4$，为偶数。可以证明，无论如何都无法将所有的负数都变为正数。而且特别地，每次都会剩下一个负数。由于要让最后的序列总和最大，所以我们应该让这个数的**绝对值尽可能小**。这个过程可以在输入的时候进行判断。
    
这样就分讨完了，得代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define wtl(x) wt(x),putchar('\n')
#define kg putchar(' ')
#define hh putchar('\n')
signed main()
{
	int n;
	rd(n);
	int ans=0,mn=1010,cnt=0;
	for(int i=1;i<=2*n-1;i++)
	{
		int x;
		rd(x);
		ans+=abs(x);
		mn=min(mn,abs(x));
		cnt+=(x<=-1);
	}
	if((n&1)||(!(n&1)&&!(cnt&1)))
	{
		wtl(ans);
	}
	else
	{
		wtl(ans-mn-mn);
	}
	return 0;
}
```

遇到这种题目，草稿纸是万能的。

---

## 作者：Spir1t (赞：1)

### [CF301A](https://www.luogu.com.cn/problem/CF301A)


------------
水题，直接贪心加分讨就行了，具体的请往下看：

首先，我们可以观察到以下几个关键点：

1. 对于任意一个整数，其绝对值肯定是非负数。
2. 如果一个整数为负数，那么它的绝对值就是正数。

根据上述观察，我们可以得出结论：无论是奇数个数还是偶数个数，所有数的绝对值的和 $ans$ 都是非负数。因此，当 $n$ 是奇数时，不论负数的个数是奇数还是偶数，直接输出 $ans$ 即可。

对于 $n$ 是偶数的情况，我们需要进一步考虑负数的个数。如果负数的个数是偶数，那么负数的绝对值也都是非负数，并且每个负数的绝对值都会被计算两次（正负数），因此 $ans$ 的值就是正确的结果。但是，如果负数的个数是奇数，那么必然存在至少一个负数的绝对值只被计算了一次，而其他数的绝对值都至少被计算了两次。为了得到正确的结果，我们需要从 $ans$ 中减去两倍最小的负数的绝对值。

贴个代码：

```
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch > '9' or ch < '0') {
		if (ch == '-')f = -1;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
const int Ma=INT_MAX;
const int Mi=INT_MIN;
int n;
int a[205];
signed main() {
	n=read();
	int ans=0;  // 所有数的绝对值之和
	int num=0;    // 负数的个数
	int mi=Ma;  // 最小绝对值
	for (int i = 0; i < 2*n - 1; ++i) {
		a[i]=read();
		ans += abs(a[i]);
		if (a[i] < 0) {
			num++;
		}
		mi = min(mi, abs(a[i]));
	}
	if (n % 2  or (n % 2 == 0 and num % 2 == 0)) {
		printf("%d qwq\n",ans);
	} else {
		printf("%d\n",ans-mi*2);
	}
	return 0;
}



```
[AC记录](https://www.luogu.com.cn/record/120162580)


---

## 作者：XL4453 (赞：1)

------------
题目分析：

考虑贪心，尽量把负数翻成正数，否则就使得负数尽量小。

首先发现，两次翻转 $n$ 个并使得其中有 $n-1$ 个数相同，可以看做是直接的翻转两个数，那么如果负数的个数是偶数个，一定可以将其全都翻成正数。

然后发现如果 $n$ 是奇数，那么即使有奇数个负数也可以全都翻成正数，具体为翻出恰好 $n$ 个负数，然后一次全都翻正。

剩下唯一一种情况就是负数个数是奇数个，而 $n$ 是偶数。那么就意味着一定有一个数是负的（或者是 0），而最优情况显然是使得绝对值最小的那一个是负的。


------------
代码：
```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[205],minx=2147483647,num,sum;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=2*n-1;i++){
		scanf("%d",&a[i]);
		if(a[i]<0)num++;
		minx=min(minx,abs(a[i]));
		sum+=abs(a[i]);
	}
	if(n&1){
		printf("%d",sum);
		return 0;
	}
	if(num&1){
		printf("%d",sum-2*minx);
		return 0;
	}
	printf("%d",sum);
	return 0;
}
```


---

## 作者：JacoAquamarine (赞：0)

签到题中夹带着贪心

考虑要尽可能把所有数变成正数。

若 $n$ 为奇数，则一定可以变成全部正数，首先翻出 $n$ 个负数，其他的下一次翻完。

若 $n$ 为偶数，显然定有一个数还是负数，考虑最小的哪个。

[Accept](https://codeforces.com/contest/301/submission/222058475)

代码如下：
```cpp
#include<iostream>
#include<cmath>
#define rep(a,b,c) for(int a=b;a<=c;a++)
inline int read();
using namespace std;
int n,ans,minx=INT_MAX,cnt;
int main(){
	cin>>n;
	rep(i,1,2*n-1){
		int x=read();
		ans+=abs(x);
		minx=min(minx,abs(x));
		if(x<0)cnt++;
	}
	if((cnt%2==0&&n%2==0)||n%2==1)cout<<ans<<endl;
	else cout<<ans-minx*2;
	return 0;
}
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
```

---

## 作者：hubin1 (赞：0)

# Yaroslav and Sequence

## 题意

现有 $2n-1$ 个整数，每次操作可以使其中的 $n$ 个数 $\times (-1)$。

现在请问进行任意次操作后，这些整数的最大和是多少？

## 数据范围

对于 $100\%$ 的数据，$1\le n\le100,1\le|x|\le1000$

## 思路
贪心加分类讨论。
- 如果 $n$ 是一个奇数，我们**一定**可以把它都变成非负数。
- 如果 $n$ 是偶数且有**奇数个**负数，这时一定会剩下一个数，因为我们要让最后的和最大，就应该让这个数的**绝对值**尽可能小。
- 如果 $n$ 是偶数但是有**偶数个**负数，可以通过一种方法，把这些数都变成非负数。

## Code
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int minn=INT_MAX;
    int ans=0;//全部的和
    int cnt=0;
    int n,temp;
    cin>>n;
    for(int i=1;i<=2*n-1;i++)
    {
        cin>>temp;
        ans=ans+abs(temp);//把绝对值全部加起来
        minn=min(minn,abs(temp));//找绝对值最小的数
        if(temp<0)
            cnt++;//统计负数个数
    }
    // cout<<ans<<endl;
    if(n%2==1||(n%2==0&&cnt%2==0))
        cout<<ans<<endl;
    else if(cnt%2==1)
        cout<<ans-2*minn<<endl;
    return 0;
}
```

---

## 作者：qfpjm (赞：0)

# 题解

- 分类讨论。

- $n$ 为奇数，那么无论 $a_i$ 里有几个数小于零，都可以变为正。原因：当一段 $a_i<0$ 数量为奇数，那么我们可以翻转包含这段的区间（或者这段区间里面长度为 $n$ 的区间，这取决于 $n$ 的大小），那么负数的数量会变为偶数个，偶数个时，翻转包含这段的区间（或者这段区间里面长度为 $n$ 的区间，这取决于 $n$ 的大小），那么又变回奇数个负数，最后会剩下 $n$ 个连在一起的负数。

- $n$ 为偶数，$a_i$ 中如果有奇数个负数，那么无法全部变为负数，但总会只剩下一个负数。原因：基本同上，无论翻转包含这段的区间，还是这段包含这段翻转区间，剩下的负数个数都为奇数个，最终会剩下 $n + 1$ 个连在一起的负数。$a_i$ 中如果有偶数个负数，可以全变为正，原因完全同上。

- 所以，对于可以全变为正的情况，答案即为 $\sum\limits_{i=1}^{2\times n-1}abs(a_i)$。对于剩下一个为负的情况，为了保证最优，要减去 $a_i$ 中绝数值最小的数两倍。

- 代码十分简单，就不放了。

---

## 作者：ztxtjz (赞：0)

## 【题意】
有$2n-1$个数，每次操作可以将$n$个数变为它的相反数，求操作后$2n-1$个数和的最大值。
## 【思路】
分类讨论

①$n$为奇数: $2n-1$个数可以经过转换全部变为非负数。

样例：$n=1$ {-100}→{100}

②$n$为偶数:负数的个数为奇数时会剩下一个负数（包括$0$），为偶数个时$2n-1$个数可以经过转换全部变为非负数。

样例：$n=2$ {-1,-100,-1}→{1,100,-1}
## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans,k,t=1e5;
int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n*2-1;i++) scanf("%d",&x),ans+=abs(x),k+=x<0,t=min(t,abs(x));  //ans为所有数绝对值的和，k为负数个数，t为所有数绝对值的最小值
	if(n&1||!(n&1)&&!(k&1)) printf("%d",ans);  //n为奇数或n为偶数且负数个数为偶数
	else printf("%d",ans-2*t);  //n为偶数且负数个数为奇数
	return 0;
}
```

---

## 作者：Arvin2018 (赞：0)

~~拖着骨折的右手用左手来发一篇题解~~

这题大概是CF数据有锅 0通过诶 ~~第三个点连damage大佬都WA得和我一样~~

思路：

排序
->
如果有负数，依次将最小的负数*-1
->sum

代码如下（不可食用）
```
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;//输入
	int m = 2*n-1;//用m表示2n-1
	int a[m];//数组
	for(int i = 0; i < m; i++){
		cin >> a[i];
	}
	sort(a, a+m);//从小到大排序
	if(a[0] < 0){//如果最小的为负数
		for(int i = 0; a[i] < 0 && n /*a[i]是负数，n够用*/; i++){
			a[i] *= -1;
			n--;
		}
	}
	long long sum = 0;
	for(int i = 0; i < m; i++){
		sum += a[i];//求和
	}
	cout << sum;//输出
	return 0;
}

```
~~左手也废了~~

UPD

去CF跑了一趟，发现正解（不知道为啥）

```
#include <bits/stdc++.h>
using namespace std;
int n,sum=0,neg=0,m=1001,x;
int main(){
  cin>>n;
  for(int i=0;i<-1+2*n;++i){
    cin>>x;
    neg+=(x<0);
    sum+=abs(x);
    m=min(m,abs(x));
  }
  if(neg%2&&n%2==0)sum-=2*m;
  cout<<sum;
}
```

---

