# SBANK - Sorting Bank Accounts

## 题目描述

 In one of the internet banks thousands of operations are being performed every day. Since certain customers do business more actively than others, some of the bank accounts occur many times in the list of operations. Your task is to sort the bank account numbers in ascending order. If an account appears twice or more in the list, write the number of repetitions just after the account number. The format of accounts is as follows: **2** control digits, an **8**-digit code of the bank, **16** digits identifying the owner (written in groups of four digits), for example (at the end of each line there is exactly one space):

**30 10103538 2222 1233 6160 0142**  **Banks are real-time institutions and they need FAST solutions. If you feel you can meet the challenge within a very stringent time limit, go ahead!** A well designed sorting algorithm in a fast language is likely to succeed.

## 样例 #1

### 输入

```
2
6
03 10103538 2222 1233 6160 0142 
03 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 

5
30 10103538 2222 1233 6160 0144 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0145 
30 10103538 2222 1233 6160 0146 
30 10103538 2222 1233 6160 0143```

### 输出

```
03 10103538 2222 1233 6160 0141 1
03 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0141 2
30 10103538 2222 1233 6160 0142 2

30 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0143 1
30 10103538 2222 1233 6160 0144 1
30 10103538 2222 1233 6160 0145 1
30 10103538 2222 1233 6160 0146 1```

# 题解

## 作者：_Qer (赞：6)

蒟蒻来一发**map**的题解

创建一个结构体来存每张卡的信息（string的卡号，int的出现次数）

然后创建一个<string, card>的map来记录（顺便去重和排序）

然后遍历这个map来输出

```cpp
#include <bits/stdc++.h>
using namespace std;
struct card{
    string bank;
    //卡号
    int n;
    //次数
};
//存卡信息的结构体
int t, n;
//数据组数和输入的卡数
string s, tmp;
//暂存卡号和输入
int main()
{
    cin >> t;
    while (t--)//t组数据
    {
        map<string, card> _map;//定义一个map，用string来找card
        cin >> n;
        for (int i = 1; i <= n; ++i)//n张卡
        {
            s = "";//初始化
            for (int j = 1; j <= 6; ++j)//一张卡分了6段
            {
                cin >> tmp;
                s += tmp;//string神奇操作，直接接到s的末尾
            }
            ++_map[s].n;//记录出现次数
            _map[s].bank = s;//记录卡号
        }
        for (map<string, card>::iterator i = _map.begin(); i != _map.end(); ++i)
        {//遍历map的操作
            //利用iterator来遍历
            //以下为毒瘤输出，说明直接在这里先说了
            //i->first意为取map的第i个元素的key值
            //用这个来找value然后输出（可怕的格式）
            cout << _map[i->first].bank[0] << _map[i->first].bank[1] << " ";
            for (int j = 0; j < 8; ++j)
            {
                cout << _map[i->first].bank[j + 2];
            }
            cout << " ";
            for (int j = 0; j < 4; ++j)
            {
                cout << _map[i->first].bank[j + 10];
            }
            cout << " ";
            for (int j = 0; j < 4; ++j)
            {
                cout << _map[i->first].bank[j + 14];
            }
            cout << " ";
            for (int j = 0; j < 4; ++j)
            {
                cout << _map[i->first].bank[j + 18];
            }
            cout << " ";
            for (int j = 0; j < 4; ++j)
            {
                cout << _map[i->first].bank[j + 22];
            }
            cout << " ";
            cout << _map[i->first].n << endl;
            //毒瘤输出结束
        }
        cout << endl;
    }
    return 0;
}
```

PS：最后用时约5000ms，题目限制7000ms

---

## 作者：siyue (赞：4)

此题解的用时超过1000ms了，不过题目要求**7000ms**。

算法比较简单，对字符串数组排序，然后依次计算相同元素个数后输出字符串和计数器。

```
#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
string s[100002];
int main()
{

    int i,k,j,t,n;
    cin>>t;
    for(k=1;k<=t;k++)
    {
        cin>>n;
        getline(cin,s[0]);/**< 处理一下回车，s[0]没有什么特殊意义 */
        for(i=1;i<=n;i++)
        {
            getline(cin,s[i]);
        }
        sort(s+1,s+n+1);
        s[n+1]="";/**< 加一个特例，方便后面判断相同元素个数 */
        int c=1;
        for(i=1;i<=n;i++)
        {

            if(s[i+1].compare(s[i])==0)
            {
                c++;
            }
            else
            {
                cout<<s[i]<<' '<<c<<endl;
                c=1;
            }
        }
    }
    return 0;
}

```


