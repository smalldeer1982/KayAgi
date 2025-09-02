# Queue at the School

## 题目描述

During the break the schoolchildren, boys and girls, formed a queue of $ n $ people in the canteen. Initially the children stood in the order they entered the canteen. However, after a while the boys started feeling awkward for standing in front of the girls in the queue and they started letting the girls move forward each second.

Let's describe the process more precisely. Let's say that the positions in the queue are sequentially numbered by integers from $ 1 $ to $ n $ , at that the person in the position number $ 1 $ is served first. Then, if at time $ x $ a boy stands on the $ i $ -th position and a girl stands on the $ (i+1) $ -th position, then at time $ x+1 $ the $ i $ -th position will have a girl and the $ (i+1) $ -th position will have a boy. The time is given in seconds.

You've got the initial position of the children, at the initial moment of time. Determine the way the queue is going to look after $ t $ seconds.

## 样例 #1

### 输入

```
5 1
BGGBG
```

### 输出

```
GBGGB
```

## 样例 #2

### 输入

```
5 2
BGGBG
```

### 输出

```
GGBGB
```

## 样例 #3

### 输入

```
4 1
GGGB
```

### 输出

```
GGGB
```

# 题解

## 作者：6954717a (赞：8)

##### 这个题我的想法可能有点复杂
###### ~~但总归做出来了~~

看见各位大佬没有发题解的，那我便来凑个数。

## 第一篇题解，各位神犇莫嘲讽QAQ

下面正文开始

首先定义几个变量n,t,ans，因为题干中指明小孩们不超过50个，那么这个题便觉得用字符数组比较好一些
### 便于查看每个变量时态的各个位置。

#### 接着就搜索，搜索就好了···

# 下面上代码Code

    #include<iostream>
    #include<cstdio>
    #include<algorithm>
    using namespace std;
    char a[100];
    int n,t,ans;
    int print()//输出 
    {
        for(int i=1;i<=n;i++)
        cout<<a[i];
    }
    int search(int i)
    {
        for(int i=1;i<=n;i++)
            if(a[i]=='B'&&a[i+1]=='G')
            {
                a[i]='G';
                a[i+1]='B';//进行替换 
                i++;//替换之后需要加一次i(换位是两个人换) 
            }
        ans++;//搜索一次计数器就加一次 
        if(ans==t)print();//如果时间达到了规定就输出 
        else search(i+1);//不达到接着搜索 
    }
    int main()
    {
        scanf("%d%d",&n,&t);
        for(int i=1;i<=n;i++)
        cin>>a[i];//输入 
        search(1);//开始搜索 
    }
    
## 杜绝抄袭，从我做起！！！

---

## 作者：HNYLMS_MuQiuFeng (赞：5)

这道题目其实是这样的：

课间休息时，小学生、男孩和女孩在食堂里排成一队。最初孩子们站在食堂里排队。然而，过了一会儿，男孩子们站在排在队伍前面的女孩们开始感到尴尬，他们开始让女孩每秒向前移动。

让我们更精确地描述这个过程。假设队列中的位置由1到n的整数顺序编号，位置号1中的人首先被服务。然后，如果在时间X，男孩站在第i个位置，女孩站在第i+1个位置，然后下一秒，男孩女孩的位置会交换，也就是此时第i个是女孩，第i+1个是男孩。时间是以秒为单位给出的。

在最初的时刻，你得到了孩子们的初始位置。确定队列在T秒之后的方式。

输入

第一行包含两个整数n和t（1≤n，t≤50），表示队列中的子数和队列将转换成需要查找的排列的时间。

下一行输入字符串s，s仅由‘B’和‘G’构成（B表示男孩，G表示女孩）

输出

输出字符串A，它描述了T秒后的排列。

## 其实这道题可以直接用循环做，时间复杂度为O(n*t)；

