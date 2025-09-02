# Letter

## 题目描述

给你一个字符串，我们每一次操作都可以将一个大写字母变成任意小写字母，当然同理也可以将小写字母变成任意大写字母，问最少操作多少次，能够使得字符串变成前边都是大写字母，后边都是小写字母。

## 样例 #1

### 输入

```
PRuvetSTAaYA
```

### 输出

```
5
```

## 样例 #2

### 输入

```
OYPROSTIYAOPECHATALSYAPRIVETSTASYA
```

### 输出

```
0
```

## 样例 #3

### 输入

```
helloworld
```

### 输出

```
0
```

# 题解

## 作者：siyue (赞：7)

字符串要分成前后两段，简称A段，B段，每段长度>=0。

从序列角度看，A段所有字符必须翻转成大写，B段所有字符翻转为小写字母。用两个数组a和b来表示要翻转的字符个数，ai表示从1-i个字符有多少个小写字母，bi表示i-n有多少个大写字母。

这样a[i]+b[i+1]就是以i为分界点时，要翻转的字符个数，取其最小值即可，注意分界点i可以是0和n，表示全部小写和全部大写。

```
int a[100005],b[100005];
int main()
{
    string s;
    int i,j;
    cin>>s;
    int n=s.length();
    a[0]=0;
    b[n+1]=0;
    for(i=1;i<=n;i++)
    {
        if(s[i-1]>='a'&&s[i-1]<='z')
        {
            a[i]=a[i-1]+1;
        }
        else
        {
            a[i]=a[i-1];
        }
    }
    for(i=n;i>=1;i--)
    {
        if(s[i-1]>='A'&&s[i-1]<='Z')
        {
            b[i]=b[i+1]+1;
        }
        else
        {
            b[i]=b[i+1];
        }
    }
    int minx=n;
    for(i=0;i<=n;i++)
    {
        minx=min(a[i]+b[i+1],minx);
    }
    cout<<minx;
    return 0;
}
```

---

## 作者：Sparda (赞：3)

蒟蒻之我只能做这种**普及-**的题qwq （~~因为我只会嘤嘤嘤啊~~）

-------------
题目是这样的，就是经过x次操作让这个字符串变成前面一截是大写字母，后面一截是小写字母，如样例一：

PRuvetSTAaYA

改变后是：

PRUVETSTAAYA

