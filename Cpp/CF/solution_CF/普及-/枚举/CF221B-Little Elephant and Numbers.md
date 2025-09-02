# Little Elephant and Numbers

## 题目描述

The Little Elephant loves numbers.

He has a positive integer $ x $ . The Little Elephant wants to find the number of positive integers $ d $ , such that $ d $ is the divisor of $ x $ , and $ x $ and $ d $ have at least one common (the same) digit in their decimal representations.

Help the Little Elephant to find the described number.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10
```

### 输出

```
2
```

# 题解

## 作者：bigclever (赞：3)

### 思路：
按题意模拟即可。先枚举 $x$ 的所有因数，再判断该因数是否与 $x$ 含有共同数字。如果有，则方案数加一。

注意：如果从 $1$ 到 $x$ 逐一判断会超时，所以我们只需要枚举到 $\sqrt x$，并且每一次判断 $x$ 和 $x \div i$ 是否满足条件就可以了。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,bool> a,b;
bool check(int n){
	b.clear();//初始化
	while(n)b[n%10]=true,n/=10;//标记n的每一位数字
	for(int i=0;i<=9;i++)
		if(a[i]&&b[i])return true;//如果这个数字x和n都有，则n是一个符合条件的数
	return false;
}
int main(){
	int x,ans=0,t; 
	cin>>x,t=x;
	while(t)a[t%10]=true,t/=10;//标记x的每一位数字
	for(int i=1;i<=x/i;i++)//枚举x的因数
		if(x%i==0){
            ans+=check(i);
            if(x/i!=i)ans+=check(x/i);//记得判重
        }
	cout<<ans;
	return 0;
}
```

---

## 作者：liupan2010 (赞：2)

前言：

