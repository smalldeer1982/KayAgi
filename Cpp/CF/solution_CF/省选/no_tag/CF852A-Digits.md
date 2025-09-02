# Digits

## 题目描述

John gave Jack a very hard problem. He wrote a very big positive integer $ A_{0} $ on a piece of paper. The number is less than $ 10^{200000} $ . In each step, Jack is allowed to put $ '+' $ signs in between some of the digits (maybe none) of the current number and calculate the sum of the expression. He can perform the same procedure on that sum and so on. The resulting sums can be labeled respectively by $ A_{1} $ , $ A_{2} $ etc. His task is to get to a single digit number.

The problem is that there is not much blank space on the paper. There are only three lines of space, so he can't perform more than three steps. Since he wants to fill up the paper completely, he will perform exactly three steps.

Jack must not add leading zeros to intermediate results, but he can put $ '+' $ signs in front of digit $ 0 $ . For example, if the current number is $ 1000100 $ , $ 10+001+00 $ is a valid step, resulting in number $ 11 $ .

## 说明/提示

In the first sample, Jack can't put $ '+' $ signs anywhere, so he just writes $ 1 $ in each line and solves the problem. Here, solution is unique.

In the second sample, Jack first puts $ '+' $ between every two consecutive digits, thus getting the result $ 5+8+0+6=19 $ . He does the same on the second step, getting $ 1+9=10 $ . Once more, he gets $ 1+0=1 $ , so after three steps, the result is $ 1 $ and his solution is correct.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
1
1
1
```

## 样例 #2

### 输入

```
4
5806
```

### 输出

```
5+8+0+6
1+9
1+0
```

# 题解

## 作者：yijan (赞：7)

Orz @Wen_kr 讲的一道有趣的（大雾）思维题

#### 题目大意：给定一个长度为 $n$ 的很长的数，在一次操作可以在其中放若干个加号隔开它，希望使得三次操作后这个数字变成一个一位数，求任意一种操作方案

首先，虽然数据范围是$2\times 10^5$，但是对于**任意一个数**本题都是有解的。

看到这个题第一映像肯定就是：直接一位一位拆，肯定很小了，但是只要细想（~~询问一下wkr~~）就会发现是有特例的！ 例如数码和事$289$，直接拆成289，而289无论怎样想要拆成1肯定都需3步，一共四步，是错的。

换一种思路，如果直接随机处理呢？反正289这种情况是很少见的，为什么不能随机拆分，然后暴力判断一下呢？确实可以。这样可以A了这道题，但是下面只讨论正确做法。（并且懒得给~~码~~代码了~）

需要进行分类讨论：

下文假设原数是$A$，$f(A)$为$A$的数码和

### 1. 当$f(A)\leq 288$

第一重仍然是直接直接一位一位拆

通过暴力打表发现除了$f(A)\neq199$的情况直接拆炸了其他情况第二维直接拆完全没问题！并且显然当$f(A)=199$的时候可以拆成$1+99$，$1+00$

但是至于为什么是288呢？请看下面分析

### 2. 当$289\leq f(A)≤999$

令$A=a_0a_1a_2...a_n$

我们假设

$X=a_0a_1+a_2a_3+...+a_{n-1}a_n$（若$n$不为偶数情况类似，不多写了）  
$Y=a_0+a_1a_2+a_3a_4+...+a_{n-2}a_{n-1}+a_n$

也就是说$X$是$A$从头开始两位两位拆的，$Y$是$A$从第二位开始两个两个拆的，于是有

$X+Y=11f(A)-9a_n$

由于显然$f(A)>9\times 9 = 81 ≥ 9a_n$ ， 有$X+Y>10f(A)$ 

假设$X$是其中较大的一个（哪一个大本质相同），

有$X>5f(A)$（显然的放缩）

由于$f(A)>288$，$5f(A)>1000$是肯定的了

为什么我们要煞费苦心让$X>1000$呢，假设构造一个序列

$s_0=a_0+a_1+...+a_n=f(A)$

$s_1=a_0a_1+a_2+a_3+...+a_n$

$s_2=a_0a_1+a_2a_3+a_4+a_5+...+a_n$

$...$

$s_{n/2}=a_0a_1+...+a_{n-1}a_{n}=X$

（这里是我们默认了$X>Y$假设$Y>X$那么只需要更改拆分方式）

$s$ 这个序列有什么性质呢？

1. $s$ 单调递增（显然）
2. $s$ 每一次增加量不会超过$81$ （ $a_i\times 9$ 也不到81）
3. $s$ 在递增过程中**一定会产生一次进位**，因为$f(A)\leq 999$而$X>1000$

假设 $s_p<1000,s_{p+1}>1000$ 有性质2 有$s_{p+1}\leq 1080$

而显然$1000\leq x\leq 1080$的数字都是可以两次拆分结束的。

那么我们可以先计算$X,Y$然后通过提到的方法得到一种拆分方式使得可以在三次拆分后结束。

看起来这还是一种极其特殊的情况，但是考虑为什么这个方法可行，本质上就是构造出了一次**进位**，并且进位后得到的那个值一定可以被两步拆出来。那么既然三位数可行，为什么更高位数不可可以用类似思路呢？

### 3. $1000\leq f(A) $

同样的，考虑构造出形如$1000…000ab$的形式。

然而这次通过两位两位拆是没法进位了，那么考虑三位三位拆

类似的，构造

$X=a_0a_1a_2 + a_3a_4a_5 + ...a_{n-2}a_{n-1}a_n$

$Y=a_0+a_1a_2a_3 + a_4a_5a_6 + ...+a_{n-4}a_{n-3}a_{n-2} + a_{n-1}a_n$

$Z=a_0+a_1+a_2a_3a_4 + a_5a_6a_7 + ...+a_{n-3}a_{n-2}a_{n-1} + a_n$

也就是从头开始拆，从第一个开始拆，第二个开始拆

同样假设$X>Y>Z$ 那么通过放缩这次有$X>30f(A)$

没错，显然这是一定会进位的！

接下来就是类似第二种情况的思路，构造 $s$ 序列

$s_0=a_0+a_1+...+a_n=f(A)$

$s_1=a_0a_1a_2+a_3+...+a_n$

$...$

$s_{n/3}=a_0a_1a_2+a_3a_4a_5+...+a_{n-2}a_{n-1}a_n$

同样假设在$s_{p}$的时候产生了一次进位，但是这一次性质就没有前面那么优秀了，每一次的增加量会达到999，没有达到预期的$1000...80$之内

首先形式化写出$s_{p-1}$

$s_{p-1}=a_0a_1a_2+...+a_ta_{t+1}a_{t+2}+a_{t+3}+a_{t+4}+...+a_n$

那么我们可以像第二种情况对于$a_{t+4}+...+a_n$进行另一种合并方式

$s_p'=a_0a_1a_2+...+a_ta_{t+1}a_{t+2}+(a_{t+3}a_{t+4}+a_{t+5})+a_{t+6}+...+a_n$

$....$

$s_n' = a_0a_1a_2+...+a_ta_{t+1}a_{t+2}+(a_{t+3}a_{t+4}+a_{t+5})+...+(a_{n-2}a_{n-1}+a_n)$

那么在这其中肯定会发生一次进位，为什么？

假设从$s_{p-1}$开始三个三个合并，序列至少会增加$X-s_{p-1}$由于$X>30f(A)$,$s_{p-1}<10f(A)$（还没进位）所以至少增加了$20f(A)$

但是按照这个枚举方法，之多增加了原来增加的$\frac{1}{11}$（这个可以手画一下很好推），就增加了至少$\frac{20}{11}f(A)$，一定可以进位！而现在的增加量再次变成了$81$，然后就做出来了。

------

由于全文均放缩了很多+yijan很懒，直接把第二个情况没讨论放进第三个情况写的（由于自己找不出反例），在cf上跑过去了。（如果有证明可以联系菜鸡yijan）所以这个又长又难看的code只是参考啦

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXN 200016
int A[MAXN] , n , p , f;
int tp[9];
int ni( int x ) {
    int res = 0;
    for( int i = 8 ; i > 0 ; -- i ) if( x / tp[i] )
        printf("%d+",(x/tp[i]) % 10) , res += ( x / tp[i] ) % 10;
    printf("%d\n",x%10) , res += x % 10;
    return res;
}
int main() {
    tp[0] = 1; for( int i = 1 ; i < 9 ; ++ i ) tp[i] = tp[i-1] * 10;
    cin >> n;
    for (int i = 1; i <= n; ++i) scanf("%1d", &A[i]) , f += A[i];
    if( f < 289 ) {
        for( int i = 1 ; i < n ; ++ i ) printf("%d+",A[i]);
        printf("%d\n",A[n]);
        if( f == 199 )
            puts("1+99") , puts("1+00");
        else
            ni( ni( f ) );
    } else {
        int X = 0 , Y = 0 , Z = 0 , mx;
        for( int i = 1 ; i <= n ; i += 3 )
            if( i + 2 <= n ) X += A[i] * 100 + A[i+1] * 10 + A[i+2];
            else
            { for( int t = n ; t >= i ; -- t ) X += A[t]; i = n; }
        for( int i = 2 ; i <= n ; i += 3 )
            if( i + 2 <= n ) Y += A[i] * 100 + A[i+1] * 10 + A[i+2];
            else
            { for( int t = n ; t >= i ; -- t ) Y += A[t]; i = n; }
        for( int i = 3 ; i <= n ; i += 3 )
            if( i + 2 <= n ) Z += A[i] * 100 + A[i+1] * 10 + A[i+2];
            else
            { for( int t = n ; t >= i ; -- t ) Z += A[t]; i = n; }
        mx = max( X , max( Y , Z ) );
        if( X == mx ) {
            int tmp = f , tt = (int)log10( f ) + 1 , i;
            for( i = 1 ; i <= n ; i += 3 )
                if( ( tmp + A[i]*99 + A[i+1]*9 ) / tp[tt] )
                    break;
                else { printf("%d%d%d+",A[i],A[i+1],A[i+2]) , tmp += A[i]*99 + A[i+1]*9; }
            for( ; i <= n ; i += 3 )
                if( ( tmp + A[i]*9 ) / tp[tt] )
                    break;
                else { printf("%d%d+%d+",A[i],A[i+1],A[i+2]) , tmp += A[i] * 9;}
            printf("%d%d+",A[i],A[i+1]);
            tmp += A[i] * 9;
            for( int j = i + 2 ; j < n ; ++ j ) printf("%d+",A[j]);
            printf("%d\n",A[n]);
            ni( ni( tmp ) );
        } else if( Y == mx ) {
            int tmp = f , tt = (int)log10( f ) + 1 , i;
            printf("%d+",A[1]);
            for( i = 2 ; i <= n ; i += 3 )
                if( ( tmp + A[i]*99 + A[i+1]*9 ) / tp[tt] )
                    break;
                else tmp += A[i]*99 + A[i+1]*9 , printf("%d%d%d+",A[i],A[i+1],A[i+2]);
            for( ; i <= n ; i += 3 )
                if( ( tmp + A[i]*9 ) / tp[tt] )
                    break;
                else tmp += A[i] * 9 , printf("%d%d+%d+",A[i],A[i+1],A[i+2]);
            tmp += A[i] * 9;
            printf("%d%d+",A[i],A[i+1]);
            for( int j = i + 2 ; j < n ; ++ j ) printf("%d+",A[j]);
            printf("%d\n",A[n]);
            ni( ni( tmp ) );
        } else if( Z == mx ) {
            int tmp = f , tt = (int)log10( f ) + 1 , i;
            printf("%d+%d+",A[1],A[2]);
            for( i = 3 ; i <= n ; i += 3 )
                if( ( tmp + A[i]*99 + A[i+1]*9 ) / tp[tt] )
                    break;
                else tmp += A[i]*99 + A[i+1]*9 , printf("%d%d%d+",A[i],A[i+1],A[i+2]);
            for( ; i <= n ; i += 3 )
                if( ( tmp + A[i]*9 ) / tp[tt] )
                    break;
                else tmp += A[i] * 9 , printf("%d%d+%d+",A[i],A[i+1],A[i+2]);
            tmp += A[i] * 9;
            printf("%d%d+",A[i],A[i+1]);
            for( int j = i + 2 ; j < n ; ++ j ) printf("%d+",A[j]);
            printf("%d\n",A[n]);
            ni( ni( tmp ) );
        }
    }
}
```





