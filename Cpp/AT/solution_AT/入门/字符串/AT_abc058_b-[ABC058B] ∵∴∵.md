# [ABC058B] ∵∴∵

## 题目描述

すぬけ君新注册了一个编程竞赛网站的会员。由于他没有信心记住注册时使用的密码，所以决定把密码记在手边的纸上。不过，直接记下来可能会被别人偷看到密码，因此他决定将字符串中偶数位置的字符和奇数位置的字符分别记在不同的纸上。

现在给定只包含密码奇数位置字符且顺序未变的字符串 $O$，以及只包含密码偶数位置字符且顺序未变的字符串 $E$。请你帮すぬけ君还原出原始密码。

## 说明/提示

### 限制

- $O$ 和 $E$ 均为仅由小写英文字母（`a` - `z`）组成的字符串。
- $1 \leq |O|, |E| \leq 50$。
- $|O| - |E|$ 的值为 $0$ 或 $1$。

### 样例解释 1

将 `xaybzc` 的奇数位置字符取出得到 `xyz`，偶数位置字符取出得到 `abc`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
xyz
abc```

### 输出

```
xaybzc```

## 样例 #2

### 输入

```
atcoderbeginnercontest
atcoderregularcontest```

### 输出

```
aattccooddeerrbreeggiunlnaerrccoonntteesstt```

# 题解

## 作者：_•́へ•́╬_ (赞：4)

## 我的想法：输入一个字符就插入到原串里面
```cpp
#include<bits/stdc++.h>//懒人专用头文件
using namespace std;
string s;char c;
main()
{
    cin>>s;
    for(register int i=1;cin>>c/*一直输入*/;i+=2/*不能是++，刚刚插入的那个字符也算一个位置*/)s.insert(i,&c/*记住，要取地址*/);
    cout<<s;/*输入文件里有回车，所以不用手动添加endl*/
}
```

---

## 作者：chengni (赞：3)

这道题很简单，我的做的时候把题目认为难了，就是长度相差很多的两个字符串合成一个，但实际效果是一样的。

先找到长的和短的的长度，先一起输出，再输出剩下的就可以了。

```cpp
#include<bits/stdc++.h>

using namespace std;

char a[52],b[52];

int main(){
	cin>>a;
	cin>>b;
	int la=strlen(a),lb=strlen(b);
	int l=min(la,lb),ll=max(la,lb);
	for(int i=0;i<=l-1;i++)
		cout<<a[i]<<b[i];
	if(la>lb)
		for(int i=l;i<=ll-1;i++)
			cout<<a[i];
	else for(int i=l;i<=ll-1;i++)
			cout<<b[i];
	return 0;
}

```

---

## 作者：智子·起源 (赞：3)

#### “可笑名义上的监管，影身在迷雾之间。靠题解来获得存在感~~”

这道题思路还是非常简单的，而且没那么多细节。但我相信一些刚刚开始学习c++的同学可能还需要帮助。所以……
### 这篇题解是照顾刚开始学c++的新同学们的^_^
### 欢迎加入c++大家庭！^_^

首先，思路很简单。
既然题目说“a记录奇数位，b记录偶数位,保持其相对顺序，找到原字符串”那么我们就可以输出a[1],再输出b[1]，再输出a[2]，再输出b[2]，再输出a[3]，再输出b[3]……如此类推a、b数组交错进行输出。

## 就是暴力输出法。
接下来，是程序的详细解释（如果同学有一些格式错误或者想找一些程序写法的参考，可以看一下^_^）
```cpp
#include<iostream>
#include<string>
using namespace std;
string a,b;
int a_i,b_i;//"_"可以当做字符加入变量名，这样可以让思路更清晰^_^
int main()
{
  cin>>a>>b;//输入两个字符串。
  while(1)//while格式的无限循环
  {
    if(a_i!=a.size())//如果字符串a没有输出完
	{
	  cout<<a[a_i];//输出
	  a_i++;//将当前输出项坐标+1。
	}
    if(b_i!=b.size())//如果字符串b没有输出完
	{
	  cout<<b[b_i];//输出
	  b_i++;//将当前输出项坐标+1。
	}
    if(a_i==a.size()&&b_i==b.size())break;//如果两个字符串都输出完了，那就退出循环。
  }
  cout<<endl;//岛国题(AT题)要换行！！
  return 0;
}
```
### 题讲完了，希望大家都有所收获。

## 最后，祝各位新手的c++旅程中快乐成长！
#### 如果这篇题解帮助了你，妾身想让你帮忙点个赞，谢谢！^_^

---

## 作者：Purple_sword (赞：1)

这是一道蛮水的题目（~~我不会告诉你,我在长度方面卡了一次~~）
```cpp
#include<bits/stdc++.h>//万能头文件，洛谷的福利
using namespace std;
string a,b;//定义两个字符串
int main(){
    cin>>a;
    cin>>b;//输入字符串
    int x=a.size(),y=b.size();//记录两个字符串长度
    for(int i=0;i<y;i++){
        cout<<a[i]<<b[i];
    }//先按照不是长的那段输出
    if(x>y){
        cout<<a[x-1];
    }//如果长度不同再最后补上
    return 0;//结束！！
}
```

---

## 作者：yu__xuan (赞：1)

闲来无聊刷红题。~~即然是一道红题应该都是我这样的蒟蒻在做吧题解就写得详细一点吧！~~

~~这题竟然不用输出换行！~~

这题思路就是先读入两个字符串，然后开一个答案类型的char数组（a[100001]）.定义两个变量(js1=0,js2=1)一个赋值为零一个赋值为一。for第一个字符串将每个元素存入a[js1]每一次js1+2，for第二个字符串将每个元素存入a[js2]每一次js2+2。最后for a数组不为空就输出。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
using namespace std;
char a[100001];
char false1[10001],false2[10001];
int main()
{
	int js1=0,js2=1;
	cin>>false1>>false2;
	int na=strlen(false1),nb=strlen(false2);
	for(int sum1=0;sum1<na;++sum1,js1+=2)
		a[js1]=false1[sum1];
	for(int sum2=0;sum2<nb;++sum2,js2+=2)
		a[js2]=false2[sum2];
	int maxx=max(js1,js2);
	for(int i=0;i<=maxx;++i)
		if(a[i]!='\0') cout<<a[i];
	return 0;
}
```

