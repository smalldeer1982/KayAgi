# Preparation for International Women's Day

## 题目描述

International Women's Day is coming soon! Polycarp is preparing for the holiday.

There are $ n $ candy boxes in the shop for sale. The $ i $ -th box contains $ d_i $ candies.

Polycarp wants to prepare the maximum number of gifts for $ k $ girls. Each gift will consist of exactly two boxes. The girls should be able to share each gift equally, so the total amount of candies in a gift (in a pair of boxes) should be divisible by $ k $ . In other words, two boxes $ i $ and $ j $ ( $ i \ne j $ ) can be combined as a gift if $ d_i + d_j $ is divisible by $ k $ .

How many boxes will Polycarp be able to give? Of course, each box can be a part of no more than one gift. Polycarp cannot use boxes "partially" or redistribute candies between them.

## 说明/提示

In the first example Polycarp can give the following pairs of boxes (pairs are presented by indices of corresponding boxes):

- $ (2, 3) $ ;
- $ (5, 6) $ ;
- $ (1, 4) $ .

So the answer is $ 6 $ .

In the second example Polycarp can give the following pairs of boxes (pairs are presented by indices of corresponding boxes):

- $ (6, 8) $ ;
- $ (2, 3) $ ;
- $ (1, 4) $ ;
- $ (5, 7) $ .

So the answer is $ 8 $ .

In the third example Polycarp can give the following pairs of boxes (pairs are presented by indices of corresponding boxes):

- $ (1, 2) $ ;
- $ (6, 7) $ .

So the answer is $ 4 $ .

## 样例 #1

### 输入

```
7 2
1 2 2 3 2 4 10
```

### 输出

```
6
```

## 样例 #2

### 输入

```
8 2
1 2 2 3 2 4 6 10
```

### 输出

```
8
```

## 样例 #3

### 输入

```
7 3
1 2 2 3 2 4 5
```

### 输出

```
4
```

# 题解

## 作者：I_like_magic (赞：10)

这道题其实很简单

要让两数和为 $k$ 的倍数，需要满足以下两条件之一：

- 两数都是 $k$ 的倍数

- 两数的余数和为 $k$

因此，我们可以先统计出余数

再按上述条件算出共有多少组，即可得到答案

**注意：**

- 当 $k$ 为偶数时，余数为 $k/2$ 的数要两两配对，不要多算

- 这里统计的是组数，记得输出时乘 $2$ .

AC Code:

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
inline int read(){
	int s = 0, w = 1; char ch =   getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') w = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s*w;
}
//快读
int n,k,cnt[100],sum;
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		int a=read();
		cnt[a%k]++;
	}
	sum+=cnt[0]/2;
	for(int i=1;i<k/2.0;i++) sum+=min(cnt[i],cnt[k-i]);
	if(k%2==0) sum+=cnt[k/2]/2;//余数为 k/2 的要特殊判断哦！！
	printf("%d",sum*2);//记得乘二
	return 0;//完美收尾
}
```

---

## 作者：AzureMist (赞：6)

如果要组成 $k$ 的倍数，那么选出的两个数 $a$ 和 $b$ 必须满足：$a\%k+b\%k=0$ 或 $k$

其中需特判两种情况：

1.整除的只能互相组合；

2.在 $k$ 为偶数时，余数为 $\frac{k}{2}$ 的也只能互相组合

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int min(int a,int b){
	return a<b?a:b;
}
int main()
{
	int n,k,sum=0;
	cin>>n>>k;
	int d[n],r[k];
	memset(r,0,sizeof(r));
	for(int i=0;i<=n-1;i++)
	{
		cin>>d[i];
		r[d[i]%k]++;//记录余数
	}
	for(int i=0;i<=k/2;i++)
	{
		if(i==0||i*2==k) sum=sum+r[i]/2;//特判
		else sum=sum+min(r[i],r[k-i]); //正常情况，将就少的
	}
	sum*=2;
	cout<<sum;
	return 0; 
} 
```

---

## 作者：fuxuantong123 (赞：4)

# CF1133B Preparation for International Women's Day 题解
## 思路
要使两数和是 $k$ 的倍数，就要使两数都是 $k$ 的倍数或两数的余数和为 $k$。

即 $a \bmod k + b \bmod k = 0$ 或 $k$。

