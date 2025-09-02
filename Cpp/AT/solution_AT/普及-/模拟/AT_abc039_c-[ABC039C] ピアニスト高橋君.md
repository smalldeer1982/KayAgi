# [ABC039C] ピアニスト高橋君

## 题目描述

题意描述
高桥君在一个钢琴键上，向右转，查看了20个键的颜色，问他所在的键是哪个？（钢琴键重复着白黑白黑白白黑白黑白黑白，音阶是 Do，#Do，Re，#Re，Mi，Fa，#Fa，So，#So，La，#La,Si）

## 样例 #1

### 输入

```
WBWBWWBWBWBWWBWBWWBW```

### 输出

```
Do```

# 题解

## 作者：JimmyF (赞：4)

    
因为钢琴键以12个键为一个周期，所以我们只需要截取前12个键就可以推出答案了。

可以使用打表策略，只要将12种情况对应的12种键的颜色，然后查找每一种情况，最后输出相对应情况的对应音阶即可。

解此题体分为4步骤：

1. 输入

2. 制表

3. 查找

4. 输出

### 献上代码：
	​```cpp
    #include <bits/stdc++.h> //文件头
    using namespace std;
    string st,st2;    //定义高桥君往右看到的字符串
    string st3[13]= 
    {
        {""},
        {"WBWBWWBWBWBW"},
        {"BWBWWBWBWBWW"},
        {"WBWWBWBWBWWB"},
        {"BWWBWBWBWWBW"},
        {"WWBWBWBWWBWB"},
        {"WBWBWBWWBWBW"},
        {"BWBWBWWBWBWW"},
        {"WBWBWWBWBWWB"},
        {"BWBWWBWBWWBW"},
        {"WBWWBWBWWBWB"},
        {"BWWBWBWWBWBW"},
        {"WWBWBWWBWBWB"},
    };
    //制12种的情况表
    string st1[25]={"1","Do","#Do","Re","#Re","Mi","Fa","#Fa","So","#So","La","#La","Si"};  //制音阶表
    int main()
    {
        cin>>st;  //输入字符串
        for(int i=0; i<=11; i++)
        st2+=st[i]; //截取前12位
        for(int i=1; i<=12; i++)
        if(st3[i]==st2){cout<<st1[i]<<endl;return 0;} //逐一查找，并输出
        return 0;
    }
    ​```
    
最后，洛谷提醒您：道路千万条，AC第一条，AT不换行，爆0两行泪！

---

## 作者：Cheese_int (赞：3)

