# [USACO22FEB] Sleeping in Class B

## 题目描述

奶牛 Bessie 最近很高兴能够重返线下课堂！不幸的是，她的老师 Farmer John 讲课非常无聊，因此她经常在课堂上睡着。  
Farmer John 注意到 Bessie 在课堂上没有专心听讲。他让班上的另一位学生 Elsie 记录 Bessie 在每节课上睡着的次数。总共有 $N$ 节课（$1 \leq N \leq 10^5$），Elsie 记录到 Bessie 在第 $i$ 节课上睡着了 $a_i$ 次（$0 \leq a_i \leq 10^6$）。所有课程中 Bessie 睡着的总次数不超过 $10^6$。

Elsie 对 Bessie 感到非常竞争，她希望让 Farmer John 觉得 Bessie 在每节课上睡着的次数是一致的——让问题看起来完全是 Bessie 的错，而与 Farmer John 有时无聊的讲课无关。Elsie 修改记录的唯一方式是将两节相邻的课合并。例如，如果 $a = [1,2,3,4,5]$，那么如果 Elsie 合并第二和第三节课，记录将变为 $[1,5,4,5]$。

请帮助 Elsie 计算她需要对记录进行的最少修改次数，以使记录中的所有数字相等。

## 说明/提示

对于第一个测试用例，Elsie 可以通过 3 次修改将记录改为全为 $3$：
```
   1 2 3 1 1 1
-> 3 3 1 1 1
-> 3 3 2 1
-> 3 3 3
```

对于第二个测试用例，Elsie 可以通过 2 次修改将记录改为全为 $7$：
```
   2 2 3
-> 2 5
-> 7
```

对于最后一个测试用例，Elsie 不需要进行任何操作，因为记录已经由相同的数字组成。

## 样例 #1

### 输入

```
3
6
1 2 3 1 1 1
3
2 2 3
5
0 0 0 0 0```

### 输出

```
3
2
0```

# 题解

## 作者：Zirnc (赞：9)