---

## 作者：xfrvq (赞：3)

考虑一个贪心，就是每次我只把数一位一位的拆，但这是假的。

比如 $11\cdots1$，共 $289$ 个 $1$。第一次拆成 $289$，第二次拆成 $19$，第三次拆成 $10$。

但是直觉告诉我们这样的数没多少。

于是我们考虑两种分配方法：一位一位拆和两位两位拆。

然后用随机化来控制两种方法的出现情况，合理调整比例就可以通过。

```cpp
#include<iostream>
#include<string>
#include<random>

using namespace std;

int main(){
	mt19937 rnd(1507);
	int 1507;
	cin >> 1507;
	string s;
	cin >> s;
	const int v = 10;
	for(;;){
		string t = s,t0,t1,t2;
		int a = 0,b = 0,c = 0;
		for(int i = 0;i < t.length();){
			if(i) t0 += '+';
			if(rnd() % v == 0 || i == t.length() - 1) a += t[i] - '0',t0 += t[i],++i;
			else a += (t[i] - '0') * 10 + (t[i + 1] - '0'),t0 += t[i],t0 += t[i + 1],i += 2;
		}
		t = to_string(a);
		for(int i = 0;i < t.length();){
			if(i) t1 += '+';
			if(rnd() % v == 0 || i == t.length() - 1) b += t[i] - '0',t1 += t[i],++i;
			else b += (t[i] - '0') * 10 + (t[i + 1] - '0'),t1 += t[i],t1 += t[i + 1],i += 2;
		}
		t = to_string(b);
		for(int i = 0;i < t.length();){
			if(i) t2 += '+';
			if(rnd() % v == 0 || i == t.length() - 1) c += t[i] - '0',t2 += t[i],++i;
			else c += (t[i] - '0') * 10 + (t[i + 1] - '0'),t2 += t[i],t2 += t[i + 1],i += 2;
		}
		if(c < 10){
			cout << t0 << endl << t1 << endl << t2 << endl;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：__LiChangChao__ (赞：1)

## 思路
第一眼看到这道题，有一个显然的贪心做法：将每一位之间都加上 `+` 号。

但想一想，很容易发现假了，比如：

```
99999999999999999999991
```

用这种贪心最终的输出结果为：

```
9+9+9+9+9+9+9+9+9+9+9+9+9+9+9+9+9+9+9+9+9+9+1
1+9+9
1+9
```

因为 $1+9=10$，所以这种贪心是不对的。

然而构造正解实在太难想，然而可以想一想用什么办法来解决这个问题？

上面的贪心的问题在于容易被构造位数和卡掉，那只要穿插几个两位数不就解决了吗？如何加入两位数？考虑**随机化**来控制。随机化的概率自己看着设就好了，我设置的是 $\frac{1}{20}$。

但是随机化也有可能因为运气不好而算出一个两位数，因此要在最后检查一下答案是否为一位数。

按照这个思路写出代码，再测试一下：

```
9+9+9+9+99+9+9+99+9+9+9+9+9+9+9+9+9+9+9+9+1
3+6+1
1+0
```

$1+0=1$，$1$ 是一位数，正确。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int pos;
inline int rand(int x,int y) {//（伪）随机数，生成一个x到y之间的（伪）随机数 
	if(x>y)y=x;
	return x==y?x:rand()%(y-x+1)+x;
}
string ss,s,s1,ans[10];
int sum,num=0,n;
inline void solve(){
	pos=5;//概率 
	int cnt=0;
	s=ss;
	for(int i=1; i<=3; i++) {
		s1="";
		sum=0;
		for(int i=0; i<s.length(); i++) {//随机化添加+号 
			s1+=s[i];
			if(rand(1,100)<=pos&&i<s.length()-2) {
				s1+=s[++i];
			}
			if(i!=s.length()-1)s1+='+';
		}
		num=0;
		for(int i=0; i<s1.length(); i++) {
			if(s1[i]=='+')sum+=num,num=0;//计算表达式 
			else num=num*10+(s1[i]-'0');
		}
		sum+=num;
		s="";
		while(sum) {
			s=(char)(sum%10+'0')+s;//数字转字符串 
			sum/=10;
		}
		ans[++cnt]=s1;
		pos=0;//除第一次处理外，其他的一位一位添加加号 
	}
} 
int main() {
	srand(114514);
	cin>>n>>ss;
	solve();
	while(s.length()!=1)solve();//检查答案正确性
	cout<<ans[1]<<"\n"<<ans[2]<<"\n"<<ans[3];
}

```

