# Digits Sequence (Hard Edition)

## 题目描述

序列123456789101112131415161718192021222324252627282930313233343536...是无穷无尽的,现在你要输出它的第k项。

## 样例 #1

### 输入

```
7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
21
```

### 输出

```
5
```

# 题解

## 作者：MarchKid_Joe (赞：8)

[CF1177B Digits Sequence (Hard Edition)](https://www.luogu.com.cn/problem/CF1177B)
# 1. 题目
给定一个序列 123456789101112...... 求第 $k$ 个数字是几？

# 2. 思路
- **判断位数**

 1~9 所占数字共 1*(9-1+1)=9 个
 
 10~99 所占数字共 2 * (99-10+1)=180 个
 
 100~999 所占数字共 3 * (999-100+1)=2700 个
 
 ... ...
 
所以我们可以根据这个规律去判断第 $k$ 个数字所在的是 $n$ 位数，如

当$k$=123时

123-9=114<180，所以为2位数。

当$k$=10000时

10000-9=9991>180

9991-180=9811>2700

9811-2700=7111<36000，所以为4位数。

即在求几位数时仅需数减到第几次就不能再往下减了代码实现
```cpp
for(int n=1,i=1;k-n*i*9>=0;n++,i*=10)
{
	k-=n*i*9;
}
```
- **判断第$k$个数字所在的数**

很简单，只需要用减后的$k$/$n$，然后再往前补数——比如$n$=2(2位数)，只需$k$/$n$+9；$n$=3(3位数)，只需$k$/$n$+99... ...
```cpp
/*用a来存储9,99，999，只需在开始所在的for循环中实现,最后再将a+k/n
*/
for(int n=1,i=1;k-n*i*9>=0;n++,i*=10)
{
	k-=n*i*9;
	a+=i*9;
}
a+=k/n;
/*此处为特判，在除不尽时，a应+1，例如当k=12时，不特判时a=10，但是实际为11*/
if(k%n!=0)++a;
```
- **查询**

求出**余数**$o$，然后**从左向右**第 $o$ 个数即为所求

# 3. 代码
```cpp
#include<cstdio>
using namespace std;
long long k,i,n,a,o;
int main()
{
	scanf("%lld",&k);
	for(n=1,i=1;k-i*n*9>=0;n++,i*=10)
	{
		a+=i*9;
		k-=i*n*9;
	}
	a+=k/n;
	if(k%n!=0)
	{
		++a;
		o=n-(k%n);
	}
	while(o-->0) a/=10;
	printf("%lld",a%10);
	return 0;
}
```

---

## 作者：Limit (赞：6)

[A题](http://codeforces.com/problemset/problem/1177/A)想必都是秒掉了,~~就是一个模拟就能过了...~~

然后发现B题居然题面和A题相同,但是数据范围貌似~~QAQ~~
于是就有了这样一篇博客...

```cpp
#include<bits/stdc++.h>
using namespace std;
long long N;
int main()
{
    scanf("%lld",&N);//注意long long读入
    long long now=0;//记录当前长度
    int len=0;//记录当前每个数字长度
    long long _long=9,sum=1;
    while(now<N)
    {
        len+=1;
        now+=_long*len;
        _long*=10;
        sum*=10;
    }
    _long/=10;
    now-=_long*len;
    long long QAQ=(N-now)/len+sum/10;//找到这个位置在哪个数字的哪个位置
    int rank=(N-now)%len;
    int i;
    if(!rank)//如果在第零位则是上一个数字的最后一位
    {
        rank=len;
        QAQ--;
    }
    for(i=1;i<=len-rank;i++)QAQ/=10;//找到这个数字的这个位置
    printf("%lld",QAQ%10);//输出
    return 0;
}
```
时间复杂度大概就是~~O(?)~~
反正很小就对了...

---

## 作者：淸梣ling (赞：5)

# 题目链接
[CF1177B](https://www.luogu.com.cn/problem/CF1177B)

相似题目：[CF1177A](https://www.luogu.com.cn/problem/CF1177A)

# 分析
对于A题的话暴力模拟就可以过去，但B题的 $k$ 范围很大，所以就需要换一种方法加快模拟的速度。

仔细观察以下

```
1~9  9个数
10~99 90个数
100~999 900个数
...
```

我们可以发现数字长度为 $i$ 的数字有 $9 \times 10^{i-1}$ 个。

那么就可以推出数字长度为 $i$ 的数字总长度为 $len=i \times 9 \times 10^{i-1}$。

那么枚举变量 $i$ 速度将会大大增加。在用一个 $all$ 存储总长度即可。

能枚举长度了，那么数字怎么找呢？我们可以先想办法找到 $k$ 所在的数字，在想办法把单个数字提取出来。

假设现在 $all$ 再加一次就大于等于 $k$，说明现在只需在长度为 $i$ 的数字里面找。可知 $len$ 中 $k-all$ 位就是所求答案，又因每个数长度都为 $i$，可以得到 $k$ 所在的数字从 $10^{i-1}$ 数的第 $\lceil \frac{k-all}{i} \rceil$ 个，数字就是 $10^{i-1}-1+\lceil \frac{k-all}{i} \rceil$（第一个数是$10^{i-1}$，所以要减一），那么数的第几位就可以用取余算出来，此时在处理一下余数为 $0$ 的情况，即 $(k-all-1) \mod i+1$ ,那么此题就愉快的A掉啦。

# code
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	long long k;
	long long i;//数字长度为i
	long long all=0;//总长度
    long long last_len;//还差多少位
    long long r_to_l;
    long long l_to_r;
    long long num;
	long long len=9;//数字长度为i总长度为len

	cin>>k;
	for(i=1;;i++,len*=10)
	{
		if(all+i*len>=k)
		{
			last_len=k-all;

			r_to_l=(last_len-1)%i+1;
            //所在数从右往左数第几位
			
            l_to_r= i+1 - r_to_l;
            //所在数从左往右数第几位
            //l_to_r + r_to_l = i+1
			
            num=len/9-1 + (last_len+i-1)/i;
            //计算k所在数字
            //这里向上取整用的(a+b-1)/b==ceil(a/b)
			
            while(l_to_r!=1)//循环找数
			{
				num/=10;
				--l_to_r;
			}
			
            cout<<num%10;//输出
			break;
		}
		all+=i*len;
	}
	return 0;
}

```
完结~~

---

## 作者：yeshubo_qwq (赞：4)

## 题意
输出序列 $123456789101112131415161718192021222324252627282930313233343536...$ 的第 $k$ 项。
## 思路
观察这个序列，发现这是由 $1$，$2$，$3$，$4$，$5$，$6$，$7$，$8$，$9$，$10$，$11$……一直连接起来得到的。

$k$ 的范围是 $10^{12}$，不能直接一位一位求出答案，需要利用找规律加快速度。

序列中所占位数：

一位数：$9\times1=9$ 位，

两位数：$90\times2=180$ 位，

三位数：$900\times3=2700$ 位，

……

我们可以利用此规律减去位数，加速程序。

```cpp
	x=9;y=1;
	while(k-x*y>0)k-=x*y,x*=10,y++,s+=x;//减去位数
	//y是位数，x表示有几个y位数
```

然后利用余数求出对应的 $y$ 位数要取的位数 $g$，并求出答案。

```cpp
	k%y==0?g=y:g=k%y;//取g位数 
	return cout<<(int)(pow(10,y-1)+(k-1)/y)/(int)pow(10,y-g)%10,0;//求出答案
```
## 代码
完整的~~高清可抄~~程序：
```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
int k,x,y,s,g;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>k;
	x=9;y=1;
	while(k-x*y>0)k-=x*y,x*=10,y++,s+=x;//减去位数
	//y是位数，x表示有几个y位数
	k%y==0?g=y:g=k%y;//取g位数 
	return cout<<(int)(pow(10,y-1)+(k-1)/y)/(int)pow(10,y-g)%10,0;//求出答案 
}
```


---

## 作者：linluke (赞：2)

一个简单的模拟，首先先计算当前是几位数，具体计算方法为循环枚举，我们知道对于i位数有$9 \times 10^i$个，所以如果全部计算的话应该贡献为$i \times 9 \times 10^i$，这样通过枚举就很容易确定现在是几位数了。然后根据几位数推断当前的数是什么，数的个数应该是$\frac{k}{i}$(这里的k指剩余的k)，然后即可求出我们要求的诗这个数的第几位。  

本代码应该算是比较简短的，压行前24行。

```cpp
#include <cstdio>

int main(){
    long long k; scanf("%lld", &k);
    long long cur = 1, cnt = 9;
    while (cur * cnt < k){k -= cur * cnt; cnt *= 10, ++cur;}
    long long mod = k % cur, a = (k - 1) / cur;
    if (!mod) mod = cur;
    long long num = 1;
    for (int i = 1; i < cur; ++i) num *= 10;
    num += a;
    for (int i = 1; i <= (cur - mod); ++i) num /= 10;
    printf("%lld", num % 10);
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### [传送门](https://www.luogu.com.cn/problem/CF1177B)
题意：

给一个序列 $ 1234567891011121314151617...$ ，求出它的第 $k$ 项。
#### 思路:
1.找规律

一位： $ 9 $ 个

二位： $ 180 $ 个

三位： $ 2700 $ 个

 $ 9=1 \times 9 \times 1 $

 $ 180=10 \times 9 \times 2 $

 $ 2700=100 \times 9 \times3 $

2.余数处理

在减的过程中，统计数量。

余数除以位数再一个一个找出数字就可以啦。

####  AC code
```cpp
#include<bits/stdc++.h>
#define int long long//十年OI一场空，不开longlong见祖宗 
using namespace std;
int k,p10,pp,sum,s,y;
signed main(){
	cin>>k;
	if(k<=9){cout<<k;return 0;}//特判 
	p10=0;pp=1;//pp表示1~...   p10表示10的几次方 
	while(k>0){    //逐个剪去 
		k-=pp*9*pow(10,p10);
		sum+=9*pow(10,p10);//sum表示总个数 
		pp++;p10++;
	}
	pp--;p10--;
	k+=pp*9*pow(10,p10);
	sum-=9*pow(10,p10);//降负的还原 
	s=k/pp;
	y=k%pp;
	sum+=s;
	if(y==0)cout<<sum%10;//余数为0时，直接输出各位 
	else {
		sum++;
		pp=pp-y;
		cout<<sum/(int)(pow(10,pp))%10;//取出第pp位 
	}
	return 0;//！！！完结撒花！！！ 
}
```


---

## 作者：lmndiscyhyzdxss (赞：1)

[题目传送门CF1177B Digits Sequence (Hard Edition)](https://www.luogu.com.cn/problem/CF1177B)

咱先讲讲思路：

- 我们可以把题目指出的数列分成如下：

分解前:  $ 123456789101112131415161718...... $ 

分解后:  $ 1,2,3,4,5,6,7,8,9,10,11,12,13...... $

- 判断位数

$  1  $ ~ $  9  $  所占数字共  $  1 \times (9-1+1)=9  $  个。

$  10  $ ~ $  99  $  所占数字共  $  2 \times (99-10+1)=180  $  个。

$  100  $ ~ $  999  $  所占数字共  $  3 \times (999-100+1)=2700  $ 个。

 $ \ldots\ldots $ 

我们统计出数字个数和,比较后即可得出含有第 $ k $ 个数字的那个数有 $ h $ 位。

这是代码：

```cpp
    for(int i=1;i<=12;i++)
    {
        l+=i*(pow(10,i)-pow(10,i-1));
        if(l>=k){h=i;break;}
    }
```


 $ 1. $ 然后求出这个位数的最小数：``pow(10,h)`` 

 $ 2. $ 再求出  $  h-1  $  位及之前的数字个数和：``l-=h*(pow(10,h)-pow(10,h-1));``

 $ 3. $ 接着求出含有第  $  k  $  个数字的那个数是  $  h  $  位数的第几个：``t1=(k-l)/h;``

 $ 4. $ 再求出第  $  k  $  个数字在那个数的第几位：``t2=(k-l)%h;``

 $ 5. $ 然后求出这个数是几：``g=z+t1;``
 
 $ 6. $ 加个特判：``if(t2==0)g--,t2=h;``

 $ 7. $ 来个数字分离：

```cpp
    while(g>0)
    {
    	a[++j]=g%10,g=g/10;
    }
```

最后求出来：``cout<<a[j-t2+1];``

## 话不多说,直接上代码

```cpp
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
long long k,l=0,h,j=0;
int a[22];
int main(){
	cin>>k;
   for(int i=1;i<=12;i++)//判断有几位
   {
       l+=i*(pow(10,i)-pow(10,i-1));
       if(l>=k){h=i;break;}
   }
   l-=h*(pow(10,h)-pow(10,h-1));
   long long z=pow(10,h-1),t1=(k-l)/h,t2=(k-l)%h;//这个位数的最小数，h位数的第几个，在那个数的第几位。
   long long g=z+t1;//这个数是几
   if(t2==0)g--,t2=h;//特判
   while(g>0)//数字分离
   {
      a[++j]=g%10,g=g/10;
   }
    cout<<a[j-t2+1];
    return 0;
}
```


---

## 作者：MILLOPE (赞：1)

## 题目
>[CF1177A](https://www.luogu.org/problemnew/show/CF1177A)

>[CF1177B](https://www.luogu.org/problemnew/show/CF1177B)

>题目描述
序列123456789101112131415161718192021222324252627282930313233343536...是无穷无尽的,现在你要输出它的第k项。
>两道题面一模一样的题，只不过数据范围不同

## 题解
- 找出所求的$k$所在的数字是几位数，并且确定这个数，设为$x$
- 求出所求项在$x$中是从左向右数第几位，输出$x$对应位即可
- 求出是几位数字的方法
	$k = k - (9 *1 +90 *2 +\cdots +(9 *10^n)*n) \ \ \ \ \ (k>0)$
	即$n$位数在序列中对应长度为$9*10^n*n$（手推一下应该很好理解）
- 设$k$为最终所减后剩下的值，$cnt$为当前所在区间位数
- 令$a = (k - 1) / cnt$，$b = (k - 1) mod \ cnt + 1$，因为我们要求$k$对应的这个数字，所以$a$表示在此区间中所求的这个数$x$前面有几个数，$b$为$k$对应这个数字从左往右数的第几位
- 那么显然$x =\begin{cases} 10^{cnt-1}+a & b > 0 \\ 10^{cnt-1} + (a -1) & b=0\end{cases}$
- 最终答案为$x / 10^{cnt - b} \ mod \ 10$

## code 
```cpp
#include <bits/stdc++.h> 
using namespace std; 
typedef long long LL; 

int main() {
    LL k; 
    scanf("%lld", &k); 
    LL now = 9, cnt = 1; 
    while (k > 0) {
        k -= now * cnt; 
        now *= 10; 
        ++cnt; 
    }
    now /= 10; 
    cnt--; 
    k += now * cnt; 
    LL a = (k - 1) / cnt; 
    LL b = (k - 1) % cnt + 1; 
    LL c = 1; 
    for (int i = 1; i < cnt; ++i) 
    	c *= 10; 
    if (b == 0) --a; 
    c += a; 
    for (LL i = 1; i <= cnt - b; ++i) 
        c /= 10; 
    printf("%lld", c % 10); 
    return 0; 
}
```

---

## 作者：Φρανκ (赞：0)

题意：求数列 $1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 0, 1, 1, 1, 2, ...$ 的第 $k$ 项。

核心思想：数位计算

解：

分三步：

1. 判断所在数的位数
2. 判断所在数的值
3. 判断在所在数的数位

容易发现，$i$ 位数共有 $9\times 10^{i-1}$ 个，占 $i\times 9\times 10^{i-1}$ 个数位。令 $i$ 位以内的数共占 $a_i$ 个数位，由数学归纳法可以证明 $a_i=10a_{i-1}+10^i-1$ 。若 $a_i-1\le k\le a_i$ ，就说明该数有 $i$ 位。（也就是说，所有 $i$ 位以下的数都在它以前）

然后可以知道，第 $k$ 项在第 $\lceil\frac{k-a_{i-1}}{i}\rceil$ 个 $i$ 位数中，且该数在该项右面有 $i\times\lceil\frac{k-a_{i-1}}{i}\rceil -k-a_{i-1}$ 位 。也就是说，它是 $\lceil\frac{k-a_{i-1}}{i}\rceil+10^i-1$ 的 $10^{i\times\lceil\frac{k-a_{i-1}}{i}\rceil -k-a_{i-1}}$ 位。通过取余求算即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long k, d[12]={0, 9, 189, 2889, 38889, 488889, 5888889, 68888889, 788888889, 8888888889, 98888888889, 1088888888889}, vk, rk, res;
int main()
{
	cin>>k;
	for(int i=1; i<=11; i++)
		if(k<=d[i])//判断位数 
		{
			vk=(k-d[i-1]-1)/i+1+pow(10, i-1)-1;//判断值 
			rk=(i-(k-d[i-1])%i)%i;//判断数位 
//			cout<<vk<<" "<<rk;
			res=(vk%(long long)(pow(10, rk+1))/(long long)(pow(10, rk)));//求数字 
			cout<<res; 
			return 0;
		}
	return 0;
}

```

---

## 作者：hhh_778899 (赞：0)

## 题意

- 给定一个由连续正整数拼接成的序列，要求输出这个序列的第 $k$ 项。

## $\textcolor{black}{\operatorname{Step}\,1}$

- 要想求出第 $k$ 项的值，我们需要先判断这个数字所在数的位数，于是开始找规律：

- 一位数：共 $9$ 个，位数为 $9 \times 1 = 9$ 位；

- 两位数：共 $90$ 个，位数为 $90 \times 2 = 180$ 位；

- 三位数：共 $900$ 个，位数为 $900 \times 3 = 2700$ 位；

$\implies n$ 位数：共 $9 \times 10^{\,n-1}$ 个，位数为 $9 \times 10^{\,n-1} \times n$ 位。

$\implies$ 代码如下：

```cpp
long long k,len=1,p=9;//考虑到数据范围，必须开long long
cin>>k;
while(k>len*p)//len代表几位数，p代表len位数的个数
{
	k-=len*p;
	p*=10;
	len++;
}
```

- 注：以下步骤中提到的 $k$ ，均指第一阶段结束后 $k$ 的取值，即为剩余的位数。

## $\textcolor{black}{\operatorname{Step}\,2}$

- 求出 $k$ 所在的数是 $len$ 位数后，我们就能知道还有几个数位才能到 $k$ 。

- 用剩余的数位个数除以 $len$ 并向上取整，即可求出 $k$ 所在的数是第几个 $len$ 位数。

- 由此，我们便可以推出第二阶段的公式 (千万别忘了 $-1$ ) ：

$$ans=10^{\;len-1}+\left\lceil\dfrac{k}{len}\right\rceil-1$$

$\implies$ 代码： `ans=pow(10.0,len-1)+ceil((double)k/len)-1;`

## $\textcolor{black}{\operatorname{Step}\,3}$

- 有了前两个阶段，现在我们只需求出 $k$ 处于 $ans$ 的第几位就行了。

- 显然，我们用 $k$ 除以 $len$ 所得的余数，就是 $k$ 在 $ans$ 中的位数。

- 但这里需要注意：如果余数是 $0$ ，那么 $k$ 就是 $ans$ 的末位，也就是第 $len$ 位。

$\implies$ 代码：`k%len==0?k=len:k%=len;`

## $\textcolor{black}{\operatorname{Step}\,4}$

- 第四阶段，我们的目标就是要想办法输出 $ans$ 特定的某一位，方法其实很多。

- 这里我用的是头文件 `<sstream>` 中自带的函数，将整数转为字符串，代码如下：

```cpp
string NumberToString(long long ans)
{
	stringstream ss;
	ss<<ans;
	return ss.str();
}
```

- 最后，输出字符串从左往右特定的一位，这个题就算做完啦。下面附上完整代码：

```cpp
#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

string NumberToString(long long ans)
{
	stringstream ss;
	ss<<ans;
	return ss.str();
}

int main()
{
	long long k,len=1,p=9,ans;
	cin>>k;
	while(k>len*p)
	{
		k-=len*p;
		p*=10;
		len++;
	}
	ans=pow(10.0,len-1)+ceil((double)k/len)-1;
	k%len==0?k=len:k%=len;
	string s=NumberToString(ans);
	cout<<s[k-1];//注意数组下标从0开始，所以要减1
	return 0;
}
```

- 双倍经验：[CF1177A](https://www.luogu.com.cn/problem/CF1177A)

---

## 作者：_Spectator_ (赞：0)


[可能更好的食用体验](/blog/523641/CF1177B) $|$ 
[题目传送门](/problem/CF1177B) $|$ 
[我的其他题解](/blog/523641/#type=题解)

本题为 [CF1177A](/problem/CF1177A) 的强化版，疑似谷内最水紫题（现已掉绿 QwQ）。

------------

${\large\color{#00CD00}\text{主要思路}}$

首先我们把这个数串按位数分段，可以得到：

$1$ 位：$(1,2,3,...,9)$ 共 $9-1+1=9$ 个数，占 $1\times9=9$ 个数字。

$2$ 位：$(10,11,12,...,99)$ 共 $99-10+1=90$ 个数，占 $2\times90=180$ 个数字。

$3$ 位：$(100,101,102,...,999)$ 共 $999-100+1=900$ 个数，占 $3\times900=270$ 个数字。

$\dots\dots$

规律已经很明显了，$len$ 位数就会占 $9\times10^{len-1}\times len$ 个数字。于是，我们就能计算出第 $k$ 个数字所在的数的位数：

```cpp
len=1,t=9;　
while(k>t*len)k-=t*len,t*=10,len++;　
```
以 $k=21$ 为例，计算完后 $len=2,k=12$。再用剩下的 $12$ 位数字除以 $2$，就能计算出这是第 $6$ 个 $2$ 位数，也就是 $10^{2-1}+6-1=15$。由于 $12\mod2=0$，所以应该是 $15$ 的第 $2$ 个数字，即 $5$。

这样做看起来已经没有什么问题了，但其实还是有一些瑕疵。例如，当 $k=20$ 时，计算完位数后 $len=2,k=11$。这时用 $11\div2$，会计算出这是第 $5$ 个 $2$ 位数，明显不符合我们的预期。所以，在计算这是第几个 $len$ 位数时，应该要**向上取整**。这样，才算解决了。

总结：
1. 计算出第 $k$ 位数所在的数的位数 $len$。
2. $k\div len$，求出是第几个 $len$ 位数，要向上取整。
3. $k\mod len$，找到是这个数的第几位，得数为 $0$ 时为最后一位。

最后提供几组数据，大家可以拿来测一测：

1. **输入：**`10`$\qquad$**输出：**`1`
2. **输入：**`189`$\qquad$**输出：**`9`
3. **输入：**`114514`$\qquad$**输出：**`4`
4. **输入：**`1000000000000`$\qquad$**输出：**`1`

------------

${\large\color{#00CD00}\text{完整代码}}$

代码貌似也是所有题解里最简短的了。

```cpp
#pragma G++ optimize(2)
#include<bits/stdc++.h>
using namespace std;
long long k,len=1,t=9,s;
int main()
{　
	ios::sync_with_stdio(false);
	cin>>k;　
	while(k>t*len)k-=t*len,t*=10,len++;//计算出第k位数所在的数的位数 
	s=pow(10,len-1)+ceil(k*1.0/len)-1,k%=len;//ceil(x)的作用是将x向上取整 
	if(k==0)k=len;　
	cout<<to_string(s)[k-1];　
	//to_string()的作用是将一个整数转化为字符串。后面能直接用下标运算符访问也属实是惊到我了 
	return 0;　
}　
```
对了，`to_string()`函数是 C++11 的新函数，~~和我一样~~还在用 C++98 的读者可以使用[洛谷IDE](/ide)编辑程序。

**[${\color{Black}\textbf{xt\_\_}}$](/user/523641) 温馨提示：**


${\large\color{White}\text\colorbox{#AD8800}{题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $

---

## 作者：LYqwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1177B)

# 题目大意

输出 $1234567891011121314151617\dots$ 的第 $k(1 \le k \le 10^{12})$ 项。

# 思路

考虑直接模拟，$\mathcal{O}(k)$ 时间复杂度建立这个序列，并输出第 $k$ 项。显然，这是不可行的方法，数据范围为 $10^{12}$。~~但是[CF1177A](https://www.luogu.com.cn/problem/CF1177A)可以。~~

那么我们就要考虑更快的方法：找出包含第 $k$ 项的那个数。

## 确定位数

首先，需要确定这个数的位数。

先来观察一下位数分别为 $1,2,3,4,5\dots$ 位的数分别有多少个：

- $1$ 位：$[1 \dots 9]$，$9$ 个数。
- $2$ 位：$[10 \dots 99]$，$90$ 个数。
- $3$ 位：$[100 \dots 999]$，$900$ 个数。
- $\dots$

但是，我们要求的是这些数合在一起，就像字符串拼接一样，一共有多少位。很简单，将不同位数的数的数量乘上它们各自的位数，就是一共的位数了。

- $1$ 位：一共 $9$ 个数，$9$ 位。
- $2$ 位：一共 $90$ 个数，$180$ 位。
- $3$ 位：一共 $900$ 个数，$2700$ 位。
- $\dots$

设位数为 $len$，那么当前位数的数的总位数计算公式为：$len \times 10^{len-1} \times 9$。

得到这些结论，那么得出到底是几位数就很简单了。

进行一个循环，定义 $len=1$，$len$ 每次加一，我们每次将 $k$ 减去有 $len$ 位的数的总位数，直到发现再减就比 $0$ 小了为止。

$len$ 最后的值即为包含第 $k$ 位数的数的位数。

~~怎么这么绕口令啊。~~

代码实现：

```cpp
ll i,len; // 用 i 存放 10^len-1
// 只要序列第 k 位不在当前位数的数里，那就继续减，直到找到为止
for(i=1; k-len*i*9>=0; len++,i*=10){
	k-=len*i*9; // 减去当前位数的数的总长度，下一次要找比当前多一位的
}
```

## 确定包含第 $k$ 位的数是多少

我们定义包含第 $k$ 位的数为 $n$。

最基本的，就是将位数 $\le len$ 的数的个数都加进去，这样就找到了这个数的最小值。这个操作要和上面的找位数一起执行

如何准确确定这个数是多少呢？

在我们找到这个数的最小值后，$k$ 成为了序列上从有 $len$ 位数开始的第 $k$ 项。$len$ 是位数，那么 $n+\dfrac{k}{len}$ 就是包含第 $k$ 位的数。

例如 $len=3$，经过操作后的 $k=6$，那么 $n$ 就应该是 $\dots 100101102103 \dots$ 中的 $101$，也就是 $99+\dfrac{3}{6}$。

应该很容易理解吧，就是要求第 $k$ 位，$k$ 除以 $len$ 就代表有多少个三位数在 $[k,len]$ 之间，就这么简单。

还有一个问题，就是——

## 若 $k \bmod len \ne 0$？

上面只考虑了最基本的情况，这里需要加上一个特判。

还是一个例子：$len=3,k=5$，截取的序列为 $\dots 100101102103 \dots$，尝试使 $n \gets n+\dfrac{k}{len}$，`C++` 有自动向下取整，所以得到的结果为 $100$。显然，包含第 $k$ 位的数并不是 $100$，而是 $100+1=101$。

在 $n \gets n+1$ 后，答案也有所变更。我们可以通过式子 $len-(k \bmod len)$ 得出答案在哪一位，设 $len-(k \bmod len)$ 为 $bit$，那么我们将 $n$ 的后 $bit-1$ 位去掉即可。

处理后，$n$ 的个位就是答案。

# 代码

代码里注释也很详细的(可以说是差不多又讲了一遍)。

此代码也可过[CF1177A](https://www.luogu.com.cn/problem/CF1177A)。

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
// n 存放第 k 个数字所在的数，用于计算最后的答案
// len 存放 k 所在数的位数
// bit 用于存储序列第 k 位在 n 中从右往左数哪一位
ll k,n,len=1,bit;

int main(){
	// k 存放的是要求序列的位数，我们循环时直接让它减去已经跳过的位
	cin >> k;
	// 越到高位，包含的数越多(废话)
	// 只要序列第 k 位不在当前位数的数里，那就继续减，直到找到为止
	for(ll i=1; k-len*i*9>=0; len++,i*=10){
		k-=len*i*9; // 减去当前位数的数的总长度，下一次要找比当前多一位的
		n+=i*9; // 计算序列第 k 位所在的数
	}
	// 经过上面的处理后的 k 就是序列从有 len 位数开始的第 k 项
	// 就比如 len=3，那么现在的答案就是 100101102103... 的第 k 项
	// 那么 k/len 就是从 len 位数开始，经过了多少个数才到包含第 k 项的那个数
	// 于是包含 k 的那个数 n 加上 k/len 就正好是包含 k 的那个数了
	n+=k/len;
	// 还有一个问题：k/len 除不尽的情况
	// 如果 k/len 刚好除的尽，那么答案就是这个数的个位，应该很容易理解吧
	// 若除不尽，万(hěn)能(dú)的 C++(C cǎo) 会向下取整
	// 那就说明，现在的 n 还不是包含 k 的那个数，n+1 才是包含 k 的数
    // 例如，执行完上面代码的 k=5,len=3,n=100
    // 在 ...100101102... 中，显然，n 应该是 101 才对
	// 所以就要加一个特判
	if(k%len!=0){
		n++; // 转移到下一个数
		bit=len-(k%len);
    	// 我们还要将 n 的个位变为答案
		// 可以通过 len-(k%len) 得出最终答案在 n 的从右往左数第几位
		// 然后，将 n 后面 bit 位都去掉，就得到最终答案；n 的第一位了
		while(bit-->0){
			n/=10;
		}
	}
	cout << n%10 << endl; // 剩下数的最后一位即为答案
	return 0;
}
```

~~代码里是不是好多注释都是废话？~~

---

## 作者：F_Mu (赞：0)

题意：将1，2，3，……，n的数字拼成一个字符串，问该字符串中的某一位是多少。

分析：

第一步：找到答案所在数的位数，比如找到的是9876中的6，9876为答案所在数，位数为4。

第二步：找到答案所在数在当前位数排第几，比如123在3位数中排第24(100排第一）。此时即可找到答案所在数。

第三步：找到答案在答案所在数从左往右排第几，比如9876的7排第3。

第四步：除法找到答案。
```cpp
#include <bits/stdc++.h>

#define maxn 2005
#define mod 1000000007
#define inf 0x3f3f3f3f
#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define LL long long
using namespace std;

ll pow(ll x, ll y) {//快速幂模板
    ll ans = 1;
    while (y) {
        if (y & 1)
            ans = ans * x;
        x *= x;
        y >>= 1;
    }
    return ans;
}

int main() {
    start;
    ll k;
    cin >> k;
    if (k < 10) {//直接输出k<10的情况
        cout << k << endl;
        return 0;
    }
    ll cnt = 1;//当前位数
    ll num = 9;//当前位数的数字有多少个
    ll tot = 9;//总共数了多少数
    while (tot < k) {
        num *= 10;
        ++cnt;
        tot += num * cnt;
    }
    tot -= num * cnt;//（（答案所在数）的位数-1）有多少数
    k -= tot;//答案在减去前面数列后为第几
    ll n = k / cnt;//答案所在数在当前位数的数字中排第几
    k %= cnt;//答案在所在数从左往右数第几位
    ll base = pow(10ll, cnt - 1);//当前位数的最小数
    if (k == 0) {//如果整除，说明是当前位数往后数n个数的最后一位
        cout << (base + n) % 10 << endl;
        return 0;
    }
    ll m = pow(10ll, cnt - k);//从左往右数的第几位后面全部除掉
    cout << (base + n) / m % 10 << endl;
    return 0;
}
```


---

## 作者：xh39 (赞：0)

思路(很简单):先找出具体是那个数字,在确定是哪一位,就可以了。

怎么找出是那个数字?先确定这个数字的是几位数,在确定在这个从1至$10^{(\text{位数-1})}$有多少个数字,然后就可以计算出这个数字当前位数中是第几个,接下来就用$10^{\text{(位数-1)}}$+这个数。

简单思路放代码里了。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long size(long long a){ //求一个整数的长度。
    int sum=0;
    if(a==0){
        return 1;
    }
    while(a!=0){ //能除几次10就有几位。
        a/=10;
        sum++;
    }
    return sum;
}
long long get(long long a,long long k){ //求一个整数a的第k位。(应该不难求吧。。。)
    long long zyl=(long long)(size(a)-k),xyq;
    xyq=pow(10,zyl);
    return a/xyq%10; //先去掉k位之后那些数,再取当前数的个位数,就是答案。
}
int main(){
    long long sum=0,k,i,t; //i是用来看结果有几位。sum是用来统计从1到上一位总共经历了多少位数。
    cin>>k;
    for(i=1;sum+(i*9)*size(i)<k;i*=10){
        sum+=(i*9)*size(i);
    }
    t=i+(k-sum-1)/size(i); //计算出是哪个数。
    if((k-sum)%size(i)==0){ //特殊判断如果是余0相当于余size(i)。(因为没有第0位)
        cout<<get(t,size(i));
    }else{
        cout<<get(t,(k-sum)%size(i));
    }
    return 0;
}
```
好像我的代码在cf里用c++11会$\color{blue}wrong\;anwer\;on\;test\;33$,只能用c++14。

温馨提示:记得开long long!

---

## 作者：SFWR (赞：0)

根据题意模拟找到$k$所在的整数与在此整数中的位置即可
具体的是先找出位数，再找出同样位数的个数，相减得到$k$所在整数。

具体方法看代码即可，写了一些特判，麻烦了一点,还要注意由于$k$很大，全部开$LL$保过

```cpp
#include<bits/stdc++.h>
using namespace std;
long long int k,to=9,ti=0,num[100000];
int main()
{
	cin>>k;
	while(1)
	{ti++;
	if(k-to*ti>=0)k=k-to*ti;
	else break;
	to*=10;
	}
	if(k==0){cout<<9;return 0;}
	if(k%ti==0){long long int q=pow(10,ti-1)+k/ti-1;cout<<q%10;return 0;}
	else {
	long long int sum=k/ti*ti;
	long long int q=pow(10,ti-1)+k/ti,pos=0;
	while(q)
	{
		num[++pos]=q%10;
		q/=10;
	}
	k=k-k/ti*ti;
	cout<<num[pos-k+1];	
	}
}
```



---

