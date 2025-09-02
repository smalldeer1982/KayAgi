# Funny Encryption Method

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=960

[PDF](https://uva.onlinejudge.org/external/100/p10019.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10019/ab61a55b13f53a52e7e0fb57d2b672a1a2942116.png)

## 样例 #1

### 输入

```
3
265
111
1234```

### 输出

```
3 5
6 3
5 5```

# 题解

## 作者：Amberhart (赞：2)

进制转换的题，有点考思维。

思路：

函数部分，只有一个，求的是当 $M$（我代码里用的 $n$） 为十进制时 $1$ 的个数。

写法简单来说就是一直将 $n$ 一直除以 $2$，如果余数为 $1$，计数器 $c$ 加一。

---
主函数部分：

1. 读入组数 $t$ 和 询问的数 $n$；

2. 输出函数 `ten_1` 的值；

3. `while` 循环数出 $n$ 为十六进制时 $1$ 的个数。

---
代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int ten_1(int n){//十进制时1的个数
	int c=0;
	while(n!=0){
		if(n%2!=0){//余数为1时
			c++;
		}
		n=n/2;//一直除下去
	}
	return c;
}
int t,n,c,x;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cout<<ten_1(n)<<" ";
		while(n!=0){
			x=n%10;//n为16进制，将n转化为10进制就是向10取余
			while(x!=0){//按题目意思，将x再转化为2进制数1的个数
				if(x%2==1){
					c++;
				}
				x=x/2;//一直除下去
			}
			n=n/10;//一直除下去，不然会死循环
		}
		cout<<c<<"\n";
		c=0;//注意要清0
	}
	return 0;
}


```


---

## 作者：No21 (赞：2)

### 解题思路

$M$ 既是一个十进制数，又是一个十六进制数，因此 $M$ 不可能包含 $A,B,C,D,E,F$，且 $M$ 最大只有 $9999$，因此我们直接输入一个整数类型的 $M$。

对于十进制，我们直接用短除法进行进制转换，每模出一个 $1$ 就给答案增加 $1$。

我们知道十进制怎么做，所以我们考虑一个十六进制的数要怎么转化为十进制。很简单，十六进制转换为十进制只需要给第 $i$ 位数乘上 $16^{i-1}$ 即可。

[十进制转二进制](https://baike.baidu.com/item/%E5%8D%81%E8%BF%9B%E5%88%B6%E8%BD%AC%E4%BA%8C%E8%BF%9B%E5%88%B6/393189?fr=ge_ala)

[十六进制转十进制](https://baike.baidu.com/item/%E5%8D%81%E5%85%AD%E8%BF%9B%E5%88%B6%E8%87%B3%E5%8D%81%E8%BF%9B%E5%88%B6%E8%BD%AC%E6%8D%A2/21503487)

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    int n,m,m16;
    int a[5]={0,1,16,256,4096};
    int check(int a)
    {
        int ans=0,x=a;
        while(x)
        {
            if(x%2==1)
                ans++;
            x/=2;
        }
        return ans;
    }
    int mian()
    {
        cin>>n;
        while(n--)
        {
            cin>>m;
            cout<<check(m)<<' ';
            m16=0;
            for(int i=1;m;i++)
            {
                m16+=m%10*a[i];
                m/=10;
            }
            cout<<check(m16)<<'\n';
        }
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

话说这题为什么是绿色，[P1143](https://www.luogu.com.cn/problem/P1143)都只有橙色。

---

## 作者：ICU152_lowa_IS8 (赞：1)

本题建议降橙，评绿是不是太高了点。

翻了一圈题解没有 `lowbit` 函数的写法，这个函数在树状数组的遍历中就是干相当于这个题目要干的事。

____

如下代码为 `lowbit` 函数，其可以求出一个整数的二进制位中最低的一位的**值**，即，$(110000)_2$ 这个数放进 `lowbit` 函数返回的是 $16$ （即 $2^{5-1}$）而并非 $5$。

```
int lowbit(int t){
	return t&(-t);
}
```

然后我们可以通过这个函数统计出 $M$ 转成二进制之后含有多少个 $1$，输出答案即可。原理的话，学过树状数组的可以跳过。

### 没有学过树状数组的可以看一下：

```
int checksum(int n){
	int ans=0;
	for(int i=n;i;i-=lowbit(i)){
		ans++;
	}
	return ans;
}
```

给定一个二进制数 $(1100000010)_2$，第一次循环会先减去 $(10)_2$，得到 $(1100000000)_2$。

如果你还没发现什么，那么再进行一步，得到 $(1000000000)_2$。

发现了吗？每次循环会减掉二进制中的一个 $1$！那么我们只需要一直循环直到将 $M$ 减成 $0$ 然后统计次数即可。

同时本题的数据范围极小（$1\leq M\leq9999$），用刚才讲的方法（时间复杂度 $O(N\log M)$）完全可以通过。

先直接按照我们刚才的方法跑一遍，然后再将 $M$ 当作十六进制之后转成十进制（怎么写没关系，数据范围非常小）之后按照刚才的方法跑一遍，输出两次的答案即可。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int lowbit(int t){
	return t&(-t);
}
int checksum(int n){
	int ans=0;
	for(int i=n;i;i-=lowbit(i)){
		ans++;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	while(n--){
		int m;
		cin>>m;
		cout<<checksum(m)<<" ";
		int t=0;
		while(m){
			t=t*16+m%10;
			m/=10;
		}
		cout<<checksum(t)<<"\n";
	}
	return 0;
}

```

