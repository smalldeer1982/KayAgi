# Magic Powder - 2

## 题目描述

The term of this problem is the same as the previous one, the only exception — increased restrictions.

## 样例 #1

### 输入

```
1 1000000000
1
1000000000
```

### 输出

```
2000000000
```

## 样例 #2

### 输入

```
10 1
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1 1 1 1 1 1
```

### 输出

```
0
```

## 样例 #3

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

## 样例 #4

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

## 作者：CodeMao (赞：18)

这是本蒟蒻的第一篇题解，希望管理员大大能够通过。

第一次写题解有许多不规范的地方，希望管理员大大能够谅解。

这是个好题目。

主算法：**二分答案**。

注意数据范围，记得开 ```long long```。

思路：

首先运用二分法查找答案 ```mid``` ，```ans=0``` 。

先确定查找范围，因为这题没有明确指出，所以就默认  ```l=0,r=1<<30``` ，这里使用了位运算， ```1<<30```   即 $2^{30}$ ，反正二分查找是 $\text{O}(\log n)$ ，最多循环只会执行 $30$ 次，不用担心超时的问题。只要 ```l<=r``` 就一直执行下去，每次在循环一开始就 ```mid=(l+r)>>1``` ，这里 ```(l+r)>>1``` 就相当于 ```(l+r)/2``` 。

因为有 $M$ 个魔法材料，且每个魔法材料可以变为任意一种原材料。

所以我们可以写一个 ```check``` ，在 ```check``` 中开一个 ```sum``` 变量，```sum=0```，不断加上 ```max(a[i]*mid-b[i],0);```

最后判断 ```sum<=m``` 即可。

如果 ```sum<=m``` , 则 ```l=mid+1,ans=mid;``` 否则 ```r=mid-1```，最后在循环外面输出 ```ans``` 即可。

相信屏幕前的这位巨佬一定听懂了。

下面附上完整 ```AC``` 代码:
```cpp
#include <cstdio>
typedef long long ll; //简易定义long long类型
const int N=100005;
int a[N], b[N], n, k;
ll mx(ll a, ll b){//求两个数中较大数
    return a>b ? a : b;
}
bool check(int x){//检测答案可行性
    ll sum=0;
    for (int i=1; i<=n; i++)
        sum+=mx(1ll*a[i]*x-b[i], 0ll);//注意要转long long类型
    if (sum<=k) return true;
    return false;
}
void in(int &x){//快速输入
	char c=getchar();
	while (c<'0' || c>'9') c=getchar();
	for (x=0; c>='0' && c<='9'; c=getchar())
		x=x*10+c-'0';
}
int main(){
    in(n),in(k);
    for (int i=1; i<=n; i++) 
        in(a[i]);
    for (int i=1; i<=n; i++) 
    	in(b[i]);
    int l=0, r=1<<30, ans=0;
    while (l<=r){//二分答案
	int mid=(l+r)>>1;
        if (check(mid))//检查答案是否可行
            l=mid+1, ans=mid;
	else 
    	    r=mid-1;
    }
    printf("%d\n", ans);
    return 0; //完结撒花
}
```
尊敬的巨佬，麻烦动一动您发财的小手指，帮我这位蒟蒻点个赞吧！同时如果对本蒟蒻的题解有疑问或觉得有不足之处的话，可以再讨论区指出或者私信我哦！您的大恩大德我一定会记一辈子的！


---

## 作者：xiaoxiaoxia (赞：6)

# Part 1 题目意思
今天我们要来造房子。造这个房子需要 $n$ 种原料，每造一个房子需要第 $i$ 种原料 $a_{i}$ 个。现在你有第 $i$ 种原料 $b_{i}$ 个。此外，你还有一种特殊的原料 $k$ 个，每个特殊原料可以当作任意一个其它原料使用。那么问题来了，你最多可以造多少个房子呢？
# Part 2 思路分析
这道题先分析一下数据，作为一名信息学竞赛的学生，分析数据就是一件必不可少的事情。根据题目答案最大 $2\times10^9$ 推出，必定要使用二分答案，那二分答案是什么呢？我就来好好说到说到。
# Part 3 二分查找
在说二分答案之前，先要来说一说二分查找。先来一道题目：有一个由小到大的数列，从中搜索一个数的下标。根据这道题目，我们就来看一下二分查找的模板。
```cpp
while(l<r){
    mid=lt+(r-l)/2;
	if(num[mid]>=s){ //这里的s就是我们要搜索的数
		r=mid;
	}else{
		l=mid+1;
	}
}
```
就是我们从这个数列的中间这个数开始比较，是中间这个数大还是我们要找的这个数大，所以就有三种情况：

|情况|  做法|
| :----------- | :-----------|
|  中间的数=要找的数|      向数列的左边搜索，因为要找到第一次出现这个数的下标|
|  中间的数>要找的数|     向数列左边搜索 |
| 中间的数<要找的数 |  	向数列右边搜索|

