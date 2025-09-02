# PRIMPERM - Prime Permutations

## 题目描述

$t$ 组数据，每组数据给定一个整数 $n$，求 $n$ 的排列中有多少个排列是质数。

## 说明/提示

$t<10^4$，$n<10^7$

## 样例 #1

### 输入

```
2
13
110```

### 输出

```
2
1```

# 题解

## 作者：_RainCappuccino_ (赞：1)

# 题意
给定一个数 $n$，请求出将 $n$ 拆散后，可以组成的数字中（**无前导零的**）质数的个数。 

# 思路

## First 排列

此题首先需要找出将 $n$ 拆散后的所有没有前导零的排列。

那排列怎么求呢？

有一个 STL：`next_permutation`，可以求出一个数组的下一个排列。

用法：`next_permutation(a + x,a + y)`。

表示求出 $a$ 数组从地址 $x$ 到 $y$ 变化成其的下一个排列。

## Second 判断质数

显然，这道题如果单纯的一个一个判断素数是不行的。

这时候需要用到**欧拉筛了**，它可以线性预处理出一个范围内所有的质数，以及一个数是不是质数，此题 $n \le 10^7$ 可以通过。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define db double
#define M 10000010

#define For(i, j, k) for (int i = j; i <= k; i++)
#define Rep(i, j, k) for (int i = j; i >= k; i--)
#define mem(a, b) memset(a, b, sizeof a)
#define INF 0x3f3f3f3f
#define LNF 0x3f3f3f3f3f3f3f3f
#define endl '\n'
#define IOS (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0))

int num;
int a[10];

bool is_pri[M];
int prime[M];
int cnt;

void euler(int n)//欧拉筛
{
    memset(is_pri, true, sizeof(is_pri));
    is_pri[1] = false; 
    for(int i = 2; i <= n; ++i)
    {
        if(is_pri[i]) prime[++cnt] = i;
        for(int j = 1; j <= cnt && i * prime[j] <= n; ++j)
        {
            is_pri[i * prime[j]] = false;
            if(i % prime[j] == 0) break;
        }
    }
}

signed main(){
    IOS;
    euler(M - 10);//预处理1e7
    int t;
    cin >> t;
    while(t --){
        cin >> num;
        int w = 0,ans = 0;
        while(num) a[++w] = num % 10,num /= 10;
        sort(a + 1,a + 1 + w);//注意得从最小的排列开始，不然枚举不完
        do{
            int p = 0;
            Rep(i,w,1){
                p = p * 10 + a[i];
            }
            if(is_pri[p] && (int)log10(p) + 1 == w) ans ++;
        } while(next_permutation(a + 1,a + 1 + w));//当没有下一个排列是，函数返回false，否则ture
        cout << ans << endl;
    }
    return 0;
}