---

## 作者：Aw顿顿 (赞：0)

这道题很简单

也就是先存储

然后在输出

看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100001],b,s[10000001];
int i=0;
int main()
{
	cin>>a;
	for(int j=0;j<strlen(a);j++)
	{
		s[i]=a[j];
		i+=2;
	}
	i=1;
	a[0]='\0';
	cin>>a;
	for(int j=0;j<strlen(a);j++)
	{
		s[i]=a[j];
		i+=2;
	}
	cout<<s<<endl;
	return 0;
}
```
这个代码AC了

希望大家~~多做水题啊~~



---

## 作者：StarLbright40 (赞：0)

兴致勃勃地做完题~提交~

结果一看题解。。。

四个长度变量？转换器？插入？

果然本蒟蒻无法理解dalao的世界~~我才不会告诉你是我不会~~

温馨提示：**做外国题不要只看翻译！**

因为数据范围通常都放在原文里边

那么现在我们来看一下数据范围（本蒟蒻强行凸显自己的作用）

1.**O and E consists of lowercase English letters (a - z)**

俩字符串全是小写字母（其实没啥影响）

2.**1 ≤ ∣O∣,∣E∣ ≤ 50**

长度最多50

3.**∣O∣ − ∣E∣ is either 0 or 1**（重点）

就是说：**俩字符串要么一样长，要么第一个比第二个多1**

~~所以用四个长度变量的dalao可以歇着了~~

（那么大家应该都会了吧）

上代码：

```
#include<bits/stdc++.h>//我爱万能头 
using namespace std;
char a[55],b[55];int l,i;
int main(){
	scanf("%s%s",a,b);
	l=strlen(b);//存储较小的长度 
	for(i=0;i<l;i++) printf("%c%c",a[i],b[i]);//交替输出 
	if(strlen(a)>strlen(b)) printf("%c",a[l]);//如果a长一点单独输出 
	printf("\n");//岛国题要换行 
	return 0;//再见 
}
```
（特别浅显是不是）

想抄也行，反正棕名也是自己作（貌似也没人抄）

---

## 作者：CZQ_King (赞：0)

这道题很简单，只要找到最大的长度，然后输出就可以了。
#### 值得注意的是，不要输出空字符

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100],b[100];//string也是可以的
int main(){
    cin>>a>>b;//char数组可以直接输入
    for(int i=0;i<max(strlen(a),strlen(b));i++){//循环到更大的长度(string用max(a.length(),b.length()))
        if(a[i]!='\0')cout<<a[i];//不要输出空的字符
        if(b[i]!='\0')cout<<b[i];//你也是
    }
    cout<<endl;//别忘了回车
    return 0;
}
```

---

## 作者：MaoHanKun (赞：0)

	#include<cstdio>//很简单的思路，输出一个字符串a，再输出一个字符串b，然后循环到结束。 
	#include<cstring>
	using namespace std;
	int a,b,a1,b1;//记录长度。 
	bool ok;//转换器。 
	char s[55],ss[55];
	int main(){
		scanf("%s%s",&s,&ss);//输入。 
		a=strlen(s);b=strlen(ss);//记录两个字符串的长度。 
		for(int i=0;i<a+b;++i){
			if(ok){//输出一个字符串b。 
				printf("%c",ss[b1]);//%c为输出单个字符。 
				b1++;
				ok=0;//转换。 
			}
			else{//输出一个字符串a。 
				printf("%c",s[a1]);
				a1++;
				ok=1;
			}
		}
		return 0;
	}//完美结束。 