---

## 作者：_Kouki_ (赞：1)

### 题目翻译
给你一个数 $ N $ ,求 $ N $ 的 $ 10 $ 和 $ 16 $ 进制下，转 $ 2 $ 进制的数中 $ 1 $ 的个数。   

### 题目思路
- 若是 $ 10 $ 进制，直接 $ \div 2 $ ,看 $ 1 $ 的个数。   
- 若是 $ 16 $ 进制，需要每一位进行转二进制。   
  那么我们不妨将 $ 0-9 $ 每一位转二进制的 $ 1 $ 的个数打出来。
  
```cpp
int getnum[55]={0,1,1,2,1,2,2,3,1,2};
```
如上，这是每一位转二进制后的1的个数。     
现在我们只要根据这个思路，去实现代码！

### 题目代码

```cpp
#include<bits/stdc++.h>
using namespace std;
/*
Kouki 的做题想法
如下 www
*/
int t;
int n;
int getnum[55]={0,1,1,2,1,2,2,3,1,2};
/*
难度：普及-
思路：
* 10进制直接转
* 16进制一位一位转
  *我们可以打表就行了！
* QAQ，开始实现！ 
*/
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        int tmp;
        long long ans;
        tmp=n,ans=0;
        while(tmp){
            if(tmp%2==1) ans++;
            tmp/=2;
        }
        printf("%lld ",ans);
        tmp=n,ans=0;
        while(tmp){
            ans+=getnum[tmp%10];
            tmp/=10;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

这题主要考察进制的一些运算，这十分重要。   
在以后更加深入的学习中，会有更多基于进制的衍生运算符。

---

## 作者：AlexandreLea (赞：0)

## 题目大意

给出一个数 $M$，求将 $M$ 分别视作十进制数和十六进制数时二进制上分别有多少位 $1$。

## 题目思路

不需要思路。十进制转十六进制不需要思路。

```cpp
#include <iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,nn=0,de=1;
        cin>>n;
        cout<<__builtin_popcount(n)<<" ";
        for(int i=1;i<=10;i++) nn+=de*(n%10),n/=10,de*=16;
        cout<<__builtin_popcount(nn)<<endl;
    }
    return 0;
}
```

**EO_OF**

---

## 作者：Rookie_t (赞：0)

这是一道橙题难度进制转换。 

可以模拟十进制或十六进制转二进制的过程。

当 $n$ 为 $10$ 进制时，就用普通方式转换，然后再统计 $1$ 的个数。

当 $n$ 为 $16$ 进制时，就用一位一位转换，然后再统计 $1$ 的个数。

代码如下： 

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,cnt = 0;
void turn(){
	y = x;
	while(y != 0){
		if(y%2 == 1){
			cnt++;
		}
		y /= 2;
	}
	cout<<cnt<<" ";
	y = x;
	cnt = 0;
	while(y != 0){
		int z = y % 10;
		while(z != 0){
			if(z%2 == 1){
				cnt++;
			}
			z /= 2;
		}
		y /= 10;
	}
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cnt = 0;
		cin>>x;
		turn();
		cout<<cnt<<endl;
	}
	return 0;
}
```

