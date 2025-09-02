# [USACO2.3] 零的数列 Zero Sum

## 题目描述

请考虑一个由 $1$ 到 $N$ 的数字组成的递增数列：$1, 2, 3, \ldots, N$。

现在请在数列中插入 `+` 表示加，或者 `-` 表示减，` `（空格） 表示空白（例如 `1-2 3` 就等于 `1-23`），来将每一对数字组合在一起（请不要在第一个数字前插入符号）。

计算该表达式的结果并判断其值是否为 $0$。 请你写一个程序找出所有产生和为零的长度为N的数列。


## 说明/提示

翻译来自NOCOW

USACO 2.3


## 样例 #1

### 输入

```
7
```

### 输出

```
1+2-3+4-5-6+7
1+2-3-4+5+6-7
1-2 3+4+5+6+7
1-2 3-4 5+6 7
1-2+3+4-5+6-7
1-2-3-4-5+6+7```

# 题解

## 作者：john666 (赞：24)

速度很快的：

分析：

1、搜索对象为符号位，共n-1个；

2、搜索状态search(int k,int s,int q,char c)；

对于每数字后面可加的符号有空格、+、-三种；

k为第几个，s为当前总和，q为待处理的前一个数值，c为最后一个非空格符号；

3、搜索条件：分别搜索三种符号所得的表达式的和，当k=n且和为0时输出；

4、返回处理：每次返回时需要从上一个数开始向下搜索。

详见代码：

-----------------------------------------------------------

```cpp
#include<bits/stdc++.h>//john.c_Tae Yeon
#define sea 1000500
using namespace std;
int n,sz[20],ss;
char symbol[20];
void sear(int k,int s,int q,char c){
    if(k==n){
        if(c=='+'){
            s=s+q;
        }
        else{
            s=s-q;
        }
        if(s==0){
            ss++;
            cout<<"1";
            for(int i=1;i<n;i++){
                cout<<symbol[i]<<sz[i];
            }
            cout<<" "<<ss<<endl;
        }
    }
    else{
        symbol[k]=' ';
        sear(k+1,s,q*10+sz[k],c);
        symbol[k]='+';
        if(c=='+'){
            sear(k+1,s+q,sz[k],'+');
        }
        else{
            sear(k+1,s-q,sz[k],'+');
        }
        symbol[k]='-';
        if(c=='+'){
            sear(k+1,s+q,sz[k],'-');
        }
        else{
            sear(k+1,s-q,sz[k],'-');
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        sz[i]=i+1;
    }
    sear(1,0,1,'+');
    return 0;
}
```

---

## 作者：redegg (赞：16)

因为这题最多只有9个数字，也就是最多只有8个符号。

我们可以采取暴力直接枚举出所有可能。

然后交给勤劳的双手写判断。。。。。。。

我将“ ”“+”“-”分别用数字1,2,3代替，后来发现输出刚好是ascll码表的排列。

先是dfs，然后将空格去掉，在此我是将去掉空格后的数字和符号都存到了两个新的数组里面。

最后for一遍存数字的和存符号的（并且计算），如果发现算出来为0就将这个迷一般的东西输出出来。

一句话，暴力出奇迹。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[10];
int b[10];
int f[10];
int z[10];

bool run(int n)
{
    memset(f,0,sizeof(f));
    int p=1;
    f[p]=1;
    for(int i=1;i<=n;i++)
    {
        if(a[i]==0)
        {
            f[p]=f[p]*10+i+1;
        }
        else
        {
            z[p]=a[i];
            p++;
            f[p]=f[p]*10+i+1;
        }
    }
    int ans=f[1];
    /*
    for(int i=1;i<=p;i++)
    {
        cout<<f[i]<<" ";
    }
    cout<<endl;
    system("pause");*/
    for(int i=1;i<p;i++)
    {
        if(z[i]==1)
        {
            ans+=f[i+1];
        }
        else
        {
            ans-=f[i+1];
        }
        //cout<<ans<<endl;
    }
    if(ans==0)return 1;
    else return 0;
}

void dfs(int v,int x)
{
    if(v==x)
    {
        if(run(x))
        {
            cout<<1;
            for(int i=1;i<=x;i++)
            {
                if(a[i]==1)cout<<"+"<<i+1;
                if(a[i]==0)cout<<" "<<i+1;
                if(a[i]==2)cout<<"-"<<i+1;
            }
            cout<<endl;
        }
        return ;
    }
    for(int i=0;i<=2;i++)
    {
        a[v+1]=i;
        dfs(v+1,x);
    }
}

int main()
{
    int n;
    cin>>n;

    for(int i=0;i<=2;i++)
    {
        a[1]=i;
        dfs(1,n-1);
    }
    return 0;
}
```

---

## 作者：Celebrate (赞：12)

这一题我们dfs数字间的符号，找到n-1个符号就判断一次

如果可行就输出

dfs比较容易打，但是判断有一些难，为了减少难度，我在1之

前放一个‘+‘，这一符号就会和数字一样多了，也不用麻烦的找

第一个了

这个优化是这样的：

原来：   1+2+3+4+5+6+7
改变后：+1+2+3+4+5+6+7

代码如下：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n,a[11];
char s[3]={' ','+','-'};
inline bool check()//判断是否可行，整个程序最难的地方 
{
	int ans=0,t;
	for(int i=1;i<=n;i++)//n个符号 
	{
		if(a[i]==0) continue;//如果是‘ ’就不用管了 
		t=i;
		for(int j=i+1;j<=n;j++)//找‘ ’ 
		{
			if(a[j]!=0) break;//如果不是空格，就不管了 
			t=t*10+j;
		}
		if(a[i]==1) ans+=t;//加或减 
		else ans-=t;
	}
	if(ans==0) return true;//返还 
	return false;
}
void dfs(int k)
{
	if(k==n+1)//如果符号找完了 
	{
		if(check()==true)//判断是否可以 
		{
			printf("1");//如果可以就输出 
			for(int i=2;i<=n;i++) printf("%c%d",s[a[i]],i);
			printf("\n");
		}
	}
	else
	{
		for(int i=0;i<=2;i++)//递归 
		{
			a[k]=i;//记录值 
			dfs(k+1);//往下搜索 
			a[k]=0;//回溯 
		}
	}
}
int main()
{
	scanf("%d",&n);a[1]=1;//刚刚说的在1之前放符号 
	dfs(2);//从第二个开始 
	return 0;
}
```

---

## 作者：光明正大 (赞：11)

**粗略翻了一遍题解发现都很长，便自己写了一份貌似很短的bfs**

大佬勿喷

大致思路如下：

------------

对于每个空，要么不填符号，要么+，要么-

还有就是先简单初始化一下，记录数字i到j组成的数

另开一个string记录结果存起来，最后sort一遍

话不多说，上代码：

~~不理解的的看注释~~
```cpp
//谢绝抄袭，后果自负
#include<algorithm>
#include<iostream>
using namespace std;
//a表示从i到j组成的数字
//ans0表示当前方案计算结果
int n,ans,ans0,a[11][11],a0[11]={0,1,2,3,4,5,6,7,8,9};
//anss为当前的方案，ansss为最终方案
string anss="1 2 3 4 5 6 7 8 9",ansss[110];
//x表示搜索完了x
inline void search(int x)
{
//搜完n个数，判断是否符合题意
	if(x==n) {if(ans0==0) {ans++;ansss[ans]=anss;}return ;}
	for(int i=x+1;i<=n;i++)//不填的情况包括在循环里
	{
//填+
		ans0+=a[x+1][i];anss[x*2-1]='+';
		search(i);
//回溯
		ans0-=a[x+1][i];anss[x*2-1]=' ';
//填-
		if(x)//首位不能填-
		{
			ans0-=a[x+1][i];anss[x*2-1]='-';
			search(i);
//回溯
			ans0+=a[x+1][i];anss[x*2-1]=' ';
		}
	}
}
int main()
{
	cin>>n;
//初始化
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) for(int k=i;k<=j;k++) a[i][j]=a[i][j]*10+a0[k];
	search(0);
//按字典序排序
	sort(ansss+1,ansss+ans+1);
	for(int i=1;i<=ans;i++)
	{
//不要输出多了
		for(int j=0;j<=2*n-1;j++) cout<<ansss[i][j];
		cout<<endl;
	}
	return 0;
}
```
大致就是这样