[题目传送门](https://www.luogu.com.cn/problem/solution/CF221B)

一道简单但是码量较大的一道题。

------------

思路：

用 $i$ 从 $1$ 循环至 $\sqrt{x}$，再将 $x$ 与 $i$ 分离数位，再逐个比较。如果有相同的数字就将答案加一。

注意：当 $i$ 为 $\sqrt{x}$ 时，只需要加一次答案！

------------

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,t3,t4,ans;
bool flag;
int t1[10],t2[10];
int main(){
	cin>>x;
	for(int i=1;i*i<=x;i++){
		if(x%i==0){
			int y=x,j=i;
			t3=0,t4=0;
			//分离数位，这里因为是由赋值直接替换数组里的值，就不用 memset 了。 
			while(y){
				t1[t3]=y%10;
				t3++;
				y/=10;
			}
			while(j){
				t2[t4]=j%10;
				t4++;
				j/=10;
			}
			flag=true;
			//注意，这里循环变量只要从 0 循环到 t3-1 或 t4-1！ 
			for(int k=0;k<t3;k++){
				for(int l=0;l<t4;l++){
					//如果相同 
					if(t1[k]==t2[l]){
						ans++;
						flag=false;
						break;
					}
				}
				if(!flag){
					break;
				}
			}
			//注意特判 
			if(i*i!=x){
				y=x,j=x/i;
				t4=0;
				while(j){
					t2[t4]=j%10;
					t4++;
					j/=10;
				}
				flag=true;
				for(int k=0;k<t3;k++){
					for(int l=0;l<t4;l++){
						if(t1[k]==t2[l]){
							ans++;
							flag=false;
							break;
						}
					}
					if(!flag){
						break;
					}
				}
			}
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：zgy_123 (赞：2)

做法其他大佬分析地很详细了，我就来分析一下复杂度。

首先是找因数，这部分复杂度 $O(\sqrt n)$。

然后，对于每个因数，枚举判断是否满足，这里放一下[因数个数定理](https://cn.bing.com/search?q=%E5%9B%A0%E6%95%B0%E4%B8%AA%E6%95%B0%E5%AE%9A%E7%90%86&cvid=3f5506a211cc463abdee2e07224bda91&aqs=edge.0.0j69i57j0l7.10245j0j4&FORM=ANAB01&PC=CNNDDB)，不了解的自行了解。

所以我们得出：$n$ 的因数个数为

$$\prod_{i=1}^{m} ( \alpha _i+1 )$$

因为 $2\times3\times5\times7\times11\times13\times17\times19\times23\times29=223092870$，所以得出 $n$ 最多有 $1024$ 个因数，接近线性。

对于每个因数 $x$，我们花 $O(\log_{10}n+\log_{10}x)$ 的时间来判断，也可以近似为线性，总复杂度约为 $O(1)$。

所以综上，算法复杂度为 $O(\sqrt n)$。

---

## 作者：CCDYJXZ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF221B)。

**题意**：

给出一个数 $x$，求在所有 $x$ 的因数中，有和 $x$ 在十进制表示中一样数字的数的个数。

**思路**：

题意简单明了，但范围过大，一般做法肯定会超时，所以我们得优化一下。枚举 $x$ 的因数时，只需枚举到 $\sqrt{x}$ 就行。因为一个数如果能够整除 $x$，那 $x$ 除以它的商也肯定是 $x$ 的因数。所以当我们枚举时，如果它是 $x$ 的因数，只需判断它和 $x$ 除以它的商是否满足条件即可。**注意**，此方法枚举到 $\sqrt{x}$ 时，可能会**判重**，需要**特判**。



------------

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool aa[10];//保存x十进制中出现过得数。 
int main(){
    int a,s,d1,d2,f,g=0;
	cin>>a;
	f=a;
	while(f){
		aa[f%10]=1;
		f/=10; //找出所有x的十进制中出现过得数。 
	}
	s=sqrt(a);
	for(int i=1;i<=s;i++){
		if(a%i==0){
			if(i==a/i){//特判 
				d1=i;
				while(d1){
					if(aa[d1%10]){
						g++;
						break;
					}
					d1/=10;
				}
			}
			else{
				d1=i;d2=a/i;
				while(d1){//判断此x的因数与它对应的数是否满足条件。 
					if(aa[d1%10]){
						g++;//满足数量加一。 
						break;
					}
					d1/=10;
				}
				while(d2){
					if(aa[d2%10]){
						g++;
						break;
					}
					d2/=10;
				}
			}
		}
	} 
	cout<<g;//输出所有个数。 
    return 0;
}
```
蒟蒻发题解，如有不满请见谅。

---

## 作者：zhuweiqi (赞：1)

模拟题。

在 $1$ 至 $\sqrt{n}$ 之间寻找 $n$ 的因数，如果 $i$ 是 $n$ 的因数，那么 $n\div i$ 一定也是 $n$ 的因数，然后再把 $n$ 和当前需要判断的数的所有包含的数字标记一下，如果存在一个数字并且两个数都有这种数字，答案 $+1$。注意两个点，第一，如果 $i = \sqrt{n}$ 时需要特判，不能重复算！第二，标记数组需要及时清空！上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int f=1,n=0;
	char c;
	c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f; 
}
int a[10],b[10];
int main(){
	int n=read(),ans=0;
	for(int i=1;i<=sqrt(n);i++){
		if(n%i==0){
			int x,y,flag;
			x=n,y=i,flag=0;
			while(x){
				a[x%10]=1;
				x/=10;
			}
			while(y){
				b[y%10]=1;
				y/=10;
			}
			for(int j=0;j<10;j++){
				if(a[j] && b[j]){
					flag=1;
					break;
				}
			}
			if(flag==1) ans++;
			if(i==sqrt(n)) break;
			memset(a,0,sizeof(a));
			memset(b,0,sizeof(b));
			x=n,y=n/i,flag=0;
			while(x){
				a[x%10]=1;
				x/=10;
			}
			while(y){
				b[y%10]=1;
				y/=10;
			}
			for(int j=0;j<10;j++){
				if(a[j] && b[j]){
					flag=1;
					break;
				}
			}
			if(flag==1) ans++;
			memset(a,0,sizeof(a));
			memset(b,0,sizeof(b));
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：221B (赞：1)

~~蒟蒻在想有没有以自己名字命名的题，结果还真找到了~~

咳咳，言归正传。这道题的大意是：给你一个数x，找出满足条件的d的个数，d的条件是：d是x的因数，且d和x至少有一个相同的数字。输出满足条件的d的个数。

这道题蒟蒻提交了八次，总结了一下，TLE是最大的问题。


------------

首先TLE在判断有没有相同数字这里，估计大多数小伙伴是这样写的：
```cpp
int pan(int a){//a是x的因数
    int o[10001];
    int w=0;
    while(a){
        int t=a%10;//每一位判断
        for(int i=1;i<=l;i++)
        if(t==b[i])//b数组里储存的是x的每一位数字，如果有相同的数字就返回1
        return 1;
        a/=10;
    }
    return 0;
}
```
过了八个测试点QwQ。这样判断肯定是会超时的。因为x最大是十位，所以x的每一个因数最多都要判断：这个因数的位数*10 那么多次。

那么怎么样改进呢？我们不妨改成这样：

```cpp
int pan(int a) {
    while(a) {
        int t=a%10;
        if(b[t]==1)//b数组里代表的是x的每一位数字有没有出现过，如果a的某一位数字在b数组里的状态是1，即为有相同数字，返回1.
            return 1;
        a/=10;
    }
    return 0;
}
```
这样就大大缩小了时间复杂度。


------------

还有一个会TLE的地方，在寻找x的因数这里。因为x的最大值是10^9,如果从1到x逐个寻找的话，则要循环10^9次（~~不超时的orz~~）。
如下：
```cpp
for(int i=1;i<=x;i++){
        if(x%i==0)
        if(pan(i)==1)++s;
    }
```
~~完美TLE~~

所以就要有另一种思路辽，我们可以改成这样:
```cpp
for(int i=1; i<=sqrt(x); i++) {//从1找到sqrt(x)
        if(x%i==0) {//如果i是x的因数
            if(pan(i)==1)//如果有相同的数字
                ++s;//计入总数
        }
    }
    for(int i=1; i<sqrt(x); i++) {//相当于从sqrt(x)+1找到x，只是大大缩小了时间复杂度
        if(x%i==0) {
            if(pan(x/i)==1)//判断x/i与x有没有相同数字，和线性筛有相似之点
            ++s;
        }
    }
```
这样就不会超时辣！


------------
只要注意了以上几个问题，AC应该是没有问题的。另赠完整代码：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int b[100001];
int pan(int x) {//判断有没有相同数字，详解见上文
    while(x) {
        int t=x%10;
        if(b[t]==1)
            return 1;
        x/=10;
    }
    return 0;
}
inline int read() {//快读，比cin和scanf都快
    int X=0,w=0;
    char ch=0;
    while(!isdigit(ch)) {
        w|=ch=='-';
        ch=getchar();
    }
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x) {//快写，比cout和printf都快
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int main() {
    int x=read(),s=0;
    int j=x;
    while(j) {//将x的每一位数字储存在数组中
        b[j%10]=1;
        j/=10;
    }
    for(int i=1; i<=sqrt(x); i++) {//查找x的因数，详解见上文
        if(x%i==0) {
            if(pan(i)==1)
                ++s;
        }
    }
    for(int i=1; i<sqrt(x); i++) {
        if(x%i==0) {
            if(pan(x/i)==1)++s;
        }
    }
   write(s);//输出
    return 0;//养成好习惯
}
```


------------

**本蒟蒻还是很蒟的，所以请大家不要在意蒟蒻的这份代码，它不值得你Ctrl+c。**感谢各位dalao赏脸！


---

## 作者：togeth1 (赞：1)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF221B)

### [题意解析]
给你一个整数 $x$，找一个合法的 $d$，而一个合法的 $d$ 则是要满足： 
+ 是 $x$ 的某个因子。
+ 与 $x$ 至少要有 $1$ 个相同的数字。

### [思路分析]
一道模拟题，只要码力过关，写出这题的正解就不难。就按题目说的，再在 $x$ 的范围内找出 $x$ 的因子，判断这个因数与 $x$ 是否有相同的数字就行了。而分解质因数的复杂度是 $O(\sqrt{n})$ 所以模拟不会超时，具体的模拟过程放在代码了。

### [贴上代码]

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,x;
bool f[10010],s[10010];
/*只储存有 或 没有 所以可以开 bool 数组*/
void init(){
	int t=n;
	while(t){
		f[t%10] = 1;
		/*标记出现*/
		t /= 10;	
	}
}
/*初始化，求出一开始 x 出现过的各个数字*/
signed main(){
	cin>>n;
	init();
	for(int i=1; i*i<=n; i++)/*因子是成对出现的，只用枚举一半*/ 
		if(n%i == 0){/*如果可以整除，它就是 x 的一个因子*/
			bool flag = 0;x=i;
			/*初始化*/
			memset(s,0,sizeof(s));
			/*清 0 */
			while(x){
				s[x%10] = 1;
				x /= 10;
			}
			/*求 i 这个因子出现过的各个数字*/
			for(int i=0; i<10; i++)
				if(f[i] ==1 && s[i]==1){
					flag = 1;
					break;
					/*至少 1 个就好*/
				}
			/*找出相同的数字*/
			ans += flag;/*累加答案*/
			/*因为因子是成对出现的，所以我们还要考虑另一半，重复一次上面的操作*/
			memset(s,0,sizeof(s));
			x = n/i;
			flag = 0;
			/*初始化*/
			while(x){
				s[x%10] = 1;
				x /= 10;
			}
			/*求 x/i 这个因子出现过的各个数字*/
			for(int i=0; i<10; i++)
				if(f[i] ==1 && s[i]==1){
					flag = 1;
					break;
				}
			/*找出相同的数字*/
			if(n/i != i)ans += flag;
			/*如果不是平方数，累加答案*/
		}
	cout<<ans;
	return 0;
}
```
这个代码看上去~~又丑又长~~。我们可以把一些重复的部分简化一下。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,x;
bool f[10010],s[10010];
/*只储存有 或 没有 所以可以开 bool 数组*/
void init(){
	int t=n;
	while(t){
		f[t%10] = 1;
		/*标记出现*/
		t /= 10;	
	}
}
/*初始化，求出一开始 x 出现过的各个数字*/
bool check(int x){
	/*初始化*/
	memset(s,0,sizeof(s));
	/*清 0 */
	while(x){
		s[x%10] = 1;
		x /= 10;
	}
	/*求 i 这个因子出现过的各个数字*/
	for(int i=0; i<10; i++)
		if(f[i] ==1 && s[i]==1)
			return 1;
	return 0;
	/*找出相同的数字*/ 
} 
/*写成函数这样会好看一点*/
signed main(){
	cin>>n;
	init();
	for(int i=1; i*i<=n; i++)/*因子是成对出现的，只用枚举一半*/ 
		if(n%i == 0){/*如果可以整除，它就是 x 的一个因子*/
			ans += check(i);/*累加答案*/
			if(n/i != i)ans += check(n/i);
			/*如果不是平方数，累加答案*/
		}
	cout<<ans;
	return 0;
}
```
这样看上去就好看一些了。

---

## 作者：zsh_haha (赞：0)

### 题意理解

这题的翻译不太恰当啊！

我的修改版本：

>小象喜欢数字。
>
>他有一个正整数 $x$，小象想要找到正整数 $d$，使得 $x\bmod d=0$，并且 $x$ 和 $d$ 在十进制中有至少一个相同的数字。
>
>帮助小象找到符合要求的 $d$ 的个数。

### 思路讲解

首先，这题的解法肯定是暴力枚举，但是，要优化！

如何优化？

我先讲一下优化前的算法：从 $1$ 枚举到 $x$ 逐一判断，时间复杂度为 $
\mathcal O(x)$，这种方法**会超时**。

现在来优化，我们设一个数为 $A$，它的一个因子为 $y$。

那么我们得到如下等式：

$A\bmod y=0$

$A\bmod(A/y)=0$

通过上面的等式，我们知道，如果 $y\le\sqrt{x}$，那么 $A/y\ge\sqrt{x}$，所以，我们只要遍历到 $\sqrt{x}$，未遍历到的部分，只需要把 $x$ 除一下得到的数再判断即可。

### 通过代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
bool pd(int num,int d){//判断是否有共有的数字 
	int a[10]={0},b[10]={0};//桶 
	while(d){
		a[d%10]++;
		d/=10;
	}
	while(num){
		b[num%10]++;
		num/=10;
	}
	for(int i=0;i<10;i++){
		if(a[i]&&b[i]){
			return true;
		}
	}
	return false;
}
int main(){
	int d;
	cin>>d;
	int sum=0;
	for(int i=1;i*i<=d;i++){
		if(d%i==0){//判断因子 
			if(pd(i,d)){
				sum++;
			}
			if(i*i!=d&&pd(d/i,d)){
				//注意若 i=d/i，不能加，这样会重合 
				//i=d/i => i*i=d 
				sum++;
			}
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：Moon_Wind (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF221B)

------------

思路简单，码量不小的一道题。

**思路：**

观察题目可以发现，因为因数都是**成对出现**的，所以本题只需要枚举到 $\sqrt{x}$，然后统计枚举到的数中有多少满足条件即可解决问题。


**代码部分：**


------------
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool bj[10];
signed main(){
     ios:sync_with_stdio(0);
     cin.tie(0),cout.tie(0); //输入输出优化
    int a,s,d1,d2,f,g=0;
	cin>>a;
	f=a;
	while(f){
		bj[f%10]=1;
		f/=10; 
	}
	for(int i=1;i*i<=a;i++){//枚举到N的平方根，这里可以优化一下。
		if(a%i==0){//判断是否符合条件
			if(i==a/i){
				d1=i;
				while(d1){
					if(bj[d1%10]){
						g++;
						break;
					}
					d1/=10;
				}
			}
			else{
				d1=i;d2=a/i;
				while(d1){
					if(bj[d1%10]){
						g++;
						break;
					}
					d1/=10;
				}
				while(d2){
					if(bj[d2%10]){
						g++;
						break;
					}
					d2/=10;
				}
			}
		}
	} 
    cout<<g;
    return 0;
}
```


------------


---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，发现我们只需将 $i$ 枚举到 $\sqrt x$，因为因数都是成对出现的，如果 $i$ 是 $x$ 的因数，那么 $x \div i$ 也必定是 $x$ 的因数。接着再按题意判断即可。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,xx,ans;
bool f[10];
int get(int a){
	while(a!=0){
		if(f[a%10]){
			return 1;
		}
		a/=10;
	}
	return 0;
}
int main(){
	cin>>x;
	xx=x;
	while(xx!=0){
		f[xx%10]=true;
		xx/=10;
	}
	for(int i=1;i<=sqrt(x);i++){
		if(x%i==0){
			ans+=get(i);
			if(i*i!=x){
				ans+=get(x/i);
			}
		}
	}
	cout<<ans;
	return 0; 
}
```


---

## 作者：lkjzyd20 (赞：0)

### 思路
按题意模拟即可。

在 $1$ 至 $\sqrt{n}$ 之间寻找 $n$ 的因数，如果 $i
$ 是 $n$ 的因数，那么 $n÷i$ 一定也是 $n$ 的因数，再判断 $i$ 和 $n÷i$ 是否与 $x$ 含有共同数字。如果有，则方案数加一。

注意：如果 $i$ 和 $n÷i$ 是相同的数字，则要去重。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[10], b[10];
int x, ans, t; 
bool check(int n)
{
	memset(b, 0, sizeof b);
	for(; n;) b[n % 10] = 1, n /= 10;
	for(int i = 0; i < 10; ++ i)
		if(a[i] && b[i])
		    return 1;
	return 0;
}
main()
{
	cin >> x;
	t = x;
	for(; t;) b[t % 10] = 1, t /= 10;
	for(int i = 1; i <= x / i; ++ i)
		if(x % i == 0)
		{
            ans += check(i);
            if(x / i != i)
                ans += check(x / i);
        }
	cout << ans;
	return 0;
}

```

---

