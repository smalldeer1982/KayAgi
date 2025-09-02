# [ARC017A] 素数、コンテスト、素数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc017/tasks/arc017_1

アルゴリズムとコンテストが大好きな俺は、AtCoder Regular Contest(ARC) にも毎回欠かさずに参加していた。  
 しかしある時のこと、大学で怪しげな連中に突然「あなたは素数の光を信じますか？」と話しかけられてから様子がおかしい。  
 俺は数学がそこまでできるわけではないが、素数ぐらいは知っている。$ 1 $ とその数自身でしか割り切れない正の整数のことだ。  
 ただし $ 1 $ が素数じゃないってことだって知ってる。でも素数の光っていうのは何だかよく分からなかった。  
 奴らの話を聞いてからなんだか変だ。頭の中にはいつだって片隅に素数がいるし、素数を見るとなぜかたまらなく嬉しくなるようになった。  
 これまで毎回欠かさず参加していた ARC も、素数回のときでないと、なんだかうまくいかない気がして見送ってしまう。  
 そういえば、今もちょうど ARC が始まったところらしい。今回の ARC には、俺は無事に出られるのだろうか。

入力は以下の形式で標準入力から与えられる。

> $ N $

- $ N\ (17\ \leq\ N\ \leq\ 1,000,000) $ は、ARC が何回目の開催であるかを表す整数である。
 
 ARC$ N $ に出場できるとき、すなわち $ N $ が素数のときは `YES`、そうでないときは `NO` と一行に出力せよ。 ```
<pre class="prettyprint linenums">
17
```

 ```
<pre class="prettyprint linenums">
YES
```

 今回の ARC017 は、$ 17 $ が素数である($ 2 $ から $ 16 $ までのいずれの整数でも割り切れない)ため参加することができる。 ```
<pre class="prettyprint linenums">
18
```

 ```
<pre class="prettyprint linenums">
NO
```

 次回の ARC018 は、$ 18 $ がたとえば $ 2 $ や $ 3 $ で割り切れるため参加することができない。 ```
<pre class="prettyprint linenums">
999983
```

 ```
<pre class="prettyprint linenums">
YES
```

 ARC999983 はいつ頃開催されることになるのでしょうか。 ```
<pre class="prettyprint linenums">
672263
```

 ```
<pre class="prettyprint linenums">
NO
```

 $ 672263 $ は $ 1 $ とそれ自身以外に、$ 547 $ と $ 1229 $ で割り切ることができる。

# 题解

## 作者：MIN__2500 (赞：45)

加个bool函数即可

代码如下
```
#include<bits/stdc++.h>
using namespace std;
bool  iszhishu(int a)
{
    for(int i=2;i*i<=a;i++)//如果一个数是合数，那它就会有一个大的乘数和一个小的乘数。那6举例1,2,3,6。1,6除外2,3只需判断i*i是否小于a就行了
    {
        if(a%i==0)//如果a%i=0，说明是质数就返回0
            return 0;
    }
    return 1;
}
int main()
{
   int n;
    cin>>n;
    if(iszhishu(n)==1)//把甩到bool函数里，如果返回1
    cout<<"YES"<<endl;//执行1，别忘了endl
    else
    cout<<"NO"<<endl;//执行0，别忘了endl否则wa
    return 0;
}
```
留下一个赞，AC一整天

---

## 作者：presucc (赞：10)

	#include<cstdio>
  
	#include<cmath>
  
	bool prime(int n)

{

	if (n==1) return false;
	for (int i=2;i<=sqrt(n);i++)
		if (n%i==0) return false;
	return true;
}

	int main()

{
	
		int p;
		scanf("%d",&p);
		if (prime(p)) printf("YES\n");
		else printf("NO\n");
		return 0;
}

先附个代码，表达我心里的痛楚……

试了3次才知道：所有岛国题都是要末尾回车的！！

这就是我AT2203这道简单题做了N次都没做对的原因！！

我这位蒟蒻在此提醒大家：要养成输出回车的好习惯！！

咳咳，回到正题，这里用的是一种比较朴素的判断素数的方法。