---

## 作者：zqh123b (赞：0)

**一道裸裸的进制转换题！**

就是把十进制分别转成二进制和十六进制，然后数 $1$ 的个数。

具体做法见代码：
```cpp
//zqh123b的题解代码
#include<bits/stdc++.h>
using namespace std;
int Get_the_1_in_the_BIN_of_the_number(int n){//二进制中1的个数
	int ans=0;
	while(n){
		ans+=n&1;//相当于if(n%2==1)ans++，位运算速度更快
		n>>=1;//相当于n/=2，位运算速度更快
	}
	return ans;
}
int Get_the_1_in_the_HEX_of_the_number(int n){//十六进制中1的个数
	int the_number_of_HEX_in_BIN[]={0000,0001,0010,0011,0100,0101,0110,0111,1000,1001,1010};//十六进制数一位用二进制表示（由于n可以是十进制，因此一位的权值不超过10）
	int the_number_of_1_of_HEX_in_BIN[]={0,1,1,2,1,2,2,3,1,2,2};//十六进制中一位用二进制表示的1的个数
	int ans=0;
	while(n){
		ans+=the_number_of_1_of_HEX_in_BIN[n%10];
		n/=10;
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		printf("%d ",Get_the_1_in_the_BIN_of_the_number(n));//答案1
		printf("%d\n",Get_the_1_in_the_HEX_of_the_number(n));//答案2
	}
	return 0;
}
//代码不可AC请勿抄袭
```


---

## 作者：G__G (赞：0)

先简化题意：

给定一个既是十进制数又是十六进制的数 $M$，求 $M$ 转换成二进制数后 $1$ 的个数。

首先看当 $M$ 为十进制数时，我们可以模拟短除法的过程，反复除 $2$ 统计余数为 $1$ 的次数。

而当 $M$ 为十六进制数时，我们可以一位一位的转换，再统计 $1$ 的个数。

最核心的部分就是进制转换，可参考 [B2143](https://www.luogu.com.cn/problem/B2143)。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int x,y,cnt=0;;
		cin>>x;
		y=x;
		while(y!=0){
			if(y%2==1){
				cnt++;
			}
			y/=2;
		}
		cout<<cnt<<" ";
		y=x;
		cnt=0;
		while(y!=0){
			int z=y%10;
			while(z!=0){
				if(z%2==1){
					cnt++;
				}
				z/=2;
			}
			y/=10;
		}
		cout<<cnt<<endl;
	}
	return 0;
}
```


---

## 作者：LegendaryGrandmaster (赞：0)

输入一个数 $n$，输出当 $n$ 为 $10$ 进制和 $16$ 进制时二进制中 $1$ 的个数。

函数 `__builtin_popcount(n)` 表示 $10$ 进制数 $n$ 二进制中 $1$ 的个数，直接调用。

$16$ 进制按照进制的写法写即可，先把 $16$ 进制数 $n$ 转为 $10$ 进制数，再依次对 $2$ 取模，累计 $1$ 的个数即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--){
		int n;
	    cin>>n;
	    cout<<__builtin_popcount(n)<<' ';
	    string st=to_string(n);
	    int w=1,s=0;
	    for(int i=st.size()-1;i>=0;i--){
	        if(st[i]>='0'&&st[i]<='9')s+=(st[i]-48)*w;
			else s+=(st[i]-'A'+10)*w;
	        w*=16;
	    }
	    int c=0;
	    while(s>0){
	        c+=s%2;
	        s/=2;
	    }
	    cout<<c<<'\n';
	}
}
```

---

## 作者：Siteyava_145 (赞：0)

问题：

给定 $n$。问 $n$ 表示十进制时转化成二进制后 $1$ 的个数，和问 $n$ 表示十六进制时转化成二进制后 $1$ 的个数。

众所周知，C++里有一个内置函数 `__builtin_popcount(n)`，用来统计 $n$ 转化成二进制后 $1$ 的个数。

这道题。。。不就是为它而出的吗。。。

而且，$16$ 进制数转化成二进制后 $1$ 的个数，只需要统计每一个数位的 $\operatorname{popcount}$，就可以了。这个就不必多讲了吧。$(13)_{16}=(00010011)_2$，按位转化。