下面直接上代码：
```cpp
#include<iostream>//万能头固然好，可我就是不想用你来打我啊（划掉）
#include<cstdio>//可是对于OI选手们来说还是得了解一下各种库的
#include<string>
using namespace std;
string s;int len,a,n;//这道题我是直接用字符串做的所以第一个输入数据其实
//对我的程序没有什么用只是因为数据原因必须输入而已
int main()
{
	cin>>a>>n;//输入a,n（a在这里只是为了迎合读入的第一个数据）
	cin>>s;len=s.size();//读入字符串，
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<len;j++)
		{
			if(s[j]=='B'&&s[j+1]=='G')
			{
				swap(s[j],s[j+1]);j++;//如果这一次交换了那么下一位就
                //不必交换，所以要跳掉一个（因为有可能是BGG）
                //换了以后变成（GBG）
                //如果不加一在下一次搜索还会交换变成（GGB）
			}
		}
	}
	cout<<s;
	return 0;//愉快の输出，AC啦，锵锵！
 } 
```
## 杜绝抄袭，从我做起！！！

---

## 作者：Dancing_Wave (赞：2)

这道题是一个基础的模拟题，我们按照题意模拟即可：

每一个时间点从对头到队尾找如过前面的是男生，后面的是女生就将他俩交换。

但是，这道题说每个时间点每个人最多只能换一次，那么每交换一次就直接从他们俩后面的人继续找，就避免了一个男生一个时间点交换好几次的情况了。

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
string s; //方便储存男生女生的排列
int main(){
	cin>>n>>t;
	cin>>s;
	for(int i=1;i<=t;i++){
		for(int i=0;i<n-1;i++){//本来应该是1~n-1但因为字符串从0开始存，所以是0~n-2
			if(s[i]=='B'&&s[i+1]=='G'){//题目条件
				swap(s[i],s[i+1]);//交换
				i++;//直接到下一位学生
			}
		}
	}
	cout<<s<<endl;//输出我们要求的状态
	return 0;
}
```

---

## 作者：liuzitong (赞：1)

这题我看其他dalao的题解了，其实一开始我跟他们方法差不多。
只是我输入字符串的时候一开始用了gets，导致我以为方法错了，然后换了个不太一样的做法。
##### 每一轮一个人只可能交换一次，于是我们可以标记（常规思路），但这样做就有点像“多测”，必须要“清空”标记数组（因为一个人虽然在一轮只能交换一次，但不只一轮）

###### 方法主要思路：
###### 从第一个字符开始如果他是‘B’&&他的下一个是‘G’（~~B喜欢G~~）所以就交换啦~ ~但每一轮一个人只可能交换一次，所以做个标记，下一次在遇到就不交换了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);//cin的优化，写上是个好习惯哦~
	int a,i;
	cin>>a;//输入队列长度
	char s[a];//这是那个“队”
	bool b[a];//标记
	memset(b,0,sizeof(b));//千万清空
	int t;
	cin>>t;//输入几轮
	cin>>s;//输入队
	for(int j=0;j<t;j++){//循环t次
	for(i=1;i<=strlen(s);i++){//循环strlen个人
		if(s[i]=='G'&&s[i-1]=='B'&&b[i]==0&&b[i-1]==0){//如果没有标记并且男的在女的前面
			s[i]='B';
			s[i-1]='G';//交换
			b[i]++;//标记
			b[i-1]++;
		}
	}
	memset(b,0,sizeof(b));//标记
	}
	cout<<s<<'\n';//输出
	return 0;
}

```
觉得好可以点赞哦！！！


---

## 作者：xxxjz (赞：0)

就这道题也能评得上普及？额——

算了，不说废话，先给大家讲一下思路吧！

站在女孩们前面的男孩们开始感到尴尬，下一秒，他们会让身后的女孩站到自己前面。从这句话可看出只要当前位置是男生（B），下一个位置是女生（G）,他们俩就要交换位置。

### - 所以我们可以判断：如果当前位置是男生，并且下一个位置是女生，就交换位置。

判断代码如下：
```cpp
if(st[i]=='B'&&st[i+1]=='G')swap(st[i],st[i+1]);
```

注意事项：交换后记得要把位置+1，这样才能到下一对可能交换的组合。

俗话说得好：代码虽小，五脏俱全，让本蒟蒻顺便贴上代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
string st;
int main()
{
    cin>>n>>t;
    cin>>st;
    for(int q=1; q<=t; q++)
    for(int i=0; i<st.size()-1; i++)
	    if(st[i]=='B'&&st[i+1]=='G')  {swap(st[i],st[i+1]);i++;}
	cout<<st;
  return 0;
}