---

## 作者：PC_DOS (赞：4)

本题是一道模拟题，我们可以采用将输入的账号视为字符串的方法，将账号存入一个vector(of string)并对其进行快速排序。为了实现查重并保存重复次数，我们可以采用一个从string映射到int的map来保存账号出现的次数。在输入字符串sAccount时，检查map(sAccount)的值，如果为0，则将字符串放入动态数组并将map(sAccount)的值加1，否则，直接map(sAccount)的值加1即可。

需要注意的点:

1. 单个账号之间有空格，建议使用getline(cin,sAccount)获取字符串。

2. 排序直接按照字典序排序即可，使用STL提供的sort()方法可以很方便。

3. 在开始获取字符串之前要先执行一次getline()方法，目的是读取掉输入数字之后留下的不需要的字符。

代码:
```
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sAccount; //暂存输入的账号
	map<string, int> mapAccounts; //建立账号和出现次数的对应
	vector<string> arrAccounts; //存放账号
	register int i, j; //循环计数器
	int nTest, nCount; //nTest-测试用例个数；nCount-每个用例账户数
	cin >> nTest; //读入测试用例个数
	for (i = 1; i <= nTest; ++i){ //开始执行
		cin >> nCount; //读入个数
		getline(cin, sAccount); //读取掉输入数字之后留下的不需要的字符
        for (j = 1; j <= nCount; ++j){ //读入账户
			getline(cin, sAccount); //获取行
			if (mapAccounts[sAccount]){ //如果map中此帐户已经存在
				++mapAccounts[sAccount]; //个数加一
			}
			else{ //否则
				arrAccounts.push_back(sAccount); //字符串压入动态数组
				++mapAccounts[sAccount]; //个数加一
			}
		}
		sort(arrAccounts.begin(), arrAccounts.end()); //按照字典序排序
		for (j = 0; j < arrAccounts.size(); ++j){ //输出
			cout << arrAccounts[j] << ' ' << mapAccounts[arrAccounts[j]] << endl; //输出莫忘换行
		}
		cout << endl; //别忘了空一行
		arrAccounts.clear(); //清空动态数组
		mapAccounts.clear(); //清空映射表
	}
	return 0; //结束
}
```

---

## 作者：SIXIANG32 (赞：3)

一道 ```map``` 好题。  
闲话少说，切入正题——


------------
显然，统计一个字符串出现的次数普通的数组很难实现。  
那么，神奇的 ```map``` 就要~~自带 BGM+高光~~登场啦~  
```map``` 是映射，说白了就是个万能下标的数组，用途及其广，由于内置红黑树，可自动排序，时间复杂度也都是 $\log_2$级别的，非常实用，有时也可以靠着 ```map``` 省空间。 

```map``` 的格式是这样的：  
```cpp
map<下标类型,值的类型>名字;
```  

那么我们已经有个大致的思路了，遇到一个字符串，运用 ```map``` 统计这个字符串出现的次数。  

可是题目还要输出字符串，这普通的 ```map``` 就难以统计了。  

我们可以运用 ```pair``` 这个好东西。```pair``` 可以把两个元素合成一组成为一个 ```pair```，说白了就是个两个元素的结构体，但是能省代码。  

```pair``` 的格式是：  
```cpp
pair<类型,类型>
```  
想取第一个元素为 ```first```，第二个元素为 ```second```。  

如果想弄一个 ```pair```，我们需要用 ```make_pair``` 函数，格式和 ```pair``` 定义一样，就不多说了。  

还有个问题，就是 ```map``` 的下标我们并不是很清楚啊，如果用数组存，那还要排序，那就太不方便了，而且这样做也很多余，因为 ```map``` 内置排序。  

这时候，我们就要用 ```iterator``` 迭代器进行遍历了，这个迭代器和指针差不多，用法也与指针相似。在遍历 ```map``` 的时候，```it->first``` 为下标，```it->second``` 为值。  


