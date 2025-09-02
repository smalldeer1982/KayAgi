# [ABC045B] 3人でカードゲームイージー

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc045/tasks/abc045_b

A さん、B さん、C さんの $ 3 $ 人が以下のようなカードゲームをプレイしています。

- 最初、$ 3 $ 人はそれぞれ `a`、`b`、`c` いずれかの文字が書かれたカードを、何枚か持っている。これらは入力で与えられた順番に持っており、途中で並べ替えたりしない。
- $ A $ さんのターンから始まる。
- 現在自分のターンである人がカードを $ 1 $ 枚以上持っているならば、そのうち先頭のカードを捨てる。その後、捨てられたカードに書かれているアルファベットと同じ名前の人 (例えば、カードに `a` と書かれていたならば A さん) のターンとなる。
- 現在自分のターンである人がカードを $ 1 $ 枚も持っていないならば、その人がゲームの勝者となり、ゲームは終了する。

$ 3 $ 人が最初に持っているカードがそれぞれ先頭から順に与えられます。 具体的には、文字列 $ S_A $、$ S_B $、$ S_C $ が与えられます。文字列 $ S_A $ の $ i $ 文字目 ( $ 1\ \leq\ i\ \leq\ |S_A| $ ) に書かれている文字が、A さんの持っている中で先頭から $ i $ 番目のカードに 書かれている文字です。文字列 $ S_B $、 $ S_C $ についても同様です。

最終的に誰がこのゲームの勝者となるかを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ S_A\ \leq\ 100 $
- $ 1\ \leq\ S_B\ \leq\ 100 $
- $ 1\ \leq\ S_C\ \leq\ 100 $
- $ S_A $、$ S_B $、$ S_C $ に含まれる文字はそれぞれ `a`、`b`、`c` のいずれか

### Sample Explanation 1

ゲームは以下のように進行します。 - A さんが、持っている中で最初のカード `a` を捨てる。次は A さんの番となる。 - A さんが、持っている中で最初のカード `c` を捨てる。次は C さんの番となる。 - C さんが、持っている中で最初のカード `c` を捨てる。次は C さんの番となる。 - C さんが、持っている中で最初のカード `a` を捨てる。次は A さんの番となる。 - A さんが、持っている中で最初のカード `a` を捨てる。次は A さんの番となる。 - A さんはもう持っているカードがない。よって A さんの勝利となり、ゲームは終了する。

## 样例 #1

### 输入

```
aca
accc
ca```

### 输出

```
A```

## 样例 #2

### 输入

```
abcb
aacb
bccc```

### 输出

```
C```

# 题解

## 作者：Kevin_Zhen (赞：7)

## 挑战本题最短码量
### 变量介绍
1.s[]为本题的三个字符串，Alice的下标为0，Bob为1，Charlie为2。  
2.p[]为当前牌堆顶指针。  
3.k记录当前要从哪个牌堆抽牌（因为Alice先开始，所以初值为0）。
### 思路
刚开始先判断当前牌堆是否已空，空的话输出，跳出循环。  
具体实现是看当前牌堆顶指针是否已经指到len[k]处。
```cpp
if (p[k] == len[k]) {
	printf("%c\n", k + 'A');
	break;
}
```
倘若非空的话，把k指向当前牌堆顶的字母所指的牌堆，同时当前牌堆顶指针后移一位。
```cpp
k = s[k][p[k]++] - 'a';
```
### AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

string s[3];
int p[3];
int len[3];
int k = 0;

int main() {
	for (int i = 0; i < 3; ++i) cin >> s[i], len[i] = s[i].size();
	while (1) {
		if (p[k] == len[k]) {
			printf("%c\n", k + 'A');
			break;
		}
		k = s[k][p[k]++] - 'a';
	}
	return 0;
}
```
### 完结撒花！*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：KazamiHina (赞：1)

个人感觉这题没有紫色难度吧

这题只是一个简单的模拟题

首先来模拟一下第一组样例

$aca$

$accc$

$ca$

先从第一个人开始，先拿出了$a$，还是第一个人，然后拿出了$c$，到了第三个人，第三个人拿出了$c$，还是第三个人，接下来拿出$a$（注意，这里的第三个人还没有赢），然后到了第一个人，第一个人拿出了$a$，然后第一个人就赢了

所以按照样例模拟了之后代码就很简单了

这题也没有多组数据

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

string as,bs,cs;
int al,bl,cl;
int at=-1,bt=-1,ct=-1;//注意，这里要初始化为-1，因为后面的at++/bt++/ct++是写在前面的
char flag='a';//一开始初始化为第一个人先开始

inline void solve(){
	for( ; ; ){//死循环
		if(at>=al){//如果A拿完了
			puts("A");//A赢了
			break;//退出循环
		}
		if(bt>=bl){
			puts("B");
			break;
		}
		if(ct>=cl){
			puts("C");
			break;
		}
		if(flag=='a'){//如果是a拿牌
			at++;//这张牌去掉
			flag=as[at];//as[at]这个人拿牌
		}
		if(flag=='b'){
			bt++;
			flag=bs[bt];
		}
		if(flag=='c'){
			ct++;
			flag=cs[ct];
		}
	}
}

int main(){//这题也没有多组数据，不用初始化
	cin>>as>>bs>>cs;
	al=as.size();
	bl=bs.size();
	cl=cs.size();
	solve();
	return 0;
}
```

