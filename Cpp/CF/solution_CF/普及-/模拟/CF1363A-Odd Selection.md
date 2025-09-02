# Odd Selection

## 题目描述

给出一个 $n$ 项的数列，要求选出 $x$ 个数（不要求连续），使这 $x$ 个数的和为奇数。判断这是否可能。

## 说明/提示

对于第一组数据，我们必须选出 $999$ ，其为奇数。

对于第二组数据，我们必须选出 $1000$ ，其不是奇数。

对于第三组数据，我们可以选择 $51$ ，使得总和为奇数。

对于第四组数据，我们必须选择 $51$ 与 $50$ ，和为 $51+50=101$ 为奇数。

对于第五组数据，我们必须选择全部的三个数，但是总和并不是奇数。

## 样例 #1

### 输入

```
5
1 1
999
1 1
1000
2 1
51 50
2 2
51 50
3 3
101 102 103```

### 输出

```
Yes
No
Yes
Yes
No```

# 题解

## 作者：__shadow__ (赞：5)

【问题分析】

因为要求和是奇数，所以可以想到想到以下定律：

+ $1+0\equiv1(\bmod2)$
+ $1+1\equiv0(\bmod2)$
+ $0+0\equiv0(\bmod2)$

所以不管什么数加上偶数，它的奇偶性都不会改变。

因此我们发现偶数只有凑数量的作用，只有奇数可以对结果的奇偶性产生影响。

同时由上面的规律还可得奇数必须由奇数个奇数和任意个偶数组成，所以我们就先统计出可使用奇数的个数（因为是奇数个奇数，所以如果总共有偶数个的话就要减去 $1$ ）。

之后分成几种情况：
+ 判断有无奇数；
+ 判断需要的数字个数大于可用奇数个数时，偶数够不够补上；
+ 判断需要的数字个数小于可用奇数个数时，是否要奇数个数，或者要偶数个数时有无偶数；

【设计程序】
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<queue>
using namespace std;
int n, x, t, sum;//sum是奇数个数 
int main()
{
	int Q;//Q是数据组数 
	scanf ("%d", &Q);
	while (Q--)
	{
		sum = 0;//奇数个数归零 
		scanf ("%d%d", &n, &x);//n是有几个数  x是要取几个数 
		for (int i = 1;i <= n; i++)
		{
			scanf ("%d", &t);//输入这个数 
			if (t % 2 != 0)//如果是奇数 
				sum++;//sum 加一 
		}
		if (!sum)//如果没有奇数，肯定不行 
		{
			printf ("No\n");
			continue;
		} 
		if (sum % 2 == 0)//如果有偶数个奇数 
		{
			sum--;//奇数个数减一 
			n--;//因为要用（n-sum）算偶数个数，所以n也要减一 
		}
		if (x >= sum && (x - sum) <= (n - sum))
		//如果x比sum大，并且偶数数量足够补空 
		{
			printf ("Yes\n");//输出可行 
			continue;
		}
		if (x < sum)//如果x比sum小 
		{
			if((n - sum) > 0 || x % 2 != 0)
			//当有一个偶数或要奇数个数时 
			{
				printf ("Yes\n");//输出可行 
				continue;
			}
		}
		printf ("No\n");//剩下的情况输出不行 
	}
	return 0;
}
```

有错误欢迎私信指出。

---

## 作者：SpeedStar (赞：4)

### 算法分析
注意到，如果有奇数多个奇数数字的话，那么$x$个数字之和必为奇数。

我们可以首先维护两个变量$odd$和$even$，分别表示数组中奇数的数量和偶数的数量。然后我们可以遍历0到$odd$，每扫过奇数个($i$)奇数时，判断$x-i$是否不超过$even$。

### C++代码
```cpp
#include <iostream>

#define rep(i, n) for (int i = 0; i < n; ++i)