（参考 [USACO 官方题解](http://www.usaco.org/current/data/sol_prob1_bronze_feb22.html)）

关键点是发现：不论怎么改变数组，**它的元素总和总是不变的**。

通过枚举处理后的数组的长度 $r$，我们可以知道每一段的和 $\frac{\text{sum}(a)}{r}$。判断这个和是不是整数，再检验一下能不能凑出这个和就可以了。

时间复杂度：$O(N \cdot (\#\text{sum}(a)\text{ 因子个数 }))$

```cpp
int a[1000006];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      sum += a[i];
    }
    int ans;
    for (int i = n; i >= 1; i--) { // r
      if (sum % i != 0)
        continue;
      int cur = 0;
      bool flag = 1;
      for (int j = 0; j < n; j++) {
        cur += a[j];
        if (cur > sum / i) {
          flag = 0;
          break;
        } else if (cur == sum / i) {
          cur = 0;
        }
      }
      if (flag) {
        ans = n - i;
        break;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
```

---

## 作者：lnwhl (赞：6)

# P8183 [USACO22FEB] Sleeping in Class B 题解
## 题目大意
一共有 $T$ 组数据，每组数据给定一个长度为 $n$ 的数列。你可以在数列上进行任意次操作，每次操作可以合并相邻的两个数。求最少操作次数使数列的每个数都相等。
## 思路
正向求最小操作次数很难，但我们反向可以穷举合并过后的**数列长度** $k$。

易知无论怎么操作**数列总和** $sum$ 都不变。所以我们可以知道，要想使合并后的每个数都相等，$\frac{sum}{k}$ 一定是一个整数，所以我们只要穷举 $sum$ 的所有质因子就可以了，设 $m$ 为 $sum$ 质因子总数。之后我们可以 $O(n)$ 遍历整个数列，使所有的数都合并成 $\frac{sum}{k}$，判断是否可行就可以了。

总复杂度为 $O(T\cdot n\cdot m)$，足以通过本题。详见代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[100001],sum,sumT;
int main()
{
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        cin>>n;sum=0;
        for(int j=1;j<=n;j++)
        {
            cin>>a[j];sum+=a[j];
        }
        for(int j=n;j>=1;j--)//穷举合并后的数列长度
        {
            if(sum%j==0)
            {
                sumT=sum/j;//每个数的值
                int pre=0;bool ok=1;
                for(int k=1;k<=n;k++)//判断是否可行
                {
                    pre+=a[k];
                    if(pre>sumT){ok=0;break;}
                    else if(pre==sumT)pre=0;
                }
                if(ok==1){cout<<n-j<<endl;break;}
            }
        }
    }
    return 0;
}

```


---

## 作者：江户川コナン (赞：3)

[传送门](https://www.luogu.com.cn/problem/P8183)

简单分析题意：
给你一个数组，你可以将这个数组中的相邻 $k (1 \le k \le n )$ 个数替换为它们的和，设这样为 $1$ 次操作，则进行多少次操作后，数组中所有的数相等。

由此可得：因为只是从几个数变为它们的和，**因此数组中数的总和不变**，即$\sum\limits_{i=1}^ma_i $（$m$ 为当前数组的大小）始终不变；又因为最后数组内所有数相等，以及要求最少的操作次数（即最后的数组大小应该尽量大），所以考虑思路：$i$ 从 $sum$ 循环至 $1$($sum$ 为$\sum\limits_{i=1}^na_i$)，若 $ sum \bmod i = 0$
则使用函数贪心判断可否操作使最后为 $i$ 个 $\frac {sum} i $。若可行，就输出函数返回值（最少操作次数）并结束程序。
那么就可以写出主程序了：
```cpp
int read(){
    memset(a,0,sizeof a);
    cin>>n;
    bool flag=true;
    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(i>=2){
            if(a[i+1]!=a[i]) flag=false;//特判数组本身就相等
        }
        sum+=a[i];//求和
    }
    if(flag){
        cout<<0<<endl;
        return 0;
    }
    for(int i=sum;i>=1;i--){
        if(sum%i==0){
            int x=find(sum/i);
            if(x){//如果当前i可行就直接输出返回
                cout<<x<<endl;
                return 0;
            }
        }
    }
}
int main(){
    cin>>T;
    while(T--){//多组数据
        read();
    }
    return 0;
}
```
接下来就是判断函数部分了：贪心，对于每一个新遍历到的数，将其加起来，若目前若干数和已经 $= \frac{sum} i$，则最优策略就是将这些数加起来(其他方案不会更优),和清零；如果已经 $> \frac{sum}i$，则当前选择的 $i$ 一定是错的，直接返回;如果当前数不是和中第一个数 ,则 $ans \gets ans+1$。最后函数返回 $ans$
```cpp
int find(int k){
    int ans=0,sum=0,flag=true;
    for(int i=1;i<=n;i++){
        if(!flag）//当前不是选中的第一个数
            ans+=1;
        sum+=a[i];
        if(sum==k){//达成，清零
            sum=0;
            flag=true;
            continue;
        }
        if(sum>k){//不可能实现，直接返回false
            return 0;
        }
        flag=false;
    }
    return ans;
}
```
完整AC程序：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n;
const int maxn=1e5+5;
int a[maxn];
int find(int k){
    int ans=0,sum=0,flag=true;
    for(int i=1;i<=n;i++){
        if(!flag）//当前不是选中的第一个数
            ans+=1;
        sum+=a[i];
        if(sum==k){//达成，清零
            sum=0;
            flag=true;
            continue;
        }
        if(sum>k){//不可能实现，直接返回false
            return 0;
        }
        flag=false;
    }
    return ans;
}
int read(){
    memset(a,0,sizeof a);
    cin>>n;
    bool flag=true;
    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(i>=2){
            if(a[i+1]!=a[i]) flag=false;//特判数组本身就相等
        }
        sum+=a[i];//求和
    }
    if(flag){
        cout<<0<<endl;
        return 0;
    }
    for(int i=sum;i>=1;i--){
        if(sum%i==0){
            int x=find(sum/i);
            if(x){//如果当前i可行就直接输出返回
                cout<<x<<endl;
                return 0;
            }
        }
    }
}
int main(){
    cin>>T;
    while(T--){//多组数据
        read();
    }
    return 0;
}
```
完结撒花~

---

## 作者：Dr_Gilbert (赞：3)

# USACO22FEB Sleeping in Class B

【题目大意】给定一个序列 $S$ ，可以进行若干次操作，每次选择序列中任意两个相邻的数合并，合并后的数为原数的和，求至少进行多少次操作可以使得 $S$ 中每个数都相同。

可以考虑一下，合并完成后的序列中每个数的来源。不难发现，合并完成后序列内的每个数都是原序列一段连续区间的和。而合并完成后区间各个数字的值一定是原序列各数字之和的因数。

所以可以从小到大枚举总和的所有约数，对于原序列尝试进行合并，如果尝试成功，则答案就是合并次数。显然，任何一个序列都可以被合并成各数字相同的新序列（合并成一个），所以一定有解。

关于尝试合并的实现，因为合并后序列中每个数都对应着原序列中一段区间的和，所以从序列的第一项开始尝试累加，如果无法累加成正在尝试的因子即为失败。具体的代码实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100010],n;
bool check(int k){//尝试合并
	int tmp=0;
	for (int i=1;i<=n;i++){
		if (tmp<k) tmp+=a[i];//尝试累加
		if (tmp==k){
			tmp=0;
			continue;
		}
		if (tmp>k) return 0;//凑不出，失败
	}
	return 1;//成功
}
int main(){
	int t;
	cin>>t;
	while (t--){
		cin>>n;
		int maxn=-1,sum=0;
		for (int i=1;i<=n;i++){
			cin>>a[i];
			maxn=max(maxn,a[i]);
			sum+=a[i];
		}
		if (sum==0){//注意特判0的情况，否则除以0会出现RE
			cout<<0<<endl;
			continue;
		}
		for (int i=maxn;i<=sum;i++){//从序列中最大值开始枚举
			if (sum%i) continue;//枚举每个约数，不能整除就跳过
			if (check(i)){
				int l=sum/i;//新序列长度
				cout<<n-l<<endl;//合并次数
				break;
			}
		}
	}
	return 0;
}
```

关于时间复杂度：

由求约数个数时采用的“倍数法”可得，$1\cdots N$ 的约数个数之和约为 $N\log N$ 个（参考《算法竞赛进阶指南》），其中每个数的约束个数均摊约为 $\log N$ 个，故时间复杂度约为 $O(n\log n)$。

---

## 作者：oddy (赞：3)

## Description

给定一个长为 $n$ 的序列 $a$，任何时刻都可以合并任意两个相邻的元素，新元素的值等于它们的和。求最少的合并次数使得序列里每个元素都相等。

## Analysis

设最终序列里的每个元素都等于 $k$，则有两个显而易见的结论：

1. 一个 $k$ 合法（就是说，有可能成为答案里的 $k$）的充要条件为 $k \mid \sum a$ 且 $a$ 能够被分成 $\dfrac{n}{k}$ 个块，每个块中数的和都等于 $k$。
2. 对于合法的 $k$，$k$ 越小，合并次数越少。

所以有如下算法：

从小到大枚举 $k$，若合法就算出答案并输出。

答案是多少呢？当合并后的序列里每个数都为 $k$ 时，一共有 $\dfrac{\sum a}{k}$ 个数，所以要合并 $n - \dfrac{\sum a}{k}$ 次。

## Code

```cpp
#include <cstdio>

int t, n, s, f, a[100001];

bool check(int x) {
    if(s % x) return false;            // 除不尽直接去掉
    f = 0;
    for(int i = 1; i <= n; i++) {
        f += a[i];
        if(f > x) return false;        // f > x，说明无论如何这个块一定分不出来
        f %= x;
    }
    return true;
}

int main() {
    for(scanf("%d", &t); t; --t) {
        s = 0;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%d", a+i), s += a[i];
        if(!s) puts("0");
        else for(int i = 1; i <= s; i++) if(check(i)) {
            printf("%d\n", n - s / i);
            break;
        }
    }
    return 0;
}
```

---

## 作者：Jorisy (赞：1)

和 [CF1462D](https://www.luogu.com.cn/problem/CF1462D) 完全一样。

总之就是要合并成几个相同的数，那么这个数必然是 $\sum_{i=1}^{n}a_i$ 的因数。

那么暴力 $O(n\sqrt{sum})$（令 $sum=\sum_{i=1}^na_i$）求 $i$ 和 $\frac{sum}{i}$ 是否可行，可行则取最小值。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,a[100005],sum,ans;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		sum=0;
		ans=1e9;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=a[i];
		}
		if(sum==0)//特判
		{
			cout<<0<<endl;
			continue;
		}
		for(int i=1;i*i<=sum;i++)
		{
			if(sum%i) continue;//不是 sum 的因数
			int x=i,f=1,t=0;
			ll s=0;
			for(int j=1;j<=n;j++)//对于 i 的暴力
			{
				s+=a[j];
				if(s==x)
				{
					t++;
					s=0;
				}
				else if(s>x)
				{
					f=0;
					break;
				}
			}
			if(f) ans=min(ans,n-t);
			x=sum/i;
			f=1;
			t=s=0;
			for(int j=1;j<=n;j++)//对于 sum/i 的暴力
			{
				s+=a[j];
				if(s==x)
				{
					t++;
					s=0;
				}
				else if(s>x)
				{
					f=0;
					break;
				}
			}
			if(f) ans=min(ans,n-t);
		}
		cout<<ans<<endl;
	}
 	return 0;
}
```

---

## 作者：Ginger_he (赞：1)

本文同步更新于[博客园](https://www.cnblogs.com/Gingerhe/p/15966083.html)
# 题目描述
给定序列 $\{a_n\}$，每次操作可以合并相邻的两个数，求使得序列中所有数相等的最小操作次数。
# 题解
设 $\displaystyle\sum_{i=1}^n a_i=s$，因为合并不会影响 $s$，所以我们可以枚举 $s$ 的因数作为最后序列中的数值。  
假设 $x$ 为 $s$ 的某个因数，从左到右进行如下操作：若 $res<x$，则让 $res$ 加上当前数；若 $res=x$，则将 $res$ 清零，即前面枚举的数合并成 $x$；若 $res>x$，则此种情况不可行。  
最后，由于要求最小操作次数，所以我们要让每个数尽量的小，将 $s$ 的因数从小到大枚举，一找到答案 `break` 即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int t,n,s,cnt,a[maxn],p[1005],res,ans;
bool flag;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		flag=ans=cnt=s=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			flag|=(a[i]!=a[1]);
			s+=a[i];
		}
		if(!flag)
		{
			printf("0\n");
			continue;
		}
		for(int i=1;i<=s;i++)
		{
			if(s%i)
				continue;
			p[++cnt]=i;
		}
		for(int i=1;i<=cnt;i++)
		{
			res=ans=0;
			for(int j=1;j<=n;j++)
			{
				res+=a[j];
				ans++;
				if(res==p[i])
				{
					res=0;
					ans--;
				}
				if(res>p[i])
					goto L;
			}
			break;
			L:;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：CANTORSORT (赞：0)

我们可以倒序枚举 **合并后剩下记录数量 $i$**，

对当前情况下进行判断能否 **合并成每组记录均等** 的情况。

由于要均等，

所以，一旦 $i\nmid n$，

**就可以直接跳过(常数优化)**。

则总时间复杂度为 $O(T\times n^2)$，

由于常数有优化，

所以速度实际上更快。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005];
inline void solve()
{
	int sum=0;
	for(int i=1;i<=n;i++)
		sum+=a[i];
	for(int j=n;j;j--) //倒序枚举
	{
		if(!(sum%j))
		{
			int target=sum/j,now=0; //target在这里就是平均数
			bool flag=1;
			for(int i=1;i<=n;i++)
			{
				now+=a[i];
				if(now>target)
				{
					flag=0;
					break;
				}
				if(now==target)
					now=0;
			}
			if(flag) //可以实现
			{
				printf("%d\n",n-j);
				return;
			}
		}
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",a+i);
		solve();
	}
	return 0;
}
```

---

## 作者：3a51_ (赞：0)

### 题目大意

给你一个长度为 $n$ 的序列 $a_1 \cdots a_n$，每次可以合并相邻两数，求最少要多少次操作才可以使得剩余元素都相等。

### 思路

考虑总和。发现无论多少次操作总和都不变。也就是说，最终序列的那个元素一定是总和的约数。先 $O(n)$ 计算总和，然后暴力 $O(n)$ 分解质因数，最后一一枚举质因数，判断即可，判断 $O(n)$，枚举 $O(\log_2n)$，总时间复杂度 $O(T \times n \times \log_2 n)$。

### code

```cpp
/*
work by:Tothetime_tolife
time:1s
space:128MB
*/
#include<bits/stdc++.h>
#define int long long
#define Tothetime_tolife using
#define AK namespace
#define IOI std
Tothetime_tolife AK IOI;
const int Mod1=998244353;
const int Mod2=1000000007;
int gcd(int a,int b){return __gcd(a,b);}
int lcm(int a,int b){return a*b/gcd(a,b);}
int qpow(int a,int b){int res=1;while(b){if(b&1){res=res*a%Mod1;}b>>=1;a=a*a%Mod1;}return res%Mod1;}
template <typename T> inline void read(T& x) {
	x=0;T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=x*f;
	return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg){
	read(x);
	read(arg...);
}
template <typename T>void write(T x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
template <typename T,typename ...Arg>void write(T& x,Arg& ...arg){
	write(x);
	putchar(' ');
	write(arg...);
}
int T,n,sum,a[100005];
int p[1005],cnt=0;
int tmp,ans=0;
int kp=2;
int f(int x){
	int now=0;
	for(int i=1;i<=n;i++){
		now+=a[i];
		if(now>x) return 0;
		if(now==x) now=0;
	}
    if(now!=0) return 0;
	return 1;
}
signed main()
{
	//;;;;;
	read(T);
	while(T--){
		sum=0;
		read(n);
		for(int i=1;i<=n;i++ ){
			read(a[i]);
			sum+=a[i];
		}
		tmp=sum;ans=sum+1;cnt=0;
        if(sum==1){
            cout<<n-1<<endl;
            continue;
        }
        else if(sum==0){
            cout<<0<<endl;
            continue;
        }
        memset(p,0,sizeof(p));
		for(int i=1;i<=tmp;i++){
			if(tmp%i==0){
				p[++cnt]=i;
            }
		}
		for(int i=1;i<=cnt;i++){
			if(f(p[i])) ans=min(ans,p[i]);
		}
		cout<<n-(sum/ans)<<endl;
	}
	
	return 0;
}
//QwQ

```

---