所以问题就解决了，具体详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		int x=__builtin_popcount(n);//直接统计
		int xx=0;//16进制下转化为二进制后1的个数
		while(n){
			xx+=__builtin_popcount(n%10);//按位转化+统计
			n/=10;//每一位
		}
		cout<<x<<' '<<xx<<endl;
	}
} 
```


---

## 作者：Hywel (赞：0)

给出一个数，算出它分别用 $10$ 进制和 $16$ 进制表达式作为 $2$ 进制的所有为1的数量。

$10$ 进制的 $2$ 进制位要判断太简单了，只要不断加上除 $2$ 的余数就行，作为 $16$ 进制时更简单，每个数字都有对应的 $4$ 个二进制数，列表就行。

```cpp
#include<bits/stdc++.h>
namespace IO
{
	template < typename T > inline void write( T x )
	{
	    if(x < 0)
	        putchar('-') , x = - x;
	    if(x == 0)
	    {
	        putchar('0') ;
	        return ;
	    }
	    if(x > 9)
	        write(x / 10) ;
	    putchar(x % 10 + '0') ;
	    return ;
	}
	template < typename T > inline void read( T &x )
	{
	    x = 0 ; int w = 1 ; char ch = getchar() ;
	    while( !isdigit( ch ) ) { if(ch == '-') w = -1 ; ch = getchar() ; }
	    while( isdigit( ch ) ) x = (x << 1) + (x << 3) + (ch ^ 48) , ch = getchar() ;
	    x *= w;
	}
}

#define writeln(x) write(x) , putchar('\n')
#define writesp(x) write(x) , putchar(' ')
using namespace IO ;
int fun10(int x);
int fun16(int x);
int a[10] = {0,1,1,2,1,2,2,3,1,2};
signed main()
{
    int T, n;
    read(T);
    while(T--){
        read(n);
        printf("%d %d\n", fun10(n), fun16(n));
    }
    return 0;
}
int fun10(int x)
{
    int num = 0;
    while(x){
        num += x % 2;
        x /= 2;
    }
    return num;
}
int fun16(int x)
{
    int num = 0;
    while(x){
        num += a[x%10];
        x /= 10;
    }
    return num;
}
```

---

## 作者：Orz_Deng (赞：0)

## 翻译：给你一个数字，统计他是十进制数和十六进制数时转化为二进制后每个位上1的个数。

# so？
先按十进制算，然后统计每位上的数字转化成二进制即可。（十六进制每位对应4个二进制位）
个人只放转2进制代码。。。
```
int zhuan(int a) 
   {
	int ans = 0;
	while ( a ) {
		ans += a%2;
		a >>= 1;
	}
	return ans;
}
```
希望各位AC。。。

---

## 作者：紊莫 (赞：0)

## 翻译（题意）  
$N(0<N<1001)$ 组数据给定整数 $M$，满足 $0<M<9999$，求其 16 进制和 10 进制各位数字转换为 2 进制后，1 的个数之和。
## 分析
10 进制：用转换 2 进制的短除法即可，不多做解释。  
16 进制：取出每一位，求出那一位的 2 进制的值即可，可以写如下函数。  
```cpp
int f16(int a)
{
    int num = 0;
    while(a) {
        num += a & 1;//等价于a%2
        a >>= 1;//等价于a/=2
    }
    return num;
}

```
知道了以上原理，不妨打表出 0 到 9 中每一位作 16 进制的 2 进制值。
```cpp
int base[]={0,1,1,2,1,2,2,3,1,2};
```
## 代码
综上所述，代码如下。
为了节省篇幅，快读压缩至了一行，毕竟只是一个工具。  
小贴士：本题读入输出量略大，建议快读或者 scanf。
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
int base[]={0,1,1,2,1,2,2,3,1,2};
int main()
{
	int t=read();
	while(t--)
	{
		int n=read(),ans10=0,ans16=0;
		int x=n;
		while(x)//先处理十进制
		{
			ans10+=x&1;
			x/=2;
		}
		x=n;
		while(x)//十六进制
		{
			ans16+=base[x%10];
			x/=10;
		}
		printf("%d %d\n",ans10,ans16);
	}
	return 0;
}


```


---

