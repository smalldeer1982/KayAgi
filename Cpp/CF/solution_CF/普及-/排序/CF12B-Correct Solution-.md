# Correct Solution?

## 题目描述

在一个寒冷的冬夜，Alice 和她的哥哥 Bob 正坐在家中的壁炉旁，玩一个有趣的游戏。

Alice 给出了一个数 $n$，并让 Bob 找到满足以下条件的数：

- 通过将这个数的数位打乱，得到一个没有前导零的最小的新数。

“没问题！“ Bob 立刻给出了答案。因为 Alice 并不知道哥哥的答案是否正确，所以她将 $n$ 和哥哥给出的答案给了你，希望你能帮她判断这个答案是否正确。

## 样例 #1

### 输入

```
3310
1033
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
4
5
```

### 输出

```
WRONG_ANSWER
```

# 题解

## 作者：TLMPEX (赞：8)

思路：先输入两个字符串，再把字符串转换成数字串，把第一个数字串排序，并用交换第一个数和第一个不是0的数，最后比较，如果一样就输出‘OK’了，否则输出‘WRONG_ANSWER’了。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
string A,B;
int a[10],b[10];
int main(){
	int i,l;
	cin>>A>>B;
	if(A.size()!=B.size()){//如果长度不一样，那肯定输出"WRONG_ANSWER"
		cout<<"WRONG_ANSWER";
		return 0;
	}
	l=A.size();
	for(i=0;i<l;i++)
		a[i]=A[i]-'0';//转换
	for(i=0;i<l;i++)
		b[i]=B[i]-'0';//转换
	sort(a,a+l);//排序
	i=0;
	while(a[i]==0&&i<l)i++;//找到第一个不是0的数的下标
	swap(a[0],a[i]);//交换
	for(i=0;i<l;i++)//比较
		if(a[i]!=b[i]){
			cout<<"WRONG_ANSWER";
			return 0;
		}
	cout<<"OK";
}
```


---

## 作者：Lips (赞：4)

# 连个橙题都得做 $3,4$ 次的我还能干啥？

###  $\text{Part.1 }$简述一下题意：

给你两个数 $a,b$，问你 $b$ 是否是 $a$ 每位数字重新从小到大排序后所组成的新数。

### $\text{Part.2 }$思路：

读入方面，楼下做的很麻烦，速度也慢，这里给大家提供一种类似快读思想的读入方式。

先定义一个临时 $char$ 类型变量 $ch$，然后一直 $\operatorname{getchar}()$，直到读入换行符`\n`。对于每个新的 $ch$，珂以把它装到一个数组里，这里便体现高精的思想，以数组来装整数！

写个函数，利用指针，$4$ 行搞定输入部分！

```cpp
inline int read(int* a,int& tot)
{
	ch=getchar();
	while(ch>='0'&&ch<='9') a[++tot]=(ch-'0'),ch=getchar();
} 
```
$\text{main}$ 函数里：

```cpp
read(a,tot1),read(b,tot2);
```

其中 $tot1$ 和 $tot2$ 都是指数组长度。

把 $a$ 数组排个序，与 $b$ 数组对比一下是否一样即可。

但这样的结果是 $WA$。。。

我们发现，如果一个数为 $250$，则排序过后为 $025$，不合法，所以便要将离首位最近的位置的非零的数调换 $swap$ 一下好惹。

```cpp
while(a[pos]==0) pos++;
swap(a[1],a[pos]);
```
但我们发现，还是 $WA$。。。（这就是我的历程

再读一遍题发现，$b$ 可能有前导 $0$！！！

特判一下就好惹呗。

上高清无注释代码~~方便您们抄（bushi~~

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=30;
int a[MAXN],b[MAXN],tot1,tot2,pos=1;
char ch;
inline int read(int* a,int& tot)
{
	ch=getchar();
	while(ch>='0'&&ch<='9') a[++tot]=(ch-'0'),ch=getchar();
} 
int main()
{
	read(a,tot1),read(b,tot2);
	if(tot1==1&&tot2==tot1)
	{
		if(a[1]==b[1]) puts("OK");
		else puts("WRONG_ANSWER");
		return 0;
	}
	if(tot2!=1) if(b[1]==0){puts("WRONG_ANSWER");return 0;}
	sort(a+1,a+1+tot1);
	while(a[pos]==0) pos++;
	swap(a[1],a[pos]);
	if(tot1!=tot2) {puts("WRONG_ANSWER");return 0;}
	for(register int i=1;i<=tot1;i++)if(a[i]!=b[i]){puts("WRONG_ANSWER");return 0;}
	puts("OK");
	return 0;
}
```
完结撒花~

