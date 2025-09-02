# Laboratory Work

## 题目描述

$Anya$ 和 $Kirill$ 正在做一个物理实验，他们必须测量一些值 $n$ 次，然后求出平均值以降低误差。

$Kirill$ 已经完成了测量，得到了 $n$ 个数据：$x_1,x_2,\dots,x_n$。这些值非常接近，其中的最大值与最小值之差不超过 $2$。

$Anya$ 不想去测量，但是他也不能直接抄 $Kirill$ 的数据，因为每次测量的误差是随机的，如果直接抄的话会被老师发现。$Anya$ 想要得到一组数据 $y_1,y_2,\dots,y_n$ ，这组数据满足如下条件：

* $x_1,x_2,\dots,x_n$ 的平均值要等于 $y_1,y_2,\dots,y_n$ 的平均值。
* $\max(y_1,y_2,\dots,y_n) \le \max(x_1,x_2,\dots,x_n)$ 并且 $\min(y_1,y_2,\dots,y_n) \ge \min(x_1,x_2,\dots,x_n)$。
* 两组数据中相等的数尽可能少，即你造的数据中尽量不要出现 $Kirill$ 的数据中出现过的数。

找出这样的一组测量值。

## 说明/提示

$1 \le n \le 100000$。

$-100000 \le x_i \le 100000$

[样例解释]

第一个样例中，$0,0,0,0,0,0$ 与 $-1,1,1,0,0,-1$ 的平均值相等，只有两个相等的 $0$。

第二个样例中，要想使平均值相等，$Anya$ 的测量值只能与 $Kirill$ 的测量值相等。

第三个样例中，最少也要有 $5$ 个相等的数。