不懂的可以私信问我

望管理员通过

谢谢大家

---

## 作者：jzqjzq (赞：7)

膜拜一下楼下写三进制和在DFS里计算的大神们   OrzOrzOrz

本蒟蒻直接无脑爆搜，代码比楼下写爆搜C++大神们的要短

wsm呢，我直接在DFS外建好原串：

形如“1 2 3 4 5 6 7 8 9”对就是这样；

然后在搜索中直接把空格换成加减号，这样其实很方便

还有我这个程序好像无需判重（#斜眼笑#）

wsm呢，字符串处理时枚举空格不用判重

是不是很暴力呢

详见代码：

```cpp
#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
using namespace std;
int n;
bool check(string s){//别看这么长，都是Ctrl+C,Ctrl+V，不信往下看
    char p='+';//预处理
    int l=s.size();int x=0,y=0;
    for(int i=0;i<l;i++){
        if(s[i]==' ')continue;//空格直接忽略
        if(s[i]>='0'&&s[i]<='9')y=y*10+(int)(s[i]-'0');//处理数字
        if(s[i]=='+'){//计算加
            if(p=='+')x=x+y;
            if(p=='-')x=x-y;
            y=0;//清空，下同
            p='+';
        }
        if(s[i]=='-'){//计算减
            if(p=='+')x=x+y;
            if(p=='-')x=x-y;
            y=0;
            p='-';
        }
    }
    if(p=='+')x=x+y;//最后答案计算，和前面一模一样
    if(p=='-')x=x-y;
    if(x==0)return true;//判断
    return false;
}
void dfs(int k,string s){//是不是很短？很暴力？
    if(k==n){//搜完
        if(check(s))cout<<s<<endl;//直接交给求值
        return;
    }
    int p=2*k-1;//计算空格位置
    dfs(k+1,s);
    s[p]='+';
    dfs(k+1,s);
    s[p]='-';
    dfs(k+1,s);//五行解决字符串处理
}
int main()
{
    cin>>n;
    string s;
    for(int i=1;i<=n;i++)s=s+(char)(i+'0')+' ';//建串形如“1 2 3 4 5 6 7 8 9”
    s.erase(2*n-1,1);
    dfs(1,s);//直接导入字符串
        return 0;
}
```

---

## 作者：jiu_fen_ku_ye_ye (赞：3)




这题数据小，用回溯做很好。
但是一定要注意细节的处理
~~~~
#include<bits/stdc++.h>
using namespace std;
int shu[10]={0,1,2,3,4,5,6,7,8,9},n,k[21];//shu是1至9的数;n是输入的数据;k为符号 
void rec(int a,int b,int c,int d)//a->现在的次数;b->累加值;c->下一个符号(1--'+';2--'-';空格不包括);d->未经处理的数 
{
	if (a==n)//当次数达到时，进行判断 
	{
		if (c==1)//最后一次处理不要忘记 
			b+=d;
		else
			b-=d;
		if (b==0)//如果为 0，输出。否则回溯 
		{
			for (int i=1;i<=n;i++)
			{
				cout<<i;
				switch(k[i])
				{
					case 1:cout<<"+";break;//判断符号 
					case 2:cout<<"-";break;
					case 3:cout<<" ";break;
				}
			}
			cout<<endl;
		}
	}
	else//按照ASCLL码排序，空格最小，然后是加号，再是减号，因此按照' '->'+'->'-'的顺序查找
	{
		k[a]=3;//空格下一个符号不变，数字累加到d中 
		rec(a+1,b,c,10*d+shu[a+1]);
		k[a]=1;//a++;累加的值加上(c=1)或减去(c=2)d;c变为k[a];d变为下一个数 
		if (c==1)//加和减每个分两种情况讨论：1.现在的符号为 +；2.现在的符号为 - 
			rec(a+1,b+d,k[a],shu[a+1]);
		else
			rec(a+1,b-d,k[a],shu[a+1]);
		k[a]=2;
		if (c==1)
			rec(a+1,b+d,k[a],shu[a+1]);
		else
			rec(a+1,b-d,k[a],shu[a+1]);

	}
}
int main()
{
	cin>>n;
	rec(1,0,1,1);//调用函数 
	return 0; 
}
~~~~
以上就是代码，供大家参考。
如有不当，还请大佬们多谅解

---

## 作者：梦里调音 (赞：3)

 ## 思路极简！！！
 
 @redegg
 
 感谢！（run部分借鉴了您的程序）
 
 但思路是自己的！！！
 
 算法：
 
 # DFS
 
 或者叫：
 
 # 暴搜
 
 qaq
 
 还有一点要注意：
 
 	输出要按照ASCII码的顺序
    
 所以，如果读者的代码是按：+ - _
 
 会WA三个点
 
 正确顺序：_ + -
 
 我们用s数组记录符号，1：_；2：+；3：-
 
 直接在主程序里DFS即可
 
 ```
#include <iostream>
using namespace std;
int n,s[1000001];//_+-
bool run(){//这段是求和（借鉴来的）
	int f[10]={0},z[10]={0};
	int p=1;
    f[p]=1;
    for(int i=1;i<=n;i++)
    {
        if(s[i]==1)
        {
            f[p]=f[p]*10+i+1;
        }
        else
        {
            z[p]=s[i];
            p++;
            f[p]=f[p]*10+i+1;
        }
    }
    int ans=f[1];
    for(int i=1;i<p;i++){
    	if(z[i]==2){
    		ans+=f[i+1];
		}
		else{
			ans-=f[i+1];
		}
	}
	if(ans==0){
		return 1;
	}
	else return 0;
    
}
int main(void){
	cin>>n;
	n--;注意要--，否则会大一个数（我也母鸡why）
	int p=1;
	s[1]=1;
	while(p>0){//DFS
		if(s[p]>3)p--;
		else{
			if(p==n){//长度达到
				if(run()==1){//和==0
					cout<<1;//输出
					for(int i=1;i<=n;i++){
						if(s[i]==2)cout<<"+"<<i+1;
						else if(s[i]==3)cout<<"-"<<i+1;
						else cout<<" "<<i+1;
					}
					cout<<endl;
				}
			}
			else{
				s[++p]=0;//进栈+初始化
			}
		}
		s[p]++;//这个不解释了
	}
}
```


---

## 作者：SIGSEGV (赞：3)

dfs是一个好东西。
用一个STL vector来放置操作符，用深搜来生成所有可能。

calc函数直接套模板

