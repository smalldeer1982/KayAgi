# Fair Game

## 题目描述

Petya and Vasya decided to play a game. They have $ n $ cards ( $ n $ is an even number). A single integer is written on each card.

Before the game Petya will choose an integer and after that Vasya will choose another integer (different from the number that Petya chose). During the game each player takes all the cards with number he chose. For example, if Petya chose number $ 5 $ before the game he will take all cards on which $ 5 $ is written and if Vasya chose number $ 10 $ before the game he will take all cards on which $ 10 $ is written.

The game is considered fair if Petya and Vasya can take all $ n $ cards, and the number of cards each player gets is the same.

Determine whether Petya and Vasya can choose integer numbers before the game so that the game is fair.

## 说明/提示

In the first example the game will be fair if, for example, Petya chooses number $ 11 $ , and Vasya chooses number $ 27 $ . Then the will take all cards — Petya will take cards $ 1 $ and $ 4 $ , and Vasya will take cards $ 2 $ and $ 3 $ . Thus, each of them will take exactly two cards.

In the second example fair game is impossible because the numbers written on the cards are equal, but the numbers that Petya and Vasya should choose should be distinct.

In the third example it is impossible to take all cards. Petya and Vasya can take at most five cards — for example, Petya can choose number $ 10 $ and Vasya can choose number $ 20 $ . But for the game to be fair it is necessary to take $ 6 $ cards.

## 样例 #1

### 输入

```
4
11
27
27
11
```

### 输出

```
YES
11 27
```

## 样例 #2

### 输入

```
2
6
6
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
6
10
20
30
20
10
20
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
6
1
1
2
2
3
3
```

### 输出

```
NO
```

# 题解

## 作者：kon_tori (赞：7)


简化后题意：如果出现的牌为两种，且张数相等则输出$YES$，否则输出$NO$。

借鉴了几位大佬的思路，蒟蒻用的也是桶排序(~~班门弄斧？~~)，思路在代码中。
```cpp
/* light_chaser */
  #include<bits/stdc++.h>
  using namespace std;
  int n,h,m;
  int a[101];//用桶排来存每种牌的张数
  int maxn=0,ans=0;//maxn用来存几种牌中点数比较大的那种
  
  inline int read(){
      register int s=0,w=1;
      register char ch=getchar();
      while(ch<'0'||ch>'9'){
          if(ch=='-')w=-1;
          ch=getchar();
      }
      while(ch>='0'&&ch<='9') 
      s=s*10+ch-'0',ch=getchar();
      return s*w;
  }//快读
  
  int main(){
      n=read();
      for(int i=1; i<=n; i++){
          h=read();
          a[h]++;//存入桶中
          maxn=max(maxn,h);//每次更新maxn的数值可作为之后循环的次数
      }
      for(int j=1; j<=maxn; j++){//遍历每种可能的牌
          if(a[j]>=1){
              ans++;//记录牌的种类
              if(j!=maxn){
                  m=j;//找到其他种类的牌(即该种牌存在且不为点数最大的那种牌)
              }
          }
      }
      if(ans>2||a[maxn]!=n/2){//如果>2种或者任意一种牌的点数不等于n/2就不成立
          puts("NO");//puts 输出自带换行
          return 0;
      }
      else{
          puts("YES");
          cout<<m<<" "<<maxn<<"\n";
          return 0;
      }
  }
```
感谢管理员的辛勤付出！

蒟蒻的第$2$篇题解，望通过。

$updated:$向管理员表示抱歉，提交后又修改了几处语法错误，以后我会注意的。



---

## 作者：qwerta (赞：7)

~~啊哈一道入门水题~~

既然是入门难度就用入门方法写
###题意：

如果所有的牌里面只有两种牌，并且两种牌张数相等，则符合条件