实际上，蒟蒻掌握判断素数分方法应该有以下五种：

方法一：枚举（普通法）

时间复杂度：O(n)

每个数都求出它的因数个数，当它等于2时便是素数，不等于2时便不是素数，小学生常用方法，只能给30分~

附代码：

	bool prime(int n)

	{
		int num=0;
		for (int i=1;i<=n;i++)
		if (n%i==0)
			num++;
		if (num==2) return true;
		else return false;
	}

小学生的方法不会好到哪去的，下面要出场的是中学生的办法：

方法二：枚举（精英法）
时间复杂度：O(sqrt(n))

还是枚举，但是枚举到n的平方根就够了，这应该是大多数编程者第一次遇到的方法，60分~

附代码：

	bool prime(int n)
    
	{
		int judge=0;
		for (int i=2;i<=sqrt(n);i++)
			if (n%i==0)
				return false;
		return true;
	}
注：sqrt要用头文件#include<cmath>

中学生的方法虽然好了，但是还有更优的方法——高中法，同时也带来了一种想法——剪枝。

方法三：枚举（集训法）

时间复杂度：O(sqrt(n)/2)

又是枚举，但是在方法二的基础上少了一些东西：除了2，剩下的质数全是奇数，那么……（后面的你懂的~）给80分吧~

附代码：

	bool prime(int n)

{

		int judge=0;
		if (n%2==0) return false;
		else
		{
			for (int i=3;i<=sqrt(n);i+=2)
				if (n%i==0)
					return false;
		}
		return true;
}

注：sqrt要用头文件#include<cmath>

好了，在第四种方法出来前，你有两种选择：一是想着：“前三种方法够我用的了，装逼去~”那么恭喜你，回头是岸；二是想着：“这可不够，我还是要更努力，学习更多方法的呢！”那么同样恭喜你，前方等待你的是鲜花和汗水~

第四种方法也是剪枝，不过是大学生用的方法。

方法四：枚举（尊想法）

时间复杂度：O(sqrt(n)/6)

咳咳，首先得讲一下素数的出现规律：（大黑板来也~）

证明：大于等于5的质数一定和6的倍数相邻。