(最少改变5个字母）

-------------
（由此得出，这是一道神奇的**普及-**作为蒟蒻的我都能做得dp题啊 _~~嘤嘤嘤~~_ ）

-------------
所以，我们可以用一个dp[MAXN][2]来记录，

dp[i][0]表示到第i个字符全部改小写字母所需改变量

dp[i][1]表示到第i个字符全部改大写字母所需改变量

然后，答案自然而然就是min(dp[len-1][0],dp[len-1][1])啊啊啊

~~是不是很简单~~

下面附上AC代码

```cpp

/*The Bone Of My Sword*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define MAXN 100005
using namespace std;
char s[MAXN];
int dp[MAXN][2];//dp[i][0]表示到i为止全部改为小写字母所需操作次数
				//dp[i][1]表示到i为止全部改为大写字母所需操作 
int len; 
int main(void){
	scanf("%s",&s);
	len = strlen(s);
	if(s[0] >= 'a'&&s[0] <= 'z')
		dp[0][0] = 0,dp[0][1] = 1;
	else	dp[0][0] = 1,dp[0][1] = 0;
	for(int i = 1;i < len;i ++){
		if(s[i] >= 'a'&&s[i] <= 'z'){
			dp[i][0] = min(dp[i-1][0],dp[i-1][1]);
			dp[i][1] = dp[i-1][1]+1;
		}
		else{
			dp[i][0] = min(dp[i-1][0],dp[i-1][1])+1;
			dp[i][1] = dp[i-1][1] ;
		}
	}
	cout << min(dp[len-1][0],dp[len-1][1]) << endl;
	return 0;
} 
```




---

## 作者：Tyyyyyy (赞：1)

## 经典的~~暴力枚举~~算法。
因为要把字符串分为2段，前半段全为大写，后半段全为小写，因此可以枚举每一个分界点对应的修改次数。

但按这种算法，时间复杂度为$O(n^2)$，而本题数据最大是$10^5$，肯定会爆掉。

因此，我们可以考虑用前缀和维护数组，使时间复杂度变为$O(n)$。

AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100001];
int fro[100001],beh[100001],ans=1e9;//注意ans要定义一个极大值
int main()
{
	gets(s);
	int n=strlen(s);
	fro[0]=beh[n+1]=0;//初始化
	for(int i=1;i<=n;i++)
	{
		if(s[i-1]>='a'&&s[i-1]<='z')fro[i]=fro[i-1]+1;
		else fro[i]=fro[i-1];//对于前半段计算前缀和
	}
	for(int i=n;i>=1;i--)
	{
		if(s[i-1]>='A'&&s[i-1]<='Z')beh[i]=beh[i+1]+1;
		else beh[i]=beh[i+1];//对于后半段计算前缀和
	}
	for(int i=0;i<=n;i++)ans=min(ans,fro[i]+beh[i+1]);//枚举分界点计算修改次数
	printf("%d",ans);
	return 0;
}
```

---

## 作者：江山_远方 (赞：1)

蒟蒻来写题解了qwq  
题意很简单，就是钦定一个字符串的某个位置，使其和其前面的所有字符都是大写字母，后面的所有字符都是小写字母，该位置可以随意选择，问最少改变次数是多少？  
本来窝打算暴力水过去的，即为枚举该位置，然后对于每个位置暴力查询，看看最小操作次数，最后求最小值。  
代码写完，样例测完，然后我准备提交时……  
毒瘤的数据看到了->10^5  
蒟蒻的内心瞬间崩溃……  
后来老师讲了前缀和，昏昏欲睡的我立刻一个鲤鱼打挺，对啊！前缀和！  
我们珂以对于每个点记录从1到该点需要改变的大写字母数和小写字母数  
酱就可以可以对于O(n)的暴力查询进行时间维护，使其降低到O(1)
代码：  
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;//名字空间
string st;
int l,MIN;
int s1[110000],s2[110000];//定义
int main()//主程序
{
	cin>>st;//读入
	l=st.size();//求字符串st的长度的函数,并记录下来
	for(int i=1;i<=l;i++)//求到该点的大写和小写字母分别的改编次数
	  if(st[i-1]>='A'&&st[i-1]<='Z')//如果是大写字母
	  {
	  	s1[i]=s1[i-1]+1;//改变一个大写字母
	  	s2[i]=s2[i-1];//小写字母不变,继承上一个点
	  }
	  else//如果是小写字母
	  {
	  	s1[i]=s1[i-1];//大写写字母不变,继承上一个点
	  	s2[i]=s2[i-1]+1;//改变一个小写字母
	  }
	MIN=2000000000;//求最小值要先付最大值
	for(int i=0;i<=l;i++)MIN=min(MIN,s2[i]+s1[l]-s1[i]);//首先要把前面所有的小写字母改编成大写字母,是s2[i],然后再把后面的大写字母改成小写字母，前面的不用改，所以为s1[l]-s1[i]
	cout<<MIN;
	return 0;
} 
```
于是AC抱回家……

---

## 作者：开始新的记忆 (赞：1)

题目大意：给你一串由大小写的英文字母组成的字符，现在你可以让一个字母的大小写变化，合法的字符串满足可以把这串字符串能分为两段，左边的一段由大写字母构成，另一段由小写字母构成，现在要你用最小的操作数来把这串字符串改合法，并输出要多少次操作。

