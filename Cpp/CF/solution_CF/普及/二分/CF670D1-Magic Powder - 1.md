# Magic Powder - 1

## 题目描述

**注意**：本题有两个不同的版本，分别对应两个不同的难度。

早晨醒来，Apollinaria决定烘焙曲奇。烘焙一块曲奇需要 $n$ 种食材，她知道对于每一种食材需要在曲奇中放入 $a_i$ 克。为了准备一块曲奇，Apollinaria需要准备所有 $n$ 种食材。

对于第 $i$ 种食材，Apollinaria有 $b_i$ 克。她拥有 $k$ 克魔法能量。每 $1$ 克魔法能量都能恰好转换成为任意 $n$ 中食材中的一种。

请你帮助Apollinaria计算她使用已有的食材和她的魔法能量最多可以烘焙出多少曲奇。

## 说明/提示

样例一说明：将 $1$ 个魔法能量转换成第 $2$ 个食材，这样可以制作出 $4$ 块曲奇。

样例二说明：将 $2$ 个魔法能量转换成第 $1,3$ 个食材，这样可以制作出 $3$ 块曲奇。剩下的 $1$ 个魔法能量可以不使用，因为这不会使得最终答案增加。

## 样例 #1

### 输入

```
3 1
2 1 4
11 3 16
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 3
4 3 5 6
11 12 14 20
```

### 输出

```
3
```

# 题解

## 作者：wuyixiang (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF670D1)

题目大意：制一块曲奇需要第 $i$ 种材料 $a_i$ 克，你可以变出任意 $k$ 克材料，现在已经有 $b_i$ 克，问最多可以制作几个曲奇。

不难想到答案具有单调性，而且数据挺水，考虑二分。

每次可以设置一个 $mid$（$l$ 与 $r$ 的均值），如果符合条件，则往上找；否则往下找。这里注意：为了避免死循环，计算 `(l + r) / 2` 时，应该还要再加个 `1`。详见代码。

最后是函数部分了。这个很简单，直接判断 $\sum\limits\max(mid \times a_i - b_i) $ 是否 $\le k$ 即可。

附代码：

```cpp
#include <iostream>
#define int long long
using namespace std;
int n,m,a[200005],b[200005],l = 0,r = 1e9;
bool check(int mi)
{
    int sum = 0;
    for(int i = 1;i <= n; i++)
        sum += max(0LL,a[i] * mi - b[i]);//求还需要的克数
    return sum <= m;
}
signed main()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i ++)cin >> a[i];
    for(int i = 1;i <= n;i ++)cin >> b[i];
    while(l < r)//二分
    {
        int mid = (l + r + 1) / 2;
        if(check(mid))l = mid;
        else r = mid - 1;
    }
    cout << l;
}
```

---

## 作者：豆浆 (赞：1)

Magic Powder系列题解：

#### [题目](https://www.luogu.org/problem/CF670D1)

题目大意：

	做一个饼干需要有n种材料，每种材料需要ai克。现在每种材料有bi克。还有k克神奇材料，可以代替那n种材料。1克神奇材料替换1克普通材料。



思路：



	明显如果我们能够做出来x个饼干，那么一定能够做出来x-1个饼干，同理x-2也一定能够做出来。
	所以这里一定有一个单调性在这里边。
	那么我们二分结果就行。
	注意数据范围~
    