这个时候我们不断去重复上述操作，我们可以用 $l$ 来存储这个数列开始的坐标，$r$ 来存储这个数列结束的坐标，$mid$ 来存储这个数列中间这个数的坐标。
#### 注意：找 $mid$ 的值我们最好使用 $l+(r-l)/2$ 而不是 $(l+r)/2$，因为假如这个数列很大, $l+r$ 有可能直接爆了。
那么最后我们就可以找到这个数的下标了，我们要这个数的下标如果简单的遍历，那么时间复杂度就是 $O(nm)$,用二分就可以把时间缩短到 $\log n$。
# Part 4 二分答案
  那么接下来，我们在知道了二分搜索的前提下，我们来看一看二分答案，二分答案的实质就是把前面二分搜索的数列变为我们答案的所有可能性，$mid$ 就是我们尝试的答案，二分答案的前题就是答案具有单调性，直接将有点难以理解，还是直接上[题](https://www.luogu.com.cn/problem/P1577)。

首先是看一下题目，是符合单调性的，然后这些长度都是两位小数，非常不方便我们二分，这边就把所有的长度都 $\times100$，最后把答案再 $/100$，就可以避免了。
  
我们这里假设，绳子最长是题目里给的 $100000.00\times100$ 后就是 $10000000$，这就是答案的最大值，不可能会比这个大，那么答案的最小值就是 $0$，所以 $l=0,r=10000000$，所以我们这里把这个数组开始二分，那么现在的难点就是验证这个答案能不能取到。
  
我们现在用每一个长度去除以 $mid$，把每一个段数加起来，然后把这个总段数和我们要的段数 $K$ 进行比较，我们假设这个总段数为 $num$，结论：



 情况| 做法
| :----------- | :----------- |
| $num>K$| 向右搜索| 
|  $num=K$|  向右搜索|
| $num<K$ |  向左搜索|


向右搜索，我们就把 $l=mid$ 向左搜索，我们就把 $r=mid$ 然后不断收缩，这个 $mid/100$ 就是最终的答案。
# Part 5 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+5;
ll n, k, a[maxn], b[maxn];
bool check(ll mid) 
{
	ll kk=k;
	for(int i=1;i<=n;i++) 
	{
		if(mid*a[i]-b[i]>0) 
		{
			kk-=mid*a[i]-b[i];
			if(kk<0)return false;
		}
	}
	return true;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];	
	}
	ll l=0,r=2e9;
	while(l<r) 
	{
		ll mid=l+(r-l+1)/2;
		if(check(mid))
		{
			l=mid;
		}
		else 
		{
			r=mid-1;
		}
	}
	cout<<l<<endl;
}
```

---

## 作者：鎏金 (赞：5)

# ~~这是一道大水题~~
###### 狗头滑稽
###  _个人理解（还有本人老师）_
## 本题要用到二分法和贪心（主要是二分）！！
##### 第一次发题解有不对的地方还请关照，代码里的注释会比较详细。
###### 备注：我是c++党。代码已AC
### 下面见代码
##### 求审核大大给个通过！！！
## 多谢@稀音Seine大佬的帮助理解！！

------------

```cpp
#include<bits/stdc++.h>
using namespace std;//本体采用二分法 
typedef long long lol;//简化long long 定义 

lol n;//n为材料种类 
lol a[100005],b[100005];//a为 每个要多少个 ,b为有多少个
lol k;//魔法材料的个数 

int main()//主函数 
{
	cin>>n>>k;//输入材料种类数、魔法材料个数 
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];//循环输入要用到的每种材料数、拥有的材料数 
	lol l=0;//定义l表示结果，应该也表示二分答案最初的左端，初始化为0 
	lol r=2e9;//r表示二分最右一端点 
	while(l<r)//如果二分图中间存在值，开始循环 
	{
		lol mid=(l+r)/2;//定义中间值middle为左右端点的1/2 
		lol pro=k;//用pro代表k的值，意义相当于k的一个备份  
		if(l+1==r)mid=l+1;// 由于整形除法直接截掉余数  ，提前进行操作 
		for(int i=1;i<=n;i++){//开循环，循环次数为材料种数次 
		pro-=max(a[i]*mid-b[i],0LL);//0LL意为longlong类型的0，给魔法材料数减去使用材料数，结果为剩余材料数 
		/*a【i】表示第i种材料的需求，mid表示此时中间值
		b【i】表示第i种材料已经有的数量，表示需要的魔法粉的值     */ 
		if(pro<0)//若魔法粉的数量少于0， 
		break;//则应结束整个for循环，否则继续循环 
		}
		if(pro>=0)//若魔法粉刚好用完或有剩余 
		l=mid;//给l赋值为middle  
		else r=mid-1;//否则重置右端点继续进行循环 
	}
	cout<<l;//输出结果 
	return 0;
}

