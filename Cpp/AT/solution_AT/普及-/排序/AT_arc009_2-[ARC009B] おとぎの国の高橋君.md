# [ARC009B] おとぎの国の高橋君

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc009/tasks/arc009_2

高橋君の住むAtCoder国では、私達が普段使用する数字と同様に $ 10 $ 個のアラビア数字 $ (0-9) $ の $ 10 $ 進数が使われています。  
 しかし、私達が普段使用する数字は大小関係が $ 0\ の順になっているのに対して、
AtCoder国の数字ではその大小関係が異なっています。
例えば、AtCoder国の数字では\ 0\ の順になっている場合、AtCoder国では\ 9 $ よりも $ 8 $ の方が大きいことになります。また、$ 97 $ よりも $ 72 $ の方が大きいことになります。  
  
 AtCoder国の数字の大小関係といくつかの数が与えられるので、AtCoder国の数字の大小関係で昇順に並び替えてください。  
 なお、私達が普段使用する数字同様、AtCoder国で最も小さい数字は $ 0 $ であることは決まっています。 入力は以下の形式で標準入力から与えられる。

> $ b_0 $ $ b_1 $ ‥‥ $ b_9 $ $ N $ $ a_0 $ $ a_1 $ : : $ a_{N-1} $

- 入力は $ N+2 $ 行ある。
- $ 1 $ 行目には、AtCoder国での $ 1 $ 桁の数字の大小関係が与えられる。 
  - AtCoder国では $ b_0\ であることを表している。 $
  - $ b_0 $ は必ず $ 0 $ である。
  - 重複する数字は存在せず、$ 0 $ から $ 9 $ までの数字が $ 1 $ 度ずつ現れる。
- $ 2 $ 行目には並び替える数の個数を表す整数 $ N(1≦N≦777) $ が与えられる。
- $ 3 $ 行目からの $ N $ 行には、$ j+3 $ 行目に並び替える数を表す整数 $ a_j(1≦a_j≦777,777,777) $ が与えられる。
 
 与えられた数をAtCoder国の数字の大小関係にあわせて昇順に並び替え、標準出力に $ 1 $ 行に $ 1 $ つの数字ずつ出力せよ。  
 なお、最後には改行を出力せよ。 ```

0 8 1 3 5 4 9 7 6 2
10
1
2
3
4
5
6
7
8
9
10
```

 ```

8
1
3
5
4
9
7
6
2
10
```

- AtCoder国ではこの大小関係の場合、$ 0,\ 8,\ 1,\ 3,\ 5,\ 4,\ 9,\ 7,\ 6,\ 2,\ 80,\ 88,\ 81,\ 83,\ ...,\ 86,\ 82,\ 10,\ 18,\ 11,\ ... $ の順に大きくなるので、答えは上記の順になります。
 
```

0 9 8 7 6 5 4 3 2 1
3
13467932
98738462
74392
```

 ```

74392
98738462
13467932
```

- $ 5 $ 桁の数は $ 8 $ 桁の数よりも小さいので、$ 1 $ 番は $ 74392 $ になります。
- $ 98738462 $ と $ 13467932 $ では最上位の $ 9 $ は$ 1 $ より小さいので、$ 98738462 $ が $ 2 $ 番目、$ 13467932 $ が $ 3 $ 番目になります。
 
```

0 1 2 3 4 5 6 7 8 9
4
643
1234
43
909
```

 ```

43
643
909
1234
```

- 私達の普段使用する数と同じ大小関係に昇順に並べます。
 
```

0 7 4 3 9 5 6 2 1 8
2
333
333
```

 ```

333
333
```

 ```

0 2 4 6 8 1 3 5 7 9
1
10
```

 ```

10
```

# 题解

## 作者：CZQ_King (赞：7)

看到这题，我第一的反应是：

## 基数排序！