因此，我们可以先计算出余数，存进桶数组，再按上述条件算出共有多少组，即可得到答案。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int mp[110];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	int ans=0;
	for(int i=1;i<=n;i++){
		int fw;
		scanf("%d",&fw);
		mp[fw%k]++;
	}
	for(int i=0;i<=k/2;i++){
		if(i==k-i || i==0){
			ans+=mp[i]/2;
		}
		else{
			ans+=min(mp[i],mp[k-i]);
		}
	}
	printf("%d",ans*2);
return 0;
}
```


---

## 作者：lylahh (赞：2)

### 1.大致题意：

给定一些数字，求其中一共有几对数字之和为 $k$ 的倍数，注意每个数字仅能用一次，即用完就要扔掉！！！~~(题目描述有歧义)~~

~~(我才不会告诉你我就因为没看懂题见着样例懵了十分钟呢)~~

### 2.分析

显然，因为和是 $k$ 的倍数，所以不需要关注 $k$ 及以上的部分，因此要先模 $k$ 。

我们可以用桶来记录， $k$ 的数值也完全撑得住，只需要特判数值为 $0$ 和 $k/2$ 的情况，其他求桶中 $x$ 和 $k-x$ 的较小值即可。

### 3.AC代码

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
inline long long read(){
	long long s=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();}
	while(ch>='0'&&ch<='9'){
		s=(s<<1)+(s<<3)+(ch^48);
		ch=getchar();}
	return s*f;
}//快读 
inline void Scanf();//输入，作者习惯，也可以写在 main 函数里
long long n,k;//输入专用
long long t[105];//桶
long long ans;//记录答案 
int main()
{
	Scanf();
	ans+=t[0]/2;//特判两个数直接被整除的情况(向下取整)
	for(int i=1;i<=k/2;i++)
		if(i*2!=k)
			ans+=min(t[i],t[k-i]);//普通情况下，求两个数的较小值 
		else
			ans+=t[i]/2;//如果枚举到 k 的一半，则输出的值须除以二(向下取整) 
	printf("%lld",ans*2);
	return 0;
}
inline void Scanf(){ //输入 
	n=read();k=read();
	for(int i=1;i<=n;i++)
	{
		long long x=read();
		t[x%k]++;//放入桶中，记得模k
	}
}

```


---

## 作者：andyli (赞：2)

题目要求$k|d_i+d_j$，可以理解为$d_i\%k+d_j\%k=0 \texttt{或} k$，所以先将输入的序列$d$按除以$k$的余数进行分类，假设$cnt[i]$表示输入序列中$\%k=i$ 的数量，那么礼物的个数就是$\frac{cnt[0]}{2}+\{min(cnt[i],cnt[j]) | i <j\}$，当$k$为偶数时，那么礼物个数还要加上$\frac{cnt[\frac{k}{2}]}{2}$，最终答案的箱子数就是礼物个数$\times 2$。  
代码如下：
```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 105;

int cnt[maxn];
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        cnt[x % k]++; // 统计除以k余数的个数
    }
    int ans = cnt[0] / 2; // %k=0时，可以配对%k=0数量/2个礼物
    for (int i = 1, j = k - 1; i <= j; i++, j--)
        if (i == j) // k为偶数时的特殊情况
            ans += cnt[i] / 2;
        else
            ans += min(cnt[i], cnt[j]);
    printf("%d\n", ans * 2); // 箱子数=礼物数*2
    return 0;
}
```

---