代码：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
template <typename _Tp> inline void read(_Tp&x){
    char ch;bool flag=0;x=0;
    while(ch=getchar(),!isdigit(ch))if(ch=='-')flag=1;
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    if(flag)x=-x;
}
using namespace std;
long long n,m;
long long a[150010];
long long b[150010];
long long slove(long long mid){
    long long sum=0;
    for(long long i=1;i<=n;i++){
        if(b[i]-a[i]*mid<0){
        	sum+=b[i]-a[i]*mid;
		}
        if(-1*sum>m){
        	return 0;
		}
    }
    if(sum>=0){
    	return 1;
	}
    if(sum<0&&-1*sum<=m){
    	return 1;
	}
    return 0;
}
int main(){
	long long ans=0;
    long long l=0;
    long long r=2000000000;
    read(n);
    read(m);
    for(long long i=1;i<=n;i++){
        read(a[i]);
	}
    for(long long i=1;i<=n;i++){
    	read(b[i]);
	}
    while(r-l>=0){
        long long mid=(l+r)/2;
        if(slove(mid)==1){
            l=mid+1;
            ans=mid;
        }
        else{
            r=mid-1;
		} 
    }
    cout<<ans;
	return 0;
}
```




---

## 作者：Erica_N_Contina (赞：0)

## EV&HV 思路

很明显如果我们考虑直接计算出答案，那么我们无法知道我们应该如何计算每一种食材需要用多少能量来转化。所以我们使用**正难则反**的思想，考虑**二分答案。**

我们二分 Apollinaria 最终可以烘焙出多少曲奇，如何使用 `check` 函数来检查当前二分的值是否合法。在 `check` 函数中，因为我们已经知道最终要烘焙出多少曲奇，所以我们可以直接计算出对于每种食材我们需要多少能量来转化。这样我们就可以统计出在当前二分的值下我们一共需要多少能量，与 $k$ 进行比较即可得出是否合法。

注意一点，我们在二分时设定上界要注意，不能太小，但是太大了会爆 long long。笔者的上界定在 $2^{34}$，约 $1.7\times 10^{10}$，并且如果把上界定为 $2\times 10^{10}$ 就会爆。





## 代码

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}


// void solve(){

//     cerr<<"\nintrr[][]=";
//     for(int i=1;i<=n;i++)cerr<<t[i].l<<' '<<t[i].r<<endl;
// }



const int N=5e5+5;
 const int M=5e5+5;
const int INF=2e9+5;
const int MOD=2e9+7;
bool f1;
int n,t,k;
int b[N],base;
int ans;
int a[N];
bool f2;


bool check(int x){
	int t=k;
	for(int i=1;i<=n;i++){
		t-=max(0ll,1ll*x*a[i]-b[i]);if(t<0)return 0;
	}
	if(t<0)return 0;
	return 1;
}


signed main(){

    // freopen("woof.in","r",stdin);
    // freopen("woof.out","w",stdout);

	n=rd,k=rd;
	for(int i=1;i<=n;i++)a[i]=rd;
	for(int i=1;i<=n;i++)b[i]=rd;

	int l=0,r=1ll<<34;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}

	cout<<ans<<endl;
    
}

/*
2 5
0 1 1 1 1
0 1 1 2 4
0 2 1 2 1
0 2 1 1 4
*/
```




---

## 作者：rainbow_cat (赞：0)

### 思路：一个很简单的二分答案    
二分的区间是从 $0$ 到 $b_i$ 中的最大值。在这里我们使用二分的第二个模版也就是 `(l+r+1)/2`，这里重点讲解 check 函数怎么写。首先便利每一个食材，判断其数量是否足够制作 $x$ 个曲奇。如果不够就就用魔法食材代替，当魔法食材耗尽且当前食材不够，返回 $0$。   
#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1010],b[1010],l,r;
bool check(int x)
{
	int f=k;
	for(int i=1;i<=n;i++)
	{
		if(b[i]+f<a[i]*x)return 0;
		if(b[i]<a[i]*x&&(a[i]*x-b[i])<=f)f-=a[i]*x-b[i];
	}
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		r=max(r,b[i]);
	}
	r+=k;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		if(check(mid))l=mid;
		else r=mid-1;
	}
	cout<<l;
	return 0;
}
```

---

## 作者：MujicaSaki (赞：0)

### 思路：

因为饼干数量具有单调性，所以考虑二分答案。

我们把各个具有的材料数量和所需的材料数量倍数关系算出来。如果材料数量足够做 $x$ 个饼干则直接看下一个材料，而如果不够就使用魔法材料。并且判断魔法材料是不是够。

二分就不说了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[100005],b[100005],maxn,s,mid;
inline char ftgetc(){
	static char s[1000000],*p=s+1000000,*pend=s+1000000;
	if (p==pend){
		p=s;
		fread(s,1,1000000,stdin);
	}
	return *p++;
}
inline long long read(){
	register long long n(0),c(ftgetc());
	while (48>c||c>57) c=ftgetc();
	while (48<=c&&c<=57){
		n=(n<<1)+(n<<3)+(c^48);
		c=ftgetc();
	}
	return n;
}
long long check(long long x)
{
	bool f=1;
    for(int i=1;i<=n;i++)
	{
        if(b[i]/a[i]<x)
        {
            if(k>=((b[i]/a[i])+x-b[i]/a[i])*a[i]-b[i]) k-=((b[i]/a[i])+x-b[i]/a[i])*a[i]-b[i];
            else 
            {
                f=0;
                break;
            }
        }
	}
	return f;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
    for(int i=1;i<=n;i++) maxn=max(maxn,b[i]/a[i]);
    long long l=1,r=maxn+k/n,k1=k;
	while(l<=r)
	{
		mid=(l+r)/2;
        if(check(mid)) l=mid+1;
        else r=mid-1;
        k=k1;
	}
	cout<<r;
}
```


---

## 作者：Dehydration (赞：0)

### 前言：

这是 Magic Powder 系列的第一题，作为第一题，咱洛谷题解里全是解决第二题的二分方法，我就来说一下~~菜鸡系列~~的暴力方法！这个很重要，数据小了我们也要随着他吗！等会只会打正解不会骗分了！而且我的复杂度与他们不相上下！

