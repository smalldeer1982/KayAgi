# 古老的密码 Ancient Cipher

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4085

[PDF](https://uva.onlinejudge.org/external/13/p1339.pdf)

## 样例 #1

### 输入

```
JWPUDJSTVP
VICTORIOUS
MAMA
ROME
HAHA
HEHE
AAA
AAA
NEERCISTHEBEST
SECRETMESSAGES```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：Saberlve (赞：12)

# 大家在做此题前请留意那鲜艳的红色
相信本来想要怒刷红题找信心的人看到这个题就默默地关掉了，因为它的题目描述根本不像一道红题。


------------
## 所以我们再读一遍题


----------
嗯？？我们突然有了新发现，这题根本不需要求出所谓的映射规则，只要判断能不能转就好了，即便翻译规则可能只是瞎编的。


------------
相信说到这，大家都有思路了。没错！只要统计两个字符串中每个字符出现的次数，再比较是否相同就ok了。有重复的也不用考虑，可以随便对应。
### 下面上代码：
```
#include<bits/stdc++.h>
using namespace std;
char a[100001],b[100001];//存储字符 
int pw[10001],mw[100001];//统计个数 
int main()
{
	int i,l;
	scanf("%s",a);
	l=strlen(a);
	scanf("%s",b);//大家都懂 
	for(i=0;i<l;i++)
	{
		pw[a[i]-'A']++;	
		mw[b[i]-'A']++;
	}//因为只有26个大写字母，只需减A就能得到平常的顺序 
	sort(pw,pw+26);
	sort(mw,mw+26); //排序，方便之后比较 
	for(i=0;i<26;i++)
	{
		if(pw[i]!=mw[i])
		{
			cout<<"NO";return 0;
		}//如果有多的或少的就肯定不匹配。 
	}
	cout<<"YES";//一样的话输出yes 
	return 0;//完美结束 
}
```
## 就到这里了，，这题还是很简单的，建议手打一遍哦

---

## 作者：octal (赞：6)

# 第一次被red坑了这么久

# 于是决定发个题解

###  ~~貌似是数据改过了，之前的题解基本上都不能AC啊~~

## 数据应该是长这样的啊！！！~~（你懂的）~~

![](https://cdn.luogu.com.cn/upload/pic/59864.png)

## 建议管理员如果有空，能改一下翻译哦

### 这道题本身不难

### 就是对“桶”概念的运用

### 然后用一个sort进行比对就好了



## 最后附上代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
string x,y;
int i,t[30],p[30];

int main()
{
    while(cin>>x>>y)
    {
      memset(t,0,sizeof(t));
      memset(p,0,sizeof(p));
      if(x.size()!=y.size())
      {
    	  cout<<"NO"<<endl;
    	  continue;
      }
      for(i=0;i<x.size();i++)
      {
     	  t[x[i]-'A']++;
          p[y[i]-'A']++;
      }
      sort(t,t+26);
      sort(p,p+26);
      bool b=true;
      for(int i=0;i<=25;i++)
      if(t[i]!=p[i])
      {
    	  cout<<"NO"<<endl;
    	  b=false;
    	  break;
      }
      if(b)
      cout<<"YES"<<endl;
    }
    return 0;
}
```

由于题解中说明了题目本身的问题

希望管理员可以给过


---

## 作者：PC_DOS (赞：6)

这道题乍一看一头雾水: 凯撒加密和乱序加密的密钥都不可知，枚举肯定是行不通的，后来发现明文和密文之间有一个关系:

>密文: JWPUDJSTVP

>J出现2次，P出现2次，W出现1次，U出现1次，V出现1次，D出现1次，S出现1次。

>明文: VICTORIOUS

>O出现2次，I出现2次，V出现1次，C出现1次，T出现1次，R出现1次，S出现1次。

>密文: HAHA

>H出现2次，A出现2次。

>明文: HEHE

>H出现2次，E出现2次。

是不是说，合法的明文-密文对之间，总会有个数相等的字母出现相同的频数？

这是肯定的，首先，凯撒加密仅是对字母进行替换，会改变出现的字母，但是不会造成频数的改变，也就是说，如果某频数X对应Y个字母，凯撒加密之后对应关系(X,Y)依然存在。至于乱序加密，只是改变字母的顺序，不可能改变频数-字母个数对应关系。

所以，只需要分别得到密文字符串和可能的明文字符串之间频数-字母个数对应关系，比较两个关系是否相等即可。

代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int arrCharFreqOrig[26] = { 0 }, arrCharFreqCrypted[26] = { 0 }, iLength, i; //arrCharFreqOrig-记录推断的明文中各个字母出现的频数；arrCharFreqCrypted-记录密文中各个字母出现的频数；iLength-记录字符串长度；i-循环计数器
	string sOrig, sCrypted; //sOrig-推断的明文；sCrypted-密文
	while (cin >> sCrypted){ //如果有密文被读入(测试时，输入最后一个密文-明文对之后使用CTRL+Z(^Z)终止读入循环)
		cin >> sOrig; //读入推断的明文
		iLength = sCrypted.length(); //记录长度
		for (i = 0; i < iLength; ++i){ //统计各个字符出现的频数
			++arrCharFreqCrypted[sCrypted[i] - 'A'];
			++arrCharFreqOrig[sOrig[i] - 'A'];
		}
		sort(arrCharFreqCrypted, arrCharFreqCrypted + 26);
		sort(arrCharFreqOrig, arrCharFreqOrig + 26); //排序，去除字母表序的影响
		for (i = 0; i <= 25; ++i){ //判断频数-字母个数对应关系是否相等
			if (arrCharFreqCrypted[i] != arrCharFreqOrig[i]){ //显然如果对应关系相等，arrCharFreqCrypted[i] = arrCharFreqOrig[i]，如果发现arrCharFreqCrypted[i] <> arrCharFreqOrig[i]，对应关系不成立
				cout << "NO\n"; //输出否
				goto init; //跳出循环，转到init处
			}
		}
		cout << "YES\n"; //如果循环没有被跳出，说明对应关系成立
	init:
		for (i = 0; i <= 25; ++i){ //初始化两个数组
			arrCharFreqCrypted[i] = 0;
			arrCharFreqOrig[i] = 0;
		}
	}
	return 0; //结束
}
```

---

## 作者：andyli (赞：5)

楼下那个代码有点乱（~~怪~~），还用什么goto的。
实际上就是直接统计字符个数，排序后比较各个字母出现的数量。
代码如下：
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
const int maxn = 26;

int cnt1[maxn], cnt2[maxn];
int main()
{
	string s1, s2;
	while (cin >> s1 >> s2)
	{
		memset(cnt1, 0, sizeof(cnt1));
		memset(cnt2, 0, sizeof(cnt2));
		size_t len = s1.length();
		for (size_t i = 0; i < len; i++)
		{
			cnt1[s1[i] - 'A']++;
			cnt2[s2[i] - 'A']++;
		}
		sort(cnt1, cnt1 + 26);
		sort(cnt2, cnt2 + 26);
		bool flag = true;
		for (size_t i = 0; i < 26; i++)
		{
			if (cnt1[i] != cnt2[i])
			{
				flag = false;
				break;
			}
		}
		if (flag)
			cout << "YES" << endl;
		else
			cout << "NO " << endl;
	}
	return 0;
} //代码仅供参考，请各位自行编写代码，严禁抄袭
```

---

## 作者：mnesia (赞：2)

最初看到这道题的时候，其实感觉很无厘头是正常的，因为这个需要一点小小的思维量。

仔细浏览题面就可以发现，对密码做解密其实只有两种操作：

1. 随机排序；
2. 一一映射，即类似于 `f(x)` 与 `x` 的关系，或者说 `y` 与 `x` 的关系。

既然只有这两种操作，那就说明**明文字符串中原来某个字母出现了 a 次，在密文中就一定能找到一个字母，它出现的次数为 a**。

有了这个思路，接下来解题步骤就比较好想了：

1. 读入两个字符串，首先判断它们的长度是否相同，如果不相同就肯定不能互相转换，直接输出 `NO`，进入下一轮循环；
2. 对两字符串中各个字母出现的次数进行统计，统计结束之后对两个数组进行排序；
3. 遍历两个数组，如果发现第 i 小的“字母出现次数”（即在一个字符串中所有字母中出现次数的第 i 小的次数）不相等，那么根据上文的思路，两字符串不能互相转换，输出 `NO`；
4. 如果遍历结束后仍未找到不相等的“字母出现次数”，那么两字符串可以互相转换，输出 `YES`；
5. 从步骤 1 重新进行，直至无字符串输入。

下面给出代码实现过程：
```
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
string str1, str2;
int cnt1[27], cnt2[27];

void count(void);
bool compare(void);

void count()
{
    for(unsigned i = 0;i < str1.size();i++)
    {
        cnt1[str1[i] - 'A' + 1]++;
        cnt2[str2[i] - 'A' + 1]++;
    }
    return ;
}
bool compare()
{
    for(int i = 1;i <= 26;i++)
    {
        if(cnt1[i] != cnt2[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    while(cin >> str1 >> str2)
    {
        memset(cnt1, 0, sizeof(cnt1));
        memset(cnt2, 0, sizeof(cnt2));
        if(str1.size() != str2.size())
        {
            cout << "NO" << endl;
            continue;
        }
        count();//对 str1,str2 中各个字符出现的次数进行统计
        sort(cnt1 + 1, cnt1 + 27);
        sort(cnt2 + 1, cnt2 + 27);
        if(compare())
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
	return 0;
}

```
注：其实题面原文中有给出两字符串长度一定相等的条件（“Input”最后一行：“The lengths of both lines of the input file are equal and do not exceed 100.”），因此其实不用像我这样再添加一个判断字符串长度是否相等的步骤。

---

## 作者：D2T1 (赞：2)


既然字母可以重排，则每个字母的位置并不重要，重要的是每个字母出现的次数。

这样可以先统计出两个字符串中各个字母出现的次数，得到两个数组 $cnt1[26]$ 和 $cnt2[26]$。

下一步需要一点想象力：只要两个数组排序之后的结果相同，输入的两个串就可以通过重排和一一映射变得相同。

这样，问题的核心就是排序。

——《算法竞赛入门经典 第2版》


于是就很[简单](https://www.luogu.com.cn/record/list?pid=UVA1339&user=390770&status=14&page=1)了

```cpp
//UVA1339
#include <algorithm>
#include <iostream>
using namespace std;
int cnt1[26],cnt2[26];
string a1,a2;

int main(){
	while(cin >> a1 >> a2){	
		bool flg=true;
		for(int i=0; i<26; i++){
			cnt1[i]=0;
			cnt2[i]=0;
		}
		for(int i=0; i<a1.size(); i++){
			cnt1[a1[i]-'A']++;
			cnt2[a2[i]-'A']++;
		}
		sort(cnt1,cnt1+26);
		sort(cnt2,cnt2+26);
		for(int i=0; i<26; i++){
			if(cnt1[i]!=cnt2[i]){
				flg=false;
				break;
			}
		}
		cout << (flg?"YES":"NO") << endl;
	}
	return 0;
}
```


---

## 作者：超级小周 (赞：1)

这道题我想了大概有1个多小时...（这还是道入门难度的题）

转换，排序的方法不晓得，只叫你说YES，NO。由于转换字符加多少，排序也不知道规律，一般思路肯定做不出来。我想，正因为转换字符加多少，排序也不知道怎么排，所以可以任意字符可以转换成任意字符,所以只要统计一个字符串中每个字符（A，B...Z）的个数，那另一个字符要想YES,必然与上一个字符有联系。顺序问题就用sort来解决！
```c
	#include<bits/stdc++.h>
	using namespace std;
	string a,b;
	int a1[101]={0},b1[101]={0};//用来计数
	int main(){
		int lena,lenb;
		cin>>a;
		cin>>b;
		lena=a.size();
		lenb=b.size();
		if(lena!=lenb){//直接判断
			cout<<"NO";return 0;
		}
	/*	for(int i=0;i<=lena-1;i++){
			a[i]=a[i]-1;
		}*///这里是我以前错的地方，我想求解解不出来
		for(int i=0;i<=lena-1;i++){
			a1[a[i]-'A']++;//0为‘A’，25为‘Z’
			b1[b[i]-'A']++;//当然你有强迫症的话‘A’后面+1
		}
		sort(a1,a1+26);//排序
		sort(b1,b1+26);
		for(int i=0;i<26;i++){//可以比较了
			if(a1[i]!=b1[i]){cout<<"NO";return 0;
			}
		}
		cout<<"YES";
	return 0;}
```


这题告诉我们，不要被表面现象所迷惑，确实简单，但思路你想不出来的话就难了（像我做了一个多小时(ˇˍˇ））

---

## 作者：梁欣艺 (赞：1)

## **这题其实很简单，但是坑点很多。**

看到题目的第一反应是：找规律。

于是，埋头奋笔疾书一阵子后毫无头绪，开始怀疑自己的数学能力。


###### 但是，~~自恋~~机智的你发现，其实只要找每个字母出现的次数能否一一对应便可。



------------



 _举个例子——_ 

在一组对应值中：

e,s,g,t这四个字母出现的次数分别是2,5,3,2

而d,s,j,q这四个字母出现的次数也分别是2,5,3,2

那么它们就是~~一伙的~~符合规则的（就是这么随便，数字一一对应就行，别管是谁对应谁）


------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char later[3000],first[3000];
int lo,cnt[3000000],dnt[3000000];
int main()
{
	while(cin>>later>>first)
	{
		memset(cnt, 0, sizeof(cnt));
        memset(dnt, 0, sizeof(dnt));//Attention!这里是初始化的操作； 		
		lo=strlen(later);//Attention!用string申请的变量要用 lo=later.length();
		for(int i=0;i<lo;i++)
		{
			cnt[later[i]-'A']++;
			dnt[first[i]-'A']++;
		} 
		sort(cnt,cnt+26);
		sort(dnt,dnt+26);
		//#调试#for(int i=0;i<=25;i++)	{cout<<cnt[i];cout<<dnt[i]<<" ";} 
		bool flag=true;
		for(int i=0;i<26;i++) 
		{ 
	 		//#调试#cout<<cnt[i]<<dnt[i]<<" "; 
			if(cnt[i]!=dnt[i])
			{
				flag=false;
				break;//Attention！这里不能直接输出no然后return 0，不然后面会全挂； 
			}
		}
		if(flag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}	
	return 0;
}
```
**//rp++;**

---

## 作者：Zhangshihao (赞：0)

## 这道题有些奇怪（~~但不过也挺水的~~）
 做题过程中小心跳坑
## 思路如下
 按照题目给定的示例输入来看给定的两个输入串都是大写字母并且长度相等，通过对其中一个字符串进行某种映射变为另一个字符串，如果可以的话，即输出“YES”，如果不行，就要输出“NO”，因此我们直接计算两个字符串中各个字母的个数，分别将个数赋值给两个数组，由于并没有规定是哪种映射方式，因此只要将两个数组进行重排后，如果数组相等，即符合题意，输出“YES”。
## 代码如下
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
string s1="",s2="";
int main()
{
     int flag=1;  //标志位，判断最后两个数组是否相同
    while(cin>>s1>>s2){
        int a[30]={0};   //两个数组分别记录字母出现的次数
        int b[30]={0};
        for(int i=0;i<s1.length();i++){
            if(s1[i]=='A') s1[i]='Z';   
            else s1[i]--;
            a[s1[i]-'A']++;
            b[s2[i]-'A']++;
        }
        sort(a,a+30);  //对两个数组进行排序
        sort(b,b+30);
        for(int i=1;i<30;i++)
            if(a[i]!=b[i]) flag=0;
        if(flag) cout<<"YES"<<endl;
        else {
                cout<<"NO"<<endl;
                flag=1;
        }
    }
    return 0;//结束
}
```


---

## 作者：fjy666 (赞：0)

## 0x01 思路
这题虽然题面中似乎和加密解密有关，但实际却和它没关系。  
我们发现：
- 重新排列的时候，位置变了
- 一一映射的时候，字母变了

不变的是什么？对了！出现次数！  
所以，我们只要统计每个字母的出现次数，再看看能不能构成一一映射即可！  
怎么判断能否构成一一映射？
- 双重循环 $\Theta(T\times26^2)$
- `std::sort` $\Theta(T\times26\log26)$

## 0x02 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
const int kMaxn = 150,kMaxm = 35;
char a[kMaxn],b[kMaxn];
int a_[kMaxm],b_[kMaxm];

int main()
{
	while(~scanf("%s%s",a,b))
	{
		memset(a_,0,sizeof(a_));
		memset(b_,0,sizeof(b_));
		char *pa = a,*pb = b;
		while(*pa)
		{
			++a_[*pa - 'A'];
			++b_[*pb - 'A'];
			++pa;
			++pb;
		}
		std::sort(a_,a_+26);
		std::sort(b_,b_+26);
		fo(i,0,25)
			if(a_[i] != b_[i])
			{
				puts("NO");
				goto EndLoop;
			}
		puts("YES");
		EndLoop:; 
	}
    rtn 0;
}
```

---

## 作者：fjy666 (赞：0)

### 0x01 思路
由于整个字符串是可以 **重新排列的**，那么，字母的位置并不重要，重要的是它们的出现次数！ 

例如：在字符串 $\texttt{qwq}$ 中，$\texttt{q}$ 出现了两次，$\texttt{w}$ 出现了一次，我们把它记作 $\{2q,1w\}$ 吧！  
同理，$\texttt{aqq}$ 应该记作 $\{1a,2q\}$ 。  
接下来，将 $\{2q,1w\}$ 重排，得到 $\{1w,2q\}$ 。  
然后我们发现：$1=1,2=2$，只要将 $w \rightarrow a$ 就珂以了！

那么，只要记录每个字母出现的次数，在判断它们能否一一对应，就珂以了！  

时间复杂度：$\Theta(Tn\log n)$，其中 $n$ 是字符集的大小，在这里为 $26$。

------------
### 0x02 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
const int kMaxn = 150,kMaxm = 35;
char a[kMaxn],b[kMaxn];
int a_[kMaxm],b_[kMaxm];

int main()
{
	while(~scanf("%s%s",a,b))
	{
		memset(a_,0,sizeof(a_));
		memset(b_,0,sizeof(b_));
		char *pa = a,*pb = b;
		while(*pa)
		{
			++a_[*pa - 'A'];
			++b_[*pb - 'A'];
			++pa;
			++pb;
		}
		std::sort(a_,a_+26);
		std::sort(b_,b_+26);
		fo(i,0,25)
			if(a_[i] != b_[i])
			{
				puts("NO");
				goto EndLoop;
			}
		puts("YES");
		EndLoop:; 
	}
    rtn 0;
}
```

---