---

## 作者：o51gHaboTei1 (赞：1)

发现一个假的贪心：连续拆开每一位加在一起。

但是这样的贪心是很容易被卡掉的。

一个小优化是随机几位在第二次操作中变成十位数，但是概率还是不高，至少我是被卡住了的。。。

一个合理的想法是在每次拆位的时候将个位数与十位数的比例设为 $\frac{10}{1}$，这样的话个位数和十位数的和差不多是等大的，而会带来更多的随机情况，比较划算。

这个概率挺难算的，就不算了吧。

看到题解区有个老哥是把比例设为 $\frac{1}{10}$，感觉这样是错的，只是概率波动挺小的，但最后还是能跑过的。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5 , mod = 10;
int n,m;
mt19937 rnd(114514);
string s;
int main()
{
	scanf("%d",&n);
	cin >> s;
	while(1)
	{
		string m = s,s0,s1,s2;
		int sm = 0;
		int i = 0;
		while(i < m.size())
		{
			if(i) s0 += '+';
			if(rnd() % mod != 0 || i == m.size() - 1) sm += (m[i] - '0') , s0 += m[i] , i ++;
			else 
			{
				sm += ((m[i] - '0') * 10 + (m[i + 1] - '0'));
				s0 += m[i] , s0 += m[i + 1];
				i += 2;
			}
		}
		m = to_string(sm);
		i = 0 , sm = 0;
		while(i < m.size())
		{
			if(i) s1 += '+';
			if(rnd() % mod != 0 || i == m.size() - 1) sm += (m[i] - '0') , s1 += m[i] , i ++;
			else 
			{
				sm += ((m[i] - '0') * 10 + (m[i + 1] - '0'));
				s1 += m[i] , s1 += m[i + 1];
				i += 2;
			}
		}
		m = to_string(sm);
		i = 0 , sm = 0;
		while(i < m.size())
		{
			if(i) s2 += '+';
			if(rnd() % mod != 0 || i == m.size() - 1) sm += (m[i] - '0') , s2 += m[i] , i ++;
			else 
			{
				sm += ((m[i] - '0') * 10 + (m[i + 1] - '0'));
				s2 += m[i] , s2 += m[i + 1];
				i += 2;
			}
		}
		if(sm < 10)
		{
			cout << s0 << endl << s1 << endl << s2 << endl;
			return 0;
		}
	}
	return 0;
}

