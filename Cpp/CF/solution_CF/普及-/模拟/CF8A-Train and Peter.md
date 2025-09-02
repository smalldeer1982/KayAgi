# Train and Peter

## 题目描述

Peter 很喜欢坐火车去旅行。他实在是太喜欢坐火车了，以至于在火车上睡着了（雾）。

在一个夏天，Peter 正在一个从 A 城开往 B 城的列车上。像往常一样，他睡着了。突然，他醒了过来（?），开始看窗外的景物。他发现每一个火车站都有一面彩旗（旗上只有一种颜色）。

Peter 开始记忆他看到的彩旗的顺序。但是很快地，他又睡着了。不幸地，他没睡多久又醒来了，并且他开始继续记他看到的彩旗。一段时间以后，他又睡着了，这次直到旅途结束都没醒来。

到站以后，他告诉了他的父母他在旅途中看到的彩旗的顺序——在他中途睡着之前和中途睡着之后分别看到的两个颜色序列。

他的父母知道 Peter 特别喜欢幻想，所以他们把 Peter 说的序列给了你，并请你判断他的乘车方向。

他的父母用不同的小写字母表示不同的颜色。相同字母表示相同颜色，不同字母表示不同颜色。

## 说明/提示

列车一直都在移动，所以一面同样的旗子不可能被看到两次。

## 样例 #1

### 输入

```
atob
a
b
```

### 输出

```
forward
```

## 样例 #2

### 输入

```
aaacaaa
aca
aa
```

### 输出

```
both
```

# 题解

## 作者：SIXIANG32 (赞：8)

貌似有很多人正最短题解，但是目前看来我的码量似乎最少，长度也是最短。（大雾（准备好被打脸。  
闲话少说，切入正题——


------------
题目看起来很饶人，我们一起来把~~恶臭的~~题面简化一下：  
> 在母串中**依次**查找 $s1$ 和 $s2$ 或者在反转中的母串**依次**查找 $s1$ 和 $s2$。  

为什么是依次呢？因为 Peter 不可能在看到 $s2$ 之前看到 $s1$ ~~否则 Peter 怕不是个透视眼外星人。~~  

把题意概括了，那么我们基本上可以构造一个简单的思路，就是先在原串中先查找 $s1$ 再查找 $s2$，然后再在反转后的原串重复这一操作。对于每个操作的答案进行判断并输出。  


------------
既然构造好了解决的算法，我们就要考虑如何用程序实现。  
Q1：用什么类型存储？  
A1：```string``` 字符串类型，自带 STL 各种神仙的~~常数大的~~函数。 

Q2：怎样查找？  
A2：运用 ```string``` 中的 ```find``` 函数进行查找。如果要查找某字符串 / 字符第一次出现的位置，可以这样写：```母串.find(要查找的字符串)```。如果要查找某个在 $pos$ 位置后的字符串的位置，可以这样写：```母串.find(pos,要查找的字符串)```。  

Q3：怎样反转？  
A3：运用 STL 的 ```reverse``` 函数！  

~~也就是说这个就是个 STL 应用题对不对（~~  


------------
上 9 行的代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{ 
	string s1,s2,s3,cs1;
	cin>>s1>>s2>>s3,cs1=s1,reverse(cs1.begin(),cs1.end());
	int pos1=s1.find(s2),pos2=cs1.find(s2),f1=s1.find(s3,pos1+s2.size()),f2=cs1.find(s3,pos2+s2.size());
	cout<<((pos1==-1&&pos2==-1)?("fantasy"):((f1!=-1&&f2==-1)?("forward"):((f1==-1&&f2!=-1)?("backward"):((f1!=-1&&f2!=-1)?("both"):("fantasy"))))); 
}
```

---

## 作者：Forever1507 (赞：6)

# [传送门](https://www.luogu.com.cn/problem/CF8A)
其实这道题挺水的就是查找一下彩旗序列里有没有 Peter 醒的时候看到的序列，但是要小心一下顺序。

看到题解区有不少比谁代码短的我觉得真的没必要，所以这篇题解的代码可能略长但即使初学 OI 也能看懂，没有任何花里胡哨的操作~~其实是我不会~~。

具体看注释：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	bool forward=0,backward=0;//存能不能按两种顺序找到序列
	string a,b,c;//输入的三个字符串
	getline(cin,a);//cin也可以但个人习惯getline
	getline(cin,b);
	getline(cin,c);
	int a1=a.size();//a串的长度
	if(a.find(b)<=a1&&a.find(c,a.find(b)+b.size())<=a1){//第一个判断，如果以正序可以找到并且第二个串在第一个后面（非常重要！刚开始愣是卡了5分钟）
		forward=1;
	}
	reverse(a.begin(),a.end());	//翻转字符串
	if(a.find(b)<=a1&&a.find(c,a.find(b)+b.size())<=a1){//同上
		backward=1;
	}
	if(forward==1&&backward==1){
		cout<<"both";
	}
	else if(forward==1){//else if防止重复输出
		cout<<"forward";
	}
	else if(backward==1){
		cout<<"backward";
	}
	else{
		cout<<"fantasy";
	}
	return 0;//好习惯
}

```


