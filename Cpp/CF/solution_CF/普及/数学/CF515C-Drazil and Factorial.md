# Drazil and Factorial

## 题目描述

Drazil正在和Varda一起玩数学游戏。

让我们定义正整数x作为其数字的阶乘的乘积。例如，F(135)=1!*3!*5!=720。

首先，他们选择一个十进制数a，a是一个由n个数字组成的数。此数字可能以前导零开头。然后他们要找到最大正数x，x满足以下两个条件：

1.x不包含任何数字0和数字1。

2.F(x)=F(a)。

帮朋友找到这样的号码。

## 样例 #1

### 输入

```
4
1234
```

### 输出

```
33222
```

## 样例 #2

### 输入

```
3
555
```

### 输出

```
555
```

# 题解

## 作者：Leasier (赞：4)

由于只有 $0$ ~ $9$ 需要分解，考虑对每个数所能分解出的阶乘打表。

以 $9$ 为例，考虑对 $9!$ 分解质因数，得到 $9! = 2^7 \times 3^4 \times 5 \times 7$。显然地，需要从其中最大的质数开始分解。分解出 $7!$ 后，还剩 $2^3 \times 3^2$。由于分解式里有 $2$ 个 $3$，考虑分解出 $(3!)^2$，还剩 $2$。此时再分解出一个 $2!$ 即可。

以此类推，每个此范围内的数均可分解。~~如果不想自己推，可以参考我的代码。~~

最后将每个阶乘分解出的所有阶乘从大到小输出即可。

代码：
```cpp
#include <stdio.h>

int cnt[17];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		int a;
		scanf("%1d", &a);
		if (a == 2){
			cnt[2]++;
		} else if (a == 3){
			cnt[3]++;
		} else if (a == 4){
			cnt[2] += 2;
			cnt[3]++;
		} else if (a == 5){
			cnt[5]++;
		} else if (a == 6){
			cnt[3]++;
			cnt[5]++;
		} else if (a == 7){
			cnt[7]++;
		} else if (a == 8){
			cnt[2] += 3;
			cnt[7]++;
		} else if (a == 9){
			cnt[2]++;
			cnt[3] += 2;
			cnt[7]++;
		}
	}
	for (int i = 1; i <= cnt[7]; i++){
		printf("7");
	}
	for (int i = 1; i <= cnt[5]; i++){
		printf("5");
	}
	for (int i = 1; i <= cnt[3]; i++){
		printf("3");
	}
	for (int i = 1; i <= cnt[2]; i++){
		printf("2");
	}
	return 0;
}
```

---

## 作者：Krimson (赞：2)

这里用一种奇怪的方法过了这道题，本质上是通过找规律来优化dp  
希望这篇题解能让像我这样的蒟蒻也能知道是怎么发现规律的  


------------

对于每一个数的阶乘，都可以直接对其质因数分解~~应该都能想到吧~~  
然后我们就可以对读入的x得到下面这样一个数组  
```cpp
while(x){
        switch (x%10)
        {
            case 1:
            break;
            case 2:
            num[2]++;
            break;
            case 3:
            num[2]++;
            num[3]++;
            break;
            case 4:
            num[2]+=3;
            num[3]++;
            break;
            case 5:
            num[2]+=3;
            num[3]++;
            num[5]++;
            break;
            case 6:
            num[2]+=4;
            num[3]+=2;
            num[5]++;
            break;
            case 7:
            num[2]+=4;
            num[3]+=2;
            num[5]++;
            num[7]++;
            break;
            case 8:
            num[2]+=7;
            num[3]+=2;
            num[5]++;
            num[7]++;
            break;
            case 9:
            num[2]+=7;
            num[3]+=4;
            num[5]++;
            num[7]++;
            break;
        }
        x/=10;
    }
```
~~这题完全没有用到n~~  
其实直接改称num[1,2,3,4]会快很多，内存地址上直接是连续的，访问也会快一些，但是用2，3，5，7比较直观  

设$f[x][y][z][v]$表示最大的有x个2，y个3，z个5,v个七构成的F(a)  
每次往前加入任意一个数j，设能多增加now[2,3,5,7]个因数  
于是可以得到转移方程  
$f[x][y][z][v]=max(f[x][y][z][v],j+f[x-now[2]][y-now[3]][z-now[5]][v-now[7]])$  
  
