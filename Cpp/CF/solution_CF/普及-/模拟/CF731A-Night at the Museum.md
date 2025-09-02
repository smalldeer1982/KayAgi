# Night at the Museum

## 题目描述

Grigoriy像某一喜剧电影中的英雄一样（我也不知道哪一部）晚上在博物馆里当保安。第一天晚上他收到了一个标签打印机。他要去给展馆里的文物一个个贴标签了。

这个标签打印机可以打印一张塑料标签。它打印的标签上的字母一个连着一个。打印机上有一个小写英文字母环，一个指向选中字母的指针和一个选中字母的按钮。字母环一个字母为一个，你想怎么转就怎么转，顺逆皆可。下面那张图为指针和字母环排列顺序。指针开始指向“a”。

Grigoriy添加一样新展品时需要打印出它的名字贴在上面。打完一个字母后不需要返回到字母“a”。

我们的英雄现在有点慌了。他感觉有些展品活过来了而且要锤他，所以他想赶快把名字打完回家。帮他找到打印字符串时字母环最少转动多少格。

## 说明/提示

1.从‘a’到‘z’（逆时针1格）  
2.从‘z’到‘e’（顺时针5格）   
3.从‘e’到‘u’（逆时针10格）   
4.从‘u’到‘s’（逆时针2格）

## 样例 #1

### 输入

```
zeus
```

### 输出

```
18
```

## 样例 #2

### 输入

```
map
```

### 输出

```
35
```

## 样例 #3

### 输入

```
ares
```

### 输出

```
34
```

# 题解

## 作者：liuyifan (赞：1)

[楼下](https://studyingfather.blog.luogu.org/solution-cf731a)已经发了基于char数组的题解了,那我来发一个string的吧

顺便普及一下c和c++中常用的快读快写的方法

在c++中,cin和cout在不加
```cpp
std::ios::sync_with_stdio(0);
```
时是最慢的,但noip中又不能这样用(于freopen混用会造成文件指针混乱),而scanf次之,但在某些数据大得scanf都会tle或者卡常数的题目中,就需要用到我们的大杀器:输入输出优化.

```cpp
inline void getint(int &x)
{
	x=0;
	char ch=getchar();
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
}//读入一个int,使用方式getint(x);
```
```cpp
inline void putint(reg ll x)
{
     if(x<0)putchar('-'),x=-x;
     if(x>9)putint(x/10);
     putchar(x%10+'0');
}//输出一个int,使用方式putint(x);
```
以上同学们可直接背下,对于[CCF老年机](http://www.noi.cn/)非常实用

完整code:
```cpp
#include<bits
#define ll long long
#define reg register
using namespace
string s;
ll ans;
char tmp='a';
inline void putint(reg ll x)
{
     if(x<0)putchar('-'),x=-x;
     if(x>9)putint(x/10);
     putchar(x%10+'0');
}
int main()
{
    getline(cin,s);//读入一整行
    for(reg ll i=0;i<s.length();
    {
        ans+=min(abs(tmp-s[i]),26-abs(tmp-s[i]));
        tmp=s[i];
    }//累加
    putint(ans);//输出
    return
}
```
拒绝抄袭,共建和谐洛谷

[My Blog](https://www.luogu.org/blog/liuyifan/)

---

## 作者：lu_fish (赞：0)

这道题主要是要考察字符串的一些知识。

只要比较顺时针与逆时针那个更短再加到ans里就可以了。

```cpp
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
//以上不解释
int main(){
    string s;
    cin>>s;
    int ans=0;//这里一定要初始化，不然会出来一个不知道什么数的数
    ans+=min(abs(s[0]-'a'),26-abs(s[0]-'a'));//比较顺时针转与逆时针转的较小值
    for(int i=1;i<s.size();i++){
        ans+=min(abs(s[i]-s[i-1]),26-abs(s[i]-s[i-1]));//比较顺时针转与逆时针转的较小值
    }
    cout<<ans<<endl;//输出
    return 0;//结束求过qaq
}
```

---

## 作者：stry (赞：0)

这题的思路很简单，直接通过比较来进行判断，是逆时针旋转的次数少，还是顺时针少，ans+=少的那一种方案。注意：当前位置要等于现在所在的字母。之后输出ans。
## 接下来是程序
```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
char ch[105];
int ans;
int main()
{
 char ch1='a';
 scanf("%s",ch);
 int len1=strlen(ch);
 for(int i=0;i<len1;i++)
 {
  ans+=min(abs(ch1-ch[i]),26-abs(ch1-ch[i]));
  ch1=ch[i];
 }
 printf("%d",ans);
 return 0;
}
```


---

## 作者：StudyingFather (赞：0)

一道字符串处理的水题，每次旋转时求出顺时针和逆时针的旋转次数，比较一下即可。
```cpp
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
char str[105];
int main()
{
 int ans=0;
 char arr='a';
 scanf("%s",str);
 int len=strlen(str);
 for(int i=0;i<len;i++)
 {
  ans+=min(abs(arr-str[i]),26-abs(arr-str[i]));
  arr=str[i];//更新当前位置
 }
 printf("%d",ans);
 return 0;
}
```

---

