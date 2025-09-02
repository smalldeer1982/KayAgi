# [USACO19DEC] Where Am I? B

## 题目描述

Farmer John 出门沿着马路散步，但是他现在发现可能迷路了！

沿路有一排共 $N$ 个农场。不幸的是农场并没有编号，这使得 Farmer John 难以分辨他在这条路上所处的位置。然而，每个农场都沿路设有一个彩色的邮箱，所以 Farmer John 希望能够通过查看最近的几个邮箱的颜色来唯一确定他所在的位置。

每个邮箱的颜色用 A..Z 之间的一个字母来指定，所以沿着道路的 $N$ 个邮箱的序列可以用一个长为 $N$ 的由字母 A..Z 组成的字符串来表示。某些邮箱可能会有相同的颜色。Farmer John 想要知道最小的 $K$ 的值，使得他查看任意连续 $K$ 个邮箱序列，他都可以唯一确定这一序列在道路上的位置。

例如，假设沿路的邮箱序列为 `ABCDABC` 。Farmer John 不能令 $K=3$，因为如果他看到了 `ABC`，沿路有两个这一连续颜色序列可能所在的位置。最小可行的 $K$ 的值为 $K=4$，因为如果他查看任意连续 4 个邮箱，这一颜色序列可以唯一确定他在道路上的位置。

## 说明/提示

$1 \leq N \leq 100$。

## 样例 #1

### 输入

```
7
ABCDABC```

### 输出

```
4```

# 题解

## 作者：CandyCandyFruit (赞：44)

第一眼看到题目时，我内心欣喜万分：太好了，终于有一道水题可刷了！于是我就开开心心地提交了**求这个字符串里出现不同字母的个数的代码**（样例过的了）。

结果...$10$分（代码就不贴了，防止你们说我傻）。

我便开始重新看题目：