这里的+指的是数码上的加，就是把一个数xxxyyy变成jxxxyyy  
而字符串中有这样一个性质：a+b=ab  
用string类型就可以很轻松的实现上面的转移！    
用代码实现即可  
```cpp
 for(ri i=1;i<=num[2];++i){//最多把它变成2222222...的形式，所以枚举num[2]次
        for(ri j=2;j<=9;++j){
            if(j!=2&&j!=3&&j!=5&&j!=7) continue;
            memset(now,0,sizeof(now));
            switch (j)
            {
                case 1:
                break;
                case 2:
                now[2]=1;
                break;
                case 3:
                now[2]=1;
                now[3]=1;
                break;
                case 4:
                now[2]=3;
                now[3]=1;
                break;
                case 5:
                now[2]=3;
                now[3]=1;
                now[5]=1;
                break;
                case 6:
                now[2]=4;
                now[3]=2;
                now[5]=1;
                break;
                case 7:
                now[2]=4;
                now[3]=2;
                now[5]=1;
                now[7]=1;
                break;
                case 8:
                now[2]=7;
                now[3]=2;
                now[5]=1;
                now[7]=1;
                break;
                case 9:
                now[2]=7;
                now[3]=4;
                now[5]=1;
                now[7]=1;
                break;
            }
            for(ri x=min(7*(i-1)+now[2],num[2]);x>=now[2];--x){
                for(ri y=min(4*(i-1)+now[3],num[3]);y>=now[3];--y){
                    for (ri   z = min(i-1+now[5],num[5]);z >= now[5]; --z)
                    {
                        for (ri v = min(i-1+now[7],num[7]); v >= now[7]; --v)
                        {
                            if(f[x-now[2]][y-now[3]][z-now[5]][v-now[7]].length()>=i-1){//可以把一些不合法的“”给筛掉，其实不加也行  
                                    f[x][y][z][v]=mx((char)(j+'0')+f[x-now[2]][y-now[3]][z-now[5]][v-now[7]],f[x][y][z][v]);    
                            }
                        }                        
                    }
                }
            }
        }
    }
```
注意此处f我是用string类型的，比较两个string大小的函数要自己写一下  
```cpp
il string mx(string a,string b){
    if(a.length()>b.length()) return a;
    else if(a.length()<b.length()) return b;
    for(ri i=0;i<=a.length();++i){
        if(a[i]>b[i]) return a;
        else if(a[i]<b[i]) return b;
    }
    
```

------------
这就完了？  
当然没有  
观察最极端的情况999999999999999,它最后的结果的位数是60位左右，一共有105个x，60个y，15个z和15个v，加上每次都要枚举2～9的数字  
得到了$O(60*60*105*15*15*8)=O(680400000)$,显然会T，实测只能过前15个点  
于是开始进入正题如何优化  
首先通过测试发现最外层的for在对极限数据999999999999999只要循环三十次就可以得到结果了，于是把最外层的循环次数改称30次，成功优化了一半  

是进行第二步优化  
通过观察可以发现，几组测试出来的数据答案都只有2，3，5，7  
难道是巧合？  
用上面的程序测试，发现可以4,6,8,9都是可以转换成2,3,5,7的  
9 7332  
8 7222  
6 53  
4 322  
而2，3，5，7之间不能转换  
同时也不难证明对于一串数字xxxxxxx4xxxx  
把这个4变成332并不影响其他的x,且一定能使结果增大  
对于数码的排列也暂时不用管，最后只要sort一下就能得到最大的排列  
到这里已经可以直接用$O(n)$的贪心A掉这道题了  
~~我舍不得我的DP啊~~  
于是在原DP上进行修改，其实没改什么东西，只是把每次枚举2~9的j改成了2，3，5，7  
现在它的复杂度我也不会算了,看起来没什么变化，但是它已经变成$O(\texttt{能过})$了  
往比较函数里加了一个cnt，发现对于999999999999999，只要比较4037653次就能出结果了，还是蛮快的  

至于为什么坚持用DP，那得问为什么这题会出现在某校DP专项训练中了

