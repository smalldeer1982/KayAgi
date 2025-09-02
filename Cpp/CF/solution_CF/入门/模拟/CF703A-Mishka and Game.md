# Mishka and Game

## 题目描述

Mishka是一只小北极熊。正如所知的，小熊喜欢在他们的空闲时间为了巧克力玩骰子。在一个美妙的早上，她正走在冰块上时，Mishka遇见了她的朋友Chris，她们就开始玩这个游戏了。

这个游戏的规则十分简单：首先定义一个回合数$n$ 。
在每一回合，每个玩家扔一个在它的表面写着$1$ 到$6$ 的立方体骰子。扔出较大的数的那个玩家获得这一回合的胜利。如果两名玩家扔出的数一样，则没有胜者。

一般来说，赢得较多回合的玩家将获得这个游戏的胜利。如果两个玩家赢得的回合数相同，这场游戏的结果是平局。

Mishka仍然非常的小以至于不能算胜负场，所以她要求你观看这场比赛并确定结果。请帮帮她吧！

## 说明/提示

在第一个样例中，Mishka在第一回合输了，但在第二回合和第三回合赢了，因此她是游戏的获胜者。

在第二个样例中，Mishka在第一回合赢了，Chris在第二回合赢了，游戏结束时以比分1:1战平。

在第三个样例中，Chris在第一回合赢了，但是后面两个回合没有胜利者。游戏的获胜者是Chris。

by @Khassar

## 样例 #1

### 输入

```
3
3 5
2 1
4 2
```

### 输出

```
Mishka```

## 样例 #2

### 输入

```
2
6 1
1 6
```

### 输出

```
Friendship is magic!^^```

## 样例 #3

### 输入

```
3
1 5
3 3
2 2
```

### 输出

```
Chris```

# 题解

## 作者：Taurus_Lzc (赞：2)

到现在见到的为数不多的水题之一  
当然CF还有很多有趣的题  
下见代码：
```cpp
#include<iostream>
using namespace std;
int main(){
	int n,a,b,cnt=0;  //cnt拿来计数
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>a>>b;
		if (a>b) cnt++;  //若Mishka胜则++
		else if (a<b) cnt--;  //不要直接写else，会WA，这里要在判断并--
		else cnt=cnt;  //打平则不动
	}  //下面根据题意简单判断
	if (cnt>0) cout<<"Mishka";  
	else if (cnt<0) cout<<"Chris";
	else cout<<"Friendship is magic!^^";
}
```

---

## 作者：Obito (赞：1)

# 模拟

直接按题意模拟就行。

这么水的题竟然没有人做，难道dalao们都去做难题了吗？？
具体详见代码。
```
#include<bits/stdc++.h>
int ans1,ans2,a,b,i,j,k;//定义变量，ans1表示统计Mishka赢的次数，ans2表示统计Chris赢的次数
using namespace std;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);noip时用的文件
	int n,m;
	cin>>n;//输入总次数
	for(i=1;i<=n;i++) {//边输入边做
	cin>>a>>b;
	if(a>b)ans1++;	//开始统计
	else if(a<b)ans2++;
	}
	if(ans1==ans2)cout<<"Friendship is magic!^^";
	if(ans1>ans2)cout<<"Mishka";
	if(ans1<ans2)cout<<"Chris";//输出
	return 0;//完美结束
}

```
谢谢dalao们观看，作为蒟蒻就只能写写这些水题的题解了！


---

## 作者：PC_DOS (赞：1)

这是一道模拟题，只需要循环读入每一回合的游戏结果，判断每一轮的胜负并在最后判断双方的胜平负即可。

通过一个仅有两个元素的数组来存放双方胜利的次数，非平局的回合里将胜者的计数加一。

当然，对于这道题目来说，通过一个正常的整型数组存放就够了，在实际的运用中，更推荐使用STL提供的map<KeyType, ValueType>数据结构来建立一个从string映射到int的map来存放双方的胜利次数(也就是定义一个map<string, int>)，这样可以提高代码的可读性，便于未来的维护。

代码:
```
#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(false); //输入输出加速
    int nWin[2] = { 0 }, iMishka, iChris, nCount;
    /*
    	nWin - 双方的胜利次数，第一个为Mishka，第二个为Chris
        iMishka - Mishka的点数
        iChris - Chris的点数
        nCount - 回合数
    */
    cin >> nCount; //读入回合数
    while (nCount--){ //循环读入每个回合的资料
        cin >> iMishka >> iChris; //读入点数
        if (iMishka > iChris) //如果Mishka胜
            ++nWin[0]; //胜利次数加一
        else if (iMishka < iChris) //如果Chris胜
            ++nWin[1]; //胜利次数加一
        //平局不处理
    }
    if (nWin[0]>nWin[1]) //如果Mishka胜利
        cout << "Mishka"; //提示
    else if (nWin[0] < nWin[1]) //如果Chris胜利
        cout << "Chris"; //提示
    else //平局
        cout << "Friendship is magic!^^"; //提(马)示(教)平(金)局(句)
    return 0; //结束
}
```

~~话说这题平局的提示是哪个马迷想出来的?~~

---

## 作者：北雪2009 (赞：0)