---

## 作者：jeremyjy (赞：0)

这是一道入门题，但我先做错了

Reason：我使用了直接交替输出，本以为输到空字符评测机会自动跳过，结果就**WA**了！

上代码（有坑勿抄）：【复制】
```cpp
#include<bits/stdc++.h>//万能库
using namespace std;//使用名字空间
string a,b;//字符串定义
int main()//主程序
{
	int i;//定义
	cin<<a>>b;//输入
	for(i=0;i<max(a.size(叫你抄题解),b.size(叫你抄题解));i++)
	{
		cout<<a[i];//输出A串
		if(b[i]!=0)
			cout<<b[i];//与别人做法的difference：我是不断交替输出，遇到''再PD
	}
	cout<<endl;//岛国OJ要换行
	return 0;//华丽结束
}
```
抵制抄袭，共建和谐[洛谷](luogu.org)！

---

## 作者：封禁用户 (赞：0)

不解释上代码：
```pascal
var
    s1,s2,s3:ansistring;//数据可能很大，所以要用这个
    i:longint;
    b:boolean;
begin
    readln(s1);
    readln(s2);
    if(length(s1)<length(s2))then//判断最长的，好循环
    begin
        s3:=s1;
        s1:=s2;
        s2:=s3;
    end;
    if(length(s1)<>length(s2))then b:=true;//不等于就标记，不然少的那个会爆
    if(b)then
    begin
        for i:=1 to length(s1)-1 do//不等情况下
        begin
            write(s1[i],s2[i]);
        end;
        write(s1[length(s1)]);//要把没输出的补上
    end
    else
    begin
        for i:=1 to length(s1) do//正常情况
        begin
            write(s1[i],s2[i]);
        end;
    end;
end.


```


---

## 作者：Andysun06 (赞：0)

### 一道~~很简单~~的题，先用length()找到最长的长度和最短的长度，再输出配对得上的，最后输出剩下的。


------------
### 废话不多说，上代码（p党）：
    var i,j,n,m,kkk:longint;
        s1,s2,s3:string;
    begin
    readln(s1);//输入字符串
    readln(s2);
    i:=length(s1);//找到长度
    j:=length(s2);//同上
    if i<j then//找到最长的长度和最短的长度
    begin//交换
     n:=i;
     m:=j;
    end
    else
    begin
     n:=j;
     m:=i;
    end;
    for kkk:=1 to n do//输出配对得上的
    write(s1[kkk],s2[kkk]);
    if i>j then//输出剩下的
    for kkk:=n+1 to m do
    write(s1[kkk])
    else
    for kkk:=n+1 to m do
    write(s2[kkk]);
    writeln;//一定要换行!!!!!!!!
    end.
## 洛谷非常重视学术诚信！！！

---

## 作者：两年打铁 (赞：0)

这道题其实很~~简单~~，
可以让两个字符串中的每一位交替输出，就可以达到奇偶位的要求。
以下是代码。



------------
```
#include<bits/stdc++.h>
using namespace std;
char s[51],h[51];
int a,b,i,j;
int main()
{
	scanf("%s%s",s+1,h+1);
	a=strlen(s+1);
	b=strlen(h+1);
	if(a==b)//判断两个字符串长度是否相同，如果相同可以直接输出。
	{
		for(i=1;i<=a;++i)printf("%c%c",s[i],h[i]);
	}
	else //当然了如果不相同可以循环中不输出最后一位到最后补上。
	{
		for(i=1;i<=b;++i)printf("%c%c",s[i],h[i]);
		printf("%c",s[a]);
	}
	printf("\n");//换行。
}

```


---

## 作者：stry (赞：0)

这一题可以纯属爆枚，由于题目没有保证字符串a的长度==字符串b的长度，所以有两种情况，一种是字符串a的长度==字符串b的长度，这种情况就直接先输出字符串a的第i位在输出字符串b的第i位，for一直循环到字符串a的长度，第一种情况的暴力枚举就做完了。还有一种情况是字符串a的长度>字符串b的长度（因为没有奇数位会有偶数位吗），那么就输出字符串a的第i位和字符串b的第i位，一直循环到字符串a的位数-1（因为没有奇数位会有偶数位吗）最后在特别输出字符串a的最后一位，这样第二种方法就做完了。

### #注意，i不能再for里定义，因为输出要输出字符串a的第最后一位(也就是第i位)。
### #在for里不能在定义i了！！！
### #最后记得AT（岛国）题要换行！！！
程序如下：

```cpp
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
string st,stt;
int i=0;
int main()
{   
    cin>>st>>stt;
    if(st.size()!=stt.size())
    {
    for(i=0;i<st.size()-1;i++)
    {
        cout<<st[i]<<stt[i];
    }
    cout<<st[i];    
    }
    else
    {
    for(i=0;i<st.size();i++)
    {
        cout<<st[i]<<stt[i];
    }   
    }
    printf("\n");
    return 0;
}
```



---

