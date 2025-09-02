# Chord

## 题目描述

Vasya studies music.

He has learned lots of interesting stuff. For example, he knows that there are 12 notes: C, C#, D, D#, E, F, F#, G, G#, A, B, H. He also knows that the notes are repeated cyclically: after H goes C again, and before C stands H. We will consider the C note in the row's beginning and the C note after the H similar and we will identify them with each other. The distance between the notes along the musical scale is measured in tones: between two consecutive notes there's exactly one semitone, that is, 0.5 tone. The distance is taken from the lowest tone to the uppest one, that is, the distance between C and E is 4 semitones and between E and C is 8 semitones

Vasya also knows what a chord is. A chord is an unordered set of no less than three notes. However, for now Vasya only works with triads, that is with the chords that consist of exactly three notes. He can already distinguish between two types of triads — major and minor.

Let's define a major triad. Let the triad consist of notes $ X $ , $ Y $ and $ Z $ . If we can order the notes so as the distance along the musical scale between $ X $ and $ Y $ equals 4 semitones and the distance between $ Y $ and $ Z $ is 3 semitones, then the triad is major. The distance between $ X $ and $ Z $ , accordingly, equals 7 semitones.

A minor triad is different in that the distance between $ X $ and $ Y $ should be 3 semitones and between $ Y $ and $ Z $ — 4 semitones.

For example, the triad "C E G" is major: between C and E are 4 semitones, and between E and G are 3 semitones. And the triplet "C# B F" is minor, because if we order the notes as "B C# F", than between B and C# will be 3 semitones, and between C# and F — 4 semitones.

Help Vasya classify the triad the teacher has given to him.

## 样例 #1

### 输入

```
C E G
```

### 输出

```
major
```

## 样例 #2

### 输入

```
C# B F
```

### 输出

```
minor
```

## 样例 #3

### 输入

```
A B H
```

### 输出

```
strange
```

# 题解

## 作者：Zachary_Cloud (赞：5)

## $Sol$

~~这道题我被坑了好几次~~，题目中的 $|XY|$ 不是指它们乘积的绝对值，而是 $\large\color{red}\texttt{它们的差的绝对值}$！

$\texttt{Then}$，我们就可以~~愉快的打暴力了~~。

还有一个小注意点，每次都需要排序一下，当它们为 $\text{strange}$ 时，要把第一个音符提高八度，也就是 $+12$，然后再接着往下判断。

## $Code$

```cpp
#include <bits/stdc++.h>
using namespace std;
string gett[13] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "B", "H"}; //思路跟楼上差不多，根据字符串排序
string c1, c2, c3;
int a[4];
int main() {
	cin >> c1 >> c2 >> c3;
	for (int i = 0; i < 13; ++i) { //转为数字
		if (c1 == gett[i]) a[1] = i;
		if (c2 == gett[i]) a[2] = i;
		if (c3 == gett[i]) a[3] = i;
	}
	for (int i = 1; i <= 3; ++i) {
		sort(a + 1, a + 4); //排序
		if ((abs(a[1] - a[2]) == 4 && abs(a[2] - a[3]) == 3)) {cout << "major" << endl; return 0;} //判断为 major
        else if ((abs(a[1] - a[2]) == 3 && abs(a[2] - a[3]) == 4)) {cout << "minor" << endl; return 0;} //判断为 minor
		a[1] += 12; //第一个音符+=12
	}
	cout << "strange" << endl; //strange
	return 0;
}
```


---

## 作者：WNico (赞：4)

# [CF88A Chord](https://www.luogu.org/problemnew/show/CF88A)