贴代码：
```cpp
#include <bits/stdc++.h> 
using namespace std;
int n,l;//n是数字，l是表达式长度
vector<char> opt;
char expr[50];
int calc()
{
	char oop = '+';int sum = 0,num = 0;
    //sum是总和，num是当前数
	for (int i = 0;i < l;i++)
	{
		if (isdigit(expr[i])) num = num * 10 + expr[i] - '0';//计算num
		else 
		{
			if (oop == '+') sum += num,num = 0;
			else sum -= num,num = 0;//更新sum
			oop = expr[i];
		}
	}
	if (oop == '+') sum += num;else sum -= num;//最后一步也要计算
	return sum; 
}
void dfs(int num) //深搜，其实num可以用opt.size()代替
{
	if (num == n)
	{
		memset(expr,0,sizeof(expr));l = 0;//重置
		expr[l++] = '1';//第一个前面不加符号
		for (int i = 2;i <= n;i++)
		{
			if (opt[i - 2] != ' ') expr[l++] = opt[i - 2];//运算符，忽略空格
			expr[l++] = i + '0';
		}
		if (calc() == 0)
		{
			printf("1");
			for (int i = 2;i <= n;i++) printf("%c%d",opt[i - 2],i);//打印
			printf("\n");
		}
		return;
	}
	opt.push_back(' ');dfs(num + 1);opt.pop_back();
	opt.push_back('+');dfs(num + 1);opt.pop_back();
	opt.push_back('-');dfs(num + 1);opt.pop_back();//扩展
}
int main ()
{
	scanf("%d",&n);
	dfs(1);
	return 0;
}
```

---

## 作者：BuXiangJuanLe (赞：2)

DFS写了半天竟然写不出来……

虽然题解里有枚举的算法，但这篇更简单粗暴，直接分n的情况讨论，一点脑子也不用过~~（一点思维含量也没有但还是无耻地求管理员通过Orz）~~

求和的时候记录上一个数的正负，到下一个数的时候加上或减去上一个数。注意最后会少加/减一个数，要补上

code:

```cpp
// luogu-judger-enable-o2
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
string num = "1 2 3 4 5 6 7 8 9";
string o = " +-";

void check(){
    int sum = 0, cur = 0;
    int last = 1;
    for(int i=0 ; i<2*n-1 ; i++){
        if(isdigit(num[i])) cur = cur*10 + (num[i]^48);
        else{
            if(num[i] == ' ') continue;
            sum += last*cur;
            cur = 0;
            if(num[i] == '+') last = 1;
            if(num[i] == '-') last = -1;
        }
    }
    sum += last*cur;
    if(sum == 0) cout<<num.substr(0, 2*n-1)<<endl;
}

int main(){
    cin>>n;
    switch(n){
        
        case 3:{
            for(int a=0 ; a<3 ; a++){
                num[1] = o[a];
                for(int b=0 ; b<3 ; b++){
                    num[3] = o[b];
                    check();
                }
            }			
            break;
        }
        
        case 4:{
            for(int a=0 ; a<3 ; a++){
                num[1] = o[a];
                for(int b=0 ; b<3 ; b++){
                    num[3] = o[b];
                    for(int c=0 ; c<3 ; c++){
                        num[5] = o[c];
                        check();
                    }
                }
            }			
            break;
        }
        
        case 5:{
            for(int a=0 ; a<3 ; a++){
                num[1] = o[a];
                for(int b=0 ; b<3 ; b++){
                    num[3] = o[b];
                    for(int c=0 ; c<3 ; c++){
                        num[5] = o[c];
                        for(int d=0 ; d<3 ; d++){
                            num[7] = o[d];
                            check();
                        }
                    }
                }
            }			
            break;
        }
        
        case 6:{
            for(int a=0 ; a<3 ; a++){
                num[1] = o[a];
                for(int b=0 ; b<3 ; b++){
                    num[3] = o[b];
                    for(int c=0 ; c<3 ; c++){
                        num[5] = o[c];
                        for(int d=0 ; d<3 ; d++){
                            num[7] = o[d];
                            for(int e=0 ; e<3 ; e++){
                                num[9] = o[e];
                                check();
                            }
                        }
                    }
                }
            }				
            break;
        }
        
        case 7:{
            for(int a=0 ; a<3 ; a++){
                num[1] = o[a];
                for(int b=0 ; b<3 ; b++){
                    num[3] = o[b];
                    for(int c=0 ; c<3 ; c++){
                        num[5] = o[c];
                        for(int d=0 ; d<3 ; d++){
                            num[7] = o[d];
                            for(int e=0 ; e<3 ; e++){
                                num[9] = o[e];
                                for(int f=0 ; f<3 ; f++){
                                    num[11] = o[f];
                                    check();
                                }
                            }
                        }
                    }
                }
            }				
            break;
        }
        
        case 8:{
            for(int a=0 ; a<3 ; a++){
                num[1] = o[a];
                for(int b=0 ; b<3 ; b++){
                    num[3] = o[b];
                    for(int c=0 ; c<3 ; c++){
                        num[5] = o[c];
                        for(int d=0 ; d<3 ; d++){
                            num[7] = o[d];
                            for(int e=0 ; e<3 ; e++){
                                num[9] = o[e];
                                for(int f=0 ; f<3 ; f++){
                                    num[11] = o[f];
                                    for(int g=0 ; g<3 ; g++){
                                        num[13] = o[g];
                                        check();
                                    }
                                }
                            }
                        }
                    }
                }
            }			
            break;
        }
        
        case 9:{
            for(int a=0 ; a<3 ; a++){
                num[1] = o[a];
                for(int b=0 ; b<3 ; b++){
                    num[3] = o[b];
                    for(int c=0 ; c<3 ; c++){
                        num[5] = o[c];
                        for(int d=0 ; d<3 ; d++){
                            num[7] = o[d];
                            for(int e=0 ; e<3 ; e++){
                                num[9] = o[e];
                                for(int f=0 ; f<3 ; f++){
                                    num[11] = o[f];
                                    for(int g=0 ; g<3 ; g++){
                                        num[13] = o[g];
                                        for(int h=0 ; h<3 ; h++){
                                            num[15] = o[h];
                                            check();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        
    }
    return 0;
}
```

---

## 作者：cellur925 (赞：2)

一看到这道题我们可以首先想到三进制枚举。因为对于每个数字间的“空隙”都有三种可能：放加号、放减号、不放。

然后由于本菜菜第一次写n进制枚举加上这题十分恶心的字符串处理属性于是在实现上耗费了好久。

题解里好像没有c++三进制枚举qwq。只有p码大神写的。那我就写一发qwq。

### 思路：

首先将当前枚举的三进制数抽离得到我们当前情况的放符号情况。


然后我们处理得到当前情况的字符串seq。

其次，由于字符串之间可能有不放的符号，这对我们检验式子的值非常不利，所以我们再从seq中拣出可以处理的可做串real。

然后我们计算就好了qwq。

### 细节：

每次枚举都要把两个串清空。（想一想，为什么。）

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<cctype>
#include<cstring>
#include<queue>

using namespace std;

int n,sum,pos,ret,res,wei[10000];
char seq[1000],real[1000];
map<int,char>opt;

int ksm(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a;
		b>>=1;
		a=a*a;
	}
	return ans;
}

int stack_calc()
{
	queue<char>q;
	int i=0,ans=0;
	int num[10],coun=0;
	memset(num,0,sizeof(num));
	while(i<=res)
	{
		if(real[i]=='+'||real[i]=='-') q.push(real[i]);
		else 
		{
			int noww=i;
			while(isdigit(real[i])) i++;
			i--;
			int hu=0,step=0;
			for(int j=i;j>=noww;j--)
			{
				hu+=((int)real[j]-'0')*ksm(10,step); 
				step++;
			}
			num[++coun]=hu;
			i++;
			continue;
		}
		i++;
	}
	i=2;ans=num[1];
	while(i<=coun)
	{
		char yu=q.front();q.pop();
		if(yu=='+')
			ans+=num[i];
		if(yu=='-')
			ans-=num[i];
		i++;
	}
	return ans;
}

