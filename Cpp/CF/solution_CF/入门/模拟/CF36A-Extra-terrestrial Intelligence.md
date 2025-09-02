# Extra-terrestrial Intelligence

## 题目背景

注意这题要加上这个：

```
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 题目描述

Recently Vasya got interested in finding extra-terrestrial intelligence. He made a simple extra-terrestrial signals’ receiver and was keeping a record of the signals for $ n $ days in a row. Each of those $ n $ days Vasya wrote a 1 in his notebook if he had received a signal that day and a 0 if he hadn’t. Vasya thinks that he has found extra-terrestrial intelligence if there is a system in the way the signals has been received, i.e. if all the intervals between successive signals are equal. Otherwise, Vasya thinks that the signals were sent by some stupid aliens no one cares about. Help Vasya to deduce from the information given by the receiver if he has found extra-terrestrial intelligence or not.

## 样例 #1

### 输入

```
8
00111000
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
7
1001011
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
7
1010100
```

### 输出

```
YES
```

# 题解

## 作者：引领天下 (赞：7)

这题好坑啊……

其实模拟并不难，但是输入和输出有坑：

# 输入要加freopen("input.txt","r",stdin) 输出要加freopen("output.txt","w",stdout)

# 输入要加freopen("input.txt","r",stdin) 输出要加freopen("output.txt","w",stdout)

# 输入要加freopen("input.txt","r",stdin) 输出要加freopen("output.txt","w",stdout)

重要的事情说三遍

代码：

```cpp
#include<cstdio>
int n,a[105],l1,l2;
int main(void){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf ("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%1d",&a[i]);
        if(a[i]&&!l1)l1=i;//记录第一个1
        else if (a[i]&&!l2)l2=i;//记录第2个1
    }
    for (int i=l2+1;i<=n;i++)if (a[i]&&i-l2==l2-l1)l1=l2,l2=i;//间隔相同，更新
    else if(a[i])return !printf ("NO");//不相同直接退出
    printf ("YES");
}
```

---

## 作者：林家三少 (赞：2)

一道 

$$\colorbox{red}{\color{white}字符串}$$ 

所以用模拟就OK啦

我一开始是这样判断的：

```cpp
if(st[i]=='1'&&ks==0)  //如果它是第一个'1'
{
	ks=1;  //这个是用来标记第一个'1'是否出现
	ans=0;  //间距重新标记为0
}
```
这是第一个'1'
```cpp
if(st[i]=='1'&&ks==1&&ks2==0)  //如果它是第二个'1'
{
	ks2=1;  //标记第二个'1'出现
	ks3=ans;  //ks3是表示它们之间应有的间距
	ans=0;  //间距重新标记为0
}
```
这是第二个'1'
```cpp
if(st[i]=='1'&&ks==1&&ks2==1)  //以后的'1'都这样
{
	if(ans!=ks3)  //如果它的间距不是应有的
	{
		cout<<"NO\n";  //输出NO，再换行
		return 0;  //Bye-bye
	}
	ans=0;  //如果不是，那间距就清0
}
```
这是以后的'1'

但是......错了


```cpp
就这个样例：

7
1010100

我输出的是：NO

```
后来我调试了一下，发现顺序搞错了

应该是：

```cpp
1.以后的'1'
2.第二个'1'
3.第一个'1'
这样来判断
```
AC程序：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n,ks,ks2,ks3,ans;  //定好变量
string st;  //字符串
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);  //不知道为什么，这一题需要打文件头
	cin>>n;
	cin>>st;  //输入
	for(int i=0;i<=st.size()-1;i++)  //循环
	{
		if(st[i]=='1'&&ks==1&&ks2==1)  //如上
		{
			if(ans!=ks3)
			{
				cout<<"NO\n";
				return 0;
			}
			ans=0;
		}
		if(st[i]=='1'&&ks==1&&ks2==0)  //如上
		{
			ks2=1;
			ks3=ans;
			ans=0;
		}
		if(st[i]=='1'&&ks==0)  //如上
		{
			ks=1;
			ans=0;
		}
		if(st[i]=='0'&&ks==1)  如果第一个'1'出现了
			ans++;  //间距++
	}
	cout<<"YES\n";  //到最后就输出"YES"
	return 0;  //完美结束
}
```


---

## 作者：花里心爱 (赞：1)