## 题目传送门：
[AT1898](https://www.luogu.com.cn/problem/AT1898)

## 强调问题：
2022.10.06 : 在 AT 题库里千万别打多余的换行！！

如果你用 `scanf` 读入字符串的话，会报错，像这样：

```
scanf ("%s", s);
```

就会报错，因为 `scanf` 是 C 语言的，而 `string` 是 C ++ 的特性。

在考试中 RE 是我们最不想遇到的问题，所以为了我们的~~分数~~，我们在考试中读入字符串尽量就 `cin` 就可以了。如果觉得慢，~~就用快读优化一下~~。

#### 还有一个问题：

钢琴中是没有 **# Mi** 和 **# Xi** 的，所以打表不要把他们也打进去 。

## 思路：

读完了这道题，我的第一反应就是 **打表**，我们只需要把 **每一种情况** 罗列出来就可以了。看一下表格。

|  | 字母（起始） | 按键 | 答案（最终） |
| :-----------: | :-----------: | :-----------: | :-----------: |
| 1 | Do | WBWBWBWWBWBW | Fa |
| 2 | #Do | BWBWBWWBWBWW | #Fa  |
| 3 | Re | WBWBWWBWBWWB  | So |
| 4 | #Re | BWBWWBWBWWBW | #So |
| 5 | Mi | WBWWBWBWWBWB | La |
| 6 | Fa | BWWBWBWWBWBW | #La |
| 7 | #Fa | WWBWBWWBWBWB | Si |
| 8 | So | WBWBWWBWBWBW | Do |
| 9 | #So | BWBWWBWBWBWW | #Do |
| 10 | La | WBWWBWBWBWWB | Re |
| 11 | #La | BWWBWBWBWWBW | #Re |
| 12 | Xi | WWBWBWBWWBWB | Mi |

最后我们只需要按照上面的表格**模拟**一下就可以了。
我们来看一下代码。

## 代码：

```cpp

#include <bits/stdc++.h>

using namespace std;

string s;	//c++的好东西

int main () {
	
    cin >> s;
                  /*按照暴力打表求出此题*/
    if (s.substr (0, 12) == "WBWBWWBWBWBW")	printf ("Do");	
    if (s.substr (0, 12) == "BWBWWBWBWBWW")	printf ("#Do");
    if (s.substr (0, 12) == "WBWWBWBWBWWB")	printf ("Re");
    if (s.substr (0, 12) == "BWWBWBWBWWBW")	printf ("#Re");
    if (s.substr (0, 12) == "WWBWBWBWWBWB")	printf ("Mi");
    if (s.substr (0, 12) == "WBWBWBWWBWBW")	printf ("Fa");
    if (s.substr (0, 12) == "BWBWBWWBWBWW")	printf ("#Fa");
    if (s.substr (0, 12) == "WBWBWWBWBWWB")	printf ("So");
    if (s.substr (0, 12) == "BWBWWBWBWWBW")	printf ("#So");
    if (s.substr (0, 12) == "WBWWBWBWWBWB")	printf ("La");
    if (s.substr (0, 12) == "BWWBWBWWBWBW")	printf ("#La");
    if (s.substr (0, 12) == "WWBWBWWBWBWB")	printf ("Si");	
	
    return 0;
}
```

**暴力出奇迹。**

###### 求通过。

---

## 作者：a1a2a3a4a5 (赞：1)

## [AT1898](https://www.luogu.com.cn/problem/AT1898)：
### ①题意：

1.  我们会输入钢琴上 $ans$ 位置右数的 $20$ 个字符——表示琴键的颜色（只有黑 B  白 W ）求 $ans$ 位置琴键的音调。

1. 琴键颜色从琴最左端开始向右数总是循环的： `W B W B W W B W B W B W` 。

1. 琴键音符从琴最左端开始向右数总是循环： `Do #Do Re #Re Mi Fa #Fa So #So La #La Si` 。


### ②枚举：

1. 枚举每个位置：看 $i$ 位置右边的  $20$  个字符组成的字符串是否和输入的字符串一样，如果一样：说明  $i = ans$  则输出 $i$ 位置的音符。

1. 不管琴有无限的琴键，再往后枚举都是重复的，以规律中各个字符为开端枚举一回合就行了。

### ③优化：

1. 防止太多的 `if` ：预处理，存在数组里。

1. 访问越界：用  $\bmod$ 运算，或者把数组多复制几份。


### ④代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,o1="WBWBWWBWBWBW",
//琴键黑白色的规律
o2[12]={"Do","#Do","Re","#Re","Mi","Fa","#Fa","So","#So","La","#La","Si"};
//琴键音调规律
int main()
{
    cin >> s;
    for(int i = 0, l; i < 20; i + +)
    {
        l = 1;
        //l判断现在枚举的字符串是否与输入的字符串一样
        for (int j = 0; j < 20; j++)
        if(o1[(i + j) % 12] != s[j]) l = 0;
        //如果现在枚举的字符串与输入的字符串不一样就标记
        if(l == 1) {cout << o2[i % 12]; break;}
        //没有被标记过说明字符串符合题意，输出并结束
    }
    return 0;
}
```

---

## 作者：Escapism (赞：1)

模拟加打表题。

[题目传送门](https://www.luogu.com.cn/problem/AT1898)

# 题意

高桥在钢琴上。他可以看到他左边 $20$ 个琴键的颜色。现在他把这 $20$ 个键的颜色告诉了你。要你判断他在哪个键上。

# 思路

高桥君能看到 $20$ 个键，那么我们可以打一个字符串，包含了高桥君任何可能站在琴键上的前 $20$ 个键。

然后，我们只需要枚举这 $20$ 个键的位置，如果与打表内的相同，那么就是下一个键。

# 代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

string s,t;
int a[10] = {0,2,4,5,7,9,11};
string b[10] = {"Do","Re","Mi","Fa","So","La","Si"};

int main(){
	s = "WBWBWWBWBWBW";
	s = s + s + s + s + s + s + s; //打表
	cin >> t;
	for (int i=0;i<=6;i++)
		if (s.substr(a[i],20) == t){ //截取子串
			cout << b[i];
			break;
		}
	return 0;
}
```




---

## 作者：AirQwQ (赞：0)

## 思路

刚读完题就发现钢琴键 $12$ 个一循环，故知道前十二个，就可以直接推出来第 $20$ 个，所以就愉快地打表了。

## 实现

- 首先需要知道 [```substr```](https://baike.baidu.com/item/substr/10685875?fr=aladdin)。

- 接下来就是打（数）表（数）：


|    | 起始字母   |  对应键    |   对应答案 |
| -----------: | -----------: | -----------: | -----------: |
| 1  | Do  | WBWBWBWWBWBW | Fa |
| 2  | #Do  | BWBWBWWBWBWW | #Fa |
| 3  | Re  | WBWBWWBWBWWB | So |
| 4  | #Re  | BWBWWBWBWWBW | #So |
| 5  | Mi  | WBWWBWBWWBWB | La |
| 6  | Fa  | BWWBWBWWBWBW | #La |
| 7  | #Fa  | WWBWBWWBWBWB | Si |
| 8  | So  | WBWBWWBWBWBW | Do |
| 9  | #So  | BWBWWBWBWBWW | #Do |
| 10  | La  | WBWWBWBWBWWB | Re |
| 11  | #La  | BWWBWBWBWWBW | #Re |
| 12 | Si  | WWBWBWBWWBWB | Mi |

## Code

代码以第一种情况为例：
```cpp
if(s.substr(0,12)=="WBWBWBWWBWBW")
	cout<<"Fa";
```

所以写 $12$ 个 ```if``` 语句判断就好啦。~~（完整代码太丑就不放了）~~





---

## 作者：jimmyfj (赞：0)

可以发现，$12$ 个音阶为一个周期，我们以 `WBWBWWBWBWBW` 中的每一个音阶为开头，列举出所有的音阶顺序，再与输入的字符串的前 $12$ 位进行对比，符合哪一个就输出对应开头的音。

参考代码如下 :
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

string str;

int main()
{
    cin >> str;
    str = str.substr(0, 12);//截取输入的字符串的前 12 位
    printf( str == "WBWBWWBWBWBW" ? "Do\n" : ( str == "BWBWWBWBWBWW" ? "#Do\n" : ( str == "WBWWBWBWBWWB" ? "Re\n" : ( str == "BWWBWBWBWWBW" ? "#Re\n" : ( str == "WWBWBWBWWBWB" ? "Mi\n" : ( str == "WBWBWBWWBWBW" ? "Fa\n" : ( str == "BWBWBWWBWBWW" ? "#Fa\n" : ( str == "WBWBWWBWBWWB" ? "So\n" : ( str == "BWBWWBWBWWBW" ? "#So\n" : ( str == "WBWWBWBWWBWB" ? "La\n" : ( str == "BWWBWBWWBWBW" ? "#La\n" : "Si\n" ) ) ) ) ) ) ) ) ) ) );//把字符串与所有的音阶顺序进行对比
    
    return 0;
}
```


---

## 作者：makerlife (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT1898) | [AT 原题传送门](https://atcoder.jp/contests/abc039/tasks/abc039_c)

一道**简单的**打表题。

我们可以把题目给出的 $12$ 个音所对应的输入字符串先存好，然后直接字符串比对。

然后按照比对结果输出对应的音符即可解决本题。

## 代码

```cpp
#include<string>
#include<cstring>
#include<iostream>
using namespace std；
string s,str;
string s1[20]={"","WBWBWWBWBWBW","BWBWWBWBWBWW","WBWWBWBWBWWB","BWWBWBWBWWBW","WWBWBWBWWBWB","WBWBWBWWBWBW","BWBWBWWBWBWW","WBWBWWBWBWWB","BWBWWBWBWWBW","WBWWBWBWWBWB","BWWBWBWWBWBW","WWBWBWWBWBWB"};//输入给出的颜色打表
string s2[20]={"","Do","#Do","Re","#Re","Mi","Fa","#Fa","So","#So","La","#La","Si"};//对应的音符打表
int main()
{
	cin>>s;
    for(int i=0;i<=11;i++)
    {
        str+=s[i];//截取输入前 12 位
    }
    for(int i=1;i<=12;i++)
    {
        if(str==s1[i])//字符串比对
        {
            cout<<s2[i]<<endl;
            return 0;
        }
    }
	return 0;
}
```

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

这道题有不打表的方法，参见萤火·神龙的题解，我用的是打表的方法，我们可以打表每一种输入情况下他会输出的按键，但我们根据前12个按键的情况就可以推出第20个按键是什么音符了，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
string st1;
int main()
{
    cin>>st1;//输入
    if(st1.substr(0,12)=="WBWBWWBWBWBW")cout<<"Do";
    if(st1.substr(0,12)=="BWBWWBWBWBWW")cout<<"#Do";
    if(st1.substr(0,12)=="WBWWBWBWBWWB")cout<<"Re";
    if(st1.substr(0,12)=="BWWBWBWBWWBW")cout<<"#Re";
    if(st1.substr(0,12)=="WWBWBWBWWBWB")cout<<"Mi";
    if(st1.substr(0,12)=="WBWBWBWWBWBW")cout<<"Fa";
    if(st1.substr(0,12)=="BWBWBWWBWBWW")cout<<"#Fa";
    if(st1.substr(0,12)=="WBWBWWBWBWWB")cout<<"So";
    if(st1.substr(0,12)=="BWBWWBWBWWBW")cout<<"#So";
    if(st1.substr(0,12)=="WBWWBWBWWBWB")cout<<"La";
    if(st1.substr(0,12)=="BWWBWBWWBWBW")cout<<"#La";
    if(st1.substr(0,12)=="WWBWBWWBWBWB")cout<<"Si";
    //以上为枚举前12个按键然后推出第20个按键是什么音符的表
	return 0;
}

```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