[Blog](https://a-wnico-blog.blog.luogu.org/#)

## 题意

12个音符

C, C#, D, D#, E, F, F#, G, G#, A, B, H

当三个音符X,Y,Z满足

|XZ|==7,|XY|==4时是一个“major”和弦

当|XZ|==7,|XY|==3时是“minor”

都不是的就输出“strange”

（其实是自己交的翻译）

****注意****：输入的不一定按顺序，需要排序；如果比对出strange，将最小的音高八度比对（这个和乐理知识有关，我不太好解释）

## 解法

先把输入的三个音符（字符串）转成数字

排序

比对三个音符之间关系

如果是strange，将第一个音符提高八度（+=12）再进行比对

3次之后依然是strange就可以直接输出strange

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int rep(string s){						//音符转为数字
    if(s=="C") return 1;
    else if(s=="C#") return 2;
    else if(s=="D") return 3;
    else if(s=="D#") return 4;
    else if(s=="E") return 5;
    else if(s=="F") return 6;
    else if(s=="F#") return 7;
    else if(s=="G") return 8;
    else if(s=="G#") return 9;
    else if(s=="A") return 10;
    else if(s=="B") return 11;
    else if(s=="H") return 12;
    else return 0;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);							//cin加速
    
    string note;
    int a[3];
    cin>>note;
    a[0]=rep(note);
    cin>>note;
    a[1]=rep(note);
    cin>>note;							//输入字符串
    a[2]=rep(note);						//转为数字
    sort(a,a+3);						//排序
    int ans=0,cnt=3;;	
    while(!ans&&cnt){					//进行三次判断
        if(a[2]-a[0]==7){
            if(a[1]-a[0]==4) ans=1;		//判断major
            else if(a[1]-a[0]==3) ans=2;//判断minor	
        }
        a[0]+=12;						//重新排序
        sort(a,a+3);
        cnt--;
    }
    if(ans==1) cout<<"major";
    else if(ans==2) cout<<"minor";		//输出
    else cout<<"strange";
    return 0;
}
```


---

## 作者：yangyuanxi44 (赞：4)

这道题需要乐理知识。

这是一道模拟题，首先我们输入三个字符串，再转化相应的编号，将 3 个编号先排下序，这样就不用取绝对值了，下来枚举三个编号的两两组和（一共 3 组），如果符合 major 或 minor 直接输出即可，不符合将最小的编号加 12 （我也不知道为什么，这是乐理知识）再排下序，枚举玩所有情况后都不符合那就输出 strange。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2,s3;
int x,y,z,music[4],flag;
int change(string s){//转换
	if(s=="C")  return 1;
	if(s=="C#") return 2;
	if(s=="D")  return 3;
	if(s=="D#") return 4;
	if(s=="E")  return 5;
	if(s=="F")  return 6;
	if(s=="F#") return 7;
	if(s=="G")  return 8;
	if(s=="G#") return 9;
	if(s=="A")  return 10;
	if(s=="B")  return 11;
	if(s=="H")  return 12;
}
int main(){
	cin>>s1>>s2>>s3;
	music[1]=change(s1),music[2]=change(s2),music[3]=change(s3);
	sort(music+1,music+3+1);
	int T=3;
	while(T--){//枚举3种情况
		if(music[2]-music[1]==4&&music[3]-music[2]==3){
			cout<<"major"<<endl,flag=1;
			break;
		}   
		else if(music[2]-music[1]==3&&music[3]-music[2]==4){
			cout<<"minor"<<endl,flag=2; 
			break;
		}   
		else{
			music[1]+=12;//不符合+12
			sort(music+1,music+1+3);
		}
	}
	if(!flag)
	   cout<<"strange"<<endl;
	return 0;
}

```

谢谢大家阅读，感谢管理员的审核。

---

## 作者：ForeverHYX (赞：1)

# 题解006 CF88A
## 01 前置芝士 String

$string$ 是 $C++ STL$中自带的一种特殊数据类型，顾名思义，就是字符串。

而且最 $amazing$ 的就是 $string$ 支持整个字符串的比对，这样我们就可以快乐地直接知道输入字符串是哪个音啦！

## 02 本题算法

显而易见，我们先要对读入的音符进行处理，我们发现有一些音符像是 $C#$ 之类的超过了一个字符，所以我们需要使用 $string$ ，同时我们构造一个字符串数组，有序存储这张音符表。再通过枚举来得到这个音符的数字编号进行后续处理。

```cpp
cin >> ch1 >> ch2 >> ch3;
    for (int i = 0; i < 12; i++)
    {
        if (ch1 == rhy[i])//rhy=rhythm 有序存储音符
            place[1] = i;
        if (ch2 == rhy[i])
            place[2] = i;
        if (ch3 == rhy[i])
            place[3] = i;
    }//寻找输入音符的编号
```
但是观察样例我们发现输入并不一定严格有序，因此我们每次都需要排序（我使用的是冒泡）。

但是第二组样例中我们又发现可以先将一个音符移位12格再与别的音符进行比较。

既然这样，思路就很清晰了，多次移位+重新排序+重新比较。 _（次数我学习了另一篇题解，用的是三次，听说是乐理知识？好厉害。）_