---

## 作者：gary2005 (赞：3)

总思想    **排序**—**去前导零**


------------

上代码


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int num[15]={0};//其实不会超过10位
	int tempnum,weishu=0;
	scanf("%d",&tempnum);//输入一开始的数 
	while(tempnum!=0) {//将数转换位数字 
		num[++weishu]=tempnum%10;//倒存  注意！！！ 
		tempnum/=10;
	}
	sort(num+1,num+1+weishu); //排序 
	for(int i=1;i<=weishu;i++){
		if(num[i]!=0){//找到第一个非零数与第一个对调 （去除前导零并保证最小） 
			swap(num[i],num[1]);//对调函数 
			break;
		}
	} 
	string bob;
	cin>>bob;//bob的答案 
	if(bob.length()==1&&bob[0]=='0'&&tempnum==0){//如果都是0则正确 
		printf("OK");
		return 0;
	}
	if(bob.length()!=weishu){//位数不一样当然错 
		printf("WRONG_ANSWER");
		return 0;
	}
	for(int i=0;i<weishu;i++){
		if(bob[i]-'0'!=num[i+1]){//一个数字不一样，错      注意！bob存放的是字符应当减‘0’ 
			printf("WRONG_ANSWER");
			return 0;
		}
	}
	printf("OK");
	return 0;
}
```

---

## 作者：BotDand (赞：1)

# Problems
输入一个整数$n$，输出它重新排列的最小数（无前导$0$）。
# Answer
可以先将$n$从小到大排好序，再去找前导$0$，将$0$转移到后面。

但是要注意一点：$n$是一位数时，应单判。
# Code
```pascal
var
  a,b:string;
  i,j:longint;
  t:char;
begin
  readln(a);
  readln(b);
  if length(a)=1 then begin if a=b then writeln('OK') else writeln('WRONG_ANSWER');exit;end;//单判
  for i:=1 to length(a)-1 do for j:=i+1 to length(a) do if a[i]>a[j] then begin t:=a[i];a[i]:=a[j];a[j]:=t;end;//从小到大排序
  i:=1;while a[i]='0' do inc(i);a[1]:=a[i];for j:=2 to i do a[j]:='0';//前导0
  if a=b then writeln('OK') else writeln('WRONG_ANSWER');//判断
end.
```

---

## 作者：fls233666 (赞：1)

题目要求判断给出的数字是不是各位上的数字组合出的**不含前导0的最小数字**。

按照题意，我们首先会有这样一个简单的想法：把题目给的数字读入进来，**对各位上的数字字符排序**，得到最小数字后进行字符串比较，得出结果。

但是这样排序出来的数字是带前导零的，所以这个方法不可行QAQ。

但是，我们得到了一个关键信息：**要排序**！

换一种思路：对0~9这些字符进行桶排序【即记录每个字符出现的次数】。然后每次从这些字符中选出最小的拼到答案的字符串上，得到最小数。

这个方法是可行的，因为对于第一次找最小数时，可以特判一下，然后从1开始找。

最后，还要注意：**要特判只有0的情况**

于是就有了下面的AC代码：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int num[10];
string spc="0";
int main(){
    string s1,s2,ans="";
    cin>>s1>>s2;   //读入
    if(s1==spc){
        printf(s2==spc?"OK":"WRONG_ANSWER");
        return 0;   //特判只有0
    }
    for(int i=0;i<s1.size();i++)
        num[s1[i]-'0']++;   //桶排序
    for(int i=0,bg=0;i<s1.size();i++,bg=0){
        if(!i) bg=1;   //特判前导零
        for(int j=bg;j<=9;j++){
            if(num[j]){   //选择数字
                ans+=j+'0';   //拼接
                num[j]--;
                break;
            }
        }
    }
   // cout<<ans;
    printf(ans==s2?"OK":"WRONG_ANSWER");  //输出判断结果
    return 0;
}
```