$qwqwq$

---

## 作者：AlwaysForward (赞：1)

我的第一道紫题！！！(第一篇题解，希望通过）

主要是字符串，设一个循环，检测当前字符串的第一个，若是a则下个循环跳到a字符串，若是b则下个循环跳到b字符串，若是c则下个循环跳到c字符串，然后删除第一个。直到a,b,c中一个字符串为空，哪个先空输哪个，整体思路就是这样。

代码奉上（copy代码的爆零！！！）：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
    string a,b,c;
    int x=0,y=0,z=0;
    cin>>a>>b>>c;
    string k="a";
    for(int i=1;;i++){
    	if(k=="a"){
    	    k=a.substr(0,1);
		    a=a.erase(0,1);
		    if(x==1){
		    	cout<<"A";
		    	return 0;
			}
		    if(a==""){
		       x=1;
			}
		}
		if(k=="b"){
    	    k=b.substr(0,1);
		    b=b.eresa(0,1);
		    if(y==1){
		    	cout<<"B";
		    	return 0;
			}
		    if(b==""){
		       y=1;
			}
		}
		if(k=="c"){
    	    k=c.substr(0,1);
		    c=c.erase(0,1);
		    if(z==1){
		    	cout<<"C";
		    	return 0;
			}
		    if(c==""){
		       z=1;
			}
		}
		}
	}

```


---

## 作者：RE_Ripper (赞：1)

**这道题目我们可以选择模拟**，首先我们先输入手牌，再读取他们的手牌个数*
因为下标从零开始，而每次出牌要加1，所以我们可以初始化为-1，第一次循环时下表就会变0.然后**s1[a]-'a'+1**即是下一位玩家的回合（如：s1[a]==a,则结果为1，又是a回合，若s1[a]==b，则结果为2，即B玩家回合）因为回合必须出牌，所以每一回合结束，他的回合个数与手牌相等，则手牌数为零胜利，**AT记得换行**  
~~**代码助理解**~~

```
#include <bits/stdc++.h>
using namespace std;
int tmp;
char s1[1000],s2[1000],s3[1000];
int main()
{
    int a,b,c;
    int long_a,long_b,long_c;
    while(cin>>s1>>s2>>s3)
	{
        long_a=strlen(s1);
		long_b=strlen(s2);
		long_c=strlen(s3);
        tmp=1,//初始化
		a=-1;
		b=-1;
		c=-1;
        while(true)
		{
            if(long_a==a)
			{
                cout<<"A"<<endl;
                break;
            }
            else if(long_b==b)
			{
                cout<<"B"<<endl;
                break;
            }
            else if(long_c==c)
			{
                cout<<"C"<<endl;
                break;
            }
            if(tmp==1)
			{
                a++;
                tmp=s1[a]-'a'+1;
            }
            else if(tmp==2)
			{
                b++;
                tmp=s2[b]-1+1;
            }
            else if(tmp==3)
			{
                c++;
                tmp=s3[c]-'a'+1;
            }
        }
    }
    return 0;
}
```




---

## 作者：Mr_WA的大号 (赞：0)

粉骨碎身浑不怕，要留清白在人间。小学生又来发题解了！

题号:AT2066

难度：★★

算法：模拟

## 开课了！

模拟式这道题的关键要素。

模拟：就是按照题目的意思去跟着做，没有什么难度。

这一题的总体思路如下：

1.输入。输入的时候要把每个字符串的长度也统计下来。

2.模拟。先判断这份牌有没有拿完，拿完了就输出。接着将这副牌拿走的牌数++，最后转换牌堆。

3.输出。（告诉你个小秘密：AT题目要换行）

课讲完了,上代码：
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<iomanip>
using namespace std;
int k,len[5],x[5];
string st[5];
int main()
{
	cin>>st[1];
	len[1]=st[1].size();
	cin>>st[2];
	len[2]=st[2].size();
	cin>>st[3];
	len[3]=st[3].size();//输入
	k=1;//当前牌堆记得初始化为1
	while(x[k]<len[k])//判断牌堆是否拿完，拿完就退出
	{
		k=st[k][x[k]++]-96;//转换牌堆后牌数++
	}
	cout<<char(k+64)<<endl;//输出，记得换行
	return 0;
}
```
祝大家能AC！

---

