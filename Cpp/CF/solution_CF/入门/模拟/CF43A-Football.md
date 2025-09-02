# Football

## 题目描述

One day Vasya decided to have a look at the results of Berland 1910 Football Championship’s finals. Unfortunately he didn't find the overall score of the match; however, he got hold of a profound description of the match's process. On the whole there are $ n $ lines in that description each of which described one goal. Every goal was marked with the name of the team that had scored it. Help Vasya, learn the name of the team that won the finals. It is guaranteed that the match did not end in a tie.

## 样例 #1

### 输入

```
1
ABC
```

### 输出

```
ABC
```

## 样例 #2

### 输入

```
5
A
ABA
ABA
A
A
```

### 输出

```
A
```

# 题解

## 作者：Ajwallet (赞：11)

# 本题史上最短代码，没有之一！
思路和楼下一样，都是利用C++STL中自带的$map$库（映射）

就是可以定义任意类型下标，值也可以是任意类型的数组或变量（任意类型包括结构体，STL的其他库等，也可以嵌套$map$成为二维数组）

定义方法

$map<typename,typename>yourname$;

第一个typename是下标类型，第二个是值的类型，yourname是变量名或数组名

# 代码
```cpp
#include<map>
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;int n,maxn;//maxn为进球最多的那个球队进球数，n为进球次数
map<string,int>s;string ans,k;//s表示每支球队进球几个，ans表示进球最多的那个球队，k为输入的球队
int main()
{
	scanf("%d",&n);
	while(n--)
	 {
     	cin>>k;s[k]++;//输入，并且此队进球
     	if(s[k]>maxn) {maxn=s[k];ans=k;}
     }
	cout<<ans;//输入
}
```

---

## 作者：wubaiting2020 (赞：7)

答题思路：先读入一个，存下来，后面继续读，如果一样就加第一个，不然就加第二个，顺便把第二个队存下来
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() 
{
    int n,a1=0,a2=0;string a,b,s;
    cin>>n;
    cin>>s;//先读入一个
	a=s;//存下来
	a1++;//第一队得分+1
    for(int i=2;i<=n;i++)
    {
    	cin>>s;
		if(s==a)a1++;//如果是第一队，第一队得分+1
		else {a2++;b=s;}//否则是第二队，并存第二队队名
	}
	if(a1>a2)cout<<a;//比较得分
	else cout<<b;
    return 0;
}
```

---

## 作者：rmolives (赞：7)

可能用Kotlin写的很少见吧

```
import java.util.*

fun main(args: Array<String>) {
    val sc = Scanner(System.`in`)
    val a = sc.nextInt() - 1
    val b = sc.next()
    var c = 0
    var d = 0
    var e = ""
    for (i in 1..a) {
        val f = sc.next()
        if (f != b) {
            e = f
            c++
        } else
            d++
    }
    if (c > d)
        println(e)
    else
        println(b)
}

```

---

## 作者：char32_t (赞：3)

# 题解 CF43A 【Football】
------------
这道题其实只是一道简单的计数问题，但难点在于如何分别获取两支队伍的名字（因为不能保证前两个名字不同，即可能前两分由同一支队伍获得），那么我们可以转换一下思路，只维护第一支进球的队伍的得分，又因为不会出现平局的情况，所以另一支队伍的得分就是总进球数减去第一支队伍的分数。

Code：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
struct team {
	string name;//队名 
	int grade;//得分 
} t[2];//使用结构体存储两只队伍 
string str;//中转字符串 
int main() {
	int n;
	scanf("%d", &n);//输入总得分 
	cin>>t[0].name;//获得第一支进球队伍的名字 
	t[0].grade++;//得分加1 
	for(int i=1; i<=n-1; i++) {
		cin>>str;//获得第二支进球队伍的名字 
		if(str!=t[0].name) t[1].name=str;//如果和第一支进球队伍的名字不同，就是第二支队伍的名字 
		else t[0].grade++;//否则是第一支队伍的进球，分数加1 
	}
	if(t[0].grade>n-t[0].grade) cout<<t[0].name;//如果第一支队伍得分更高，则输出第一支队伍的名字 
	else cout<<t[1].name;//否则输出第二支球队的名字 
	return 0;
}
```

