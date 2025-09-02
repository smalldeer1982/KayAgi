# 决斗 Headshot

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4511

[PDF](https://uva.onlinejudge.org/external/16/p1636.pdf)

# 题解

## 作者：qwerta (赞：4)

对于直接开枪，记一下有多少个$0$，再记一下其中有多少个$0$的后一位为$1$，挂掉的概率为(01的数量)/(0的数量)．

转一下之后挂掉的概率就是(0的数量)/(序列长度)

然后比较一下就好了．

懒得处理精度，用了交叉相乘．

```
/*
  qwerta 
  UVA1636 Headshot Accepted 
  代码 C++，0.46KB
  提交时间 2018-10-26 17:13:47
  耗时/内存 0ms, 0KB
*/
#include<iostream>
#include<cstdio>
using namespace std;
string s;
int main()
{
    while(cin>>s)
    {
        int zr=0;//记录0的个数
        for(int i=0;i<s.length();++i)
        if(s[i]=='0')zr++;
        //shoot
        int dy=0;//记录01的个数
        for(int i=0;i<s.length()-1;++i)
        if(s[i]=='0'&&s[i+1]=='1')dy++;
        int n=s.length();
        if(s[n-1]=='0'&&s[0]=='1')dy++;//别忘了它是环形的
        //
        int y=s.length()-zr;//算1的个数
        if(dy*n<zr*y){cout<<"SHOOT"<<endl;}//如果dy/zr<y/n
        else if(dy*n==zr*y){cout<<"EQUAL"<<endl;}
        else cout<<"ROTATE"<<endl;
    }
    return 0;
}
```

---

## 作者：Tjaweiof (赞：2)

# UVA1636 题解——Tjaweiof
[题目传送门](https://www.luogu.com.cn/problem/UVA1636)

设 $a$ 为序列中 `00` 的数量，$b$ 为序列中 `0` 的数量，其实就是让我们比较 $\tfrac{a}{b}$ 与 $\tfrac{b}{n}$ 的大小，若 $\tfrac{a}{b}$ 大就输出 `SHOOT`，若 $\tfrac{b}{n}$ 大就输出 `ROTATE`，否则输出 `EQUAL`。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int n;
double a, b;
int main(){
    while (cin >> s){
        a = b = 0;
        n = s.size();
        s = " " + s;
        for (int i = 1; i <= n; i++){
            if (s[i] == '0'){
                b++;
                if (s[i + 1] == '0'){
                    a++;
                }
            }
        }
        if (s[n] == '0' && s[1] == '0'){
            a++;
        }
        if (a / b > b / (double)n){
            cout << "SHOOT";
        } else if (a / b < b / (double)n){
            cout << "ROTATE";
        } else {
            cout << "EQUAL";
        }
        cout << endl;
    }
    return 0;
}
```
#### 此代码时间复杂度 $O(n)$，空间复杂度 $O(n)$，完美过关！

---

## 作者：Grisses (赞：2)

一把左轮手枪，我们知道弹仓内子弹的相对位置。你在和你的朋友玩俄罗斯转盘 ~~（这什么垃圾朋友）~~。你的朋友先将弹仓随机转了任意下，然后开枪了，他没有挂。现在该你了，你需要决定是直接开枪还是转随机下再开枪。没转一次或开一枪现在的子弹槽会向移到它左边相邻的子弹槽的位置上。

如果你选择直接开枪，那么活下来的概率就是一个没有子弹的位置后面一个也没有子弹的位置的位置在所有没有子弹的位置中的占比。

如果你选择旋转，那么活下来的概率就是没有子弹的位置在所有位置中的占比。

最后判断怎么的操作活下来的概率大就行了。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,cnt,sum;
  char s[105];
  signed main()
  {
      while(scanf("%s",s+1)!=EOF){
          cnt=sum=0;
          n=strlen(s+1);
          s[n+1]=s[1];
          for(int i=1;i<=n;i++){
              if(s[i]=='0')sum++;
              if(s[i]=='0'&&s[i+1]=='0')cnt++;
          }
          if(n*cnt>sum*sum)puts("SHOOT");
          else if(n*cnt<sum*sum)puts("ROTATE");
          else puts("EQUAL");
      }
      return 0;
  }
```

---

## 作者：Onana_in_XMFLS (赞：1)

[Link](https://www.luogu.com.cn/problem/UVA1636)

~~big water 题！话说为什么是左轮~~

直接扣一枪空膛的概率是个[条件概率](https://baike.baidu.com/item/%E6%9D%A1%E4%BB%B6%E6%A6%82%E7%8E%87/4475278?fr=aladdin)，等于子串 $00$ 的个数除以 $00$ 和 $01$ 总数（也就是子串 $0$ 的个数），转一下再扣空膛的概率为 $0$ 的比率。



------------

~~以下为正常模式~~

设子串 $00$ 的个数为 $a$ ，子串 $0$ 的个数为 $b$，则两个概率分别为 $a/b$ 以及 $b/n$ ，问题就转化为比较它们，前者大就是 ```SHOOT```，相等就是 ```EQUAL```后者大就是```ROTATE```。

代码（**仅为主体部分**）
```cpp
	string s;
	while(cin>>s)
	{
		int n = s.length();
		s += s;
		int a = 0,b = 0;
		for(int i = 0;i < n;++i)
			if(s[i] == '0') 
			{
				++b;
				if(s[i+1] == '0') ++a;
			}
		if(a*n > b*b) puts("SHOOT");
		else if(a*n == b*b) puts("EQUAL");
		else puts("ROTATE");
	}
```

---

## 作者：_WF_ (赞：0)

## 题目理解

这道题是一个**俄罗斯转盘**的游戏
。
### 若不转：

因为已知第一枪**没有子弹**，所以这一发一定为 $0$ 下一发有子弹的概率为

若下一发有子弹的数量 $/$ 总的没有子弹的数量。

### 若转：
即 有子弹数 $/$ 能放子弹数

## 代码实现
```
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	while(cin>>s)
	{
		
		int _01=0,_0=0,_1=0;
		for(int i=0;i<s.size()-1;i++)
		{
			if(s[i]=='0'&&s[i+1]=='1')_01++;
		}
		if(s[s.size()-1]=='0'&&s[1]=='1')_01++;
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='0')_0++;
			else _1++;
		 } 
		if(_01*s.size()>_0*_0)cout<<"ROTATE\n";
		else if(_01*s.size()==_0*_0)cout<<"EQUAL\n";
		else cout<<"SHOOT\n";
	}
 } 
```


---

## 作者：ruanshaochuan______ (赞：0)

我们定义序列长度为 $s$，序列中 $0$ 的数量为 $ans$，自己为 $0$ 并且下一位也为 $0$ 的数量为 $sum$。   
如果你选择直接开枪，那么活下来的概率就是 $\dfrac{sum}{ans}$。  
如果选择转一下再开枪，那么你活下来的概率就是 $\dfrac{ans}{s}$。      
如果直接比较会出现精度问题，所以我们选择将两边都乘上一个 $ans\times s$，变型成 $sum \times s$ 和 $ans^2$ 再去比较大小。   
代码    
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    int ans,sum;
    while(cin>>s)
    {
        ans=sum=0;
        s+=s[0];//别忘了序列是循环的
        for(int i=0;i+1<s.size();i++)//只需要循环到原序列的最后一个就可以了
        {
            if(s[i]=='0')
                ans++;
            if(s[i]=='0'&&s[i+1]=='0')
                sum++;
        }
        if((s.size()-1)*sum>ans*ans)
            cout<<"SHOOT"<<endl;
        else
        if((s.size()-1)*sum<ans*ans)
            cout<<"ROTATE"<<endl;
        else
            cout<<"EQUAL"<<endl;
    }
}
```



---

## 作者：Astatinear (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA1636)


首先，考虑随机转的概率，能转到没子弹概率显然是序列中 $0$ 的个数除以总个数。

在考虑直接开枪，由于没有告诉你当前是哪一个档，所以要枚举所有的 `0`，并记录下一发为 `0` 的个数。然后用这个数除以序列中 `0` 的个数，就是直接 `shoot` 不会有子弹的概率。

最后看两个的大小就可以了。（由于可能存在精度问题，考虑除法改为乘法。）

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string b;
int main()
{
    while(cin>>b)
    {
    	int zero1,zero2,zero3;
    	zero1=zero2=zero3=0;
    	for(int i=0;i<b.length();++i)
    	{
    		zero3++;
    		if(b[i]=='0') zero1++;
    		if(b[i]=='0'&&b[(i+1)%b.length()]=='0') zero2++;
    	}
    	if(zero2*zero3==zero1*zero1) puts("EQUAL");
    	else if(zero2*zero3<zero1*zero1) puts("ROTATE");
    	else puts("SHOOT");
    }
}

```

---

## 作者：Unnamed114514 (赞：0)

首先，令 $b$ 为 $0$ 的数量，那么第一发就有 $b$ 种情况；令 $a$ 为 $0$ 后为 $1$ 的数量，那么对于 `SHOOT` 有子弹的概率就是 $\dfrac{a}{b}$；令 $n$ 为位置的总数，$c$ 为 $1$ 的数量，那么旋转后有子弹的概率就是 $\dfrac{c}{n}$。

那么，我们只需要比较 $\dfrac{a}{b}$ 和 $\dfrac{c}{n}$ 即可。

---

## 作者：A_Đark_Horcrux (赞：0)

更新于 2021 年 11 月 11 日：修正了笔误

首先，开了一枪是空枪，说明当前位是 $0$，对于直接开一枪的情况，我们判断当前的 $0$ 下一位是 $0$（没子弹）还是 $1$（有子弹）。此时我们是不知道当前的 $0$ 是哪一位，所有考虑整个串中的 $0$ 的下一位，它的下一位可能是 $0$ 或 $1$，则下一枪没子弹的概率为$\frac{\textsf{（所有0中后面是0的情况）}}{\text{所有情况（所有0中后面是0或1的情况）}}$ 所有情况的个数即为串中0的个数。

对于转一转的情况，没子弹的概率即为$\frac{\textsf{0的个数}}{\text{串的长度（0和1的个数和）}}$ 。求出来以后比一比大小即可。

__注意__ 

1.由于子弹序列是环形序列，所以要将串尾特殊考虑，常用的方法是让序列复制一遍（即加上它本身）：

```string a; cin>>a; a+=a;```

2.比大小的时候可以将分式比较通过交叉相乘化为整数比较，避免了精度问题。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
string a;
int main()
{
    while(cin>>a)
    {
        int l=a.length(); a+=a;//复制一遍
        int s=0,s1=0;
        for(int i=0;i<l;i++)
        	if(a[i]=='0')
			{
				s++;//统计0的个数
				if(a[i+1]=='0') s1++;//统计"00"子串的个数
			}
        if(s1*l>s*s) puts("SHOOT");//交叉相乘
        else if(s1*l==s*s) puts("EQUAL");
        else puts("ROTATE");
    }
    return 0;
}//结束啦awa
```

---

## 作者：小闸蟹 (赞：0)

```cpp
// 条件概率题：
// 直接打一枪没事的概率是等于子串"00"的个数除以"00"和"01"的个数（即0的个数）
// 这前面的一个0表示上一个人打的是空弹，后面的0/1表示这次的子弹情况
// 转一下再打一枪没事的概率等于0在该字符串中出现的概率
// 以a表示子串"00"的个数，b表示0的个数，n表示字符串长度
// 所以就只要比较a/b和b/n的大小即可
// 然后交叉相乘一下，避免除0的错误，也不用怕精度问题
#include <iostream>
#include <string>

int main()
{
    std::string Str;
    while (std::cin >> Str)
    {
        int a = 0, b = 0;
        auto n = static_cast<int>(Str.size());
        for (int i = 0; i < n; ++i)
        {
            if (Str[i] == '0')
            {
                ++b;    // b表示0的个数
                if (Str[(i + 1) % n] == '0')    // 注意是个环形的，所以要取模
                {
                    ++a;    // a表示"01"串的个数
                }
            }
        }

        if (a * n == b * b)
        {
            std::puts("EQUAL");
        }
        else if (a * n > b * b)
        {
            std::puts("SHOOT");
        }
        else
        {
            std::puts("ROTATE");
        }
    }

    return 0;
}
```

---