using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n, x;
		cin >> n >> x;
		
		int odd = 0, even = 0;
		rep(i, n) {
			int a;
			cin >> a;
			(a & 1 ? odd : even)++;
		}
		bool ok = false;
		rep(i, odd + 1) {
			if (i & 1 && i <= x && x - i <= even) ok = true;
		}
        cout << (ok ? "Yes" : "No") << '\n';
	}
	
	return 0;
}
```


---

## 作者：KSToki (赞：2)

# 题目大意
给定 $n$ 个数，问是否可以从中选出 $x$ 个数使得这 $x$ 个数的和为奇数。
# 题目分析
显然我们不关心数字的大小，只关心它是奇数还是偶数，所以就将 $n$ 个数中奇数和偶数的数量分别统计起来，如果 $n$ 个数中没有奇数直接输出 No。

这时我们可以先取出一个奇数，将需求量 $x$ 减一。因为两个奇偶性相同的数的和为偶数，那么看现在的 $x$ 是不是奇数，如果是则判断有没有偶数，没有则输出 No，否则取出一个偶数，将需求量 $x$ 减一。

最后，如果当前奇数的数量是奇数，那么将奇数的数量减一，因为那个数肯定没用，判断剩下的奇数数量与偶数数量的和是否大于等于当前的 $x$，如果是则输出 Yes，否则输出 No。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,k,a,b;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&x);
		a=0;
		b=0;//多测不清空，爆零两行泪。话说这样例数据不清空还能过
		for(register int i=1;i<=n;++i)
		{
			scanf("%d",&k);
			if(k&1)
				++a;//统计奇数数量
			else
				++b;//统计偶数数量
		}
		if(a==0)//没有一个奇数
		{
			puts("No");
			continue;
		}
		--a;
		--x;//选定一个奇数
		if(x&1)//当前 x 是奇数
		{
			if(b==0)//没有偶数填空
			{
				puts("No");
				continue;
			}
			--b;
			--x;//选定一个偶数
		}
		a=a/2*2;//如果是奇数则会减一
		if(a+b>=x)//判断，输出
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
```


---

## 作者：_s_z_y_ (赞：1)

## 思路
这道题因为是判断数字为奇数，所以不用考虑数字大小，只需要统计奇数和偶数的个数。

我们发现任意数加上偶数其奇偶性都不会发生改变，只有奇数会改变结果的奇偶性。

所以有以下三种情况需要判断：

- 是否有奇数。
- 是否能凑够 $x-1$ 个偶数和一个奇数。
- 如果偶数不够，是否能够用两个奇数代替两个偶数使数量达到 $x$ 个。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,x,j,o; 
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n>>x;
		j=0,o=0;//将奇数和偶数个数归零
		for(int k=1;k<=n;k++)
		{
			int a;
			cin>>a;
			if(a%2==1)//统计奇偶数个数
				j++;
			else
				o++;
		}
		if(j==0)//没有奇数
		{
			cout<<"No\n";
			continue;
		}
		--j;//使用一个奇数，使结果变为奇数
		--x;
		if(x%2==1)//还需要奇数个数
		{
			if(o==0)//因为偶数个奇数和为偶数，所以至少需要一个偶数
			{
				cout<<"No\n";
				continue;
			}
			--o;
			--x;
		}
		j=j/2*2;//保证最后使用奇数个奇数
		if(j+o>=x)//能凑够 x 个数
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
	return 0;
}

```

---

## 作者：StayAlone (赞：1)

### 题意
给定 $n$ 个数 $a_i$，从中任意取出 $x$ 个数，问能否让这些数的和为奇数。  
$1\leqslant a_i \leqslant 1000, 1\leqslant x \leqslant n \leqslant 1000$。

**有多组数据，$T \leqslant 100$**。  

### 思路

显然有某个数加上一个偶数，其奇偶性不发生变化。所以先统计出奇数的数量 $k$，偶数的数量 $p$。  

- $k = 0$ 时，输出 `NO`。

若 $k > x$，多余的 $k$ 没用，将其抛掉。令现在的 $k = \min(k, x)$。若 $k$ 为偶数，这些数加起来时偶数，则 $k = k - 1$，让 $k$ 成为**最大、合法的所选择的奇数数量**。

接下来就很明显了。

- 若 $k + p\geqslant x$，输出 `Yes`。
- 反之，输出 `No`。  


[AC code 记录](https://www.luogu.com.cn/record/62118728)  
```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i = j; i <= int(n); ++i)
#define rep2(i, j, n) for (int i = j; i >= int(n); --i)
using namespace std;
typedef 
namespace stupid_lrc
{
	template <typename T>
	il void read(T &x)
    
   il int read()
	
	template <typename T>
	il void write(T x)
	
	template <typename T>
	il T my_max(const T &x, const T &y)
	
	template <typename T>
	il T my_min(const T &x, const T &y)
	