---

## 作者：览遍千秋 (赞：2)

map模板题

需要掌握迭代器

代码：

```cpp
#include<bits/stdc++.h>  //头文件
using namespace std;
int n,maxx;
map<string,int>mp;//定义一个map
string s,ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        mp[s]++;//统计所有球队的分值
    }
    for(map<string,int>::iterator it=mp.begin();it!=mp.end();it++)//遍历所有map
    {
        if(it->second>maxx)//second是它的值
        {
            maxx=it->second;
            ans=it->first;//first是定义时的string类型
        }
    }
    cout<<ans<<endl;
}
```

该代码可以支持不止两支球队的情况

---

## 作者：hewo (赞：1)

这道题我用结构体a,b来存两个队伍。本身思路就是模拟，所以思路详见代码：

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
struct tTeam{
	int hs;
	string name;
	tTeam()
	{
		hs=0;//胜场 
		name="CZ";//初始名字，作用见下 
	}//初始化 
}a,b;
int main()
{
	
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string x;
		cin>>x;
		if(b.name=="CZ"||a.name=="CZ") //只要有一个为初始名字 
		{
			if(a.name=="CZ")//优先存a 
			{
				a.name=x;//有下面的东西，无需a.hs++; 
			}
			else if(b.name=="CZ"&&x!=a.name)//当b为初始且不是a的名字时 
			{
				b.name=x;
			}
		}
		if(a.name==x) a.hs++;
		else if(b.name==x)b.hs++;
	}
	if(a.hs>b.hs) cout<<a.name<<endl;//比较 
	else cout<<b.name<<endl;
	return 0;
}
```

**要注意赋值b.name时应判断与a不一样**

比如前2个输入A A，a.name与b.name便会均为A


错误代码
```cpp
else if(b.name=="CZ")
	{
		b.name=x;
	}
```



---

## 作者：不到前10不改名 (赞：1)

//泥萌永远不知道一个纯c党的悲痛......   
//代码错了，没人帮查   
//函数大部分全靠手打，没有STL，string不知比char先进了几倍   
//这么水的一道题我还能做那么多变，真是无语
```
#include<stdio.h>
#include<string.h>
int n,i,mzy,zjq;
char srx[21],sry[21],lhy[21];
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {scanf("%s",&srx);
    if(!sry[0])
    strcpy(sry,srx);//为什么要先输入一个呢，这样也可以！
    else if(!lhy[0]||strcmp(srx,sry)!=0)//虽然因为这个原因狂wa7次，加一个CMP的原因是防止前两个进球为同一球队，若先输入一个呢就可以避免（然鹅我并没有）
    strcpy(lhy,srx);//复制
    if(strcmp(srx,sry)==0)/也就这种比较的破函数才能用了，哎
    mzy++;//累加进球数
    else
    zjq++;}
    if(mzy>zjq)
    printf("%s\n",sry);
    else
    printf("%s\n",lhy);
    return 0;
}
```

---

## 作者：Register (赞：1)

# 没读题。。。
之前由没读题，所以就写了个支持100个球队的代码

### 每个球队最后的数据都是由名字和进球颗数组成的

	当又有XX队进球时我们就要遍历每一个已进球的球队
    如果找到了，那就让该球队的进球数+1
    否则，新增一个球队，将进球数设为1

最后，用sort比出进球最多的队

奉上代码：
```cpp
#include <iostream>//输入输出流库
#include <string>//我也不知道我为什么要加
#include <algorithm>//sort STL大法好
using namespace std;//cin、cout、sort都要用
struct team{//球队类型结构体
	int sum;
	string name;
};
bool comp(const team &a,const team &b){//comp大家都会写吧。。。
	return a.sum>b.sum;
}
int main(){
	team a[101];//定义球队
	int n,t=0/*记录球队总支数的*/;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string s;//XX球队名字临时储存
		cin>>s;
		int j=t+1;//不加1到时后会少算目前置顶的
		bool flag=false;//判断是否需要新增
		while(--j)//从上到下遍历
			if(a[j].name==s)/*找到了*/ {a[j].sum++;/*那个球队多进一个球*/flag=true;break;}
		if(!flag) {a[++t].name=s;a[t].sum=1;}//还没找到就新增球队
	}
	sort(a+1,a+t+1,comp);//sort
	cout<<a[1].name<<endl;//输出大佬的名字
	return 0;
}
```

---

## 作者：Andysun06 (赞：1)

# 题解 CF43A 【Football】：
## 只要就一个个累加出现球队的次数
#### pascal题解：
    var a,b,c:string;
        n,m,i,j:longint;//n，m用来累加球队赢的次数
        x:array[1..10000]of string;    
    begin 
    readln(j);  
    readln(x[1]);//输入x【1】 
    a:=x[1];  //x[1]一定是两个中的一个球队
    for i:=2 to j do//输入x【i】   
    begin    
     readln(x[i]);     
     if x[i]<>a then  //如果发现了另一个球队    
      b:=x[i];//记录下来      
    end;    
    for i:=1 to j do//进行累加  
     if x[i]=a then  //如果球队赢了 
      n:=n+1
    else    
     m:=m+1;    
    if n>m then//如果第一个球队赢了  
     writeln(a)  //输出球队一 
    else   //否则
    writeln(b); //输出球队二 
    end.

---

## 作者：wushuang0828 (赞：0)

## **题目很水，用桶排就可以AC**

    这道题也没有什么坑，所以也不用什么特判，就是球队的名字麻烦了些。
    所以我用了一个数组，这种方法比较通用。
    废话不多说，上代码：
```pascal
var
 n,i,j,s,sum:longint;
 a,b:array[0..100] of string;
