# Stones on the Table

## 题目描述

桌子上有N个石头，每一块都可以是红的、绿的或蓝的。计算从桌子上取下的石头的最小数量，以便任何两块相邻的石头都有不同的颜色。如果没有其他石头，一排石头被认为是相邻的。

## 样例 #1

### 输入

```
3
RRG
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
RRRRR
```

### 输出

```
4
```

## 样例 #3

### 输入

```
4
BRBG
```

### 输出

```
0
```

# 题解

## 作者：TianLuen (赞：5)

# CF266A C++题解
注：本题解在做法上相比其他题解有所改进
## 题目大意
- 有 $n$ 块石头
- 每一块石头都是红、绿、蓝（RGB） $3$ 种颜色之一
- 拿掉若干块石头，以做到相邻的石头颜色不同
- 求出拿掉石头的块数
## 题意分析
根据题意，即可得知，如果有一块石头与之前的那块石头颜色相同，就必须取走，否则将无法做到相邻石头颜色不同。

参考了此题其他题解，解法基本一致，此外此题应该也没有其他的常见解法了。

不过，我的解法，在空间上进行了优化。

其他的题解几乎都使用了线性数据结构，包括数组、字符串、队列、栈等等。那么，这题能不能不用这些数据结构而做到AC呢？可以。

### 空间优化方案
我们只需要两个字符变量，一个存储新输入的字符（颜色），另一个记录上一次输入的字符（颜色）。注意，每次需要更新记录上一次输入字符的变量。

这样，可以大大压缩原本使用数组所使用的空间。（遗憾的是，本题数据范围很小，因此效果不够明显。即使这样，我依然强烈建议，尽可能地压缩空间吧！）
## 代码
### 变量解释
|类型|变量名|用途|
|:-:|:-:|:-:|
|int|n|无用变量|
|int|sum|记录答案|
|char|a|存储新输入的字符|
|char|t|记录上一次输入的字符|
### AC代码
```cpp
#include<iostream>
using namespace std;
int n,sum;
char a,t;
int main()
{
    cin>>n;
    while(cin>>a)
    {
        if(a==t)
            sum++;
        t=a;
    }
    cout<<sum;
    return 0;
}
```
## THE END

---

## 作者：封禁用户 (赞：4)

# CF266A Stones on the Table 题解

> 这道题目如果用正常的字符串去做，有可能会有点难想，但是我们可以用stack（栈）来存储没有重复的字符串而不用去管里面的顺序，只需要对比栈顶就可以，因为这个字符串是有序的。

先来介绍一下stack的几种常用的方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/imwuiuhg.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/v1epzxtr.png)

这是几种栈常用的方法，我们就根据这个思路来做一下这道题目。

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//using
int main()
{
    stack<char>s;//STL栈定义，注意是char类型的
    int n,sum=0;//定义
    cin>>n;//输入
    for(int i=0;i<n;i++)//暴力循环枚举，注意这里，他已经告诉你了字符串的长度，所以可以枚举输入
    {
        char ch;//定义
        cin>>ch;//输入
        if(i==0) s.push(ch);//这里需要特判一下，如果是第一个字符串，前面没有比较的，所以直接入栈
        else//其他情况
        {
            if(ch==s.top()) sum++;//如果和栈顶元素比较，这个数字已经有了，直接退出
            else s.push(ch);//其他情况，插入栈里面
        }
    }
    cout<<sum;//输出被删除总数
    return 0;//华丽结束
}
```
> 补充，这里的栈等一下会有一个示意图，不了解的可以看下

![](https://cdn.luogu.com.cn/upload/image_hosting/wyundpku.png)

就是这样比较的。

学会了吗？

[Thomas_ 的博客](https://zyy-txws-noip.blog.luogu.org/)

原创，侵权必究

---

## 作者：林家三少 (赞：2)

	CF题+1
    
只需要一些简单的判断就行了，

	判断它前一个是否和它相同
    
但我一开始被坑到了，错在循环下标

	我一开始写的是：for(int i=1;i<st.size();i++)
    但这样是错的(勿抄
    
但只要我们加个东西

	for(int i=1;i<=st.size();i++)
    就是加个'='
    
马上就AC了！

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>  
using namespace std;
string st;  //定义字符串
int n,ans;  //定义变量
int main()
{
	cin>>n>>st;  //输入
	ans=n;  //ans赋值
	for(int i=1;i<=st.size();i++)//进入循环
	{
		if(st[i]!=st[i-1]) //来判断一下
			ans-=1;  //ans就减1
	}
	cout<<ans;  //最后输出
	return 0;
}
```


---

## 作者：微香玉烛暗 (赞：2)

这篇题解也许没有楼下简单，但是很实用！

```cpp
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>//万能头，不能用啊！！！
using namespace std;
typedef long long ll;
template<class AC>void r(AC &x){//AC,我从不手软！
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
string s;
int n,ans;
int main(){
    r(n);
    cin>>s;
    for(int i=0;i<n;i++)if(s[i+1]==s[i])ans++;
    cout<<ans<<endl;
    return 0;
}

```

就这样啦！
么么哒，886！爱你们！洛谷永远是我的家！！

---

## 作者：AlwaysForward (赞：0)

# 此题用 char 也许是很好的选择

浏览了一下其他题解，发现很多人都用的字符串，如果不告诉你长度，我认为使用 char 还是更方便。

```
	cin>>d[1];
	for(int i=2;i<=n;i++){
		cin>>d[i];
		if(d[i]==d[i-1])s++;
	}
```
核心代码如上。

为什么先要写一个 ```cin>>d[1]```？如果不这样，那就需要在下面另加一个判断 ```if(i>1)``` ，因为```i=1```时，```i-1=0```。其实也可以将 $d[0]$ 设为负数，因为没有一堆石头的数量是负数。或者这样也可以：
```
	for(int i=1;i<n;i++){
		cin>>d[i];
		if(d[i]==d[i+1])s++;
	}
```
然后就判断：当前这个是否与前一个/后一个相同。

代码双手奉上：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,s=0;
	cin>>n;
	char d[n+1];
	cin>>d[1];
	for(int i=2;i<=n;i++){
		cin>>d[i];
		if(d[i]==d[i-1])s++;
	}
	cout<<s<<endl;
}
```



---

## 作者：meyi (赞：0)

# 一道**~~(水)~~**题
## 思路：判断有多少相邻的相同字母
## 接下来上代码:
```cpp
#include<cstdio>
int a,d;//a就是题目中的n，d为计数器
char b,c;//这俩字符代替字符串s，b为当前字符，c为b的前一个字母
main(){
	scanf("%d",&a);//输入字符串长度
	while((b=getchar())=='\n');//过滤掉换行
	c=b;
    //由于过滤完换行后已经输入了字符串s的第一个字母，所以b从第二个字母开始，c赋值为b
	while(--a){	//因为已输入一个字母，所以只剩n-1个字母需要输入
		d+=((b=getchar())==c);//判断b是否等于c，这里用表达式省略了if
		c=b;//将c赋值为b
	}
	printf("%d",d);//输出
}
```

---

## 作者：该起什么名字 (赞：0)

这题就是判断有多少个连着的且相同的字母
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	int n,sum=0;
	cin>>n;
	cin>>s;
	//cout<<s;
	for(int i=0;i<n;i++)
	{
		if(s[i]==s[i+1]) 
			sum++;//判断是否满足条件 
	}
	cout<<sum;
	return 0;
}
```

---