## 作者：粤若稽古 (赞：2)

 Talk is cheap, show me your code!
 
 (我之前的bug————
 
 ans=ans+min(cnt[j],cnt[k-j]); 和 ans+=min(cnt[j],cnt[k-j]);
 
 好像是不太一样呢～～
 
 （但是我至今不知道这是什么玄学……QAQ
 
 （聪明的你，可不可以把你的想法分享给我，分享给大家呢？
 
 
 
 	#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #define min(x,y) x<y?x:y
    
    int main(){
        long long n,k,x;
        scanf("%lld%lld",&n,&k);
        long long cnt[1000];
        memset(cnt,0, sizeof(cnt));
        for (long long i = 0; i < n; ++i) {
            scanf("%lld",&x);
            x=x%k;
            cnt[x]++;
        }
        long long ans;
        ans=cnt[0]/2;
        for (long j = 1; j <= k-j ; ++j) {
            if (j < k-j){
                ans+=min(cnt[j],cnt[k-j]);
            }
            else{
                ans+=cnt[j]/2;
            }
        }
        printf("%lld\n",ans*2);
    
    
        return 0;
    }

---

## 作者：zzy_zhouzhiyuan (赞：1)

#### 题目大意
把 $n$ 个数两两组合，且每组的两个数的和是 $k$ 的倍数。

#### 思路分析
两个数的和为 $k$ 的倍数，有两种情况：

+ 两个数都是 $k$ 的倍数

+ 两个数除以 $k$ 的余数的和等于 $k$

因此我们可以用桶来记录余数，将余数为 $1$ 和 $k-1$，$2$ 和 $k-2$ 等搭配，并特判余数为 $0$，以及 $k$ 是偶数时余数为 $k\div2$ 的情况。

AC Code：

```c
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[200005];
int f[105];
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),f[a[i]%k]++;
    int s=f[0]/2;//特殊情况
    for(int i=1;i<=k/2;i++){
        int u=k-i;
        if(i==u)s+=f[i]/2;//特殊情况
        else s+=min(f[i],f[u]);
    }
    printf("%d",s*2);//记得乘2
    return 0;
}
```


---

## 作者：_zxh110408 (赞：1)


[题目传送门](https://www.luogu.com.cn/problem/CF1133B)

## 题意


给你 $n$ 个数，两两组成 $k$ 的倍数。 即，从 $n$ 个数中每次选两个数，这两个数的和必须为 $k$ 的倍数。问最多能选出多少个数满足条件。


## 思路

 $(A+B) \bmod k =A \bmod k + B \bmod k$  。求两个数的和为 $k$ 的倍数 即 两个数分别除以 $k$ 的余数之和是  $k$ 或 $0$ 。更据上面的结论，我们可以把题目中输入的数替换成这个数除以 $k$ 的余数。输入完后将和为 $k$  的两组数两两配对就可以了。

注意：这里要要加两个特判，第一个是本身就是 $k$ 的倍数的数要和它自己配对；第二个是在 $k$ 是个双数时，除以k的余数是 $k$ 的一半的数也是要和它自己配对。


## 代码
```cpp

#include<bits/stdc++.h>
using namespace std;
int main(){
	int k;
	int n;
	cin>>n;
	cin>>k;
	map<int,int>m;
	for (int i=0;i<n;i++){
		int a;
		cin>>a;
		m[a%k]++;
		
	}
	int ans=0;
	for (int i=0;i<k;i++){
		if (i==0 or (k%2==0 and i==k/2)){
			ans+=m[i]/2;
			m[i]/=2;
			continue;
		}
		int cnt=min(m[i],m[k-i]);
		ans+=cnt;
		m[i]-=cnt;
		m[k-i]-=cnt;
	}
	cout<<ans*2<<endl;
	return 0;
} 
```



---

## 作者：mahaoming (赞：0)

# CF1133B Preparation for International Women's Day 题解

### 思路

根据同余定理，要让两数和为 $k$ 的倍数，只要让两数的余数为 $k$ 的倍数即可。所以，我们统计以下所有余数的个数就可以求出答案了。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')w=-1;
		c=getchar();
	}
	while('0'<=c&&c<='9')s=s*10+c-'0',c=getchar();
	return s*w;
}
int n,k,v[105],s,a;
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)a=read(),v[a%k]++;
	for(int i=0;i<=k/2;i++)
		if(i==k-i||i==0)s+=v[i]/2;
		else s+=min(v[i],v[k-i]);
	s*=2; 
	cout<<s;
	return 0;
}

```


---

## 作者：Liu_Tianze (赞：0)

# CF1133B 题解

[**题目链接**](https://www.luogu.com.cn/problem/CF1133B)

推荐跳转至[**我的博客**](https://www.luogu.com.cn/blog/Liu-Tianze/CF1133B)进行阅读

### 题目分析

我们的目标就是选取两个数字，使得两个数之和为 $k$ 的倍数。我们不妨考虑计算每一个数字除以 $k$ 的余数，我们就能通过计算组合后的余数，判断是否能被 $k$ 整除。
  
  符合要求的有以下几种：
  - 两个余数为 $0$ 的数
  - 余数相加为 $k$ 的两个数
  
因此我们就开一个筒子 $cnt[i]$ 表示除以 $k$ 后余数为 $i$ 的数字的个数，在输入时维护。

对于 $ans$ 的计算详见代码即可！

### 代码

直接上 AC 代码

```cpp
#include <iostream>
#define N 200010
#define K 110

