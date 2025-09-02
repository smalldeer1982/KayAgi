# [ABC091B] Two Colors Card Game

## 题目描述

有两组字符串，一组蓝色，一组红色，各有n、m个字符串。你可以随便说一个字符串：

如果你在蓝色的字符串组中找到了这个字符串，就加一分；如果在红色的字符串组中找到了，就扣一分。

现在让你输出得分的最大值，且只有得分非负时才输出。

## 样例 #1

### 输入

```
3
apple
orange
apple
1
grape```

### 输出

```
2```

## 样例 #2

### 输入

```
3
apple
orange
apple
5
apple
apple
apple
apple
apple```

### 输出

```
1```

## 样例 #3

### 输入

```
1
voldemort
10
voldemort
voldemort
voldemort
voldemort
voldemort
voldemort
voldemort
voldemort
voldemort
voldemort```

### 输出

```
0```

## 样例 #4

### 输入

```
6
red
red
blue
yellow
yellow
red
5
red
red
yellow
green
blue```

### 输出

```
1```

# 题解

## 作者：Ninelife_Cat (赞：2)

`map` 是个好东西啊，会用它的话这题就能轻松过掉了。

如果不会的话请左转 [map的使用方法](https://www.cnblogs.com/ZY-Dream/p/10037931.html)。

主要思路就是通过 `map` 直接以一个字符串作为数组下标，如果是蓝组的字符串，就把得分加一，否则把得分减一，最后取个最大值就好啦。

核心代码：

```cpp
int n,m,ans;
string s[101],t;
map<string,int> cnt;
signed main()
{
	n=read();//快读什么的就不放了
	for(ri int i=1;i<=n;++i)
		cin>>s[i],++cnt[s[i]];//输入蓝组字符串并增加得分
	m=read();
	for(ri int i=1;i<=m;++i)
		cin>>t,--cnt[t];//输入红组字符串并减少得分
	for(ri int i=1;i<=n;++i)
		ans=max(ans,cnt[s[i]]);//取最大值
	cout<<ans;
	return 0;
}

---

## 作者：LucasXu80 (赞：2)

这道题的理解还是有一些难度的。来给大家详细地讲一下吧！

先来读题。这道题好像没有翻译，来给大家用翻译一下：

有两组字符串，一组蓝色，一组红色，各有n、m个字符串。你可以随便说一个字符串：

如果你在蓝色的字符串组中找到了这个字符串，就加一分；如果在红色的字符串组中找到了，就扣一分。

现在让你输出得分的最大值，**且只有得分非负时才输出。**

读懂了题目，怎么实现呢？

初步的思想一定是遍历蓝色的字符串组。

如果一个字符串在两组中都没有出现过，得分一定是0分，不可能是最高的；

如果一个字符串只在红组中出现了，得分是负分，更不用考虑了。

所以只要遍历蓝组就可以了！

这样这道题的核心就想通了。如果在蓝组中发现了与目标字符串相同的字符串（**包括自己！！！**），得分+1；如果在红组中发现了，得分-1。

核心部分讲完了，来看看细节。 _（以下部分dalao请略过）_ 

如何存储这些字符串呢？用一个叫字符串数组的东西：
```cpp
string s[101],t[101];
```
字符串数组中的每一项都是一个字符串。

好了，接下来就是完整代码了！大家可以先去做题再回来看代码（推荐），也可以利用我的代码加深理解！

```cpp
#include <bits/stdc++.h>//万能头文件！
using namespace std;
int main()
{
    string s[101],t[101];//定义字符数组，s代表蓝色，t代表红色
    int n,m;//分别代表蓝组和红组的个数
    cin>>n;
    for (int i=1; i<=n; i++)
    {
        cin>>s[i];
    }
    cin>>m;
    for (int i=1; i<=m; i++)
    {
        cin>>t[i];
    }
    //以上部分输入蓝组、红组
    int score=0,ans=0;//score记录一个目标字符串的得分，ans记录最终答案（也就是最大值）
    for (int i=1; i<=n; i++)//遍历蓝组中的每一项
    {
        //以下寻找对应的字符串
        for (int j=1; j<=n; j++)//遍历蓝组中的每一项
        {
            if (s[i]==s[j]) score++;//蓝组中找到了，加一分
        }
        for (int j=1; j<=m; j++)//遍历红组中的每一项
        {
            if (s[i]==t[j]) score--;//红组中找到了，扣一分
        }
        if (score>ans) ans=score;//如果分数大于目前最大值，说明这是一个更好的字符串，将ans赋值为现在的score
        score=0;//别忘了归零score！
    }
    if (ans>=0) cout<<ans<<endl;//只有当ans>=0时才输出，不要忘了哟~
    return 0;//AC代码完成！
}
```
好了，这道题就到这里了。希望对大家的解题有帮助！~~（大佬勿喷呜呜呜）~~

The end

---