![](https://cdn.luogu.com.cn/upload/image_hosting/0mo3gg5l.png)

我在这篇文章里暂且称“$ABC$”那样有**两个**（或以上）完全相等的东西为“小字符串”。可以得出，当小字符串长度$=3$时，$k=4$。所以我们就要求出最长的小字符串的长度，并且加一后输出。

$AC$代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,m;
char a[250];
void c(int i,int j)
{
	if(a[i]==a[j])//判断这两个字母是否相同 （如果相同，小字符串的位数+1） 
	{
		s++;
		c(i+1,j+1);//接着看下一个字母是否相同 
	}
	
}
int main()
{
	scanf("%d",&n);
	for(int z=1;z<=n;z++)
	cin>>a[z];
	for(int w=1;w<=n;w++)//二重循环，数据够小，不怕超时 
	{
		for(int b=w+1;b<=n;b++)// 注意这里b要等于w+1，不然会一直相等（就会等同于“w=w”） 
		{
			s=0;//统计当前的相同的小字符串里所包含的字母数 
			c(w,b);//自定义函数寻找最长的两个小字符串 
			if(s>m) m=s;//如果这个小字符串里字母的数量超过最大值，最大值更新 
		}
	}
	printf("%d",m+1);//因为最大的相等的小字符串有两个（及以上），所以需要加一。 
	return 0;
}
```

[顺便安利一下我的bolg](https://ptemma-250.blog.luogu.org/#)

---

## 作者：Ace_Radom (赞：14)

### 2019-12-21 19:56 初版

### 2020-1-4 更新

	在 string 成员函数 find 的第二种用法的叙述中：
    错误的把 k 打成了 a 。
    目前已经修复。

主要考了一个字符串的处理。

## 先分析题意

老朋友FarmerJohn在一条有彩色邮箱的路上**迷路了**。【滑稽】

颜色一共有26种，用 A-Z 对应表示。

现在FarmerJohn知道邮箱颜色的排列，他想知道在这条路中，他最少可以通过几个邮箱的颜色来确定他的位置。

## 思路	
    
    其实就是要求字符串中满足所有长度为 k 的子串在该字符串中只出现一次的 k 的最小值。
    
为了达到这个效果，我们需要借助 C++ string 的成员函数。

需添加头文件（用万头的跳过）：

	#include<string>
    
这里用到的成员函数有三个，下面讲讲用法：

    s.substr( n , k )
    	在字符串 s 中，从第 n 位开始截取长度为 k 的子串
    s.find( s1 ) 
    	在字符串 s 中，查找子串 s1 ，返回 s1 第一次出现的位置
    s.find( s1 , k )
    	用法与上一个基本相同
        在字符串 s 中，从 k 位置开始查找子串 s1 ，返回 s1 第一次出现的位置
    //两个find成员函数如果没找到，返回 string::npos
    
所以在题目中，只需要截取一个子串，查找它在字符串中是否有重复第二遍，再反复暴力即可。

但不用考虑在该子串前有重复的问题。

因为这里查找是从左向右推的，如果在前面有重复，之前就会被筛出来。

## 代码：

~~~C++
#include<bits/stdc++.h>
using namespace std;
string s;
bool b = false;  //是否找到
int n;
void Compare( int k ){
    for ( int i = 0 ; i <= n - k ; i++ )
    {
        string ss;  //截取的子串
        ss = s.substr( i , k );  //从 i 开始，截取 k 长的子串
        if ( s.find( ss , i + 1 ) != string::npos )
        //在 i 位置之后查找字串 ss 并找到
        {
            return;  //不满足条件，返回
        }
        if ( i == n - k )  //成功做到最后，即满足条件
        {
            cout << k << endl;
            b = true;
            return;
            //输出 k ，结束程序
        }
    }
}
int main(){
    cin >> n;
    cin >> s;
    int k = 1;
    while ( !b )  //仍不满足条件
    {
        k++;
        Compare( k );  //检查长度为 k 的子串
    }
    //因为在子串长度为 k 时绝对满足条件，所以无需设置跳出程序
    return 0;
}
~~~

---

## 作者：Strong_Jelly (赞：9)

### 第一篇题解

**思路 :** $O(n ^ 3)$暴力枚举所有区间，定义一个$map$来存储是否有重复的区间，从小到大枚举所有长度$(1$ ~ $n)$, 直到找到一个区间满足条件，具体情况看代码。

```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
int n;
string s;
map < string, int > mp;//map存是否访问过 
signed main()
{
	scanf("%d\n", &n);
	cin >> s;
	for(register int l = 1; l <= n; ++l)
	{
		int f = 1;//是否可以满足题目要求 
		mp.clear();//清空map 
		for(register int i = 0, j = i + l - 1; i < n && j < n; ++i, j = i + l - 1)//枚举一个长度为l的区间 
		{
			string x = "";//初始化 
			for(register int k = i; k <= j; ++k)
			{
				x += s[k];//拼接起来 
			}
			if(mp[x] == 1)//如果出现过 
			{
				f = 0;//不行 
				break;
			}
			mp[x] = 1;//标记为出现过 
		}
		if(f)//可以 
		{
			printf("%d", l);//输出 
			return 0;//退出 
		}
	}
	return 0;
}
```


---

## 作者：智子·起源 (赞：8)

## 就没有人想到这个简单的三FOR方法吗？

### 那我就来分享一下：

通过理解题目，我们可以发现，k这是越小越好的。

- 所以我们可以直接判断字符串内任意连续k位的所有子串有没有重复。

- 有就继续枚举下一个k没有，那就输出当前枚举的k即可。

- k的最大范围就是字符串长度（就只有一种情况，别告诉我还不能确定）

方法简单，思路明了，程序就更不在话下了。
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
string s;int len;
bool ck(int x)
{
  for(int i=0;i<len-x+1;i++)
  {
    string ss=s.substr(i,x);//记录当前枚举的连续k位的数字。
    int num=0;
    for(int j=0;j<len-x+1;j++)//枚举找重复。
      if(s.substr(j,x)==ss)num++;//记录重复次数
    if(num>1)return false;//如果有重复那就证明不符合。（除去它本身一个）
  }
  return true;//所有的都不重复，返回true。
}
int main()
{
  cin>>len>>s;
  for(int i=1;i<=len;i++)//枚举最小k
    if(ck(i)){cout<<i;return 0;}//判断符不符合条件。
  return 0;
}
```


---

## 作者：ZJ_Res (赞：7)

在这道题目中，我们可以定义一个[set（一种关联式容器）](https://blog.csdn.net/weixin_42036617/article/details/91049826)：

再通过枚举k然后进行哈希，

```cpp
mp.clear();
m=1;
for(int i=1;i<=n-len+1;i++){
	j=i+len-1;s=0;
	for(int k=i;k<=j;k++){
		s=(long long)s*bas%Mod;
		s+=a[k];
	}   
	if(mp.count(s)){
		m=0;
		break;
	}
	mp.insert(s);
}
```
最后再直接判断：

```cpp
if(m){
	cout<<len;
	return 0;
}
```

完事（以下是完整代码）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Mod=1e9+7,bas=131;
set<int>mp;//定义set
char c[110];//110大小防止溢出
int n,m,a[110],j,s;
int main(){
    cin>>n;
    scanf("%s",c+1);
    for(int i=1;i<=n;i++){
        a[i]=c[i]-'A'+1;//预处理
    }
    for(int len=1;len<=n;len++){
        mp.clear();//清空
	m=1;
        for(int i=1;i<=n-len+1;i++){
            j=i+len-1;s=0;
            for(int k=i;k<=j;k++){
                s=(long long)s*bas%Mod;
                s+=a[k];
            }   
            if(mp.count(s)){//查找
                m=0;
                break;
            }
            mp.insert(s);//插入
        }
        if(m){
            cout<<len;
            return 0;
        }
    }
    return 0;
}
```




---

## 作者：chenyilai (赞：7)


### 如果要给这道题加个算法标签的话，那么一定是字符串+枚举，暴力（这道题n<=100,三重循环没问题）
```pascal
var a:array[1..100] of string; n:int64; i,j,k:longint; b:boolean; s:string;
begin
  readln(n); readln(s);
  for i:=1 to n do//用来枚举题目中的K
   begin
    b:=true;
    for j:=1 to n-i+1 do//用来枚举开始的地方
     begin
      for k:=1 to j-1 do//用来判断j开始的i个字符是否与前面重复
       if a[k]=copy(s,j,i) then//如果重复了,就退出循环，节省时间。
        begin
         b:=false; break;
        end;
      a[j]:=copy(s,j,i);//记录下Farmer John 从j开始看到的邮箱颜色
     end;
    if b=true then
     begin
      writeln(i); halt;//如果不会重复，就直接输出。
     end;
   end; 
end.//完美收场
```

------------

特别提醒：
1.比赛时halt前一定要close(input); close(output); !!!!!

2.如果n<=10000 的话，一定会超时，就不能用枚举，暴力做了。

3.不要抄袭!!!!!

---

## 作者：NOUN007 (赞：7)

## [题目传送门](https://www.luogu.com.cn/problem/P5832)

题面其实不难理解，翻译过来就是找一个最小的数值 k 使得在字符串 S 内的任意 k 个连续的字符都不会出现第二次

## [STL大法好](https://en.cppreference.com/w/cpp)
想到这里，完全就可以用STL里的substr()和find()函数了

通过使用substr()截取原串 S 内的 k 个连续字符，定义为 S0，在原串 S 内使用find()查找是否含有 S0 即可。如果寻找到了 S0，那么find()函数会返回最近的与 S0 匹配的字符串的第一个字符的下标，如果没有找到则会返回一个非常大的值，就可以用这个性质来判断是否存在重复的 S0 了。

代码如下
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define N 
using namespace std;
string S,S0;int n;

inline ll read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}

int main(){
    n=read();
    cin>>S;
    for(int k=1;k<=n;i++){
        bool flag=0;		      //用flag判断是否所有的S0都符合要求
        for(int j=0;j<n-k;j++){
            S0=S.substr(j,k);
            if(S.find(S0,j+1)<=100){  //如果找到了就直接跳过本个k值
                    flag=1;
                    break;
                }
        }
        if(!flag){		      //全都符合条件就直接输出
            printf("%d\n",k);
            break;
        }
    }
    return 0;
}

```


---