void work(int x)
{
	memset(wei,0,sizeof(wei));
	int qwq=x;
	while(qwq)
	{
		wei[++pos]=qwq%3;
		qwq/=3;
	}
} 

int main()
{
	scanf("%d",&n);
	opt[0]=' ';opt[1]='+';opt[2]='-';
	int fAKe=ksm(3,n-1)-1;
	n--;
	for(int i=1;i<=fAKe;i++)
	{
		pos=0;
		work(i);
		memset(seq,0,sizeof(seq));
		memset(real,0,sizeof(real));
		ret=-1,res=-1;seq[++ret]='1';
		for(int j=n;j>=1;j--)
			seq[++ret]=opt[wei[j]],seq[++ret]=n-j+2+'0';
		int j=0;
		for(int g=0;g<=ret;g++)
		{
			if(seq[j]!=' ') real[++res]=seq[j];
			j++;
		}
		if(stack_calc()==0) printf("%s\n",seq);	
	}
	return 0;
}
```

---

## 作者：卢卢2004 (赞：1)

看PASCAL的选手被C++的选手虐，我来发一个简洁的题解，原代码如下：

```cpp
var
  n:longint;
  a:array[1..9] of char;
procedure dfs(cs,s,t,l:longint);//深搜
var
  i:longint;
begin
  if cs>n then
  begin
    if s+t*l=0 then
    begin
      for i:=1 to n-1 do write(i,a[i+1]);
      writeln(n);
    end;
    exit;
  end;
  a[cs]:=' '; dfs(cs+1,s,t*10+cs,l);//符号
  a[cs]:='+'; dfs(cs+1,s+t*l,cs,1);
  a[cs]:='-'; dfs(cs+1,s+t*l,cs,-1);
end;
begin
  readln(n);
  dfs(2,0,1,1);// 层数，总和，当前，符号
end.
```

---

## 作者：「QQ红包」 (赞：1)

啊，这么小的范围？暴搜！


当然这道题也可以打表。

这题主要是空格的情况不好处理，如果无空格情况的话就可以在标记符号的同时把下一位加上，

这个的话必须找到下一个符号，再将上一个数加上或减去。

比如：

1+2 3 搜到+的时候，把1加上去，搜到空的时候继续往下搜，结尾的时候再把23给加上


```cpp
#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include<time.h>
#include<vector>
#include<bitset>
#include<memory>
#include<utility>
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#define LL unsigned long long
using namespace std;
int n,sum;
char a[9];//存8个间隔的符号，‘+’‘-’‘ ’
void dfs(int t,int x,int he)
//t存深度，x存本个数字的长度（没有计算）,he存上一位符号1为+,2为- 
{
    if (t==n)//搜到了 
    {
        int s=sum;
        if (he==1) s+=x; else s-=x;//最后一个数字得算进去 
        if (s==0)//和为0
        {
            for (int ii=1;ii<n;ii++)//输出数字和符号 
            {
                printf("%d%c",ii,a[ii]);
            }
            printf("%d\n",n);//最后一个数单独输出
        }
        return;
    }
```
/**************空号这种情况**************/
```cpp
    a[t]=' ';//标记 
    if  (he==1)//如果前面那个符号是加号 
        dfs(t+1,x*10+t+1,1);
    else dfs(t+1,x*10+t+1,2);
```
/**************+号这种情况**************/
```cpp
    a[t]='+';//标记
    if (he==1)//如果前面那个符号是加号 
    {
        sum+=x;
        dfs(t+1,t+1,1);
        sum-=x;
    }
    else
    {
        sum-=x;
        dfs(t+1,t+1,1);
        sum+=x;
    }
```
/**************-号这种情况**************/
```cpp
    a[t]='-';
    if (he==1)
    {
        sum+=x;
        dfs(t+1,t+1,2);
        sum-=x;
    }
    else
    {
        sum-=x;
        dfs(t+1,t+1,2);
        sum+=x;
    }
    return;
}
int main()
{
    freopen("zerosum.in","r",stdin);
    freopen("zerosum.out","w",stdout);
    scanf("%d",&n);
    dfs(1,1,1);//暴搜 
    return 0;
}
```

---

## 作者：lightmain (赞：1)

看到这里的题解，好像没有非常简洁、可读性很强的代码。实际上，这个题不需要什么if语句，不需要什么循环，就靠两个函数，可以很简单地解决问题。

下文的代码，是一定需要伪代码和纸上计算才能保证没有需要你疯改1小时的bug的。

```cpp
/*
ID: the_psk1
PROB: zerosum
LANG:C++
*/
#include <cstdio>
using namespace std;
const int N = 15;
int n;
char st[N];//用来存符号的栈 
void output() {
	char s[N*2];
	for(int i = 1; i <= n; ++i) {
		//2  * i - 2是用f(1) = 0, f(2) = 2求出来的初中一次函数，下文同理 
		s[2 * i - 2] = i + '0';
	}
	for(int i = 1; i < n; ++i) {
		s[2 * i - 1] = st[i];
	}
	s[2 * n - 1] = '\0';
	printf("%s\n", s);
}

//每一次函数运行，自己规定好处理level数字的后面那个符号 
void f(int level, int pnum, int sign, int sum) {
	//printf("%d, %d, %d, %d\n", level, pnum, sign, sum);
	if(level == n) {
		if( pnum * sign + sum == 0)
			output();
		return ;
	}
	st[level] = ' ';
	f(level + 1, pnum * 10 + level + 1, sign, sum              );
	st[level] = '+';
	f(level + 1, level + 1            , 1   , sum + sign * pnum);
	st[level] = '-';
	f(level + 1, level + 1            , -1  , sum + sign * pnum);
}