translated by [yu__xuan](https://www.luogu.com.cn/user/142110).

## 样例 #1

### 输入

```
6
-1 1 1 0 0 -1
```

### 输出

```
2
0 0 0 0 0 0 
```

## 样例 #2

### 输入

```
3
100 100 101
```

### 输出

```
3
101 100 100 
```

## 样例 #3

### 输入

```
7
-10 -9 -10 -8 -10 -9 -9
```

### 输出

```
5
-10 -10 -9 -9 -9 -9 -9 
```

# 题解

## 作者：开始新的记忆 (赞：3)

题目大意：现在有n个数，其中最大和最小的差不超过2，现在要你找到一串数使得满足以下条件：

1.这串数的和与给出的数之和相等。

2.使得其中相等的数目尽可能少。（例如样例-10 -10 -10 -9 -9 -9 -8,与给出的中-10 -10 -10，-9 -9相等，而另外两个-10就不算相等）

问你最少会有多少数相等，输出这串数。

大致思路：如果最大值最小值的差小于等于1，那么就输出原数列；如果为2，那么有两种操作：1.把两个中间数变为一大一小。2.把一大一小变为两个中间数。所以我们只要判断是做1还是2即可。

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll sum=0,a[100010],ans[100010];
int n;

int main()
{	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		sum+=a[i];
	}
	sort(a+1,a+1+n);
	if(a[n]-a[1]<=1)
	{
		cout<<n<<endl;
		for(int i=1;i<=n;i++)
			cout<<a[i]<<' ';
		cout<<endl;
		return 0;
	}
	int num_min=0,num_max=0,num_mid=0;
	for(int i=1;i<=n;++i)
	{
		if(a[i]==a[1]) 
			num_min++;
		else if(a[i]==a[n])  
			num_max++;
		else 
			num_mid++;
	}
	int t=min(num_min,num_max),k=num_mid/2;
	ll st=a[1];
	if(t>k)
	{
		for(int i=1;i<=t;++i) 
			a[i]=st+1;
		for(int i=n;i>n-t;--i) 
			a[i]=st+1;
		cout<<n-t*2<<endl;
	}		
	else
	{
		for(int i=1;i<=k;++i)
		{
			int ed=num_min+i*2;
			a[ed-1]=st,a[ed]=st+2;
		}
		cout<<n-k*2<<endl;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)
		cout<<a[i]<<' ';
	cout<<endl;
	return 0;
}
```


---

## 作者：hnczy (赞：0)

## 题意
给你一些数，这些数的差不大于二，求平均数相等，且范围不变或减小的序列中，每一个数出现次数与原序列的出现个数取最小值之和最小的序列。

## 解析
因为这一个序列随便交换值都是一样的，那就可以按从小到大的顺序进行赋值，而且因为差值不大于二，那每两个数都有一个临界点，枚举临界点即可，因为平均数相等，说明和相等，那么就可以算出第二个临界点，计算收益即可。时间复杂度 $O(n)$。
## 代码
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000000;
int n,a[1000005];
int cnt[5],l,r,ans=N;
int sum,mx=-1E9,mi=1E9,mid;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		mx=max(a[i],mx);
		mi=min(a[i],mi);
	}
	if(mx-mi==2)mid=mi+mx>>1;
	if(mx-mi!=2){
		cout<<n<<endl;
		for(int i=1;i<=n;i++){
			printf("%d ",a[i]);
		}
		return 0;
	}
	//cout<<mi<<endl;
	for(int i=1;i<=n;i++){
		if(a[i]==mi)cnt[1]++,sum+=1;
		else if(a[i]==mid)cnt[2]++,sum+=2;
		else cnt[3]++,sum+=3;
	}
	//cout<<cnt[1]<<" "<<cnt[2]<<" "<<cnt[3]<<endl;
	for(int i=0;i<=n;i++){
		if(i+(n-i)*2>sum)continue;
		int j=n-(sum-(i+(n-i)*2))+1;
		if(j<=i)break; 
		int res=min(i,cnt[1])+min(j-i-1,cnt[2])+min(n-j+1,cnt[3]);
		if(res<ans)l=i,r=j,ans=res;
	}
	cout<<ans<<endl; 
	for(int i=1;i<=l;i++){
		printf("%lld ",mi);
	}
	for(int i=l+1;i<r;i++){
		printf("%lld ",mid);
	}
	for(int i=r;i<=n;i++){
		printf("%lld ",mx);
	}
	return 0;
}

---

## 作者：wangzikang (赞：0)

观察限制条件。

$\overline{x}=\overline{y}$ 说明改完后的数和相等。

限制 2 说明改的数列 $y$ 中任意元素 $a \in [\min x,\max x]$

发现我们只能进行两种操作：

$\min x,\min x+2 \to \min x+1,\min x+1$

或者

$\min x+1,\min x+1 \to \min x,\min x+2$

于是我们结合限制 3 可以得到一个算法，分别求出全做第一种和第二种的相同个数，取最大的输出方案，方案显然很好构造。

但是我们注意到只有有 $\min x+2 = \max x$ 的时候才能进行操作，所以特判 $\min x+2 \not = \max x$ 一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3],b[1000011];
signed main(){
	cin>>n;
	int M=3214123;
	for(int i=1;i<=n;++i){
		cin>>b[i];
		M=min(b[i],M);
	}
	for(int i=1;i<=n;++i){
		a[b[i]-M]++;
	}
	if(!a[2]){
		cout<<n<<'\n';
		for(int i=1;i<=n;++i){
			cout<<b[i]<<' ';
		}
	}else{
		int x=min(a[0],a[2]);
		if(a[1]<(x<<1)){
			cout<<n-(x<<1)<<'\n';
			a[0]-=x,a[2]-=x,a[1]+=(x<<1);
			for(int i=0;i<=2;++i){
				while(a[i]--)cout<<i+M<<' ';
			}
		}else{
			x=(a[1]>>1);
			a[0]+=x,a[2]+=x; 
			a[1]-=(x<<1);
			cout<<n-(x<<1)<<'\n';
			if(a[1])cout<<M+1<<' ';
			while(a[0]--)cout<<M<<' ';
			while(a[2]--)cout<<2+M<<' ';
		}
	}
	return 0;
}
```


---

## 作者：Forever_LYD (赞：0)

题目对于我这种阅读理解及其垃圾的人还是比较繁杂的，看了好久才看懂题意。其实就是让你找到一个数列，使其满足题目中的那三个条件。