证明过程：证明：令x≥1，将大于等于5的自然数表示如下：····· 6x-1，6x，6x+1，6x+2，6x+3，6x+4，6x+5，6(x+1），6(x+1)+1 ······可以看到，不在6的倍数两侧，即6x两侧的数为6x+2，6x+3，6x+4，由于2(3x+1)，3(2x+1)，2(3x+2)，所以它们一定不是素数，再除去6x本身，显然，素数要出现只可能出现在6x的相邻两侧。

好了，大家应该都想到了吧~将刚开始的“i++”跨度为1的变化变为“i+=6”跨度为6的变化，速度当然也快了许多~ 能有100分~

附代码：


	bool prime(int n)

{

		if (n==1) return false；
    	if(n==2||n==3)
    	    return true;
    	if(n%6!=1&&n%6!=5)
    	    return false ;
    	int tmp=sqrt(n); 
    	for(int i=5;i<=tmp;i+=6)
    	    if(n%i==0||n%(i+2)==0)
    	        return false;
    	return true;
}

最后一种方法，大佬公用方法——筛法

时间复杂度：O(n)

看到这里，你大概会骂我了：作者的数学辣么差，连n>sqrt(n)/6都不知道？？

好了，我解释解释：这里的n意思是一起判断n个数所需的时间，也就是说，如果要和上面格式相同，那么这个的时间复杂度应该是无限接近于O(1)

为了不误导部分小学生们，还是改改吧~


   时间复杂度：O(1)

看，多快！！ 120分！！

算法解析：

Step1：把2-n的自然数放入a[2]到a[n]中（所放入的数与下标号相同）；

Step2：在数组元素中，以下标为序，按顺序找到未曾找过的最小素数minp和他的位置p（即下标号）；

Step3：从p+1开始，把凡是能被minp整除的各元素值从a数组中删去（筛掉），也就是给该元素值置0；

Step4：让p=p+1，重复执行step2，step3，知道minp>floor(sqrt(n))为止；
Step5：打印输出a数组中留下来、未被筛掉的各元素值。

如图：（以n==100为例）

①2 3 4 5 6 7 8 9 10 11 12 13 14 15 …… 98 99 100//初始化

②2 3  5  7  9  11  13  15 ……  99 //筛去被2整除的数；

③2 3 5  7    11  13   ……   //筛去被3整除的数；

………………………………………………

n次后……

n  2 3 5 7 11 13 17 ……//全剩素数了

（emmm...可怜的1从方法一到方法五都是被和谐的~~嘻嘻）

附代码：（给出完整代码哟~）

	#include <iostream>
	#include<cmath>
	#include<iomanip>
	#include<cstring>
	using namespace std;
	int n;
	bool a[100005];
	int main()
	{
		memset(a,true,sizeof(a));
		a[1]=false;
		cin>>n;
		for (int i=2;i<=sqrt(n);i++)
		{
			if (a[i])
			{
				for (int j=2;j<=n/i;j++)
				a[i*j]=false;
			}
		}
		for (int i=2;i<=n;++i)
		{
			if (a[i])
			cout<<i<<’ ’;
		}
		return 0;
	}
给了辣么多方法，不一定什么情况都要用筛法，按实际情况来定。因为如果判断素数只是一个复杂程序里面的一个小分支的话，那么方法二也能满足你了~越往下，编程复杂度越高，所以要看情况而行~（排除那些在他看来所有方法编程复杂度为O(1）的大佬）

最后，附每种方法的测试范围：

方法一：n>26500时，time超过1000ms;

方法二：n>1650000时，time超过1000ms;

方法三：n>2600000时，time 超过1000ms;

方法四：n>7200000时，time 超过1000ms;

方法五：n>35000000时，time超过1000ms;

但是方法五有个致命的缺陷：随着n的变大，a数组的下标也越来越大，最终有可能爆零~

所以，方法五的优化方法就留给你们去思考啦~（其实很简单的哦~）

开头那个才是本题的正解哟~

---

## 作者：Nartsam (赞：5)

### ~~这题简直可以当MillerRabin判素法的模板题~~

代码里有注释，这里就不多解释了
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
using namespace std;
typedef long long ll;
//在long long范围内只需试验前10个素数就可以
const int pri[10]={2,3,5,7,11,13,17,19,23,29};
//快速幂，如果数据范围会爆long long的话要用快速乘，本题不需要
ll qPow(ll a,ll b,ll p){
	ll res=1;
	while(b){
		if(b&1) res=res*a%p;
		a=a*a%p; b>>=1;
	}
	return res%p;
}
//二次探查，试探一次的错误率为1/2，k次的错误率为1/2^k
bool detective(ll a,ll n){
	int r=0; ll d=n-1;
	while((d&1)==0) d>>=1,++r;
	for(ll x=qPow(a,d,n),y;r;--r){
		y=x*x%n;
		if(y==1){
			if(x==1) return 1;
			if(x==n-1) return 1;
			return 0;
		}
		x=y;
	}
	return 0;
}
//算法主体
bool MillerRabin(ll x){
	if(x==1) return 0;
	for(int i=0;i<10;++i){
		if(x==pri[i]) return 1;
		if(x%pri[i]==0) return 0;
		if(!detective(pri[i],x)) return 0;
	}
	return 1;
}
int main(){
	int n; scanf("%d",&n);
	if(MillerRabin(n)){
		puts("YES");
	}
	else{
		puts("NO");
	}
	return 0;
}
```

---

## 作者：MortimerHaydn (赞：2)

#### 题面要求判断n是不是素数，是的输出YES，不要打反了。开始解这道题前先给大家介绍一个叫**埃拉托斯特尼筛选法**的算法。是一种简单检定素数的算法。  
#### 模拟一下它筛素数的方法：
### 假如我有一组像2~10这样的数列：
### 2 3 4 5 6 7 8 9 10
### 找出数列中第一个素数，也就是2。再在后面的数列中划掉2的倍数。就变成这样：
### 2 3  _~~4~~_ 5 _~~6~~_ 7 _~~8~~_ 9 _~~10~~_ 剩下：
### 2 3 5 7 9
### 如果现在这个数列中最大数小于第一个素数的平方，那么剩下的数列中所有的数都是素数，否则就再找出第二个素数。显然9大于2的平方
### 找出第二个素数，就是3.再在后面的数列中划掉3的倍数。就剩下了：
### 2 3 5 7
### 再划掉5的倍数。因为没有5的倍数了（除了5）,7小于5的平方，所以数列2~10里有素数：2 3 5 7 。
#### 代码：
```cpp
bool he[1000005]={0};//判断是否是素数（质数）
void Eratosthemes(int n){//埃拉托斯特尼筛选法（简称埃氏筛）
	for(int i=2;i<=n;i++){//因为1既不是素数，也不是合数
		if(he[i]){//i已经有两个以上的因数了
			continue; 
		} 
		for(int j=2;j*i<=n;j++){//查找i，j的积，一定是合数 
			he[i*j]=1;//因为我们查找的是i，j的积，所以i*j是合数 
		}
	} 
}//he数组就是是否是素数
```
这就是一道版题，AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool he[1000005]={0};//判断是否是素数（质数）
void Eratosthemes(int n){//埃拉托斯特尼筛选法（简称埃氏筛）
	for(int i=2;i<=n;i++){//因为1既不是素数，也不是合数
		if(he[i]){//i已经有两个以上的因数了
			continue; 
		} 
		for(int j=2;j*i<=n;j++){//查找i，j的积，一定是合数 
			he[i*j]=1;//因为我们查找的是i，j的积，所以i*j是合数 
		}
	} 
}//he数组就是是否是素数 
int n; 
int main(){
	scanf("%d",&n);
	Eratosthemes(n);
	if(!he[n]){//如果n是素数 
		printf("YES\n");//换行，如果你想AC的话 
	}
	else{
		printf("NO\n");//一定要换行 
	}
	return 0;
} 
```


---

## 作者：真·峭岩仙道 (赞：2)

本蒟蒻看到题解区dalao们代码都好长啊。。。

不废话，先上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n;
    cin>>n;
    bool x=true;
    for(long long i=2;i<n;i++){
        if(n%i==0){
        x=false;
        break;
    }
    }
    if(x) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}
```
大概描述一下思路：把从2开始的所有数枚举一遍，看是不是能整除。

怎么实现呢：只要定义一个bool函数，如果能整除，直接结束就可以了。

# 一定要换行啊！！！不换只会WA啊！！！

---

## 作者：梦里调音 (赞：2)

我只想告诉你们：
## 不换行就等着WA吧！！！

**思路**：
从2开始枚举，直到根号n。

为什么不用枚举到n呢？

回答：两个数相乘为n，一个小于根号n，另一个必然大于根号n。

所以，根号n到n的部分就不需要啦，在前面枚举过了。

代码：

```cpp
#include <iostream>
using namespace std;;
int main(){
	long long int i,j,k,m,n;
	cin>>n;
	for(i=2;i*i<=n;i++)if(n%i==0){
		cout<<"NO\n";//不是质数就直接输出白白
		return 0;
	}
	cout<<"YES\n";//是质数才可以走过循环
	return 0;
}
```


---

## 作者：Cinderella (赞：2)

本蒟蒻又来发题解啦！

话不多说，进入正题。

这题让我们做的东东其实是十分简单的，就是——判断一个数n是否为质数（也叫素数）。

我滴思路和各位dalao都是一模一样的呢，只是我想优化一下，就是for循环的终值用sqrt(n){n的开方}。

直接献上代码↓
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>

using namespace std;
long long n,p=1;
int main()
{
 scanf("%I64d",&n);
  for(int i=2;i<=sqrt(n);i++)//用sqrt(n)会更节省时间哦！
 {
    if(n%i==0) 
    {
      p=0;
      break;
    }
 }
 if(p==1) cout<<"YES";
 else cout<<"NO";
 return 0;
}

```

最后，还想提醒大家两点：

### 1.看清“YES”和“NO”的写法！不要写成“Yes”和“No”！

### 2.记得换行！

｛本人就是因为以上两点悲催滴错了3次！}

