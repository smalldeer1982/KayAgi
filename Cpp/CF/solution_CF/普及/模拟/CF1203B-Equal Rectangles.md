# Equal Rectangles

## 题目描述

## 题意简述

你得到了 $4n$ 根木棍。如果这 $4n$ 根木棍可以拼成 $n$ 个面积相同的矩形，请输出 `YES`，否则输出 `NO`。木棍不可以拼接、剪断和不用完。

## 样例 #1

### 输入

```
5
1
1 1 10 10
2
10 5 2 10 1 1 2 5
2
10 5 1 10 5 1 1 1
2
1 1 1 1 1 1 1 1
1
10000 10000 10000 10000
```

### 输出

```
YES
YES
NO
YES
YES
```

# 题解

## 作者：andyli (赞：4)

本题可用贪心解决，首先判断是否相等的边的数量均为奇数，再将$4n$条边进行排序，最后循环将最小边\*最大边进行判断是否都等于一个固定的数字$k$即可。  
代码如下：  
```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 405;

int A[maxn], cnt[10005];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= (n << 2); i++)
            scanf("%d", &A[i]), cnt[A[i]]++; // 统计相同的边数量
        bool flag = true;
        for (int i = 1; i <= 10000 && flag; i++)
            if (cnt[i] & 1)
                flag = false; // 要求均为奇数
        sort(A + 1, A + (n << 2) + 1);
        int k = A[1] * A[n << 2]; // 最小数*最大数
        for (int i = 2, j = (n << 2) - 1; i < j && flag; i++, j--)
            if (A[i] * A[j] != k)
                flag = false; // 必须等于一个相同的数k
        printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}
```

---

## 作者：tzc_wk (赞：2)

### 题意：
给你$4n$个木棒，问是否能用这$4n$个木棒搭成$n$个面积相等的矩形。