## 03 AC代码

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
string rhy[13] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "B", "H"};
string ch1, ch2, ch3;
int place[4];
int flag;
int main()
{
    cin >> ch1 >> ch2 >> ch3;
    for (int i = 0; i < 12; i++)
    {
        if (ch1 == rhy[i])//rhy=rhythm 有序存储音符
            place[1] = i;
        if (ch2 == rhy[i])
            place[2] = i;
        if (ch3 == rhy[i])
            place[3] = i;
    }//寻找输入音符的编号
    for (int k = 1; k <= 3; k++)
    {
        for (int i = 1; i <= 3; i++)
        {
            for (int j = 1; j < i; j++)
            {
                if (place[j] > place[i])
                    swap(place[i], place[j]);
            }
        }
        if ((abs(place[1] - place[2]) == 4 && abs(place[2] - place[3]) == 3))
            flag = 1;//flag表示乐曲类型 1：major 2：minor 0：strange
        else if ((abs(place[1] - place[2]) == 3 && abs(place[2] - place[3]) == 4))
            flag = 2;
        place[1] += 12;
    }//多次循环判断乐符
    if (flag == 1)
        cout << "major";
    else if (flag == 2)
        cout << "minor";
    else
        cout << "strange";//结果判断
}
```

抄代码没有意义哟，建议看一遍再自己写。

 _本蒟蒻的第六篇题解，望管理员大大通过，同时祝所有人国庆，中秋快乐！！！_ 

---

## 作者：lidundun (赞：0)

# Chord
由于只有三个输入，可以暴力枚举一下，先把三个音符转为数字，然后排序一下，就开始检测。还要注意一下，每次判断完之后，把第一个字符变高 $8$ 度，然后继续判断，一共三次。
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t[4],mp[7][4]={0,0,0,0,0,1,2,3,0,1,3,2,0,2,1,3,0,2,3,1,0,3,1,2,0,3,2,1};
string a,b,c,s[13]={" ","C","C#","D","D#","E","F","F#","G","G#","A","B","H"};
int main()
{
	cin>>a>>b>>c;
	for(int i=1;i<=12;i++)
	{
		if(a==s[i])  t[1]=i;
		if(b==s[i])  t[2]=i;
		if(c==s[i])  t[3]=i;
	}
	for(int i=1;i<=3;i++)
	{
		sort(t+1,t+4);
		if(abs(t[1]-t[2])==4&&abs(t[2]-t[3])==3)
		{
			printf("major");
			return 0;
		}
		if(abs(t[1]-t[2])==3&&abs(t[2]-t[3])==4)
		{
			printf("minor");
			return 0;
		}
		t[1]+=12;
	}
	printf("strange");
	return 0;
}
```


---

## 作者：Fist_PROF (赞：0)

废话不多说直接讲题。

首先乐理知识要稍微有一点点，这里也差不多给出来了，按照题目的顺序，每个都从 $1$ 开始每个增加 $1$。

然后依照题意直接模拟。

这里直接用绝对值计算必然不太好计算，所以我们就给它做个排序，这样一来就可以免除用绝对值的复杂操作。

然后，注意，如果没有找到和弦的话，需要再接着算一遍！

AC 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int c(string s){
	if(s=="C")return 1;
	else if(s=="C#")return 2;
	else if(s=="D")return 3;
	else if(s=="D#")return 4;
	else if(s=="E")return 5;
	else if(s=="F")return 6;
	else if(s=="F#")return 7;
	else if(s=="G")return 8;
	else if(s=="G#")return 9;
	else if(s=="A")return 10;
	else if(s=="B")return 11;
	else if(s=="H")return 12;
}
int main(){	
	string s[55];
	int a[55];
	for(int i=1;i<=3;i++){
		cin>>s[i];
		a[i]=c(s[i]);
	}
	sort(a+1,a+4);
	for(int i=1;i<=3;i++){
		if(a[2]-a[1]==4&&a[3]-a[2]==3){
			cout<<"major"<<endl;
			return 0;
		}
		else if(a[2]-a[1]==3&&a[3]-a[2]==4){
			cout<<"minor"<<endl;
			return 0;
		}
		else{
			a[1]+=12;
			sort(a+1,a+4);
		}
	}
	cout<<"strange"<<endl;
	return 0;
}
```



---

## 作者：cyrxdzj (赞：0)

### 一、思路

本题其实涉及乐理知识。不过稍微了解一下就好了。

每个音符的编号对应表：

|音符|编号|
| :----------: | :----------: |
|$C$|$1$|
|$C\#$|$2$|
|$D$|$3$|
|$D\#$|$4$|
|$E$|$5$|
|$F$|$6$|
|$F\#$|$7$|
|$G$|$8$|
|$G\#$|$9$|
|$A$|$10$|
|$B$|$11$|
|$H$|$12$|

把输入的音符从大到小排序，并根据题意计算相邻两个音符编号之差，再根据题意输出 `major`、`minor` 或 `strange`。

需要注意，如果一次匹配不成功，则需要将最小的音符升八度（编号加 $12$），并再次排序、匹配。

### 二、完整代码

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int get_id(string str)//获取音符编号。
{
	if(str=="C")
	{
		return 1;
	}
	else if(str=="C#")
	{
		return 2;
	}
	else if(str=="D")
	{
		return 3;
	}
	else if(str=="D#")
	{
		return 4;
	}
	else if(str=="E")
	{
		return 5;
	}
	else if(str=="F")
	{
		return 6;
	}
	else if(str=="F#")
	{
		return 7;
	}
	else if(str=="G")
	{
		return 8;
	}
	else if(str=="G#")
	{
		return 9;
	}
	else if(str=="A")
	{
		return 10;
	}
	else if(str=="B")
	{
		return 11;
	}
	else if(str=="H")
	{
		return 12;
	}
}
int main()
{
	string input[3];
	int id[3];
	for(int i=0;i<3;i++)
	{
		cin>>input[i];
		id[i]=get_id(input[i]);
	}
	sort(id,id+3);//排序。
	for(int i=1;i<=3;i++)
	{
		if(id[1]-id[0]==4&&id[2]-id[1]==3)//匹配大调。
		{
			cout<<"major"<<endl;
			return 0;
		}
		else if(id[1]-id[0]==3&&id[2]-id[1]==4)//匹配小调。
		{
			cout<<"minor"<<endl;
			return 0;
		}
		else//未成功匹配。
		{
			id[0]+=12;
			sort(id,id+3);//重新排序。
		}
	}
	cout<<"strange"<<endl;
	return 0;//完结撒花！
}

```