所以以此模拟
```
#include<iostream>
using namespace std;
int main()
{
    int n,i,x,z1=0,z2=0,s1=0,s2=0;//z1,z2分别为两个整数，s1,s2为两整数出现的次数，赋初值为0
    cin>>n;//输入
    if(n%2==1){cout<<"NO";return 0;}//如果牌数为奇数，显然不符合
    for(i=1;i<=n;i++)
    {
        cin>>x;//输入当前的那张牌
        if(z1==0){z1=x;s1++;}//if(z1==0)则说明1号整数未出现过，将读入的数当作一号整数，出现次数++
        else if(z2==0&&x!=z1){z2=x;s2++;}//z1出现过但z2未出现过，将读入的数当z2
        else if(x==z1)s1++;//计数
        else if(x==z2)s2++;//计数
    }
    if(s1==s2&&s1==n/2)//两种牌张数相等且分别为总牌数的一半
    cout<<"YES"<<endl<<z1<<" "<<z2;//输出
    else cout<<"NO";
    return 0;
}
```
注意：原题中有说"If there are several solutions, print any of them.",所以**不用在乎两种牌的顺序**

---

## 作者：111_222_333 (赞：5)

没看见Pascal，赶紧发一波......

这道题的思路其实很简单，你只要用一个桶把所有数都存起来，然后在用一个for循环去找有数的桶，再用一个s累加，最后再判断一下，就好了。

话不多说，还是看代码详细解释......（~~那你先的时候说那么多没用的干嘛？!~~）

献上我丑陋的代码......
```pascal
var a:array[0..110] of longint;//定数组的时候定的大一点（~~我被坑了好几次~~）
    n,i,c,x,s,y,x1,y1:longint;
 begin
  readln(n);//读入n
   for i:=1 to n do
    begin
     readln(c);//读入n个数
     a[c]:=a[c]+1;
    end;
    //桶
   for i:=1 to 100 do//1~100全部找一遍
    if a[i]<>0 then begin s:=s+1;if s=1 then begin x:=a[i];x1:=i;end else begin y:=a[i];y1:=i;end;end;
    //s是有几个不同的数，x是把第1个数的数量保存下来，x1是第1个数保存下来，y和y1同上
    //（这里的话，如果不同的数有好几个，那么y和y1会变来变去，但是，变的同时，s会比2大，那么就不用输出，所以可以在else那里加一个判断，但不加也可以）
   if (s=2)and(x=y) then begin writeln('YES');write(x1,' ',y1);end else write('NO');
   //判断数是不是只有2个，如果是，那么再判断这两个数的数量是不是相同的，是，则输出YES；不是，则输出NO
end.
```
## 再提醒一下，这里的no和yes是大写，大写！！！！！

如果还有什么看不懂的地方，在留言区打出来，我不一定实时回答，但我看了一定会回答的......

---

## 作者：Chaos1018 (赞：3)

###### ~~题意什么的楼下已经说过了，就不再重复了~~
# 不过这里我使用的是桶的思想
上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1009];//桶的数组，用来存放每种卡片数字的出现次数
int main(){
	int n,x,max1=0;//n表示卡片数量，x表示正在输入的卡片，max1表示所有卡片中最大的一张的面值
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		a[x]++;
		max1=max(x,max1);//输入，进桶，更新最大值
	}
	int ans;//ans表示另一张卡片的面值
	int m=0;//m表示共有多少种卡片
	for(int i=1;i<=max1;i++){
		if(a[i]!=0)
		 m++;
		if(i!=max1 && a[i]!=0){
			ans=i;//更新另一张，如果有多个，那么等会会直接退出，注意！！要特判i=max1的情况！！！
		}
	}
	if(m>2){
		cout<<"NO";return 0;
	}
	if(a[max1]!=n/2){
		cout<<"NO";return 0;
	}//照题意模拟。。。如果种类大于2，直接出NO，如果其中一个数的出现次数不等于n/2，直接出NO。
	else{
		cout<<"YES"<<endl<<ans<<" "<<max1;
	}//反之，直接出max1和ans,就行。
	return 0;
} 
```
###总之，这道题还是不算很难~~毕竟是入门难度的题~~相信你们一定能做出来:-）

---

## 作者：Forever1507 (赞：1)

# [传送门](https://www.luogu.com.cn/problem/CF864A)
~~话说这么多人用桶是什么鬼？~~

没什么难的，直接模拟即可，用一个 $cnt$ 数组记录每一个数出现的次数。（英文题目里面说了，每一个数都 $\le100$ ,所以不用开 $map$ ）

再用一个 $sum$ 记录有多少个不同的数，不等于 $2$ 的话直接输出 `NO` 然后 `return 0` 就完事儿了。等于二就判断一下那两个数出现的次数是否相等，不等就同上，否则输出玩完 `YES` 然后输出那两个数就行了。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt[105],sum,a,b;//想用map也可以，乐意就行
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int d;
		cin>>d;
		if(!cnt[d]){//如果没有出现过
			sum++;
			if(!a)a=d;
			else b=d;//存储出现的两个数
		}
		cnt[d]++;
	}
	if(sum!=2){//不等于2的情况
		cout<<"NO";
		return 0;
	}
	if(cnt[a]==cnt[b]){//比对出现次数
		cout<<"YES"<<'\n'<<a<<' '<<b;//输出
		return 0;
	}
	else cout<<"NO";
	return 0;
}
```