	template <typename T>
	il T lowbit(const T &x)
    
	il void restr(string &s)

	il void wrstr(const string &s, const unsigned &len)
	
	il string ItS(int k)
	
	il int StI(const string &s)
}
// 奇妙缺省源
using namespace stupid_lrc;
int T, n, x, a[1010];

int main()
{
	read(T);
	while (T--)
	{
		read(n); read(x); int cnt1 = 0;
		rep1(i, 1, n) read(a[i]), cnt1 += (a[i] & 1);
		int cnt2 = n - cnt1;
		if (!cnt1)
		{
			puts("No");
			continue;
		}
		if (cnt1 > x) cnt1 = x;
		if ((cnt1 & 1) == 0) --cnt1;
		if (cnt1 + cnt2 >= x) puts("yEs");
		else puts("No");
	}
	rout;
}
```

---

## 作者：bovine__kebi (赞：1)

### 算法分析：  
首先我们要了解一个性质，当有奇数个奇数时，我们的数列的和就为奇数。

知道了这个之后就很好想了，就直接暴力枚举判断一下能不能选出奇数个奇数，使得剩下的数是符合偶数个数的，也就是看看剩下的数字的数量在不在偶数数量的范围内就好了，具体看看代码吧：  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;
int main()
{
    int T;//多测
    scanf("%d",&T);
    for(int i=1;i<=T;i++)
    {
        int n,x;
        int a[maxn];//输入的数组，其实没什么必要，但是这么写比较方便
        int odd=0,even=0;//记得初始化，分别为偶数和奇数
        bool flag=0;//给个布尔类型的标记，之后好判断输出答案
        scanf("%d %d",&n,&x);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]&1)even++;//如果是奇数，就让奇数计数器+1
            else odd++;//偶数也一样
        }
        if(even==0){puts("No");continue;}//特判0的情况
        int m=min(even&1?even:even-1,x&1?x:x-1);//从奇数个数和选的数的个数中取最小值，降低运算量，并且直接将他们变成比他小的最大的奇数
        for(int i=m;i>=1;i-=2)//枚举所有的奇数个的奇数，看看可不可行
        {
             if(x-i<=odd){flag=1;break;}
        }
        flag?puts("Yes"):puts("No");//输出
    }
}
```

---

## 作者：lingfunny (赞：1)

## 题目分析 & 代码
首先了解几个东西：
1. 奇数×奇数=奇数
2. 偶数×偶数=偶数
3. 奇数×偶数=偶数

然后要分几个类，代码里写的真的很详细啦！！

```cpp
#include <cstdio>
#include <iostream>

const int maxn = 1005;

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

int T,n,x,cnt1,cnt2;							//cnt1表示奇数的个数，cnt2表示偶数的个数 

int main(){
	T=read();
	while(T--){
		n=read();x=read();cnt1=cnt2=0;
		for(int i=1;i<=n;++i)
		if(read()%2)++cnt1;
		else ++cnt2;
		if(cnt1 == 0){							//如果没有奇数，就不可能凑成
			printf("No\n");
			continue;
		}
		x--;cnt1--;								//用x个数凑出奇数，可以拆分为用x-1个数凑出一个偶数，最后在加上一个奇数 
		if(x<=cnt2){							//如果偶数足够多，剩下x-1个数都可以用偶数凑 
			printf("Yes\n");
			continue;
		}
		if(x%2){								//如果x-1是奇数 
			if(cnt2 == 0){						//如果没有偶数，那么就是要用奇数个奇数凑出偶数，显然不可能 
				printf("No\n");
				continue;
			}
			--cnt2;--x;							//如果有偶数，这个用 x-1（奇数）个数凑出偶数就可以化成用 x-2（偶数）个数凑出偶数 
		}
												//从if出来后，可以确保现在的x是个偶数，现在就是要用x个数凑出偶数 
		x-=cnt1/2*2;							//假设偶数不够，奇数来凑  每两个奇数凑成一个偶数，则可以拿cnt1/2*2个数来凑偶数（这里要下取整） 
		printf("%s\n",x<=cnt2?"Yes":"No"); 
	}
	return 0;
}
```