begin
 readln(n);//输入
 for i:=1 to n do
  begin
   readln(a[i]);//输入球队名称
   if a[i]<>b[j] then begin inc(j); b[j]:=a[i]; end;//其实这里应该是要一个循坏来判断的，但是这里只有两个球队，所以只用一个if也是可行的
  end;
 for i:=1 to n do
  begin
   if a[i]=b[1] then inc(s);//判断，并累加
   if a[i]=b[2] then inc(sum);//判断，并累加
  end;
 if s>sum then writeln(b[1])
          else writeln(b[2]);//比较大小输出大的数
end.//完美结束
```

---

## 作者：Konjaku_百分百 (赞：0)

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,a[10];//定义n个数，和数组（要开大点，不然会运行错误）
string s,x,y;//定义三个字符串，方便后面做题
int main()
{
 //freopen(".in","r",stdin);
 //freopen(".out","w",stdout);
 cin>>n;//输入有多少个数
 cin>>s;//先输入一个字符串，方便存储
 x=s;//存储第一个字符串先
 a[1]++;//a[1]存着第一个s字符串
 for(int i=2; i<=n; i++)//循环
 {
  cin>>s;//输入字符串
  if(x!=s)//如果第一个字符串不等于s[i]字符串
  {
   a[2]++;//那就a[2]数组加1
   y=s;//那y就存储着与x不同的字符串
  }
  else a[1]++;//如果不是这样的话，a[1]数组+1
 }
 if(a[1]>a[2]) cout<<x;//如果a[1]的个数也就是x的个数大于a[2]也就是y，那就输出x字符串
 else cout<<y;//如果不是这样的话，那就输出y字符串
 return 0;//结束程序
}
```

---

## 作者：Aehnuwx (赞：0)

**这道题只是处理有一小点麻烦，就是一个字符串+模拟。**

我用的是最最朴素的方法了，dalao勿喷。

先定义三个字符串（不是字符数组！），前两个用于输出判断（没错！就是这样！），最后一个才是输入用的。

再定义两个整型的变量，用于保存进球数。

哎，算了，讲的太麻烦，在代码里讲的更清楚。