---

## 作者：PC_DOS (赞：1)

按照题意模拟即可。

使用一个结构体记录每种牌的花色和数量，根据题意可知，游戏公平的条件是:

1. 只有两种牌

2. 两种牌数量相等

所以就可以得到代码了:
```
#include <iostream>
#include <vector>
using namespace std; //头文件和命名空间
struct Card{ //使用一个结构体记录每种牌的花色和数量
	int iNum; //花色
	int nCount = 1; //数量
};
vector<Card> arrCards; //存放牌的动态数组
int FindPosition(int iNum){ //寻找某种牌是否已经存在，返回-1为不存在，否则返回它在arrCards之中的索引
	int i;
	if (arrCards.size() == 0){ 
		return -1;
	}
	for (i = 0; i <= arrCards.size() - 1; ++i){
		if (arrCards[i].iNum == iNum){
			return i;
		}
	}
	return -1;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nCards,i,iPos; //nCards-总牌数，iPos-对于每一张输入的牌面，存放FindPosition的返回
	Card crdTmp; //暂存输入的牌
	cin >> nCards; //读入总牌数
	for (i = 1; i <= nCards; ++i){ //输入牌
		cin >> crdTmp.iNum;
		iPos = FindPosition(crdTmp.iNum); //确认存在与否
		if (iPos != -1){ //存在
			++arrCards[iPos].nCount; //牌数加一
		}
		else{ //不存在
			arrCards.push_back(crdTmp); //添加进数组
		}
	}
	if (arrCards.size() != 2){ //没有两种牌
		cout << "NO"; //不公平
	}
	else if (arrCards[0].nCount == arrCards[1].nCount){ //只有两种牌且两种牌数量相等
		cout << "YES\n" << arrCards[0].iNum << ' ' << arrCards[1].iNum; //公平
	}
	else{ //两种牌数量不等
		cout << "NO"; //不公平
	}
	return 0; //结束
}
```

---

## 作者：sodak (赞：0)

## 思路
首先记录出现过几种数字，两种以上或者只有一种一定不公平，然后如果两种数字出现的次数相同，那么公平，如果不相同，那么不公平
## code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register 
#define gc getchar()
#define getch while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=gc;}
#define getnu while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=gc;}
using namespace std;
inline int read(){int s=0,f=1;char ch=gc;getch;getnu;return s*f;}
int main(){
	int n=read();
	int id1=0,id2=0,cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++){
		int x=read();
		if(!id1)id1=x,cnt1++;
		else if(!id2&&x!=id1)id2=x,cnt2++;
		else {
			if(x!=id1&&x!=id2)return puts("NO"),0;
			else x==id1?cnt1++:cnt2++;
		}
	}
	if(cnt1!=cnt2||!id1||!id2)return puts("NO"),0;
	puts("YES");
	printf("%d %d\n",min(id1,id2),max(id1,id2));
}