int main(){
//    freopen("zerosum.in", "r", stdin);
//    freopen("zerosum.out", "w", stdout);
    scanf("%d", &n);
    f(1, 1, 1, 0);
    return 0;
}
/*

*/
```
代码风格也很重要。我认为，最好的方式是，不要有太多换行，但是变量名、运算符、表达式之间的空格一定要打足，这样会使得代码更胖一些，更适合普遍的屏幕的尺寸。

---

## 作者：rainygame (赞：0)

本题我用了一种新的枚举方法，这种方法是我解这道题时**独立发现**的。（我用了 $2$ 个小时写出来了）

**本题解最早的[提交记录](https://www.luogu.com.cn/record/94335448)在 C++14 (GCC 9) 的最优解中稳排倒数第一，用时约是倒数第二的 $2$ 倍，因此请小心使用此方法！**

当我们看到这个题的时候，就可以想到暴力枚举了。

然鹅普通的二进制枚举值只适用于类似 01 背包这种只有 $2$ 个状态的枚举，但是我们现在有 $3$ 个状态，怎么办呢？

此时，我们突然想到了一个注意：可以扩充 $1$ 个二进制位呀！

普通的二进制枚举用 $1$ 个二进制位表示 $1$ 个状态，但是我们的二进制枚举使用 $2$ 个二进制位表示 $1$ 个状态，这样就可以达到~~计算量翻倍~~表示复杂状态的目的了！

因为我们需要枚举 $n-1$ 个符号的状态，每个符号又需要 $2$ 个二进制位来表示其状态，所以一共需要 $2(n-1)$ 个二进制位。

那我们怎么分解这个二进制呢？

我们可以参考普通的二进制枚举时什么样的：

```cpp
for (int i=0; i<(1<<n); i++){
    base = 0;
    for (int j=1; j<=n; j++){
        a[i] = (i >> base & 1);  // 举个例子
        base++;
    }
}
```

我们看一下哪里要改一下：

1. 第一个枚举的终点应该改成 `(1 << ((n-1)<<1))`。（具体看上面的解释）

2. `base` 不能只增加 $1$，因为我们每个状态有 $2$ 个符号位，所以应该要增加 $2$。

3. 因为我们实际上有 $3$ 个状态，所以我们需要改成 `(i << base & 3)`（可能有人会问为什么是 $3$，因为 $3 = (11)_2$，任何一个数都会只保留最低的两个二进制位，相当于对 $4$ 取余）。

大家都会改了吧，那么核心代码就只有那么几行：

```cpp
for (int i=1; i<(1 << ((n-1)<<1)); i++){  // 二进制枚举 
	str = "1";  // 初始化，至少有一个1 
	base = 0;
	for (int j=2; j<=n; j++){  // 枚举2~n的数 
		str += symbol[i >> base & 3];
		str += j + '0';
		base += 2;
	}
		
	if (judge()) vis.insert(str);  // 计算是否合法 
}
```


其中 `symbol = {' ', ' ', '+', '-'}`；`judge()` 为计算函数，用于计算表达式的值是否为 $0$。

因为 `judge()` 函数不是这篇题解的重点，所以不展开讲，只给注释代码。完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const char symbol[] = {' ', ' ', '+', '-'};  // 符号 

int n, base, now, ex, oth;
stack<int> st;  // 用于计算，数值和符号用一个栈 
bool flag;

set<string> vis;  // 集合储存，因为是4进制，不仅要排序，而且还要去重 
string str;  // 获得的算式 

void count(){
	ex = st.top();  // 符号 
	st.pop();
	oth = st.top();  // 数值 
	st.pop();
	if (ex) now += oth;  // 判断符号并计算 
	else now = oth - now;
}

bool judge(){  // 判断是否为0 
	if (!st.empty()) st.pop();  // 注意要清空栈 
	
	now = 0;  // 当前数值 
	for (int i=0; i<str.size(); i++){
		if (str[i] >= '0' && str[i] <= '9'){  // 如果是数字 
			now = now*10 + (str[i]-'0');  // 计数器加上之前的 
			if (i == str.size()-1){  // 已经是最后一个了 
				if (st.empty()) return false;  // 全部空格的肯定不行 
				count();
				st.push(now);  // 把数值推进去 
			}
		}else if (str[i] == '-' || str[i] == '+'){  // 如果是符号 
			if (!st.empty()) count();  // 栈非空，表示里面有数 
			st.push(now);  // 把数加进去 
			st.push(str[i] == '+');  // 把符号加进去 
			now = 0;  // 清空计数器 
		}  // 空格不用管 
	}
	
	return st.top() == 0;  // 判断是否等于0 
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	
	for (int i=1; i<(1 << ((n-1)<<1)); i++){  // 二进制枚举 
		str = "1";  // 初始化，至少有一个1 
		base = 0;
		for (int j=2; j<=n; j++){  // 枚举2~n的数 
			str += symbol[i >> base & 3];
			str += j + '0';
			base += 2;
		}
		
		if (judge()) vis.insert(str);  // 计算是否合法 
	}
	
	for (auto i: vis) cout << i << '\n';  // 输出，set是自动排序的 

	return 0;
}

```

时间复杂度为 $O(2^n) \times O(n) = O(2^nn)$，其中 $O(2^n)$ 是枚举，$O(n)$ 是判断。空间复杂度为 $O(2^n)$，因为要储存合法的情况。

这里有几个小技巧：

1. 我们枚举的时候还是需要枚举空格的，但是计算的时候我们可以直接忽略掉，什么也不判断。

2. 因为这个二进制生成的字符串可能会重复，需要去重，而且后面是要升序排序的，所以我使用 `set`，一举两得。

3. 可以把一次计算单独写成一个 `count()` 函数，这样可以节省代码量。

虽然你可能觉得它很没用，但是在某次选拔赛中，我把深搜写挂了，心急如焚的时候突然想到二进制枚举，然后只用了 $20$ 分钟通过了那道题（ACM 赛制），这让我在毒瘤的 $14$ 题中通过了 $5$ 题（第一名 $7$ 题），也让我在计算总成绩时排名 $16$（共 $120$ 人）。这说明，二进制枚举确实有点用。

---

## 作者：Hzq11_ (赞：0)

# stringstream大法好!!!
这是一道dfs的模板题,这么小的数据($n$≤$9$),暴搜是过的了的。  
可是,由于时间原因(我太蒻了),不想(会)手写判断,所以,本蒟蒻动用了<sstream>库里的$stringstream…$  
虽然它很慢,但这么小的数据绝对过得了...
### 先说说判断怎么写
```cpp
inline bool check(const string &Str_1){
    int n=1;
    const int Len=Str_1.size();
    for (int i=0;i<Len;i++)               //数出有几个数
        if (Str_1[i]=='+'||Str_1[i]=='-')
            n++;
    stringstream Sin;                     //定义stringstream流
    for (int i=0;i<Len;i++)
    	if (Str_1[i]!=' ')
    		Sin<<Str_1[i];
    int Ans=0;
    for (int i=0,Temp;i<n;i++)            //加在一起
    	Sin>>Temp,Ans+=Temp;
    Sin.flush();                          //别忘了清空
    return Ans==0;
}
```
是不是没有半点技术含量?  
判断写完了,就好写了
### 完整代码双手奉上
```cpp
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
int Tm_N;
string Str;
inline bool check(const string &Str_1){
    int n=1;
    const int Len=Str_1.size();
    for (register int i=0;i<Len;i++)
        if (Str_1[i]=='+'||Str_1[i]=='-')
            n++;
    stringstream Sin;
    for (register int i=0;i<Len;i++)
    	if (Str_1[i]!=' ')
    		Sin<<Str_1[i];
    int Ans=0;
    for (int i=0,Temp;i<n;i++)
    	Sin>>Temp,Ans+=Temp;
    Sin.flush();
    return Ans==0;
}
void dfs(int N){
    Str+=char (N+48);
    const int Len=Str.size();
    if (N==Tm_N){
        if (check (Str))
            cout<<Str<<endl;
        Str.erase (Len-1,1);
        return;
    }
    Str+=" ";
    dfs (N+1);
    Str.replace (Len,1,"+");
    dfs (N+1);
    Str.replace (Len,1,"-");
    dfs (N+1);
    Str.erase (Len-1,2);
}
int main(){
    ios::sync_with_stdio (false);
    cin>>Tm_N;
    dfs (1);
    return 0;
}
```
~~蒟蒻的代码,Dalao勿喷~~

---

## 作者：tcswuzb (赞：0)

### 本蒟蒻今天独立做出来的第一道题