---

## 作者：冰糖鸽子 (赞：5)

~~哇，两个争最短解的欸，我就笑笑不说话~~

打脸现场x2，这个代码就14行

那怎么做到的呢？当然是用某黑科技：三目运算符

举例：

- (1 ? "a" : "b") 的值是 a

- (0 ? "a" : "b") 的值是 b

- (0 ? "a" : (0 ? "b" : "c")) 的值是 c

PS : 由于三目运算符奇奇怪怪的优先级，所以都要加括号

那就可以完美的放到程序里了，不是么 (笑)

放代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s,x,y;
int xl,yl,a,b;
int main(){
    cin >> s >> x >> y;
    xl = s.find(x),yl = s.find(y,xl+x.length());
    a = ((yl!=string::npos&&xl!=string::npos) ? 1 : 0);
    reverse(s.begin(),s.end());
    xl = s.find(x),yl = s.find(y,xl+x.length());
    b = ((yl!=string::npos&&xl!=string::npos) ? 1 : 0);
    cout << ((a == 1 && b == 1)?"both":((a==1 && b == 0)?"forward":((a == 0 && b == 1)?"backward":"fantasy"))) << endl;
    return 0;
}
```


---

## 作者：LuckyCloud (赞：2)

## 内心OS
**~~莫名感觉自己的代码简单易懂~~**翻了那么多CF的题解Pascal貌似很少，~~想当初学pascal的时候还是小学生~~那就来一波简单粗暴的代码吧，Pascal的字符串函数真的蛮好用的。


------------

## 正经题解
Pos求出S1在S2中的起始位置，如果S1在S2中不存在的话，就返回0。
按照题目意思，我们就先设第一次醒着的时候看到的彩旗序列为Q1，总彩旗序列为S1，第二次醒着看到的彩旗序列设为Q2，然后直接调用Pos函数找到第一次看到Q1的位置，接着调用delete函数删除从S1起始位置一直到Q1末端位置的所有彩旗，这样当我们调用Pos函数查找Q2的出现位置的时候，**就可以保证Q2一定出现在Q1后面并且Q1和Q2没有交集**


------------

## 补充
######  什么叫没有交集？请看这个例子
###### Luckycloudisextremlyjuruo
###### Luckycloudis
###### is
###### 如果算法中不删除从S1起始位置一直到Q1末端位置的所有彩旗
###### Q1的出现位置就是1（ _L_ uckycloudis） ，Q2的出现位置就是11（Luckycloud _i_ s)
###### 显然这样是错误的因为Q1和Q2有交集。
## 思考题
以上介绍的是从A到B站的做饭，至于从B到A站的做法，一模一样，~~我就不赘述了~~我觉得我已经写的很仔细了QAQ

------------
```pascal

var
 s,p1,p2,mid:ansistring;
 lens,lenp1,lenp2,flag:longint;
 i,j,k,l,n,m:longint;
begin
 readln(s);
 mid:=s;
 readln(p1);
 lenp1:=length(p1);
 readln(p2);
 lenp2:=length(p2);
 n:=pos(p1,mid);
 delete(mid,1,n+lenp1-1);
 m:=pos(p2,mid);
 if (m>0)and(n>0) then  flag:=flag+1;
 lens:=length(s);
 mid:=s;
 for i:=1 to lens do
   mid[i]:=s[lens-i+1];

 n:=pos(p1,mid);
 delete(mid,1,n+lenp1-1);
 m:=pos(p2,mid);
 if (m>0)and(n>0) then flag:=flag+2;
 if flag=3 then writeln('both');
 if flag=1 then writeln('forward');
 if flag=2 then writeln('backward');
 if flag=0 then writeln('fantasy');