```

---

## 作者：__builtin_orz (赞：0)

这一题主要是模拟
```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;//名字命名空间
int n,a[5],b[10005],na,nb;//定义本题需要的变量
int main()//主函数
{
	a[1]=-999999;
	a[2]=-999999;
   //设置两种数的默认值
   
	cin>>n;//输入n
    
	if(n%2==1)
	{
		cout<<"NO";
		return 0;
	}//特判，如果是单数绝不可能分为两半
    
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}//读入数据
    
	sort(b,b+n+1);//排序
   //排序是为了这个：
   //假如数据是这个：8,8,8,8
   //那么排序后是：8，8,8,8
   if(b[1]==b[n])//这里是设置第一种数是b[1]，第二种数是b[n]。
   {
   		cout<<"NO";
      retrun 0;
   }
   //假如头和尾的数字一样，那么可以说明只有一种数字，即为“NO”。
	//三种或更多种数的情况下面判断
	for(int i=1;i<=n;i++)
	{
		if(b[i]==b[1])na++;//第一种数个数加一
		else
		if(b[i]==b[n])nb++;//第二种数个数加一
		else
		{
			cout<<"NO";
			return 0;
		}//假如不等于第一个也不等于第n个，就是出现了第三种数，直接输出NO。
	}
	if(na==nb)cout<<"YES\n"<<b[1]<<" "<<b[n];//若两种数的数量相等，输出YES
	else cout<<"NO";//若数字不同，输出NO
	return 0;//完结撒花
}
```


---

## 作者：Fat_Fish (赞：0)

**判断条件：** 仅当两个人可以拿走全部的卡片并且两人拿走的卡片数相同,否则这个游戏就是不公平的.

**解题思路：** 我们可以运用$map$,将相同数字卡片的个数记录下来，两重循环，**比较两种不同数字卡片个数是否相等**即可。

$Code$
```cpp
#include<iostream>
#include<bits/stdc++.h>//头文件
#define max(a,b) a>b?a:b//自定义max函数，STL的很慢
using namespace std;
int main(){
	int n;
	cin>>n;//n张卡片
	int a[n+1],max=0;//max是数字的最大值，
	map<int ,int> op;//op储存卡片个数，默认初值为0
	for(int i=1;i<=n;++i){
		cin>>a[i];//输入
		++op[a[i]];//以卡片上的数字进行储存
		max=max(max,a[i]);//打擂台找出数字的最大值
	}
	for(int i=1;i<=max;++i){//根据值寻找，若根据输入寻找可能有重复情况
		if(!op[i]){//若op[i]=0，即没有这张卡片，跳过
			continue;
		}
		for(int j=i+1;j<=max;++j){
			if(!op[j])continue;//同理
			if(op[i]==op[j]){//若两种卡牌个数相等·
				cout<<"YES\n"<<a[i]<<' '<<a[j];//按题意输出 ，YES大写
				return 0;//结束程序
			}
		}
	}
	cout<<"NO\n";//若一直没找到，输出NO
	return 0;
} 
```
$map$的用法见[这篇博客](https://blog.csdn.net/google19890102/article/details/51720305)


---

## 作者：PrefixAMS (赞：0)

# 注意：本题只有在只有两种数的前提下才能YES

#### 之后比较两个数的个数 相等则YES否则NO

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct io
{
	int tong,shu;
}e[100110];
bool cmp(io a,io b)
{
	return a.tong>+b.tong;
}
int a,n,maxn=-101010;
int main()
{
	cin>>n;
	for(int i=1;i<=100010;i++)
	{
		e[i].shu=i;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		e[a].tong++;
	//	cout<<e[a].shu<<" "<<e[a].tong<<endl;
		maxn=max(maxn,a);
	}
	sort(e+1,e+maxn+1,cmp);
	if(e[3].tong) {
		cout<<"NO";
		return 0;
	}
	for(int i=2;i<=100;i++) {
		if(e[i].tong==0) {
		//	cout<<e[i].shu<<" "<<e[i].tong<<endl;
			cout<<"NO";
			return 0;
		}
		if(e[i].tong==e[i-1].tong)
		{
			cout<<"YES"<<endl;
			cout<<e[i-1].shu<<" "<<e[i].shu;
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：以墨 (赞：0)

回归纪念第一发！
看了半天才发现是只能有两种牌......
发现题解中貌似没有用排序做的，就发一下吧。
先不管有几种牌，反正排个序之后相同数字的肯定都会到一块。
再看一下是否恰好是两种还有一半对一半。
因为已经排过序了，在整除之下，要是保证一半对一半，数组(1~n）下标1~n/2的数字肯定要相同，下标n/2+1~n的数字肯定也要相同，再保证不会出现样例2的情况就可以了。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=107;
int a[N],n;
int main(){
	scanf("%d",&n);
	if(n&1){
		printf("NO\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	if(a[1]==a[n>>1]&&a[(n>>1)+1]==a[n]&&a[n]>a[1])
		printf("YES\n%d %d\n",a[1],a[n]);
	else
		printf("NO\n");
	return 0;
}

```


---

## 作者：T_F_P (赞：0)

# 打表