---

## 作者：GavinZheng (赞：1)

# CF852A Digits

隔壁yijian大佬写出了正解。那我就写一个随机化大法吧？

我们先考虑一种错误的贪心，每个数字分成一位,使其分割后数字和最小。虽然这样是错的，但是我们发现错误的概率很小。所以我们可以每次随机一个数字一位或者两个数字一位，后者的概率调整在百分之一左右。我们用这样的方法做出第一次分割，剩余的两次分割都每个数字一位即可。最后判断一下是否满足条件，如果不满足就重新跑一遍随机化。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<time.h>
#include<string>
#include<stdlib.h>
#define MAX 100
using namespace std;
char s[200500];
int ans[200500],cnt=0,n,nums;
int data[3][200500],add[3];
string output;
int rd() {
    int num=rand()%MAX;
    if(num==0)return 2;
    else return 1;
}
bool generate() {
    cnt=0,nums=0;output.clear();
    for(int i=0;i<n;i++) {
            if(i!=0)output.push_back('+');
            if(i!=n-1&&rd()==2) {
                ans[++cnt]=(s[i]-'0')*10+s[i+1]-'0';
                output.push_back(s[i]);output.push_back(s[i+1]);
                i++;
            }
            else {
                ans[++cnt]=s[i]-'0';
                output.push_back(s[i]);
            }
    }
    return 1;
}
void out() {
    cout<<output;
    printf("\n");
    for (int i = add[1]; i >=1; i--) {
        printf("%d", data[1][i]);
        if (i != 1)printf("+");
    }
    printf("\n");
    for (int i = add[2]; i >=1; i--) {
        printf("%d", data[2][i]);
        if (i != 1)printf("+");
    }
    return;
}
int main() {
    srand((unsigned)(time(NULL)));
    scanf("%d%s",&n,s);
    while(generate()) {
        long long tot=0,trans;add[0]=add[1]=add[2]=0;
        for(int i=1;i<=cnt;i++)tot+=ans[i];trans=tot;tot=0;
        while(trans){tot+=trans%10;data[1][++add[1]]=trans%10;trans/=10;}trans=tot;tot=0;
        while(trans){tot+=trans%10;data[2][++add[2]]=trans%10;trans/=10;}
        if(tot<=9){out();return 0;}
        else continue;
    }
}
```

---

## 作者：lsw1 (赞：0)

一道有趣的随机化。

首先，容易证明对于每个在题目给定范围内的数都有解。

直觉上肯定是每个数拆分成一位一位在相加，但是这有反例：如果是 $289$ 个数码 $1$，直接将其便乘 $289$ 会需要四步，即这个贪心事不正确的。

这种情况毕竟事少数，考虑使用随机化解决这个问题。对于每一个数字与数字之间的间隙，以 $\varepsilon$ 的概率在这个间隙不加上 `+` ，以 $1-\varepsilon$ 的概率加上 `+` 即可。$\varepsilon$ 可取 $3\%$。由于事随机出来的，不一定一次就可以随机出正确的，所以我们要一直随机直至随机出一个正确的方案。

```cpp
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
void solve(string s)
{
	vector<int>ans[3];//ans[i]表示在第i+1次操作在哪些位置填上加号
	string x[3];//x[i]表示第i+1次操作后的数事肾摸
	for(int i = 0;i < 3;i++)
	{
		x[i] = s;
		int sum = 0,cur = s[0] - '0';
		for(int j = 1;j < s.size();j++)
		{
			if(rand() % 100 <= 97)//一定概率加+
			{
				ans[i].push_back(j);
				sum += cur;
				cur = s[j] - '0';
			}
			else
			{
				cur = cur * 10 + s[j] - '0';
			}
		}
		sum += cur;
		stringstream ss;
		ss << sum;
		ss >> s;
	}
	if(s.size() == 1)
	{
		for(int i = 0;i < 3;i++)
		{
			int cur = 0;
			for(int j = 0;j < x[i].size();j++)
			{
				if(cur < ans[i].size() && j == ans[i][cur])
				{
					cout << "+";
					cur++;
				}
				cout << x[i][j];
			}
			cout << endl;
		}
		exit(0);//找到一个就结束程序
	}
}
int main()
{
	string s;
	cin >> s >> s;
	while(1)//一直随机直至随机出一个正确的方案
	{
		solve(s);
	}
	return 0;
}
```

---

