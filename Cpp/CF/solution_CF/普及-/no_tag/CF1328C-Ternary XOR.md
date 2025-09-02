# Ternary XOR

## 题目描述

A number is ternary if it contains only digits $ 0 $ , $ 1 $ and $ 2 $ . For example, the following numbers are ternary: $ 1022 $ , $ 11 $ , $ 21 $ , $ 2002 $ .

You are given a long ternary number $ x $ . The first (leftmost) digit of $ x $ is guaranteed to be $ 2 $ , the other digits of $ x $ can be $ 0 $ , $ 1 $ or $ 2 $ .

Let's define the ternary XOR operation $ \odot $ of two ternary numbers $ a $ and $ b $ (both of length $ n $ ) as a number $ c = a \odot b $ of length $ n $ , where $ c_i = (a_i + b_i) \% 3 $ (where $ \% $ is modulo operation). In other words, add the corresponding digits and take the remainders of the sums when divided by $ 3 $ . For example, $ 10222 \odot 11021 = 21210 $ .

Your task is to find such ternary numbers $ a $ and $ b $ both of length $ n $ and both without leading zeros that $ a \odot b = x $ and $ max(a, b) $ is the minimum possible.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
5
22222
5
21211
1
2
9
220222021```

### 输出

```
11111
11111
11000
10211
1
1
110111011
110111010```

# 题解

## 作者：fzwfzwfzw (赞：2)

题意是t组数据，然后每组一个n和一个数字串c，有0，1，2三种数字

这道题想让你构造两个字符串，使得（ai+bi）%3=ci，还要使

max（a，b）最小，当然我们这两个字符串不会有3或以上的数字

所以我们最直接的办法就是

当ci=2的时候，ai=bi=1；

当ci=0的时候，ai=bi=0；

当ci=1的时候，将ai=1，bi=0因为ai>bi所以这个串a大于b所以

#### 让a的后面**所有值**都最小，都为零，

那么b就等于ci。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()//手写快读
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
int n,m;
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
	{
		int a;
		a=read();
		string b;//读入这个字符串,这个b就是c数字串
		cin>>b;
		int cnt=0; 
		for(int i=0;i<b.size();i++)
		{
			if(cnt==1)printf("0");
			else if(b[i]=='0')printf("0");//0
			else if(b[i]=='2')printf("1");//2
			else if(b[i]=='1')//1这里加一个标记，后面的所有答案都是0
			{
				printf("1");
				cnt=1;
			}
		}
		printf("\n");
		cnt=0;
		for(int i=0;i<b.size();i++)
		{
			if(cnt==1)
			{
				if(b[i]=='2')printf("2");
				if(b[i]=='0')printf("0");
				if(b[i]=='1')printf("1");
			}
			else if(b[i]=='2')printf("1");
			else if(b[i]=='0')printf("0");
			else if(b[i]=='1')printf("0"),cnt=1;//1这里加一个标记，后面的所有答案都是ci
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Minecraft万岁 (赞：2)

本题为贪心 由于题目中说首位三进制为 $2$ 那就不用担心有前导 $0$ 的存在啦 看看怎么构造答案  
我们让 $a[]$ 为读入的字符串 $ansa[]$ $ansb[]$ 为最终的答案  

首先对于 $a[i]=0$ 的情况 肯定 $ansa[i]=ansb[i]=0$ 不让数字增加 没人会让 $ansa[i]=1$ $ansb[i]=2$ 吧    

再关注 $a[i]=1$ 的情况 注意到要让两个字符串最大的最小 
于是乎我们有让总和**最小** 其余**尽量均摊**的思想 我们发现 这种情况下答案对应位子必然一个 为 $1$ 一个为 $0$  又考虑到尽量均摊 我们就让最高位的 $1$ 填在一个答案里 其余都填在另一个答案里 可以保证尽量的平均 不妨让最高位的答案填在 $ansa[]$ 里 其余填在 $ansb[]$ 里 ~~下面好说一点~~

最后考虑 $a[i]=2$ 的情况 分成两类      

- 前面已经填过最高位的 $1$  
我们可以发现 如果两边都填上 $1$ 会让 $ansa[]$ 进一步增加 不符合**总和最小**以及**尽量均摊**的前提条件 于是我们将 $ansb[i]$ 填入 $2$ 保证了 **尽量均摊** 的条件  
- 前面没有填过最高位的 $1$  
这个就简单了 直接两边都填上 $1$ ~~这个很容易想吧~~  


于是这个神奇的题目就做完了   
贴上我的代码  


------------
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char x[50005];//读入的字符串 
char ansa[50005];//第一个答案字符串 
char ansb[50005];//第二个答案字符串 
bool flag1;//判断之前有没有在高位填过1 
int t,n; 
inline void read(int &x)//快读 
{
	int f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline int mn(int _x,int _y)
{
	return _x<_y?_x:_y;
}
inline int mx(int _x,int _y)
{
	return _x>_y?_x:_y;
}
inline int ab(int _x)
{
	if(_x<0) return -_x;
	else return _x;
}
int main()
{
	read(t);
	while(t--)
	{
		flag1=true;//开始肯定没有在高位填过1 
		read(n);
		scanf("%s",1+x);//从下标1开始读入字符串 
		for(int i=1;i<=n;i++)//从高到低  
		{
			if(x[i]=='0') //几个大情况 
			{
				ansa[i]=ansb[i]='0';
			}
			if(x[i]=='1')
			{
				if(flag1)//没填过 
				{
					ansa[i]='1';//在 ansa[i]中填上1 
					ansb[i]='0';
					flag1=false;//标记为填过了 
				}
				else//填过了就在另一个中填 
				{
					ansa[i]='0';
					ansb[i]='1';
				}
			}
			if(x[i]=='2')
			{
				if(!flag1)//按照思路分类 
				{
					ansa[i]='0';
					ansb[i]='2';
				} 
				else
				{
					ansa[i]=ansb[i]='1';
				}
			}
		}
		for(int i=1;i<=n;i++) printf("%c",ansa[i]);//打印两个答案 
		puts("");
		for(int i=1;i<=n;i++) printf("%c",ansb[i]);
		puts("");	
	} 
	return 0;
}



```