------------
最后贴上AC代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
const bool krimson=true;
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
/*
5443200
*/
ll cnt;
il string mx(string a,string b){
    ++cnt;
    if(a.length()>b.length()) return a;
    else if(a.length()<b.length()) return b;
    for(ri i=0;i<=a.length();++i){
        if(a[i]>b[i]) return a;
        else if(a[i]<b[i]) return b;
    }
    return a;
}
/*
9 7332
8 7222
6 53
4 322
*/
string  f[106][61][16][16];
ll n,x;
int num[10];
int main(){
    // freopen("rand.in","r",stdin);
    // freopen("1.out","w",stdout);
    n=read();
    x=read();
    while(x){
        switch (x%10)
        {
            case 1:
            break;
            case 2:
            num[2]++;
            break;
            case 3:
            num[2]++;
            num[3]++;
            break;
            case 4:
            num[2]+=3;
            num[3]++;
            break;
            case 5:
            num[2]+=3;
            num[3]++;
            num[5]++;
            break;
            case 6:
            num[2]+=4;
            num[3]+=2;
            num[5]++;
            break;
            case 7:
            num[2]+=4;
            num[3]+=2;
            num[5]++;
            num[7]++;
            break;
            case 8:
            num[2]+=7;
            num[3]+=2;
            num[5]++;
            num[7]++;
            break;
            case 9:
            num[2]+=7;
            num[3]+=4;
            num[5]++;
            num[7]++;
            break;
        }
        x/=10;
    }
    int now[10]={};
    int len=num[7]+num[5]-num[7]+(num[3]-2*num[7]-2*(num[5]-num[7]))+num[2]-num[7]*4-(num[5]-num[7])*3-(num[3]-2*num[7]-2*(num[5]-num[7]));
    for(ri i=1;i<=min(len,30);++i){
        for(ri j=2;j<=9;++j){
            if(j!=2&&j!=3&&j!=5&&j!=7) continue;
            memset(now,0,sizeof(now));
            switch (j)
            {
                case 1:
                break;
                case 2:
                now[2]=1;
                break;
                case 3:
                now[2]=1;
                now[3]=1;
                break;
                case 4:
                now[2]=3;
                now[3]=1;
                break;
                case 5:
                now[2]=3;
                now[3]=1;
                now[5]=1;
                break;
                case 6:
                now[2]=4;
                now[3]=2;
                now[5]=1;
                break;
                case 7:
                now[2]=4;
                now[3]=2;
                now[5]=1;
                now[7]=1;
                break;
                case 8:
                now[2]=7;
                now[3]=2;
                now[5]=1;
                now[7]=1;
                break;
                case 9:
                now[2]=7;
                now[3]=4;
                now[5]=1;
                now[7]=1;
                break;
            }
            for(ri x=min(7*(i-1)+now[2],num[2]);x>=now[2];--x){
                for(ri y=min(4*(i-1)+now[3],num[3]);y>=now[3];--y){
                    for (ri   z = min(i-1+now[5],num[5]);z >= now[5]; --z)
                    {
                        for (ri v = min(i-1+now[7],num[7]); v >= now[7]; --v)
                        {
                            if(f[x-now[2]][y-now[3]][z-now[5]][v-now[7]].length()>=i-1){
                                    f[x][y][z][v]=mx((char)(j+'0')+f[x-now[2]][y-now[3]][z-now[5]][v-now[7]],f[x][y][z][v]);    
                            }
                        }                        
                    }
                }
            }
        }
    }
    int ans[114514]={};
    for(ri i=0;i<f[num[2]][num[3]][num[5]][num[7]].length();++i) ans[i+1]=f[num[2]][num[3]][num[5]][num[7]][i]-'0';
    len=f[num[2]][num[3]][num[5]][num[7]].length();
    sort(ans+1,ans+len+1);
    for(ri i=len;i>=1;--i) write(ans[i]);
    return 0;
}
```


---

## 作者：灵光一闪 (赞：1)

看了下题解，感觉我的比较好一些，我用的是vector,用sort简单一遍过 ~~（编译都不带编译的~~

代码：
```
//#include<bits/stdc++.h>

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
#include<string>
#include<cmath>
#include<map>

using namespace std;
vector <int> g;
int main()
{
    int n;
    char c;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>c;
        if(c=='6')
        {
            g.push_back(5);//手算结果
            g.push_back(3);//ctrl+c ctrl+v大fa好！
        }
        else if(c=='8')
        {
            g.push_back(7);
            g.push_back(2);
            g.push_back(2);
            g.push_back(2);
        }
        else if(c=='9')
        {
            g.push_back(7);
            g.push_back(3);
            g.push_back(3);
            g.push_back(2);
        }
        else if(c=='4')
        {
            g.push_back(3);
            g.push_back(2);
            g.push_back(2);
        }
        else if(c!='0'&&c!='1')//如果都没有就直接压进去
            g.push_back(c-'0');
    }
    sort(g.begin(),g.end());
    reverse(g.begin(),g.end());
    for(int i=0;i<g.size();i++)
        cout<<g[i];
    return 0;
}
```
哦对了前面``tryrtj`` dalao不是说``不知为啥就想到的分解质因数``吗，我来解答一下：首先，题目说``最大``，众所周知，2位数大于1位数，而分解质因数可以使位数最大化，再``sort+reverse``就可以了

The End.

---

## 作者：cyy233 (赞：1)


#  ~~打表过蓝题~~

对于每一个数字，如6

我们把它分成**几个阶乘相乘的形式**

让能分的阶乘数尽量地多，最后构成的数必然最大

你可用10分钟手算

$1!=1!$

$2!=2!$

$3!=3!$

$4!=3!*2!*2!$

$5!=5!$

$6!=5!*3!$

$7!=7!$

$8!=7!*2!*2!*2!$

$9!=7!*3!*3!*2!$

把这些数放入一个数组，再从大到小排序，输出答案

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,x,cnt,ans[100010];
inline LL read(){
	LL f=1,x=0;char c=getchar();
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>=48&&c<=57){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f*x;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();x=read();
	while(x){
		if(x%10==1||x%10==0){
			x/=10;
			continue;
		}
		else if(x%10==4){
			ans[++cnt]=3;
			ans[++cnt]=2;
			ans[++cnt]=2;
		}
		else if(x%10==6){
			ans[++cnt]=5;
			ans[++cnt]=3;
		}
		else if(x%10==8){
			ans[++cnt]=7;
			ans[++cnt]=2;
			ans[++cnt]=2;
			ans[++cnt]=2;
		}
		else if(x%10==9){
			ans[++cnt]=7;
			ans[++cnt]=3;
			ans[++cnt]=3;
			ans[++cnt]=2;
		}
		else ans[++cnt]=x%10;
		x/=10;
	}
	sort(ans+1,ans+cnt+1);
	for(int i=cnt;i>=1;i--)
		cout<<ans[i];
	fclose(stdin);fclose(stdout);
	return 0;
}

```