---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1363A)&[CF 链接](http://codeforces.com/problemset/problem/1363/A)

## 题目简述

共有 $T$ 组数据。

对于每组数据，给定 $n,x$ 和 $n$ 个数，问是否可以从 $n$ 个数中选 $x$ 个使其和为**奇数**，可以输出 `Yes`，否则输出 `No`。

## 思路

首先在输入过程中记录**奇数的个数**，接着**特判没有奇数的情况，直接输出 `No` 即可**。

接着如果奇数有**偶数个**，则把奇数个数减一，因为我们拿着偶数个奇数**没有任何用处**，所以扔掉一个即可。

下面判断 $x$ **是否大于奇数个数**，如果大于且**剩余偶数可补上空缺**，可输出 `Yes`；如果不大于则**判断是否有偶数或 $x$ 为奇数**，满足其中一个即可输出 `Yes`；否则输出 `No`。

下面是**代码**实现：

```cpp
#include<iostream>
using namespace std;

int T, n, x;

int main() {
	cin >> T; // 多组输入
	while(T --) {
		int sum = 0; // 初始化奇数个数
		cin >> n >> x;
		for(int i = 1, tmp; i <= n; i++) {
			cin >> tmp;
			if (tmp & 1) sum++; // 如果是奇数则加 1
		}
		if(!sum) {
			cout << "No\n"; // 没有奇数特判输出 No
			continue; // 直接返回
		} 
		if(!(sum & 1)) sum --, n --; // 奇数个数为偶数处理
		if(x >= sum && (x - sum) <= (n - sum)) { cout << "Yes\n"; continue; } // 情况 1
		if(x < sum) 
			if((n - sum) > 0 || x % 2 != 0) { cout << "Yes\n"; continue; } // 情况 2
		printf ("No\n"); // 情况 3，直接输出 No
	}
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/118606784)

$$\text{The End!}$$

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1363A) & [CF链接](http://codeforces.com/problemset/problem/1363/A)

## 思路分析：

首先了解数学常识：

1. 奇数 $+$ 奇数 $=$ 偶数

2. 奇数 $+$ 偶数 $=$ 奇数

3. 偶数 $+$ 偶数 $=$ 偶数

这是一道数学 $O(1)$  判断题，因为加和的奇偶性不受偶数影响，~~偶数就是来凑数的~~，所以只需要判断奇数即可。另外，因为答案中奇数个数只可能有奇数个，所以当奇数个数是偶数时，要减一，因为多出来的那一个对答案没有贡献。

## 代码：

```cpp
#include<iostream>
using namespace std;
int T,n,x,ji,ou,tmp;
int main(){
	cin>>T;//T组数据
	while(T--){
		bool flag=false;//记录答案
		ji=ou=0;//初始化
		cin>>n>>x;
		for(int i=1;i<=n;i++){
			cin>>tmp;
			//记录奇偶数数量
			if(tmp%2==0){
				ou+=1;
			}else{
				ji+=1;
			}			
		}
		if(ji==0){
			cout<<"No"<<endl;//如果没有奇数，直接No
			continue;
		}
		if(ji%2==0){
			ji-=1;//让奇数个数为奇数
		}
		if(x>=ji&&x-ji<=ou){//其实x-ji<=ou没有用
			flag=true;//如果x大于奇数数量且偶数能补全x个
		}else if(x<ji){
			if(ou||x%2==1){//如果有偶数或x为奇数
				flag=true;
			}
		}
		//输出
		if(flag){
			cout<<"Yes"<<endl;
		}else{
			cout<<"No"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：ytcccf (赞：0)

## CF1363A Odd Selection 题解

### 题意简述

给出一个 $n$ 项的数列，要求从中选出 $x$ 个数（不一定连续），使得这 $x$ 个数的和是奇数，问是否可能。多测。

### 题目分析

题目难度：普及-。

AC code 时间复杂度为 $\Theta(tn)$。

### 解题思路 

小学奥数的东西：

+ 奇数 $\times$ 奇数=奇数
+ 奇数 $\times$ 偶数=偶数
+ 偶数 $\times$ 偶数=偶数
+ 奇数 $+$ 偶数=奇数
+ 奇数 $+$ 奇数=偶数
+ 偶数 $+$ 偶数=偶数

由此可见，偶数不会使原数的奇偶性变化，所以只需在 $x$ 个数中出现奇数个奇数，剩下的补上偶数即可使得和为偶数，具体写在代码注释中了。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);//cin、cout优化，还是十分有用的 
	int t;
	cin>>t; 
	while(t--)//多测 
	{
		int n,x,k,s1=0,s2=0;
		cin>>n>>x;
		for(int i=1;i<=n;i++)
		{
			cin>>k;
			if(k&1) s1++;//记录奇数数量 
			else s2++;//记录偶数数量 
		}
		if(!s1) cout<<"No"<<endl;//全是偶数显然不可能 
		else if((!s2)&&(!(x&1))) cout<<"No"<<endl;//如果没有偶数，x又是偶数，加和必然为偶数 
		else if(s1>=x) cout<<"Yes"<<endl;//其他情况下奇数比x多就成立
		//因为如果x是奇数，显然成立，x为偶数的话就放一个偶数和x-1个奇数 
		else if(s1&1) cout<<"Yes"<<endl;//这种情况下奇数有奇数个，补偶数即可 
		else if(x==n) cout<<"No"<<endl;//如果n个数必须都用上，显然不成立 
		else cout<<"Yes"<<endl;//如果奇数有偶数个，去掉一个即可 
	}
	return 0;//完结撒花~ 
}
```

---

## 作者：Yizhixiaoyun (赞：0)

[本套题所有题解](https://www.luogu.com.cn/blog/yizhixiaoyun/cf1363-ti-xie)

由于笔者水平较弱，所以可能只能一路做到自己做不了的题，不保证能全部写完。

------------

看到题的第一反应是：**不可以的情况非常少**。

再仔细一想，只有几种情况是不可以的：

- 在 $x = n$ 且奇数的个数为偶时。

- 总数为偶数且没有偶数。

- 没有奇数。

其它情况全部都是可以的。

```cpp
#include<bits/stdc++.h>
#define ok puts("YES")
#define no puts("NO")
using namespace std;
int T;
int n,x,y;
int cnt1,cnt2;
inline void init(){
    cin>>n>>x;cnt1=0;cnt2=0;
    for(register int i=1;i<=n;++i){
        cin>>y;
        if(y%2==0) cnt1++;
        else cnt2++;
    }
}
int main(){
    cin>>T;
    while(T--){
        init();
        if(x==n){
            if(cnt2%2==0) no;
            else ok;
        }
        else if(cnt1==0){
            if(x%2==0) no;
            else ok;
        }
        else if(cnt2==0) no;
        else ok;
    }
}
``

---

## 作者：_easy_ (赞：0)

# 思路
在输入时，判断输入的数里面有几个奇数，然后分类讨论就行了。
### 1. 零个奇数
直接输出 $No$。

code:
```cpp
if(!cnt){
	cout<<"No"<<endl;
	continue;
}
```
### 2. 比 $x$ 小个奇数
如果是奇数个奇数或者全部选上，输出 $Yes$，其余情况输出 $No$。

code:
```cpp
if(cnt<x){
	if(cnt&1){
		cout<<"Yes"<<endl;
		continue;
	}
	if(x<n){
		cout<<"Yes"<<endl;
		continue;
	}
	cout<<"No"<<endl;
	continue;
}
```
### 3. 刚好 $x$ 个奇数
如果 $x$ 是奇数或者不用全部选完，输出 $Yes$，其余情况输出 $No$。

code:
```cpp
if(cnt==x){
	if(x&1){
		cout<<"Yes"<<endl;
		continue;
	}
	if(cnt==n){
		cout<<"No"<<endl;
		continue;
	}
	cout<<"Yes"<<endl;
	continue;
}
```
### 4. 比 $x$ 大个奇数
与刚好 $x$ 个奇数判断方法相同。如果 $x$ 是奇数或者不用全部选完，输出 $Yes$，其余情况输出 $No$。

code:
与 $3$ 相同，这里就不给出来了。
# Code
代码已经分段给出。
注：$cnt$ 表示奇数个数。

---

## 作者：grass8cow (赞：0)

要使和是奇数，选取的奇数必有奇数个。

考虑对于每次询问，列举选取的奇数个数，若偶数个数大于等于还需选的个数，则输出 "Yes" ,否则输出 "No" 。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x,a,i,s;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>x;s=0;
		for(i=1;i<=n;i++)
		{
			cin>>a;
			if(a%2==1)s++;
		}
		int flag=0;
		for(int i=1;i<=min(s,x);i+=2)
		{
			if(n-s>=x-i)
			{
				flag=1;
				break;
			}
		}
		if(flag)cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```


---