如下图所示，这就是基数排序（这个图搞了好久）
![](https://s2.ax1x.com/2019/08/04/ey096f.gif)

我们可以类似基数排序的方法，来对这些数据进行排序，即使他们数字的顺序不是和我们一样的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[800],len;
struct S{//定义结构体
	int num;//Atcoder国的数字，类似于10个桶
	queue<int>q;//放数字，这里为了简化使用了队列，也可以用数组
}x[10];//Atcoder国的10个数字的顺序
int main(){
	for(int i=0;i<10;i++)cin>>x[i].num;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		len=max(len,(int)log10(a[i])+1);//获取输入的数字中长度最长的数字的长度
	}
	for(int i=1;i<=len;i++){//从个位开始，直到最高位
		int po=pow(10,i-1),k=0;//po用于计算数字的某一位
		for(int i=0;i<n;i++){//将数字放进桶里
			for(int j=0;j<10;j++){//在10个桶里找
				if(a[i]/po%10==x[j].num){//如果某一位相等
					x[j].q.push(a[i]);//添加到队列里
					break;//后面都不可能了，直接break掉
				}
			}
		}
		for(int i=0;i<10;i++){//分别从10个桶里拿出来
			while(!x[i].q.empty()){//直到桶里空了
				a[k++]=x[i].q.front();//获得最前面的
				x[i].q.pop();//记得要弹走最前面的
			}
		}
	}
	for(int i=0;i<n;i++)cout<<a[i]<<endl;//输出全部
}
```

---

## 作者：MattL (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/AT315) & [原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/315)

~~这题太shui了~~

---

**题意：**

要求你按题目给的数字的大小顺序排序。

---

**解题：**

首先，排序我们可以用 ```sort``` 来进行排序。

正常排序模板：

```cpp
sort(first,last);//first是数组第一个数据的地址，last是最后一个数据的地址+1
```
而要是你有特定要求的话……
```cpp
sort(first,last,cmp);//first和last同上，cmp是自定义的bool类型的比较函数
```
其实你重载运算符也行。

在这题， ```cmp``` 函数如下：
```cpp
inline bool cmp(string a,string b)//inline是调用时加速的
{
    if(a.size()!=b.size())return a.size()<b.size();//要是位数都不同，就可以直接return了
    for (int i = 0; i < a.size(); ++i) {//由于长度相等，a或b的size()都可以
        if(a[i]!=b[i])return c[a[i]-'0']<c[b[i]-'0'];//要是这一位不一样，就可以按照题目给的顺序return了
    }
    return false;//相等，return true或false都行
}
```
好了，现在核心部分都讲完了，就来实现吧！

---

**代码：**

完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline long long read()//快读，可以不用
{
    register long long x=0,f=1;
    register char c=getchar();
    while(c<'0'||c>'9')if(c=='-'){f=-1,c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}

int c[10],n;//c[i]表示i的等级
string b[788];
inline bool cmp(string a,string b)//解释见上
{
    if(a.size()!=b.size())return a.size()<b.size();
    for (int i = 0; i < a.size(); ++i) {
        if(a[i]!=b[i])return c[a[i]-'0']<c[b[i]-'0'];
    }
    return false;
}
int main() {
    for (int i = 0; i <10; ++i) {
        c[read()]=i;//读入题目要求的大小顺序
    }
    n=read();
    for (int i = 0; i < n; ++i) {
        cin>>b[i];//输入要排序的数据
    }
    sort(b,b+n,cmp);//排序
    for (int i = 0; i < n; ++i) {
        cout<<b[i]<<endl;//输出排序后的数组
    }
    return 0;
}

```


---

## 作者：LiveZoom (赞：1)

# 题解 AT315 【おとぎの国の高橋君】

本题是对sort排序和字符串的考察。我们用字符串来存这些数。

- 存储大小之间的关系

我们用一个cmp数组，表示数字$i,j$之间的大小关系：

1.cmp[i][j]=0时，表示数字i小于j。  
2.cmp[i][j]=1时，表示数字i大于j。

定义：

```cpp
bool cmp[10][10];
```

修改：

```cpp
	for (int i = 0; i < 10; i++) {
		cin >> x[i];//x[i]表示排名第i个的数字
		for (int j = 0; j < i; j++) {
			cmp[x[i]][x[j]] = true;//遍历所有“小于”x[i]的数，并标记
		}
	}	
```

- sort排序

sort的精华就是比较函数了：  

```cpp
bool cmp1 (string a, string b) {//由于我们有cmp的数组了，为了不重复，就定义了个cmp1
	int len1 = a.size(), len2 = b.size();//分别表示a,b的数位个数
	if (len1 > len2) return false;//如果a的数位多于b的数位，则返回false
	else if (len1 < len2) return true;//同理，当b的数位多于a的数位，则返回true
	for (int i = 0; i < len1; i++) {//从0~len1-1，就相当于从各位遍历到最高位
		if (cmp[a[i] - '0'][b[i] - '0']) return false;//但a[i]“大于”b[i]，返回false
		else if (cmp[b[i] - '0'][a[i] - '0']) return true;//否则返回true
	}
	return false;//这个写true或false没有区别
}
```
其余的部分很简单，就不讲了。

整体代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
string a[900];
int x[10];

bool cmp[10][10];

