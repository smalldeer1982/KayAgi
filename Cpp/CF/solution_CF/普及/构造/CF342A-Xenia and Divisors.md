# Xenia and Divisors

## 题目描述

Xenia the mathematician has a sequence consisting of $ n $ ( $ n $ is divisible by 3) positive integers, each of them is at most 7. She wants to split the sequence into groups of three so that for each group of three $ a,b,c $ the following conditions held:

- $ a&lt;b&lt;c $ ;
- $ a $ divides $ b $ , $ b $ divides $ c $ .

Naturally, Xenia wants each element of the sequence to belong to exactly one group of three. Thus, if the required partition exists, then it has ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF342A/cf2733ea0aacbe28f053605e4a0603ddeb7a4835.png) groups of three.

Help Xenia, find the required partition or else say that it doesn't exist.

## 样例 #1

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
6
2 2 1 1 4 6
```

### 输出

```
1 2 4
1 2 6
```

# 题解

## 作者：FQR_ (赞：10)

[题目传送门](/problem/CF342A)

### 思路

因为所有的数字都不大于 $7$ ，我们不难发现，能组成三元组的只有三种搭配：

1. `1 2 4`

1. `1 3 6`

1. `1 2 6`


在这三种搭配中，不存在数字 $5$ 和 $7$ 。所以如果输入的数字含有 $5$ 或 $7$ ，就输出`-1`。

---

接下来，我们可以发现，数字 $4$ 只在第一种搭配中出现过，数字 $3$ 只在第二种搭配中出现过。

所以，数字 $4$ 只能出现在第一种搭配中，数字 $3$ 只能出现在第二种搭配中。

我们先从第一种搭配和第二种搭配入手。如果这个特殊数字的数量多于其他两个数字的数量，输出`-1`。否则，这个搭配输出的个数就是特殊数字的数量。

最后，处理第三种搭配。如果剩下的 $1 , 2 , 6$ 数量相等 ，这种搭配输出的个数就是其中一个的数量。否则输出`-1`。

---

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void finish()
{
	cout<<-1;
	exit(0);
}
int n,a[10],x,y,z;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++)
	{
		int m;
		cin>>m;
		if(m==5||m==7) finish();
		a[m]++;
	}
	if(a[4]>a[1]||a[4]>a[2]) finish();
	x=a[4];a[1]-=a[4];a[2]-=a[4];
	
	if(a[3]>a[1]||a[3]>a[6]) finish();
	y=a[3];a[1]-=a[3];a[6]-=a[3];
	
	if(a[1]!=a[2]||a[1]!=a[6]||a[2]!=a[6]) finish();
	z=a[1];
	
	while(x--) cout<<"1 2 4"<<endl;
	while(y--) cout<<"1 3 6"<<endl;
	while(z--) cout<<"1 2 6"<<endl;
	return 0;
}


```

---

## 作者：ztyo_zysclown (赞：6)

首先，因为 $n$ 小于等于 $7$，那么能组成的方案数只有三种，即
```
1 3 6

1 2 6

1 2 4
```
于是我们就可以发现，这三种方案是没有 $5$ 和 $7$ 的，所以一旦序列中出现了 $5$ 和 $7$ 直接无解，可以输出 $-1$。

那么，排除了以上两种方案外，当序列中有 $3$ 时，那么 $3$ 只能放在 $1 3 6$ 这一种组合中，于是可以发现：因为 $3$ 只有这一种情况，所以当 $1$ 小于 $3$ 或 $6$ 小于 $3$ 时，也是无解的。如果有解 $3$ 的个数就是解的个数。

接下来，排除 $1 3 6$ 这种方案外，$6$ 就只能存在于 $1 2 6$ 这个方案，与 $3$ 同理，当 $1$ 小于 $6$ 或 $2$ 小于 $6$ 时，是无解的如果有解，$6$ 的个数就是解的个数。

然后，$4$ 就只能在 $1 2 4$ 这一种方案中，与上同理，但这里由于排除过上面两种方案，那么就不是小于的个数了，是等于，此时解的个数是 $1$ 的个数，$2$ 的个数，$4$ 的个数中的任意一个。