感谢 [olinr](https://www.luogu.org/space/show?uid=88460)大佬 以及 [c。](https://www.luogu.org/space/show?uid=98516)
dalao

拿到本题第一眼 

### 无他 唯暴搜尔

c。dalao 告诉我符号以及字符分开处理

olinr dalao 帮助我debug了许多 还告诉我许多好法子

本题暴搜的好处 ： 1.边界明确 2.数据范围良心

首先 vector 存当前状态

达到执行边界之后 检测

然后

本蒟蒻先把数值整理出 存入栈

注:栈是先进后出 为了维持运算顺序 所以再读入另一个栈

扫描vector 存在运算符号则计算

### 注:由于答案要求字典序 所以先空格后加号再减号

感谢 olinr dalao的提醒

详细见代码

# CODE：

```cpp
#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<stack>
#include<list>
#include<set>
#include<deque>
#include<vector>
#include<ctime>
#define ll long long
#define inf 0x7fffffff
#define N 500008
#define IL inline
#define M 1008611
#define D double
#define ull unsigned long long
#define R register
using namespace std;
template<typename T>void read(T &a)
{
    T x=0,f=1;char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')f=0;ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+ch-'0';ch=getchar();
    }
    a=f?x:-x;
}
/*-------------OI使我快乐-------------*/
vector<char> A;
int n;
char key[51]={' ','+','-'};
char TA[15]={'0','1','2','3','4','5','6','7','8','9'};
IL void dfs(int now,int tp)
//now表示当前搜索到第几个数字或符号 
//tp表示是数字还是符号 
{
	if(now==n && tp==2)//已经搜索到第n个数字 无需再处理第n个符号 结束 
	{
//		printf("youngsc\n");
		int tmp=0;stack<int> B,C;
//		for(R int i=0;i<A.size();++i) printf("%c",A[i]);
//		printf("\n");
		for(R int i=0;i<A.size();++i)
		{
			if(isdigit(A[i])) tmp=tmp*10+A[i]-'0';//是数字则不断读入 
			else if(A[i]==' ') continue;//空格对于数字可以跳过 
			else if(A[i]=='+' || A[i]=='-') B.push(tmp),tmp=0;
			//遇到运算符号 先读入数 再清零 （蒟蒻吃过亏） 
		}
		B.push(tmp);tmp=0;
		int now1,now2;
		while(B.size()) C.push(B.top()),B.pop();//维持运算顺序 再反向存栈 
//		printf("\n");
		for(R int i=0;i<A.size();++i)
		{
			if(A[i]=='+')//运算 
			{
				now1=C.top();C.pop();now2=C.top();C.pop();
				C.push(now1+now2);
			}
			else if(A[i]=='-')
			{
				now1=C.top();C.pop();now2=C.top();C.pop();
				C.push(now1-now2);
			}
		}
		if(C.top()==0)
		 {//最终结果是零 yes  不是零 no 
		 	for(R int i=0;i<A.size();++i) printf("%c",A[i]);
		 	printf("\n"); 
		 } 
//		printf("\nMlovTry\n\n\n");
		return;
	}
	if(tp==1)
	{
		A.push_back(TA[now]);
		dfs(now,2);
		A.pop_back();
        //一开始以为数字不用回溯
        //可是后来发现不回溯不行
	}
	if(tp==2)
	{
		for(R int i=0;i<3;++i)
		{
			A.push_back(key[i]);
			dfs(now+1,1);
			A.pop_back();
            //枚举三种符号 回溯
		}
	}
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    read(n);
    dfs(1,1);//开始暴搜 
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

```

---

## 作者：lx233 (赞：0)

因为n很小，直接暴力dfs就可以找到，或者全排列，但是讲道理，以练个dfs为初衷怎么变成了开始练大模拟。。。

反正我是错了很多次。。。 zj一直在安慰我这个很难的！很容易写错的！  我才不信。。。
dfs就是把所有可能都枚举一下，前几天刚刚看了书，不算麻烦
【dfs里面（其实也就是回溯法吧。。）】
【需要注意最后判断相等的时候 】
if (x == n+1)		x--;
因为假设n有8 ，那么1-7安排好了走到8的时候才会判断相等，所以这里是n+1，同时后面cal和输出的时候最好x--

对于cal..  就是算是否等于0,感觉还是反面算好算
如果是正的其实只要最后加一个结束符号判断就好了，否则不能处理5+67
同理，倒着的时候【也应该注意1开头的那些】
1 2 3 4 5 6 7的值怎么计算。。
最开始还想着直接sum+1  实际上这个1并不是可忽略之意  而是其前面必须是正的所以固定为'+'

其他需要注意的
1.我经常犯的错误: 
	（1）i--会忘掉
	（2）cc和c如果数组名字一样可能会混
    （3）flag这种用过之后【每个地方都要置空】
    （4）如果两个相等的地方改了，都要改，不然不统一又错（此题是+- 其他情况copy过去的代码经常只是改了一边，没改另一边）  
2.char数组赋值（全赋值。。 直接写一串儿那样）似乎只能在定义的时候直接初始化掉（反正不能初始化两次）
3.也可以直接char c[6] = "  +-" ;会更快
4.别忽视三位数的情况，我把bool flag直接变成了int flag
倒着加就会出现4 5 加成54的情况
同志仍需努力啊-。-
说出来你可能不信，现在是晚上九点半，我从四点半就开始写这个题了，是不是一点都不像有c++和数据结构基础之后又已经搞了半年的人

```cpp
//不用全都写出来..  大概 然后重要的还要手打的 
//dfs for numbers
#include<iostream>
#include<vector>
using namespace std;
int n;
int num[10] = { 0,1,2,3,4,5,6,7,8,9 };
 char cc[10] = { ' ','+'};
 //初始化只能在定义 的时候
//char cc[10];
char c[6] = "  +-" ;
int cal(int x) {
	int sum = 0;
	int flag = 0;
	int tmp = 0;
	for (int i = x; i >= 1; i--) {
		if (cc[i] == ' ') {
			if (flag != 0) {
				flag++;
			}
			else {
				flag = 1; 
			}
			
		}
		else if (cc[i] == '+') {
			if (flag != 0) {
				tmp = num[i]; int k = i + 1;
				while (flag != 0) {
					tmp = tmp * 10 + num[k];
					flag--; k++;
				}
				//tmp = tmp + num[i] * 10;
			}
			else tmp = num[i];
			sum = sum + tmp;
			tmp = 0;
			flag = 0;
		}
		else if (cc[i] == '-') {
			if (flag != 0) {
				tmp = num[i]; int k = i+1;
				while (flag!=0) {
					tmp = tmp * 10 + num[k];
					flag--; k++;
				}
				//tmp = tmp + num[i] * 10;
			}
			else tmp = num[i];
			sum = sum - tmp;
			tmp = 0;
			flag = 0;
		}
	}
	//忽然觉得...  这是不定长度的东西  
	//还是先思考一下  然后稍微写一下因为...  因为直接实现后面似乎不好写
	//可以先用vector处理一下 之后再..
	//关键是处理空格所以 先把数字提取出来吧.... 

	//然后忽然想到上课讲的运算符加减法... 既然问题出在最后一位不知道上面..  我们不如倒着算 反正只有加减
	//运算律结合律...   倒着处理一下如果有' ',就多点tmp*10  否则直接加到最后答案上去
	//有的时候乱起来debug.. 真的不如直接推翻了重写啊
	return sum;

	/*
	//x位的运算
	int sum = 1;
	x--;
	int f = 0; int tmp=0;
	for (int i = 2; i <= x; i++) {
		if (cc[i] == '+')  f = 1; 
		else if (cc[i] == '-')f = 2;
		else if (cc[i] == ' ')f = 3;
		if (f == 1  ) {
			if (i == x || cc[i + 1] != ' ')
			sum = num[i] + tmp+sum; tmp = 0;
		}
		else if ( f == 2) {
			if (cc[i + 1] != ' ') {
				sum = sum - (num[i] + tmp); tmp = 0;
			}
		}
		else if (f == 3) {
			tmp = num[i] * 10 + tmp;
		}
		//else tmp = num[i] * 10;
	}return sum;*/
}

void  dfs(int x) {
	//break条件
	if (x == n+1) {//n+1是基于前面的都安排好了
		x--;
		if (cal(x) == 0){
			cout << num[1];
			for (int i = 2; i <= x; i++) 
			cout  << cc[i]<<num[i];
			cout << endl;
		}
	}
	else  if (x == 1) dfs(x + 1);
	else{//就是不等于1的时候, 同志还需努力
		//先放运算符,再连接数字
		for (int i = 1; i <= 3; i++) {
			cc[x] = c[i];
			dfs(x + 1);
		}
	}
}
int main() {
	//cout << cal(5);
	cin >> n;
	dfs(1);
	return 0;
}
```





连续不过了好几篇题解了-。-   
反正也是自己写了提醒自己-。-。-。-。-

---

## 作者：WAMonster (赞：0)

## ~~观摩了一下楼上好像没有人用枚举全排列，那我就发一下吧~~
首先数据范围极小（$3<=n<=9$），而枚举次数$3^9$也不过一万多

如果再算上$O(n)$的时间计算每个算式，总时间复杂度也只有$O(3^n×n)$，可以放心0ms过

而最主要的问题还是计算。加减都容易实现，对于空格，我的方法是用一个变量last储存该空格之前的那个数，比如枚举到：
```
/*
1 2 3
   ^
 当前空格  
*/
```
那么last的值就是23。我们可以把遇到这个空格之前加的（或减的）数（即last）减去（或加上），再加上（或减去）空格前面（即last）与后面一位拼接形成的新数，如此做一直到遇到运算符为止。当做完整个序列后，判断一次答案是否是0即可。

### PS：整齐但巨丑的代码，~~没有任何剪枝~~

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define fp(i,a,b) for(register int i=a;i<=b;++i)
#define f3(i) for(register int i=1;i<=3;++i)
int n,ss;
char base[4]={0,' ','+','-'};
char ans[10];

int cpt(int bb){//参数是方便测试用的
	int res=1,last=1,sym=1;
	fp(i,1,n-1){
		if(ans[i]=='+'){
			sym=1;
			last=i+1;
			res+=last;
		}
		else if(ans[i]=='-'){
			sym=-1;
			last=i+1;
			res-=last;
		}
		else if(ans[i]==' '){
			int now=last*10+i+1;
			res+=sym*(now-last);
			last=now;
		}
		if(bb)printf("%d:%d ",res,last);
	}
	if(bb)printf("\n");
	return res;
}
void print(){
	fp(i,1,n-1)printf("%d%c",i,ans[i]);
	printf("%d\n",n);
}
int main()
{
	scanf("%d",&n);
    //考验耐力的时候到了
	f3(a){
		ans[1]=base[a];
		f3(b){
			ans[2]=base[b];
			if(n>3)f3(c){
				ans[3]=base[c];
				if(n>4)f3(d){
					ans[4]=base[d];
					if(n>5)f3(e){
						ans[5]=base[e];
						if(n>6)f3(f){
							ans[6]=base[f];
							if(n>7)f3(g){
								ans[7]=base[g];
								if(n>8)f3(h){
									ans[8]=base[h];
									if(!cpt(0))
									print();
								}
								else if(!cpt(0))
								print(),cpt(0);								 
							}
							else if(!cpt(0))
							print();
						}
						else if(!cpt(0))
						print();					
					}
					else if(!cpt(0))
					print();
				}
				else if(!cpt(0))
				print();			
			}
			else if(!cpt(0))
			print();
		}
	}
	return 0;
}

```

---

## 作者：ww3113306 (赞：0)

虽然数据很小，，但是我第一反应是用dfs，，下面代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct abc
{
    int x;
    char before;
};
abc s[10];int n;char a[3]={' ','+','-'};
void print()
{
    int i;
    printf("%d",s[1].x);
    for(i=2;i<=n;i++)
        printf("%c%d",s[i].before,s[i].x);//由于要打出‘  ’，所以打印s数组而不是ans数组
    printf("\n");    
}
bool may()//判断和是否为0的函数
{
    int i,t=1;abc ans[15];int kk=0;bool zz=false;//这个bool必须加，因为要判断是不是有符号
    for(i=0;i<=n;i++)//手动初始化
    {
        ans[i].x=0;
        ans[i].before=' ';
    }
    ans[t].x=1;//手动给ans[1].x赋值
    for(i=2;i<=n;i++)//从2开始处理，因为要排除1前面默认的‘  ’
        if(s[i].before==' ') //如果第i个数前面的符号是‘  ’，那就将这个数与之前已经读入的ans[t].x合并。（注意t不能由i代替，因为合并操作，t不一定等于i，t代表的是ans数组里面存的数的个数）
            ans[t].x=ans[t].x*10+s[i].x;
        else//如果是‘+’or‘-’。将这个数存入ans（不合并）
        {
            t++;
            ans[t].x=s[i].x;
            ans[t].before=s[i].before;
        }    
    for(i=1;i<=t;i++)
    {
        if(i==1)//ans的第一个由于没有符号，所以要特判一下
        {
            kk+=ans[i].x;
            continue;//因为是第一个数，跳过下面的操作
        }
        if(ans[i].before=='+') kk+=ans[i].x,zz=true;//如果是+，kk就+=
        else if(ans[i].before=='-') kk-=ans[i].x,zz=true;//同上
    }
    if(kk==0&&zz==true) return true;//如果kk（总和）==0，并且有符号，返回true
    else return false;//否则返回false
}
void dfs(int now/*现在轮到的数字*/)
{
    int i;bool z=false;
    if(now==n)//如果已经搜到了第n个数
    {
        z=may();//判断总和是否为0
        if(z==true)    print();//如果和为0，输出    
    }
    for(i=0;i<=2;i++)
        if(now+1<=n)//因为第一个数字前面不能加符号，所以从第2个数开始处理，如果没有越界就继续搜
        {
            s[now+1].before=a[i];//这一因为会被后面的符号覆盖，所以不必初始化和回溯
            dfs(now+1);
        }
}
int main()//美好的主函数
{
    int i;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        s[i].x=i;
    dfs(1);//从1开始搜索
    return 0;
}
```

---

## 作者：chauchat (赞：0)

来一份简洁无比的代码

整个思路很简单，就是无脑枚举三个符号。字符串处理是比较麻烦的

怎么处理开心就好。。。

我这里直接模拟两个栈实现加减法 简直不能再优美，应该容易懂的







```cpp
#include<iostream>
using namespace std;
#include<cstring>
#include<ctype.h>
//" " < "+" < "-"
int n;
char now[15];
bool check(){
    char stack1[10];
    int stack2[10],temp = 1,p1 = 0,p2 = 0;
    //处理符号栈和数字栈，再一一取出计算
    for(int i = 2;i < 2 * n;i += 2){
        if(now[i] == ' ') temp = 10 * temp + (now[i+1] - '0');
        else{
            stack1[++p1] = now[i];
            stack2[++p2] = temp; temp = now[i+1] - '0';
        }
    }
    stack2[++p2] = temp;
    int a = stack2[1],b = stack2[2],ptr = 2;
    for(int i = 1;i <= p1;i++){
        if(stack1[i] == '+'){
            a += b; b = stack2[++ptr];
        }else{
            a -= b; b = stack2[++ptr];
        }
    }
    if(!a) return true;
    return false;
}
void dfs(int step){
    if(step == n){
        if(check()){
            for(int i = 1;i < 2 * n;i++) cout<<now[i];
            cout<<endl;
        }
        return;
    }
    now[2 * step] = ' ';
    now[2 * step + 1] = step + 1 + '0';
    dfs(step + 1);
    now[2 * step] = '+';
    now[2 * step + 1] = step + 1 + '0';
    dfs(step + 1);
    now[2 * step] = '-';
    now[2 * step + 1] = step + 1 + '0';
    dfs(step + 1);
}
int main(){
    cin>>n;
    now[1] = '1';
    dfs(1);
    return 0;
}
```

---

## 作者：汇文客 (赞：0)

这道题可采用三进制穷举‘+’、‘-’、‘ ’，考察的主要是字符串处理。

```delphi

//uses math;呜呜！洛谷不给用数学库……
const f:array[0..2]of string=(' ','+','-');
var b:array[1..8]of longint;
    st,s:string;
    n,i,j,l,num,ans,max:longint;
begin
  readln(n);
  max:=1;
  for i:=1 to n-1 do max:=max*3;//这么小的数据就不用快速幂了。
  for i:=0 to max-2 do
  begin
    fillchar(b,sizeof(b),0);
    st:='';
    num:=i;l:=0;
    while num>0 do
    begin
      inc(l);
      b[l]:=num mod 3;
      num:=num div 3;
    end;
    st:='1';
    for j:=n-1 downto 1 do
    st:=st+f[b[j]]+chr(n-j+49);
    l:=1;s:=st;
    while(l<=length(st))do
    begin
      inc(l);
      if st[l]=' ' then delete(st,l,1);
    end;l:=1;
    while(l+1<=length(st))and
    (ord(st[l+1])<>43)and(ord(st[l+1])<>45)do inc(l);
    val(copy(st,1,l),ans);
    delete(st,1,l);
    while st<>'' do
    begin
      l:=1;
      case st[l] of
      '+':begin
            while(l+1<=length(st))and
            (ord(st[l+1])<>43)and(ord(st[l+1])<>45)do inc(l);
            val(copy(st,2,l-1),j);
            delete(st,1,l);ans:=ans+j;
          end;
      '-':begin
            while(l+1<=length(st))and
            (ord(st[l+1])<>43)and(ord(st[l+1])<>45)do inc(l);
            val(copy(st,1,l),j);
            delete(st,1,l);ans:=ans+j;
          end;
      end;
    end;
    if ans=0 then writeln(s);
  end;
end.

```

---

## 作者：jijidawang (赞：0)

看到题目，一惊。

看到数据范围，想到了打表。

数字肯定不能手算，开个$\texttt{freopen}$，用这个程序：
```cpp
#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<windows.h>
#define sc(x) scanf("%d",&x);
using namespace std;
int n;
int a[100],ch[100],b[100];
char aaa;
bool check()
{
    bool pd=0;
    char c[100];
    int d[100];
    int lenc=0,lend=0;
    memset(d,0,sizeof(d)); 
    for (int i=1;i<=n;i++)
    {
        c[++lenc]=i+48;
        if (i==n)  continue;
        if (ch[i]==1) continue;
        else if (ch[i]==2) c[++lenc]='+';
        else if (ch[i]==3) c[++lenc]='-';
    }
    for (int i=1;i<=lenc;i++)
    {
        if (c[i]>='0'&&c[i]<='9')
        {
            int num=0;
            while (c[i]>='0'&&c[i]<='9')
            {
                num=num*10+(c[i]-48);
                i++;
            }
            d[++lend]=num;
        }
        if (pd)
        {
            d[lend]=-d[lend];
            pd=0;
        }
        if (c[i]=='+')  continue;
        if (c[i]=='-')
        {
            pd=1;
            continue;
        }
    } 
    int num=0;
    for (int i=1;i<=lend;i++)
        num+=d[i];
    if (!num) return 1;
    return 0;
}
void dfs(int nowid)
{
    if (nowid==n+1)
    {
        if (check()==1)  
        {
            for (int i=1;i<=n;i++)
            {
                printf("%d",i);
                if (i==n) continue;
                if (ch[i]==1) printf(" ");
                else if(ch[i]==2) printf("+");
                else printf("-");
            }
            printf("\n");
        }
        else cout<<"\n";
        return ;
    }
    if (nowid+1>n)
    {
        ch[nowid]=0;
        dfs(nowid+1);
    }
    else
    {
        ch[nowid]=1;
        dfs(nowid+1);
        ch[nowid]=2;
        dfs(nowid+1);
        ch[nowid]=3;
        dfs(nowid+1);
    }
}
int main()
{
    sc(n);
    for(int i=1;i<=n;i++)  a[i]=i;
    dfs(1);
    return 0;
}
```
然后~~徒手~~用程序去掉所有换行。
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	string cc;
    bool flag=false;
    cin>>cc;
    int len=cc.length();
    for (int i=0;i<len;i++)
    {
		if (cc[i]=='\n')
        {
        	if (flag) cc.erase(i,1);
        	else flag=true;          //留一个'\n'。
        }
        else flag=false;             //回false。
     }
     return 0;                       //emm
}
```
于是就得到了~~优美的~~打表代码：
```
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	switch(n)
	{
		case 3:cout<<"1+2-3";break;
		case 4:cout<<"1-2-3+4";break;
		case 5:cout<<"1 2-3-4-5";break;
		case 6:cout<<"1 2+3-4-5-6";break;
		case 7:cout<<"1+2-3+4-5-6+7\n1+2-3-4+5+6-7\n1-2 3+4+5+6+7\n1-2 3-4 5+6 7\n1-2+3+4-5+6-7\n1-2-3-4-5+6+7";break;
		case 8:cout<<"1 2-3 4-5 6+7 8\n1+2 3-4 5+6+7+8\n1+2+3+4-5-6-7+8\n1+2+3-4+5-6+7-8\n1+2-3+4+5+6-7-8\n1+2-3-4-5-6+7+8\n1-2 3-4+5+6+7+8\n1-2+3-4-5+6-7+8\n1-2-3+4+5-6-7+8\n1-2-3+4-5+6+7-8";break;
		case 9:cout<<"1 2+3 4-5 6-7+8+9\n1 2+3+4-5-6-7+8-9\n1 2+3-4 5+6+7+8+9\n1 2+3-4+5-6+7-8-9\n1 2-3+4+5 6-7 8+9\n1 2-3+4+5+6-7-8-9\n1 2-3-4-5+6-7-8+9\n1 2-3-4-5-6+7+8-9\n1+2-3 4-5 6+7 8+9\n1-2 3-4-5 6-7+8 9\n1-2-3 4+5+6+7+8+9";break;
	}       
	return 0;
}
```

---

## 作者：yz0414 (赞：0)

这题数据小，可以直接暴搜。

从第二个开始搜起，字符串先为'1'，如果t=n+1就说明做完了，如果成立sum就加一，最后输出sum。

判断:

做一遍最长不降子序列，把和求出来，如果是0就返回true，否则返回false.

注意：按照字典序，' ' < '+' < '-'

代码：
```pascal
var n:longint;
function pd(s:string):boolean;
var i,x,sum:longint; ch:char;
begin
   while pos(' ',s)<>0 do delete(s,pos(' ',s),1);
   x:=0; s:=s+'+'; ch:='+'; sum:=0;
   for i:=1 to length(s) do
     if s[i]in['0'..'9'] then
      x:=x*10+ord(s[i])-48 else
      begin
         if ch='+' then sum:=sum+x;
         if ch='-' then sum:=sum-x;
         x:=0; ch:=s[i];
      end;
   exit(sum=0);
end;
procedure sc(t:longint;s:string);
begin
   if t=n+1 then
    begin
       if pd(s) then writeln(s);
       exit;
    end;
   sc(t+1,s+' '+chr(t+48));
   sc(t+1,s+'+'+chr(t+48));
   sc(t+1,s+'-'+chr(t+48));
end;
begin
   readln(n);
   sc(2,'1');
end.
```


---