using namespace std;

int d[N],cnt[K];

int main(){
	int n,k;
	int ans=0;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		cnt[d[i]%k]++;
	}
	ans+=cnt[0]/2;
	for(int i=1;i<=k/2;i++){
		if(i*2==k){
			ans+=cnt[i]/2;
			continue;
		}
		int low=min(cnt[i],cnt[k-i]);
		ans+=low;
	}
	cout<<ans*2<<endl;
	return 0;
}
```



---

## 作者：Yizhixiaoyun (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/solution/CF1133B)

## 题目分析

我们开两个数组，一个用于输入，另一个存的是其除以 $k$ 余 $i$ 的余数。

如果 $i+j$ 是 $k$ 的倍数，我们就可以配成 $2\times \min(b_i,b_j)$ 个盒子。

需要注意的是，如果 $i = j$ 可以配成 $b_i-(b_i\ mod\ 2)$ 个盒子。

由此便可写出代码。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pf push_front
#define ass assign
#define fst first
#define sec second
#define lb lower_bound
#define ub upper_bound
using namespace std;
long long n,k,ans;
long long a[200010],tong[110];
int main(){
	cin>>n>>k;
	for(register int i=1;i<=n;++i) cin>>a[i];
	for(register int i=1;i<=n;++i) tong[a[i]%k]++;
	for(register int i=0;i<=k/2;++i){
		if(i==(k-i)%k) ans+=(tong[i]/2)*2;
		else ans+=min(tong[i],tong[(k-i)%k])*2; 
	}
	cout<<ans;
}
```


---

## 作者：Daniel_yao (赞：0)

## 题目描述

有 $n$ 盒糖果，第 $i$ 盒糖果有 $d_i$ 颗糖果。你现在要准备一些礼物送给学生。每个礼物包好恰好两个糖果盒，每个糖果盒最多出现在一个礼物中，并且需要保证每个礼物内的糖果总数都能被 $k$ 整除，即若一个礼物包含了 $i,j(i \ne j)$ 盒糖果，则需要保证 $d_i + d_j$ 被 $k$ 整除。

请你求出最多有多少个糖果盒可以成为礼物的一部分。

## 具体思路

枚举 $i$ $mod$ $j$ 所有可能的余数，并记录下来，判断是否有重复，有，更新答案，没有，则继续枚举

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int n, k, f[N];
int main() {
  cin >> n >> k;
  for(int i = 0, x; i < n; i++){
    cin >> x;
    f[x % k]++;  // 统计余数数量
  }
  int ans = 0;
  for(int i = 1, j = k - 1; i <= j; i++, j--){  // 枚举余数
    if(i == j) {
      ans += f[i] / 2 * 2;
    }else{
      ans += min(f[i], f[j]) * 2;
    }
  }
  cout << ans + f[0] / 2 * 2;  // 余数为 0
  return 0;
}
```
完结！！

---

## 作者：linxuanrui (赞：0)

### 思路

考虑和为 $k$ 的倍数的情况：肯定有一个是模 $k$ 为 $a$，另一个模 $k$ 为 $k-a$。

如果你看到这里就写了代码并交了上去，你会发现结果是 WA。为什么呢？是因为我们有一些特殊情况没有考虑到。

当一个数模 $k$ 为 $0$ 或 $\dfrac{k}{2}$ 时，另一个数和他模 $k$ 同余。这里特判一下就好了。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
typedef long long ll;
using namespace std;
int n,k,a[200001],ans,num[101];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(int i = 1;i <= n;i++)cin >> a[i],num[a[i] % k]++;
	for(int i = 0;i <= k / 2;i++){
		if(i == 0 || i * 2 == k)ans += num[i] / 2;
		else ans += min(num[i],num[k - i]);
	}
	cout << ans * 2;
}
```

---