end.
```

---

## 作者：Soshine_溯闪 (赞：1)

我 **第八次** 传题解。     
一道模拟题，牵涉字符串的知识，最后输出有用一点逻辑推理。        
总体来说还是很水的。       
# 整体思路
1. 先在原 $a$ 中找 $b$ ,然后在 $b$ 后面找 $c$ ，可以用 .find 函数来找。   
2. 如果两个字符串首次出现的位置在 $a$ 的范围里面，换句话说就是位置 ≥0 ，并且＜ $a$ 的长度，第一部分就是成立的。      
3. 将 $a$ 翻转，看看回来能不能看到。    
4. 第二部分处理与第 1 条差不多，如果满足 第 2 条那么第二部分就成立。     
# 输出
1. 如果两个部分均满足，输出 $both$ 。
2. 如果都不满足，输出 $fantasy$ 。
3. **只**有第一部分满足，说明只有去时能看到，输出 $forward$ 。
4. **只**有第二部分满足，说明只有回时能看到，输出 $backward$ 。
# 上程序
```
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
string a,b,c;
int ok1,ok2; 		//定义 
int main(){
	cin>>a>>b>>c;		//输入 
	ok1=ok2=0;		//定义 
	int fb1=a.find(b,0);		//寻找 
	int fc1=a.find(c,fb1+b.length());		//在b后寻找 
	if(fb1<a.size()&&fb1>=0&&fc1<a.size()&&fc1>=0) ok1=1;		//如果满足，ok1就置1 
	reverse(a.begin(),a.end());		//翻转 
	int fb2=a.find(b,0);		//再寻找 
	int fc2=a.find(c,fb2+b.length());		//在b后寻找 
	if(fb2<a.size()&&fb2>=0&&fc2<a.size()&&fc2>=0) ok2=1;		//满足条件，ok2就置1 
	if(ok1&&ok2) cout<<"both"<<endl;		//两者满足输出这个 
	else if(!ok1&&!ok2) cout<<"fantasy"<<endl;		//两者都不满足，输出这个 
	else if(ok1&&!ok2) cout<<"forward"<<endl;		//第一个满足输出这个 
	else if(!ok1&&ok2) cout<<"backward"<<endl;		//第二个满足输出这个 
	return 0;		//完美AC 
}
```
跪求管理员给过。    
就酱，我们有 **圆** 再见。     

---

## 作者：qzhwmjb (赞：1)

### 思路
---
题目让我们 $a$ 中依次找到 $b$ 和 $c$。那就可以利用[ $find()$ 函数](https://www.cnblogs.com/wkfvawl/p/9429128.html)来找 $b$,$c$。
在依靠其返回值，来判断 $4$ 种可能性。  
1. 顺 $b$，顺 $c$，逆 $b$，逆 $c$，有两个或两个以上没找到，$fantasy$。  
2. 顺 $b$，顺 $c$，逆 $b$，逆 $c$，全找到，$both$。  
3. 顺 $b$，顺 $c$，全找到，逆 $b$，逆 $c$，有一个或一个以上没找到，$forward$。  
4. 顺 $b$，顺 $c$，有一个或一个以上没找到，逆 $b$，逆 $c$，全找到，$backward$。  
### 全代码
---
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c,sum;
int i,j,k;
int main() {
	cin>>a>>b>>c;
	for(i=a.size()-1; i>=0; i--) {
		sum += a[i];
	}
	int x_1=a.find(b,0),x_2=a.find(c,x_1+b.size());
	int y_1=sum.find(b,0),y_2=sum.find(c,y_1+b.size());
	if((x_1==-1||x_2==-1)&&(y_1==-1||y_2==-1)) {
		cout<<"fantasy"<<endl;
	} else if(x_1!=-1&&x_2!=-1&&y_1!=-1&&y_2!=-1){
		cout<<"both"<<endl;
	} else if(x_1!=-1&&x_2!=-1&&(y_1==-1||y_2==-1)){
		cout<<"forward"<<endl;
	} else {
		cout<<"backward"<<endl;
	}
	return 0;
}
```