```



---

## 作者：Adolfo_North (赞：1)

将题目分解成两个部分：

- ###  判断素数

如果用暴力筛因子的方法，在 $t \le 10^4,n \le 10^7$ 下肯定是要超时的，所以用了时间和空间都比较廉价的埃氏筛法。

代码：

```cpp
bool f[10000010];//值为1不是质数。
void init(){
	f[0]=f[1]=1;//0，1不是质数。
	for(int i=2;i<=10000000;i++){
		if(!f[i]){
			for(int j=2*i;j<=10000000;j+=i){
				f[j]=1;//质数的倍数不是质数。
			}
		}
	}
}
```

- ### 全排列

手写全排列太麻烦了，所以这里用函数 `next_permutation`，用法：`next_permutaion(数组名+起始地址，数组名+末尾地址+1)`，注意使用之前要对数组进行升序排序。



------------
代码（前面都讲清楚了，不放注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int w[11],prime[10000010];
bool f[10000010];
void init(){
	f[0]=f[1]=1;
	for(int i=2;i<=10000000;i++){
		if(!f[i]){
			for(int j=2*i;j<=10000000;j+=i){
				f[j]=1;
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	init();
	int T;
	cin>>T;
	while(T--){
		int n,m=0,ans=0;
		cin>>n;
		while(n!=0){
			w[++m]=n%10;
			n/=10;
		}
		sort(w+1,w+1+m);
		do{
			if(!w[1]) continue;
			n=0;
			for(int i=1;i<=m;i++){
				n=n*10+w[i];
			}
			ans+=!f[n];
		}while(next_permutation(w+1,w+m+1));
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/SP8591)

#### 题目大意

共 $T$ 组数据，每组数据给定一个整数 $n$，求 $n$ 的所有排列中有多少个是质数。

$1 \leq n\leq 10^7,t\leq 10^4$

#### 思路

由于数据规模很小，所以可以用用欧拉筛预算出 $[1,10^7]$ 之内的素数，再用 `next_permutation` 暴力算出 $n$ 的全排列，最后输出答案即可。

`next_permutation` 函数功能是输出所有比当前排列大的排列，顺序是从小到大。当排列已经是最大，返回假，否则真。

#### 注意

1. 暴力枚举全排列时先将原序列排序。

2. 0 不能是数字的首位。

普及题，真没什么可讲了。

#### 贴贴代码

```cpp
int main(){
	Euler(Maxn);//筛质数
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);cnt=0;res=0;
		while(n){
			A[++cnt]=n%10; //转换成序列
			n/=10;
		}
		sort(A+1,A+cnt+1); // 排序
		do{
			res+=isprime[toLL()]; 
        		//toLL() 表示转成整数
		}while(next_permutation(A+1,A+cnt+1));
		printf("%lld\n",res);
	}
	return 0;
}
```


---

## 作者：asas111 (赞：0)

## 思路
先将输入数的每一位存进数组，对数组进行排序，接下来开始全排列。

对于全排列，STL 中有一个函数叫 next_permutation，可以很方便地得到下一个全排列。然后将数组组合成 $1$ 个数。但是通过样例发现排列不能有前导 $0$，所以要进行特判。

最后判断素数。直接去暴力判断肯定会超时。因为 $n$ 的范围并不大，可以用埃氏筛预处理。但是要特判 $1$，因为 $1$ 不是素数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[10000009]={0,1},b[19];//特判1
int main(){
	cin>>t;
	for(int i=2;i<=10000000;i++){//埃氏筛
		if(a[i])continue;
		for(int j=2*i;j<=10000000/i*i;j+=i)a[j]=1;
	}
	while(t--){
		int n,k=0,t=0,f=0;
		cin>>n;
		while(n>0)b[++k]=n%10,n/=10;
		sort(b+1,b+1+k);//先排序
		for(int i=1;i<=k;i++)f=f*10+b[i];
		if(!a[f]&&b[1])t++;
		while(next_permutation(b+1,b+1+k)){//下一个全排列
			f=0;
			for(int i=1;i<=k;i++)f=f*10+b[i];
			if(!a[f]&&b[1])t++;//特判前导0
		}
		cout<<t<<endl;
	}
	return 0;
}
```


---

## 作者：fstu (赞：0)