好啦，以上就是AT807 【素数、コンテスト、素数】的题解，如有不足，请各位dalao在右边→评论区指出！

~~悄悄滴留下个赞吧！~~

---

## 作者：不到前10不改名 (赞：2)

我又来水at了！。。。
线筛（真正的大佬可以做的真正线筛）
还有很多素数判断但不稳定也用不着就不讲了
其实i*i比sqrt快。。。（逃）
```
#include<stdio.h>
int a[10000001];
int main()
{
    int n,i,j,t;
    a[1]=1;
    scanf("%d",&n);
    for(i=2;i<=n;i++)
    {if(a[i]==0)
    for(j=i*2;j<=n;j+=i)
    if(a[j]==0)
    {a[j]=1;}}
    if(a[n]==0)
    printf("YES\n");//大写加回车。。。
    else
    printf("NO\n");
    return 0;
}
```

---

## 作者：meyi (赞：1)

**一道水题，但是本蒟蒻用了miller_rabin算法（小题大做，果然还是我太蒻了），详细说明可见洛谷日报#98，这里只在代码中简单介绍。**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll rand(ll n){
	//返回[0,n]的随机数
    return (double)rand()/RAND_MAX*n+0.5;
}
inline ll qmul(ll a, ll b, ll mod){
	//快速计算(a+b)%mod
    ll res=0;
    while(b){
        if(b&1){
            --b;
            res=(res+a)%mod;
        }
        b>>=1;
        a=(a<<1)%mod;
    }
    return res;
}
inline ll qpow(ll a,ll b,ll mod){
	//快速计算(a^b)%mod
    ll res=1;
    while(b){
        if(b&1)res=qmul(res,a,mod);
        b>>=1;
        a=qmul(a,a,mod);
    }
    return res;
}
inline bool judge(ll a,ll n){
/*
    miller_rabin算法的精华，运用了拆分思想，
    具体见洛谷日报#98
*/
    ll tem=n-1;
    register int j=0;
    while(!(tem&1)){
        tem>>=1;
        j++;
    }
    ll x=qpow(a,tem,n);
    if(x==1||x+1==n) return true;
    while(j--){
        x=qmul(x,x,n);
        if(x+1==n)return true;
    }
    return false;
}
inline bool miller_rabin(ll n){
	//检查n是否为素数
    if(n==2)return true;
    if(n<2||n%2==0)return false;
    for(register int i=1;i<21;++i){
        ll a=rand(n-2)+1;
        if(!judge(a,n))return false;
    }
    return true;
}
int n;
main(){
	//按照题意模拟
	scanf("%d",&n);
	puts(miller_rabin(n)?"YES":"NO");
}
```

---

## 作者：do_not_use_sort (赞：1)

给大家来讲解一下这一道题嗯
首先嘛这一道题是可以在我们刚刚学完FOR循环时做的一个题
这个题目要求我们判断素数嘛
素数就是质数质数的因数<=2
是就printf("YES")
否则是NO
上代码
```cpp
#include<stdio.h>
int main()
{
    int i,j,k;
    scanf("%d",&i);
    for(j=1;j<=i;j++)
    {
        if(i%j==0)
        {
          k++;  
        }
    }
    if(k<=2)
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    return 0;
}
```

---

## 作者：lsyx0918 (赞：0)

总而言之，统而言之，这道题只是一道判断素数题罢了。我用函数解答的，当然也可以用别的方法。这里只用函数来求了

二话不说，发代码喽！！！：
```cpp
#include<iostream>//头文件，尽量别用万能头
using namespace std;
int isprime(long long n) //个人喜欢在后面写函数，先声明一下
int main()//主函数 
{
    long long n; //定义变量 
    cin>>n;
    //判断素数
    if(isprime(n)) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;//结束
}
int isprime(long long n) //判断素数函数
{
    if(n<2) return 0;//1和0不能参与判断素数函数内，先来个了断
    //现在开始正式判断函数！！
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0) return 0;
    }
    return 1;
}
```
现在，声明一条重要启示：

**AT不换行，暴零两行泪！**

---

## 作者：bym666 (赞：0)

# AT807 【素数、コンテスト、素数】
这道题实在是太水，不负入门之名，就是一个判断素数而已（不过为什么要用日语）。详细注释请看代码↓↓↓

代码如下：
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
bool prime(int x)//判断是否为素数
{
	int i;
	for(i=2;i*i<=x;i++)
	{
		if(x%i==0) return 0;//如果整除则不是
	}
	if(x<2) return 0;//如果是0或1则不是
	return 1;//剩下的都是
}
int main()
{
    int n;
    cin>>n;//输入
    if (prime(n)) cout<<"YES"<<endl;//如果是输出"YES"
    else cout<<"NO"<<endl;//不是输出"NO"
    return 0;//结束程序
}
```
注：日语题所有输出记得加换行，否则就会全WA。