下面是代码
```
#include<bits/stdc++.h>
using namespace std;
int n;
int a[111000];
int a1,a2,a3,a4,a5,a6,a7;
int main(){
    cin>>n;
    bool s=false;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]==5||a[i]==7){
            s=true;
        }
        if(a[i]==1){
            a1++;
        }
        if(a[i]==2){
            a2++;
        }
        if(a[i]==3){
            a3++;
        }
        if(a[i]==4){
            a4++;
        }
        if(a[i]==5){
            a5++;
        }
        if(a[i]==6){
            a6++;
        }
    }
    if(s==true){
        cout<<-1;
        return 0;
    }
    int sum6;
    int sum4;
    int sum3;
    if(a1<a3||a6<a3){
        cout<<-1;
        return 0;
    }
    a6=a6-a3;
    a1=a1-a3;
    sum3=a3;
    if(a2<a6||a1<a6){
        cout<<-1;
        return 0;
    }
    a2=a2-a6;
    a1=a1-a6;
    sum6=a6;
    if(a2!=a1||a4!=a2){
        cout<<-1;
        return 0;
    }
    sum4=a1;
    for(int i=1;i<=sum3;i++){
        cout<<"1 3 6"<<endl;
    }
    for(int i=1;i<=sum6;i++){
        cout<<"1 2 6"<<endl;
    }
    for(int i=1;i<=sum4;i++){
        cout<<"1 2 4"<<endl;
    }
    return 0;
}
```


---

## 作者：dabenBbx (赞：3)

我们可以较为轻松的发现满足题目要求的数对有 $3$ 个。

如下所示：

``1 2 4``，``1 2 6``，``1 3 6``。


可以证明没有其他满足题目要求的数对。

所以，我们只需要判断出这个序列的每一个数出现的次数就可以了。

我们开一个数组，统计每一个数出现的次数即可。

代码如下所示：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[8],b,c,d;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int m;
        cin>>m;
        if(m==5||m==7){
            cout<<-1;
            return 0;
        }
        a[m]++;
    }
    if(a[4]>a[1]||a[4]>a[2]){
        cout<<-1;
        return 0;
    }//如果4的个数超过1或2
    b=a[4];
    a[1]-=a[4];
    a[2]-=a[4];
    if(a[3]>a[1]||a[3]>a[6]){
        cout<<-1;
        return 0;
    }//如果3的个数超过1或6
    c=a[3];
    a[1]-=a[3];
    a[6]-=a[3];
    if(a[1]!=a[2]||a[1]!=a[6]||a[2]!=a[6]){
        cout<<-1;
        return 0;
    }
    d=a[1];
    while(b--)cout<<1<<" "<<2<<" "<<4<<"\n";
    while(c--)cout<<1<<" "<<3<<" "<<6<<"\n";
    while(d--)cout<<1<<" "<<2<<" "<<6<<"\n";
    //循环输出
    return 0;
}
```


---

## 作者：zk_y (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF342A)

题目比较简洁，我们发现数列中的每一个数 $num$ 都满足 $num\le 7$。

因此，我们考虑直接枚举每一种方案。

我们将其分成两类。

$1$ 含有 $1$ 的：

这一类比较好处理，我们可以使用手算出只有一下 $3$ 种情况：

 ``1 2 6`` 和 ``1 3 6`` 和 ``1 2 4``。

$2$ 不含有 $1$ 的：

这一类更好处理，我们假设这种情况的三个数是 $a,b,c$，但是由于 $a\ne1$，$$，$c\ne1$，所以 $c_{min}=a\times 4\ge 2\times4=8$。

但是，题目告诉我们 $c\le 7$，矛盾。所以不存在这样的不含有 $1$ 的组合。

所以，我们只需要处理这三个数列就可以了。

我们发现这个数列如果含有 $5$ 和 $7$，那么这个数列一定不能构成，毕竟这三种情况都没有 $5$ 和 $7$。

所以，我们开一个桶，统计一下每个数字的个数即可。

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
int n,x,y,z;
int num[N],tot[10];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&num[i]);
		if(num[i]==5||num[i]==7){
			printf("-1");
			return 0;
		}
		tot[num[i]]++;
	}
	if(tot[1]!=(tot[4]+tot[6])){
		printf("-1");
		return 0;
	}
	if(tot[2]+tot[3]!=tot[1]){
		printf("-1");
		return 0;
	}
	if(tot[2]<tot[4]||tot[6]<tot[3]){
		printf("-1");
		return 0;
	}
	for(int i=1;i<=tot[4];i++){
		printf("1 2 4\n"); 
	}
	for(int i=1;i<=tot[3];i++){
		printf("1 3 6\n");
	}
	for(int i=1;i<=tot[2]-tot[4];i++){
		printf("1 2 6\n");
	}
	return 0;
}
```


---

## 作者：ruruo (赞：1)

因为所有数均 $\leq 7$，而 $\leq 7$ 的合数只有 $4$ 和 $6$，因此所有满足题目要求的三元组只有：

1. `1 2 4` 

2. `1 3 6` 

3. `1 2 6`

因此就不难得到以下的分类讨论：

1. 首先，若出现 $5, 7$ 直接无解，因为三个三元组中的任意一个都不含有 $5, 7$。

