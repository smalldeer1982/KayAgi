# Couple number

## 题目描述

对于一个整数 $n$，若存在两个自然数 $x, y$，满足 $n = x^2 - y^2$，则称 $n$ 是 Couple number。

给出 $a,b$，请求出 $[a, b]$ 范围内有多少个 Couple number。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $-10^7 \le a < b \le 10^7$ ，$b - a \le 10^7$。

## 样例 #1

### 输入

```
1 10
```

### 输出

```
7
```

# 题解

## 作者：刘心远 (赞：158)

嘿嘿，超简单的数学题！！！

【算法分析】

step 1：a^2-b^2=(a+b)(a-b)=>a+b与a-b奇偶性相同

step 3：所以(a+b)(a-b)要么是奇数，要么是4的倍数

step 4：couple number要么是奇数，要么是4的倍数

step 5：验证：若n=2k-1，则(a+b)(a-b)=2k-1

a+b=2k-1, a-b=1, a=k, b=k-1正确！

若n=4k，则(a+b)(a-b)=4k, a+b=2k, a-b=2, a=k+1, b=k-1正确！

【温馨提示】题目说是整数，而非正整数，所以不用特判！

【华丽标程】

```cpp
#include<iostream>
using namespace std;
int main()
{
    int n1,n2,i,ans=0;
    cin>>n1>>n2;
    for(i=n1;i<=n2;i++)
    if(i%4==0||i%2!=0)ans++;  //奇数或4的倍数
    cout<<ans<<endl;
    return 0;
}
更多消息请见http://blog.sina.com.cn/s/blog_1754bd7130102wxk5.html
```

---

## 作者：张文奕 (赞：29)

这道题运用了平方差公式


这里给大家演示一下平方差公式化简的步骤

   (a+b)(a-b)
   =a(a-b)+b(a-b)
   =a^2-ab+ab-b^2
   =a^2-b^2
   
∴ 由此式反推回去


a^2-b^2=(a+b)(a-b)

a+b与a-b奇偶性一定相同

证明：

a+b-(a-b)=a+b-a+b=2b

∵b是整数，∴2b一定是偶数

∴a+b与a-b奇偶性相同

那么，出现Couple number数有两种情况：a+b为奇数或a+b为偶数

如果a+b是奇数，奇数乘奇数一定还得奇数，这是情况①

如果a+b是偶数，偶数乘偶数一定是4的倍数，这是情况②

综上所述，Couple number必须符合是4的倍数或是奇数中的一种

那么只需要枚举Couple number,时间复杂度为O(n1-n2)

题目保证n1-n2<1e7,所以不用担心TLE

下面是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n1,n2,ans;
int main(){
    cin>>n1>>n2;
    for (;n1<=n2;n1++)
        if (n1%2||n1%4==0) ans++;
    cout<<ans;
    return 0;
}```

---

## 作者：KesdiaelKen (赞：19)

看大家好像都是模拟的，我这里来一波数学计算的，时间复杂度大约只有O(1)。

思路，下面的各位大神已经说得很清楚了，下面再跟大家稍微解释一下。

若使n=a^2-b^2，则n=(a+b)(a-b)。

①n%4==0，则设n=4k，有a=k+1，b=k-1时等式成立；

②n%4==1，则设n=4k+1，有a=2k+1，b=2k时等式成立；

③n%4==2，则(a+b)与(a-b)中一个为奇数，一个为2的奇数倍。又因为(a+b)，(a-b)同奇偶性，所以与结论矛盾，即不成立。

④n%4==0，则设n=4k+3，有a=2k+2，b=2k+1时等式成立；

综上：n%4!=2时，均可符合n=a^2-b^2；反之亦然。

所以只需要找出n1至n2之间mod4余2的数，然后用总数减去它就行了。

然而不用枚举（要是数据再大点，就炸了），直接数学方法算就行了。

这里只详细解析n1、n2大于0的情况，其他情况由此情况均可以推得——

设mod4余2这样的数为N数，则：

n1至n2间的N数数量=n2至1的N数数量-(n1-1)至1的N数数量。可得x至1间的N数数量为：[(x+2)/4]（分类讨论即可）。所以有n1至n2间的N数数量=(n2+2)/4-(n1+1)/4（C++版公式）。

对于其他情况，比如一正一负或两负，只需要转化成上述情况，就可以算出来了。

另有解析，请看代码：

    
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
int main()
{
    long long gs,ygs;
    long long n1,n2;
    scanf("%lld%lld",&n1,&n2);
    ygs=n2-n1+1;//求总个数
    int h1,h2;
    if(n1<=0&&n2>=0)//一正一负
    {
        h1=(n2+2)/4;
        h2=((-n1)+2)/4;//将它分成正负两段分别统计
        gs=h1+h2;//求和即可
    }
    else
    {
        if(n1>0)//均为正数
        gs=(n2+2)/4-(n1+1)/4;//同上文解析
        else//均为负数
        gs=(-n1+2)/4-(-n2+1)/4;//取相反数，然后同均为正数情况
    }
    printf("%lld",ygs-gs);//相减即是答案
    return 0;
}
```