再看那三个条件，最主要的就是数列的平均值要等于原数列的平均值，且数列的最大值最小值要分别大于等于和小于等于原数列的。

直接一个一个去模拟肯定是行不通的。最大值和最小值的差不大于 $2$ 也就是说，当其恰好为 $2$ 时，那该序列的中位数肯定但最大最小值的距离相等，既要保证平均数又得设计最大最小值，还不能有过多重复，那么就只能考虑将这个中位数转换为最大最小值，或者把最大最小值换为中位数。

当这个差值不为 $2$ 时，数列无法再进行又一次变化，所以就要保留原数列不变。

代码也就很好实现了。

---

## 作者：DANIEL_x_ (赞：0)

## 思路：
因为最大值与最小值的差是 $2$，那么原来的数列，就应该只有最大值，最小值和中间的那个值，每个都相差 $1$。

如果最大值减最小值差为 $0$ 或 $1$ 呢就只能选择原数列。

如果差是 $2$，就是判断，把中间数变成一大一小，还是一大一小变成中间数。

## code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[n],najm=200000;
    for (int i=0;i<n;i++)
        cin >> a[i],najm=min(najm,a[i]);
    int povt[3]={0};
    for (int i=0;i<n;i++)
        povt[a[i]-najm]++;
    if (povt[2]==0){
        cout << n << endl;
        for (int i=0;i<n;i++)
            cout << a[i] << " ";
        return 0;
    }
    int razl=(povt[1]/2)*2;
    razl=max(razl,2*min(povt[0],povt[2]));
    cout << n-razl << endl;
    if ((povt[1]/2)*2>=max(razl,2*min(povt[0],povt[2]))){
        for (int i=0;i<povt[0]+(povt[1]/2);i++)
            cout << najm << " ";
        if (povt[1]%2) cout << najm+1 << " ";
        for (int i=0;i<povt[2]+(povt[1]/2);i++)
            cout << najm+2 << " ";
    }
    else {
        for (int i=0;i<povt[0]-min(povt[0],povt[2]);i++)
            cout << najm << " ";
        for (int i=0;i<povt[1]+2*min(povt[0],povt[2]);i++)
            cout << najm+1 << " ";
        for (int i=0;i<povt[2]-min(povt[0],povt[2]);i++)
            cout << najm+2 << " ";
    }

    return 0;
}

    	       		 			    		  	 			
```


---

## 作者：lmy_2011 (赞：0)

### 题目大意:  
给定一个序列，极差超过 $2$，让你构建一个数目相同，平均数相同，极差不超过 $2$，且和原数列相同数字最少的数列。要求构造出的数列中最大值与最小值不能大于或小于原数列中的最大值与最小值。
### 思路：
因为极差为 $2$，那么原数列中就只有 $3$ 种数，最大值、最小值、中间值，且三种数之间都只差 $1$，那么

- 若极差为 $0$，那么原数列就是由相同的数组成的，所以新数列只能选择原数列。

- 若极差为 $1$，同理，只能选择原数列。

- 若极差为 $2$，我们用 $1$、$2$、$3$ 分别来代表数列中的最小值、中间值、最大值，每增加一对 $(2,2)$，就会少一对 $(1,3)$。所以先比较 $(2,2)$ 和 $(1,3)$ 的数目，如果 $(2,2)$ 比 $(1,3)$ 多，那么就把 $(2,2)$ 都变成 $(1,3)$。反过来也一样。

代码（重在理解而不是抄袭）：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
 
using namespace std;
 
#define N 100001
 
int a[N];
 
void read(int &x)
{
    x=0; int f=1; char c=getchar();
    while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
    while(isdigit(c)) { x=x*10+c-'0'; c=getchar(); }
    x*=f;
}
 
int main()
{
    int n;
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    sort(a+1,a+n+1);
    if(a[n]-a[1]<=1) 
    {
        printf("%d\n",n);
        for(int i=1;i<=n;++i) printf("%d ",a[i]);
        return 0;
    }
    int s1=0,s2=0,s3=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==a[1]) s1++;
        else if(a[i]==a[n]) s3++;
        else s2++;
    }
    int t=min(s1,s3),k=s2/2;
    int m=a[1];
    if(t>k)
    {
        for(int i=1;i<=t;++i) a[i]=m+1;
        for(int i=1;i<=t;++i) a[n-i+1]=m+1;        
        printf("%d\n",n-t*2);
        for(int i=1;i<=n;++i) printf("%d ",a[i]);
    }
    else
    {
        for(int i=1;i<=k;++i) a[s1+i*2-1]=m,a[s1+i*2]=m+2;
        printf("%d\n",n-k*2);
        for(int i=1;i<=n;++i) printf("%d ",a[i]);
    }
}
```