2. 其次，如果 $3$ 的个数小于 $1, 6$ 中任意一个的个数，无解。因为 $3$ 只能放在 `1 3 6` 这个三元组中。

3. 再次，如果 $2$ 的个数小于剩下的 $1, 6$ 中任意一个的个数，无解。因为 $2$ 只能放在 `1 2 6` 这个三元组中。

4. 最后，如果 $4$ 的个数不等于剩下的 $1, 2$ 中任意一个的个数，无解。因为 $4$ 只能放在 `1 2 4` 这个三元组中。

最后得到三个三元组的个数，输出即可。

```cpp
#include<bits/stdc++.h>
#define end {cout << "-1\n"; return 0;}
using namespace std;

int n;
int cnt[10];
int cnt1, cnt2, cnt3;

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    if(cnt[5] || cnt[7]) end
    if(cnt[6] < cnt[3] || cnt[1] < cnt[3]) end
    cnt1 = cnt[3], cnt[6] -= cnt[3], cnt[1] -= cnt[3];
    if(cnt[2] < cnt[6] || cnt[1] < cnt[6]) end
    cnt2 = cnt[6], cnt[2] -= cnt[6], cnt[1] -= cnt[6];
    if(cnt[1] != cnt[2] || cnt[2] != cnt[4]) end
    cnt3 = cnt[1];
    for(int i = 1; i <= cnt1; i++) cout << "1 3 6\n";
    for(int i = 1; i <= cnt2; i++) cout << "1 2 6\n";
    for(int i = 1; i <= cnt3; i++) cout << "1 2 4\n";
    return 0;
}
```


---

## 作者：BADFIVE (赞：1)

**题意**: 在 $n$ 个 $\le 7$ 的正整数中选取 $\frac{n}{3}$ 个数对，满足 $a < b < c$ 且 $a$ 整除 $b$ ，$b$ 整除 $c$ 。输出方案，如果无解，输出 $-1$ 。   
**思路**: 这题是一个数学规律的题，因为 $\frac{n}{3}$ 个数对的范围都是 $\le 7$ 的，且满足 $a$ , $b$ , $c$ 能够相互整除的情况，所以经推导只有 $3$ 种情况:   
$\cdot$ $1$ $2$ $4$   
$\cdot$ $1$ $2$ $6$   
$\cdot$ $1$ $3$ $6$   
确定每一组的数量，只有第三组有 $3$ ，所以第三组的数量就确定了，
然后再看剩下的两组，只有第一组有 $4$ ，那么第一组也就确定，然后剩下的就是第二组，当然第二组只有 $6$ ，看相不相等而且必需要 $\ge0$ 才行
```
#include<bits/stdc++.h>
using namespace std;
int dp[1001],Map[1001];
int main() {
	int n,x;
	cin>>n;
	memset(dp,0,sizeof(dp));
	memset(Map,0,sizeof(Map));
	for(int i=0; i<n; i++) {
		cin>>x;
		dp[x]++;
	}
	for(int j=1; j<=6; j++)
		Map[j]=dp[j];
	dp[1]=dp[1]-dp[3];
	dp[1]=dp[1]-dp[4];
	dp[2]=dp[2]-dp[4];
	dp[6]=dp[6]-dp[3];
	if(dp[1]>=0&&dp[2]>=0&&dp[6]>=0&&dp[1]==dp[2]&&dp[1]==dp[6]&&(n==(Map[1]+Map[2]+Map[3]+Map[4]+Map[6]))) {
		for(int i=1; i<=dp[4]; i++) {
			printf("1 2 4\n");
		}
		for(int i=1; i<=dp[6]; i++)
			printf("1 2 6\n");
		for(int i=1; i<=dp[3]; i++)
			printf("1 3 6\n");
	} else {
		printf("-1\n");
	}
}
```

---

## 作者：离散小波变换° (赞：0)

## 题目大意

$n(n<10^5)$ 个正整数，要求选出 $\frac{n}{3}$ 对数对 $(a,b,c)$，使得每对数对满足 $a<b<c,a|b,b|c$。无解输出 $-1$。

保证每个数字不超过 $7$，且 $n$ 是 $3$ 的倍数。

## 题解

观察到每个数字不大于 $7$，因此我们可以进行一系列简单的分类讨论。

- 首先，一旦出现 $5,7$ 就无解。

很显然，$5,7$ 前面只能放 $1$。而 $1$ 只能放在第一个。又由于没有不超过 $7$ 的数字能够被 $5,7$ 整除，因此无解。

目前还剩下 $\{1,2,3,4,6\}$，继续讨论。

- $3$ 只能放在第二位。

这个结论很容易通过枚举得出来。显然，如果 $3$ 放在第一位，那么第二位就要放 $6$，第三位无数字可放；如果 $3$ 放在最后一位，那么它的前面只能放 $1$，而 $1$ 的前面就不能放任何数字了。