---

## 作者：zhuangzhenhao168 (赞：10)

	有很多人一直在那说什么奇数或是4的倍数，那么，为什么啦？？？我就来解释一下。
	首先，0  1  4  9  16  25  36 …… 相信大家看出来了，这是0的平方、1的平方、2的平方、3的平方…… 我们让两两相减，得到 1  3  5  7  9  11 …… 发现了吧！！！
	两两相减得到递增的奇数。所以，每个奇数都可以这么表示。例如：7，看看上面的表，发现7是第5个数减去第4个数，也就是16 - 9。
    再让这些奇数两两相加，得到 4  8  12  16  20  24  28 …… 可以看出来，每个4的倍数都可以这么表示。例如，16，它是第4个奇数与第5个奇数的和，也就是：
    16 = 7 + 9 = （16 - 9）+（25 - 16）=25 - 9 = 5^2 - 3^2 。其他的4的倍数也可以这么表示。再例如：
    20 = 9 + 11 = （25 - 16）+（36 - 25）= 36 - 16 = 6^2 - 4^2 。
    所以！ 
###     凡是奇数或是4的倍数都是俩数的平方差！ _~~反之亦然~~_
	上代码：
 	#include<bits/stdc++.h>    // 我是个懒人 
	using namespace std;
	int n1,n2,ans;
	int main(){
  	    cin>>n1>>n2;
   	    for(int i=n1;i<=n2;i++)
            if(i%4==0||i%2!=0)   //奇数或4的倍数
		    ans++;  
        cout<<ans<<endl;
        return 0;
	}