## 题意  
[题目链接](https://www.luogu.com.cn/problem/SP8591)  

输入 $t$ 表示 $n$ 的数量，输入 $t$ 个整数 $n$。  
对于每个 $n$，将 $n$ 的每一位拆出来组成一个序列。记该序列为 $N$。  
对 $N$ 进行全排列，输出 $N$ 的某个排列按照顺序组成的数是素数的排列的数量。  

### 举例  
比如 $n=123$，则 $N=\{1,2,3\}$。  
那么 $N$ 的全排列是：  
$$\{1,2,3\},\{1,3,2\},\{2,1,3\},\{2,3,1\},\{3,1,2\},\{3,2,1\}$$  
上面的每个序列按照顺序组成的数是：  
$$123,132,213,231,312,321$$  
上面的数中没有数是素数，那么就输出 $0$。  

## 分析  
本题有两个重要步骤：  
1. 生成全排列  
2. 判断是否是素数  

### 步骤 1  
用 DFS 的方式枚举每一种排列。  

设当前在求解 $[l,r]$ 区间的元素的全排列。  
如果 $l=r$，则意味着当前已经生成了一次排列，可以开始判断是否是素数了，  
否则遍历当前区间的每一个元素，  
将当前遍历到的元素放到当前区间的首位，即第 $l$ 位，  
递归求解 $[l+1,r]$；  
求解后回溯，将当前区间的第 $1$ 个元素，即第 $l$ 个元素放回原位。  
然后……妥妥的  
![TLE](https://cdn.luogu.com.cn/upload/image_hosting/r9n3f7fg.png)  

用递归的方式求解全排列时间复杂度过高，于是我们可以用 `STL` 库中的 `next_permutation` 来生成全排列。

具体细节请看代码。  

### 步骤 2  
可以用线性筛的方法先筛出来有哪些数是质数。  

考虑对于任意一个大于 $1$ 的正整数 $n$，那么它的 $x$ 倍就是合数（$x > 1$）。  
如果我们从小到大遍历每个数，把当前的数的所有比自己大的倍数标记为合数，那么遍历完成后没有被标记的数就是素数了。  
这就是埃氏筛法，时间复杂度 $O(n\log\log n)$。  

埃氏筛法会将一个合数多次标记，如果能让每个合数都只被标记一次，那么时间复杂度就可以降到 $O(n)$ 了，这就是线性筛。  
具体步骤请看代码。  

（以上内容改编自 [OI-Wiki](https://oiwiki.com/math/number-theory/sieve/)）  

## 代码  
[AC 代码](https://www.luogu.com.cn/paste/nx7yy02w)  
[AC 记录](https://www.luogu.com.cn/record/122598948)  



---

## 作者：Code_Fish_GoodBye (赞：0)

[题目链接](https://www.luogu.com.cn/problem/SP8591)

## 题目大意
给出 $1$ 个数 $n$，求 $n$ 的各位拆分后重新排列组合得到新数是质数的个数。

## 思路（欧拉筛，全排列）
对于求质数，与其每组数据运行 $1$ 次质数筛，不如在一开始就筛出 $[1,10^7]$ 内的所有质数，用 ```bool``` 数组统计起来，这样只需运行 $1$ 次质数筛，大大节约了时间。

对于筛法，这里使用时间复杂度为 $O(n)$ 的线性筛（欧拉筛），模板如下：
```cpp
inline void ola(int n){//欧拉筛 
	isprime[1]=false;//1不是质数 
    for(int i=2;i<=n;i++) isprime[i]=true;//默认都是质数 
    for(int i=2;i<=n;i++){//从2开始筛 
        if(isprime[i]) p[++t]=i;//是质数 
        for(int j=1;j<=t&&i*p[j]<=n;j++){
            isprime[p[j]*i]=false;//如果这个数是质数，那么它的倍数肯定不是质数 
            if(i%p[j]==0) break;
        }
    }
}
```
接下来，我们可以分解 $n$ 的每一位，用数组存起来，使用 ```next_permutation``` 进行全排列，最后得出新数判断即可，时间复杂度 $O(t (\log_{10} n)!)$。

**注意：**

1. 有多组数据。

1. 排列组成的第一个数不能为 $0$。

参考代码（请勿抄袭）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e7+10;
bool isprime[MAXN];
int p[MAXN],t,n,s[10];
inline void ola(int n){//欧拉筛 
	isprime[1]=false;//1不是质数 
    for(int i=2;i<=n;i++) isprime[i]=true;//默认都是质数 
    for(int i=2;i<=n;i++){//从2开始筛 
        if(isprime[i]) p[++t]=i;//是质数 
        for(int j=1;j<=t&&i*p[j]<=n;j++){
            isprime[p[j]*i]=false;//如果这个数是质数，那么它的倍数肯定不是质数 
            if(i%p[j]==0) break;
        }
    }
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ola(10000000);//筛出质数 
	cin>>t;
	while(t--){
		cin>>n;
		int tot=0,ans=0;
		while(n){//分解各位 
			s[++tot]=n%10;
			n/=10;
		}
		sort(s+1,s+tot+1);//从小到大排 
		do{
			if(!s[1]) continue;//排列组成的第一个数不能为0
			int QwQ=0;
			for(int i=1;i<=tot;i++){
				QwQ*=10;
				QwQ+=s[i];//得出新数 
			}
			if(isprime[QwQ]) ans++;//如果是质数，答案加1 
		}while(next_permutation(s+1,s+tot+1));
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Rainbow_Sky (赞：0)

## 思路

首先在这道题目中有两个需要处理的部分：

1. 质数。因为要求是不是质数，一次次的判断又太过麻烦，我们可以通过**欧拉筛**提前预处理好所有数据范围内的质数，最后直接判断即可。

	模板：
	```cpp
	for(int i=2;i<=n;i++)
	{
		if(f[i]==0) p[++cnt]=i;
		for(int j=1;j<=cnt,i*p[j]<=n;j++)
		{
			f[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
	```

2. 全排列。我们可以使用 C++ 内部的一个函数 `next_permutation`。

	`next_permutation`：将当前排列更改为**全排列中的下一个排列**。如果当前排列已经是**全排列中的最后一个排列**（元素完全从大到小排列），函数返回 `false` 并将排列更改为**全排列中的第一个排列**（元素完全从小到大排列）；否则，函数返回 `true`。`next_permutation(v.begin(), v.end())` 或 `next_permutation(v + begin, v + end)`。
   
   这是 OI wiki 中的解释，可以通俗的理解为每次更新一个全排列，没了，就返回 `false`。

就此这道题就可以 AC 了。

---

## 作者：lkjzyd20 (赞：0)

如果用暴力筛因子的方法，在 $t < 10^4, n < 10^7$ 下肯定是要超时的，所以用了时间和空间都较优的埃氏筛法来预处理出 $1 \sim 10^7$ 的质数。

对于每一个 $n$，先提取出 $n$ 的每一位，放到一个数组里。求出数组的全排列，（使用函数 `next_permutation`，用法：`next_permutaion（数组名+起始地址，数组名+末尾地址+1）`，注意使用之前要对数组进行升序排序），之后判断组成的数字是否为素数即可。

代码如下：
```cpp
main()
{
	init(MAXN); //筛素数
	read(t);
   	for(; t; -- t)
   	{
        read(n);
        int cnt = 0, res = 0;
	    for(;n;)
        {
    		a[++ cnt] = n % 10; //转换成序列
	    	n /= 10;
	    }
		sort(a + 1, a + cnt + 1); // 排序
		do{
            if(!a[1]) continue; // 全排列的第一个数字不能是 0
            n = 0;
            rep(i, 1, cnt) n = n * 10 + a[i]; // 将全排列转化成数字
            res += !f[n];
		}while(next_permutation(a + 1, a + cnt + 1));
        write(res, '\n');
	}
	return 0;
}
```

---

## 作者：bigclever (赞：0)

~~自己提交的翻译，那必须写一篇题解啊~~
## 思路：
将 $n$ 的每一位依次**存放到数组**里，再对数组进行全排列，如果该排列是质数，则答案 $+1$。

还要注意两点：
- 因为 $n \lt 10^7$ 且有多组数据，如果对于每一个排列都暴力判断是否为质数的话会超时。所以要用埃氏筛或者欧拉筛**提前筛出质数**，这样就能做到 $O(1)$ 判断。
- 在求 $n$ 的所有排列时可以用 `next_permutation` 函数，这样能解决手写的麻烦。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int num[10],prime[10000005];
bool ok[10000005];
void init(int n){//欧拉筛
        ok[0]=ok[1]=true;
        for(int i=2,cnt=0;i<=n;i++){
            if(!ok[i])prime[++cnt]=i;
            for(int j=1;j<=cnt&&prime[j]*i<=n;j++){
                ok[prime[j]*i]=true;
                if(i%prime[j]==0)break;
            }
        }
}
int main(){
        init(10000000);//筛出质数
        int t; cin>>t;
        while(t--){
            int n,ws=0,ans=0; cin>>n;
            while(n)num[++ws]=n%10,n/=10;//将n的每一位依次存放到数组里
            sort(num+1,num+ws+1);
            do{
                if(num[1]==0)continue;//首位不能为0
                int d=0; 
                for(int i=1;i<=ws;i++)d=d*10+num[i];//转换为数字
                if(!ok[d])ans++;//如果没有被标记，说明是质数
            }while(next_permutation(num+1,num+ws+1));//进行全排列
            cout<<ans<<endl;
        }
	  return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/SP8591)        
简单题。      
我们先预处理出 $1$ 到 $10^7$ 的质数。    
对于每一个 $n$，先提取出 $n$ 的每一位，放到一个数组里。求出数组的全排列，之后判断组成的数字是否为素数。       
这里要注意，数组的第一项不能是 $0$。          
设 $m$ 是 $n$ 的位数，那么这个做法的时间复杂度是 $O(Tm!m)$，可以通过。       
~~这个人一开始想用 Miller_Rabin 水过去~~      
CODE：      
```
//Code by __dest__ruct__or__(uid=592238)
#include <iostream>
#include <algorithm>
using namespace std;
#define umap unordered_map
#define ll long long
#define pii pair<int,int>
#define pll pair<long long,long long>
namespace mySTL{
	inline int max(int a,int b){return a>b?a:b;}
	inline int min(int a,int b){return a<b?a:b;}
	inline int abs(int a){return a<0?-a:a;}
	inline int read(){char c=getchar();int f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline long long readll(){char c=getchar();long long f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline void swap(int &a,int &b){a^=b,b^=a,a^=b;}
	inline void write(int x){if(x<0){putchar('-');x=-x;}
	if(x>=10){write(x/10);}putchar(x%10+'0');}
	inline void writell(long long x){if(x<0){putchar('-');x=-x;}
	if(x>=10){writell(x/10);}putchar(x%10+'0');}
	inline ll pw(ll a,ll b,ll p){if(b==0)return 1;
	if(b==1)return a;
	ll mid=pw(a,b/2,p)%p;
	if(b&1)return mid*mid%p*a%p;else{return mid*mid%p;}}
}
using namespace mySTL;
ll t,n,a[11],m,ans,prime[10000010],ps;
bool b[10000010]={true,true};
void init(){//线性筛
	for(ll i=2;i<=10000000;i++){
		if(!b[i]){
			prime[++ps]=i;
		}
		for(ll j=1;j<=ps&&i*prime[j]<=10000000;j++){
			b[i*prime[j]]=true;
			if(i%prime[j]==0){
				break;
			}
		}
	}
}
int main(void){
	init();
	//freopen("data.txt","r",stdin);
	t=readll();
	while(t--){
		ans=0;
		n=readll();
		m=0;
		while(n){//提取n的每一位
			a[m++]=n%10;
			n/=10;
		}
		sort(a,a+m);//这里不能忘记排序
		do{//求全排列
			if(a[0]==0){
				continue;
			}
			n=0;
			for(int i=0;i<m;i++){//符合要求就生成数字
				n*=10;
				n+=a[i];
			}
			if(!b[n]){
				ans++;
			}
		}while(next_permutation(a,a+m));
		writell(ans);
		putchar('\n');
	}
	return 0;
}
```


---