---

## 作者：RagnaLP (赞：1)

一开始还以为可以用康托展开，可然而这是只是一道字符串处理题（~~至少我是这样写的~~)

算法核心：

把输入的第一组数作为字符串处理，便于一个一个的从小到大排序，再将排序后的字符串中的前置0替换到第一个非0数字后，比较两个字符串是否相同即可( _strcmp()_   )
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
char n[15],m[15];//数据范围：10^9
int ln,lm;//储存n和m的长度
bool cmp(char a,char b){
	return a<b;
}//快排，按照ASCII排，其实就是按照数字大小排序
int main(){
	cin>>n>>m;
	ln=strlen(n);
	lm=strlen(m);
    //特判1：长度不同
	if(ln!=lm){
		printf("WRONG_ANSWER");
		return 0;
	}
    //特判2：两个都为0
	else if(n[0]=='0'&&m[0]=='0'){
		printf("OK");
		return 0;
	}
	sort(n,n+ln,cmp);
	int i=0;//记录前置0的个数
	while(n[i]=='0'){
		i++;
	}//此时n[i]为第一个非0数
	swap(n[0],n[i]);//交换位置
	if(strcmp(n,m)==0)//比较字符串是否相同（头文件<cstring>）
		printf("OK");
	else
		printf("WRONG_ANSWER");
	return 0;
}
```

---

## 作者：犀首 (赞：0)

# 算法分析
没有用排序，而是用了一个小根堆，个人感觉蛮直观的。基本思路是先求题目要求的“最小数”，然后和输入的第二行相比较。求“最小数”的基本步骤分三步：

------------
1. 把第一行序列中最小的非0数字放到目标序列最前面
1. 如果有第一行序列中有0，则把0跟在目标序列后面
1. 再把剩下的数放到小根堆里面，然后从小根堆里面取数，依次放到目标序列后面


------------
# 代码及注释
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int N=15;
priority_queue<int,vector<int>,greater<int> > heap;     //建一个小根堆
vector<int> A,B,C;
int st[N];                                              //表示A中的那些数已用过
int get_min(){
    int min=10;
    int pos=-1;                                         //表示最小值的位置
    for(int i=0;i<A.size();i++) if(A[i] && A[i]<min) min=A[i];
    for(int i=0;i<A.size();i++) if(A[i]==min) pos=i;
    if(pos==-1){
        st[0]=1;
        return 0;
    }
    else{
        st[pos]=1;
        return min;
    }
}
void push_zero(){
    for(int i=0;i<A.size();i++) if(A[i]==0 && !st[i]) st[i]=1,C.push_back(0);
}
void push_min(){
    for(int i=0;i<A.size();i++) if(!st[i]) heap.push(A[i]);
    while(!heap.empty()){
        int t=heap.top();
        heap.pop();
        C.push_back(t);
    }
}
bool cmp(){
    if(B.size()!=C.size()) return false;
    for(int i=0;i<B.size();i++){
        if(B[i]!=C[i]) return false;
    }
    return true;
}
int main(){
    
    string a,b;
    cin>>a>>b;
    for(int i=0;i<a.size();i++) A.push_back(a[i]-'0');
    for(int i=0;i<b.size();i++) B.push_back(b[i]-'0');
    
    if(B.size()>1 && B[0]==0) {cout<<"WRONG_ANSWER";return 0;}
    
    C.push_back(get_min());                              //把非0的最小值放在前面
    push_zero();                                         //然后把0跟在后面
    push_min();                                          //然后把剩下的最小值放进去
    
    if(cmp()) cout<<"OK";
    else cout<<"WRONG_ANSWER";
    //test//for(int i=0;i<C.size();i++) cout<<C[i];
    
    
    
    return 0;
    
}
```


