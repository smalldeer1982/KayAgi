# One and Two

## 题目描述

# One and Two


给你一个数列 $ a_1, a_2, \ldots, a_n $ . 数列中的每一个数的值要么是 $ 1 $ 要么是 $ 2 $ .
找到一个最小的正整数 $ k $，使之满足：
- $ 1 \leq k \leq n-1 $ , and
- $ a_1 \cdot a_2 \cdot \ldots \cdot a_k = a_{k+1} \cdot a_{k+2} \cdot \ldots \cdot a_n $ .

## 说明/提示

就是找一个最小的整数 $k$,使满足 $k$ 及其前面的乘积和其之后的乘积相等。

## 样例 #1

### 输入

```
3
6
2 2 1 2 1 2
3
1 2 1
4
1 1 1 1```

### 输出

```
2
-1
1```

# 题解

## 作者：_wakeup (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1788A)
## 题意
有一个只包含 $1$ 和 $2$，长度为 $n$ 的序列里，找出一个最小的整数 $k$，使得 $a_1\times a_2\times a_3\times......a_k=a_{k+1}\times a_{k+2}\times a_{k+3}\times......\times a_{n}$。也就是找一条分界线，分界线前面的乘积与后面的乘积相等。

如果没有符合的 $k$，则输出 $-1$。
## 解法说明
$n\le 1000$，显而易见，如果全部乘起来，最大可以是 $2^{1000}$，不管用什么数据类型去存，都会爆。但是序列只包含 $1$ 和 $2$，$1$ 对乘积没有影响，所以只看 $2$ 的数量有几个就行，$2$ 的个数相同，就代表乘积相同。用前缀和去存 $2$ 的个数，然后暴力 $k$，便可以轻松通过此题。
## 代码
```
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,a,he[1010];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		int flag=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a;
			if(a==2)he[i]=he[i-1]+1;//前缀和统计个数
			else he[i]=he[i-1];
		}
		for(int i=1;i<=n;i++)
		{
			if(he[i]==he[n]-he[i])//判断个数是否相等
			{
				cout<<i<<endl;
				flag=1;
				break;
			}
		}
		if(flag==0)cout<<"-1"<<endl;
	}
	return 0;
}
```


---

## 作者：ylch (赞：1)

# [CF1788A](https://www.luogu.com.cn/problem/CF1788A) One and Two

## PART1. 题意简述

有一个数列 $a_1,a_2,\cdots,a_{n-1},a_{n}$，其中 $a_i \in \{1,2\}$，要求出一条分割线，位置为 $k$，使得 $a_1 \times a_2 \times \cdots \times a_k \equiv a_{k+1} \times a_{k+2} \times \cdots \times a_{n-1} \times a_{n}$。

## PART2. 解题思路

开始想到的自然是暴力+高精度，然而一个大大的 TLE 摆在了我的眼前。

于是我开始苦思冥想如何优化：

关于乘积，可以得出一个显而易见的结论，$1$ 在乘法算式里是对结果没有影响的，所以可以枚举分割点，统计分割线左边和右边 $2$ 的个数（此处可以使用前缀和优化），如果分割线两边 $2$ 的个数相等，自然就乘积一样了。

以上方法解决了计算的问题，时间复杂度 $\text{O}(n)$。

## PART3. $\text{\color{green}AC}$ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[1005];
int s[1005];

signed main()
{
	int T;
	for (cin >> T; T--; )
	{
		cin >> n;
		for (int i=1; i<=n; i++)
		{
			cin >> a[i];
			s[i] = s[i-1] + (a[i] == 2); //统计前缀和
		}
		bool flag = false;
		for (int i=1; i<=n; i++)	
		{
			if (s[i] == s[n]-s[i]) //如果前i个的2个数 = 后i个2的个数，说明找到了答案
			{
				cout << i << endl;
				flag = true;
				break;
			}
		}
		if (!flag)	cout << -1 << endl; //找不到别忘输出-1
		memset(s, 0, sizeof s); //一定要清空！！！
	}
	return 0;
}
```

## End

管理员大大辛苦啦~

谢谢大家！祝大家 $\text{\color{green}AC}$！

---

## 作者：awaken1802 (赞：1)

### 题意：
有 $t$ 组数据，每组数据有一个数 $n$ 和一个长度为 $n$ 并且只含有 $1$ 和 $2$ 的数列 $a$。要求你找出一个最小的数 $k$，使得 $1 \leq k \leq n$ 并且 $a_1$ 到 $a_k$ 的积等于 $a_{k+1}$ 到 $a_n$ 的积。

如果没有符合题意的 $k$，则输出 $-1$。
### 思路：
因为 $n \leq 1000$，所以直接乘肯定不行。因为数列只含有 $1$ 和 $2$，而 $1$ 对乘积没有影响，所以我们可以想出以下算法：

用一个变量 $ans$ 记录数列中 $2$ 的个数。

若 $ans$ 是奇数，说明数列中 $2$ 的个数无法平均分成两倍。直接输出 $-1$ 即可。

若 $ans = 0$，说明数列只有 $1$，输出 $1$ 即可。

若 $ans$ 是偶数，就设置变量 $jilu$ 记录 $2$ 的个数。当 $jilu$ 是 $ans$ 的一半时，就输出此时第 $jilu$ 个 $2$ 的下标。
### 注意事项：
一定要清空 $ans$ 和 $jilu$！
### 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long t,n,a[1010],ans,jilu;
int main(){
	scanf("%lld",&t);
	for(long long i=1;i<=t;i++){
		scanf("%lld",&n);
		ans=0;
		jilu=0;
		for(long long j=1;j<=n;j++){
		    scanf("%lld",&a[j]);
		    if(a[j]==2)ans++;
		}
		if(ans%2>0)printf("-1\n");
		else if(ans==0)printf("1\n");
		else{
			for(long long j=1;j<=n;j++){
				if(a[j]==2)jilu++;
				if(jilu==ans/2){
				    ans=j;
			            break;
				}
			}
		   printf("%lld\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：Spir1t (赞：1)

## CF1788A One and Two


------------
### 思路：
这题可以说是一眼秒，开个前缀和数组记录 $2$ 的个数，最后判断 $2$ 的个数是否相同，相同的话直接输出下标跳出循环，如果到最后一直没找到就输出 `-1` 即可。

---

## 作者：Paris_Commune (赞：1)

这题是前缀和吧。

$1$ 不影响乘积，因此决定乘积大小的就是 $2$ 的个数。

然后开个前缀和数组，记录前缀的 $2$ 的个数。

然后用前缀和表示出题目要求的乘积式子，再判断即可。

```cpp
#include<cstdio>
#include<cstring>
int a[1005], b[1005];