---

## 作者：hucy2021 (赞：0)

判断一个数是否为素数有很多方法，这里我介绍几种比较简单的
### 1.简单版
根据定义，素数n除1和它本身以外没有其他约数，那么**枚举1到n-1判断是否整除**即可,时间复杂度O（n）
```
bool isPrime_2( int num )
{
     for(int i= 2;i <=num-1; i++)//枚举
        if(num %i== 0)
          return 0 ;
     return 1 ;
}

```
但是这个代码明显效率极低，于是我们在这段代码基础上，又寻找出另一种方法
### 2.改进版
之前我们枚举了从1到n-1之间的所有的数，效率极低，那么我们不可以减少循环次数从而提高效率呢 

其实我们只需要 **枚举到sqrt（n）即可**，假如一个数是合数，那么将它因式分解后得到的约数必定一个大于sqrt（n）一个小于sqrt（n），所以如果在1到sqrt（n）这一部分中没有约数，大于sqrt（n）的部分必然没有约数

改进代码如下
```
bool isPrime_2( int num )
{
     for(int i= 2;i <=sqrt（num）; i++)
    //调用sqrt()要添加头文件#include<cmath>,如果不想加可以写成i*i<=n;
        if(num %i== 0)
          return 0 ;
     return 1 ;
}

```
这样时间复杂度就是O(sqrt(n))，要快得多了，不过这里还有一种更快的方法（从大佬那里学来的）
### 3.利用素数分布规律
素数分布规律是这样子：**大于等于5的质数一定和6的倍数相邻**