### 思路：
我们不难想到，如果能够搭成$n$个面积相等的矩形，必然是最短的木棒和最长的木棒搭配，第二短的木棒和第二长的木棒搭配……。那么思路就有了，将木棒从小到大排序，然后从头到尾扫描一遍，判断一下就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[405],sum;
inline void solve(){
	cin>>n;
	sum=0;
	for(int i=1;i<=(n<<2);i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(sum%2){
		puts("NO");
		return;
	}
	sort(a+1,a+(n<<2)+1);
	bool flag=1;
	for(int i=1;i<=n*4;i+=2){
		if(a[i]!=a[i+1])	flag=0;
		if(a[i]*a[n*4-i]!=a[1]*a[n*4-1])	flag=0;
	}
	if(flag)	puts("YES");
	else		puts("NO");
}
int main(){
	int T;cin>>T;
	while(T--)	solve();
	return 0;
}
```

---

## 作者：Vocaloid_Paranoia (赞：1)


**水题。**

[题目传送门](https://www.luogu.com.cn/problem/CF1203B) 				[我的博客](https://www.luogu.com.cn/blog/705523/solution-cf1203b)

## 题意

你得到了 $4n$ 根木棍。如果这 $4n$ 根木棍可以拼成 $n$ 个面积相同的矩形，请输出 `YES`，否则输出 `NO`。木棍不可以拼接、剪断和不用完。

## 思路
根据题意模拟即可。

输入之后先排序，然后用两个变量 $m,t$ 扫一遍，作为矩形，判断对边和面积是否相等，用 $f$ 记录。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,a[505];
int main() {
	cin>>q;
	while(q--) {
		int n,m=1,t,s,f=0;
		cin>>n;
		while(m<=n*4) {//输入
			cin>>a[m];
			m++;
		}
		sort(a+1,a+n*4+1);//排序
		m=1;//从两头开始扫
		t=n*4-1;
		s=a[1]*a[n*4];//面积
		while(m<t) {
			if (a[m]!=a[m+1]||a[t]!=a[t+1]||a[m]*a[t]!=s) { //如果对边不相等||面积不相等
				cout<<"NO"<<endl;//否
				f=1;
				break;
			}
			m+=2;//下一组
			t-=2;
		}
		if (!f)
			cout<<"YES"<<endl;//是
	}
	return 0;
}
```

## 坑

- $f$ 要初始化。

- $4n$ 根木棍，$n$ 要乘 $4$ 。

------------

[AC记录](https://www.luogu.com.cn/record/119445768)

---

## 作者：きりと (赞：1)

**题目：CF1203B**

题意很好理解，直接讲思路

思路：

因为要组成矩形，由于矩形对边相等，所以，先对所有木棍的长度从小到大排序

```cpp
cin>>n;
for(int i=1;i<=n*4;i++)
{
	cin>>a[i];
}
sort(a+1,a+4*n+1);
```
然后再for一遍，找有没有相邻的两根木棍长度不等，若有，则有一种长度的木棍只有一根

此时显然不能构成矩形，直接输出NO

```cpp
for(int i=1;i<=4*n;i+=2)
{
	if(a[i]!=a[i+1])
	{
		cout<<"NO"<<endl;
		goto flag;
	}
}
```
找完以后，我做了一步可有可无的操作：去重，这样可以方便后面的分析

```cpp
int kkk=0;
for(int i=1;i<=4*n;i+=2)
{
	a[++kkk]=a[i];
}
```
注意，此时，a数组里存的是所有矩形的可能边长

简单分析一下，要使矩形面积都相同，则要找出一种方法使$a[i]$两两成对，每对乘积相等

要使乘积相等，则较小的$a[i]$必须要和大的成对，所以，显然$a[1]$要和$a[kkk]$成对,$a[2]$要和a[kkk-1]成对

那么解法就很明显了，二分或者直接一遍for，找数组a两端元素乘积是否相等

```cpp
int temp=a[1]*a[kkk];
for(int i=2;i<=kkk/2;i++)
{
	if(a[i]*a[kkk+1-i]!=temp)
	{
		cout<<"NO"<<endl;
		goto flag;
	}
}
cout<<"YES"<<endl;
```


---

## 作者：AstaSunch_ (赞：0)

# $\tt{0x00}$ 序

蒟蒻的第 $\bf\color{red}23$ 篇题解。

# $\tt{0x01}$ 明

有 $4n$ 根木棒，能否用它们拼成 $n$ 个面积相等的矩形？

# $\tt{0x02}$ 解

一道贪心题。

我们知道，如果想让这些矩形面积相等，则一定是较小的木棍和较大的木棍匹配，否则最后剩下一些很小的或很大的没法拼出来。

# $\tt{0x03}$ 文

题目这么简单，就不放代码了罢（评黄真是太高了）。

---

## 作者：_colin1112_ (赞：0)

+ 一道简单的贪心+排序做法。

## 思路

首先将这 ${4\times n}$ 个木棍进行排序，然后先计算出最小乘最大的面积，再用一个 while 循环进行依次判断即可。

判断条件为：

1. 由于长方形对边相等，所以需判断对边是否相等。

2. 两边相乘，要与最小乘最大的面积所相等。

如果两个条件相等，那就输出 `YES`，反之则输出 `NO`。

## AC Code：

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E=1e6+5;
ll t;
ll n;
ll arr[E];
ll i,j;
inline void read(ll &x){//快读
	char ch=getchar();ll f=1;x=0;
	while(!isdigit(ch) && ch^'-') ch=getchar();
	if(ch=='-') f=-1,ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	x*=f;
}
inline void write(ll x){//快写，不过代码好像没用上
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9)
		write(x/10);
    putchar(x%10+'0');
}
int main(){
	read(t);
	while(t--){
		read(n);
		for(int i=1;i<=4*n;i++){
			read(arr[i]);
		}
		stable_sort(arr+1,arr+4*n+1);//似乎排序要快些
		ll S=arr[1]*arr[4*n];
		bool flag=true;
		i=1;j=4*n;
		while(i<j){
			if(arr[i]!=arr[i+1] || arr[j]!=arr[j-1] || arr[i]*arr[j]!=S){//判断两个条件是否成立
				cout <<"NO\n";
				flag=false;
				break;
			}
			i+=2;
			j-=2;
		}
		if(flag==true){
			cout <<"YES\n";
		}
	}
    return 0;//完结撒花！
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现把 $4n$ 根木棍的长度排序之后，将第一短的和第一长的组合成一个矩形，将第二短的和第二长的组合成一个矩形，以此类推，符合条件的概率是最大的。模拟即可。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n,a[405];
bool f;
int main(){
	cin>>q;
	while(q--){
		cin>>n;
		f=true;
		for(int i=1;i<=4*n;i++){
			cin>>a[i];
		}
		sort(a+1,a+4*n+1);
		for(int i=1;i<=4*n;i+=2){
			if(a[i]!=a[i+1]||a[i]*a[4*n-i]!=a[1]*a[4*n-1]){
				cout<<"NO"<<endl;
				f=false;
				break;
			}
		}
		if(f){
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：doubleyu (赞：0)

### 前言:
 ```cpp
 inline long long read(){
	long long x=0;
	char c=getchar();
	while(c<'0' || c>'9'){
		c=getchar();
	}
	while(c>='0' && c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
 ```
 这段代码展示的是快读，快读在读入多组数据时比`scanf`和`cin`快.
### 分析:
既然是`4n`所以必为偶数，不用判断棍子少没少的情况。
### 思路:
首先想到排序，排完序后干什么呢？
我举一个例子(排完序后)：
    `1 1 2 2 5 5 10 10`
    不难看出肯定要将木棍进行大小搭配，只有大小搭配才能平均分配面积。
小学学过的。
### 代码实现（此代码为我考场时代码）：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long q,n,a[100000],cc,sum,dd,gg;//gg,cc,dd用来判断
inline long long read(){
	long long x=0;
	char c=getchar();
	while(c<'0' || c>'9'){
		c=getchar();
	}
	while(c>='0' && c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int main(){
	q=read();
	//	cout<<q; 
	while(q--){
		cc=0;
		dd=0; 
		gg=0;
		n=read();
		for(int i=0;i<4*n;i++){
			a[i]=read();
		}
		sort(a,a+n*4);
		sum=a[0]*a[4*n-1];//先算出值，后面用来进行比较，如果不等那么输出NO
//		cout<<endl;
//		for(int i=0;i<n*4;i++){
//			cout<<a[i]<<" ";
//		}
//		cout<<endl;
		if(n==1){//n==1说明木棍只有一种情况，前面已经给木棍排序了，所以只用判断就行
			if(a[0]==a[1]  && a[2]==a[3]){
				cout<<"YES"<<endl;
				gg=1;
			}
		}
		else{
			for(int i=0;i<n*2;i++){//此for循环用来判断木棍是不是成对的
			if(a[i]==a[i+1]){
				i++;				
			}
			else{
				cout<<"NO"<<endl;			
				gg=1;
				cc=1;
				break;
			}
		}		
		}

		if(cc!=1 && gg==0){						
			//cout<<"dasd:"<<sum;
			for(int i=2;i<=4*n/2+1;i++){//因为前面已经算了最小*最大了，而且已经判断过成对了，所以从2开始
				//cout<<a[i]<<"*"<<a[n-i-1]<<endl;
				if(sum!=a[i]*a[4*n-i-1]){//现阶段的最大最小是否等于sum
					cout<<"NO"<<endl;
					dd=1;
					break;
				}
			}
			if(dd!=1){
				cout<<"YES"<<endl;
			}
		}
	}
	return 0;
} 
/*
5
1
1 1 10 10
2
10 5 2 10 1 1 2 5
2
10 5 1 10 5 1 1 1
2 
1 1 1 1 1 1 1 1 
1
10000 10000 10000 10000
*/
```

---

## 作者：_LighT_ (赞：0)

## 题意

不重不漏地使用 $4n$ 根木棍拼成 $n$ 个面积相等的矩形。

## 思路

1. 矩形对边相等，即对应边长的木棍应为 $2$ 的倍数。

2. 将我们求出的第一个矩形的面积 $S$ 作为基准，如果后续矩形的面积不等于 $S$ ，即可判断无解。

3. 木棍长度 $a_i \le 10^4$，不妨开个桶，采用双指针从两侧向内搜。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
const int MAXN=1E4+5;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x;
}
int a[MAXN],n;
void solve(){
	for(ri i=1;i<MAXN;++i)
		a[i]=0;
   //多测不清空，WA两行泪
	n=read()<<2;
	for(ri i=1;i<=n;++i)
		++a[read()];
	int l=1,r=MAXN-1,S;
	while(!a[l]) ++l;
	while(!a[r]) --r;
	S=l*r;
	while(n){
		while(!a[l]) ++l;
		while(!a[r]) --r;
      //双指针遍历
		if(a[l]<2||a[r]<2){
			printf("NO\n");
			return;
		}
		if(l*r!=S){
			printf("NO\n");
			return;
		}
		a[l]-=2;a[r]-=2;
		n-=4;
	}
	printf("YES\n");
	return;
}
int main(){
	int T=read();
	while(T--)
		solve();
	return 0;
}
```

## 小结

时间复杂度：$O(a_i)$.

相较于其他题解本题解适于 $a_i$ 较小而 $n$ 较大的情形。

---

## 作者：AmemiyaHaruka5 (赞：0)

咕了两天后过来写写。。。。。。

其实是小奥题......我自己都不知道为啥卡了十几分钟（还不是因为我蔡

先来一手排序，然后就可以从头到尾判一遍，如果有当对于每个奇数i，若$a_i \neq a_{i +1}$，则无法构成足够数量的矩形，可以直接输no处理其他情况。~~其实貌似不加这段特判也过得去，就是当时敲的时候怕出现一堆无法构成矩形的情况然后T掉~~ ~~然后算了一下发现这么搞常数反而会增大~~

然后就是由矩形计算公式$S=ab$推出两个木棒拼成矩形时，若其面积全部相等，则必为最大的与最小的拼，次大的与次小的拼，以此类推。

然后就过掉了。数据与$a_i$无关，$n$还很小，面积也不会爆`int`，总之就很水（

~~这里吐槽一句这是什么神奇的数据范围啊~~

代码（极长警告）：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while(N--)
    {
        int n;
        cin >> n;
        int arr[401];
        int k = 4 * n;
        for(int i = 1;i <= k;i++)
        {
            cin >> arr[i];
        }
        sort(arr + 1,arr + k + 1);
        bool flaga = true;
        for(int i = 1;i <= k;i += 2)
        {
            if(arr[i] != arr[i + 1])
            {
                flaga = false;
                break;
            }
        }
        if(!flaga)
        {
            cout << "NO" << endl;
            continue;
        }
        int area = arr[1] * arr[k];
        bool flag = true;
        for(int i = 3,j = k - 2;i <= 2 * n;i += 2,j -= 2)
        {
            if(arr[i] * arr[j] != area)
            {
                flag = false;
                break;
            }
        }
        if(flag)
            cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
```

---

## 作者：Luban (赞：0)

因为个人原因未能参加本次CF比赛，赛后补一发题解，同时花15分钟做做T-A、B

这道题的数据比较友好，n,k都不大，完全可以让O(kn log n)的算法通过，所以我们想到了排序

要求面积相等，每种长度的变的数量都得是偶数，并且肯定是最小两边和最大两边配对、次小两边和次大两边配对的（否则肯定不会相等）

排序正好可以很好的解决这个问题，本题难度大概在Noip pj T1-T2的难度左右

上代码吧；

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[505];
int main()
{
	int q;
	cin>>q;
	while(q--)
	{
		int n,i=1,j,ans;
		bool flag=0;
		cin>>n;
		n*=4;
		while(i<=n)
		{
			cin>>a[i];
			i++;
		}
		sort(a+1,a+n+1);
		i=1;
		j=n-1;
		ans=a[1]*a[n];
		while(i<j)
		{
			if (a[i]!=a[i+1]||a[j]!=a[j+1]||a[i]*a[j]!=ans)
			{
				cout<<"NO"<<endl;
				flag=1;
				break;
			}
			i+=2;
			j-=2;
		}
		if (!flag) cout<<"YES"<<endl;
	}
	return 0;
}
```
P.s:个人码风原因，代码过长，各位看官可以进行压行处理，实际代码量很小的，5-10分钟100%能打完

---

## 作者：__HHX__ (赞：0)

# 题目大意
给你 $4n$ 个木棍，能否构造出 $n$ 个**面积相同**的矩形。
# 题目思路
大体思路让**当前可选最大**与**当前可选最小**配对。

因为**当前可选最大**与**当前可选第二小**配对，那**当前可选最小**与**当前可选第二大**配对。

而**当前可选最大**与**当前可选第二小**配对的面积一定大于**当前可选最小**与**当前可选第二大**配对面积。

不然**当前可选最小**与**当前可选第二小**相等，并且**当前可选最大**与**当前可选第二大**相等。

所以让**当前可选最大**与**当前可选最小**配对为最优方案。

还有，**一定要**判断**每个长度**的木棍有**双数个**。
# 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;

const int MaxN=1e4+3;
int a[MaxN];
int main(){
	int q;
	cin>>q;
	while(q--)
	{
		int n;
		bool f=0;
		cin>>n;
		for(int i=1;i<=4*n;i++)
		{
			cin>>a[i];
		}
		sort(a+1,a+n*4+1);//必须排序 
		int area=a[1]*a[4*n];//面积 
		for(int i=1,j=4*n;i<j;i+=2,j-=2)//双向奔赴 
		{
			if(a[i]!=a[i+1]||a[j]!=a[j-1]||a[i]*a[j]!=area)//a[i]!=a[i+1]||a[j]!=a[j-1]特别重要不然就违反了每个长度的木棍有双数个的规则 
			{
				f=1;
			}
		}
		cout<<(f?"NO\n":"YES\n");
	}
}
```

---