```


---

## 作者：Kirito_1205 (赞：0)

**本蒟蒻第一次发题解，大佬不要喷啊QWQ**

这道题直接**模拟**

### 主要考虑一下变换位置时的重叠情况（听不懂没关系，你WA的时候你就知道了）
**大致思路讲一下：输入进来一个字符串，然后直接从头来，如果当前是B且下一个是G，那么记录当前的坐标，1秒过后统一进行处理（我的思路其实有点繁琐的）**

代码里有注释，可以自己看
## 话不多说，上Code~
```cpp
#include<iostream>
//防抄袭（不过你要是删了也没用呢QWQ）！ 
using namespace std;
int main()
{
	int n,T;//人数和时间 
	int i,j,temp=0;
	char t;//作交换用的变量 
	string s;//队列 
	cin>>n>>T;
	cin>>s;//输入 
	while(T--)//反正T后面没用，从一个大佬处学到的 
	{
		int xy[1000]={0};//记录要交换的坐标 
		temp=0;//有若干秒，所以做初始化 
		for(i=0;i<n;i++)
		{
			if(s[i]=='B'&&s[i+1]=='G')//如果当前是B且i+1是G 
			{
				xy[temp]=i;//记录当前坐标 
				temp++;//次数加一 
			}
		}
		for(i=0;i<temp;i++)//开始处理 ，注意是小于号 
		{
			t=s[xy[i]];
			s[xy[i]]=s[xy[i]+1];
			s[xy[i]+1]=t;//交换三步走（如果有更简单得写法可以评论） 
		}
	}
	for(i=0;i<n;i++)
	{
		cout<<s[i];//输出 
	}
	return 0; //完美の结束！ 
}
```
OK！
求管理员大大给过啊！！！~~虽然写的并不是很辛苦呢~~~

---

## 作者：fls233666 (赞：0)

**2020年2月13日更新：按照要求修正题解格式**

-------

初见这题，看到 $(1<=n,t<=50)$，就决定**模拟**来解决这题。

我想，既然是每一秒男孩都会让在他后面的女孩排到他的前面，就可以模拟每一秒的所有交换，最后把整个交换后的字符串输出即可。

于是，我先打出了下面的代码：

```cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
    int n,t;
    char c;
    string queue;  //存队列
    cin>>n>>t;  
    cin>>queue;
  	//输入数据
  
    for(int ti=1;ti<=t;ti++){
        for(int i=0;i<n-1;i++){
            if(queue[i]=='B'&&queue[i+1]=='G'){
  				//如果第i个位置是男孩且第i+1个位置是女孩
  				//暴力交换
  				c=queue[i];
  				queue[i]=queue[i+1];
  				queue[i+1]=c;
  			}
        }
    }
  
    cout<<queue;  //输出
    return 0;
}
```

然后连样例都过不去......

## why?

我们看看样例一循环的整个过程：

初始队列：$\texttt{BGGBG}$；

当 $i=0$ 时，符合 if 条件，交换，得：$\texttt{GBGBG}$；

**当 $i=1$ 时，符合 if 条件，交换，得：$\texttt{GGBBG}$**；

当 $i=3$ 时，符合 if 条件，交换，得：$\texttt{GGBGB}$；

输出 wrong answer: $\texttt{GGBGB}$。

**显然，中间多交换了一次！**


------------


### 新策略

1. 循环把 $0 \to n-2$ 的位置遍历一遍（** n-1 就是队尾了，防越界不遍历**）；
2. 把所有男孩的下标位置存到一个动态数组 vector 里面（ _用动态数组省内存_ ）；
3. 循环遍历 vector，检查每个男孩的位置，进行交换；
4. 重复1到3步 $t$ 遍，输出结果（**注意每次循环之前要把 vector 数组清空**！）；


------------


AC 代码如下：

```cpp
#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main(){
    int n,t;
    string queue;
    cin>>n>>t;
    cin>>queue;
    vector<int>boy;  //存男孩下标位置的动态数组
  
    for(int ti=1;ti<=t;ti++){
        boy.clear();  //注意要清空！！
        for(int i=0;i<n-1;i++){
            if(queue[i]=='B')
                boy.push_back(i);  //记录位置
        }
        for(int i=0;i<boy.size();i++){
            if(queue[boy[i]+1]=='G'){  //检查每个男孩位置
                //更暴力的交换
                queue[boy[i]]='G';
                queue[boy[i]+1]='B';
            }
        }
    }
                                       
    cout<<queue;    //输出答案
    return 0;
}
```


---