void solve()
{
	int n;
	scanf("%d",&n);
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=b[i-1]+int(a[i]==2);	
	}
	for(int i=1;i<=(n-1);i++)
	{
		if(b[i]==b[n]-b[i])
		{
			printf("%d\n",i);
			return;
		}
	}
	printf("-1\n");
}

int main()
{
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：mz2022 (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1788A)

题目大意：
--------
给你一个长度为 $n$ 的数列 $a_1,a_2$ $...$ $a_n$ ，其中的数仅为 $1$ 或 $2$，要求一个最小的 $k$ 使得从 $1$ 到 $k$ 所有 $a_i$ 之积等于 $k+1$ 到 $n$ 的所有 $a_i$ 之积。

思路：
--------
首先考虑暴力枚举 $k$，但由于本题最坏情况下乘积将超过 unsigned long long 范围，所以需要开高精度，而开了高精度会 TLE，暴力不行。

然后我们注意到 $a_i$ 的值只会为 $1$ 或 $2$，而 $1$ 的值对结果没有影响，所以只需要先统计所有 $2$ 的个数，然后当枚举到一个 $i$ 使得 $1$ 到 $i$ 中 $2$ 的个数 为所有 $2$ 的个数的一半，即为所求，当然也可以直接使用前缀和去寻找，这里不予说明，想了解的话可以看看其他题解。

注意事项：
--------
详见代码。

Code：
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define cyc(i,l,r) for(int i=l;i<=r;i++) 
int T,n,ok=0,tot_all=0,tot_half=0,a[1005];
void read(int &n){char c,w=1;for(;48>c||c>57;c=getchar())w=c==45?-1:1;for(n=0;47<c&&c<58;c=getchar())n=n*10+(c^48);n*=w;}
void write(int x){if(x<0)putchar(45),x=-x;char c[41],s=0;for(;x;)c[s++]=x%10,x/=10;if(!s)putchar(48);for(;s--;)putchar(c[s]+48);}
void clear(){tot_all=0,tot_half=0,ok=0;}//多组数据记得清空变量。 
void Solve() 
{
	clear();
    read(n);
    cyc(i,1,n) {
		read(a[i]);
		if(a[i]==2)tot_all++;
	}//统计所有2的个数。 
    cyc(i,1,n-1) {//注意题目里说的是1<=K<=n-1。 
        if(a[i]==2)tot_half++;//枚举K，找到最终答案。
        if(tot_half*2==tot_all) {//找到了就输出。 
            cout<<i<<endl;
            ok=1;
            break;
        } 
    }
    if(!ok)cout<<-1<<endl;//没找到输出-1。	
}
int main()
{
    cin>>T;
    while(T--)Solve();
    return 0;//完结撒花。 
}
```

---

## 作者：liangbob (赞：0)

### CF1788A 题解

#### 思路分析

简单前缀和的题。

直接乘会爆。

观察到数组由 $1$ 和 $2$ 组成，而题目要求乘起来。由于 $1$ 不影响乘积的结果，于是乘积结果看 $2$ 的个数即可。

但是直接统计又会爆掉。注意到题面的乘积是连续的，于是可以开个前缀和数组 $sum$，$sum_i$ 记录数组中前 $i$ 个数中含有多少个 $2$。

之后遍历 $2$ 到 $n-1$（第一项和最后一项显然不满足要求）。若 $sum_i = sum_n-sum_i$，输出并退出程序。若全部遍历完程序仍未退出，则代表未找到，输出 $-1$。

#### 关键代码

```cpp
void solve()
{
	int n;
	cin >> n;
	memset(a, 0x0, sizeof(a)); //多测不清空，爆零两行泪
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
		if(a[i] == 2) sum[i] = sum[i - 1] + 1; //如果是二，统计
		else sum[i] = sum[i - 1];
	}
	for(int i = 2;i < n;i++)
	{
		if(sum[i] == sum[n] - sum[i]) //如果符合要求
		{
			cout << i << endl; //输出并退出程序
			return;
		}
	}
	cout << -1 << endl; //找不到，输出 -1
}
```



---