### CF36A 题解
这是一道十分有坑点的题…………

**最大的坑点:这题需要文件输入输出！！！**

	输入文件:input.txt
    输出文件:output.txt

我们可以$O(n)$模拟一遍。

首先，题目保证了

	It’s guaranteed that the given record sequence contains at least three 1s.

也就是序列中至少有3个字符'1'，所以不用考虑序列中'1'构不成等距数列的问题。

~~显然~~，我们~~很容易~~就会想到:前2个'1'决定了等距数列的距离。

那么，我们就可以从$i=0$开始向后扫将前2个'1'的位置下标相减，即
```cpp
dr=pr[2]-pr[1];    //pr记录了'1'位置的下标
```
然后，只需要看后一个'1'与前一个'1'是否等距就可以啦！也就是
```cpp
if(dr!=(pr[i]-pr[i-1])puts("NO");
```
**一个小小的空间优化：**

其实我们不需要把所有的$pr[i]$存起来。

只需要看当前的'1'与前一个'1'的距离就可以啦！

下面是不解释的代码:
```cpp
#include<cstdio>
using namespace std;
int n,pr=-1,dr=-1;     //亲测初始化为0会爆炸(因为数组下标是0开始的)
char s[105];
int main(){
	freopen("input.txt","r",stdin);  //这题需要文件输入输出
	freopen("output.txt","w",stdout);
    scanf("%d%s",&n,s);
    for(int i=0;i<n;++i){
    	if(s[i]=='1'){
    		if(pr==-1)       //存第一个数
    			pr=i;
    		else if(dr==-1)  //存第二个数
    			dr=i-pr;
    		else if(dr!=(i-pr)){  //之后的数不等距，输出NO，退出
    			puts("NO");
    			return 0;
    		}
    		pr=i;
    	}
    }
    puts("YES");             //到这里就说明所有'1'等距啦
    return 0;
}
```

---

## 作者：OdtreePrince (赞：1)

# -字符串-

这道题有的人要提交两遍，比如蒟蒻我。

That's because 很多人不加freopen，such as me！

除了这个，一切就简单了！开头把没用的零删去，紧接着求间距，jj=jian ju->$\color{red}\texttt{间距，不要误解}$!

边判断，边输出并退出。

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string s;
    int i=-1,jj,n,b=1;
    cin>>n>>s;
    while(s[++i]=='0') ;
    for(int j=i+1;j<s.size();j++){
        if(s[j]=='1'&&b){
            b=0;
            jj=j-i;
            i=j;
        }
        else{
            if(s[j]=='1'){
                if((j-i)!=jj){
                    cout<<"NO";
                    return 0;
                }
                else i=j;
            }
        }
    }
    cout<<"YES";
    return 0;
}~~~

---

## 作者：wpj20241021005 (赞：1)

这一道题不是非常的难，看到数据规模，3<=n<=100，脑海中便直接涌现出了一个方法：暴力搜。俗话说暴力出奇迹，但也不能在任何题上都暴力，但这一题暴力是完全没有问题的。

主要思想就是，先找到第一个‘1’，然后向后面搜，找到第二个‘1’，然后记录他们之间的空位关系，再找下一个‘1’，比较两者，如果相同，继续重复上述动作，如果不同，直接跳出循环，“cout<<‘NO’；”（应该是双引号，但由于语文标点问题，所以才用到单引号）。要注意的是，最后一个‘1’之后的‘0’一个都不能算。

还有一点要提醒的，一定不要忘了freopen！！！

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
string a;//万能的STL
bool flag;
int sum1,sum2,n;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>a;//输入，因为有STL，所以输入n只是摆设，以下的n全可换位a.size()-1
	for(int i=0;i<n;i++){//循环
		if(a[i]=='1'){//判断，找‘1’
			sum1=0;
			while(a[++i]!='1'){//向后搜
				if(i==n) break;//打破循环，不然程序会死循环
				sum1++;//计数
			}
			if(sum1!=sum2&&flag==true&&i!=n){//判断是否相等，并特判不是第一个‘1’和最后一个‘1’
				cout<<"NO";
				return 0;//结束
			}
			sum2=sum1;//因为第一次sum2==0，所以这一句还是要的
			flag=true;//flag为真
			i--;//到上一个数
		}
	}
	cout<<"YES";//输出
	fclose(stdin);
	fclose(stdout);//完结撒花
} 
```


---

## 作者：LiveZoom (赞：0)

# 题解 CF36A 【Extra-terrestrial Intelligence】
此题是道数组的运用和字符串（~~但听大佬说不用数组，我还是太菜了~~）
此题输入太鬼畜了：

```cpp
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
```

然后就是用数组存储第$i$个出现的$1$加入数组：

```cpp
	for(int i=0;i<s.size();i++){
		if(s[i]=='1')a[++tot]=i;
	}
