# Lucky Year

## 题目描述

除了一年中的许多假期，Berland的居民还有一整个幸运年。如果年份中有不超过1个的非零数字，这一年就被认为是幸运的。所以100,40000,5年是幸运的，12,3001,12345年不是。

你被告知了Berland当前的年份，你的任务就是去找到Berland还要等多久才能迎来下一个幸运年。

## 说明/提示

第一个样例中，下一个幸运年是5。在第二个中 — 300。在第三个中 — 5000。

by @Khassar

## 样例 #1

### 输入

```
4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
201
```

### 输出

```
99
```

## 样例 #3

### 输入

```
4000
```

### 输出

```
1000
```

# 题解

## 作者：豆浆 (赞：5)

##### [题目](https://www.luogu.org/problem/CF808A)

这是一道水题

~~模拟~~就够了



思路:
log10(n)得到的，是n除了最高位外，还有多少位
将这个数字传入pow函数，可得到n的基数，即n的最高位改为1，其他位改为0的数，先记作tp
n/tp*tp,相当于最高位不变，其他位置0，再加上tp，相当于最高位加1

code:

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
int suan(int n){
    int s=1;
    for(int i=1;i<=n-1;i++){
        s*=10;
    }
    return s;
}
int main()	{
    char a[100];
    cin>>a;
    int l=strlen(a);
    if(l==1){
    	cout<<1;
    	return 0;
	}
    int x=atoi(a);
    cout<<suan(l)*(a[0]-47)-x;
    return 0;
}
```
点个赞再走吧✿✿ヽ(°▽°)ノ✿



---

## 作者：MZY666 (赞：4)

评测真慢...百般聊赖的我来发一个简单做法的题解扒。

[原题传送门](https://www.luogu.com.cn/problem/CF808A)。[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-cf808a)。

### 【 题意概括 】

输入某个年份，求下一个幸运年（不包括此年）距离次年还有多少年。

幸运年的定义：年份中只有不超过 $1$ 个非零数字的年份。

没错，就这样。

### 【 思路 】

- 小小的插叙：打字打到这里时再交了一次A了，那 $271$ 个测试点我惊了 ~~出题人真闲~~。

回归正题。

其实我们只需让除 非最高位的数位 均为 $0$ 即可。因为最高位（$0$ 除外，但此题不用考虑 $0$）必须为非零数。

随后让最高位 $+1$ 所得数即为所求年份。

那么我们该如何寻找最高位的位置以及其值呢？

可以先用以下代码实现查询位数：

```cpp
i=1;
while(i<=n)i*=10;
i/=10;
```

这样一来，$i \times j\ (\ j<10\ )$ 的值就会是最高位的值。即 $i \times j=n$ 。

那么，当 $(i \times j)>n$ 时，其值就是所求年份了。

随后通过以下代码寻找 $j$ 的值：

```cpp
for(j=1;j<10;j++)if(i*j>n)break;
```

于是 $i \times j -n$ 即为所求。

其它细节见代码吧。

### 【 代码实现 + 注释 】

```cpp
#include<bits/stdc++.h>//万能头文件可好 
using namespace std;
#define ll long long//个人习惯
int main(){//主函数 
	ll n,i=1,j;//定义
	scanf("%lld",&n);//输入
	while(i<=n)i*=10;//上文有解释
	i/=10;//上文有解释
	for(j=1;j<=9;j++)if(i*j>n)break;//若大于当前年份即可退出循环
	printf("%lld\n",i*j-n);//输出答案
	return 0;//over~
}
```

由于作者自愿禁言了，如果有建议请私信。否则将**无法**回复您哦！

完结撒花~（疯狂暗示 $-v-$

---

## 作者：Cult_style (赞：4)

这道题的数据比较大，直接用循环枚举的话会超时

因为n最大是1000000000，如果数据就是1000000000的话，要循环9000000000次，能不超时吗？

所以，我们仔细看一下，只有是一位数或者最高位不是零其他位数都是零的情况下，才可能是幸运数字，找到幸运数字也不难，我们发现，除了最高位时就的数字之外，幸运数字就是和它同样位数，除了最高位是比原数最高位数多1，其他位数都是零的数。

而如果它的最高位是九，就是比它多一位数字，最高位数字是1，其他数字都是零的数。

好了，献上代码

```
#include<bits/stdc++.h>
using namespace std;
char s[20];
//一串字符
int a;//我们要找的幸运数字
int main(){
    cin>>s;
    int len=strlen(s);
    int cnt=1;
    int k=0;
    for(int i=len-1;i>=0;i--){
	k+=cnt*(s[i]-'0');
	cnt*=10;
    }
    //以上是把n变成整数,为了好取n的最高位，所以不一开始就是整数了
    if(s[0]=='9'){
	int x=1;
	for(int i=0;i<len;i++)
           	x*=10;		
	printf("%d",x-k);
	return 0;
    }
    //九得特判
    a=s[0]-'0'+1;
    //先取最高位
    for(int i=0;i<len-1;i++)
	a*=10;
    //找到幸运数字
    printf("%d",a-k);
    //输出
    return 0;
}
```
#### ~~求过求赞~~


---

## 作者：YYen (赞：1)

### 思路：
假设正整数 $ n $ 的位数为 $ m $，最高位数字为 $ k $，那么 $ n $ 的下一个幸运年必定是 $ (k + 1) \times 10^{m - 1} $。这个道理应该很容易理解，可以代入一些具体数据来验证一下。
### 代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring> 
using namespace std;

int digitcnt(int num)
{
    int cnt = 0;
    while (num >= 10)
    {
        num /= 10;
        cnt++;
    }
    num++;
    for (int i = 1; i <= cnt; i++) num *= 10;
    return num;
}

int main()
{
    int num;
    cin >> num;
    cout << digitcnt(num) - num << endl;
    return 0;
}
```