>证明：当x≥1时，将大于等于5的自然数表示如下：6x-1，6x，6x+1，6x+2，6x+3，6x+4，6x+5，6(x+1），6(x+1)+1 等
显然，不在6的倍数（6x）两侧的数，6x+2，6x+3，6x+4，由于它们可以分解成2(3x+1)，3(2x+1)，2(3x+2)，所以它们一定不是素数，再除去6x本身，显然，素数只可能在6x的相邻两侧。


```
#include<iostream>
#include<cmath>
using namespace std;
bool isPrime( int num )
{
    if(num ==2|| num==3 )
        return 1 ; //比5小的素数特判
    if(num %6!= 1&&num %6!= 5)
    	return 0 ;//在6两侧不是
    for(int i= 5;i <=num; i+=6 )
        if(num %i== 0||num %(i+ 2)==0 )
            return 0 ;//在6的倍数两侧不是
    return 1 ;
}
int main(){
	int m;
	cin>>m;
	if(isPrime(m)) cout<<"YES"<<endl;//调用即可
	else cout<<"NO"<<endl;
	return 0;
} 
```
**End**

---

## 作者：唐一文 (赞：0)

### 思路：从2开始枚举，直到根号n。

Q：为什么不用枚举到n呢？

A：两个数相乘为n，一个小于根号n，另一个必然大于根号n，所以，根号n到n的部分在前面就相当于枚举过了。

**精髓**：
```cpp
if(n<2){  //特判
    cout<<"NO"<<endl;
    return 0;  //结束程序
}
for(i=2;i<=sqrt(n);i++){
    if(!(n%i)){  //如果在2到sqrt(n)中有个数能整除n
        cout<<"NO";
        return 0;  //结束程序
    }
}
cout<<"YES";
```

---

## 作者：zzhz (赞：0)

## ~~又找到了一道AT的水题~~   
这题不难，话不多说，直接上代码     
代码如下：    
```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
int main(){
    int n,i,s=0;
    cin>>n;//输入
    if(n<2) {cout<<"NO"<<endl;return 0;}//小于2的都不是质数
    for(i=2;i<=n-1;i++)
        {if(n%i!=0) s++;//质数的因数
        }       
    if(s==n-2) cout<<"YES"<<endl;//判定是否为质数
    else cout<<"NO"<<endl;
    return 0;//结束了
}
```
最后提醒一点：    
AT的题一定要换行！   
本蒟蒻心地善良   
但是，    
非紧急情况不要用此功能！ 

---

## 作者：丁丁の丁丁 (赞：0)

# 首先，声明一下这是进口题（日本出产）输出要换行。
## coding
~~~~
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
	long long n,m,i,s=0;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		if(n%i==0) s++;//判断有多少个因数 
	}
	if(s==2) cout<<"YES"<<endl;//有两个就是质数
	else cout<<"NO"<<endl;//否则就是合数
	return 0;//最后结束
}
~~~~
### 欧耶，押韵。