大致思路：我们可以枚举一下以每个点做隔断的最小操作数，但是每次都去循环寻找的话就要用O(n^2)的时间，显然不行。于是我们想到了可以用两个数组去记录当前字母及之前（左）有多少小写字母和当前字母及之后（右）有多少大写字母，类似于一个前缀和，我们用On的预处理，On的查找即可，每次查找将两个数组相加并-1（因为当前点重复算了），算出最小值。

```
#include<bits/stdc++.h>
using namespace std;
int ans1[100010],ans2[100010],mixn=0x7fffffff;
string a;

int main()
{	cin>>a;
	int n=a.size();
	for(int i=1;i<=n;++i)
		if(a[i-1]>='a' && a[i-1]<='z')
			ans1[i]=ans1[i-1]+1;
		else
			ans1[i]=ans1[i-1];
	for(int i=n;i>=1;--i)
		if(a[i-1]>='A' && a[i-1]<='Z')
			ans2[i]=ans2[i+1]+1;
		else
			ans2[i]=ans2[i+1];
	for(int i=1;i<=n;++i)
		mixn=min(mixn,ans1[i]+ans2[i]-1);
	cout<<mixn<<endl;
	return 0;
}
```


---

## 作者：A_Đark_Horcrux (赞：0)

考虑枚举中心点，计算出把中心点及其左边全部变为大写，把中心点右边全部变为小写的操作次数。但每次暴力计算显然是不行的qaq

设字符串长为 $n$，我们可以记录一个前缀和，定义 $f_i$ 为第 $1\sim i$ 位中小写字母的个数，再记录一个后缀和，定义 $g_i$ 为第 $i\sim n$ 位中小写字母的个数。

这样，假设中心点为 $x$ ，则需要的操作数为第 $i$ 位及以前的小写字母个数，加上第 $i$ 位以后的大写字母个数，也就是 $f[i]+g[i+1]$ ，就可以 $O(n)$ 计算啦qwq

```cpp
#include<iostream>
#include<cctype>//判断大小写的函数
using namespace std;
const int N=1e5+10;
int l,minn=1e9+7,i,f[N],g[N]; string s;
int main()
{
	cin>>s; l=s.size();
	for(i=1;i<=l;i++) f[i]=f[i-1]+bool(islower(s[i-1]));//计算前缀和
	for(i=l;i>=1;i--) g[i]=g[i+1]+bool(isupper(s[i-1]));//计算后缀和
   	//注意cctype头文件中函数的返回值不一定是0和1，所以加上bool()
	for(i=0;i<=l;i++) minn=min(minn,f[i]+g[i+1]);//计算
	cout<<minn; return 0;//输出awa
}
```

---

## 作者：wkjwkj (赞：0)

题目思路是比较清晰的。

我们可以建立两个前缀和数组 $sum1$ 与 $sum2$ 。  $sum1_i$ 所代表的的意义是 $1\sim i$ 中有多少个小写字母， $sum2_i$ 所表示的是 $1\sim i$ 中有多少个大写字母，用时间复杂度为 $O(n)$ 的预处理的出这两个数组，其次枚举分割点则以 $i$ 作为分割点时，所得到的的答案为 $ans=sum1[i]+sum2[n]-sum2[i]$ 在这些答案中取最小值即可得到最终答案。

总体时间复杂度为 $O(n)$ 。

注意：由于字符串可能全都是大写字母或小写字母，所以我们枚举分割点的区间应为 $0\sim n$ 。

下面附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100005];
int sum1[100005],sum2[100005];
int ans=1e9;
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		sum1[i]=sum1[i-1],sum2[i]=sum2[i-1];
		if(s[i]>='a'&&s[i]<='z')sum1[i]++;
		else sum2[i]++;
		//printf("%d %d\n",sum1[i],sum2[i]);
	}
	for(int i=0;i<=n;i++)
	{
		ans=min(ans,sum1[i]+sum2[n]-sum2[i]);
		//printf("%d\n",sum1[i]+sum2[n]-sum2[i]);
	}  
	printf("%d\n",ans);
	return 0;
}
```





---