---

## 作者：Loner_Knowledge (赞：1)

这是一道字符串模拟题

---

只需要正序和逆序分别查找第一段和第二段子串即可。

```cpp
#include<cstdio>
#include<cstring>
const char *str[4]={"fantasy","forward","backward","both"};
char s[100002],s1[102],s2[102];
int main() {
	int p=-1;
	bool t=0,flag1=0,flag2=0;
	scanf("%s%s%s",s,s1,s2);
	for(int i=0;s[i]&&p==-1;++i) {		//正序查找第一段
		t=1;
		for(int j=0;s1[j]&&t;++j)
			if(s[i+j]!=s1[j])
				t=0;
		if(t)
			p=i+strlen(s1);			//存储第一段结尾位置
	}
	if(p!=-1)
		for(int i=p;s[i]&&!flag1;++i) {			//正序查找第二段
			flag1=1;
			for(int j=0;s2[j]&&flag1;++j)
				if(s[i+j]!=s2[j])
					flag1=0;
		}
	p=-1;
	for(int i=strlen(s)-1;i>=0&&p==-1;--i) {		//逆序查找第一段
		t=1;
		for(int j=0;s1[j]&&t;++j)
			if(s[i-j]!=s1[j])
				t=0;
		if(t)
			p=i-strlen(s1);			//存储第一段结尾位置
	}
	if(p!=-1)
		for(int i=p;i>=0&&!flag2;--i) {			//逆序查找第二段
			flag2=1;
			for(int j=0;s2[j]&&flag2;++j)
				if(s[i-j]!=s2[j])
					flag2=0;
		}
	printf("%s",str[flag1+flag2*2]);
	return 0;
}
```

---


---

## 作者：xh39 (赞：0)

别看题目唠叨一大堆,其实真正的题意就是问你一个字符串正着看和倒着看是不是顺序看到s1和s2。

~~算法:这么简单还有算法?~~

其实就只需要掌握简单的找一个字符串的子串是否可以找到,并返回找到的位置(这个子串末尾),然后找第二个子串只能从返回的位置+1开始找(因为题目有说"列车一直都在移动，所以**一面同样**的旗子**不可能**被看到**两次**。")。

倒着看也很容易,把字符串倒过来重复刚才的就可以了。

接下来上代码:

```cpp
#include<bits/stdc++.h>//万能头文件,包含c++所有库函数。
using namespace std;
int zc(string a,string b,int pos){//判断在pos后面b会不会是a的子串。
	int i,sizea=a.size(),sizeb=b.size();
	for(i=pos;i<=sizea-sizeb;i++){
		if(a.substr(i,sizeb)==b){//substr,取字符串的一个子串,有2个参数,第一个是从哪一位开始取,第二个是取几位。值得注意的是,只有字符串才行,字符数组不行
			return i+sizeb-1;//记得-1,因为原来就是在第一位。
		}
	}
	return -1;//没找到返回-1
}
int main(){
	string s,s1,s2;//s就是题目中的s0
	int size,size1,size2,t,i;
	bool zheng=false,fan=false;
	cin>>s>>s1>>s2;
	size=s.size();
	size1=s1.size();
	size2=s2.size();
	t=zc(s,s1,0);
	if(t!=-1&&zc(s,s2,t+1)!=-1){
		zheng=true;
	}
	for(i=0;i<size-i-1;i++){//倒过来,交换的数前一个比后一个要大,立刻停止。不然就交换了2次。
		swap(s[i],s[size-i-1]);
	}
	t=zc(s,s1,0);
	if(t!=-1&&zc(s,s2,t+1)!=-1){
		fan=true;
	}
	if(zheng){
		if(fan){//既可以正着看又可以反着看。
			cout<<"both";
		}else{//只可以正着看。
			cout<<"forward";
		}
	}else if(fan){//不可以正着看但可以反着看。
		cout<<"backward";
	}else{//都不可以。
		cout<<"fantasy";
	}
	return 0;
}

```

最后温馨提示一句:单词别打错了啊。

[AC评测记录](https://www.luogu.org/recordnew/show/16509006)别怀疑我没通过

---