### 三、后记

记录：<https://www.luogu.com.cn/record/52303007>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：xukaiyi_kaiyi (赞：0)

翻了好久题解，才发现这道题挺冷的。
# 首先明确乐理知识
## 键在键盘上是循环的
![](https://cdn.luogu.com.cn/upload/image_hosting/zdeuya3a.png)

~~拿出了我的FL~~

这样的话就有了新的思路！
# 准备

```cpp
#include<iostream>
#include<string>
using namespace std;
bool bucket[100];//标记是否可以按下某个键
const string note[13]={"","C","C#","D","D#","E","F","F#","G","G#","A","B","H"};
string temp;
int x,y,z;
```

# 输入

```cpp
void input(){
    cin>>temp;
    for(int i=1;i<=12;i++)if(temp==note[i])x=i;//暴力循环输入，这里本可以break掉，但由于时间宽裕，就省去了；
    cin>>temp;
    for(int i=1;i<=12;i++)if(temp==note[i])y=i;
    cin>>temp;
    for(int i=1;i<=12;i++)if(temp==note[i])z=i;
}
```

# 主函数

```cpp
signed main(){
    input();//输入
    for(int i=0;i<3;i++){//预处理
        bucket[i*12+x]=true;
        bucket[i*12+y]=true;
        bucket[i*12+z]=true;
    }
    for(int i=0;i<=36;i++){//循环判断
        if(bucket[i+1] && bucket[i+5] && bucket[i+8]){
            cout<<"major";
            return 0;
        }
        if(bucket[i+1] && bucket[i+4] && bucket[i+8]){
            cout<<"minor";
            return 0;
        }
    }
    cout<<"strange";
    return 0;
}
```
**由于我可能写的不是很清楚，所以再图解剖析一遍：**

输入：```C E G```

预处理：将每个八度的 ```C E G``` 都打上标记（不可能超过三个八度~~两个都不可能~~）

![](https://cdn.luogu.com.cn/upload/image_hosting/utxu5blg.png)

在标志中找有没有哪三个数能组成大调和弦或小调和弦，也就是——

大调（major）：是否能找到一个数$x$，使 $x+1$ , $x+5$ , $x+8$都被打上过标记（ $5-1=4,8-5=3$ ）；

小调（minor）：是否能找到一个数$x$，使 $x+1$ , $x+4$ , $x+8$都被打上过标记（ $4-1=3,8-4=4$ ）；

然后就是一个循环结构的事了。

都讲到这个地步了，应该能理解全部代码了吧；

else 私信我！

AC code:

```cpp
#include<iostream>
#include<string>
using namespace std;
bool bucket[100];
const string note[13]={"","C","C#","D","D#","E","F","F#","G","G#","A","B","H"};
string temp;
int x,y,z;
void input(){
    cin>>temp;
    for(int i=1;i<=12;i++)if(temp==note[i])x=i;
    cin>>temp;
    for(int i=1;i<=12;i++)if(temp==note[i])y=i;
    cin>>temp;
    for(int i=1;i<=12;i++)if(temp==note[i])z=i;
}
signed main(){
    input();
    for(int i=0;i<3;i++){
        bucket[i*12+x]=true;
        bucket[i*12+y]=true;
        bucket[i*12+z]=true;
    }
    for(int i=0;i<=36;i++){
        if(bucket[i+1] && bucket[i+5] && bucket[i+8]){
            cout<<"major";
            return 0;
        }
        if(bucket[i+1] && bucket[i+4] && bucket[i+8]){
            cout<<"minor";
            return 0;
        }
    }
    cout<<"strange";
    return 0;
}

```

# 后话：感谢管理员的审核！

---