## 介绍一下我的打表：

把每一个输入的数i都存在数组的第i位

这样方便统计每一个数出现了几次

打表准备:

```cpp
int dabiao[10000]; 
```

先清零（memset）:

```cpp
memset(dabiao,0,sizeof(dabiao));
```

再输入（one是一个卡牌的值，方便后期判断）：

```cpp
	int a;
	scanf("%d",&a);
	int b;
	for(int i=0;i<a;i++){
		scanf("%d",&b);
		if(dabiao[b]==0){
			kind++;
			one=b;
		}
		dabiao[b]++;
	}
```

再判断卡牌种类是否为2：

```cpp
if(kind!=2){
		printf("NO");
		return 0;
	}
```

如果为2（one派大用场）：

```cpp
if(dabiao[one]!=a/2){
		printf("NO");
		return 0;
	}
	printf("YES\n");
	for(int i=0;i<1000;i++){
		if(dabiao[i]!=0){
			printf("%d ",i);
		}
	}
```

下面附上全部代码（含注释）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int dabiao[10000]; //特殊打表： 
int main(){
	memset(dabiao,0,sizeof(dabiao));//清零 
	int kind=0;//种类 
	int one;//一种值（方便后面）——看到底你就知道 
	int a;
	scanf("%d",&a);
	int b;
	for(int i=0;i<a;i++){
		scanf("%d",&b);
		if(dabiao[b]==0){
			kind++;
			one=b;//最后一种值 
		}
		dabiao[b]++;
	}//输入完毕 
	if(kind!=2){
		printf("NO");
		return 0;
	}//如果取不光（2种牌以上） 
	if(dabiao[one]!=a/2){
		printf("NO");
		return 0;
	}//两种牌数量不等 
	printf("YES\n");//可以！ 
	for(int i=0;i<1000;i++){
		if(dabiao[i]!=0){
			printf("%d ",i);//输出 （i为卡牌值（详见特殊打表）） 
		}
	}
	return 0;//必写
} 
```

~~本蒟蒻的第四篇题解~~

# 如果觉得有帮助，请点赞！^&^

---

## 作者：2x6_81 (赞：0)

~~这是一道给蒟蒻做的题~~

只要能全部抽完就可以

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,x=0,y=0,a=0,b=0;//定义变量,因为1<=m<=100,所以x,y只要在1~100之外服值可以了
	cin>>n;
	for(int i=0;i<n;i++)//和 for(int i=1;i<=n;i++) 差不多
	{
		cin>>m;
		if(x==0 or x==m) x=m,a++;//如果x未被赋值,x=m;如果x==m,x=m后x的值不会变
		else if(y==0 or y==m) y=m,b++;//如果x!=m,y未被赋值,y=m;如果y==m,y=m后y的值不会变
		else {cout<<"NO"<<endl; return 0;}//如果x!=m,y!=m;那么这就是出口(可能有人用不惯)
	}
	if(a==b) cout<<"YES"<<endl<<x<<' '<<y<<endl;//判断,输出
	else cout<<"NO"<<endl;
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：0)

题目不难~~需要仔细读一下的~~

整理题意为如下条件

1.只有两种牌

2.两种牌数量相等

啊哈！核心已经攻破，打代码去吧！

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct card
{
    int c,id;
}a[101];//桶，牌的数字出现次数（c）和号码（id）
int n,k;
bool cmp(card x,card y)//排序
{
    return x.c>y.c;
}
int main()
{
    cin>>n;
    for(int i=1;i<=100;i++)
        a[i].id=i;//存牌号
    for(int i=1;i<=n;i++)
    {
        cin>>k;
        a[k].c++;//桶计数
    }
    sort(a+1,a+101,cmp);//排序
    for(int i=1;i<=n;i++)//查找
    {
		if(a[i].c==0||i==n)//如果没牌了或已经到了最后一个桶查找还没结束
        {
            cout<<"NO"<<endl;//不能满足条件
            return 0;
        }
        if(a[i].c==a[i+1].c&&a[i].c+a[i+1].c==n)//如果两种牌数量相等且只有两种牌
        {
            cout<<"YES"<<endl<<min(a[i].id,a[i+1].id)<<" "<<max(a[i].id,a[i+1].id)<<endl;//输出YES，牌号
            return 0;
        }
    }
}
```

---