```
然后用$d$来表示第$1$个到第$2$个的距离，在遍历$a$数组如果差与$d$不同则停止，结束时输出YES即可：

```cpp
	int d=a[2]-a[1];
	for(int i=3;i<=tot;i++){
		if(a[i]-a[i-1]!=d){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
```

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int a[105],tot;
int main()
{
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='1')a[++tot]=i;
	}
	int d=a[2]-a[1];
	for(int i=3;i<=tot;i++){
		if(a[i]-a[i-1]!=d){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
    return 0;
}

```

于是我们就解决这道鬼畜题了（加了防作弊哦~）

---

## 作者：cq_loves_Capoo (赞：0)

这道题很明显就是等差数列，只不过变成了字符串的形式而已。                                           
先给大家讲下等差数列：        
1 2 3 4 5 6 7 8 9 10            
2-1=3-2=4-3=5-4......         
在这个数列里每个数与前一项的差都相等，这就叫等差数列。        
说到这里，大家应该都清楚这题怎么做了吧。     
AC代码：                     
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cmath>
#include<cstdlib>//头文件
using namespace std;
int n,m,s[111111],ds;//定义变量
string st;//字符串
int main()
{//主程序来了
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
        //不加freopen的话这题就会错
	scanf("%d",&n);
	cin>>st;//输入
	for(int i=0;i<n;i++) if(st[i]=='1') m++,s[m]=i;//记住每个“1”的位置
	ds=s[2]-s[1];//先求出第二项减第一项的差
	for(int i=3;i<=m;i++) 
	{
        	if(s[i]-s[i-1]!=ds) //如果不等于第二项减第一项的值，直接输出“NO”.
        	{
        	    printf("NO");
         	    return 0;//退出程序
       	 	}
	}
	printf("YES");//如果全部符合，输出“YES”。
	return 0;//好习惯
}

```



---

## 作者：hensier (赞：0)

本题中要处理字符串输入的话，有以下三种方法：

【方法$1$：用一个$int$保存（推荐指数：☆☆）】

用一个$int$保存的话，占用空间少，看起来方便，但处理起来较为麻烦。如果要如此的话，还需要再新建一个保存数码为$1$的个数的变量。然后当这个数大于$0$的时候，每一次如果这个数求余$10$为$1$就加$1$，并逐个保存位置。

【方法$2$：用$char*$保存（推荐指数：☆☆☆☆）】

可以直接使用$gets$输入并$[0,|s|)$计算'$1$'的个数（$s$为该字符串，$|s|$为字符串$s$的长度）。但是这样容易出错，因为第一行与第二行之间的换行必须考虑到。

【方法$3$：用$scanf($"$\%1d$"$,a[i]);$的格式输入（推荐指数：☆☆☆☆☆）】

这种方式我们平常使用不多——用这种方法可以有效输入一位数。

当然必须注意文件输入和输出（$CF$的很多题目都有这个规定，而且很多时候不提示——好处就是能模拟考试，但坏处就是在平时容易忽略，无缘无故地$WA$）。

这个解决了，这道题目基本上就解决了。

$AC$代码[（本蒟蒻记录）](https://www.luogu.com.cn/record/31180383)：

```cpp
#include<cstdio>
int n,i,x,y,pos[101],seq[101];//pos保存位置，seq保存数列
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);//这两行不能忘写
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%1d",&seq[i]);//每次输入一位数字
        if(seq[i])pos[++x]=i;//pos数组更新
    }
    y=pos[2]-pos[1];//距离初始化为pos[2]-pos[1]
    for(i=2;i<x;i++)
    {
        if(pos[i+1]-pos[i]-y)
        {
            printf("NO");//只要有一个距离不同就输出NO并结束程序
            return 0;
        }
    }
    printf("YES");
}
```

---