---

## 作者：王熙文 (赞：0)

## 题解

首先，最小相同的个数一定为每个数在 $x$ 与 $y$ 出现次数的最小值的总和。

当最大值减去最小值不为 $2$ 时，答案一定为原数组，因为没法变了。

当最大值减去最小值为 $2$ 时，考虑 $y$ 数组是从 $x$ 数组怎么操作得来的。

因为我们需要让最终的数组平均数不变，所以最终 $y$ 得到的平衡一定可以通过每一次“平衡”的操作得来。容易发现“平衡”的操作有两种：

* 将一个最小值和一个最大值变成两个中间值。

* 将两个中间值变成一个最小值和一个最大值。

因为两个操作是相对的，所以最优解只通过一种操作即可得。

因为最终的数组尽量要与之前的数组不同，所以不管哪种操作，都要尽可能使操作次数最多。

设原数组中最小值出现次数为 $\text{cnt1}$，中间值出现次数为 $\text{cnt2}$，最大值出现次数为 $\text{cnt3}$。则

* 如果只执行第一个操作，最小值的出现次数和最大值的出现次数同时减去了 $\min\{\text{cnt1},\text{cnt3}\}$，而中间值的出现次数增加了 $2 \times \min\{\text{cnt1},\text{cnt3}\}$。此时相同的个数为 $|\text{cnt1}-\text{cnt3}| + \text{cnt2}$。

* 如果只执行第二种操作，中间值的出现次数变为 $\text{cnt2} \bmod 2$，最小值和最大值的出现次数分别增加 $\lfloor \dfrac{\text{cnt2}}{2} \rfloor$。此时相同的个数为 $\text{cnt1}+\text{cnt3}+(\text{cnt2} \bmod 2)$。

对于这两个相同的个数取更小的并输出方案即可。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;

int a[100010];

int main()
{
    int in=1e9,ax=-1e9;
    cin>>n;
    for(int i=1; i<=n; ++i)
    {
        cin>>a[i];
        in=min(in,a[i]);
        ax=max(ax,a[i]);
    }
    if(ax-in!=2)
    {
        cout<<n<<'\n';
        for(int i=1; i<=n; ++i) cout<<a[i]<<' ';
        return 0;
    }
    int cnt1=0,cnt2=0,cnt3=0;
    for(int i=1; i<=n; ++i)
    {
        cnt1+=(a[i]==in),cnt2+=(a[i]==in+1),cnt3+=(a[i]==in+2);
    }
    int ans1=cnt1+cnt3+(cnt2&1),ans2=abs(cnt1-cnt3)+cnt2;
    if(ans1<ans2)
    {
        cout<<ans1<<'\n';
        for(int i=1; i<=cnt1+(cnt2>>1); ++i) cout<<in<<' ';
        for(int i=1; i<=(cnt2&1); ++i) cout<<in+1<<' ';
        for(int i=1; i<=cnt3+(cnt2>>1); ++i) cout<<in+2<<' ';
    }
    else
    {
        cout<<ans2<<'\n';
        for(int i=1; i<=cnt1-cnt3; ++i) cout<<in<<' ';
        for(int i=1; i<=cnt2+(min(cnt1,cnt3)<<1); ++i) cout<<in+1<<' ';
        for(int i=1; i<=cnt3-cnt1; ++i) cout<<in+2<<' ';
    }
    return 0;
}
```

---