~~这道题我觉得是一道比超级玛丽游戏还简单的大水题~~   
这道题关键在于要记录Mishka和Chris赢得次数，如果相等，就是打平，否则谁赢得多谁赢。   
贴上代码：         
```cpp
#include<bits/stdc++.h>    //万能头
#include<stdio.h>
using namespace std;
int n,a,b,m,c,f;
int main(){
	ios::sync_with_stdio(false);   //cin,cout快读快输，用scanf和printf的同学就不要用了，会RE
	cin>>n;
	for(int i=1;i<=n;i++){    //循环读入
		cin>>a>>b;   
		if(a>b) m++;      //检测在这一回里谁赢
		if(a<b) c++;
	}
	if(m>c) cout<<"Mishka";    //判断输出
	else if(m<c) cout<<"Chris";
		else if(m==c) cout<<"Friendship is magic!^^";
	return 0;    //以一个华丽的return 0;结束
}

```

---

## 作者：_edge_ (赞：0)

一眼望下去，咦？怎么没有用scanf的呢？

scanf和printf比cin和cout要快一点。

好了我们先来看一下题目

题目大概意思

就是有n对数，然后让你去将它们比大小记录，谁赢的多谁获胜

这道题我们先用cin和cout做：

```cpp
#include <iostream>
using namespace std;

```
> 头文件

```

        int n,Mishka=0,Chris=0;
        cin>>n;

```
> 然后设变量n(有n对数)，Mishka(Mishka赢的次数)，Chris(赢的次数)。

```cpp
        cin>>n;
        for (int i=1; i<=n; i++)//循环n对数
        {
                int s1,s2;
                cin>>s1>>s2;//读入每次的数字
                if (s1>s2) Mishka++;//如果这一轮Mishka赢那么他加一
                if (s2>s1) Chris++;//如果这一轮Chris赢那么他加一
        }
```

> 读入n，然后开始记录

```cpp
        if (Mishka>Chris) cout<<"Mishka"<<endl;//如果Mishka赢那么输出"Mishka"
        if (Chris>Mishka) cout<<"Chris"<<endl;//同上
        if (Mishka==Chris) cout<<"Friendship is magic!^^"<<endl;//如果平局那么输出"Friendship is magic!^^"
```
> 输出结果

然后我们来思考怎么用scanf和printf加速

把cin和cout改成scanf和printf就可以了

下面附上完整代码：

```cpp
#include <cstdio>//可不用iostream
//可不用std命名空间
int main()
{
        int n,Mishka=0,Chris=0;
        scanf("%d",&n);
        for (int i=1; i<=n; i++)
        {
                int s1,s2;
                scanf("%d %d",&s1,&s2);
                if (s1>s2) Mishka++;
                if (s2>s1) Chris++;
        }
        if (Mishka>Chris) printf("Mishka\n");
        if (Chris>Mishka) printf("Chris\n");
        if (Mishka==Chris) printf("Friendship is magic!^^\n");
        return 0;
}
```

总结

这道题的标签是：统计和模拟

---

也在这里祝各位大佬，同学CSP-j或CSP-S RP++！！

---

## 作者：丁丁の丁丁 (赞：0)

cf的题就是简单，下面来看代码
~~~~
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,m,k,l=0,i,s=0;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>m>>k;
		if(m>k) s++; //Mishka赢一局，计数器+1；
		if(k>m) l++;//Chris赢一局，计数器+1；
		if(m=k) s=s+0;//一样的话不加；
	}
	if(s>l) cout<<"Mishka";
	else if(l>s) cout<<"Chris";
	else cout<<"Friendship is magic!^^";//判断n局谁赢得多，相等的话输出Friendship is magic^^!
	return 0;
 } 
 ~~~~
 希望本蒟蒻的代码能帮助到各位，同时也祝谷民们建党节快乐

---

## 作者：土川崇贺 (赞：0)

	分开统计，最后比较。
   ```
#include<iostream>
using namespace std;
int main()
{
    long long n,as=0,bs=0;
	cin>>n;
	long long a[n],b[n];
	for(int i=0;i<n;i++)
	{
		cin>>a[i]>>b[i];
		if(a[i]>b[i])
		{
			as++;
		}
		if(b[i]>a[i])
		{
			bs++;
		}
	}
	if(as>bs)
	{
		cout<<"Mishka";
	}
	else if(as<bs)
	{
		cout<<"Chris";
	}
	else
	{
		cout<<"Friendship is magic!^^";
	}
	return 0;	
}
```

---

## 作者：罗贤泽 (赞：0)

一道模拟题，比较简单~~水~~，只要统计一下双方每局的对战情况，最后判断就行了。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int Mishka=0,Chris=0;//这两个变量记录了双方的胜负情况 
	int n;
	cin>>n;//读入有多少回合
	for(int i=0;i<n;i++)
	{
		int t1,t2;//两个临时变量，用来存放点数
		cin>>t1>>t2;
		if(t1>t2)//判断胜负 
		{
			Mishka++;	
		}	
		if(t2>t1)
		{
			Chris++;
		}
	}
	if(Mishka>Chris)
	{
		cout<<"Mishka";	
	} 
	else if(Mishka<Chris)
	{
		cout<<"Chris"; 
	} 
	else
	{
		cout<<"Friendship is magic!^^";
	}
	return 0;	
} 
```

---