还剩下 $\{1,2,4,6\}$ 需要讨论。

- 去掉 $3$ 之后，$6$ 只能组成 $(1,2,6)$。

非常显然的结论。因此我们可以直接将所有的 $6$ 组成这种格式。

此时我们能够发现，剩下的数字 $\{1,2,4\}$ 只能组成一种组合，因此直接全部输出就行了。

## 参考代码

```
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
#define no puts("-1"),exit(0)
int n,cnt[8],_136,_126,_124;
int main(){
    n=qread();
    up(1,n,i) ++cnt[qread()];
    if(cnt[5]||cnt[7]) no;
    if(cnt[6]<cnt[3]||cnt[1]<cnt[3]) no;
    _136+=cnt[3],cnt[6]-=_136,cnt[1]-=_136;
    if(cnt[2]<cnt[6]||cnt[1]<cnt[6]) no;
    _126+=cnt[6],cnt[2]-=_126,cnt[1]-=_126;
    if(cnt[1]!=cnt[2]||cnt[2]!=cnt[4]) no;
    _124+=cnt[1];
    up(1,_136,i) puts("1 3 6");
    up(1,_126,i) puts("1 2 6");
    up(1,_124,i) puts("1 2 4");
    return 0;
}

---

## 作者：WinterRain208 (赞：0)

CF342A 【Xenia and Divisors】

### 题意

给你$n$个数字，分成$n/3$个三元组（$n$保证为$3$的倍数），每组形为($a,b,c$)，要求$a$整除$b$，$b$整除$c$。输出方案，顺序不限。如果无解，输出$-1$。

$n$小于$1e5$，所有数字不大于$7$。

### $SOLUTION$

首先我们开一个大小为$10$的桶来存储数字。

我们一个数字一个数字来分析。

$1$：不能 被任何数整除，可以整除任何数，显然只能放在三元组$a$的位置才行。

$2$:只能被一整除，可以整除$4,6$，只能放在第二位，因为放在第三位前面两个位子只能放一。放在第一位不管第二位放$4$还是$6$第三位都放不了。

$3$:只能被一整除，可以整除$6$，只能放在第二位。原因的话可以用上面的思路分析。

$4$:可以被$1,2$整除，不能整除其他数，只可以放在第三位。

$5$：只可以被$1$整除，不能整除其他数，是个素数，无法放入三元组。

$6$:可以被$1,2,3$整除，不能整除其他数，放在第三位。

$7$:也不能放入三元组。

那么：

| 第一位 | $1$ |
| -----------: | -----------: |
| 第二位 | $2,3$ |
| 第三位 | $4,6$ |

根据乘法原理，我们组成的三元组只可能是$(1,2,4)$或$(1,2,6)$或$(1,3,4)$或$(1,3,6)$。其中$(1,3,4)$不符题意，舍去。

那问题就变成了求如何把所有数分为上述三元组的了。

首先输入中如果含$5,7$，那肯定无解，然后一边计算，一边判断即可。

### 思路

先凑$(1,3,6)$，因为$3$的数量是固定的，只能在这个三元组里面。

然后$6$的数量也固定了，我们求$(1,2,6)$。

最后来求$(1,2,4)$。

如果第一步里面$3$的数量多于$1$或$6$的数量，无解。有解就把计数器里$1,6$的数量分别减去$3$的数量。

第二步判断$6$的数量，第三步只要看$1,2,6$的数量是否相等即可，同理。

这题就解决了。

### $CODE$

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=1e5+5;

#define ll long long
#define ri register int 

int cnt[10],n,x,a,b,c;

void init(){
	memset(cnt,0,sizeof(cnt));
}
void end(){
	puts("-1");
	exit(0);
}
int main(){
	scanf("%d",&n);
	init();
	F(i,1,n){
		scanf("%d",&x);
		++cnt[x];
	}
	if(cnt[5]||cnt[7])end();
	if(cnt[1]<cnt[3]||cnt[6]<cnt[3])end();
	a=cnt[3],cnt[1]-=cnt[3],cnt[6]-=cnt[3];
	if(cnt[1]<cnt[6]||cnt[2]<cnt[6])end();
	b=cnt[6],cnt[1]-=cnt[6],cnt[2]-=cnt[6];
	if(cnt[1]!=cnt[2]||cnt[2]!=cnt[4])end();
	c=cnt[1];
	F(i,1,a)puts("1 3 6");
	F(i,1,b)puts("1 2 6");
	F(i,1,c)puts("1 2 4");
    return 0;
}
```

码风丑陋，望见谅。有错误欢迎指出，谢谢！

$wtrl$。


---

