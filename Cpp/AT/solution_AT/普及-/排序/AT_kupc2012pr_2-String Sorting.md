# String Sorting

## 题目描述

设有 $n$ 个正整数（$n \le 100$）长度为 $m$（$m \le 30$），将它们联接成一排，组成一个最大的多位整数。

# 题解

## 作者：stry (赞：3)

其实这一题考察的就是字符串的排序

可能有很多同学不知道，其实字符串也是可以快排的

大致如下：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
string a[110];
long long n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    }
    sort(a+1,a+1+n);//没想到吧
    for(int i=1;i<=n;i++)
    {
    	cout<<a[i];
    }
    return 0;
}
```
可是这一题需要的是从大到小

于是再这个就行了
```cpp
bool cmp(string a,string b)
{
    return a+b>b+a;
}
```
于是我们得出最后的程序：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
string a[110];
long long n,m;
bool cmp(string a,string b)
{
    return a+b>b+a;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
	{
    	cin>>a[i];
	}
	sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
	{
    	cout<<b[i];
	}
    return 0;
}
```
是不是很~~简单~~

希望此题解能给您带来帮助，千万别Ctrl+C哟！

---

## 作者：勘探员·引魂人 (赞：2)

**前言：如果您采用了此题解，场面那叫一个壮观！**

**思路：枚举i和j，判断a[i]+a[j]是否小于a[j]+a[i]，如果符合，swap(a[i],a[j])，最后把排好序的东西结合成一个数字串并输出**

```
#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>//文件头啊，你怎么这么难啊
using namespace std;
int n;//定义n
string st[25],st1;//定义字符串
int main()
{
  cin>>n;       //输入n
  for(int i=1;i<=n;i++)
  {
	cin>>st[i];  //输入每个字符串
  }	  
  for(int i=1;i<n;i++)
  {
	for(int j=i+1;j<=n;j++)
    {
	  if(st[i]+st[j]<st[j]+st[i])  swap(st[i],st[j]);	//枚举i和j，判断a[i]+a[j]是否小于a[j]+a[i]，如果符合，swap(a[i],a[j])
	}		
  }	  
  for(int i=1;i<=n;i++)
  {
	st1+=st[i];  //把排好序的东西结合成一个数字串
  }	  
  cout<<st1<<endl;//输出（换行）！
    return 0;
}
```


---

## 作者：林家三少 (赞：1)

## 一道简单的排序题

m其实没有什么用，所以就讲讲排序就行了

	4 2
    12 32 21
    
    排序：
    x=12,y=32
    32+12>12+32
    现在：
    32 12 21
    x=12,y=21
    21+12>12+21
    现在：32 21 12
    最后输出：322112
    
代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
string a[105];
int n,m;
//定义
bool cmp(string x,string y){
    return x+y>y+x;
}//进行排序
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    }
    //输出
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
    	cout<<a[i];
        //排序后已是从大到小
        //所以直接输出
    }
    cout<<"\n";
    //最后加一个换行
    return 0;
}

```


---

## 作者：Cambridge (赞：1)


小学生又来发题解了！

这道题其实m是没有什么用的，排一下序再输出即可。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    bool cpp(string x,string y)
    {
        return x+y>y+x;
        /*排序两个数加起来的和
        例如3和4
        排序结果是43>34
        */
    }
    string a[100000];
    long long n,m;//定义变量
    int main()
    {
        cin>>n>>m;//读入n和m
        for(int i=1; i<=n; i++)
        {
            cin>>a[i];//读入数据
        }
        sort(a+1,a+1+n,cpp);//快排一下
        for(int i=1; i<=n; i++)
        {
            cout<<a[i];	
        }
        cout<<endl;
        return 0;
    }
# AT不换行，爆零两行泪
好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：da32s1da (赞：1)

与P1012一模一样

字符串排序即可
```
#include<bits/stdc++.h>
using namespace std;
string s[1000];
int n,m;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i=-~i) cin>>s[i];
    sort(s+1,s+n+1);
    for(int i=n;i>=1;i=~-i)cout<<s[i];
    cout<<endl;
}
```

---

## 作者：C20210404杜铖昊 (赞：1)

这道题方法很简单：

输入不要输入int类型

用string类型输入（用来排序）

要用一个函数来排序：

只要两个字符串a b接起来：

部分code:

```
bool cmp(string a,string b){
    return a+b > b+a;
}
```

写好之后调用就可以了

code:
```
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
string s[105];
int n,m;
bool cmp(string a,string b){
    return a+b > b+a;
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1; i <= n;++i) cin>>s[i];
    sort(s+1,s+1+n,cmp);
    for(int i = 1; i <= n;++i) cout<<s[i];
    cout<<endl;
    return 0;
}
```

注意换行！！！

---

## 作者：C20210404杜铖昊 (赞：0)

这道题方法很简单：

输入不要输入int类型

用string类型输入（~~用来排序~~）

要用一个函数来排序：

只要两个字符串a b接起来：

部分code:
```
bool cmp(string a,string b){
	return a+b > b+a;
}
```
写好之后调用就可以了

code:
```
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
string s[105];
int n,m;
bool cmp(string a,string b){
	return a+b > b+a;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i = 1; i <= n;++i) cin>>s[i];
	sort(s+1,s+1+n,cmp);
	for(int i = 1; i <= n;++i) cout<<s[i];
	cout<<endl;
	return 0;
}
```
注意换行！！！



---

## 作者：_•́へ•́╬_ (赞：0)

**~~@da32s1da 的代码有东西看不懂，我的好些~~**
```cpp
#include<bits/stdc++.h>
using namespace std;
string a[666];int n,m;
bool cmp(string p,string q)
{
    return p+q>q+p;//排序用
}

main()
{
    scanf("%d%d\n",&n,&m);
    for(register int i=0;i<n;i++)cin>>a[i];//输入
    sort(a,a+n,cmp);//排序
    for(register int i=0;i<n;i++)cout<<a[i];//输出
    putchar('\n');//打一个回车
}
```
## 小东西：听说加上$register$运行快一点
## 还有：根本用不到$m$!

---

