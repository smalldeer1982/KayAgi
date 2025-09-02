# Grasshopper And the String

## 题目描述

## 题意描述

一天，有一只蚱蜢正在草地上跳跃，它发现了一张纸，上面有一个字符串。蚱蜢感兴趣的是，它所需要的最小的跳跃能力是多少，才能跳到纸的另一端，它只会跳到元音字母上(为'A','E','I','O','U','Y')。

形式上，蚱蜢从字符串的最左边一个字符的左侧开始跳，目标是跳到最右边一个字符的右侧。蚱蜢的跳跃能力的值就是它跳跃的距离。跳跃能力最小为 $1$ 。

![](https://cdn.luogu.org/upload/vjudge_pic/CF733A/3d6ef82d52bf3bf3e745680bd25bf47489d98417.png)

如图，样例1中蚱蜢所需的最小跳跃能力为4。

## 样例 #1

### 输入

```
ABABBBACFEYUKOTT
```

### 输出

```
4```

## 样例 #2

### 输入

```
AAA
```

### 输出

```
1```

# 题解

## 作者：Alex_Wei (赞：26)

~~我也就只能写写水题的题解了~~

#### 思路：模拟，用一个整型变量a存放上一个元音的位置，初始值为-1（下标从0开始），每次遇到元音就更新答案，更新a

具体思路见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string p;
int a=-1,m;//m存放答案 
int main()
{
	cin>>p;
	for(int x=0;x<p.size();x++)
		if(p[x]=='A'||p[x]=='E'||p[x]=='I'||p[x]=='O'||p[x]=='U'||p[x]=='Y')//如果是元音 
			m=max(m,x-a),a=x;//更新a，如果长度比m大就更新m 
	cout<<max(m,(int)p.size()-a);//不要忘了判断最后一跳的长度 
	return 0;//望管理员通过 
}
```
#### 珍爱生命，远离抄袭

如果你觉得这篇题解不错，那就点个赞吧，谢谢！

---

## 作者：二字 (赞：4)

# 别说我蒟蒻，我觉得这是对于初学者字符串方面及编程思想提高的一道好题

## 我的方法不用从下标零开始或者两边加空格什么的

### 先看看本题的一个大“陷阱”就是：
# 元音包括a，e，i，o，u _还有Y_！！！

下面贴代码
```cpp
#include<bits/stdc++.h>//万能头

using namespace std;//命名空间用于cin和cout
int main(){
	string s;//这个字符串
	long long l=1,max=0;//l为连续非元音字符次数，max为最终输出结果，即最大连续次数
	getline(cin,s);//读入字符（其实cin也可以）
	for(int i=0;i<=s.length()-1;i++){//省略最后一个字符，为什么请看后面
		if(s[i]!='A'&&s[i]!='Y'&&s[i]!='E'&&s[i]!='I'&&s[i]!='O'&&s[i]!='U'){//如果不是元音
			l++;//连续值增加
		}
		else l=1;//注意l的初始值为1因为即使是俩元音相邻l的值也应为1，因此要少检测一个字符即最后一个字符
		if(l>max) max=l;//你懂的
	}
	cout<<max;//输出
} 
```

---

## 作者：不到前10不改名 (赞：2)


```
#include<stdio.h>
#include<string.h>
int i,t=-1,sry;//注意，如果你在第四个点搞死没有过去，请把t值赋为-1，因为这里如果你按照字符串的0~n-1来算的话起始点就在-1处
char srx[1001];
int max(int x,int y)
{
    if(x>y)
    return x;
    return y;
}
int main()
{
    scanf("%s",srx);
    for(i=0;i<strlen(srx);i++)//当然你也可以学习另一位大佬把数组转换为1~n，就没这么麻烦了
    if(srx[i]=='A'||srx[i]=='E'||srx[i]=='I'||srx[i]=='O'||srx[i]=='U'||srx[i]=='Y')//符合元音字母（数据合法，都是大写）
    {sry=max(i-t,sry);//最大能力，不要被题面的最小（1）给迷惑了！
    t=i;}//记录起始点
    sry=max(sry,strlen(srx)-t);//因为前面起始点并未落下，应该落到最后一点，也就是点n（1~n的话是n+1），再判断一下，也不用加if，如果最后一个是的话就是1，没有影响
    printf("%d",sry);
    return 0;
}
```

---

## 作者：XMK_萌新 (赞：1)

没有什么事枚举没有解决的问题，如果有，那就用**二分**。

~~但好像顺序枚举不会T啊【滑稽】~~

~~但为了把事情弄复杂，~~
二分蚱蜢跳的最大距离，然后暴力。。

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int l=1,r,mid;
string t="a",s;
bool check(int q)
{
    int fwd=0;	//距离上一个元音有多少距离
    for(int i=1;i<t.size();i++)
    {
        fwd++;	//往前推进一格
        if(fwd>q) return false;	//已经无法跳到此格
        if(t[i]=='A'||t[i]=='E'||t[i]=='I'||t[i]=='O'||t[i]=='U'||t[i]=='Y') fwd=0;	//调到元音，清零
    }
    return true;	//每个格子都能调到
}
int main()
{
    cin>>s;
    r=s.size()+2;
    t+=s;
    t+='a';
    //在字符串首位都补个位
    while(l<r)	//二分！！！
    {
        mid=(l+r)/2;
        if(check(mid)) r=mid;	//如果以mid来跳，能符合要求，把右边界锁定
        else l=mid+1;	//锁定左边界为一个大于mid的数
    }
    cout<<l;
    return 0;
}
```

---

## 作者：OdtreePrince (赞：1)

# -模拟-

纯粹就是字符串+模拟，因此找出弹跳最大值，输出就行。

可以用while循环解决，这里我就用了for循环解决，大家值得一看，但是循环结束后还要再进行答案更新哦。

~~~
#include<bits/stdc++.h>
using namespace std;
string s;
int check(int i){
    if(s[i]!='A'&&s[i]!='E'&&s[i]!='I'&&s[i]!='O'&&s[i]!='U'&&s[i]!='Y') return 0;
    return 1;
}
int main(){
    cin>>s;
    int l=s.size();
    int i=0,maxx=0;
    while(!check(i)&&i<s.size()) i++;
    maxx=i+1;
    for(int j=i+1;j<s.size();j++){
        if(check(j)) maxx=max(maxx,j-i),i=j;
    }
    maxx=max(maxx,l-i);
    cout<<maxx;
    return 0;
}
~~~

---

## 作者：ShineEternal (赞：0)

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
char s[10001];
int main()
{
    gets(s);
    int pd=0;
    int ans=1;
    int m=strlen(s);//先记录下来
    for(int i=m-1;i>=0;i--)//本人喜欢下标从1开始，但转化的时候切记要从后往前
    {
        s[i+1]=s[i];
    }
    for(int i=1;i<=m;i++)
    {
        if(s[i]=='A'||s[i]=='E'||s[i]=='I'||s[i]=='O'||s[i]=='U'||s[i]=='Y')
        {
            ans=fmax(ans,i-pd);
            pd=i;//pd记录当前位置
        }//一个一个距离的取最大值
       
    }
    if(pd!=m)
    {
        ans=fmax(ans,m+1-pd);
    }//判断最后一个是不是元音字母
    printf("%d",ans);//输出
    return 0;
}
```

---

## 作者：Thomas_Cat (赞：0)

UPDATE:不好意思，之前提交代码的时候少了y，我谢罪

这题太水了，直接输入之后循环比较一次即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool check(char ch){//检查函数，判断是否为元音
    if(ch=='A'||ch=='E'||ch=='I'||ch=='O'||ch=='U'|| ch=='Y') return 1;
    return 0;
}
int main(){
    char ch[200];//定义
    cin>>ch;//输入
    int flag=0,MAX=INT_MIN;//MAX定义最小值，不会翻车
    for(int i=0;i<strlen(ch);i++)//循环判断
        if(check(ch[i])) //如果是元音
        {
            if(i-flag>MAX)  //如果这个距离更大
            {
                MAX=i-flag;//替换距离
            }
            flag=i;//同上
        }
    cout<<MAX;//我谔谔，输出答案
    return 0;//华丽结束
}
```

---