---

## 作者：Catreap (赞：0)

判断质数就行了

我提供一个比较快(加了优化)的判断质数方法

一个判断质数方法的证明：

令x≥1，将大于等于5的自然数表示如下：
······${{6x-1}}$ ，${{6x}}$，${{6x+1}}$，${{6x+2}}$，${{6x+3}}$，${{6x+4}}$，${{6x+5}}$，${{6(x+1)}}$，${{6(x+1)+1}}$ ······
可以看到，不在6的倍数两侧，即6x两侧的数为${{6x+2}}$，${{6x+3}}$，${{6x+4}}$，由于${{2(3x+1)}}$，${{3(2x+1)}}$，${{2(3x+2)}}$，所以它们一定不是素数，再除去${{6x}}$本身，显然，素数要出现只可能出现在6x的相邻两侧。这里要注意的一点是，在6的倍数相邻两侧并不是一定就是质数。

此时判断质数可以6个为单元快进，循环中只需要考虑${{6i-1}}$和${{6i+1}}$的情况，即循环的步长可以定为6，每次判断循环变量${{k}}$和${{k+2}}$的情况即可。

```cpp
bool Prime(ll num) {//判断质数函数 最好开long long
    if(num==0 || num==1) return 0;//0,1特殊判断
    if(num==2 || num==3) return 1;//2,3打表判断
    if(num%6!=1 && num%6!=5) return 0;
    ll tmp=sqrt(num);//开方
    for(ll i=5; i<=tmp; i+=6) {//6个为单元快进
        if(num%i==0 || num%(i+2)==0) return 0;
    }//考虑6i-1和6i+1的情况
    return 1;//质数！QwQ
}
```

最后附上~~高清无码~~代码(不要吐槽，我个人比较喜欢$fread$)

## Code
```cpp
#include<cstdio>
#include<cmath>
#define ll long long
#define SIZE 100000
bool Error=0;
inline char nc() {
#ifdef WIN32
    return getchar();
#endif
    static char buf[SIZE],*p1=buf+SIZE,*pend=buf+SIZE;
    if (p1==pend) {
        p1=buf,pend=buf+fread(buf,1,SIZE,stdin);
        if (pend==p1) {
            Error=1;
            return -1;
        }
    }
    return *p1++;
}
inline void read(ll &x) {
    bool sign=0;
    char ch=nc();
    x=0;
    for (; ch==' '||ch=='\n'||ch=='\r'||ch=='\t'; ch=nc());
    if (Error)return;
    if (ch=='-')sign=1,ch=nc();
    for (; ch>='0'&&ch<='9'; ch=nc())x=x*10+ch-'0';
    if (sign)x=-x;
}
bool Prime(ll num) {
    if(num==0 || num==1) return 0;
    if(num==2 || num==3) return 1;
    if(num%6!=1 && num%6!=5) return 0;
    ll tmp=sqrt(num);
    for(ll i=5; i<=tmp; i+=6) {
        if(num%i==0 || num%(i+2)==0) return 0;
    }
    return 1;
}
int main(int argc,char *argv[]) {
    ll BigNum;
    read(BigNum);
    return Prime(BigNum)?
	printf("YES\n")&0:printf("NO\n")&0;
}
```