```


---

## 作者：豆浆 (赞：4)

Magic Powder系列题解：

#### [题目](https://www.luogu.org/problem/CF670D2)

题目大意：

	给你N种材料，以及M个魔法材料。
	每个魔法材料可以变成任意一种魔法材料。
	现在已知做一个饼干要用每种材料Ai个，而且已知每种饼干我们初始有Bi个。
	问最多可以做出来多少饼干。



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

## 作者：chenziyang1 (赞：1)

## 题意简述
有 $n$ 种材料，以及 $m$ 个魔法材料。

每个魔法材料可以变成任意一种材料。

已知做一个饼干要用每种材料 $a_{i}$ 个，而且每种饼干初始有 $b_{i}$ 个。

问最多可以做出来多少饼干。
## 思路
  **二分答案**即可。
  
  如果还不知道二分是什么，可以看一下这个[oi-wiki链接](https://oi-wiki.org/basic/binary/)。
  
  二分的时间复杂度是 $O(\log(n))$，**不会超时**。
 
  我们可以写一个 $\operatorname{check}$ 函数，用于**判断当前答案是否正确**。
  
 $\operatorname{check}$函数的思路如下：
  1. 创建一个变量 $need$，作为当前需要使用的魔法材料数量。
  2. 枚举材料数，依次判断是否符合条件。
  3. 如果 $a_{i} \times x-b_{i}>k$，说明魔法材料不够用，返回错误消息。
  4. 否则每次对 $a_{i} \times x-b_{i}$ 和 $0$ 进行比较，用 $need$ 累加较大的那个。
  5. 枚举完毕后，判断 $need$ 是否大于数据给出的最多可使用的魔法材料数量。如果大于，返回错误消息。否则返回正确消息。
  
## 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define vl vector<ll>
vl a, b;
ll n, k, mi, ma;
```
```cpp
int check(ll x){
	ll need = 0;//1.
	for(int i = 1; i <= n;i++){//2.
		if(a[i] * x - b[i] > k)return 0;//3.
		need += max(a[i] * x - b[i], 0ll);//4.（0ll的意思是long long类型的0）
	}
	return need <= k;//5.
}
```
```cpp
int main(){
	cin >> n >> k;
	a = b = vl(n + 1);//初始化a,b(修改a,b的大小为n+1)。
	for(int i = 1; i <= n;i++){
		cin >> a[i];
	}
	for(int i = 1; i <= n;i++){
		cin >> b[i];
	}
	ll l = 0, r = 2e9;
	while(l<=r){//二分
		ll mid = l + r >> 1;//>>和/2等价
		if(check(mid)){
			l = mid + 1;
		}else{
			r = mid - 1;
		}
	}
	cout << l - 1 << "\n";
}

```
Update in 2023.8.18：修改不合理处,更改排版。

Update in 2024.3.6：修改不合理处

---

## 作者：Ninelife_Cat (赞：1)

本题的翻译不太清楚，建议去[弱化版](https://www.luogu.com.cn/problem/CF670D1)看。

由于 $n$ 的范围比较大，暴力枚举会超时，所以考虑二分。

设 $mid$ 为做出来的饼干数量，那么每种材料就需要 $a_i\times mid$ 个。

如果该材料的数量 $b_i$ 少于需要的数量，就用魔法材料代替缺少的那部分。

最后只判断需要魔法材料的数量是否大于 $m$ 就行了，如果大于 $m$ 就是不合法的。

核心代码：

```cpp
const int N=1e5+10;
int n,m,a[N],b[N],ans;
inline bool Check(int mid)
{
	ri unsigned long long res=0;//res记录需要多少魔法材料
	for(ri int i=1;i<=n;++i)
	{
		if(mid*a[i]>b[i]) res+=mid*a[i]-b[i];
		if(res>m) return 0;//小坑点:必须边做边判不合法的情况,否则res可能会溢出
	}
	return res<=m;
}
signed main()
{
	n=read();m=read();
	for(ri int i=1;i<=n;++i)
		a[i]=read();
	for(ri int i=1;i<=n;++i)
		b[i]=read();
	ri int l=0,r=2e9;
	while(l<=r)
	{
		ri int mid=l+r>>1;
		Check(mid)?ans=mid,l=mid+1:r=mid-1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## HV 思路

和 EV 没什么区别。

二分答案。

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

## 作者：Fislett (赞：0)

[更好的阅读体验](https://tongyuxin.blog.luogu.org/solution-cf670d2)
# 1. 题意
题目大意就是一块曲奇饼干需要 $n$ 种食材，第 $i$ 种需要 $a_i$ 克，而你手中有这种食材 $b_i$ 克，还有另外 $k$ 克食材每一克可以代替任何一种食材一克，求最多能做多少块曲奇。
# 2.思路
由于食材数量是固定的，那么肯定存在一个 $mid$，使得食材能够烘焙出 $1 \sim mid$ 块曲奇，而不能烘焙出 $mid$ 以上块曲奇。我们只需要二分寻找出 $mid$ 即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100001], b[100001];
long long n, k, l, r, ans;
bool check(long long mid)
{
    long long sum = 0;
    for (long long i = 1; i <= n; i ++)
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