bool cmp1 (string a, string b) {
	int len1 = a.size(), len2 = b.size();
	if (len1 > len2) return false;
	else if (len1 < len2) return true;
	for (int i = 0; i < len1; i++) {
		if (cmp[a[i] - '0'][b[i] - '0']) return false;
		else if (cmp[b[i] - '0'][a[i] - '0']) return true;
	}
	return false;
}

int main() {
	for (int i = 0; i < 10; i++) {
		cin >> x[i];
		for (int j = 0; j < i; j++) {
			cmp[x[i]][x[j]] = true;
		}
	}	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort (a + 1, a + 1 + n, cmp1);
	for (int i = 1; i <= n; i++)
		cout << a[i] << endl;
	return 0;
}
```

---

## 作者：monstersqwq (赞：1)

使用一个数组 s 记录 AtCoder 国的数字大小关系， $s_i$ 表示 AtCoder 国的数字 i 表示我们使用的数字 j。

用字符串存储 AtCoder 国家的数字，直接进行 sort 的升序排序。

排序函数（cmp，bool 类型）：长度不相等时返回长度更小的，相等时把它转换成我们使用的数字，再返回更小的。（string 类型的长度函数是 $a.\operatorname{length}()$，转换我使用的是一个循环，每次 $a1 \gets a1 \times 10 + s_{a_i-'0'}$）

其它在代码里都有注释。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>//可爱的头文件 
using namespace std;
string a[800];//存储数字 
int s[10],n;//s[i]=j表示AtCoder国的数字i是我们使用的j 
bool cmp(string a,string b)
{
	if(a.length() !=b.length() ) return a.length() <b.length() ;//长度不相等时返回长度更小的 
	int a1=0,b1=0;
	for(int i=0;i<a.length() ;i++)
	{
		a1=a1*10+s[a[i]-'0'];
	}
	for(int i=0;i<b.length() ;i++)
	{
		b1=b1*10+s[b[i]-'0'];//转换成我们使用的数字（其实可以合并成1个循环） 
	}
	return a1<b1;//返回数值更小的 
}
int main()
{
	for(int i=0;i<=9;i++)
	{
		int tmp;
		cin>>tmp;
		s[tmp]=i;
	}
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//读入 
	}
	sort(a+1,a+n+1,cmp);//排序 
	for(int i=1;i<=n;i++)
	{
		cout<<a[i]<<endl;//输出 
	}
    return 0;
}
```


---

## 作者：happybob (赞：0)

 _Update：2020.11.5 新增运算符重载代码_ 

本题还真是有意思！

我的思路是这样的

对于输入的顺序，将这些顺序先储存起来

然后输入时做一个类，类中包含一个数字和一个类似运算符重载的小于函数is_small，参数有两个，两个类

对于这两个类，转成字符串做比较，先看长度，长度一样一位位比较

附上AC代码（好像我这个内存和时间都比大家多，哇）

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int mp[15];

class Cla
{
    public:
        int a;
        bool is_small(Cla g, Cla h)
        {
            string x = to_string(g.a), y = to_string(h.a);
            int len = x.length(), len2 = y.length();
            if(len > len2)
            {
                return false;
            }
            else if(len < len2)
            {
                return true;
            }
            else
            {
                len--;
                len2--;
                for(int i = 0; i <= len; i++)
                {
                    if(mp[x[i] - '0'] < mp[y[i] - '0'])
                    {
                        return true;
                    }
                    else if(mp[x[i] - '0'] > mp[y[i] - '0'])
                    {
                        return false;
                    }
                }
                return true;
            }
        }
};

Cla a[790], s;

bool cmp(Cla x, Cla y)
{
    return s.is_small(x, y);
}
int main()
{
    for(int i = 1; i <= 10; i++)
    {
        int x;
        cin >> x;
        mp[x] = i;
    }
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i].a;
    }
    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; i++)
    {
        cout << a[i].a << endl;
    }
    return 0;
}
```

但这个代码的效率比较低，其原因在于to_string()，这样写的话每次转string很慢

那直接写成string更好，还有我们上面讲过运算符重载，那我们也可以用运算符重载做

那你肯定会问，运算符重载不是只支持一个参数吗？对比两个类怎么做？

那你肯定是不知道友元函数

友元是支持两个参数的哦

注意，友元函数是定义在类外，所以如果用operator <(x, y)的话不要再operator前加‘类.’做访问

那么，代码不就简单了吗？速度快了几十ms

```
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int mp[15];

