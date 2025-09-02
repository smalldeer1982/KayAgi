# Game with string

## 题目描述

Two people are playing a game with a string $ s $ , consisting of lowercase latin letters.

On a player's turn, he should choose two consecutive equal letters in the string and delete them.

For example, if the string is equal to "xaax" than there is only one possible turn: delete "aa", so the string will become "xx". A player not able to make a turn loses.

Your task is to determine which player will win if both play optimally.

## 说明/提示

In the first example the first player is unable to make a turn, so he loses.

In the second example first player turns the string into "q", then second player is unable to move, so he loses.

## 样例 #1

### 输入

```
abacaba
```

### 输出

```
No
```

## 样例 #2

### 输入

```
iiq
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
abba
```

### 输出

```
No
```

# 题解

## 作者：BINYU (赞：5)

这题不就是一个消消乐吗，只是一次只能消除两个，判断是否能赢

由于不能消除了就输了，所以

#### 有能消的就会消，所有成对出现的字符都会被消掉

那我们统计能消掉的次数即可

由于中间的消掉了，两边的就相邻了，那么建立一个栈，按序存未被消掉的字符，栈顶就是最后一个未被消掉的字符，消掉后，下面的字符就成了栈顶，所以用栈很方便

操作方法：

每读入一个字符，就拿它和栈顶（上一个未被消除的字符）比较，如果相同，就删除栈顶（消除），如果不相同，就把它入栈（因为它成为了最后一个未被消掉的字符了）

代码如下：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
char s;
int ans;
stack <char> x;//STL库里的栈
int main()
{
	cin>>s;
	x.push(s);//先把第一个放进去，不然会RE
	while(cin>>s)//边读边处理
	{
		if(x.size() > 0&&s == x.top())x.pop(),ans++;//相同
		else x.push(s);//不同
	}
	if(ans % 2 == 1)cout<<"Yes";//能胜利
	else cout<<"No";//不能胜利
	return 0;
}
```


---

## 作者：Reywmp (赞：4)

**基础不好害死人**，我竟然不知道EOF,~scanf这些东西exe跑不出来。。。

后来绝望了放到ide里面测居然出来答案了。卡了50min啊！！！

所以大家要明白

＞文件类型的东西exe是跑不出来的！

------------

这题其实水的很，不过要用文件输入方面的东西。

思路很简单，我们边输入字符串边做。

如果当前输入的字符串与前一个一样，就无视掉并删除前一个，相当于一个人的操作。

如何删除呢？其实我们只需要将当前的位置-2（因为每次i都要++，所以相当于-1），后面输入进来就的会覆盖掉前面的。

每次删除回合数+1，看最后回合总数的奇偶性就会知道谁赢了。

------------

代码如下：

```cpp
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int x=0;int i=1;
	while(cin>>a[i])//文件输入内容，exe跑不出来（反正我跑不出来）
	{
		if(a[i]<'a'||a[i]>'z')break;//这个是保障用的，貌似不需要
		if(a[i]==a[i-1])//如果一样
		{
			i-=2;x++;//删除并加一次回合
		}
		i++;
	}
	if(x%2==1)puts("Yes");//为奇数则是A赢了
	else puts("No");//为偶则是B
	return 0;
}
```

---

## 作者：zhanghzqwq (赞：3)

这道题还是很水的，我选择用栈做，只要判断去掉次数的奇偶性我们就能得出来答案了。要是去掉答案的次数为奇数那么就是A赢，反之B赢。最后一点，判断此时字符是否和站顶一样的时候，必须要先判断栈是否为空，不然会re的。时间复杂度为$\mathcal O(n)$。

AC代码：

```cpp
#include<stack>//栈的头文件
#include<iostream>
using namespace std;
int main(){
	stack<char> s;//新建一个栈
	char ch;
	int cnt=0;
	while(cin>>ch){
		if(!s.empty()&&ch==s.top()){//判相同
			s.pop();
			cnt++;//次数++
		}else{
			s.push(ch);//否则入栈
		}
	}
	if(cnt%2==1){//判次数奇偶性
		cout<<"Yes"<<endl;
	}else{
		cout<<"No"<<endl;
	}
	return 0;//完结撒花
}
```


---

## 作者：世末OIer (赞：3)

现在来介绍一种模拟的做法（AC）


```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
	n=s.size();
	int i,j;
	int h=0,t=n-1;
	int gs=0;
	s='&'+s;
	s+='#';
	for(i=0;i<s.size()-1;++i){
		while(i<s.size()-1 and s[i]==s[i+1]){      //看看能不能和后面配对
			s.erase(s.begin()+i);
			s.erase(s.begin()+i);
			i-=1;
			++gs;
		}
		while(i and s[i]==s[i-1]){                 //看看能不能和前面的数前面的数配对(因为之前的配对可能回造成一些新的配对)
			s.erase(s.begin()+i-1);
			s.erase(s.begin()+i-1);
			i-=2;
			++gs;
		}
	}
	if(gs%2) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
$\text{A}$ 与 $\text{B}$ 正在玩一个关于由小写拉丁字符构成的字符串 $s$ 的游戏。

每一个人会轮流操作，先 $\text{A}$ 后 $\text{B}$。

对于每一次操作，操作者需要将 $s$ 中的两个 __连续且相同__ 的字符消除，消除后的字符串由另一个人操作。