---

## 作者：laboba (赞：1)

考虑这样一种策略：从最高位开始枚举a和b，逐位判断并决策。
显然枚举到i位时，此时a的前i-1位与b的前i-1为是否相同对策略有影响。

如果相同：
1. t[i]=0,此时a和b均应为0
2. t[i]=1,此时a和b应分出大小，一个此位为1，一个此位为0，不妨设a>b，a[i]=1,b[i]=0。理由：如果不这样做，最优策略则为均选2，则这样最大数必然比前一种策略大。
3. t[i]=2,此时应a[i]=b[i]=1。

如果不同：

由于我们保证a>b,所以无论后面的数如何选择，最大数都一定为a，则我们应让a尽量小，所以a此位为0，b为t[i]。

至于判断是否相同，只需要一个bool变量equal，初始为true，当需要变换的时候赋值为false。

代码如下：
```cpp
#include<cstdio>
using namespace std;
const int N=50010;
int n;
int a[N],b[N],x[N];//x[i]即为t[i]。
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%1d",&x[i]);//%1d可以保证只读入一位。
		bool equal=true;
		for(int i=1;i<=n;i++){
			if(equal){//相等的情况
				if(x[i]==0){
					a[i]=0;
					b[i]=0;
				}
				if(x[i]==1){
					equal=false;
					a[i]=1;
					b[i]=0;
				}
				if(x[i]==2){
					a[i]=1;
					b[i]=1;
				}
			}
			else {//不等的情况
				a[i]=0;
				b[i]=x[i];
			}
		}
		for(int i=1;i<=n;i++)printf("%d",a[i]),a[i]=0;
		printf("\n");
		for(int i=1;i<=n;i++)printf("%d",b[i]),b[i]=0;
		printf("\n");
	}
}
```

如有不懂的可以私信我。

~~自我感觉讲的比楼上清楚，求通过~~

---