class Cla
{
    public:
        string a;
        friend bool operator <(const Cla &x, const Cla &y)//友元需在返回类型前加上friend
        {
            int len = x.a.length(), len2 = y.a.length();
            if(len > len2)
            {
                return false;
            }
            else if(len < len2)
            {
                return true;
            }
            else
            {
                len--;
                len2--;
                for(int i = 0; i <= len; i++)
                {
                    if(mp[x.a[i] - '0'] < mp[y.a[i] - '0'])
                    {
                        return true;
                    }
                    else if(mp[x.a[i] - '0'] > mp[y.a[i] - '0'])
                    {
                        return false;
                    }
                }
                return true;
            }
        }
};

Cla a[790];

bool cmp(Cla x, Cla y)
{
    return x < y;//也可以写成operator <(x, y);
}

int main()
{
    for(int i = 1; i <= 10; i++)
    {
        int x;
        cin >> x;
        mp[x] = i;
    }
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i].a;
    }
    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; i++)
    {
        cout << a[i].a << endl;
    }
    return 0;
}
```

---

## 作者：_Ayanami_ (赞：0)

直接用字符串处理

将数字变为对应成正常数字

然后按排序一遍输出
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	string s,ss;
}
z[777];
char a[10];//存对应的数字
int n,l,x;
bool cmp(node x,node y)
{
	if(x.s.length()==y.s.length())return x.s<y.s;
	//长度相等时直接按字典序
	else return x.s.length()<y.s.length();
	//长度不相等时短的放前面
}
int main()
{
	for(register int i=0;i<10;++i)
	{
		cin>>x;
		a[x]=i+'0';
	}
	cin>>n;
	for(register int i=0;i<n;++i)
	{
		cin>>z[i].s;
		z[i].ss=z[i].s;
		l=z[i].s.length();
		for(register int j=0;j<l;++j)
		{
			z[i].s[j]=a[z[i].s[j]-'0'];//替换
		}
	}
	sort(z,z+n,cmp);//排序
	for(register int i=0;i<n;++i)
	{
		cout<<z[i].ss<<endl;
	}
}
```

---

## 作者：智子·起源 (赞：0)

### 思路很简单，就是模拟。

### 我是用结构体排序的。。。

定义一个结构体数组，里面有两个元素：1、它本身的数字；2、它在数字中的大小（以便于结构体排序）

由于前导0的问题，我是用字符串求出它在数字中的大小的。（Cover第一篇题解）

放代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,f[10],s;string ss;
struct data
{int a,b;}a[778];
bool cmp(data a,data b){return a.b<b.b;}
int main()
{
  for(int i=0;i<10;i++){cin>>s;f[s]=i;}
  cin>>n;
  for(int i=0;i<n;i++)
  {
    cin>>a[i].a;
    s=a[i].a,a[i].b=0,ss="";
    while(s>0)ss+=s%10,s/=10;
    for(int j=ss.size()-1;j>=0;j--)a[i].b=a[i].b*10+f[ss[j]];
  }//读入原来的数并求出它的实际大小。
  sort(a,a+n,cmp);//按实际大小结构体排序。
  for(int i=0;i<n;i++)cout<<a[i].a<<endl;//输出
  return 0;
}
```


---

## 作者：RioBlu (赞：0)

最多只有777个数字，使用选择排序即可

本题因为使用数字不会简单，所以我使用了字符串
```
#include<bits/stdc++.h>
using namespace std;
long long qwq[14];//第X个数的权（大小）
bool xz(string a,string b)//比较函数，如果a>b return 1;否则return 0;
{
	if(a.size()>b.size())return 1;//a的位数比b的位数多
	if(a.size()<b.size())return 0;//a的位数比b的位数少
	for(int s=0;s<a.size();s++)
	{
		if(qwq[a[s]-'0']<qwq[b[s]-'0'])return 0;//b小
		if(qwq[a[s]-'0']>qwq[b[s]-'0'])return 1;//a大
	}
	return 0;
}
long long a,b;
string c[800];
int main()
{
	for(int s=0;s<10;s++)
	{
		cin>>b;
		qwq[b]=s+1;
	}
	cin>>a;
	for(int s=0;s<a;s++)
	{
		cin>>c[s];
	}
	for(int s=0;s<a;s++)//选择排序
	{
		for(int v=s+1;v<a;v++)
		{
			if(xz(c[s],c[v]))//c[s]>c[v]（前面的大于后面的，就交换）
			{
				swap(c[s],c[v]);
			}
		}
	}
	for(int s=0;s<a;s++)//输出
	{
		cout<<c[s]<<endl;
	}
}
```

---