---

## 作者：ahawzlc (赞：0)

思路：字符串处理 + 排序。

----

首先如果两个数长度不一样，又不准有前导零，这种情况直接```WRONG_ANSWER```退出。

根据题意，我们把第一个数字按照每一位数的大小排序，因为不能 0 不能作为首位，所以我们找到最小的一个数字替换过来，如果和第二个数一样那肯定莫得问题。

当然要是两个数本来就是 0 ，那么肯定是可以的。

```
#include<bits/stdc++.h>
using namespace std;
int main() {
	char a[25],b[25];
	cin>>a>>b;
	int lena=strlen(a),lenb=strlen(b);
	if(lena!=lenb) {
		puts("WRONG_ANSWER");
		return 0;
	}
	if(a[0]==b[0]&&a[0]=='0') {
		puts("OK");
		return 0;
	}
	sort(a,a+lena);
	int opt=0;
	while(a[opt]=='0') opt++;
	swap(a[0],a[opt]);
	if(!strcmp(a,b)) puts("OK");
	else puts("WRONG_ANSWER");
	return 0;
}
```

---

## 作者：2x6_81 (赞：0)

在这道题，实际上开始时有些人以为这就是输入2个整数（$0 \le n,m \leq 10^9$）

然而，这题实际上应该是处理字符串（数组）

#### 核心：从左到右第一位不能是0（0除外）；而且我们的想法是什么？ 不就是从所有数字中挑一个最小的非0数字在第一位（0除外），其它的从小到大排吗？
所以，代码就出来了：
```
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
using namespace std;
char m[100],n[100],ans[100];//m,n:两个数,ans:最小的数
int x[100];//桶
int lenm=0,lenn=0,l;
static void input()//(读入优化吧)
{
	//(边读边判断)
	while((m[lenm]=getchar())!='\n') lenm++,x[m[lenm-1]-'0']++;//set桶
	while((n[lenn]=getchar())!='\n') lenn++;
	return;
}
static bool pd1()
{
	//长度判断(不等即可结束!)
	return lenn==lenm;
}
static int pd2()
{
	//有人说0要特判,没错.但是为什么不直接把所有一位数都判断呢
	if(lenn==1 and lenm==1)
	if(m[0]==n[0])
	return 1;
	else
	return 0;
	else return 2;//一位以上回2(不是一位数),(特例)
}
static void set_ans()
{
	for(int i=1;i<10;i++)//所有数字中挑一个最小的非0数字
	if(x[i]>0) {ans[l++]=i+'0',x[i]--; break;}
    //其它的利用桶从小到大排(桶排)
	for(int i=0;i<10;i++)
	for(int j=0;j<x[i];j++)
	ans[l++]=i+'0';
	return;
}
static bool pd3()
{
	//判断是否最小
	for(int i=0;i<l;i++)
	if(ans[i]!=n[i]) return 0;
	return 1;
}
int main()
{
	input();
	if(!pd1()) {cout<<"WRONG_ANSWER"<<endl; return 0;}//长度是否相等
	if(pd2()==1) {cout<<"OK"<<endl; return 0;}//是否是1
	else if(!pd2()) {cout<<"WRONG_ANSWER"<<endl; return 0;}//是否是0(假)
	set_ans();//set最小的数
	if(pd3()) cout<<"OK"<<endl;//开始了最后一步判断
	else cout<<"WRONG_ANSWER"<<endl;
    return 0;
}
```
哦，对了，你们有些人是不是想问什么叫"static"。嗯，这是指"静态的"。不懂的童鞋自己翻翻书，查查资料([帮你百度一下](https://baike.baidu.com/item/static/9598919?fr=aladdin))

---