---

## 作者：锦瑟，华年 (赞：1)

这题很简单啊，为什么通过率那么低？？？

好了，这题主要思路是暴力模拟，共两种思路。

1.暴力模拟，定义变量$ans$为计数器，每次循环$n$加一，计数器$ans$也加一，对每次加得的$n$进行判断，如果符合条件，输出计数器$ans$。好了，上代码：

	#include<stdio.h>
	using namespace std;
	int check(int k){
		int sum=0;
		while(k){
			if(k%10)sum++;
			if(sum>1)return 0;
			k/=10;
		}
		return 1;
	}
	int main(){
		int n,ans=1;
		scanf("%d",&n);
		n++;
		while(check(n)==0){
			ans++;n++;
		}
		printf("%d",ans);
		return 0;
	}
    
如果这样做的话，会TLE，[评测记录](https://www.luogu.com.cn/record/31615981)，那么我们怎么优化呢，我们接下来就讲讲优化。

我们可以发现，其实这题就是求整十（或整个，整百，整千……按位数而定）数，只需把第一个数加一，第二个数至最后一个数变成零，把这样求得的数减去原数即是答案。不过，为了保险起见，最好开long long，不然会爆int。好了，上代码：

	#include<stdio.h>
	using namespace std;
	int main(){
		long long n,n1,ans=1,h;//十年OI一场空，不开long long见祖宗。
		scanf("%lld",&n);
		n1=n;
		while(n1){//求数
			h=n1%10;
			n1/=10;
			ans*=10;
		}
		ans/=10;
		ans*=(h+1);//求数
		printf("%lld",ans-n);//输出答案
		return 0;
	}
    
好了，题解结束，最后我想说一句，为什么这题有271个测试点？？？CF是不是疯了？？？好了，拜拜~~(^_^)

---

## 作者：int32 (赞：0)

## $\text{Solution}$

设下一个 Lucky Year 的年份为 $y$。

由于只能有一个非零数位，所以 $y=a\times10^k\ (1\leq a\leq10,1\leq k\leq9)$。

我们发现，$a$ 一定比 $n$ 的首位数字大 $1$。所以考虑拆解出 $n$ 最高位，计算出 $a$。

其次我们发现，$k=\log_{10}n$，可据此计算。

答案即为 $y-n$。

## $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int calc(int n){//计算 n 的位数
	int res=0;
	while(n){
		++res;
		n/=10;
	}
	return res;
}
signed main(){
	cin>>n;
	int p=calc(n);//n 位数
	int q=n/(int)(pow(10,p-1))+1;//n 最高位
	int r=q*pow(10,p-1);//Lucky Year
	cout<<r-n;//答案
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
年份中有不超过 $1$ 个非 $0$ 数字的年份是幸运年份。现给出当前年份 $n$，求到下一个幸运年份还要等多久。

**数据范围：$1\leqslant n\leqslant 10^9$。**
## Solution
分类讨论，只需要 $\texttt{if}$ 即可：

- $1\leqslant n\leqslant 9$，此时只需要再等一年。
- $10\leqslant n\leqslant 99$，那我们就肯定只有 $n\equiv 0\pmod {10}$ 的年份才是幸运年份。所以，如果 $10\mid n$，那么还要再等十年，否则还要再等 $(10-n\mod{10})$ 年。
- $100\leqslant n\leqslant 999$，那我们就肯定只有 $n\equiv 0\pmod {100}$ 的年份才是幸运年份。所以，如果 $100\mid n$，那么还要再等 $100$ 年，否则还要再等 $(100-n\mod{100})$ 年。
- $1000\leqslant n\leqslant 9999$，那我们就肯定只有 $n\equiv 0\pmod {1000}$ 的年份才是幸运年份。所以，如果 $1000\mid n$，那么还要再等 $1000$ 年，否则还要再等 $(1000-n\mod{1000})$ 年。
- $10000\leqslant n\leqslant 99999$，那我们就肯定只有 $n\equiv 0\pmod {10000}$ 的年份才是幸运年份。所以，如果 $10000\mid n$，那么还要再等 $10000$ 年，否则还要再等 $(10000-n\mod{10000})$ 年。
- $100000\leqslant n\leqslant 999999$，那我们就肯定只有 $n\equiv 0\pmod {100000}$ 的年份才是幸运年份。所以，如果 $100000\mid n$，那么还要再等 $100000$ 年，否则还要再等 $(100000-n\mod{100000})$ 年。
- $1000000\leqslant n\leqslant 9999999$，那我们就肯定只有 $n\equiv 0\pmod {1000000}$ 的年份才是幸运年份。所以，如果 $1000000\mid n$，那么还要再等 $1000000$ 年，否则还要再等 $(1000000-n\mod{1000000})$ 年。
- $10000000\leqslant n\leqslant 99999999$，那我们就肯定只有 $n\equiv 0\pmod {10000000}$ 的年份才是幸运年份。所以，如果 $10000000\mid n$，那么还要再等 $10000000$ 年，否则还要再等 $(10000000-n\mod{10000000})$ 年。
- $100000000\leqslant n\leqslant 999999999$，那我们就肯定只有 $n\equiv 0\pmod {100000000}$ 的年份才是幸运年份。所以，如果 $100000000\mid n$，那么还要再等 $100000000$ 年，否则还要再等 $(100000000-n\mod{100000000})$ 年。
- $n=1000000000$，则还需要再等 $1000000000$ 年。

讨论完毕。
## Code
```cpp
int n;

int main() {
	scanf("%d", &n);
	if(n >= 1 && n <= 9)	printf("1");
	else if(n >= 10 && n <= 99) printf("%d", !(n % 10) ? 10 : 10 - n % 10);
	else if(n >= 100 && n <= 999)	printf("%d", !(n % 100) ? 100: 100 - n % 100);
	else if(n >= 1000 && n <= 9999)	printf("%d", !(n % 1000) ? 1000 : 1000 - n % 1000);
	else if(n >= 10000 && n <= 99999)	printf("%d", !(n % 10000) ? 10000: 10000 - n % 10000);
	else if(n >= 100000 && n <= 999999)	printf("%d", !(n % 100000) ? 100000 : 100000 - n % 100000);
	else if(n >= 1000000 && n <= 9999999)	printf("%d", !(n % 1000000) ? 1000000: 1000000 - n % 1000000);
	else if(n >= 10000000 && n <= 99999999)	printf("%d", !(n % 10000000) ? 10000000 : 10000000 - n % 10000000);
	else if(n >= 100000000 && n <= 999999999)	printf("%d", !(n % 100000000) ? 100000000 : 100000000 - n % 100000000);
	else	printf("1000000000");
	return 0;
}
```

---

## 作者：LucasXu80 (赞：0)

我相信不少人和我一样，一上来直接枚举，结果[可想而知](https://www.luogu.com.cn/record/33953387)。

那么，有什么方法能降低时间复杂度呢？

介绍一种$O(1)$的做法（本人时间复杂度没学好，不清楚这个是不是$O(1)$，如果错了大佬勿喷QAQ）

嗯，可能你们已经猜到了：

## 打表

~~（假装我不慌）~~

首先是打表程序，这个表不难打，把$1$~$9$后面加一堆$0$就OK了。

来看看代码~

```cpp
#include <iostream>
using namespace std;
int main()
{
    cout<<"0,"; //数组的第0项，个人习惯吧
    for (int i=0; i<=9; i++) //后面0的个数 
    {
        for (int j=1; j<=9; j++) //第一位数 
        {
            cout<<j; //先输出第一位数 
            for (int k=1; k<=i; k++) //输出i个0 
            {
                cout<<0;
            }
            cout<<","; //输出逗号方便直接复制 
        }
    }
    return 0;
}
```
当然这里保险起见我多打了几个数，导致超过了整形范围，需要开long long。

接下来看看解题程序，思路很简单了。

遍历数组中的每一项，如果比目标数$n$**大**（严格大于，否则如果原数就符合要求会有问题）就退出循环，并输出两数之差。

注意，不需要特判，因为前面已经严格大于，不会再出现问题了。

上完整代码了~

```cpp
#include <iostream>
using namespace std;
long long a[]={/*省略，防抄袭+太长了*/};
int main()
{
    int n,num; //num记录下一个满足要求的数的数组下标
    cin>>n;
    for (int i=1; i<=100; i++) //100为了保险才开那么大的
    {
        if (a[i]>n) //严格大于目标数
        {
            num=i; //记录下标
            break; //退出循环
        }
    }
    cout<<a[num]-n; //输出两数之差即可
    return 0;
}
```
嗯，271个点，史上最多。。。

这份题解就到此为止了，希望大家喜欢，求赞！

---

## 作者：WsW_ (赞：0)

### 更新
这是一篇已通过的题解。  

- $2024.12.25$ 更新旧题解。

---
### 思路
因为除了 $1$ 个数位上可以不是 $0$，其他都得是 $0$，所以一定是最高位上是非零数字，其他数位上都得是 $0$。  
而且还要最小，所以下一个幸运年的最高位比现在的年份最高位大 $1$。 

知道下一个幸运年是多少后，减去目前是第几年即可得出答案。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ws(int &x){
	int sum=0;
	if(x==0)return 1;
	while(x>=10){
		x/=10;
		sum++;
	}
	return sum+1;
}
int poww(int y){
	int x=1;
	while(--y)x*=10;
	return x;
}
int main(){
	scanf("%d",&n);
	int x=n,l=ws(x);
	printf("%d",(x+1)*poww(l)-n);
	return 0;
}
```

---