对于每一次操作，如果不能找到两个符合要求的字符，那么操作者输。
## $\text{Solution}$
水题。  
显然博弈论只是层皮，胜负就与操作次数的奇偶性有关。  
由于有删除操作，我写了个链表，每次删除后再递归往两侧看能不能接着删。  
看其他题解许多使用了栈，做法也很简单。
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+100;
inline ll read(){
	ll x(0),f(1);char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n;
int l[N],r[N],ans;
char s[N];
bool vis[N];
void del(int x,int y){
	++ans;vis[x]=vis[y]=1;
	int xx=l[x],yy=r[y];
	r[xx]=yy;l[yy]=xx;
	if(xx>0&&yy<=n&&s[xx]==s[yy]) del(xx,yy);
	return;
}
int main(){
	scanf(" %s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++) l[i]=i-1,r[i]=i+1;
	r[0]=1;l[n+1]=n;
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		if(s[i]==s[l[i]]) del(l[i],i);
	}
	if(ans&1) printf("Yes");
	else printf("No");
}
```


---

## 作者：zsc2003 (赞：1)

#### 2019.1.22 codeforces div2 

##### 题目大意:

读入一个字符串$s$，

有两个人，每个人每次可以消掉两个相连且相同的字符

最终无法再一次消除的人输

假设两人均采用最有策略

则先手输输出```No```,否则输出```Yes```

##### 思路

每次遇到能消除的就消除即可

边读入边进行操作

统计一下总共能消掉$tot$对字符

若为$tot$偶数，则输出```No```即先手输

否则输出```Yes```

##### 下面附上本人的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100100;
char s[N];
int pos,tot;
int main()
{
	char ch=getchar();
	while('a'>ch||ch>'z')
		ch=getchar();//使用getcahr()一个字符一个字符的读入，先过略掉之前的东西
	while('a'<=ch&&ch<='z')
	{
		if('a'>ch||ch>'z')
			break;//不是字符则停止读入
		if(pos!=0)
		{
			if(ch==s[pos-1])
				++tot,--pos;
			else
				s[pos++]=ch;
		}
		else
			s[pos++]=ch;
		ch=getchar();
	}
	if(tot%2==0)
		puts("No");//先手输
	else
		puts("Yes");//后手输
	return 0;
}
```



---

## 作者：da32s1da (赞：1)

很明显，只需看去掉次数的奇偶即可。

奇数为Yes，偶数为No。

qwq因为比较懒，直接开了一个stack<char>来做

```
#include<cstdio>
#include<stack>
#include<cstring>
using namespace std;
const int N=1e5+50;
char s[N];int len,Ans;
stack<char>qwq;
int main(){
	scanf("%s",s);
	len=strlen(s);
	for(int i=0;i<len;i++){
		if(qwq.empty()||s[i]!=qwq.top())qwq.push(s[i]);
		else Ans++,qwq.pop();
	}
	puts(Ans&1?"Yes":"No");
}
```

---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/CF1104B)

题目大意：
```
读入一个字符串。

有两个人，每个人每次可以消掉两个相连且相同的字符。

最终无法再一次消除的人输。

假设两人均采用最优策略，若先手会输则输出No，否则输出Yes。
```

看到各位dalao都详细的讲过了栈和判断奇偶性的写法，那我这个蒟蒻就来补充一种朴素的模拟的做法。

思路：~~显然是模拟题，没什么好说的~~。每一次操作时从头到尾扫描一遍，寻找能消除的字母。如果有，就消除之，换下一个人操作；如果没有，输出结果

方法（以一次操作为例）：

- $1.$ 从头到尾寻找是否存在两个可以消除的字符（连续且相同）；

- $2.$ 如果能找到，消除之，后面补上来，换下一个人操作；

- $3.$ 如果不能找到，退出循环，输出答案。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long//个人习惯 
using namespace std;
char s[100005];//s数组是当前的字符串（如题意） 
int ans=1,l;//ans是当前轮到哪一个人操作（1为A取，-1为B取），l是字符串长度 
int main()
{
	scanf("%s",s);//输入 
	l=strlen(s);//计算长度 
	while(1)//死循环 
	{
		int ok=0;//ok是由于储存是否存在两个可以消除的字符的（0为没有，1为有） 
		for(int i=0;i<l-1;i++) 
		{
			if(s[i]==s[i+1])//如果它们连续且相同 
			{
				for(int j=i;j<l-2;j++)
				{
					s[j]=s[j+2];//把后面的往前移，补上删除后的空位
				}
                //这里因为刚才那个循环时已经把消除的两个字母替换了（等同于清除了），所以就不用管了 
				ok=1;//找得到可以消除的 
				l-=2;//因为删除了两个字符，所以串的长度要减2 
				break;//退出查找 
			}
		}
		if(ok)ans=!ans;//如果找到了，变成下一个人操作  
		else break;//如果没找到，就退出循环   
	}
	if(ans)printf("No");//如果轮到A取时不能再取了，A就失败了
	else printf("Yes");//如果轮到B取时不能再取了，A就胜利了
	return 0;//结束程序 
}
```

$2021.1.3$ ：增加了一部分 $\LaTeX$ ，增加了注释并增加了一部分说明。

---