```


---

## 作者：Pisces (赞：9)

~~这怕是用新评测机的极（zui）优题解~~（运行内存居然只有0.6MB）

若两个数同号，则ans(a,b)=ans(0,max(abs(a),abs(b)))-ans(0,min(abs(a),abs(b)))+一个小小的特判（因为a也被减掉了）。

若两数异号，则ans(a,b)=ans(0,abs(a))+ans(0,abs(b))-中间重复的数（有3个）

而ans(0,m)=m+2-(m+2)/4，所以我用了一种神奇的方法（快读和答案一起算）。
```cpp
#pragma GCC target ("popcnt")//按位运算玄学优化
#include<stdio.h>//省空间
#include<ctype.h>//省空间
bool a[2],b;//用来存符号（正负）
bool p,q;//用来加的特判
inline char nc(){//玄学优化
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline long long read()//快读+运算
{
    long long X=0; char ch=0;
    while(!isdigit(ch)) {a[b^1]|=ch=='-';ch=nc();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=nc();
    X+=2;//将ans(0,abs(m))求出
    p=X&3;//特判，判断该数是否满足（这是第二个数）
    q|=p;//第一个数的特判
    return X-(X>>2);//结果
}
int main(){
	long long m=read(),n=read();
	if(a[0]==a[1]) printf("%lld",m>n?m-n+p:n-m+q);//同号情况
	else printf("%lld",m+n-3);//异号情况
	return 0;
}
```

---

## 作者：空城旧梦— (赞：7)

## pascal的题解真是少！！
让我来一发吧

根据Couple number的定义来判断

n=a²-b²=(a-b)×(a+b)   （平方差公式，不多说）

再由奇偶性可知(a-b)和(a+b)的奇偶性一样，接下来分两种情况讨论
1. 若都为奇数，则n也为奇数，那么假设(a+b)=n，(a-b)=1。可以解得a=(n+1)/2，b=(n-1)/2。因为n为奇数，a，b一定有整数解
2. 若都为偶数，则n为两个偶数的乘积，n必为4的倍数

接下来问题就变得十分简单，只要判断n1 和 n2之间满足是奇数或是4的倍数的数的总个数。

直接上代码

```pascal
var  n1,n2,i,j,k,l,ans:longint;
begin
  readln(n1,n2);
  for  i:=n1  to  n2  do
    if  odd(i)//判断奇偶
      then  inc(ans)
      else
        if  i mod 4=0  then  inc(ans);//判断是否为4的倍数
  writeln(ans);
end.

```

---

## 作者：午尘 (赞：5)

qwq颓了差不多一个星期文化课了qwq……

所以来写道数学题。

先放代码吧……

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n1,n2,k,i,s;
int main(){
	scanf("%lld%lld",&n1,&n2);
	s=0;
    for (i=n1;i<=n2;i++){
     if (i%4!=2 && i%4!=-2)  s++;
 }
    cout<<s<<endl;
  return  0;
}
```



------------

先说说注意点：

scanf输入用lld!!（www踩坑好几次了）。

还有就是考虑负数情况！！题目说**整数**！！没有“正”字！！



------------


接下来是证明啦……

```
//   a^2-b^2=(a-b)(a+b)
//   a+b-a+b=2*b 所以这两个因数之差为偶数  所以它们只能是两个奇数or两个偶数 
//   奇数情况：1 和 n  n-1一定是偶数，所以奇数都可以
//   偶数情况：i*j=n   i,j 均为偶数  所以2*2=4  n必须为4的倍数 
```
就照代码的形式放啦~


---

## 作者：0carryt0 (赞：4)

超短11行蒟蒻代码。

a^2-b^2=(a+b)(a-b)

1. 若a与b一奇一偶，设a=2x+1，b=2y；

式子就为（2x+2y+1）(2x+1-2y)

奇数乘奇数必为奇数，所以奇数可以。

2. 若a与b都为奇或都为偶，设a=2x，b=2y；

式子为4（x-y）（x+y）

则为4的倍数。

综上，只要枚举n1-n2中所有数ni，ni%4不为2就是可行的数。

**ps：一定要取绝对值，会有负数的！！！**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n1,n2;
int main()
{
    long long sum=0;
    scanf("%lld%lld",&n1,&n2);
    for(int i=n1;i<=n2;i++)
      if (abs(i%4)!=2) sum++;
    cout<<sum;
    return 0;
}
```
简单数学介绍，希望可以帮到大家


---

## 作者：36492677cwy (赞：3)

**拿例题看：
1~10判断：

1=1^2-0^2

2=没有 //（2-2）%4==0（也算）

3=2^2-1^2

4=2^2-0^2

5=3^2-2^2

6=没有 //（6-2）%4==0

7=4^2-3^2

8=3^2-1^2

9=5^2-4^2

10没有 //（10-2）%4==0

不难发现，当判断数字k时，看看（k-2）是否是4的倍数，若是4的倍数，则不是Couple number

代码如下：

```
#include<bits/stdc++.h>

using namespace std;

long long n1,n2,i,sum=0;

int main(){

	cin>>n1>>n2;
    
	sum=n2-n1+1;//共有n2-n1+1个数
    
	for(i=n1;i<=n2;i++){
    
		if((i-2)%4==0)sum--;//判断
        
	}
    
	cout<<sum;
    
}
```
**

---

## 作者：封禁用户 (赞：3)

楼下的大佬们居然无一例外的都使用了n%4!=2这个东西求的，然而我用的是暴力法，类似于筛法。思路是这样的：若n=a^2-b^2(a、b∈Z)，则根据平方差公式，有n=(a+b)(a-b)，那么设n=i×j，则可得二元一次方程组：

a+b=i
a-b=j
那么a=(i+j)/2，b=(i-j)/2，由于a、b都是整数，那么就可以得出这条结论：

### **若i+j为偶数，则i×j一定为Couple Number。**

所以我们就可以暴力枚举i和j，再开个布尔数组做标记就行了。

代码如下：

```cpp
    #include<iostream>
    #include<cstdio>
    #include<cmath>
    using namespace std;
    unsigned char bv[500000000];
    //首先做一点说明，这里用暴力筛法求的都是非负的CoupleNumber，如果是负的话可以看绝对值是不是CoupleNumber
    int main(){
        int l,r;
        cin>>l>>r;
        int n=max(abs(l),abs(r));//由于区间可能为负，所以要求出0~绝对值较大的那个区间中的CoupleNumber
        int sqr=sqrt(n)+1;
        for(int i=1;i<=sqr;i++){
            int loop=n/i;
            for(int j=i;j<=loop;j++){
                if((i+j)%2==0){
                    bv[i*j]=1;//i+j为偶则i*j为CoupleNumber
                }
            }
        }
        bv[0]=1;//这里要注意0也是CoupleNumber
        if(l<0&&r<0){//如果l和r都小于0的话就相当于求[|r|,|l|]
            int tmp=abs(l);
            l=abs(r);
            r=tmp;
        }
        int tot=0;
        if(l>=0&&r>=0){
            for(int i=l;i<=r;i++){
                if(bv[i])tot++;
            }
        }
        if(l<0){
        //如果l为负r为正则求[0,r]和[1,|l|]
            for(int i=0;i<=r;i++){
                if(bv[i])tot++;
            }
            l=abs(l);
            for(int i=1;i<=l;i++){
                if(bv[i])tot++;
            }
        }
        cout<<tot<<endl;
        return(0);
    }

```

---

## 作者：dell20050604 (赞：2)

本题代码十分简单，思路也并不难，但是为什么很多人30分，那是因为i%2==1是错的，i可以是负的，故要用abs，废话不多说，上代码！！




```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<string>
#include<map>
#include<vector>
#include<stack>
#include<queue>
#include<cstring>
#include<cmath>
#include<cstdio>
using namespace std;
int i,n1,n2,ans;
int main()
{
    cin>>n1>>n2;
    for(i=n1;i<=n2;++i)
    {
        if(i%4==0) ans++;
        if(abs(i)%2==1) ans++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：星之海 (赞：1)

蒟蒻来写一个题解

看到这题我先想到的是公式：(a+b)(a-b)=a²-b²

但是想了一下，如果用这种方法的话也可以，但是要枚举每个平方数之间的差，可能会超时

于是打算用找规律大法(<>_<>)

先从样例数据下手

1~10的话——

里面可以用平方差表示的数分别是：1 3 4 5 7 8 9

然后看一下不是平方差的哪些数：2 6 10

很快发现，它们是偶数

可是4、8也是偶数

于是认为，如果在一个范围 L...R 内，被排除的数应该是奇数、或者不是4的整数倍的数

所以代码非常好构建

```
#include<iostream>
#include<cstdio>
using namespace std;
inline int read()//玄学的读入优化
{
	int x=0,w=1;
	char c;
	while(c<'0'||c>'9')
	{
		if(c=='-')
		w=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*w;
}
int main()
{
	ios::sync_with_stdio(false);//玄学的stdio时间复杂度读入优化
	register int i;//register类型神奇优化
	register int a,b,sum=0;
	a=read();
	b=read();
	for(i=a;i<=b;i++)//枚举
	if(i%4==0||i%2!=0)//条件
	sum++;//累加
	cout<<sum<<endl;//输出结果即可
	return 0;
}//骚气的我8ms完美通过此题
```

---

## 作者：ghj1222 (赞：1)

**题目大意**：输入n1,n2，输出能够满足x∈[n1,n2]且满足x∈{y|y=a^2-b^2,a,b∈Z}的整数的个数

**幼儿园**：告你俩数，告我这俩数范围内（包括这俩数）中的所有能满足某个条件的整数的个数。条件是什么？条件就是这个数是一个整数的平方减去另一个整数的平方

**以下为数学公式和C++的混合体**

**分析**：

n=a^2-b^2

=(a+b)(a-b)

设a+b=x,a-b=y

则xy=n，a=(x+y)/2，b=(x-y)/2

∵a,b∈Z

∴(x+y)%2==0 (x-y)%2==0

∴x,y同奇偶

当x,y同奇时，n为奇

当x,y同偶时，n%4==0

综上，当n%2!=0或n%4==0时候是cp num

**另一种方法**

设a-b=1且a,b∈Z

则a^2-b^2=(a+b)\*(a-b)=a+b

即n=a+b

∵a-b=1

∴a,b不同奇偶

∴a+b为奇数

∴n为奇数

∴当a-b=1且a,b∈Z时，n=a^2-b^2为奇数

设a-b=2且a,b∈Z

则a^2-b^2=(a+b)(a-b)=2(a+b)

即n=2(a+b)

∵a-b=2

∴a,b同奇偶

∴a+b为偶数

∴n为四的倍数

∴当a-b=2且a,b∈Z时，n=a^2-b^2为4的倍数

综上，(略)

**实现**

从n1到n2循环，按照条件判断即可，代码略

**实现II**

有的XXX（脑补这是什么）想实现O(1)，怎么办？

我们会发现，每连续的四个数中就有三个cp num，那么我们就可以让n1+=4(n1-n2>4的情况下)，缩小n1到n2的范围，n1每+=4，ans+=3，那么如果我们让n2-n1<=4时，设n1+=4t,ans+=3t，请见代码：(注释)

```cpp
#include <cstdio>
using namespace std;
int main()
{
    int n1,n2,ans=0;
    scanf("%d%d",&n1,&n2);
    ans+=(n2-n1)/4*3;//(n2-n1)/4就是t，ans+=3t
    n1+=(n2-n1)/4*4;//(n2-n1)/4就是t，n1+=4t
    for(int i=n1;i<=n2;i++)//此时n2-n1<=4，可以算作是O(1)了吧。。。
        if(i%4==0||i%2!=0)//条件
            ans++;
    printf("%d\n",ans);
    return 0; 
}
```

---

## 作者：「QQ红包」 (赞：1)

由平方差公式可得，奇数和所有的4的倍数都是两个整数的平方差

此题与P1737 平方差问题的区别：1737强调了是两个正整数的平方之差，所以那题0,1,4不可以。

```cpp
#include<set>    
#include<map>    
#include<list>    
#include<queue>    
#include<stack>    
#include<string>    
#include<math.h>    
#include<time.h>    
#include<vector>    
#include<bitset>    
#include<memory>    
#include<utility>    
#include<stdio.h>    
#include<sstream>    
#include<iostream>    
#include<stdlib.h>    
#include<string.h>    
#include<algorithm> 
#define LL unsigned long long    
using namespace std;  
int main()  
{  
    int n,m;int sum=0;
    cin>>n>>m;
    for (int i=n;i<=m;i++)
    {
        if (abs(i%4)!=2)sum++;###**//一定要加绝对值！！！！ **###
    }
    cout<<sum;
    return 0;  
}
```

---

## 作者：ROOToj (赞：1)



代码极简的数学题，由平方差公式可得：除4k+2（k为整数）以外的整数均能找到两个整数的平方差与其相等。该公式可以简化为：(i-2)%4!=0。


附上AC源代码：













```cpp
#include
using namespace std;
int a,b,i,sum=0;
int main()
{
    scanf('%d%d',&a,&b);
    for(i=a;i<=b;i++)
        if((i-2)%4)sum++;
    printf('%d\n',sum);
    return 0;
}
```
​

-------------------------------------------END-------------------------------------------​​​​


---

## 作者：Shallowy (赞：0)

（pascal）关于Couple number的特征，我想下面的dalao们已经讲得很清楚了，即该数满足以下一点：

1. 该数为奇数；

2. 该数为4的倍数。

所以，偶数中是2的奇数倍的数不是Couple number.

如：2,4,6,8,10,12......中，4,8,12......是Couple number，其余不是。

因为Couple number实在有点多，所以我们可以只看不是Couple number的数。

容易得出，所有非Couple number数构成了一个公差为4的等差数列，这就很好办了。

**只要求出范围内非Couple number数的个数，即等差数列的项数，再求范围内数字总数与其之差，就是所求答案**

- 等差数列中，项数=（末项-首项）/公差+1.

首项、末项算法如下：

- 首项i：1. i=n1;

2. 若n1为奇数，则i=n1+1;（此时的i为不小于n1的最小的偶数）

3. 若i mod 4=0,则i=i+2.（如果i本身是Couple number，则下一个偶数是非Couple number）

- 末项j：1. j=n2;

2. 若n2为奇数，则j=n2-1;（此时的j为不大于n2的最大的偶数）

3. 若j mod 4=0,则j=j-2.（如果j本身是Couple number，则上一个偶数是非Couple number）

范围内Couple number的个数即为 (n2-n1+1)-((j-i) div 4+1)，化简后为 n2-n1-(j-i) div 4.

0ms看着舒服多了~

附上丑陋的pascal代码（化简得可能有点多，对比上面就行）。

```cpp
var
  a,b,i,j:longint;
procedure pd(var x,y:longint; z:longint);  //由于两数算法相似，就放在同一过程里了
  begin
    if odd(x) then y:=x+z div 2  //2 div 2=1，(-2) div 2=-1.
              else y:=x;
    if y mod 4=0 then inc(y,z);
  end;
begin
  read(a,b);  //输入n1,n2.
  pd(a,i,2); pd(b,j,-2);  //求i时+2，求j时+(-2).
  write(b-a-(j-i) div 4);  //直接输出.
end.
```

---

## 作者：墨凝而止 (赞：0)

已知（4k+2）者（k∈N\*)不可表示为二数平方差。此公式大有益处。

```delphi
var
n,a,b,i:longint;
function pd(k:longint):boolean;
begin
   if (k-2) mod 4=0 then exit(false) else exit(true);
end;
begin
  readln(a,b);
  for i:=a to b do if pd(i) then inc(n);
  write(n);
end.
```

---

## 作者：courage (赞：0)

很容易证明，除了形如4k+2的数，其他数都能表示为整数平方差。

由于n2-n1<=10000000，所以完全可以用穷举法判断，从而降低了代码复杂度。可以用位运算加速

```cpp

#include<cstdio>
int l,r,ans=0;
inline int abs(int x){
    return (x>0?x:-x);
}
int main(){
    scanf("%d%d",&l,&r);
    for (int i=l;i<=r;i++)
        if ((abs(i)&3)!=2) ans++;
    printf("%d",ans);
}

```

---