---

## 作者：JiaY19 (赞：0)

~~众所周知，打表是提高的基础~~

#### 思路

一道~~比较简单的~~打表题。

做这道题，需要三步。

1. 拿出笔和纸。

2. 手算出每个数的拆分。

3. 写代码。

至于如何手算，我们可以进行枚举。

需要遵从**尽量多拆**的原则。

因为只要数位变大了，整个数自然就变大了。

手算的表我们选择用桶装。

因为数据很小，桶比较快。

至于代码就很简单了。

#### Code

表见程序。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, num[15];

int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

int main()
{
    m = read();
    for (int i = 1; i <= m; i++)
    {
        int y; 
        scanf("%1d", &y);
        if (y == 2) num[2]++;
        else if (y == 3) num[3]++;
        else if (y == 4) num[2] += 2 , num[3]++;
        else if (y == 5) num[5]++;
        else if (y == 6) num[3]++ , num[5]++;
        else if (y == 7) num[7]++;
        else if (y == 8) num[2] += 3 , num[7]++;
        else if (y == 9) num[2]++ , num[3] += 2 , num[7]++;
    }
    for (int i = 1; i <= num[7]; i++) cout << 7;
    for (int i = 1; i <= num[5]; i++) cout << 5;
    for (int i = 1; i <= num[3]; i++) cout << 3;
    for (int i = 1; i <= num[2]; i++) cout << 2;
    return 0;
}

```

完结撒花！

---

## 作者：tryrtj (赞：0)

先声明一下，这题真的好难想

刚开始一看题，哈哈，枚举？求阶乘？每一位不就最大9嘛，在一看，诶？！阶乘的乘积？莫非是。。。高精度？再一看题，n<=15。。。枚举法凉凉

不知为啥就想到的分解质因数，这题真的是分解质因数嘞

于是开始分

2 

2 3

2 2 2 3 

2 2 2 3 5

2 2 2 2 3 3 5 

2 2 2 2 3 3 5 7

2 2 2 2 2 2 2 3 3 5 7 

2 2 2 2 2 2 2 3 3 3 3 5 7 

真好，然后记下来，更直观些就是

1=1

2=2

3=3

4=2+2+3

5=5

6=5+3

7=7

8=2+2+2+7

9=2+3+3+7

只需要定义一个数组来存储就行啦。

现在开始解释：因为数字的位数越多，数字就越大，所以要尽全力把数字分成更多位，这时就用到了分解质因数，将n!分解成n1!*n2!*...的形式。

举个栗子：

```
8=1*2*3*4*5*6*7*8
=2*2*2*2*2*2*2*3*3*3*3*5*7
=2!*2!*2!*7!
```

然后用字符串读入，每一位判断就行了

#### 温馨提示：一定要细心

我就是因为算错一个数而WA了一次

完整代码：

```
#include<iostream>
#include<string>
using namespace std;
int a[20]={0};
int main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	for(int i=0;i<n;i++){
		int t=s[i]-'0';
		if(t==2)a[2]++;
		if(t==3){
			a[3]++;
		}
		if(t==4){
			a[2]+=2;
			a[3]++;
		}
		if(t==5){
			a[5]++;
		}
		if(t==6){
			a[3]++;
			a[5]++;
		}
		if(t==7){
			a[7]++;
		}
		if(t==8){
			a[2]+=3;
			a[7]++;
		}
		if(t==9){
			a[2]++;
			a[3]+=2;
			a[7]++;
		}
	}
	for(int i=9;i>1;i--){
		for(int j=0;j<a[i];j++){
			cout<<i;
		}
	}
	return 0;
}
```

---