## 作者：andyli (赞：0)

依次遍历给定数字的每一位，同时记录当前是否有两位不同。  

- 若第 $i$ 位为 `0`，则 $a_i=b_i=0$ 一定是最优解。  
- 若第 $i$ 位为 `1`，若已有第 $j$ 位不同，不妨设$a_j<b_j$，则 $a_i=1,b_i=0$ 是最优解，否则 $a_i=0,b_i=1$，并更新标记。  
- 若第 $i$ 位为 `2`，若已有第 $j$ 位不同，不妨设$a_j<b_j$，则 $a_i=2,b_i=0$ 是最优解，否则 $a_i=b_i=1$ 为最优解。  

时间复杂度 $\mathcal O(n)$。  

代码如下：  
```cpp
const int maxn = 50005;

char A[maxn], ans1[maxn], ans2[maxn];
int main()
{
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        io.read(A + 1);
        ans1[1] = ans2[1] = '1';
        for (int i = 2; i <= n + 1; i++)
            ans1[i] = ans2[i] = '\0';
        bool g = 0;
        for (int i = 1; i <= n; i++) {
            if (A[i] == '2') {
                if (g)
                    ans1[i] = '2', ans2[i] = '0';
                else
                    ans1[i] = ans2[i] = '1';
            }
            if (A[i] == '1') {
                if (g)
                    ans1[i] = '1', ans2[i] = '0';
                else
                    ans1[i] = '0', ans2[i] = '1', g = true;
            }
            if (A[i] == '0')
                ans1[i] = ans2[i] = '0';
        }
        writeln(ans1 + 1);
        writeln(ans2 + 1);
    }
    return 0;
}
```

---

## 作者：Ignotus (赞：0)

### 题目大意
定义三进制按位异或 $⊙$ 为若 $c=a⊙b$，则有 $c_i=(a_i+b_i)\%3$。现有 $t$ 组数据，每组数据输入一个 $n$ 位的三进制数 $x$，要求对于每组数据，输出满足 $a⊙b=x$，且使 $\max(a,b)$ 最小的 $a$，$b$。若有多个答案，输出任意一个即可。输入保证 $x$ 的第一位是 $2$。  
#### 主要思路  
本题贪心即可。  
因为保证第一位是 $2$，所以 $a$，$b$ 的第一位都是 $1$ 才能保证 $a$，$b$ 中的较大值最小。  
接下来，如果是 $0$，则两位都是 $0$；如果是 $2$，则两位都是 $1$。  
如果第一次出现 $1$，则可以让 $a$ 的下一位为 $1$，$b$ 的下一位为 $0$，此时 $a$ 的值一定大于 $b$，则之后 $a$ 的所有为都是 $0$，一定保证 $a$（较大的数）最小。

#### 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int t,n,flag;
char x[100010],a[100010],b[100010];

int main()
{
        cin>>t;
        while(t--){
                memset(x, '0', sizeof x);
                memset(a, '0', sizeof a);
                memset(b, '0', sizeof b);
                flag=0;//多组数据，需要初始化
                cin>>n;
                getchar();//先读入上一行的换行符
                for(int i=1; i<=n; i++) x[i]=getchar();
                a[1]=b[1]='1';
                for(int i=2; i<=n; i++){
                        if(x[i]=='0') a[i]=b[i]='0';
                        if(x[i]=='1') {
                                if(flag==0){
                                        a[i]='1';
                                        b[i]='0';
                                        flag=1;
                                }
                                else if(flag==1){
                                        a[i]='0';
                                        b[i]='1';
                                }
                        } 
                        if(x[i]=='2'){
                                if(flag==0){
                                        a[i]='1';
                                        b[i]='1';
                                }
                                else if(flag==1){
                                        a[i]='0';
                                        b[i]='2';
                                }
                        }
                }//再根据题意模拟即可
                for(int i=1; i<=n; i++) cout<<a[i];
                cout<<endl;
                for(int i=1; i<=n; i++) cout<<b[i];
                cout<<endl;//输出
        }
        return 0;
}
```  
感谢阅读！


---