$code$

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
string str1, str2;
string goal; //三个字符串
int n, score1 = 0, score2 = 0;//n和保存进球数的变量
void print();
int main() {
	scanf("%d", &n);
	cin >> goal;
	score1 ++;
	str1 = goal;//一进去第一个进球就默认为是第一个球队进的球，将这个球队的名字存放到str1里。输出的时候用
	for(int i = 2; i <= n; i ++) { //所以现在for循环就从2开始循环了
		cin >> goal; //再输入
		if(goal != str1) {
			score2 ++;
			str2 = goal;
		}
		else {
			score1 ++;
			str1 = goal;
		}
  		//上面是判断进球的球队是1号球队还是2号球队，并将进球球队加1分
	}
	print(); //输出函数，当然你可以直接在主函数里写
	return 0;
}
void print() {
	if(score1 > score2) cout << str1;
	else cout << str2;
  	//输出得分高的那一队
}
```

---

## 作者：PC_DOS (赞：0)

使用一个由字符串对应到整数的map(~~用惯了.NET我喜欢叫它字典~~)记录比分(标识符mapScore)，每读入一个队伍名字sInput就让mapScore[sInput]的值加一。

map属于STL中的内容，使用时需要:
```
//#include <map>
```

map的定义方法为:
```
//map<键类型,内容类型> 标识符;
```

依照键访问map中的内容的方法为:
```
//标识符[键名];
```

于是可以得到代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //关闭与STDIO的同步，提高输入输出的效率
	string sTeam1(""), sTeam2(""), sInput; //分别定义两支队伍的名字和暂存输入的字符串
	map<string, int> mapScore; //定义从字符串到整数的map
	int nCount,i; //nCount-输入个数，i-循环变量
	cin >> nCount; //读入个数
	getline(cin, sInput); //读取掉输入nCount后留下的不需要的东西
	getline(cin, sInput); //读入第一支队伍的名字
	sTeam1 = sInput; //保存第一支队伍的名字
	++mapScore[sInput]; //第一支队伍加一分
	for (i = 2; i <= nCount; ++i){ //从第二条记录开始读
		getline(cin, sInput); //读入记录
		if (sInput != sTeam1 && sTeam2==""){ //如果第二支队伍还没有名字
			sTeam2 = sInput; //保存第二支队伍的名字
		}
		++mapScore[sInput]; //读入的队伍得分加一
	}
	if (mapScore[sTeam1] > mapScore[sTeam2]){ //判断谁的得分高并输出胜利者，由于题目给定不存在平局，所以没有处理平局。
		cout << sTeam1;
	}
	else{
		cout << sTeam2;
	}
	return 0; //结束
}
```

---

## 作者：panda_wang (赞：0)

# 【题意】
### 读入一个数N，然后输入a[n]个字符(字符串)，分别为进球球队的名字，输出赢得那一队的球队名称
### 注意(将关乎整个题目的做法)：题目中说是两个球队（重点在【题目分析】中会提到）
# 【解决方案】
### 使用语言：Python3
### 解决方法：从头开始，遍历整个字符串数组，当读到与临时变量（fname）不同的值时，将名称存入sname，将进球数存入sec。当读到与临时变量（fname）相同的值时，将进球数存入fid。
### 代码：
```Python3
    x = int(input())
    s = []
    
    fid = 0
    sec = 0
    
    for fr1 in range(x):
    s.append(input())
    
    fname = s[0]
    sname = " "
    
    for fr2 in range(x):
    if (s[fr2]==fname):
    fid=fid+1
    else:
    sname = s[fr2]
    sec=sec+1
    
    if fid>sec:
    print(fname)
    else:
    print(sname)
```
# 【题目分析】
### 1.为什么只用定义两个进球数,和两个名称呢？
### 1.答：这里是本题最大的坑点之一，是考验大家细心的一个地方，题目中都已经提到
> 保证只有两个球队
### 那，就只用定义两个进球数，和两个名称了。
# 【坑点分析】
### 1.if语句：请读【题目分析】


---