------------
一切技术问题已经全部解决了，下面再总结一下思路：  
1. 用一个 ```map<string,pair<string,int> >``` 存储字符串和出现的次数。  
2. 运用迭代器遍历这个 ```map```并且输出。

上代码：
```cpp
#include<iostream>
#include<utility>//pair的头文件
#include<map>//map的头文件
#define MSPSI map<string,pair<string,int> >
#define glcs getline(cin,str)
using namespace std;
MSPSI M1;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		M1.clear();//一定要先把这个 map 清空
		string str;
		int n;
		cin>>n;
		glcs;
		for(int p=1;p<=n;p++)
			glcs,M1[str]=make_pair(str,M1[str].second+1);
		for(MSPSI::iterator it=M1.begin();it!=M1.end();it++)
			cout<<M1[it->first].first<<' '<<M1[it->first].second<<endl;
		cout<<endl;
	}
}
```
看我写的这么认真，管理大大给个通过嘛 qwq

---

## 作者：zhanghengrui (赞：2)

看了下两篇题解，发现都是用__string__来存账户号的。这里发一种用__int__做的。

（其实用__string__会省事很多，但相对来说__int__比较快~~（貌似这题用__string__也能过）~~）

话不多说，上代码。
```cpp
#include<cstdio>
#include<map>
class account//结构体（其实用struct也没什么区别）
{
    private:
        int control,code,identifying[4];//变量，从前到后依次对应题目中从前到后六段
    public:
        void input()//输入函数
        {
            scanf("%d%d%d%d%d%d",&control,&code,identifying,identifying+1,identifying+2,identifying+3);
        }
        void output()//输出函数
        {
            printf("%02d %08d %04d %04d %04d %04d",control,code,identifying[0],identifying[1],identifying[2],identifying[3]);//不足应有的位数就输出‘0’
        }
        bool operator<(const account& a) const//比较函数，用于升序排列
        {
        	//一段一段比较
            if(control<a.control) return true;
            if(control>a.control) return false;
            if(code<a.code) return true;
            if(code>a.code) return false;
            for(int i=0;i<4;++i)
            {
                if(identifying[i]<a.identifying[i]) return true;
                if(identifying[i]>a.identifying[i]) return false;
            }
            return false;
        }
};
std::map<account,int> mp;//map
int main()
{
    int t,n;
    account tmp;
    scanf("%d",&t);
    while(t--)//t组数据
    {
        scanf("%d",&n);
        while(n--)
        {
            tmp.input();//输入
            ++mp[tmp];//出现次数+1
        }
        for(std::map<account,int>::iterator iter=mp.begin();iter!=mp.end();++iter)//遍历map并输出
        {
            if(iter!=mp.begin()) putchar(10);
            tmp=iter->first;
            tmp.output();//输出账户号
            printf(" %d",iter->second);//输出出现次数
        }
        if(t)//如果还有数据
        {
            puts("\n");//相当于printf("\n\n")
            mp.clear();//清空map
        }
    }
    return 0;
}
```
[AC记录](https://www.luogu.org/record/show?rid=12853208)

~~（2018.11.01 暂时还没有比我快的）~~

---

## 作者：Drystynt (赞：1)

看到各位dalao都用$\rm map$、$\rm vector$一些高级东西，本人不才，~~只会用string~~(bushi)，那就来一个low点的题解吧

首先，$\rm string$类型是可以被$\rm sort$的，就是按字典序排列的。

后面一个模拟即可。

**坑点：**

1. 账号中间有空格，要用`getline`!
2. 输入可能会在账号最后又输入一个空格，所以我输出没有用`cout`，而是写了一个函数`printt`:

```cpp
void printt(string s)
{
for(int i=0;;i++){
    if(i==s.length() || (i==s.size()-1 && s[i]==' '))break;
    else cout<<s[i];}
}
```

**In a word,**上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[100001];
void printt(string s)
{
for(int i=0;;i++){
    if(i==s.length() || (i==s.size()-1 && s[i]==' '))break;
    else cout<<s[i];}
}

int main()
{
    int n;cin>>n;
    for(int k=1;k<=n;k++)
    {
        int t;
        cin>>t;
        scanf("\n");
        for(int l=1;l<=t;l++)
        {
            getline(cin,s[l]);
        }
        sort(s+1,s+t+1);
        printt(s[1]);cout<<' ';
        int b=1;
        for(int i=2;i<=t;i++)
        {
            if(s[i]==s[i-1])
                b++;
            else
            {
                cout<<b<<endl;b=1;
                printt(s[i]);cout<<' ';
            }
        }
        cout<<b<<endl;
    }
    cout<<endl;
    return 0;
}
```

---

## 作者：几时明月 (赞：0)

看到这题，我就想起了结构体，嗯。作为蒟蒻的我，迫不及待地写了这一篇题解.

首先，我们要有一个字符串来存储每张卡的信息

用整型变量来存储卡出现的次数

当然，定义结构体有些人Ta没学过，它是这么用的
```cpp
struct{

要定义的东西

}定义名；
```
然后，就没然后了，代码来了：
```cpp
#include <bits/stdc++.h>//多用万能头
using namespace std;
struct card{//结构体
    string b;
    int n;
};
int t, n;//定义
string s, m;
int main(){
    cin >> t;
    while (t--){
        map<string, card> _map;
        cin >> n;
        for (int i = 1; i <= n; ++i){
            s = "";
            for (int j = 1; j <= 6; ++j){
                cin >> m;
                s += m;
            }
            ++_map[s].n;
            _map[s].b = s;
        }//到后面就只是很多循环
        for (map<string, card>::iterator i = _map.begin(); i != _map.end(); ++i){
            cout << _map[i->first].b[0] << _map[i->first].b[1] << " ";
            for (int j = 0; j < 8; ++j)
            {
                cout << _map[i->first].b[j + 2];
            }
            cout << " ";
            for (int j = 0; j < 4; ++j)
            {
                cout << _map[i->first].b[j + 10];
            }
            cout << " ";
            for (int j = 0; j < 4; ++j)
            {
                cout << _map[i->first].b[j + 14];
            }
            cout << " ";
            for (int j = 0; j < 4; ++j)
            {
                cout << _map[i->first].b[j + 18];
            }
            cout << " ";
            for (int j = 0; j < 4; j++){
                cout << _map[i->first].b[j + 22];
            }
            cout << " ";
            cout << _map[i->first].n << endl;//最后输出
        }
        cout << endl;
    }
    return 0;//终于结束了
}
```
很长，但不会超时，要用时大于了5000ms,但你可以看看题目。

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

废话不多说，这道题我们使用模拟法来解题。（不过我这种模拟法跟其他楼的大佬方法有一些不同）

我们先将输入的字符串进行字典序排序，这里要注意一下，因为会出现空格，所以我们要用"getline()"，就是将整一行读入。然后我们再寻找一串相同的号码的起始点和结束点，并用：结束点-起始点+1求出这一串相同的号码的个数。

详情代码：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;
long long t,n;
string st[1000000];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		getline(cin,st[0]);
		for(int i=1; i<=n; i++)
		{
			getline(cin,st[i]);
		}
		sort(st+1,st+1+n);
		st[n+1]="";
		int wzz=1;
		for(int i=1; i<=n; i++)
		{
			if(st[i]==st[i+1])continue;
			cout<<st[i]<<' '<<i-wzz+1<<endl;
			wzz=i+1;
		}
	}
    return 0;
}

```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：happybob (赞：0)

STL大法好，来一个map + string吧

其实很简单，每次用6次for循环读入一个string，然后和一个y，每次读入把读入的加到y后面，循环变量大于等于2就加空格！，然后通过map <string, int>类型每次加一，代码如下：

```cpp
#include <iostream>
#include <map>
#include <cstring>
using namespace std;

map <string, int> mp;

int main()
{
    int n, m;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> m;
        for(int v = 1; v <= m; v++)
        {
            string y, p;
            for(int j = 1; j <= 6; j++)
            {
                cin >> p;
                if(j >= 2)
                {
                    y += ' ' + p;
                }
                else
                {
                    y += p;
                }
            }
            mp[y]++;
        }
        for(map <string, int>::iterator it = mp.begin(); it != mp.end(); ++it)
        {
            cout << it -> first << " " << it -> second << endl;
        }
        mp.clear();//这个不能忘
    }
    return 0;
}
```

还有另外一个map题解的毒瘤输出是啥？看不懂

---

## 作者：iorit (赞：0)

[原题](https://www.luogu.com.cn/problem/SP27)

这题可以直接暴力A

因为：

`时间限制 | 内存限制`

$\quad\;$`7.00s | 1.46GB`

![/ts](https://cdn.luogu.com.cn/upload/pic/62239.png)

注意输入有空格，所以要用getline

### 代码

```cpp
// 此处应有头文件
int n,t;
string a[100005];
int main()
{
    cin >> t;
    while(t--)
    {
    	cin >> n;
    	scanf("\n"); // 处理换行，否则getline会少读一行
    	for(int i = 1;i <= n;i++)
    		getline( cin , a[i] );
    	sort(a + 1 , a + 1 + n); // 直接排序
    	int cnt = 1; // 重复次数
    	for(int i = 1;i <= n;i++)
    	{
    		if( i < n && a[i] == a[i + 1] )
    			cnt++;
			else
			{
				cout << a[i] << " " << cnt << endl;
				cnt = 1;
			}
		}
	}
    return 0;
}
```


---

## 作者：Nozebry (赞：0)

## $Problems$
给出 $T$ 组数据，每组数据先给出一个整数 $n$（$0\le n\le100000$)，再给出 $n$ 个字符串，表示某个人的银行帐号的 $ID$。现在要你先对银行帐号进行升序排序，并把重复出现的银行帐号进行合并。
## $Answer$
这道题我们可以用**最长平台**来做。

先用一个快拍对 $n$个银行帐号进行排列，在利用一个数 $ans$ 来记录某个银行帐号出现的次数，如果当前这个银行帐号与前面那个不相等，则表示这个银行帐号已经不会在出现了，就把这个帐号和 $ans$ 输出。

## $Code$
```pascal
var
	t,i,n,ans:longint;
	a:array[0..110000]of string;

procedure sort(l,r:longint);//利用快拍把银行帐号按照升序排列一下
var
	i,j:longint;
	x,y:string;
begin
	i:=l;j:=r;x:=a[(l+r)>>1];
	repeat
		while a[i]<x do inc(i);
		while x<a[j] do dec(j);
		if not(i>j) then
		begin
			y:=a[i];a[i]:=a[j];a[j]:=y;
			inc(i);dec(j);
		end;
	until i>j;
	if l<j then sort(l,j);
	if i<r then sort(i,r);
end;

begin
	readln(t);
	while t>0 do
	begin
		readln(n);dec(t);
		for i:=1 to n do
		begin
			readln(a[i]);
			if a[i][length(a[i])]=' ' then delete(a[i],length(a[i]),1);//特殊考虑，如果最后一位有空格，则需要删除。
		end;
		sort(1,n);ans:=1;
		for i:=2 to n do
			if a[i]=a[i-1] then inc(ans)//如果这个帐号还在出现，则把ans继续累加
				else
				begin
					writeln(a[i-1],' ',ans);//不然则输出。注意，因为是当前这个与前一个不一样，而ans统计的是a[i-1]出现的次数，所以输出是应是a[i-1]
					ans:=1;
				end;
		writeln(a[i],' ',ans);//最后一个帐号是可能与前一个相同的，所以需要还需再输出一下。
	end;
end.
```

---

## 作者：hensier (赞：0)

该题可以使用$struct+sort$（快排$STL$大法）进行简单模拟——~~然而大佬们却在使用高端的$map$。~~

算法还是比较容易理解的——每一组数据的初始化要求也不是太苛刻。而$struct$存储的话，由于$int$会自动去掉前导$0$，因此我们考虑使用$string$类型进行保存。

再者，我们可以做一些富有价值的函数——$compare(cmp)$函数对于$struct$快排来说极其重要，而我们可以设置一个$check$函数来检验两个$struct$的值是否完全相等。

本程序为了更加方便地判断是否相等，因此引入了$STL-sort$算法。$sort$的算法本质就是将一组数据从小到大（或者按照$compare(cmp)$函数的指示）的顺序进行排列。而如果某一数据重复，那么它们必定在排序之后连续出现，这也方便了查找。

具体方法就是——$sort$之后，设置一个指针（以下简称$id$）和一个新的自定义结构体变量（以下简称$current$）。$id$初始化为$1$（本蒟蒻采用初始下标为$1$），$current$初始化为每一组数据输入进来的第一个元素。接着在$i∈[2,n]$区间进行循环。对于任何一个$i$，如果输入进来的第$i$个结构体与$current$不同，则输出$current$的所有值和值相等的个数——即$i-id$。这样的循环进行之后，必定留存着一个$current$。这个时候就需要在每一组数据的最后把这个$current$及其个数进行输出——这样才能考虑全面。

$AC$代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct bank
{
    string a[6];
}b[100001],current;//定义结构体数组以及上文中的current
bool check(bank x,bank y)
{
    for(int i=0;i<6;i++)if(x.a[i]!=y.a[i])return 0;
    return 1;
}//设置check函数，只要有一个元素不相等就返回0，否则返回1
bool compare(bank x,bank y)
{
    for(int i=0;i<6;i++)if(x.a[i]!=y.a[i])return x.a[i]<y.a[i];按照升序排列
    return 0;//这里写return 1;也无妨
}
int t,n,i,j,id;
int main()
{
    scanf("%d",&t);//数据组数
    while(t--)
    {
        scanf("%d",&n);//输入元素个数
        for(i=1;i<=n;i++)for(j=0;j<6;j++)cin>>b[i].a[j];//每一个元素输入
        std::sort(b+1,b+n+1,compare);//进行排序
        current=b[1];
        id=1;//指针、结构体初始化
        for(i=2;i<=n;i++)
        {
            if(!check(b[i],current))
            {
                for(j=0;j<6;j++)cout<<current.a[j]<<" ";//不相同就输出current（即上一次）的值
                printf("%d\n",i-id);//输出个数
                id=i;
                current=b[i];//指针和结构体重新设置
            }
        }
        for(j=0;j<6;j++)cout<<current.a[j]<<" ";
        printf("%d\n\n",n-id+1);//最后还要进行输出（有两个换行）
    }
}
```

---

## 作者：Zirnc (赞：0)

[ChungZH's blog](https://chungzh.cn) · [ChungZH's OI blog](https://oi.chungzh.cn)

这道题还算简单，其实不需要用 `map`（虽然刚开始我也是想到 `map` 的，但是觉得有点麻烦）。用一个 `string` 数组存号码，把所有号码读进去，排序，然后输出的时候数一下出现的次数就行了。

~~我的解法在 2019.08.20 的时候按最优解排序是第二  嘿嘿嘿~~


```cpp
// [SP27 SBANK - Sorting Bank Accounts] https://www.luogu.org/problem/SP27
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; i++)
    {
        int n;
        scanf("%d", &n);

        string a[n];
        getchar();
        for (int j = 0; j < n; j++)
        {
            getline(cin, a[j]);
        }
        if (i == T-1) a[n-1] += ' ';
        sort(a, a+n);

        int cnt = 1;
        for (int j = 1; j < n; j++)
        {
            if (a[j] == a[j-1])
            {
                cnt++;
            } else {
                cout << a[j-1] << cnt << '\n';
                cnt = 1;
            }
        }
        cout << a[n-1] << cnt << '\n';
    }
    return 0;
}
```

---

## 作者：TRZ_2007 (赞：0)

翻了下大佬们的题解，都觉得写得太复杂了，所以本蒟蒻就发一个简单点的。  
在题目描述哪里停了一会儿，因为不知道用什么来做关键字排序，然后突然想起来$string$有自带的大小比较。  
那就可以把它来当数字来看了。
$code$
```
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;//定义大一点总没有坏处
int t;
string bank[N];//定义一个string类型的数组来存银行账号
void doit()//有多组样例
{
	int n,sum=1;
	cin>>n;
	getchar();//过滤空格
	for(int i=1;i<=n;i++)
		getline(cin,bank[i]);//读入，注意用getline
	sort(bank+1,bank+n+1);
	for(int i=1;i<=n;i++)
	{
		if(bank[i]!=bank[i+1])
		{
			cout<<bank[i]<<" "<<sum<<"\n";//如果排好后下一个不是自己人，就输出
			sum=1;//计数器归1
		}
		else if(bank[i]==bank[i+1])//还是的话继续加
			sum++;
	}
}
int main()
{
	cin>>t;//读入t
	while(t--) doit();
}
```

---