---

## 作者：快乐的坤 (赞：0)

    var n,i:int64;//舍得打点更好。
        x:boolean;//定布尔行以便判断。
    begin
      x:=true;//一定要先赋值。
      readln(n);//输入不多说。
      for i:=2 to n-1 do//for循环，千万别to n，不然你WA定了（每个数一定是自己的倍（因）数）。
        begin//其实没必要加小begin、end，但这样更好看，能养成好习惯。
          if n mod i=0 then//来判断了。
            x:=false;//如果不是质数就直接给他弄错误。
        end;
      if x=true then//如果是对就代表他除了1和自己以外没有因数。
        writeln('YES')//那么他就是质数。
      else//如果他还有因数的话。
        writeln('NO');//那他就不是质数。
    end.

---

## 作者：xyn0901 (赞：0)

这题数据小，而且没有1，直接用筛法~~(accode的题就是水）~~

```pascal
var n,i:longint;
begin
readln(n);
for i:=2 to trunc(sqrt(n)) do
if n mod i=0 then begin writeln('NO'); halt; end;
writeln('YES');
end.
```

---

## 作者：废物yehan (赞：0)

由于一道水题，我们可以采用先找出所有素数的方法来做，采用埃式筛就行。
	不说废话了 上代码。
    ```cpp
#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include<algorithm>
#include<string.h>
using namespace std;
bool ai[1000005]; 
int main()
{
	long long n;
    
	cin>>n;
    
	memset(ai,1,sizeof(ai)); 
    
	for(int i=2;i<=1000005;i++)
    
	{
    
		if(ai[i])
        
		{
        
			for(int j=i*2;j<=1000005;j=j+i)
            
			{
            
				ai[j]=0;
                
			}
            
		}
        
	}
    
	if(ai[n])
    
	{
    
		cout<<"YES"<<endl;    
	}
    
    
	else
    
	{
    
		cout<<"NO"<<endl;
        
	} 
    
	return 0;
    
}


```

---

## 作者：PC_DOS (赞：0)

这是一道模拟题，由于数据量不大，我们只需要借助穷举法，枚举从2到sqrt(N)之间的每一个数并判断是不是N的因数即可。如果发现一个因数，返回false，否则返回true。

代码:
```
#include <iostream>
#include <cmath>
using namespace std; //头文件和命名空间
inline bool IsPrime(long long iNum){ //穷举法判断素数的函数
	register long long i;
	if (iNum <= 1)
		return false;
	for (i = 2; i <= sqrt(iNum); ++i){
		if (iNum%i == 0)
			return false;
	}
	return true;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int iNum; //数字
	while (cin >> iNum){ //读入数字
		if (IsPrime(iNum)) //判断是不是素数并输出
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0; //结束
}
```

---

## 作者：char32_t (赞：0)

# 题解 AT807 【素数、コンテスト、素数】
------------
**牛刀杀鸡系列**

这道题也可以用线性筛素数解决...

$code:$
```cpp
#include<cstdio>
#include<cstring>
#define _max 1000000//因为范围为17<=n<=1000000 所以最大值设为1000000
bool prime[_max];//质数表 
int primes[_max];
int num_prime=0;
void make_prime() {//线性筛素数
    memset(prime, true, sizeof(prime));
    prime[0]=prime[1]=false;
    for(int i=2; i<=_max; i++) {
        if(prime[i]) primes[num_prime++]=i;
        for(int j=0; j<num_prime&&i*primes[j]<_max; j++) {
            prime[i*primes[j]]=false;
            if(!(i%primes[j])) break;
        }
    }
    return;
}
int main(){
    make_prime();//打出质数表
    int n;
    scanf("%d", &n);//读入n
    if(prime[n]==true) printf("YES\n");//判断并输出 
    else printf("NO\n");
    return 0;
}
```

---