ps：附上我的[博客](https://www.luogu.com.cn/blog/661534/)，[题目](https://www.luogu.com.cn/problem/CF670D1)和[我的提交记录](https://cdn.luogu.com.cn/upload/image_hosting/02qls87h.png)。

### 思路：

言归正传，暴力的思路很好想，定义一个 ```for(K=0;;K++)``` 来从零开始搜索答案，每次将 ```b[i]=b[i]-a[i]``` 如果 ```b[i]<0``` 就记录下来累加，如果累加和超过 $K$，就代表答案就是现在的 $K$，```break```掉然后输出答案，反之 $K$ 减掉累加和继续搜索，直到搜到为止。

但有几个我掉过的坑：

1. ```if(b[i]<0)```时你要累加```abs(b[i])```或者减去```b[i]```（因为```b[i]<0```）。

2. 还是```if(b[i]<0)```时你要将```b[i]```归回 0，因为 $k$ 将他给还清了。

3. 要开```long long```。

对了，还有一个优化，你可以在输入时候定义一个```MIN =LONG_LONG_MAX``` ，记录所有 ```b[i]/a[i]```的最小值，从 ```for(K=MIN;;K++)```开始搜，但在这里没什么用~~都能过~~，就省略了。



### 代码：

```
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[1005],b[1005];//不开long long见祖宗！
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
    /*
	可以MIN优化
	for(int i=1;i<=n;i++)cin>>b[i],MIN=min(a[i]/b[i],MIN);
	for(int i=1;i<=n;i++)a[i]-=b[i]*MIN;这个一定要啊 
	for(K=MIN;;K++)
	{
		......
	}
	*/
	long long K;
    for(K=0;;K++)//从0开始搜
    {
    	long long sum=0;
    	for(int i=1;i<=n;i++)
    	b[i]-=a[i];
    	for(int i=1;i<=n;i++)
    	if(b[i]<0)
    	sum=sum+abs(b[i]),b[i]=0;
    	if(sum>k)
    	{
    		break;
		}
		k-=sum;
	}
	cout<<K<<'\n'; //k和K不要弄混了
    return 0;
}


```

---

## 作者：Marshall001 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF670D1)

## 题目大题

Apollinaria 想要烘培一些曲奇。烘焙一块曲奇需要 $n$ 种食材，对于每一种食材需要在曲奇中放入 $a_i$ 克。为了准备一块曲奇，Apollinaria 需要准备所有 $n$ 种食材。

对于第 $i$ 种食材，Apollinaria 有 $b_i$ 克。她拥有 $k$ 克魔法能量。每 $1$ 克魔法能量都能恰好转换成为任意 $n$ 中食材中的一种。

请求出 Apollinaria 最多可以烘焙出多少曲奇。

## 思路

稍加思考就能看出这是一道二分题。我们只需要从 $0$ 到曲奇上线一直二分，最后得出的值就是最后的答案了。

## 代码

```cpp
#include <iostream>
using namespace std;
const int MAXN=1e3+5;
int n,K;
int a[MAXN],b[MAXN];
bool check(int x){
	int k=K;
	for(int i=1;i<=n;i++){
		int sum=a[i]*x;
		if(sum>b[i]){
			if(k>=sum-b[i]){
				k-=sum-b[i];
			}
			else{
				return 0;
			}
		}
	}
	return 1;
}
int main(){
	cin>>n>>K;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	int l=0,r=2000,ans=0;//注意，曲奇的上限是2000，而不是1000
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)==1){
			l=mid+1;
			ans=mid;//记录答案
		}
		else{
			r=mid-1;
		}
	}
	cout<<ans;
	return 0;
}
```

## THE END

---

## 作者：Fislett (赞：0)

[更好的阅读体验](https://tongyuxin.blog.luogu.org/solution-cf670d1)
# 1. 题意
题目大意就是一块曲奇饼干需要 $n$ 种食材，第 $i$ 种需要 $a_i$ 克，而你手中有这种食材 $b_i$ 克，还有另外 $k$ 克食材每一克可以代替任何一种食材一克，求最多能做多少块曲奇。
# 2.思路
由于食材数量是固定的，那么肯定存在一个 $mid$，使得食材能够烘焙出 $1 \sim mid$ 块曲奇，而不能烘焙出 $mid$ 以上块曲奇。我们只需要二分寻找出 $mid$ 即可。
# 3.代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1001], b[1001];
long long n, k, l, r, ans;
bool check(long long mid)
{
    long long sum = 0;
    for(long long i = 1; i <= n; i ++)
	{
        if (b[i] < a[i] * mid) sum += a[i] * mid - b[i];
        if (sum > k) return false;
    }
    if (sum <= k) return true;
    return false;
}
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i ++) scanf("%d", &b[i]);
	l = 0, r = 2e9;
	while (l <= r)
	{
		long long mid = l + r >> 1;
		if (check(mid)) {l = mid + 1; ans = mid;}
		else r = mid - 1;
	}
	printf("%lld", ans);
}
```

---

